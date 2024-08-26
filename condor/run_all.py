import re, os, sys, glob, time, logging, multiprocessing, socket, subprocess, shlex, getpass, math, ROOT
from argparse import ArgumentParser
from common_functions import *

# ---------------------- Cmd Line  -----------------------

# Read options from command line
usage = "Usage: python %prog filelists [options]"
parser = ArgumentParser(usage=usage)
parser.add_argument("--run",         dest="run",         action="store_true", default=False, help="Without this option, script only prints cmds it would otherwise excecute")
parser.add_argument("--full",        dest="full",        action="store_true", default=False, help="Run on all datasets found in filelists directory")
parser.add_argument("--test",        dest="test",        action="store_true", default=False, help="Run only on some test files (jetht, ttbar, qcd, T5ttcc)")
parser.add_argument("--batch",       dest="batch",       action="store_true", default=False, help="Send the jobs to batch")
parser.add_argument("--condor",      dest="condor",      action="store_true", default=True,  help="Send the jobs to condor")
parser.add_argument("--queue",       dest="QUEUE",       type=str,       default="1nh", help="Specify which batch queue to use on LxBatch (Default=1nh)")
parser.add_argument("--optim",       dest="optim",       action="store_true", default=True,  help="Optimize job event number based log files in --prevdir, or measured skim ratios")
parser.add_argument("--prevdir",     dest="PREVDIR",     type=str,       default="",    help="Previous running directory used to optimize jobs (default=last dir in results/)")
parser.add_argument("--jobtime",     dest="JOBTIME",     type=int,          default=1500,  help="Desired job running time in s (default=1500)")
parser.add_argument("--quick",       dest="NQUICK",      type=int,          default=0,     help="Run only on a subset of events (1/NQUICK)")
parser.add_argument("--nevt",        dest="NEVT",        type=int,          default=-1,    help="Tells how many event to run as a maximum in a single job (Default=-1 all)")
parser.add_argument("--nfile",       dest="NFILE",       type=int,          default=-1,    help="Tells how many input files to run in a single job (Default=-1 all)")
parser.add_argument("--sleep",       dest="SLEEP",       type=int,          default=3,     help="Wait for this number of seconds between submitting each batch job (Default 3s)")
parser.add_argument("--useprev",     dest="useprev",     action="store_true", default=False, help="Use previously created temporary filelists")
parser.add_argument("--nproc",       dest="NPROC",       type=int,          default=1,     help="Tells how many parallel interactive jobs to start (Default=3)")
parser.add_argument("--outdir",      dest="OUTDIR",      type=str,       default="",    help="Output directory (Default: results/run_[SUBTIME])")
parser.add_argument("--skimout",     dest="SKIMOUT",     type=str,       default="",    help="Output directory for skimming")
parser.add_argument("--skim",        dest="skim",        action="store_true", default=False, help="Skim output to --skimout directory (change in script)")
parser.add_argument("--mirror",      dest="mirror",      action="store_true", default=False, help="Also copy skim output to EOS")
parser.add_argument("--mirror_user", dest="mirror_user", action="store_true", default=False, help="Also copy skim output to Janos' EOS")
parser.add_argument("--plot",        dest="plot",        action="store_true", default=False, help="Make plots after running using Plotter (Janos)")
parser.add_argument("--replot",      dest="replot",      action="store_true", default=False, help="Remake latest set of plots using Plotter (Janos)")
parser.add_argument("--recover",     dest="recover",     action="store_true", default=False, help="Recover stopped task (eg. due to some error)")
parser.add_argument("--nohadd",      dest="nohadd",      action="store_true", default=False, help="Disable hadding output files")
parser.add_argument("--nocheck",     dest="nocheck",     action="store_true", default=False, help="Disable nevent check for output files")
parser.add_argument("--haddonly",    dest="haddonly",    action="store_true", default=False, help="Do not submit any jobs, only merge output")
parser.add_argument("--update",      dest="update",      action="store_true", default=False, help="Update/Bugfix the Analyzer/Plotter code and recompile")
opt = parser.parse_args()

# ----------------------  Settings -----------------------
# Some further (usually) fixed settings, should edit them in this file

# Make sure we start with a fresh token (lasts 24h)
#if 'lxplus' in socket.gethostname(): special_call(["kinit", "-R"], opt.run, 0)

# Output directories/files
SUBTIME = time.strftime("%Y_%m_%d_%Hh%Mm%S", time.localtime())
TMPDIR = "/tmp/"+getpass.getuser()+"/"
if socket.gethostname() == 'login.uscms.org':
    TMPDIR = TMPDIR.replace("/tmp/","/local-scratch/")
if opt.OUTDIR == "" and not opt.skim and not opt.replot:
    opt.OUTDIR = "results/run_"+SUBTIME # log files, backup files, output files for non-skims

if opt.skim:
    COPYSCRIPT = ""
    if opt.OUTDIR == "":
        opt.OUTDIR = "results/skim_"+SUBTIME # log files, backup files, output files for non-skims
    # Mirror also here
    if opt.SKIMOUT == "":
        print("ERROR: Give a suitable --skimout argument, eg. --skimout ntuple/grid18/Skim_Oct31_2Jet_1JetAK8")
        sys.exit()
    if opt.NFILE == -1 and opt.NEVT == -1 and not opt.optim and not opt.useprev:
        print("ERROR: Give a suitable --nfile, --nevt or --optim argument, otherwise output might become too large!")
        sys.exit()
    if opt.NQUICK>1:
        if opt.mirror or opt.mirror_user:
            print("ERROR: Please, don't mirror stuff to EOS, when testing!")
            sys.exit()
    else:
        if opt.mirror:
            # --mirror copies here
            EOS_JANOS  = "gsiftp://eoscmsftp.cern.ch//eos/cms/store/caf/user/jkarancs/B2GTTreeNtuple/"
        elif opt.mirror_user:
            # --mirror copies here
            EOS_JANOS  = "root://eosuser.cern.ch//eos/user/j/jkarancs/B2GTTreeNtuple/"
        else:
            # If not, then makes a script for Viktor
            EOS_VIKTOR = "gsiftp://eoscmsftp.cern.ch//eos/cms/store/caf/user/veszpv/B2GTTreeNtuple/"
            COPYSCRIPT = opt.SKIMOUT.replace(opt.SKIMOUT.split("/")[-1],"")+"mirror_to_Viktors_EOS_"+opt.SKIMOUT.split("/")[-1]+".sh"
            print("Warning: Don't you want to mirror to EOS? Add: --mirror option!")
            print("         If not, ignore this message!")
            print(("         Creating a copy script for Viktor: "+COPYSCRIPT))

if opt.NEVT == -1 and opt.optim:
    print("Set default NEVT = 1000000 (optimized for 2 hour jobs)")
    opt.NEVT = 1000000
if opt.batch and opt.NEVT == -1 and not opt.optim and not opt.useprev and not opt.condor:
    print("ERROR: Give a suitable --nevt or --optim argument, otherwise some jobs will run too long on batch!")
    print("       Recommended to start with: --queue=8nh --nevt=1000000")
    print("       Then next time, you can use default 1nh queue with ~1500s jobs using: --optim")
    print("       If too many jobs fail, try lowering job runtime eg: --optim --jobtime=1200")
    print("       Or use --useprev option to run on previously created temporary filelists")
    sys.exit()
#if opt.optim and not opt.skim and opt.PREVDIR == "":
#    sorted_dirs = sorted(glob.glob("results/*/"), key=os.path.getmtime)
#    if len(sorted_dirs):
#        opt.PREVDIR = sorted_dirs[-1][:-1]
#        print("Using --optim option, but no --prevdir argument was given, using previous working directory: "+opt.PREVDIR
#    else:
#        print("ERROR: Using --optim option, but no --prevdir argument was given, and cannot find previous working directory in results/*"
#        sys.exit()
if opt.plot:
    #PLOTTER_IN automatic
    if opt.test:
        PLOTTER_OUT = "results/Plotter_test.root"
    else:
        PLOTTER_OUT = opt.OUTDIR.replace("run_","Plotter_out_")+".root"
if opt.replot:
    if opt.OUTDIR == "":
        # Find last working directory automatically and find output files there
        opt.OUTDIR  = max(glob.glob("results/run_*"), key=os.path.getmtime)
        PLOTTER_IN  = max(glob.glob("results/Plotter_out_*.root"), key=os.path.getmtime).replace("_replot","")
        PLOTTER_OUT = PLOTTER_IN.replace(".root","_replot.root")
        PLOTTER_IN  = [PLOTTER_IN]
    else:
        PLOTTER_IN  = sorted(glob.glob(opt.OUTDIR+"/*.root"))
        PLOTTER_OUT = opt.OUTDIR.replace("run_","Plotter_out_")+"_replot.root"

