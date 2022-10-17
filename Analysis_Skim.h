#include "TLorentzVector.h"
#include "TMath.h"
#include "include/AnalysisBase.h"
//#include "Razor.h"

//_______________________________________________________
//                  Calculate variables

void
Analysis::calculate_variables(eventBuffer& data, const unsigned int& syst_index)
{
}

//_______________________________________________________
//                Define Skimming cuts
//   (Not needed, unless you want to skim the ntuple)

bool
Analysis::pass_skimming(eventBuffer& data)
{
/*
  int NJetAK8 = 0; 
  for (size_t i=0; i<data.FatJet.size(); ++i) {
    // pt cut intentionally removed to accept all jets for systematics
    if ( (data.FatJet[i].jetId == 2 || data.FatJet[i].jetId == 6) &&
	 data.FatJet[i].pt         >= 100 &&
         std::abs(data.FatJet[i].eta)  <  3.0 ) {
      NJetAK8++;
    }
  }

  if (!(NJetAK8>=1)) return 0;
*/
  int nLepVeto = 0;
  int nMuSelect = 0;
  int nEleSelect = 0;
  int nPhotonPreSelect = 0;
  std::vector<TLorentzVector> veto_leptons_noiso, selected_leptons, photons_PreSelect;
  if (!isSignal) {
    // Count veto electrons
    for (size_t i=0; i<data.Electron.size(); ++i) {
      TLorentzVector ele_v4; ele_v4.SetPtEtaPhiM(data.Electron[i].pt, data.Electron[i].eta, data.Electron[i].phi, data.Electron[i].mass);
      double pt      = data.Electron[i].pt;
      double eta     = data.Electron[i].eta;
      float abseta   = std::abs(eta);
      float miniIso  = data.Electron[i].miniPFRelIso_all;
      float absd0    = std::abs(data.Electron[i].dxy);
      float absdz    = std::abs(data.Electron[i].dz);
      bool id_veto_noiso   = (data.Electron[i].mvaFall17V2noIso_WPL == 1.0);
      bool id_select_noiso = (data.Electron[i].mvaFall17V2noIso_WP90 == 1.0);
      float absIso  = data.Electron[i].pfRelIso03_all*pt;
      float ipsig = std::abs(data.Electron[i].sip3d);
      // Veto
      if ( id_veto_noiso &&
     pt      >= 5 &&
     abseta  <  2.5 && !(abseta>=1.442 && abseta< 1.556) &&
     ( ( absd0   <  0.05 &&
         absdz   <  0.1 )
       || ipsig  <  4 ) &&
     ( pt>20 ?
       miniIso <  0.1 :
       miniIso <  0.1 || absIso < 5) ) {
        veto_leptons.push_back(ele_v4);
        nLepVeto++;
      }
      if ( id_select_noiso &&
      pt        >= 10 &&
      abseta    <  2.5 && !(abseta>=1.442 && abseta< 1.556) &&
      miniIso   <  0.1 &&
      absd0     <  0.05 &&
      absdz     <  0.1) {
        selected_leptons.push_back(ele_v4);
        nEleSelect++;
      }
    }
    // Count veto muons
     for (size_t i=0; i<data.Muon.size(); ++i) {
       TLorentzVector mu_v4; mu_v4.SetPtEtaPhiM(data.Muon[i].pt, data.Muon[i].eta, data.Muon[i].phi, data.Muon[i].mass);
       float pt = data.Muon[i].pt;
       float abseta = std::abs(data.Muon[i].eta);
       float miniIso = data.Muon[i].miniPFRelIso_all;
       float absIso  = data.Muon[i].pfRelIso04_all*pt;
       float absd0 = std::abs(data.Muon[i].dxy);
       float absdz = std::abs(data.Muon[i].dz);
       float ipsig = std::abs(data.Muon[i].sip3d);
       bool id_veto_noiso   = (data.Muon[i].softId == 1.0);
       bool id_select_noiso = (data.Muon[i].mediumId == 1.0);
      // Veto
      if ( id_veto_noiso &&
     pt      >= 5 &&
     abseta  <  2.4 &&
     ( ( absd0   <  0.2 &&
         absdz   <  0.5 )
       || ipsig  <  4 ) &&
     ( pt>20 ?
       miniIso <  0.4 : 
       miniIso <  0.4 || absIso < 10) ) {
        nLepVeto++;
        veto_leptons.push_back(mu_v4);
      }
      if( id_select_noiso &&
      pt      >= 10 &&
      abseta  <  2.4 &&
      miniIso <  0.15 &&
      absd0   <  0.05 &&
      absdz   <  0.1 ) {
        nMuSelect++;
        selected_leptons.push_back(mu_v4);
      }
    }
    // Count photons
    for (size_t i=0; i<data.Photon.size(); ++i) {
      TLorentzVector pho_v4; pho_v4.SetPtEtaPhiM(data.Photon[i].pt, data.Photon[i].eta, data.Photon[i].phi, data.Photon[i].mass);
      float pt = data.Photon[i].pt;
      float abseta = std::abs(data.Photon[i].eta);
      bool ele_veto  = data.Photon[i].electronVeto;
      
      if (ele_veto &&
        pt        >= 40 &&
        abseta    <  2.5 ) {
        nPhotonPreSelect++;
        photons_PreSelect.push_back(pho_v4);
      }
    }
    // Let events with at least 1 ele/mu/phtotn pass
    //if (NMuVeto >0)         return 1;
    //if (NEleVeto>0)         return 1;
    //if (nPhotonPreSelect>0) return 1;
  }

  // Add the lepton (pair) to MET
  TVector3 met_1l, met_1vl, met_ll;
  met_1l. SetPtEtaPhi(data.MET_pt, 0, data.MET_phi);
  met_1vl.SetPtEtaPhi(data.MET_pt, 0, data.MET_phi);
  met_ll. SetPtEtaPhi(data.MET_pt, 0, data.MET_phi);
  if (nEleSelect+nMuSelect==1) {
    TVector3 lep_met;
    lep_met.SetPtEtaPhi(selected_leptons[0].Pt(), 0, selected_leptons[0].Phi());
    met_1l += lep_met;
  }
  if (nLepVeto==1) {
    TVector3 lep_met;
    lep_met.SetPtEtaPhi(veto_leptons[0].Pt(), 0, veto_leptons[0].Phi());
    met_1vl += lep_met;
  }
  if (nEleSelect==2 || nMuSelect==2) {
    TVector3 lep_pair_met;
    lep_pair_met.SetPtEtaPhi(lep_pair.Pt(), 0, lep_pair.Phi());
    met_ll += lep_pair_met;
  }

  // Add the photon to MET
  TVector3 met_pho;
  met_pho.SetPtEtaPhi(data.MET_pt, 0, data.MET_phi);
  if (nPhotonPreSelect==1) {
    // Add also preselected photons
    TVector3 pho_met;
    pho_met.SetPtEtaPhi(photons_PreSelect[0].Pt(), 0, photons_PreSelect[0].Phi());
    met_pho += pho_met;
  }


  float MR=-9999., MTR=-9999., R=-9999., R2=-9999.;
  float MTR_1l=-9999., R_1l=-9999., R2_1l=-9999.;
  float MTR_1vl=-9999., R_1vl=-9999., R2_1vl=-9999.;
  float MTR_ll=-9999., R_ll=-9999., R2_ll=-9999.;
  float MR_pho=-9999., MTR_pho=-9999., R_pho=-9999., R2_pho=-9999.;
  std::vector<TLorentzVector> selected_jets_AK4;
  std::vector<TLorentzVector> nophoton_jets_AK4;
  std::vector<TLorentzVector> hemis_AK4;
  std::vector<TLorentzVector> hemis_AK4_nophoton;

  for(size_t i=0; i<data.Jet.size(); ++i) {
    TLorentzVector jet_v4; jet_v4.SetPtEtaPhiM(data.Jet[i].pt, data.Jet[i].eta, data.Jet[i].phi, data.Jet[i].mass);
    if (  (data.Jet[i].jetId >= 1) &&
           data.Jet[i].pt         >= 40 &&
           std::abs(data.Jet[i].eta)  <  2.4 ) { 
       selected_jets_AK4.push_back(jet_v4);
       if(nPhotonPreSelect==1){
         double dR = photons_PreSelect[0].DeltaR(jet_v4);
         double pt_ratio = photons_PreSelect[0].Pt()/jet_v4.Pt();
         if(!(dR<0.4 && pt_ratio>=0.5&&pt_ratio<2.0)) nophoton_jets_AK4.push_back(jet_v4);
       }
    }
  }
  if (selected_jets_AK4.size()>=2) hemis_AK4 = Razor::CombineJets(selected_jets_AK4);
  else hemis_AK4.clear();
  if (nPhotonPreSelect==1) {
    if (nophoton_jets_AK4.size()>=2) hemis_AK4_nophoton = Razor::CombineJets(nophoton_jets_AK4);
    else hemis_AK4_nophoton.clear();
  } else hemis_AK4_nophoton = hemis_AK4;

  if (hemis_AK4.size()==2) {
    // Normal Razor
    TVector3 shifted_met;
    shifted_met.SetPtEtaPhi(data.MET_pt, 0, data.MET_phi);
    MR  = Razor::CalcMR(hemis_AK4[0], hemis_AK4[1]);
    MTR = Razor::CalcMTR(hemis_AK4[0], hemis_AK4[1], shifted_met);
    R   = MTR/MR;
    R2  = R*R;
    // 1 (selected) lepton added
    if (nEleSelect+nMuSelect==1) {
      MTR_1l = Razor::CalcMTR(hemis_AK4[0], hemis_AK4[1], met_1l);
      R_1l   = MTR_1l/MR;
      R2_1l  = R_1l*R_1l;
    }
    // 1 veto lepton added (default)
    if (nLepVeto==1) {
      MTR_1vl = Razor::CalcMTR(hemis_AK4[0], hemis_AK4[1], met_1vl);
      R_1vl   = MTR_1vl/MR;
      R2_1vl  = R_1vl*R_1vl;
    }
    // 2 leptons added
  if (nEleSelect==2 || nMuSelect==2) {
      MTR_ll = Razor::CalcMTR(hemis_AK4[0], hemis_AK4[1], met_ll);
      R_ll   = MTR_ll/MR;
      R2_ll  = R_ll*R_ll;
    }
  }
  // Remove photon from both jet collections and add to MET
  if (hemis_AK4_nophoton.size()==2) {
    MR_pho  = Razor::CalcMR(hemis_AK4_nophoton[0], hemis_AK4_nophoton[1]);
    MTR_pho = Razor::CalcMTR(hemis_AK4_nophoton[0], hemis_AK4_nophoton[1], met_pho);
    R_pho   = MTR_pho/MR_pho;
    R2_pho  = R_pho*R_pho;
    dPhiRazorNoPho = std::abs(TVector2::Phi_mpi_pi(hemis_AK4_nophoton[0].Phi() - hemis_AK4_nophoton[1].Phi()));
  }
  if (R2<0.04&&R2_1l<0.04&&R2_1vl<0.04&&R2_ll<0.04&&R2_pho<0.04) return 0;
  return 1;
}

