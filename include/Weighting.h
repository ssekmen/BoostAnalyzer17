#ifndef WEIGHTING_H
#define WEIGHTING_H

// Private headers
#include "Variables.h"
#include "EventSelections.h"
#include "C1N2_hinoXSEC.h"
#include "C1N2_winoXSEC.h"
#include "GluinoXSec.h"
#include "StopXSec.h"
#include "CharginoXSec.h"
#include "NeutralinoXSec.h"
#include "SquarkXSec.h"

// 3rd party headers
#include "tnm.h" // for getplot
#include "TH2.h"
#include "TH3.h"
#include "TGraphAsymmErrors.h"
#include "TString.h"

// common libraries
#include <algorithm>
#include <iostream>
#include <vector>

class Weighting
{
public:
  Weighting(Variables& var) : v(var) {
    w_nm1.resize(magic_enum::enum_count<EventSelections::Regions>());
    sf_weight.resize(magic_enum::enum_count<EventSelections::Regions>());
    all_weights.resize(10,1);
  }
  ~Weighting() {}

  void init_weight_histos();

  void init_input();

  void fill_weight_histos(const bool&, const bool&, const unsigned int&, const double&);

  double get_xsec_from_ntuple(const std::vector<std::string>&, const bool&);

  std::pair<double, double> get_xsec_totweight_from_txt_file(const std::string&);

  double get_totweight_from_ntuple(const std::vector<std::string>&, const bool&);

  void calc_signal_weightnorm(const std::vector<std::string>&, double&, const bool&, TDirectory*, bool);

  double get_signal_weightnorm();

  void init_pileup_reweighting(const bool&, const std::vector<std::string>&);

  double get_toppt_weight(const double&, const unsigned int&, const bool&);

  double get_isr_weight(const double&, const unsigned int&, const bool&);

  double get_pileup_weight(const double, const double&, const unsigned int&, const bool&);

  double get_l1_prefiring_weight(const double&);

  double get_ht_weight(const double&);

  double get_alphas_weight(const double&, const int&);

  //double get_scale_weight(const std::vector<double>&, const double&, const unsigned int&);
  double get_scale_weight(const double&, const unsigned int&);

  double calc_lostlep_weight(const double&);

  double calc_trigger_efficiency(const double&);

  double weight;
  std::vector<double> all_weights;
  std::vector<double> sf_weight;
  // N-1 weights
  std::vector<std::vector<double> > w_nm1;

  double triggereff_had_nor2 = 1.0;
  double triggereff_lep      = 1.0;
  double triggereff_pho      = 1.0;

  std::map<uint32_t, std::string> signal_bins;

  double get_syst_weight(const double&, const double&, const double&, const double&);

  double get_syst_weight(const double&, const double&, const double&);

  Variables& v;

  // make sure binning is the same as in PlottingBase
  std::vector<double> HT_2D_bins = {200,  450,  600,  700, 800, 900, 1000, 1200, 10000}; // 2D Trigger Eff Run2017-18
  std::vector<double> MET_2D_bins = {60, 100, 130, 160, 180, 200, 250, 300, 400, 4000}; // 2D Trigger Eff Run2017-18
  std::vector<int> merged_trigger_bins = {1,3,5,  11,   20, 37,44,  46,52,53, 55,57,59,61,62, 64,65,66,67,68,69,70,71};

  // ISR weights
  // https://indico.cern.ch/event/592621/contributions/2398559/attachments/1383909/2105089/16-12-05_ana_manuelf_isr.pdf
  // https://indico.cern.ch/event/616816/contributions/2489809/attachments/1418579/2174166/17-02-22_ana_isr_ewk.pdf
  int isr_type = 0;
  std::vector<float> isr_weights_strong = {1, 0.92,  0.821, 0.715, 0.662, 0.561, 0.511};
  std::vector<float> isr_weights_weak = {1, 1.052, 1.179, 1.150, 1.057, 1.000, 0.912, 0.783};
  double isr_normfact = 1;

  //_______________________________________________________
  //                Input histograms

  //TGraphAsymmErrors* eff_trigger;
  //TH3D* eff_3D_trigger_lep;
  //TH3D* eff_3D_trigger_lep_up;
  //TH3D* eff_3D_trigger_lep_down;
  //TH2D* eff_trigger_lep;
  //TH2D* eff_trigger_lep_up;
  //TH2D* eff_trigger_lep_down;
  //TH2D* eff_trigger_pho;
  //TH2D* eff_trigger_pho_up;
  //TH2D* eff_trigger_pho_down;
  //TH2D* eff_trigger_F_met;
  //TH2D* eff_trigger_F_mu;
  //TH2D* eff_trigger_F_ele;
  //TH2D* eff_trigger_F_pho;

  TGraphAsymmErrors* trig_had_mu;
  TGraphAsymmErrors* trig_had_mu_nor2;
  TGraphAsymmErrors* trig_had_ele;
  TGraphAsymmErrors* trig_had_ele_nor2;
  TGraphAsymmErrors* trig_had_pho;
  TGraphAsymmErrors* trig_had_pho_nor2;
  TGraphAsymmErrors* trig_ele;
  TGraphAsymmErrors* trig_mu;
  TGraphAsymmErrors* trig_pho_eb;
  TGraphAsymmErrors* trig_pho_ee;

  TH2F* h_prefmap_photon;
  TH2F* h_prefmap_jet;


  //_______________________________________________________
  //             List of weighting Histograms

  TH1D* h_totweight;
  TH1D* h_totweight_toppt;
  TH1D* h_totweight_pileup;
  std::vector<TH2D*> vh_totweight_signal;
  std::vector<TH2D*> vh_xsec_signal;
  std::vector<TH2D*> vh_weightnorm_signal;
  //std::vector<TH3D*> vh_totweight3D_signal;
  //std::vector<TH3D*> vh_xsec3D_signal;
  //std::vector<TH3D*> vh_weightnorm3D_signal;
  std::map<size_t, double> totweight3D_signal;
  std::map<size_t, double> weightnorm3D_signal;
  TH1D* h_nisrjets;
  TH1D* h_totweight_isr;
  TH1D* h_npvLowHigh_data;
  std::vector<TH3D*> vh_npvLowHigh_signal;
  TH1D* h_pileup_data;
  TH1D* h_pileup_data_down;
  TH1D* h_pileup_data_up;
  TH1D* h_pileup_mc;
  TH1D* h_pileup_weight;
  TH1D* h_pileup_weight_down;
  TH1D* h_pileup_weight_up;
  TH1D* h_nvtx;
  TH1D* h_nvtx_rw;

  TH1D* h_trigger_pass;
  TH1D* h_trigger_total;
  TH2D* h_trigger2d_pass;
  TH2D* h_trigger2d_total;
};

