#ifndef ANALYSIS_H
#define ANALYSIS_H

// Private headers
#include "tnm.h"
#include "Variables.h"
#include "Weighting.h"
#include "EventSelections.h"
#include "ScaleFactors.h"
#include "PlottingBase.h"

// 3rd party headers
#include "TH3.h"
#include "TStopwatch.h"
#include "TString.h"

// common libraries
#include <iostream>
#include <vector>

// _____________________________________________________________
//        Analysis: Methods common in all analysis

class Analysis
{
public:
  Analysis(Variables& var) :
    weighting(Weighting(var)),
    event_selections(EventSelections(var)),
    scale_factors(ScaleFactors(var)),
    plotting(Plotting(var))
    //v(var)
  {
    sw_1_  = new TStopwatch;
    sw_1k_  = new TStopwatch;
    sw_10k_ = new TStopwatch;
    sw_job_ = new TStopwatch;

    syst = {
      "lumi", "toppt", "isr", "pileup",
      "alphas", "facscale", "renscale", "facrenscale", "lostlep",
      "trigger", "jes", "jer", "met", "ak8scale",
      "elereco", "eleid", "eleiso", "elefastsim",
      "muontrk", "muonidiso", "muonfastsim",
      "btag", "btagfastsim",
      "wtag", "wtagfastsim", "wmistag", "wmistagfastsim", "wmasstag","wantitag",
      "toptag", "toptagfastsim", "topmistag", "topmistagfastsim",
      "top0bmasstag","topmasstag","topantitag"
    };
  }
  ~Analysis() {
    delete sw_1_;
    delete sw_1k_;
    delete sw_10k_;
    delete sw_job_;
  }

  Weighting weighting;
  
  EventSelections event_selections;
  
  ScaleFactors scale_factors;
  
  Plotting plotting;

  void job_monitoring(const int&, const int&, const int&, const std::string&, const float);

  void init_histos(const bool&);

  void fill_histos(const bool&, const bool&, const unsigned int&, const double&);

  std::vector<std::string> syst;

  void initialize1(const bool&, const unsigned int&, const unsigned int&);

  void initialize2(const bool&, const unsigned int&, const unsigned int&);

private:

  TStopwatch *sw_1_, *sw_1k_, *sw_10k_, *sw_job_;
  std::map<std::string, int> bad_files;

  TH1D* h_read_speed_1k;
  TH1D* h_read_speed_10k;
  TH1D* h_read_speed_job;
  TH2D* h_read_speed_vs_nevt_10k;
  TH2D* h_read_speed_vs_nevt_job;
  TH1D* h_runtime_job;
  TH2D* h_runtime_vs_nevt_job;

  //_______________________________________________________
  //             List of systematics Histograms

  /*
  std::vector<TH1D*> vh_MRR2_data;
  std::vector<TH1D*> vh_MRR2_data_nj45;
  std::vector<TH1D*> vh_MRR2_data_nj6;
  std::vector<std::vector<TH1D*> > vvh_MRR2_bkg;
  std::vector<std::vector<TH1D*> > vvh_MRR2_bkg_nj45;
  std::vector<std::vector<TH1D*> > vvh_MRR2_bkg_nj6;
  std::map<uint32_t, std::vector<TH1D*> > m_vh_MRR2_sig;
  std::map<uint32_t, std::vector<TH1D*> > m_vh_MRR2_sig_nj45;
  std::map<uint32_t, std::vector<TH1D*> > m_vh_MRR2_sig_nj6;
  
  // Histos for the Z(nunu) estimate
  TH2D* h_MR_R2_G_EB; // For counts in data
  TH2D* h_MR_R2_G_EE;
  TH2D* h_MR_R2_G_EB_nj45;
  TH2D* h_MR_R2_G_EB_nj6;
  TH2D* h_MR_R2_G_EE_nj45;
  TH2D* h_MR_R2_G_EE_nj6;
  TH3D* h_CHIsoTemplate_Fake_g_EB; // Fake photon templates (data)
  TH3D* h_CHIsoTemplate_Fake_g_EE;
  TH3D* h_CHIsoTemplate_Fake_g_EB_MC; // Fake photon templates (mc)
  TH3D* h_CHIsoTemplate_Fake_g_EE_MC;
  TH3D* h_CHIsoTemplate_Prompt_g_EB; // Prompt photon template (GJets)
  TH3D* h_CHIsoTemplate_Prompt_g_EE;
  TH3D* h_MR_R2_CHIso_GNoIso_EB; // For purity in data
  TH3D* h_MR_R2_CHIso_GNoIso_EE;
  TH3D* h_MR_R2_CHIso_GNoIso_EB_nj45;
  TH3D* h_MR_R2_CHIso_GNoIso_EB_nj6;
  TH3D* h_MR_R2_CHIso_GNoIso_EE_nj45;
  TH3D* h_MR_R2_CHIso_GNoIso_EE_nj6;
  TH3D* h_MR_R2_CHIso_gNoIso_EB; // For purity in data (G-1)
  TH3D* h_MR_R2_CHIso_gNoIso_EE;
  TH3D* h_MR_R2_CHIso_gNoIso_EB_nj45;
  TH3D* h_MR_R2_CHIso_gNoIso_EB_nj6;
  TH3D* h_MR_R2_CHIso_gNoIso_EE_nj45;
  TH3D* h_MR_R2_CHIso_gNoIso_EE_nj6;
  TH3D* h_MR_R2_IsPrompt_G_EB; // MC truth for photon purity
  TH3D* h_MR_R2_IsPrompt_G_EE;
  TH3D* h_MR_R2_IsDirect_G_EB; // MC truth for direct fraction
  TH3D* h_MR_R2_IsDirect_G_EE;
  TH2D* h_MR_R2_S; // Counts for Transfer factor: S(mc)/G(mc)
  TH2D* h_MR_R2_S_nj45;
  TH2D* h_MR_R2_S_nj6;
  TH2D* h_MR_R2_G_DirectPrompt;
  TH2D* h_MR_R2_G_DirectPrompt_nj45;
  TH2D* h_MR_R2_G_DirectPrompt_nj6;
  TH2D* h_MR_R2_Z; // Double ratio: [G(data)/G(mc)] / [Z(ll,data)/Z(ll,mc)]
  TH2D* h_MR_R2_Z_nj45;
  TH2D* h_MR_R2_Z_nj6;
  TH2D* h_MR_R2_G;
  TH2D* h_MR_R2_G_nj45;
  TH2D* h_MR_R2_G_nj6;
  // 1 Lepton estimate
  TH2D* h_MR_R2_L;
  TH2D* h_MR_R2_L_nj45;
  TH2D* h_MR_R2_L_nj6;
  // Q' closure
  TH2D* h_MR_R2_q;
  TH2D* h_MR_R2_q_nj45;
  TH2D* h_MR_R2_q_nj6;

  int calc_mrr2_bin_(eventBuffer&, const char&);
  */
};