//_______________________________________________________
//          Define Analysis event selection cuts
//     Can define all sorts of Signal/Control regions

void
Analysis::define_selections(const eventBuffer& d)
{
  analysis_cuts.clear();
}

//____________________________________________________
//          Analysis Specific Scale factors
//    (Defined for each search region separately)

void
Analysis::apply_scale_factors(eventBuffer& data, const unsigned int& s, const std::vector<std::vector<double> >& nSigmaSFs)
{
}

//_______________________________________________________
//                 Signal Region
//     Must define it, because we blind it in data!

bool
Analysis::signal_selection(const eventBuffer& data) {
  //return apply_all_cuts('S');
  return 0;
}

//_______________________________________________________
//                 List of Histograms


//_______________________________________________________
//              Define Histograms here
void
Analysis::init_analysis_histos(const unsigned int& syst_nSyst, const unsigned int& syst_index)
{

}

//_______________________________________________________
//               Fill Histograms here
void
Analysis::fill_analysis_histos(eventBuffer& data, const unsigned int& syst_index, const double& weight)
{
  double w = weight; // No scale factor applied
  if (syst_index == 0) {
    // syst_index should only be non-0 if settings.varySystematics is true
    // in case of studying systematics, one should fill a different histogram for each syst_index
    // this variable can be used to chose the correct vector element in case there is a vector of histograms
    // It makes sense, to cut on syst_index == 0, for all ordinary plots
    // syst_index == 0 always guarantees, there are no variations in any systematics
    
    // Check what include variables are available in AnalysisBase.h
    // There a good chance a lot of stuff is already calculated!
    // Especially include object selections or variables to cut on in Analysis

    //bool pass = data.HLT_AK8PFJet360_TrimMass30+data.HLT_PFHT800 == 0 ? false : true;
    //bool pass1 = (data.HLT_AK8PFJet450 == 1 || data.HLT_PFHT800 == 1 || data.HLT_PFHT900 == 1);
    //bool pass2 = (data.HLT_AK8PFJet450 == 1 || data.HLT_PFHT800 == 1);
    //bool pass3 = (data.HLT_AK8PFJet450 == 1 || data.HLT_PFHT900 == 1);

    /*
      Weight:
      They now include trigger efficiencies for MC by default
      w is the event weight without any scale factor applied
      Because scale factors are region dependend, then
      in order to apply them, one has to use the sf_weight[region] variable instead
      eg. sf_weight['S']
     */

    // Baseline cuts 
    // Additionally, let's apply the trigger selection
    // since the weight contains the trigger scaling in MC
    // no specific region, so don't apply scale factors
    // Especially for comparison plots with Ufuk/Fatma
    // Alternatively, could apply SF of the Signal regio

    //double w = sf_weight['S']; // Scale factors applied for the Signal region


    }


    // Trigger efficiencies
    // No weighting
 
    // I guess these histots are for data only (trigger efficiencies)
    // One could just use the normal weight  for that ( = 1)
    // Since MC already has trigger efficiency weight applied already
    // one could use simply 1 as the weight there also
    // N-1 weights are not currently supported

    //w = isData ? 1 : sf_weight['S'];
    w = 1;

}

// Methods used by SmartHistos (Plotter)
// Can leave them empty
void
Analysis::define_histo_options(const double& w, const eventBuffer& d, const unsigned int& syst_nSyst,
			       const unsigned int& syst_index, bool runOnSkim=false)
{
}

void
Analysis::load_analysis_histos(std::string inputfile)
{
}

void
Analysis::save_analysis_histos(bool draw=0)
{
}