void Weighting::init_input() {
  if (v.isSignal) {
    if (v.sample.Contains("TChi")) {
      isr_type = 1; 
    } else {
      isr_type = 2;
    }

    std::ifstream isrFile("data/isr_normfact.txt");
    // Read all nSigmas, nums
    int year = 0;
    std::string sample = "";
    double normfact = 0;
    std::string line;
    while (std::getline(isrFile, line)) {
      std::stringstream nth_line;
      nth_line<<line;
      nth_line>>year;
      nth_line>>sample;
      nth_line>>normfact;
      if (v.sample == TString(sample) && year == v.year) {
        isr_normfact = normfact;
      }
    }
    std::cout<<"Signal ISR normalization factor: "<<isr_normfact<<std::endl;
  }

  // 1D Trigger efficiency
  //if (v.year==2018) {
  //} else
  //if (v.year==2017) {
  //  TH1D* pass  = getplot_TH1D("trigger_eff/191029/SingleLepton.root", "h_HT_TrigNoMass_1", "trig01");
  //  TH1D* total = getplot_TH1D("trigger_eff/191029/SingleLepton.root", "h_HT_TrigNoMass_0", "trig02");
  //  //TH1D* pass  = getplot_TH1D("trigger_eff/191029/SingleLepton.root", "h_MET_TrigMass_1", "trig01");
  //  //TH1D* total = getplot_TH1D("trigger_eff/191029/SingleLepton.root", "h_MET_TrigMass_0", "trig02");
  //  //TH1D* pass  = getplot_TH1D("trigger_eff/191029/SingleLepton.root", "h_AK8JetMass_TrigMass_1", "trig01");
  //  //TH1D* total = getplot_TH1D("trigger_eff/191029/SingleLepton.root", "h_AK8JetMass_TrigMass_0", "trig02");
  //  eff_trigger = new TGraphAsymmErrors(pass, total, "cl=0.683 b(1,1) mode");
  //}
  
  // L1 prefiring maps
  if (v.year==2016) {
    h_prefmap_photon = getplot_TH2F("data/L1PreFiring/L1PrefiringMaps_WithUL17.root", "L1prefiring_photonptvseta_2016BtoH", "l1prepho");
    h_prefmap_jet    = getplot_TH2F("data/L1PreFiring/L1PrefiringMaps_WithUL17.root", "L1prefiring_jetptvseta_2016BtoH",    "l1prejet");
  } else if (v.year==2017) {
    h_prefmap_photon = getplot_TH2F("data/L1PreFiring/L1PrefiringMaps_WithUL17.root", "L1prefiring_photonptvseta_2017BtoF", "l1prepho");
    h_prefmap_jet    = getplot_TH2F("data/L1PreFiring/L1PrefiringMaps_WithUL17.root", "L1prefiring_jetptvseta_2017BtoF",    "l1prejet");
  }
  
  // Trigger efficiencies from Janos
  if (v.year==2016) {
    trig_had_mu       = getplot_TGraphAsymmErrors("trigger_eff/220502/TriggerEffRun2.root", "2016_had_mu",       "trig1");
    trig_had_mu_nor2  = getplot_TGraphAsymmErrors("trigger_eff/220502/TriggerEffRun2.root", "2016_had_mu_nor2",  "trig2");
    trig_had_ele      = getplot_TGraphAsymmErrors("trigger_eff/220502/TriggerEffRun2.root", "2016_had_ele",      "trig3");
    trig_had_ele_nor2 = getplot_TGraphAsymmErrors("trigger_eff/220502/TriggerEffRun2.root", "2016_had_ele_nor2", "trig4");
    trig_had_pho      = getplot_TGraphAsymmErrors("trigger_eff/220502/TriggerEffRun2.root", "2016_had_pho",      "trig5");
    trig_had_pho_nor2 = getplot_TGraphAsymmErrors("trigger_eff/220502/TriggerEffRun2.root", "2016_had_pho_nor2", "trig6");
    trig_ele          = getplot_TGraphAsymmErrors("trigger_eff/220502/TriggerEffRun2.root", "2016_ele",          "trig7");
    trig_mu           = getplot_TGraphAsymmErrors("trigger_eff/220502/TriggerEffRun2.root", "2016_mu",           "trig8");
    trig_pho_eb       = getplot_TGraphAsymmErrors("trigger_eff/220502/TriggerEffRun2.root", "2016_pho_eb",       "trig9");
    trig_pho_ee       = getplot_TGraphAsymmErrors("trigger_eff/220502/TriggerEffRun2.root", "2016_pho_ee",       "trig10");
  } else if (v.year==2017) {
    trig_had_mu       = getplot_TGraphAsymmErrors("trigger_eff/220502/TriggerEffRun2.root", "2017_had_mu",       "trig1");
    trig_had_mu_nor2  = getplot_TGraphAsymmErrors("trigger_eff/220502/TriggerEffRun2.root", "2017_had_mu_nor2",  "trig2");
    trig_had_ele      = getplot_TGraphAsymmErrors("trigger_eff/220502/TriggerEffRun2.root", "2017_had_ele",      "trig3");
    trig_had_ele_nor2 = getplot_TGraphAsymmErrors("trigger_eff/220502/TriggerEffRun2.root", "2017_had_ele_nor2", "trig4");
    trig_had_pho      = getplot_TGraphAsymmErrors("trigger_eff/220502/TriggerEffRun2.root", "2017_had_pho",      "trig5");
    trig_had_pho_nor2 = getplot_TGraphAsymmErrors("trigger_eff/220502/TriggerEffRun2.root", "2017_had_pho_nor2", "trig6");
    trig_ele          = getplot_TGraphAsymmErrors("trigger_eff/220502/TriggerEffRun2.root", "2017_ele",          "trig7");
    trig_mu           = getplot_TGraphAsymmErrors("trigger_eff/220502/TriggerEffRun2.root", "2017_mu",           "trig8");
    trig_pho_eb       = getplot_TGraphAsymmErrors("trigger_eff/220502/TriggerEffRun2.root", "2017_pho_eb",       "trig9");
    trig_pho_ee       = getplot_TGraphAsymmErrors("trigger_eff/220502/TriggerEffRun2.root", "2017_pho_ee",       "trig10");
  } else if (v.year==2018) {
    trig_had_mu       = getplot_TGraphAsymmErrors("trigger_eff/220502/TriggerEffRun2.root", "2018_had_mu",       "trig1");
    trig_had_mu_nor2  = getplot_TGraphAsymmErrors("trigger_eff/220502/TriggerEffRun2.root", "2018_had_mu_nor2",  "trig2");
    trig_had_ele      = getplot_TGraphAsymmErrors("trigger_eff/220502/TriggerEffRun2.root", "2018_had_ele",      "trig3");
    trig_had_ele_nor2 = getplot_TGraphAsymmErrors("trigger_eff/220502/TriggerEffRun2.root", "2018_had_ele_nor2", "trig4");
    trig_had_pho      = getplot_TGraphAsymmErrors("trigger_eff/220502/TriggerEffRun2.root", "2018_had_pho",      "trig5");
    trig_had_pho_nor2 = getplot_TGraphAsymmErrors("trigger_eff/220502/TriggerEffRun2.root", "2018_had_pho_nor2", "trig6");
    trig_ele          = getplot_TGraphAsymmErrors("trigger_eff/220502/TriggerEffRun2.root", "2018_ele",          "trig7");
    trig_mu           = getplot_TGraphAsymmErrors("trigger_eff/220502/TriggerEffRun2.root", "2018_mu",           "trig8");
    trig_pho_eb       = getplot_TGraphAsymmErrors("trigger_eff/220502/TriggerEffRun2.root", "2018_pho_eb",       "trig9");
    trig_pho_ee       = getplot_TGraphAsymmErrors("trigger_eff/220502/TriggerEffRun2.root", "2018_pho_ee",       "trig10");
  }
  //TMP  } else {
  //TMP  
  //TMP    // 2D Trigger Efficiency (New) - Use combination of SingleElectron + MET datasets
  //TMP    TH2D* lep_pass_2d;
  //TMP    TH2D* lep_total_2d;
  //TMP    if (v.year==2018) {
  //TMP      lep_pass_2d  = getplot_TH2D("trigger_eff/SingleMuonTriggerEff2018_v190804.root",   "h_HT_MET_TriggerEff_1",  "trig11");
  //TMP      lep_total_2d = getplot_TH2D("trigger_eff/SingleMuonTriggerEff2018_v190804.root",   "h_HT_MET_TriggerEff_0",  "trig12");  
  //TMP    } else {
  //TMP      std::cout<<"Weighting::init_input(): trigger not yet defined for 2016"<<std::endl;
  //TMP      std::exit(1);
  //TMP      lep_pass_2d  = getplot_TH2D("trigger_eff/2016_placeholder",   "h_HT_MET_TrigNoMass_1",  "trig03");
  //TMP      lep_total_2d = getplot_TH2D("trigger_eff/2016_placeholder",   "h_HT_MET_TrigNoMass_0",  "trig04");
  //TMP    }
  //TMP    
  //TMP    eff_trigger_lep      = (TH2D*)lep_total_2d->Clone("eff_trigger_lep");      eff_trigger_lep     ->Reset();
  //TMP    eff_trigger_lep_up   = (TH2D*)lep_total_2d->Clone("eff_trigger_lep_up");   eff_trigger_lep_up  ->Reset();
  //TMP    eff_trigger_lep_down = (TH2D*)lep_total_2d->Clone("eff_trigger_lep_down"); eff_trigger_lep_down->Reset();
  //TMP    
  //TMP    for (int i=1; i<lep_total_2d->GetNbinsX()+1; i++) for (int j=1; j<lep_total_2d->GetNbinsY()+1; j++) {
  //TMP      int lep_pass = lep_pass_2d->GetBinContent(i,j), lep_total = lep_total_2d->GetBinContent(i,j);
  //TMP      if (lep_total>0) {
  //TMP        TH1D p("p","",1,0,1); p.SetBinContent(1,lep_pass);  p.SetBinError(1,std::sqrt(lep_pass));
  //TMP        TH1D t("t","",1,0,1); t.SetBinContent(1,lep_total); t.SetBinError(1,std::sqrt(lep_total));
  //TMP        double eff = 0, err_up = 0, err_down = 0;
  //TMP        geteff_AE(TGraphAsymmErrors(&p,&t), 0, eff, err_up, err_down);
  //TMP        //std::cout<<"Trigger efficiency: "<<i<<" "<<j<<" "<<eff-err_down<<" "<<eff<<" "<<eff+err_up<<std::endl;
  //TMP        eff_trigger_lep     ->SetBinContent(i,j,eff);
  //TMP        eff_trigger_lep_up  ->SetBinContent(i,j,eff+err_up);
  //TMP        eff_trigger_lep_down->SetBinContent(i,j,eff-err_down);
  //TMP        // SPECIAL: Set error to the total counts, so we know if a bin is not empty
  //TMP        eff_trigger_lep     ->SetBinError(i,j,lep_total);
  //TMP      }
  //TMP    }
  //TMP    
  //TMP    TH2D* pho_pass_2d;
  //TMP    TH2D* pho_total_2d;
  //TMP    if (v.year==2018) {
  //TMP      pho_pass_2d  = getplot_TH2D("trigger_eff/EGammaTriggerEff2019_v20190906.root",   "h_HT_MET_TriggerEff_1",   "trig7");
  //TMP      pho_total_2d = getplot_TH2D("trigger_eff/EGammaTriggerEff2019_v20190906.root",   "h_HT_MET_TriggerEff_0",  "trig8");
  //TMP    } else if (v.year==2017) {
  //TMP      pho_pass_2d  = getplot_TH2D("trigger_eff/191029/SinglePhoton.root",   "h_HT_MET_TrigNoMass_1",  "trig11");
  //TMP      pho_total_2d = getplot_TH2D("trigger_eff/191029/SinglePhoton.root",   "h_HT_MET_TrigNoMass_0",  "trig12");
  //TMP    } else {
  //TMP      std::cout<<"Weighting::init_input(): trigger not yet defined for 2016"<<std::endl;
  //TMP      std::exit(1);
  //TMP      pho_pass_2d  = getplot_TH2D("trigger_eff/2016_placeholder",   "h_HT_MET_TrigNoMass_1",  "trig11");
  //TMP      pho_total_2d = getplot_TH2D("trigger_eff/2016_placeholder",   "h_HT_MET_TrigNoMass_0",  "trig12");    
  //TMP    }
  //TMP    
  //TMP    eff_trigger_pho      = (TH2D*)pho_total_2d->Clone("eff_trigger_pho");      eff_trigger_pho     ->Reset();
  //TMP    eff_trigger_pho_up   = (TH2D*)pho_total_2d->Clone("eff_trigger_pho_up");   eff_trigger_pho_up  ->Reset();
  //TMP    eff_trigger_pho_down = (TH2D*)pho_total_2d->Clone("eff_trigger_pho_down"); eff_trigger_pho_down->Reset();
  //TMP    
  //TMP    for (int i=1; i<pho_total_2d->GetNbinsX()+1; i++) for (int j=1; j<pho_total_2d->GetNbinsY()+1; j++) {
  //TMP      int pho_pass = pho_pass_2d->GetBinContent(i,j), pho_total = pho_total_2d->GetBinContent(i,j);
  //TMP      if (pho_total>0) {
  //TMP        TH1D p("p","",1,0,1); p.SetBinContent(1,pho_pass);  p.SetBinError(1,std::sqrt(pho_pass));
  //TMP        TH1D t("t","",1,0,1); t.SetBinContent(1,pho_total); t.SetBinError(1,std::sqrt(pho_total));
  //TMP        double eff = 0, err_up = 0, err_down = 0;
  //TMP        geteff_AE(TGraphAsymmErrors(&p,&t), 0, eff, err_up, err_down);
  //TMP        //std::cout<<"Trigger efficiency: "<<i<<" "<<j<<" "<<eff-err_down<<" "<<eff<<" "<<eff+err_up<<std::endl;
  //TMP        eff_trigger_pho     ->SetBinContent(i,j,eff);
  //TMP        eff_trigger_pho_up  ->SetBinContent(i,j,eff+err_up);
  //TMP        eff_trigger_pho_down->SetBinContent(i,j,eff-err_down);
  //TMP        // SPECIAL: Set error to the total counts, so we know if a bin is not empty
  //TMP        eff_trigger_pho     ->SetBinError(i,j,pho_total);
  //TMP      }
  //TMP    }
  //TMP    
  //TMP    // 3D Trigger Efficiency 
  //TMP    TH3D* lep_pass_3d;
  //TMP    TH3D* lep_total_3d;
  //TMP    //if (v.year==2018) {
  //TMP    //} else 
  //TMP    if (v.year==2017) {
  //TMP      lep_pass_3d   = getplot_TH3D("trigger_eff/191029/SingleLepton.root",   "h_HT_MET_AK8JetMass_TrigNoMass_1",  "trig21");
  //TMP      lep_total_3d  = getplot_TH3D("trigger_eff/191029/SingleLepton.root",   "h_HT_MET_AK8JetMass_TrigNoMass_0",  "trig22");
  //TMP      
  //TMP      eff_3D_trigger_lep       = (TH3D*)lep_total_3d ->Clone("eff_3D_trigger_lep");       eff_3D_trigger_lep      ->Reset();
  //TMP      eff_3D_trigger_lep_up    = (TH3D*)lep_total_3d ->Clone("eff_3D_trigger_lep_up");    eff_3D_trigger_lep_up   ->Reset();
  //TMP      eff_3D_trigger_lep_down  = (TH3D*)lep_total_3d ->Clone("eff_3D_trigger_lep_down");  eff_3D_trigger_lep_down ->Reset();
  //TMP      
  //TMP      for (int i=1; i<lep_total_3d->GetNbinsX()+1; i++) {
  //TMP        for (int j=1; j<lep_total_3d->GetNbinsY()+1; j++) {
  //TMP          for (int k=1; k<lep_total_3d->GetNbinsZ()+1; k++) {
  //TMP            int lep_pass = lep_pass_3d->GetBinContent(i,j,k), lep_total = lep_total_3d->GetBinContent(i,j,k);
  //TMP            if (lep_total>0) {
  //TMP              TH1D p("p","",1,0,1); p.SetBinContent(1,lep_pass);  p.SetBinError(1,std::sqrt(lep_pass));
  //TMP              TH1D t("t","",1,0,1); t.SetBinContent(1,lep_total); t.SetBinError(1,std::sqrt(lep_total));
  //TMP              double eff = 0, err_up = 0, err_down = 0;
  //TMP              geteff_AE(TGraphAsymmErrors(&p,&t), 0, eff, err_up, err_down);
  //TMP              //std::cout<<"Trigger efficiency: "<<i<<" "<<j<<" "<<eff-err_down<<" "<<eff<<" "<<eff+err_up<<std::endl;
  //TMP              eff_3D_trigger_lep     ->SetBinContent(i,j,k,eff);
  //TMP              eff_3D_trigger_lep_up  ->SetBinContent(i,j,k,eff+err_up);
  //TMP              eff_3D_trigger_lep_down->SetBinContent(i,j,k,eff-err_down);
  //TMP              // SPECIAL: Set error to the total counts, so we know if a bin is not empty
  //TMP              eff_3D_trigger_lep     ->SetBinError(i,j,k,lep_total);
  //TMP            }
  //TMP          }
  //TMP        }
  //TMP      }
  //TMP    }
  //TMP    
  //TMP    // Same trigger efficiencies but in the F region (needed for fake rates)
  //TMP    const char* fin;
  //TMP    if (v.year==2018) {
  //TMP      fin = "trigger_eff/FakeRates2018.root";
  //TMP    } else if (v.year==2017) {
  //TMP      fin = "trigger_eff/Dec02_Golden_JSON/F_Region.root";
  //TMP    }
  //TMP    eff_trigger_F_met = getplot_TH2D(fin, "met", "trig_f_met");
  //TMP    eff_trigger_F_mu  = getplot_TH2D(fin, "mu",  "trig_f_mu");
  //TMP    eff_trigger_F_ele = getplot_TH2D(fin, "ele", "trig_f_ele");
  //TMP    eff_trigger_F_pho = getplot_TH2D(fin, "pho", "trig_f_pho");
}


