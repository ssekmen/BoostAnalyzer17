
import re, os, sys, glob, time, logging, multiprocessing, socket, subprocess, shlex, getpass, ROOT
from optparse import OptionParser


# ---------------------- Cmd Line  -----------------------

# Read options from command line
usage = "Usage: python %prog -d <input/output dir> -m <sms model> box1 box2 box3 ..."
parser = OptionParser(usage=usage)
parser.add_option('-d','--dir',         dest="dir",         type="string",       default="",       help="Input/output directory (use output of Analyzer)")
parser.add_option('-m','--model',       dest="model",       type="string",       default="T5ttcc", help='Signal model (default="T5ttcc")')
parser.add_option('--nproc',            dest="nproc",       type="int",          default=-1,        help="Tells how many parallel combine to start (Default=6/1 - local/batch)")
parser.add_option("--batch",            dest="batch",       action="store_true", default=False,    help="Send the jobs to batch")
parser.add_option("--queue",            dest="queue",       type="string",       default="8nm",    help="Specify which batch queue to use (Default=8nm)")
parser.add_option('-n','--ncardperjob', dest="ncardperjob", type="int",          default=2,        help='Number of cards to process per batch job (default=2)')
parser.add_option('--blind',            dest="blind",       action="store_true", default=False,    help='Do not use data for limits/significance')

(opt,args) = parser.parse_args()

if opt.nproc == -1:
    opt.nproc = 1 if opt.batch else 6

boxes = args

if len(boxes)<1:
    print "Error: give additional argument(s) for the boxes to run on (eg. python scripts/combine_cards.py -d <inputdir> -m <model> WAna_nj35 WAna_nj6 TopAna"
    sys.exit()

DATE = time.strftime("%Y_%m_%d_%Hh%Mm%S", time.localtime())

# --------------------- Functions ------------------------
# Show and run command with stdout on screen
icommand=0
def special_call(cmd, verbose=1):
    global icommand, opt
    if verbose:
        print("[%d]" % icommand),
        for i in xrange(len(cmd)): print cmd[i],
        print ""
    ntry = 0
    while True:
        try:
            if subprocess.call(cmd):
                print "ERROR: Problem executing command:"
                print("[%d]" % icommand)
                for i in xrange(len(cmd)): print cmd[i],
                print ""
                print "exiting."
                sys.exit()
        except:
            print "Could not excecute command: "
            print("[%d]" % icommand)
            for i in xrange(len(cmd)): print cmd[i],
            print ""
            print "Wait 10s and continue"
            time.sleep(10)
            ntry += 1
            if ntry == 20: sys.exit()
            continue
        break
    if verbose: print ""
    sys.stdout.flush()
    icommand+=1

# Run command with stdout/stderr saved to logfile
def logged_call(cmd, logfile, append=False):
    global opt
    dirname = os.path.dirname(logfile)
    if dirname != "" and not os.path.exists(dirname):
        special_call(["mkdir", "-p", os.path.dirname(logfile)], 0)
    ntry = 0
    while True:
        try:
            with open(logfile, "a" if append else "w") as log:
                proc = subprocess.Popen(cmd, stdout=log, stderr=log, close_fds=True)
                proc.wait()
        except:
            print "Could not write to disk (IOError), wait 10s and continue"
            time.sleep(10)
            ntry += 1
            if ntry == 20: sys.exit()
            continue
        break

# Run a single Combine instance (on a single input list, i.e. one dataset)
combine_cmds = []
def combine_job((jobindex)):
    global combine_cmds, opt
    cmd = combine_cmds[jobindex]
    if opt.batch:
        print "Sending job to batch (queue: "+opt.queue+")"
        if os.getcwd().startswith("/afs"):
            log = "/tmp/dummy.log"
            cmd = shlex.split('bsub -q '+opt.queue+' -J '+DATE+'_'+str(jobindex)+' -oo '+log+' -L /bin/bash '+os.getcwd()+'/scripts/Combine_batch_job.sh '+os.environ['CMSSW_BASE']+' '+os.getcwd())+cmd
        else:
            # Currently bsub cannot send the log file to EOS, so in order to avoid annoying e-mails and LSFJOB directories,
            # we send the output to a dummy tmp file. The log output will be copied inside the script instead
            #log = "/tmp/"+getpass.getuser()+"/"+os.path.dirname(opt.OUTDIR+"/").split("/")[-1]+"/"+os.path.basename(output_log)
            log = "/tmp/dummy.log"
            #log = os.getcwd()+"/"+opt.dir+"/combine/log/"+str(jobindex)+".log"
            #if not os.path.exists(os.path.dirname(log)):
            #    special_call(["mkdir", "-p", os.path.dirname(log)], 0)
            #    special_call(['chmod', '-R', '777', "/tmp/"+getpass.getuser()], 0)
            cmd = shlex.split('bsub -q '+opt.queue+' -J '+DATE+'_'+str(jobindex)+' -oo '+log+' -L /bin/bash '+os.getcwd()+'/scripts/Combine_batch_job.sh '+os.environ['CMSSW_BASE']+' '+os.getcwd())+cmd
        special_call(cmd, 1)
        time.sleep(1)
    else:
        print "Starting new combine job: "+(" ".join(cmd))
        if opt.nproc>3: cmd = ['nice']+cmd
        log = "/tmp/dummy.log"
        logged_call(cmd, log)
    return log

# Run all Combine jobs in parallel
def run_combine(combine_cmds, nproc):
    global opt
    njob = len(combine_cmds)
    if njob<nproc: nproc = njob
    if opt.batch:
        print "Running "+str(njob)+" instances of Combine jobs on batch:"
    else:
        print "Running "+str(njob)+" instances of Combine jobs locally, using "+str(opt.nproc)+" CPUs:"
    print
    # Use the N CPUs in parallel on the current computer to run combine for all jobs
    workers = multiprocessing.Pool(processes=nproc)
    output_files = workers.map(combine_job, range(njob), chunksize=1)
    workers.close()
    workers.join()
    print "All Combine jobs finished."
    print
    return output_files

# -------------------- Run Combine -----------------------

print "Making a list of commands to run"
combine_cmds = []
for card in glob.glob(opt.dir+"/cards/RazorBoost_SMS-"+opt.model+"_*_"+boxes[0]+".txt"):
    mg   = card.replace("_"+boxes[0]+".txt","").split("_")[-2:][0]
    mchi = card.replace("_"+boxes[0]+".txt","").split("_")[-2:][1]
    if len(boxes) > 1: card = card.replace(boxes[0],"combined")
    combine_cmds.append(["python", "scripts/Combine_job.py", "--blind", "-M", "AsymptoticLimits", "-d", card]+boxes)

# Merge n commands into a single job
if opt.batch and opt.ncardperjob>1:
    new_combine_cmds = []
    for i in range(len(combine_cmds)):
        if i%opt.ncardperjob == 0:
            merged_cmds = []
        merged_cmds.append("___".join(combine_cmds[i]))
        if i+1==len(combine_cmds) or i%opt.ncardperjob == opt.ncardperjob-1:
            new_combine_cmds.append([",".join(merged_cmds)])
    combine_cmds = new_combine_cmds

# For testing a single job
#combine_cmds = combine_cmds[:1]

# Run combine
if not os.path.exists(opt.dir+"/combine"): special_call(["mkdir", "-p", opt.dir+"/combine"], 0)
run_combine(combine_cmds, opt.nproc)

print "Done."

