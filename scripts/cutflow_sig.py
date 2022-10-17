import sys
from string import *
from ROOT import TFile
from math import sqrt 

def printCut(cut,info,option="counts"):
    sig1 = 0
    sig2 = 0
    for sample,t in info.iteritems():
        c = t[cut]
        effxs = c 
        if "GluinoToRPVStopbl" in sample:
            sig1 = effxs
        if "SbotToRPVN1qqlv" in sample:
            sig2 = effxs
    if option == "counts":
        #print "Cut %s \t %d \t %d" % (cut,sig1,sig2)
        row = "%s & %.4g & %.4g \\\\ \n" % (cut,sig1,sig2) 
        return row.replace("%","\%")
    
def makeCutflowTable(info,intlumi,cuts):
    table = open("cutflow.tex",'w')
    # get the table header stuff
    header = """\\begin{sidewaystable}[p]
\\centering
\\fontsize{7 pt}{1 em}
\\selectfont
\\caption{Cutflow table. Event counts are normalized to $%(lumi)s\\textrm{fb}^{-1}$. }
\\begin{tabular}{| l || c | c |}
\\hline
Cut & GluinoToRPVStopbl & SbotToRPVN1qqlv \\\\ \\hline
""" % {"lumi":intlumi}
    table.write(header)

    # put the body of the table
    for cut in cuts:
        table.write( printCut(cut,info,"counts") )
        #table.write( printCut(cut,info,signame,"Percentage") )
        table.write("\\hline\n")
        
    # put the table closing stuff
    footer = """\\end{tabular}
\\label{tab:cutflow}
\\end{sidewaystable}
"""
    table.write(footer)
    
    table.close()

def allcuts():
    cuts = [
#"CR_2LepInv_1JetAK8", "CR_2LepInv_NJet", "CR_2LepInv_MR", "CR_2LepInv_HLT", "CR_2LepInv_2Lep", "CR_2LepInv_0Pho", "CR_2LepInv_R2", "CR_2LepInv_OppCharge", "CR_2LepInv_1M", "CR_2LepInv_dPhi", "CR_2LepInv_Mll"
"SR_Had_1htop_sf_3", "SR_Had_2htop_sf_3", "SR_Had_V_b_45j_sf_3", "SR_Had_V_b_6j_sf_3", "SR_Had_1V_0b_34j_sf_3", "SR_Had_1V_0b_5j_sf_3", "SR_Had_2V_0b_24j_sf_3", "SR_Had_2V_0b_5j_sf_3", "SR_Had_H_b_45j_sf_3", "SR_Had_H_b_6j_sf_3", "SR_Had_2H_b_6j_sf_3", "SR_Had_HV_b_6j_sf_3", "SR_Had_1H_0b_34j_sf_3", "SR_Had_1H_0b_5j_sf_3", "SR_Had_2H_0b_34j_sf_3", "SR_Had_2H_0b_5j_sf_3", "SR_Had_HV_0b_24j_sf_3", "SR_Had_HV_0b_5j_sf_3", "SR_Lep_1htop_sf_3", "SR_Lep_V_b_sf_3", "SR_Lep_V_0b_sf_3", "SR_Lep_H_b_sf_3", "SR_Lep_H_0b_sf_3", "SR_Leptop_0htop_sf_3", "SR_Leptop_1htop_sf_3", "SR_Lepjet_0V_24j_sf_3", "SR_Lepjet_0V_5j_sf_3", "SR_Lepjet_1V_24j_sf_3", "SR_Lepjet_1V_5j_sf_3"
            ]
    return cuts

if __name__ == '__main__':

    #if len(sys.argv) < 2:
        #print "Run as: python %s <samples file> " % (sys.argv[0])
        #sys.exit()
    #samplesfile = sys.argv[1]
    
    #datasets = open(samplesfile).readlines()
    #datasets = open(samplesfile).read().splitlines()

    names = {}
    info = {}
    counts_allhad = {}
    counts_semilep = {}
    counts_dilep = {}
        
    # Integrated luminosity in fb-1s
    intlumi = 137

    inputdir = "../results/run_2022_10_04/hadd/"
    signame = "2017_GluinoToRPVStopbl"
    
    fs = TFile.Open(inputdir + signame + ".root") #It should be fixed.
    histos = fs.Get("counts")
    countss = {}
    for bin in range(histos.GetNbinsX()):
        countss[histos.GetXaxis().GetBinLabel(bin+1)] = histos.GetBinContent(bin+1)
    info[signame] = (countss)

    datasets = {"2017_GluinoToRPVStopbl", "2017_SbotToRPVN1qqlv"}
    
    for d in datasets:
        sample = d
        samplew_ = sample.replace('/', '_')
        names['samplew_'] = samplew_
        print(d)
        f = TFile.Open(inputdir+d + ".root")
        histo = f.Get("counts")
        counts = {}
        for bin in range(histo.GetNbinsX()):
            counts[histo.GetXaxis().GetBinLabel(bin+1)] = histo.GetBinContent(bin+1)
        if counts["NoCuts"] == 0: continue
        info[samplew_] = (counts)
        f.Close()


    cuts = allcuts()
    #print "Make cutflow table"

    #print "Cut \t \t qcd \t tt \t wj \t diboson \t single top \t ZJet \t TTX \t DYJet \t Higgs \t signal \t data \n"
    makeCutflowTable(info,intlumi,cuts)

    #print "\n"