//_______________________________________________________
//              Define Histograms here
void
Weighting::init_weight_histos()
{
  // bins
  Double_t gluinoBins[202]; for (int i=0; i<202; ++i) gluinoBins[i] = (i-0.5)*25;
  Double_t stopBins[402];   for (int i=0; i<402; ++i) stopBins[i] = (i-0.5)*5;
  Double_t npvLowHighBins[3] = { 0,20,100 };
  // total weight
  h_totweight                     = new TH1D("totweight",           "MC;;Total (generator) event weight", 1,0,1);
  h_totweight_toppt               = new TH1D("totweight_toppt",     "MC;;Total toppt weight",             2,0,2);
  h_totweight_pileup              = new TH1D("totweight_pileup",    "MC;;Total pileup weight",            2,0,2);
  vh_totweight_signal    .push_back(new TH2D("totweight_T1tttt",    "T1tttt or T5ttcc or T5tttt;m_{#tilde{g}} (GeV);m_{#tilde{#chi}^{0}_{1}} (GeV);Total Weight",        201,gluinoBins, 201,gluinoBins));
  vh_totweight_signal    .push_back(new TH2D("totweight_T2tt",      "T2tt;m_{#tilde{t}} (GeV);m_{#tilde{#chi}^{0}_{1}} (GeV);Total Weight",        401,stopBins, 401,stopBins));
  vh_totweight_signal    .push_back(new TH2D("totweight_TChiHH",    "TChiHH;m_{#tilde{#chi}^{0}_{3}=#tilde{#chi}^{0}_{2}} (GeV);m_{#tilde{#chi}^{0}_{1}} (GeV);Total Weight",        401,stopBins, 401,stopBins));
  vh_totweight_signal    .push_back(new TH2D("totweight_TChi",    "TChi;m_{#tilde{#chi}^{0}_{3}=#tilde{#chi}^{0}_{2}} (GeV);m_{#tilde{#chi}^{0}_{1}} (GeV);Total Weight",        401,stopBins, 401,stopBins));
  vh_totweight_signal    .push_back(new TH2D("totweight_T6qq",    "T6qq;m_{#tilde{#q}} (GeV);m_{#tilde{#chi}^{0}_{2}} (GeV);Total Weight",       401,stopBins, 401,stopBins));
  vh_totweight_signal    .push_back(new TH2D("totweight_T5qqqqZH",  "T5qqqqZH;m_{#tilde{g}} (GeV);m_{#tilde{#chi}^{0}_{2}} (GeV);Total Weight",        201,gluinoBins, 201,gluinoBins));
  // --> too much memory
  //vh_totweight3D_signal  .push_back(new TH3D("totweight_T6bbZH",    "T6bbZH;m_{#tilde{t}} (GeV);#tilde{#chi}^{0}_{2}} (GeV);m_{#tilde{#chi}^{0}_{1}} (GeV);Total Weight", 401,stopBins, 401,stopBins, 401,stopBins));
  // ISR reweighting
  h_nisrjets                      = new TH1D("nisrjets",            ";N_{ISR jets}", 16,-0.5,15.5);
  h_totweight_isr                 = new TH1D("totweight_isr",       "MC;;Total (generator) event weight", 2,0,2);
  // signal weight
  vh_xsec_signal         .push_back(new TH2D("xsec_T1tttt",         "T1tttt or T5ttcc or T5tttt;m_{#tilde{g}} (GeV);m_{#tilde{#chi}^{0}_{1}} (GeV);Cross-section (pb)",  201,gluinoBins, 201,gluinoBins));
  vh_weightnorm_signal   .push_back(new TH2D("weightnorm_T1tttt",   "T1tttt or T5ttcc or T5tttt;m_{#tilde{g}} (GeV);m_{#tilde{#chi}^{0}_{1}} (GeV);weight norm. factor", 201,gluinoBins, 201,gluinoBins));
  vh_xsec_signal         .push_back(new TH2D("xsec_T2tt",           "T2tt;m_{#tilde{t}} (GeV);m_{#tilde{#chi}^{0}_{1}} (GeV);Cross-section (pb)",  401,stopBins, 401,stopBins));
  vh_weightnorm_signal   .push_back(new TH2D("weightnorm_T2tt",     "T2tt;m_{#tilde{t}} (GeV);m_{#tilde{#chi}^{0}_{1}} (GeV);weight norm. factor", 401,stopBins, 401,stopBins));
  vh_xsec_signal         .push_back(new TH2D("xsec_TChiHH",         "TChiHH;m_{#tilde{#chi}^{0}_{3}=#tilde{#chi}^{0}_{2}} (GeV);m_{#tilde{#chi}^{0}_{1}} (GeV);Cross-section (pb)",  401,stopBins, 401,stopBins));
  vh_weightnorm_signal   .push_back(new TH2D("weightnorm_TChiHH",   "TChiHH;m_{#tilde{#chi}^{0}_{3}=#tilde{#chi}^{0}_{2}} (GeV);m_{#tilde{#chi}^{0}_{1}} (GeV);weight norm. factor", 401,stopBins, 401,stopBins));
  vh_xsec_signal         .push_back(new TH2D("xsec_TChi",         "TChi;m_{#tilde{#chi}^{#pm}_{0}=#tilde{#chi}^{0}_{2}} (GeV);m_{#tilde{#chi}^{0}_{1}} (GeV);Cross-section (pb)",  401,stopBins, 401,stopBins));
  vh_weightnorm_signal   .push_back(new TH2D("weightnorm_TChi",   "TChi;m_{#tilde{#chi}^{#pm}_{0}=#tilde{#chi}^{0}_{2}} (GeV);m_{#tilde{#chi}^{0}_{1}} (GeV);weight norm. factor", 401,stopBins, 401,stopBins));
  vh_xsec_signal         .push_back(new TH2D("xsec_T6qq",         "T6qq;m_{#tilde{#q}} (GeV);m_{#tilde{#chi}^{0}_{2}} (GeV);Cross-section (pb)",  401,stopBins, 401,stopBins));
  vh_weightnorm_signal   .push_back(new TH2D("weightnorm_T6qq",   "T6qq;m_{#tilde{#q}} (GeV);m_{#tilde{#chi}^{0}_{2}} (GeV);weight norm. factor", 401,stopBins, 401,stopBins));
  vh_xsec_signal         .push_back(new TH2D("xsec_T5qqqqZH",       "T5qqqqZH;m_{#tilde{g}} (GeV);m_{#tilde{#chi}^{0}_{2}} (GeV);Cross-section (pb)",  201,gluinoBins, 201,gluinoBins));
  vh_weightnorm_signal   .push_back(new TH2D("weightnorm_T5qqqqZH", "T5qqqqZH;m_{#tilde{g}} (GeV);m_{#tilde{#chi}^{0}_{2}} (GeV);weight norm. factor", 201,gluinoBins, 201,gluinoBins));
  // --> too much memory
  //vh_xsec3D_signal       .push_back(new TH3D("xsec_T6bbZH",         "T6bbZH;m_{#tilde{#chi}^{#pm}_{0} (GeV);#tilde{#chi}^{0}_{2}} (GeV);m_{#tilde{#chi}^{0}_{1}} (GeV);Cross-section (pb)",  401,stopBins, 401,stopBins, 401,stopBins));
  //vh_weightnorm3D_signal .push_back(new TH3D("weightnorm_T6bbZH",   "T6bbZH;m_{#tilde{t}} (GeV);#tilde{#chi}^{0}_{2}} (GeV);m_{#tilde{#chi}^{0}_{1}} (GeV);weight norm. factor", 401,stopBins, 401,stopBins, 401,stopBins));
  // npv for extrapolations
  h_npvLowHigh_data               = new TH1D("npvLowHigh_data",     "Number of vertices - Data;N_{Vertices}", 2,npvLowHighBins);
  vh_npvLowHigh_signal   .push_back(new TH3D("npvLowHigh_T1tttt",   "T1tttt or T5ttcc or T5tttt;m_{#tilde{g}} (GeV);m_{#tilde{#chi}^{0}_{1}} (GeV);N_{vertex}", 201,gluinoBins, 201,gluinoBins, 2,npvLowHighBins));
  vh_npvLowHigh_signal   .push_back(new TH3D("npvLowHigh_T2tt",     "T2tt;m_{#tilde{t}} (GeV);m_{#tilde{#chi}^{0}_{1}} (GeV);N_{vertex}",                       401,stopBins, 401,stopBins,     2,npvLowHighBins));
  vh_npvLowHigh_signal   .push_back(new TH3D("npvLowHigh_TChiWZ",   "TChiWZ;m_{#tilde{#chi}^{#pm}_{0}=#tilde{#chi}^{0}_{2}} (GeV);m_{#tilde{#chi}^{0}_{1}} (GeV);N_{vertex}", 401,stopBins, 401,stopBins,     2,npvLowHighBins));
  vh_npvLowHigh_signal   .push_back(new TH3D("npvLowHigh_TChiHH",   "TChiHH;m_{#tilde{#chi}^{0}_{3}=#tilde{#chi}^{0}_{2}} (GeV);m_{#tilde{#chi}^{0}_{1}} (GeV);N_{vertex}", 401,stopBins, 401,stopBins,     2,npvLowHighBins));
  vh_npvLowHigh_signal   .push_back(new TH3D("npvLowHigh_T5qqqqZH", "T5qqqqZH;m_{#tilde{g}} (GeV);m_{#tilde{#chi}^{0}_{1}} (GeV);N_{vertex}", 201,gluinoBins, 201,gluinoBins, 2,npvLowHighBins));
  //vh_npvLowHigh_signal   .push_back(new TH3D("npvLowHigh_T6bbZH",   "T6bbZH;m_{#tilde{t}} (GeV);#tilde{#chi}^{0}_{2}} (GeV);m_{#tilde{#chi}^{0}_{1}} (GeV);N_{vertex}", 201,gluinoBins,201,gluinoBins, 201,gluinoBins, 2,npvLowHighBins));
  // pileup
  h_pileup_data                = new TH1D("pileup_data",        "Pile-up distribution - Data (Nominal);Pile-up", 100,0,100);
  h_pileup_data_down           = new TH1D("pileup_data_down",   "Pile-up distribution - Data (down);Pile-up",    100,0,100);
  h_pileup_data_up             = new TH1D("pileup_data_up",     "Pile-up distribution - Data (up);Pile-up",      100,0,100);
  h_pileup_mc                  = new TH1D("pileup_mc",          "Pile-up distribution - MC;Pile-up",             100,0,100);
  h_pileup_weight              = new TH1D("pileup_weight",      "Pile-up weights - Nominal MB X-sec (69 mb);Pile-up;Weight",    100,0,100);
  h_pileup_weight_down         = new TH1D("pileup_weight_down", "Pile-up weights - MB X-sec up 5% (72.45 mb);Pile-up;Weight",   100,0,100);
  h_pileup_weight_up           = new TH1D("pileup_weight_up",   "Pile-up weights - MB X-sec down 5% (65.55 mb);Pile-up;Weight", 100,0,100);
  h_nvtx                       = new TH1D("nvtx",               "Number of vertices - Nominal;N_{Vertices}",                      101,-0.5,100.5);
  h_nvtx_rw                    = new TH1D("nvtx_rw",            "Number of vertices - Pile-up reweighted (MC only);N_{Vertices}", 101,-0.5,100.5);

  // trigger efficiency
  double htbins[19]  = { 0, 200, 300, 400, 500, 600, 650, 700, 750, 800, 850, 900, 950, 1000, 1200, 1500, 2000, 4000, 10000 };
  double HTB[12] = {400, 500, 600, 700, 750, 800, 850, 900, 950, 1000, 1500, 10000};
  double ptB[9]  = {200, 300, 400, 450, 500, 550, 600, 1000, 10000};
  h_trigger_pass                = new TH1D("trigger_pass",    "Pass trigger;H_{T} (GeV)", 18,htbins);
  h_trigger_total               = new TH1D("trigger_total",          "Total;H_{T} (GeV)", 18,htbins);
  h_trigger2d_pass              = new TH2D("trigger2d_pass",  "Pass trigger;H_{T} (GeV);Leading AK8 jet p_{T} (GeV)", 11,HTB, 8,ptB);
  h_trigger2d_total             = new TH2D("trigger2d_total",        "Total;H_{T} (GeV);Leading AK8 jet p_{T} (GeV)", 11,HTB, 8,ptB);

}