# Working directory, during running we cd here and back
if opt.test:
    EXEC_PATH = os.getcwd()
elif opt.replot:
    EXEC_PATH = opt.OUTDIR+"/BoostAnalyzer17_replot"
else:
    EXEC_PATH = opt.OUTDIR+"/BoostAnalyzer17"

# Print some options for logging
if not opt.run:
    print("--run option not specified, doing a dry run (only printing out commands)")

if opt.full:
    print("Running with option: --full")
if opt.skim:
    print("Running with option: --skim")
elif opt.replot:
    print("Running with option: --replot")
    opt.plot = 0 # for safety
elif opt.test:
    print("Running with option: --test (few files)")

if opt.plot:
    print("Running with option: --plot (will produce plots with Plotter)")

if opt.NQUICK>1:
    print(("Running with option: --quick "+str(opt.NQUICK)+" (1/"+str(opt.NQUICK)+" statistics)"))

# Some automatic filelists
if opt.recover:
    saved_path = os.getcwd()
    os.chdir(EXEC_PATH)
    input_filelists  = sorted(glob.glob("filelists/*/data/*.txt"))
    input_filelists += sorted(glob.glob("filelists/*/backgrounds/*.txt"))
    input_filelists += sorted(glob.glob("filelists/*/signals/*.txt"))
    os.chdir(saved_path)
elif opt.full:
    input_filelists  = sorted(glob.glob("filelists/*/data/*.txt"))
    input_filelists += sorted(glob.glob("filelists/*/backgrounds/*.txt"))
    input_filelists += sorted(glob.glob("filelists/*/signals/*.txt"))
elif opt.test:
    input_filelists  = sorted(glob.glob("filelists/2017/data/JetHT*.txt"))
    input_filelists += sorted(glob.glob("filelists/2017/backgrounds/QCD_HT*.txt"))
    input_filelists += sorted(glob.glob("filelists/2017/backgrounds/TT_powheg-pythia8_ext4*.txt"))
    input_filelists += sorted(glob.glob("filelists/2017/signals/FastSim_SMS-T5ttcc*.txt"))
elif not opt.replot:
    print("Always tell me what filelists to run over (except when using --full or --test options)!")
    print(("For more help, run as python %s -h" % (sys.argv[0])))
    sys.exit()
else:
    input_filelists = ""

# Read some options from included settings_*.h file
with open("Analyzer.cc") as ana:
    for line in ana:
        if '#include "settings' in line:
            settings_file = line.split()[1].replace('"','')
vary_syst = False
with open(settings_file) as settings:
    for line in settings:
        if "define SYST" in line and not "0" in line:
            vary_syst = True

# ----------------- Analyzer Arguments -------------------
# Analyzer (see below in functions):
# Each element supplies 3 arguments for each Analyzer job:
# [output filename, input file list, output log]
# For skimming/full running, all datasets are used
# for testing a selected few

if opt.recover:
    if not opt.useprev:
        opt.useprev = True
    if os.path.exists(opt.OUTDIR+"/log/condor_joblist_EU.txt"):
        os.remove(opt.OUTDIR+"/log/condor_joblist_EU.txt")
    if os.path.exists(opt.OUTDIR+"/log/condor_joblist_US.txt"):
        os.remove(opt.OUTDIR+"/log/condor_joblist_US.txt")
if opt.useprev:
    if os.path.exists(EXEC_PATH+'/filelists_tmp/job_splitting.txt'):
        opt.optim = True

if opt.useprev:
    print("Reusing previously created temporary filelists for split jobs (eg. --batch) in filelists_tmp/:")
elif (opt.NFILE != -1 or opt.NEVT != -1):
    print("Start creating new temporary filelists for split jobs (eg. batch) in filelists_tmp/:")
    for tmp_txtfile in glob.glob('filelists_tmp/*/*/*.txt'): os.remove(tmp_txtfile)
    if os.path.exists('filelists_tmp/job_splitting.txt'): os.remove('filelists_tmp/job_splitting.txt')

ana_arguments = []
if not opt.useprev and (opt.NEVT != -1 or opt.optim):
    # Save job splitting info
    job_splitting_file = open('filelists_tmp/job_splitting.txt', 'w')

# get optimization event ratios
optim_ratios = {}
def get_optim_ratios(opt, samplename):
    global optim_ratios
    if samplename in list(optim_ratios.keys()):
        return optim_ratios[samplename]
    else:
        optim = 1.0
        if opt.optim:
            optim_found = False
            # Skimming uses a text file (skim_ratios.txt)
            if opt.skim:
                with open("skim_ratios.txt") as ratios:
                    for line in ratios:
                        column = line.split()
                        #if samplename == column[2]:
                        if column[1] in samplename and not optim_found:
                            optim = float(column[0])
                            optim_found = True
            else:
                # Other jobs use the results (job_ratios.txt) from a previous run
                # generated by calc_job_optim.py using the JobMonitoringReport from previous logs file 
                with open("systjob_ratios.txt" if vary_syst else "job_ratios.txt") as ratios:
                    for line in ratios:
                        column = line.split()
                        if samplename == column[1]:
                            #optim = float(column[0]) * 0.8
                            optim = float(column[0])
                            optim_found = True
                # If no optimization found (happens rarely for new samples), use 0.2 (to be safe for all samples)
                # Make sure to remake the job_ratios.txt file after the run!
                if not optim_found:
                    print(("No optimization found for "+samplename+" using 1.0"))
                    optim = 1.0
        optim_ratios[samplename] = optim
        return optim

# get filelist counts and site infos
# determined by condor/setup.py script
counts = {}
sites = {}


countfileloc = "condor/filelist_and_counts.txt"
if opt.recover: countfileloc = EXEC_PATH+"/condor/filelist_and_counts.txt"
with open(countfileloc, 'r') as counts_file:
    for line in counts_file.readlines():
        counts[line.split()[0]] = int(line.split()[1])
        sites[line.split()[0]]  = line.split()[2]

