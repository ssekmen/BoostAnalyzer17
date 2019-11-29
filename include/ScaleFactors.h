#ifndef SCALEFACTORS_H
#define SCALEFACTORS_H

// Private headers
#include "Variables.h"
#include "EventSelections.h"

// 3rd party headers
#include "tnm.h" // for getplot
#include "BTagCalibrationStandalone.cpp" // From BTAG POG
#include "TFile.h"
#include "TH2.h"
#include "TGraphErrors.h"
#include "TGraphAsymmErrors.h"
#include "TProfile.h"
#include "TString.h"

// common libraries
#include <iostream>
#include <vector>

class ScaleFactors
{

public:
  typedef EventSelections::Regions Region;
  ScaleFactors(Variables& var) :
    v(var) {
    scale_factors.resize(magic_enum::enum_count<Region>());
  }
  ~ScaleFactors() {}

  void init_sf_histos();

  void init_input();

  void fill_sf_histos(const bool&, const bool&, const unsigned int&, const double&);

  double calc_top_tagging_sf(const double&, const double&, const double&, const double&, const bool&);
  double calc_fake_top_0b_mass_tagging_sf(const double&);
  double calc_fake_top_mass_tagging_sf(const double&);
  double calc_fake_top_anti_tagging_sf(const double&);

  double calc_w_tagging_sf(const double&, const double&, const double&, const double&, const bool&);
  double calc_fake_w_mass_tagging_sf(const double&);
  double calc_fake_w_anti_tagging_sf(const double&);

  std::pair<double, double> calc_b_tagging_sf(const double&, const double&, const bool&);

  std::tuple<double, double> calc_ele_sf(const double&, const double&, const double&, const double&, const bool&);

  std::tuple<double, double> calc_muon_sf(const double&, const double&, const double&, const bool&);
  
  void apply_scale_factors(std::vector<double>&, std::vector<std::vector<double> >&, 
                           const unsigned int&, const std::vector<std::vector<double> >&);

  std::vector<std::vector<double> > scale_factors;

private:
  
  Variables& v;

  double get_syst_weight_(const double&, const double&, const double&, const double&);

  double get_syst_weight_(const double&, const double&, const double&);

  BTagCalibration* btag_calib_full_;
  BTagCalibration* btag_calib_fast_;
  BTagCalibrationReader* btag_sf_full_loose_;
  BTagCalibrationReader* btag_sf_fast_loose_;
  BTagCalibrationReader* btag_sf_full_medium_;
  BTagCalibrationReader* btag_sf_fast_medium_;

  //_______________________________________________________
  //                Input histograms

  TProfile* eff_btag_b_loose;
  TProfile* eff_btag_c_loose;
  TProfile* eff_btag_l_loose;
  TProfile* eff_btag_b_medium;
  TProfile* eff_btag_c_medium;
  TProfile* eff_btag_l_medium;
  
  TH2F* eff_full_ele_reco;
  TH2F* eff_full_ele_vetoid;
  TH2F* eff_full_ele_looseid;
  TH2F* eff_full_ele_mediumid;
  TH2F* eff_full_ele_mvalooseid_tightip2d;
  TH2F* eff_full_ele_miniiso01;
  TH2F* eff_full_ele_miniiso02;
  TH2F* eff_full_ele_miniiso04;
  TH2D* eff_fast_ele_vetoid;
  TH2D* eff_fast_ele_looseid;
  TH2D* eff_fast_ele_mediumid;
  TH2D* eff_fast_ele_mvalooseid_tightip2d;
  TH2D* eff_fast_ele_miniiso01;
  TH2D* eff_fast_ele_miniiso02;
  TH2D* eff_fast_ele_miniiso04;
  TH2F* eff_full_ele_veto;
  //TGraphAsymmErrors* eff_full_muon_trk;
  //TGraphAsymmErrors* eff_full_muon_trk_veto;
  TH2F* eff_full_muon_looseid;
  TH2F* eff_full_muon_mediumid;
  TH2F* eff_full_muon_miniiso04;
  TH2F* eff_full_muon_miniiso02;
  //TH2F* eff_full_muon_looseip2d;
  //TH2F* eff_full_muon_tightip2d;
  TH2D* eff_fast_muon_vetoid;
  TH2D* eff_fast_muon_looseid;
  TH2D* eff_fast_muon_mediumid;
  TH2F* eff_full_muon_veto;
  
  TH1D* eff_full_fake_bW;
  TH1D* eff_full_fake_eW;
  TH1D* eff_full_fake_baW;
  TH1D* eff_full_fake_eaW;
  TH1D* eff_full_fake_bm0bW;
  TH1D* eff_full_fake_em0bW;
  TH1D* eff_full_fake_bTop;
  TH1D* eff_full_fake_eTop;
  TH1D* eff_full_fake_baTop;
  TH1D* eff_full_fake_eaTop;
  TH1D* eff_full_fake_bmTop;
  TH1D* eff_full_fake_emTop;
  TH1D* eff_full_fake_bm0bTop;
  TH1D* eff_full_fake_em0bTop;
  TGraphErrors* eff_full_POG_W;
  TH1D* eff_full_POG_Top;
  TH1D* eff_full_POG_Top_up;
  TH1D* eff_full_POG_Top_down;
  /*
    TGraphAsymmErrors* eff_full_fake_bW;
    TGraphAsymmErrors* eff_full_fake_eW;
    TGraphAsymmErrors* eff_full_fake_baW;
    TGraphAsymmErrors* eff_full_fake_eaW;
    TGraphAsymmErrors* eff_full_fake_bm0bW;
    TGraphAsymmErrors* eff_full_fake_em0bW;
    TGraphAsymmErrors* eff_full_fake_bTop;
    TGraphAsymmErrors* eff_full_fake_eTop;
    TGraphAsymmErrors* eff_full_fake_baTop;
    TGraphAsymmErrors* eff_full_fake_eaTop;
    TGraphAsymmErrors* eff_full_fake_bmTop;
    TGraphAsymmErrors* eff_full_fake_emTop;
    TGraphAsymmErrors* eff_full_fake_bm0bTop;
    TGraphAsymmErrors* eff_full_fake_em0bTop;
  */
  TGraphAsymmErrors* eff_fast_bW;
  TGraphAsymmErrors* eff_fast_eW;
  TGraphAsymmErrors* eff_fast_bTop;
  TGraphAsymmErrors* eff_fast_eTop;
  TGraphAsymmErrors* eff_fast_fake_bW;
  TGraphAsymmErrors* eff_fast_fake_eW;
  TGraphAsymmErrors* eff_fast_fake_bTop;
  TGraphAsymmErrors* eff_fast_fake_eTop;

  //_______________________________________________________
  //           List of scale factor Histograms

  TH2D* h_btag_eff_b_loose;
  TH2D* h_btag_eff_c_loose;
  TH2D* h_btag_eff_l_loose;
  TH2D* h_btag_eff_b_medium;
  TH2D* h_btag_eff_c_medium;
  TH2D* h_btag_eff_l_medium;

};

