import os, sys, ROOT


#outdir = "trigger_eff/200429"
#outdir = "trigger_eff/200508"
#outdir = "trigger_eff/200511"
#outdir = "trigger_eff/200601"
#outdir = "trigger_eff/200603"
#outdir = "trigger_eff/200607"
outdir = "trigger_eff/210220"

#fin  = ROOT.TFile.Open("results/Plotter_out_2019_12_12.root")
#fin  = ROOT.TFile.Open("results/Plotter_out_2020_01_31.root")
#fin  = ROOT.TFile.Open("results/Plotter_out_2020_02_03.root")
#fin  = ROOT.TFile.Open("results/Plotter_out_2020_02_21.root")
#fin  = ROOT.TFile.Open("results/Plotter_out_2020_04_03.root")
#fin  = ROOT.TFile.Open("results/Plotter_out_2020_04_29.root")
#fin  = ROOT.TFile.Open("results/Plotter_out_2020_04_30.root")
#fin  = ROOT.TFile.Open("results/Plotter_out_2020_05_06.root")
#fin  = ROOT.TFile.Open("results/Plotter_out_2020_05_08.root")
#fin  = ROOT.TFile.Open("results/Plotter_out_2020_05_11.root")
#fin  = ROOT.TFile.Open("results/Plotter_out_2020_05_26_unskim.root")
#fin  = ROOT.TFile.Open("results/Plotter_out_2020_06_01.root")
#fin  = ROOT.TFile.Open("results/Plotter_out_2020_06_03.root")
#fin  = ROOT.TFile.Open("results/Plotter_out_2020_06_07_unskim.root")
fin  = ROOT.TFile.Open("results/Plotter_out_2021_02_20_syst.root")