//_______________________________________________________
//               Fill Histograms here
void
Weighting::fill_weight_histos(const bool& varySystematics, const bool& runOnSkim, const unsigned int& syst_index, const double& weight)
{
  // ISR jets counting
  // Taken from:
  // https://github.com/manuelfs/babymaker/blob/0136340602ee28caab14e3f6b064d1db81544a0a/bmaker/plugins/bmaker_full.cc#L1268-L1295
  if (!v.isData&&syst_index==0) {
    h_nisrjets->Fill(v.nJetISR, weight);
  }
  if (runOnSkim) {
    if (syst_index == 0) {
      // trigger efficiency, measured in single lepton datasets
      // SingleElectron dataset: Pass HLT_Ele27_WPTight_Gsf && 1 Electron
      // SingleMuon     dataset: Pass HLT_IsoMu27 && 1 Muon
      // SinglePhoton   dataset: Pass all single photon triggers && 1 Photon
      // Baseline cuts to be applied: 3 jets, 1 AK8 jet, MR & R^2
      bool pass_aux_trigger = 0;
      int njet = v.Jet.Jet.n;
      double R2 = v.R2;
      double MR = v.MR;
      if (v.sample.Contains("MET")) {
        if (v.HLT_PFMET120_PFMHT120_IDTight==1&&v.nLepVeto==0&&v.Tau.Veto.n==0) pass_aux_trigger = 1;
      } else if (v.sample.Contains("SingleElectron")) {
        if ((v.HLT_Ele32_WPTight_Gsf==1)&&v.Electron.Veto.n==1&&v.Muon.Veto.n==0) pass_aux_trigger = 1;
      } else if (v.sample.Contains("SingleMuon")) {
        if (v.HLT_IsoMu27==1&&v.Muon.Veto.n==1&&v.Electron.Veto.n==0) pass_aux_trigger = 1;
      } else if (v.sample.Contains("SinglePhoton")) {
        bool OR_HLT_Photon =
          v.HLT_Photon200==1 ||
          v.HLT_Photon300_NoHE==1;
        if (OR_HLT_Photon==1&&v.Photon.Select.n==1&&v.nLepVeto==0&&v.Tau.Veto.n==0) pass_aux_trigger = 1;
        njet = v.Jet.JetNoPho.n;
        R2 = v.R2_pho;
        MR = v.MR_pho;
      }
      if (pass_aux_trigger) {
        if (v.FatJet.JetAK8.n>=1 && njet>=3 && MR>=800 && R2>=0.08) {
          if (v.HLT_AK8PFJet450==1 || v.HLT_PFHT1050==1) {
            h_trigger_pass  ->Fill(v.AK4_Ht);
            h_trigger2d_pass->Fill(v.AK4_Ht, v.FatJet.JetAK8(0).pt);
          }
          h_trigger_total   ->Fill(v.AK4_Ht);
          h_trigger2d_total ->Fill(v.AK4_Ht, v.FatJet.JetAK8(0).pt);
        }
      }
    } // end syst_index == 0
  } else {
    // Skimming only histos
    // Save the number of vertices in Data and Signal
    if (v.isData) {
      // Use baseline selection
      if (v.FatJet.JetAK8.n>=1 && v.Jet.Jet.n>=3 && v.MR>=800 && v.R2>=0.08) {
        if (v.HLT_AK8PFJet450==1 || v.HLT_PFHT1050==1) h_npvLowHigh_data->Fill(v.PV_npvsGood);
      }
    } else if (v.isSignal) {
      if (v.sample.Contains("T2tt")) vh_npvLowHigh_signal[1]->Fill(v.susy_mass[0], v.susy_mass[1], v.PV_npvsGood);
      else                          vh_npvLowHigh_signal[0]->Fill(v.susy_mass[0], v.susy_mass[1], v.PV_npvsGood);
    }
  }
}


//_______________________________________________________
//           Read cross-section from ntuple
double
Weighting::get_xsec_from_ntuple(const std::vector<std::string>& filenames, const bool& runOnSkim)
{
  float evt_XSec=0, prev_XSec=0;
  for (const auto& filename : filenames) {
    TFile *f = TFile::Open(filename.c_str());
    TTree* tree = (TTree*)f->Get(runOnSkim ? "B2GTree" : "B2GTTreeMaker/B2GTree");
    tree->GetBranch("evt_XSec")->SetAddress(&evt_XSec);
    tree->GetEntry(0);
    f->Close();
    if (prev_XSec!=0&&prev_XSec!=evt_XSec) {
      error("Weighting - Files added with different cross-sections. Please, add them separately!");
      return 0;
    }
    prev_XSec = evt_XSec;
  }
  return evt_XSec;
}

//_______________________________________________________
//           Read cross-section from txt file
std::pair<double, double>
Weighting::get_xsec_totweight_from_txt_file(const std::string& txt_file)
{
  double XSec = 0, Totweight = 0;
  std::ifstream xsecFile(txt_file.c_str());
  if ( !xsecFile.good() ) {
    return std::make_pair(0,0);
    std::cout<<"Unable to open cross-section file: "<<txt_file<<std::endl;
    error("Please provide the correct txt file for Cross-sections in settings.h!");
  } else {

    std::string line;
    std::string shortname, primary_dataset;
    double xsec, totweight;
    while ( std::getline(xsecFile, line) ) {
      std::stringstream nth_line;
      nth_line<<line;
      nth_line>>shortname;
      nth_line>>primary_dataset;
      nth_line>>xsec;
      nth_line>>totweight;
      // For skimmed samples, remove certain postfixes
      // Please, synchronize with setup.py script
      //std::string dirname = sample;
      //for (std::string pf : { "_2", "_ext1", "_ext2", "_ext3", "_ext4", "_backup", "_unskimmed" })
      //if (TString(dirname).EndsWith(pf.c_str())) dirname.erase(dirname.size()-pf.size(), pf.size());
      if (v.sample.Contains(primary_dataset)) {
        XSec = xsec;
        Totweight = totweight;
      }

    }
  }
  if (XSec == 0) {
    std::cout<<"No crossection found for "<<v.sample<<" in cross section file: "<<txt_file<<std::endl;
    error("Please fix the cross-section file in settings.h!");
  }

  return std::make_pair(XSec, Totweight);
}

//_______________________________________________________
//          Read total weight from ntuple histos
double
Weighting::get_totweight_from_ntuple(const std::vector<std::string>& filenames, const bool& runOnSkim)
{
  // Merging totweight histos
  for (const auto& filename : filenames) {
    TFile* f = TFile::Open(filename.c_str());
    h_totweight->Add((TH1D*)f->Get(runOnSkim ? "totweight" : "EventCounter/totweight"));
    //std::cout<<f<<" "<<filename<<" "<<histoname.c_str()<<" "<<f->Get(histoname.c_str())<<" "<<h_totweight->GetBinContent(1)<<std::endl;
    f->Close();
  }
  return h_totweight->GetBinContent(1);
}