void ScaleFactors::init_input() {
  // B-tagging
  // Efficiencies (Oct31 - test)
  TFile* f;
  if (v.year==2018) {
    if (v.sample.Contains("FastSim"))
      f = TFile::Open("btag_eff/December_03/FastSim_SMS-T5ttcc.root");
    else if (v.sample.Contains("WJetsToLNu"))
      f = TFile::Open("btag_eff/August_21/WJetsToLNu.root");
    else if (v.sample.Contains("TT")||v.sample.Contains("ST"))
      f = TFile::Open("btag_eff/August_21/TT.root");
    else
      f = TFile::Open("btag_eff/August_21/QCD.root");
  } else if (v.year==2017) {
    if (v.sample.Contains("FastSim"))
      f = TFile::Open("btag_eff/December_03/FastSim_SMS-T5ttcc.root");
    else if (v.sample.Contains("WJetsToLNu"))
      f = TFile::Open("btag_eff/August_21/WJetsToLNu.root");
    else if (v.sample.Contains("TT")||v.sample.Contains("ST"))
      f = TFile::Open("btag_eff/August_21/TT.root");
    else
      f = TFile::Open("btag_eff/August_21/QCD.root");
  } else {
    std::cout<<"ScaleFactors::init_input(): btagging sfs not yet defined for 2016"<<std::endl;
    std::exit(1);
    f = TFile::Open("btag_eff/2016_placeholder");
  }

  eff_btag_b_loose  = ((TH2D*)f->Get("btag_eff_b_loose"))->ProfileX();
  eff_btag_c_loose  = ((TH2D*)f->Get("btag_eff_c_loose"))->ProfileX();
  eff_btag_l_loose  = ((TH2D*)f->Get("btag_eff_l_loose"))->ProfileX();
  eff_btag_b_medium = ((TH2D*)f->Get("btag_eff_b_medium"))->ProfileX();
  eff_btag_c_medium = ((TH2D*)f->Get("btag_eff_c_medium"))->ProfileX();
  eff_btag_l_medium = ((TH2D*)f->Get("btag_eff_l_medium"))->ProfileX();
  eff_btag_b_loose  ->SetDirectory(0);
  eff_btag_c_loose  ->SetDirectory(0);
  eff_btag_l_loose  ->SetDirectory(0);
  eff_btag_b_medium ->SetDirectory(0);
  eff_btag_c_medium ->SetDirectory(0);
  eff_btag_l_medium ->SetDirectory(0);
  f->Close();
  // Moriond17 SFs
  // https://twiki.cern.ch/twiki/bin/viewauth/CMS/BtagRecommendation94X
  if (v.year==2018) {
    btag_calib_full_ = new BTagCalibration("csvv2", "scale_factors/btag/DeepCSV_102XSF_V1.csv");
  } else if (v.year==2017) {
    btag_calib_full_ =  new BTagCalibration("csvv2", "scale_factors/btag/DeepCSV_94XSF_V3_B_F.csv");
  }
  // Loose WP
  btag_sf_full_loose_  = new BTagCalibrationReader(BTagEntry::OP_LOOSE, "central", {"up", "down"});
  btag_sf_full_loose_->load(*btag_calib_full_, BTagEntry::FLAV_B,    "comb");
  btag_sf_full_loose_->load(*btag_calib_full_, BTagEntry::FLAV_C,    "comb");
  btag_sf_full_loose_->load(*btag_calib_full_, BTagEntry::FLAV_UDSG, "incl");
  // Medium WP
  btag_sf_full_medium_ = new BTagCalibrationReader(BTagEntry::OP_MEDIUM, "central", {"up", "down"});
  btag_sf_full_medium_->load(*btag_calib_full_, BTagEntry::FLAV_B,    "comb");
  btag_sf_full_medium_->load(*btag_calib_full_, BTagEntry::FLAV_C,    "comb");
  btag_sf_full_medium_->load(*btag_calib_full_, BTagEntry::FLAV_UDSG, "incl");
  // Spring16 FastSim
  if (v.year==2018) {
    btag_calib_fast_ =  new BTagCalibration("csvv2", "scale_factors/btag/deepcsv_13TEV_18SL_7_5_2019.csv");
  } else if (v.year==2017) {
    // This file needed minor formatting to be readable
    // sed 's;^";;;s; "\;;;;s;"";";g;' scale_factors/btag/fastsim_csvv2_ttbar_26_1_2017.csv
    btag_calib_fast_ =  new BTagCalibration("csvv2", "scale_factors/btag/deepcsv_13TEV_17SL_18_3_2019.csv");
  }
  // Loose WP
  btag_sf_fast_loose_  = new BTagCalibrationReader(BTagEntry::OP_LOOSE, "central", {"up", "down"});
  btag_sf_fast_loose_->load(*btag_calib_fast_, BTagEntry::FLAV_B,    "fastsim");
  btag_sf_fast_loose_->load(*btag_calib_fast_, BTagEntry::FLAV_C,    "fastsim");
  btag_sf_fast_loose_->load(*btag_calib_fast_, BTagEntry::FLAV_UDSG, "fastsim");
  // Medium WP
  btag_sf_fast_medium_ = new BTagCalibrationReader(BTagEntry::OP_MEDIUM, "central", {"up", "down"});
  btag_sf_fast_medium_->load(*btag_calib_fast_, BTagEntry::FLAV_B,    "fastsim");
  btag_sf_fast_medium_->load(*btag_calib_fast_, BTagEntry::FLAV_C,    "fastsim");
  btag_sf_fast_medium_->load(*btag_calib_fast_, BTagEntry::FLAV_UDSG, "fastsim");

  // SoftDrop Mass correction for W tagging - Spring
  // https://twiki.cern.ch/twiki/bin/view/CMS/JetWtagging?rev=43#Recipes_to_obtain_the_PUPPI_soft
  
  //TMP  TFile* file;
  //TMP  if (v.year==2018) {
  //TMP    file = TFile::Open("scale_factors/softdrop_mass_corr/puppiCorr.root");
  //TMP  } else if (v.year==2017) {
  //TMP    // Moriond17+ReReco
  //TMP    file = TFile::Open("scale_factors/softdrop_mass_corr/puppiCorr.root");
  //TMP  }
  //TMP  puppisd_corrGEN_      = (TF1*)((TF1*)file->Get("puppiJECcorr_gen"))->Clone();
  //TMP  puppisd_corrRECO_cen_ = (TF1*)((TF1*)file->Get("puppiJECcorr_reco_0eta1v3"))->Clone();
  //TMP  puppisd_corrRECO_for_ = (TF1*)((TF1*)file->Get("puppiJECcorr_reco_1v3eta2v5"))->Clone();
  //TMP  file->Close();

  // Lepton scale factors
  if (v.year==2018) {
    // Ele - Reconstruction  SF - https://twiki.cern.ch/twiki/bin/view/CMS/EgammaIDRecipesRun2?rev=38#Electron_efficiencies_and_scale
    eff_full_ele_reco                 = getplot_TH2F("scale_factors/electron/reco/egammaEffi.txt_EGM2D_updatedAll.root","EGamma_SF2D", "ele1");//2018
    // Ele - Data-FullSim    SF - https://twiki.cern.ch/twiki/bin/view/CMS/SUSLeptonSF?rev=210#Data_leading_order_FullSim_MC_co
    eff_full_ele_vetoid               = getplot_TH2F("scale_factors/electron/fullsim/ElectronScaleFactors_Run2018.root","Run2018_CutBasedVetoNoIso94XV2"  ,"ele2");
    eff_full_ele_looseid              = getplot_TH2F("scale_factors/electron/fullsim/ElectronScaleFactors_Run2018.root","Run2018_CutBasedLooseNoIso94XV2" ,"ele3");
    eff_full_ele_mediumid             = getplot_TH2F("scale_factors/electron/fullsim/ElectronScaleFactors_Run2018.root","Run2018_CutBasedMediumNoIso94XV2","ele4");
    eff_full_ele_mvalooseid_tightip2d = getplot_TH2F("scale_factors/electron/fullsim/ElectronScaleFactors_Run2018.root","Run2018_MVAVLooseIP2D"           ,"ele5");
    eff_full_ele_miniiso01            = getplot_TH2F("scale_factors/electron/fullsim/ElectronScaleFactors_Run2018.root","Run2018_Mini"  ,"ele6");
    eff_full_ele_miniiso02            = getplot_TH2F("scale_factors/electron/fullsim/ElectronScaleFactors_Run2018.root","Run2018_Mini2" ,"ele7");
    eff_full_ele_miniiso04            = getplot_TH2F("scale_factors/electron/fullsim/ElectronScaleFactors_Run2018.root","Run2018_Mini4" ,"ele8");
    // Ele - FullSim-FastSim SF - https://twiki.cern.ch/twiki/bin/view/CMS/SUSLeptonSF?rev=210#FullSim_FastSim_TTBar_MC_compari
    eff_fast_ele_vetoid               = getplot_TH2D("scale_factors/electron/fastsim/detailed_ele_full_fast_sf_18.root", "CutBasedVetoNoIso94XV2_sf", "ele9");
    eff_fast_ele_looseid              = getplot_TH2D("scale_factors/electron/fastsim/detailed_ele_full_fast_sf_18.root", "CutBasedLooseNoIso94XV2_sf", "ele10");
    eff_fast_ele_mediumid             = getplot_TH2D("scale_factors/electron/fastsim/detailed_ele_full_fast_sf_18.root", "CutBasedMediumNoIso94XV1_sf", "ele11");
    eff_fast_ele_mvalooseid_tightip2d = getplot_TH2D("scale_factors/electron/fastsim/detailed_ele_full_fast_sf_18.root", "MVAVLooseIP2D_sf", "ele12");
    eff_fast_ele_miniiso01            = getplot_TH2D("scale_factors/electron/fastsim/detailed_ele_full_fast_sf_18.root", "MVAVLooseTightIP2DMini_sf", "ele13");
    eff_fast_ele_miniiso02            = getplot_TH2D("scale_factors/electron/fastsim/detailed_ele_full_fast_sf_18.root", "MVAVLooseTightIP2DMini2_sf", "ele14");
    eff_fast_ele_miniiso04            = getplot_TH2D("scale_factors/electron/fastsim/detailed_ele_full_fast_sf_18.root", "MVAVLooseTightIP2DMini4_sf", "ele15");
    // Inclusive Razor Scale Factors
    eff_full_ele_veto                 = getplot_TH2F("scale_factors/RazorRunAuxFiles_Expanded/"
  							  "efficiency_results_VetoElectronSelectionEffDenominatorGen_2016_Rereco_Golden.root",
  							  "ScaleFactor_VetoElectronSelectionEffDenominatorGen", "ele16");//2017
  
    // Muon Tracking eff     SF - https://twiki.cern.ch/twiki/bin/view/CMS/SUSLeptonSF?rev=210#FullSim_FastSim_TTBar_MC_com_AN1
    //eff_full_muon_trk   		    = getplot_TGraphAsymmErrors("scale_factors/muon/tracking/Tracking_EfficienciesAndSF_BCDEFGH.root", "ratio_eff_eta3_dr030e030_corr", "mu1");
    //eff_full_muon_trk_veto	    = getplot_TGraphAsymmErrors("scale_factors/muon/tracking/Tracking_EfficienciesAndSF_BCDEFGH.root", "ratio_eff_eta3_tk0_dr030e030_corr", "mu2");
    // Muon Data-FullSim     SF - https://twiki.cern.ch/twiki/bin/view/CMS/SUSLeptonSF?rev=210#Data_leading_order_FullSim_M_AN1
    eff_full_muon_looseid		    = getplot_TH2F("scale_factors/muon/fullsim/RunABCD_SF_ID.root",  "NUM_SoftID_DEN_TrackerMuons_pt_abseta",    "mu3");
    eff_full_muon_mediumid	    = getplot_TH2F("scale_factors/muon/fullsim/RunABCD_SF_ID.root",  "NUM_MediumID_DEN_TrackerMuons_pt_abseta",  "mu4");
    eff_full_muon_miniiso04	    = getplot_TH2F("scale_factors/muon/fullsim/RunABCD_SF_ID.root", "NUM_LooseID_DEN_TrackerMuons_pt_abseta", "mu5");
    eff_full_muon_miniiso02	    = getplot_TH2F("scale_factors/muon/fullsim/RunABCD_SF_ID.root", "NUM_TightID_DEN_TrackerMuons_pt_abseta","mu6");
    //eff_full_muon_looseip2d	    = getplot_TH2F("scale_factors/muon/fullsim/TnP_NUM_MediumIP2D_DENOM_LooseID_VAR_map_pt_eta.root",    "SF", "mu7");
    //eff_full_muon_tightip2d	    = getplot_TH2F("scale_factors/muon/fullsim/TnP_NUM_TightIP2D_DENOM_MediumID_VAR_map_pt_eta.root",    "SF", "mu8");
    // Muon FullSim-FastSim  SF - https://twiki.cern.ch/twiki/bin/view/CMS/SUSLeptonSF?rev=210#FullSim_FastSim_TTBar_MC_com_AN1
    eff_fast_muon_vetoid		    = getplot_TH2D("scale_factors/muon/fastsim/detailed_mu_full_fast_sf_18.root", "miniIso04_LooseId_sf", "mu10");
    eff_fast_muon_looseid		    = getplot_TH2D("scale_factors/muon/fastsim/detailed_mu_full_fast_sf_18.root", "miniIso02_LooseId_sf", "mu9");
    eff_fast_muon_mediumid	    = getplot_TH2D("scale_factors/muon/fastsim/detailed_mu_full_fast_sf_18.root", "miniIso02_MediumId_sf","mu11");
   // Inclusive Razor Scale Factors
    eff_full_muon_veto                = getplot_TH2F("scale_factors/RazorRunAuxFiles_Expanded/"
  							  "efficiency_results_VetoMuonSelectionEffDenominatorGen_2016_Rereco_Golden.root",
  							  "ScaleFactor_VetoMuonSelectionEffDenominatorGen", "mu15");//2017
  } else if (v.year==2017) {
    // Ele - Reconstruction  SF - https://twiki.cern.ch/twiki/bin/view/CMS/EgammaIDRecipesRun2?rev=38#Electron_efficiencies_and_scale
    eff_full_ele_reco                 = getplot_TH2F("scale_factors/electron/reco/egammaEffi.txt_EGM2D_runBCDEF_passingRECO.root","EGamma_SF2D", "ele1");
    // Ele - Data-FullSim    SF - https://twiki.cern.ch/twiki/bin/view/CMS/SUSLeptonSF?rev=210#Data_leading_order_FullSim_MC_co
    eff_full_ele_vetoid               = getplot_TH2F("scale_factors/electron/fullsim/ElectronScaleFactors_Run2017.root","Run2017_CutBasedVetoNoIso94XV2"  ,"ele2");
    eff_full_ele_looseid              = getplot_TH2F("scale_factors/electron/fullsim/ElectronScaleFactors_Run2017.root","Run2017_CutBasedLooseNoIso94XV2" ,"ele3");
    eff_full_ele_mediumid             = getplot_TH2F("scale_factors/electron/fullsim/ElectronScaleFactors_Run2017.root","Run2017_CutBasedMediumNoIso94XV2","ele4");
    eff_full_ele_mvalooseid_tightip2d = getplot_TH2F("scale_factors/electron/fullsim/ElectronScaleFactors_Run2017.root","Run2017_MVAVLooseIP2D"           ,"ele5");
    eff_full_ele_miniiso01            = getplot_TH2F("scale_factors/electron/fullsim/ElectronScaleFactors_Run2017.root","Run2017_MVAVLooseTightIP2DMini"  ,"ele6");
    eff_full_ele_miniiso02            = getplot_TH2F("scale_factors/electron/fullsim/ElectronScaleFactors_Run2017.root","Run2017_MVAVLooseTightIP2DMini2" ,"ele7");
    eff_full_ele_miniiso04            = getplot_TH2F("scale_factors/electron/fullsim/ElectronScaleFactors_Run2017.root","Run2017_MVAVLooseTightIP2DMini4" ,"ele8");
    // Ele - FullSim-FastSim SF - https://twiki.cern.ch/twiki/bin/view/CMS/SUSLeptonSF?rev=210#FullSim_FastSim_TTBar_MC_compari
    eff_fast_ele_vetoid               = getplot_TH2D("scale_factors/electron/fastsim/detailed_ele_full_fast_sf_17.root",  "CutBasedVetoNoIso94XV2_sf", "ele9");
    eff_fast_ele_looseid              = getplot_TH2D("scale_factors/electron/fastsim/detailed_ele_full_fast_sf_17.root",  "CutBasedLooseNoIso94XV2_sf", "ele10");
    eff_fast_ele_mediumid             = getplot_TH2D("scale_factors/electron/fastsim/detailed_ele_full_fast_sf_17.root",  "CutBasedMediumNoIso94XV2_sf", "ele11");
    eff_fast_ele_mvalooseid_tightip2d = getplot_TH2D("scale_factors/electron/fastsim/detailed_ele_full_fast_sf_17.root",  "MVAVLooseIP2D_sf", "ele12");
    eff_fast_ele_miniiso01            = getplot_TH2D("scale_factors/electron/fastsim/detailed_ele_full_fast_sf_17.root",  "MVAVLooseTightIP2DMini_sf", "ele13");
    eff_fast_ele_miniiso02            = getplot_TH2D("scale_factors/electron/fastsim/detailed_ele_full_fast_sf_17.root",  "MVAVLooseTightIP2DMini2_sf", "ele14");
    eff_fast_ele_miniiso04            = getplot_TH2D("scale_factors/electron/fastsim/detailed_ele_full_fast_sf_17.root",  "MVAVLooseTightIP2DMini4_sf", "ele15");
    // Inclusive Razor Scale Factors
    eff_full_ele_veto                 = getplot_TH2F("scale_factors/RazorRunAuxFiles_Expanded/"
                                                     "efficiency_results_VetoElectronSelectionEffDenominatorGen_2016_Rereco_Golden.root",
                                                     "ScaleFactor_VetoElectronSelectionEffDenominatorGen", "ele16");
  
    // Muon Tracking eff     SF - https://twiki.cern.ch/twiki/bin/view/CMS/SUSLeptonSF?rev=210#FullSim_FastSim_TTBar_MC_com_AN1
    //eff_full_muon_trk   		    = getplot_TGraphAsymmErrors("scale_factors/muon/tracking/Tracking_EfficienciesAndSF_BCDEFGH.root", "ratio_eff_eta3_dr030e030_corr", "mu1");
    //eff_full_muon_trk_veto	    = getplot_TGraphAsymmErrors("scale_factors/muon/tracking/Tracking_EfficienciesAndSF_BCDEFGH.root", "ratio_eff_eta3_tk0_dr030e030_corr", "mu2");
    // Muon Data-FullSim     SF - https://twiki.cern.ch/twiki/bin/view/CMS/SUSLeptonSF?rev=210#Data_leading_order_FullSim_M_AN1
    eff_full_muon_looseid		    = getplot_TH2F("scale_factors/muon/fullsim/RunBCDEF_SF_ID.root",  "NUM_SoftID_DEN_genTracks_pt_abseta",    "mu3");
    eff_full_muon_mediumid	    = getplot_TH2F("scale_factors/muon/fullsim/RunBCDEF_SF_ID.root",  "NUM_MediumID_DEN_genTracks_pt_abseta",  "mu4");
    eff_full_muon_miniiso04	    = getplot_TH2F("scale_factors/muon/fullsim/RunBCDEF_SF_ISO.root", "NUM_LooseRelIso_DEN_LooseID_pt_abseta", "mu5");
    eff_full_muon_miniiso02	    = getplot_TH2F("scale_factors/muon/fullsim/RunBCDEF_SF_ISO.root", "NUM_TightRelIso_DEN_MediumID_pt_abseta","mu6");
    //eff_full_muon_looseip2d	    = getplot_TH2F("scale_factors/muon/fullsim/TnP_NUM_MediumIP2D_DENOM_LooseID_VAR_map_pt_eta.root",    "SF", "mu7");
    //eff_full_muon_tightip2d	    = getplot_TH2F("scale_factors/muon/fullsim/TnP_NUM_TightIP2D_DENOM_MediumID_VAR_map_pt_eta.root",    "SF", "mu8");
    // Muon FullSim-FastSim  SF - https://twiki.cern.ch/twiki/bin/view/CMS/SUSLeptonSF?rev=210#FullSim_FastSim_TTBar_MC_com_AN1
    eff_fast_muon_vetoid		    = getplot_TH2D("scale_factors/muon/fastsim/detailed_mu_full_fast_sf_17.root", "miniIso02_LooseId_sf", "mu9");
    eff_fast_muon_looseid		    = getplot_TH2D("scale_factors/muon/fastsim/detailed_mu_full_fast_sf_17.root", "miniIso04_LooseId_sf", "mu10");
    eff_fast_muon_mediumid	    = getplot_TH2D("scale_factors/muon/fastsim/detailed_mu_full_fast_sf_17.root", "miniIso02_MediumId_sf","mu11");
    // Inclusive Razor Scale Factors
    eff_full_muon_veto                = getplot_TH2F("scale_factors/RazorRunAuxFiles_Expanded/"
                                                     "efficiency_results_VetoMuonSelectionEffDenominatorGen_2016_Rereco_Golden.root",
                                                     "ScaleFactor_VetoMuonSelectionEffDenominatorGen", "mu15");
  }

  // W/Top (anti-/mass-)tag (and fake rate) scale factors
  if (v.year==2018) {
    eff_full_fake_bW      = getplot_TH1D("scale_factors/w_top_tag/WTopTagSF.root",                             "bW",      "full_fake_W_barrel");
    eff_full_fake_eW      = getplot_TH1D("scale_factors/w_top_tag/WTopTagSF.root",                             "eW",      "full_fake_W_endcap");
    eff_full_fake_bm0bW   = getplot_TH1D("scale_factors/w_top_tag/WTopTagSF.root",                             "bm0bW",   "full_fake_m0bW_barrel");
    eff_full_fake_em0bW   = getplot_TH1D("scale_factors/w_top_tag/WTopTagSF.root",                             "em0bW",   "full_fake_m0bW_endcap");
    eff_full_fake_baW     = getplot_TH1D("scale_factors/w_top_tag/WTopTagSF.root",                             "baW",     "full_fake_aW_barrel");
    eff_full_fake_eaW     = getplot_TH1D("scale_factors/w_top_tag/WTopTagSF.root",                             "eaW",     "full_fake_aW_endcap");
    eff_full_fake_bTop    = getplot_TH1D("scale_factors/w_top_tag/WTopTagSF.root",                             "bTop",    "full_fake_Top_barrel");
    eff_full_fake_eTop    = getplot_TH1D("scale_factors/w_top_tag/WTopTagSF.root",                             "eTop",    "full_fake_Top_endcap");
    eff_full_fake_bmTop   = getplot_TH1D("scale_factors/w_top_tag/WTopTagSF.root",                             "bmTop",   "full_fake_mTop_barrel");
    eff_full_fake_emTop   = getplot_TH1D("scale_factors/w_top_tag/WTopTagSF.root",                             "emTop",   "full_fake_mTop_endcap");
    eff_full_fake_bm0bTop = getplot_TH1D("scale_factors/w_top_tag/WTopTagSF.root",                             "bm0bTop", "full_fake_0bmTop_barrel");
    eff_full_fake_em0bTop = getplot_TH1D("scale_factors/w_top_tag/WTopTagSF.root",                             "em0bTop", "full_fake_0bmTop_endcap");
    eff_full_fake_baTop   = getplot_TH1D("scale_factors/w_top_tag/WTopTagSF.root",                             "baTop",   "full_fake_aTop_barrel");
    eff_full_fake_eaTop   = getplot_TH1D("scale_factors/w_top_tag/WTopTagSF.root",                             "eaTop",   "full_fake_aTop_endcap");
    eff_full_POG_Top      = getplot_TH1D("scale_factors/w_top_tag/2017TopTaggingScaleFactors.root",            "PUPPI_wp2_btag/sf_mergedTop_nominal", "full_POG_Top");
    eff_full_POG_Top_up   = getplot_TH1D("scale_factors/w_top_tag/2017TopTaggingScaleFactors.root",            "PUPPI_wp2_btag/sf_mergedTop_up", "full_POG_Top_up");
    eff_full_POG_Top_down = getplot_TH1D("scale_factors/w_top_tag/2017TopTaggingScaleFactors.root",            "PUPPI_wp2_btag/sf_mergedTop_down", "full_POG_Top_down");
    eff_full_POG_W        = getplot_TGraphErrors("scale_factors/w_top_tag/SF_tau21_0p45_ptDependence_200to600GeV.root","Graph",       "full_POG_W");
    
    eff_fast_bW           = getplot_TGraphAsymmErrors("scale_factors/w_top_tag/fastsim/FullFastSimTagSF_BarrelEndcap_Janos.root", "bWFF",    "fast_bW");
    eff_fast_eW           = getplot_TGraphAsymmErrors("scale_factors/w_top_tag/fastsim/FullFastSimTagSF_BarrelEndcap_Janos.root", "eWFF",    "fast_eW");
    eff_fast_bTop         = getplot_TGraphAsymmErrors("scale_factors/w_top_tag/fastsim/FullFastSimTagSF_BarrelEndcap_Janos.root", "bTopFF",  "fast_bTop");
    eff_fast_eTop         = getplot_TGraphAsymmErrors("scale_factors/w_top_tag/fastsim/FullFastSimTagSF_BarrelEndcap_Janos.root", "eTopFF",  "fast_eTop");
    eff_fast_fake_bW      = getplot_TGraphAsymmErrors("scale_factors/w_top_tag/fastsim/FullFastSimTagSF_BarrelEndcap_Janos.root", "bMWFF",   "fast_fake_bW");
    eff_fast_fake_eW      = getplot_TGraphAsymmErrors("scale_factors/w_top_tag/fastsim/FullFastSimTagSF_BarrelEndcap_Janos.root", "eMWFF",   "fast_fake_eW");
    eff_fast_fake_bTop    = getplot_TGraphAsymmErrors("scale_factors/w_top_tag/fastsim/FullFastSimTagSF_BarrelEndcap_Janos.root", "bMTopFF", "fast_fake_bTop");
    eff_fast_fake_eTop    = getplot_TGraphAsymmErrors("scale_factors/w_top_tag/fastsim/FullFastSimTagSF_BarrelEndcap_Janos.root", "eMTopFF", "fast_fake_eTop");
  } else if (v.year==2017) {
    eff_full_fake_bW      = getplot_TH1D("scale_factors/w_top_tag/WTopTagSF.root",                             "bW",      "full_fake_W_barrel");
    eff_full_fake_eW      = getplot_TH1D("scale_factors/w_top_tag/WTopTagSF.root",                             "eW",      "full_fake_W_endcap");
    eff_full_fake_bm0bW   = getplot_TH1D("scale_factors/w_top_tag/WTopTagSF.root",                             "bm0bW",   "full_fake_m0bW_barrel");
    eff_full_fake_em0bW   = getplot_TH1D("scale_factors/w_top_tag/WTopTagSF.root",                             "em0bW",   "full_fake_m0bW_endcap");
    eff_full_fake_baW     = getplot_TH1D("scale_factors/w_top_tag/WTopTagSF.root",                             "baW",     "full_fake_aW_barrel");
    eff_full_fake_eaW     = getplot_TH1D("scale_factors/w_top_tag/WTopTagSF.root",                             "eaW",     "full_fake_aW_endcap");
    eff_full_fake_bTop    = getplot_TH1D("scale_factors/w_top_tag/WTopTagSF.root",                             "bTop",    "full_fake_Top_barrel");
    eff_full_fake_eTop    = getplot_TH1D("scale_factors/w_top_tag/WTopTagSF.root",                             "eTop",    "full_fake_Top_endcap");
    eff_full_fake_bmTop   = getplot_TH1D("scale_factors/w_top_tag/WTopTagSF.root",                             "bmTop",   "full_fake_mTop_barrel");
    eff_full_fake_emTop   = getplot_TH1D("scale_factors/w_top_tag/WTopTagSF.root",                             "emTop",   "full_fake_mTop_endcap");
    eff_full_fake_bm0bTop = getplot_TH1D("scale_factors/w_top_tag/WTopTagSF.root",                             "bm0bTop", "full_fake_0bmTop_barrel");
    eff_full_fake_em0bTop = getplot_TH1D("scale_factors/w_top_tag/WTopTagSF.root",                             "em0bTop", "full_fake_0bmTop_endcap");
    eff_full_fake_baTop   = getplot_TH1D("scale_factors/w_top_tag/WTopTagSF.root",                             "baTop",   "full_fake_aTop_barrel");
    eff_full_fake_eaTop   = getplot_TH1D("scale_factors/w_top_tag/WTopTagSF.root",                             "eaTop",   "full_fake_aTop_endcap");
    eff_full_POG_Top      = getplot_TH1D("scale_factors/w_top_tag/2017TopTaggingScaleFactors.root",            "PUPPI_wp2_btag/sf_mergedTop_nominal", "full_POG_Top");
    eff_full_POG_Top_up   = getplot_TH1D("scale_factors/w_top_tag/2017TopTaggingScaleFactors.root",            "PUPPI_wp2_btag/sf_mergedTop_up", "full_POG_Top_up");
    eff_full_POG_Top_down = getplot_TH1D("scale_factors/w_top_tag/2017TopTaggingScaleFactors.root",            "PUPPI_wp2_btag/sf_mergedTop_down", "full_POG_Top_down");
    eff_full_POG_W        = getplot_TGraphErrors("scale_factors/w_top_tag/SF_tau21_0p45_ptDependence_200to600GeV.root","Graph",       "full_POG_W");
    
    eff_fast_bW           = getplot_TGraphAsymmErrors("scale_factors/w_top_tag/fastsim/FullFastSimTagSF_BarrelEndcap_Janos.root", "bWFF",    "fast_bW");
    eff_fast_eW           = getplot_TGraphAsymmErrors("scale_factors/w_top_tag/fastsim/FullFastSimTagSF_BarrelEndcap_Janos.root", "eWFF",    "fast_eW");
    eff_fast_bTop         = getplot_TGraphAsymmErrors("scale_factors/w_top_tag/fastsim/FullFastSimTagSF_BarrelEndcap_Janos.root", "bTopFF",  "fast_bTop");
    eff_fast_eTop         = getplot_TGraphAsymmErrors("scale_factors/w_top_tag/fastsim/FullFastSimTagSF_BarrelEndcap_Janos.root", "eTopFF",  "fast_eTop");
    eff_fast_fake_bW      = getplot_TGraphAsymmErrors("scale_factors/w_top_tag/fastsim/FullFastSimTagSF_BarrelEndcap_Janos.root", "bMWFF",   "fast_fake_bW");
    eff_fast_fake_eW      = getplot_TGraphAsymmErrors("scale_factors/w_top_tag/fastsim/FullFastSimTagSF_BarrelEndcap_Janos.root", "eMWFF",   "fast_fake_eW");
    eff_fast_fake_bTop    = getplot_TGraphAsymmErrors("scale_factors/w_top_tag/fastsim/FullFastSimTagSF_BarrelEndcap_Janos.root", "bMTopFF", "fast_fake_bTop");
    eff_fast_fake_eTop    = getplot_TGraphAsymmErrors("scale_factors/w_top_tag/fastsim/FullFastSimTagSF_BarrelEndcap_Janos.root", "eMTopFF", "fast_fake_eTop");
  }
}