# Loop over all filelists
for filelist in input_filelists:
    # Options for Analyzer
    options = []
    if opt.NQUICK>1: options.append("quickTest="+str(opt.NQUICK))
    if opt.skim and not opt.plot: options.append("noPlots=1")
    
    # decide year, based on subdirectory
    year="2016"
    if "/2017/" in filelist:
        year = "2017"
    elif "/2018/" in filelist:
        year = "2018"
    elif "/2016APV/" in filelist:
        year = "2016APV"
    options.append("year="+year)
    
    # Will put all files into the OUTDIR and its subdirectories
    log_file = opt.OUTDIR+"/log/"+year+"_"+filelist.split("/")[-1].replace("txt", "log")
    if opt.skim:
        # Except for skim, where we send the large output files to a different directory
        # keeping subdirectory structure (suitable for a future input )
        output_file = opt.SKIMOUT+"/"+year+"_"+filelist.split("/")[-1].replace(".txt","/Skim.root")
    else:
        output_file = opt.OUTDIR +"/"+year+"_"+filelist.split("/")[-1].replace("txt", "root")
    
    # Temporary filelists
    if opt.useprev:
        #print(filelist
        #print(len(ana_arguments)
        # Use previously created lists
        #if not opt.skim: options.append("fullFileList="+filelist) # Need full ntuple to correctly normalize weights
        jobsplit_options = {}
        if opt.recover:
            saved_path = os.getcwd()
            os.chdir(EXEC_PATH)
        if opt.NEVT != -1 or opt.optim:
            with open("filelists_tmp/job_splitting.txt") as job_splitting_file:
                for line in job_splitting_file.readlines():
                    jobsplit_options[line.split()[0]] = line.split()[1:]
        prev_lists = sorted(glob.glob(filelist.replace("filelists","filelists_tmp").replace(".txt","_[0-9]*.txt")))
        new_lists = []
        for jobnum in range(1,1+len(prev_lists)):
            new_lists.append(filelist.replace("filelists","filelists_tmp").replace(".txt","_"+str(jobnum)+".txt"))
        #prev_lists = new_lists
        if opt.recover:
            os.chdir(saved_path)
        for i in range(0, len(new_lists)):
            tmp_filelist = new_lists[i]
            #jobnum = tmp_filelist.replace(".txt","").split("_")[-1]
            jobnum = i+1
            job_opt = list(options)
            if opt.NEVT != -1 or opt.optim:
                job_opt += jobsplit_options[tmp_filelist]
            job_args = [output_file.replace(".root","_"+str(jobnum)+".root"), [EXEC_PATH+"/"+tmp_filelist], job_opt, log_file.replace(".log","_"+str(jobnum)+".log")]
            ana_arguments.append(job_args)        
    elif opt.NEVT != -1 or opt.optim:
        # SPLIT MODE (recommended for batch): Each jobs runs on max opt.NEVT
        
        # Options: Need full ntuple to correctly normalize weights (OBSOLETE)
        #if not opt.skim: options.append("fullFileList="+EXEC_PATH+"/"+filelist) # Need full ntuple to correctly normalize weights
        
        nevtperjob_sample = opt.NEVT
        # Further optimize this number
        # based on measured unskimmed to skimmed ratios (found in skim_ratios.txt)
        if opt.optim:
            samplename = year+"_"+filelist.split("/")[-1][:-4]
            nevtperjob_sample = int(get_optim_ratios(opt, samplename) * opt.NEVT)
        
        # Loop on file lists and split to tmp_filelists for nevt < nevtperjob_sample
        with open(filelist, 'r') as f:
            files = f.read().splitlines()
            jobnum = 0
            ifirst = 0
            curr_nevt = 0
            curr_files = []
            curr_max_nevt = 0
            for i in range(0, len(files)):
                nevt = counts[files[i]]
                # First get the number of events in the file from txt file created by condor/setup.py
                if files[i] in counts:
                    nevt = counts[files[i]]
                else:
                    print("ERROR: File not found in condor/filelist_and_counts.txt")
                    print((files[i]))
                    sys.exit()
                # OLD method: Create a new list after every nevtperjob_sample
                #if i==0 or (curr_nevt + nevt > nevtperjob_sample):
                #    jobnum += 1
                #    tmp_filelist = filelist.replace("filelists","filelists_tmp").replace(".txt","_"+str(jobnum)+".txt")
                #    job_args = [output_file.replace(".root","_"+str(jobnum)+".root"), [EXEC_PATH+"/"+tmp_filelist], options, log_file.replace(".log","_"+str(jobnum)+".log")]
                #    ana_arguments.append(job_args)
                #    curr_nevt = 0
                #curr_nevt += nevt
                #ntry = 0
                #while True:
                #    try:
                #        with open(tmp_filelist, "a") as job_filelist:
                #            print>>job_filelist, files[i]
                #    except:
                #        print("Warning: Could not write to disk (IOError), wait 10s and continue"
                #        time.sleep(10)
                #        ntry += 1
                #        if ntry == 20: sys.exit()
                #        continue
                #    break
                
                # New method, split jobs by exactly configurable event number (ignore input file boundaries)
                if not "/data/" in filelist:
                    # MC - Contains files with same branches, so exactly nevt jobs can be specified
                    curr_nevt += nevt
                    curr_files.append(files[i])
                    curr_max_nevt += nevt
                    while curr_nevt >= nevtperjob_sample:
                        # job options
                        job_opt = list(options)
                        opt_save = []
                        job_opt.append("ifirst="+str(int(ifirst)))
                        opt_save.append("ifirst="+str(int(ifirst)))
                        ilast = ifirst + nevtperjob_sample
                        if ilast <= curr_max_nevt:
                            job_opt.append("ilast="+str(int(ilast)))
                            opt_save.append("ilast="+str(int(ilast)))
                        # filelist
                        jobnum += 1
                        tmp_filelist = filelist.replace("filelists","filelists_tmp").replace(".txt","_"+str(jobnum)+".txt")
                        with open(tmp_filelist, "w") as job_filelist:
                            for filename in curr_files:
                                print(filename, file=job_filelist)
                        job_args = [output_file.replace(".root","_"+str(jobnum)+".root"), [EXEC_PATH+"/"+tmp_filelist], job_opt, log_file.replace(".log","_"+str(jobnum)+".log")]
                        ana_arguments.append(job_args)
                        # save job splitting info for later recovery/useprev etc.
                        print(tmp_filelist+" "+(" ".join(opt_save)), file=job_splitting_file)
                        # prepare next iteration
                        curr_nevt -= nevtperjob_sample
                        if ilast == curr_max_nevt:
                            ifirst = 0
                        else:
                            ifirst = nevt - curr_nevt
                        curr_files = []
                        curr_max_nevt = 0
                        if ifirst > 0:
                            curr_files.append(files[i])
                            curr_max_nevt += nevt
                    # Add rest to last job
                    if i+1 == len(files) and (ifirst != 0 or (ifirst==0 and jobnum==0)):
                        # job options
                        job_opt = list(options)
                        opt_save = []
                        job_opt.append("ifirst="+str(int(ifirst)))
                        opt_save.append("ifirst="+str(int(ifirst)))
                        job_opt.append("ilast="+str(int(curr_max_nevt)))
                        opt_save.append("ilast="+str(int(curr_max_nevt)))
                        # filelist
                        jobnum += 1
                        tmp_filelist = filelist.replace("filelists","filelists_tmp").replace(".txt","_"+str(jobnum)+".txt")
                        with open(tmp_filelist, "w") as job_filelist:
                            for filename in curr_files:
                                print(filename, file=job_filelist)
                                #print(filename, job_filelist)
                        job_args = [output_file.replace(".root","_"+str(jobnum)+".root"), [EXEC_PATH+"/"+tmp_filelist], job_opt, log_file.replace(".log","_"+str(jobnum)+".log")]
                        ana_arguments.append(job_args)
                        # save job splitting info for later recovery/useprev etc.
                        print(tmp_filelist+" "+(" ".join(opt_save)), file=job_splitting_file)
                else:
                    # Data - Contains files that cannot be merged in TChain due to different branches (L1 bit for eg.)
                    # Use maximum 1 file per job and split them if a smaller event number is required
                    ifirst = 0
                    nsplit = int(math.ceil(float(nevt)/float(nevtperjob_sample)))
                    nevtperjob = int(math.ceil(float(nevt)/nsplit))
                    for isplit in range(nsplit):
                        # job options
                        job_opt = list(options)
                        opt_save = []
                        ilast = min(ifirst + nevtperjob, nevt)
                        job_opt.append("ifirst="+str(int(ifirst)))
                        opt_save.append("ifirst="+str(int(ifirst)))
                        job_opt.append("ilast="+str(int(ilast)))
                        opt_save.append("ilast="+str(int(ilast)))
                        # filelist
                        jobnum += 1
                        tmp_filelist = filelist.replace("filelists","filelists_tmp").replace(".txt","_"+str(jobnum)+".txt")
                        with open(tmp_filelist, "w") as job_filelist:
                            print(files[i], file=job_filelist)
                        job_args = [output_file.replace(".root","_"+str(jobnum)+".root"), [EXEC_PATH+"/"+tmp_filelist], job_opt, log_file.replace(".log","_"+str(jobnum)+".log")]
                        ana_arguments.append(job_args)
                        # save job splitting info for later recovery/useprev etc.
                        print(tmp_filelist+" "+(" ".join(opt_save)), file=job_splitting_file)
                        # prepare next iteration
                        ifirst = ilast
        
        # Some printouts
        if opt.optim:
            print(("  "+filelist.replace("filelists","filelists_tmp").replace(".txt","_*.txt")+" created (MAX NEVT (optim) = "+str(nevtperjob_sample)+")"))
        else:
            print(("  "+filelist.replace("filelists","filelists_tmp").replace(".txt","_*.txt")+" created"))
    elif opt.NFILE != -1:
        # SPLIT MODE: Each jobs runs on max opt.NFILE
        #if not opt.skim: options.append("fullFileList="+EXEC_PATH+"/"+filelist) # Need full ntuple to correctly normalize weights
        with open(filelist) as f:
            files = f.read().splitlines()
            for n in range(1, (len(files)-1)/opt.NFILE+2):
                tmp_filelist = filelist.replace("filelists","filelists_tmp").replace(".txt","_"+str(n)+".txt")
                with open(tmp_filelist, "w") as job_filelist:
                    for i in range((n-1)*opt.NFILE, min(n*opt.NFILE,len(files))):
                        print(files[i], file=job_filelist)
                job_args = [output_file.replace(".root","_"+str(n)+".root"), [EXEC_PATH+"/"+tmp_filelist], options, log_file.replace(".log","_"+str(n)+".log")]
                ana_arguments.append(job_args)
    else:
        # In case of a single job/dataset
        ana_arguments.append([output_file, [EXEC_PATH+"/"+filelist], options, log_file])

