import os, re, sys, glob, socket, subprocess, ROOT

opt = "skim"
#opt = "unskim"
if len(sys.argv)>1: opt = sys.argv[1]

#ANA_BASE = os.environ['CMSSW_BASE']+'/src/BoostAnalyzer17'
current_directory = os.getcwd()
ANA_BASE = current_directory
if 'grid18.kfki.hu' in socket.gethostname(): ANA_BASE='/data/jkarancs/CMSSW/BoostAnalyzer17'
if opt == "unskim":
    print("Unskimmed ntuples selected")
    vf = ["condor/filelist_unskim_2016.txt", "condor/filelist_unskim_2016APV.txt", "condor/filelist_unskim_2017.txt", "condor/filelist_unskim_2018.txt"]
else:
    print("Skimmed ntuples selected")
    vf = ["condor/filelist_2016.txt", "condor/filelist_2016APV.txt", "condor/filelist_2017.txt", "condor/filelist_2018.txt"]

# private methods
def grep(cmd, togrep):
    results = []
    for i in range(len(togrep)):
        results.append([])
    tmpfile = "/tmp/tmpcmd.txt"
    if os.path.exists(tmpfile): os.remove(tmpfile)
    with open(tmpfile, "w") as chk:
        proc = subprocess.Popen(cmd, stdout=chk, stderr=chk, close_fds=True)
        proc.wait()
    proxyerror = False
    with open(tmpfile, "r") as chk:
        for line in chk:
            for i in range(len(togrep)):
                if togrep[i] in line:
                    results[i].append(line.replace('\n',''))
    os.remove(tmpfile)
    return results

# Fix issues with cases where the file cannot be read
def open_file(filename):
    fin = 0
    if "root://cms-xrd-global.cern.ch/" in filename:
        fin = ROOT.TFile.Open(filename)
        if not fin:
            lfn = filename.replace("root://cms-xrd-global.cern.ch/","")
            servers = grep(["xrdfs", "cms-xrd-global.cern.ch", "locate", "-d", "-m", lfn], ["Server Read"])
            for i in range(len(servers[0])):
                server = servers[0][i].split()[0]
                newfilename = filename.replace("cms-xrd-global.cern.ch", server)
                fin = ROOT.TFile.Open(newfilename)
                if fin:
                    break
    else:
        fin = ROOT.TFile.Open(filename)
    return fin

print("Creating file lists ... ")
if not os.path.exists(ANA_BASE+'/filelists/2016/data'):        os.makedirs(ANA_BASE+'/filelists/2016/data')
if not os.path.exists(ANA_BASE+'/filelists/2016/signals'):     os.makedirs(ANA_BASE+'/filelists/2016/signals')
if not os.path.exists(ANA_BASE+'/filelists/2016/backgrounds'): os.makedirs(ANA_BASE+'/filelists/2016/backgrounds')
if not os.path.exists(ANA_BASE+'/filelists/2016APV/data'):        os.makedirs(ANA_BASE+'/filelists/2016APV/data')
if not os.path.exists(ANA_BASE+'/filelists/2016APV/signals'):     os.makedirs(ANA_BASE+'/filelists/2016APV/signals')
if not os.path.exists(ANA_BASE+'/filelists/2016APV/backgrounds'): os.makedirs(ANA_BASE+'/filelists/2016APV/backgrounds')
if not os.path.exists(ANA_BASE+'/filelists/2017/data'):        os.makedirs(ANA_BASE+'/filelists/2017/data')
if not os.path.exists(ANA_BASE+'/filelists/2017/signals'):     os.makedirs(ANA_BASE+'/filelists/2017/signals')
if not os.path.exists(ANA_BASE+'/filelists/2017/backgrounds'): os.makedirs(ANA_BASE+'/filelists/2017/backgrounds')
if not os.path.exists(ANA_BASE+'/filelists/2018/data'):        os.makedirs(ANA_BASE+'/filelists/2018/data')
if not os.path.exists(ANA_BASE+'/filelists/2018/signals'):     os.makedirs(ANA_BASE+'/filelists/2018/signals')
if not os.path.exists(ANA_BASE+'/filelists/2018/backgrounds'): os.makedirs(ANA_BASE+'/filelists/2018/backgrounds')
for txtfile in glob.glob(ANA_BASE+'/filelists/*/*/*.txt'):
    os.remove(txtfile)

for flist in vf:
    # Decide year
    year = '2016'
    if '2017' in flist:
        year = '2017'
    elif '2018' in flist:
        year = '2018'
    elif 'APV' in flist:
        year = '2016APV'
    with open(flist) as filelist:
        for line in filelist:
            filename = line.split()[0]
            sample = ""
            # don't forget also tnm.cc
            for i in range(2,len(filename.split("/"))+1):
                subdir = filename.split("/")[-i]
                if len(subdir):
                    # make sure the exclusion is the same in tnm.cc
                    if (sample == "" and not subdir[0].isdigit() and not subdir.startswith("PU") and not
                        subdir.startswith("NANOAOD") and not subdir.startswith("Nano")):
                        if "unskim" in flist and "/data/" in filename:
                            sample = subdir+"_"+filename.split("/")[-(i+1)]
                        else:
                            sample = subdir
            # Data
            if re.compile('.*20[1-2][0-9][A-J].*').match(sample):
                fl = open(ANA_BASE+'/filelists/'+year+'/data/'+sample+'.txt', 'a')
                print(filename, file=fl)
            # Signals
            elif re.compile('.*T[1-9][t,b,c,q,W,Z,H][t,b,c,q,W,Z,H].*').match(sample) or "TChi" in sample or "SMS-" in sample:
                fl = open(ANA_BASE+'/filelists/'+year+'/signals/'+sample+'.txt', 'a')
                print(filename, file=fl)
            # Backgrounds
            else:
                fl = open(ANA_BASE+'/filelists/'+year+'/backgrounds/'+sample+'.txt', 'a')
                print(filename, file=fl)