//_______________________________________________________
//       Calculate weight normalization for signal
void
Weighting::calc_signal_weightnorm(const std::vector<std::string>& filenames, double& intLumi, const bool& varySystematics, TDirectory* dir, bool verbose=0)
{
  // Find the index of the current signal
  std::string weightname;
  if (v.year== 2018) {
    if (TString(filenames[0]).Contains("T1tttt"))        { v.signal_index = 0; weightname = "data/2018/SMS-T1tttt_TuneCP2_13TeV-madgraphMLM-pythia8.root"; }
    else if (TString(filenames[0]).Contains("T2bW"))     { v.signal_index = 1; weightname = "data/2018/SMS-T2bW_TuneCP2_13TeV-madgraphMLM-pythia8.root"; }
    else if (TString(filenames[0]).Contains("T2bt"))     { v.signal_index = 1; weightname = "data/2018/SMS-T2bt_TuneCP2_13TeV-madgraphMLM-pythia8.root"; }
    else if (TString(filenames[0]).Contains("T2tt"))     { v.signal_index = 1; weightname = "data/2018/SMS-T2tt_TuneCP2_13TeV-madgraphMLM-pythia8.root "; }
    else if (TString(filenames[0]).Contains("T5qqqqVV")) { v.signal_index = 0; weightname = "data/2018/SMS-T5qqqqVV_TuneCP2_13TeV-madgraphMLM-pythia8.root"; }
    else if (TString(filenames[0]).Contains("T5qqqqZH")) { v.signal_index = 0; weightname = "data/2018/SMS-T5qqqqZH-mGluino-1000to2500_TuneCP2_13TeV-madgraphMLM-pythia8.root"; }
    else if (TString(filenames[0]).Contains("T5qqqqHH")) { v.signal_index = 0; weightname = "data/2018/SMS-T5qqqqHH_TuneCP2_13TeV-madgraphMLM-pythia8.root"; }
    else if (TString(filenames[0]).Contains("T5ttcc"))   { v.signal_index = 0; weightname = "data/2018/SMS-T5ttcc_TuneCP2_13TeV-madgraphMLM-pythia8.root"; }
    else if (TString(filenames[0]).Contains("TChiHH_HToBB_HToBB"))                 { v.signal_index = 3; weightname = "data/2018/SMS-TChiHH_HToBB_HToBB_TuneCP2_13TeV-madgraphMLM-pythia8.root"; }
    else if (TString(filenames[0]).Contains("TChiHH_HToBB_HToTauTau"))             { v.signal_index = 3; weightname = "data/2018/SMS-TChiHH_HToBB_HToTauTau_TuneCP2_13TeV-madgraphMLM-pythia8.root"; }
    else if (TString(filenames[0]).Contains("TChiHH_HToGG"))                       { v.signal_index = 3; weightname = "data/2018/SMS-TChiHH_HToGG_TuneCP2_13TeV-madgraphMLM-pythia8.root"; }
    else if (TString(filenames[0]).Contains("TChiHH_HToWWZZTauTau_HToWWZZTauTau")) { v.signal_index = 3; weightname = "data/2018/SMS-TChiHH_HToWWZZTauTau_HToWWZZTauTau_TuneCP2_13TeV-madgraphMLM-pythia8.root"; }
    else if (TString(filenames[0]).Contains("TChiHZ_HToBB_ZToLL"))                 { v.signal_index = 3; weightname = "data/2018/SMS-TChiHZ_HToBB_ZToLL_TuneCP2_13TeV-madgraphMLM-pythia8.root"; }
    else if (TString(filenames[0]).Contains("TChiHZ_HToGG"))                       { v.signal_index = 3; weightname = "data/2018/SMS-TChiHZ_HToGG_TuneCP2_13TeV-madgraphMLM-pythia8.root"; }
    else if (TString(filenames[0]).Contains("TChiWH"))  													 { v.signal_index = 2; weightname = "data/2018/SMS-TChiWH_TuneCP2_13TeV-madgraphMLM-pythia8.root"; }
    else if (TString(filenames[0]).Contains("TChiWZ"))  													 { v.signal_index = 3; weightname = "data/2018/SMS-TChiWZ_TuneCP2_13TeV-madgraphMLM-pythia8.root"; }
    else if (TString(filenames[0]).Contains("TChiHH"))  													 { v.signal_index = 3; weightname = "data/2018/SMS-TChiHH_TuneCP2_13TeV-madgraphMLM-pythia8.root"; }
  } else if (v.year==2017) {
    if (TString(filenames[0]).Contains("T1tttt"))        { v.signal_index = 0; weightname = "data/2017/SMS-T1tttt_TuneCP2_13TeV-madgraphMLM-pythia8.root"; }
    else if (TString(filenames[0]).Contains("T2bW")) { v.signal_index = 1; weightname = "data/2017/SMS-T2bW_TuneCP2_13TeV-madgraphMLM-pythia8.root"; }
    else if (TString(filenames[0]).Contains("T2bt")) { v.signal_index = 1; weightname = "data/2017/SMS-T2bt_TuneCP2_13TeV-madgraphMLM-pythia8.root"; }
    else if (TString(filenames[0]).Contains("T2tt")) { v.signal_index = 1; weightname = "data/2017/SMS-T2tt_TuneCP2_13TeV-madgraphMLM-pythia8.root"; }
    else if (TString(filenames[0]).Contains("T6ttHZ")) { v.signal_index = 1; weightname = "data/2017/SMS-T6ttHZ_TuneCP2_13TeV-madgraphMLM-pythia8.root"; }
    else if (TString(filenames[0]).Contains("T5qqqqVV")) { v.signal_index = 0; weightname = "data/2017/SMS-T5qqqqVV_TuneCP2_13TeV-madgraphMLM-pythia8.root"; }
    else if (TString(filenames[0]).Contains("T5qqqqZH")) { v.signal_index = 0; weightname = "data/2017/SMS-T5qqqqZH-mGluino-1000to2500_TuneCP2_13TeV-madgraphMLM-pythia8.root"; }
    else if (TString(filenames[0]).Contains("T5qqqqHH")) { v.signal_index = 0; weightname = "data/2017/SMS-T5qqqqHH_TuneCP2_13TeV-madgraphMLM-pythia8.root"; }
    else if (TString(filenames[0]).Contains("T5ttcc")) { v.signal_index = 0; weightname = "data/2017/SMS-T5ttcc_TuneCP2_13TeV-madgraphMLM-pythia8.root"; }
    else if (TString(filenames[0]).Contains("TChiHZ_HToBB_ZToLL")) { v.signal_index = 0; weightname = "data/2017/SMS-TChiHZ_HToBB_ZToLL_TuneCP2_13TeV-madgraphMLM-pythia8.root"; }
    else if (TString(filenames[0]).Contains("TChiHZ_HToGG")) { v.signal_index = 0; weightname = "data/2017/SMS-TChiHZ_HToGG_TuneCP2_13TeV-madgraphMLM-pythia8.root"; }
    else if (TString(filenames[0]).Contains("TChiWH_HToGG")) { v.signal_index = 0; weightname = "data/2017/SMS-TChiWH_HToGG_TuneCP2_13TeV-madgraphMLM-pythia8.root"; }
    else if (TString(filenames[0]).Contains("TChiWH_WToLNu_HToBB")) { v.signal_index = 0; weightname = "data/2017/SMS-TChiWH_WToLNu_HToBB_TuneCP2_13TeV-madgraphMLM-pythia8.root"; }
    else if (TString(filenames[0]).Contains("TChiWH_WToLNu_HToVVTauTau")) { v.signal_index = 0; weightname = "data/2017/SMS-TChiWH_WToLNu_HToVVTauTau_TuneCP2_13TeV-madgraphMLM-pythia8.root"; }
    else if (TString(filenames[0]).Contains("TChiZZ_ZToLL")) { v.signal_index = 0; weightname = "data/2017/SMS-TChiZZ_ZToLL_TuneCP2_13TeV-madgraphMLM-pythia8.root"; }
    else if (TString(filenames[0]).Contains("TChiHH_HToBB_HToBB")) { v.signal_index = 3; weightname = "data/2017/SMS-TChiHH_HToBB_HToBB_TuneCP2_13TeV-madgraphMLM-pythia8_RunIIFall17NanoAODv4.root"; }
    else if (TString(filenames[0]).Contains("TChiHH_HToBB_HToTauTau"))             { v.signal_index = 3; weightname = "data/2017/SMS-TChiHH_HToBB_HToTauTau_TuneCP2_13TeV-madgraphMLM-pythia8.root"; }
    else if (TString(filenames[0]).Contains("TChiHH_HToWWZZTauTau_HToWWZZTauTau")) { v.signal_index = 3; weightname = "data/2017/SMS-TChiHH_HToWWZZTauTau_HToWWZZTauTau_TuneCP2_13TeV-madgraphMLM-pythia8.root"; }
    else if (TString(filenames[0]).Contains("TChiHZ_HToBB_ZToLL"))                 { v.signal_index = 3; weightname = "data/2017/SMS-TChiHZ_HToBB_ZToLL_TuneCP2_13TeV-madgraphMLM-pythia8.root"; }
    else if (TString(filenames[0]).Contains("T6qqWZ"))   { v.signal_index = 4; weightname = "data/2017/SMS-T6qqWZ.root"; }
    else if (TString(filenames[0]).Contains("TChiWH"))   { v.signal_index = 3; weightname = "data/2017/SMS-TChiWH_TuneCP2_13TeV-madgraphMLM-pythia8.root"; }
    else if (TString(filenames[0]).Contains("TChiWZ"))   { v.signal_index = 3; weightname = "data/2017/SMS-TChiWZ_TuneCP2_13TeV-madgraphMLM-pythia8.root"; }
    else if (TString(filenames[0]).Contains("TChiHH"))   { v.signal_index = 3; weightname = "data/2017/SMS-TChiHH_TuneCP2_13TeV-madgraphMLM-pythia8.root"; }
    else if (TString(filenames[0]).Contains("T6bbZH"))   { v.signal_index = 5; weightname = "data/2017/SMS-T6bbZH_RunIIFall17NanoAODv5.root"; }
  } else {
    if (TString(filenames[0]).Contains("T2bH_HToGG")) { v.signal_index = 1; weightname = "data/2016/SMS-T2bH_HToGG_TuneCUETP8M1_13TeV-madgraphMLM-pythia8.root"; }
    else if (TString(filenames[0]).Contains("T1tttt"))        { v.signal_index = 0; weightname = "data/2016/SMS-T1tttt_TuneCUETP8M1_13TeV-madgraphMLM-pythia8.root"; }
    else if (TString(filenames[0]).Contains("T2tt")) { v.signal_index = 1; weightname = "data/2016/SMS-T2tt_TuneCUETP8M1_13TeV-madgraphMLM-pythia8.root"; }
    else if (TString(filenames[0]).Contains("T2bW")) { v.signal_index = 1; weightname = "data/2016/SMS-T2bW_TuneCUETP8M1_13TeV-madgraphMLM-pythia8.root"; }
    else if (TString(filenames[0]).Contains("T2bt")) { v.signal_index = 1; weightname = "data/2016/SMS-T2bt_TuneCUETP8M1_13TeV-madgraphMLM-pythia8.root"; }
    else if (TString(filenames[0]).Contains("T5qqqqVV")) { v.signal_index = 0; weightname = "data/2016/SMS-T5qqqqVV_TuneCUETP8M1_13TeV-madgraphMLM-pythia8.root"; }
    else if (TString(filenames[0]).Contains("T5qqqqHH")) { v.signal_index = 0; weightname = "data/2016/SMS-T5qqqqHH_TuneCUETP8M1_13TeV-madgraphMLM-pythia8.root"; }
    else if (TString(filenames[0]).Contains("T5ttcc")) { v.signal_index = 0; weightname = "data/2016/SMS-T5ttcc_TuneCP2_13TeV-madgraphMLM-pythia8.root"; }
    else if (TString(filenames[0]).Contains("TChiHH_HToBB_HToBB"))   { v.signal_index = 3; weightname = "data/2016/SMS-TChiHH_HToBB_HToBB_TuneCUETP8M1_13TeV-madgraphMLM-pythia8.root"; }
    else if (TString(filenames[0]).Contains("TChiHH_HToBB_HToTauTau"))   { v.signal_index = 3; weightname = "data/2016/SMS-TChiHH_HToBB_HToTauTau_TuneCUETP8M1_13TeV-madgraphMLM-pythia8.root"; }
    else if (TString(filenames[0]).Contains("TChiHH_HToGG")) { v.signal_index = 3; weightname = "data/2016/SMS-TChiHH_HToGG_TuneCUETP8M1_13TeV-madgraphMLM-pythia8.root"; }
    else if (TString(filenames[0]).Contains("TChiHH_HToWWZZTauTau_HToWWZZTauTau")) { v.signal_index = 3; weightname = "data/2016/SMS-TChiHH_HToWWZZTauTau_HToWWZZTauTau_TuneCUETP8M1_13TeV-madgraphMLM-pythia8.root"; }
    else if (TString(filenames[0]).Contains("TChiHZ_HToBB_ZToLL")) { v.signal_index = 3; weightname = "data/2016/SMS-TChiHZ_HToBB_ZToLL_TuneCUETP8M1_13TeV-madgraphMLM-pythia8.root"; }
    else if (TString(filenames[0]).Contains("TChiHZ_HToGG")) { v.signal_index = 3; weightname = "data/2016/SMS-TChiHZ_HToGG_TuneCUETP8M1_13TeV-madgraphMLM-pythia8.root"; }
    else if (TString(filenames[0]).Contains("TChiWH_HToGG")) { v.signal_index = 2; weightname = "data/2016/SMS-TChiWH_HToGG_TuneCUETP8M1_13TeV-madgraphMLM-pythia8.root"; }
    else if (TString(filenames[0]).Contains("TChiWH_WToLNu_HToBB")) { v.signal_index = 2; weightname = "data/2016/SMS-TChiWH_WToLNu_HToBB_TuneCUETP8M1_13TeV-madgraphMLM-pythia8.root"; }
    else if (TString(filenames[0]).Contains("TChiWH_WToLNu_HToVVTauTau")) { v.signal_index = 2; weightname = "data/2016/SMS-TChiWH_WToLNu_HToVVTauTau_TuneCUETP8M1_13TeV-madgraphMLM-pythia8.root"; }
    else if (TString(filenames[0]).Contains("TChiWH"))   { v.signal_index = 3; weightname = "data/2016/SMS-TChiWH_TuneCUETP8M1_13TeV-madgraphMLM-pythia8.root"; }
    else if (TString(filenames[0]).Contains("TChiWZ"))   { v.signal_index = 3; weightname = "data/2016/SMS-TChiWZ_TuneCUETP8M1_13TeV-madgraphMLM-pythia8.root"; }
    else if (TString(filenames[0]).Contains("TChiHH"))   { v.signal_index = 3; weightname = "data/2016/SMS-TChiHH_TuneCUETP8M1_13TeV-madgraphMLM-pythia8.root"; }
    else if (TString(filenames[0]).Contains("TChiZZ_ZToLL")) { v.signal_index = 3; weightname = "data/2016/SMS-TChiZZ_ZToLL_TuneCUETP8M1_13TeV-madgraphMLM-pythia8.root"; }
    else if (TString(filenames[0]).Contains("TChiZZ_ZToLL_ZToLL")) { v.signal_index = 3; weightname = "data/2016/SMS-TChiZZ_ZToLL_ZToLL_TuneCUETP8M1_13TeV-madgraphMLM-pythia8.root"; }
  }

  // Merge totweight histos
  std::map<int, double> xsec_mother;
  //TFile* f = TFile::Open(filenames[0].c_str());
  TFile* f = TFile::Open(weightname.c_str());
  // Get total weight
  if (v.signal_index==0) {
    vh_totweight_signal[v.signal_index]->Add((TH2D*)f->Get("totweight_T1tttt"));
  }
  else if (v.signal_index==2) {
    vh_totweight_signal[v.signal_index]->Add((TH2D*)f->Get("totweight_TChiHH"));
  }
  else if (v.signal_index==3) {
    vh_totweight_signal[v.signal_index]->Add((TH2D*)f->Get("totweight_TChi"));
  }
  else if (v.signal_index==4) {
    vh_totweight_signal[v.signal_index]->Add((TH2D*)f->Get("totweight_T6qq"));
  }
  else if (v.signal_index==5) {
    TH3D *h = (TH3D*)f->Get("totweight_T6bbZH");
    for (int binx=1; binx<=401; ++binx) for (int biny=1; biny<=401; ++biny) for (int binz=1; binz<=401; ++binz)
      if (h->GetBinContent(binx,biny,binz)) totweight3D_signal[binx+401*(biny+401*binz)] = h->GetBinContent(binx,biny,binz);
  } else {
    vh_totweight_signal[v.signal_index]->Add((TH2D*)f->Get("totweight_T2tt")); // has equivalent binning to TChiWZ
  }
  f->Close();

  // Set xsec for each gluino/stop mass bin
  // Read gluino/stop xsec from same file used in TTree step
  if(v.signal_index == 5){
    if (verbose) std::cout<<"Normalization variables:"<<std::endl;
    // Calculate weight normalization
    // weightnorm = (settings.intLumi*xsec)/totweight;
    for (const auto& totw : totweight3D_signal) {
      double mMother = ((totw.first%402)-1)*5;
      double mLSP2   = (((totw.first/402)%402)-1)*5;
      double mLSP1   = (((totw.first/402)/402)-1)*5;
      double xsec    = GetStopXSec(mMother).first;
      double tot     = totw.second;
      double wnorm   = intLumi * xsec / tot;
      weightnorm3D_signal[totw.first] = wnorm;
      if (verbose)
        std::cout<<"  Bin: M(b~)="<<mMother<<" M(LSP2)="<<mLSP2<<" M(LSP1)="<<mLSP1<<":   xsec="<<xsec<<" totweight="<<tot<<" weightnorm="<<wnorm<<std::endl;
      uint32_t bin = totw.first;
      std::stringstream ss;
      ss<<"_"<<mMother<<"_"<<mLSP1<<"_"<<mLSP2;
      signal_bins[bin] = ss.str();
    }
  }
  else {
    for (int binx=1, nbinx=vh_xsec_signal[v.signal_index]->GetNbinsX(); binx<=nbinx; ++binx) {
      double mMother = vh_xsec_signal[v.signal_index]->GetXaxis()->GetBinCenter(binx);
      xsec_mother[binx] = (v.signal_index==0) ? GetGluinoXSec(mMother).first : ((v.signal_index==1 || v.signal_index==5) ? GetStopXSec(mMother).first : ((v.signal_index==3 || v.signal_index==2) ? GetC1N2_hinoXSEC(mMother).first : (v.signal_index==4 ? GetSquarkXSec(mMother).first : GetCharginoXSec(mMother).first))); // first: mean xsec (pb), second: error (%)
      for (int biny=1, nbiny=vh_xsec_signal[v.signal_index]->GetNbinsY(); biny<=nbiny; ++biny)
        vh_xsec_signal[v.signal_index]->SetBinContent(binx, biny, xsec_mother[binx]);
    }
    // Calculate weight normalization
    // weightnorm = (settings.intLumi*xsec)/totweight;
    // Divide(h1,h2,c1,c2) --> c1*h1/(c2*h2)
		if (TString(filenames[0]).Contains("TChiWH")){
      if(v.year== 2018)      intLumi = 59740*137.191/101.269;
      else if(v.year== 2017) intLumi = 41529*137.191/101.269;
			else intLumi = 0;
		}
    vh_weightnorm_signal[v.signal_index]->Divide(vh_xsec_signal[v.signal_index], vh_totweight_signal[v.signal_index], intLumi);
    if (verbose) std::cout<<"Normalization variables:"<<std::endl;
    for (int binx=1, nbinx=vh_xsec_signal[v.signal_index]->GetNbinsX(); binx<=nbinx; ++binx) {
      for (int biny=1, nbiny=vh_xsec_signal[v.signal_index]->GetNbinsY(); biny<=nbiny; ++biny) {
        double mMother = vh_xsec_signal[v.signal_index]->GetXaxis()->GetBinCenter(binx);
        double mLSP = vh_xsec_signal[v.signal_index]->GetYaxis()->GetBinCenter(biny);
        double xsec  = vh_xsec_signal[v.signal_index]      ->GetBinContent(binx, biny);
        double totw  = vh_totweight_signal[v.signal_index] ->GetBinContent(binx, biny);
        double wnorm = vh_weightnorm_signal[v.signal_index]->GetBinContent(binx, biny);
        if (totw>0) {
          if (verbose) {
            if (v.signal_index==0) std::cout<<"  Bin: M(g~)=" <<mMother<<" M(LSP)="<<mLSP<<":   xsec="<<xsec<<" totweight="<<totw<<" weightnorm="<<wnorm<<std::endl;
            if (v.signal_index==1) std::cout<<"  Bin: M(s~)="<<mMother<<" M(LSP)="<<mLSP<<":   xsec="<<xsec<<" totweight="<<totw<<" weightnorm="<<wnorm<<std::endl;
            if (v.signal_index==2) std::cout<<"  Bin: M(chi~)="<<mMother<<" M(LSP)="<<mLSP<<":   xsec="<<xsec<<" totweight="<<totw<<" weightnorm="<<wnorm<<std::endl;
            if (v.signal_index==3) std::cout<<"  Bin: M(LSP2)="<<mMother<<" M(LSP)="<<mLSP<<":   xsec="<<xsec<<" totweight="<<totw<<" weightnorm="<<wnorm<<std::endl;
            if (v.signal_index==4) std::cout<<"  Bin: M(q~)="<<mMother<<" M(LSP2)="<<mLSP<<":   xsec="<<xsec<<" totweight="<<totw<<" weightnorm="<<wnorm<<std::endl;
          }
          uint32_t bin = mMother * 10000 + mLSP;
          //std::cout<<"Weighting: uint="<<bin<<std::endl;
          std::stringstream ss;
          ss<<"_"<<mMother<<"_"<<mLSP;
          signal_bins[bin] = ss.str();
        }
      }
    }
  }
}

