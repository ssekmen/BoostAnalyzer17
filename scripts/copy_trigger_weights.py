import os, sys, ROOT

outdir = "trigger_eff/230603"

fin  = ROOT.TFile.Open("results/Plotter_out_2023_05_26.root")


if not os.path.exists(outdir): os.makedirs(outdir)
first = True
for year in ["2016","2016APV", "2017", "2018"]:
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
        [year+"_pho_eb"       , ["HLTEff_SinglePho_vs_PhotonPtFewBins/LeptonicMeasurements_"+year+"_Baseline_Barrel",  0, 807]], # (prev: 1) 0: HT  807,  1: MET 417
        [year+"_pho_ee"       , ["HLTEff_SinglePho_vs_PhotonPtFewBins/LeptonicMeasurements_"+year+"_Baseline_Endcap",  0, 807]], # (prev: 1) 0: HT  807,  1: MET 417
        ]
    print(year)
    for caninfo in cans:
        name = caninfo[0]
        info = caninfo[1]
        can = fin.Get(info[0])
        #print(name)
        #print(info)
        #print(can)
        if can.GetListOfPrimitives().At(info[1]).GetName() != "Graph":
            print("Error in file: "+fin.GetName()+", can: "+info[0]+" i="+str(info[1])+" - Not a Graph, it is: "+can.GetListOfPrimitives().At(info[1]).GetName()+" ("+can.GetListOfPrimitives().At(info[1]).GetTitle()+")")
            print("All items:")
            for i in range(can.GetListOfPrimitives().GetEntries()):
                print("i="+str(i)+": "+can.GetListOfPrimitives().At(i).GetName()+" ("+can.GetListOfPrimitives().At(i).GetTitle()+")")
                
        else:
            g = can.GetListOfPrimitives().At(info[1])
            if g.GetLineColor() != info[2]:
                print("Error, the color of the graph is not the expected one (correct measurement could be missing!)")
                print("Color of "+info[0]+" = "+str(g.GetLineColor()))
                print("Expected color: "+str(info[2]))
                print("All graphs:")
                for i in range(can.GetListOfPrimitives().GetEntries()):
                    if can.GetListOfPrimitives().At(i).GetName() == "Graph":
                        print("i="+str(i)+": "+str(can.GetListOfPrimitives().At(i).GetLineColor()))
                sys.exit()
            fout = ROOT.TFile.Open(outdir+"/TriggerEffRun2.root", "RECREATE" if first else "UPDATE")
            g.Write(name)
            fout.Close()
            first = False

fin.Close()
