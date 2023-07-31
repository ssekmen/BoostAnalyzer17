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
#include "TStopwatch.h"
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

    debug = 0;
    t_s0 = 0;
    t_s1 = 0;
    t_s2 = 0;
    t_s3 = 0;
    t_s4 = 0;
    t_s5 = 0;
    t_s6 = 0;
    t_s7 = 0;
    t_s8 = 0;
    t_s9 = 0;
    if (debug) {
      sw_s0 = new TStopwatch;
      sw_s1 = new TStopwatch;
      sw_s2 = new TStopwatch;
      sw_s3 = new TStopwatch;
      sw_s4 = new TStopwatch;
      sw_s5 = new TStopwatch;
      sw_s6 = new TStopwatch;
      sw_s7 = new TStopwatch;
      sw_s8 = new TStopwatch;
      sw_s9 = new TStopwatch;
      sw_s0->Reset();
      sw_s1->Reset();
      sw_s2->Reset();
      sw_s3->Reset();
      sw_s4->Reset();
      sw_s5->Reset();
      sw_s6->Reset();
      sw_s7->Reset();
      sw_s8->Reset();
      sw_s9->Reset();
    }
    
    // Select which scale/correction factors to use for each region
    scale_factors.resize(magic_enum::enum_count<Region>());
    
    scale_factors[Region::Val_QCD16_W].push_back(&sf_boost);
    scale_factors[Region::Val_QCD16_W].push_back(&sf_ele_veto);
    scale_factors[Region::Val_QCD16_W].push_back(&sf_muon_veto);
    scale_factors[Region::Val_QCD16_W].push_back(&sf_btag_loose);
    scale_factors[Region::Val_QCD16_W].push_back(&cf_QTW);
    scale_factors[Region::Val_QCD16_W].push_back(&cf_Z);

		scale_factors[Region::Val_QCD16_V] = scale_factors[Region::Val_QCD16_Top] = scale_factors[Region::Val_QCD16_Z] = scale_factors[Region::Val_QCD16_H] = scale_factors[Region::Val_QCD16_W];
    
    scale_factors[Region::Val_Top16_W].push_back(&sf_boost);
    scale_factors[Region::Val_Top16_W].push_back(&sf_ele_veto);
    scale_factors[Region::Val_Top16_W].push_back(&sf_muon_veto);
    scale_factors[Region::Val_Top16_W].push_back(&sf_btag_medium);
    scale_factors[Region::Val_Top16_W].push_back(&cf_QTW);
    scale_factors[Region::Val_Top16_W].push_back(&cf_Z);

		scale_factors[Region::Val_Top16_V] = scale_factors[Region::Val_Top16_Top] = scale_factors[Region::Val_Top16_Z] = scale_factors[Region::Val_Top16_H] = scale_factors[Region::Val_Top16_W];
    
    scale_factors[Region::Val_W16_W].push_back(&sf_boost);
    scale_factors[Region::Val_W16_W].push_back(&sf_ele_veto);
    scale_factors[Region::Val_W16_W].push_back(&sf_muon_veto);
    scale_factors[Region::Val_W16_W].push_back(&sf_btag_loose);
    scale_factors[Region::Val_W16_W].push_back(&cf_QTW);
    scale_factors[Region::Val_W16_W].push_back(&cf_Z);

		scale_factors[Region::Val_W16_V] = scale_factors[Region::Val_W16_Top] = scale_factors[Region::Val_W16_Z] = scale_factors[Region::Val_W16_H] = scale_factors[Region::Val_W16_W];
    
    scale_factors[Region::CR_QCD17_1Boost].push_back(&sf_boost);
    scale_factors[Region::CR_QCD17_1Boost].push_back(&sf_ele_veto);
    scale_factors[Region::CR_QCD17_1Boost].push_back(&sf_muon_veto);
    scale_factors[Region::CR_QCD17_1Boost].push_back(&sf_btag_loose);
    scale_factors[Region::CR_QCD17_1Boost].push_back(&cf_QTW_CR);

		scale_factors[Region::CR_QCD17_2Boost] = scale_factors[Region::CR_QCD17_1Boost];
    
    scale_factors[Region::CR_Top17_1Boost].push_back(&sf_boost);
    scale_factors[Region::CR_Top17_1Boost].push_back(&sf_ele_veto);
    scale_factors[Region::CR_Top17_1Boost].push_back(&sf_muon_veto);
    scale_factors[Region::CR_Top17_1Boost].push_back(&sf_btag_medium);
    scale_factors[Region::CR_Top17_1Boost].push_back(&cf_QTW_CR);

		scale_factors[Region::CR_Top17_2Boost] = scale_factors[Region::CR_Top17_1Boost];
    
    scale_factors[Region::CR_W17_1Boost].push_back(&sf_boost);
    scale_factors[Region::CR_W17_1Boost].push_back(&sf_ele_veto);
    scale_factors[Region::CR_W17_1Boost].push_back(&sf_muon_veto);
    scale_factors[Region::CR_W17_1Boost].push_back(&sf_btag_loose);
    scale_factors[Region::CR_W17_1Boost].push_back(&cf_QTW_CR);

		scale_factors[Region::CR_W17_2Boost] = scale_factors[Region::CR_W17_1Boost];

    scale_factors[Region::CoCR_QCD17_1Boost].push_back(&sf_boost);
    scale_factors[Region::CoCR_QCD17_1Boost].push_back(&sf_ele_veto);
    scale_factors[Region::CoCR_QCD17_1Boost].push_back(&sf_muon_veto);
    scale_factors[Region::CoCR_QCD17_1Boost].push_back(&sf_btag_loose);
    scale_factors[Region::CoCR_QCD17_1Boost].push_back(&cf_QTW_CoCR);

		scale_factors[Region::CoCR_QCD17_2Boost] = scale_factors[Region::CoCR_QCD17_1Boost];
    
    scale_factors[Region::CoCR_Top17_1Boost].push_back(&sf_boost);
    scale_factors[Region::CoCR_Top17_1Boost].push_back(&sf_ele_veto);
    scale_factors[Region::CoCR_Top17_1Boost].push_back(&sf_muon_veto);
    scale_factors[Region::CoCR_Top17_1Boost].push_back(&sf_btag_medium);
    scale_factors[Region::CoCR_Top17_1Boost].push_back(&cf_QTW_CoCR);

		scale_factors[Region::CoCR_Top17_2Boost] = scale_factors[Region::CoCR_Top17_1Boost];
    
    scale_factors[Region::CoCR_W17_1Boost].push_back(&sf_boost);
    scale_factors[Region::CoCR_W17_1Boost].push_back(&sf_ele_veto);
    scale_factors[Region::CoCR_W17_1Boost].push_back(&sf_muon_veto);
    scale_factors[Region::CoCR_W17_1Boost].push_back(&sf_btag_loose);
    scale_factors[Region::CoCR_W17_1Boost].push_back(&cf_QTW_CoCR);

		scale_factors[Region::CoCR_W17_2Boost] = scale_factors[Region::CoCR_W17_1Boost];

    scale_factors[Region::Val_DiLep] = scale_factors[Region::CR_Top17_1Boost];
    
    scale_factors[Region::CR_LTop17_1Boost].push_back(&sf_boost);
    scale_factors[Region::CR_LTop17_1Boost].push_back(&sf_ele_veto);
    scale_factors[Region::CR_LTop17_1Boost].push_back(&sf_muon_veto);
    scale_factors[Region::CR_LTop17_1Boost].push_back(&sf_btag_medium);
    scale_factors[Region::CR_LTop17_1Boost].push_back(&cf_L_CR);

		scale_factors[Region::CR_LTop17_2Boost] = scale_factors[Region::CR_LTop17_1Boost];
    
    scale_factors[Region::CR_L17_1Boost].push_back(&sf_boost);
    scale_factors[Region::CR_L17_1Boost].push_back(&sf_ele_veto);
    scale_factors[Region::CR_L17_1Boost].push_back(&sf_muon_veto);
    scale_factors[Region::CR_L17_1Boost].push_back(&sf_btag_loose);
    scale_factors[Region::CR_L17_1Boost].push_back(&cf_L_CR);

		scale_factors[Region::CR_L17_2Boost] = scale_factors[Region::CR_L17_1Boost];
    
    scale_factors[Region::Val_NonIso_RMT].push_back(&sf_boost);
    scale_factors[Region::Val_NonIso_RMT].push_back(&cf_NonIso);

		scale_factors[Region::CR_NonIso_RMTdPhi] = scale_factors[Region::Val_NonIso_RdPhi] = scale_factors[Region::Val_NonIso_RMT];
    
    scale_factors[Region::CR_NonIso_0b_RMTdPhi].push_back(&sf_boost);
    scale_factors[Region::CR_NonIso_0b_RMTdPhi].push_back(&sf_btag_loose);
    scale_factors[Region::CR_NonIso_0b_RMTdPhi].push_back(&cf_NonIso_CR);

    scale_factors[Region::CR_NonIso_b_RMTdPhi].push_back(&sf_boost);
    scale_factors[Region::CR_NonIso_b_RMTdPhi].push_back(&sf_btag_medium);
    scale_factors[Region::CR_NonIso_b_RMTdPhi].push_back(&cf_NonIso_CR);
    
    scale_factors[Region::CoCR_NonIso_0b_RMTdPhi].push_back(&sf_boost);
    scale_factors[Region::CoCR_NonIso_0b_RMTdPhi].push_back(&sf_btag_loose);
    scale_factors[Region::CoCR_NonIso_0b_RMTdPhi].push_back(&cf_NonIso_CoCR);

    scale_factors[Region::CoCR_NonIso_b_RMTdPhi].push_back(&sf_boost);
    scale_factors[Region::CoCR_NonIso_b_RMTdPhi].push_back(&sf_btag_medium);
    scale_factors[Region::CoCR_NonIso_b_RMTdPhi].push_back(&cf_NonIso_CoCR);
    
    scale_factors[Region::CR_Fake].push_back(&sf_ele_veto);
    scale_factors[Region::CR_Fake].push_back(&sf_muon_veto);
    scale_factors[Region::CR_Fake].push_back(&sf_btag_loose);
    scale_factors[Region::Val_Fake] = scale_factors[Region::CR_Fake_MET500] = scale_factors[Region::CR_Fake];
    
    scale_factors[Region::CR_Real].push_back(&sf_ele_veto);
    scale_factors[Region::CR_Real].push_back(&sf_muon_veto);
    scale_factors[Region::CR_Real].push_back(&sf_btag_medium);
    
    scale_factors[Region::CR_1LepInv].push_back(&sf_boost);
    scale_factors[Region::CR_1LepInv].push_back(&sf_ele_veto);
    scale_factors[Region::CR_1LepInv].push_back(&sf_muon_veto);
    scale_factors[Region::CR_1LepInv].push_back(&sf_btag_loose);
    scale_factors[Region::CR_1LepInv_LepTrig] = scale_factors[Region::CR_1LepInv];
    
    scale_factors[Region::CR_2LepInv].push_back(&sf_boost);
    scale_factors[Region::CR_2LepInv].push_back(&sf_ele_medium);
    scale_factors[Region::CR_2LepInv].push_back(&sf_muon_medium);
    scale_factors[Region::CR_2LepInv].push_back(&sf_btag_loose);
    
    scale_factors[Region::CR_1PhoInv].push_back(&sf_boost);
    scale_factors[Region::CR_1PhoInv].push_back(&sf_ele_veto);
    scale_factors[Region::CR_1PhoInv].push_back(&sf_muon_veto);
    scale_factors[Region::CR_1PhoInv].push_back(&sf_pho_medium);
    scale_factors[Region::CR_1PhoInv].push_back(&cf_Z_CR);

    scale_factors[Region::Val_Signal_V].push_back(&sf_boost);
    scale_factors[Region::Val_Signal_V].push_back(&sf_ele_veto);
    scale_factors[Region::Val_Signal_V].push_back(&sf_muon_veto);
    scale_factors[Region::Val_Signal_V].push_back(&sf_btag_medium);
    scale_factors[Region::Val_Signal_V].push_back(&cf_QTW);
    scale_factors[Region::Val_Signal_V].push_back(&cf_Z);

		scale_factors[Region::Val_Signal_H] = scale_factors[Region::Val_Signal_Top] = scale_factors[Region::Val_Signal_V];

    // Validation regions
    scale_factors[Region::Val_Signal].push_back(&sf_boost);
    scale_factors[Region::Val_Signal].push_back(&sf_ele_veto);
    scale_factors[Region::Val_Signal].push_back(&sf_muon_veto);
    scale_factors[Region::Val_Signal].push_back(&sf_btag_medium);
    scale_factors[Region::Val_Signal].push_back(&cf_QTW);
    scale_factors[Region::Val_Signal].push_back(&cf_Z);
 
		scale_factors[Region::Val_Signal_LostLep] = scale_factors[Region::Val_Signal];
 
    scale_factors[Region::Val_QCD].push_back(&sf_boost);
    scale_factors[Region::Val_QCD].push_back(&sf_ele_veto);
    scale_factors[Region::Val_QCD].push_back(&sf_muon_veto);
    scale_factors[Region::Val_QCD].push_back(&sf_btag_loose);
    scale_factors[Region::Val_QCD].push_back(&cf_QTW);
    scale_factors[Region::Val_QCD].push_back(&cf_Z);
 
    scale_factors[Region::Val_Signal_L_V].push_back(&sf_boost);
    scale_factors[Region::Val_Signal_L_V].push_back(&sf_ele_veto);
    scale_factors[Region::Val_Signal_L_V].push_back(&sf_muon_veto);
    scale_factors[Region::Val_Signal_L_V].push_back(&sf_btag_medium);
    scale_factors[Region::Val_Signal_L_V].push_back(&cf_QTW);
    scale_factors[Region::Val_Signal_L_V].push_back(&cf_L);
    
		scale_factors[Region::Val_Signal_L_H] = scale_factors[Region::Val_Signal_L_Top] = scale_factors[Region::Val_Signal_L_V];

    // Validation regions
    scale_factors[Region::Val_Signal_L].push_back(&sf_boost);
    scale_factors[Region::Val_Signal_L].push_back(&sf_ele_veto);
    scale_factors[Region::Val_Signal_L].push_back(&sf_muon_veto);
    scale_factors[Region::Val_Signal_L].push_back(&sf_btag_medium);
    scale_factors[Region::Val_Signal_L].push_back(&cf_QTW);
    scale_factors[Region::Val_Signal_L].push_back(&cf_L);
 
    scale_factors[Region::Val_QCD_L].push_back(&sf_boost);
    scale_factors[Region::Val_QCD_L].push_back(&sf_ele_veto);
    scale_factors[Region::Val_QCD_L].push_back(&sf_muon_veto);
    scale_factors[Region::Val_QCD_L].push_back(&sf_btag_loose);
    scale_factors[Region::Val_QCD_L].push_back(&cf_QTW);
    scale_factors[Region::Val_QCD_L].push_back(&cf_L);
 
    scale_factors[Region::Val_Lep].push_back(&sf_boost);
    scale_factors[Region::Val_Lep].push_back(&sf_ele_medium);
    scale_factors[Region::Val_Lep].push_back(&sf_muon_medium);
    //scale_factors[Region::Val_Lep].push_back(&cf_QTW);
    //scale_factors[Region::Val_Lep].push_back(&cf_Z);
    
    scale_factors[Region::Val_Lep_0b].push_back(&sf_boost);
    scale_factors[Region::Val_Lep_0b].push_back(&sf_ele_medium);
    scale_factors[Region::Val_Lep_0b].push_back(&sf_muon_medium);
    scale_factors[Region::Val_Lep_0b].push_back(&sf_btag_loose);
    //scale_factors[Region::Val_Lep_0b].push_back(&cf_QTW);
    //scale_factors[Region::Val_Lep_0b].push_back(&cf_Z);
    
    scale_factors[Region::Val_Lep_b].push_back(&sf_boost);
    scale_factors[Region::Val_Lep_b].push_back(&sf_ele_medium);
    scale_factors[Region::Val_Lep_b].push_back(&sf_muon_medium);
    scale_factors[Region::Val_Lep_b].push_back(&sf_btag_medium);
    //scale_factors[Region::Val_Lep_b].push_back(&cf_QTW);
    //scale_factors[Region::Val_Lep_b].push_back(&cf_Z);
    
    // Signal regions
    // veto lep
    scale_factors[Region::SR_Had_2htop].push_back(&sf_boost);
    scale_factors[Region::SR_Had_2htop].push_back(&sf_ele_veto);
    scale_factors[Region::SR_Had_2htop].push_back(&sf_muon_veto);
    scale_factors[Region::SR_Had_2htop].push_back(&cf_QTW);
    scale_factors[Region::SR_Had_2htop].push_back(&cf_Z);

    // veto lep, 1b
    scale_factors[Region::Pre].push_back(&sf_boost);
    scale_factors[Region::Pre].push_back(&sf_ele_medium);
    scale_factors[Region::Pre].push_back(&sf_muon_medium);
    scale_factors[Region::Pre].push_back(&sf_btag_medium);

    scale_factors[Region::Pre_Had].push_back(&sf_boost);
    scale_factors[Region::Pre_Had].push_back(&sf_ele_veto);
    scale_factors[Region::Pre_Had].push_back(&sf_muon_veto);
    scale_factors[Region::Pre_Had].push_back(&sf_btag_medium);

    scale_factors[Region::SR_Had_V_b_45j].push_back(&sf_boost);
    scale_factors[Region::SR_Had_V_b_45j].push_back(&sf_ele_veto);
    scale_factors[Region::SR_Had_V_b_45j].push_back(&sf_muon_veto);
    scale_factors[Region::SR_Had_V_b_45j].push_back(&sf_btag_medium);
    scale_factors[Region::SR_Had_V_b_45j].push_back(&cf_QTW);
    scale_factors[Region::SR_Had_V_b_45j].push_back(&cf_Z);

    scale_factors[Region::SR_Had_V_b_6j] = scale_factors[Region::SR_Had_H_b_45j] = scale_factors[Region::SR_Had_H_b_6j] = scale_factors[Region::SR_Had_1htop] =
      scale_factors[Region::SR_Had_HV_b_6j] = scale_factors[Region::SR_Had_V_b_45j];
    
    // veto lep, 0b
    scale_factors[Region::SR_Had_1V_0b_34j].push_back(&sf_boost);
    scale_factors[Region::SR_Had_1V_0b_34j].push_back(&sf_ele_veto);
    scale_factors[Region::SR_Had_1V_0b_34j].push_back(&sf_muon_veto);
    scale_factors[Region::SR_Had_1V_0b_34j].push_back(&sf_btag_loose);
    scale_factors[Region::SR_Had_1V_0b_34j].push_back(&cf_QTW);
    scale_factors[Region::SR_Had_1V_0b_34j].push_back(&cf_Z);

    scale_factors[Region::SR_Had_1V_0b_5j] = scale_factors[Region::SR_Had_2V_0b_24j] = scale_factors[Region::SR_Had_2V_0b_5j] = 
      scale_factors[Region::SR_Had_H_0b_34j] = scale_factors[Region::SR_Had_H_0b_5j] =
      scale_factors[Region::SR_Had_HV_0b_24j] = scale_factors[Region::SR_Had_HV_0b_5j] = scale_factors[Region::SR_Had_1V_0b_34j];
    
    // lepton
    scale_factors[Region::Pre_Lep].push_back(&sf_boost);
    scale_factors[Region::Pre_Lep].push_back(&sf_ele_medium);
    scale_factors[Region::Pre_Lep].push_back(&sf_muon_medium);

    scale_factors[Region::SR_Lep_1htop].push_back(&sf_boost);
    scale_factors[Region::SR_Lep_1htop].push_back(&sf_ele_medium);
    scale_factors[Region::SR_Lep_1htop].push_back(&sf_muon_medium);
    scale_factors[Region::SR_Lep_1htop].push_back(&cf_QTW);
    scale_factors[Region::SR_Lep_1htop].push_back(&cf_Z);
    
    // lep, 1b
    scale_factors[Region::SR_Lep_V_b].push_back(&sf_boost);
    scale_factors[Region::SR_Lep_V_b].push_back(&sf_ele_medium);
    scale_factors[Region::SR_Lep_V_b].push_back(&sf_muon_medium);
    scale_factors[Region::SR_Lep_V_b].push_back(&sf_btag_medium);
    scale_factors[Region::SR_Lep_V_b].push_back(&cf_QTW);
    scale_factors[Region::SR_Lep_V_b].push_back(&cf_Z);

    scale_factors[Region::SR_Lep_H_b] = scale_factors[Region::SR_Lep_V_b];
    
    // lep, 0b
    scale_factors[Region::SR_Lep_V_0b].push_back(&sf_boost);
    scale_factors[Region::SR_Lep_V_0b].push_back(&sf_ele_medium);
    scale_factors[Region::SR_Lep_V_0b].push_back(&sf_muon_medium);
    scale_factors[Region::SR_Lep_V_0b].push_back(&sf_btag_loose);
    scale_factors[Region::SR_Lep_V_0b].push_back(&cf_QTW);
    scale_factors[Region::SR_Lep_V_0b].push_back(&cf_Z);

    scale_factors[Region::SR_Lep_H_0b] = scale_factors[Region::SR_Lep_V_0b];
    
    // 0b
    scale_factors[Region::SR_Lepjet_0V_24j].push_back(&sf_boost);
    scale_factors[Region::SR_Lepjet_0V_24j].push_back(&sf_btag_loose);
    scale_factors[Region::SR_Lepjet_0V_24j].push_back(&cf_NonIso);

    scale_factors[Region::SR_Lepjet_0V_5j] = scale_factors[Region::SR_Lepjet_1V_24j] = scale_factors[Region::SR_Lepjet_1V_5j] = scale_factors[Region::SR_Lepjet_0V_24j];
		scale_factors[Region::SR_Leptop_0htop] = scale_factors[Region::SR_Leptop_1htop] = scale_factors[Region::SR_Lepjet_0V_24j];

    scale_factors[Region::TR_Had_H_b_45j] = scale_factors[Region::TR_Had_H_b_6j] = 
    scale_factors[Region::TR_Had_HV_b_6j] = scale_factors[Region::SR_Had_V_b_45j];

    scale_factors[Region::TR_Had_H_0b_34j] = scale_factors[Region::TR_Had_H_0b_5j] =
    scale_factors[Region::TR_Had_HV_0b_24j] = scale_factors[Region::TR_Had_HV_0b_5j] = scale_factors[Region::SR_Had_1V_0b_34j];

    scale_factors[Region::TR_Lep_H_b] = scale_factors[Region::SR_Lep_V_b];
    scale_factors[Region::TR_Lep_H_0b] = scale_factors[Region::SR_Lep_V_0b];
    
    
  }
  ~ScaleFactors() {
    if (debug) {
      double t_s_sum = t_s0 + t_s1 + t_s2 + t_s3 + t_s4
        + t_s5 + t_s6 + t_s7 + t_s8 + t_s9;
      std::cout<<"ScaleFactors Time benchmarks:"<<std::endl;
      std::cout<<"- sf0: "<<t_s0<<"   ("<<(100*t_s0/t_s_sum)<<"%)"<<std::endl;
      std::cout<<"- sf1: "<<t_s1<<"   ("<<(100*t_s1/t_s_sum)<<"%)"<<std::endl;
      std::cout<<"- sf2: "<<t_s2<<"   ("<<(100*t_s2/t_s_sum)<<"%)"<<std::endl;
      std::cout<<"- sf3: "<<t_s3<<"   ("<<(100*t_s3/t_s_sum)<<"%)"<<std::endl;
      std::cout<<"- sf4: "<<t_s4<<"   ("<<(100*t_s4/t_s_sum)<<"%)"<<std::endl;
      std::cout<<"- sf5: "<<t_s5<<"   ("<<(100*t_s5/t_s_sum)<<"%)"<<std::endl;
      std::cout<<"- sf6: "<<t_s6<<"   ("<<(100*t_s6/t_s_sum)<<"%)"<<std::endl;
      std::cout<<"- sf7: "<<t_s7<<"   ("<<(100*t_s7/t_s_sum)<<"%)"<<std::endl;
      std::cout<<"- sf8: "<<t_s8<<"   ("<<(100*t_s8/t_s_sum)<<"%)"<<std::endl;
      std::cout<<"- sf9: "<<t_s9<<"   ("<<(100*t_s9/t_s_sum)<<"%)"<<std::endl;
      std::cout<<"- SUM:     "<<t_s_sum<<std::endl;
    }
  }

  void init_sf_histos();

  void init_input();

  void fill_sf_histos(const bool&, const bool&, const unsigned int&, const double&);

  double calc_boost_tagging_sf(const double&, const double&, const double&);
  double calc_mass_tagging_sf();

  double calc_top_tagging_sf(const double&, const double&, const double&, const double&);
  double calc_fake_top_0b_mass_tagging_sf(const double&);
  double calc_fake_top_mass_tagging_sf(const double&);
  double calc_fake_top_anti_tagging_sf(const double&);

  double calc_w_tagging_sf(const double&, const double&, const double&, const double&);
  double calc_fake_w_mass_tagging_sf(const double&);
  double calc_fake_w_anti_tagging_sf(const double&);

	double calc_QTW_CR_cf(int);
	double calc_QTW_CoCR_cf(int);
	std::pair<double, double> calc_Z_CR_cf(int);
	double calc_nonIso_CR_cf(int);
	double calc_nonIso_CoCR_cf(int);

	double calc_QTW_cf(const double&, int);
	std::pair<double, double> calc_Z_cf(const double&, int);
	double calc_nonIso_cf(const double&, int);

  std::pair<double, double> calc_b_tagging_sf(const double&, const double&);

  //std::tuple<double, double> calc_ele_sf(const double&, const double&, const double&, const double&);
  std::tuple<double, double> calc_ele_sf(const double&, const double&);

  double calc_pho_sf();

  //std::tuple<double, double> calc_muon_sf(const double&, const double&, const double&);
  std::tuple<double, double> calc_muon_sf(const double&, const double&);
  
  void apply_scale_factors(const unsigned int&, std::vector<double>&, std::vector<std::vector<double> >&, 
                           const unsigned int&, const std::vector<std::vector<double> >&);

  std::vector<std::vector<double*> > scale_factors;

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
  TH2F* eff_full_ele_razor;
  TH2F* eff_full_pho_mediumid;
  //TGraphAsymmErrors* eff_full_muon_trk;
  //TGraphAsymmErrors* eff_full_muon_trk_veto;
  TH2F* eff_full_muon_looseid;
  TH2F* eff_full_muon_mediumid;
  TH2F* eff_full_muon_miniiso04;
  TH2F* eff_full_muon_miniiso02;
  TH2D* eff_fast_muon_vetoid;
  TH2D* eff_fast_muon_looseid;
  TH2D* eff_fast_muon_mediumid;
  TH2F* eff_full_muon_razor;
  TH2F* eff_full_muon_veto;
  
  TGraphErrors* eff_full_POG_W;
  TH1D* eff_full_POG_Top;
  TH1D* eff_full_POG_Top_up;
  TH1D* eff_full_POG_Top_down;
  TGraphAsymmErrors* eff_full_fake_bLepTop;
  TGraphAsymmErrors* eff_full_fake_eLepTop;
  //TGraphAsymmErrors* eff_fast_fake_bLepTop;
  //TGraphAsymmErrors* eff_fast_fake_eLepTop;
  //TGraphAsymmErrors* eff_fast_bLepTop;
  //TGraphAsymmErrors* eff_fast_eLepTop;
  TGraphAsymmErrors* eff_full_fake_bHadTop;
  TGraphAsymmErrors* eff_full_fake_eHadTop;
  //TGraphAsymmErrors* eff_fast_fake_bHadTop;
  //TGraphAsymmErrors* eff_fast_fake_eHadTop;
  //TGraphAsymmErrors* eff_fast_bHadTop;
  //TGraphAsymmErrors* eff_fast_eHadTop;
  TGraphAsymmErrors* eff_full_fake_bHadV;
  TGraphAsymmErrors* eff_full_fake_eHadV;
  //TGraphAsymmErrors* eff_fast_fake_bHadV;
  //TGraphAsymmErrors* eff_fast_fake_eHadV;
  //TGraphAsymmErrors* eff_fast_bHadV;
  //TGraphAsymmErrors* eff_fast_eHadV;
  TGraphAsymmErrors* eff_full_fake_bHadH;
  TGraphAsymmErrors* eff_full_fake_eHadH;
  TGraphAsymmErrors* eff_full_fake_bHadHTop;
  TGraphAsymmErrors* eff_full_fake_eHadHTop;
  //TGraphAsymmErrors* eff_fast_fake_bHadH;
  //TGraphAsymmErrors* eff_fast_fake_eHadH;
  //TGraphAsymmErrors* eff_fast_bHadH;
  //TGraphAsymmErrors* eff_fast_eHadH;
  TGraphAsymmErrors* eff_full_fake_bMass;
  TGraphAsymmErrors* eff_full_fake_eMass;
  TGraphAsymmErrors* eff_full_bMassTop;
  TGraphAsymmErrors* eff_full_eMassTop;
  TH1D* eff_full_fake_bW;
  TH1D* eff_full_fake_eW;
  TGraphAsymmErrors* eff_fast_V;
  TGraphAsymmErrors* eff_fast_W;
  TGraphAsymmErrors* eff_fast_Z;
  TGraphAsymmErrors* eff_fast_H;
  TGraphAsymmErrors* eff_fast_HadTop;
  TGraphAsymmErrors* eff_fast_LepTop;

  TGraphAsymmErrors* g_cf_G_run2;
  TGraphAsymmErrors* g_cf_GJet_njet_run2;	
  TGraphAsymmErrors* g_cf_G_MassTag_run2;
  TGraphAsymmErrors* g_cf_G;
  TGraphAsymmErrors* g_cf_G_MassTag;
  TGraphAsymmErrors* g_cf_Q_1boost;
  TGraphAsymmErrors* g_cf_Q_2boost;
  TGraphAsymmErrors* g_cf_T_1boost;
  TGraphAsymmErrors* g_cf_T_2boost;
  TGraphAsymmErrors* g_cf_W_1boost;
  TGraphAsymmErrors* g_cf_W_2boost;
  TGraphAsymmErrors* g_cocf_Q_1boost;
  TGraphAsymmErrors* g_cocf_Q_2boost;
  TGraphAsymmErrors* g_cocf_T_1boost;
  TGraphAsymmErrors* g_cocf_T_2boost;
  TGraphAsymmErrors* g_cocf_W_1boost;
  TGraphAsymmErrors* g_cocf_W_2boost;
  TGraphAsymmErrors* g_cocf_NonIso_W;
  TGraphAsymmErrors* g_cocf_NonIso_T;
  TGraphAsymmErrors* g_cf_L_1boost;
  TGraphAsymmErrors* g_cf_L_2boost;
  TGraphAsymmErrors* g_cf_LT_1boost;
  TGraphAsymmErrors* g_cf_LT_2boost;
  TGraphAsymmErrors* g_cf_NonIso_W;
  TGraphAsymmErrors* g_cf_NonIso_T;
  TGraphAsymmErrors* g_cf_Q_njet_1boost;
  TGraphAsymmErrors* g_cf_Q_njet_2boost;
  TGraphAsymmErrors* g_cf_T_njet_1boost;
  TGraphAsymmErrors* g_cf_T_njet_2boost;
  TGraphAsymmErrors* g_cf_W_njet_1boost;
  TGraphAsymmErrors* g_cf_W_njet_2boost;
  TGraphAsymmErrors* g_cocf_Q_njet_1boost;
  TGraphAsymmErrors* g_cocf_Q_njet_2boost;
  TGraphAsymmErrors* g_cocf_T_njet_1boost;
  TGraphAsymmErrors* g_cocf_T_njet_2boost;
  TGraphAsymmErrors* g_cocf_W_njet_1boost;
  TGraphAsymmErrors* g_cocf_W_njet_2boost;
  TGraphAsymmErrors* g_cocf_NonIso_W_njet;
  TGraphAsymmErrors* g_cocf_NonIso_T_njet;
  TGraphAsymmErrors* g_cf_L_njet_1boost;
  TGraphAsymmErrors* g_cf_LT_njet_1boost;
  TGraphAsymmErrors* g_cf_L_njet_2boost;
  TGraphAsymmErrors* g_cf_LT_njet_2boost;
  TGraphAsymmErrors* g_cf_NonIso_W_njet;
  TGraphAsymmErrors* g_cf_NonIso_T_njet;
  TGraphAsymmErrors* g_cf_GJet_njet;

  //_______________________________________________________
  //         List of scale and correction factors
  
  double sf_boost;
  double sf_mass;
  double sf_ele_veto, sf_ele_medium;
  double sf_pho_medium;
  double sf_muon_veto, sf_muon_medium;
  double sf_btag_loose, sf_btag_medium;

  double cf_QTW_CR;
  double cf_QTW_CoCR;
  double cf_L_CR;
  double cf_Z_CR;
  double cf_QTW;
  double cf_Z;
  double cf_L;
  double cf_NonIso;
  double cf_NonIso_CR;
  double cf_NonIso_CoCR;

  //_______________________________________________________
  //           List of scale factor Histograms

  TH2D* h_btag_eff_b_loose;
  TH2D* h_btag_eff_c_loose;
  TH2D* h_btag_eff_l_loose;
  TH2D* h_btag_eff_b_medium;
  TH2D* h_btag_eff_c_medium;
  TH2D* h_btag_eff_l_medium;

  // Benchmarking
  int debug;
  double t_s0;
  double t_s1;
  double t_s2;
  double t_s3;
  double t_s4;
  double t_s5;
  double t_s6;
  double t_s7;
  double t_s8;
  double t_s9;
  TStopwatch *sw_s0;
  TStopwatch *sw_s1;
  TStopwatch *sw_s2;
  TStopwatch *sw_s3;
  TStopwatch *sw_s4;
  TStopwatch *sw_s5;
  TStopwatch *sw_s6;
  TStopwatch *sw_s7;
  TStopwatch *sw_s8;
  TStopwatch *sw_s9;

  void sw_(TStopwatch*, double&, bool start);
  
};


