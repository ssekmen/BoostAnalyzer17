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

  float MR = -9999., MTR=-9999., R=-9999., R2=-9999.;
  std::vector<TLorentzVector> selected_jets_AK4;
  std::vector<TLorentzVector> hemis_AK4;

  for(size_t i=0; i<data.Jet.size(); ++i) {
    TLorentzVector jet_v4; jet_v4.SetPtEtaPhiM(data.Jet[i].pt, data.Jet[i].eta, data.Jet[i].phi, data.Jet[i].mass);
    if (  (data.Jet[i].jetId == 2 || data.Jet[i].jetId == 6 ) &&
           data.Jet[i].pt         >= 30 &&
           std::abs(data.Jet[i].eta)  <  2.4 )  selected_jets_AK4.push_back(jet_v4);
  }
  if (selected_jets_AK4.size()>=2) hemis_AK4 = Razor::CombineJets(selected_jets_AK4);
  else hemis_AK4.clear();
  if (hemis_AK4.size()==2) {
    // Normal Razor
    TVector3 shifted_met;
    shifted_met.SetPtEtaPhi(data.MET_pt, 0, data.MET_phi);
    MR  = Razor::CalcMR(hemis_AK4[0], hemis_AK4[1]);
    MTR = Razor::CalcMTR(hemis_AK4[0], hemis_AK4[1], shifted_met);
    R   = MTR/MR;
    R2  = R*R;
  }
  if (!isSignal) {
    // Count veto electrons
    int NEleVeto = 0;
    for (size_t i=0; i<data.Electron.size(); ++i) {
      double pt      = data.Electron[i].pt;
      double eta     = data.Electron[i].eta;
      float abseta   = std::abs(eta);
      float miniIso  = data.Electron[i].miniPFRelIso_all;
      float absd0    = std::abs(data.Electron[i].dxy);
      float absdz    = std::abs(data.Electron[i].dz);
      bool id_veto_noiso   = (data.Electron[i].mvaFall17noIso_WPL == 1.0);
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
        NEleVeto++;
      }
    }
    // Count veto muons
    int NMuVeto = 0;
     for (size_t i=0; i<data.Muon.size(); ++i) {
       float pt = data.Muon[i].pt;
       float abseta = std::abs(data.Muon[i].eta);
       float miniIso = data.Muon[i].miniPFRelIso_all;
       float absIso  = data.Muon[i].pfRelIso04_all*pt;
       float absd0 = std::abs(data.Muon[i].dxy);
       float absdz = std::abs(data.Muon[i].dz);
       float ipsig = std::abs(data.Muon[i].sip3d);
       bool id_veto_noiso   = (data.Muon[i].softId == 1.0);
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
        NMuVeto++;
      }
    }
    // Count photons
    int NPhotonPreSelect = 0;
    for (size_t i=0; i<data.Photon.size(); ++i) {
      float pt = data.Photon[i].pt;
      float abseta = std::abs(data.Photon[i].eta);
      bool ele_veto  = data.Photon[i].electronVeto;
      bool id_PreSelect= data.Photon[i].mvaID_WP80;
      
      if ( id_PreSelect &&
        ele_veto &&
        pt        >= 40 &&
        abseta    <  2.5 ) {
        NPhotonPreSelect++;
      }
    }
    // Let events with at least 1 ele/mu/phtotn pass
    if (NMuVeto >0)         return 1;
    if (NEleVeto>0)         return 1;
    if (NPhotonPreSelect>0) return 1;
  }

  if (!(R2>=0.04)) return 0;
  return 1;
}

//_______________________________________________________
//          Define Analysis event selection cuts
//     Can define all sorts of Signal/Control regions

