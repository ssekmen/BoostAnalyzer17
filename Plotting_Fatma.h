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
        signal = "StackPlotHSignal";
        //signal = "StackPlotVSignal";

      } else if (region==Region::SR_Had_H_b_45j||region==Region::SR_Had_H_b_6j||region==Region::SR_Had_2H_b_6j||region==Region::SR_Had_HV_b_6j||
                 region==Region::SR_Had_1H_0b_34j||region==Region::SR_Had_1H_0b_5j||region==Region::SR_Had_2H_0b_34j||region==Region::SR_Had_2H_0b_5j||
                 region==Region::SR_Had_HV_0b_24j||region==Region::SR_Had_HV_0b_5j) {
        opt    = (data=="Blind") ? o_stk_s_H : o_stk_d_H;
        signal = "StackPlotVSignal";
        //signal = "StackPlotHSignal";
      
      }

    

      // Masses
      sh.AddHistos(  s+"hadtop", { .fill=c+"HadTopMass",              .pfs={signal,"Year",cut},               .cuts={},.draw=d,.opt=opt,.ranges=r_Stk5});
      sh.AddHistos(  s+"leptop", { .fill=c+"LepTopMass",              .pfs={signal,"Year",cut},               .cuts={},.draw=d,.opt=opt,.ranges=r_Stk5});
      sh.AddHistos(  s+"hadw",   { .fill=c+"HadWMass",                .pfs={signal,"Year",cut},               .cuts={},.draw=d,.opt=opt,.ranges=r_Stk5});
      sh.AddHistos(  s+"hadz",   { .fill=c+"HadZMass",                .pfs={signal,"Year",cut},               .cuts={},.draw=d,.opt=opt,.ranges=r_Stk5});
      sh.AddHistos(  s+"hadh",   { .fill=c+"HadHMass",                .pfs={signal,"Year",cut},               .cuts={},.draw=d,.opt=opt,.ranges=r_Stk5});
    }
  }

  // -------------------------------------------------------------------------
  //                                  Leptons

  // Selected Leptons
  for (auto region : {Region::Pre, Region::CR_2LepInv, Region::CR_DiLep}) {
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
  for (auto region : {Region::Pre, Region::CR_Top17_1Boost, Region::CR_2LepInv, Region::CR_DiLep, Region::CR_1PhoInv, Region::Val_Signal}) {
    sh.SetHistoWeights({ [&w,region] { return w.sf_weight[region]; } });
    if (region==Region::CR_2LepInv)
      sh.SetHistoWeights({ [&w,region] { return w.w_nm1[region][9]*w.triggereff_lep; } });
    if (region==Region::CR_1PhoInv&&v.year!=2016)
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
  for (auto region : {Region::Pre, Region::CR_QCD17_1Boost, Region::CR_W17_1Boost, Region::CR_1LepInv, Region::CR_1LepInv_LepTrig, Region::CR_2LepInv, Region::CR_DiLep, Region::CR_1PhoInv, Region::Val_QCD}) {
    sh.SetHistoWeights({ [&w,region] { return w.sf_weight[region]; } });
    if (region==Region::CR_2LepInv||region==Region::CR_1LepInv_LepTrig)
      sh.SetHistoWeights({ [&w,region] { return w.w_nm1[region][9]*w.triggereff_lep; } });
    if (region==Region::CR_1PhoInv&&v.year!=2016)
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

  for (auto region : {Region::Pre, Region::CR_Top17_1Boost,Region::CR_W17_1Boost,Region::CR_QCD17_1Boost, Region::CR_1LepInv, Region::CR_1LepInv_LepTrig, Region::CR_2LepInv, Region::CR_DiLep, Region::CR_1PhoInv, Region::CR_Fake, Region::CR_Fake_MET100, Region::Val_Signal, Region::Val_QCD}) {
    sh.SetHistoWeights({ [&w,region] { return w.sf_weight[region]; } });
    if (region==Region::CR_2LepInv||region==Region::CR_1LepInv_LepTrig)
      sh.SetHistoWeights({ [&w,region] { return w.w_nm1[region][9]*w.triggereff_lep; } });
    if (region==Region::CR_1PhoInv&&v.year!=2016)
      sh.SetHistoWeights({ [&w,region] { return w.w_nm1[region][9]*w.triggereff_pho; } });
    if (region==Region::CR_Fake||region==Region::CR_Fake_MET100)
      sh.SetHistoWeights({ [&w,region] { return w.w_nm1[region][9]*w.triggereff_had_nor2; } });
    std::string cut1(magic_enum::enum_name(region));
    //std::string cut2 = cut1;
    //if      (region==Region::Val_Signal||region==Region::CR_Top) cut2 += "_Excl1W";
    //else if (region==Region::CR_QCD||region==Region::Val_QCD) cut2 += "_Excl1aW";
    //else if (region==Region::CR_W) cut2 += "_Excl1mW";
    //else if (region==Region::CR_1LepInv||region==Region::CR_2LepInv||region==Region::CR_1PhoInv) cut2 += "_Excl1mW";
    std::vector<std::string> cuts;
    cuts.push_back(cut1);
    //if (cut2!=cut1) cuts.push_back(cut2);


  //std::cout<<"-------------------------------------------------------"<<std::endl;
  //std::cout<<"  Total cell count for each SmartHisto:"<<std::endl;
  //sh.GetTotalNCells();
  //std::cout<<"-------------------------------------------------------"<<std::endl;
}
}

#endif // End header guard