void ScaleFactors::init_input() {
  // B-tagging
  // Efficiencies (Oct31 - test)
  TFile* f;
  if (v.isFastSim)
    f = TFile::Open("btag_eff/SMS-T5ttcc.root");
  else if (v.isWJets)
    f = TFile::Open("btag_eff/WJetsToLNu.root");
  else if (v.isTop)
    f = TFile::Open("btag_eff/TT.root");
  else
    f = TFile::Open("btag_eff/QCD.root");
  if (v.year==2018) {
    eff_btag_b_loose  = ((TH2D*)f->Get("btag_eff_b_loose_2018"))->ProfileX();
    eff_btag_c_loose  = ((TH2D*)f->Get("btag_eff_c_loose_2018"))->ProfileX();
    eff_btag_l_loose  = ((TH2D*)f->Get("btag_eff_l_loose_2018"))->ProfileX();
    eff_btag_b_medium = ((TH2D*)f->Get("btag_eff_b_medium_2018"))->ProfileX();
    eff_btag_c_medium = ((TH2D*)f->Get("btag_eff_c_medium_2018"))->ProfileX();
    eff_btag_l_medium = ((TH2D*)f->Get("btag_eff_l_medium_2018"))->ProfileX();
  } else if (v.year==2017) {
    eff_btag_b_loose  = ((TH2D*)f->Get("btag_eff_b_loose_2017"))->ProfileX();
    eff_btag_c_loose  = ((TH2D*)f->Get("btag_eff_c_loose_2017"))->ProfileX();
    eff_btag_l_loose  = ((TH2D*)f->Get("btag_eff_l_loose_2017"))->ProfileX();
    eff_btag_b_medium = ((TH2D*)f->Get("btag_eff_b_medium_2017"))->ProfileX();
    eff_btag_c_medium = ((TH2D*)f->Get("btag_eff_c_medium_2017"))->ProfileX();
    eff_btag_l_medium = ((TH2D*)f->Get("btag_eff_l_medium_2017"))->ProfileX();
  } else if (v.isAPV) {
    eff_btag_b_loose  = ((TH2D*)f->Get("btag_eff_b_loose_2016APV"))->ProfileX();
    eff_btag_c_loose  = ((TH2D*)f->Get("btag_eff_c_loose_2016APV"))->ProfileX();
    eff_btag_l_loose  = ((TH2D*)f->Get("btag_eff_l_loose_2016APV"))->ProfileX();
    eff_btag_b_medium = ((TH2D*)f->Get("btag_eff_b_medium_2016APV"))->ProfileX();
    eff_btag_c_medium = ((TH2D*)f->Get("btag_eff_c_medium_2016APV"))->ProfileX();
    eff_btag_l_medium = ((TH2D*)f->Get("btag_eff_l_medium_2016APV"))->ProfileX();
  } else {
    eff_btag_b_loose  = ((TH2D*)f->Get("btag_eff_b_loose_2016"))->ProfileX();
    eff_btag_c_loose  = ((TH2D*)f->Get("btag_eff_c_loose_2016"))->ProfileX();
    eff_btag_l_loose  = ((TH2D*)f->Get("btag_eff_l_loose_2016"))->ProfileX();
    eff_btag_b_medium = ((TH2D*)f->Get("btag_eff_b_medium_2016"))->ProfileX();
    eff_btag_c_medium = ((TH2D*)f->Get("btag_eff_c_medium_2016"))->ProfileX();
    eff_btag_l_medium = ((TH2D*)f->Get("btag_eff_l_medium_2016"))->ProfileX();
  }
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
    btag_calib_full_ = new BTagCalibration("DeepCSV", "scale_factors/btag/wp_deepJet_106XUL18_v2.csv");
  } else if (v.year==2017) {
    btag_calib_full_ = new BTagCalibration("DeepCSV", "scale_factors/btag/wp_deepJet_106XUL17_v3.csv");
  } else {
    if(v.isAPV) btag_calib_full_ = new BTagCalibration("DeepCSV", "scale_factors/btag/wp_deepJet_106XUL16preVFP_v2.csv");
    else        btag_calib_full_ = new BTagCalibration("DeepCSV", "scale_factors/btag/wp_deepJet_106XUL16postVFP_v3.csv");
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
    btag_calib_fast_ =  new BTagCalibration("deepcsv", "scale_factors/btag/deepcsv_13TEV_18SL_7_5_2019.csv");
  } else if (v.year==2017) {
    // This file needed minor formatting to be readable
    // sed 's;^";;;s; "\;;;;s;"";";g;' scale_factors/btag/fastsim_csvv2_ttbar_26_1_2017.csv
    btag_calib_fast_ =  new BTagCalibration("deepcsv", "scale_factors/btag/deepcsv_13TEV_17SL_18_3_2019.csv");
  } else {
    btag_calib_fast_ =  new BTagCalibration("deepcsv", "scale_factors/btag/deepcsv_13TEV_16SL_18_3_2019.csv");
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
    // Ele - Data-FullSim    SF - Krisztina https://cernbox.cern.ch/s/TBfGJipStDRHSLA, https://cernbox.cern.ch/index.php/s/FtJgqfaNbtFtUMK
    eff_full_ele_veto                 = getplot_TH2F("scale_factors/electron/fullsim/passingVeto_UL2018_SF2D.root",      "EGamma_SF2D", "ele16");
    eff_full_ele_razor                = getplot_TH2F("scale_factors/electron/fullsim/passingRazor_UL2018_SF2D.root",     "EGamma_SF2D", "ele17");
    // Ele - FullSim-FastSim SF - https://twiki.cern.ch/twiki/bin/view/CMS/SUSLeptonSF?rev=210#FullSim_FastSim_TTBar_MC_compari
    eff_fast_ele_vetoid               = getplot_TH2D("scale_factors/electron/fastsim/detailed_ele_full_fast_sf_18.root", "CutBasedVetoNoIso94XV2_sf", "ele9");
    eff_fast_ele_looseid              = getplot_TH2D("scale_factors/electron/fastsim/detailed_ele_full_fast_sf_18.root", "CutBasedLooseNoIso94XV2_sf", "ele10");
    eff_fast_ele_mediumid             = getplot_TH2D("scale_factors/electron/fastsim/detailed_ele_full_fast_sf_18.root", "CutBasedMediumNoIso94XV1_sf", "ele11");
    eff_fast_ele_mvalooseid_tightip2d = getplot_TH2D("scale_factors/electron/fastsim/detailed_ele_full_fast_sf_18.root", "MVAVLooseIP2D_sf", "ele12");
    eff_fast_ele_miniiso01            = getplot_TH2D("scale_factors/electron/fastsim/detailed_ele_full_fast_sf_18.root", "MVAVLooseTightIP2DMini_sf", "ele13");
    eff_fast_ele_miniiso02            = getplot_TH2D("scale_factors/electron/fastsim/detailed_ele_full_fast_sf_18.root", "MVAVLooseTightIP2DMini2_sf", "ele14");
    eff_fast_ele_miniiso04            = getplot_TH2D("scale_factors/electron/fastsim/detailed_ele_full_fast_sf_18.root", "MVAVLooseTightIP2DMini4_sf", "ele15");
    eff_full_pho_mediumid             = getplot_TH2F("scale_factors/photon/fullsim/egammaEffi.txt_EGM2D_Pho_Med_UL18.root","EGamma_SF2D","pho1");
    // Inclusive Razor Scale Factors
    //eff_full_ele_veto                 = getplot_TH2F("scale_factors/RazorRunAuxFiles_Expanded/"
  	//						  "efficiency_results_VetoElectronSelectionEffDenominatorGen_2016_Rereco_Golden.root",
  	//						  "ScaleFactor_VetoElectronSelectionEffDenominatorGen", "ele16");//2017
  
    // Muon Tracking eff     SF - https://twiki.cern.ch/twiki/bin/view/CMS/SUSLeptonSF?rev=210#FullSim_FastSim_TTBar_MC_com_AN1
    //eff_full_muon_trk   		    = getplot_TGraphAsymmErrors("scale_factors/muon/tracking/Tracking_EfficienciesAndSF_BCDEFGH.root", "ratio_eff_eta3_dr030e030_corr", "mu1");
    //eff_full_muon_trk_veto	    = getplot_TGraphAsymmErrors("scale_factors/muon/tracking/Tracking_EfficienciesAndSF_BCDEFGH.root", "ratio_eff_eta3_tk0_dr030e030_corr", "mu2");
    // Muon Data-FullSim     SF - https://twiki.cern.ch/twiki/bin/view/CMS/SUSLeptonSF?rev=210#Data_leading_order_FullSim_M_AN1
    eff_full_muon_looseid		    = getplot_TH2F("scale_factors/muon/fullsim/RunABCD_SF_ID.root",  "NUM_SoftID_DEN_TrackerMuons_pt_abseta",    "mu3");
    eff_full_muon_mediumid	    = getplot_TH2F("scale_factors/muon/fullsim/RunABCD_SF_ID.root",  "NUM_MediumID_DEN_TrackerMuons_pt_abseta",  "mu4");
    eff_full_muon_miniiso04	    = getplot_TH2F("scale_factors/muon/fullsim/RunABCD_SF_ID.root", "NUM_LooseID_DEN_TrackerMuons_pt_abseta", "mu5");
    eff_full_muon_miniiso02	    = getplot_TH2F("scale_factors/muon/fullsim/RunABCD_SF_ID.root", "NUM_TightID_DEN_TrackerMuons_pt_abseta","mu6");
		eff_full_muon_razor					= getplot_TH2F("scale_factors/muon/fullsim/NUM_RazorPass_UL2018_DEN_genTracks_abseta_pt.root", "NUM_RazorPass_DEN_genTracks_abseta_pt", "mu7");
		eff_full_muon_veto					= getplot_TH2F("scale_factors/muon/fullsim/NUM_RazorVeto_UL2018_DEN_genTracks_abseta_pt.root", "NUM_RazorVeto_DEN_genTracks_abseta_pt", "mu8");
    // Muon FullSim-FastSim  SF - https://twiki.cern.ch/twiki/bin/view/CMS/SUSLeptonSF?rev=210#FullSim_FastSim_TTBar_MC_com_AN1
    eff_fast_muon_vetoid		    = getplot_TH2D("scale_factors/muon/fastsim/detailed_mu_full_fast_sf_18.root", "miniIso04_LooseId_sf", "mu10");
    eff_fast_muon_looseid		    = getplot_TH2D("scale_factors/muon/fastsim/detailed_mu_full_fast_sf_18.root", "miniIso02_LooseId_sf", "mu9");
    eff_fast_muon_mediumid	    = getplot_TH2D("scale_factors/muon/fastsim/detailed_mu_full_fast_sf_18.root", "miniIso02_MediumId_sf","mu11");
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
    // Ele - Data-FullSim    SF - Krisztina https://cernbox.cern.ch/s/TBfGJipStDRHSLA, https://cernbox.cern.ch/index.php/s/FtJgqfaNbtFtUMK
    eff_full_ele_veto                 = getplot_TH2F("scale_factors/electron/fullsim/passingVeto_UL2017_SF2D.root",      "EGamma_SF2D", "ele16");
    eff_full_ele_razor                = getplot_TH2F("scale_factors/electron/fullsim/passingRazor_UL2017_SF2D.root",     "EGamma_SF2D", "ele17");
    // Ele - FullSim-FastSim SF - https://twiki.cern.ch/twiki/bin/view/CMS/SUSLeptonSF?rev=210#FullSim_FastSim_TTBar_MC_compari
    eff_fast_ele_vetoid               = getplot_TH2D("scale_factors/electron/fastsim/detailed_ele_full_fast_sf_17.root",  "CutBasedVetoNoIso94XV2_sf", "ele9");
    eff_fast_ele_looseid              = getplot_TH2D("scale_factors/electron/fastsim/detailed_ele_full_fast_sf_17.root",  "CutBasedLooseNoIso94XV2_sf", "ele10");
    eff_fast_ele_mediumid             = getplot_TH2D("scale_factors/electron/fastsim/detailed_ele_full_fast_sf_17.root",  "CutBasedMediumNoIso94XV2_sf", "ele11");
    eff_fast_ele_mvalooseid_tightip2d = getplot_TH2D("scale_factors/electron/fastsim/detailed_ele_full_fast_sf_17.root",  "MVAVLooseIP2D_sf", "ele12");
    eff_fast_ele_miniiso01            = getplot_TH2D("scale_factors/electron/fastsim/detailed_ele_full_fast_sf_17.root",  "MVAVLooseTightIP2DMini_sf", "ele13");
    eff_fast_ele_miniiso02            = getplot_TH2D("scale_factors/electron/fastsim/detailed_ele_full_fast_sf_17.root",  "MVAVLooseTightIP2DMini2_sf", "ele14");
    eff_fast_ele_miniiso04            = getplot_TH2D("scale_factors/electron/fastsim/detailed_ele_full_fast_sf_17.root",  "MVAVLooseTightIP2DMini4_sf", "ele15");
    eff_full_pho_mediumid             = getplot_TH2F("scale_factors/photon/fullsim/egammaEffi.txt_EGM2D_PHO_Medium_UL17.root","EGamma_SF2D","pho1");
    // Inclusive Razor Scale Factors
    //eff_full_ele_veto                 = getplot_TH2F("scale_factors/RazorRunAuxFiles_Expanded/"
    //                                                 "efficiency_results_VetoElectronSelectionEffDenominatorGen_2016_Rereco_Golden.root",
    //                                                 "ScaleFactor_VetoElectronSelectionEffDenominatorGen", "ele16");
  
    // Muon Tracking eff     SF - https://twiki.cern.ch/twiki/bin/view/CMS/SUSLeptonSF?rev=210#FullSim_FastSim_TTBar_MC_com_AN1
    //eff_full_muon_trk   		    = getplot_TGraphAsymmErrors("scale_factors/muon/tracking/Tracking_EfficienciesAndSF_BCDEFGH.root", "ratio_eff_eta3_dr030e030_corr", "mu1");
    //eff_full_muon_trk_veto	    = getplot_TGraphAsymmErrors("scale_factors/muon/tracking/Tracking_EfficienciesAndSF_BCDEFGH.root", "ratio_eff_eta3_tk0_dr030e030_corr", "mu2");
    // Muon Data-FullSim     SF - https://twiki.cern.ch/twiki/bin/view/CMS/SUSLeptonSF?rev=210#Data_leading_order_FullSim_M_AN1
    eff_full_muon_looseid		    = getplot_TH2F("scale_factors/muon/fullsim/RunBCDEF_SF_ID.root",  "NUM_SoftID_DEN_genTracks_pt_abseta",    "mu3");
    eff_full_muon_mediumid	    = getplot_TH2F("scale_factors/muon/fullsim/RunBCDEF_SF_ID.root",  "NUM_MediumID_DEN_genTracks_pt_abseta",  "mu4");
    eff_full_muon_miniiso04	    = getplot_TH2F("scale_factors/muon/fullsim/RunBCDEF_SF_ISO.root", "NUM_LooseRelIso_DEN_LooseID_pt_abseta", "mu5");
    eff_full_muon_miniiso02	    = getplot_TH2F("scale_factors/muon/fullsim/RunBCDEF_SF_ISO.root", "NUM_TightRelIso_DEN_MediumID_pt_abseta","mu6");
		eff_full_muon_razor					= getplot_TH2F("scale_factors/muon/fullsim/NUM_RazorPass_UL2017_DEN_genTracks_abseta_pt.root", "NUM_RazorPass_DEN_genTracks_abseta_pt", "mu7");
		eff_full_muon_veto					= getplot_TH2F("scale_factors/muon/fullsim/NUM_RazorVeto_UL2017_DEN_genTracks_abseta_pt.root", "NUM_RazorVeto_DEN_genTracks_abseta_pt", "mu8");
    // Muon FullSim-FastSim  SF - https://twiki.cern.ch/twiki/bin/view/CMS/SUSLeptonSF?rev=210#FullSim_FastSim_TTBar_MC_com_AN1
    eff_fast_muon_vetoid		    = getplot_TH2D("scale_factors/muon/fastsim/detailed_mu_full_fast_sf_17.root", "miniIso02_LooseId_sf", "mu9");
    eff_fast_muon_looseid		    = getplot_TH2D("scale_factors/muon/fastsim/detailed_mu_full_fast_sf_17.root", "miniIso04_LooseId_sf", "mu10");
    eff_fast_muon_mediumid	    = getplot_TH2D("scale_factors/muon/fastsim/detailed_mu_full_fast_sf_17.root", "miniIso02_MediumId_sf","mu11");
    // Inclusive Razor Scale Factors
  } else if(v.isAPV) {
    // Ele - Reconstruction  SF - https://twiki.cern.ch/twiki/bin/view/CMS/EgammaIDRecipesRun2?rev=38#Electron_efficiencies_and_scale
    eff_full_ele_reco                 = getplot_TH2F("scale_factors/electron/reco/egammaEffi.txt_EGM2D_runBCDEF_passingRECO.root","EGamma_SF2D", "ele1");
    // Ele - Data-FullSim    SF - https://twiki.cern.ch/twiki/bin/view/CMS/SUSLeptonSF?rev=210#Data_leading_order_FullSim_MC_co
    eff_full_ele_vetoid               = getplot_TH2F("scale_factors/electron/fullsim/ElectronScaleFactors_Run2016.root","Run2016_CutBasedVetoNoIso94XV2"  ,"ele2");
    eff_full_ele_looseid              = getplot_TH2F("scale_factors/electron/fullsim/ElectronScaleFactors_Run2016.root","Run2016_CutBasedLooseNoIso94XV2" ,"ele3");
    eff_full_ele_mediumid             = getplot_TH2F("scale_factors/electron/fullsim/ElectronScaleFactors_Run2016.root","Run2016_CutBasedMediumNoIso94XV2","ele4");
    eff_full_ele_mvalooseid_tightip2d = getplot_TH2F("scale_factors/electron/fullsim/ElectronScaleFactors_Run2016.root","Run2016_MVAVLooseIP2D"           ,"ele5");
    eff_full_ele_miniiso01            = getplot_TH2F("scale_factors/electron/fullsim/ElectronScaleFactors_Run2016.root","Run2016_Mini"  ,"ele6");
    eff_full_ele_miniiso02            = getplot_TH2F("scale_factors/electron/fullsim/ElectronScaleFactors_Run2016.root","Run2016_Mini2" ,"ele7");
    eff_full_ele_miniiso04            = getplot_TH2F("scale_factors/electron/fullsim/ElectronScaleFactors_Run2016.root","Run2016_Mini4" ,"ele8");
    // Ele - Data-FullSim    SF - Krisztina https://cernbox.cern.ch/s/TBfGJipStDRHSLA, https://cernbox.cern.ch/index.php/s/FtJgqfaNbtFtUMK
    eff_full_ele_veto                 = getplot_TH2F("scale_factors/electron/fullsim/passingVeto_UL2016preVFP_SF2D.root",      "EGamma_SF2D", "ele16");
    eff_full_ele_razor                = getplot_TH2F("scale_factors/electron/fullsim/passingRazor_UL2016preVFP_SF2D.root",     "EGamma_SF2D", "ele17");
    // Ele - FullSim-FastSim SF - https://twiki.cern.ch/twiki/bin/view/CMS/SUSLeptonSF?rev=210#FullSim_FastSim_TTBar_MC_compari
    eff_fast_ele_vetoid               = getplot_TH2D("scale_factors/electron/fastsim/detailed_ele_full_fast_sf_17.root",  "CutBasedVetoNoIso94XV2_sf", "ele9");
    eff_fast_ele_looseid              = getplot_TH2D("scale_factors/electron/fastsim/detailed_ele_full_fast_sf_17.root",  "CutBasedLooseNoIso94XV2_sf", "ele10");
    eff_fast_ele_mediumid             = getplot_TH2D("scale_factors/electron/fastsim/detailed_ele_full_fast_sf_17.root",  "CutBasedMediumNoIso94XV2_sf", "ele11");
    eff_fast_ele_mvalooseid_tightip2d = getplot_TH2D("scale_factors/electron/fastsim/detailed_ele_full_fast_sf_17.root",  "MVAVLooseIP2D_sf", "ele12");
    eff_fast_ele_miniiso01            = getplot_TH2D("scale_factors/electron/fastsim/detailed_ele_full_fast_sf_17.root",  "MVAVLooseTightIP2DMini_sf", "ele13");
    eff_fast_ele_miniiso02            = getplot_TH2D("scale_factors/electron/fastsim/detailed_ele_full_fast_sf_17.root",  "MVAVLooseTightIP2DMini2_sf", "ele14");
    eff_fast_ele_miniiso04            = getplot_TH2D("scale_factors/electron/fastsim/detailed_ele_full_fast_sf_17.root",  "MVAVLooseTightIP2DMini4_sf", "ele15");
    eff_full_pho_mediumid             = getplot_TH2F("scale_factors/photon/fullsim/egammaEffi.txt_EGM2D_Pho_Medium_UL16.root","EGamma_SF2D","pho1");
    // Inclusive Razor Scale Factors
    //eff_full_ele_veto                 = getplot_TH2F("scale_factors/RazorRunAuxFiles_Expanded/"
    //                                                 "efficiency_results_VetoElectronSelectionEffDenominatorGen_2016_Rereco_Golden.root",
    //                                                 "ScaleFactor_VetoElectronSelectionEffDenominatorGen", "ele16");
  
    // Muon Tracking eff     SF - https://twiki.cern.ch/twiki/bin/view/CMS/SUSLeptonSF?rev=210#FullSim_FastSim_TTBar_MC_com_AN1
    //eff_full_muon_trk   		    = getplot_TGraphAsymmErrors("scale_factors/muon/tracking/Tracking_EfficienciesAndSF_BCDEFGH.root", "ratio_eff_eta3_dr030e030_corr", "mu1");
    //eff_full_muon_trk_veto	    = getplot_TGraphAsymmErrors("scale_factors/muon/tracking/Tracking_EfficienciesAndSF_BCDEFGH.root", "ratio_eff_eta3_tk0_dr030e030_corr", "mu2");
    // Muon Data-FullSim     SF - https://twiki.cern.ch/twiki/bin/view/CMS/SUSLeptonSF?rev=210#Data_leading_order_FullSim_M_AN1
    eff_full_muon_looseid		    = getplot_TH2F("scale_factors/muon/fullsim/TnP_NUM_LooseID_DENOM_generalTracks_VAR_map_pt_eta.root", "SF", "mu3");
    eff_full_muon_mediumid	    = getplot_TH2F("scale_factors/muon/fullsim/TnP_NUM_MediumID_DENOM_generalTracks_VAR_map_pt_eta.root","SF", "mu4");
    eff_full_muon_miniiso04	    = getplot_TH2F("scale_factors/muon/fullsim/TnP_NUM_MiniIsoLoose_DENOM_LooseID_VAR_map_pt_eta.root",  "SF", "mu5");
    eff_full_muon_miniiso02	    = getplot_TH2F("scale_factors/muon/fullsim/TnP_NUM_MiniIsoTight_DENOM_LooseID_VAR_map_pt_eta.root",  "SF", "mu6");
		eff_full_muon_razor					= getplot_TH2F("scale_factors/muon/fullsim/NUM_RazorPass_UL2016APV_DEN_genTracks_abseta_pt.root", "NUM_RazorPass_DEN_genTracks_abseta_pt", "mu7");
		eff_full_muon_veto					= getplot_TH2F("scale_factors/muon/fullsim/NUM_RazorVeto_UL2016APV_DEN_genTracks_abseta_pt.root", "NUM_RazorVeto_DEN_genTracks_abseta_pt", "mu8");
    // Muon FullSim-FastSim  SF - https://twiki.cern.ch/twiki/bin/view/CMS/SUSLeptonSF?rev=210#FullSim_FastSim_TTBar_MC_com_AN1
    eff_fast_muon_vetoid		    = getplot_TH2D("scale_factors/muon/fastsim/detailed_mu_full_fast_sf_17.root", "miniIso02_LooseId_sf", "mu9");
    eff_fast_muon_looseid		    = getplot_TH2D("scale_factors/muon/fastsim/detailed_mu_full_fast_sf_17.root", "miniIso04_LooseId_sf", "mu10");
    eff_fast_muon_mediumid	    = getplot_TH2D("scale_factors/muon/fastsim/detailed_mu_full_fast_sf_17.root", "miniIso02_MediumId_sf","mu11");
    // Inclusive Razor Scale Factors
  } else {
    // Ele - Reconstruction  SF - https://twiki.cern.ch/twiki/bin/view/CMS/EgammaIDRecipesRun2?rev=38#Electron_efficiencies_and_scale
    eff_full_ele_reco                 = getplot_TH2F("scale_factors/electron/reco/egammaEffi.txt_EGM2D_runBCDEF_passingRECO.root","EGamma_SF2D", "ele1");
    // Ele - Data-FullSim    SF - https://twiki.cern.ch/twiki/bin/view/CMS/SUSLeptonSF?rev=210#Data_leading_order_FullSim_MC_co
    eff_full_ele_vetoid               = getplot_TH2F("scale_factors/electron/fullsim/ElectronScaleFactors_Run2016.root","Run2016_CutBasedVetoNoIso94XV2"  ,"ele2");
    eff_full_ele_looseid              = getplot_TH2F("scale_factors/electron/fullsim/ElectronScaleFactors_Run2016.root","Run2016_CutBasedLooseNoIso94XV2" ,"ele3");
    eff_full_ele_mediumid             = getplot_TH2F("scale_factors/electron/fullsim/ElectronScaleFactors_Run2016.root","Run2016_CutBasedMediumNoIso94XV2","ele4");
    eff_full_ele_mvalooseid_tightip2d = getplot_TH2F("scale_factors/electron/fullsim/ElectronScaleFactors_Run2016.root","Run2016_MVAVLooseIP2D"           ,"ele5");
    eff_full_ele_miniiso01            = getplot_TH2F("scale_factors/electron/fullsim/ElectronScaleFactors_Run2016.root","Run2016_Mini"  ,"ele6");
    eff_full_ele_miniiso02            = getplot_TH2F("scale_factors/electron/fullsim/ElectronScaleFactors_Run2016.root","Run2016_Mini2" ,"ele7");
    eff_full_ele_miniiso04            = getplot_TH2F("scale_factors/electron/fullsim/ElectronScaleFactors_Run2016.root","Run2016_Mini4" ,"ele8");
    // Ele - Data-FullSim    SF - Krisztina https://cernbox.cern.ch/s/TBfGJipStDRHSLA, https://cernbox.cern.ch/index.php/s/FtJgqfaNbtFtUMK
    eff_full_ele_veto                 = getplot_TH2F("scale_factors/electron/fullsim/passingVeto_UL2016postVFP_SF2D.root",      "EGamma_SF2D", "ele16");
    eff_full_ele_razor                = getplot_TH2F("scale_factors/electron/fullsim/passingRazor_UL2016postVFP_SF2D.root",     "EGamma_SF2D", "ele17");
    // Ele - FullSim-FastSim SF - https://twiki.cern.ch/twiki/bin/view/CMS/SUSLeptonSF?rev=210#FullSim_FastSim_TTBar_MC_compari
    eff_fast_ele_vetoid               = getplot_TH2D("scale_factors/electron/fastsim/detailed_ele_full_fast_sf_17.root",  "CutBasedVetoNoIso94XV2_sf", "ele9");
    eff_fast_ele_looseid              = getplot_TH2D("scale_factors/electron/fastsim/detailed_ele_full_fast_sf_17.root",  "CutBasedLooseNoIso94XV2_sf", "ele10");
    eff_fast_ele_mediumid             = getplot_TH2D("scale_factors/electron/fastsim/detailed_ele_full_fast_sf_17.root",  "CutBasedMediumNoIso94XV2_sf", "ele11");
    eff_fast_ele_mvalooseid_tightip2d = getplot_TH2D("scale_factors/electron/fastsim/detailed_ele_full_fast_sf_17.root",  "MVAVLooseIP2D_sf", "ele12");
    eff_fast_ele_miniiso01            = getplot_TH2D("scale_factors/electron/fastsim/detailed_ele_full_fast_sf_17.root",  "MVAVLooseTightIP2DMini_sf", "ele13");
    eff_fast_ele_miniiso02            = getplot_TH2D("scale_factors/electron/fastsim/detailed_ele_full_fast_sf_17.root",  "MVAVLooseTightIP2DMini2_sf", "ele14");
    eff_fast_ele_miniiso04            = getplot_TH2D("scale_factors/electron/fastsim/detailed_ele_full_fast_sf_17.root",  "MVAVLooseTightIP2DMini4_sf", "ele15");
    eff_full_pho_mediumid             = getplot_TH2F("scale_factors/photon/fullsim/egammaEffi.txt_EGM2D_Pho_Medium_UL16_postVFP.root","EGamma_SF2D","pho1");
    // Inclusive Razor Scale Factors
    //eff_full_ele_veto                 = getplot_TH2F("scale_factors/RazorRunAuxFiles_Expanded/"
    //                                                 "efficiency_results_VetoElectronSelectionEffDenominatorGen_2016_Rereco_Golden.root",
    //                                                 "ScaleFactor_VetoElectronSelectionEffDenominatorGen", "ele16");
  
    // Muon Tracking eff     SF - https://twiki.cern.ch/twiki/bin/view/CMS/SUSLeptonSF?rev=210#FullSim_FastSim_TTBar_MC_com_AN1
    //eff_full_muon_trk   		    = getplot_TGraphAsymmErrors("scale_factors/muon/tracking/Tracking_EfficienciesAndSF_BCDEFGH.root", "ratio_eff_eta3_dr030e030_corr", "mu1");
    //eff_full_muon_trk_veto	    = getplot_TGraphAsymmErrors("scale_factors/muon/tracking/Tracking_EfficienciesAndSF_BCDEFGH.root", "ratio_eff_eta3_tk0_dr030e030_corr", "mu2");
    // Muon Data-FullSim     SF - https://twiki.cern.ch/twiki/bin/view/CMS/SUSLeptonSF?rev=210#Data_leading_order_FullSim_M_AN1
    eff_full_muon_looseid		    = getplot_TH2F("scale_factors/muon/fullsim/TnP_NUM_LooseID_DENOM_generalTracks_VAR_map_pt_eta.root", "SF", "mu3");
    eff_full_muon_mediumid	    = getplot_TH2F("scale_factors/muon/fullsim/TnP_NUM_MediumID_DENOM_generalTracks_VAR_map_pt_eta.root","SF", "mu4");
    eff_full_muon_miniiso04	    = getplot_TH2F("scale_factors/muon/fullsim/TnP_NUM_MiniIsoLoose_DENOM_LooseID_VAR_map_pt_eta.root",  "SF", "mu5");
    eff_full_muon_miniiso02	    = getplot_TH2F("scale_factors/muon/fullsim/TnP_NUM_MiniIsoTight_DENOM_LooseID_VAR_map_pt_eta.root",  "SF", "mu6");
		eff_full_muon_razor					= getplot_TH2F("scale_factors/muon/fullsim/NUM_RazorPass_UL2016_DEN_genTracks_abseta_pt.root", "NUM_RazorPass_DEN_genTracks_abseta_pt", "mu7");
		eff_full_muon_veto					= getplot_TH2F("scale_factors/muon/fullsim/NUM_RazorVeto_UL2016_DEN_genTracks_abseta_pt.root", "NUM_RazorVeto_DEN_genTracks_abseta_pt", "mu8");
    // Muon FullSim-FastSim  SF - https://twiki.cern.ch/twiki/bin/view/CMS/SUSLeptonSF?rev=210#FullSim_FastSim_TTBar_MC_com_AN1
    eff_fast_muon_vetoid		    = getplot_TH2D("scale_factors/muon/fastsim/detailed_mu_full_fast_sf_17.root", "miniIso02_LooseId_sf", "mu9");
    eff_fast_muon_looseid		    = getplot_TH2D("scale_factors/muon/fastsim/detailed_mu_full_fast_sf_17.root", "miniIso04_LooseId_sf", "mu10");
    eff_fast_muon_mediumid	    = getplot_TH2D("scale_factors/muon/fastsim/detailed_mu_full_fast_sf_17.root", "miniIso02_MediumId_sf","mu11");
    // Inclusive Razor Scale Factors
  }

  // W/Top (anti-/mass-)tag (and fake rate) scale factors
  if (v.year==2018) {
    eff_full_fake_bLepTop = getplot_TGraphAsymmErrors("scale_factors/boosted_objects/Top_W_Z_H_fakes.root", "full_fake_2018_bLepTop", "full_fake_LepTop_barrel");
    eff_full_fake_eLepTop = getplot_TGraphAsymmErrors("scale_factors/boosted_objects/Top_W_Z_H_fakes.root", "full_fake_2018_eLepTop", "full_fake_LepTop_endcap");
    eff_full_fake_bHadTop = getplot_TGraphAsymmErrors("scale_factors/boosted_objects/Top_W_Z_H_fakes.root", "full_fake_2018_bHadTop", "full_fake_HadTop_barrel");
    eff_full_fake_eHadTop = getplot_TGraphAsymmErrors("scale_factors/boosted_objects/Top_W_Z_H_fakes.root", "full_fake_2018_eHadTop", "full_fake_HadTop_endcap");
    eff_full_fake_bHadV   = getplot_TGraphAsymmErrors("scale_factors/boosted_objects/Top_W_Z_H_fakes.root", "full_fake_2018_bHadV",   "full_fake_HadV_barrel");
    eff_full_fake_eHadV   = getplot_TGraphAsymmErrors("scale_factors/boosted_objects/Top_W_Z_H_fakes.root", "full_fake_2018_eHadV",   "full_fake_HadV_endcap");
    eff_full_fake_bHadH   = getplot_TGraphAsymmErrors("scale_factors/boosted_objects/Top_W_Z_H_fakes.root", "full_fake_2018_bHadH",   "full_fake_HadH_barrel");
    eff_full_fake_eHadH   = getplot_TGraphAsymmErrors("scale_factors/boosted_objects/Top_W_Z_H_fakes.root", "full_fake_2018_eHadH",   "full_fake_HadH_endcap");
    eff_full_fake_bHadHTop= getplot_TGraphAsymmErrors("scale_factors/boosted_objects/Top_W_Z_H_fakes.root", "full_fake_2018_bHadHTop","full_fake_HadH_top_barrel");
    eff_full_fake_eHadHTop= getplot_TGraphAsymmErrors("scale_factors/boosted_objects/Top_W_Z_H_fakes.root", "full_fake_2018_eHadHTop","full_fake_HadH_top_endcap");
    eff_full_fake_bMass   = getplot_TGraphAsymmErrors("scale_factors/boosted_objects/Top_W_Z_H_fakes.root", "full_fake_2018_bMass",   "full_fake_Mass_barrel");
    eff_full_fake_eMass   = getplot_TGraphAsymmErrors("scale_factors/boosted_objects/Top_W_Z_H_fakes.root", "full_fake_2018_eMass",   "full_fake_Mass_endcap");
    eff_full_bMassTop     = getplot_TGraphAsymmErrors("scale_factors/boosted_objects/Top_W_Z_H_fakes.root", "full_real_2018_bMassTop","full_real_MassTop_barrel");
    eff_full_eMassTop     = getplot_TGraphAsymmErrors("scale_factors/boosted_objects/Top_W_Z_H_fakes.root", "full_real_2018_eMassTop","full_real_MassTop_endcap");
    eff_full_POG_Top      = getplot_TH1D("scale_factors/w_top_tag/2017TopTaggingScaleFactors.root",            "PUPPI_wp2_btag/sf_mergedTop_nominal", "full_POG_Top");
    eff_full_POG_Top_up   = getplot_TH1D("scale_factors/w_top_tag/2017TopTaggingScaleFactors.root",            "PUPPI_wp2_btag/sf_mergedTop_up", "full_POG_Top_up");
    eff_full_POG_Top_down = getplot_TH1D("scale_factors/w_top_tag/2017TopTaggingScaleFactors.root",            "PUPPI_wp2_btag/sf_mergedTop_down", "full_POG_Top_down");
    eff_full_POG_W        = getplot_TGraphErrors("scale_factors/w_top_tag/SF_tau21_0p45_ptDependence_200to600GeV.root","Graph",       "full_POG_W");
    
    eff_fast_V           = getplot_TGraphAsymmErrors("scale_factors/boosted_objects/Top_W_Z_H_fakes.root", "full_fast_2018_HadV",  "fast_V");
    eff_fast_W           = getplot_TGraphAsymmErrors("scale_factors/boosted_objects/Top_W_Z_H_fakes.root", "full_fast_2018_HadW",  "fast_W");
    eff_fast_Z           = getplot_TGraphAsymmErrors("scale_factors/boosted_objects/Top_W_Z_H_fakes.root", "full_fast_2018_HadZ",  "fast_Z");
    eff_fast_H           = getplot_TGraphAsymmErrors("scale_factors/boosted_objects/Top_W_Z_H_fakes.root", "full_fast_2018_HadH",  "fast_H");
    eff_fast_HadTop      = getplot_TGraphAsymmErrors("scale_factors/boosted_objects/Top_W_Z_H_fakes.root", "full_fast_2018_HadTop","fast_HadTop");
    eff_fast_LepTop      = getplot_TGraphAsymmErrors("scale_factors/boosted_objects/Top_W_Z_H_fakes.root", "full_fast_2018_LepTop","fast_LepTop");
  } else if (v.year==2017) {
    eff_full_fake_bLepTop = getplot_TGraphAsymmErrors("scale_factors/boosted_objects/Top_W_Z_H_fakes.root", "full_fake_2017_bLepTop", "full_fake_LepTop_barrel");
    eff_full_fake_eLepTop = getplot_TGraphAsymmErrors("scale_factors/boosted_objects/Top_W_Z_H_fakes.root", "full_fake_2017_eLepTop", "full_fake_LepTop_endcap");
    eff_full_fake_bHadTop = getplot_TGraphAsymmErrors("scale_factors/boosted_objects/Top_W_Z_H_fakes.root", "full_fake_2017_bHadTop", "full_fake_HadTop_barrel");
    eff_full_fake_eHadTop = getplot_TGraphAsymmErrors("scale_factors/boosted_objects/Top_W_Z_H_fakes.root", "full_fake_2017_eHadTop", "full_fake_HadTop_endcap");
    eff_full_fake_bHadV   = getplot_TGraphAsymmErrors("scale_factors/boosted_objects/Top_W_Z_H_fakes.root", "full_fake_2017_bHadV",   "full_fake_HadV_barrel");
    eff_full_fake_eHadV   = getplot_TGraphAsymmErrors("scale_factors/boosted_objects/Top_W_Z_H_fakes.root", "full_fake_2017_eHadV",   "full_fake_HadV_endcap");
    eff_full_fake_bHadH   = getplot_TGraphAsymmErrors("scale_factors/boosted_objects/Top_W_Z_H_fakes.root", "full_fake_2017_bHadH",   "full_fake_HadH_barrel");
    eff_full_fake_eHadH   = getplot_TGraphAsymmErrors("scale_factors/boosted_objects/Top_W_Z_H_fakes.root", "full_fake_2017_eHadH",   "full_fake_HadH_endcap");
    eff_full_fake_bHadHTop= getplot_TGraphAsymmErrors("scale_factors/boosted_objects/Top_W_Z_H_fakes.root", "full_fake_2017_bHadHTop","full_fake_HadH_top_barrel");
    eff_full_fake_eHadHTop= getplot_TGraphAsymmErrors("scale_factors/boosted_objects/Top_W_Z_H_fakes.root", "full_fake_2017_eHadHTop","full_fake_HadH_top_endcap");
    eff_full_fake_bMass   = getplot_TGraphAsymmErrors("scale_factors/boosted_objects/Top_W_Z_H_fakes.root", "full_fake_2017_bMass",   "full_fake_Mass_barrel");
    eff_full_fake_eMass   = getplot_TGraphAsymmErrors("scale_factors/boosted_objects/Top_W_Z_H_fakes.root", "full_fake_2017_eMass",   "full_fake_Mass_endcap");
    eff_full_bMassTop     = getplot_TGraphAsymmErrors("scale_factors/boosted_objects/Top_W_Z_H_fakes.root", "full_real_2017_bMassTop","full_real_MassTop_barrel");
    eff_full_eMassTop     = getplot_TGraphAsymmErrors("scale_factors/boosted_objects/Top_W_Z_H_fakes.root", "full_real_2017_eMassTop","full_real_MassTop_endcap");
    eff_full_POG_Top      = getplot_TH1D("scale_factors/w_top_tag/2017TopTaggingScaleFactors.root",            "PUPPI_wp2_btag/sf_mergedTop_nominal", "full_POG_Top");
    eff_full_POG_Top_up   = getplot_TH1D("scale_factors/w_top_tag/2017TopTaggingScaleFactors.root",            "PUPPI_wp2_btag/sf_mergedTop_up", "full_POG_Top_up");
    eff_full_POG_Top_down = getplot_TH1D("scale_factors/w_top_tag/2017TopTaggingScaleFactors.root",            "PUPPI_wp2_btag/sf_mergedTop_down", "full_POG_Top_down");
    eff_full_POG_W        = getplot_TGraphErrors("scale_factors/w_top_tag/SF_tau21_0p45_ptDependence_200to600GeV.root","Graph",       "full_POG_W");
    
    eff_fast_V           = getplot_TGraphAsymmErrors("scale_factors/boosted_objects/Top_W_Z_H_fakes.root", "full_fast_2017_HadV",  "fast_V");
    eff_fast_W           = getplot_TGraphAsymmErrors("scale_factors/boosted_objects/Top_W_Z_H_fakes.root", "full_fast_2017_HadW",  "fast_W");
    eff_fast_Z           = getplot_TGraphAsymmErrors("scale_factors/boosted_objects/Top_W_Z_H_fakes.root", "full_fast_2017_HadZ",  "fast_Z");
    eff_fast_H           = getplot_TGraphAsymmErrors("scale_factors/boosted_objects/Top_W_Z_H_fakes.root", "full_fast_2017_HadH",  "fast_H");
    eff_fast_HadTop      = getplot_TGraphAsymmErrors("scale_factors/boosted_objects/Top_W_Z_H_fakes.root", "full_fast_2017_HadTop","fast_HadTop");
    eff_fast_LepTop      = getplot_TGraphAsymmErrors("scale_factors/boosted_objects/Top_W_Z_H_fakes.root", "full_fast_2017_LepTop","fast_LepTop");
  } else if(v.isAPV) {
    eff_full_fake_bLepTop = getplot_TGraphAsymmErrors("scale_factors/boosted_objects/Top_W_Z_H_fakes.root", "full_fake_2016_bLepTop", "full_fake_LepTop_barrel");
    eff_full_fake_eLepTop = getplot_TGraphAsymmErrors("scale_factors/boosted_objects/Top_W_Z_H_fakes.root", "full_fake_2016_eLepTop", "full_fake_LepTop_endcap");
    eff_full_fake_bHadTop = getplot_TGraphAsymmErrors("scale_factors/boosted_objects/Top_W_Z_H_fakes.root", "full_fake_2016_bHadTop", "full_fake_HadTop_barrel");
    eff_full_fake_eHadTop = getplot_TGraphAsymmErrors("scale_factors/boosted_objects/Top_W_Z_H_fakes.root", "full_fake_2016_eHadTop", "full_fake_HadTop_endcap");
    eff_full_fake_bHadV   = getplot_TGraphAsymmErrors("scale_factors/boosted_objects/Top_W_Z_H_fakes.root", "full_fake_2016_bHadV",   "full_fake_HadV_barrel");
    eff_full_fake_eHadV   = getplot_TGraphAsymmErrors("scale_factors/boosted_objects/Top_W_Z_H_fakes.root", "full_fake_2016_eHadV",   "full_fake_HadV_endcap");
    eff_full_fake_bHadH   = getplot_TGraphAsymmErrors("scale_factors/boosted_objects/Top_W_Z_H_fakes.root", "full_fake_2016_bHadH",   "full_fake_HadH_barrel");
    eff_full_fake_eHadH   = getplot_TGraphAsymmErrors("scale_factors/boosted_objects/Top_W_Z_H_fakes.root", "full_fake_2016_eHadH",   "full_fake_HadH_endcap");
    eff_full_fake_bHadHTop= getplot_TGraphAsymmErrors("scale_factors/boosted_objects/Top_W_Z_H_fakes.root", "full_fake_2016_bHadHTop","full_fake_HadH_top_barrel");
    eff_full_fake_eHadHTop= getplot_TGraphAsymmErrors("scale_factors/boosted_objects/Top_W_Z_H_fakes.root", "full_fake_2016_eHadHTop","full_fake_HadH_top_endcap");
    eff_full_fake_bMass   = getplot_TGraphAsymmErrors("scale_factors/boosted_objects/Top_W_Z_H_fakes.root", "full_fake_2016_bMass",   "full_fake_Mass_barrel");
    eff_full_fake_eMass   = getplot_TGraphAsymmErrors("scale_factors/boosted_objects/Top_W_Z_H_fakes.root", "full_fake_2016_eMass",   "full_fake_Mass_endcap");
    eff_full_bMassTop     = getplot_TGraphAsymmErrors("scale_factors/boosted_objects/Top_W_Z_H_fakes.root", "full_real_2016_bMassTop","full_real_MassTop_barrel");
    eff_full_eMassTop     = getplot_TGraphAsymmErrors("scale_factors/boosted_objects/Top_W_Z_H_fakes.root", "full_real_2016_eMassTop","full_real_MassTop_endcap");
    eff_full_POG_Top      = getplot_TH1D("scale_factors/w_top_tag/2017TopTaggingScaleFactors.root",            "PUPPI_wp2_btag/sf_mergedTop_nominal", "full_POG_Top");
    eff_full_POG_Top_up   = getplot_TH1D("scale_factors/w_top_tag/2017TopTaggingScaleFactors.root",            "PUPPI_wp2_btag/sf_mergedTop_up", "full_POG_Top_up");
    eff_full_POG_Top_down = getplot_TH1D("scale_factors/w_top_tag/2017TopTaggingScaleFactors.root",            "PUPPI_wp2_btag/sf_mergedTop_down", "full_POG_Top_down");
    eff_full_POG_W        = getplot_TGraphErrors("scale_factors/w_top_tag/SF_tau21_0p45_ptDependence_200to600GeV.root","Graph",       "full_POG_W");
    eff_fast_V           = getplot_TGraphAsymmErrors("scale_factors/boosted_objects/Top_W_Z_H_fakes.root", "full_fast_2016_HadV",  "fast_V");
    eff_fast_W           = getplot_TGraphAsymmErrors("scale_factors/boosted_objects/Top_W_Z_H_fakes.root", "full_fast_2016_HadW",  "fast_W");
    eff_fast_Z           = getplot_TGraphAsymmErrors("scale_factors/boosted_objects/Top_W_Z_H_fakes.root", "full_fast_2016_HadZ",  "fast_Z");
    eff_fast_H           = getplot_TGraphAsymmErrors("scale_factors/boosted_objects/Top_W_Z_H_fakes.root", "full_fast_2016_HadH",  "fast_H");
    eff_fast_HadTop      = getplot_TGraphAsymmErrors("scale_factors/boosted_objects/Top_W_Z_H_fakes.root", "full_fast_2016_HadTop","fast_HadTop");
    eff_fast_LepTop      = getplot_TGraphAsymmErrors("scale_factors/boosted_objects/Top_W_Z_H_fakes.root", "full_fast_2016_LepTop","fast_LepTop");
  } else {
    eff_full_fake_bLepTop = getplot_TGraphAsymmErrors("scale_factors/boosted_objects/Top_W_Z_H_fakes.root", "full_fake_2016_bLepTop", "full_fake_LepTop_barrel");
    eff_full_fake_eLepTop = getplot_TGraphAsymmErrors("scale_factors/boosted_objects/Top_W_Z_H_fakes.root", "full_fake_2016_eLepTop", "full_fake_LepTop_endcap");
    eff_full_fake_bHadTop = getplot_TGraphAsymmErrors("scale_factors/boosted_objects/Top_W_Z_H_fakes.root", "full_fake_2016_bHadTop", "full_fake_HadTop_barrel");
    eff_full_fake_eHadTop = getplot_TGraphAsymmErrors("scale_factors/boosted_objects/Top_W_Z_H_fakes.root", "full_fake_2016_eHadTop", "full_fake_HadTop_endcap");
    eff_full_fake_bHadV   = getplot_TGraphAsymmErrors("scale_factors/boosted_objects/Top_W_Z_H_fakes.root", "full_fake_2016_bHadV",   "full_fake_HadV_barrel");
    eff_full_fake_eHadV   = getplot_TGraphAsymmErrors("scale_factors/boosted_objects/Top_W_Z_H_fakes.root", "full_fake_2016_eHadV",   "full_fake_HadV_endcap");
    eff_full_fake_bHadH   = getplot_TGraphAsymmErrors("scale_factors/boosted_objects/Top_W_Z_H_fakes.root", "full_fake_2016_bHadH",   "full_fake_HadH_barrel");
    eff_full_fake_eHadH   = getplot_TGraphAsymmErrors("scale_factors/boosted_objects/Top_W_Z_H_fakes.root", "full_fake_2016_eHadH",   "full_fake_HadH_endcap");
    eff_full_fake_bHadHTop= getplot_TGraphAsymmErrors("scale_factors/boosted_objects/Top_W_Z_H_fakes.root", "full_fake_2016_bHadHTop","full_fake_HadH_top_barrel");
    eff_full_fake_eHadHTop= getplot_TGraphAsymmErrors("scale_factors/boosted_objects/Top_W_Z_H_fakes.root", "full_fake_2016_eHadHTop","full_fake_HadH_top_endcap");
    eff_full_fake_bMass   = getplot_TGraphAsymmErrors("scale_factors/boosted_objects/Top_W_Z_H_fakes.root", "full_fake_2016_bMass",   "full_fake_Mass_barrel");
    eff_full_fake_eMass   = getplot_TGraphAsymmErrors("scale_factors/boosted_objects/Top_W_Z_H_fakes.root", "full_fake_2016_eMass",   "full_fake_Mass_endcap");
    eff_full_bMassTop     = getplot_TGraphAsymmErrors("scale_factors/boosted_objects/Top_W_Z_H_fakes.root", "full_real_2016_bMassTop","full_real_MassTop_barrel");
    eff_full_eMassTop     = getplot_TGraphAsymmErrors("scale_factors/boosted_objects/Top_W_Z_H_fakes.root", "full_real_2016_eMassTop","full_real_MassTop_endcap");
    eff_full_POG_Top      = getplot_TH1D("scale_factors/w_top_tag/2017TopTaggingScaleFactors.root",            "PUPPI_wp2_btag/sf_mergedTop_nominal", "full_POG_Top");
    eff_full_POG_Top_up   = getplot_TH1D("scale_factors/w_top_tag/2017TopTaggingScaleFactors.root",            "PUPPI_wp2_btag/sf_mergedTop_up", "full_POG_Top_up");
    eff_full_POG_Top_down = getplot_TH1D("scale_factors/w_top_tag/2017TopTaggingScaleFactors.root",            "PUPPI_wp2_btag/sf_mergedTop_down", "full_POG_Top_down");
    eff_full_POG_W        = getplot_TGraphErrors("scale_factors/w_top_tag/SF_tau21_0p45_ptDependence_200to600GeV.root","Graph",       "full_POG_W");
    
    eff_fast_V           = getplot_TGraphAsymmErrors("scale_factors/boosted_objects/Top_W_Z_H_fakes.root", "full_fast_2016_HadV",  "fast_V");
    eff_fast_W           = getplot_TGraphAsymmErrors("scale_factors/boosted_objects/Top_W_Z_H_fakes.root", "full_fast_2016_HadW",  "fast_W");
    eff_fast_Z           = getplot_TGraphAsymmErrors("scale_factors/boosted_objects/Top_W_Z_H_fakes.root", "full_fast_2016_HadZ",  "fast_Z");
    eff_fast_H           = getplot_TGraphAsymmErrors("scale_factors/boosted_objects/Top_W_Z_H_fakes.root", "full_fast_2016_HadH",  "fast_H");
    eff_fast_HadTop      = getplot_TGraphAsymmErrors("scale_factors/boosted_objects/Top_W_Z_H_fakes.root", "full_fast_2016_HadTop","fast_HadTop");
    eff_fast_LepTop      = getplot_TGraphAsymmErrors("scale_factors/boosted_objects/Top_W_Z_H_fakes.root", "full_fast_2016_LepTop","fast_LepTop");
  }

  //CFs for full run2	
  g_cf_G_run2 = getplot_TGraphAsymmErrors("correction_factors/CF_GJetsrun2.root", "CorrectionFactor", "GJets_corr");
  g_cf_GJet_njet_run2 = getplot_TGraphAsymmErrors("correction_factors/CF_GJetsNJETrun2.root", "CorrectionFactor", "GJet_njet_corr");	
	g_cf_G_MassTag_run2 = getplot_TGraphAsymmErrors("correction_factors/CF_mass-tag_run2.root", "CorrectionFactor", "GJetsMassTag_corr");
	
  if (v.year==2018) {
    g_cf_G = getplot_TGraphAsymmErrors("correction_factors/CF_GJets2018.root", "CorrectionFactor", "GJets_corr");
    g_cf_GJet_njet = getplot_TGraphAsymmErrors("correction_factors/CF_GJetsNJET2018.root", "CorrectionFactor", "GJet_njet_corr");
    g_cf_G_MassTag = getplot_TGraphAsymmErrors("correction_factors/CF_mass-tag_2018.root", "CorrectionFactor", "GJetsMassTag_corr");
    g_cf_Q_1boost = getplot_TGraphAsymmErrors("correction_factors/CFs.root", "qtw_20181BoostMRR2Bin_step0_cf_Q", "QCD_corr_1boostjet"); 
    g_cf_Q_2boost = getplot_TGraphAsymmErrors("correction_factors/CFs.root", "qtw_20182BoostMRR2Bin_step0_cf_Q", "QCD_corr_2boostjet");
    g_cf_W_1boost = getplot_TGraphAsymmErrors("correction_factors/CFs.root", "qtw_20181BoostMRR2Bin_step0_cf_W", "W_corr_1boostjet");
    g_cf_W_2boost = getplot_TGraphAsymmErrors("correction_factors/CFs.root", "qtw_20182BoostMRR2Bin_step0_cf_W", "W_corr_2boostjet");
    g_cf_T_1boost = getplot_TGraphAsymmErrors("correction_factors/CFs.root", "qtw_20181BoostMRR2Bin_step0_cf_T", "TOP_corr_1boostjet");
    g_cf_T_2boost = getplot_TGraphAsymmErrors("correction_factors/CFs.root", "qtw_20182BoostMRR2Bin_step0_cf_T", "TOP_corr_2boostjet");
    g_cf_L_1boost = getplot_TGraphAsymmErrors("correction_factors/CFs.root", "lt_20181BoostMRR21vlBin_step0_cf_W", "L_corr_1boostjet");
    g_cf_L_2boost = getplot_TGraphAsymmErrors("correction_factors/CFs.root", "lt_20181BoostMRR21vlBin_step0_cf_W", "L_corr_2boostjet");
    g_cf_LT_1boost = getplot_TGraphAsymmErrors("correction_factors/CFs.root","lt_20181BoostMRR21vlBin_step0_cf_T", "LT_corr_1boostjet");
    g_cf_LT_2boost = getplot_TGraphAsymmErrors("correction_factors/CFs.root","lt_20181BoostMRR21vlBin_step0_cf_T", "LT_corr_2boostjet");
    g_cf_NonIso_W = getplot_TGraphAsymmErrors("correction_factors/CFs.root", "noniso_2018MRR2Bin_step0_cf_W", "W_corr_nonisolep");
    g_cf_NonIso_T = getplot_TGraphAsymmErrors("correction_factors/CFs.root", "noniso_2018MRR2Bin_step0_cf_T", "T_corr_nonisolep");
    g_cf_Q_njet_1boost  = getplot_TGraphAsymmErrors("correction_factors/NJet_CFs.root", "qtw_20181BoostNJetBins_step1_cf_Q", "QCD_corr_njet_1boostjet");
    g_cf_Q_njet_2boost  = getplot_TGraphAsymmErrors("correction_factors/NJet_CFs.root", "qtw_20182BoostNJetBins_step1_cf_Q", "QCD_corr_njet_2boostjet");
    g_cf_T_njet_1boost  = getplot_TGraphAsymmErrors("correction_factors/NJet_CFs.root", "qtw_20181BoostNJetBins_step1_cf_T", "TOP_corr_njet_1boostjet");
    g_cf_T_njet_2boost  = getplot_TGraphAsymmErrors("correction_factors/NJet_CFs.root", "qtw_20182BoostNJetBins_step1_cf_T", "TOP_corr_njet_2boostjet");
    g_cf_W_njet_1boost  = getplot_TGraphAsymmErrors("correction_factors/NJet_CFs.root", "qtw_20181BoostNJetBins_step1_cf_W", "W_corr_njet_1boostjet");
    g_cf_W_njet_2boost  = getplot_TGraphAsymmErrors("correction_factors/NJet_CFs.root", "qtw_20182BoostNJetBins_step1_cf_W", "W_corr_njet_2boostjet");
    g_cf_L_njet_1boost  = getplot_TGraphAsymmErrors("correction_factors/NJet_CFs.root", "lt_20181BoostNJetBins_step1_cf_W", "L_corr_njet_1boostjet");
    g_cf_L_njet_2boost  = getplot_TGraphAsymmErrors("correction_factors/NJet_CFs.root", "lt_20181BoostNJetBins_step1_cf_W", "L_corr_njet_2boostjet");
    g_cf_LT_njet_1boost = getplot_TGraphAsymmErrors("correction_factors/NJet_CFs.root", "lt_20181BoostNJetBins_step1_cf_T", "LT_corr_njet_1boostjet");
    g_cf_LT_njet_2boost = getplot_TGraphAsymmErrors("correction_factors/NJet_CFs.root", "lt_20181BoostNJetBins_step1_cf_T", "LT_corr_njet_2boostjet");
    g_cf_NonIso_W_njet  = getplot_TGraphAsymmErrors("correction_factors/NJet_CFs.root", "noniso_2018NJetBins_step1_cf_W", "W_corr_njet_nonisolep");
    g_cf_NonIso_T_njet  = getplot_TGraphAsymmErrors("correction_factors/NJet_CFs.root", "noniso_2018NJetBins_step1_cf_T", "T_corr_njet_nonisolep");
    g_cocf_Q_1boost = getplot_TGraphAsymmErrors("correction_factors/CFs.root", "qtw_20181BoostMRR2Bin_step1_cf_Q", "QCD_cor_1boostjet"); 
    g_cocf_Q_2boost = getplot_TGraphAsymmErrors("correction_factors/CFs.root", "qtw_20182BoostMRR2Bin_step1_cf_Q", "QCD_cor_2boostjet");
    g_cocf_W_1boost = getplot_TGraphAsymmErrors("correction_factors/CFs.root", "qtw_20181BoostMRR2Bin_step1_cf_W", "W_cor_1boostjet");
    g_cocf_W_2boost = getplot_TGraphAsymmErrors("correction_factors/CFs.root", "qtw_20182BoostMRR2Bin_step1_cf_W", "W_cor_2boostjet");
    g_cocf_T_1boost = getplot_TGraphAsymmErrors("correction_factors/CFs.root", "qtw_20181BoostMRR2Bin_step1_cf_T", "TOP_cor_1boostjet");
    g_cocf_T_2boost = getplot_TGraphAsymmErrors("correction_factors/CFs.root", "qtw_20182BoostMRR2Bin_step1_cf_T", "TOP_cor_2boostjet");
    g_cocf_NonIso_W = getplot_TGraphAsymmErrors("correction_factors/CFs.root", "noniso_2018MRR2Bin_step1_cf_W", "W_cor_nonisolep");
    g_cocf_NonIso_T = getplot_TGraphAsymmErrors("correction_factors/CFs.root", "noniso_2018MRR2Bin_step1_cf_T", "T_cor_nonisolep");
    g_cocf_Q_njet_1boost  = getplot_TGraphAsymmErrors("correction_factors/NJet_CFs.root", "qtw_20181BoostNJetBins_step0_cf_Q", "QCD_cor_njet_1boostjet");
    g_cocf_Q_njet_2boost  = getplot_TGraphAsymmErrors("correction_factors/NJet_CFs.root", "qtw_20182BoostNJetBins_step0_cf_Q", "QCD_cor_njet_2boostjet");
    g_cocf_T_njet_1boost  = getplot_TGraphAsymmErrors("correction_factors/NJet_CFs.root", "qtw_20181BoostNJetBins_step0_cf_T", "TOP_cor_njet_1boostjet");
    g_cocf_T_njet_2boost  = getplot_TGraphAsymmErrors("correction_factors/NJet_CFs.root", "qtw_20182BoostNJetBins_step0_cf_T", "TOP_cor_njet_2boostjet");
    g_cocf_W_njet_1boost  = getplot_TGraphAsymmErrors("correction_factors/NJet_CFs.root", "qtw_20181BoostNJetBins_step0_cf_W", "W_cor_njet_1boostjet");
    g_cocf_W_njet_2boost  = getplot_TGraphAsymmErrors("correction_factors/NJet_CFs.root", "qtw_20182BoostNJetBins_step0_cf_W", "W_cor_njet_2boostjet");
    g_cocf_NonIso_W_njet  = getplot_TGraphAsymmErrors("correction_factors/NJet_CFs.root", "noniso_2018NJetBins_step0_cf_W", "W_cor_njet_nonisolep");
    g_cocf_NonIso_T_njet  = getplot_TGraphAsymmErrors("correction_factors/NJet_CFs.root", "noniso_2018NJetBins_step0_cf_T", "T_cor_njet_nonisolep");
  } else if (v.year==2017) {
    g_cf_G = getplot_TGraphAsymmErrors("correction_factors/CF_GJets2017.root", "CorrectionFactor", "GJets_corr");
    g_cf_GJet_njet = getplot_TGraphAsymmErrors("correction_factors/CF_GJetsNJET2017.root", "CorrectionFactor", "GJet_njet_corr");
    g_cf_G_MassTag = getplot_TGraphAsymmErrors("correction_factors/CF_mass-tag_2017.root", "CorrectionFactor", "GJetsMassTag_corr");
    g_cf_Q_1boost = getplot_TGraphAsymmErrors("correction_factors/CFs.root", "qtw_20171BoostMRR2Bin_step0_cf_Q", "QCD_corr_1boostjet"); 
    g_cf_Q_2boost = getplot_TGraphAsymmErrors("correction_factors/CFs.root", "qtw_20172BoostMRR2Bin_step0_cf_Q", "QCD_corr_2boostjet");
    g_cf_W_1boost = getplot_TGraphAsymmErrors("correction_factors/CFs.root", "qtw_20171BoostMRR2Bin_step0_cf_W", "W_corr_1boostjet");
    g_cf_W_2boost = getplot_TGraphAsymmErrors("correction_factors/CFs.root", "qtw_20172BoostMRR2Bin_step0_cf_W", "W_corr_2boostjet");
    g_cf_T_1boost = getplot_TGraphAsymmErrors("correction_factors/CFs.root", "qtw_20171BoostMRR2Bin_step0_cf_T", "TOP_corr_1boostjet");
    g_cf_T_2boost = getplot_TGraphAsymmErrors("correction_factors/CFs.root", "qtw_20172BoostMRR2Bin_step0_cf_T", "TOP_corr_2boostjet");
    g_cf_L_1boost = getplot_TGraphAsymmErrors("correction_factors/CFs.root", "lt_20171BoostMRR21vlBin_step0_cf_W", "L_corr_1boostjet");
    g_cf_L_2boost = getplot_TGraphAsymmErrors("correction_factors/CFs.root", "lt_20171BoostMRR21vlBin_step0_cf_W", "L_corr_2boostjet");
    g_cf_LT_1boost = getplot_TGraphAsymmErrors("correction_factors/CFs.root","lt_20171BoostMRR21vlBin_step0_cf_T", "LT_corr_1boostjet");
    g_cf_LT_2boost = getplot_TGraphAsymmErrors("correction_factors/CFs.root","lt_20171BoostMRR21vlBin_step0_cf_T", "LT_corr_2boostjet");
    g_cf_NonIso_W = getplot_TGraphAsymmErrors("correction_factors/CFs.root", "noniso_2017MRR2Bin_step0_cf_W", "W_corr_nonisolep");
    g_cf_NonIso_T = getplot_TGraphAsymmErrors("correction_factors/CFs.root", "noniso_2017MRR2Bin_step0_cf_T", "T_corr_nonisolep");
    g_cf_Q_njet_1boost  = getplot_TGraphAsymmErrors("correction_factors/NJet_CFs.root", "qtw_20171BoostNJetBins_step1_cf_Q", "QCD_corr_njet_1boostjet");
    g_cf_Q_njet_2boost  = getplot_TGraphAsymmErrors("correction_factors/NJet_CFs.root", "qtw_20172BoostNJetBins_step1_cf_Q", "QCD_corr_njet_2boostjet");
    g_cf_T_njet_1boost  = getplot_TGraphAsymmErrors("correction_factors/NJet_CFs.root", "qtw_20171BoostNJetBins_step1_cf_T", "TOP_corr_njet_1boostjet");
    g_cf_T_njet_2boost  = getplot_TGraphAsymmErrors("correction_factors/NJet_CFs.root", "qtw_20172BoostNJetBins_step1_cf_T", "TOP_corr_njet_2boostjet");
    g_cf_W_njet_1boost  = getplot_TGraphAsymmErrors("correction_factors/NJet_CFs.root", "qtw_20171BoostNJetBins_step1_cf_W", "W_corr_njet_1boostjet");
    g_cf_W_njet_2boost  = getplot_TGraphAsymmErrors("correction_factors/NJet_CFs.root", "qtw_20172BoostNJetBins_step1_cf_W", "W_corr_njet_2boostjet");
    g_cf_L_njet_1boost  = getplot_TGraphAsymmErrors("correction_factors/NJet_CFs.root", "lt_20171BoostNJetBins_step1_cf_W", "L_corr_njet_1boostjet");
    g_cf_L_njet_2boost  = getplot_TGraphAsymmErrors("correction_factors/NJet_CFs.root", "lt_20171BoostNJetBins_step1_cf_W", "L_corr_njet_2boostjet");
    g_cf_LT_njet_1boost = getplot_TGraphAsymmErrors("correction_factors/NJet_CFs.root", "lt_20171BoostNJetBins_step1_cf_T", "LT_corr_njet_1boostjet");
    g_cf_LT_njet_2boost = getplot_TGraphAsymmErrors("correction_factors/NJet_CFs.root", "lt_20171BoostNJetBins_step1_cf_T", "LT_corr_njet_2boostjet");
    g_cf_NonIso_W_njet  = getplot_TGraphAsymmErrors("correction_factors/NJet_CFs.root", "noniso_2017NJetBins_step1_cf_W", "W_corr_njet_nonisolep");
    g_cf_NonIso_T_njet  = getplot_TGraphAsymmErrors("correction_factors/NJet_CFs.root", "noniso_2017NJetBins_step1_cf_T", "T_corr_njet_nonisolep");
    g_cocf_Q_1boost = getplot_TGraphAsymmErrors("correction_factors/CFs.root", "qtw_20171BoostMRR2Bin_step1_cf_Q", "QCD_cor_1boostjet"); 
    g_cocf_Q_2boost = getplot_TGraphAsymmErrors("correction_factors/CFs.root", "qtw_20172BoostMRR2Bin_step1_cf_Q", "QCD_cor_2boostjet");
    g_cocf_W_1boost = getplot_TGraphAsymmErrors("correction_factors/CFs.root", "qtw_20171BoostMRR2Bin_step1_cf_W", "W_cor_1boostjet");
    g_cocf_W_2boost = getplot_TGraphAsymmErrors("correction_factors/CFs.root", "qtw_20172BoostMRR2Bin_step1_cf_W", "W_cor_2boostjet");
    g_cocf_T_1boost = getplot_TGraphAsymmErrors("correction_factors/CFs.root", "qtw_20171BoostMRR2Bin_step1_cf_T", "TOP_cor_1boostjet");
    g_cocf_T_2boost = getplot_TGraphAsymmErrors("correction_factors/CFs.root", "qtw_20172BoostMRR2Bin_step1_cf_T", "TOP_cor_2boostjet");
    g_cocf_NonIso_W = getplot_TGraphAsymmErrors("correction_factors/CFs.root", "noniso_2017MRR2Bin_step1_cf_W", "W_cor_njet_nonisolep");
    g_cocf_NonIso_T = getplot_TGraphAsymmErrors("correction_factors/CFs.root", "noniso_2017MRR2Bin_step1_cf_T", "T_cor_njet_nonisolep");
    g_cocf_Q_njet_1boost  = getplot_TGraphAsymmErrors("correction_factors/NJet_CFs.root", "qtw_20171BoostNJetBins_step0_cf_Q", "QCD_cor_njet_1boostjet");
    g_cocf_Q_njet_2boost  = getplot_TGraphAsymmErrors("correction_factors/NJet_CFs.root", "qtw_20172BoostNJetBins_step0_cf_Q", "QCD_cor_njet_2boostjet");
    g_cocf_T_njet_1boost  = getplot_TGraphAsymmErrors("correction_factors/NJet_CFs.root", "qtw_20171BoostNJetBins_step0_cf_T", "TOP_cor_njet_1boostjet");
    g_cocf_T_njet_2boost  = getplot_TGraphAsymmErrors("correction_factors/NJet_CFs.root", "qtw_20172BoostNJetBins_step0_cf_T", "TOP_cor_njet_2boostjet");
    g_cocf_W_njet_1boost  = getplot_TGraphAsymmErrors("correction_factors/NJet_CFs.root", "qtw_20171BoostNJetBins_step0_cf_W", "W_cor_njet_1boostjet");
    g_cocf_W_njet_2boost  = getplot_TGraphAsymmErrors("correction_factors/NJet_CFs.root", "qtw_20172BoostNJetBins_step0_cf_W", "W_cor_njet_2boostjet");
    g_cocf_NonIso_W_njet  = getplot_TGraphAsymmErrors("correction_factors/NJet_CFs.root", "noniso_2017NJetBins_step0_cf_W", "W_cor_njet_nonisolep");
    g_cocf_NonIso_T_njet  = getplot_TGraphAsymmErrors("correction_factors/NJet_CFs.root", "noniso_2017NJetBins_step0_cf_T", "T_cor_njet_nonisolep");
  } else {
    g_cf_G = getplot_TGraphAsymmErrors("correction_factors/CF_GJets2016.root", "CorrectionFactor", "GJets_corr");
    g_cf_GJet_njet = getplot_TGraphAsymmErrors("correction_factors/CF_GJetsNJET2016.root", "CorrectionFactor", "GJet_njet_corr");
    g_cf_G_MassTag = getplot_TGraphAsymmErrors("correction_factors/CF_mass-tag_2016.root", "CorrectionFactor", "GJetsMassTag_corr");
    g_cf_Q_1boost = getplot_TGraphAsymmErrors("correction_factors/CFs.root", "qtw_20161BoostMRR2Bin_step0_cf_Q", "QCD_corr_1boostjet"); 
    g_cf_Q_2boost = getplot_TGraphAsymmErrors("correction_factors/CFs.root", "qtw_20162BoostMRR2Bin_step0_cf_Q", "QCD_corr_2boostjet");
    g_cf_W_1boost = getplot_TGraphAsymmErrors("correction_factors/CFs.root", "qtw_20161BoostMRR2Bin_step0_cf_W", "W_corr_1boostjet");
    g_cf_W_2boost = getplot_TGraphAsymmErrors("correction_factors/CFs.root", "qtw_20162BoostMRR2Bin_step0_cf_W", "W_corr_2boostjet");
    g_cf_T_1boost = getplot_TGraphAsymmErrors("correction_factors/CFs.root", "qtw_20161BoostMRR2Bin_step0_cf_T", "TOP_corr_1boostjet");
    g_cf_T_2boost = getplot_TGraphAsymmErrors("correction_factors/CFs.root", "qtw_20162BoostMRR2Bin_step0_cf_T", "TOP_corr_2boostjet");
    g_cf_L_1boost = getplot_TGraphAsymmErrors("correction_factors/CFs.root", "lt_20161BoostMRR21vlBin_step0_cf_W", "L_corr_1boostjet");
    g_cf_L_2boost = getplot_TGraphAsymmErrors("correction_factors/CFs.root", "lt_20161BoostMRR21vlBin_step0_cf_W", "L_corr_2boostjet");
    g_cf_LT_1boost = getplot_TGraphAsymmErrors("correction_factors/CFs.root","lt_20161BoostMRR21vlBin_step0_cf_T", "LT_corr_1boostjet");
    g_cf_LT_2boost = getplot_TGraphAsymmErrors("correction_factors/CFs.root","lt_20161BoostMRR21vlBin_step0_cf_T", "LT_corr_2boostjet");
    g_cf_NonIso_W = getplot_TGraphAsymmErrors("correction_factors/CFs.root", "noniso_2016MRR2Bin_step0_cf_W", "W_corr_nonisolep");
    g_cf_NonIso_T = getplot_TGraphAsymmErrors("correction_factors/CFs.root", "noniso_2016MRR2Bin_step0_cf_T", "T_corr_nonisolep");
    g_cf_Q_njet_1boost  = getplot_TGraphAsymmErrors("correction_factors/NJet_CFs.root", "qtw_20161BoostNJetBins_step1_cf_Q", "QCD_corr_njet_1boostjet");
    g_cf_Q_njet_2boost  = getplot_TGraphAsymmErrors("correction_factors/NJet_CFs.root", "qtw_20162BoostNJetBins_step1_cf_Q", "QCD_corr_njet_2boostjet");
    g_cf_T_njet_1boost  = getplot_TGraphAsymmErrors("correction_factors/NJet_CFs.root", "qtw_20161BoostNJetBins_step1_cf_T", "TOP_corr_njet_1boostjet");
    g_cf_T_njet_2boost  = getplot_TGraphAsymmErrors("correction_factors/NJet_CFs.root", "qtw_20162BoostNJetBins_step1_cf_T", "TOP_corr_njet_2boostjet");
    g_cf_W_njet_1boost  = getplot_TGraphAsymmErrors("correction_factors/NJet_CFs.root", "qtw_20161BoostNJetBins_step1_cf_W", "W_corr_njet_1boostjet");
    g_cf_W_njet_2boost  = getplot_TGraphAsymmErrors("correction_factors/NJet_CFs.root", "qtw_20162BoostNJetBins_step1_cf_W", "W_corr_njet_2boostjet");
    g_cf_L_njet_1boost  = getplot_TGraphAsymmErrors("correction_factors/NJet_CFs.root", "lt_20161BoostNJetBins_step1_cf_W", "L_corr_njet_1boostjet");
    g_cf_L_njet_2boost  = getplot_TGraphAsymmErrors("correction_factors/NJet_CFs.root", "lt_20161BoostNJetBins_step1_cf_W", "L_corr_njet_2boostjet");
    g_cf_LT_njet_1boost = getplot_TGraphAsymmErrors("correction_factors/NJet_CFs.root", "lt_20161BoostNJetBins_step1_cf_T", "LT_corr_njet_1boostjet");
    g_cf_LT_njet_2boost = getplot_TGraphAsymmErrors("correction_factors/NJet_CFs.root", "lt_20161BoostNJetBins_step1_cf_T", "LT_corr_njet_2boostjet");
    g_cf_NonIso_W_njet  = getplot_TGraphAsymmErrors("correction_factors/NJet_CFs.root", "noniso_2016NJetBins_step1_cf_W", "W_corr_njet_nonisolep");
    g_cf_NonIso_T_njet  = getplot_TGraphAsymmErrors("correction_factors/NJet_CFs.root", "noniso_2016NJetBins_step1_cf_T", "T_corr_njet_nonisolep");
    g_cocf_Q_1boost = getplot_TGraphAsymmErrors("correction_factors/CFs.root", "qtw_20161BoostMRR2Bin_step1_cf_Q", "QCD_cor_1boostjet"); 
    g_cocf_Q_2boost = getplot_TGraphAsymmErrors("correction_factors/CFs.root", "qtw_20162BoostMRR2Bin_step1_cf_Q", "QCD_cor_2boostjet");
    g_cocf_W_1boost = getplot_TGraphAsymmErrors("correction_factors/CFs.root", "qtw_20161BoostMRR2Bin_step1_cf_W", "W_cor_1boostjet");
    g_cocf_W_2boost = getplot_TGraphAsymmErrors("correction_factors/CFs.root", "qtw_20162BoostMRR2Bin_step1_cf_W", "W_cor_2boostjet");
    g_cocf_T_1boost = getplot_TGraphAsymmErrors("correction_factors/CFs.root", "qtw_20161BoostMRR2Bin_step1_cf_T", "TOP_cor_1boostjet");
    g_cocf_T_2boost = getplot_TGraphAsymmErrors("correction_factors/CFs.root", "qtw_20162BoostMRR2Bin_step1_cf_T", "TOP_cor_2boostjet");
    g_cocf_NonIso_W = getplot_TGraphAsymmErrors("correction_factors/CFs.root", "noniso_2016MRR2Bin_step1_cf_W", "W_cor_njet_nonisolep");
    g_cocf_NonIso_T = getplot_TGraphAsymmErrors("correction_factors/CFs.root", "noniso_2016MRR2Bin_step1_cf_T", "T_cor_njet_nonisolep");
    g_cocf_Q_njet_1boost  = getplot_TGraphAsymmErrors("correction_factors/NJet_CFs.root", "qtw_20161BoostNJetBins_step0_cf_Q", "QCD_cor_njet_1boostjet");
    g_cocf_Q_njet_2boost  = getplot_TGraphAsymmErrors("correction_factors/NJet_CFs.root", "qtw_20162BoostNJetBins_step0_cf_Q", "QCD_cor_njet_2boostjet");
    g_cocf_T_njet_1boost  = getplot_TGraphAsymmErrors("correction_factors/NJet_CFs.root", "qtw_20161BoostNJetBins_step0_cf_T", "TOP_cor_njet_1boostjet");
    g_cocf_T_njet_2boost  = getplot_TGraphAsymmErrors("correction_factors/NJet_CFs.root", "qtw_20162BoostNJetBins_step0_cf_T", "TOP_cor_njet_2boostjet");
    g_cocf_W_njet_1boost  = getplot_TGraphAsymmErrors("correction_factors/NJet_CFs.root", "qtw_20161BoostNJetBins_step0_cf_W", "W_cor_njet_1boostjet");
    g_cocf_W_njet_2boost  = getplot_TGraphAsymmErrors("correction_factors/NJet_CFs.root", "qtw_20162BoostNJetBins_step0_cf_W", "W_cor_njet_2boostjet");
    g_cocf_NonIso_W_njet  = getplot_TGraphAsymmErrors("correction_factors/NJet_CFs.root", "noniso_2016NJetBins_step0_cf_W", "W_cor_njet_nonisolep");
    g_cocf_NonIso_T_njet  = getplot_TGraphAsymmErrors("correction_factors/NJet_CFs.root", "noniso_2016NJetBins_step0_cf_T", "T_cor_njet_nonisolep");
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

double ScaleFactors::calc_boost_tagging_sf(const double& nSigmaBoostTagSF, const double& nSigmaBoostTagFastSimSF,
                                           const double& nSigmaBoostMisTagSF) {
  // TODO: Get POG scale factors for tags - derive the missing ones (leptop, higgs)
  //       Calculate and apply fastsim scale factors
  double w = 1;
  double eff, err_up, err_down;
  while (v.FatJet.Loop()) {
    bool isB = std::abs(v.FatJet().eta)<1.5;
    if (v.FatJet.LepJet.pass[v.FatJet.i]) {
      //geteff_AE(isB ? eff_full_fake_bLepTop : eff_full_fake_eLepTop, v.FatJet().pt, eff, err_up, err_down);
      //w *= get_syst_weight_(eff, eff+err_up, eff-err_down, nSigmaBoostMisTagSF);
			w *= 1;
    // Top - Leptonic
		} else if (v.FatJet.LepTop.pass[v.FatJet.i]) {
      geteff_AE(isB ? eff_full_fake_bLepTop : eff_full_fake_eLepTop, v.FatJet().pt, eff, err_up, err_down);
      w *= get_syst_weight_(eff, eff+err_up, eff-err_down, nSigmaBoostMisTagSF);
      if (v.isFastSim) {
        geteff_AE(eff_fast_LepTop, v.FatJet().pt, eff, err_up, err_down);
        w *= get_syst_weight_(eff, eff+err_up, eff-err_down, nSigmaBoostTagFastSimSF);
      }
    // H - Hadronic
    } else if (v.FatJet.HadH.pass[v.FatJet.i]) {
      // Fake
      if (!v.FatJet().matchGenHadH) {
        geteff_AE(isB ? eff_full_fake_bHadH : eff_full_fake_eHadH, v.FatJet().pt, eff, err_up, err_down);
        w *= get_syst_weight_(eff, eff+err_up, eff-err_down, nSigmaBoostMisTagSF);
      } else {
				//LP WP now // Will test MP vs LP for Hiigs tagging
        if (v.year==2016) {
				if(v.isAPV)   {
            if      (v.FatJet().pt>=450&&v.FatJet().pt<500) w *= get_syst_weight_(1.032, 1.035+0.096, 1.032-0.090, nSigmaBoostTagSF);
            else if (v.FatJet().pt>=500&&v.FatJet().pt<600) w *= get_syst_weight_(1.062, 1.062+0.092, 1.062-0.082, nSigmaBoostTagSF);
            else if (v.FatJet().pt>=600)                    w *= get_syst_weight_(1.002, 1.002+0.106, 1.002-0.101, nSigmaBoostTagSF);
				} else {                                                                                           
            if      (v.FatJet().pt>=450&&v.FatJet().pt<500) w *= get_syst_weight_(1.031, 1.031+0.058, 1.031-0.050, nSigmaBoostTagSF);
            else if (v.FatJet().pt>=500&&v.FatJet().pt<600) w *= get_syst_weight_(1.089, 1.089+0.076, 1.089-0.068, nSigmaBoostTagSF);
            else if (v.FatJet().pt>=600)                    w *= get_syst_weight_(1.057, 1.057+0.077, 1.057-0.056, nSigmaBoostTagSF);
				}                                                                                                  
        } else if (v.year==2017) {                                                                         
            if      (v.FatJet().pt>=450&&v.FatJet().pt<500) w *= get_syst_weight_(0.966, 0.966+0.055, 0.966-0.057, nSigmaBoostTagSF);
            else if (v.FatJet().pt>=500&&v.FatJet().pt<600) w *= get_syst_weight_(1.021, 1.021+0.053, 1.021-0.052, nSigmaBoostTagSF);
            else if (v.FatJet().pt>=600)                    w *= get_syst_weight_(0.979, 0.979+0.035, 0.979-0.038, nSigmaBoostTagSF);
        } else if (v.year==2018) {                                                                         
            if      (v.FatJet().pt>=450&&v.FatJet().pt<500) w *= get_syst_weight_(0.921, 0.921+0.071, 0.921-0.077, nSigmaBoostTagSF);
            else if (v.FatJet().pt>=500&&v.FatJet().pt<600) w *= get_syst_weight_(1.006, 1.006+0.024, 1.006-0.026, nSigmaBoostTagSF);
            else if (v.FatJet().pt>=600)                    w *= get_syst_weight_(1.001, 1.001+0.035, 1.001-0.037, nSigmaBoostTagSF);
        }
      	if (v.isFastSim) {
        	geteff_AE(eff_fast_H, v.FatJet().pt, eff, err_up, err_down);
        	w *= get_syst_weight_(eff, eff+err_up, eff-err_down, nSigmaBoostTagFastSimSF);
      	}
      }
    // Top - Hadronic
    } else if (v.FatJet.HadTop.pass[v.FatJet.i]) {
      if (v.FatJet().matchGenHadTop) {
        // We use WP2 (1.0% MR)
        if (v.year==2016) {
					if(v.isAPV) {
            if (v.FatJet().pt>=300&&v.FatJet().pt<400) w *= get_syst_weight_(1.25, 1.25+0.15, 1.25-0.14, nSigmaBoostTagSF);
            if (v.FatJet().pt>=400&&v.FatJet().pt<480) w *= get_syst_weight_(1.14, 1.14+0.15, 1.14-0.11, nSigmaBoostTagSF);
            if (v.FatJet().pt>=480&&v.FatJet().pt<600) w *= get_syst_weight_(1.23, 1.23+0.18, 1.23-0.17, nSigmaBoostTagSF);
            if (v.FatJet().pt>=600&&v.FatJet().pt<1200)w *= get_syst_weight_(1.38, 1.38+0.32, 1.38-0.36, nSigmaBoostTagSF);
					} else {
            if (v.FatJet().pt>=300&&v.FatJet().pt<400) w *= get_syst_weight_(1.03, 1.03+0.08, 1.03-0.09, nSigmaBoostTagSF);
            if (v.FatJet().pt>=400&&v.FatJet().pt<480) w *= get_syst_weight_(0.99, 0.99+0.05, 0.99-0.05, nSigmaBoostTagSF);
            if (v.FatJet().pt>=480&&v.FatJet().pt<600) w *= get_syst_weight_(1.13, 1.13+0.18, 1.13-0.14, nSigmaBoostTagSF);
            if (v.FatJet().pt>=600&&v.FatJet().pt<1200)w *= get_syst_weight_(1.30, 1.30+0.31, 1.30-0.28, nSigmaBoostTagSF);
					}
        } else if (v.year==2017) {
          if (v.FatJet().pt>=300&&v.FatJet().pt<400) w *= get_syst_weight_(1.27, 1.27+0.13, 1.27-0.13, nSigmaBoostTagSF);
          if (v.FatJet().pt>=400&&v.FatJet().pt<480) w *= get_syst_weight_(1.02, 1.02+0.04, 1.02-0.04, nSigmaBoostTagSF);
          if (v.FatJet().pt>=480&&v.FatJet().pt<600) w *= get_syst_weight_(1.06, 1.06+0.12, 1.06-0.04, nSigmaBoostTagSF);
          if (v.FatJet().pt>=600&&v.FatJet().pt<1200)w *= get_syst_weight_(1.00, 1.00+0.06, 1.00-0.06, nSigmaBoostTagSF);
        } else if (v.year==2018) {
          if (v.FatJet().pt>=300&&v.FatJet().pt<400) w *= get_syst_weight_(1.12, 1.12+0.11, 1.12-0.09, nSigmaBoostTagSF);
          if (v.FatJet().pt>=400&&v.FatJet().pt<480) w *= get_syst_weight_(0.99, 0.99+0.04, 0.99-0.03, nSigmaBoostTagSF);
          if (v.FatJet().pt>=480&&v.FatJet().pt<600) w *= get_syst_weight_(0.99, 0.99+0.03, 0.99-0.03, nSigmaBoostTagSF);
          if (v.FatJet().pt>=600&&v.FatJet().pt<1200)w *= get_syst_weight_(0.98, 0.98+0.05, 0.98-0.06, nSigmaBoostTagSF);
        }
      	if (v.isFastSim) {
        	geteff_AE(eff_fast_HadTop, v.FatJet().pt, eff, err_up, err_down);
        	w *= get_syst_weight_(eff, eff+err_up, eff-err_down, nSigmaBoostTagFastSimSF);
      	}
      } else {
        // Fake
        geteff_AE(isB ? eff_full_fake_bHadTop : eff_full_fake_eHadTop, v.FatJet().pt, eff, err_up, err_down);
        w *= get_syst_weight_(eff, eff+err_up, eff-err_down, nSigmaBoostMisTagSF);
      }
    // W/Z - Hadronic
    } else if (v.FatJet.HadV.pass[v.FatJet.i]) {
      if (v.FatJet().matchGenHadW||v.FatJet().matchGenHadZ) {
        // We use WP2 (1.0% MR)
        if (v.year==2016) {
					if(v.isAPV) {
          	if      (v.FatJet().pt>=200&&v.FatJet().pt<300) w *= get_syst_weight_(1.01, 1.01+0.07, 1.01-0.07, nSigmaBoostTagSF);
          	else if (v.FatJet().pt>=300&&v.FatJet().pt<400) w *= get_syst_weight_(1.00, 1.00+0.10, 1.00-0.09, nSigmaBoostTagSF);
          	else if (v.FatJet().pt>=400&&v.FatJet().pt<800) w *= get_syst_weight_(1.05, 1.05+0.10, 1.05-0.10, nSigmaBoostTagSF);
					} else {
          	if      (v.FatJet().pt>=200&&v.FatJet().pt<300) w *= get_syst_weight_(1.13, 1.13+0.06, 1.13-0.06, nSigmaBoostTagSF);
          	else if (v.FatJet().pt>=300&&v.FatJet().pt<400) w *= get_syst_weight_(1.08, 1.08+0.05, 1.08-0.05, nSigmaBoostTagSF);
          	else if (v.FatJet().pt>=400&&v.FatJet().pt<800) w *= get_syst_weight_(1.16, 1.16+0.08, 1.16-0.14, nSigmaBoostTagSF);
					}
        } else if (v.year==2017) {
          if      (v.FatJet().pt>=200&&v.FatJet().pt<300) w *= get_syst_weight_(0.96, 0.96+0.05, 0.96-0.04, nSigmaBoostTagSF);
          else if (v.FatJet().pt>=300&&v.FatJet().pt<400) w *= get_syst_weight_(0.94, 0.94+0.08, 0.94-0.05, nSigmaBoostTagSF);
          else if (v.FatJet().pt>=400&&v.FatJet().pt<800) w *= get_syst_weight_(0.79, 0.79+0.12, 0.79-0.10, nSigmaBoostTagSF);
        } else if (v.year==2018) {
          if      (v.FatJet().pt>=200&&v.FatJet().pt<300) w *= get_syst_weight_(1.02, 1.02+0.02, 1.02-0.03, nSigmaBoostTagSF);
          else if (v.FatJet().pt>=300&&v.FatJet().pt<400) w *= get_syst_weight_(0.97, 0.97+0.06, 0.97-0.06, nSigmaBoostTagSF);
          else if (v.FatJet().pt>=400&&v.FatJet().pt<800) w *= get_syst_weight_(1.03, 1.03+0.06, 1.03-0.16, nSigmaBoostTagSF);
        }
      	if (v.isFastSim) {
      		geteff_AE(eff_fast_V, v.FatJet().pt, eff, err_up, err_down);
      		w *= get_syst_weight_(eff, eff+err_up, eff-err_down, nSigmaBoostTagFastSimSF);
      	}
      }
      // Fake
      else if (!(v.FatJet().matchGenHadW||v.FatJet().matchGenHadZ)) {
        geteff_AE(isB ? eff_full_fake_bHadV : eff_full_fake_eHadV, v.FatJet().pt, eff, err_up, err_down);
        w *= get_syst_weight_(eff, eff+err_up, eff-err_down, nSigmaBoostMisTagSF);
      }
    }
  }
  return w;
}

double ScaleFactors::calc_mass_tagging_sf() {
	//const double& temp = 0;
  double w = 1;
  double eff, err_up, err_down;
  while (v.FatJet.Loop()) {
    bool isB = std::abs(v.FatJet().eta)<1.5;
    // Masstag
    if (v.FatJet.JetAK8Mass.pass[v.FatJet.i]) {
      if (v.FatJet().matchGenLepTop||v.FatJet().matchGenHadTop||
          v.FatJet().matchGenHadW||v.FatJet().matchGenHadZ||v.FatJet().matchGenHadH) {
        // Real massive objects
        //geteff_AE(isB ? eff_full_bMassTop : eff_full_eMassTop, v.FatJet().pt, eff, err_up, err_down);
				eff = 1;
    		w *= eff;
      } else {
        // Fakes
        geteff_AE(isB ? eff_full_fake_bMass : eff_full_fake_eMass, v.FatJet().pt, eff, err_up, err_down);
    		w *= eff;
      }
    }
  }
  return w;
}

double ScaleFactors::calc_QTW_CR_cf(int flag=0) {
  double w = 1.0;
  double eff, err_up, err_down;
	int nObj = v.FatJet.JetAK8Mass.n;
  if (v.isQCD){
		if(flag&0) { eff = 1; err_up = 0; err_down = 0;}
		if(flag&1) { geteff_AE(nObj ==1 ? g_cf_Q_1boost : g_cf_Q_2boost, v.MR*v.R2, eff, err_up, err_down); w *= eff;}
		if(flag&2) { geteff_AE(nObj ==1 ? g_cf_Q_njet_1boost : g_cf_Q_njet_2boost, v.Jet.Jet.n, eff, err_up, err_down); w *= eff;}
  } else if (v.isTop){
		if(flag&0) { eff = 1; err_up = 0; err_down = 0;}
		if(flag&1) { geteff_AE(nObj ==1 ? g_cf_T_1boost : g_cf_T_2boost, v.MR*v.R2, eff, err_up, err_down); w *= eff;}
		if(flag&2) { geteff_AE(nObj ==1 ? g_cf_T_njet_1boost : g_cf_T_njet_2boost, v.Jet.Jet.n, eff, err_up, err_down); w *= eff;}
  } else if (v.isWJets){
		if(flag&0) { eff = 1; err_up = 0; err_down = 0;}
		if(flag&1) { geteff_AE(nObj ==1 ? g_cf_W_1boost : g_cf_W_2boost, v.MR*v.R2, eff, err_up, err_down); w *= eff;}
		if(flag&2) { geteff_AE(nObj ==1 ? g_cf_W_njet_1boost : g_cf_W_njet_2boost, v.Jet.Jet.n, eff, err_up, err_down); w *= eff;}
  }
  return w;
}

double ScaleFactors::calc_QTW_CoCR_cf(int flag=0) {
  double w = 1.0;
  double eff, err_up, err_down;
	int nObj = v.FatJet.JetAK8Mass.n;
  if (v.isQCD){
		if(flag&0) { eff = 1; err_up = 0; err_down = 0;}
		if(flag&1) { geteff_AE(nObj ==1 ? g_cocf_Q_njet_1boost : g_cocf_Q_njet_2boost, v.Jet.Jet.n, eff, err_up, err_down); w *= eff;}
		if(flag&2) { geteff_AE(nObj ==1 ? g_cocf_Q_1boost : g_cocf_Q_2boost, v.MR*v.R2, eff, err_up, err_down); w *= eff;}
  } else if (v.isTop){
		if(flag&0) { eff = 1; err_up = 0; err_down = 0;}
		if(flag&1) { geteff_AE(nObj ==1 ? g_cocf_T_njet_1boost : g_cocf_T_njet_2boost, v.Jet.Jet.n, eff, err_up, err_down); w *= eff;}
		if(flag&2) { geteff_AE(nObj ==1 ? g_cocf_T_1boost : g_cocf_T_2boost, v.MR*v.R2, eff, err_up, err_down); w *= eff;}
  } else if (v.isWJets){
		if(flag&0) { eff = 1; err_up = 0; err_down = 0;}
		if(flag&1) { geteff_AE(nObj ==1 ? g_cocf_W_njet_1boost : g_cocf_W_njet_2boost, v.Jet.Jet.n, eff, err_up, err_down); w *= eff;}
		if(flag&2) { geteff_AE(nObj ==1 ? g_cocf_W_1boost : g_cocf_W_2boost, v.MR*v.R2, eff, err_up, err_down); w *= eff;}
  }
  return w;
}

std::pair<double, double> ScaleFactors::calc_Z_CR_cf(int flag=0) {
  double weight_L = 1.0, weight_G = 1.0;
  double eff, err_up, err_down;
	int nObj = v.FatJet.JetAK8Mass.n;
  if (v.isTop){
		if(flag&0) { eff = 1; err_up = 0; err_down = 0;}
		if(flag&1) { geteff_AE(nObj ==1 ? g_cf_LT_1boost : g_cf_LT_2boost, v.MR*v.R2_1vl, eff, err_up, err_down); weight_L *= eff;}
		if(flag&2) { geteff_AE(nObj ==1 ? g_cf_LT_njet_1boost : g_cf_LT_njet_2boost, v.Jet.Jet.n, eff, err_up, err_down); weight_L *= eff;}
  } else if (v.isWJets){
		if(flag&0) { eff = 1; err_up = 0; err_down = 0;}
		if(flag&1) { geteff_AE(nObj ==1 ? g_cf_L_1boost : g_cf_L_2boost, v.MR*v.R2_1vl, eff, err_up, err_down); weight_L *= eff;}
		if(flag&2) { geteff_AE(nObj ==1 ? g_cf_L_njet_1boost : g_cf_L_njet_2boost, v.Jet.Jet.n, eff, err_up, err_down); weight_L *= eff;}
  } else if (v.isGJets){
		if(flag&0) { eff = 1; err_up = 0; err_down = 0;}
    if(flag&1) { geteff_AE(g_cf_G, v.MR_pho*v.R2_pho, eff, err_up, err_down); weight_G *= eff;}
    if(flag&2) { geteff_AE(g_cf_GJet_njet, v.Jet.Jet.n, eff, err_up, err_down); weight_G *= eff;}
		if(flag&4) { geteff_AE(g_cf_G_MassTag, nObj, eff, err_up, err_down); weight_G *= eff;}
  }
  return std::make_pair(weight_G, weight_L);
}

double ScaleFactors::calc_nonIso_CR_cf(int flag=0) {
  double w = 1.0;
  double eff, err_up, err_down;
	int nObj = v.FatJet.JetAK8Mass.n;
  if (v.isQCD){
		if(flag&0) { geteff_AE(nObj ==1 ? g_cf_Q_1boost : g_cf_Q_2boost, v.MR*v.R2, eff, err_up, err_down); w *= eff;}
		if(flag&0) { geteff_AE(nObj ==1 ? g_cf_Q_njet_1boost : g_cf_Q_njet_2boost, v.Jet.Jet.n, eff, err_up, err_down); w *= eff;}
  } else if (v.isTop){
		if(flag&0) { eff = 1; err_up = 0; err_down = 0;}
    if(flag&1) { geteff_AE(g_cf_NonIso_T, v.MR*v.R2, eff, err_up, err_down); w *= eff;}
    if(flag&2) { geteff_AE(g_cf_NonIso_T_njet, v.Jet.Jet.n, eff, err_up, err_down); w *= eff;}
  } else if (v.isWJets){
		if(flag&0) { eff = 1; err_up = 0; err_down = 0;}
    if(flag&1) { geteff_AE(g_cf_NonIso_W, v.MR*v.R2, eff, err_up, err_down); w *= eff;}
    if(flag&2) { geteff_AE(g_cf_NonIso_W_njet, v.Jet.Jet.n, eff, err_up, err_down); w *= eff;}
  }
  return w;
}

double ScaleFactors::calc_nonIso_CoCR_cf(int flag=0) {
  double w = 1.0;
  double eff, err_up, err_down;
	int nObj = v.FatJet.JetAK8Mass.n;
  if (v.isQCD){
		if(flag&0) { eff = 1; err_up = 0; err_down = 0;}
		if(flag&0) { geteff_AE(nObj ==1 ? g_cocf_Q_njet_1boost : g_cocf_Q_njet_2boost, v.Jet.Jet.n, eff, err_up, err_down); w *= eff;}
		if(flag&0) { geteff_AE(nObj ==1 ? g_cocf_Q_1boost : g_cocf_Q_2boost, v.MR*v.R2, eff, err_up, err_down); w *= eff;}
  } else if (v.isTop){
		if(flag&0) { eff = 1; err_up = 0; err_down = 0;}
    if(flag&1) { geteff_AE(g_cocf_NonIso_T_njet, v.Jet.Jet.n, eff, err_up, err_down); w *= eff;}
    if(flag&2) { geteff_AE(g_cocf_NonIso_T, v.MR*v.R2, eff, err_up, err_down); w *= eff;}
  } else if (v.isWJets){
		if(flag&0) { eff = 1; err_up = 0; err_down = 0;}
    if(flag&1) { geteff_AE(g_cocf_NonIso_W_njet, v.Jet.Jet.n, eff, err_up, err_down); w *= eff;}
    if(flag&2) { geteff_AE(g_cocf_NonIso_W, v.MR*v.R2, eff, err_up, err_down); w *= eff;}
  }
  return w;
}


double ScaleFactors::calc_QTW_cf(const double& nSigmaCRSF, int flag=0) {
  double w = 1.0, w1 = 1.0, w2 = 1.0;
  double eff, err_up, err_down;
	int nObj = v.FatJet.HadTop.n + v.FatJet.HadH.n + v.FatJet.HadV.n;
  if (v.isQCD){
		if(flag&0) { eff = 1; err_up = 0; err_down = 0;}
		if(flag&1) { geteff_AE(nObj ==1 ? g_cf_Q_1boost : g_cf_Q_2boost, v.MR*v.R2, eff, err_up, err_down); w *= get_syst_weight_(eff, eff+err_up, eff-err_down, nSigmaCRSF);}
		if(flag&2) { geteff_AE(nObj ==1 ? g_cf_Q_njet_1boost : g_cf_Q_njet_2boost, v.Jet.Jet.n, eff, err_up, err_down); w *= get_syst_weight_(eff, eff+err_up, eff-err_down, nSigmaCRSF);}
		if(flag&3) { geteff_AE(nObj ==1 ? g_cf_Q_1boost : g_cf_Q_2boost, v.MR*v.R2, eff, err_up, err_down); w1 *= eff;}
		if(flag&3) { geteff_AE(nObj ==1 ? g_cf_Q_njet_1boost : g_cf_Q_njet_2boost, v.Jet.Jet.n, eff, err_up, err_down); w1 *= eff;}
		if(flag&3) { geteff_AE(nObj ==1 ? g_cocf_Q_njet_1boost : g_cocf_Q_njet_2boost, v.Jet.Jet.n, eff, err_up, err_down); w2 *= eff;}
		if(flag&3) { geteff_AE(nObj ==1 ? g_cocf_Q_1boost : g_cocf_Q_2boost, v.MR*v.R2, eff, err_up, err_down); w2 *= eff;}
  } else if (v.isTop){
		if(flag&0) { eff = 1; err_up = 0; err_down = 0;}
		if(flag&1) { geteff_AE(nObj ==1 ? g_cf_T_1boost : g_cf_T_2boost, v.MR*v.R2, eff, err_up, err_down); w *= get_syst_weight_(eff, eff+err_up, eff-err_down, nSigmaCRSF);}
		if(flag&2) { geteff_AE(nObj ==1 ? g_cf_T_njet_1boost : g_cf_T_njet_2boost, v.Jet.Jet.n, eff, err_up, err_down); w *= get_syst_weight_(eff, eff+err_up, eff-err_down, nSigmaCRSF);}
		if(flag&3) { geteff_AE(nObj ==1 ? g_cf_T_1boost : g_cf_T_2boost, v.MR*v.R2, eff, err_up, err_down); w1 *= eff;}
		if(flag&3) { geteff_AE(nObj ==1 ? g_cf_T_njet_1boost : g_cf_T_njet_2boost, v.Jet.Jet.n, eff, err_up, err_down); w1 *= eff;}
		if(flag&3) { geteff_AE(nObj ==1 ? g_cocf_T_njet_1boost : g_cocf_T_njet_2boost, v.Jet.Jet.n, eff, err_up, err_down); w2 *= eff;}
		if(flag&3) { geteff_AE(nObj ==1 ? g_cocf_T_1boost : g_cocf_T_2boost, v.MR*v.R2, eff, err_up, err_down); w2 *= eff;}
  } else if (v.isWJets){
		if(flag&0) { eff = 1; err_up = 0; err_down = 0;}
		if(flag&1) { geteff_AE(nObj ==1 ? g_cf_W_1boost : g_cf_W_2boost, v.MR*v.R2, eff, err_up, err_down); w *= get_syst_weight_(eff, eff+err_up, eff-err_down, nSigmaCRSF);}
		if(flag&2) { geteff_AE(nObj ==1 ? g_cf_W_njet_1boost : g_cf_W_njet_2boost, v.Jet.Jet.n, eff, err_up, err_down); w *= get_syst_weight_(eff, eff+err_up, eff-err_down, nSigmaCRSF);}
		if(flag&3) { geteff_AE(nObj ==1 ? g_cf_W_1boost : g_cf_W_2boost, v.MR*v.R2, eff, err_up, err_down); w1 *= eff;}
		if(flag&3) { geteff_AE(nObj ==1 ? g_cf_W_njet_1boost : g_cf_W_njet_2boost, v.Jet.Jet.n, eff, err_up, err_down); w1 *= eff;}
		if(flag&3) { geteff_AE(nObj ==1 ? g_cocf_W_njet_1boost : g_cocf_W_njet_2boost, v.Jet.Jet.n, eff, err_up, err_down); w2 *= eff;}
		if(flag&3) { geteff_AE(nObj ==1 ? g_cocf_W_1boost : g_cocf_W_2boost, v.MR*v.R2, eff, err_up, err_down); w2 *= eff;}
  }
	w *= get_syst_weight_(1, 1+abs(w1-w2), 1-abs(w1-w2), nSigmaCRSF);
  return w;
}

std::pair<double, double> ScaleFactors::calc_Z_cf(const double& nSigmaCRSF, int flag=0) {
  double weight_L = 1.0, weight_G = 1.0;
	double w1 = 1., w2 = 1.;
  double eff, err_up, err_down;
	int nObj = v.FatJet.HadTop.n + v.FatJet.HadH.n + v.FatJet.HadV.n;
  if (v.isZInv){
		if(flag&0) { eff = 1; err_up = 0; err_down = 0;}
		if(flag&1) { geteff_AE(nObj ==1 ? g_cf_L_1boost : g_cf_L_2boost, v.MR*v.R2, eff, err_up, err_down); weight_L *= get_syst_weight_(eff, eff+err_up, eff-err_down, nSigmaCRSF);}
		if(flag&2) { geteff_AE(nObj ==1 ? g_cf_L_njet_1boost : g_cf_L_njet_2boost, v.Jet.Jet.n, eff, err_up, err_down); weight_L *= get_syst_weight_(eff, eff+err_up, eff-err_down, nSigmaCRSF);}
		if(flag&0) { eff = 1; err_up = 0; err_down = 0;}
    if(flag&1) { geteff_AE(g_cf_G, v.MR*v.R2, eff, err_up, err_down); weight_G *= get_syst_weight_(eff, eff+err_up, eff-err_down, nSigmaCRSF);}
    if(flag&2) { geteff_AE(g_cf_GJet_njet, v.Jet.Jet.n, eff, err_up, err_down); weight_G *= get_syst_weight_(eff, eff+err_up, eff-err_down, nSigmaCRSF);}
		if(flag&4) { geteff_AE(g_cf_G_MassTag, nObj, eff, err_up, err_down); weight_G *= get_syst_weight_(eff, eff+err_up, eff-err_down, nSigmaCRSF);}
		if(flag&8) {
			if(v.year == 2016) 			weight_G *= get_syst_weight_(0.7941, 0.7941+0.02362, 0.7941-0.02362, nSigmaCRSF);
			else if(v.year == 2017) weight_G *= get_syst_weight_(1.1917, 1.1917+0.03351, 1.1917-0.03351, nSigmaCRSF);
			else if(v.year == 2018) weight_G *= get_syst_weight_(0.8214, 0.8214+0.02151, 0.8214-0.02151, nSigmaCRSF);
		}

		if(flag&15) { geteff_AE(nObj ==1 ? g_cf_L_1boost : g_cf_L_2boost, v.MR*v.R2, eff, err_up, err_down); w1 *= eff;}
		if(flag&15) { geteff_AE(nObj ==1 ? g_cf_L_njet_1boost : g_cf_L_njet_2boost, v.Jet.Jet.n, eff, err_up, err_down); w1 *= eff;}
    if(flag&15) { geteff_AE(g_cf_G, v.MR*v.R2, eff, err_up, err_down); w2 *= eff;}
    if(flag&15) { geteff_AE(g_cf_GJet_njet, v.Jet.Jet.n, eff, err_up, err_down); w2 *= eff;}
		if(flag&15) { geteff_AE(g_cf_G_MassTag, nObj, eff, err_up, err_down); w2 *= eff;}

		weight_L *= get_syst_weight_(1, 1+abs(w1-w2), 1-abs(w1-w2), nSigmaCRSF);
		weight_G *= get_syst_weight_(1, 1+abs(w1-w2), 1-abs(w1-w2), nSigmaCRSF);
  }
  return std::make_pair(weight_G, weight_L);
}

double ScaleFactors::calc_nonIso_cf(const double& nSigmaCRSF, int flag=0) {
  double w = 1.0;
	double w1 = 1., w2 = 1.;
  double eff, err_up, err_down;
	int nObj = v.FatJet.LepTop.n + v.FatJet.LepJet.n + v.FatJet.HadTop.n + v.FatJet.HadV.n;
  if (v.isQCD){
		//if(flag&0) { eff = 1; err_up = 0; err_down = 0;}
		if(flag&0) { geteff_AE(nObj ==1 ? g_cf_Q_1boost : g_cf_Q_2boost, v.MR*v.R2, eff, err_up, err_down); w *= get_syst_weight_(eff, eff+err_up, eff-err_down, nSigmaCRSF);}
		if(flag&0) { geteff_AE(nObj ==1 ? g_cf_Q_njet_1boost : g_cf_Q_njet_2boost, v.Jet.Jet.n, eff, err_up, err_down); w *= get_syst_weight_(eff, eff+err_up, eff-err_down, nSigmaCRSF);}
		if(flag&3) { geteff_AE(nObj ==1 ? g_cf_Q_1boost : g_cf_Q_2boost, v.MR*v.R2, eff, err_up, err_down); w1 *= eff;}
		if(flag&3) { geteff_AE(nObj ==1 ? g_cf_Q_njet_1boost : g_cf_Q_njet_2boost, v.Jet.Jet.n, eff, err_up, err_down); w1 *= eff;}
		if(flag&3) { geteff_AE(nObj ==1 ? g_cocf_Q_njet_1boost : g_cocf_Q_njet_2boost, v.Jet.Jet.n, eff, err_up, err_down); w2 *= eff;}
		if(flag&3) { geteff_AE(nObj ==1 ? g_cocf_Q_1boost : g_cocf_Q_2boost, v.MR*v.R2, eff, err_up, err_down); w2 *= eff;}
  } else if (v.isTop){
		if(flag&0) { eff = 1; err_up = 0; err_down = 0;}
    if(flag&1) { geteff_AE(g_cf_NonIso_T, v.MR*v.R2, eff, err_up, err_down); w *= get_syst_weight_(eff, eff+err_up, eff-err_down, nSigmaCRSF);}
    if(flag&2) { geteff_AE(g_cf_NonIso_T_njet, v.Jet.Jet.n, eff, err_up, err_down); w *= get_syst_weight_(eff, eff+err_up, eff-err_down, nSigmaCRSF);}
    if(flag&3) { geteff_AE(g_cf_NonIso_T, v.MR*v.R2, eff, err_up, err_down); w1 *= eff;}
    if(flag&3) { geteff_AE(g_cf_NonIso_T_njet, v.Jet.Jet.n, eff, err_up, err_down); w1 *= eff;}
    if(flag&3) { geteff_AE(g_cocf_NonIso_T_njet, v.Jet.Jet.n, eff, err_up, err_down); w2 *= eff;}
    if(flag&3) { geteff_AE(g_cocf_NonIso_T, v.MR*v.R2, eff, err_up, err_down); w2 *= eff;}
  } else if (v.isWJets){
		if(flag&0) { eff = 1; err_up = 0; err_down = 0;}
    if(flag&1) { geteff_AE(g_cf_NonIso_W, v.MR*v.R2, eff, err_up, err_down); w *= get_syst_weight_(eff, eff+err_up, eff-err_down, nSigmaCRSF);}
    if(flag&2) { geteff_AE(g_cf_NonIso_W_njet, v.Jet.Jet.n, eff, err_up, err_down); w *= get_syst_weight_(eff, eff+err_up, eff-err_down, nSigmaCRSF);}
    if(flag&3) { geteff_AE(g_cf_NonIso_W, v.MR*v.R2, eff, err_up, err_down); w1 *= eff;}
    if(flag&3) { geteff_AE(g_cf_NonIso_W, v.Jet.Jet.n, eff, err_up, err_down); w1 *= eff;}
    if(flag&3) { geteff_AE(g_cocf_NonIso_W, v.Jet.Jet.n, eff, err_up, err_down); w2 *= eff;}
    if(flag&3) { geteff_AE(g_cocf_NonIso_W, v.MR*v.R2, eff, err_up, err_down); w2 *= eff;}
  }
	w *= get_syst_weight_(1, 1+abs(w1-w2), 1-abs(w1-w2), nSigmaCRSF);
  return w;
}

std::pair<double, double> ScaleFactors::calc_b_tagging_sf(const double& nSigmaBTagSF, const double& nSigmaBTagFastSimSF) {

  double pMC_loose = 1, pData_loose = 1;
  double pMC_medium = 1, pData_medium = 1;
  while (v.Jet.Loop()) {
    // Jet ID
    if (v.Jet.Jet.pass[v.Jet.i]) {
      float pt = v.Jet().pt, eta = v.Jet().eta;
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
      if (v.isFastSim) {
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
  double weight_loose = 1, weight_medium = 1;
  if(pMC_loose!=0) weight_loose = pData_loose/pMC_loose;
  if(pMC_medium!=0) weight_medium = pData_medium/pMC_medium;
  return std::make_pair(weight_loose, weight_medium);
}

//std::tuple<double, double> ScaleFactors::calc_ele_sf(const double& nSigmaEleRecoSF, const double& nSigmaEleIDSF, const double& nSigmaEleIsoSF, const double& nSigmaEleFastSimSF) {
std::tuple<double, double> ScaleFactors::calc_ele_sf(const double& nSigmaEleFullSimSF, const double& nSigmaEleFastSimSF) {
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
      //weight_veto   *= get_syst_weight_(reco_sf, reco_sf_err, nSigmaEleRecoSF);

      if (v.isFastSim) {
        geteff2D(eff_fast_ele_mvalooseid_tightip2d, pt, eta, sf, sf_err);
        weight_veto *= sf;
      }
      
      geteff2D(eff_full_ele_veto, pt, eta, sf, sf_err);
      weight_veto *= get_syst_weight_(sf, sf_err, nSigmaEleFullSimSF);
      if (v.isFastSim) {
        geteff2D(eff_fast_ele_miniiso04, pt, eta, sf, sf_err);
        weight_veto *= sf;
        // Apply 2% error per electron leg
        weight_veto *= get_syst_weight_(1, 0.02, nSigmaEleFastSimSF);
      }
    }

    // Selected Electrons
    if (v.Electron.Select.pass[v.Electron.i]) {
      // RECO
      //weight_select   *= get_syst_weight_(reco_sf, reco_sf_err, nSigmaEleRecoSF);
        
      if (v.isFastSim) {
        // FASTSIM ID
        geteff2D(eff_fast_ele_mediumid, pt, eta, sf, sf_err);
        weight_select *= sf;
      }

      // ISO
      geteff2D(eff_full_ele_razor, pt, eta, sf, sf_err);
      weight_select *= get_syst_weight_(sf, sf_err, nSigmaEleFullSimSF);
      
      if (v.isFastSim) {
        // FASTSIM ISO
        if (ELE_SELECT_MINIISO_CUT == 0.1)
          geteff2D(eff_fast_ele_miniiso01, pt, eta, sf, sf_err);
        weight_select *= sf;
        // Apply 2% error per electron leg
        weight_select *= get_syst_weight_(1, 0.02, nSigmaEleFastSimSF);
      }
    }
  }

  return std::make_tuple(weight_veto, weight_select);
}

double ScaleFactors::calc_pho_sf() {
  double sf, sf_err;
  double weight_select = 1.0;
  while (v.Photon.Loop()) {
    double pt  = v.Photon().pt;
    double eta = v.Photon().eta;

    // Selected Photons
    if (v.Photon.Select.pass[v.Photon.i]) {
      // ID
      geteff2D(eff_full_pho_mediumid, pt, eta, sf, sf_err);
      weight_select *= sf;
    }
  }
  return weight_select;
}

//std::tuple<double, double> ScaleFactors::calc_muon_sf(const double& nSigmaMuonTrkSF, const double& nSigmaMuonFullSimSF, const double& nSigmaMuonFastSimSF) {
std::tuple<double, double> ScaleFactors::calc_muon_sf(const double& nSigmaMuonFullSimSF, const double& nSigmaMuonFastSimSF) {
  //double trk_sf=1, trk_sf_err_up=0, trk_sf_err_down=0, trk_sf_veto=1, trk_sf_veto_err_up=0, trk_sf_veto_err_down=0, sf, sf_err;
	double sf, sf_err;
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
      //weight_veto *= get_syst_weight_(trk_sf_veto, trk_sf_veto+trk_sf_veto_err_up, trk_sf_veto-trk_sf_veto_err_down, nSigmaMuonTrkSF);

      // ID
      geteff2D(eff_full_muon_veto, pt, eta, sf, sf_err);
      weight_veto *= sf;
      if (v.isFastSim) {
        // FASTSIM ID
        geteff2D(eff_fast_muon_vetoid, pt, eta, sf, sf_err);
        weight_veto *= sf;
      }
      
      // ISO
      //if (MU_VETO_MINIISO_CUT == 0.2)
      //  geteff2D(eff_full_muon_miniiso02, pt, eta, sf, sf_err);
      //else if (MU_VETO_MINIISO_CUT == 0.4)
      //  geteff2D(eff_full_muon_miniiso04, pt, eta, sf, sf_err);
      //weight_veto *= sf;
      //
      // Additional systematics
      //weight_veto *= get_syst_weight_(1, 0.03, nSigmaMuonFullSimSF);
      //if (v.isFastSim) weight_veto *= get_syst_weight_(1, 0.02, nSigmaMuonFastSimSF);
    }

    // Selected Muons
    if (v.Muon.Select.pass[v.Muon.i]) {
      // Apply Tracking scale factor here
      //if (MU_SELECT_PT_CUT<10) {
      //  weight_select *= get_syst_weight_(trk_sf_veto, trk_sf_veto+trk_sf_veto_err_up, trk_sf_veto-trk_sf_veto_err_down, nSigmaMuonTrkSF);
      //} else {
      //  weight_select *= get_syst_weight_(trk_sf, trk_sf+trk_sf_err_up, trk_sf-trk_sf_err_down, nSigmaMuonTrkSF);
      //}
      //
      // ID
      geteff2D(eff_full_muon_razor, pt, eta, sf, sf_err);
      weight_select *= sf;
      if (v.isFastSim) {
        // FASTSIM ID
        geteff2D(eff_fast_muon_mediumid, pt, eta, sf, sf_err);
        weight_select *= sf;
      }
      //
      //// ISO
      //if (MU_SELECT_MINIISO_CUT == 0.2)
      //  geteff2D(eff_full_muon_miniiso02, pt, eta, sf, sf_err);
      //else if (MU_SELECT_MINIISO_CUT == 0.4)
      //  geteff2D(eff_full_muon_miniiso04, pt, eta, sf, sf_err);
      //weight_select *= sf;

      // Additional systematics
      //weight_select *= get_syst_weight_(1, 0.03, nSigmaMuonFullSimSF);
      //if (v.isFastSim) weight_select *= get_syst_weight_(1, 0.02, nSigmaMuonFastSimSF);
    }
  }

  return std::make_tuple(weight_veto, weight_select);
}


