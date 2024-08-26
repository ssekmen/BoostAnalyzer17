import os, re, sys, glob, time, logging, multiprocessing, socket, subprocess, shlex, ROOT
import numpy as np
from optparse import OptionParser

# ---------------------- Cmd Line  -----------------------

# Read options from command line
usage = "Usage: python %prog [options]"
parser = OptionParser(usage=usage)
parser.add_option("-d","--prevdir",   dest="PREVDIR", type="string",       default="",    help="Previous running directory")
parser.add_option("-t","--jobtime",   dest="JOBTIME", type="int",          default=1200,  help="Desired job running time (default=1200s)")
parser.add_option("-n","--nevt",      dest="NEVT",    type="int",          default=-1,    help="Tells how many event to run as a maximum in a single job (Default=-1 all)")
parser.add_option("--prev",           dest="PREV",    action="store_true", default=False, help="Calculate difference to previos ratio")
parser.add_option("--useprev",        dest="USEPREV", action="store_true", default=False, help="Use previous ratio if more pessimistic")
parser.add_option("--update",         dest="UPDATE",  action="store_true", default=False, help="Use previous ratio if more pessimistic")
(opt,args) = parser.parse_args()

# Get list of samples
samplenames = []
for filename in glob.glob(opt.PREVDIR+"/log/*.out"):
    samplename = filename.split("/")[-1].rsplit("_",1)[0]
    if samplename not in samplenames and not "_resub" in samplename:
        samplenames.append(samplename)

# Loop on log files for each sample
all_prev = {}
for samplename in samplenames:
    # Get previous ratios
    prev = 0.2
    if os.path.exists(("syst" if "syst" in opt.PREVDIR  else "")+"job_ratios.txt"):
        with open(("syst" if "syst" in opt.PREVDIR  else "")+"job_ratios.txt") as ratios:
            for line in ratios:
                if samplename == line.split()[1]:
                    prev = float(line.split()[0])
    all_prev[samplename] = prev

if opt.UPDATE:
    if os.path.exists(("syst" if "syst" in opt.PREVDIR  else "")+"job_ratios.txt"):
        new_ratios = open(("syst" if "syst" in opt.PREVDIR  else "")+"job_ratios.txt","w")

for samplename in samplenames:
    prev = all_prev[samplename]
    min_nps  = float(1e6)
    tot_nevt = float(0)
    tot_time = float(0)
    max_time = float(0)
    all_nps  = []
    one_found = False
    for log_file in sorted(glob.glob(opt.PREVDIR+"/log/"+samplename+"*.out")):
        if not "_resub" in log_file:
            with open (log_file) as log:
                found = False
                for line in log:
                    if re.search("JobMonitoringReport", line):
                        found = True
                        one_found = True
                        column  = line.split()
                        runtime = column[-5]
                        nevt    = column[-3]
                        nps     = column[-1]
                        #print samplename+" "+nevt+"/"+runtime+" = "+nps
                        if (float(nps)<min_nps): min_nps = float(nps)
                        if (float(runtime)>max_time): max_time = float(runtime)
                        tot_nevt += float(nevt)
                        tot_time += float(runtime)
                        all_nps.append(float(nps))
                if not found:
                    print "No JobMonitoringReport found in file: "+log_file
    if one_found:
        # Use the lowest job speed to set speed
        max_nevt = opt.JOBTIME * min_nps
        ratio = max_nevt / opt.NEVT
        # Use the median job speed to set ratio
        # This is better in excluding the slow jobs
        np_all_nps = np.array(all_nps)
        mean   = np.mean(np_all_nps)
        median = np.median(np_all_nps)
        stdev  = np.std(np_all_nps)
        ratio = median * opt.JOBTIME  / opt.NEVT
        #print ("%-85s   MIN=%7.1f  AVG=%7.1f   MEAN+-STDEV=%7.1f+-%7.1f    MEDIAN=%7.1f   MAX_NEVT=%10d   RATIO=%5.2f" % (samplename, min_nps, (tot_nevt/tot_time), mean, stdev, median, max_nevt, ratio))
        if opt.PREV:
            # Deal with extremely differing cases (happens usually with 1 job samples)
            # Take the average of the two
            if ratio/prev < 0.5 or ratio/prev > 2.0:
                ratio = (ratio + prev) / 2.0
            use = ratio
            #if prev < ratio and not prev==-1: use = prev
            print ("corr/new/old/use: %3.2f %3.2f %3.2f %3.2f %s" % (use/prev, ratio, prev, use, samplename))
            if opt.UPDATE: print>>new_ratios, ("%3.2f %s" % (ratio, samplename))
        elif opt.USEPREV:
            # Deal with extremely differing cases (happens usually with 1 job samples)
            # Take the average of the two
            if ratio/prev < 0.5 or ratio/prev > 2.0:
                ratio = (ratio + prev) / 2.0
            #if prev < ratio and not prev==-1: ratio = prev
            print ("%3.2f %s" % (ratio, samplename))
            if opt.UPDATE: print>>new_ratios, ("%3.2f %s" % (ratio, samplename))
        else:
            print ("%3.2f %s" % (ratio, samplename))
            if opt.UPDATE: print>>new_ratios, ("%3.2f %s" % (ratio, samplename))
        #print ("%-50s %10d" % (samplename, max_time))
        #print "SAMPLE="+samplename+" MIN="+str(min_nps)+" AVG="+str(tot_nevt/tot_time)+" MAX_NEVT="+str(max_nevt)+" RATIO="+str(ratio)
    
