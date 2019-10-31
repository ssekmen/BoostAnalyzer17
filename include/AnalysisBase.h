#include <iostream>
#include <functional>
#include <map>
#include <vector>
#include "TTree.h"
#include "TFile.h"
#include "TF1.h"
#include "TF2.h"
#include "TH3.h"
#include "TGraphAsymmErrors.h"
#include "TProfile.h"
#include "TStopwatch.h"
#include "TRandom3.h"
#include <unistd.h>

#include "tnm.h"
#include "GluinoXSec.h"
#include "StopXSec.h"
#include "CharginoXSec.h"
#include "NeutralinoXSec.h"
#include "Razor.h"

#include "BTagCalibrationStandalone.cpp"
using namespace std;
#define YEAR    2017
// _____________________________________________________________
//        AnalysisBase: Methods common in all analysis

class AnalysisBase
{
public:
  AnalysisBase(const bool& isData, const bool& isSignal, const std::string& dirname) :
    isData(isData),
    isSignal(isSignal),
    isBackground(!isData&&!isSignal),
    sample(dirname)
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
    //for (int i=1; i<=100; ++i) {
    //  std::stringsteam ss;
    //  ss<<"pdf"<<i;
    //  bkg_syst.push_bask(ss.str());
    //}

    other_trigger_eff = 1.0;
  }
  ~AnalysisBase() {
    delete sw_1_;
    delete sw_1k_;
    delete sw_10k_;
    delete sw_job_;
  }

  typedef struct Cut { std::string name; std::function<bool()> func; } Cut;
  std::vector<Cut> baseline_cuts;

  // Functions used by the Analyzer
  void define_preselections(const eventBuffer&);

  void calculate_common_variables(eventBuffer&, const unsigned int&, const int&, int);

  void init_common_histos(const bool&);

  void fill_common_histos(eventBuffer&, const bool&, const bool&, const unsigned int&, const double&, const std::vector<std::string>&);

  double get_xsec_from_ntuple(const std::vector<std::string>&, const bool&);

  std::pair<double, double> get_xsec_totweight_from_txt_file(const std::string&);

  double get_totweight_from_ntuple(const std::vector<std::string>&, const bool&);

  void calc_signal_weightnorm(const std::vector<std::string>&, const double&, const bool&, TDirectory*, bool);

  void init_pileup_reweighting(const std::string&, const bool&, const std::vector<std::string>&);

  double get_toppt_weight(eventBuffer&, const double&, const unsigned int&, const bool&);

  double get_isr_weight(eventBuffer&, const double&, const unsigned int&, const bool&);

  //std::pair<double, double> get_signal_mass(eventBuffer&, const int&);
  std::vector<double> get_signal_mass(eventBuffer&, const int&);

  double get_pileup_weight(eventBuffer&, const double&, const unsigned int&, const bool&);

  void rescale_smear_jet_met(eventBuffer&, const bool&, const unsigned int&, const double&,
                             const double&, const double&, const bool&, const double&);

  double get_ht_weight(eventBuffer&, const double&);

  double get_alphas_weight(const std::vector<float>&, const double&, const int&);

  double get_scale_weight(const std::vector<float>&, const std::vector<double>&, const double&, const unsigned int&);

  double get_syst_weight(const double&, const double&, const double&, const double&);

  double get_syst_weight(const double&, const double&, const double&);

  void job_monitoring(const int&, const int&, const int&, const std::string&, const float);

  void init_syst_input();

  double calc_top_tagging_sf(eventBuffer&, const double&, const double&, const double&, const double&, const bool&);
  double calc_fake_top_0b_mass_tagging_sf(eventBuffer&, const double&);
  double calc_fake_top_mass_tagging_sf(eventBuffer&, const double&);
  double calc_fake_top_anti_tagging_sf(eventBuffer&, const double&);

  double calc_w_tagging_sf(eventBuffer&, const double&, const double&, const double&, const double&, const bool&);
  double calc_fake_w_mass_tagging_sf(eventBuffer&, const double&);
  double calc_fake_w_anti_tagging_sf(eventBuffer&, const double&);

  std::pair<double, double> calc_b_tagging_sf(eventBuffer&, const double&, const double&, const bool&);

  std::tuple<double, double, double> calc_ele_sf(eventBuffer&, const double&, const double&, const double&, const double&, const bool&);

  std::tuple<double, double, double> calc_muon_sf(eventBuffer&, const double&, const double&, const double&, const bool&);

  double calc_lostlep_weight(eventBuffer&, const double&);

  double calc_trigger_efficiency(eventBuffer&, const double&);

  int calc_mrr2_bin(eventBuffer&, const char&);

  std::map<char, std::vector<double> > scale_factors;
  std::map<char, double> sf_weight;
  std::vector<double> all_weights;

  double other_trigger_eff;

  const bool isData;
  const bool isSignal;
  const bool isBackground;
  const std::string sample;
  std::vector<std::string> syst;

  std::map<char, std::vector<Cut> > analysis_cuts;

  bool apply_cut(char, std::string);
  bool apply_cut(char, unsigned int);
  bool apply_ncut(char, std::string);
  bool apply_ncut(char, unsigned int);
  bool apply_cuts(char, std::vector<std::string>);
  bool apply_cuts(char, std::vector<unsigned int>);
  bool apply_all_cuts(char);
  bool apply_all_cuts_except(char, std::string);
  bool apply_all_cuts_except(char, unsigned int);
  bool apply_all_cuts_except(char, std::vector<std::string>);
  bool apply_all_cuts_except(char, std::vector<unsigned int>);

private:

  TStopwatch *sw_1_, *sw_1k_, *sw_10k_, *sw_job_;
  TRandom3 rnd_;
  std::map<std::string, int> bad_files;

  BTagCalibration* btag_calib_full_;
  BTagCalibration* btag_calib_fast_;
  BTagCalibrationReader* btag_sf_full_loose_;
  BTagCalibrationReader* btag_sf_fast_loose_;
  BTagCalibrationReader* btag_sf_full_medium_;
  BTagCalibrationReader* btag_sf_fast_medium_;

  TF1* puppisd_corrGEN_      = 0;
  TF1* puppisd_corrRECO_cen_ = 0;
  TF1* puppisd_corrRECO_for_ = 0;
};

// _____________________________________________________________
//         Analysis: Analysis specific methods/histos

class Analysis : public AnalysisBase
{
public:
  Analysis(const bool isData, const bool& isSignal, const std::string& dirname) :
    AnalysisBase(isData, isSignal, dirname)
  {}
  ~Analysis() {}

  void calculate_variables(eventBuffer&, const unsigned int&);

  bool pass_skimming(eventBuffer&);

  void define_selections(const eventBuffer&);

  virtual bool signal_selection(const eventBuffer&);

  void apply_scale_factors(eventBuffer&, const unsigned int&, const std::vector<std::vector<double> >&);

  void define_histo_options(const double&, const eventBuffer&, const unsigned int&, const unsigned int&, bool);

  void init_analysis_histos(const unsigned int&, const unsigned int&);

  void fill_analysis_histos(eventBuffer&, const unsigned int&, const double&);

  void load_analysis_histos(std::string);

  void save_analysis_histos(bool);

private:

  typedef struct Sample { std::string postfix; std::string legend; std::string color; std::vector<std::string> dirs; } Sample;
  typedef struct PostfixOptions { size_t index; std::string postfixes; std::string legends; std::string colors; } PostfixOptions;
  PostfixOptions get_pf_opts_(std::vector<std::vector<Sample> > lists, std::string);
};


//_______________________________________________________
//                 Define baseline cuts
void
AnalysisBase::define_preselections(const eventBuffer& data)
{
  baseline_cuts.clear();

  // Apply the same cuts as it is in the ntuple - Only for check
  // cut is an std::function, which we can define easily with a lambda function

  //baseline_cuts.push_back({ .name="ntuple_filter", .func = [&data]() {
  //      		      // Define cut function here:
  //      		      if ( !(data.FatJet.size()>=2) ) return 0;
  //      		      if ( !(data.FatJet.pt[0]>350) ) return 0;
  //      		      if ( !(data.FatJet.pt[1]>350) ) return 0;
  //      		      return 1;
  //      		    } });

  // Recommended event filters by MET group - Updated to 80X Recommendations
  // https://twiki.cern.ch/twiki/bin/view/CMS/MissingETOptionalFiltersRun2?rev=101#Analysis_Recommendations_for_ana
  //
  // Select at least one good vertex (|z|<24, |rho|<2, ndof>=4)
  // NGoodVtx defined in:
  // https://github.com/jkarancs/B2GTTrees/blob/v8.0.x_v2.1_Oct24/plugins/B2GEdmExtraVarProducer.cc#L528-L531
  // baseline_cuts.push_back({ .name="met_filter_NGoodVtx",          .func = [&data] { return data.evt.NGoodVtx>0; } });
  baseline_cuts.push_back({ .name="Clean_goodVertices",      .func = [&data] { return data.Flag_goodVertices; } });

  // Other filters (in 80X MiniAODv2)
  // https://twiki.cern.ch/twiki/bin/view/CMS/MissingETOptionalFiltersRun2?rev=101#What_is_available_in_MiniAOD
  baseline_cuts.push_back({ .name="Clean_CSC_Halo_SuperTight",    .func = [&data,this] { return isSignal ? 1 : data.Flag_globalSuperTightHalo2016Filter; } });
  baseline_cuts.push_back({ .name="Clean_HBHE_Noise",        .func = [&data] { return data.Flag_HBHENoiseFilter; } });
  baseline_cuts.push_back({ .name="Clean_HBHE_IsoNoise",     .func = [&data] { return data.Flag_HBHENoiseIsoFilter; } });
  baseline_cuts.push_back({ .name="Clean_Ecal_Dead_Cell_TP", .func = [&data] { return data.Flag_EcalDeadCellTriggerPrimitiveFilter; } });
  baseline_cuts.push_back({ .name="Clean_EE_Bad_Sc",         .func = [&data,this] { return isData ? data.Flag_eeBadScFilter : 1; } });
  // Not in MiniAODv2 (producer added)
  baseline_cuts.push_back({ .name="Clean_Bad_Muon",          .func = [&data] { return data.Flag_BadPFMuonFilter; } });
  //baseline_cuts.push_back({ .name="Clean_Bad_Charged",       .func = [&data] { return data.Flag_BadChargedCandidateFilter; } });
}


//_______________________________________________________
//                 Object selections


/*
  Jet ID (Oct31/Jan12 ntuple):
  https://twiki.cern.ch/twiki/bin/view/CMS/JetID13TeVRun2017

  For AK4 Jet Selection Choose:
  - Tight jet ID
  - pt > 30
  - |eta| < 2.4 //Maybe we should change the higher

  For AK8 Jet Selection Choose:
  - Tight jet ID
  - pt > 200 (this cut was lowered to 170 for skimming)
  - |eta| < 2.4 //Maybe we should change the higher

*/

#define JET_AK4_PT_CUT  40 //30 is original
#define JET_AK4_ETA_CUT 2.4
#define JET_AK8_PT_CUT  200
#define JET_AK8_ETA_CUT 2.4


/*
  Latest b-tagging WPs/SFs:
  https://twiki.cern.ch/twiki/bin/viewauth/CMS/BtagRecommendation94X

  Choose:
  - CombinedSecondaryVertex v2
  - DeepCSV >= 0.1522 (Loose - for Veto)
  - DeepCSV >= 0.4941 (Medium - for Tag)

*/

#define B_SUBJET_CSV_LOOSE_CUT 0.1522
#define B_CSV_LOOSE_CUT        0.1522
#define B_CSV_MEDIUM_CUT       0.4941
#define B_CSV_TIGHT_CUT        0.8001


/*
  Boosted W-tagging:

  Latest WPs/SFs:
  https://twiki.cern.ch/twiki/bin/view/CMS/JetWtagging?rev=54#Working_points_and_scale_factors

  W-Tag selection:
  - AK8 CHS jets
  - pt > 200
  - |eta| < 2.4
  - 65 <= Puppi SD Mass (corrected) < 105
  - Medium WP: Puppi tau21 < 0.4

*/

#define W_PT_CUT            200
#define W_ETA_CUT           2.4
#define W_SD_MASS_CUT_LOW   65
#define W_SD_MASS_CUT_HIGH  105
#if YEAR == 2018
#define W_TAU21_LOOSE_CUT   0.75 // For 2018 data
#define W_TAU21_TIGHT_CUT   0.35 // For 2018 data
#else
#define W_TAU21_LOOSE_CUT   0.55
#define W_TAU21_TIGHT_CUT   0.45 // There is a Tighter WP: 0.35
#endif

#if YEAR == 2018
#define W_TAG_HP_SF       0.964 //For 2018
#define W_TAG_HP_SF_ERR   0.032 //For 2018
#define W_TAG_LP_SF       1.118 //For 2018
#define W_TAG_LP_SF_ERR   0.143 //For 2018
#else
#define W_TAG_HP_SF       0.97
#define W_TAG_HP_SF_ERR   0.06
#define W_TAG_LP_SF       1.14
#define W_TAG_LP_SF_ERR   0.29
#endif
#define W_TAG_JMS_SF      0.982
#define W_TAG_JMS_SF_ERR  0.004
#define W_TAG_JMR_SF      1.09
#define W_TAG_JMR_SF_ERR  0.05
#define W_TAG_SIGMA_MC    10.1

/*

Top Tagging working points (No subjet B tag):

Latest WPs/SFs:
https://twiki.cern.ch/twiki/bin/view/CMS/JetTopTagging?rev=14#13_TeV_working_points_CMSSW_8_0

Choose:
- Tightest selection
- AK8 CHS jets
- 105 < Puppi SD Mass < 210
- Puppi tau32 < 0.46


Top Tagging working point (with subjet b tag):

Latest WPs/SFs:
https://twiki.cern.ch/twiki/bin/view/CMS/JetTopTagging?rev=14#13_TeV_working_points_CMSSW_8_0
https://twiki.cern.ch/twiki/bin/viewauth/CMS/BtagRecommendation94X

Choose:
- Use Tightest selection
- AK8 CHS jets
- 105 <= Puppi SD Mass < 210
- Puppi tau32 < 0.46
- max subjet BTag DeepCSV > 0.1522
*/

#define HADTOP_PT_CUT            400
#define HADTOP_ETA_CUT           2.4
#define HADTOP_SD_MASS_CUT_LOW   105
#define HADTOP_SD_MASS_CUT_HIGH  210
#define HADTOP_TAU32_CUT        0.46

#define HADTOP_TAG_SF           1.05
#define HADTOP_TAG_SF_ERR_UP    0.07
#define HADTOP_TAG_SF_ERR_DOWN  0.04

#define LEPTOP_PT_CUT            300
#define LEPTOP_ETA_CUT           2.4
#define LEPTOP_SD_MASS_CUT_LOW    50
#define LEPTOP_SD_MASS_CUT_HIGH  200 // Not un upper cut, but a massive jet version

#define TOP_BTAG_CSV         0.1522 // Common for lep/had tops


/*
  Latest Electron IDs:
  [1] Cut Based  - https://twiki.cern.ch/twiki/bin/view/CMS/CutBasedElectronIdentificationRun2?rev=41#Working_points_for_2016_data_for
  [2] MVA        - https://twiki.cern.ch/twiki/bin/view/CMS/MultivariateElectronIdentificationRun2?rev=30#Recommended_MVA_recipes_for_2016
  [3] SUSY (Use) - https://twiki.cern.ch/twiki/bin/view/CMS/SUSLeptonSF?rev=172#Electrons

  Latest Isolation WPs:
  [4] SUSY MiniIso Loose/Tight - https://twiki.cern.ch/twiki/bin/view/CMS/SUSLeptonSF?rev=172#ID_IP_ISO_AN1
  [5] RazorInclusive - https://github.com/RazorCMS/RazorAnalyzer/blob/master/src/RazorAnalyzer.cc#L1210

  Latest Impact Point Cut:
  [6] SUSY Loose/Tight IP2D (Use) - https://twiki.cern.ch/twiki/bin/view/CMS/SUSLeptonSF?rev=172#ID_IP_ISO_AN1
  [7] POG  Tight - https://twiki.cern.ch/twiki/bin/view/CMS/CutBasedElectronIdentificationRun2?rev=41#Offline_selection_criteria

  For Veto (Regions except Z) Choose:
  - Spring15 Cut based Veto ID without relIso (EA) cut
  - for pt<20  absolute iso03 (EA) < 5
  - Mini-Isolation (EA)/pt < 0.1 (Medium WP [4])
  - pt >= 5
  - |eta| < 2.5
  - |d0| < 0.2, |dz| < 0.5 (Loose IP2D [6])
  OR when using MVA:
  - Spring16 MVA Loose ID
  - for pt>=20 Mini-Isolation (EA)/pt < 0.2 (RazorInclusive cut [5])
  - pt >= 5
  - |eta| < 2.5
  - 3D IP sig < 4

  For Selection (Z) Choose:
  - Spring15 Cut based Medium ID without relIso (EA) cut
  - Mini-Isolation (EA)/pt < 0.1 (Tight WP [4])
  - pt >= 10
  - |eta| < 2.5, also exclude barrel-endcap gap [1.442,1556]
  - |d0| < 0.05, |dz| < 0.1 (Tight IP2D [6])
  OR when using MVA:
  - Spring16 MVA Loose ID
  - Mini-Isolation (EA)/pt < 0.1 (Tight WP [4])
  - pt >= 10
  - |eta| < 2.5, also exclude barrel-endcap gap [1.442,1556]
  - |d0| < 0.05, |dz| < 0.1 (Tight IP2D [6])


  For Tight Selection (TriggerEff Only) Choose:
  - Spring15 Cut based Tight ID (including relIso (EA) cut)
  - pt >= 30
  - |eta| < 2.5, also exclude barrel-endcap gap [1.442,1556]
  - |d0| < 0.05, |dz| < 0.1 (Tight IP2D and IP3D [6])

  For Loose selection (deprecated) Choose:
  - Spring15 Cut based Loose ID without relIso (EA) cut
  - Mini-Isolation (EA)/pt < 0.1 (Tight WP [4])
  - pt >= 10
  - |eta| < 2.5, also exclude barrel-endcap gap [1.442,1556]
  - |d0| < 0.2, |dz| < 0.5 (Loose IP2D [6])

*/

#define ELE_VETO_PT_CUT        5
#define ELE_VETO_ETA_CUT       2.5
#define ELE_VETO_MINIISO_CUT   0.4
#define ELE_VETO_IP_D0_CUT     0.05
#define ELE_VETO_IP_DZ_CUT     0.1
#define ELE_VETO_IP_3D_CUT     4   // For skim only
#define ELE_VETO_ABSISO_CUT    5   // For skim only

#if INC == 1
#define ELE_LOOSE_PT_CUT       25 // 5-25pt bins [5-10, 10-15, 15-25, 25 ---]
#define USE_MVA_CUT            0.46 // we are not sure
#define ELE_LOOSE_ETA_CUT      2.5

#else
#define ELE_LOOSE_PT_CUT       10
#define ELE_LOOSE_ETA_CUT      2.5
#define ELE_LOOSE_MINIISO_CUT  0.1
#define ELE_LOOSE_IP_D0_CUT    0.2
#define ELE_LOOSE_IP_DZ_CUT    0.5
#endif

#define ELE_SELECT_PT_CUT      10
#define ELE_SELECT_ETA_CUT     2.5
#define ELE_SELECT_MINIISO_CUT 0.1
#define ELE_SELECT_IP_D0_CUT   0.05
#define ELE_SELECT_IP_DZ_CUT   0.1

#if INC == 1
#define ELE_TIGHT_PT_CUT                            30
#define ELE_TIGHT_ETA_CUT                           2.5
#define ELE_TIGHT_DELTAETA_SC_CUT                   1.479
#define ELE_TIGHT_SIEIE_BARREL_CUT                  0.0101  // SigmaIEtaIEta
#define ELE_TIGHT_SIEIE_ENDCAP_CUT                  0.0279
#define ELE_TIGHT_HOVERE_ENDCAP_CUT                 0.0615
#define ELE_TIGHT_HOVERE_BARREL_CUT                 0.0597
#define ELE_TIGHT_ONEOVEREMINUSONEOVERP_BARREL_CUT  0.012
#define ELE_TIGHT_ONEOVEREMINUSONEOVERP_ENDCAP_CUT  0.00999
#define ELE_TIGHT_IP_D0_ENDCAP_CUT                  0.0351
#define ELE_TIGHT_IP_D0_BARREL_CUT                  0.0111
#define ELE_TIGHT_IP_DZ_ENDCAP_CUT                  0.417
#define ELE_TIGHT_IP_DZ_BARREL_CUT                  0.0466
#define ELE_TIGHT_LOSTHITS_ENDCAP_CUT               1
#define ELE_TIGHT_LOSTHITS_BARREL_CUT               2

#else
#define ELE_TIGHT_PT_CUT       30
//#define ELE_TIGHT_PT_CUT       10
#define ELE_TIGHT_ETA_CUT      2.5
#define ELE_TIGHT_IP_D0_CUT    0.05
#define ELE_TIGHT_IP_DZ_CUT    0.1
#define ELE_TIGHT_IP_SIG_CUT   4
#endif








/*
  Latest Muon IDs (Loose/Medium):
  [1] POG Loose/Medium - https://twiki.cern.ch/twiki/bin/view/CMS/SWGuideMuonIdRun2?rev=28#Short_Term_Instructions_for_Mori

  Latest Isolation WPs:
  [2] SUSY MiniISo Loose/Tight - https://twiki.cern.ch/twiki/bin/view/CMS/SUSLeptonSF?rev=172#ID_IP_ISO
  [3] POG Tight RelIso - https://twiki.cern.ch/twiki/bin/view/CMS/SWGuideMuonIdRun2?rev=28#Muon_Isolation
  [4] RazorInclusive - https://github.com/RazorCMS/RazorAnalyzer/blob/master/src/RazorAnalyzer.cc#L1602

  Latest Impact Point Cut (Loose/Tight):
  [5] SUSY Loose/Tight IP2D - https://twiki.cern.ch/twiki/bin/view/CMS/SUSLeptonSF?rev=172#ID_IP_ISO

  For Veto (All except Z) Choose:
  - POG recommended Loose ID (No Iso/IP)
  - for pt>=20 Mini-Isolation (EA)/pt < 0.2 (RazorInclusive cut [4])
  - for pt<20  absolute iso04 (EA) < 10
  - pt >= 5
  - |eta| < 2.4
  - 3D IP sig < 4

  For Loose Choose:
  - POG recommended Loose ID (No Iso/IP)
  - Mini-Isolation (EA)/pt < 0.2 (Tight WP [2])
  - pt >= 10
  - |eta| < 2.4
  - |d0| < 0.2, |dz| < 0.5 (Loose IP2D [5])

  For Selection (Z) Choose:
  - POG recommended Medium ID (No Iso/IP)
  - Mini-Isolation (EA)/pt < 0.2 (tight WP [2])
  - pt >= 5
  - |eta| < 2.4
  - |d0| < 0.05, |dz| < 0.1 (Tight IP2D [5])

  For Tight Selection (TriggerEff Only) Choose:
  - POG recommended Tight ID (No Iso/IP)
  - comb. rel. Isolation (R=0.4) < 0.15 (tight WP [3])
  - pt >= 30
  - |eta| < 2.4
  - |d0| < 0.05, |dz| < 0.1 (Tight IP2D and IP3D [5])

*/

#define MU_VETO_PT_CUT         5
#define MU_VETO_ETA_CUT        2.4
#define MU_VETO_MINIISO_CUT    0.4
#define MU_VETO_IP_D0_CUT      0.2
#define MU_VETO_IP_DZ_CUT      0.5
#define MU_VETO_ABSISO_CUT     10  // For skim only
#define MU_VETO_IP_3D_CUT      4   // For skim only

#if INC == 1
//------> Inclusive Specific Muon definitions (Loose selection)
#define MU_LOOSE_PT_CUT        20
#define MU_LOOSE_ETA_CUT       2.4
#define MU_LOOSE_MINIISO_CUT_0 0.2
#define MU_LOOSE_MINIISO_CUT_1 10
#define MU_LOOSE_IP_3D_CUT     4
#else
#define MU_LOOSE_PT_CUT        10
#define MU_LOOSE_ETA_CUT       2.4
#define MU_LOOSE_MINIISO_CUT   0.15
#define MU_LOOSE_IP_D0_CUT     0.2
#define MU_LOOSE_IP_DZ_CUT     0.5
#endif

#define MU_SELECT_PT_CUT       10
#define MU_SELECT_ETA_CUT      2.4
#define MU_SELECT_MINIISO_CUT  0.2
#define MU_SELECT_IP_D0_CUT    0.05
#define MU_SELECT_IP_DZ_CUT    0.1

#if INC == 1
//------> Inclusive Specific Muon definitions (Tight selection)
#define MU_TIGHT_PT_CUT        25
#define MU_TIGHT_ETA_CUT       2.4
#define MU_TIGHT_IP_3D_CUT     4
#define MU_TIGHT_IP_D0_CUT     0.2
#define MU_TIGHT_MINIISO_CUT   0.2
#else
#define MU_TIGHT_PT_CUT        30
//#define MU_TIGHT_PT_CUT        10
#define MU_TIGHT_ETA_CUT       2.4
#define MU_TIGHT_RELISO_CUT    0.15
#define MU_TIGHT_IP_D0_CUT     0.05
#define MU_TIGHT_IP_DZ_CUT     0.1
#define MU_TIGHT_IP_SIG_CUT    4
#endif
/*
  Latest Tau IDs:
  https://twiki.cern.ch/twiki/bin/view/CMS/TauIDRecommendation13TeV?rev=35

  For Veto Choose:
  - POG Loose ID:
  + byLooseCombinedIsolationDeltaBetaCorr3Hits"
  - pt >= 18 (Same as MINIAOD)

  OR use:
  - Isolated charged trk = 0
  + pt>=5 (ele/mu), 10 (hadrons)
  + isolation (dR=0.3) / pt < 0.2 (ele/mu), 0.1 (hadrons)
  + |dz| < 0.1

*/

#define  TAU_VETO_PT_CUT  18
#define  TAU_VETO_ETA_CUT 3.0


/*
  Latest Photon IDs:
  https://twiki.cern.ch/twiki/bin/view/CMS/CutBasedPhotonIdentificationRun2?rev=36

  For Selection Choose:
  - Spring16 Cut based Medium photon ID
  - Pass electron veto
  - pt >= 80
  - |eta| < 2.5

*/


#define PHOTON_SELECT_PT_CUT        80
#define PHOTON_SELECT_ETA_CUT       2.5

/*
//_______________________________________________________
//              Rescale jet 4-momenta

// Variables to save the original values before applying any systematics on them
std::vector<float> AK4_E, AK4_pt;
std::vector<float> AK8_E, AK8_pt, AK8_softDropMass;//, AK8_trimmedMass, AK8_prunedMass, AK8_filteredMass;
std::vector<float> AK8_softDropMass0;
std::vector<float> AK8_softDropMass1;
std::vector<float> AK8_softDropMass2;
std::vector<float> AK8_softDropMassCorr; // Correction for W tagging
std::vector<float> softDropMassCorr;     // POG Correction + uncertainties for W tagging
std::vector<float> softDropMass;         // JES Correction + uncertainties for top tagging

std::vector<float> AK4_JERSmearFactor,     AK8_JERSmearFactor;
std::vector<float> AK4_JERSmearFactorUp,   AK8_JERSmearFactorUp;
std::vector<float> AK4_JERSmearFactorDown, AK8_JERSmearFactorDown;
std::vector<float> AK8_JMR_random;

TVector3 met;
TVector3 dmet_JESUp,  dmet_JESDown;
TVector3 dmet_JERUp,  dmet_JERDown;
TVector3 dmet_RestUp, dmet_RestDown;

bool recalc_megajets;

void
AnalysisBase::rescale_smear_jet_met(eventBuffer data, const bool& applySmearing, const unsigned int& syst_index,
const double& nSigmaJES, const double& nSigmaJER, const double& nSigmaRestMET,
const bool& rescaleAK8, const double& nSigmaRescaleAK8)
{
// Apply Jet Energy Scale (JES) and Jet Energy Resolution (JER) corrections
// For AK8 jets which are used for W tagging (only):
// - Additionally or instead apply jet mass scale (JMS) and jet mass resolutin (JMR) corrections
recalc_megajets = (nSigmaJES!=0) || (nSig9aJER!=0);

// Initialization (needed for later variations
if (syst_index==0) {
// Save the original values for later (before applying any systematics)
AK4_pt           = data.Jet[i].pt;
AK8_E            = data.FatJet[i].E;
AK8_pt           = data.FatJet[i].pt;
AK8_softDropMass = data.FatJet[i].msoftdrop;

// Correction for Puppi SoftDrop Mass
// (Needed for W tagging)
// https://twiki.cern.ch/twiki/bin/view/CMS/JetWtagging?rev=43#Working_points_and_scale_factors
AK8_softDropMassCorr.clear();
for (size_t i=0; i<data.FatJet.size()(); ++i) {
double puppi_pt  = data.FatJet[i].pt;
double puppi_eta = data.FatJet[i].eta;
double puppi_sd_mass_w = data.FatJet[i].msoftdrop;
double corr = puppisd_corrGEN_->Eval(puppi_pt);
if(std::abs(puppi_eta)<=1.3) corr *= puppisd_corrRECO_cen_->Eval(puppi_pt);
else corr *= puppisd_corrRECO_for_->Eval(puppi_pt);
AK8_softDropMassCorr.push_back(puppi_sd_mass_w * corr);
}

*/
/*
// Calculate the JER/JMR smear factors
if (applySmearing) {
AK4_JERSmearFactor    .clear();
AK4_JERSmearFactorUp  .clear();
AK4_JERSmearFactorDown.clear();
for (size_t i=0; i<data.Jet.size(); ++i) {
double JERSmear     = data.Jet[i].Smearedpt[i]/data.Jet[i].pt[i];
double JERSmearUp   = 1 + (JERSmear-1) * (data.Jet[i].JERSFUp[i]  -1) / (data.Jet[i].JERSF[i]-1);
double JERSmearDown = 1 + (JERSmear-1) * (data.Jet[i].JERSFDown[i]-1) / (data.Jet[i].JERSF[i]-1);
AK4_JERSmearFactor    .push_back(JERSmear);
AK4_JERSmearFactorUp  .push_back(JERSmearUp);
AK4_JERSmearFactorDown.push_back(JERSmearDown);
}
AK8_JERSmearFactor    .clear();
AK8_JERSmearFactorUp  .clear();
AK8_JERSmearFactorDown.clear();
AK8_JMR_random.clear();
for (size_t i=0; i<data.FatJet.size()(); ++i) {
double JERSmear     = data.FatJet.Smearedpt[i]/data.FatJet[i].pt;
double JERSmearUp   = 1 + (JERSmear-1) * (data.FatJet.JERSFUp[i]  -1) / (data.FatJet.JERSF[i]-1);
double JERSmearDown = 1 + (JERSmear-1) * (data.FatJet.JERSFDown[i]-1) / (data.FatJet.JERSF[i]-1);
AK8_JERSmearFactor    .push_back(JERSmear);
AK8_JERSmearFactorUp  .push_back(JERSmearUp);
AK8_JERSmearFactorDown.push_back(JERSmearDown);
// Apply random gaussian smearing to worsen mass resolution (It cannot improve with this method)
// Recipe is the same as the stochastic smearing explained here:
// https://twiki.cern.ch/twiki/bin/viewauth/CMS/JetResolution#Smearing_procedures
// Generate the random number once, and vary the systematics only on the SF
double sigma_rel = W_TAG_SIGMA_MC / (AK8_softDropMassCorr[i] * W_TAG_JMS_SF);
double random = rnd_.Gaus(0,sigma_rel);
AK8_JMR_random.push_back(random);
}
}
*/

//_________________________________________________
//                      MET

/*
// Save the original MET
met.SetPtEtaPhi(data.MET_pt, 0, data.MET_phi);

}
*/

/*
// Apply systematic variations
// Even if Sigmas=0, we still smear jets!
// AK4 jets
while(data.Jet.Loop()) {
size_t i = data.Jet[i].it;
double scaleJES = get_syst_weight(1.0, data.Jet[i].jecUncertainty, nSigmaJES);
data.Jet[i].pt[i] = AK4_pt[i] * scaleJES;
data.Jet[i].E[i]  = AK4_E[i]  * scaleJES;
if (applySmearing) {
double scaleJER = get_syst_weight(AK4_JERSmearFactor[i], AK4_JERSmearFactorUp[i], AK4_JERSmearFactorDown[i], nSigmaJER);
data.Jet[i].pt[i] *= scaleJER;
data.Jet[i].E[i]  *= scaleJER;
}
}
// AK8 jets
softDropMassCorr.clear();
softDropMass    .clear();
while(data.FatJet.Loop()) {
size_t i = data.FatJet.it;
double scaleJES = get_syst_weight(1.0, data.FatJet.jecUncertainty[i], nSigmaJES);
data.FatJet[i].pt = AK8_pt[i] * scaleJES;
data.FatJet.E[i]  = AK8_E[i]  * scaleJES;
double scaleJER = 1;
if (applySmearing) {
scaleJER = get_syst_weight(AK8_JERSmearFactor[i], AK8_JERSmearFactorUp[i], AK8_JERSmearFactorDown[i], nSigmaJER);
data.FatJet[i].pt *= scaleJER;
data.FatJet.E[i]  *= scaleJER;
}
*/

/*
  double rescale_v4 = 1.0;
  if (rescaleAK8) {
  // Apply AK8 jet rescaling to match data distribution for Z/G/DY MCs
  // Get the scale/offset from: scripts/calc_pt_scaling.C
  // Rescale the whole 4-momentum, because the Z-mass peak (in AK8 jet) also looks shifted
  //double scale = 0.867 + 0.039*nSigmaRescaleAK8, offset = 33.2 + 36.4 *nSigmaRescaleAK8;
  double scale = 0.848 + 0.047*nSigmaRescaleAK8, offset = 39.6 + 38.7 *nSigmaRescaleAK8;
  // Use original pt without any scale/smear to determine the right scaling
  double orig_pt = AK8_pt[i];
  if (applySmearing) orig_pt *= AK8_JERSmearFactor[i];
  rescale_v4 = scale + offset/orig_pt;
  data.FatJet[i].pt *= rescale_v4;
  data.FatJet[i].E  *= rescale_v4;
  }
  //AK8_Ht += data.FatJet[i].pt;

*/
/*
// For W jet mass apply combination of both JES+JMS and JMR (JER not needed)
// JES uncertainty is added on top of the JMS one (in quadrature)
double comb_unc = std::sqrt(W_TAG_JMS_SF_ERR*W_TAG_JMS_SF_ERR + data.FatJet.jecUncertainty[i]*data.FatJet.jecUncertainty[i]);
double scaleJMS = get_syst_weight(W_TAG_JMS_SF, comb_unc, nSigmaJES);
//double scaled_corrected_mass = AK8_softDropMassCorr[i] * scaleJMS * rescale_v4;
double scaled_corrected_mass = AK8_softDropMassCorr[i] * scaleJMS;
// Apply random gaussian smearing to worsen mass resolution (It cannot improve with this method)
if (applySmearing) {
double scale_factor = get_syst_weight(W_TAG_JMR_SF, W_TAG_JMR_SF_ERR, nSigmaJER);
if (scale_factor > 1) {
double scaleJMR = 1 + AK8_JMR_random[i] * std::sqrt( scale_factor*scale_factor - 1 );
scaled_corrected_mass *= scaleJMR;
}
}
softDropMassCorr.push_back(scaled_corrected_mass);

// For Top jet mass, apply only JES + JER for now
// (Since there's no other recommendation)
double scaled_top_mass = AK8_softDropMass[i] * scaleJES;
if (applySmearing) scaled_top_mass *= scaleJER;
softDropMass.push_back(scaled_top_mass);

}
TVector3 dmet(0,0,0);
TVector3 shifted_met = met + dmet;
data.MET_pt[0]  = shifted_met.pt();
data.MET_phi[0] = shifted_met.phi();
}
*/
//_______________________________________________________
//                 Define common variables


// AK4 jets
/*
  convention:

  iObject  -  gives the index of the nth selected object in the original collection

  example:
  for (size_t i=0; i<nJet; ++i) h_pt->Fill( data.Jet[i].pt[iJet[i]] );
  or
  if (nJet>0) vh_pt[0] -> Fill( data.Jet[i].pt[iJet[0]] );
  if (nJet>1) vh_pt[1] -> Fill( data.Jet[i].pt[iJet[1]] );


  itObject  -  gives the index in the selected collection

  example:
  for (size_t it=0; it<data.Jet[i].size(); ++it)
  if (passLooseJet[it]) vh_pt[itJet[it]]->Fill( data.Jet[i].pt[it] );

*/

//std::pair<double, double> susy_mass;
std::vector<double> susy_mass;

std::vector<size_t > iJet;
std::vector<size_t > iJetLepTightNoIso;
std::vector<size_t > iJetLepTight2D;
std::vector<size_t > iJetNoLep;
std::vector<size_t > iLooseBTag;
std::vector<size_t > iMediumBTag;
std::vector<size_t > iTightBTag;
std::vector<size_t > itJet;
std::vector<size_t > itJetNoLep;
std::vector<size_t > itLooseBTag;
std::vector<size_t > itMediumBTag;
std::vector<size_t > itTightBTag;
std::vector<bool> passLooseJet;
std::vector<bool> passLooseJetNoLep;
std::vector<bool> passLooseJetNoPho;
std::vector<bool> passLooseBTag;
std::vector<bool> passMediumBTag;
std::vector<bool> passTightBTag;
std::vector<bool> passLooseIsoBTag;
std::vector<bool> passMediumIsoBTag;
std::vector<double> AK4_photonDR;
std::vector<double> AK4_photonPtRatio;
std::vector<double> AK4_eleDR;
std::vector<double> AK4_elePtRatio;
std::vector<double> AK4_muonDR;
std::vector<double> AK4_muonPtRatio;
size_t nJet;
size_t nJetNoLep;
size_t nJetNoPho;
size_t nLooseBTag;
size_t nMediumBTag;
size_t nMediumBTagNoPho;
size_t nTightBTag;
size_t nLooseIsoBTag;
size_t nMediumIsoBTag;
double AK4_Ht, AK4_HtOnline, AK4_HtNoLep;
double minDeltaPhi; // Min(DeltaPhi(Jet_i, MET)), i=1,2,3,4
double dPhiRazor, dPhiRazorNoPho, dPhiRazor_new;

// AK8 jets
std::vector<size_t > iJetAK8;
std::vector<size_t > iWMassTag;
std::vector<size_t > iBoostMassTag;
std::vector<size_t > iBoostMassBTag;
std::vector<size_t > iLooseWTag;
std::vector<size_t > iTightWTag;
std::vector<size_t > iTightWAntiTag;
std::vector<size_t > iHadTopMassTag;
std::vector<size_t > iHadTop1BMassTag;
std::vector<size_t > iHadTopTag;
std::vector<size_t > iHadTop0BMassTag;
std::vector<size_t > iHadTop0BAntiTag;
std::vector<size_t > itJetAK8;
std::vector<size_t > itWMassTag;
std::vector<size_t > itBoostMassTag;
std::vector<size_t > itBoostMassBTag;
std::vector<size_t > itLooseWTag;
std::vector<size_t > itTightWTag;
std::vector<size_t > itTightWAntiTag;
std::vector<size_t > itHadTopMassTag;
std::vector<size_t > itHadTop1BMassTag;
std::vector<size_t > itHadTopTag;
std::vector<size_t > itHadTop0BMassTag;
std::vector<size_t > itHadTop0BAntiTag;
std::vector<double> tau21;
std::vector<double> tau31;
std::vector<double> tau32;
std::vector<double> AK8_photonDR;
std::vector<double> AK8_photonPtRatio;
std::vector<double> AK8_eleDR;
std::vector<double> AK8_elePtRatio;
std::vector<double> AK8_muonDR;
std::vector<double> AK8_muonPtRatio;
std::vector<double> AK8_maxSubJetCSV;
std::vector<double> AK8_E;
std::vector<double> AK8_LSF;
std::vector<double> AK8_LSF_NoIso;
std::vector<int>    AK8_nSubJet;
std::vector<float> softDropMassW;
std::vector<float> softDropMassTop;
std::vector<bool> passSubJetBTag;
std::vector<bool> passLooseJetAK8;
std::vector<bool> passWMassTag;
std::vector<bool> passBoostMassTag;
std::vector<bool> passBoostMassBTag;
std::vector<bool> passLooseWTag;
std::vector<bool> passTightWTag;
std::vector<bool> passTightWAntiTag;
std::vector<bool> passHadTopTag;
std::vector<bool> passHadTopMassTag;
std::vector<bool> passHadTop1BMassTag;
std::vector<bool> passHadTop0BMassTag;
std::vector<bool> passHadTop0BAntiTag;
std::vector<bool> passOtherWMassTag;
std::vector<bool> passOtherTightWTag;
std::vector<bool> passOtherTightWAntiTag;
std::vector<bool> passOtherHadTopTag;
std::vector<bool> passOtherHadTopMassTag;
std::vector<bool> passOtherHadTop0BMassTag;
std::vector<bool> passOtherHadTop0BAntiTag;
size_t nJetAK8;
size_t nJetAK8mass;
size_t nWMassTag;
size_t nBoostMassTag;
size_t nBoostMassBTag;
size_t nLooseWTag;
size_t nTightWTag;
size_t nHadWTag1;
size_t nHadWTag3;
size_t nTightWAntiTag;
size_t nSubJetBTag;
size_t nHadTopTag;
size_t nHadTopTag2;
size_t nHadTopTag3;
size_t nHadTopTag4;
size_t nHadTopMassTag;
size_t nHadTop1BMassTag;
size_t nHadTop0BMassTag;
size_t nHadTop0BAntiTag;
double AK8_Ht;
double minDeltaR_W_b;
// All new and old tagger WPs
size_t nW1;
size_t nW2;
size_t nW3;
size_t nTop1;
size_t nTop2;
size_t nTop3;
size_t nTop4;
size_t nTop5;
size_t nWDeepMD1;
size_t nWDeepMD2;
size_t nWDeepMD3;
size_t nWDeep1;
size_t nWDeep2;
size_t nWDeep3;
size_t nZDeepMD1;
size_t nZDeepMD2;
size_t nZDeepMD3;
size_t nZDeep1;
size_t nZDeep2;
size_t nZDeep3;
size_t nVDeep1;
size_t nVDeep2;
size_t nVDeep3;
size_t nHDeepMD1;
size_t nHDeepMD2;
size_t nHDeepMD3;
size_t nHDeep1;
size_t nHDeep2;
size_t nHDeep3;
size_t nTopDeepMD1;
size_t nTopDeepMD2;
size_t nTopDeepMD3;
size_t nTopDeepMD4;
size_t nTopDeep1;
size_t nTopDeep2;
size_t nTopDeep3;
size_t nTopDeep4;
double dPhiBoostedJetMET;
double dPhiBoostedJetLep;
double dPhiBoostedJetLepMET;
// Selected tagger and WP - Start using these from now on!
std::vector<size_t > iHadW;
std::vector<size_t > iHadZ;
std::vector<size_t > iHadV;
std::vector<size_t > iHadH;
std::vector<size_t > iHadTop;
std::vector<size_t > iLepJetCand;
std::vector<size_t > iLepJet;
std::vector<size_t > iLepTop;
std::vector<size_t > iLepJetHighMass;
std::vector<size_t > iLepTopHighMass;
std::vector<size_t > itHadW;
std::vector<size_t > itHadZ;
std::vector<size_t > itHadV;
std::vector<size_t > itHadH;
std::vector<size_t > itHadTop;
std::vector<size_t > itLepJetCand;
std::vector<size_t > itLepJet;
std::vector<size_t > itLepTop;
std::vector<size_t > itLepJetHighMass;
std::vector<size_t > itLepTopHighMass;
std::vector<bool> passHadW;
std::vector<bool> passHadZ;
std::vector<bool> passHadV;
std::vector<bool> passHadH;
std::vector<bool> passHadTop;
std::vector<bool> passLepJetCand;
std::vector<bool> passLepJet;
std::vector<bool> passLepJetNoIso;
std::vector<bool> passLepJetNoPt;
std::vector<bool> passLepTop;
std::vector<bool> passLepJetHighMass;
std::vector<bool> passLepTopHighMass;
std::vector<bool> passLepTopNoIso;
std::vector<bool> passLepTopNoPt;
std::vector<bool> passLepTopNoMass;
std::vector<bool> passLepTopNoSubJetB;
size_t nHadW;
size_t nHadZ;
size_t nHadV;
size_t nHadH;
size_t nHadTop;
size_t nLepJetCand;
size_t nLepJet;
size_t nLepTop;
size_t nLepJetHighMass;
size_t nLepTopHighMass;

// Leptons
std::vector<size_t > iEleVeto;
std::vector<size_t > iMuVeto;
std::vector<size_t > iTauVeto;
std::vector<size_t > iEleLoose;
std::vector<size_t > iMuLoose;
std::vector<size_t > iEleSelect;
std::vector<size_t > iMuSelect;
std::vector<size_t > iLepTest;
std::vector<size_t > itEleVeto;
std::vector<size_t > itMuVeto;
std::vector<size_t > itTauVeto;
std::vector<size_t > itEleLoose;
std::vector<size_t > itMuLoose;
std::vector<size_t > itEleSelect;
std::vector<size_t > itMuSelect;
std::vector<size_t > iEleTight;
std::vector<size_t > iEleTightNoIso;
std::vector<size_t > iEleTight2D;
std::vector<size_t > iMuTight;
std::vector<size_t > iMuTightNoIso;
std::vector<size_t > iMuTight2D;
std::vector<size_t > itEleTight;
std::vector<size_t > itMuTight;
std::vector<size_t > itEleTest;
std::vector<size_t > itMuTest;
std::vector<size_t > itLepTest;
std::vector<bool> passEleVeto;
std::vector<bool> passEleVetoNoIso;
std::vector<bool> passMuVeto;
std::vector<bool> passMuVetoNoIso;
std::vector<bool> passTauVeto;
std::vector<bool> passEleLoose;
std::vector<bool> passMuLoose;
std::vector<bool> passEleSelect;
std::vector<bool> passMuSelect;
std::vector<bool> passEleTight;
std::vector<bool> passEleTightNoIso;
std::vector<bool> passEleTight2D;
std::vector<bool> passMuTight;
std::vector<bool> passMuTightNoIso;
std::vector<bool> passMuTight2D;
std::vector<bool> passEleTest;
std::vector<bool> passMuTest;
std::vector<double> eleJetDR;
std::vector<double> eleJetDPhi;
std::vector<double> eleJetPt;
std::vector<double> muJetDR;
std::vector<double> muJetDPhi;
std::vector<double> muJetPt;
std::vector<double> eleCleanJetDRmin, eleCleanJetPtrel;
std::vector<double> muCleanJetDRmin,  muCleanJetPtrel;
std::vector<double> tightNoIsoLepCleanJetDRmin, tightNoIsoLepCleanJetPtrel;
std::vector<double> ak8MatchedTightNoIsoLepCleanJetDRmin, ak8MatchedTightNoIsoLepCleanJetPtrel;
std::vector<int>    ak8MatchedGenLeptonMotherID;

size_t nEleVetoNoIso;
size_t nEleVeto;
size_t nEleLoose;
size_t nEleSelect;
size_t nEleTight;
size_t nEleTightNoIso;
size_t nEleTight2D;
size_t nMuVetoNoIso;
size_t nMuVeto;
size_t nMuLoose;
size_t nMuSelect;
size_t nMuTight;
size_t nMuTightNoIso;
size_t nMuTight2D;
size_t nTauVeto;
size_t nLepVetoNoIso;
size_t nLepVeto2D;
size_t nLepVeto;
size_t nLepLoose;
size_t nLepSelect;
size_t nLepTight;
size_t nLepTightNoIso;
size_t nLepTight2D;
size_t nEleTest;
size_t nMuTest;
size_t nLepTest;
// Photons
std::vector<size_t > iPhotonPreSelect;
std::vector<size_t > iPhotonSelect;
std::vector<size_t > iPhotonFake;
std::vector<size_t > itPhotonPreSelect;
std::vector<size_t > itPhotonSelect;
std::vector<size_t > itPhotonFake;
std::vector<bool> passPhotonPreSelect;
std::vector<bool> passPhotonSelect;
//std::vector<bool> passPhotonPrompt;
std::vector<bool> passPhotonFake;
std::vector<double> ChargedHadronIsoEACorr;
size_t nPhotonPreSelect, nPhotonSelect, nPhotonFake;
double tightLeppt, tightLepEta, tightLepPhi;        // For Inclusive analysis
double MT, MT_vetolep, MT_allvetolep, MT_lepTight, MT_lepTightNoIso, MT_lepTight2D;
double MT_boost;
double vetoLepPt, vetoLepEta, vetoLepPhi;
double MET_1l, MTR_1l, R_1l, R2_1l, minDeltaPhi_1l, M_1l;
double MET_1vl, MTR_1vl, R_1vl, R2_1vl, minDeltaPhi_1vl, M_1vl;
double MET_ll, MTR_ll, R_ll, R2_ll, minDeltaPhi_ll, M_ll, M_ll_lepTight;
double MET_pho, MR_pho, MTR_pho, R_pho, R2_pho, minDeltaPhi_pho;
double MET_pz, MET_eta;
double MR_new, MTR_new, R_new, R2_new;
double dPhi_ll_met, dPhi_ll_jet;
std::vector<TLorentzVector> TightWTag;
std::vector<TLorentzVector> hemis_AK4;
std::vector<TLorentzVector> hemis_AK4_nophoton;
std::vector<TLorentzVector> saved_hemis_AK4;
std::vector<TLorentzVector> saved_hemis_AK4_nophoton;
std::vector<TLorentzVector> newhemis_AK4;
std::vector<TLorentzVector> newhemis_AK4_nophoton;
std::vector<TLorentzVector> saved_newhemis_AK4;
std::vector<TLorentzVector> saved_newhemis_AK4_nophoton;

// gen particles
std::vector<bool> passGenLastCopyCand;
std::vector<bool> passGenNoSameMother;
std::vector<bool> passGenFinalState;
std::vector<bool> passGenLepton;
std::vector<bool> passGenLeptonFromW;
std::vector<bool> passGenLeptonFromZ;
std::vector<bool> passGenLeptonFromH;
std::vector<bool> passGenLeptonFromTop;
std::vector<bool> passGenb;
std::vector<bool> passGenW;
std::vector<bool> passGenLepW;
std::vector<bool> passGenHadW;
std::vector<bool> passGenZ;
std::vector<bool> passGenLepZ;
std::vector<bool> passGenHadZ;
std::vector<bool> passGenH;
std::vector<bool> passGenLepH;
std::vector<bool> passGenHadH;
std::vector<bool> passGenTop;
std::vector<bool> passGenLepTop;
std::vector<bool> passGenHadTop;
// matching to objects
std::vector<bool> genLepPassLepVeto;
std::vector<bool> genLepPassLepTightNoIso;
std::vector<bool> genLepPassLepTight2D;
std::vector<bool> genHadWPassHadWTag;
std::vector<bool> genHadZPassHadZTag;
std::vector<bool> genHadHPassHadHTag;
std::vector<bool> genHadTopPassHadTopTag;
std::vector<bool> genLepTopPassLepTopTag;
std::vector<bool> genHadWPassHadWMassTag;
std::vector<bool> genHadTopPassHadTopMassTag;
// object gen truth
std::vector<bool> ak8MatchGenHadW;
std::vector<bool> ak8MatchGenHadZ;
std::vector<bool> ak8MatchGenHadH;
std::vector<bool> ak8MatchGenHadTop;
std::vector<bool> ak8MatchGenLepTop;
std::vector<bool> ak8MatchGenLepton;
std::vector<bool> eleMatchGenEle;
std::vector<bool> eleMatchGenEleFromW;
std::vector<bool> eleMatchGenEleFromZ;
std::vector<bool> eleMatchGenEleFromH;
std::vector<bool> eleMatchGenEleFromTop;
std::vector<bool> muMatchGenMu;
std::vector<bool> muMatchGenMuFromW;
std::vector<bool> muMatchGenMuFromZ;
std::vector<bool> muMatchGenMuFromH;
std::vector<bool> muMatchGenMuFromTop;
std::vector<size_t > iGenLepton,        itGenLepton;
std::vector<size_t > iGenLeptonFromW,   itGenLeptonFromW;
std::vector<size_t > iGenLeptonFromZ,   itGenLeptonFromZ;
std::vector<size_t > iGenLeptonFromH,   itGenLeptonFromH;
std::vector<size_t > iGenLeptonFromTop, itGenLeptonFromTop;
std::vector<size_t > iGenb,       itGenb;
std::vector<size_t > iGenW,       itGenW;
std::vector<size_t > iGenLepW,    itGenLepW;
std::vector<size_t > iGenHadW,    itGenHadW;
std::vector<size_t > iGenZ,	  itGenZ;
std::vector<size_t > iGenLepZ,	  itGenLepZ;
std::vector<size_t > iGenHadZ,	  itGenHadZ;
std::vector<size_t > iGenH,       itGenH;
std::vector<size_t > iGenLepH,    itGenLepH;
std::vector<size_t > iGenHadH,    itGenHadH;
std::vector<size_t > iGenTop,     itGenTop;
std::vector<size_t > iGenLepTop,  itGenLepTop;
std::vector<size_t > iGenHadTop,  itGenHadTop;
std::vector<size_t > iGenHadWMatchedAK8;
std::vector<size_t > iGenHadZMatchedAK8;
std::vector<size_t > iGenHadHMatchedAK8;
std::vector<size_t > iGenHadTopMatchedAK8;
std::vector<size_t > iGenLepHMatchedAK8;
std::vector<size_t > iGenLepTopMatchedAK8;
std::vector<size_t > iGenLeptonMatchedAK8;
std::vector<size_t > iGenLepWMatchedGenLep;
std::vector<size_t > iGenLepZMatchedGenLep;
std::vector<size_t > iGenLepHMatchedGenLep;
std::vector<size_t > iGenLepTopMatchedGenLep;
std::vector<size_t > iGenWtagZ,   itGenWtagZ; // From Changgi
std::vector<size_t > iGenMassW,   itGenMassW;
std::vector<size_t > iGenMassTop, itGenMassTop;
size_t nGenLepton;
size_t nGenEle;
size_t nGenMu;
size_t nGenTau;
size_t nGenLeptonFromW;
size_t nGenEleFromW;
size_t nGenMuFromW;
size_t nGenTauFromW;
size_t nGenLeptonFromZ;
size_t nGenEleFromZ;
size_t nGenMuFromZ;
size_t nGenTauFromZ;
size_t nGenLeptonFromH;
size_t nGenEleFromH;
size_t nGenMuFromH;
size_t nGenTauFromH;
size_t nGenLeptonFromTop;
size_t nGenEleFromTop;
size_t nGenMuFromTop;
size_t nGenTauFromTop;
size_t nGenb;
size_t nGenW;
size_t nGenLepW;
size_t nGenHadW;
size_t nGenZ;
size_t nGenLepZ;
size_t nGenHadZ;
size_t nGenH;
size_t nGenLepH;
size_t nGenHadH;
size_t nGenTop;
size_t nGenLepTop;
size_t nGenHadTop;
// Changgi uses these
size_t nGenWtagZ;
size_t nGenMassW;
size_t nGenMassTop;
int nWTag; 
int nmWTag;
int npreWTag;
int nTopTag;
int nmTopTag;
int npreTopTag;
int nGenPhotonFake;
int nGenPhotonPromptDirect;
int nGenPhotonPromptFragmentation;
std::vector<TLorentzVector> veto_electrons;
std::vector<TLorentzVector> veto_muons;
//std::vector<TLorentzVector> veto_muons_noiso, veto_muons, selected_muons;
std::vector<TLorentzVector> veto_leptons_noiso, veto_leptons, selected_leptons;
std::vector<TLorentzVector> tight_leptons, tight_leptons_noiso, tight_leptons_2D, test_leptons;
std::vector<TLorentzVector> selected_jets;
std::vector<TLorentzVector> selected_bs;
std::vector<TLorentzVector> selected_Ws;
std::vector<TLorentzVector> selected_Zs;
std::vector<TLorentzVector> selected_Hs;
std::vector<TLorentzVector> selected_leptops;
std::vector<TLorentzVector> selected_hadtops;
std::vector<TLorentzVector> selected_boost;
std::vector<TLorentzVector> selected_genlep;
TLorentzVector lep_pair;
std::vector<double> r_iso_tight_leptons;
//std::vector<bool> veto_lep_in_jet;
//std::vector<bool> veto_mu_in_jet, selected_mu_in_jet;
std::vector<size_t > iJet_Boost;

bool recalc_megajets = false;

float MR, MTR, R, R2;

void
AnalysisBase::calculate_common_variables(eventBuffer& data, const unsigned int& syst_index, const int& signal_index, int debug = 0)
{
  if (debug) std::cout<<"AnalysisBase::calc_common_var: start (new event)"<<std::endl;

  // It only makes sense to calculate certain variables only once
  // if they don't depend on jet energy (eg. leptons)
  if (debug) std::cout<<"AnalysisBase::calc_common_var: init start"<<std::endl;
  std::vector<TLorentzVector> leptons_to_megajet;
  if (syst_index == 0) {
    veto_electrons     .clear();
    veto_muons         .clear();
    veto_leptons_noiso .clear();
    veto_leptons       .clear();
    selected_leptons   .clear();
    tight_leptons      .clear();
    tight_leptons_noiso.clear();
    tight_leptons_2D   .clear();
    test_leptons       .clear();
    selected_jets      .clear();
    selected_bs        .clear();
    selected_Ws        .clear();
    selected_Zs        .clear();
    selected_Hs        .clear();
    selected_leptops   .clear();
    selected_hadtops   .clear();
    selected_boost     .clear();
    selected_genlep    .clear();
    lep_pair.SetPxPyPzE(0,0,0,0);
    r_iso_tight_leptons.clear();

    if (isSignal) susy_mass = get_signal_mass(data, signal_index);

    // Initial loop on AK4 jets (needed for eg. get the jet ID for ele/muon 2D cut)
    passLooseJet       .assign(data.Jet.size(), 0);
    for(size_t i=0; i<data.Jet.size(); ++i) {
      // Jet ID (Define also after JER/JES variation!)
      passLooseJet[i] = ( (data.Jet[i].jetId == 2 || data.Jet[i].jetId == 6) &&
                          data.Jet[i].pt            >= JET_AK4_PT_CUT &&
                          std::abs(data.Jet[i].eta)  < JET_AK4_ETA_CUT );
    }
    if (debug) std::cout<<"AnalysisBase::calc_common_var: end init AK4"<<std::endl;
        
    // Intitial loop on AK8 jets
    tau21           .assign(data.FatJet.size(), 9999);
    tau31           .assign(data.FatJet.size(), 9999);
    tau32           .assign(data.FatJet.size(), 9999);
    AK8_maxSubJetCSV.assign(data.FatJet.size(), -9999);
    AK8_nSubJet     .assign(data.FatJet.size(), 0);
    passSubJetBTag  .assign(data.FatJet.size(), 0);
    nSubJetBTag = 0;
    for (size_t i=0; i<data.FatJet.size(); ++i) {
      //size_t i = data.FatJet.it;
      // N-subjettiness
      if (data.FatJet[i].tau1>0) tau21[i] = data.FatJet[i].tau2/data.FatJet[i].tau1;
      if (data.FatJet[i].tau1>0) tau31[i] = data.FatJet[i].tau3/data.FatJet[i].tau1;
      if (data.FatJet[i].tau2>0) tau32[i] = data.FatJet[i].tau3/data.FatJet[i].tau2;
      // Maximum SubJet btag discriminator
      int i_sj0 = data.FatJet[i].subJetIdx1, i_sj1 = data.FatJet[i].subJetIdx2;
      if (i_sj0 != -1) {
        ++AK8_nSubJet[i];
        if (data.SubJet[i_sj0].btagDeepB > AK8_maxSubJetCSV[i]) AK8_maxSubJetCSV[i] = data.SubJet[i_sj0].btagDeepB;
      }
      if (i_sj1 != -1) {
        ++AK8_nSubJet[i];
        if (data.SubJet[i_sj1].btagDeepB > AK8_maxSubJetCSV[i]) AK8_maxSubJetCSV[i] = data.SubJet[i_sj1].btagDeepB;
      }
      if ((passSubJetBTag[i] = (AK8_maxSubJetCSV[i] > TOP_BTAG_CSV) )) nSubJetBTag++;
    }
    if (debug) std::cout<<"AnalysisBase::calc_common_var: end init AK8"<<std::endl;

    // Event Letpons
    iEleVeto         .clear();
    iEleLoose        .clear();
    iEleSelect       .clear();
    iEleTight        .clear();
    iEleTightNoIso   .clear();
    iEleTight2D      .clear();
    iLepTest         .clear();
    iJetLepTightNoIso.clear();
    iJetLepTight2D   .clear();
    itEleVeto        .assign(data.Electron.size(), (size_t)-1);
    itEleLoose       .assign(data.Electron.size(), (size_t)-1);
    itEleSelect      .assign(data.Electron.size(), (size_t)-1);
    itEleTight       .assign(data.Electron.size(), (size_t)-1);
    itEleTest        .assign(data.Electron.size(), (size_t)-1);
    passEleVeto      .assign(data.Electron.size(), 0);
    passEleVetoNoIso .assign(data.Electron.size(), 0);
    passEleLoose     .assign(data.Electron.size(), 0);
    passEleSelect    .assign(data.Electron.size(), 0);
    passEleTight     .assign(data.Electron.size(), 0);
    passEleTightNoIso.assign(data.Electron.size(), 0);
    passEleTight2D   .assign(data.Electron.size(), 0);
    passEleTest      .assign(data.Electron.size(), 0);
    eleCleanJetDRmin      .assign(data.Electron.size(), 9999);
    eleCleanJetPtrel      .assign(data.Electron.size(), 9999);
    tightNoIsoLepCleanJetDRmin.clear();
    tightNoIsoLepCleanJetPtrel.clear();
    nEleVetoNoIso = nEleVeto = nEleLoose = nEleSelect = nEleTight = nEleTest = 0;
    nEleTightNoIso = nEleTight2D = 0;
    for (size_t i=0; i<data.Electron.size(); ++i) {
      TLorentzVector ele_v4; ele_v4.SetPtEtaPhiM(data.Electron[i].pt, data.Electron[i].eta, data.Electron[i].phi, data.Electron[i].mass);
      float pt = data.Electron[i].pt;
      float abseta = std::abs(data.Electron[i].eta);
      float miniIso = data.Electron[i].miniPFRelIso_all;
      float absd0 = std::abs(data.Electron[i].dxy);
      float absdz = std::abs(data.Electron[i].dz);
      //  float ipsig = std::abs(data.Electron[i].sip3d);
#if INC == 1

      float etasc = std::abs(data.Electron[i].deltaEtaSC + data.Electron[i].eta);  // supercluster for inclusive(nanoaod)
      float hoe = data.Electron[i].hoe; // HoverE
      float eInvMinusPInv = data.Electron[i].eInvMinusPInv; // (1/E-1/P)
      float sieie = data.Electron[i].sieie;
      float lostHits = data.Electron[i].lostHits;
      float mva = data.Electron[i].mvaFall17V2noIso_WPL;
#else
      float ipsig = std::abs(data.Electron[i].sip3d);

#endif
      //bool id_veto_noiso   = (data.Electron[i].cutBased >= 1.0);
      bool id_veto_noiso   = data.Electron[i].mvaFall17V2noIso_WPL; // Higher efficiency, no isolation
#if INC == 1
      //int categ = data.Electron[i].mvaTTH;


      float mva2 = (data.Electron[i].mvaTTH); // tryout
#else
      bool id_loose_noiso = (data.Electron[i].mvaFall17V2noIso_WPL == 1.0);
#endif
      bool id_select_noiso = (data.Electron[i].mvaFall17V2noIso_WP90 == 1.0); //medium
      bool id_select       = (data.Electron[i].mvaFall17V2Iso_WP90 == 1.0);   //medium no isolation
      // Tight ID is too inefficient for electrons, use the medium instead
#if INC == 1
      bool id_tight        = (data.Electron[i].mvaFall17V2Iso_WP80 == 1.0); //tight
#endif
      //bool id_tight_noiso  = (data.Electron[i].mvaFall17V2noIso_WP80 == 1.0); //tight no isolation
      bool id_test  = (data.Electron[i].mvaFall17V2noIso_WP80 == 1.0);

      // Calculate the B2G 2D cut variables
      // [Lepton]_jetPtRelv2 is available in v5 NanoAOD, but it is bugged :(
      // Try to do what (should be) done in NanoAOD (revert JEC, subtract ele, reapply JEC) based on the original NanoAOD recipe:
      // https://github.com/cms-nanoAOD/cmssw/blob/master-cmsswmaster/PhysicsTools/NanoAOD/plugins/LeptonJetVarProducer.cc#L152-L162
      // 1) if no jetIdx, or no jet id --> match nearest jet passing the ID for DR, leave Ptrel = 9999
      // 2) if    jetIdx -> calculate DR
      // 3)              -> subtract lep pt from jet, check if passs pt cut (if not Ptrel=9999), calculate Ptrel
      // Calculate dRmin for the associated/nearest jet
      int jetIdx = data.Electron[i].jetIdx;
      TLorentzVector jet_v4;
      bool isPartOfJet = true;
      if (jetIdx==-1) isPartOfJet = false;
      else if (!passLooseJet[jetIdx]) isPartOfJet = false;
      if (debug>1) std::cout<<"Start calculating 2D cut for - iEle="<<i<<" isPartOfJet="<<isPartOfJet<<" matched jetIdx="<<jetIdx<<std::endl;
      if (isPartOfJet) {
        jet_v4.SetPtEtaPhiM(data.Jet[jetIdx].pt, data.Jet[jetIdx].eta, data.Jet[jetIdx].phi, data.Jet[jetIdx].mass);
        eleCleanJetDRmin[i] = ele_v4.DeltaR(jet_v4);
      } else for(size_t j=0; j<data.Jet.size(); ++j) if (passLooseJet[j]) {
        jet_v4.SetPtEtaPhiM(data.Jet[j].pt, data.Jet[j].eta, data.Jet[j].phi, data.Jet[j].mass);
        double dR = ele_v4.DeltaR(jet_v4);
        if (dR<eleCleanJetDRmin[i]) {
          eleCleanJetDRmin[i] = dR;
          if (debug>1) std::cout<<" - matched to jetdIdx="<<j<<" dR="<<dR<<std::endl; 
        }
      }
      if (debug>1) std::cout<<"jetIdx="<<jetIdx<<std::endl;
      // Calculate pTrel for the associated/nearest jet
      // First subtract the ele from the jet
      // The JEC reverted ele energy subtraction should work in the mean time
      if (jetIdx!=1) {
        jet_v4.SetPtEtaPhiM(data.Jet[jetIdx].pt, data.Jet[jetIdx].eta, data.Jet[jetIdx].phi, data.Jet[jetIdx].mass);
        if (debug>1) std::cout<<"-       jet pt="<<jet_v4.Pt()<<std::endl;
        jet_v4 -= ele_v4*(1/(1-data.Jet[jetIdx].rawFactor));
        // Then, for version 2 check also that the cleaned jet passes the minimum pt threshold cut that is considered in the analysis
        // If not, revert back to the previous closest jet
        if (debug>1) std::cout<<"- clean jet pt="<<jet_v4.Pt()<<std::endl;
        if (jet_v4.Pt() >= JET_AK4_PT_CUT) {
          eleCleanJetPtrel[i] = ele_v4.Perp(jet_v4.Vect());
          if (debug>1) std::cout<<"  + pass pt cut, Ptrel="<<eleCleanJetPtrel[i]<<std::endl;
        }
      }
      if (debug>1) std::cout<<"-------------------------------------------------------------"<<std::endl;
      if (debug>1) std::cout<<"ele jet DRmin="<<eleCleanJetDRmin[i]<<" Ptrel="<<eleCleanJetPtrel[i]<<std::endl<<std::endl;

      if ((passEleVetoNoIso[i] =
           ( id_veto_noiso &&
             pt      >= ELE_VETO_PT_CUT &&
             abseta  <  ELE_VETO_ETA_CUT && //!(abseta>=1.442 && abseta< 1.556) &&
             absd0   <  ELE_VETO_IP_D0_CUT &&
             absdz   <  ELE_VETO_IP_DZ_CUT) )) {
        veto_leptons_noiso.push_back(ele_v4);
        nEleVetoNoIso++;
        if ((passEleVeto[i] = (miniIso <  ELE_VETO_MINIISO_CUT) )) {
          iEleVeto.push_back(i);
          itEleVeto[i] = nEleVeto++;
          veto_electrons.push_back(ele_v4);
          veto_leptons.push_back(ele_v4);
          //veto_lep_in_jet.push_back(data.Electron.IsPartOfNearAK4Jet[i]);
        }
      }
      // Loose
#if INC == 1

      if ((passEleLoose[i] =
           (
            (( pt > 5  || pt < 10) && ((etasc  < 0.8 && mva2 > 0.46) || ((etasc >= 0.8 && etasc < 1.479) && mva2 > -0.03) || (etasc >= 1.479 && mva2 > -0.06))) ||
            ((pt >= 10 || pt <=15) && ((etasc  < 0.8 && mva > -0.48) ||((etasc >= 0.8 && etasc < 1.479) && mva > -0.67) || (etasc >= 1.479 && mva > -0.49))) ||
            ((pt >= 15 || pt <= 25) && (  (etasc <  0.8 && mva > (-0.48-0.037)*(pt-15) ) ||
                                          ((etasc >= 0.8 && etasc < 1.479) && mva > (-0.67-0.024)*(pt-15)) ||
                                          (etasc >= 1.479 && mva > (-0.49-0.034)*(pt-15))))||
            ((pt > 25 ) &&            (  (etasc < 0.8 && mva > -0.85) || ((etasc >= 0.8 &&  etasc < 1.479) && mva > -0.91) || (etasc >= 1.479 && mva > -0.83)))

            ))) {
        iEleLoose.push_back(i);
        itEleLoose[i] = nEleLoose++;
      }
#else
      if ((passEleLoose[i] =
           ( id_loose_noiso &&
             pt        >= ELE_LOOSE_PT_CUT &&
             abseta    <  ELE_LOOSE_ETA_CUT && !(abseta>=1.442 && abseta< 1.556) &&
             miniIso   <  ELE_LOOSE_MINIISO_CUT &&
             absd0     <  ELE_LOOSE_IP_D0_CUT &&
             absdz     <  ELE_LOOSE_IP_DZ_CUT)) ) {
        iEleLoose.push_back(i);
        itEleLoose[i] = nEleLoose++;
      }
#endif
      // Select
      if ((passEleSelect[i] =
           ( id_select_noiso &&
             pt        >= ELE_SELECT_PT_CUT &&
             abseta    <  ELE_SELECT_ETA_CUT && !(abseta>=1.442 && abseta< 1.556) &&
             miniIso   <  ELE_SELECT_MINIISO_CUT &&
             absd0     <  ELE_SELECT_IP_D0_CUT &&
             absdz     <  ELE_SELECT_IP_DZ_CUT))) {
        selected_leptons.push_back(ele_v4);
        iEleSelect.push_back(i);
        itEleSelect[i] = nEleSelect++;
      }

#if INC == 1
      // Tight for inclusive
      if((passEleTight[i] =
          // *********************** should we use this ID selection????
          // Janos: no this seems to be an outdated cut based selection
          //        Please revise and remove the lines with manual cuts
          //        I advise to use id_select, id_tight might be too tight
          ( id_tight &&  
            (  ( pt             >  ELE_TIGHT_PT_CUT &&    // for Barrel selection
                 etasc          <= ELE_TIGHT_DELTAETA_SC_CUT &&
                 absd0          <  ELE_TIGHT_IP_D0_BARREL_CUT &&
                 absdz          <  ELE_TIGHT_IP_DZ_BARREL_CUT &&
                 sieie          <  ELE_TIGHT_SIEIE_BARREL_CUT &&
                 hoe            <  ELE_TIGHT_HOVERE_BARREL_CUT &&
                 lostHits       <=  ELE_TIGHT_LOSTHITS_BARREL_CUT &&
                 eInvMinusPInv  <  ELE_TIGHT_ONEOVEREMINUSONEOVERP_BARREL_CUT ) ||
               ( pt             >  ELE_TIGHT_PT_CUT &&               // for Endcap selection
                 etasc          >= ELE_TIGHT_DELTAETA_SC_CUT &&
                 etasc          < 2.5 &&
                 absd0          <  ELE_TIGHT_IP_D0_ENDCAP_CUT &&
                 absdz          <  ELE_TIGHT_IP_DZ_ENDCAP_CUT &&
                 sieie          <  ELE_TIGHT_SIEIE_ENDCAP_CUT &&
                 hoe            <  ELE_TIGHT_HOVERE_ENDCAP_CUT &&
                 lostHits       <=  ELE_TIGHT_LOSTHITS_ENDCAP_CUT &&
                 eInvMinusPInv  <  ELE_TIGHT_ONEOVEREMINUSONEOVERP_ENDCAP_CUT  )
               ))) ) {
        tight_leptons.push_back(ele_v4);
        iEleTight.push_back(i);
        itEleTight[i] = nEleTight++;
        float r_iso = std::max(0.05, std::min(0.2, 10./pt));
        r_iso_tight_leptons.push_back(r_iso);
      }

#else
      // Tight
      if ( pt        >= ELE_TIGHT_PT_CUT &&
           abseta    <  ELE_TIGHT_ETA_CUT && !(abseta>=1.442 && abseta< 1.556) &&
           absd0     <  ELE_TIGHT_IP_D0_CUT &&
           absdz     <  ELE_TIGHT_IP_DZ_CUT &&
           ipsig     <  ELE_TIGHT_IP_SIG_CUT ) {
        if (( passEleTight[i] = id_select)) {
          tight_leptons.push_back(ele_v4);
          iEleTight.push_back(i);
          itEleTight[i] = nEleTight++;
          float r_iso = std::max(0.05, std::min(0.2, 10./pt));
          r_iso_tight_leptons.push_back(r_iso);
        }
        if (( passEleTightNoIso[i] = id_select_noiso )) {
          nEleTightNoIso++;
          iEleTightNoIso.push_back(i);
          tight_leptons_noiso.push_back(ele_v4);
          iJetLepTightNoIso.push_back(data.Electron[i].jetIdx);
          tightNoIsoLepCleanJetDRmin.push_back(eleCleanJetDRmin[i]);
          tightNoIsoLepCleanJetPtrel.push_back(eleCleanJetPtrel[i]);
          if (( passEleTight2D[i] = eleCleanJetDRmin[i]>0.4 || eleCleanJetPtrel[i]>15 )) {
            nEleTight2D++;
            iEleTight2D.push_back(i);
            tight_leptons_2D.push_back(ele_v4);
            iJetLepTight2D.push_back(data.Electron[i].jetIdx);
          }
        }
      }
#endif

      if ((passEleTest[i] =
           ( id_test &&
             pt        >= 50 &&
             abseta    <  ELE_SELECT_ETA_CUT && !(abseta>=1.442 && abseta< 1.556)  &&
             absd0     <  ELE_SELECT_IP_D0_CUT &&
             absdz     <  ELE_SELECT_IP_DZ_CUT &&
             miniIso   < ELE_SELECT_MINIISO_CUT
             ))){
        test_leptons.push_back(ele_v4);
        iLepTest.push_back(i);
        itEleTest[i] = nEleTest++;
      }

      // Check if the electron needs to be added to the megajet
      if (!isPartOfJet && (passEleSelect[i]||passEleTight2D[i])) leptons_to_megajet.push_back(ele_v4);
    }


    if (debug) std::cout<<"AnalysisBase::calc_common_var: end init ele"<<std::endl;

    // Number of Veto/Select Muons
    iMuVeto         .clear();
    iMuLoose        .clear();
    iMuSelect       .clear();
    iMuTight        .clear();
    iMuTightNoIso   .clear();
    iMuTight2D      .clear();
    itMuVeto        .assign(data.Muon.size(),  (size_t)-1);
    itMuLoose       .assign(data.Muon.size(),  (size_t)-1);
    itMuSelect      .assign(data.Muon.size(),  (size_t)-1);
    itMuTight       .assign(data.Muon.size(),  (size_t)-1);
    itMuTest        .assign(data.Muon.size(),  (size_t)-1);
    passMuVeto      .assign(data.Muon.size(),  0);
    passMuVetoNoIso .assign(data.Muon.size(),  0);
    passMuLoose     .assign(data.Muon.size(),  0);
    passMuSelect    .assign(data.Muon.size(),  0);
    passMuTight     .assign(data.Muon.size(),  0);
    passMuTightNoIso.assign(data.Muon.size(),  0);
    passMuTight2D   .assign(data.Muon.size(),  0);
    passMuTest      .assign(data.Muon.size(),  0);
    muCleanJetDRmin.assign(data.Muon.size(), 9999);
    muCleanJetPtrel.assign(data.Muon.size(), 9999);
    nMuVetoNoIso = nMuVeto = nMuLoose = nMuSelect = nMuTight = nMuTest = 0;
    nMuTightNoIso = nMuTight2D = 0;
    for (size_t i=0; i<data.Muon.size(); ++i) {
      TLorentzVector mu_v4; mu_v4.SetPtEtaPhiM(data.Muon[i].pt, data.Muon[i].eta, data.Muon[i].phi, data.Muon[i].mass);
      float pt = data.Muon[i].pt;
      float abseta = std::abs(data.Muon[i].eta);
      float miniIso = data.Muon[i].miniPFRelIso_all;
      float absd0 = std::abs(data.Muon[i].dxy);
      float absdz = std::abs(data.Muon[i].dz);
      float ipsig = std::abs(data.Muon[i].sip3d);
      bool id_veto_noiso   = (data.Muon[i].softId == 1.0);
      bool id_loose_noiso  = (data.Muon[i].softId == 1.0);
      bool id_select_noiso = (data.Muon[i].mediumId == 1.0);
      bool id_tight_noiso  = (data.Muon[i].tightId == 1.0);
#if INC == 0
      float relIso = data.Muon[i].pfRelIso04_all;
#endif

      // Calculate the B2G 2D cut variables
      // [Lepton]_jetPtRelv2 is available in v5 NanoAOD, but it is bugged :(
      // Try to do what (should be) done in NanoAOD (revert JEC, subtract ele, reapply JEC) based on the original NanoAOD recipe:
      // https://github.com/cms-nanoAOD/cmssw/blob/master-cmsswmaster/PhysicsTools/NanoAOD/plugins/LeptonJetVarProducer.cc#L152-L162
      // 1) if no jetIdx, or no jet id --> match nearest jet passing the ID for DR, leave Ptrel = 9999
      // 2) if    jetIdx -> calculate DR
      // 3)              -> subtract lep pt from jet, check if passs pt cut (if not Ptrel=9999), calculate Ptrel
      // Calculate dRmin for the associated/nearest jet
      int jetIdx = data.Muon[i].jetIdx;
      TLorentzVector jet_v4;
      bool isPartOfJet = true;
      if (jetIdx==-1) isPartOfJet = false;
      else if (!passLooseJet[jetIdx]) isPartOfJet = false;
      if (isPartOfJet) {
        jet_v4.SetPtEtaPhiM(data.Jet[jetIdx].pt, data.Jet[jetIdx].eta, data.Jet[jetIdx].phi, data.Jet[jetIdx].mass);
        muCleanJetDRmin[i] = mu_v4.DeltaR(jet_v4);
      } else for(size_t j=0; j<data.Jet.size(); ++j) if (passLooseJet[j]) {
        jet_v4.SetPtEtaPhiM(data.Jet[j].pt, data.Jet[j].eta, data.Jet[j].phi, data.Jet[j].mass);
        double dR = mu_v4.DeltaR(jet_v4);
        if (dR<muCleanJetDRmin[i]) muCleanJetDRmin[i] = dR;
      }
      // Calculate pTrel for the associated/nearest jet
      // First subtract the muon from the jet
      // Similar to [Lepton]_jetPtRelv2, a useful variable Jet_muonSubtrFactor is in NanoAOD v5
      // Problem is that the Signal is in v4, and also that this variable is also bugged :(
      // The JEC reverted ele energy subtraction should work in the mean time (similar to electrons)
      if (jetIdx!=1) {
        jet_v4.SetPtEtaPhiM(data.Jet[jetIdx].pt, data.Jet[jetIdx].eta, data.Jet[jetIdx].phi, data.Jet[jetIdx].mass);
        //jet_v4 *= data.Jet[jetIdx].muonSubtrFactor; // Variable bugged
        jet_v4 -= mu_v4*(1/(1-data.Jet[jetIdx].rawFactor));
        // Then, for version 2 check also that the cleaned jet passes the minimum pt threshold cut that is considered in the analysis
        // If not, revert back to the previous closest jet
        if (jet_v4.Pt() >= JET_AK4_PT_CUT) muCleanJetPtrel[i] = mu_v4.Perp(jet_v4.Vect());
      }

      // Veto
      if ((passMuVetoNoIso[i] =
           (id_veto_noiso &&
            pt      >= MU_VETO_PT_CUT &&
            abseta  <  MU_VETO_ETA_CUT &&
            absd0   <  MU_VETO_IP_D0_CUT &&
            absdz   <  MU_VETO_IP_DZ_CUT))) {
        veto_leptons_noiso.push_back(mu_v4);
        //veto_muons_noiso.push_back(mu_v4);
        nMuVetoNoIso++;
        if ((passMuVeto[i] = (miniIso <  MU_VETO_MINIISO_CUT))) {
          iMuVeto.push_back(i);
          itMuVeto[i] = nMuVeto++;
          veto_muons.push_back(mu_v4);
          veto_leptons.push_back(mu_v4);
          //veto_muons.push_back(mu_v4);
          //veto_lep_in_jet.push_back(data.Muon[i].IsPartOfNearAK4Jet[i]);
          //veto_mu_in_jet.push_back(data.Muon[i].IsPartOfNearAK4Jet[i]);
        }
      }
      // Loose
#if INC == 1
      if ((passMuLoose[i] =
           ( (id_loose_noiso &&(
                                (pt       >  MU_LOOSE_PT_CUT &&
                                 abseta   <  MU_LOOSE_ETA_CUT &&
                                 miniIso  <  MU_LOOSE_MINIISO_CUT_0 &&
                                 ipsig    <  MU_LOOSE_IP_3D_CUT ) ||
                                (pt      <= MU_LOOSE_PT_CUT &&
                                 pt      >  5 &&
                                 abseta  <  MU_LOOSE_ETA_CUT &&
                                 miniIso <  MU_LOOSE_MINIISO_CUT_1 &&
                                 ipsig   <  MU_LOOSE_IP_3D_CUT )))))) {
        iMuLoose.push_back(i);
        itMuLoose[i] = nMuLoose++;
      }
#else
      if ((passMuLoose[i] =
           ( id_loose_noiso &&
             pt      >= MU_LOOSE_PT_CUT &&
             abseta  <  MU_LOOSE_ETA_CUT &&
             miniIso <  MU_LOOSE_MINIISO_CUT &&
             absd0   <  MU_LOOSE_IP_D0_CUT &&
             absdz   <  MU_LOOSE_IP_DZ_CUT))) {
        iMuLoose.push_back(i);
        itMuLoose[i] = nMuLoose++;
      }
#endif

      // Select
      if((passMuSelect[i] =
          ( id_select_noiso &&
            pt      >= MU_SELECT_PT_CUT &&
            abseta  <  MU_SELECT_ETA_CUT &&
            miniIso <  MU_SELECT_MINIISO_CUT &&
            absd0   <  MU_SELECT_IP_D0_CUT &&
            absdz   <  MU_SELECT_IP_DZ_CUT))) {
        selected_leptons.push_back(mu_v4);
        //selected_muons.push_back(mu_v4);
        iMuSelect.push_back(i);
        itMuSelect[i] = nMuSelect++;
        //selected_mu_in_jet.push_back(data.Muon[i].IsPartOfNearAK4Jet[i]);
      }
      // Tight
#if INC == 1                       //Inclusive Tight Muon definition.
      if ((passMuTight[i] =
           ( id_tight_noiso &&
             pt      >= MU_TIGHT_PT_CUT &&
             abseta  <  MU_TIGHT_ETA_CUT &&
             absd0   <  MU_TIGHT_IP_D0_CUT &&
             miniIso <  MU_TIGHT_MINIISO_CUT &&
             ipsig   <  MU_TIGHT_IP_3D_CUT))) {
        tight_leptons.push_back(mu_v4);
        iMuTight.push_back(i);
        itMuTight[i] = nMuTight++;
        float r_iso = std::max(0.05, std::min(0.2, 10./pt));
        r_iso_tight_leptons.push_back(r_iso);
      }
#else
      if (( passMuTightNoIso[i] =
            ( id_tight_noiso &&
              pt      >= MU_TIGHT_PT_CUT &&
              abseta  <  MU_TIGHT_ETA_CUT &&
              absd0   <  MU_TIGHT_IP_D0_CUT &&
              absdz   <  MU_TIGHT_IP_DZ_CUT &&
              ipsig   <  MU_TIGHT_IP_SIG_CUT) )) {
        nMuTightNoIso++;
        iMuTightNoIso.push_back(i);
        tight_leptons_noiso.push_back(mu_v4);
        iJetLepTightNoIso.push_back(data.Muon[i].jetIdx);
        tightNoIsoLepCleanJetDRmin.push_back(muCleanJetDRmin[i]);
        tightNoIsoLepCleanJetPtrel.push_back(muCleanJetPtrel[i]);
        if (( passMuTight[i] = relIso  <  MU_TIGHT_RELISO_CUT )) {
          tight_leptons.push_back(mu_v4);
          iMuTight.push_back(i);
          itMuTight[i] = nMuTight++;
          float r_iso = std::max(0.05, std::min(0.2, 10./pt));
          r_iso_tight_leptons.push_back(r_iso);
        }
        if (( passMuTight2D[i] = muCleanJetDRmin[i]>0.4 || muCleanJetPtrel[i]>15 )) {
          nMuTight2D++;
          iMuTight2D.push_back(i);
          tight_leptons_2D.push_back(mu_v4);
          iJetLepTight2D.push_back(data.Muon[i].jetIdx);
        }
      }
#endif

      // Test
      if((passMuTest[i] =
          ( id_select_noiso &&
            pt      >= 50 &&
            abseta  <  2.1 &&
            absd0   <  MU_SELECT_IP_D0_CUT &&
            absdz   <  MU_SELECT_IP_DZ_CUT))) {
        test_leptons.push_back(mu_v4);
        iLepTest.push_back(i);
        itMuTest[i] = nMuTest++;
      }

      // Check if the muon needs to be added to the megajet
      if (!isPartOfJet && (passMuSelect[i]||passMuTight2D[i])) leptons_to_megajet.push_back(mu_v4);
    } // end of muon loop

    if (debug) std::cout<<"AnalysisBase::calc_common_var: end init mu"<<std::endl;

    nLepVetoNoIso  = nEleVetoNoIso  + nMuVetoNoIso;
    nLepVeto       = nEleVeto       + nMuVeto;
    nLepLoose      = nEleLoose      + nMuLoose;
    nLepSelect     = nEleSelect     + nMuSelect;
    nLepTight      = nEleTight      + nMuTight;
    nLepTightNoIso = nEleTightNoIso + nMuTightNoIso;
    nLepTight2D    = nEleTight2D    + nMuTight2D;
    nLepTest       = nEleTest       + nMuTest;

    // Number of Veto Taus
    iTauVeto      .clear();
    itTauVeto     .assign(data.Tau.size(),  (size_t)-1);
    passTauVeto   .assign(data.Tau.size(),  0);
    nTauVeto = 0;
    for (size_t i=0; i<data.Tau.size(); ++i) {
      //bool id_veto = (data.Tau[i].idMVAnewDM2017v2>=4); // equivalent &4 --> Loose WP
      bool id_veto = (data.Tau[i].idMVAnewDM2017v2&1); // --> VVLoose WP
      //double pt      = data.Tau[i].pt;
      //double eta     = data.Tau[i].eta;
      //float abseta = std::abs(eta);
      // Veto
      if((passTauVeto[i] =
          ( id_veto
            //&& pt      >= TAU_VETO_PT_CUT   // inclusive
            //&& abseta  <  TAU_VETO_ETA_CUT  // inclusive
            ))) {
        iTauVeto.push_back(i);
        itTauVeto[i] = nTauVeto++;
      }
    }
    if (debug) std::cout<<"AnalysisBase::calc_common_var: end init tau"<<std::endl;

    // MT
    MT = 9999;
    if (nLepSelect==1) {
      if (nEleSelect==1) {
        MT = sqrt( 2*data.Electron[iEleSelect[0]].pt*data.MET_pt * (1 - std::cos(data.MET_phi-data.Electron[iEleSelect[0]].phi)) );
      } else if (nMuSelect==1) {
        MT = sqrt( 2*data.Muon[iMuSelect[0]].pt*data.MET_pt * (1 - std::cos(data.MET_phi-data.Muon[iMuSelect[0]].phi)) );
      }
    }

    MT_lepTight = 9999;
    if (nLepTight==1) {
      if (nEleTight==1) {
        MT_lepTight = sqrt( 2*data.Electron[iEleTight[0]].pt*data.MET_pt * (1 - std::cos(data.MET_phi-data.Electron[iEleTight[0]].phi)) );
      } else if (nMuTight==1) {
        MT_lepTight = sqrt( 2*data.Muon[iMuTight[0]].pt*data.MET_pt * (1 - std::cos(data.MET_phi-data.Muon[iMuTight[0]].phi)) );
      }
    }

    MT_lepTightNoIso = 9999;
    if (nLepTightNoIso==1) {
      if (nEleTightNoIso==1) {
        MT_lepTightNoIso = sqrt( 2*data.Electron[iEleTightNoIso[0]].pt*data.MET_pt * (1 - std::cos(data.MET_phi-data.Electron[iEleTightNoIso[0]].phi)) );
      } else if (nMuTightNoIso==1) {
        MT_lepTightNoIso = sqrt( 2*data.Muon[iMuTightNoIso[0]].pt*data.MET_pt * (1 - std::cos(data.MET_phi-data.Muon[iMuTightNoIso[0]].phi)) );
      }
    }

    MT_lepTight2D = 9999;
    if (nLepTight2D==1) {
      MT_lepTight2D = sqrt( 2*tight_leptons_2D[0].Pt()*data.MET_pt * (1 - std::cos(data.MET_phi-tight_leptons_2D[0].Phi())) );
    } else if (nLepTight2D==2) {
      if (tight_leptons_2D[0].Pt()>tight_leptons_2D[1].Pt()) {
        MT_lepTight2D = sqrt( 2*tight_leptons_2D[0].Pt()*data.MET_pt * (1 - std::cos(data.MET_phi-tight_leptons_2D[0].Phi())) );
      } else {
        MT_lepTight2D = sqrt( 2*tight_leptons_2D[1].Pt()*data.MET_pt * (1 - std::cos(data.MET_phi-tight_leptons_2D[1].Phi())) );
      }
    }

    MT_vetolep = 9999;
    if (nLepVeto==1) {
      if (nEleVeto==1) {
        MT_vetolep = sqrt( 2*data.Electron[iEleVeto[0]].pt*data.MET_pt * (1 - std::cos(data.MET_phi-data.Electron[iEleVeto[0]].phi)) );
      } else if (nMuVeto==1) {
        MT_vetolep = sqrt( 2*data.Muon[iMuVeto[0]].pt*data.MET_pt * (1 - std::cos(data.MET_phi-data.Muon[iMuVeto[0]].phi)) );
      }
    }
    MT_allvetolep = 9999;
    vetoLepPt  = -9999;
    vetoLepPhi = -9999;
    vetoLepEta = -9999;
    if (nEleVeto+nMuVeto+nTauVeto==1) {
      if (nEleVeto==1) {
        vetoLepPt  = data.Electron[iEleVeto[0]].pt;
        vetoLepPhi = data.Electron[iEleVeto[0]].phi;
        vetoLepEta = data.Electron[iEleVeto[0]].eta;
      } else if (nMuVeto==1) {
        vetoLepPt  = data.Muon[iMuVeto[0]].pt;
        vetoLepPhi = data.Muon[iMuVeto[0]].phi;
        vetoLepEta = data.Muon[iMuVeto[0]].eta;
      } else if (nTauVeto==1) {
        vetoLepPt  = data.Tau[iTauVeto[0]].pt;
        vetoLepPhi = data.Tau[iTauVeto[0]].phi;
        vetoLepEta = data.Tau[iTauVeto[0]].eta;
      }
      MT_allvetolep = sqrt( 2*vetoLepPt*data.MET_pt * (1 - std::cos(data.MET_phi-vetoLepPhi)) );
    }
#if INC == 1
    tightLeppt  = -9999;
    tightLepPhi = -9999;
    tightLepEta = -9999;
    if (nEleTight+nMuTight==1) {
      if (nEleTight==1) {
        tightLeppt  = data.Electron[iEleTight[0]].pt;
        tightLepPhi = data.Electron[iEleTight[0]].phi;
        tightLepEta = data.Electron[iEleTight[0]].eta;
      } else if (nMuTight==1) {
        tightLeppt  = data.Muon[iMuTight[0]].pt;
        tightLepPhi = data.Muon[iMuTight[0]].phi;
        tightLepEta = data.Muon[iMuTight[0]].eta;
      }
    }
#endif
    // M_ll, dPhi_ll_met
    M_ll = -9999;
    dPhi_ll_met = 9999;
    if (nLepSelect==2) {
      TLorentzVector lep1, lep2;
      if (nEleSelect==2) {
        lep1.SetPtEtaPhiM(data.Electron[iEleSelect[0]].pt, data.Electron[iEleSelect[0]].eta, data.Electron[iEleSelect[0]].phi, data.Electron[iEleSelect[0]].mass);
        lep2.SetPtEtaPhiM(data.Electron[iEleSelect[1]].pt, data.Electron[iEleSelect[1]].eta, data.Electron[iEleSelect[1]].phi, data.Electron[iEleSelect[1]].mass);
        lep_pair = lep1+lep2;
        M_ll = lep_pair.M();
        dPhi_ll_met = std::abs(TVector2::Phi_mpi_pi(lep_pair.Phi() - data.MET_phi));
      } else if (nMuSelect==2) {
        lep1.SetPtEtaPhiM(data.Muon[iMuSelect[0]].pt, data.Muon[iMuSelect[0]].eta, data.Muon[iMuSelect[0]].phi, data.Muon[iMuSelect[0]].mass);
        lep2.SetPtEtaPhiM(data.Muon[iMuSelect[1]].pt, data.Muon[iMuSelect[1]].eta, data.Muon[iMuSelect[1]].phi, data.Muon[iMuSelect[1]].mass);
        lep_pair = lep1+lep2;
        M_ll = lep_pair.M();
        dPhi_ll_met = std::abs(TVector2::Phi_mpi_pi(lep_pair.Phi() - data.MET_phi));
      }
    }

    // inclusive

    M_ll_lepTight = -9999;
    dPhi_ll_met = 9999;
    if (nLepTight==2) {
      TLorentzVector lep1, lep2;
      if (nEleTight==2) {
        lep1.SetPtEtaPhiM(data.Electron[iEleTight[0]].pt, data.Electron[iEleTight[0]].eta, data.Electron[iEleTight[0]].phi, data.Electron[iEleTight[0]].mass);
        lep2.SetPtEtaPhiM(data.Electron[iEleTight[1]].pt, data.Electron[iEleTight[1]].eta, data.Electron[iEleTight[1]].phi, data.Electron[iEleTight[1]].mass);
        lep_pair = lep1+lep2;
        M_ll_lepTight = lep_pair.M();
        dPhi_ll_met = std::abs(TVector2::Phi_mpi_pi(lep_pair.Phi() - data.MET_phi));
      } else if (nMuTight==2) {
        lep1.SetPtEtaPhiM(data.Muon[iMuTight[0]].pt, data.Muon[iMuTight[0]].eta, data.Muon[iMuTight[0]].phi, data.Muon[iMuTight[0]].mass);
        lep2.SetPtEtaPhiM(data.Muon[iMuTight[1]].pt, data.Muon[iMuTight[1]].eta, data.Muon[iMuTight[1]].phi, data.Muon[iMuTight[1]].mass);
        lep_pair = lep1+lep2;
        M_ll_lepTight = lep_pair.M();
        dPhi_ll_met = std::abs(TVector2::Phi_mpi_pi(lep_pair.Phi() - data.MET_phi));
      }
    }

    if (debug) std::cout<<"AnalysisBase::calc_common_var: end init razor"<<std::endl;
  } // end if (syst_index==0)
  if (debug) std::cout<<"AnalysisBase::calc_common_var: end init"<<std::endl;
  
  // Count photons
  std::vector<TLorentzVector> photons_PreSelect, selected_photons;
  std::vector<TLorentzVector> faked_photons;
  iPhotonPreSelect   .clear();
  iPhotonSelect      .clear();
  iPhotonFake        .clear();
  itPhotonPreSelect  .assign(data.Photon.size(), (size_t)-1);
  itPhotonSelect     .assign(data.Photon.size(), (size_t)-1);
  itPhotonFake       .assign(data.Photon.size(), (size_t)-1);
  passPhotonPreSelect.assign(data.Photon.size(), 0);
  passPhotonSelect   .assign(data.Photon.size(), 0);
  //passPhotonPrompt   .assign(data.Photon.size(), 0);
  passPhotonFake     .assign(data.Photon.size(), 0);
  ChargedHadronIsoEACorr.clear();
  nPhotonPreSelect = nPhotonSelect = nPhotonFake = 0;
  for (size_t i=0; i<data.Photon.size(); ++i) {
    TLorentzVector pho_v4; pho_v4.SetPtEtaPhiM(data.Photon[i].pt, data.Photon[i].eta, data.Photon[i].phi, data.Photon[i].mass);
    float pt = data.Photon[i].pt;
    float abseta = std::abs(data.Photon[i].eta);
    bool ele_veto  = data.Photon[i].electronVeto;
    bool id_select = data.Photon[i].mvaID_WP80; // 80% is medium
    bool pixel_veto = data.Photon[i].pixelSeed;
    ChargedHadronIsoEACorr.push_back(data.Photon[i].pfRelIso03_chg);

    // Implementing cuts for Spring16 v2.2 Medium ID
    // https://twiki.cern.ch/twiki/bin/view/CMS/CutBasedPhotonIdentificationRun2?rev=36#Recommended_Working_points_for_2
    // Using the table, not the presentation, same as this VID cfg:
    // https://github.com/ikrav/cmssw/blob/65fa87654e6744efdff2e16d55a5b86bbdccd48d/RecoEgamma/PhotonIdentification/python/Identification/cutBasedPhotonID_Spring16_V2p2_cff.py#L50-L78
    // Exclude Sigma_ietaieta cut in order to be able to measure QCD background

    bool id_PreSel = false;
    if ( data.Photon[i].isScEtaEB){
      // Barrel cuts (EB)
      // TODO: update Photon ID, with Cut based bitmapo
      id_PreSel =
        data.Photon[i].hoe                          < 0.02197 ;//&&
      //data.Photon[i].sieie                   < 0.01015 &&
      //ChargedHadronIsoEACorr[i]                   < 1.141 &&
      //data.Photon[i].pfRelIso03_all - data.Photon[i].pfRelIso03_chg < 1.189+0.01512*pt+2.259e-05*pt*pt &&
      //data.Photon[i].pfRelIso03_all        < 2.08+0.004017*pt;
    } else {
      // Encap cuts (EE)
      id_PreSel =
        data.Photon[i].hoe                          < 0.0326 ;//&&
      //data.Photon[i].sieie                   < 0.0272 &&
      //ChargedHadronIsoEACorr[i]                   < 1.051 &&
      //data.Photon[i].pfRelIso03_all - data.Photon[i].pfRelIso03_chg < 2.718+0.0117*pt+2.3e-05*pt*pt &&
      //data.Photon[i].pfRelIso03_all < 3.867+0.0037*pt;
    }
    // Medium ID without Sigma_ietaieta cut
    if(( passPhotonPreSelect[i] =
         ( id_PreSel &&
           ele_veto &&
           pt        >= PHOTON_SELECT_PT_CUT &&
           abseta    <  PHOTON_SELECT_ETA_CUT ))) {
      iPhotonPreSelect.push_back(i);
      itPhotonPreSelect[i] = nPhotonPreSelect++;
      photons_PreSelect.push_back(pho_v4);
      // Fake photons (those that fail the SigmaIeteIeta cut)
      if(( passPhotonFake[i] =
           (data.Photon[i].sieie >= (data.Photon[i].isScEtaEB ? 0.01015 : 0.0272)))) {
        faked_photons.push_back(pho_v4);
        iPhotonFake.push_back(i);
        itPhotonFake[i] = nPhotonFake++;
      }
    }

    // Photons passing full ID
    if(( passPhotonSelect[i] =
         ( id_select &&
           ele_veto &&
           !pixel_veto &&
           pt        >= PHOTON_SELECT_PT_CUT &&
           abseta    <  PHOTON_SELECT_ETA_CUT ))) {
      selected_photons.push_back(pho_v4);
      iPhotonSelect.push_back(i);
      itPhotonSelect[i] = nPhotonSelect++;
    }
  }
  if (debug) std::cout<<"AnalysisBase::calc_common_var: end pho"<<std::endl;

  // Lepton/MET calculations

  // Add the lepton (pair) to MET
  TVector3 met_1l, met_1vl, met_ll;
  met_1l. SetPtEtaPhi(data.MET_pt, 0, data.MET_phi);
  met_1vl.SetPtEtaPhi(data.MET_pt, 0, data.MET_phi);
  met_ll. SetPtEtaPhi(data.MET_pt, 0, data.MET_phi);
  if (nLepSelect==1) {
    TVector3 lep_met;
    lep_met.SetPtEtaPhi(selected_leptons[0].Pt(), 0, selected_leptons[0].Phi());
    met_1l += lep_met;
  }
  if (nLepVeto==1) {
    TVector3 lep_met;
    lep_met.SetPtEtaPhi(veto_leptons[0].Pt(), 0, veto_leptons[0].Phi());
    met_1vl += lep_met;
  }
  if (M_ll!=-9999) {
    TVector3 lep_pair_met;
    lep_pair_met.SetPtEtaPhi(lep_pair.Pt(), 0, lep_pair.Phi());
    met_ll += lep_pair_met;
  }

  if (M_ll_lepTight!=-9999) {  // inclusive
    TVector3 lep_pair_met;
    lep_pair_met.SetPtEtaPhi(lep_pair.Pt(), 0, lep_pair.Phi());
    met_ll += lep_pair_met;
  }

  // Add the photon to MET
  TVector3 met_pho;
  met_pho.SetPtEtaPhi(data.MET_pt, 0, data.MET_phi);
  if (nPhotonSelect==1) {
    TVector3 pho_met;
    pho_met.SetPtEtaPhi(selected_photons[0].Pt(), 0, selected_photons[0].Phi());
    met_pho += pho_met;
  } else if (nPhotonPreSelect==1) {
    // Add also preselected photons
    TVector3 pho_met;
    pho_met.SetPtEtaPhi(photons_PreSelect[0].Pt(), 0, photons_PreSelect[0].Phi());
    met_pho += pho_met;
  }

  // Add the fake photon to MET
  TVector3 met_fakepho;
  met_fakepho.SetPtEtaPhi(data.MET_pt, 0, data.MET_phi);
  if (nPhotonFake==1) {
    TVector3 pho_met;
    pho_met.SetPtEtaPhi(faked_photons[0].Pt(), 0, faked_photons[0].Phi());
    met_fakepho += pho_met;
  }
  
  // Reconstruct the neutrino 4 momentum for single lepton events
  // https://twiki.cern.ch/twiki/bin/view/Main/TopPairProduction
  // https://github.com/BoostedScalefactors/WTopScalefactorProducer/blob/master/Skimmer/python/variables.py
  MET_eta = -9999;
  MET_pz  = -9999;
  if (nLepSelect==1) {
    double MET_px = data.MET_pt*std::cos(data.MET_phi);
    double MET_py = data.MET_pt*std::sin(data.MET_phi);
    double MET_pz = 0;
    double a = 80.379*80.379 - selected_leptons[0].M()*selected_leptons[0].M() + 2*selected_leptons[0].Px()*MET_px + 2*selected_leptons[0].Py()*MET_py;
    double A =  4 * (selected_leptons[0].E()*selected_leptons[0].E() - selected_leptons[0].Pz()*selected_leptons[0].Pz());
    double B = -4 * a * selected_leptons[0].Pz();
    double C =  4 * (selected_leptons[0].E()*selected_leptons[0].E()) * (MET_px*MET_px + MET_py*MET_py) - a*a;
    double D = B*B - 4*A*C;
    // If there are real solutions, use the one with lowest pz                                            
    if (D>=0) {
      double s1 = (-B+std::sqrt(D))/(2*A);
      double s2 = (-B-std::sqrt(D))/(2*A);
      if (std::abs(s1)<std::abs(s2)) {
        MET_pz = s1;
      } else {
        MET_pz = s2;
      }
    } else {
      MET_pz = -B/(2*A);
    }
    MET_eta = TVector3(MET_px, MET_py, MET_pz).PseudoRapidity();
  }

  if (debug) std::cout<<"AnalysisBase::calc_common_var: end met+lep/pho"<<std::endl;
  // Rest of the vairables need to be recalculated each time the jet energy is changed
  // eg. Jet selection, W/top tags, HT (obviously), etc. that depends on jet pt

  // AK4 jets
  iJet          .clear();
  iJetNoLep     .clear();
  iLooseBTag    .clear();
  iMediumBTag   .clear();
  iTightBTag    .clear();
  itJet              .assign(data.Jet.size(), (size_t)-1);
  itJetNoLep         .assign(data.Jet.size(), (size_t)-1);
  itLooseBTag        .assign(data.Jet.size(), (size_t)-1);
  itMediumBTag       .assign(data.Jet.size(), (size_t)-1);
  itTightBTag        .assign(data.Jet.size(), (size_t)-1);
  passLooseJet       .assign(data.Jet.size(), 0);
  passLooseJetNoLep  .assign(data.Jet.size(), 0);
  passLooseJetNoPho  .assign(data.Jet.size(), 0);
  passLooseBTag      .assign(data.Jet.size(), 0);
  passMediumBTag     .assign(data.Jet.size(), 0);
  passTightBTag      .assign(data.Jet.size(), 0);
  passLooseIsoBTag   .assign(data.Jet.size(), 0);
  passMediumIsoBTag  .assign(data.Jet.size(), 0);
  AK4_photonDR       .assign(data.Jet.size(), 9999);
  AK4_photonPtRatio  .assign(data.Jet.size(), 0);
  AK4_eleDR          .assign(data.Jet.size(), 9999);
  AK4_elePtRatio     .assign(data.Jet.size(), 0);
  AK4_muonDR         .assign(data.Jet.size(), 9999);
  AK4_muonPtRatio    .assign(data.Jet.size(), 0);
  nJet = nJetNoLep = nJetNoPho = 0;
  nLooseBTag  = 0;
  nMediumBTag = nMediumBTagNoPho = 0;
  nTightBTag  = 0;
  nLooseIsoBTag  = 0;
  nMediumIsoBTag = 0;
  AK4_Ht = AK4_HtOnline = AK4_HtNoLep = 0;
  minDeltaPhi = minDeltaPhi_1l = minDeltaPhi_1vl = minDeltaPhi_ll = minDeltaPhi_pho = dPhi_ll_jet = 9999;
  for(size_t i=0; i<data.Jet.size(); ++i) {
    if (debug>1) std::cout<<"AnalysisBase::calc_common_var: AK4 "<<i<<" start"<<std::endl;
    TLorentzVector jet_v4; jet_v4.SetPtEtaPhiM(data.Jet[i].pt, data.Jet[i].eta, data.Jet[i].phi, data.Jet[i].mass);
    // Jet ID
    if (( passLooseJet[i] =
          ( (data.Jet[i].jetId == 2 || data.Jet[i].jetId == 6 )&&
            data.Jet[i].pt         >= JET_AK4_PT_CUT &&
            //data.Jet[i].chHEF > 0.05 && data.Jet[i].neHEF < 0.8 && data.Jet[i].neEmEF < 0.7 &&
            std::abs(data.Jet[i].eta)  <  JET_AK4_ETA_CUT ))) {

      if (debug>1) std::cout<<"AnalysisBase::calc_common_var: AK4 "<<i<<" id ok"<<std::endl;
      iJet.push_back(i);
      itJet[i] = nJet++;
      selected_jets.push_back(jet_v4);
      AK4_Ht += data.Jet[i].pt;

      // B tagging
      if (( passLooseBTag[i] = data.Jet[i].btagDeepB >= B_CSV_LOOSE_CUT )) {
        iLooseBTag.push_back(i);
        itLooseBTag[i] = nLooseBTag++;
      }
      if (( passMediumBTag[i] = data.Jet[i].btagDeepB >= B_CSV_MEDIUM_CUT )) {
        iMediumBTag.push_back(i);
        itMediumBTag[i] = nMediumBTag++;
        selected_bs.push_back(jet_v4);
      }
      if (( passTightBTag[i]  = data.Jet[i].btagDeepB >= B_CSV_TIGHT_CUT )) {
        iTightBTag.push_back(i);
        itTightBTag[i] = nTightBTag++;
      }
      if (debug>1) std::cout<<"AnalysisBase::calc_common_var: AK4 "<<i<<" b-tagging ok"<<std::endl;
      
      // Lepton-jet overlap
      for (const auto& veto_electron : veto_electrons) {
        double dR = veto_electron.DeltaR(jet_v4);
        if (dR<AK4_eleDR[i]) {
          AK4_eleDR[i] = dR;
          AK4_elePtRatio[i] = veto_electron.Pt()/jet_v4.Pt();
        }
      }
      for (const auto& veto_muon : veto_muons) {
        double dR = veto_muon.DeltaR(jet_v4);
        if (dR<AK4_muonDR[i]) {
          AK4_muonDR[i] = dR;
          AK4_muonPtRatio[i] = veto_muon.Pt()/jet_v4.Pt();
        }
      }
      // Exclude jets that have tight leptons in the isolation cone for the DeltaPhi calculation
      double mindR = 9999;
      double r_iso = -9999;
      for (size_t j=0, n=tight_leptons.size(); j<n; ++j) {
        double dR = tight_leptons[j].DeltaR(jet_v4);
        if (dR<mindR) {
          mindR=dR;
          r_iso = r_iso_tight_leptons[j];
        }
      }
      if ((passLooseJetNoLep[i] = (mindR>=r_iso))) {
        iJetNoLep.push_back(i);
        itJetNoLep[i] = nJetNoLep++;
        AK4_HtNoLep += data.Jet[i].pt;
      }
      if (debug>1) std::cout<<"AnalysisBase::calc_common_var: AK4 "<<i<<" lepton-overlap ok"<<std::endl;
      // Photon-jet overlap
      for (size_t j=0; j<selected_photons.size(); ++j) {
        double dR = selected_photons[j].DeltaR(jet_v4);
        if (dR<AK4_photonDR[i]) {
          AK4_photonDR[i] = dR;
          AK4_photonPtRatio[i] = selected_photons[j].Pt()/jet_v4.Pt();
          //jMatch = j;
        }
      }
      // Exclude jets that have overlapping photon
      if (nPhotonSelect==1) {
        if ((passLooseJetNoPho[i] = (data.Photon[iPhotonSelect[0]].jetIdx==i))) {
          nJetNoPho++;
          if (data.Jet[i].btagDeepB >= B_CSV_MEDIUM_CUT) nMediumBTagNoPho++;
        }
      } else if (nPhotonPreSelect==1) {
        if ((passLooseJetNoPho[i] = (data.Photon[iPhotonPreSelect[0]].jetIdx==i))) {
          nJetNoPho++;
          if (data.Jet[i].btagDeepB >= B_CSV_MEDIUM_CUT) nMediumBTagNoPho++;
        }
      }
      if (debug>1) std::cout<<"AnalysisBase::calc_common_var: AK4 "<<i<<" photon-overlap ok"<<std::endl;

      // minDeltaPhi
      if (nJet<=4) {
        double dphi = std::abs(TVector2::Phi_mpi_pi(data.MET_phi - data.Jet[i].phi));
        if (dphi<minDeltaPhi) minDeltaPhi = dphi;
        // with added (veto) lepton
        double dphi_met1l = std::abs(TVector2::Phi_mpi_pi(met_1l.Phi() - data.Jet[i].phi));
        if (dphi_met1l<minDeltaPhi_1l) minDeltaPhi_1l = dphi_met1l;
        double dphi_met1vl = std::abs(TVector2::Phi_mpi_pi(met_1vl.Phi() - data.Jet[i].phi));
        if (dphi_met1vl<minDeltaPhi_1vl) minDeltaPhi_1vl = dphi_met1vl;
        // with added lepton pair
        double dphi_metll = std::abs(TVector2::Phi_mpi_pi(met_ll.Phi() - data.Jet[i].phi));
        if (dphi_metll<minDeltaPhi_ll) minDeltaPhi_ll = dphi_metll;
        // with added photon
        double dphi_metpho = std::abs(TVector2::Phi_mpi_pi(met_pho.Phi() - data.Jet[i].phi));
        if (dphi_metpho<minDeltaPhi_pho) minDeltaPhi_pho = dphi_metpho;
        // jet lep-pair angle
        if (M_ll!=-9999) {
          double dphi_ll = std::abs(TVector2::Phi_mpi_pi(lep_pair.Phi() - data.Jet[i].phi));
          if (dphi_ll<dPhi_ll_jet) dPhi_ll_jet = dphi_ll;
        }
        if (M_ll_lepTight!=-9999) { // inclusive
          double dphi_ll = std::abs(TVector2::Phi_mpi_pi(lep_pair.Phi() - data.Jet[i].phi));
          if (dphi_ll<dPhi_ll_jet) dPhi_ll_jet = dphi_ll;
        }
      }
      if (debug>1) std::cout<<"AnalysisBase::calc_common_var: AK4 "<<i<<" min dphi ok"<<std::endl;

    } // End Jet Selection

    // Online jet selection for HT (+ testing Additional Loose Jet ID)
    if ( //data.Jet[i].looseJetpdgId == 1 &&
        data.Jet[i].pt         >  40 &&
        std::abs(data.Jet[i].eta)  <  3.0 ) {
      AK4_HtOnline += data.Jet[i].pt;

    }
      if (debug>1) std::cout<<"AnalysisBase::calc_common_var: AK4 "<<i<<" end"<<std::endl;
  } // End AK4 Jet Loop
  if (debug) std::cout<<"AnalysisBase::calc_common_var: end AK4"<<std::endl;

  // Selected jets may vary with systematics, so lepton/photon-jet matching might be needed a 2nd time
  // Nearest jet to lepton
  eleJetDR     .assign(data.Electron.size(),  9999);
  eleJetDPhi   .assign(data.Electron.size(),  9999);
  eleJetPt     .assign(data.Electron.size(), -9999);
  for (size_t i=0; i<data.Electron.size(); ++i) {
    TLorentzVector ele_v4; ele_v4.SetPtEtaPhiM(data.Electron[i].pt, data.Electron[i].eta, data.Electron[i].phi, data.Electron[i].mass);
    for (const auto& jet : selected_jets) {
      double dR = ele_v4.DeltaR(jet);
      if (dR<eleJetDR[i]) {
        eleJetDR[i] = dR;
        eleJetPt[i] = jet.Pt();
      }
      double dPhi = std::abs(ele_v4.DeltaPhi(jet));
      if (dPhi<eleJetDPhi[i]) eleJetDPhi[i] = dPhi;
    }
  }
  muJetDR     .assign(data.Muon.size(),  9999);
  muJetDPhi   .assign(data.Muon.size(),  9999);
  muJetPt     .assign(data.Muon.size(), -9999);
  for (size_t i=0; i<data.Muon.size(); ++i) {
    TLorentzVector mu_v4; mu_v4.SetPtEtaPhiM(data.Muon[i].pt, data.Muon[i].eta, data.Muon[i].phi, data.Muon[i].mass);
    for (const auto& jet : selected_jets) {
      double dR = mu_v4.DeltaR(jet);
      if (dR<muJetDR[i]) {
        muJetDR[i] = dR;
        muJetPt[i] = jet.Pt();
      }
      double dPhi = std::abs(mu_v4.DeltaPhi(jet));
      if (dPhi<muJetDPhi[i]) muJetDPhi[i] = dPhi;
    }
  }
  // Match non isolated tight lepton to nearest AK4 jet to be able to tell which Razor megajet it belongs
  for (size_t i=0; i<tight_leptons_noiso.size(); ++i) {
    bool match = false;
    if (iJetLepTightNoIso[i]==-1) match = true;
    else if (!passLooseJet[iJetLepTightNoIso[i]]) match = true;
    if (match) {
      double mindR = 9999;
      for(size_t j=0; j<selected_jets.size(); ++j) {
        double dR = tight_leptons_noiso[i].DeltaR(selected_jets[j]);
        if (dR<mindR) {
          mindR = dR;
          iJetLepTightNoIso[i] = iJet[j];
        }
      }
    }
  }
  for (size_t i=0; i<tight_leptons_2D.size(); ++i) {
    bool match = false;
    if (iJetLepTight2D[i]==-1) match = true;
    else if (!passLooseJet[iJetLepTight2D[i]]) match = true;
    if (match) {
      double mindR = 9999;
      for(size_t j=0; j<selected_jets.size(); ++j) {
        double dR = tight_leptons_2D[i].DeltaR(selected_jets[j]);
        if (dR<mindR) {
          mindR = dR;
          iJetLepTight2D[i] = iJet[j];
        }
      }
    }
  }

  if (debug) std::cout<<"AnalysisBase::calc_common_var: end AK4-lep matching"<<std::endl;

  // AK8 jets
  iJetAK8          .clear();
  iWMassTag        .clear();
  iBoostMassTag    .clear();
  iBoostMassBTag   .clear();
  iLooseWTag       .clear();
  iTightWTag       .clear();
  TightWTag        .clear();
  iTightWAntiTag   .clear();
  iHadTopMassTag   .clear();
  iHadTop1BMassTag .clear();
  iHadTopTag       .clear();
  iHadTop0BMassTag .clear();
  iHadTop0BAntiTag .clear();
  softDropMassW    .clear();
  softDropMassTop  .clear();
  iHadW            .clear();
  iHadZ            .clear();
  iHadV            .clear();
  iHadH            .clear();
  iHadTop          .clear();
  iLepJetCand      .clear();
  iLepJet          .clear();
  iLepTop          .clear();
  iLepJetHighMass  .clear();
  iLepTopHighMass  .clear();
  itJetAK8             .assign(data.FatJet.size(), (size_t)-1);
  itWMassTag           .assign(data.FatJet.size(), (size_t)-1);
  itBoostMassTag       .assign(data.FatJet.size(), (size_t)-1);
  itBoostMassBTag      .assign(data.FatJet.size(), (size_t)-1);
  itLooseWTag          .assign(data.FatJet.size(), (size_t)-1);
  itTightWTag          .assign(data.FatJet.size(), (size_t)-1);
  itTightWAntiTag      .assign(data.FatJet.size(), (size_t)-1);
  itHadTopMassTag      .assign(data.FatJet.size(), (size_t)-1);
  itHadTop1BMassTag    .assign(data.FatJet.size(), (size_t)-1);
  itHadTopTag          .assign(data.FatJet.size(), (size_t)-1);
  itHadTop0BMassTag    .assign(data.FatJet.size(), (size_t)-1);
  itHadTop0BAntiTag    .assign(data.FatJet.size(), (size_t)-1);
  itHadW               .assign(data.FatJet.size(), (size_t)-1);
  itHadZ               .assign(data.FatJet.size(), (size_t)-1);
  itHadV               .assign(data.FatJet.size(), (size_t)-1);
  itHadH               .assign(data.FatJet.size(), (size_t)-1);
  itHadTop             .assign(data.FatJet.size(), (size_t)-1);
  itLepJetCand         .assign(data.FatJet.size(), (size_t)-1);
  itLepJet             .assign(data.FatJet.size(), (size_t)-1);
  itLepTop             .assign(data.FatJet.size(), (size_t)-1);
  itLepJetHighMass     .assign(data.FatJet.size(), (size_t)-1);
  itLepTopHighMass     .assign(data.FatJet.size(), (size_t)-1);
  passLooseJetAK8      .assign(data.FatJet.size(), 0);
  passWMassTag         .assign(data.FatJet.size(), 0);
  passBoostMassTag     .assign(data.FatJet.size(), 0);
  passBoostMassBTag    .assign(data.FatJet.size(), 0);
  passLooseWTag        .assign(data.FatJet.size(), 0);
  passTightWTag        .assign(data.FatJet.size(), 0);
  passTightWAntiTag    .assign(data.FatJet.size(), 0);
  passHadTopTag        .assign(data.FatJet.size(), 0);
  passHadTopMassTag    .assign(data.FatJet.size(), 0);
  passHadTop1BMassTag  .assign(data.FatJet.size(), 0);
  passHadTop0BMassTag  .assign(data.FatJet.size(), 0);
  passHadTop0BAntiTag  .assign(data.FatJet.size(), 0);
  passHadW             .assign(data.FatJet.size(), 0);
  passHadZ             .assign(data.FatJet.size(), 0);
  passHadV             .assign(data.FatJet.size(), 0);
  passHadH             .assign(data.FatJet.size(), 0);
  passHadTop           .assign(data.FatJet.size(), 0);
  passLepJetCand       .assign(data.FatJet.size(), 0);
  passLepJet           .assign(data.FatJet.size(), 0);
  passLepJetNoIso      .assign(data.FatJet.size(), 0);
  passLepJetNoPt       .assign(data.FatJet.size(), 0);
  passLepTop           .assign(data.FatJet.size(), 0);
  passLepJetHighMass   .assign(data.FatJet.size(), 0);
  passLepTopHighMass   .assign(data.FatJet.size(), 0);
  passLepTopNoIso      .assign(data.FatJet.size(), 0);
  passLepTopNoPt       .assign(data.FatJet.size(), 0);
  passLepTopNoMass     .assign(data.FatJet.size(), 0);
  passLepTopNoSubJetB  .assign(data.FatJet.size(), 0);
  passOtherWMassTag       .assign(data.FatJet.size(), 0);
  passOtherTightWTag      .assign(data.FatJet.size(), 0);
  passOtherTightWAntiTag  .assign(data.FatJet.size(), 0);
  passOtherHadTopTag      .assign(data.FatJet.size(), 0);
  passOtherHadTopMassTag  .assign(data.FatJet.size(), 0);
  passOtherHadTop0BMassTag.assign(data.FatJet.size(), 0);
  passOtherHadTop0BAntiTag.assign(data.FatJet.size(), 0);
  AK8_photonDR         .assign(data.FatJet.size(), 9999);
  AK8_photonPtRatio    .assign(data.FatJet.size(), 0);
  AK8_eleDR            .assign(data.FatJet.size(), 9999);
  AK8_elePtRatio       .assign(data.FatJet.size(), 0);
  AK8_muonDR           .assign(data.FatJet.size(), 9999);
  AK8_muonPtRatio      .assign(data.FatJet.size(), 0);
  AK8_E                .assign(data.FatJet.size(), -9999);
  AK8_LSF              .assign(data.FatJet.size(), -9999);
  AK8_LSF_NoIso        .assign(data.FatJet.size(), -9999);
  ak8MatchedTightNoIsoLepCleanJetDRmin.assign(data.FatJet.size(), -9999);
  ak8MatchedTightNoIsoLepCleanJetPtrel.assign(data.FatJet.size(), -9999);
  ak8MatchedGenLeptonMotherID.assign(data.FatJet.size(), -9999);
  nJetAK8          = 0;
  nJetAK8mass      = 0;
  nWMassTag        = 0;
  nBoostMassTag    = 0;
  nBoostMassBTag   = 0;
  nLooseWTag       = 0;
  nTightWTag       = 0;
  nHadWTag1        = 0;
  nHadWTag3        = 0;
  nTightWAntiTag   = 0;
  nSubJetBTag      = 0;
  nHadTopMassTag   = 0;
  nHadTop1BMassTag = 0;
  nHadTopTag       = 0;
  nHadTopTag2      = 0;
  nHadTopTag3      = 0;
  nHadTopTag4      = 0;
  nHadTop0BMassTag = 0;
  nHadTop0BAntiTag = 0;
  AK8_Ht   = 0;
  minDeltaR_W_b = 9999;
  nW1         = nW2         = nW3 = 0;
  nWDeepMD1   = nWDeepMD2   = nWDeepMD3 = 0;
  nWDeep1     = nWDeep2     = nWDeep3 = 0;
  nZDeepMD1   = nZDeepMD2   = nZDeepMD3 = 0;
  nZDeep1     = nZDeep2     = nZDeep3 = 0;
  nVDeep1     = nVDeep2     = nVDeep3 = 0;
  nHDeepMD1   = nHDeepMD2   = nHDeepMD3 = 0;
  nHDeep1     = nHDeep2     = nHDeep3 = 0;
  nTop1       = nTop2       = nTop3       = nTop4 = nTop5 = 0;
  nTopDeepMD1 = nTopDeepMD2 = nTopDeepMD3 = nTopDeepMD4 = 0;
  nTopDeep1   = nTopDeep2   = nTopDeep3   = nTopDeep4 = 0;
  nHadW       = 0;
  nHadZ       = 0;
  nHadV       = 0;
  nHadH       = 0;
  nHadTop     = 0;
  nLepJetCand       = 0;
  nLepJet           = 0;
  nLepTop           = 0;
  nLepJetHighMass   = 0;
  nLepTopHighMass   = 0;
  dPhiBoostedJetMET    = 9999;
  dPhiBoostedJetLep    = 9999;
  dPhiBoostedJetLepMET = 9999;
  double maxpt = 0;
  for (size_t i=0; i<data.FatJet.size(); ++i) {
    if (debug>1) std::cout<<"AnalysisBase::calc_common_var: AK8 "<<i<<" start"<<std::endl;
    TLorentzVector AK8_v4; AK8_v4.SetPtEtaPhiM(data.FatJet[i].pt, data.FatJet[i].eta, data.FatJet[i].phi, data.FatJet[i].mass);

    //double isData ? sd_mass_w   = data.FatJet[i].msoftdrop : softDropMassCorr[i];
    double sd_mass_w   = data.FatJet[i].msoftdrop;
    double sd_mass_top = data.FatJet[i].msoftdrop;
    AK8_E[i] = AK8_v4.E();

    softDropMassW   .push_back(sd_mass_w);
    softDropMassTop .push_back(sd_mass_top);

    if (debug>1) std::cout<<"AnalysisBase::calc_common_var: AK8 "<<i<<" mass ok"<<std::endl;

    // Jet ID
    if (( passLooseJetAK8[i] =
          ( (data.FatJet[i].jetId == 2 || data.FatJet[i].jetId == 6)&&
            data.FatJet[i].pt         >= JET_AK8_PT_CUT &&
            std::abs(data.FatJet[i].eta)  <  JET_AK8_ETA_CUT ))) {

      if (debug>1) std::cout<<"AnalysisBase::calc_common_var: AK8 "<<i<<" id ok"<<std::endl;
      // Photon jet veto (not applied):
      // - Calculate dR and pt ratio of photons overlapping with the jet
      // - Remove jet if dR<0.8
      for (size_t j=0; j<selected_photons.size(); ++j) {
        double dR = selected_photons[j].DeltaR(AK8_v4);
        if (dR<AK8_photonDR[i]) {
          AK8_photonDR[i] = dR;
          AK8_photonPtRatio[i] = selected_photons[j].Pt()/AK8_v4.Pt();
        }
      }
      //if ( passLooseJetAK8[i] = (AK8_photonDR[i]>=0.8) ) {
      iJetAK8.push_back(i);
      itJetAK8[i] = nJetAK8++;
      if(sd_mass_w >= W_SD_MASS_CUT_LOW) nJetAK8mass++;
      
      // Lepton-jet overlap
      for (size_t j=0; j<veto_electrons.size(); ++j) {
        double dR = veto_electrons[j].DeltaR(AK8_v4);
        if (dR<AK8_eleDR[i]) {
          AK8_eleDR[i] = dR;
          AK8_elePtRatio[i] = veto_electrons[j].Pt()/AK8_v4.Pt();
        }
      }
      for (size_t j=0; j<veto_muons.size(); ++j) {
        double dR = veto_muons[j].DeltaR(AK8_v4);
        if (dR<AK8_muonDR[i]) {
          AK8_muonDR[i] = dR;
          AK8_muonPtRatio[i] = veto_muons[j].Pt()/AK8_v4.Pt();
        }
      }
      // Calculate LSF for tight leptons
      bool ak8MatchLepTight2D = false;
      double lepSubJetDR = 9999;
      for (size_t j=0; j<tight_leptons_2D.size(); ++j) {
        TLorentzVector subjet_v4 = AK8_v4;
        double DR = tight_leptons_2D[j].DeltaR(subjet_v4);
        if (DR<0.8 && DR<lepSubJetDR) {
          ak8MatchLepTight2D = true;
          lepSubJetDR = DR;
          AK8_LSF[i] = std::min(tight_leptons_2D[j].Pt() / subjet_v4.Pt(), 0.999999);
          for (const int& iSubJet : { data.FatJet[i].subJetIdx1, data.FatJet[i].subJetIdx2 }) if (iSubJet!=-1) {
            subjet_v4.SetPtEtaPhiM(data.SubJet[j].pt, data.SubJet[j].eta, data.SubJet[j].phi, data.SubJet[j].mass);
            DR = tight_leptons_2D[j].DeltaR(subjet_v4);
            if (DR<lepSubJetDR) {
              lepSubJetDR = DR;
              AK8_LSF[i] = std::min(tight_leptons_2D[j].Pt() / subjet_v4.Pt(), 0.999999);
            }
          }
        }
      }
      // Same with lepton without isolation
      bool ak8MatchLepTightNoIso = false;
      size_t iMatchLepTightNoIso = -1;
      lepSubJetDR = 9999;
      for (size_t j=0; j<tight_leptons_noiso.size(); ++j) {
        TLorentzVector subjet_v4 = AK8_v4;
        double DR = tight_leptons_noiso[j].DeltaR(subjet_v4);
        if (DR<0.8 && DR<lepSubJetDR) {
          ak8MatchLepTightNoIso = true;
          lepSubJetDR = DR;
          AK8_LSF_NoIso[i] = std::min(tight_leptons_noiso[j].Pt() / subjet_v4.Pt(), 0.999999);
          for (const int& iSubJet : { data.FatJet[i].subJetIdx1, data.FatJet[i].subJetIdx2 }) if (iSubJet!=-1) {
            subjet_v4.SetPtEtaPhiM(data.SubJet[j].pt, data.SubJet[j].eta, data.SubJet[j].phi, data.SubJet[j].mass);
            DR = tight_leptons_noiso[j].DeltaR(subjet_v4);
            if (DR<lepSubJetDR) {
              lepSubJetDR = DR;
              AK8_LSF_NoIso[i] = std::min(tight_leptons_noiso[j].Pt() / subjet_v4.Pt(), 0.999999);
              iMatchLepTightNoIso = j;
            }
          }
        }
      }
      if (iMatchLepTightNoIso != (size_t)-1) {
        ak8MatchedTightNoIsoLepCleanJetDRmin[i] = tightNoIsoLepCleanJetDRmin[iMatchLepTightNoIso];
        ak8MatchedTightNoIsoLepCleanJetPtrel[i] = tightNoIsoLepCleanJetPtrel[iMatchLepTightNoIso];
      }

      if (debug>1) std::cout<<"AnalysisBase::calc_common_var: AK8 "<<i<<" overlap ok"<<std::endl;
      
      // Tagging Variables
      double tau_21     = tau21[i];
      double tau_32     = tau32[i];
      double pt         = data.FatJet[i].pt;
      double abseta     = data.FatJet[i].eta;
      double deepMD_w   = data.FatJet[i].deepTagMD_WvsQCD;
      double deepMD_z   = data.FatJet[i].deepTagMD_ZvsQCD;
      double deepMD_h   = data.FatJet[i].deepTagMD_HbbvsQCD;
      double deepMD_top = data.FatJet[i].deepTagMD_TvsQCD;
      double deep_w     = data.FatJet[i].deepTag_WvsQCD;
      double deep_z     = data.FatJet[i].deepTag_ZvsQCD;
      //double deep_h     = data.FatJet[i].deepTag_H; // Only in v5 NanoAOD
      double deep_top   = data.FatJet[i].deepTag_TvsQCD;
      double sd_mass    = data.FatJet[i].msoftdrop;
      
      // _______________________________________________________
      //                   Hadronic W Tag definition
      
      if((passBoostMassTag[i] = (
                                 data.FatJet[i].msoftdrop >= 50
                                 ))) {
        iBoostMassTag.push_back(i);
        itBoostMassTag[i] = nBoostMassTag++;
      }
      if((passBoostMassBTag[i] = (
                                  passSubJetBTag[i] &&
                                  data.FatJet[i].msoftdrop >= 50
                                  ))) {
        iBoostMassBTag.push_back(i);
        itBoostMassBTag[i] = nBoostMassBTag++;
      }

      if ((passWMassTag[i] =
           ( pt        >= W_PT_CUT &&
             abseta    <  W_ETA_CUT &&
             sd_mass   >= W_SD_MASS_CUT_LOW &&
             sd_mass   <  W_SD_MASS_CUT_HIGH))) {
        iWMassTag.push_back(i);
        itWMassTag[i] = nWMassTag++;
        // Loose/Tight W Tag Working points
        if ((passLooseWTag[i] = (tau_21 < W_TAU21_LOOSE_CUT))) {
          iLooseWTag.push_back(i);
          itLooseWTag[i] = nLooseWTag++;
        }
        if (tau_21 < 0.35) nHadWTag1++;
        if (tau_21 < 0.55) nHadWTag3++;
        if ((passTightWTag[i] = (tau_21 < W_TAU21_TIGHT_CUT))) {
        //if ((passTightWTag[i] = (data.FatJet[i].deepTagMD_WvsQCD > 0.884 ))) {
          iTightWTag.push_back(i);
          itTightWTag[i] = nTightWTag++;
          TightWTag.push_back(AK8_v4);
          // dR between W and b
          for(size_t j=0; j<data.Jet.size(); ++j) {
            TLorentzVector AK4_v4; AK4_v4.SetPtEtaPhiM(data.Jet[j].pt, data.Jet[j].eta, data.Jet[j].phi, data.Jet[j].mass);
            if (passMediumBTag[j]) {
              double dR = AK4_v4.DeltaR(AK8_v4);
              if (dR<minDeltaR_W_b) minDeltaR_W_b = dR;
            }
          }
        } else {
          passTightWAntiTag[i] = 1;
          iTightWAntiTag.push_back(i);
          itTightWAntiTag[i] = nTightWAntiTag++;
        }
      }
      // Same without mass smearing
      if ((passOtherWMassTag[i] =
           ( pt        >= W_PT_CUT &&
             abseta    <  W_ETA_CUT &&
             sd_mass   >= W_SD_MASS_CUT_LOW &&
             sd_mass   <  W_SD_MASS_CUT_HIGH))) {
        passOtherTightWTag[i] = (tau_21 < W_TAU21_TIGHT_CUT);
        passOtherTightWAntiTag[i] = !passOtherTightWTag[i];
      }
      if (debug>1) std::cout<<"AnalysisBase::calc_common_var: AK8 "<<i<<" wtag ok"<<std::endl;

      // _______________________________________________________
      //                  Hadronic Top Tag definition

      minDeltaR_W_b = 9999;
      if ((passHadTopMassTag[i] =
           ( pt          >= HADTOP_PT_CUT &&
             abseta      <  HADTOP_ETA_CUT &&
             sd_mass     >= HADTOP_SD_MASS_CUT_LOW &&
             sd_mass     <  HADTOP_SD_MASS_CUT_HIGH))) {
        itHadTopMassTag[i] = nHadTopMassTag++;
        iHadTopMassTag.push_back(i);
        if ((passHadTop1BMassTag[i] = passSubJetBTag[i])) {
          itHadTop1BMassTag[i] = nHadTop1BMassTag++;
          iHadTop1BMassTag.push_back(i);
          //if ((passHadTopTag[i] = (tau_32 < HADTOP_TAU32_CUT))) {
          if ((passHadTopTag[i] = (data.FatJet[i].deepTagMD_WvsQCD > 0.578))) {
            itHadTopTag[i] = nHadTopTag++;
            iHadTopTag.push_back(i);
          }
          if (tau_32 < 0.54) nHadTopTag2++;
          if (tau_32 < 0.65) nHadTopTag3++;
          if (tau_32 < 0.80) nHadTopTag4++;
        } else {
          for(size_t j=0; j<data.Jet.size(); ++j) {
            TLorentzVector AK4_v4; AK4_v4.SetPtEtaPhiM(data.Jet[j].pt, data.Jet[j].eta, data.Jet[j].phi, data.Jet[j].mass);
            if (passMediumBTag[j]) {
              double dR = AK4_v4.DeltaR(AK8_v4);
              if (dR<minDeltaR_W_b) minDeltaR_W_b = dR;
            }
          }
          //if(minDeltaR_W_b > 0.8) {
          passHadTop0BMassTag[i] = 1;
          itHadTop0BMassTag[i] = nHadTop0BMassTag++;
          iHadTop0BMassTag.push_back(i);
          //}
          if ((passHadTop0BAntiTag[i] = (tau_32 >= HADTOP_TAU32_CUT))) {
            itHadTop0BAntiTag[i] = nHadTop0BAntiTag++;
            iHadTop0BAntiTag.push_back(i);
          }
        }
      }
      // Other top mass correction
      minDeltaR_W_b = 9999;
      if ((passOtherHadTopMassTag[i] =
           ( pt          >= HADTOP_PT_CUT &&
             sd_mass     >= HADTOP_SD_MASS_CUT_LOW &&
             sd_mass     <  HADTOP_SD_MASS_CUT_HIGH))) {
        if (passSubJetBTag[i]) {
          passOtherHadTopTag[i] = (tau_32 < HADTOP_TAU32_CUT);
        } else {
          for(size_t j=0; j<data.Jet.size(); ++j) {
            TLorentzVector AK4_v4; AK4_v4.SetPtEtaPhiM(data.Jet[j].pt, data.Jet[j].eta, data.Jet[j].phi, data.Jet[j].mass);
            if (passMediumBTag[j]) {
              double dR = AK4_v4.DeltaR(AK8_v4);
              if (dR<minDeltaR_W_b) minDeltaR_W_b = dR;
            }
          }
          if(minDeltaR_W_b > 0.8) {
            passOtherHadTop0BMassTag[i] = minDeltaR_W_b > 0.8;
            passOtherHadTop0BAntiTag[i] = (tau_32 >= HADTOP_TAU32_CUT);
          }
        }
      }

      if (debug>1) std::cout<<"AnalysisBase::calc_common_var: AK8 "<<i<<" top tag ok"<<std::endl;
      // New and old tagger WPs
      // WPs from slide 4 in (2017 values)
      // https://indico.cern.ch/event/840827/contributions/3527925/attachments/1895214/3126510/DeepAK8_Top_W_SFs_2017_JMAR_PK.pdf
      // Hadronic W tagging
      bool passHadW1 = false, passHadW2 = false, passHadW3 = false;
      if (passWMassTag[i]) {
        if (tau21[i] < 0.55) nW1++;
        if (tau21[i] < 0.45) nW2++;
        if (tau21[i] < 0.35) nW3++;
        if (deepMD_w > 0.313) nWDeepMD1++;
        if (deepMD_w > 0.802) nWDeepMD2++;
        if (deepMD_w > 0.884) nWDeepMD3++;
      }
      if (pt        >= W_PT_CUT &&
          abseta    <  W_ETA_CUT) {
        if (( passHadW1 = deep_w > 0.779 )) nWDeep1++;
        if (( passHadW2 = deep_w > 0.981 )) nWDeep2++;
        if (( passHadW3 = deep_w > 0.991 )) nWDeep3++;
      }
      if (debug>1) std::cout<<"AnalysisBase::calc_common_var: AK8 "<<i<<" new W tag ok"<<std::endl;
      // Hadronic Z Tagging
      // Use some ad-hoc working points now (unknown mistag rate)
      // TODO: Check again with signal
      bool passHadZ1 = false, passHadZ2 = false, passHadZ3 = false;
      if (pt >= 200 &&
          abseta    <  2.4) {
        if (sd_mass >= 70 &&
            sd_mass <  110) {
          if (deepMD_z > 0.30) nZDeepMD1++;
          if (deepMD_z > 0.80) nZDeepMD2++;
          if (deepMD_z > 0.90) nZDeepMD3++;
        }
        if (( passHadZ1 = deep_z > 0.8  )) nZDeep1++;
        if (( passHadZ2 = deep_z > 0.95 )) nZDeep2++;
        if (( passHadZ3 = deep_z > 0.99 )) nZDeep3++;
      }
      if (debug>1) std::cout<<"AnalysisBase::calc_common_var: AK8 "<<i<<" new Z tag ok"<<std::endl;
      // Hadronic Higgs Tagging
      // Use some ad-hoc working points now (unknown mistag rate)
      // TODO: Check latest WPs (if available) and check performance with signal
      bool passHadH1 = false, passHadH2 = false, passHadH3 = false;
      if (pt >= 300 &&
          abseta    <  2.4) {
        if (sd_mass >= 100 &&
            sd_mass <  140) {
          if (( passHadH1 = deepMD_h > 0.30 )) nHDeepMD1++;
          if (( passHadH2 = deepMD_h > 0.80 )) nHDeepMD2++;
          if (( passHadH3 = deepMD_h > 0.90 )) nHDeepMD3++;
        }
        //if (( passHadH1 = deep_h > 0.8  )) nHDeep1++;
        //if (( passHadH2 = deep_h > 0.95 )) nHDeep2++;
        //if (( passHadH3 = deep_h > 0.99 )) nHDeep3++;
      }
      if (debug>1) std::cout<<"AnalysisBase::calc_common_var: AK8 "<<i<<" new H tag ok"<<std::endl;
      // Hadronic top tagging
      bool passHadTop1 = false, passHadTop2 = false, passHadTop3 = false, passHadTop4 = false;
      if (passHadTop1BMassTag[i]) {
        if (tau32[i] < 0.80) nTop1++;
        if (tau32[i] < 0.65) nTop2++;
        if (tau32[i] < 0.54) nTop3++;
        if (tau32[i] < 0.46) nTop4++;
        if (tau32[i] < 0.40) nTop5++;
      }
      // Pass mass tag without upper mass cut
      // TODO: Check signal discrimination of softdrop mass N-1 (no max cut)
      if ( pt          >= HADTOP_PT_CUT &&
           abseta      <  HADTOP_ETA_CUT &&
           sd_mass     >= HADTOP_SD_MASS_CUT_LOW ) {
        if (deepMD_top > 0.054) nTopDeepMD1++;
        if (deepMD_top > 0.391) nTopDeepMD2++;
        if (deepMD_top > 0.578) nTopDeepMD3++;
        if (deepMD_top > 0.843) nTopDeepMD4++;
      }
      if (pt        >= HADTOP_PT_CUT &&
          abseta    <  HADTOP_ETA_CUT) {
        if (( passHadTop1 = deep_top > 0.093 )) nTopDeep1++;
        if (( passHadTop2 = deep_top > 0.745 )) nTopDeep2++;
        if (( passHadTop3 = deep_top > 0.895 )) nTopDeep3++;
        if (( passHadTop4 = deep_top > 0.986 )) nTopDeep4++;
      }
      if (debug>1) std::cout<<"AnalysisBase::calc_common_var: AK8 "<<i<<" new had top tag ok"<<std::endl;
      // Leptonic top tagging
      if (( passLepJetCand[i] =
            ( ak8MatchLepTight2D &&
              pt          >= LEPTOP_PT_CUT &&
              abseta       < LEPTOP_ETA_CUT ) )) {
        itLepJetCand[i] = nLepJetCand++;
        iLepJetCand.push_back(i);
        if ( sd_mass     >= LEPTOP_SD_MASS_CUT_LOW ) {
          if (( passLepTop[i] = passSubJetBTag[i] )) {
            itLepTop[i] = nLepTop++;
            iLepTop.push_back(i);
          } else {
            passLepJet[i] = true;
            itLepJet[i] = nLepJet++;
            iLepJet.push_back(i);
          }
        }
        // High mass version
        if ( sd_mass     >= LEPTOP_SD_MASS_CUT_HIGH ) {
          if (( passLepTopHighMass[i] = passSubJetBTag[i] )) {
            itLepTopHighMass[i] = nLepTopHighMass++;
            iLepTopHighMass.push_back(i);
          } else {
            passLepJetHighMass[i] = true;
            itLepJetHighMass[i] = nLepJetHighMass++;
            iLepJetHighMass.push_back(i);
          }
        }
      }
      if (debug>1) std::cout<<"AnalysisBase::calc_common_var: AK8 "<<i<<" new lep top tag ok"<<std::endl;
      // N-1 selections
      passLepJetNoIso[i] = 
        ( ak8MatchLepTightNoIso &&
          pt          >= LEPTOP_PT_CUT &&
          abseta       < LEPTOP_ETA_CUT &&
          sd_mass     >= LEPTOP_SD_MASS_CUT_LOW &&
          !passSubJetBTag[i] );
      passLepJetNoPt[i] = 
        ( ak8MatchLepTight2D &&
          abseta       < LEPTOP_ETA_CUT &&
          sd_mass     >= LEPTOP_SD_MASS_CUT_LOW &&
          !passSubJetBTag[i] );
      passLepTopNoIso[i] = 
        ( ak8MatchLepTightNoIso &&
          pt          >= LEPTOP_PT_CUT &&
          abseta       < LEPTOP_ETA_CUT &&
          sd_mass     >= LEPTOP_SD_MASS_CUT_LOW &&
          passSubJetBTag[i] );
      passLepTopNoPt[i] = 
        ( ak8MatchLepTight2D &&
          abseta       < LEPTOP_ETA_CUT &&
          sd_mass     >= LEPTOP_SD_MASS_CUT_LOW &&
          passSubJetBTag[i] );
      passLepTopNoMass[i] = 
        ( ak8MatchLepTight2D &&
          pt          >= LEPTOP_PT_CUT &&
          abseta       < LEPTOP_ETA_CUT &&
          passSubJetBTag[i] );
      passLepTopNoSubJetB[i] = 
        ( ak8MatchLepTight2D &&
          pt          >= LEPTOP_PT_CUT &&
          abseta       < LEPTOP_ETA_CUT &&
          sd_mass     >= LEPTOP_SD_MASS_CUT_LOW );
      if (debug>1) std::cout<<"AnalysisBase::calc_common_var: AK8 "<<i<<" new lep top tag N-1 ok"<<std::endl;
      // Exclusive hadronic jet tag definitons
      if (!(passLepJet[i]||passLepTop[i])) {
        // For top signals
        if (( passHadTop[i] = passHadTop2)) {
          itHadTop[i] = nHadTop++;
          iHadTop.push_back(i);
        } else if (( passHadW[i] = passHadW2 )) {
          itHadW[i] = nHadW++;
          iHadW.push_back(i);
        }
        // For W/Z/H signals
        if (( passHadZ[i] = passHadZ2 )) {
          itHadZ[i] = nHadZ++;
          iHadZ.push_back(i);
        }
        if (( passHadV[i] = passHadW2 || passHadZ2)) {
          nVDeep2++;
          itHadV[i] = nHadV++;
          iHadV.push_back(i);
        }
        if ( passHadW1 || passHadZ1 ) nVDeep1++;
        if ( passHadW3 || passHadZ3 ) nVDeep3++;
        if (( passHadH[i] = passHadH2 )) {
          itHadH[i] = nHadH++;
          iHadH.push_back(i);
        }
      }
      if (debug>1) std::cout<<"AnalysisBase::calc_common_var: AK8 "<<i<<" new exclusive tags ok"<<std::endl;
      if (debug>1) std::cout<<"AnalysisBase::calc_common_var: AK8 "<<i<<" new taggers ok"<<std::endl;

      //if (passTightWTag(i]) selected_Ws.push_back(AK8_v4);
      //if (passHadTopTag[i]) selected_hadtops.push_back(AK8_v4);
      if (passHadW[i])   selected_Ws.push_back(AK8_v4);
      if (passHadZ[i])   selected_Zs.push_back(AK8_v4);
      if (passHadH[i])   selected_Hs.push_back(AK8_v4);
      if (passLepTop[i]) selected_leptops.push_back(AK8_v4);
      if (passHadTop[i]) selected_hadtops.push_back(AK8_v4);
      if (passHadW[i]||passHadZ[i]||passHadH[i]||passHadTop[i]||passLepJet[i]||passLepTop[i]) {
        selected_boost.push_back(AK8_v4);
        // lep/MET angle wrt. leading boost jet
        if (data.FatJet[i].pt>maxpt) {
          maxpt = data.FatJet[i].pt;
          dPhiBoostedJetMET = std::abs(TVector2::Phi_mpi_pi(data.MET_phi - data.FatJet[i].phi));
          TVector3 lep_met, met_1l;
          met_1l. SetPtEtaPhi(data.MET_pt, 0, data.MET_phi);
          if (nLepTight2D==1) {
            lep_met.SetPtEtaPhi(tight_leptons_2D[0].Pt(), 0, tight_leptons_2D[0].Phi());
            met_1l += lep_met;
            dPhiBoostedJetLep    = std::abs(TVector2::Phi_mpi_pi(tight_leptons_2D[0].Phi() - data.FatJet[i].phi));
            dPhiBoostedJetLepMET = std::abs(TVector2::Phi_mpi_pi(met_1l.Phi() - data.FatJet[i].phi));
          } else if (nLepTight2D==2) {
            if (tight_leptons_2D[0].Pt()>tight_leptons_2D[1].Pt()) {
              lep_met.SetPtEtaPhi(tight_leptons_2D[0].Pt(), 0, tight_leptons_2D[0].Phi());
              met_1l += lep_met;
              dPhiBoostedJetLep    = std::abs(TVector2::Phi_mpi_pi(tight_leptons_2D[0].Phi() - data.FatJet[i].phi));
              dPhiBoostedJetLepMET = std::abs(TVector2::Phi_mpi_pi(met_1l.Phi() - data.FatJet[i].phi));
            } else {
              lep_met.SetPtEtaPhi(tight_leptons_2D[1].Pt(), 0, tight_leptons_2D[1].Phi());
              met_1l += lep_met;
              dPhiBoostedJetLep    = std::abs(TVector2::Phi_mpi_pi(tight_leptons_2D[1].Phi() - data.FatJet[i].phi));
              dPhiBoostedJetLepMET = std::abs(TVector2::Phi_mpi_pi(met_1l.Phi() - data.FatJet[i].phi));
            }
          }
        }
        // Match to nearest AK4 jet to be able to tell which hemisphere the boosted object belongs to
        double mindR = 9999;
        size_t iJet = -1;
        for(size_t j=0; j<data.Jet.size(); ++j) if (passLooseJet[j]) {
          TLorentzVector jet_v4; jet_v4.SetPtEtaPhiM(data.Jet[j].pt, data.Jet[j].eta, data.Jet[j].phi, data.Jet[j].mass);
          double dR = AK8_v4.DeltaR(jet_v4);
          if (dR<mindR) {
            mindR = dR;
            iJet = j;
          }
        }
        iJet_Boost.push_back(iJet);
      }

      //} // End photon jet veto

    } // End Jet Selection

    // Online jet selection for AK8 HT
    if ( data.FatJet[i].pt         > 150 &&
         std::abs(data.FatJet[i].eta)  <  2.5 ) {
      // Ht
      AK8_Ht += data.FatJet[i].pt;
    }

    if (debug>1) std::cout<<"AnalysisBase::calc_common_var: AK8 "<<i<<" end"<<std::endl;
  } // End AK8 Jet Loop
  if (debug) std::cout<<"AnalysisBase::calc_common_var: end AK8"<<std::endl;

  // MT calculated for leptonic top and MET
  MT_boost = -9999;
  if (selected_boost.size()>0) MT_boost = sqrt( 2*selected_boost[0].Pt()*data.MET_pt * (1 - std::cos(data.MET_phi-selected_boost[0].Phi())) );

  // Isolated btags (not inside V tagged AK8)
  for(size_t i=0; i<data.Jet.size(); ++i) {
    TLorentzVector jet_v4; jet_v4.SetPtEtaPhiM(data.Jet[i].pt, data.Jet[i].eta, data.Jet[i].phi, data.Jet[i].mass);
    double minDR = 9999;
    for (size_t j=0; j<data.FatJet.size(); ++j) {
      // TODO: Allow 
      if (passHadV[j]) {
        TLorentzVector AK8_v4; AK8_v4.SetPtEtaPhiM(data.FatJet[j].pt, data.FatJet[j].eta, data.FatJet[j].phi, data.FatJet[j].mass);
        double DR = jet_v4.DeltaR(AK8_v4);
        if (DR<minDR) minDR = DR;
      }
    }
    if (minDR>0.8) {
      if (( passLooseIsoBTag[i]  = passLooseBTag[i] ))  nLooseIsoBTag++;
      if (( passMediumIsoBTag[i] = passMediumBTag[i] )) nMediumIsoBTag++;
    }
  }

  // Loop on generator particles
  size_t nGenPart = isData ? 0 : data.GenPart.size();
  passGenLastCopyCand       .assign(nGenPart, 0);
  passGenNoSameMother       .assign(nGenPart, 1);
  passGenFinalState         .assign(nGenPart, 0);
  passGenLepton             .assign(nGenPart, 0);
  passGenLeptonFromW        .assign(nGenPart, 0);
  passGenLeptonFromZ        .assign(nGenPart, 0);
  passGenLeptonFromH        .assign(nGenPart, 0);
  passGenLeptonFromTop      .assign(nGenPart, 0);
  passGenb                  .assign(nGenPart, 0);
  passGenW                  .assign(nGenPart, 0);
  passGenLepW               .assign(nGenPart, 0);
  passGenHadW               .assign(nGenPart, 0);
  passGenZ                  .assign(nGenPart, 0);
  passGenLepZ               .assign(nGenPart, 0);
  passGenHadZ               .assign(nGenPart, 0);
  passGenH                  .assign(nGenPart, 0);
  passGenLepH               .assign(nGenPart, 0);
  passGenHadH               .assign(nGenPart, 0);
  passGenTop                .assign(nGenPart, 0);
  passGenLepTop             .assign(nGenPart, 0);
  passGenHadTop             .assign(nGenPart, 0);
  genLepPassLepVeto         .assign(nGenPart, 0);
  genLepPassLepTightNoIso   .assign(nGenPart, 0);
  genLepPassLepTight2D      .assign(nGenPart, 0);
  genHadWPassHadWTag        .assign(nGenPart, 0);
  genHadZPassHadZTag        .assign(nGenPart, 0);
  genHadHPassHadHTag        .assign(nGenPart, 0);
  genHadTopPassHadTopTag    .assign(nGenPart, 0);
  genLepTopPassLepTopTag    .assign(nGenPart, 0);
  genHadWPassHadWMassTag    .assign(nGenPart, 0);
  genHadTopPassHadTopMassTag.assign(nGenPart, 0);
  iGenLepton       .clear();
  iGenLeptonFromW  .clear();
  iGenLeptonFromZ  .clear();
  iGenLeptonFromH  .clear();
  iGenLeptonFromTop.clear();
  iGenb            .clear();
  iGenW            .clear();
  iGenLepW         .clear();
  iGenHadW         .clear();
  iGenZ            .clear();
  iGenLepZ         .clear();
  iGenHadZ         .clear();
  iGenH            .clear();
  iGenLepH         .clear();
  iGenHadH         .clear();
  iGenTop          .clear();
  iGenLepTop       .clear();
  iGenHadTop       .clear();
  iGenWtagZ        .clear();
  iGenMassW        .clear();
  iGenMassTop      .clear();
  iGenHadWMatchedAK8     .assign(nGenPart, (size_t)-1);
  iGenHadZMatchedAK8     .assign(nGenPart, (size_t)-1);
  iGenHadHMatchedAK8     .assign(nGenPart, (size_t)-1);
  iGenHadTopMatchedAK8   .assign(nGenPart, (size_t)-1);
  iGenLepTopMatchedAK8   .assign(nGenPart, (size_t)-1);
  iGenLeptonMatchedAK8   .assign(nGenPart, (size_t)-1);
  iGenLepWMatchedGenLep  .assign(nGenPart, (size_t)-1);
  iGenLepZMatchedGenLep  .assign(nGenPart, (size_t)-1);
  iGenLepHMatchedGenLep  .assign(nGenPart, (size_t)-1);
  iGenLepTopMatchedGenLep.assign(nGenPart, (size_t)-1);
  itGenLepton            .assign(nGenPart, (size_t)-1);
  itGenLeptonFromW       .assign(nGenPart, (size_t)-1);
  itGenLeptonFromZ       .assign(nGenPart, (size_t)-1);
  itGenLeptonFromH       .assign(nGenPart, (size_t)-1);
  itGenLeptonFromTop     .assign(nGenPart, (size_t)-1);
  itGenb                 .assign(nGenPart, (size_t)-1);
  itGenW                 .assign(nGenPart, (size_t)-1);
  itGenLepW              .assign(nGenPart, (size_t)-1);
  itGenHadW              .assign(nGenPart, (size_t)-1);
  itGenZ                 .assign(nGenPart, (size_t)-1);
  itGenLepZ              .assign(nGenPart, (size_t)-1);
  itGenHadZ              .assign(nGenPart, (size_t)-1);
  itGenH                 .assign(nGenPart, (size_t)-1);
  itGenLepH              .assign(nGenPart, (size_t)-1);
  itGenHadH              .assign(nGenPart, (size_t)-1);
  itGenTop               .assign(nGenPart, (size_t)-1);
  itGenLepTop            .assign(nGenPart, (size_t)-1);
  itGenHadTop            .assign(nGenPart, (size_t)-1);
  itGenWtagZ             .assign(nGenPart, (size_t)-1);
  itGenMassW             .assign(nGenPart, (size_t)-1);
  itGenMassTop           .assign(nGenPart, (size_t)-1);
  nGenLepton        = 0;
  nGenLeptonFromW   = 0;
  nGenEleFromW      = 0;
  nGenMuFromW       = 0;
  nGenTauFromW      = 0;
  nGenLeptonFromZ   = 0;
  nGenEleFromZ      = 0;
  nGenMuFromZ       = 0;
  nGenTauFromZ      = 0;
  nGenLeptonFromH   = 0;
  nGenEleFromH      = 0;
  nGenMuFromH       = 0;
  nGenTauFromH      = 0;
  nGenLeptonFromTop = 0;
  nGenEleFromTop    = 0;
  nGenMuFromTop     = 0;
  nGenTauFromTop    = 0;
  nGenb             = 0;
  nGenW             = 0;
  nGenLepW          = 0;
  nGenHadW          = 0;
  nGenZ             = 0;
  nGenLepZ          = 0;
  nGenHadZ          = 0;
  nGenH             = 0;
  nGenLepH          = 0;
  nGenHadH          = 0;
  nGenTop           = 0;
  nGenLepTop        = 0;
  nGenHadTop        = 0;
  nGenWtagZ = nGenMassW = nGenMassTop = 0;
  npreWTag = nWTag = nmWTag = npreTopTag = nTopTag = nmTopTag = 0;
  nGenPhotonFake = nGenPhotonPromptDirect = nGenPhotonPromptFragmentation = 0;
  TLorentzVector wtag_v4;
  std::vector<TLorentzVector> selected_genmatched_photon;
  std::vector<TLorentzVector> selected_genw_v4;
  std::vector<TLorentzVector> selected_genb_v4;
  TLorentzVector fatjet_v4;
  ak8MatchGenHadW         .assign(data.FatJet.size(),   0);
  ak8MatchGenHadZ         .assign(data.FatJet.size(),   0);
  ak8MatchGenHadH         .assign(data.FatJet.size(),   0);
  ak8MatchGenHadTop       .assign(data.FatJet.size(),   0);
  ak8MatchGenLepTop       .assign(data.FatJet.size(),   0);
  ak8MatchGenLepton       .assign(data.FatJet.size(),   0);
  eleMatchGenEle          .assign(data.Electron.size(), 0);
  eleMatchGenEleFromW     .assign(data.Electron.size(), 0);
  eleMatchGenEleFromZ     .assign(data.Electron.size(), 0);
  eleMatchGenEleFromH     .assign(data.Electron.size(), 0);
  eleMatchGenEleFromTop   .assign(data.Electron.size(), 0);
  muMatchGenMu            .assign(data.Muon.size(),     0);
  muMatchGenMuFromW       .assign(data.Muon.size(),     0);
  muMatchGenMuFromZ       .assign(data.Muon.size(),     0);
  muMatchGenMuFromH       .assign(data.Muon.size(),     0);
  muMatchGenMuFromTop     .assign(data.Muon.size(),     0);
  // 1st Loop is a recursive search for (grand/)mothers
  // set flags based on (grand/)daughters (eg. leptonic decays for W/top)
  // TODO: debug Data, which says the collection size is not 0
  if (!isData) for(size_t i=0; i<nGenPart; ++i) {
    if (debug>1) std::cout<<"AnalysisBase::calc_common_var: gen 1st loop "<<i<<" start"<<std::endl;
    int motherid = -9999, grandmotherid = -9999, greatgrandmotherid = -9999;
    int iMother = data.GenPart[i].genPartIdxMother, iGrandmother = -1, iGreatgrandmother = -1;
    // Set the mother to the first ancestor that has different pdg id
    if (iMother!=-1) {
      while (data.GenPart[iMother].pdgId == data.GenPart[i].pdgId) {
        passGenNoSameMother[iMother] = 0;
        iMother = data.GenPart[iMother].genPartIdxMother;
      }
      if (iMother!=-1) {
        motherid = data.GenPart[iMother].pdgId;
        // The mother is a candidate for final non-decayed state
        // But have to check that it does not have a daughter with the same pdgId
        // found in the previous iteration
        passGenLastCopyCand[iMother] = 1;
        iGrandmother = data.GenPart[iMother].genPartIdxMother;
        if (iGrandmother!=-1) {
          // Remove intermediate states from history (where id matches that of the mother)
          while (data.GenPart[iGrandmother].pdgId == data.GenPart[iMother].pdgId) iGrandmother = data.GenPart[iGrandmother].genPartIdxMother;
          if (iGrandmother!=-1) {
            grandmotherid = data.GenPart[iGrandmother].pdgId;
            // This seems a bit too much, but there are cases like: top->W->tau->ele/mu
            iGreatgrandmother = data.GenPart[iGrandmother].genPartIdxMother;
            if (iGreatgrandmother!=-1) {
              while (data.GenPart[iGreatgrandmother].pdgId == data.GenPart[iGrandmother].pdgId) iGreatgrandmother = data.GenPart[iGreatgrandmother].genPartIdxMother;
              if (iGreatgrandmother!=-1) {
                greatgrandmotherid = data.GenPart[iGreatgrandmother].pdgId;
              }
            }
          }
        }
      }
    }
    if (debug>1) std::cout<<"AnalysisBase::calc_common_var: gen 1st loop "<<i<<" (grand/)mother ok"<<std::endl;
    
    // Check if particle is the last copy
    // gen status flags stored bitwise, bits are: 
    // 0 : isPrompt, 1 : isDecayedLeptonHadron, 2 : isTauDecayProduct, 3 : isPromptTauDecayProduct, 
    // 4 : isDirectTauDecayProduct, 5 : isDirectPromptTauDecayProduct, 6 : isDirectHadronDecayProduct, 
    // 7 : isHardProcess, 8 : fromHardProcess, 9 : isHardProcessTauDecayProduct, 
    // 10 : isDirectHardProcessTauDecayProduct, 11 : fromHardProcessBeforeFSR, 
    // 12 : isFirstCopy, 13 : isLastCopy, 14 : isLastCopyBeforeFSR
    // Good presentation from Josh Bendavid (slide 13-17)
    // https://indico.cern.ch/event/402279/contributions/960421/attachments/805964/1104514/mcaod-Jun17-2015.pdf#search=isLastCopy%20GenPart
    // isLastCopy: last copy of a given particle.  More likely, but notguaranteed, to have "final" physical kinematics
    // --> Correctly give status=1 for e/mu, and status=2 for tau
    //     But is unreliable for Ws, there we need to recursively
    //     eg.: lep -> W (final) -> W (interm) -> top
    //     isLastCopy fails O(%) for the final state W, especially for electrons (as high as 3%)
    bool isLastCopy = (data.GenPart[i].statusFlags>>13)&1;
    if (isLastCopy) {
      // Generator final state leptons
      if (( passGenLepton[i] = 
            ( std::abs(data.GenPart[i].pdgId)==11 ||
              std::abs(data.GenPart[i].pdgId)==13 ||
              std::abs(data.GenPart[i].pdgId)==15 ) )) {
        // Leptons from W
        if (( passGenLeptonFromW[i] = (std::abs(motherid)==24) )) {
          passGenLepW[iMother] = 1;
          iGenLepWMatchedGenLep[iMother] = i;
          // also from leptonic top
          if (( passGenLeptonFromTop[i] = (std::abs(grandmotherid)==6) )) {
            passGenLepTop[iGrandmother] = 1;
            iGenLepTopMatchedGenLep[iGrandmother] = i;
          }
          // also from Higgs
          if (( passGenLeptonFromH[i] = (std::abs(grandmotherid)==25) )) {
            passGenLepH[iGrandmother] = 1;
            iGenLepHMatchedGenLep[iGrandmother] = i;
          }
        }
        // Leptons from Z
        else if (( passGenLeptonFromZ[i] = (std::abs(motherid)==23) )) {
          passGenLepZ[iMother] = 1;
          iGenLepZMatchedGenLep[iMother] = i;
          // also from Higgs
          if (( passGenLeptonFromH[i] = (std::abs(grandmotherid)==25) )) {
            passGenLepH[iGrandmother] = 1;
            iGenLepHMatchedGenLep[iGrandmother] = i;
          }
        }
        // Leptons from H
        else if (( passGenLeptonFromH[i] = (std::abs(motherid)==25) )) {
          passGenLepH[iMother] = 1;
          iGenLepHMatchedGenLep[iMother] = i;
        }
        // Lepton from taus, here we go ... :)
        else if ( ( std::abs(data.GenPart[i].pdgId)==11 ||
               std::abs(data.GenPart[i].pdgId)==13 ) &&
             std::abs(motherid)==15) {
          // also lepton from W
          if (( passGenLeptonFromW[i] = (std::abs(grandmotherid)==24) )) {
            passGenLepW[iGrandmother] = 1;
            iGenLepWMatchedGenLep[iGrandmother] = i;
            // also lepton from top
            if (( passGenLeptonFromTop[i] = (std::abs(greatgrandmotherid)==6) )) {
              passGenLepTop[iGreatgrandmother] = 1;
              iGenLepTopMatchedGenLep[iGreatgrandmother] = i;
            }
          }
        }
      }
    }
    if (debug>1) std::cout<<"AnalysisBase::calc_common_var: gen 1st loop "<<i<<" end"<<std::endl;
  }
  if (debug) std::cout<<"AnalysisBase::calc_common_var: end gen 1st loop"<<std::endl;

  // 2nd Loop, to calculate gen matched objects
  if (!isData) for(size_t i=0; i<nGenPart; ++i) {
    if (debug>1) std::cout<<"AnalysisBase::calc_common_var: gen 2nd loop "<<i<<" start"<<std::endl;
    double gen_mass = data.GenPart[i].mass;
    // mass is not stored in NanoAOD for particle masses below 10 GeV, need to look it up in PDG
    if (std::abs(data.GenPart[i].pdgId)==1)      gen_mass = 0.005;
    else if (std::abs(data.GenPart[i].pdgId)==2) gen_mass = 0.002;
    else if (std::abs(data.GenPart[i].pdgId)==3) gen_mass = 0.095;
    else if (std::abs(data.GenPart[i].pdgId)==4) gen_mass = 1.275;
    else if (std::abs(data.GenPart[i].pdgId)==5) gen_mass = 4.180;
    else if (std::abs(data.GenPart[i].pdgId)==11) gen_mass = 0.0005;
    else if (std::abs(data.GenPart[i].pdgId)==13) gen_mass = 0.106;
    else if (std::abs(data.GenPart[i].pdgId)==15) gen_mass = 1.777;
    TLorentzVector gen_v4; gen_v4.SetPtEtaPhiM(data.GenPart[i].pt, data.GenPart[i].eta, data.GenPart[i].phi, gen_mass);
    int motherid = -9999, iMother = data.GenPart[i].genPartIdxMother;
    if (iMother!=-1) {
      while (data.GenPart[iMother].pdgId == data.GenPart[i].pdgId) iMother = data.GenPart[iMother].genPartIdxMother;
      if (iMother!=-1) motherid = data.GenPart[iMother].pdgId;
    }
    if (debug>1) std::cout<<"AnalysisBase::calc_common_var: gen 2nd loop "<<i<<" masses ok"<<std::endl;

    // Generator leptons
    if (passGenLepton[i]) {
      if (debug>1) std::cout<<"AnalysisBase::calc_common_var: gen 2nd loop "<<i<<" gen lep"<<std::endl;
      iGenLepton.push_back(i);
      itGenLepton[i] = nGenLepton++;
      if (std::abs(data.GenPart[i].pdgId)==11) {
        for (size_t j=0; j<data.Electron.size(); ++j) if (data.Electron[j].genPartIdx==i) eleMatchGenEle[j] = 1;
        nGenEle++;
      }
      if (std::abs(data.GenPart[i].pdgId)==13) {
        for (size_t j=0; j<data.Muon.size(); ++j) if (data.Muon[j].genPartIdx==i) muMatchGenMu[j] = 1;
        nGenMu++;
      }
      if (std::abs(data.GenPart[i].pdgId)==15) {
        nGenTau++;
      }
      selected_genlep.push_back(gen_v4);

      // leptons from W decay
      if (passGenLeptonFromW[i]) {
        iGenLeptonFromW.push_back(i);
        itGenLeptonFromW[i] = nGenLeptonFromW++;
        if (std::abs(data.GenPart[i].pdgId)==11) {
          for (size_t j=0; j<data.Electron.size(); ++j) if (data.Electron[j].genPartIdx==i) eleMatchGenEleFromW[j] = 1;
          nGenEleFromW++;
        }
        if (std::abs(data.GenPart[i].pdgId)==13) {
          for (size_t j=0; j<data.Muon.size(); ++j) if (data.Muon[j].genPartIdx==i) muMatchGenMuFromW[j] = 1;
          nGenMuFromW++;
        }
        if (std::abs(data.GenPart[i].pdgId)==15) {
          nGenTauFromW++;
        }
      }
      if (debug>1) std::cout<<"AnalysisBase::calc_common_var: gen 2nd loop "<<i<<" gen lep from W ok"<<std::endl;

      // leptons from Z decay
      if (passGenLeptonFromZ[i]) {
        iGenLeptonFromZ.push_back(i);
        itGenLeptonFromZ[i] = nGenLeptonFromZ++;
        if (std::abs(data.GenPart[i].pdgId)==11) {
          for (size_t j=0; j<data.Electron.size(); ++j) if (data.Electron[j].genPartIdx==i) eleMatchGenEleFromZ[j] = 1;
          nGenEleFromZ++;
        }
        if (std::abs(data.GenPart[i].pdgId)==13) {
          for (size_t j=0; j<data.Muon.size(); ++j) if (data.Muon[j].genPartIdx==i) muMatchGenMuFromZ[j] = 1;
          nGenMuFromZ++;
        }
        if (std::abs(data.GenPart[i].pdgId)==15) {
          nGenTauFromZ++;
        }
      }
      if (debug>1) std::cout<<"AnalysisBase::calc_common_var: gen 2nd loop "<<i<<" gen lep from Z ok"<<std::endl;

      // leptons from Higgs decay
      if (passGenLeptonFromH[i]) {
        iGenLeptonFromH.push_back(i);
        itGenLeptonFromH[i] = nGenLeptonFromH++;
        if (std::abs(data.GenPart[i].pdgId)==11) {
          for (size_t j=0; j<data.Electron.size(); ++j) if (data.Electron[j].genPartIdx==i) eleMatchGenEleFromW[j] = 1;
          nGenEleFromH++;
        }
        if (std::abs(data.GenPart[i].pdgId)==13) {
          for (size_t j=0; j<data.Muon.size(); ++j) if (data.Muon[j].genPartIdx==i) muMatchGenMuFromH[j] = 1;
          nGenMuFromH++;
        }
        if (std::abs(data.GenPart[i].pdgId)==15) {
          nGenTauFromH++;
        }
      }
      if (debug>1) std::cout<<"AnalysisBase::calc_common_var: gen 2nd loop "<<i<<" gen lep from Higgs ok"<<std::endl;

      // leptons from top decay
      if (passGenLeptonFromTop[i]) {
        iGenLeptonFromTop.push_back(i);
        itGenLeptonFromTop[i] = nGenLeptonFromTop++;
        if (std::abs(data.GenPart[i].pdgId)==11) {
          nGenEleFromTop++;
          for (size_t j=0; j<data.Electron.size(); ++j) if (data.Electron[j].genPartIdx==i) eleMatchGenEleFromTop[j] = 1;
        }
        if (std::abs(data.GenPart[i].pdgId)==13) {
          nGenMuFromTop++;
          for (size_t j=0; j<data.Muon.size(); ++j) if (data.Muon[j].genPartIdx==i) muMatchGenMuFromTop[j] = 1;
        } 
        if (std::abs(data.GenPart[i].pdgId)==15) {
          nGenTauFromTop++;
        }
      }

      if (debug>1) std::cout<<"AnalysisBase::calc_common_var: gen 2nd loop "<<i<<" gen lep from top ok"<<std::endl;

      // Match Lepton to AK8
      double mindR = 9999;
      size_t iMatchAK8 = -1;
      for (size_t j=0; j<data.FatJet.size(); ++j) {
        fatjet_v4.SetPtEtaPhiM(data.FatJet[j].pt, data.FatJet[j].eta, data.FatJet[j].phi, data.FatJet[j].mass);
        double dR = gen_v4.DeltaR(fatjet_v4);
        if (dR<0.8) {
          ak8MatchGenLepton[j] = true;
          if (passGenLeptonFromTop[i]) {
            ak8MatchedGenLeptonMotherID[j] = 6;
          } else if (passGenLeptonFromW[i]) {
            ak8MatchedGenLeptonMotherID[j] = 24;
          } else if (passGenLeptonFromZ[i]) {
            ak8MatchedGenLeptonMotherID[j] = 23;
          } else if (passGenLeptonFromH[i]) {
            ak8MatchedGenLeptonMotherID[j] = 25;
          } else {
            ak8MatchedGenLeptonMotherID[j] = motherid;
          }
          if (dR<mindR) {
            mindR = dR;
            iMatchAK8 = j;
          }
        }
      }
      if (iMatchAK8!=(size_t)-1) {
        iGenLeptonMatchedAK8[i] = iMatchAK8;
        //genHadWPassHadWTag[i] = passHadW[iMatchAK8]; // TODO: Match to lepton-jet (nob) tag
      }
      
      if (std::abs(data.GenPart[i].pdgId)==11) {
        // Match electron selections
        for (size_t j=0; j<data.Electron.size(); ++j) if (data.Electron[j].genPartIdx==i) {
          if (passEleVeto[j])       genLepPassLepVeto[i] = 1;
          if (passEleTightNoIso[j]) genLepPassLepTightNoIso[i] = 1;
          if (passEleTight2D[j])    genLepPassLepTight2D[i] = 1;
        }
      } else if (std::abs(data.GenPart[i].pdgId)==13) {
        // Match muon selections
        for (size_t j=0; j<data.Muon.size(); ++j) if (data.Muon[j].genPartIdx==i) {
          if (passMuVeto[j])       genLepPassLepVeto[i] = 1;
          if (passMuTightNoIso[j]) genLepPassLepTightNoIso[i] = 1;
          if (passMuTight2D[j])    genLepPassLepTight2D[i] = 1;
        }
      } else if (std::abs(data.GenPart[i].pdgId)==15) {
        // Match tau selections
        // Unlike other leptons, the taus decay to leptons or hadrons
        // It is only fair to match to the ID of the corresponding decay product
        // for ele/mu, the matching will be done above for the tau daughters
        // The reco taus are for the hadronic decay, so require Tau_genPartFlav==5
        for (size_t j=0; j<data.Tau.size(); ++j) if (data.Tau[j].genPartIdx==i) {
          if (data.Tau[j].genPartFlav==5&&passTauVeto[j]) genLepPassLepVeto[i] = 1;
        }
      }
      if (debug>1) std::cout<<"AnalysisBase::calc_common_var: gen 2nd loop "<<i<<" lep object matching ok"<<std::endl;
    }
    if (debug>1) std::cout<<"AnalysisBase::calc_common_var: gen 2nd loop "<<i<<" gen leptons ok"<<std::endl;

    // Prompt photons (from gq mother)
    if( std::abs(data.GenPart[i].pdgId) == 22 && (std::abs(motherid)==1||std::abs(motherid)==2||std::abs(motherid)==3||std::abs(motherid)==4||std::abs(motherid)==5||std::abs(motherid)==6||std::abs(motherid)==21)){
      for (size_t iPhoton=0; iPhoton<selected_photons.size(); ++iPhoton) {
        if(gen_v4.DeltaR(selected_photons[iPhoton]) < 0.1 && data.GenPart[i].pt/selected_photons[iPhoton].Pt() > 0.5 && data.GenPart[i].pt/selected_photons[iPhoton].Pt() < 2 && data.GenPart[i].status == 1) selected_genmatched_photon.push_back(selected_photons[iPhoton]);
        else nGenPhotonFake++;
      }
    }
    if (debug>1) std::cout<<"AnalysisBase::calc_common_var: gen 2nd loop "<<i<<" prompt photons ok"<<std::endl;

    // Final non-decayed state particles
    if ( (passGenFinalState[i] = data.GenPart[i].status==1 || data.GenPart[i].status==2 || (passGenLastCopyCand[i] && passGenNoSameMother[i])) ) {
      // Apply cut |eta| < 2.4
      if (std::abs(data.GenPart[i].eta)<2.4) {

        // gen bs
        if(std::abs(data.GenPart[i].pdgId)==5) {
          iGenb.push_back(i);
          itGenb[i] = nGenb++;
          selected_genb_v4.push_back(gen_v4);
        }
        if (debug>1) std::cout<<"AnalysisBase::calc_common_var: gen 2nd loop "<<i<<" final state bs ok"<<std::endl;
        
        // gen Ws
        // Consider hadronically decaying Ws and match them to AK8 jet
        if (( passGenW[i] = std::abs(data.GenPart[i].pdgId)==24 )) {
          iGenW.push_back(i);
          itGenW[i] = nGenW++;
          if (passGenLepW[i]) {
            iGenLepW.push_back(i);
            itGenLepW[i] = nGenLepW++;
          } else {
            passGenHadW[i] = 1;
            iGenHadW.push_back(i);
            itGenHadW[i] = nGenHadW++;
            selected_genw_v4.push_back(gen_v4);
            double mindR = 9999;
            size_t iMatchAK8 = -1;
            for (size_t j=0; j<data.FatJet.size(); ++j) {
              fatjet_v4.SetPtEtaPhiM(data.FatJet[j].pt, data.FatJet[j].eta, data.FatJet[j].phi, data.FatJet[j].mass);
              double dR = gen_v4.DeltaR(fatjet_v4);
              if (dR<0.8) {
                ak8MatchGenHadW[j] = true;
                if (dR<mindR) {
                  mindR = dR;
                  iMatchAK8 = j;
                }
                npreWTag++;
              }
            }
            if (iMatchAK8!=(size_t)-1) {
              iGenHadWMatchedAK8[i] = iMatchAK8;
              genHadWPassHadWTag[i] = passHadW[iMatchAK8];
              // Changgi
              genHadWPassHadWMassTag[i] = passWMassTag[iMatchAK8];
              if (passHadW[iMatchAK8]) {
                nWTag++;
              }
            }
          }
        }
        if (debug>1) std::cout<<"AnalysisBase::calc_common_var: gen 2nd loop "<<i<<" final state Ws ok"<<std::endl;

        // gen Zs
        if (( passGenZ[i] = std::abs(data.GenPart[i].pdgId)==23 )) {
          iGenZ.push_back(i);
          itGenZ[i] = nGenZ++;
          if (passGenLepZ[i]) {
            iGenLepZ.push_back(i);
            itGenLepZ[i] = nGenLepZ++;
          } else {
            passGenHadZ[i] = 1;
            iGenHadZ.push_back(i);
            itGenHadZ[i] = nGenHadZ++;
            double mindR = 9999;
            size_t iMatchAK8 = -1;
            for (size_t j=0; j<data.FatJet.size(); ++j) {
              fatjet_v4.SetPtEtaPhiM(data.FatJet[j].pt, data.FatJet[j].eta, data.FatJet[j].phi, data.FatJet[j].mass);
              double dR = gen_v4.DeltaR(fatjet_v4);
              if (dR<0.8) {
                ak8MatchGenHadZ[j] = true;
                if (dR<mindR) {
                  mindR = dR;
                  iMatchAK8 = j;
                }
              }
            }
            if (iMatchAK8!=(size_t)-1) {
              iGenHadZMatchedAK8[i] = iMatchAK8;
              genHadZPassHadZTag[i] = passHadZ[iMatchAK8];
            }
          }
        }
        if (debug>1) std::cout<<"AnalysisBase::calc_common_var: gen 2nd loop "<<i<<" final state Zs ok"<<std::endl;

        // gen Higgs
        if (( passGenH[i] = std::abs(data.GenPart[i].pdgId)==25 )) {
          iGenH.push_back(i);
          itGenH[i] = nGenH++;
          if (passGenLepH[i]) {
            iGenLepH.push_back(i);
            itGenLepH[i] = nGenLepH++;
          } else {
            passGenHadH[i] = 1;
            iGenHadH.push_back(i);
            itGenHadH[i] = nGenHadH++;
            double mindR = 9999;
            size_t iMatchAK8 = -1;
            for (size_t j=0; j<data.FatJet.size(); ++j) {
              fatjet_v4.SetPtEtaPhiM(data.FatJet[j].pt, data.FatJet[j].eta, data.FatJet[j].phi, data.FatJet[j].mass);
              double dR = gen_v4.DeltaR(fatjet_v4);
              if (dR<0.8) {
                ak8MatchGenHadH[j] = true;
                if (dR<mindR) {
                  mindR = dR;
                  iMatchAK8 = j;
                }
              }
            }
            if (iMatchAK8!=(size_t)-1) {
              iGenHadHMatchedAK8[i] = iMatchAK8;
              genHadHPassHadHTag[i] = passHadH[iMatchAK8];
            }
          }
        }
        if (debug>1) std::cout<<"AnalysisBase::calc_common_var: gen 2nd loop "<<i<<" final state Higgs' k"<<std::endl;
        
        // gen tops
        if(( passGenTop[i] = std::abs(data.GenPart[i].pdgId)==6 )) {
          if (debug>1) std::cout<<"AnalysisBase::calc_common_var: gen 2nd loop "<<i<<" gentop start"<<std::endl;
          iGenTop.push_back(i);
          itGenTop[i] = nGenTop++;
          double mindR = 9999;
          size_t iMatchAK8 = -1;
          if (passGenLepTop[i]) {
            if (debug>1) std::cout<<"AnalysisBase::calc_common_var: gen 2nd loop "<<i<<" gentop lep start"<<std::endl;
            iGenLepTop.push_back(i);
            itGenLepTop[i] = nGenLepTop++;
            for (size_t j=0; j<data.FatJet.size(); ++j) {
              if (debug>1) std::cout<<"AnalysisBase::calc_common_var: gen 2nd loop "<<i<<" iFatJet="<<j<<std::endl;
              fatjet_v4.SetPtEtaPhiM(data.FatJet[j].pt, data.FatJet[j].eta, data.FatJet[j].phi, data.FatJet[j].mass);
              double dR = gen_v4.DeltaR(fatjet_v4);
              if (dR<0.8) {
                ak8MatchGenLepTop[j] = true;
                if (dR<mindR) {
                  mindR = dR;
                  iMatchAK8 = j;
                }
              }
            }
            if (debug>1) std::cout<<"AnalysisBase::calc_common_var: gen 2nd loop "<<i<<" gentop lep jet match ok"<<std::endl;
            if (iMatchAK8!=(size_t)-1) {
              iGenLepTopMatchedAK8[i] = iMatchAK8;
              genLepTopPassLepTopTag[i] = passLepTop[iMatchAK8];
            }
            if (debug>1) std::cout<<"AnalysisBase::calc_common_var: gen 2nd loop "<<i<<" gentop lep ok"<<std::endl;
          } else {
            if (debug>1) std::cout<<"AnalysisBase::calc_common_var: gen 2nd loop "<<i<<" gentop had start"<<std::endl;
            passGenHadTop[i] = 1;
            iGenHadTop.push_back(i);
            itGenHadTop[i] = nGenHadTop++;
            for (size_t j=0; j<data.FatJet.size(); ++j) {
              if (debug>1) std::cout<<"AnalysisBase::calc_common_var: gen 2nd loop "<<i<<" iFatJet="<<j<<std::endl;
              fatjet_v4.SetPtEtaPhiM(data.FatJet[j].pt, data.FatJet[j].eta, data.FatJet[j].phi, data.FatJet[j].mass);
              double dR = gen_v4.DeltaR(fatjet_v4);
              if (dR<0.8) {
                ak8MatchGenHadTop[j] = true;
                if (dR<mindR) {
                  mindR = dR;
                  iMatchAK8 = j;
                }
                npreTopTag++;
                if (debug>1) std::cout<<"AnalysisBase::calc_common_var: gen 2nd loop "<<i<<" iFatJet="<<j<<std::endl;
              }
            }
            if (debug>1) std::cout<<"AnalysisBase::calc_common_var: gen 2nd loop "<<i<<" gentop had jet match ok"<<std::endl;
            if (iMatchAK8!=(size_t)-1) {
              if (debug>1) std::cout<<"AnalysisBase::calc_common_var: gen 2nd loop AK8="<<iMatchAK8<<" ok1"<<std::endl;
              iGenHadTopMatchedAK8[i] = iMatchAK8;
              genHadTopPassHadTopTag[i] = passHadTop[iMatchAK8];
              // Changgi
              genHadTopPassHadTopMassTag[i] = passHadTopMassTag[iMatchAK8];
              if (passHadTop1BMassTag[iMatchAK8]) {
                if (debug>1) std::cout<<"AnalysisBase::calc_common_var: gen 2nd loop AK8="<<iMatchAK8<<" ok2"<<std::endl;
                iGenMassTop.push_back(i);
                itGenMassTop[i] = nmTopTag++;
              }
            }
            if (debug>1) std::cout<<"AnalysisBase::calc_common_var: gen 2nd loop "<<i<<" gentop had ok9"<<std::endl;
          }
        }
        if (debug>1) std::cout<<"AnalysisBase::calc_common_var: gen 2nd loop "<<i<<" final state tops ok"<<std::endl;
      } // End abs(eta) cut
    } // End passGenFinalState
  } // End GenPart loop
  if (debug) std::cout<<"AnalysisBase::calc_common_var: end gen 2nd loop"<<std::endl;

  // genW-genb-AK8 matching by Changgi
  for(size_t i=0;i<selected_genw_v4.size();++i){
    for(size_t k=0;k<selected_genb_v4.size();++k){
      for (size_t j=0; j<data.FatJet.size(); ++j) {
        wtag_v4.SetPtEtaPhiM(data.FatJet[j].pt, data.FatJet[j].eta, data.FatJet[j].phi, data.FatJet[j].mass);
        //double dR = wtag_v4.DeltaR(selected_genw_v4[i]);
        double dR = selected_genw_v4[i].DeltaR(wtag_v4);
        double dR1 = 9999;
        if (dR<0.8) {
          if (passWMassTag[j]) {
            nmWTag=1;
            dR1 = selected_genb_v4[k].DeltaR(wtag_v4);
            if (dR1<0.8) nmWTag=-1;
            else{ iGenMassW.push_back(j); itGenMassW[j] = nGenMassW++;}
          }
          if (passTightWTag[j]) {
            //passWTag = 1;
            nWTag=1;
            //dR1 = wtag_v4.DeltaR(selected_genb_v4[k]);
            dR1 = selected_genb_v4[k].DeltaR(wtag_v4);
            if (dR1<0.8) nWTag=-1;
            else{
              //iGenHadW.push_back(j);
              //itGenHadW[j] = nGenHadW++;
            }
          }
          //passpreWTag = 1;
          npreWTag++;
        }
      }
    }
  }
  if (debug) std::cout<<"AnalysisBase::calc_common_var: end genW-genb-AK8 matching loop"<<std::endl;

  // Direct/Fragmentation photon flags (photon far from/close to qg)
  for(size_t j=0; j<selected_genmatched_photon.size(); ++j){
    if (!isData) for(size_t i=0; i<nGenPart; ++i) {
      if((std::abs(data.GenPart[i].pdgId)==1||std::abs(data.GenPart[i].pdgId)==2||std::abs(data.GenPart[i].pdgId)==3||std::abs(data.GenPart[i].pdgId)==4||std::abs(data.GenPart[i].pdgId)==5||std::abs(data.GenPart[i].pdgId)==6||std::abs(data.GenPart[i].pdgId)==21) && data.GenPart[i].status==23) {
        TLorentzVector genpho;
        genpho.SetPtEtaPhiM(data.GenPart[i].pt, data.GenPart[i].eta, data.GenPart[i].phi, data.GenPart[i].mass);
        double dR_genqg = genpho.DeltaR(selected_genmatched_photon[j]);
        if (dR_genqg > 0.4) nGenPhotonPromptDirect++;
        else nGenPhotonPromptFragmentation++;
      }
    }
  }
  if (debug) std::cout<<"AnalysisBase::calc_common_var: end direct/frag photon matching"<<std::endl;

  // Recalculation of Razor variables
  // Has to be done after jet uncertainties applied
  // Get selected AK4 jets (input for megajets)

  // Calculating hemispheres is a CPU intensive task
  // So we only do it when really necessary (no pt variations)
  // And save them if no systematics are applied on jets
  if (syst_index==0 || recalc_megajets) {
    if (debug) std::cout<<"AnalysisBase::calc_common_var: calc megajets start"<<std::endl;
    // Get input jets
    std::vector<TLorentzVector> selected_jets_AK4, nophoton_jets_AK4;
    for(size_t i=0; i<data.Jet.size(); ++i) {
      TLorentzVector jet_v4; jet_v4.SetPtEtaPhiM(data.Jet[i].pt, data.Jet[i].eta, data.Jet[i].phi, data.Jet[i].mass);
      // Pass jet selection criteria
      if (passLooseJet[i]) selected_jets_AK4.push_back(jet_v4);
      if (passLooseJetNoPho[i]&&(nPhotonSelect==1||nPhotonPreSelect==1)) nophoton_jets_AK4.push_back(jet_v4);
    }
    // Add lepton
    for (const auto& lepton : leptons_to_megajet) selected_jets_AK4.push_back(lepton);
    if (debug) std::cout<<"AnalysisBase::calc_common_var: calc megajets - collect jets ok"<<std::endl;
    // Calculate hemispheres (old method)
    if (selected_jets_AK4.size()>=2) hemis_AK4 = Razor::CombineJets(selected_jets_AK4);
    else hemis_AK4.clear();
    if (nPhotonSelect==1||nPhotonPreSelect==1) {
      if (nophoton_jets_AK4.size()>=2) hemis_AK4_nophoton = Razor::CombineJets(nophoton_jets_AK4);
      else hemis_AK4_nophoton.clear();
    } else hemis_AK4_nophoton = hemis_AK4;
    // Save result
    if (syst_index==0) {
      saved_hemis_AK4 = hemis_AK4;
      saved_hemis_AK4_nophoton = hemis_AK4_nophoton;
    }
    if (debug) std::cout<<"AnalysisBase::calc_common_var: calc megajets - find hemispheres ok"<<std::endl;
    // Calculate hemispheres (new method)
    // Force boosted objects to be located on separate hemispheres
    if (selected_jets_AK4.size()>=2) newhemis_AK4 = Razor::CombineJetsNew(selected_jets_AK4, iJet_Boost);
    else newhemis_AK4.clear();
    //if (nPhotonSelect==1||nPhotonPreSelect==1) {
    //  if (nophoton_jets_AK4.size()>=2) newhemis_AK4_nophoton = Razor::CombineJetsNew(nophoton_jets_AK4, iJet_Boost);
    //  else newhemis_AK4_nophoton.clear();
    //} else newhemis_AK4_nophoton = newhemis_AK4;
    // Save result
    if (syst_index==0) {
      saved_newhemis_AK4 = newhemis_AK4;
      //saved_newhemis_AK4_nophoton = newhemis_AK4_nophoton;
    }
    if (debug) std::cout<<"AnalysisBase::calc_common_var: calc megajets - find hemispheres (new) ok"<<std::endl;
  } else {
    // Load previously calculated result
    hemis_AK4 = saved_hemis_AK4;
    hemis_AK4_nophoton = saved_hemis_AK4_nophoton;
    newhemis_AK4 = saved_newhemis_AK4;
    //newhemis_AK4_nophoton = saved_newhemis_AK4_nophoton;
  }

  // Recalculate Razor (also with 1/2lep or pho added to MET)
  MET_1l = MET_1vl = MET_ll = MET_pho = -9999;
  MR  = MR_pho = -9999;
  MTR = MTR_1l = MTR_1vl = MTR_ll = MTR_pho = -9999;
  R   = R_1l   = R_1vl   = R_ll   = R_pho   = -9999;
  R2  = R2_1l  = R2_1vl  = R2_ll  = R2_pho  = -9999;
  dPhiRazor = dPhiRazorNoPho = 9999;
  if (hemis_AK4.size()==2) {
    // Normal Razor
    TVector3 shifted_met;
    shifted_met.SetPtEtaPhi(data.MET_pt, 0, data.MET_phi);
    MR  = Razor::CalcMR(hemis_AK4[0], hemis_AK4[1]);
    MTR = Razor::CalcMTR(hemis_AK4[0], hemis_AK4[1], shifted_met);
    R   = MTR/MR;
    R2  = R*R;
    dPhiRazor = std::abs(TVector2::Phi_mpi_pi(hemis_AK4[0].Phi() - hemis_AK4[1].Phi()));
    // 1 (selected) lepton added
    if (nLepSelect==1) {
      MET_1l = met_1l.Pt();
      MTR_1l = Razor::CalcMTR(hemis_AK4[0], hemis_AK4[1], met_1l);
      R_1l   = MTR_1l/MR;
      R2_1l  = R_1l*R_1l;
    }
    // 1 veto lepton added (default)
    if (nLepVeto==1) {
      MET_1vl = met_1vl.Pt();
      MTR_1vl = Razor::CalcMTR(hemis_AK4[0], hemis_AK4[1], met_1vl);
      R_1vl   = MTR_1vl/MR;
      R2_1vl  = R_1vl*R_1vl;
    }
    // 2 leptons added
    if (M_ll!=-9999) {
      MET_ll = met_ll.Pt();
      MTR_ll = Razor::CalcMTR(hemis_AK4[0], hemis_AK4[1], met_ll);
      R_ll   = MTR_ll/MR;
      R2_ll  = R_ll*R_ll;
    }
  }
  //if (nTightWTag==2) {
  //  TVector3 shifted_met;
  //  shifted_met.SetPtEtaPhi(data.MET_pt, 0, data.MET_phi);
  //  MR  = Razor::CalcMR(TightWTag[0], TightWTag[1]);
  //  MTR = Razor::CalcMTR(TightWTag[0], TightWTag[1], shifted_met);
  //  R   = MTR/MR;
  //  R2  = R*R;
  //  dPhiRazor = std::abs(TVector2::Phi_mpi_pi(TightWTag[0].Phi() - TightWTag[1].Phi()));
  //}
  // Remove photon from both jet collections and add to MET
  MET_pho = data.MET_pt;
  R2_pho = R2;
  MR_pho = MR;
  if (hemis_AK4_nophoton.size()==2) {
    MET_pho = met_pho.Pt();
    MR_pho  = Razor::CalcMR(hemis_AK4_nophoton[0], hemis_AK4_nophoton[1]);
    MTR_pho = Razor::CalcMTR(hemis_AK4_nophoton[0], hemis_AK4_nophoton[1], met_pho);
    R_pho   = MTR_pho/MR_pho;
    R2_pho  = R_pho*R_pho;
    dPhiRazorNoPho = std::abs(TVector2::Phi_mpi_pi(hemis_AK4_nophoton[0].Phi() - hemis_AK4_nophoton[1].Phi()));
  }
  // Recalculate Razor (also with 1/2lep or pho added to MET)
  MR_new  = -9999;
  MTR_new = -9999;
  R_new = -9999;
  R2_new = -9999;
  dPhiRazor_new = 9999;
  if (newhemis_AK4.size()==2) {
    // Normal Razor
    TVector3 shifted_met;
    shifted_met.SetPtEtaPhi(data.MET_pt, 0, data.MET_phi);
    MR_new  = Razor::CalcMR(newhemis_AK4[0], newhemis_AK4[1]);
    MTR_new = Razor::CalcMTR(newhemis_AK4[0], newhemis_AK4[1], shifted_met);
    R_new   = MTR/MR;
    R2_new  = R*R;
    dPhiRazor_new = std::abs(TVector2::Phi_mpi_pi(newhemis_AK4[0].Phi() - newhemis_AK4[1].Phi()));
  }
  if (debug) std::cout<<"AnalysisBase::calc_common_var: calc razor ok"<<std::endl;
  if (debug) std::cout<<"AnalysisBase::calc_common_var: end"<<std::endl;
}

//_______________________________________________________
//  Apply analysis cuts in the specified search region

bool
AnalysisBase::apply_all_cuts(char region) {
  return apply_ncut(region, analysis_cuts[region].size());
}

bool
AnalysisBase::apply_ncut(char region, unsigned int ncut) {
  if (ncut>analysis_cuts[region].size()) return 0;
  for (unsigned int i=0; i<ncut; ++i) if ( ! analysis_cuts[region][i].func() ) return 0;
  return 1;
}

// Cuts to apply/exclude by cut name
bool
AnalysisBase::apply_cut(char region, std::string cut_name) {
  for (const auto& cut : analysis_cuts[region]) if (cut_name == cut.name) return cut.func();
  return 0;
}

bool
AnalysisBase::apply_cuts(char region, std::vector<std::string> cuts) {
  for (const auto& cut_in_region : analysis_cuts[region]) for (const auto& cut : cuts)
    if (cut == cut_in_region.name) if (!cut_in_region.func()) return 0;
  return 1;
}

bool
AnalysisBase::apply_all_cuts_except(char region, std::string cut_to_skip) {
  bool result = true, found = false;
  for (const auto& cut : analysis_cuts[region]) {
    if (cut.name == cut_to_skip) {
      found = true;
      continue;
    }
    if (!cut.func()) result = false;
  }
  // If a certain cut meant to be skipped (N-1) is not found for some reason
  // eg. mistyped, then end the job with ar error
  // This is for safety: We do not want to fill histograms wrongly by mistake
  if (!found) {
    std::cout<<"No cut to be skipped exsists in search region \""<<region<<"\" with name: \""<<cut_to_skip<<"\""<<std::endl;
    error("AnalysisBase - the second argument for apply_all_cuts_except() is a non-sensical cut");
  }
  return result;
}

bool
AnalysisBase::apply_all_cuts_except(char region, std::vector<std::string> cuts_to_skip) {
  bool result = true;
  unsigned int found = 0;
  for (const auto& cut : analysis_cuts[region]) {
    for (const auto& cut_to_skip : cuts_to_skip) if (cut.name==cut_to_skip) {
      ++found;
      continue;
    }
    if (!cut.func()) result = false;
  }
  // If a certain cut meant to be skipped is not found for some reason
  // eg. mistyped, then end the job with ar error
  // This is for safety: We do not want to fill histograms wrongly by mistake
  if (found!=cuts_to_skip.size()) {
    std::cout<<"A cut to be skipped does not exsist in seaerch region \""<<region<<"\" with names: ";
    for (const auto& cut : cuts_to_skip) std::cout<<cut<<", "; std::cout<<std::endl;
    error("AnalysisBase - the second argument for apply_all_cuts_except() contains at least one non-sensical cut");
  }
  return result;
}


// Same functions but with cut index which is faster (can use an enum, to make it nicer)
bool
AnalysisBase::apply_cut(char region, unsigned int cut_index) { return analysis_cuts[region][cut_index].func(); }

bool
AnalysisBase::apply_cuts(char region, std::vector<unsigned int> cuts) {
  for (const unsigned int& cut : cuts) if ( ! analysis_cuts[region][cut].func() ) return 0;
  return 1;
}

bool
AnalysisBase::apply_all_cuts_except(char region, unsigned int cut_to_skip) {
  if (cut_to_skip>=analysis_cuts[region].size()) {
    std::cout<<"Index ("<<cut_to_skip<<") is too high for the cut to be skipped in search region '"<<region<<"'"<<std::endl;
    error("AnalysisBase::apply_all_cuts_except(char region, unsigned int cut_to_skip)");
  }
  for (unsigned int i=0, n=analysis_cuts[region].size(); i<n; ++i) {
    if (i==cut_to_skip) continue;
    if ( ! analysis_cuts[region][i].func() ) return 0;
  }
  return 1;
}

bool
AnalysisBase::apply_all_cuts_except(char region, std::vector<unsigned int> cuts_to_skip) {
  for (unsigned int i=0, n=analysis_cuts[region].size(); i<n; ++i) {
    for (const unsigned int& cut_to_skip : cuts_to_skip) if (i!=cut_to_skip)
      if ( ! analysis_cuts[region][i].func() ) return 0;
  }
  return 1;
}

//_______________________________________________________
//                 List of Histograms

TH1D* h_totweight;
TH1D* h_totweight_toppt;
TH1D* h_totweight_pileup;
std::vector<TH2D*> vh_totweight_signal;
std::vector<TH2D*> vh_xsec_signal;
std::vector<TH2D*> vh_weightnorm_signal;
std::vector<TH3D*> vh_totweight3D_signal;
std::vector<TH3D*> vh_xsec3D_signal;
std::vector<TH3D*> vh_weightnorm3D_signal;
TH1D* h_nisrjets;
TH1D* h_totweight_isr;
std::vector<TH3D*> vh_nisrjets_signal;
std::vector<TH3D*> vh_totweight_signal_isr;
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
TH1D* h_read_speed_1k;
TH1D* h_read_speed_10k;
TH1D* h_read_speed_job;
TH2D* h_read_speed_vs_nevt_10k;
TH2D* h_read_speed_vs_nevt_job;
TH1D* h_runtime_job;
TH2D* h_runtime_vs_nevt_10k;
TH2D* h_runtime_vs_nevt_job;
TH2D* h_btag_eff_b_loose;
TH2D* h_btag_eff_c_loose;
TH2D* h_btag_eff_l_loose;
TH2D* h_btag_eff_b_medium;
TH2D* h_btag_eff_c_medium;
TH2D* h_btag_eff_l_medium;

TH1D* h_trigger_pass;
TH1D* h_trigger_total;
TH2D* h_trigger2d_pass;
TH2D* h_trigger2d_total;
TH2D* h_trigger2d_nolep_pass;
TH2D* h_trigger2d_nolep_total;

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

//_______________________________________________________
//              Define Histograms here
void
AnalysisBase::init_common_histos(const bool& varySystematics)
{
  // bins
  Double_t gluinoBins[202]; for (int i=0; i<202; ++i) gluinoBins[i] = (i-0.5)*25;
  Double_t stopBins[402];   for (int i=0; i<402; ++i) stopBins[i] = (i-0.5)*5;
  Double_t npvLowHighBins[3] = { 0,20,100 };
  Double_t isrWeightBins[3] = {0,1,2};
  Double_t isrJetBins[17]; for (int i=0; i<17; ++i) isrJetBins[i] = i-0.5;
  // total weight
  h_totweight                     = new TH1D("totweight",           "MC;;Total (generator) event weight", 1,0,1);
  h_totweight_toppt               = new TH1D("totweight_toppt",     "MC;;Total toppt weight",             2,0,2);
  h_totweight_pileup              = new TH1D("totweight_pileup",    "MC;;Total pileup weight",            2,0,2);
  vh_totweight_signal    .push_back(new TH2D("totweight_T1tttt",    "T1tttt or T5ttcc or T5tttt;m_{#tilde{g}} (GeV);m_{#tilde{#chi}^{0}_{1}} (GeV);Total Weight",        201,gluinoBins, 201,gluinoBins));
  vh_totweight_signal    .push_back(new TH2D("totweight_T2tt",      "T2tt;m_{#tilde{t}} (GeV);m_{#tilde{#chi}^{0}_{1}} (GeV);Total Weight",        401,stopBins, 401,stopBins));
  vh_totweight_signal    .push_back(new TH2D("totweight_TChiWZ",    "TChiWZ;m_{#tilde{#chi}^{#pm}_{0}=#tilde{#chi}^{0}_{2}} (GeV);m_{#tilde{#chi}^{0}_{1}} (GeV);Total Weight",        401,stopBins, 401,stopBins));
  vh_totweight_signal    .push_back(new TH2D("totweight_TChiHH",    "TChiHH;m_{#tilde{#chi}^{0}_{3}=#tilde{#chi}^{0}_{2}} (GeV);m_{#tilde{#chi}^{0}_{1}} (GeV);Total Weight",        401,stopBins, 401,stopBins));
  vh_totweight_signal    .push_back(new TH2D("totweight_T5qqqqZH",  "T5qqqqZH;m_{#tilde{g}} (GeV);m_{#tilde{#chi}^{0}_{2}} (GeV);Total Weight",        201,gluinoBins, 201,gluinoBins));
  vh_totweight3D_signal  .push_back(new TH3D("totweight_T6bbZH",    "T6bbZH;m_{#tilde{t}} (GeV);#tilde{#chi}^{0}_{2}} (GeV);m_{#tilde{#chi}^{0}_{1}} (GeV);Total Weight", 401,stopBins, 401,stopBins, 401,stopBins));
  // ISR reweighting
  h_nisrjets                      = new TH1D("nisrjets",            ";N_{ISR jets}", 16,isrJetBins);
  h_totweight_isr                 = new TH1D("totweight_isr",       "MC;;Total (generator) event weight", 2,isrWeightBins);
  vh_nisrjets_signal     .push_back(new TH3D("nisrjets_T1tttt",     ";m_{#tilde{g}} (GeV);m_{#tilde{#chi}^{0}_{1}} (GeV);Total Weight;N_{ISR jets}", 201,gluinoBins, 201,gluinoBins, 16,isrJetBins));
  vh_nisrjets_signal     .push_back(new TH3D("nisrjets_T2tt",       ";m_{#tilde{t}} (GeV);m_{#tilde{#chi}^{0}_{1}} (GeV);Total Weight;N_{ISR jets}", 401,stopBins,  401,stopBins,    16,isrJetBins));
  vh_nisrjets_signal     .push_back(new TH3D("nisrjets_TChiWZ",     ";m_{#tilde{#chi}^{#pm}_{0}=#tilde{#chi}^{0}_{2}} (GeV);m_{#tilde{#chi}^{0}_{1}} (GeV);Total Weight;N_{ISR jets}", 401,stopBins,  401,stopBins,    16,isrJetBins));
  vh_nisrjets_signal     .push_back(new TH3D("nisrjets_TChiHH",     ";m_{#tilde{#chi}^{0}_{3}=#tilde{#chi}^{0}_{2}} (GeV);m_{#tilde{#chi}^{0}_{1}} (GeV);Total Weight;N_{ISR jets}", 401,stopBins,  401,stopBins,    16,isrJetBins));
  vh_nisrjets_signal     .push_back(new TH3D("nisrjets_T5qqqqZH",   ";m_{#tilde{g}} (GeV);m_{#tilde{#chi}^{0}_{2}} (GeV);Total Weight;N_{ISR jets}", 201,gluinoBins, 201,gluinoBins, 16,isrJetBins));
  //vh_nisrjets_signal     .push_back(new TH3D("nisrjets_T6bbZH",     ";m_{#tilde{t}} (GeV);#tilde{#chi}^{0}_{2}} (GeV);m_{#tilde{#chi}^{0}_{1}} (GeV);Total Weight;N_{ISR jets}", 401,stopBins, 401,stopBins,  401,stopBins,    16,isrJetBins));

  vh_totweight_signal_isr.push_back(new TH3D("totweight_isr_T1tttt","T1tttt or T5ttcc or T5tttt;m_{#tilde{g}} (GeV);m_{#tilde{#chi}^{0}_{1}} (GeV);Total Weight",        201,gluinoBins, 201,gluinoBins, 2,isrWeightBins));
  vh_totweight_signal_isr.push_back(new TH3D("totweight_isr_T2tt",  "T2tt;m_{#tilde{t}} (GeV);m_{#tilde{#chi}^{0}_{1}} (GeV);Total Weight",                              401,stopBins,   401,stopBins,   2,isrWeightBins));
  vh_totweight_signal_isr.push_back(new TH3D("totweight_isr_TChiWZ","TChiWZ;m_{#tilde{#chi}^{#pm}_{0}=#tilde{#chi}^{0}_{2}} (GeV);m_{#tilde{#chi}^{0}_{1}} (GeV);Total Weight",                              401,stopBins,   401,stopBins,   2,isrWeightBins));
  vh_totweight_signal_isr.push_back(new TH3D("totweight_isr_TChiHH","TChiHH;m_{#tilde{#chi}^{#pm}_{0}=#tilde{#chi}^{0}_{2}} (GeV);m_{#tilde{#chi}^{0}_{1}} (GeV);Total Weight",                              401,stopBins,   401,stopBins,   2,isrWeightBins));
  vh_totweight_signal_isr.push_back(new TH3D("totweight_isr_T5qqqqZH","T5qqqqZH;m_{#tilde{g}} (GeV);m_{#tilde{#chi}^{0}_{2}} (GeV);Total Weight",        201,gluinoBins, 201,gluinoBins, 2,isrWeightBins));
  //vh_totweight_signal_isr.push_back(new TH3D("totweight_isr_T6bbZH","T6bbZH;m_{#tilde{t}} (GeV);#tilde{#chi}^{0}_{2}} (GeV);m_{#tilde{#chi}^{0}_{1}} (GeV);Total Weight", 401,stopBins,   401,stopBins,   2,isrWeightBins));
  // signal weight
  vh_xsec_signal         .push_back(new TH2D("xsec_T1tttt",         "T1tttt or T5ttcc or T5tttt;m_{#tilde{g}} (GeV);m_{#tilde{#chi}^{0}_{1}} (GeV);Cross-section (pb)",  201,gluinoBins, 201,gluinoBins));
  vh_weightnorm_signal   .push_back(new TH2D("weightnorm_T1tttt",   "T1tttt or T5ttcc or T5tttt;m_{#tilde{g}} (GeV);m_{#tilde{#chi}^{0}_{1}} (GeV);weight norm. factor", 201,gluinoBins, 201,gluinoBins));
  vh_xsec_signal         .push_back(new TH2D("xsec_T2tt",           "T2tt;m_{#tilde{t}} (GeV);m_{#tilde{#chi}^{0}_{1}} (GeV);Cross-section (pb)",  401,stopBins, 401,stopBins));
  vh_weightnorm_signal   .push_back(new TH2D("weightnorm_T2tt",     "T2tt;m_{#tilde{t}} (GeV);m_{#tilde{#chi}^{0}_{1}} (GeV);weight norm. factor", 401,stopBins, 401,stopBins));
  vh_xsec_signal         .push_back(new TH2D("xsec_TChiWZ",         "TChiWZ;m_{#tilde{#chi}^{#pm}_{0}=#tilde{#chi}^{0}_{2}} (GeV);m_{#tilde{#chi}^{0}_{1}} (GeV);Cross-section (pb)",  401,stopBins, 401,stopBins));
  vh_weightnorm_signal   .push_back(new TH2D("weightnorm_TChiWZ",   "TChiWZ;m_{#tilde{#chi}^{#pm}_{0}=#tilde{#chi}^{0}_{2}} (GeV);m_{#tilde{#chi}^{0}_{1}} (GeV);weight norm. factor", 401,stopBins, 401,stopBins));
  vh_xsec_signal         .push_back(new TH2D("xsec_TChiHH",         "TChiHH;m_{#tilde{#chi}^{0}_{3}=#tilde{#chi}^{0}_{2}} (GeV);m_{#tilde{#chi}^{0}_{1}} (GeV);Cross-section (pb)",  401,stopBins, 401,stopBins));
  vh_weightnorm_signal   .push_back(new TH2D("weightnorm_TChiHH",   "TChiHH;m_{#tilde{#chi}^{0}_{3}=#tilde{#chi}^{0}_{2}} (GeV);m_{#tilde{#chi}^{0}_{1}} (GeV);weight norm. factor", 401,stopBins, 401,stopBins));
  vh_xsec_signal         .push_back(new TH2D("xsec_T5qqqqZH",       "T5qqqqZH;m_{#tilde{g}} (GeV);m_{#tilde{#chi}^{0}_{2}} (GeV);Cross-section (pb)",  201,gluinoBins, 201,gluinoBins));
  vh_weightnorm_signal   .push_back(new TH2D("weightnorm_T5qqqqZH", "T5qqqqZH;m_{#tilde{g}} (GeV);m_{#tilde{#chi}^{0}_{2}} (GeV);weight norm. factor", 201,gluinoBins, 201,gluinoBins));
  vh_xsec3D_signal       .push_back(new TH3D("xsec_T6bbZH",         "T6bbZH;m_{#tilde{#chi}^{#pm}_{0} (GeV);#tilde{#chi}^{0}_{2}} (GeV);m_{#tilde{#chi}^{0}_{1}} (GeV);Cross-section (pb)",  401,stopBins, 401,stopBins, 401,stopBins));
  vh_weightnorm3D_signal .push_back(new TH3D("weightnorm_T6bbZH",   "T6bbZH;m_{#tilde{t}} (GeV);#tilde{#chi}^{0}_{2}} (GeV);m_{#tilde{#chi}^{0}_{1}} (GeV);weight norm. factor", 401,stopBins, 401,stopBins, 401,stopBins));
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
  // job_monitoring histos
  h_read_speed_1k              = new TH1D("read_speed_1k",          ";Read speed (Events/s);Measurement/1k Event",  1000,0,10000);
  h_read_speed_10k             = new TH1D("read_speed_10k",         ";Read speed (Events/s);Measurement/10k Event", 1000,0,10000);
  h_read_speed_job             = new TH1D("read_speed_job",         ";Read speed (Events/s);Measurement/Job",       1000,0,10000);
  h_read_speed_vs_nevt_10k     = new TH2D("read_speed_vs_nevt_10k", ";Entry;Read speed (Events/s)/10k Event",       100,0,10000000, 200,0,10000);
  h_read_speed_vs_nevt_job     = new TH2D("read_speed_vs_nevt_job", ";Total Entries;Read speed (Events/s)/Job",     100,0,10000000, 200,0,10000);
  h_runtime_job                = new TH1D("runtime_job",            ";Total job run-time (min)",                    600,0,600);
  h_runtime_vs_nevt_job        = new TH2D("runtime_vs_nevt_job",    ";Total Entries;Total job run-time (min)",      100,0,10000000, 600,0,600);

  // btagging efficiency
  double ptbins[11]  = { 20,30,50,70,100,140,200,300,600,1000,4000 };
  double effbins[3] = { -0.5,0.5,1.5 };
  h_btag_eff_b_loose            = new TH2D("btag_eff_b_loose",  ";AK4 Jet p_{T} (GeV);Pass b-tag", 10,ptbins, 2,effbins);
  h_btag_eff_c_loose            = new TH2D("btag_eff_c_loose",  ";AK4 Jet p_{T} (GeV);Pass b-tag", 10,ptbins, 2,effbins);
  h_btag_eff_l_loose            = new TH2D("btag_eff_l_loose",  ";AK4 Jet p_{T} (GeV);Pass b-tag", 10,ptbins, 2,effbins);
  h_btag_eff_b_medium           = new TH2D("btag_eff_b_medium", ";AK4 Jet p_{T} (GeV);Pass b-tag", 10,ptbins, 2,effbins);
  h_btag_eff_c_medium           = new TH2D("btag_eff_c_medium", ";AK4 Jet p_{T} (GeV);Pass b-tag", 10,ptbins, 2,effbins);
  h_btag_eff_l_medium           = new TH2D("btag_eff_l_medium", ";AK4 Jet p_{T} (GeV);Pass b-tag", 10,ptbins, 2,effbins);

  // trigger efficiency
  double htbins[19]  = { 0, 200, 300, 400, 500, 600, 650, 700, 750, 800, 850, 900, 950, 1000, 1200, 1500, 2000, 4000, 10000 };
  double HTB[12] = {400, 500, 600, 700, 750, 800, 850, 900, 950, 1000, 1500, 10000};
  double ptB[9]  = {200, 300, 400, 450, 500, 550, 600, 1000, 10000};
  h_trigger_pass                = new TH1D("trigger_pass",    "Pass trigger;H_{T} (GeV)", 18,htbins);
  h_trigger_total               = new TH1D("trigger_total",          "Total;H_{T} (GeV)", 18,htbins);
  h_trigger2d_pass              = new TH2D("trigger2d_pass",  "Pass trigger;H_{T} (GeV);Leading AK8 jet p_{T} (GeV)", 11,HTB, 8,ptB);
  h_trigger2d_total             = new TH2D("trigger2d_total",        "Total;H_{T} (GeV);Leading AK8 jet p_{T} (GeV)", 11,HTB, 8,ptB);
  h_trigger2d_nolep_pass        = new TH2D("trigger2d_nolep_pass",  "Pass trigger;H_{T} (GeV);Leading AK8 jet p_{T} (GeV)", 11,HTB, 8,ptB);
  h_trigger2d_nolep_total       = new TH2D("trigger2d_nolep_total",        "Total;H_{T} (GeV);Leading AK8 jet p_{T} (GeV)", 11,HTB, 8,ptB);

  std::vector<std::string> regions = {"S", "s", "T", "W", "Q", "q", "Z", "L", "G", "G_DirectPrompt", "S_LooseWP"};

  if (varySystematics) {
    for (size_t i=0; i<regions.size(); ++i) {
      if (isData) {
        // Data
        vh_MRR2_data     .push_back(new TH1D((std::string("MRR2_")+regions[i]+"_data").c_str(),      ";MR/R^{2} bins (unrolled);Counts", 25,0,25));
        vh_MRR2_data_nj45.push_back(new TH1D((std::string("MRR2_")+regions[i]+"_data_nj45").c_str(), ";MR/R^{2} bins (unrolled);Counts", 25,0,25));
        vh_MRR2_data_nj6 .push_back(new TH1D((std::string("MRR2_")+regions[i]+"_data_nj6").c_str(),  ";MR/R^{2} bins (unrolled);Counts", 25,0,25));
      } else if (!isSignal) {
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
}

//_______________________________________________________
//               Fill Histograms here
void
AnalysisBase::fill_common_histos(eventBuffer& d, const bool& varySystematics, const bool& runOnSkim, const unsigned int& syst_index, const double& weight, const std::vector<std::string>& filenames)
{
  if (runOnSkim) {
    if (syst_index == 0) {
      // btag efficiency - No event selection cuts to be applied
      // When making this plot, should remove all baseline cuts
      for(size_t i=0; i<d.Jet.size(); ++i) {
        if (passLooseJet[i]) {
          if (d.Jet[i].hadronFlavour==5) {
            h_btag_eff_b_loose ->Fill(d.Jet[i].pt, passLooseBTag[i]);
            h_btag_eff_b_medium->Fill(d.Jet[i].pt, passMediumBTag[i]);
          } else if (d.Jet[i].hadronFlavour==4) {
            h_btag_eff_c_loose ->Fill(d.Jet[i].pt, passLooseBTag[i]);
            h_btag_eff_c_medium->Fill(d.Jet[i].pt, passMediumBTag[i]);
          } else {
            h_btag_eff_l_loose ->Fill(d.Jet[i].pt, passLooseBTag[i]);
            h_btag_eff_l_medium->Fill(d.Jet[i].pt, passMediumBTag[i]);
          }
        }
      }
      // trigger efficiency, measured in single lepton datasets
      // SingleElectron dataset: Pass HLT_Ele27_WPTight_Gsf && 1 Electron
      // SingleMuon     dataset: Pass HLT_IsoMu27 && 1 Muon
      // SinglePhoton   dataset: Pass all single photon triggers && 1 Photon
      // Baseline cuts to be applied: 3 jets, 1 AK8 jet, MR & R^2
      bool pass_aux_trigger = 0;
      int njet = nJet;
      if (TString(sample).Contains("MET")) {
        //if (d.hlt.PFMET120_PFMHT120_IDTight==1&&d.met.pt[0]>200&&nLepVeto==0&&d.evt.NIsoTrk==0) pass_aux_trigger = 1;
        if (d.HLT_PFMET120_PFMHT120_IDTight==1&&nLepVeto==0&&nTauVeto==0) pass_aux_trigger = 1;
      } else if (TString(sample).Contains("SingleElectron")) {
        //if ((d.hlt.Ele23_WPLoose_Gsf==1||d.hlt.Ele27_WPTight_Gsf==1)&&nEleTight>=1&&nMuVeto==0) pass_aux_trigger = 1;
        if ((d.HLT_Ele32_WPTight_Gsf==1)&&nEleVeto==1&&nMuVeto==0) pass_aux_trigger = 1;
      } else if (TString(sample).Contains("SingleMuon")) {
        //if (d.hlt.IsoMu27==1&&nMuTight>=1&&nEleVeto==0) pass_aux_trigger = 1;
        if (d.HLT_IsoMu27==1&&nMuVeto==1&&nEleVeto==0) pass_aux_trigger = 1;
      } else if (TString(sample).Contains("SinglePhoton")) {
        bool OR_HLT_Photon =
          d.HLT_Photon200==1 ||
          d.HLT_Photon300_NoHE==1;
        //if (OR_HLT_Photon==1&&nPhotonSelect==1&&nLepVeto==0&&d.evt.NIsoTrk==0) pass_aux_trigger = 1;
        if (OR_HLT_Photon==1&&nPhotonSelect==1&&nLepVeto==0&&nTauVeto==0) pass_aux_trigger = 1;
        njet = nJetNoPho;
        R2 = R2_pho;
        MR = MR_pho;
      }
      if (pass_aux_trigger) {
        if (nJetAK8>=1 && njet>=3 && MR>=800 && R2>=0.08) {
          if (d.HLT_AK8PFJet450==1 || d.HLT_PFHT1050==1) {
            h_trigger_pass  ->Fill(AK4_Ht);
            h_trigger2d_pass->Fill(AK4_Ht, d.FatJet[iJetAK8[0]].pt);
            h_trigger2d_nolep_pass->Fill(AK4_HtNoLep, d.FatJet[iJetAK8[0]].pt);
          }
          h_trigger_total   ->Fill(AK4_Ht);
          h_trigger2d_total ->Fill(AK4_Ht, d.FatJet[iJetAK8[0]].pt);
          h_trigger2d_nolep_total ->Fill(AK4_HtNoLep, d.FatJet[iJetAK8[0]].pt);
        }
      }

      // Fill Histos for the Z(nunu) estimate
      if (isData) {
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
      } else if (isBackground) {
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
      if (isData) {
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
      } else if (isBackground) {
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
      if (isData) {
        if (TString(sample).Contains("JetHT")) {
          for (size_t i=0; i<regions.size(); ++i) {
            int MRR2_bin = calc_mrr2_bin(d, regions[i]);
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
      } else if (isSignal) {
        /*
          if (apply_all_cuts('S')) {
          uint32_t mMother = TString(sample).Contains("T2tt") ? std::round(d.evt.SUSY_Stop_Mass/5.0)*5 : std::round(d.evt.SUSY_Gluino_Mass/25.0)*25;
          uint32_t mLSP    = TString(sample).Contains("T2tt") ? std::round(d.evt.SUSY_LSP_Mass /5.0)*5 : std::round(d.evt.SUSY_LSP_Mass   /25.0)*25;
          uint32_t signal_bin = mMother * 10000 + mLSP;
          int MRR2_bin = calc_mrr2_bin(d, 'S');
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
          }*/
      } else {
        // Backgrounds
        for (size_t i=0; i<regions.size(); ++i) {
          if (apply_all_cuts(regions[i])) {
            int MRR2_bin = calc_mrr2_bin(d, regions[i]);
            vvh_MRR2_bkg[i][syst_index]->Fill(MRR2_bin, sf_weight[regions[i]]);
            if (nJet>=4) {
              if (nJet<6) vvh_MRR2_bkg_nj45[i][syst_index]->Fill(MRR2_bin, sf_weight[regions[i]]);
              else        vvh_MRR2_bkg_nj6 [i][syst_index]->Fill(MRR2_bin, sf_weight[regions[i]]);
            }
            if (regions[i]=='G') {
              // Save also the direct prompt photons for G region
              // Needed for transfer factors
              /*if (d.Photon[i].isPromptDirect[iPhotonSelect[0]]==1) {
                vvh_MRR2_bkg[i+1][syst_index]->Fill(MRR2_bin, sf_weight[regions[i]]);
                if (nJet>=4) {
                if (nJet<6) vvh_MRR2_bkg_nj45[i+1][syst_index]->Fill(MRR2_bin, sf_weight[regions[i]]);
                else        vvh_MRR2_bkg_nj6 [i+1][syst_index]->Fill(MRR2_bin, sf_weight[regions[i]]);
                }
                }*/
            }
          }
        }
        // Signal regions with loosened tau32/21 requirements
#if TOP == 0
        if (apply_all_cuts_except('S',"1W")&&nWMassTag>=1) {
          int MRR2_bin = calc_mrr2_bin(d, 'S');
          vvh_MRR2_bkg[regions.size()+1][syst_index]->Fill(MRR2_bin, sf_weight['S']);
          if (nJet>=4) {
            if (nJet<6) vvh_MRR2_bkg_nj45[regions.size()+1][syst_index]->Fill(MRR2_bin, sf_weight['S']);
            else        vvh_MRR2_bkg_nj6 [regions.size()+1][syst_index]->Fill(MRR2_bin, sf_weight['S']);
          }
        }
#else
        if (apply_all_cuts_except('S',"1Top")&&nHadTopTag4>=1) {
          int MRR2_bin = calc_mrr2_bin(d, 'S');
          vvh_MRR2_bkg[regions.size()+1][syst_index]->Fill(MRR2_bin, sf_weight['S']);
          if (nJet>=4) {
            if (nJet<6) vvh_MRR2_bkg_nj45[regions.size()+1][syst_index]->Fill(MRR2_bin, sf_weight['S']);
            else        vvh_MRR2_bkg_nj6 [regions.size()+1][syst_index]->Fill(MRR2_bin, sf_weight['S']);
          }
        }
#endif
      }
    } // end of systematics
  } /*else {
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
    if (isData) {
    // Use baseline selection
    if (nJetAK8>=1 && nJet>=3 && MR>=800 && R2>=0.08) {
    if (d.HLT_AK8PFJet450==1 || d.HLT_PFHT1050==1) {
    h_npvLowHigh_data->Fill(d.PV_npvsGood);
    }
    }
    }*//* else if (isSignal) {
          if (TString(sample).Contains("T2tt")) {
          vh_npvLowHigh_signal[1]->Fill(d.evt.SUSY_Stop_Mass,   d.evt.SUSY_LSP_Mass, d.evt.NGoodVtx);
          } else {
          vh_npvLowHigh_signal[0]->Fill(d.evt.SUSY_Gluino_Mass, d.evt.SUSY_LSP_Mass, d.evt.NGoodVtx);
          }
          }
          }*/
}

//_______________________________________________________
//           Read cross-section from ntuple
double
AnalysisBase::get_xsec_from_ntuple(const std::vector<std::string>& filenames, const bool& runOnSkim)
{
  float evt_XSec=0, prev_XSec=0;
  for (const auto& filename : filenames) {
    TFile *f = TFile::Open(filename.c_str());
    TTree* tree = (TTree*)f->Get(runOnSkim ? "B2GTree" : "B2GTTreeMaker/B2GTree");
    tree->GetBranch("evt_XSec")->SetAddress(&evt_XSec);
    tree->GetEntry(0);
    f->Close();
    if (prev_XSec!=0&&prev_XSec!=evt_XSec) {
      error("AnalysisBase - Files added with different cross-sections. Please, add them separately!");
      return 0;
    }
    prev_XSec = evt_XSec;
  }
  return evt_XSec;
}

//_______________________________________________________
//           Read cross-section from txt file
std::pair<double, double>
AnalysisBase::get_xsec_totweight_from_txt_file(const std::string& txt_file)
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
      if (TString(sample).Contains(shortname)) {
        XSec = xsec;
        Totweight = totweight;
      }

    }
  }
  if (XSec == 0) {
    std::cout<<"No crossection found for "<<sample<<" in cross section file: "<<txt_file<<std::endl;
    error("Please fix the cross-section file in settings.h!");
  }

  return std::make_pair(XSec, Totweight);
}

//_______________________________________________________
//          Read total weight from ntuple histos
double
AnalysisBase::get_totweight_from_ntuple(const std::vector<std::string>& filenames, const bool& runOnSkim)
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
AnalysisBase::calc_signal_weightnorm(const std::vector<std::string>& filenames, const double& intLumi, const bool& varySystematics, TDirectory* dir, bool verbose=1)
{
  // Find the index of the current signal
  int signal_index=-1; //= TString(filenames[0]).Contains("T2tt"); // 0: Mlsp vs Mgluino - T1tttt, T1ttbb, T5ttcc, T5tttt; 1: Mlsp vs Mstop - T2tt
  string weightname;
#if YEAR == 2018
  if (TString(filenames[0]).Contains("T1tttt"))        { signal_index = 0; weightname = "data/SMS-T1tttt_TuneCP2_13TeV-madgraphMLM-pythia8_RunIIAutumn18NanoAODv5.root"; }
  else if (TString(filenames[0]).Contains("T5ttcc"))   { signal_index = 0; weightname = "data/SMS-T5ttcc_TuneCP2_13TeV-madgraphMLM-pythia8_RunIIAutumn18NanoAODv5.root"; }
  else if (TString(filenames[0]).Contains("T5qqqqVV")) { signal_index = 0; weightname = "data/SMS-T5qqqqVV_TuneCP2_13TeV-madgraphMLM-pythia8_RunIIAutumn18NanoAODv5.root"; }
  else if (TString(filenames[0]).Contains("T2tt"))     { signal_index = 1; weightname = "data/SMS-T2tt_TuneCP2_13TeV-madgraphMLM-pythia8_RunIIAutumn18NanoAODv5.root"; }
  else if (TString(filenames[0]).Contains("T2bW"))     { signal_index = 1; weightname = "data/SMS-T2bW_TuneCP2_13TeV-madgraphMLM-pythia8_RunIIAutumn18NanoAODv5.root"; }
  else if (TString(filenames[0]).Contains("TChi"))     { signal_index = 2; weightname = "data/SMS-TChiWZ_TuneCP2_13TeV-madgraphMLM-pythia8_RunIIAutumn18NanoAODv5.root"; }
#else
  if (TString(filenames[0]).Contains("T1tttt"))        { signal_index = 0; weightname = "data/SMS-T1tttt_TuneCP2_13TeV-madgraphMLM-pythia8_RunIIFall17NanoAODv4.root"; }
  else if (TString(filenames[0]).Contains("T5ttcc"))   { signal_index = 0; weightname = "data/SMS-T5ttcc_TuneCP2_13TeV-madgraphMLM-pythia8_RunIIFall17NanoAODv4.root"; }
  else if (TString(filenames[0]).Contains("T5qqqqVV")) { signal_index = 0; weightname = "data/SMS-T5qqqqVV_TuneCP2_13TeV-madgraphMLM-pythia8_RunIIFall17NanoAODv4.root"; }
  else if (TString(filenames[0]).Contains("T2tt"))     { signal_index = 1; weightname = "data/SMS-T2tt_TuneCP2_13TeV-madgraphMLM-pythia8_RunIIFall17NanoAODv4.root"; }
  else if (TString(filenames[0]).Contains("T2bW"))     { signal_index = 1; weightname = "data/SMS-T2bW_TuneCP2_13TeV-madgraphMLM-pythia8_RunIIFall17NanoAODv4.root"; }
  else if (TString(filenames[0]).Contains("TChiHH"))   { signal_index = 3; weightname = "data/SMS-TChiHH_HToBB_HToBB_TuneCP2_13TeV-madgraphMLM-pythia8_RunIIFall17NanoAODv4.root"; } //totweight_TChiHH
  else if (TString(filenames[0]).Contains("TChiWZ"))   { signal_index = 2; weightname = "data/SMS-TChiWZ_TuneCP2_13TeV-madgraphMLM-pythia8_RunIIFall17NanoAODv5.root"; }
  else if (TString(filenames[0]).Contains("TChiWH"))   { signal_index = 2; weightname = "data/SMS-TChiWH_RunIIFall17NanoAODv5.root"; }
  else if (TString(filenames[0]).Contains("T5qqqqZH")) { signal_index = 4; weightname = "data/SMS-T5qqqqZH_TuneCUETP8M1_13TeV-madgraphMLM-pythia8NanoAODv5.root"; }
  else if (TString(filenames[0]).Contains("T6bbZH"))   { signal_index = 5; weightname = "data/SMS-T6bbZH_RunIIFall17NanoAODv5.root"; } //totweight_T6bbZH
#endif

  // Merge totweight histos
  std::map<int, double> xsec_mother;
  //TFile* f = TFile::Open(filenames[0].c_str());
  TFile* f = TFile::Open(weightname.c_str());
  // Get total weight
  if (signal_index==0 || signal_index==4) {
    vh_totweight_signal[signal_index]->Add((TH2D*)f->Get("totweight_T1tttt"));
  }
  else if (signal_index==3) {
    vh_totweight_signal[signal_index]->Add((TH2D*)f->Get("totweight_TChiHH"));
  }
  else if (signal_index==5) {
    vh_totweight3D_signal[0]->Add((TH3D*)f->Get("totweight_T6bbZH"));
  } else {
    vh_totweight_signal[signal_index]->Add((TH2D*)f->Get("totweight_T2tt")); // has equivalent binning to TChiWZ
  }
  f->Close();

  // Set xsec for each gluino/stop mass bin
  // Read gluino/stop xsec from same file used in TTree step
  std::map<uint32_t, std::string> signal_bins;

  if(signal_index == 5){
    for (int binx=1, nbinx=vh_xsec3D_signal[0]->GetNbinsX(); binx<=nbinx; ++binx) {
      double mMother = vh_xsec3D_signal[0]->GetXaxis()->GetBinCenter(binx);
      xsec_mother[binx] = GetStopXSec(mMother).first; // first: mean xsec (pb), second: error (%)
      for (int biny=1, nbiny=vh_xsec3D_signal[0]->GetNbinsY(); biny<=nbiny; ++biny) {
        for (int binz=1, nbinz=vh_xsec3D_signal[0]->GetNbinsZ(); binz<=nbinz; ++binz) {
          vh_xsec3D_signal[0]->SetBinContent(binx, biny, binz, xsec_mother[binx]);
        }
      }
    }
    // Calculate weight normalization
    // weightnorm = (settings.intLumi*xsec)/totweight;
    // Divide(h1,h2,c1,c2) --> c1*h1/(c2*h2)
    vh_weightnorm3D_signal[0]->Divide(vh_xsec3D_signal[0], vh_totweight3D_signal[0], intLumi);
    if (verbose) std::cout << "Normalization variables:" << std::endl;
    for (int binx=1, nbinx=vh_xsec3D_signal[0]->GetNbinsX(); binx<=nbinx; ++binx) {
      for (int biny=1, nbiny=vh_xsec3D_signal[0]->GetNbinsY(); biny<=nbiny; ++biny) {
        for (int binz=1, nbinz=vh_xsec3D_signal[0]->GetNbinsZ(); binz<=nbinz; ++binz) {
          double mMother = vh_xsec3D_signal[0]->GetXaxis()->GetBinCenter(binx);
          double mLSP1   = vh_xsec3D_signal[0]->GetYaxis()->GetBinCenter(biny);
          double mLSP    = vh_xsec3D_signal[0]->GetZaxis()->GetBinCenter(binz);
          double xsec    = vh_xsec3D_signal[0]      ->GetBinContent(binx, biny, binz);
          double totw    = vh_totweight3D_signal[0] ->GetBinContent(binx, biny, binz);
          double wnorm   = vh_weightnorm3D_signal[0]->GetBinContent(binx, biny, binz);
          if (totw>0) {
            if (verbose) {
              std::cout<<"  Bin: M(b~)="  <<mMother<<" M(LSP2)="<<mLSP1<<" M(LSP1)="<<mLSP<<":   xsec="<<xsec<<" totweight="<<totw<<" weightnorm="<<wnorm<<std::endl;
            }
            uint32_t bin = mMother * 10000 + mLSP;
            std::stringstream ss;
            ss<<"_"<<mMother<<"_"<<mLSP;
            signal_bins[bin] = ss.str();
          }
        }
      }
    }
  }
  else {
    for (int binx=1, nbinx=vh_xsec_signal[signal_index]->GetNbinsX(); binx<=nbinx; ++binx) {
      double mMother = vh_xsec_signal[signal_index]->GetXaxis()->GetBinCenter(binx);
      xsec_mother[binx] = (signal_index==0 || signal_index==4) ? GetGluinoXSec(mMother).first : ((signal_index==1 || signal_index==5) ? GetStopXSec(mMother).first : (signal_index==3 ? GetNeutralinoXSec(mMother).first : GetCharginoXSec(mMother).first)); // first: mean xsec (pb), second: error (%)
      for (int biny=1, nbiny=vh_xsec_signal[signal_index]->GetNbinsY(); biny<=nbiny; ++biny)
        vh_xsec_signal[signal_index]->SetBinContent(binx, biny, xsec_mother[binx]);
    }
    // Calculate weight normalization
    // weightnorm = (settings.intLumi*xsec)/totweight;
    // Divide(h1,h2,c1,c2) --> c1*h1/(c2*h2)
    vh_weightnorm_signal[signal_index]->Divide(vh_xsec_signal[signal_index], vh_totweight_signal[signal_index], intLumi);
    if (verbose) std::cout << "Normalization variables:" << std::endl;
    for (int binx=1, nbinx=vh_xsec_signal[signal_index]->GetNbinsX(); binx<=nbinx; ++binx) {
      for (int biny=1, nbiny=vh_xsec_signal[signal_index]->GetNbinsY(); biny<=nbiny; ++biny) {
        double mMother = vh_xsec_signal[signal_index]->GetXaxis()->GetBinCenter(binx);
        double mLSP = vh_xsec_signal[signal_index]->GetYaxis()->GetBinCenter(biny);
        double xsec  = vh_xsec_signal[signal_index]      ->GetBinContent(binx, biny);
        double totw  = vh_totweight_signal[signal_index] ->GetBinContent(binx, biny);
        double wnorm = vh_weightnorm_signal[signal_index]->GetBinContent(binx, biny);
        if (totw>0) {
          if (verbose) {
            if (signal_index==0) std::cout<<"  Bin: M(g~)="  <<mMother<<" M(LSP)="<<mLSP<<":   xsec="<<xsec<<" totweight="<<totw<<" weightnorm="<<wnorm<<std::endl;
              if (signal_index==1) std::cout<<"  Bin: M(s~)="  <<mMother<<" M(LSP)="<<mLSP<<":   xsec="<<xsec<<" totweight="<<totw<<" weightnorm="<<wnorm<<std::endl;
            if (signal_index==2) std::cout<<"  Bin: M(chi~)="<<mMother<<" M(LSP)="<<mLSP<<":   xsec="<<xsec<<" totweight="<<totw<<" weightnorm="<<wnorm<<std::endl;
            if (signal_index==3) std::cout<<"  Bin: M(LSP2)="<<mMother<<" M(LSP)="<<mLSP<<":   xsec="<<xsec<<" totweight="<<totw<<" weightnorm="<<wnorm<<std::endl;
            if (signal_index==4) std::cout<<"  Bin: M(g~)="<<mMother<<" M(LSP2)="<<mLSP<<":   xsec="<<xsec<<" totweight="<<totw<<" weightnorm="<<wnorm<<std::endl;
          }
          uint32_t bin = mMother * 10000 + mLSP;
          std::stringstream ss;
          ss<<"_"<<mMother<<"_"<<mLSP;
          signal_bins[bin] = ss.str();
        }
      }
    }
  }

  if (varySystematics&&isSignal) {
    dir->cd();
    // Declare systematics histos for Signals
    for (const auto& bin : signal_bins) {
      m_vh_MRR2_sig     [bin.first] = std::vector<TH1D*>();
      m_vh_MRR2_sig_nj45[bin.first] = std::vector<TH1D*>();
      m_vh_MRR2_sig_nj6 [bin.first] = std::vector<TH1D*>();
      m_vh_MRR2_sig     [bin.first].push_back(new TH1D((std::string("MRR2_S_signal")+bin.second).c_str(),         ";MR/R^{2} bins (unrolled);Counts", 25,0,25));
      m_vh_MRR2_sig_nj45[bin.first].push_back(new TH1D((std::string("MRR2_S_signal")+bin.second+"_nj45").c_str(), ";MR/R^{2} bins (unrolled);Counts", 25,0,25));
      m_vh_MRR2_sig_nj6 [bin.first].push_back(new TH1D((std::string("MRR2_S_signal")+bin.second+"_nj6").c_str(),  ";MR/R^{2} bins (unrolled);Counts", 25,0,25));
      for (size_t j=0; j<syst.size(); ++j) {
        std::stringstream ss, ss45, ss6;
        ss  <<"MRR2_S_signal"<<bin.second<<"_"<<syst[j];
        ss45<<"MRR2_S_signal"<<bin.second<<"_nj45_"<<syst[j];
        ss6 <<"MRR2_S_signal"<<bin.second<<"_nj6_"<<syst[j];
        m_vh_MRR2_sig     [bin.first].push_back(new TH1D((ss.str()+"Up").c_str(),     ";MR/R^{2} bins (unrolled);Counts", 25,0,25));
        m_vh_MRR2_sig     [bin.first].push_back(new TH1D((ss.str()+"Down").c_str(),   ";MR/R^{2} bins (unrolled);Counts", 25,0,25));
        m_vh_MRR2_sig_nj45[bin.first].push_back(new TH1D((ss45.str()+"Up").c_str(),   ";MR/R^{2} bins (unrolled);Counts", 25,0,25));
        m_vh_MRR2_sig_nj45[bin.first].push_back(new TH1D((ss45.str()+"Down").c_str(), ";MR/R^{2} bins (unrolled);Counts", 25,0,25));
        m_vh_MRR2_sig_nj6 [bin.first].push_back(new TH1D((ss6.str()+"Up").c_str(),    ";MR/R^{2} bins (unrolled);Counts", 25,0,25));
        m_vh_MRR2_sig_nj6 [bin.first].push_back(new TH1D((ss6.str()+"Down").c_str(),  ";MR/R^{2} bins (unrolled);Counts", 25,0,25));
      }
    }
  }
}


//_______________________________________________________
//             Load pile-up reweighting infos
void
AnalysisBase::init_pileup_reweighting(const std::string& pileupDir, const bool& runOnSkim, const std::vector<std::string>& filenames)
{
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
AnalysisBase::get_syst_weight(const double& weight_nominal, const double& weight_up, const double& weight_down, const double& nSigma)
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
AnalysisBase::get_syst_weight(const double& weight_nominal, const double& uncertainty, const double& nSigma)
{
  double w = weight_nominal;
  // Use symmetrical difference for up/down variation
  if (nSigma!=0.) w *= 1.0 + nSigma * uncertainty;
  return w;
}

/*
std::pair<double, double>
AnalysisBase::get_signal_mass(eventBuffer& data, const int& signal_index)
{
  double m_mother=0, m_lsp=0;
  if (!isData) for(size_t i=0, nGenPart=data.GenPart.size(); i<nGenPart; ++i) {
    if (signal_index==0)      { if(std::abs(data.GenPart[i].pdgId) == 1000021) m_mother = data.GenPart[i].mass; } // gluino
    else if (signal_index==1) { if(std::abs(data.GenPart[i].pdgId) == 1000006) m_mother = data.GenPart[i].mass; } // stop
    else if (signal_index==2) { if(std::abs(data.GenPart[i].pdgId) == 1000024) m_mother = data.GenPart[i].mass; } // chargino
    else if (signal_index==3) { if(std::abs(data.GenPart[i].pdgId) == 1000023) m_mother = data.GenPart[i].mass; } // neutralino2 (chi^0_2)
    else if (signal_index==4) { if(std::abs(data.GenPart[i].pdgId) == 1000021) m_mother = data.GenPart[i].mass; } // gluino

    if (signal_index==4)      { if(std::abs(data.GenPart[i].pdgId) == 1000023) m_lsp = data.GenPart[i].mass;    } // neutralino2
    else                      { if(std::abs(data.GenPart[i].pdgId) == 1000022) m_lsp = data.GenPart[i].mass;    } // LSP neutralino (chi^0_1)
  }
  m_mother = std::round(m_mother/5)*5;
  m_lsp    = std::round(m_lsp/25)*25;
  return make_pair(m_mother, m_lsp); 
}
*/

std::vector<double>
AnalysisBase::get_signal_mass(eventBuffer& data, const int& signal_index)
{
  double m_mother=0, m_lsp=0, m_lsp2=0;
  std::vector<double> mass;
  mass.clear();
  if (isSignal) for(size_t i=0, nGenPart=data.GenPart.size(); i<nGenPart; ++i) {
    if (signal_index==0 || signal_index==4) { if(std::abs(data.GenPart[i].pdgId) == 1000021) m_mother = data.GenPart[i].mass; } // gluino
    else if (signal_index==1)               { if(std::abs(data.GenPart[i].pdgId) == 1000006) m_mother = data.GenPart[i].mass; } // stop
    else if (signal_index==2)               { if(std::abs(data.GenPart[i].pdgId) == 1000024) m_mother = data.GenPart[i].mass; } // chargino
    else if (signal_index==3)               { if(std::abs(data.GenPart[i].pdgId) == 1000023) m_mother = data.GenPart[i].mass; } // neutralino2 (chi^0_2)
    else if (signal_index==5)               { if(std::abs(data.GenPart[i].pdgId) == 1000005) m_mother = data.GenPart[i].mass; } // sb
    if (signal_index==5)                    { if(std::abs(data.GenPart[i].pdgId) == 1000023) m_lsp2   = data.GenPart[i].mass; } // neutralino2
    if (signal_index==4)                    { if(std::abs(data.GenPart[i].pdgId) == 1000023) m_lsp    = data.GenPart[i].mass; } // neutralino2
    else                                    { if(std::abs(data.GenPart[i].pdgId) == 1000022) m_lsp    = data.GenPart[i].mass; } // LSP neutralino (chi^0_1)
  }
  m_mother = std::round(m_mother/5)*5;
  m_lsp    = std::round(m_lsp/25)*25;
  m_lsp2   = std::round(m_lsp2/25)*25;

  mass.push_back(m_mother);
  mass.push_back(m_lsp);
  mass.push_back(m_lsp2);
  return mass;
}

//_______________________________________________________
//                  Top pt reweighting
double
AnalysisBase::get_toppt_weight(eventBuffer& data, const double& nSigmaToppt, const unsigned int& syst_index, const bool& runOnSkim)
{
  double w_nom = 1;//, n=0;
  if (!isData) for(size_t i=0, nGenPart=data.GenPart.size(); i<nGenPart; ++i) {
    // Select last copy of the particles only (i.e. their daughters are different)
    if (data.GenPart[i].status == 1) {
      if(std::abs(data.GenPart[i].pdgId)==6) {
        double a = 0.0615, b = -0.0005;
        w_nom *= std::exp(a + b * data.GenPart[i].pt);
        //std::cout<<"evt="<<data.evt.EventNumber<<" i="<<i<<" top id="<<data.GenPart[i].pdgId<<" dau0 id="<<data.GenPart[i].Dau0pdgId<<" dau1 id="<<data.GenPart[i].Dau1pdgId<<" pt="<<data.GenPart[i].pt[i]<<" w="<<w<<std::endl;
        //n+=1;
      }
    }
  }
  w_nom = std::sqrt(w_nom);
  //std::cout<<"N top = "<<n<<" w_nom = "<<w_nom<<std::endl<<std::endl;
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
AnalysisBase::get_isr_weight(eventBuffer& data, const double& nSigmaISR, const unsigned int& syst_index, const bool& runOnSkim)
{
  // Implementing the reweighting in this presentation:
  // https://indico.cern.ch/event/592621/contributions/2398559/attachments/1383909/2105089/16-12-05_ana_manuelf_isr.pdf
  // Using the values found on slide 8 (T2tt and T1tttt)
  double w = 1; // NanoAOD don't have ISR information, Maybe signal have them
  // ttbar ISR reweighting not needed, we do top pt reweighting!
  /*
    if (isSignal) {
    double d = TString(sample).Contains("T2tt") ? 1.121 : 1.143;
    int n = data.evt.NISRJets;
    double w = 0;
    if      (n==0) w = d;
    else if (n==1) w = d * 0.920;
    else if (n==2) w = d * 0.821;
    else if (n==3) w = d * 0.715;
    else if (n==4) w = d * 0.662;
    else if (n==5) w = d * 0.561;
    else           w = d * 0.511;
    double err = (1-w)/2;
    double w_isr_up   = w + err;
    double w_isr      = w;
    double w_isr_down = w - err;
    w = get_syst_weight(w_isr, w_isr_up, w_isr_down, nSigmaISR);
    if (syst_index==0&&!runOnSkim) {
    if (TString(sample).Contains("T2tt")) {
    vh_totweight_signal_isr[1]->Fill(data.evt.SUSY_Stop_Mass,   data.evt.SUSY_LSP_Mass, 0);
    vh_totweight_signal_isr[1]->Fill(data.evt.SUSY_Stop_Mass,   data.evt.SUSY_LSP_Mass, 1, w_isr);
    } else {
    vh_totweight_signal_isr[0]->Fill(data.evt.SUSY_Gluino_Mass, data.evt.SUSY_LSP_Mass, 0);
    vh_totweight_signal_isr[0]->Fill(data.evt.SUSY_Gluino_Mass, data.evt.SUSY_LSP_Mass, 1, w_isr);
    }
    }
    }*/
  return w;
}

//_______________________________________________________
//                  Get pile-up weight
double
AnalysisBase::get_pileup_weight(eventBuffer& data, const double& nSigmaPU, const unsigned int& syst_index, const bool& runOnSkim)
{
  if (!isSignal) {
    // Background
    int pu_bin = data.Pileup_nTrueInt+1; // eg. pileup 0, is filled in bin 1
    double w_pileup = h_pileup_weight->GetBinContent(pu_bin);
    double w_pileup_up = h_pileup_weight_up->GetBinContent(pu_bin);
    double w_pileup_down = h_pileup_weight_down->GetBinContent(pu_bin);
    double w = get_syst_weight(w_pileup, w_pileup_up, w_pileup_down, nSigmaPU);
    if (syst_index==0&&!runOnSkim) {
      h_totweight_pileup->Fill(0);
      h_totweight_pileup->Fill(1, w_pileup);
    }
    return w;
  } else {
    // Signal
    // Do not reweight, but split to a low/high pileup region
    if (nSigmaPU==1) return data.PV_npvsGood>=h_npvLowHigh_data->GetBinLowEdge(2);
    else if (nSigmaPU==-1) return data.PV_npvsGood<h_npvLowHigh_data->GetBinLowEdge(2);
    return 1;
  }
}


//____________________________________________________
//                  HT reweighting

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

double
AnalysisBase::get_ht_weight(eventBuffer& data, const double& nSigmaHT)
{
  // Using method described by Julie Hogan:
  // https://indico.cern.ch/event/508384/contributions/2029874/attachments/1255336/1852975/JetRwtIssues_B2GWkshp_040816.pdf
  // Use linear functions calculated with scripts/CalcHTScaleFactors.C macro
  // linear function(s): p0 + p1 * HT

  // Calculate unscaled jet HT
  double ht = 0;
  for(size_t i=0; i<data.FatJet.size(); ++i) ht += data.FatJet[i].pt;

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
AnalysisBase::get_alphas_weight(const std::vector<float>& alphas_Weights, const double& nSigmaAlphaS, const int& LHA_PDF_ID)
{
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
}


//_______________________________________________________
//                  Get scale weight
double
AnalysisBase::get_scale_weight(const std::vector<float>& scale_Weights, const std::vector<double>& scale_weight_norm, const double& nSigmaScale, const unsigned int& numScale)
{
  /*
    Typical LHE run info:
    <weightgroup combine="envelope" type="Central scale variation">
    <weight id="1"> mur=1 muf=1 </weight>
    <weight id="2"> mur=1 muf=2 </weight>     --> save [0]
    <weight id="3"> mur=1 muf=0.5 </weight>   --> save [1]
    <weight id="4"> mur=2 muf=1 </weight>     --> save [2]
    <weight id="5"> mur=2 muf=2 </weight>     --> save [3]
    <weight id="6"> mur=2 muf=0.5 </weight>
    <weight id="7"> mur=0.5 muf=1 </weight>   --> save [4]
    <weight id="8"> mur=0.5 muf=2 </weight>
    <weight id="9"> mur=0.5 muf=0.5 </weight> --> save [5]
    </weightgroup>

    SUSY GEN Lumi info:
    GEN:   LHE, id = 1, Central scale variation,  mur=1 muf=1
    GEN:   LHE, id = 2, Central scale variation,  mur=1 muf=2
    GEN:   LHE, id = 3, Central scale variation,  mur=1 muf=0.5
    GEN:   LHE, id = 4, Central scale variation,  mur=2 muf=1
    GEN:   LHE, id = 5, Central scale variation,  mur=2 muf=2
    GEN:   LHE, id = 6, Central scale variation,  mur=2 muf=0.5
    GEN:   LHE, id = 7, Central scale variation,  mur=0.5 muf=1
    GEN:   LHE, id = 8, Central scale variation,  mur=0.5 muf=2
    GEN:   LHE, id = 9, Central scale variation,  mur=0.5 muf=0.5

    https://github.com/jkarancs/B2GTTrees/blob/master/plugins/B2GEdmExtraVarProducer.cc#L195-L202
    We save only ids: 2,3,4,5,7,9 (in this order)

    The idea here is to randomly choose to vary mu_f or mu_r or both simulataneously
    and rescale weight difference the usual way by desired nSigma
  */
  if (nSigmaScale==0) return 1; // No systematics
  if (scale_Weights.empty()) return 1; // ST samples are known to miss scale weights
  if (scale_weight_norm.empty()) {
    error("AnalysisBase - Scale weight normalizations were not provided for this sample, rerun scripts/get_scaleweight_norm.py on unskimmed ntuple");
  }
  double w_scale = 1;
  double w_scale_up = 1;   // Corresponds to 0.5 (More signal events)
  double w_scale_down = 1; // Corresponds to 2.0 (Less signal events)
  if (numScale==1) {
    // Vary factorization scale
    // fix mu_r = 1.0, vary mu_f = 0,5, 2.0
    w_scale_up   = scale_Weights[1] / scale_weight_norm[1];
    w_scale_down = scale_Weights[0] / scale_weight_norm[0];
  } else if (numScale==2) {
    // Vary renormalization scale
    // fix mu_f = 1.0, vary mu_r = 0,5, 2.0
    w_scale_up   = scale_Weights[4] / scale_weight_norm[4];
    w_scale_down = scale_Weights[2] / scale_weight_norm[2];
  } else if (numScale==3) {
    // Vary both simulatneously
    // mu_r = mu_f = 0,5, 2.0
    w_scale_up   = scale_Weights[5] / scale_weight_norm[5];
    w_scale_down = scale_Weights[3] / scale_weight_norm[3];
  }
  w_scale = get_syst_weight(w_scale, w_scale_up, w_scale_down, nSigmaScale);
  return w_scale;
}

//_______________________________________________________
//                Benchmarking (batch) jobs

void
AnalysisBase::job_monitoring(const int& entry, const int& ifirst, const int& ilast, const std::string& curr_file, const float threshold=5)
{
  int curr_entry = entry - ifirst;
  if (curr_entry==0) {
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

//_______________________________________________________
//                Calculate scale factors

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
TGraphAsymmErrors* eff_full_muon_trk;
TGraphAsymmErrors* eff_full_muon_trk_veto;
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

TGraphAsymmErrors* eff_trigger;
TH3D* eff_3D_trigger_lep;
TH3D* eff_3D_trigger_lep_up;
TH3D* eff_3D_trigger_lep_down;
TH2D* eff_trigger_lep;
TH2D* eff_trigger_lep_up;
TH2D* eff_trigger_lep_down;
TH2D* eff_trigger_pho;
TH2D* eff_trigger_pho_up;
TH2D* eff_trigger_pho_down;
TH2D* eff_trigger_F_met;
TH2D* eff_trigger_F_mu;
TH2D* eff_trigger_F_ele;
TH2D* eff_trigger_F_pho;

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

void AnalysisBase::init_syst_input() {
  TString Sample(sample);

  // B-tagging
  // Efficiencies (Oct31 - test)
  TFile* f;
#if YEAR == 2018
  if (Sample.Contains("FastSim"))
    f = TFile::Open("btag_eff/December_03/FastSim_SMS-T5ttcc.root");
  else if (Sample.Contains("WJetsToLNu"))
    f = TFile::Open("btag_eff/August_21/WJetsToLNu.root");
  else if (Sample.Contains("TT")||Sample.Contains("ST"))
    f = TFile::Open("btag_eff/August_21/TT.root");
  else
    f = TFile::Open("btag_eff/August_21/QCD.root");
#else
  if (Sample.Contains("FastSim"))
    f = TFile::Open("btag_eff/December_03/FastSim_SMS-T5ttcc.root");
  else if (Sample.Contains("WJetsToLNu"))
    f = TFile::Open("btag_eff/August_21/WJetsToLNu.root");
  else if (Sample.Contains("TT")||Sample.Contains("ST"))
    f = TFile::Open("btag_eff/August_21/TT.root");
  else
    f = TFile::Open("btag_eff/August_21/QCD.root");
#endif
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
#if YEAR == 2018
   btag_calib_full_ = new BTagCalibration("csvv2", "scale_factors/btag/DeepCSV_102XSF_V1.csv");
#else
  btag_calib_full_ =  new BTagCalibration("csvv2", "scale_factors/btag/DeepCSV_94XSF_V3_B_F.csv");
#endif
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
#if YEAR == 2018  
  btag_calib_fast_ =  new BTagCalibration("csvv2", "scale_factors/btag/deepcsv_13TEV_18SL_7_5_2019.csv");
#else
  // This file needed minor formatting to be readable
  // sed 's;^";;;s; "\;;;;s;"";";g;' scale_factors/btag/fastsim_csvv2_ttbar_26_1_2017.csv
  btag_calib_fast_ =  new BTagCalibration("csvv2", "scale_factors/btag/deepcsv_13TEV_17SL_18_3_2019.csv");
#endif
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
  
#if YEAR == 2018  
  TFile* file = TFile::Open("scale_factors/softdrop_mass_corr/puppiCorr.root");
#else
  // Moriond17+ReReco
  TFile* file = TFile::Open("scale_factors/softdrop_mass_corr/puppiCorr.root");
#endif
  puppisd_corrGEN_      = (TF1*)((TF1*)file->Get("puppiJECcorr_gen"))->Clone();
  puppisd_corrRECO_cen_ = (TF1*)((TF1*)file->Get("puppiJECcorr_reco_0eta1v3"))->Clone();
  puppisd_corrRECO_for_ = (TF1*)((TF1*)file->Get("puppiJECcorr_reco_1v3eta2v5"))->Clone();
  file->Close();

  // Lepton scale factors
#if YEAR == 2018
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
#else
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
#endif
  // 1D Trigger efficiency
#if YEAR == 2018
#else
  TH1D* pass  = getplot_TH1D("trigger_eff/191029/SingleLepton.root", "h_HT_TrigNoMass_1", "trig01");
  TH1D* total = getplot_TH1D("trigger_eff/191029/SingleLepton.root", "h_HT_TrigNoMass_0", "trig02");
  //TH1D* pass  = getplot_TH1D("trigger_eff/191029/SingleLepton.root", "h_MET_TrigMass_1", "trig01");
  //TH1D* total = getplot_TH1D("trigger_eff/191029/SingleLepton.root", "h_MET_TrigMass_0", "trig02");
  //TH1D* pass  = getplot_TH1D("trigger_eff/191029/SingleLepton.root", "h_AK8JetMass_TrigMass_1", "trig01");
  //TH1D* total = getplot_TH1D("trigger_eff/191029/SingleLepton.root", "h_AK8JetMass_TrigMass_0", "trig02");
  eff_trigger = new TGraphAsymmErrors(pass, total, "cl=0.683 b(1,1) mode");
#endif

  // 2D Trigger Efficiency (New) - Use combination of SingleElectron + MET datasets
#if YEAR == 2018
  TH2D* lep_pass_2d  = getplot_TH2D("trigger_eff/SingleMuonTriggerEff2018_v190804.root",   "h_HT_MET_TriggerEff_1",  "trig11");
  TH2D* lep_total_2d = getplot_TH2D("trigger_eff/SingleMuonTriggerEff2018_v190804.root",   "h_HT_MET_TriggerEff_0",  "trig12");  
#else  
  TH2D* lep_pass_2d  = getplot_TH2D("trigger_eff/191029/SingleLepton.root",   "h_HT_MET_TrigNoMass_1",  "trig03");
  TH2D* lep_total_2d = getplot_TH2D("trigger_eff/191029/SingleLepton.root",   "h_HT_MET_TrigNoMass_0",  "trig04");
#endif

  eff_trigger_lep      = (TH2D*)lep_total_2d->Clone("eff_trigger_lep");      eff_trigger_lep     ->Reset();
  eff_trigger_lep_up   = (TH2D*)lep_total_2d->Clone("eff_trigger_lep_up");   eff_trigger_lep_up  ->Reset();
  eff_trigger_lep_down = (TH2D*)lep_total_2d->Clone("eff_trigger_lep_down"); eff_trigger_lep_down->Reset();

  for (int i=1; i<lep_total_2d->GetNbinsX()+1; i++) for (int j=1; j<lep_total_2d->GetNbinsY()+1; j++) {
    int lep_pass = lep_pass_2d->GetBinContent(i,j), lep_total = lep_total_2d->GetBinContent(i,j);
    if (lep_total>0) {
      TH1D p("p","",1,0,1); p.SetBinContent(1,lep_pass);  p.SetBinError(1,std::sqrt(lep_pass));
      TH1D t("t","",1,0,1); t.SetBinContent(1,lep_total); t.SetBinError(1,std::sqrt(lep_total));
      double eff = 0, err_up = 0, err_down = 0;
      geteff_AE(TGraphAsymmErrors(&p,&t), 0, eff, err_up, err_down);
      //std::cout<<"Trigger efficiency: "<<i<<" "<<j<<" "<<eff-err_down<<" "<<eff<<" "<<eff+err_up<<std::endl;
      eff_trigger_lep     ->SetBinContent(i,j,eff);
      eff_trigger_lep_up  ->SetBinContent(i,j,eff+err_up);
      eff_trigger_lep_down->SetBinContent(i,j,eff-err_down);
      // SPECIAL: Set error to the total counts, so we know if a bin is not empty
      eff_trigger_lep     ->SetBinError(i,j,lep_total);
    }
  }

#if YEAR == 2018
  TH2D* pho_pass_2d  = getplot_TH2D("trigger_eff/EGammaTriggerEff2019_v20190906.root",   "h_HT_MET_TriggerEff_1",   "trig7");
  TH2D* pho_total_2d = getplot_TH2D("trigger_eff/EGammaTriggerEff2019_v20190906.root",   "h_HT_MET_TriggerEff_0",  "trig8");
#else
  TH2D* pho_pass_2d  = getplot_TH2D("trigger_eff/191029/SinglePhoton.root",   "h_HT_MET_TrigNoMass_1",  "trig11");
  TH2D* pho_total_2d = getplot_TH2D("trigger_eff/191029/SinglePhoton.root",   "h_HT_MET_TrigNoMass_0",  "trig12");
#endif  

  eff_trigger_pho      = (TH2D*)pho_total_2d->Clone("eff_trigger_pho");      eff_trigger_pho     ->Reset();
  eff_trigger_pho_up   = (TH2D*)pho_total_2d->Clone("eff_trigger_pho_up");   eff_trigger_pho_up  ->Reset();
  eff_trigger_pho_down = (TH2D*)pho_total_2d->Clone("eff_trigger_pho_down"); eff_trigger_pho_down->Reset();

  for (int i=1; i<pho_total_2d->GetNbinsX()+1; i++) for (int j=1; j<pho_total_2d->GetNbinsY()+1; j++) {
    int pho_pass = pho_pass_2d->GetBinContent(i,j), pho_total = pho_total_2d->GetBinContent(i,j);
    if (pho_total>0) {
      TH1D p("p","",1,0,1); p.SetBinContent(1,pho_pass);  p.SetBinError(1,std::sqrt(pho_pass));
      TH1D t("t","",1,0,1); t.SetBinContent(1,pho_total); t.SetBinError(1,std::sqrt(pho_total));
      double eff = 0, err_up = 0, err_down = 0;
      geteff_AE(TGraphAsymmErrors(&p,&t), 0, eff, err_up, err_down);
      //std::cout<<"Trigger efficiency: "<<i<<" "<<j<<" "<<eff-err_down<<" "<<eff<<" "<<eff+err_up<<std::endl;
      eff_trigger_pho     ->SetBinContent(i,j,eff);
      eff_trigger_pho_up  ->SetBinContent(i,j,eff+err_up);
      eff_trigger_pho_down->SetBinContent(i,j,eff-err_down);
      // SPECIAL: Set error to the total counts, so we know if a bin is not empty
      eff_trigger_pho     ->SetBinError(i,j,pho_total);
    }
  }

  // 3D Trigger Efficiency 
#if YEAR == 2018
#else
  TH3D* lep_pass_3d   = getplot_TH3D("trigger_eff/191029/SingleLepton.root",   "h_HT_MET_AK8JetMass_TrigNoMass_1",  "trig21");
  TH3D* lep_total_3d  = getplot_TH3D("trigger_eff/191029/SingleLepton.root",   "h_HT_MET_AK8JetMass_TrigNoMass_0",  "trig22");

  eff_3D_trigger_lep       = (TH3D*)lep_total_3d ->Clone("eff_3D_trigger_lep");       eff_3D_trigger_lep      ->Reset();
  eff_3D_trigger_lep_up    = (TH3D*)lep_total_3d ->Clone("eff_3D_trigger_lep_up");    eff_3D_trigger_lep_up   ->Reset();
  eff_3D_trigger_lep_down  = (TH3D*)lep_total_3d ->Clone("eff_3D_trigger_lep_down");  eff_3D_trigger_lep_down ->Reset();

  for (int i=1; i<lep_total_3d->GetNbinsX()+1; i++) {
    for (int j=1; j<lep_total_3d->GetNbinsY()+1; j++) {
      for (int k=1; k<lep_total_3d->GetNbinsZ()+1; k++) {
        int lep_pass = lep_pass_3d->GetBinContent(i,j,k), lep_total = lep_total_3d->GetBinContent(i,j,k);
        if (lep_total>0) {
          TH1D p("p","",1,0,1); p.SetBinContent(1,lep_pass);  p.SetBinError(1,std::sqrt(lep_pass));
          TH1D t("t","",1,0,1); t.SetBinContent(1,lep_total); t.SetBinError(1,std::sqrt(lep_total));
          double eff = 0, err_up = 0, err_down = 0;
          geteff_AE(TGraphAsymmErrors(&p,&t), 0, eff, err_up, err_down);
          //std::cout<<"Trigger efficiency: "<<i<<" "<<j<<" "<<eff-err_down<<" "<<eff<<" "<<eff+err_up<<std::endl;
          eff_3D_trigger_lep     ->SetBinContent(i,j,k,eff);
          eff_3D_trigger_lep_up  ->SetBinContent(i,j,k,eff+err_up);
          eff_3D_trigger_lep_down->SetBinContent(i,j,k,eff-err_down);
          // SPECIAL: Set error to the total counts, so we know if a bin is not empty
          eff_3D_trigger_lep     ->SetBinError(i,j,k,lep_total);
        }
      }
    }
  }
#endif

  // Same trigger efficiencies but in the F region (needed for fake rates)
#if YEAR == 2018
  const char* fin = "trigger_eff/FakeRates2018.root";
#else
  const char* fin = "trigger_eff/Dec02_Golden_JSON/F_Region.root";
#endif
  eff_trigger_F_met = getplot_TH2D(fin, "met", "trig_f_met");
  eff_trigger_F_mu  = getplot_TH2D(fin, "mu",  "trig_f_mu");
  eff_trigger_F_ele = getplot_TH2D(fin, "ele", "trig_f_ele");
  eff_trigger_F_pho = getplot_TH2D(fin, "pho", "trig_f_pho");

  // W/Top (anti-/mass-)tag (and fake rate) scale factors
  // From Changgi
  //    eff_fast_bW           = getplot_TH1D("scale_factors/w_top_tag/fastsim/FullFastSimTagSF_BarrelEndcap.root", "bWFF",    "fast_bW");
  //    eff_fast_eW           = getplot_TH1D("scale_factors/w_top_tag/fastsim/FullFastSimTagSF_BarrelEndcap.root", "eWFF",    "fast_eW");
  //    eff_fast_bTop         = getplot_TH1D("scale_factors/w_top_tag/fastsim/FullFastSimTagSF_BarrelEndcap.root", "bTopFF",  "fast_bTop");
  //    eff_fast_eTop         = getplot_TH1D("scale_factors/w_top_tag/fastsim/FullFastSimTagSF_BarrelEndcap.root", "eTopFF",  "fast_eTop");
  // From Janos
  /*
  //eff_full_fake_bW      = getplot_TGraphAsymmErrors("scale_factors/w_top_tag/WTopTagSF_Janos.root",                             "bW",      "full_fake_W_barrel");
  //eff_full_fake_eW      = getplot_TGraphAsymmErrors("scale_factors/w_top_tag/WTopTagSF_Janos.root",                             "eW",      "full_fake_W_endcap");
  //eff_full_fake_bm0bW   = getplot_TGraphAsymmErrors("scale_factors/w_top_tag/WTopTagSF_Janos.root",                             "bm0bW",   "full_fake_m0bW_barrel");
  //eff_full_fake_em0bW   = getplot_TGraphAsymmErrors("scale_factors/w_top_tag/WTopTagSF_Janos.root",                             "em0bW",   "full_fake_m0bW_endcap");
  //eff_full_fake_baW     = getplot_TGraphAsymmErrors("scale_factors/w_top_tag/WTopTagSF_Janos.root",                             "baW",     "full_fake_aW_barrel");
  //eff_full_fake_eaW     = getplot_TGraphAsymmErrors("scale_factors/w_top_tag/WTopTagSF_Janos.root",                             "eaW",     "full_fake_aW_endcap");
  //eff_full_fake_bTop    = getplot_TGraphAsymmErrors("scale_factors/w_top_tag/WTopTagSF_Janos.root",                             "bTop",    "full_fake_Top_barrel");
  //eff_full_fake_eTop    = getplot_TGraphAsymmErrors("scale_factors/w_top_tag/WTopTagSF_Janos.root",                             "eTop",    "full_fake_Top_endcap");
  //eff_full_fake_bmTop   = getplot_TGraphAsymmErrors("scale_factors/w_top_tag/WTopTagSF_Janos.root",                             "bmTop",   "full_fake_mTop_barrel");
  //eff_full_fake_emTop   = getplot_TGraphAsymmErrors("scale_factors/w_top_tag/WTopTagSF_Janos.root",                             "emTop",   "full_fake_mTop_endcap");
  //eff_full_fake_bm0bTop = getplot_TGraphAsymmErrors("scale_factors/w_top_tag/WTopTagSF_Janos.root",                             "bm0bTop", "full_fake_0bmTop_barrel");
  //eff_full_fake_em0bTop = getplot_TGraphAsymmErrors("scale_factors/w_top_tag/WTopTagSF_Janos.root",                             "em0bTop", "full_fake_0bmTop_endcap");
  //eff_full_fake_baTop   = getplot_TGraphAsymmErrors("scale_factors/w_top_tag/WTopTagSF_Janos.root",                             "baTop",   "full_fake_aTop_barrel");
  //eff_full_fake_eaTop   = getplot_TGraphAsymmErrors("scale_factors/w_top_tag/WTopTagSF_Janos.root",                             "eaTop",   "full_fake_aTop_endcap");
  */
#if YEAR == 2018
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
#else
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
#endif
}


double AnalysisBase::calc_top_tagging_sf(eventBuffer& data, const double& nSigmaTopTagSF, const double& nSigmaTopTagFastSimSF,
                                         const double& nSigmaTopMisTagSF, const double& nSigmaTopMisTagFastSimSF, const bool& isFastSim) {
  double w = 1;
  for (size_t i=0; i<data.FatJet.size(); ++i) {
    if( data.FatJet[i].pt          >= 400 &&
        std::abs(data.FatJet[i].eta)  <  2.4 &&
        data.FatJet[i].msoftdrop >= 105 &&
        data.FatJet[i].msoftdrop <  210 &&
        data.FatJet[i].tau3/data.FatJet[i].tau2 < 0.46) {
      // Gen-matched tags
      if (ak8MatchGenHadTop[i]) {
        // Use POG scale factor for tag
        w *= get_syst_weight(HADTOP_TAG_SF, HADTOP_TAG_SF+HADTOP_TAG_SF_ERR_UP, HADTOP_TAG_SF-HADTOP_TAG_SF_ERR_DOWN, nSigmaTopTagSF);
        // Additionally use our scale factors for FastSim
        if (isFastSim) {
          //double eff, err;
          double eff, err_up, err_down;
          if (std::abs(data.FatJet[i].eta)<1.5) {
            //geteff1D(eff_fast_bTop, data.FatJet[i].pt, eff, err);
            geteff_AE(eff_fast_bTop, data.FatJet[i].pt, eff, err_up, err_down);
          } else {
            //geteff1D(eff_fast_eTop, data.FatJet[i].pt, eff, err);
            geteff_AE(eff_fast_eTop, data.FatJet[i].pt, eff, err_up, err_down);
          }
          //w *= get_syst_weight(eff, eff+err, eff-err, nSigmaTopTagFastSimSF);
          w *= get_syst_weight(eff, eff+err_up, eff-err_down, nSigmaTopTagFastSimSF);
        }
      } else {
        // Mis-tags: Top tagging fake rate scale factor
        double eff, err;
        double err_up, err_down;
        //double eff, err_up, err_down;
        /*
          if (std::abs(data.FatJet[i].eta)<1.5) {
          geteff1D(eff_full_fake_bTop, data.FatJet[i].pt, eff, err);
          //geteff_AE(eff_full_fake_bTop, data.FatJet[i].pt, eff, err_up, err_down);
          } else {
          geteff1D(eff_full_fake_eTop, data.FatJet[i].pt, eff, err);
          //geteff_AE(eff_full_fake_eTop, data.FatJet[i].pt, eff, err_up, err_down);
          }
          //w *= get_syst_weight(eff, eff+err, eff-err, nSigmaTopMisTagSF);
          */

        double pT = (data.FatJet[i].pt > 1000 ? 1000 : data.FatJet[i].pt);
        geteff1D(eff_full_POG_Top, pT, eff, err);
        geteff1D(eff_full_POG_Top_up, pT, err_up, err);
        geteff1D(eff_full_POG_Top_down, pT, err_down, err);
        w *= get_syst_weight(eff, err_up, err_down, nSigmaTopMisTagSF);
        //w *= get_syst_weight(eff, eff+err_up, eff-err_down, nSigmaTopMisTagSF);
        if (isFastSim) {
          if (std::abs(data.FatJet[i].eta)<1.5) {
            geteff_AE(eff_fast_fake_bTop, data.FatJet[i].pt, eff, err_up, err_down);
          } else {
            geteff_AE(eff_fast_fake_eTop, data.FatJet[i].pt, eff, err_up, err_down);
          }
          w *= get_syst_weight(eff, eff+err_up, eff-err_down, nSigmaTopMisTagFastSimSF);
        }
      }
    }
  }

  return w;
}

double AnalysisBase::calc_fake_top_0b_mass_tagging_sf(eventBuffer& data, const double& nSigmaTop0BMassTagSF) {
  double w = 1;
  if (nGenTop==0) for (size_t i=0; i<data.FatJet.size(); ++i) {
    if( data.FatJet[i].pt          >= 400 &&
        std::abs(data.FatJet[i].eta)  <  2.4 &&
        data.FatJet[i].msoftdrop >= 105 &&
        data.FatJet[i].msoftdrop <  210 ) {
      TLorentzVector AK8_v4; AK8_v4.SetPtEtaPhiM(data.FatJet[i].pt, data.FatJet[i].eta, data.FatJet[i].phi, data.FatJet[i].mass);
      float minDeltaR_W_b = 9999;
      for(size_t j=0; j<data.Jet.size(); ++j) {
        TLorentzVector AK4_v4; AK4_v4.SetPtEtaPhiM(data.Jet[j].pt, data.Jet[j].eta, data.Jet[j].phi, data.Jet[j].mass);
        if( (data.Jet[i].jetId == 2 || data.Jet[i].jetId == 6 )&&
            data.Jet[i].pt         > JET_AK4_PT_CUT &&
            //data.Jet[i].chHEF > 0.05 && data.Jet[i].neHEF < 0.8 && data.Jet[i].neEmEF < 0.7 &&
            data.Jet[i].btagDeepB >= 0.4941 &&
            std::abs(data.Jet[i].eta)  <  2.4 ) {
          double dR = AK4_v4.DeltaR(AK8_v4);
          if (dR<minDeltaR_W_b) minDeltaR_W_b = dR;
        }
      }
      if(minDeltaR_W_b <= 0.8) continue;
      double eff, err;
      //double eff, err_up, err_down;
      if (std::abs(data.FatJet[i].eta)<1.5) {
        geteff1D(eff_full_fake_bm0bTop, data.FatJet[i].pt, eff, err);
        //geteff_AE(eff_full_fake_bm0bTop, data.FatJet[i].pt, eff, err_up, err_down);
      } else {
        geteff1D(eff_full_fake_em0bTop, data.FatJet[i].pt, eff, err);
        //geteff_AE(eff_full_fake_em0bTop, data.FatJet[i].pt, eff, err_up, err_down);
      }
      w *= get_syst_weight(eff, eff+err, eff-err, nSigmaTop0BMassTagSF);
      //w *= get_syst_weight(eff, eff+err_up, eff-err_down, nSigmaTop0BMassTagSF);
    }
  }

  return w;
}

double AnalysisBase::calc_fake_top_mass_tagging_sf(eventBuffer& data, const double& nSigmaTopMassTagSF) {
  double w = 1;
  if (nGenTop==0) for (size_t i=0; i<data.FatJet.size(); ++i) {
    if( data.FatJet[i].pt          >= 400 &&
        std::abs(data.FatJet[i].eta)  <  2.4 &&
        data.FatJet[i].msoftdrop >= 105 &&
        data.FatJet[i].msoftdrop <  210) {
      double eff, err;
      // double eff, err_up, err_down;
      if (std::abs(data.FatJet[i].eta)<1.5) {
        geteff1D(eff_full_fake_bmTop, data.FatJet[i].pt, eff, err);
        //geteff_AE(eff_full_fake_bmTop, data.FatJet[i].pt, eff, err_up, err_down);
      } else {
        geteff1D(eff_full_fake_emTop, data.FatJet[i].pt, eff, err);
        //geteff_AE(eff_full_fake_emTop, data.FatJet[i].pt, eff, err_up, err_down);
      }
      w *= get_syst_weight(eff, eff+err, eff-err, nSigmaTopMassTagSF);
      //w *= get_syst_weight(eff, eff+err_up, eff-err_down, nSigmaTopMassTagSF);
    }
  }

  return w;
}

double AnalysisBase::calc_fake_top_anti_tagging_sf(eventBuffer& data, const double& nSigmaTopAntiTagSF) {
  double w = 1;
  if (nGenTop==0) for (size_t i=0; i<data.FatJet.size(); ++i) {
    if( data.FatJet[i].pt          >= 400 &&
        std::abs(data.FatJet[i].eta)  <  2.4 &&
        data.FatJet[i].msoftdrop >= 105 &&
        data.FatJet[i].msoftdrop <  210 &&
        data.FatJet[i].tau3/data.FatJet[i].tau2 >= 0.46) {
      double eff, err;
      //double eff, err_up, err_down;
      if (std::abs(data.FatJet[i].eta)<1.5) {
        geteff1D(eff_full_fake_baTop, data.FatJet[i].pt, eff, err);
        //geteff_AE(eff_full_fake_baTop, data.FatJet[i].pt, eff, err_up, err_down);
      } else {
        geteff1D(eff_full_fake_eaTop, data.FatJet[i].pt, eff, err);
        //geteff_AE(eff_full_fake_eaTop, data.FatJet[i].pt, eff, err_up, err_down);
      }
      w *= get_syst_weight(eff, eff+err, eff-err, nSigmaTopAntiTagSF);
      //w *= get_syst_weight(eff, eff+err_up, eff-err_down, nSigmaTopAntiTagSF);
    }
  }

  return w;
}

double AnalysisBase::calc_w_tagging_sf(eventBuffer& data, const double& nSigmaWTagSF, const double& nSigmaWTagFastSimSF,
                                       const double& nSigmaWMisTagSF, const double& nSigmaWMisTagFastSimSF, const bool& isFastSim) {
  double w = 1.0;
  // New method
  for (size_t i=0; i<data.FatJet.size(); ++i) {
    bool GenW = false;
    if( data.FatJet[i].pt          >= 200 &&
        std::abs(data.FatJet[i].eta)  <  2.4 &&
        data.FatJet[i].msoftdrop >= 65 &&
        data.FatJet[i].msoftdrop <  105 &&
        data.FatJet[i].tau2/data.FatJet[i].tau1 < 0.45) {
      TLorentzVector wtag_v4; wtag_v4.SetPtEtaPhiM(data.FatJet[i].pt, data.FatJet[i].eta, data.FatJet[i].phi, data.FatJet[i].mass);
      double dR = 9999;
      if (!isData) for(size_t j=0, nGenPart=data.GenPart.size(); j<nGenPart; ++j) {
        if ( std::abs(data.GenPart[j].pdgId)==24 ) {
          TLorentzVector genw_v4; genw_v4.SetPtEtaPhiM(data.GenPart[j].pt, data.GenPart[j].eta, data.GenPart[j].phi, data.GenPart[j].mass);
          dR = genw_v4.DeltaR(wtag_v4);
          if (dR<0.8) GenW = true;
        }
      }
      if (GenW) {
        // Use POG scale factor for efficiency scale factor
        w *= get_syst_weight(W_TAG_HP_SF, W_TAG_HP_SF_ERR, nSigmaWTagSF);
        // Additionally use our scale factors for FastSim
        if (isFastSim) {
          //double eff, err;
          double eff, err_up, err_down;
          if (std::abs(data.FatJet[i].eta)<1.5) {
            //geteff1D(eff_fast_bW, data.FatJet[i].pt, eff, err);
            geteff_AE(eff_fast_bW, data.FatJet[i].pt, eff, err_up, err_down);
          } else {
            //geteff1D(eff_fast_eW, data.FatJet[i].pt, eff, err);
            geteff_AE(eff_fast_eW, data.FatJet[i].pt, eff, err_up, err_down);
          }
          //w *= get_syst_weight(eff, eff+err, eff-err, nSigmaWTagFastSimSF);
          w *= get_syst_weight(eff, eff+err_up, eff-err_down, nSigmaWTagFastSimSF);
        }
      } else  {
        // W tagging fake rate scale factor
        double eff, err;
        double err_up, err_down;
        //double eff, err_up, err_down;
        /*
          if (std::abs(data.FatJet[i].eta)<1.5) {
          geteff1D(eff_full_fake_bW, data.FatJet[i].pt, eff, err);
          //geteff_AE(eff_full_fake_bW, data.FatJet[i].pt, eff, err_up, err_down);
          } else {
          geteff1D(eff_full_fake_eW, data.FatJet[i].pt, eff, err);
          //geteff_AE(eff_full_fake_eW, data.FatJet[i].pt, eff, err_up, err_down);
          }
        */
        double pT = (data.FatJet[i].pt > 500 ? 500 : data.FatJet[i].pt);
        geteffGE(eff_full_POG_W, pT, eff, err);
        w *= get_syst_weight(eff, eff+err, eff-err, nSigmaWMisTagSF);
        //w *= get_syst_weight(eff, eff+err_up, eff-err_down, nSigmaWMisTagSF);
        if (isFastSim) {
          if (std::abs(data.FatJet[i].eta)<1.5) {
            geteff_AE(eff_fast_fake_bW, data.FatJet[i].pt, eff, err_up, err_down);
          } else {
            geteff_AE(eff_fast_fake_eW, data.FatJet[i].pt, eff, err_up, err_down);
          }
          w *= get_syst_weight(eff, eff+err_up, eff-err_down, nSigmaWMisTagFastSimSF);
        }
      }
      GenW = false;
    } else if( data.FatJet[i].pt          >= 200 &&
               std::abs(data.FatJet[i].eta)  <  2.4 &&
               data.FatJet[i].msoftdrop >= 65 &&
               data.FatJet[i].msoftdrop <  105 &&
               data.FatJet[i].tau2/data.FatJet[i].tau1 >= 0.45) {
      TLorentzVector wtag_v4; wtag_v4.SetPtEtaPhiM(data.FatJet[i].pt, data.FatJet[i].eta, data.FatJet[i].phi, data.FatJet[i].mass);
      double dR = 9999;
      if (!isData) for(size_t j=0, nGenPart=data.GenPart.size(); j<nGenPart; ++j) {
        if ( std::abs(data.GenPart[j].pdgId)==24 ) {
          TLorentzVector genw_v4; genw_v4.SetPtEtaPhiM(data.GenPart[j].pt, data.GenPart[j].eta, data.GenPart[j].phi, data.GenPart[j].mass);
          dR = genw_v4.DeltaR(wtag_v4);
          if (dR<0.8) GenW = true;
        }
      }
      if (GenW) w *= get_syst_weight(W_TAG_LP_SF, W_TAG_LP_SF_ERR, nSigmaWTagSF);
    }
  }
  return w;
}

double AnalysisBase::calc_fake_w_mass_tagging_sf(eventBuffer& data, const double& nSigmaWMassTagSF) {
  double w = 1.0;

  for (size_t i=0; i<data.FatJet.size(); ++i) {
    bool GenW = false;
    if( data.FatJet[i].pt          >= 200 &&
        std::abs(data.FatJet[i].eta)  <  2.4 &&
        data.FatJet[i].msoftdrop >= 65 &&
        data.FatJet[i].msoftdrop <  105 &&
        data.FatJet[i].tau2/data.FatJet[i].tau1 < 0.45) {
      if (!isData) for(size_t j=0, nGenPart=data.GenPart.size(); j<nGenPart; ++j) {
        if ( std::abs(data.GenPart[j].pdgId)==24 ) GenW = true;
      }
      if (!GenW) {
        double eff, err;
        //double eff, err_up, err_down;
        if (std::abs(data.FatJet[i].eta)<1.5) {
          geteff1D(eff_full_fake_bm0bW, data.FatJet[i].pt, eff, err);
          //geteff_AE(eff_full_fake_bm0bW, data.FatJet[i].pt, eff, err_up, err_down);
        } else {
          geteff1D(eff_full_fake_em0bW, data.FatJet[i].pt, eff, err);
          //geteff_AE(eff_full_fake_em0bW, data.FatJet[i].pt, eff, err_up, err_down);
        }
        w *= get_syst_weight(eff, eff+err, eff-err, nSigmaWMassTagSF);
        //w *= get_syst_weight(eff, eff+err_up, eff-err_down, nSigmaWMassTagSF);
      }
    }
  }

  return w;
}

double AnalysisBase::calc_fake_w_anti_tagging_sf(eventBuffer& data, const double& nSigmaWAntiTagSF) {
  double w = 1.0;

  for (size_t i=0; i<data.FatJet.size(); ++i) {
    if( data.FatJet[i].pt          >= 200 &&
        std::abs(data.FatJet[i].eta)  <  2.4 &&
        data.FatJet[i].msoftdrop >= 65 &&
        data.FatJet[i].msoftdrop <  105) {
      double eff, err;
      //double eff, err_up, err_down;
      if (std::abs(data.FatJet[i].eta)<1.5) {
        geteff1D(eff_full_fake_baW, data.FatJet[i].pt, eff, err);
        //geteff_AE(eff_full_fake_baW, data.FatJet[i].pt, eff, err_up, err_down);
      } else {
        geteff1D(eff_full_fake_eaW, data.FatJet[i].pt, eff, err);
        //geteff_AE(eff_full_fake_eaW, data.FatJet[i].pt, eff, err_up, err_down);
      }
      w *= get_syst_weight(eff, eff+err, eff-err, nSigmaWAntiTagSF);
      //w *= get_syst_weight(eff, eff+err_up, eff-err_down, nSigmaWAntiTagSF);
    }
  }

  return w;
}


std::pair<double, double> AnalysisBase::calc_b_tagging_sf(eventBuffer& data, const double& nSigmaBTagSF, const double& nSigmaBTagFastSimSF,  const bool& isFastSim) {

  double pMC_loose = 1, pData_loose = 1;
  double pMC_medium = 1, pData_medium = 1;
  for(size_t i=0; i<data.Jet.size(); ++i) {
    float pt = data.Jet[i].pt, eta = data.Jet[i].eta;
    // Jet ID
    if ( (data.Jet[i].jetId == 2 || data.Jet[i].jetId == 6 )&&
         pt         >= JET_AK4_PT_CUT &&
         //data.Jet[i].chHEF > 0.05 && data.Jet[i].neHEF < 0.8 && data.Jet[i].neEmEF < 0.7 &&
         std::abs(eta)  <  JET_AK4_ETA_CUT ) {

      // Btag efficiencies (quark flavour dependent)
      BTagEntry::JetFlavor FLAV;
      double eff_medium = 1.0, eff_loose = 1.0;
      if (data.Jet[i].hadronFlavour==5) {
        FLAV = BTagEntry::FLAV_B;
        eff_loose  = geteff1D(eff_btag_b_loose,  pt, false);
        eff_medium = geteff1D(eff_btag_b_medium, pt, false);
      } else if (data.Jet[i].hadronFlavour==4) {
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

      double sf_loose       = get_syst_weight(sf_loose_cen,  sf_loose_up,  sf_loose_down,  nSigmaBTagSF);
      double sf_medium      = get_syst_weight(sf_medium_cen, sf_medium_up, sf_medium_down, nSigmaBTagSF);

      // FastSim
      if (isFastSim) {
        sf_loose_cen   = btag_sf_fast_loose_ ->eval_auto_bounds("central", FLAV, eta, pt);
        sf_loose_up    = btag_sf_fast_loose_ ->eval_auto_bounds("up",      FLAV, eta, pt);
        sf_loose_down  = btag_sf_fast_loose_ ->eval_auto_bounds("down",    FLAV, eta, pt);
        sf_medium_cen  = btag_sf_fast_medium_->eval_auto_bounds("central", FLAV, eta, pt);
        sf_medium_up   = btag_sf_fast_medium_->eval_auto_bounds("up",      FLAV, eta, pt);
        sf_medium_down = btag_sf_fast_medium_->eval_auto_bounds("down",    FLAV, eta, pt);

        sf_loose      *= get_syst_weight(sf_loose_cen,  sf_loose_up,  sf_loose_down,  nSigmaBTagFastSimSF);
        sf_medium     *= get_syst_weight(sf_medium_cen, sf_medium_up, sf_medium_down, nSigmaBTagFastSimSF);
      }

      // Working points
      if (data.Jet[i].btagDeepB >= B_CSV_LOOSE_CUT) {
        pMC_loose   *= eff_loose;
        pData_loose *= eff_loose * sf_loose;
      } else {
        pMC_loose   *= 1 - eff_loose;
        pData_loose *= 1 - eff_loose * sf_loose;
      }

      if (data.Jet[i].btagDeepB >= B_CSV_MEDIUM_CUT) {
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

std::tuple<double, double, double> AnalysisBase::calc_ele_sf(eventBuffer& data, const double& nSigmaEleRecoSF, const double& nSigmaEleIDSF, const double& nSigmaEleIsoSF, const double& nSigmaEleFastSimSF,const bool& isFastSim) {
  double reco_sf, reco_sf_err, sf, sf_err;
  double weight_veto  = 1.0, weight_loose = 1.0, weight_select = 1.0;
  for (size_t i=0; i<data.Electron.size(); ++i) {
    double pt      = data.Electron[i].pt;
    double eta     = data.Electron[i].eta;
    float abseta   = std::abs(eta);
    float miniIso  = data.Electron[i].miniPFRelIso_all;
    float absd0    = std::abs(data.Electron[i].dxy);
    float absdz    = std::abs(data.Electron[i].dz);

    bool id_veto_noiso   = (data.Electron[i].cutBased >= 1.0);
#if INC == 1
    float mva = data.Electron[i].mvaFall17V2noIso_WPL;
    float mva2 = (data.Electron[i].mvaTTH); // deneme
    float etasc = std::abs(data.Electron[i].deltaEtaSC + data.Electron[i].eta);  // supercluster for inclusive(nanoaod)
#else
    bool id_loose_noiso = (data.Electron[i].mvaFall17V2noIso_WPL == 1.0);
#endif

    bool id_select_noiso = (data.Electron[i].mvaFall17V2noIso_WP90 == 1.0);
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
    if ( id_veto_noiso &&
         pt      >= ELE_VETO_PT_CUT &&
         abseta  <  ELE_VETO_ETA_CUT && !(abseta>=1.442 && abseta< 1.556) &&
         absd0   <  ELE_VETO_IP_D0_CUT &&
         absdz   <  ELE_VETO_IP_DZ_CUT ) {
      //geteff2D(eff_full_ele_vetoid, pt, eta, sf, sf_err);
      geteff2D(eff_full_ele_mvalooseid_tightip2d, pt, eta, sf, sf_err);
      weight_veto *= get_syst_weight(sf, sf_err, nSigmaEleIDSF);
      if (isFastSim) {
        geteff2D(eff_fast_ele_mvalooseid_tightip2d, pt, eta, sf, sf_err);
        weight_veto *= sf;
      }
      if ( miniIso <  ELE_VETO_MINIISO_CUT ) {
        // Apply Iso scale factor
        if (ELE_VETO_MINIISO_CUT == 0.1)
          geteff2D(eff_full_ele_miniiso01, pt, eta, sf, sf_err);
        else if (ELE_VETO_MINIISO_CUT == 0.2)
          geteff2D(eff_full_ele_miniiso02, pt, eta, sf, sf_err);
        else if (ELE_VETO_MINIISO_CUT == 0.4)
          geteff2D(eff_full_ele_miniiso04, pt, eta, sf, sf_err);
        weight_veto *= get_syst_weight(sf, sf_err, nSigmaEleIsoSF);
        if (isFastSim) {
          if (ELE_VETO_MINIISO_CUT == 0.1)
            geteff2D(eff_fast_ele_miniiso01, pt, eta, sf, sf_err);
          else if (ELE_VETO_MINIISO_CUT == 0.2)
            geteff2D(eff_fast_ele_miniiso02, pt, eta, sf, sf_err);
          else if (ELE_VETO_MINIISO_CUT == 0.4)
            geteff2D(eff_fast_ele_miniiso04, pt, eta, sf, sf_err);
          weight_veto *= sf;
          // Apply 2% error per electron leg
          weight_veto *= get_syst_weight(1, 0.02, nSigmaEleFastSimSF);
        }
        // Apply the Reco SF
        weight_veto   *= get_syst_weight(reco_sf, reco_sf_err, nSigmaEleRecoSF);
      }
    }

    // Loose Electrons

#if INC == 1

    if (
        (( pt > 5  || pt < 10) && ((etasc  < 0.8 && mva2 > 0.46) || ((etasc >= 0.8 && etasc < 1.479) && mva2 > -0.03) || (etasc >= 1.479 && mva2 > -0.06))) ||
        ((pt >= 10 || pt <=15) && ((etasc  < 0.8 && mva > -0.48) ||((etasc >= 0.8 && etasc < 1.479) && mva > -0.67) || (etasc >= 1.479 && mva > -0.49))) ||
        ((pt >= 15 || pt <= 25) && (((etasc <  0.8 && mva > (-0.48-0.037)*(pt-15))) ||
                                    ((etasc >= 0.8 && etasc < 1.479) && mva > (-0.67-0.024)*(pt-15)) ||
                                    (etasc >= 1.479 && mva > (-0.49-0.034)*(pt-15)))) ||
        ((pt > 25 ) &&            ((etasc < 0.8 && mva > -0.85) || ((etasc >= 0.8 &&  etasc < 1.479) && mva > -0.91) || (etasc >= 1.479 && mva > -0.83)))

        )

      {
        // Apply ID scale factor
        geteff2D(eff_full_ele_looseid, pt, eta, sf, sf_err);
        weight_loose *= get_syst_weight(sf, sf_err, nSigmaEleIDSF);
        if (isFastSim) {
          geteff2D(eff_fast_ele_looseid, pt, eta, sf, sf_err);
          weight_loose *= sf;
        }
        weight_loose   *= get_syst_weight(reco_sf, reco_sf_err, nSigmaEleRecoSF);
      }
#else
    if ( id_loose_noiso &&
         pt      >= ELE_LOOSE_PT_CUT &&
         abseta  <  ELE_LOOSE_ETA_CUT && !(abseta>=1.442 && abseta< 1.556) ) {
      // Apply ID scale factor
      geteff2D(eff_full_ele_looseid, pt, eta, sf, sf_err);
      weight_loose *= get_syst_weight(sf, sf_err, nSigmaEleIDSF);
      if (isFastSim) {
        geteff2D(eff_fast_ele_looseid, pt, eta, sf, sf_err);
        weight_loose *= sf;
      }

      if ( miniIso <  ELE_LOOSE_MINIISO_CUT &&
           absd0   <  ELE_LOOSE_IP_D0_CUT &&
           absdz   <  ELE_LOOSE_IP_DZ_CUT ) {
        // Apply Iso scale factor
        if (ELE_LOOSE_MINIISO_CUT == 0.1)
          geteff2D(eff_full_ele_miniiso01, pt, eta, sf, sf_err);
        else if (ELE_LOOSE_MINIISO_CUT == 0.2)
          geteff2D(eff_full_ele_miniiso02, pt, eta, sf, sf_err);
        else if (ELE_LOOSE_MINIISO_CUT == 0.4)
          geteff2D(eff_full_ele_miniiso04, pt, eta, sf, sf_err);
        weight_loose *= get_syst_weight(sf, sf_err, nSigmaEleIsoSF);
        if (isFastSim) {
          if (ELE_LOOSE_MINIISO_CUT == 0.1)
            geteff2D(eff_fast_ele_miniiso01, pt, eta, sf, sf_err);
          else if (ELE_LOOSE_MINIISO_CUT == 0.2)
            geteff2D(eff_fast_ele_miniiso02, pt, eta, sf, sf_err);
          else if (ELE_LOOSE_MINIISO_CUT == 0.4)
            geteff2D(eff_fast_ele_miniiso04, pt, eta, sf, sf_err);
          weight_loose *= sf;
          // Apply 2% error per electron leg
          weight_loose *= get_syst_weight(1, 0.02, nSigmaEleFastSimSF);
        }

        // Apply the Reco SF
        weight_loose   *= get_syst_weight(reco_sf, reco_sf_err, nSigmaEleRecoSF);
      }
    }

#endif
    // Selected Electrons
    if ( id_select_noiso &&
         pt      >= ELE_SELECT_PT_CUT &&
         abseta  <  ELE_SELECT_ETA_CUT && !(abseta>=1.442 && abseta< 1.556) ) {
      // Apply ID scale factor
      geteff2D(eff_full_ele_mediumid, pt, eta, sf, sf_err);
      weight_select *= get_syst_weight(sf, sf_err, nSigmaEleIDSF);
      if (isFastSim) {
        geteff2D(eff_fast_ele_mediumid, pt, eta, sf, sf_err);
        weight_select *= sf;
      }
      if ( miniIso <  ELE_SELECT_MINIISO_CUT &&
           absd0   <  ELE_SELECT_IP_D0_CUT &&
           absdz   <  ELE_SELECT_IP_DZ_CUT ) {
        // Apply Iso scale factor
        if (ELE_SELECT_MINIISO_CUT == 0.1)
          geteff2D(eff_full_ele_miniiso01, pt, eta, sf, sf_err);
        else if (ELE_SELECT_MINIISO_CUT == 0.2)
          geteff2D(eff_full_ele_miniiso02, pt, eta, sf, sf_err);
        else if (ELE_SELECT_MINIISO_CUT == 0.4)
          geteff2D(eff_full_ele_miniiso04, pt, eta, sf, sf_err);
        weight_select *= get_syst_weight(sf, sf_err, nSigmaEleIsoSF);
        if (isFastSim) {
          if (ELE_SELECT_MINIISO_CUT == 0.1)
            geteff2D(eff_fast_ele_miniiso01, pt, eta, sf, sf_err);
          else if (ELE_SELECT_MINIISO_CUT == 0.2)
            geteff2D(eff_fast_ele_miniiso02, pt, eta, sf, sf_err);
          else if (ELE_SELECT_MINIISO_CUT == 0.4)
            geteff2D(eff_fast_ele_miniiso04, pt, eta, sf, sf_err);
          weight_select *= sf;
          // Apply 2% error per electron leg
          weight_select *= get_syst_weight(1, 0.02, nSigmaEleFastSimSF);
        }
        // Apply the Reco SF
        weight_select   *= get_syst_weight(reco_sf, reco_sf_err, nSigmaEleRecoSF);
      }
    }

  }

  return std::make_tuple(weight_veto, weight_loose, weight_select);
}

std::tuple<double, double, double> AnalysisBase::calc_muon_sf(eventBuffer& data, const double& nSigmaMuonTrkSF, const double& nSigmaMuonFullSimSF, const double& nSigmaMuonFastSimSF, const bool& isFastSim) {
  double trk_sf=1, trk_sf_err_up=0, trk_sf_err_down=0, trk_sf_veto=1, trk_sf_veto_err_up=0, trk_sf_veto_err_down=0, sf, sf_err;
  double weight_veto  = 1.0, weight_loose = 1.0, weight_select = 1.0;
  for (size_t i=0; i<data.Muon.size(); ++i) {
    double pt      = data.Muon[i].pt;
    double eta     = data.Muon[i].eta;
    float abseta   = std::abs(eta);
#if INC == 1
    float ipsig = std::abs(data.Muon[i].sip3d);
#endif
    float miniIso  = data.Muon[i].miniPFRelIso_all;
    bool id_veto_noiso   = (data.Muon[i].softId  == 1.0);
    float absd0    = std::abs(data.Muon[i].dxy);
    float absdz    = std::abs(data.Muon[i].dz);
    bool id_loose_noiso  = (data.Muon[i].softId  == 1.0);
    bool id_select_noiso = (data.Muon[i].mediumId == 1.0);
    // Tacking efficiency scale factor
    //geteff_AE(eff_full_muon_trk,      eta, trk_sf,      trk_sf_err_up,      trk_sf_err_down);
    //geteff_AE(eff_full_muon_trk_veto, eta, trk_sf_veto, trk_sf_veto_err_up, trk_sf_veto_err_down);

    // Veto Muons
    // Using previous POG ID scale factors
    if ( id_veto_noiso &&
         pt      >= MU_VETO_PT_CUT &&
         abseta  <  MU_VETO_ETA_CUT &&
         miniIso <  MU_VETO_MINIISO_CUT &&
         absd0   <  MU_VETO_IP_D0_CUT &&
         absdz   <  MU_VETO_IP_DZ_CUT ) {
      // Apply ID scale factor
      geteff2D(eff_full_muon_looseid, pt, eta, sf, sf_err);
      weight_veto *= sf;
      if (isFastSim) {
        geteff2D(eff_fast_muon_vetoid, pt, eta, sf, sf_err);
        weight_veto *= sf;
      }
      // Apply Isolation scale factor
      if (MU_VETO_MINIISO_CUT == 0.2)
        geteff2D(eff_full_muon_miniiso02, pt, eta, sf, sf_err);
      else if (MU_VETO_MINIISO_CUT == 0.4)
        geteff2D(eff_full_muon_miniiso04, pt, eta, sf, sf_err);
      weight_veto *= sf;
      // Apply IP efficiency scale factor
      //geteff2D(eff_full_muon_looseip2d, pt, eta, sf, sf_err);
      //weight_veto *= sf;
      // Apply systematics
      weight_veto *= get_syst_weight(1, 0.03, nSigmaMuonFullSimSF);
      if (isFastSim) weight_veto *= get_syst_weight(1, 0.02, nSigmaMuonFastSimSF);
      // Apply Tracking scale factor here
      weight_veto *= get_syst_weight(trk_sf_veto, trk_sf_veto+trk_sf_veto_err_up, trk_sf_veto-trk_sf_veto_err_down, nSigmaMuonTrkSF);
    }

    // Loose Muons
#if INC == 1
    if ( id_loose_noiso && (
                            (pt      >= MU_LOOSE_PT_CUT &&
                             abseta  <  MU_LOOSE_ETA_CUT &&
                             miniIso <  MU_LOOSE_MINIISO_CUT_0 &&
                             ipsig    <  MU_LOOSE_IP_3D_CUT)  ||
                            (pt      >5 &&
                             abseta  <  MU_LOOSE_ETA_CUT &&
                             miniIso <  MU_LOOSE_MINIISO_CUT_1 &&
                             ipsig    <  MU_LOOSE_IP_3D_CUT) ) ){

      // Apply ID scale factor
      geteff2D(eff_full_muon_looseid, pt, eta, sf, sf_err);
      weight_loose *= sf;
      if (isFastSim) {
        geteff2D(eff_fast_muon_looseid, pt, eta, sf, sf_err);
        weight_loose *= sf;
      }
      // Apply Isolation scale factor
      if (MU_LOOSE_MINIISO_CUT_0 == 0.2)
        geteff2D(eff_full_muon_miniiso02, pt, eta, sf, sf_err);
      else if (MU_LOOSE_MINIISO_CUT_0 == 0.4)
        geteff2D(eff_full_muon_miniiso04, pt, eta, sf, sf_err);
      if (MU_LOOSE_MINIISO_CUT_1 == 10)
        geteff2D(eff_full_muon_miniiso02, pt, eta, sf, sf_err);
      else if (MU_LOOSE_MINIISO_CUT_1 == 0.4)
        geteff2D(eff_full_muon_miniiso04, pt, eta, sf, sf_err);
      weight_loose *= sf;
      // Apply systematics
      weight_loose *= get_syst_weight(1, 0.03, nSigmaMuonFullSimSF);
      if (isFastSim) weight_loose *= get_syst_weight(1, 0.02, nSigmaMuonFastSimSF);
      // Apply Tracking scale factor here
      if (MU_LOOSE_PT_CUT<20) {
        weight_loose *= get_syst_weight(trk_sf_veto, trk_sf_veto+trk_sf_veto_err_up, trk_sf_veto-trk_sf_veto_err_down, nSigmaMuonTrkSF);
      } else {
        weight_loose *= get_syst_weight(trk_sf, trk_sf+trk_sf_err_up, trk_sf-trk_sf_err_down, nSigmaMuonTrkSF);
      }
    }
#else
    if ( id_loose_noiso &&
         pt      >= MU_LOOSE_PT_CUT &&
         abseta  <  MU_LOOSE_ETA_CUT &&
         miniIso <  MU_LOOSE_MINIISO_CUT &&
         absd0   <  MU_LOOSE_IP_D0_CUT &&
         absdz   <  MU_LOOSE_IP_DZ_CUT ) {
      // Apply ID scale factor
      geteff2D(eff_full_muon_looseid, pt, eta, sf, sf_err);
      weight_loose *= sf;
      if (isFastSim) {
        geteff2D(eff_fast_muon_looseid, pt, eta, sf, sf_err);
        weight_loose *= sf;
      }
      // Apply Isolation scale factor
      if (MU_LOOSE_MINIISO_CUT == 0.2)
        geteff2D(eff_full_muon_miniiso02, pt, eta, sf, sf_err);
      else if (MU_LOOSE_MINIISO_CUT == 0.4)
        geteff2D(eff_full_muon_miniiso04, pt, eta, sf, sf_err);
      weight_loose *= sf;
      // Apply systematics
      weight_loose *= get_syst_weight(1, 0.03, nSigmaMuonFullSimSF);
      if (isFastSim) weight_loose *= get_syst_weight(1, 0.02, nSigmaMuonFastSimSF);
      // Apply Tracking scale factor here
      if (MU_LOOSE_PT_CUT<10) {
        weight_loose *= get_syst_weight(trk_sf_veto, trk_sf_veto+trk_sf_veto_err_up, trk_sf_veto-trk_sf_veto_err_down, nSigmaMuonTrkSF);
      } else {
        weight_loose *= get_syst_weight(trk_sf, trk_sf+trk_sf_err_up, trk_sf-trk_sf_err_down, nSigmaMuonTrkSF);
      }
    }
#endif

    // Selected Muons
    if ( id_select_noiso &&
         pt      >= MU_SELECT_PT_CUT &&
         abseta  <  MU_SELECT_ETA_CUT &&
         miniIso <  MU_SELECT_MINIISO_CUT &&
         absd0   <  MU_SELECT_IP_D0_CUT &&
         absdz   <  MU_SELECT_IP_DZ_CUT ) {
      // Apply ID scale factor
      geteff2D(eff_full_muon_mediumid, pt, eta, sf, sf_err);
      weight_select *= sf;
      if (isFastSim) {
        geteff2D(eff_fast_muon_mediumid, pt, eta, sf, sf_err);
        weight_select *= sf;
      }
      // Apply Isolation scale factor
      if (MU_SELECT_MINIISO_CUT == 0.2)
        geteff2D(eff_full_muon_miniiso02, pt, eta, sf, sf_err);
      else if (MU_SELECT_MINIISO_CUT == 0.4)
        geteff2D(eff_full_muon_miniiso04, pt, eta, sf, sf_err);
      weight_select *= sf;
      // Apply IP efficiency scale factor
      //geteff2D(eff_full_muon_tightip2d, pt, eta, sf, sf_err);
      //weight_select *= sf;
      // Apply systematics
      weight_select *= get_syst_weight(1, 0.03, nSigmaMuonFullSimSF);
      if (isFastSim) weight_select *= get_syst_weight(1, 0.02, nSigmaMuonFastSimSF);
      // Apply Tracking scale factor here
      if (MU_SELECT_PT_CUT<10) {
        weight_select *= get_syst_weight(trk_sf_veto, trk_sf_veto+trk_sf_veto_err_up, trk_sf_veto-trk_sf_veto_err_down, nSigmaMuonTrkSF);
      } else {
        weight_select *= get_syst_weight(trk_sf, trk_sf+trk_sf_err_up, trk_sf-trk_sf_err_down, nSigmaMuonTrkSF);
      }
    }

  }

  return std::make_tuple(weight_veto, weight_loose, weight_select);
}


//  double AnalysisBase::calc_njet_weight(eventBuffer data, const double& nSigmaNJetWeight) {
//    // QCD Njet Reweighting
//    // First run this script to obtain the expo fit parameters
//    // root scripts/calc_njet_weight.C
//    // Up variation taken from Q region
//    // Down variation taken from G-1 region
//    double w_up = std::exp(-4.15259e-01 + 9.97141e-02 * nJet);
//    double w_dn = std::exp( 1.02951e+00 - 1.90498e-01 * nJet);
//    double weight = get_syst_weight(1.0, w_up, w_dn, nSigmaNJetWeight);
//    return weight;
//  }


double AnalysisBase::calc_lostlep_weight(eventBuffer& data, const double& nSigmaLostLep) {
  // Lost Lepton event weight
  // First run this script to obtain the lost lepton uncertainties
  // python scripts/calc_lostlepsyst.py
  // Use the averages combination of all leptons for W/top
  double weight = 1;
  if (nEleVeto+nMuVeto+nTauVeto==0) {
    if (!isData) for(size_t i=0, nGenPart=data.GenPart.size(); i<nGenPart; ++i) {
      // Check if the gen particle is a final state lepton from W mother
      if (passGenLeptonFromW[i]) {
        double unc = 0;
        double abseta = std::abs(data.GenPart[i].eta);
        if      (abseta<0.5) unc = 0.125;
        else if (abseta<1.0) unc = 0.126;
        else if (abseta<1.5) unc = 0.129;
        else if (abseta<2.0) unc = 0.143;
        else if (abseta<2.5) unc = 0.175;
        weight *= get_syst_weight(1.0, unc, nSigmaLostLep);
        //std::cout<<"Lost-lepton found: pt/eta/id = "<<data.GenPart[i].pt[i]<<" "<<data.GenPart[i].eta[i]<<" "<<data.GenPart[i].pdgId<<" E/M/T="<<nEleVeto<<"/"<<nMuVeto<<"/"<<nTauVeto<<std::endl;
      }
    }
  }
  return weight;
}


double AnalysisBase::calc_trigger_efficiency(eventBuffer& data, const double& nSigmaTrigger) {
  /*
  // 1D trigger efficiency method
  double eff, err_up, err_down;
  if (nJetAK8>0) {
  geteff_AE(eff_trigger, AK4_Ht, eff, err_up, err_down);
  double w = get_syst_weight(eff, eff+err_up, eff-err_down, nSigmaTrigger);
  return w;
  } else return 0;
  */
  // 2D trigger efficiency in bins of HT and Jet1pt
  // Check the presence of a lepton/photon and apply different weights
  TH2D *h      = eff_trigger_lep;
  TH2D *h_up   = eff_trigger_lep_up;
  TH2D *h_down = eff_trigger_lep_down;
  double MET = data.MET_pt;

  if (nPhotonPreSelect>=1) {
    h      = eff_trigger_pho;
    h_up   = eff_trigger_pho_up;
    h_down = eff_trigger_pho_down;
  }

  if (nJetAK8>0) {
    double eff = 0, total = 0;
    geteff2D(h, MET, AK4_Ht, eff, total); // total was saved to histo error
    if (total>0) {
      double eff_up   = geteff2D(h_up,   MET, AK4_Ht);
      double eff_down = geteff2D(h_down, MET, AK4_Ht);
      double w = get_syst_weight(eff, eff_up, eff_down, nSigmaTrigger);
      return w;
    } else return 0;
  } else return 0;
  /*
    TH3D *h      = eff_3D_trigger_lep;
    TH3D *h_up   = eff_3D_trigger_lep_up;
    TH3D *h_down = eff_3D_trigger_lep_down;
    if (nJetAK8>0) {
    double eff = 0, total = 0;
    geteff3D(h, data.FatJet[iJetAK8[0]].msoftdrop, data.MET_pt, AK4_Ht, eff, total); // total was saved to histo error
    // For the time being only weight the measurable phase space
    // Rest is 0 --> Could weight with the TGraphAsymmErrors::Efficiency value (0.5+-0.5)
    if (total>0) {
    double eff_up   = geteff3D(h_up,   data.FatJet[iJetAK8[0]].msoftdrop, data.MET_pt, AK4_Ht);
    double eff_down = geteff3D(h_down, data.FatJet[iJetAK8[0]].msoftdrop, data.MET_pt, AK4_Ht);
    double w = get_syst_weight(eff, eff_up, eff_down, nSigmaTrigger);
    return w;
    } else return 0;
    } else return 0;
  */
}


int AnalysisBase::calc_mrr2_bin(eventBuffer& d, const char& region) {
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