print('Done.')

print("Updating input event number txt file ... ")
bad_files = open("bad_files_found.txt", "w")
#if os.path.exists("condor/filelist_and_counts.txt"):
#    os.remove("condor/filelist_and_counts.txt")

# make a list of files already there
counted_already = []
if os.path.exists("condor/filelist_and_counts.txt"):
    with open("condor/filelist_and_counts.txt", 'r') as countsfile:
        for line in countsfile:
            counted_already.append(line.split()[0])

sites = {}
with open("condor/filelist_and_counts.txt", 'a') as countsfile:
    for flist in vf:
        with open(flist) as filelist:
            for line in filelist:
                filename = line.split()[0]
                if filename not in counted_already:
                    fin = open_file(filename)
                    if not fin:
                        print(filename+" could not open")
                        print(filename+" bad file", file=bad_files)
                    else:
                        tree = fin.Get("Events")
                        if tree:
                            if tree.GetEntries()>0:
                                # Check if the dataset is hosted in US sites
                                site =  "EU"
                                if "fnal.gov" in filename:
                                    condor_site = "US"
                                elif "wisc.edu" in filename:
                                    condor_site = "US"
                                elif "ufl.edu" in filename:
                                    condor_site = "US"
                                elif "cms-xrd-global.cern.ch" in filename:
                                    # NANOAOD, so need to check in DAS
                                    lfn = filename.replace("root://cms-xrd-global.cern.ch/","")
                                    dataset = "/".join(lfn.split("/")[:-2])
                                    if dataset in sites:
                                        site = sites[dataset]
                                    else:
                                        dascheck = grep(["dasgoclient", "--query", "site file="+lfn], ["X509_USER", "T2_US"])
                                        if len(dascheck[0]):
                                            print()
                                            print("ERROR! - proxy not found, please restart script after issuing this command:")
                                            print("voms-proxy-init -voms cms -rfc")
                                            sys.exit()
                                        if len(dascheck[1]):
                                            site = "US"
                                        sites[dataset] = site
                                print(filename+" "+str(tree.GetEntries())+" "+site, file=countsfile)
                                #print filename+" "+str(tree.GetEntries())+" "+site
                            else:
                                print(filename+" has 0 entries")
                                print(filename+" 0 entry", file=bad_files)
                        else:
                                print(filename+" has no tree")
                                print(filename+" no tree", file=bad_files)

print("Creating temp file list directories (for batch and split jobs) ... ")
if not os.path.exists(ANA_BASE+'/filelists_tmp/2016/data'):        os.makedirs(ANA_BASE+'/filelists_tmp/2016/data')
if not os.path.exists(ANA_BASE+'/filelists_tmp/2016/signals'):     os.makedirs(ANA_BASE+'/filelists_tmp/2016/signals')
if not os.path.exists(ANA_BASE+'/filelists_tmp/2016/backgrounds'): os.makedirs(ANA_BASE+'/filelists_tmp/2016/backgrounds')
if not os.path.exists(ANA_BASE+'/filelists_tmp/2016APV/data'):        os.makedirs(ANA_BASE+'/filelists_tmp/2016APV/data')
if not os.path.exists(ANA_BASE+'/filelists_tmp/2016APV/signals'):     os.makedirs(ANA_BASE+'/filelists_tmp/2016APV/signals')
if not os.path.exists(ANA_BASE+'/filelists_tmp/2016APV/backgrounds'): os.makedirs(ANA_BASE+'/filelists_tmp/2016APV/backgrounds')
if not os.path.exists(ANA_BASE+'/filelists_tmp/2017/data'):        os.makedirs(ANA_BASE+'/filelists_tmp/2017/data')
if not os.path.exists(ANA_BASE+'/filelists_tmp/2017/signals'):     os.makedirs(ANA_BASE+'/filelists_tmp/2017/signals')
if not os.path.exists(ANA_BASE+'/filelists_tmp/2017/backgrounds'): os.makedirs(ANA_BASE+'/filelists_tmp/2017/backgrounds')
if not os.path.exists(ANA_BASE+'/filelists_tmp/2018/data'):        os.makedirs(ANA_BASE+'/filelists_tmp/2018/data')
if not os.path.exists(ANA_BASE+'/filelists_tmp/2018/signals'):     os.makedirs(ANA_BASE+'/filelists_tmp/2018/signals')
if not os.path.exists(ANA_BASE+'/filelists_tmp/2018/backgrounds'): os.makedirs(ANA_BASE+'/filelists_tmp/2018/backgrounds')

print('Done.')