//_______________________________________________________
//              Define Histograms here
void
ScaleFactors::init_sf_histos()
{
  // btagging efficiency
  double ptbins[11]  = { 20,30,50,70,100,140,200,300,600,1000,4000 };
  double effbins[3] = { -0.5,0.5,1.5 };
  h_btag_eff_b_loose            = new TH2D("btag_eff_b_loose",  ";AK4 Jet p_{T} (GeV);Pass b-tag", 10,ptbins, 2,effbins);
  h_btag_eff_c_loose            = new TH2D("btag_eff_c_loose",  ";AK4 Jet p_{T} (GeV);Pass b-tag", 10,ptbins, 2,effbins);
  h_btag_eff_l_loose            = new TH2D("btag_eff_l_loose",  ";AK4 Jet p_{T} (GeV);Pass b-tag", 10,ptbins, 2,effbins);
  h_btag_eff_b_medium           = new TH2D("btag_eff_b_medium", ";AK4 Jet p_{T} (GeV);Pass b-tag", 10,ptbins, 2,effbins);
  h_btag_eff_c_medium           = new TH2D("btag_eff_c_medium", ";AK4 Jet p_{T} (GeV);Pass b-tag", 10,ptbins, 2,effbins);
  h_btag_eff_l_medium           = new TH2D("btag_eff_l_medium", ";AK4 Jet p_{T} (GeV);Pass b-tag", 10,ptbins, 2,effbins);

}