//_______________________________________________________
//              Define Histograms here
void
Analysis::init_histos(const bool& varySystematics)
{
  // job_monitoring histos
  h_read_speed_1k              = new TH1D("read_speed_1k",          ";Read speed (Events/s);Measurement/1k Event",  1000,0,10000);
  h_read_speed_10k             = new TH1D("read_speed_10k",         ";Read speed (Events/s);Measurement/10k Event", 1000,0,10000);
  h_read_speed_job             = new TH1D("read_speed_job",         ";Read speed (Events/s);Measurement/Job",       1000,0,10000);
  h_read_speed_vs_nevt_10k     = new TH2D("read_speed_vs_nevt_10k", ";Entry;Read speed (Events/s)/10k Event",       100,0,10000000, 200,0,10000);
  h_read_speed_vs_nevt_job     = new TH2D("read_speed_vs_nevt_job", ";Total Entries;Read speed (Events/s)/Job",     100,0,10000000, 200,0,10000);
  h_runtime_job                = new TH1D("runtime_job",            ";Total job run-time (min)",                    600,0,600);
  h_runtime_vs_nevt_job        = new TH2D("runtime_vs_nevt_job",    ";Total Entries;Total job run-time (min)",      100,0,10000000, 600,0,600);

  /*
  std::vector<std::string> regions = {"S", "s", "T", "W", "Q", "q", "Z", "L", "G", "G_DirectPrompt", "S_LooseWP"};

  if (varySystematics) {
    for (size_t i=0; i<regions.size(); ++i) {
      if (isData_) {
        // Data
        vh_MRR2_data     .push_back(new TH1D((std::string("MRR2_")+regions[i]+"_data").c_str(),      ";MR/R^{2} bins (unrolled);Counts", 25,0,25));
        vh_MRR2_data_nj45.push_back(new TH1D((std::string("MRR2_")+regions[i]+"_data_nj45").c_str(), ";MR/R^{2} bins (unrolled);Counts", 25,0,25));
        vh_MRR2_data_nj6 .push_back(new TH1D((std::string("MRR2_")+regions[i]+"_data_nj6").c_str(),  ";MR/R^{2} bins (unrolled);Counts", 25,0,25));
      } else if (!isSignal_) {
        // Background
        vvh_MRR2_bkg     .push_back(std::vector<TH1D*>());
        vvh_MRR2_bkg_nj45.push_back(std::vector<TH1D*>());
        vvh_MRR2_bkg_nj6 .push_back(std::vector<TH1D*>());
        vvh_MRR2_bkg[i]     .push_back(new TH1D((std::string("MRR2_")+regions[i]+"_bkg").c_str(),      ";MR/R^{2} bins (unrolled);Counts", 25,0,25));
        vvh_MRR2_bkg_nj45[i].push_back(new TH1D((std::string("MRR2_")+regions[i]+"_bkg_nj45").c_str(), ";MR/R^{2} bins (unrolled);Counts", 25,0,25));
        vvh_MRR2_bkg_nj6[i] .push_back(new TH1D((std::string("MRR2_")+regions[i]+"_bkg_nj6").c_str(),  ";MR/R^{2} bins (unrolled);Counts", 25,0,25));
        for (size_t j=0; j<syst.size(); ++j) {
          std::stringstream ss;
          ss<<"MRR2_"<<regions[i]<<"_bkg_"<<syst[j];
          vvh_MRR2_bkg[i].push_back(new TH1D((ss.str()+"Up").c_str(),   ";MR/R^{2} bins (unrolled);Counts", 25,0,25));
          vvh_MRR2_bkg[i].push_back(new TH1D((ss.str()+"Down").c_str(), ";MR/R^{2} bins (unrolled);Counts", 25,0,25));
          std::stringstream ss45;
          ss45<<"MRR2_"<<regions[i]<<"_bkg_nj45_"<<syst[j];
          vvh_MRR2_bkg_nj45[i].push_back(new TH1D((ss45.str()+"Up").c_str(),   ";MR/R^{2} bins (unrolled);Counts", 25,0,25));
          vvh_MRR2_bkg_nj45[i].push_back(new TH1D((ss45.str()+"Down").c_str(), ";MR/R^{2} bins (unrolled);Counts", 25,0,25));
          std::stringstream ss6;
          ss6<<"MRR2_"<<regions[i]<<"_bkg_nj6_"<<syst[j];
          vvh_MRR2_bkg_nj6[i].push_back(new TH1D((ss6.str()+"Up").c_str(),   ";MR/R^{2} bins (unrolled);Counts", 25,0,25));
          vvh_MRR2_bkg_nj6[i].push_back(new TH1D((ss6.str()+"Down").c_str(), ";MR/R^{2} bins (unrolled);Counts", 25,0,25));
        }
      }
    }
  }
  // Signals --> Declare them later after the signal weight calculation
  // in calc_signal_weightnorm()

  double mrbins[6]  = { 800, 1000, 1200, 1600, 2000, 4000 };
  double r2bins[6]  = { 0.08, 0.12, 0.16, 0.24, 0.4, 1.5 };
  double isdirectbins[3] = {-0.5,0.5,1.5};
  double chisobins[21] = { 0 };
  for (int i=0; i<21; ++i) chisobins[i] = float(i)/2.;

  // Histos for the Z(nunu) estimate
  h_MR_R2_G_EB                 = new TH2D("MR_R2_G_EB",                 "G region, EB;M_{R} (GeV);R^{2}",       5,mrbins, 5,r2bins);
  h_MR_R2_G_EE                 = new TH2D("MR_R2_G_EE",                 "G region, EE;M_{R} (GeV);R^{2}",       5,mrbins, 5,r2bins);
  h_MR_R2_G_EB_nj45            = new TH2D("MR_R2_G_EB_nj45",            "G region, EB, nj45;M_{R} (GeV);R^{2}", 5,mrbins, 5,r2bins);
  h_MR_R2_G_EB_nj6             = new TH2D("MR_R2_G_EB_nj6",             "G region, EB, nj6-;M_{R} (GeV);R^{2}", 5,mrbins, 5,r2bins);
  h_MR_R2_G_EE_nj45            = new TH2D("MR_R2_G_EE_nj45 ",           "G region, EE, nj45;M_{R} (GeV);R^{2}", 5,mrbins, 5,r2bins);
  h_MR_R2_G_EE_nj6             = new TH2D("MR_R2_G_EE_nj6",             "G region, EE, nj6-;M_{R} (GeV);R^{2}", 5,mrbins, 5,r2bins);
  h_CHIsoTemplate_Fake_g_EB    = new TH3D("CHIsoTemplate_Fake_g_EB",    "G-1 region, EB;M_{R} (GeV);R^{2};Photon Charged Isolation (GeV)", 5,mrbins, 5,r2bins, 20,chisobins);
  h_CHIsoTemplate_Fake_g_EE    = new TH3D("CHIsoTemplate_Fake_g_EE",    "G-1 region, EE;M_{R} (GeV);R^{2};Photon Charged Isolation (GeV)", 5,mrbins, 5,r2bins, 20,chisobins);
  h_CHIsoTemplate_Fake_g_EB_MC = new TH3D("CHIsoTemplate_Fake_g_EB_MC", "G-1 region, EB (MC);M_{R} (GeV);R^{2};Photon Charged Isolation (GeV)", 5,mrbins, 5,r2bins, 20,chisobins);
  h_CHIsoTemplate_Fake_g_EE_MC = new TH3D("CHIsoTemplate_Fake_g_EE_MC", "G-1 region, EE (MC);M_{R} (GeV);R^{2};Photon Charged Isolation (GeV)", 5,mrbins, 5,r2bins, 20,chisobins);
  h_CHIsoTemplate_Prompt_g_EB  = new TH3D("CHIsoTemplate_Prompt_g_EB",  "G-1 region, EB;M_{R} (GeV);R^{2};Photon Charged Isolation (GeV)", 5,mrbins, 5,r2bins, 20,chisobins);
  h_CHIsoTemplate_Prompt_g_EE  = new TH3D("CHIsoTemplate_Prompt_g_EE",  "G-1 region, EE;M_{R} (GeV);R^{2};Photon Charged Isolation (GeV)", 5,mrbins, 5,r2bins, 20,chisobins);
  h_MR_R2_CHIso_GNoIso_EB      = new TH3D("MR_R2_CHIso_GNoIso_EB",      "G region (w/o CH iso.), EB;M_{R} (GeV);R^{2};Photon Charged Isolation (GeV)",      5,mrbins, 5,r2bins, 20,chisobins);
  h_MR_R2_CHIso_GNoIso_EE      = new TH3D("MR_R2_CHIso_GNoIso_EE",      "G region (w/o CH iso.), EE;M_{R} (GeV);R^{2};Photon Charged Isolation (GeV)",      5,mrbins, 5,r2bins, 20,chisobins);
  h_MR_R2_CHIso_GNoIso_EB_nj45 = new TH3D("MR_R2_CHIso_GNoIso_EB_nj45", "G region (w/o CH iso.), EB nj45;M_{R} (GeV);R^{2};Photon Charged Isolation (GeV)", 5,mrbins, 5,r2bins, 20,chisobins);
  h_MR_R2_CHIso_GNoIso_EB_nj6  = new TH3D("MR_R2_CHIso_GNoIso_EB_nj6",  "G region (w/o CH iso.), EB nj6-;M_{R} (GeV);R^{2};Photon Charged Isolation (GeV)", 5,mrbins, 5,r2bins, 20,chisobins);
  h_MR_R2_CHIso_GNoIso_EE_nj45 = new TH3D("MR_R2_CHIso_GNoIso_EE_nj45 ","G region (w/o CH iso.), EE nj45;M_{R} (GeV);R^{2};Photon Charged Isolation (GeV)", 5,mrbins, 5,r2bins, 20,chisobins);
  h_MR_R2_CHIso_GNoIso_EE_nj6  = new TH3D("MR_R2_CHIso_GNoIso_EE_nj6",  "G region (w/o CH iso.), EE nj6-;M_{R} (GeV);R^{2};Photon Charged Isolation (GeV)", 5,mrbins, 5,r2bins, 20,chisobins);
  h_MR_R2_CHIso_gNoIso_EB      = new TH3D("MR_R2_CHIso_gNoIso_EB",      "G-1 region (w/o CH iso.), EB;M_{R} (GeV);R^{2};Photon Charged Isolation (GeV)",      5,mrbins, 5,r2bins, 20,chisobins);
  h_MR_R2_CHIso_gNoIso_EE      = new TH3D("MR_R2_CHIso_gNoIso_EE",      "G-1 region (w/o CH iso.), EE;M_{R} (GeV);R^{2};Photon Charged Isolation (GeV)",      5,mrbins, 5,r2bins, 20,chisobins);
  h_MR_R2_CHIso_gNoIso_EB_nj45 = new TH3D("MR_R2_CHIso_gNoIso_EB_nj45", "G-1 region (w/o CH iso.), EB nj45;M_{R} (GeV);R^{2};Photon Charged Isolation (GeV)", 5,mrbins, 5,r2bins, 20,chisobins);
  h_MR_R2_CHIso_gNoIso_EB_nj6  = new TH3D("MR_R2_CHIso_gNoIso_EB_nj6",  "G-1 region (w/o CH iso.), EB nj6-;M_{R} (GeV);R^{2};Photon Charged Isolation (GeV)", 5,mrbins, 5,r2bins, 20,chisobins);
  h_MR_R2_CHIso_gNoIso_EE_nj45 = new TH3D("MR_R2_CHIso_gNoIso_EE_nj45 ","G-1 region (w/o CH iso.), EE nj45;M_{R} (GeV);R^{2};Photon Charged Isolation (GeV)", 5,mrbins, 5,r2bins, 20,chisobins);
  h_MR_R2_CHIso_gNoIso_EE_nj6  = new TH3D("MR_R2_CHIso_gNoIso_EE_nj6",  "G-1 region (w/o CH iso.), EE nj6-;M_{R} (GeV);R^{2};Photon Charged Isolation (GeV)", 5,mrbins, 5,r2bins, 20,chisobins);
  h_MR_R2_IsPrompt_G_EB        = new TH3D("MR_R2_IsPrompt_G_EB",        "G region, EB;M_{R} (GeV);R^{2}", 5,mrbins, 5,r2bins, 2,isdirectbins);
  h_MR_R2_IsPrompt_G_EE        = new TH3D("MR_R2_IsPrompt_G_EE",        "G region, EE;M_{R} (GeV);R^{2}", 5,mrbins, 5,r2bins, 2,isdirectbins);
  h_MR_R2_IsDirect_G_EB        = new TH3D("MR_R2_IsDirect_G_EB",        "G region, EB;M_{R} (GeV);R^{2}", 5,mrbins, 5,r2bins, 2,isdirectbins);
  h_MR_R2_IsDirect_G_EE        = new TH3D("MR_R2_IsDirect_G_EE",        "G region, EE;M_{R} (GeV);R^{2}", 5,mrbins, 5,r2bins, 2,isdirectbins);
  h_MR_R2_S                    = new TH2D("MR_R2_S",                    "S region;M_{R} (GeV);R^{2}",       5,mrbins, 5,r2bins);
  h_MR_R2_S_nj45               = new TH2D("MR_R2_S_nj45",               "S region, nj45;M_{R} (GeV);R^{2}", 5,mrbins, 5,r2bins);
  h_MR_R2_S_nj6                = new TH2D("MR_R2_S_nj6",                "S region, nj6-;M_{R} (GeV);R^{2}", 5,mrbins, 5,r2bins);
  h_MR_R2_G_DirectPrompt       = new TH2D("MR_R2_G_DirectPrompt",       "G region (direct,prompt #gamma);M_{R} (GeV);R^{2}",       5,mrbins, 5,r2bins);
  h_MR_R2_G_DirectPrompt_nj45  = new TH2D("MR_R2_G_DirectPrompt_nj45",  "G region (direct,prompt #gamma), nj45;M_{R} (GeV);R^{2}", 5,mrbins, 5,r2bins);
  h_MR_R2_G_DirectPrompt_nj6   = new TH2D("MR_R2_G_DirectPrompt_nj6",   "G region (direct,prompt #gamma), nj6-;M_{R} (GeV);R^{2}", 5,mrbins, 5,r2bins);
  h_MR_R2_Z                    = new TH2D("MR_R2_Z",                    "Z region;M_{R} (GeV);R^{2}",       5,mrbins, 5,r2bins);
  h_MR_R2_Z_nj45               = new TH2D("MR_R2_Z_nj45",               "Z region, nj45;M_{R} (GeV);R^{2}", 5,mrbins, 5,r2bins);
  h_MR_R2_Z_nj6                = new TH2D("MR_R2_Z_nj6",                "Z region, nj6-;M_{R} (GeV);R^{2}", 5,mrbins, 5,r2bins);
  h_MR_R2_G                    = new TH2D("MR_R2_G",                    "G region;M_{R} (GeV);R^{2}",       5,mrbins, 5,r2bins);
  h_MR_R2_G_nj45               = new TH2D("MR_R2_G_nj45",               "G region, nj45;M_{R} (GeV);R^{2}", 5,mrbins, 5,r2bins);
  h_MR_R2_G_nj6                = new TH2D("MR_R2_G_nj6",                "G region, nj6-;M_{R} (GeV);R^{2}", 5,mrbins, 5,r2bins);
  h_MR_R2_L                    = new TH2D("MR_R2_L",                    "L region;M_{R} (GeV);R^{2}",       5,mrbins, 5,r2bins);
  h_MR_R2_L_nj45               = new TH2D("MR_R2_L_nj45",               "L region, nj45;M_{R} (GeV);R^{2}", 5,mrbins, 5,r2bins);
  h_MR_R2_L_nj6                = new TH2D("MR_R2_L_nj6",                "L region, nj6-;M_{R} (GeV);R^{2}", 5,mrbins, 5,r2bins);
  h_MR_R2_q                    = new TH2D("MR_R2_q",                    "q region;M_{R} (GeV);R^{2}",       5,mrbins, 5,r2bins);
  h_MR_R2_q_nj45               = new TH2D("MR_R2_q_nj45",               "q region, nj45;M_{R} (GeV);R^{2}", 5,mrbins, 5,r2bins);
  h_MR_R2_q_nj6                = new TH2D("MR_R2_q_nj6",                "q region, nj6-;M_{R} (GeV);R^{2}", 5,mrbins, 5,r2bins);
  */
}

