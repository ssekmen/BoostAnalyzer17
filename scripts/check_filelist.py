#!/usr/bin/python
# usage: python scripts/check_filelist.py [filelist]

import os, sys, subprocess, random, shutil, operator, ROOT
from timeit import default_timer as timer

filelist = sys.argv[1]

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

def ping(server):
    avg_ping = 2000.0
    lines = grep(["ping", "-c", "1", "-w", "2", server],["rtt min/avg/max/mdev"])[0]
    if len(lines)==1:
        avg_ping = float(lines[0].split()[3].split("/")[1])
    return avg_ping

# Make a list of all input files
files = []
with open(filelist) as fl_in:
    for line in fl_in:
        files.append(line.split()[0])

# Check that each can be successfully read and matches the number of events in filelist_and_counts.txt
tmp_filelist = filelist.replace(".txt","_tmp.txt")
if os.path.exists(tmp_filelist): os.remove(tmp_filelist)
nretry = 0
fail = False
nfileok = 0
nfile = 0
with open(tmp_filelist, "w") as fl_out:
    for chkfile in files:
        nfile += 1
        print "Start checking: "+chkfile
        exp_count =  0
        with open("condor/filelist_and_counts.txt") as countsfile:
            for line in countsfile:
                if chkfile in line:
                    exp_count = int(line.split()[1])
        print "- Expected counts: "+str(exp_count)
        filename = ""
        all_ok = False
        while not all_ok and nretry<3:
            if filename == "":
                filename = chkfile
            else:
                nretry += 1
                print "File failed previous file checks:"
                print filename
                if "root://cms-xrd-global.cern.ch/" in chkfile:
                    print "Checking the read speed of files on alternative servers"
                    print "--------------------------------------------"
                    lfn = chkfile.replace("root://cms-xrd-global.cern.ch/","")
                    servers = grep(["xrdfs", "cms-xrd-global.cern.ch", "locate", "-d", "-m", lfn], ["Server Read"])[0]
                    besttime = 9999
                    bestfile = ""
                    nok = 0
                    # First ping servers to see which are the closest ones and check them in that order
                    pings = {}
                    for i in range(len(servers)):
                        pings[i] = ping(servers[i].split()[0].split(":")[0])
                    sorted_pings = sorted(pings.items(), key=operator.itemgetter(1))
                    for i in range(len(servers)):
                        j = sorted_pings[i][0]
                        avg_ping = sorted_pings[i][1]
                        server = servers[j].split()[0]
                        newfilename = chkfile.replace("cms-xrd-global.cern.ch", server)
                        print "ALTERNATIVE: "+newfilename
                        starttime = timer()
                        fin = ROOT.TFile.Open(newfilename)
                        ok = False
                        if fin:
                            tree = fin.Get("Events")
                            if tree:
                                entries = tree.GetEntries()
                                if entries==exp_count:
                                    ok = True
                                    nok += 1
                            fin.Close()
                        readtime = timer()-starttime
                        print "             --> "+("OK" if ok else "Not OK")+" READTIME: "+str(readtime)+" s, PING: "+str(avg_ping)+" ms, R/P: "+str(readtime/avg_ping*1000)
                        if ok and readtime<besttime:
                            besttime = readtime
                            bestfile = newfilename
                        if besttime<1.0 and nok>=4: break
                    print "--------------------------------------------"
                    print "Best file found ("+str(besttime)+"): "+bestfile
                    print
                    if bestfile != "":
                        filename = bestfile
                else:
                    print "--> This file needs copying"
                    localfilename = chkfile.split("//")[-1]
                    if not os.path.exists(os.path.dirname(localfilename)):
                        os.makedirs(os.path.dirname(localfilename))
                    subprocess.call(["xrdcp", chkfile, localfilename])
                    if os.path.exists(localfilename):
                       filename = localfilename
                       print "--> Copying successful: "+localfilename
                    else:
                       print "Error: file copy failed"
                       print "Retry in 5 minutes"
                       time.sleep(300)
            print "Testing file: "+filename
            starttime = timer()
            fin = ROOT.TFile.Open(filename)
            if not fin:
                print "  --> Could not open"
            else:
                print "  --> Opening successful"
                tree = fin.Get("Events")
                if not tree:
                    print "  --> Could not read tree"
                else:
                    print "  --> Reading tree successful"
                    entries = tree.GetEntries()
                    if entries!=exp_count:
                        print "  --> Tree has wrong number of entries: "+str(entries)
                    else:
                        print "  --> Tree has the right number of entries: "+str(entries)
                        all_ok = True
                        #if filename != chkfile: all_ok = True
                fin.Close()
            readtime = timer()-starttime
            print "  --> Time of reed test: "+str(readtime)
            if all_ok:
                if filename == chkfile:
                    nfileok += 1
                print "  --> Save: "+filename
                print>>fl_out, filename
            else:
                if nretry==3:
                    print>>fl_out, chkfile
                    fail = True
                    print "  --> Retry limit (3) reached, end testing"
                else:
                    print "  --> Discard and retry"
            print

if fail:
    print "ERROR: Failed to fix file read errors"
    os.remove(tmp_filelist)
elif nfile==nfileok:
    print "SUCCESS: All files accessible, no change in filelist"
    os.remove(tmp_filelist)
else:
    print "SUCCESS: "+str(nfile-nfileok)+" file(s) were replaced by mirrors"
    shutil.move(tmp_filelist, filelist)