double Weighting::get_signal_weightnorm() {
  v.get_signal_mass();
  if (v.signal_index==5) {
    return weightnorm3D_signal[size_t((v.susy_mass[0]/5)+1 + 402*((v.susy_mass[2]/5)+1+402*((v.susy_mass[1]/5)+1)))];
  } else if(v.signal_index==4){
    return vh_weightnorm_signal[v.signal_index]->GetBinContent(vh_weightnorm_signal[v.signal_index]->FindBin(1800, 1200));
  } else {
    return vh_weightnorm_signal[v.signal_index]->GetBinContent(vh_weightnorm_signal[v.signal_index]->FindBin(v.susy_mass[0], v.susy_mass[1]));
  }
}


//_______________________________________________________
//             Load pile-up reweighting infos
void
Weighting::init_pileup_reweighting(const bool& runOnSkim, const std::vector<std::string>& filenames)
{
  std::string pileupDir = "pileup/Legacy2017/";
  if (v.year==2016) pileupDir = "pileup/Legacy2016/";
  else if (v.year==2018) pileupDir = "pileup/Legacy2018/";
  // Get data histogram (generated by pileupCalc.py script)
  TFile* f_pileup_data = TFile::Open((pileupDir+"data_pileup.root").c_str());
  h_pileup_data->Add((TH1D*)f_pileup_data->Get("pileup"));
  f_pileup_data->Close();
  // Also get up/down variations
  TFile* f_pileup_data_down = TFile::Open((pileupDir+"data_pileup_down.root").c_str());
  h_pileup_data_down->Add((TH1D*)f_pileup_data_down->Get("pileup"));
  f_pileup_data_down->Close();
  TFile* f_pileup_data_up = TFile::Open((pileupDir+"data_pileup_up.root").c_str());
  h_pileup_data_up->Add((TH1D*)f_pileup_data_up->Get("pileup"));
  f_pileup_data_up->Close();
  // get mc histogram (used to generate mc pile-up)
  TFile* f_pileup_mc = TFile::Open((pileupDir+"mc_pileup.root").c_str());
  h_pileup_mc->Add((TH1D*)f_pileup_mc->Get("pileup"));
  f_pileup_mc->Close();
  // // Get mc histogram saved inside the ntuple (unfiltered pileup distribution)
  // std::cout<<h_pileup_mc->GetEntries()<<std::endl;
  // for (const auto& filename : filenames) {
  //   TFile* f_pileup_mc = TFile::Open(filename.c_str());
  //   h_pileup_mc->Add((TH1D*)f_pileup_mc->Get(runOnSkim ? "pileup_mc" : "EventCounter/pileup"));
  //   f_pileup_mc->Close();
  //   std::cout<<h_pileup_mc->GetEntries()<<std::endl;
  // }
  // Divide normalized data histo by normalized mc histo to get pileup weights for each bin
  h_pileup_weight     ->Divide(h_pileup_data,      h_pileup_mc, 1/h_pileup_data->Integral(),      1/h_pileup_mc->Integral());
  h_pileup_weight_down->Divide(h_pileup_data_down, h_pileup_mc, 1/h_pileup_data_down->Integral(), 1/h_pileup_mc->Integral());
  h_pileup_weight_up  ->Divide(h_pileup_data_up,   h_pileup_mc, 1/h_pileup_data_up->Integral(),   1/h_pileup_mc->Integral());
}

//_______________________________________________________
//              function to get scaled weight
double
Weighting::get_syst_weight(const double& weight_nominal, const double& weight_up, const double& weight_down, const double& nSigma)
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
Weighting::get_syst_weight(const double& weight_nominal, const double& uncertainty, const double& nSigma)
{
  double w = weight_nominal;
  // Use symmetrical difference for up/down variation
  if (nSigma!=0.) w *= 1.0 + nSigma * uncertainty;
  return w;
}


//_______________________________________________________
//                  Top pt reweighting
double
Weighting::get_toppt_weight(const double& nSigmaToppt, const unsigned int& syst_index, const bool& runOnSkim)
{
  double w_nom = 1;//, n=0;
  if (!v.isData) while (v.GenPart.Top.Loop()) {
    double a = 0.0615, b = -0.0005;
    w_nom *= std::exp(a + b * v.GenPart.Top().pt);
  }
  w_nom = std::sqrt(w_nom);
  //std::cout<<"N top = "<<v.GenPart.Top.n<<" w_nom = "<<w_nom<<std::endl<<std::endl;
  double w_toppt_up = 1;
  double w_toppt = std::sqrt(w_nom);
  double w_toppt_down = w_nom; // Nominal weight is typically below 1 (below top pt>123) --> use as down variation
  double w = get_syst_weight(w_toppt, w_toppt_up, w_toppt_down, nSigmaToppt);
  if (syst_index==0&&!runOnSkim) {
    h_totweight_toppt->Fill(0);
    h_totweight_toppt->Fill(1, w_toppt);
  }
  return w;
}

