import ROOT, glob

source = "results/run_2021_04_09_syst"
#source = "results/run_2021_04_18_unskim" #--> very different weights for top signals


inputs = sorted(glob.glob(source+"/hadd/*SMS*.root"))

for signal in inputs:
    fin = ROOT.TFile.Open(signal)
    hin = fin.Get("totweight_isr")
    print signal.split("/")[-1].replace(".root","").replace("_"," ",1)+" "+str(hin.GetBinContent(1)/hin.GetBinContent(2))
    fin.Close()
