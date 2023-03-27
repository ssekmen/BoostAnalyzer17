import re, os, sys, glob, time, logging, multiprocessing, socket, subprocess, shlex, getpass, ROOT
from optparse import OptionParser
import numpy as np

# ---------------------- Cmd Line  -----------------------

# Read options from command line
usage = "Usage: python %prog filelists [options]"
parser = OptionParser(usage=usage)
parser.add_option("--run",         dest="run",         action="store_true", default=False,   help="Without this option, script only prints cmds it would otherwise excecute")
parser.add_option('-d','--dir',    dest="dir",         type="string",       default="",         help="Input/output directory (use output of Analyzer)")
parser.add_option("--bin",         dest="BIN",          type="string",       default="",      help="Analysis bin, eg. _nj35 (default="")")
parser.add_option('--nocards',     dest="nocards",     action="store_true", default=False,      help='Do not create data cards, i.e. run on existing ones (default=create them)')
parser.add_option('--test',        dest="TEST",        type="int",          default=0,          help="Run only on a N signal points (default=0 - all)")
parser.add_option('-b','--box',    dest="box",         type="string",       default="AnaBoost", help='Analysis box, RazorBoost")')
parser.add_option('-m','--model',  dest="model",       type="string",       default="T5ttcc",   help='Signal model (default="T5ttcc")')
(opt,args) = parser.parse_args()


# run script to get above numbers: python scripts/calc_systematics.py
qcd_syst = 0.24
dy_syst  = 0.29
if "TopAna" in opt.box:
    qcd_syst = 0.13
    dy_syst  = 0.19


# List of systematics to consider -> for now same as 2016  
systematics = [
    "",
    "_topptUp",
    "_topptDown",
    "_isrUp",
    "_isrDown",
    "_pileupUp",
    "_pileupDown",
    "_L1PreFiringUp",
    "_L1PreFiringDown",
    "_alphasUp",
    "_alphasDown",
    "_scaleUp",
    "_scaleDown",
    #"_lostlepUp",
    #"_lostlepDown",
    "_triggerUp",
    "_triggerDown",
    "_jesUp",
    "_jesDown",
    "_jerUp",
    "_jerDown",
    "_metUp",
    "_metDown",
    "_RescaleAK8Up",
    "_RescaleAK8Down",
    "_BoostTagUp",
    "_BoostTagDown",
    "_BoostTag_FastsimUp",
    "_BoostTag_FastsimDown",
    "_BoostmisTagUp",
    "_BoostmisTagDown",
    "_BoostmisTag_FastsimUp",
    "_BoostmisTag_FastsimDown",
    "_EleRecoUp",
    "_EleRecoDown",
    "_EleIDUp",
    "_EleIDDown",
    "_EleIsoUp",
    "_EleIsoDown",
    "_EleFastsimUp",
    "_EleFastsimDown",
    "_PhoIDUp",
    "_PhoIDDown",
    "_MuonTrackUp",
    "_MuonTrackDown",
    "_MuonFullsimUp",
    "_MuonFullsimDown",
    "_MuonFastsimUp",
    "_MuonFastsimDown",
    "_BTagUp",
    "_BTagDown",
    "_BTagFastsimUp",
    "_BTagFastsimDown",
    "_cf_QTWUp",
    "_cf_QTWDown",
    "_cf_NonIso_Up",
    "_cf_NonIso_Down",
    "_cf_ZUp",
    "_cf_ZDown",
]


# --------------------- Functions ------------------------
# Show and run command with stdout on screen
icommand=0
def special_call(cmd, verbose=1):
    global icommand, opt
    if verbose:
        if opt.run:
            print("[%d]" % icommand),
        else:
            print("[dry]"),
        for i in xrange(len(cmd)): print (cmd[i]),
        print ("")
    if opt.run:
        ntry = 0
        while True:
            try:
                if subprocess.call(cmd):
                    print ("ERROR: Problem executing command:")
                    print("[%d]" % icommand)
                    for i in xrange(len(cmd)): print (cmd[i]),
                    print ("")
                    print ("exiting.")
                    sys.exit()
            except:
                print ("Could not execute command: ")
                print("[%d]" % icommand)
                for i in xrange(len(cmd)): print (cmd[i]),
                print ("")
                print ("Wait 10s and continue")
                time.sleep(10)
                ntry += 1
                if ntry == 20: sys.exit()
                continue
            break
        if verbose: print ("")
    sys.stdout.flush()
    icommand+=1

# Run command with stdout/stderr saved to logfile
def logged_call(cmd, logfile):
    global opt
    dirname = os.path.dirname(logfile)
    #print ("dirnamaa=========================  "+dirname)
    if dirname != "" and not os.path.exists(dirname):
        special_call(["mkdir", "-p", os.path.dirname(logfile)], 0)
    if opt.run:
        ntry = 0
        while True:
            try:
                with open(logfile, "a") as log:
                    proc = subprocess.Popen(cmd, stdout=log, stderr=log, close_fds=True)
                    proc.wait()
            except:
                print ("Could not write to disk (IOError), wait 10s and continue")
                time.sleep(10)
                ntry += 1
                if ntry == 20: sys.exit()
                continue
            break
    else:
        proc = subprocess.call(["echo", "[dry]"]+cmd+[">", logfile])