if not opt.useprev and (opt.NEVT != -1 or opt.optim):
    job_splitting_file.close()

print(("Number of jobs: "+str(len(ana_arguments))))

# Determine the sites to run the job for condor
# Check if the input file is in the EU/US and set the site there if needed
for i in range(0, len(ana_arguments)):
    tmp_filelist = ana_arguments[i][1][0]
    if not opt.useprev and not opt.recover:
        tmp_filelist = tmp_filelist.replace(EXEC_PATH+"/","")
    with open(tmp_filelist) as job_filelist:
        filename = job_filelist.read().splitlines()[0]
        condor_site = sites[filename]
    ana_arguments[i].append(condor_site)

# Recover info about previously submitted jobs
last_known_status = [-1] * len(ana_arguments) # -1: start, 0: finished, time(): last submit/status check
last_condor_jobid = [""] * len(ana_arguments)
batch_number = 0
cluster_ids = []
found_jobs = []
if opt.recover:
    if opt.batch:
        nrecov = 0
        if opt.condor:
            # Recover latest condor submissions
            for condor_log_file in sorted(glob.glob(opt.OUTDIR+"/log/condor_task_*.log"), key=os.path.getmtime):
                batch_number = int(condor_log_file.split("_")[-1].replace(".log","")) + 1 # increment for the next submission
                with open(condor_log_file) as condor_log:
                    for line in condor_log.readlines():
                        if "submitted to cluster" in line:
                            clusterid = line.split()[-1].replace(".","")
                            cluster_ids.append(clusterid)
            if len(cluster_ids):
                print(("Recovering jobs from cluster ids: "+(" ".join(cluster_ids))))
                logged_call(shlex.split('condor_q -w --nobatch '+(" ".join(cluster_ids))), TMPDIR+'batchstatus_'+cluster_ids[-1]+'.txt', 1)
                with open(TMPDIR+'batchstatus_'+clusterid+'.txt') as batchstatus:
                    lines = batchstatus.readlines()
                    for line in lines:
                        for clusterid in cluster_ids:
                            if line.startswith(clusterid+"."):
                                job_status = line.split()[5]
                                if job_status != "X":
                                    jobid = line.split()[0]
                                    input_tmp_filelist = line.split()[9]
                                    for i in range(0, len(ana_arguments)):
                                        if input_tmp_filelist == ana_arguments[i][1][0].replace(EXEC_PATH+"/",""):
                                            jobindex = i
                                    output_file = ana_arguments[jobindex][0]
                                    if output_file not in found_jobs:
                                        if not os.path.exists(output_file):
                                            found_jobs.append(output_file)
                                            last_known_status[jobindex] = int(time.time())
                                            last_condor_jobid[jobindex] = jobid
                                            nrecov += 1
                                            #print("- Found running HTCondor job: ID = "+jobid+" ("+input_tmp_filelist+", jobindex = "+str(jobindex)+")"
                os.remove(TMPDIR+'batchstatus_'+cluster_ids[-1]+'.txt')
        else:
            # Check if the submission time is available
            if os.path.exists(EXEC_PATH+"/creation_time.txt"):
                with open(EXEC_PATH+"/creation_time.txt") as sub_time:
                    SUBTIME=sub_time.readline().replace('\n','')
                    print(("Recovering previous jobs with submission time: "+SUBTIME))
                    # Check status of all running/pending jobs on lxbatch
                    logged_call(shlex.split('bjobs -W -noheader'), TMPDIR+'batchstatus_'+SUBTIME+'.txt', 1)
                    with open(TMPDIR+'batchstatus_'+SUBTIME+'.txt') as batchstatus:
                        lines = batchstatus.readlines()
                        for line in lines:
                            if not "job found" in line: # output can be: "No unfinished job found"
                                jobname = line.split()[6]
                                if jobname.startswith(SUBTIME):
                                    jobindex = int(jobname.split("_")[-1])
                                    last_known_status[jobindex] = int(time.time())
                                    nrecov += 1
                    os.remove(TMPDIR+'batchstatus_'+SUBTIME+'.txt')
        print(("Successfully recovered "+str(nrecov)+" running jobs from previous submissions"))

if opt.NFILE != -1 or opt.NEVT != -1 and not opt.useprev:
    print("All temporary filelist ready.")
    print()

# --------------------- Functions ------------------------

# backup files for bookkeeping
def backup_files(backup_dir, creation_time, update):
    if update:
        if os.path.exists(backup_dir+"_orig"):
            special_call(["rm", "-rf", backup_dir], opt.run)
        else:
            special_call(["mv", backup_dir, backup_dir+"_orig"], opt.run)
    else:
        print(("Backing up files in: "+backup_dir))
        print()
    if not os.path.exists(backup_dir): special_call(["mkdir", "-p", backup_dir], opt.run)
    special_call(["cp", "-rpL", "btag_eff", "condor", "correction_factors", "data", "filelists", "filelists_tmp", "include", "pileup", "python", "scale_factors", "scripts", "src", "systematics", "trigger_eff", "setup.sh"] + glob.glob("*.h") + glob.glob("*.cc") + glob.glob("*ratios.txt") + glob.glob("Makefile*") + [backup_dir+"/"], opt.run)
    #special_call(["mv", backup_dir+"/RazorBoost-CMS-Connect", backup_dir+"/condor"], opt.run)
    special_call(["rm", "-rf", backup_dir+"/condor/.git"], opt.run)
    if not opt.update:
        with open(backup_dir+"/creation_time.txt","w") as sub_time:
            print(creation_time, file=sub_time)
    print()

# Compile programs
def compile(Ana = 1, Plotter = 1):
    global opt, EXEC_PATH
    print("Compiling ...")
    print()
    saved_path = os.getcwd()
    if opt.run: os.chdir(EXEC_PATH)
    special_call(["make", "clean"], opt.run)
    if Ana:
        special_call(["make", "-j8", "Analyzer"], opt.run)
        special_call(["chmod", "777", "Analyzer"], opt.run)
    if Plotter:
        special_call(["make", "-j8", "Plotter"], opt.run)
        special_call(["chmod", "777", "Plotter"], opt.run)
    # Copy the results folder to the uscms stash server
    if opt.run: os.chdir(saved_path)
    print()

def create_sandbox(backup_dir, update):
    print("Creating sandbox for condor")
    print()
    #sandbox = os.path.split(backup_dir)[0]+"/sandbox-BoostAnalyzer17.tar"
    sandbox = "sandbox-BoostAnalyzer17.tar"
    if update:
        special_call(["rm", sandbox], opt.run)
    special_call(["tar", "-cf", sandbox, "-C", os.path.split(backup_dir)[0], "BoostAnalyzer17"], opt.run)
    print()

