import ROOT
ROOT.PyConfig.DisableRootLogon = True
ROOT.gROOT.SetBatch(True)
import sys
from common_functions import *

input_file  = "results/Plotter_out_2023_10_09_syst.root"
plotdir     = "Plots/scale_factors/2023_10_09/"
output_file = "scale_factors/boosted_objects/Top_W_Z_H_fakes.root"

def get_tgae_ratio_(data, mc):
    ratio = data.Clone()
    for i in range(ratio.GetN()):
        x_data = ROOT.Double(0)
        y_data = ROOT.Double(0)
        data.GetPoint(i, x_data, y_data)
        xh_data = data.GetErrorXhigh(i)
        xl_data = data.GetErrorXlow(i)
        yh_data = data.GetErrorYhigh(i)
        yl_data = data.GetErrorYlow(i)
        x_mc = ROOT.Double(0)
        y_mc = ROOT.Double(0)
        mc.GetPoint(i, x_mc, y_mc)
        yh_mc = mc.GetErrorYhigh(i)
        yl_mc = mc.GetErrorYlow(i)
        if (y_mc==0.):   continue
        y_ratio = y_data/y_mc
        if (y_data==0.):
            yh = yh_mc
            yl = yl_mc
        else:
            yh = y_ratio * ((yh_data*yh_data)/(y_data*y_data) + (yh_mc*yh_mc)/(y_mc*y_mc))**0.5
            yl = y_ratio * ((yl_data*yl_data)/(y_data*y_data) + (yl_mc*yl_mc)/(y_mc*y_mc))**0.5
        yl = min(yl, y_ratio)
        ratio.SetPoint(i, x_data, y_ratio)
        ratio.SetPointError(i, xl_data, xh_data, yl, yh)
    return ratio