def load(f, name, pf=""):
    h = f.Get(name)
    h_new = ROOT.TH1D(h.GetName()+pf,h.GetTitle(),h.GetNbinsX(),h.GetXaxis().GetXmin(),h.GetXaxis().GetXmax())
    for i in range (0, h.GetNbinsX()):
        h_new.SetBinContent(i,h.GetBinContent(i));
        h_new.SetBinError(i,h.GetBinError(i));
    h_new.SetEntries(h.GetEntries())
    h_new.SetDirectory(0)
    return h_new


def bg_est(name, data, sub, mult, div):
    est = data.Clone(name)
    for hist in sub:
        est.Add(hist, -1)
    est.Multiply(mult)
    est.Divide(div)
    return est



def calc_syst_err(vh, name):
    nominal = vh[0].Clone(name)
    syst_up = vh[0].Clone(name+"_up")
    syst_dn = vh[0].Clone(name+"_dn")
    for binx in range(1, nominal.GetNbinsX()+1):
        err_up = nominal.GetBinError(binx) ** 2
        err_dn = nominal.GetBinError(binx) ** 2
    for i in range(1, len(vh)):
        syst_err = vh[i].GetBinContent(binx)-nominal.GetBinContent(binx)
        if syst_err>0:
            err_up += syst_err ** 2
 
        else:
            err_dn += syst_err ** 2
 
    err_up = err_up ** 0.5
    err_dn = err_dn ** 0.5
    syst_up.SetBinContent(binx, err_up)
    syst_dn.SetBinContent(binx, err_dn)
    return [nominal, syst_up, syst_dn]
 
    
# ----------------- Harvest histograms -------------------


print ("Loading histograms")


# Data
 

f = ROOT.TFile.Open("syst_"+opt.dir+"/DataCard_Test.root")

S_data = load(f,"Top/MRR2_S_bkg_Top","_data") # gecici olarak sadece data ici dolu olsub diye bir tane mc aldim


# Signal

S_signal = []
counter = 0
for ikey in range(0, f.GetListOfKeys().GetEntries()):
    name = f.GetListOfKeys().At(ikey).GetName()
    #print ("name11=========================  "+str(name))
    if name.startswith("MRR2_S_T5ttcc") and not "Up" in name and not "Down" in name:

        #print ("name22=========================  "+str(name))
        counter+=1
        S_syst = []
        for syst in systematics:
            S_syst.append(load(f, name+syst, "_sig"))
                #print ("S_syst=========================  "+str(S_syst))

            
        S_signal.append(S_syst)

    #if counter>10:
    #    break


# Background
# top

S_TT = []
for syst in systematics:
    S_TT.append(load(f,"Top/MRR2_S_bkg_Top"+syst,"_TT"))


# multijet

S_MJ = []
for syst in systematics:
    S_MJ.append(load(f,"Multijet/MRR2_S_bkg_Multijet"+syst,"_MJ"))
    
# wjets

S_WJ = []
for syst in systematics:
    S_WJ.append(load(f,"WJet/MRR2_S_bkg_WJet"+syst,"_WJ"))

# ztoinv
S_ZI = []
for syst in systematics:
    S_ZI.append(load(f,"ZJet/MRR2_S_bkg_ZJet"+syst,"_ZI"))

# other
S_OT = []
for syst in systematics:
    S_OT.append(load(f,"Other/MRR2_S_bkg_other"+syst,"_OT"))



# Caluclating background 
print "Calculating background"

Top_est      = []
MultiJet_est = []
WJets_est    = []
ZInv_est     = []
Other_est    = []
for i in range(0, len(systematics)):
    S_TT_est = S_TT[i].Clone("Top" +systematics[i])
    S_MJ_est = S_MJ[i].Clone("MultiJet"+systematics[i])
    S_WJ_est = S_WJ[i].Clone("WJets" +systematics[i])
    S_ZI_est = S_ZI[i].Clone("ZJets"+systematics[i])
    S_OT_est = S_OT[i].Clone("Other" +systematics[i])

    Top_est     .append(S_TT_est)
    MultiJet_est.append(S_MJ_est)
    WJets_est   .append(S_WJ_est)
    ZInv_est    .append(S_ZI_est)
    Other_est   .append(S_OT_est)



print ("Looping on Signal points")

# Now save a different root file for each signal point
if not opt.nocards and opt.TEST==0:
    print "Looping on Signal points and creating data cards"
    if not os.path.exists("syst_"+opt.dir+"/cards"):
        special_call(["mkdir", "-p", "syst_"+opt.dir+"/cards"], 0)


cards = []