# Run a single Analyzer instance (on a single input list, i.e. one dataset)
def analyzer_job(jobindex):
    global ana_arguments, opt, EXEC_PATH, COPYSCRIPT
    output_file = ana_arguments[jobindex][0]
    input_list  = ana_arguments[jobindex][1]
    options     = ana_arguments[jobindex][2]
    output_log  = ana_arguments[jobindex][3]
    condor_site = ana_arguments[jobindex][4]
    if opt.run:
        if opt.batch:
            if not opt.condor:
                print(("Sending job to LxBatch (queue: "+opt.QUEUE+"), expected output: "+output_file))
        else:
            print(("Start Analyzing, expected output: "+output_file))
    if not os.path.exists(os.path.dirname(output_file)):
        special_call(["mkdir", "-p", os.path.dirname(output_file)], opt.run, 0)
    cmd = [EXEC_PATH+"/Analyzer", output_file] + options + input_list
    if opt.batch:
        logdirname = os.path.dirname(output_log)
        if logdirname != "" and not os.path.exists(logdirname): special_call(["mkdir", "-p", logdirname], opt.run, 0)
        if opt.condor:
            with open(opt.OUTDIR+"/log/condor_joblist_"+condor_site+".txt", "a") as joblist:
                output_out = output_log.replace(".log",".out")
                output_err = output_log.replace(".log",".err")
                filelist = input_list[0].replace(EXEC_PATH+"/","")
                print(output_out+', '+output_err+', '+output_log+', "output.root='+output_file+'", '+filelist+' '+' '.join(options), file=joblist)
                #print>>joblist, output_out+', '+output_err+', '+output_log+', "output.root='+output_file+'", '+filelist
        else:
            # Submit job to lxbatch (immediately)
            if os.getcwd().startswith("/afs"):
                cmd = shlex.split('bsub -q '+opt.QUEUE+' -J '+SUBTIME+'_'+str(jobindex)+' -oo '+output_log+' -L /bin/bash '+os.getcwd()+'/scripts/Analyzer_batch_job.sh '+os.getcwd()+' '+output_log)+cmd
            else:
                # Currently bsub cannot send the log file to EOS, so in order to avoid annoying e-mails and LSFJOB directories,
                # we send the output to a dummy afs file. The log output will be copied inside the script instead
                #job_log = "/tmp/"+getpass.getuser()+"/"+os.path.dirname(opt.OUTDIR+"/").split("/")[-1]+"/"+os.path.basename(output_log)
                job_log = "/tmp/"+os.path.basename(output_log)
                #if not os.path.exists(os.path.dirname(job_log)):
                #    special_call(["mkdir", "-p", os.path.dirname(job_log)], opt.run, 0)
                #    special_call(['chmod', '-R', '777', "/tmp/"+getpass.getuser()], opt.run, 0)
                #cmd = shlex.split('bsub -q '+opt.QUEUE+' -J '+SUBTIME+'_'+str(jobindex)+' -oo '+job_log+' -L /bin/bash '+os.getcwd()+'/scripts/Analyzer_batch_job.sh '+os.getcwd()+' '+output_log)+cmd
                if vary_syst:
                    cmd = shlex.split('bsub -M 3500000 -v 5000000 -q '+opt.QUEUE+' -J '+SUBTIME+'_'+str(jobindex)+' -oo '+job_log+' -L /bin/bash '+os.getcwd()+'/scripts/Analyzer_batch_job.sh '+os.getcwd()+' '+output_log)+cmd
                else:
                    cmd = shlex.split('bsub -M 1500000 -v 3000000 -q '+opt.QUEUE+' -J '+SUBTIME+'_'+str(jobindex)+' -oo '+job_log+' -L /bin/bash '+os.getcwd()+'/scripts/Analyzer_batch_job.sh '+os.getcwd()+' '+output_log)+cmd
            special_call(cmd, opt.run, not opt.run)
            time.sleep(opt.SLEEP)
    else:
        if opt.NPROC>3: cmd = ['nice']+cmd
        logged_call(cmd, output_log, opt.run)
    # Mirror output (copy to EOS)
    if opt.skim:
        outpath = output_file.split("/")[-3]+"/"+output_file.split("/")[-2]+"/"+output_file.split("/")[-1]
        if opt.mirror or opt.mirror_user: logged_call(["env", "--unset=LD_LIBRARY_PATH", "gfal-copy", "-f", "-r", output_file, EOS_JANOS+outpath], output_log, opt.run)
        elif opt.run and opt.NQUICK==0:
            with open(COPYSCRIPT, "a") as script:
                print('env --unset=LD_LIBRARY_PATH gfal-copy -r '+output_file+' '+EOS_VIKTOR+outpath, file=script)
                #print>>script, 'srm-set-permissions -type=CHANGE -group=RW '+EOS_VIKTOR+outpath
    return output_file


def hadd_job(output, list, log, batch=True):
    if batch:
        special_call(["truncate", "-s", "1K", output], opt.run, 0)
        #logged_call(["condor/submit_condor_task.sh", "hadd", ",".join(list), output, log.replace(".log","")], log.replace(".log","_condor.log"), opt.run)
        logged_call(["hadd", "-f", "-v", output]+list, log, opt.run)
    else:
        logged_call(["hadd", "-f", "-v", output]+list, log, opt.run)

def merge_output(ana_arguments, last_known_status):
    # Check list of files ready to be merged (with hadd)
    if not os.path.exists(opt.OUTDIR+"/hadd"): special_call(["mkdir", "-p", opt.OUTDIR+"/hadd"], opt.run, 0)
    prev_sample = ""
    mergeables = []
    all_mergeables = []
    njob = len(ana_arguments)
    all_hadded = []
    for i in range(0, njob):
        job_index = ana_arguments[i][0][:-5].split("_")[-1]
        sample = ana_arguments[i][0][:-(6+len(job_index))]
        if sample != prev_sample:
            prev_sample = sample
            ready_to_merge = True
            if len(mergeables)>1: all_mergeables.append(mergeables)
            hadded_filename = sample.rsplit("/",1)[0]+"/hadd/"+sample.rsplit("/",1)[1]+".root"
            mergeables = [hadded_filename]
            all_hadded.append(hadded_filename)
        if ready_to_merge:
            if last_known_status[i]==0:
                mergeables.append(ana_arguments[i][0])
            else:
                ready_to_merge = False
                mergeables = []
        #print(("%4d - %d - missing=%d - %s" % (i, ready_to_merge, last_known_status[i]==-1, ana_arguments[i][0]))
    if ready_to_merge: all_mergeables.append(mergeables)
    # Merge them if they are ready
    for i in range(0, len(all_mergeables)):
        output   = all_mergeables[i][0]
        log      = output.rsplit("/",1)[0]+"/log/"+output.rsplit("/",1)[1].replace(".root",".log")
        allinput = all_mergeables[i][1:]
        mergeonbatch = False
        if os.path.exists(output):
            if os.path.getsize(output)==1024 and (time.time()-os.path.getmtime(output))>3600:
                print(("Redo failed merging (locally) for "+output))
                os.remove(output)
                mergeonbatch = False
        if not os.path.exists(output):
            if len(allinput)==1:
                # Single files can simply be copied
                print(("File for "+all_mergeables[i][0]+" is ready"))
                special_call(["cp","-p", allinput[0], output], opt.run, 0)
            else:
                # Multiple files will be hadded
                print((str(len(allinput))+" files for "+output+" are ready to be merged"))
                #logged_call(["hadd", "-f", "-v", "-n", "200"]+all_mergeables[i], all_mergeables[i][0].rsplit("/",1)[0]+"/log/"+all_mergeables[i][0].rsplit("/",1)[1].replace(".root",".log"), opt.run)
                # hadd produces problems when merging too many files
                # so we merge files in chunks of maximum 100 files each
                # problems happen typically over a few hundred input files
                Nmerge = 100
                alltmp = []
                if len(allinput)<Nmerge:
                    # Simple hadding all output files
                    hadd_job(output, allinput, log, mergeonbatch)
                else:
                    # Two staged hadding:
                    # - First merge every Nmerge files to temp files
                    for n in range(1, (len(allinput)-1)/Nmerge+2):
                        tmpoutput = output.replace(".root","_"+str(n)+".root")
                        if os.path.isfile(tmpoutput):
                            if os.path.getsize(tmpoutput)>1024:
                                alltmp.append(tmpoutput)
                            elif os.path.getsize(tmpoutput)==1024 and (time.time()-os.path.getmtime(tmpoutput))>3600:
                                tmplist = []
                                for i in range((n-1)*Nmerge, min(n*Nmerge,len(allinput))): tmplist.append(allinput[i])
                                tmplog = tmpoutput.rsplit("/",1)[0]+"/log/"+tmpoutput.rsplit("/",1)[1].replace(".root",".log")
                                print(("- Merging into temp file (again, locally): "+tmpoutput))
                                hadd_job(tmpoutput, tmplist, tmplog, False)
                                if os.path.getsize(tmpoutput)>1024:
                                    alltmp.append(tmpoutput)
                        else:
                            tmplist = []
                            for i in range((n-1)*Nmerge, min(n*Nmerge,len(allinput))): tmplist.append(allinput[i])
                            tmplog    = tmpoutput.rsplit("/",1)[0]+"/log/"+tmpoutput.rsplit("/",1)[1].replace(".root",".log")
                            print(("- Merging into temp file: "+tmpoutput))
                            hadd_job(tmpoutput, tmplist, tmplog, mergeonbatch)
                    # - then merge the resulting temp files into a single file
                    #   and remove the temporary files
                    if len(alltmp) == (len(allinput)-1)/Nmerge+1:
                        print(("- Merging temp files into: "+output))
                        hadd_job(output, alltmp, log, mergeonbatch)
                        for tmpfile in alltmp:
                            #if os.path.isfile(tmpfile):
                            #    os.remove(tmpfile)
                            #else:
                            if not os.path.isfile(tmpfile):
                                print(("Something went wrong with the hadding of tmp file: "+tmpfile))
                                sys.exit()
                #  Check that the result has the right size (if not, delete)
                if os.path.isfile(output):
                    if os.path.getsize(output) < 1000: os.remove(output)
    # Do partial merging when a year and data type is ready
    all_ready = []
    saved_path = os.getcwd()
    os.chdir(EXEC_PATH)
    alldir = sorted(glob.glob("filelists/*/*"))
    os.chdir(saved_path)
    for listdir in alldir:
        haddoutfile = (EXEC_PATH+"/"+listdir).replace("BoostAnalyzer17/filelists","hadd").replace("2016/","2016_").replace("2017/","2017_").replace("2018/","2018_").replace("2016APV/","2016APV_")+".root"
        if os.path.exists(haddoutfile):
            if os.path.getsize(haddoutfile)>1024:
                all_ready.append(haddoutfile)
            elif os.path.getsize(haddoutfile)==1024 and (time.time()-os.path.getmtime(haddoutfile))>3600:
                ready = []
                for item in sorted(glob.glob(EXEC_PATH+"/"+listdir+"/*.txt")):
                    hadded = item.replace("BoostAnalyzer17/filelists/","hadd/").replace("/data/","_").replace("/signals/","_").replace("/backgrounds/","_").replace(".txt",".root")
                    if os.path.exists(hadded):
                        if os.path.getsize(hadded)>1024:
                            ready.append(hadded)
                # The batch job probably failed, so redo it locally
                hadd_job(haddoutfile, ready, haddoutfile.replace("hadd","hadd/log").replace(".root",".log"), False)
        else:
            #print(allitem
            ready = []
            allitem = sorted(glob.glob(EXEC_PATH+"/"+listdir+"/*.txt"))
            for item in allitem:
                hadded = item.replace("BoostAnalyzer17/filelists/","hadd/").replace("/data/","_").replace("/signals/","_").replace("/backgrounds/","_").replace(".txt",".root")
                if os.path.exists(hadded):
                    if os.path.getsize(hadded)>1024:
                        ready.append(hadded)
            if len(ready) == len(allitem):
                if not os.path.exists(haddoutfile):
                    print(("Larger set of jobs ready, merging output files into: "+haddoutfile))
                    hadd_job(haddoutfile, ready, haddoutfile.replace("hadd","hadd/log").replace(".root",".log"))
    # And finally merge all partial output files to a single final output file
    final_hadded_filename = opt.OUTDIR+".root"
    if len(all_ready)+1 == len(alldir):
        if os.path.exists(final_hadded_filename):
            if os.path.getsize(final_hadded_filename)<1024:
                os.remove(final_hadded_filename)
                print(("All jobs are ready, merging (again) all output files into: "+final_hadded_filename))
                hadd_job(final_hadded_filename, all_ready, opt.OUTDIR+"/hadd/log/final.log", False)
        else:
            print(("All jobs are ready, merging all output files into: "+final_hadded_filename))
            hadd_job(final_hadded_filename, all_ready, opt.OUTDIR+"/hadd/log/final.log", False)