//_______________________________________________________
//               Fill Histograms here
void
ScaleFactors::fill_sf_histos(const bool& varySystematics, const bool& runOnSkim, const unsigned int& syst_index, const double& weight)
{
  if (syst_index == 0) {
    // btag efficiency - No event selection cuts to be applied
    // When making this plot, should remove all baseline cuts
    while (v.Jet.Loop()) {
      if (v.Jet.Jet.pass[v.Jet.i]) {
        if (v.Jet().hadronFlavour==5) {
          h_btag_eff_b_loose ->Fill(v.Jet().pt, v.Jet.LooseBTag.pass[v.Jet.i]);
          h_btag_eff_b_medium->Fill(v.Jet().pt, v.Jet.MediumBTag.pass[v.Jet.i]);
        } else if (v.Jet().hadronFlavour==4) {
          h_btag_eff_c_loose ->Fill(v.Jet().pt, v.Jet.LooseBTag.pass[v.Jet.i]);
          h_btag_eff_c_medium->Fill(v.Jet().pt, v.Jet.MediumBTag.pass[v.Jet.i]);
        } else {
          h_btag_eff_l_loose ->Fill(v.Jet().pt, v.Jet.LooseBTag.pass[v.Jet.i]);
          h_btag_eff_l_medium->Fill(v.Jet().pt, v.Jet.MediumBTag.pass[v.Jet.i]);
        }
      }
    }
  }
}

