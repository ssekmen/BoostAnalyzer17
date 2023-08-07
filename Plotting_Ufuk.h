#ifndef PLOTTING_H
#define PLOTTING_H
#include "include/Analysis.h"

//_______________________________________________________
//                  Calculate variables


//_______________________________________________________
//      Define Histo options: Filling/Postfixes

void
Plotting::define_additional_histo_settings(const Weighting& w, EventSelections& evt_sel, const unsigned int& syst_nSyst, const unsigned int& syst_index)
{
  
}

//_______________________________________________________
//              Define Histograms here
void
Plotting::define_additional_histos(const Weighting& w, const unsigned int& syst_nSyst, const unsigned int& syst_index) {


  //__________________________________
  //        Define Smarthistos
  //__________________________________

  // Usage of AddHistos:
  // sh.AddHistos(type, { .fill=fill parameter(s), .pfs={list of posfix names}, .cuts={list of cuts},.draw="ROOT Draw() options", .opt="SmartHistos options", .ranges={plot ranges and overridden legend location}});
  // 1st param: string, the object/event type defined by the first parameter in AddHistoType()
  // 2nd param (.fill): string, either the name of a FillParam using the first parameter of AddNeFillParams() for a 1D histo, or two fillparams separated by "_vs_" for a 2D one
  // 3rd param (.pfs):  vector of strings for each Postfix name defined by the first parameter in AddNewPostfix(), supports up to 5 Postfix
  //                    N.B: for 1D plots, the first postfix is used to draw different plots on the same canvas, while creating multiple plots with the rest
  // 4th param (.cuts): vector of cuts before filling (I do not encourage the usage, because usually postfixes work nicer by attaching a string to the plot name)
  // 5th param (.draw): The option to use when using the TH1D/TH2D.Draw() method
  // 6th param (.opt):  SmartHistos specific options, some common examples:
  //   "Stack"+"N"   : Make a stack histo for all postfix, except the first N (can be data, signals, etc.)
  //   "Log"         : Log Y or Z scale
  //   "LogX"        : Log X scale
  //   "TwoCol"+"XY" : Split legend to two columns, and specify how many rows should each hav maximum
  //   "AddInt"      : Add integral of the histogram to the legend
  //   "AddRatio"    : Create a ratio of either 1st pf / 2nd pf, or 1st and pf/stacked histo
  //   There are many more, please peek into source code for complete list or see other examples
  // 7th .ranges: List of axis ranges in order: xlow,xhigh, ylow,yhigh, then  zlow,zhigh for 2D plot 
  //              OR the location of the top left edge of the legend (x1,y2), the legend size is auto adjusted 
  //              (by setting x2 and y1 depending on the number of entries)

  // Systematics:

  // The systematics of the plot are hidden in an additional dimension added to the histogram
  // eg.  a TH1D and it's systematic variations are stored in a TH2D
  // Each extra dimensional bin contain a variation of the underlying distribution
  // To enable this, a special dummy axis needs to be added which is called "Counts"
  // The string "Counts_vs_" is added to the plot name
  // and the "syst " is attached to the histogram type so the code knows to fill this
  // additional axis

  
  bool systematics = 1;
  
  std::string s = "";
  std::string c = "";
  if (systematics) {
    s = "syst ";
    c = "Counts_vs_";
  }

  sh.SetHistoWeights({ [] { return 1; } });

  for (auto region : {Region::CR_1PhoInv}){
    //sh.SetHistoWeights({ [&w,region] { return w.w_nm1[region][9]*w.triggereff_pho;} });
    sh.SetHistoWeights({ [&w,region] { return w.sf_weight[region]; } });
    std::string cut(magic_enum::enum_name(region));
    std::string opt  = o_stk_d; 
    //sh.AddHistos(s+"prepho", {.fill="NJetNoPho_vs_PhotonCHIso_preslectphopt", .pfs={"Data_MC", "SIEIE", "EB", "Year", cut}, .cuts={}, .draw=d, .opt={}, .ranges={}});
    //sh.AddHistos(s+"prepho", {.fill="NJetNoPho_vs_PhotonCHIso_preslectphopt", .pfs={"Data_MC", "SIEIE", "EE", "Year", cut}, .cuts={}, .draw=d, .opt={}, .ranges={}});

    //sh.AddHistos(s+"prepho", {.fill="MRR2NoPho_vs_PhotonCHIso_preslectphopt", .pfs={"Data_MC", "SIEIE", "EB", "Year", cut}, .cuts={}, .draw=d, .opt={}, .ranges={}}); 
    //sh.AddHistos(s+"prepho", {.fill="MRR2NoPho_vs_PhotonCHIso_preslectphopt", .pfs={"Data_MC", "SIEIE", "EE", "Year", cut}, .cuts={}, .draw=d, .opt={}, .ranges={}});
    //
    //sh.AddHistos("prepho", {.fill="MRR2NoPhoBins_vs_PhotonSIEIE", .pfs={"Data_MC","1Fake","EB_EE",cut+"_Excl1Pho"}, .cuts={}, .draw=d, .opt={}, .ranges={}}); 	
    //sh.AddHistos("prepho", {.fill="MRR2NoPhoBins_vs_PhotonSIEIE", .pfs={"Data_MC","EB_EE","PromptDirect","SIEIE",cut+"_Excl1Pho"}, .cuts={}, .draw=d, .opt={}, .ranges={}});
    //sh.AddHistos("prepho", {.fill="MRR2NoPhoBins_vs_PhotonSIEIE", .pfs={"Data_MC","EB_EE","SIEIE",cut+"_Excl1Pho"}, .cuts={}, .draw=d, .opt={}, .ranges={}});
    //sh.AddHistos("prepho", {.fill="MRR2NoPho_vs_PhotonSIEIEtimesPt", .pfs={"Data_MC", "EB_EE" , "SIEIE", "Year", cut+"_Excl1Pho"}, .cuts={}, .draw="PE1",.opt=o_1or2d_d+"AddRatio", .ranges={}});    
    //
    //sh.AddHistos("prepho", {.fill="MRR2NoPho_vs_PhotonCHIso_preslectphopt", .pfs={"Data_MC", "EB_EE" , "SIEIE", "Year", cut+"_Excl1Pho"}, .cuts={}, .draw="PE1",.opt=o_1or2d_d+"AddRatio", .ranges={}});   

   //sh.AddHistos("prepho", {.fill="MRR2NoPhoBins_vs_PhotonCHIso_preslectphopt", .pfs={"Data_MC","1Fake","EB_EE",cut+"_Excl1Pho"}, .cuts={}, .draw=d, .opt={}, .ranges={}}); //Fake

   //sh.AddHistos("prepho", {.fill="MRR2NoPhoBins_vs_PhotonCHIso_preslectphopt", .pfs={"Data_MC","EB_EE","PromptDirect","SIEIE",cut+"_Excl1Pho"}, .cuts={}, .draw=d, .opt={}, .ranges={}}); //Prompt

  //sh.AddHistos("prepho", {.fill="MRR2NoPhoBins_vs_PhotonCHIso_preslectphopt", .pfs={"Data_MC","EB_EE","SIEIE",cut+"_Excl1Pho"}, .cuts={}, .draw=d, .opt={}, .ranges={}}); //Target

  //sh.AddHistos("prepho", {.fill="MRR2NoPho_vs_PhotonCHIso_METpho", .pfs={"Data_MC", "1Fake", "EB_EE", cut+"_Excl1Pho"}, .cuts={}, .draw=d, .opt={}, .ranges={}}); //Fake

  //sh.AddHistos("prepho", {.fill="MRR2NoPho_vs_PhotonCHIso_METpho", .pfs={"Data_MC", "EB_EE", "PromptDirect", "SIEIE", cut+"_Excl1Pho"}, .cuts={}, .draw=d, .opt={}, .ranges={}}); //Prompt

  //sh.AddHistos("prepho", {.fill="MRR2NoPho_vs_PhotonCHIso_METpho", .pfs={"Data_MC", "EB_EE", "SIEIE", cut+"_Excl1Pho"}, .cuts={}, .draw=d, .opt={}, .ranges={}}); //Target

  sh.AddHistos("prepho", {.fill="MRR2NoPhoBins_vs_PhotonSIEIE", .pfs={"Data_MC","FakePhoton","EB_EE",cut+"_Excl1Pho"}, .cuts={}, .draw=d, .opt={}, .ranges={}}); //Fake
  sh.AddHistos("prepho", {.fill="MRR2NoPhoBins_vs_PhotonSIEIE", .pfs={"Data_MC","PromptPhoton","EB_EE",cut+"_Excl1Pho"}, .cuts={}, .draw=d, .opt={}, .ranges={}}); //Prompt
  sh.AddHistos("prepho", {.fill="MRR2NoPhoBins_vs_PhotonSIEIE", .pfs={"Data_MC","SelectNoIsoPhoton","EB_EE",cut+"_Excl1Pho"}, .cuts={}, .draw=d, .opt={}, .ranges={}}); //Target

  sh.AddHistos("prepho", {.fill="MRR2NoPhoBins_vs_PhotonSIEIE", .pfs={"Data_MC","FakePhoton","EB_EE",cut+"_Excl1Pho1M"}, .cuts={}, .draw=d, .opt={}, .ranges={}}); //Fake
  sh.AddHistos("prepho", {.fill="MRR2NoPhoBins_vs_PhotonSIEIE", .pfs={"Data_MC","PromptPhoton","EB_EE",cut+"_Excl1Pho1M"}, .cuts={}, .draw=d, .opt={}, .ranges={}}); //Prompt
  sh.AddHistos("prepho", {.fill="MRR2NoPhoBins_vs_PhotonSIEIE", .pfs={"Data_MC","SelectNoIsoPhoton","EB_EE",cut+"_Excl1Pho1M"}, .cuts={}, .draw=d, .opt={}, .ranges={}}); //Target

  //sh.AddHistos("prepho", {.fill="MRR2NoPho_vs_PhotonCHIso_preslectphoptREBin", .pfs={"Data_MC","FakePhoton","EB_EE",cut+"_Excl1Pho"}, .cuts={}, .draw=d, .opt={}, .ranges={}}); //Fake

  //sh.AddHistos("prepho", {.fill="MRR2NoPho_vs_PhotonCHIso_preslectphoptREBin", .pfs={"Data_MC","PromptPhoton","EB_EE",cut+"_Excl1Pho"}, .cuts={}, .draw=d, .opt={}, .ranges={}}); //Prompt

  //sh.AddHistos("prepho", {.fill="MRR2NoPho_vs_PhotonCHIso_preslectphoptREBin", .pfs={"Data_MC","SelectNoIsoPhoton","EB_EE",cut+"_Excl1Pho"}, .cuts={}, .draw=d, .opt={}, .ranges={}}); //Target

  //sh.AddHistos("prepho", {.fill="MRR2NoPhoBins_vs_PhotonCHIso_preslectphoptLN", .pfs={"Data_MC","1Fake","EB_EE",cut+"_Excl1Pho"}, .cuts={}, .draw=d, .opt={}, .ranges={}}); //Fake

  //sh.AddHistos("prepho", {.fill="MRR2NoPhoBins_vs_PhotonCHIso_preslectphoptLN", .pfs={"Data_MC","EB_EE","PromptDirect","SIEIE",cut+"_Excl1Pho"}, .cuts={}, .draw=d, .opt={}, .ranges={}}); //Prompt

  //sh.AddHistos("prepho", {.fill="MRR2NoPhoBins_vs_PhotonCHIso_preslectphoptLN", .pfs={"Data_MC","EB_EE","SIEIE",cut+"_Excl1Pho"}, .cuts={}, .draw=d, .opt={}, .ranges={}}); //Targe

    //sh.AddHistos("prepho", {.fill="MRR2NoPho_vs_PhotonCHIso_preslectphoptREBin", .pfs={"Data_MC", "EB_EE" , "SIEIE", "Year", cut+"_Excl1Pho"}, .cuts={}, .draw="PE1",.opt=o_1or2d_d+"AddRatio", .ranges={}}); 

    //sh.AddHistos("prepho", {.fill="MRR2NoPho_vs_PhotonCHIso_preslectphoptLog", .pfs={"Data_MC", "EB_EE" , "SIEIE", "Year", cut+"_Excl1Pho"}, .cuts={}, .draw="PE1",.opt=o_1or2d_d+"AddRatio", .ranges={}});

    //sh.AddHistos("prepho", {.fill="MRR2NoPho_vs_PhotonCHIso_preslectphoptLN", .pfs={"Data_MC", "EB_EE" , "SIEIE", "Year", cut+"_Excl1Pho"}, .cuts={}, .draw="PE1",.opt=o_1or2d_d+"AddRatio", .ranges={}});

    //sh.AddHistos(s+"prepho", {.fill="MRR2NoPho_vs_PhotonCHIso_preslectphoptLog", .pfs={"Data_MC", "SIEIE", "EE", "Year", cut}, .cuts={}, .draw=d, .opt={}, .ranges={}});

    //sh.AddHistos(s+"prepho", {.fill="MRR2NoPho_vs_PhotonCHIso_phopt", .pfs={"Data_MC", "SIEIE", "EB", "Year", cut}, .cuts={}, .draw=d, .opt={}, .ranges={}});
    //sh.AddHistos(s+"prepho", {.fill="MRR2NoPho_vs_PhotonCHIso_phopt", .pfs={"Data_MC", "SIEIE", "EE", "Year", cut}, .cuts={}, .draw=d, .opt={}, .ranges={}});
    // MR vs CHiso
    //sh.AddHistos(s+"prepho", {.fill="MRNoPhoBins_vs_PhotonCHIso", .pfs={"Data_MC", "SIEIE", "EB", "Year", cut}, .cuts={}, .draw=d, .opt={}, .ranges={}});
    //sh.AddHistos(s+"prepho", {.fill="MRNoPhoBins_vs_PhotonCHIso", .pfs={"Data_MC", "SIEIE", "EE", "Year", cut}, .cuts={}, .draw=d, .opt={}, .ranges={}});    
   
    //R2 vs Chiso
    //sh.AddHistos(s+"prepho", {.fill="R2NoPhoBins_vs_PhotonCHIso", .pfs={"Data_MC", "SIEIE", "EB", "Year", cut}, .cuts={}, .draw=d, .opt={}, .ranges={}});
    //sh.AddHistos(s+"prepho", {.fill="R2NoPhoBins_vs_PhotonCHIso", .pfs={"Data_MC", "SIEIE", "EE", "Year", cut}, .cuts={}, .draw=d, .opt={}, .ranges={}});

    // CHIso distribution
    //sh.AddHistos(s+"prepho", {.fill=c+"PhotonCHIso", .pfs={"Data_MC", "Year", "EB_EE",cut}, .cuts={}, .draw="PE1", .opt={}, .ranges={}});

    // Data Photon Truth - Direct Prompt Photon or Diret Fragmentation Photon
    //sh.AddHistos(s+"prepho", {.fill=c+"MRR2NoPho", .pfs={"StackPlot", "Data_PhotonTruth", "Year", cut}, .cuts={}, .draw="HIST", .opt={}, .ranges={}});
    //sh.AddHistos(s+"prepho", {.fill=c+"MRR2", .pfs={"Data_MC", "Year", "EB", cut}, .cuts={}, .draw="HIST", .opt={}, .ranges={}});
    //sh.AddHistos(s+"prepho", {.fill=c+"MRR2", .pfs={"Data_MC", "Year", "EE", cut}, .cuts={}, .draw="HIST", .opt={}, .ranges={}});
    //sh.AddHistos(s+"prepho", {.fill=c+"MRR2", .pfs={"Data_MC", "EB", "PromptDirect", cut}, .cuts={}, .draw="HIST", .opt={}, .ranges={}});
    //sh.AddHistos(s+"prepho", {.fill=c+"MRR2", .pfs={"Data_MC", "EE", "PromptDirect", cut}, .cuts={}, .draw="HIST", .opt={}, .ranges={}});

    //sh.AddHistos(s+"prepho",      { .fill="DirectFraction_vs_NJetNoPho",        .pfs={"Background","Prompt", "EB_EE", "Year",cut}, .cuts={},.draw=d,.opt=o_1or2d_s,.ranges={0,0, 0,1, 0.4,0.5}}); 
    //sh.AddHistos(s+"prepho",      { .fill="DirectFraction_vs_NJetNoPho",        .pfs={"Background","Prompt", "EE", "Year", cut}, .cuts={},.draw=d,.opt=o_1or2d_s,.ranges={0,0, 0,1, 0.4,0.5}});
	
    //sh.AddHistos(s+"prepho",      { .fill="DirectFraction_vs_MRR2NoPhoBins",        .pfs={"Background","Prompt", "EB_EE", "Year",cut}, .cuts={},.draw=d,.opt=o_1or2d_s,.ranges={0,0, 0,1, 0.4,0.5}});	
    //sh.AddHistos(s+"prepho",      { .fill="DirectFraction_vs_MRR2NoPho",        .pfs={"Background","Prompt", "EE", "Year",cut}, .cuts={},.draw=d,.opt=o_1or2d_s,.ranges={0,0, 0,1, 0.4,0.5}});

    //sh.AddHistos("prepho", {.fill=c+"MRR2NoPhoBins", .pfs={"StackPlot", "Year", cut}, .cuts={}, .draw=d, .opt={}, .ranges=r_Stk6});
    //sh.AddHistos("prepho", {.fill=c+"MRR2NoPhoBins", .pfs={"StackPlot", "Year", "EB_EE"}, .cuts={}, .draw=d, .opt={}, .ranges=r_Stk6});
    
    //sh.AddHistos(s+"prepho", {.fill="MRR2NoPho_vs_PhotonCHIso_preslectphopt", .pfs={"Data_MC", "Year", cut}, .cuts={}, .draw="HIST", .opt={}, .ranges={}});
    //sh.AddHistos(s+"prepho", {.fill="MRR2NoPho_vs_PhotonCHIso_preslectphopt", .pfs={"Data_MC", "Year", "EB_EE", cut}, .cuts={}, .draw="HIST", .opt={}, .ranges={}});    	
    //sh.AddHistos(s+"prepho", {.fill="MRR2NoPho_vs_PhotonCHIso_preslectphoptLN", .pfs={"Data_MC", "Year", cut}, .cuts={}, .draw="HIST", .opt={}, .ranges={}});
    //sh.AddHistos(s+"prepho", {.fill="MRR2NoPho_vs_PhotonCHIso_preslectphoptLN", .pfs={"Data_MC", "Year", "EB_EE", cut}, .cuts={}, .draw="HIST", .opt={}, .ranges={}}); 
   
    //sh.AddHistos("prepho", {.fill=c+"MRR2NoPhoBins", .pfs={"StackPlot", "Year", cut+"_Excl1Pho"}, .cuts={}, .draw=d, .opt={}, .ranges=r_Stk6});
    //sh.AddHistos("prepho", {.fill=c+"MRR2NoPhoBins", .pfs={"StackPlot", "Year", "EB_EE", cut+"_Excl1Pho"}, .cuts={}, .draw=d, .opt={}, .ranges=r_Stk6});
    //sh.AddHistos("prepho", {.fill=c+"PhotonCHIso_preslectphopt", .pfs={"StackPlot", "Year", cut+"_Excl1Pho"}, .cuts={}, .draw=d, .opt=opt, .ranges=r_Stk6});
    //sh.AddHistos("prepho", {.fill=c+"PhotonCHIso_preslectphopt", .pfs={"StackPlot", "Year", "EB_EE", cut+"_Excl1Pho"}, .cuts={}, .draw=d, .opt=opt, .ranges=r_Stk6});
    //
    //sh.AddHistos("prepho", {.fill=c+"PhotonCHIso_preslectphoptREBin", .pfs={"StackPlot", "Year", cut+"_Excl1Pho"}, .cuts={}, .draw=d, .opt=opt, .ranges=r_Stk6});
    //sh.AddHistos("prepho", {.fill=c+"PhotonCHIso_preslectphoptREBin", .pfs={"StackPlot", "Year", "MRR2Pho150", cut+"_Excl1Pho"}, .cuts={}, .draw=d, .opt=opt, .ranges=r_Stk6});
    //sh.AddHistos("prepho", {.fill=c+"PhotonCHIso_preslectphoptREBin", .pfs={"StackPlot", "Year", "MRR2Pho200", cut+"_Excl1Pho"}, .cuts={}, .draw=d, .opt=opt, .ranges=r_Stk6});
    //sh.AddHistos("prepho", {.fill=c+"PhotonCHIso_preslectphoptREBin", .pfs={"StackPlot", "Year", "MRR2Pho250", cut+"_Excl1Pho"}, .cuts={}, .draw=d, .opt=opt, .ranges=r_Stk6});
    //sh.AddHistos("prepho", {.fill=c+"PhotonCHIso_preslectphoptREBin", .pfs={"StackPlot", "Year", "MRR2Pho300", cut+"_Excl1Pho"}, .cuts={}, .draw=d, .opt=opt, .ranges=r_Stk6});
    //sh.AddHistos("prepho", {.fill=c+"PhotonCHIso_preslectphoptREBin", .pfs={"StackPlot", "Year", "MRR2Pho3000", cut+"_Excl1Pho"}, .cuts={}, .draw=d, .opt=opt, .ranges=r_Stk6});

    //sh.AddHistos("prepho", {.fill=c+"PhotonCHIso_preslectphoptREBin", .pfs={"StackPlot", "Year", "EB_EE", cut+"_Excl1Pho"}, .cuts={}, .draw=d, .opt=opt, .ranges=r_Stk6});
    //sh.AddHistos("prepho", {.fill=c+"PhotonCHIso_preslectphoptREBin", .pfs={"StackPlot", "Year", "MRR2Pho150", "EB_EE", cut+"_Excl1Pho"}, .cuts={}, .draw=d, .opt=opt, .ranges=r_Stk6});
    //sh.AddHistos("prepho", {.fill=c+"PhotonCHIso_preslectphoptREBin", .pfs={"StackPlot", "Year", "MRR2Pho200", "EB_EE", cut+"_Excl1Pho"}, .cuts={}, .draw=d, .opt=opt, .ranges=r_Stk6});
    //sh.AddHistos("prepho", {.fill=c+"PhotonCHIso_preslectphoptREBin", .pfs={"StackPlot", "Year", "MRR2Pho250", "EB_EE", cut+"_Excl1Pho"}, .cuts={}, .draw=d, .opt=opt, .ranges=r_Stk6});
    //sh.AddHistos("prepho", {.fill=c+"PhotonCHIso_preslectphoptREBin", .pfs={"StackPlot", "Year", "MRR2Pho300", "EB_EE", cut+"_Excl1Pho"}, .cuts={}, .draw=d, .opt=opt, .ranges=r_Stk6});
    //sh.AddHistos("prepho", {.fill=c+"PhotonCHIso_preslectphoptREBin", .pfs={"StackPlot", "Year", "MRR2Pho3000", "EB_EE", cut+"_Excl1Pho"}, .cuts={}, .draw=d, .opt=opt, .ranges=r_Stk6});
    //

    sh.AddHistos(s+"prepho", {.fill=c+"MRR2NoPhoBins", .pfs={"Data", "run2", "EB_EE", cut}, .cuts={}, .draw=d, .opt={}, .ranges={}});
    sh.AddHistos(s+"prepho", {.fill=c+"MRR2NoPhoBins", .pfs={"Data", "run2", cut}, .cuts={}, .draw=d, .opt={}, .ranges={}});
    sh.AddHistos(s+"prepho", {.fill=c+"MRR2NoPhoBins", .pfs={"StackPlot", "run2", cut}, .cuts={}, .draw=d, .opt={}, .ranges=r_Stk6});
    //sh.AddHistos(s+"prepho", {.fill=c+"NJetNoPhoBins", .pfs={"Data", "Year", "EB_EE", cut}, .cuts={}, .draw=d, .opt={}, .ranges={}});
    //sh.AddHistos(s+"prepho", {.fill=c+"NJetNoPhoBins", .pfs={"Data", "Year", cut}, .cuts={}, .draw=d, .opt={}, .ranges={}});
    //sh.AddHistos(s+"prepho", {.fill=c+"NJetNoPhoBins", .pfs={"StackPlot", "Year", cut}, .cuts={}, .draw=d, .opt={}, .ranges=r_Stk6});
    //sh.AddHistos(s+"prepho", {.fill=c+"1or2Boost", .pfs={"Data", "Year", "EB_EE", cut}, .cuts={}, .draw=d, .opt={}, .ranges={}});
    //sh.AddHistos(s+"prepho", {.fill=c+"1or2Boost", .pfs={"Data", "Year", cut}, .cuts={}, .draw=d, .opt={}, .ranges={}});
    //sh.AddHistos(s+"prepho", {.fill=c+"1or2Boost", .pfs={"StackPlot", "Year", cut}, .cuts={}, .draw=d, .opt={}, .ranges=r_Stk6});


  }
}

#endif // End header guard