//_______________________________________________________
//               Fill Histograms here
void
Analysis::fill_histos(const bool& varySystematics, const bool& runOnSkim, const unsigned int& syst_index, const double& weight)
{
  /*  
  if (runOnSkim) {
    if (syst_index == 0) {
      // Fill Histos for the Z(nunu) estimate
      if (isData_) {
        // All photon counts in G (data)
        if (apply_all_cuts('G')) {
          bool EB = d.Photon[0].isScEtaEB;
          if (EB) h_MR_R2_G_EB->Fill(MR_pho, R2_pho);
          else    h_MR_R2_G_EE->Fill(MR_pho, R2_pho);
          if (nJetNoPho>=4) {
            if (nJetNoPho<6) {
              if (EB) h_MR_R2_G_EB_nj45->Fill(MR_pho, R2_pho);
              else    h_MR_R2_G_EE_nj45->Fill(MR_pho, R2_pho);
            } else {
              if (EB) h_MR_R2_G_EB_nj6->Fill(MR_pho, R2_pho);
              else    h_MR_R2_G_EE_nj6->Fill(MR_pho, R2_pho);
            }
          }
        }
        // Fake photon templates
        if (apply_all_cuts_except('G',"1Pho")) {
          if (nPhotonFake==1) {
            bool EB = d.Photon[iPhotonFake[0]].isScEtaEB;
            if (EB) h_CHIsoTemplate_Fake_g_EB->Fill(MR_pho, R2_pho, d.Photon[iPhotonFake[0]].pfRelIso03_chg, sf_weight['G']);
            else    h_CHIsoTemplate_Fake_g_EE->Fill(MR_pho, R2_pho, d.Photon[iPhotonFake[0]].pfRelIso03_chg, sf_weight['G']);
          }
        }
      } else if (isBackground_) {
        // Prompt photon templates
        if (apply_all_cuts_except('G',"1Pho")) {
          if (nPhotonPreSelect==1) {
            if (d.Photon[iPhotonPreSelect[0]].sieie < (d.Photon[iPhotonPreSelect[0]].isScEtaEB ? 0.01015 : 0.0272)) {
              bool EB = d.Photon[iPhotonPreSelect[0]].isScEtaEB;
              if (nGenPhotonPromptDirect>=1||nGenPhotonPromptFragmentation>=1) {
                if (EB) h_CHIsoTemplate_Prompt_g_EB->Fill(MR_pho, R2_pho, d.Photon[iPhotonPreSelect[0]].pfRelIso03_chg, sf_weight['G']);
                else    h_CHIsoTemplate_Prompt_g_EE->Fill(MR_pho, R2_pho, d.Photon[iPhotonPreSelect[0]].pfRelIso03_chg, sf_weight['G']);
              } else {
                if (EB) h_CHIsoTemplate_Fake_g_EB_MC->Fill(MR_pho, R2_pho, d.Photon[iPhotonPreSelect[0]].pfRelIso03_chg, sf_weight['G']);
                else    h_CHIsoTemplate_Fake_g_EE_MC->Fill(MR_pho, R2_pho, d.Photon[iPhotonPreSelect[0]].pfRelIso03_chg, sf_weight['G']);
              }
            }
          }
        }
      }
      // Charged Hadron Isolation distributions for Purity measurement
      if (isData_) {
        if (apply_all_cuts_except('G',"1Pho")) {
          if (nPhotonPreSelect==1) {
            if (d.Photon[iPhotonPreSelect[0]].sieie < (d.Photon[iPhotonPreSelect[0]].isScEtaEB ? 0.01015 : 0.0272)) {
              // Select 1 photon with CHIso N-1 cuts
              bool EB = d.Photon[iPhotonPreSelect[0]].isScEtaEB;
              //if (EB) h_MR_R2_CHIso_GNoIso_EB->Fill(MR_pho, R2_pho, pfRelIso03_chgEACorr[iPhotonPreSelect[0]]);
              //else    h_MR_R2_CHIso_GNoIso_EE->Fill(MR_pho, R2_pho, pfRelIso03_chgEACorr[iPhotonPreSelect[0]]);
              if (EB) h_MR_R2_CHIso_GNoIso_EB->Fill(MR_pho, R2_pho, d.Photon[iPhotonPreSelect[0]].pfRelIso03_chg);
              else    h_MR_R2_CHIso_GNoIso_EE->Fill(MR_pho, R2_pho, d.Photon[iPhotonPreSelect[0]].pfRelIso03_chg);
              if (nJetNoPho>=4) {
                if (nJetNoPho<6) {
                  //if (EB) h_MR_R2_CHIso_GNoIso_EB_nj45->Fill(MR_pho, R2_pho, pfRelIso03_chgEACorr[iPhotonPreSelect[0]]);
                  //else    h_MR_R2_CHIso_GNoIso_EE_nj45->Fill(MR_pho, R2_pho, pfRelIso03_chgEACorr[iPhotonPreSelect[0]]);
                  if (EB) h_MR_R2_CHIso_GNoIso_EB_nj45->Fill(MR_pho, R2_pho, d.Photon[iPhotonPreSelect[0]].pfRelIso03_chg);
                  else    h_MR_R2_CHIso_GNoIso_EE_nj45->Fill(MR_pho, R2_pho, d.Photon[iPhotonPreSelect[0]].pfRelIso03_chg);
                } else {
                  //if (EB) h_MR_R2_CHIso_GNoIso_EB_nj6->Fill(MR_pho, R2_pho, pfRelIso03_chgEACorr[iPhotonPreSelect[0]]);
                  //else    h_MR_R2_CHIso_GNoIso_EE_nj6->Fill(MR_pho, R2_pho, pfRelIso03_chgEACorr[iPhotonPreSelect[0]]);
                  if (EB) h_MR_R2_CHIso_GNoIso_EB_nj6->Fill(MR_pho, R2_pho, d.Photon[iPhotonPreSelect[0]].pfRelIso03_chg);
                  else    h_MR_R2_CHIso_GNoIso_EE_nj6->Fill(MR_pho, R2_pho, d.Photon[iPhotonPreSelect[0]].pfRelIso03_chg);
                }
              }
            }
          }
        }
        // G-1 region
        if (apply_all_cuts_except('G',"1Pho")) {
          if (nPhotonPreSelect==1) {
            if (d.Photon[iPhotonPreSelect[0]].sieie < (d.Photon[iPhotonPreSelect[0]].isScEtaEB ? 0.01015 : 0.0272)) {
              // Select 1 photon with CHIso N-1 cuts
              bool EB = d.Photon[iPhotonPreSelect[0]].isScEtaEB;
              //if (EB) h_MR_R2_CHIso_gNoIso_EB->Fill(MR_pho, R2_pho, ChargedHadronIsoEACorr[iPhotonPreSelect[0]]);
              //else    h_MR_R2_CHIso_gNoIso_EE->Fill(MR_pho, R2_pho, ChargedHadronIsoEACorr[iPhotonPreSelect[0]]);
              if (EB) h_MR_R2_CHIso_gNoIso_EB->Fill(MR_pho, R2_pho, d.Photon[iPhotonPreSelect[0]].pfRelIso03_chg);
              else    h_MR_R2_CHIso_gNoIso_EE->Fill(MR_pho, R2_pho, d.Photon[iPhotonPreSelect[0]].pfRelIso03_chg);
              if (nJetNoPho>=4) {
                if (nJetNoPho<6) {
                  //if (EB) h_MR_R2_CHIso_gNoIso_EB_nj45->Fill(MR_pho, R2_pho, pfRelIso03_chgEACorr[iPhotonPreSelect[0]]);
                  //else    h_MR_R2_CHIso_gNoIso_EE_nj45->Fill(MR_pho, R2_pho, pfRelIso03_chgEACorr[iPhotonPreSelect[0]]);
                  if (EB) h_MR_R2_CHIso_gNoIso_EB_nj45->Fill(MR_pho, R2_pho, d.Photon[iPhotonPreSelect[0]].pfRelIso03_chg);
                  else    h_MR_R2_CHIso_gNoIso_EE_nj45->Fill(MR_pho, R2_pho, d.Photon[iPhotonPreSelect[0]].pfRelIso03_chg);
                } else {
                  //if (EB) h_MR_R2_CHIso_gNoIso_EB_nj6->Fill(MR_pho, R2_pho, pfRelIso03_chgEACorr[iPhotonPreSelect[0]]);
                  //else    h_MR_R2_CHIso_gNoIso_EE_nj6->Fill(MR_pho, R2_pho, pfRelIso03_chgEACorr[iPhotonPreSelect[0]]);
                  if (EB) h_MR_R2_CHIso_gNoIso_EB_nj6->Fill(MR_pho, R2_pho, d.Photon[iPhotonPreSelect[0]].pfRelIso03_chg);
                  else    h_MR_R2_CHIso_gNoIso_EE_nj6->Fill(MR_pho, R2_pho, d.Photon[iPhotonPreSelect[0]].pfRelIso03_chg);
                }
              }
            }
          }
        }
      } else if (isBackground_) {
        // Direct photon ratio from MC
        if (apply_all_cuts('G')) {
          //std::cout<<"Pass G: "<<MR_pho<<" "<<R2_pho<<" "<<d.evt.RunNumber<<" "<<d.evt.LumiBlock<<" "<<d.evt.EventNumber<<std::endl;
          bool EB = d.Photon[iPhotonSelect[0]].isScEtaEB;
          bool isPrompt = nGenPhotonPromptDirect>=1||nGenPhotonPromptFragmentation>=1;
          bool isPromptDirect = nGenPhotonPromptDirect>=1;
          // Prompt photon fraction
          if (EB) h_MR_R2_IsPrompt_G_EB->Fill(MR_pho, R2_pho, isPrompt, sf_weight['G']);
          else    h_MR_R2_IsPrompt_G_EE->Fill(MR_pho, R2_pho, isPrompt, sf_weight['G']);
          // Direct photon fraction of prompt photons
          if (isPrompt) {
            if (EB) h_MR_R2_IsDirect_G_EB->Fill(MR_pho, R2_pho, isPromptDirect, sf_weight['G']);
            else    h_MR_R2_IsDirect_G_EE->Fill(MR_pho, R2_pho, isPromptDirect, sf_weight['G']);
          }
          // Prompt direct photons in G control region
          if (isPromptDirect==1) {
            h_MR_R2_G_DirectPrompt->Fill(MR_pho, R2_pho, sf_weight['G']);
            if (nJetNoPho>=4) {
              if (nJetNoPho<6) h_MR_R2_G_DirectPrompt_nj45->Fill(MR_pho, R2_pho, sf_weight['G']);
              else             h_MR_R2_G_DirectPrompt_nj6 ->Fill(MR_pho, R2_pho, sf_weight['G']);
            }
          }
        }
      }
      // Counts for transfer factors/ratios
      if (apply_all_cuts('S')) {
        h_MR_R2_S->Fill(MR, R2, sf_weight['S']);
        if (nJet>=4) {
          if (nJet<6) h_MR_R2_S_nj45->Fill(MR, R2, sf_weight['S']);
          else        h_MR_R2_S_nj6 ->Fill(MR, R2, sf_weight['S']);
        }
      }
      // photon/1-lepton/2-lepton estimates
      if (apply_all_cuts('Z')) {
        h_MR_R2_Z->Fill(MR, R2_ll, sf_weight['Z']);
        if (nJet>=4) {
          if (nJet<6) h_MR_R2_Z_nj45->Fill(MR, R2_ll, sf_weight['Z']);
          else        h_MR_R2_Z_nj6 ->Fill(MR, R2_ll, sf_weight['Z']);
        }
      }
      if (apply_all_cuts('L')) {
        h_MR_R2_L->Fill(MR, R2_1l, sf_weight['L']);
        if (nJet>=4) {
          if (nJet<6) h_MR_R2_L_nj45->Fill(MR, R2_1l, sf_weight['L']);
          else        h_MR_R2_L_nj6 ->Fill(MR, R2_1l, sf_weight['L']);
        }
      }
      if (apply_all_cuts('G')) {
        h_MR_R2_G->Fill(MR_pho, R2_pho, sf_weight['G']);
        if (nJetNoPho>=4) {
          if (nJetNoPho<6) h_MR_R2_G_nj45->Fill(MR_pho, R2_pho, sf_weight['G']);
          else             h_MR_R2_G_nj6 ->Fill(MR_pho, R2_pho, sf_weight['G']);
        }
      }
      // closure test in Q'
      if (apply_all_cuts('q')) {
        h_MR_R2_q->Fill(MR, R2, sf_weight['q']);
        if (nJet>=4) {
          if (nJet<6) h_MR_R2_q_nj45->Fill(MR, R2, sf_weight['q']);
          else        h_MR_R2_q_nj6 ->Fill(MR, R2, sf_weight['q']);
        }
      }


    } // end syst_index == 0

    if (varySystematics) {
      // Fill plots for systematics
      const std::vector<char> regions = {'S', 's', 'T', 'W', 'Q', 'q', 'Z', 'L', 'G'};
      if (isData_) {
        if (TString(sample).Contains("JetHT")) {
          for (size_t i=0; i<regions.size(); ++i) {
            int MRR2_bin = calc_mrr2_bin_(d, regions[i]);
            if (this->apply_all_cuts(regions[i])) {
              vh_MRR2_data[i]->Fill(MRR2_bin);
              if (nJet>=4) {
                if (nJet<6) vh_MRR2_data_nj45[i]->Fill(MRR2_bin);
                else        vh_MRR2_data_nj6[i] ->Fill(MRR2_bin);
              }
            }
          }
          // Save also vertex count (for signal systematics)
          if (nJetAK8>=1 && nJet>=3 && MR>=800 && R2>=0.08) {
            if (d.HLT_AK8PFJet450==1 || d.HLT_PFHT1050==1) {
              h_nvtx->Fill(d.PV_npvsGood);
              h_npvLowHigh_data->Fill(d.PV_npvsGood);
            }
          }
        }
      } else if (isSignal_) {
        if (apply_all_cuts('S')) {
          uint32_t mMother = TString(sample).Contains("T2tt") ? std::round(d.evt.SUSY_Stop_Mass/5.0)*5 : std::round(d.evt.SUSY_Gluino_Mass/25.0)*25;
          uint32_t mLSP    = TString(sample).Contains("T2tt") ? std::round(d.evt.SUSY_LSP_Mass /5.0)*5 : std::round(d.evt.SUSY_LSP_Mass   /25.0)*25;
          uint32_t signal_bin = mMother * 10000 + mLSP;
          int MRR2_bin = calc_mrr2_bin_(d, 'S');
          m_vh_MRR2_sig[signal_bin][syst_index]->Fill(MRR2_bin, sf_weight['S']);
          if (nJet>=4) {
            if (nJet<6) m_vh_MRR2_sig_nj45[signal_bin][syst_index]->Fill(MRR2_bin, sf_weight['S']);
            else        m_vh_MRR2_sig_nj6 [signal_bin][syst_index]->Fill(MRR2_bin, sf_weight['S']);
          }
          // npv for Signal
          if (TString(sample).Contains("T2tt")) {
            vh_npvLowHigh_signal[1]->Fill(d.evt.SUSY_Stop_Mass,   d.evt.SUSY_LSP_Mass, d.evt.NGoodVtx);
          } else {
            vh_npvLowHigh_signal[0]->Fill(d.evt.SUSY_Gluino_Mass, d.evt.SUSY_LSP_Mass, d.evt.NGoodVtx);
          }
        } else {
          // Backgrounds
          for (size_t i=0; i<regions.size(); ++i) {
            if (apply_all_cuts(regions[i])) {
              int MRR2_bin = calc_mrr2_bin_(d, regions[i]);
              vvh_MRR2_bkg[i][syst_index]->Fill(MRR2_bin, sf_weight[regions[i]]);
              if (nJet>=4) {
                if (nJet<6) vvh_MRR2_bkg_nj45[i][syst_index]->Fill(MRR2_bin, sf_weight[regions[i]]);
                else        vvh_MRR2_bkg_nj6 [i][syst_index]->Fill(MRR2_bin, sf_weight[regions[i]]);
              }
              if (regions[i]=='G') {
                // Save also the direct prompt photons for G region
                // Needed for transfer factors
                if (d.Photon[i].isPromptDirect[iPhotonSelect[0]]==1) {
                  vvh_MRR2_bkg[i+1][syst_index]->Fill(MRR2_bin, sf_weight[regions[i]]);
                  if (nJet>=4) {
                    if (nJet<6) vvh_MRR2_bkg_nj45[i+1][syst_index]->Fill(MRR2_bin, sf_weight[regions[i]]);
                    else        vvh_MRR2_bkg_nj6 [i+1][syst_index]->Fill(MRR2_bin, sf_weight[regions[i]]);
                  }
                }
              }
            }
          }
          // Signal regions with loosened tau32/21 requirements
          //#if TOP == 0
            if (apply_all_cuts_except('S',"1W")&&nWMassTag>=1) {
              int MRR2_bin = calc_mrr2_bin_(d, 'S');
              vvh_MRR2_bkg[regions.size()+1][syst_index]->Fill(MRR2_bin, sf_weight['S']);
              if (nJet>=4) {
                if (nJet<6) vvh_MRR2_bkg_nj45[regions.size()+1][syst_index]->Fill(MRR2_bin, sf_weight['S']);
                else        vvh_MRR2_bkg_nj6 [regions.size()+1][syst_index]->Fill(MRR2_bin, sf_weight['S']);
              }
            }
            //#else
              if (apply_all_cuts_except('S',"1Top")&&nHadTopTag4>=1) {
                int MRR2_bin = calc_mrr2_bin_(d, 'S');
                vvh_MRR2_bkg[regions.size()+1][syst_index]->Fill(MRR2_bin, sf_weight['S']);
                if (nJet>=4) {
                  if (nJet<6) vvh_MRR2_bkg_nj45[regions.size()+1][syst_index]->Fill(MRR2_bin, sf_weight['S']);
                  else        vvh_MRR2_bkg_nj6 [regions.size()+1][syst_index]->Fill(MRR2_bin, sf_weight['S']);
                }
              }
              //#endif
                }
      } // end of systematics
    } else {
      // Skimming only histos
      nJet = nJetAK8 = 0;
      for(size_t i=0; i<d.Jet.size(); ++i) {
        // Jet ID
        if ( d.Jet[i].jetId >= 2 &&
             d.Jet[i].pt         >= JET_AK4_PT_CUT &&
             std::abs(d.Jet[i].eta)  <  JET_AK4_ETA_CUT ) {
          nJet++;
        }
      }
      for (size_t i=0; i<d.FatJet.size(); ++i) {
        // Jet ID
        if ( d.FatJet[i].jetId == 2 &&
             d.FatJet[i].pt         >= JET_AK8_PT_CUT &&
             std::abs(d.FatJet[i].eta)  <  JET_AK8_ETA_CUT ) {
          nJetAK8++;
        }
      }
      // Save the number of vertices in Data and Signal
      if (isData_) {
        // Use baseline selection
        if (nJetAK8>=1 && nJet>=3 && MR>=800 && R2>=0.08) {
          if (d.HLT_AK8PFJet450==1 || d.HLT_PFHT1050==1) {
            h_npvLowHigh_data->Fill(d.PV_npvsGood);
          }
        }
      } else if (isSignal_) {
        if (TString(sample).Contains("T2tt")) {
          vh_npvLowHigh_signal[1]->Fill(d.evt.SUSY_Stop_Mass,   d.evt.SUSY_LSP_Mass, d.evt.NGoodVtx);
        } else {
          vh_npvLowHigh_signal[0]->Fill(d.evt.SUSY_Gluino_Mass, d.evt.SUSY_LSP_Mass, d.evt.NGoodVtx);
        }
      }
    }
  }
  */
}