def getplot(inname, canname, index, clonename, add_syst=0.0, replace=0):
    fin = ROOT.TFile.Open(inname, "READ")
    #print canname
    can = fin.Get(canname)
    can.Draw()
    g = can.GetListOfPrimitives().At(index)
    #print canname
    # Add JES uncertainties (for fake rates only)
    ##  if "Fake" in canname:
    ##      g_num       = can.GetListOfPrimitives().At(index-2).Clone(clonename)
    ##      g_den       = can.GetListOfPrimitives().At(index-2).Clone(clonename)
    ##      g_den_jesUp = fin.Get(canname.replace("__","_syst1_")).GetListOfPrimitives().At(0).Clone(clonename+"_jesUp")
    ##      g_den_jesDn = fin.Get(canname.replace("__","_syst2_")).GetListOfPrimitives().At(0).Clone(clonename+"_jesDn")
    ##      g_jesUp = get_tgae_ratio_(g_num, g_den_jesUp)
    ##      g_jesDn = get_tgae_ratio_(g_num, g_den_jesDn)
    ##      for i in range(g.GetN()):
    ##          x     = ROOT.Double(0)
    ##          x_up  = ROOT.Double(0)
    ##          x_dn  = ROOT.Double(0)
    ##          y     = ROOT.Double(0)
    ##          y_up  = ROOT.Double(0)
    ##          y_dn  = ROOT.Double(0)
    ##          g.GetPoint(i, x, y)
    ##          for j in range(g_jesUp.GetN()):
    ##              g_jesUp.GetPoint(j, x_up, y_up)
    ##              if x_up==x: break
    ##          if x_up==x:
    ##              for j in range(g_jesDn.GetN()):
    ##                  g_jesDn.GetPoint(j, x_dn, y_dn)
    ##                  if x_dn==x: break
    ##              if x_dn==x:
    ##                  yl    = g.GetErrorYlow(i)
    ##                  yh    = g.GetErrorYhigh(i)
    ##                  yl_syst = min(0, min(y_up-y, y_dn-y))
    ##                  yh_syst = max(0, max(y_up-y, y_dn-y))
    ##                  yl_tot = (yl*yl + yl_syst*yl_syst)**0.5
    ##                  yh_tot = (yh*yh + yh_syst*yh_syst)**0.5
    ##                  g.SetPointError(i, g.GetErrorXlow(i), g.GetErrorXhigh(i), yl_tot, yh_tot)
    ##                  #print ( "%d   %d %d %d    %3.2f+%3.3f-%3.3f   %3.2f %3.2f   +%3.3f  -%3.3f" % (i, x, x_up, x_dn, y, yh, yl, y_up, y_dn, yh_tot, yl_tot))
    ##      # Add also the 1b systematic
    ##      can_1b = fin.Get(canname.replace("_F_","_f_").replace("_Excl0b","_Excl1b"))
    ##      g_1b = can_1b.GetListOfPrimitives().At(index).Clone(clonename+"_1b")
    ##      avg_syst = 0
    ##      n = 0
    ##      for i in range(g.GetN()):
    ##          x_1b  = ROOT.Double(0)
    ##          y_1b  = ROOT.Double(0)
    ##          g.GetPoint(i, x, y)
    ##          for j in range(g_1b.GetN()):
    ##              g_1b.GetPoint(j, x_1b, y_1b)
    ##              if x_1b==x: break
    ##          if x_1b==x:
    ##              # Add the difference as a symmetric uncertainty
    ##              yl = g.GetErrorYlow(i)
    ##              yh = g.GetErrorYhigh(i)
    ##              y_syst = abs(y_1b-y)
    ##              if (add_syst>0): y_syst = ( (y_syst ** 2) + (add_syst ** 2) ) ** 0.5
    ##              yl_tot = min((yl*yl + y_syst*y_syst)**0.5, y)
    ##              yh_tot = (yh*yh + y_syst*y_syst)**0.5
    ##              g.SetPointError(i, g.GetErrorXlow(i), g.GetErrorXhigh(i), yl_tot, yh_tot)
    ##              #print ( "%d   x=%d   orig-y: %3.3f+%3.3f-%3.3f   1b-y: %3.3f   syst: %3.3f --> new-y(err): +%3.3f-%3.3f" % (i, x, y, yh, yl, y_1b, y_syst, yh_tot, yl_tot))
    ##              if (yl>0 or yh>0) and x<2000:
    ##                  avg_syst += y_syst
    ##                  n+=1
    ##      avg_syst /= n
    ##      #print ("%.1f - %s" % (avg_syst*100, canname))
    ##  elif "FullFastSim" in canname:
    ##      # Add also the baseline selection as a systematic
    ##      can_baseline = fin.Get(canname.replace("FullFastSim","FullFastSim_P_NoWeight"))
    ##      g_baseline = can_baseline.GetListOfPrimitives().At(index).Clone(clonename+"_baseline")
    ##      if replace:
    ##          can = can_baseline
    ##          g   = g_baseline
    ##          can.Draw()
    ##      else:
    ##          avg_syst = 0
    ##          n = 0
    ##          for i in range(g.GetN()):
    ##              x       = ROOT.Double(0)
    ##              y       = ROOT.Double(0)
    ##              x_baseline  = ROOT.Double(0)
    ##              y_baseline  = ROOT.Double(0)
    ##              g.GetPoint(i, x, y)
    ##              for j in range(g_baseline.GetN()):
    ##                  g_baseline.GetPoint(j, x_baseline, y_baseline)
    ##                  if x_baseline==x: break
    ##              if x_baseline==x:
    ##                  # Add the difference as an assymmetric uncertainty
    ##                  yl = g.GetErrorYlow(i)
    ##                  yh = g.GetErrorYhigh(i)
    ##                  yl_tot = yl ** 2
    ##                  yh_tot = yh ** 2
    ##                  if y_baseline<y: yl_tot += (y-y_baseline) ** 2
    ##                  if y_baseline>y: yh_tot += (y_baseline-y) ** 2
    ##                  if add_syst>0:
    ##                      yl_tot += add_syst ** 2
    ##                      yh_tot += add_syst ** 2
    ##                  yl_tot = min(yl_tot**0.5, y)
    ##                  yh_tot = yh_tot**0.5
    ##                  g.SetPointError(i, g.GetErrorXlow(i), g.GetErrorXhigh(i), yl_tot, yh_tot)
    ##                  #print ( "%d   x=%d  skim-y: %3.3f+%3.3f-%3.3f   baseline-y: %3.3f   -->   new-y(err): +%3.3f-%3.3f" % (i, x, y, yh, yl, y_baseline, yh_tot, yl_tot))
    ##                  if (yl_tot>0 or yh_tot>0) and x<2000:
    ##                      avg_syst += (yl_tot+yh_tot)/2
    ##                      n+=1
    ##          avg_syst /= n
    ##          #print ("%.1f - %s" % (avg_syst*100, canname))
    #sys.exit()
    can.Update()
    name = plotdir+canname.replace("/","_").replace("Few","").replace("Bins","").replace("OneBin","").replace("F__","F_").replace("F_Excl0b_","F_Excl0b").replace("_Data_MC","")
    save_plot(can, "", name, 0)
    fin.Close()
    return g