if not os.path.exists(outdir): os.makedirs(outdir)
first = True
for year in ["2016", "2017", "2018"]:
    #can1 = fin.Get("HLTEff_MET_or_HT_MET_or_HT_vs_HTMET/HadronicMeasurements_Baseline")
    #can2 = fin.Get("HLTEff_MET_or_HT_MET_or_HT_vs_HTMET/HadronicMeasurementsNoR2_BaselineNoR2")
    #can1 = fin.Get("HLTEff_PFMET120_PFMHT120_vs_MET/HadronicMeasurements_Baseline")
    #can2 = fin.Get("HLTEff_PFMET120_PFMHT120_vs_MET/HadronicMeasurementsNoR2_BaselineNoR2")
    #can1 = fin.Get("HLTEff_PFMET120_PFMHT120_vs_METFixEE2017/HadronicMeasurements_Baseline")
    #can2 = fin.Get("HLTEff_PFMET120_PFMHT120_vs_METFixEE2017/HadronicMeasurementsNoR2_BaselineNoR2")
    #can1 = fin.Get("HLTEff_Boost_vs_HTMET/HadronicMeasurements_Baseline_"+year)
    #can2 = fin.Get("HLTEff_Boost_vs_HTMET/HadronicMeasurementsNoR2_BaselineNoR2_"+year)
    
    #vg1 = []
    #for i in range(can1.GetListOfPrimitives().GetEntries()):
    #    if can1.GetListOfPrimitives().At(i).GetName() == "Graph":
    #        vg1.append(can1.GetListOfPrimitives().At(i))
    #vg2 = []
    #for i in range(can2.GetListOfPrimitives().GetEntries()):
    #    if can2.GetListOfPrimitives().At(i).GetName() == "Graph":
    #        vg2.append(can2.GetListOfPrimitives().At(i))
    
    #fout = ROOT.TFile.Open("trigger_eff/191218/TriggerEff2017.root","RECREATE")
    #fout = ROOT.TFile.Open("trigger_eff/191218/TriggerEff2017_METonly.root","RECREATE")
    #fout = ROOT.TFile.Open("trigger_eff/191218/TriggerEff2017_METonly_FixEE2017.root","RECREATE")
    #fout = ROOT.TFile.Open("trigger_eff/191218/TriggerEff2017_FixEE2017.root","RECREATE")
    #fout = ROOT.TFile.Open("trigger_eff/200405/TriggerEffRun2.root", "RECREATE" if year=="2016" else "UPDATE")
    #vg1[0].Write("ele_"+year)
    #vg1[1].Write("pho_"+year)
    #vg1[2].Write("mu_"+year)
    #vg2[0].Write("nor2_ele_"+year)
    #vg2[1].Write("nor2_pho_"+year)
    #vg2[1].Write("nor2_mu_"+year)
    
    cans = [
        [year+"_had_ele"      , ["HLTEff_Hadronic_vs_HTMET/HadronicMeasurements_"+year+"_Baseline",                 1, 633]], # (prev: 1) 1: Ele 633, 52: Muon 601 51: Pho 402
        [year+"_had_ele_nor2" , ["HLTEff_Hadronic_vs_HTMET/HadronicMeasurementsNoR2_"+year+"_BaselineNoR2",         1, 633]], # (prev: 1) 1: Ele 633, 52: Muon 601 51: Pho 402
        [year+"_had_mu"       , ["HLTEff_Hadronic_vs_HTMET/HadronicMeasurements_"+year+"_Baseline",                52, 601]], # (prev: 1) 1: Ele 633, 52: Muon 601 51: Pho 402
        [year+"_had_mu_nor2"  , ["HLTEff_Hadronic_vs_HTMET/HadronicMeasurementsNoR2_"+year+"_BaselineNoR2",        52, 601]], # (prev: 1) 1: Ele 633, 52: Muon 601 51: Pho 402
        [year+"_had_pho"      , ["HLTEff_Hadronic_vs_HTMET/HadronicMeasurements_"+year+"_Baseline",                51, 402]], # (prev: 1) 1: Ele 633, 52: Muon 601 51: Pho 402
        #[year+"_had_pho_nor2" , ["HLTEff_Hadronic_vs_HTMET/HadronicMeasurementsNoR2_"+year+"_BaselineNoR2",        51, 402]], # (prev: 1) 1: Ele 633, 52: Muon 601 51: Pho 402
        [year+"_had_pho_nor2" , ["HLTEff_Hadronic_vs_PhotonPtBins/HadronicMeasurementsNoR2_"+year+"_BaselineNoR2",   1, 402]], # (prev: 1) 0: Ele 633, 2: Muon 601 1: Pho 402
        [year+"_ele"          , ["HLTEff_SingleEle_vs_ElePt/LeptonicMeasurements_"+year+"_Baseline_1Ele",           1, 417]], # (prev: 1) 0: HT  807,  1: MET 417
        [year+"_mu"           , ["HLTEff_SingleMu_vs_MuPt/LeptonicMeasurements_"+year+"_Baseline_1Muon",            1, 417]], # (prev: 1) 0: HT  807,  1: MET 417
        [year+"_pho_eb"       , ["HLTEff_SinglePho_vs_PhotonPtBins/LeptonicMeasurements_"+year+"_Baseline_Barrel",  0, 807]], # (prev: 1) 0: HT  807,  1: MET 417
        [year+"_pho_ee"       , ["HLTEff_SinglePho_vs_PhotonPtBins/LeptonicMeasurements_"+year+"_Baseline_Endcap",  0, 807]], # (prev: 1) 0: HT  807,  1: MET 417
        ]
    for caninfo in cans:
        name = caninfo[0]
        info = caninfo[1]
        can = fin.Get(info[0])
        if can.GetListOfPrimitives().At(info[1]).GetName() != "Graph":
            print "Error in file: "+fin.GetName()+", can: "+info[0]+" i="+str(info[1])+" - Not a Graph, it is: "+can.GetListOfPrimitives().At(info[1]).GetName()+" ("+can.GetListOfPrimitives().At(info[1]).GetTitle()+")"
            print "All items:"
            for i in range(can.GetListOfPrimitives().GetEntries()):
                print "i="+str(i)+": "+can.GetListOfPrimitives().At(i).GetName()+" ("+can.GetListOfPrimitives().At(i).GetTitle()+")"
                
        else:
            g = can.GetListOfPrimitives().At(info[1])
            if g.GetLineColor() != info[2]:
                print "Error, the color of the graph is not the expected one (correct measurement could be missing!)"
                print "Color of "+info[0]+" = "+str(g.GetLineColor())
                print "Expected color: "+str(info[2])
                print "All graphs:"
                for i in range(can.GetListOfPrimitives().GetEntries()):
                    if can.GetListOfPrimitives().At(i).GetName() == "Graph":
                        print "i="+str(i)+": "+str(can.GetListOfPrimitives().At(i).GetLineColor())
                sys.exit()
            fout = ROOT.TFile.Open(outdir+"/TriggerEffRun2.root", "RECREATE" if first else "UPDATE")
            g.Write(name)
            fout.Close()
            first = False

fin.Close()

