#ifndef EVENTBUFFER_H
#define EVENTBUFFER_H
//----------------------------------------------------------------------------
// File:        eventBuffer.h
// Description: Analyzer header for ntuples created by TheNtupleMaker
// Created:     Mon Mar  2 00:15:55 2020 by mkanalyzer.py v2.0.1 23-Mar-2019
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

struct eventBuffer
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
  std::vector<int>	Electron_cutBased_Fall17_V1;
  std::vector<bool>	Electron_cutBased_HEEP;
  std::vector<int>	Electron_cutBased_HLTPreSel;
  std::vector<int>	Electron_cutBased_Spring15;
  std::vector<int>	Electron_cutBased_Sum16;
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
  std::vector<float>	Electron_jetPtRelv2;
  std::vector<float>	Electron_jetRelIso;
  std::vector<int>	Electron_lostHits;
  std::vector<float>	Electron_mass;
  std::vector<float>	Electron_miniPFRelIso_all;
  std::vector<float>	Electron_miniPFRelIso_chg;
  std::vector<float>	Electron_mvaFall17V1Iso;
  std::vector<bool>	Electron_mvaFall17V1Iso_WP80;
  std::vector<bool>	Electron_mvaFall17V1Iso_WP90;
  std::vector<bool>	Electron_mvaFall17V1Iso_WPL;
  std::vector<float>	Electron_mvaFall17V1noIso;
  std::vector<bool>	Electron_mvaFall17V1noIso_WP80;
  std::vector<bool>	Electron_mvaFall17V1noIso_WP90;
  std::vector<bool>	Electron_mvaFall17V1noIso_WPL;
  std::vector<float>	Electron_mvaFall17V2Iso;
  std::vector<bool>	Electron_mvaFall17V2Iso_WP80;
  std::vector<bool>	Electron_mvaFall17V2Iso_WP90;
  std::vector<bool>	Electron_mvaFall17V2Iso_WPL;
  std::vector<float>	Electron_mvaFall17V2noIso;
  std::vector<bool>	Electron_mvaFall17V2noIso_WP80;
  std::vector<bool>	Electron_mvaFall17V2noIso_WP90;
  std::vector<bool>	Electron_mvaFall17V2noIso_WPL;
  std::vector<float>	Electron_mvaSpring16GP;
  std::vector<bool>	Electron_mvaSpring16GP_WP80;
  std::vector<bool>	Electron_mvaSpring16GP_WP90;
  std::vector<float>	Electron_mvaSpring16HZZ;
  std::vector<bool>	Electron_mvaSpring16HZZ_WPL;
  std::vector<float>	Electron_mvaTTH;
  std::vector<int>	Electron_pdgId;
  std::vector<float>	Electron_pfRelIso03_all;
  std::vector<float>	Electron_pfRelIso03_chg;
  std::vector<float>	Electron_phi;
  std::vector<int>	Electron_photonIdx;
  std::vector<float>	Electron_pt;
  std::vector<float>	Electron_r9;
  std::vector<int>	Electron_seedGain;
  std::vector<float>	Electron_sieie;
  std::vector<float>	Electron_sip3d;
  std::vector<int>	Electron_tightCharge;
  std::vector<int>	Electron_vidNestedWPBitmap;
  std::vector<int>	Electron_vidNestedWPBitmapHEEP;
  std::vector<int>	Electron_vidNestedWPBitmapSpring15;
  std::vector<int>	Electron_vidNestedWPBitmapSum16;
  std::vector<float>	FatJet_area;
  std::vector<float>	FatJet_btagCMVA;
  std::vector<float>	FatJet_btagCSVV2;
  std::vector<float>	FatJet_btagDDBvL;
  std::vector<float>	FatJet_btagDDBvL_noMD;
  std::vector<float>	FatJet_btagDDCvB;
  std::vector<float>	FatJet_btagDDCvB_noMD;
  std::vector<float>	FatJet_btagDDCvL;
  std::vector<float>	FatJet_btagDDCvL_noMD;
  std::vector<float>	FatJet_btagDeepB;
  std::vector<float>	FatJet_btagHbb;
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
  std::vector<float>	FatJet_eta;
  std::vector<int>	FatJet_jetId;
  std::vector<float>	FatJet_mass;
  std::vector<float>	FatJet_msoftdrop;
  std::vector<float>	FatJet_n2b1;
  std::vector<float>	FatJet_n3b1;
  std::vector<float>	FatJet_phi;
  std::vector<float>	FatJet_pt;
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
  std::vector<float>	GenPart_eta;
  std::vector<int>	GenPart_genPartIdxMother;
  std::vector<float>	GenPart_mass;
  std::vector<int>	GenPart_pdgId;
  std::vector<float>	GenPart_phi;
  std::vector<float>	GenPart_pt;
  std::vector<int>	GenPart_status;
  std::vector<int>	GenPart_statusFlags;
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
  std::vector<float>	Jet_btagCMVA;
  std::vector<float>	Jet_btagCSVV2;
  std::vector<float>	Jet_btagDeepB;
  std::vector<float>	Jet_btagDeepC;
  std::vector<float>	Jet_btagDeepFlavB;
  std::vector<float>	Jet_btagDeepFlavC;
  std::vector<float>	Jet_chEmEF;
  std::vector<float>	Jet_chHEF;
  std::vector<int>	Jet_cleanmask;
  std::vector<int>	Jet_electronIdx1;
  std::vector<int>	Jet_electronIdx2;
  std::vector<float>	Jet_eta;
  std::vector<int>	Jet_genJetIdx;
  std::vector<int>	Jet_hadronFlavour;
  std::vector<float>	Jet_jercCHF;
  std::vector<float>	Jet_jercCHPUF;
  std::vector<int>	Jet_jetId;
  std::vector<float>	Jet_mass;
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
  std::vector<int>	Jet_puId;
  std::vector<float>	Jet_qgl;
  std::vector<float>	Jet_rawFactor;
  std::vector<float>	LHEPart_eta;
  std::vector<float>	LHEPart_mass;
  std::vector<int>	LHEPart_pdgId;
  std::vector<float>	LHEPart_phi;
  std::vector<float>	LHEPart_pt;
  std::vector<float>	LHEPdfWeight;
  std::vector<float>	LHEReweightingWeight;
  std::vector<float>	LHEScaleWeight;
  std::vector<int>	Muon_charge;
  std::vector<int>	Muon_cleanmask;
  std::vector<float>	Muon_dxy;
  std::vector<float>	Muon_dxyErr;
  std::vector<float>	Muon_dz;
  std::vector<float>	Muon_dzErr;
  std::vector<float>	Muon_eta;
  std::vector<int>	Muon_fsrPhotonIdx;
  std::vector<int>	Muon_genPartFlav;
  std::vector<int>	Muon_genPartIdx;
  std::vector<int>	Muon_highPtId;
  std::vector<bool>	Muon_inTimeMuon;
  std::vector<float>	Muon_ip3d;
  std::vector<bool>	Muon_isGlobal;
  std::vector<bool>	Muon_isPFcand;
  std::vector<bool>	Muon_isTracker;
  std::vector<int>	Muon_jetIdx;
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
  std::vector<float>	Muon_segmentComp;
  std::vector<float>	Muon_sip3d;
  std::vector<bool>	Muon_softId;
  std::vector<float>  Muon_softMva;
  std::vector<bool>	Muon_softMvaId;
  std::vector<int>	Muon_tightCharge;
  std::vector<bool>	Muon_tightId;
  std::vector<int>	Muon_tkIsoId;
  std::vector<float>	Muon_tkRelIso;
  std::vector<bool>	Muon_triggerIdLoose;
  std::vector<float>	Muon_tunepRelPt;
  std::vector<float>	OtherPV_z;
  std::vector<int>	Photon_charge;
  std::vector<int>	Photon_cleanmask;
  std::vector<int>	Photon_cutBased;
  std::vector<int>	Photon_cutBased17Bitmap;
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
  std::vector<float>	Photon_mvaID17;
  std::vector<bool>	Photon_mvaID17_WP80;
  std::vector<bool>	Photon_mvaID17_WP90;
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
  std::vector<float>	SubJet_btagCMVA;
  std::vector<float>	SubJet_btagCSVV2;
  std::vector<float>	SubJet_btagDeepB;
  std::vector<float>	SubJet_eta;
  std::vector<float>	SubJet_mass;
  std::vector<float>	SubJet_n2b1;
  std::vector<float>	SubJet_n3b1;
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
  std::vector<int>	Tau_idAntiEle;
  std::vector<int>	Tau_idAntiEle2018;
  std::vector<int>	Tau_idAntiMu;
  std::vector<bool>	Tau_idDecayMode;
  std::vector<bool>	Tau_idDecayModeNewDMs;
  std::vector<int>	Tau_idDeepTau2017v2p1VSe;
  std::vector<int>	Tau_idDeepTau2017v2p1VSjet;
  std::vector<int>	Tau_idDeepTau2017v2p1VSmu;
  std::vector<int>	Tau_idMVAnewDM2017v2;
  std::vector<int>	Tau_idMVAoldDM;
  std::vector<int>	Tau_idMVAoldDM2017v1;
  std::vector<int>	Tau_idMVAoldDM2017v2;
  std::vector<int>	Tau_idMVAoldDMdR032017v2;
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
  std::vector<float>	Tau_rawAntiEle;
  std::vector<float>	Tau_rawAntiEle2018;
  std::vector<int>	Tau_rawAntiEleCat;
  std::vector<int>	Tau_rawAntiEleCat2018;
  std::vector<float>	Tau_rawDeepTau2017v2p1VSe;
  std::vector<float>	Tau_rawDeepTau2017v2p1VSjet;
  std::vector<float>	Tau_rawDeepTau2017v2p1VSmu;
  std::vector<float>	Tau_rawIso;
  std::vector<float>	Tau_rawIsodR03;
  std::vector<float>	Tau_rawMVAnewDM2017v2;
  std::vector<float>	Tau_rawMVAoldDM;
  std::vector<float>	Tau_rawMVAoldDM2017v1;
  std::vector<float>	Tau_rawMVAoldDM2017v2;
  std::vector<float>	Tau_rawMVAoldDMdR032017v2;
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
  int	nSV;
  int	nOtherPV;
  int	nLHEReweightingWeight;
  int	nLHEPdfWeight;
  int	nTrigObj;
  int	nFsrPhoton;
  int	nElectron;
  int	nIsoTrack;
  int	nPhoton;

  float	CaloMET_phi;
  float	CaloMET_pt;
  float	CaloMET_sumEt;
  float	ChsMET_phi;
  float	ChsMET_pt;
  float	ChsMET_sumEt;
  bool	Flag_BadChargedCandidateFilter;
  bool	Flag_BadChargedCandidateSummer16Filter;
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
  bool	Flag_ecalBadCalibFilterV2;
  bool	Flag_ecalLaserCorrFilter;
  bool	Flag_eeBadScFilter;
  bool	Flag_globalSuperTightHalo2016Filter;
  bool	Flag_globalTightHalo2016Filter;
  bool	Flag_goodVertices;
  bool	Flag_hcalLaserEventFilter;
  bool	Flag_muonBadTrackFilter;
  bool	Flag_trkPOGFilters;
  bool	Flag_trkPOG_logErrorTooManyClusters;
  bool	Flag_trkPOG_manystripclus53X;
  bool	Flag_trkPOG_toomanystripclus53X;
  float	GenMET_phi;
  float	GenMET_pt;
  float	Generator_binvar;
  int	Generator_id1;
  int	Generator_id2;
  float	Generator_scalePDF;
  float	Generator_weight;
  float	Generator_x1;
  float	Generator_x2;
  float	Generator_xpdf1;
  float	Generator_xpdf2;

  bool	HLT_AK4PFJet100;
  bool  HLT_AK4PFJet120;
  bool	HLT_AK4PFJet30;
  bool	HLT_AK4PFJet50;
  bool	HLT_AK4PFJet80;
  bool	HLT_AK8PFHT650_TrimR0p1PT0p03Mass50;
  bool	HLT_AK8PFHT700_TrimR0p1PT0p03Mass50;
  bool  HLT_AK8PFHT750_TrimMass50;
  bool  HLT_AK8PFHT800_TrimMass50;
  bool  HLT_AK8PFHT850_TrimMass50;
  bool  HLT_AK8PFHT900_TrimMass50;
  bool	HLT_AK8PFJet140;
  bool	HLT_AK8PFJet200;
  bool	HLT_AK8PFJet260;
  bool	HLT_AK8PFJet320;
  bool  HLT_AK8PFJet360_TrimMass30;
  bool  HLT_AK8PFJet380_TrimMass30;
  bool  HLT_AK8PFJet400_TrimMass30;
  bool  HLT_AK8PFJet420_TrimMass30;
  bool  HLT_AK8PFJet550;
  bool	HLT_AK8PFJet40;
  bool	HLT_AK8PFJet400;
  bool	HLT_AK8PFJet450;
  bool	HLT_AK8PFJet500;
  bool	HLT_AK8PFJet60;
  bool	HLT_AK8PFJet80;
  bool  HLT_Ele115_CaloIdVT_GsfTrkIdT; 
  bool  HLT_Ele15_IsoVVVL_PFHT450;
  bool	HLT_Ele23_WPLoose_Gsf;
  bool	HLT_Ele25_WPTight_Gsf;
  bool	HLT_Ele27_WPLoose_Gsf;
  bool	HLT_Ele27_WPTight_Gsf;
  bool  HLT_Ele28_WPTight_Gsf;
  bool	HLT_Ele30_WPTight_Gsf;
  bool  HLT_Ele32_WPTight_Gsf;
  bool	HLT_Ele35_WPLoose_Gsf;
  bool  HLT_Ele35_WPTight_Gsf;
  bool  HLT_Ele38_WPTight_Gsf;
  bool  HLT_Ele40_WPTight_Gsf;
  bool	HLT_Ele45_WPLoose_Gsf;
  bool	HLT_HT200;
  bool	HLT_HT2000;
  bool	HLT_HT2500;
  bool	HLT_HT275;
  bool	HLT_HT325;
  bool	HLT_HT410to430;
  bool	HLT_HT425;
  bool	HLT_HT430to450;
  bool	HLT_HT450to470;
  bool	HLT_HT470to500;
  bool	HLT_HT500to550;
  bool	HLT_HT550to650;
  bool	HLT_HT575;
  bool	HLT_HT650;
  bool	HLT_IsoMu20;
  bool	HLT_IsoMu22;
  bool	HLT_IsoMu24;
  bool	HLT_IsoMu27;
  bool  HLT_IsoMu30;
  bool	HLT_IsoTkMu20;
  bool	HLT_IsoTkMu22;
  bool	HLT_IsoTkMu24;
  bool	HLT_IsoTkMu27;
  bool	HLT_MET100;
  bool	HLT_MET150;
  bool	HLT_MET200;
  bool	HLT_MET250;
  bool	HLT_MET300;
  bool	HLT_MET600;
  bool	HLT_MET60_IsoTrk35_Loose;
  bool	HLT_MET700;
  bool	HLT_MET75_IsoTrk50;
  bool	HLT_MET90_IsoTrk50;
  bool  HLT_Mu15_IsoVVVL_PFHT450;
  bool	HLT_Mu20;
  bool	HLT_Mu27;
  bool	HLT_Mu28NoFiltersNoVtx_CentralCaloJet40;
  bool	HLT_Mu300;
  bool	HLT_Mu350;
  bool	HLT_Mu50;
  bool	HLT_Mu55;
  bool  HLT_PFHT1050;
  bool	HLT_PFHT125;
  bool	HLT_PFHT180;
  bool	HLT_PFHT370;
  bool	HLT_PFHT430;
  bool	HLT_PFHT510;
  bool	HLT_PFHT590;
  bool	HLT_PFHT200;
  bool	HLT_PFHT250;
  bool	HLT_PFHT300;
  bool	HLT_PFHT300_PFMET100;
  bool	HLT_PFHT300_PFMET110;
  bool	HLT_PFHT350;
  bool	HLT_PFHT400;
  bool	HLT_PFHT475;
  bool  HLT_PFHT500_PFMET100_PFMHT100_IDTight;
  bool  HLT_PFHT500_PFMET110_PFMHT110_IDTight;
  bool	HLT_PFHT600;
  bool	HLT_PFHT650;
  bool	HLT_PFHT680;
  bool  HLT_PFHT700_PFMET85_PFMHT85_IDTight;
  bool  HLT_PFHT700_PFMET95_PFMHT95_IDTight;
  bool  HLT_PFHT780;
  bool	HLT_PFHT800;
  bool  HLT_PFHT800_PFMET75_PFMHT75_IDTight;
  bool  HLT_PFHT800_PFMET85_PFMHT85_IDTight;
  bool  HLT_PFHT890;
  bool	HLT_PFHT900;
  bool	HLT_PFJet140;
  bool	HLT_PFJet200;
  bool	HLT_PFJet260;
  bool	HLT_PFJet320;
  bool	HLT_PFJet40;
  bool	HLT_PFJet400;
  bool	HLT_PFJet450;
  bool	HLT_PFJet500;
  bool	HLT_PFJet60;
  bool	HLT_PFJet80;
  bool	HLT_PFMET100_PFMHT100_IDTight;
  bool	HLT_PFMET110_PFMHT110_IDTight;
  bool	HLT_PFMET120_PFMHT120_IDTight;
  bool	HLT_PFMET170_HBHECleaned;
  bool	HLT_PFMET170_JetIdCleaned;
  bool	HLT_PFMET170_NoiseCleaned;
  bool	HLT_PFMET170_NotCleaned;
  bool	HLT_PFMET300;
  bool	HLT_PFMET400;
  bool	HLT_PFMET500;
  bool	HLT_PFMET600;
  bool	HLT_PFMET90_PFMHT90_IDTight;
  bool	HLT_PFMETNoMu90_PFMHTNoMu90_IDTight;
  bool  HLT_PFMETTypeOne120_PFMHT120_IDTight;
  bool  HLT_PFMETNoMu100_PFMHTNoMu100_IDTight;
  bool  HLT_PFMETNoMu110_PFMHTNoMu110_IDTight;
  bool  HLT_PFMETNoMu120_PFMHTNoMu120_IDTight;
  bool  HLT_PFMETNoMu130_PFMHTNoMu130_IDTight;
  bool  HLT_PFMETNoMu140_PFMHTNoMu140_IDTight;
  bool  HLT_Photon100EBHE10;
  bool  HLT_Photon100EB_TightID_TightIso;
  bool  HLT_Photon100EEHE10;
  bool  HLT_Photon100EE_TightID_TightIso;
  bool  HLT_Photon110EB_TightID_TightIso;
  bool  HLT_Photon120EB_TightID_TightIso;
  bool	HLT_Photon120;
  bool	HLT_Photon125;
  bool	HLT_Photon135_PFMET100;
  bool	HLT_Photon150;
  bool	HLT_Photon165_HE10;
  bool	HLT_Photon175;
  bool  HLT_Photon200;
  bool  HLT_Photon20;
  bool	HLT_Photon22;
  bool	HLT_Photon25;
  bool	HLT_Photon250_NoHE;
  bool	HLT_Photon30;
  bool	HLT_Photon300_NoHE;
  bool	HLT_Photon33;
  bool	HLT_Photon36;
  bool	HLT_Photon50;
  bool	HLT_Photon500;
  bool	HLT_Photon600;
  bool	HLT_Photon75;
  bool	HLT_Photon90;
  bool	HLT_Rsq0p25;
  bool	HLT_Rsq0p30;
  bool  HLT_Rsq0p35;
  bool  HLT_Rsq0p40;
  bool  HLT_RsqMR300_Rsq0p09_MR200;
  bool  HLT_RsqMR320_Rsq0p09_MR200;
  bool	HLT_RsqMR240_Rsq0p09_MR200;
  bool	HLT_RsqMR270_Rsq0p09_MR200;
  bool  HLT_TkMu20;
  bool  HLT_TkMu27;
  bool  HLT_TkMu50;
  bool  HLTriggerFinalPath;                                                                                                                                                                           
  bool  HLTriggerFirstPath;
  float	LHEWeight_originalXWGTUP;
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
  float	METFixEE2017_MetUnclustEnUpDeltaX;
  float	METFixEE2017_MetUnclustEnUpDeltaY;
  float	METFixEE2017_covXX;
  float	METFixEE2017_covXY;
  float	METFixEE2017_covYY;
  float	METFixEE2017_phi;
  float	METFixEE2017_pt;
  float	METFixEE2017_significance;
  float	METFixEE2017_sumEt;
  float	MET_MetUnclustEnUpDeltaX;
  float	MET_MetUnclustEnUpDeltaY;
  float	MET_covXX;
  float	MET_covXY;
  float	MET_covYY;
  float	MET_fiducialGenPhi;
  float	MET_fiducialGenPt;
  float	MET_phi;
  float	MET_pt;
  float	MET_significance;
  float	MET_sumEt;
  float	PSWeight;
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
  float	PuppiMET_pt;
  float	PuppiMET_sumEt;
  float	RawMET_phi;
  float	RawMET_pt;
  float	RawMET_sumEt;
  float	TkMET_phi;
  float	TkMET_pt;
  float	TkMET_sumEt;
  float	btagWeight_CMVA;
  float	btagWeight_CSVV2;
  long	event;
  float	fixedGridRhoFastjetAll;
  float	fixedGridRhoFastjetCentral;
  float	fixedGridRhoFastjetCentralCalo;
  float	fixedGridRhoFastjetCentralChargedPileUp;
  float	fixedGridRhoFastjetCentralNeutral;
  int	genTtbarId;
  float	genWeight;
  unsigned int	luminosityBlock;
  unsigned int	run;

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
    int	cutBased_Fall17_V1;
    bool	cutBased_HEEP;
    int	cutBased_HLTPreSel;
    int	cutBased_Spring15;
    int	cutBased_Sum16;
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
    float	jetPtRelv2;
    float	jetRelIso;
    int	lostHits;
    float	mass;
    float	miniPFRelIso_all;
    float	miniPFRelIso_chg;
    float	mvaFall17V1Iso;
    bool	mvaFall17V1Iso_WP80;
    bool	mvaFall17V1Iso_WP90;
    bool	mvaFall17V1Iso_WPL;
    float	mvaFall17V1noIso;
    bool	mvaFall17V1noIso_WP80;
    bool	mvaFall17V1noIso_WP90;
    bool	mvaFall17V1noIso_WPL;
    float	mvaFall17V2Iso;
    bool	mvaFall17V2Iso_WP80;
    bool	mvaFall17V2Iso_WP90;
    bool	mvaFall17V2Iso_WPL;
    float	mvaFall17V2noIso;
    bool	mvaFall17V2noIso_WP80;
    bool	mvaFall17V2noIso_WP90;
    bool	mvaFall17V2noIso_WPL;
    float	mvaSpring16GP;
    bool	mvaSpring16GP_WP80;
    bool	mvaSpring16GP_WP90;
    float	mvaSpring16HZZ;
    bool	mvaSpring16HZZ_WPL;
    float	mvaTTH;
    int	pdgId;
    float	pfRelIso03_all;
    float	pfRelIso03_chg;
    float	phi;
    int	photonIdx;
    float	pt;
    float	r9;
    int	seedGain;
    float	sieie;
    float	sip3d;
    int	tightCharge;
    int	vidNestedWPBitmap;
    int	vidNestedWPBitmapHEEP;
    int	vidNestedWPBitmapSpring15;
    int	vidNestedWPBitmapSum16;

    std::ostream& operator<<(std::ostream& os)
    {
      char r[1024];
      os << "Electron" << std::endl;
      sprintf(r, "  %-32s: %f\n", "charge", ( double)charge); os << r;
      sprintf(r, "  %-32s: %f\n", "cleanmask", ( double)cleanmask); os << r;
      sprintf(r, "  %-32s: %f\n", "convVeto", ( double)convVeto); os << r;
      sprintf(r, "  %-32s: %f\n", "cutBased", ( double)cutBased); os << r;
      sprintf(r, "  %-32s: %f\n", "cutBased_Fall17_V1", ( double)cutBased_Fall17_V1); os << r;
      sprintf(r, "  %-32s: %f\n", "cutBased_HEEP", ( double)cutBased_HEEP); os << r;
      sprintf(r, "  %-32s: %f\n", "cutBased_HLTPreSel", ( double)cutBased_HLTPreSel); os << r;
      sprintf(r, "  %-32s: %f\n", "cutBased_Spring15", ( double)cutBased_Spring15); os << r;
      sprintf(r, "  %-32s: %f\n", "cutBased_Sum16", ( double)cutBased_Sum16); os << r;
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
      sprintf(r, "  %-32s: %f\n", "jetPtRelv2", ( double)jetPtRelv2); os << r;
      sprintf(r, "  %-32s: %f\n", "jetRelIso", ( double)jetRelIso); os << r;
      sprintf(r, "  %-32s: %f\n", "lostHits", ( double)lostHits); os << r;
      sprintf(r, "  %-32s: %f\n", "mass", ( double)mass); os << r;
      sprintf(r, "  %-32s: %f\n", "miniPFRelIso_all", ( double)miniPFRelIso_all); os << r;
      sprintf(r, "  %-32s: %f\n", "miniPFRelIso_chg", ( double)miniPFRelIso_chg); os << r;
      sprintf(r, "  %-32s: %f\n", "mvaFall17V1Iso", ( double)mvaFall17V1Iso); os << r;
      sprintf(r, "  %-32s: %f\n", "mvaFall17V1Iso_WP80", ( double)mvaFall17V1Iso_WP80); os << r;
      sprintf(r, "  %-32s: %f\n", "mvaFall17V1Iso_WP90", ( double)mvaFall17V1Iso_WP90); os << r;
      sprintf(r, "  %-32s: %f\n", "mvaFall17V1Iso_WPL", ( double)mvaFall17V1Iso_WPL); os << r;
      sprintf(r, "  %-32s: %f\n", "mvaFall17V1noIso", ( double)mvaFall17V1noIso); os << r;
      sprintf(r, "  %-32s: %f\n", "mvaFall17V1noIso_WP80", ( double)mvaFall17V1noIso_WP80); os << r;
      sprintf(r, "  %-32s: %f\n", "mvaFall17V1noIso_WP90", ( double)mvaFall17V1noIso_WP90); os << r;
      sprintf(r, "  %-32s: %f\n", "mvaFall17V1noIso_WPL", ( double)mvaFall17V1noIso_WPL); os << r;
      sprintf(r, "  %-32s: %f\n", "mvaFall17V2Iso", ( double)mvaFall17V2Iso); os << r;
      sprintf(r, "  %-32s: %f\n", "mvaFall17V2Iso_WP80", ( double)mvaFall17V2Iso_WP80); os << r;
      sprintf(r, "  %-32s: %f\n", "mvaFall17V2Iso_WP90", ( double)mvaFall17V2Iso_WP90); os << r;
      sprintf(r, "  %-32s: %f\n", "mvaFall17V2Iso_WPL", ( double)mvaFall17V2Iso_WPL); os << r;
      sprintf(r, "  %-32s: %f\n", "mvaFall17V2noIso", ( double)mvaFall17V2noIso); os << r;
      sprintf(r, "  %-32s: %f\n", "mvaFall17V2noIso_WP80", ( double)mvaFall17V2noIso_WP80); os << r;
      sprintf(r, "  %-32s: %f\n", "mvaFall17V2noIso_WP90", ( double)mvaFall17V2noIso_WP90); os << r;
      sprintf(r, "  %-32s: %f\n", "mvaFall17V2noIso_WPL", ( double)mvaFall17V2noIso_WPL); os << r;
      sprintf(r, "  %-32s: %f\n", "mvaSpring16GP", ( double)mvaSpring16GP); os << r;
      sprintf(r, "  %-32s: %f\n", "mvaSpring16GP_WP80", ( double)mvaSpring16GP_WP80); os << r;
      sprintf(r, "  %-32s: %f\n", "mvaSpring16GP_WP90", ( double)mvaSpring16GP_WP90); os << r;
      sprintf(r, "  %-32s: %f\n", "mvaSpring16HZZ", ( double)mvaSpring16HZZ); os << r;
      sprintf(r, "  %-32s: %f\n", "mvaSpring16HZZ_WPL", ( double)mvaSpring16HZZ_WPL); os << r;
      sprintf(r, "  %-32s: %f\n", "mvaTTH", ( double)mvaTTH); os << r;
      sprintf(r, "  %-32s: %f\n", "pdgId", ( double)pdgId); os << r;
      sprintf(r, "  %-32s: %f\n", "pfRelIso03_all", ( double)pfRelIso03_all); os << r;
      sprintf(r, "  %-32s: %f\n", "pfRelIso03_chg", ( double)pfRelIso03_chg); os << r;
      sprintf(r, "  %-32s: %f\n", "phi", ( double)phi); os << r;
      sprintf(r, "  %-32s: %f\n", "photonIdx", ( double)photonIdx); os << r;
      sprintf(r, "  %-32s: %f\n", "pt", ( double)pt); os << r;
      sprintf(r, "  %-32s: %f\n", "r9", ( double)r9); os << r;
      sprintf(r, "  %-32s: %f\n", "seedGain", ( double)seedGain); os << r;
      sprintf(r, "  %-32s: %f\n", "sieie", ( double)sieie); os << r;
      sprintf(r, "  %-32s: %f\n", "sip3d", ( double)sip3d); os << r;
      sprintf(r, "  %-32s: %f\n", "tightCharge", ( double)tightCharge); os << r;
      sprintf(r, "  %-32s: %f\n", "vidNestedWPBitmap", ( double)vidNestedWPBitmap); os << r;
      sprintf(r, "  %-32s: %f\n", "vidNestedWPBitmapHEEP", ( double)vidNestedWPBitmapHEEP); os << r;
      sprintf(r, "  %-32s: %f\n", "vidNestedWPBitmapSpring15", ( double)vidNestedWPBitmapSpring15); os << r;
      sprintf(r, "  %-32s: %f\n", "vidNestedWPBitmapSum16", ( double)vidNestedWPBitmapSum16); os << r;
      return os;
    }
  };

  struct FatJet_s
  {
    float	area;
    float	btagCMVA;
    float	btagCSVV2;
    float	btagDDBvL;
    float	btagDDBvL_noMD;
    float	btagDDCvB;
    float	btagDDCvB_noMD;
    float	btagDDCvL;
    float	btagDDCvL_noMD;
    float	btagDeepB;
    float	btagHbb;
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
    float	eta;
    int	jetId;
    float	mass;
    float	msoftdrop;
    float	n2b1;
    float	n3b1;
    float	phi;
    float	pt;
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
      sprintf(r, "  %-32s: %f\n", "btagCMVA", ( double)btagCMVA); os << r;
      sprintf(r, "  %-32s: %f\n", "btagCSVV2", ( double)btagCSVV2); os << r;
      sprintf(r, "  %-32s: %f\n", "btagDDBvL", ( double)btagDDBvL); os << r;
      sprintf(r, "  %-32s: %f\n", "btagDDBvL_noMD", ( double)btagDDBvL_noMD); os << r;
      sprintf(r, "  %-32s: %f\n", "btagDDCvB", ( double)btagDDCvB); os << r;
      sprintf(r, "  %-32s: %f\n", "btagDDCvB_noMD", ( double)btagDDCvB_noMD); os << r;
      sprintf(r, "  %-32s: %f\n", "btagDDCvL", ( double)btagDDCvL); os << r;
      sprintf(r, "  %-32s: %f\n", "btagDDCvL_noMD", ( double)btagDDCvL_noMD); os << r;
      sprintf(r, "  %-32s: %f\n", "btagDeepB", ( double)btagDeepB); os << r;
      sprintf(r, "  %-32s: %f\n", "btagHbb", ( double)btagHbb); os << r;
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
      sprintf(r, "  %-32s: %f\n", "eta", ( double)eta); os << r;
      sprintf(r, "  %-32s: %f\n", "jetId", ( double)jetId); os << r;
      sprintf(r, "  %-32s: %f\n", "mass", ( double)mass); os << r;
      sprintf(r, "  %-32s: %f\n", "msoftdrop", ( double)msoftdrop); os << r;
      sprintf(r, "  %-32s: %f\n", "n2b1", ( double)n2b1); os << r;
      sprintf(r, "  %-32s: %f\n", "n3b1", ( double)n3b1); os << r;
      sprintf(r, "  %-32s: %f\n", "phi", ( double)phi); os << r;
      sprintf(r, "  %-32s: %f\n", "pt", ( double)pt); os << r;
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
    float	btagCMVA;
    float	btagCSVV2;
    float	btagDeepB;
    float	btagDeepC;
    float	btagDeepFlavB;
    float	btagDeepFlavC;
    float	chEmEF;
    float	chHEF;
    int	cleanmask;
    int	electronIdx1;
    int	electronIdx2;
    float	eta;
    int	genJetIdx;
    int	hadronFlavour;
    float	jercCHF;
    float	jercCHPUF;
    int	jetId;
    float	mass;
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
    int	puId;
    float	qgl;
    float	rawFactor;

    std::ostream& operator<<(std::ostream& os)
    {
      char r[1024];
      os << "Jet" << std::endl;
      sprintf(r, "  %-32s: %f\n", "area", ( double)area); os << r;
      sprintf(r, "  %-32s: %f\n", "bRegCorr", ( double)bRegCorr); os << r;
      sprintf(r, "  %-32s: %f\n", "bRegRes", ( double)bRegRes); os << r;
      sprintf(r, "  %-32s: %f\n", "btagCMVA", ( double)btagCMVA); os << r;
      sprintf(r, "  %-32s: %f\n", "btagCSVV2", ( double)btagCSVV2); os << r;
      sprintf(r, "  %-32s: %f\n", "btagDeepB", ( double)btagDeepB); os << r;
      sprintf(r, "  %-32s: %f\n", "btagDeepC", ( double)btagDeepC); os << r;
      sprintf(r, "  %-32s: %f\n", "btagDeepFlavB", ( double)btagDeepFlavB); os << r;
      sprintf(r, "  %-32s: %f\n", "btagDeepFlavC", ( double)btagDeepFlavC); os << r;
      sprintf(r, "  %-32s: %f\n", "chEmEF", ( double)chEmEF); os << r;
      sprintf(r, "  %-32s: %f\n", "chHEF", ( double)chHEF); os << r;
      sprintf(r, "  %-32s: %f\n", "cleanmask", ( double)cleanmask); os << r;
      sprintf(r, "  %-32s: %f\n", "electronIdx1", ( double)electronIdx1); os << r;
      sprintf(r, "  %-32s: %f\n", "electronIdx2", ( double)electronIdx2); os << r;
      sprintf(r, "  %-32s: %f\n", "eta", ( double)eta); os << r;
      sprintf(r, "  %-32s: %f\n", "genJetIdx", ( double)genJetIdx); os << r;
      sprintf(r, "  %-32s: %f\n", "hadronFlavour", ( double)hadronFlavour); os << r;
      sprintf(r, "  %-32s: %f\n", "jercCHF", ( double)jercCHF); os << r;
      sprintf(r, "  %-32s: %f\n", "jercCHPUF", ( double)jercCHPUF); os << r;
      sprintf(r, "  %-32s: %f\n", "jetId", ( double)jetId); os << r;
      sprintf(r, "  %-32s: %f\n", "mass", ( double)mass); os << r;
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
      sprintf(r, "  %-32s: %f\n", "puId", ( double)puId); os << r;
      sprintf(r, "  %-32s: %f\n", "qgl", ( double)qgl); os << r;
      sprintf(r, "  %-32s: %f\n", "rawFactor", ( double)rawFactor); os << r;
      return os;
    }
  };

  struct LHEPart_s
  {
    float	eta;
    float	mass;
    int	pdgId;
    float	phi;
    float	pt;

    std::ostream& operator<<(std::ostream& os)
    {
      char r[1024];
      os << "LHEPart" << std::endl;
      sprintf(r, "  %-32s: %f\n", "eta", ( double)eta); os << r;
      sprintf(r, "  %-32s: %f\n", "mass", ( double)mass); os << r;
      sprintf(r, "  %-32s: %f\n", "pdgId", ( double)pdgId); os << r;
      sprintf(r, "  %-32s: %f\n", "phi", ( double)phi); os << r;
      sprintf(r, "  %-32s: %f\n", "pt", ( double)pt); os << r;
      return os;
    }
  };

  struct Muon_s
  {
    int	charge;
    int	cleanmask;
    float	dxy;
    float	dxyErr;
    float	dz;
    float	dzErr;
    float	eta;
    int	fsrPhotonIdx;
    int	genPartFlav;
    int	genPartIdx;
    int	highPtId;
    bool	inTimeMuon;
    float	ip3d;
    bool	isGlobal;
    bool	isPFcand;
    bool	isTracker;
    int	jetIdx;
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
    float	segmentComp;
    float	sip3d;
    bool	softId;
    float softMva;
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
      sprintf(r, "  %-32s: %f\n", "dz", ( double)dz); os << r;
      sprintf(r, "  %-32s: %f\n", "dzErr", ( double)dzErr); os << r;
      sprintf(r, "  %-32s: %f\n", "eta", ( double)eta); os << r;
      sprintf(r, "  %-32s: %f\n", "fsrPhotonIdx", ( double)fsrPhotonIdx); os << r;
      sprintf(r, "  %-32s: %f\n", "genPartFlav", ( double)genPartFlav); os << r;
      sprintf(r, "  %-32s: %f\n", "genPartIdx", ( double)genPartIdx); os << r;
      sprintf(r, "  %-32s: %f\n", "highPtId", ( double)highPtId); os << r;
      sprintf(r, "  %-32s: %f\n", "inTimeMuon", ( double)inTimeMuon); os << r;
      sprintf(r, "  %-32s: %f\n", "ip3d", ( double)ip3d); os << r;
      sprintf(r, "  %-32s: %f\n", "isGlobal", ( double)isGlobal); os << r;
      sprintf(r, "  %-32s: %f\n", "isPFcand", ( double)isPFcand); os << r;
      sprintf(r, "  %-32s: %f\n", "isTracker", ( double)isTracker); os << r;
      sprintf(r, "  %-32s: %f\n", "jetIdx", ( double)jetIdx); os << r;
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
    int	cutBased17Bitmap;
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
    float	mvaID17;
    bool	mvaID17_WP80;
    bool	mvaID17_WP90;
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
      sprintf(r, "  %-32s: %f\n", "cutBased17Bitmap", ( double)cutBased17Bitmap); os << r;
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
      sprintf(r, "  %-32s: %f\n", "mvaID17", ( double)mvaID17); os << r;
      sprintf(r, "  %-32s: %f\n", "mvaID17_WP80", ( double)mvaID17_WP80); os << r;
      sprintf(r, "  %-32s: %f\n", "mvaID17_WP90", ( double)mvaID17_WP90); os << r;
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


  struct SubJet_s
  {
    float	btagCMVA;
    float	btagCSVV2;
    float	btagDeepB;
    float	eta;
    float	mass;
    float	n2b1;
    float	n3b1;
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
      sprintf(r, "  %-32s: %f\n", "btagCMVA", ( double)btagCMVA); os << r;
      sprintf(r, "  %-32s: %f\n", "btagCSVV2", ( double)btagCSVV2); os << r;
      sprintf(r, "  %-32s: %f\n", "btagDeepB", ( double)btagDeepB); os << r;
      sprintf(r, "  %-32s: %f\n", "eta", ( double)eta); os << r;
      sprintf(r, "  %-32s: %f\n", "mass", ( double)mass); os << r;
      sprintf(r, "  %-32s: %f\n", "n2b1", ( double)n2b1); os << r;
      sprintf(r, "  %-32s: %f\n", "n3b1", ( double)n3b1); os << r;
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
    int	idAntiEle;
    int	idAntiEle2018;
    int	idAntiMu;
    bool	idDecayMode;
    bool	idDecayModeNewDMs;
    int	idDeepTau2017v2p1VSe;
    int	idDeepTau2017v2p1VSjet;
    int	idDeepTau2017v2p1VSmu;
    int	idMVAnewDM2017v2;
    int	idMVAoldDM;
    int	idMVAoldDM2017v1;
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
    float	rawAntiEle;
    float	rawAntiEle2018;
    int	rawAntiEleCat;
    int	rawAntiEleCat2018;
    float	rawDeepTau2017v2p1VSe;
    float	rawDeepTau2017v2p1VSjet;
    float	rawDeepTau2017v2p1VSmu;
    float	rawIso;
    float	rawIsodR03;
    float	rawMVAnewDM2017v2;
    float	rawMVAoldDM;
    float	rawMVAoldDM2017v1;
    float	rawMVAoldDM2017v2;
    float	rawMVAoldDMdR032017v2;

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
      sprintf(r, "  %-32s: %f\n", "idAntiEle", ( double)idAntiEle); os << r;
      sprintf(r, "  %-32s: %f\n", "idAntiEle2018", ( double)idAntiEle2018); os << r;
      sprintf(r, "  %-32s: %f\n", "idAntiMu", ( double)idAntiMu); os << r;
      sprintf(r, "  %-32s: %f\n", "idDecayMode", ( double)idDecayMode); os << r;
      sprintf(r, "  %-32s: %f\n", "idDecayModeNewDMs", ( double)idDecayModeNewDMs); os << r;
      sprintf(r, "  %-32s: %f\n", "idDeepTau2017v2p1VSe", ( double)idDeepTau2017v2p1VSe); os << r;
      sprintf(r, "  %-32s: %f\n", "idDeepTau2017v2p1VSjet", ( double)idDeepTau2017v2p1VSjet); os << r;
      sprintf(r, "  %-32s: %f\n", "idDeepTau2017v2p1VSmu", ( double)idDeepTau2017v2p1VSmu); os << r;
      sprintf(r, "  %-32s: %f\n", "idMVAnewDM2017v2", ( double)idMVAnewDM2017v2); os << r;
      sprintf(r, "  %-32s: %f\n", "idMVAoldDM", ( double)idMVAoldDM); os << r;
      sprintf(r, "  %-32s: %f\n", "idMVAoldDM2017v1", ( double)idMVAoldDM2017v1); os << r;
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
      sprintf(r, "  %-32s: %f\n", "rawAntiEle", ( double)rawAntiEle); os << r;
      sprintf(r, "  %-32s: %f\n", "rawAntiEle2018", ( double)rawAntiEle2018); os << r;
      sprintf(r, "  %-32s: %f\n", "rawAntiEleCat", ( double)rawAntiEleCat); os << r;
      sprintf(r, "  %-32s: %f\n", "rawAntiEleCat2018", ( double)rawAntiEleCat2018); os << r;
      sprintf(r, "  %-32s: %f\n", "rawDeepTau2017v2p1VSe", ( double)rawDeepTau2017v2p1VSe); os << r;
      sprintf(r, "  %-32s: %f\n", "rawDeepTau2017v2p1VSjet", ( double)rawDeepTau2017v2p1VSjet); os << r;
      sprintf(r, "  %-32s: %f\n", "rawDeepTau2017v2p1VSmu", ( double)rawDeepTau2017v2p1VSmu); os << r;
      sprintf(r, "  %-32s: %f\n", "rawIso", ( double)rawIso); os << r;
      sprintf(r, "  %-32s: %f\n", "rawIsodR03", ( double)rawIsodR03); os << r;
      sprintf(r, "  %-32s: %f\n", "rawMVAnewDM2017v2", ( double)rawMVAnewDM2017v2); os << r;
      sprintf(r, "  %-32s: %f\n", "rawMVAoldDM", ( double)rawMVAoldDM); os << r;
      sprintf(r, "  %-32s: %f\n", "rawMVAoldDM2017v1", ( double)rawMVAoldDM2017v1); os << r;
      sprintf(r, "  %-32s: %f\n", "rawMVAoldDM2017v2", ( double)rawMVAoldDM2017v2); os << r;
      sprintf(r, "  %-32s: %f\n", "rawMVAoldDMdR032017v2", ( double)rawMVAoldDMdR032017v2); os << r;
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
        Electron[i].cutBased_Fall17_V1	= Electron_cutBased_Fall17_V1[i];
        Electron[i].cutBased_HEEP	= (bool)Electron_cutBased_HEEP[i];
        Electron[i].cutBased_HLTPreSel	= Electron_cutBased_HLTPreSel[i];
        Electron[i].cutBased_Spring15	= Electron_cutBased_Spring15[i];
        Electron[i].cutBased_Sum16	= Electron_cutBased_Sum16[i];
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
        Electron[i].jetPtRelv2	= Electron_jetPtRelv2[i];
        Electron[i].jetRelIso	= Electron_jetRelIso[i];
        Electron[i].lostHits	= Electron_lostHits[i];
        Electron[i].mass	= Electron_mass[i];
        Electron[i].miniPFRelIso_all	= Electron_miniPFRelIso_all[i];
        Electron[i].miniPFRelIso_chg	= Electron_miniPFRelIso_chg[i];
        Electron[i].mvaFall17V1Iso	= Electron_mvaFall17V1Iso[i];
        Electron[i].mvaFall17V1Iso_WP80	= (bool)Electron_mvaFall17V1Iso_WP80[i];
        Electron[i].mvaFall17V1Iso_WP90	= (bool)Electron_mvaFall17V1Iso_WP90[i];
        Electron[i].mvaFall17V1Iso_WPL	= (bool)Electron_mvaFall17V1Iso_WPL[i];
        Electron[i].mvaFall17V1noIso	= Electron_mvaFall17V1noIso[i];
        Electron[i].mvaFall17V1noIso_WP80	= (bool)Electron_mvaFall17V1noIso_WP80[i];
        Electron[i].mvaFall17V1noIso_WP90	= (bool)Electron_mvaFall17V1noIso_WP90[i];
        Electron[i].mvaFall17V1noIso_WPL	= (bool)Electron_mvaFall17V1noIso_WPL[i];
        Electron[i].mvaFall17V2Iso	= Electron_mvaFall17V2Iso[i];
        Electron[i].mvaFall17V2Iso_WP80	= (bool)Electron_mvaFall17V2Iso_WP80[i];
        Electron[i].mvaFall17V2Iso_WP90	= (bool)Electron_mvaFall17V2Iso_WP90[i];
        Electron[i].mvaFall17V2Iso_WPL	= (bool)Electron_mvaFall17V2Iso_WPL[i];
        Electron[i].mvaFall17V2noIso	= Electron_mvaFall17V2noIso[i];
        Electron[i].mvaFall17V2noIso_WP80	= (bool)Electron_mvaFall17V2noIso_WP80[i];
        Electron[i].mvaFall17V2noIso_WP90	= (bool)Electron_mvaFall17V2noIso_WP90[i];
        Electron[i].mvaFall17V2noIso_WPL	= (bool)Electron_mvaFall17V2noIso_WPL[i];
        Electron[i].mvaSpring16GP	= Electron_mvaSpring16GP[i];
        Electron[i].mvaSpring16GP_WP80	= (bool)Electron_mvaSpring16GP_WP80[i];
        Electron[i].mvaSpring16GP_WP90	= (bool)Electron_mvaSpring16GP_WP90[i];
        Electron[i].mvaSpring16HZZ	= Electron_mvaSpring16HZZ[i];
        Electron[i].mvaSpring16HZZ_WPL	= (bool)Electron_mvaSpring16HZZ_WPL[i];
        Electron[i].mvaTTH	= Electron_mvaTTH[i];
        Electron[i].pdgId	= Electron_pdgId[i];
        Electron[i].pfRelIso03_all	= Electron_pfRelIso03_all[i];
        Electron[i].pfRelIso03_chg	= Electron_pfRelIso03_chg[i];
        Electron[i].phi	= Electron_phi[i];
        Electron[i].photonIdx	= Electron_photonIdx[i];
        Electron[i].pt	= Electron_pt[i];
        Electron[i].r9	= Electron_r9[i];
        Electron[i].seedGain	= Electron_seedGain[i];
        Electron[i].sieie	= Electron_sieie[i];
        Electron[i].sip3d	= Electron_sip3d[i];
        Electron[i].tightCharge	= Electron_tightCharge[i];
        Electron[i].vidNestedWPBitmap	= Electron_vidNestedWPBitmap[i];
        Electron[i].vidNestedWPBitmapHEEP	= Electron_vidNestedWPBitmapHEEP[i];
        Electron[i].vidNestedWPBitmapSpring15	= Electron_vidNestedWPBitmapSpring15[i];
        Electron[i].vidNestedWPBitmapSum16	= Electron_vidNestedWPBitmapSum16[i];
      }
  }

  void fillFatJets()
  {
    FatJet.resize(FatJet_area.size());
    for(unsigned int i=0; i < FatJet.size(); ++i)
      {
        FatJet[i].area	= FatJet_area[i];
        FatJet[i].btagCMVA	= FatJet_btagCMVA[i];
        FatJet[i].btagCSVV2	= FatJet_btagCSVV2[i];
        FatJet[i].btagDDBvL	= FatJet_btagDDBvL[i];
        FatJet[i].btagDDBvL_noMD	= FatJet_btagDDBvL_noMD[i];
        FatJet[i].btagDDCvB	= FatJet_btagDDCvB[i];
        FatJet[i].btagDDCvB_noMD	= FatJet_btagDDCvB_noMD[i];
        FatJet[i].btagDDCvL	= FatJet_btagDDCvL[i];
        FatJet[i].btagDDCvL_noMD	= FatJet_btagDDCvL_noMD[i];
        FatJet[i].btagDeepB	= FatJet_btagDeepB[i];
        FatJet[i].btagHbb	= FatJet_btagHbb[i];
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
        FatJet[i].eta	= FatJet_eta[i];
        FatJet[i].jetId	= FatJet_jetId[i];
        FatJet[i].mass	= FatJet_mass[i];
        FatJet[i].msoftdrop	= FatJet_msoftdrop[i];
        FatJet[i].n2b1	= FatJet_n2b1[i];
        FatJet[i].n3b1	= FatJet_n3b1[i];
        FatJet[i].phi	= FatJet_phi[i];
        FatJet[i].pt	= FatJet_pt[i];
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
    IsoTrack.resize(IsoTrack_dxy.size());
    for(unsigned int i=0; i < IsoTrack.size(); ++i)
      {
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
        Jet[i].btagCMVA	= Jet_btagCMVA[i];
        Jet[i].btagCSVV2	= Jet_btagCSVV2[i];
        Jet[i].btagDeepB	= Jet_btagDeepB[i];
        Jet[i].btagDeepC	= Jet_btagDeepC[i];
        Jet[i].btagDeepFlavB	= Jet_btagDeepFlavB[i];
        Jet[i].btagDeepFlavC	= Jet_btagDeepFlavC[i];
        Jet[i].chEmEF	= Jet_chEmEF[i];
        Jet[i].chHEF	= Jet_chHEF[i];
        Jet[i].cleanmask	= Jet_cleanmask[i];
        Jet[i].electronIdx1	= Jet_electronIdx1[i];
        Jet[i].electronIdx2	= Jet_electronIdx2[i];
        Jet[i].eta	= Jet_eta[i];
        Jet[i].genJetIdx	= Jet_genJetIdx[i];
        Jet[i].hadronFlavour	= Jet_hadronFlavour[i];
        Jet[i].jercCHF	= Jet_jercCHF[i];
        Jet[i].jercCHPUF	= Jet_jercCHPUF[i];
        Jet[i].jetId	= Jet_jetId[i];
        Jet[i].mass	= Jet_mass[i];
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
        Jet[i].pt	= Jet_pt[i];
        Jet[i].puId	= Jet_puId[i];
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
        LHEPart[i].mass	= LHEPart_mass[i];
        LHEPart[i].pdgId	= LHEPart_pdgId[i];
        LHEPart[i].phi	= LHEPart_phi[i];
        LHEPart[i].pt	= LHEPart_pt[i];
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
        Muon[i].dz	= Muon_dz[i];
        Muon[i].dzErr	= Muon_dzErr[i];
        Muon[i].eta	= Muon_eta[i];
        Muon[i].fsrPhotonIdx	= Muon_fsrPhotonIdx[i];
        Muon[i].genPartFlav	= Muon_genPartFlav[i];
        Muon[i].genPartIdx	= Muon_genPartIdx[i];
        Muon[i].highPtId	= Muon_highPtId[i];
        Muon[i].inTimeMuon	= (bool)Muon_inTimeMuon[i];
        Muon[i].ip3d	= Muon_ip3d[i];
        Muon[i].isGlobal	= (bool)Muon_isGlobal[i];
        Muon[i].isPFcand	= (bool)Muon_isPFcand[i];
        Muon[i].isTracker	= (bool)Muon_isTracker[i];
        Muon[i].jetIdx	= Muon_jetIdx[i];
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
        Muon[i].segmentComp	= Muon_segmentComp[i];
        Muon[i].sip3d	= Muon_sip3d[i];
        Muon[i].softId	= (bool)Muon_softId[i];
        Muon[i].softMva = Muon_softMva[i];
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
        Photon[i].cutBased17Bitmap	= Photon_cutBased17Bitmap[i];
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
        Photon[i].mvaID17	= Photon_mvaID17[i];
        Photon[i].mvaID17_WP80	= (bool)Photon_mvaID17_WP80[i];
        Photon[i].mvaID17_WP90	= (bool)Photon_mvaID17_WP90[i];
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

  void fillSubJets()
  {
    SubJet.resize(SubJet_btagCMVA.size());
    for(unsigned int i=0; i < SubJet.size(); ++i)
      {
        SubJet[i].btagCMVA	= SubJet_btagCMVA[i];
        SubJet[i].btagCSVV2	= SubJet_btagCSVV2[i];
        SubJet[i].btagDeepB	= SubJet_btagDeepB[i];
        SubJet[i].eta	= SubJet_eta[i];
        SubJet[i].mass	= SubJet_mass[i];
        SubJet[i].n2b1	= SubJet_n2b1[i];
        SubJet[i].n3b1	= SubJet_n3b1[i];
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
        Tau[i].idAntiEle	= Tau_idAntiEle[i];
        Tau[i].idAntiEle2018	= Tau_idAntiEle2018[i];
        Tau[i].idAntiMu	= Tau_idAntiMu[i];
        Tau[i].idDecayMode	= (bool)Tau_idDecayMode[i];
        Tau[i].idDecayModeNewDMs	= (bool)Tau_idDecayModeNewDMs[i];
        Tau[i].idDeepTau2017v2p1VSe	= Tau_idDeepTau2017v2p1VSe[i];
        Tau[i].idDeepTau2017v2p1VSjet	= Tau_idDeepTau2017v2p1VSjet[i];
        Tau[i].idDeepTau2017v2p1VSmu	= Tau_idDeepTau2017v2p1VSmu[i];
        Tau[i].idMVAnewDM2017v2	= Tau_idMVAnewDM2017v2[i];
        Tau[i].idMVAoldDM	= Tau_idMVAoldDM[i];
        Tau[i].idMVAoldDM2017v1	= Tau_idMVAoldDM2017v1[i];
        Tau[i].idMVAoldDM2017v2	= Tau_idMVAoldDM2017v2[i];
        Tau[i].idMVAoldDMdR032017v2	= Tau_idMVAoldDMdR032017v2[i];
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
        Tau[i].rawAntiEle	= Tau_rawAntiEle[i];
        Tau[i].rawAntiEle2018	= Tau_rawAntiEle2018[i];
        Tau[i].rawAntiEleCat	= Tau_rawAntiEleCat[i];
        Tau[i].rawAntiEleCat2018	= Tau_rawAntiEleCat2018[i];
        Tau[i].rawDeepTau2017v2p1VSe	= Tau_rawDeepTau2017v2p1VSe[i];
        Tau[i].rawDeepTau2017v2p1VSjet	= Tau_rawDeepTau2017v2p1VSjet[i];
        Tau[i].rawDeepTau2017v2p1VSmu	= Tau_rawDeepTau2017v2p1VSmu[i];
        Tau[i].rawIso	= Tau_rawIso[i];
        Tau[i].rawIsodR03	= Tau_rawIsodR03[i];
        Tau[i].rawMVAnewDM2017v2	= Tau_rawMVAnewDM2017v2[i];
        Tau[i].rawMVAoldDM	= Tau_rawMVAoldDM[i];
        Tau[i].rawMVAoldDM2017v1	= Tau_rawMVAoldDM2017v1[i];
        Tau[i].rawMVAoldDM2017v2	= Tau_rawMVAoldDM2017v2[i];
        Tau[i].rawMVAoldDMdR032017v2	= Tau_rawMVAoldDMdR032017v2[i];
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


  std::vector<eventBuffer::CorrT1METJet_s> CorrT1METJet;
  std::vector<eventBuffer::Electron_s> Electron;
  std::vector<eventBuffer::FatJet_s> FatJet;
  std::vector<eventBuffer::FsrPhoton_s> FsrPhoton;
  std::vector<eventBuffer::GenPart_s> GenPart;
  std::vector<eventBuffer::IsoTrack_s> IsoTrack;
  std::vector<eventBuffer::Jet_s> Jet;
  std::vector<eventBuffer::LHEPart_s> LHEPart;
  std::vector<eventBuffer::Muon_s> Muon;
  std::vector<eventBuffer::Photon_s> Photon;
  std::vector<eventBuffer::SubJet_s> SubJet;
  std::vector<eventBuffer::Tau_s> Tau;
  std::vector<eventBuffer::TrigObj_s> TrigObj;

  void fillObjects()
  {
    fillCorrT1METJets();
    fillElectrons();
    fillFatJets();
    fillFsrPhotons();
    fillGenParts();
    fillIsoTracks();
    fillJets();
    fillLHEParts();
    fillMuons();
    fillPhotons();
    fillSubJets();
    fillTaus();
    fillTrigObjs();
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
            Electron_cutBased_Fall17_V1[i]	= Electron_cutBased_Fall17_V1[j];
            Electron_cutBased_HEEP[i]	= Electron_cutBased_HEEP[j];
            Electron_cutBased_HLTPreSel[i]	= Electron_cutBased_HLTPreSel[j];
            Electron_cutBased_Spring15[i]	= Electron_cutBased_Spring15[j];
            Electron_cutBased_Sum16[i]	= Electron_cutBased_Sum16[j];
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
            Electron_jetPtRelv2[i]	= Electron_jetPtRelv2[j];
            Electron_jetRelIso[i]	= Electron_jetRelIso[j];
            Electron_lostHits[i]	= Electron_lostHits[j];
            Electron_mass[i]	= Electron_mass[j];
            Electron_miniPFRelIso_all[i]	= Electron_miniPFRelIso_all[j];
            Electron_miniPFRelIso_chg[i]	= Electron_miniPFRelIso_chg[j];
            Electron_mvaFall17V1Iso[i]	= Electron_mvaFall17V1Iso[j];
            Electron_mvaFall17V1Iso_WP80[i]	= Electron_mvaFall17V1Iso_WP80[j];
            Electron_mvaFall17V1Iso_WP90[i]	= Electron_mvaFall17V1Iso_WP90[j];
            Electron_mvaFall17V1Iso_WPL[i]	= Electron_mvaFall17V1Iso_WPL[j];
            Electron_mvaFall17V1noIso[i]	= Electron_mvaFall17V1noIso[j];
            Electron_mvaFall17V1noIso_WP80[i]	= Electron_mvaFall17V1noIso_WP80[j];
            Electron_mvaFall17V1noIso_WP90[i]	= Electron_mvaFall17V1noIso_WP90[j];
            Electron_mvaFall17V1noIso_WPL[i]	= Electron_mvaFall17V1noIso_WPL[j];
            Electron_mvaFall17V2Iso[i]	= Electron_mvaFall17V2Iso[j];
            Electron_mvaFall17V2Iso_WP80[i]	= Electron_mvaFall17V2Iso_WP80[j];
            Electron_mvaFall17V2Iso_WP90[i]	= Electron_mvaFall17V2Iso_WP90[j];
            Electron_mvaFall17V2Iso_WPL[i]	= Electron_mvaFall17V2Iso_WPL[j];
            Electron_mvaFall17V2noIso[i]	= Electron_mvaFall17V2noIso[j];
            Electron_mvaFall17V2noIso_WP80[i]	= Electron_mvaFall17V2noIso_WP80[j];
            Electron_mvaFall17V2noIso_WP90[i]	= Electron_mvaFall17V2noIso_WP90[j];
            Electron_mvaFall17V2noIso_WPL[i]	= Electron_mvaFall17V2noIso_WPL[j];
            Electron_mvaSpring16GP[i]	= Electron_mvaSpring16GP[j];
            Electron_mvaSpring16GP_WP80[i]	= Electron_mvaSpring16GP_WP80[j];
            Electron_mvaSpring16GP_WP90[i]	= Electron_mvaSpring16GP_WP90[j];
            Electron_mvaSpring16HZZ[i]	= Electron_mvaSpring16HZZ[j];
            Electron_mvaSpring16HZZ_WPL[i]	= Electron_mvaSpring16HZZ_WPL[j];
            Electron_mvaTTH[i]	= Electron_mvaTTH[j];
            Electron_pdgId[i]	= Electron_pdgId[j];
            Electron_pfRelIso03_all[i]	= Electron_pfRelIso03_all[j];
            Electron_pfRelIso03_chg[i]	= Electron_pfRelIso03_chg[j];
            Electron_phi[i]	= Electron_phi[j];
            Electron_photonIdx[i]	= Electron_photonIdx[j];
            Electron_pt[i]	= Electron_pt[j];
            Electron_r9[i]	= Electron_r9[j];
            Electron_seedGain[i]	= Electron_seedGain[j];
            Electron_sieie[i]	= Electron_sieie[j];
            Electron_sip3d[i]	= Electron_sip3d[j];
            Electron_tightCharge[i]	= Electron_tightCharge[j];
            Electron_vidNestedWPBitmap[i]	= Electron_vidNestedWPBitmap[j];
            Electron_vidNestedWPBitmapHEEP[i]	= Electron_vidNestedWPBitmapHEEP[j];
            Electron_vidNestedWPBitmapSpring15[i]	= Electron_vidNestedWPBitmapSpring15[j];
            Electron_vidNestedWPBitmapSum16[i]	= Electron_vidNestedWPBitmapSum16[j];
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
            FatJet_btagCMVA[i]	= FatJet_btagCMVA[j];
            FatJet_btagCSVV2[i]	= FatJet_btagCSVV2[j];
            FatJet_btagDDBvL[i]	= FatJet_btagDDBvL[j];
            FatJet_btagDDBvL_noMD[i]	= FatJet_btagDDBvL_noMD[j];
            FatJet_btagDDCvB[i]	= FatJet_btagDDCvB[j];
            FatJet_btagDDCvB_noMD[i]	= FatJet_btagDDCvB_noMD[j];
            FatJet_btagDDCvL[i]	= FatJet_btagDDCvL[j];
            FatJet_btagDDCvL_noMD[i]	= FatJet_btagDDCvL_noMD[j];
            FatJet_btagDeepB[i]	= FatJet_btagDeepB[j];
            FatJet_btagHbb[i]	= FatJet_btagHbb[j];
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
            FatJet_eta[i]	= FatJet_eta[j];
            FatJet_jetId[i]	= FatJet_jetId[j];
            FatJet_mass[i]	= FatJet_mass[j];
            FatJet_msoftdrop[i]	= FatJet_msoftdrop[j];
            FatJet_n2b1[i]	= FatJet_n2b1[j];
            FatJet_n3b1[i]	= FatJet_n3b1[j];
            FatJet_phi[i]	= FatJet_phi[j];
            FatJet_pt[i]	= FatJet_pt[j];
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
            Jet_btagCMVA[i]	= Jet_btagCMVA[j];
            Jet_btagCSVV2[i]	= Jet_btagCSVV2[j];
            Jet_btagDeepB[i]	= Jet_btagDeepB[j];
            Jet_btagDeepC[i]	= Jet_btagDeepC[j];
            Jet_btagDeepFlavB[i]	= Jet_btagDeepFlavB[j];
            Jet_btagDeepFlavC[i]	= Jet_btagDeepFlavC[j];
            Jet_chEmEF[i]	= Jet_chEmEF[j];
            Jet_chHEF[i]	= Jet_chHEF[j];
            Jet_cleanmask[i]	= Jet_cleanmask[j];
            Jet_electronIdx1[i]	= Jet_electronIdx1[j];
            Jet_electronIdx2[i]	= Jet_electronIdx2[j];
            Jet_eta[i]	= Jet_eta[j];
            Jet_genJetIdx[i]	= Jet_genJetIdx[j];
            Jet_hadronFlavour[i]	= Jet_hadronFlavour[j];
            Jet_jercCHF[i]	= Jet_jercCHF[j];
            Jet_jercCHPUF[i]	= Jet_jercCHPUF[j];
            Jet_jetId[i]	= Jet_jetId[j];
            Jet_mass[i]	= Jet_mass[j];
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
            Jet_pt[i]	= Jet_pt[j];
            Jet_puId[i]	= Jet_puId[j];
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
            LHEPart_mass[i]	= LHEPart_mass[j];
            LHEPart_pdgId[i]	= LHEPart_pdgId[j];
            LHEPart_phi[i]	= LHEPart_phi[j];
            LHEPart_pt[i]	= LHEPart_pt[j];
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
            Muon_dz[i]	= Muon_dz[j];
            Muon_dzErr[i]	= Muon_dzErr[j];
            Muon_eta[i]	= Muon_eta[j];
            Muon_fsrPhotonIdx[i]	= Muon_fsrPhotonIdx[j];
            Muon_genPartFlav[i]	= Muon_genPartFlav[j];
            Muon_genPartIdx[i]	= Muon_genPartIdx[j];
            Muon_highPtId[i]	= Muon_highPtId[j];
            Muon_inTimeMuon[i]	= Muon_inTimeMuon[j];
            Muon_ip3d[i]	= Muon_ip3d[j];
            Muon_isGlobal[i]	= Muon_isGlobal[j];
            Muon_isPFcand[i]	= Muon_isPFcand[j];
            Muon_isTracker[i]	= Muon_isTracker[j];
            Muon_jetIdx[i]	= Muon_jetIdx[j];
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
            Muon_segmentComp[i]	= Muon_segmentComp[j];
            Muon_sip3d[i]	= Muon_sip3d[j];
            Muon_softId[i]	= Muon_softId[j];
            Muon_softMva[i] = Muon_softMva[j];
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
            Photon_cutBased17Bitmap[i]	= Photon_cutBased17Bitmap[j];
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
            Photon_mvaID17[i]	= Photon_mvaID17[j];
            Photon_mvaID17_WP80[i]	= Photon_mvaID17_WP80[j];
            Photon_mvaID17_WP90[i]	= Photon_mvaID17_WP90[j];
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
            SubJet_btagCMVA[i]	= SubJet_btagCMVA[j];
            SubJet_btagCSVV2[i]	= SubJet_btagCSVV2[j];
            SubJet_btagDeepB[i]	= SubJet_btagDeepB[j];
            SubJet_eta[i]	= SubJet_eta[j];
            SubJet_mass[i]	= SubJet_mass[j];
            SubJet_n2b1[i]	= SubJet_n2b1[j];
            SubJet_n3b1[i]	= SubJet_n3b1[j];
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
            Tau_idAntiEle[i]	= Tau_idAntiEle[j];
            Tau_idAntiEle2018[i]	= Tau_idAntiEle2018[j];
            Tau_idAntiMu[i]	= Tau_idAntiMu[j];
            Tau_idDecayMode[i]	= Tau_idDecayMode[j];
            Tau_idDecayModeNewDMs[i]	= Tau_idDecayModeNewDMs[j];
            Tau_idDeepTau2017v2p1VSe[i]	= Tau_idDeepTau2017v2p1VSe[j];
            Tau_idDeepTau2017v2p1VSjet[i]	= Tau_idDeepTau2017v2p1VSjet[j];
            Tau_idDeepTau2017v2p1VSmu[i]	= Tau_idDeepTau2017v2p1VSmu[j];
            Tau_idMVAnewDM2017v2[i]	= Tau_idMVAnewDM2017v2[j];
            Tau_idMVAoldDM[i]	= Tau_idMVAoldDM[j];
            Tau_idMVAoldDM2017v1[i]	= Tau_idMVAoldDM2017v1[j];
            Tau_idMVAoldDM2017v2[i]	= Tau_idMVAoldDM2017v2[j];
            Tau_idMVAoldDMdR032017v2[i]	= Tau_idMVAoldDMdR032017v2[j];
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
            Tau_rawAntiEle[i]	= Tau_rawAntiEle[j];
            Tau_rawAntiEle2018[i]	= Tau_rawAntiEle2018[j];
            Tau_rawAntiEleCat[i]	= Tau_rawAntiEleCat[j];
            Tau_rawAntiEleCat2018[i]	= Tau_rawAntiEleCat2018[j];
            Tau_rawDeepTau2017v2p1VSe[i]	= Tau_rawDeepTau2017v2p1VSe[j];
            Tau_rawDeepTau2017v2p1VSjet[i]	= Tau_rawDeepTau2017v2p1VSjet[j];
            Tau_rawDeepTau2017v2p1VSmu[i]	= Tau_rawDeepTau2017v2p1VSmu[j];
            Tau_rawIso[i]	= Tau_rawIso[j];
            Tau_rawIsodR03[i]	= Tau_rawIsodR03[j];
            Tau_rawMVAnewDM2017v2[i]	= Tau_rawMVAnewDM2017v2[j];
            Tau_rawMVAoldDM[i]	= Tau_rawMVAoldDM[j];
            Tau_rawMVAoldDM2017v1[i]	= Tau_rawMVAoldDM2017v1[j];
            Tau_rawMVAoldDM2017v2[i]	= Tau_rawMVAoldDM2017v2[j];
            Tau_rawMVAoldDMdR032017v2[i]	= Tau_rawMVAoldDMdR032017v2[j];
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
    choose["Events/CaloMET_phi"]	= DEFAULT;
    choose["Events/CaloMET_pt"]	= DEFAULT;
    choose["Events/CaloMET_sumEt"]	= DEFAULT;
    choose["Events/ChsMET_phi"]	= DEFAULT;
    choose["Events/ChsMET_pt"]	= DEFAULT;
    choose["Events/ChsMET_sumEt"]	= DEFAULT;
    choose["Events/CorrT1METJet_area"]	= DEFAULT;
    choose["Events/CorrT1METJet_eta"]	= DEFAULT;
    choose["Events/CorrT1METJet_muonSubtrFactor"]	= DEFAULT;
    choose["Events/CorrT1METJet_phi"]	= DEFAULT;
    choose["Events/CorrT1METJet_rawPt"]	= DEFAULT;
    choose["Events/Electron_charge"]	= DEFAULT;
    choose["Events/Electron_cleanmask"]	= DEFAULT;
    choose["Events/Electron_convVeto"]	= DEFAULT;
    choose["Events/Electron_cutBased"]	= DEFAULT;
    choose["Events/Electron_cutBased_Fall17_V1"]	= DEFAULT;
    choose["Events/Electron_cutBased_HEEP"]	= DEFAULT;
    choose["Events/Electron_cutBased_HLTPreSel"]	= DEFAULT;
    choose["Events/Electron_cutBased_Spring15"]	= DEFAULT;
    choose["Events/Electron_cutBased_Sum16"]	= DEFAULT;
    choose["Events/Electron_deltaEtaSC"]	= DEFAULT;
    choose["Events/Electron_dr03EcalRecHitSumEt"]	= DEFAULT;
    choose["Events/Electron_dr03HcalDepth1TowerSumEt"]	= DEFAULT;
    choose["Events/Electron_dr03TkSumPt"]	= DEFAULT;
    choose["Events/Electron_dr03TkSumPtHEEP"]	= DEFAULT;
    choose["Events/Electron_dxy"]	= DEFAULT;
    choose["Events/Electron_dxyErr"]	= DEFAULT;
    choose["Events/Electron_dz"]	= DEFAULT;
    choose["Events/Electron_dzErr"]	= DEFAULT;
    choose["Events/Electron_eCorr"]	= DEFAULT;
    choose["Events/Electron_eInvMinusPInv"]	= DEFAULT;
    choose["Events/Electron_energyErr"]	= DEFAULT;
    choose["Events/Electron_eta"]	= DEFAULT;
    choose["Events/Electron_genPartFlav"]	= DEFAULT;
    choose["Events/Electron_genPartIdx"]	= DEFAULT;
    choose["Events/Electron_hoe"]	= DEFAULT;
    choose["Events/Electron_ip3d"]	= DEFAULT;
    choose["Events/Electron_isPFcand"]	= DEFAULT;
    choose["Events/Electron_jetIdx"]	= DEFAULT;
    choose["Events/Electron_jetPtRelv2"]	= DEFAULT;
    choose["Events/Electron_jetRelIso"]	= DEFAULT;
    choose["Events/Electron_lostHits"]	= DEFAULT;
    choose["Events/Electron_mass"]	= DEFAULT;
    choose["Events/Electron_miniPFRelIso_all"]	= DEFAULT;
    choose["Events/Electron_miniPFRelIso_chg"]	= DEFAULT;
    choose["Events/Electron_mvaFall17V1Iso"]	= DEFAULT;
    choose["Events/Electron_mvaFall17V1Iso_WP80"]	= DEFAULT;
    choose["Events/Electron_mvaFall17V1Iso_WP90"]	= DEFAULT;
    choose["Events/Electron_mvaFall17V1Iso_WPL"]	= DEFAULT;
    choose["Events/Electron_mvaFall17V1noIso"]	= DEFAULT;
    choose["Events/Electron_mvaFall17V1noIso_WP80"]	= DEFAULT;
    choose["Events/Electron_mvaFall17V1noIso_WP90"]	= DEFAULT;
    choose["Events/Electron_mvaFall17V1noIso_WPL"]	= DEFAULT;
    choose["Events/Electron_mvaFall17V2Iso"]	= DEFAULT;
    choose["Events/Electron_mvaFall17V2Iso_WP80"]	= DEFAULT;
    choose["Events/Electron_mvaFall17V2Iso_WP90"]	= DEFAULT;
    choose["Events/Electron_mvaFall17V2Iso_WPL"]	= DEFAULT;
    choose["Events/Electron_mvaFall17V2noIso"]	= DEFAULT;
    choose["Events/Electron_mvaFall17V2noIso_WP80"]	= DEFAULT;
    choose["Events/Electron_mvaFall17V2noIso_WP90"]	= DEFAULT;
    choose["Events/Electron_mvaFall17V2noIso_WPL"]	= DEFAULT;
    choose["Events/Electron_mvaSpring16GP"]	= DEFAULT;
    choose["Events/Electron_mvaSpring16GP_WP80"]	= DEFAULT;
    choose["Events/Electron_mvaSpring16GP_WP90"]	= DEFAULT;
    choose["Events/Electron_mvaSpring16HZZ"]	= DEFAULT;
    choose["Events/Electron_mvaSpring16HZZ_WPL"]	= DEFAULT;
    choose["Events/Electron_mvaTTH"]	= DEFAULT;
    choose["Events/Electron_pdgId"]	= DEFAULT;
    choose["Events/Electron_pfRelIso03_all"]	= DEFAULT;
    choose["Events/Electron_pfRelIso03_chg"]	= DEFAULT;
    choose["Events/Electron_phi"]	= DEFAULT;
    choose["Events/Electron_photonIdx"]	= DEFAULT;
    choose["Events/Electron_pt"]	= DEFAULT;
    choose["Events/Electron_r9"]	= DEFAULT;
    choose["Events/Electron_seedGain"]	= DEFAULT;
    choose["Events/Electron_sieie"]	= DEFAULT;
    choose["Events/Electron_sip3d"]	= DEFAULT;
    choose["Events/Electron_tightCharge"]	= DEFAULT;
    choose["Events/Electron_vidNestedWPBitmap"]	= DEFAULT;
    choose["Events/Electron_vidNestedWPBitmapHEEP"]	= DEFAULT;
    choose["Events/Electron_vidNestedWPBitmapSpring15"]	= DEFAULT;
    choose["Events/Electron_vidNestedWPBitmapSum16"]	= DEFAULT;
    choose["Events/FatJet_area"]	= DEFAULT;
    choose["Events/FatJet_btagCMVA"]	= DEFAULT;
    choose["Events/FatJet_btagCSVV2"]	= DEFAULT;
    choose["Events/FatJet_btagDDBvL"]	= DEFAULT;
    choose["Events/FatJet_btagDDBvL_noMD"]	= DEFAULT;
    choose["Events/FatJet_btagDDCvB"]	= DEFAULT;
    choose["Events/FatJet_btagDDCvB_noMD"]	= DEFAULT;
    choose["Events/FatJet_btagDDCvL"]	= DEFAULT;
    choose["Events/FatJet_btagDDCvL_noMD"]	= DEFAULT;
    choose["Events/FatJet_btagDeepB"]	= DEFAULT;
    choose["Events/FatJet_btagHbb"]	= DEFAULT;
    choose["Events/FatJet_deepTagMD_H4qvsQCD"]	= DEFAULT;
    choose["Events/FatJet_deepTagMD_HbbvsQCD"]	= DEFAULT;
    choose["Events/FatJet_deepTagMD_TvsQCD"]	= DEFAULT;
    choose["Events/FatJet_deepTagMD_WvsQCD"]	= DEFAULT;
    choose["Events/FatJet_deepTagMD_ZHbbvsQCD"]	= DEFAULT;
    choose["Events/FatJet_deepTagMD_ZHccvsQCD"]	= DEFAULT;
    choose["Events/FatJet_deepTagMD_ZbbvsQCD"]	= DEFAULT;
    choose["Events/FatJet_deepTagMD_ZvsQCD"]	= DEFAULT;
    choose["Events/FatJet_deepTagMD_bbvsLight"]	= DEFAULT;
    choose["Events/FatJet_deepTagMD_ccvsLight"]	= DEFAULT;
    choose["Events/FatJet_deepTag_H"]	= DEFAULT;
    choose["Events/FatJet_deepTag_QCD"]	= DEFAULT;
    choose["Events/FatJet_deepTag_QCDothers"]	= DEFAULT;
    choose["Events/FatJet_deepTag_TvsQCD"]	= DEFAULT;
    choose["Events/FatJet_deepTag_WvsQCD"]	= DEFAULT;
    choose["Events/FatJet_deepTag_ZvsQCD"]	= DEFAULT;
    choose["Events/FatJet_eta"]	= DEFAULT;
    choose["Events/FatJet_jetId"]	= DEFAULT;
    choose["Events/FatJet_mass"]	= DEFAULT;
    choose["Events/FatJet_msoftdrop"]	= DEFAULT;
    choose["Events/FatJet_n2b1"]	= DEFAULT;
    choose["Events/FatJet_n3b1"]	= DEFAULT;
    choose["Events/FatJet_phi"]	= DEFAULT;
    choose["Events/FatJet_pt"]	= DEFAULT;
    choose["Events/FatJet_rawFactor"]	= DEFAULT;
    choose["Events/FatJet_subJetIdx1"]	= DEFAULT;
    choose["Events/FatJet_subJetIdx2"]	= DEFAULT;
    choose["Events/FatJet_tau1"]	= DEFAULT;
    choose["Events/FatJet_tau2"]	= DEFAULT;
    choose["Events/FatJet_tau3"]	= DEFAULT;
    choose["Events/FatJet_tau4"]	= DEFAULT;
    choose["Events/Flag_BadChargedCandidateFilter"]	= DEFAULT;
    choose["Events/Flag_BadChargedCandidateSummer16Filter"]	= DEFAULT;
    choose["Events/Flag_BadPFMuonFilter"]	= DEFAULT;
    choose["Events/Flag_BadPFMuonSummer16Filter"]	= DEFAULT;
    choose["Events/Flag_CSCTightHalo2015Filter"]	= DEFAULT;
    choose["Events/Flag_CSCTightHaloFilter"]	= DEFAULT;
    choose["Events/Flag_CSCTightHaloTrkMuUnvetoFilter"]	= DEFAULT;
    choose["Events/Flag_EcalDeadCellBoundaryEnergyFilter"]	= DEFAULT;
    choose["Events/Flag_EcalDeadCellTriggerPrimitiveFilter"]	= DEFAULT;
    choose["Events/Flag_HBHENoiseFilter"]	= DEFAULT;
    choose["Events/Flag_HBHENoiseIsoFilter"]	= DEFAULT;
    choose["Events/Flag_HcalStripHaloFilter"]	= DEFAULT;
    choose["Events/Flag_METFilters"]	= DEFAULT;
    choose["Events/Flag_chargedHadronTrackResolutionFilter"]	= DEFAULT;
    choose["Events/Flag_ecalBadCalibFilter"]	= DEFAULT;
    choose["Events/Flag_ecalBadCalibFilterV2"]	= DEFAULT;
    choose["Events/Flag_ecalLaserCorrFilter"]	= DEFAULT;
    choose["Events/Flag_eeBadScFilter"]	= DEFAULT;
    choose["Events/Flag_globalSuperTightHalo2016Filter"]	= DEFAULT;
    choose["Events/Flag_globalTightHalo2016Filter"]	= DEFAULT;
    choose["Events/Flag_goodVertices"]	= DEFAULT;
    choose["Events/Flag_hcalLaserEventFilter"]	= DEFAULT;
    choose["Events/Flag_muonBadTrackFilter"]	= DEFAULT;
    choose["Events/Flag_trkPOGFilters"]	= DEFAULT;
    choose["Events/Flag_trkPOG_logErrorTooManyClusters"]	= DEFAULT;
    choose["Events/Flag_trkPOG_manystripclus53X"]	= DEFAULT;
    choose["Events/Flag_trkPOG_toomanystripclus53X"]	= DEFAULT;
    choose["Events/FsrPhoton_dROverEt2"]	= DEFAULT;
    choose["Events/FsrPhoton_eta"]	= DEFAULT;
    choose["Events/FsrPhoton_muonIdx"]	= DEFAULT;
    choose["Events/FsrPhoton_phi"]	= DEFAULT;
    choose["Events/FsrPhoton_pt"]	= DEFAULT;
    choose["Events/FsrPhoton_relIso03"]	= DEFAULT;
    choose["Events/GenMET_phi"]	= DEFAULT;
    choose["Events/GenMET_pt"]	= DEFAULT;
    choose["Events/GenPart_eta"]	= DEFAULT;
    choose["Events/GenPart_genPartIdxMother"]	= DEFAULT;
    choose["Events/GenPart_mass"]	= DEFAULT;
    choose["Events/GenPart_pdgId"]	= DEFAULT;
    choose["Events/GenPart_phi"]	= DEFAULT;
    choose["Events/GenPart_pt"]	= DEFAULT;
    choose["Events/GenPart_status"]	= DEFAULT;
    choose["Events/GenPart_statusFlags"]	= DEFAULT;
    choose["Events/Generator_binvar"]	= DEFAULT;
    choose["Events/Generator_id1"]	= DEFAULT;
    choose["Events/Generator_id2"]	= DEFAULT;
    choose["Events/Generator_scalePDF"]	= DEFAULT;
    choose["Events/Generator_weight"]	= DEFAULT;
    choose["Events/Generator_x1"]	= DEFAULT;
    choose["Events/Generator_x2"]	= DEFAULT;
    choose["Events/Generator_xpdf1"]	= DEFAULT;
    choose["Events/Generator_xpdf2"]	= DEFAULT;
    choose["Events/HLT_AK4PFJet100"]	= DEFAULT;
    choose["Events/HLT_AK4PFJet120"]  = DEFAULT;
    choose["Events/HLT_AK4PFJet30"]	= DEFAULT;
    choose["Events/HLT_AK4PFJet50"]	= DEFAULT;
    choose["Events/HLT_AK4PFJet80"]	= DEFAULT;
    choose["Events/HLT_AK8PFHT650_TrimR0p1PT0p03Mass50"]	= DEFAULT;
    choose["Events/HLT_AK8PFHT700_TrimR0p1PT0p03Mass50"]	= DEFAULT;
    choose["Events/HLT_AK8PFHT750_TrimMass50"]	= DEFAULT;
    choose["Events/HLT_AK8PFHT800_TrimMass50"]	= DEFAULT;
    choose["Events/HLT_AK8PFHT850_TrimMass50"]  = DEFAULT;
    choose["Events/HLT_AK8PFHT900_TrimMass50"]  = DEFAULT;
    choose["Events/HLT_AK8PFJet140"]	= DEFAULT;
    choose["Events/HLT_AK8PFJet200"]	= DEFAULT;
    choose["Events/HLT_AK8PFJet260"]	= DEFAULT;
    choose["Events/HLT_AK8PFJet320"]	= DEFAULT;
    choose["Events/HLT_AK8PFJet360_TrimMass30"]	= DEFAULT;
    choose["Events/HLT_AK8PFJet40"]	= DEFAULT;
    choose["Events/HLT_AK8PFJet400"]	= DEFAULT;
    choose["Events/HLT_AK8PFJet400_TrimMass30"]	= DEFAULT;
    choose["Events/HLT_AK8PFJet450"]	= DEFAULT;
    choose["Events/HLT_AK8PFJet500"]	= DEFAULT;
    choose["Events/HLT_AK8PFJet60"]	= DEFAULT;
    choose["Events/HLT_AK8PFJet80"]	= DEFAULT;
    choose["Events/HLT_Ele115_CaloIdVT_GsfTrkIdT"]  = DEFAULT;
    choose["Events/HLT_Ele15_IsoVVVL_PFHT450"]  = DEFAULT;
    choose["Events/HLT_Ele23_WPLoose_Gsf"]	= DEFAULT;
    choose["Events/HLT_Ele25_WPTight_Gsf"]	= DEFAULT;
    choose["Events/HLT_Ele27_WPLoose_Gsf"]	= DEFAULT;
    choose["Events/HLT_Ele27_WPTight_Gsf"]	= DEFAULT;
    choose["Events/HLT_Ele28_WPTight_Gsf"]  = DEFAULT;
    choose["Events/HLT_Ele30_WPTight_Gsf"]	= DEFAULT;
    choose["Events/HLT_Ele32_WPTight_Gsf"]	= DEFAULT;
    choose["Events/HLT_Ele35_WPLoose_Gsf"]	= DEFAULT;
    choose["Events/HLT_Ele35_WPTight_Gsf"]  = DEFAULT;
    choose["Events/HLT_Ele38_WPTight_Gsf"]  = DEFAULT;
    choose["Events/HLT_Ele40_WPTight_Gsf"]  = DEFAULT;
    choose["Events/HLT_Ele45_WPLoose_Gsf"]	= DEFAULT;
    choose["Events/HLT_HT200"]	= DEFAULT;
    choose["Events/HLT_HT2000"]	= DEFAULT;
    choose["Events/HLT_HT2500"]	= DEFAULT;
    choose["Events/HLT_HT275"]	= DEFAULT;
    choose["Events/HLT_HT325"]	= DEFAULT;
    choose["Events/HLT_HT410to430"]	= DEFAULT;
    choose["Events/HLT_HT425"]	= DEFAULT;
    choose["Events/HLT_HT430to450"]	= DEFAULT;
    choose["Events/HLT_HT450to470"]	= DEFAULT;
    choose["Events/HLT_HT470to500"]	= DEFAULT;
    choose["Events/HLT_HT500to550"]	= DEFAULT;
    choose["Events/HLT_HT550to650"]	= DEFAULT;
    choose["Events/HLT_HT575"]	= DEFAULT;
    choose["Events/HLT_HT650"]	= DEFAULT;
    choose["Events/HLT_IsoMu20"]	= DEFAULT;
    choose["Events/HLT_IsoMu22"]	= DEFAULT;
    choose["Events/HLT_IsoMu24"]	= DEFAULT;
    choose["Events/HLT_IsoMu27"]	= DEFAULT;
    choose["Events/HLT_IsoMu30"]  = DEFAULT;
    choose["Events/HLT_IsoTkMu20"]	= DEFAULT;
    choose["Events/HLT_IsoTkMu22"]	= DEFAULT;
    choose["Events/HLT_IsoTkMu24"]	= DEFAULT;
    choose["Events/HLT_IsoTkMu27"]	= DEFAULT;
    choose["Events/HLT_MET100"]	= DEFAULT;
    choose["Events/HLT_MET150"]	= DEFAULT;
    choose["Events/HLT_MET200"]	= DEFAULT;
    choose["Events/HLT_MET250"]	= DEFAULT;
    choose["Events/HLT_MET300"]	= DEFAULT;
    choose["Events/HLT_MET600"]	= DEFAULT;
    choose["Events/HLT_MET60_IsoTrk35_Loose"]	= DEFAULT;
    choose["Events/HLT_MET700"]	= DEFAULT;
    choose["Events/HLT_MET75_IsoTrk50"]	= DEFAULT;
    choose["Events/HLT_MET90_IsoTrk50"]	= DEFAULT;
    choose["Events/HLT_Mu15_IsoVVVL_PFHT450"] = DEFAULT;
    choose["Events/HLT_Mu20"]	= DEFAULT;
    choose["Events/HLT_Mu27"]	= DEFAULT;
    choose["Events/HLT_Mu300"]	= DEFAULT;
    choose["Events/HLT_Mu350"]	= DEFAULT;
    choose["Events/HLT_Mu50"]	= DEFAULT;
    choose["Events/HLT_Mu55"]	= DEFAULT;
    choose["Events/HLT_PFHT1050"] = DEFAULT;
    choose["Events/HLT_PFHT125"]	= DEFAULT;
    choose["Events/HLT_PFHT180"]	= DEFAULT;
    choose["Events/HLT_PFHT370"]	= DEFAULT;
    choose["Events/HLT_PFHT430"]	= DEFAULT;
    choose["Events/HLT_PFHT510"]	= DEFAULT;
    choose["Events/HLT_PFHT590"]	= DEFAULT;
    choose["Events/HLT_PFHT200"]	= DEFAULT;
    choose["Events/HLT_PFHT250"]	= DEFAULT;
    choose["Events/HLT_PFHT300"]	= DEFAULT;
    choose["Events/HLT_PFHT300_PFMET100"]	= DEFAULT;
    choose["Events/HLT_PFHT300_PFMET110"]	= DEFAULT;
    choose["Events/HLT_PFHT350"]	= DEFAULT;
    choose["Events/HLT_PFHT400"]	= DEFAULT;
    choose["Events/HLT_PFHT475"]	= DEFAULT;
    choose["Events/HLT_PFHT500_PFMET100_PFMHT100_IDTight"]  = DEFAULT;
    choose["Events/HLT_PFHT500_PFMET110_PFMHT110_IDTight"]  = DEFAULT;
    choose["Events/HLT_PFHT600"]	= DEFAULT;
    choose["Events/HLT_PFHT650"]	= DEFAULT;
    choose["Events/HLT_PFHT680"]  = DEFAULT;
    choose["Events/HLT_PFHT700_PFMET85_PFMHT85_IDTight"]  = DEFAULT;
    choose["Events/HLT_PFHT700_PFMET95_PFMHT95_IDTight"]  = DEFAULT;
    choose["Events/HLT_PFHT780"]  = DEFAULT;
    choose["Events/HLT_PFHT800_PFMET75_PFMHT75_IDTight"]  = DEFAULT;
    choose["Events/HLT_PFHT800_PFMET85_PFMHT85_IDTight"]  = DEFAULT;
    choose["Events/HLT_PFHT890"]  = DEFAULT;
    choose["Events/HLT_PFHT800"]	= DEFAULT;
    choose["Events/HLT_PFHT900"]	= DEFAULT;
    choose["Events/HLT_PFJet140"]	= DEFAULT;
    choose["Events/HLT_PFJet200"]	= DEFAULT;
    choose["Events/HLT_PFJet260"]	= DEFAULT;
    choose["Events/HLT_PFJet320"]	= DEFAULT;
    choose["Events/HLT_PFJet40"]	= DEFAULT;
    choose["Events/HLT_PFJet400"]	= DEFAULT;
    choose["Events/HLT_PFJet450"]	= DEFAULT;
    choose["Events/HLT_PFJet500"]	= DEFAULT;
    choose["Events/HLT_PFJet60"]	= DEFAULT;
    choose["Events/HLT_PFJet80"]	= DEFAULT;
    choose["Events/HLT_PFMET100_PFMHT100_IDTight"]	= DEFAULT;
    choose["Events/HLT_PFMET110_PFMHT110_IDTight"]	= DEFAULT;
    choose["Events/HLT_PFMET120_PFMHT120_IDTight"]	= DEFAULT;
    choose["Events/HLT_PFMET170_HBHECleaned"]	= DEFAULT;
    choose["Events/HLT_PFMET170_JetIdCleaned"]	= DEFAULT;
    choose["Events/HLT_PFMET170_NoiseCleaned"]	= DEFAULT;
    choose["Events/HLT_PFMET170_NotCleaned"]	= DEFAULT;
    choose["Events/HLT_PFMET300"]	= DEFAULT;
    choose["Events/HLT_PFMET400"]	= DEFAULT;
    choose["Events/HLT_PFMET500"]	= DEFAULT;
    choose["Events/HLT_PFMET600"]	= DEFAULT;
    choose["Events/HLT_PFMET90_PFMHT90_IDTight"]	= DEFAULT;
    choose["Events/HLT_PFMETNoMu90_PFMHTNoMu90_IDTight"]	= DEFAULT;
    choose["Events/HLT_PFMETNoMu100_PFMHTNoMu100_IDTight"]  = DEFAULT;
    choose["Events/HLT_PFMETNoMu110_PFMHTNoMu110_IDTight"]  = DEFAULT;
    choose["Events/HLT_PFMETNoMu120_PFMHTNoMu120_IDTight"]  = DEFAULT;
    choose["Events/HLT_PFMETNoMu130_PFMHTNoMu130_IDTight"]  = DEFAULT;
    choose["Events/HLT_PFMETNoMu140_PFMHTNoMu140_IDTight"]  = DEFAULT;
    choose["Events/HLT_PFMETTypeOne120_PFMHT120_IDTight"] = DEFAULT;
    choose["Events/HLT_Photon100EBHE10"]  = DEFAULT;
    choose["Events/HLT_Photon100EB_TightID_TightIso"] = DEFAULT;
    choose["Events/HLT_Photon100EEHE10"]  = DEFAULT;
    choose["Events/HLT_Photon100EE_TightID_TightIso"] = DEFAULT;
    choose["Events/HLT_Photon110EB_TightID_TightIso"] = DEFAULT;
    choose["Events/HLT_Photon120"]	= DEFAULT;
    choose["Events/HLT_Photon125"]	= DEFAULT;
    choose["Events/HLT_Photon135_PFMET100"]	= DEFAULT;
    choose["Events/HLT_Photon150"]	= DEFAULT;
    choose["Events/HLT_Photon165_HE10"]	= DEFAULT;
    choose["Events/HLT_Photon175"]	= DEFAULT;
    choose["Events/HLT_Photon20"] = DEFAULT;
    choose["Events/HLT_Photon200"]  = DEFAULT;
    choose["Events/HLT_Photon22"]	= DEFAULT;
    choose["Events/HLT_Photon25"]	= DEFAULT;
    choose["Events/HLT_Photon250_NoHE"]	= DEFAULT;
    choose["Events/HLT_Photon30"]	= DEFAULT;
    choose["Events/HLT_Photon300_NoHE"]	= DEFAULT;
    choose["Events/HLT_Photon33"] = DEFAULT;
    choose["Events/HLT_Photon36"]	= DEFAULT;
    choose["Events/HLT_Photon50"]	= DEFAULT;
    choose["Events/HLT_Photon500"]	= DEFAULT;
    choose["Events/HLT_Photon600"]	= DEFAULT;
    choose["Events/HLT_Photon75"]	= DEFAULT;
    choose["Events/HLT_Photon90"]	= DEFAULT;
    choose["Events/HLT_Rsq0p25"]	= DEFAULT;
    choose["Events/HLT_Rsq0p30"]	= DEFAULT;
    choose["Events/HLT_Rsq0p35"]  = DEFAULT;
    choose["Events/HLT_Rsq0p40"]  = DEFAULT;
    choose["Events/HLT_RsqMR300_Rsq0p09_MR200"] = DEFAULT;
    choose["Events/HLT_RsqMR320_Rsq0p09_MR200"] = DEFAULT;
    choose["Events/HLT_RsqMR240_Rsq0p09_MR200"]	= DEFAULT;
    choose["Events/HLT_RsqMR270_Rsq0p09_MR200"]	= DEFAULT;
    choose["Events/HLT_TkMu20"]	= DEFAULT;
    choose["Events/HLT_TkMu27"]	= DEFAULT;
    choose["Events/HLT_TkMu50"]	= DEFAULT;
    choose["Events/HLTriggerFinalPath"]	= DEFAULT;
    choose["Events/HLTriggerFirstPath"]	= DEFAULT;
    choose["Events/IsoTrack_dxy"]	= DEFAULT;
    choose["Events/IsoTrack_dz"]	= DEFAULT;
    choose["Events/IsoTrack_eta"]	= DEFAULT;
    choose["Events/IsoTrack_fromPV"]	= DEFAULT;
    choose["Events/IsoTrack_isFromLostTrack"]	= DEFAULT;
    choose["Events/IsoTrack_isHighPurityTrack"]	= DEFAULT;
    choose["Events/IsoTrack_isPFcand"]	= DEFAULT;
    choose["Events/IsoTrack_miniPFRelIso_all"]	= DEFAULT;
    choose["Events/IsoTrack_miniPFRelIso_chg"]	= DEFAULT;
    choose["Events/IsoTrack_pdgId"]	= DEFAULT;
    choose["Events/IsoTrack_pfRelIso03_all"]	= DEFAULT;
    choose["Events/IsoTrack_pfRelIso03_chg"]	= DEFAULT;
    choose["Events/IsoTrack_phi"]	= DEFAULT;
    choose["Events/IsoTrack_pt"]	= DEFAULT;
    choose["Events/Jet_area"]	= DEFAULT;
    choose["Events/Jet_bRegCorr"]	= DEFAULT;
    choose["Events/Jet_bRegRes"]	= DEFAULT;
    choose["Events/Jet_btagCMVA"]	= DEFAULT;
    choose["Events/Jet_btagCSVV2"]	= DEFAULT;
    choose["Events/Jet_btagDeepB"]	= DEFAULT;
    choose["Events/Jet_btagDeepC"]	= DEFAULT;
    choose["Events/Jet_btagDeepFlavB"]	= DEFAULT;
    choose["Events/Jet_btagDeepFlavC"]	= DEFAULT;
    choose["Events/Jet_chEmEF"]	= DEFAULT;
    choose["Events/Jet_chHEF"]	= DEFAULT;
    choose["Events/Jet_cleanmask"]	= DEFAULT;
    choose["Events/Jet_electronIdx1"]	= DEFAULT;
    choose["Events/Jet_electronIdx2"]	= DEFAULT;
    choose["Events/Jet_eta"]	= DEFAULT;
    choose["Events/Jet_genJetIdx"]	= DEFAULT;
    choose["Events/Jet_hadronFlavour"]	= DEFAULT;
    choose["Events/Jet_jercCHF"]	= DEFAULT;
    choose["Events/Jet_jercCHPUF"]	= DEFAULT;
    choose["Events/Jet_jetId"]	= DEFAULT;
    choose["Events/Jet_mass"]	= DEFAULT;
    choose["Events/Jet_muEF"]	= DEFAULT;
    choose["Events/Jet_muonIdx1"]	= DEFAULT;
    choose["Events/Jet_muonIdx2"]	= DEFAULT;
    choose["Events/Jet_muonSubtrFactor"]	= DEFAULT;
    choose["Events/Jet_nConstituents"]	= DEFAULT;
    choose["Events/Jet_nElectrons"]	= DEFAULT;
    choose["Events/Jet_nMuons"]	= DEFAULT;
    choose["Events/Jet_neEmEF"]	= DEFAULT;
    choose["Events/Jet_neHEF"]	= DEFAULT;
    choose["Events/Jet_partonFlavour"]	= DEFAULT;
    choose["Events/Jet_phi"]	= DEFAULT;
    choose["Events/Jet_pt"]	= DEFAULT;
    choose["Events/Jet_puId"]	= DEFAULT;
    choose["Events/Jet_qgl"]	= DEFAULT;
    choose["Events/Jet_rawFactor"]	= DEFAULT;
    choose["Events/LHEPart_eta"]	= DEFAULT;
    choose["Events/LHEPart_mass"]	= DEFAULT;
    choose["Events/LHEPart_pdgId"]	= DEFAULT;
    choose["Events/LHEPart_phi"]	= DEFAULT;
    choose["Events/LHEPart_pt"]	= DEFAULT;
    choose["Events/LHEPdfWeight"]	= DEFAULT;
    choose["Events/LHEReweightingWeight"]	= DEFAULT;
    choose["Events/LHEScaleWeight"]	= DEFAULT;
    choose["Events/LHEWeight_originalXWGTUP"]	= DEFAULT;
    choose["Events/LHE_HT"]	= DEFAULT;
    choose["Events/LHE_HTIncoming"]	= DEFAULT;
    choose["Events/LHE_Nb"]	= DEFAULT;
    choose["Events/LHE_Nc"]	= DEFAULT;
    choose["Events/LHE_Nglu"]	= DEFAULT;
    choose["Events/LHE_Njets"]	= DEFAULT;
    choose["Events/LHE_NpLO"]	= DEFAULT;
    choose["Events/LHE_NpNLO"]	= DEFAULT;
    choose["Events/LHE_Nuds"]	= DEFAULT;
    choose["Events/LHE_Vpt"]	= DEFAULT;
    choose["Events/METFixEE2017_MetUnclustEnUpDeltaX"]  = DEFAULT;
    choose["Events/METFixEE2017_MetUnclustEnUpDeltaY"]  = DEFAULT;
    choose["Events/METFixEE2017_covXX"] = DEFAULT;
    choose["Events/METFixEE2017_covXY"] = DEFAULT;
    choose["Events/METFixEE2017_covYY"] = DEFAULT;
    choose["Events/METFixEE2017_phi"] = DEFAULT;
    choose["Events/METFixEE2017_pt"]  = DEFAULT;
    choose["Events/METFixEE2017_significance"]  = DEFAULT;
    choose["Events/METFixEE2017_sumEt"] = DEFAULT;
    choose["Events/MET_MetUnclustEnUpDeltaX"]	= DEFAULT;
    choose["Events/MET_MetUnclustEnUpDeltaY"]	= DEFAULT;
    choose["Events/MET_covXX"]	= DEFAULT;
    choose["Events/MET_covXY"]	= DEFAULT;
    choose["Events/MET_covYY"]	= DEFAULT;
    choose["Events/MET_fiducialGenPhi"]	= DEFAULT;
    choose["Events/MET_fiducialGenPt"]	= DEFAULT;
    choose["Events/MET_phi"]	= DEFAULT;
    choose["Events/MET_pt"]	= DEFAULT;
    choose["Events/MET_significance"]	= DEFAULT;
    choose["Events/MET_sumEt"]	= DEFAULT;
    choose["Events/Muon_charge"]	= DEFAULT;
    choose["Events/Muon_cleanmask"]	= DEFAULT;
    choose["Events/Muon_dxy"]	= DEFAULT;
    choose["Events/Muon_dxyErr"]	= DEFAULT;
    choose["Events/Muon_dz"]	= DEFAULT;
    choose["Events/Muon_dzErr"]	= DEFAULT;
    choose["Events/Muon_eta"]	= DEFAULT;
    choose["Events/Muon_fsrPhotonIdx"]	= DEFAULT;
    choose["Events/Muon_genPartFlav"]	= DEFAULT;
    choose["Events/Muon_genPartIdx"]	= DEFAULT;
    choose["Events/Muon_highPtId"]	= DEFAULT;
    choose["Events/Muon_inTimeMuon"]	= DEFAULT;
    choose["Events/Muon_ip3d"]	= DEFAULT;
    choose["Events/Muon_isGlobal"]	= DEFAULT;
    choose["Events/Muon_isPFcand"]	= DEFAULT;
    choose["Events/Muon_isTracker"]	= DEFAULT;
    choose["Events/Muon_jetIdx"]	= DEFAULT;
    choose["Events/Muon_jetPtRelv2"]	= DEFAULT;
    choose["Events/Muon_jetRelIso"]	= DEFAULT;
    choose["Events/Muon_looseId"]	= DEFAULT;
    choose["Events/Muon_mass"]	= DEFAULT;
    choose["Events/Muon_mediumId"]	= DEFAULT;
    choose["Events/Muon_mediumPromptId"]	= DEFAULT;
    choose["Events/Muon_miniIsoId"]	= DEFAULT;
    choose["Events/Muon_miniPFRelIso_all"]	= DEFAULT;
    choose["Events/Muon_miniPFRelIso_chg"]	= DEFAULT;
    choose["Events/Muon_multiIsoId"]	= DEFAULT;
    choose["Events/Muon_mvaId"]	= DEFAULT;
    choose["Events/Muon_mvaLowPt"]	= DEFAULT;
    choose["Events/Muon_mvaTTH"]	= DEFAULT;
    choose["Events/Muon_nStations"]	= DEFAULT;
    choose["Events/Muon_nTrackerLayers"]	= DEFAULT;
    choose["Events/Muon_pdgId"]	= DEFAULT;
    choose["Events/Muon_pfIsoId"]	= DEFAULT;
    choose["Events/Muon_pfRelIso03_all"]	= DEFAULT;
    choose["Events/Muon_pfRelIso03_chg"]	= DEFAULT;
    choose["Events/Muon_pfRelIso04_all"]	= DEFAULT;
    choose["Events/Muon_phi"]	= DEFAULT;
    choose["Events/Muon_pt"]	= DEFAULT;
    choose["Events/Muon_ptErr"]	= DEFAULT;
    choose["Events/Muon_segmentComp"]	= DEFAULT;
    choose["Events/Muon_sip3d"]	= DEFAULT;
    choose["Events/Muon_softId"]	= DEFAULT;
    choose["Muon_softMva"]  = DEFAULT;
    choose["Events/Muon_softMvaId"]	= DEFAULT;
    choose["Events/Muon_tightCharge"]	= DEFAULT;
    choose["Events/Muon_tightId"]	= DEFAULT;
    choose["Events/Muon_tkIsoId"]	= DEFAULT;
    choose["Events/Muon_tkRelIso"]	= DEFAULT;
    choose["Events/Muon_triggerIdLoose"]	= DEFAULT;
    choose["Events/Muon_tunepRelPt"]	= DEFAULT;
    choose["Events/OtherPV_z"]	= DEFAULT;
    choose["Events/PSWeight"]	= DEFAULT;
    choose["Events/PV_chi2"]	= DEFAULT;
    choose["Events/PV_ndof"]	= DEFAULT;
    choose["Events/PV_npvs"]	= DEFAULT;
    choose["Events/PV_npvsGood"]	= DEFAULT;
    choose["Events/PV_score"]	= DEFAULT;
    choose["Events/PV_x"]	= DEFAULT;
    choose["Events/PV_y"]	= DEFAULT;
    choose["Events/PV_z"]	= DEFAULT;
    choose["Events/Photon_charge"]	= DEFAULT;
    choose["Events/Photon_cleanmask"]	= DEFAULT;
    choose["Events/Photon_cutBased"]	= DEFAULT;
    choose["Events/Photon_cutBased17Bitmap"]	= DEFAULT;
    choose["Events/Photon_eCorr"]	= DEFAULT;
    choose["Events/Photon_electronIdx"]	= DEFAULT;
    choose["Events/Photon_electronVeto"]	= DEFAULT;
    choose["Events/Photon_energyErr"]	= DEFAULT;
    choose["Events/Photon_eta"]	= DEFAULT;
    choose["Events/Photon_genPartFlav"]	= DEFAULT;
    choose["Events/Photon_genPartIdx"]	= DEFAULT;
    choose["Events/Photon_hoe"]	= DEFAULT;
    choose["Events/Photon_isScEtaEB"]	= DEFAULT;
    choose["Events/Photon_isScEtaEE"]	= DEFAULT;
    choose["Events/Photon_jetIdx"]	= DEFAULT;
    choose["Events/Photon_mass"]	= DEFAULT;
    choose["Events/Photon_mvaID"]	= DEFAULT;
    choose["Events/Photon_mvaID17"]	= DEFAULT;
    choose["Events/Photon_mvaID17_WP80"]	= DEFAULT;
    choose["Events/Photon_mvaID17_WP90"]	= DEFAULT;
    choose["Events/Photon_mvaID_WP80"]	= DEFAULT;
    choose["Events/Photon_mvaID_WP90"]	= DEFAULT;
    choose["Events/Photon_pdgId"]	= DEFAULT;
    choose["Events/Photon_pfRelIso03_all"]	= DEFAULT;
    choose["Events/Photon_pfRelIso03_chg"]	= DEFAULT;
    choose["Events/Photon_phi"]	= DEFAULT;
    choose["Events/Photon_pixelSeed"]	= DEFAULT;
    choose["Events/Photon_pt"]	= DEFAULT;
    choose["Events/Photon_r9"]	= DEFAULT;
    choose["Events/Photon_seedGain"]	= DEFAULT;
    choose["Events/Photon_sieie"]	= DEFAULT;
    choose["Events/Photon_vidNestedWPBitmap"]	= DEFAULT;
    choose["Events/Pileup_gpudensity"]	= DEFAULT;
    choose["Events/Pileup_nPU"]	= DEFAULT;
    choose["Events/Pileup_nTrueInt"]	= DEFAULT;
    choose["Events/Pileup_pudensity"]	= DEFAULT;
    choose["Events/Pileup_sumEOOT"]	= DEFAULT;
    choose["Events/Pileup_sumLOOT"]	= DEFAULT;
    choose["Events/PuppiMET_phi"]	= DEFAULT;
    choose["Events/PuppiMET_pt"]	= DEFAULT;
    choose["Events/PuppiMET_sumEt"]	= DEFAULT;
    choose["Events/RawMET_phi"]	= DEFAULT;
    choose["Events/RawMET_pt"]	= DEFAULT;
    choose["Events/RawMET_sumEt"]	= DEFAULT;
    choose["Events/SubJet_btagCMVA"]	= DEFAULT;
    choose["Events/SubJet_btagCSVV2"]	= DEFAULT;
    choose["Events/SubJet_btagDeepB"]	= DEFAULT;
    choose["Events/SubJet_eta"]	= DEFAULT;
    choose["Events/SubJet_mass"]	= DEFAULT;
    choose["Events/SubJet_n2b1"]	= DEFAULT;
    choose["Events/SubJet_n3b1"]	= DEFAULT;
    choose["Events/SubJet_phi"]	= DEFAULT;
    choose["Events/SubJet_pt"]	= DEFAULT;
    choose["Events/SubJet_rawFactor"]	= DEFAULT;
    choose["Events/SubJet_tau1"]	= DEFAULT;
    choose["Events/SubJet_tau2"]	= DEFAULT;
    choose["Events/SubJet_tau3"]	= DEFAULT;
    choose["Events/SubJet_tau4"]	= DEFAULT;
    choose["Events/Tau_charge"]	= DEFAULT;
    choose["Events/Tau_chargedIso"]	= DEFAULT;
    choose["Events/Tau_cleanmask"]	= DEFAULT;
    choose["Events/Tau_decayMode"]	= DEFAULT;
    choose["Events/Tau_dxy"]	= DEFAULT;
    choose["Events/Tau_dz"]	= DEFAULT;
    choose["Events/Tau_eta"]	= DEFAULT;
    choose["Events/Tau_genPartFlav"]	= DEFAULT;
    choose["Events/Tau_genPartIdx"]	= DEFAULT;
    choose["Events/Tau_idAntiEle"]	= DEFAULT;
    choose["Events/Tau_idAntiEle2018"]	= DEFAULT;
    choose["Events/Tau_idAntiMu"]	= DEFAULT;
    choose["Events/Tau_idDecayMode"]	= DEFAULT;
    choose["Events/Tau_idDecayModeNewDMs"]	= DEFAULT;
    choose["Events/Tau_idDeepTau2017v2p1VSe"]	= DEFAULT;
    choose["Events/Tau_idDeepTau2017v2p1VSjet"]	= DEFAULT;
    choose["Events/Tau_idDeepTau2017v2p1VSmu"]	= DEFAULT;
    choose["Events/Tau_idMVAnewDM2017v2"]	= DEFAULT;
    choose["Events/Tau_idMVAoldDM"]	= DEFAULT;
    choose["Events/Tau_idMVAoldDM2017v1"]	= DEFAULT;
    choose["Events/Tau_idMVAoldDM2017v2"]	= DEFAULT;
    choose["Events/Tau_idMVAoldDMdR032017v2"]	= DEFAULT;
    choose["Events/Tau_jetIdx"]	= DEFAULT;
    choose["Events/Tau_leadTkDeltaEta"]	= DEFAULT;
    choose["Events/Tau_leadTkDeltaPhi"]	= DEFAULT;
    choose["Events/Tau_leadTkPtOverTauPt"]	= DEFAULT;
    choose["Events/Tau_mass"]	= DEFAULT;
    choose["Events/Tau_neutralIso"]	= DEFAULT;
    choose["Events/Tau_phi"]	= DEFAULT;
    choose["Events/Tau_photonsOutsideSignalCone"]	= DEFAULT;
    choose["Events/Tau_pt"]	= DEFAULT;
    choose["Events/Tau_puCorr"]	= DEFAULT;
    choose["Events/Tau_rawAntiEle"]	= DEFAULT;
    choose["Events/Tau_rawAntiEle2018"]	= DEFAULT;
    choose["Events/Tau_rawAntiEleCat"]	= DEFAULT;
    choose["Events/Tau_rawAntiEleCat2018"]	= DEFAULT;
    choose["Events/Tau_rawDeepTau2017v2p1VSe"]	= DEFAULT;
    choose["Events/Tau_rawDeepTau2017v2p1VSjet"]	= DEFAULT;
    choose["Events/Tau_rawDeepTau2017v2p1VSmu"]	= DEFAULT;
    choose["Events/Tau_rawIso"]	= DEFAULT;
    choose["Events/Tau_rawIsodR03"]	= DEFAULT;
    choose["Events/Tau_rawMVAnewDM2017v2"]	= DEFAULT;
    choose["Events/Tau_rawMVAoldDM"]	= DEFAULT;
    choose["Events/Tau_rawMVAoldDM2017v1"]	= DEFAULT;
    choose["Events/Tau_rawMVAoldDM2017v2"]	= DEFAULT;
    choose["Events/Tau_rawMVAoldDMdR032017v2"]	= DEFAULT;
    choose["Events/TkMET_phi"]	= DEFAULT;
    choose["Events/TkMET_pt"]	= DEFAULT;
    choose["Events/TkMET_sumEt"]	= DEFAULT;
    choose["Events/TrigObj_eta"]	= DEFAULT;
    choose["Events/TrigObj_filterBits"]	= DEFAULT;
    choose["Events/TrigObj_id"]	= DEFAULT;
    choose["Events/TrigObj_l1charge"]	= DEFAULT;
    choose["Events/TrigObj_l1iso"]	= DEFAULT;
    choose["Events/TrigObj_l1pt"]	= DEFAULT;
    choose["Events/TrigObj_l1pt_2"]	= DEFAULT;
    choose["Events/TrigObj_l2pt"]	= DEFAULT;
    choose["Events/TrigObj_phi"]	= DEFAULT;
    choose["Events/TrigObj_pt"]	= DEFAULT;
    choose["Events/btagWeight_CMVA"]	= DEFAULT;
    choose["Events/btagWeight_CSVV2"]	= DEFAULT;
    choose["Events/event"]	= DEFAULT;
    choose["Events/fixedGridRhoFastjetAll"]	= DEFAULT;
    choose["Events/fixedGridRhoFastjetCentral"]	= DEFAULT;
    choose["Events/fixedGridRhoFastjetCentralCalo"]	= DEFAULT;
    choose["Events/fixedGridRhoFastjetCentralChargedPileUp"]	= DEFAULT;
    choose["Events/fixedGridRhoFastjetCentralNeutral"]	= DEFAULT;
    choose["Events/genTtbarId"]	= DEFAULT;
    choose["Events/genWeight"]	= DEFAULT;
    choose["Events/luminosityBlock"]	= DEFAULT;
    choose["Events/run"]	= DEFAULT;

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
                if ( choose.find(key) != choose.end() )
                  {
                    choose[key] = true;
                    std::cout << "	" << key << std::endl;
                  }
                else
                  {
                    std::cout << "	** error ** unknown branch: "
                              << key
                              << std::endl
                              << "Please fix and try again. Bye!"
                              << std::endl;
                    exit(0);
                  }
              }
          }
      }
    if ( choose["Events/CaloMET_phi"] )
      input->select("Events/CaloMET_phi", 	CaloMET_phi);
    if ( choose["Events/CaloMET_pt"] )
      input->select("Events/CaloMET_pt", 	CaloMET_pt);
    if ( choose["Events/CaloMET_sumEt"] )
      input->select("Events/CaloMET_sumEt", 	CaloMET_sumEt);
    if ( choose["Events/ChsMET_phi"] )
      input->select("Events/ChsMET_phi", 	ChsMET_phi);
    if ( choose["Events/ChsMET_pt"] )
      input->select("Events/ChsMET_pt", 	ChsMET_pt);
    if ( choose["Events/ChsMET_sumEt"] )
      input->select("Events/ChsMET_sumEt", 	ChsMET_sumEt);
    if ( choose["Events/CorrT1METJet_area"] )
      input->select("Events/CorrT1METJet_area", 	CorrT1METJet_area);
    if ( choose["Events/CorrT1METJet_eta"] )
      input->select("Events/CorrT1METJet_eta", 	CorrT1METJet_eta);
    if ( choose["Events/CorrT1METJet_muonSubtrFactor"] )
      input->select("Events/CorrT1METJet_muonSubtrFactor",
                     CorrT1METJet_muonSubtrFactor);
    if ( choose["Events/CorrT1METJet_phi"] )
      input->select("Events/CorrT1METJet_phi", 	CorrT1METJet_phi);
    if ( choose["Events/CorrT1METJet_rawPt"] )
      input->select("Events/CorrT1METJet_rawPt", 	CorrT1METJet_rawPt);
    if ( choose["Events/Electron_charge"] )
      input->select("Events/Electron_charge", 	Electron_charge);
    if ( choose["Events/Electron_cleanmask"] )
      input->select("Events/Electron_cleanmask", 	Electron_cleanmask);
    if ( choose["Events/Electron_convVeto"] )
      input->select("Events/Electron_convVeto", 	Electron_convVeto);
    if ( choose["Events/Electron_cutBased"] )
      input->select("Events/Electron_cutBased", 	Electron_cutBased);
    if ( choose["Events/Electron_cutBased_Fall17_V1"] )
      input->select("Events/Electron_cutBased_Fall17_V1",
                     Electron_cutBased_Fall17_V1);
    if ( choose["Events/Electron_cutBased_HEEP"] )
      input->select("Events/Electron_cutBased_HEEP",
                     Electron_cutBased_HEEP);
    if ( choose["Events/Electron_cutBased_HLTPreSel"] )
      input->select("Events/Electron_cutBased_HLTPreSel",
                     Electron_cutBased_HLTPreSel);
    if ( choose["Events/Electron_cutBased_Spring15"] )
      input->select("Events/Electron_cutBased_Spring15",
                     Electron_cutBased_Spring15);
    if ( choose["Events/Electron_cutBased_Sum16"] )
      input->select("Events/Electron_cutBased_Sum16",
                     Electron_cutBased_Sum16);
    if ( choose["Events/Electron_deltaEtaSC"] )
      input->select("Events/Electron_deltaEtaSC", 	Electron_deltaEtaSC);
    if ( choose["Events/Electron_dr03EcalRecHitSumEt"] )
      input->select("Events/Electron_dr03EcalRecHitSumEt",
                     Electron_dr03EcalRecHitSumEt);
    if ( choose["Events/Electron_dr03HcalDepth1TowerSumEt"] )
      input->select("Events/Electron_dr03HcalDepth1TowerSumEt",
                     Electron_dr03HcalDepth1TowerSumEt);
    if ( choose["Events/Electron_dr03TkSumPt"] )
      input->select("Events/Electron_dr03TkSumPt", 	Electron_dr03TkSumPt);
    if ( choose["Events/Electron_dr03TkSumPtHEEP"] )
      input->select("Events/Electron_dr03TkSumPtHEEP",
                     Electron_dr03TkSumPtHEEP);
    if ( choose["Events/Electron_dxy"] )
      input->select("Events/Electron_dxy", 	Electron_dxy);
    if ( choose["Events/Electron_dxyErr"] )
      input->select("Events/Electron_dxyErr", 	Electron_dxyErr);
    if ( choose["Events/Electron_dz"] )
      input->select("Events/Electron_dz", 	Electron_dz);
    if ( choose["Events/Electron_dzErr"] )
      input->select("Events/Electron_dzErr", 	Electron_dzErr);
    if ( choose["Events/Electron_eCorr"] )
      input->select("Events/Electron_eCorr", 	Electron_eCorr);
    if ( choose["Events/Electron_eInvMinusPInv"] )
      input->select("Events/Electron_eInvMinusPInv",
                     Electron_eInvMinusPInv);
    if ( choose["Events/Electron_energyErr"] )
      input->select("Events/Electron_energyErr", 	Electron_energyErr);
    if ( choose["Events/Electron_eta"] )
      input->select("Events/Electron_eta", 	Electron_eta);
    if ( choose["Events/Electron_genPartFlav"] )
      input->select("Events/Electron_genPartFlav", 	Electron_genPartFlav);
    if ( choose["Events/Electron_genPartIdx"] )
      input->select("Events/Electron_genPartIdx", 	Electron_genPartIdx);
    if ( choose["Events/Electron_hoe"] )
      input->select("Events/Electron_hoe", 	Electron_hoe);
    if ( choose["Events/Electron_ip3d"] )
      input->select("Events/Electron_ip3d", 	Electron_ip3d);
    if ( choose["Events/Electron_isPFcand"] )
      input->select("Events/Electron_isPFcand", 	Electron_isPFcand);
    if ( choose["Events/Electron_jetIdx"] )
      input->select("Events/Electron_jetIdx", 	Electron_jetIdx);
    if ( choose["Events/Electron_jetPtRelv2"] )
      input->select("Events/Electron_jetPtRelv2", 	Electron_jetPtRelv2);
    if ( choose["Events/Electron_jetRelIso"] )
      input->select("Events/Electron_jetRelIso", 	Electron_jetRelIso);
    if ( choose["Events/Electron_lostHits"] )
      input->select("Events/Electron_lostHits", 	Electron_lostHits);
    if ( choose["Events/Electron_mass"] )
      input->select("Events/Electron_mass", 	Electron_mass);
    if ( choose["Events/Electron_miniPFRelIso_all"] )
      input->select("Events/Electron_miniPFRelIso_all",
                     Electron_miniPFRelIso_all);
    if ( choose["Events/Electron_miniPFRelIso_chg"] )
      input->select("Events/Electron_miniPFRelIso_chg",
                     Electron_miniPFRelIso_chg);
    if ( choose["Events/Electron_mvaFall17V1Iso"] )
      input->select("Events/Electron_mvaFall17V1Iso",
                     Electron_mvaFall17V1Iso);
    if ( choose["Events/Electron_mvaFall17V1Iso_WP80"] )
      input->select("Events/Electron_mvaFall17V1Iso_WP80",
                     Electron_mvaFall17V1Iso_WP80);
    if ( choose["Events/Electron_mvaFall17V1Iso_WP90"] )
      input->select("Events/Electron_mvaFall17V1Iso_WP90",
                     Electron_mvaFall17V1Iso_WP90);
    if ( choose["Events/Electron_mvaFall17V1Iso_WPL"] )
      input->select("Events/Electron_mvaFall17V1Iso_WPL",
                     Electron_mvaFall17V1Iso_WPL);
    if ( choose["Events/Electron_mvaFall17V1noIso"] )
      input->select("Events/Electron_mvaFall17V1noIso",
                     Electron_mvaFall17V1noIso);
    if ( choose["Events/Electron_mvaFall17V1noIso_WP80"] )
      input->select("Events/Electron_mvaFall17V1noIso_WP80",
                     Electron_mvaFall17V1noIso_WP80);
    if ( choose["Events/Electron_mvaFall17V1noIso_WP90"] )
      input->select("Events/Electron_mvaFall17V1noIso_WP90",
                     Electron_mvaFall17V1noIso_WP90);
    if ( choose["Events/Electron_mvaFall17V1noIso_WPL"] )
      input->select("Events/Electron_mvaFall17V1noIso_WPL",
                     Electron_mvaFall17V1noIso_WPL);
    if ( choose["Events/Electron_mvaFall17V2Iso"] )
      input->select("Events/Electron_mvaFall17V2Iso",
                     Electron_mvaFall17V2Iso);
    if ( choose["Events/Electron_mvaFall17V2Iso_WP80"] )
      input->select("Events/Electron_mvaFall17V2Iso_WP80",
                     Electron_mvaFall17V2Iso_WP80);
    if ( choose["Events/Electron_mvaFall17V2Iso_WP90"] )
      input->select("Events/Electron_mvaFall17V2Iso_WP90",
                     Electron_mvaFall17V2Iso_WP90);
    if ( choose["Events/Electron_mvaFall17V2Iso_WPL"] )
      input->select("Events/Electron_mvaFall17V2Iso_WPL",
                     Electron_mvaFall17V2Iso_WPL);
    if ( choose["Events/Electron_mvaFall17V2noIso"] )
      input->select("Events/Electron_mvaFall17V2noIso",
                     Electron_mvaFall17V2noIso);
    if ( choose["Events/Electron_mvaFall17V2noIso_WP80"] )
      input->select("Events/Electron_mvaFall17V2noIso_WP80",
                     Electron_mvaFall17V2noIso_WP80);
    if ( choose["Events/Electron_mvaFall17V2noIso_WP90"] )
      input->select("Events/Electron_mvaFall17V2noIso_WP90",
                     Electron_mvaFall17V2noIso_WP90);
    if ( choose["Events/Electron_mvaFall17V2noIso_WPL"] )
      input->select("Events/Electron_mvaFall17V2noIso_WPL",
                     Electron_mvaFall17V2noIso_WPL);
    if ( choose["Events/Electron_mvaSpring16GP"] )
      input->select("Events/Electron_mvaSpring16GP",
                     Electron_mvaSpring16GP);
    if ( choose["Events/Electron_mvaSpring16GP_WP80"] )
      input->select("Events/Electron_mvaSpring16GP_WP80",
                     Electron_mvaSpring16GP_WP80);
    if ( choose["Events/Electron_mvaSpring16GP_WP90"] )
      input->select("Events/Electron_mvaSpring16GP_WP90",
                     Electron_mvaSpring16GP_WP90);
    if ( choose["Events/Electron_mvaSpring16HZZ"] )
      input->select("Events/Electron_mvaSpring16HZZ",
                     Electron_mvaSpring16HZZ);
    if ( choose["Events/Electron_mvaSpring16HZZ_WPL"] )
      input->select("Events/Electron_mvaSpring16HZZ_WPL",
                     Electron_mvaSpring16HZZ_WPL);
    if ( choose["Events/Electron_mvaTTH"] )
      input->select("Events/Electron_mvaTTH", 	Electron_mvaTTH);
    if ( choose["Events/Electron_pdgId"] )
      input->select("Events/Electron_pdgId", 	Electron_pdgId);
    if ( choose["Events/Electron_pfRelIso03_all"] )
      input->select("Events/Electron_pfRelIso03_all",
                     Electron_pfRelIso03_all);
    if ( choose["Events/Electron_pfRelIso03_chg"] )
      input->select("Events/Electron_pfRelIso03_chg",
                     Electron_pfRelIso03_chg);
    if ( choose["Events/Electron_phi"] )
      input->select("Events/Electron_phi", 	Electron_phi);
    if ( choose["Events/Electron_photonIdx"] )
      input->select("Events/Electron_photonIdx", 	Electron_photonIdx);
    if ( choose["Events/Electron_pt"] )
      input->select("Events/Electron_pt", 	Electron_pt);
    if ( choose["Events/Electron_r9"] )
      input->select("Events/Electron_r9", 	Electron_r9);
    if ( choose["Events/Electron_seedGain"] )
      input->select("Events/Electron_seedGain", 	Electron_seedGain);
    if ( choose["Events/Electron_sieie"] )
      input->select("Events/Electron_sieie", 	Electron_sieie);
    if ( choose["Events/Electron_sip3d"] )
      input->select("Events/Electron_sip3d", 	Electron_sip3d);
    if ( choose["Events/Electron_tightCharge"] )
      input->select("Events/Electron_tightCharge", 	Electron_tightCharge);
    if ( choose["Events/Electron_vidNestedWPBitmap"] )
      input->select("Events/Electron_vidNestedWPBitmap",
                     Electron_vidNestedWPBitmap);
    if ( choose["Events/Electron_vidNestedWPBitmapHEEP"] )
      input->select("Events/Electron_vidNestedWPBitmapHEEP",
                     Electron_vidNestedWPBitmapHEEP);
    if ( choose["Events/Electron_vidNestedWPBitmapSpring15"] )
      input->select("Events/Electron_vidNestedWPBitmapSpring15",
                     Electron_vidNestedWPBitmapSpring15);
    if ( choose["Events/Electron_vidNestedWPBitmapSum16"] )
      input->select("Events/Electron_vidNestedWPBitmapSum16",
                     Electron_vidNestedWPBitmapSum16);
    if ( choose["Events/FatJet_area"] )
      input->select("Events/FatJet_area", 	FatJet_area);
    if ( choose["Events/FatJet_btagCMVA"] )
      input->select("Events/FatJet_btagCMVA", 	FatJet_btagCMVA);
    if ( choose["Events/FatJet_btagCSVV2"] )
      input->select("Events/FatJet_btagCSVV2", 	FatJet_btagCSVV2);
    if ( choose["Events/FatJet_btagDDBvL"] )
      input->select("Events/FatJet_btagDDBvL", 	FatJet_btagDDBvL);
    if ( choose["Events/FatJet_btagDDBvL_noMD"] )
      input->select("Events/FatJet_btagDDBvL_noMD", 	FatJet_btagDDBvL_noMD);
    if ( choose["Events/FatJet_btagDDCvB"] )
      input->select("Events/FatJet_btagDDCvB", 	FatJet_btagDDCvB);
    if ( choose["Events/FatJet_btagDDCvB_noMD"] )
      input->select("Events/FatJet_btagDDCvB_noMD", 	FatJet_btagDDCvB_noMD);
    if ( choose["Events/FatJet_btagDDCvL"] )
      input->select("Events/FatJet_btagDDCvL", 	FatJet_btagDDCvL);
    if ( choose["Events/FatJet_btagDDCvL_noMD"] )
      input->select("Events/FatJet_btagDDCvL_noMD", 	FatJet_btagDDCvL_noMD);
    if ( choose["Events/FatJet_btagDeepB"] )
      input->select("Events/FatJet_btagDeepB", 	FatJet_btagDeepB);
    if ( choose["Events/FatJet_btagHbb"] )
      input->select("Events/FatJet_btagHbb", 	FatJet_btagHbb);
    if ( choose["Events/FatJet_deepTagMD_H4qvsQCD"] )
      input->select("Events/FatJet_deepTagMD_H4qvsQCD",
                     FatJet_deepTagMD_H4qvsQCD);
    if ( choose["Events/FatJet_deepTagMD_HbbvsQCD"] )
      input->select("Events/FatJet_deepTagMD_HbbvsQCD",
                     FatJet_deepTagMD_HbbvsQCD);
    if ( choose["Events/FatJet_deepTagMD_TvsQCD"] )
      input->select("Events/FatJet_deepTagMD_TvsQCD",
                     FatJet_deepTagMD_TvsQCD);
    if ( choose["Events/FatJet_deepTagMD_WvsQCD"] )
      input->select("Events/FatJet_deepTagMD_WvsQCD",
                     FatJet_deepTagMD_WvsQCD);
    if ( choose["Events/FatJet_deepTagMD_ZHbbvsQCD"] )
      input->select("Events/FatJet_deepTagMD_ZHbbvsQCD",
                     FatJet_deepTagMD_ZHbbvsQCD);
    if ( choose["Events/FatJet_deepTagMD_ZHccvsQCD"] )
      input->select("Events/FatJet_deepTagMD_ZHccvsQCD",
                     FatJet_deepTagMD_ZHccvsQCD);
    if ( choose["Events/FatJet_deepTagMD_ZbbvsQCD"] )
      input->select("Events/FatJet_deepTagMD_ZbbvsQCD",
                     FatJet_deepTagMD_ZbbvsQCD);
    if ( choose["Events/FatJet_deepTagMD_ZvsQCD"] )
      input->select("Events/FatJet_deepTagMD_ZvsQCD",
                     FatJet_deepTagMD_ZvsQCD);
    if ( choose["Events/FatJet_deepTagMD_bbvsLight"] )
      input->select("Events/FatJet_deepTagMD_bbvsLight",
                     FatJet_deepTagMD_bbvsLight);
    if ( choose["Events/FatJet_deepTagMD_ccvsLight"] )
      input->select("Events/FatJet_deepTagMD_ccvsLight",
                     FatJet_deepTagMD_ccvsLight);
    if ( choose["Events/FatJet_deepTag_H"] )
      input->select("Events/FatJet_deepTag_H", 	FatJet_deepTag_H);
    if ( choose["Events/FatJet_deepTag_QCD"] )
      input->select("Events/FatJet_deepTag_QCD", 	FatJet_deepTag_QCD);
    if ( choose["Events/FatJet_deepTag_QCDothers"] )
      input->select("Events/FatJet_deepTag_QCDothers",
                     FatJet_deepTag_QCDothers);
    if ( choose["Events/FatJet_deepTag_TvsQCD"] )
      input->select("Events/FatJet_deepTag_TvsQCD", 	FatJet_deepTag_TvsQCD);
    if ( choose["Events/FatJet_deepTag_WvsQCD"] )
      input->select("Events/FatJet_deepTag_WvsQCD", 	FatJet_deepTag_WvsQCD);
    if ( choose["Events/FatJet_deepTag_ZvsQCD"] )
      input->select("Events/FatJet_deepTag_ZvsQCD", 	FatJet_deepTag_ZvsQCD);
    if ( choose["Events/FatJet_eta"] )
      input->select("Events/FatJet_eta", 	FatJet_eta);
    if ( choose["Events/FatJet_jetId"] )
      input->select("Events/FatJet_jetId", 	FatJet_jetId);
    if ( choose["Events/FatJet_mass"] )
      input->select("Events/FatJet_mass", 	FatJet_mass);
    if ( choose["Events/FatJet_msoftdrop"] )
      input->select("Events/FatJet_msoftdrop", 	FatJet_msoftdrop);
    if ( choose["Events/FatJet_n2b1"] )
      input->select("Events/FatJet_n2b1", 	FatJet_n2b1);
    if ( choose["Events/FatJet_n3b1"] )
      input->select("Events/FatJet_n3b1", 	FatJet_n3b1);
    if ( choose["Events/FatJet_phi"] )
      input->select("Events/FatJet_phi", 	FatJet_phi);
    if ( choose["Events/FatJet_pt"] )
      input->select("Events/FatJet_pt", 	FatJet_pt);
    if ( choose["Events/FatJet_rawFactor"] )
      input->select("Events/FatJet_rawFactor", 	FatJet_rawFactor);
    if ( choose["Events/FatJet_subJetIdx1"] )
      input->select("Events/FatJet_subJetIdx1", 	FatJet_subJetIdx1);
    if ( choose["Events/FatJet_subJetIdx2"] )
      input->select("Events/FatJet_subJetIdx2", 	FatJet_subJetIdx2);
    if ( choose["Events/FatJet_tau1"] )
      input->select("Events/FatJet_tau1", 	FatJet_tau1);
    if ( choose["Events/FatJet_tau2"] )
      input->select("Events/FatJet_tau2", 	FatJet_tau2);
    if ( choose["Events/FatJet_tau3"] )
      input->select("Events/FatJet_tau3", 	FatJet_tau3);
    if ( choose["Events/FatJet_tau4"] )
      input->select("Events/FatJet_tau4", 	FatJet_tau4);
    if ( choose["Events/Flag_BadChargedCandidateFilter"] )
      input->select("Events/Flag_BadChargedCandidateFilter",
                     Flag_BadChargedCandidateFilter);
    if ( choose["Events/Flag_BadChargedCandidateSummer16Filter"] )
      input->select("Events/Flag_BadChargedCandidateSummer16Filter",
                     Flag_BadChargedCandidateSummer16Filter);
    if ( choose["Events/Flag_BadPFMuonFilter"] )
      input->select("Events/Flag_BadPFMuonFilter", 	Flag_BadPFMuonFilter);
    if ( choose["Events/Flag_BadPFMuonSummer16Filter"] )
      input->select("Events/Flag_BadPFMuonSummer16Filter",
                     Flag_BadPFMuonSummer16Filter);
    if ( choose["Events/Flag_CSCTightHalo2015Filter"] )
      input->select("Events/Flag_CSCTightHalo2015Filter",
                     Flag_CSCTightHalo2015Filter);
    if ( choose["Events/Flag_CSCTightHaloFilter"] )
      input->select("Events/Flag_CSCTightHaloFilter",
                     Flag_CSCTightHaloFilter);
    if ( choose["Events/Flag_CSCTightHaloTrkMuUnvetoFilter"] )
      input->select("Events/Flag_CSCTightHaloTrkMuUnvetoFilter",
                     Flag_CSCTightHaloTrkMuUnvetoFilter);
    if ( choose["Events/Flag_EcalDeadCellBoundaryEnergyFilter"] )
      input->select("Events/Flag_EcalDeadCellBoundaryEnergyFilter",
                     Flag_EcalDeadCellBoundaryEnergyFilter);
    if ( choose["Events/Flag_EcalDeadCellTriggerPrimitiveFilter"] )
      input->select("Events/Flag_EcalDeadCellTriggerPrimitiveFilter",
                     Flag_EcalDeadCellTriggerPrimitiveFilter);
    if ( choose["Events/Flag_HBHENoiseFilter"] )
      input->select("Events/Flag_HBHENoiseFilter", 	Flag_HBHENoiseFilter);
    if ( choose["Events/Flag_HBHENoiseIsoFilter"] )
      input->select("Events/Flag_HBHENoiseIsoFilter",
                     Flag_HBHENoiseIsoFilter);
    if ( choose["Events/Flag_HcalStripHaloFilter"] )
      input->select("Events/Flag_HcalStripHaloFilter",
                     Flag_HcalStripHaloFilter);
    if ( choose["Events/Flag_METFilters"] )
      input->select("Events/Flag_METFilters", 	Flag_METFilters);
    if ( choose["Events/Flag_chargedHadronTrackResolutionFilter"] )
      input->select("Events/Flag_chargedHadronTrackResolutionFilter",
                     Flag_chargedHadronTrackResolutionFilter);
    if ( choose["Events/Flag_ecalBadCalibFilter"] )
      input->select("Events/Flag_ecalBadCalibFilter",
                     Flag_ecalBadCalibFilter);
    if ( choose["Events/Flag_ecalBadCalibFilterV2"] )
      input->select("Events/Flag_ecalBadCalibFilterV2",
                     Flag_ecalBadCalibFilterV2);
    if ( choose["Events/Flag_ecalLaserCorrFilter"] )
      input->select("Events/Flag_ecalLaserCorrFilter",
                     Flag_ecalLaserCorrFilter);
    if ( choose["Events/Flag_eeBadScFilter"] )
      input->select("Events/Flag_eeBadScFilter", 	Flag_eeBadScFilter);
    if ( choose["Events/Flag_globalSuperTightHalo2016Filter"] )
      input->select("Events/Flag_globalSuperTightHalo2016Filter",
                     Flag_globalSuperTightHalo2016Filter);
    if ( choose["Events/Flag_globalTightHalo2016Filter"] )
      input->select("Events/Flag_globalTightHalo2016Filter",
                     Flag_globalTightHalo2016Filter);
    if ( choose["Events/Flag_goodVertices"] )
      input->select("Events/Flag_goodVertices", 	Flag_goodVertices);
    if ( choose["Events/Flag_hcalLaserEventFilter"] )
      input->select("Events/Flag_hcalLaserEventFilter",
                     Flag_hcalLaserEventFilter);
    if ( choose["Events/Flag_muonBadTrackFilter"] )
      input->select("Events/Flag_muonBadTrackFilter",
                     Flag_muonBadTrackFilter);
    if ( choose["Events/Flag_trkPOGFilters"] )
      input->select("Events/Flag_trkPOGFilters", 	Flag_trkPOGFilters);
    if ( choose["Events/Flag_trkPOG_logErrorTooManyClusters"] )
      input->select("Events/Flag_trkPOG_logErrorTooManyClusters",
                     Flag_trkPOG_logErrorTooManyClusters);
    if ( choose["Events/Flag_trkPOG_manystripclus53X"] )
      input->select("Events/Flag_trkPOG_manystripclus53X",
                     Flag_trkPOG_manystripclus53X);
    if ( choose["Events/Flag_trkPOG_toomanystripclus53X"] )
      input->select("Events/Flag_trkPOG_toomanystripclus53X",
                     Flag_trkPOG_toomanystripclus53X);
    if ( choose["Events/FsrPhoton_dROverEt2"] )
      input->select("Events/FsrPhoton_dROverEt2", 	FsrPhoton_dROverEt2);
    if ( choose["Events/FsrPhoton_eta"] )
      input->select("Events/FsrPhoton_eta", 	FsrPhoton_eta);
    if ( choose["Events/FsrPhoton_muonIdx"] )
      input->select("Events/FsrPhoton_muonIdx", 	FsrPhoton_muonIdx);
    if ( choose["Events/FsrPhoton_phi"] )
      input->select("Events/FsrPhoton_phi", 	FsrPhoton_phi);
    if ( choose["Events/FsrPhoton_pt"] )
      input->select("Events/FsrPhoton_pt", 	FsrPhoton_pt);
    if ( choose["Events/FsrPhoton_relIso03"] )
      input->select("Events/FsrPhoton_relIso03", 	FsrPhoton_relIso03);
    if ( choose["Events/GenMET_phi"] )
      input->select("Events/GenMET_phi", 	GenMET_phi);
    if ( choose["Events/GenMET_pt"] )
      input->select("Events/GenMET_pt", 	GenMET_pt);
    if ( choose["Events/GenPart_eta"] )
      input->select("Events/GenPart_eta", 	GenPart_eta);
    if ( choose["Events/GenPart_genPartIdxMother"] )
      input->select("Events/GenPart_genPartIdxMother",
                     GenPart_genPartIdxMother);
    if ( choose["Events/GenPart_mass"] )
      input->select("Events/GenPart_mass", 	GenPart_mass);
    if ( choose["Events/GenPart_pdgId"] )
      input->select("Events/GenPart_pdgId", 	GenPart_pdgId);
    if ( choose["Events/GenPart_phi"] )
      input->select("Events/GenPart_phi", 	GenPart_phi);
    if ( choose["Events/GenPart_pt"] )
      input->select("Events/GenPart_pt", 	GenPart_pt);
    if ( choose["Events/GenPart_status"] )
      input->select("Events/GenPart_status", 	GenPart_status);
    if ( choose["Events/GenPart_statusFlags"] )
      input->select("Events/GenPart_statusFlags", 	GenPart_statusFlags);
    if ( choose["Events/Generator_binvar"] )
      input->select("Events/Generator_binvar", 	Generator_binvar);
    if ( choose["Events/Generator_id1"] )
      input->select("Events/Generator_id1", 	Generator_id1);
    if ( choose["Events/Generator_id2"] )
      input->select("Events/Generator_id2", 	Generator_id2);
    if ( choose["Events/Generator_scalePDF"] )
      input->select("Events/Generator_scalePDF", 	Generator_scalePDF);
    if ( choose["Events/Generator_weight"] )
      input->select("Events/Generator_weight", 	Generator_weight);
    if ( choose["Events/Generator_x1"] )
      input->select("Events/Generator_x1", 	Generator_x1);
    if ( choose["Events/Generator_x2"] )
      input->select("Events/Generator_x2", 	Generator_x2);
    if ( choose["Events/Generator_xpdf1"] )
      input->select("Events/Generator_xpdf1", 	Generator_xpdf1);
    if ( choose["Events/Generator_xpdf2"] )
      input->select("Events/Generator_xpdf2", 	Generator_xpdf2);
    if ( choose["Events/HLT_AK4PFJet100"] )
      input->select("Events/HLT_AK4PFJet100", 	HLT_AK4PFJet100);
    if ( choose["Events/HLT_AK4PFJet120"] )
      input->select("Events/HLT_AK4PFJet120",   HLT_AK4PFJet120);
    if ( choose["Events/HLT_AK4PFJet30"] )
      input->select("Events/HLT_AK4PFJet30", 	HLT_AK4PFJet30);
    if ( choose["Events/HLT_AK4PFJet50"] )
      input->select("Events/HLT_AK4PFJet50", 	HLT_AK4PFJet50);
    if ( choose["Events/HLT_AK4PFJet80"] )
      input->select("Events/HLT_AK4PFJet80", 	HLT_AK4PFJet80);
    if ( choose["Events/HLT_AK8PFHT650_TrimR0p1PT0p03Mass50"] )
      input->select("Events/HLT_AK8PFHT650_TrimR0p1PT0p03Mass50",
                     HLT_AK8PFHT650_TrimR0p1PT0p03Mass50);
    if ( choose["Events/HLT_AK8PFHT700_TrimR0p1PT0p03Mass50"] )
      input->select("Events/HLT_AK8PFHT700_TrimR0p1PT0p03Mass50",
                     HLT_AK8PFHT700_TrimR0p1PT0p03Mass50);
    if ( choose["Events/HLT_AK8PFHT750_TrimMass50"] )
      input->select("Events/HLT_AK8PFHT750_TrimMass50",
                     HLT_AK8PFHT750_TrimMass50);
    if ( choose["Events/HLT_AK8PFHT800_TrimMass50"] )
      input->select("Events/HLT_AK8PFHT800_TrimMass50",
                     HLT_AK8PFHT800_TrimMass50);
    if ( choose["Events/HLT_AK8PFHT850_TrimMass50"] )
      input->select("Events/HLT_AK8PFHT850_TrimMass50",
                     HLT_AK8PFHT850_TrimMass50);
    if ( choose["Events/HLT_AK8PFHT900_TrimMass50"] )
      input->select("Events/HLT_AK8PFHT900_TrimMass50",
                     HLT_AK8PFHT900_TrimMass50);
    if ( choose["Events/HLT_AK8PFJet140"] )
      input->select("Events/HLT_AK8PFJet140", 	HLT_AK8PFJet140);
    if ( choose["Events/HLT_AK8PFJet200"] )
      input->select("Events/HLT_AK8PFJet200", 	HLT_AK8PFJet200);
    if ( choose["Events/HLT_AK8PFJet260"] )
      input->select("Events/HLT_AK8PFJet260", 	HLT_AK8PFJet260);
    if ( choose["Events/HLT_AK8PFJet320"] )
      input->select("Events/HLT_AK8PFJet320", 	HLT_AK8PFJet320);
    if ( choose["Events/HLT_AK8PFJet360_TrimMass30"] )
      input->select("Events/HLT_AK8PFJet360_TrimMass30",
                     HLT_AK8PFJet360_TrimMass30);
    if ( choose["Events/HLT_AK8PFJet40"] )
      input->select("Events/HLT_AK8PFJet40", 	HLT_AK8PFJet40);
    if ( choose["Events/HLT_AK8PFJet400"] )
      input->select("Events/HLT_AK8PFJet400", 	HLT_AK8PFJet400);
    if ( choose["Events/HLT_AK8PFJet400_TrimMass30"] )
      input->select("Events/HLT_AK8PFJet400_TrimMass30",
                     HLT_AK8PFJet400_TrimMass30);
    if ( choose["Events/HLT_AK8PFJet450"] )
      input->select("Events/HLT_AK8PFJet450", 	HLT_AK8PFJet450);
    if ( choose["Events/HLT_AK8PFJet500"] )
      input->select("Events/HLT_AK8PFJet500", 	HLT_AK8PFJet500);
    if ( choose["Events/HLT_AK8PFJet60"] )
      input->select("Events/HLT_AK8PFJet60", 	HLT_AK8PFJet60);
    if ( choose["Events/HLT_AK8PFJet80"] )
      input->select("Events/HLT_AK8PFJet80", 	HLT_AK8PFJet80);
    if ( choose["Events/HLT_Ele115_CaloIdVT_GsfTrkIdT"] )
      input->select("Events/HLT_Ele115_CaloIdVT_GsfTrkIdT",
                     HLT_Ele115_CaloIdVT_GsfTrkIdT);
    if ( choose["Events/HLT_Ele15_IsoVVVL_PFHT450"] )
      input->select("Events/HLT_Ele15_IsoVVVL_PFHT450",
                     HLT_Ele15_IsoVVVL_PFHT450);
    if ( choose["Events/HLT_Ele23_WPLoose_Gsf"] )
      input->select("Events/HLT_Ele23_WPLoose_Gsf", 	HLT_Ele23_WPLoose_Gsf);
    if ( choose["Events/HLT_Ele25_WPTight_Gsf"] )
      input->select("Events/HLT_Ele25_WPTight_Gsf", 	HLT_Ele25_WPTight_Gsf);
    if ( choose["Events/HLT_Ele27_WPLoose_Gsf"] )
      input->select("Events/HLT_Ele27_WPLoose_Gsf", 	HLT_Ele27_WPLoose_Gsf);
    if ( choose["Events/HLT_Ele27_WPTight_Gsf"] )
      input->select("Events/HLT_Ele27_WPTight_Gsf", 	HLT_Ele27_WPTight_Gsf);
    if ( choose["Events/HLT_Ele28_WPTight_Gsf"] )
      input->select("Events/HLT_Ele28_WPTight_Gsf",   HLT_Ele28_WPTight_Gsf);
    if ( choose["Events/HLT_Ele30_WPTight_Gsf"] )
      input->select("Events/HLT_Ele30_WPTight_Gsf", 	HLT_Ele30_WPTight_Gsf);
    if ( choose["Events/HLT_Ele32_WPTight_Gsf"] )
      input->select("Events/HLT_Ele32_WPTight_Gsf", 	HLT_Ele32_WPTight_Gsf);
    if ( choose["Events/HLT_Ele35_WPLoose_Gsf"] )
      input->select("Events/HLT_Ele35_WPLoose_Gsf", 	HLT_Ele35_WPLoose_Gsf);
    if ( choose["Events/HLT_Ele35_WPTight_Gsf"] )
      input->select("Events/HLT_Ele35_WPTight_Gsf",   HLT_Ele35_WPTight_Gsf);
    if ( choose["Events/HLT_Ele38_WPTight_Gsf"] )
      input->select("Events/HLT_Ele38_WPTight_Gsf",   HLT_Ele38_WPTight_Gsf);
    if ( choose["Events/HLT_Ele40_WPTight_Gsf"] ) 
      input->select("Events/HLT_Ele40_WPTight_Gsf",   HLT_Ele40_WPTight_Gsf);
    if ( choose["Events/HLT_Ele45_WPLoose_Gsf"] )
      input->select("Events/HLT_Ele45_WPLoose_Gsf", 	HLT_Ele45_WPLoose_Gsf);
    if ( choose["Events/HLT_HT200"] )
      input->select("Events/HLT_HT200", 	HLT_HT200);
    if ( choose["Events/HLT_HT2000"] )
      input->select("Events/HLT_HT2000", 	HLT_HT2000);
    if ( choose["Events/HLT_HT2500"] )
      input->select("Events/HLT_HT2500", 	HLT_HT2500);
    if ( choose["Events/HLT_HT275"] )
      input->select("Events/HLT_HT275", 	HLT_HT275);
    if ( choose["Events/HLT_HT325"] )
      input->select("Events/HLT_HT325", 	HLT_HT325);
    if ( choose["Events/HLT_HT410to430"] )
      input->select("Events/HLT_HT410to430", 	HLT_HT410to430);
    if ( choose["Events/HLT_HT425"] )
      input->select("Events/HLT_HT425", 	HLT_HT425);
    if ( choose["Events/HLT_HT430to450"] )
      input->select("Events/HLT_HT430to450", 	HLT_HT430to450);
    if ( choose["Events/HLT_HT450to470"] )
      input->select("Events/HLT_HT450to470", 	HLT_HT450to470);
    if ( choose["Events/HLT_HT470to500"] )
      input->select("Events/HLT_HT470to500", 	HLT_HT470to500);
    if ( choose["Events/HLT_HT500to550"] )
      input->select("Events/HLT_HT500to550", 	HLT_HT500to550);
    if ( choose["Events/HLT_HT550to650"] )
      input->select("Events/HLT_HT550to650", 	HLT_HT550to650);
    if ( choose["Events/HLT_HT575"] )
      input->select("Events/HLT_HT575", 	HLT_HT575);
    if ( choose["Events/HLT_HT650"] )
      input->select("Events/HLT_HT650", 	HLT_HT650);
    if ( choose["Events/HLT_IsoMu20"] )
      input->select("Events/HLT_IsoMu20", 	HLT_IsoMu20);
    if ( choose["Events/HLT_IsoMu22"] )
      input->select("Events/HLT_IsoMu22", 	HLT_IsoMu22);
    if ( choose["Events/HLT_IsoMu24"] )
      input->select("Events/HLT_IsoMu24", 	HLT_IsoMu24);
    if ( choose["Events/HLT_IsoMu27"] )
      input->select("Events/HLT_IsoMu27", 	HLT_IsoMu27);
    if ( choose["Events/HLT_IsoMu30"] )
      input->select("Events/HLT_IsoMu30",   HLT_IsoMu30);
    if ( choose["Events/HLT_IsoTkMu20"] )
      input->select("Events/HLT_IsoTkMu20", 	HLT_IsoTkMu20);
    if ( choose["Events/HLT_IsoTkMu22"] )
      input->select("Events/HLT_IsoTkMu22", 	HLT_IsoTkMu22);
    if ( choose["Events/HLT_IsoTkMu24"] )
      input->select("Events/HLT_IsoTkMu24", 	HLT_IsoTkMu24);
    if ( choose["Events/HLT_IsoTkMu27"] )
      input->select("Events/HLT_IsoTkMu27", 	HLT_IsoTkMu27);
    if ( choose["Events/HLT_MET100"] )
      input->select("Events/HLT_MET100", 	HLT_MET100);
    if ( choose["Events/HLT_MET150"] )
      input->select("Events/HLT_MET150", 	HLT_MET150);
    if ( choose["Events/HLT_MET200"] )
      input->select("Events/HLT_MET200", 	HLT_MET200);
    if ( choose["Events/HLT_MET250"] )
      input->select("Events/HLT_MET250", 	HLT_MET250);
    if ( choose["Events/HLT_MET300"] )
      input->select("Events/HLT_MET300", 	HLT_MET300);
    if ( choose["Events/HLT_MET600"] )
      input->select("Events/HLT_MET600", 	HLT_MET600);
    if ( choose["Events/HLT_MET60_IsoTrk35_Loose"] )
      input->select("Events/HLT_MET60_IsoTrk35_Loose",
                     HLT_MET60_IsoTrk35_Loose);
    if ( choose["Events/HLT_MET700"] )
      input->select("Events/HLT_MET700", 	HLT_MET700);
    if ( choose["Events/HLT_MET75_IsoTrk50"] )
      input->select("Events/HLT_MET75_IsoTrk50", 	HLT_MET75_IsoTrk50);
    if ( choose["Events/HLT_MET90_IsoTrk50"] )
      input->select("Events/HLT_MET90_IsoTrk50", 	HLT_MET90_IsoTrk50);
    if ( choose["Events/HLT_Mu15_IsoVVVL_PFHT450"] )
      input->select("Events/HLT_Mu15_IsoVVVL_PFHT450",
                     HLT_Mu15_IsoVVVL_PFHT450);
    if ( choose["Events/HLT_Mu20"] )
      input->select("Events/HLT_Mu20", 	HLT_Mu20);
    if ( choose["Events/HLT_Mu27"] )
      input->select("Events/HLT_Mu27", 	HLT_Mu27);
    if ( choose["Events/HLT_Mu300"] )
      input->select("Events/HLT_Mu300", 	HLT_Mu300);
    if ( choose["Events/HLT_Mu350"] )
      input->select("Events/HLT_Mu350", 	HLT_Mu350);
    if ( choose["Events/HLT_Mu50"] )
      input->select("Events/HLT_Mu50", 	HLT_Mu50);
    if ( choose["Events/HLT_Mu55"] )
      input->select("Events/HLT_Mu55", 	HLT_Mu55);
    if ( choose["Events/HLT_PFHT1050"] )
      input->select("Events/HLT_PFHT1050",  HLT_PFHT1050);
    if ( choose["Events/HLT_PFHT125"] )
      input->select("Events/HLT_PFHT125", 	HLT_PFHT125);
    if ( choose["Events/HLT_PFHT180"] )
      input->select("Events/HLT_PFHT180", 	HLT_PFHT180);
    if ( choose["Events/HLT_PFHT370"] )
      input->select("Events/HLT_PFHT370", 	HLT_PFHT370);
    if ( choose["Events/HLT_PFHT430"] )
      input->select("Events/HLT_PFHT430", 	HLT_PFHT430);
    if ( choose["Events/HLT_PFHT510"] )
      input->select("Events/HLT_PFHT510", 	HLT_PFHT510);
    if ( choose["Events/HLT_PFHT590"] )
      input->select("Events/HLT_PFHT590", 	HLT_PFHT590);
    if ( choose["Events/HLT_PFHT200"] )
      input->select("Events/HLT_PFHT200", 	HLT_PFHT200);
    if ( choose["Events/HLT_PFHT250"] )
      input->select("Events/HLT_PFHT250", 	HLT_PFHT250);
    if ( choose["Events/HLT_PFHT300"] )
      input->select("Events/HLT_PFHT300", 	HLT_PFHT300);
    if ( choose["Events/HLT_PFHT300_PFMET100"] )
      input->select("Events/HLT_PFHT300_PFMET100", 	HLT_PFHT300_PFMET100);
    if ( choose["Events/HLT_PFHT300_PFMET110"] )
      input->select("Events/HLT_PFHT300_PFMET110", 	HLT_PFHT300_PFMET110);
    if ( choose["Events/HLT_PFHT350"] )
      input->select("Events/HLT_PFHT350", 	HLT_PFHT350);
    if ( choose["Events/HLT_PFHT400"] )
      input->select("Events/HLT_PFHT400", 	HLT_PFHT400);
    if ( choose["Events/HLT_PFHT475"] )
      input->select("Events/HLT_PFHT475", 	HLT_PFHT475);
    if ( choose["Events/HLT_PFHT500_PFMET100_PFMHT100_IDTight"] )
      input->select("Events/HLT_PFHT500_PFMET100_PFMHT100_IDTight",
                     HLT_PFHT500_PFMET100_PFMHT100_IDTight);
    if ( choose["Events/HLT_PFHT500_PFMET110_PFMHT110_IDTight"] )
      input->select("Events/HLT_PFHT500_PFMET110_PFMHT110_IDTight",
                     HLT_PFHT500_PFMET110_PFMHT110_IDTight);
    if ( choose["Events/HLT_PFHT600"] )
      input->select("Events/HLT_PFHT600", 	HLT_PFHT600);
    if ( choose["Events/HLT_PFHT650"] )
      input->select("Events/HLT_PFHT650", 	HLT_PFHT650);
    if ( choose["Events/HLT_PFHT680"] )
      input->select("Events/HLT_PFHT680",   HLT_PFHT680);
    if ( choose["Events/HLT_PFHT700_PFMET85_PFMHT85_IDTight"] )
      input->select("Events/HLT_PFHT700_PFMET85_PFMHT85_IDTight",
                     HLT_PFHT700_PFMET85_PFMHT85_IDTight);
    if ( choose["Events/HLT_PFHT700_PFMET95_PFMHT95_IDTight"] )
      input->select("Events/HLT_PFHT700_PFMET95_PFMHT95_IDTight",
                     HLT_PFHT700_PFMET95_PFMHT95_IDTight);
    if ( choose["Events/HLT_PFHT780"] )
      input->select("Events/HLT_PFHT780",   HLT_PFHT780);
    if ( choose["Events/HLT_PFHT800_PFMET75_PFMHT75_IDTight"] )
      input->select("Events/HLT_PFHT800_PFMET75_PFMHT75_IDTight",
                     HLT_PFHT800_PFMET75_PFMHT75_IDTight);
    if ( choose["Events/HLT_PFHT800_PFMET85_PFMHT85_IDTight"] )
      input->select("Events/HLT_PFHT800_PFMET85_PFMHT85_IDTight",
                     HLT_PFHT800_PFMET85_PFMHT85_IDTight);
    if ( choose["Events/HLT_PFHT890"] )
      input->select("Events/HLT_PFHT890",   HLT_PFHT890);
    if ( choose["Events/HLT_PFHT800"] )
      input->select("Events/HLT_PFHT800", 	HLT_PFHT800);
    if ( choose["Events/HLT_PFHT900"] )
      input->select("Events/HLT_PFHT900", 	HLT_PFHT900);
    if ( choose["Events/HLT_PFJet140"] )
      input->select("Events/HLT_PFJet140", 	HLT_PFJet140);
    if ( choose["Events/HLT_PFJet200"] )
      input->select("Events/HLT_PFJet200", 	HLT_PFJet200);
    if ( choose["Events/HLT_PFJet260"] )
      input->select("Events/HLT_PFJet260", 	HLT_PFJet260);
    if ( choose["Events/HLT_PFJet320"] )
      input->select("Events/HLT_PFJet320", 	HLT_PFJet320);
    if ( choose["Events/HLT_PFJet40"] )
      input->select("Events/HLT_PFJet40", 	HLT_PFJet40);
    if ( choose["Events/HLT_PFJet400"] )
      input->select("Events/HLT_PFJet400", 	HLT_PFJet400);
    if ( choose["Events/HLT_PFJet450"] )
      input->select("Events/HLT_PFJet450", 	HLT_PFJet450);
    if ( choose["Events/HLT_PFJet500"] )
      input->select("Events/HLT_PFJet500", 	HLT_PFJet500);
    if ( choose["Events/HLT_PFJet60"] )
      input->select("Events/HLT_PFJet60", 	HLT_PFJet60);
    if ( choose["Events/HLT_PFJet80"] )
      input->select("Events/HLT_PFJet80", 	HLT_PFJet80);
    if ( choose["Events/HLT_PFMET100_PFMHT100_IDTight"] )
      input->select("Events/HLT_PFMET100_PFMHT100_IDTight",
                     HLT_PFMET100_PFMHT100_IDTight);
    if ( choose["Events/HLT_PFMET110_PFMHT110_IDTight"] )
      input->select("Events/HLT_PFMET110_PFMHT110_IDTight",
                     HLT_PFMET110_PFMHT110_IDTight);
    if ( choose["Events/HLT_PFMET120_PFMHT120_IDTight"] )
      input->select("Events/HLT_PFMET120_PFMHT120_IDTight",
                     HLT_PFMET120_PFMHT120_IDTight);
    if ( choose["Events/HLT_PFMET170_HBHECleaned"] )
      input->select("Events/HLT_PFMET170_HBHECleaned",
                     HLT_PFMET170_HBHECleaned);
    if ( choose["Events/HLT_PFMET170_JetIdCleaned"] )
      input->select("Events/HLT_PFMET170_JetIdCleaned",
                     HLT_PFMET170_JetIdCleaned);
    if ( choose["Events/HLT_PFMET170_NoiseCleaned"] )
      input->select("Events/HLT_PFMET170_NoiseCleaned",
                     HLT_PFMET170_NoiseCleaned);
    if ( choose["Events/HLT_PFMET170_NotCleaned"] )
      input->select("Events/HLT_PFMET170_NotCleaned",
                     HLT_PFMET170_NotCleaned);
    if ( choose["Events/HLT_PFMET300"] )
      input->select("Events/HLT_PFMET300", 	HLT_PFMET300);
    if ( choose["Events/HLT_PFMET400"] )
      input->select("Events/HLT_PFMET400", 	HLT_PFMET400);
    if ( choose["Events/HLT_PFMET500"] )
      input->select("Events/HLT_PFMET500", 	HLT_PFMET500);
    if ( choose["Events/HLT_PFMET600"] )
      input->select("Events/HLT_PFMET600", 	HLT_PFMET600);
    if ( choose["Events/HLT_PFMET90_PFMHT90_IDTight"] )
      input->select("Events/HLT_PFMET90_PFMHT90_IDTight",
                     HLT_PFMET90_PFMHT90_IDTight);
    if ( choose["Events/HLT_PFMETNoMu90_PFMHTNoMu90_IDTight"] )
      input->select("Events/HLT_PFMETNoMu90_PFMHTNoMu90_IDTight",
                     HLT_PFMETNoMu90_PFMHTNoMu90_IDTight);
    if ( choose["Events/HLT_PFMETNoMu100_PFMHTNoMu100_IDTight"] )
      input->select("Events/HLT_PFMETNoMu100_PFMHTNoMu100_IDTight",
                     HLT_PFMETNoMu100_PFMHTNoMu100_IDTight);
    if ( choose["Events/HLT_PFMETNoMu110_PFMHTNoMu110_IDTight"] )
      input->select("Events/HLT_PFMETNoMu110_PFMHTNoMu110_IDTight",
                     HLT_PFMETNoMu110_PFMHTNoMu110_IDTight);
    if ( choose["Events/HLT_PFMETNoMu120_PFMHTNoMu120_IDTight"] )
      input->select("Events/HLT_PFMETNoMu120_PFMHTNoMu120_IDTight",
                     HLT_PFMETNoMu120_PFMHTNoMu120_IDTight);
    if ( choose["Events/HLT_PFMETNoMu130_PFMHTNoMu130_IDTight"] )
      input->select("Events/HLT_PFMETNoMu130_PFMHTNoMu130_IDTight",
                     HLT_PFMETNoMu130_PFMHTNoMu130_IDTight);
    if ( choose["Events/HLT_PFMETNoMu140_PFMHTNoMu140_IDTight"] )
      input->select("Events/HLT_PFMETNoMu140_PFMHTNoMu140_IDTight",
                     HLT_PFMETNoMu140_PFMHTNoMu140_IDTight);
    if ( choose["Events/HLT_PFMETTypeOne120_PFMHT120_IDTight"] )                                                                                                                                            
      input->select("Events/HLT_PFMETTypeOne120_PFMHT120_IDTight",
                     HLT_PFMETTypeOne120_PFMHT120_IDTight);
    if ( choose["Events/HLT_Photon100EBHE10"] )
      input->select("Events/HLT_Photon100EBHE10",   HLT_Photon100EBHE10);
    if ( choose["Events/HLT_Photon100EB_TightID_TightIso"] )
      input->select("Events/HLT_Photon100EB_TightID_TightIso",
                     HLT_Photon100EB_TightID_TightIso); 
    if ( choose["Events/HLT_Photon100EEHE10"] )
      input->select("Events/HLT_Photon100EEHE10",   HLT_Photon100EEHE10);
    if ( choose["Events/HLT_Photon100EE_TightID_TightIso"] )
      input->select("Events/HLT_Photon100EE_TightID_TightIso",
                     HLT_Photon100EE_TightID_TightIso);
    if ( choose["Events/HLT_Photon110EB_TightID_TightIso"] )
      input->select("Events/HLT_Photon110EB_TightID_TightIso",
                     HLT_Photon110EB_TightID_TightIso);
    if ( choose["Events/HLT_Photon120"] )
      input->select("Events/HLT_Photon120", 	HLT_Photon120);
    if ( choose["Events/HLT_Photon125"] )
      input->select("Events/HLT_Photon125", 	HLT_Photon125);
    if ( choose["Events/HLT_Photon135_PFMET100"] )
      input->select("Events/HLT_Photon135_PFMET100",
                     HLT_Photon135_PFMET100);
    if ( choose["Events/HLT_Photon150"] )
      input->select("Events/HLT_Photon150", 	HLT_Photon150);
    if ( choose["Events/HLT_Photon165_HE10"] )
      input->select("Events/HLT_Photon165_HE10", 	HLT_Photon165_HE10);
    if ( choose["Events/HLT_Photon175"] )
      input->select("Events/HLT_Photon175", 	HLT_Photon175);
    if ( choose["Events/HLT_Photon20"] )
      input->select("Events/HLT_Photon20",  HLT_Photon20);
    if ( choose["Events/HLT_Photon200"] ) 
      input->select("Events/HLT_Photon200",   HLT_Photon200);
    if ( choose["Events/HLT_Photon22"] )
      input->select("Events/HLT_Photon22", 	HLT_Photon22);
    if ( choose["Events/HLT_Photon25"] )
      input->select("Events/HLT_Photon25", 	HLT_Photon25);
    if ( choose["Events/HLT_Photon250_NoHE"] )
      input->select("Events/HLT_Photon250_NoHE", 	HLT_Photon250_NoHE);
    if ( choose["Events/HLT_Photon30"] )
      input->select("Events/HLT_Photon30", 	HLT_Photon30);
    if ( choose["Events/HLT_Photon300_NoHE"] )
      input->select("Events/HLT_Photon300_NoHE", 	HLT_Photon300_NoHE);
    if ( choose["Events/HLT_Photon33"] )
      input->select("Events/HLT_Photon33",  HLT_Photon33);
    if ( choose["Events/HLT_Photon36"] )
      input->select("Events/HLT_Photon36", 	HLT_Photon36);
    if ( choose["Events/HLT_Photon50"] )
      input->select("Events/HLT_Photon50", 	HLT_Photon50);
    if ( choose["Events/HLT_Photon500"] )
      input->select("Events/HLT_Photon500", 	HLT_Photon500);
    if ( choose["Events/HLT_Photon600"] )
      input->select("Events/HLT_Photon600", 	HLT_Photon600);
    if ( choose["Events/HLT_Photon75"] )
      input->select("Events/HLT_Photon75", 	HLT_Photon75);
    if ( choose["Events/HLT_Photon90"] )
      input->select("Events/HLT_Photon90", 	HLT_Photon90);
    if ( choose["Events/HLT_Rsq0p25"] )
      input->select("Events/HLT_Rsq0p25", 	HLT_Rsq0p25);
    if ( choose["Events/HLT_Rsq0p30"] )
      input->select("Events/HLT_Rsq0p30", 	HLT_Rsq0p30);
    if ( choose["Events/HLT_Rsq0p35"] )
      input->select("Events/HLT_Rsq0p35",   HLT_Rsq0p35);
    if ( choose["Events/HLT_Rsq0p40"] )
      input->select("Events/HLT_Rsq0p40",   HLT_Rsq0p40);
    if ( choose["Events/HLT_RsqMR300_Rsq0p09_MR200"] )  
      input->select("Events/HLT_RsqMR300_Rsq0p09_MR200",
                     HLT_RsqMR300_Rsq0p09_MR200);
    if ( choose["Events/HLT_RsqMR320_Rsq0p09_MR200"] )
      input->select("Events/HLT_RsqMR320_Rsq0p09_MR200",
                     HLT_RsqMR320_Rsq0p09_MR200);
    if ( choose["Events/HLT_RsqMR240_Rsq0p09_MR200"] )
      input->select("Events/HLT_RsqMR240_Rsq0p09_MR200",
                     HLT_RsqMR240_Rsq0p09_MR200);
    if ( choose["Events/HLT_RsqMR270_Rsq0p09_MR200"] )
      input->select("Events/HLT_RsqMR270_Rsq0p09_MR200",
                     HLT_RsqMR270_Rsq0p09_MR200);
    if ( choose["Events/HLT_TkMu20"] )
      input->select("Events/HLT_TkMu20", 	HLT_TkMu20);
    if ( choose["Events/HLT_TkMu27"] )
      input->select("Events/HLT_TkMu27", 	HLT_TkMu27);
    if ( choose["Events/HLT_TkMu50"] )
      input->select("Events/HLT_TkMu50", 	HLT_TkMu50);
    if ( choose["Events/HLTriggerFinalPath"] )
      input->select("Events/HLTriggerFinalPath", 	HLTriggerFinalPath);
    if ( choose["Events/HLTriggerFirstPath"] )
      input->select("Events/HLTriggerFirstPath", 	HLTriggerFirstPath);
    if ( choose["Events/IsoTrack_dxy"] )
      input->select("Events/IsoTrack_dxy", 	IsoTrack_dxy);
    if ( choose["Events/IsoTrack_dz"] )
      input->select("Events/IsoTrack_dz", 	IsoTrack_dz);
    if ( choose["Events/IsoTrack_eta"] )
      input->select("Events/IsoTrack_eta", 	IsoTrack_eta);
    if ( choose["Events/IsoTrack_fromPV"] )
      input->select("Events/IsoTrack_fromPV", 	IsoTrack_fromPV);
    if ( choose["Events/IsoTrack_isFromLostTrack"] )
      input->select("Events/IsoTrack_isFromLostTrack",
                     IsoTrack_isFromLostTrack);
    if ( choose["Events/IsoTrack_isHighPurityTrack"] )
      input->select("Events/IsoTrack_isHighPurityTrack",
                     IsoTrack_isHighPurityTrack);
    if ( choose["Events/IsoTrack_isPFcand"] )
      input->select("Events/IsoTrack_isPFcand", 	IsoTrack_isPFcand);
    if ( choose["Events/IsoTrack_miniPFRelIso_all"] )
      input->select("Events/IsoTrack_miniPFRelIso_all",
                     IsoTrack_miniPFRelIso_all);
    if ( choose["Events/IsoTrack_miniPFRelIso_chg"] )
      input->select("Events/IsoTrack_miniPFRelIso_chg",
                     IsoTrack_miniPFRelIso_chg);
    if ( choose["Events/IsoTrack_pdgId"] )
      input->select("Events/IsoTrack_pdgId", 	IsoTrack_pdgId);
    if ( choose["Events/IsoTrack_pfRelIso03_all"] )
      input->select("Events/IsoTrack_pfRelIso03_all",
                     IsoTrack_pfRelIso03_all);
    if ( choose["Events/IsoTrack_pfRelIso03_chg"] )
      input->select("Events/IsoTrack_pfRelIso03_chg",
                     IsoTrack_pfRelIso03_chg);
    if ( choose["Events/IsoTrack_phi"] )
      input->select("Events/IsoTrack_phi", 	IsoTrack_phi);
    if ( choose["Events/IsoTrack_pt"] )
      input->select("Events/IsoTrack_pt", 	IsoTrack_pt);
    if ( choose["Events/Jet_area"] )
      input->select("Events/Jet_area", 	Jet_area);
    if ( choose["Events/Jet_bRegCorr"] )
      input->select("Events/Jet_bRegCorr", 	Jet_bRegCorr);
    if ( choose["Events/Jet_bRegRes"] )
      input->select("Events/Jet_bRegRes", 	Jet_bRegRes);
    if ( choose["Events/Jet_btagCMVA"] )
      input->select("Events/Jet_btagCMVA", 	Jet_btagCMVA);
    if ( choose["Events/Jet_btagCSVV2"] )
      input->select("Events/Jet_btagCSVV2", 	Jet_btagCSVV2);
    if ( choose["Events/Jet_btagDeepB"] )
      input->select("Events/Jet_btagDeepB", 	Jet_btagDeepB);
    if ( choose["Events/Jet_btagDeepC"] )
      input->select("Events/Jet_btagDeepC", 	Jet_btagDeepC);
    if ( choose["Events/Jet_btagDeepFlavB"] )
      input->select("Events/Jet_btagDeepFlavB", 	Jet_btagDeepFlavB);
    if ( choose["Events/Jet_btagDeepFlavC"] )
      input->select("Events/Jet_btagDeepFlavC", 	Jet_btagDeepFlavC);
    if ( choose["Events/Jet_chEmEF"] )
      input->select("Events/Jet_chEmEF", 	Jet_chEmEF);
    if ( choose["Events/Jet_chHEF"] )
      input->select("Events/Jet_chHEF", 	Jet_chHEF);
    if ( choose["Events/Jet_cleanmask"] )
      input->select("Events/Jet_cleanmask", 	Jet_cleanmask);
    if ( choose["Events/Jet_electronIdx1"] )
      input->select("Events/Jet_electronIdx1", 	Jet_electronIdx1);
    if ( choose["Events/Jet_electronIdx2"] )
      input->select("Events/Jet_electronIdx2", 	Jet_electronIdx2);
    if ( choose["Events/Jet_eta"] )
      input->select("Events/Jet_eta", 	Jet_eta);
    if ( choose["Events/Jet_genJetIdx"] )
      input->select("Events/Jet_genJetIdx", 	Jet_genJetIdx);
    if ( choose["Events/Jet_hadronFlavour"] )
      input->select("Events/Jet_hadronFlavour", 	Jet_hadronFlavour);
    if ( choose["Events/Jet_jercCHF"] )
      input->select("Events/Jet_jercCHF", 	Jet_jercCHF);
    if ( choose["Events/Jet_jercCHPUF"] )
      input->select("Events/Jet_jercCHPUF", 	Jet_jercCHPUF);
    if ( choose["Events/Jet_jetId"] )
      input->select("Events/Jet_jetId", 	Jet_jetId);
    if ( choose["Events/Jet_mass"] )
      input->select("Events/Jet_mass", 	Jet_mass);
    if ( choose["Events/Jet_muEF"] )
      input->select("Events/Jet_muEF", 	Jet_muEF);
    if ( choose["Events/Jet_muonIdx1"] )
      input->select("Events/Jet_muonIdx1", 	Jet_muonIdx1);
    if ( choose["Events/Jet_muonIdx2"] )
      input->select("Events/Jet_muonIdx2", 	Jet_muonIdx2);
    if ( choose["Events/Jet_muonSubtrFactor"] )
      input->select("Events/Jet_muonSubtrFactor", 	Jet_muonSubtrFactor);
    if ( choose["Events/Jet_nConstituents"] )
      input->select("Events/Jet_nConstituents", 	Jet_nConstituents);
    if ( choose["Events/Jet_nElectrons"] )
      input->select("Events/Jet_nElectrons", 	Jet_nElectrons);
    if ( choose["Events/Jet_nMuons"] )
      input->select("Events/Jet_nMuons", 	Jet_nMuons);
    if ( choose["Events/Jet_neEmEF"] )
      input->select("Events/Jet_neEmEF", 	Jet_neEmEF);
    if ( choose["Events/Jet_neHEF"] )
      input->select("Events/Jet_neHEF", 	Jet_neHEF);
    if ( choose["Events/Jet_partonFlavour"] )
      input->select("Events/Jet_partonFlavour", 	Jet_partonFlavour);
    if ( choose["Events/Jet_phi"] )
      input->select("Events/Jet_phi", 	Jet_phi);
    if ( choose["Events/Jet_pt"] )
      input->select("Events/Jet_pt", 	Jet_pt);
    if ( choose["Events/Jet_puId"] )
      input->select("Events/Jet_puId", 	Jet_puId);
    if ( choose["Events/Jet_qgl"] )
      input->select("Events/Jet_qgl", 	Jet_qgl);
    if ( choose["Events/Jet_rawFactor"] )
      input->select("Events/Jet_rawFactor", 	Jet_rawFactor);
    if ( choose["Events/LHEPart_eta"] )
      input->select("Events/LHEPart_eta", 	LHEPart_eta);
    if ( choose["Events/LHEPart_mass"] )
      input->select("Events/LHEPart_mass", 	LHEPart_mass);
    if ( choose["Events/LHEPart_pdgId"] )
      input->select("Events/LHEPart_pdgId", 	LHEPart_pdgId);
    if ( choose["Events/LHEPart_phi"] )
      input->select("Events/LHEPart_phi", 	LHEPart_phi);
    if ( choose["Events/LHEPart_pt"] )
      input->select("Events/LHEPart_pt", 	LHEPart_pt);
    if ( choose["Events/LHEPdfWeight"] )
      input->select("Events/LHEPdfWeight", 	LHEPdfWeight);
    if ( choose["Events/LHEReweightingWeight"] )
      input->select("Events/LHEReweightingWeight", 	LHEReweightingWeight);
    if ( choose["Events/LHEScaleWeight"] )
      input->select("Events/LHEScaleWeight", 	LHEScaleWeight);
    if ( choose["Events/LHEWeight_originalXWGTUP"] )
      input->select("Events/LHEWeight_originalXWGTUP",
                     LHEWeight_originalXWGTUP);
    if ( choose["Events/LHE_HT"] )
      input->select("Events/LHE_HT", 	LHE_HT);
    if ( choose["Events/LHE_HTIncoming"] )
      input->select("Events/LHE_HTIncoming", 	LHE_HTIncoming);
    if ( choose["Events/LHE_Nb"] )
      input->select("Events/LHE_Nb", 	LHE_Nb);
    if ( choose["Events/LHE_Nc"] )
      input->select("Events/LHE_Nc", 	LHE_Nc);
    if ( choose["Events/LHE_Nglu"] )
      input->select("Events/LHE_Nglu", 	LHE_Nglu);
    if ( choose["Events/LHE_Njets"] )
      input->select("Events/LHE_Njets", 	LHE_Njets);
    if ( choose["Events/LHE_NpLO"] )
      input->select("Events/LHE_NpLO", 	LHE_NpLO);
    if ( choose["Events/LHE_NpNLO"] )
      input->select("Events/LHE_NpNLO", 	LHE_NpNLO);
    if ( choose["Events/LHE_Nuds"] )
      input->select("Events/LHE_Nuds", 	LHE_Nuds);
    if ( choose["Events/LHE_Vpt"] )
      input->select("Events/LHE_Vpt", 	LHE_Vpt);
    if ( choose["Events/METFixEE2017_MetUnclustEnUpDeltaX"] )
      input->select("Events/METFixEE2017_MetUnclustEnUpDeltaX",
                     METFixEE2017_MetUnclustEnUpDeltaX);
    if ( choose["Events/METFixEE2017_MetUnclustEnUpDeltaY"] )
      input->select("Events/METFixEE2017_MetUnclustEnUpDeltaY",
                     METFixEE2017_MetUnclustEnUpDeltaY);
    if ( choose["Events/METFixEE2017_covXX"] )
      input->select("Events/METFixEE2017_covXX",  METFixEE2017_covXX);
    if ( choose["Events/METFixEE2017_covXY"] )
      input->select("Events/METFixEE2017_covXY",  METFixEE2017_covXY);
    if ( choose["Events/METFixEE2017_covYY"] )
      input->select("Events/METFixEE2017_covYY",  METFixEE2017_covYY);
    if ( choose["Events/METFixEE2017_phi"] )
      input->select("Events/METFixEE2017_phi",  METFixEE2017_phi);
    if ( choose["Events/METFixEE2017_pt"] )
      input->select("Events/METFixEE2017_pt",   METFixEE2017_pt);
    if ( choose["Events/METFixEE2017_significance"] )
      input->select("Events/METFixEE2017_significance",
                     METFixEE2017_significance);
    if ( choose["Events/METFixEE2017_sumEt"] )
      input->select("Events/METFixEE2017_sumEt",  METFixEE2017_sumEt);
    if ( choose["Events/MET_MetUnclustEnUpDeltaX"] )
      input->select("Events/MET_MetUnclustEnUpDeltaX",
                     MET_MetUnclustEnUpDeltaX);
    if ( choose["Events/MET_MetUnclustEnUpDeltaY"] )
      input->select("Events/MET_MetUnclustEnUpDeltaY",
                     MET_MetUnclustEnUpDeltaY);
    if ( choose["Events/MET_covXX"] )
      input->select("Events/MET_covXX", 	MET_covXX);
    if ( choose["Events/MET_covXY"] )
      input->select("Events/MET_covXY", 	MET_covXY);
    if ( choose["Events/MET_covYY"] )
      input->select("Events/MET_covYY", 	MET_covYY);
    if ( choose["Events/MET_fiducialGenPhi"] )
      input->select("Events/MET_fiducialGenPhi", 	MET_fiducialGenPhi);
    if ( choose["Events/MET_fiducialGenPt"] )
      input->select("Events/MET_fiducialGenPt", 	MET_fiducialGenPt);
    if ( choose["Events/MET_phi"] )
      input->select("Events/MET_phi", 	MET_phi);
    if ( choose["Events/MET_pt"] )
      input->select("Events/MET_pt", 	MET_pt);
    if ( choose["Events/MET_significance"] )
      input->select("Events/MET_significance", 	MET_significance);
    if ( choose["Events/MET_sumEt"] )
      input->select("Events/MET_sumEt", 	MET_sumEt);
    if ( choose["Events/Muon_charge"] )
      input->select("Events/Muon_charge", 	Muon_charge);
    if ( choose["Events/Muon_cleanmask"] )
      input->select("Events/Muon_cleanmask", 	Muon_cleanmask);
    if ( choose["Events/Muon_dxy"] )
      input->select("Events/Muon_dxy", 	Muon_dxy);
    if ( choose["Events/Muon_dxyErr"] )
      input->select("Events/Muon_dxyErr", 	Muon_dxyErr);
    if ( choose["Events/Muon_dz"] )
      input->select("Events/Muon_dz", 	Muon_dz);
    if ( choose["Events/Muon_dzErr"] )
      input->select("Events/Muon_dzErr", 	Muon_dzErr);
    if ( choose["Events/Muon_eta"] )
      input->select("Events/Muon_eta", 	Muon_eta);
    if ( choose["Events/Muon_fsrPhotonIdx"] )
      input->select("Events/Muon_fsrPhotonIdx", 	Muon_fsrPhotonIdx);
    if ( choose["Events/Muon_genPartFlav"] )
      input->select("Events/Muon_genPartFlav", 	Muon_genPartFlav);
    if ( choose["Events/Muon_genPartIdx"] )
      input->select("Events/Muon_genPartIdx", 	Muon_genPartIdx);
    if ( choose["Events/Muon_highPtId"] )
      input->select("Events/Muon_highPtId", 	Muon_highPtId);
    if ( choose["Events/Muon_inTimeMuon"] )
      input->select("Events/Muon_inTimeMuon", 	Muon_inTimeMuon);
    if ( choose["Events/Muon_ip3d"] )
      input->select("Events/Muon_ip3d", 	Muon_ip3d);
    if ( choose["Events/Muon_isGlobal"] )
      input->select("Events/Muon_isGlobal", 	Muon_isGlobal);
    if ( choose["Events/Muon_isPFcand"] )
      input->select("Events/Muon_isPFcand", 	Muon_isPFcand);
    if ( choose["Events/Muon_isTracker"] )
      input->select("Events/Muon_isTracker", 	Muon_isTracker);
    if ( choose["Events/Muon_jetIdx"] )
      input->select("Events/Muon_jetIdx", 	Muon_jetIdx);
    if ( choose["Events/Muon_jetPtRelv2"] )
      input->select("Events/Muon_jetPtRelv2", 	Muon_jetPtRelv2);
    if ( choose["Events/Muon_jetRelIso"] )
      input->select("Events/Muon_jetRelIso", 	Muon_jetRelIso);
    if ( choose["Events/Muon_looseId"] )
      input->select("Events/Muon_looseId", 	Muon_looseId);
    if ( choose["Events/Muon_mass"] )
      input->select("Events/Muon_mass", 	Muon_mass);
    if ( choose["Events/Muon_mediumId"] )
      input->select("Events/Muon_mediumId", 	Muon_mediumId);
    if ( choose["Events/Muon_mediumPromptId"] )
      input->select("Events/Muon_mediumPromptId", 	Muon_mediumPromptId);
    if ( choose["Events/Muon_miniIsoId"] )
      input->select("Events/Muon_miniIsoId", 	Muon_miniIsoId);
    if ( choose["Events/Muon_miniPFRelIso_all"] )
      input->select("Events/Muon_miniPFRelIso_all", 	Muon_miniPFRelIso_all);
    if ( choose["Events/Muon_miniPFRelIso_chg"] )
      input->select("Events/Muon_miniPFRelIso_chg", 	Muon_miniPFRelIso_chg);
    if ( choose["Events/Muon_multiIsoId"] )
      input->select("Events/Muon_multiIsoId", 	Muon_multiIsoId);
    if ( choose["Events/Muon_mvaId"] )
      input->select("Events/Muon_mvaId", 	Muon_mvaId);
    if ( choose["Events/Muon_mvaLowPt"] )
      input->select("Events/Muon_mvaLowPt", 	Muon_mvaLowPt);
    if ( choose["Events/Muon_mvaTTH"] )
      input->select("Events/Muon_mvaTTH", 	Muon_mvaTTH);
    if ( choose["Events/Muon_nStations"] )
      input->select("Events/Muon_nStations", 	Muon_nStations);
    if ( choose["Events/Muon_nTrackerLayers"] )
      input->select("Events/Muon_nTrackerLayers", 	Muon_nTrackerLayers);
    if ( choose["Events/Muon_pdgId"] )
      input->select("Events/Muon_pdgId", 	Muon_pdgId);
    if ( choose["Events/Muon_pfIsoId"] )
      input->select("Events/Muon_pfIsoId", 	Muon_pfIsoId);
    if ( choose["Events/Muon_pfRelIso03_all"] )
      input->select("Events/Muon_pfRelIso03_all", 	Muon_pfRelIso03_all);
    if ( choose["Events/Muon_pfRelIso03_chg"] )
      input->select("Events/Muon_pfRelIso03_chg", 	Muon_pfRelIso03_chg);
    if ( choose["Events/Muon_pfRelIso04_all"] )
      input->select("Events/Muon_pfRelIso04_all", 	Muon_pfRelIso04_all);
    if ( choose["Events/Muon_phi"] )
      input->select("Events/Muon_phi", 	Muon_phi);
    if ( choose["Events/Muon_pt"] )
      input->select("Events/Muon_pt", 	Muon_pt);
    if ( choose["Events/Muon_ptErr"] )
      input->select("Events/Muon_ptErr", 	Muon_ptErr);
    if ( choose["Events/Muon_segmentComp"] )
      input->select("Events/Muon_segmentComp", 	Muon_segmentComp);
    if ( choose["Events/Muon_sip3d"] )
      input->select("Events/Muon_sip3d", 	Muon_sip3d);
    if ( choose["Events/Muon_softId"] )
      input->select("Events/Muon_softId", 	Muon_softId);
    if ( choose["Muon_softMva"] )
      input->select("Events/Muon_softMva",  Muon_softMva);
    if ( choose["Events/Muon_softMvaId"] )
      input->select("Events/Muon_softMvaId", 	Muon_softMvaId);
    if ( choose["Events/Muon_tightCharge"] )
      input->select("Events/Muon_tightCharge", 	Muon_tightCharge);
    if ( choose["Events/Muon_tightId"] )
      input->select("Events/Muon_tightId", 	Muon_tightId);
    if ( choose["Events/Muon_tkIsoId"] )
      input->select("Events/Muon_tkIsoId", 	Muon_tkIsoId);
    if ( choose["Events/Muon_tkRelIso"] )
      input->select("Events/Muon_tkRelIso", 	Muon_tkRelIso);
    if ( choose["Events/Muon_triggerIdLoose"] )
      input->select("Events/Muon_triggerIdLoose", 	Muon_triggerIdLoose);
    if ( choose["Events/Muon_tunepRelPt"] )
      input->select("Events/Muon_tunepRelPt", 	Muon_tunepRelPt);
    if ( choose["Events/OtherPV_z"] )
      input->select("Events/OtherPV_z", 	OtherPV_z);
    if ( choose["Events/PSWeight"] )
      input->select("Events/PSWeight", 	PSWeight);
    if ( choose["Events/PV_chi2"] )
      input->select("Events/PV_chi2", 	PV_chi2);
    if ( choose["Events/PV_ndof"] )
      input->select("Events/PV_ndof", 	PV_ndof);
    if ( choose["Events/PV_npvs"] )
      input->select("Events/PV_npvs", 	PV_npvs);
    if ( choose["Events/PV_npvsGood"] )
      input->select("Events/PV_npvsGood", 	PV_npvsGood);
    if ( choose["Events/PV_score"] )
      input->select("Events/PV_score", 	PV_score);
    if ( choose["Events/PV_x"] )
      input->select("Events/PV_x", 	PV_x);
    if ( choose["Events/PV_y"] )
      input->select("Events/PV_y", 	PV_y);
    if ( choose["Events/PV_z"] )
      input->select("Events/PV_z", 	PV_z);
    if ( choose["Events/Photon_charge"] )
      input->select("Events/Photon_charge", 	Photon_charge);
    if ( choose["Events/Photon_cleanmask"] )
      input->select("Events/Photon_cleanmask", 	Photon_cleanmask);
    if ( choose["Events/Photon_cutBased"] )
      input->select("Events/Photon_cutBased", 	Photon_cutBased);
    if ( choose["Events/Photon_cutBased17Bitmap"] )
      input->select("Events/Photon_cutBased17Bitmap",
                     Photon_cutBased17Bitmap);
    if ( choose["Events/Photon_eCorr"] )
      input->select("Events/Photon_eCorr", 	Photon_eCorr);
    if ( choose["Events/Photon_electronIdx"] )
      input->select("Events/Photon_electronIdx", 	Photon_electronIdx);
    if ( choose["Events/Photon_electronVeto"] )
      input->select("Events/Photon_electronVeto", 	Photon_electronVeto);
    if ( choose["Events/Photon_energyErr"] )
      input->select("Events/Photon_energyErr", 	Photon_energyErr);
    if ( choose["Events/Photon_eta"] )
      input->select("Events/Photon_eta", 	Photon_eta);
    if ( choose["Events/Photon_genPartFlav"] )
      input->select("Events/Photon_genPartFlav", 	Photon_genPartFlav);
    if ( choose["Events/Photon_genPartIdx"] )
      input->select("Events/Photon_genPartIdx", 	Photon_genPartIdx);
    if ( choose["Events/Photon_hoe"] )
      input->select("Events/Photon_hoe", 	Photon_hoe);
    if ( choose["Events/Photon_isScEtaEB"] )
      input->select("Events/Photon_isScEtaEB", 	Photon_isScEtaEB);
    if ( choose["Events/Photon_isScEtaEE"] )
      input->select("Events/Photon_isScEtaEE", 	Photon_isScEtaEE);
    if ( choose["Events/Photon_jetIdx"] )
      input->select("Events/Photon_jetIdx", 	Photon_jetIdx);
    if ( choose["Events/Photon_mass"] )
      input->select("Events/Photon_mass", 	Photon_mass);
    if ( choose["Events/Photon_mvaID"] )
      input->select("Events/Photon_mvaID", 	Photon_mvaID);
    if ( choose["Events/Photon_mvaID17"] )
      input->select("Events/Photon_mvaID17", 	Photon_mvaID17);
    if ( choose["Events/Photon_mvaID17_WP80"] )
      input->select("Events/Photon_mvaID17_WP80", 	Photon_mvaID17_WP80);
    if ( choose["Events/Photon_mvaID17_WP90"] )
      input->select("Events/Photon_mvaID17_WP90", 	Photon_mvaID17_WP90);
    if ( choose["Events/Photon_mvaID_WP80"] )
      input->select("Events/Photon_mvaID_WP80", 	Photon_mvaID_WP80);
    if ( choose["Events/Photon_mvaID_WP90"] )
      input->select("Events/Photon_mvaID_WP90", 	Photon_mvaID_WP90);
    if ( choose["Events/Photon_pdgId"] )
      input->select("Events/Photon_pdgId", 	Photon_pdgId);
    if ( choose["Events/Photon_pfRelIso03_all"] )
      input->select("Events/Photon_pfRelIso03_all", 	Photon_pfRelIso03_all);
    if ( choose["Events/Photon_pfRelIso03_chg"] )
      input->select("Events/Photon_pfRelIso03_chg", 	Photon_pfRelIso03_chg);
    if ( choose["Events/Photon_phi"] )
      input->select("Events/Photon_phi", 	Photon_phi);
    if ( choose["Events/Photon_pixelSeed"] )
      input->select("Events/Photon_pixelSeed", 	Photon_pixelSeed);
    if ( choose["Events/Photon_pt"] )
      input->select("Events/Photon_pt", 	Photon_pt);
    if ( choose["Events/Photon_r9"] )
      input->select("Events/Photon_r9", 	Photon_r9);
    if ( choose["Events/Photon_seedGain"] )
      input->select("Events/Photon_seedGain", 	Photon_seedGain);
    if ( choose["Events/Photon_sieie"] )
      input->select("Events/Photon_sieie", 	Photon_sieie);
    if ( choose["Events/Photon_vidNestedWPBitmap"] )
      input->select("Events/Photon_vidNestedWPBitmap",
                     Photon_vidNestedWPBitmap);
    if ( choose["Events/Pileup_gpudensity"] )
      input->select("Events/Pileup_gpudensity", 	Pileup_gpudensity);
    if ( choose["Events/Pileup_nPU"] )
      input->select("Events/Pileup_nPU", 	Pileup_nPU);
    if ( choose["Events/Pileup_nTrueInt"] )
      input->select("Events/Pileup_nTrueInt", 	Pileup_nTrueInt);
    if ( choose["Events/Pileup_pudensity"] )
      input->select("Events/Pileup_pudensity", 	Pileup_pudensity);
    if ( choose["Events/Pileup_sumEOOT"] )
      input->select("Events/Pileup_sumEOOT", 	Pileup_sumEOOT);
    if ( choose["Events/Pileup_sumLOOT"] )
      input->select("Events/Pileup_sumLOOT", 	Pileup_sumLOOT);
    if ( choose["Events/PuppiMET_phi"] )
      input->select("Events/PuppiMET_phi", 	PuppiMET_phi);
    if ( choose["Events/PuppiMET_pt"] )
      input->select("Events/PuppiMET_pt", 	PuppiMET_pt);
    if ( choose["Events/PuppiMET_sumEt"] )
      input->select("Events/PuppiMET_sumEt", 	PuppiMET_sumEt);
    if ( choose["Events/RawMET_phi"] )
      input->select("Events/RawMET_phi", 	RawMET_phi);
    if ( choose["Events/RawMET_pt"] )
      input->select("Events/RawMET_pt", 	RawMET_pt);
    if ( choose["Events/RawMET_sumEt"] )
      input->select("Events/RawMET_sumEt", 	RawMET_sumEt);
    if ( choose["Events/SubJet_btagCMVA"] )
      input->select("Events/SubJet_btagCMVA", 	SubJet_btagCMVA);
    if ( choose["Events/SubJet_btagCSVV2"] )
      input->select("Events/SubJet_btagCSVV2", 	SubJet_btagCSVV2);
    if ( choose["Events/SubJet_btagDeepB"] )
      input->select("Events/SubJet_btagDeepB", 	SubJet_btagDeepB);
    if ( choose["Events/SubJet_eta"] )
      input->select("Events/SubJet_eta", 	SubJet_eta);
    if ( choose["Events/SubJet_mass"] )
      input->select("Events/SubJet_mass", 	SubJet_mass);
    if ( choose["Events/SubJet_n2b1"] )
      input->select("Events/SubJet_n2b1", 	SubJet_n2b1);
    if ( choose["Events/SubJet_n3b1"] )
      input->select("Events/SubJet_n3b1", 	SubJet_n3b1);
    if ( choose["Events/SubJet_phi"] )
      input->select("Events/SubJet_phi", 	SubJet_phi);
    if ( choose["Events/SubJet_pt"] )
      input->select("Events/SubJet_pt", 	SubJet_pt);
    if ( choose["Events/SubJet_rawFactor"] )
      input->select("Events/SubJet_rawFactor", 	SubJet_rawFactor);
    if ( choose["Events/SubJet_tau1"] )
      input->select("Events/SubJet_tau1", 	SubJet_tau1);
    if ( choose["Events/SubJet_tau2"] )
      input->select("Events/SubJet_tau2", 	SubJet_tau2);
    if ( choose["Events/SubJet_tau3"] )
      input->select("Events/SubJet_tau3", 	SubJet_tau3);
    if ( choose["Events/SubJet_tau4"] )
      input->select("Events/SubJet_tau4", 	SubJet_tau4);
    if ( choose["Events/Tau_charge"] )
      input->select("Events/Tau_charge", 	Tau_charge);
    if ( choose["Events/Tau_chargedIso"] )
      input->select("Events/Tau_chargedIso", 	Tau_chargedIso);
    if ( choose["Events/Tau_cleanmask"] )
      input->select("Events/Tau_cleanmask", 	Tau_cleanmask);
    if ( choose["Events/Tau_decayMode"] )
      input->select("Events/Tau_decayMode", 	Tau_decayMode);
    if ( choose["Events/Tau_dxy"] )
      input->select("Events/Tau_dxy", 	Tau_dxy);
    if ( choose["Events/Tau_dz"] )
      input->select("Events/Tau_dz", 	Tau_dz);
    if ( choose["Events/Tau_eta"] )
      input->select("Events/Tau_eta", 	Tau_eta);
    if ( choose["Events/Tau_genPartFlav"] )
      input->select("Events/Tau_genPartFlav", 	Tau_genPartFlav);
    if ( choose["Events/Tau_genPartIdx"] )
      input->select("Events/Tau_genPartIdx", 	Tau_genPartIdx);
    if ( choose["Events/Tau_idAntiEle"] )
      input->select("Events/Tau_idAntiEle", 	Tau_idAntiEle);
    if ( choose["Events/Tau_idAntiEle2018"] )
      input->select("Events/Tau_idAntiEle2018", 	Tau_idAntiEle2018);
    if ( choose["Events/Tau_idAntiMu"] )
      input->select("Events/Tau_idAntiMu", 	Tau_idAntiMu);
    if ( choose["Events/Tau_idDecayMode"] )
      input->select("Events/Tau_idDecayMode", 	Tau_idDecayMode);
    if ( choose["Events/Tau_idDecayModeNewDMs"] )
      input->select("Events/Tau_idDecayModeNewDMs", 	Tau_idDecayModeNewDMs);
    if ( choose["Events/Tau_idDeepTau2017v2p1VSe"] )
      input->select("Events/Tau_idDeepTau2017v2p1VSe",
                     Tau_idDeepTau2017v2p1VSe);
    if ( choose["Events/Tau_idDeepTau2017v2p1VSjet"] )
      input->select("Events/Tau_idDeepTau2017v2p1VSjet",
                     Tau_idDeepTau2017v2p1VSjet);
    if ( choose["Events/Tau_idDeepTau2017v2p1VSmu"] )
      input->select("Events/Tau_idDeepTau2017v2p1VSmu",
                     Tau_idDeepTau2017v2p1VSmu);
    if ( choose["Events/Tau_idMVAnewDM2017v2"] )
      input->select("Events/Tau_idMVAnewDM2017v2", 	Tau_idMVAnewDM2017v2);
    if ( choose["Events/Tau_idMVAoldDM"] )
      input->select("Events/Tau_idMVAoldDM", 	Tau_idMVAoldDM);
    if ( choose["Events/Tau_idMVAoldDM2017v1"] )
      input->select("Events/Tau_idMVAoldDM2017v1", 	Tau_idMVAoldDM2017v1);
    if ( choose["Events/Tau_idMVAoldDM2017v2"] )
      input->select("Events/Tau_idMVAoldDM2017v2", 	Tau_idMVAoldDM2017v2);
    if ( choose["Events/Tau_idMVAoldDMdR032017v2"] )
      input->select("Events/Tau_idMVAoldDMdR032017v2",
                     Tau_idMVAoldDMdR032017v2);
    if ( choose["Events/Tau_jetIdx"] )
      input->select("Events/Tau_jetIdx", 	Tau_jetIdx);
    if ( choose["Events/Tau_leadTkDeltaEta"] )
      input->select("Events/Tau_leadTkDeltaEta", 	Tau_leadTkDeltaEta);
    if ( choose["Events/Tau_leadTkDeltaPhi"] )
      input->select("Events/Tau_leadTkDeltaPhi", 	Tau_leadTkDeltaPhi);
    if ( choose["Events/Tau_leadTkPtOverTauPt"] )
      input->select("Events/Tau_leadTkPtOverTauPt", 	Tau_leadTkPtOverTauPt);
    if ( choose["Events/Tau_mass"] )
      input->select("Events/Tau_mass", 	Tau_mass);
    if ( choose["Events/Tau_neutralIso"] )
      input->select("Events/Tau_neutralIso", 	Tau_neutralIso);
    if ( choose["Events/Tau_phi"] )
      input->select("Events/Tau_phi", 	Tau_phi);
    if ( choose["Events/Tau_photonsOutsideSignalCone"] )
      input->select("Events/Tau_photonsOutsideSignalCone",
                     Tau_photonsOutsideSignalCone);
    if ( choose["Events/Tau_pt"] )
      input->select("Events/Tau_pt", 	Tau_pt);
    if ( choose["Events/Tau_puCorr"] )
      input->select("Events/Tau_puCorr", 	Tau_puCorr);
    if ( choose["Events/Tau_rawAntiEle"] )
      input->select("Events/Tau_rawAntiEle", 	Tau_rawAntiEle);
    if ( choose["Events/Tau_rawAntiEle2018"] )
      input->select("Events/Tau_rawAntiEle2018", 	Tau_rawAntiEle2018);
    if ( choose["Events/Tau_rawAntiEleCat"] )
      input->select("Events/Tau_rawAntiEleCat", 	Tau_rawAntiEleCat);
    if ( choose["Events/Tau_rawAntiEleCat2018"] )
      input->select("Events/Tau_rawAntiEleCat2018", 	Tau_rawAntiEleCat2018);
    if ( choose["Events/Tau_rawDeepTau2017v2p1VSe"] )
      input->select("Events/Tau_rawDeepTau2017v2p1VSe",
                     Tau_rawDeepTau2017v2p1VSe);
    if ( choose["Events/Tau_rawDeepTau2017v2p1VSjet"] )
      input->select("Events/Tau_rawDeepTau2017v2p1VSjet",
                     Tau_rawDeepTau2017v2p1VSjet);
    if ( choose["Events/Tau_rawDeepTau2017v2p1VSmu"] )
      input->select("Events/Tau_rawDeepTau2017v2p1VSmu",
                     Tau_rawDeepTau2017v2p1VSmu);
    if ( choose["Events/Tau_rawIso"] )
      input->select("Events/Tau_rawIso", 	Tau_rawIso);
    if ( choose["Events/Tau_rawIsodR03"] )
      input->select("Events/Tau_rawIsodR03", 	Tau_rawIsodR03);
    if ( choose["Events/Tau_rawMVAnewDM2017v2"] )
      input->select("Events/Tau_rawMVAnewDM2017v2", 	Tau_rawMVAnewDM2017v2);
    if ( choose["Events/Tau_rawMVAoldDM"] )
      input->select("Events/Tau_rawMVAoldDM", 	Tau_rawMVAoldDM);
    if ( choose["Events/Tau_rawMVAoldDM2017v1"] )
      input->select("Events/Tau_rawMVAoldDM2017v1", 	Tau_rawMVAoldDM2017v1);
    if ( choose["Events/Tau_rawMVAoldDM2017v2"] )
      input->select("Events/Tau_rawMVAoldDM2017v2", 	Tau_rawMVAoldDM2017v2);
    if ( choose["Events/Tau_rawMVAoldDMdR032017v2"] )
      input->select("Events/Tau_rawMVAoldDMdR032017v2",
                     Tau_rawMVAoldDMdR032017v2);
    if ( choose["Events/TkMET_phi"] )
      input->select("Events/TkMET_phi", 	TkMET_phi);
    if ( choose["Events/TkMET_pt"] )
      input->select("Events/TkMET_pt", 	TkMET_pt);
    if ( choose["Events/TkMET_sumEt"] )
      input->select("Events/TkMET_sumEt", 	TkMET_sumEt);
    if ( choose["Events/TrigObj_eta"] )
      input->select("Events/TrigObj_eta", 	TrigObj_eta);
    if ( choose["Events/TrigObj_filterBits"] )
      input->select("Events/TrigObj_filterBits", 	TrigObj_filterBits);
    if ( choose["Events/TrigObj_id"] )
      input->select("Events/TrigObj_id", 	TrigObj_id);
    if ( choose["Events/TrigObj_l1charge"] )
      input->select("Events/TrigObj_l1charge", 	TrigObj_l1charge);
    if ( choose["Events/TrigObj_l1iso"] )
      input->select("Events/TrigObj_l1iso", 	TrigObj_l1iso);
    if ( choose["Events/TrigObj_l1pt"] )
      input->select("Events/TrigObj_l1pt", 	TrigObj_l1pt);
    if ( choose["Events/TrigObj_l1pt_2"] )
      input->select("Events/TrigObj_l1pt_2", 	TrigObj_l1pt_2);
    if ( choose["Events/TrigObj_l2pt"] )
      input->select("Events/TrigObj_l2pt", 	TrigObj_l2pt);
    if ( choose["Events/TrigObj_phi"] )
      input->select("Events/TrigObj_phi", 	TrigObj_phi);
    if ( choose["Events/TrigObj_pt"] )
      input->select("Events/TrigObj_pt", 	TrigObj_pt);
    if ( choose["Events/btagWeight_CMVA"] )
      input->select("Events/btagWeight_CMVA", 	btagWeight_CMVA);
    if ( choose["Events/btagWeight_CSVV2"] )
      input->select("Events/btagWeight_CSVV2", 	btagWeight_CSVV2);
    if ( choose["Events/event"] )
      input->select("Events/event", 	event);
    if ( choose["Events/fixedGridRhoFastjetAll"] )
      input->select("Events/fixedGridRhoFastjetAll",
                     fixedGridRhoFastjetAll);
    if ( choose["Events/fixedGridRhoFastjetCentral"] )
      input->select("Events/fixedGridRhoFastjetCentral",
                     fixedGridRhoFastjetCentral);
    if ( choose["Events/fixedGridRhoFastjetCentralCalo"] )
      input->select("Events/fixedGridRhoFastjetCentralCalo",
                     fixedGridRhoFastjetCentralCalo);
    if ( choose["Events/fixedGridRhoFastjetCentralChargedPileUp"] )
      input->select("Events/fixedGridRhoFastjetCentralChargedPileUp",
                     fixedGridRhoFastjetCentralChargedPileUp);
    if ( choose["Events/fixedGridRhoFastjetCentralNeutral"] )
      input->select("Events/fixedGridRhoFastjetCentralNeutral",
                     fixedGridRhoFastjetCentralNeutral);
    if ( choose["Events/genTtbarId"] )
      input->select("Events/genTtbarId", 	genTtbarId);
    if ( choose["Events/genWeight"] )
      input->select("Events/genWeight", 	genWeight);
    if ( choose["Events/luminosityBlock"] )
      input->select("Events/luminosityBlock", 	luminosityBlock);
    if ( choose["Events/run"] )
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
    output->add("nSV", 	nSV);
    output->add("nOtherPV", 	nOtherPV);
    output->add("nLHEReweightingWeight", 	nLHEReweightingWeight);
    output->add("nLHEPdfWeight", 	nLHEPdfWeight);
    output->add("nTrigObj", 	nTrigObj);
    output->add("nFsrPhoton", 	nFsrPhoton);
    output->add("nElectron", 	nElectron);
    output->add("nIsoTrack", 	nIsoTrack);
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
    output->add("Events/Electron_charge[nElectron]", 	Electron_charge);
    output->add("Events/Electron_cleanmask[nElectron]",
                 Electron_cleanmask);
    output->add("Events/Electron_convVeto[nElectron]", 	Electron_convVeto);
    output->add("Events/Electron_cutBased[nElectron]", 	Electron_cutBased);
    output->add("Events/Electron_cutBased_Fall17_V1[nElectron]",
                 Electron_cutBased_Fall17_V1);
    output->add("Events/Electron_cutBased_HEEP[nElectron]",
                 Electron_cutBased_HEEP);
    output->add("Events/Electron_cutBased_HLTPreSel[nElectron]",
                 Electron_cutBased_HLTPreSel);
    output->add("Events/Electron_cutBased_Spring15[nElectron]",
                 Electron_cutBased_Spring15);
    output->add("Events/Electron_cutBased_Sum16[nElectron]",
                 Electron_cutBased_Sum16);
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
    output->add("Events/Electron_mvaFall17V1Iso[nElectron]",
                 Electron_mvaFall17V1Iso);
    output->add("Events/Electron_mvaFall17V1Iso_WP80[nElectron]",
                 Electron_mvaFall17V1Iso_WP80);
    output->add("Events/Electron_mvaFall17V1Iso_WP90[nElectron]",
                 Electron_mvaFall17V1Iso_WP90);
    output->add("Events/Electron_mvaFall17V1Iso_WPL[nElectron]",
                 Electron_mvaFall17V1Iso_WPL);
    output->add("Events/Electron_mvaFall17V1noIso[nElectron]",
                 Electron_mvaFall17V1noIso);
    output->add("Events/Electron_mvaFall17V1noIso_WP80[nElectron]",
                 Electron_mvaFall17V1noIso_WP80);
    output->add("Events/Electron_mvaFall17V1noIso_WP90[nElectron]",
                 Electron_mvaFall17V1noIso_WP90);
    output->add("Events/Electron_mvaFall17V1noIso_WPL[nElectron]",
                 Electron_mvaFall17V1noIso_WPL);
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
    output->add("Events/Electron_mvaSpring16GP[nElectron]",
                 Electron_mvaSpring16GP);
    output->add("Events/Electron_mvaSpring16GP_WP80[nElectron]",
                 Electron_mvaSpring16GP_WP80);
    output->add("Events/Electron_mvaSpring16GP_WP90[nElectron]",
                 Electron_mvaSpring16GP_WP90);
    output->add("Events/Electron_mvaSpring16HZZ[nElectron]",
                 Electron_mvaSpring16HZZ);
    output->add("Events/Electron_mvaSpring16HZZ_WPL[nElectron]",
                 Electron_mvaSpring16HZZ_WPL);
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
    output->add("Events/Electron_seedGain[nElectron]", 	Electron_seedGain);
    output->add("Events/Electron_sieie[nElectron]", 	Electron_sieie);
    output->add("Events/Electron_sip3d[nElectron]", 	Electron_sip3d);
    output->add("Events/Electron_tightCharge[nElectron]",
                 Electron_tightCharge);
    output->add("Events/Electron_vidNestedWPBitmap[nElectron]",
                 Electron_vidNestedWPBitmap);
    output->add("Events/Electron_vidNestedWPBitmapHEEP[nElectron]",
                 Electron_vidNestedWPBitmapHEEP);
    output->add("Events/Electron_vidNestedWPBitmapSpring15[nElectron]",
                 Electron_vidNestedWPBitmapSpring15);
    output->add("Events/Electron_vidNestedWPBitmapSum16[nElectron]",
                 Electron_vidNestedWPBitmapSum16);
    output->add("Events/FatJet_area[nFatJet]", 	FatJet_area);
    output->add("Events/FatJet_btagCMVA[nFatJet]", 	FatJet_btagCMVA);
    output->add("Events/FatJet_btagCSVV2[nFatJet]", 	FatJet_btagCSVV2);
    output->add("Events/FatJet_btagDDBvL[nFatJet]", 	FatJet_btagDDBvL);
    output->add("Events/FatJet_btagDDBvL_noMD[nFatJet]",
                 FatJet_btagDDBvL_noMD);
    output->add("Events/FatJet_btagDDCvB[nFatJet]", 	FatJet_btagDDCvB);
    output->add("Events/FatJet_btagDDCvB_noMD[nFatJet]",
                 FatJet_btagDDCvB_noMD);
    output->add("Events/FatJet_btagDDCvL[nFatJet]", 	FatJet_btagDDCvL);
    output->add("Events/FatJet_btagDDCvL_noMD[nFatJet]",
                 FatJet_btagDDCvL_noMD);
    output->add("Events/FatJet_btagDeepB[nFatJet]", 	FatJet_btagDeepB);
    output->add("Events/FatJet_btagHbb[nFatJet]", 	FatJet_btagHbb);
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
    output->add("Events/FatJet_eta[nFatJet]", 	FatJet_eta);
    output->add("Events/FatJet_jetId[nFatJet]", 	FatJet_jetId);
    output->add("Events/FatJet_mass[nFatJet]", 	FatJet_mass);
    output->add("Events/FatJet_msoftdrop[nFatJet]", 	FatJet_msoftdrop);
    output->add("Events/FatJet_n2b1[nFatJet]", 	FatJet_n2b1);
    output->add("Events/FatJet_n3b1[nFatJet]", 	FatJet_n3b1);
    output->add("Events/FatJet_phi[nFatJet]", 	FatJet_phi);
    output->add("Events/FatJet_pt[nFatJet]", 	FatJet_pt);
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
    output->add("Events/Flag_ecalBadCalibFilterV2", 	Flag_ecalBadCalibFilterV2);
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
    output->add("Events/Generator_binvar", 	Generator_binvar);
    output->add("Events/Generator_id1", 	Generator_id1);
    output->add("Events/Generator_id2", 	Generator_id2);
    output->add("Events/Generator_scalePDF", 	Generator_scalePDF);
    output->add("Events/Generator_weight", 	Generator_weight);
    output->add("Events/Generator_x1", 	Generator_x1);
    output->add("Events/Generator_x2", 	Generator_x2);
    output->add("Events/Generator_xpdf1", 	Generator_xpdf1);
    output->add("Events/Generator_xpdf2", 	Generator_xpdf2);
    output->add("Events/HLT_AK4PFJet100", 	HLT_AK4PFJet100);
    output->add("Events/HLT_AK4PFJet120",   HLT_AK4PFJet120);
    output->add("Events/HLT_AK4PFJet30", 	HLT_AK4PFJet30);
    output->add("Events/HLT_AK4PFJet50", 	HLT_AK4PFJet50);
    output->add("Events/HLT_AK4PFJet80", 	HLT_AK4PFJet80);
    output->add("Events/HLT_AK8PFHT650_TrimR0p1PT0p03Mass50",
                 HLT_AK8PFHT650_TrimR0p1PT0p03Mass50);
    output->add("Events/HLT_AK8PFHT700_TrimR0p1PT0p03Mass50",
                 HLT_AK8PFHT700_TrimR0p1PT0p03Mass50);
    output->add("Events/HLT_AK8PFHT750_TrimMass50",
                 HLT_AK8PFHT750_TrimMass50);
    output->add("Events/HLT_AK8PFHT800_TrimMass50",
                 HLT_AK8PFHT800_TrimMass50);
    output->add("Events/HLT_AK8PFHT850_TrimMass50",
                 HLT_AK8PFHT850_TrimMass50);
    output->add("Events/HLT_AK8PFHT900_TrimMass50",
                 HLT_AK8PFHT900_TrimMass50);
    output->add("Events/HLT_AK8PFJet140", 	HLT_AK8PFJet140);
    output->add("Events/HLT_AK8PFJet200", 	HLT_AK8PFJet200);
    output->add("Events/HLT_AK8PFJet260", 	HLT_AK8PFJet260);
    output->add("Events/HLT_AK8PFJet320", 	HLT_AK8PFJet320);
    output->add("Events/HLT_AK8PFJet360_TrimMass30",
                 HLT_AK8PFJet360_TrimMass30);
    output->add("Events/HLT_AK8PFJet40", 	HLT_AK8PFJet40);
    output->add("Events/HLT_AK8PFJet400", 	HLT_AK8PFJet400);
    output->add("Events/HLT_AK8PFJet400_TrimMass30",
                 HLT_AK8PFJet400_TrimMass30);
    output->add("Events/HLT_AK8PFJet450", 	HLT_AK8PFJet450);
    output->add("Events/HLT_AK8PFJet500", 	HLT_AK8PFJet500);
    output->add("Events/HLT_AK8PFJet60", 	HLT_AK8PFJet60);
    output->add("Events/HLT_AK8PFJet80", 	HLT_AK8PFJet80);
    output->add("Events/HLT_Ele115_CaloIdVT_GsfTrkIdT",
                 HLT_Ele115_CaloIdVT_GsfTrkIdT);
    output->add("Events/HLT_Ele15_IsoVVVL_PFHT450",
                 HLT_Ele15_IsoVVVL_PFHT450);
    output->add("Events/HLT_Ele23_WPLoose_Gsf", 	HLT_Ele23_WPLoose_Gsf);
    output->add("Events/HLT_Ele25_WPTight_Gsf", 	HLT_Ele25_WPTight_Gsf);
    output->add("Events/HLT_Ele27_WPLoose_Gsf", 	HLT_Ele27_WPLoose_Gsf);
    output->add("Events/HLT_Ele27_WPTight_Gsf", 	HLT_Ele27_WPTight_Gsf);
    output->add("Events/HLT_Ele28_WPTight_Gsf",   HLT_Ele28_WPTight_Gsf);
    output->add("Events/HLT_Ele30_WPTight_Gsf", 	HLT_Ele30_WPTight_Gsf);
    output->add("Events/HLT_Ele32_WPTight_Gsf", 	HLT_Ele32_WPTight_Gsf);
    output->add("Events/HLT_Ele35_WPLoose_Gsf", 	HLT_Ele35_WPLoose_Gsf);
    output->add("Events/HLT_Ele35_WPTight_Gsf",   HLT_Ele35_WPTight_Gsf);
    output->add("Events/HLT_Ele38_WPTight_Gsf",   HLT_Ele38_WPTight_Gsf);
    output->add("Events/HLT_Ele40_WPTight_Gsf",   HLT_Ele40_WPTight_Gsf);
    output->add("Events/HLT_Ele45_WPLoose_Gsf", 	HLT_Ele45_WPLoose_Gsf);
    output->add("Events/HLT_HT200", 	HLT_HT200);
    output->add("Events/HLT_HT2000", 	HLT_HT2000);
    output->add("Events/HLT_HT2500", 	HLT_HT2500);
    output->add("Events/HLT_HT275", 	HLT_HT275);
    output->add("Events/HLT_HT325", 	HLT_HT325);
    output->add("Events/HLT_HT410to430", 	HLT_HT410to430);
    output->add("Events/HLT_HT425", 	HLT_HT425);
    output->add("Events/HLT_HT430to450", 	HLT_HT430to450);
    output->add("Events/HLT_HT450to470", 	HLT_HT450to470);
    output->add("Events/HLT_HT470to500", 	HLT_HT470to500);
    output->add("Events/HLT_HT500to550", 	HLT_HT500to550);
    output->add("Events/HLT_HT550to650", 	HLT_HT550to650);
    output->add("Events/HLT_HT575", 	HLT_HT575);
    output->add("Events/HLT_HT650", 	HLT_HT650);
    output->add("Events/HLT_IsoMu20", 	HLT_IsoMu20);
    output->add("Events/HLT_IsoMu22", 	HLT_IsoMu22);
    output->add("Events/HLT_IsoMu24", 	HLT_IsoMu24);
    output->add("Events/HLT_IsoMu27", 	HLT_IsoMu27);
    output->add("Events/HLT_IsoMu30",   HLT_IsoMu30);
    output->add("Events/HLT_IsoTkMu20", 	HLT_IsoTkMu20);
    output->add("Events/HLT_IsoTkMu22", 	HLT_IsoTkMu22);
    output->add("Events/HLT_IsoTkMu24", 	HLT_IsoTkMu24);
    output->add("Events/HLT_IsoTkMu27", 	HLT_IsoTkMu27);
    output->add("Events/HLT_MET100", 	HLT_MET100);
    output->add("Events/HLT_MET150", 	HLT_MET150);
    output->add("Events/HLT_MET200", 	HLT_MET200);
    output->add("Events/HLT_MET250", 	HLT_MET250);
    output->add("Events/HLT_MET300", 	HLT_MET300);
    output->add("Events/HLT_MET600", 	HLT_MET600);
    output->add("Events/HLT_MET60_IsoTrk35_Loose",
                 HLT_MET60_IsoTrk35_Loose);
    output->add("Events/HLT_MET700", 	HLT_MET700);
    output->add("Events/HLT_MET75_IsoTrk50", 	HLT_MET75_IsoTrk50);
    output->add("Events/HLT_MET90_IsoTrk50", 	HLT_MET90_IsoTrk50);
    output->add("Events/HLT_Mu15_IsoVVVL_PFHT450",
                 HLT_Mu15_IsoVVVL_PFHT450);
    output->add("Events/HLT_Mu20", 	HLT_Mu20);
    output->add("Events/HLT_Mu27", 	HLT_Mu27);
    output->add("Events/HLT_Mu300", 	HLT_Mu300);
    output->add("Events/HLT_Mu350", 	HLT_Mu350);
    output->add("Events/HLT_Mu50", 	HLT_Mu50);
    output->add("Events/HLT_Mu55", 	HLT_Mu55);
    output->add("Events/HLT_PFHT1050",  HLT_PFHT1050);
    output->add("Events/HLT_PFHT125", 	HLT_PFHT125);
    output->add("Events/HLT_PFHT180", 	HLT_PFHT180);
    output->add("Events/HLT_PFHT370", 	HLT_PFHT370);
    output->add("Events/HLT_PFHT430", 	HLT_PFHT430);
    output->add("Events/HLT_PFHT510", 	HLT_PFHT510);
    output->add("Events/HLT_PFHT590", 	HLT_PFHT590);
    output->add("Events/HLT_PFHT200", 	HLT_PFHT200);
    output->add("Events/HLT_PFHT250", 	HLT_PFHT250);
    output->add("Events/HLT_PFHT300", 	HLT_PFHT300);
    output->add("Events/HLT_PFHT300_PFMET100", 	HLT_PFHT300_PFMET100);
    output->add("Events/HLT_PFHT300_PFMET110", 	HLT_PFHT300_PFMET110);
    output->add("Events/HLT_PFHT350", 	HLT_PFHT350);
    output->add("Events/HLT_PFHT400", 	HLT_PFHT400);
    output->add("Events/HLT_PFHT475", 	HLT_PFHT475);
    output->add("Events/HLT_PFHT500_PFMET100_PFMHT100_IDTight",
                 HLT_PFHT500_PFMET100_PFMHT100_IDTight);
    output->add("Events/HLT_PFHT500_PFMET110_PFMHT110_IDTight",
                 HLT_PFHT500_PFMET110_PFMHT110_IDTight);
    output->add("Events/HLT_PFHT600", 	HLT_PFHT600);
    output->add("Events/HLT_PFHT650", 	HLT_PFHT650);
    output->add("Events/HLT_PFHT680",   HLT_PFHT680);
    output->add("Events/HLT_PFHT700_PFMET85_PFMHT85_IDTight",
                 HLT_PFHT700_PFMET85_PFMHT85_IDTight);
    output->add("Events/HLT_PFHT700_PFMET95_PFMHT95_IDTight",
                 HLT_PFHT700_PFMET95_PFMHT95_IDTight);
    output->add("Events/HLT_PFHT780",   HLT_PFHT780);
    output->add("Events/HLT_PFHT800_PFMET75_PFMHT75_IDTight",
                 HLT_PFHT800_PFMET75_PFMHT75_IDTight);
    output->add("Events/HLT_PFHT800_PFMET85_PFMHT85_IDTight",
                 HLT_PFHT800_PFMET85_PFMHT85_IDTight);
    output->add("Events/HLT_PFHT890",   HLT_PFHT890);
    output->add("Events/HLT_PFHT800", 	HLT_PFHT800);
    output->add("Events/HLT_PFHT900", 	HLT_PFHT900);
    output->add("Events/HLT_PFJet140", 	HLT_PFJet140);
    output->add("Events/HLT_PFJet200", 	HLT_PFJet200);
    output->add("Events/HLT_PFJet260", 	HLT_PFJet260);
    output->add("Events/HLT_PFJet320", 	HLT_PFJet320);
    output->add("Events/HLT_PFJet40", 	HLT_PFJet40);
    output->add("Events/HLT_PFJet400", 	HLT_PFJet400);
    output->add("Events/HLT_PFJet450", 	HLT_PFJet450);
    output->add("Events/HLT_PFJet500", 	HLT_PFJet500);
    output->add("Events/HLT_PFJet60", 	HLT_PFJet60);
    output->add("Events/HLT_PFJet80", 	HLT_PFJet80);
    output->add("Events/HLT_PFMET100_PFMHT100_IDTight",
                 HLT_PFMET100_PFMHT100_IDTight);
    output->add("Events/HLT_PFMET110_PFMHT110_IDTight",
                 HLT_PFMET110_PFMHT110_IDTight);
    output->add("Events/HLT_PFMET120_PFMHT120_IDTight",
                 HLT_PFMET120_PFMHT120_IDTight);
    output->add("Events/HLT_PFMET170_HBHECleaned",
                 HLT_PFMET170_HBHECleaned);
    output->add("Events/HLT_PFMET170_JetIdCleaned",
                 HLT_PFMET170_JetIdCleaned);
    output->add("Events/HLT_PFMET170_NoiseCleaned",
                 HLT_PFMET170_NoiseCleaned);
    output->add("Events/HLT_PFMET170_NotCleaned", 	HLT_PFMET170_NotCleaned);
    output->add("Events/HLT_PFMET300", 	HLT_PFMET300);
    output->add("Events/HLT_PFMET400", 	HLT_PFMET400);
    output->add("Events/HLT_PFMET500", 	HLT_PFMET500);
    output->add("Events/HLT_PFMET600", 	HLT_PFMET600);
    output->add("Events/HLT_PFMET90_PFMHT90_IDTight",
                 HLT_PFMET90_PFMHT90_IDTight);
    output->add("Events/HLT_PFMETNoMu90_PFMHTNoMu90_IDTight",
                 HLT_PFMETNoMu90_PFMHTNoMu90_IDTight);
    output->add("Events/HLT_PFMETNoMu100_PFMHTNoMu100_IDTight",
                 HLT_PFMETNoMu100_PFMHTNoMu100_IDTight);
    output->add("Events/HLT_PFMETNoMu110_PFMHTNoMu110_IDTight",
                 HLT_PFMETNoMu110_PFMHTNoMu110_IDTight);
    output->add("Events/HLT_PFMETNoMu120_PFMHTNoMu120_IDTight",
                 HLT_PFMETNoMu120_PFMHTNoMu120_IDTight);
    output->add("Events/HLT_PFMETNoMu130_PFMHTNoMu130_IDTight",
                 HLT_PFMETNoMu130_PFMHTNoMu130_IDTight);
    output->add("Events/HLT_PFMETNoMu140_PFMHTNoMu140_IDTight",
                 HLT_PFMETNoMu140_PFMHTNoMu140_IDTight);
    output->add("Events/HLT_PFMETTypeOne120_PFMHT120_IDTight",
                 HLT_PFMETTypeOne120_PFMHT120_IDTight);
    output->add("Events/HLT_Photon100EBHE10",   HLT_Photon100EBHE10);
    output->add("Events/HLT_Photon100EB_TightID_TightIso",
                 HLT_Photon100EB_TightID_TightIso);
    output->add("Events/HLT_Photon100EEHE10",   HLT_Photon100EEHE10);
    output->add("Events/HLT_Photon100EE_TightID_TightIso",
                 HLT_Photon100EE_TightID_TightIso);
    output->add("Events/HLT_Photon110EB_TightID_TightIso",
                 HLT_Photon110EB_TightID_TightIso);
    output->add("Events/HLT_Photon120", 	HLT_Photon120);
    output->add("Events/HLT_Photon125", 	HLT_Photon125);
    output->add("Events/HLT_Photon135_PFMET100", 	HLT_Photon135_PFMET100);
    output->add("Events/HLT_Photon150", 	HLT_Photon150);
    output->add("Events/HLT_Photon165_HE10", 	HLT_Photon165_HE10);
    output->add("Events/HLT_Photon175", 	HLT_Photon175);
    output->add("Events/HLT_Photon20",  HLT_Photon20);
    output->add("Events/HLT_Photon200",   HLT_Photon200);
    output->add("Events/HLT_Photon22", 	HLT_Photon22);
    output->add("Events/HLT_Photon25", 	HLT_Photon25);
    output->add("Events/HLT_Photon250_NoHE", 	HLT_Photon250_NoHE);
    output->add("Events/HLT_Photon30", 	HLT_Photon30);
    output->add("Events/HLT_Photon300_NoHE", 	HLT_Photon300_NoHE);
    output->add("Events/HLT_Photon33",  HLT_Photon33);
    output->add("Events/HLT_Photon36", 	HLT_Photon36);
    output->add("Events/HLT_Photon50", 	HLT_Photon50);
    output->add("Events/HLT_Photon500", 	HLT_Photon500);
    output->add("Events/HLT_Photon600", 	HLT_Photon600);
    output->add("Events/HLT_Photon75", 	HLT_Photon75);
    output->add("Events/HLT_Photon90", 	HLT_Photon90);
    output->add("Events/HLT_Rsq0p25", 	HLT_Rsq0p25);
    output->add("Events/HLT_Rsq0p30", 	HLT_Rsq0p30);
    output->add("Events/HLT_Rsq0p35",   HLT_Rsq0p35);
    output->add("Events/HLT_Rsq0p40",   HLT_Rsq0p40);
    output->add("Events/HLT_RsqMR300_Rsq0p09_MR200",
                 HLT_RsqMR300_Rsq0p09_MR200);
    output->add("Events/HLT_RsqMR320_Rsq0p09_MR200", 
                 HLT_RsqMR320_Rsq0p09_MR200);
    output->add("Events/HLT_RsqMR240_Rsq0p09_MR200",
                 HLT_RsqMR240_Rsq0p09_MR200);
    output->add("Events/HLT_RsqMR270_Rsq0p09_MR200",
                 HLT_RsqMR270_Rsq0p09_MR200);
    output->add("Events/HLT_TkMu20", 	HLT_TkMu20);
    output->add("Events/HLT_TkMu27", 	HLT_TkMu27);
    output->add("Events/HLT_TkMu50", 	HLT_TkMu50);
    output->add("Events/HLTriggerFinalPath", 	HLTriggerFinalPath);
    output->add("Events/HLTriggerFirstPath", 	HLTriggerFirstPath);
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
    output->add("Events/Jet_btagCMVA[nJet]", 	Jet_btagCMVA);
    output->add("Events/Jet_btagCSVV2[nJet]", 	Jet_btagCSVV2);
    output->add("Events/Jet_btagDeepB[nJet]", 	Jet_btagDeepB);
    output->add("Events/Jet_btagDeepC[nJet]", 	Jet_btagDeepC);
    output->add("Events/Jet_btagDeepFlavB[nJet]", 	Jet_btagDeepFlavB);
    output->add("Events/Jet_btagDeepFlavC[nJet]", 	Jet_btagDeepFlavC);
    output->add("Events/Jet_chEmEF[nJet]", 	Jet_chEmEF);
    output->add("Events/Jet_chHEF[nJet]", 	Jet_chHEF);
    output->add("Events/Jet_cleanmask[nJet]", 	Jet_cleanmask);
    output->add("Events/Jet_electronIdx1[nJet]", 	Jet_electronIdx1);
    output->add("Events/Jet_electronIdx2[nJet]", 	Jet_electronIdx2);
    output->add("Events/Jet_eta[nJet]", 	Jet_eta);
    output->add("Events/Jet_genJetIdx[nJet]", 	Jet_genJetIdx);
    output->add("Events/Jet_hadronFlavour[nJet]", 	Jet_hadronFlavour);
    output->add("Events/Jet_jercCHF[nJet]", 	Jet_jercCHF);
    output->add("Events/Jet_jercCHPUF[nJet]", 	Jet_jercCHPUF);
    output->add("Events/Jet_jetId[nJet]", 	Jet_jetId);
    output->add("Events/Jet_mass[nJet]", 	Jet_mass);
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
    output->add("Events/Jet_pt[nJet]", 	Jet_pt);
    output->add("Events/Jet_puId[nJet]", 	Jet_puId);
    output->add("Events/Jet_qgl[nJet]", 	Jet_qgl);
    output->add("Events/Jet_rawFactor[nJet]", 	Jet_rawFactor);
    output->add("Events/LHEPart_eta[nLHEPart]", 	LHEPart_eta);
    output->add("Events/LHEPart_mass[nLHEPart]", 	LHEPart_mass);
    output->add("Events/LHEPart_pdgId[nLHEPart]", 	LHEPart_pdgId);
    output->add("Events/LHEPart_phi[nLHEPart]", 	LHEPart_phi);
    output->add("Events/LHEPart_pt[nLHEPart]", 	LHEPart_pt);
    output->add("Events/LHEPdfWeight[nLHEPdfWeight]", 	LHEPdfWeight);
    output->add("Events/LHEReweightingWeight[nLHEReweightingWeight]",
                 LHEReweightingWeight);
    output->add("Events/LHEScaleWeight[nLHEScaleWeight]", 	LHEScaleWeight);
    output->add("Events/LHEWeight_originalXWGTUP",
                 LHEWeight_originalXWGTUP);
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
    output->add("Events/METFixEE2017_MetUnclustEnUpDeltaX",
                 METFixEE2017_MetUnclustEnUpDeltaX);
    output->add("Events/METFixEE2017_MetUnclustEnUpDeltaY",
                 METFixEE2017_MetUnclustEnUpDeltaY);
    output->add("Events/METFixEE2017_covXX",  METFixEE2017_covXX);
    output->add("Events/METFixEE2017_covXY",  METFixEE2017_covXY);
    output->add("Events/METFixEE2017_covYY",  METFixEE2017_covYY);
    output->add("Events/METFixEE2017_phi",  METFixEE2017_phi);
    output->add("Events/METFixEE2017_pt",   METFixEE2017_pt);
    output->add("Events/METFixEE2017_significance",
                 METFixEE2017_significance); 
    output->add("Events/METFixEE2017_sumEt",  METFixEE2017_sumEt);
    output->add("Events/MET_MetUnclustEnUpDeltaX",
                 MET_MetUnclustEnUpDeltaX);
    output->add("Events/MET_MetUnclustEnUpDeltaY",
                 MET_MetUnclustEnUpDeltaY);
    output->add("Events/MET_covXX", 	MET_covXX);
    output->add("Events/MET_covXY", 	MET_covXY);
    output->add("Events/MET_covYY", 	MET_covYY);
    output->add("Events/MET_fiducialGenPhi", 	MET_fiducialGenPhi);
    output->add("Events/MET_fiducialGenPt", 	MET_fiducialGenPt);
    output->add("Events/MET_phi", 	MET_phi);
    output->add("Events/MET_pt", 	MET_pt);
    output->add("Events/MET_significance", 	MET_significance);
    output->add("Events/MET_sumEt", 	MET_sumEt);
    output->add("Events/Muon_charge[nMuon]", 	Muon_charge);
    output->add("Events/Muon_cleanmask[nMuon]", 	Muon_cleanmask);
    output->add("Events/Muon_dxy[nMuon]", 	Muon_dxy);
    output->add("Events/Muon_dxyErr[nMuon]", 	Muon_dxyErr);
    output->add("Events/Muon_dz[nMuon]", 	Muon_dz);
    output->add("Events/Muon_dzErr[nMuon]", 	Muon_dzErr);
    output->add("Events/Muon_eta[nMuon]", 	Muon_eta);
    output->add("Events/Muon_fsrPhotonIdx[nMuon]", 	Muon_fsrPhotonIdx);
    output->add("Events/Muon_genPartFlav[nMuon]", 	Muon_genPartFlav);
    output->add("Events/Muon_genPartIdx[nMuon]", 	Muon_genPartIdx);
    output->add("Events/Muon_highPtId[nMuon]", 	Muon_highPtId);
    output->add("Events/Muon_inTimeMuon[nMuon]", 	Muon_inTimeMuon);
    output->add("Events/Muon_ip3d[nMuon]", 	Muon_ip3d);
    output->add("Events/Muon_isGlobal[nMuon]", 	Muon_isGlobal);
    output->add("Events/Muon_isPFcand[nMuon]", 	Muon_isPFcand);
    output->add("Events/Muon_isTracker[nMuon]", 	Muon_isTracker);
    output->add("Events/Muon_jetIdx[nMuon]", 	Muon_jetIdx);
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
    output->add("Events/Muon_segmentComp[nMuon]", 	Muon_segmentComp);
    output->add("Events/Muon_sip3d[nMuon]", 	Muon_sip3d);
    output->add("Events/Muon_softId[nMuon]", 	Muon_softId);
    output->add("Events/Muon_softMva[nMuon]",   Muon_softMva);
    output->add("Events/Muon_softMvaId[nMuon]", 	Muon_softMvaId);
    output->add("Events/Muon_tightCharge[nMuon]", 	Muon_tightCharge);
    output->add("Events/Muon_tightId[nMuon]", 	Muon_tightId);
    output->add("Events/Muon_tkIsoId[nMuon]", 	Muon_tkIsoId);
    output->add("Events/Muon_tkRelIso[nMuon]", 	Muon_tkRelIso);
    output->add("Events/Muon_triggerIdLoose[nMuon]", 	Muon_triggerIdLoose);
    output->add("Events/Muon_tunepRelPt[nMuon]", 	Muon_tunepRelPt);
    output->add("Events/OtherPV_z[nOtherPV]", 	OtherPV_z);
    output->add("Events/PSWeight", 	PSWeight);
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
    output->add("Events/Photon_cutBased17Bitmap[nPhoton]",
                 Photon_cutBased17Bitmap);
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
    output->add("Events/Photon_mvaID17[nPhoton]", 	Photon_mvaID17);
    output->add("Events/Photon_mvaID17_WP80[nPhoton]",
                 Photon_mvaID17_WP80);
    output->add("Events/Photon_mvaID17_WP90[nPhoton]",
                 Photon_mvaID17_WP90);
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
    output->add("Events/PuppiMET_pt", 	PuppiMET_pt);
    output->add("Events/PuppiMET_sumEt", 	PuppiMET_sumEt);
    output->add("Events/RawMET_phi", 	RawMET_phi);
    output->add("Events/RawMET_pt", 	RawMET_pt);
    output->add("Events/RawMET_sumEt", 	RawMET_sumEt);
    output->add("Events/SubJet_btagCMVA[nSubJet]", 	SubJet_btagCMVA);
    output->add("Events/SubJet_btagCSVV2[nSubJet]", 	SubJet_btagCSVV2);
    output->add("Events/SubJet_btagDeepB[nSubJet]", 	SubJet_btagDeepB);
    output->add("Events/SubJet_eta[nSubJet]", 	SubJet_eta);
    output->add("Events/SubJet_mass[nSubJet]", 	SubJet_mass);
    output->add("Events/SubJet_n2b1[nSubJet]", 	SubJet_n2b1);
    output->add("Events/SubJet_n3b1[nSubJet]", 	SubJet_n3b1);
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
    output->add("Events/Tau_idAntiEle[nTau]", 	Tau_idAntiEle);
    output->add("Events/Tau_idAntiEle2018[nTau]", 	Tau_idAntiEle2018);
    output->add("Events/Tau_idAntiMu[nTau]", 	Tau_idAntiMu);
    output->add("Events/Tau_idDecayMode[nTau]", 	Tau_idDecayMode);
    output->add("Events/Tau_idDecayModeNewDMs[nTau]",
                 Tau_idDecayModeNewDMs);
    output->add("Events/Tau_idDeepTau2017v2p1VSe[nTau]",
                 Tau_idDeepTau2017v2p1VSe);
    output->add("Events/Tau_idDeepTau2017v2p1VSjet[nTau]",
                 Tau_idDeepTau2017v2p1VSjet);
    output->add("Events/Tau_idDeepTau2017v2p1VSmu[nTau]",
                 Tau_idDeepTau2017v2p1VSmu);
    output->add("Events/Tau_idMVAnewDM2017v2[nTau]", 	Tau_idMVAnewDM2017v2);
    output->add("Events/Tau_idMVAoldDM[nTau]", 	Tau_idMVAoldDM);
    output->add("Events/Tau_idMVAoldDM2017v1[nTau]", 	Tau_idMVAoldDM2017v1);
    output->add("Events/Tau_idMVAoldDM2017v2[nTau]", 	Tau_idMVAoldDM2017v2);
    output->add("Events/Tau_idMVAoldDMdR032017v2[nTau]",
                 Tau_idMVAoldDMdR032017v2);
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
    output->add("Events/Tau_rawAntiEle[nTau]", 	Tau_rawAntiEle);
    output->add("Events/Tau_rawAntiEle2018[nTau]", 	Tau_rawAntiEle2018);
    output->add("Events/Tau_rawAntiEleCat[nTau]", 	Tau_rawAntiEleCat);
    output->add("Events/Tau_rawAntiEleCat2018[nTau]",
                 Tau_rawAntiEleCat2018);
    output->add("Events/Tau_rawDeepTau2017v2p1VSe[nTau]",
                 Tau_rawDeepTau2017v2p1VSe);
    output->add("Events/Tau_rawDeepTau2017v2p1VSjet[nTau]",
                 Tau_rawDeepTau2017v2p1VSjet);
    output->add("Events/Tau_rawDeepTau2017v2p1VSmu[nTau]",
                 Tau_rawDeepTau2017v2p1VSmu);
    output->add("Events/Tau_rawIso[nTau]", 	Tau_rawIso);
    output->add("Events/Tau_rawIsodR03[nTau]", 	Tau_rawIsodR03);
    output->add("Events/Tau_rawMVAnewDM2017v2[nTau]",
                 Tau_rawMVAnewDM2017v2);
    output->add("Events/Tau_rawMVAoldDM[nTau]", 	Tau_rawMVAoldDM);
    output->add("Events/Tau_rawMVAoldDM2017v1[nTau]",
                 Tau_rawMVAoldDM2017v1);
    output->add("Events/Tau_rawMVAoldDM2017v2[nTau]",
                 Tau_rawMVAoldDM2017v2);
    output->add("Events/Tau_rawMVAoldDMdR032017v2[nTau]",
                 Tau_rawMVAoldDMdR032017v2);
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
    output->add("Events/btagWeight_CMVA", 	btagWeight_CMVA);
    output->add("Events/btagWeight_CSVV2", 	btagWeight_CSVV2);
    output->add("Events/event", 	event);
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
    Electron_cutBased_Fall17_V1	= std::vector<int>(25,0);
    Electron_cutBased_HEEP	= std::vector<bool>(25,0);
    Electron_cutBased_HLTPreSel	= std::vector<int>(25,0);
    Electron_cutBased_Spring15	= std::vector<int>(25,0);
    Electron_cutBased_Sum16	= std::vector<int>(25,0);
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
    Electron_jetPtRelv2	= std::vector<float>(25,0);
    Electron_jetRelIso	= std::vector<float>(25,0);
    Electron_lostHits	= std::vector<int>(25,0);
    Electron_mass	= std::vector<float>(25,0);
    Electron_miniPFRelIso_all	= std::vector<float>(25,0);
    Electron_miniPFRelIso_chg	= std::vector<float>(25,0);
    Electron_mvaFall17V1Iso	= std::vector<float>(25,0);
    Electron_mvaFall17V1Iso_WP80	= std::vector<bool>(25,0);
    Electron_mvaFall17V1Iso_WP90	= std::vector<bool>(25,0);
    Electron_mvaFall17V1Iso_WPL	= std::vector<bool>(25,0);
    Electron_mvaFall17V1noIso	= std::vector<float>(25,0);
    Electron_mvaFall17V1noIso_WP80	= std::vector<bool>(25,0);
    Electron_mvaFall17V1noIso_WP90	= std::vector<bool>(25,0);
    Electron_mvaFall17V1noIso_WPL	= std::vector<bool>(25,0);
    Electron_mvaFall17V2Iso	= std::vector<float>(25,0);
    Electron_mvaFall17V2Iso_WP80	= std::vector<bool>(25,0);
    Electron_mvaFall17V2Iso_WP90	= std::vector<bool>(25,0);
    Electron_mvaFall17V2Iso_WPL	= std::vector<bool>(25,0);
    Electron_mvaFall17V2noIso	= std::vector<float>(25,0);
    Electron_mvaFall17V2noIso_WP80	= std::vector<bool>(25,0);
    Electron_mvaFall17V2noIso_WP90	= std::vector<bool>(25,0);
    Electron_mvaFall17V2noIso_WPL	= std::vector<bool>(25,0);
    Electron_mvaSpring16GP	= std::vector<float>(25,0);
    Electron_mvaSpring16GP_WP80	= std::vector<bool>(25,0);
    Electron_mvaSpring16GP_WP90	= std::vector<bool>(25,0);
    Electron_mvaSpring16HZZ	= std::vector<float>(25,0);
    Electron_mvaSpring16HZZ_WPL	= std::vector<bool>(25,0);
    Electron_mvaTTH	= std::vector<float>(25,0);
    Electron_pdgId	= std::vector<int>(25,0);
    Electron_pfRelIso03_all	= std::vector<float>(25,0);
    Electron_pfRelIso03_chg	= std::vector<float>(25,0);
    Electron_phi	= std::vector<float>(25,0);
    Electron_photonIdx	= std::vector<int>(25,0);
    Electron_pt	= std::vector<float>(25,0);
    Electron_r9	= std::vector<float>(25,0);
    Electron_seedGain	= std::vector<int>(25,0);
    Electron_sieie	= std::vector<float>(25,0);
    Electron_sip3d	= std::vector<float>(25,0);
    Electron_tightCharge	= std::vector<int>(25,0);
    Electron_vidNestedWPBitmap	= std::vector<int>(25,0);
    Electron_vidNestedWPBitmapHEEP	= std::vector<int>(25,0);
    Electron_vidNestedWPBitmapSpring15	= std::vector<int>(25,0);
    Electron_vidNestedWPBitmapSum16	= std::vector<int>(25,0);
    FatJet_area	= std::vector<float>(15,0);
    FatJet_btagCMVA	= std::vector<float>(15,0);
    FatJet_btagCSVV2	= std::vector<float>(15,0);
    FatJet_btagDDBvL	= std::vector<float>(15,0);
    FatJet_btagDDBvL_noMD	= std::vector<float>(15,0);
    FatJet_btagDDCvB	= std::vector<float>(15,0);
    FatJet_btagDDCvB_noMD	= std::vector<float>(15,0);
    FatJet_btagDDCvL	= std::vector<float>(15,0);
    FatJet_btagDDCvL_noMD	= std::vector<float>(15,0);
    FatJet_btagDeepB	= std::vector<float>(15,0);
    FatJet_btagHbb	= std::vector<float>(15,0);
    FatJet_deepTagMD_H4qvsQCD	= std::vector<float>(15,0);
    FatJet_deepTagMD_HbbvsQCD	= std::vector<float>(15,0);
    FatJet_deepTagMD_TvsQCD	= std::vector<float>(15,0);
    FatJet_deepTagMD_WvsQCD	= std::vector<float>(15,0);
    FatJet_deepTagMD_ZHbbvsQCD	= std::vector<float>(15,0);
    FatJet_deepTagMD_ZHccvsQCD	= std::vector<float>(15,0);
    FatJet_deepTagMD_ZbbvsQCD	= std::vector<float>(15,0);
    FatJet_deepTagMD_ZvsQCD	= std::vector<float>(15,0);
    FatJet_deepTagMD_bbvsLight	= std::vector<float>(15,0);
    FatJet_deepTagMD_ccvsLight	= std::vector<float>(15,0);
    FatJet_deepTag_H	= std::vector<float>(15,0);
    FatJet_deepTag_QCD	= std::vector<float>(15,0);
    FatJet_deepTag_QCDothers	= std::vector<float>(15,0);
    FatJet_deepTag_TvsQCD	= std::vector<float>(15,0);
    FatJet_deepTag_WvsQCD	= std::vector<float>(15,0);
    FatJet_deepTag_ZvsQCD	= std::vector<float>(15,0);
    FatJet_eta	= std::vector<float>(15,0);
    FatJet_jetId	= std::vector<int>(15,0);
    FatJet_mass	= std::vector<float>(15,0);
    FatJet_msoftdrop	= std::vector<float>(15,0);
    FatJet_n2b1	= std::vector<float>(15,0);
    FatJet_n3b1	= std::vector<float>(15,0);
    FatJet_phi	= std::vector<float>(15,0);
    FatJet_pt	= std::vector<float>(15,0);
    FatJet_rawFactor	= std::vector<float>(15,0);
    FatJet_subJetIdx1	= std::vector<int>(15,0);
    FatJet_subJetIdx2	= std::vector<int>(15,0);
    FatJet_tau1	= std::vector<float>(15,0);
    FatJet_tau2	= std::vector<float>(15,0);
    FatJet_tau3	= std::vector<float>(15,0);
    FatJet_tau4	= std::vector<float>(15,0);
    FsrPhoton_dROverEt2	= std::vector<float>(10,0);
    FsrPhoton_eta	= std::vector<float>(10,0);
    FsrPhoton_muonIdx	= std::vector<int>(10,0);
    FsrPhoton_phi	= std::vector<float>(10,0);
    FsrPhoton_pt	= std::vector<float>(10,0);
    FsrPhoton_relIso03	= std::vector<float>(10,0);
    GenPart_eta	= std::vector<float>(155,0);
    GenPart_genPartIdxMother	= std::vector<int>(155,0);
    GenPart_mass	= std::vector<float>(155,0);
    GenPart_pdgId	= std::vector<int>(155,0);
    GenPart_phi	= std::vector<float>(155,0);
    GenPart_pt	= std::vector<float>(155,0);
    GenPart_status	= std::vector<int>(155,0);
    GenPart_statusFlags	= std::vector<int>(155,0);
    IsoTrack_dxy	= std::vector<float>(20,0);
    IsoTrack_dz	= std::vector<float>(20,0);
    IsoTrack_eta	= std::vector<float>(20,0);
    IsoTrack_fromPV	= std::vector<int>(20,0);
    IsoTrack_isFromLostTrack	= std::vector<bool>(20,0);
    IsoTrack_isHighPurityTrack	= std::vector<bool>(20,0);
    IsoTrack_isPFcand	= std::vector<bool>(20,0);
    IsoTrack_miniPFRelIso_all	= std::vector<float>(20,0);
    IsoTrack_miniPFRelIso_chg	= std::vector<float>(20,0);
    IsoTrack_pdgId	= std::vector<int>(20,0);
    IsoTrack_pfRelIso03_all	= std::vector<float>(20,0);
    IsoTrack_pfRelIso03_chg	= std::vector<float>(20,0);
    IsoTrack_phi	= std::vector<float>(20,0);
    IsoTrack_pt	= std::vector<float>(20,0);
    Jet_area	= std::vector<float>(45,0);
    Jet_bRegCorr	= std::vector<float>(45,0);
    Jet_bRegRes	= std::vector<float>(45,0);
    Jet_btagCMVA	= std::vector<float>(45,0);
    Jet_btagCSVV2	= std::vector<float>(45,0);
    Jet_btagDeepB	= std::vector<float>(45,0);
    Jet_btagDeepC	= std::vector<float>(45,0);
    Jet_btagDeepFlavB	= std::vector<float>(45,0);
    Jet_btagDeepFlavC	= std::vector<float>(45,0);
    Jet_chEmEF	= std::vector<float>(45,0);
    Jet_chHEF	= std::vector<float>(45,0);
    Jet_cleanmask	= std::vector<int>(45,0);
    Jet_electronIdx1	= std::vector<int>(45,0);
    Jet_electronIdx2	= std::vector<int>(45,0);
    Jet_eta	= std::vector<float>(45,0);
    Jet_genJetIdx	= std::vector<int>(45,0);
    Jet_hadronFlavour	= std::vector<int>(45,0);
    Jet_jercCHF	= std::vector<float>(45,0);
    Jet_jercCHPUF	= std::vector<float>(45,0);
    Jet_jetId	= std::vector<int>(45,0);
    Jet_mass	= std::vector<float>(45,0);
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
    Jet_puId	= std::vector<int>(45,0);
    Jet_qgl	= std::vector<float>(45,0);
    Jet_rawFactor	= std::vector<float>(45,0);
    LHEPart_eta	= std::vector<float>(20,0);
    LHEPart_mass	= std::vector<float>(20,0);
    LHEPart_pdgId	= std::vector<int>(20,0);
    LHEPart_phi	= std::vector<float>(20,0);
    LHEPart_pt	= std::vector<float>(20,0);
    LHEPdfWeight	= std::vector<float>(155,0);
    LHEReweightingWeight	= std::vector<float>(100,0);
    LHEScaleWeight	= std::vector<float>(25,0);
    Muon_charge	= std::vector<int>(25,0);
    Muon_cleanmask	= std::vector<int>(25,0);
    Muon_dxy	= std::vector<float>(25,0);
    Muon_dxyErr	= std::vector<float>(25,0);
    Muon_dz	= std::vector<float>(25,0);
    Muon_dzErr	= std::vector<float>(25,0);
    Muon_eta	= std::vector<float>(25,0);
    Muon_fsrPhotonIdx	= std::vector<int>(25,0);
    Muon_genPartFlav	= std::vector<int>(25,0);
    Muon_genPartIdx	= std::vector<int>(25,0);
    Muon_highPtId	= std::vector<int>(25,0);
    Muon_inTimeMuon	= std::vector<bool>(25,0);
    Muon_ip3d	= std::vector<float>(25,0);
    Muon_isGlobal	= std::vector<bool>(25,0);
    Muon_isPFcand	= std::vector<bool>(25,0);
    Muon_isTracker	= std::vector<bool>(25,0);
    Muon_jetIdx	= std::vector<int>(25,0);
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
    Muon_segmentComp	= std::vector<float>(25,0);
    Muon_sip3d	= std::vector<float>(25,0);
    Muon_softId	= std::vector<bool>(25,0);
    Muon_softMva  = std::vector<float>(25,0);
    Muon_softMvaId	= std::vector<bool>(25,0);
    Muon_tightCharge	= std::vector<int>(25,0);
    Muon_tightId	= std::vector<bool>(25,0);
    Muon_tkIsoId	= std::vector<int>(25,0);
    Muon_tkRelIso	= std::vector<float>(25,0);
    Muon_triggerIdLoose	= std::vector<bool>(25,0);
    Muon_tunepRelPt	= std::vector<float>(25,0);
    OtherPV_z	= std::vector<float>(15,0);
    Photon_charge	= std::vector<int>(25,0);
    Photon_cleanmask	= std::vector<int>(25,0);
    Photon_cutBased	= std::vector<int>(25,0);
    Photon_cutBased17Bitmap	= std::vector<int>(25,0);
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
    Photon_mvaID17	= std::vector<float>(25,0);
    Photon_mvaID17_WP80	= std::vector<bool>(25,0);
    Photon_mvaID17_WP90	= std::vector<bool>(25,0);
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
    SubJet_btagCMVA	= std::vector<float>(15,0);
    SubJet_btagCSVV2	= std::vector<float>(15,0);
    SubJet_btagDeepB	= std::vector<float>(15,0);
    SubJet_eta	= std::vector<float>(15,0);
    SubJet_mass	= std::vector<float>(15,0);
    SubJet_n2b1	= std::vector<float>(15,0);
    SubJet_n3b1	= std::vector<float>(15,0);
    SubJet_phi	= std::vector<float>(15,0);
    SubJet_pt	= std::vector<float>(15,0);
    SubJet_rawFactor	= std::vector<float>(15,0);
    SubJet_tau1	= std::vector<float>(15,0);
    SubJet_tau2	= std::vector<float>(15,0);
    SubJet_tau3	= std::vector<float>(15,0);
    SubJet_tau4	= std::vector<float>(15,0);
    Tau_charge	= std::vector<int>(25,0);
    Tau_chargedIso	= std::vector<float>(25,0);
    Tau_cleanmask	= std::vector<int>(25,0);
    Tau_decayMode	= std::vector<int>(25,0);
    Tau_dxy	= std::vector<float>(25,0);
    Tau_dz	= std::vector<float>(25,0);
    Tau_eta	= std::vector<float>(25,0);
    Tau_genPartFlav	= std::vector<int>(25,0);
    Tau_genPartIdx	= std::vector<int>(25,0);
    Tau_idAntiEle	= std::vector<int>(25,0);
    Tau_idAntiEle2018	= std::vector<int>(25,0);
    Tau_idAntiMu	= std::vector<int>(25,0);
    Tau_idDecayMode	= std::vector<bool>(25,0);
    Tau_idDecayModeNewDMs	= std::vector<bool>(25,0);
    Tau_idDeepTau2017v2p1VSe	= std::vector<int>(25,0);
    Tau_idDeepTau2017v2p1VSjet	= std::vector<int>(25,0);
    Tau_idDeepTau2017v2p1VSmu	= std::vector<int>(25,0);
    Tau_idMVAnewDM2017v2	= std::vector<int>(25,0);
    Tau_idMVAoldDM	= std::vector<int>(25,0);
    Tau_idMVAoldDM2017v1	= std::vector<int>(25,0);
    Tau_idMVAoldDM2017v2	= std::vector<int>(25,0);
    Tau_idMVAoldDMdR032017v2	= std::vector<int>(25,0);
    Tau_jetIdx	= std::vector<int>(25,0);
    Tau_leadTkDeltaEta	= std::vector<float>(25,0);
    Tau_leadTkDeltaPhi	= std::vector<float>(25,0);
    Tau_leadTkPtOverTauPt	= std::vector<float>(25,0);
    Tau_mass	= std::vector<float>(25,0);
    Tau_neutralIso	= std::vector<float>(25,0);
    Tau_phi	= std::vector<float>(25,0);
    Tau_photonsOutsideSignalCone	= std::vector<float>(25,0);
    Tau_pt	= std::vector<float>(25,0);
    Tau_puCorr	= std::vector<float>(25,0);
    Tau_rawAntiEle	= std::vector<float>(25,0);
    Tau_rawAntiEle2018	= std::vector<float>(25,0);
    Tau_rawAntiEleCat	= std::vector<int>(25,0);
    Tau_rawAntiEleCat2018	= std::vector<int>(25,0);
    Tau_rawDeepTau2017v2p1VSe	= std::vector<float>(25,0);
    Tau_rawDeepTau2017v2p1VSjet	= std::vector<float>(25,0);
    Tau_rawDeepTau2017v2p1VSmu	= std::vector<float>(25,0);
    Tau_rawIso	= std::vector<float>(25,0);
    Tau_rawIsodR03	= std::vector<float>(25,0);
    Tau_rawMVAnewDM2017v2	= std::vector<float>(25,0);
    Tau_rawMVAoldDM	= std::vector<float>(25,0);
    Tau_rawMVAoldDM2017v1	= std::vector<float>(25,0);
    Tau_rawMVAoldDM2017v2	= std::vector<float>(25,0);
    Tau_rawMVAoldDMdR032017v2	= std::vector<float>(25,0);
    TrigObj_eta	= std::vector<float>(60,0);
    TrigObj_filterBits	= std::vector<int>(60,0);
    TrigObj_id	= std::vector<int>(60,0);
    TrigObj_l1charge	= std::vector<int>(60,0);
    TrigObj_l1iso	= std::vector<int>(60,0);
    TrigObj_l1pt	= std::vector<float>(60,0);
    TrigObj_l1pt_2	= std::vector<float>(60,0);
    TrigObj_l2pt	= std::vector<float>(60,0);
    TrigObj_phi	= std::vector<float>(60,0);
    TrigObj_pt	= std::vector<float>(60,0);
    CorrT1METJet	= std::vector<eventBuffer::CorrT1METJet_s>(45);
    Electron	= std::vector<eventBuffer::Electron_s>(25);
    FatJet	= std::vector<eventBuffer::FatJet_s>(15);
    FsrPhoton	= std::vector<eventBuffer::FsrPhoton_s>(10);
    GenPart	= std::vector<eventBuffer::GenPart_s>(155);
    IsoTrack	= std::vector<eventBuffer::IsoTrack_s>(20);
    Jet	= std::vector<eventBuffer::Jet_s>(45);
    LHEPart	= std::vector<eventBuffer::LHEPart_s>(20);
    Muon	= std::vector<eventBuffer::Muon_s>(25);
    Photon	= std::vector<eventBuffer::Photon_s>(25);
    SubJet	= std::vector<eventBuffer::SubJet_s>(15);
    Tau	= std::vector<eventBuffer::Tau_s>(25);
    TrigObj	= std::vector<eventBuffer::TrigObj_s>(60);

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