for year in ["2016", "2016APV", "2017", "2018"]:
    # Fake rates (Data/MC)
    #bLepJet   = getplot(input_file, "LepJetTagFakeRate_vs_JetAK8PtBins/"+   "Data_MC_"+year+"_CR_Fake_0b__Barrel", 2, "bLepJet")
    bHadTop   = getplot(input_file, "HadTopTagFakeRate_vs_JetAK8PtBins/"+   "Data_MC_"+year+"_CR_Fake__Barrel", 2, "bHadTop")
    bHadV     = getplot(input_file, "HadVTagFakeRate_vs_JetAK8PtBins/"+     "Data_MC_"+year+"_CR_Fake__Barrel", 2, "bHadV")
    bHadH     = getplot(input_file, "HadHTagFakeRate_vs_JetAK8PtBins/"+  		"Data_MC_"+year+"_Pre__Barrel",     2, "bHadH")
    #bHadHTop  = getplot(input_file, "HadHTagFakeRate_vs_JetAK8PtFewBins/"+  "Data_MC_"+year+"_CR_Real__Barrel",        2, "bHadHTop")
    #bMassFake = getplot(input_file, "MassTagFakeRate_vs_JetAK8PtBins/"+     "Data_MC_"+year+"_CR_Fake_0b__Barrel", 2, "bMassFake")
    #bMassTop  = getplot(input_file, "MassTagFakeRate_vs_JetAK8PtBins/"+     "Data_MC_"+year+"_CR_Real__Barrel",        2, "bMassTop")
    #eLepJet   = getplot(input_file, "LepJetTagFakeRate_vs_JetAK8PtFewBins/"+ "Data_MC_"+year+"_CR_Fake__Endcap",        2, "eLepJet")
    eHadTop   = getplot(input_file, "HadTopTagFakeRate_vs_JetAK8PtFewBins/"+   "Data_MC_"+year+"_CR_Fake__Endcap", 2, "eHadTop")
    eHadV     = getplot(input_file, "HadVTagFakeRate_vs_JetAK8PtFewBins/"+     "Data_MC_"+year+"_CR_Fake__Endcap", 2, "eHadV")
    eHadH     = getplot(input_file, "HadHTagFakeRate_vs_JetAK8PtFewBins/"+   	"Data_MC_"+year+"_Pre__Endcap",     2, "eHadH")
    #eHadHTop  = getplot(input_file, "HadHTagFakeRate_vs_JetAK8PtTwoBin/"+   "Data_MC_"+year+"_CR_Real__Endcap",        2, "eHadHTop")
    #eMassFake = getplot(input_file, "MassTagFakeRate_vs_JetAK8PtFewBins/"+     "Data_MC_"+year+"_CR_Fake_0b__Endcap", 2, "eMassFake")
    #eMassTop  = getplot(input_file, "MassTagFakeRate_vs_JetAK8PtFewBins/"+     "Data_MC_"+year+"_CR_Real__Endcap",        2, "eMassTop")

    if not year=="2016APV":
    	#fLepJet   = getplot(input_file, "LepJetTaggingEfficiency_vs_GenMatchedAK8JetPtBins/"+   "FullFastSim_"+year+"_Pre_", 2, "fLepJet")
    	fHadTop   = getplot(input_file, "HadTopTaggingEfficiency_vs_GenMatchedAK8JetPtBins/"+   "FullFastSim_"+year+"_Pre_", 2, "fHadTop")
    	fHadW     = getplot(input_file, "HadWTaggingEfficiency_vs_GenMatchedAK8JetPtBins/"+     "FullFastSim_"+year+"_Pre_", 2, "fHadW")
    	fHadZ     = getplot(input_file, "HadZTaggingEfficiency_vs_GenMatchedAK8JetPtBins/"+     "FullFastSim_"+year+"_Pre_", 2, "fHadZ")
    	fHadV     = getplot(input_file, "HadVTaggingEfficiency_vs_GenMatchedAK8JetPtBins/"+     "FullFastSim_"+year+"_Pre_", 2, "fHadV")
    	fHadH     = getplot(input_file, "HadHTaggingEfficiency_vs_GenMatchedAK8JetPtBins/"+  		"FullFastSim_"+year+"_Pre_", 2, "fHadH")

    
    fout1 = ROOT.TFile.Open(output_file, "RECREATE" if year=="2016" else "UPDATE")
    #bLepJet.Write("full_fake_"+year+"_bLepJet")
    #eLepJet.Write("full_fake_"+year+"_eLepJet")
    bHadTop.Write("full_fake_"+year+"_bHadTop")
    eHadTop.Write("full_fake_"+year+"_eHadTop")
    bHadV.Write("full_fake_"+year+"_bHadV")
    eHadV.Write("full_fake_"+year+"_eHadV")
    bHadH.Write("full_fake_"+year+"_bHadH")
    eHadH.Write("full_fake_"+year+"_eHadH")
    #bHadHTop.Write("full_fake_"+year+"_bHadHTop")
    #eHadHTop.Write("full_fake_"+year+"_eHadHTop")
    #bMassFake.Write("full_fake_"+year+"_bMass")
    #eMassFake.Write("full_fake_"+year+"_eMass")
    #bMassTop.Write("full_real_"+year+"_bMassTop")
    #eMassTop.Write("full_real_"+year+"_eMassTop")
    if not year=="2016APV":
    	#fLepJet.Write("full_fast_"+year+"_LepJet")
    	fHadTop.Write("full_fast_"+year+"_HadTop")
    	fHadW.Write("full_fast_"+year+"_HadW")
    	fHadZ.Write("full_fast_"+year+"_HadZ")
    	fHadV.Write("full_fast_"+year+"_HadV")
    	fHadH.Write("full_fast_"+year+"_HadH")
    fout1.Close()

# Fast/FullSim
##  bWFF    = getplot(input_file, "WTaggingEfficiency_vs_GenWMatchedAK8JetPtBins/FullFastSim_Barrel",     3, "bWFF")
##  
##  fout2 = ROOT.TFile.Open(output_file, "RECREATE")
##  bWFF   .Write("bWFF")
##  fout2.Close()
