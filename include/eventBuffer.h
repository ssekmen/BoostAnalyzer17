#ifndef EVENTBUFFER_H
#define EVENTBUFFER_H
//----------------------------------------------------------------------------
// File:        eventBuffer.h
// Description: Analyzer header for ntuples created by TheNtupleMaker
// Created:     Fri Jun  3 06:42:30 2022 by mkanalyzer.py v2.0.3 14-Oct-2020
// Author:      Changgi Huh
//----------------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cmath>
#include <map>
#include <cassert>
#include "treestream.h"

//Based on UL18, update UL16, UL17 by hand
struct Event_s 
{
  int	nTau;
  int	nMuon;
  int	nLHEScaleWeight;
  int	nFatJet;
  int	nLHEPart;
  int	nGenPart;
  int	nPSWeight;
  int	nSubJet;
  int	nCorrT1METJet;
  int	nJet;
  int	nGenJet;
  int	nOtherPV;
  int	nLHEReweightingWeight;
  int	nboostedTau;
  int	nLHEPdfWeight;
  int	nTrigObj;
  int	nFsrPhoton;
  int	nElectron;
  int	nSubGenJetAK8;
  int	nGenIsolatedPhoton;
  int	nIsoTrack;
  int	nGenJetAK8;
  int	nPhoton;

  float	CaloMET_phi;
  float	CaloMET_pt;
  float	CaloMET_sumEt;
  float	ChsMET_phi;
  float	ChsMET_pt;
  float	ChsMET_sumEt;
  float	DeepMETResolutionTune_phi;
  float	DeepMETResolutionTune_pt;
  float	DeepMETResponseTune_phi;
  float	DeepMETResponseTune_pt;
  bool	Flag_BadChargedCandidateFilter;
  bool	Flag_BadChargedCandidateSummer16Filter;
  bool	Flag_BadPFMuonDzFilter;
  bool	Flag_BadPFMuonFilter;
  bool	Flag_BadPFMuonSummer16Filter;
  bool	Flag_CSCTightHalo2015Filter;
  bool	Flag_CSCTightHaloFilter;
  bool	Flag_CSCTightHaloTrkMuUnvetoFilter;
  bool	Flag_EcalDeadCellBoundaryEnergyFilter;
  bool	Flag_EcalDeadCellTriggerPrimitiveFilter;
  bool	Flag_HBHENoiseFilter;
  bool	Flag_HBHENoiseIsoFilter;
  bool	Flag_HcalStripHaloFilter;
  bool	Flag_METFilters;
  bool	Flag_chargedHadronTrackResolutionFilter;
  bool	Flag_ecalBadCalibFilter;
  bool	Flag_ecalLaserCorrFilter;
  bool	Flag_eeBadScFilter;
  bool	Flag_globalSuperTightHalo2016Filter;
  bool	Flag_globalTightHalo2016Filter;
  bool	Flag_goodVertices;
  bool	Flag_hcalLaserEventFilter;
  bool	Flag_hfNoisyHitsFilter;
  bool	Flag_muonBadTrackFilter;
  bool	Flag_trkPOGFilters;
  bool	Flag_trkPOG_logErrorTooManyClusters;
  bool	Flag_trkPOG_manystripclus53X;
  bool	Flag_trkPOG_toomanystripclus53X;
  float	GenMET_phi;
  float	GenMET_pt;
  float	GenVtx_t0;
  float	GenVtx_x;
  float	GenVtx_y;
  float	GenVtx_z;
  float	Generator_binvar;
  int	Generator_id1;
  int	Generator_id2;
  float	Generator_scalePDF;
  float	Generator_weight;
  float	Generator_x1;
  float	Generator_x2;
  float	Generator_xpdf1;
  float	Generator_xpdf2;
	bool	HLT_PFHT300_PFMET110;
	bool	HLT_PFHT800;
	bool	HLT_PFHT900;
	bool	HLT_Ele15_IsoVVVL_PFHT350;
	bool	HLT_Ele105_CaloIdVT_GsfTrkIdT;
	bool	HLT_Mu15_IsoVVVL_PFHT350;
	bool	HLT_IsoTkMu24;
	bool	HLT_TkMu50;
	bool	HLT_Mu15_IsoVVVL_PFHT400;
	bool	HLT_IsoTkMu27;
	bool	HLT_Ele15_IsoVVVL_PFHT400;
	bool	HLT_Photon22;
	bool	HLT_Photon30;
	bool	HLT_Photon36;
	bool	HLT_Photon125;
	bool	HLT_Photon165_HE10;
	bool	HLT_Photon250_NoHE;
	bool	HLT_PFHT125;
	bool	HLT_PFHT200;
	bool	HLT_PFHT300;
	bool	HLT_PFHT400;
	bool	HLT_PFHT475;
	bool	HLT_PFHT650;
  bool	HLT_AK4CaloJet100;
  bool	HLT_AK4CaloJet120;
  bool	HLT_AK4CaloJet30;
  bool	HLT_AK4CaloJet40;
  bool	HLT_AK4CaloJet50;
  bool	HLT_AK4CaloJet80;
  bool	HLT_AK4PFJet100;
  bool	HLT_AK4PFJet120;
  bool	HLT_AK4PFJet30;
  bool	HLT_AK4PFJet50;
  bool	HLT_AK4PFJet80;
  bool	HLT_AK8PFHT750_TrimMass50;
  bool	HLT_AK8PFHT800_TrimMass50;
  bool	HLT_AK8PFHT850_TrimMass50;
  bool	HLT_AK8PFHT900_TrimMass50;
  bool	HLT_AK8PFJet140;
  bool	HLT_AK8PFJet15;
  bool	HLT_AK8PFJet200;
  bool	HLT_AK8PFJet25;
  bool	HLT_AK8PFJet260;
  bool	HLT_AK8PFJet320;
  bool	HLT_AK8PFJet330_TrimMass30_PFAK8BTagDeepCSV_p1;
  bool	HLT_AK8PFJet330_TrimMass30_PFAK8BTagDeepCSV_p17;
  bool	HLT_AK8PFJet330_TrimMass30_PFAK8BoostedDoubleB_np2;
  bool	HLT_AK8PFJet330_TrimMass30_PFAK8BoostedDoubleB_np4;
  bool	HLT_AK8PFJet330_TrimMass30_PFAK8BoostedDoubleB_p02;
  bool	HLT_AK8PFJet360_TrimMass30;
  bool	HLT_AK8PFJet380_TrimMass30;
  bool	HLT_AK8PFJet40;
  bool	HLT_AK8PFJet400;
  bool	HLT_AK8PFJet400_TrimMass30;
  bool	HLT_AK8PFJet420_TrimMass30;
  bool	HLT_AK8PFJet450;
  bool	HLT_AK8PFJet500;
  bool	HLT_AK8PFJet550;
  bool	HLT_AK8PFJet60;
  bool	HLT_AK8PFJet80;
  bool	HLT_AK8PFJetFwd140;
  bool	HLT_AK8PFJetFwd15;
  bool	HLT_AK8PFJetFwd200;
  bool	HLT_AK8PFJetFwd25;
  bool	HLT_AK8PFJetFwd260;
  bool	HLT_AK8PFJetFwd320;
  bool	HLT_AK8PFJetFwd40;
  bool	HLT_AK8PFJetFwd400;
  bool	HLT_AK8PFJetFwd450;
  bool	HLT_AK8PFJetFwd500;
  bool	HLT_AK8PFJetFwd60;
  bool	HLT_AK8PFJetFwd80;
  bool	HLT_Ele115_CaloIdVT_GsfTrkIdT;
  bool	HLT_Ele12_CaloIdL_TrackIdL_IsoVL_PFJet30;
  bool	HLT_Ele135_CaloIdVT_GsfTrkIdT;
  bool	HLT_Ele145_CaloIdVT_GsfTrkIdT;
  bool	HLT_Ele15_CaloIdL_TrackIdL_IsoVL_PFJet30;
  bool	HLT_Ele15_Ele8_CaloIdL_TrackIdL_IsoVL;
  bool	HLT_Ele15_IsoVVVL_PFHT450;
  bool	HLT_Ele15_IsoVVVL_PFHT450_CaloBTagDeepCSV_4p5;
  bool	HLT_Ele15_IsoVVVL_PFHT450_PFMET50;
  bool	HLT_Ele15_IsoVVVL_PFHT600;
  bool	HLT_Ele15_WPLoose_Gsf;
  bool	HLT_Ele16_Ele12_Ele8_CaloIdL_TrackIdL;
  bool	HLT_Ele17_CaloIdM_TrackIdM_PFJet30;
  bool	HLT_Ele17_WPLoose_Gsf;
  bool	HLT_Ele200_CaloIdVT_GsfTrkIdT;
  bool	HLT_Ele20_WPLoose_Gsf;
  bool	HLT_Ele20_WPTight_Gsf;
  bool	HLT_Ele20_eta2p1_WPLoose_Gsf;
  bool	HLT_Ele23_CaloIdL_TrackIdL_IsoVL_PFJet30;
  bool	HLT_Ele23_CaloIdM_TrackIdM_PFJet30;
  bool	HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL;
  bool	HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ;
  bool	HLT_Ele24_eta2p1_WPTight_Gsf_LooseChargedIsoPFTauHPS30_eta2p1_CrossL1;
  bool	HLT_Ele24_eta2p1_WPTight_Gsf_LooseChargedIsoPFTauHPS30_eta2p1_TightID_CrossL1;
  bool	HLT_Ele24_eta2p1_WPTight_Gsf_MediumChargedIsoPFTauHPS30_eta2p1_CrossL1;
  bool	HLT_Ele24_eta2p1_WPTight_Gsf_MediumChargedIsoPFTauHPS30_eta2p1_TightID_CrossL1;
  bool	HLT_Ele24_eta2p1_WPTight_Gsf_TightChargedIsoPFTauHPS30_eta2p1_CrossL1;
  bool	HLT_Ele24_eta2p1_WPTight_Gsf_TightChargedIsoPFTauHPS30_eta2p1_TightID_CrossL1;
  bool	HLT_Ele250_CaloIdVT_GsfTrkIdT;
  bool	HLT_Ele27_Ele37_CaloIdL_MW;
  bool	HLT_Ele27_WPTight_Gsf;
  bool	HLT_Ele28_HighEta_SC20_Mass55;
  bool	HLT_Ele28_WPTight_Gsf;
  bool	HLT_Ele28_eta2p1_WPTight_Gsf_HT150;
  bool	HLT_Ele300_CaloIdVT_GsfTrkIdT;
  bool	HLT_Ele30_WPTight_Gsf;
  bool	HLT_Ele30_eta2p1_WPTight_Gsf_CentralPFJet35_EleCleaned;
  bool	HLT_Ele32_WPTight_Gsf;
  bool	HLT_Ele32_WPTight_Gsf_L1DoubleEG;
  bool	HLT_Ele35_WPTight_Gsf;
  bool	HLT_Ele35_WPTight_Gsf_L1EGMT;
  bool	HLT_Ele38_WPTight_Gsf;
  bool	HLT_Ele40_WPTight_Gsf;
  bool	HLT_Ele50_CaloIdVT_GsfTrkIdT_PFJet165;
  bool	HLT_Ele50_IsoVVVL_PFHT450;
  bool	HLT_Ele8_CaloIdL_TrackIdL_IsoVL_PFJet30;
  bool	HLT_Ele8_CaloIdM_TrackIdM_PFJet30;
  bool	HLT_HT300_Beamspot;
  bool	HLT_HT400_DisplacedDijet40_DisplacedTrack;
  bool	HLT_HT425;
  bool	HLT_HT430_DisplacedDijet40_DisplacedTrack;
  bool	HLT_HT430_DisplacedDijet60_DisplacedTrack;
  bool	HLT_HT450_Beamspot;
  bool	HLT_HT500_DisplacedDijet40_DisplacedTrack;
  bool	HLT_HT550_DisplacedDijet60_Inclusive;
  bool	HLT_HT650_DisplacedDijet60_Inclusive;
  bool	HLT_IsoMu20;
  bool	HLT_IsoMu20_eta2p1_LooseChargedIsoPFTauHPS27_eta2p1_CrossL1;
  bool	HLT_IsoMu20_eta2p1_LooseChargedIsoPFTauHPS27_eta2p1_TightID_CrossL1;
  bool	HLT_IsoMu20_eta2p1_MediumChargedIsoPFTauHPS27_eta2p1_CrossL1;
  bool	HLT_IsoMu20_eta2p1_MediumChargedIsoPFTauHPS27_eta2p1_TightID_CrossL1;
  bool	HLT_IsoMu20_eta2p1_TightChargedIsoPFTauHPS27_eta2p1_CrossL1;
  bool	HLT_IsoMu20_eta2p1_TightChargedIsoPFTauHPS27_eta2p1_TightID_CrossL1;
  bool	HLT_IsoMu24;
  bool	HLT_IsoMu24_TwoProngs35;
  bool	HLT_IsoMu24_eta2p1;
  bool	HLT_IsoMu24_eta2p1_MediumChargedIsoPFTau50_Trk30_eta2p1_1pr;
  bool	HLT_IsoMu24_eta2p1_MediumChargedIsoPFTauHPS35_Trk1_TightID_eta2p1_Reg_CrossL1;
  bool	HLT_IsoMu24_eta2p1_MediumChargedIsoPFTauHPS35_Trk1_eta2p1_Reg_CrossL1;
  bool	HLT_IsoMu24_eta2p1_TightChargedIsoPFTauHPS35_Trk1_TightID_eta2p1_Reg_CrossL1;
  bool	HLT_IsoMu24_eta2p1_TightChargedIsoPFTauHPS35_Trk1_eta2p1_Reg_CrossL1;
  bool	HLT_IsoMu27;
  bool	HLT_IsoMu27_LooseChargedIsoPFTauHPS20_Trk1_eta2p1_SingleL1;
  bool	HLT_IsoMu27_MET90;
  bool	HLT_IsoMu27_MediumChargedIsoPFTauHPS20_Trk1_eta2p1_SingleL1;
  bool	HLT_IsoMu27_TightChargedIsoPFTauHPS20_Trk1_eta2p1_SingleL1;
  bool	HLT_IsoMu30;
  bool	HLT_IsoTrackHB;
  bool	HLT_IsoTrackHE;
  bool	HLT_MET105_IsoTrk50;
  bool	HLT_MET120_IsoTrk50;
  bool	HLT_Mu10_TrkIsoVVL_DiPFJet40_DEta3p5_MJJ750_HTT350_PFMETNoMu60;
  bool	HLT_Mu12;
  bool	HLT_Mu12_DoublePFJets100_CaloBTagDeepCSV_p71;
  bool	HLT_Mu12_DoublePFJets200_CaloBTagDeepCSV_p71;
  bool	HLT_Mu12_DoublePFJets350_CaloBTagDeepCSV_p71;
  bool	HLT_Mu12_DoublePFJets40MaxDeta1p6_DoubleCaloBTagDeepCSV_p71;
  bool	HLT_Mu12_DoublePFJets40_CaloBTagDeepCSV_p71;
  bool	HLT_Mu12_DoublePFJets54MaxDeta1p6_DoubleCaloBTagDeepCSV_p71;
  bool	HLT_Mu12_DoublePFJets62MaxDeta1p6_DoubleCaloBTagDeepCSV_p71;
  bool	HLT_Mu12_DoublePhoton20;
  bool	HLT_Mu12_IP6_part0;
  bool	HLT_Mu12_IP6_part1;
  bool	HLT_Mu12_IP6_part2;
  bool	HLT_Mu12_IP6_part3;
  bool	HLT_Mu12_IP6_part4;
  bool	HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL;
  bool	HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ;
  bool	HLT_Mu15;
  bool	HLT_Mu15_IsoVVVL_PFHT450;
  bool	HLT_Mu15_IsoVVVL_PFHT450_CaloBTagDeepCSV_4p5;
  bool	HLT_Mu15_IsoVVVL_PFHT450_PFMET50;
  bool	HLT_Mu15_IsoVVVL_PFHT600;
  bool	HLT_Mu17;
  bool	HLT_Mu17_Photon30_IsoCaloId;
  bool	HLT_Mu17_TrkIsoVVL;
  bool	HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL;
  bool	HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ;
  bool	HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8;
  bool	HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass8;
  bool	HLT_Mu18_Mu9;
  bool	HLT_Mu18_Mu9_DZ;
  bool	HLT_Mu18_Mu9_SameSign;
  bool	HLT_Mu18_Mu9_SameSign_DZ;
  bool	HLT_Mu19;
  bool	HLT_Mu19_TrkIsoVVL;
  bool	HLT_Mu19_TrkIsoVVL_Mu9_TrkIsoVVL;
  bool	HLT_Mu19_TrkIsoVVL_Mu9_TrkIsoVVL_DZ;
  bool	HLT_Mu19_TrkIsoVVL_Mu9_TrkIsoVVL_DZ_Mass3p8;
  bool	HLT_Mu19_TrkIsoVVL_Mu9_TrkIsoVVL_DZ_Mass8;
  bool	HLT_Mu20;
  bool	HLT_Mu20_Mu10;
  bool	HLT_Mu20_Mu10_DZ;
  bool	HLT_Mu20_Mu10_SameSign;
  bool	HLT_Mu20_Mu10_SameSign_DZ;
  bool	HLT_Mu20_TkMu0_Phi;
  bool	HLT_Mu23_Mu12;
  bool	HLT_Mu23_Mu12_DZ;
  bool	HLT_Mu23_Mu12_SameSign;
  bool	HLT_Mu23_Mu12_SameSign_DZ;
  bool	HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL;
  bool	HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ;
  bool	HLT_Mu25_TkMu0_Onia;
  bool	HLT_Mu25_TkMu0_Phi;
  bool	HLT_Mu27;
  bool	HLT_Mu27_Ele37_CaloIdL_MW;
  bool	HLT_Mu30_TkMu0_Psi;
  bool	HLT_Mu30_TkMu0_Upsilon;
  bool	HLT_Mu37_Ele27_CaloIdL_MW;
  bool	HLT_Mu37_TkMu27;
  bool	HLT_Mu38NoFiltersNoVtxDisplaced_Photon38_CaloIdL;
  bool	HLT_Mu3_L1SingleMu5orSingleMu7;
  bool	HLT_Mu3_PFJet40;
  bool	HLT_Mu3er1p5_PFJet100er2p5_PFMET100_PFMHT100_IDTight;
  bool	HLT_Mu3er1p5_PFJet100er2p5_PFMET70_PFMHT70_IDTight;
  bool	HLT_Mu3er1p5_PFJet100er2p5_PFMET80_PFMHT80_IDTight;
  bool	HLT_Mu3er1p5_PFJet100er2p5_PFMET90_PFMHT90_IDTight;
  bool	HLT_Mu3er1p5_PFJet100er2p5_PFMETNoMu100_PFMHTNoMu100_IDTight;
  bool	HLT_Mu3er1p5_PFJet100er2p5_PFMETNoMu70_PFMHTNoMu70_IDTight;
  bool	HLT_Mu3er1p5_PFJet100er2p5_PFMETNoMu80_PFMHTNoMu80_IDTight;
  bool	HLT_Mu3er1p5_PFJet100er2p5_PFMETNoMu90_PFMHTNoMu90_IDTight;
  bool	HLT_Mu43NoFiltersNoVtxDisplaced_Photon43_CaloIdL;
  bool	HLT_Mu43NoFiltersNoVtx_Photon43_CaloIdL;
  bool	HLT_Mu48NoFiltersNoVtx_Photon48_CaloIdL;
  bool	HLT_Mu4_TrkIsoVVL_DiPFJet90_40_DEta3p5_MJJ750_HTT300_PFMETNoMu60;
  bool	HLT_Mu50;
  bool	HLT_Mu50_IsoVVVL_PFHT450;
  bool	HLT_Mu55;
  bool	HLT_Mu7_IP4_part0;
  bool	HLT_Mu7_IP4_part1;
  bool	HLT_Mu7_IP4_part2;
  bool	HLT_Mu7_IP4_part3;
  bool	HLT_Mu7_IP4_part4;
  bool	HLT_Mu7p5_L2Mu2_Jpsi;
  bool	HLT_Mu7p5_L2Mu2_Upsilon;
  bool	HLT_Mu7p5_Track2_Jpsi;
  bool	HLT_Mu7p5_Track2_Upsilon;
  bool	HLT_Mu7p5_Track3p5_Jpsi;
  bool	HLT_Mu7p5_Track3p5_Upsilon;
  bool	HLT_Mu7p5_Track7_Jpsi;
  bool	HLT_Mu7p5_Track7_Upsilon;
  bool	HLT_Mu8;
  bool	HLT_Mu8_DiEle12_CaloIdL_TrackIdL;
  bool	HLT_Mu8_DiEle12_CaloIdL_TrackIdL_DZ;
  bool	HLT_Mu8_Ele8_CaloIdM_TrackIdM_Mass8_PFHT350;
  bool	HLT_Mu8_Ele8_CaloIdM_TrackIdM_Mass8_PFHT350_DZ;
  bool	HLT_Mu8_IP3_part0;
  bool	HLT_Mu8_IP3_part1;
  bool	HLT_Mu8_IP3_part2;
  bool	HLT_Mu8_IP3_part3;
  bool	HLT_Mu8_IP3_part4;
  bool	HLT_Mu8_IP5_part0;
  bool	HLT_Mu8_IP5_part1;
  bool	HLT_Mu8_IP5_part2;
  bool	HLT_Mu8_IP5_part3;
  bool	HLT_Mu8_IP5_part4;
  bool	HLT_Mu8_IP6_part0;
  bool	HLT_Mu8_IP6_part1;
  bool	HLT_Mu8_IP6_part2;
  bool	HLT_Mu8_IP6_part3;
  bool	HLT_Mu8_IP6_part4;
  bool	HLT_Mu8_TrkIsoVVL;
  bool	HLT_Mu8_TrkIsoVVL_DiPFJet40_DEta3p5_MJJ750_HTT300_PFMETNoMu60;
  bool	HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL;
  bool	HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ;
  bool	HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_CaloDiJet30;
  bool	HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_CaloDiJet30_CaloBtagDeepCSV_1p5;
  bool	HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_PFDiJet30;
  bool	HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_PFDiJet30_PFBtagDeepCSV_1p5;
  bool	HLT_Mu9_IP4_part0;
  bool	HLT_Mu9_IP4_part1;
  bool	HLT_Mu9_IP4_part2;
  bool	HLT_Mu9_IP4_part3;
  bool	HLT_Mu9_IP4_part4;
  bool	HLT_Mu9_IP5_part0;
  bool	HLT_Mu9_IP5_part1;
  bool	HLT_Mu9_IP5_part2;
  bool	HLT_Mu9_IP5_part3;
  bool	HLT_Mu9_IP5_part4;
  bool	HLT_Mu9_IP6_part0;
  bool	HLT_Mu9_IP6_part1;
  bool	HLT_Mu9_IP6_part2;
  bool	HLT_Mu9_IP6_part3;
  bool	HLT_Mu9_IP6_part4;
  bool	HLT_OldMu100;
  bool	HLT_PFHT1050;
  bool	HLT_PFHT180;
  bool	HLT_PFHT250;
  bool	HLT_PFHT330PT30_QuadPFJet_75_60_45_40;
  bool	HLT_PFHT330PT30_QuadPFJet_75_60_45_40_TriplePFBTagDeepCSV_4p5;
  bool	HLT_PFHT350;
  bool	HLT_PFHT350MinPFJet15;
  bool	HLT_PFHT370;
  bool	HLT_PFHT400_SixPFJet32;
  bool	HLT_PFHT400_SixPFJet32_DoublePFBTagDeepCSV_2p94;
  bool	HLT_PFHT430;
  bool	HLT_PFHT450_SixPFJet36;
  bool	HLT_PFHT450_SixPFJet36_PFBTagDeepCSV_1p59;
  bool	HLT_PFHT500_PFMET100_PFMHT100_IDTight;
  bool	HLT_PFHT500_PFMET110_PFMHT110_IDTight;
  bool	HLT_PFHT510;
  bool	HLT_PFHT590;
  bool	HLT_PFHT680;
  bool	HLT_PFHT700_PFMET85_PFMHT85_IDTight;
  bool	HLT_PFHT700_PFMET95_PFMHT95_IDTight;
  bool	HLT_PFHT780;
  bool	HLT_PFHT800_PFMET75_PFMHT75_IDTight;
  bool	HLT_PFHT800_PFMET85_PFMHT85_IDTight;
  bool	HLT_PFHT890;
  bool	HLT_PFJet140;
  bool	HLT_PFJet15;
  bool	HLT_PFJet200;
  bool	HLT_PFJet25;
  bool	HLT_PFJet260;
  bool	HLT_PFJet320;
  bool	HLT_PFJet40;
  bool	HLT_PFJet400;
  bool	HLT_PFJet450;
  bool	HLT_PFJet500;
  bool	HLT_PFJet550;
  bool	HLT_PFJet60;
  bool	HLT_PFJet80;
  bool	HLT_PFJetFwd140;
  bool	HLT_PFJetFwd15;
  bool	HLT_PFJetFwd200;
  bool	HLT_PFJetFwd25;
  bool	HLT_PFJetFwd260;
  bool	HLT_PFJetFwd320;
  bool	HLT_PFJetFwd40;
  bool	HLT_PFJetFwd400;
  bool	HLT_PFJetFwd450;
  bool	HLT_PFJetFwd500;
  bool	HLT_PFJetFwd60;
  bool	HLT_PFJetFwd80;
  bool	HLT_PFMET100_PFMHT100_IDTight_CaloBTagDeepCSV_3p1;
  bool	HLT_PFMET100_PFMHT100_IDTight_PFHT60;
  bool	HLT_PFMET110_PFMHT110_IDTight;
  bool	HLT_PFMET110_PFMHT110_IDTight_CaloBTagDeepCSV_3p1;
  bool	HLT_PFMET120_PFMHT120_IDTight;
  bool	HLT_PFMET120_PFMHT120_IDTight_CaloBTagDeepCSV_3p1;
  bool	HLT_PFMET120_PFMHT120_IDTight_PFHT60;
  bool	HLT_PFMET130_PFMHT130_IDTight;
  bool	HLT_PFMET130_PFMHT130_IDTight_CaloBTagDeepCSV_3p1;
  bool	HLT_PFMET140_PFMHT140_IDTight;
  bool	HLT_PFMET140_PFMHT140_IDTight_CaloBTagDeepCSV_3p1;
  bool	HLT_PFMET200_HBHECleaned;
  bool	HLT_PFMET200_HBHE_BeamHaloCleaned;
  bool	HLT_PFMET200_NotCleaned;
  bool	HLT_PFMET250_HBHECleaned;
  bool	HLT_PFMET300_HBHECleaned;
  bool	HLT_PFMETNoMu100_PFMHTNoMu100_IDTight_PFHT60;
  bool	HLT_PFMETNoMu110_PFMHTNoMu110_IDTight;
  bool	HLT_PFMETNoMu120_PFMHTNoMu120_IDTight;
  bool	HLT_PFMETNoMu120_PFMHTNoMu120_IDTight_PFHT60;
  bool	HLT_PFMETNoMu130_PFMHTNoMu130_IDTight;
  bool	HLT_PFMETNoMu140_PFMHTNoMu140_IDTight;
  bool	HLT_PFMETTypeOne100_PFMHT100_IDTight_PFHT60;
  bool	HLT_PFMETTypeOne110_PFMHT110_IDTight;
  bool	HLT_PFMETTypeOne120_PFMHT120_IDTight;
  bool	HLT_PFMETTypeOne120_PFMHT120_IDTight_PFHT60;
  bool	HLT_PFMETTypeOne130_PFMHT130_IDTight;
  bool	HLT_PFMETTypeOne140_PFMHT140_IDTight;
  bool	HLT_PFMETTypeOne200_HBHE_BeamHaloCleaned;
  bool	HLT_Photon100EBHE10;
  bool	HLT_Photon100EB_TightID_TightIso;
  bool	HLT_Photon100EEHE10;
  bool	HLT_Photon100EE_TightID_TightIso;
  bool	HLT_Photon110EB_TightID_TightIso;
  bool	HLT_Photon120;
  bool	HLT_Photon120EB_TightID_TightIso;
  bool	HLT_Photon120_R9Id90_HE10_IsoM;
  bool	HLT_Photon150;
  bool	HLT_Photon165_R9Id90_HE10_IsoM;
  bool	HLT_Photon175;
  bool	HLT_Photon20;
  bool	HLT_Photon200;
  bool	HLT_Photon20_HoverELoose;
  bool	HLT_Photon300_NoHE;
  bool	HLT_Photon30_HoverELoose;
  bool	HLT_Photon33;
  bool	HLT_Photon35_TwoProngs35;
  bool	HLT_Photon50;
  bool	HLT_Photon50_R9Id90_HE10_IsoM;
  bool	HLT_Photon50_R9Id90_HE10_IsoM_EBOnly_PFJetsMJJ300DEta3_PFMET50;
  bool	HLT_Photon60_R9Id90_CaloIdL_IsoL;
  bool	HLT_Photon60_R9Id90_CaloIdL_IsoL_DisplacedIdL;
  bool	HLT_Photon60_R9Id90_CaloIdL_IsoL_DisplacedIdL_PFHT350MinPFJet15;
  bool	HLT_Photon75;
  bool	HLT_Photon75_R9Id90_HE10_IsoM;
  bool	HLT_Photon75_R9Id90_HE10_IsoM_EBOnly_CaloMJJ300_PFJetsMJJ400DEta3;
  bool	HLT_Photon75_R9Id90_HE10_IsoM_EBOnly_CaloMJJ400_PFJetsMJJ600DEta3;
  bool	HLT_Photon75_R9Id90_HE10_IsoM_EBOnly_PFJetsMJJ300DEta3;
  bool	HLT_Photon75_R9Id90_HE10_IsoM_EBOnly_PFJetsMJJ600DEta3;
  bool	HLT_Photon90;
  bool	HLT_Photon90_CaloIdL_PFHT700;
  bool	HLT_Photon90_R9Id90_HE10_IsoM;
  bool	HLT_Rsq0p35;
  bool	HLT_Rsq0p40;
  bool	HLT_RsqMR300_Rsq0p09_MR200;
  bool	HLT_RsqMR300_Rsq0p09_MR200_4jet;
  bool	HLT_RsqMR320_Rsq0p09_MR200;
  bool	HLT_RsqMR320_Rsq0p09_MR200_4jet;
  bool	HLT_SingleJet30_Mu12_SinglePFJet40;
  bool	HLT_SinglePhoton10_Eta3p1ForPPRef;
  bool	HLT_SinglePhoton20_Eta3p1ForPPRef;
  bool	HLT_SinglePhoton30_Eta3p1ForPPRef;
  bool	HLT_Tau3Mu_Mu7_Mu1_TkMu1_IsoTau15;
  bool	HLT_Tau3Mu_Mu7_Mu1_TkMu1_IsoTau15_Charge1;
  bool	HLT_Tau3Mu_Mu7_Mu1_TkMu1_Tau15;
  bool	HLT_Tau3Mu_Mu7_Mu1_TkMu1_Tau15_Charge1;
  bool	HLT_TkMu100;
  bool	HLT_Trimuon5_3p5_2_Upsilon_Muon;
  bool	HLT_TrimuonOpen_5_3p5_2_Upsilon_Muon;
  bool	HLT_TrkMu12_DoubleTrkMu5NoFiltersNoVtx;
  bool	HLT_TrkMu16NoFiltersNoVtx;
  bool	HLT_TrkMu16_DoubleTrkMu6NoFiltersNoVtx;
  bool	HLT_TrkMu17_DoubleTrkMu8NoFiltersNoVtx;
  bool	HLT_TrkMu6NoFiltersNoVtx;
  bool	HLTriggerFinalPath;
  bool	HLTriggerFirstPath;
  float	L1PreFiringWeight_Dn;
  float	L1PreFiringWeight_ECAL_Dn;
  float	L1PreFiringWeight_ECAL_Nom;
  float	L1PreFiringWeight_ECAL_Up;
  float	L1PreFiringWeight_Muon_Nom;
  float	L1PreFiringWeight_Muon_StatDn;
  float	L1PreFiringWeight_Muon_StatUp;
  float	L1PreFiringWeight_Muon_SystDn;
  float	L1PreFiringWeight_Muon_SystUp;
  float	L1PreFiringWeight_Nom;
  float	L1PreFiringWeight_Up;
  bool	L1Reco_step;
  bool	L1simulation_step;
  float	LHEWeight_originalXWGTUP;
  float	LHE_AlphaS;
  float	LHE_HT;
  float	LHE_HTIncoming;
  int	LHE_Nb;
  int	LHE_Nc;
  int	LHE_Nglu;
  int	LHE_Njets;
  int	LHE_NpLO;
  int	LHE_NpNLO;
  int	LHE_Nuds;
  float	LHE_Vpt;
  float	MET_MetUnclustEnUpDeltaX;
  float	MET_MetUnclustEnUpDeltaY;
  float	MET_T1Smear_phi;
  float	MET_T1Smear_phi_jerDown;
  float	MET_T1Smear_phi_jerUp;
  float	MET_T1Smear_phi_jesTotalDown;
  float	MET_T1Smear_phi_jesTotalUp;
  float	MET_T1Smear_phi_unclustEnDown;
  float	MET_T1Smear_phi_unclustEnUp;
  float	MET_T1Smear_pt;
  float	MET_T1Smear_pt_jerDown;
  float	MET_T1Smear_pt_jerUp;
  float	MET_T1Smear_pt_jesTotalDown;
  float	MET_T1Smear_pt_jesTotalUp;
  float	MET_T1Smear_pt_unclustEnDown;
  float	MET_T1Smear_pt_unclustEnUp;
  float	MET_T1_phi;
  float	MET_T1_phi_jerDown;
  float	MET_T1_phi_jerUp;
  float	MET_T1_phi_jesTotalDown;
  float	MET_T1_phi_jesTotalUp;
  float	MET_T1_phi_unclustEnDown;
  float	MET_T1_phi_unclustEnUp;
  float	MET_T1_pt;
  float	MET_T1_pt_jerDown;
  float	MET_T1_pt_jerUp;
  float	MET_T1_pt_jesTotalDown;
  float	MET_T1_pt_jesTotalUp;
  float	MET_T1_pt_unclustEnDown;
  float	MET_T1_pt_unclustEnUp;
  float	MET_covXX;
  float	MET_covXY;
  float	MET_covYY;
  float	MET_fiducialGenPhi;
  float	MET_fiducialGenPt;
  float	MET_phi;
  float	MET_pt;
  float	MET_significance;
  float	MET_sumEt;
  float	MET_sumPtUnclustered;
  float	PV_chi2;
  float	PV_ndof;
  int	PV_npvs;
  int	PV_npvsGood;
  float	PV_score;
  float	PV_x;
  float	PV_y;
  float	PV_z;
  float	Pileup_gpudensity;
  int	Pileup_nPU;
  float	Pileup_nTrueInt;
  float	Pileup_pudensity;
  int	Pileup_sumEOOT;
  int	Pileup_sumLOOT;
  float	PuppiMET_phi;
  float	PuppiMET_phiJERDown;
  float	PuppiMET_phiJERUp;
  float	PuppiMET_phiJESDown;
  float	PuppiMET_phiJESUp;
  float	PuppiMET_phiUnclusteredDown;
  float	PuppiMET_phiUnclusteredUp;
  float	PuppiMET_pt;
  float	PuppiMET_ptJERDown;
  float	PuppiMET_ptJERUp;
  float	PuppiMET_ptJESDown;
  float	PuppiMET_ptJESUp;
  float	PuppiMET_ptUnclusteredDown;
  float	PuppiMET_ptUnclusteredUp;
  float	PuppiMET_sumEt;
  float	RawMET_phi;
  float	RawMET_pt;
  float	RawMET_sumEt;
  float	RawPuppiMET_phi;
  float	RawPuppiMET_pt;
  float	RawPuppiMET_sumEt;
  float	TkMET_phi;
  float	TkMET_pt;
  float	TkMET_sumEt;
  float	btagWeight_CSVV2;
  float	btagWeight_DeepCSVB;
  long	event;
  double	eventWeight;
  float	fixedGridRhoFastjetAll;
  float	fixedGridRhoFastjetCentral;
  float	fixedGridRhoFastjetCentralCalo;
  float	fixedGridRhoFastjetCentralChargedPileUp;
  float	fixedGridRhoFastjetCentralNeutral;
  int	genTtbarId;
  float	genWeight;
  unsigned int	luminosityBlock;
  float	puWeight;
  float	puWeightDown;
  float	puWeightUp;
  unsigned int	run;

  std::vector<float>	LHEPdfWeight;
  std::vector<float>	LHEReweightingWeight;
  std::vector<float>	LHEScaleWeight;
};
struct eventBuffer : Event_s
{
  //--------------------------------------------------------------------------
  // --- Declare variables
  //--------------------------------------------------------------------------
  std::vector<float>	CorrT1METJet_area;
  std::vector<float>	CorrT1METJet_eta;
  std::vector<float>	CorrT1METJet_muonSubtrFactor;
  std::vector<float>	CorrT1METJet_phi;
  std::vector<float>	CorrT1METJet_rawPt;
  std::vector<int>	Electron_charge;
  std::vector<int>	Electron_cleanmask;
  std::vector<bool>	Electron_convVeto;
  std::vector<int>	Electron_cutBased;
  std::vector<bool>	Electron_cutBased_HEEP;
  std::vector<float>	Electron_dEscaleDown;
  std::vector<float>	Electron_dEscaleUp;
  std::vector<float>	Electron_dEsigmaDown;
  std::vector<float>	Electron_dEsigmaUp;
  std::vector<float>	Electron_deltaEtaSC;
  std::vector<float>	Electron_dr03EcalRecHitSumEt;
  std::vector<float>	Electron_dr03HcalDepth1TowerSumEt;
  std::vector<float>	Electron_dr03TkSumPt;
  std::vector<float>	Electron_dr03TkSumPtHEEP;
  std::vector<float>	Electron_dxy;
  std::vector<float>	Electron_dxyErr;
  std::vector<float>	Electron_dz;
  std::vector<float>	Electron_dzErr;
  std::vector<float>	Electron_eCorr;
  std::vector<float>	Electron_eInvMinusPInv;
  std::vector<float>	Electron_energyErr;
  std::vector<float>	Electron_eta;
  std::vector<int>	Electron_genPartFlav;
  std::vector<int>	Electron_genPartIdx;
  std::vector<float>	Electron_hoe;
  std::vector<float>	Electron_ip3d;
  std::vector<bool>	Electron_isPFcand;
  std::vector<int>	Electron_jetIdx;
  std::vector<int>	Electron_jetNDauCharged;
  std::vector<float>	Electron_jetPtRelv2;
  std::vector<float>	Electron_jetRelIso;
  std::vector<int>	Electron_lostHits;
  std::vector<float>	Electron_mass;
  std::vector<float>	Electron_miniPFRelIso_all;
  std::vector<float>	Electron_miniPFRelIso_chg;
  std::vector<float>	Electron_mvaFall17V2Iso;
  std::vector<bool>	Electron_mvaFall17V2Iso_WP80;
  std::vector<bool>	Electron_mvaFall17V2Iso_WP90;
  std::vector<bool>	Electron_mvaFall17V2Iso_WPL;
  std::vector<float>	Electron_mvaFall17V2noIso;
  std::vector<bool>	Electron_mvaFall17V2noIso_WP80;
  std::vector<bool>	Electron_mvaFall17V2noIso_WP90;
  std::vector<bool>	Electron_mvaFall17V2noIso_WPL;
  std::vector<float>	Electron_mvaTTH;
  std::vector<int>	Electron_pdgId;
  std::vector<float>	Electron_pfRelIso03_all;
  std::vector<float>	Electron_pfRelIso03_chg;
  std::vector<float>	Electron_phi;
  std::vector<int>	Electron_photonIdx;
  std::vector<float>	Electron_pt;
  std::vector<float>	Electron_r9;
  std::vector<float>	Electron_scEtOverPt;
  std::vector<int>	Electron_seedGain;
  std::vector<float>	Electron_sieie;
  std::vector<float>	Electron_sip3d;
  std::vector<int>	Electron_tightCharge;
  std::vector<int>	Electron_vidNestedWPBitmap;
  std::vector<int>	Electron_vidNestedWPBitmapHEEP;
  std::vector<float>	FatJet_area;
  std::vector<float>	FatJet_btagCSVV2;
  std::vector<float>	FatJet_btagDDBvLV2;
  std::vector<float>	FatJet_btagDDCvBV2;
  std::vector<float>	FatJet_btagDDCvLV2;
  std::vector<float>	FatJet_btagDeepB;
  std::vector<float>	FatJet_btagHbb;
  std::vector<float>	FatJet_corr_JEC;
  std::vector<float>	FatJet_corr_JER;
  std::vector<float>	FatJet_corr_JMR;
  std::vector<float>	FatJet_corr_JMS;
  std::vector<float>	FatJet_deepTagMD_H4qvsQCD;
  std::vector<float>	FatJet_deepTagMD_HbbvsQCD;
  std::vector<float>	FatJet_deepTagMD_TvsQCD;
  std::vector<float>	FatJet_deepTagMD_WvsQCD;
  std::vector<float>	FatJet_deepTagMD_ZHbbvsQCD;
  std::vector<float>	FatJet_deepTagMD_ZHccvsQCD;
  std::vector<float>	FatJet_deepTagMD_ZbbvsQCD;
  std::vector<float>	FatJet_deepTagMD_ZvsQCD;
  std::vector<float>	FatJet_deepTagMD_bbvsLight;
  std::vector<float>	FatJet_deepTagMD_ccvsLight;
  std::vector<float>	FatJet_deepTag_H;
  std::vector<float>	FatJet_deepTag_QCD;
  std::vector<float>	FatJet_deepTag_QCDothers;
  std::vector<float>	FatJet_deepTag_TvsQCD;
  std::vector<float>	FatJet_deepTag_WvsQCD;
  std::vector<float>	FatJet_deepTag_ZvsQCD;
  std::vector<int>	FatJet_electronIdx3SJ;
  std::vector<float>	FatJet_eta;
  std::vector<int>	FatJet_genJetAK8Idx;
  std::vector<int>	FatJet_hadronFlavour;
  std::vector<int>	FatJet_jetId;
  std::vector<float>	FatJet_lsf3;
  std::vector<float>	FatJet_mass;
  std::vector<float>	FatJet_mass_jerDown;
  std::vector<float>	FatJet_mass_jerUp;
  std::vector<float>	FatJet_mass_jesTotalDown;
  std::vector<float>	FatJet_mass_jesTotalUp;
  std::vector<float>	FatJet_mass_jmrDown;
  std::vector<float>	FatJet_mass_jmrUp;
  std::vector<float>	FatJet_mass_jmsDown;
  std::vector<float>	FatJet_mass_jmsUp;
  std::vector<float>	FatJet_mass_nom;
  std::vector<float>	FatJet_mass_raw;
  std::vector<float>	FatJet_msoftdrop;
  std::vector<float>	FatJet_msoftdrop_corr_JMR;
  std::vector<float>	FatJet_msoftdrop_corr_JMS;
  std::vector<float>	FatJet_msoftdrop_corr_PUPPI;
  std::vector<float>	FatJet_msoftdrop_jerDown;
  std::vector<float>	FatJet_msoftdrop_jerUp;
  std::vector<float>	FatJet_msoftdrop_jesTotalDown;
  std::vector<float>	FatJet_msoftdrop_jesTotalUp;
  std::vector<float>	FatJet_msoftdrop_jmrDown;
  std::vector<float>	FatJet_msoftdrop_jmrUp;
  std::vector<float>	FatJet_msoftdrop_jmsDown;
  std::vector<float>	FatJet_msoftdrop_jmsUp;
  std::vector<float>	FatJet_msoftdrop_nom;
  std::vector<float>	FatJet_msoftdrop_raw;
  std::vector<float>	FatJet_msoftdrop_tau21DDT_jerDown;
  std::vector<float>	FatJet_msoftdrop_tau21DDT_jerUp;
  std::vector<float>	FatJet_msoftdrop_tau21DDT_jmrDown;
  std::vector<float>	FatJet_msoftdrop_tau21DDT_jmrUp;
  std::vector<float>	FatJet_msoftdrop_tau21DDT_jmsDown;
  std::vector<float>	FatJet_msoftdrop_tau21DDT_jmsUp;
  std::vector<float>	FatJet_msoftdrop_tau21DDT_nom;
  std::vector<int>	FatJet_muonIdx3SJ;
  std::vector<float>	FatJet_n2b1;
  std::vector<float>	FatJet_n3b1;
  std::vector<int>	FatJet_nBHadrons;
  std::vector<int>	FatJet_nCHadrons;
  std::vector<int>	FatJet_nConstituents;
  std::vector<float>	FatJet_particleNetMD_QCD;
  std::vector<float>	FatJet_particleNetMD_Xbb;
  std::vector<float>	FatJet_particleNetMD_Xcc;
  std::vector<float>	FatJet_particleNetMD_Xqq;
  std::vector<float>	FatJet_particleNet_H4qvsQCD;
  std::vector<float>	FatJet_particleNet_HbbvsQCD;
  std::vector<float>	FatJet_particleNet_HccvsQCD;
  std::vector<float>	FatJet_particleNet_QCD;
  std::vector<float>	FatJet_particleNet_TvsQCD;
  std::vector<float>	FatJet_particleNet_WvsQCD;
  std::vector<float>	FatJet_particleNet_ZvsQCD;
  std::vector<float>	FatJet_particleNet_mass;
  std::vector<float>	FatJet_phi;
  std::vector<float>	FatJet_pt;
  std::vector<float>	FatJet_pt_jerDown;
  std::vector<float>	FatJet_pt_jerUp;
  std::vector<float>	FatJet_pt_jesTotalDown;
  std::vector<float>	FatJet_pt_jesTotalUp;
  std::vector<float>	FatJet_pt_nom;
  std::vector<float>	FatJet_pt_raw;
  std::vector<float>	FatJet_rawFactor;
  std::vector<int>	FatJet_subJetIdx1;
  std::vector<int>	FatJet_subJetIdx2;
  std::vector<float>	FatJet_tau1;
  std::vector<float>	FatJet_tau2;
  std::vector<float>	FatJet_tau3;
  std::vector<float>	FatJet_tau4;
  std::vector<float>	FsrPhoton_dROverEt2;
  std::vector<float>	FsrPhoton_eta;
  std::vector<int>	FsrPhoton_muonIdx;
  std::vector<float>	FsrPhoton_phi;
  std::vector<float>	FsrPhoton_pt;
  std::vector<float>	FsrPhoton_relIso03;
  std::vector<float>	GenIsolatedPhoton_eta;
  std::vector<float>	GenIsolatedPhoton_mass;
  std::vector<float>	GenIsolatedPhoton_phi;
  std::vector<float>	GenIsolatedPhoton_pt;
  std::vector<float>	GenJetAK8_eta;
  std::vector<int>	GenJetAK8_hadronFlavour;
  std::vector<float>	GenJetAK8_mass;
  std::vector<int>	GenJetAK8_partonFlavour;
  std::vector<float>	GenJetAK8_phi;
  std::vector<float>	GenJetAK8_pt;
  std::vector<float>	GenJet_eta;
  std::vector<int>	GenJet_hadronFlavour;
  std::vector<float>	GenJet_mass;
  std::vector<int>	GenJet_partonFlavour;
  std::vector<float>	GenJet_phi;
  std::vector<float>	GenJet_pt;
  std::vector<float>	GenPart_eta;
  std::vector<int>	GenPart_genPartIdxMother;
  std::vector<float>	GenPart_mass;
  std::vector<int>	GenPart_pdgId;
  std::vector<float>	GenPart_phi;
  std::vector<float>	GenPart_pt;
  std::vector<int>	GenPart_status;
  std::vector<int>	GenPart_statusFlags;
  std::vector<int>	IsoTrack_charge;
  std::vector<float>	IsoTrack_dxy;
  std::vector<float>	IsoTrack_dz;
  std::vector<float>	IsoTrack_eta;
  std::vector<int>	IsoTrack_fromPV;
  std::vector<bool>	IsoTrack_isFromLostTrack;
  std::vector<bool>	IsoTrack_isHighPurityTrack;
  std::vector<bool>	IsoTrack_isPFcand;
  std::vector<float>	IsoTrack_miniPFRelIso_all;
  std::vector<float>	IsoTrack_miniPFRelIso_chg;
  std::vector<int>	IsoTrack_pdgId;
  std::vector<float>	IsoTrack_pfRelIso03_all;
  std::vector<float>	IsoTrack_pfRelIso03_chg;
  std::vector<float>	IsoTrack_phi;
  std::vector<float>	IsoTrack_pt;
  std::vector<float>	Jet_area;
  std::vector<float>	Jet_bRegCorr;
  std::vector<float>	Jet_bRegRes;
  std::vector<float>	Jet_btagCSVV2;
  std::vector<float>	Jet_btagDeepB;
  std::vector<float>	Jet_btagDeepCvB;
  std::vector<float>	Jet_btagDeepCvL;
  std::vector<float>	Jet_btagDeepFlavB;
  std::vector<float>	Jet_btagDeepFlavCvB;
  std::vector<float>	Jet_btagDeepFlavCvL;
  std::vector<float>	Jet_btagDeepFlavQG;
  std::vector<float>	Jet_cRegCorr;
  std::vector<float>	Jet_cRegRes;
  std::vector<float>	Jet_chEmEF;
  std::vector<float>	Jet_chFPV0EF;
  std::vector<float>	Jet_chHEF;
  std::vector<int>	Jet_cleanmask;
  std::vector<float>	Jet_corr_JEC;
  std::vector<float>	Jet_corr_JER;
  std::vector<int>	Jet_electronIdx1;
  std::vector<int>	Jet_electronIdx2;
  std::vector<float>	Jet_eta;
  std::vector<int>	Jet_genJetIdx;
  std::vector<int>	Jet_hadronFlavour;
  std::vector<int>	Jet_hfadjacentEtaStripsSize;
  std::vector<int>	Jet_hfcentralEtaStripSize;
  std::vector<float>	Jet_hfsigmaEtaEta;
  std::vector<float>	Jet_hfsigmaPhiPhi;
  std::vector<int>	Jet_jetId;
  std::vector<float>	Jet_mass;
  std::vector<float>	Jet_mass_jerDown;
  std::vector<float>	Jet_mass_jerUp;
  std::vector<float>	Jet_mass_jesTotalDown;
  std::vector<float>	Jet_mass_jesTotalUp;
  std::vector<float>	Jet_mass_nom;
  std::vector<float>	Jet_mass_raw;
  std::vector<float>	Jet_muEF;
  std::vector<int>	Jet_muonIdx1;
  std::vector<int>	Jet_muonIdx2;
  std::vector<float>	Jet_muonSubtrFactor;
  std::vector<int>	Jet_nConstituents;
  std::vector<int>	Jet_nElectrons;
  std::vector<int>	Jet_nMuons;
  std::vector<float>	Jet_neEmEF;
  std::vector<float>	Jet_neHEF;
  std::vector<int>	Jet_partonFlavour;
  std::vector<float>	Jet_phi;
  std::vector<float>	Jet_pt;
  std::vector<float>	Jet_pt_jerDown;
  std::vector<float>	Jet_pt_jerUp;
  std::vector<float>	Jet_pt_jesTotalDown;
  std::vector<float>	Jet_pt_jesTotalUp;
  std::vector<float>	Jet_pt_nom;
  std::vector<float>	Jet_pt_raw;
  std::vector<int>	Jet_puId;
  std::vector<float>	Jet_puIdDisc;
  std::vector<float>	Jet_qgl;
  std::vector<float>	Jet_rawFactor;
  std::vector<float>	LHEPart_eta;
  std::vector<float>	LHEPart_incomingpz;
  std::vector<float>	LHEPart_mass;
  std::vector<int>	LHEPart_pdgId;
  std::vector<float>	LHEPart_phi;
  std::vector<float>	LHEPart_pt;
  std::vector<int>	LHEPart_spin;
  std::vector<int>	LHEPart_status;
  std::vector<int>	Muon_charge;
  std::vector<int>	Muon_cleanmask;
  std::vector<float>	Muon_dxy;
  std::vector<float>	Muon_dxyErr;
  std::vector<float>	Muon_dxybs;
  std::vector<float>	Muon_dz;
  std::vector<float>	Muon_dzErr;
  std::vector<float>	Muon_eta;
  std::vector<int>	Muon_fsrPhotonIdx;
  std::vector<int>	Muon_genPartFlav;
  std::vector<int>	Muon_genPartIdx;
  std::vector<int>	Muon_highPtId;
  std::vector<bool>	Muon_highPurity;
  std::vector<bool>	Muon_inTimeMuon;
  std::vector<float>	Muon_ip3d;
  std::vector<bool>	Muon_isGlobal;
  std::vector<bool>	Muon_isPFcand;
  std::vector<bool>	Muon_isStandalone;
  std::vector<bool>	Muon_isTracker;
  std::vector<int>	Muon_jetIdx;
  std::vector<int>	Muon_jetNDauCharged;
  std::vector<float>	Muon_jetPtRelv2;
  std::vector<float>	Muon_jetRelIso;
  std::vector<bool>	Muon_looseId;
  std::vector<float>	Muon_mass;
  std::vector<bool>	Muon_mediumId;
  std::vector<bool>	Muon_mediumPromptId;
  std::vector<int>	Muon_miniIsoId;
  std::vector<float>	Muon_miniPFRelIso_all;
  std::vector<float>	Muon_miniPFRelIso_chg;
  std::vector<int>	Muon_multiIsoId;
  std::vector<int>	Muon_mvaId;
  std::vector<float>	Muon_mvaLowPt;
  std::vector<int>	Muon_mvaLowPtId;
  std::vector<float>	Muon_mvaTTH;
  std::vector<int>	Muon_nStations;
  std::vector<int>	Muon_nTrackerLayers;
  std::vector<int>	Muon_pdgId;
  std::vector<int>	Muon_pfIsoId;
  std::vector<float>	Muon_pfRelIso03_all;
  std::vector<float>	Muon_pfRelIso03_chg;
  std::vector<float>	Muon_pfRelIso04_all;
  std::vector<float>	Muon_phi;
  std::vector<float>	Muon_pt;
  std::vector<float>	Muon_ptErr;
  std::vector<int>	Muon_puppiIsoId;
  std::vector<float>	Muon_segmentComp;
  std::vector<float>	Muon_sip3d;
  std::vector<bool>	Muon_softId;
  std::vector<float>	Muon_softMva;
  std::vector<bool>	Muon_softMvaId;
  std::vector<int>	Muon_tightCharge;
  std::vector<bool>	Muon_tightId;
  std::vector<int>	Muon_tkIsoId;
  std::vector<float>	Muon_tkRelIso;
  std::vector<bool>	Muon_triggerIdLoose;
  std::vector<float>	Muon_tunepRelPt;
  std::vector<float>	OtherPV_z;
  std::vector<float>	PSWeight;
  std::vector<int>	Photon_charge;
  std::vector<int>	Photon_cleanmask;
  std::vector<int>	Photon_cutBased;
  std::vector<int>	Photon_cutBased_Fall17V1Bitmap;
  std::vector<float>	Photon_dEscaleDown;
  std::vector<float>	Photon_dEscaleUp;
  std::vector<float>	Photon_dEsigmaDown;
  std::vector<float>	Photon_dEsigmaUp;
  std::vector<float>	Photon_eCorr;
  std::vector<int>	Photon_electronIdx;
  std::vector<bool>	Photon_electronVeto;
  std::vector<float>	Photon_energyErr;
  std::vector<float>	Photon_eta;
  std::vector<int>	Photon_genPartFlav;
  std::vector<int>	Photon_genPartIdx;
  std::vector<float>	Photon_hoe;
  std::vector<bool>	Photon_isScEtaEB;
  std::vector<bool>	Photon_isScEtaEE;
  std::vector<int>	Photon_jetIdx;
  std::vector<float>	Photon_mass;
  std::vector<float>	Photon_mvaID;
  std::vector<float>	Photon_mvaID_Fall17V1p1;
  std::vector<bool>	Photon_mvaID_WP80;
  std::vector<bool>	Photon_mvaID_WP90;
  std::vector<int>	Photon_pdgId;
  std::vector<float>	Photon_pfRelIso03_all;
  std::vector<float>	Photon_pfRelIso03_chg;
  std::vector<float>	Photon_phi;
  std::vector<bool>	Photon_pixelSeed;
  std::vector<float>	Photon_pt;
  std::vector<float>	Photon_r9;
  std::vector<int>	Photon_seedGain;
  std::vector<float>	Photon_sieie;
  std::vector<int>	Photon_vidNestedWPBitmap;
  std::vector<float>	SubGenJetAK8_eta;
  std::vector<float>	SubGenJetAK8_mass;
  std::vector<float>	SubGenJetAK8_phi;
  std::vector<float>	SubGenJetAK8_pt;
  std::vector<float>	SubJet_btagCSVV2;
  std::vector<float>	SubJet_btagDeepB;
  std::vector<float>	SubJet_eta;
  std::vector<int>	SubJet_hadronFlavour;
  std::vector<float>	SubJet_mass;
  std::vector<float>	SubJet_n2b1;
  std::vector<float>	SubJet_n3b1;
  std::vector<int>	SubJet_nBHadrons;
  std::vector<int>	SubJet_nCHadrons;
  std::vector<float>	SubJet_phi;
  std::vector<float>	SubJet_pt;
  std::vector<float>	SubJet_rawFactor;
  std::vector<float>	SubJet_tau1;
  std::vector<float>	SubJet_tau2;
  std::vector<float>	SubJet_tau3;
  std::vector<float>	SubJet_tau4;
  std::vector<int>	Tau_charge;
  std::vector<float>	Tau_chargedIso;
  std::vector<int>	Tau_cleanmask;
  std::vector<int>	Tau_decayMode;
  std::vector<float>	Tau_dxy;
  std::vector<float>	Tau_dz;
  std::vector<float>	Tau_eta;
  std::vector<int>	Tau_genPartFlav;
  std::vector<int>	Tau_genPartIdx;
  std::vector<bool>	Tau_idAntiEleDeadECal;
  std::vector<int>	Tau_idAntiMu;
  std::vector<bool>	Tau_idDecayModeOldDMs;
  std::vector<int>	Tau_idDeepTau2017v2p1VSe;
  std::vector<int>	Tau_idDeepTau2017v2p1VSjet;
  std::vector<int>	Tau_idDeepTau2017v2p1VSmu;
  std::vector<int>	Tau_jetIdx;
  std::vector<float>	Tau_leadTkDeltaEta;
  std::vector<float>	Tau_leadTkDeltaPhi;
  std::vector<float>	Tau_leadTkPtOverTauPt;
  std::vector<float>	Tau_mass;
  std::vector<float>	Tau_neutralIso;
  std::vector<float>	Tau_phi;
  std::vector<float>	Tau_photonsOutsideSignalCone;
  std::vector<float>	Tau_pt;
  std::vector<float>	Tau_puCorr;
  std::vector<float>	Tau_rawDeepTau2017v2p1VSe;
  std::vector<float>	Tau_rawDeepTau2017v2p1VSjet;
  std::vector<float>	Tau_rawDeepTau2017v2p1VSmu;
  std::vector<float>	Tau_rawIso;
  std::vector<float>	Tau_rawIsodR03;
  std::vector<float>	TrigObj_eta;
  std::vector<int>	TrigObj_filterBits;
  std::vector<int>	TrigObj_id;
  std::vector<int>	TrigObj_l1charge;
  std::vector<int>	TrigObj_l1iso;
  std::vector<float>	TrigObj_l1pt;
  std::vector<float>	TrigObj_l1pt_2;
  std::vector<float>	TrigObj_l2pt;
  std::vector<float>	TrigObj_phi;
  std::vector<float>	TrigObj_pt;
  std::vector<int>	boostedTau_charge;
  std::vector<float>	boostedTau_chargedIso;
  std::vector<int>	boostedTau_decayMode;
  std::vector<float>	boostedTau_eta;
  std::vector<int>	boostedTau_genPartFlav;
  std::vector<int>	boostedTau_genPartIdx;
  std::vector<int>	boostedTau_idAntiEle2018;
  std::vector<int>	boostedTau_idAntiMu;
  std::vector<int>	boostedTau_idMVAnewDM2017v2;
  std::vector<int>	boostedTau_idMVAoldDM2017v2;
  std::vector<int>	boostedTau_idMVAoldDMdR032017v2;
  std::vector<int>	boostedTau_jetIdx;
  std::vector<float>	boostedTau_leadTkDeltaEta;
  std::vector<float>	boostedTau_leadTkDeltaPhi;
  std::vector<float>	boostedTau_leadTkPtOverTauPt;
  std::vector<float>	boostedTau_mass;
  std::vector<float>	boostedTau_neutralIso;
  std::vector<float>	boostedTau_phi;
  std::vector<float>	boostedTau_photonsOutsideSignalCone;
  std::vector<float>	boostedTau_pt;
  std::vector<float>	boostedTau_puCorr;
  std::vector<float>	boostedTau_rawAntiEle2018;
  std::vector<int>	boostedTau_rawAntiEleCat2018;
  std::vector<float>	boostedTau_rawIso;
  std::vector<float>	boostedTau_rawIsodR03;
  std::vector<float>	boostedTau_rawMVAnewDM2017v2;
  std::vector<float>	boostedTau_rawMVAoldDM2017v2;
  std::vector<float>	boostedTau_rawMVAoldDMdR032017v2;

  //--------------------------------------------------------------------------
  // --- Structs can be filled by calling fill(), or individual fill
  // --- methods, e.g., fillElectrons()
  // --- after the call to read(...)
  //----------- --------------------------------------------------------------
  struct CorrT1METJet_s
  {
    float	area;
    float	eta;
    float	muonSubtrFactor;
    float	phi;
    float	rawPt;

    std::ostream& operator<<(std::ostream& os)
    {
      char r[1024];
      os << "CorrT1METJet" << std::endl;
      sprintf(r, "  %-32s: %f\n", "area", ( double)area); os << r;
      sprintf(r, "  %-32s: %f\n", "eta", ( double)eta); os << r;
      sprintf(r, "  %-32s: %f\n", "muonSubtrFactor", ( double)muonSubtrFactor); os << r;
      sprintf(r, "  %-32s: %f\n", "phi", ( double)phi); os << r;
      sprintf(r, "  %-32s: %f\n", "rawPt", ( double)rawPt); os << r;
      return os;
    }
  };

  struct Electron_s
  {
    int	charge;
    int	cleanmask;
    bool	convVeto;
    int	cutBased;
    bool	cutBased_HEEP;
    float	dEscaleDown;
    float	dEscaleUp;
    float	dEsigmaDown;
    float	dEsigmaUp;
    float	deltaEtaSC;
    float	dr03EcalRecHitSumEt;
    float	dr03HcalDepth1TowerSumEt;
    float	dr03TkSumPt;
    float	dr03TkSumPtHEEP;
    float	dxy;
    float	dxyErr;
    float	dz;
    float	dzErr;
    float	eCorr;
    float	eInvMinusPInv;
    float	energyErr;
    float	eta;
    int	genPartFlav;
    int	genPartIdx;
    float	hoe;
    float	ip3d;
    bool	isPFcand;
    int	jetIdx;
    int	jetNDauCharged;
    float	jetPtRelv2;
    float	jetRelIso;
    int	lostHits;
    float	mass;
    float	miniPFRelIso_all;
    float	miniPFRelIso_chg;
    float	mvaFall17V2Iso;
    bool	mvaFall17V2Iso_WP80;
    bool	mvaFall17V2Iso_WP90;
    bool	mvaFall17V2Iso_WPL;
    float	mvaFall17V2noIso;
    bool	mvaFall17V2noIso_WP80;
    bool	mvaFall17V2noIso_WP90;
    bool	mvaFall17V2noIso_WPL;
    float	mvaTTH;
    int	pdgId;
    float	pfRelIso03_all;
    float	pfRelIso03_chg;
    float	phi;
    int	photonIdx;
    float	pt;
    float	r9;
    float	scEtOverPt;
    int	seedGain;
    float	sieie;
    float	sip3d;
    int	tightCharge;
    int	vidNestedWPBitmap;
    int	vidNestedWPBitmapHEEP;

    std::ostream& operator<<(std::ostream& os)
    {
      char r[1024];
      os << "Electron" << std::endl;
      sprintf(r, "  %-32s: %f\n", "charge", ( double)charge); os << r;
      sprintf(r, "  %-32s: %f\n", "cleanmask", ( double)cleanmask); os << r;
      sprintf(r, "  %-32s: %f\n", "convVeto", ( double)convVeto); os << r;
      sprintf(r, "  %-32s: %f\n", "cutBased", ( double)cutBased); os << r;
      sprintf(r, "  %-32s: %f\n", "cutBased_HEEP", ( double)cutBased_HEEP); os << r;
      sprintf(r, "  %-32s: %f\n", "dEscaleDown", ( double)dEscaleDown); os << r;
      sprintf(r, "  %-32s: %f\n", "dEscaleUp", ( double)dEscaleUp); os << r;
      sprintf(r, "  %-32s: %f\n", "dEsigmaDown", ( double)dEsigmaDown); os << r;
      sprintf(r, "  %-32s: %f\n", "dEsigmaUp", ( double)dEsigmaUp); os << r;
      sprintf(r, "  %-32s: %f\n", "deltaEtaSC", ( double)deltaEtaSC); os << r;
      sprintf(r, "  %-32s: %f\n", "dr03EcalRecHitSumEt", ( double)dr03EcalRecHitSumEt); os << r;
      sprintf(r, "  %-32s: %f\n", "dr03HcalDepth1TowerSumEt", ( double)dr03HcalDepth1TowerSumEt); os << r;
      sprintf(r, "  %-32s: %f\n", "dr03TkSumPt", ( double)dr03TkSumPt); os << r;
      sprintf(r, "  %-32s: %f\n", "dr03TkSumPtHEEP", ( double)dr03TkSumPtHEEP); os << r;
      sprintf(r, "  %-32s: %f\n", "dxy", ( double)dxy); os << r;
      sprintf(r, "  %-32s: %f\n", "dxyErr", ( double)dxyErr); os << r;
      sprintf(r, "  %-32s: %f\n", "dz", ( double)dz); os << r;
      sprintf(r, "  %-32s: %f\n", "dzErr", ( double)dzErr); os << r;
      sprintf(r, "  %-32s: %f\n", "eCorr", ( double)eCorr); os << r;
      sprintf(r, "  %-32s: %f\n", "eInvMinusPInv", ( double)eInvMinusPInv); os << r;
      sprintf(r, "  %-32s: %f\n", "energyErr", ( double)energyErr); os << r;
      sprintf(r, "  %-32s: %f\n", "eta", ( double)eta); os << r;
      sprintf(r, "  %-32s: %f\n", "genPartFlav", ( double)genPartFlav); os << r;
      sprintf(r, "  %-32s: %f\n", "genPartIdx", ( double)genPartIdx); os << r;
      sprintf(r, "  %-32s: %f\n", "hoe", ( double)hoe); os << r;
      sprintf(r, "  %-32s: %f\n", "ip3d", ( double)ip3d); os << r;
      sprintf(r, "  %-32s: %f\n", "isPFcand", ( double)isPFcand); os << r;
      sprintf(r, "  %-32s: %f\n", "jetIdx", ( double)jetIdx); os << r;
      sprintf(r, "  %-32s: %f\n", "jetNDauCharged", ( double)jetNDauCharged); os << r;
      sprintf(r, "  %-32s: %f\n", "jetPtRelv2", ( double)jetPtRelv2); os << r;
      sprintf(r, "  %-32s: %f\n", "jetRelIso", ( double)jetRelIso); os << r;
      sprintf(r, "  %-32s: %f\n", "lostHits", ( double)lostHits); os << r;
      sprintf(r, "  %-32s: %f\n", "mass", ( double)mass); os << r;
      sprintf(r, "  %-32s: %f\n", "miniPFRelIso_all", ( double)miniPFRelIso_all); os << r;
      sprintf(r, "  %-32s: %f\n", "miniPFRelIso_chg", ( double)miniPFRelIso_chg); os << r;
      sprintf(r, "  %-32s: %f\n", "mvaFall17V2Iso", ( double)mvaFall17V2Iso); os << r;
      sprintf(r, "  %-32s: %f\n", "mvaFall17V2Iso_WP80", ( double)mvaFall17V2Iso_WP80); os << r;
      sprintf(r, "  %-32s: %f\n", "mvaFall17V2Iso_WP90", ( double)mvaFall17V2Iso_WP90); os << r;
      sprintf(r, "  %-32s: %f\n", "mvaFall17V2Iso_WPL", ( double)mvaFall17V2Iso_WPL); os << r;
      sprintf(r, "  %-32s: %f\n", "mvaFall17V2noIso", ( double)mvaFall17V2noIso); os << r;
      sprintf(r, "  %-32s: %f\n", "mvaFall17V2noIso_WP80", ( double)mvaFall17V2noIso_WP80); os << r;
      sprintf(r, "  %-32s: %f\n", "mvaFall17V2noIso_WP90", ( double)mvaFall17V2noIso_WP90); os << r;
      sprintf(r, "  %-32s: %f\n", "mvaFall17V2noIso_WPL", ( double)mvaFall17V2noIso_WPL); os << r;
      sprintf(r, "  %-32s: %f\n", "mvaTTH", ( double)mvaTTH); os << r;
      sprintf(r, "  %-32s: %f\n", "pdgId", ( double)pdgId); os << r;
      sprintf(r, "  %-32s: %f\n", "pfRelIso03_all", ( double)pfRelIso03_all); os << r;
      sprintf(r, "  %-32s: %f\n", "pfRelIso03_chg", ( double)pfRelIso03_chg); os << r;
      sprintf(r, "  %-32s: %f\n", "phi", ( double)phi); os << r;
      sprintf(r, "  %-32s: %f\n", "photonIdx", ( double)photonIdx); os << r;
      sprintf(r, "  %-32s: %f\n", "pt", ( double)pt); os << r;
      sprintf(r, "  %-32s: %f\n", "r9", ( double)r9); os << r;
      sprintf(r, "  %-32s: %f\n", "scEtOverPt", ( double)scEtOverPt); os << r;
      sprintf(r, "  %-32s: %f\n", "seedGain", ( double)seedGain); os << r;
      sprintf(r, "  %-32s: %f\n", "sieie", ( double)sieie); os << r;
      sprintf(r, "  %-32s: %f\n", "sip3d", ( double)sip3d); os << r;
      sprintf(r, "  %-32s: %f\n", "tightCharge", ( double)tightCharge); os << r;
      sprintf(r, "  %-32s: %f\n", "vidNestedWPBitmap", ( double)vidNestedWPBitmap); os << r;
      sprintf(r, "  %-32s: %f\n", "vidNestedWPBitmapHEEP", ( double)vidNestedWPBitmapHEEP); os << r;
      return os;
    }
  };

  struct FatJet_s
  {
    float	area;
    float	btagCSVV2;
    float	btagDDBvLV2;
    float	btagDDCvBV2;
    float	btagDDCvLV2;
    float	btagDeepB;
    float	btagHbb;
    float	corr_JEC;
    float	corr_JER;
    float	corr_JMR;
    float	corr_JMS;
    float	deepTagMD_H4qvsQCD;
    float	deepTagMD_HbbvsQCD;
    float	deepTagMD_TvsQCD;
    float	deepTagMD_WvsQCD;
    float	deepTagMD_ZHbbvsQCD;
    float	deepTagMD_ZHccvsQCD;
    float	deepTagMD_ZbbvsQCD;
    float	deepTagMD_ZvsQCD;
    float	deepTagMD_bbvsLight;
    float	deepTagMD_ccvsLight;
    float	deepTag_H;
    float	deepTag_QCD;
    float	deepTag_QCDothers;
    float	deepTag_TvsQCD;
    float	deepTag_WvsQCD;
    float	deepTag_ZvsQCD;
    int	electronIdx3SJ;
    float	eta;
    int	genJetAK8Idx;
    int	hadronFlavour;
    int	jetId;
    float	lsf3;
    float	mass;
    float	mass_jerDown;
    float	mass_jerUp;
    float	mass_jesTotalDown;
    float	mass_jesTotalUp;
    float	mass_jmrDown;
    float	mass_jmrUp;
    float	mass_jmsDown;
    float	mass_jmsUp;
    float	mass_nom;
    float	mass_raw;
    float	msoftdrop;
    float	msoftdrop_corr_JMR;
    float	msoftdrop_corr_JMS;
    float	msoftdrop_corr_PUPPI;
    float	msoftdrop_jerDown;
    float	msoftdrop_jerUp;
    float	msoftdrop_jesTotalDown;
    float	msoftdrop_jesTotalUp;
    float	msoftdrop_jmrDown;
    float	msoftdrop_jmrUp;
    float	msoftdrop_jmsDown;
    float	msoftdrop_jmsUp;
    float	msoftdrop_nom;
    float	msoftdrop_raw;
    float	msoftdrop_tau21DDT_jerDown;
    float	msoftdrop_tau21DDT_jerUp;
    float	msoftdrop_tau21DDT_jmrDown;
    float	msoftdrop_tau21DDT_jmrUp;
    float	msoftdrop_tau21DDT_jmsDown;
    float	msoftdrop_tau21DDT_jmsUp;
    float	msoftdrop_tau21DDT_nom;
    int	muonIdx3SJ;
    float	n2b1;
    float	n3b1;
    int	nBHadrons;
    int	nCHadrons;
    int	nConstituents;
    float	particleNetMD_QCD;
    float	particleNetMD_Xbb;
    float	particleNetMD_Xcc;
    float	particleNetMD_Xqq;
    float	particleNet_H4qvsQCD;
    float	particleNet_HbbvsQCD;
    float	particleNet_HccvsQCD;
    float	particleNet_QCD;
    float	particleNet_TvsQCD;
    float	particleNet_WvsQCD;
    float	particleNet_ZvsQCD;
    float	particleNet_mass;
    float	phi;
    float	pt;
    float	pt_jerDown;
    float	pt_jerUp;
    float	pt_jesTotalDown;
    float	pt_jesTotalUp;
    float	pt_nom;
    float	pt_raw;
    float	rawFactor;
    int	subJetIdx1;
    int	subJetIdx2;
    float	tau1;
    float	tau2;
    float	tau3;
    float	tau4;

    std::ostream& operator<<(std::ostream& os)
    {
      char r[1024];
      os << "FatJet" << std::endl;
      sprintf(r, "  %-32s: %f\n", "area", ( double)area); os << r;
      sprintf(r, "  %-32s: %f\n", "btagCSVV2", ( double)btagCSVV2); os << r;
      sprintf(r, "  %-32s: %f\n", "btagDDBvLV2", ( double)btagDDBvLV2); os << r;
      sprintf(r, "  %-32s: %f\n", "btagDDCvBV2", ( double)btagDDCvBV2); os << r;
      sprintf(r, "  %-32s: %f\n", "btagDDCvLV2", ( double)btagDDCvLV2); os << r;
      sprintf(r, "  %-32s: %f\n", "btagDeepB", ( double)btagDeepB); os << r;
      sprintf(r, "  %-32s: %f\n", "btagHbb", ( double)btagHbb); os << r;
      sprintf(r, "  %-32s: %f\n", "corr_JEC", ( double)corr_JEC); os << r;
      sprintf(r, "  %-32s: %f\n", "corr_JER", ( double)corr_JER); os << r;
      sprintf(r, "  %-32s: %f\n", "corr_JMR", ( double)corr_JMR); os << r;
      sprintf(r, "  %-32s: %f\n", "corr_JMS", ( double)corr_JMS); os << r;
      sprintf(r, "  %-32s: %f\n", "deepTagMD_H4qvsQCD", ( double)deepTagMD_H4qvsQCD); os << r;
      sprintf(r, "  %-32s: %f\n", "deepTagMD_HbbvsQCD", ( double)deepTagMD_HbbvsQCD); os << r;
      sprintf(r, "  %-32s: %f\n", "deepTagMD_TvsQCD", ( double)deepTagMD_TvsQCD); os << r;
      sprintf(r, "  %-32s: %f\n", "deepTagMD_WvsQCD", ( double)deepTagMD_WvsQCD); os << r;
      sprintf(r, "  %-32s: %f\n", "deepTagMD_ZHbbvsQCD", ( double)deepTagMD_ZHbbvsQCD); os << r;
      sprintf(r, "  %-32s: %f\n", "deepTagMD_ZHccvsQCD", ( double)deepTagMD_ZHccvsQCD); os << r;
      sprintf(r, "  %-32s: %f\n", "deepTagMD_ZbbvsQCD", ( double)deepTagMD_ZbbvsQCD); os << r;
      sprintf(r, "  %-32s: %f\n", "deepTagMD_ZvsQCD", ( double)deepTagMD_ZvsQCD); os << r;
      sprintf(r, "  %-32s: %f\n", "deepTagMD_bbvsLight", ( double)deepTagMD_bbvsLight); os << r;
      sprintf(r, "  %-32s: %f\n", "deepTagMD_ccvsLight", ( double)deepTagMD_ccvsLight); os << r;
      sprintf(r, "  %-32s: %f\n", "deepTag_H", ( double)deepTag_H); os << r;
      sprintf(r, "  %-32s: %f\n", "deepTag_QCD", ( double)deepTag_QCD); os << r;
      sprintf(r, "  %-32s: %f\n", "deepTag_QCDothers", ( double)deepTag_QCDothers); os << r;
      sprintf(r, "  %-32s: %f\n", "deepTag_TvsQCD", ( double)deepTag_TvsQCD); os << r;
      sprintf(r, "  %-32s: %f\n", "deepTag_WvsQCD", ( double)deepTag_WvsQCD); os << r;
      sprintf(r, "  %-32s: %f\n", "deepTag_ZvsQCD", ( double)deepTag_ZvsQCD); os << r;
      sprintf(r, "  %-32s: %f\n", "electronIdx3SJ", ( double)electronIdx3SJ); os << r;
      sprintf(r, "  %-32s: %f\n", "eta", ( double)eta); os << r;
      sprintf(r, "  %-32s: %f\n", "genJetAK8Idx", ( double)genJetAK8Idx); os << r;
      sprintf(r, "  %-32s: %f\n", "hadronFlavour", ( double)hadronFlavour); os << r;
      sprintf(r, "  %-32s: %f\n", "jetId", ( double)jetId); os << r;
      sprintf(r, "  %-32s: %f\n", "lsf3", ( double)lsf3); os << r;
      sprintf(r, "  %-32s: %f\n", "mass", ( double)mass); os << r;
      sprintf(r, "  %-32s: %f\n", "mass_jerDown", ( double)mass_jerDown); os << r;
      sprintf(r, "  %-32s: %f\n", "mass_jerUp", ( double)mass_jerUp); os << r;
      sprintf(r, "  %-32s: %f\n", "mass_jesTotalDown", ( double)mass_jesTotalDown); os << r;
      sprintf(r, "  %-32s: %f\n", "mass_jesTotalUp", ( double)mass_jesTotalUp); os << r;
      sprintf(r, "  %-32s: %f\n", "mass_jmrDown", ( double)mass_jmrDown); os << r;
      sprintf(r, "  %-32s: %f\n", "mass_jmrUp", ( double)mass_jmrUp); os << r;
      sprintf(r, "  %-32s: %f\n", "mass_jmsDown", ( double)mass_jmsDown); os << r;
      sprintf(r, "  %-32s: %f\n", "mass_jmsUp", ( double)mass_jmsUp); os << r;
      sprintf(r, "  %-32s: %f\n", "mass_nom", ( double)mass_nom); os << r;
      sprintf(r, "  %-32s: %f\n", "mass_raw", ( double)mass_raw); os << r;
      sprintf(r, "  %-32s: %f\n", "msoftdrop", ( double)msoftdrop); os << r;
      sprintf(r, "  %-32s: %f\n", "msoftdrop_corr_JMR", ( double)msoftdrop_corr_JMR); os << r;
      sprintf(r, "  %-32s: %f\n", "msoftdrop_corr_JMS", ( double)msoftdrop_corr_JMS); os << r;
      sprintf(r, "  %-32s: %f\n", "msoftdrop_corr_PUPPI", ( double)msoftdrop_corr_PUPPI); os << r;
      sprintf(r, "  %-32s: %f\n", "msoftdrop_jerDown", ( double)msoftdrop_jerDown); os << r;
      sprintf(r, "  %-32s: %f\n", "msoftdrop_jerUp", ( double)msoftdrop_jerUp); os << r;
      sprintf(r, "  %-32s: %f\n", "msoftdrop_jesTotalDown", ( double)msoftdrop_jesTotalDown); os << r;
      sprintf(r, "  %-32s: %f\n", "msoftdrop_jesTotalUp", ( double)msoftdrop_jesTotalUp); os << r;
      sprintf(r, "  %-32s: %f\n", "msoftdrop_jmrDown", ( double)msoftdrop_jmrDown); os << r;
      sprintf(r, "  %-32s: %f\n", "msoftdrop_jmrUp", ( double)msoftdrop_jmrUp); os << r;
      sprintf(r, "  %-32s: %f\n", "msoftdrop_jmsDown", ( double)msoftdrop_jmsDown); os << r;
      sprintf(r, "  %-32s: %f\n", "msoftdrop_jmsUp", ( double)msoftdrop_jmsUp); os << r;
      sprintf(r, "  %-32s: %f\n", "msoftdrop_nom", ( double)msoftdrop_nom); os << r;
      sprintf(r, "  %-32s: %f\n", "msoftdrop_raw", ( double)msoftdrop_raw); os << r;
      sprintf(r, "  %-32s: %f\n", "msoftdrop_tau21DDT_jerDown", ( double)msoftdrop_tau21DDT_jerDown); os << r;
      sprintf(r, "  %-32s: %f\n", "msoftdrop_tau21DDT_jerUp", ( double)msoftdrop_tau21DDT_jerUp); os << r;
      sprintf(r, "  %-32s: %f\n", "msoftdrop_tau21DDT_jmrDown", ( double)msoftdrop_tau21DDT_jmrDown); os << r;
      sprintf(r, "  %-32s: %f\n", "msoftdrop_tau21DDT_jmrUp", ( double)msoftdrop_tau21DDT_jmrUp); os << r;
      sprintf(r, "  %-32s: %f\n", "msoftdrop_tau21DDT_jmsDown", ( double)msoftdrop_tau21DDT_jmsDown); os << r;
      sprintf(r, "  %-32s: %f\n", "msoftdrop_tau21DDT_jmsUp", ( double)msoftdrop_tau21DDT_jmsUp); os << r;
      sprintf(r, "  %-32s: %f\n", "msoftdrop_tau21DDT_nom", ( double)msoftdrop_tau21DDT_nom); os << r;
      sprintf(r, "  %-32s: %f\n", "muonIdx3SJ", ( double)muonIdx3SJ); os << r;
      sprintf(r, "  %-32s: %f\n", "n2b1", ( double)n2b1); os << r;
      sprintf(r, "  %-32s: %f\n", "n3b1", ( double)n3b1); os << r;
      sprintf(r, "  %-32s: %f\n", "nBHadrons", ( double)nBHadrons); os << r;
      sprintf(r, "  %-32s: %f\n", "nCHadrons", ( double)nCHadrons); os << r;
      sprintf(r, "  %-32s: %f\n", "nConstituents", ( double)nConstituents); os << r;
      sprintf(r, "  %-32s: %f\n", "particleNetMD_QCD", ( double)particleNetMD_QCD); os << r;
      sprintf(r, "  %-32s: %f\n", "particleNetMD_Xbb", ( double)particleNetMD_Xbb); os << r;
      sprintf(r, "  %-32s: %f\n", "particleNetMD_Xcc", ( double)particleNetMD_Xcc); os << r;
      sprintf(r, "  %-32s: %f\n", "particleNetMD_Xqq", ( double)particleNetMD_Xqq); os << r;
      sprintf(r, "  %-32s: %f\n", "particleNet_H4qvsQCD", ( double)particleNet_H4qvsQCD); os << r;
      sprintf(r, "  %-32s: %f\n", "particleNet_HbbvsQCD", ( double)particleNet_HbbvsQCD); os << r;
      sprintf(r, "  %-32s: %f\n", "particleNet_HccvsQCD", ( double)particleNet_HccvsQCD); os << r;
      sprintf(r, "  %-32s: %f\n", "particleNet_QCD", ( double)particleNet_QCD); os << r;
      sprintf(r, "  %-32s: %f\n", "particleNet_TvsQCD", ( double)particleNet_TvsQCD); os << r;
      sprintf(r, "  %-32s: %f\n", "particleNet_WvsQCD", ( double)particleNet_WvsQCD); os << r;
      sprintf(r, "  %-32s: %f\n", "particleNet_ZvsQCD", ( double)particleNet_ZvsQCD); os << r;
      sprintf(r, "  %-32s: %f\n", "particleNet_mass", ( double)particleNet_mass); os << r;
      sprintf(r, "  %-32s: %f\n", "phi", ( double)phi); os << r;
      sprintf(r, "  %-32s: %f\n", "pt", ( double)pt); os << r;
      sprintf(r, "  %-32s: %f\n", "pt_jerDown", ( double)pt_jerDown); os << r;
      sprintf(r, "  %-32s: %f\n", "pt_jerUp", ( double)pt_jerUp); os << r;
      sprintf(r, "  %-32s: %f\n", "pt_jesTotalDown", ( double)pt_jesTotalDown); os << r;
      sprintf(r, "  %-32s: %f\n", "pt_jesTotalUp", ( double)pt_jesTotalUp); os << r;
      sprintf(r, "  %-32s: %f\n", "pt_nom", ( double)pt_nom); os << r;
      sprintf(r, "  %-32s: %f\n", "pt_raw", ( double)pt_raw); os << r;
      sprintf(r, "  %-32s: %f\n", "rawFactor", ( double)rawFactor); os << r;
      sprintf(r, "  %-32s: %f\n", "subJetIdx1", ( double)subJetIdx1); os << r;
      sprintf(r, "  %-32s: %f\n", "subJetIdx2", ( double)subJetIdx2); os << r;
      sprintf(r, "  %-32s: %f\n", "tau1", ( double)tau1); os << r;
      sprintf(r, "  %-32s: %f\n", "tau2", ( double)tau2); os << r;
      sprintf(r, "  %-32s: %f\n", "tau3", ( double)tau3); os << r;
      sprintf(r, "  %-32s: %f\n", "tau4", ( double)tau4); os << r;
      return os;
    }
  };

  struct FsrPhoton_s
  {
    float	dROverEt2;
    float	eta;
    int	muonIdx;
    float	phi;
    float	pt;
    float	relIso03;

    std::ostream& operator<<(std::ostream& os)
    {
      char r[1024];
      os << "FsrPhoton" << std::endl;
      sprintf(r, "  %-32s: %f\n", "dROverEt2", ( double)dROverEt2); os << r;
      sprintf(r, "  %-32s: %f\n", "eta", ( double)eta); os << r;
      sprintf(r, "  %-32s: %f\n", "muonIdx", ( double)muonIdx); os << r;
      sprintf(r, "  %-32s: %f\n", "phi", ( double)phi); os << r;
      sprintf(r, "  %-32s: %f\n", "pt", ( double)pt); os << r;
      sprintf(r, "  %-32s: %f\n", "relIso03", ( double)relIso03); os << r;
      return os;
    }
  };

  struct GenIsolatedPhoton_s
  {
    float	eta;
    float	mass;
    float	phi;
    float	pt;

    std::ostream& operator<<(std::ostream& os)
    {
      char r[1024];
      os << "GenIsolatedPhoton" << std::endl;
      sprintf(r, "  %-32s: %f\n", "eta", ( double)eta); os << r;
      sprintf(r, "  %-32s: %f\n", "mass", ( double)mass); os << r;
      sprintf(r, "  %-32s: %f\n", "phi", ( double)phi); os << r;
      sprintf(r, "  %-32s: %f\n", "pt", ( double)pt); os << r;
      return os;
    }
  };

  struct GenJet_s
  {
    float	eta;
    int	hadronFlavour;
    float	mass;
    int	partonFlavour;
    float	phi;
    float	pt;

    std::ostream& operator<<(std::ostream& os)
    {
      char r[1024];
      os << "GenJet" << std::endl;
      sprintf(r, "  %-32s: %f\n", "eta", ( double)eta); os << r;
      sprintf(r, "  %-32s: %f\n", "hadronFlavour", ( double)hadronFlavour); os << r;
      sprintf(r, "  %-32s: %f\n", "mass", ( double)mass); os << r;
      sprintf(r, "  %-32s: %f\n", "partonFlavour", ( double)partonFlavour); os << r;
      sprintf(r, "  %-32s: %f\n", "phi", ( double)phi); os << r;
      sprintf(r, "  %-32s: %f\n", "pt", ( double)pt); os << r;
      return os;
    }
  };

  struct GenJetAK8_s
  {
    float	eta;
    int	hadronFlavour;
    float	mass;
    int	partonFlavour;
    float	phi;
    float	pt;

    std::ostream& operator<<(std::ostream& os)
    {
      char r[1024];
      os << "GenJetAK8" << std::endl;
      sprintf(r, "  %-32s: %f\n", "eta", ( double)eta); os << r;
      sprintf(r, "  %-32s: %f\n", "hadronFlavour", ( double)hadronFlavour); os << r;
      sprintf(r, "  %-32s: %f\n", "mass", ( double)mass); os << r;
      sprintf(r, "  %-32s: %f\n", "partonFlavour", ( double)partonFlavour); os << r;
      sprintf(r, "  %-32s: %f\n", "phi", ( double)phi); os << r;
      sprintf(r, "  %-32s: %f\n", "pt", ( double)pt); os << r;
      return os;
    }
  };

  struct GenPart_s
  {
    float	eta;
    int	genPartIdxMother;
    float	mass;
    int	pdgId;
    float	phi;
    float	pt;
    int	status;
    int	statusFlags;

    std::ostream& operator<<(std::ostream& os)
    {
      char r[1024];
      os << "GenPart" << std::endl;
      sprintf(r, "  %-32s: %f\n", "eta", ( double)eta); os << r;
      sprintf(r, "  %-32s: %f\n", "genPartIdxMother", ( double)genPartIdxMother); os << r;
      sprintf(r, "  %-32s: %f\n", "mass", ( double)mass); os << r;
      sprintf(r, "  %-32s: %f\n", "pdgId", ( double)pdgId); os << r;
      sprintf(r, "  %-32s: %f\n", "phi", ( double)phi); os << r;
      sprintf(r, "  %-32s: %f\n", "pt", ( double)pt); os << r;
      sprintf(r, "  %-32s: %f\n", "status", ( double)status); os << r;
      sprintf(r, "  %-32s: %f\n", "statusFlags", ( double)statusFlags); os << r;
      return os;
    }
  };

  struct IsoTrack_s
  {
    int	charge;
    float	dxy;
    float	dz;
    float	eta;
    int	fromPV;
    bool	isFromLostTrack;
    bool	isHighPurityTrack;
    bool	isPFcand;
    float	miniPFRelIso_all;
    float	miniPFRelIso_chg;
    int	pdgId;
    float	pfRelIso03_all;
    float	pfRelIso03_chg;
    float	phi;
    float	pt;

    std::ostream& operator<<(std::ostream& os)
    {
      char r[1024];
      os << "IsoTrack" << std::endl;
      sprintf(r, "  %-32s: %f\n", "charge", ( double)charge); os << r;
      sprintf(r, "  %-32s: %f\n", "dxy", ( double)dxy); os << r;
      sprintf(r, "  %-32s: %f\n", "dz", ( double)dz); os << r;
      sprintf(r, "  %-32s: %f\n", "eta", ( double)eta); os << r;
      sprintf(r, "  %-32s: %f\n", "fromPV", ( double)fromPV); os << r;
      sprintf(r, "  %-32s: %f\n", "isFromLostTrack", ( double)isFromLostTrack); os << r;
      sprintf(r, "  %-32s: %f\n", "isHighPurityTrack", ( double)isHighPurityTrack); os << r;
      sprintf(r, "  %-32s: %f\n", "isPFcand", ( double)isPFcand); os << r;
      sprintf(r, "  %-32s: %f\n", "miniPFRelIso_all", ( double)miniPFRelIso_all); os << r;
      sprintf(r, "  %-32s: %f\n", "miniPFRelIso_chg", ( double)miniPFRelIso_chg); os << r;
      sprintf(r, "  %-32s: %f\n", "pdgId", ( double)pdgId); os << r;
      sprintf(r, "  %-32s: %f\n", "pfRelIso03_all", ( double)pfRelIso03_all); os << r;
      sprintf(r, "  %-32s: %f\n", "pfRelIso03_chg", ( double)pfRelIso03_chg); os << r;
      sprintf(r, "  %-32s: %f\n", "phi", ( double)phi); os << r;
      sprintf(r, "  %-32s: %f\n", "pt", ( double)pt); os << r;
      return os;
    }
  };

  struct Jet_s
  {
    float	area;
    float	bRegCorr;
    float	bRegRes;
    float	btagCSVV2;
    float	btagDeepB;
    float	btagDeepCvB;
    float	btagDeepCvL;
    float	btagDeepFlavB;
    float	btagDeepFlavCvB;
    float	btagDeepFlavCvL;
    float	btagDeepFlavQG;
    float	cRegCorr;
    float	cRegRes;
    float	chEmEF;
    float	chFPV0EF;
    float	chHEF;
    int	cleanmask;
    float	corr_JEC;
    float	corr_JER;
    int	electronIdx1;
    int	electronIdx2;
    float	eta;
    int	genJetIdx;
    int	hadronFlavour;
    int	hfadjacentEtaStripsSize;
    int	hfcentralEtaStripSize;
    float	hfsigmaEtaEta;
    float	hfsigmaPhiPhi;
    int	jetId;
    float	mass;
    float	mass_jerDown;
    float	mass_jerUp;
    float	mass_jesTotalDown;
    float	mass_jesTotalUp;
    float	mass_nom;
    float	mass_raw;
    float	muEF;
    int	muonIdx1;
    int	muonIdx2;
    float	muonSubtrFactor;
    int	nConstituents;
    int	nElectrons;
    int	nMuons;
    float	neEmEF;
    float	neHEF;
    int	partonFlavour;
    float	phi;
    float	pt;
    float	pt_jerDown;
    float	pt_jerUp;
    float	pt_jesTotalDown;
    float	pt_jesTotalUp;
    float	pt_nom;
    float	pt_raw;
    int	puId;
    float	puIdDisc;
    float	qgl;
    float	rawFactor;

    std::ostream& operator<<(std::ostream& os)
    {
      char r[1024];
      os << "Jet" << std::endl;
      sprintf(r, "  %-32s: %f\n", "area", ( double)area); os << r;
      sprintf(r, "  %-32s: %f\n", "bRegCorr", ( double)bRegCorr); os << r;
      sprintf(r, "  %-32s: %f\n", "bRegRes", ( double)bRegRes); os << r;
      sprintf(r, "  %-32s: %f\n", "btagCSVV2", ( double)btagCSVV2); os << r;
      sprintf(r, "  %-32s: %f\n", "btagDeepB", ( double)btagDeepB); os << r;
      sprintf(r, "  %-32s: %f\n", "btagDeepCvB", ( double)btagDeepCvB); os << r;
      sprintf(r, "  %-32s: %f\n", "btagDeepCvL", ( double)btagDeepCvL); os << r;
      sprintf(r, "  %-32s: %f\n", "btagDeepFlavB", ( double)btagDeepFlavB); os << r;
      sprintf(r, "  %-32s: %f\n", "btagDeepFlavCvB", ( double)btagDeepFlavCvB); os << r;
      sprintf(r, "  %-32s: %f\n", "btagDeepFlavCvL", ( double)btagDeepFlavCvL); os << r;
      sprintf(r, "  %-32s: %f\n", "btagDeepFlavQG", ( double)btagDeepFlavQG); os << r;
      sprintf(r, "  %-32s: %f\n", "cRegCorr", ( double)cRegCorr); os << r;
      sprintf(r, "  %-32s: %f\n", "cRegRes", ( double)cRegRes); os << r;
      sprintf(r, "  %-32s: %f\n", "chEmEF", ( double)chEmEF); os << r;
      sprintf(r, "  %-32s: %f\n", "chFPV0EF", ( double)chFPV0EF); os << r;
      sprintf(r, "  %-32s: %f\n", "chHEF", ( double)chHEF); os << r;
      sprintf(r, "  %-32s: %f\n", "cleanmask", ( double)cleanmask); os << r;
      sprintf(r, "  %-32s: %f\n", "corr_JEC", ( double)corr_JEC); os << r;
      sprintf(r, "  %-32s: %f\n", "corr_JER", ( double)corr_JER); os << r;
      sprintf(r, "  %-32s: %f\n", "electronIdx1", ( double)electronIdx1); os << r;
      sprintf(r, "  %-32s: %f\n", "electronIdx2", ( double)electronIdx2); os << r;
      sprintf(r, "  %-32s: %f\n", "eta", ( double)eta); os << r;
      sprintf(r, "  %-32s: %f\n", "genJetIdx", ( double)genJetIdx); os << r;
      sprintf(r, "  %-32s: %f\n", "hadronFlavour", ( double)hadronFlavour); os << r;
      sprintf(r, "  %-32s: %f\n", "hfadjacentEtaStripsSize", ( double)hfadjacentEtaStripsSize); os << r;
      sprintf(r, "  %-32s: %f\n", "hfcentralEtaStripSize", ( double)hfcentralEtaStripSize); os << r;
      sprintf(r, "  %-32s: %f\n", "hfsigmaEtaEta", ( double)hfsigmaEtaEta); os << r;
      sprintf(r, "  %-32s: %f\n", "hfsigmaPhiPhi", ( double)hfsigmaPhiPhi); os << r;
      sprintf(r, "  %-32s: %f\n", "jetId", ( double)jetId); os << r;
      sprintf(r, "  %-32s: %f\n", "mass", ( double)mass); os << r;
      sprintf(r, "  %-32s: %f\n", "mass_jerDown", ( double)mass_jerDown); os << r;
      sprintf(r, "  %-32s: %f\n", "mass_jerUp", ( double)mass_jerUp); os << r;
      sprintf(r, "  %-32s: %f\n", "mass_jesTotalDown", ( double)mass_jesTotalDown); os << r;
      sprintf(r, "  %-32s: %f\n", "mass_jesTotalUp", ( double)mass_jesTotalUp); os << r;
      sprintf(r, "  %-32s: %f\n", "mass_nom", ( double)mass_nom); os << r;
      sprintf(r, "  %-32s: %f\n", "mass_raw", ( double)mass_raw); os << r;
      sprintf(r, "  %-32s: %f\n", "muEF", ( double)muEF); os << r;
      sprintf(r, "  %-32s: %f\n", "muonIdx1", ( double)muonIdx1); os << r;
      sprintf(r, "  %-32s: %f\n", "muonIdx2", ( double)muonIdx2); os << r;
      sprintf(r, "  %-32s: %f\n", "muonSubtrFactor", ( double)muonSubtrFactor); os << r;
      sprintf(r, "  %-32s: %f\n", "nConstituents", ( double)nConstituents); os << r;
      sprintf(r, "  %-32s: %f\n", "nElectrons", ( double)nElectrons); os << r;
      sprintf(r, "  %-32s: %f\n", "nMuons", ( double)nMuons); os << r;
      sprintf(r, "  %-32s: %f\n", "neEmEF", ( double)neEmEF); os << r;
      sprintf(r, "  %-32s: %f\n", "neHEF", ( double)neHEF); os << r;
      sprintf(r, "  %-32s: %f\n", "partonFlavour", ( double)partonFlavour); os << r;
      sprintf(r, "  %-32s: %f\n", "phi", ( double)phi); os << r;
      sprintf(r, "  %-32s: %f\n", "pt", ( double)pt); os << r;
      sprintf(r, "  %-32s: %f\n", "pt_jerDown", ( double)pt_jerDown); os << r;
      sprintf(r, "  %-32s: %f\n", "pt_jerUp", ( double)pt_jerUp); os << r;
      sprintf(r, "  %-32s: %f\n", "pt_jesTotalDown", ( double)pt_jesTotalDown); os << r;
      sprintf(r, "  %-32s: %f\n", "pt_jesTotalUp", ( double)pt_jesTotalUp); os << r;
      sprintf(r, "  %-32s: %f\n", "pt_nom", ( double)pt_nom); os << r;
      sprintf(r, "  %-32s: %f\n", "pt_raw", ( double)pt_raw); os << r;
      sprintf(r, "  %-32s: %f\n", "puId", ( double)puId); os << r;
      sprintf(r, "  %-32s: %f\n", "puIdDisc", ( double)puIdDisc); os << r;
      sprintf(r, "  %-32s: %f\n", "qgl", ( double)qgl); os << r;
      sprintf(r, "  %-32s: %f\n", "rawFactor", ( double)rawFactor); os << r;
      return os;
    }
  };

  struct LHEPart_s
  {
    float	eta;
    float	incomingpz;
    float	mass;
    int	pdgId;
    float	phi;
    float	pt;
    int	spin;
    int	status;

    std::ostream& operator<<(std::ostream& os)
    {
      char r[1024];
      os << "LHEPart" << std::endl;
      sprintf(r, "  %-32s: %f\n", "eta", ( double)eta); os << r;
      sprintf(r, "  %-32s: %f\n", "incomingpz", ( double)incomingpz); os << r;
      sprintf(r, "  %-32s: %f\n", "mass", ( double)mass); os << r;
      sprintf(r, "  %-32s: %f\n", "pdgId", ( double)pdgId); os << r;
      sprintf(r, "  %-32s: %f\n", "phi", ( double)phi); os << r;
      sprintf(r, "  %-32s: %f\n", "pt", ( double)pt); os << r;
      sprintf(r, "  %-32s: %f\n", "spin", ( double)spin); os << r;
      sprintf(r, "  %-32s: %f\n", "status", ( double)status); os << r;
      return os;
    }
  };

  struct Muon_s
  {
    int	charge;
    int	cleanmask;
    float	dxy;
    float	dxyErr;
    float	dxybs;
    float	dz;
    float	dzErr;
    float	eta;
    int	fsrPhotonIdx;
    int	genPartFlav;
    int	genPartIdx;
    int	highPtId;
    bool	highPurity;
    bool	inTimeMuon;
    float	ip3d;
    bool	isGlobal;
    bool	isPFcand;
    bool	isStandalone;
    bool	isTracker;
    int	jetIdx;
    int	jetNDauCharged;
    float	jetPtRelv2;
    float	jetRelIso;
    bool	looseId;
    float	mass;
    bool	mediumId;
    bool	mediumPromptId;
    int	miniIsoId;
    float	miniPFRelIso_all;
    float	miniPFRelIso_chg;
    int	multiIsoId;
    int	mvaId;
    float	mvaLowPt;
    int	mvaLowPtId;
    float	mvaTTH;
    int	nStations;
    int	nTrackerLayers;
    int	pdgId;
    int	pfIsoId;
    float	pfRelIso03_all;
    float	pfRelIso03_chg;
    float	pfRelIso04_all;
    float	phi;
    float	pt;
    float	ptErr;
    int	puppiIsoId;
    float	segmentComp;
    float	sip3d;
    bool	softId;
    float	softMva;
    bool	softMvaId;
    int	tightCharge;
    bool	tightId;
    int	tkIsoId;
    float	tkRelIso;
    bool	triggerIdLoose;
    float	tunepRelPt;

    std::ostream& operator<<(std::ostream& os)
    {
      char r[1024];
      os << "Muon" << std::endl;
      sprintf(r, "  %-32s: %f\n", "charge", ( double)charge); os << r;
      sprintf(r, "  %-32s: %f\n", "cleanmask", ( double)cleanmask); os << r;
      sprintf(r, "  %-32s: %f\n", "dxy", ( double)dxy); os << r;
      sprintf(r, "  %-32s: %f\n", "dxyErr", ( double)dxyErr); os << r;
      sprintf(r, "  %-32s: %f\n", "dxybs", ( double)dxybs); os << r;
      sprintf(r, "  %-32s: %f\n", "dz", ( double)dz); os << r;
      sprintf(r, "  %-32s: %f\n", "dzErr", ( double)dzErr); os << r;
      sprintf(r, "  %-32s: %f\n", "eta", ( double)eta); os << r;
      sprintf(r, "  %-32s: %f\n", "fsrPhotonIdx", ( double)fsrPhotonIdx); os << r;
      sprintf(r, "  %-32s: %f\n", "genPartFlav", ( double)genPartFlav); os << r;
      sprintf(r, "  %-32s: %f\n", "genPartIdx", ( double)genPartIdx); os << r;
      sprintf(r, "  %-32s: %f\n", "highPtId", ( double)highPtId); os << r;
      sprintf(r, "  %-32s: %f\n", "highPurity", ( double)highPurity); os << r;
      sprintf(r, "  %-32s: %f\n", "inTimeMuon", ( double)inTimeMuon); os << r;
      sprintf(r, "  %-32s: %f\n", "ip3d", ( double)ip3d); os << r;
      sprintf(r, "  %-32s: %f\n", "isGlobal", ( double)isGlobal); os << r;
      sprintf(r, "  %-32s: %f\n", "isPFcand", ( double)isPFcand); os << r;
      sprintf(r, "  %-32s: %f\n", "isStandalone", ( double)isStandalone); os << r;
      sprintf(r, "  %-32s: %f\n", "isTracker", ( double)isTracker); os << r;
      sprintf(r, "  %-32s: %f\n", "jetIdx", ( double)jetIdx); os << r;
      sprintf(r, "  %-32s: %f\n", "jetNDauCharged", ( double)jetNDauCharged); os << r;
      sprintf(r, "  %-32s: %f\n", "jetPtRelv2", ( double)jetPtRelv2); os << r;
      sprintf(r, "  %-32s: %f\n", "jetRelIso", ( double)jetRelIso); os << r;
      sprintf(r, "  %-32s: %f\n", "looseId", ( double)looseId); os << r;
      sprintf(r, "  %-32s: %f\n", "mass", ( double)mass); os << r;
      sprintf(r, "  %-32s: %f\n", "mediumId", ( double)mediumId); os << r;
      sprintf(r, "  %-32s: %f\n", "mediumPromptId", ( double)mediumPromptId); os << r;
      sprintf(r, "  %-32s: %f\n", "miniIsoId", ( double)miniIsoId); os << r;
      sprintf(r, "  %-32s: %f\n", "miniPFRelIso_all", ( double)miniPFRelIso_all); os << r;
      sprintf(r, "  %-32s: %f\n", "miniPFRelIso_chg", ( double)miniPFRelIso_chg); os << r;
      sprintf(r, "  %-32s: %f\n", "multiIsoId", ( double)multiIsoId); os << r;
      sprintf(r, "  %-32s: %f\n", "mvaId", ( double)mvaId); os << r;
      sprintf(r, "  %-32s: %f\n", "mvaLowPt", ( double)mvaLowPt); os << r;
      sprintf(r, "  %-32s: %f\n", "mvaLowPtId", ( double)mvaLowPtId); os << r;
      sprintf(r, "  %-32s: %f\n", "mvaTTH", ( double)mvaTTH); os << r;
      sprintf(r, "  %-32s: %f\n", "nStations", ( double)nStations); os << r;
      sprintf(r, "  %-32s: %f\n", "nTrackerLayers", ( double)nTrackerLayers); os << r;
      sprintf(r, "  %-32s: %f\n", "pdgId", ( double)pdgId); os << r;
      sprintf(r, "  %-32s: %f\n", "pfIsoId", ( double)pfIsoId); os << r;
      sprintf(r, "  %-32s: %f\n", "pfRelIso03_all", ( double)pfRelIso03_all); os << r;
      sprintf(r, "  %-32s: %f\n", "pfRelIso03_chg", ( double)pfRelIso03_chg); os << r;
      sprintf(r, "  %-32s: %f\n", "pfRelIso04_all", ( double)pfRelIso04_all); os << r;
      sprintf(r, "  %-32s: %f\n", "phi", ( double)phi); os << r;
      sprintf(r, "  %-32s: %f\n", "pt", ( double)pt); os << r;
      sprintf(r, "  %-32s: %f\n", "ptErr", ( double)ptErr); os << r;
      sprintf(r, "  %-32s: %f\n", "puppiIsoId", ( double)puppiIsoId); os << r;
      sprintf(r, "  %-32s: %f\n", "segmentComp", ( double)segmentComp); os << r;
      sprintf(r, "  %-32s: %f\n", "sip3d", ( double)sip3d); os << r;
      sprintf(r, "  %-32s: %f\n", "softId", ( double)softId); os << r;
      sprintf(r, "  %-32s: %f\n", "softMva", ( double)softMva); os << r;
      sprintf(r, "  %-32s: %f\n", "softMvaId", ( double)softMvaId); os << r;
      sprintf(r, "  %-32s: %f\n", "tightCharge", ( double)tightCharge); os << r;
      sprintf(r, "  %-32s: %f\n", "tightId", ( double)tightId); os << r;
      sprintf(r, "  %-32s: %f\n", "tkIsoId", ( double)tkIsoId); os << r;
      sprintf(r, "  %-32s: %f\n", "tkRelIso", ( double)tkRelIso); os << r;
      sprintf(r, "  %-32s: %f\n", "triggerIdLoose", ( double)triggerIdLoose); os << r;
      sprintf(r, "  %-32s: %f\n", "tunepRelPt", ( double)tunepRelPt); os << r;
      return os;
    }
  };

  struct Photon_s
  {
    int	charge;
    int	cleanmask;
    int	cutBased;
    int	cutBased_Fall17V1Bitmap;
    float	dEscaleDown;
    float	dEscaleUp;
    float	dEsigmaDown;
    float	dEsigmaUp;
    float	eCorr;
    int	electronIdx;
    bool	electronVeto;
    float	energyErr;
    float	eta;
    int	genPartFlav;
    int	genPartIdx;
    float	hoe;
    bool	isScEtaEB;
    bool	isScEtaEE;
    int	jetIdx;
    float	mass;
    float	mvaID;
    float	mvaID_Fall17V1p1;
    bool	mvaID_WP80;
    bool	mvaID_WP90;
    int	pdgId;
    float	pfRelIso03_all;
    float	pfRelIso03_chg;
    float	phi;
    bool	pixelSeed;
    float	pt;
    float	r9;
    int	seedGain;
    float	sieie;
    int	vidNestedWPBitmap;

    std::ostream& operator<<(std::ostream& os)
    {
      char r[1024];
      os << "Photon" << std::endl;
      sprintf(r, "  %-32s: %f\n", "charge", ( double)charge); os << r;
      sprintf(r, "  %-32s: %f\n", "cleanmask", ( double)cleanmask); os << r;
      sprintf(r, "  %-32s: %f\n", "cutBased", ( double)cutBased); os << r;
      sprintf(r, "  %-32s: %f\n", "cutBased_Fall17V1Bitmap", ( double)cutBased_Fall17V1Bitmap); os << r;
      sprintf(r, "  %-32s: %f\n", "dEscaleDown", ( double)dEscaleDown); os << r;
      sprintf(r, "  %-32s: %f\n", "dEscaleUp", ( double)dEscaleUp); os << r;
      sprintf(r, "  %-32s: %f\n", "dEsigmaDown", ( double)dEsigmaDown); os << r;
      sprintf(r, "  %-32s: %f\n", "dEsigmaUp", ( double)dEsigmaUp); os << r;
      sprintf(r, "  %-32s: %f\n", "eCorr", ( double)eCorr); os << r;
      sprintf(r, "  %-32s: %f\n", "electronIdx", ( double)electronIdx); os << r;
      sprintf(r, "  %-32s: %f\n", "electronVeto", ( double)electronVeto); os << r;
      sprintf(r, "  %-32s: %f\n", "energyErr", ( double)energyErr); os << r;
      sprintf(r, "  %-32s: %f\n", "eta", ( double)eta); os << r;
      sprintf(r, "  %-32s: %f\n", "genPartFlav", ( double)genPartFlav); os << r;
      sprintf(r, "  %-32s: %f\n", "genPartIdx", ( double)genPartIdx); os << r;
      sprintf(r, "  %-32s: %f\n", "hoe", ( double)hoe); os << r;
      sprintf(r, "  %-32s: %f\n", "isScEtaEB", ( double)isScEtaEB); os << r;
      sprintf(r, "  %-32s: %f\n", "isScEtaEE", ( double)isScEtaEE); os << r;
      sprintf(r, "  %-32s: %f\n", "jetIdx", ( double)jetIdx); os << r;
      sprintf(r, "  %-32s: %f\n", "mass", ( double)mass); os << r;
      sprintf(r, "  %-32s: %f\n", "mvaID", ( double)mvaID); os << r;
      sprintf(r, "  %-32s: %f\n", "mvaID_Fall17V1p1", ( double)mvaID_Fall17V1p1); os << r;
      sprintf(r, "  %-32s: %f\n", "mvaID_WP80", ( double)mvaID_WP80); os << r;
      sprintf(r, "  %-32s: %f\n", "mvaID_WP90", ( double)mvaID_WP90); os << r;
      sprintf(r, "  %-32s: %f\n", "pdgId", ( double)pdgId); os << r;
      sprintf(r, "  %-32s: %f\n", "pfRelIso03_all", ( double)pfRelIso03_all); os << r;
      sprintf(r, "  %-32s: %f\n", "pfRelIso03_chg", ( double)pfRelIso03_chg); os << r;
      sprintf(r, "  %-32s: %f\n", "phi", ( double)phi); os << r;
      sprintf(r, "  %-32s: %f\n", "pixelSeed", ( double)pixelSeed); os << r;
      sprintf(r, "  %-32s: %f\n", "pt", ( double)pt); os << r;
      sprintf(r, "  %-32s: %f\n", "r9", ( double)r9); os << r;
      sprintf(r, "  %-32s: %f\n", "seedGain", ( double)seedGain); os << r;
      sprintf(r, "  %-32s: %f\n", "sieie", ( double)sieie); os << r;
      sprintf(r, "  %-32s: %f\n", "vidNestedWPBitmap", ( double)vidNestedWPBitmap); os << r;
      return os;
    }
  };

  struct SubGenJetAK8_s
  {
    float	eta;
    float	mass;
    float	phi;
    float	pt;

    std::ostream& operator<<(std::ostream& os)
    {
      char r[1024];
      os << "SubGenJetAK8" << std::endl;
      sprintf(r, "  %-32s: %f\n", "eta", ( double)eta); os << r;
      sprintf(r, "  %-32s: %f\n", "mass", ( double)mass); os << r;
      sprintf(r, "  %-32s: %f\n", "phi", ( double)phi); os << r;
      sprintf(r, "  %-32s: %f\n", "pt", ( double)pt); os << r;
      return os;
    }
  };

  struct SubJet_s
  {
    float	btagCSVV2;
    float	btagDeepB;
    float	eta;
    int	hadronFlavour;
    float	mass;
    float	n2b1;
    float	n3b1;
    int	nBHadrons;
    int	nCHadrons;
    float	phi;
    float	pt;
    float	rawFactor;
    float	tau1;
    float	tau2;
    float	tau3;
    float	tau4;

    std::ostream& operator<<(std::ostream& os)
    {
      char r[1024];
      os << "SubJet" << std::endl;
      sprintf(r, "  %-32s: %f\n", "btagCSVV2", ( double)btagCSVV2); os << r;
      sprintf(r, "  %-32s: %f\n", "btagDeepB", ( double)btagDeepB); os << r;
      sprintf(r, "  %-32s: %f\n", "eta", ( double)eta); os << r;
      sprintf(r, "  %-32s: %f\n", "hadronFlavour", ( double)hadronFlavour); os << r;
      sprintf(r, "  %-32s: %f\n", "mass", ( double)mass); os << r;
      sprintf(r, "  %-32s: %f\n", "n2b1", ( double)n2b1); os << r;
      sprintf(r, "  %-32s: %f\n", "n3b1", ( double)n3b1); os << r;
      sprintf(r, "  %-32s: %f\n", "nBHadrons", ( double)nBHadrons); os << r;
      sprintf(r, "  %-32s: %f\n", "nCHadrons", ( double)nCHadrons); os << r;
      sprintf(r, "  %-32s: %f\n", "phi", ( double)phi); os << r;
      sprintf(r, "  %-32s: %f\n", "pt", ( double)pt); os << r;
      sprintf(r, "  %-32s: %f\n", "rawFactor", ( double)rawFactor); os << r;
      sprintf(r, "  %-32s: %f\n", "tau1", ( double)tau1); os << r;
      sprintf(r, "  %-32s: %f\n", "tau2", ( double)tau2); os << r;
      sprintf(r, "  %-32s: %f\n", "tau3", ( double)tau3); os << r;
      sprintf(r, "  %-32s: %f\n", "tau4", ( double)tau4); os << r;
      return os;
    }
  };

  struct Tau_s
  {
    int	charge;
    float	chargedIso;
    int	cleanmask;
    int	decayMode;
    float	dxy;
    float	dz;
    float	eta;
    int	genPartFlav;
    int	genPartIdx;
    bool	idAntiEleDeadECal;
    int	idAntiMu;
    bool	idDecayModeOldDMs;
    int	idDeepTau2017v2p1VSe;
    int	idDeepTau2017v2p1VSjet;
    int	idDeepTau2017v2p1VSmu;
    int	jetIdx;
    float	leadTkDeltaEta;
    float	leadTkDeltaPhi;
    float	leadTkPtOverTauPt;
    float	mass;
    float	neutralIso;
    float	phi;
    float	photonsOutsideSignalCone;
    float	pt;
    float	puCorr;
    float	rawDeepTau2017v2p1VSe;
    float	rawDeepTau2017v2p1VSjet;
    float	rawDeepTau2017v2p1VSmu;
    float	rawIso;
    float	rawIsodR03;

    std::ostream& operator<<(std::ostream& os)
    {
      char r[1024];
      os << "Tau" << std::endl;
      sprintf(r, "  %-32s: %f\n", "charge", ( double)charge); os << r;
      sprintf(r, "  %-32s: %f\n", "chargedIso", ( double)chargedIso); os << r;
      sprintf(r, "  %-32s: %f\n", "cleanmask", ( double)cleanmask); os << r;
      sprintf(r, "  %-32s: %f\n", "decayMode", ( double)decayMode); os << r;
      sprintf(r, "  %-32s: %f\n", "dxy", ( double)dxy); os << r;
      sprintf(r, "  %-32s: %f\n", "dz", ( double)dz); os << r;
      sprintf(r, "  %-32s: %f\n", "eta", ( double)eta); os << r;
      sprintf(r, "  %-32s: %f\n", "genPartFlav", ( double)genPartFlav); os << r;
      sprintf(r, "  %-32s: %f\n", "genPartIdx", ( double)genPartIdx); os << r;
      sprintf(r, "  %-32s: %f\n", "idAntiEleDeadECal", ( double)idAntiEleDeadECal); os << r;
      sprintf(r, "  %-32s: %f\n", "idAntiMu", ( double)idAntiMu); os << r;
      sprintf(r, "  %-32s: %f\n", "idDecayModeOldDMs", ( double)idDecayModeOldDMs); os << r;
      sprintf(r, "  %-32s: %f\n", "idDeepTau2017v2p1VSe", ( double)idDeepTau2017v2p1VSe); os << r;
      sprintf(r, "  %-32s: %f\n", "idDeepTau2017v2p1VSjet", ( double)idDeepTau2017v2p1VSjet); os << r;
      sprintf(r, "  %-32s: %f\n", "idDeepTau2017v2p1VSmu", ( double)idDeepTau2017v2p1VSmu); os << r;
      sprintf(r, "  %-32s: %f\n", "jetIdx", ( double)jetIdx); os << r;
      sprintf(r, "  %-32s: %f\n", "leadTkDeltaEta", ( double)leadTkDeltaEta); os << r;
      sprintf(r, "  %-32s: %f\n", "leadTkDeltaPhi", ( double)leadTkDeltaPhi); os << r;
      sprintf(r, "  %-32s: %f\n", "leadTkPtOverTauPt", ( double)leadTkPtOverTauPt); os << r;
      sprintf(r, "  %-32s: %f\n", "mass", ( double)mass); os << r;
      sprintf(r, "  %-32s: %f\n", "neutralIso", ( double)neutralIso); os << r;
      sprintf(r, "  %-32s: %f\n", "phi", ( double)phi); os << r;
      sprintf(r, "  %-32s: %f\n", "photonsOutsideSignalCone", ( double)photonsOutsideSignalCone); os << r;
      sprintf(r, "  %-32s: %f\n", "pt", ( double)pt); os << r;
      sprintf(r, "  %-32s: %f\n", "puCorr", ( double)puCorr); os << r;
      sprintf(r, "  %-32s: %f\n", "rawDeepTau2017v2p1VSe", ( double)rawDeepTau2017v2p1VSe); os << r;
      sprintf(r, "  %-32s: %f\n", "rawDeepTau2017v2p1VSjet", ( double)rawDeepTau2017v2p1VSjet); os << r;
      sprintf(r, "  %-32s: %f\n", "rawDeepTau2017v2p1VSmu", ( double)rawDeepTau2017v2p1VSmu); os << r;
      sprintf(r, "  %-32s: %f\n", "rawIso", ( double)rawIso); os << r;
      sprintf(r, "  %-32s: %f\n", "rawIsodR03", ( double)rawIsodR03); os << r;
      return os;
    }
  };

  struct TrigObj_s
  {
    float	eta;
    int	filterBits;
    int	id;
    int	l1charge;
    int	l1iso;
    float	l1pt;
    float	l1pt_2;
    float	l2pt;
    float	phi;
    float	pt;

    std::ostream& operator<<(std::ostream& os)
    {
      char r[1024];
      os << "TrigObj" << std::endl;
      sprintf(r, "  %-32s: %f\n", "eta", ( double)eta); os << r;
      sprintf(r, "  %-32s: %f\n", "filterBits", ( double)filterBits); os << r;
      sprintf(r, "  %-32s: %f\n", "id", ( double)id); os << r;
      sprintf(r, "  %-32s: %f\n", "l1charge", ( double)l1charge); os << r;
      sprintf(r, "  %-32s: %f\n", "l1iso", ( double)l1iso); os << r;
      sprintf(r, "  %-32s: %f\n", "l1pt", ( double)l1pt); os << r;
      sprintf(r, "  %-32s: %f\n", "l1pt_2", ( double)l1pt_2); os << r;
      sprintf(r, "  %-32s: %f\n", "l2pt", ( double)l2pt); os << r;
      sprintf(r, "  %-32s: %f\n", "phi", ( double)phi); os << r;
      sprintf(r, "  %-32s: %f\n", "pt", ( double)pt); os << r;
      return os;
    }
  };

  struct boostedTau_s
  {
    int	charge;
    float	chargedIso;
    int	decayMode;
    float	eta;
    int	genPartFlav;
    int	genPartIdx;
    int	idAntiEle2018;
    int	idAntiMu;
    int	idMVAnewDM2017v2;
    int	idMVAoldDM2017v2;
    int	idMVAoldDMdR032017v2;
    int	jetIdx;
    float	leadTkDeltaEta;
    float	leadTkDeltaPhi;
    float	leadTkPtOverTauPt;
    float	mass;
    float	neutralIso;
    float	phi;
    float	photonsOutsideSignalCone;
    float	pt;
    float	puCorr;
    float	rawAntiEle2018;
    int	rawAntiEleCat2018;
    float	rawIso;
    float	rawIsodR03;
    float	rawMVAnewDM2017v2;
    float	rawMVAoldDM2017v2;
    float	rawMVAoldDMdR032017v2;

    std::ostream& operator<<(std::ostream& os)
    {
      char r[1024];
      os << "boostedTau" << std::endl;
      sprintf(r, "  %-32s: %f\n", "charge", ( double)charge); os << r;
      sprintf(r, "  %-32s: %f\n", "chargedIso", ( double)chargedIso); os << r;
      sprintf(r, "  %-32s: %f\n", "decayMode", ( double)decayMode); os << r;
      sprintf(r, "  %-32s: %f\n", "eta", ( double)eta); os << r;
      sprintf(r, "  %-32s: %f\n", "genPartFlav", ( double)genPartFlav); os << r;
      sprintf(r, "  %-32s: %f\n", "genPartIdx", ( double)genPartIdx); os << r;
      sprintf(r, "  %-32s: %f\n", "idAntiEle2018", ( double)idAntiEle2018); os << r;
      sprintf(r, "  %-32s: %f\n", "idAntiMu", ( double)idAntiMu); os << r;
      sprintf(r, "  %-32s: %f\n", "idMVAnewDM2017v2", ( double)idMVAnewDM2017v2); os << r;
      sprintf(r, "  %-32s: %f\n", "idMVAoldDM2017v2", ( double)idMVAoldDM2017v2); os << r;
      sprintf(r, "  %-32s: %f\n", "idMVAoldDMdR032017v2", ( double)idMVAoldDMdR032017v2); os << r;
      sprintf(r, "  %-32s: %f\n", "jetIdx", ( double)jetIdx); os << r;
      sprintf(r, "  %-32s: %f\n", "leadTkDeltaEta", ( double)leadTkDeltaEta); os << r;
      sprintf(r, "  %-32s: %f\n", "leadTkDeltaPhi", ( double)leadTkDeltaPhi); os << r;
      sprintf(r, "  %-32s: %f\n", "leadTkPtOverTauPt", ( double)leadTkPtOverTauPt); os << r;
      sprintf(r, "  %-32s: %f\n", "mass", ( double)mass); os << r;
      sprintf(r, "  %-32s: %f\n", "neutralIso", ( double)neutralIso); os << r;
      sprintf(r, "  %-32s: %f\n", "phi", ( double)phi); os << r;
      sprintf(r, "  %-32s: %f\n", "photonsOutsideSignalCone", ( double)photonsOutsideSignalCone); os << r;
      sprintf(r, "  %-32s: %f\n", "pt", ( double)pt); os << r;
      sprintf(r, "  %-32s: %f\n", "puCorr", ( double)puCorr); os << r;
      sprintf(r, "  %-32s: %f\n", "rawAntiEle2018", ( double)rawAntiEle2018); os << r;
      sprintf(r, "  %-32s: %f\n", "rawAntiEleCat2018", ( double)rawAntiEleCat2018); os << r;
      sprintf(r, "  %-32s: %f\n", "rawIso", ( double)rawIso); os << r;
      sprintf(r, "  %-32s: %f\n", "rawIsodR03", ( double)rawIsodR03); os << r;
      sprintf(r, "  %-32s: %f\n", "rawMVAnewDM2017v2", ( double)rawMVAnewDM2017v2); os << r;
      sprintf(r, "  %-32s: %f\n", "rawMVAoldDM2017v2", ( double)rawMVAoldDM2017v2); os << r;
      sprintf(r, "  %-32s: %f\n", "rawMVAoldDMdR032017v2", ( double)rawMVAoldDMdR032017v2); os << r;
      return os;
    }
  };


  void fillCorrT1METJets()
  {
    CorrT1METJet.resize(CorrT1METJet_area.size());
    for(unsigned int i=0; i < CorrT1METJet.size(); ++i)
      {
        CorrT1METJet[i].area	= CorrT1METJet_area[i];
        CorrT1METJet[i].eta	= CorrT1METJet_eta[i];
        CorrT1METJet[i].muonSubtrFactor	= CorrT1METJet_muonSubtrFactor[i];
        CorrT1METJet[i].phi	= CorrT1METJet_phi[i];
        CorrT1METJet[i].rawPt	= CorrT1METJet_rawPt[i];
      }
  }

  void fillElectrons()
  {
    Electron.resize(Electron_charge.size());
    for(unsigned int i=0; i < Electron.size(); ++i)
      {
        Electron[i].charge	= Electron_charge[i];
        Electron[i].cleanmask	= Electron_cleanmask[i];
        Electron[i].convVeto	= (bool)Electron_convVeto[i];
        Electron[i].cutBased	= Electron_cutBased[i];
        Electron[i].cutBased_HEEP	= (bool)Electron_cutBased_HEEP[i];
        Electron[i].dEscaleDown	= Electron_dEscaleDown[i];
        Electron[i].dEscaleUp	= Electron_dEscaleUp[i];
        Electron[i].dEsigmaDown	= Electron_dEsigmaDown[i];
        Electron[i].dEsigmaUp	= Electron_dEsigmaUp[i];
        Electron[i].deltaEtaSC	= Electron_deltaEtaSC[i];
        Electron[i].dr03EcalRecHitSumEt	= Electron_dr03EcalRecHitSumEt[i];
        Electron[i].dr03HcalDepth1TowerSumEt	= Electron_dr03HcalDepth1TowerSumEt[i];
        Electron[i].dr03TkSumPt	= Electron_dr03TkSumPt[i];
        Electron[i].dr03TkSumPtHEEP	= Electron_dr03TkSumPtHEEP[i];
        Electron[i].dxy	= Electron_dxy[i];
        Electron[i].dxyErr	= Electron_dxyErr[i];
        Electron[i].dz	= Electron_dz[i];
        Electron[i].dzErr	= Electron_dzErr[i];
        Electron[i].eCorr	= Electron_eCorr[i];
        Electron[i].eInvMinusPInv	= Electron_eInvMinusPInv[i];
        Electron[i].energyErr	= Electron_energyErr[i];
        Electron[i].eta	= Electron_eta[i];
        Electron[i].genPartFlav	= Electron_genPartFlav[i];
        Electron[i].genPartIdx	= Electron_genPartIdx[i];
        Electron[i].hoe	= Electron_hoe[i];
        Electron[i].ip3d	= Electron_ip3d[i];
        Electron[i].isPFcand	= (bool)Electron_isPFcand[i];
        Electron[i].jetIdx	= Electron_jetIdx[i];
        Electron[i].jetNDauCharged	= Electron_jetNDauCharged[i];
        Electron[i].jetPtRelv2	= Electron_jetPtRelv2[i];
        Electron[i].jetRelIso	= Electron_jetRelIso[i];
        Electron[i].lostHits	= Electron_lostHits[i];
        Electron[i].mass	= Electron_mass[i];
        Electron[i].miniPFRelIso_all	= Electron_miniPFRelIso_all[i];
        Electron[i].miniPFRelIso_chg	= Electron_miniPFRelIso_chg[i];
        Electron[i].mvaFall17V2Iso	= Electron_mvaFall17V2Iso[i];
        Electron[i].mvaFall17V2Iso_WP80	= (bool)Electron_mvaFall17V2Iso_WP80[i];
        Electron[i].mvaFall17V2Iso_WP90	= (bool)Electron_mvaFall17V2Iso_WP90[i];
        Electron[i].mvaFall17V2Iso_WPL	= (bool)Electron_mvaFall17V2Iso_WPL[i];
        Electron[i].mvaFall17V2noIso	= Electron_mvaFall17V2noIso[i];
        Electron[i].mvaFall17V2noIso_WP80	= (bool)Electron_mvaFall17V2noIso_WP80[i];
        Electron[i].mvaFall17V2noIso_WP90	= (bool)Electron_mvaFall17V2noIso_WP90[i];
        Electron[i].mvaFall17V2noIso_WPL	= (bool)Electron_mvaFall17V2noIso_WPL[i];
        Electron[i].mvaTTH	= Electron_mvaTTH[i];
        Electron[i].pdgId	= Electron_pdgId[i];
        Electron[i].pfRelIso03_all	= Electron_pfRelIso03_all[i];
        Electron[i].pfRelIso03_chg	= Electron_pfRelIso03_chg[i];
        Electron[i].phi	= Electron_phi[i];
        Electron[i].photonIdx	= Electron_photonIdx[i];
        Electron[i].pt	= Electron_pt[i];
        Electron[i].r9	= Electron_r9[i];
        Electron[i].scEtOverPt	= Electron_scEtOverPt[i];
        Electron[i].seedGain	= Electron_seedGain[i];
        Electron[i].sieie	= Electron_sieie[i];
        Electron[i].sip3d	= Electron_sip3d[i];
        Electron[i].tightCharge	= Electron_tightCharge[i];
        Electron[i].vidNestedWPBitmap	= Electron_vidNestedWPBitmap[i];
        Electron[i].vidNestedWPBitmapHEEP	= Electron_vidNestedWPBitmapHEEP[i];
      }
  }

  void fillFatJets()
  {
    FatJet.resize(FatJet_area.size());
    for(unsigned int i=0; i < FatJet.size(); ++i)
      {
        FatJet[i].area	= FatJet_area[i];
        FatJet[i].btagCSVV2	= FatJet_btagCSVV2[i];
        FatJet[i].btagDDBvLV2	= FatJet_btagDDBvLV2[i];
        FatJet[i].btagDDCvBV2	= FatJet_btagDDCvBV2[i];
        FatJet[i].btagDDCvLV2	= FatJet_btagDDCvLV2[i];
        FatJet[i].btagDeepB	= FatJet_btagDeepB[i];
        FatJet[i].btagHbb	= FatJet_btagHbb[i];
        FatJet[i].corr_JEC	= FatJet_corr_JEC[i];
        FatJet[i].corr_JER	= FatJet_corr_JER[i];
        FatJet[i].corr_JMR	= FatJet_corr_JMR[i];
        FatJet[i].corr_JMS	= FatJet_corr_JMS[i];
        FatJet[i].deepTagMD_H4qvsQCD	= FatJet_deepTagMD_H4qvsQCD[i];
        FatJet[i].deepTagMD_HbbvsQCD	= FatJet_deepTagMD_HbbvsQCD[i];
        FatJet[i].deepTagMD_TvsQCD	= FatJet_deepTagMD_TvsQCD[i];
        FatJet[i].deepTagMD_WvsQCD	= FatJet_deepTagMD_WvsQCD[i];
        FatJet[i].deepTagMD_ZHbbvsQCD	= FatJet_deepTagMD_ZHbbvsQCD[i];
        FatJet[i].deepTagMD_ZHccvsQCD	= FatJet_deepTagMD_ZHccvsQCD[i];
        FatJet[i].deepTagMD_ZbbvsQCD	= FatJet_deepTagMD_ZbbvsQCD[i];
        FatJet[i].deepTagMD_ZvsQCD	= FatJet_deepTagMD_ZvsQCD[i];
        FatJet[i].deepTagMD_bbvsLight	= FatJet_deepTagMD_bbvsLight[i];
        FatJet[i].deepTagMD_ccvsLight	= FatJet_deepTagMD_ccvsLight[i];
        FatJet[i].deepTag_H	= FatJet_deepTag_H[i];
        FatJet[i].deepTag_QCD	= FatJet_deepTag_QCD[i];
        FatJet[i].deepTag_QCDothers	= FatJet_deepTag_QCDothers[i];
        FatJet[i].deepTag_TvsQCD	= FatJet_deepTag_TvsQCD[i];
        FatJet[i].deepTag_WvsQCD	= FatJet_deepTag_WvsQCD[i];
        FatJet[i].deepTag_ZvsQCD	= FatJet_deepTag_ZvsQCD[i];
        FatJet[i].electronIdx3SJ	= FatJet_electronIdx3SJ[i];
        FatJet[i].eta	= FatJet_eta[i];
        FatJet[i].genJetAK8Idx	= FatJet_genJetAK8Idx[i];
        FatJet[i].hadronFlavour	= FatJet_hadronFlavour[i];
        FatJet[i].jetId	= FatJet_jetId[i];
        FatJet[i].lsf3	= FatJet_lsf3[i];
        FatJet[i].mass	= FatJet_mass_nom[i];
        FatJet[i].mass_jerDown	= FatJet_mass_jerDown[i];
        FatJet[i].mass_jerUp	= FatJet_mass_jerUp[i];
        FatJet[i].mass_jesTotalDown	= FatJet_mass_jesTotalDown[i];
        FatJet[i].mass_jesTotalUp	= FatJet_mass_jesTotalUp[i];
        FatJet[i].mass_jmrDown	= FatJet_mass_jmrDown[i];
        FatJet[i].mass_jmrUp	= FatJet_mass_jmrUp[i];
        FatJet[i].mass_jmsDown	= FatJet_mass_jmsDown[i];
        FatJet[i].mass_jmsUp	= FatJet_mass_jmsUp[i];
        FatJet[i].mass_nom	= FatJet_mass_nom[i];
        FatJet[i].mass_raw	= FatJet_mass_raw[i];
        FatJet[i].msoftdrop	= FatJet_msoftdrop_nom[i];
        FatJet[i].msoftdrop_corr_JMR	= FatJet_msoftdrop_corr_JMR[i];
        FatJet[i].msoftdrop_corr_JMS	= FatJet_msoftdrop_corr_JMS[i];
        FatJet[i].msoftdrop_corr_PUPPI	= FatJet_msoftdrop_corr_PUPPI[i];
        FatJet[i].msoftdrop_jerDown	= FatJet_msoftdrop_jerDown[i];
        FatJet[i].msoftdrop_jerUp	= FatJet_msoftdrop_jerUp[i];
        FatJet[i].msoftdrop_jesTotalDown	= FatJet_msoftdrop_jesTotalDown[i];
        FatJet[i].msoftdrop_jesTotalUp	= FatJet_msoftdrop_jesTotalUp[i];
        FatJet[i].msoftdrop_jmrDown	= FatJet_msoftdrop_jmrDown[i];
        FatJet[i].msoftdrop_jmrUp	= FatJet_msoftdrop_jmrUp[i];
        FatJet[i].msoftdrop_jmsDown	= FatJet_msoftdrop_jmsDown[i];
        FatJet[i].msoftdrop_jmsUp	= FatJet_msoftdrop_jmsUp[i];
        FatJet[i].msoftdrop_nom	= FatJet_msoftdrop_nom[i];
        FatJet[i].msoftdrop_raw	= FatJet_msoftdrop_raw[i];
        FatJet[i].msoftdrop_tau21DDT_jerDown	= FatJet_msoftdrop_tau21DDT_jerDown[i];
        FatJet[i].msoftdrop_tau21DDT_jerUp	= FatJet_msoftdrop_tau21DDT_jerUp[i];
        FatJet[i].msoftdrop_tau21DDT_jmrDown	= FatJet_msoftdrop_tau21DDT_jmrDown[i];
        FatJet[i].msoftdrop_tau21DDT_jmrUp	= FatJet_msoftdrop_tau21DDT_jmrUp[i];
        FatJet[i].msoftdrop_tau21DDT_jmsDown	= FatJet_msoftdrop_tau21DDT_jmsDown[i];
        FatJet[i].msoftdrop_tau21DDT_jmsUp	= FatJet_msoftdrop_tau21DDT_jmsUp[i];
        FatJet[i].msoftdrop_tau21DDT_nom	= FatJet_msoftdrop_tau21DDT_nom[i];
        FatJet[i].muonIdx3SJ	= FatJet_muonIdx3SJ[i];
        FatJet[i].n2b1	= FatJet_n2b1[i];
        FatJet[i].n3b1	= FatJet_n3b1[i];
        FatJet[i].nBHadrons	= FatJet_nBHadrons[i];
        FatJet[i].nCHadrons	= FatJet_nCHadrons[i];
        FatJet[i].nConstituents	= FatJet_nConstituents[i];
        FatJet[i].particleNetMD_QCD	= FatJet_particleNetMD_QCD[i];
        FatJet[i].particleNetMD_Xbb	= FatJet_particleNetMD_Xbb[i];
        FatJet[i].particleNetMD_Xcc	= FatJet_particleNetMD_Xcc[i];
        FatJet[i].particleNetMD_Xqq	= FatJet_particleNetMD_Xqq[i];
        FatJet[i].particleNet_H4qvsQCD	= FatJet_particleNet_H4qvsQCD[i];
        FatJet[i].particleNet_HbbvsQCD	= FatJet_particleNet_HbbvsQCD[i];
        FatJet[i].particleNet_HccvsQCD	= FatJet_particleNet_HccvsQCD[i];
        FatJet[i].particleNet_QCD	= FatJet_particleNet_QCD[i];
        FatJet[i].particleNet_TvsQCD	= FatJet_particleNet_TvsQCD[i];
        FatJet[i].particleNet_WvsQCD	= FatJet_particleNet_WvsQCD[i];
        FatJet[i].particleNet_ZvsQCD	= FatJet_particleNet_ZvsQCD[i];
        FatJet[i].particleNet_mass	= FatJet_particleNet_mass[i];
        FatJet[i].phi	= FatJet_phi[i];
        FatJet[i].pt	= FatJet_pt_nom[i];
        FatJet[i].pt_jerDown	= FatJet_pt_jerDown[i];
        FatJet[i].pt_jerUp	= FatJet_pt_jerUp[i];
        FatJet[i].pt_jesTotalDown	= FatJet_pt_jesTotalDown[i];
        FatJet[i].pt_jesTotalUp	= FatJet_pt_jesTotalUp[i];
        FatJet[i].pt_nom	= FatJet_pt_nom[i];
        FatJet[i].pt_raw	= FatJet_pt_raw[i];
        FatJet[i].rawFactor	= FatJet_rawFactor[i];
        FatJet[i].subJetIdx1	= FatJet_subJetIdx1[i];
        FatJet[i].subJetIdx2	= FatJet_subJetIdx2[i];
        FatJet[i].tau1	= FatJet_tau1[i];
        FatJet[i].tau2	= FatJet_tau2[i];
        FatJet[i].tau3	= FatJet_tau3[i];
        FatJet[i].tau4	= FatJet_tau4[i];
      }
  }

  void fillFsrPhotons()
  {
    FsrPhoton.resize(FsrPhoton_dROverEt2.size());
    for(unsigned int i=0; i < FsrPhoton.size(); ++i)
      {
        FsrPhoton[i].dROverEt2	= FsrPhoton_dROverEt2[i];
        FsrPhoton[i].eta	= FsrPhoton_eta[i];
        FsrPhoton[i].muonIdx	= FsrPhoton_muonIdx[i];
        FsrPhoton[i].phi	= FsrPhoton_phi[i];
        FsrPhoton[i].pt	= FsrPhoton_pt[i];
        FsrPhoton[i].relIso03	= FsrPhoton_relIso03[i];
      }
  }

  void fillGenIsolatedPhotons()
  {
    GenIsolatedPhoton.resize(GenIsolatedPhoton_eta.size());
    for(unsigned int i=0; i < GenIsolatedPhoton.size(); ++i)
      {
        GenIsolatedPhoton[i].eta	= GenIsolatedPhoton_eta[i];
        GenIsolatedPhoton[i].mass	= GenIsolatedPhoton_mass[i];
        GenIsolatedPhoton[i].phi	= GenIsolatedPhoton_phi[i];
        GenIsolatedPhoton[i].pt	= GenIsolatedPhoton_pt[i];
      }
  }

  void fillGenJets()
  {
    GenJet.resize(GenJet_eta.size());
    for(unsigned int i=0; i < GenJet.size(); ++i)
      {
        GenJet[i].eta	= GenJet_eta[i];
        GenJet[i].hadronFlavour	= GenJet_hadronFlavour[i];
        GenJet[i].mass	= GenJet_mass[i];
        GenJet[i].partonFlavour	= GenJet_partonFlavour[i];
        GenJet[i].phi	= GenJet_phi[i];
        GenJet[i].pt	= GenJet_pt[i];
      }
  }

  void fillGenJetAK8s()
  {
    GenJetAK8.resize(GenJetAK8_eta.size());
    for(unsigned int i=0; i < GenJetAK8.size(); ++i)
      {
        GenJetAK8[i].eta	= GenJetAK8_eta[i];
        GenJetAK8[i].hadronFlavour	= GenJetAK8_hadronFlavour[i];
        GenJetAK8[i].mass	= GenJetAK8_mass[i];
        GenJetAK8[i].partonFlavour	= GenJetAK8_partonFlavour[i];
        GenJetAK8[i].phi	= GenJetAK8_phi[i];
        GenJetAK8[i].pt	= GenJetAK8_pt[i];
      }
  }

  void fillGenParts()
  {
    GenPart.resize(GenPart_eta.size());
    for(unsigned int i=0; i < GenPart.size(); ++i)
      {
        GenPart[i].eta	= GenPart_eta[i];
        GenPart[i].genPartIdxMother	= GenPart_genPartIdxMother[i];
        GenPart[i].mass	= GenPart_mass[i];
        GenPart[i].pdgId	= GenPart_pdgId[i];
        GenPart[i].phi	= GenPart_phi[i];
        GenPart[i].pt	= GenPart_pt[i];
        GenPart[i].status	= GenPart_status[i];
        GenPart[i].statusFlags	= GenPart_statusFlags[i];
      }
  }

  void fillIsoTracks()
  {
    IsoTrack.resize(IsoTrack_charge.size());
    for(unsigned int i=0; i < IsoTrack.size(); ++i)
      {
        IsoTrack[i].charge	= IsoTrack_charge[i];
        IsoTrack[i].dxy	= IsoTrack_dxy[i];
        IsoTrack[i].dz	= IsoTrack_dz[i];
        IsoTrack[i].eta	= IsoTrack_eta[i];
        IsoTrack[i].fromPV	= IsoTrack_fromPV[i];
        IsoTrack[i].isFromLostTrack	= (bool)IsoTrack_isFromLostTrack[i];
        IsoTrack[i].isHighPurityTrack	= (bool)IsoTrack_isHighPurityTrack[i];
        IsoTrack[i].isPFcand	= (bool)IsoTrack_isPFcand[i];
        IsoTrack[i].miniPFRelIso_all	= IsoTrack_miniPFRelIso_all[i];
        IsoTrack[i].miniPFRelIso_chg	= IsoTrack_miniPFRelIso_chg[i];
        IsoTrack[i].pdgId	= IsoTrack_pdgId[i];
        IsoTrack[i].pfRelIso03_all	= IsoTrack_pfRelIso03_all[i];
        IsoTrack[i].pfRelIso03_chg	= IsoTrack_pfRelIso03_chg[i];
        IsoTrack[i].phi	= IsoTrack_phi[i];
        IsoTrack[i].pt	= IsoTrack_pt[i];
      }
  }

  void fillJets()
  {
    Jet.resize(Jet_area.size());
    for(unsigned int i=0; i < Jet.size(); ++i)
      {
        Jet[i].area	= Jet_area[i];
        Jet[i].bRegCorr	= Jet_bRegCorr[i];
        Jet[i].bRegRes	= Jet_bRegRes[i];
        Jet[i].btagCSVV2	= Jet_btagCSVV2[i];
        Jet[i].btagDeepB	= Jet_btagDeepB[i];
        Jet[i].btagDeepCvB	= Jet_btagDeepCvB[i];
        Jet[i].btagDeepCvL	= Jet_btagDeepCvL[i];
        Jet[i].btagDeepFlavB	= Jet_btagDeepFlavB[i];
        Jet[i].btagDeepFlavCvB	= Jet_btagDeepFlavCvB[i];
        Jet[i].btagDeepFlavCvL	= Jet_btagDeepFlavCvL[i];
        Jet[i].btagDeepFlavQG	= Jet_btagDeepFlavQG[i];
        Jet[i].cRegCorr	= Jet_cRegCorr[i];
        Jet[i].cRegRes	= Jet_cRegRes[i];
        Jet[i].chEmEF	= Jet_chEmEF[i];
        Jet[i].chFPV0EF	= Jet_chFPV0EF[i];
        Jet[i].chHEF	= Jet_chHEF[i];
        Jet[i].cleanmask	= Jet_cleanmask[i];
        Jet[i].corr_JEC	= Jet_corr_JEC[i];
        Jet[i].corr_JER	= Jet_corr_JER[i];
        Jet[i].electronIdx1	= Jet_electronIdx1[i];
        Jet[i].electronIdx2	= Jet_electronIdx2[i];
        Jet[i].eta	= Jet_eta[i];
        Jet[i].genJetIdx	= Jet_genJetIdx[i];
        Jet[i].hadronFlavour	= Jet_hadronFlavour[i];
        Jet[i].hfadjacentEtaStripsSize	= Jet_hfadjacentEtaStripsSize[i];
        Jet[i].hfcentralEtaStripSize	= Jet_hfcentralEtaStripSize[i];
        Jet[i].hfsigmaEtaEta	= Jet_hfsigmaEtaEta[i];
        Jet[i].hfsigmaPhiPhi	= Jet_hfsigmaPhiPhi[i];
        Jet[i].jetId	= Jet_jetId[i];
        Jet[i].mass	= Jet_mass_nom[i];
        Jet[i].mass_jerDown	= Jet_mass_jerDown[i];
        Jet[i].mass_jerUp	= Jet_mass_jerUp[i];
        Jet[i].mass_jesTotalDown	= Jet_mass_jesTotalDown[i];
        Jet[i].mass_jesTotalUp	= Jet_mass_jesTotalUp[i];
        Jet[i].mass_nom	= Jet_mass_nom[i];
        Jet[i].mass_raw	= Jet_mass_raw[i];
        Jet[i].muEF	= Jet_muEF[i];
        Jet[i].muonIdx1	= Jet_muonIdx1[i];
        Jet[i].muonIdx2	= Jet_muonIdx2[i];
        Jet[i].muonSubtrFactor	= Jet_muonSubtrFactor[i];
        Jet[i].nConstituents	= Jet_nConstituents[i];
        Jet[i].nElectrons	= Jet_nElectrons[i];
        Jet[i].nMuons	= Jet_nMuons[i];
        Jet[i].neEmEF	= Jet_neEmEF[i];
        Jet[i].neHEF	= Jet_neHEF[i];
        Jet[i].partonFlavour	= Jet_partonFlavour[i];
        Jet[i].phi	= Jet_phi[i];
        Jet[i].pt	= Jet_pt_nom[i];
        Jet[i].pt_jerDown	= Jet_pt_jerDown[i];
        Jet[i].pt_jerUp	= Jet_pt_jerUp[i];
        Jet[i].pt_jesTotalDown	= Jet_pt_jesTotalDown[i];
        Jet[i].pt_jesTotalUp	= Jet_pt_jesTotalUp[i];
        Jet[i].pt_nom	= Jet_pt_nom[i];
        Jet[i].pt_raw	= Jet_pt_raw[i];
        Jet[i].puId	= Jet_puId[i];
        Jet[i].puIdDisc	= Jet_puIdDisc[i];
        Jet[i].qgl	= Jet_qgl[i];
        Jet[i].rawFactor	= Jet_rawFactor[i];
      }
  }

  void fillLHEParts()
  {
    LHEPart.resize(LHEPart_eta.size());
    for(unsigned int i=0; i < LHEPart.size(); ++i)
      {
        LHEPart[i].eta	= LHEPart_eta[i];
        LHEPart[i].incomingpz	= LHEPart_incomingpz[i];
        LHEPart[i].mass	= LHEPart_mass[i];
        LHEPart[i].pdgId	= LHEPart_pdgId[i];
        LHEPart[i].phi	= LHEPart_phi[i];
        LHEPart[i].pt	= LHEPart_pt[i];
        LHEPart[i].spin	= LHEPart_spin[i];
        LHEPart[i].status	= LHEPart_status[i];
      }
  }

  void fillMuons()
  {
    Muon.resize(Muon_charge.size());
    for(unsigned int i=0; i < Muon.size(); ++i)
      {
        Muon[i].charge	= Muon_charge[i];
        Muon[i].cleanmask	= Muon_cleanmask[i];
        Muon[i].dxy	= Muon_dxy[i];
        Muon[i].dxyErr	= Muon_dxyErr[i];
        Muon[i].dxybs	= Muon_dxybs[i];
        Muon[i].dz	= Muon_dz[i];
        Muon[i].dzErr	= Muon_dzErr[i];
        Muon[i].eta	= Muon_eta[i];
        Muon[i].fsrPhotonIdx	= Muon_fsrPhotonIdx[i];
        Muon[i].genPartFlav	= Muon_genPartFlav[i];
        Muon[i].genPartIdx	= Muon_genPartIdx[i];
        Muon[i].highPtId	= Muon_highPtId[i];
        Muon[i].highPurity	= (bool)Muon_highPurity[i];
        Muon[i].inTimeMuon	= (bool)Muon_inTimeMuon[i];
        Muon[i].ip3d	= Muon_ip3d[i];
        Muon[i].isGlobal	= (bool)Muon_isGlobal[i];
        Muon[i].isPFcand	= (bool)Muon_isPFcand[i];
        Muon[i].isStandalone	= (bool)Muon_isStandalone[i];
        Muon[i].isTracker	= (bool)Muon_isTracker[i];
        Muon[i].jetIdx	= Muon_jetIdx[i];
        Muon[i].jetNDauCharged	= Muon_jetNDauCharged[i];
        Muon[i].jetPtRelv2	= Muon_jetPtRelv2[i];
        Muon[i].jetRelIso	= Muon_jetRelIso[i];
        Muon[i].looseId	= (bool)Muon_looseId[i];
        Muon[i].mass	= Muon_mass[i];
        Muon[i].mediumId	= (bool)Muon_mediumId[i];
        Muon[i].mediumPromptId	= (bool)Muon_mediumPromptId[i];
        Muon[i].miniIsoId	= Muon_miniIsoId[i];
        Muon[i].miniPFRelIso_all	= Muon_miniPFRelIso_all[i];
        Muon[i].miniPFRelIso_chg	= Muon_miniPFRelIso_chg[i];
        Muon[i].multiIsoId	= Muon_multiIsoId[i];
        Muon[i].mvaId	= Muon_mvaId[i];
        Muon[i].mvaLowPt	= Muon_mvaLowPt[i];
        Muon[i].mvaLowPtId	= Muon_mvaLowPtId[i];
        Muon[i].mvaTTH	= Muon_mvaTTH[i];
        Muon[i].nStations	= Muon_nStations[i];
        Muon[i].nTrackerLayers	= Muon_nTrackerLayers[i];
        Muon[i].pdgId	= Muon_pdgId[i];
        Muon[i].pfIsoId	= Muon_pfIsoId[i];
        Muon[i].pfRelIso03_all	= Muon_pfRelIso03_all[i];
        Muon[i].pfRelIso03_chg	= Muon_pfRelIso03_chg[i];
        Muon[i].pfRelIso04_all	= Muon_pfRelIso04_all[i];
        Muon[i].phi	= Muon_phi[i];
        Muon[i].pt	= Muon_pt[i];
        Muon[i].ptErr	= Muon_ptErr[i];
        Muon[i].puppiIsoId	= Muon_puppiIsoId[i];
        Muon[i].segmentComp	= Muon_segmentComp[i];
        Muon[i].sip3d	= Muon_sip3d[i];
        Muon[i].softId	= (bool)Muon_softId[i];
        Muon[i].softMva	= Muon_softMva[i];
        Muon[i].softMvaId	= (bool)Muon_softMvaId[i];
        Muon[i].tightCharge	= Muon_tightCharge[i];
        Muon[i].tightId	= (bool)Muon_tightId[i];
        Muon[i].tkIsoId	= Muon_tkIsoId[i];
        Muon[i].tkRelIso	= Muon_tkRelIso[i];
        Muon[i].triggerIdLoose	= (bool)Muon_triggerIdLoose[i];
        Muon[i].tunepRelPt	= Muon_tunepRelPt[i];
      }
  }

  void fillPhotons()
  {
    Photon.resize(Photon_charge.size());
    for(unsigned int i=0; i < Photon.size(); ++i)
      {
        Photon[i].charge	= Photon_charge[i];
        Photon[i].cleanmask	= Photon_cleanmask[i];
        Photon[i].cutBased	= Photon_cutBased[i];
        Photon[i].cutBased_Fall17V1Bitmap	= Photon_cutBased_Fall17V1Bitmap[i];
        Photon[i].dEscaleDown	= Photon_dEscaleDown[i];
        Photon[i].dEscaleUp	= Photon_dEscaleUp[i];
        Photon[i].dEsigmaDown	= Photon_dEsigmaDown[i];
        Photon[i].dEsigmaUp	= Photon_dEsigmaUp[i];
        Photon[i].eCorr	= Photon_eCorr[i];
        Photon[i].electronIdx	= Photon_electronIdx[i];
        Photon[i].electronVeto	= (bool)Photon_electronVeto[i];
        Photon[i].energyErr	= Photon_energyErr[i];
        Photon[i].eta	= Photon_eta[i];
        Photon[i].genPartFlav	= Photon_genPartFlav[i];
        Photon[i].genPartIdx	= Photon_genPartIdx[i];
        Photon[i].hoe	= Photon_hoe[i];
        Photon[i].isScEtaEB	= (bool)Photon_isScEtaEB[i];
        Photon[i].isScEtaEE	= (bool)Photon_isScEtaEE[i];
        Photon[i].jetIdx	= Photon_jetIdx[i];
        Photon[i].mass	= Photon_mass[i];
        Photon[i].mvaID	= Photon_mvaID[i];
        Photon[i].mvaID_Fall17V1p1	= Photon_mvaID_Fall17V1p1[i];
        Photon[i].mvaID_WP80	= (bool)Photon_mvaID_WP80[i];
        Photon[i].mvaID_WP90	= (bool)Photon_mvaID_WP90[i];
        Photon[i].pdgId	= Photon_pdgId[i];
        Photon[i].pfRelIso03_all	= Photon_pfRelIso03_all[i];
        Photon[i].pfRelIso03_chg	= Photon_pfRelIso03_chg[i];
        Photon[i].phi	= Photon_phi[i];
        Photon[i].pixelSeed	= (bool)Photon_pixelSeed[i];
        Photon[i].pt	= Photon_pt[i];
        Photon[i].r9	= Photon_r9[i];
        Photon[i].seedGain	= Photon_seedGain[i];
        Photon[i].sieie	= Photon_sieie[i];
        Photon[i].vidNestedWPBitmap	= Photon_vidNestedWPBitmap[i];
      }
  }

  void fillSubGenJetAK8s()
  {
    SubGenJetAK8.resize(SubGenJetAK8_eta.size());
    for(unsigned int i=0; i < SubGenJetAK8.size(); ++i)
      {
        SubGenJetAK8[i].eta	= SubGenJetAK8_eta[i];
        SubGenJetAK8[i].mass	= SubGenJetAK8_mass[i];
        SubGenJetAK8[i].phi	= SubGenJetAK8_phi[i];
        SubGenJetAK8[i].pt	= SubGenJetAK8_pt[i];
      }
  }

  void fillSubJets()
  {
    SubJet.resize(SubJet_btagCSVV2.size());
    for(unsigned int i=0; i < SubJet.size(); ++i)
      {
        SubJet[i].btagCSVV2	= SubJet_btagCSVV2[i];
        SubJet[i].btagDeepB	= SubJet_btagDeepB[i];
        SubJet[i].eta	= SubJet_eta[i];
        SubJet[i].hadronFlavour	= SubJet_hadronFlavour[i];
        SubJet[i].mass	= SubJet_mass[i];
        SubJet[i].n2b1	= SubJet_n2b1[i];
        SubJet[i].n3b1	= SubJet_n3b1[i];
        SubJet[i].nBHadrons	= SubJet_nBHadrons[i];
        SubJet[i].nCHadrons	= SubJet_nCHadrons[i];
        SubJet[i].phi	= SubJet_phi[i];
        SubJet[i].pt	= SubJet_pt[i];
        SubJet[i].rawFactor	= SubJet_rawFactor[i];
        SubJet[i].tau1	= SubJet_tau1[i];
        SubJet[i].tau2	= SubJet_tau2[i];
        SubJet[i].tau3	= SubJet_tau3[i];
        SubJet[i].tau4	= SubJet_tau4[i];
      }
  }

  void fillTaus()
  {
    Tau.resize(Tau_charge.size());
    for(unsigned int i=0; i < Tau.size(); ++i)
      {
        Tau[i].charge	= Tau_charge[i];
        Tau[i].chargedIso	= Tau_chargedIso[i];
        Tau[i].cleanmask	= Tau_cleanmask[i];
        Tau[i].decayMode	= Tau_decayMode[i];
        Tau[i].dxy	= Tau_dxy[i];
        Tau[i].dz	= Tau_dz[i];
        Tau[i].eta	= Tau_eta[i];
        Tau[i].genPartFlav	= Tau_genPartFlav[i];
        Tau[i].genPartIdx	= Tau_genPartIdx[i];
        Tau[i].idAntiEleDeadECal	= (bool)Tau_idAntiEleDeadECal[i];
        Tau[i].idAntiMu	= Tau_idAntiMu[i];
        Tau[i].idDecayModeOldDMs	= (bool)Tau_idDecayModeOldDMs[i];
        Tau[i].idDeepTau2017v2p1VSe	= Tau_idDeepTau2017v2p1VSe[i];
        Tau[i].idDeepTau2017v2p1VSjet	= Tau_idDeepTau2017v2p1VSjet[i];
        Tau[i].idDeepTau2017v2p1VSmu	= Tau_idDeepTau2017v2p1VSmu[i];
        Tau[i].jetIdx	= Tau_jetIdx[i];
        Tau[i].leadTkDeltaEta	= Tau_leadTkDeltaEta[i];
        Tau[i].leadTkDeltaPhi	= Tau_leadTkDeltaPhi[i];
        Tau[i].leadTkPtOverTauPt	= Tau_leadTkPtOverTauPt[i];
        Tau[i].mass	= Tau_mass[i];
        Tau[i].neutralIso	= Tau_neutralIso[i];
        Tau[i].phi	= Tau_phi[i];
        Tau[i].photonsOutsideSignalCone	= Tau_photonsOutsideSignalCone[i];
        Tau[i].pt	= Tau_pt[i];
        Tau[i].puCorr	= Tau_puCorr[i];
        Tau[i].rawDeepTau2017v2p1VSe	= Tau_rawDeepTau2017v2p1VSe[i];
        Tau[i].rawDeepTau2017v2p1VSjet	= Tau_rawDeepTau2017v2p1VSjet[i];
        Tau[i].rawDeepTau2017v2p1VSmu	= Tau_rawDeepTau2017v2p1VSmu[i];
        Tau[i].rawIso	= Tau_rawIso[i];
        Tau[i].rawIsodR03	= Tau_rawIsodR03[i];
      }
  }

  void fillTrigObjs()
  {
    TrigObj.resize(TrigObj_eta.size());
    for(unsigned int i=0; i < TrigObj.size(); ++i)
      {
        TrigObj[i].eta	= TrigObj_eta[i];
        TrigObj[i].filterBits	= TrigObj_filterBits[i];
        TrigObj[i].id	= TrigObj_id[i];
        TrigObj[i].l1charge	= TrigObj_l1charge[i];
        TrigObj[i].l1iso	= TrigObj_l1iso[i];
        TrigObj[i].l1pt	= TrigObj_l1pt[i];
        TrigObj[i].l1pt_2	= TrigObj_l1pt_2[i];
        TrigObj[i].l2pt	= TrigObj_l2pt[i];
        TrigObj[i].phi	= TrigObj_phi[i];
        TrigObj[i].pt	= TrigObj_pt[i];
      }
  }

  void fillboostedTaus()
  {
    boostedTau.resize(boostedTau_charge.size());
    for(unsigned int i=0; i < boostedTau.size(); ++i)
      {
        boostedTau[i].charge	= boostedTau_charge[i];
        boostedTau[i].chargedIso	= boostedTau_chargedIso[i];
        boostedTau[i].decayMode	= boostedTau_decayMode[i];
        boostedTau[i].eta	= boostedTau_eta[i];
        boostedTau[i].genPartFlav	= boostedTau_genPartFlav[i];
        boostedTau[i].genPartIdx	= boostedTau_genPartIdx[i];
        boostedTau[i].idAntiEle2018	= boostedTau_idAntiEle2018[i];
        boostedTau[i].idAntiMu	= boostedTau_idAntiMu[i];
        boostedTau[i].idMVAnewDM2017v2	= boostedTau_idMVAnewDM2017v2[i];
        boostedTau[i].idMVAoldDM2017v2	= boostedTau_idMVAoldDM2017v2[i];
        boostedTau[i].idMVAoldDMdR032017v2	= boostedTau_idMVAoldDMdR032017v2[i];
        boostedTau[i].jetIdx	= boostedTau_jetIdx[i];
        boostedTau[i].leadTkDeltaEta	= boostedTau_leadTkDeltaEta[i];
        boostedTau[i].leadTkDeltaPhi	= boostedTau_leadTkDeltaPhi[i];
        boostedTau[i].leadTkPtOverTauPt	= boostedTau_leadTkPtOverTauPt[i];
        boostedTau[i].mass	= boostedTau_mass[i];
        boostedTau[i].neutralIso	= boostedTau_neutralIso[i];
        boostedTau[i].phi	= boostedTau_phi[i];
        boostedTau[i].photonsOutsideSignalCone	= boostedTau_photonsOutsideSignalCone[i];
        boostedTau[i].pt	= boostedTau_pt[i];
        boostedTau[i].puCorr	= boostedTau_puCorr[i];
        boostedTau[i].rawAntiEle2018	= boostedTau_rawAntiEle2018[i];
        boostedTau[i].rawAntiEleCat2018	= boostedTau_rawAntiEleCat2018[i];
        boostedTau[i].rawIso	= boostedTau_rawIso[i];
        boostedTau[i].rawIsodR03	= boostedTau_rawIsodR03[i];
        boostedTau[i].rawMVAnewDM2017v2	= boostedTau_rawMVAnewDM2017v2[i];
        boostedTau[i].rawMVAoldDM2017v2	= boostedTau_rawMVAoldDM2017v2[i];
        boostedTau[i].rawMVAoldDMdR032017v2	= boostedTau_rawMVAoldDMdR032017v2[i];
      }
  }


  std::vector<eventBuffer::CorrT1METJet_s> CorrT1METJet;
  std::vector<eventBuffer::Electron_s> Electron;
  std::vector<eventBuffer::FatJet_s> FatJet;
  std::vector<eventBuffer::FsrPhoton_s> FsrPhoton;
  std::vector<eventBuffer::GenIsolatedPhoton_s> GenIsolatedPhoton;
  std::vector<eventBuffer::GenJet_s> GenJet;
  std::vector<eventBuffer::GenJetAK8_s> GenJetAK8;
  std::vector<eventBuffer::GenPart_s> GenPart;
  std::vector<eventBuffer::IsoTrack_s> IsoTrack;
  std::vector<eventBuffer::Jet_s> Jet;
  std::vector<eventBuffer::LHEPart_s> LHEPart;
  std::vector<eventBuffer::Muon_s> Muon;
  std::vector<eventBuffer::Photon_s> Photon;
  std::vector<eventBuffer::SubGenJetAK8_s> SubGenJetAK8;
  std::vector<eventBuffer::SubJet_s> SubJet;
  std::vector<eventBuffer::Tau_s> Tau;
  std::vector<eventBuffer::TrigObj_s> TrigObj;
  std::vector<eventBuffer::boostedTau_s> boostedTau;

  void fillObjects()
  {
    fillCorrT1METJets();
    fillElectrons();
    fillFatJets();
    fillFsrPhotons();
    fillGenIsolatedPhotons();
    fillGenJets();
    fillGenJetAK8s();
    fillGenParts();
    fillIsoTracks();
    fillJets();
    fillLHEParts();
    fillMuons();
    fillPhotons();
    fillSubGenJetAK8s();
    fillSubJets();
    fillTaus();
    fillTrigObjs();
    fillboostedTaus();
  }

   //--------------------------------------------------------------------------
  // Save objects for which the select function was called
  void saveObjects()
  {
    int n = 0;

    n = 0;
    try
      {
         n = indexmap["CorrT1METJet"].size();
      }
    catch (...)
      {}
    if ( n > 0 )
      {
        std::vector<int>& index = indexmap["CorrT1METJet"];
        for(int i=0; i < n; ++i)
          {
            int j = index[i];
            CorrT1METJet_area[i]	= CorrT1METJet_area[j];
            CorrT1METJet_eta[i]	= CorrT1METJet_eta[j];
            CorrT1METJet_muonSubtrFactor[i]	= CorrT1METJet_muonSubtrFactor[j];
            CorrT1METJet_phi[i]	= CorrT1METJet_phi[j];
            CorrT1METJet_rawPt[i]	= CorrT1METJet_rawPt[j];
          }
      }
    nCorrT1METJet = n;

    n = 0;
    try
      {
         n = indexmap["Electron"].size();
      }
    catch (...)
      {}
    if ( n > 0 )
      {
        std::vector<int>& index = indexmap["Electron"];
        for(int i=0; i < n; ++i)
          {
            int j = index[i];
            Electron_charge[i]	= Electron_charge[j];
            Electron_cleanmask[i]	= Electron_cleanmask[j];
            Electron_convVeto[i]	= Electron_convVeto[j];
            Electron_cutBased[i]	= Electron_cutBased[j];
            Electron_cutBased_HEEP[i]	= Electron_cutBased_HEEP[j];
            Electron_dEscaleDown[i]	= Electron_dEscaleDown[j];
            Electron_dEscaleUp[i]	= Electron_dEscaleUp[j];
            Electron_dEsigmaDown[i]	= Electron_dEsigmaDown[j];
            Electron_dEsigmaUp[i]	= Electron_dEsigmaUp[j];
            Electron_deltaEtaSC[i]	= Electron_deltaEtaSC[j];
            Electron_dr03EcalRecHitSumEt[i]	= Electron_dr03EcalRecHitSumEt[j];
            Electron_dr03HcalDepth1TowerSumEt[i]	= Electron_dr03HcalDepth1TowerSumEt[j];
            Electron_dr03TkSumPt[i]	= Electron_dr03TkSumPt[j];
            Electron_dr03TkSumPtHEEP[i]	= Electron_dr03TkSumPtHEEP[j];
            Electron_dxy[i]	= Electron_dxy[j];
            Electron_dxyErr[i]	= Electron_dxyErr[j];
            Electron_dz[i]	= Electron_dz[j];
            Electron_dzErr[i]	= Electron_dzErr[j];
            Electron_eCorr[i]	= Electron_eCorr[j];
            Electron_eInvMinusPInv[i]	= Electron_eInvMinusPInv[j];
            Electron_energyErr[i]	= Electron_energyErr[j];
            Electron_eta[i]	= Electron_eta[j];
            Electron_genPartFlav[i]	= Electron_genPartFlav[j];
            Electron_genPartIdx[i]	= Electron_genPartIdx[j];
            Electron_hoe[i]	= Electron_hoe[j];
            Electron_ip3d[i]	= Electron_ip3d[j];
            Electron_isPFcand[i]	= Electron_isPFcand[j];
            Electron_jetIdx[i]	= Electron_jetIdx[j];
            Electron_jetNDauCharged[i]	= Electron_jetNDauCharged[j];
            Electron_jetPtRelv2[i]	= Electron_jetPtRelv2[j];
            Electron_jetRelIso[i]	= Electron_jetRelIso[j];
            Electron_lostHits[i]	= Electron_lostHits[j];
            Electron_mass[i]	= Electron_mass[j];
            Electron_miniPFRelIso_all[i]	= Electron_miniPFRelIso_all[j];
            Electron_miniPFRelIso_chg[i]	= Electron_miniPFRelIso_chg[j];
            Electron_mvaFall17V2Iso[i]	= Electron_mvaFall17V2Iso[j];
            Electron_mvaFall17V2Iso_WP80[i]	= Electron_mvaFall17V2Iso_WP80[j];
            Electron_mvaFall17V2Iso_WP90[i]	= Electron_mvaFall17V2Iso_WP90[j];
            Electron_mvaFall17V2Iso_WPL[i]	= Electron_mvaFall17V2Iso_WPL[j];
            Electron_mvaFall17V2noIso[i]	= Electron_mvaFall17V2noIso[j];
            Electron_mvaFall17V2noIso_WP80[i]	= Electron_mvaFall17V2noIso_WP80[j];
            Electron_mvaFall17V2noIso_WP90[i]	= Electron_mvaFall17V2noIso_WP90[j];
            Electron_mvaFall17V2noIso_WPL[i]	= Electron_mvaFall17V2noIso_WPL[j];
            Electron_mvaTTH[i]	= Electron_mvaTTH[j];
            Electron_pdgId[i]	= Electron_pdgId[j];
            Electron_pfRelIso03_all[i]	= Electron_pfRelIso03_all[j];
            Electron_pfRelIso03_chg[i]	= Electron_pfRelIso03_chg[j];
            Electron_phi[i]	= Electron_phi[j];
            Electron_photonIdx[i]	= Electron_photonIdx[j];
            Electron_pt[i]	= Electron_pt[j];
            Electron_r9[i]	= Electron_r9[j];
            Electron_scEtOverPt[i]	= Electron_scEtOverPt[j];
            Electron_seedGain[i]	= Electron_seedGain[j];
            Electron_sieie[i]	= Electron_sieie[j];
            Electron_sip3d[i]	= Electron_sip3d[j];
            Electron_tightCharge[i]	= Electron_tightCharge[j];
            Electron_vidNestedWPBitmap[i]	= Electron_vidNestedWPBitmap[j];
            Electron_vidNestedWPBitmapHEEP[i]	= Electron_vidNestedWPBitmapHEEP[j];
          }
      }
    nElectron = n;

    n = 0;
    try
      {
         n = indexmap["FatJet"].size();
      }
    catch (...)
      {}
    if ( n > 0 )
      {
        std::vector<int>& index = indexmap["FatJet"];
        for(int i=0; i < n; ++i)
          {
            int j = index[i];
            FatJet_area[i]	= FatJet_area[j];
            FatJet_btagCSVV2[i]	= FatJet_btagCSVV2[j];
            FatJet_btagDDBvLV2[i]	= FatJet_btagDDBvLV2[j];
            FatJet_btagDDCvBV2[i]	= FatJet_btagDDCvBV2[j];
            FatJet_btagDDCvLV2[i]	= FatJet_btagDDCvLV2[j];
            FatJet_btagDeepB[i]	= FatJet_btagDeepB[j];
            FatJet_btagHbb[i]	= FatJet_btagHbb[j];
            FatJet_corr_JEC[i]	= FatJet_corr_JEC[j];
            FatJet_corr_JER[i]	= FatJet_corr_JER[j];
            FatJet_corr_JMR[i]	= FatJet_corr_JMR[j];
            FatJet_corr_JMS[i]	= FatJet_corr_JMS[j];
            FatJet_deepTagMD_H4qvsQCD[i]	= FatJet_deepTagMD_H4qvsQCD[j];
            FatJet_deepTagMD_HbbvsQCD[i]	= FatJet_deepTagMD_HbbvsQCD[j];
            FatJet_deepTagMD_TvsQCD[i]	= FatJet_deepTagMD_TvsQCD[j];
            FatJet_deepTagMD_WvsQCD[i]	= FatJet_deepTagMD_WvsQCD[j];
            FatJet_deepTagMD_ZHbbvsQCD[i]	= FatJet_deepTagMD_ZHbbvsQCD[j];
            FatJet_deepTagMD_ZHccvsQCD[i]	= FatJet_deepTagMD_ZHccvsQCD[j];
            FatJet_deepTagMD_ZbbvsQCD[i]	= FatJet_deepTagMD_ZbbvsQCD[j];
            FatJet_deepTagMD_ZvsQCD[i]	= FatJet_deepTagMD_ZvsQCD[j];
            FatJet_deepTagMD_bbvsLight[i]	= FatJet_deepTagMD_bbvsLight[j];
            FatJet_deepTagMD_ccvsLight[i]	= FatJet_deepTagMD_ccvsLight[j];
            FatJet_deepTag_H[i]	= FatJet_deepTag_H[j];
            FatJet_deepTag_QCD[i]	= FatJet_deepTag_QCD[j];
            FatJet_deepTag_QCDothers[i]	= FatJet_deepTag_QCDothers[j];
            FatJet_deepTag_TvsQCD[i]	= FatJet_deepTag_TvsQCD[j];
            FatJet_deepTag_WvsQCD[i]	= FatJet_deepTag_WvsQCD[j];
            FatJet_deepTag_ZvsQCD[i]	= FatJet_deepTag_ZvsQCD[j];
            FatJet_electronIdx3SJ[i]	= FatJet_electronIdx3SJ[j];
            FatJet_eta[i]	= FatJet_eta[j];
            FatJet_genJetAK8Idx[i]	= FatJet_genJetAK8Idx[j];
            FatJet_hadronFlavour[i]	= FatJet_hadronFlavour[j];
            FatJet_jetId[i]	= FatJet_jetId[j];
            FatJet_lsf3[i]	= FatJet_lsf3[j];
            FatJet_mass[i]	= FatJet_mass_nom[j];
            FatJet_mass_jerDown[i]	= FatJet_mass_jerDown[j];
            FatJet_mass_jerUp[i]	= FatJet_mass_jerUp[j];
            FatJet_mass_jesTotalDown[i]	= FatJet_mass_jesTotalDown[j];
            FatJet_mass_jesTotalUp[i]	= FatJet_mass_jesTotalUp[j];
            FatJet_mass_jmrDown[i]	= FatJet_mass_jmrDown[j];
            FatJet_mass_jmrUp[i]	= FatJet_mass_jmrUp[j];
            FatJet_mass_jmsDown[i]	= FatJet_mass_jmsDown[j];
            FatJet_mass_jmsUp[i]	= FatJet_mass_jmsUp[j];
            FatJet_mass_nom[i]	= FatJet_mass_nom[j];
            FatJet_mass_raw[i]	= FatJet_mass_raw[j];
            FatJet_msoftdrop[i]	= FatJet_msoftdrop_nom[j];
            FatJet_msoftdrop_corr_JMR[i]	= FatJet_msoftdrop_corr_JMR[j];
            FatJet_msoftdrop_corr_JMS[i]	= FatJet_msoftdrop_corr_JMS[j];
            FatJet_msoftdrop_corr_PUPPI[i]	= FatJet_msoftdrop_corr_PUPPI[j];
            FatJet_msoftdrop_jerDown[i]	= FatJet_msoftdrop_jerDown[j];
            FatJet_msoftdrop_jerUp[i]	= FatJet_msoftdrop_jerUp[j];
            FatJet_msoftdrop_jesTotalDown[i]	= FatJet_msoftdrop_jesTotalDown[j];
            FatJet_msoftdrop_jesTotalUp[i]	= FatJet_msoftdrop_jesTotalUp[j];
            FatJet_msoftdrop_jmrDown[i]	= FatJet_msoftdrop_jmrDown[j];
            FatJet_msoftdrop_jmrUp[i]	= FatJet_msoftdrop_jmrUp[j];
            FatJet_msoftdrop_jmsDown[i]	= FatJet_msoftdrop_jmsDown[j];
            FatJet_msoftdrop_jmsUp[i]	= FatJet_msoftdrop_jmsUp[j];
            FatJet_msoftdrop_nom[i]	= FatJet_msoftdrop_nom[j];
            FatJet_msoftdrop_raw[i]	= FatJet_msoftdrop_raw[j];
            FatJet_msoftdrop_tau21DDT_jerDown[i]	= FatJet_msoftdrop_tau21DDT_jerDown[j];
            FatJet_msoftdrop_tau21DDT_jerUp[i]	= FatJet_msoftdrop_tau21DDT_jerUp[j];
            FatJet_msoftdrop_tau21DDT_jmrDown[i]	= FatJet_msoftdrop_tau21DDT_jmrDown[j];
            FatJet_msoftdrop_tau21DDT_jmrUp[i]	= FatJet_msoftdrop_tau21DDT_jmrUp[j];
            FatJet_msoftdrop_tau21DDT_jmsDown[i]	= FatJet_msoftdrop_tau21DDT_jmsDown[j];
            FatJet_msoftdrop_tau21DDT_jmsUp[i]	= FatJet_msoftdrop_tau21DDT_jmsUp[j];
            FatJet_msoftdrop_tau21DDT_nom[i]	= FatJet_msoftdrop_tau21DDT_nom[j];
            FatJet_muonIdx3SJ[i]	= FatJet_muonIdx3SJ[j];
            FatJet_n2b1[i]	= FatJet_n2b1[j];
            FatJet_n3b1[i]	= FatJet_n3b1[j];
            FatJet_nBHadrons[i]	= FatJet_nBHadrons[j];
            FatJet_nCHadrons[i]	= FatJet_nCHadrons[j];
            FatJet_nConstituents[i]	= FatJet_nConstituents[j];
            FatJet_particleNetMD_QCD[i]	= FatJet_particleNetMD_QCD[j];
            FatJet_particleNetMD_Xbb[i]	= FatJet_particleNetMD_Xbb[j];
            FatJet_particleNetMD_Xcc[i]	= FatJet_particleNetMD_Xcc[j];
            FatJet_particleNetMD_Xqq[i]	= FatJet_particleNetMD_Xqq[j];
            FatJet_particleNet_H4qvsQCD[i]	= FatJet_particleNet_H4qvsQCD[j];
            FatJet_particleNet_HbbvsQCD[i]	= FatJet_particleNet_HbbvsQCD[j];
            FatJet_particleNet_HccvsQCD[i]	= FatJet_particleNet_HccvsQCD[j];
            FatJet_particleNet_QCD[i]	= FatJet_particleNet_QCD[j];
            FatJet_particleNet_TvsQCD[i]	= FatJet_particleNet_TvsQCD[j];
            FatJet_particleNet_WvsQCD[i]	= FatJet_particleNet_WvsQCD[j];
            FatJet_particleNet_ZvsQCD[i]	= FatJet_particleNet_ZvsQCD[j];
            FatJet_particleNet_mass[i]	= FatJet_particleNet_mass[j];
            FatJet_phi[i]	= FatJet_phi[j];
            FatJet_pt[i]	= FatJet_pt_nom[j];
            FatJet_pt_jerDown[i]	= FatJet_pt_jerDown[j];
            FatJet_pt_jerUp[i]	= FatJet_pt_jerUp[j];
            FatJet_pt_jesTotalDown[i]	= FatJet_pt_jesTotalDown[j];
            FatJet_pt_jesTotalUp[i]	= FatJet_pt_jesTotalUp[j];
            FatJet_pt_nom[i]	= FatJet_pt_nom[j];
            FatJet_pt_raw[i]	= FatJet_pt_raw[j];
            FatJet_rawFactor[i]	= FatJet_rawFactor[j];
            FatJet_subJetIdx1[i]	= FatJet_subJetIdx1[j];
            FatJet_subJetIdx2[i]	= FatJet_subJetIdx2[j];
            FatJet_tau1[i]	= FatJet_tau1[j];
            FatJet_tau2[i]	= FatJet_tau2[j];
            FatJet_tau3[i]	= FatJet_tau3[j];
            FatJet_tau4[i]	= FatJet_tau4[j];
          }
      }
    nFatJet = n;

    n = 0;
    try
      {
         n = indexmap["FsrPhoton"].size();
      }
    catch (...)
      {}
    if ( n > 0 )
      {
        std::vector<int>& index = indexmap["FsrPhoton"];
        for(int i=0; i < n; ++i)
          {
            int j = index[i];
            FsrPhoton_dROverEt2[i]	= FsrPhoton_dROverEt2[j];
            FsrPhoton_eta[i]	= FsrPhoton_eta[j];
            FsrPhoton_muonIdx[i]	= FsrPhoton_muonIdx[j];
            FsrPhoton_phi[i]	= FsrPhoton_phi[j];
            FsrPhoton_pt[i]	= FsrPhoton_pt[j];
            FsrPhoton_relIso03[i]	= FsrPhoton_relIso03[j];
          }
      }
    nFsrPhoton = n;

    n = 0;
    try
      {
         n = indexmap["GenIsolatedPhoton"].size();
      }
    catch (...)
      {}
    if ( n > 0 )
      {
        std::vector<int>& index = indexmap["GenIsolatedPhoton"];
        for(int i=0; i < n; ++i)
          {
            int j = index[i];
            GenIsolatedPhoton_eta[i]	= GenIsolatedPhoton_eta[j];
            GenIsolatedPhoton_mass[i]	= GenIsolatedPhoton_mass[j];
            GenIsolatedPhoton_phi[i]	= GenIsolatedPhoton_phi[j];
            GenIsolatedPhoton_pt[i]	= GenIsolatedPhoton_pt[j];
          }
      }
    nGenIsolatedPhoton = n;

    n = 0;
    try
      {
         n = indexmap["GenJet"].size();
      }
    catch (...)
      {}
    if ( n > 0 )
      {
        std::vector<int>& index = indexmap["GenJet"];
        for(int i=0; i < n; ++i)
          {
            int j = index[i];
            GenJet_eta[i]	= GenJet_eta[j];
            GenJet_hadronFlavour[i]	= GenJet_hadronFlavour[j];
            GenJet_mass[i]	= GenJet_mass[j];
            GenJet_partonFlavour[i]	= GenJet_partonFlavour[j];
            GenJet_phi[i]	= GenJet_phi[j];
            GenJet_pt[i]	= GenJet_pt[j];
          }
      }
    nGenJet = n;

    n = 0;
    try
      {
         n = indexmap["GenJetAK8"].size();
      }
    catch (...)
      {}
    if ( n > 0 )
      {
        std::vector<int>& index = indexmap["GenJetAK8"];
        for(int i=0; i < n; ++i)
          {
            int j = index[i];
            GenJetAK8_eta[i]	= GenJetAK8_eta[j];
            GenJetAK8_hadronFlavour[i]	= GenJetAK8_hadronFlavour[j];
            GenJetAK8_mass[i]	= GenJetAK8_mass[j];
            GenJetAK8_partonFlavour[i]	= GenJetAK8_partonFlavour[j];
            GenJetAK8_phi[i]	= GenJetAK8_phi[j];
            GenJetAK8_pt[i]	= GenJetAK8_pt[j];
          }
      }
    nGenJetAK8 = n;

    n = 0;
    try
      {
         n = indexmap["GenPart"].size();
      }
    catch (...)
      {}
    if ( n > 0 )
      {
        std::vector<int>& index = indexmap["GenPart"];
        for(int i=0; i < n; ++i)
          {
            int j = index[i];
            GenPart_eta[i]	= GenPart_eta[j];
            GenPart_genPartIdxMother[i]	= GenPart_genPartIdxMother[j];
            GenPart_mass[i]	= GenPart_mass[j];
            GenPart_pdgId[i]	= GenPart_pdgId[j];
            GenPart_phi[i]	= GenPart_phi[j];
            GenPart_pt[i]	= GenPart_pt[j];
            GenPart_status[i]	= GenPart_status[j];
            GenPart_statusFlags[i]	= GenPart_statusFlags[j];
          }
      }
    nGenPart = n;

    n = 0;
    try
      {
         n = indexmap["IsoTrack"].size();
      }
    catch (...)
      {}
    if ( n > 0 )
      {
        std::vector<int>& index = indexmap["IsoTrack"];
        for(int i=0; i < n; ++i)
          {
            int j = index[i];
            IsoTrack_charge[i]	= IsoTrack_charge[j];
            IsoTrack_dxy[i]	= IsoTrack_dxy[j];
            IsoTrack_dz[i]	= IsoTrack_dz[j];
            IsoTrack_eta[i]	= IsoTrack_eta[j];
            IsoTrack_fromPV[i]	= IsoTrack_fromPV[j];
            IsoTrack_isFromLostTrack[i]	= IsoTrack_isFromLostTrack[j];
            IsoTrack_isHighPurityTrack[i]	= IsoTrack_isHighPurityTrack[j];
            IsoTrack_isPFcand[i]	= IsoTrack_isPFcand[j];
            IsoTrack_miniPFRelIso_all[i]	= IsoTrack_miniPFRelIso_all[j];
            IsoTrack_miniPFRelIso_chg[i]	= IsoTrack_miniPFRelIso_chg[j];
            IsoTrack_pdgId[i]	= IsoTrack_pdgId[j];
            IsoTrack_pfRelIso03_all[i]	= IsoTrack_pfRelIso03_all[j];
            IsoTrack_pfRelIso03_chg[i]	= IsoTrack_pfRelIso03_chg[j];
            IsoTrack_phi[i]	= IsoTrack_phi[j];
            IsoTrack_pt[i]	= IsoTrack_pt[j];
          }
      }
    nIsoTrack = n;

    n = 0;
    try
      {
         n = indexmap["Jet"].size();
      }
    catch (...)
      {}
    if ( n > 0 )
      {
        std::vector<int>& index = indexmap["Jet"];
        for(int i=0; i < n; ++i)
          {
            int j = index[i];
            Jet_area[i]	= Jet_area[j];
            Jet_bRegCorr[i]	= Jet_bRegCorr[j];
            Jet_bRegRes[i]	= Jet_bRegRes[j];
            Jet_btagCSVV2[i]	= Jet_btagCSVV2[j];
            Jet_btagDeepB[i]	= Jet_btagDeepB[j];
            Jet_btagDeepCvB[i]	= Jet_btagDeepCvB[j];
            Jet_btagDeepCvL[i]	= Jet_btagDeepCvL[j];
            Jet_btagDeepFlavB[i]	= Jet_btagDeepFlavB[j];
            Jet_btagDeepFlavCvB[i]	= Jet_btagDeepFlavCvB[j];
            Jet_btagDeepFlavCvL[i]	= Jet_btagDeepFlavCvL[j];
            Jet_btagDeepFlavQG[i]	= Jet_btagDeepFlavQG[j];
            Jet_cRegCorr[i]	= Jet_cRegCorr[j];
            Jet_cRegRes[i]	= Jet_cRegRes[j];
            Jet_chEmEF[i]	= Jet_chEmEF[j];
            Jet_chFPV0EF[i]	= Jet_chFPV0EF[j];
            Jet_chHEF[i]	= Jet_chHEF[j];
            Jet_cleanmask[i]	= Jet_cleanmask[j];
            Jet_corr_JEC[i]	= Jet_corr_JEC[j];
            Jet_corr_JER[i]	= Jet_corr_JER[j];
            Jet_electronIdx1[i]	= Jet_electronIdx1[j];
            Jet_electronIdx2[i]	= Jet_electronIdx2[j];
            Jet_eta[i]	= Jet_eta[j];
            Jet_genJetIdx[i]	= Jet_genJetIdx[j];
            Jet_hadronFlavour[i]	= Jet_hadronFlavour[j];
            Jet_hfadjacentEtaStripsSize[i]	= Jet_hfadjacentEtaStripsSize[j];
            Jet_hfcentralEtaStripSize[i]	= Jet_hfcentralEtaStripSize[j];
            Jet_hfsigmaEtaEta[i]	= Jet_hfsigmaEtaEta[j];
            Jet_hfsigmaPhiPhi[i]	= Jet_hfsigmaPhiPhi[j];
            Jet_jetId[i]	= Jet_jetId[j];
            Jet_mass[i]	= Jet_mass_nom[j];
            Jet_mass_jerDown[i]	= Jet_mass_jerDown[j];
            Jet_mass_jerUp[i]	= Jet_mass_jerUp[j];
            Jet_mass_jesTotalDown[i]	= Jet_mass_jesTotalDown[j];
            Jet_mass_jesTotalUp[i]	= Jet_mass_jesTotalUp[j];
            Jet_mass_nom[i]	= Jet_mass_nom[j];
            Jet_mass_raw[i]	= Jet_mass_raw[j];
            Jet_muEF[i]	= Jet_muEF[j];
            Jet_muonIdx1[i]	= Jet_muonIdx1[j];
            Jet_muonIdx2[i]	= Jet_muonIdx2[j];
            Jet_muonSubtrFactor[i]	= Jet_muonSubtrFactor[j];
            Jet_nConstituents[i]	= Jet_nConstituents[j];
            Jet_nElectrons[i]	= Jet_nElectrons[j];
            Jet_nMuons[i]	= Jet_nMuons[j];
            Jet_neEmEF[i]	= Jet_neEmEF[j];
            Jet_neHEF[i]	= Jet_neHEF[j];
            Jet_partonFlavour[i]	= Jet_partonFlavour[j];
            Jet_phi[i]	= Jet_phi[j];
            Jet_pt[i]	= Jet_pt_nom[j];
            Jet_pt_jerDown[i]	= Jet_pt_jerDown[j];
            Jet_pt_jerUp[i]	= Jet_pt_jerUp[j];
            Jet_pt_jesTotalDown[i]	= Jet_pt_jesTotalDown[j];
            Jet_pt_jesTotalUp[i]	= Jet_pt_jesTotalUp[j];
            Jet_pt_nom[i]	= Jet_pt_nom[j];
            Jet_pt_raw[i]	= Jet_pt_raw[j];
            Jet_puId[i]	= Jet_puId[j];
            Jet_puIdDisc[i]	= Jet_puIdDisc[j];
            Jet_qgl[i]	= Jet_qgl[j];
            Jet_rawFactor[i]	= Jet_rawFactor[j];
          }
      }
    nJet = n;

    n = 0;
    try
      {
         n = indexmap["LHEPart"].size();
      }
    catch (...)
      {}
    if ( n > 0 )
      {
        std::vector<int>& index = indexmap["LHEPart"];
        for(int i=0; i < n; ++i)
          {
            int j = index[i];
            LHEPart_eta[i]	= LHEPart_eta[j];
            LHEPart_incomingpz[i]	= LHEPart_incomingpz[j];
            LHEPart_mass[i]	= LHEPart_mass[j];
            LHEPart_pdgId[i]	= LHEPart_pdgId[j];
            LHEPart_phi[i]	= LHEPart_phi[j];
            LHEPart_pt[i]	= LHEPart_pt[j];
            LHEPart_spin[i]	= LHEPart_spin[j];
            LHEPart_status[i]	= LHEPart_status[j];
          }
      }
    nLHEPart = n;

    n = 0;
    try
      {
         n = indexmap["Muon"].size();
      }
    catch (...)
      {}
    if ( n > 0 )
      {
        std::vector<int>& index = indexmap["Muon"];
        for(int i=0; i < n; ++i)
          {
            int j = index[i];
            Muon_charge[i]	= Muon_charge[j];
            Muon_cleanmask[i]	= Muon_cleanmask[j];
            Muon_dxy[i]	= Muon_dxy[j];
            Muon_dxyErr[i]	= Muon_dxyErr[j];
            Muon_dxybs[i]	= Muon_dxybs[j];
            Muon_dz[i]	= Muon_dz[j];
            Muon_dzErr[i]	= Muon_dzErr[j];
            Muon_eta[i]	= Muon_eta[j];
            Muon_fsrPhotonIdx[i]	= Muon_fsrPhotonIdx[j];
            Muon_genPartFlav[i]	= Muon_genPartFlav[j];
            Muon_genPartIdx[i]	= Muon_genPartIdx[j];
            Muon_highPtId[i]	= Muon_highPtId[j];
            Muon_highPurity[i]	= Muon_highPurity[j];
            Muon_inTimeMuon[i]	= Muon_inTimeMuon[j];
            Muon_ip3d[i]	= Muon_ip3d[j];
            Muon_isGlobal[i]	= Muon_isGlobal[j];
            Muon_isPFcand[i]	= Muon_isPFcand[j];
            Muon_isStandalone[i]	= Muon_isStandalone[j];
            Muon_isTracker[i]	= Muon_isTracker[j];
            Muon_jetIdx[i]	= Muon_jetIdx[j];
            Muon_jetNDauCharged[i]	= Muon_jetNDauCharged[j];
            Muon_jetPtRelv2[i]	= Muon_jetPtRelv2[j];
            Muon_jetRelIso[i]	= Muon_jetRelIso[j];
            Muon_looseId[i]	= Muon_looseId[j];
            Muon_mass[i]	= Muon_mass[j];
            Muon_mediumId[i]	= Muon_mediumId[j];
            Muon_mediumPromptId[i]	= Muon_mediumPromptId[j];
            Muon_miniIsoId[i]	= Muon_miniIsoId[j];
            Muon_miniPFRelIso_all[i]	= Muon_miniPFRelIso_all[j];
            Muon_miniPFRelIso_chg[i]	= Muon_miniPFRelIso_chg[j];
            Muon_multiIsoId[i]	= Muon_multiIsoId[j];
            Muon_mvaId[i]	= Muon_mvaId[j];
            Muon_mvaLowPt[i]	= Muon_mvaLowPt[j];
            Muon_mvaLowPtId[i]	= Muon_mvaLowPtId[j];
            Muon_mvaTTH[i]	= Muon_mvaTTH[j];
            Muon_nStations[i]	= Muon_nStations[j];
            Muon_nTrackerLayers[i]	= Muon_nTrackerLayers[j];
            Muon_pdgId[i]	= Muon_pdgId[j];
            Muon_pfIsoId[i]	= Muon_pfIsoId[j];
            Muon_pfRelIso03_all[i]	= Muon_pfRelIso03_all[j];
            Muon_pfRelIso03_chg[i]	= Muon_pfRelIso03_chg[j];
            Muon_pfRelIso04_all[i]	= Muon_pfRelIso04_all[j];
            Muon_phi[i]	= Muon_phi[j];
            Muon_pt[i]	= Muon_pt[j];
            Muon_ptErr[i]	= Muon_ptErr[j];
            Muon_puppiIsoId[i]	= Muon_puppiIsoId[j];
            Muon_segmentComp[i]	= Muon_segmentComp[j];
            Muon_sip3d[i]	= Muon_sip3d[j];
            Muon_softId[i]	= Muon_softId[j];
            Muon_softMva[i]	= Muon_softMva[j];
            Muon_softMvaId[i]	= Muon_softMvaId[j];
            Muon_tightCharge[i]	= Muon_tightCharge[j];
            Muon_tightId[i]	= Muon_tightId[j];
            Muon_tkIsoId[i]	= Muon_tkIsoId[j];
            Muon_tkRelIso[i]	= Muon_tkRelIso[j];
            Muon_triggerIdLoose[i]	= Muon_triggerIdLoose[j];
            Muon_tunepRelPt[i]	= Muon_tunepRelPt[j];
          }
      }
    nMuon = n;

    n = 0;
    try
      {
         n = indexmap["Photon"].size();
      }
    catch (...)
      {}
    if ( n > 0 )
      {
        std::vector<int>& index = indexmap["Photon"];
        for(int i=0; i < n; ++i)
          {
            int j = index[i];
            Photon_charge[i]	= Photon_charge[j];
            Photon_cleanmask[i]	= Photon_cleanmask[j];
            Photon_cutBased[i]	= Photon_cutBased[j];
            Photon_cutBased_Fall17V1Bitmap[i]	= Photon_cutBased_Fall17V1Bitmap[j];
            Photon_dEscaleDown[i]	= Photon_dEscaleDown[j];
            Photon_dEscaleUp[i]	= Photon_dEscaleUp[j];
            Photon_dEsigmaDown[i]	= Photon_dEsigmaDown[j];
            Photon_dEsigmaUp[i]	= Photon_dEsigmaUp[j];
            Photon_eCorr[i]	= Photon_eCorr[j];
            Photon_electronIdx[i]	= Photon_electronIdx[j];
            Photon_electronVeto[i]	= Photon_electronVeto[j];
            Photon_energyErr[i]	= Photon_energyErr[j];
            Photon_eta[i]	= Photon_eta[j];
            Photon_genPartFlav[i]	= Photon_genPartFlav[j];
            Photon_genPartIdx[i]	= Photon_genPartIdx[j];
            Photon_hoe[i]	= Photon_hoe[j];
            Photon_isScEtaEB[i]	= Photon_isScEtaEB[j];
            Photon_isScEtaEE[i]	= Photon_isScEtaEE[j];
            Photon_jetIdx[i]	= Photon_jetIdx[j];
            Photon_mass[i]	= Photon_mass[j];
            Photon_mvaID[i]	= Photon_mvaID[j];
            Photon_mvaID_Fall17V1p1[i]	= Photon_mvaID_Fall17V1p1[j];
            Photon_mvaID_WP80[i]	= Photon_mvaID_WP80[j];
            Photon_mvaID_WP90[i]	= Photon_mvaID_WP90[j];
            Photon_pdgId[i]	= Photon_pdgId[j];
            Photon_pfRelIso03_all[i]	= Photon_pfRelIso03_all[j];
            Photon_pfRelIso03_chg[i]	= Photon_pfRelIso03_chg[j];
            Photon_phi[i]	= Photon_phi[j];
            Photon_pixelSeed[i]	= Photon_pixelSeed[j];
            Photon_pt[i]	= Photon_pt[j];
            Photon_r9[i]	= Photon_r9[j];
            Photon_seedGain[i]	= Photon_seedGain[j];
            Photon_sieie[i]	= Photon_sieie[j];
            Photon_vidNestedWPBitmap[i]	= Photon_vidNestedWPBitmap[j];
          }
      }
    nPhoton = n;

    n = 0;
    try
      {
         n = indexmap["SubGenJetAK8"].size();
      }
    catch (...)
      {}
    if ( n > 0 )
      {
        std::vector<int>& index = indexmap["SubGenJetAK8"];
        for(int i=0; i < n; ++i)
          {
            int j = index[i];
            SubGenJetAK8_eta[i]	= SubGenJetAK8_eta[j];
            SubGenJetAK8_mass[i]	= SubGenJetAK8_mass[j];
            SubGenJetAK8_phi[i]	= SubGenJetAK8_phi[j];
            SubGenJetAK8_pt[i]	= SubGenJetAK8_pt[j];
          }
      }
    nSubGenJetAK8 = n;

    n = 0;
    try
      {
         n = indexmap["SubJet"].size();
      }
    catch (...)
      {}
    if ( n > 0 )
      {
        std::vector<int>& index = indexmap["SubJet"];
        for(int i=0; i < n; ++i)
          {
            int j = index[i];
            SubJet_btagCSVV2[i]	= SubJet_btagCSVV2[j];
            SubJet_btagDeepB[i]	= SubJet_btagDeepB[j];
            SubJet_eta[i]	= SubJet_eta[j];
            SubJet_hadronFlavour[i]	= SubJet_hadronFlavour[j];
            SubJet_mass[i]	= SubJet_mass[j];
            SubJet_n2b1[i]	= SubJet_n2b1[j];
            SubJet_n3b1[i]	= SubJet_n3b1[j];
            SubJet_nBHadrons[i]	= SubJet_nBHadrons[j];
            SubJet_nCHadrons[i]	= SubJet_nCHadrons[j];
            SubJet_phi[i]	= SubJet_phi[j];
            SubJet_pt[i]	= SubJet_pt[j];
            SubJet_rawFactor[i]	= SubJet_rawFactor[j];
            SubJet_tau1[i]	= SubJet_tau1[j];
            SubJet_tau2[i]	= SubJet_tau2[j];
            SubJet_tau3[i]	= SubJet_tau3[j];
            SubJet_tau4[i]	= SubJet_tau4[j];
          }
      }
    nSubJet = n;

    n = 0;
    try
      {
         n = indexmap["Tau"].size();
      }
    catch (...)
      {}
    if ( n > 0 )
      {
        std::vector<int>& index = indexmap["Tau"];
        for(int i=0; i < n; ++i)
          {
            int j = index[i];
            Tau_charge[i]	= Tau_charge[j];
            Tau_chargedIso[i]	= Tau_chargedIso[j];
            Tau_cleanmask[i]	= Tau_cleanmask[j];
            Tau_decayMode[i]	= Tau_decayMode[j];
            Tau_dxy[i]	= Tau_dxy[j];
            Tau_dz[i]	= Tau_dz[j];
            Tau_eta[i]	= Tau_eta[j];
            Tau_genPartFlav[i]	= Tau_genPartFlav[j];
            Tau_genPartIdx[i]	= Tau_genPartIdx[j];
            Tau_idAntiEleDeadECal[i]	= Tau_idAntiEleDeadECal[j];
            Tau_idAntiMu[i]	= Tau_idAntiMu[j];
            Tau_idDecayModeOldDMs[i]	= Tau_idDecayModeOldDMs[j];
            Tau_idDeepTau2017v2p1VSe[i]	= Tau_idDeepTau2017v2p1VSe[j];
            Tau_idDeepTau2017v2p1VSjet[i]	= Tau_idDeepTau2017v2p1VSjet[j];
            Tau_idDeepTau2017v2p1VSmu[i]	= Tau_idDeepTau2017v2p1VSmu[j];
            Tau_jetIdx[i]	= Tau_jetIdx[j];
            Tau_leadTkDeltaEta[i]	= Tau_leadTkDeltaEta[j];
            Tau_leadTkDeltaPhi[i]	= Tau_leadTkDeltaPhi[j];
            Tau_leadTkPtOverTauPt[i]	= Tau_leadTkPtOverTauPt[j];
            Tau_mass[i]	= Tau_mass[j];
            Tau_neutralIso[i]	= Tau_neutralIso[j];
            Tau_phi[i]	= Tau_phi[j];
            Tau_photonsOutsideSignalCone[i]	= Tau_photonsOutsideSignalCone[j];
            Tau_pt[i]	= Tau_pt[j];
            Tau_puCorr[i]	= Tau_puCorr[j];
            Tau_rawDeepTau2017v2p1VSe[i]	= Tau_rawDeepTau2017v2p1VSe[j];
            Tau_rawDeepTau2017v2p1VSjet[i]	= Tau_rawDeepTau2017v2p1VSjet[j];
            Tau_rawDeepTau2017v2p1VSmu[i]	= Tau_rawDeepTau2017v2p1VSmu[j];
            Tau_rawIso[i]	= Tau_rawIso[j];
            Tau_rawIsodR03[i]	= Tau_rawIsodR03[j];
          }
      }
    nTau = n;

    n = 0;
    try
      {
         n = indexmap["TrigObj"].size();
      }
    catch (...)
      {}
    if ( n > 0 )
      {
        std::vector<int>& index = indexmap["TrigObj"];
        for(int i=0; i < n; ++i)
          {
            int j = index[i];
            TrigObj_eta[i]	= TrigObj_eta[j];
            TrigObj_filterBits[i]	= TrigObj_filterBits[j];
            TrigObj_id[i]	= TrigObj_id[j];
            TrigObj_l1charge[i]	= TrigObj_l1charge[j];
            TrigObj_l1iso[i]	= TrigObj_l1iso[j];
            TrigObj_l1pt[i]	= TrigObj_l1pt[j];
            TrigObj_l1pt_2[i]	= TrigObj_l1pt_2[j];
            TrigObj_l2pt[i]	= TrigObj_l2pt[j];
            TrigObj_phi[i]	= TrigObj_phi[j];
            TrigObj_pt[i]	= TrigObj_pt[j];
          }
      }
    nTrigObj = n;

    n = 0;
    try
      {
         n = indexmap["boostedTau"].size();
      }
    catch (...)
      {}
    if ( n > 0 )
      {
        std::vector<int>& index = indexmap["boostedTau"];
        for(int i=0; i < n; ++i)
          {
            int j = index[i];
            boostedTau_charge[i]	= boostedTau_charge[j];
            boostedTau_chargedIso[i]	= boostedTau_chargedIso[j];
            boostedTau_decayMode[i]	= boostedTau_decayMode[j];
            boostedTau_eta[i]	= boostedTau_eta[j];
            boostedTau_genPartFlav[i]	= boostedTau_genPartFlav[j];
            boostedTau_genPartIdx[i]	= boostedTau_genPartIdx[j];
            boostedTau_idAntiEle2018[i]	= boostedTau_idAntiEle2018[j];
            boostedTau_idAntiMu[i]	= boostedTau_idAntiMu[j];
            boostedTau_idMVAnewDM2017v2[i]	= boostedTau_idMVAnewDM2017v2[j];
            boostedTau_idMVAoldDM2017v2[i]	= boostedTau_idMVAoldDM2017v2[j];
            boostedTau_idMVAoldDMdR032017v2[i]	= boostedTau_idMVAoldDMdR032017v2[j];
            boostedTau_jetIdx[i]	= boostedTau_jetIdx[j];
            boostedTau_leadTkDeltaEta[i]	= boostedTau_leadTkDeltaEta[j];
            boostedTau_leadTkDeltaPhi[i]	= boostedTau_leadTkDeltaPhi[j];
            boostedTau_leadTkPtOverTauPt[i]	= boostedTau_leadTkPtOverTauPt[j];
            boostedTau_mass[i]	= boostedTau_mass[j];
            boostedTau_neutralIso[i]	= boostedTau_neutralIso[j];
            boostedTau_phi[i]	= boostedTau_phi[j];
            boostedTau_photonsOutsideSignalCone[i]	= boostedTau_photonsOutsideSignalCone[j];
            boostedTau_pt[i]	= boostedTau_pt[j];
            boostedTau_puCorr[i]	= boostedTau_puCorr[j];
            boostedTau_rawAntiEle2018[i]	= boostedTau_rawAntiEle2018[j];
            boostedTau_rawAntiEleCat2018[i]	= boostedTau_rawAntiEleCat2018[j];
            boostedTau_rawIso[i]	= boostedTau_rawIso[j];
            boostedTau_rawIsodR03[i]	= boostedTau_rawIsodR03[j];
            boostedTau_rawMVAnewDM2017v2[i]	= boostedTau_rawMVAnewDM2017v2[j];
            boostedTau_rawMVAoldDM2017v2[i]	= boostedTau_rawMVAoldDM2017v2[j];
            boostedTau_rawMVAoldDMdR032017v2[i]	= boostedTau_rawMVAoldDMdR032017v2[j];
          }
      }
    nboostedTau = n;
  }

  //--------------------------------------------------------------------------
  // A read-only buffer 
  eventBuffer() : input(0), output(0), choose(std::map<std::string, bool>()) {}
  eventBuffer(itreestream& stream, std::string varlist="")
  : input(&stream),
    output(0),
    choose(std::map<std::string, bool>())
  {
    if ( !input->good() ) 
      {
        std::cout << "eventBuffer - please check stream!" 
                  << std::endl;
	    exit(0);
      }

    initBuffers();
    
    // default is to select all branches      
    bool DEFAULT = varlist == "";
    choose["CaloMET_phi"]	= DEFAULT;
    choose["CaloMET_pt"]	= DEFAULT;
    choose["CaloMET_sumEt"]	= DEFAULT;
    choose["ChsMET_phi"]	= DEFAULT;
    choose["ChsMET_pt"]	= DEFAULT;
    choose["ChsMET_sumEt"]	= DEFAULT;
    choose["CorrT1METJet_area"]	= DEFAULT;
    choose["CorrT1METJet_eta"]	= DEFAULT;
    choose["CorrT1METJet_muonSubtrFactor"]	= DEFAULT;
    choose["CorrT1METJet_phi"]	= DEFAULT;
    choose["CorrT1METJet_rawPt"]	= DEFAULT;
    choose["DeepMETResolutionTune_phi"]	= DEFAULT;
    choose["DeepMETResolutionTune_pt"]	= DEFAULT;
    choose["DeepMETResponseTune_phi"]	= DEFAULT;
    choose["DeepMETResponseTune_pt"]	= DEFAULT;
    choose["Electron_charge"]	= DEFAULT;
    choose["Electron_cleanmask"]	= DEFAULT;
    choose["Electron_convVeto"]	= DEFAULT;
    choose["Electron_cutBased"]	= DEFAULT;
    choose["Electron_cutBased_HEEP"]	= DEFAULT;
    choose["Electron_dEscaleDown"]	= DEFAULT;
    choose["Electron_dEscaleUp"]	= DEFAULT;
    choose["Electron_dEsigmaDown"]	= DEFAULT;
    choose["Electron_dEsigmaUp"]	= DEFAULT;
    choose["Electron_deltaEtaSC"]	= DEFAULT;
    choose["Electron_dr03EcalRecHitSumEt"]	= DEFAULT;
    choose["Electron_dr03HcalDepth1TowerSumEt"]	= DEFAULT;
    choose["Electron_dr03TkSumPt"]	= DEFAULT;
    choose["Electron_dr03TkSumPtHEEP"]	= DEFAULT;
    choose["Electron_dxy"]	= DEFAULT;
    choose["Electron_dxyErr"]	= DEFAULT;
    choose["Electron_dz"]	= DEFAULT;
    choose["Electron_dzErr"]	= DEFAULT;
    choose["Electron_eCorr"]	= DEFAULT;
    choose["Electron_eInvMinusPInv"]	= DEFAULT;
    choose["Electron_energyErr"]	= DEFAULT;
    choose["Electron_eta"]	= DEFAULT;
    choose["Electron_genPartFlav"]	= DEFAULT;
    choose["Electron_genPartIdx"]	= DEFAULT;
    choose["Electron_hoe"]	= DEFAULT;
    choose["Electron_ip3d"]	= DEFAULT;
    choose["Electron_isPFcand"]	= DEFAULT;
    choose["Electron_jetIdx"]	= DEFAULT;
    choose["Electron_jetNDauCharged"]	= DEFAULT;
    choose["Electron_jetPtRelv2"]	= DEFAULT;
    choose["Electron_jetRelIso"]	= DEFAULT;
    choose["Electron_lostHits"]	= DEFAULT;
    choose["Electron_mass"]	= DEFAULT;
    choose["Electron_miniPFRelIso_all"]	= DEFAULT;
    choose["Electron_miniPFRelIso_chg"]	= DEFAULT;
    choose["Electron_mvaFall17V2Iso"]	= DEFAULT;
    choose["Electron_mvaFall17V2Iso_WP80"]	= DEFAULT;
    choose["Electron_mvaFall17V2Iso_WP90"]	= DEFAULT;
    choose["Electron_mvaFall17V2Iso_WPL"]	= DEFAULT;
    choose["Electron_mvaFall17V2noIso"]	= DEFAULT;
    choose["Electron_mvaFall17V2noIso_WP80"]	= DEFAULT;
    choose["Electron_mvaFall17V2noIso_WP90"]	= DEFAULT;
    choose["Electron_mvaFall17V2noIso_WPL"]	= DEFAULT;
    choose["Electron_mvaTTH"]	= DEFAULT;
    choose["Electron_pdgId"]	= DEFAULT;
    choose["Electron_pfRelIso03_all"]	= DEFAULT;
    choose["Electron_pfRelIso03_chg"]	= DEFAULT;
    choose["Electron_phi"]	= DEFAULT;
    choose["Electron_photonIdx"]	= DEFAULT;
    choose["Electron_pt"]	= DEFAULT;
    choose["Electron_r9"]	= DEFAULT;
    choose["Electron_scEtOverPt"]	= DEFAULT;
    choose["Electron_seedGain"]	= DEFAULT;
    choose["Electron_sieie"]	= DEFAULT;
    choose["Electron_sip3d"]	= DEFAULT;
    choose["Electron_tightCharge"]	= DEFAULT;
    choose["Electron_vidNestedWPBitmap"]	= DEFAULT;
    choose["Electron_vidNestedWPBitmapHEEP"]	= DEFAULT;
    choose["FatJet_area"]	= DEFAULT;
    choose["FatJet_btagCSVV2"]	= DEFAULT;
    choose["FatJet_btagDDBvLV2"]	= DEFAULT;
    choose["FatJet_btagDDCvBV2"]	= DEFAULT;
    choose["FatJet_btagDDCvLV2"]	= DEFAULT;
    choose["FatJet_btagDeepB"]	= DEFAULT;
    choose["FatJet_btagHbb"]	= DEFAULT;
    choose["FatJet_corr_JEC"]	= DEFAULT;
    choose["FatJet_corr_JER"]	= DEFAULT;
    choose["FatJet_corr_JMR"]	= DEFAULT;
    choose["FatJet_corr_JMS"]	= DEFAULT;
    choose["FatJet_deepTagMD_H4qvsQCD"]	= DEFAULT;
    choose["FatJet_deepTagMD_HbbvsQCD"]	= DEFAULT;
    choose["FatJet_deepTagMD_TvsQCD"]	= DEFAULT;
    choose["FatJet_deepTagMD_WvsQCD"]	= DEFAULT;
    choose["FatJet_deepTagMD_ZHbbvsQCD"]	= DEFAULT;
    choose["FatJet_deepTagMD_ZHccvsQCD"]	= DEFAULT;
    choose["FatJet_deepTagMD_ZbbvsQCD"]	= DEFAULT;
    choose["FatJet_deepTagMD_ZvsQCD"]	= DEFAULT;
    choose["FatJet_deepTagMD_bbvsLight"]	= DEFAULT;
    choose["FatJet_deepTagMD_ccvsLight"]	= DEFAULT;
    choose["FatJet_deepTag_H"]	= DEFAULT;
    choose["FatJet_deepTag_QCD"]	= DEFAULT;
    choose["FatJet_deepTag_QCDothers"]	= DEFAULT;
    choose["FatJet_deepTag_TvsQCD"]	= DEFAULT;
    choose["FatJet_deepTag_WvsQCD"]	= DEFAULT;
    choose["FatJet_deepTag_ZvsQCD"]	= DEFAULT;
    choose["FatJet_electronIdx3SJ"]	= DEFAULT;
    choose["FatJet_eta"]	= DEFAULT;
    choose["FatJet_genJetAK8Idx"]	= DEFAULT;
    choose["FatJet_hadronFlavour"]	= DEFAULT;
    choose["FatJet_jetId"]	= DEFAULT;
    choose["FatJet_lsf3"]	= DEFAULT;
    choose["FatJet_mass"]	= DEFAULT;
    choose["FatJet_mass_jerDown"]	= DEFAULT;
    choose["FatJet_mass_jerUp"]	= DEFAULT;
    choose["FatJet_mass_jesTotalDown"]	= DEFAULT;
    choose["FatJet_mass_jesTotalUp"]	= DEFAULT;
    choose["FatJet_mass_jmrDown"]	= DEFAULT;
    choose["FatJet_mass_jmrUp"]	= DEFAULT;
    choose["FatJet_mass_jmsDown"]	= DEFAULT;
    choose["FatJet_mass_jmsUp"]	= DEFAULT;
    choose["FatJet_mass_nom"]	= DEFAULT;
    choose["FatJet_mass_raw"]	= DEFAULT;
    choose["FatJet_msoftdrop"]	= DEFAULT;
    choose["FatJet_msoftdrop_corr_JMR"]	= DEFAULT;
    choose["FatJet_msoftdrop_corr_JMS"]	= DEFAULT;
    choose["FatJet_msoftdrop_corr_PUPPI"]	= DEFAULT;
    choose["FatJet_msoftdrop_jerDown"]	= DEFAULT;
    choose["FatJet_msoftdrop_jerUp"]	= DEFAULT;
    choose["FatJet_msoftdrop_jesTotalDown"]	= DEFAULT;
    choose["FatJet_msoftdrop_jesTotalUp"]	= DEFAULT;
    choose["FatJet_msoftdrop_jmrDown"]	= DEFAULT;
    choose["FatJet_msoftdrop_jmrUp"]	= DEFAULT;
    choose["FatJet_msoftdrop_jmsDown"]	= DEFAULT;
    choose["FatJet_msoftdrop_jmsUp"]	= DEFAULT;
    choose["FatJet_msoftdrop_nom"]	= DEFAULT;
    choose["FatJet_msoftdrop_raw"]	= DEFAULT;
    choose["FatJet_msoftdrop_tau21DDT_jerDown"]	= DEFAULT;
    choose["FatJet_msoftdrop_tau21DDT_jerUp"]	= DEFAULT;
    choose["FatJet_msoftdrop_tau21DDT_jmrDown"]	= DEFAULT;
    choose["FatJet_msoftdrop_tau21DDT_jmrUp"]	= DEFAULT;
    choose["FatJet_msoftdrop_tau21DDT_jmsDown"]	= DEFAULT;
    choose["FatJet_msoftdrop_tau21DDT_jmsUp"]	= DEFAULT;
    choose["FatJet_msoftdrop_tau21DDT_nom"]	= DEFAULT;
    choose["FatJet_muonIdx3SJ"]	= DEFAULT;
    choose["FatJet_n2b1"]	= DEFAULT;
    choose["FatJet_n3b1"]	= DEFAULT;
    choose["FatJet_nBHadrons"]	= DEFAULT;
    choose["FatJet_nCHadrons"]	= DEFAULT;
    choose["FatJet_nConstituents"]	= DEFAULT;
    choose["FatJet_particleNetMD_QCD"]	= DEFAULT;
    choose["FatJet_particleNetMD_Xbb"]	= DEFAULT;
    choose["FatJet_particleNetMD_Xcc"]	= DEFAULT;
    choose["FatJet_particleNetMD_Xqq"]	= DEFAULT;
    choose["FatJet_particleNet_H4qvsQCD"]	= DEFAULT;
    choose["FatJet_particleNet_HbbvsQCD"]	= DEFAULT;
    choose["FatJet_particleNet_HccvsQCD"]	= DEFAULT;
    choose["FatJet_particleNet_QCD"]	= DEFAULT;
    choose["FatJet_particleNet_TvsQCD"]	= DEFAULT;
    choose["FatJet_particleNet_WvsQCD"]	= DEFAULT;
    choose["FatJet_particleNet_ZvsQCD"]	= DEFAULT;
    choose["FatJet_particleNet_mass"]	= DEFAULT;
    choose["FatJet_phi"]	= DEFAULT;
    choose["FatJet_pt"]	= DEFAULT;
    choose["FatJet_pt_jerDown"]	= DEFAULT;
    choose["FatJet_pt_jerUp"]	= DEFAULT;
    choose["FatJet_pt_jesTotalDown"]	= DEFAULT;
    choose["FatJet_pt_jesTotalUp"]	= DEFAULT;
    choose["FatJet_pt_nom"]	= DEFAULT;
    choose["FatJet_pt_raw"]	= DEFAULT;
    choose["FatJet_rawFactor"]	= DEFAULT;
    choose["FatJet_subJetIdx1"]	= DEFAULT;
    choose["FatJet_subJetIdx2"]	= DEFAULT;
    choose["FatJet_tau1"]	= DEFAULT;
    choose["FatJet_tau2"]	= DEFAULT;
    choose["FatJet_tau3"]	= DEFAULT;
    choose["FatJet_tau4"]	= DEFAULT;
    choose["Flag_BadChargedCandidateFilter"]	= DEFAULT;
    choose["Flag_BadChargedCandidateSummer16Filter"]	= DEFAULT;
    choose["Flag_BadPFMuonDzFilter"]	= DEFAULT;
    choose["Flag_BadPFMuonFilter"]	= DEFAULT;
    choose["Flag_BadPFMuonSummer16Filter"]	= DEFAULT;
    choose["Flag_CSCTightHalo2015Filter"]	= DEFAULT;
    choose["Flag_CSCTightHaloFilter"]	= DEFAULT;
    choose["Flag_CSCTightHaloTrkMuUnvetoFilter"]	= DEFAULT;
    choose["Flag_EcalDeadCellBoundaryEnergyFilter"]	= DEFAULT;
    choose["Flag_EcalDeadCellTriggerPrimitiveFilter"]	= DEFAULT;
    choose["Flag_HBHENoiseFilter"]	= DEFAULT;
    choose["Flag_HBHENoiseIsoFilter"]	= DEFAULT;
    choose["Flag_HcalStripHaloFilter"]	= DEFAULT;
    choose["Flag_METFilters"]	= DEFAULT;
    choose["Flag_chargedHadronTrackResolutionFilter"]	= DEFAULT;
    choose["Flag_ecalBadCalibFilter"]	= DEFAULT;
    choose["Flag_ecalLaserCorrFilter"]	= DEFAULT;
    choose["Flag_eeBadScFilter"]	= DEFAULT;
    choose["Flag_globalSuperTightHalo2016Filter"]	= DEFAULT;
    choose["Flag_globalTightHalo2016Filter"]	= DEFAULT;
    choose["Flag_goodVertices"]	= DEFAULT;
    choose["Flag_hcalLaserEventFilter"]	= DEFAULT;
    choose["Flag_hfNoisyHitsFilter"]	= DEFAULT;
    choose["Flag_muonBadTrackFilter"]	= DEFAULT;
    choose["Flag_trkPOGFilters"]	= DEFAULT;
    choose["Flag_trkPOG_logErrorTooManyClusters"]	= DEFAULT;
    choose["Flag_trkPOG_manystripclus53X"]	= DEFAULT;
    choose["Flag_trkPOG_toomanystripclus53X"]	= DEFAULT;
    choose["FsrPhoton_dROverEt2"]	= DEFAULT;
    choose["FsrPhoton_eta"]	= DEFAULT;
    choose["FsrPhoton_muonIdx"]	= DEFAULT;
    choose["FsrPhoton_phi"]	= DEFAULT;
    choose["FsrPhoton_pt"]	= DEFAULT;
    choose["FsrPhoton_relIso03"]	= DEFAULT;
    choose["GenIsolatedPhoton_eta"]	= DEFAULT;
    choose["GenIsolatedPhoton_mass"]	= DEFAULT;
    choose["GenIsolatedPhoton_phi"]	= DEFAULT;
    choose["GenIsolatedPhoton_pt"]	= DEFAULT;
    choose["GenJetAK8_eta"]	= DEFAULT;
    choose["GenJetAK8_hadronFlavour"]	= DEFAULT;
    choose["GenJetAK8_mass"]	= DEFAULT;
    choose["GenJetAK8_partonFlavour"]	= DEFAULT;
    choose["GenJetAK8_phi"]	= DEFAULT;
    choose["GenJetAK8_pt"]	= DEFAULT;
    choose["GenJet_eta"]	= DEFAULT;
    choose["GenJet_hadronFlavour"]	= DEFAULT;
    choose["GenJet_mass"]	= DEFAULT;
    choose["GenJet_partonFlavour"]	= DEFAULT;
    choose["GenJet_phi"]	= DEFAULT;
    choose["GenJet_pt"]	= DEFAULT;
    choose["GenMET_phi"]	= DEFAULT;
    choose["GenMET_pt"]	= DEFAULT;
    choose["GenPart_eta"]	= DEFAULT;
    choose["GenPart_genPartIdxMother"]	= DEFAULT;
    choose["GenPart_mass"]	= DEFAULT;
    choose["GenPart_pdgId"]	= DEFAULT;
    choose["GenPart_phi"]	= DEFAULT;
    choose["GenPart_pt"]	= DEFAULT;
    choose["GenPart_status"]	= DEFAULT;
    choose["GenPart_statusFlags"]	= DEFAULT;
    choose["GenVtx_t0"]	= DEFAULT;
    choose["GenVtx_x"]	= DEFAULT;
    choose["GenVtx_y"]	= DEFAULT;
    choose["GenVtx_z"]	= DEFAULT;
    choose["Generator_binvar"]	= DEFAULT;
    choose["Generator_id1"]	= DEFAULT;
    choose["Generator_id2"]	= DEFAULT;
    choose["Generator_scalePDF"]	= DEFAULT;
    choose["Generator_weight"]	= DEFAULT;
    choose["Generator_x1"]	= DEFAULT;
    choose["Generator_x2"]	= DEFAULT;
    choose["Generator_xpdf1"]	= DEFAULT;
    choose["Generator_xpdf2"]	= DEFAULT;
		choose["HLT_PFHT300_PFMET110"]	= DEFAULT;
		choose["HLT_PFHT125"]	= DEFAULT;
		choose["HLT_PFHT200"]	= DEFAULT;
		choose["HLT_PFHT300"]	= DEFAULT;
		choose["HLT_PFHT400"]	= DEFAULT;
		choose["HLT_PFHT475"]	= DEFAULT;
		choose["HLT_PFHT650"]	= DEFAULT;
		choose["HLT_PFHT800"]	= DEFAULT;
		choose["HLT_PFHT900"]	= DEFAULT;
		choose["HLT_Ele15_IsoVVVL_PFHT350"]	= DEFAULT;
		choose["HLT_Ele105_CaloIdVT_GsfTrkIdT"]	= DEFAULT;
		choose["HLT_Mu15_IsoVVVL_PFHT350"]	= DEFAULT;
		choose["HLT_IsoTkMu24"]	= DEFAULT;
		choose["HLT_TkMu50"]	= DEFAULT;
		choose["HLT_Mu15_IsoVVVL_PFHT400"]	= DEFAULT;
		choose["HLT_IsoTkMu27"]	= DEFAULT;
		choose["HLT_Ele15_IsoVVVL_PFHT400"]	= DEFAULT;
		choose["HLT_Photon22"]	= DEFAULT;
		choose["HLT_Photon30"]	= DEFAULT;
		choose["HLT_Photon36"]	= DEFAULT;
		choose["HLT_Photon125"]	= DEFAULT;
		choose["HLT_Photon165_HE10"]	= DEFAULT;
		choose["HLT_Photon250_NoHE"]	= DEFAULT;
    choose["HLT_AK4CaloJet100"]	= DEFAULT;
    choose["HLT_AK4CaloJet120"]	= DEFAULT;
    choose["HLT_AK4CaloJet30"]	= DEFAULT;
    choose["HLT_AK4CaloJet40"]	= DEFAULT;
    choose["HLT_AK4CaloJet50"]	= DEFAULT;
    choose["HLT_AK4CaloJet80"]	= DEFAULT;
    choose["HLT_AK4PFJet100"]	= DEFAULT;
    choose["HLT_AK4PFJet120"]	= DEFAULT;
    choose["HLT_AK4PFJet30"]	= DEFAULT;
    choose["HLT_AK4PFJet50"]	= DEFAULT;
    choose["HLT_AK4PFJet80"]	= DEFAULT;
    choose["HLT_AK8PFHT750_TrimMass50"]	= DEFAULT;
    choose["HLT_AK8PFHT800_TrimMass50"]	= DEFAULT;
    choose["HLT_AK8PFHT850_TrimMass50"]	= DEFAULT;
    choose["HLT_AK8PFHT900_TrimMass50"]	= DEFAULT;
    choose["HLT_AK8PFJet140"]	= DEFAULT;
    choose["HLT_AK8PFJet15"]	= DEFAULT;
    choose["HLT_AK8PFJet200"]	= DEFAULT;
    choose["HLT_AK8PFJet25"]	= DEFAULT;
    choose["HLT_AK8PFJet260"]	= DEFAULT;
    choose["HLT_AK8PFJet320"]	= DEFAULT;
    choose["HLT_AK8PFJet330_TrimMass30_PFAK8BTagDeepCSV_p1"]	= DEFAULT;
    choose["HLT_AK8PFJet330_TrimMass30_PFAK8BTagDeepCSV_p17"]	= DEFAULT;
    choose["HLT_AK8PFJet330_TrimMass30_PFAK8BoostedDoubleB_np2"]	= DEFAULT;
    choose["HLT_AK8PFJet330_TrimMass30_PFAK8BoostedDoubleB_np4"]	= DEFAULT;
    choose["HLT_AK8PFJet330_TrimMass30_PFAK8BoostedDoubleB_p02"]	= DEFAULT;
    choose["HLT_AK8PFJet360_TrimMass30"]	= DEFAULT;
    choose["HLT_AK8PFJet380_TrimMass30"]	= DEFAULT;
    choose["HLT_AK8PFJet40"]	= DEFAULT;
    choose["HLT_AK8PFJet400"]	= DEFAULT;
    choose["HLT_AK8PFJet400_TrimMass30"]	= DEFAULT;
    choose["HLT_AK8PFJet420_TrimMass30"]	= DEFAULT;
    choose["HLT_AK8PFJet450"]	= DEFAULT;
    choose["HLT_AK8PFJet500"]	= DEFAULT;
    choose["HLT_AK8PFJet550"]	= DEFAULT;
    choose["HLT_AK8PFJet60"]	= DEFAULT;
    choose["HLT_AK8PFJet80"]	= DEFAULT;
    choose["HLT_AK8PFJetFwd140"]	= DEFAULT;
    choose["HLT_AK8PFJetFwd15"]	= DEFAULT;
    choose["HLT_AK8PFJetFwd200"]	= DEFAULT;
    choose["HLT_AK8PFJetFwd25"]	= DEFAULT;
    choose["HLT_AK8PFJetFwd260"]	= DEFAULT;
    choose["HLT_AK8PFJetFwd320"]	= DEFAULT;
    choose["HLT_AK8PFJetFwd40"]	= DEFAULT;
    choose["HLT_AK8PFJetFwd400"]	= DEFAULT;
    choose["HLT_AK8PFJetFwd450"]	= DEFAULT;
    choose["HLT_AK8PFJetFwd500"]	= DEFAULT;
    choose["HLT_AK8PFJetFwd60"]	= DEFAULT;
    choose["HLT_AK8PFJetFwd80"]	= DEFAULT;
    choose["HLT_Ele115_CaloIdVT_GsfTrkIdT"]	= DEFAULT;
    choose["HLT_Ele12_CaloIdL_TrackIdL_IsoVL_PFJet30"]	= DEFAULT;
    choose["HLT_Ele135_CaloIdVT_GsfTrkIdT"]	= DEFAULT;
    choose["HLT_Ele145_CaloIdVT_GsfTrkIdT"]	= DEFAULT;
    choose["HLT_Ele15_CaloIdL_TrackIdL_IsoVL_PFJet30"]	= DEFAULT;
    choose["HLT_Ele15_Ele8_CaloIdL_TrackIdL_IsoVL"]	= DEFAULT;
    choose["HLT_Ele15_IsoVVVL_PFHT450"]	= DEFAULT;
    choose["HLT_Ele15_IsoVVVL_PFHT450_CaloBTagDeepCSV_4p5"]	= DEFAULT;
    choose["HLT_Ele15_IsoVVVL_PFHT450_PFMET50"]	= DEFAULT;
    choose["HLT_Ele15_IsoVVVL_PFHT600"]	= DEFAULT;
    choose["HLT_Ele15_WPLoose_Gsf"]	= DEFAULT;
    choose["HLT_Ele16_Ele12_Ele8_CaloIdL_TrackIdL"]	= DEFAULT;
    choose["HLT_Ele17_CaloIdM_TrackIdM_PFJet30"]	= DEFAULT;
    choose["HLT_Ele17_WPLoose_Gsf"]	= DEFAULT;
    choose["HLT_Ele200_CaloIdVT_GsfTrkIdT"]	= DEFAULT;
    choose["HLT_Ele20_WPLoose_Gsf"]	= DEFAULT;
    choose["HLT_Ele20_WPTight_Gsf"]	= DEFAULT;
    choose["HLT_Ele20_eta2p1_WPLoose_Gsf"]	= DEFAULT;
    choose["HLT_Ele23_CaloIdL_TrackIdL_IsoVL_PFJet30"]	= DEFAULT;
    choose["HLT_Ele23_CaloIdM_TrackIdM_PFJet30"]	= DEFAULT;
    choose["HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL"]	= DEFAULT;
    choose["HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ"]	= DEFAULT;
    choose["HLT_Ele24_eta2p1_WPTight_Gsf_LooseChargedIsoPFTauHPS30_eta2p1_CrossL1"]	= DEFAULT;
    choose["HLT_Ele24_eta2p1_WPTight_Gsf_LooseChargedIsoPFTauHPS30_eta2p1_TightID_CrossL1"]	= DEFAULT;
    choose["HLT_Ele24_eta2p1_WPTight_Gsf_MediumChargedIsoPFTauHPS30_eta2p1_CrossL1"]	= DEFAULT;
    choose["HLT_Ele24_eta2p1_WPTight_Gsf_MediumChargedIsoPFTauHPS30_eta2p1_TightID_CrossL1"]	= DEFAULT;
    choose["HLT_Ele24_eta2p1_WPTight_Gsf_TightChargedIsoPFTauHPS30_eta2p1_CrossL1"]	= DEFAULT;
    choose["HLT_Ele24_eta2p1_WPTight_Gsf_TightChargedIsoPFTauHPS30_eta2p1_TightID_CrossL1"]	= DEFAULT;
    choose["HLT_Ele250_CaloIdVT_GsfTrkIdT"]	= DEFAULT;
    choose["HLT_Ele27_Ele37_CaloIdL_MW"]	= DEFAULT;
    choose["HLT_Ele27_WPTight_Gsf"]	= DEFAULT;
    choose["HLT_Ele28_HighEta_SC20_Mass55"]	= DEFAULT;
    choose["HLT_Ele28_WPTight_Gsf"]	= DEFAULT;
    choose["HLT_Ele28_eta2p1_WPTight_Gsf_HT150"]	= DEFAULT;
    choose["HLT_Ele300_CaloIdVT_GsfTrkIdT"]	= DEFAULT;
    choose["HLT_Ele30_WPTight_Gsf"]	= DEFAULT;
    choose["HLT_Ele30_eta2p1_WPTight_Gsf_CentralPFJet35_EleCleaned"]	= DEFAULT;
    choose["HLT_Ele32_WPTight_Gsf"]	= DEFAULT;
    choose["HLT_Ele32_WPTight_Gsf_L1DoubleEG"]	= DEFAULT;
    choose["HLT_Ele35_WPTight_Gsf"]	= DEFAULT;
    choose["HLT_Ele35_WPTight_Gsf_L1EGMT"]	= DEFAULT;
    choose["HLT_Ele38_WPTight_Gsf"]	= DEFAULT;
    choose["HLT_Ele40_WPTight_Gsf"]	= DEFAULT;
    choose["HLT_Ele50_CaloIdVT_GsfTrkIdT_PFJet165"]	= DEFAULT;
    choose["HLT_Ele50_IsoVVVL_PFHT450"]	= DEFAULT;
    choose["HLT_Ele8_CaloIdL_TrackIdL_IsoVL_PFJet30"]	= DEFAULT;
    choose["HLT_Ele8_CaloIdM_TrackIdM_PFJet30"]	= DEFAULT;
    choose["HLT_HT300_Beamspot"]	= DEFAULT;
    choose["HLT_HT400_DisplacedDijet40_DisplacedTrack"]	= DEFAULT;
    choose["HLT_HT425"]	= DEFAULT;
    choose["HLT_HT430_DisplacedDijet40_DisplacedTrack"]	= DEFAULT;
    choose["HLT_HT430_DisplacedDijet60_DisplacedTrack"]	= DEFAULT;
    choose["HLT_HT450_Beamspot"]	= DEFAULT;
    choose["HLT_HT500_DisplacedDijet40_DisplacedTrack"]	= DEFAULT;
    choose["HLT_HT550_DisplacedDijet60_Inclusive"]	= DEFAULT;
    choose["HLT_HT650_DisplacedDijet60_Inclusive"]	= DEFAULT;
    choose["HLT_IsoMu20"]	= DEFAULT;
    choose["HLT_IsoMu20_eta2p1_LooseChargedIsoPFTauHPS27_eta2p1_CrossL1"]	= DEFAULT;
    choose["HLT_IsoMu20_eta2p1_LooseChargedIsoPFTauHPS27_eta2p1_TightID_CrossL1"]	= DEFAULT;
    choose["HLT_IsoMu20_eta2p1_MediumChargedIsoPFTauHPS27_eta2p1_CrossL1"]	= DEFAULT;
    choose["HLT_IsoMu20_eta2p1_MediumChargedIsoPFTauHPS27_eta2p1_TightID_CrossL1"]	= DEFAULT;
    choose["HLT_IsoMu20_eta2p1_TightChargedIsoPFTauHPS27_eta2p1_CrossL1"]	= DEFAULT;
    choose["HLT_IsoMu20_eta2p1_TightChargedIsoPFTauHPS27_eta2p1_TightID_CrossL1"]	= DEFAULT;
    choose["HLT_IsoMu24"]	= DEFAULT;
    choose["HLT_IsoMu24_TwoProngs35"]	= DEFAULT;
    choose["HLT_IsoMu24_eta2p1"]	= DEFAULT;
    choose["HLT_IsoMu24_eta2p1_MediumChargedIsoPFTau50_Trk30_eta2p1_1pr"]	= DEFAULT;
    choose["HLT_IsoMu24_eta2p1_MediumChargedIsoPFTauHPS35_Trk1_TightID_eta2p1_Reg_CrossL1"]	= DEFAULT;
    choose["HLT_IsoMu24_eta2p1_MediumChargedIsoPFTauHPS35_Trk1_eta2p1_Reg_CrossL1"]	= DEFAULT;
    choose["HLT_IsoMu24_eta2p1_TightChargedIsoPFTauHPS35_Trk1_TightID_eta2p1_Reg_CrossL1"]	= DEFAULT;
    choose["HLT_IsoMu24_eta2p1_TightChargedIsoPFTauHPS35_Trk1_eta2p1_Reg_CrossL1"]	= DEFAULT;
    choose["HLT_IsoMu27"]	= DEFAULT;
    choose["HLT_IsoMu27_LooseChargedIsoPFTauHPS20_Trk1_eta2p1_SingleL1"]	= DEFAULT;
    choose["HLT_IsoMu27_MET90"]	= DEFAULT;
    choose["HLT_IsoMu27_MediumChargedIsoPFTauHPS20_Trk1_eta2p1_SingleL1"]	= DEFAULT;
    choose["HLT_IsoMu27_TightChargedIsoPFTauHPS20_Trk1_eta2p1_SingleL1"]	= DEFAULT;
    choose["HLT_IsoMu30"]	= DEFAULT;
    choose["HLT_IsoTrackHB"]	= DEFAULT;
    choose["HLT_IsoTrackHE"]	= DEFAULT;
    choose["HLT_MET105_IsoTrk50"]	= DEFAULT;
    choose["HLT_MET120_IsoTrk50"]	= DEFAULT;
    choose["HLT_Mu10_TrkIsoVVL_DiPFJet40_DEta3p5_MJJ750_HTT350_PFMETNoMu60"]	= DEFAULT;
    choose["HLT_Mu12"]	= DEFAULT;
    choose["HLT_Mu12_DoublePFJets100_CaloBTagDeepCSV_p71"]	= DEFAULT;
    choose["HLT_Mu12_DoublePFJets200_CaloBTagDeepCSV_p71"]	= DEFAULT;
    choose["HLT_Mu12_DoublePFJets350_CaloBTagDeepCSV_p71"]	= DEFAULT;
    choose["HLT_Mu12_DoublePFJets40MaxDeta1p6_DoubleCaloBTagDeepCSV_p71"]	= DEFAULT;
    choose["HLT_Mu12_DoublePFJets40_CaloBTagDeepCSV_p71"]	= DEFAULT;
    choose["HLT_Mu12_DoublePFJets54MaxDeta1p6_DoubleCaloBTagDeepCSV_p71"]	= DEFAULT;
    choose["HLT_Mu12_DoublePFJets62MaxDeta1p6_DoubleCaloBTagDeepCSV_p71"]	= DEFAULT;
    choose["HLT_Mu12_DoublePhoton20"]	= DEFAULT;
    choose["HLT_Mu12_IP6_part0"]	= DEFAULT;
    choose["HLT_Mu12_IP6_part1"]	= DEFAULT;
    choose["HLT_Mu12_IP6_part2"]	= DEFAULT;
    choose["HLT_Mu12_IP6_part3"]	= DEFAULT;
    choose["HLT_Mu12_IP6_part4"]	= DEFAULT;
    choose["HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL"]	= DEFAULT;
    choose["HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ"]	= DEFAULT;
    choose["HLT_Mu15"]	= DEFAULT;
    choose["HLT_Mu15_IsoVVVL_PFHT450"]	= DEFAULT;
    choose["HLT_Mu15_IsoVVVL_PFHT450_CaloBTagDeepCSV_4p5"]	= DEFAULT;
    choose["HLT_Mu15_IsoVVVL_PFHT450_PFMET50"]	= DEFAULT;
    choose["HLT_Mu15_IsoVVVL_PFHT600"]	= DEFAULT;
    choose["HLT_Mu17"]	= DEFAULT;
    choose["HLT_Mu17_Photon30_IsoCaloId"]	= DEFAULT;
    choose["HLT_Mu17_TrkIsoVVL"]	= DEFAULT;
    choose["HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL"]	= DEFAULT;
    choose["HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ"]	= DEFAULT;
    choose["HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8"]	= DEFAULT;
    choose["HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass8"]	= DEFAULT;
    choose["HLT_Mu18_Mu9"]	= DEFAULT;
    choose["HLT_Mu18_Mu9_DZ"]	= DEFAULT;
    choose["HLT_Mu18_Mu9_SameSign"]	= DEFAULT;
    choose["HLT_Mu18_Mu9_SameSign_DZ"]	= DEFAULT;
    choose["HLT_Mu19"]	= DEFAULT;
    choose["HLT_Mu19_TrkIsoVVL"]	= DEFAULT;
    choose["HLT_Mu19_TrkIsoVVL_Mu9_TrkIsoVVL"]	= DEFAULT;
    choose["HLT_Mu19_TrkIsoVVL_Mu9_TrkIsoVVL_DZ"]	= DEFAULT;
    choose["HLT_Mu19_TrkIsoVVL_Mu9_TrkIsoVVL_DZ_Mass3p8"]	= DEFAULT;
    choose["HLT_Mu19_TrkIsoVVL_Mu9_TrkIsoVVL_DZ_Mass8"]	= DEFAULT;
    choose["HLT_Mu20"]	= DEFAULT;
    choose["HLT_Mu20_Mu10"]	= DEFAULT;
    choose["HLT_Mu20_Mu10_DZ"]	= DEFAULT;
    choose["HLT_Mu20_Mu10_SameSign"]	= DEFAULT;
    choose["HLT_Mu20_Mu10_SameSign_DZ"]	= DEFAULT;
    choose["HLT_Mu20_TkMu0_Phi"]	= DEFAULT;
    choose["HLT_Mu23_Mu12"]	= DEFAULT;
    choose["HLT_Mu23_Mu12_DZ"]	= DEFAULT;
    choose["HLT_Mu23_Mu12_SameSign"]	= DEFAULT;
    choose["HLT_Mu23_Mu12_SameSign_DZ"]	= DEFAULT;
    choose["HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL"]	= DEFAULT;
    choose["HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ"]	= DEFAULT;
    choose["HLT_Mu25_TkMu0_Onia"]	= DEFAULT;
    choose["HLT_Mu25_TkMu0_Phi"]	= DEFAULT;
    choose["HLT_Mu27"]	= DEFAULT;
    choose["HLT_Mu27_Ele37_CaloIdL_MW"]	= DEFAULT;
    choose["HLT_Mu30_TkMu0_Psi"]	= DEFAULT;
    choose["HLT_Mu30_TkMu0_Upsilon"]	= DEFAULT;
    choose["HLT_Mu37_Ele27_CaloIdL_MW"]	= DEFAULT;
    choose["HLT_Mu37_TkMu27"]	= DEFAULT;
    choose["HLT_Mu38NoFiltersNoVtxDisplaced_Photon38_CaloIdL"]	= DEFAULT;
    choose["HLT_Mu3_L1SingleMu5orSingleMu7"]	= DEFAULT;
    choose["HLT_Mu3_PFJet40"]	= DEFAULT;
    choose["HLT_Mu3er1p5_PFJet100er2p5_PFMET100_PFMHT100_IDTight"]	= DEFAULT;
    choose["HLT_Mu3er1p5_PFJet100er2p5_PFMET70_PFMHT70_IDTight"]	= DEFAULT;
    choose["HLT_Mu3er1p5_PFJet100er2p5_PFMET80_PFMHT80_IDTight"]	= DEFAULT;
    choose["HLT_Mu3er1p5_PFJet100er2p5_PFMET90_PFMHT90_IDTight"]	= DEFAULT;
    choose["HLT_Mu3er1p5_PFJet100er2p5_PFMETNoMu100_PFMHTNoMu100_IDTight"]	= DEFAULT;
    choose["HLT_Mu3er1p5_PFJet100er2p5_PFMETNoMu70_PFMHTNoMu70_IDTight"]	= DEFAULT;
    choose["HLT_Mu3er1p5_PFJet100er2p5_PFMETNoMu80_PFMHTNoMu80_IDTight"]	= DEFAULT;
    choose["HLT_Mu3er1p5_PFJet100er2p5_PFMETNoMu90_PFMHTNoMu90_IDTight"]	= DEFAULT;
    choose["HLT_Mu43NoFiltersNoVtxDisplaced_Photon43_CaloIdL"]	= DEFAULT;
    choose["HLT_Mu43NoFiltersNoVtx_Photon43_CaloIdL"]	= DEFAULT;
    choose["HLT_Mu48NoFiltersNoVtx_Photon48_CaloIdL"]	= DEFAULT;
    choose["HLT_Mu4_TrkIsoVVL_DiPFJet90_40_DEta3p5_MJJ750_HTT300_PFMETNoMu60"]	= DEFAULT;
    choose["HLT_Mu50"]	= DEFAULT;
    choose["HLT_Mu50_IsoVVVL_PFHT450"]	= DEFAULT;
    choose["HLT_Mu55"]	= DEFAULT;
    choose["HLT_Mu7_IP4_part0"]	= DEFAULT;
    choose["HLT_Mu7_IP4_part1"]	= DEFAULT;
    choose["HLT_Mu7_IP4_part2"]	= DEFAULT;
    choose["HLT_Mu7_IP4_part3"]	= DEFAULT;
    choose["HLT_Mu7_IP4_part4"]	= DEFAULT;
    choose["HLT_Mu7p5_L2Mu2_Jpsi"]	= DEFAULT;
    choose["HLT_Mu7p5_L2Mu2_Upsilon"]	= DEFAULT;
    choose["HLT_Mu7p5_Track2_Jpsi"]	= DEFAULT;
    choose["HLT_Mu7p5_Track2_Upsilon"]	= DEFAULT;
    choose["HLT_Mu7p5_Track3p5_Jpsi"]	= DEFAULT;
    choose["HLT_Mu7p5_Track3p5_Upsilon"]	= DEFAULT;
    choose["HLT_Mu7p5_Track7_Jpsi"]	= DEFAULT;
    choose["HLT_Mu7p5_Track7_Upsilon"]	= DEFAULT;
    choose["HLT_Mu8"]	= DEFAULT;
    choose["HLT_Mu8_DiEle12_CaloIdL_TrackIdL"]	= DEFAULT;
    choose["HLT_Mu8_DiEle12_CaloIdL_TrackIdL_DZ"]	= DEFAULT;
    choose["HLT_Mu8_Ele8_CaloIdM_TrackIdM_Mass8_PFHT350"]	= DEFAULT;
    choose["HLT_Mu8_Ele8_CaloIdM_TrackIdM_Mass8_PFHT350_DZ"]	= DEFAULT;
    choose["HLT_Mu8_IP3_part0"]	= DEFAULT;
    choose["HLT_Mu8_IP3_part1"]	= DEFAULT;
    choose["HLT_Mu8_IP3_part2"]	= DEFAULT;
    choose["HLT_Mu8_IP3_part3"]	= DEFAULT;
    choose["HLT_Mu8_IP3_part4"]	= DEFAULT;
    choose["HLT_Mu8_IP5_part0"]	= DEFAULT;
    choose["HLT_Mu8_IP5_part1"]	= DEFAULT;
    choose["HLT_Mu8_IP5_part2"]	= DEFAULT;
    choose["HLT_Mu8_IP5_part3"]	= DEFAULT;
    choose["HLT_Mu8_IP5_part4"]	= DEFAULT;
    choose["HLT_Mu8_IP6_part0"]	= DEFAULT;
    choose["HLT_Mu8_IP6_part1"]	= DEFAULT;
    choose["HLT_Mu8_IP6_part2"]	= DEFAULT;
    choose["HLT_Mu8_IP6_part3"]	= DEFAULT;
    choose["HLT_Mu8_IP6_part4"]	= DEFAULT;
    choose["HLT_Mu8_TrkIsoVVL"]	= DEFAULT;
    choose["HLT_Mu8_TrkIsoVVL_DiPFJet40_DEta3p5_MJJ750_HTT300_PFMETNoMu60"]	= DEFAULT;
    choose["HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL"]	= DEFAULT;
    choose["HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ"]	= DEFAULT;
    choose["HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_CaloDiJet30"]	= DEFAULT;
    choose["HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_CaloDiJet30_CaloBtagDeepCSV_1p5"]	= DEFAULT;
    choose["HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_PFDiJet30"]	= DEFAULT;
    choose["HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_PFDiJet30_PFBtagDeepCSV_1p5"]	= DEFAULT;
    choose["HLT_Mu9_IP4_part0"]	= DEFAULT;
    choose["HLT_Mu9_IP4_part1"]	= DEFAULT;
    choose["HLT_Mu9_IP4_part2"]	= DEFAULT;
    choose["HLT_Mu9_IP4_part3"]	= DEFAULT;
    choose["HLT_Mu9_IP4_part4"]	= DEFAULT;
    choose["HLT_Mu9_IP5_part0"]	= DEFAULT;
    choose["HLT_Mu9_IP5_part1"]	= DEFAULT;
    choose["HLT_Mu9_IP5_part2"]	= DEFAULT;
    choose["HLT_Mu9_IP5_part3"]	= DEFAULT;
    choose["HLT_Mu9_IP5_part4"]	= DEFAULT;
    choose["HLT_Mu9_IP6_part0"]	= DEFAULT;
    choose["HLT_Mu9_IP6_part1"]	= DEFAULT;
    choose["HLT_Mu9_IP6_part2"]	= DEFAULT;
    choose["HLT_Mu9_IP6_part3"]	= DEFAULT;
    choose["HLT_Mu9_IP6_part4"]	= DEFAULT;
    choose["HLT_OldMu100"]	= DEFAULT;
    choose["HLT_PFHT1050"]	= DEFAULT;
    choose["HLT_PFHT180"]	= DEFAULT;
    choose["HLT_PFHT250"]	= DEFAULT;
    choose["HLT_PFHT330PT30_QuadPFJet_75_60_45_40"]	= DEFAULT;
    choose["HLT_PFHT330PT30_QuadPFJet_75_60_45_40_TriplePFBTagDeepCSV_4p5"]	= DEFAULT;
    choose["HLT_PFHT350"]	= DEFAULT;
    choose["HLT_PFHT350MinPFJet15"]	= DEFAULT;
    choose["HLT_PFHT370"]	= DEFAULT;
    choose["HLT_PFHT400_SixPFJet32"]	= DEFAULT;
    choose["HLT_PFHT400_SixPFJet32_DoublePFBTagDeepCSV_2p94"]	= DEFAULT;
    choose["HLT_PFHT430"]	= DEFAULT;
    choose["HLT_PFHT450_SixPFJet36"]	= DEFAULT;
    choose["HLT_PFHT450_SixPFJet36_PFBTagDeepCSV_1p59"]	= DEFAULT;
    choose["HLT_PFHT500_PFMET100_PFMHT100_IDTight"]	= DEFAULT;
    choose["HLT_PFHT500_PFMET110_PFMHT110_IDTight"]	= DEFAULT;
    choose["HLT_PFHT510"]	= DEFAULT;
    choose["HLT_PFHT590"]	= DEFAULT;
    choose["HLT_PFHT680"]	= DEFAULT;
    choose["HLT_PFHT700_PFMET85_PFMHT85_IDTight"]	= DEFAULT;
    choose["HLT_PFHT700_PFMET95_PFMHT95_IDTight"]	= DEFAULT;
    choose["HLT_PFHT780"]	= DEFAULT;
    choose["HLT_PFHT800_PFMET75_PFMHT75_IDTight"]	= DEFAULT;
    choose["HLT_PFHT800_PFMET85_PFMHT85_IDTight"]	= DEFAULT;
    choose["HLT_PFHT890"]	= DEFAULT;
    choose["HLT_PFJet140"]	= DEFAULT;
    choose["HLT_PFJet15"]	= DEFAULT;
    choose["HLT_PFJet200"]	= DEFAULT;
    choose["HLT_PFJet25"]	= DEFAULT;
    choose["HLT_PFJet260"]	= DEFAULT;
    choose["HLT_PFJet320"]	= DEFAULT;
    choose["HLT_PFJet40"]	= DEFAULT;
    choose["HLT_PFJet400"]	= DEFAULT;
    choose["HLT_PFJet450"]	= DEFAULT;
    choose["HLT_PFJet500"]	= DEFAULT;
    choose["HLT_PFJet550"]	= DEFAULT;
    choose["HLT_PFJet60"]	= DEFAULT;
    choose["HLT_PFJet80"]	= DEFAULT;
    choose["HLT_PFJetFwd140"]	= DEFAULT;
    choose["HLT_PFJetFwd15"]	= DEFAULT;
    choose["HLT_PFJetFwd200"]	= DEFAULT;
    choose["HLT_PFJetFwd25"]	= DEFAULT;
    choose["HLT_PFJetFwd260"]	= DEFAULT;
    choose["HLT_PFJetFwd320"]	= DEFAULT;
    choose["HLT_PFJetFwd40"]	= DEFAULT;
    choose["HLT_PFJetFwd400"]	= DEFAULT;
    choose["HLT_PFJetFwd450"]	= DEFAULT;
    choose["HLT_PFJetFwd500"]	= DEFAULT;
    choose["HLT_PFJetFwd60"]	= DEFAULT;
    choose["HLT_PFJetFwd80"]	= DEFAULT;
    choose["HLT_PFMET100_PFMHT100_IDTight_CaloBTagDeepCSV_3p1"]	= DEFAULT;
    choose["HLT_PFMET100_PFMHT100_IDTight_PFHT60"]	= DEFAULT;
    choose["HLT_PFMET110_PFMHT110_IDTight"]	= DEFAULT;
    choose["HLT_PFMET110_PFMHT110_IDTight_CaloBTagDeepCSV_3p1"]	= DEFAULT;
    choose["HLT_PFMET120_PFMHT120_IDTight"]	= DEFAULT;
    choose["HLT_PFMET120_PFMHT120_IDTight_CaloBTagDeepCSV_3p1"]	= DEFAULT;
    choose["HLT_PFMET120_PFMHT120_IDTight_PFHT60"]	= DEFAULT;
    choose["HLT_PFMET130_PFMHT130_IDTight"]	= DEFAULT;
    choose["HLT_PFMET130_PFMHT130_IDTight_CaloBTagDeepCSV_3p1"]	= DEFAULT;
    choose["HLT_PFMET140_PFMHT140_IDTight"]	= DEFAULT;
    choose["HLT_PFMET140_PFMHT140_IDTight_CaloBTagDeepCSV_3p1"]	= DEFAULT;
    choose["HLT_PFMET200_HBHECleaned"]	= DEFAULT;
    choose["HLT_PFMET200_HBHE_BeamHaloCleaned"]	= DEFAULT;
    choose["HLT_PFMET200_NotCleaned"]	= DEFAULT;
    choose["HLT_PFMET250_HBHECleaned"]	= DEFAULT;
    choose["HLT_PFMET300_HBHECleaned"]	= DEFAULT;
    choose["HLT_PFMETNoMu100_PFMHTNoMu100_IDTight_PFHT60"]	= DEFAULT;
    choose["HLT_PFMETNoMu110_PFMHTNoMu110_IDTight"]	= DEFAULT;
    choose["HLT_PFMETNoMu120_PFMHTNoMu120_IDTight"]	= DEFAULT;
    choose["HLT_PFMETNoMu120_PFMHTNoMu120_IDTight_PFHT60"]	= DEFAULT;
    choose["HLT_PFMETNoMu130_PFMHTNoMu130_IDTight"]	= DEFAULT;
    choose["HLT_PFMETNoMu140_PFMHTNoMu140_IDTight"]	= DEFAULT;
    choose["HLT_PFMETTypeOne100_PFMHT100_IDTight_PFHT60"]	= DEFAULT;
    choose["HLT_PFMETTypeOne110_PFMHT110_IDTight"]	= DEFAULT;
    choose["HLT_PFMETTypeOne120_PFMHT120_IDTight"]	= DEFAULT;
    choose["HLT_PFMETTypeOne120_PFMHT120_IDTight_PFHT60"]	= DEFAULT;
    choose["HLT_PFMETTypeOne130_PFMHT130_IDTight"]	= DEFAULT;
    choose["HLT_PFMETTypeOne140_PFMHT140_IDTight"]	= DEFAULT;
    choose["HLT_PFMETTypeOne200_HBHE_BeamHaloCleaned"]	= DEFAULT;
    choose["HLT_Photon100EBHE10"]	= DEFAULT;
    choose["HLT_Photon100EB_TightID_TightIso"]	= DEFAULT;
    choose["HLT_Photon100EEHE10"]	= DEFAULT;
    choose["HLT_Photon100EE_TightID_TightIso"]	= DEFAULT;
    choose["HLT_Photon110EB_TightID_TightIso"]	= DEFAULT;
    choose["HLT_Photon120"]	= DEFAULT;
    choose["HLT_Photon120EB_TightID_TightIso"]	= DEFAULT;
    choose["HLT_Photon120_R9Id90_HE10_IsoM"]	= DEFAULT;
    choose["HLT_Photon150"]	= DEFAULT;
    choose["HLT_Photon165_R9Id90_HE10_IsoM"]	= DEFAULT;
    choose["HLT_Photon175"]	= DEFAULT;
    choose["HLT_Photon20"]	= DEFAULT;
    choose["HLT_Photon200"]	= DEFAULT;
    choose["HLT_Photon20_HoverELoose"]	= DEFAULT;
    choose["HLT_Photon300_NoHE"]	= DEFAULT;
    choose["HLT_Photon30_HoverELoose"]	= DEFAULT;
    choose["HLT_Photon33"]	= DEFAULT;
    choose["HLT_Photon35_TwoProngs35"]	= DEFAULT;
    choose["HLT_Photon50"]	= DEFAULT;
    choose["HLT_Photon50_R9Id90_HE10_IsoM"]	= DEFAULT;
    choose["HLT_Photon50_R9Id90_HE10_IsoM_EBOnly_PFJetsMJJ300DEta3_PFMET50"]	= DEFAULT;
    choose["HLT_Photon60_R9Id90_CaloIdL_IsoL"]	= DEFAULT;
    choose["HLT_Photon60_R9Id90_CaloIdL_IsoL_DisplacedIdL"]	= DEFAULT;
    choose["HLT_Photon60_R9Id90_CaloIdL_IsoL_DisplacedIdL_PFHT350MinPFJet15"]	= DEFAULT;
    choose["HLT_Photon75"]	= DEFAULT;
    choose["HLT_Photon75_R9Id90_HE10_IsoM"]	= DEFAULT;
    choose["HLT_Photon75_R9Id90_HE10_IsoM_EBOnly_CaloMJJ300_PFJetsMJJ400DEta3"]	= DEFAULT;
    choose["HLT_Photon75_R9Id90_HE10_IsoM_EBOnly_CaloMJJ400_PFJetsMJJ600DEta3"]	= DEFAULT;
    choose["HLT_Photon75_R9Id90_HE10_IsoM_EBOnly_PFJetsMJJ300DEta3"]	= DEFAULT;
    choose["HLT_Photon75_R9Id90_HE10_IsoM_EBOnly_PFJetsMJJ600DEta3"]	= DEFAULT;
    choose["HLT_Photon90"]	= DEFAULT;
    choose["HLT_Photon90_CaloIdL_PFHT700"]	= DEFAULT;
    choose["HLT_Photon90_R9Id90_HE10_IsoM"]	= DEFAULT;
    choose["HLT_Rsq0p35"]	= DEFAULT;
    choose["HLT_Rsq0p40"]	= DEFAULT;
    choose["HLT_RsqMR300_Rsq0p09_MR200"]	= DEFAULT;
    choose["HLT_RsqMR300_Rsq0p09_MR200_4jet"]	= DEFAULT;
    choose["HLT_RsqMR320_Rsq0p09_MR200"]	= DEFAULT;
    choose["HLT_RsqMR320_Rsq0p09_MR200_4jet"]	= DEFAULT;
    choose["HLT_SingleJet30_Mu12_SinglePFJet40"]	= DEFAULT;
    choose["HLT_SinglePhoton10_Eta3p1ForPPRef"]	= DEFAULT;
    choose["HLT_SinglePhoton20_Eta3p1ForPPRef"]	= DEFAULT;
    choose["HLT_SinglePhoton30_Eta3p1ForPPRef"]	= DEFAULT;
    choose["HLT_Tau3Mu_Mu7_Mu1_TkMu1_IsoTau15"]	= DEFAULT;
    choose["HLT_Tau3Mu_Mu7_Mu1_TkMu1_IsoTau15_Charge1"]	= DEFAULT;
    choose["HLT_Tau3Mu_Mu7_Mu1_TkMu1_Tau15"]	= DEFAULT;
    choose["HLT_Tau3Mu_Mu7_Mu1_TkMu1_Tau15_Charge1"]	= DEFAULT;
    choose["HLT_TkMu100"]	= DEFAULT;
    choose["HLT_Trimuon5_3p5_2_Upsilon_Muon"]	= DEFAULT;
    choose["HLT_TrimuonOpen_5_3p5_2_Upsilon_Muon"]	= DEFAULT;
    choose["HLT_TrkMu12_DoubleTrkMu5NoFiltersNoVtx"]	= DEFAULT;
    choose["HLT_TrkMu16NoFiltersNoVtx"]	= DEFAULT;
    choose["HLT_TrkMu16_DoubleTrkMu6NoFiltersNoVtx"]	= DEFAULT;
    choose["HLT_TrkMu17_DoubleTrkMu8NoFiltersNoVtx"]	= DEFAULT;
    choose["HLT_TrkMu6NoFiltersNoVtx"]	= DEFAULT;
    choose["HLTriggerFinalPath"]	= DEFAULT;
    choose["HLTriggerFirstPath"]	= DEFAULT;
    choose["IsoTrack_charge"]	= DEFAULT;
    choose["IsoTrack_dxy"]	= DEFAULT;
    choose["IsoTrack_dz"]	= DEFAULT;
    choose["IsoTrack_eta"]	= DEFAULT;
    choose["IsoTrack_fromPV"]	= DEFAULT;
    choose["IsoTrack_isFromLostTrack"]	= DEFAULT;
    choose["IsoTrack_isHighPurityTrack"]	= DEFAULT;
    choose["IsoTrack_isPFcand"]	= DEFAULT;
    choose["IsoTrack_miniPFRelIso_all"]	= DEFAULT;
    choose["IsoTrack_miniPFRelIso_chg"]	= DEFAULT;
    choose["IsoTrack_pdgId"]	= DEFAULT;
    choose["IsoTrack_pfRelIso03_all"]	= DEFAULT;
    choose["IsoTrack_pfRelIso03_chg"]	= DEFAULT;
    choose["IsoTrack_phi"]	= DEFAULT;
    choose["IsoTrack_pt"]	= DEFAULT;
    choose["Jet_area"]	= DEFAULT;
    choose["Jet_bRegCorr"]	= DEFAULT;
    choose["Jet_bRegRes"]	= DEFAULT;
    choose["Jet_btagCSVV2"]	= DEFAULT;
    choose["Jet_btagDeepB"]	= DEFAULT;
    choose["Jet_btagDeepCvB"]	= DEFAULT;
    choose["Jet_btagDeepCvL"]	= DEFAULT;
    choose["Jet_btagDeepFlavB"]	= DEFAULT;
    choose["Jet_btagDeepFlavCvB"]	= DEFAULT;
    choose["Jet_btagDeepFlavCvL"]	= DEFAULT;
    choose["Jet_btagDeepFlavQG"]	= DEFAULT;
    choose["Jet_cRegCorr"]	= DEFAULT;
    choose["Jet_cRegRes"]	= DEFAULT;
    choose["Jet_chEmEF"]	= DEFAULT;
    choose["Jet_chFPV0EF"]	= DEFAULT;
    choose["Jet_chHEF"]	= DEFAULT;
    choose["Jet_cleanmask"]	= DEFAULT;
    choose["Jet_corr_JEC"]	= DEFAULT;
    choose["Jet_corr_JER"]	= DEFAULT;
    choose["Jet_electronIdx1"]	= DEFAULT;
    choose["Jet_electronIdx2"]	= DEFAULT;
    choose["Jet_eta"]	= DEFAULT;
    choose["Jet_genJetIdx"]	= DEFAULT;
    choose["Jet_hadronFlavour"]	= DEFAULT;
    choose["Jet_hfadjacentEtaStripsSize"]	= DEFAULT;
    choose["Jet_hfcentralEtaStripSize"]	= DEFAULT;
    choose["Jet_hfsigmaEtaEta"]	= DEFAULT;
    choose["Jet_hfsigmaPhiPhi"]	= DEFAULT;
    choose["Jet_jetId"]	= DEFAULT;
    choose["Jet_mass"]	= DEFAULT;
    choose["Jet_mass_jerDown"]	= DEFAULT;
    choose["Jet_mass_jerUp"]	= DEFAULT;
    choose["Jet_mass_jesTotalDown"]	= DEFAULT;
    choose["Jet_mass_jesTotalUp"]	= DEFAULT;
    choose["Jet_mass_nom"]	= DEFAULT;
    choose["Jet_mass_raw"]	= DEFAULT;
    choose["Jet_muEF"]	= DEFAULT;
    choose["Jet_muonIdx1"]	= DEFAULT;
    choose["Jet_muonIdx2"]	= DEFAULT;
    choose["Jet_muonSubtrFactor"]	= DEFAULT;
    choose["Jet_nConstituents"]	= DEFAULT;
    choose["Jet_nElectrons"]	= DEFAULT;
    choose["Jet_nMuons"]	= DEFAULT;
    choose["Jet_neEmEF"]	= DEFAULT;
    choose["Jet_neHEF"]	= DEFAULT;
    choose["Jet_partonFlavour"]	= DEFAULT;
    choose["Jet_phi"]	= DEFAULT;
    choose["Jet_pt"]	= DEFAULT;
    choose["Jet_pt_jerDown"]	= DEFAULT;
    choose["Jet_pt_jerUp"]	= DEFAULT;
    choose["Jet_pt_jesTotalDown"]	= DEFAULT;
    choose["Jet_pt_jesTotalUp"]	= DEFAULT;
    choose["Jet_pt_nom"]	= DEFAULT;
    choose["Jet_pt_raw"]	= DEFAULT;
    choose["Jet_puId"]	= DEFAULT;
    choose["Jet_puIdDisc"]	= DEFAULT;
    choose["Jet_qgl"]	= DEFAULT;
    choose["Jet_rawFactor"]	= DEFAULT;
    choose["L1PreFiringWeight_Dn"]	= DEFAULT;
    choose["L1PreFiringWeight_ECAL_Dn"]	= DEFAULT;
    choose["L1PreFiringWeight_ECAL_Nom"]	= DEFAULT;
    choose["L1PreFiringWeight_ECAL_Up"]	= DEFAULT;
    choose["L1PreFiringWeight_Muon_Nom"]	= DEFAULT;
    choose["L1PreFiringWeight_Muon_StatDn"]	= DEFAULT;
    choose["L1PreFiringWeight_Muon_StatUp"]	= DEFAULT;
    choose["L1PreFiringWeight_Muon_SystDn"]	= DEFAULT;
    choose["L1PreFiringWeight_Muon_SystUp"]	= DEFAULT;
    choose["L1PreFiringWeight_Nom"]	= DEFAULT;
    choose["L1PreFiringWeight_Up"]	= DEFAULT;
    choose["L1Reco_step"]	= DEFAULT;
    choose["L1simulation_step"]	= DEFAULT;
    choose["LHEPart_eta"]	= DEFAULT;
    choose["LHEPart_incomingpz"]	= DEFAULT;
    choose["LHEPart_mass"]	= DEFAULT;
    choose["LHEPart_pdgId"]	= DEFAULT;
    choose["LHEPart_phi"]	= DEFAULT;
    choose["LHEPart_pt"]	= DEFAULT;
    choose["LHEPart_spin"]	= DEFAULT;
    choose["LHEPart_status"]	= DEFAULT;
    choose["LHEPdfWeight"]	= DEFAULT;
    choose["LHEReweightingWeight"]	= DEFAULT;
    choose["LHEScaleWeight"]	= DEFAULT;
    choose["LHEWeight_originalXWGTUP"]	= DEFAULT;
    choose["LHE_AlphaS"]	= DEFAULT;
    choose["LHE_HT"]	= DEFAULT;
    choose["LHE_HTIncoming"]	= DEFAULT;
    choose["LHE_Nb"]	= DEFAULT;
    choose["LHE_Nc"]	= DEFAULT;
    choose["LHE_Nglu"]	= DEFAULT;
    choose["LHE_Njets"]	= DEFAULT;
    choose["LHE_NpLO"]	= DEFAULT;
    choose["LHE_NpNLO"]	= DEFAULT;
    choose["LHE_Nuds"]	= DEFAULT;
    choose["LHE_Vpt"]	= DEFAULT;
    choose["MET_MetUnclustEnUpDeltaX"]	= DEFAULT;
    choose["MET_MetUnclustEnUpDeltaY"]	= DEFAULT;
    choose["MET_T1Smear_phi"]	= DEFAULT;
    choose["MET_T1Smear_phi_jerDown"]	= DEFAULT;
    choose["MET_T1Smear_phi_jerUp"]	= DEFAULT;
    choose["MET_T1Smear_phi_jesTotalDown"]	= DEFAULT;
    choose["MET_T1Smear_phi_jesTotalUp"]	= DEFAULT;
    choose["MET_T1Smear_phi_unclustEnDown"]	= DEFAULT;
    choose["MET_T1Smear_phi_unclustEnUp"]	= DEFAULT;
    choose["MET_T1Smear_pt"]	= DEFAULT;
    choose["MET_T1Smear_pt_jerDown"]	= DEFAULT;
    choose["MET_T1Smear_pt_jerUp"]	= DEFAULT;
    choose["MET_T1Smear_pt_jesTotalDown"]	= DEFAULT;
    choose["MET_T1Smear_pt_jesTotalUp"]	= DEFAULT;
    choose["MET_T1Smear_pt_unclustEnDown"]	= DEFAULT;
    choose["MET_T1Smear_pt_unclustEnUp"]	= DEFAULT;
    choose["MET_T1_phi"]	= DEFAULT;
    choose["MET_T1_phi_jerDown"]	= DEFAULT;
    choose["MET_T1_phi_jerUp"]	= DEFAULT;
    choose["MET_T1_phi_jesTotalDown"]	= DEFAULT;
    choose["MET_T1_phi_jesTotalUp"]	= DEFAULT;
    choose["MET_T1_phi_unclustEnDown"]	= DEFAULT;
    choose["MET_T1_phi_unclustEnUp"]	= DEFAULT;
    choose["MET_T1_pt"]	= DEFAULT;
    choose["MET_T1_pt_jerDown"]	= DEFAULT;
    choose["MET_T1_pt_jerUp"]	= DEFAULT;
    choose["MET_T1_pt_jesTotalDown"]	= DEFAULT;
    choose["MET_T1_pt_jesTotalUp"]	= DEFAULT;
    choose["MET_T1_pt_unclustEnDown"]	= DEFAULT;
    choose["MET_T1_pt_unclustEnUp"]	= DEFAULT;
    choose["MET_covXX"]	= DEFAULT;
    choose["MET_covXY"]	= DEFAULT;
    choose["MET_covYY"]	= DEFAULT;
    choose["MET_fiducialGenPhi"]	= DEFAULT;
    choose["MET_fiducialGenPt"]	= DEFAULT;
    choose["MET_phi"]	= DEFAULT;
    choose["MET_pt"]	= DEFAULT;
    choose["MET_significance"]	= DEFAULT;
    choose["MET_sumEt"]	= DEFAULT;
    choose["MET_sumPtUnclustered"]	= DEFAULT;
    choose["Muon_charge"]	= DEFAULT;
    choose["Muon_cleanmask"]	= DEFAULT;
    choose["Muon_dxy"]	= DEFAULT;
    choose["Muon_dxyErr"]	= DEFAULT;
    choose["Muon_dxybs"]	= DEFAULT;
    choose["Muon_dz"]	= DEFAULT;
    choose["Muon_dzErr"]	= DEFAULT;
    choose["Muon_eta"]	= DEFAULT;
    choose["Muon_fsrPhotonIdx"]	= DEFAULT;
    choose["Muon_genPartFlav"]	= DEFAULT;
    choose["Muon_genPartIdx"]	= DEFAULT;
    choose["Muon_highPtId"]	= DEFAULT;
    choose["Muon_highPurity"]	= DEFAULT;
    choose["Muon_inTimeMuon"]	= DEFAULT;
    choose["Muon_ip3d"]	= DEFAULT;
    choose["Muon_isGlobal"]	= DEFAULT;
    choose["Muon_isPFcand"]	= DEFAULT;
    choose["Muon_isStandalone"]	= DEFAULT;
    choose["Muon_isTracker"]	= DEFAULT;
    choose["Muon_jetIdx"]	= DEFAULT;
    choose["Muon_jetNDauCharged"]	= DEFAULT;
    choose["Muon_jetPtRelv2"]	= DEFAULT;
    choose["Muon_jetRelIso"]	= DEFAULT;
    choose["Muon_looseId"]	= DEFAULT;
    choose["Muon_mass"]	= DEFAULT;
    choose["Muon_mediumId"]	= DEFAULT;
    choose["Muon_mediumPromptId"]	= DEFAULT;
    choose["Muon_miniIsoId"]	= DEFAULT;
    choose["Muon_miniPFRelIso_all"]	= DEFAULT;
    choose["Muon_miniPFRelIso_chg"]	= DEFAULT;
    choose["Muon_multiIsoId"]	= DEFAULT;
    choose["Muon_mvaId"]	= DEFAULT;
    choose["Muon_mvaLowPt"]	= DEFAULT;
    choose["Muon_mvaLowPtId"]	= DEFAULT;
    choose["Muon_mvaTTH"]	= DEFAULT;
    choose["Muon_nStations"]	= DEFAULT;
    choose["Muon_nTrackerLayers"]	= DEFAULT;
    choose["Muon_pdgId"]	= DEFAULT;
    choose["Muon_pfIsoId"]	= DEFAULT;
    choose["Muon_pfRelIso03_all"]	= DEFAULT;
    choose["Muon_pfRelIso03_chg"]	= DEFAULT;
    choose["Muon_pfRelIso04_all"]	= DEFAULT;
    choose["Muon_phi"]	= DEFAULT;
    choose["Muon_pt"]	= DEFAULT;
    choose["Muon_ptErr"]	= DEFAULT;
    choose["Muon_puppiIsoId"]	= DEFAULT;
    choose["Muon_segmentComp"]	= DEFAULT;
    choose["Muon_sip3d"]	= DEFAULT;
    choose["Muon_softId"]	= DEFAULT;
    choose["Muon_softMva"]	= DEFAULT;
    choose["Muon_softMvaId"]	= DEFAULT;
    choose["Muon_tightCharge"]	= DEFAULT;
    choose["Muon_tightId"]	= DEFAULT;
    choose["Muon_tkIsoId"]	= DEFAULT;
    choose["Muon_tkRelIso"]	= DEFAULT;
    choose["Muon_triggerIdLoose"]	= DEFAULT;
    choose["Muon_tunepRelPt"]	= DEFAULT;
    choose["OtherPV_z"]	= DEFAULT;
    choose["PSWeight"]	= DEFAULT;
    choose["PV_chi2"]	= DEFAULT;
    choose["PV_ndof"]	= DEFAULT;
    choose["PV_npvs"]	= DEFAULT;
    choose["PV_npvsGood"]	= DEFAULT;
    choose["PV_score"]	= DEFAULT;
    choose["PV_x"]	= DEFAULT;
    choose["PV_y"]	= DEFAULT;
    choose["PV_z"]	= DEFAULT;
    choose["Photon_charge"]	= DEFAULT;
    choose["Photon_cleanmask"]	= DEFAULT;
    choose["Photon_cutBased"]	= DEFAULT;
    choose["Photon_cutBased_Fall17V1Bitmap"]	= DEFAULT;
    choose["Photon_dEscaleDown"]	= DEFAULT;
    choose["Photon_dEscaleUp"]	= DEFAULT;
    choose["Photon_dEsigmaDown"]	= DEFAULT;
    choose["Photon_dEsigmaUp"]	= DEFAULT;
    choose["Photon_eCorr"]	= DEFAULT;
    choose["Photon_electronIdx"]	= DEFAULT;
    choose["Photon_electronVeto"]	= DEFAULT;
    choose["Photon_energyErr"]	= DEFAULT;
    choose["Photon_eta"]	= DEFAULT;
    choose["Photon_genPartFlav"]	= DEFAULT;
    choose["Photon_genPartIdx"]	= DEFAULT;
    choose["Photon_hoe"]	= DEFAULT;
    choose["Photon_isScEtaEB"]	= DEFAULT;
    choose["Photon_isScEtaEE"]	= DEFAULT;
    choose["Photon_jetIdx"]	= DEFAULT;
    choose["Photon_mass"]	= DEFAULT;
    choose["Photon_mvaID"]	= DEFAULT;
    choose["Photon_mvaID_Fall17V1p1"]	= DEFAULT;
    choose["Photon_mvaID_WP80"]	= DEFAULT;
    choose["Photon_mvaID_WP90"]	= DEFAULT;
    choose["Photon_pdgId"]	= DEFAULT;
    choose["Photon_pfRelIso03_all"]	= DEFAULT;
    choose["Photon_pfRelIso03_chg"]	= DEFAULT;
    choose["Photon_phi"]	= DEFAULT;
    choose["Photon_pixelSeed"]	= DEFAULT;
    choose["Photon_pt"]	= DEFAULT;
    choose["Photon_r9"]	= DEFAULT;
    choose["Photon_seedGain"]	= DEFAULT;
    choose["Photon_sieie"]	= DEFAULT;
    choose["Photon_vidNestedWPBitmap"]	= DEFAULT;
    choose["Pileup_gpudensity"]	= DEFAULT;
    choose["Pileup_nPU"]	= DEFAULT;
    choose["Pileup_nTrueInt"]	= DEFAULT;
    choose["Pileup_pudensity"]	= DEFAULT;
    choose["Pileup_sumEOOT"]	= DEFAULT;
    choose["Pileup_sumLOOT"]	= DEFAULT;
    choose["PuppiMET_phi"]	= DEFAULT;
    choose["PuppiMET_phiJERDown"]	= DEFAULT;
    choose["PuppiMET_phiJERUp"]	= DEFAULT;
    choose["PuppiMET_phiJESDown"]	= DEFAULT;
    choose["PuppiMET_phiJESUp"]	= DEFAULT;
    choose["PuppiMET_phiUnclusteredDown"]	= DEFAULT;
    choose["PuppiMET_phiUnclusteredUp"]	= DEFAULT;
    choose["PuppiMET_pt"]	= DEFAULT;
    choose["PuppiMET_ptJERDown"]	= DEFAULT;
    choose["PuppiMET_ptJERUp"]	= DEFAULT;
    choose["PuppiMET_ptJESDown"]	= DEFAULT;
    choose["PuppiMET_ptJESUp"]	= DEFAULT;
    choose["PuppiMET_ptUnclusteredDown"]	= DEFAULT;
    choose["PuppiMET_ptUnclusteredUp"]	= DEFAULT;
    choose["PuppiMET_sumEt"]	= DEFAULT;
    choose["RawMET_phi"]	= DEFAULT;
    choose["RawMET_pt"]	= DEFAULT;
    choose["RawMET_sumEt"]	= DEFAULT;
    choose["RawPuppiMET_phi"]	= DEFAULT;
    choose["RawPuppiMET_pt"]	= DEFAULT;
    choose["RawPuppiMET_sumEt"]	= DEFAULT;
    choose["SubGenJetAK8_eta"]	= DEFAULT;
    choose["SubGenJetAK8_mass"]	= DEFAULT;
    choose["SubGenJetAK8_phi"]	= DEFAULT;
    choose["SubGenJetAK8_pt"]	= DEFAULT;
    choose["SubJet_btagCSVV2"]	= DEFAULT;
    choose["SubJet_btagDeepB"]	= DEFAULT;
    choose["SubJet_eta"]	= DEFAULT;
    choose["SubJet_hadronFlavour"]	= DEFAULT;
    choose["SubJet_mass"]	= DEFAULT;
    choose["SubJet_n2b1"]	= DEFAULT;
    choose["SubJet_n3b1"]	= DEFAULT;
    choose["SubJet_nBHadrons"]	= DEFAULT;
    choose["SubJet_nCHadrons"]	= DEFAULT;
    choose["SubJet_phi"]	= DEFAULT;
    choose["SubJet_pt"]	= DEFAULT;
    choose["SubJet_rawFactor"]	= DEFAULT;
    choose["SubJet_tau1"]	= DEFAULT;
    choose["SubJet_tau2"]	= DEFAULT;
    choose["SubJet_tau3"]	= DEFAULT;
    choose["SubJet_tau4"]	= DEFAULT;
    choose["Tau_charge"]	= DEFAULT;
    choose["Tau_chargedIso"]	= DEFAULT;
    choose["Tau_cleanmask"]	= DEFAULT;
    choose["Tau_decayMode"]	= DEFAULT;
    choose["Tau_dxy"]	= DEFAULT;
    choose["Tau_dz"]	= DEFAULT;
    choose["Tau_eta"]	= DEFAULT;
    choose["Tau_genPartFlav"]	= DEFAULT;
    choose["Tau_genPartIdx"]	= DEFAULT;
    choose["Tau_idAntiEleDeadECal"]	= DEFAULT;
    choose["Tau_idAntiMu"]	= DEFAULT;
    choose["Tau_idDecayModeOldDMs"]	= DEFAULT;
    choose["Tau_idDeepTau2017v2p1VSe"]	= DEFAULT;
    choose["Tau_idDeepTau2017v2p1VSjet"]	= DEFAULT;
    choose["Tau_idDeepTau2017v2p1VSmu"]	= DEFAULT;
    choose["Tau_jetIdx"]	= DEFAULT;
    choose["Tau_leadTkDeltaEta"]	= DEFAULT;
    choose["Tau_leadTkDeltaPhi"]	= DEFAULT;
    choose["Tau_leadTkPtOverTauPt"]	= DEFAULT;
    choose["Tau_mass"]	= DEFAULT;
    choose["Tau_neutralIso"]	= DEFAULT;
    choose["Tau_phi"]	= DEFAULT;
    choose["Tau_photonsOutsideSignalCone"]	= DEFAULT;
    choose["Tau_pt"]	= DEFAULT;
    choose["Tau_puCorr"]	= DEFAULT;
    choose["Tau_rawDeepTau2017v2p1VSe"]	= DEFAULT;
    choose["Tau_rawDeepTau2017v2p1VSjet"]	= DEFAULT;
    choose["Tau_rawDeepTau2017v2p1VSmu"]	= DEFAULT;
    choose["Tau_rawIso"]	= DEFAULT;
    choose["Tau_rawIsodR03"]	= DEFAULT;
    choose["TkMET_phi"]	= DEFAULT;
    choose["TkMET_pt"]	= DEFAULT;
    choose["TkMET_sumEt"]	= DEFAULT;
    choose["TrigObj_eta"]	= DEFAULT;
    choose["TrigObj_filterBits"]	= DEFAULT;
    choose["TrigObj_id"]	= DEFAULT;
    choose["TrigObj_l1charge"]	= DEFAULT;
    choose["TrigObj_l1iso"]	= DEFAULT;
    choose["TrigObj_l1pt"]	= DEFAULT;
    choose["TrigObj_l1pt_2"]	= DEFAULT;
    choose["TrigObj_l2pt"]	= DEFAULT;
    choose["TrigObj_phi"]	= DEFAULT;
    choose["TrigObj_pt"]	= DEFAULT;
    choose["boostedTau_charge"]	= DEFAULT;
    choose["boostedTau_chargedIso"]	= DEFAULT;
    choose["boostedTau_decayMode"]	= DEFAULT;
    choose["boostedTau_eta"]	= DEFAULT;
    choose["boostedTau_genPartFlav"]	= DEFAULT;
    choose["boostedTau_genPartIdx"]	= DEFAULT;
    choose["boostedTau_idAntiEle2018"]	= DEFAULT;
    choose["boostedTau_idAntiMu"]	= DEFAULT;
    choose["boostedTau_idMVAnewDM2017v2"]	= DEFAULT;
    choose["boostedTau_idMVAoldDM2017v2"]	= DEFAULT;
    choose["boostedTau_idMVAoldDMdR032017v2"]	= DEFAULT;
    choose["boostedTau_jetIdx"]	= DEFAULT;
    choose["boostedTau_leadTkDeltaEta"]	= DEFAULT;
    choose["boostedTau_leadTkDeltaPhi"]	= DEFAULT;
    choose["boostedTau_leadTkPtOverTauPt"]	= DEFAULT;
    choose["boostedTau_mass"]	= DEFAULT;
    choose["boostedTau_neutralIso"]	= DEFAULT;
    choose["boostedTau_phi"]	= DEFAULT;
    choose["boostedTau_photonsOutsideSignalCone"]	= DEFAULT;
    choose["boostedTau_pt"]	= DEFAULT;
    choose["boostedTau_puCorr"]	= DEFAULT;
    choose["boostedTau_rawAntiEle2018"]	= DEFAULT;
    choose["boostedTau_rawAntiEleCat2018"]	= DEFAULT;
    choose["boostedTau_rawIso"]	= DEFAULT;
    choose["boostedTau_rawIsodR03"]	= DEFAULT;
    choose["boostedTau_rawMVAnewDM2017v2"]	= DEFAULT;
    choose["boostedTau_rawMVAoldDM2017v2"]	= DEFAULT;
    choose["boostedTau_rawMVAoldDMdR032017v2"]	= DEFAULT;
    choose["btagWeight_CSVV2"]	= DEFAULT;
    choose["btagWeight_DeepCSVB"]	= DEFAULT;
    choose["event"]	= DEFAULT;
    choose["eventWeight"]	= DEFAULT;
    choose["fixedGridRhoFastjetAll"]	= DEFAULT;
    choose["fixedGridRhoFastjetCentral"]	= DEFAULT;
    choose["fixedGridRhoFastjetCentralCalo"]	= DEFAULT;
    choose["fixedGridRhoFastjetCentralChargedPileUp"]	= DEFAULT;
    choose["fixedGridRhoFastjetCentralNeutral"]	= DEFAULT;
    choose["genTtbarId"]	= DEFAULT;
    choose["genWeight"]	= DEFAULT;
    choose["luminosityBlock"]	= DEFAULT;
    choose["puWeight"]	= DEFAULT;
    choose["puWeightDown"]	= DEFAULT;
    choose["puWeightUp"]	= DEFAULT;
    choose["run"]	= DEFAULT;

    if ( DEFAULT )
      {
        std::cout << std::endl
                  << "eventBuffer - All branches selected"
                  << std::endl;
      }
    else
      {
        std::cout << "eventBuffer - branches selected:"
                  << std::endl;      
        std::istringstream sin(varlist);
        while ( sin )
          {
            std::string key;
            sin >> key;
            if ( sin )
              {
		        std::map<std::string, bool>::iterator it;
		        for(it = choose.begin(); it != choose.end(); it++)
		          {
		            if ( it->first.length() > key.length() )
		              {
			            if ( it->first.substr(0, key.size()) == key )
			              {
			                choose[it->first] = true;
			              }
		              }
                  }
              }
          }
      }
    if ( choose["CaloMET_phi"] )
      input->select("Events/CaloMET_phi", 	CaloMET_phi);
    if ( choose["CaloMET_pt"] )
      input->select("Events/CaloMET_pt", 	CaloMET_pt);
    if ( choose["CaloMET_sumEt"] )
      input->select("Events/CaloMET_sumEt", 	CaloMET_sumEt);
    if ( choose["ChsMET_phi"] )
      input->select("Events/ChsMET_phi", 	ChsMET_phi);
    if ( choose["ChsMET_pt"] )
      input->select("Events/ChsMET_pt", 	ChsMET_pt);
    if ( choose["ChsMET_sumEt"] )
      input->select("Events/ChsMET_sumEt", 	ChsMET_sumEt);
    if ( choose["CorrT1METJet_area"] )
      input->select("Events/CorrT1METJet_area", 	CorrT1METJet_area);
    if ( choose["CorrT1METJet_eta"] )
      input->select("Events/CorrT1METJet_eta", 	CorrT1METJet_eta);
    if ( choose["CorrT1METJet_muonSubtrFactor"] )
      input->select("Events/CorrT1METJet_muonSubtrFactor",
                     CorrT1METJet_muonSubtrFactor);
    if ( choose["CorrT1METJet_phi"] )
      input->select("Events/CorrT1METJet_phi", 	CorrT1METJet_phi);
    if ( choose["CorrT1METJet_rawPt"] )
      input->select("Events/CorrT1METJet_rawPt", 	CorrT1METJet_rawPt);
    if ( choose["DeepMETResolutionTune_phi"] )
      input->select("Events/DeepMETResolutionTune_phi",
                     DeepMETResolutionTune_phi);
    if ( choose["DeepMETResolutionTune_pt"] )
      input->select("Events/DeepMETResolutionTune_pt",
                     DeepMETResolutionTune_pt);
    if ( choose["DeepMETResponseTune_phi"] )
      input->select("Events/DeepMETResponseTune_phi",
                     DeepMETResponseTune_phi);
    if ( choose["DeepMETResponseTune_pt"] )
      input->select("Events/DeepMETResponseTune_pt",
                     DeepMETResponseTune_pt);
    if ( choose["Electron_charge"] )
      input->select("Events/Electron_charge", 	Electron_charge);
    if ( choose["Electron_cleanmask"] )
      input->select("Events/Electron_cleanmask", 	Electron_cleanmask);
    if ( choose["Electron_convVeto"] )
      input->select("Events/Electron_convVeto", 	Electron_convVeto);
    if ( choose["Electron_cutBased"] )
      input->select("Events/Electron_cutBased", 	Electron_cutBased);
    if ( choose["Electron_cutBased_HEEP"] )
      input->select("Events/Electron_cutBased_HEEP",
                     Electron_cutBased_HEEP);
    if ( choose["Electron_dEscaleDown"] )
      input->select("Events/Electron_dEscaleDown", 	Electron_dEscaleDown);
    if ( choose["Electron_dEscaleUp"] )
      input->select("Events/Electron_dEscaleUp", 	Electron_dEscaleUp);
    if ( choose["Electron_dEsigmaDown"] )
      input->select("Events/Electron_dEsigmaDown", 	Electron_dEsigmaDown);
    if ( choose["Electron_dEsigmaUp"] )
      input->select("Events/Electron_dEsigmaUp", 	Electron_dEsigmaUp);
    if ( choose["Electron_deltaEtaSC"] )
      input->select("Events/Electron_deltaEtaSC", 	Electron_deltaEtaSC);
    if ( choose["Electron_dr03EcalRecHitSumEt"] )
      input->select("Events/Electron_dr03EcalRecHitSumEt",
                     Electron_dr03EcalRecHitSumEt);
    if ( choose["Electron_dr03HcalDepth1TowerSumEt"] )
      input->select("Events/Electron_dr03HcalDepth1TowerSumEt",
                     Electron_dr03HcalDepth1TowerSumEt);
    if ( choose["Electron_dr03TkSumPt"] )
      input->select("Events/Electron_dr03TkSumPt", 	Electron_dr03TkSumPt);
    if ( choose["Electron_dr03TkSumPtHEEP"] )
      input->select("Events/Electron_dr03TkSumPtHEEP",
                     Electron_dr03TkSumPtHEEP);
    if ( choose["Electron_dxy"] )
      input->select("Events/Electron_dxy", 	Electron_dxy);
    if ( choose["Electron_dxyErr"] )
      input->select("Events/Electron_dxyErr", 	Electron_dxyErr);
    if ( choose["Electron_dz"] )
      input->select("Events/Electron_dz", 	Electron_dz);
    if ( choose["Electron_dzErr"] )
      input->select("Events/Electron_dzErr", 	Electron_dzErr);
    if ( choose["Electron_eCorr"] )
      input->select("Events/Electron_eCorr", 	Electron_eCorr);
    if ( choose["Electron_eInvMinusPInv"] )
      input->select("Events/Electron_eInvMinusPInv",
                     Electron_eInvMinusPInv);
    if ( choose["Electron_energyErr"] )
      input->select("Events/Electron_energyErr", 	Electron_energyErr);
    if ( choose["Electron_eta"] )
      input->select("Events/Electron_eta", 	Electron_eta);
    if ( choose["Electron_genPartFlav"] )
      input->select("Events/Electron_genPartFlav", 	Electron_genPartFlav);
    if ( choose["Electron_genPartIdx"] )
      input->select("Events/Electron_genPartIdx", 	Electron_genPartIdx);
    if ( choose["Electron_hoe"] )
      input->select("Events/Electron_hoe", 	Electron_hoe);
    if ( choose["Electron_ip3d"] )
      input->select("Events/Electron_ip3d", 	Electron_ip3d);
    if ( choose["Electron_isPFcand"] )
      input->select("Events/Electron_isPFcand", 	Electron_isPFcand);
    if ( choose["Electron_jetIdx"] )
      input->select("Events/Electron_jetIdx", 	Electron_jetIdx);
    if ( choose["Electron_jetNDauCharged"] )
      input->select("Events/Electron_jetNDauCharged",
                     Electron_jetNDauCharged);
    if ( choose["Electron_jetPtRelv2"] )
      input->select("Events/Electron_jetPtRelv2", 	Electron_jetPtRelv2);
    if ( choose["Electron_jetRelIso"] )
      input->select("Events/Electron_jetRelIso", 	Electron_jetRelIso);
    if ( choose["Electron_lostHits"] )
      input->select("Events/Electron_lostHits", 	Electron_lostHits);
    if ( choose["Electron_mass"] )
      input->select("Events/Electron_mass", 	Electron_mass);
    if ( choose["Electron_miniPFRelIso_all"] )
      input->select("Events/Electron_miniPFRelIso_all",
                     Electron_miniPFRelIso_all);
    if ( choose["Electron_miniPFRelIso_chg"] )
      input->select("Events/Electron_miniPFRelIso_chg",
                     Electron_miniPFRelIso_chg);
    if ( choose["Electron_mvaFall17V2Iso"] )
      input->select("Events/Electron_mvaFall17V2Iso",
                     Electron_mvaFall17V2Iso);
    if ( choose["Electron_mvaFall17V2Iso_WP80"] )
      input->select("Events/Electron_mvaFall17V2Iso_WP80",
                     Electron_mvaFall17V2Iso_WP80);
    if ( choose["Electron_mvaFall17V2Iso_WP90"] )
      input->select("Events/Electron_mvaFall17V2Iso_WP90",
                     Electron_mvaFall17V2Iso_WP90);
    if ( choose["Electron_mvaFall17V2Iso_WPL"] )
      input->select("Events/Electron_mvaFall17V2Iso_WPL",
                     Electron_mvaFall17V2Iso_WPL);
    if ( choose["Electron_mvaFall17V2noIso"] )
      input->select("Events/Electron_mvaFall17V2noIso",
                     Electron_mvaFall17V2noIso);
    if ( choose["Electron_mvaFall17V2noIso_WP80"] )
      input->select("Events/Electron_mvaFall17V2noIso_WP80",
                     Electron_mvaFall17V2noIso_WP80);
    if ( choose["Electron_mvaFall17V2noIso_WP90"] )
      input->select("Events/Electron_mvaFall17V2noIso_WP90",
                     Electron_mvaFall17V2noIso_WP90);
    if ( choose["Electron_mvaFall17V2noIso_WPL"] )
      input->select("Events/Electron_mvaFall17V2noIso_WPL",
                     Electron_mvaFall17V2noIso_WPL);
    if ( choose["Electron_mvaTTH"] )
      input->select("Events/Electron_mvaTTH", 	Electron_mvaTTH);
    if ( choose["Electron_pdgId"] )
      input->select("Events/Electron_pdgId", 	Electron_pdgId);
    if ( choose["Electron_pfRelIso03_all"] )
      input->select("Events/Electron_pfRelIso03_all",
                     Electron_pfRelIso03_all);
    if ( choose["Electron_pfRelIso03_chg"] )
      input->select("Events/Electron_pfRelIso03_chg",
                     Electron_pfRelIso03_chg);
    if ( choose["Electron_phi"] )
      input->select("Events/Electron_phi", 	Electron_phi);
    if ( choose["Electron_photonIdx"] )
      input->select("Events/Electron_photonIdx", 	Electron_photonIdx);
    if ( choose["Electron_pt"] )
      input->select("Events/Electron_pt", 	Electron_pt);
    if ( choose["Electron_r9"] )
      input->select("Events/Electron_r9", 	Electron_r9);
    if ( choose["Electron_scEtOverPt"] )
      input->select("Events/Electron_scEtOverPt", 	Electron_scEtOverPt);
    if ( choose["Electron_seedGain"] )
      input->select("Events/Electron_seedGain", 	Electron_seedGain);
    if ( choose["Electron_sieie"] )
      input->select("Events/Electron_sieie", 	Electron_sieie);
    if ( choose["Electron_sip3d"] )
      input->select("Events/Electron_sip3d", 	Electron_sip3d);
    if ( choose["Electron_tightCharge"] )
      input->select("Events/Electron_tightCharge", 	Electron_tightCharge);
    if ( choose["Electron_vidNestedWPBitmap"] )
      input->select("Events/Electron_vidNestedWPBitmap",
                     Electron_vidNestedWPBitmap);
    if ( choose["Electron_vidNestedWPBitmapHEEP"] )
      input->select("Events/Electron_vidNestedWPBitmapHEEP",
                     Electron_vidNestedWPBitmapHEEP);
    if ( choose["FatJet_area"] )
      input->select("Events/FatJet_area", 	FatJet_area);
    if ( choose["FatJet_btagCSVV2"] )
      input->select("Events/FatJet_btagCSVV2", 	FatJet_btagCSVV2);
    if ( choose["FatJet_btagDDBvLV2"] )
      input->select("Events/FatJet_btagDDBvLV2", 	FatJet_btagDDBvLV2);
    if ( choose["FatJet_btagDDCvBV2"] )
      input->select("Events/FatJet_btagDDCvBV2", 	FatJet_btagDDCvBV2);
    if ( choose["FatJet_btagDDCvLV2"] )
      input->select("Events/FatJet_btagDDCvLV2", 	FatJet_btagDDCvLV2);
    if ( choose["FatJet_btagDeepB"] )
      input->select("Events/FatJet_btagDeepB", 	FatJet_btagDeepB);
    if ( choose["FatJet_btagHbb"] )
      input->select("Events/FatJet_btagHbb", 	FatJet_btagHbb);
    if ( choose["FatJet_corr_JEC"] )
      input->select("Events/FatJet_corr_JEC", 	FatJet_corr_JEC);
    if ( choose["FatJet_corr_JER"] )
      input->select("Events/FatJet_corr_JER", 	FatJet_corr_JER);
    if ( choose["FatJet_corr_JMR"] )
      input->select("Events/FatJet_corr_JMR", 	FatJet_corr_JMR);
    if ( choose["FatJet_corr_JMS"] )
      input->select("Events/FatJet_corr_JMS", 	FatJet_corr_JMS);
    if ( choose["FatJet_deepTagMD_H4qvsQCD"] )
      input->select("Events/FatJet_deepTagMD_H4qvsQCD",
                     FatJet_deepTagMD_H4qvsQCD);
    if ( choose["FatJet_deepTagMD_HbbvsQCD"] )
      input->select("Events/FatJet_deepTagMD_HbbvsQCD",
                     FatJet_deepTagMD_HbbvsQCD);
    if ( choose["FatJet_deepTagMD_TvsQCD"] )
      input->select("Events/FatJet_deepTagMD_TvsQCD",
                     FatJet_deepTagMD_TvsQCD);
    if ( choose["FatJet_deepTagMD_WvsQCD"] )
      input->select("Events/FatJet_deepTagMD_WvsQCD",
                     FatJet_deepTagMD_WvsQCD);
    if ( choose["FatJet_deepTagMD_ZHbbvsQCD"] )
      input->select("Events/FatJet_deepTagMD_ZHbbvsQCD",
                     FatJet_deepTagMD_ZHbbvsQCD);
    if ( choose["FatJet_deepTagMD_ZHccvsQCD"] )
      input->select("Events/FatJet_deepTagMD_ZHccvsQCD",
                     FatJet_deepTagMD_ZHccvsQCD);
    if ( choose["FatJet_deepTagMD_ZbbvsQCD"] )
      input->select("Events/FatJet_deepTagMD_ZbbvsQCD",
                     FatJet_deepTagMD_ZbbvsQCD);
    if ( choose["FatJet_deepTagMD_ZvsQCD"] )
      input->select("Events/FatJet_deepTagMD_ZvsQCD",
                     FatJet_deepTagMD_ZvsQCD);
    if ( choose["FatJet_deepTagMD_bbvsLight"] )
      input->select("Events/FatJet_deepTagMD_bbvsLight",
                     FatJet_deepTagMD_bbvsLight);
    if ( choose["FatJet_deepTagMD_ccvsLight"] )
      input->select("Events/FatJet_deepTagMD_ccvsLight",
                     FatJet_deepTagMD_ccvsLight);
    if ( choose["FatJet_deepTag_H"] )
      input->select("Events/FatJet_deepTag_H", 	FatJet_deepTag_H);
    if ( choose["FatJet_deepTag_QCD"] )
      input->select("Events/FatJet_deepTag_QCD", 	FatJet_deepTag_QCD);
    if ( choose["FatJet_deepTag_QCDothers"] )
      input->select("Events/FatJet_deepTag_QCDothers",
                     FatJet_deepTag_QCDothers);
    if ( choose["FatJet_deepTag_TvsQCD"] )
      input->select("Events/FatJet_deepTag_TvsQCD", 	FatJet_deepTag_TvsQCD);
    if ( choose["FatJet_deepTag_WvsQCD"] )
      input->select("Events/FatJet_deepTag_WvsQCD", 	FatJet_deepTag_WvsQCD);
    if ( choose["FatJet_deepTag_ZvsQCD"] )
      input->select("Events/FatJet_deepTag_ZvsQCD", 	FatJet_deepTag_ZvsQCD);
    if ( choose["FatJet_electronIdx3SJ"] )
      input->select("Events/FatJet_electronIdx3SJ", 	FatJet_electronIdx3SJ);
    if ( choose["FatJet_eta"] )
      input->select("Events/FatJet_eta", 	FatJet_eta);
    if ( choose["FatJet_genJetAK8Idx"] )
      input->select("Events/FatJet_genJetAK8Idx", 	FatJet_genJetAK8Idx);
    if ( choose["FatJet_hadronFlavour"] )
      input->select("Events/FatJet_hadronFlavour", 	FatJet_hadronFlavour);
    if ( choose["FatJet_jetId"] )
      input->select("Events/FatJet_jetId", 	FatJet_jetId);
    if ( choose["FatJet_lsf3"] )
      input->select("Events/FatJet_lsf3", 	FatJet_lsf3);
    if ( choose["FatJet_mass"] )
      input->select("Events/FatJet_mass", 	FatJet_mass_nom);
    if ( choose["FatJet_mass_jerDown"] )
      input->select("Events/FatJet_mass_jerDown", 	FatJet_mass_jerDown);
    if ( choose["FatJet_mass_jerUp"] )
      input->select("Events/FatJet_mass_jerUp", 	FatJet_mass_jerUp);
    if ( choose["FatJet_mass_jesTotalDown"] )
      input->select("Events/FatJet_mass_jesTotalDown",
                     FatJet_mass_jesTotalDown);
    if ( choose["FatJet_mass_jesTotalUp"] )
      input->select("Events/FatJet_mass_jesTotalUp",
                     FatJet_mass_jesTotalUp);
    if ( choose["FatJet_mass_jmrDown"] )
      input->select("Events/FatJet_mass_jmrDown", 	FatJet_mass_jmrDown);
    if ( choose["FatJet_mass_jmrUp"] )
      input->select("Events/FatJet_mass_jmrUp", 	FatJet_mass_jmrUp);
    if ( choose["FatJet_mass_jmsDown"] )
      input->select("Events/FatJet_mass_jmsDown", 	FatJet_mass_jmsDown);
    if ( choose["FatJet_mass_jmsUp"] )
      input->select("Events/FatJet_mass_jmsUp", 	FatJet_mass_jmsUp);
    if ( choose["FatJet_mass_nom"] )
      input->select("Events/FatJet_mass_nom", 	FatJet_mass_nom);
    if ( choose["FatJet_mass_raw"] )
      input->select("Events/FatJet_mass_raw", 	FatJet_mass_raw);
    if ( choose["FatJet_msoftdrop"] )
      input->select("Events/FatJet_msoftdrop", 	FatJet_msoftdrop_nom);
    if ( choose["FatJet_msoftdrop_corr_JMR"] )
      input->select("Events/FatJet_msoftdrop_corr_JMR",
                     FatJet_msoftdrop_corr_JMR);
    if ( choose["FatJet_msoftdrop_corr_JMS"] )
      input->select("Events/FatJet_msoftdrop_corr_JMS",
                     FatJet_msoftdrop_corr_JMS);
    if ( choose["FatJet_msoftdrop_corr_PUPPI"] )
      input->select("Events/FatJet_msoftdrop_corr_PUPPI",
                     FatJet_msoftdrop_corr_PUPPI);
    if ( choose["FatJet_msoftdrop_jerDown"] )
      input->select("Events/FatJet_msoftdrop_jerDown",
                     FatJet_msoftdrop_jerDown);
    if ( choose["FatJet_msoftdrop_jerUp"] )
      input->select("Events/FatJet_msoftdrop_jerUp",
                     FatJet_msoftdrop_jerUp);
    if ( choose["FatJet_msoftdrop_jesTotalDown"] )
      input->select("Events/FatJet_msoftdrop_jesTotalDown",
                     FatJet_msoftdrop_jesTotalDown);
    if ( choose["FatJet_msoftdrop_jesTotalUp"] )
      input->select("Events/FatJet_msoftdrop_jesTotalUp",
                     FatJet_msoftdrop_jesTotalUp);
    if ( choose["FatJet_msoftdrop_jmrDown"] )
      input->select("Events/FatJet_msoftdrop_jmrDown",
                     FatJet_msoftdrop_jmrDown);
    if ( choose["FatJet_msoftdrop_jmrUp"] )
      input->select("Events/FatJet_msoftdrop_jmrUp",
                     FatJet_msoftdrop_jmrUp);
    if ( choose["FatJet_msoftdrop_jmsDown"] )
      input->select("Events/FatJet_msoftdrop_jmsDown",
                     FatJet_msoftdrop_jmsDown);
    if ( choose["FatJet_msoftdrop_jmsUp"] )
      input->select("Events/FatJet_msoftdrop_jmsUp",
                     FatJet_msoftdrop_jmsUp);
    if ( choose["FatJet_msoftdrop_nom"] )
      input->select("Events/FatJet_msoftdrop_nom", 	FatJet_msoftdrop_nom);
    if ( choose["FatJet_msoftdrop_raw"] )
      input->select("Events/FatJet_msoftdrop_raw", 	FatJet_msoftdrop_raw);
    if ( choose["FatJet_msoftdrop_tau21DDT_jerDown"] )
      input->select("Events/FatJet_msoftdrop_tau21DDT_jerDown",
                     FatJet_msoftdrop_tau21DDT_jerDown);
    if ( choose["FatJet_msoftdrop_tau21DDT_jerUp"] )
      input->select("Events/FatJet_msoftdrop_tau21DDT_jerUp",
                     FatJet_msoftdrop_tau21DDT_jerUp);
    if ( choose["FatJet_msoftdrop_tau21DDT_jmrDown"] )
      input->select("Events/FatJet_msoftdrop_tau21DDT_jmrDown",
                     FatJet_msoftdrop_tau21DDT_jmrDown);
    if ( choose["FatJet_msoftdrop_tau21DDT_jmrUp"] )
      input->select("Events/FatJet_msoftdrop_tau21DDT_jmrUp",
                     FatJet_msoftdrop_tau21DDT_jmrUp);
    if ( choose["FatJet_msoftdrop_tau21DDT_jmsDown"] )
      input->select("Events/FatJet_msoftdrop_tau21DDT_jmsDown",
                     FatJet_msoftdrop_tau21DDT_jmsDown);
    if ( choose["FatJet_msoftdrop_tau21DDT_jmsUp"] )
      input->select("Events/FatJet_msoftdrop_tau21DDT_jmsUp",
                     FatJet_msoftdrop_tau21DDT_jmsUp);
    if ( choose["FatJet_msoftdrop_tau21DDT_nom"] )
      input->select("Events/FatJet_msoftdrop_tau21DDT_nom",
                     FatJet_msoftdrop_tau21DDT_nom);
    if ( choose["FatJet_muonIdx3SJ"] )
      input->select("Events/FatJet_muonIdx3SJ", 	FatJet_muonIdx3SJ);
    if ( choose["FatJet_n2b1"] )
      input->select("Events/FatJet_n2b1", 	FatJet_n2b1);
    if ( choose["FatJet_n3b1"] )
      input->select("Events/FatJet_n3b1", 	FatJet_n3b1);
    if ( choose["FatJet_nBHadrons"] )
      input->select("Events/FatJet_nBHadrons", 	FatJet_nBHadrons);
    if ( choose["FatJet_nCHadrons"] )
      input->select("Events/FatJet_nCHadrons", 	FatJet_nCHadrons);
    if ( choose["FatJet_nConstituents"] )
      input->select("Events/FatJet_nConstituents", 	FatJet_nConstituents);
    if ( choose["FatJet_particleNetMD_QCD"] )
      input->select("Events/FatJet_particleNetMD_QCD",
                     FatJet_particleNetMD_QCD);
    if ( choose["FatJet_particleNetMD_Xbb"] )
      input->select("Events/FatJet_particleNetMD_Xbb",
                     FatJet_particleNetMD_Xbb);
    if ( choose["FatJet_particleNetMD_Xcc"] )
      input->select("Events/FatJet_particleNetMD_Xcc",
                     FatJet_particleNetMD_Xcc);
    if ( choose["FatJet_particleNetMD_Xqq"] )
      input->select("Events/FatJet_particleNetMD_Xqq",
                     FatJet_particleNetMD_Xqq);
    if ( choose["FatJet_particleNet_H4qvsQCD"] )
      input->select("Events/FatJet_particleNet_H4qvsQCD",
                     FatJet_particleNet_H4qvsQCD);
    if ( choose["FatJet_particleNet_HbbvsQCD"] )
      input->select("Events/FatJet_particleNet_HbbvsQCD",
                     FatJet_particleNet_HbbvsQCD);
    if ( choose["FatJet_particleNet_HccvsQCD"] )
      input->select("Events/FatJet_particleNet_HccvsQCD",
                     FatJet_particleNet_HccvsQCD);
    if ( choose["FatJet_particleNet_QCD"] )
      input->select("Events/FatJet_particleNet_QCD",
                     FatJet_particleNet_QCD);
    if ( choose["FatJet_particleNet_TvsQCD"] )
      input->select("Events/FatJet_particleNet_TvsQCD",
                     FatJet_particleNet_TvsQCD);
    if ( choose["FatJet_particleNet_WvsQCD"] )
      input->select("Events/FatJet_particleNet_WvsQCD",
                     FatJet_particleNet_WvsQCD);
    if ( choose["FatJet_particleNet_ZvsQCD"] )
      input->select("Events/FatJet_particleNet_ZvsQCD",
                     FatJet_particleNet_ZvsQCD);
    if ( choose["FatJet_particleNet_mass"] )
      input->select("Events/FatJet_particleNet_mass",
                     FatJet_particleNet_mass);
    if ( choose["FatJet_phi"] )
      input->select("Events/FatJet_phi", 	FatJet_phi);
    if ( choose["FatJet_pt"] )
      input->select("Events/FatJet_pt", 	FatJet_pt_nom);
    if ( choose["FatJet_pt_jerDown"] )
      input->select("Events/FatJet_pt_jerDown", 	FatJet_pt_jerDown);
    if ( choose["FatJet_pt_jerUp"] )
      input->select("Events/FatJet_pt_jerUp", 	FatJet_pt_jerUp);
    if ( choose["FatJet_pt_jesTotalDown"] )
      input->select("Events/FatJet_pt_jesTotalDown",
                     FatJet_pt_jesTotalDown);
    if ( choose["FatJet_pt_jesTotalUp"] )
      input->select("Events/FatJet_pt_jesTotalUp", 	FatJet_pt_jesTotalUp);
    if ( choose["FatJet_pt_nom"] )
      input->select("Events/FatJet_pt_nom", 	FatJet_pt_nom);
    if ( choose["FatJet_pt_raw"] )
      input->select("Events/FatJet_pt_raw", 	FatJet_pt_raw);
    if ( choose["FatJet_rawFactor"] )
      input->select("Events/FatJet_rawFactor", 	FatJet_rawFactor);
    if ( choose["FatJet_subJetIdx1"] )
      input->select("Events/FatJet_subJetIdx1", 	FatJet_subJetIdx1);
    if ( choose["FatJet_subJetIdx2"] )
      input->select("Events/FatJet_subJetIdx2", 	FatJet_subJetIdx2);
    if ( choose["FatJet_tau1"] )
      input->select("Events/FatJet_tau1", 	FatJet_tau1);
    if ( choose["FatJet_tau2"] )
      input->select("Events/FatJet_tau2", 	FatJet_tau2);
    if ( choose["FatJet_tau3"] )
      input->select("Events/FatJet_tau3", 	FatJet_tau3);
    if ( choose["FatJet_tau4"] )
      input->select("Events/FatJet_tau4", 	FatJet_tau4);
    if ( choose["Flag_BadChargedCandidateFilter"] )
      input->select("Events/Flag_BadChargedCandidateFilter",
                     Flag_BadChargedCandidateFilter);
    if ( choose["Flag_BadChargedCandidateSummer16Filter"] )
      input->select("Events/Flag_BadChargedCandidateSummer16Filter",
                     Flag_BadChargedCandidateSummer16Filter);
    if ( choose["Flag_BadPFMuonDzFilter"] )
      input->select("Events/Flag_BadPFMuonDzFilter",
                     Flag_BadPFMuonDzFilter);
    if ( choose["Flag_BadPFMuonFilter"] )
      input->select("Events/Flag_BadPFMuonFilter", 	Flag_BadPFMuonFilter);
    if ( choose["Flag_BadPFMuonSummer16Filter"] )
      input->select("Events/Flag_BadPFMuonSummer16Filter",
                     Flag_BadPFMuonSummer16Filter);
    if ( choose["Flag_CSCTightHalo2015Filter"] )
      input->select("Events/Flag_CSCTightHalo2015Filter",
                     Flag_CSCTightHalo2015Filter);
    if ( choose["Flag_CSCTightHaloFilter"] )
      input->select("Events/Flag_CSCTightHaloFilter",
                     Flag_CSCTightHaloFilter);
    if ( choose["Flag_CSCTightHaloTrkMuUnvetoFilter"] )
      input->select("Events/Flag_CSCTightHaloTrkMuUnvetoFilter",
                     Flag_CSCTightHaloTrkMuUnvetoFilter);
    if ( choose["Flag_EcalDeadCellBoundaryEnergyFilter"] )
      input->select("Events/Flag_EcalDeadCellBoundaryEnergyFilter",
                     Flag_EcalDeadCellBoundaryEnergyFilter);
    if ( choose["Flag_EcalDeadCellTriggerPrimitiveFilter"] )
      input->select("Events/Flag_EcalDeadCellTriggerPrimitiveFilter",
                     Flag_EcalDeadCellTriggerPrimitiveFilter);
    if ( choose["Flag_HBHENoiseFilter"] )
      input->select("Events/Flag_HBHENoiseFilter", 	Flag_HBHENoiseFilter);
    if ( choose["Flag_HBHENoiseIsoFilter"] )
      input->select("Events/Flag_HBHENoiseIsoFilter",
                     Flag_HBHENoiseIsoFilter);
    if ( choose["Flag_HcalStripHaloFilter"] )
      input->select("Events/Flag_HcalStripHaloFilter",
                     Flag_HcalStripHaloFilter);
    if ( choose["Flag_METFilters"] )
      input->select("Events/Flag_METFilters", 	Flag_METFilters);
    if ( choose["Flag_chargedHadronTrackResolutionFilter"] )
      input->select("Events/Flag_chargedHadronTrackResolutionFilter",
                     Flag_chargedHadronTrackResolutionFilter);
    if ( choose["Flag_ecalBadCalibFilter"] )
      input->select("Events/Flag_ecalBadCalibFilter",
                     Flag_ecalBadCalibFilter);
    if ( choose["Flag_ecalLaserCorrFilter"] )
      input->select("Events/Flag_ecalLaserCorrFilter",
                     Flag_ecalLaserCorrFilter);
    if ( choose["Flag_eeBadScFilter"] )
      input->select("Events/Flag_eeBadScFilter", 	Flag_eeBadScFilter);
    if ( choose["Flag_globalSuperTightHalo2016Filter"] )
      input->select("Events/Flag_globalSuperTightHalo2016Filter",
                     Flag_globalSuperTightHalo2016Filter);
    if ( choose["Flag_globalTightHalo2016Filter"] )
      input->select("Events/Flag_globalTightHalo2016Filter",
                     Flag_globalTightHalo2016Filter);
    if ( choose["Flag_goodVertices"] )
      input->select("Events/Flag_goodVertices", 	Flag_goodVertices);
    if ( choose["Flag_hcalLaserEventFilter"] )
      input->select("Events/Flag_hcalLaserEventFilter",
                     Flag_hcalLaserEventFilter);
    if ( choose["Flag_hfNoisyHitsFilter"] )
      input->select("Events/Flag_hfNoisyHitsFilter",
                     Flag_hfNoisyHitsFilter);
    if ( choose["Flag_muonBadTrackFilter"] )
      input->select("Events/Flag_muonBadTrackFilter",
                     Flag_muonBadTrackFilter);
    if ( choose["Flag_trkPOGFilters"] )
      input->select("Events/Flag_trkPOGFilters", 	Flag_trkPOGFilters);
    if ( choose["Flag_trkPOG_logErrorTooManyClusters"] )
      input->select("Events/Flag_trkPOG_logErrorTooManyClusters",
                     Flag_trkPOG_logErrorTooManyClusters);
    if ( choose["Flag_trkPOG_manystripclus53X"] )
      input->select("Events/Flag_trkPOG_manystripclus53X",
                     Flag_trkPOG_manystripclus53X);
    if ( choose["Flag_trkPOG_toomanystripclus53X"] )
      input->select("Events/Flag_trkPOG_toomanystripclus53X",
                     Flag_trkPOG_toomanystripclus53X);
    if ( choose["FsrPhoton_dROverEt2"] )
      input->select("Events/FsrPhoton_dROverEt2", 	FsrPhoton_dROverEt2);
    if ( choose["FsrPhoton_eta"] )
      input->select("Events/FsrPhoton_eta", 	FsrPhoton_eta);
    if ( choose["FsrPhoton_muonIdx"] )
      input->select("Events/FsrPhoton_muonIdx", 	FsrPhoton_muonIdx);
    if ( choose["FsrPhoton_phi"] )
      input->select("Events/FsrPhoton_phi", 	FsrPhoton_phi);
    if ( choose["FsrPhoton_pt"] )
      input->select("Events/FsrPhoton_pt", 	FsrPhoton_pt);
    if ( choose["FsrPhoton_relIso03"] )
      input->select("Events/FsrPhoton_relIso03", 	FsrPhoton_relIso03);
    if ( choose["GenIsolatedPhoton_eta"] )
      input->select("Events/GenIsolatedPhoton_eta", 	GenIsolatedPhoton_eta);
    if ( choose["GenIsolatedPhoton_mass"] )
      input->select("Events/GenIsolatedPhoton_mass",
                     GenIsolatedPhoton_mass);
    if ( choose["GenIsolatedPhoton_phi"] )
      input->select("Events/GenIsolatedPhoton_phi", 	GenIsolatedPhoton_phi);
    if ( choose["GenIsolatedPhoton_pt"] )
      input->select("Events/GenIsolatedPhoton_pt", 	GenIsolatedPhoton_pt);
    if ( choose["GenJetAK8_eta"] )
      input->select("Events/GenJetAK8_eta", 	GenJetAK8_eta);
    if ( choose["GenJetAK8_hadronFlavour"] )
      input->select("Events/GenJetAK8_hadronFlavour",
                     GenJetAK8_hadronFlavour);
    if ( choose["GenJetAK8_mass"] )
      input->select("Events/GenJetAK8_mass", 	GenJetAK8_mass);
    if ( choose["GenJetAK8_partonFlavour"] )
      input->select("Events/GenJetAK8_partonFlavour",
                     GenJetAK8_partonFlavour);
    if ( choose["GenJetAK8_phi"] )
      input->select("Events/GenJetAK8_phi", 	GenJetAK8_phi);
    if ( choose["GenJetAK8_pt"] )
      input->select("Events/GenJetAK8_pt", 	GenJetAK8_pt);
    if ( choose["GenJet_eta"] )
      input->select("Events/GenJet_eta", 	GenJet_eta);
    if ( choose["GenJet_hadronFlavour"] )
      input->select("Events/GenJet_hadronFlavour", 	GenJet_hadronFlavour);
    if ( choose["GenJet_mass"] )
      input->select("Events/GenJet_mass", 	GenJet_mass);
    if ( choose["GenJet_partonFlavour"] )
      input->select("Events/GenJet_partonFlavour", 	GenJet_partonFlavour);
    if ( choose["GenJet_phi"] )
      input->select("Events/GenJet_phi", 	GenJet_phi);
    if ( choose["GenJet_pt"] )
      input->select("Events/GenJet_pt", 	GenJet_pt);
    if ( choose["GenMET_phi"] )
      input->select("Events/GenMET_phi", 	GenMET_phi);
    if ( choose["GenMET_pt"] )
      input->select("Events/GenMET_pt", 	GenMET_pt);
    if ( choose["GenPart_eta"] )
      input->select("Events/GenPart_eta", 	GenPart_eta);
    if ( choose["GenPart_genPartIdxMother"] )
      input->select("Events/GenPart_genPartIdxMother",
                     GenPart_genPartIdxMother);
    if ( choose["GenPart_mass"] )
      input->select("Events/GenPart_mass", 	GenPart_mass);
    if ( choose["GenPart_pdgId"] )
      input->select("Events/GenPart_pdgId", 	GenPart_pdgId);
    if ( choose["GenPart_phi"] )
      input->select("Events/GenPart_phi", 	GenPart_phi);
    if ( choose["GenPart_pt"] )
      input->select("Events/GenPart_pt", 	GenPart_pt);
    if ( choose["GenPart_status"] )
      input->select("Events/GenPart_status", 	GenPart_status);
    if ( choose["GenPart_statusFlags"] )
      input->select("Events/GenPart_statusFlags", 	GenPart_statusFlags);
    if ( choose["GenVtx_t0"] )
      input->select("Events/GenVtx_t0", 	GenVtx_t0);
    if ( choose["GenVtx_x"] )
      input->select("Events/GenVtx_x", 	GenVtx_x);
    if ( choose["GenVtx_y"] )
      input->select("Events/GenVtx_y", 	GenVtx_y);
    if ( choose["GenVtx_z"] )
      input->select("Events/GenVtx_z", 	GenVtx_z);
    if ( choose["Generator_binvar"] )
      input->select("Events/Generator_binvar", 	Generator_binvar);
    if ( choose["Generator_id1"] )
      input->select("Events/Generator_id1", 	Generator_id1);
    if ( choose["Generator_id2"] )
      input->select("Events/Generator_id2", 	Generator_id2);
    if ( choose["Generator_scalePDF"] )
      input->select("Events/Generator_scalePDF", 	Generator_scalePDF);
    if ( choose["Generator_weight"] )
      input->select("Events/Generator_weight", 	Generator_weight);
    if ( choose["Generator_x1"] )
      input->select("Events/Generator_x1", 	Generator_x1);
    if ( choose["Generator_x2"] )
      input->select("Events/Generator_x2", 	Generator_x2);
    if ( choose["Generator_xpdf1"] )
      input->select("Events/Generator_xpdf1", 	Generator_xpdf1);
    if ( choose["Generator_xpdf2"] )
      input->select("Events/Generator_xpdf2", 	Generator_xpdf2);
		if ( choose["HLT_PFHT300_PFMET110"] )
			input->select("Events/HLT_PFHT300_PFMET110", 	HLT_PFHT300_PFMET110);
		if ( choose["HLT_PFHT125"] )
			input->select("Events/HLT_PFHT125", 	HLT_PFHT125);
		if ( choose["HLT_PFHT200"] )
			input->select("Events/HLT_PFHT200", 	HLT_PFHT200);
		if ( choose["HLT_PFHT300"] )
			input->select("Events/HLT_PFHT300", 	HLT_PFHT300);
		if ( choose["HLT_PFHT400"] )
			input->select("Events/HLT_PFHT400", 	HLT_PFHT400);
		if ( choose["HLT_PFHT475"] )
			input->select("Events/HLT_PFHT475", 	HLT_PFHT475);
		if ( choose["HLT_PFHT650"] )
			input->select("Events/HLT_PFHT650", 	HLT_PFHT650);
		if ( choose["HLT_PFHT800"] )
			input->select("Events/HLT_PFHT800", 	HLT_PFHT800);
		if ( choose["HLT_PFHT900"] )
			input->select("Events/HLT_PFHT900", 	HLT_PFHT900);
		if ( choose["HLT_Ele15_IsoVVVL_PFHT350"] )
			input->select("Events/HLT_Ele15_IsoVVVL_PFHT350",
					HLT_Ele15_IsoVVVL_PFHT350);
		if ( choose["HLT_Ele105_CaloIdVT_GsfTrkIdT"] )
			input->select("Events/HLT_Ele105_CaloIdVT_GsfTrkIdT",
					HLT_Ele105_CaloIdVT_GsfTrkIdT);
		if ( choose["HLT_Mu15_IsoVVVL_PFHT350"] )
			input->select("Events/HLT_Mu15_IsoVVVL_PFHT350",
					HLT_Mu15_IsoVVVL_PFHT350);
		if ( choose["HLT_IsoTkMu24"] )
			input->select("Events/HLT_IsoTkMu24", 	HLT_IsoTkMu24);
		if ( choose["HLT_TkMu50"] )
			input->select("Events/HLT_TkMu50", 	HLT_TkMu50);
		if ( choose["HLT_Mu15_IsoVVVL_PFHT400"] )
			input->select("Events/HLT_Mu15_IsoVVVL_PFHT400",
					HLT_Mu15_IsoVVVL_PFHT400);
		if ( choose["HLT_IsoTkMu27"] )
			input->select("Events/HLT_IsoTkMu27", 	HLT_IsoTkMu27);
		if ( choose["HLT_Ele15_IsoVVVL_PFHT400"] )
			input->select("Events/HLT_Ele15_IsoVVVL_PFHT400",
					HLT_Ele15_IsoVVVL_PFHT400);
		if ( choose["HLT_Photon22"] )
			input->select("Events/HLT_Photon22", 	HLT_Photon22);
		if ( choose["HLT_Photon30"] )
			input->select("Events/HLT_Photon30", 	HLT_Photon30);
		if ( choose["HLT_Photon36"] )
			input->select("Events/HLT_Photon36", 	HLT_Photon36);
		if ( choose["HLT_Photon125"] )
			input->select("Events/HLT_Photon125", 	HLT_Photon125);
		if ( choose["HLT_Photon165_HE10"] )
			input->select("Events/HLT_Photon165_HE10", 	HLT_Photon165_HE10);
		if ( choose["HLT_Photon250_NoHE"] )
    if ( choose["HLT_AK4CaloJet100"] )
      input->select("Events/HLT_AK4CaloJet100", 	HLT_AK4CaloJet100);
    if ( choose["HLT_AK4CaloJet120"] )
      input->select("Events/HLT_AK4CaloJet120", 	HLT_AK4CaloJet120);
    if ( choose["HLT_AK4CaloJet30"] )
      input->select("Events/HLT_AK4CaloJet30", 	HLT_AK4CaloJet30);
    if ( choose["HLT_AK4CaloJet40"] )
      input->select("Events/HLT_AK4CaloJet40", 	HLT_AK4CaloJet40);
    if ( choose["HLT_AK4CaloJet50"] )
      input->select("Events/HLT_AK4CaloJet50", 	HLT_AK4CaloJet50);
    if ( choose["HLT_AK4CaloJet80"] )
      input->select("Events/HLT_AK4CaloJet80", 	HLT_AK4CaloJet80);
    if ( choose["HLT_AK4PFJet100"] )
      input->select("Events/HLT_AK4PFJet100", 	HLT_AK4PFJet100);
    if ( choose["HLT_AK4PFJet120"] )
      input->select("Events/HLT_AK4PFJet120", 	HLT_AK4PFJet120);
    if ( choose["HLT_AK4PFJet30"] )
      input->select("Events/HLT_AK4PFJet30", 	HLT_AK4PFJet30);
    if ( choose["HLT_AK4PFJet50"] )
      input->select("Events/HLT_AK4PFJet50", 	HLT_AK4PFJet50);
    if ( choose["HLT_AK4PFJet80"] )
      input->select("Events/HLT_AK4PFJet80", 	HLT_AK4PFJet80);
    if ( choose["HLT_AK8PFHT750_TrimMass50"] )
      input->select("Events/HLT_AK8PFHT750_TrimMass50",
                     HLT_AK8PFHT750_TrimMass50);
    if ( choose["HLT_AK8PFHT800_TrimMass50"] )
      input->select("Events/HLT_AK8PFHT800_TrimMass50",
                     HLT_AK8PFHT800_TrimMass50);
    if ( choose["HLT_AK8PFHT850_TrimMass50"] )
      input->select("Events/HLT_AK8PFHT850_TrimMass50",
                     HLT_AK8PFHT850_TrimMass50);
    if ( choose["HLT_AK8PFHT900_TrimMass50"] )
      input->select("Events/HLT_AK8PFHT900_TrimMass50",
                     HLT_AK8PFHT900_TrimMass50);
    if ( choose["HLT_AK8PFJet140"] )
      input->select("Events/HLT_AK8PFJet140", 	HLT_AK8PFJet140);
    if ( choose["HLT_AK8PFJet15"] )
      input->select("Events/HLT_AK8PFJet15", 	HLT_AK8PFJet15);
    if ( choose["HLT_AK8PFJet200"] )
      input->select("Events/HLT_AK8PFJet200", 	HLT_AK8PFJet200);
    if ( choose["HLT_AK8PFJet25"] )
      input->select("Events/HLT_AK8PFJet25", 	HLT_AK8PFJet25);
    if ( choose["HLT_AK8PFJet260"] )
      input->select("Events/HLT_AK8PFJet260", 	HLT_AK8PFJet260);
    if ( choose["HLT_AK8PFJet320"] )
      input->select("Events/HLT_AK8PFJet320", 	HLT_AK8PFJet320);
    if ( choose["HLT_AK8PFJet330_TrimMass30_PFAK8BTagDeepCSV_p1"] )
      input->select("Events/HLT_AK8PFJet330_TrimMass30_PFAK8BTagDeepCSV_p1",
                     HLT_AK8PFJet330_TrimMass30_PFAK8BTagDeepCSV_p1);
    if ( choose["HLT_AK8PFJet330_TrimMass30_PFAK8BTagDeepCSV_p17"] )
      input->select("Events/HLT_AK8PFJet330_TrimMass30_PFAK8BTagDeepCSV_p17",
                     HLT_AK8PFJet330_TrimMass30_PFAK8BTagDeepCSV_p17);
    if ( choose["HLT_AK8PFJet330_TrimMass30_PFAK8BoostedDoubleB_np2"] )
      input->select("Events/HLT_AK8PFJet330_TrimMass30_PFAK8BoostedDoubleB_np2",
                     HLT_AK8PFJet330_TrimMass30_PFAK8BoostedDoubleB_np2);
    if ( choose["HLT_AK8PFJet330_TrimMass30_PFAK8BoostedDoubleB_np4"] )
      input->select("Events/HLT_AK8PFJet330_TrimMass30_PFAK8BoostedDoubleB_np4",
                     HLT_AK8PFJet330_TrimMass30_PFAK8BoostedDoubleB_np4);
    if ( choose["HLT_AK8PFJet330_TrimMass30_PFAK8BoostedDoubleB_p02"] )
      input->select("Events/HLT_AK8PFJet330_TrimMass30_PFAK8BoostedDoubleB_p02",
                     HLT_AK8PFJet330_TrimMass30_PFAK8BoostedDoubleB_p02);
    if ( choose["HLT_AK8PFJet360_TrimMass30"] )
      input->select("Events/HLT_AK8PFJet360_TrimMass30",
                     HLT_AK8PFJet360_TrimMass30);
    if ( choose["HLT_AK8PFJet380_TrimMass30"] )
      input->select("Events/HLT_AK8PFJet380_TrimMass30",
                     HLT_AK8PFJet380_TrimMass30);
    if ( choose["HLT_AK8PFJet40"] )
      input->select("Events/HLT_AK8PFJet40", 	HLT_AK8PFJet40);
    if ( choose["HLT_AK8PFJet400"] )
      input->select("Events/HLT_AK8PFJet400", 	HLT_AK8PFJet400);
    if ( choose["HLT_AK8PFJet400_TrimMass30"] )
      input->select("Events/HLT_AK8PFJet400_TrimMass30",
                     HLT_AK8PFJet400_TrimMass30);
    if ( choose["HLT_AK8PFJet420_TrimMass30"] )
      input->select("Events/HLT_AK8PFJet420_TrimMass30",
                     HLT_AK8PFJet420_TrimMass30);
    if ( choose["HLT_AK8PFJet450"] )
      input->select("Events/HLT_AK8PFJet450", 	HLT_AK8PFJet450);
    if ( choose["HLT_AK8PFJet500"] )
      input->select("Events/HLT_AK8PFJet500", 	HLT_AK8PFJet500);
    if ( choose["HLT_AK8PFJet550"] )
      input->select("Events/HLT_AK8PFJet550", 	HLT_AK8PFJet550);
    if ( choose["HLT_AK8PFJet60"] )
      input->select("Events/HLT_AK8PFJet60", 	HLT_AK8PFJet60);
    if ( choose["HLT_AK8PFJet80"] )
      input->select("Events/HLT_AK8PFJet80", 	HLT_AK8PFJet80);
    if ( choose["HLT_AK8PFJetFwd140"] )
      input->select("Events/HLT_AK8PFJetFwd140", 	HLT_AK8PFJetFwd140);
    if ( choose["HLT_AK8PFJetFwd15"] )
      input->select("Events/HLT_AK8PFJetFwd15", 	HLT_AK8PFJetFwd15);
    if ( choose["HLT_AK8PFJetFwd200"] )
      input->select("Events/HLT_AK8PFJetFwd200", 	HLT_AK8PFJetFwd200);
    if ( choose["HLT_AK8PFJetFwd25"] )
      input->select("Events/HLT_AK8PFJetFwd25", 	HLT_AK8PFJetFwd25);
    if ( choose["HLT_AK8PFJetFwd260"] )
      input->select("Events/HLT_AK8PFJetFwd260", 	HLT_AK8PFJetFwd260);
    if ( choose["HLT_AK8PFJetFwd320"] )
      input->select("Events/HLT_AK8PFJetFwd320", 	HLT_AK8PFJetFwd320);
    if ( choose["HLT_AK8PFJetFwd40"] )
      input->select("Events/HLT_AK8PFJetFwd40", 	HLT_AK8PFJetFwd40);
    if ( choose["HLT_AK8PFJetFwd400"] )
      input->select("Events/HLT_AK8PFJetFwd400", 	HLT_AK8PFJetFwd400);
    if ( choose["HLT_AK8PFJetFwd450"] )
      input->select("Events/HLT_AK8PFJetFwd450", 	HLT_AK8PFJetFwd450);
    if ( choose["HLT_AK8PFJetFwd500"] )
      input->select("Events/HLT_AK8PFJetFwd500", 	HLT_AK8PFJetFwd500);
    if ( choose["HLT_AK8PFJetFwd60"] )
      input->select("Events/HLT_AK8PFJetFwd60", 	HLT_AK8PFJetFwd60);
    if ( choose["HLT_AK8PFJetFwd80"] )
      input->select("Events/HLT_AK8PFJetFwd80", 	HLT_AK8PFJetFwd80);
    if ( choose["HLT_Ele115_CaloIdVT_GsfTrkIdT"] )
      input->select("Events/HLT_Ele115_CaloIdVT_GsfTrkIdT",
                     HLT_Ele115_CaloIdVT_GsfTrkIdT);
    if ( choose["HLT_Ele12_CaloIdL_TrackIdL_IsoVL_PFJet30"] )
      input->select("Events/HLT_Ele12_CaloIdL_TrackIdL_IsoVL_PFJet30",
                     HLT_Ele12_CaloIdL_TrackIdL_IsoVL_PFJet30);
    if ( choose["HLT_Ele135_CaloIdVT_GsfTrkIdT"] )
      input->select("Events/HLT_Ele135_CaloIdVT_GsfTrkIdT",
                     HLT_Ele135_CaloIdVT_GsfTrkIdT);
    if ( choose["HLT_Ele145_CaloIdVT_GsfTrkIdT"] )
      input->select("Events/HLT_Ele145_CaloIdVT_GsfTrkIdT",
                     HLT_Ele145_CaloIdVT_GsfTrkIdT);
    if ( choose["HLT_Ele15_CaloIdL_TrackIdL_IsoVL_PFJet30"] )
      input->select("Events/HLT_Ele15_CaloIdL_TrackIdL_IsoVL_PFJet30",
                     HLT_Ele15_CaloIdL_TrackIdL_IsoVL_PFJet30);
    if ( choose["HLT_Ele15_Ele8_CaloIdL_TrackIdL_IsoVL"] )
      input->select("Events/HLT_Ele15_Ele8_CaloIdL_TrackIdL_IsoVL",
                     HLT_Ele15_Ele8_CaloIdL_TrackIdL_IsoVL);
    if ( choose["HLT_Ele15_IsoVVVL_PFHT450"] )
      input->select("Events/HLT_Ele15_IsoVVVL_PFHT450",
                     HLT_Ele15_IsoVVVL_PFHT450);
    if ( choose["HLT_Ele15_IsoVVVL_PFHT450_CaloBTagDeepCSV_4p5"] )
      input->select("Events/HLT_Ele15_IsoVVVL_PFHT450_CaloBTagDeepCSV_4p5",
                     HLT_Ele15_IsoVVVL_PFHT450_CaloBTagDeepCSV_4p5);
    if ( choose["HLT_Ele15_IsoVVVL_PFHT450_PFMET50"] )
      input->select("Events/HLT_Ele15_IsoVVVL_PFHT450_PFMET50",
                     HLT_Ele15_IsoVVVL_PFHT450_PFMET50);
    if ( choose["HLT_Ele15_IsoVVVL_PFHT600"] )
      input->select("Events/HLT_Ele15_IsoVVVL_PFHT600",
                     HLT_Ele15_IsoVVVL_PFHT600);
    if ( choose["HLT_Ele15_WPLoose_Gsf"] )
      input->select("Events/HLT_Ele15_WPLoose_Gsf", 	HLT_Ele15_WPLoose_Gsf);
    if ( choose["HLT_Ele16_Ele12_Ele8_CaloIdL_TrackIdL"] )
      input->select("Events/HLT_Ele16_Ele12_Ele8_CaloIdL_TrackIdL",
                     HLT_Ele16_Ele12_Ele8_CaloIdL_TrackIdL);
    if ( choose["HLT_Ele17_CaloIdM_TrackIdM_PFJet30"] )
      input->select("Events/HLT_Ele17_CaloIdM_TrackIdM_PFJet30",
                     HLT_Ele17_CaloIdM_TrackIdM_PFJet30);
    if ( choose["HLT_Ele17_WPLoose_Gsf"] )
      input->select("Events/HLT_Ele17_WPLoose_Gsf", 	HLT_Ele17_WPLoose_Gsf);
    if ( choose["HLT_Ele200_CaloIdVT_GsfTrkIdT"] )
      input->select("Events/HLT_Ele200_CaloIdVT_GsfTrkIdT",
                     HLT_Ele200_CaloIdVT_GsfTrkIdT);
    if ( choose["HLT_Ele20_WPLoose_Gsf"] )
      input->select("Events/HLT_Ele20_WPLoose_Gsf", 	HLT_Ele20_WPLoose_Gsf);
    if ( choose["HLT_Ele20_WPTight_Gsf"] )
      input->select("Events/HLT_Ele20_WPTight_Gsf", 	HLT_Ele20_WPTight_Gsf);
    if ( choose["HLT_Ele20_eta2p1_WPLoose_Gsf"] )
      input->select("Events/HLT_Ele20_eta2p1_WPLoose_Gsf",
                     HLT_Ele20_eta2p1_WPLoose_Gsf);
    if ( choose["HLT_Ele23_CaloIdL_TrackIdL_IsoVL_PFJet30"] )
      input->select("Events/HLT_Ele23_CaloIdL_TrackIdL_IsoVL_PFJet30",
                     HLT_Ele23_CaloIdL_TrackIdL_IsoVL_PFJet30);
    if ( choose["HLT_Ele23_CaloIdM_TrackIdM_PFJet30"] )
      input->select("Events/HLT_Ele23_CaloIdM_TrackIdM_PFJet30",
                     HLT_Ele23_CaloIdM_TrackIdM_PFJet30);
    if ( choose["HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL"] )
      input->select("Events/HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL",
                     HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL);
    if ( choose["HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ"] )
      input->select("Events/HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ",
                     HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ);
    if ( choose["HLT_Ele24_eta2p1_WPTight_Gsf_LooseChargedIsoPFTauHPS30_eta2p1_CrossL1"] )
      input->select("Events/HLT_Ele24_eta2p1_WPTight_Gsf_LooseChargedIsoPFTauHPS30_eta2p1_CrossL1",
                     HLT_Ele24_eta2p1_WPTight_Gsf_LooseChargedIsoPFTauHPS30_eta2p1_CrossL1);
    if ( choose["HLT_Ele24_eta2p1_WPTight_Gsf_LooseChargedIsoPFTauHPS30_eta2p1_TightID_CrossL1"] )
      input->select("Events/HLT_Ele24_eta2p1_WPTight_Gsf_LooseChargedIsoPFTauHPS30_eta2p1_TightID_CrossL1",
                     HLT_Ele24_eta2p1_WPTight_Gsf_LooseChargedIsoPFTauHPS30_eta2p1_TightID_CrossL1);
    if ( choose["HLT_Ele24_eta2p1_WPTight_Gsf_MediumChargedIsoPFTauHPS30_eta2p1_CrossL1"] )
      input->select("Events/HLT_Ele24_eta2p1_WPTight_Gsf_MediumChargedIsoPFTauHPS30_eta2p1_CrossL1",
                     HLT_Ele24_eta2p1_WPTight_Gsf_MediumChargedIsoPFTauHPS30_eta2p1_CrossL1);
    if ( choose["HLT_Ele24_eta2p1_WPTight_Gsf_MediumChargedIsoPFTauHPS30_eta2p1_TightID_CrossL1"] )
      input->select("Events/HLT_Ele24_eta2p1_WPTight_Gsf_MediumChargedIsoPFTauHPS30_eta2p1_TightID_CrossL1",
                     HLT_Ele24_eta2p1_WPTight_Gsf_MediumChargedIsoPFTauHPS30_eta2p1_TightID_CrossL1);
    if ( choose["HLT_Ele24_eta2p1_WPTight_Gsf_TightChargedIsoPFTauHPS30_eta2p1_CrossL1"] )
      input->select("Events/HLT_Ele24_eta2p1_WPTight_Gsf_TightChargedIsoPFTauHPS30_eta2p1_CrossL1",
                     HLT_Ele24_eta2p1_WPTight_Gsf_TightChargedIsoPFTauHPS30_eta2p1_CrossL1);
    if ( choose["HLT_Ele24_eta2p1_WPTight_Gsf_TightChargedIsoPFTauHPS30_eta2p1_TightID_CrossL1"] )
      input->select("Events/HLT_Ele24_eta2p1_WPTight_Gsf_TightChargedIsoPFTauHPS30_eta2p1_TightID_CrossL1",
                     HLT_Ele24_eta2p1_WPTight_Gsf_TightChargedIsoPFTauHPS30_eta2p1_TightID_CrossL1);
    if ( choose["HLT_Ele250_CaloIdVT_GsfTrkIdT"] )
      input->select("Events/HLT_Ele250_CaloIdVT_GsfTrkIdT",
                     HLT_Ele250_CaloIdVT_GsfTrkIdT);
    if ( choose["HLT_Ele27_Ele37_CaloIdL_MW"] )
      input->select("Events/HLT_Ele27_Ele37_CaloIdL_MW",
                     HLT_Ele27_Ele37_CaloIdL_MW);
    if ( choose["HLT_Ele27_WPTight_Gsf"] )
      input->select("Events/HLT_Ele27_WPTight_Gsf", 	HLT_Ele27_WPTight_Gsf);
    if ( choose["HLT_Ele28_HighEta_SC20_Mass55"] )
      input->select("Events/HLT_Ele28_HighEta_SC20_Mass55",
                     HLT_Ele28_HighEta_SC20_Mass55);
    if ( choose["HLT_Ele28_WPTight_Gsf"] )
      input->select("Events/HLT_Ele28_WPTight_Gsf", 	HLT_Ele28_WPTight_Gsf);
    if ( choose["HLT_Ele28_eta2p1_WPTight_Gsf_HT150"] )
      input->select("Events/HLT_Ele28_eta2p1_WPTight_Gsf_HT150",
                     HLT_Ele28_eta2p1_WPTight_Gsf_HT150);
    if ( choose["HLT_Ele300_CaloIdVT_GsfTrkIdT"] )
      input->select("Events/HLT_Ele300_CaloIdVT_GsfTrkIdT",
                     HLT_Ele300_CaloIdVT_GsfTrkIdT);
    if ( choose["HLT_Ele30_WPTight_Gsf"] )
      input->select("Events/HLT_Ele30_WPTight_Gsf", 	HLT_Ele30_WPTight_Gsf);
    if ( choose["HLT_Ele30_eta2p1_WPTight_Gsf_CentralPFJet35_EleCleaned"] )
      input->select("Events/HLT_Ele30_eta2p1_WPTight_Gsf_CentralPFJet35_EleCleaned",
                     HLT_Ele30_eta2p1_WPTight_Gsf_CentralPFJet35_EleCleaned);
    if ( choose["HLT_Ele32_WPTight_Gsf"] )
      input->select("Events/HLT_Ele32_WPTight_Gsf", 	HLT_Ele32_WPTight_Gsf);
    if ( choose["HLT_Ele32_WPTight_Gsf_L1DoubleEG"] )
      input->select("Events/HLT_Ele32_WPTight_Gsf_L1DoubleEG",
                     HLT_Ele32_WPTight_Gsf_L1DoubleEG);
    if ( choose["HLT_Ele35_WPTight_Gsf"] )
      input->select("Events/HLT_Ele35_WPTight_Gsf", 	HLT_Ele35_WPTight_Gsf);
    if ( choose["HLT_Ele35_WPTight_Gsf_L1EGMT"] )
      input->select("Events/HLT_Ele35_WPTight_Gsf_L1EGMT",
                     HLT_Ele35_WPTight_Gsf_L1EGMT);
    if ( choose["HLT_Ele38_WPTight_Gsf"] )
      input->select("Events/HLT_Ele38_WPTight_Gsf", 	HLT_Ele38_WPTight_Gsf);
    if ( choose["HLT_Ele40_WPTight_Gsf"] )
      input->select("Events/HLT_Ele40_WPTight_Gsf", 	HLT_Ele40_WPTight_Gsf);
    if ( choose["HLT_Ele50_CaloIdVT_GsfTrkIdT_PFJet165"] )
      input->select("Events/HLT_Ele50_CaloIdVT_GsfTrkIdT_PFJet165",
                     HLT_Ele50_CaloIdVT_GsfTrkIdT_PFJet165);
    if ( choose["HLT_Ele50_IsoVVVL_PFHT450"] )
      input->select("Events/HLT_Ele50_IsoVVVL_PFHT450",
                     HLT_Ele50_IsoVVVL_PFHT450);
    if ( choose["HLT_Ele8_CaloIdL_TrackIdL_IsoVL_PFJet30"] )
      input->select("Events/HLT_Ele8_CaloIdL_TrackIdL_IsoVL_PFJet30",
                     HLT_Ele8_CaloIdL_TrackIdL_IsoVL_PFJet30);
    if ( choose["HLT_Ele8_CaloIdM_TrackIdM_PFJet30"] )
      input->select("Events/HLT_Ele8_CaloIdM_TrackIdM_PFJet30",
                     HLT_Ele8_CaloIdM_TrackIdM_PFJet30);
    if ( choose["HLT_HT300_Beamspot"] )
      input->select("Events/HLT_HT300_Beamspot", 	HLT_HT300_Beamspot);
    if ( choose["HLT_HT400_DisplacedDijet40_DisplacedTrack"] )
      input->select("Events/HLT_HT400_DisplacedDijet40_DisplacedTrack",
                     HLT_HT400_DisplacedDijet40_DisplacedTrack);
    if ( choose["HLT_HT425"] )
      input->select("Events/HLT_HT425", 	HLT_HT425);
    if ( choose["HLT_HT430_DisplacedDijet40_DisplacedTrack"] )
      input->select("Events/HLT_HT430_DisplacedDijet40_DisplacedTrack",
                     HLT_HT430_DisplacedDijet40_DisplacedTrack);
    if ( choose["HLT_HT430_DisplacedDijet60_DisplacedTrack"] )
      input->select("Events/HLT_HT430_DisplacedDijet60_DisplacedTrack",
                     HLT_HT430_DisplacedDijet60_DisplacedTrack);
    if ( choose["HLT_HT450_Beamspot"] )
      input->select("Events/HLT_HT450_Beamspot", 	HLT_HT450_Beamspot);
    if ( choose["HLT_HT500_DisplacedDijet40_DisplacedTrack"] )
      input->select("Events/HLT_HT500_DisplacedDijet40_DisplacedTrack",
                     HLT_HT500_DisplacedDijet40_DisplacedTrack);
    if ( choose["HLT_HT550_DisplacedDijet60_Inclusive"] )
      input->select("Events/HLT_HT550_DisplacedDijet60_Inclusive",
                     HLT_HT550_DisplacedDijet60_Inclusive);
    if ( choose["HLT_HT650_DisplacedDijet60_Inclusive"] )
      input->select("Events/HLT_HT650_DisplacedDijet60_Inclusive",
                     HLT_HT650_DisplacedDijet60_Inclusive);
    if ( choose["HLT_IsoMu20"] )
      input->select("Events/HLT_IsoMu20", 	HLT_IsoMu20);
    if ( choose["HLT_IsoMu20_eta2p1_LooseChargedIsoPFTauHPS27_eta2p1_CrossL1"] )
      input->select("Events/HLT_IsoMu20_eta2p1_LooseChargedIsoPFTauHPS27_eta2p1_CrossL1",
                     HLT_IsoMu20_eta2p1_LooseChargedIsoPFTauHPS27_eta2p1_CrossL1);
    if ( choose["HLT_IsoMu20_eta2p1_LooseChargedIsoPFTauHPS27_eta2p1_TightID_CrossL1"] )
      input->select("Events/HLT_IsoMu20_eta2p1_LooseChargedIsoPFTauHPS27_eta2p1_TightID_CrossL1",
                     HLT_IsoMu20_eta2p1_LooseChargedIsoPFTauHPS27_eta2p1_TightID_CrossL1);
    if ( choose["HLT_IsoMu20_eta2p1_MediumChargedIsoPFTauHPS27_eta2p1_CrossL1"] )
      input->select("Events/HLT_IsoMu20_eta2p1_MediumChargedIsoPFTauHPS27_eta2p1_CrossL1",
                     HLT_IsoMu20_eta2p1_MediumChargedIsoPFTauHPS27_eta2p1_CrossL1);
    if ( choose["HLT_IsoMu20_eta2p1_MediumChargedIsoPFTauHPS27_eta2p1_TightID_CrossL1"] )
      input->select("Events/HLT_IsoMu20_eta2p1_MediumChargedIsoPFTauHPS27_eta2p1_TightID_CrossL1",
                     HLT_IsoMu20_eta2p1_MediumChargedIsoPFTauHPS27_eta2p1_TightID_CrossL1);
    if ( choose["HLT_IsoMu20_eta2p1_TightChargedIsoPFTauHPS27_eta2p1_CrossL1"] )
      input->select("Events/HLT_IsoMu20_eta2p1_TightChargedIsoPFTauHPS27_eta2p1_CrossL1",
                     HLT_IsoMu20_eta2p1_TightChargedIsoPFTauHPS27_eta2p1_CrossL1);
    if ( choose["HLT_IsoMu20_eta2p1_TightChargedIsoPFTauHPS27_eta2p1_TightID_CrossL1"] )
      input->select("Events/HLT_IsoMu20_eta2p1_TightChargedIsoPFTauHPS27_eta2p1_TightID_CrossL1",
                     HLT_IsoMu20_eta2p1_TightChargedIsoPFTauHPS27_eta2p1_TightID_CrossL1);
    if ( choose["HLT_IsoMu24"] )
      input->select("Events/HLT_IsoMu24", 	HLT_IsoMu24);
    if ( choose["HLT_IsoMu24_TwoProngs35"] )
      input->select("Events/HLT_IsoMu24_TwoProngs35",
                     HLT_IsoMu24_TwoProngs35);
    if ( choose["HLT_IsoMu24_eta2p1"] )
      input->select("Events/HLT_IsoMu24_eta2p1", 	HLT_IsoMu24_eta2p1);
    if ( choose["HLT_IsoMu24_eta2p1_MediumChargedIsoPFTau50_Trk30_eta2p1_1pr"] )
      input->select("Events/HLT_IsoMu24_eta2p1_MediumChargedIsoPFTau50_Trk30_eta2p1_1pr",
                     HLT_IsoMu24_eta2p1_MediumChargedIsoPFTau50_Trk30_eta2p1_1pr);
    if ( choose["HLT_IsoMu24_eta2p1_MediumChargedIsoPFTauHPS35_Trk1_TightID_eta2p1_Reg_CrossL1"] )
      input->select("Events/HLT_IsoMu24_eta2p1_MediumChargedIsoPFTauHPS35_Trk1_TightID_eta2p1_Reg_CrossL1",
                     HLT_IsoMu24_eta2p1_MediumChargedIsoPFTauHPS35_Trk1_TightID_eta2p1_Reg_CrossL1);
    if ( choose["HLT_IsoMu24_eta2p1_MediumChargedIsoPFTauHPS35_Trk1_eta2p1_Reg_CrossL1"] )
      input->select("Events/HLT_IsoMu24_eta2p1_MediumChargedIsoPFTauHPS35_Trk1_eta2p1_Reg_CrossL1",
                     HLT_IsoMu24_eta2p1_MediumChargedIsoPFTauHPS35_Trk1_eta2p1_Reg_CrossL1);
    if ( choose["HLT_IsoMu24_eta2p1_TightChargedIsoPFTauHPS35_Trk1_TightID_eta2p1_Reg_CrossL1"] )
      input->select("Events/HLT_IsoMu24_eta2p1_TightChargedIsoPFTauHPS35_Trk1_TightID_eta2p1_Reg_CrossL1",
                     HLT_IsoMu24_eta2p1_TightChargedIsoPFTauHPS35_Trk1_TightID_eta2p1_Reg_CrossL1);
    if ( choose["HLT_IsoMu24_eta2p1_TightChargedIsoPFTauHPS35_Trk1_eta2p1_Reg_CrossL1"] )
      input->select("Events/HLT_IsoMu24_eta2p1_TightChargedIsoPFTauHPS35_Trk1_eta2p1_Reg_CrossL1",
                     HLT_IsoMu24_eta2p1_TightChargedIsoPFTauHPS35_Trk1_eta2p1_Reg_CrossL1);
    if ( choose["HLT_IsoMu27"] )
      input->select("Events/HLT_IsoMu27", 	HLT_IsoMu27);
    if ( choose["HLT_IsoMu27_LooseChargedIsoPFTauHPS20_Trk1_eta2p1_SingleL1"] )
      input->select("Events/HLT_IsoMu27_LooseChargedIsoPFTauHPS20_Trk1_eta2p1_SingleL1",
                     HLT_IsoMu27_LooseChargedIsoPFTauHPS20_Trk1_eta2p1_SingleL1);
    if ( choose["HLT_IsoMu27_MET90"] )
      input->select("Events/HLT_IsoMu27_MET90", 	HLT_IsoMu27_MET90);
    if ( choose["HLT_IsoMu27_MediumChargedIsoPFTauHPS20_Trk1_eta2p1_SingleL1"] )
      input->select("Events/HLT_IsoMu27_MediumChargedIsoPFTauHPS20_Trk1_eta2p1_SingleL1",
                     HLT_IsoMu27_MediumChargedIsoPFTauHPS20_Trk1_eta2p1_SingleL1);
    if ( choose["HLT_IsoMu27_TightChargedIsoPFTauHPS20_Trk1_eta2p1_SingleL1"] )
      input->select("Events/HLT_IsoMu27_TightChargedIsoPFTauHPS20_Trk1_eta2p1_SingleL1",
                     HLT_IsoMu27_TightChargedIsoPFTauHPS20_Trk1_eta2p1_SingleL1);
    if ( choose["HLT_IsoMu30"] )
      input->select("Events/HLT_IsoMu30", 	HLT_IsoMu30);
    if ( choose["HLT_IsoTrackHB"] )
      input->select("Events/HLT_IsoTrackHB", 	HLT_IsoTrackHB);
    if ( choose["HLT_IsoTrackHE"] )
      input->select("Events/HLT_IsoTrackHE", 	HLT_IsoTrackHE);
    if ( choose["HLT_MET105_IsoTrk50"] )
      input->select("Events/HLT_MET105_IsoTrk50", 	HLT_MET105_IsoTrk50);
    if ( choose["HLT_MET120_IsoTrk50"] )
      input->select("Events/HLT_MET120_IsoTrk50", 	HLT_MET120_IsoTrk50);
    if ( choose["HLT_Mu10_TrkIsoVVL_DiPFJet40_DEta3p5_MJJ750_HTT350_PFMETNoMu60"] )
      input->select("Events/HLT_Mu10_TrkIsoVVL_DiPFJet40_DEta3p5_MJJ750_HTT350_PFMETNoMu60",
                     HLT_Mu10_TrkIsoVVL_DiPFJet40_DEta3p5_MJJ750_HTT350_PFMETNoMu60);
    if ( choose["HLT_Mu12"] )
      input->select("Events/HLT_Mu12", 	HLT_Mu12);
    if ( choose["HLT_Mu12_DoublePFJets100_CaloBTagDeepCSV_p71"] )
      input->select("Events/HLT_Mu12_DoublePFJets100_CaloBTagDeepCSV_p71",
                     HLT_Mu12_DoublePFJets100_CaloBTagDeepCSV_p71);
    if ( choose["HLT_Mu12_DoublePFJets200_CaloBTagDeepCSV_p71"] )
      input->select("Events/HLT_Mu12_DoublePFJets200_CaloBTagDeepCSV_p71",
                     HLT_Mu12_DoublePFJets200_CaloBTagDeepCSV_p71);
    if ( choose["HLT_Mu12_DoublePFJets350_CaloBTagDeepCSV_p71"] )
      input->select("Events/HLT_Mu12_DoublePFJets350_CaloBTagDeepCSV_p71",
                     HLT_Mu12_DoublePFJets350_CaloBTagDeepCSV_p71);
    if ( choose["HLT_Mu12_DoublePFJets40MaxDeta1p6_DoubleCaloBTagDeepCSV_p71"] )
      input->select("Events/HLT_Mu12_DoublePFJets40MaxDeta1p6_DoubleCaloBTagDeepCSV_p71",
                     HLT_Mu12_DoublePFJets40MaxDeta1p6_DoubleCaloBTagDeepCSV_p71);
    if ( choose["HLT_Mu12_DoublePFJets40_CaloBTagDeepCSV_p71"] )
      input->select("Events/HLT_Mu12_DoublePFJets40_CaloBTagDeepCSV_p71",
                     HLT_Mu12_DoublePFJets40_CaloBTagDeepCSV_p71);
    if ( choose["HLT_Mu12_DoublePFJets54MaxDeta1p6_DoubleCaloBTagDeepCSV_p71"] )
      input->select("Events/HLT_Mu12_DoublePFJets54MaxDeta1p6_DoubleCaloBTagDeepCSV_p71",
                     HLT_Mu12_DoublePFJets54MaxDeta1p6_DoubleCaloBTagDeepCSV_p71);
    if ( choose["HLT_Mu12_DoublePFJets62MaxDeta1p6_DoubleCaloBTagDeepCSV_p71"] )
      input->select("Events/HLT_Mu12_DoublePFJets62MaxDeta1p6_DoubleCaloBTagDeepCSV_p71",
                     HLT_Mu12_DoublePFJets62MaxDeta1p6_DoubleCaloBTagDeepCSV_p71);
    if ( choose["HLT_Mu12_DoublePhoton20"] )
      input->select("Events/HLT_Mu12_DoublePhoton20",
                     HLT_Mu12_DoublePhoton20);
    if ( choose["HLT_Mu12_IP6_part0"] )
      input->select("Events/HLT_Mu12_IP6_part0", 	HLT_Mu12_IP6_part0);
    if ( choose["HLT_Mu12_IP6_part1"] )
      input->select("Events/HLT_Mu12_IP6_part1", 	HLT_Mu12_IP6_part1);
    if ( choose["HLT_Mu12_IP6_part2"] )
      input->select("Events/HLT_Mu12_IP6_part2", 	HLT_Mu12_IP6_part2);
    if ( choose["HLT_Mu12_IP6_part3"] )
      input->select("Events/HLT_Mu12_IP6_part3", 	HLT_Mu12_IP6_part3);
    if ( choose["HLT_Mu12_IP6_part4"] )
      input->select("Events/HLT_Mu12_IP6_part4", 	HLT_Mu12_IP6_part4);
    if ( choose["HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL"] )
      input->select("Events/HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL",
                     HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL);
    if ( choose["HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ"] )
      input->select("Events/HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ",
                     HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ);
    if ( choose["HLT_Mu15"] )
      input->select("Events/HLT_Mu15", 	HLT_Mu15);
    if ( choose["HLT_Mu15_IsoVVVL_PFHT450"] )
      input->select("Events/HLT_Mu15_IsoVVVL_PFHT450",
                     HLT_Mu15_IsoVVVL_PFHT450);
    if ( choose["HLT_Mu15_IsoVVVL_PFHT450_CaloBTagDeepCSV_4p5"] )
      input->select("Events/HLT_Mu15_IsoVVVL_PFHT450_CaloBTagDeepCSV_4p5",
                     HLT_Mu15_IsoVVVL_PFHT450_CaloBTagDeepCSV_4p5);
    if ( choose["HLT_Mu15_IsoVVVL_PFHT450_PFMET50"] )
      input->select("Events/HLT_Mu15_IsoVVVL_PFHT450_PFMET50",
                     HLT_Mu15_IsoVVVL_PFHT450_PFMET50);
    if ( choose["HLT_Mu15_IsoVVVL_PFHT600"] )
      input->select("Events/HLT_Mu15_IsoVVVL_PFHT600",
                     HLT_Mu15_IsoVVVL_PFHT600);
    if ( choose["HLT_Mu17"] )
      input->select("Events/HLT_Mu17", 	HLT_Mu17);
    if ( choose["HLT_Mu17_Photon30_IsoCaloId"] )
      input->select("Events/HLT_Mu17_Photon30_IsoCaloId",
                     HLT_Mu17_Photon30_IsoCaloId);
    if ( choose["HLT_Mu17_TrkIsoVVL"] )
      input->select("Events/HLT_Mu17_TrkIsoVVL", 	HLT_Mu17_TrkIsoVVL);
    if ( choose["HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL"] )
      input->select("Events/HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL",
                     HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL);
    if ( choose["HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ"] )
      input->select("Events/HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ",
                     HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ);
    if ( choose["HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8"] )
      input->select("Events/HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8",
                     HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8);
    if ( choose["HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass8"] )
      input->select("Events/HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass8",
                     HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass8);
    if ( choose["HLT_Mu18_Mu9"] )
      input->select("Events/HLT_Mu18_Mu9", 	HLT_Mu18_Mu9);
    if ( choose["HLT_Mu18_Mu9_DZ"] )
      input->select("Events/HLT_Mu18_Mu9_DZ", 	HLT_Mu18_Mu9_DZ);
    if ( choose["HLT_Mu18_Mu9_SameSign"] )
      input->select("Events/HLT_Mu18_Mu9_SameSign", 	HLT_Mu18_Mu9_SameSign);
    if ( choose["HLT_Mu18_Mu9_SameSign_DZ"] )
      input->select("Events/HLT_Mu18_Mu9_SameSign_DZ",
                     HLT_Mu18_Mu9_SameSign_DZ);
    if ( choose["HLT_Mu19"] )
      input->select("Events/HLT_Mu19", 	HLT_Mu19);
    if ( choose["HLT_Mu19_TrkIsoVVL"] )
      input->select("Events/HLT_Mu19_TrkIsoVVL", 	HLT_Mu19_TrkIsoVVL);
    if ( choose["HLT_Mu19_TrkIsoVVL_Mu9_TrkIsoVVL"] )
      input->select("Events/HLT_Mu19_TrkIsoVVL_Mu9_TrkIsoVVL",
                     HLT_Mu19_TrkIsoVVL_Mu9_TrkIsoVVL);
    if ( choose["HLT_Mu19_TrkIsoVVL_Mu9_TrkIsoVVL_DZ"] )
      input->select("Events/HLT_Mu19_TrkIsoVVL_Mu9_TrkIsoVVL_DZ",
                     HLT_Mu19_TrkIsoVVL_Mu9_TrkIsoVVL_DZ);
    if ( choose["HLT_Mu19_TrkIsoVVL_Mu9_TrkIsoVVL_DZ_Mass3p8"] )
      input->select("Events/HLT_Mu19_TrkIsoVVL_Mu9_TrkIsoVVL_DZ_Mass3p8",
                     HLT_Mu19_TrkIsoVVL_Mu9_TrkIsoVVL_DZ_Mass3p8);
    if ( choose["HLT_Mu19_TrkIsoVVL_Mu9_TrkIsoVVL_DZ_Mass8"] )
      input->select("Events/HLT_Mu19_TrkIsoVVL_Mu9_TrkIsoVVL_DZ_Mass8",
                     HLT_Mu19_TrkIsoVVL_Mu9_TrkIsoVVL_DZ_Mass8);
    if ( choose["HLT_Mu20"] )
      input->select("Events/HLT_Mu20", 	HLT_Mu20);
    if ( choose["HLT_Mu20_Mu10"] )
      input->select("Events/HLT_Mu20_Mu10", 	HLT_Mu20_Mu10);
    if ( choose["HLT_Mu20_Mu10_DZ"] )
      input->select("Events/HLT_Mu20_Mu10_DZ", 	HLT_Mu20_Mu10_DZ);
    if ( choose["HLT_Mu20_Mu10_SameSign"] )
      input->select("Events/HLT_Mu20_Mu10_SameSign",
                     HLT_Mu20_Mu10_SameSign);
    if ( choose["HLT_Mu20_Mu10_SameSign_DZ"] )
      input->select("Events/HLT_Mu20_Mu10_SameSign_DZ",
                     HLT_Mu20_Mu10_SameSign_DZ);
    if ( choose["HLT_Mu20_TkMu0_Phi"] )
      input->select("Events/HLT_Mu20_TkMu0_Phi", 	HLT_Mu20_TkMu0_Phi);
    if ( choose["HLT_Mu23_Mu12"] )
      input->select("Events/HLT_Mu23_Mu12", 	HLT_Mu23_Mu12);
    if ( choose["HLT_Mu23_Mu12_DZ"] )
      input->select("Events/HLT_Mu23_Mu12_DZ", 	HLT_Mu23_Mu12_DZ);
    if ( choose["HLT_Mu23_Mu12_SameSign"] )
      input->select("Events/HLT_Mu23_Mu12_SameSign",
                     HLT_Mu23_Mu12_SameSign);
    if ( choose["HLT_Mu23_Mu12_SameSign_DZ"] )
      input->select("Events/HLT_Mu23_Mu12_SameSign_DZ",
                     HLT_Mu23_Mu12_SameSign_DZ);
    if ( choose["HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL"] )
      input->select("Events/HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL",
                     HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL);
    if ( choose["HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ"] )
      input->select("Events/HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ",
                     HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ);
    if ( choose["HLT_Mu25_TkMu0_Onia"] )
      input->select("Events/HLT_Mu25_TkMu0_Onia", 	HLT_Mu25_TkMu0_Onia);
    if ( choose["HLT_Mu25_TkMu0_Phi"] )
      input->select("Events/HLT_Mu25_TkMu0_Phi", 	HLT_Mu25_TkMu0_Phi);
    if ( choose["HLT_Mu27"] )
      input->select("Events/HLT_Mu27", 	HLT_Mu27);
    if ( choose["HLT_Mu27_Ele37_CaloIdL_MW"] )
      input->select("Events/HLT_Mu27_Ele37_CaloIdL_MW",
                     HLT_Mu27_Ele37_CaloIdL_MW);
    if ( choose["HLT_Mu30_TkMu0_Psi"] )
      input->select("Events/HLT_Mu30_TkMu0_Psi", 	HLT_Mu30_TkMu0_Psi);
    if ( choose["HLT_Mu30_TkMu0_Upsilon"] )
      input->select("Events/HLT_Mu30_TkMu0_Upsilon",
                     HLT_Mu30_TkMu0_Upsilon);
    if ( choose["HLT_Mu37_Ele27_CaloIdL_MW"] )
      input->select("Events/HLT_Mu37_Ele27_CaloIdL_MW",
                     HLT_Mu37_Ele27_CaloIdL_MW);
    if ( choose["HLT_Mu37_TkMu27"] )
      input->select("Events/HLT_Mu37_TkMu27", 	HLT_Mu37_TkMu27);
    if ( choose["HLT_Mu38NoFiltersNoVtxDisplaced_Photon38_CaloIdL"] )
      input->select("Events/HLT_Mu38NoFiltersNoVtxDisplaced_Photon38_CaloIdL",
                     HLT_Mu38NoFiltersNoVtxDisplaced_Photon38_CaloIdL);
    if ( choose["HLT_Mu3_L1SingleMu5orSingleMu7"] )
      input->select("Events/HLT_Mu3_L1SingleMu5orSingleMu7",
                     HLT_Mu3_L1SingleMu5orSingleMu7);
    if ( choose["HLT_Mu3_PFJet40"] )
      input->select("Events/HLT_Mu3_PFJet40", 	HLT_Mu3_PFJet40);
    if ( choose["HLT_Mu3er1p5_PFJet100er2p5_PFMET100_PFMHT100_IDTight"] )
      input->select("Events/HLT_Mu3er1p5_PFJet100er2p5_PFMET100_PFMHT100_IDTight",
                     HLT_Mu3er1p5_PFJet100er2p5_PFMET100_PFMHT100_IDTight);
    if ( choose["HLT_Mu3er1p5_PFJet100er2p5_PFMET70_PFMHT70_IDTight"] )
      input->select("Events/HLT_Mu3er1p5_PFJet100er2p5_PFMET70_PFMHT70_IDTight",
                     HLT_Mu3er1p5_PFJet100er2p5_PFMET70_PFMHT70_IDTight);
    if ( choose["HLT_Mu3er1p5_PFJet100er2p5_PFMET80_PFMHT80_IDTight"] )
      input->select("Events/HLT_Mu3er1p5_PFJet100er2p5_PFMET80_PFMHT80_IDTight",
                     HLT_Mu3er1p5_PFJet100er2p5_PFMET80_PFMHT80_IDTight);
    if ( choose["HLT_Mu3er1p5_PFJet100er2p5_PFMET90_PFMHT90_IDTight"] )
      input->select("Events/HLT_Mu3er1p5_PFJet100er2p5_PFMET90_PFMHT90_IDTight",
                     HLT_Mu3er1p5_PFJet100er2p5_PFMET90_PFMHT90_IDTight);
    if ( choose["HLT_Mu3er1p5_PFJet100er2p5_PFMETNoMu100_PFMHTNoMu100_IDTight"] )
      input->select("Events/HLT_Mu3er1p5_PFJet100er2p5_PFMETNoMu100_PFMHTNoMu100_IDTight",
                     HLT_Mu3er1p5_PFJet100er2p5_PFMETNoMu100_PFMHTNoMu100_IDTight);
    if ( choose["HLT_Mu3er1p5_PFJet100er2p5_PFMETNoMu70_PFMHTNoMu70_IDTight"] )
      input->select("Events/HLT_Mu3er1p5_PFJet100er2p5_PFMETNoMu70_PFMHTNoMu70_IDTight",
                     HLT_Mu3er1p5_PFJet100er2p5_PFMETNoMu70_PFMHTNoMu70_IDTight);
    if ( choose["HLT_Mu3er1p5_PFJet100er2p5_PFMETNoMu80_PFMHTNoMu80_IDTight"] )
      input->select("Events/HLT_Mu3er1p5_PFJet100er2p5_PFMETNoMu80_PFMHTNoMu80_IDTight",
                     HLT_Mu3er1p5_PFJet100er2p5_PFMETNoMu80_PFMHTNoMu80_IDTight);
    if ( choose["HLT_Mu3er1p5_PFJet100er2p5_PFMETNoMu90_PFMHTNoMu90_IDTight"] )
      input->select("Events/HLT_Mu3er1p5_PFJet100er2p5_PFMETNoMu90_PFMHTNoMu90_IDTight",
                     HLT_Mu3er1p5_PFJet100er2p5_PFMETNoMu90_PFMHTNoMu90_IDTight);
    if ( choose["HLT_Mu43NoFiltersNoVtxDisplaced_Photon43_CaloIdL"] )
      input->select("Events/HLT_Mu43NoFiltersNoVtxDisplaced_Photon43_CaloIdL",
                     HLT_Mu43NoFiltersNoVtxDisplaced_Photon43_CaloIdL);
    if ( choose["HLT_Mu43NoFiltersNoVtx_Photon43_CaloIdL"] )
      input->select("Events/HLT_Mu43NoFiltersNoVtx_Photon43_CaloIdL",
                     HLT_Mu43NoFiltersNoVtx_Photon43_CaloIdL);
    if ( choose["HLT_Mu48NoFiltersNoVtx_Photon48_CaloIdL"] )
      input->select("Events/HLT_Mu48NoFiltersNoVtx_Photon48_CaloIdL",
                     HLT_Mu48NoFiltersNoVtx_Photon48_CaloIdL);
    if ( choose["HLT_Mu4_TrkIsoVVL_DiPFJet90_40_DEta3p5_MJJ750_HTT300_PFMETNoMu60"] )
      input->select("Events/HLT_Mu4_TrkIsoVVL_DiPFJet90_40_DEta3p5_MJJ750_HTT300_PFMETNoMu60",
                     HLT_Mu4_TrkIsoVVL_DiPFJet90_40_DEta3p5_MJJ750_HTT300_PFMETNoMu60);
    if ( choose["HLT_Mu50"] )
      input->select("Events/HLT_Mu50", 	HLT_Mu50);
    if ( choose["HLT_Mu50_IsoVVVL_PFHT450"] )
      input->select("Events/HLT_Mu50_IsoVVVL_PFHT450",
                     HLT_Mu50_IsoVVVL_PFHT450);
    if ( choose["HLT_Mu55"] )
      input->select("Events/HLT_Mu55", 	HLT_Mu55);
    if ( choose["HLT_Mu7_IP4_part0"] )
      input->select("Events/HLT_Mu7_IP4_part0", 	HLT_Mu7_IP4_part0);
    if ( choose["HLT_Mu7_IP4_part1"] )
      input->select("Events/HLT_Mu7_IP4_part1", 	HLT_Mu7_IP4_part1);
    if ( choose["HLT_Mu7_IP4_part2"] )
      input->select("Events/HLT_Mu7_IP4_part2", 	HLT_Mu7_IP4_part2);
    if ( choose["HLT_Mu7_IP4_part3"] )
      input->select("Events/HLT_Mu7_IP4_part3", 	HLT_Mu7_IP4_part3);
    if ( choose["HLT_Mu7_IP4_part4"] )
      input->select("Events/HLT_Mu7_IP4_part4", 	HLT_Mu7_IP4_part4);
    if ( choose["HLT_Mu7p5_L2Mu2_Jpsi"] )
      input->select("Events/HLT_Mu7p5_L2Mu2_Jpsi", 	HLT_Mu7p5_L2Mu2_Jpsi);
    if ( choose["HLT_Mu7p5_L2Mu2_Upsilon"] )
      input->select("Events/HLT_Mu7p5_L2Mu2_Upsilon",
                     HLT_Mu7p5_L2Mu2_Upsilon);
    if ( choose["HLT_Mu7p5_Track2_Jpsi"] )
      input->select("Events/HLT_Mu7p5_Track2_Jpsi", 	HLT_Mu7p5_Track2_Jpsi);
    if ( choose["HLT_Mu7p5_Track2_Upsilon"] )
      input->select("Events/HLT_Mu7p5_Track2_Upsilon",
                     HLT_Mu7p5_Track2_Upsilon);
    if ( choose["HLT_Mu7p5_Track3p5_Jpsi"] )
      input->select("Events/HLT_Mu7p5_Track3p5_Jpsi",
                     HLT_Mu7p5_Track3p5_Jpsi);
    if ( choose["HLT_Mu7p5_Track3p5_Upsilon"] )
      input->select("Events/HLT_Mu7p5_Track3p5_Upsilon",
                     HLT_Mu7p5_Track3p5_Upsilon);
    if ( choose["HLT_Mu7p5_Track7_Jpsi"] )
      input->select("Events/HLT_Mu7p5_Track7_Jpsi", 	HLT_Mu7p5_Track7_Jpsi);
    if ( choose["HLT_Mu7p5_Track7_Upsilon"] )
      input->select("Events/HLT_Mu7p5_Track7_Upsilon",
                     HLT_Mu7p5_Track7_Upsilon);
    if ( choose["HLT_Mu8"] )
      input->select("Events/HLT_Mu8", 	HLT_Mu8);
    if ( choose["HLT_Mu8_DiEle12_CaloIdL_TrackIdL"] )
      input->select("Events/HLT_Mu8_DiEle12_CaloIdL_TrackIdL",
                     HLT_Mu8_DiEle12_CaloIdL_TrackIdL);
    if ( choose["HLT_Mu8_DiEle12_CaloIdL_TrackIdL_DZ"] )
      input->select("Events/HLT_Mu8_DiEle12_CaloIdL_TrackIdL_DZ",
                     HLT_Mu8_DiEle12_CaloIdL_TrackIdL_DZ);
    if ( choose["HLT_Mu8_Ele8_CaloIdM_TrackIdM_Mass8_PFHT350"] )
      input->select("Events/HLT_Mu8_Ele8_CaloIdM_TrackIdM_Mass8_PFHT350",
                     HLT_Mu8_Ele8_CaloIdM_TrackIdM_Mass8_PFHT350);
    if ( choose["HLT_Mu8_Ele8_CaloIdM_TrackIdM_Mass8_PFHT350_DZ"] )
      input->select("Events/HLT_Mu8_Ele8_CaloIdM_TrackIdM_Mass8_PFHT350_DZ",
                     HLT_Mu8_Ele8_CaloIdM_TrackIdM_Mass8_PFHT350_DZ);
    if ( choose["HLT_Mu8_IP3_part0"] )
      input->select("Events/HLT_Mu8_IP3_part0", 	HLT_Mu8_IP3_part0);
    if ( choose["HLT_Mu8_IP3_part1"] )
      input->select("Events/HLT_Mu8_IP3_part1", 	HLT_Mu8_IP3_part1);
    if ( choose["HLT_Mu8_IP3_part2"] )
      input->select("Events/HLT_Mu8_IP3_part2", 	HLT_Mu8_IP3_part2);
    if ( choose["HLT_Mu8_IP3_part3"] )
      input->select("Events/HLT_Mu8_IP3_part3", 	HLT_Mu8_IP3_part3);
    if ( choose["HLT_Mu8_IP3_part4"] )
      input->select("Events/HLT_Mu8_IP3_part4", 	HLT_Mu8_IP3_part4);
    if ( choose["HLT_Mu8_IP5_part0"] )
      input->select("Events/HLT_Mu8_IP5_part0", 	HLT_Mu8_IP5_part0);
    if ( choose["HLT_Mu8_IP5_part1"] )
      input->select("Events/HLT_Mu8_IP5_part1", 	HLT_Mu8_IP5_part1);
    if ( choose["HLT_Mu8_IP5_part2"] )
      input->select("Events/HLT_Mu8_IP5_part2", 	HLT_Mu8_IP5_part2);
    if ( choose["HLT_Mu8_IP5_part3"] )
      input->select("Events/HLT_Mu8_IP5_part3", 	HLT_Mu8_IP5_part3);
    if ( choose["HLT_Mu8_IP5_part4"] )
      input->select("Events/HLT_Mu8_IP5_part4", 	HLT_Mu8_IP5_part4);
    if ( choose["HLT_Mu8_IP6_part0"] )
      input->select("Events/HLT_Mu8_IP6_part0", 	HLT_Mu8_IP6_part0);
    if ( choose["HLT_Mu8_IP6_part1"] )
      input->select("Events/HLT_Mu8_IP6_part1", 	HLT_Mu8_IP6_part1);
    if ( choose["HLT_Mu8_IP6_part2"] )
      input->select("Events/HLT_Mu8_IP6_part2", 	HLT_Mu8_IP6_part2);
    if ( choose["HLT_Mu8_IP6_part3"] )
      input->select("Events/HLT_Mu8_IP6_part3", 	HLT_Mu8_IP6_part3);
    if ( choose["HLT_Mu8_IP6_part4"] )
      input->select("Events/HLT_Mu8_IP6_part4", 	HLT_Mu8_IP6_part4);
    if ( choose["HLT_Mu8_TrkIsoVVL"] )
      input->select("Events/HLT_Mu8_TrkIsoVVL", 	HLT_Mu8_TrkIsoVVL);
    if ( choose["HLT_Mu8_TrkIsoVVL_DiPFJet40_DEta3p5_MJJ750_HTT300_PFMETNoMu60"] )
      input->select("Events/HLT_Mu8_TrkIsoVVL_DiPFJet40_DEta3p5_MJJ750_HTT300_PFMETNoMu60",
                     HLT_Mu8_TrkIsoVVL_DiPFJet40_DEta3p5_MJJ750_HTT300_PFMETNoMu60);
    if ( choose["HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL"] )
      input->select("Events/HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL",
                     HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL);
    if ( choose["HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ"] )
      input->select("Events/HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ",
                     HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ);
    if ( choose["HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_CaloDiJet30"] )
      input->select("Events/HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_CaloDiJet30",
                     HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_CaloDiJet30);
    if ( choose["HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_CaloDiJet30_CaloBtagDeepCSV_1p5"] )
      input->select("Events/HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_CaloDiJet30_CaloBtagDeepCSV_1p5",
                     HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_CaloDiJet30_CaloBtagDeepCSV_1p5);
    if ( choose["HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_PFDiJet30"] )
      input->select("Events/HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_PFDiJet30",
                     HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_PFDiJet30);
    if ( choose["HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_PFDiJet30_PFBtagDeepCSV_1p5"] )
      input->select("Events/HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_PFDiJet30_PFBtagDeepCSV_1p5",
                     HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_PFDiJet30_PFBtagDeepCSV_1p5);
    if ( choose["HLT_Mu9_IP4_part0"] )
      input->select("Events/HLT_Mu9_IP4_part0", 	HLT_Mu9_IP4_part0);
    if ( choose["HLT_Mu9_IP4_part1"] )
      input->select("Events/HLT_Mu9_IP4_part1", 	HLT_Mu9_IP4_part1);
    if ( choose["HLT_Mu9_IP4_part2"] )
      input->select("Events/HLT_Mu9_IP4_part2", 	HLT_Mu9_IP4_part2);
    if ( choose["HLT_Mu9_IP4_part3"] )
      input->select("Events/HLT_Mu9_IP4_part3", 	HLT_Mu9_IP4_part3);
    if ( choose["HLT_Mu9_IP4_part4"] )
      input->select("Events/HLT_Mu9_IP4_part4", 	HLT_Mu9_IP4_part4);
    if ( choose["HLT_Mu9_IP5_part0"] )
      input->select("Events/HLT_Mu9_IP5_part0", 	HLT_Mu9_IP5_part0);
    if ( choose["HLT_Mu9_IP5_part1"] )
      input->select("Events/HLT_Mu9_IP5_part1", 	HLT_Mu9_IP5_part1);
    if ( choose["HLT_Mu9_IP5_part2"] )
      input->select("Events/HLT_Mu9_IP5_part2", 	HLT_Mu9_IP5_part2);
    if ( choose["HLT_Mu9_IP5_part3"] )
      input->select("Events/HLT_Mu9_IP5_part3", 	HLT_Mu9_IP5_part3);
    if ( choose["HLT_Mu9_IP5_part4"] )
      input->select("Events/HLT_Mu9_IP5_part4", 	HLT_Mu9_IP5_part4);
    if ( choose["HLT_Mu9_IP6_part0"] )
      input->select("Events/HLT_Mu9_IP6_part0", 	HLT_Mu9_IP6_part0);
    if ( choose["HLT_Mu9_IP6_part1"] )
      input->select("Events/HLT_Mu9_IP6_part1", 	HLT_Mu9_IP6_part1);
    if ( choose["HLT_Mu9_IP6_part2"] )
      input->select("Events/HLT_Mu9_IP6_part2", 	HLT_Mu9_IP6_part2);
    if ( choose["HLT_Mu9_IP6_part3"] )
      input->select("Events/HLT_Mu9_IP6_part3", 	HLT_Mu9_IP6_part3);
    if ( choose["HLT_Mu9_IP6_part4"] )
      input->select("Events/HLT_Mu9_IP6_part4", 	HLT_Mu9_IP6_part4);
    if ( choose["HLT_OldMu100"] )
      input->select("Events/HLT_OldMu100", 	HLT_OldMu100);
    if ( choose["HLT_PFHT1050"] )
      input->select("Events/HLT_PFHT1050", 	HLT_PFHT1050);
    if ( choose["HLT_PFHT180"] )
      input->select("Events/HLT_PFHT180", 	HLT_PFHT180);
    if ( choose["HLT_PFHT250"] )
      input->select("Events/HLT_PFHT250", 	HLT_PFHT250);
    if ( choose["HLT_PFHT330PT30_QuadPFJet_75_60_45_40"] )
      input->select("Events/HLT_PFHT330PT30_QuadPFJet_75_60_45_40",
                     HLT_PFHT330PT30_QuadPFJet_75_60_45_40);
    if ( choose["HLT_PFHT330PT30_QuadPFJet_75_60_45_40_TriplePFBTagDeepCSV_4p5"] )
      input->select("Events/HLT_PFHT330PT30_QuadPFJet_75_60_45_40_TriplePFBTagDeepCSV_4p5",
                     HLT_PFHT330PT30_QuadPFJet_75_60_45_40_TriplePFBTagDeepCSV_4p5);
    if ( choose["HLT_PFHT350"] )
      input->select("Events/HLT_PFHT350", 	HLT_PFHT350);
    if ( choose["HLT_PFHT350MinPFJet15"] )
      input->select("Events/HLT_PFHT350MinPFJet15", 	HLT_PFHT350MinPFJet15);
    if ( choose["HLT_PFHT370"] )
      input->select("Events/HLT_PFHT370", 	HLT_PFHT370);
    if ( choose["HLT_PFHT400_SixPFJet32"] )
      input->select("Events/HLT_PFHT400_SixPFJet32",
                     HLT_PFHT400_SixPFJet32);
    if ( choose["HLT_PFHT400_SixPFJet32_DoublePFBTagDeepCSV_2p94"] )
      input->select("Events/HLT_PFHT400_SixPFJet32_DoublePFBTagDeepCSV_2p94",
                     HLT_PFHT400_SixPFJet32_DoublePFBTagDeepCSV_2p94);
    if ( choose["HLT_PFHT430"] )
      input->select("Events/HLT_PFHT430", 	HLT_PFHT430);
    if ( choose["HLT_PFHT450_SixPFJet36"] )
      input->select("Events/HLT_PFHT450_SixPFJet36",
                     HLT_PFHT450_SixPFJet36);
    if ( choose["HLT_PFHT450_SixPFJet36_PFBTagDeepCSV_1p59"] )
      input->select("Events/HLT_PFHT450_SixPFJet36_PFBTagDeepCSV_1p59",
                     HLT_PFHT450_SixPFJet36_PFBTagDeepCSV_1p59);
    if ( choose["HLT_PFHT500_PFMET100_PFMHT100_IDTight"] )
      input->select("Events/HLT_PFHT500_PFMET100_PFMHT100_IDTight",
                     HLT_PFHT500_PFMET100_PFMHT100_IDTight);
    if ( choose["HLT_PFHT500_PFMET110_PFMHT110_IDTight"] )
      input->select("Events/HLT_PFHT500_PFMET110_PFMHT110_IDTight",
                     HLT_PFHT500_PFMET110_PFMHT110_IDTight);
    if ( choose["HLT_PFHT510"] )
      input->select("Events/HLT_PFHT510", 	HLT_PFHT510);
    if ( choose["HLT_PFHT590"] )
      input->select("Events/HLT_PFHT590", 	HLT_PFHT590);
    if ( choose["HLT_PFHT680"] )
      input->select("Events/HLT_PFHT680", 	HLT_PFHT680);
    if ( choose["HLT_PFHT700_PFMET85_PFMHT85_IDTight"] )
      input->select("Events/HLT_PFHT700_PFMET85_PFMHT85_IDTight",
                     HLT_PFHT700_PFMET85_PFMHT85_IDTight);
    if ( choose["HLT_PFHT700_PFMET95_PFMHT95_IDTight"] )
      input->select("Events/HLT_PFHT700_PFMET95_PFMHT95_IDTight",
                     HLT_PFHT700_PFMET95_PFMHT95_IDTight);
    if ( choose["HLT_PFHT780"] )
      input->select("Events/HLT_PFHT780", 	HLT_PFHT780);
    if ( choose["HLT_PFHT800_PFMET75_PFMHT75_IDTight"] )
      input->select("Events/HLT_PFHT800_PFMET75_PFMHT75_IDTight",
                     HLT_PFHT800_PFMET75_PFMHT75_IDTight);
    if ( choose["HLT_PFHT800_PFMET85_PFMHT85_IDTight"] )
      input->select("Events/HLT_PFHT800_PFMET85_PFMHT85_IDTight",
                     HLT_PFHT800_PFMET85_PFMHT85_IDTight);
    if ( choose["HLT_PFHT890"] )
      input->select("Events/HLT_PFHT890", 	HLT_PFHT890);
    if ( choose["HLT_PFJet140"] )
      input->select("Events/HLT_PFJet140", 	HLT_PFJet140);
    if ( choose["HLT_PFJet15"] )
      input->select("Events/HLT_PFJet15", 	HLT_PFJet15);
    if ( choose["HLT_PFJet200"] )
      input->select("Events/HLT_PFJet200", 	HLT_PFJet200);
    if ( choose["HLT_PFJet25"] )
      input->select("Events/HLT_PFJet25", 	HLT_PFJet25);
    if ( choose["HLT_PFJet260"] )
      input->select("Events/HLT_PFJet260", 	HLT_PFJet260);
    if ( choose["HLT_PFJet320"] )
      input->select("Events/HLT_PFJet320", 	HLT_PFJet320);
    if ( choose["HLT_PFJet40"] )
      input->select("Events/HLT_PFJet40", 	HLT_PFJet40);
    if ( choose["HLT_PFJet400"] )
      input->select("Events/HLT_PFJet400", 	HLT_PFJet400);
    if ( choose["HLT_PFJet450"] )
      input->select("Events/HLT_PFJet450", 	HLT_PFJet450);
    if ( choose["HLT_PFJet500"] )
      input->select("Events/HLT_PFJet500", 	HLT_PFJet500);
    if ( choose["HLT_PFJet550"] )
      input->select("Events/HLT_PFJet550", 	HLT_PFJet550);
    if ( choose["HLT_PFJet60"] )
      input->select("Events/HLT_PFJet60", 	HLT_PFJet60);
    if ( choose["HLT_PFJet80"] )
      input->select("Events/HLT_PFJet80", 	HLT_PFJet80);
    if ( choose["HLT_PFJetFwd140"] )
      input->select("Events/HLT_PFJetFwd140", 	HLT_PFJetFwd140);
    if ( choose["HLT_PFJetFwd15"] )
      input->select("Events/HLT_PFJetFwd15", 	HLT_PFJetFwd15);
    if ( choose["HLT_PFJetFwd200"] )
      input->select("Events/HLT_PFJetFwd200", 	HLT_PFJetFwd200);
    if ( choose["HLT_PFJetFwd25"] )
      input->select("Events/HLT_PFJetFwd25", 	HLT_PFJetFwd25);
    if ( choose["HLT_PFJetFwd260"] )
      input->select("Events/HLT_PFJetFwd260", 	HLT_PFJetFwd260);
    if ( choose["HLT_PFJetFwd320"] )
      input->select("Events/HLT_PFJetFwd320", 	HLT_PFJetFwd320);
    if ( choose["HLT_PFJetFwd40"] )
      input->select("Events/HLT_PFJetFwd40", 	HLT_PFJetFwd40);
    if ( choose["HLT_PFJetFwd400"] )
      input->select("Events/HLT_PFJetFwd400", 	HLT_PFJetFwd400);
    if ( choose["HLT_PFJetFwd450"] )
      input->select("Events/HLT_PFJetFwd450", 	HLT_PFJetFwd450);
    if ( choose["HLT_PFJetFwd500"] )
      input->select("Events/HLT_PFJetFwd500", 	HLT_PFJetFwd500);
    if ( choose["HLT_PFJetFwd60"] )
      input->select("Events/HLT_PFJetFwd60", 	HLT_PFJetFwd60);
    if ( choose["HLT_PFJetFwd80"] )
      input->select("Events/HLT_PFJetFwd80", 	HLT_PFJetFwd80);
    if ( choose["HLT_PFMET100_PFMHT100_IDTight_CaloBTagDeepCSV_3p1"] )
      input->select("Events/HLT_PFMET100_PFMHT100_IDTight_CaloBTagDeepCSV_3p1",
                     HLT_PFMET100_PFMHT100_IDTight_CaloBTagDeepCSV_3p1);
    if ( choose["HLT_PFMET100_PFMHT100_IDTight_PFHT60"] )
      input->select("Events/HLT_PFMET100_PFMHT100_IDTight_PFHT60",
                     HLT_PFMET100_PFMHT100_IDTight_PFHT60);
    if ( choose["HLT_PFMET110_PFMHT110_IDTight"] )
      input->select("Events/HLT_PFMET110_PFMHT110_IDTight",
                     HLT_PFMET110_PFMHT110_IDTight);
    if ( choose["HLT_PFMET110_PFMHT110_IDTight_CaloBTagDeepCSV_3p1"] )
      input->select("Events/HLT_PFMET110_PFMHT110_IDTight_CaloBTagDeepCSV_3p1",
                     HLT_PFMET110_PFMHT110_IDTight_CaloBTagDeepCSV_3p1);
    if ( choose["HLT_PFMET120_PFMHT120_IDTight"] )
      input->select("Events/HLT_PFMET120_PFMHT120_IDTight",
                     HLT_PFMET120_PFMHT120_IDTight);
    if ( choose["HLT_PFMET120_PFMHT120_IDTight_CaloBTagDeepCSV_3p1"] )
      input->select("Events/HLT_PFMET120_PFMHT120_IDTight_CaloBTagDeepCSV_3p1",
                     HLT_PFMET120_PFMHT120_IDTight_CaloBTagDeepCSV_3p1);
    if ( choose["HLT_PFMET120_PFMHT120_IDTight_PFHT60"] )
      input->select("Events/HLT_PFMET120_PFMHT120_IDTight_PFHT60",
                     HLT_PFMET120_PFMHT120_IDTight_PFHT60);
    if ( choose["HLT_PFMET130_PFMHT130_IDTight"] )
      input->select("Events/HLT_PFMET130_PFMHT130_IDTight",
                     HLT_PFMET130_PFMHT130_IDTight);
    if ( choose["HLT_PFMET130_PFMHT130_IDTight_CaloBTagDeepCSV_3p1"] )
      input->select("Events/HLT_PFMET130_PFMHT130_IDTight_CaloBTagDeepCSV_3p1",
                     HLT_PFMET130_PFMHT130_IDTight_CaloBTagDeepCSV_3p1);
    if ( choose["HLT_PFMET140_PFMHT140_IDTight"] )
      input->select("Events/HLT_PFMET140_PFMHT140_IDTight",
                     HLT_PFMET140_PFMHT140_IDTight);
    if ( choose["HLT_PFMET140_PFMHT140_IDTight_CaloBTagDeepCSV_3p1"] )
      input->select("Events/HLT_PFMET140_PFMHT140_IDTight_CaloBTagDeepCSV_3p1",
                     HLT_PFMET140_PFMHT140_IDTight_CaloBTagDeepCSV_3p1);
    if ( choose["HLT_PFMET200_HBHECleaned"] )
      input->select("Events/HLT_PFMET200_HBHECleaned",
                     HLT_PFMET200_HBHECleaned);
    if ( choose["HLT_PFMET200_HBHE_BeamHaloCleaned"] )
      input->select("Events/HLT_PFMET200_HBHE_BeamHaloCleaned",
                     HLT_PFMET200_HBHE_BeamHaloCleaned);
    if ( choose["HLT_PFMET200_NotCleaned"] )
      input->select("Events/HLT_PFMET200_NotCleaned",
                     HLT_PFMET200_NotCleaned);
    if ( choose["HLT_PFMET250_HBHECleaned"] )
      input->select("Events/HLT_PFMET250_HBHECleaned",
                     HLT_PFMET250_HBHECleaned);
    if ( choose["HLT_PFMET300_HBHECleaned"] )
      input->select("Events/HLT_PFMET300_HBHECleaned",
                     HLT_PFMET300_HBHECleaned);
    if ( choose["HLT_PFMETNoMu100_PFMHTNoMu100_IDTight_PFHT60"] )
      input->select("Events/HLT_PFMETNoMu100_PFMHTNoMu100_IDTight_PFHT60",
                     HLT_PFMETNoMu100_PFMHTNoMu100_IDTight_PFHT60);
    if ( choose["HLT_PFMETNoMu110_PFMHTNoMu110_IDTight"] )
      input->select("Events/HLT_PFMETNoMu110_PFMHTNoMu110_IDTight",
                     HLT_PFMETNoMu110_PFMHTNoMu110_IDTight);
    if ( choose["HLT_PFMETNoMu120_PFMHTNoMu120_IDTight"] )
      input->select("Events/HLT_PFMETNoMu120_PFMHTNoMu120_IDTight",
                     HLT_PFMETNoMu120_PFMHTNoMu120_IDTight);
    if ( choose["HLT_PFMETNoMu120_PFMHTNoMu120_IDTight_PFHT60"] )
      input->select("Events/HLT_PFMETNoMu120_PFMHTNoMu120_IDTight_PFHT60",
                     HLT_PFMETNoMu120_PFMHTNoMu120_IDTight_PFHT60);
    if ( choose["HLT_PFMETNoMu130_PFMHTNoMu130_IDTight"] )
      input->select("Events/HLT_PFMETNoMu130_PFMHTNoMu130_IDTight",
                     HLT_PFMETNoMu130_PFMHTNoMu130_IDTight);
    if ( choose["HLT_PFMETNoMu140_PFMHTNoMu140_IDTight"] )
      input->select("Events/HLT_PFMETNoMu140_PFMHTNoMu140_IDTight",
                     HLT_PFMETNoMu140_PFMHTNoMu140_IDTight);
    if ( choose["HLT_PFMETTypeOne100_PFMHT100_IDTight_PFHT60"] )
      input->select("Events/HLT_PFMETTypeOne100_PFMHT100_IDTight_PFHT60",
                     HLT_PFMETTypeOne100_PFMHT100_IDTight_PFHT60);
    if ( choose["HLT_PFMETTypeOne110_PFMHT110_IDTight"] )
      input->select("Events/HLT_PFMETTypeOne110_PFMHT110_IDTight",
                     HLT_PFMETTypeOne110_PFMHT110_IDTight);
    if ( choose["HLT_PFMETTypeOne120_PFMHT120_IDTight"] )
      input->select("Events/HLT_PFMETTypeOne120_PFMHT120_IDTight",
                     HLT_PFMETTypeOne120_PFMHT120_IDTight);
    if ( choose["HLT_PFMETTypeOne120_PFMHT120_IDTight_PFHT60"] )
      input->select("Events/HLT_PFMETTypeOne120_PFMHT120_IDTight_PFHT60",
                     HLT_PFMETTypeOne120_PFMHT120_IDTight_PFHT60);
    if ( choose["HLT_PFMETTypeOne130_PFMHT130_IDTight"] )
      input->select("Events/HLT_PFMETTypeOne130_PFMHT130_IDTight",
                     HLT_PFMETTypeOne130_PFMHT130_IDTight);
    if ( choose["HLT_PFMETTypeOne140_PFMHT140_IDTight"] )
      input->select("Events/HLT_PFMETTypeOne140_PFMHT140_IDTight",
                     HLT_PFMETTypeOne140_PFMHT140_IDTight);
    if ( choose["HLT_PFMETTypeOne200_HBHE_BeamHaloCleaned"] )
      input->select("Events/HLT_PFMETTypeOne200_HBHE_BeamHaloCleaned",
                     HLT_PFMETTypeOne200_HBHE_BeamHaloCleaned);
    if ( choose["HLT_Photon100EBHE10"] )
      input->select("Events/HLT_Photon100EBHE10", 	HLT_Photon100EBHE10);
    if ( choose["HLT_Photon100EB_TightID_TightIso"] )
      input->select("Events/HLT_Photon100EB_TightID_TightIso",
                     HLT_Photon100EB_TightID_TightIso);
    if ( choose["HLT_Photon100EEHE10"] )
      input->select("Events/HLT_Photon100EEHE10", 	HLT_Photon100EEHE10);
    if ( choose["HLT_Photon100EE_TightID_TightIso"] )
      input->select("Events/HLT_Photon100EE_TightID_TightIso",
                     HLT_Photon100EE_TightID_TightIso);
    if ( choose["HLT_Photon110EB_TightID_TightIso"] )
      input->select("Events/HLT_Photon110EB_TightID_TightIso",
                     HLT_Photon110EB_TightID_TightIso);
    if ( choose["HLT_Photon120"] )
      input->select("Events/HLT_Photon120", 	HLT_Photon120);
    if ( choose["HLT_Photon120EB_TightID_TightIso"] )
      input->select("Events/HLT_Photon120EB_TightID_TightIso",
                     HLT_Photon120EB_TightID_TightIso);
    if ( choose["HLT_Photon120_R9Id90_HE10_IsoM"] )
      input->select("Events/HLT_Photon120_R9Id90_HE10_IsoM",
                     HLT_Photon120_R9Id90_HE10_IsoM);
    if ( choose["HLT_Photon150"] )
      input->select("Events/HLT_Photon150", 	HLT_Photon150);
    if ( choose["HLT_Photon165_R9Id90_HE10_IsoM"] )
      input->select("Events/HLT_Photon165_R9Id90_HE10_IsoM",
                     HLT_Photon165_R9Id90_HE10_IsoM);
    if ( choose["HLT_Photon175"] )
      input->select("Events/HLT_Photon175", 	HLT_Photon175);
    if ( choose["HLT_Photon20"] )
      input->select("Events/HLT_Photon20", 	HLT_Photon20);
    if ( choose["HLT_Photon200"] )
      input->select("Events/HLT_Photon200", 	HLT_Photon200);
    if ( choose["HLT_Photon20_HoverELoose"] )
      input->select("Events/HLT_Photon20_HoverELoose",
                     HLT_Photon20_HoverELoose);
    if ( choose["HLT_Photon300_NoHE"] )
      input->select("Events/HLT_Photon300_NoHE", 	HLT_Photon300_NoHE);
    if ( choose["HLT_Photon30_HoverELoose"] )
      input->select("Events/HLT_Photon30_HoverELoose",
                     HLT_Photon30_HoverELoose);
    if ( choose["HLT_Photon33"] )
      input->select("Events/HLT_Photon33", 	HLT_Photon33);
    if ( choose["HLT_Photon35_TwoProngs35"] )
      input->select("Events/HLT_Photon35_TwoProngs35",
                     HLT_Photon35_TwoProngs35);
    if ( choose["HLT_Photon50"] )
      input->select("Events/HLT_Photon50", 	HLT_Photon50);
    if ( choose["HLT_Photon50_R9Id90_HE10_IsoM"] )
      input->select("Events/HLT_Photon50_R9Id90_HE10_IsoM",
                     HLT_Photon50_R9Id90_HE10_IsoM);
    if ( choose["HLT_Photon50_R9Id90_HE10_IsoM_EBOnly_PFJetsMJJ300DEta3_PFMET50"] )
      input->select("Events/HLT_Photon50_R9Id90_HE10_IsoM_EBOnly_PFJetsMJJ300DEta3_PFMET50",
                     HLT_Photon50_R9Id90_HE10_IsoM_EBOnly_PFJetsMJJ300DEta3_PFMET50);
    if ( choose["HLT_Photon60_R9Id90_CaloIdL_IsoL"] )
      input->select("Events/HLT_Photon60_R9Id90_CaloIdL_IsoL",
                     HLT_Photon60_R9Id90_CaloIdL_IsoL);
    if ( choose["HLT_Photon60_R9Id90_CaloIdL_IsoL_DisplacedIdL"] )
      input->select("Events/HLT_Photon60_R9Id90_CaloIdL_IsoL_DisplacedIdL",
                     HLT_Photon60_R9Id90_CaloIdL_IsoL_DisplacedIdL);
    if ( choose["HLT_Photon60_R9Id90_CaloIdL_IsoL_DisplacedIdL_PFHT350MinPFJet15"] )
      input->select("Events/HLT_Photon60_R9Id90_CaloIdL_IsoL_DisplacedIdL_PFHT350MinPFJet15",
                     HLT_Photon60_R9Id90_CaloIdL_IsoL_DisplacedIdL_PFHT350MinPFJet15);
    if ( choose["HLT_Photon75"] )
      input->select("Events/HLT_Photon75", 	HLT_Photon75);
    if ( choose["HLT_Photon75_R9Id90_HE10_IsoM"] )
      input->select("Events/HLT_Photon75_R9Id90_HE10_IsoM",
                     HLT_Photon75_R9Id90_HE10_IsoM);
    if ( choose["HLT_Photon75_R9Id90_HE10_IsoM_EBOnly_CaloMJJ300_PFJetsMJJ400DEta3"] )
      input->select("Events/HLT_Photon75_R9Id90_HE10_IsoM_EBOnly_CaloMJJ300_PFJetsMJJ400DEta3",
                     HLT_Photon75_R9Id90_HE10_IsoM_EBOnly_CaloMJJ300_PFJetsMJJ400DEta3);
    if ( choose["HLT_Photon75_R9Id90_HE10_IsoM_EBOnly_CaloMJJ400_PFJetsMJJ600DEta3"] )
      input->select("Events/HLT_Photon75_R9Id90_HE10_IsoM_EBOnly_CaloMJJ400_PFJetsMJJ600DEta3",
                     HLT_Photon75_R9Id90_HE10_IsoM_EBOnly_CaloMJJ400_PFJetsMJJ600DEta3);
    if ( choose["HLT_Photon75_R9Id90_HE10_IsoM_EBOnly_PFJetsMJJ300DEta3"] )
      input->select("Events/HLT_Photon75_R9Id90_HE10_IsoM_EBOnly_PFJetsMJJ300DEta3",
                     HLT_Photon75_R9Id90_HE10_IsoM_EBOnly_PFJetsMJJ300DEta3);
    if ( choose["HLT_Photon75_R9Id90_HE10_IsoM_EBOnly_PFJetsMJJ600DEta3"] )
      input->select("Events/HLT_Photon75_R9Id90_HE10_IsoM_EBOnly_PFJetsMJJ600DEta3",
                     HLT_Photon75_R9Id90_HE10_IsoM_EBOnly_PFJetsMJJ600DEta3);
    if ( choose["HLT_Photon90"] )
      input->select("Events/HLT_Photon90", 	HLT_Photon90);
    if ( choose["HLT_Photon90_CaloIdL_PFHT700"] )
      input->select("Events/HLT_Photon90_CaloIdL_PFHT700",
                     HLT_Photon90_CaloIdL_PFHT700);
    if ( choose["HLT_Photon90_R9Id90_HE10_IsoM"] )
      input->select("Events/HLT_Photon90_R9Id90_HE10_IsoM",
                     HLT_Photon90_R9Id90_HE10_IsoM);
    if ( choose["HLT_Rsq0p35"] )
      input->select("Events/HLT_Rsq0p35", 	HLT_Rsq0p35);
    if ( choose["HLT_Rsq0p40"] )
      input->select("Events/HLT_Rsq0p40", 	HLT_Rsq0p40);
    if ( choose["HLT_RsqMR300_Rsq0p09_MR200"] )
      input->select("Events/HLT_RsqMR300_Rsq0p09_MR200",
                     HLT_RsqMR300_Rsq0p09_MR200);
    if ( choose["HLT_RsqMR300_Rsq0p09_MR200_4jet"] )
      input->select("Events/HLT_RsqMR300_Rsq0p09_MR200_4jet",
                     HLT_RsqMR300_Rsq0p09_MR200_4jet);
    if ( choose["HLT_RsqMR320_Rsq0p09_MR200"] )
      input->select("Events/HLT_RsqMR320_Rsq0p09_MR200",
                     HLT_RsqMR320_Rsq0p09_MR200);
    if ( choose["HLT_RsqMR320_Rsq0p09_MR200_4jet"] )
      input->select("Events/HLT_RsqMR320_Rsq0p09_MR200_4jet",
                     HLT_RsqMR320_Rsq0p09_MR200_4jet);
    if ( choose["HLT_SingleJet30_Mu12_SinglePFJet40"] )
      input->select("Events/HLT_SingleJet30_Mu12_SinglePFJet40",
                     HLT_SingleJet30_Mu12_SinglePFJet40);
    if ( choose["HLT_SinglePhoton10_Eta3p1ForPPRef"] )
      input->select("Events/HLT_SinglePhoton10_Eta3p1ForPPRef",
                     HLT_SinglePhoton10_Eta3p1ForPPRef);
    if ( choose["HLT_SinglePhoton20_Eta3p1ForPPRef"] )
      input->select("Events/HLT_SinglePhoton20_Eta3p1ForPPRef",
                     HLT_SinglePhoton20_Eta3p1ForPPRef);
    if ( choose["HLT_SinglePhoton30_Eta3p1ForPPRef"] )
      input->select("Events/HLT_SinglePhoton30_Eta3p1ForPPRef",
                     HLT_SinglePhoton30_Eta3p1ForPPRef);
    if ( choose["HLT_Tau3Mu_Mu7_Mu1_TkMu1_IsoTau15"] )
      input->select("Events/HLT_Tau3Mu_Mu7_Mu1_TkMu1_IsoTau15",
                     HLT_Tau3Mu_Mu7_Mu1_TkMu1_IsoTau15);
    if ( choose["HLT_Tau3Mu_Mu7_Mu1_TkMu1_IsoTau15_Charge1"] )
      input->select("Events/HLT_Tau3Mu_Mu7_Mu1_TkMu1_IsoTau15_Charge1",
                     HLT_Tau3Mu_Mu7_Mu1_TkMu1_IsoTau15_Charge1);
    if ( choose["HLT_Tau3Mu_Mu7_Mu1_TkMu1_Tau15"] )
      input->select("Events/HLT_Tau3Mu_Mu7_Mu1_TkMu1_Tau15",
                     HLT_Tau3Mu_Mu7_Mu1_TkMu1_Tau15);
    if ( choose["HLT_Tau3Mu_Mu7_Mu1_TkMu1_Tau15_Charge1"] )
      input->select("Events/HLT_Tau3Mu_Mu7_Mu1_TkMu1_Tau15_Charge1",
                     HLT_Tau3Mu_Mu7_Mu1_TkMu1_Tau15_Charge1);
    if ( choose["HLT_TkMu100"] )
      input->select("Events/HLT_TkMu100", 	HLT_TkMu100);
    if ( choose["HLT_Trimuon5_3p5_2_Upsilon_Muon"] )
      input->select("Events/HLT_Trimuon5_3p5_2_Upsilon_Muon",
                     HLT_Trimuon5_3p5_2_Upsilon_Muon);
    if ( choose["HLT_TrimuonOpen_5_3p5_2_Upsilon_Muon"] )
      input->select("Events/HLT_TrimuonOpen_5_3p5_2_Upsilon_Muon",
                     HLT_TrimuonOpen_5_3p5_2_Upsilon_Muon);
    if ( choose["HLT_TrkMu12_DoubleTrkMu5NoFiltersNoVtx"] )
      input->select("Events/HLT_TrkMu12_DoubleTrkMu5NoFiltersNoVtx",
                     HLT_TrkMu12_DoubleTrkMu5NoFiltersNoVtx);
    if ( choose["HLT_TrkMu16NoFiltersNoVtx"] )
      input->select("Events/HLT_TrkMu16NoFiltersNoVtx",
                     HLT_TrkMu16NoFiltersNoVtx);
    if ( choose["HLT_TrkMu16_DoubleTrkMu6NoFiltersNoVtx"] )
      input->select("Events/HLT_TrkMu16_DoubleTrkMu6NoFiltersNoVtx",
                     HLT_TrkMu16_DoubleTrkMu6NoFiltersNoVtx);
    if ( choose["HLT_TrkMu17_DoubleTrkMu8NoFiltersNoVtx"] )
      input->select("Events/HLT_TrkMu17_DoubleTrkMu8NoFiltersNoVtx",
                     HLT_TrkMu17_DoubleTrkMu8NoFiltersNoVtx);
    if ( choose["HLT_TrkMu6NoFiltersNoVtx"] )
      input->select("Events/HLT_TrkMu6NoFiltersNoVtx",
                     HLT_TrkMu6NoFiltersNoVtx);
    if ( choose["HLTriggerFinalPath"] )
      input->select("Events/HLTriggerFinalPath", 	HLTriggerFinalPath);
    if ( choose["HLTriggerFirstPath"] )
      input->select("Events/HLTriggerFirstPath", 	HLTriggerFirstPath);
    if ( choose["IsoTrack_charge"] )
      input->select("Events/IsoTrack_charge", 	IsoTrack_charge);
    if ( choose["IsoTrack_dxy"] )
      input->select("Events/IsoTrack_dxy", 	IsoTrack_dxy);
    if ( choose["IsoTrack_dz"] )
      input->select("Events/IsoTrack_dz", 	IsoTrack_dz);
    if ( choose["IsoTrack_eta"] )
      input->select("Events/IsoTrack_eta", 	IsoTrack_eta);
    if ( choose["IsoTrack_fromPV"] )
      input->select("Events/IsoTrack_fromPV", 	IsoTrack_fromPV);
    if ( choose["IsoTrack_isFromLostTrack"] )
      input->select("Events/IsoTrack_isFromLostTrack",
                     IsoTrack_isFromLostTrack);
    if ( choose["IsoTrack_isHighPurityTrack"] )
      input->select("Events/IsoTrack_isHighPurityTrack",
                     IsoTrack_isHighPurityTrack);
    if ( choose["IsoTrack_isPFcand"] )
      input->select("Events/IsoTrack_isPFcand", 	IsoTrack_isPFcand);
    if ( choose["IsoTrack_miniPFRelIso_all"] )
      input->select("Events/IsoTrack_miniPFRelIso_all",
                     IsoTrack_miniPFRelIso_all);
    if ( choose["IsoTrack_miniPFRelIso_chg"] )
      input->select("Events/IsoTrack_miniPFRelIso_chg",
                     IsoTrack_miniPFRelIso_chg);
    if ( choose["IsoTrack_pdgId"] )
      input->select("Events/IsoTrack_pdgId", 	IsoTrack_pdgId);
    if ( choose["IsoTrack_pfRelIso03_all"] )
      input->select("Events/IsoTrack_pfRelIso03_all",
                     IsoTrack_pfRelIso03_all);
    if ( choose["IsoTrack_pfRelIso03_chg"] )
      input->select("Events/IsoTrack_pfRelIso03_chg",
                     IsoTrack_pfRelIso03_chg);
    if ( choose["IsoTrack_phi"] )
      input->select("Events/IsoTrack_phi", 	IsoTrack_phi);
    if ( choose["IsoTrack_pt"] )
      input->select("Events/IsoTrack_pt", 	IsoTrack_pt);
    if ( choose["Jet_area"] )
      input->select("Events/Jet_area", 	Jet_area);
    if ( choose["Jet_bRegCorr"] )
      input->select("Events/Jet_bRegCorr", 	Jet_bRegCorr);
    if ( choose["Jet_bRegRes"] )
      input->select("Events/Jet_bRegRes", 	Jet_bRegRes);
    if ( choose["Jet_btagCSVV2"] )
      input->select("Events/Jet_btagCSVV2", 	Jet_btagCSVV2);
    if ( choose["Jet_btagDeepB"] )
      input->select("Events/Jet_btagDeepB", 	Jet_btagDeepB);
    if ( choose["Jet_btagDeepCvB"] )
      input->select("Events/Jet_btagDeepCvB", 	Jet_btagDeepCvB);
    if ( choose["Jet_btagDeepCvL"] )
      input->select("Events/Jet_btagDeepCvL", 	Jet_btagDeepCvL);
    if ( choose["Jet_btagDeepFlavB"] )
      input->select("Events/Jet_btagDeepFlavB", 	Jet_btagDeepFlavB);
    if ( choose["Jet_btagDeepFlavCvB"] )
      input->select("Events/Jet_btagDeepFlavCvB", 	Jet_btagDeepFlavCvB);
    if ( choose["Jet_btagDeepFlavCvL"] )
      input->select("Events/Jet_btagDeepFlavCvL", 	Jet_btagDeepFlavCvL);
    if ( choose["Jet_btagDeepFlavQG"] )
      input->select("Events/Jet_btagDeepFlavQG", 	Jet_btagDeepFlavQG);
    if ( choose["Jet_cRegCorr"] )
      input->select("Events/Jet_cRegCorr", 	Jet_cRegCorr);
    if ( choose["Jet_cRegRes"] )
      input->select("Events/Jet_cRegRes", 	Jet_cRegRes);
    if ( choose["Jet_chEmEF"] )
      input->select("Events/Jet_chEmEF", 	Jet_chEmEF);
    if ( choose["Jet_chFPV0EF"] )
      input->select("Events/Jet_chFPV0EF", 	Jet_chFPV0EF);
    if ( choose["Jet_chHEF"] )
      input->select("Events/Jet_chHEF", 	Jet_chHEF);
    if ( choose["Jet_cleanmask"] )
      input->select("Events/Jet_cleanmask", 	Jet_cleanmask);
    if ( choose["Jet_corr_JEC"] )
      input->select("Events/Jet_corr_JEC", 	Jet_corr_JEC);
    if ( choose["Jet_corr_JER"] )
      input->select("Events/Jet_corr_JER", 	Jet_corr_JER);
    if ( choose["Jet_electronIdx1"] )
      input->select("Events/Jet_electronIdx1", 	Jet_electronIdx1);
    if ( choose["Jet_electronIdx2"] )
      input->select("Events/Jet_electronIdx2", 	Jet_electronIdx2);
    if ( choose["Jet_eta"] )
      input->select("Events/Jet_eta", 	Jet_eta);
    if ( choose["Jet_genJetIdx"] )
      input->select("Events/Jet_genJetIdx", 	Jet_genJetIdx);
    if ( choose["Jet_hadronFlavour"] )
      input->select("Events/Jet_hadronFlavour", 	Jet_hadronFlavour);
    if ( choose["Jet_hfadjacentEtaStripsSize"] )
      input->select("Events/Jet_hfadjacentEtaStripsSize",
                     Jet_hfadjacentEtaStripsSize);
    if ( choose["Jet_hfcentralEtaStripSize"] )
      input->select("Events/Jet_hfcentralEtaStripSize",
                     Jet_hfcentralEtaStripSize);
    if ( choose["Jet_hfsigmaEtaEta"] )
      input->select("Events/Jet_hfsigmaEtaEta", 	Jet_hfsigmaEtaEta);
    if ( choose["Jet_hfsigmaPhiPhi"] )
      input->select("Events/Jet_hfsigmaPhiPhi", 	Jet_hfsigmaPhiPhi);
    if ( choose["Jet_jetId"] )
      input->select("Events/Jet_jetId", 	Jet_jetId);
    if ( choose["Jet_mass"] )
      input->select("Events/Jet_mass", 	Jet_mass_nom);
    if ( choose["Jet_mass_jerDown"] )
      input->select("Events/Jet_mass_jerDown", 	Jet_mass_jerDown);
    if ( choose["Jet_mass_jerUp"] )
      input->select("Events/Jet_mass_jerUp", 	Jet_mass_jerUp);
    if ( choose["Jet_mass_jesTotalDown"] )
      input->select("Events/Jet_mass_jesTotalDown", 	Jet_mass_jesTotalDown);
    if ( choose["Jet_mass_jesTotalUp"] )
      input->select("Events/Jet_mass_jesTotalUp", 	Jet_mass_jesTotalUp);
    if ( choose["Jet_mass_nom"] )
      input->select("Events/Jet_mass_nom", 	Jet_mass_nom);
    if ( choose["Jet_mass_raw"] )
      input->select("Events/Jet_mass_raw", 	Jet_mass_raw);
    if ( choose["Jet_muEF"] )
      input->select("Events/Jet_muEF", 	Jet_muEF);
    if ( choose["Jet_muonIdx1"] )
      input->select("Events/Jet_muonIdx1", 	Jet_muonIdx1);
    if ( choose["Jet_muonIdx2"] )
      input->select("Events/Jet_muonIdx2", 	Jet_muonIdx2);
    if ( choose["Jet_muonSubtrFactor"] )
      input->select("Events/Jet_muonSubtrFactor", 	Jet_muonSubtrFactor);
    if ( choose["Jet_nConstituents"] )
      input->select("Events/Jet_nConstituents", 	Jet_nConstituents);
    if ( choose["Jet_nElectrons"] )
      input->select("Events/Jet_nElectrons", 	Jet_nElectrons);
    if ( choose["Jet_nMuons"] )
      input->select("Events/Jet_nMuons", 	Jet_nMuons);
    if ( choose["Jet_neEmEF"] )
      input->select("Events/Jet_neEmEF", 	Jet_neEmEF);
    if ( choose["Jet_neHEF"] )
      input->select("Events/Jet_neHEF", 	Jet_neHEF);
    if ( choose["Jet_partonFlavour"] )
      input->select("Events/Jet_partonFlavour", 	Jet_partonFlavour);
    if ( choose["Jet_phi"] )
      input->select("Events/Jet_phi", 	Jet_phi);
    if ( choose["Jet_pt"] )
      input->select("Events/Jet_pt", 	Jet_pt_nom);
    if ( choose["Jet_pt_jerDown"] )
      input->select("Events/Jet_pt_jerDown", 	Jet_pt_jerDown);
    if ( choose["Jet_pt_jerUp"] )
      input->select("Events/Jet_pt_jerUp", 	Jet_pt_jerUp);
    if ( choose["Jet_pt_jesTotalDown"] )
      input->select("Events/Jet_pt_jesTotalDown", 	Jet_pt_jesTotalDown);
    if ( choose["Jet_pt_jesTotalUp"] )
      input->select("Events/Jet_pt_jesTotalUp", 	Jet_pt_jesTotalUp);
    if ( choose["Jet_pt_nom"] )
      input->select("Events/Jet_pt_nom", 	Jet_pt_nom);
    if ( choose["Jet_pt_raw"] )
      input->select("Events/Jet_pt_raw", 	Jet_pt_raw);
    if ( choose["Jet_puId"] )
      input->select("Events/Jet_puId", 	Jet_puId);
    if ( choose["Jet_puIdDisc"] )
      input->select("Events/Jet_puIdDisc", 	Jet_puIdDisc);
    if ( choose["Jet_qgl"] )
      input->select("Events/Jet_qgl", 	Jet_qgl);
    if ( choose["Jet_rawFactor"] )
      input->select("Events/Jet_rawFactor", 	Jet_rawFactor);
    if ( choose["L1PreFiringWeight_Dn"] )
      input->select("Events/L1PreFiringWeight_Dn", 	L1PreFiringWeight_Dn);
    if ( choose["L1PreFiringWeight_ECAL_Dn"] )
      input->select("Events/L1PreFiringWeight_ECAL_Dn",
                     L1PreFiringWeight_ECAL_Dn);
    if ( choose["L1PreFiringWeight_ECAL_Nom"] )
      input->select("Events/L1PreFiringWeight_ECAL_Nom",
                     L1PreFiringWeight_ECAL_Nom);
    if ( choose["L1PreFiringWeight_ECAL_Up"] )
      input->select("Events/L1PreFiringWeight_ECAL_Up",
                     L1PreFiringWeight_ECAL_Up);
    if ( choose["L1PreFiringWeight_Muon_Nom"] )
      input->select("Events/L1PreFiringWeight_Muon_Nom",
                     L1PreFiringWeight_Muon_Nom);
    if ( choose["L1PreFiringWeight_Muon_StatDn"] )
      input->select("Events/L1PreFiringWeight_Muon_StatDn",
                     L1PreFiringWeight_Muon_StatDn);
    if ( choose["L1PreFiringWeight_Muon_StatUp"] )
      input->select("Events/L1PreFiringWeight_Muon_StatUp",
                     L1PreFiringWeight_Muon_StatUp);
    if ( choose["L1PreFiringWeight_Muon_SystDn"] )
      input->select("Events/L1PreFiringWeight_Muon_SystDn",
                     L1PreFiringWeight_Muon_SystDn);
    if ( choose["L1PreFiringWeight_Muon_SystUp"] )
      input->select("Events/L1PreFiringWeight_Muon_SystUp",
                     L1PreFiringWeight_Muon_SystUp);
    if ( choose["L1PreFiringWeight_Nom"] )
      input->select("Events/L1PreFiringWeight_Nom", 	L1PreFiringWeight_Nom);
    if ( choose["L1PreFiringWeight_Up"] )
      input->select("Events/L1PreFiringWeight_Up", 	L1PreFiringWeight_Up);
    if ( choose["L1Reco_step"] )
      input->select("Events/L1Reco_step", 	L1Reco_step);
    if ( choose["L1simulation_step"] )
      input->select("Events/L1simulation_step", 	L1simulation_step);
    if ( choose["LHEPart_eta"] )
      input->select("Events/LHEPart_eta", 	LHEPart_eta);
    if ( choose["LHEPart_incomingpz"] )
      input->select("Events/LHEPart_incomingpz", 	LHEPart_incomingpz);
    if ( choose["LHEPart_mass"] )
      input->select("Events/LHEPart_mass", 	LHEPart_mass);
    if ( choose["LHEPart_pdgId"] )
      input->select("Events/LHEPart_pdgId", 	LHEPart_pdgId);
    if ( choose["LHEPart_phi"] )
      input->select("Events/LHEPart_phi", 	LHEPart_phi);
    if ( choose["LHEPart_pt"] )
      input->select("Events/LHEPart_pt", 	LHEPart_pt);
    if ( choose["LHEPart_spin"] )
      input->select("Events/LHEPart_spin", 	LHEPart_spin);
    if ( choose["LHEPart_status"] )
      input->select("Events/LHEPart_status", 	LHEPart_status);
    if ( choose["LHEPdfWeight"] )
      input->select("Events/LHEPdfWeight", 	LHEPdfWeight);
    if ( choose["LHEReweightingWeight"] )
      input->select("Events/LHEReweightingWeight", 	LHEReweightingWeight);
    if ( choose["LHEScaleWeight"] )
      input->select("Events/LHEScaleWeight", 	LHEScaleWeight);
    if ( choose["LHEWeight_originalXWGTUP"] )
      input->select("Events/LHEWeight_originalXWGTUP",
                     LHEWeight_originalXWGTUP);
    if ( choose["LHE_AlphaS"] )
      input->select("Events/LHE_AlphaS", 	LHE_AlphaS);
    if ( choose["LHE_HT"] )
      input->select("Events/LHE_HT", 	LHE_HT);
    if ( choose["LHE_HTIncoming"] )
      input->select("Events/LHE_HTIncoming", 	LHE_HTIncoming);
    if ( choose["LHE_Nb"] )
      input->select("Events/LHE_Nb", 	LHE_Nb);
    if ( choose["LHE_Nc"] )
      input->select("Events/LHE_Nc", 	LHE_Nc);
    if ( choose["LHE_Nglu"] )
      input->select("Events/LHE_Nglu", 	LHE_Nglu);
    if ( choose["LHE_Njets"] )
      input->select("Events/LHE_Njets", 	LHE_Njets);
    if ( choose["LHE_NpLO"] )
      input->select("Events/LHE_NpLO", 	LHE_NpLO);
    if ( choose["LHE_NpNLO"] )
      input->select("Events/LHE_NpNLO", 	LHE_NpNLO);
    if ( choose["LHE_Nuds"] )
      input->select("Events/LHE_Nuds", 	LHE_Nuds);
    if ( choose["LHE_Vpt"] )
      input->select("Events/LHE_Vpt", 	LHE_Vpt);
    if ( choose["MET_MetUnclustEnUpDeltaX"] )
      input->select("Events/MET_MetUnclustEnUpDeltaX",
                     MET_MetUnclustEnUpDeltaX);
    if ( choose["MET_MetUnclustEnUpDeltaY"] )
      input->select("Events/MET_MetUnclustEnUpDeltaY",
                     MET_MetUnclustEnUpDeltaY);
    if ( choose["MET_T1Smear_phi"] )
      input->select("Events/MET_T1Smear_phi", 	MET_T1Smear_phi);
    if ( choose["MET_T1Smear_phi_jerDown"] )
      input->select("Events/MET_T1Smear_phi_jerDown",
                     MET_T1Smear_phi_jerDown);
    if ( choose["MET_T1Smear_phi_jerUp"] )
      input->select("Events/MET_T1Smear_phi_jerUp", 	MET_T1Smear_phi_jerUp);
    if ( choose["MET_T1Smear_phi_jesTotalDown"] )
      input->select("Events/MET_T1Smear_phi_jesTotalDown",
                     MET_T1Smear_phi_jesTotalDown);
    if ( choose["MET_T1Smear_phi_jesTotalUp"] )
      input->select("Events/MET_T1Smear_phi_jesTotalUp",
                     MET_T1Smear_phi_jesTotalUp);
    if ( choose["MET_T1Smear_phi_unclustEnDown"] )
      input->select("Events/MET_T1Smear_phi_unclustEnDown",
                     MET_T1Smear_phi_unclustEnDown);
    if ( choose["MET_T1Smear_phi_unclustEnUp"] )
      input->select("Events/MET_T1Smear_phi_unclustEnUp",
                     MET_T1Smear_phi_unclustEnUp);
    if ( choose["MET_T1Smear_pt"] )
      input->select("Events/MET_T1Smear_pt", 	MET_T1Smear_pt);
    if ( choose["MET_T1Smear_pt_jerDown"] )
      input->select("Events/MET_T1Smear_pt_jerDown",
                     MET_T1Smear_pt_jerDown);
    if ( choose["MET_T1Smear_pt_jerUp"] )
      input->select("Events/MET_T1Smear_pt_jerUp", 	MET_T1Smear_pt_jerUp);
    if ( choose["MET_T1Smear_pt_jesTotalDown"] )
      input->select("Events/MET_T1Smear_pt_jesTotalDown",
                     MET_T1Smear_pt_jesTotalDown);
    if ( choose["MET_T1Smear_pt_jesTotalUp"] )
      input->select("Events/MET_T1Smear_pt_jesTotalUp",
                     MET_T1Smear_pt_jesTotalUp);
    if ( choose["MET_T1Smear_pt_unclustEnDown"] )
      input->select("Events/MET_T1Smear_pt_unclustEnDown",
                     MET_T1Smear_pt_unclustEnDown);
    if ( choose["MET_T1Smear_pt_unclustEnUp"] )
      input->select("Events/MET_T1Smear_pt_unclustEnUp",
                     MET_T1Smear_pt_unclustEnUp);
    if ( choose["MET_T1_phi"] )
      input->select("Events/MET_T1_phi", 	MET_T1_phi);
    if ( choose["MET_T1_phi_jerDown"] )
      input->select("Events/MET_T1_phi_jerDown", 	MET_T1_phi_jerDown);
    if ( choose["MET_T1_phi_jerUp"] )
      input->select("Events/MET_T1_phi_jerUp", 	MET_T1_phi_jerUp);
    if ( choose["MET_T1_phi_jesTotalDown"] )
      input->select("Events/MET_T1_phi_jesTotalDown",
                     MET_T1_phi_jesTotalDown);
    if ( choose["MET_T1_phi_jesTotalUp"] )
      input->select("Events/MET_T1_phi_jesTotalUp", 	MET_T1_phi_jesTotalUp);
    if ( choose["MET_T1_phi_unclustEnDown"] )
      input->select("Events/MET_T1_phi_unclustEnDown",
                     MET_T1_phi_unclustEnDown);
    if ( choose["MET_T1_phi_unclustEnUp"] )
      input->select("Events/MET_T1_phi_unclustEnUp",
                     MET_T1_phi_unclustEnUp);
    if ( choose["MET_T1_pt"] )
      input->select("Events/MET_T1_pt", 	MET_T1_pt);
    if ( choose["MET_T1_pt_jerDown"] )
      input->select("Events/MET_T1_pt_jerDown", 	MET_T1_pt_jerDown);
    if ( choose["MET_T1_pt_jerUp"] )
      input->select("Events/MET_T1_pt_jerUp", 	MET_T1_pt_jerUp);
    if ( choose["MET_T1_pt_jesTotalDown"] )
      input->select("Events/MET_T1_pt_jesTotalDown",
                     MET_T1_pt_jesTotalDown);
    if ( choose["MET_T1_pt_jesTotalUp"] )
      input->select("Events/MET_T1_pt_jesTotalUp", 	MET_T1_pt_jesTotalUp);
    if ( choose["MET_T1_pt_unclustEnDown"] )
      input->select("Events/MET_T1_pt_unclustEnDown",
                     MET_T1_pt_unclustEnDown);
    if ( choose["MET_T1_pt_unclustEnUp"] )
      input->select("Events/MET_T1_pt_unclustEnUp", 	MET_T1_pt_unclustEnUp);
    if ( choose["MET_covXX"] )
      input->select("Events/MET_covXX", 	MET_covXX);
    if ( choose["MET_covXY"] )
      input->select("Events/MET_covXY", 	MET_covXY);
    if ( choose["MET_covYY"] )
      input->select("Events/MET_covYY", 	MET_covYY);
    if ( choose["MET_fiducialGenPhi"] )
      input->select("Events/MET_fiducialGenPhi", 	MET_fiducialGenPhi);
    if ( choose["MET_fiducialGenPt"] )
      input->select("Events/MET_fiducialGenPt", 	MET_fiducialGenPt);
    if ( choose["MET_phi"] )
      input->select("Events/MET_phi", 	MET_phi);
    if ( choose["MET_pt"] )
      input->select("Events/MET_pt", 	MET_pt);
    if ( choose["MET_significance"] )
      input->select("Events/MET_significance", 	MET_significance);
    if ( choose["MET_sumEt"] )
      input->select("Events/MET_sumEt", 	MET_sumEt);
    if ( choose["MET_sumPtUnclustered"] )
      input->select("Events/MET_sumPtUnclustered", 	MET_sumPtUnclustered);
    if ( choose["Muon_charge"] )
      input->select("Events/Muon_charge", 	Muon_charge);
    if ( choose["Muon_cleanmask"] )
      input->select("Events/Muon_cleanmask", 	Muon_cleanmask);
    if ( choose["Muon_dxy"] )
      input->select("Events/Muon_dxy", 	Muon_dxy);
    if ( choose["Muon_dxyErr"] )
      input->select("Events/Muon_dxyErr", 	Muon_dxyErr);
    if ( choose["Muon_dxybs"] )
      input->select("Events/Muon_dxybs", 	Muon_dxybs);
    if ( choose["Muon_dz"] )
      input->select("Events/Muon_dz", 	Muon_dz);
    if ( choose["Muon_dzErr"] )
      input->select("Events/Muon_dzErr", 	Muon_dzErr);
    if ( choose["Muon_eta"] )
      input->select("Events/Muon_eta", 	Muon_eta);
    if ( choose["Muon_fsrPhotonIdx"] )
      input->select("Events/Muon_fsrPhotonIdx", 	Muon_fsrPhotonIdx);
    if ( choose["Muon_genPartFlav"] )
      input->select("Events/Muon_genPartFlav", 	Muon_genPartFlav);
    if ( choose["Muon_genPartIdx"] )
      input->select("Events/Muon_genPartIdx", 	Muon_genPartIdx);
    if ( choose["Muon_highPtId"] )
      input->select("Events/Muon_highPtId", 	Muon_highPtId);
    if ( choose["Muon_highPurity"] )
      input->select("Events/Muon_highPurity", 	Muon_highPurity);
    if ( choose["Muon_inTimeMuon"] )
      input->select("Events/Muon_inTimeMuon", 	Muon_inTimeMuon);
    if ( choose["Muon_ip3d"] )
      input->select("Events/Muon_ip3d", 	Muon_ip3d);
    if ( choose["Muon_isGlobal"] )
      input->select("Events/Muon_isGlobal", 	Muon_isGlobal);
    if ( choose["Muon_isPFcand"] )
      input->select("Events/Muon_isPFcand", 	Muon_isPFcand);
    if ( choose["Muon_isStandalone"] )
      input->select("Events/Muon_isStandalone", 	Muon_isStandalone);
    if ( choose["Muon_isTracker"] )
      input->select("Events/Muon_isTracker", 	Muon_isTracker);
    if ( choose["Muon_jetIdx"] )
      input->select("Events/Muon_jetIdx", 	Muon_jetIdx);
    if ( choose["Muon_jetNDauCharged"] )
      input->select("Events/Muon_jetNDauCharged", 	Muon_jetNDauCharged);
    if ( choose["Muon_jetPtRelv2"] )
      input->select("Events/Muon_jetPtRelv2", 	Muon_jetPtRelv2);
    if ( choose["Muon_jetRelIso"] )
      input->select("Events/Muon_jetRelIso", 	Muon_jetRelIso);
    if ( choose["Muon_looseId"] )
      input->select("Events/Muon_looseId", 	Muon_looseId);
    if ( choose["Muon_mass"] )
      input->select("Events/Muon_mass", 	Muon_mass);
    if ( choose["Muon_mediumId"] )
      input->select("Events/Muon_mediumId", 	Muon_mediumId);
    if ( choose["Muon_mediumPromptId"] )
      input->select("Events/Muon_mediumPromptId", 	Muon_mediumPromptId);
    if ( choose["Muon_miniIsoId"] )
      input->select("Events/Muon_miniIsoId", 	Muon_miniIsoId);
    if ( choose["Muon_miniPFRelIso_all"] )
      input->select("Events/Muon_miniPFRelIso_all", 	Muon_miniPFRelIso_all);
    if ( choose["Muon_miniPFRelIso_chg"] )
      input->select("Events/Muon_miniPFRelIso_chg", 	Muon_miniPFRelIso_chg);
    if ( choose["Muon_multiIsoId"] )
      input->select("Events/Muon_multiIsoId", 	Muon_multiIsoId);
    if ( choose["Muon_mvaId"] )
      input->select("Events/Muon_mvaId", 	Muon_mvaId);
    if ( choose["Muon_mvaLowPt"] )
      input->select("Events/Muon_mvaLowPt", 	Muon_mvaLowPt);
    if ( choose["Muon_mvaLowPtId"] )
      input->select("Events/Muon_mvaLowPtId", 	Muon_mvaLowPtId);
    if ( choose["Muon_mvaTTH"] )
      input->select("Events/Muon_mvaTTH", 	Muon_mvaTTH);
    if ( choose["Muon_nStations"] )
      input->select("Events/Muon_nStations", 	Muon_nStations);
    if ( choose["Muon_nTrackerLayers"] )
      input->select("Events/Muon_nTrackerLayers", 	Muon_nTrackerLayers);
    if ( choose["Muon_pdgId"] )
      input->select("Events/Muon_pdgId", 	Muon_pdgId);
    if ( choose["Muon_pfIsoId"] )
      input->select("Events/Muon_pfIsoId", 	Muon_pfIsoId);
    if ( choose["Muon_pfRelIso03_all"] )
      input->select("Events/Muon_pfRelIso03_all", 	Muon_pfRelIso03_all);
    if ( choose["Muon_pfRelIso03_chg"] )
      input->select("Events/Muon_pfRelIso03_chg", 	Muon_pfRelIso03_chg);
    if ( choose["Muon_pfRelIso04_all"] )
      input->select("Events/Muon_pfRelIso04_all", 	Muon_pfRelIso04_all);
    if ( choose["Muon_phi"] )
      input->select("Events/Muon_phi", 	Muon_phi);
    if ( choose["Muon_pt"] )
      input->select("Events/Muon_pt", 	Muon_pt);
    if ( choose["Muon_ptErr"] )
      input->select("Events/Muon_ptErr", 	Muon_ptErr);
    if ( choose["Muon_puppiIsoId"] )
      input->select("Events/Muon_puppiIsoId", 	Muon_puppiIsoId);
    if ( choose["Muon_segmentComp"] )
      input->select("Events/Muon_segmentComp", 	Muon_segmentComp);
    if ( choose["Muon_sip3d"] )
      input->select("Events/Muon_sip3d", 	Muon_sip3d);
    if ( choose["Muon_softId"] )
      input->select("Events/Muon_softId", 	Muon_softId);
    if ( choose["Muon_softMva"] )
      input->select("Events/Muon_softMva", 	Muon_softMva);
    if ( choose["Muon_softMvaId"] )
      input->select("Events/Muon_softMvaId", 	Muon_softMvaId);
    if ( choose["Muon_tightCharge"] )
      input->select("Events/Muon_tightCharge", 	Muon_tightCharge);
    if ( choose["Muon_tightId"] )
      input->select("Events/Muon_tightId", 	Muon_tightId);
    if ( choose["Muon_tkIsoId"] )
      input->select("Events/Muon_tkIsoId", 	Muon_tkIsoId);
    if ( choose["Muon_tkRelIso"] )
      input->select("Events/Muon_tkRelIso", 	Muon_tkRelIso);
    if ( choose["Muon_triggerIdLoose"] )
      input->select("Events/Muon_triggerIdLoose", 	Muon_triggerIdLoose);
    if ( choose["Muon_tunepRelPt"] )
      input->select("Events/Muon_tunepRelPt", 	Muon_tunepRelPt);
    if ( choose["OtherPV_z"] )
      input->select("Events/OtherPV_z", 	OtherPV_z);
    if ( choose["PSWeight"] )
      input->select("Events/PSWeight", 	PSWeight);
    if ( choose["PV_chi2"] )
      input->select("Events/PV_chi2", 	PV_chi2);
    if ( choose["PV_ndof"] )
      input->select("Events/PV_ndof", 	PV_ndof);
    if ( choose["PV_npvs"] )
      input->select("Events/PV_npvs", 	PV_npvs);
    if ( choose["PV_npvsGood"] )
      input->select("Events/PV_npvsGood", 	PV_npvsGood);
    if ( choose["PV_score"] )
      input->select("Events/PV_score", 	PV_score);
    if ( choose["PV_x"] )
      input->select("Events/PV_x", 	PV_x);
    if ( choose["PV_y"] )
      input->select("Events/PV_y", 	PV_y);
    if ( choose["PV_z"] )
      input->select("Events/PV_z", 	PV_z);
    if ( choose["Photon_charge"] )
      input->select("Events/Photon_charge", 	Photon_charge);
    if ( choose["Photon_cleanmask"] )
      input->select("Events/Photon_cleanmask", 	Photon_cleanmask);
    if ( choose["Photon_cutBased"] )
      input->select("Events/Photon_cutBased", 	Photon_cutBased);
    if ( choose["Photon_cutBased_Fall17V1Bitmap"] )
      input->select("Events/Photon_cutBased_Fall17V1Bitmap",
                     Photon_cutBased_Fall17V1Bitmap);
    if ( choose["Photon_dEscaleDown"] )
      input->select("Events/Photon_dEscaleDown", 	Photon_dEscaleDown);
    if ( choose["Photon_dEscaleUp"] )
      input->select("Events/Photon_dEscaleUp", 	Photon_dEscaleUp);
    if ( choose["Photon_dEsigmaDown"] )
      input->select("Events/Photon_dEsigmaDown", 	Photon_dEsigmaDown);
    if ( choose["Photon_dEsigmaUp"] )
      input->select("Events/Photon_dEsigmaUp", 	Photon_dEsigmaUp);
    if ( choose["Photon_eCorr"] )
      input->select("Events/Photon_eCorr", 	Photon_eCorr);
    if ( choose["Photon_electronIdx"] )
      input->select("Events/Photon_electronIdx", 	Photon_electronIdx);
    if ( choose["Photon_electronVeto"] )
      input->select("Events/Photon_electronVeto", 	Photon_electronVeto);
    if ( choose["Photon_energyErr"] )
      input->select("Events/Photon_energyErr", 	Photon_energyErr);
    if ( choose["Photon_eta"] )
      input->select("Events/Photon_eta", 	Photon_eta);
    if ( choose["Photon_genPartFlav"] )
      input->select("Events/Photon_genPartFlav", 	Photon_genPartFlav);
    if ( choose["Photon_genPartIdx"] )
      input->select("Events/Photon_genPartIdx", 	Photon_genPartIdx);
    if ( choose["Photon_hoe"] )
      input->select("Events/Photon_hoe", 	Photon_hoe);
    if ( choose["Photon_isScEtaEB"] )
      input->select("Events/Photon_isScEtaEB", 	Photon_isScEtaEB);
    if ( choose["Photon_isScEtaEE"] )
      input->select("Events/Photon_isScEtaEE", 	Photon_isScEtaEE);
    if ( choose["Photon_jetIdx"] )
      input->select("Events/Photon_jetIdx", 	Photon_jetIdx);
    if ( choose["Photon_mass"] )
      input->select("Events/Photon_mass", 	Photon_mass);
    if ( choose["Photon_mvaID"] )
      input->select("Events/Photon_mvaID", 	Photon_mvaID);
    if ( choose["Photon_mvaID_Fall17V1p1"] )
      input->select("Events/Photon_mvaID_Fall17V1p1",
                     Photon_mvaID_Fall17V1p1);
    if ( choose["Photon_mvaID_WP80"] )
      input->select("Events/Photon_mvaID_WP80", 	Photon_mvaID_WP80);
    if ( choose["Photon_mvaID_WP90"] )
      input->select("Events/Photon_mvaID_WP90", 	Photon_mvaID_WP90);
    if ( choose["Photon_pdgId"] )
      input->select("Events/Photon_pdgId", 	Photon_pdgId);
    if ( choose["Photon_pfRelIso03_all"] )
      input->select("Events/Photon_pfRelIso03_all", 	Photon_pfRelIso03_all);
    if ( choose["Photon_pfRelIso03_chg"] )
      input->select("Events/Photon_pfRelIso03_chg", 	Photon_pfRelIso03_chg);
    if ( choose["Photon_phi"] )
      input->select("Events/Photon_phi", 	Photon_phi);
    if ( choose["Photon_pixelSeed"] )
      input->select("Events/Photon_pixelSeed", 	Photon_pixelSeed);
    if ( choose["Photon_pt"] )
      input->select("Events/Photon_pt", 	Photon_pt);
    if ( choose["Photon_r9"] )
      input->select("Events/Photon_r9", 	Photon_r9);
    if ( choose["Photon_seedGain"] )
      input->select("Events/Photon_seedGain", 	Photon_seedGain);
    if ( choose["Photon_sieie"] )
      input->select("Events/Photon_sieie", 	Photon_sieie);
    if ( choose["Photon_vidNestedWPBitmap"] )
      input->select("Events/Photon_vidNestedWPBitmap",
                     Photon_vidNestedWPBitmap);
    if ( choose["Pileup_gpudensity"] )
      input->select("Events/Pileup_gpudensity", 	Pileup_gpudensity);
    if ( choose["Pileup_nPU"] )
      input->select("Events/Pileup_nPU", 	Pileup_nPU);
    if ( choose["Pileup_nTrueInt"] )
      input->select("Events/Pileup_nTrueInt", 	Pileup_nTrueInt);
    if ( choose["Pileup_pudensity"] )
      input->select("Events/Pileup_pudensity", 	Pileup_pudensity);
    if ( choose["Pileup_sumEOOT"] )
      input->select("Events/Pileup_sumEOOT", 	Pileup_sumEOOT);
    if ( choose["Pileup_sumLOOT"] )
      input->select("Events/Pileup_sumLOOT", 	Pileup_sumLOOT);
    if ( choose["PuppiMET_phi"] )
      input->select("Events/PuppiMET_phi", 	PuppiMET_phi);
    if ( choose["PuppiMET_phiJERDown"] )
      input->select("Events/PuppiMET_phiJERDown", 	PuppiMET_phiJERDown);
    if ( choose["PuppiMET_phiJERUp"] )
      input->select("Events/PuppiMET_phiJERUp", 	PuppiMET_phiJERUp);
    if ( choose["PuppiMET_phiJESDown"] )
      input->select("Events/PuppiMET_phiJESDown", 	PuppiMET_phiJESDown);
    if ( choose["PuppiMET_phiJESUp"] )
      input->select("Events/PuppiMET_phiJESUp", 	PuppiMET_phiJESUp);
    if ( choose["PuppiMET_phiUnclusteredDown"] )
      input->select("Events/PuppiMET_phiUnclusteredDown",
                     PuppiMET_phiUnclusteredDown);
    if ( choose["PuppiMET_phiUnclusteredUp"] )
      input->select("Events/PuppiMET_phiUnclusteredUp",
                     PuppiMET_phiUnclusteredUp);
    if ( choose["PuppiMET_pt"] )
      input->select("Events/PuppiMET_pt", 	PuppiMET_pt);
    if ( choose["PuppiMET_ptJERDown"] )
      input->select("Events/PuppiMET_ptJERDown", 	PuppiMET_ptJERDown);
    if ( choose["PuppiMET_ptJERUp"] )
      input->select("Events/PuppiMET_ptJERUp", 	PuppiMET_ptJERUp);
    if ( choose["PuppiMET_ptJESDown"] )
      input->select("Events/PuppiMET_ptJESDown", 	PuppiMET_ptJESDown);
    if ( choose["PuppiMET_ptJESUp"] )
      input->select("Events/PuppiMET_ptJESUp", 	PuppiMET_ptJESUp);
    if ( choose["PuppiMET_ptUnclusteredDown"] )
      input->select("Events/PuppiMET_ptUnclusteredDown",
                     PuppiMET_ptUnclusteredDown);
    if ( choose["PuppiMET_ptUnclusteredUp"] )
      input->select("Events/PuppiMET_ptUnclusteredUp",
                     PuppiMET_ptUnclusteredUp);
    if ( choose["PuppiMET_sumEt"] )
      input->select("Events/PuppiMET_sumEt", 	PuppiMET_sumEt);
    if ( choose["RawMET_phi"] )
      input->select("Events/RawMET_phi", 	RawMET_phi);
    if ( choose["RawMET_pt"] )
      input->select("Events/RawMET_pt", 	RawMET_pt);
    if ( choose["RawMET_sumEt"] )
      input->select("Events/RawMET_sumEt", 	RawMET_sumEt);
    if ( choose["RawPuppiMET_phi"] )
      input->select("Events/RawPuppiMET_phi", 	RawPuppiMET_phi);
    if ( choose["RawPuppiMET_pt"] )
      input->select("Events/RawPuppiMET_pt", 	RawPuppiMET_pt);
    if ( choose["RawPuppiMET_sumEt"] )
      input->select("Events/RawPuppiMET_sumEt", 	RawPuppiMET_sumEt);
    if ( choose["SubGenJetAK8_eta"] )
      input->select("Events/SubGenJetAK8_eta", 	SubGenJetAK8_eta);
    if ( choose["SubGenJetAK8_mass"] )
      input->select("Events/SubGenJetAK8_mass", 	SubGenJetAK8_mass);
    if ( choose["SubGenJetAK8_phi"] )
      input->select("Events/SubGenJetAK8_phi", 	SubGenJetAK8_phi);
    if ( choose["SubGenJetAK8_pt"] )
      input->select("Events/SubGenJetAK8_pt", 	SubGenJetAK8_pt);
    if ( choose["SubJet_btagCSVV2"] )
      input->select("Events/SubJet_btagCSVV2", 	SubJet_btagCSVV2);
    if ( choose["SubJet_btagDeepB"] )
      input->select("Events/SubJet_btagDeepB", 	SubJet_btagDeepB);
    if ( choose["SubJet_eta"] )
      input->select("Events/SubJet_eta", 	SubJet_eta);
    if ( choose["SubJet_hadronFlavour"] )
      input->select("Events/SubJet_hadronFlavour", 	SubJet_hadronFlavour);
    if ( choose["SubJet_mass"] )
      input->select("Events/SubJet_mass", 	SubJet_mass);
    if ( choose["SubJet_n2b1"] )
      input->select("Events/SubJet_n2b1", 	SubJet_n2b1);
    if ( choose["SubJet_n3b1"] )
      input->select("Events/SubJet_n3b1", 	SubJet_n3b1);
    if ( choose["SubJet_nBHadrons"] )
      input->select("Events/SubJet_nBHadrons", 	SubJet_nBHadrons);
    if ( choose["SubJet_nCHadrons"] )
      input->select("Events/SubJet_nCHadrons", 	SubJet_nCHadrons);
    if ( choose["SubJet_phi"] )
      input->select("Events/SubJet_phi", 	SubJet_phi);
    if ( choose["SubJet_pt"] )
      input->select("Events/SubJet_pt", 	SubJet_pt);
    if ( choose["SubJet_rawFactor"] )
      input->select("Events/SubJet_rawFactor", 	SubJet_rawFactor);
    if ( choose["SubJet_tau1"] )
      input->select("Events/SubJet_tau1", 	SubJet_tau1);
    if ( choose["SubJet_tau2"] )
      input->select("Events/SubJet_tau2", 	SubJet_tau2);
    if ( choose["SubJet_tau3"] )
      input->select("Events/SubJet_tau3", 	SubJet_tau3);
    if ( choose["SubJet_tau4"] )
      input->select("Events/SubJet_tau4", 	SubJet_tau4);
    if ( choose["Tau_charge"] )
      input->select("Events/Tau_charge", 	Tau_charge);
    if ( choose["Tau_chargedIso"] )
      input->select("Events/Tau_chargedIso", 	Tau_chargedIso);
    if ( choose["Tau_cleanmask"] )
      input->select("Events/Tau_cleanmask", 	Tau_cleanmask);
    if ( choose["Tau_decayMode"] )
      input->select("Events/Tau_decayMode", 	Tau_decayMode);
    if ( choose["Tau_dxy"] )
      input->select("Events/Tau_dxy", 	Tau_dxy);
    if ( choose["Tau_dz"] )
      input->select("Events/Tau_dz", 	Tau_dz);
    if ( choose["Tau_eta"] )
      input->select("Events/Tau_eta", 	Tau_eta);
    if ( choose["Tau_genPartFlav"] )
      input->select("Events/Tau_genPartFlav", 	Tau_genPartFlav);
    if ( choose["Tau_genPartIdx"] )
      input->select("Events/Tau_genPartIdx", 	Tau_genPartIdx);
    if ( choose["Tau_idAntiEleDeadECal"] )
      input->select("Events/Tau_idAntiEleDeadECal", 	Tau_idAntiEleDeadECal);
    if ( choose["Tau_idAntiMu"] )
      input->select("Events/Tau_idAntiMu", 	Tau_idAntiMu);
    if ( choose["Tau_idDecayModeOldDMs"] )
      input->select("Events/Tau_idDecayModeOldDMs", 	Tau_idDecayModeOldDMs);
    if ( choose["Tau_idDeepTau2017v2p1VSe"] )
      input->select("Events/Tau_idDeepTau2017v2p1VSe",
                     Tau_idDeepTau2017v2p1VSe);
    if ( choose["Tau_idDeepTau2017v2p1VSjet"] )
      input->select("Events/Tau_idDeepTau2017v2p1VSjet",
                     Tau_idDeepTau2017v2p1VSjet);
    if ( choose["Tau_idDeepTau2017v2p1VSmu"] )
      input->select("Events/Tau_idDeepTau2017v2p1VSmu",
                     Tau_idDeepTau2017v2p1VSmu);
    if ( choose["Tau_jetIdx"] )
      input->select("Events/Tau_jetIdx", 	Tau_jetIdx);
    if ( choose["Tau_leadTkDeltaEta"] )
      input->select("Events/Tau_leadTkDeltaEta", 	Tau_leadTkDeltaEta);
    if ( choose["Tau_leadTkDeltaPhi"] )
      input->select("Events/Tau_leadTkDeltaPhi", 	Tau_leadTkDeltaPhi);
    if ( choose["Tau_leadTkPtOverTauPt"] )
      input->select("Events/Tau_leadTkPtOverTauPt", 	Tau_leadTkPtOverTauPt);
    if ( choose["Tau_mass"] )
      input->select("Events/Tau_mass", 	Tau_mass);
    if ( choose["Tau_neutralIso"] )
      input->select("Events/Tau_neutralIso", 	Tau_neutralIso);
    if ( choose["Tau_phi"] )
      input->select("Events/Tau_phi", 	Tau_phi);
    if ( choose["Tau_photonsOutsideSignalCone"] )
      input->select("Events/Tau_photonsOutsideSignalCone",
                     Tau_photonsOutsideSignalCone);
    if ( choose["Tau_pt"] )
      input->select("Events/Tau_pt", 	Tau_pt);
    if ( choose["Tau_puCorr"] )
      input->select("Events/Tau_puCorr", 	Tau_puCorr);
    if ( choose["Tau_rawDeepTau2017v2p1VSe"] )
      input->select("Events/Tau_rawDeepTau2017v2p1VSe",
                     Tau_rawDeepTau2017v2p1VSe);
    if ( choose["Tau_rawDeepTau2017v2p1VSjet"] )
      input->select("Events/Tau_rawDeepTau2017v2p1VSjet",
                     Tau_rawDeepTau2017v2p1VSjet);
    if ( choose["Tau_rawDeepTau2017v2p1VSmu"] )
      input->select("Events/Tau_rawDeepTau2017v2p1VSmu",
                     Tau_rawDeepTau2017v2p1VSmu);
    if ( choose["Tau_rawIso"] )
      input->select("Events/Tau_rawIso", 	Tau_rawIso);
    if ( choose["Tau_rawIsodR03"] )
      input->select("Events/Tau_rawIsodR03", 	Tau_rawIsodR03);
    if ( choose["TkMET_phi"] )
      input->select("Events/TkMET_phi", 	TkMET_phi);
    if ( choose["TkMET_pt"] )
      input->select("Events/TkMET_pt", 	TkMET_pt);
    if ( choose["TkMET_sumEt"] )
      input->select("Events/TkMET_sumEt", 	TkMET_sumEt);
    if ( choose["TrigObj_eta"] )
      input->select("Events/TrigObj_eta", 	TrigObj_eta);
    if ( choose["TrigObj_filterBits"] )
      input->select("Events/TrigObj_filterBits", 	TrigObj_filterBits);
    if ( choose["TrigObj_id"] )
      input->select("Events/TrigObj_id", 	TrigObj_id);
    if ( choose["TrigObj_l1charge"] )
      input->select("Events/TrigObj_l1charge", 	TrigObj_l1charge);
    if ( choose["TrigObj_l1iso"] )
      input->select("Events/TrigObj_l1iso", 	TrigObj_l1iso);
    if ( choose["TrigObj_l1pt"] )
      input->select("Events/TrigObj_l1pt", 	TrigObj_l1pt);
    if ( choose["TrigObj_l1pt_2"] )
      input->select("Events/TrigObj_l1pt_2", 	TrigObj_l1pt_2);
    if ( choose["TrigObj_l2pt"] )
      input->select("Events/TrigObj_l2pt", 	TrigObj_l2pt);
    if ( choose["TrigObj_phi"] )
      input->select("Events/TrigObj_phi", 	TrigObj_phi);
    if ( choose["TrigObj_pt"] )
      input->select("Events/TrigObj_pt", 	TrigObj_pt);
    if ( choose["boostedTau_charge"] )
      input->select("Events/boostedTau_charge", 	boostedTau_charge);
    if ( choose["boostedTau_chargedIso"] )
      input->select("Events/boostedTau_chargedIso", 	boostedTau_chargedIso);
    if ( choose["boostedTau_decayMode"] )
      input->select("Events/boostedTau_decayMode", 	boostedTau_decayMode);
    if ( choose["boostedTau_eta"] )
      input->select("Events/boostedTau_eta", 	boostedTau_eta);
    if ( choose["boostedTau_genPartFlav"] )
      input->select("Events/boostedTau_genPartFlav",
                     boostedTau_genPartFlav);
    if ( choose["boostedTau_genPartIdx"] )
      input->select("Events/boostedTau_genPartIdx", 	boostedTau_genPartIdx);
    if ( choose["boostedTau_idAntiEle2018"] )
      input->select("Events/boostedTau_idAntiEle2018",
                     boostedTau_idAntiEle2018);
    if ( choose["boostedTau_idAntiMu"] )
      input->select("Events/boostedTau_idAntiMu", 	boostedTau_idAntiMu);
    if ( choose["boostedTau_idMVAnewDM2017v2"] )
      input->select("Events/boostedTau_idMVAnewDM2017v2",
                     boostedTau_idMVAnewDM2017v2);
    if ( choose["boostedTau_idMVAoldDM2017v2"] )
      input->select("Events/boostedTau_idMVAoldDM2017v2",
                     boostedTau_idMVAoldDM2017v2);
    if ( choose["boostedTau_idMVAoldDMdR032017v2"] )
      input->select("Events/boostedTau_idMVAoldDMdR032017v2",
                     boostedTau_idMVAoldDMdR032017v2);
    if ( choose["boostedTau_jetIdx"] )
      input->select("Events/boostedTau_jetIdx", 	boostedTau_jetIdx);
    if ( choose["boostedTau_leadTkDeltaEta"] )
      input->select("Events/boostedTau_leadTkDeltaEta",
                     boostedTau_leadTkDeltaEta);
    if ( choose["boostedTau_leadTkDeltaPhi"] )
      input->select("Events/boostedTau_leadTkDeltaPhi",
                     boostedTau_leadTkDeltaPhi);
    if ( choose["boostedTau_leadTkPtOverTauPt"] )
      input->select("Events/boostedTau_leadTkPtOverTauPt",
                     boostedTau_leadTkPtOverTauPt);
    if ( choose["boostedTau_mass"] )
      input->select("Events/boostedTau_mass", 	boostedTau_mass);
    if ( choose["boostedTau_neutralIso"] )
      input->select("Events/boostedTau_neutralIso", 	boostedTau_neutralIso);
    if ( choose["boostedTau_phi"] )
      input->select("Events/boostedTau_phi", 	boostedTau_phi);
    if ( choose["boostedTau_photonsOutsideSignalCone"] )
      input->select("Events/boostedTau_photonsOutsideSignalCone",
                     boostedTau_photonsOutsideSignalCone);
    if ( choose["boostedTau_pt"] )
      input->select("Events/boostedTau_pt", 	boostedTau_pt);
    if ( choose["boostedTau_puCorr"] )
      input->select("Events/boostedTau_puCorr", 	boostedTau_puCorr);
    if ( choose["boostedTau_rawAntiEle2018"] )
      input->select("Events/boostedTau_rawAntiEle2018",
                     boostedTau_rawAntiEle2018);
    if ( choose["boostedTau_rawAntiEleCat2018"] )
      input->select("Events/boostedTau_rawAntiEleCat2018",
                     boostedTau_rawAntiEleCat2018);
    if ( choose["boostedTau_rawIso"] )
      input->select("Events/boostedTau_rawIso", 	boostedTau_rawIso);
    if ( choose["boostedTau_rawIsodR03"] )
      input->select("Events/boostedTau_rawIsodR03", 	boostedTau_rawIsodR03);
    if ( choose["boostedTau_rawMVAnewDM2017v2"] )
      input->select("Events/boostedTau_rawMVAnewDM2017v2",
                     boostedTau_rawMVAnewDM2017v2);
    if ( choose["boostedTau_rawMVAoldDM2017v2"] )
      input->select("Events/boostedTau_rawMVAoldDM2017v2",
                     boostedTau_rawMVAoldDM2017v2);
    if ( choose["boostedTau_rawMVAoldDMdR032017v2"] )
      input->select("Events/boostedTau_rawMVAoldDMdR032017v2",
                     boostedTau_rawMVAoldDMdR032017v2);
    if ( choose["btagWeight_CSVV2"] )
      input->select("Events/btagWeight_CSVV2", 	btagWeight_CSVV2);
    if ( choose["btagWeight_DeepCSVB"] )
      input->select("Events/btagWeight_DeepCSVB", 	btagWeight_DeepCSVB);
    if ( choose["event"] )
      input->select("Events/event", 	event);
    if ( choose["eventWeight"] )
      input->select("Events/eventWeight", 	eventWeight);
    if ( choose["fixedGridRhoFastjetAll"] )
      input->select("Events/fixedGridRhoFastjetAll",
                     fixedGridRhoFastjetAll);
    if ( choose["fixedGridRhoFastjetCentral"] )
      input->select("Events/fixedGridRhoFastjetCentral",
                     fixedGridRhoFastjetCentral);
    if ( choose["fixedGridRhoFastjetCentralCalo"] )
      input->select("Events/fixedGridRhoFastjetCentralCalo",
                     fixedGridRhoFastjetCentralCalo);
    if ( choose["fixedGridRhoFastjetCentralChargedPileUp"] )
      input->select("Events/fixedGridRhoFastjetCentralChargedPileUp",
                     fixedGridRhoFastjetCentralChargedPileUp);
    if ( choose["fixedGridRhoFastjetCentralNeutral"] )
      input->select("Events/fixedGridRhoFastjetCentralNeutral",
                     fixedGridRhoFastjetCentralNeutral);
    if ( choose["genTtbarId"] )
      input->select("Events/genTtbarId", 	genTtbarId);
    if ( choose["genWeight"] )
      input->select("Events/genWeight", 	genWeight);
    if ( choose["luminosityBlock"] )
      input->select("Events/luminosityBlock", 	luminosityBlock);
    if ( choose["puWeight"] )
      input->select("Events/puWeight", 	puWeight);
    if ( choose["puWeightDown"] )
      input->select("Events/puWeightDown", 	puWeightDown);
    if ( choose["puWeightUp"] )
      input->select("Events/puWeightUp", 	puWeightUp);
    if ( choose["run"] )
      input->select("Events/run", 	run);

  }

  // A write-only buffer
  eventBuffer(otreestream& stream)
  : input(0),
    output(&stream)
  {
    initBuffers();

    output->add("nTau", 	nTau);
    output->add("nMuon", 	nMuon);
    output->add("nLHEScaleWeight", 	nLHEScaleWeight);
    output->add("nFatJet", 	nFatJet);
    output->add("nLHEPart", 	nLHEPart);
    output->add("nGenPart", 	nGenPart);
    output->add("nPSWeight", 	nPSWeight);
    output->add("nSubJet", 	nSubJet);
    output->add("nCorrT1METJet", 	nCorrT1METJet);
    output->add("nJet", 	nJet);
    output->add("nGenJet", 	nGenJet);
    output->add("nOtherPV", 	nOtherPV);
    output->add("nLHEReweightingWeight", 	nLHEReweightingWeight);
    output->add("nboostedTau", 	nboostedTau);
    output->add("nLHEPdfWeight", 	nLHEPdfWeight);
    output->add("nTrigObj", 	nTrigObj);
    output->add("nFsrPhoton", 	nFsrPhoton);
    output->add("nElectron", 	nElectron);
    output->add("nSubGenJetAK8", 	nSubGenJetAK8);
    output->add("nGenIsolatedPhoton", 	nGenIsolatedPhoton);
    output->add("nIsoTrack", 	nIsoTrack);
    output->add("nGenJetAK8", 	nGenJetAK8);
    output->add("nPhoton", 	nPhoton);
  
    output->add("Events/CaloMET_phi", 	CaloMET_phi);
    output->add("Events/CaloMET_pt", 	CaloMET_pt);
    output->add("Events/CaloMET_sumEt", 	CaloMET_sumEt);
    output->add("Events/ChsMET_phi", 	ChsMET_phi);
    output->add("Events/ChsMET_pt", 	ChsMET_pt);
    output->add("Events/ChsMET_sumEt", 	ChsMET_sumEt);
    output->add("Events/CorrT1METJet_area[nCorrT1METJet]",
                 CorrT1METJet_area);
    output->add("Events/CorrT1METJet_eta[nCorrT1METJet]",
                 CorrT1METJet_eta);
    output->add("Events/CorrT1METJet_muonSubtrFactor[nCorrT1METJet]",
                 CorrT1METJet_muonSubtrFactor);
    output->add("Events/CorrT1METJet_phi[nCorrT1METJet]",
                 CorrT1METJet_phi);
    output->add("Events/CorrT1METJet_rawPt[nCorrT1METJet]",
                 CorrT1METJet_rawPt);
    output->add("Events/DeepMETResolutionTune_phi",
                 DeepMETResolutionTune_phi);
    output->add("Events/DeepMETResolutionTune_pt",
                 DeepMETResolutionTune_pt);
    output->add("Events/DeepMETResponseTune_phi", 	DeepMETResponseTune_phi);
    output->add("Events/DeepMETResponseTune_pt", 	DeepMETResponseTune_pt);
    output->add("Events/Electron_charge[nElectron]", 	Electron_charge);
    output->add("Events/Electron_cleanmask[nElectron]",
                 Electron_cleanmask);
    output->add("Events/Electron_convVeto[nElectron]", 	Electron_convVeto);
    output->add("Events/Electron_cutBased[nElectron]", 	Electron_cutBased);
    output->add("Events/Electron_cutBased_HEEP[nElectron]",
                 Electron_cutBased_HEEP);
    output->add("Events/Electron_dEscaleDown[nElectron]",
                 Electron_dEscaleDown);
    output->add("Events/Electron_dEscaleUp[nElectron]",
                 Electron_dEscaleUp);
    output->add("Events/Electron_dEsigmaDown[nElectron]",
                 Electron_dEsigmaDown);
    output->add("Events/Electron_dEsigmaUp[nElectron]",
                 Electron_dEsigmaUp);
    output->add("Events/Electron_deltaEtaSC[nElectron]",
                 Electron_deltaEtaSC);
    output->add("Events/Electron_dr03EcalRecHitSumEt[nElectron]",
                 Electron_dr03EcalRecHitSumEt);
    output->add("Events/Electron_dr03HcalDepth1TowerSumEt[nElectron]",
                 Electron_dr03HcalDepth1TowerSumEt);
    output->add("Events/Electron_dr03TkSumPt[nElectron]",
                 Electron_dr03TkSumPt);
    output->add("Events/Electron_dr03TkSumPtHEEP[nElectron]",
                 Electron_dr03TkSumPtHEEP);
    output->add("Events/Electron_dxy[nElectron]", 	Electron_dxy);
    output->add("Events/Electron_dxyErr[nElectron]", 	Electron_dxyErr);
    output->add("Events/Electron_dz[nElectron]", 	Electron_dz);
    output->add("Events/Electron_dzErr[nElectron]", 	Electron_dzErr);
    output->add("Events/Electron_eCorr[nElectron]", 	Electron_eCorr);
    output->add("Events/Electron_eInvMinusPInv[nElectron]",
                 Electron_eInvMinusPInv);
    output->add("Events/Electron_energyErr[nElectron]",
                 Electron_energyErr);
    output->add("Events/Electron_eta[nElectron]", 	Electron_eta);
    output->add("Events/Electron_genPartFlav[nElectron]",
                 Electron_genPartFlav);
    output->add("Events/Electron_genPartIdx[nElectron]",
                 Electron_genPartIdx);
    output->add("Events/Electron_hoe[nElectron]", 	Electron_hoe);
    output->add("Events/Electron_ip3d[nElectron]", 	Electron_ip3d);
    output->add("Events/Electron_isPFcand[nElectron]", 	Electron_isPFcand);
    output->add("Events/Electron_jetIdx[nElectron]", 	Electron_jetIdx);
    output->add("Events/Electron_jetNDauCharged[nElectron]",
                 Electron_jetNDauCharged);
    output->add("Events/Electron_jetPtRelv2[nElectron]",
                 Electron_jetPtRelv2);
    output->add("Events/Electron_jetRelIso[nElectron]",
                 Electron_jetRelIso);
    output->add("Events/Electron_lostHits[nElectron]", 	Electron_lostHits);
    output->add("Events/Electron_mass[nElectron]", 	Electron_mass);
    output->add("Events/Electron_miniPFRelIso_all[nElectron]",
                 Electron_miniPFRelIso_all);
    output->add("Events/Electron_miniPFRelIso_chg[nElectron]",
                 Electron_miniPFRelIso_chg);
    output->add("Events/Electron_mvaFall17V2Iso[nElectron]",
                 Electron_mvaFall17V2Iso);
    output->add("Events/Electron_mvaFall17V2Iso_WP80[nElectron]",
                 Electron_mvaFall17V2Iso_WP80);
    output->add("Events/Electron_mvaFall17V2Iso_WP90[nElectron]",
                 Electron_mvaFall17V2Iso_WP90);
    output->add("Events/Electron_mvaFall17V2Iso_WPL[nElectron]",
                 Electron_mvaFall17V2Iso_WPL);
    output->add("Events/Electron_mvaFall17V2noIso[nElectron]",
                 Electron_mvaFall17V2noIso);
    output->add("Events/Electron_mvaFall17V2noIso_WP80[nElectron]",
                 Electron_mvaFall17V2noIso_WP80);
    output->add("Events/Electron_mvaFall17V2noIso_WP90[nElectron]",
                 Electron_mvaFall17V2noIso_WP90);
    output->add("Events/Electron_mvaFall17V2noIso_WPL[nElectron]",
                 Electron_mvaFall17V2noIso_WPL);
    output->add("Events/Electron_mvaTTH[nElectron]", 	Electron_mvaTTH);
    output->add("Events/Electron_pdgId[nElectron]", 	Electron_pdgId);
    output->add("Events/Electron_pfRelIso03_all[nElectron]",
                 Electron_pfRelIso03_all);
    output->add("Events/Electron_pfRelIso03_chg[nElectron]",
                 Electron_pfRelIso03_chg);
    output->add("Events/Electron_phi[nElectron]", 	Electron_phi);
    output->add("Events/Electron_photonIdx[nElectron]",
                 Electron_photonIdx);
    output->add("Events/Electron_pt[nElectron]", 	Electron_pt);
    output->add("Events/Electron_r9[nElectron]", 	Electron_r9);
    output->add("Events/Electron_scEtOverPt[nElectron]",
                 Electron_scEtOverPt);
    output->add("Events/Electron_seedGain[nElectron]", 	Electron_seedGain);
    output->add("Events/Electron_sieie[nElectron]", 	Electron_sieie);
    output->add("Events/Electron_sip3d[nElectron]", 	Electron_sip3d);
    output->add("Events/Electron_tightCharge[nElectron]",
                 Electron_tightCharge);
    output->add("Events/Electron_vidNestedWPBitmap[nElectron]",
                 Electron_vidNestedWPBitmap);
    output->add("Events/Electron_vidNestedWPBitmapHEEP[nElectron]",
                 Electron_vidNestedWPBitmapHEEP);
    output->add("Events/FatJet_area[nFatJet]", 	FatJet_area);
    output->add("Events/FatJet_btagCSVV2[nFatJet]", 	FatJet_btagCSVV2);
    output->add("Events/FatJet_btagDDBvLV2[nFatJet]", 	FatJet_btagDDBvLV2);
    output->add("Events/FatJet_btagDDCvBV2[nFatJet]", 	FatJet_btagDDCvBV2);
    output->add("Events/FatJet_btagDDCvLV2[nFatJet]", 	FatJet_btagDDCvLV2);
    output->add("Events/FatJet_btagDeepB[nFatJet]", 	FatJet_btagDeepB);
    output->add("Events/FatJet_btagHbb[nFatJet]", 	FatJet_btagHbb);
    output->add("Events/FatJet_corr_JEC[nFatJet]", 	FatJet_corr_JEC);
    output->add("Events/FatJet_corr_JER[nFatJet]", 	FatJet_corr_JER);
    output->add("Events/FatJet_corr_JMR[nFatJet]", 	FatJet_corr_JMR);
    output->add("Events/FatJet_corr_JMS[nFatJet]", 	FatJet_corr_JMS);
    output->add("Events/FatJet_deepTagMD_H4qvsQCD[nFatJet]",
                 FatJet_deepTagMD_H4qvsQCD);
    output->add("Events/FatJet_deepTagMD_HbbvsQCD[nFatJet]",
                 FatJet_deepTagMD_HbbvsQCD);
    output->add("Events/FatJet_deepTagMD_TvsQCD[nFatJet]",
                 FatJet_deepTagMD_TvsQCD);
    output->add("Events/FatJet_deepTagMD_WvsQCD[nFatJet]",
                 FatJet_deepTagMD_WvsQCD);
    output->add("Events/FatJet_deepTagMD_ZHbbvsQCD[nFatJet]",
                 FatJet_deepTagMD_ZHbbvsQCD);
    output->add("Events/FatJet_deepTagMD_ZHccvsQCD[nFatJet]",
                 FatJet_deepTagMD_ZHccvsQCD);
    output->add("Events/FatJet_deepTagMD_ZbbvsQCD[nFatJet]",
                 FatJet_deepTagMD_ZbbvsQCD);
    output->add("Events/FatJet_deepTagMD_ZvsQCD[nFatJet]",
                 FatJet_deepTagMD_ZvsQCD);
    output->add("Events/FatJet_deepTagMD_bbvsLight[nFatJet]",
                 FatJet_deepTagMD_bbvsLight);
    output->add("Events/FatJet_deepTagMD_ccvsLight[nFatJet]",
                 FatJet_deepTagMD_ccvsLight);
    output->add("Events/FatJet_deepTag_H[nFatJet]", 	FatJet_deepTag_H);
    output->add("Events/FatJet_deepTag_QCD[nFatJet]", 	FatJet_deepTag_QCD);
    output->add("Events/FatJet_deepTag_QCDothers[nFatJet]",
                 FatJet_deepTag_QCDothers);
    output->add("Events/FatJet_deepTag_TvsQCD[nFatJet]",
                 FatJet_deepTag_TvsQCD);
    output->add("Events/FatJet_deepTag_WvsQCD[nFatJet]",
                 FatJet_deepTag_WvsQCD);
    output->add("Events/FatJet_deepTag_ZvsQCD[nFatJet]",
                 FatJet_deepTag_ZvsQCD);
    output->add("Events/FatJet_electronIdx3SJ[nFatJet]",
                 FatJet_electronIdx3SJ);
    output->add("Events/FatJet_eta[nFatJet]", 	FatJet_eta);
    output->add("Events/FatJet_genJetAK8Idx[nFatJet]",
                 FatJet_genJetAK8Idx);
    output->add("Events/FatJet_hadronFlavour[nFatJet]",
                 FatJet_hadronFlavour);
    output->add("Events/FatJet_jetId[nFatJet]", 	FatJet_jetId);
    output->add("Events/FatJet_lsf3[nFatJet]", 	FatJet_lsf3);
    output->add("Events/FatJet_mass[nFatJet]", 	FatJet_mass_nom);
    output->add("Events/FatJet_mass_jerDown[nFatJet]",
                 FatJet_mass_jerDown);
    output->add("Events/FatJet_mass_jerUp[nFatJet]", 	FatJet_mass_jerUp);
    output->add("Events/FatJet_mass_jesTotalDown[nFatJet]",
                 FatJet_mass_jesTotalDown);
    output->add("Events/FatJet_mass_jesTotalUp[nFatJet]",
                 FatJet_mass_jesTotalUp);
    output->add("Events/FatJet_mass_jmrDown[nFatJet]",
                 FatJet_mass_jmrDown);
    output->add("Events/FatJet_mass_jmrUp[nFatJet]", 	FatJet_mass_jmrUp);
    output->add("Events/FatJet_mass_jmsDown[nFatJet]",
                 FatJet_mass_jmsDown);
    output->add("Events/FatJet_mass_jmsUp[nFatJet]", 	FatJet_mass_jmsUp);
    output->add("Events/FatJet_mass_nom[nFatJet]", 	FatJet_mass_nom);
    output->add("Events/FatJet_mass_raw[nFatJet]", 	FatJet_mass_raw);
    output->add("Events/FatJet_msoftdrop[nFatJet]", 	FatJet_msoftdrop_nom);
    output->add("Events/FatJet_msoftdrop_corr_JMR[nFatJet]",
                 FatJet_msoftdrop_corr_JMR);
    output->add("Events/FatJet_msoftdrop_corr_JMS[nFatJet]",
                 FatJet_msoftdrop_corr_JMS);
    output->add("Events/FatJet_msoftdrop_corr_PUPPI[nFatJet]",
                 FatJet_msoftdrop_corr_PUPPI);
    output->add("Events/FatJet_msoftdrop_jerDown[nFatJet]",
                 FatJet_msoftdrop_jerDown);
    output->add("Events/FatJet_msoftdrop_jerUp[nFatJet]",
                 FatJet_msoftdrop_jerUp);
    output->add("Events/FatJet_msoftdrop_jesTotalDown[nFatJet]",
                 FatJet_msoftdrop_jesTotalDown);
    output->add("Events/FatJet_msoftdrop_jesTotalUp[nFatJet]",
                 FatJet_msoftdrop_jesTotalUp);
    output->add("Events/FatJet_msoftdrop_jmrDown[nFatJet]",
                 FatJet_msoftdrop_jmrDown);
    output->add("Events/FatJet_msoftdrop_jmrUp[nFatJet]",
                 FatJet_msoftdrop_jmrUp);
    output->add("Events/FatJet_msoftdrop_jmsDown[nFatJet]",
                 FatJet_msoftdrop_jmsDown);
    output->add("Events/FatJet_msoftdrop_jmsUp[nFatJet]",
                 FatJet_msoftdrop_jmsUp);
    output->add("Events/FatJet_msoftdrop_nom[nFatJet]",
                 FatJet_msoftdrop_nom);
    output->add("Events/FatJet_msoftdrop_raw[nFatJet]",
                 FatJet_msoftdrop_raw);
    output->add("Events/FatJet_msoftdrop_tau21DDT_jerDown[nFatJet]",
                 FatJet_msoftdrop_tau21DDT_jerDown);
    output->add("Events/FatJet_msoftdrop_tau21DDT_jerUp[nFatJet]",
                 FatJet_msoftdrop_tau21DDT_jerUp);
    output->add("Events/FatJet_msoftdrop_tau21DDT_jmrDown[nFatJet]",
                 FatJet_msoftdrop_tau21DDT_jmrDown);
    output->add("Events/FatJet_msoftdrop_tau21DDT_jmrUp[nFatJet]",
                 FatJet_msoftdrop_tau21DDT_jmrUp);
    output->add("Events/FatJet_msoftdrop_tau21DDT_jmsDown[nFatJet]",
                 FatJet_msoftdrop_tau21DDT_jmsDown);
    output->add("Events/FatJet_msoftdrop_tau21DDT_jmsUp[nFatJet]",
                 FatJet_msoftdrop_tau21DDT_jmsUp);
    output->add("Events/FatJet_msoftdrop_tau21DDT_nom[nFatJet]",
                 FatJet_msoftdrop_tau21DDT_nom);
    output->add("Events/FatJet_muonIdx3SJ[nFatJet]", 	FatJet_muonIdx3SJ);
    output->add("Events/FatJet_n2b1[nFatJet]", 	FatJet_n2b1);
    output->add("Events/FatJet_n3b1[nFatJet]", 	FatJet_n3b1);
    output->add("Events/FatJet_nBHadrons[nFatJet]", 	FatJet_nBHadrons);
    output->add("Events/FatJet_nCHadrons[nFatJet]", 	FatJet_nCHadrons);
    output->add("Events/FatJet_nConstituents[nFatJet]",
                 FatJet_nConstituents);
    output->add("Events/FatJet_particleNetMD_QCD[nFatJet]",
                 FatJet_particleNetMD_QCD);
    output->add("Events/FatJet_particleNetMD_Xbb[nFatJet]",
                 FatJet_particleNetMD_Xbb);
    output->add("Events/FatJet_particleNetMD_Xcc[nFatJet]",
                 FatJet_particleNetMD_Xcc);
    output->add("Events/FatJet_particleNetMD_Xqq[nFatJet]",
                 FatJet_particleNetMD_Xqq);
    output->add("Events/FatJet_particleNet_H4qvsQCD[nFatJet]",
                 FatJet_particleNet_H4qvsQCD);
    output->add("Events/FatJet_particleNet_HbbvsQCD[nFatJet]",
                 FatJet_particleNet_HbbvsQCD);
    output->add("Events/FatJet_particleNet_HccvsQCD[nFatJet]",
                 FatJet_particleNet_HccvsQCD);
    output->add("Events/FatJet_particleNet_QCD[nFatJet]",
                 FatJet_particleNet_QCD);
    output->add("Events/FatJet_particleNet_TvsQCD[nFatJet]",
                 FatJet_particleNet_TvsQCD);
    output->add("Events/FatJet_particleNet_WvsQCD[nFatJet]",
                 FatJet_particleNet_WvsQCD);
    output->add("Events/FatJet_particleNet_ZvsQCD[nFatJet]",
                 FatJet_particleNet_ZvsQCD);
    output->add("Events/FatJet_particleNet_mass[nFatJet]",
                 FatJet_particleNet_mass);
    output->add("Events/FatJet_phi[nFatJet]", 	FatJet_phi);
    output->add("Events/FatJet_pt[nFatJet]", 	FatJet_pt_nom);
    output->add("Events/FatJet_pt_jerDown[nFatJet]", 	FatJet_pt_jerDown);
    output->add("Events/FatJet_pt_jerUp[nFatJet]", 	FatJet_pt_jerUp);
    output->add("Events/FatJet_pt_jesTotalDown[nFatJet]",
                 FatJet_pt_jesTotalDown);
    output->add("Events/FatJet_pt_jesTotalUp[nFatJet]",
                 FatJet_pt_jesTotalUp);
    output->add("Events/FatJet_pt_nom[nFatJet]", 	FatJet_pt_nom);
    output->add("Events/FatJet_pt_raw[nFatJet]", 	FatJet_pt_raw);
    output->add("Events/FatJet_rawFactor[nFatJet]", 	FatJet_rawFactor);
    output->add("Events/FatJet_subJetIdx1[nFatJet]", 	FatJet_subJetIdx1);
    output->add("Events/FatJet_subJetIdx2[nFatJet]", 	FatJet_subJetIdx2);
    output->add("Events/FatJet_tau1[nFatJet]", 	FatJet_tau1);
    output->add("Events/FatJet_tau2[nFatJet]", 	FatJet_tau2);
    output->add("Events/FatJet_tau3[nFatJet]", 	FatJet_tau3);
    output->add("Events/FatJet_tau4[nFatJet]", 	FatJet_tau4);
    output->add("Events/Flag_BadChargedCandidateFilter",
                 Flag_BadChargedCandidateFilter);
    output->add("Events/Flag_BadChargedCandidateSummer16Filter",
                 Flag_BadChargedCandidateSummer16Filter);
    output->add("Events/Flag_BadPFMuonDzFilter", 	Flag_BadPFMuonDzFilter);
    output->add("Events/Flag_BadPFMuonFilter", 	Flag_BadPFMuonFilter);
    output->add("Events/Flag_BadPFMuonSummer16Filter",
                 Flag_BadPFMuonSummer16Filter);
    output->add("Events/Flag_CSCTightHalo2015Filter",
                 Flag_CSCTightHalo2015Filter);
    output->add("Events/Flag_CSCTightHaloFilter", 	Flag_CSCTightHaloFilter);
    output->add("Events/Flag_CSCTightHaloTrkMuUnvetoFilter",
                 Flag_CSCTightHaloTrkMuUnvetoFilter);
    output->add("Events/Flag_EcalDeadCellBoundaryEnergyFilter",
                 Flag_EcalDeadCellBoundaryEnergyFilter);
    output->add("Events/Flag_EcalDeadCellTriggerPrimitiveFilter",
                 Flag_EcalDeadCellTriggerPrimitiveFilter);
    output->add("Events/Flag_HBHENoiseFilter", 	Flag_HBHENoiseFilter);
    output->add("Events/Flag_HBHENoiseIsoFilter", 	Flag_HBHENoiseIsoFilter);
    output->add("Events/Flag_HcalStripHaloFilter",
                 Flag_HcalStripHaloFilter);
    output->add("Events/Flag_METFilters", 	Flag_METFilters);
    output->add("Events/Flag_chargedHadronTrackResolutionFilter",
                 Flag_chargedHadronTrackResolutionFilter);
    output->add("Events/Flag_ecalBadCalibFilter", 	Flag_ecalBadCalibFilter);
    output->add("Events/Flag_ecalLaserCorrFilter",
                 Flag_ecalLaserCorrFilter);
    output->add("Events/Flag_eeBadScFilter", 	Flag_eeBadScFilter);
    output->add("Events/Flag_globalSuperTightHalo2016Filter",
                 Flag_globalSuperTightHalo2016Filter);
    output->add("Events/Flag_globalTightHalo2016Filter",
                 Flag_globalTightHalo2016Filter);
    output->add("Events/Flag_goodVertices", 	Flag_goodVertices);
    output->add("Events/Flag_hcalLaserEventFilter",
                 Flag_hcalLaserEventFilter);
    output->add("Events/Flag_hfNoisyHitsFilter", 	Flag_hfNoisyHitsFilter);
    output->add("Events/Flag_muonBadTrackFilter", 	Flag_muonBadTrackFilter);
    output->add("Events/Flag_trkPOGFilters", 	Flag_trkPOGFilters);
    output->add("Events/Flag_trkPOG_logErrorTooManyClusters",
                 Flag_trkPOG_logErrorTooManyClusters);
    output->add("Events/Flag_trkPOG_manystripclus53X",
                 Flag_trkPOG_manystripclus53X);
    output->add("Events/Flag_trkPOG_toomanystripclus53X",
                 Flag_trkPOG_toomanystripclus53X);
    output->add("Events/FsrPhoton_dROverEt2[nFsrPhoton]",
                 FsrPhoton_dROverEt2);
    output->add("Events/FsrPhoton_eta[nFsrPhoton]", 	FsrPhoton_eta);
    output->add("Events/FsrPhoton_muonIdx[nFsrPhoton]", 	FsrPhoton_muonIdx);
    output->add("Events/FsrPhoton_phi[nFsrPhoton]", 	FsrPhoton_phi);
    output->add("Events/FsrPhoton_pt[nFsrPhoton]", 	FsrPhoton_pt);
    output->add("Events/FsrPhoton_relIso03[nFsrPhoton]",
                 FsrPhoton_relIso03);
    output->add("Events/GenIsolatedPhoton_eta[nGenIsolatedPhoton]",
                 GenIsolatedPhoton_eta);
    output->add("Events/GenIsolatedPhoton_mass[nGenIsolatedPhoton]",
                 GenIsolatedPhoton_mass);
    output->add("Events/GenIsolatedPhoton_phi[nGenIsolatedPhoton]",
                 GenIsolatedPhoton_phi);
    output->add("Events/GenIsolatedPhoton_pt[nGenIsolatedPhoton]",
                 GenIsolatedPhoton_pt);
    output->add("Events/GenJetAK8_eta[nGenJetAK8]", 	GenJetAK8_eta);
    output->add("Events/GenJetAK8_hadronFlavour[nGenJetAK8]",
                 GenJetAK8_hadronFlavour);
    output->add("Events/GenJetAK8_mass[nGenJetAK8]", 	GenJetAK8_mass);
    output->add("Events/GenJetAK8_partonFlavour[nGenJetAK8]",
                 GenJetAK8_partonFlavour);
    output->add("Events/GenJetAK8_phi[nGenJetAK8]", 	GenJetAK8_phi);
    output->add("Events/GenJetAK8_pt[nGenJetAK8]", 	GenJetAK8_pt);
    output->add("Events/GenJet_eta[nGenJet]", 	GenJet_eta);
    output->add("Events/GenJet_hadronFlavour[nGenJet]",
                 GenJet_hadronFlavour);
    output->add("Events/GenJet_mass[nGenJet]", 	GenJet_mass);
    output->add("Events/GenJet_partonFlavour[nGenJet]",
                 GenJet_partonFlavour);
    output->add("Events/GenJet_phi[nGenJet]", 	GenJet_phi);
    output->add("Events/GenJet_pt[nGenJet]", 	GenJet_pt);
    output->add("Events/GenMET_phi", 	GenMET_phi);
    output->add("Events/GenMET_pt", 	GenMET_pt);
    output->add("Events/GenPart_eta[nGenPart]", 	GenPart_eta);
    output->add("Events/GenPart_genPartIdxMother[nGenPart]",
                 GenPart_genPartIdxMother);
    output->add("Events/GenPart_mass[nGenPart]", 	GenPart_mass);
    output->add("Events/GenPart_pdgId[nGenPart]", 	GenPart_pdgId);
    output->add("Events/GenPart_phi[nGenPart]", 	GenPart_phi);
    output->add("Events/GenPart_pt[nGenPart]", 	GenPart_pt);
    output->add("Events/GenPart_status[nGenPart]", 	GenPart_status);
    output->add("Events/GenPart_statusFlags[nGenPart]",
                 GenPart_statusFlags);
    output->add("Events/GenVtx_t0", 	GenVtx_t0);
    output->add("Events/GenVtx_x", 	GenVtx_x);
    output->add("Events/GenVtx_y", 	GenVtx_y);
    output->add("Events/GenVtx_z", 	GenVtx_z);
    output->add("Events/Generator_binvar", 	Generator_binvar);
    output->add("Events/Generator_id1", 	Generator_id1);
    output->add("Events/Generator_id2", 	Generator_id2);
    output->add("Events/Generator_scalePDF", 	Generator_scalePDF);
    output->add("Events/Generator_weight", 	Generator_weight);
    output->add("Events/Generator_x1", 	Generator_x1);
    output->add("Events/Generator_x2", 	Generator_x2);
    output->add("Events/Generator_xpdf1", 	Generator_xpdf1);
    output->add("Events/Generator_xpdf2", 	Generator_xpdf2);
		output->add("Events/HLT_PFHT300_PFMET110", 	HLT_PFHT300_PFMET110);
		output->add("Events/HLT_PFHT125", 	HLT_PFHT125);
		output->add("Events/HLT_PFHT200", 	HLT_PFHT200);
		output->add("Events/HLT_PFHT300", 	HLT_PFHT300);
		output->add("Events/HLT_PFHT400", 	HLT_PFHT400);
		output->add("Events/HLT_PFHT475", 	HLT_PFHT475);
		output->add("Events/HLT_PFHT650", 	HLT_PFHT650);
		output->add("Events/HLT_PFHT800", 	HLT_PFHT800);
		output->add("Events/HLT_PFHT900", 	HLT_PFHT900);
		output->add("Events/HLT_Ele15_IsoVVVL_PFHT350",
				HLT_Ele15_IsoVVVL_PFHT350);
		output->add("Events/HLT_Ele105_CaloIdVT_GsfTrkIdT",
				HLT_Ele105_CaloIdVT_GsfTrkIdT);
		output->add("Events/HLT_Mu15_IsoVVVL_PFHT350",
				HLT_Mu15_IsoVVVL_PFHT350);
		output->add("Events/HLT_IsoTkMu24", 	HLT_IsoTkMu24);
		output->add("Events/HLT_TkMu50", 	HLT_TkMu50);
		output->add("Events/HLT_Mu15_IsoVVVL_PFHT400",
				HLT_Mu15_IsoVVVL_PFHT400);
		output->add("Events/HLT_IsoTkMu27", 	HLT_IsoTkMu27);
		output->add("Events/HLT_Ele15_IsoVVVL_PFHT400",
				HLT_Ele15_IsoVVVL_PFHT400);
		output->add("Events/HLT_Photon22", 	HLT_Photon22);
		output->add("Events/HLT_Photon30", 	HLT_Photon30);
		output->add("Events/HLT_Photon36", 	HLT_Photon36);
		output->add("Events/HLT_Photon125", 	HLT_Photon125);
		output->add("Events/HLT_Photon165_HE10", 	HLT_Photon165_HE10);
		output->add("Events/HLT_Photon250_NoHE", 	HLT_Photon250_NoHE);
    output->add("Events/HLT_AK4CaloJet100", 	HLT_AK4CaloJet100);
    output->add("Events/HLT_AK4CaloJet120", 	HLT_AK4CaloJet120);
    output->add("Events/HLT_AK4CaloJet30", 	HLT_AK4CaloJet30);
    output->add("Events/HLT_AK4CaloJet40", 	HLT_AK4CaloJet40);
    output->add("Events/HLT_AK4CaloJet50", 	HLT_AK4CaloJet50);
    output->add("Events/HLT_AK4CaloJet80", 	HLT_AK4CaloJet80);
    output->add("Events/HLT_AK4PFJet100", 	HLT_AK4PFJet100);
    output->add("Events/HLT_AK4PFJet120", 	HLT_AK4PFJet120);
    output->add("Events/HLT_AK4PFJet30", 	HLT_AK4PFJet30);
    output->add("Events/HLT_AK4PFJet50", 	HLT_AK4PFJet50);
    output->add("Events/HLT_AK4PFJet80", 	HLT_AK4PFJet80);
    output->add("Events/HLT_AK8PFHT750_TrimMass50",
                 HLT_AK8PFHT750_TrimMass50);
    output->add("Events/HLT_AK8PFHT800_TrimMass50",
                 HLT_AK8PFHT800_TrimMass50);
    output->add("Events/HLT_AK8PFHT850_TrimMass50",
                 HLT_AK8PFHT850_TrimMass50);
    output->add("Events/HLT_AK8PFHT900_TrimMass50",
                 HLT_AK8PFHT900_TrimMass50);
    output->add("Events/HLT_AK8PFJet140", 	HLT_AK8PFJet140);
    output->add("Events/HLT_AK8PFJet15", 	HLT_AK8PFJet15);
    output->add("Events/HLT_AK8PFJet200", 	HLT_AK8PFJet200);
    output->add("Events/HLT_AK8PFJet25", 	HLT_AK8PFJet25);
    output->add("Events/HLT_AK8PFJet260", 	HLT_AK8PFJet260);
    output->add("Events/HLT_AK8PFJet320", 	HLT_AK8PFJet320);
    output->add("Events/HLT_AK8PFJet330_TrimMass30_PFAK8BTagDeepCSV_p1",
                 HLT_AK8PFJet330_TrimMass30_PFAK8BTagDeepCSV_p1);
    output->add("Events/HLT_AK8PFJet330_TrimMass30_PFAK8BTagDeepCSV_p17",
                 HLT_AK8PFJet330_TrimMass30_PFAK8BTagDeepCSV_p17);
    output->add("Events/HLT_AK8PFJet330_TrimMass30_PFAK8BoostedDoubleB_np2",
                 HLT_AK8PFJet330_TrimMass30_PFAK8BoostedDoubleB_np2);
    output->add("Events/HLT_AK8PFJet330_TrimMass30_PFAK8BoostedDoubleB_np4",
                 HLT_AK8PFJet330_TrimMass30_PFAK8BoostedDoubleB_np4);
    output->add("Events/HLT_AK8PFJet330_TrimMass30_PFAK8BoostedDoubleB_p02",
                 HLT_AK8PFJet330_TrimMass30_PFAK8BoostedDoubleB_p02);
    output->add("Events/HLT_AK8PFJet360_TrimMass30",
                 HLT_AK8PFJet360_TrimMass30);
    output->add("Events/HLT_AK8PFJet380_TrimMass30",
                 HLT_AK8PFJet380_TrimMass30);
    output->add("Events/HLT_AK8PFJet40", 	HLT_AK8PFJet40);
    output->add("Events/HLT_AK8PFJet400", 	HLT_AK8PFJet400);
    output->add("Events/HLT_AK8PFJet400_TrimMass30",
                 HLT_AK8PFJet400_TrimMass30);
    output->add("Events/HLT_AK8PFJet420_TrimMass30",
                 HLT_AK8PFJet420_TrimMass30);
    output->add("Events/HLT_AK8PFJet450", 	HLT_AK8PFJet450);
    output->add("Events/HLT_AK8PFJet500", 	HLT_AK8PFJet500);
    output->add("Events/HLT_AK8PFJet550", 	HLT_AK8PFJet550);
    output->add("Events/HLT_AK8PFJet60", 	HLT_AK8PFJet60);
    output->add("Events/HLT_AK8PFJet80", 	HLT_AK8PFJet80);
    output->add("Events/HLT_AK8PFJetFwd140", 	HLT_AK8PFJetFwd140);
    output->add("Events/HLT_AK8PFJetFwd15", 	HLT_AK8PFJetFwd15);
    output->add("Events/HLT_AK8PFJetFwd200", 	HLT_AK8PFJetFwd200);
    output->add("Events/HLT_AK8PFJetFwd25", 	HLT_AK8PFJetFwd25);
    output->add("Events/HLT_AK8PFJetFwd260", 	HLT_AK8PFJetFwd260);
    output->add("Events/HLT_AK8PFJetFwd320", 	HLT_AK8PFJetFwd320);
    output->add("Events/HLT_AK8PFJetFwd40", 	HLT_AK8PFJetFwd40);
    output->add("Events/HLT_AK8PFJetFwd400", 	HLT_AK8PFJetFwd400);
    output->add("Events/HLT_AK8PFJetFwd450", 	HLT_AK8PFJetFwd450);
    output->add("Events/HLT_AK8PFJetFwd500", 	HLT_AK8PFJetFwd500);
    output->add("Events/HLT_AK8PFJetFwd60", 	HLT_AK8PFJetFwd60);
    output->add("Events/HLT_AK8PFJetFwd80", 	HLT_AK8PFJetFwd80);
    output->add("Events/HLT_Ele115_CaloIdVT_GsfTrkIdT",
                 HLT_Ele115_CaloIdVT_GsfTrkIdT);
    output->add("Events/HLT_Ele12_CaloIdL_TrackIdL_IsoVL_PFJet30",
                 HLT_Ele12_CaloIdL_TrackIdL_IsoVL_PFJet30);
    output->add("Events/HLT_Ele135_CaloIdVT_GsfTrkIdT",
                 HLT_Ele135_CaloIdVT_GsfTrkIdT);
    output->add("Events/HLT_Ele145_CaloIdVT_GsfTrkIdT",
                 HLT_Ele145_CaloIdVT_GsfTrkIdT);
    output->add("Events/HLT_Ele15_CaloIdL_TrackIdL_IsoVL_PFJet30",
                 HLT_Ele15_CaloIdL_TrackIdL_IsoVL_PFJet30);
    output->add("Events/HLT_Ele15_Ele8_CaloIdL_TrackIdL_IsoVL",
                 HLT_Ele15_Ele8_CaloIdL_TrackIdL_IsoVL);
    output->add("Events/HLT_Ele15_IsoVVVL_PFHT450",
                 HLT_Ele15_IsoVVVL_PFHT450);
    output->add("Events/HLT_Ele15_IsoVVVL_PFHT450_CaloBTagDeepCSV_4p5",
                 HLT_Ele15_IsoVVVL_PFHT450_CaloBTagDeepCSV_4p5);
    output->add("Events/HLT_Ele15_IsoVVVL_PFHT450_PFMET50",
                 HLT_Ele15_IsoVVVL_PFHT450_PFMET50);
    output->add("Events/HLT_Ele15_IsoVVVL_PFHT600",
                 HLT_Ele15_IsoVVVL_PFHT600);
    output->add("Events/HLT_Ele15_WPLoose_Gsf", 	HLT_Ele15_WPLoose_Gsf);
    output->add("Events/HLT_Ele16_Ele12_Ele8_CaloIdL_TrackIdL",
                 HLT_Ele16_Ele12_Ele8_CaloIdL_TrackIdL);
    output->add("Events/HLT_Ele17_CaloIdM_TrackIdM_PFJet30",
                 HLT_Ele17_CaloIdM_TrackIdM_PFJet30);
    output->add("Events/HLT_Ele17_WPLoose_Gsf", 	HLT_Ele17_WPLoose_Gsf);
    output->add("Events/HLT_Ele200_CaloIdVT_GsfTrkIdT",
                 HLT_Ele200_CaloIdVT_GsfTrkIdT);
    output->add("Events/HLT_Ele20_WPLoose_Gsf", 	HLT_Ele20_WPLoose_Gsf);
    output->add("Events/HLT_Ele20_WPTight_Gsf", 	HLT_Ele20_WPTight_Gsf);
    output->add("Events/HLT_Ele20_eta2p1_WPLoose_Gsf",
                 HLT_Ele20_eta2p1_WPLoose_Gsf);
    output->add("Events/HLT_Ele23_CaloIdL_TrackIdL_IsoVL_PFJet30",
                 HLT_Ele23_CaloIdL_TrackIdL_IsoVL_PFJet30);
    output->add("Events/HLT_Ele23_CaloIdM_TrackIdM_PFJet30",
                 HLT_Ele23_CaloIdM_TrackIdM_PFJet30);
    output->add("Events/HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL",
                 HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL);
    output->add("Events/HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ",
                 HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ);
    output->add("Events/HLT_Ele24_eta2p1_WPTight_Gsf_LooseChargedIsoPFTauHPS30_eta2p1_CrossL1",
                 HLT_Ele24_eta2p1_WPTight_Gsf_LooseChargedIsoPFTauHPS30_eta2p1_CrossL1);
    output->add("Events/HLT_Ele24_eta2p1_WPTight_Gsf_LooseChargedIsoPFTauHPS30_eta2p1_TightID_CrossL1",
                 HLT_Ele24_eta2p1_WPTight_Gsf_LooseChargedIsoPFTauHPS30_eta2p1_TightID_CrossL1);
    output->add("Events/HLT_Ele24_eta2p1_WPTight_Gsf_MediumChargedIsoPFTauHPS30_eta2p1_CrossL1",
                 HLT_Ele24_eta2p1_WPTight_Gsf_MediumChargedIsoPFTauHPS30_eta2p1_CrossL1);
    output->add("Events/HLT_Ele24_eta2p1_WPTight_Gsf_MediumChargedIsoPFTauHPS30_eta2p1_TightID_CrossL1",
                 HLT_Ele24_eta2p1_WPTight_Gsf_MediumChargedIsoPFTauHPS30_eta2p1_TightID_CrossL1);
    output->add("Events/HLT_Ele24_eta2p1_WPTight_Gsf_TightChargedIsoPFTauHPS30_eta2p1_CrossL1",
                 HLT_Ele24_eta2p1_WPTight_Gsf_TightChargedIsoPFTauHPS30_eta2p1_CrossL1);
    output->add("Events/HLT_Ele24_eta2p1_WPTight_Gsf_TightChargedIsoPFTauHPS30_eta2p1_TightID_CrossL1",
                 HLT_Ele24_eta2p1_WPTight_Gsf_TightChargedIsoPFTauHPS30_eta2p1_TightID_CrossL1);
    output->add("Events/HLT_Ele250_CaloIdVT_GsfTrkIdT",
                 HLT_Ele250_CaloIdVT_GsfTrkIdT);
    output->add("Events/HLT_Ele27_Ele37_CaloIdL_MW",
                 HLT_Ele27_Ele37_CaloIdL_MW);
    output->add("Events/HLT_Ele27_WPTight_Gsf", 	HLT_Ele27_WPTight_Gsf);
    output->add("Events/HLT_Ele28_HighEta_SC20_Mass55",
                 HLT_Ele28_HighEta_SC20_Mass55);
    output->add("Events/HLT_Ele28_WPTight_Gsf", 	HLT_Ele28_WPTight_Gsf);
    output->add("Events/HLT_Ele28_eta2p1_WPTight_Gsf_HT150",
                 HLT_Ele28_eta2p1_WPTight_Gsf_HT150);
    output->add("Events/HLT_Ele300_CaloIdVT_GsfTrkIdT",
                 HLT_Ele300_CaloIdVT_GsfTrkIdT);
    output->add("Events/HLT_Ele30_WPTight_Gsf", 	HLT_Ele30_WPTight_Gsf);
    output->add("Events/HLT_Ele30_eta2p1_WPTight_Gsf_CentralPFJet35_EleCleaned",
                 HLT_Ele30_eta2p1_WPTight_Gsf_CentralPFJet35_EleCleaned);
    output->add("Events/HLT_Ele32_WPTight_Gsf", 	HLT_Ele32_WPTight_Gsf);
    output->add("Events/HLT_Ele32_WPTight_Gsf_L1DoubleEG",
                 HLT_Ele32_WPTight_Gsf_L1DoubleEG);
    output->add("Events/HLT_Ele35_WPTight_Gsf", 	HLT_Ele35_WPTight_Gsf);
    output->add("Events/HLT_Ele35_WPTight_Gsf_L1EGMT",
                 HLT_Ele35_WPTight_Gsf_L1EGMT);
    output->add("Events/HLT_Ele38_WPTight_Gsf", 	HLT_Ele38_WPTight_Gsf);
    output->add("Events/HLT_Ele40_WPTight_Gsf", 	HLT_Ele40_WPTight_Gsf);
    output->add("Events/HLT_Ele50_CaloIdVT_GsfTrkIdT_PFJet165",
                 HLT_Ele50_CaloIdVT_GsfTrkIdT_PFJet165);
    output->add("Events/HLT_Ele50_IsoVVVL_PFHT450",
                 HLT_Ele50_IsoVVVL_PFHT450);
    output->add("Events/HLT_Ele8_CaloIdL_TrackIdL_IsoVL_PFJet30",
                 HLT_Ele8_CaloIdL_TrackIdL_IsoVL_PFJet30);
    output->add("Events/HLT_Ele8_CaloIdM_TrackIdM_PFJet30",
                 HLT_Ele8_CaloIdM_TrackIdM_PFJet30);
    output->add("Events/HLT_HT300_Beamspot", 	HLT_HT300_Beamspot);
    output->add("Events/HLT_HT400_DisplacedDijet40_DisplacedTrack",
                 HLT_HT400_DisplacedDijet40_DisplacedTrack);
    output->add("Events/HLT_HT425", 	HLT_HT425);
    output->add("Events/HLT_HT430_DisplacedDijet40_DisplacedTrack",
                 HLT_HT430_DisplacedDijet40_DisplacedTrack);
    output->add("Events/HLT_HT430_DisplacedDijet60_DisplacedTrack",
                 HLT_HT430_DisplacedDijet60_DisplacedTrack);
    output->add("Events/HLT_HT450_Beamspot", 	HLT_HT450_Beamspot);
    output->add("Events/HLT_HT500_DisplacedDijet40_DisplacedTrack",
                 HLT_HT500_DisplacedDijet40_DisplacedTrack);
    output->add("Events/HLT_HT550_DisplacedDijet60_Inclusive",
                 HLT_HT550_DisplacedDijet60_Inclusive);
    output->add("Events/HLT_HT650_DisplacedDijet60_Inclusive",
                 HLT_HT650_DisplacedDijet60_Inclusive);
    output->add("Events/HLT_IsoMu20", 	HLT_IsoMu20);
    output->add("Events/HLT_IsoMu20_eta2p1_LooseChargedIsoPFTauHPS27_eta2p1_CrossL1",
                 HLT_IsoMu20_eta2p1_LooseChargedIsoPFTauHPS27_eta2p1_CrossL1);
    output->add("Events/HLT_IsoMu20_eta2p1_LooseChargedIsoPFTauHPS27_eta2p1_TightID_CrossL1",
                 HLT_IsoMu20_eta2p1_LooseChargedIsoPFTauHPS27_eta2p1_TightID_CrossL1);
    output->add("Events/HLT_IsoMu20_eta2p1_MediumChargedIsoPFTauHPS27_eta2p1_CrossL1",
                 HLT_IsoMu20_eta2p1_MediumChargedIsoPFTauHPS27_eta2p1_CrossL1);
    output->add("Events/HLT_IsoMu20_eta2p1_MediumChargedIsoPFTauHPS27_eta2p1_TightID_CrossL1",
                 HLT_IsoMu20_eta2p1_MediumChargedIsoPFTauHPS27_eta2p1_TightID_CrossL1);
    output->add("Events/HLT_IsoMu20_eta2p1_TightChargedIsoPFTauHPS27_eta2p1_CrossL1",
                 HLT_IsoMu20_eta2p1_TightChargedIsoPFTauHPS27_eta2p1_CrossL1);
    output->add("Events/HLT_IsoMu20_eta2p1_TightChargedIsoPFTauHPS27_eta2p1_TightID_CrossL1",
                 HLT_IsoMu20_eta2p1_TightChargedIsoPFTauHPS27_eta2p1_TightID_CrossL1);
    output->add("Events/HLT_IsoMu24", 	HLT_IsoMu24);
    output->add("Events/HLT_IsoMu24_TwoProngs35", 	HLT_IsoMu24_TwoProngs35);
    output->add("Events/HLT_IsoMu24_eta2p1", 	HLT_IsoMu24_eta2p1);
    output->add("Events/HLT_IsoMu24_eta2p1_MediumChargedIsoPFTau50_Trk30_eta2p1_1pr",
                 HLT_IsoMu24_eta2p1_MediumChargedIsoPFTau50_Trk30_eta2p1_1pr);
    output->add("Events/HLT_IsoMu24_eta2p1_MediumChargedIsoPFTauHPS35_Trk1_TightID_eta2p1_Reg_CrossL1",
                 HLT_IsoMu24_eta2p1_MediumChargedIsoPFTauHPS35_Trk1_TightID_eta2p1_Reg_CrossL1);
    output->add("Events/HLT_IsoMu24_eta2p1_MediumChargedIsoPFTauHPS35_Trk1_eta2p1_Reg_CrossL1",
                 HLT_IsoMu24_eta2p1_MediumChargedIsoPFTauHPS35_Trk1_eta2p1_Reg_CrossL1);
    output->add("Events/HLT_IsoMu24_eta2p1_TightChargedIsoPFTauHPS35_Trk1_TightID_eta2p1_Reg_CrossL1",
                 HLT_IsoMu24_eta2p1_TightChargedIsoPFTauHPS35_Trk1_TightID_eta2p1_Reg_CrossL1);
    output->add("Events/HLT_IsoMu24_eta2p1_TightChargedIsoPFTauHPS35_Trk1_eta2p1_Reg_CrossL1",
                 HLT_IsoMu24_eta2p1_TightChargedIsoPFTauHPS35_Trk1_eta2p1_Reg_CrossL1);
    output->add("Events/HLT_IsoMu27", 	HLT_IsoMu27);
    output->add("Events/HLT_IsoMu27_LooseChargedIsoPFTauHPS20_Trk1_eta2p1_SingleL1",
                 HLT_IsoMu27_LooseChargedIsoPFTauHPS20_Trk1_eta2p1_SingleL1);
    output->add("Events/HLT_IsoMu27_MET90", 	HLT_IsoMu27_MET90);
    output->add("Events/HLT_IsoMu27_MediumChargedIsoPFTauHPS20_Trk1_eta2p1_SingleL1",
                 HLT_IsoMu27_MediumChargedIsoPFTauHPS20_Trk1_eta2p1_SingleL1);
    output->add("Events/HLT_IsoMu27_TightChargedIsoPFTauHPS20_Trk1_eta2p1_SingleL1",
                 HLT_IsoMu27_TightChargedIsoPFTauHPS20_Trk1_eta2p1_SingleL1);
    output->add("Events/HLT_IsoMu30", 	HLT_IsoMu30);
    output->add("Events/HLT_IsoTrackHB", 	HLT_IsoTrackHB);
    output->add("Events/HLT_IsoTrackHE", 	HLT_IsoTrackHE);
    output->add("Events/HLT_MET105_IsoTrk50", 	HLT_MET105_IsoTrk50);
    output->add("Events/HLT_MET120_IsoTrk50", 	HLT_MET120_IsoTrk50);
    output->add("Events/HLT_Mu10_TrkIsoVVL_DiPFJet40_DEta3p5_MJJ750_HTT350_PFMETNoMu60",
                 HLT_Mu10_TrkIsoVVL_DiPFJet40_DEta3p5_MJJ750_HTT350_PFMETNoMu60);
    output->add("Events/HLT_Mu12", 	HLT_Mu12);
    output->add("Events/HLT_Mu12_DoublePFJets100_CaloBTagDeepCSV_p71",
                 HLT_Mu12_DoublePFJets100_CaloBTagDeepCSV_p71);
    output->add("Events/HLT_Mu12_DoublePFJets200_CaloBTagDeepCSV_p71",
                 HLT_Mu12_DoublePFJets200_CaloBTagDeepCSV_p71);
    output->add("Events/HLT_Mu12_DoublePFJets350_CaloBTagDeepCSV_p71",
                 HLT_Mu12_DoublePFJets350_CaloBTagDeepCSV_p71);
    output->add("Events/HLT_Mu12_DoublePFJets40MaxDeta1p6_DoubleCaloBTagDeepCSV_p71",
                 HLT_Mu12_DoublePFJets40MaxDeta1p6_DoubleCaloBTagDeepCSV_p71);
    output->add("Events/HLT_Mu12_DoublePFJets40_CaloBTagDeepCSV_p71",
                 HLT_Mu12_DoublePFJets40_CaloBTagDeepCSV_p71);
    output->add("Events/HLT_Mu12_DoublePFJets54MaxDeta1p6_DoubleCaloBTagDeepCSV_p71",
                 HLT_Mu12_DoublePFJets54MaxDeta1p6_DoubleCaloBTagDeepCSV_p71);
    output->add("Events/HLT_Mu12_DoublePFJets62MaxDeta1p6_DoubleCaloBTagDeepCSV_p71",
                 HLT_Mu12_DoublePFJets62MaxDeta1p6_DoubleCaloBTagDeepCSV_p71);
    output->add("Events/HLT_Mu12_DoublePhoton20", 	HLT_Mu12_DoublePhoton20);
    output->add("Events/HLT_Mu12_IP6_part0", 	HLT_Mu12_IP6_part0);
    output->add("Events/HLT_Mu12_IP6_part1", 	HLT_Mu12_IP6_part1);
    output->add("Events/HLT_Mu12_IP6_part2", 	HLT_Mu12_IP6_part2);
    output->add("Events/HLT_Mu12_IP6_part3", 	HLT_Mu12_IP6_part3);
    output->add("Events/HLT_Mu12_IP6_part4", 	HLT_Mu12_IP6_part4);
    output->add("Events/HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL",
                 HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL);
    output->add("Events/HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ",
                 HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ);
    output->add("Events/HLT_Mu15", 	HLT_Mu15);
    output->add("Events/HLT_Mu15_IsoVVVL_PFHT450",
                 HLT_Mu15_IsoVVVL_PFHT450);
    output->add("Events/HLT_Mu15_IsoVVVL_PFHT450_CaloBTagDeepCSV_4p5",
                 HLT_Mu15_IsoVVVL_PFHT450_CaloBTagDeepCSV_4p5);
    output->add("Events/HLT_Mu15_IsoVVVL_PFHT450_PFMET50",
                 HLT_Mu15_IsoVVVL_PFHT450_PFMET50);
    output->add("Events/HLT_Mu15_IsoVVVL_PFHT600",
                 HLT_Mu15_IsoVVVL_PFHT600);
    output->add("Events/HLT_Mu17", 	HLT_Mu17);
    output->add("Events/HLT_Mu17_Photon30_IsoCaloId",
                 HLT_Mu17_Photon30_IsoCaloId);
    output->add("Events/HLT_Mu17_TrkIsoVVL", 	HLT_Mu17_TrkIsoVVL);
    output->add("Events/HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL",
                 HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL);
    output->add("Events/HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ",
                 HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ);
    output->add("Events/HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8",
                 HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8);
    output->add("Events/HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass8",
                 HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass8);
    output->add("Events/HLT_Mu18_Mu9", 	HLT_Mu18_Mu9);
    output->add("Events/HLT_Mu18_Mu9_DZ", 	HLT_Mu18_Mu9_DZ);
    output->add("Events/HLT_Mu18_Mu9_SameSign", 	HLT_Mu18_Mu9_SameSign);
    output->add("Events/HLT_Mu18_Mu9_SameSign_DZ",
                 HLT_Mu18_Mu9_SameSign_DZ);
    output->add("Events/HLT_Mu19", 	HLT_Mu19);
    output->add("Events/HLT_Mu19_TrkIsoVVL", 	HLT_Mu19_TrkIsoVVL);
    output->add("Events/HLT_Mu19_TrkIsoVVL_Mu9_TrkIsoVVL",
                 HLT_Mu19_TrkIsoVVL_Mu9_TrkIsoVVL);
    output->add("Events/HLT_Mu19_TrkIsoVVL_Mu9_TrkIsoVVL_DZ",
                 HLT_Mu19_TrkIsoVVL_Mu9_TrkIsoVVL_DZ);
    output->add("Events/HLT_Mu19_TrkIsoVVL_Mu9_TrkIsoVVL_DZ_Mass3p8",
                 HLT_Mu19_TrkIsoVVL_Mu9_TrkIsoVVL_DZ_Mass3p8);
    output->add("Events/HLT_Mu19_TrkIsoVVL_Mu9_TrkIsoVVL_DZ_Mass8",
                 HLT_Mu19_TrkIsoVVL_Mu9_TrkIsoVVL_DZ_Mass8);
    output->add("Events/HLT_Mu20", 	HLT_Mu20);
    output->add("Events/HLT_Mu20_Mu10", 	HLT_Mu20_Mu10);
    output->add("Events/HLT_Mu20_Mu10_DZ", 	HLT_Mu20_Mu10_DZ);
    output->add("Events/HLT_Mu20_Mu10_SameSign", 	HLT_Mu20_Mu10_SameSign);
    output->add("Events/HLT_Mu20_Mu10_SameSign_DZ",
                 HLT_Mu20_Mu10_SameSign_DZ);
    output->add("Events/HLT_Mu20_TkMu0_Phi", 	HLT_Mu20_TkMu0_Phi);
    output->add("Events/HLT_Mu23_Mu12", 	HLT_Mu23_Mu12);
    output->add("Events/HLT_Mu23_Mu12_DZ", 	HLT_Mu23_Mu12_DZ);
    output->add("Events/HLT_Mu23_Mu12_SameSign", 	HLT_Mu23_Mu12_SameSign);
    output->add("Events/HLT_Mu23_Mu12_SameSign_DZ",
                 HLT_Mu23_Mu12_SameSign_DZ);
    output->add("Events/HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL",
                 HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL);
    output->add("Events/HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ",
                 HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ);
    output->add("Events/HLT_Mu25_TkMu0_Onia", 	HLT_Mu25_TkMu0_Onia);
    output->add("Events/HLT_Mu25_TkMu0_Phi", 	HLT_Mu25_TkMu0_Phi);
    output->add("Events/HLT_Mu27", 	HLT_Mu27);
    output->add("Events/HLT_Mu27_Ele37_CaloIdL_MW",
                 HLT_Mu27_Ele37_CaloIdL_MW);
    output->add("Events/HLT_Mu30_TkMu0_Psi", 	HLT_Mu30_TkMu0_Psi);
    output->add("Events/HLT_Mu30_TkMu0_Upsilon", 	HLT_Mu30_TkMu0_Upsilon);
    output->add("Events/HLT_Mu37_Ele27_CaloIdL_MW",
                 HLT_Mu37_Ele27_CaloIdL_MW);
    output->add("Events/HLT_Mu37_TkMu27", 	HLT_Mu37_TkMu27);
    output->add("Events/HLT_Mu38NoFiltersNoVtxDisplaced_Photon38_CaloIdL",
                 HLT_Mu38NoFiltersNoVtxDisplaced_Photon38_CaloIdL);
    output->add("Events/HLT_Mu3_L1SingleMu5orSingleMu7",
                 HLT_Mu3_L1SingleMu5orSingleMu7);
    output->add("Events/HLT_Mu3_PFJet40", 	HLT_Mu3_PFJet40);
    output->add("Events/HLT_Mu3er1p5_PFJet100er2p5_PFMET100_PFMHT100_IDTight",
                 HLT_Mu3er1p5_PFJet100er2p5_PFMET100_PFMHT100_IDTight);
    output->add("Events/HLT_Mu3er1p5_PFJet100er2p5_PFMET70_PFMHT70_IDTight",
                 HLT_Mu3er1p5_PFJet100er2p5_PFMET70_PFMHT70_IDTight);
    output->add("Events/HLT_Mu3er1p5_PFJet100er2p5_PFMET80_PFMHT80_IDTight",
                 HLT_Mu3er1p5_PFJet100er2p5_PFMET80_PFMHT80_IDTight);
    output->add("Events/HLT_Mu3er1p5_PFJet100er2p5_PFMET90_PFMHT90_IDTight",
                 HLT_Mu3er1p5_PFJet100er2p5_PFMET90_PFMHT90_IDTight);
    output->add("Events/HLT_Mu3er1p5_PFJet100er2p5_PFMETNoMu100_PFMHTNoMu100_IDTight",
                 HLT_Mu3er1p5_PFJet100er2p5_PFMETNoMu100_PFMHTNoMu100_IDTight);
    output->add("Events/HLT_Mu3er1p5_PFJet100er2p5_PFMETNoMu70_PFMHTNoMu70_IDTight",
                 HLT_Mu3er1p5_PFJet100er2p5_PFMETNoMu70_PFMHTNoMu70_IDTight);
    output->add("Events/HLT_Mu3er1p5_PFJet100er2p5_PFMETNoMu80_PFMHTNoMu80_IDTight",
                 HLT_Mu3er1p5_PFJet100er2p5_PFMETNoMu80_PFMHTNoMu80_IDTight);
    output->add("Events/HLT_Mu3er1p5_PFJet100er2p5_PFMETNoMu90_PFMHTNoMu90_IDTight",
                 HLT_Mu3er1p5_PFJet100er2p5_PFMETNoMu90_PFMHTNoMu90_IDTight);
    output->add("Events/HLT_Mu43NoFiltersNoVtxDisplaced_Photon43_CaloIdL",
                 HLT_Mu43NoFiltersNoVtxDisplaced_Photon43_CaloIdL);
    output->add("Events/HLT_Mu43NoFiltersNoVtx_Photon43_CaloIdL",
                 HLT_Mu43NoFiltersNoVtx_Photon43_CaloIdL);
    output->add("Events/HLT_Mu48NoFiltersNoVtx_Photon48_CaloIdL",
                 HLT_Mu48NoFiltersNoVtx_Photon48_CaloIdL);
    output->add("Events/HLT_Mu4_TrkIsoVVL_DiPFJet90_40_DEta3p5_MJJ750_HTT300_PFMETNoMu60",
                 HLT_Mu4_TrkIsoVVL_DiPFJet90_40_DEta3p5_MJJ750_HTT300_PFMETNoMu60);
    output->add("Events/HLT_Mu50", 	HLT_Mu50);
    output->add("Events/HLT_Mu50_IsoVVVL_PFHT450",
                 HLT_Mu50_IsoVVVL_PFHT450);
    output->add("Events/HLT_Mu55", 	HLT_Mu55);
    output->add("Events/HLT_Mu7_IP4_part0", 	HLT_Mu7_IP4_part0);
    output->add("Events/HLT_Mu7_IP4_part1", 	HLT_Mu7_IP4_part1);
    output->add("Events/HLT_Mu7_IP4_part2", 	HLT_Mu7_IP4_part2);
    output->add("Events/HLT_Mu7_IP4_part3", 	HLT_Mu7_IP4_part3);
    output->add("Events/HLT_Mu7_IP4_part4", 	HLT_Mu7_IP4_part4);
    output->add("Events/HLT_Mu7p5_L2Mu2_Jpsi", 	HLT_Mu7p5_L2Mu2_Jpsi);
    output->add("Events/HLT_Mu7p5_L2Mu2_Upsilon", 	HLT_Mu7p5_L2Mu2_Upsilon);
    output->add("Events/HLT_Mu7p5_Track2_Jpsi", 	HLT_Mu7p5_Track2_Jpsi);
    output->add("Events/HLT_Mu7p5_Track2_Upsilon",
                 HLT_Mu7p5_Track2_Upsilon);
    output->add("Events/HLT_Mu7p5_Track3p5_Jpsi", 	HLT_Mu7p5_Track3p5_Jpsi);
    output->add("Events/HLT_Mu7p5_Track3p5_Upsilon",
                 HLT_Mu7p5_Track3p5_Upsilon);
    output->add("Events/HLT_Mu7p5_Track7_Jpsi", 	HLT_Mu7p5_Track7_Jpsi);
    output->add("Events/HLT_Mu7p5_Track7_Upsilon",
                 HLT_Mu7p5_Track7_Upsilon);
    output->add("Events/HLT_Mu8", 	HLT_Mu8);
    output->add("Events/HLT_Mu8_DiEle12_CaloIdL_TrackIdL",
                 HLT_Mu8_DiEle12_CaloIdL_TrackIdL);
    output->add("Events/HLT_Mu8_DiEle12_CaloIdL_TrackIdL_DZ",
                 HLT_Mu8_DiEle12_CaloIdL_TrackIdL_DZ);
    output->add("Events/HLT_Mu8_Ele8_CaloIdM_TrackIdM_Mass8_PFHT350",
                 HLT_Mu8_Ele8_CaloIdM_TrackIdM_Mass8_PFHT350);
    output->add("Events/HLT_Mu8_Ele8_CaloIdM_TrackIdM_Mass8_PFHT350_DZ",
                 HLT_Mu8_Ele8_CaloIdM_TrackIdM_Mass8_PFHT350_DZ);
    output->add("Events/HLT_Mu8_IP3_part0", 	HLT_Mu8_IP3_part0);
    output->add("Events/HLT_Mu8_IP3_part1", 	HLT_Mu8_IP3_part1);
    output->add("Events/HLT_Mu8_IP3_part2", 	HLT_Mu8_IP3_part2);
    output->add("Events/HLT_Mu8_IP3_part3", 	HLT_Mu8_IP3_part3);
    output->add("Events/HLT_Mu8_IP3_part4", 	HLT_Mu8_IP3_part4);
    output->add("Events/HLT_Mu8_IP5_part0", 	HLT_Mu8_IP5_part0);
    output->add("Events/HLT_Mu8_IP5_part1", 	HLT_Mu8_IP5_part1);
    output->add("Events/HLT_Mu8_IP5_part2", 	HLT_Mu8_IP5_part2);
    output->add("Events/HLT_Mu8_IP5_part3", 	HLT_Mu8_IP5_part3);
    output->add("Events/HLT_Mu8_IP5_part4", 	HLT_Mu8_IP5_part4);
    output->add("Events/HLT_Mu8_IP6_part0", 	HLT_Mu8_IP6_part0);
    output->add("Events/HLT_Mu8_IP6_part1", 	HLT_Mu8_IP6_part1);
    output->add("Events/HLT_Mu8_IP6_part2", 	HLT_Mu8_IP6_part2);
    output->add("Events/HLT_Mu8_IP6_part3", 	HLT_Mu8_IP6_part3);
    output->add("Events/HLT_Mu8_IP6_part4", 	HLT_Mu8_IP6_part4);
    output->add("Events/HLT_Mu8_TrkIsoVVL", 	HLT_Mu8_TrkIsoVVL);
    output->add("Events/HLT_Mu8_TrkIsoVVL_DiPFJet40_DEta3p5_MJJ750_HTT300_PFMETNoMu60",
                 HLT_Mu8_TrkIsoVVL_DiPFJet40_DEta3p5_MJJ750_HTT300_PFMETNoMu60);
    output->add("Events/HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL",
                 HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL);
    output->add("Events/HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ",
                 HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ);
    output->add("Events/HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_CaloDiJet30",
                 HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_CaloDiJet30);
    output->add("Events/HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_CaloDiJet30_CaloBtagDeepCSV_1p5",
                 HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_CaloDiJet30_CaloBtagDeepCSV_1p5);
    output->add("Events/HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_PFDiJet30",
                 HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_PFDiJet30);
    output->add("Events/HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_PFDiJet30_PFBtagDeepCSV_1p5",
                 HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_PFDiJet30_PFBtagDeepCSV_1p5);
    output->add("Events/HLT_Mu9_IP4_part0", 	HLT_Mu9_IP4_part0);
    output->add("Events/HLT_Mu9_IP4_part1", 	HLT_Mu9_IP4_part1);
    output->add("Events/HLT_Mu9_IP4_part2", 	HLT_Mu9_IP4_part2);
    output->add("Events/HLT_Mu9_IP4_part3", 	HLT_Mu9_IP4_part3);
    output->add("Events/HLT_Mu9_IP4_part4", 	HLT_Mu9_IP4_part4);
    output->add("Events/HLT_Mu9_IP5_part0", 	HLT_Mu9_IP5_part0);
    output->add("Events/HLT_Mu9_IP5_part1", 	HLT_Mu9_IP5_part1);
    output->add("Events/HLT_Mu9_IP5_part2", 	HLT_Mu9_IP5_part2);
    output->add("Events/HLT_Mu9_IP5_part3", 	HLT_Mu9_IP5_part3);
    output->add("Events/HLT_Mu9_IP5_part4", 	HLT_Mu9_IP5_part4);
    output->add("Events/HLT_Mu9_IP6_part0", 	HLT_Mu9_IP6_part0);
    output->add("Events/HLT_Mu9_IP6_part1", 	HLT_Mu9_IP6_part1);
    output->add("Events/HLT_Mu9_IP6_part2", 	HLT_Mu9_IP6_part2);
    output->add("Events/HLT_Mu9_IP6_part3", 	HLT_Mu9_IP6_part3);
    output->add("Events/HLT_Mu9_IP6_part4", 	HLT_Mu9_IP6_part4);
    output->add("Events/HLT_OldMu100", 	HLT_OldMu100);
    output->add("Events/HLT_PFHT1050", 	HLT_PFHT1050);
    output->add("Events/HLT_PFHT180", 	HLT_PFHT180);
    output->add("Events/HLT_PFHT250", 	HLT_PFHT250);
    output->add("Events/HLT_PFHT330PT30_QuadPFJet_75_60_45_40",
                 HLT_PFHT330PT30_QuadPFJet_75_60_45_40);
    output->add("Events/HLT_PFHT330PT30_QuadPFJet_75_60_45_40_TriplePFBTagDeepCSV_4p5",
                 HLT_PFHT330PT30_QuadPFJet_75_60_45_40_TriplePFBTagDeepCSV_4p5);
    output->add("Events/HLT_PFHT350", 	HLT_PFHT350);
    output->add("Events/HLT_PFHT350MinPFJet15", 	HLT_PFHT350MinPFJet15);
    output->add("Events/HLT_PFHT370", 	HLT_PFHT370);
    output->add("Events/HLT_PFHT400_SixPFJet32", 	HLT_PFHT400_SixPFJet32);
    output->add("Events/HLT_PFHT400_SixPFJet32_DoublePFBTagDeepCSV_2p94",
                 HLT_PFHT400_SixPFJet32_DoublePFBTagDeepCSV_2p94);
    output->add("Events/HLT_PFHT430", 	HLT_PFHT430);
    output->add("Events/HLT_PFHT450_SixPFJet36", 	HLT_PFHT450_SixPFJet36);
    output->add("Events/HLT_PFHT450_SixPFJet36_PFBTagDeepCSV_1p59",
                 HLT_PFHT450_SixPFJet36_PFBTagDeepCSV_1p59);
    output->add("Events/HLT_PFHT500_PFMET100_PFMHT100_IDTight",
                 HLT_PFHT500_PFMET100_PFMHT100_IDTight);
    output->add("Events/HLT_PFHT500_PFMET110_PFMHT110_IDTight",
                 HLT_PFHT500_PFMET110_PFMHT110_IDTight);
    output->add("Events/HLT_PFHT510", 	HLT_PFHT510);
    output->add("Events/HLT_PFHT590", 	HLT_PFHT590);
    output->add("Events/HLT_PFHT680", 	HLT_PFHT680);
    output->add("Events/HLT_PFHT700_PFMET85_PFMHT85_IDTight",
                 HLT_PFHT700_PFMET85_PFMHT85_IDTight);
    output->add("Events/HLT_PFHT700_PFMET95_PFMHT95_IDTight",
                 HLT_PFHT700_PFMET95_PFMHT95_IDTight);
    output->add("Events/HLT_PFHT780", 	HLT_PFHT780);
    output->add("Events/HLT_PFHT800_PFMET75_PFMHT75_IDTight",
                 HLT_PFHT800_PFMET75_PFMHT75_IDTight);
    output->add("Events/HLT_PFHT800_PFMET85_PFMHT85_IDTight",
                 HLT_PFHT800_PFMET85_PFMHT85_IDTight);
    output->add("Events/HLT_PFHT890", 	HLT_PFHT890);
    output->add("Events/HLT_PFJet140", 	HLT_PFJet140);
    output->add("Events/HLT_PFJet15", 	HLT_PFJet15);
    output->add("Events/HLT_PFJet200", 	HLT_PFJet200);
    output->add("Events/HLT_PFJet25", 	HLT_PFJet25);
    output->add("Events/HLT_PFJet260", 	HLT_PFJet260);
    output->add("Events/HLT_PFJet320", 	HLT_PFJet320);
    output->add("Events/HLT_PFJet40", 	HLT_PFJet40);
    output->add("Events/HLT_PFJet400", 	HLT_PFJet400);
    output->add("Events/HLT_PFJet450", 	HLT_PFJet450);
    output->add("Events/HLT_PFJet500", 	HLT_PFJet500);
    output->add("Events/HLT_PFJet550", 	HLT_PFJet550);
    output->add("Events/HLT_PFJet60", 	HLT_PFJet60);
    output->add("Events/HLT_PFJet80", 	HLT_PFJet80);
    output->add("Events/HLT_PFJetFwd140", 	HLT_PFJetFwd140);
    output->add("Events/HLT_PFJetFwd15", 	HLT_PFJetFwd15);
    output->add("Events/HLT_PFJetFwd200", 	HLT_PFJetFwd200);
    output->add("Events/HLT_PFJetFwd25", 	HLT_PFJetFwd25);
    output->add("Events/HLT_PFJetFwd260", 	HLT_PFJetFwd260);
    output->add("Events/HLT_PFJetFwd320", 	HLT_PFJetFwd320);
    output->add("Events/HLT_PFJetFwd40", 	HLT_PFJetFwd40);
    output->add("Events/HLT_PFJetFwd400", 	HLT_PFJetFwd400);
    output->add("Events/HLT_PFJetFwd450", 	HLT_PFJetFwd450);
    output->add("Events/HLT_PFJetFwd500", 	HLT_PFJetFwd500);
    output->add("Events/HLT_PFJetFwd60", 	HLT_PFJetFwd60);
    output->add("Events/HLT_PFJetFwd80", 	HLT_PFJetFwd80);
    output->add("Events/HLT_PFMET100_PFMHT100_IDTight_CaloBTagDeepCSV_3p1",
                 HLT_PFMET100_PFMHT100_IDTight_CaloBTagDeepCSV_3p1);
    output->add("Events/HLT_PFMET100_PFMHT100_IDTight_PFHT60",
                 HLT_PFMET100_PFMHT100_IDTight_PFHT60);
    output->add("Events/HLT_PFMET110_PFMHT110_IDTight",
                 HLT_PFMET110_PFMHT110_IDTight);
    output->add("Events/HLT_PFMET110_PFMHT110_IDTight_CaloBTagDeepCSV_3p1",
                 HLT_PFMET110_PFMHT110_IDTight_CaloBTagDeepCSV_3p1);
    output->add("Events/HLT_PFMET120_PFMHT120_IDTight",
                 HLT_PFMET120_PFMHT120_IDTight);
    output->add("Events/HLT_PFMET120_PFMHT120_IDTight_CaloBTagDeepCSV_3p1",
                 HLT_PFMET120_PFMHT120_IDTight_CaloBTagDeepCSV_3p1);
    output->add("Events/HLT_PFMET120_PFMHT120_IDTight_PFHT60",
                 HLT_PFMET120_PFMHT120_IDTight_PFHT60);
    output->add("Events/HLT_PFMET130_PFMHT130_IDTight",
                 HLT_PFMET130_PFMHT130_IDTight);
    output->add("Events/HLT_PFMET130_PFMHT130_IDTight_CaloBTagDeepCSV_3p1",
                 HLT_PFMET130_PFMHT130_IDTight_CaloBTagDeepCSV_3p1);
    output->add("Events/HLT_PFMET140_PFMHT140_IDTight",
                 HLT_PFMET140_PFMHT140_IDTight);
    output->add("Events/HLT_PFMET140_PFMHT140_IDTight_CaloBTagDeepCSV_3p1",
                 HLT_PFMET140_PFMHT140_IDTight_CaloBTagDeepCSV_3p1);
    output->add("Events/HLT_PFMET200_HBHECleaned",
                 HLT_PFMET200_HBHECleaned);
    output->add("Events/HLT_PFMET200_HBHE_BeamHaloCleaned",
                 HLT_PFMET200_HBHE_BeamHaloCleaned);
    output->add("Events/HLT_PFMET200_NotCleaned", 	HLT_PFMET200_NotCleaned);
    output->add("Events/HLT_PFMET250_HBHECleaned",
                 HLT_PFMET250_HBHECleaned);
    output->add("Events/HLT_PFMET300_HBHECleaned",
                 HLT_PFMET300_HBHECleaned);
    output->add("Events/HLT_PFMETNoMu100_PFMHTNoMu100_IDTight_PFHT60",
                 HLT_PFMETNoMu100_PFMHTNoMu100_IDTight_PFHT60);
    output->add("Events/HLT_PFMETNoMu110_PFMHTNoMu110_IDTight",
                 HLT_PFMETNoMu110_PFMHTNoMu110_IDTight);
    output->add("Events/HLT_PFMETNoMu120_PFMHTNoMu120_IDTight",
                 HLT_PFMETNoMu120_PFMHTNoMu120_IDTight);
    output->add("Events/HLT_PFMETNoMu120_PFMHTNoMu120_IDTight_PFHT60",
                 HLT_PFMETNoMu120_PFMHTNoMu120_IDTight_PFHT60);
    output->add("Events/HLT_PFMETNoMu130_PFMHTNoMu130_IDTight",
                 HLT_PFMETNoMu130_PFMHTNoMu130_IDTight);
    output->add("Events/HLT_PFMETNoMu140_PFMHTNoMu140_IDTight",
                 HLT_PFMETNoMu140_PFMHTNoMu140_IDTight);
    output->add("Events/HLT_PFMETTypeOne100_PFMHT100_IDTight_PFHT60",
                 HLT_PFMETTypeOne100_PFMHT100_IDTight_PFHT60);
    output->add("Events/HLT_PFMETTypeOne110_PFMHT110_IDTight",
                 HLT_PFMETTypeOne110_PFMHT110_IDTight);
    output->add("Events/HLT_PFMETTypeOne120_PFMHT120_IDTight",
                 HLT_PFMETTypeOne120_PFMHT120_IDTight);
    output->add("Events/HLT_PFMETTypeOne120_PFMHT120_IDTight_PFHT60",
                 HLT_PFMETTypeOne120_PFMHT120_IDTight_PFHT60);
    output->add("Events/HLT_PFMETTypeOne130_PFMHT130_IDTight",
                 HLT_PFMETTypeOne130_PFMHT130_IDTight);
    output->add("Events/HLT_PFMETTypeOne140_PFMHT140_IDTight",
                 HLT_PFMETTypeOne140_PFMHT140_IDTight);
    output->add("Events/HLT_PFMETTypeOne200_HBHE_BeamHaloCleaned",
                 HLT_PFMETTypeOne200_HBHE_BeamHaloCleaned);
    output->add("Events/HLT_Photon100EBHE10", 	HLT_Photon100EBHE10);
    output->add("Events/HLT_Photon100EB_TightID_TightIso",
                 HLT_Photon100EB_TightID_TightIso);
    output->add("Events/HLT_Photon100EEHE10", 	HLT_Photon100EEHE10);
    output->add("Events/HLT_Photon100EE_TightID_TightIso",
                 HLT_Photon100EE_TightID_TightIso);
    output->add("Events/HLT_Photon110EB_TightID_TightIso",
                 HLT_Photon110EB_TightID_TightIso);
    output->add("Events/HLT_Photon120", 	HLT_Photon120);
    output->add("Events/HLT_Photon120EB_TightID_TightIso",
                 HLT_Photon120EB_TightID_TightIso);
    output->add("Events/HLT_Photon120_R9Id90_HE10_IsoM",
                 HLT_Photon120_R9Id90_HE10_IsoM);
    output->add("Events/HLT_Photon150", 	HLT_Photon150);
    output->add("Events/HLT_Photon165_R9Id90_HE10_IsoM",
                 HLT_Photon165_R9Id90_HE10_IsoM);
    output->add("Events/HLT_Photon175", 	HLT_Photon175);
    output->add("Events/HLT_Photon20", 	HLT_Photon20);
    output->add("Events/HLT_Photon200", 	HLT_Photon200);
    output->add("Events/HLT_Photon20_HoverELoose",
                 HLT_Photon20_HoverELoose);
    output->add("Events/HLT_Photon300_NoHE", 	HLT_Photon300_NoHE);
    output->add("Events/HLT_Photon30_HoverELoose",
                 HLT_Photon30_HoverELoose);
    output->add("Events/HLT_Photon33", 	HLT_Photon33);
    output->add("Events/HLT_Photon35_TwoProngs35",
                 HLT_Photon35_TwoProngs35);
    output->add("Events/HLT_Photon50", 	HLT_Photon50);
    output->add("Events/HLT_Photon50_R9Id90_HE10_IsoM",
                 HLT_Photon50_R9Id90_HE10_IsoM);
    output->add("Events/HLT_Photon50_R9Id90_HE10_IsoM_EBOnly_PFJetsMJJ300DEta3_PFMET50",
                 HLT_Photon50_R9Id90_HE10_IsoM_EBOnly_PFJetsMJJ300DEta3_PFMET50);
    output->add("Events/HLT_Photon60_R9Id90_CaloIdL_IsoL",
                 HLT_Photon60_R9Id90_CaloIdL_IsoL);
    output->add("Events/HLT_Photon60_R9Id90_CaloIdL_IsoL_DisplacedIdL",
                 HLT_Photon60_R9Id90_CaloIdL_IsoL_DisplacedIdL);
    output->add("Events/HLT_Photon60_R9Id90_CaloIdL_IsoL_DisplacedIdL_PFHT350MinPFJet15",
                 HLT_Photon60_R9Id90_CaloIdL_IsoL_DisplacedIdL_PFHT350MinPFJet15);
    output->add("Events/HLT_Photon75", 	HLT_Photon75);
    output->add("Events/HLT_Photon75_R9Id90_HE10_IsoM",
                 HLT_Photon75_R9Id90_HE10_IsoM);
    output->add("Events/HLT_Photon75_R9Id90_HE10_IsoM_EBOnly_CaloMJJ300_PFJetsMJJ400DEta3",
                 HLT_Photon75_R9Id90_HE10_IsoM_EBOnly_CaloMJJ300_PFJetsMJJ400DEta3);
    output->add("Events/HLT_Photon75_R9Id90_HE10_IsoM_EBOnly_CaloMJJ400_PFJetsMJJ600DEta3",
                 HLT_Photon75_R9Id90_HE10_IsoM_EBOnly_CaloMJJ400_PFJetsMJJ600DEta3);
    output->add("Events/HLT_Photon75_R9Id90_HE10_IsoM_EBOnly_PFJetsMJJ300DEta3",
                 HLT_Photon75_R9Id90_HE10_IsoM_EBOnly_PFJetsMJJ300DEta3);
    output->add("Events/HLT_Photon75_R9Id90_HE10_IsoM_EBOnly_PFJetsMJJ600DEta3",
                 HLT_Photon75_R9Id90_HE10_IsoM_EBOnly_PFJetsMJJ600DEta3);
    output->add("Events/HLT_Photon90", 	HLT_Photon90);
    output->add("Events/HLT_Photon90_CaloIdL_PFHT700",
                 HLT_Photon90_CaloIdL_PFHT700);
    output->add("Events/HLT_Photon90_R9Id90_HE10_IsoM",
                 HLT_Photon90_R9Id90_HE10_IsoM);
    output->add("Events/HLT_Rsq0p35", 	HLT_Rsq0p35);
    output->add("Events/HLT_Rsq0p40", 	HLT_Rsq0p40);
    output->add("Events/HLT_RsqMR300_Rsq0p09_MR200",
                 HLT_RsqMR300_Rsq0p09_MR200);
    output->add("Events/HLT_RsqMR300_Rsq0p09_MR200_4jet",
                 HLT_RsqMR300_Rsq0p09_MR200_4jet);
    output->add("Events/HLT_RsqMR320_Rsq0p09_MR200",
                 HLT_RsqMR320_Rsq0p09_MR200);
    output->add("Events/HLT_RsqMR320_Rsq0p09_MR200_4jet",
                 HLT_RsqMR320_Rsq0p09_MR200_4jet);
    output->add("Events/HLT_SingleJet30_Mu12_SinglePFJet40",
                 HLT_SingleJet30_Mu12_SinglePFJet40);
    output->add("Events/HLT_SinglePhoton10_Eta3p1ForPPRef",
                 HLT_SinglePhoton10_Eta3p1ForPPRef);
    output->add("Events/HLT_SinglePhoton20_Eta3p1ForPPRef",
                 HLT_SinglePhoton20_Eta3p1ForPPRef);
    output->add("Events/HLT_SinglePhoton30_Eta3p1ForPPRef",
                 HLT_SinglePhoton30_Eta3p1ForPPRef);
    output->add("Events/HLT_Tau3Mu_Mu7_Mu1_TkMu1_IsoTau15",
                 HLT_Tau3Mu_Mu7_Mu1_TkMu1_IsoTau15);
    output->add("Events/HLT_Tau3Mu_Mu7_Mu1_TkMu1_IsoTau15_Charge1",
                 HLT_Tau3Mu_Mu7_Mu1_TkMu1_IsoTau15_Charge1);
    output->add("Events/HLT_Tau3Mu_Mu7_Mu1_TkMu1_Tau15",
                 HLT_Tau3Mu_Mu7_Mu1_TkMu1_Tau15);
    output->add("Events/HLT_Tau3Mu_Mu7_Mu1_TkMu1_Tau15_Charge1",
                 HLT_Tau3Mu_Mu7_Mu1_TkMu1_Tau15_Charge1);
    output->add("Events/HLT_TkMu100", 	HLT_TkMu100);
    output->add("Events/HLT_Trimuon5_3p5_2_Upsilon_Muon",
                 HLT_Trimuon5_3p5_2_Upsilon_Muon);
    output->add("Events/HLT_TrimuonOpen_5_3p5_2_Upsilon_Muon",
                 HLT_TrimuonOpen_5_3p5_2_Upsilon_Muon);
    output->add("Events/HLT_TrkMu12_DoubleTrkMu5NoFiltersNoVtx",
                 HLT_TrkMu12_DoubleTrkMu5NoFiltersNoVtx);
    output->add("Events/HLT_TrkMu16NoFiltersNoVtx",
                 HLT_TrkMu16NoFiltersNoVtx);
    output->add("Events/HLT_TrkMu16_DoubleTrkMu6NoFiltersNoVtx",
                 HLT_TrkMu16_DoubleTrkMu6NoFiltersNoVtx);
    output->add("Events/HLT_TrkMu17_DoubleTrkMu8NoFiltersNoVtx",
                 HLT_TrkMu17_DoubleTrkMu8NoFiltersNoVtx);
    output->add("Events/HLT_TrkMu6NoFiltersNoVtx",
                 HLT_TrkMu6NoFiltersNoVtx);
    output->add("Events/HLTriggerFinalPath", 	HLTriggerFinalPath);
    output->add("Events/HLTriggerFirstPath", 	HLTriggerFirstPath);
    output->add("Events/IsoTrack_charge[nIsoTrack]", 	IsoTrack_charge);
    output->add("Events/IsoTrack_dxy[nIsoTrack]", 	IsoTrack_dxy);
    output->add("Events/IsoTrack_dz[nIsoTrack]", 	IsoTrack_dz);
    output->add("Events/IsoTrack_eta[nIsoTrack]", 	IsoTrack_eta);
    output->add("Events/IsoTrack_fromPV[nIsoTrack]", 	IsoTrack_fromPV);
    output->add("Events/IsoTrack_isFromLostTrack[nIsoTrack]",
                 IsoTrack_isFromLostTrack);
    output->add("Events/IsoTrack_isHighPurityTrack[nIsoTrack]",
                 IsoTrack_isHighPurityTrack);
    output->add("Events/IsoTrack_isPFcand[nIsoTrack]", 	IsoTrack_isPFcand);
    output->add("Events/IsoTrack_miniPFRelIso_all[nIsoTrack]",
                 IsoTrack_miniPFRelIso_all);
    output->add("Events/IsoTrack_miniPFRelIso_chg[nIsoTrack]",
                 IsoTrack_miniPFRelIso_chg);
    output->add("Events/IsoTrack_pdgId[nIsoTrack]", 	IsoTrack_pdgId);
    output->add("Events/IsoTrack_pfRelIso03_all[nIsoTrack]",
                 IsoTrack_pfRelIso03_all);
    output->add("Events/IsoTrack_pfRelIso03_chg[nIsoTrack]",
                 IsoTrack_pfRelIso03_chg);
    output->add("Events/IsoTrack_phi[nIsoTrack]", 	IsoTrack_phi);
    output->add("Events/IsoTrack_pt[nIsoTrack]", 	IsoTrack_pt);
    output->add("Events/Jet_area[nJet]", 	Jet_area);
    output->add("Events/Jet_bRegCorr[nJet]", 	Jet_bRegCorr);
    output->add("Events/Jet_bRegRes[nJet]", 	Jet_bRegRes);
    output->add("Events/Jet_btagCSVV2[nJet]", 	Jet_btagCSVV2);
    output->add("Events/Jet_btagDeepB[nJet]", 	Jet_btagDeepB);
    output->add("Events/Jet_btagDeepCvB[nJet]", 	Jet_btagDeepCvB);
    output->add("Events/Jet_btagDeepCvL[nJet]", 	Jet_btagDeepCvL);
    output->add("Events/Jet_btagDeepFlavB[nJet]", 	Jet_btagDeepFlavB);
    output->add("Events/Jet_btagDeepFlavCvB[nJet]", 	Jet_btagDeepFlavCvB);
    output->add("Events/Jet_btagDeepFlavCvL[nJet]", 	Jet_btagDeepFlavCvL);
    output->add("Events/Jet_btagDeepFlavQG[nJet]", 	Jet_btagDeepFlavQG);
    output->add("Events/Jet_cRegCorr[nJet]", 	Jet_cRegCorr);
    output->add("Events/Jet_cRegRes[nJet]", 	Jet_cRegRes);
    output->add("Events/Jet_chEmEF[nJet]", 	Jet_chEmEF);
    output->add("Events/Jet_chFPV0EF[nJet]", 	Jet_chFPV0EF);
    output->add("Events/Jet_chHEF[nJet]", 	Jet_chHEF);
    output->add("Events/Jet_cleanmask[nJet]", 	Jet_cleanmask);
    output->add("Events/Jet_corr_JEC[nJet]", 	Jet_corr_JEC);
    output->add("Events/Jet_corr_JER[nJet]", 	Jet_corr_JER);
    output->add("Events/Jet_electronIdx1[nJet]", 	Jet_electronIdx1);
    output->add("Events/Jet_electronIdx2[nJet]", 	Jet_electronIdx2);
    output->add("Events/Jet_eta[nJet]", 	Jet_eta);
    output->add("Events/Jet_genJetIdx[nJet]", 	Jet_genJetIdx);
    output->add("Events/Jet_hadronFlavour[nJet]", 	Jet_hadronFlavour);
    output->add("Events/Jet_hfadjacentEtaStripsSize[nJet]",
                 Jet_hfadjacentEtaStripsSize);
    output->add("Events/Jet_hfcentralEtaStripSize[nJet]",
                 Jet_hfcentralEtaStripSize);
    output->add("Events/Jet_hfsigmaEtaEta[nJet]", 	Jet_hfsigmaEtaEta);
    output->add("Events/Jet_hfsigmaPhiPhi[nJet]", 	Jet_hfsigmaPhiPhi);
    output->add("Events/Jet_jetId[nJet]", 	Jet_jetId);
    output->add("Events/Jet_mass[nJet]", 	Jet_mass_nom);
    output->add("Events/Jet_mass_jerDown[nJet]", 	Jet_mass_jerDown);
    output->add("Events/Jet_mass_jerUp[nJet]", 	Jet_mass_jerUp);
    output->add("Events/Jet_mass_jesTotalDown[nJet]",
                 Jet_mass_jesTotalDown);
    output->add("Events/Jet_mass_jesTotalUp[nJet]", 	Jet_mass_jesTotalUp);
    output->add("Events/Jet_mass_nom[nJet]", 	Jet_mass_nom);
    output->add("Events/Jet_mass_raw[nJet]", 	Jet_mass_raw);
    output->add("Events/Jet_muEF[nJet]", 	Jet_muEF);
    output->add("Events/Jet_muonIdx1[nJet]", 	Jet_muonIdx1);
    output->add("Events/Jet_muonIdx2[nJet]", 	Jet_muonIdx2);
    output->add("Events/Jet_muonSubtrFactor[nJet]", 	Jet_muonSubtrFactor);
    output->add("Events/Jet_nConstituents[nJet]", 	Jet_nConstituents);
    output->add("Events/Jet_nElectrons[nJet]", 	Jet_nElectrons);
    output->add("Events/Jet_nMuons[nJet]", 	Jet_nMuons);
    output->add("Events/Jet_neEmEF[nJet]", 	Jet_neEmEF);
    output->add("Events/Jet_neHEF[nJet]", 	Jet_neHEF);
    output->add("Events/Jet_partonFlavour[nJet]", 	Jet_partonFlavour);
    output->add("Events/Jet_phi[nJet]", 	Jet_phi);
    output->add("Events/Jet_pt[nJet]", 	Jet_pt_nom);
    output->add("Events/Jet_pt_jerDown[nJet]", 	Jet_pt_jerDown);
    output->add("Events/Jet_pt_jerUp[nJet]", 	Jet_pt_jerUp);
    output->add("Events/Jet_pt_jesTotalDown[nJet]", 	Jet_pt_jesTotalDown);
    output->add("Events/Jet_pt_jesTotalUp[nJet]", 	Jet_pt_jesTotalUp);
    output->add("Events/Jet_pt_nom[nJet]", 	Jet_pt_nom);
    output->add("Events/Jet_pt_raw[nJet]", 	Jet_pt_raw);
    output->add("Events/Jet_puId[nJet]", 	Jet_puId);
    output->add("Events/Jet_puIdDisc[nJet]", 	Jet_puIdDisc);
    output->add("Events/Jet_qgl[nJet]", 	Jet_qgl);
    output->add("Events/Jet_rawFactor[nJet]", 	Jet_rawFactor);
    output->add("Events/L1PreFiringWeight_Dn", 	L1PreFiringWeight_Dn);
    output->add("Events/L1PreFiringWeight_ECAL_Dn",
                 L1PreFiringWeight_ECAL_Dn);
    output->add("Events/L1PreFiringWeight_ECAL_Nom",
                 L1PreFiringWeight_ECAL_Nom);
    output->add("Events/L1PreFiringWeight_ECAL_Up",
                 L1PreFiringWeight_ECAL_Up);
    output->add("Events/L1PreFiringWeight_Muon_Nom",
                 L1PreFiringWeight_Muon_Nom);
    output->add("Events/L1PreFiringWeight_Muon_StatDn",
                 L1PreFiringWeight_Muon_StatDn);
    output->add("Events/L1PreFiringWeight_Muon_StatUp",
                 L1PreFiringWeight_Muon_StatUp);
    output->add("Events/L1PreFiringWeight_Muon_SystDn",
                 L1PreFiringWeight_Muon_SystDn);
    output->add("Events/L1PreFiringWeight_Muon_SystUp",
                 L1PreFiringWeight_Muon_SystUp);
    output->add("Events/L1PreFiringWeight_Nom", 	L1PreFiringWeight_Nom);
    output->add("Events/L1PreFiringWeight_Up", 	L1PreFiringWeight_Up);
    output->add("Events/L1Reco_step", 	L1Reco_step);
    output->add("Events/L1simulation_step", 	L1simulation_step);
    output->add("Events/LHEPart_eta[nLHEPart]", 	LHEPart_eta);
    output->add("Events/LHEPart_incomingpz[nLHEPart]", 	LHEPart_incomingpz);
    output->add("Events/LHEPart_mass[nLHEPart]", 	LHEPart_mass);
    output->add("Events/LHEPart_pdgId[nLHEPart]", 	LHEPart_pdgId);
    output->add("Events/LHEPart_phi[nLHEPart]", 	LHEPart_phi);
    output->add("Events/LHEPart_pt[nLHEPart]", 	LHEPart_pt);
    output->add("Events/LHEPart_spin[nLHEPart]", 	LHEPart_spin);
    output->add("Events/LHEPart_status[nLHEPart]", 	LHEPart_status);
    output->add("Events/LHEPdfWeight[nLHEPdfWeight]", 	LHEPdfWeight);
    output->add("Events/LHEReweightingWeight[nLHEReweightingWeight]",
                 LHEReweightingWeight);
    output->add("Events/LHEScaleWeight[nLHEScaleWeight]", 	LHEScaleWeight);
    output->add("Events/LHEWeight_originalXWGTUP",
                 LHEWeight_originalXWGTUP);
    output->add("Events/LHE_AlphaS", 	LHE_AlphaS);
    output->add("Events/LHE_HT", 	LHE_HT);
    output->add("Events/LHE_HTIncoming", 	LHE_HTIncoming);
    output->add("Events/LHE_Nb", 	LHE_Nb);
    output->add("Events/LHE_Nc", 	LHE_Nc);
    output->add("Events/LHE_Nglu", 	LHE_Nglu);
    output->add("Events/LHE_Njets", 	LHE_Njets);
    output->add("Events/LHE_NpLO", 	LHE_NpLO);
    output->add("Events/LHE_NpNLO", 	LHE_NpNLO);
    output->add("Events/LHE_Nuds", 	LHE_Nuds);
    output->add("Events/LHE_Vpt", 	LHE_Vpt);
    output->add("Events/MET_MetUnclustEnUpDeltaX",
                 MET_MetUnclustEnUpDeltaX);
    output->add("Events/MET_MetUnclustEnUpDeltaY",
                 MET_MetUnclustEnUpDeltaY);
    output->add("Events/MET_T1Smear_phi", 	MET_T1Smear_phi);
    output->add("Events/MET_T1Smear_phi_jerDown", 	MET_T1Smear_phi_jerDown);
    output->add("Events/MET_T1Smear_phi_jerUp", 	MET_T1Smear_phi_jerUp);
    output->add("Events/MET_T1Smear_phi_jesTotalDown",
                 MET_T1Smear_phi_jesTotalDown);
    output->add("Events/MET_T1Smear_phi_jesTotalUp",
                 MET_T1Smear_phi_jesTotalUp);
    output->add("Events/MET_T1Smear_phi_unclustEnDown",
                 MET_T1Smear_phi_unclustEnDown);
    output->add("Events/MET_T1Smear_phi_unclustEnUp",
                 MET_T1Smear_phi_unclustEnUp);
    output->add("Events/MET_T1Smear_pt", 	MET_T1Smear_pt);
    output->add("Events/MET_T1Smear_pt_jerDown", 	MET_T1Smear_pt_jerDown);
    output->add("Events/MET_T1Smear_pt_jerUp", 	MET_T1Smear_pt_jerUp);
    output->add("Events/MET_T1Smear_pt_jesTotalDown",
                 MET_T1Smear_pt_jesTotalDown);
    output->add("Events/MET_T1Smear_pt_jesTotalUp",
                 MET_T1Smear_pt_jesTotalUp);
    output->add("Events/MET_T1Smear_pt_unclustEnDown",
                 MET_T1Smear_pt_unclustEnDown);
    output->add("Events/MET_T1Smear_pt_unclustEnUp",
                 MET_T1Smear_pt_unclustEnUp);
    output->add("Events/MET_T1_phi", 	MET_T1_phi);
    output->add("Events/MET_T1_phi_jerDown", 	MET_T1_phi_jerDown);
    output->add("Events/MET_T1_phi_jerUp", 	MET_T1_phi_jerUp);
    output->add("Events/MET_T1_phi_jesTotalDown", 	MET_T1_phi_jesTotalDown);
    output->add("Events/MET_T1_phi_jesTotalUp", 	MET_T1_phi_jesTotalUp);
    output->add("Events/MET_T1_phi_unclustEnDown",
                 MET_T1_phi_unclustEnDown);
    output->add("Events/MET_T1_phi_unclustEnUp", 	MET_T1_phi_unclustEnUp);
    output->add("Events/MET_T1_pt", 	MET_T1_pt);
    output->add("Events/MET_T1_pt_jerDown", 	MET_T1_pt_jerDown);
    output->add("Events/MET_T1_pt_jerUp", 	MET_T1_pt_jerUp);
    output->add("Events/MET_T1_pt_jesTotalDown", 	MET_T1_pt_jesTotalDown);
    output->add("Events/MET_T1_pt_jesTotalUp", 	MET_T1_pt_jesTotalUp);
    output->add("Events/MET_T1_pt_unclustEnDown", 	MET_T1_pt_unclustEnDown);
    output->add("Events/MET_T1_pt_unclustEnUp", 	MET_T1_pt_unclustEnUp);
    output->add("Events/MET_covXX", 	MET_covXX);
    output->add("Events/MET_covXY", 	MET_covXY);
    output->add("Events/MET_covYY", 	MET_covYY);
    output->add("Events/MET_fiducialGenPhi", 	MET_fiducialGenPhi);
    output->add("Events/MET_fiducialGenPt", 	MET_fiducialGenPt);
    output->add("Events/MET_phi", 	MET_phi);
    output->add("Events/MET_pt", 	MET_pt);
    output->add("Events/MET_significance", 	MET_significance);
    output->add("Events/MET_sumEt", 	MET_sumEt);
    output->add("Events/MET_sumPtUnclustered", 	MET_sumPtUnclustered);
    output->add("Events/Muon_charge[nMuon]", 	Muon_charge);
    output->add("Events/Muon_cleanmask[nMuon]", 	Muon_cleanmask);
    output->add("Events/Muon_dxy[nMuon]", 	Muon_dxy);
    output->add("Events/Muon_dxyErr[nMuon]", 	Muon_dxyErr);
    output->add("Events/Muon_dxybs[nMuon]", 	Muon_dxybs);
    output->add("Events/Muon_dz[nMuon]", 	Muon_dz);
    output->add("Events/Muon_dzErr[nMuon]", 	Muon_dzErr);
    output->add("Events/Muon_eta[nMuon]", 	Muon_eta);
    output->add("Events/Muon_fsrPhotonIdx[nMuon]", 	Muon_fsrPhotonIdx);
    output->add("Events/Muon_genPartFlav[nMuon]", 	Muon_genPartFlav);
    output->add("Events/Muon_genPartIdx[nMuon]", 	Muon_genPartIdx);
    output->add("Events/Muon_highPtId[nMuon]", 	Muon_highPtId);
    output->add("Events/Muon_highPurity[nMuon]", 	Muon_highPurity);
    output->add("Events/Muon_inTimeMuon[nMuon]", 	Muon_inTimeMuon);
    output->add("Events/Muon_ip3d[nMuon]", 	Muon_ip3d);
    output->add("Events/Muon_isGlobal[nMuon]", 	Muon_isGlobal);
    output->add("Events/Muon_isPFcand[nMuon]", 	Muon_isPFcand);
    output->add("Events/Muon_isStandalone[nMuon]", 	Muon_isStandalone);
    output->add("Events/Muon_isTracker[nMuon]", 	Muon_isTracker);
    output->add("Events/Muon_jetIdx[nMuon]", 	Muon_jetIdx);
    output->add("Events/Muon_jetNDauCharged[nMuon]", 	Muon_jetNDauCharged);
    output->add("Events/Muon_jetPtRelv2[nMuon]", 	Muon_jetPtRelv2);
    output->add("Events/Muon_jetRelIso[nMuon]", 	Muon_jetRelIso);
    output->add("Events/Muon_looseId[nMuon]", 	Muon_looseId);
    output->add("Events/Muon_mass[nMuon]", 	Muon_mass);
    output->add("Events/Muon_mediumId[nMuon]", 	Muon_mediumId);
    output->add("Events/Muon_mediumPromptId[nMuon]", 	Muon_mediumPromptId);
    output->add("Events/Muon_miniIsoId[nMuon]", 	Muon_miniIsoId);
    output->add("Events/Muon_miniPFRelIso_all[nMuon]",
                 Muon_miniPFRelIso_all);
    output->add("Events/Muon_miniPFRelIso_chg[nMuon]",
                 Muon_miniPFRelIso_chg);
    output->add("Events/Muon_multiIsoId[nMuon]", 	Muon_multiIsoId);
    output->add("Events/Muon_mvaId[nMuon]", 	Muon_mvaId);
    output->add("Events/Muon_mvaLowPt[nMuon]", 	Muon_mvaLowPt);
    output->add("Events/Muon_mvaLowPtId[nMuon]", 	Muon_mvaLowPtId);
    output->add("Events/Muon_mvaTTH[nMuon]", 	Muon_mvaTTH);
    output->add("Events/Muon_nStations[nMuon]", 	Muon_nStations);
    output->add("Events/Muon_nTrackerLayers[nMuon]", 	Muon_nTrackerLayers);
    output->add("Events/Muon_pdgId[nMuon]", 	Muon_pdgId);
    output->add("Events/Muon_pfIsoId[nMuon]", 	Muon_pfIsoId);
    output->add("Events/Muon_pfRelIso03_all[nMuon]", 	Muon_pfRelIso03_all);
    output->add("Events/Muon_pfRelIso03_chg[nMuon]", 	Muon_pfRelIso03_chg);
    output->add("Events/Muon_pfRelIso04_all[nMuon]", 	Muon_pfRelIso04_all);
    output->add("Events/Muon_phi[nMuon]", 	Muon_phi);
    output->add("Events/Muon_pt[nMuon]", 	Muon_pt);
    output->add("Events/Muon_ptErr[nMuon]", 	Muon_ptErr);
    output->add("Events/Muon_puppiIsoId[nMuon]", 	Muon_puppiIsoId);
    output->add("Events/Muon_segmentComp[nMuon]", 	Muon_segmentComp);
    output->add("Events/Muon_sip3d[nMuon]", 	Muon_sip3d);
    output->add("Events/Muon_softId[nMuon]", 	Muon_softId);
    output->add("Events/Muon_softMva[nMuon]", 	Muon_softMva);
    output->add("Events/Muon_softMvaId[nMuon]", 	Muon_softMvaId);
    output->add("Events/Muon_tightCharge[nMuon]", 	Muon_tightCharge);
    output->add("Events/Muon_tightId[nMuon]", 	Muon_tightId);
    output->add("Events/Muon_tkIsoId[nMuon]", 	Muon_tkIsoId);
    output->add("Events/Muon_tkRelIso[nMuon]", 	Muon_tkRelIso);
    output->add("Events/Muon_triggerIdLoose[nMuon]", 	Muon_triggerIdLoose);
    output->add("Events/Muon_tunepRelPt[nMuon]", 	Muon_tunepRelPt);
    output->add("Events/OtherPV_z[nOtherPV]", 	OtherPV_z);
    output->add("Events/PSWeight[nPSWeight]", 	PSWeight);
    output->add("Events/PV_chi2", 	PV_chi2);
    output->add("Events/PV_ndof", 	PV_ndof);
    output->add("Events/PV_npvs", 	PV_npvs);
    output->add("Events/PV_npvsGood", 	PV_npvsGood);
    output->add("Events/PV_score", 	PV_score);
    output->add("Events/PV_x", 	PV_x);
    output->add("Events/PV_y", 	PV_y);
    output->add("Events/PV_z", 	PV_z);
    output->add("Events/Photon_charge[nPhoton]", 	Photon_charge);
    output->add("Events/Photon_cleanmask[nPhoton]", 	Photon_cleanmask);
    output->add("Events/Photon_cutBased[nPhoton]", 	Photon_cutBased);
    output->add("Events/Photon_cutBased_Fall17V1Bitmap[nPhoton]",
                 Photon_cutBased_Fall17V1Bitmap);
    output->add("Events/Photon_dEscaleDown[nPhoton]", 	Photon_dEscaleDown);
    output->add("Events/Photon_dEscaleUp[nPhoton]", 	Photon_dEscaleUp);
    output->add("Events/Photon_dEsigmaDown[nPhoton]", 	Photon_dEsigmaDown);
    output->add("Events/Photon_dEsigmaUp[nPhoton]", 	Photon_dEsigmaUp);
    output->add("Events/Photon_eCorr[nPhoton]", 	Photon_eCorr);
    output->add("Events/Photon_electronIdx[nPhoton]", 	Photon_electronIdx);
    output->add("Events/Photon_electronVeto[nPhoton]",
                 Photon_electronVeto);
    output->add("Events/Photon_energyErr[nPhoton]", 	Photon_energyErr);
    output->add("Events/Photon_eta[nPhoton]", 	Photon_eta);
    output->add("Events/Photon_genPartFlav[nPhoton]", 	Photon_genPartFlav);
    output->add("Events/Photon_genPartIdx[nPhoton]", 	Photon_genPartIdx);
    output->add("Events/Photon_hoe[nPhoton]", 	Photon_hoe);
    output->add("Events/Photon_isScEtaEB[nPhoton]", 	Photon_isScEtaEB);
    output->add("Events/Photon_isScEtaEE[nPhoton]", 	Photon_isScEtaEE);
    output->add("Events/Photon_jetIdx[nPhoton]", 	Photon_jetIdx);
    output->add("Events/Photon_mass[nPhoton]", 	Photon_mass);
    output->add("Events/Photon_mvaID[nPhoton]", 	Photon_mvaID);
    output->add("Events/Photon_mvaID_Fall17V1p1[nPhoton]",
                 Photon_mvaID_Fall17V1p1);
    output->add("Events/Photon_mvaID_WP80[nPhoton]", 	Photon_mvaID_WP80);
    output->add("Events/Photon_mvaID_WP90[nPhoton]", 	Photon_mvaID_WP90);
    output->add("Events/Photon_pdgId[nPhoton]", 	Photon_pdgId);
    output->add("Events/Photon_pfRelIso03_all[nPhoton]",
                 Photon_pfRelIso03_all);
    output->add("Events/Photon_pfRelIso03_chg[nPhoton]",
                 Photon_pfRelIso03_chg);
    output->add("Events/Photon_phi[nPhoton]", 	Photon_phi);
    output->add("Events/Photon_pixelSeed[nPhoton]", 	Photon_pixelSeed);
    output->add("Events/Photon_pt[nPhoton]", 	Photon_pt);
    output->add("Events/Photon_r9[nPhoton]", 	Photon_r9);
    output->add("Events/Photon_seedGain[nPhoton]", 	Photon_seedGain);
    output->add("Events/Photon_sieie[nPhoton]", 	Photon_sieie);
    output->add("Events/Photon_vidNestedWPBitmap[nPhoton]",
                 Photon_vidNestedWPBitmap);
    output->add("Events/Pileup_gpudensity", 	Pileup_gpudensity);
    output->add("Events/Pileup_nPU", 	Pileup_nPU);
    output->add("Events/Pileup_nTrueInt", 	Pileup_nTrueInt);
    output->add("Events/Pileup_pudensity", 	Pileup_pudensity);
    output->add("Events/Pileup_sumEOOT", 	Pileup_sumEOOT);
    output->add("Events/Pileup_sumLOOT", 	Pileup_sumLOOT);
    output->add("Events/PuppiMET_phi", 	PuppiMET_phi);
    output->add("Events/PuppiMET_phiJERDown", 	PuppiMET_phiJERDown);
    output->add("Events/PuppiMET_phiJERUp", 	PuppiMET_phiJERUp);
    output->add("Events/PuppiMET_phiJESDown", 	PuppiMET_phiJESDown);
    output->add("Events/PuppiMET_phiJESUp", 	PuppiMET_phiJESUp);
    output->add("Events/PuppiMET_phiUnclusteredDown",
                 PuppiMET_phiUnclusteredDown);
    output->add("Events/PuppiMET_phiUnclusteredUp",
                 PuppiMET_phiUnclusteredUp);
    output->add("Events/PuppiMET_pt", 	PuppiMET_pt);
    output->add("Events/PuppiMET_ptJERDown", 	PuppiMET_ptJERDown);
    output->add("Events/PuppiMET_ptJERUp", 	PuppiMET_ptJERUp);
    output->add("Events/PuppiMET_ptJESDown", 	PuppiMET_ptJESDown);
    output->add("Events/PuppiMET_ptJESUp", 	PuppiMET_ptJESUp);
    output->add("Events/PuppiMET_ptUnclusteredDown",
                 PuppiMET_ptUnclusteredDown);
    output->add("Events/PuppiMET_ptUnclusteredUp",
                 PuppiMET_ptUnclusteredUp);
    output->add("Events/PuppiMET_sumEt", 	PuppiMET_sumEt);
    output->add("Events/RawMET_phi", 	RawMET_phi);
    output->add("Events/RawMET_pt", 	RawMET_pt);
    output->add("Events/RawMET_sumEt", 	RawMET_sumEt);
    output->add("Events/RawPuppiMET_phi", 	RawPuppiMET_phi);
    output->add("Events/RawPuppiMET_pt", 	RawPuppiMET_pt);
    output->add("Events/RawPuppiMET_sumEt", 	RawPuppiMET_sumEt);
    output->add("Events/SubGenJetAK8_eta[nSubGenJetAK8]",
                 SubGenJetAK8_eta);
    output->add("Events/SubGenJetAK8_mass[nSubGenJetAK8]",
                 SubGenJetAK8_mass);
    output->add("Events/SubGenJetAK8_phi[nSubGenJetAK8]",
                 SubGenJetAK8_phi);
    output->add("Events/SubGenJetAK8_pt[nSubGenJetAK8]", 	SubGenJetAK8_pt);
    output->add("Events/SubJet_btagCSVV2[nSubJet]", 	SubJet_btagCSVV2);
    output->add("Events/SubJet_btagDeepB[nSubJet]", 	SubJet_btagDeepB);
    output->add("Events/SubJet_eta[nSubJet]", 	SubJet_eta);
    output->add("Events/SubJet_hadronFlavour[nSubJet]",
                 SubJet_hadronFlavour);
    output->add("Events/SubJet_mass[nSubJet]", 	SubJet_mass);
    output->add("Events/SubJet_n2b1[nSubJet]", 	SubJet_n2b1);
    output->add("Events/SubJet_n3b1[nSubJet]", 	SubJet_n3b1);
    output->add("Events/SubJet_nBHadrons[nSubJet]", 	SubJet_nBHadrons);
    output->add("Events/SubJet_nCHadrons[nSubJet]", 	SubJet_nCHadrons);
    output->add("Events/SubJet_phi[nSubJet]", 	SubJet_phi);
    output->add("Events/SubJet_pt[nSubJet]", 	SubJet_pt);
    output->add("Events/SubJet_rawFactor[nSubJet]", 	SubJet_rawFactor);
    output->add("Events/SubJet_tau1[nSubJet]", 	SubJet_tau1);
    output->add("Events/SubJet_tau2[nSubJet]", 	SubJet_tau2);
    output->add("Events/SubJet_tau3[nSubJet]", 	SubJet_tau3);
    output->add("Events/SubJet_tau4[nSubJet]", 	SubJet_tau4);
    output->add("Events/Tau_charge[nTau]", 	Tau_charge);
    output->add("Events/Tau_chargedIso[nTau]", 	Tau_chargedIso);
    output->add("Events/Tau_cleanmask[nTau]", 	Tau_cleanmask);
    output->add("Events/Tau_decayMode[nTau]", 	Tau_decayMode);
    output->add("Events/Tau_dxy[nTau]", 	Tau_dxy);
    output->add("Events/Tau_dz[nTau]", 	Tau_dz);
    output->add("Events/Tau_eta[nTau]", 	Tau_eta);
    output->add("Events/Tau_genPartFlav[nTau]", 	Tau_genPartFlav);
    output->add("Events/Tau_genPartIdx[nTau]", 	Tau_genPartIdx);
    output->add("Events/Tau_idAntiEleDeadECal[nTau]",
                 Tau_idAntiEleDeadECal);
    output->add("Events/Tau_idAntiMu[nTau]", 	Tau_idAntiMu);
    output->add("Events/Tau_idDecayModeOldDMs[nTau]",
                 Tau_idDecayModeOldDMs);
    output->add("Events/Tau_idDeepTau2017v2p1VSe[nTau]",
                 Tau_idDeepTau2017v2p1VSe);
    output->add("Events/Tau_idDeepTau2017v2p1VSjet[nTau]",
                 Tau_idDeepTau2017v2p1VSjet);
    output->add("Events/Tau_idDeepTau2017v2p1VSmu[nTau]",
                 Tau_idDeepTau2017v2p1VSmu);
    output->add("Events/Tau_jetIdx[nTau]", 	Tau_jetIdx);
    output->add("Events/Tau_leadTkDeltaEta[nTau]", 	Tau_leadTkDeltaEta);
    output->add("Events/Tau_leadTkDeltaPhi[nTau]", 	Tau_leadTkDeltaPhi);
    output->add("Events/Tau_leadTkPtOverTauPt[nTau]",
                 Tau_leadTkPtOverTauPt);
    output->add("Events/Tau_mass[nTau]", 	Tau_mass);
    output->add("Events/Tau_neutralIso[nTau]", 	Tau_neutralIso);
    output->add("Events/Tau_phi[nTau]", 	Tau_phi);
    output->add("Events/Tau_photonsOutsideSignalCone[nTau]",
                 Tau_photonsOutsideSignalCone);
    output->add("Events/Tau_pt[nTau]", 	Tau_pt);
    output->add("Events/Tau_puCorr[nTau]", 	Tau_puCorr);
    output->add("Events/Tau_rawDeepTau2017v2p1VSe[nTau]",
                 Tau_rawDeepTau2017v2p1VSe);
    output->add("Events/Tau_rawDeepTau2017v2p1VSjet[nTau]",
                 Tau_rawDeepTau2017v2p1VSjet);
    output->add("Events/Tau_rawDeepTau2017v2p1VSmu[nTau]",
                 Tau_rawDeepTau2017v2p1VSmu);
    output->add("Events/Tau_rawIso[nTau]", 	Tau_rawIso);
    output->add("Events/Tau_rawIsodR03[nTau]", 	Tau_rawIsodR03);
    output->add("Events/TkMET_phi", 	TkMET_phi);
    output->add("Events/TkMET_pt", 	TkMET_pt);
    output->add("Events/TkMET_sumEt", 	TkMET_sumEt);
    output->add("Events/TrigObj_eta[nTrigObj]", 	TrigObj_eta);
    output->add("Events/TrigObj_filterBits[nTrigObj]", 	TrigObj_filterBits);
    output->add("Events/TrigObj_id[nTrigObj]", 	TrigObj_id);
    output->add("Events/TrigObj_l1charge[nTrigObj]", 	TrigObj_l1charge);
    output->add("Events/TrigObj_l1iso[nTrigObj]", 	TrigObj_l1iso);
    output->add("Events/TrigObj_l1pt[nTrigObj]", 	TrigObj_l1pt);
    output->add("Events/TrigObj_l1pt_2[nTrigObj]", 	TrigObj_l1pt_2);
    output->add("Events/TrigObj_l2pt[nTrigObj]", 	TrigObj_l2pt);
    output->add("Events/TrigObj_phi[nTrigObj]", 	TrigObj_phi);
    output->add("Events/TrigObj_pt[nTrigObj]", 	TrigObj_pt);
    output->add("Events/boostedTau_charge[nboostedTau]",
                 boostedTau_charge);
    output->add("Events/boostedTau_chargedIso[nboostedTau]",
                 boostedTau_chargedIso);
    output->add("Events/boostedTau_decayMode[nboostedTau]",
                 boostedTau_decayMode);
    output->add("Events/boostedTau_eta[nboostedTau]", 	boostedTau_eta);
    output->add("Events/boostedTau_genPartFlav[nboostedTau]",
                 boostedTau_genPartFlav);
    output->add("Events/boostedTau_genPartIdx[nboostedTau]",
                 boostedTau_genPartIdx);
    output->add("Events/boostedTau_idAntiEle2018[nboostedTau]",
                 boostedTau_idAntiEle2018);
    output->add("Events/boostedTau_idAntiMu[nboostedTau]",
                 boostedTau_idAntiMu);
    output->add("Events/boostedTau_idMVAnewDM2017v2[nboostedTau]",
                 boostedTau_idMVAnewDM2017v2);
    output->add("Events/boostedTau_idMVAoldDM2017v2[nboostedTau]",
                 boostedTau_idMVAoldDM2017v2);
    output->add("Events/boostedTau_idMVAoldDMdR032017v2[nboostedTau]",
                 boostedTau_idMVAoldDMdR032017v2);
    output->add("Events/boostedTau_jetIdx[nboostedTau]",
                 boostedTau_jetIdx);
    output->add("Events/boostedTau_leadTkDeltaEta[nboostedTau]",
                 boostedTau_leadTkDeltaEta);
    output->add("Events/boostedTau_leadTkDeltaPhi[nboostedTau]",
                 boostedTau_leadTkDeltaPhi);
    output->add("Events/boostedTau_leadTkPtOverTauPt[nboostedTau]",
                 boostedTau_leadTkPtOverTauPt);
    output->add("Events/boostedTau_mass[nboostedTau]", 	boostedTau_mass);
    output->add("Events/boostedTau_neutralIso[nboostedTau]",
                 boostedTau_neutralIso);
    output->add("Events/boostedTau_phi[nboostedTau]", 	boostedTau_phi);
    output->add("Events/boostedTau_photonsOutsideSignalCone[nboostedTau]",
                 boostedTau_photonsOutsideSignalCone);
    output->add("Events/boostedTau_pt[nboostedTau]", 	boostedTau_pt);
    output->add("Events/boostedTau_puCorr[nboostedTau]",
                 boostedTau_puCorr);
    output->add("Events/boostedTau_rawAntiEle2018[nboostedTau]",
                 boostedTau_rawAntiEle2018);
    output->add("Events/boostedTau_rawAntiEleCat2018[nboostedTau]",
                 boostedTau_rawAntiEleCat2018);
    output->add("Events/boostedTau_rawIso[nboostedTau]",
                 boostedTau_rawIso);
    output->add("Events/boostedTau_rawIsodR03[nboostedTau]",
                 boostedTau_rawIsodR03);
    output->add("Events/boostedTau_rawMVAnewDM2017v2[nboostedTau]",
                 boostedTau_rawMVAnewDM2017v2);
    output->add("Events/boostedTau_rawMVAoldDM2017v2[nboostedTau]",
                 boostedTau_rawMVAoldDM2017v2);
    output->add("Events/boostedTau_rawMVAoldDMdR032017v2[nboostedTau]",
                 boostedTau_rawMVAoldDMdR032017v2);
    output->add("Events/btagWeight_CSVV2", 	btagWeight_CSVV2);
    output->add("Events/btagWeight_DeepCSVB", 	btagWeight_DeepCSVB);
    output->add("Events/event", 	event);
    output->add("Events/eventWeight", 	eventWeight);
    output->add("Events/fixedGridRhoFastjetAll", 	fixedGridRhoFastjetAll);
    output->add("Events/fixedGridRhoFastjetCentral",
                 fixedGridRhoFastjetCentral);
    output->add("Events/fixedGridRhoFastjetCentralCalo",
                 fixedGridRhoFastjetCentralCalo);
    output->add("Events/fixedGridRhoFastjetCentralChargedPileUp",
                 fixedGridRhoFastjetCentralChargedPileUp);
    output->add("Events/fixedGridRhoFastjetCentralNeutral",
                 fixedGridRhoFastjetCentralNeutral);
    output->add("Events/genTtbarId", 	genTtbarId);
    output->add("Events/genWeight", 	genWeight);
    output->add("Events/luminosityBlock", 	luminosityBlock);
    output->add("Events/puWeight", 	puWeight);
    output->add("Events/puWeightDown", 	puWeightDown);
    output->add("Events/puWeightUp", 	puWeightUp);
    output->add("Events/run", 	run);

  }

  void initBuffers()
  {
    CorrT1METJet_area	= std::vector<float>(45,0);
    CorrT1METJet_eta	= std::vector<float>(45,0);
    CorrT1METJet_muonSubtrFactor	= std::vector<float>(45,0);
    CorrT1METJet_phi	= std::vector<float>(45,0);
    CorrT1METJet_rawPt	= std::vector<float>(45,0);
    Electron_charge	= std::vector<int>(25,0);
    Electron_cleanmask	= std::vector<int>(25,0);
    Electron_convVeto	= std::vector<bool>(25,0);
    Electron_cutBased	= std::vector<int>(25,0);
    Electron_cutBased_HEEP	= std::vector<bool>(25,0);
    Electron_dEscaleDown	= std::vector<float>(25,0);
    Electron_dEscaleUp	= std::vector<float>(25,0);
    Electron_dEsigmaDown	= std::vector<float>(25,0);
    Electron_dEsigmaUp	= std::vector<float>(25,0);
    Electron_deltaEtaSC	= std::vector<float>(25,0);
    Electron_dr03EcalRecHitSumEt	= std::vector<float>(25,0);
    Electron_dr03HcalDepth1TowerSumEt	= std::vector<float>(25,0);
    Electron_dr03TkSumPt	= std::vector<float>(25,0);
    Electron_dr03TkSumPtHEEP	= std::vector<float>(25,0);
    Electron_dxy	= std::vector<float>(25,0);
    Electron_dxyErr	= std::vector<float>(25,0);
    Electron_dz	= std::vector<float>(25,0);
    Electron_dzErr	= std::vector<float>(25,0);
    Electron_eCorr	= std::vector<float>(25,0);
    Electron_eInvMinusPInv	= std::vector<float>(25,0);
    Electron_energyErr	= std::vector<float>(25,0);
    Electron_eta	= std::vector<float>(25,0);
    Electron_genPartFlav	= std::vector<int>(25,0);
    Electron_genPartIdx	= std::vector<int>(25,0);
    Electron_hoe	= std::vector<float>(25,0);
    Electron_ip3d	= std::vector<float>(25,0);
    Electron_isPFcand	= std::vector<bool>(25,0);
    Electron_jetIdx	= std::vector<int>(25,0);
    Electron_jetNDauCharged	= std::vector<int>(25,0);
    Electron_jetPtRelv2	= std::vector<float>(25,0);
    Electron_jetRelIso	= std::vector<float>(25,0);
    Electron_lostHits	= std::vector<int>(25,0);
    Electron_mass	= std::vector<float>(25,0);
    Electron_miniPFRelIso_all	= std::vector<float>(25,0);
    Electron_miniPFRelIso_chg	= std::vector<float>(25,0);
    Electron_mvaFall17V2Iso	= std::vector<float>(25,0);
    Electron_mvaFall17V2Iso_WP80	= std::vector<bool>(25,0);
    Electron_mvaFall17V2Iso_WP90	= std::vector<bool>(25,0);
    Electron_mvaFall17V2Iso_WPL	= std::vector<bool>(25,0);
    Electron_mvaFall17V2noIso	= std::vector<float>(25,0);
    Electron_mvaFall17V2noIso_WP80	= std::vector<bool>(25,0);
    Electron_mvaFall17V2noIso_WP90	= std::vector<bool>(25,0);
    Electron_mvaFall17V2noIso_WPL	= std::vector<bool>(25,0);
    Electron_mvaTTH	= std::vector<float>(25,0);
    Electron_pdgId	= std::vector<int>(25,0);
    Electron_pfRelIso03_all	= std::vector<float>(25,0);
    Electron_pfRelIso03_chg	= std::vector<float>(25,0);
    Electron_phi	= std::vector<float>(25,0);
    Electron_photonIdx	= std::vector<int>(25,0);
    Electron_pt	= std::vector<float>(25,0);
    Electron_r9	= std::vector<float>(25,0);
    Electron_scEtOverPt	= std::vector<float>(25,0);
    Electron_seedGain	= std::vector<int>(25,0);
    Electron_sieie	= std::vector<float>(25,0);
    Electron_sip3d	= std::vector<float>(25,0);
    Electron_tightCharge	= std::vector<int>(25,0);
    Electron_vidNestedWPBitmap	= std::vector<int>(25,0);
    Electron_vidNestedWPBitmapHEEP	= std::vector<int>(25,0);
    FatJet_area	= std::vector<float>(25,0);
    FatJet_btagCSVV2	= std::vector<float>(25,0);
    FatJet_btagDDBvLV2	= std::vector<float>(25,0);
    FatJet_btagDDCvBV2	= std::vector<float>(25,0);
    FatJet_btagDDCvLV2	= std::vector<float>(25,0);
    FatJet_btagDeepB	= std::vector<float>(25,0);
    FatJet_btagHbb	= std::vector<float>(25,0);
    FatJet_corr_JEC	= std::vector<float>(25,0);
    FatJet_corr_JER	= std::vector<float>(25,0);
    FatJet_corr_JMR	= std::vector<float>(25,0);
    FatJet_corr_JMS	= std::vector<float>(25,0);
    FatJet_deepTagMD_H4qvsQCD	= std::vector<float>(25,0);
    FatJet_deepTagMD_HbbvsQCD	= std::vector<float>(25,0);
    FatJet_deepTagMD_TvsQCD	= std::vector<float>(25,0);
    FatJet_deepTagMD_WvsQCD	= std::vector<float>(25,0);
    FatJet_deepTagMD_ZHbbvsQCD	= std::vector<float>(25,0);
    FatJet_deepTagMD_ZHccvsQCD	= std::vector<float>(25,0);
    FatJet_deepTagMD_ZbbvsQCD	= std::vector<float>(25,0);
    FatJet_deepTagMD_ZvsQCD	= std::vector<float>(25,0);
    FatJet_deepTagMD_bbvsLight	= std::vector<float>(25,0);
    FatJet_deepTagMD_ccvsLight	= std::vector<float>(25,0);
    FatJet_deepTag_H	= std::vector<float>(25,0);
    FatJet_deepTag_QCD	= std::vector<float>(25,0);
    FatJet_deepTag_QCDothers	= std::vector<float>(25,0);
    FatJet_deepTag_TvsQCD	= std::vector<float>(25,0);
    FatJet_deepTag_WvsQCD	= std::vector<float>(25,0);
    FatJet_deepTag_ZvsQCD	= std::vector<float>(25,0);
    FatJet_electronIdx3SJ	= std::vector<int>(25,0);
    FatJet_eta	= std::vector<float>(25,0);
    FatJet_genJetAK8Idx	= std::vector<int>(25,0);
    FatJet_hadronFlavour	= std::vector<int>(25,0);
    FatJet_jetId	= std::vector<int>(25,0);
    FatJet_lsf3	= std::vector<float>(25,0);
    FatJet_mass	= std::vector<float>(25,0);
    FatJet_mass_jerDown	= std::vector<float>(25,0);
    FatJet_mass_jerUp	= std::vector<float>(25,0);
    FatJet_mass_jesTotalDown	= std::vector<float>(25,0);
    FatJet_mass_jesTotalUp	= std::vector<float>(25,0);
    FatJet_mass_jmrDown	= std::vector<float>(25,0);
    FatJet_mass_jmrUp	= std::vector<float>(25,0);
    FatJet_mass_jmsDown	= std::vector<float>(25,0);
    FatJet_mass_jmsUp	= std::vector<float>(25,0);
    FatJet_mass_nom	= std::vector<float>(25,0);
    FatJet_mass_raw	= std::vector<float>(25,0);
    FatJet_msoftdrop	= std::vector<float>(25,0);
    FatJet_msoftdrop_corr_JMR	= std::vector<float>(25,0);
    FatJet_msoftdrop_corr_JMS	= std::vector<float>(25,0);
    FatJet_msoftdrop_corr_PUPPI	= std::vector<float>(25,0);
    FatJet_msoftdrop_jerDown	= std::vector<float>(25,0);
    FatJet_msoftdrop_jerUp	= std::vector<float>(25,0);
    FatJet_msoftdrop_jesTotalDown	= std::vector<float>(25,0);
    FatJet_msoftdrop_jesTotalUp	= std::vector<float>(25,0);
    FatJet_msoftdrop_jmrDown	= std::vector<float>(25,0);
    FatJet_msoftdrop_jmrUp	= std::vector<float>(25,0);
    FatJet_msoftdrop_jmsDown	= std::vector<float>(25,0);
    FatJet_msoftdrop_jmsUp	= std::vector<float>(25,0);
    FatJet_msoftdrop_nom	= std::vector<float>(25,0);
    FatJet_msoftdrop_raw	= std::vector<float>(25,0);
    FatJet_msoftdrop_tau21DDT_jerDown	= std::vector<float>(25,0);
    FatJet_msoftdrop_tau21DDT_jerUp	= std::vector<float>(25,0);
    FatJet_msoftdrop_tau21DDT_jmrDown	= std::vector<float>(25,0);
    FatJet_msoftdrop_tau21DDT_jmrUp	= std::vector<float>(25,0);
    FatJet_msoftdrop_tau21DDT_jmsDown	= std::vector<float>(25,0);
    FatJet_msoftdrop_tau21DDT_jmsUp	= std::vector<float>(25,0);
    FatJet_msoftdrop_tau21DDT_nom	= std::vector<float>(25,0);
    FatJet_muonIdx3SJ	= std::vector<int>(25,0);
    FatJet_n2b1	= std::vector<float>(25,0);
    FatJet_n3b1	= std::vector<float>(25,0);
    FatJet_nBHadrons	= std::vector<int>(25,0);
    FatJet_nCHadrons	= std::vector<int>(25,0);
    FatJet_nConstituents	= std::vector<int>(25,0);
    FatJet_particleNetMD_QCD	= std::vector<float>(25,0);
    FatJet_particleNetMD_Xbb	= std::vector<float>(25,0);
    FatJet_particleNetMD_Xcc	= std::vector<float>(25,0);
    FatJet_particleNetMD_Xqq	= std::vector<float>(25,0);
    FatJet_particleNet_H4qvsQCD	= std::vector<float>(25,0);
    FatJet_particleNet_HbbvsQCD	= std::vector<float>(25,0);
    FatJet_particleNet_HccvsQCD	= std::vector<float>(25,0);
    FatJet_particleNet_QCD	= std::vector<float>(25,0);
    FatJet_particleNet_TvsQCD	= std::vector<float>(25,0);
    FatJet_particleNet_WvsQCD	= std::vector<float>(25,0);
    FatJet_particleNet_ZvsQCD	= std::vector<float>(25,0);
    FatJet_particleNet_mass	= std::vector<float>(25,0);
    FatJet_phi	= std::vector<float>(25,0);
    FatJet_pt	= std::vector<float>(25,0);
    FatJet_pt_jerDown	= std::vector<float>(25,0);
    FatJet_pt_jerUp	= std::vector<float>(25,0);
    FatJet_pt_jesTotalDown	= std::vector<float>(25,0);
    FatJet_pt_jesTotalUp	= std::vector<float>(25,0);
    FatJet_pt_nom	= std::vector<float>(25,0);
    FatJet_pt_raw	= std::vector<float>(25,0);
    FatJet_rawFactor	= std::vector<float>(25,0);
    FatJet_subJetIdx1	= std::vector<int>(25,0);
    FatJet_subJetIdx2	= std::vector<int>(25,0);
    FatJet_tau1	= std::vector<float>(25,0);
    FatJet_tau2	= std::vector<float>(25,0);
    FatJet_tau3	= std::vector<float>(25,0);
    FatJet_tau4	= std::vector<float>(25,0);
    FsrPhoton_dROverEt2	= std::vector<float>(15,0);
    FsrPhoton_eta	= std::vector<float>(15,0);
    FsrPhoton_muonIdx	= std::vector<int>(15,0);
    FsrPhoton_phi	= std::vector<float>(15,0);
    FsrPhoton_pt	= std::vector<float>(15,0);
    FsrPhoton_relIso03	= std::vector<float>(15,0);
    GenIsolatedPhoton_eta	= std::vector<float>(10,0);
    GenIsolatedPhoton_mass	= std::vector<float>(10,0);
    GenIsolatedPhoton_phi	= std::vector<float>(10,0);
    GenIsolatedPhoton_pt	= std::vector<float>(10,0);
    GenJetAK8_eta	= std::vector<float>(25,0);
    GenJetAK8_hadronFlavour	= std::vector<int>(25,0);
    GenJetAK8_mass	= std::vector<float>(25,0);
    GenJetAK8_partonFlavour	= std::vector<int>(25,0);
    GenJetAK8_phi	= std::vector<float>(25,0);
    GenJetAK8_pt	= std::vector<float>(25,0);
    GenJet_eta	= std::vector<float>(45,0);
    GenJet_hadronFlavour	= std::vector<int>(45,0);
    GenJet_mass	= std::vector<float>(45,0);
    GenJet_partonFlavour	= std::vector<int>(45,0);
    GenJet_phi	= std::vector<float>(45,0);
    GenJet_pt	= std::vector<float>(45,0);
    GenPart_eta	= std::vector<float>(185,0);
    GenPart_genPartIdxMother	= std::vector<int>(185,0);
    GenPart_mass	= std::vector<float>(185,0);
    GenPart_pdgId	= std::vector<int>(185,0);
    GenPart_phi	= std::vector<float>(185,0);
    GenPart_pt	= std::vector<float>(185,0);
    GenPart_status	= std::vector<int>(185,0);
    GenPart_statusFlags	= std::vector<int>(185,0);
    IsoTrack_charge	= std::vector<int>(25,0);
    IsoTrack_dxy	= std::vector<float>(25,0);
    IsoTrack_dz	= std::vector<float>(25,0);
    IsoTrack_eta	= std::vector<float>(25,0);
    IsoTrack_fromPV	= std::vector<int>(25,0);
    IsoTrack_isFromLostTrack	= std::vector<bool>(25,0);
    IsoTrack_isHighPurityTrack	= std::vector<bool>(25,0);
    IsoTrack_isPFcand	= std::vector<bool>(25,0);
    IsoTrack_miniPFRelIso_all	= std::vector<float>(25,0);
    IsoTrack_miniPFRelIso_chg	= std::vector<float>(25,0);
    IsoTrack_pdgId	= std::vector<int>(25,0);
    IsoTrack_pfRelIso03_all	= std::vector<float>(25,0);
    IsoTrack_pfRelIso03_chg	= std::vector<float>(25,0);
    IsoTrack_phi	= std::vector<float>(25,0);
    IsoTrack_pt	= std::vector<float>(25,0);
    Jet_area	= std::vector<float>(45,0);
    Jet_bRegCorr	= std::vector<float>(45,0);
    Jet_bRegRes	= std::vector<float>(45,0);
    Jet_btagCSVV2	= std::vector<float>(45,0);
    Jet_btagDeepB	= std::vector<float>(45,0);
    Jet_btagDeepCvB	= std::vector<float>(45,0);
    Jet_btagDeepCvL	= std::vector<float>(45,0);
    Jet_btagDeepFlavB	= std::vector<float>(45,0);
    Jet_btagDeepFlavCvB	= std::vector<float>(45,0);
    Jet_btagDeepFlavCvL	= std::vector<float>(45,0);
    Jet_btagDeepFlavQG	= std::vector<float>(45,0);
    Jet_cRegCorr	= std::vector<float>(45,0);
    Jet_cRegRes	= std::vector<float>(45,0);
    Jet_chEmEF	= std::vector<float>(45,0);
    Jet_chFPV0EF	= std::vector<float>(45,0);
    Jet_chHEF	= std::vector<float>(45,0);
    Jet_cleanmask	= std::vector<int>(45,0);
    Jet_corr_JEC	= std::vector<float>(45,0);
    Jet_corr_JER	= std::vector<float>(45,0);
    Jet_electronIdx1	= std::vector<int>(45,0);
    Jet_electronIdx2	= std::vector<int>(45,0);
    Jet_eta	= std::vector<float>(45,0);
    Jet_genJetIdx	= std::vector<int>(45,0);
    Jet_hadronFlavour	= std::vector<int>(45,0);
    Jet_hfadjacentEtaStripsSize	= std::vector<int>(45,0);
    Jet_hfcentralEtaStripSize	= std::vector<int>(45,0);
    Jet_hfsigmaEtaEta	= std::vector<float>(45,0);
    Jet_hfsigmaPhiPhi	= std::vector<float>(45,0);
    Jet_jetId	= std::vector<int>(45,0);
    Jet_mass	= std::vector<float>(45,0);
    Jet_mass_jerDown	= std::vector<float>(45,0);
    Jet_mass_jerUp	= std::vector<float>(45,0);
    Jet_mass_jesTotalDown	= std::vector<float>(45,0);
    Jet_mass_jesTotalUp	= std::vector<float>(45,0);
    Jet_mass_nom	= std::vector<float>(45,0);
    Jet_mass_raw	= std::vector<float>(45,0);
    Jet_muEF	= std::vector<float>(45,0);
    Jet_muonIdx1	= std::vector<int>(45,0);
    Jet_muonIdx2	= std::vector<int>(45,0);
    Jet_muonSubtrFactor	= std::vector<float>(45,0);
    Jet_nConstituents	= std::vector<int>(45,0);
    Jet_nElectrons	= std::vector<int>(45,0);
    Jet_nMuons	= std::vector<int>(45,0);
    Jet_neEmEF	= std::vector<float>(45,0);
    Jet_neHEF	= std::vector<float>(45,0);
    Jet_partonFlavour	= std::vector<int>(45,0);
    Jet_phi	= std::vector<float>(45,0);
    Jet_pt	= std::vector<float>(45,0);
    Jet_pt_jerDown	= std::vector<float>(45,0);
    Jet_pt_jerUp	= std::vector<float>(45,0);
    Jet_pt_jesTotalDown	= std::vector<float>(45,0);
    Jet_pt_jesTotalUp	= std::vector<float>(45,0);
    Jet_pt_nom	= std::vector<float>(45,0);
    Jet_pt_raw	= std::vector<float>(45,0);
    Jet_puId	= std::vector<int>(45,0);
    Jet_puIdDisc	= std::vector<float>(45,0);
    Jet_qgl	= std::vector<float>(45,0);
    Jet_rawFactor	= std::vector<float>(45,0);
    LHEPart_eta	= std::vector<float>(25,0);
    LHEPart_incomingpz	= std::vector<float>(25,0);
    LHEPart_mass	= std::vector<float>(25,0);
    LHEPart_pdgId	= std::vector<int>(25,0);
    LHEPart_phi	= std::vector<float>(25,0);
    LHEPart_pt	= std::vector<float>(25,0);
    LHEPart_spin	= std::vector<int>(25,0);
    LHEPart_status	= std::vector<int>(25,0);
    LHEPdfWeight	= std::vector<float>(155,0);
    LHEReweightingWeight	= std::vector<float>(100,0);
    LHEScaleWeight	= std::vector<float>(25,0);
    Muon_charge	= std::vector<int>(25,0);
    Muon_cleanmask	= std::vector<int>(25,0);
    Muon_dxy	= std::vector<float>(25,0);
    Muon_dxyErr	= std::vector<float>(25,0);
    Muon_dxybs	= std::vector<float>(25,0);
    Muon_dz	= std::vector<float>(25,0);
    Muon_dzErr	= std::vector<float>(25,0);
    Muon_eta	= std::vector<float>(25,0);
    Muon_fsrPhotonIdx	= std::vector<int>(25,0);
    Muon_genPartFlav	= std::vector<int>(25,0);
    Muon_genPartIdx	= std::vector<int>(25,0);
    Muon_highPtId	= std::vector<int>(25,0);
    Muon_highPurity	= std::vector<bool>(25,0);
    Muon_inTimeMuon	= std::vector<bool>(25,0);
    Muon_ip3d	= std::vector<float>(25,0);
    Muon_isGlobal	= std::vector<bool>(25,0);
    Muon_isPFcand	= std::vector<bool>(25,0);
    Muon_isStandalone	= std::vector<bool>(25,0);
    Muon_isTracker	= std::vector<bool>(25,0);
    Muon_jetIdx	= std::vector<int>(25,0);
    Muon_jetNDauCharged	= std::vector<int>(25,0);
    Muon_jetPtRelv2	= std::vector<float>(25,0);
    Muon_jetRelIso	= std::vector<float>(25,0);
    Muon_looseId	= std::vector<bool>(25,0);
    Muon_mass	= std::vector<float>(25,0);
    Muon_mediumId	= std::vector<bool>(25,0);
    Muon_mediumPromptId	= std::vector<bool>(25,0);
    Muon_miniIsoId	= std::vector<int>(25,0);
    Muon_miniPFRelIso_all	= std::vector<float>(25,0);
    Muon_miniPFRelIso_chg	= std::vector<float>(25,0);
    Muon_multiIsoId	= std::vector<int>(25,0);
    Muon_mvaId	= std::vector<int>(25,0);
    Muon_mvaLowPt	= std::vector<float>(25,0);
    Muon_mvaLowPtId	= std::vector<int>(25,0);
    Muon_mvaTTH	= std::vector<float>(25,0);
    Muon_nStations	= std::vector<int>(25,0);
    Muon_nTrackerLayers	= std::vector<int>(25,0);
    Muon_pdgId	= std::vector<int>(25,0);
    Muon_pfIsoId	= std::vector<int>(25,0);
    Muon_pfRelIso03_all	= std::vector<float>(25,0);
    Muon_pfRelIso03_chg	= std::vector<float>(25,0);
    Muon_pfRelIso04_all	= std::vector<float>(25,0);
    Muon_phi	= std::vector<float>(25,0);
    Muon_pt	= std::vector<float>(25,0);
    Muon_ptErr	= std::vector<float>(25,0);
    Muon_puppiIsoId	= std::vector<int>(25,0);
    Muon_segmentComp	= std::vector<float>(25,0);
    Muon_sip3d	= std::vector<float>(25,0);
    Muon_softId	= std::vector<bool>(25,0);
    Muon_softMva	= std::vector<float>(25,0);
    Muon_softMvaId	= std::vector<bool>(25,0);
    Muon_tightCharge	= std::vector<int>(25,0);
    Muon_tightId	= std::vector<bool>(25,0);
    Muon_tkIsoId	= std::vector<int>(25,0);
    Muon_tkRelIso	= std::vector<float>(25,0);
    Muon_triggerIdLoose	= std::vector<bool>(25,0);
    Muon_tunepRelPt	= std::vector<float>(25,0);
    OtherPV_z	= std::vector<float>(15,0);
    PSWeight	= std::vector<float>(15,0);
    Photon_charge	= std::vector<int>(25,0);
    Photon_cleanmask	= std::vector<int>(25,0);
    Photon_cutBased	= std::vector<int>(25,0);
    Photon_cutBased_Fall17V1Bitmap	= std::vector<int>(25,0);
    Photon_dEscaleDown	= std::vector<float>(25,0);
    Photon_dEscaleUp	= std::vector<float>(25,0);
    Photon_dEsigmaDown	= std::vector<float>(25,0);
    Photon_dEsigmaUp	= std::vector<float>(25,0);
    Photon_eCorr	= std::vector<float>(25,0);
    Photon_electronIdx	= std::vector<int>(25,0);
    Photon_electronVeto	= std::vector<bool>(25,0);
    Photon_energyErr	= std::vector<float>(25,0);
    Photon_eta	= std::vector<float>(25,0);
    Photon_genPartFlav	= std::vector<int>(25,0);
    Photon_genPartIdx	= std::vector<int>(25,0);
    Photon_hoe	= std::vector<float>(25,0);
    Photon_isScEtaEB	= std::vector<bool>(25,0);
    Photon_isScEtaEE	= std::vector<bool>(25,0);
    Photon_jetIdx	= std::vector<int>(25,0);
    Photon_mass	= std::vector<float>(25,0);
    Photon_mvaID	= std::vector<float>(25,0);
    Photon_mvaID_Fall17V1p1	= std::vector<float>(25,0);
    Photon_mvaID_WP80	= std::vector<bool>(25,0);
    Photon_mvaID_WP90	= std::vector<bool>(25,0);
    Photon_pdgId	= std::vector<int>(25,0);
    Photon_pfRelIso03_all	= std::vector<float>(25,0);
    Photon_pfRelIso03_chg	= std::vector<float>(25,0);
    Photon_phi	= std::vector<float>(25,0);
    Photon_pixelSeed	= std::vector<bool>(25,0);
    Photon_pt	= std::vector<float>(25,0);
    Photon_r9	= std::vector<float>(25,0);
    Photon_seedGain	= std::vector<int>(25,0);
    Photon_sieie	= std::vector<float>(25,0);
    Photon_vidNestedWPBitmap	= std::vector<int>(25,0);
    SubGenJetAK8_eta	= std::vector<float>(35,0);
    SubGenJetAK8_mass	= std::vector<float>(35,0);
    SubGenJetAK8_phi	= std::vector<float>(35,0);
    SubGenJetAK8_pt	= std::vector<float>(35,0);
    SubJet_btagCSVV2	= std::vector<float>(30,0);
    SubJet_btagDeepB	= std::vector<float>(30,0);
    SubJet_eta	= std::vector<float>(30,0);
    SubJet_hadronFlavour	= std::vector<int>(30,0);
    SubJet_mass	= std::vector<float>(30,0);
    SubJet_n2b1	= std::vector<float>(30,0);
    SubJet_n3b1	= std::vector<float>(30,0);
    SubJet_nBHadrons	= std::vector<int>(30,0);
    SubJet_nCHadrons	= std::vector<int>(30,0);
    SubJet_phi	= std::vector<float>(30,0);
    SubJet_pt	= std::vector<float>(30,0);
    SubJet_rawFactor	= std::vector<float>(30,0);
    SubJet_tau1	= std::vector<float>(30,0);
    SubJet_tau2	= std::vector<float>(30,0);
    SubJet_tau3	= std::vector<float>(30,0);
    SubJet_tau4	= std::vector<float>(30,0);
    Tau_charge	= std::vector<int>(20,0);
    Tau_chargedIso	= std::vector<float>(20,0);
    Tau_cleanmask	= std::vector<int>(20,0);
    Tau_decayMode	= std::vector<int>(20,0);
    Tau_dxy	= std::vector<float>(20,0);
    Tau_dz	= std::vector<float>(20,0);
    Tau_eta	= std::vector<float>(20,0);
    Tau_genPartFlav	= std::vector<int>(20,0);
    Tau_genPartIdx	= std::vector<int>(20,0);
    Tau_idAntiEleDeadECal	= std::vector<bool>(20,0);
    Tau_idAntiMu	= std::vector<int>(20,0);
    Tau_idDecayModeOldDMs	= std::vector<bool>(20,0);
    Tau_idDeepTau2017v2p1VSe	= std::vector<int>(20,0);
    Tau_idDeepTau2017v2p1VSjet	= std::vector<int>(20,0);
    Tau_idDeepTau2017v2p1VSmu	= std::vector<int>(20,0);
    Tau_jetIdx	= std::vector<int>(20,0);
    Tau_leadTkDeltaEta	= std::vector<float>(20,0);
    Tau_leadTkDeltaPhi	= std::vector<float>(20,0);
    Tau_leadTkPtOverTauPt	= std::vector<float>(20,0);
    Tau_mass	= std::vector<float>(20,0);
    Tau_neutralIso	= std::vector<float>(20,0);
    Tau_phi	= std::vector<float>(20,0);
    Tau_photonsOutsideSignalCone	= std::vector<float>(20,0);
    Tau_pt	= std::vector<float>(20,0);
    Tau_puCorr	= std::vector<float>(20,0);
    Tau_rawDeepTau2017v2p1VSe	= std::vector<float>(20,0);
    Tau_rawDeepTau2017v2p1VSjet	= std::vector<float>(20,0);
    Tau_rawDeepTau2017v2p1VSmu	= std::vector<float>(20,0);
    Tau_rawIso	= std::vector<float>(20,0);
    Tau_rawIsodR03	= std::vector<float>(20,0);
    TrigObj_eta	= std::vector<float>(75,0);
    TrigObj_filterBits	= std::vector<int>(75,0);
    TrigObj_id	= std::vector<int>(75,0);
    TrigObj_l1charge	= std::vector<int>(75,0);
    TrigObj_l1iso	= std::vector<int>(75,0);
    TrigObj_l1pt	= std::vector<float>(75,0);
    TrigObj_l1pt_2	= std::vector<float>(75,0);
    TrigObj_l2pt	= std::vector<float>(75,0);
    TrigObj_phi	= std::vector<float>(75,0);
    TrigObj_pt	= std::vector<float>(75,0);
    boostedTau_charge	= std::vector<int>(15,0);
    boostedTau_chargedIso	= std::vector<float>(15,0);
    boostedTau_decayMode	= std::vector<int>(15,0);
    boostedTau_eta	= std::vector<float>(15,0);
    boostedTau_genPartFlav	= std::vector<int>(15,0);
    boostedTau_genPartIdx	= std::vector<int>(15,0);
    boostedTau_idAntiEle2018	= std::vector<int>(15,0);
    boostedTau_idAntiMu	= std::vector<int>(15,0);
    boostedTau_idMVAnewDM2017v2	= std::vector<int>(15,0);
    boostedTau_idMVAoldDM2017v2	= std::vector<int>(15,0);
    boostedTau_idMVAoldDMdR032017v2	= std::vector<int>(15,0);
    boostedTau_jetIdx	= std::vector<int>(15,0);
    boostedTau_leadTkDeltaEta	= std::vector<float>(15,0);
    boostedTau_leadTkDeltaPhi	= std::vector<float>(15,0);
    boostedTau_leadTkPtOverTauPt	= std::vector<float>(15,0);
    boostedTau_mass	= std::vector<float>(15,0);
    boostedTau_neutralIso	= std::vector<float>(15,0);
    boostedTau_phi	= std::vector<float>(15,0);
    boostedTau_photonsOutsideSignalCone	= std::vector<float>(15,0);
    boostedTau_pt	= std::vector<float>(15,0);
    boostedTau_puCorr	= std::vector<float>(15,0);
    boostedTau_rawAntiEle2018	= std::vector<float>(15,0);
    boostedTau_rawAntiEleCat2018	= std::vector<int>(15,0);
    boostedTau_rawIso	= std::vector<float>(15,0);
    boostedTau_rawIsodR03	= std::vector<float>(15,0);
    boostedTau_rawMVAnewDM2017v2	= std::vector<float>(15,0);
    boostedTau_rawMVAoldDM2017v2	= std::vector<float>(15,0);
    boostedTau_rawMVAoldDMdR032017v2	= std::vector<float>(15,0);
    CorrT1METJet	= std::vector<eventBuffer::CorrT1METJet_s>(45);
    Electron	= std::vector<eventBuffer::Electron_s>(25);
    FatJet	= std::vector<eventBuffer::FatJet_s>(25);
    FsrPhoton	= std::vector<eventBuffer::FsrPhoton_s>(15);
    GenIsolatedPhoton	= std::vector<eventBuffer::GenIsolatedPhoton_s>(10);
    GenJet	= std::vector<eventBuffer::GenJet_s>(45);
    GenJetAK8	= std::vector<eventBuffer::GenJetAK8_s>(25);
    GenPart	= std::vector<eventBuffer::GenPart_s>(185);
    IsoTrack	= std::vector<eventBuffer::IsoTrack_s>(25);
    Jet	= std::vector<eventBuffer::Jet_s>(45);
    LHEPart	= std::vector<eventBuffer::LHEPart_s>(25);
    Muon	= std::vector<eventBuffer::Muon_s>(25);
    Photon	= std::vector<eventBuffer::Photon_s>(25);
    SubGenJetAK8	= std::vector<eventBuffer::SubGenJetAK8_s>(35);
    SubJet	= std::vector<eventBuffer::SubJet_s>(30);
    Tau	= std::vector<eventBuffer::Tau_s>(20);
    TrigObj	= std::vector<eventBuffer::TrigObj_s>(75);
    boostedTau	= std::vector<eventBuffer::boostedTau_s>(15);

  }
      
  void read(int entry)
  {
    if ( !input ) 
      { 
        std::cout << "** eventBuffer::read - first  call read-only constructor!"
                  << std::endl;
        assert(0);
      }
    input->read(entry);

    // clear indexmap
    for(std::map<std::string, std::vector<int> >::iterator
    item=indexmap.begin(); 
    item != indexmap.end();
    ++item)
    item->second.clear();
  }

  void select(std::string objname)
  {
    indexmap[objname] = std::vector<int>();
  }

  void select(std::string objname, int index)
  {
    try
     {
       indexmap[objname].push_back(index);
     }
    catch (...)
     {
       std::cout << "** eventBuffer::select - first call select(""" 
                 << objname << """)" 
                 << std::endl;
       assert(0);
    }
  }

 void ls()
 {
   if( input ) input->ls();
 }

 int size()
 {
   if( input ) 
     return input->size();
   else
     return 0;
 }

 void close()
 {
   if( input )   input->close();
   if( output ) output->close();
 }

 // --- indexmap keeps track of which objects have been flagged for selection
 std::map<std::string, std::vector<int> > indexmap;

 // to read events
 itreestream* input;

 // to write events
 otreestream* output;

 // switches for choosing branches
 std::map<std::string, bool> choose;

}; 
#endif