//____________________________________________________
//          Analysis Specific Scale factors
//    (Defined for each search region separately)

void
ScaleFactors::apply_scale_factors(const unsigned int& syst_index, std::vector<double>& all_weights, std::vector<std::vector<double> >& w_nm1,
                                  const unsigned int& s, const std::vector<std::vector<double> >& nSigmaSFs)
{
  size_t i = 0;

  // Don't forget to specify the total number of sigmas you use in settings_*.h !
  // Boosted objects - Top/W/Z/Higgs/Mass (tag data/fullsim, tag fastsim/fullsim, mistag data/fullsim, mistag fastsim/fullsim)
  if (debug) sw_(sw_s0, t_s0, 1);
  sf_boost = calc_boost_tagging_sf(nSigmaSFs[i][s], nSigmaSFs[i+1][s], nSigmaSFs[i+2][s]);
  //sf_mass  = calc_mass_tagging_sf();
	sf_mass = 1;
  i+=3;
  if (debug) sw_(sw_s0, t_s0, 0);

  // Electron SFs (5 sigmas - reco, fullsim id/iso, fastsim)
  if (debug) sw_(sw_s1, t_s1, 1);
  std::tie(sf_ele_veto, sf_ele_medium) = calc_ele_sf(nSigmaSFs[i][s], nSigmaSFs[i+1][s]);
  i+=2;
  if (debug) sw_(sw_s1, t_s1, 0);

  // Photon SFs
  if (debug) sw_(sw_s1, t_s1, 1);
  sf_pho_medium = calc_pho_sf();
  if (debug) sw_(sw_s1, t_s1, 0);

  // Muon SFs (3 sigmas - tracking, fullsim, fastsim)
  if (debug) sw_(sw_s2, t_s2, 1);
  std::tie(sf_muon_veto, sf_muon_medium) =  calc_muon_sf(nSigmaSFs[i][s], nSigmaSFs[i+1][s]);
  i+=2;
  if (debug) sw_(sw_s2, t_s2, 0);

  // b tagging SFs (2 sigma - fullsim, fastsim)
  if (debug) sw_(sw_s3, t_s3, 1);
  std::pair<double, double> sf_btag = calc_b_tagging_sf(nSigmaSFs[i][s], nSigmaSFs[i+1][s]);
  sf_btag_loose = sf_btag.first, sf_btag_medium = sf_btag.second;
  i+=2;
  if (debug) sw_(sw_s3, t_s3, 0);

  if (debug) sw_(sw_s4, t_s4, 1);
	// CFs application for CRs
	// 0 : Nothing to apply, 1 : MRxR2 CFs apply, 2 : NJet CFs apply, 3 : MRxR2, NJet CFs apply
	cf_QTW_CR = calc_QTW_CR_cf(0);
	cf_QTW_CoCR = calc_QTW_CoCR_cf(0);
	cf_NonIso_CR = calc_nonIso_CR_cf(0);
	cf_NonIso_CoCR = calc_nonIso_CoCR_cf(0);
	// 0 : Nothing to apply, 1 : MRxR2 CFs apply, 2 : NJet CFs apply, 3 : MRxR2, NJet CFs apply, 4 : NBoostJet CFs apply, 7 : MRxR2, NJet, NBoostJet CFs apply
	std::pair<double, double> cf_ZL_CR = calc_Z_CR_cf(0);
	cf_Z_CR = cf_ZL_CR.first, cf_L_CR = cf_ZL_CR.second;
  if (debug) sw_(sw_s4, t_s4, 0);

  if (debug) sw_(sw_s5, t_s5, 1);


	// CFs application for VRs, SRs
	// 0 : Nothing to apply, 1 : MRxR2 CFs apply, 2 : NJet CFs apply, 3 : MRxR2, NJet CFs apply
	cf_QTW = calc_QTW_cf(nSigmaSFs[i][s], 0);
	cf_NonIso = calc_nonIso_cf(nSigmaSFs[i+2][s], 0);
	// 0 : Nothing to apply, 1 : MRxR2 CFs apply, 2 : NJet CFs apply, 3 : MRxR2, NJet CFs apply, 4 : NBoostJet CFs apply, 7 : MRxR2, NJet, NBoostJet CFs apply, 8 : Double ratio apply, 15 : MRxR2, NJet, NBoostJet CFs, Double ratio apply apply
	std::pair<double, double> cf_ZL = calc_Z_cf(nSigmaSFs[i+1][s], 0);
	cf_Z = cf_ZL.first, cf_L = cf_ZL.second;

	i+=3;
  if (debug) sw_(sw_s5, t_s5, 0);

    // N-1 weights
  // Calculate weight for all search regions, but without a specific weight
  // Do not allow syst variation, because it's very slow
  // And we probably don't care about systematics in N-1 weight plots
  if (syst_index==0) {
    //for (const auto& region : magic_enum::enum_values<Region>()) {
    for (size_t region=0; region<Region::SR_Had_1htop; ++region) {
      if (debug) sw_(sw_s6, t_s6, 1);
      size_t n=all_weights.size()+scale_factors[region].size();
      if (w_nm1[region].empty()) w_nm1[region].resize(n,1);
      else w_nm1[region].assign(n,1);
      if (debug) sw_(sw_s6, t_s6, 0);
      if (debug) sw_(sw_s7, t_s7, 1);
      // [i] is the index of the weight to exclude
      for (size_t i=0; i<n; ++i) {
        w_nm1[region][i] = 1;
        if (!v.isData) {
            // [j] all the rest is applied
          for (size_t j=0; j<n; ++j) if (j!=i) {
            if (j<all_weights.size()) w_nm1[region][i] *= all_weights[j];
            else  w_nm1[region][i] *= (*scale_factors[region][j-all_weights.size()]);
          }
        }
      }
      if (debug) sw_(sw_s7, t_s7, 0);
    }
  }
}

void ScaleFactors::sw_(TStopwatch* sw, double& t, bool start=true) {
  if (start) {
    sw->Start(kTRUE); 
  } else {
    sw->Stop();
    t += sw-> RealTime();
  }
}

#endif // End header guard