void
Analysis::define_selections(const eventBuffer& d)
{
  analysis_cuts.clear();

  // Define here cuts that are include in all Signal/Control regions
  // MET Filters, etc. are already applied in AnalysisBase.h, See baseline_cuts

  // cut0: signal mass region
/*
bool isT2tt = TString(sample).Contains("T2tt");
  if(isT2tt){ 
  baseline_cuts.push_back({ .name="signal_mass_selection",   .func = [&d]{ 
            //return d.evt.SUSY_Gluino_Mass==mGluino[num] && d.evt.SUSY_LSP_Mass==mLSP[num];
            //return d.evt.SUSY_Gluino_Mass==2000 && d.evt.SUSY_LSP_Mass==300;
            return d.evt.SUSY_Stop_Mass==1100 && d.evt.SUSY_LSP_Mass==0;
	    } });}
bool isT5tttt = TString(sample).Contains("T5tttt");
  if(isT5tttt){ 
  baseline_cuts.push_back({ .name="signal_mass_selection",   .func = [&d]{ 
            //return d.evt.SUSY_Gluino_Mass==mGluino[num] && d.evt.SUSY_LSP_Mass==mLSP[num];
            return d.evt.SUSY_Gluino_Mass==1400 && d.evt.SUSY_LSP_Mass==300;
            //return d.evt.SUSY_Stop_Mass==800 && d.evt.SUSY_LSP_Mass==100;
	    } });}
bool isT1tttt = TString(sample).Contains("T1tttt");
  if(isT1tttt){ 
  baseline_cuts.push_back({ .name="signal_mass_selection",   .func = [&d]{ 
            return d.evt.SUSY_Gluino_Mass==1400 && d.evt.SUSY_LSP_Mass==300;
	    } });}
bool isT5ttcc = TString(sample).Contains("T5ttcc");
  if(isT5ttcc){ 
  baseline_cuts.push_back({ .name="signal_mass_selection",   .func = [&d]{ 
            return d.evt.SUSY_Gluino_Mass==1700 && d.evt.SUSY_LSP_Mass==300;
	    } });}
*/
  // fake rate
  analysis_cuts['K'].push_back({ .name="1JetAK8",    .func = []    { return nJetAK8>=1;                      }}); // Similar to pt>200, one AK8 jet has pt>200
  analysis_cuts['K'].push_back({ .name="NJet",       .func = []    { return nJet>=4;                          }});
  analysis_cuts['K'].push_back({ .name="HLT",   .func = [this,&d]  { return isData ? d.HLT_AK8PFJet450==1 || d.HLT_PFHT1050==1 : 1; }});
  //analysis_cuts['K'].push_back({ .name="HLT",   .func = [this,&d]  { return d.HLT_AK8PFJet450==1 || d.HLT_PFHT1050==1; }});
  analysis_cuts['K'].push_back({ .name="0Ele",       .func = []    { return nEleVeto==0;                      }});
  analysis_cuts['K'].push_back({ .name="0Mu",        .func = []    { return nMuVeto==0;                       }});
  analysis_cuts['K'].push_back({ .name="0b",         .func = []    { return nLooseBTag==0;                    }});
#if USE_ISO_TRK_VETO > 0
  analysis_cuts['K'].push_back({ .name="0Tau",       .func = [&d]  { return d.evt.NIsoTrk==0;                 }});  
#else  
  analysis_cuts['K'].push_back({ .name="0Tau",       .func = []    { return nTauVeto==0;                      }});
#endif 
  analysis_cuts['K'].push_back({ .name="InvmDPhi",.func = []    { return dPhiRazor>=2.8;                  }});

  analysis_cuts['k'].push_back({ .name="1JetAK8",    .func = []    { return nJetAK8>=1;                      }}); // Similar to pt>200, one AK8 jet has pt>200
  analysis_cuts['k'].push_back({ .name="NJet",       .func = []    { return nJet>=4;                          }});
  analysis_cuts['k'].push_back({ .name="HLT",   .func = [this,&d]  { return isData ? d.HLT_AK8PFJet450==1 || d.HLT_PFHT1050==1 : 1; }});
  //analysis_cuts['k'].push_back({ .name="HLT",   .func = [this,&d]  { return d.HLT_AK8PFJet450==1 || d.HLT_PFHT1050==1; }});
  analysis_cuts['k'].push_back({ .name="0Ele",       .func = []    { return nEleVeto==0;                      }});
  analysis_cuts['k'].push_back({ .name="0Mu",        .func = []    { return nMuVeto==0;                       }});
#if USE_ISO_TRK_VETO > 0
  analysis_cuts['k'].push_back({ .name="0Tau",       .func = [&d]  { return d.evt.NIsoTrk==0;                 }});  
#else  
  analysis_cuts['k'].push_back({ .name="0Tau",       .func = []    { return nTauVeto==0;                      }});
#endif 
  analysis_cuts['k'].push_back({ .name="mDPhi",      .func = []    { return dPhiRazor<2.8;                    }});

  // Gen Level Information
  bool isFFsim = TString(sample).Contains("TTJets_madgraphMLM");
  if(isFFsim){ 
    analysis_cuts['b'].push_back({ .name="genW",     .func = []    { return npreWTag > 0;                     }});
    analysis_cuts['b'].push_back({ .name="mWTag",    .func = []    { return nmWTag > 0;                       }});
    analysis_cuts['b'].push_back({ .name="WTag",     .func = []    { return nWTag > 0;                        }});
    analysis_cuts['B'].push_back({ .name="genTop",   .func = []    { return npreTopTag > 0;                   }});
    analysis_cuts['B'].push_back({ .name="mTopTag",  .func = []    { return nmTopTag > 0;                     }});
    analysis_cuts['B'].push_back({ .name="TopTag",   .func = []    { return nTopTag > 0;                      }});
  }
  
  // preselection
  analysis_cuts['P'].push_back({ .name="1JetAK8",    .func = []    { return nJetAK8>=1;                      }}); // Similar to pt>200, one AK8 jet has pt>200
  analysis_cuts['P'].push_back({ .name="NJet",       .func = []    { return nJet>=4;                          }}); // Separate cut, so one can exclude (N-1)
  analysis_cuts['P'].push_back({ .name="MR_R2",    .func = [&d]  { return MR>=800 && R2>=0.08;     }});
  analysis_cuts['P'].push_back({ .name="HLT",   .func = [this,&d]  { return isData ? d.HLT_AK8PFJet450==1 || d.HLT_PFHT1050==1 : 1; }});
  //analysis_cuts['P'].push_back({ .name="HLT",   .func = [this,&d]  { return d.HLT_AK8PFJet450==1 || d.HLT_PFHT1050==1; }});

#if TOP == 0
  // S: Signal region
  analysis_cuts['S'].push_back({ .name="1JetAK8",    .func = []    { return nJetAK8>=1;                      }}); // Similar to pt>200, one AK8 jet has pt>200
  analysis_cuts['S'].push_back({ .name="NJet",       .func = []    { return nJet>=4;                          }}); // Separate cut, so one can exclude (N-1)
  analysis_cuts['S'].push_back({ .name="MR_R2",      .func = [&d]  { return MR>=800 && R2>=0.08;  }});
  analysis_cuts['S'].push_back({ .name="HLT",   .func = [this,&d]  { return isData ? d.HLT_AK8PFJet450==1 || d.HLT_PFHT1050==1 : 1; }});
  //analysis_cuts['S'].push_back({ .name="HLT",   .func = [this,&d]  { return d.HLT_AK8PFJet450==1 || d.HLT_PFHT1050==1; }});
  analysis_cuts['S'].push_back({ .name="0Ele",       .func = []    { return nEleVeto==0;                      }});
  analysis_cuts['S'].push_back({ .name="0Mu",        .func = []    { return nMuVeto==0;                       }});
  //analysis_cuts['S'].push_back({ .name="0IsoTrk",    .func = [&d]  { return d.evt.NIsoTrk==0;                 }});
#if USE_ISO_TRK_VETO > 0
  analysis_cuts['S'].push_back({ .name="0Tau",       .func = [&d]  { return d.evt.NIsoTrk==0;                 }});  
#else  
  analysis_cuts['S'].push_back({ .name="0Tau",       .func = []    { return nTauVeto==0;                      }});
#endif 
  analysis_cuts['S'].push_back({ .name="1b",         .func = []    { return nMediumBTag>=1;                   }});
  analysis_cuts['S'].push_back({ .name="1W",         .func = []    { return nTightWTag>=1;                    }});
  //analysis_cuts['S'].push_back({ .name="mDPhi",      .func = []    { return minDeltaPhi>=0.5;                 }});
  analysis_cuts['S'].push_back({ .name="mDPhi",      .func = []    { return dPhiRazor<2.8;                 }});

  // S': DPhi Control region of Signal region
  analysis_cuts['s'].push_back({ .name="1JetAK8",    .func = []    { return nJetAK8>=1;                      }}); // Similar to pt>200, one AK8 jet has pt>200
  analysis_cuts['s'].push_back({ .name="NJet",       .func = []    { return nJet>=4;                          }}); // Separate cut, so one can exclude (N-1)
  analysis_cuts['s'].push_back({ .name="MR_R2",      .func = [&d]  { return MR>=800 && R2>=0.08;  }});
  analysis_cuts['s'].push_back({ .name="HLT",   .func = [this,&d]  { return isData ? d.HLT_AK8PFJet450==1 || d.HLT_PFHT1050==1 : 1; }});
  //analysis_cuts['s'].push_back({ .name="HLT",   .func = [this,&d]  { return d.HLT_AK8PFJet450==1 || d.HLT_PFHT1050==1; }});
  analysis_cuts['s'].push_back({ .name="0Ele",       .func = []    { return nEleVeto==0;                      }});
  analysis_cuts['s'].push_back({ .name="0Mu",        .func = []    { return nMuVeto==0;                       }});
  //analysis_cuts['s'].push_back({ .name="0IsoTrk",    .func = [&d]  { return d.evt.NIsoTrk==0;                 }});
#if USE_ISO_TRK_VETO > 0
  analysis_cuts['s'].push_back({ .name="0Tau",       .func = [&d]  { return d.evt.NIsoTrk==0;                 }});  
#else  
  analysis_cuts['s'].push_back({ .name="0Tau",       .func = []    { return nTauVeto==0;                      }});
#endif 
  analysis_cuts['s'].push_back({ .name="1b",         .func = []    { return nMediumBTag>=1;                   }});
  analysis_cuts['s'].push_back({ .name="1W",         .func = []    { return nTightWTag>=1;                    }});
  //analysis_cuts['s'].push_back({ .name="InvmDPhi",   .func = []    { return minDeltaPhi<0.5;                  }});
  analysis_cuts['s'].push_back({ .name="InvmDPhi",   .func = []    { return dPhiRazor>=2.8;                  }});

  // Q: QCD enriched control sample
  analysis_cuts['Q'].push_back({ .name="1JetAK8",    .func = []    { return nJetAK8>=1;                      }}); // Similar to pt>200, one AK8 jet has pt>200
  analysis_cuts['Q'].push_back({ .name="NJet",       .func = []    { return nJet>=4;                          }});
  analysis_cuts['Q'].push_back({ .name="MR_R2",      .func = [&d]  { return MR>=800 && R2>=0.08;  }});
  analysis_cuts['Q'].push_back({ .name="HLT",   .func = [this,&d]  { return isData ? d.HLT_AK8PFJet450==1 || d.HLT_PFHT1050==1 : 1; }});
  //analysis_cuts['Q'].push_back({ .name="HLT",   .func = [this,&d]  { return d.HLT_AK8PFJet450==1 || d.HLT_PFHT1050==1; }});
  analysis_cuts['Q'].push_back({ .name="0Ele",       .func = []    { return nEleVeto==0;                      }});
  analysis_cuts['Q'].push_back({ .name="0Mu",        .func = []    { return nMuVeto==0;                       }});
#if USE_ISO_TRK_VETO > 0
  analysis_cuts['Q'].push_back({ .name="0Tau",       .func = [&d]  { return d.evt.NIsoTrk==0;                 }});  
#else  
  analysis_cuts['Q'].push_back({ .name="0Tau",       .func = []    { return nTauVeto==0;                      }});
#endif 
  analysis_cuts['Q'].push_back({ .name="0b",         .func = []    { return nLooseBTag==0;                    }});
  analysis_cuts['Q'].push_back({ .name="1aW",        .func = []    { return nTightWAntiTag>=1;                }});
  //analysis_cuts['Q'].push_back({ .name="InvmDPhi",.func = []    { return minDeltaPhi<0.3;                  }});
  analysis_cuts['Q'].push_back({ .name="InvmDPhi",.func = []    { return dPhiRazor>=2.8;                  }});

  // Q': Dphi Control region of QCD enriched sample
  analysis_cuts['q'].push_back({ .name="1JetAK8",    .func = []    { return nJetAK8>=1;                      }}); // Similar to pt>200, one AK8 jet has pt>200
  analysis_cuts['q'].push_back({ .name="NJet",       .func = []    { return nJet>=4;                          }});
  analysis_cuts['q'].push_back({ .name="MR_R2",      .func = [&d]  { return MR>=800 && R2>=0.08;  }});
  analysis_cuts['q'].push_back({ .name="HLT",   .func = [this,&d]  { return isData ? d.HLT_AK8PFJet450==1 || d.HLT_PFHT1050==1 : 1; }});
  //analysis_cuts['q'].push_back({ .name="HLT",   .func = [this,&d]  { return d.HLT_AK8PFJet450==1 || d.HLT_PFHT1050==1; }});
  analysis_cuts['q'].push_back({ .name="0Ele",       .func = []    { return nEleVeto==0;                      }});
  analysis_cuts['q'].push_back({ .name="0Mu",        .func = []    { return nMuVeto==0;                       }});
#if USE_ISO_TRK_VETO > 0
  analysis_cuts['q'].push_back({ .name="0Tau",       .func = [&d]  { return d.evt.NIsoTrk==0;                 }});  
#else  
  analysis_cuts['q'].push_back({ .name="0Tau",       .func = []    { return nTauVeto==0;                      }});
#endif 
  analysis_cuts['q'].push_back({ .name="0b",         .func = []    { return nLooseBTag==0;                    }});
  analysis_cuts['q'].push_back({ .name="1aW",        .func = []    { return nTightWAntiTag>=1;                }});
  analysis_cuts['q'].push_back({ .name="mDPhi",      .func = []    { return dPhiRazor<2.8;                 }});

  // T: Top enriched control sample
  analysis_cuts['T'].push_back({ .name="1JetAK8",    .func = []    { return nJetAK8>=1;                      }}); // Similar to pt>200, one AK8 jet has pt>200
  analysis_cuts['T'].push_back({ .name="NJet",       .func = []    { return nJet>=4;                          }});
  analysis_cuts['T'].push_back({ .name="MR_R2",      .func = [&d]  { return MR>=800 && R2>=0.08;  }});
  analysis_cuts['T'].push_back({ .name="HLT",   .func = [this,&d]  { return isData ? d.HLT_AK8PFJet450==1 || d.HLT_PFHT1050==1 : 1; }});
  //analysis_cuts['T'].push_back({ .name="HLT",   .func = [this,&d]  { return d.HLT_AK8PFJet450==1 || d.HLT_PFHT1050==1; }});
  analysis_cuts['T'].push_back({ .name="1Lep",       .func = []    { return nLepVeto==1;                      }});
  analysis_cuts['T'].push_back({ .name="1b",         .func = []    { return nMediumBTag>=1;                   }});
  analysis_cuts['T'].push_back({ .name="1W",         .func = []    { return nTightWTag>=1;                    }});
  analysis_cuts['T'].push_back({ .name="mDPhi",      .func = []    { return dPhiRazor<2.8;                 }});
  analysis_cuts['T'].push_back({ .name="MT",         .func = []    { return MT_vetolep<100;                   }});

  // W: W enriched control sample
  analysis_cuts['W'].push_back({ .name="1JetAK8",    .func = []    { return nJetAK8>=1;                      }}); // Similar to pt>200, one AK8 jet has pt>200
  analysis_cuts['W'].push_back({ .name="NJet",       .func = []    { return nJet>=4;                          }});
  analysis_cuts['W'].push_back({ .name="MR_R2",      .func = [&d]  { return MR>=800 && R2>=0.08;  }});
  analysis_cuts['W'].push_back({ .name="HLT",   .func = [this,&d]  { return isData ? d.HLT_AK8PFJet450==1 || d.HLT_PFHT1050==1 : 1; }});
  //analysis_cuts['W'].push_back({ .name="HLT",   .func = [this,&d]  { return d.HLT_AK8PFJet450==1 || d.HLT_PFHT1050==1; }});
  analysis_cuts['W'].push_back({ .name="1Lep",       .func = []    { return nLepVeto==1;                      }});
  analysis_cuts['W'].push_back({ .name="0b",         .func = []    { return nLooseBTag==0;                    }});
  analysis_cuts['W'].push_back({ .name="1mW",        .func = []    { return nWMassTag>=1;                     }});
  analysis_cuts['W'].push_back({ .name="mDPhi",      .func = []    { return dPhiRazor<2.8;                 }});
  analysis_cuts['W'].push_back({ .name="MT",         .func = []    { return MT_vetolep>=30 && MT_vetolep<100; }});

  // L: 1-lepton invisible control sample with veto lepton
  analysis_cuts['L'].push_back({ .name="1JetAK8",    .func = []    { return nJetAK8>=1;                       }});
  analysis_cuts['L'].push_back({ .name="NJet",       .func = []    { return nJet>=4;                          }});
  analysis_cuts['L'].push_back({ .name="MR",         .func = [&d]  { return MR>=800;                    }});
  analysis_cuts['L'].push_back({ .name="R2",         .func = [&d]  { return R2_1vl>=0.08;                     }});
  analysis_cuts['L'].push_back({ .name="HLT",   .func = [this,&d]  { return isData ? d.HLT_AK8PFJet450==1 || d.HLT_PFHT1050==1 : 1; }});
  //analysis_cuts['L'].push_back({ .name="HLT",   .func = [this,&d]  { return d.HLT_AK8PFJet450==1 || d.HLT_PFHT1050==1; }});
  analysis_cuts['L'].push_back({ .name="0b",         .func = []    { return nLooseBTag==0;                    }});
  analysis_cuts['L'].push_back({ .name="1Lep",       .func = []    { return nLepVeto==1;                      }});
  analysis_cuts['L'].push_back({ .name="1mW",        .func = []    { return nWMassTag>=1;                     }});
  analysis_cuts['L'].push_back({ .name="mDPhi",      .func = []    { return dPhiRazor<2.8;                    }});
  analysis_cuts['L'].push_back({ .name="MT",         .func = []    { return MT_vetolep>=30 && MT_vetolep<100; }});

  // Z: Z->ll enriched control sample
  analysis_cuts['Z'].push_back({ .name="1JetAK8",    .func = []    { return nJetAK8>=1;                      }}); // Similar to pt>200, one AK8 jet has pt>200
  analysis_cuts['Z'].push_back({ .name="NJet",       .func = []    { return nJet>=4;                          }}); // Separate cut, so one can exclude (N-1)
  analysis_cuts['Z'].push_back({ .name="MR_R2ll",    .func = [&d]  { return MR>=800 && R2_ll>=0.08;     }});
  analysis_cuts['Z'].push_back({ .name="HLT",   .func = [this,&d]  { return isData ? d.HLT_AK8PFJet450==1 || d.HLT_PFHT1050==1 : 1; }});
  //analysis_cuts['Z'].push_back({ .name="HLT",   .func = [this,&d]  { return d.HLT_AK8PFJet450==1 || d.HLT_PFHT1050==1; }});
  analysis_cuts['Z'].push_back({ .name="2Lep",       .func = []    { return (nEleSelect==2&&nMuVeto==0)||(nMuSelect==2&&nEleVeto==0); }});
  analysis_cuts['Z'].push_back({ .name="OppCharge",  .func = [&d]  { 
				   if (nEleSelect==2) return (d.Electron[iEleSelect[0]].charge + d.Electron[iEleSelect[1]].charge)==0;
				   else if (nMuSelect==2) return (d.Muon[iMuSelect[0]].charge  + d.Muon[iMuSelect[1]].charge)==0;
				   return false;
				 }});
  analysis_cuts['Z'].push_back({ .name="1mW",        .func = []    { return nWMassTag>=1;                     }});
  analysis_cuts['Z'].push_back({ .name="mDPhill",    .func = []    { return dPhiRazor<2.8;              }});
  analysis_cuts['Z'].push_back({ .name="Mll",        .func = []    { return std::abs(M_ll-91.2)<10;           }});

  // G: Photon enriched sample
  analysis_cuts['G'].push_back({ .name="1JetAK8",    .func = []    { return nJetAK8>=1;                       }});
  analysis_cuts['G'].push_back({ .name="1Pho",       .func = []    { return nPhotonSelect==1;                 }     });
  analysis_cuts['G'].push_back({ .name="NJet",       .func = []    { return nJetNoPho>=3;                     }});
  analysis_cuts['G'].push_back({ .name="MR",         .func = [&d]  { return MR_pho>=800;                    }});
  analysis_cuts['G'].push_back({ .name="R2",         .func = [&d]  { return R2_pho>=0.08;                     }});
  analysis_cuts['G'].push_back({ .name="HLT",   .func = [this,&d]  { return isData ? d.HLT_AK8PFJet450==1 || d.HLT_PFHT1050==1 : 1; }});
  //analysis_cuts['G'].push_back({ .name="HLT",   .func = [this,&d]  { return d.HLT_AK8PFJet450==1 || d.HLT_PFHT1050==1; }});
  analysis_cuts['G'].push_back({ .name="0Ele",       .func = []    { return nEleVeto==0;                      }});
  analysis_cuts['G'].push_back({ .name="0Mu",        .func = []    { return nMuVeto==0;                       }});
#if USE_ISO_TRK_VETO > 0
  analysis_cuts['G'].push_back({ .name="0Tau",       .func = [&d]  { return d.evt.NIsoTrk==0;                 }});  
#else  
  analysis_cuts['G'].push_back({ .name="0Tau",       .func = []    { return nTauVeto==0;                      }});
#endif 
  analysis_cuts['G'].push_back({ .name="1mW",        .func = []    { return nWMassTag>=1;                     }});
  analysis_cuts['G'].push_back({ .name="mDPhi",      .func = []    { return dPhiRazor<2.8;                    }});

  // z: Z->ll enriched control sample (with full tag)
  analysis_cuts['z'].push_back({ .name="1JetAK8",    .func = []    { return nJetAK8>=1;                       }}); 
  analysis_cuts['z'].push_back({ .name="NJet",       .func = []    { return nJet>=4;                          }});
  analysis_cuts['z'].push_back({ .name="MR",         .func = [&d]  { return MR>=800;                    }}); 
  analysis_cuts['z'].push_back({ .name="R2ll",       .func = [&d]  { return R2_ll>=0.08;                      }}); 
  analysis_cuts['z'].push_back({ .name="HLT",   .func = [this,&d]  { return isData ? d.HLT_AK8PFJet450==1 || d.HLT_PFHT1050==1 : 1; }}); 
  //analysis_cuts['z'].push_back({ .name="HLT",   .func = [this,&d]  { return d.HLT_AK8PFJet450==1 || d.HLT_PFHT1050==1; }});
  analysis_cuts['z'].push_back({ .name="2Lep",       .func = []    { return (nEleSelect==2&&nMuVeto==0)||(nMuSelect==2&&nEleVeto==0); }});
  analysis_cuts['z'].push_back({ .name="OppCharge",  .func = [&d]  { 
           if (nEleSelect==2) return (d.Electron[iEleSelect[0]].charge + d.Electron[iEleSelect[1]].charge)==0;
           else if (nMuSelect==2) return (d.Muon[iMuSelect[0]].charge + d.Muon[iMuSelect[1]].charge)==0;
           return false;
         }}); 
  analysis_cuts['z'].push_back({ .name="1W",         .func = []    { return nTightWTag>=1;                    }}); 
//analysis_cuts['z'].push_back({ .name="1mW",        .func = []    { return nWMassTag>=1;                     }});
  analysis_cuts['z'].push_back({ .name="mDPhill",    .func = []    { return dPhiRazor<2.8;                    }}); 
  analysis_cuts['z'].push_back({ .name="Mll",        .func = []    { return std::abs(M_ll-91.2)<10;           }}); 

#else

  // t: Boosted Top Signal region
  analysis_cuts['S'].push_back({ .name="1JetAK8",    .func = []    { return nJetAK8>=1;                      }}); 
  analysis_cuts['S'].push_back({ .name="NJet",       .func = []    { return nJet>=3;                          }});
  analysis_cuts['S'].push_back({ .name="MR_R2",      .func = [&d]  { return MR>=800 && R2>=0.08;  }});
  analysis_cuts['S'].push_back({ .name="HLT",   .func = [this,&d]  { return isData ? d.HLT_AK8PFJet450==1 || d.HLT_PFHT1050==1 : 1; }});
  //analysis_cuts['S'].push_back({ .name="HLT",   .func = [this,&d]  { return d.HLT_AK8PFJet450==1 || d.HLT_PFHT1050==1; }});
  analysis_cuts['S'].push_back({ .name="0Ele",       .func = []    { return nEleVeto==0;                      }});
  analysis_cuts['S'].push_back({ .name="0Mu",        .func = []    { return nMuVeto==0;                       }});
#if USE_ISO_TRK_VETO > 0
  analysis_cuts['S'].push_back({ .name="0Tau",       .func = [&d]  { return d.evt.NIsoTrk==0;                 }});  
#else  
  analysis_cuts['S'].push_back({ .name="0Tau",       .func = []    { return nTauVeto==0;                      }});
#endif 
  analysis_cuts['S'].push_back({ .name="1Top",       .func = []    { return nHadTopTag>=1;                    }});
  analysis_cuts['S'].push_back({ .name="mDPhi",      .func = []    { return dPhiRazor<2.8;                 }});

  // a: Boosted Top' Signal region
  analysis_cuts['s'].push_back({ .name="1JetAK8",    .func = []    { return nJetAK8>=1;                      }}); 
  analysis_cuts['s'].push_back({ .name="NJet",       .func = []    { return nJet>=3;                          }});
  analysis_cuts['s'].push_back({ .name="MR_R2",      .func = [&d]  { return MR>=800 && R2>=0.08;  }});
  analysis_cuts['s'].push_back({ .name="HLT",   .func = [this,&d]  { return isData ? d.HLT_AK8PFJet450==1 || d.HLT_PFHT1050==1 : 1; }});
  //analysis_cuts['s'].push_back({ .name="HLT",   .func = [this,&d]  { return d.HLT_AK8PFJet450==1 || d.HLT_PFHT1050==1; }});
  analysis_cuts['s'].push_back({ .name="0Ele",       .func = []    { return nEleVeto==0;                      }});
  analysis_cuts['s'].push_back({ .name="0Mu",        .func = []    { return nMuVeto==0;                       }});
#if USE_ISO_TRK_VETO > 0
  analysis_cuts['s'].push_back({ .name="0Tau",       .func = [&d]  { return d.evt.NIsoTrk==0;                 }});  
#else  
  analysis_cuts['s'].push_back({ .name="0Tau",       .func = []    { return nTauVeto==0;                      }});
#endif 
  analysis_cuts['s'].push_back({ .name="1Top",       .func = []    { return nHadTopTag>=1;                    }});
  //analysis_cuts['s'].push_back({ .name="InvmDPhi",      .func = []    { return minDeltaPhi<0.5;                 }});
  analysis_cuts['s'].push_back({ .name="InvmDPhi",      .func = []    { return dPhiRazor>=2.8;                 }});

  // t: Boosted Top Q region
  analysis_cuts['Q'].push_back({ .name="1JetAK8",    .func = []    { return nJetAK8>=1;                      }}); 
  analysis_cuts['Q'].push_back({ .name="NJet",       .func = []    { return nJet>=3;                          }});
  analysis_cuts['Q'].push_back({ .name="MR_R2",      .func = [&d]  { return MR>=800 && R2>=0.08;  }});
  analysis_cuts['Q'].push_back({ .name="HLT",   .func = [this,&d]  { return isData ? d.HLT_AK8PFJet450==1 || d.HLT_PFHT1050==1 : 1; }});
  //analysis_cuts['Q'].push_back({ .name="HLT",   .func = [this,&d]  { return d.HLT_AK8PFJet450==1 || d.HLT_PFHT1050==1; }});
  analysis_cuts['Q'].push_back({ .name="0Ele",       .func = []    { return nEleVeto==0;                      }});
  analysis_cuts['Q'].push_back({ .name="0Mu",        .func = []    { return nMuVeto==0;                       }});
#if USE_ISO_TRK_VETO > 0
  analysis_cuts['Q'].push_back({ .name="0Tau",       .func = [&d]  { return d.evt.NIsoTrk==0;                 }});  
#else  
  analysis_cuts['Q'].push_back({ .name="0Tau",       .func = []    { return nTauVeto==0;                      }});
#endif 
  analysis_cuts['Q'].push_back({ .name="0b",         .func = []    { return nLooseBTag==0;                    }});
  analysis_cuts['Q'].push_back({ .name="1aTop",       .func = []   { return nHadTop0BAntiTag>=1;                    }});
  //analysis_cuts['Q'].push_back({ .name="mDPhi",      .func = []    { return minDeltaPhi<0.3;                 }});
  analysis_cuts['Q'].push_back({ .name="InvmDPhi",      .func = []    { return dPhiRazor>=2.8;                 }});

  // t: Boosted Top Q' region
  analysis_cuts['q'].push_back({ .name="1JetAK8",    .func = []    { return nJetAK8>=1;                      }}); 
  analysis_cuts['q'].push_back({ .name="NJet",       .func = []    { return nJet>=3;                          }});
  analysis_cuts['q'].push_back({ .name="MR_R2",      .func = [&d]  { return MR>=800 && R2>=0.08;  }});
  analysis_cuts['q'].push_back({ .name="HLT",   .func = [this,&d]  { return isData ? d.HLT_AK8PFJet450==1 || d.HLT_PFHT1050==1 : 1; }});
  //analysis_cuts['q'].push_back({ .name="HLT",   .func = [this,&d]  { return d.HLT_AK8PFJet450==1 || d.HLT_PFHT1050==1; }});
  analysis_cuts['q'].push_back({ .name="0Ele",       .func = []    { return nEleVeto==0;                      }});
  analysis_cuts['q'].push_back({ .name="0Mu",        .func = []    { return nMuVeto==0;                       }});
#if USE_ISO_TRK_VETO > 0
  analysis_cuts['q'].push_back({ .name="0Tau",       .func = [&d]  { return d.evt.NIsoTrk==0;                 }});  
#else  
  analysis_cuts['q'].push_back({ .name="0Tau",       .func = []    { return nTauVeto==0;                      }});
#endif 
  analysis_cuts['q'].push_back({ .name="0b",         .func = []    { return nLooseBTag==0;                    }});
  analysis_cuts['q'].push_back({ .name="1aTop",       .func = []   { return nHadTop0BAntiTag>=1;                    }});
  //analysis_cuts['q'].push_back({ .name="InvmDPhi",      .func = []    { return minDeltaPhi>=0.5;                 }});
  analysis_cuts['q'].push_back({ .name="mDPhi",      .func = []    { return dPhiRazor<2.8;                 }});

  // t: Boosted Top T region
  analysis_cuts['T'].push_back({ .name="1JetAK8",    .func = []    { return nJetAK8>=1;                      }}); 
  analysis_cuts['T'].push_back({ .name="NJet",       .func = []    { return nJet>=3;                          }});
  analysis_cuts['T'].push_back({ .name="MR_R2",      .func = [&d]  { return MR>=800 && R2>=0.08;  }});
  analysis_cuts['T'].push_back({ .name="HLT",   .func = [this,&d]  { return isData ? d.HLT_AK8PFJet450==1 || d.HLT_PFHT1050==1 : 1; }});
  //analysis_cuts['T'].push_back({ .name="HLT",   .func = [this,&d]  { return d.HLT_AK8PFJet450==1 || d.HLT_PFHT1050==1; }});
  analysis_cuts['T'].push_back({ .name="1Lep",       .func = []    { return nLepVeto==1;                      }});
  analysis_cuts['T'].push_back({ .name="1Top",       .func = []   { return nHadTopTag>=1;                    }});
  //analysis_cuts['T'].push_back({ .name="mDPhi",      .func = []    { return minDeltaPhi>=0.5;                 }});
  analysis_cuts['T'].push_back({ .name="mDPhi",      .func = []    { return dPhiRazor<2.8;                 }});
  analysis_cuts['T'].push_back({ .name="MT",         .func = []    { return     MT_vetolep<100;               }});

  // t: Boosted Top W region
  analysis_cuts['W'].push_back({ .name="1JetAK8",    .func = []    { return nJetAK8>=1;                      }}); 
  analysis_cuts['W'].push_back({ .name="NJet",       .func = []    { return nJet>=3;                          }});
  analysis_cuts['W'].push_back({ .name="MR_R2",      .func = [&d]  { return MR>=800 && R2>=0.08;  }});
  analysis_cuts['W'].push_back({ .name="HLT",   .func = [this,&d]  { return isData ? d.HLT_AK8PFJet450==1 || d.HLT_PFHT1050==1 : 1; }});
  //analysis_cuts['W'].push_back({ .name="HLT",   .func = [this,&d]  { return d.HLT_AK8PFJet450==1 || d.HLT_PFHT1050==1; }});
  analysis_cuts['W'].push_back({ .name="1Lep",       .func = []    { return nLepVeto==1;                      }});
  analysis_cuts['W'].push_back({ .name="0b",         .func = []    { return nLooseBTag==0;                    }});
  analysis_cuts['W'].push_back({ .name="1mTop",       .func = []   { return nHadTop0BMassTag>=1;                    }});
  //analysis_cuts['W'].push_back({ .name="mDPhi",      .func = []    { return minDeltaPhi>=0.5;                 }});
  analysis_cuts['W'].push_back({ .name="mDPhi",      .func = []    { return dPhiRazor<2.8;                 }});
  analysis_cuts['W'].push_back({ .name="MT",         .func = []    { return MT_vetolep>=30 && MT_vetolep<100; }});

  // L: 1-lepton invisible control sample with veto lepton
  analysis_cuts['L'].push_back({ .name="1JetAK8",    .func = []    { return nJetAK8>=1;                       }});
  analysis_cuts['L'].push_back({ .name="NJet",       .func = []    { return nJet>=3;                          }});
  analysis_cuts['L'].push_back({ .name="MR",         .func = [&d]  { return MR>=800;                    }});
  analysis_cuts['L'].push_back({ .name="R2",         .func = [&d]  { return R2_1vl>=0.08;                     }});
  analysis_cuts['L'].push_back({ .name="HLT",   .func = [this,&d]  { return isData ? d.HLT_AK8PFJet450==1 || d.HLT_PFHT1050==1 : 1; }});
  //analysis_cuts['L'].push_back({ .name="HLT",   .func = [this,&d]  { return d.HLT_AK8PFJet450==1 || d.HLT_PFHT1050==1; }});
  analysis_cuts['L'].push_back({ .name="1Lep",       .func = []    { return nLepVeto==1;                      }});
  analysis_cuts['L'].push_back({ .name="0b",         .func = []    { return nLooseBTag==0;                    }});
  analysis_cuts['L'].push_back({ .name="1mTop",      .func = []    { return nHadTop0BMassTag>=1;              }});
  analysis_cuts['L'].push_back({ .name="mDPhi",      .func = []    { return dPhiRazor<2.8;                    }});
  analysis_cuts['L'].push_back({ .name="MT",         .func = []    { return MT_vetolep>=30 && MT_vetolep<100; }});

  // Z: Z->ll enriched control sample
  analysis_cuts['Z'].push_back({ .name="1JetAK8",    .func = []    { return nJetAK8>=1;                      }}); 
  analysis_cuts['Z'].push_back({ .name="NJet",       .func = []    { return nJet>=3;                          }});
  analysis_cuts['Z'].push_back({ .name="MR_R2ll",    .func = [&d]  { return MR>=800 && R2_ll>=0.08;     }});
  analysis_cuts['Z'].push_back({ .name="HLT",   .func = [this,&d]  { return isData ? d.HLT_AK8PFJet450==1 || d.HLT_PFHT1050==1 : 1; }});
  //analysis_cuts['Z'].push_back({ .name="HLT",   .func = [this,&d]  { return d.HLT_AK8PFJet450==1 || d.HLT_PFHT1050==1; }});
  analysis_cuts['Z'].push_back({ .name="2Lep",       .func = []    { return (nEleSelect==2&&nMuVeto==0)||(nMuSelect==2&&nEleVeto==0); }});
  analysis_cuts['Z'].push_back({ .name="OppCharge",  .func = [&d]  { 
				   if (nEleSelect==2) return (d.Electron[iEleSelect[0]].charge + d.Electron[iEleSelect[1]].charge)==0;
				   else if (nMuSelect==2) return (d.Muon[iMuSelect[0]].charge + d.Muon[iMuSelect[1]].charge)==0;
				   return false;
				 }});
  analysis_cuts['Z'].push_back({ .name="1mTop",        .func = []    { return nHadTopMassTag>=1;                     }});
  analysis_cuts['Z'].push_back({ .name="mDPhill",    .func = []    { return dPhiRazor<2.8;              }});
  analysis_cuts['Z'].push_back({ .name="Mll",        .func = []    { return std::abs(M_ll-91.2)<10;           }});
  // G: Photon enriched sample
  analysis_cuts['G'].push_back({ .name="1JetAK8",    .func = []    { return nJetAK8>=1;                       }});
  analysis_cuts['G'].push_back({ .name="1Pho",       .func = []    { return nPhotonSelect==1;                 }});
  analysis_cuts['G'].push_back({ .name="NJet",       .func = []    { return nJetNoPho>=3;                     }});
  analysis_cuts['G'].push_back({ .name="MR",         .func = [&d]  { return MR_pho>=800;                      }});
  analysis_cuts['G'].push_back({ .name="R2",         .func = [&d]  { return R2_pho>=0.08;                     }});
  analysis_cuts['G'].push_back({ .name="HLT",   .func = [this,&d]  { return isData ? d.HLT_AK8PFJet450==1 || d.HLT_PFHT1050==1 : 1; }});
  //analysis_cuts['G'].push_back({ .name="HLT",   .func = [this,&d]  { return d.HLT_AK8PFJet450==1 || d.HLT_PFHT1050==1; }});
  analysis_cuts['G'].push_back({ .name="0Ele",       .func = []    { return nEleVeto==0;                      }});
  analysis_cuts['G'].push_back({ .name="0Mu",        .func = []    { return nMuVeto==0;                       }});
#if USE_ISO_TRK_VETO > 0
  analysis_cuts['G'].push_back({ .name="0Tau",       .func = [&d]  { return d.evt.NIsoTrk==0;                 }});  
#else  
  analysis_cuts['G'].push_back({ .name="0Tau",       .func = []    { return nTauVeto==0;                      }});
#endif 
  analysis_cuts['G'].push_back({ .name="1mTop",      .func = []    { return nHadTopMassTag>=1;                }});
//analysis_cuts['G'].push_back({ .name="mDPhi",      .func = []    { return minDeltaPhi_pho>=0.5;             }});
  analysis_cuts['G'].push_back({ .name="mDPhi",      .func = []    { return dPhiRazorNoPho<2.8;               }});

/*
  analysis_cuts['p'].push_back({ .name="1JetAK8",    .func = []    { return nJetAK8>=1;                      }});
  analysis_cuts['p'].push_back({ .name="NJet",       .func = []    { return nJet>=3;                          }});
  analysis_cuts['p'].push_back({ .name="MR_R2",    .func = [&d]  { return MR>=800 && R2_1vl>=0.08;     }});
  analysis_cuts['p'].push_back({ .name="HLT",   .func = [this,&d]  { return isData ? d.HLT_AK8PFJet450==1 || d.HLT_PFHT800==1 || d.HLT_PFHT900==1 : 1; }});
  analysis_cuts['p'].push_back({ .name="1Lep",       .func = []    { return nLepTest==1 && (dR_2D > 0.4 || rel_pT_2D > 25); }});
  analysis_cuts['p'].push_back({ .name="1Top",       .func = []    { return nHadTopTag>=1;                    }});
  analysis_cuts['p'].push_back({ .name="mDPhi",      .func = []    { return dPhiRazor<2.8;                 }});

  analysis_cuts['D'].push_back({ .name="1JetAK8",    .func = []    { return nJetAK8>=1;                      }});
  analysis_cuts['D'].push_back({ .name="NJet",       .func = []    { return nJet>=3;                          }});
  analysis_cuts['D'].push_back({ .name="MR_R2",    .func = [&d]  { return MR>=800 && R2_1vl>=0.08;     }});
  analysis_cuts['D'].push_back({ .name="HLT",   .func = [this,&d]  { return isData ? d.HLT_AK8PFJet450==1 || d.HLT_PFHT800==1 || d.HLT_PFHT900==1 : 1; }});
  analysis_cuts['D'].push_back({ .name="1Lep",       .func = []    { return nLepTest==1 && (dR_2D > 0.4 || rel_pT_2D > 25); }});
  analysis_cuts['D'].push_back({ .name="1Top",       .func = []    { return nHadTopTag>=1;                    }});
  analysis_cuts['D'].push_back({ .name="mDPhi",      .func = []    { return dPhiRazor<2.8;                 }});
  analysis_cuts['D'].push_back({ .name="MT",         .func = []    { return MT_vetolep<100;               }});

  analysis_cuts['d'].push_back({ .name="1JetAK8",    .func = []    { return nJetAK8>=1;                      }}); // Similar to pt>200, one AK8 jet has pt>200
  analysis_cuts['d'].push_back({ .name="NJet",       .func = []    { return nJet>=3;                          }}); // Separate cut, so one can exclude (N-1)
  analysis_cuts['d'].push_back({ .name="MR_R2",      .func = [&d]  { return MR>=800 && R2>=0.08;  }});
  analysis_cuts['d'].push_back({ .name="HLT",   .func = [this,&d]  { return isData ? d.HLT_AK8PFJet450==1 || d.HLT_PFHT800==1 || d.HLT_PFHT900==1 : 1; }});
  analysis_cuts['d'].push_back({ .name="1Lep",       .func = []    { return nLepTest==1 && (dR_2D > 0.4 || rel_pT_2D > 25); }});
  analysis_cuts['d'].push_back({ .name="0b",         .func = []    { return nLooseBTag==0;                    }});
  analysis_cuts['d'].push_back({ .name="1mTop",       .func = []   { return nHadTop0BMassTag>=1;                    }});
  analysis_cuts['d'].push_back({ .name="mDPhi",      .func = []    { return dPhiRazor<2.8;                 }});
  analysis_cuts['d'].push_back({ .name="MT",         .func = []    { return MT_vetolep>=30 && MT_vetolep<100; }});
*/
#endif

  // G-1: Photon enriched sample (G without boosted object)
  analysis_cuts['g'].push_back({ .name="1JetAK8",    .func = []    { return nJetAK8>=1;                       }}); 
  analysis_cuts['g'].push_back({ .name="1Pho",       .func = []    { return nPhotonSelect==1;                 }}); 
  analysis_cuts['g'].push_back({ .name="NJet",       .func = []    { return nJetNoPho>=3;                     }}); 
  analysis_cuts['g'].push_back({ .name="MR",         .func = [&d]  { return MR_pho>=800;                      }}); 
  analysis_cuts['g'].push_back({ .name="R2",         .func = [&d]  { return R2_pho>=0.08;                     }}); 
  analysis_cuts['g'].push_back({ .name="HLT",   .func = [this,&d]  { return isData ? d.HLT_AK8PFJet450==1 || d.HLT_PFHT1050==1 : 1; }}); 
  //analysis_cuts['g'].push_back({ .name="HLT",   .func = [this,&d]  { return d.HLT_AK8PFJet450==1 || d.HLT_PFHT1050==1; }});
  analysis_cuts['g'].push_back({ .name="0Ele",       .func = []    { return nEleVeto==0;                      }}); 
  analysis_cuts['g'].push_back({ .name="0Mu",        .func = []    { return nMuVeto==0;                       }}); 
#if USE_ISO_TRK_VETO > 0
  analysis_cuts['g'].push_back({ .name="0Tau",       .func = [&d]  { return d.evt.NIsoTrk==0;                 }}); 
#else
  analysis_cuts['g'].push_back({ .name="0Tau",       .func = []    { return nTauVeto==0;                      }}); 
#endif
  analysis_cuts['g'].push_back({ .name="mDPhi",      .func = []    { return dPhiRazorNoPho<2.8;               }}); 

  // w: Inclusive Razor-like W enriched region
  analysis_cuts['w'].push_back({ .name="1JetAK8",    .func = []    { return nJetAK8>=1;                       }}); 
  analysis_cuts['w'].push_back({ .name="MR",         .func = [&d]  { return MR>=300;                    }}); 
  analysis_cuts['w'].push_back({ .name="R2",         .func = [&d]  { return R2>=0.15;                   }}); 
  analysis_cuts['w'].push_back({ .name="HLT",   .func = [this,&d]  { return isData ? d.HLT_AK8PFJet450==1 || d.HLT_PFHT1050==1 : 1; }}); 
  //analysis_cuts['w'].push_back({ .name="HLT",   .func = [this,&d]  { return d.HLT_AK8PFJet450==1 || d.HLT_PFHT1050==1; }});
  analysis_cuts['w'].push_back({ .name="1Lep",       .func = []    { return nLepSelect==1;                    }}); 
  analysis_cuts['w'].push_back({ .name="MET",        .func = [&d]  { return d.MET_pt>=30;                  }}); 
  analysis_cuts['w'].push_back({ .name="MT",         .func = []    { return MT>=30 && MT<100;                 }}); 
  analysis_cuts['w'].push_back({ .name="0b",         .func = []    { return nLooseBTag==0;                    }}); 

  // F: Fake rate measurement region
  analysis_cuts['F'].push_back({ .name="1JetAK8",    .func = []    { return nJetAK8>=1;                       }}); 
  analysis_cuts['F'].push_back({ .name="MR",         .func = [&d]  { return MR>=800;                    }}); 
  analysis_cuts['F'].push_back({ .name="NJet",       .func = []    { return nJet>=3;                          }}); 
  analysis_cuts['F'].push_back({ .name="HLT",   .func = [this,&d]  { return isData ? d.HLT_AK8PFJet450==1 || d.HLT_PFHT1050==1 : 1; }}); 
  //analysis_cuts['F'].push_back({ .name="HLT",   .func = [this,&d]  { return d.HLT_AK8PFJet450==1 || d.HLT_PFHT1050==1; }});
  analysis_cuts['F'].push_back({ .name="0Ele",       .func = []    { return nEleVeto==0;                      }}); 
  analysis_cuts['F'].push_back({ .name="0Mu",        .func = []    { return nMuVeto==0;                       }}); 
#if USE_ISO_TRK_VETO > 0
  analysis_cuts['F'].push_back({ .name="0Tau",       .func = [&d]  { return d.evt.NIsoTrk==0;                 }}); 
#else
  analysis_cuts['F'].push_back({ .name="0Tau",       .func = []    { return nTauVeto==0;                      }}); 
#endif
  analysis_cuts['F'].push_back({ .name="0b",         .func = []    { return nLooseBTag==0;                    }}); 
//analysis_cuts['F'].push_back({ .name="InvmDPhi0p3",.func = []    { return minDeltaPhi<0.3;                  }});
  analysis_cuts['F'].push_back({ .name="InvmDPhi0p3",.func = []    { return dPhiRazor>=2.8;                   }}); 

  // F: F+1b
  analysis_cuts['f'].push_back({ .name="1JetAK8",    .func = []    { return nJetAK8>=1;                       }}); 
  analysis_cuts['f'].push_back({ .name="MR",         .func = [&d]  { return MR>=800;                    }}); 
  analysis_cuts['f'].push_back({ .name="NJet",       .func = []    { return nJet>=3;                          }}); 
  analysis_cuts['f'].push_back({ .name="HLT",   .func = [this,&d]  { return isData ? d.HLT_AK8PFJet450==1 || d.HLT_PFHT1050==1 : 1; }}); 
  //analysis_cuts['f'].push_back({ .name="HLT",   .func = [this,&d]  { return d.HLT_AK8PFJet450==1 || d.HLT_PFHT1050==1; }});
  analysis_cuts['f'].push_back({ .name="0Ele",       .func = []    { return nEleVeto==0;                      }}); 
  analysis_cuts['f'].push_back({ .name="0Mu",        .func = []    { return nMuVeto==0;                       }}); 
#if USE_ISO_TRK_VETO > 0
  analysis_cuts['f'].push_back({ .name="0Tau",       .func = [&d]  { return d.evt.NIsoTrk==0;                 }}); 
#else
  analysis_cuts['f'].push_back({ .name="0Tau",       .func = []    { return nTauVeto==0;                      }}); 
#endif
  analysis_cuts['f'].push_back({ .name="1b",         .func = []    { return nMediumBTag>=1;                   }}); 
//analysis_cuts['f'].push_back({ .name="InvmDPhi0p3",.func = []    { return minDeltaPhi<0.3;                  }});
  analysis_cuts['f'].push_back({ .name="InvmDPhi0p3",.func = []    { return dPhiRazor>=2.8;                   }}); 

  // H: HT>=1TeV+1b
  analysis_cuts['H'].push_back({ .name="1JetAK8",    .func = []    { return nJetAK8>=1;                       }}); 
  analysis_cuts['H'].push_back({ .name="NJet",       .func = []    { return nJet>=3;                          }}); 
  analysis_cuts['H'].push_back({ .name="HLT",   .func = [this,&d]  { return isData ? d.HLT_AK8PFJet450==1 || d.HLT_PFHT1050==1 : 1; }}); 
  //analysis_cuts['H'].push_back({ .name="HLT",   .func = [this,&d]  { return d.HLT_AK8PFJet450==1 || d.HLT_PFHT1050==1; }});
  analysis_cuts['H'].push_back({ .name="0Ele",       .func = []    { return nEleVeto==0;                      }}); 
  analysis_cuts['H'].push_back({ .name="0Mu",        .func = []    { return nMuVeto==0;                       }}); 
#if USE_ISO_TRK_VETO > 0
  analysis_cuts['H'].push_back({ .name="0Tau",       .func = [&d]  { return d.evt.NIsoTrk==0;                 }}); 
#else
  analysis_cuts['H'].push_back({ .name="0Tau",       .func = []    { return nTauVeto==0;                      }});
#endif
  analysis_cuts['H'].push_back({ .name="1b",         .func = []    { return nMediumBTag>=1;                   }});
  analysis_cuts['H'].push_back({ .name="HT",         .func = []    { return AK4_Ht>=1000;                     }});
}