for signal_syst in S_signal:
    scan_point = signal_syst[0].GetName()[:-4].replace("MRR2_S_T5ttcc_","")
    root_filename = "syst_"+opt.dir+"/cards/RazorBoost_SMS-"+opt.model+"_"+scan_point+"_"+opt.box+".root"


    print ("scan_point=========================  "+str(scan_point))
    fout = ROOT.TFile.Open(root_filename,"RECREATE")
    print (" -- Creating root file: "+root_filename)

    
    #fout = ROOT.TFile.Open(root_filename,"RECREATE")
    #print "  Creating root file: "+root_filename
    # Add signal systematics

    for i in range(0, len(systematics)):
        signal_syst[i].Write("Signal"+systematics[i])
        #print ("signal_syst[i]=========================  "+str(signal_syst[i]))


            # Add background estimates
    for bkg in [Top_est, MultiJet_est, WJets_est, ZInv_est, Other_est]:
        for syst_var in bkg:
            syst_var.Write()
            # Add data counts
    S_data.Write("data_obs")

    card_filename = root_filename.replace(".root",".txt")
    cards.append(card_filename)
    if not opt.nocards:
        print "  Creating data card: "+card_filename
        card=open(card_filename, 'w+')
        card.write(
'''imax 1 number of channels
jmax 5 number of backgrounds
kmax * number of nuisance parameters
------------------------------------------------------------
observation '''
        )
        card.write(str(S_data.Integral()))
        card.write(
           

'''
------------------------------------------------------------
shapes * * '''
        )
        card.write(root_filename)
        card.write(
''' $PROCESS $PROCESS_$SYSTEMATIC
------------------------------------------------------------
bin   '''
        )
        card.write("%s\t%s\t%s\t%s\t%s\t%s" % (opt.box, opt.box, opt.box, opt.box, opt.box, opt.box))
        card.write(
'''
process     Signal      Top     MultiJet     WJets     ZJets     Other
process     0           1          2          3        4        5
rate        '''
        )
        card.write("%.3f\t%.3f\t%.3f\t%.3f\t%.3f\t%.3f" % (signal_syst[0].Integral(), Top_est[0].Integral(), MultiJet_est[0].Integral(), WJets_est[0].Integral(), ZInv_est[0].Integral(), Other_est[0].Integral()) )
        card.write(

'''

------------------------------------------------------------

lumi                    lnN     1.025   1.025   1.025   1.025   1.025   1.025
toppt                   shape   -       1.0     1.0     1.0     1.0     1.0
isr                     shape   1.0     -       -       -       -        -
pileup                  shape   1.0     1.0     1.0     1.0     1.0     1.0
L1PreFiring             shape   1.0     1.0     1.0     1.0     1.0     1.0
alphas                  shape   1.0     1.0     1.0     1.0     1.0     1.0
scale                   shape   1.0     1.0     1.0     1.0     1.0     1.0
lostlep                 shape   1.0     1.0     1.0     1.0     1.0     1.0
trigger                 shape   1.0     1.0     1.0     1.0     1.0     1.0
jes                     shape   1.0     1.0     1.0     1.0     1.0     1.0
jer                     shape   1.0     1.0     1.0     1.0     1.0     1.0
met                     shape   1.0     1.0     1.0     1.0     1.0     1.0
RescaleAK8              shape   -       1.0     1.0     1.0     1.0     1.0
BoostTag                shape   -       1.0     1.0     1.0     1.0     1.0
BoostTag_Fastsim        shape   1.0     -       -       -       -        -
BoostmisTag             shape   -       1.0     1.0     1.0     1.0     1.0
BoostmisTag_Fastsim     shape   1.0     -       -       -       -        -
massTag                 shape   1.0     1.0     1.0     1.0     1.0     1.0
EleReco                 shape   -       1.0     1.0     1.0     1.0     1.0
EleID                   shape   -       1.0     1.0     1.0     1.0     1.0
EleIso                  shape   -       1.0     1.0     1.0     1.0     1.0
EleFastsim              shape   1.0     -       -       -       -        -
MuonTrack               shape   -       1.0     1.0     1.0     1.0     1.0
MuonFullsim             shape   -       1.0     1.0     1.0     1.0     1.0
MuonFastsim             shape   1.0     -       -       -       -        -
BTag                    shape   -       1.0     1.0     1.0     1.0     1.0
BTagFastsim             shape   1.0     -       -       -       -        -
cf_Q                    shape   -       -       1.0     -       -        -
cf_T                    shape   -       1.0     -       -       -        -
cf_W                    shape   -       -       -       1.0     -        -
cf_Z                    shape   -       -       -       -       1.0      -
cf_L                    shape   -       -       -       -       1.0      -
cf_njet_Q               shape   -       -       1.0     -       -        -
cf_njet_T               shape   -       1.0     -       -       -        -
cf_njet_W               shape   -       -       -       1.0     -        -
cf_njet_ZG              shape   -       -       -       -       1.0      -
cf_njet_ZL              shape   -       -       -       -       1.0      -
cf_NonIso_T             shape   -       1.0     -       -       -        -
cf_NonIso_W             shape   -       -       -       1.0     -        -
cf_NonIso_njet_T        shape   -       1.0     -       -       -        -
cf_NonIso_njet_W        shape   -       -       -       1.0     -        -
''')
card.close()
print "Done."


