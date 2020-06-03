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

  // ----------------------------------------------------------------------------------------------
  //                                    New signal segions
  //-----------------------------------------------------------------------------------------------

  // Fully hadronic Signal Regions
  for (auto region : {
    Region::SR_Had_1htop, Region::SR_Had_2htop, Region::SR_Had_V_b_45j, Region::SR_Had_V_b_6j, Region::SR_Had_1V_0b_34j, Region::SR_Had_1V_0b_5j, Region::SR_Had_2V_0b_24j,
    Region::SR_Had_2V_0b_5j, Region::SR_Had_H_b_45j, Region::SR_Had_H_b_6j, Region::SR_Had_2H_b_6j, Region::SR_Had_HV_b_6j, Region::SR_Had_1H_0b_34j, Region::SR_Had_1H_0b_5j,
    Region::SR_Had_2H_0b_34j, Region::SR_Had_2H_0b_5j, Region::SR_Had_HV_0b_24j, Region::SR_Had_HV_0b_5j}) {
    sh.SetHistoWeights({ [&w,region] { return w.sf_weight[region]; } });
    std::string cut(magic_enum::enum_name(region));
    std::vector<std::string> showdata = {"Blind"};
    // Background study //TODO
//     // Reco measurments
//     sh.AddHistos("ele",        { .fill="EleEta",                    .pfs={"Signals_Background","Year",cut},          .cuts={},.draw="HIST",.opt=o_1or2d_s+"Norm",.ranges={}}); 
//     sh.AddHistos("ele",        { .fill="ElePt",                     .pfs={"Signals_Background","Year",cut},          .cuts={},.draw="HIST",.opt=o_1or2d_s+"Norm",.ranges={}}); 
//     sh.AddHistos("mu",         { .fill="MuEta",                     .pfs={"Signals_Background","Year",cut},          .cuts={},.draw="HIST",.opt=o_1or2d_s+"Norm",.ranges={}}); 
//     sh.AddHistos("mu",         { .fill="MuPt",                      .pfs={"Signals_Background","Year",cut},          .cuts={},.draw="HIST",.opt=o_1or2d_s+"Norm",.ranges={}}); 
//     
//     sh.AddHistos("ele veto",   { .fill="VetoEleEta",                .pfs={"Signals_Background","Year",cut},          .cuts={},.draw="HIST",.opt=o_1or2d_s+"Norm",.ranges={}}); 
//     sh.AddHistos("ele veto",   { .fill="VetoElePt",                 .pfs={"Signals_Background","Year",cut},          .cuts={},.draw="HIST",.opt=o_1or2d_s+"Norm",.ranges={}}); 
//     sh.AddHistos("mu veto",    { .fill="VetoMuEta",                 .pfs={"Signals_Background","Year",cut},          .cuts={},.draw="HIST",.opt=o_1or2d_s+"Norm",.ranges={}});
//     sh.AddHistos("mu veto",    { .fill="VetoMuPt",                  .pfs={"Signals_Background","Year",cut},          .cuts={},.draw="HIST",.opt=o_1or2d_s+"Norm",.ranges={}});
//     sh.AddHistos("tau veto",   { .fill="VetoTauEta",                .pfs={"Signals_Background","Year",cut},          .cuts={},.draw="HIST",.opt=o_1or2d_s+"Norm",.ranges={}}); 
//     sh.AddHistos("tau veto",   { .fill="VetoTauPt",                 .pfs={"Signals_Background","Year",cut},          .cuts={},.draw="HIST",.opt=o_1or2d_s+"Norm",.ranges={}}); 
//     
//     // Gen truth
//     sh.AddHistos("gen lep",    { .fill="GenLepEta",.pfs={"Signals_Background","Year",cut,"GenLepMother","GenLeptonFlavour"}, .cuts={},.draw="HIST",.opt=o_1or2d_s+"Norm",.ranges={}}); 
//     sh.AddHistos("gen lep",    { .fill="GenLepPtBins",.pfs={"Signals_Background","Year",cut,"GenLepMother","GenLeptonFlavour"}, .cuts={},.draw="HIST",.opt=o_1or2d_s+"Norm",.ranges={}}); 
//     
//     sh.AddHistos("gen hadw",   { .fill="GenHadWEta",.pfs={"Signals_Background","Year",cut}, .cuts={},.draw="HIST",.opt=o_1or2d_s+"Norm",.ranges={}});
//     sh.AddHistos("gen hadw",   { .fill="GenHadWPtBins",.pfs={"Signals_Background","Year",cut}, .cuts={},.draw="HIST",.opt=o_1or2d_s+"Norm",.ranges={}});
// 
//     sh.AddHistos("gen hadtop", { .fill="GenTopEta",.pfs={"Signals_Background","Year",cut}, .cuts={},.draw="HIST",.opt=o_1or2d_s+"Norm",.ranges={}});
//     sh.AddHistos("gen hadtop", { .fill="GenTopPtBins",.pfs={"Signals_Background","Year",cut}, .cuts={},.draw="HIST",.opt=o_1or2d_s+"Norm",.ranges={}});
//     sh.AddHistos("gen leptop", { .fill="GenLepTopMatchedGenLepEta",.pfs={"Signals_Background","Year",cut,"GenTopLeptonFlavour"}, .cuts={},.draw="HIST",.opt=o_1or2d_s+"Norm",.ranges={}});
//     sh.AddHistos("gen leptop", { .fill="GenLepTopMatchedGenLepPtBins",.pfs={"Signals_Background","Year",cut,"GenTopLeptonFlavour"}, .cuts={},.draw="HIST",.opt=o_1or2d_s+"Norm",.ranges={}});
//     sh.AddHistos("evt",    { .fill="NGenEleAndMuFrom2Tops",.pfs={"Signals_Background","Year",cut}, .cuts={},.draw="HIST",.opt=o_1or2d_s+"Norm",.ranges={}});
//     sh.AddHistos("evt",    { .fill="NGenEleAndMuAndTauFrom2Tops",.pfs={"Signals_Background","Year",cut}, .cuts={},.draw="HIST",.opt=o_1or2d_s+"Norm",.ranges={}});
    sh.AddHistos("evt",    { .fill="NGenEleAndMuFrom2Tops",.pfs={"Signals_Background","Year",cut}, .cuts={},.draw="HIST",.opt=o_1or2d_s,.ranges={}});
    sh.AddHistos("evt",    { .fill="NGenEleAndMuAndTauFrom2Tops",.pfs={"Signals_Background","Year",cut}, .cuts={},.draw="HIST",.opt=o_1or2d_s,.ranges={}});
//     sh.AddHistos("evt",    { .fill="NGenEleAndMuFrom1Top",.pfs={"Signals_Background","Year",cut}, .cuts={},.draw="HIST",.opt=o_1or2d_s+"Norm",.ranges={}});
//     sh.AddHistos("evt",    { .fill="NGenEleAndMuAndTauFrom1Top",.pfs={"Signals_Background","Year",cut}, .cuts={},.draw="HIST",.opt=o_1or2d_s+"Norm",.ranges={}});
    //end of background study 
  }


  // Isolated lepton Signal Regions
  for (auto region : {Region::SR_Lep_1htop, Region::SR_Lep_V_b, Region::SR_Lep_V_0b, Region::SR_Lep_H_b, Region::SR_Lep_H_0b}) {
    sh.SetHistoWeights({ [&w,region] { return w.sf_weight[region]; } });
    std::string cut(magic_enum::enum_name(region));
    std::vector<std::string> showdata = {"Blind"};
    // Signal discriminators
    // Background study //TODO
//     // Reco measurments
//     sh.AddHistos("ele",        { .fill="EleEta",                    .pfs={"Signals_Background","Year",cut},          .cuts={},.draw="HIST",.opt=o_1or2d_s+"Norm",.ranges={}}); 
//     sh.AddHistos("ele",        { .fill="ElePt",                     .pfs={"Signals_Background","Year",cut},          .cuts={},.draw="HIST",.opt=o_1or2d_s+"Norm",.ranges={}}); 
//     sh.AddHistos("mu",         { .fill="MuEta",                     .pfs={"Signals_Background","Year",cut},          .cuts={},.draw="HIST",.opt=o_1or2d_s+"Norm",.ranges={}}); 
//     sh.AddHistos("mu",         { .fill="MuPt",                      .pfs={"Signals_Background","Year",cut},          .cuts={},.draw="HIST",.opt=o_1or2d_s+"Norm",.ranges={}}); 
//     
//     sh.AddHistos("ele veto",   { .fill="VetoEleEta",                .pfs={"Signals_Background","Year",cut},          .cuts={},.draw="HIST",.opt=o_1or2d_s+"Norm",.ranges={}}); 
//     sh.AddHistos("ele veto",   { .fill="VetoElePt",                 .pfs={"Signals_Background","Year",cut},          .cuts={},.draw="HIST",.opt=o_1or2d_s+"Norm",.ranges={}}); 
//     sh.AddHistos("mu veto",    { .fill="VetoMuEta",                 .pfs={"Signals_Background","Year",cut},          .cuts={},.draw="HIST",.opt=o_1or2d_s+"Norm",.ranges={}});
//     sh.AddHistos("mu veto",    { .fill="VetoMuPt",                  .pfs={"Signals_Background","Year",cut},          .cuts={},.draw="HIST",.opt=o_1or2d_s+"Norm",.ranges={}});
//     sh.AddHistos("tau veto",   { .fill="VetoTauEta",                .pfs={"Signals_Background","Year",cut},          .cuts={},.draw="HIST",.opt=o_1or2d_s+"Norm",.ranges={}}); 
//     sh.AddHistos("tau veto",   { .fill="VetoTauPt",                 .pfs={"Signals_Background","Year",cut},          .cuts={},.draw="HIST",.opt=o_1or2d_s+"Norm",.ranges={}}); 
//     
//     // Gen truth
//     sh.AddHistos("gen lep",    { .fill="GenLepEta",.pfs={"Signals_Background","Year",cut,"GenLepMother","GenLeptonFlavour"}, .cuts={},.draw="HIST",.opt=o_1or2d_s+"Norm",.ranges={}}); 
//     sh.AddHistos("gen lep",    { .fill="GenLepPtBins",.pfs={"Signals_Background","Year",cut,"GenLepMother","GenLeptonFlavour"}, .cuts={},.draw="HIST",.opt=o_1or2d_s+"Norm",.ranges={}}); 
//     
//     sh.AddHistos("gen hadw",   { .fill="GenHadWEta",.pfs={"Signals_Background","Year",cut}, .cuts={},.draw="HIST",.opt=o_1or2d_s+"Norm",.ranges={}});
//     sh.AddHistos("gen hadw",   { .fill="GenHadWPtBins",.pfs={"Signals_Background","Year",cut}, .cuts={},.draw="HIST",.opt=o_1or2d_s+"Norm",.ranges={}});
// 
//     sh.AddHistos("gen hadtop", { .fill="GenTopEta",.pfs={"Signals_Background","Year",cut}, .cuts={},.draw="HIST",.opt=o_1or2d_s+"Norm",.ranges={}});
//     sh.AddHistos("gen hadtop", { .fill="GenTopPtBins",.pfs={"Signals_Background","Year",cut}, .cuts={},.draw="HIST",.opt=o_1or2d_s+"Norm",.ranges={}});
//     sh.AddHistos("gen leptop", { .fill="GenLepTopMatchedGenLepEta",.pfs={"Signals_Background","Year",cut,"GenTopLeptonFlavour"}, .cuts={},.draw="HIST",.opt=o_1or2d_s+"Norm",.ranges={}});
//     sh.AddHistos("gen leptop", { .fill="GenLepTopMatchedGenLepPtBins",.pfs={"Signals_Background","Year",cut,"GenTopLeptonFlavour"}, .cuts={},.draw="HIST",.opt=o_1or2d_s+"Norm",.ranges={}});
//     sh.AddHistos("evt",    { .fill="NGenEleAndMuFrom2Tops",.pfs={"Signals_Background","Year",cut}, .cuts={},.draw="HIST",.opt=o_1or2d_s+"Norm",.ranges={}});
//     sh.AddHistos("evt",    { .fill="NGenEleAndMuAndTauFrom2Tops",.pfs={"Signals_Background","Year",cut}, .cuts={},.draw="HIST",.opt=o_1or2d_s+"Norm",.ranges={}});
    sh.AddHistos("evt",    { .fill="NGenEleAndMuFrom2Tops",.pfs={"Signals_Background","Year",cut}, .cuts={},.draw="HIST",.opt=o_1or2d_s,.ranges={}});
    sh.AddHistos("evt",    { .fill="NGenEleAndMuAndTauFrom2Tops",.pfs={"Signals_Background","Year",cut}, .cuts={},.draw="HIST",.opt=o_1or2d_s,.ranges={}});
//     sh.AddHistos("evt",    { .fill="NGenEleAndMuFrom1Top",.pfs={"Signals_Background","Year",cut}, .cuts={},.draw="HIST",.opt=o_1or2d_s+"Norm",.ranges={}});
//     sh.AddHistos("evt",    { .fill="NGenEleAndMuAndTauFrom1Top",.pfs={"Signals_Background","Year",cut}, .cuts={},.draw="HIST",.opt=o_1or2d_s+"Norm",.ranges={}});
    //end of background study 
  }


  // Non-isolated lepton Signal Regions
  for (auto region : {Region::SR_Leptop_0htop, Region::SR_Leptop_1htop, Region::SR_Lepjet_0V_24j, Region::SR_Lepjet_0V_5j, Region::SR_Lepjet_1V_24j, Region::SR_Lepjet_1V_5j}) {
    sh.SetHistoWeights({ [&w,region] { return w.sf_weight[region]; } });
    std::string cut(magic_enum::enum_name(region));
    std::vector<std::string> showdata = {"Blind"};
    // Background study //TODO
//     // Reco measurments
//     sh.AddHistos("ele",        { .fill="EleEta",                    .pfs={"Signals_Background","Year",cut},          .cuts={},.draw="HIST",.opt=o_1or2d_s+"Norm",.ranges={}}); 
//     sh.AddHistos("ele",        { .fill="ElePt",                     .pfs={"Signals_Background","Year",cut},          .cuts={},.draw="HIST",.opt=o_1or2d_s+"Norm",.ranges={}}); 
//     sh.AddHistos("mu",         { .fill="MuEta",                     .pfs={"Signals_Background","Year",cut},          .cuts={},.draw="HIST",.opt=o_1or2d_s+"Norm",.ranges={}}); 
//     sh.AddHistos("mu",         { .fill="MuPt",                      .pfs={"Signals_Background","Year",cut},          .cuts={},.draw="HIST",.opt=o_1or2d_s+"Norm",.ranges={}}); 
//     
//     sh.AddHistos("ele veto",   { .fill="VetoEleEta",                .pfs={"Signals_Background","Year",cut},          .cuts={},.draw="HIST",.opt=o_1or2d_s+"Norm",.ranges={}}); 
//     sh.AddHistos("ele veto",   { .fill="VetoElePt",                 .pfs={"Signals_Background","Year",cut},          .cuts={},.draw="HIST",.opt=o_1or2d_s+"Norm",.ranges={}}); 
//     sh.AddHistos("mu veto",    { .fill="VetoMuEta",                 .pfs={"Signals_Background","Year",cut},          .cuts={},.draw="HIST",.opt=o_1or2d_s+"Norm",.ranges={}});
//     sh.AddHistos("mu veto",    { .fill="VetoMuPt",                  .pfs={"Signals_Background","Year",cut},          .cuts={},.draw="HIST",.opt=o_1or2d_s+"Norm",.ranges={}});
//     sh.AddHistos("tau veto",   { .fill="VetoTauEta",                .pfs={"Signals_Background","Year",cut},          .cuts={},.draw="HIST",.opt=o_1or2d_s+"Norm",.ranges={}}); 
//     sh.AddHistos("tau veto",   { .fill="VetoTauPt",                 .pfs={"Signals_Background","Year",cut},          .cuts={},.draw="HIST",.opt=o_1or2d_s+"Norm",.ranges={}}); 
//     
//     // Gen truth
//     sh.AddHistos("gen lep",    { .fill="GenLepEta",.pfs={"Signals_Background","Year",cut,"GenLepMother","GenLeptonFlavour"}, .cuts={},.draw="HIST",.opt=o_1or2d_s+"Norm",.ranges={}}); 
//     sh.AddHistos("gen lep",    { .fill="GenLepPtBins",.pfs={"Signals_Background","Year",cut,"GenLepMother","GenLeptonFlavour"}, .cuts={},.draw="HIST",.opt=o_1or2d_s+"Norm",.ranges={}}); 
//     
//     sh.AddHistos("gen hadw",   { .fill="GenHadWEta",.pfs={"Signals_Background","Year",cut}, .cuts={},.draw="HIST",.opt=o_1or2d_s+"Norm",.ranges={}});
//     sh.AddHistos("gen hadw",   { .fill="GenHadWPtBins",.pfs={"Signals_Background","Year",cut}, .cuts={},.draw="HIST",.opt=o_1or2d_s+"Norm",.ranges={}});
// 
//     sh.AddHistos("gen hadtop", { .fill="GenTopEta",.pfs={"Signals_Background","Year",cut}, .cuts={},.draw="HIST",.opt=o_1or2d_s+"Norm",.ranges={}});
//     sh.AddHistos("gen hadtop", { .fill="GenTopPtBins",.pfs={"Signals_Background","Year",cut}, .cuts={},.draw="HIST",.opt=o_1or2d_s+"Norm",.ranges={}});
//     sh.AddHistos("gen leptop", { .fill="GenLepTopMatchedGenLepEta",.pfs={"Signals_Background","Year",cut,"GenTopLeptonFlavour"}, .cuts={},.draw="HIST",.opt=o_1or2d_s+"Norm",.ranges={}});
//     sh.AddHistos("gen leptop", { .fill="GenLepTopMatchedGenLepPtBins",.pfs={"Signals_Background","Year",cut,"GenTopLeptonFlavour"}, .cuts={},.draw="HIST",.opt=o_1or2d_s+"Norm",.ranges={}});
//     sh.AddHistos("evt",    { .fill="NGenEleAndMuFrom2Tops",.pfs={"Signals_Background","Year",cut}, .cuts={},.draw="HIST",.opt=o_1or2d_s+"Norm",.ranges={}});
//     sh.AddHistos("evt",    { .fill="NGenEleAndMuAndTauFrom2Tops",.pfs={"Signals_Background","Year",cut}, .cuts={},.draw="HIST",.opt=o_1or2d_s+"Norm",.ranges={}});
    sh.AddHistos("evt",    { .fill="NGenEleAndMuFrom2Tops",.pfs={"Signals_Background","Year",cut}, .cuts={},.draw="HIST",.opt=o_1or2d_s,.ranges={}});
    sh.AddHistos("evt",    { .fill="NGenEleAndMuAndTauFrom2Tops",.pfs={"Signals_Background","Year",cut}, .cuts={},.draw="HIST",.opt=o_1or2d_s,.ranges={}});
//     sh.AddHistos("evt",    { .fill="NGenEleAndMuFrom1Top",.pfs={"Signals_Background","Year",cut}, .cuts={},.draw="HIST",.opt=o_1or2d_s+"Norm",.ranges={}});
//     sh.AddHistos("evt",    { .fill="NGenEleAndMuAndTauFrom1Top",.pfs={"Signals_Background","Year",cut}, .cuts={},.draw="HIST",.opt=o_1or2d_s+"Norm",.ranges={}});
    //end of background study 
  }


}

#endif // End header guard