//_______________________________________________________
//                Benchmarking (batch) jobs

void
Analysis::job_monitoring(const int& entry, const int& ifirst, const int& ilast, const std::string& curr_file, const float threshold=5)
{
  int curr_entry = entry - ifirst;
  if (curr_entry==0) {
    sw_1k_ ->Reset();
    sw_10k_->Reset();
    sw_job_->Reset();
    sw_1k_ ->Start(kFALSE);
    sw_10k_->Start(kFALSE);
    sw_job_->Start(kFALSE);
    std::cout<<"UnixTime-FirstEvent: "<<std::time(0)<<std::endl;
  } else {
    double time_1 = sw_1_->RealTime();
    sw_1_->Reset(); sw_1_->Start(kFALSE);
    if (time_1>threshold&&curr_entry!=1) {
      ++bad_files[curr_file];
      //std::cout<<"Bad read - time threshold: "<<threshold<<"s, unresponsive time: "<<time_1<<" s, entry: "<<entry<<" occurence: "<<bad_files[curr_file]<<std::endl;
      //if(bad_files[curr_file]==5) {
      //  std::cout<<"Badly readable file found: "<<curr_file<<std::endl;
      //  if (crash_job) {
      //    std::cout<<"Reached "<<threshold<<" occurences, exiting the job and requesting new EOS copy"<<std::endl;
      //    exit(1);
      //  }
      //}
    }
    if (curr_entry%1000==0) {
      double meas_1k = 1000/sw_1k_->RealTime();
      h_read_speed_1k->Fill(meas_1k);
      sw_1k_->Reset();
      sw_1k_->Start(kFALSE);
      //std::cout<<"Meas  1k: "<<meas_1k<<std::endl;
    }
    if (curr_entry%10000==0) {
      double meas_10k = 10000/sw_10k_->RealTime();
      h_read_speed_10k->Fill(meas_10k);
      h_read_speed_vs_nevt_10k->Fill(curr_entry, meas_10k);
      sw_10k_->Reset();
      sw_10k_->Start(kFALSE);
      double time_job = sw_job_->RealTime();
      sw_job_->Start(kFALSE);
      //std::cout<<"Meas 10k: "<<meas_10k<<std::endl;
      std::cout <<"UnixTime: "<< std::time(0) << "  JobTime(s): " << time_job << "  Nevent: " << curr_entry << " (" << ((float)curr_entry)/(ilast-ifirst)*100 
                << " %)  ReadSpeed(event/s): " << (curr_entry+1)/time_job <<"        "<< std::endl;
    }
    if (entry+1==ilast) {
      sw_job_->Stop();
      double meas_job = (ilast-ifirst)/sw_job_->RealTime();
      h_read_speed_job->Fill(meas_job);
      h_read_speed_vs_nevt_job->Fill((ilast-ifirst), meas_job);
      h_runtime_job->Fill(sw_job_->RealTime()/60.);
      h_runtime_vs_nevt_job->Fill((ilast-ifirst), sw_job_->RealTime()/60.);
      std::cout<<"JobMonitoringReport RunTime(s): "<<sw_job_->RealTime()<<" Nevents: "<<(ilast-ifirst)<<" Nevt/s: "<<meas_job<<std::endl;
      for (const auto& bad_file : bad_files)
        std::cout<<"Badly readable file found: "<<bad_file.first<<" N_occurence: "<<bad_file.second<<std::endl;
      std::cout<<"UnixTime-LastEvent: "<<std::time(0)<<std::endl;
    }
  }
}

