#ifndef SCALEFACTORS_H
#define SCALEFACTORS_H

// Private headers
#include "eventBuffer.h" // make sure to set to same as in tnm.h
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
    
    scale_factors[Region::CR_QCD17_1Boost].push_back(&sf_ele_veto);
    scale_factors[Region::CR_QCD17_1Boost].push_back(&sf_muon_veto);
    scale_factors[Region::CR_QCD17_1Boost].push_back(&sf_btag_loose);
    scale_factors[Region::CR_QCD17_1Boost].push_back(&cf_QTW_CR);

		scale_factors[Region::CR_QCD17_2Boost] = scale_factors[Region::CR_QCD17_1Boost];
    
    scale_factors[Region::CR_Top17_1Boost].push_back(&sf_ele_veto);
    scale_factors[Region::CR_Top17_1Boost].push_back(&sf_muon_veto);
    scale_factors[Region::CR_Top17_1Boost].push_back(&sf_btag_medium);
    scale_factors[Region::CR_Top17_1Boost].push_back(&cf_QTW_CR);

		scale_factors[Region::CR_Top17_2Boost] = scale_factors[Region::CR_Top17_1Boost];
    
    scale_factors[Region::CR_W17_1Boost].push_back(&sf_ele_veto);
    scale_factors[Region::CR_W17_1Boost].push_back(&sf_muon_veto);
    scale_factors[Region::CR_W17_1Boost].push_back(&sf_btag_loose);
    scale_factors[Region::CR_W17_1Boost].push_back(&cf_QTW_CR);

		scale_factors[Region::CR_W17_2Boost] = scale_factors[Region::CR_W17_1Boost];

    scale_factors[Region::CoCR_QCD17_1Boost].push_back(&sf_ele_veto);
    scale_factors[Region::CoCR_QCD17_1Boost].push_back(&sf_muon_veto);
    scale_factors[Region::CoCR_QCD17_1Boost].push_back(&sf_btag_loose);
    scale_factors[Region::CoCR_QCD17_1Boost].push_back(&cf_QTW_CoCR);

		scale_factors[Region::CoCR_QCD17_2Boost] = scale_factors[Region::CoCR_QCD17_1Boost];
    
    scale_factors[Region::CoCR_Top17_1Boost].push_back(&sf_ele_veto);
    scale_factors[Region::CoCR_Top17_1Boost].push_back(&sf_muon_veto);
    scale_factors[Region::CoCR_Top17_1Boost].push_back(&sf_btag_medium);
    scale_factors[Region::CoCR_Top17_1Boost].push_back(&cf_QTW_CoCR);

		scale_factors[Region::CoCR_Top17_2Boost] = scale_factors[Region::CoCR_Top17_1Boost];
    
    scale_factors[Region::CoCR_W17_1Boost].push_back(&sf_ele_veto);
    scale_factors[Region::CoCR_W17_1Boost].push_back(&sf_muon_veto);
    scale_factors[Region::CoCR_W17_1Boost].push_back(&sf_btag_loose);
    scale_factors[Region::CoCR_W17_1Boost].push_back(&cf_QTW_CoCR);

		scale_factors[Region::CoCR_W17_2Boost] = scale_factors[Region::CoCR_W17_1Boost];

    scale_factors[Region::Val_DiLep] = scale_factors[Region::CR_Top17_1Boost];
    
    scale_factors[Region::CR_LTop17_1Boost].push_back(&sf_ele_veto);
    scale_factors[Region::CR_LTop17_1Boost].push_back(&sf_muon_veto);
    scale_factors[Region::CR_LTop17_1Boost].push_back(&sf_btag_medium);
    scale_factors[Region::CR_LTop17_1Boost].push_back(&cf_L_CR);

		scale_factors[Region::CR_LTop17_2Boost] = scale_factors[Region::CR_LTop17_1Boost];
    
    scale_factors[Region::CR_L17_1Boost].push_back(&sf_ele_veto);
    scale_factors[Region::CR_L17_1Boost].push_back(&sf_muon_veto);
    scale_factors[Region::CR_L17_1Boost].push_back(&sf_btag_loose);
    scale_factors[Region::CR_L17_1Boost].push_back(&cf_L_CR);

		scale_factors[Region::CR_L17_2Boost] = scale_factors[Region::CR_L17_1Boost];
    
    scale_factors[Region::Val_NonIso_RMT].push_back(&sf_ele_nonIso);
    scale_factors[Region::Val_NonIso_RMT].push_back(&sf_muon_nonIso);
    scale_factors[Region::Val_NonIso_RMT].push_back(&cf_NonIso);

		scale_factors[Region::CR_NonIso_RMTdPhi] = scale_factors[Region::Val_NonIso_RdPhi] = scale_factors[Region::Val_NonIso_RMT];
    
    scale_factors[Region::CR_NonIso_0b_RMTdPhi].push_back(&sf_btag_loose);
    scale_factors[Region::CR_NonIso_0b_RMTdPhi].push_back(&sf_ele_nonIso);
    scale_factors[Region::CR_NonIso_0b_RMTdPhi].push_back(&sf_muon_nonIso);
    scale_factors[Region::CR_NonIso_0b_RMTdPhi].push_back(&cf_NonIso_CR);

    scale_factors[Region::CR_NonIso_b_RMTdPhi].push_back(&sf_btag_medium);
    scale_factors[Region::CR_NonIso_b_RMTdPhi].push_back(&sf_ele_nonIso);
    scale_factors[Region::CR_NonIso_b_RMTdPhi].push_back(&sf_muon_nonIso);
    scale_factors[Region::CR_NonIso_b_RMTdPhi].push_back(&cf_NonIso_CR);
    
    scale_factors[Region::CoCR_NonIso_0b_RMTdPhi].push_back(&sf_btag_loose);
    scale_factors[Region::CoCR_NonIso_0b_RMTdPhi].push_back(&sf_ele_nonIso);
    scale_factors[Region::CoCR_NonIso_0b_RMTdPhi].push_back(&sf_muon_nonIso);
    scale_factors[Region::CoCR_NonIso_0b_RMTdPhi].push_back(&cf_NonIso_CoCR);

    scale_factors[Region::CoCR_NonIso_b_RMTdPhi].push_back(&sf_btag_medium);
    scale_factors[Region::CoCR_NonIso_b_RMTdPhi].push_back(&sf_ele_nonIso);
    scale_factors[Region::CoCR_NonIso_b_RMTdPhi].push_back(&sf_muon_nonIso);
    scale_factors[Region::CoCR_NonIso_b_RMTdPhi].push_back(&cf_NonIso_CoCR);
    
    scale_factors[Region::CR_Fake].push_back(&sf_ele_veto);
    scale_factors[Region::CR_Fake].push_back(&sf_muon_veto);

    scale_factors[Region::CR_Fake_0b].push_back(&sf_ele_veto);
    scale_factors[Region::CR_Fake_0b].push_back(&sf_muon_veto);
    scale_factors[Region::CR_Fake_0b].push_back(&sf_btag_loose);

    scale_factors[Region::CR_Fake_b].push_back(&sf_ele_veto);
    scale_factors[Region::CR_Fake_b].push_back(&sf_muon_veto);
    scale_factors[Region::CR_Fake_b].push_back(&sf_btag_medium);
    
    scale_factors[Region::CR_Real].push_back(&sf_ele_veto);
    scale_factors[Region::CR_Real].push_back(&sf_muon_veto);
    scale_factors[Region::CR_Real].push_back(&sf_btag_medium);
    
    scale_factors[Region::CR_1LepInv].push_back(&sf_boost);
    scale_factors[Region::CR_1LepInv].push_back(&sf_ele_veto);
    scale_factors[Region::CR_1LepInv].push_back(&sf_muon_veto);
    scale_factors[Region::CR_1LepInv].push_back(&sf_btag_loose);
    scale_factors[Region::CR_1LepInv_LepTrig] = scale_factors[Region::CR_1LepInv];
    
    //scale_factors[Region::CR_2LepInv].push_back(&sf_boost);
    scale_factors[Region::CR_2LepInv].push_back(&sf_ele_medium);
    scale_factors[Region::CR_2LepInv].push_back(&sf_muon_medium);
    scale_factors[Region::CR_2LepInv].push_back(&sf_btag_loose);
    
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
    //scale_factors[Region::Pre].push_back(&sf_boost);
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
    scale_factors[Region::SR_Lepjet_0V_24j].push_back(&sf_ele_nonIso);
    scale_factors[Region::SR_Lepjet_0V_24j].push_back(&sf_muon_nonIso);
    scale_factors[Region::SR_Lepjet_0V_24j].push_back(&sf_btag_loose);
    scale_factors[Region::SR_Lepjet_0V_24j].push_back(&cf_NonIso);

    scale_factors[Region::SR_Lepjet_0V_5j] = scale_factors[Region::SR_Lepjet_1V_24j] = scale_factors[Region::SR_Lepjet_1V_5j] = scale_factors[Region::SR_Lepjet_0V_24j];
		scale_factors[Region::SR_Lepjet_1htop] = scale_factors[Region::SR_Lepjet_0V_24j];
		//scale_factors[Region::SR_Leptop_0htop] = scale_factors[Region::SR_Leptop_1htop] = scale_factors[Region::SR_Lepjet_0V_24j];

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
  double calc_pu_jet_sf(const double&);
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
	std::pair<double, double> calc_Z_cf(const double&, const double&, const double&, int);
	double calc_nonIso_cf(const double&, int);

  std::pair<double, double> calc_b_tagging_sf(const double&, const double&, const double&);

  std::tuple<double, double, double> calc_ele_sf(const double&, const double&);

  double calc_pho_sf();

  std::tuple<double, double, double> calc_muon_sf(const double&, const double&);
  
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
  
  TH2F* eff_pu;

	TH2F* eff_full_ele_veto;
	TH2F* eff_full_ele_razor;
	TH2F* eff_full_ele_nonIso;
	TH2F* eff_full_ele_nonIso_B2G ;
	TH2F* eff_fast_ele_razor;
	TH2F* eff_fast_ele_nonIso;
	TH2F* eff_fast_ele_nonIso_B2G ;
	TH2F* eff_full_muon_veto;
	TH2F* eff_full_muon_razor;
	TH2F* eff_full_muon_nonIso;
	TH2F* eff_full_muon_nonIso_B2G;
	TH2F* eff_fast_muon_razor;
	TH2F* eff_fast_muon_nonIso;
	TH2F* eff_fast_muon_nonIso_B2G;
  TH2F* eff_full_pho_mediumid;
  
  TGraphAsymmErrors* eff_full_fake_bHadTop;
  TGraphAsymmErrors* eff_full_fake_eHadTop;
  //TGraphAsymmErrors* eff_fast_fake_bHadTop;
  //TGraphAsymmErrors* eff_fast_fake_eHadTop;
  //TGraphAsymmErrors* eff_fast_bHadTop;
  //TGraphAsymmErrors* eff_fast_eHadTop;
  TGraphAsymmErrors* eff_full_fake_bHadW;
  TGraphAsymmErrors* eff_full_fake_eHadW;
  TGraphAsymmErrors* eff_full_fake_bHadZ;
  TGraphAsymmErrors* eff_full_fake_eHadZ;
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
  double sf_ele_veto, sf_ele_medium, sf_ele_nonIso;
  double sf_pho_medium;
  double sf_muon_veto, sf_muon_medium, sf_muon_nonIso;
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
  if (v.year==2018) eff_pu = getplot_TH2F("scale_factors/pu/PUID_106XTraining_ULRun2_EffSFandUncties_v1.root", "h2_eff_sfUL2018_L", "pu");
  else if (v.year==2017) eff_pu = getplot_TH2F("scale_factors/pu/PUID_106XTraining_ULRun2_EffSFandUncties_v1.root", "h2_eff_sfUL2017_L", "pu");
  else if (v.isAPV) eff_pu = getplot_TH2F("scale_factors/pu/PUID_106XTraining_ULRun2_EffSFandUncties_v1.root", "h2_eff_sfUL2016APV_L", "pu");
  else eff_pu = getplot_TH2F("scale_factors/pu/PUID_106XTraining_ULRun2_EffSFandUncties_v1.root", "h2_eff_sfUL2016_L", "pu");

  // Lepton scale factors
  if (v.year==2018) {
    eff_full_ele_veto                 = getplot_TH2F("scale_factors/electron/fullsim_electron_veto_UL2018.root",     						"EGamma_SF2D", 				"ele1");
    eff_full_ele_razor                = getplot_TH2F("scale_factors/electron/fullsim_electron_isolated_UL2018.root",     				"EGamma_SF2D", 				"ele2");
    eff_full_ele_nonIso               = getplot_TH2F("scale_factors/electron/fullsim_electron_nonIsolated_UL2018.root",     		"EGamma_SF2D", 				"ele3");
    eff_full_ele_nonIso_B2G           = getplot_TH2F("scale_factors/electron/fullsim_electron_nonIsolated_B2GCut_UL2018.root",  "h_eta_pT_electron",  "ele4");
    eff_fast_ele_razor                = getplot_TH2F("scale_factors/electron/fastsim_electron_isolated_UL2018.root",     				"EGamma_SF2D", 				"ele6");
    eff_fast_ele_nonIso               = getplot_TH2F("scale_factors/electron/fastsim_electron_nonIsolated_UL2018.root",     		"EGamma_SF2D", 				"ele7");
    eff_fast_ele_nonIso_B2G           = getplot_TH2F("scale_factors/electron/fastsim_electron_nonIsolated_B2GCut_UL2018.root",  "h_eta_pT_electron",  "ele8");
    eff_full_muon_veto                = getplot_TH2F("scale_factors/muon/fullsim_muon_veto_UL2018.root",     						"NUM_RazorVeto_DEN_genTracks_abseta_pt", 				"mu1");
    eff_full_muon_razor               = getplot_TH2F("scale_factors/muon/fullsim_muon_isolated_UL2018.root",     				"NUM_RazorPass_DEN_genTracks_abseta_pt", 				"mu2");
    eff_full_muon_nonIso              = getplot_TH2F("scale_factors/muon/fullsim_muon_nonIsolated_UL2018.root",     		"NUM_RazorNoIso_DEN_genTracks_abseta_pt", 			"mu3");
    eff_full_muon_nonIso_B2G          = getplot_TH2F("scale_factors/muon/fullsim_muon_nonIsolated_B2GCut_UL2018.root",  "h_eta_pT_muon",  															"mu4");
    eff_fast_muon_razor               = getplot_TH2F("scale_factors/muon/fastsim_muon_isolated_UL2018.root",     				"NUM_RazorPass_DEN_genTracks_abseta_pt", 				"mu6");
    eff_fast_muon_nonIso              = getplot_TH2F("scale_factors/muon/fastsim_muon_nonIsolated_UL2018.root",     		"NUM_RazorNoIso_DEN_genTracks_abseta_pt", 			"mu7");
    eff_fast_muon_nonIso_B2G          = getplot_TH2F("scale_factors/muon/fastsim_muon_nonIsolated_B2GCut_UL2018.root",  "h_eta_pT_muon",  															"mu8");
    eff_full_pho_mediumid             = getplot_TH2F("scale_factors/photon/fullsim/egammaEffi.txt_EGM2D_Pho_Med_UL18.root","EGamma_SF2D","pho1");
  } else if (v.year==2017) {
    eff_full_ele_veto                 = getplot_TH2F("scale_factors/electron/fullsim_electron_veto_UL2017.root",     						"EGamma_SF2D", 				"ele1");
    eff_full_ele_razor                = getplot_TH2F("scale_factors/electron/fullsim_electron_isolated_UL2017.root",     				"EGamma_SF2D", 				"ele2");
    eff_full_ele_nonIso               = getplot_TH2F("scale_factors/electron/fullsim_electron_nonIsolated_UL2017.root",     		"EGamma_SF2D", 				"ele3");
    eff_full_ele_nonIso_B2G           = getplot_TH2F("scale_factors/electron/fullsim_electron_nonIsolated_B2GCut_UL2017.root",  "h_eta_pT_electron",  "ele4");
    eff_fast_ele_razor                = getplot_TH2F("scale_factors/electron/fastsim_electron_isolated_UL2017.root",     				"EGamma_SF2D", 				"ele6");
    eff_fast_ele_nonIso               = getplot_TH2F("scale_factors/electron/fastsim_electron_nonIsolated_UL2017.root",     		"EGamma_SF2D", 				"ele7");
    eff_fast_ele_nonIso_B2G           = getplot_TH2F("scale_factors/electron/fastsim_electron_nonIsolated_B2GCut_UL2017.root",  "h_eta_pT_electron",  "ele8");
    eff_full_muon_veto                = getplot_TH2F("scale_factors/muon/fullsim_muon_veto_UL2017.root",     						"NUM_RazorVeto_DEN_genTracks_abseta_pt", 				"mu1");
    eff_full_muon_razor               = getplot_TH2F("scale_factors/muon/fullsim_muon_isolated_UL2017.root",     				"NUM_RazorPass_DEN_genTracks_abseta_pt", 				"mu2");
    eff_full_muon_nonIso              = getplot_TH2F("scale_factors/muon/fullsim_muon_nonIsolated_UL2017.root",     		"NUM_RazorNoIso_DEN_genTracks_abseta_pt", 			"mu3");
    eff_full_muon_nonIso_B2G          = getplot_TH2F("scale_factors/muon/fullsim_muon_nonIsolated_B2GCut_UL2017.root",  "h_eta_pT_muon",  															"mu4");
    eff_fast_muon_razor               = getplot_TH2F("scale_factors/muon/fastsim_muon_isolated_UL2017.root",     				"NUM_RazorPass_DEN_genTracks_abseta_pt", 				"mu6");
    eff_fast_muon_nonIso              = getplot_TH2F("scale_factors/muon/fastsim_muon_nonIsolated_UL2017.root",     		"NUM_RazorNoIso_DEN_genTracks_abseta_pt", 			"mu7");
    eff_fast_muon_nonIso_B2G          = getplot_TH2F("scale_factors/muon/fastsim_muon_nonIsolated_B2GCut_UL2017.root",  "h_eta_pT_muon",  															"mu8");
    eff_full_pho_mediumid             = getplot_TH2F("scale_factors/photon/fullsim/egammaEffi.txt_EGM2D_PHO_Medium_UL17.root","EGamma_SF2D","pho1");
  } else if(v.isAPV) {
    eff_full_ele_veto                 = getplot_TH2F("scale_factors/electron/fullsim_electron_veto_UL2016_preVFP.root",     						"EGamma_SF2D", 				"ele1");
    eff_full_ele_razor                = getplot_TH2F("scale_factors/electron/fullsim_electron_isolated_UL2016_preVFP.root",     				"EGamma_SF2D", 				"ele2");
    eff_full_ele_nonIso               = getplot_TH2F("scale_factors/electron/fullsim_electron_nonIsolated_UL2016_preVFP.root",     		"EGamma_SF2D", 				"ele3");
    eff_full_ele_nonIso_B2G           = getplot_TH2F("scale_factors/electron/fullsim_electron_nonIsolated_B2GCut_UL2016_preVFP.root",  "h_eta_pT_electron",  "ele4");
    eff_fast_ele_razor                = getplot_TH2F("scale_factors/electron/fastsim_electron_isolated_UL2016.root",     				"EGamma_SF2D", 				"ele6");
    eff_fast_ele_nonIso               = getplot_TH2F("scale_factors/electron/fastsim_electron_nonIsolated_UL2016.root",     		"EGamma_SF2D", 				"ele7");
    eff_fast_ele_nonIso_B2G           = getplot_TH2F("scale_factors/electron/fastsim_electron_nonIsolated_B2GCut_UL2016.root",  "h_eta_pT_electron",  "ele8");
    eff_full_muon_veto                = getplot_TH2F("scale_factors/muon/fullsim_muon_veto_UL2016_preVFP.root",     						"NUM_RazorVeto_DEN_genTracks_abseta_pt", 				"mu1");
    eff_full_muon_razor               = getplot_TH2F("scale_factors/muon/fullsim_muon_isolated_UL2016_preVFP.root",     				"NUM_RazorPass_DEN_genTracks_abseta_pt", 				"mu2");
    eff_full_muon_nonIso              = getplot_TH2F("scale_factors/muon/fullsim_muon_nonIsolated_UL2016_preVFP.root",     		"NUM_RazorNoIso_DEN_genTracks_abseta_pt", 			"mu3");
    eff_full_muon_nonIso_B2G          = getplot_TH2F("scale_factors/muon/fullsim_muon_nonIsolated_B2GCut_UL2016_preVFP.root",  "h_eta_pT_muon",  															"mu4");
    eff_fast_muon_razor               = getplot_TH2F("scale_factors/muon/fastsim_muon_isolated_UL2016.root",     				"NUM_RazorPass_DEN_genTracks_abseta_pt", 				"mu6");
    eff_fast_muon_nonIso              = getplot_TH2F("scale_factors/muon/fastsim_muon_nonIsolated_UL2016.root",     		"NUM_RazorNoIso_DEN_genTracks_abseta_pt", 			"mu7");
    eff_fast_muon_nonIso_B2G          = getplot_TH2F("scale_factors/muon/fastsim_muon_nonIsolated_B2GCut_UL2016.root",  "h_eta_pT_muon",  															"mu8");
    eff_full_pho_mediumid             = getplot_TH2F("scale_factors/photon/fullsim/egammaEffi.txt_EGM2D_Pho_Medium_UL16.root","EGamma_SF2D","pho1");
  } else {
    eff_full_ele_veto                 = getplot_TH2F("scale_factors/electron/fullsim_electron_veto_UL2016_postVFP.root",     						"EGamma_SF2D", 				"ele1");
    eff_full_ele_razor                = getplot_TH2F("scale_factors/electron/fullsim_electron_isolated_UL2016_postVFP.root",     				"EGamma_SF2D", 				"ele2");
    eff_full_ele_nonIso               = getplot_TH2F("scale_factors/electron/fullsim_electron_nonIsolated_UL2016_postVFP.root",     		"EGamma_SF2D", 				"ele3");
    eff_full_ele_nonIso_B2G           = getplot_TH2F("scale_factors/electron/fullsim_electron_nonIsolated_B2GCut_UL2016_postVFP.root",  "h_eta_pT_electron",  "ele4");
    eff_fast_ele_razor                = getplot_TH2F("scale_factors/electron/fastsim_electron_isolated_UL2016.root",     				"EGamma_SF2D", 				"ele6");
    eff_fast_ele_nonIso               = getplot_TH2F("scale_factors/electron/fastsim_electron_nonIsolated_UL2016.root",     		"EGamma_SF2D", 				"ele7");
    eff_fast_ele_nonIso_B2G           = getplot_TH2F("scale_factors/electron/fastsim_electron_nonIsolated_B2GCut_UL2016.root",  "h_eta_pT_electron",  "ele8");
    eff_full_muon_veto                = getplot_TH2F("scale_factors/muon/fullsim_muon_veto_UL2016_postVFP.root",     						"NUM_RazorVeto_DEN_genTracks_abseta_pt", 				"mu1");
    eff_full_muon_razor               = getplot_TH2F("scale_factors/muon/fullsim_muon_isolated_UL2016_postVFP.root",     				"NUM_RazorPass_DEN_genTracks_abseta_pt", 				"mu2");
    eff_full_muon_nonIso              = getplot_TH2F("scale_factors/muon/fullsim_muon_nonIsolated_UL2016_postVFP.root",     		"NUM_RazorNoIso_DEN_genTracks_abseta_pt", 			"mu3");
    eff_full_muon_nonIso_B2G          = getplot_TH2F("scale_factors/muon/fullsim_muon_nonIsolated_B2GCut_UL2016_postVFP.root",  "h_eta_pT_muon",  															"mu4");
    eff_fast_muon_razor               = getplot_TH2F("scale_factors/muon/fastsim_muon_isolated_UL2016.root",     				"NUM_RazorPass_DEN_genTracks_abseta_pt", 				"mu6");
    eff_fast_muon_nonIso              = getplot_TH2F("scale_factors/muon/fastsim_muon_nonIsolated_UL2016.root",     		"NUM_RazorNoIso_DEN_genTracks_abseta_pt", 			"mu7");
    eff_fast_muon_nonIso_B2G          = getplot_TH2F("scale_factors/muon/fastsim_muon_nonIsolated_B2GCut_UL2016.root",  "h_eta_pT_muon",  															"mu8");
    eff_full_pho_mediumid             = getplot_TH2F("scale_factors/photon/fullsim/egammaEffi.txt_EGM2D_Pho_Medium_UL16_postVFP.root","EGamma_SF2D","pho1");
  }

  // W/Top (anti-/mass-)tag (and fake rate) scale factors
  if (v.year==2018) {
    eff_full_fake_bHadTop = getplot_TGraphAsymmErrors("scale_factors/boosted_objects/Fakerate_SF_output.root", "HadTopTagFakeRate_vs_JetAK8PtBinsTopMassCut_2018_CR_Fake_Barrel_Scale", "full_Top_b");
    eff_full_fake_eHadTop = getplot_TGraphAsymmErrors("scale_factors/boosted_objects/Fakerate_SF_output.root", "HadTopTagFakeRate_vs_JetAK8PtFewBinsTopMassCut_2018_CR_Fake_Endcap_Scale", "full_Top_e");
    eff_full_fake_bHadW   = getplot_TGraphAsymmErrors("scale_factors/boosted_objects/Fakerate_SF_output.root", "HadWTagFakeRate_vs_JetAK8PtBinsWMassCut_2018_CR_Fake_Barrel_Scale",   "full_W_b");
    eff_full_fake_eHadW   = getplot_TGraphAsymmErrors("scale_factors/boosted_objects/Fakerate_SF_output.root", "HadWTagFakeRate_vs_JetAK8PtFewBinsWMassCut_2018_CR_Fake_Endcap_Scale",   "full_W_e");
    eff_full_fake_bHadZ   = getplot_TGraphAsymmErrors("scale_factors/boosted_objects/Fakerate_SF_output.root", "HadZTagFakeRate_vs_JetAK8PtBinsZMassCut_2018_CR_Fake_Barrel_Scale",   "full_Z_b");
    eff_full_fake_eHadZ   = getplot_TGraphAsymmErrors("scale_factors/boosted_objects/Fakerate_SF_output.root", "HadZTagFakeRate_vs_JetAK8PtFewBinsZMassCut_2018_CR_Fake_Endcap_Scale",   "full_Z_e");
    eff_full_fake_bHadH   = getplot_TGraphAsymmErrors("scale_factors/boosted_objects/Fakerate_SF_output.root", "HadHTagFakeRate_vs_JetAK8PtBinsHMassCut_2018_Pre_Barrel_Scale",   "full_H_b");
    eff_full_fake_eHadH   = getplot_TGraphAsymmErrors("scale_factors/boosted_objects/Fakerate_SF_output.root", "HadHTagFakeRate_vs_JetAK8PtFewBinsHMassCut_2018_Pre_Endcap_Scale",   "full_H_e");
    
    eff_fast_V           = getplot_TGraphAsymmErrors("scale_factors/boosted_objects/Top_W_Z_H_fakes.root", "full_fast_2018_HadV",  "fast_V");
    eff_fast_W           = getplot_TGraphAsymmErrors("scale_factors/boosted_objects/Top_W_Z_H_fakes.root", "full_fast_2018_HadW",  "fast_W");
    eff_fast_Z           = getplot_TGraphAsymmErrors("scale_factors/boosted_objects/Top_W_Z_H_fakes.root", "full_fast_2018_HadZ",  "fast_Z");
    eff_fast_H           = getplot_TGraphAsymmErrors("scale_factors/boosted_objects/Top_W_Z_H_fakes.root", "full_fast_2018_HadH",  "fast_H");
    eff_fast_HadTop      = getplot_TGraphAsymmErrors("scale_factors/boosted_objects/Top_W_Z_H_fakes.root", "full_fast_2018_HadTop","fast_HadTop");
  } else if (v.year==2017) {
    eff_full_fake_bHadTop = getplot_TGraphAsymmErrors("scale_factors/boosted_objects/Fakerate_SF_output.root", "HadTopTagFakeRate_vs_JetAK8PtBinsTopMassCut_2017_CR_Fake_Barrel_Scale", "full_Top_b");
    eff_full_fake_eHadTop = getplot_TGraphAsymmErrors("scale_factors/boosted_objects/Fakerate_SF_output.root", "HadTopTagFakeRate_vs_JetAK8PtFewBinsTopMassCut_2017_CR_Fake_Endcap_Scale", "full_Top_e");
    eff_full_fake_bHadW   = getplot_TGraphAsymmErrors("scale_factors/boosted_objects/Fakerate_SF_output.root", "HadWTagFakeRate_vs_JetAK8PtBinsWMassCut_2017_CR_Fake_Barrel_Scale",   "full_W_b");
    eff_full_fake_eHadW   = getplot_TGraphAsymmErrors("scale_factors/boosted_objects/Fakerate_SF_output.root", "HadWTagFakeRate_vs_JetAK8PtFewBinsWMassCut_2017_CR_Fake_Endcap_Scale",   "full_W_e");
    eff_full_fake_bHadZ   = getplot_TGraphAsymmErrors("scale_factors/boosted_objects/Fakerate_SF_output.root", "HadZTagFakeRate_vs_JetAK8PtBinsZMassCut_2017_CR_Fake_Barrel_Scale",   "full_Z_b");
    eff_full_fake_eHadZ   = getplot_TGraphAsymmErrors("scale_factors/boosted_objects/Fakerate_SF_output.root", "HadZTagFakeRate_vs_JetAK8PtFewBinsZMassCut_2017_CR_Fake_Endcap_Scale",   "full_Z_e");
    eff_full_fake_bHadH   = getplot_TGraphAsymmErrors("scale_factors/boosted_objects/Fakerate_SF_output.root", "HadHTagFakeRate_vs_JetAK8PtBinsHMassCut_2017_Pre_Barrel_Scale",   "full_H_b");
    eff_full_fake_eHadH   = getplot_TGraphAsymmErrors("scale_factors/boosted_objects/Fakerate_SF_output.root", "HadHTagFakeRate_vs_JetAK8PtFewBinsHMassCut_2017_Pre_Endcap_Scale",   "full_H_e");
    
    eff_fast_V           = getplot_TGraphAsymmErrors("scale_factors/boosted_objects/Top_W_Z_H_fakes.root", "full_fast_2017_HadV",  "fast_V");
    eff_fast_W           = getplot_TGraphAsymmErrors("scale_factors/boosted_objects/Top_W_Z_H_fakes.root", "full_fast_2017_HadW",  "fast_W");
    eff_fast_Z           = getplot_TGraphAsymmErrors("scale_factors/boosted_objects/Top_W_Z_H_fakes.root", "full_fast_2017_HadZ",  "fast_Z");
    eff_fast_H           = getplot_TGraphAsymmErrors("scale_factors/boosted_objects/Top_W_Z_H_fakes.root", "full_fast_2017_HadH",  "fast_H");
    eff_fast_HadTop      = getplot_TGraphAsymmErrors("scale_factors/boosted_objects/Top_W_Z_H_fakes.root", "full_fast_2017_HadTop","fast_HadTop");
  } else if(v.isAPV) {
    eff_full_fake_bHadTop = getplot_TGraphAsymmErrors("scale_factors/boosted_objects/Fakerate_SF_output.root", "HadTopTagFakeRate_vs_JetAK8PtBinsTopMassCut_2016APV_CR_Fake_Barrel_Scale", "full_Top_b");
    eff_full_fake_eHadTop = getplot_TGraphAsymmErrors("scale_factors/boosted_objects/Fakerate_SF_output.root", "HadTopTagFakeRate_vs_JetAK8PtFewBinsTopMassCut_2016APV_CR_Fake_Endcap_Scale", "full_Top_e");
    eff_full_fake_bHadW   = getplot_TGraphAsymmErrors("scale_factors/boosted_objects/Fakerate_SF_output.root", "HadWTagFakeRate_vs_JetAK8PtBinsWMassCut_2016APV_CR_Fake_Barrel_Scale",   "full_W_b");
    eff_full_fake_eHadW   = getplot_TGraphAsymmErrors("scale_factors/boosted_objects/Fakerate_SF_output.root", "HadWTagFakeRate_vs_JetAK8PtFewBinsWMassCut_2016APV_CR_Fake_Endcap_Scale",   "full_W_e");
    eff_full_fake_bHadZ   = getplot_TGraphAsymmErrors("scale_factors/boosted_objects/Fakerate_SF_output.root", "HadZTagFakeRate_vs_JetAK8PtBinsZMassCut_2016APV_CR_Fake_Barrel_Scale",   "full_Z_b");
    eff_full_fake_eHadZ   = getplot_TGraphAsymmErrors("scale_factors/boosted_objects/Fakerate_SF_output.root", "HadZTagFakeRate_vs_JetAK8PtFewBinsZMassCut_2016APV_CR_Fake_Endcap_Scale",   "full_Z_e");
    eff_full_fake_bHadH   = getplot_TGraphAsymmErrors("scale_factors/boosted_objects/Fakerate_SF_output.root", "HadHTagFakeRate_vs_JetAK8PtBinsHMassCut_2016APV_Pre_Barrel_Scale",   "full_H_b");
    eff_full_fake_eHadH   = getplot_TGraphAsymmErrors("scale_factors/boosted_objects/Fakerate_SF_output.root", "HadHTagFakeRate_vs_JetAK8PtFewBinsHMassCut_2016APV_Pre_Endcap_Scale",   "full_H_e");

    eff_fast_V           = getplot_TGraphAsymmErrors("scale_factors/boosted_objects/Top_W_Z_H_fakes.root", "full_fast_2016_HadV",  "fast_V");
    eff_fast_W           = getplot_TGraphAsymmErrors("scale_factors/boosted_objects/Top_W_Z_H_fakes.root", "full_fast_2016_HadW",  "fast_W");
    eff_fast_Z           = getplot_TGraphAsymmErrors("scale_factors/boosted_objects/Top_W_Z_H_fakes.root", "full_fast_2016_HadZ",  "fast_Z");
    eff_fast_H           = getplot_TGraphAsymmErrors("scale_factors/boosted_objects/Top_W_Z_H_fakes.root", "full_fast_2016_HadH",  "fast_H");
    eff_fast_HadTop      = getplot_TGraphAsymmErrors("scale_factors/boosted_objects/Top_W_Z_H_fakes.root", "full_fast_2016_HadTop","fast_HadTop");
  } else {
    eff_full_fake_bHadTop = getplot_TGraphAsymmErrors("scale_factors/boosted_objects/Fakerate_SF_output.root", "HadTopTagFakeRate_vs_JetAK8PtBinsTopMassCut_2016_CR_Fake_Barrel_Scale", "full_Top_b");
    eff_full_fake_eHadTop = getplot_TGraphAsymmErrors("scale_factors/boosted_objects/Fakerate_SF_output.root", "HadTopTagFakeRate_vs_JetAK8PtFewBinsTopMassCut_2016_CR_Fake_Endcap_Scale", "full_Top_e");
    eff_full_fake_bHadW   = getplot_TGraphAsymmErrors("scale_factors/boosted_objects/Fakerate_SF_output.root", "HadWTagFakeRate_vs_JetAK8PtBinsWMassCut_2016_CR_Fake_Barrel_Scale",   "full_W_b");
    eff_full_fake_eHadW   = getplot_TGraphAsymmErrors("scale_factors/boosted_objects/Fakerate_SF_output.root", "HadWTagFakeRate_vs_JetAK8PtFewBinsWMassCut_2016_CR_Fake_Endcap_Scale",   "full_W_e");
    eff_full_fake_bHadZ   = getplot_TGraphAsymmErrors("scale_factors/boosted_objects/Fakerate_SF_output.root", "HadZTagFakeRate_vs_JetAK8PtBinsZMassCut_2016_CR_Fake_Barrel_Scale",   "full_Z_b");
    eff_full_fake_eHadZ   = getplot_TGraphAsymmErrors("scale_factors/boosted_objects/Fakerate_SF_output.root", "HadZTagFakeRate_vs_JetAK8PtFewBinsZMassCut_2016_CR_Fake_Endcap_Scale",   "full_Z_e");
    eff_full_fake_bHadH   = getplot_TGraphAsymmErrors("scale_factors/boosted_objects/Fakerate_SF_output.root", "HadHTagFakeRate_vs_JetAK8PtBinsHMassCut_2016_Pre_Barrel_Scale",   "full_H_b");
    eff_full_fake_eHadH   = getplot_TGraphAsymmErrors("scale_factors/boosted_objects/Fakerate_SF_output.root", "HadHTagFakeRate_vs_JetAK8PtFewBinsHMassCut_2016_Pre_Endcap_Scale",   "full_H_e");
    
    eff_fast_V           = getplot_TGraphAsymmErrors("scale_factors/boosted_objects/Top_W_Z_H_fakes.root", "full_fast_2016_HadV",  "fast_V");
    eff_fast_W           = getplot_TGraphAsymmErrors("scale_factors/boosted_objects/Top_W_Z_H_fakes.root", "full_fast_2016_HadW",  "fast_W");
    eff_fast_Z           = getplot_TGraphAsymmErrors("scale_factors/boosted_objects/Top_W_Z_H_fakes.root", "full_fast_2016_HadZ",  "fast_Z");
    eff_fast_H           = getplot_TGraphAsymmErrors("scale_factors/boosted_objects/Top_W_Z_H_fakes.root", "full_fast_2016_HadH",  "fast_H");
    eff_fast_HadTop      = getplot_TGraphAsymmErrors("scale_factors/boosted_objects/Top_W_Z_H_fakes.root", "full_fast_2016_HadTop","fast_HadTop");
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
  double w = 1;
  double eff, err_up, err_down;
  while (v.FatJet.Loop()) {
    bool isB = std::abs(v.FatJet().eta)<1.5;
    double Htag = v.FatJet().particleNetMD_Xbb / (v.FatJet().particleNetMD_Xbb+v.FatJet().particleNetMD_QCD);
		double Ztag = v.FatJet().particleNet_ZvsQCD;
    if (v.FatJet.HadH.pass[v.FatJet.i]) {
      // Fake
      if (!v.FatJet().matchGenHadH) {
        geteff_AE(isB ? eff_full_fake_bHadH : eff_full_fake_eHadH, v.FatJet().pt, eff, err_up, err_down);
        w *= get_syst_weight_(eff, eff+err_up, eff-err_down, nSigmaBoostMisTagSF);
      } else {
				//LP WP
/*
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
*/
          if (v.year==2016) {
            if(v.isAPV)   {
              if(Htag >= 0.9883){
                if      (v.FatJet().pt>=300&&v.FatJet().pt<350) w *= get_syst_weight_(1.040, 1.040+0.065, 1.040-0.061, nSigmaBoostTagSF);
                else if (v.FatJet().pt>=350&&v.FatJet().pt<400) w *= get_syst_weight_(1.013, 1.013+0.045, 1.013-0.044, nSigmaBoostTagSF);
                else if (v.FatJet().pt>=400&&v.FatJet().pt<450) w *= get_syst_weight_(1.054, 1.054+0.073, 1.054-0.068, nSigmaBoostTagSF);
                else if (v.FatJet().pt>=450&&v.FatJet().pt<500) w *= get_syst_weight_(1.062, 1.062+0.086, 1.062-0.082, nSigmaBoostTagSF);
                else if (v.FatJet().pt>=500&&v.FatJet().pt<600) w *= get_syst_weight_(1.143, 1.143+0.087, 1.143-0.085, nSigmaBoostTagSF);
                else if (v.FatJet().pt>=600)                    w *= get_syst_weight_(1.059, 1.059+0.144, 1.059-0.142, nSigmaBoostTagSF);
              }   else if (Htag >= 0.9737 && Htag < 0.9883){
                if      (v.FatJet().pt>=300&&v.FatJet().pt<350) w *= get_syst_weight_(1.065, 1.065+0.073, 1.065-0.072, nSigmaBoostTagSF);
                else if (v.FatJet().pt>=350&&v.FatJet().pt<400) w *= get_syst_weight_(1.015, 1.015+0.048, 1.015-0.051, nSigmaBoostTagSF);
                else if (v.FatJet().pt>=400&&v.FatJet().pt<450) w *= get_syst_weight_(1.085, 1.085+0.065, 1.085-0.061, nSigmaBoostTagSF);
                else if (v.FatJet().pt>=450&&v.FatJet().pt<500) w *= get_syst_weight_(1.043, 1.043+0.088, 1.043-0.081, nSigmaBoostTagSF);
                else if (v.FatJet().pt>=500&&v.FatJet().pt<600) w *= get_syst_weight_(0.959, 0.959+0.076, 0.959-0.077, nSigmaBoostTagSF);
                else if (v.FatJet().pt>=600)                    w *= get_syst_weight_(1.009, 1.009+0.131, 1.009-0.111, nSigmaBoostTagSF);
              }   else if (Htag >= 0.9088 && Htag < 0.9737){
                if      (v.FatJet().pt>=300&&v.FatJet().pt<350) w *= get_syst_weight_(1.066, 1.066+0.059, 1.066-0.069, nSigmaBoostTagSF);
                else if (v.FatJet().pt>=350&&v.FatJet().pt<400) w *= get_syst_weight_(1.032, 1.032+0.052, 1.032-0.056, nSigmaBoostTagSF);
                else if (v.FatJet().pt>=400&&v.FatJet().pt<450) w *= get_syst_weight_(0.979, 0.979+0.065, 0.979-0.055, nSigmaBoostTagSF);
                else if (v.FatJet().pt>=450&&v.FatJet().pt<500) w *= get_syst_weight_(0.992, 0.992+0.086, 0.992-0.079, nSigmaBoostTagSF);
                else if (v.FatJet().pt>=500&&v.FatJet().pt<600) w *= get_syst_weight_(0.983, 0.983+0.075, 0.983-0.075, nSigmaBoostTagSF);
                else if (v.FatJet().pt>=600)                    w *= get_syst_weight_(0.971, 0.971+0.102, 0.971-0.096, nSigmaBoostTagSF);
              }
            } else {
              if   (Htag >= 0.9883){
                if      (v.FatJet().pt>=300&&v.FatJet().pt<350) w *= get_syst_weight_(1.011, 1.011+0.073, 1.011-0.075, nSigmaBoostTagSF);
                else if (v.FatJet().pt>=350&&v.FatJet().pt<400) w *= get_syst_weight_(1.060, 1.060+0.053, 1.060-0.052, nSigmaBoostTagSF);
                else if (v.FatJet().pt>=400&&v.FatJet().pt<450) w *= get_syst_weight_(1.041, 1.041+0.050, 1.041-0.048, nSigmaBoostTagSF);
                else if (v.FatJet().pt>=450&&v.FatJet().pt<500) w *= get_syst_weight_(1.034, 1.034+0.052, 1.034-0.048, nSigmaBoostTagSF);
                else if (v.FatJet().pt>=500&&v.FatJet().pt<600) w *= get_syst_weight_(1.066, 1.066+0.077, 1.066-0.073, nSigmaBoostTagSF);
                else if (v.FatJet().pt>=600)                    w *= get_syst_weight_(1.086, 1.086+0.078, 1.086-0.073, nSigmaBoostTagSF);
              }   else if (Htag >= 0.9737 && Htag < 0.9883){
                if      (v.FatJet().pt>=300&&v.FatJet().pt<350) w *= get_syst_weight_(0.990, 0.990+0.066, 0.990-0.068, nSigmaBoostTagSF);
                else if (v.FatJet().pt>=350&&v.FatJet().pt<400) w *= get_syst_weight_(0.998, 0.998+0.066, 0.998-0.065, nSigmaBoostTagSF);
                else if (v.FatJet().pt>=400&&v.FatJet().pt<450) w *= get_syst_weight_(1.022, 1.022+0.057, 1.022-0.053, nSigmaBoostTagSF);
                else if (v.FatJet().pt>=450&&v.FatJet().pt<500) w *= get_syst_weight_(1.024, 1.024+0.068, 1.024-0.059, nSigmaBoostTagSF);
                else if (v.FatJet().pt>=500&&v.FatJet().pt<600) w *= get_syst_weight_(1.113, 1.113+0.086, 1.113-0.080, nSigmaBoostTagSF);
                else if (v.FatJet().pt>=600)                    w *= get_syst_weight_(1.090, 1.090+0.080, 1.090-0.080, nSigmaBoostTagSF);
              }   else if (Htag >= 0.9088 && Htag < 0.9737){
                if      (v.FatJet().pt>=300&&v.FatJet().pt<350) w *= get_syst_weight_(0.948, 0.948+0.065, 0.948-0.067, nSigmaBoostTagSF);
                else if (v.FatJet().pt>=350&&v.FatJet().pt<400) w *= get_syst_weight_(0.965, 0.965+0.064, 0.965-0.075, nSigmaBoostTagSF);
                else if (v.FatJet().pt>=400&&v.FatJet().pt<450) w *= get_syst_weight_(0.980, 0.980+0.064, 0.980-0.057, nSigmaBoostTagSF);
                else if (v.FatJet().pt>=450&&v.FatJet().pt<500) w *= get_syst_weight_(1.032, 1.032+0.073, 1.032-0.069, nSigmaBoostTagSF);
                else if (v.FatJet().pt>=500&&v.FatJet().pt<600) w *= get_syst_weight_(1.074, 1.074+0.101, 1.074-0.112, nSigmaBoostTagSF);
                else if (v.FatJet().pt>=600)                    w *= get_syst_weight_(0.999, 0.999+0.082, 0.999-0.095, nSigmaBoostTagSF);
              }
            }
          } else if (v.year==2017) {
            if   (Htag >= 0.9870){
              if      (v.FatJet().pt>=300&&v.FatJet().pt<350) w *= get_syst_weight_(1.067, 1.067+0.096, 1.067-0.096, nSigmaBoostTagSF);
              else if (v.FatJet().pt>=350&&v.FatJet().pt<400) w *= get_syst_weight_(1.100, 1.100+0.090, 1.100-0.090, nSigmaBoostTagSF);
              else if (v.FatJet().pt>=400&&v.FatJet().pt<450) w *= get_syst_weight_(1.070, 1.070+0.055, 1.070-0.057, nSigmaBoostTagSF);
              else if (v.FatJet().pt>=450&&v.FatJet().pt<500) w *= get_syst_weight_(1.049, 1.049+0.062, 1.049-0.059, nSigmaBoostTagSF);
              else if (v.FatJet().pt>=500&&v.FatJet().pt<600) w *= get_syst_weight_(1.057, 1.057+0.064, 1.057-0.063, nSigmaBoostTagSF);
              else if (v.FatJet().pt>=600)                    w *= get_syst_weight_(1.041, 1.041+0.048, 1.041-0.050, nSigmaBoostTagSF);
            }   else if (Htag >= 0.9714 && Htag < 0.9870){
              if      (v.FatJet().pt>=300&&v.FatJet().pt<350) w *= get_syst_weight_(0.916, 0.916+0.083, 0.916-0.087, nSigmaBoostTagSF);
              else if (v.FatJet().pt>=350&&v.FatJet().pt<400) w *= get_syst_weight_(0.961, 0.961+0.064, 0.961-0.073, nSigmaBoostTagSF);
              else if (v.FatJet().pt>=400&&v.FatJet().pt<450) w *= get_syst_weight_(0.986, 0.986+0.069, 0.986-0.068, nSigmaBoostTagSF);
              else if (v.FatJet().pt>=450&&v.FatJet().pt<500) w *= get_syst_weight_(0.925, 0.925+0.080, 0.925-0.088, nSigmaBoostTagSF);
              else if (v.FatJet().pt>=500&&v.FatJet().pt<600) w *= get_syst_weight_(0.980, 0.980+0.068, 0.980-0.072, nSigmaBoostTagSF);
              else if (v.FatJet().pt>=600)                    w *= get_syst_weight_(0.918, 0.918+0.044, 0.918-0.052, nSigmaBoostTagSF);
            }   else if (Htag >= 0.9105 && Htag < 0.9714){
              if      (v.FatJet().pt>=300&&v.FatJet().pt<350) w *= get_syst_weight_(0.849, 0.849+0.047, 0.849-0.053, nSigmaBoostTagSF);
              else if (v.FatJet().pt>=350&&v.FatJet().pt<400) w *= get_syst_weight_(0.870, 0.870+0.062, 0.870-0.082, nSigmaBoostTagSF);
              else if (v.FatJet().pt>=400&&v.FatJet().pt<450) w *= get_syst_weight_(0.914, 0.914+0.085, 0.914-0.087, nSigmaBoostTagSF);
              else if (v.FatJet().pt>=450&&v.FatJet().pt<500) w *= get_syst_weight_(0.884, 0.884+0.077, 0.884-0.097, nSigmaBoostTagSF);
              else if (v.FatJet().pt>=500&&v.FatJet().pt<600) w *= get_syst_weight_(0.905, 0.905+0.048, 0.905-0.060, nSigmaBoostTagSF);
              else if (v.FatJet().pt>=600)                    w *= get_syst_weight_(0.940, 0.940+0.050, 0.940-0.052, nSigmaBoostTagSF);
					}
          } else if (v.year==2018) {
            if   (Htag >= 0.9880){
              if      (v.FatJet().pt>=300&&v.FatJet().pt<350) w *= get_syst_weight_(0.929, 0.929+0.050, 0.929-0.047, nSigmaBoostTagSF);
              else if (v.FatJet().pt>=350&&v.FatJet().pt<400) w *= get_syst_weight_(1.021, 1.021+0.059, 1.021-0.059, nSigmaBoostTagSF);
              else if (v.FatJet().pt>=400&&v.FatJet().pt<450) w *= get_syst_weight_(1.046, 1.046+0.054, 1.046-0.052, nSigmaBoostTagSF);
              else if (v.FatJet().pt>=450&&v.FatJet().pt<500) w *= get_syst_weight_(0.950, 0.950+0.056, 0.950-0.056, nSigmaBoostTagSF);
              else if (v.FatJet().pt>=500&&v.FatJet().pt<600) w *= get_syst_weight_(1.058, 1.058+0.053, 1.058-0.049, nSigmaBoostTagSF);
              else if (v.FatJet().pt>=600)                    w *= get_syst_weight_(1.016, 1.016+0.044, 1.016-0.043, nSigmaBoostTagSF);
            }   else if (Htag >= 0.9734 && Htag < 0.9880){
              if      (v.FatJet().pt>=300&&v.FatJet().pt<350) w *= get_syst_weight_(0.929, 0.929+0.051, 0.929-0.052, nSigmaBoostTagSF);
              else if (v.FatJet().pt>=350&&v.FatJet().pt<400) w *= get_syst_weight_(1.021, 1.021+0.068, 1.021-0.082, nSigmaBoostTagSF);
              else if (v.FatJet().pt>=400&&v.FatJet().pt<450) w *= get_syst_weight_(1.046, 1.046+0.080, 1.046-0.077, nSigmaBoostTagSF);
              else if (v.FatJet().pt>=450&&v.FatJet().pt<500) w *= get_syst_weight_(0.950, 0.950+0.059, 0.950-0.059, nSigmaBoostTagSF);
              else if (v.FatJet().pt>=500&&v.FatJet().pt<600) w *= get_syst_weight_(1.058, 1.058+0.050, 1.058-0.055, nSigmaBoostTagSF);
              else if (v.FatJet().pt>=600)                    w *= get_syst_weight_(1.016, 1.016+0.064, 1.016-0.083, nSigmaBoostTagSF);
            }   else if (Htag >= 0.9172 && Htag < 0.9734){
              if      (v.FatJet().pt>=300&&v.FatJet().pt<350) w *= get_syst_weight_(0.924, 0.924+0.064, 0.924-0.062, nSigmaBoostTagSF);
              else if (v.FatJet().pt>=350&&v.FatJet().pt<400) w *= get_syst_weight_(0.984, 0.984+0.065, 0.984-0.080, nSigmaBoostTagSF);
              else if (v.FatJet().pt>=400&&v.FatJet().pt<450) w *= get_syst_weight_(0.903, 0.903+0.063, 0.903-0.062, nSigmaBoostTagSF);
              else if (v.FatJet().pt>=450&&v.FatJet().pt<500) w *= get_syst_weight_(0.948, 0.948+0.062, 0.948-0.064, nSigmaBoostTagSF);
              else if (v.FatJet().pt>=500&&v.FatJet().pt<600) w *= get_syst_weight_(0.910, 0.910+0.061, 0.910-0.074, nSigmaBoostTagSF);
              else if (v.FatJet().pt>=600)                    w *= get_syst_weight_(0.969, 0.969+0.057, 0.969-0.093, nSigmaBoostTagSF);
            }
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
      if (v.FatJet().matchGenHadW) {
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
        } else if (v.FatJet().matchGenHadZ) {
        if (v.year==2016) {
					if(v.isAPV) {
            if   (Ztag >= 0.98){
          	if      (v.FatJet().pt>=200&&v.FatJet().pt<400) w *= get_syst_weight_(0.988, 0.988+0.024, 0.988-0.025, nSigmaBoostTagSF);
          	else if (v.FatJet().pt>=400&&v.FatJet().pt<600) w *= get_syst_weight_(1.041, 1.041+0.050, 1.041-0.049, nSigmaBoostTagSF);
          	else if (v.FatJet().pt>=600) 										w *= get_syst_weight_(0.978, 0.978+0.082, 0.978-0.075, nSigmaBoostTagSF);
						} else {
          	if      (v.FatJet().pt>=200&&v.FatJet().pt<400) w *= get_syst_weight_(1.000, 1.000+0.038, 1.000-0.108, nSigmaBoostTagSF);
          	else if (v.FatJet().pt>=400&&v.FatJet().pt<600) w *= get_syst_weight_(0.909, 0.909+0.180, 0.909-0.175, nSigmaBoostTagSF);
          	else if (v.FatJet().pt>=600) 										w *= get_syst_weight_(1.056, 1.056+0.330, 1.056-0.319, nSigmaBoostTagSF);
						}
					} else {
            if   (Ztag >= 0.98){
          	if      (v.FatJet().pt>=200&&v.FatJet().pt<400) w *= get_syst_weight_(1.016, 1.016+0.026, 1.016-0.027, nSigmaBoostTagSF);
          	else if (v.FatJet().pt>=400&&v.FatJet().pt<600) w *= get_syst_weight_(1.029, 1.029+0.032, 1.029-0.029, nSigmaBoostTagSF);
          	else if (v.FatJet().pt>=600) 										w *= get_syst_weight_(1.039, 1.039+0.054, 1.039-0.052, nSigmaBoostTagSF);
						} else {
          	if      (v.FatJet().pt>=200&&v.FatJet().pt<400) w *= get_syst_weight_(0.962, 0.962+0.045, 0.962-0.050, nSigmaBoostTagSF);
          	else if (v.FatJet().pt>=400&&v.FatJet().pt<600) w *= get_syst_weight_(0.966, 0.966+0.042, 0.966-0.041, nSigmaBoostTagSF);
          	else if (v.FatJet().pt>=600) 										w *= get_syst_weight_(1.081, 1.081+0.196, 1.081-0.102, nSigmaBoostTagSF);
						}
					}
        } else if (v.year==2017) {
          if   (Ztag >= 0.98){
          	if      (v.FatJet().pt>=200&&v.FatJet().pt<500) w *= get_syst_weight_(1.016, 1.016+0.035, 1.016-0.037, nSigmaBoostTagSF);
          	else if (v.FatJet().pt>=500&&v.FatJet().pt<800) w *= get_syst_weight_(1.031, 1.031+0.029, 1.031-0.025, nSigmaBoostTagSF);
          	else if (v.FatJet().pt>=600) 										w *= get_syst_weight_(0.908, 0.908+0.048, 0.908-0.076, nSigmaBoostTagSF);
					} else {                                                                                    
          	if      (v.FatJet().pt>=200&&v.FatJet().pt<500) w *= get_syst_weight_(0.932, 0.932+0.056, 0.932-0.074, nSigmaBoostTagSF);
          	else if (v.FatJet().pt>=500&&v.FatJet().pt<600) w *= get_syst_weight_(0.855, 0.855+0.095, 0.855-0.105, nSigmaBoostTagSF);
          	else if (v.FatJet().pt>=600) 										w *= get_syst_weight_(0.847, 0.847+0.274, 0.847-0.299, nSigmaBoostTagSF);
					}
        } else if (v.year==2018) {
          if   (Ztag >= 0.98){
          	if      (v.FatJet().pt>=200&&v.FatJet().pt<400) w *= get_syst_weight_(0.998, 0.998+0.020, 0.998-0.022, nSigmaBoostTagSF);
          	else if (v.FatJet().pt>=400&&v.FatJet().pt<600) w *= get_syst_weight_(0.998, 0.998+0.021, 0.998-0.021, nSigmaBoostTagSF);
          	else if (v.FatJet().pt>=600) 										w *= get_syst_weight_(1.023, 1.023+0.032, 1.023-0.030, nSigmaBoostTagSF);
					} else {                                                                                    
          	if      (v.FatJet().pt>=200&&v.FatJet().pt<400) w *= get_syst_weight_(0.855, 0.855+0.090, 0.855-0.104, nSigmaBoostTagSF);
          	else if (v.FatJet().pt>=400&&v.FatJet().pt<600) w *= get_syst_weight_(0.911, 0.911+0.093, 0.911-0.122, nSigmaBoostTagSF);
          	else if (v.FatJet().pt>=600) 										w *= get_syst_weight_(1.046, 1.046+0.137, 1.046-0.136, nSigmaBoostTagSF);
					}
        }
        }
      	if (v.isFastSim) {
      		geteff_AE(eff_fast_V, v.FatJet().pt, eff, err_up, err_down);
      		w *= get_syst_weight_(eff, eff+err_up, eff-err_down, nSigmaBoostTagFastSimSF);
      	}
      }
      // Fake
      else if (!v.FatJet().matchGenHadW) {
        geteff_AE(isB ? eff_full_fake_bHadW : eff_full_fake_eHadW, v.FatJet().pt, eff, err_up, err_down);
        w *= get_syst_weight_(eff, eff+err_up, eff-err_down, nSigmaBoostMisTagSF);
      }
      else if (!v.FatJet().matchGenHadZ) {
        geteff_AE(isB ? eff_full_fake_bHadZ : eff_full_fake_eHadZ, v.FatJet().pt, eff, err_up, err_down);
        w *= get_syst_weight_(eff, eff+err_up, eff-err_down, nSigmaBoostMisTagSF);
      }
    }
  }
  return w;
}

double ScaleFactors::calc_pu_jet_sf(const double& nSigmaPUTagSF){
  double w = 1;
  double sf, sf_err;
  while (v.Jet.Jet.Loop()) {
		if(!v.Jet.Jet().matchJet) continue;
    geteff2D(eff_pu, v.Jet.Jet().pt, v.Jet.Jet().eta, sf, sf_err);
		w *= get_syst_weight_(sf, sf_err, nSigmaPUTagSF);
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
		if(v.year == 2017) {
			if(v.FatJet.HadV.n >= 1       && v.MR*v.R2>100 && v.MR*v.R2<200) w *= get_syst_weight_(1, 1+0.647342, 1-0.647342, nSigmaCRSF);
			else if(v.FatJet.HadTop.n >= 1&& v.MR*v.R2>100 && v.MR*v.R2<200) w *= get_syst_weight_(1, 1+0.394423, 1-0.394423, nSigmaCRSF);
		}
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

std::pair<double, double> ScaleFactors::calc_Z_cf(const double& nSigmaCRSF, const double& nSigmaDR, const double& nSigmaDi, int flag=0) {
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
			if(v.year == 2016) 			weight_G *= get_syst_weight_(0.655291, 0.655291+0.152578, 0.655291-0.152578, nSigmaDR);
			else if(v.year == 2017) weight_G *= get_syst_weight_(0.648855, 0.648855+0.146534, 0.648855-0.146534, nSigmaDR);
			else if(v.year == 2018) weight_G *= get_syst_weight_(0.67865, 0.67865+0.113588, 0.67865-0.113588, nSigmaDR);
		}

		if(flag&3) { geteff_AE(nObj ==1 ? g_cf_L_1boost : g_cf_L_2boost, v.MR*v.R2, eff, err_up, err_down); w1 *= eff;}
		if(flag&3) { geteff_AE(nObj ==1 ? g_cf_L_njet_1boost : g_cf_L_njet_2boost, v.Jet.Jet.n, eff, err_up, err_down); w1 *= eff;}
    if(flag&7) { geteff_AE(g_cf_G, v.MR*v.R2, eff, err_up, err_down); w2 *= eff;}
    if(flag&7) { geteff_AE(g_cf_GJet_njet, v.Jet.Jet.n, eff, err_up, err_down); w2 *= eff;}
		if(flag&7) { geteff_AE(g_cf_G_MassTag, nObj, eff, err_up, err_down); w2 *= eff;}

		weight_L *= get_syst_weight_(1, 1+abs(w1-w2), 1-abs(w1-w2), nSigmaDi);
		weight_G *= get_syst_weight_(1, 1+abs(w1-w2), 1-abs(w1-w2), nSigmaDi);
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
		if(v.year == 2017) {
			if(v.FatJet.HadV.n >= 1       && v.MR*v.R2>100 && v.MR*v.R2<200) w *= get_syst_weight_(1, 1+0.647342, 1-0.647342, nSigmaCRSF);
			else if(v.FatJet.HadTop.n >= 1&& v.MR*v.R2>100 && v.MR*v.R2<200) w *= get_syst_weight_(1, 1+0.394423, 1-0.394423, nSigmaCRSF);
		}
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

std::pair<double, double> ScaleFactors::calc_b_tagging_sf(const double& nSigmaBTagSFbc, const double& nSigmaBTagSFlight, const double& nSigmaBTagSF) {

	double nSigmaBTag = nSigmaBTagSF;
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
				if(nSigmaBTagSFbc != 0) nSigmaBTag = nSigmaBTagSFbc;
      } else if (v.Jet().hadronFlavour==4) {
        FLAV = BTagEntry::FLAV_C;
        eff_loose  = geteff1D(eff_btag_c_loose,  pt, false);
        eff_medium = geteff1D(eff_btag_c_medium, pt, false);
				if(nSigmaBTagSFbc != 0) nSigmaBTag = nSigmaBTagSFbc;
      } else {
        FLAV = BTagEntry::FLAV_UDSG;
        eff_loose  = geteff1D(eff_btag_l_loose,  pt, false);
        eff_medium = geteff1D(eff_btag_l_medium, pt, false);
				if(nSigmaBTagSFlight != 0) nSigmaBTag = nSigmaBTagSFlight;
      }

      // Scale factors - FullSim
      double sf_loose_cen   = btag_sf_full_loose_ ->eval_auto_bounds("central", FLAV, eta, pt);
      double sf_loose_up    = btag_sf_full_loose_ ->eval_auto_bounds("up",      FLAV, eta, pt);
      double sf_loose_down  = btag_sf_full_loose_ ->eval_auto_bounds("down",    FLAV, eta, pt);
      double sf_medium_cen  = btag_sf_full_medium_->eval_auto_bounds("central", FLAV, eta, pt);
      double sf_medium_up   = btag_sf_full_medium_->eval_auto_bounds("up",      FLAV, eta, pt);
      double sf_medium_down = btag_sf_full_medium_->eval_auto_bounds("down",    FLAV, eta, pt);

      double sf_loose       = get_syst_weight_(sf_loose_cen,  sf_loose_up,  sf_loose_down,  nSigmaBTag);
      double sf_medium      = get_syst_weight_(sf_medium_cen, sf_medium_up, sf_medium_down, nSigmaBTag);

/*
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
*/

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

std::tuple<double, double, double> ScaleFactors::calc_ele_sf(const double& nSigmaEleFullSimSF, const double& nSigmaEleFastSimSF) {
  double sf, sf_err;
  double weight_veto  = 1.0, weight_select = 1.0, weight_nonIso = 1.0;
  while (v.Electron.Loop()) {
    double pt  = v.Electron().pt;
    double eta = v.Electron().eta;

    if (v.Electron.Veto.pass[v.Electron.i]) {
      if (v.isFastSim) {
        weight_veto *= 1;
      } else {
      	geteff2D(eff_full_ele_veto, pt, eta, sf, sf_err);
     		weight_veto *= get_syst_weight_(sf, sf_err, nSigmaEleFullSimSF);
			}
    }
    if (v.Electron.Select.pass[v.Electron.i]) {
      if (v.isFastSim) {
        geteff2D(eff_fast_ele_razor, pt, eta, sf, sf_err);
        weight_select *= sf;
      } else {
      	geteff2D(eff_full_ele_razor, pt, eta, sf, sf_err);
      	weight_select *= get_syst_weight_(sf, sf_err, nSigmaEleFullSimSF);
			}
    }
    if (v.Electron.NonIso.pass[v.Electron.i]) {
      if (v.isFastSim) {
        geteff2D(eff_fast_ele_nonIso, pt, eta, sf, sf_err);
        weight_nonIso *= sf;
        geteff2D(eff_fast_ele_nonIso_B2G, pt, eta, sf, sf_err);
        weight_nonIso *= sf;
      } else {
        geteff2D(eff_full_ele_nonIso, pt, eta, sf, sf_err);
        weight_nonIso *= sf;
        geteff2D(eff_full_ele_nonIso_B2G, pt, eta, sf, sf_err);
        weight_nonIso *= sf;
			}
    }
  }
  return std::make_tuple(weight_veto, weight_select, weight_nonIso);
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

std::tuple<double, double, double> ScaleFactors::calc_muon_sf(const double& nSigmaMuonFullSimSF, const double& nSigmaMuonFastSimSF) {
	double sf, sf_err;
  double weight_veto  = 1.0, weight_select = 1.0, weight_nonIso = 1.0;
  while (v.Muon.Loop()) {
    double pt  = v.Muon().pt;
    double eta = v.Muon().eta;

    // Veto Muons
    if (v.Muon.Veto.pass[v.Muon.i]) {
      if (v.isFastSim) {
        weight_veto *= 1;
      } else {
      	geteff2D(eff_full_muon_veto, pt, eta, sf, sf_err);
      	weight_veto *= sf;
			}
    }
    // Selected Muons
    if (v.Muon.Select.pass[v.Muon.i]) {
      if (v.isFastSim) {
        geteff2D(eff_fast_muon_razor, pt, eta, sf, sf_err);
        weight_select *= sf;
      } else {
      	geteff2D(eff_full_muon_razor, pt, eta, sf, sf_err);
      	weight_select *= sf;
			}
    }
    // nonIso Muons
    if (v.Muon.NonIso.pass[v.Muon.i]) {
      if (v.isFastSim) {
        geteff2D(eff_fast_muon_nonIso, pt, eta, sf, sf_err);
        weight_select *= sf;
        geteff2D(eff_fast_muon_nonIso_B2G, pt, eta, sf, sf_err);
        weight_select *= sf;
      } else {
      	geteff2D(eff_full_muon_nonIso, pt, eta, sf, sf_err);
      	weight_select *= sf;
      	geteff2D(eff_full_muon_nonIso_B2G, pt, eta, sf, sf_err);
      	weight_select *= sf;
			}
    }
  }

  return std::make_tuple(weight_veto, weight_select, weight_nonIso);
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
	//sf_boost = 1;
  i+=3;
  if (debug) sw_(sw_s0, t_s0, 0);

  // Electron SFs (5 sigmas - reco, fullsim id/iso, fastsim)
  if (debug) sw_(sw_s1, t_s1, 1);
  std::tie(sf_ele_veto, sf_ele_medium, sf_ele_nonIso) = calc_ele_sf(nSigmaSFs[i][s], nSigmaSFs[i+1][s]);
	//sf_ele_veto =1; sf_ele_medium=1; sf_ele_nonIso=1;
  i+=2;
  if (debug) sw_(sw_s1, t_s1, 0);

  // Photon SFs
  if (debug) sw_(sw_s1, t_s1, 1);
  sf_pho_medium = calc_pho_sf();
  if (debug) sw_(sw_s1, t_s1, 0);

  // Muon SFs (3 sigmas - tracking, fullsim, fastsim)
  if (debug) sw_(sw_s2, t_s2, 1);
  std::tie(sf_muon_veto, sf_muon_medium, sf_muon_nonIso) =  calc_muon_sf(nSigmaSFs[i][s], nSigmaSFs[i+1][s]);
	//sf_muon_veto = 1; sf_muon_medium=1; sf_muon_nonIso=1;
  i+=2;
  if (debug) sw_(sw_s2, t_s2, 0);

  // b tagging SFs (2 sigma - fullsim, fastsim)
  if (debug) sw_(sw_s3, t_s3, 1);
  std::pair<double, double> sf_btag = calc_b_tagging_sf(nSigmaSFs[i][s], nSigmaSFs[i+1][s], nSigmaSFs[i+2][s]);
  sf_btag_loose = sf_btag.first, sf_btag_medium = sf_btag.second;
	//sf_btag_loose=1;sf_btag_medium=1;
  i+=3;
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
	cf_NonIso = calc_nonIso_cf(nSigmaSFs[i+4][s], 0);
	// 0 : Nothing to apply, 1 : MRxR2 CFs apply, 2 : NJet CFs apply, 3 : MRxR2, NJet CFs apply, 4 : NBoostJet CFs apply, 7 : MRxR2, NJet, NBoostJet CFs apply, 8 : Double ratio apply, 15 : MRxR2, NJet, NBoostJet CFs, Double ratio apply apply
	std::pair<double, double> cf_ZL = calc_Z_cf(nSigmaSFs[i+1][s],nSigmaSFs[i+2][s],nSigmaSFs[i+3][s], 0);
	cf_Z = cf_ZL.first, cf_L = cf_ZL.second;

	i+=5;
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
