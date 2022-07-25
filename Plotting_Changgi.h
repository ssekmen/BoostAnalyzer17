// Implementation of Plotting class defined in PlottingBase.h
#ifndef PLOTTING_H
#define PLOTTING_H
#include "include/Analysis.h"

//_______________________________________________________
//                  Calculate variables


//_______________________________________________________
//      Define Histo options: Filling/Postfixes

void
Plotting::define_additional_histo_settings(const Weighting& w, EventSelections& evt_sel,
                                           const unsigned int& syst_nSyst, const unsigned int& syst_index)
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

  std::vector<std::string> standard_plots = {"HT", "HTFine", "METFine", "MET", "METFixEE2017", "PuppiMET", "RawMET", "HTMET", "MRFine", "MR", "R2Fine", "R2", "MRR2"};

  // -------------------------------------------------------------------------
  //                                   Trigger


  sh.SetHistoWeights({ [] { return 1; } });

/*
  // Hadronic triggers
  for (auto plot : {"HadronicMeasurements", "HadronicMeasurementsNoR2"}) {
    std::string cut = "Baseline";
    if (std::string(plot)=="HadronicMeasurementsNoR2") cut = "BaselineNoR2";
    for (auto trigger : std::vector<std::string>({
             "HLTEff_PFHT1050",
               "HLTEff_PFMET120_PFMHT120",
               "HLTEff_PFMETNoMu120_PFMHTNoMu120",
               "HLTEff_PFMETTypeOne120_PFMHT120",
               "HLTEff_PFHT500_PFMET100_PFMHT100",
               "HLTEff_PFHT700_PFMET85_PFMHT85",
               "HLTEff_PFHT800_PFMET75_PFMHT75",
               })) {
      for (auto std_plot : standard_plots)
        sh.AddHistos("evt", { .fill=trigger+"_vs_"+std_plot,             .pfs={                plot,"Year",cut}, .cuts={}, .draw="PE1",  .opt=o_1or2d_d+"TwoCol22", .ranges={0,0, 0,1, 0.5,0.35} });
      sh.AddHistos("evt", { .fill=trigger+"_vs_Bin",                     .pfs={                plot,"Year",cut}, .cuts={}, .draw="PE1",  .opt=o_1or2d_d+"TwoCol22", .ranges={0,0, 0,1, 0.5,0.35} });
      sh.AddHistos("evt", { .fill=trigger+"_vs_HT2DBins",                .pfs={                plot,"Year",cut}, .cuts={}, .draw="PE1",  .opt=o_1or2d_d+"TwoCol22", .ranges={0,0, 0,1, 0.5,0.35} });
      sh.AddHistos("evt", { .fill=trigger+"_vs_MET2DBins",               .pfs={                plot,"Year",cut}, .cuts={}, .draw="PE1",  .opt=o_1or2d_d+"TwoCol22", .ranges={0,0, 0,1, 0.5,0.35} });
      sh.AddHistos("evt", { .fill=trigger+"_vs_HTMET",                   .pfs={                plot,"Year",cut}, .cuts={}, .draw="PE1",  .opt=o_1or2d_d+"TwoCol22", .ranges={0,0, 0,1, 0.5,0.35} });
      sh.AddHistos("evt", { .fill=trigger+"_vs_HT1MET",                  .pfs={                plot,"Year",cut}, .cuts={}, .draw="PE1",  .opt=o_1or2d_d+"TwoCol22", .ranges={0,0, 0,1, 0.5,0.35} });
      sh.AddHistos("evt", { .fill=trigger+"_vs_HT2MET",                  .pfs={                plot,"Year",cut}, .cuts={}, .draw="PE1",  .opt=o_1or2d_d+"TwoCol22", .ranges={0,0, 0,1, 0.5,0.35} });
      sh.AddHistos("evt", { .fill=trigger+"_vs_HT3MET",                  .pfs={                plot,"Year",cut}, .cuts={}, .draw="PE1",  .opt=o_1or2d_d+"TwoCol22", .ranges={0,0, 0,1, 0.5,0.35} });
      sh.AddHistos("evt", { .fill=trigger+"_vs_HTMETPrev",               .pfs={                plot,"Year",cut}, .cuts={}, .draw="PE1",  .opt=o_1or2d_d+"TwoCol22", .ranges={0,0, 0,1, 0.5,0.35} });
    }
  }
  for (const auto& cut : {"Baseline"}) {
    for (auto plot : {"LeptonicMeasurements"}) {
      // Single lepton triggers
      for (auto std_plot : standard_plots)
        sh.AddHistos("evt", { .fill=std_plot,             .pfs={plot,"Year",cut},          .cuts={}, .draw="HIST", .opt=o_1or2d_d+"Log", .ranges={0,0, 1e-1,1e8, 0.35,0.86} });
      sh.AddHistos("evt", { .fill="HT2DBins",             .pfs={plot,"Year",cut},          .cuts={}, .draw="HIST", .opt=o_1or2d_d+"Log", .ranges={0,0, 1e-1,1e8, 0.35,0.86} });
      sh.AddHistos("evt", { .fill="RazorBinsLep",         .pfs={plot,"Year",cut},          .cuts={}, .draw="HIST", .opt=o_1or2d_d+"Log", .ranges={0,0, 1e-1,1e8, 0.35,0.86} });
      sh.AddHistos("evt", { .fill="EleNoIsoPt",           .pfs={plot,"Year",cut},          .cuts={}, .draw="HIST", .opt=o_1or2d_d+"Log", .ranges={0,0, 1e-1,1e8, 0.35,0.86} });
      sh.AddHistos("evt", { .fill="MuNoIsoPt",            .pfs={plot,"Year",cut},          .cuts={}, .draw="HIST", .opt=o_1or2d_d+"Log", .ranges={0,0, 1e-1,1e8, 0.35,0.86} });
      sh.AddHistos("evt", { .fill="EleNonIsoPt",          .pfs={plot,"Year",cut},          .cuts={}, .draw="HIST", .opt=o_1or2d_d+"Log", .ranges={0,0, 1e-1,1e8, 0.35,0.86} });
      sh.AddHistos("evt", { .fill="MuNonIsoPt",           .pfs={plot,"Year",cut},          .cuts={}, .draw="HIST", .opt=o_1or2d_d+"Log", .ranges={0,0, 1e-1,1e8, 0.35,0.86} });
      sh.AddHistos("evt", { .fill="HTElePt",              .pfs={plot,"Year",cut,"1Ele"},   .cuts={}, .draw="HIST", .opt=o_1or2d_d+"Log", .ranges={0,0, 1e-1,1e8, 0.35,0.86} });
      sh.AddHistos("evt", { .fill="HT1ElePt",             .pfs={plot,"Year",cut,"1Ele"},   .cuts={}, .draw="HIST", .opt=o_1or2d_d+"Log", .ranges={0,0, 1e-1,1e8, 0.35,0.86} });
      sh.AddHistos("evt", { .fill="HT2ElePt",             .pfs={plot,"Year",cut,"1Ele"},   .cuts={}, .draw="HIST", .opt=o_1or2d_d+"Log", .ranges={0,0, 1e-1,1e8, 0.35,0.86} });
      sh.AddHistos("evt", { .fill="HTMuPt",               .pfs={plot,"Year",cut,"1Muon"},  .cuts={}, .draw="HIST", .opt=o_1or2d_d+"Log", .ranges={0,0, 1e-1,1e8, 0.35,0.86} });
      sh.AddHistos("evt", { .fill="HT1MuPt",              .pfs={plot,"Year",cut,"1Muon"},  .cuts={}, .draw="HIST", .opt=o_1or2d_d+"Log", .ranges={0,0, 1e-1,1e8, 0.35,0.86} });
      sh.AddHistos("evt", { .fill="HT2MuPt",              .pfs={plot,"Year",cut,"1Muon"},  .cuts={}, .draw="HIST", .opt=o_1or2d_d+"Log", .ranges={0,0, 1e-1,1e8, 0.35,0.86} });
      for (auto ele_trigger : std::vector<std::string>({"HLTEff_Ele35", "HLTEff_Ele115", "HLTEff_Ele35_or_Ele115", "HLTEff_SingleEle"})) {
        for (auto std_plot : standard_plots)
          sh.AddHistos("evt", { .fill=ele_trigger+"_vs_"+std_plot,             .pfs={plot,"Year",cut,"1Ele"}, .cuts={}, .draw="PE1",  .opt=o_1or2d_d, .ranges={0,0, 0,0, 0.5,0.5} });
        sh.AddHistos("evt", { .fill=ele_trigger+"_vs_Bin",                     .pfs={plot,"Year",cut,"1Ele"}, .cuts={}, .draw="PE1",  .opt=o_1or2d_d, .ranges={0,0, 0,1, 0.5,0.5} });
        sh.AddHistos("evt", { .fill=ele_trigger+"_vs_RazorBinsLep",            .pfs={plot,"Year",cut,"1Ele"}, .cuts={}, .draw="PE1",  .opt=o_1or2d_d, .ranges={0,0, 0,1, 0.5,0.5} });
        sh.AddHistos("evt", { .fill=ele_trigger+"_vs_HT2DBins",                .pfs={plot,"Year",cut,"1Ele"}, .cuts={}, .draw="PE1",  .opt=o_1or2d_d, .ranges={0,0, 0,1, 0.5,0.53} });
        sh.AddHistos("evt", { .fill=ele_trigger+"_vs_ElePt",                   .pfs={plot,"Year",cut,"1Ele"}, .cuts={}, .draw="PE1",  .opt=o_1or2d_d, .ranges={0,0, 0,1, 0.5,0.53} });
        sh.AddHistos("evt", { .fill=ele_trigger+"_vs_HTElePt",                 .pfs={plot,"Year",cut,"1Ele"}, .cuts={}, .draw="PE1",  .opt=o_1or2d_d, .ranges={0,0, 0,1, 0.5,0.53} });
        sh.AddHistos("evt", { .fill=ele_trigger+"_vs_HT1ElePt",                .pfs={plot,"Year",cut,"1Ele"}, .cuts={}, .draw="PE1",  .opt=o_1or2d_d, .ranges={0,0, 0,1, 0.5,0.53} });
        sh.AddHistos("evt", { .fill=ele_trigger+"_vs_HT2ElePt",                .pfs={plot,"Year",cut,"1Ele"}, .cuts={}, .draw="PE1",  .opt=o_1or2d_d, .ranges={0,0, 0,1, 0.5,0.53} });
      }
      for (auto mu_trigger : std::vector<std::string>({"HLTEff_IsoMu27", "HLTEff_Mu50", "HLTEff_IsoMu27_or_Mu50", "HLTEff_SingleMu"})) {
        for (auto std_plot : standard_plots)
          sh.AddHistos("evt", { .fill=mu_trigger+"_vs_"+std_plot,             .pfs={plot,"Year",cut,"1Muon"}, .cuts={}, .draw="PE1",  .opt=o_1or2d_d, .ranges={0,0, 0,0, 0.5,0.5} });
        sh.AddHistos("evt", { .fill=mu_trigger+"_vs_Bin",                     .pfs={plot,"Year",cut,"1Muon"}, .cuts={}, .draw="PE1",  .opt=o_1or2d_d, .ranges={0,0, 0,1, 0.5,0.5} });
        sh.AddHistos("evt", { .fill=mu_trigger+"_vs_RazorBinsLep",            .pfs={plot,"Year",cut,"1Muon"}, .cuts={}, .draw="PE1",  .opt=o_1or2d_d, .ranges={0,0, 0,1, 0.5,0.5} });
        sh.AddHistos("evt", { .fill=mu_trigger+"_vs_HT2DBins",                .pfs={plot,"Year",cut,"1Muon"}, .cuts={}, .draw="PE1",  .opt=o_1or2d_d, .ranges={0,0, 0,1, 0.5,0.53} });
        sh.AddHistos("evt", { .fill=mu_trigger+"_vs_MuPt",                    .pfs={plot,"Year",cut,"1Muon"}, .cuts={}, .draw="PE1",  .opt=o_1or2d_d, .ranges={0,0, 0,1, 0.5,0.53} });
        sh.AddHistos("evt", { .fill=mu_trigger+"_vs_HTMuPt",                  .pfs={plot,"Year",cut,"1Muon"}, .cuts={}, .draw="PE1",  .opt=o_1or2d_d, .ranges={0,0, 0,1, 0.5,0.53} });
        sh.AddHistos("evt", { .fill=mu_trigger+"_vs_HT1MuPt",                 .pfs={plot,"Year",cut,"1Muon"}, .cuts={}, .draw="PE1",  .opt=o_1or2d_d, .ranges={0,0, 0,1, 0.5,0.53} });
        sh.AddHistos("evt", { .fill=mu_trigger+"_vs_HT2MuPt",                 .pfs={plot,"Year",cut,"1Muon"}, .cuts={}, .draw="PE1",  .opt=o_1or2d_d, .ranges={0,0, 0,1, 0.5,0.53} });
      }
      // Hadronic combinations
      for (auto std_plot : standard_plots)
        sh.AddHistos("evt", { .fill=std_plot,             .pfs={plot,"Year",cut},          .cuts={}, .draw="HIST", .opt=o_1or2d_d, .ranges={0,0, 0,0, 0.35,0.86} });
      sh.AddHistos("evt", { .fill="RazorBinsLep",         .pfs={plot,"Year",cut},          .cuts={}, .draw="HIST", .opt=o_1or2d_d, .ranges={0,0, 0,0, 0.35,0.86} });
      sh.AddHistos("evt", { .fill="HT2DBins",             .pfs={plot,"Year",cut},          .cuts={}, .draw="HIST", .opt=o_1or2d_d, .ranges={0,0, 0,0, 0.35,0.86} });
      sh.AddHistos("evt", { .fill="EleTightPt",           .pfs={plot,"Year",cut},          .cuts={}, .draw="HIST", .opt=o_1or2d_d, .ranges={0,0, 0,0, 0.35,0.86} });
      sh.AddHistos("evt", { .fill="HTElePt",              .pfs={plot,"Year",cut},          .cuts={}, .draw="HIST", .opt=o_1or2d_d, .ranges={0,0, 0,0, 0.35,0.86} });
      sh.AddHistos("evt", { .fill="MuTightPt",            .pfs={plot,"Year",cut},          .cuts={}, .draw="HIST", .opt=o_1or2d_d, .ranges={0,0, 0,0, 0.35,0.86} });
      sh.AddHistos("evt", { .fill="HTMuPt",               .pfs={plot,"Year",cut},          .cuts={}, .draw="HIST", .opt=o_1or2d_d, .ranges={0,0, 0,0, 0.35,0.86} });
      for (auto ele_trigger : std::vector<std::string>({"HLTEff_Ele15_HT450", "HLTEff_Ele35_or_Ele115_or_Ele15_HT450"})) {
        for (auto std_plot : standard_plots)
          sh.AddHistos("evt", { .fill=ele_trigger+"_vs_"+std_plot,             .pfs={plot,"Year",cut,"1Ele"}, .cuts={}, .draw="PE1",  .opt=o_1or2d_d, .ranges={0,0, 0,0, 0.5,0.5} });
        sh.AddHistos("evt", { .fill=ele_trigger+"_vs_Bin",                     .pfs={plot,"Year",cut,"1Ele"}, .cuts={}, .draw="PE1",  .opt=o_1or2d_d, .ranges={0,0, 0,1, 0.5,0.5} });
        sh.AddHistos("evt", { .fill=ele_trigger+"_vs_RazorBinsLep",            .pfs={plot,"Year",cut,"1Ele"}, .cuts={}, .draw="PE1",  .opt=o_1or2d_d, .ranges={0,0, 0,1, 0.5,0.5} });
        sh.AddHistos("evt", { .fill=ele_trigger+"_vs_HT2DBins",                .pfs={plot,"Year",cut,"1Ele"}, .cuts={}, .draw="PE1",  .opt=o_1or2d_d, .ranges={0,0, 0,1, 0.5,0.53} });
        sh.AddHistos("evt", { .fill=ele_trigger+"_vs_ElePt",                   .pfs={plot,"Year",cut,"1Ele"}, .cuts={}, .draw="PE1",  .opt=o_1or2d_d, .ranges={0,0, 0,1, 0.5,0.53} });
        sh.AddHistos("evt", { .fill=ele_trigger+"_vs_HTElePt",                 .pfs={plot,"Year",cut,"1Ele"}, .cuts={}, .draw="PE1",  .opt=o_1or2d_d, .ranges={0,0, 0,1, 0.5,0.53} });
      }
      for (auto mu_trigger : std::vector<std::string>({"HLTEff_Mu15_HT450", "HLTEff_IsoMu27_or_Mu50_or_Mu15_HT450"})) {
        for (auto std_plot : standard_plots)
          sh.AddHistos("evt", { .fill=mu_trigger+"_vs_"+std_plot,             .pfs={plot,"Year",cut,"1Muon"}, .cuts={}, .draw="PE1",  .opt=o_1or2d_d, .ranges={0,0, 0,0, 0.5,0.5} });
        sh.AddHistos("evt", { .fill=mu_trigger+"_vs_Bin",                     .pfs={plot,"Year",cut,"1Muon"}, .cuts={}, .draw="PE1",  .opt=o_1or2d_d, .ranges={0,0, 0,1, 0.5,0.5} });
        sh.AddHistos("evt", { .fill=mu_trigger+"_vs_RazorBinsLep",            .pfs={plot,"Year",cut,"1Muon"}, .cuts={}, .draw="PE1",  .opt=o_1or2d_d, .ranges={0,0, 0,1, 0.5,0.5} });
        sh.AddHistos("evt", { .fill=mu_trigger+"_vs_HT2DBins",                .pfs={plot,"Year",cut,"1Muon"}, .cuts={}, .draw="PE1",  .opt=o_1or2d_d, .ranges={0,0, 0,1, 0.5,0.53} });
        sh.AddHistos("evt", { .fill=mu_trigger+"_vs_MuPt",                    .pfs={plot,"Year",cut,"1Muon"}, .cuts={}, .draw="PE1",  .opt=o_1or2d_d, .ranges={0,0, 0,1, 0.5,0.53} });
        sh.AddHistos("evt", { .fill=mu_trigger+"_vs_HTMuPt",                  .pfs={plot,"Year",cut,"1Muon"}, .cuts={}, .draw="PE1",  .opt=o_1or2d_d, .ranges={0,0, 0,1, 0.5,0.53} });
      }
      // Single photon triggers
      for (auto std_plot : standard_plots)
        sh.AddHistos("evt", { .fill=std_plot,             .pfs={plot,"Year",cut,"1Pho"},          .cuts={}, .draw="HIST", .opt=o_1or2d_d+"Log", .ranges={0,0, 1e-1,1e8, 0.35,0.86} });
      sh.AddHistos("evt", { .fill="HT2DBins",             .pfs={plot,"Year",cut,"1Pho"},          .cuts={}, .draw="HIST", .opt=o_1or2d_d+"Log", .ranges={0,0, 1e-1,1e8, 0.35,0.86} });
      sh.AddHistos("evt", { .fill="PhotonPtBins",         .pfs={plot,"Year",cut,"1Pho"},          .cuts={}, .draw="HIST", .opt=o_1or2d_d+"Log", .ranges={0,0, 1e-1,1e8, 0.35,0.86} });
      sh.AddHistos("evt", { .fill="PhotonPtBins",         .pfs={plot,"Year",cut,"1Pho_EB_EE"},    .cuts={}, .draw="HIST", .opt=o_1or2d_d+"Log", .ranges={0,0, 1e-1,1e8, 0.35,0.86} });
      sh.AddHistos("evt", { .fill="PhotonEta",            .pfs={plot,"Year",cut,"1Pho"},          .cuts={}, .draw="HIST", .opt=o_1or2d_d+"Log", .ranges={0,0, 1e-1,1e8, 0.35,0.86} });
      for (auto ele_trigger : std::vector<std::string>({"HLTEff_SinglePho"})) {
        for (auto std_plot : standard_plots)
          sh.AddHistos("evt", { .fill=ele_trigger+"_vs_"+std_plot,             .pfs={plot,"Year",cut,"1Pho"}, .cuts={}, .draw="PE1",  .opt=o_1or2d_d, .ranges={0,0, 0,0, 0.5,0.5} });
        sh.AddHistos("evt", { .fill=ele_trigger+"_vs_Bin",                     .pfs={plot,"Year",cut,"1Pho"}, .cuts={}, .draw="PE1",  .opt=o_1or2d_d, .ranges={0,0, 0,1, 0.5,0.5} });
        sh.AddHistos("evt", { .fill=ele_trigger+"_vs_PhotonPtBins",            .pfs={plot,"Year",cut,"1Pho"}, .cuts={}, .draw="PE1",  .opt=o_1or2d_d, .ranges={0,0, 0,1, 0.5,0.5} });
        sh.AddHistos("evt", { .fill=ele_trigger+"_vs_PhotonPtBins",            .pfs={plot,"Year",cut,"1Pho_EB_EE"}, .cuts={}, .draw="PE1",  .opt=o_1or2d_d, .ranges={0,0, 0,1, 0.5,0.5} });
        sh.AddHistos("evt", { .fill=ele_trigger+"_vs_PhotonEta",               .pfs={plot,"Year",cut,"1Pho"}, .cuts={}, .draw="PE1",  .opt=o_1or2d_d, .ranges={0,0, 0,1, 0.5,0.5} });
        sh.AddHistos("evt", { .fill=ele_trigger+"_vs_HT2DBins",                .pfs={plot,"Year",cut,"1Pho"}, .cuts={}, .draw="PE1",  .opt=o_1or2d_d, .ranges={0,0, 0,1, 0.5,0.53} });
      }
    }
  }
  
  // ----------------------------------------------------------------------------------------------
  //                                    New preselection segions
  //-----------------------------------------------------------------------------------------------

  standard_plots = {"HT", "METFine", "MET", "METFixEE2017", "PuppiMET", "RawMET", "MRFine", "MR", "R2Fine", "R2", "MRR2", "RazorBins", "RazorBinsNew"};
  //standard_plots.push_back("HTFine");
  //standard_plots.push_back("HTMET");

  for (auto region : {Region::Pre_Had}) {
    sh.SetHistoWeights({ [&w,region] { return w.sf_weight[region]; } });
    std::string cut(magic_enum::enum_name(region));
    // Signal discriminators
    sh.AddHistos("evt",    { .fill="MRFine_vs_METFine",         .pfs={"Signals_Background","Year",cut},          .cuts={},.draw="COLZ",.opt=o_1or2d_s+"Log",.ranges={}});
    sh.AddHistos("evt",    { .fill="R2Fine_vs_METFine",         .pfs={"Signals_Background","Year",cut},          .cuts={},.draw="COLZ",.opt=o_1or2d_s+"Log",.ranges={}});
    sh.AddHistos("evt",    { .fill="R2Fine_vs_MRFine",          .pfs={"Signals_Background","Year",cut},          .cuts={},.draw="COLZ",.opt=o_1or2d_s+"Log",.ranges={}});
    sh.AddHistos("evt",    { .fill="MRFine_vs_HTFine",          .pfs={"Signals_Background","Year",cut},          .cuts={},.draw="COLZ",.opt=o_1or2d_s+"Log",.ranges={}});
    sh.AddHistos("evt",    { .fill="METFine_vs_HTFine",         .pfs={"Signals_Background","Year",cut},          .cuts={},.draw="COLZ",.opt=o_1or2d_s+"Log",.ranges={}});
    sh.AddHistos("evt",    { .fill="R2Fine_vs_MRFine",          .pfs={"Signals_Background","Year",cut},          .cuts={},.draw="COLZ",.opt=o_1or2d_s+"Log",.ranges={}});
    sh.AddHistos("evt",    { .fill="MTBoost_vs_METFine",        .pfs={"Signals_Background","Year",cut},          .cuts={},.draw="COLZ",.opt=o_1or2d_s+"Log",.ranges={}});
    sh.AddHistos("evt",    { .fill="MTBoost_vs_R2Fine",         .pfs={"Signals_Background","Year",cut},          .cuts={},.draw="COLZ",.opt=o_1or2d_s+"Log",.ranges={}});
    sh.AddHistos("evt",    { .fill="MTBoost_vs_MRFine",         .pfs={"Signals_Background","Year",cut},          .cuts={},.draw="COLZ",.opt=o_1or2d_s+"Log",.ranges={}});
    // Boosted jet Index
    sh.AddHistos("hadw",       { .fill="JetAK8Index_vs_HadWIndex",                  .pfs={"Signals_Background","Year",cut,"MatchGenHadW"},   .cuts={},.draw="COLZ",.opt=o_1or2d_s+"Log",.ranges={}});
    sh.AddHistos("hadz",       { .fill="JetAK8Index_vs_HadZIndex",                  .pfs={"Signals_Background","Year",cut,"MatchGenHadZ"},   .cuts={},.draw="COLZ",.opt=o_1or2d_s+"Log",.ranges={}});
    sh.AddHistos("hadtop",     { .fill="JetAK8Index_vs_HadTopIndex",                .pfs={"Signals_Background","Year",cut,"MatchGenHadTop"}, .cuts={},.draw="COLZ",.opt=o_1or2d_s+"Log",.ranges={}});
    sh.AddHistos("leptop",     { .fill="JetAK8Index_vs_LepTopIndex",                .pfs={"Signals_Background","Year",cut,"MatchGenLepTop"}, .cuts={},.draw="COLZ",.opt=o_1or2d_s+"Log",.ranges={}});
    sh.AddHistos("gen hadw",   { .fill="GenMatchedAK8JetIndex_vs_NGenHadW",   .pfs={"Signals_Background","Year",cut}, .cuts={},.draw="COLZ",.opt=o_1or2d_s+"Log",.ranges={}});
    sh.AddHistos("gen hadz",   { .fill="GenMatchedAK8JetIndex_vs_NGenHadZ",   .pfs={"Signals_Background","Year",cut}, .cuts={},.draw="COLZ",.opt=o_1or2d_s+"Log",.ranges={}});
    sh.AddHistos("gen hadtop", { .fill="GenMatchedAK8JetIndex_vs_NGenHadTop", .pfs={"Signals_Background","Year",cut}, .cuts={},.draw="COLZ",.opt=o_1or2d_s+"Log",.ranges={}});
    sh.AddHistos("gen leptop", { .fill="GenMatchedAK8JetIndex_vs_NGenLepTop", .pfs={"Signals_Background","Year",cut}, .cuts={},.draw="COLZ",.opt=o_1or2d_s+"Log",.ranges={}});
    // MGlunio/MSquark plots
    sh.AddHistos("evt",  { .fill="HTFine",             .pfs={"MGluinoPoints",  "MLSPPoints","GluinoSignalScans",  cut}, .cuts={},.draw=d,.opt=o_norm_s,.ranges={}});
    sh.AddHistos("evt",  { .fill="METFine",            .pfs={"MGluinoPoints",  "MLSPPoints","GluinoSignalScans",  cut}, .cuts={},.draw=d,.opt=o_norm_s,.ranges={}});
    sh.AddHistos("evt",  { .fill="R2Fine",             .pfs={"MGluinoPoints",  "MLSPPoints","GluinoSignalScans",  cut}, .cuts={},.draw=d,.opt=o_norm_s,.ranges={}});
    sh.AddHistos("evt",  { .fill="MRFine",             .pfs={"MGluinoPoints",  "MLSPPoints","GluinoSignalScans",  cut}, .cuts={},.draw=d,.opt=o_norm_s,.ranges={}});
    sh.AddHistos("evt",  { .fill="RazorBins",          .pfs={"MGluinoPoints",  "MLSPPoints","GluinoSignalScans",  cut}, .cuts={},.draw=d,.opt=o_norm_s,.ranges={}});
    sh.AddHistos("evt",  { .fill="MRR2",               .pfs={"MGluinoPoints",  "MLSPPoints","GluinoSignalScans",  cut}, .cuts={},.draw=d,.opt=o_norm_s,.ranges={}});
    sh.AddHistos("evt",  { .fill="HTFine",             .pfs={"MSquarkPoints",    "MLSPPoints","SquarkSignalScans",    cut}, .cuts={},.draw=d,.opt=o_norm_s,.ranges={}});
    sh.AddHistos("evt",  { .fill="METFine",            .pfs={"MSquarkPoints",    "MLSPPoints","SquarkSignalScans",    cut}, .cuts={},.draw=d,.opt=o_norm_s,.ranges={}});
    sh.AddHistos("evt",  { .fill="R2Fine",             .pfs={"MSquarkPoints",    "MLSPPoints","SquarkSignalScans",    cut}, .cuts={},.draw=d,.opt=o_norm_s,.ranges={}});
    sh.AddHistos("evt",  { .fill="MRFine",             .pfs={"MSquarkPoints",    "MLSPPoints","SquarkSignalScans",    cut}, .cuts={},.draw=d,.opt=o_norm_s,.ranges={}});
    sh.AddHistos("evt",  { .fill="RazorBins",          .pfs={"MSquarkPoints",    "MLSPPoints","SquarkSignalScans",    cut}, .cuts={},.draw=d,.opt=o_norm_s,.ranges={}});
    sh.AddHistos("evt",  { .fill="MRR2",               .pfs={"MSquarkPoints",    "MLSPPoints","SquarkSignalScans",    cut}, .cuts={},.draw=d,.opt=o_norm_s,.ranges={}});
    sh.AddHistos("evt",  { .fill="MRR2",               .pfs={"MEWKPoints","MLSPPoints","EWKSignalScans",cut}, .cuts={},.draw=d,.opt=o_norm_s,.ranges={}});
    sh.AddHistos("evt",  { .fill="HTFine",             .pfs={"MEWKPoints","MLSPPoints","EWKSignalScans",cut}, .cuts={},.draw=d,.opt=o_norm_s,.ranges={}});
    sh.AddHistos("evt",  { .fill="METFine",            .pfs={"MEWKPoints","MLSPPoints","EWKSignalScans",cut}, .cuts={},.draw=d,.opt=o_norm_s,.ranges={}});
    sh.AddHistos("evt",  { .fill="R2Fine",             .pfs={"MEWKPoints","MLSPPoints","EWKSignalScans",cut}, .cuts={},.draw=d,.opt=o_norm_s,.ranges={}});
    sh.AddHistos("evt",  { .fill="MRFine",             .pfs={"MEWKPoints","MLSPPoints","EWKSignalScans",cut}, .cuts={},.draw=d,.opt=o_norm_s,.ranges={}});
    sh.AddHistos("evt",  { .fill="RazorBins",          .pfs={"MEWKPoints","MLSPPoints","EWKSignalScans",cut}, .cuts={},.draw=d,.opt=o_norm_s,.ranges={}});
    // Stack plots
    std::string opt  = o_stk_d_S;
    for (auto nobj_bin : {"NJet45",
             "NW1", "NW2", "NW3", 
             //"NTop1", "NTop2", "NTop3", "NTop4", "NTop5", 
             //"NWDeepMD1", "NWDeepMD2", "NWDeepMD3", 
             //"NZDeepMD1", "NZDeepMD2", "NZDeepMD3",
             "NTopDeepMD1", "NTopDeepMD2", "NTopDeepMD3", "NTopDeepMD4",
             "NWDeep1",   "NWDeep2",   "NWDeep3", 
             "NZDeep1",   "NZDeep2",   "NZDeep3", 
             "NVDeep1",   "NVDeep2",   "NVDeep3",
             "NTopDeep1",   "NTopDeep2",   "NTopDeep3", "NTopDeep4"}) {
      std::string signal = "StackPlotTopSignal";
      opt  = o_stk_d_T;
      std::string bveto = "Nisob";
      if (TString(nobj_bin).Contains("NZ")||TString(nobj_bin).Contains("NV")) {
        signal = "StackPlotVSignal";
        opt  = o_stk_d_V;
        bveto = "Nisob_NJet24";
      }
      for (auto std_plot : standard_plots) {
        sh.AddHistos(s+"evt", { .fill=c+std_plot,                  .pfs={signal,"Year",cut,nobj_bin},         .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
        //sh.AddHistos(s+"evt", { .fill=c+std_plot,                  .pfs={signal,"Year",cut,nobj_bin,"Nb"},    .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
        //sh.AddHistos(s+"evt", { .fill=c+std_plot,                  .pfs={signal,"Year",cut,nobj_bin,bveto},   .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
        //sh.AddHistos(s+"evt", { .fill=c+std_plot,                  .pfs={signal,"Year",cut,nobj_bin,"2b"},    .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
        //sh.AddHistos(s+"evt", { .fill=c+std_plot,                  .pfs={signal,"Year",cut,nobj_bin,"MTBoost800"},    .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
      }
      if (nobj_bin != std::string("NJet45")) {
        sh.AddHistos(s+"evt", { .fill=c+"NJet",                    .pfs={signal,"Year",cut,nobj_bin},         .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
        //sh.AddHistos(s+"evt", { .fill=c+"NJet",                    .pfs={signal,"Year",cut,nobj_bin,"Nb"},    .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
        //sh.AddHistos(s+"evt", { .fill=c+"NJet",                    .pfs={signal,"Year",cut,nobj_bin,bveto},   .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
        //sh.AddHistos(s+"evt", { .fill=c+"NJet",                    .pfs={signal,"Year",cut,nobj_bin,"2b"},    .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
        //sh.AddHistos(s+"evt", { .fill=c+"NJet",                    .pfs={signal,"Year",cut,nobj_bin,"MTBoost800"},    .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
      }
      sh.AddHistos(  s+"evt", { .fill=c+"DeltaPhi",                .pfs={signal,"Year",cut+"_ExcldPhi",nobj_bin},      .cuts={},.draw=d,.opt=opt,.ranges=r_Stk9});
      // MTBoost
      sh.AddHistos(  s+"evt", { .fill=c+"MTBoost",                 .pfs={signal,"Year",cut,nobj_bin},                 .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
      //sh.AddHistos(  s+"evt", { .fill=c+"MTBoost",                 .pfs={signal,"Year",cut,nobj_bin,"Nb"},            .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
      //sh.AddHistos(  s+"evt", { .fill=c+"MTBoost",                 .pfs={signal,"Year",cut,nobj_bin,bveto},           .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
      //sh.AddHistos(  s+"evt", { .fill=c+"MTBoost",                 .pfs={signal,"Year",cut,nobj_bin,"2b"},            .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
    }
    // Exclusive W combinations
    //for (std::string nobj_bin : {"Nb", "Nisob", "2b", "NHadTop", "NTopDeepMD1", "NTopDeepMD2", "NTopDeep1", "NTopDeep2"}) {
    //  for (std::string nw_bin : {"NHadW"}) {
    //    opt  = o_stk_d_T;
    //    for (auto std_plot : standard_plots)
    //      sh.AddHistos(s+"evt", { .fill=c+std_plot,                .pfs={"StackPlotTopSignal","Year",cut,nobj_bin,nw_bin},  .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
    //    sh.AddHistos(s+"evt", { .fill=c+"NJet",                    .pfs={"StackPlotTopSignal","Year",cut,nobj_bin,nw_bin},  .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
    //    sh.AddHistos(s+"evt", { .fill=c+"MTBoost",                 .pfs={"StackPlotTopSignal","Year",cut,nobj_bin,nw_bin},  .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
    //    sh.AddHistos(s+"evt", { .fill=c+"DeltaPhi",                .pfs={"StackPlotTopSignal","Year",cut+"_ExcldPhi",nobj_bin,nw_bin}, .cuts={},.draw=d,.opt=opt,.ranges=r_Stk9});
    //  }
    //}
  }

  
  for (auto region : {Region::Pre_NonIso}) {
    sh.SetHistoWeights({ [&w,region] { return w.sf_weight[region]; } });
    std::string cut(magic_enum::enum_name(region));
    // Leptons
    sh.AddHistos("evt",    { .fill="NLepNoIso_vs_NGenLepFromTop", .pfs={"Signals_Background","Year",cut+"_Excl1LepMTdPhiJet"}, .cuts={},.draw="COLZ",.opt=o_1or2d_s+"Log",.ranges={}});
    sh.AddHistos("evt",    { .fill="NEleNoIso_vs_NGenEleFromTop", .pfs={"Signals_Background","Year",cut+"_Excl1LepMTdPhiJet"}, .cuts={},.draw="COLZ",.opt=o_1or2d_s+"Log",.ranges={}});
    sh.AddHistos("evt",    { .fill="NMuNoIso_vs_NGenMuFromTop",   .pfs={"Signals_Background","Year",cut+"_Excl1LepMTdPhiJet"}, .cuts={},.draw="COLZ",.opt=o_1or2d_s+"Log",.ranges={}});
    sh.AddHistos("evt",    { .fill="NLepNonIso_vs_NGenLepFromTop",     .pfs={"Signals_Background","Year",cut+"_Excl1LepMTdPhiJet"}, .cuts={},.draw="COLZ",.opt=o_1or2d_s+"Log",.ranges={}});
    sh.AddHistos("evt",    { .fill="NEleNonIso_vs_NGenEleFromTop",     .pfs={"Signals_Background","Year",cut+"_Excl1LepMTdPhiJet"}, .cuts={},.draw="COLZ",.opt=o_1or2d_s+"Log",.ranges={}});
    sh.AddHistos("evt",    { .fill="NMuNonIso_vs_NGenMuFromTop",       .pfs={"Signals_Background","Year",cut+"_Excl1LepMTdPhiJet"}, .cuts={},.draw="COLZ",.opt=o_1or2d_s+"Log",.ranges={}});
    // Boosted jet Index
    sh.AddHistos("hadw",       { .fill="JetAK8Index_vs_HadWIndex",                  .pfs={"Signals_Background","Year",cut,"MatchGenHadW"},   .cuts={},.draw="COLZ",.opt=o_1or2d_s+"Log",.ranges={}});
    sh.AddHistos("hadz",       { .fill="JetAK8Index_vs_HadZIndex",                  .pfs={"Signals_Background","Year",cut,"MatchGenHadZ"},   .cuts={},.draw="COLZ",.opt=o_1or2d_s+"Log",.ranges={}});
    sh.AddHistos("hadtop",     { .fill="JetAK8Index_vs_HadTopIndex",                .pfs={"Signals_Background","Year",cut,"MatchGenHadTop"}, .cuts={},.draw="COLZ",.opt=o_1or2d_s+"Log",.ranges={}});
    sh.AddHistos("leptop",     { .fill="JetAK8Index_vs_LepTopIndex",                .pfs={"Signals_Background","Year",cut,"MatchedGenLeptonMother"}, .cuts={},.draw="COLZ",.opt=o_1or2d_s+"Log",.ranges={}});
    sh.AddHistos("gen hadw",   { .fill="GenMatchedAK8JetIndex_vs_NGenHadW",   .pfs={"Signals_Background","Year",cut}, .cuts={},.draw="COLZ",.opt=o_1or2d_s+"Log",.ranges={}});
    sh.AddHistos("gen hadz",   { .fill="GenMatchedAK8JetIndex_vs_NGenHadZ",   .pfs={"Signals_Background","Year",cut}, .cuts={},.draw="COLZ",.opt=o_1or2d_s+"Log",.ranges={}});
    sh.AddHistos("gen hadtop", { .fill="GenMatchedAK8JetIndex_vs_NGenHadTop", .pfs={"Signals_Background","Year",cut}, .cuts={},.draw="COLZ",.opt=o_1or2d_s+"Log",.ranges={}});
    sh.AddHistos("gen leptop", { .fill="GenMatchedAK8JetIndex_vs_NGenLepTop", .pfs={"Signals_Background","Year",cut}, .cuts={},.draw="COLZ",.opt=o_1or2d_s+"Log",.ranges={}});
    // Signal discriminators (2D)
    sh.AddHistos("evt",    { .fill="MRFine_vs_METFine",         .pfs={"Signals_Background","Year",cut},          .cuts={},.draw="COLZ",.opt=o_1or2d_s+"Log",.ranges={}});
    sh.AddHistos("evt",    { .fill="R2Fine_vs_METFine",         .pfs={"Signals_Background","Year",cut},          .cuts={},.draw="COLZ",.opt=o_1or2d_s+"Log",.ranges={}});
    sh.AddHistos("evt",    { .fill="R2Fine_vs_MRFine",          .pfs={"Signals_Background","Year",cut},          .cuts={},.draw="COLZ",.opt=o_1or2d_s+"Log",.ranges={}});
    sh.AddHistos("evt",    { .fill="MRFine_vs_HTFine",          .pfs={"Signals_Background","Year",cut},          .cuts={},.draw="COLZ",.opt=o_1or2d_s+"Log",.ranges={}});
    sh.AddHistos("evt",    { .fill="METFine_vs_HTFine",         .pfs={"Signals_Background","Year",cut},          .cuts={},.draw="COLZ",.opt=o_1or2d_s+"Log",.ranges={}});
    sh.AddHistos("evt",    { .fill="R2Fine_vs_MRFine",          .pfs={"Signals_Background","Year",cut},          .cuts={},.draw="COLZ",.opt=o_1or2d_s+"Log",.ranges={}});
    sh.AddHistos("evt",    { .fill="MTBoost_vs_MTNonIso",       .pfs={"Signals_Background","Year",cut},          .cuts={},.draw="COLZ",.opt=o_1or2d_s+"Log",.ranges={}});
    sh.AddHistos("evt",    { .fill="MTBoost_vs_MTNonIso",       .pfs={"Signals_Background","Year",cut+"_ExclMT"},.cuts={},.draw="COLZ",.opt=o_1or2d_s+"Log",.ranges={}});
    sh.AddHistos("evt",    { .fill="MTBoost_vs_METFine",        .pfs={"Signals_Background","Year",cut},          .cuts={},.draw="COLZ",.opt=o_1or2d_s+"Log",.ranges={}});
    sh.AddHistos("evt",    { .fill="MTBoost_vs_R2Fine",         .pfs={"Signals_Background","Year",cut},          .cuts={},.draw="COLZ",.opt=o_1or2d_s+"Log",.ranges={}});
    sh.AddHistos("evt",    { .fill="MTBoost_vs_MRFine",         .pfs={"Signals_Background","Year",cut},          .cuts={},.draw="COLZ",.opt=o_1or2d_s+"Log",.ranges={}});
    // MGlunio/MSquark plots
    sh.AddHistos("evt",  { .fill="HTFine",             .pfs={"MGluinoPoints",  "MLSPPoints","GluinoSignalScans",  cut}, .cuts={},.draw=d,.opt=o_norm_s,.ranges={}});
    sh.AddHistos("evt",  { .fill="METFine",            .pfs={"MGluinoPoints",  "MLSPPoints","GluinoSignalScans",  cut}, .cuts={},.draw=d,.opt=o_norm_s,.ranges={}});
    sh.AddHistos("evt",  { .fill="R2Fine",             .pfs={"MGluinoPoints",  "MLSPPoints","GluinoSignalScans",  cut}, .cuts={},.draw=d,.opt=o_norm_s,.ranges={}});
    sh.AddHistos("evt",  { .fill="MRFine",             .pfs={"MGluinoPoints",  "MLSPPoints","GluinoSignalScans",  cut}, .cuts={},.draw=d,.opt=o_norm_s,.ranges={}});
    sh.AddHistos("evt",  { .fill="RazorBinsLep",       .pfs={"MGluinoPoints",  "MLSPPoints","GluinoSignalScans",  cut}, .cuts={},.draw=d,.opt=o_norm_s,.ranges={}});
    sh.AddHistos("evt",  { .fill="MRR2",               .pfs={"MGluinoPoints",  "MLSPPoints","GluinoSignalScans",  cut}, .cuts={},.draw=d,.opt=o_norm_s,.ranges={}});
    sh.AddHistos("evt",  { .fill="HTFine",             .pfs={"MSquarkPoints",    "MLSPPoints","SquarkSignalScans",    cut}, .cuts={},.draw=d,.opt=o_norm_s,.ranges={}});
    sh.AddHistos("evt",  { .fill="METFine",            .pfs={"MSquarkPoints",    "MLSPPoints","SquarkSignalScans",    cut}, .cuts={},.draw=d,.opt=o_norm_s,.ranges={}});
    sh.AddHistos("evt",  { .fill="R2Fine",             .pfs={"MSquarkPoints",    "MLSPPoints","SquarkSignalScans",    cut}, .cuts={},.draw=d,.opt=o_norm_s,.ranges={}});
    sh.AddHistos("evt",  { .fill="MRFine",             .pfs={"MSquarkPoints",    "MLSPPoints","SquarkSignalScans",    cut}, .cuts={},.draw=d,.opt=o_norm_s,.ranges={}});
    sh.AddHistos("evt",  { .fill="RazorBinsLep",       .pfs={"MSquarkPoints",    "MLSPPoints","SquarkSignalScans",    cut}, .cuts={},.draw=d,.opt=o_norm_s,.ranges={}});
    sh.AddHistos("evt",  { .fill="MRR2",               .pfs={"MSquarkPoints",    "MLSPPoints","SquarkSignalScans",    cut}, .cuts={},.draw=d,.opt=o_norm_s,.ranges={}});
    sh.AddHistos("evt",  { .fill="MRR2",               .pfs={"MEWKPoints","MLSPPoints","EWKSignalScans",cut}, .cuts={},.draw=d,.opt=o_norm_s,.ranges={}});
    sh.AddHistos("evt",  { .fill="HTFine",             .pfs={"MEWKPoints","MLSPPoints","EWKSignalScans",cut}, .cuts={},.draw=d,.opt=o_norm_s,.ranges={}});
    sh.AddHistos("evt",  { .fill="METFine",            .pfs={"MEWKPoints","MLSPPoints","EWKSignalScans",cut}, .cuts={},.draw=d,.opt=o_norm_s,.ranges={}});
    sh.AddHistos("evt",  { .fill="R2Fine",             .pfs={"MEWKPoints","MLSPPoints","EWKSignalScans",cut}, .cuts={},.draw=d,.opt=o_norm_s,.ranges={}});
    sh.AddHistos("evt",  { .fill="MRFine",             .pfs={"MEWKPoints","MLSPPoints","EWKSignalScans",cut}, .cuts={},.draw=d,.opt=o_norm_s,.ranges={}});
    sh.AddHistos("evt",  { .fill="RazorBinsLep",       .pfs={"MEWKPoints","MLSPPoints","EWKSignalScans",cut}, .cuts={},.draw=d,.opt=o_norm_s,.ranges={}});
    // Stack plots
    std::string opt = o_stk_d_S;
    // Boosted leptonic jets
    sh.AddHistos(s+"AK8", { .fill=c+"LepJetPt",                        .pfs={"StackPlotSignal","Year",cut,"LepJetNoPt"},                    .cuts={},.draw=d,.opt=opt,.ranges=r_Stk5});
    sh.AddHistos(s+"AK8", { .fill=c+"LepJetPt",                        .pfs={"StackPlotSignal","Year",cut,"LepJetHighMass"},                .cuts={},.draw=d,.opt=opt,.ranges=r_Stk5});
    sh.AddHistos(s+"AK8", { .fill=c+"LepJetEta",                       .pfs={"StackPlotSignal","Year",cut,"LepJet"},                        .cuts={},.draw=d,.opt=opt,.ranges=r_Stk5});
    sh.AddHistos(s+"AK8", { .fill=c+"LepJetPhi",                       .pfs={"StackPlotSignal","Year",cut,"LepJet"},                        .cuts={},.draw=d,.opt=opt,.ranges=r_Stk5});
    sh.AddHistos(s+"AK8", { .fill=c+"LepJetMass",                      .pfs={"StackPlotSignal","Year",cut,"LepJetCand"},                    .cuts={},.draw=d,.opt=opt,.ranges=r_Stk5});
    sh.AddHistos(s+"AK8", { .fill=c+"LepJetSubJetDeepB",               .pfs={"StackPlotSignal","Year",cut,"LepTopNoSubJetB"},               .cuts={},.draw=d,.opt=opt,.ranges=r_Stk5});
    sh.AddHistos(s+"AK8", { .fill=c+"LepJetTau21",                     .pfs={"StackPlotSignal","Year",cut,"LepJet"},                        .cuts={},.draw=d,.opt=opt,.ranges=r_Stk5});
    sh.AddHistos(s+"AK8", { .fill=c+"LepJetLSF",                       .pfs={"StackPlotSignal","Year",cut,"LepJet"},                        .cuts={},.draw=d,.opt=opt,.ranges=r_Stk5});
    sh.AddHistos(s+"AK8", { .fill=c+"LepJetNSubJet",                   .pfs={"StackPlotSignal","Year",cut,"LepJet"},                        .cuts={},.draw=d,.opt=opt,.ranges=r_Stk5});
    //sh.AddHistos(s+"AK8", { .fill=c+"LepJetLSFNoIso",                  .pfs={"StackPlotSignal","Year",cut+"_Excl1LepMTdPhiJet","LepJetNoIso"}, .cuts={},.draw=d,.opt=opt,.ranges=r_Stk5});
    //sh.AddHistos(s+"AK8", { .fill=c+"LepJetDRmin",                     .pfs={"StackPlotSignal","Year",cut+"_Excl1LepMTdPhiJet","LepJetNoIso"}, .cuts={},.draw=d,.opt=opt,.ranges=r_Stk5});
    //sh.AddHistos(s+"AK8", { .fill=c+"LepJetPtrel",                     .pfs={"StackPlotSignal","Year",cut+"_Excl1LepMTdPhiJet","LepJetNoIso"}, .cuts={},.draw=d,.opt=opt,.ranges=r_Stk5});
    // Boosted leptonic tops
    sh.AddHistos(s+"AK8", { .fill=c+"LepTopPt",                        .pfs={"StackPlotSignal","Year",cut,"LepTopNoPt"},                    .cuts={},.draw=d,.opt=opt,.ranges=r_Stk5});
    sh.AddHistos(s+"AK8", { .fill=c+"LepTopPt",                        .pfs={"StackPlotSignal","Year",cut,"LepTopHighMass"},                .cuts={},.draw=d,.opt=opt,.ranges=r_Stk5});
    sh.AddHistos(s+"AK8", { .fill=c+"LepTopEta",                       .pfs={"StackPlotSignal","Year",cut,"LepTop"},                        .cuts={},.draw=d,.opt=opt,.ranges=r_Stk5});
    sh.AddHistos(s+"AK8", { .fill=c+"LepTopPhi",                       .pfs={"StackPlotSignal","Year",cut,"LepTop"},                        .cuts={},.draw=d,.opt=opt,.ranges=r_Stk5});
    sh.AddHistos(s+"AK8", { .fill=c+"LepTopMass",                      .pfs={"StackPlotSignal","Year",cut,"LepTopNoMass"},                  .cuts={},.draw=d,.opt=opt,.ranges=r_Stk5});
    sh.AddHistos(s+"AK8", { .fill=c+"LepTopSubJetDeepB",               .pfs={"StackPlotSignal","Year",cut,"LepTopNoSubJetB"},               .cuts={},.draw=d,.opt=opt,.ranges=r_Stk5});
    sh.AddHistos(s+"AK8", { .fill=c+"LepTopTau21",                     .pfs={"StackPlotSignal","Year",cut,"LepTop"},                        .cuts={},.draw=d,.opt=opt,.ranges=r_Stk5});
    sh.AddHistos(s+"AK8", { .fill=c+"LepTopLSF",                       .pfs={"StackPlotSignal","Year",cut,"LepTop"},                        .cuts={},.draw=d,.opt=opt,.ranges=r_Stk5});
    sh.AddHistos(s+"AK8", { .fill=c+"LepTopNSubJet",                   .pfs={"StackPlotSignal","Year",cut,"LepTop"},                        .cuts={},.draw=d,.opt=opt,.ranges=r_Stk5});
    //sh.AddHistos(s+"AK8", { .fill=c+"LepTopLSFNoIso",                  .pfs={"StackPlotSignal","Year",cut+"_Excl1LepMTdPhiJet","LepTopNoIso"}, .cuts={},.draw=d,.opt=opt,.ranges=r_Stk5});
    //sh.AddHistos(s+"AK8", { .fill=c+"LepJetDRmin",                     .pfs={"StackPlotSignal","Year",cut+"_Excl1LepMTdPhiJet","LepTopNoIso"}, .cuts={},.draw=d,.opt=opt,.ranges=r_Stk5});
    //sh.AddHistos(s+"AK8", { .fill=c+"LepJetPtrel",                     .pfs={"StackPlotSignal","Year",cut+"_Excl1LepMTdPhiJet","LepTopNoIso"}, .cuts={},.draw=d,.opt=opt,.ranges=r_Stk5});
    for (auto nobj_bin : {"NJet45",
             //"NTop1", "NTop2", "NTop3", "NTop4", "NTop5", 
             //"NWDeepMD1", "NWDeepMD2", "NWDeepMD3", 
             //"NZDeepMD1", "NZDeepMD2", "NZDeepMD3",
             "NTopDeepMD1", "NTopDeepMD2", "NTopDeepMD3", "NTopDeepMD4",
             "NLepTop",     "NLepTopHighMass",
             "NTopDeep1",   "NTopDeep2", "NTopDeep3",   "NTopDeep4",
             "NW1",         "NW2",       "NW3", 
             "NWDeep1",     "NWDeep2",   "NWDeep3", 
             "NLepJetCand", "NLepJet",   "NLepJetHighMass",
             "NZDeep1",     "NZDeep2",   "NZDeep3", 
             "NVDeep1",     "NVDeep2",   "NVDeep3"}) {
      std::string signal = "StackPlotTopSignal";
      opt  = o_stk_d_T;
      if (TString(nobj_bin).Contains("NZ")||TString(nobj_bin).Contains("NV")||TString(nobj_bin).Contains("LepJet")) {
        signal = "StackPlotVSignal";
        opt  = o_stk_d_V;
      }
      for (auto std_plot : standard_plots) {
        sh.AddHistos(s+"evt",  { .fill=c+std_plot,                  .pfs={signal,"Year",cut,nobj_bin},         .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
        //sh.AddHistos(s+"evt",  { .fill=c+std_plot,                  .pfs={signal,"Year",cut,nobj_bin,"Nb"},    .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
        //sh.AddHistos(s+"evt",  { .fill=c+std_plot,                  .pfs={signal,"Year",cut,nobj_bin,"Nisob"}, .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
        //sh.AddHistos(s+"evt",  { .fill=c+std_plot,                  .pfs={signal,"Year",cut,nobj_bin,"2b"},    .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
        //sh.AddHistos(s+"evt",  { .fill=c+std_plot,                  .pfs={signal,"Year",cut,nobj_bin,"MTBoost800"}, .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
      }
      if (nobj_bin != std::string("NJet45")) {
        sh.AddHistos(s+"evt",  { .fill=c+"NJet",                    .pfs={signal,"Year",cut,nobj_bin},         .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
        //sh.AddHistos(s+"evt",  { .fill=c+"NJet",                    .pfs={signal,"Year",cut,nobj_bin,"Nb"},    .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
        //sh.AddHistos(s+"evt",  { .fill=c+"NJet",                    .pfs={signal,"Year",cut,nobj_bin,"Nisob"}, .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
        //sh.AddHistos(s+"evt",  { .fill=c+"NJet",                    .pfs={signal,"Year",cut,nobj_bin,"2b"},    .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
        //sh.AddHistos(s+"evt",  { .fill=c+"NJet",                    .pfs={signal,"Year",cut,nobj_bin,"MTBoost800"},    .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
      }
      sh.AddHistos(  s+"evt",  { .fill=c+"DeltaPhi",                .pfs={signal,"Year",cut,nobj_bin},                 .cuts={},.draw=d,.opt=opt,.ranges=r_Stk9});
      sh.AddHistos(  s+"evt",  { .fill=c+"DeltaPhi",                .pfs={signal,"Year",cut+"_ExclMT",nobj_bin},          .cuts={},.draw=d,.opt=opt,.ranges=r_Stk9});
      // MTBoost
      sh.AddHistos(  s+"evt",  { .fill=c+"MTBoost",                 .pfs={signal,"Year",cut,nobj_bin},                 .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
      //sh.AddHistos(  s+"evt",  { .fill=c+"MTBoost",                 .pfs={signal,"Year",cut,nobj_bin,"Nb"},            .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
      //sh.AddHistos(  s+"evt",  { .fill=c+"MTBoost",                 .pfs={signal,"Year",cut,nobj_bin,"Nisob"},         .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
      //sh.AddHistos(  s+"evt",  { .fill=c+"MTBoost",                 .pfs={signal,"Year",cut,nobj_bin,"2b"},            .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
    }
    // Exclusive Leptonic+Hadronic combinations
    //for (std::string nhad_bin : {"Nb", "Nisob", "2b", "NHadTop", "NHadW", "NTopDeepMD1", "NTopDeepMD2", "NTopDeep1", "NTopDeep2"}) {
    //  for (std::string nlep_bin : {"NLepJetCand", "NLepJet", "NLepJetHighMass", "NLepTop", "NLepTopHighMass"}) {
    //    opt  = o_stk_d_T;
    //    for (auto std_plot : standard_plots) {
    //      sh.AddHistos(s+"evt", { .fill=c+std_plot,                .pfs={"StackPlotTopSignal","Year",cut,                  nhad_bin,nlep_bin}, .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
    //      sh.AddHistos(s+"evt", { .fill=c+std_plot,                .pfs={"StackPlotTopSignal","Year",cut+"_Excl1LepMTdPhiJet",nhad_bin,nlep_bin}, .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
    //    }
    //    sh.AddHistos(s+"evt", { .fill=c+"NJet",                    .pfs={"StackPlotTopSignal","Year",cut,                  nhad_bin,nlep_bin}, .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
    //    sh.AddHistos(s+"evt", { .fill=c+"NJet",                    .pfs={"StackPlotTopSignal","Year",cut+"_Excl1LepMTdPhiJet",nhad_bin,nlep_bin}, .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
    //    sh.AddHistos(s+"evt",    { .fill=c+"MTBoost",              .pfs={"StackPlotTopSignal","Year",cut,                  nhad_bin,nlep_bin}, .cuts={},.draw=d,.opt=opt,.ranges=r_Stk5});
    //    sh.AddHistos(  s+"evt",  { .fill=c+"DeltaPhi",             .pfs={"StackPlotTopSignal","Year",cut,       nhad_bin,nlep_bin},            .cuts={},.draw=d,.opt=opt,.ranges=r_Stk9});
    //    sh.AddHistos(  s+"evt",  { .fill=c+"DeltaPhi",             .pfs={"StackPlotTopSignal","Year",cut+"_ExclMT",nhad_bin,nlep_bin},            .cuts={},.draw=d,.opt=opt,.ranges=r_Stk9});
    //  }
    //}
    //for (std::string nhad_bin : {"Nb", "Nisob", "2b", "NHadW", "NZDeep1", "NZDeep2", "NZDeep3", "NVDeep1", "NVDeep2", "NVDeep3"}) {
    //  for (std::string nlep_bin : {"NLepJetCand", "NLepJet", "NLepJetHighMass"}) {
    //    opt  = o_stk_d_V;
    //    for (auto std_plot : standard_plots) {
    //      sh.AddHistos(s+"evt", { .fill=c+std_plot,                .pfs={"StackPlotVSignal","Year",cut,                  nhad_bin,nlep_bin}, .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
    //      sh.AddHistos(s+"evt", { .fill=c+std_plot,                .pfs={"StackPlotVSignal","Year",cut+"_Excl1LepMTdPhiJet",nhad_bin,nlep_bin}, .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
    //    }
    //    sh.AddHistos(s+"evt", { .fill=c+"NJet",                    .pfs={"StackPlotVSignal","Year",cut,                  nhad_bin,nlep_bin}, .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
    //    sh.AddHistos(s+"evt", { .fill=c+"NJet",                    .pfs={"StackPlotVSignal","Year",cut+"_Excl1LepMTdPhiJet",nhad_bin,nlep_bin}, .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
    //    sh.AddHistos(s+"evt", { .fill=c+"MTBoost",                 .pfs={"StackPlotVSignal","Year",cut,                  nhad_bin,nlep_bin}, .cuts={},.draw=d,.opt=opt,.ranges=r_Stk5});
    //    sh.AddHistos(s+"evt",  { .fill=c+"DeltaPhi",               .pfs={"StackPlotVSignal","Year",cut,                  nhad_bin,nlep_bin}, .cuts={},.draw=d,.opt=opt,.ranges=r_Stk9});
    //    sh.AddHistos(s+"evt",  { .fill=c+"DeltaPhi",               .pfs={"StackPlotVSignal","Year",cut+"_ExclMT",           nhad_bin,nlep_bin}, .cuts={},.draw=d,.opt=opt,.ranges=r_Stk9});
    //  }
    //}
    // Gen Truth plots
    for (const auto& cut2 : { cut, cut+"_Excl1LepMTdPhiJet" }) {
      // gen lep/top pt
      sh.AddHistos("gen lep",    { .fill="GenLepPtBins",              .pfs={"Signals_Background","Year",cut2,"GenLepMother","GenLeptonFlavour"}, .cuts={}, .draw="HIST", .opt=o_1or2d_s+"Norm", .ranges={0,0, 0,1, 0.5,0.53} });
      //sh.AddHistos("gen leptop", { .fill="GenLepTopMatchedGenLepPt",  .pfs={"Signals_Background","Year",cut2,"GenTopLeptonFlavour"},             .cuts={}, .draw="HIST", .opt=o_1or2d_s+"Norm", .ranges={0,0, 0,1, 0.5,0.53} }); // Equivalent with above
      sh.AddHistos("gen lep",    { .fill="GenLepPtBins",  .pfs={"MGluinoPoints",  "MLSPPoints","GluinoSignalScans",  cut2,"GenLepMother"}, .cuts={}, .draw="HIST", .opt=o_1or2d_s+"Norm", .ranges={0,0, 0,1, 0.5,0.53} });
      sh.AddHistos("gen lep",    { .fill="GenLepPtBins",  .pfs={"MSquarkPoints",    "MLSPPoints","SquarkSignalScans",    cut2,"GenLepMother"}, .cuts={}, .draw="HIST", .opt=o_1or2d_s+"Norm", .ranges={0,0, 0,1, 0.5,0.53} });
      sh.AddHistos("gen lep",    { .fill="GenLepPtBins",  .pfs={"MEWKPoints","MLSPPoints","EWKSignalScans",cut2,"GenLepMother"}, .cuts={}, .draw="HIST", .opt=o_1or2d_s+"Norm", .ranges={0,0, 0,1, 0.5,0.53} });
      sh.AddHistos("gen leptop", { .fill="GenLepTopMatchedGenLepPt_vs_GenLepTopPt",   .pfs={"Signals_Background","Year",cut2,"GenTopLeptonFlavour"}, .cuts={},.draw="COLZ",.opt=o_1or2d_s+"Log",.ranges={}});
    }
  }

  
  // ROC Curves
  sh.SetHistoWeights({ [&w] { return w.sf_weight[Region::Pre]; } });
  // ---------------------- Leptons ---------------------
  for (std::string benchmark : {"Bkg"}) {
    // ----------------------  Veto  ----------------------
    for (std::string mother : {"W", "HardProcess"}) {
      // Electrons
      sh.AddHistos("ele", { .fill="EleFrom"+mother+"_"+benchmark, .pfs={"elept5_cut",        "eleeta_veto_cut",
                                                                        "eleip_medium",      "eleid_mva_loose", "eleminiiso_loose"}, .cuts={"P"},.draw="PLX",.opt="ROC", .ranges={0.5,1, 0.9,1}});
      sh.AddHistos("ele", { .fill="EleFrom"+mother+"_"+benchmark, .pfs={"elept5_cut",        "eleeta_veto_cut", "eleip_medium_cut",
                                                                        "eleid_mva_miniiso", "eleid_mva_2diso", "eleid_mva_iso",    "eleid_cut_iso"},   .cuts={"P"},.draw="PLX",.opt="ROC",   .ranges={0.5,1, 0.9,1}});
      sh.AddHistos("ele", { .fill="EleFrom"+mother+"_"+benchmark, .pfs={"elept5_cut",        "eleeta_veto_cut", "eleip_medium_cut", "eleid_mva_loose_cut",
                                                                        "eleminiiso",        "elepfiso",        "ele2diso"}, .cuts={"P"},.draw="PLX",.opt="ROC", .ranges={0.5,1, 0.9,1}});
      // Muons
      sh.AddHistos("mu",  { .fill="MuFrom"+mother+"_"+benchmark,  .pfs={"mupt5_cut",  "mueta_cut", 
                                                                        "muip_loose", "muid_soft", "muminiiso_loose"}, .cuts={"P"},.draw="PLX",.opt="ROC",  .ranges={0.5,1, 0.9,1}});
      sh.AddHistos("mu",  { .fill="MuFrom"+mother+"_"+benchmark,  .pfs={"mupt5_cut",  "mueta_cut", "muip_loose_cut", "muminiiso_loose_cut",
                                                                        "muid_mva",   "muid_soft_comp", "muid_medium_comp", "muid_tight_comp"}, .cuts={"P"},.draw="PLX",.opt="ROC", .ranges={0.5,1, 0.9,1}});
      sh.AddHistos("mu",  { .fill="MuFrom"+mother+"_"+benchmark,  .pfs={"mupt5_cut",  "mueta_cut", "muip_loose_cut", "muid_soft_cut",
                                                                        "muminiiso",  "mupfiso"}, .cuts={"P"},.draw="PLX",.opt="ROC",  .ranges={0.5,1, 0.9,1}});
    }
  }
  // --------------------- Isolated ---------------------
  for (const auto& bm : all_benchmarks) {
    // Electrons
    for (std::string mother : {"W", "HardProcess"}) {
      sh.AddHistos("ele", { .fill="EleFrom"+mother+"_"+bm.first, .pfs={"eleeta_cut",
                                                                       "elept10",           "eleip_medium",    "eleid_mva_medium", "eleminiiso_tight"}, .cuts={"P"},.draw="PLX",.opt="ROC", .ranges={0,0, 0.96,1.0}});
      sh.AddHistos("ele", { .fill="EleFrom"+mother+"_"+bm.first, .pfs={"elept10_cut",       "eleeta_cut",      "eleip_medium_cut",
                                                                       "eleid_mva_miniiso", "eleid_mva_2diso", "eleid_mva_iso",    "eleid_cut_iso"},   .cuts={"P"},.draw="PLX",.opt="ROC",   .ranges={0,0, 0.96,1.0}});
      sh.AddHistos("ele", { .fill="EleFrom"+mother+"_"+bm.first, .pfs={"elept10_cut",       "eleeta_cut",      "eleip_medium_cut", "eleid_mva_medium_cut",
                                                                       "eleminiiso",        "elepfiso",        "ele2diso"}, .cuts={"P"},.draw="PLX",.opt="ROC", .ranges={0,0, 0.96,1.0}});
      // Muons
      sh.AddHistos("mu",  { .fill="MuFrom"+mother+"_"+bm.first,  .pfs={"mueta_cut", 
                                                                       "mupt10",     "muip_medium", "muid_mediumprompt", "muminiiso_medium"}, .cuts={"P"},.draw="PLX",.opt="ROC",  .ranges={0,0, 0.96,1.0}});
      sh.AddHistos("mu",  { .fill="MuFrom"+mother+"_"+bm.first,  .pfs={"mupt10_cut", "mueta_cut",   "muip_medium_cut", "muminiiso_medium_cut",
                                                                       "muid_mva",   "muid_soft_comp", "muid_medium_comp", "muid_tight_comp"}, .cuts={"P"},.draw="PLX",.opt="ROC", .ranges={0,0, 0.96,1.0}});
      sh.AddHistos("mu",  { .fill="MuFrom"+mother+"_"+bm.first,  .pfs={"mupt10_cut", "mueta_cut",   "muip_medium_cut", "muid_mediumprompt_cut",
                                                                       "muminiiso",  "mupfiso"}, .cuts={"P"},.draw="PLX",.opt="ROC",  .ranges={0,0, 0.96,1.0}});
    }
  }
  for (const auto& bm : top_benchmarks) {
    // ------------------- Non-Isolated -------------------
    for (std::string mother : {"Top"}) {
      // Electrons and their neutrinos
      for (std::string object : {"Ele","EleNu"}) {
        sh.AddHistos("ele", { .fill=object+"From"+mother+"_"+bm.first, .pfs={"eleeta_cut",
                                                                             "elept30",           "eleip_medium",    "eleid_mva_loose", "ele2diso15"}, .cuts={"P"},.draw="PLX",.opt="ROC", .ranges={0,0, 0.8,1.0}});
        sh.AddHistos("ele", { .fill=object+"From"+mother+"_"+bm.first, .pfs={"elept30_cut",    "eleeta_cut",      "eleip_medium_cut",
                                                                             "eleid_mva_miniiso", "eleid_mva_2diso", "eleid_mva_iso",    "eleid_cut_iso"},   .cuts={"P"},.draw="PLX",.opt="ROC",   .ranges={0,0, 0.8,1.0}});
        sh.AddHistos("ele", { .fill=object+"From"+mother+"_"+bm.first, .pfs={"elept30_cut",    "eleeta_cut",      "eleip_medium_cut",  "eleid_mva_loose_cut",
                                                                             "eleminiiso",        "elepfiso",        "ele2diso"}, .cuts={"P"},.draw="PLX",.opt="ROC", .ranges={0,0, 0.8,1.0}});
      }
      // Muons and their neutrinos
      for (std::string object : {"Mu","MuNu"}) {
        sh.AddHistos("mu",  { .fill=object+"From"+mother+"_"+bm.first,  .pfs={"mueta_cut", 
                                                                              "mupt30",     "muip_tight", "muid_mva_loose",     "mu2diso15"}, .cuts={"P"},.draw="PLX",.opt="ROC",  .ranges={0,0, 0.8,1.0}});
        sh.AddHistos("mu",  { .fill=object+"From"+mother+"_"+bm.first,  .pfs={"mupt30_cut", "mueta_cut",  "muip_tight_cut", "mu2diso15_cut",
                                                                              "muid_mva",   "muid_soft_comp", "muid_medium_comp", "muid_tight_comp"}, .cuts={"P"},.draw="PLX",.opt="ROC", .ranges={0,0, 0.8,1.0}});
        sh.AddHistos("mu",  { .fill=object+"From"+mother+"_"+bm.first,  .pfs={"mupt30_cut", "mueta_cut",  "muip_tight_cut", "muid_mva_loose_cut",
                                                                              "muminiiso",  "mupfiso",    "mu2diso"}, .cuts={"P"},.draw="PLX",.opt="ROC",  .ranges={0,0, 0.8,1.0}});
      }
    }
    // ------------------- Leptonic top -------------------
    // Top with W decaying to electron and the neutrino
    for (std::string object : {"EleLepTop"}) {//,"EleNuFromLepTop"}) {
      sh.AddHistos("ele", { .fill=object+"_"+bm.first, .pfs={"eleeta_cut",        "ele_ak8eta_cut",
                                                             "ele_ak8pt300",      "ele_msoftdrop0",   "ele_sjbtag_loose",    //"deepTag_top",
                                                             "ele_neutrinodr",    //"ele_neutrinojetdr",
                                                             "elept30",           "eleip_medium",     "eleid_mva_loose",    "ele2diso15"}, .cuts={"P"},.draw="PLX",.opt="ROC", .ranges={0,1, 0.98,1.0}});
      sh.AddHistos("ele", { .fill=object+"_"+bm.first, .pfs={"elept30_cut",       "eleeta_cut",       "eleip_medium_cut",
                                                             "ele_ak8eta_cut",    "ele_ak8pt300_cut", "ele_sjbtag_loose_cut",
                                                             "eleid_mva_miniiso", "eleid_mva_2diso",  "eleid_mva_iso",       "eleid_cut_iso"},   .cuts={"P"},.draw="PLX",.opt="ROC",   .ranges={0,1, 0.98,1.0}});
      sh.AddHistos("ele", { .fill=object+"_"+bm.first, .pfs={"elept30_cut",       "eleeta_cut",       "eleip_medium_cut",    "eleid_mva_loose_cut",
                                                             "ele_ak8eta_cut",    "ele_ak8pt300_cut", "ele_sjbtag_loose_cut",
                                                             "eleminiiso",        "elepfiso",         "ele2diso"}, .cuts={"P"},.draw="PLX",.opt="ROC", .ranges={0,1, 0.98,1.0}});
    }
    // Top with W decaying to muon and the neutrino
    for (std::string object : {"MuLepTop"}) {//,"MuNuFromLepTop"}) {
      sh.AddHistos("mu",  { .fill=object+"_"+bm.first,  .pfs={"mueta_cut",     "mu_ak8eta_cut",
                                                              "mu_ak8pt300",   "mu_msoftdrop0",   "mu_sjbtag_loose",    //"deepTag_top",
                                                              "mu_neutrinodr", //"mu_neutrinojetdr",
                                                              "mupt30",        "muip_tight",      "muid_mva_loose",     "mu2diso15"}, .cuts={"P"},.draw="PLX",.opt="ROC",  .ranges={0,1, 0.98,1.0}});
      sh.AddHistos("mu",  { .fill=object+"_"+bm.first,  .pfs={"mupt30_cut",    "mueta_cut",       "muip_tight_cut",     "mu2diso15_cut",
                                                              "mu_ak8eta_cut", "mu_ak8pt300_cut", "mu_sjbtag_loose_cut",
                                                              "muid_mva",      "muid_soft_comp",  "muid_medium_comp",   "muid_tight_comp"}, .cuts={"P"},.draw="PLX",.opt="ROC", .ranges={0,1, 0.98,1.0}});
      sh.AddHistos("mu",  { .fill=object+"_"+bm.first,  .pfs={"mupt30_cut",    "mueta_cut",       "muip_tight_cut",     "muid_mva_loose_cut",
                                                              "mu_ak8eta_cut", "mu_ak8pt300_cut", "mu_sjbtag_loose_cut",
                                                              "muminiiso",     "mupfiso",         "mu2diso"}, .cuts={"P"},.draw="PLX",.opt="ROC",  .ranges={0,1, 0.98,1.0}});
    }
    // ------------------- Hadronic top -------------------
    sh.AddHistos("AK8", { .fill="HadTop_"+bm.first, .pfs={"ak8pt500_cut", "tau32_softdrop_sjbtag", "deepTagMD_top", "deepTagMD_top_minsd", "deepTag_top"}, .cuts={"P"},.draw="PLX",.opt="ROC", .ranges={0,0, 0.9,1.0}});
    sh.AddHistos("AK8", { .fill="HadTop_"+bm.first, .pfs={"ak8pt500", "msoftdrop105", "deepTagMD_top_WP1"},  .cuts={"P"},.draw="PLX",.opt="ROC", .ranges={0,0, 0.9,1.0}});
    sh.AddHistos("AK8", { .fill="HadTop_"+bm.first, .pfs={"ak8pt500", "msoftdrop_min","deepTag_top_WP1"},    .cuts={"P"},.draw="PLX",.opt="ROC", .ranges={0,0, 0.9,1.0}});
  }
  for (const auto& bm : all_benchmarks) {
    // -------------------- Hadronic W --------------------
    sh.AddHistos("AK8", { .fill="HadW_"+bm.first, .pfs={"ak8pt200_cut", "tau21_softdrop",
                                                        "deepTagMD_W", "deepTagMD_W_minsd", "deepTagMD_W_sd", "deepTag_W",
                                                        "deepTagMD_Z", "deepTagMD_Z_minsd", "deepTagMD_Z_sd", "deepTag_Z"},  .cuts={"P"},.draw="PLX",.opt="ROC", .ranges={0,0.6, 0.6,1.0}});
    sh.AddHistos("AK8", { .fill="HadW_"+bm.first, .pfs={"ak8pt200", "msoftdrop65",   "msoftdrop_max", "deepTagMD_W_WP1"},    .cuts={"P"},.draw="PLX",.opt="ROC", .ranges={0,0.5, 0.9,1.0}});
    sh.AddHistos("AK8", { .fill="HadW_"+bm.first, .pfs={"ak8pt200", "msoftdrop_min", "msoftdrop_max", "deepTag_W_WP1"},      .cuts={"P"},.draw="PLX",.opt="ROC", .ranges={0,0.5, 0.9,1.0}});
    sh.AddHistos("AK8", { .fill="HadW_"+bm.first, .pfs={"ak8pt200", "msoftdrop65",   "msoftdrop_max", "deepTagMD_W_WP2"},    .cuts={"P"},.draw="PLX",.opt="ROC", .ranges={0,0.5, 0.9,1.0}});
    sh.AddHistos("AK8", { .fill="HadW_"+bm.first, .pfs={"ak8pt200", "msoftdrop_min", "msoftdrop_max", "deepTag_W_WP2"},      .cuts={"P"},.draw="PLX",.opt="ROC", .ranges={0,0.5, 0.9,1.0}});
  }
  for (const auto& bm : WZH_benchmarks) {
    // -------------------- Hadronic Z --------------------
    sh.AddHistos("AK8", { .fill="HadZ_"+bm.first, .pfs={"ak8pt200_cut", "tau21_softdrop",
                                                        "deepTagMD_W", "deepTagMD_W_minsd", "deepTagMD_W_sd", "deepTag_W",
                                                        "deepTagMD_Z", "deepTagMD_Z_minsd", "deepTagMD_Z_sd", "deepTag_Z"}, .cuts={"P"},.draw="PLX",.opt="ROC", .ranges={0,0, 0.8,1.0}});
    sh.AddHistos("AK8", { .fill="HadZ_"+bm.first, .pfs={"ak8pt200",     "msoftdrop80",   "msoftdrop_max", "deepTagMD_Z_WP1"},  .cuts={"P"},.draw="PLX",.opt="ROC", .ranges={0,0.5, 0.9,1.0}});
    sh.AddHistos("AK8", { .fill="HadZ_"+bm.first, .pfs={"ak8pt200",     "msoftdrop_min", "msoftdrop_max", "deepTag_Z_WP1"},    .cuts={"P"},.draw="PLX",.opt="ROC", .ranges={0,0.5, 0.9,1.0}});
    sh.AddHistos("AK8", { .fill="HadZ_"+bm.first, .pfs={"ak8pt200",     "msoftdrop80",   "msoftdrop_max", "deepTagMD_Z_WP2"},  .cuts={"P"},.draw="PLX",.opt="ROC", .ranges={0,0.5, 0.9,1.0}});
    sh.AddHistos("AK8", { .fill="HadZ_"+bm.first, .pfs={"ak8pt200",     "msoftdrop_min", "msoftdrop_max", "deepTag_Z_WP2"},    .cuts={"P"},.draw="PLX",.opt="ROC", .ranges={0,0.5, 0.9,1.0}});
    // -------------------- Hadronic H --------------------
    sh.AddHistos("AK8", { .fill="HadH_"+bm.first, .pfs={"ak8pt300_cut", "deepTagMD_H",   "deepTagMD_H_minsd", "deepTagMD_H_sd", "btagHbb"}, .cuts={"P"},.draw="PLX",.opt="ROC", .ranges={0,0, 0.8,1.0}});
    sh.AddHistos("AK8", { .fill="HadH_"+bm.first, .pfs={"ak8pt300",     "msoftdrop100",  "msoftdrop_max",     "deepTagMD_H_WP2"},      .cuts={"P"},.draw="PLX",.opt="ROC", .ranges={0,0, 0.8,1.0}});
    //sh.AddHistos("AK8", { .fill="HadH_"+bm.first, .pfs={"ak8pt300",     "msoftdrop_min", "msoftdrop_max",     "deepTag_H_WP2"},        .cuts={"P"},.draw="PLX",.opt="ROC", .ranges={0,0, 0.8,1.0}});
  }



  
  // ----------------------------------------------------------------------------------------------
  //                                    New signal segions
  //-----------------------------------------------------------------------------------------------

  // Fully hadronic Signal Regions
  for (auto region : {Region::SR_Had_1htop, Region::SR_Had_2htop, Region::SR_Had_V_b_45j, Region::SR_Had_V_b_6j, Region::SR_Had_1V_0b_34j, Region::SR_Had_1V_0b_5j, Region::SR_Had_2V_0b_24j, Region::SR_Had_2V_0b_5j, 
           Region::SR_Had_H_b_45j, Region::SR_Had_H_b_6j, Region::SR_Had_2H_b_6j, Region::SR_Had_HV_b_6j, Region::SR_Had_1H_0b_34j, Region::SR_Had_1H_0b_5j, Region::SR_Had_2H_0b_34j, Region::SR_Had_2H_0b_5j, Region::SR_Had_HV_0b_24j, Region::SR_Had_HV_0b_5j}) {
    sh.SetHistoWeights({ [&w,region] { return w.sf_weight[region]; } });
    std::string cut(magic_enum::enum_name(region));
    std::vector<std::string> showdata = {"Blind"};
    // Signal discriminators
    sh.AddHistos("evt",    { .fill="MRFine_vs_METFine",         .pfs={"Signals_Background","Year",cut},          .cuts={},.draw="COLZ",.opt=o_1or2d_s+"Log",.ranges={}});
    sh.AddHistos("evt",    { .fill="R2Fine_vs_METFine",         .pfs={"Signals_Background","Year",cut},          .cuts={},.draw="COLZ",.opt=o_1or2d_s+"Log",.ranges={}});
    sh.AddHistos("evt",    { .fill="R2Fine_vs_MRFine",          .pfs={"Signals_Background","Year",cut},          .cuts={},.draw="COLZ",.opt=o_1or2d_s+"Log",.ranges={}});
    sh.AddHistos("evt",    { .fill="MRFine_vs_HTFine",          .pfs={"Signals_Background","Year",cut},          .cuts={},.draw="COLZ",.opt=o_1or2d_s+"Log",.ranges={}});
    sh.AddHistos("evt",    { .fill="METFine_vs_HTFine",         .pfs={"Signals_Background","Year",cut},          .cuts={},.draw="COLZ",.opt=o_1or2d_s+"Log",.ranges={}});
    sh.AddHistos("evt",    { .fill="R2Fine_vs_MRFine",          .pfs={"Signals_Background","Year",cut},          .cuts={},.draw="COLZ",.opt=o_1or2d_s+"Log",.ranges={}});
    sh.AddHistos("evt",    { .fill="MTBoost_vs_METFine",        .pfs={"Signals_Background","Year",cut},          .cuts={},.draw="COLZ",.opt=o_1or2d_s+"Log",.ranges={}});
    sh.AddHistos("evt",    { .fill="MTBoost_vs_R2Fine",         .pfs={"Signals_Background","Year",cut},          .cuts={},.draw="COLZ",.opt=o_1or2d_s+"Log",.ranges={}});
    sh.AddHistos("evt",    { .fill="MTBoost_vs_MRFine",         .pfs={"Signals_Background","Year",cut},          .cuts={},.draw="COLZ",.opt=o_1or2d_s+"Log",.ranges={}});
    // Stack plots
    for (auto data : showdata ) {
      std::string signal = "StackPlotSignal";
      std::string opt  = (data=="Blind") ? o_stk_s_S : o_stk_d_S;
      if (region==Region::SR_Had_1htop||region==Region::SR_Had_2htop||region==Region::SR_Had_V_b_45j||region==Region::SR_Had_V_b_6j) {
        opt    = (data=="Blind") ? o_stk_s_T : o_stk_d_T;
        signal = "StackPlotTopSignal";
      } else if (region==Region::SR_Had_1V_0b_34j||region==Region::SR_Had_1V_0b_5j||region==Region::SR_Had_2V_0b_24j||region==Region::SR_Had_2V_0b_5j) {
        opt    = (data=="Blind") ? o_stk_s_V : o_stk_d_V;
        signal = "StackPlotVSignal";
      } else if (region==Region::SR_Had_H_b_45j||region==Region::SR_Had_H_b_6j||region==Region::SR_Had_2H_b_6j||region==Region::SR_Had_HV_b_6j||
                 region==Region::SR_Had_1H_0b_34j||region==Region::SR_Had_1H_0b_5j||region==Region::SR_Had_2H_0b_34j||region==Region::SR_Had_2H_0b_5j||
                 region==Region::SR_Had_HV_0b_24j||region==Region::SR_Had_HV_0b_5j) {
        opt    = (data=="Blind") ? o_stk_s_H : o_stk_d_H;
        signal = "StackPlotHSignal";
      }
      // Masses
      sh.AddHistos(  s+"hadtop", { .fill=c+"HadTopMass",              .pfs={signal,"Year",cut},               .cuts={},.draw=d,.opt=opt,.ranges=r_Stk5});
      sh.AddHistos(  s+"leptop", { .fill=c+"LepTopMass",              .pfs={signal,"Year",cut},               .cuts={},.draw=d,.opt=opt,.ranges=r_Stk5});
      sh.AddHistos(  s+"hadw",   { .fill=c+"HadWMass",                .pfs={signal,"Year",cut},               .cuts={},.draw=d,.opt=opt,.ranges=r_Stk5});
      sh.AddHistos(  s+"hadz",   { .fill=c+"HadZMass",                .pfs={signal,"Year",cut},               .cuts={},.draw=d,.opt=opt,.ranges=r_Stk5});
      sh.AddHistos(  s+"hadh",   { .fill=c+"HadHMass",                .pfs={signal,"Year",cut},               .cuts={},.draw=d,.opt=opt,.ranges=r_Stk5});
    }
  }


  // Isolated lepton Signal Regions
  for (auto region : {Region::SR_Lep_1htop, Region::SR_Lep_V_b, Region::SR_Lep_V_0b, Region::SR_Lep_H_b, Region::SR_Lep_H_0b}) {
    sh.SetHistoWeights({ [&w,region] { return w.sf_weight[region]; } });
    std::string cut(magic_enum::enum_name(region));
    std::vector<std::string> showdata = {"Blind"};
    // Signal discriminators
    sh.AddHistos("evt",    { .fill="MRFine_vs_METFine",         .pfs={"Signals_Background","Year",cut},          .cuts={},.draw="COLZ",.opt=o_1or2d_s+"Log",.ranges={}});
    sh.AddHistos("evt",    { .fill="R2Fine_vs_METFine",         .pfs={"Signals_Background","Year",cut},          .cuts={},.draw="COLZ",.opt=o_1or2d_s+"Log",.ranges={}});
    sh.AddHistos("evt",    { .fill="R2Fine_vs_MRFine",          .pfs={"Signals_Background","Year",cut},          .cuts={},.draw="COLZ",.opt=o_1or2d_s+"Log",.ranges={}});
    sh.AddHistos("evt",    { .fill="MRFine_vs_HTFine",          .pfs={"Signals_Background","Year",cut},          .cuts={},.draw="COLZ",.opt=o_1or2d_s+"Log",.ranges={}});
    sh.AddHistos("evt",    { .fill="METFine_vs_HTFine",         .pfs={"Signals_Background","Year",cut},          .cuts={},.draw="COLZ",.opt=o_1or2d_s+"Log",.ranges={}});
    sh.AddHistos("evt",    { .fill="R2Fine_vs_MRFine",          .pfs={"Signals_Background","Year",cut},          .cuts={},.draw="COLZ",.opt=o_1or2d_s+"Log",.ranges={}});
    sh.AddHistos("evt",    { .fill="MTBoost_vs_METFine",        .pfs={"Signals_Background","Year",cut},          .cuts={},.draw="COLZ",.opt=o_1or2d_s+"Log",.ranges={}});
    sh.AddHistos("evt",    { .fill="MTBoost_vs_R2Fine",         .pfs={"Signals_Background","Year",cut},          .cuts={},.draw="COLZ",.opt=o_1or2d_s+"Log",.ranges={}});
    sh.AddHistos("evt",    { .fill="MTBoost_vs_MRFine",         .pfs={"Signals_Background","Year",cut},          .cuts={},.draw="COLZ",.opt=o_1or2d_s+"Log",.ranges={}});
    // Stack plots
    for (auto data : showdata ) {
      std::string signal = "StackPlotSignal";
      std::string opt  = (data=="Blind") ? o_stk_s_S : o_stk_d_S;
      if (region==Region::SR_Lep_1htop) {
        opt    = (data=="Blind") ? o_stk_s_T : o_stk_d_T;
        signal = "StackPlotTopSignal";
      } else if (region==Region::SR_Lep_V_0b) {
        opt    = (data=="Blind") ? o_stk_s_V : o_stk_d_V;
        signal = "StackPlotVSignal";
      } else if (region==Region::SR_Lep_H_b||region==Region::SR_Lep_H_0b) {
        opt    = (data=="Blind") ? o_stk_s_H : o_stk_d_H;
        signal = "StackPlotHSignal";
      }
      // Masses
      sh.AddHistos(  s+"hadtop", { .fill=c+"HadTopMass",              .pfs={signal,"Year",cut},               .cuts={},.draw=d,.opt=opt,.ranges=r_Stk8});
      sh.AddHistos(  s+"leptop", { .fill=c+"LepTopMass",              .pfs={signal,"Year",cut},               .cuts={},.draw=d,.opt=opt,.ranges=r_Stk8});
      sh.AddHistos(  s+"hadw",   { .fill=c+"HadWMass",                .pfs={signal,"Year",cut},               .cuts={},.draw=d,.opt=opt,.ranges=r_Stk8});
      sh.AddHistos(  s+"hadz",   { .fill=c+"HadZMass",                .pfs={signal,"Year",cut},               .cuts={},.draw=d,.opt=opt,.ranges=r_Stk8});
      sh.AddHistos(  s+"hadh",   { .fill=c+"HadHMass",                .pfs={signal,"Year",cut},               .cuts={},.draw=d,.opt=opt,.ranges=r_Stk8});
    }
  }


  // Non-isolated lepton Signal Regions
  for (auto region : {Region::SR_Leptop_0htop, Region::SR_Leptop_1htop, Region::SR_Lepjet_0V_24j, Region::SR_Lepjet_0V_5j, Region::SR_Lepjet_1V_24j, Region::SR_Lepjet_1V_5j}) {
    sh.SetHistoWeights({ [&w,region] { return w.sf_weight[region]; } });
    std::string cut(magic_enum::enum_name(region));
    std::vector<std::string> showdata = {"Blind"};
    // Signal discriminators
    sh.AddHistos("evt",    { .fill="MRFine_vs_METFine",         .pfs={"Signals_Background","Year",cut},          .cuts={},.draw="COLZ",.opt=o_1or2d_s+"Log",.ranges={}});
    sh.AddHistos("evt",    { .fill="R2Fine_vs_METFine",         .pfs={"Signals_Background","Year",cut},          .cuts={},.draw="COLZ",.opt=o_1or2d_s+"Log",.ranges={}});
    sh.AddHistos("evt",    { .fill="R2Fine_vs_MRFine",          .pfs={"Signals_Background","Year",cut},          .cuts={},.draw="COLZ",.opt=o_1or2d_s+"Log",.ranges={}});
    sh.AddHistos("evt",    { .fill="MRFine_vs_HTFine",          .pfs={"Signals_Background","Year",cut},          .cuts={},.draw="COLZ",.opt=o_1or2d_s+"Log",.ranges={}});
    sh.AddHistos("evt",    { .fill="METFine_vs_HTFine",         .pfs={"Signals_Background","Year",cut},          .cuts={},.draw="COLZ",.opt=o_1or2d_s+"Log",.ranges={}});
    sh.AddHistos("evt",    { .fill="R2Fine_vs_MRFine",          .pfs={"Signals_Background","Year",cut},          .cuts={},.draw="COLZ",.opt=o_1or2d_s+"Log",.ranges={}});
    sh.AddHistos("evt",    { .fill="MTBoost_vs_METFine",        .pfs={"Signals_Background","Year",cut},          .cuts={},.draw="COLZ",.opt=o_1or2d_s+"Log",.ranges={}});
    sh.AddHistos("evt",    { .fill="MTBoost_vs_R2Fine",         .pfs={"Signals_Background","Year",cut},          .cuts={},.draw="COLZ",.opt=o_1or2d_s+"Log",.ranges={}});
    sh.AddHistos("evt",    { .fill="MTBoost_vs_MRFine",         .pfs={"Signals_Background","Year",cut},          .cuts={},.draw="COLZ",.opt=o_1or2d_s+"Log",.ranges={}});
    // Stack plots
    for (auto data : showdata ) {
      std::string signal = "StackPlotSignal";
      std::string opt  = (data=="Blind") ? o_stk_s_S : o_stk_d_S;
      if (region==Region::SR_Leptop_0htop||region==Region::SR_Leptop_1htop) {
        opt    = (data=="Blind") ? o_stk_s_T : o_stk_d_T;
        signal = "StackPlotTopSignal";
      } else if (region==Region::SR_Lepjet_0V_24j||region==Region::SR_Lepjet_0V_5j||region==Region::SR_Lepjet_1V_24j||region==Region::SR_Lepjet_1V_5j) {
        opt    = (data=="Blind") ? o_stk_s_V : o_stk_d_V;
        signal = "StackPlotVSignal";
      }
      // Masses
      sh.AddHistos(  s+"hadtop", { .fill=c+"HadTopMass",               .pfs={signal,"Year",cut},               .cuts={},.draw=d,.opt=opt,.ranges=r_Stk8});
      sh.AddHistos(  s+"leptop", { .fill=c+"LepTopMass",               .pfs={signal,"Year",cut},               .cuts={},.draw=d,.opt=opt,.ranges=r_Stk8});
      sh.AddHistos(  s+"hadw",   { .fill=c+"HadWMass",                 .pfs={signal,"Year",cut},               .cuts={},.draw=d,.opt=opt,.ranges=r_Stk8});
      sh.AddHistos(  s+"hadz",   { .fill=c+"HadZMass",                 .pfs={signal,"Year",cut},               .cuts={},.draw=d,.opt=opt,.ranges=r_Stk8});
      sh.AddHistos(  s+"hadh",   { .fill=c+"HadHMass",                 .pfs={signal,"Year",cut},               .cuts={},.draw=d,.opt=opt,.ranges=r_Stk8});
    }
  }


  // -------------------------------------------------------------------------
  //                              Selected AK4 Jets

  for (const auto& regions : magic_enum::enum_entries<Region>()) {
    Region region = regions.first;
    std::string cut(regions.second);
    if (TString(cut).BeginsWith("CR_")||TString(cut).BeginsWith("Val_")||TString(cut).BeginsWith("Pre_")) {
      if (region==Region::CR_Fake)
        sh.SetHistoWeights({ [&w,region] { return w.w_nm1[region][9]*w.triggereff_had_nor2; } });
      else
        sh.SetHistoWeights({ [&w,region] { return w.sf_weight[region]; } });
      std::string opt = o_stk_d;
      sh.AddHistos(s+"AK4",  { .fill=c+"JetPtBins",                       .pfs={Stack,"Year",cut}, .cuts={},.draw=d,.opt=opt,.ranges=r_Stk9});
      sh.AddHistos(s+"AK4",  { .fill=c+"JetPt",                           .pfs={Stack,"Year",cut}, .cuts={},.draw=d,.opt=opt,.ranges=r_Stk9});
      sh.AddHistos(s+"AK4",  { .fill=c+"JetEta",                          .pfs={Stack,"Year",cut}, .cuts={},.draw=d,.opt=opt,.ranges=r_Stk9});
      sh.AddHistos(s+"AK4",  { .fill=c+"JetPhi",                          .pfs={Stack,"Year",cut}, .cuts={},.draw=d,.opt=opt,.ranges=r_Stk9});
      sh.AddHistos(s+"AK4",  { .fill=c+"JetDeepB",                        .pfs={Stack,"Year",cut}, .cuts={},.draw=d,.opt=opt,.ranges=r_Stk9});
      sh.AddHistos("AK4",    { .fill="JetPhotonDR",                       .pfs={Stack,"Year",cut}, .cuts={},.draw=d,.opt=opt,.ranges=r_Stk9});
      sh.AddHistos("AK4",    { .fill="JetPhotonPtRatio",                  .pfs={Stack,"Year",cut}, .cuts={},.draw=d,.opt=opt,.ranges=r_Stk9});
      sh.AddHistos("AK4",    { .fill="JetPhotonPtRatio",                  .pfs={Stack,"Year",cut,"JetPhotonDR0.05"}, .cuts={},.draw=d,.opt=opt,.ranges=r_Stk9});
      sh.AddHistos("AK4",    { .fill="JetPhotonPtRatio",                  .pfs={Stack,"Year",cut,"JetPhotonDR0.4"},  .cuts={},.draw=d,.opt=opt,.ranges=r_Stk9});
      sh.AddHistos("AK4",    { .fill="JetPhotonDR_vs_JetPhotonPtRatio",   .pfs={"Data_MC","Year",cut},  .cuts={},.draw="COLZ",.opt=o_1or2d_d, .ranges={}});
      sh.AddHistos("AK4",    { .fill="JetEleDR",                          .pfs={Stack,"Year",cut}, .cuts={},.draw=d,.opt=opt,.ranges=r_Stk9});
      sh.AddHistos("AK4",    { .fill="JetElePtRatio",                     .pfs={Stack,"Year",cut}, .cuts={},.draw=d,.opt=opt,.ranges=r_Stk9});
      sh.AddHistos("AK4",    { .fill="JetElePtRatio",                     .pfs={Stack,"Year",cut,"JetEleDR0.05"}, .cuts={},.draw=d,.opt=opt,.ranges=r_Stk9});
      sh.AddHistos("AK4",    { .fill="JetElePtRatio",                     .pfs={Stack,"Year",cut,"JetEleDR0.4"},  .cuts={},.draw=d,.opt=opt,.ranges=r_Stk9});
      sh.AddHistos("AK4",    { .fill="JetEleDR_vs_JetElePtRatio",         .pfs={"Data_MC","Year",cut},  .cuts={},.draw="COLZ",.opt=o_1or2d_d, .ranges={}});
      sh.AddHistos("AK4",    { .fill="JetMuonDR",                         .pfs={Stack,"Year",cut}, .cuts={},.draw=d,.opt=opt,.ranges=r_Stk9});
      sh.AddHistos("AK4",    { .fill="JetMuonPtRatio",                    .pfs={Stack,"Year",cut}, .cuts={},.draw=d,.opt=opt,.ranges=r_Stk9});
      sh.AddHistos("AK4",    { .fill="JetMuonPtRatio",                    .pfs={Stack,"Year",cut,"JetMuonDR0.05"}, .cuts={},.draw=d,.opt=opt,.ranges=r_Stk9});
      sh.AddHistos("AK4",    { .fill="JetMuonPtRatio",                    .pfs={Stack,"Year",cut,"JetMuonDR0.4"},  .cuts={},.draw=d,.opt=opt,.ranges=r_Stk9});
      sh.AddHistos("AK4",    { .fill="JetMuonDR_vs_JetMuonPtRatio",       .pfs={"Data_MC","Year",cut},  .cuts={},.draw="COLZ",.opt=o_1or2d_d, .ranges={}});
    }
  }

  // -------------------------------------------------------------------------
  //                                  Leptons
  
  // Leptons
  for (auto region : {Region::Pre, Region::CR_QCD17_1Boost, Region::CR_Top17_1Boost, Region::CR_W17_1Boost, Region::CR_1LepInv, Region::CR_1PhoInv, Region::Val_Signal, Region::Val_QCD}) {
  //for (auto region : {'S', Region::CR_QCD, Region::Val_Signal, Region::Val_QCD}) {
    sh.SetHistoWeights({ [&w,region] { return w.sf_weight[region]; } });
    std::string cut(magic_enum::enum_name(region));
    if (region==Region::CR_2LepInv)
      sh.SetHistoWeights({ [&w,region] { return w.w_nm1[region][9]*w.triggereff_lep; } });
    if (region==Region::CR_1PhoInv)
      sh.SetHistoWeights({ [&w,region] { return w.w_nm1[region][9]*w.triggereff_pho; } });
    if (region==Region::Pre) {
      sh.AddHistos(s+"evt",      { .fill=c+"NEleVeto",             .pfs={Stack,"Year",cut},                    .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
      sh.AddHistos(s+"ele veto", { .fill=c+"VetoElePt",            .pfs={Stack,"Year",cut},                    .cuts={},.draw=d,.opt=o_stk_d+"logX",.ranges=r_Stk6});
      sh.AddHistos(s+"ele veto", { .fill=c+"VetoEleEta",           .pfs={Stack,"Year",cut},                    .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
      sh.AddHistos(s+"evt",      { .fill=c+"NMuVeto",              .pfs={Stack,"Year",cut},                    .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
      sh.AddHistos(s+"mu veto",  { .fill=c+"VetoMuPt",             .pfs={Stack,"Year",cut},                    .cuts={},.draw=d,.opt=o_stk_d+"logX",.ranges=r_Stk6});
      sh.AddHistos(s+"mu veto",  { .fill=c+"VetoMuEta",            .pfs={Stack,"Year",cut},                    .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
      sh.AddHistos(s+"evt",      { .fill=c+"NLepVeto",             .pfs={Stack,"Year",cut},                    .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
      sh.AddHistos(s+"evt",      { .fill=c+"NIsoTrk",              .pfs={Stack,"Year",cut},                    .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
      sh.AddHistos(s+"evt",      { .fill=c+"NTauVeto",             .pfs={Stack,"Year",cut},                    .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
      sh.AddHistos(s+"tau veto", { .fill=c+"VetoTauPt",            .pfs={Stack,"Year",cut},                    .cuts={},.draw=d,.opt=o_stk_d+"logX",.ranges=r_Stk6});
      sh.AddHistos(s+"tau veto", { .fill=c+"VetoTauEta",           .pfs={Stack,"Year",cut},                    .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
      sh.AddHistos("ele tight noiso", { .fill="EleCleanJetDRmin",                     .pfs={"Signals_Background","Year",cut,"MatchGenEleFromTop"},  .cuts={},.draw="HIST",.opt=o_1or2d_s+"Log",.ranges={}});
      sh.AddHistos("ele tight noiso", { .fill="EleCleanJetPtrel",                     .pfs={"Signals_Background","Year",cut,"MatchGenEleFromTop"},  .cuts={},.draw="HIST",.opt=o_1or2d_s+"Log",.ranges={}});
      sh.AddHistos("ele tight noiso", { .fill="EleCleanJetPtrel_vs_EleCleanJetDRmin", .pfs={"Signals_Background","Year",cut,"MatchGenEleFromTop"},  .cuts={},.draw="COLZ",.opt=o_1or2d_s+"Log",.ranges={}});
      sh.AddHistos("mu tight noiso",  { .fill="MuCleanJetDRmin",                      .pfs={"Signals_Background","Year",cut,"MatchGenMuFromTop"},   .cuts={},.draw="HIST",.opt=o_1or2d_s+"Log",.ranges={}});
      sh.AddHistos("mu tight noiso",  { .fill="MuCleanJetPtrel",                      .pfs={"Signals_Background","Year",cut,"MatchGenMuFromTop"},   .cuts={},.draw="HIST",.opt=o_1or2d_s+"Log",.ranges={}});
      sh.AddHistos("mu tight noiso",  { .fill="MuCleanJetPtrel_vs_MuCleanJetDRmin",   .pfs={"Signals_Background","Year",cut,"MatchGenMuFromTop"},   .cuts={},.draw="COLZ",.opt=o_1or2d_s+"Log",.ranges={}});
    } else if (region==Region::CR_Top17_1Boost||region==Region::CR_W17_1Boost||region==Region::CR_1LepInv) {
      sh.AddHistos(s+"evt",      { .fill=c+"NEleVeto",             .pfs={Stack,"Year",cut+"_Excl1LepMT"},      .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
      sh.AddHistos(s+"ele veto", { .fill=c+"VetoElePt",            .pfs={Stack,"Year",cut},                    .cuts={},.draw=d,.opt=o_stk_d+"logX",.ranges=r_Stk6});
      sh.AddHistos(s+"ele veto", { .fill=c+"VetoEleEta",           .pfs={Stack,"Year",cut},                    .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
      sh.AddHistos(s+"evt",      { .fill=c+"NMuVeto",              .pfs={Stack,"Year",cut+"_Excl1LepMT"},      .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
      sh.AddHistos(s+"mu veto",  { .fill=c+"VetoMuPt",             .pfs={Stack,"Year",cut},                    .cuts={},.draw=d,.opt=o_stk_d+"logX",.ranges=r_Stk6});
      sh.AddHistos(s+"mu veto",  { .fill=c+"VetoMuEta",            .pfs={Stack,"Year",cut},                    .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
      sh.AddHistos(s+"evt",      { .fill=c+"NLepVeto",             .pfs={Stack,"Year",cut+"_Excl1LepMT"},      .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
    } else {
      std::string opt = o_stk_d;
      sh.AddHistos(s+"evt",      { .fill=c+"NEleVeto",             .pfs={Stack,"Year",cut+"_Excl0Ele0Tau"}, .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
      sh.AddHistos(s+"ele veto", { .fill=c+"VetoElePt",            .pfs={Stack,"Year",cut+"_Excl0Ele0Tau"}, .cuts={},.draw=d,.opt=o_stk_d+"logX",.ranges=r_Stk6});
      sh.AddHistos(s+"ele veto", { .fill=c+"VetoEleEta",           .pfs={Stack,"Year",cut+"_Excl0Ele0Tau"}, .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
      sh.AddHistos(s+"evt",      { .fill=c+"NMuVeto",              .pfs={Stack,"Year",cut+"_Excl0Mu0Tau"},  .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
      sh.AddHistos(s+"mu veto",  { .fill=c+"VetoMuPt",             .pfs={Stack,"Year",cut+"_Excl0Mu0Tau"},  .cuts={},.draw=d,.opt=o_stk_d+"logX",.ranges=r_Stk6});
      sh.AddHistos(s+"mu veto",  { .fill=c+"VetoMuEta",            .pfs={Stack,"Year",cut+"_Excl0Mu0Tau"},  .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
      sh.AddHistos(s+"evt",      { .fill=c+"NLepVeto",             .pfs={Stack,"Year",cut+"_Excl0Ele0Mu0Tau"}, .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
      sh.AddHistos(s+"evt",      { .fill=c+"NIsoTrk",              .pfs={Stack,"Year",cut+"_Excl0Tau"},  .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
      sh.AddHistos(s+"evt",      { .fill=c+"NTauVeto",             .pfs={Stack,"Year",cut+"_Excl0Tau"},  .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
      sh.AddHistos(s+"tau veto", { .fill=c+"VetoTauPt",            .pfs={Stack,"Year",cut+"_Excl0Tau"},  .cuts={},.draw=d,.opt=o_stk_d+"logX",.ranges=r_Stk6});
      sh.AddHistos(s+"tau veto", { .fill=c+"VetoTauEta",           .pfs={Stack,"Year",cut+"_Excl0Tau"},  .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
    }
  }

  // Selected Leptons
  for (auto region : {Region::Pre, Region::CR_2LepInv}) {
  //for (auto region : {Region::CR_2LepInv, Region::CR_Top, Region::CR_W}) {
    sh.SetHistoWeights({ [&w,region] { return w.sf_weight[region]; } });
    if (region==Region::CR_2LepInv)
      sh.SetHistoWeights({ [&w,region] { return w.w_nm1[region][9]*w.triggereff_lep; } });
    std::string cut(magic_enum::enum_name(region));
    std::string cut2 = cut;
    if (region==Region::CR_2LepInv) cut2 += "_Excl2LepR2";
    //else cut2 += "_Excl1LepMT";

    sh.AddHistos(s+"evt",  { .fill=c+"ElePt",                      .pfs={Stack,"Year",cut},  .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
    sh.AddHistos(s+"evt",  { .fill=c+"EleEta",                     .pfs={Stack,"Year",cut},  .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
    sh.AddHistos(s+"evt",  { .fill=c+"MuPt",                       .pfs={Stack,"Year",cut},  .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
    sh.AddHistos(s+"evt",  { .fill=c+"MuEta",                      .pfs={Stack,"Year",cut},  .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
    
    sh.AddHistos(s+"evt",  { .fill=c+"NLep",                       .pfs={Stack,"Year",cut2}, .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
    sh.AddHistos(s+"evt",  { .fill=c+"NEle",                       .pfs={Stack,"Year",cut2}, .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
    sh.AddHistos(s+"evt",  { .fill=c+"NMu",                        .pfs={Stack,"Year",cut2}, .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
    sh.AddHistos(s+"evt",  { .fill=c+"NLepTight",                  .pfs={Stack,"Year",cut2}, .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
    sh.AddHistos(s+"evt",  { .fill=c+"NLepNoIso",                  .pfs={Stack,"Year",cut2}, .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
    sh.AddHistos(s+"evt",  { .fill=c+"NEleNoIso",                  .pfs={Stack,"Year",cut2}, .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
    sh.AddHistos(s+"evt",  { .fill=c+"NMuNoIso",                   .pfs={Stack,"Year",cut2}, .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
    sh.AddHistos(s+"evt",  { .fill=c+"NLepNonIso",                 .pfs={Stack,"Year",cut2}, .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
    sh.AddHistos(s+"evt",  { .fill=c+"NEleNonIso",                 .pfs={Stack,"Year",cut2}, .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
    sh.AddHistos(s+"evt",  { .fill=c+"NMuNonIso",                  .pfs={Stack,"Year",cut2}, .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
  }


  // -------------------------------------------------------------------------
  //                                     bs

  // Selected b-tags
  for (auto region : {Region::Pre, Region::CR_Top17_1Boost, Region::CR_2LepInv, Region::CR_1PhoInv, Region::Val_Signal}) {
    sh.SetHistoWeights({ [&w,region] { return w.sf_weight[region]; } });
    if (region==Region::CR_2LepInv)
      sh.SetHistoWeights({ [&w,region] { return w.w_nm1[region][9]*w.triggereff_lep; } });
    if (region==Region::CR_1PhoInv)
      sh.SetHistoWeights({ [&w,region] { return w.w_nm1[region][9]*w.triggereff_pho; } });
    
    std::string cut1(magic_enum::enum_name(region));
    std::string cut2 = cut1;
    //if (region==Region::Pre||region==Region::CR_2LepInv||region==Region::CR_1PhoInv) 
    //  sh.SetHistoWeights({ [&w,region] { return w.sf_weight[region]*scale_factors['S'][2]; } });
    //if (region=='S'||region==Region::Val_Signal||region==Region::CR_Top) cut2 += "_Excl1b";
    std::string opt = o_stk_d;
    sh.AddHistos(s+"b",    { .fill=c+"BJetPtBins",          .pfs={Stack,"Year",cut1}, .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
    sh.AddHistos(s+"b",    { .fill=c+"BJetPt",              .pfs={Stack,"Year",cut1}, .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
    sh.AddHistos(s+"b",    { .fill=c+"BJetEta",             .pfs={Stack,"Year",cut1}, .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
    sh.AddHistos(s+"b",    { .fill=c+"BJetPhi",             .pfs={Stack,"Year",cut1}, .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
    sh.AddHistos(s+"b",    { .fill=c+"BJetDeepB",           .pfs={Stack,"Year",cut1}, .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
    sh.AddHistos(s+"evt",  { .fill=c+"NBTag",               .pfs={Stack,"Year",cut1}, .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
    //if (region!=Region::Pre&&region!=Region::CR_2LepInv&&region!=Region::CR_1PhoInv)
    //	sh.AddHistos(s+"evt",  { .fill=c+"NBTag",               .pfs={Stack,"Year",cut2}, .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
  }

  // Veto b-tags
  for (auto region : {Region::Pre, Region::CR_QCD17_1Boost, Region::CR_W17_1Boost, Region::CR_1LepInv, Region::CR_2LepInv, Region::CR_1PhoInv, Region::Val_QCD}) {
    sh.SetHistoWeights({ [&w,region] { return w.sf_weight[region]; } });
    if (region==Region::CR_2LepInv)
      sh.SetHistoWeights({ [&w,region] { return w.w_nm1[region][9]*w.triggereff_lep; } });
    if (region==Region::CR_1PhoInv)
      sh.SetHistoWeights({ [&w,region] { return w.w_nm1[region][9]*w.triggereff_pho; } });
    std::string cut1(magic_enum::enum_name(region));
    //std::string cut2 = cut1;
    //if (region==Region::CR_QCD||region==Region::Val_QCD||region==Region::CR_W||region==Region::CR_1LepInv) cut2 += "_Excl0b";
    sh.AddHistos(s+"evt",  { .fill=c+"NLooseBTag",          .pfs={Stack,"Year",cut1}, .cuts={},.draw=d,.opt=O_stk_d+"NoComb5",.ranges={0,0, 1.01e-2,1e6,  0.5,0.86}});
    //if (region!=Region::Pre&&region!=Region::CR_2LepInv&&region!=Region::CR_1PhoInv)
    //  sh.AddHistos(s+"evt",  { .fill=c+"NLooseBTag",          .pfs={Stack,"Year",cut2}, .cuts={},.draw=d,.opt=O_stk_d+"NoComb5",.ranges={0,0, 1.01e-2,1e6,  0.5,0.86}});
  }

  // -------------------------------------------------------------------------
  //                                 AK8/Ws Jets

  for (auto region : {Region::Pre, Region::CR_Top17_1Boost,Region::CR_W17_1Boost,Region::CR_QCD17_1Boost, Region::CR_1LepInv, Region::CR_2LepInv, Region::CR_1PhoInv, Region::CR_Fake, Region::Val_Signal, Region::Val_QCD}) {
    sh.SetHistoWeights({ [&w,region] { return w.sf_weight[region]; } });
    if (region==Region::CR_2LepInv)
      sh.SetHistoWeights({ [&w,region] { return w.w_nm1[region][9]*w.triggereff_lep; } });
    if (region==Region::CR_1PhoInv)
      sh.SetHistoWeights({ [&w,region] { return w.w_nm1[region][9]*w.triggereff_pho; } });
    std::string cut1(magic_enum::enum_name(region));
    //std::string cut2 = cut1;
    //if      (region==Region::Val_Signal||region==Region::CR_Top) cut2 += "_Excl1W";
    //else if (region==Region::CR_QCD||region==Region::Val_QCD) cut2 += "_Excl1aW";
    //else if (region==Region::CR_W) cut2 += "_Excl1mW";
    //else if (region==Region::CR_1LepInv||region==Region::CR_2LepInv||region==Region::CR_1PhoInv) cut2 += "_Excl1mW";
    std::vector<std::string> cuts;
    cuts.push_back(cut1);
    //if (cut2!=cut1) cuts.push_back(cut2);
    for (auto cut : cuts) {
      std::string opt = o_stk_d;
      std::string Opt = O_stk_d;
      // AK8 jets
      sh.AddHistos(s+"evt",  { .fill=c+"NJetAK8",            .pfs={Stack,"Year",cut},               .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
      sh.AddHistos(s+"AK8",  { .fill=c+"JetAK8PtBins",       .pfs={Stack,"Year",cut},               .cuts={},.draw=d,.opt=opt,.ranges=r_Stk8});
      sh.AddHistos(s+"AK8",  { .fill=c+"JetAK8Pt",           .pfs={Stack,"Year",cut},               .cuts={},.draw=d,.opt=opt,.ranges=r_Stk8});
      sh.AddHistos(s+"AK8",  { .fill=c+"JetAK8Eta",          .pfs={Stack,"Year",cut},               .cuts={},.draw=d,.opt=opt,.ranges=r_Stk8});
      sh.AddHistos(s+"AK8",  { .fill=c+"JetAK8Phi",          .pfs={Stack,"Year",cut},               .cuts={},.draw=d,.opt=opt,.ranges=r_Stk8});
      sh.AddHistos(s+"AK8",  { .fill=c+"JetAK8Mass",         .pfs={Stack,"Year",cut},               .cuts={},.draw=d,.opt=opt,.ranges=r_Stk8});
      sh.AddHistos(s+"AK8",  { .fill=c+"JetAK8Mass",         .pfs={Stack,"Year",cut,"Tau21Tagged"}, .cuts={},.draw=d,.opt=Opt,.ranges={0,0, 1.01e-2,1e8,  0.3,0.86, 0.21}});
      sh.AddHistos(s+"AK8",  { .fill=c+"JetAK8Mass",         .pfs={Stack,"Year",cut,"Tau32Tagged"}, .cuts={},.draw=d,.opt=Opt,.ranges={0,0, 1.01e-2,1e8,  0.3,0.86}});
      sh.AddHistos(s+"AK8",  { .fill=c+"JetAK8Mass",         .pfs={Stack,"Year",cut,"AK8_EB_EE"},               .cuts={},.draw=d,.opt=opt,.ranges=r_Stk8});
      //sh.AddHistos(s+"AK8",  { .fill=c+"JetAK8Mass",         .pfs={Stack,"Year",cut,"AK8_EB_EE","Tau21Tagged"}, .cuts={},.draw=d,.opt=opt,.ranges=r_Stk8});
      //sh.AddHistos(s+"AK8",  { .fill=c+"JetAK8Mass",         .pfs={Stack,"Year",cut,"AK8_EB_EE","Tau32Tagged"}, .cuts={},.draw=d,.opt=opt,.ranges=r_Stk8});
      sh.AddHistos(s+"AK8",  { .fill=c+"JetAK8Tau21",        .pfs={Stack,"Year",cut},               .cuts={},.draw=d,.opt=opt,.ranges=r_Stk8});
      sh.AddHistos(s+"AK8",  { .fill=c+"JetAK8Tau32",        .pfs={Stack,"Year",cut},               .cuts={},.draw=d,.opt=opt,.ranges=r_Stk8});
      sh.AddHistos(s+"AK8",  { .fill=c+"MaxAK8SubJetDeepB",  .pfs={Stack,"Year",cut},               .cuts={},.draw=d,.opt=opt,.ranges=r_Stk8});
      sh.AddHistos("AK8",    { .fill="JetAK8PhotonDR",       .pfs={Stack,"Year",cut},               .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
      sh.AddHistos("AK8",    { .fill="JetAK8PhotonPtRatio",  .pfs={Stack,"Year",cut},               .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
      sh.AddHistos("AK8",    { .fill="JetAK8PhotonPtRatio",  .pfs={Stack,"Year",cut,"JetAK8PhotonDR0.05"}, .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
      sh.AddHistos("AK8",    { .fill="JetAK8PhotonPtRatio",  .pfs={Stack,"Year",cut,"JetAK8PhotonDR0.8"}, .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
      sh.AddHistos("AK8",    { .fill="JetAK8PhotonDR_vs_JetAK8PhotonPtRatio", .pfs={"Data_MC","Year",cut},  .cuts={},.draw="COLZ",.opt=o_1or2d_d, .ranges={}});
      sh.AddHistos("AK8",    { .fill="JetAK8EleDR",          .pfs={Stack,"Year",cut},               .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
      sh.AddHistos("AK8",    { .fill="JetAK8ElePtRatio",     .pfs={Stack,"Year",cut},               .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
      sh.AddHistos("AK8",    { .fill="JetAK8ElePtRatio",     .pfs={Stack,"Year",cut,"JetAK8EleDR0.05"}, .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
      sh.AddHistos("AK8",    { .fill="JetAK8ElePtRatio",     .pfs={Stack,"Year",cut,"JetAK8EleDR0.8"}, .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
      sh.AddHistos("AK8",    { .fill="JetAK8EleDR_vs_JetAK8ElePtRatio", .pfs={"Data_MC","Year",cut},  .cuts={},.draw="COLZ",.opt=o_1or2d_d, .ranges={}});
      sh.AddHistos("AK8",    { .fill="JetAK8MuonDR",         .pfs={Stack,"Year",cut},               .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
      sh.AddHistos("AK8",    { .fill="JetAK8MuonPtRatio",    .pfs={Stack,"Year",cut},               .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
      sh.AddHistos("AK8",    { .fill="JetAK8MuonPtRatio",    .pfs={Stack,"Year",cut,"JetAK8MuonDR0.05"}, .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
      sh.AddHistos("AK8",    { .fill="JetAK8MuonPtRatio",    .pfs={Stack,"Year",cut,"JetAK8MuonDR0.8"}, .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
      sh.AddHistos("AK8",    { .fill="JetAK8MuonDR_vs_JetAK8MuonPtRatio", .pfs={"Data_MC","Year",cut},  .cuts={},.draw="COLZ",.opt=o_1or2d_d, .ranges={}});

      // Deep AK8 tagger plots
      sh.AddHistos(s+"AK8",  { .fill=c+"JetAK8DeepTagTvsQCD",    .pfs={Stack,"Year",cut},               .cuts={},.draw=d,.opt=opt,.ranges=r_Stk8});
      sh.AddHistos(s+"AK8",  { .fill=c+"JetAK8DeepTagWvsQCD",    .pfs={Stack,"Year",cut},               .cuts={},.draw=d,.opt=opt,.ranges=r_Stk8});
      sh.AddHistos(s+"AK8",  { .fill=c+"JetAK8DeepTagZvsQCD",    .pfs={Stack,"Year",cut},               .cuts={},.draw=d,.opt=opt,.ranges=r_Stk8});
      sh.AddHistos(s+"AK8",  { .fill=c+"JetAK8DeepTagMDHbbvsQCD",.pfs={Stack,"Year",cut},               .cuts={},.draw=d,.opt=opt,.ranges=r_Stk8});
      sh.AddHistos(s+"AK8",  { .fill=c+"JetAK8DeepTagMDWvsQCD",  .pfs={Stack,"Year",cut},               .cuts={},.draw=d,.opt=opt,.ranges=r_Stk8});
      sh.AddHistos(s+"AK8",  { .fill=c+"JetAK8DeepTagMDTvsQCD",  .pfs={Stack,"Year",cut},               .cuts={},.draw=d,.opt=opt,.ranges=r_Stk8});

      // Tagged Ws
      // Add W scale factor
      sh.AddHistos(s+"hadw",    { .fill=c+"WPtBins",            .pfs={Stack,"Year",cut},               .cuts={},.draw=d,.opt=opt,.ranges=r_Stk4});
      sh.AddHistos(s+"hadw",    { .fill=c+"WPt",                .pfs={Stack,"Year",cut},               .cuts={},.draw=d,.opt=opt,.ranges=r_Stk4});
      sh.AddHistos(s+"hadw",    { .fill=c+"WEta",               .pfs={Stack,"Year",cut},               .cuts={},.draw=d,.opt=opt,.ranges=r_Stk4});
      sh.AddHistos(s+"hadw",    { .fill=c+"WPhi",               .pfs={Stack,"Year",cut},               .cuts={},.draw=d,.opt=opt,.ranges=r_Stk4});
      sh.AddHistos(s+"hadw",    { .fill=c+"WTau21",             .pfs={Stack,"Year",cut},               .cuts={},.draw=d,.opt=Opt,.ranges=r_Stk4});
      sh.AddHistos(s+"hadw",    { .fill=c+"WMass",              .pfs={Stack,"Year",cut},               .cuts={},.draw=d,.opt=opt,.ranges=r_Stk4});
        
      // Tagged tops
      // Add top scale factor
      sh.AddHistos(s+"hadtop",  { .fill=c+"TopPtBins",          .pfs={Stack,"Year",cut},               .cuts={},.draw=d,.opt=opt,.ranges=r_Stk4});
      sh.AddHistos(s+"hadtop",  { .fill=c+"TopPt",              .pfs={Stack,"Year",cut},               .cuts={},.draw=d,.opt=opt,.ranges=r_Stk4});
      sh.AddHistos(s+"hadtop",  { .fill=c+"TopEta",             .pfs={Stack,"Year",cut},               .cuts={},.draw=d,.opt=opt,.ranges=r_Stk4});
      sh.AddHistos(s+"hadtop",  { .fill=c+"TopPhi",             .pfs={Stack,"Year",cut},               .cuts={},.draw=d,.opt=opt,.ranges=r_Stk4});
      sh.AddHistos(s+"hadtop",  { .fill=c+"TopTau32",           .pfs={Stack,"Year",cut},               .cuts={},.draw=d,.opt=opt,.ranges=r_Stk4});
      sh.AddHistos(s+"hadtop",  { .fill=c+"TopMass",            .pfs={Stack,"Year",cut},               .cuts={},.draw=d,.opt=opt,.ranges=r_Stk4});
    }
  }
*/
  
  //std::cout<<"-------------------------------------------------------"<<std::endl;
  //std::cout<<"  Total cell count for each SmartHisto:"<<std::endl;
  //sh.GetTotalNCells();
  //std::cout<<"-------------------------------------------------------"<<std::endl;
}

#endif // End header guard