//_______________________________________________________
//              function to get scaled weight
double
ScaleFactors::get_syst_weight_(const double& weight_nominal, const double& weight_up, const double& weight_down, const double& nSigma)
{
  double w = weight_nominal;
  if (nSigma == 0) {
    return w;
  } else {
    // Compute the weight according to the systematic variation considered
    // Use difference between nominal and up/down as 1 sigma variation
    double dw_up = weight_up - weight_nominal;
    double dw_down = weight_nominal - weight_down;
    if (nSigma >= 0.) {
      w += nSigma*dw_up;
    } else {
      w += nSigma*dw_down;
    }
    return w;
  }
}

double
ScaleFactors::get_syst_weight_(const double& weight_nominal, const double& uncertainty, const double& nSigma)
{
  double w = weight_nominal;
  // Use symmetrical difference for up/down variation
  if (nSigma!=0.) w *= 1.0 + nSigma * uncertainty;
  return w;
}


//_______________________________________________________
//                Calculate scale factors

double ScaleFactors::calc_top_tagging_sf(const double& nSigmaTopTagSF, const double& nSigmaTopTagFastSimSF,
                                         const double& nSigmaTopMisTagSF, const double& nSigmaTopMisTagFastSimSF, const bool& isFastSim) {
  double w = 1;
  while (v.FatJet.HadTop.Loop()) {
    // Gen-matched tags
    if (v.FatJet.HadTop().matchGenHadTop) {
      // Use POG scale factor for tag
      w *= get_syst_weight_(HADTOP_TAG_SF, HADTOP_TAG_SF+HADTOP_TAG_SF_ERR_UP, HADTOP_TAG_SF-HADTOP_TAG_SF_ERR_DOWN, nSigmaTopTagSF);
      // Additionally use our scale factors for FastSim
      if (isFastSim) {
        //double eff, err;
        double eff, err_up, err_down;
        if (std::abs(v.FatJet.HadTop().eta)<1.5) {
          //geteff1D(eff_fast_bTop, v.FatJet.HadTop().pt, eff, err);
          geteff_AE(eff_fast_bTop, v.FatJet.HadTop().pt, eff, err_up, err_down);
        } else {
          //geteff1D(eff_fast_eTop, v.FatJet.HadTop().pt, eff, err);
          geteff_AE(eff_fast_eTop, v.FatJet.HadTop().pt, eff, err_up, err_down);
        }
        //w *= get_syst_weight_(eff, eff+err, eff-err, nSigmaTopTagFastSimSF);
        w *= get_syst_weight_(eff, eff+err_up, eff-err_down, nSigmaTopTagFastSimSF);
      }
    } else {
      // Mis-tags: Top tagging fake rate scale factor
      double eff, err;
      double err_up, err_down;
      //double eff, err_up, err_down;

      /*
      if (std::abs(v.FatJet.HadTop().eta)<1.5) {
        geteff1D(eff_full_fake_bTop, v.FatJet.HadTop().pt, eff, err);
        //geteff_AE(eff_full_fake_bTop, v.FatJet.HadTop().pt, eff, err_up, err_down);
      } else {
        geteff1D(eff_full_fake_eTop, v.FatJet.HadTop().pt, eff, err);
        //geteff_AE(eff_full_fake_eTop, v.FatJet.HadTop().pt, eff, err_up, err_down);
      }
      //w *= get_syst_weight_(eff, eff+err, eff-err, nSigmaTopMisTagSF);
      
      */

      double pT = (v.FatJet.HadTop().pt > 1000 ? 1000 : v.FatJet.HadTop().pt);
      geteff1D(eff_full_POG_Top, pT, eff, err);
      geteff1D(eff_full_POG_Top_up, pT, err_up, err);
      geteff1D(eff_full_POG_Top_down, pT, err_down, err);
      w *= get_syst_weight_(eff, err_up, err_down, nSigmaTopMisTagSF);
      //w *= get_syst_weight_(eff, eff+err_up, eff-err_down, nSigmaTopMisTagSF);
      if (isFastSim) {
        if (std::abs(v.FatJet.HadTop().eta)<1.5) {
          geteff_AE(eff_fast_fake_bTop, v.FatJet.HadTop().pt, eff, err_up, err_down);
        } else {
          geteff_AE(eff_fast_fake_eTop, v.FatJet.HadTop().pt, eff, err_up, err_down);
        }
        w *= get_syst_weight_(eff, eff+err_up, eff-err_down, nSigmaTopMisTagFastSimSF);
      }
    }
  }

  return w;
}

double ScaleFactors::calc_fake_top_0b_mass_tagging_sf(const double& nSigmaTop0BMassTagSF) {
  double w = 1;
  // not a mass tag
  //if (v.GenPart.Top.n==0) while (v.FatJet.HadTop.Loop()) {
  //  //double eff, err;
  //  double eff, err_up, err_down;
  //  if (std::abs(v.FatJet.HadTop().eta)<1.5) {
  //    utils::geteff_AE(eff_full_fake_bm0bTop, v.FatJet.HadTop().pt, eff, err_up, err_down);
  //  } else {
  //    utils::geteff_AE(eff_full_fake_em0bTop, v.FatJet.HadTop().pt, eff, err_up, err_down);	
  //  }
  //  w *= get_syst_weight(eff, eff+err_up, eff-err_down, nSigmaTop0BMassTagSF);
  //}
  
  return w;
}