def get_input_count(opt, ana_arguments, jobindex):
    input_count = 0
    if opt.useprev or opt.NEVT != -1 or opt.optim:
        job_options   = ana_arguments[jobindex][2]
        for job_option in job_options:
            if job_option.startswith("ifirst"):
                ifirst = int(float(job_option.replace("ifirst=","")))
            if job_option.startswith("ilast"):
                ilast = int(float(job_option.replace("ilast=","")))
        input_count = ilast - ifirst
    else:
        tmp_filelist  = ana_arguments[jobindex][1][0]
        with open(tmp_filelist) as f:
            files = f.read().splitlines()
            for filename in files:
                input_count += counts[filename]
    return input_count

# Run all Analyzer jobs in parallel
def analysis(ana_arguments, last_known_status, last_condor_jobid, nproc):
    global opt,  batch_number, cluster_ids
    njob = len(ana_arguments)
    if not opt.batch and njob<nproc: nproc = njob
    output_files = []
    saved_path = os.getcwd()
    if opt.haddonly:
        # local hadd only task
        for jobindex in range(0, njob):
            # Check if output file exists and size is larger than 1000 bytes
            output_file = ana_arguments[jobindex][0]
            file_size = 0
            if os.path.isfile(output_file):
                file_size = os.path.getsize(output_file)
                if file_size > 1000:
                    output_files.append(output_file)
                    last_known_status[jobindex] = 0
        merge_output(ana_arguments, last_known_status)
    elif opt.batch:
        njob = len(ana_arguments)
        nfinished = 0
        if not opt.recover:
            if opt.condor:
                # condor jobs
                print(("Preparing "+str(njob)+" jobs for HTCondor submission:"))
            else:
                # lxbatch jobs
                print(("Running "+str(njob)+" instances of LxBatch jobs:"))
            print()
        
        # Loop until batch task completion
        finished = False
        #while nfinished != njob:
        while not finished:
            cyclestarttime = time.time()
            # 1) Query the status of the already running batch jobs
            if opt.condor and len(cluster_ids)>0:
                latest_condor_query = {}
                latest_batch_status = TMPDIR+'batchstatus_'+cluster_ids[-1]+'.txt'
                logged_call(shlex.split(
                    'condor_q --nobatch '+(" ".join(cluster_ids))+
                    ' -format "%s " GlobalJobId'+
                    ' -format "%s " JobStatus'+
                    ' -format "%d " JobCurrentStartExecutingDate'+
                    ' -format "%d\n" CompletionDate'), latest_batch_status, opt.run)
                with open(latest_batch_status) as batchstatus:
                    for line in batchstatus.readlines():
                        parts = line.split()
                        jobid = parts[0].split('#')[1]
                        status = int(parts[1])
                        subtime = int(parts[0].split('#')[2])
                        starttime = int(parts[2])
                        latest_condor_query[jobid] = [status, subtime, starttime]
                special_call(["mv", latest_batch_status, opt.OUTDIR+"/log/latest_batchstatus.txt"], opt.run)
            # 2) Determine a list of missing jobs
            nfinished = 0
            ncondor = 0
            nresub = 0
            for jobindex in range(0, njob):
                # Perform the following checks for each job
                # 2.0) Already completed jobs
                # 2.1) Initital submission
                # 2.2) Check batch job status for non-completed jobs
                # 2.3) Check file size for existing output file
                # 2.4) It can be opened (not corrupt) and the processed counts matches the input
                
                output_file   = ana_arguments[jobindex][0]
                tmp_filelist  = ana_arguments[jobindex][1][0]
                job_options   = ana_arguments[jobindex][2]
                output_log    = ana_arguments[jobindex][3]
                condor_site   = ana_arguments[jobindex][4]
                output_stdout = output_log.replace(".log",".out") # streamed back from condor
                # 2.0) Already completed jobs
                if last_known_status[jobindex] == 0:
                    nfinished += 1
                else:
                    submit_job = 0
                    # 2.1) Initial submission
                    if last_known_status[jobindex] == -1 and not opt.recover:
                        submit_job = 1
                    else:
                        # 2.2) Check batch job status for non-completed jobs
                        if not os.path.isfile(output_file):
                            if last_known_status[jobindex] == -1:
                                # Recovered missing job (which is not currently submitted to batch)
                                submit_job = 1
                            else:
                                # Check the status of the running batch job
                                if opt.condor:
                                    jobid       = last_condor_jobid[jobindex]
                                    # Check if the job is found with the latest query
                                    if not jobid in list(latest_condor_query.keys()):
                                        submit_job = 2
                                        last_known_status[jobindex] = -1
                                    else:
                                        # retrieve info from latest query
                                        status      = latest_condor_query[jobid][0]
                                        subtime     = latest_condor_query[jobid][1]
                                        starttime   = latest_condor_query[jobid][2]
                                        if last_known_status[jobindex] < subtime:
                                            last_known_status[jobindex] = subtime
                                        # Check the status of the job
                                        # 1 Idle, 2 Running, 3 Removed, 4 Completed, 5 Held, 6 Transferring Output
                                        if status == 1:
                                            last_known_status[jobindex] = time.time()
                                        elif status == 2 and starttime != 0:
                                            if last_known_status[jobindex] < starttime:
                                                last_known_status[jobindex] = starttime
                                            # From now on we need to comfirm:
                                            # 1) The Analyzer started running and is not stuck at the First event
                                            # 2) The read speed is as good as expected
                                            year="2016"
                                            if "/2017/" in tmp_filelist:
                                                year = "2017"
                                            elif "/2018/" in tmp_filelist:
                                                year = "2018"
                                            elif "/2016APV/" in tmp_filelist:
                                                year = "2016APV"
                                            samplename = year+"_"+("_".join(tmp_filelist.split("/")[-1].split("_")[:-1]))
                                            optim      = get_optim_ratios(opt, samplename)
                                            target_time = 7200
                                            maxratio = 10.0 # Maximum allowed ratio of target nps to actual nps
                                            target_nps = opt.NEVT * optim / target_time
                                            max_possible_nps = get_input_count(opt, ana_arguments, jobindex) / (time.time()-starttime)
                                            runtime = int(time.time()) - starttime
                                            # TODO: Delete this when all stdout is successfully streamed
                                            if max_possible_nps*maxratio < target_nps and runtime > target_time:
                                                #print("Job must be running too slow"
                                                #print("- Jobid:            "+jobid
                                                #print("- submission:       "+str(subtime)
                                                #print("- job start:        "+str(starttime)
                                                #print("- current time:     "+str(int(time.time()))
                                                #print("- running time:     "+str(runtime)
                                                #print("- max possible nps: "+str(max_possible_nps)
                                                #print("- tartget_nps:      "+str(target_nps)
                                                #print
                                                submit_job = 5
                                            elif runtime > target_time/4.0:
                                                last_known_status[jobindex] = int(time.time())
                                                if os.path.exists(output_stdout):
                                                    # Checking the streamed stdout of the job
                                                    time_job_start    = 0
                                                    time_ana_start    = 0
                                                    time_first_event  = 0
                                                    time_latest_event = 0
                                                    report_nps        = 0
                                                    nevt = 0
                                                    nps = 0
                                                    badfile = ""
                                                    with open(output_stdout) as stdout:
                                                        for line in stdout.readlines():
                                                            if line.startswith("UnixTime-JobStart:"):
                                                                time_job_start = int(line.split()[1])
                                                            elif line.startswith("UnixTime-AnalyzerStart:"):
                                                                time_ana_start = int(line.split()[1])
                                                            elif line.startswith("UnixTime-FirstEvent:"):
                                                                if len(line.split()) == 2:
                                                                    time_first_event = int(line.split()[1])
                                                                elif time_ana_start != 0:
                                                                    # Use the analyzer start + average file access time
                                                                    time_first_event = time_ana_start + 53
                                                                elif time_job_start != 0:
                                                                    time_first_event = time_job_start + 74
                                                            elif line.startswith("UnixTime:"):
                                                                #time_latest_event = int(line.split()[1])
                                                                #nevt = float(line.split()[5])
                                                                #report_nps  = float(line.split()[9])
                                                                # The streamed output is sometimes messed up (endline missing)
                                                                # So we look from the end of the column and count back
                                                                time_latest_event = int(line.split()[-9])
                                                                nevt = float(line.split()[-5])
                                                                report_nps  = float(line.split()[-1])
                                                            if "failed to read the file type data" in line and "cms-xrd-global.cern.ch" in line:
                                                                badfile = line.split()[3]
                                                    if badfile != "":
                                                        print("Unaccessible file found:")
                                                        print(badfile)
                                                    if time_job_start == 0:
                                                        print(("UnixTime-JobStart not found in: "+output_stdout))
                                                        special_call(["rm", "-rf", output_stdout], opt.run)
                                                        #sys.exit()
                                                    else:
                                                        jobruntime =  int(time.time()) - time_job_start
                                                    if jobruntime <= target_time/4.0:
                                                        if time_first_event == 0:
                                                            print("First processed event does not appear after a long runtime")
                                                            print(("runtime: "+str(runtime)))
                                                            print(("jobruntime: "+str(jobruntime)))
                                                            print(("Check log: "+os.path.basename(output_stdout)))
                                                            special_call(["cp", "-p", output_stdout, "."], opt.run, 0)
                                                    else:
                                                        time_to_start = time_first_event - time_job_start
                                                        # This should not take longer than 30 minutes
                                                        if time_to_start > 1800 and nevt == 0:
                                                            print("Job below seems to take too long to start")
                                                            print(("- Jobid:            "+jobid))
                                                            print(("- submission:       "+str(subtime)))
                                                            print(("- job start:        "+str(starttime)))
                                                            print(("- first event:      "+str(time_first_event)))
                                                            print(("- time to start:    "+str(time_to_start)))
                                                            print()
                                                            submit_job = 6
                                                        # Check the speed of the running job and identify stuck or too slow ones
                                                        # The target average Nevt/s is known from previous runs
                                                        # The current read speed should not fall greatly below that
                                                        if time_latest_event > 0:
                                                            if report_nps > 0:
                                                                nps = report_nps
                                                            elif time_first_event > 0:
                                                                nps = nevt / (time.time() - time_first_event)
                                                            else:
                                                                nps = nevt / (time.time() - starttime)
                                                            if report_nps * maxratio < target_nps:
                                                                print("Job below progresses too slowly (high batch load, bad server?)")
                                                                print(("- Jobid:            "+jobid))
                                                                print(("- submission:       "+str(subtime)))
                                                                print(("- job start:        "+str(starttime)))
                                                                print(("- first event:      "+str(time_first_event)))
                                                                print(("- latest time:      "+str(time_latest_event)))
                                                                print(("- time to start:    "+str(time_to_start)))
                                                                print(("- reported nps:     "+str(report_nps)))
                                                                print(("- tartget_nps:      "+str(target_nps)))
                                                                print()
                                                                submit_job = 7
                                                            elif nps * maxratio < target_nps:
                                                                # Job may report an adequate read speed, but still be stuck later on
                                                                # and cause the average nps to fall below the expected threshold
                                                                print("Job below seems to be stuck")
                                                                print(("- Jobid:            "+jobid))
                                                                print(("- submission:       "+str(subtime)))
                                                                print(("- job start:        "+str(starttime)))
                                                                print(("- first event:      "+str(time_first_event)))
                                                                print(("- latest time:      "+str(time_latest_event)))
                                                                print(("- time to start:    "+str(time_to_start)))
                                                                print(("- average nps:      "+str(nps)))
                                                                print(("- tartget_nps:      "+str(target_nps)))
                                                                print()
                                                                submit_job = 8
                                                        elif time_first_event > 0:
                                                            # Most jobs should return a timestamp other than the first event within an hour
                                                            # except if the job is stuck (some remote file open/read issue)
                                                            time_to_start = time_first_event - starttime
                                                            time_stuck    = int(time.time()) - time_first_event
                                                            print("Job below seems to be stuck at the first event")
                                                            print(("- Jobid:            "+jobid))
                                                            print(("- submission:       "+str(subtime)))
                                                            print(("- job start:        "+str(starttime)))
                                                            print(("- first event:      "+str(time_first_event)))
                                                            print(("- current time:     "+str(int(time.time()))))
                                                            print(("- time to start:    "+str(time_to_start)))
                                                            print(("- time stuck:       "+str(time_stuck)))
                                                            print()
                                                            submit_job = 9
                                                        else:
                                                            print("Job below seems to be missing any timestamps, please check it")
                                                            print(("- Jobid:            "+jobid))
                                                            print(("- stdout:           "+output_stdout))
                                                            print()
                                                    if submit_job > 0:
                                                        saved_stdout = output_stdout.replace(".out","_resub"+str(submit_job)+"_"+jobid+".out")
                                                        special_call(["mv", output_stdout, saved_stdout], opt.run)
                                else:
                                    # Use bjobs for LxBatch jobs
                                    # If the last submission/check is older than 10 minutes check job status with bjobs
                                    if int(time.time()) - last_known_status[jobindex] > (600 if opt.NQUICK<2 else 600/opt.NQUICK):
                                        jobname = SUBTIME+'_'+str(jobindex)
                                        logged_call(shlex.split('bjobs -J '+jobname), TMPDIR+'jobstatus_'+jobname+'.txt', opt.run)
                                        with open(TMPDIR+'jobstatus_'+jobname+'.txt') as jobstatus:
                                            lines = jobstatus.readlines()
                                            # Check if job is missing and resubmit
                                            if 'Job <'+jobname+'> is not found' in lines[0]:
                                                submit_job = 2
                                            #else:
                                            #    status = lines[1].split()[2]
                                            #    if status == 'PEND' or status == 'RUN':
                                            #        print("Job "+jobname+" is pending/running"
                                        os.remove(TMPDIR+'jobstatus_'+jobname+'.txt')
                                        last_known_status[jobindex] = int(time.time())
                        else:
                            # 2.3) Check file size for existing output file
                            file_size = os.path.getsize(output_file)
                            if file_size <= 1000:
                                submit_job = 3
                            elif not opt.nocheck:
                                # 2.4) It can be opened (not corrupt) and the processed counts matches the input
                                input_count = get_input_count(opt, ana_arguments, jobindex)
                                output_count = 0
                                with suppress_stdout_stderr():
                                    fout = ROOT.TFile.Open(output_file)
                                    if fout and not fout.TestBit(ROOT.TFile.kRecovered):
                                        h_counts = fout.Get("counts")
                                        if h_counts: output_count += h_counts.GetBinContent(1)
                                    if fout: fout.Close()
                                if (input_count != output_count): submit_job = 4
                    
                    if submit_job == 0:
                        if os.path.isfile(output_file):
                            # Passed all checks and output file is ready
                            nfinished += 1
                            output_files.append(output_file)
                            last_known_status[jobindex] = 0
                            #print(output_file+" - OK!"
                    else:
                        # Job needs to be submitted to batch
                        if submit_job > 1:
                            # Indicate that the job needs to be resubmitted
                            if submit_job == 2:
                                print(("Job["+str(jobindex)+"] output "+output_file+" is missing, resubmitting ..."))
                            elif submit_job == 3:
                                print(("Job["+str(jobindex)+"] output "+output_file+" failed file checks: file_size = "+str(file_size)+", resubmitting ..."))
                            elif submit_job == 4:
                                print(("Job["+str(jobindex)+"] output "+output_file+" failed file checks: input_count = "+str(input_count)+" output_count = "+str(output_count)+" resubmitting ..."))
                            elif submit_job == 5:
                                print(("Job["+str(jobindex)+"] output "+output_file+" failed speed check: Job still running after twice the expected run time, resubmitting ..."))
                            elif submit_job == 6:
                                print(("Job["+str(jobindex)+"] output "+output_file+" It took more than 30 minutes (time_to_start = "+str(time_to_start)+") to reach first event , resubmitting ..."))
                            elif submit_job == 7:
                                print(("Job["+str(jobindex)+"] output "+output_file+" is too slow (report_nps = "+str(report_nps)+", target_nps = "+str(target_nps)+"), resubmitting ..."))
                            elif submit_job == 8:
                                print(("Job["+str(jobindex)+"] output "+output_file+" seems stuck after first event (nevt = "+str(nevt)+", nps= "+str(nps)+", target_nps = "+str(target_nps)+"), resubmitting ..."))
                            elif submit_job == 9:
                                print(("Job["+str(jobindex)+"] output "+output_file+" is stuck at first event (time_stuck = "+str(time_stuck)+"), resubmitting ..."))
                            if os.path.isfile(output_file): os.remove(output_file)
                        if submit_job>1:
                            nresub += 1
                        analyzer_job(jobindex)
                        if opt.condor:
                            ncondor += 1
                            if condor_site == "EU":
                                last_known_status[jobindex] = 1 # rewrite when actual condor task submission
                            elif condor_site == "US":
                                last_known_status[jobindex] = 2 # rewrite when actual condor task submission
                        else:
                            last_known_status[jobindex] = int(time.time())
            
            # 3) condor job submission step (done in a single batch)
            if ncondor > 0:
                if nresub>njob/10 and njob>10:
                    print()
                    print()
                    print(("Too large fraction of jobs need to be resubmitted, nresub="+str(nresub)+", 10% threshold="+str(njob/10)))
                    print("Please check why so many job failed!")
                    print("if needed do an --update, and then --recover")
                    print("Aborting ...")
                    sys.exit()
                else:
                    print((str(ncondor)+" jobs are being submitted to HTCondor ..."))
                    for joblist in glob.glob(opt.OUTDIR+"/log/condor_joblist_??.txt"):
                        batch_number += 1
                        site = joblist.split("_")[-1].replace(".txt","")
                        joblist_to_submit = joblist.replace("condor_joblist","condor_joblist_"+str(batch_number))
                        special_call(["mv", joblist, joblist_to_submit], opt.run)
                        njobcondor = sum(1 for line in open(joblist_to_submit))
                        print(("Submitting jobs to "+site+" sites ..."))
                        # Send task to condor and get the ClusterId
                        clusterid = ""
                        latest_log_file = opt.OUTDIR+"/log/condor_task_"+str(batch_number)+".log"
                        submittime = int(time.time())
                        print(joblist_to_submit)
                        #logged_call(["condor/submit_condor_task.sh", site, opt.OUTDIR+"/sandbox-BoostAnalyzer17.tar", joblist_to_submit], latest_log_file, opt.run)
                        logged_call(["condor/submit_condor_task.sh", site, "sandbox-BoostAnalyzer17.tar", joblist_to_submit], latest_log_file, opt.run)
                        with open(latest_log_file) as latest_log:
                            for line in latest_log.readlines():
                                if "submitted to cluster" in line:
                                    clusterid = line.split()[-1].replace(".","")
                                    cluster_ids.append(clusterid)
                        if clusterid == "":
                            print("ERROR: Latest HTCondor submission failed, please check the log file:")
                            print((opt.OUTDIR+"/log/condor_task_"+str(batch_number)+".log"))
                            sys.exit()
                        # Actualize job submission time and jobids
                        newjobindex = 0
                        for ijob in range(0, njob):
                            if (last_known_status[ijob] == 1 and site == "EU") or (last_known_status[ijob] == 2 and site == "US"):
                                last_known_status[ijob] = submittime
                                last_condor_jobid[ijob] = clusterid+"."+str(newjobindex)
                                newjobindex += 1
                        print(("Successfully submitted "+str(njobcondor)+" job(s)"))
                        print(("Latest ClusterId: "+clusterid))
            
            # 4) Merge output files if all jobs in a sample are ready
            if not opt.nohadd:
                merge_output(ana_arguments, last_known_status)
            
            # 5) Print batch status
            print(("Analyzer jobs on batch (Done/All): "+str(nfinished)+"/"+str(njob)+"   \r",))
            sys.stdout.flush()
            
            # 6) Check if final output file is ready
            final_hadded_filename = opt.OUTDIR+".root"
            if os.path.exists(final_hadded_filename):
                if os.path.getsize(final_hadded_filename)>1024:
                    finished = True
            
            # 7) Sleep 10 minutes between condor job check iterations
            if not finished and opt.condor:
                cycletime = time.time()-cyclestarttime
                if cycletime<300:
                    time.sleep(int(300-cycletime))
        
    else:
        # Local analysis jobs
        print(("Running "+str(njob)+" instances of Analyzer jobs:"))
        print()
        # Use the N CPUs in parallel on the current computer to analyze all jobs
        workers = multiprocessing.Pool(processes=nproc)
        output_files = workers.map(analyzer_job, list(range(njob)), chunksize=1)
        workers.close()
        workers.join()
        last_known_status = [0] * njob
        print("All Analyzer jobs finished.")
        if not opt.nohadd:
            merge_output(ana_arguments, last_known_status)
    
    print()
    return output_files