//_______________________________________________________
//                    ISR reweighting
double
Weighting::get_isr_weight(const double& nSigmaISR, const unsigned int& syst_index, const bool& runOnSkim)
{
  // Implementing the reweighting in this presentation:
  // https://indico.cern.ch/event/592621/contributions/2398559/attachments/1383909/2105089/16-12-05_ana_manuelf_isr.pdf
  // Using the values found on slide 8 (T2tt and T1tttt)
  double w = 1;
  isr_weights_strong = {1, 0.92,  0.821, 0.715, 0.662, 0.561, 0.511};
  isr_weights_weak = {1, 1.052, 1.179, 1.150, 1.057, 1.000, 0.912, 0.783};
  // ttbar ISR reweighting not needed, we do top pt reweighting!
  if (v.isSignal) {
    w = 0;
    if (isr_type==1) {
      double EWkino_pt = v.susy_mass[0];
      size_t bin;
      if      (EWkino_pt< 50) bin = 0;
      else if (EWkino_pt<100) bin = 1;
      else if (EWkino_pt<150) bin = 2;
      else if (EWkino_pt<200) bin = 3;
      else if (EWkino_pt<300) bin = 4;
      else if (EWkino_pt<400) bin = 5;
      else if (EWkino_pt<600) bin = 6;
      else bin = 7;
      w = isr_normfact * isr_weights_weak[bin];
    } else {
      size_t bin = std::min(size_t(6), v.nJetISR);
			w = isr_normfact * isr_weights_strong[bin];
    }
    double err = (1-w)/2;
    double w_isr_up   = w + err;
    double w_isr      = w;
    double w_isr_down = w - err;
    w = get_syst_weight(w_isr, w_isr_up, w_isr_down, nSigmaISR);
    h_totweight_isr->Fill(0);
    h_totweight_isr->Fill(1, w_isr);
  }
  return w;
}

//_______________________________________________________
//                  Get pile-up weight
double
Weighting::get_pileup_weight(const double weight, const double& nSigmaPU, const unsigned int& syst_index, const bool& runOnSkim)
{
  if (!v.isSignal) {
    // Background
    int pu_bin = v.Pileup_nTrueInt+1; // eg. pileup 0, is filled in bin 1
    double w_pileup = h_pileup_weight->GetBinContent(pu_bin);
    double w_pileup_up = h_pileup_weight_up->GetBinContent(pu_bin);
    double w_pileup_down = h_pileup_weight_down->GetBinContent(pu_bin);
    double w = get_syst_weight(w_pileup, w_pileup_up, w_pileup_down, nSigmaPU);
    if (syst_index==0&&!runOnSkim) {
      h_totweight_pileup->Fill(0);
      h_totweight_pileup->Fill(1, w_pileup);
    }
    if (syst_index == 0) {
      h_nvtx   ->Fill(v.PV_npvsGood, weight);
      h_nvtx_rw->Fill(v.PV_npvsGood, weight*w);
    }
    return w;
  } else {
    // Signal
    // Do not reweight, but split to a low/high pileup region
    //if (nSigmaPU==1) return v.PV_npvsGood>=h_npvLowHigh_data->GetBinLowEdge(2);
    //else if (nSigmaPU==-1) return v.PV_npvsGood<h_npvLowHigh_data->GetBinLowEdge(2);
    return 1;
  }
}


//_______________________________________________________
//          Get L1 prefiring weight for 2016/2017
double
Weighting::get_l1_prefiring_weight(const double& nSigmaL1PreFiring)
{
  // Background and Signal
  if (v.year==2016||v.year==2017) {
    if (v.isSignal) {
      // Implement by hand: PhysicsTools/PatUtils/plugins/L1ECALPrefiringWeightProducer.cc
      //Probability for the event NOT to prefire, computed with the prefiring maps per object.
      //Up and down values correspond to the resulting value when shifting up/down all prefiring rates in prefiring maps.
      bool useEMpt_ = false;
      double prefiringRateSystUnc_ = 0.2;
      double nonPrefiringProba[3] = {1., 1., 1.};  //0: central, 1: up, 2: down
      
      // Photons
      while (v.Photon.Loop()) {
        double pt_gam  = v.Photon().pt;
        double eta_gam = v.Photon().eta;
        if (pt_gam>=20 && std::abs(eta_gam)>=2 && std::abs(eta_gam)<=3) {
          // getPrefiringRate
          int nbinsy = h_prefmap_photon->GetNbinsY();
          double maxy = h_prefmap_photon->GetYaxis()->GetBinLowEdge(nbinsy + 1);
          if (pt_gam >= maxy) pt_gam = maxy - 0.01;
          int thebin = h_prefmap_photon->FindBin(eta_gam, pt_gam);
          double prefrate = h_prefmap_photon->GetBinContent(thebin);
          double statuncty = h_prefmap_photon->GetBinError(thebin);
          double systuncty = prefiringRateSystUnc_ * prefrate;
          double prefrate_up = std::min(1., prefrate + sqrt(pow(statuncty, 2) + pow(systuncty, 2)));
          double prefrate_dn = std::max(0., prefrate - sqrt(pow(statuncty, 2) + pow(systuncty, 2)));
          nonPrefiringProba[0] *= (1. - prefrate);
          nonPrefiringProba[1] *= (1. - prefrate_up);
          nonPrefiringProba[2] *= (1. - prefrate_dn);
        }
      } // end photon loop
      
      //Now applying the prefiring maps to jets in the affected regions.
      while (v.Jet.Loop()) {
        double pt_jet  = v.Jet().pt_nom;
        double eta_jet = v.Jet().eta;
        if (pt_jet>=20 && std::abs(eta_jet)>=2 && std::abs(eta_jet)<=3) {
      
          //Loop over photons to remove overlap
          double nonprefiringprobfromoverlappingphotons[3] = {1., 1., 1.};
          while (v.Photon.Loop()) {
            double pt_gam  = v.Photon().pt;
            double eta_gam = v.Photon().eta;
            if (pt_gam>=20 && std::abs(eta_gam)>=2 && std::abs(eta_gam)<=3) {
              double dR = DeltaR(v.Photon.v4(), v.Jet.v4());
              if (dR<=0.4) {
                // getPrefiringRate
                int nbinsy = h_prefmap_photon->GetNbinsY();
                double maxy = h_prefmap_photon->GetYaxis()->GetBinLowEdge(nbinsy + 1);
                if (pt_gam >= maxy) pt_gam = maxy - 0.01;
                int thebin = h_prefmap_photon->FindBin(eta_gam, pt_gam);
                double prefrate = h_prefmap_photon->GetBinContent(thebin);
                double statuncty = h_prefmap_photon->GetBinError(thebin);
                double systuncty = prefiringRateSystUnc_ * prefrate;
                double prefrate_up = std::min(1., prefrate + sqrt(pow(statuncty, 2) + pow(systuncty, 2)));
                double prefrate_dn = std::max(0., prefrate - sqrt(pow(statuncty, 2) + pow(systuncty, 2)));
                nonprefiringprobfromoverlappingphotons[0] = (1. - prefrate);
                nonprefiringprobfromoverlappingphotons[1] = (1. - prefrate_up);
                nonprefiringprobfromoverlappingphotons[2] = (1. - prefrate_dn);
              }
            }
          } // end photon loop within jet loop
          
          //useEMpt =true if one wants to use maps parametrized vs Jet EM pt instead of pt.
          if (useEMpt_) pt_jet *= (v.Jet().neEmEF + v.Jet().chEmEF);
          // getPrefiringRate
          int nbinsy = h_prefmap_jet->GetNbinsY();
          double maxy = h_prefmap_jet->GetYaxis()->GetBinLowEdge(nbinsy + 1);
          if (pt_jet >= maxy) pt_jet = maxy - 0.01;
          int thebin = h_prefmap_jet->FindBin(eta_jet, pt_jet);
          double prefrate = h_prefmap_jet->GetBinContent(thebin);
          double statuncty = h_prefmap_jet->GetBinError(thebin);
          double systuncty = prefiringRateSystUnc_ * prefrate;
          double prefrate_up = std::min(1., prefrate + sqrt(pow(statuncty, 2) + pow(systuncty, 2)));
          double prefrate_dn = std::max(0., prefrate - sqrt(pow(statuncty, 2) + pow(systuncty, 2)));
          double nonprefiringprobfromoverlappingjet[3] = {1. - prefrate, 1. - prefrate_up, 1. - prefrate_dn};
          for (int i=0; i<3; ++i) {
            if (nonprefiringprobfromoverlappingphotons[i] == 1.)
              nonPrefiringProba[i] *= nonprefiringprobfromoverlappingjet[i];
            //If overlapping photons have a non prefiring rate larger than the jet, then replace these weights by the jet one
            else if (nonprefiringprobfromoverlappingphotons[i] > nonprefiringprobfromoverlappingjet[i]) {
              if (nonprefiringprobfromoverlappingphotons[i] != 0.)
                nonPrefiringProba[i] *= nonprefiringprobfromoverlappingjet[i] / nonprefiringprobfromoverlappingphotons[i];
              else 
                nonPrefiringProba[i] = 0.;
            }
          }
          //Last case: if overlapping photons have a non prefiring rate smaller than the jet, don't consider the jet in the event weight, and do nothing.
        }
      } // end jet loop
      return get_syst_weight(nonPrefiringProba[0], nonPrefiringProba[1], nonPrefiringProba[2], nSigmaL1PreFiring);
    } else {
      // Get it from ntuple
      return get_syst_weight(v.L1PreFiringWeight_Nom, v.L1PreFiringWeight_Up, v.L1PreFiringWeight_Dn, nSigmaL1PreFiring);
    }
  }
  return 1;
}



//____________________________________________________
//                  HT reweighting

double
Weighting::get_ht_weight(const double& nSigmaHT)
{
  // Using method described by Julie Hogan:
  // https://indico.cern.ch/event/508384/contributions/2029874/attachments/1255336/1852975/JetRwtIssues_B2GWkshp_040816.pdf
  // Use linear functions calculated with scripts/CalcHTScaleFactors.C macro
  // linear function(s): p0 + p1 * HT

  // Silver JSON
  /*
    const double p0[2]     = { 1.16434, 1.00188 };
    const double p0_err[2] = { 0.00459931, 0.0266651 };
    const double p1[2]     = { -0.000142391, -7.80628e-05 };
    const double p1_err[2] = { 3.62929e-06, 1.11035e-05 };
  */
  
  // Golden JSON
  const double p0[2]     = { 1.17155, 1.00513 };
  const double p0_err[2] = { 0.00477137, 0.028861 };
  const double p1[2]     = { -0.000143935, -7.81881e-05 };
  const double p1_err[2] = { 3.79477e-06, 1.20209e-05 };

  // Calculate unscaled jet HT
  double ht = 0;
  while (v.FatJet.Loop()) ht += v.FatJet().pt;
  
  double w = 1.0;
  if (ht>=800&&ht<2000)
    w *= get_syst_weight(p0[0], p0_err[0]/p0[0], nSigmaHT) + get_syst_weight(p1[0], p1_err[0]/p1[0], nSigmaHT) * ht;
  else if (ht>=2000)
    w *= get_syst_weight(p0[1], p0_err[1]/p0[1], nSigmaHT) + get_syst_weight(p1[1], p1_err[1]/p1[1], nSigmaHT) * ht;

  return w;
}


//_______________________________________________________
//                  Get alpha_s weight
double
Weighting::get_alphas_weight(const double& nSigmaAlphaS, const int& LHA_PDF_ID)
{
  /*
  std::vector<float> alphas_Weights; // not available in NanoAOD

  // A set of two weights corresponding to
  // Powheg:  alpha_s = 0.118 -+ 0.002
  // aMC@NLO: alpha_s = 0.118 -+ 0.001
  // Recommendation is to use +- 0.0015 --> rescale difference by 0.75 or 1.5
  // Treat weight as usual, gaussian, rescale to desired nSigma
  double w_alphas = 1;
  //double w_alphas_up   = alphas_Weights[1];
  //double w_alphas_down = alphas_Weights[0];
  double w_alphas_up   = 0;
  double w_alphas_down = 0;
  double nSigma_0_0015 = nSigmaAlphaS;
  if (LHA_PDF_ID==260000||LHA_PDF_ID==260400) {
    // Powheg samples have -+ 0.001
    nSigma_0_0015 *= 1.5;
  } else {
    // aMC@NLO samples have -+ 0.002
    nSigma_0_0015 *= 0.75;
  }
  w_alphas = get_syst_weight(w_alphas, w_alphas_up, w_alphas_down, nSigma_0_0015);
  return w_alphas;
  */
  return 1;
}