double ScaleFactors::calc_fake_top_mass_tagging_sf(const double& nSigmaTopMassTagSF) {
  double w = 1;
  //if (nGenTop==0) for (size_t i=0; i<data.FatJet.size(); ++i) {
  //  if( data.FatJet[i].pt          >= 400 &&
  //      std::abs(data.FatJet[i].eta)  <  2.4 &&
  //      data.FatJet[i].msoftdrop >= 105 &&
  //      data.FatJet[i].msoftdrop <  210) {
  //    double eff, err;
  //    // double eff, err_up, err_down;
  //    if (std::abs(data.FatJet[i].eta)<1.5) {
  //      geteff1D(eff_full_fake_bmTop, data.FatJet[i].pt, eff, err);
  //      //geteff_AE(eff_full_fake_bmTop, data.FatJet[i].pt, eff, err_up, err_down);
  //    } else {
  //      geteff1D(eff_full_fake_emTop, data.FatJet[i].pt, eff, err);
  //      //geteff_AE(eff_full_fake_emTop, data.FatJet[i].pt, eff, err_up, err_down);
  //    }
  //    w *= get_syst_weight_(eff, eff+err, eff-err, nSigmaTopMassTagSF);
  //    //w *= get_syst_weight_(eff, eff+err_up, eff-err_down, nSigmaTopMassTagSF);
  //  }
  //}

  return w;
}

double ScaleFactors::calc_fake_top_anti_tagging_sf(const double& nSigmaTopAntiTagSF) {
  double w = 1;
  //if (nGenTop==0) for (size_t i=0; i<data.FatJet.size(); ++i) {
  //  if( data.FatJet[i].pt          >= 400 &&
  //      std::abs(data.FatJet[i].eta)  <  2.4 &&
  //      data.FatJet[i].msoftdrop >= 105 &&
  //      data.FatJet[i].msoftdrop <  210 &&
  //      data.FatJet[i].tau3/data.FatJet[i].tau2 >= 0.46) {
  //    double eff, err;
  //    //double eff, err_up, err_down;
  //    if (std::abs(data.FatJet[i].eta)<1.5) {
  //      geteff1D(eff_full_fake_baTop, data.FatJet[i].pt, eff, err);
  //      //geteff_AE(eff_full_fake_baTop, data.FatJet[i].pt, eff, err_up, err_down);
  //    } else {
  //      geteff1D(eff_full_fake_eaTop, data.FatJet[i].pt, eff, err);
  //      //geteff_AE(eff_full_fake_eaTop, data.FatJet[i].pt, eff, err_up, err_down);
  //    }
  //    w *= get_syst_weight_(eff, eff+err, eff-err, nSigmaTopAntiTagSF);
  //    //w *= get_syst_weight_(eff, eff+err_up, eff-err_down, nSigmaTopAntiTagSF);
  //  }
  //}

  return w;
}

double ScaleFactors::calc_w_tagging_sf(const double& nSigmaWTagSF, const double& nSigmaWTagFastSimSF,
                                       const double& nSigmaWMisTagSF, const double& nSigmaWMisTagFastSimSF, const bool& isFastSim) {
  double w = 1.0;

  while (v.FatJet.Loop()) {
    if (v.FatJet.HadW.pass[v.FatJet.i]) {
      if (v.FatJet().matchGenHadW) {
        // Use POG scale factor for efficiency scale factor
        w *= get_syst_weight_(HADW_TAG_HP_SF, HADW_TAG_HP_SF_ERR, nSigmaWTagSF);
        // Additionally use our scale factors for FastSim
        if (isFastSim) {
          double eff, err_up, err_down;
          if (std::abs(v.FatJet().eta)<1.5) geteff_AE(eff_fast_bW, v.FatJet().pt, eff, err_up, err_down);
          else                                  geteff_AE(eff_fast_eW, v.FatJet().pt, eff, err_up, err_down);
          w *= get_syst_weight_(eff, eff+err_up, eff-err_down, nSigmaWTagFastSimSF);
        }
      } else {
        // W tagging fake rate scale factor
        double eff, err;
        double err_up, err_down;
        if (std::abs(v.FatJet().eta)<1.5) geteff1D(eff_full_fake_bW, v.FatJet().pt, eff, err);
        else                                  geteff1D(eff_full_fake_eW, v.FatJet().pt, eff, err);
        double pT = (v.FatJet().pt > 500 ? 500 : v.FatJet().pt);
        geteffGE(eff_full_POG_W, pT, eff, err);
        w *= get_syst_weight_(eff, eff+err, eff-err, nSigmaWMisTagSF);
        if (isFastSim) {
          if (std::abs(v.FatJet().eta)<1.5) geteff_AE(eff_fast_fake_bW, v.FatJet().pt, eff, err_up, err_down);
          else                                  geteff_AE(eff_fast_fake_eW, v.FatJet().pt, eff, err_up, err_down);
          w *= get_syst_weight_(eff, eff+err_up, eff-err_down, nSigmaWMisTagFastSimSF);
        }
      }
    }
  } 
  //else if (low_purity) {
  //  if (v.FatJet..matchGenHadW) w *= get_syst_weight_(HADW_TAG_LP_SF, HADW_TAG_LP_SF_ERR, nSigmaWTagSF);
  //} 
  return w;
}

double ScaleFactors::calc_fake_w_mass_tagging_sf(const double& nSigmaWMassTagSF) {
  double w = 1.0;

  //for (size_t i=0; i<data.FatJet.size(); ++i) {
  //  bool GenW = false;
  //  if( v.FatJet().pt          >= 200 &&
  //      std::abs(v.FatJet().eta)  <  2.4 &&
  //      v.FatJet().msoftdrop >= 65 &&
  //      v.FatJet().msoftdrop <  105 &&
  //      v.FatJet().tau2/v.FatJet().tau1 < 0.45) {
  //    if (!v.isData_) for(size_t j=0, nGenPart=data.GenPart.size(); j<nGenPart; ++j) {
  //      if ( std::abs(data.GenPart[j].pdgId)==24 ) GenW = true;
  //    }
  //    if (!GenW) {
  //      double eff, err;
  //      //double eff, err_up, err_down;
  //      if (std::abs(v.FatJet().eta)<1.5) {
  //        geteff1D(eff_full_fake_bm0bW, v.FatJet().pt, eff, err);
  //        //geteff_AE(eff_full_fake_bm0bW, v.FatJet().pt, eff, err_up, err_down);
  //      } else {
  //        geteff1D(eff_full_fake_em0bW, v.FatJet().pt, eff, err);
  //        //geteff_AE(eff_full_fake_em0bW, v.FatJet().pt, eff, err_up, err_down);
  //      }
  //      w *= get_syst_weight_(eff, eff+err, eff-err, nSigmaWMassTagSF);
  //      //w *= get_syst_weight_(eff, eff+err_up, eff-err_down, nSigmaWMassTagSF);
  //    }
  //  }
  //}

  return w;
}

double ScaleFactors::calc_fake_w_anti_tagging_sf(const double& nSigmaWAntiTagSF) {
  double w = 1.0;

  //for (size_t i=0; i<data.FatJet.size(); ++i) {
  //  if( v.FatJet().pt          >= 200 &&
  //      std::abs(v.FatJet().eta)  <  2.4 &&
  //      v.FatJet().msoftdrop >= 65 &&
  //      v.FatJet().msoftdrop <  105) {
  //    double eff, err;
  //    //double eff, err_up, err_down;
  //    if (std::abs(v.FatJet().eta)<1.5) {
  //      geteff1D(eff_full_fake_baW, v.FatJet().pt, eff, err);
  //      //geteff_AE(eff_full_fake_baW, v.FatJet().pt, eff, err_up, err_down);
  //    } else {
  //      geteff1D(eff_full_fake_eaW, v.FatJet().pt, eff, err);
  //      //geteff_AE(eff_full_fake_eaW, v.FatJet().pt, eff, err_up, err_down);
  //    }
  //    w *= get_syst_weight_(eff, eff+err, eff-err, nSigmaWAntiTagSF);
  //    //w *= get_syst_weight_(eff, eff+err_up, eff-err_down, nSigmaWAntiTagSF);
  //  }
  //}

  return w;
}