# Run Plotter, output of Analyzer is input for this code
def plotter(input_files, output_file):
    global opt, EXEC_PATH
    print("Start plotting from output files")
    print()
    special_call([EXEC_PATH+"/Plotter", output_file] + input_files, opt.run)
    print("Plotting finished.")
    print()

def show_result(plotter_out):
    print("Showing the result in root: ")
    print()
    special_call(["root", "-l", 'scripts/show_result.C("'+plotter_out+'")'], opt.run)

# ---------------------- Running -------------------------

# renew token before running
if opt.replot:
    if not opt.recover:
        backup_files(EXEC_PATH, SUBTIME)
        compile(0)
    plotter(PLOTTER_IN, PLOTTER_OUT)
    #if not 'lxplus' in socket.gethostname():
    #    show_result(PLOTTER_OUT)
else:
    if not opt.recover or opt.update:
        if not opt.test:
            backup_files(EXEC_PATH, SUBTIME, opt.update)
        compile(1, opt.plot)
        if opt.condor: create_sandbox(EXEC_PATH, opt.update)
    plotter_input_files = analysis(ana_arguments, last_known_status, last_condor_jobid, opt.NPROC)
    if opt.plot:
        if not opt.nohadd: plotter_input_files = [opt.OUTDIR+".root"]
        plotter(plotter_input_files, PLOTTER_OUT)
        #if not 'lxplus' in socket.gethostname():
        #    show_result(PLOTTER_OUT)

print("Done.")