/*
int Analysis::calc_mrr2_bin_(eventBuffer& d, const char& region) {
  // Select the razor variable corresponding to the desired region
  //double MR = d.evt.MR, R2 = d.evt.R2;
  if (region=='Z') {
    R2 = R2_ll;
  } else if (region=='L') {
    R2 = R2_1vl;
  } else if (region=='G') {
    R2 = R2_pho;
    MR = MR_pho;
  }
  int MRR2_bin = -1;
  if (MR>=800&&R2>=0.08) {
    MRR2_bin = 0;
    for (const auto& r2 : { 0.12, 0.16, 0.24, 0.4, 1.5 }) {
      if (R2<r2) break;
      ++MRR2_bin;
    }
    if (MRR2_bin<5) {
      for (const auto& mr : { 1000, 1200, 1600, 2000, 4000}) {
        if (MR<mr) break;
        MRR2_bin+=5;
      }
    } else MRR2_bin=9999;
  }
  return MRR2_bin;
}
*/

void
Analysis::initialize1(const bool& varySystematics, const unsigned int& syst_nSyst, const unsigned int& syst_index) {
  // Setup histograms and read input histograms for weighting/scale_factors
  init_histos(varySystematics);
  weighting.init_weight_histos();
  scale_factors.init_sf_histos();
  event_selections.define_preselections();
  event_selections.define_event_selections();
  plotting.define_histo_settings           (weighting, event_selections, syst_nSyst, syst_index);
  plotting.define_additional_histo_settings(weighting, event_selections, syst_nSyst, syst_index);
  weighting.init_input();
  scale_factors.init_input();
}

void
Analysis::initialize2(const bool& varySystematics, const unsigned int& syst_nSyst, const unsigned int& syst_index) {
  plotting.define_analysis_histos  (weighting, syst_nSyst, syst_index);
  plotting.define_additional_histos(weighting, syst_nSyst, syst_index);
}

#endif // End header guard