std::pair<double, double> ScaleFactors::calc_b_tagging_sf(const double& nSigmaBTagSF, const double& nSigmaBTagFastSimSF,  const bool& isFastSim) {

  double pMC_loose = 1, pData_loose = 1;
  double pMC_medium = 1, pData_medium = 1;
  while (v.Jet.Loop()) {
    float pt = v.Jet().pt, eta = v.Jet().eta;
    // Jet ID
    if (v.Jet.Jet.pass[v.Jet.i]) {

      // Btag efficiencies (quark flavour dependent)
      BTagEntry::JetFlavor FLAV;
      double eff_medium = 1.0, eff_loose = 1.0;
      if (v.Jet().hadronFlavour==5) {
        FLAV = BTagEntry::FLAV_B;
        eff_loose  = geteff1D(eff_btag_b_loose,  pt, false);
        eff_medium = geteff1D(eff_btag_b_medium, pt, false);
      } else if (v.Jet().hadronFlavour==4) {
        FLAV = BTagEntry::FLAV_C;
        eff_loose  = geteff1D(eff_btag_c_loose,  pt, false);
        eff_medium = geteff1D(eff_btag_c_medium, pt, false);
      } else {
        FLAV = BTagEntry::FLAV_UDSG;
        eff_loose  = geteff1D(eff_btag_l_loose,  pt, false);
        eff_medium = geteff1D(eff_btag_l_medium, pt, false);
      }

      // Scale factors - FullSim
      double sf_loose_cen   = btag_sf_full_loose_ ->eval_auto_bounds("central", FLAV, eta, pt);
      double sf_loose_up    = btag_sf_full_loose_ ->eval_auto_bounds("up",      FLAV, eta, pt);
      double sf_loose_down  = btag_sf_full_loose_ ->eval_auto_bounds("down",    FLAV, eta, pt);
      double sf_medium_cen  = btag_sf_full_medium_->eval_auto_bounds("central", FLAV, eta, pt);
      double sf_medium_up   = btag_sf_full_medium_->eval_auto_bounds("up",      FLAV, eta, pt);
      double sf_medium_down = btag_sf_full_medium_->eval_auto_bounds("down",    FLAV, eta, pt);

      double sf_loose       = get_syst_weight_(sf_loose_cen,  sf_loose_up,  sf_loose_down,  nSigmaBTagSF);
      double sf_medium      = get_syst_weight_(sf_medium_cen, sf_medium_up, sf_medium_down, nSigmaBTagSF);

      // FastSim
      if (isFastSim) {
        sf_loose_cen   = btag_sf_fast_loose_ ->eval_auto_bounds("central", FLAV, eta, pt);
        sf_loose_up    = btag_sf_fast_loose_ ->eval_auto_bounds("up",      FLAV, eta, pt);
        sf_loose_down  = btag_sf_fast_loose_ ->eval_auto_bounds("down",    FLAV, eta, pt);
        sf_medium_cen  = btag_sf_fast_medium_->eval_auto_bounds("central", FLAV, eta, pt);
        sf_medium_up   = btag_sf_fast_medium_->eval_auto_bounds("up",      FLAV, eta, pt);
        sf_medium_down = btag_sf_fast_medium_->eval_auto_bounds("down",    FLAV, eta, pt);

        sf_loose      *= get_syst_weight_(sf_loose_cen,  sf_loose_up,  sf_loose_down,  nSigmaBTagFastSimSF);
        sf_medium     *= get_syst_weight_(sf_medium_cen, sf_medium_up, sf_medium_down, nSigmaBTagFastSimSF);
      }

      // Working points
      if (v.Jet.LooseBTag.pass[v.Jet.i]) {
        pMC_loose   *= eff_loose;
        pData_loose *= eff_loose * sf_loose;
      } else {
        pMC_loose   *= 1 - eff_loose;
        pData_loose *= 1 - eff_loose * sf_loose;
      }

      if (v.Jet.MediumBTag.pass[v.Jet.i]) {
        pMC_medium   *= eff_medium;
        pData_medium *= eff_medium * sf_medium;
      } else {
        pMC_medium   *= 1 - eff_medium;
        pData_medium *= 1 - eff_medium * sf_medium;
      }
    }
  }
  double weight_loose  = pData_loose/pMC_loose;
  double weight_medium = pData_medium/pMC_medium;
  return std::make_pair(weight_loose, weight_medium);
}

std::tuple<double, double> ScaleFactors::calc_ele_sf(const double& nSigmaEleRecoSF, const double& nSigmaEleIDSF, const double& nSigmaEleIsoSF, const double& nSigmaEleFastSimSF,const bool& isFastSim) {
  double reco_sf, reco_sf_err, sf, sf_err;
  double weight_veto  = 1.0, weight_select = 1.0;
  while (v.Electron.Loop()) {
    double pt  = v.Electron().pt;
    double eta = v.Electron().eta;

    // Apply reconstruction scale factor - Warning! strange binning (pt vs eta)
    geteff2D(eff_full_ele_reco, eta, pt, reco_sf, reco_sf_err);
    // If pt is below 20 or above 80 GeV increase error by 1%
    // https://twiki.cern.ch/twiki/bin/view/CMS/EgammaIDRecipesRun2?rev=38#Electron_efficiencies_and_scale
    if (pt<20||pt>=80) reco_sf_err = std::sqrt(reco_sf_err*reco_sf_err + 0.01*0.01);

    // For FullSim scale factors, we apply syst error from each bin separately
    // For FastSim scale factors, we apply a 2% error (per electron leg)

    // Veto Electrons
    // Using previous POG ID scale factors
    // Apply ID + IP scale factor

    
    if (v.Electron.Veto.pass[v.Electron.i]) {
      // RECO
      weight_veto   *= get_syst_weight_(reco_sf, reco_sf_err, nSigmaEleRecoSF);
      // ID + IP
      geteff2D(eff_full_ele_mvalooseid_tightip2d, pt, eta, sf, sf_err);
      weight_veto *= get_syst_weight_(sf, sf_err, nSigmaEleIDSF);
      if (isFastSim) {
        geteff2D(eff_fast_ele_mvalooseid_tightip2d, pt, eta, sf, sf_err);
        weight_veto *= sf;
      }
      
      // ISO
      if (ELE_VETO_MINIISO_CUT == 0.1)
        geteff2D(eff_full_ele_miniiso01, pt, eta, sf, sf_err);
      else if (ELE_VETO_MINIISO_CUT == 0.2)
        geteff2D(eff_full_ele_miniiso02, pt, eta, sf, sf_err);
      else if (ELE_VETO_MINIISO_CUT == 0.4)
        geteff2D(eff_full_ele_miniiso04, pt, eta, sf, sf_err);
      weight_veto *= get_syst_weight_(sf, sf_err, nSigmaEleIsoSF);
      if (isFastSim) {
        // FASTSIM ISO
        if (ELE_VETO_MINIISO_CUT == 0.1)
          geteff2D(eff_fast_ele_miniiso01, pt, eta, sf, sf_err);
        else if (ELE_VETO_MINIISO_CUT == 0.2)
          geteff2D(eff_fast_ele_miniiso02, pt, eta, sf, sf_err);
        else if (ELE_VETO_MINIISO_CUT == 0.4)
          geteff2D(eff_fast_ele_miniiso04, pt, eta, sf, sf_err);
        weight_veto *= sf;
        // Apply 2% error per electron leg
        weight_veto *= get_syst_weight_(1, 0.02, nSigmaEleFastSimSF);
      }
    }

    // Selected Electrons
    if (v.Electron.Select.pass[v.Electron.i]) {
      // RECO
      weight_select   *= get_syst_weight_(reco_sf, reco_sf_err, nSigmaEleRecoSF);
        
      // ID
      geteff2D(eff_full_ele_mediumid, pt, eta, sf, sf_err);
      weight_select *= get_syst_weight_(sf, sf_err, nSigmaEleIDSF);
      if (isFastSim) {
        // FASTSIM ID
        geteff2D(eff_fast_ele_mediumid, pt, eta, sf, sf_err);
        weight_select *= sf;
      }

      // ISO
      if (ELE_SELECT_MINIISO_CUT == 0.1)
        geteff2D(eff_full_ele_miniiso01, pt, eta, sf, sf_err);
      else if (ELE_SELECT_MINIISO_CUT == 0.2)
        geteff2D(eff_full_ele_miniiso02, pt, eta, sf, sf_err);
      else if (ELE_SELECT_MINIISO_CUT == 0.4)
        geteff2D(eff_full_ele_miniiso04, pt, eta, sf, sf_err);
      weight_select *= get_syst_weight_(sf, sf_err, nSigmaEleIsoSF);
      
      if (isFastSim) {
        // FASTSIM ISO
        if (ELE_SELECT_MINIISO_CUT == 0.1)
          geteff2D(eff_fast_ele_miniiso01, pt, eta, sf, sf_err);
        else if (ELE_SELECT_MINIISO_CUT == 0.2)
          geteff2D(eff_fast_ele_miniiso02, pt, eta, sf, sf_err);
        else if (ELE_SELECT_MINIISO_CUT == 0.4)
          geteff2D(eff_fast_ele_miniiso04, pt, eta, sf, sf_err);
        weight_select *= sf;
        // Apply 2% error per electron leg
        weight_select *= get_syst_weight_(1, 0.02, nSigmaEleFastSimSF);
      }
    }
  }

  return std::make_tuple(weight_veto, weight_select);
}