//____________________________________________________
//          Analysis Specific Scale factors
//    (Defined for each search region separately)

void
Analysis::apply_scale_factors(eventBuffer& data, const unsigned int& s, const std::vector<std::vector<double> >& nSigmaSFs)
{
  bool isFastSim = TString(sample).Contains("FastSim");
  size_t i = 0;

  // Don't forget to specify the total number of sigmas you use in settings_*.h !

  // Electron SFs (5 sigmas - reco, fullsim id/iso, fastsim)
  double sf_ele_veto, sf_ele_loose, sf_ele_medium;
  std::tie(sf_ele_veto, sf_ele_loose, sf_ele_medium) = calc_ele_sf(data, nSigmaSFs[i][s], nSigmaSFs[i+1][s], nSigmaSFs[i+2][s], nSigmaSFs[i+3][s], isFastSim);
  i+=4;

  // Muon SFs (3 sigmas - tracking, fullsim, fastsim)
  double sf_muon_veto, sf_muon_loose, sf_muon_medium;
  std::tie(sf_muon_veto, sf_muon_loose, sf_muon_medium) =  calc_muon_sf(data, nSigmaSFs[i][s], nSigmaSFs[i+1][s], nSigmaSFs[i+2][s], isFastSim);
  i+=3;

  // b tagging SFs (2 sigma - fullsim, fastsim)
  std::pair<double, double> sf_btag = calc_b_tagging_sf(data, nSigmaSFs[i][s], nSigmaSFs[i+1][s], isFastSim);
#if TOP == 0
  double sf_btag_loose = sf_btag.first, sf_btag_medium = sf_btag.second;
#else
  double sf_btag_loose = sf_btag.first;//, sf_btag_medium = sf_btag.second;
#endif
  i+=2;

#if TOP == 0
  // W tagging SF  (4 sigma - fullsim, fastsim, mistag, mistag fastsim)
  double sf_w = calc_w_tagging_sf(data, nSigmaSFs[i][s], nSigmaSFs[i+1][s], nSigmaSFs[i+2][s], nSigmaSFs[i+3][s], isFastSim);
  // fake W tagging SFs (2 sigma)
  double sf_fake_mW = calc_fake_w_mass_tagging_sf(data, nSigmaSFs[i+4][s]);
  double sf_fake_aW = calc_fake_w_anti_tagging_sf(data, nSigmaSFs[i+5][s]);
#endif
  i+=6;

#if TOP != 0
  // top tagging SF (4 sigma - fullsim, fastsim, mistag, mistag fastsim)
  double sf_top = calc_top_tagging_sf(data, nSigmaSFs[i][s], nSigmaSFs[i+1][s], nSigmaSFs[i+2][s], nSigmaSFs[i+3][s], isFastSim);
  // fake top tagging SFs (3 sigmas)
  double sf_fake_0b_mTop = calc_fake_top_0b_mass_tagging_sf(data, nSigmaSFs[i+4][s]);
  double sf_fake_MTop = calc_fake_top_mass_tagging_sf(data, nSigmaSFs[i+5][s]);
  double sf_fake_aTop = calc_fake_top_anti_tagging_sf(data, nSigmaSFs[i+6][s]);
#endif
  i+=7;

  // Select scale factors to use
  for (auto& sf : scale_factors) sf.second.clear();

#if TOP == 0

  scale_factors['S'].push_back(sf_ele_veto);
  scale_factors['S'].push_back(sf_muon_veto);
  scale_factors['S'].push_back(sf_btag_medium);
  scale_factors['S'].push_back(sf_w);

  scale_factors['s'] = scale_factors['S'];

  scale_factors['Q'].push_back(sf_ele_veto);
  scale_factors['Q'].push_back(sf_muon_veto);
  scale_factors['Q'].push_back(sf_btag_loose);
  scale_factors['Q'].push_back(sf_fake_aW);

  scale_factors['q'] = scale_factors['Q'];

  scale_factors['T'].push_back(sf_ele_veto);
  scale_factors['T'].push_back(sf_muon_veto);
  scale_factors['T'].push_back(sf_btag_medium);
  scale_factors['T'].push_back(sf_w);

  scale_factors['W'].push_back(sf_ele_veto);
  scale_factors['W'].push_back(sf_muon_veto);
  scale_factors['W'].push_back(sf_btag_loose);
  scale_factors['W'].push_back(sf_fake_mW);

  scale_factors['L'] = scale_factors['W'];

  scale_factors['Z'].push_back(sf_ele_medium);
  scale_factors['Z'].push_back(sf_muon_medium);
  scale_factors['Z'].push_back(sf_fake_mW);

  scale_factors['G'].push_back(sf_ele_veto);
  scale_factors['G'].push_back(sf_muon_veto);
  scale_factors['G'].push_back(sf_fake_mW);

  scale_factors['z'].push_back(sf_ele_medium);
  scale_factors['z'].push_back(sf_muon_medium);
  scale_factors['z'].push_back(sf_w);

#else

  // Top Analysis
  scale_factors['S'].push_back(sf_ele_veto);
  scale_factors['S'].push_back(sf_muon_veto);
  scale_factors['S'].push_back(sf_top);

  scale_factors['s'] = scale_factors['S'];

  scale_factors['Q'].push_back(sf_ele_veto);
  scale_factors['Q'].push_back(sf_muon_veto);
  scale_factors['Q'].push_back(sf_fake_aTop);
  scale_factors['Q'].push_back(sf_btag_loose);

  scale_factors['q'] = scale_factors['Q'];

  scale_factors['T'].push_back(sf_ele_veto);
  scale_factors['T'].push_back(sf_muon_veto);
  scale_factors['T'].push_back(sf_top);

  scale_factors['W'].push_back(sf_ele_veto);
  scale_factors['W'].push_back(sf_muon_veto);
  scale_factors['W'].push_back(sf_fake_0b_mTop);
  scale_factors['W'].push_back(sf_btag_loose);

  scale_factors['G'].push_back(sf_ele_veto);
  scale_factors['G'].push_back(sf_muon_veto);
  scale_factors['G'].push_back(sf_fake_MTop);

  scale_factors['Z'].push_back(sf_ele_medium);
  scale_factors['Z'].push_back(sf_muon_medium);
  scale_factors['Z'].push_back(sf_fake_MTop);

  scale_factors['L'] = scale_factors['W'];

/*
  scale_factors['p'].push_back(sf_ele_veto);
  scale_factors['p'].push_back(sf_muon_veto);
  scale_factors['p'].push_back(sf_top);
  scale_factors['D'].push_back(sf_ele_veto);
  scale_factors['D'].push_back(sf_muon_veto);
  scale_factors['D'].push_back(sf_top);
  scale_factors['d'].push_back(sf_ele_veto);
  scale_factors['d'].push_back(sf_muon_veto);
  scale_factors['d'].push_back(sf_btag_loose);
  scale_factors['d'].push_back(sf_fake_0b_mTop);
*/
#endif

  scale_factors['K'].push_back(sf_ele_veto);
  scale_factors['K'].push_back(sf_muon_veto);
  scale_factors['K'].push_back(sf_btag_loose);
  scale_factors['k'].push_back(sf_ele_veto);
  scale_factors['k'].push_back(sf_muon_veto);

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