//_______________________________________________________
//                  Get scale weight
double
//Weighting::get_scale_weight(const std::vector<double>& scale_weight_norm, const double& nSigmaScale, const unsigned int& numScale)
Weighting::get_scale_weight(const double& nSigmaScale, const unsigned int& numScale)
{
  //std::vector<float> scale_Weights;
  /*
    New LHEScaleWeight in NanoAOD:
    LHE scale variation weights (w_var / w_nominal); 
    v.LHEScaleWeight[0] is rensc=0.5d0 facsc=0.5d0
    v.LHEScaleWeight[1] is rensc=0.5d0 facsc=1d0
    v.LHEScaleWeight[2] is rensc=0.5d0 facsc=2d0
    v.LHEScaleWeight[3] is rensc=  1d0 facsc=0.5d0
    v.LHEScaleWeight[4] is rensc=  1d0 facsc=1d0
    v.LHEScaleWeight[5] is rensc=  1d0 facsc=2d0
    v.LHEScaleWeight[6] is rensc=  2d0 facsc=0.5d0
    v.LHEScaleWeight[7] is rensc=  2d0 facsc=1d0
    v.LHEScaleWeight[8] is rensc=  2d0 facsc=2d0 
  */
  if (nSigmaScale==0) return 1; // No systematics
  if (v.nLHEScaleWeight==0) return 1; // ST samples are known to miss scale weights
  if (v.signal_index == 0 || v.signal_index == 3) return 1; //Must be removed in later, problem in T5qqqqHH, TChiWH, TChiWZ with LHEScaleWeight(empty)
  //if (scale_weight_norm.empty()) {
    //error("Weighting - Scale weight normalizations were not provided for this sample, rerun scripts/get_scaleweight_norm.py on unskimmed ntuple");
  //}
  double w_scale = 1;
  double w_scale_up = 1;   // Corresponds to 0.5 (More signal events)
  double w_scale_down = 1; // Corresponds to 2.0 (Less signal events)

/*
  if (numScale==1) {
    // Vary factorization scale
    // fix mu_r = 1.0, vary mu_f = 0,5, 2.0
    w_scale_up   = v.LHEScaleWeight[3] / v.LHEWeight_originalXWGTUP;
    w_scale_down = v.LHEScaleWeight[5] / v.LHEWeight_originalXWGTUP;
  } else if (numScale==2) {
    // Vary renormalization scale
    // fix mu_f = 1.0, vary mu_r = 0,5, 2.0
    w_scale_up   = v.LHEScaleWeight[1] / v.LHEWeight_originalXWGTUP;
    w_scale_down = v.LHEScaleWeight[7] / v.LHEWeight_originalXWGTUP;
  } else if (numScale==3) {
    // Vary both simulatneously
    // mu_r = mu_f = 0,5, 2.0
    w_scale_up   = v.LHEScaleWeight[0] / v.LHEWeight_originalXWGTUP;
    w_scale_down = v.LHEScaleWeight[8] / v.LHEWeight_originalXWGTUP;
  }
*/
  if (numScale==1) {
    // Vary factorization scale
    // fix mu_r = 1.0, vary mu_f = 0,5, 2.0
    w_scale_up   = v.LHEScaleWeight[3];
    w_scale_down = v.LHEScaleWeight[5];
  } else if (numScale==2) {
    // Vary renormalization scale
    // fix mu_f = 1.0, vary mu_r = 0,5, 2.0
    w_scale_up   = v.LHEScaleWeight[1];
    w_scale_down = v.LHEScaleWeight[7];
  } else if (numScale==3) {
    // Vary both simulatneously
    // mu_r = mu_f = 0,5, 2.0
    w_scale_up   = v.LHEScaleWeight[0];
    w_scale_down = v.LHEScaleWeight[8];
  }
  w_scale = get_syst_weight(w_scale, w_scale_up, w_scale_down, nSigmaScale);
  return w_scale;
}

//  double Weighting::calc_njet_weight(eventBuffer data, const double& nSigmaNJetWeight) {
//    // QCD Njet Reweighting
//    // First run this script to obtain the expo fit parameters
//    // root scripts/calc_njet_weight.C
//    // Up variation taken from Q region
//    // Down variation taken from G-1 region
//    double w_up = std::exp(-4.15259e-01 + 9.97141e-02 * nJet);
//    double w_dn = std::exp( 1.02951e+00 - 1.90498e-01 * nJet);
//    double w = get_syst_weight(1.0, w_up, w_dn, nSigmaNJetWeight);
//    return w;
//  }


double Weighting::calc_lostlep_weight(const double& nSigmaLostLep) {
  // Lost Lepton event weight
  // First run this script to obtain the lost lepton uncertainties
  // python scripts/calc_lostlepsyst.py
  // Use the averages combination of all leptons for W/top
  double w = 1;
  if (!v.isData) if (v.Electron.Veto.n+v.Muon.Veto.n+v.Tau.Veto.n==0) {
    // Final state leptons from W mother
    while (v.GenPart.LeptonFromW.Loop()) {
      double unc = 0;
      double abseta = std::abs(v.GenPart.LeptonFromW().eta);
      if      (abseta<0.5) unc = 0.125;
      else if (abseta<1.0) unc = 0.126;
      else if (abseta<1.5) unc = 0.129;
      else if (abseta<2.0) unc = 0.143;
      else if (abseta<2.5) unc = 0.175;
      w *= get_syst_weight(1.0, unc, nSigmaLostLep);
      //std::cout<<"Lost-lepton found: pt/eta/id = "<<v.GenPart.LeptonFromW().pt[i]<<" "
      //         <<v.GenPart.LeptonFromW().eta[i]<<" "<<v.GenPart.LeptonFromW().pdgId
      //         <<" E/M/T="<<v.Electron.Veto.n<<"/"<<v.Muon.Veto.n<<"/"<<v.Tau.Veto.n<<std::endl;
    }
  }
  return w;
}


double Weighting::calc_trigger_efficiency(const double& nSigmaTrigger) {
  // Trigger efficiencies from Janos
  double eff, err_up, err_down;
  double eff2, err2_up, err2_down;
  double binx = -1, v1 = v.AK4_Ht, v2 = v.MET_pt;
  for (size_t i=0, n=HT_2D_bins.size(); i+1<n; ++i) if (v1>=HT_2D_bins[i]&&v1<HT_2D_bins[i+1])
    for (size_t j=0, m=MET_2D_bins.size(); j+1<m; ++j) if (v2>=MET_2D_bins[j]&&v2<MET_2D_bins[j+1])
      binx = i*(m-1)+j;

  // For empty bins, we cannot use the value from the closest bin, 
  // because the plot is an unrolled 2D one
  // Calculate also the efficiency used for fake rate region
  if (v.Muon.Veto.n>=1) {
    geteff_AE_exactbin(trig_had_mu,       binx, eff,  err_up,  err_down);
    geteff_AE_exactbin(trig_had_mu_nor2,  binx, eff2, err2_up, err2_down);
  } else if (v.Electron.Veto.n>=1) {
    geteff_AE_exactbin(trig_had_ele,      binx, eff,  err_up,  err_down);
    geteff_AE_exactbin(trig_had_ele_nor2, binx, eff2, err2_up, err2_down);
  } else if (v.Photon.PreSelect.n>=1) {
    geteff_AE_exactbin(trig_had_pho,      binx, eff,  err_up,  err_down);
    //geteff_AE_exactbin(trig_had_pho_nor2, binx, eff2, err2_up, err2_down);
    geteff_AE(trig_had_pho_nor2, v.Photon.PreSelect(0).pt, eff2, err2_up, err2_down);
  } else {
    geteff_AE_exactbin(trig_had_ele,      binx, eff,  err_up,  err_down);
    geteff_AE_exactbin(trig_had_ele_nor2, binx, eff2, err2_up, err2_down);
  }

  double w            = get_syst_weight(eff,  eff+err_up,   eff-err_down,   nSigmaTrigger);
  triggereff_had_nor2 = get_syst_weight(eff2, eff2+err2_up, eff2-err2_down, nSigmaTrigger);

  // leptonic trigger efficiencies
  if (v.Electron.Select.n>0) {
    geteff_AE(trig_ele, v.Electron.Select(0).pt, eff, err_up, err_down);
    triggereff_lep = get_syst_weight(eff, eff+err_up, eff-err_down, nSigmaTrigger);
  } else if (v.Muon.Select.n>0) {
    geteff_AE(trig_mu, v.Muon.Select(0).pt, eff, err_up, err_down);
    triggereff_lep = get_syst_weight(eff, eff+err_up, eff-err_down, nSigmaTrigger);
  } else triggereff_lep = 0;
  
  // photonic trigger efficiencies
  if (v.Photon.PreSelect.n>0) {
      geteff_AE(v.Photon.PreSelect(0).isScEtaEE ? trig_pho_ee : trig_pho_eb, v.Photon.PreSelect(0).pt, eff, err_up, err_down);
      triggereff_pho = get_syst_weight(eff, eff+err_up, eff-err_down, nSigmaTrigger);
  } else triggereff_pho = 0;
  
  return w;
  //  } else {
  //    return 1;
  //  
  //    /*
  //    // 1D trigger efficiency method
  //    double eff, err_up, err_down;
  //    if (v.FatJet.JetAK8.n>0) {
  //    geteff_AE(eff_trigger, v.AK4_Ht, eff, err_up, err_down);
  //    double w = get_syst_weight(eff, eff+err_up, eff-err_down, nSigmaTrigger);
  //    return w;
  //    } else return 0;
  //    */
  //    // 2D trigger efficiency in bins of HT and Jet1pt
  //    // Check the presence of a lepton/photon and apply different weights
  //    TH2D *h      = eff_trigger_lep;
  //    TH2D *h_up   = eff_trigger_lep_up;
  //    TH2D *h_down = eff_trigger_lep_down;
  //    double MET = v.MET_pt;
  //  
  //    if (v.Photon.PreSelect.n>=1) {
  //      h      = eff_trigger_pho;
  //      h_up   = eff_trigger_pho_up;
  //      h_down = eff_trigger_pho_down;
  //    }
  //  
  //    if (v.FatJet.JetAK8.n>0) {
  //      double eff = 0, total = 0;
  //      geteff2D(h, MET, v.AK4_Ht, eff, total); // total was saved to histo error
  //      if (total>0) {
  //        double eff_up   = geteff2D(h_up,   MET, v.AK4_Ht);
  //        double eff_down = geteff2D(h_down, MET, v.AK4_Ht);
  //        double w = get_syst_weight(eff, eff_up, eff_down, nSigmaTrigger);
  //        return w;
  //      } else return 0;
  //    } else return 0;
  //  
  //    
  //    /*
  //    TH3D *h      = eff_3D_trigger_lep;
  //    TH3D *h_up   = eff_3D_trigger_lep_up;
  //    TH3D *h_down = eff_3D_trigger_lep_down;
  //    if (v.FatJet.JetAK8.n>0) {
  //      double eff = 0, total = 0;
  //      geteff3D(h, v.FatJet.JetAK8(0).msoftdrop, v.MET_pt, v.AK4_Ht, eff, total); // total was saved to histo error
  //      // For the time being only weight the measurable phase space
  //      // Rest is 0 --> Could weight with the TGraphAsymmErrors::Efficiency value (0.5+-0.5)
  //      if (total>0) {
  //        double eff_up   = geteff3D(h_up,   v.FatJet.JetAK8(0).msoftdrop, v.MET_pt, v.AK4_Ht);
  //        double eff_down = geteff3D(h_down, v.FatJet.JetAK8(0).msoftdrop, v.MET_pt, v.AK4_Ht);
  //        double w = get_syst_weight(eff, eff_up, eff_down, nSigmaTrigger);
  //        return w;
  //      } else return 0;
  //    } else return 0;
  //    */
  //  }
}

#endif // End header guard