std::tuple<double, double> ScaleFactors::calc_muon_sf(const double& nSigmaMuonTrkSF, const double& nSigmaMuonFullSimSF, const double& nSigmaMuonFastSimSF, const bool& isFastSim) {
  double trk_sf=1, trk_sf_err_up=0, trk_sf_err_down=0, trk_sf_veto=1, trk_sf_veto_err_up=0, trk_sf_veto_err_down=0, sf, sf_err;
  double weight_veto  = 1.0, weight_select = 1.0;
  while (v.Muon.Loop()) {
    double pt  = v.Muon().pt;
    double eta = v.Muon().eta;

    // Tacking efficiency scale factor
    //geteff_AE(eff_full_muon_trk,      eta, trk_sf,      trk_sf_err_up,      trk_sf_err_down);
    //geteff_AE(eff_full_muon_trk_veto, eta, trk_sf_veto, trk_sf_veto_err_up, trk_sf_veto_err_down);

    // Veto Muons
    if (v.Muon.Veto.pass[v.Muon.i]) {
      // Tracking
      weight_veto *= get_syst_weight_(trk_sf_veto, trk_sf_veto+trk_sf_veto_err_up, trk_sf_veto-trk_sf_veto_err_down, nSigmaMuonTrkSF);

      // ID
      geteff2D(eff_full_muon_looseid, pt, eta, sf, sf_err);
      weight_veto *= sf;
      if (isFastSim) {
        // FASTSIM ID
        geteff2D(eff_fast_muon_vetoid, pt, eta, sf, sf_err);
        weight_veto *= sf;
      }
      
      // ISO
      if (MU_VETO_MINIISO_CUT == 0.2)
        geteff2D(eff_full_muon_miniiso02, pt, eta, sf, sf_err);
      else if (MU_VETO_MINIISO_CUT == 0.4)
        geteff2D(eff_full_muon_miniiso04, pt, eta, sf, sf_err);
      weight_veto *= sf;
      
      // IP
      //geteff2D(eff_full_muon_looseip2d, pt, eta, sf, sf_err);
      //weight_veto *= sf;
      
      // Additional systematics
      weight_veto *= get_syst_weight_(1, 0.03, nSigmaMuonFullSimSF);
      if (isFastSim) weight_veto *= get_syst_weight_(1, 0.02, nSigmaMuonFastSimSF);
    }

    // Selected Muons
    if (v.Muon.Select.pass[v.Muon.i]) {
      // Apply Tracking scale factor here
      if (MU_SELECT_PT_CUT<10) {
        weight_select *= get_syst_weight_(trk_sf_veto, trk_sf_veto+trk_sf_veto_err_up, trk_sf_veto-trk_sf_veto_err_down, nSigmaMuonTrkSF);
      } else {
        weight_select *= get_syst_weight_(trk_sf, trk_sf+trk_sf_err_up, trk_sf-trk_sf_err_down, nSigmaMuonTrkSF);
      }

      // ID
      geteff2D(eff_full_muon_mediumid, pt, eta, sf, sf_err);
      weight_select *= sf;
      if (isFastSim) {
        // FASTSIM ID
        geteff2D(eff_fast_muon_mediumid, pt, eta, sf, sf_err);
        weight_select *= sf;
      }
      
      // ISO
      if (MU_SELECT_MINIISO_CUT == 0.2)
        geteff2D(eff_full_muon_miniiso02, pt, eta, sf, sf_err);
      else if (MU_SELECT_MINIISO_CUT == 0.4)
        geteff2D(eff_full_muon_miniiso04, pt, eta, sf, sf_err);
      weight_select *= sf;

      // IP
      //geteff2D(eff_full_muon_tightip2d, pt, eta, sf, sf_err);
      //weight_select *= sf;
      
      // Additional systematics
      weight_select *= get_syst_weight_(1, 0.03, nSigmaMuonFullSimSF);
      if (isFastSim) weight_select *= get_syst_weight_(1, 0.02, nSigmaMuonFastSimSF);
    }
  }

  return std::make_tuple(weight_veto, weight_select);
}

//____________________________________________________
//          Analysis Specific Scale factors
//    (Defined for each search region separately)

void
ScaleFactors::apply_scale_factors(std::vector<double>& all_weights, std::vector<std::vector<double> >& w_nm1,
                                  const unsigned int& s, const std::vector<std::vector<double> >& nSigmaSFs)
{
  bool isFastSim = v.sample.Contains("FastSim");
  size_t i = 0;

  // Don't forget to specify the total number of sigmas you use in settings_*.h !

  // Electron SFs (5 sigmas - reco, fullsim id/iso, fastsim)
  double sf_ele_veto, sf_ele_medium;
  std::tie(sf_ele_veto, sf_ele_medium) = calc_ele_sf(nSigmaSFs[i][s], nSigmaSFs[i+1][s], nSigmaSFs[i+2][s], nSigmaSFs[i+3][s], isFastSim);
  i+=4;

  // Muon SFs (3 sigmas - tracking, fullsim, fastsim)
  double sf_muon_veto, sf_muon_medium;
  std::tie(sf_muon_veto, sf_muon_medium) =  calc_muon_sf(nSigmaSFs[i][s], nSigmaSFs[i+1][s], nSigmaSFs[i+2][s], isFastSim);
  i+=3;

  // b tagging SFs (2 sigma - fullsim, fastsim)
  std::pair<double, double> sf_btag = calc_b_tagging_sf(nSigmaSFs[i][s], nSigmaSFs[i+1][s], isFastSim);
  double sf_btag_loose = sf_btag.first, sf_btag_medium = sf_btag.second;
  i+=2;

  // Select scale factors to use
  for (auto& SF : scale_factors) SF.clear();

  // Control regions
  scale_factors[Region::CR_QCD].push_back(sf_ele_veto);
  scale_factors[Region::CR_QCD].push_back(sf_muon_veto);
  scale_factors[Region::CR_QCD].push_back(sf_btag_loose);

  scale_factors[Region::CR_Top].push_back(sf_ele_veto);
  scale_factors[Region::CR_Top].push_back(sf_muon_veto);
  scale_factors[Region::CR_Top].push_back(sf_btag_medium);

  scale_factors[Region::CR_W].push_back(sf_ele_veto);
  scale_factors[Region::CR_W].push_back(sf_muon_veto);
  scale_factors[Region::CR_W].push_back(sf_btag_loose);
  scale_factors[Region::CR_1LepInv] = scale_factors[Region::CR_Fake] = scale_factors[Region::CR_W];

  scale_factors[Region::CR_2LepInv].push_back(sf_ele_medium);
  scale_factors[Region::CR_2LepInv].push_back(sf_muon_medium);

  scale_factors[Region::CR_1PhoInv].push_back(sf_ele_veto);
  scale_factors[Region::CR_1PhoInv].push_back(sf_muon_veto);

  // Validation regions
  scale_factors[Region::Val_Signal].push_back(sf_ele_veto);
  scale_factors[Region::Val_Signal].push_back(sf_muon_veto);
  scale_factors[Region::Val_Signal].push_back(sf_btag_medium);

  scale_factors[Region::Val_QCD] = scale_factors[Region::CR_QCD];

  // Signal regions
  // veto lep
  scale_factors[Region::SR_Had_1htop].push_back(sf_ele_veto);
  scale_factors[Region::SR_Had_1htop].push_back(sf_muon_veto);
  scale_factors[Region::SR_Had_2htop] = scale_factors[Region::SR_Had_1htop];

  // veto lep, 1b
  scale_factors[Region::Pre_Had].push_back(sf_ele_veto);
  scale_factors[Region::Pre_Had].push_back(sf_muon_veto);
  scale_factors[Region::Pre_Had].push_back(sf_btag_medium);
  scale_factors[Region::SR_Had_V_b_45j] = scale_factors[Region::SR_Had_V_b_6j] = scale_factors[Region::SR_Had_H_b_45j] = scale_factors[Region::SR_Had_H_b_6j] = 
    scale_factors[Region::SR_Had_2H_b_6j] = scale_factors[Region::SR_Had_HV_b_6j] = scale_factors[Region::Pre_Had];
  
  // veto lep, 0b
  scale_factors[Region::SR_Had_1V_0b_34j].push_back(sf_ele_veto);
  scale_factors[Region::SR_Had_1V_0b_34j].push_back(sf_muon_veto);
  scale_factors[Region::SR_Had_1V_0b_34j].push_back(sf_btag_loose);
  scale_factors[Region::SR_Had_1V_0b_5j] = scale_factors[Region::SR_Had_2V_0b_24j] = scale_factors[Region::SR_Had_2V_0b_5j] = 
    scale_factors[Region::SR_Had_1H_0b_34j] = scale_factors[Region::SR_Had_1H_0b_5j] = scale_factors[Region::SR_Had_2H_0b_34j] = scale_factors[Region::SR_Had_2H_0b_5j] =
    scale_factors[Region::SR_Had_HV_0b_24j] = scale_factors[Region::SR_Had_HV_0b_5j] = scale_factors[Region::SR_Had_1V_0b_34j];
  
  // lepton
  scale_factors[Region::Pre_Lep].push_back(sf_ele_medium);
  scale_factors[Region::Pre_Lep].push_back(sf_muon_medium);
  scale_factors[Region::SR_Lep_1htop] = scale_factors[Region::Pre_Lep];

  // lep, 1b
  scale_factors[Region::SR_Lep_V_b].push_back(sf_ele_medium);
  scale_factors[Region::SR_Lep_V_b].push_back(sf_muon_medium);
  scale_factors[Region::SR_Lep_V_b].push_back(sf_btag_medium);
  scale_factors[Region::SR_Lep_H_b] = scale_factors[Region::SR_Lep_V_b];
  
  // lep, 0b
  scale_factors[Region::SR_Lep_V_0b].push_back(sf_ele_medium);
  scale_factors[Region::SR_Lep_V_0b].push_back(sf_muon_medium);
  scale_factors[Region::SR_Lep_V_0b].push_back(sf_btag_loose);
  scale_factors[Region::SR_Lep_H_0b] = scale_factors[Region::SR_Lep_V_0b];
  
  // 0b
  scale_factors[Region::SR_Lepjet_0V_24j].push_back(sf_btag_loose);
  scale_factors[Region::SR_Lepjet_0V_5j] = scale_factors[Region::SR_Lepjet_1V_24j] = scale_factors[Region::SR_Lepjet_1V_5j] = scale_factors[Region::SR_Lepjet_0V_24j];
  
  // N-1 weights
  // Calculate weight for all search regions, but without a specific weight
  for (const auto& region : magic_enum::enum_values<Region>()) {
    if (w_nm1[region].empty()) w_nm1[region].resize(20,1);
    else w_nm1[region].assign(20,1);
    if (!v.isData) {
      size_t n=all_weights.size()+scale_factors[region].size();
      // [i] is the index of the weight to exclude
      for (size_t i=0; i<n; ++i) {
        w_nm1[region][i] = 1;
        // [j] all the rest is applied
        for (size_t j=0; j<n; ++j) if (j!=i) {
          if (j<all_weights.size()) w_nm1[region][i] *= all_weights[j];
          else  w_nm1[region][i] *= scale_factors[region][j-all_weights.size()];
        }
      }
    }
  }
}


#endif // End header guard