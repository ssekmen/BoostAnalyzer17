#include "TLorentzVector.h"
#include "TMath.h"
#include "include/AnalysisBase.h"



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
         std::abs(data.FatJet[i].eta)  <  JET_AK8_ETA_CUT ) {
      NJetAK8++;
    }
  }
  if (!(NJetAK8>=1)) return 0;
  //if (!(R2>=0.04)) return 0;
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

// {
  analysis_cuts.clear();

  // Define here cuts that are include in all Signal/Control regions
  // MET Filters, etc. are already applied in AnalysisBase.h, See baseline_cuts


  // preselection
  analysis_cuts['P'].push_back({ .name="1JetAK8",    .func = []    { return nJetAK8>=1;                      }}); // Similar to pt>200, one AK8 jet has pt>200
  analysis_cuts['P'].push_back({ .name="NJet",       .func = []    { return nJet>=3;                          }}); // Separate cut, so one can exclude (N-1)
  analysis_cuts['P'].push_back({ .name="MR_R2",    .func = [&d]  { return MR>=800 && R2>=0.08;     }});
  analysis_cuts['P'].push_back({ .name="HLT",   .func = [this,&d]  { return isData ? d.HLT_PFHT1050==1 || d.HLT_AK8PFHT800_TrimMass50==1 || d.HLT_PFHT500_PFMET100_PFMHT100_IDTight==1 || d.HLT_AK8PFJet450==1 || d.HLT_AK8PFJet400_TrimMass30==1 : 1; }});
  //analysis_cuts['P'].push_back({ .name="HLT",   .func = [this,&d]  { return isData ? d.HLT_PFHT1050==1 || d.HLT_AK8PFHT800_TrimMass50==1 || d.HLT_PFHT500_PFMET100_PFMHT100_IDTight==1 || d.HLT_AK8PFJet450==1 || d.HLT_AK8PFJet400_TrimMass30==1 : 1; }});

#if TOP == 0
  // S: Signal region
  analysis_cuts['S'].push_back({ .name="1JetAK8",    .func = []    { return nJetAK8>=1;                      }}); // Similar to pt>200, one AK8 jet has pt>200
  analysis_cuts['S'].push_back({ .name="NJet",       .func = []    { return nJet>=3;                          }}); // Separate cut, so one can exclude (N-1)
  analysis_cuts['S'].push_back({ .name="MR_R2",      .func = [&d]  { return MR>=800 && R2>=0.08;  }});
  analysis_cuts['S'].push_back({ .name="HLT",   .func = [this,&d]  { return isData ? d.HLT_PFHT1050==1 || d.HLT_AK8PFHT800_TrimMass50==1 || d.HLT_PFHT500_PFMET100_PFMHT100_IDTight==1 || d.HLT_AK8PFJet450==1 || d.HLT_AK8PFJet400_TrimMass30==1 : 1; }});
  //analysis_cuts['S'].push_back({ .name="HLT",   .func = [this,&d]  { return d.HLT_PFHT1050==1 || d.HLT_AK8PFHT800_TrimMass50==1 || d.HLT_PFHT500_PFMET100_PFMHT100_IDTight==1 || d.HLT_AK8PFJet450==1 || d.HLT_AK8PFJet400_TrimMass30==1; }});
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
  analysis_cuts['s'].push_back({ .name="NJet",       .func = []    { return nJet>=3;                          }}); // Separate cut, so one can exclude (N-1)
  analysis_cuts['s'].push_back({ .name="MR_R2",      .func = [&d]  { return MR>=800 && R2>=0.08;  }});
  analysis_cuts['s'].push_back({ .name="HLT",   .func = [this,&d]  { return isData ? d.HLT_PFHT1050==1 || d.HLT_AK8PFHT800_TrimMass50==1 || d.HLT_PFHT500_PFMET100_PFMHT100_IDTight==1 || d.HLT_AK8PFJet450==1 || d.HLT_AK8PFJet400_TrimMass30==1 : 1; }});
  //analysis_cuts['s'].push_back({ .name="HLT",   .func = [this,&d]  { return d.HLT_PFHT1050==1 || d.HLT_AK8PFHT800_TrimMass50==1 || d.HLT_PFHT500_PFMET100_PFMHT100_IDTight==1 || d.HLT_AK8PFJet450==1 || d.HLT_AK8PFJet400_TrimMass30==1; }});
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
  analysis_cuts['Q'].push_back({ .name="NJet",       .func = []    { return nJet>=3;                          }});
  analysis_cuts['Q'].push_back({ .name="MR_R2",      .func = [&d]  { return MR>=800 && R2>=0.08;  }});
  analysis_cuts['Q'].push_back({ .name="HLT",   .func = [this,&d]  { return isData ? d.HLT_PFHT1050==1 || d.HLT_AK8PFHT800_TrimMass50==1 || d.HLT_PFHT500_PFMET100_PFMHT100_IDTight==1 || d.HLT_AK8PFJet450==1 || d.HLT_AK8PFJet400_TrimMass30==1 : 1; }});
  //analysis_cuts['Q'].push_back({ .name="HLT",   .func = [this,&d]  { return d.HLT_PFHT1050==1 || d.HLT_AK8PFHT800_TrimMass50==1 || d.HLT_PFHT500_PFMET100_PFMHT100_IDTight==1 || d.HLT_AK8PFJet450==1 || d.HLT_AK8PFJet400_TrimMass30==1; }});
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
  analysis_cuts['q'].push_back({ .name="NJet",       .func = []    { return nJet>=3;                          }});
  analysis_cuts['q'].push_back({ .name="MR_R2",      .func = [&d]  { return MR>=800 && R2>=0.08;  }});
  analysis_cuts['q'].push_back({ .name="HLT",   .func = [this,&d]  { return isData ? d.HLT_PFHT1050==1 || d.HLT_AK8PFHT800_TrimMass50==1 || d.HLT_PFHT500_PFMET100_PFMHT100_IDTight==1 || d.HLT_AK8PFJet450==1 || d.HLT_AK8PFJet400_TrimMass30==1 : 1; }});
  //analysis_cuts['q'].push_back({ .name="HLT",   .func = [this,&d]  { return d.HLT_PFHT1050==1 || d.HLT_AK8PFHT800_TrimMass50==1 || d.HLT_PFHT500_PFMET100_PFMHT100_IDTight==1 || d.HLT_AK8PFJet450==1 || d.HLT_AK8PFJet400_TrimMass30==1; }});
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
  analysis_cuts['T'].push_back({ .name="NJet",       .func = []    { return nJet>=3;                          }});
  analysis_cuts['T'].push_back({ .name="MR_R2",      .func = [&d]  { return MR>=800 && R2>=0.08;  }});
  analysis_cuts['T'].push_back({ .name="HLT",   .func = [this,&d]  { return isData ? d.HLT_PFHT1050==1 || d.HLT_AK8PFHT800_TrimMass50==1 || d.HLT_PFHT500_PFMET100_PFMHT100_IDTight==1 || d.HLT_AK8PFJet450==1 || d.HLT_AK8PFJet400_TrimMass30==1 : 1; }});
  //analysis_cuts['T'].push_back({ .name="HLT",   .func = [this,&d]  { return d.HLT_PFHT1050==1 || d.HLT_AK8PFHT800_TrimMass50==1 || d.HLT_PFHT500_PFMET100_PFMHT100_IDTight==1 || d.HLT_AK8PFJet450==1 || d.HLT_AK8PFJet400_TrimMass30==1; }});
  analysis_cuts['T'].push_back({ .name="1Lep",       .func = []    { return nLepVeto==1;                      }});
  analysis_cuts['T'].push_back({ .name="1b",         .func = []    { return nMediumBTag>=1;                   }});
  analysis_cuts['T'].push_back({ .name="1W",         .func = []    { return nTightWTag>=1;                    }});
  analysis_cuts['T'].push_back({ .name="mDPhi",      .func = []    { return dPhiRazor<2.8;                 }});
  analysis_cuts['T'].push_back({ .name="MT",         .func = []    { return MT_vetolep<100;                   }});

  // W: W enriched control sample
  analysis_cuts['W'].push_back({ .name="1JetAK8",    .func = []    { return nJetAK8>=1;                      }}); // Similar to pt>200, one AK8 jet has pt>200
  analysis_cuts['W'].push_back({ .name="NJet",       .func = []    { return nJet>=3;                          }});
  analysis_cuts['W'].push_back({ .name="MR_R2",      .func = [&d]  { return MR>=800 && R2>=0.08;  }});
  analysis_cuts['W'].push_back({ .name="HLT",   .func = [this,&d]  { return isData ? d.HLT_PFHT1050==1 || d.HLT_AK8PFHT800_TrimMass50==1 || d.HLT_PFHT500_PFMET100_PFMHT100_IDTight==1 || d.HLT_AK8PFJet450==1 || d.HLT_AK8PFJet400_TrimMass30==1 : 1; }});
  //analysis_cuts['W'].push_back({ .name="HLT",   .func = [this,&d]  { return d.HLT_PFHT1050==1 || d.HLT_AK8PFHT800_TrimMass50==1 || d.HLT_PFHT500_PFMET100_PFMHT100_IDTight==1 || d.HLT_AK8PFJet450==1 || d.HLT_AK8PFJet400_TrimMass30==1; }});
  analysis_cuts['W'].push_back({ .name="1Lep",       .func = []    { return nLepVeto==1;                      }});
  analysis_cuts['W'].push_back({ .name="0b",         .func = []    { return nLooseBTag==0;                    }});
  analysis_cuts['W'].push_back({ .name="1mW",        .func = []    { return nWMassTag>=1;                     }});
  analysis_cuts['W'].push_back({ .name="mDPhi",      .func = []    { return dPhiRazor<2.8;                 }});
  analysis_cuts['W'].push_back({ .name="MT",         .func = []    { return MT_vetolep>=30 && MT_vetolep<100; }});

  // L: 1-lepton invisible control sample with veto lepton
  analysis_cuts['L'].push_back({ .name="1JetAK8",    .func = []    { return nJetAK8>=1;                       }});
  analysis_cuts['L'].push_back({ .name="NJet",       .func = []    { return nJet>=3;                          }});
  analysis_cuts['L'].push_back({ .name="MR",         .func = [&d]  { return MR>=800;                    }});
  analysis_cuts['L'].push_back({ .name="R2",         .func = [&d]  { return R2_1vl>=0.08;                     }});
  analysis_cuts['L'].push_back({ .name="HLT",   .func = [this,&d]  { return isData ? d.HLT_PFHT1050==1 || d.HLT_AK8PFHT800_TrimMass50==1 || d.HLT_PFHT500_PFMET100_PFMHT100_IDTight==1 || d.HLT_AK8PFJet450==1 || d.HLT_AK8PFJet400_TrimMass30==1 : 1; }});
  //analysis_cuts['L'].push_back({ .name="HLT",   .func = [this,&d]  { return d.HLT_PFHT1050==1 || d.HLT_AK8PFHT800_TrimMass50==1 || d.HLT_PFHT500_PFMET100_PFMHT100_IDTight==1 || d.HLT_AK8PFJet450==1 || d.HLT_AK8PFJet400_TrimMass30==1; }});
  analysis_cuts['L'].push_back({ .name="0b",         .func = []    { return nLooseBTag==0;                    }});
  analysis_cuts['L'].push_back({ .name="1Lep",       .func = []    { return nLepVeto==1;                      }});
  analysis_cuts['L'].push_back({ .name="1mW",        .func = []    { return nWMassTag>=1;                     }});
  analysis_cuts['L'].push_back({ .name="mDPhi",      .func = []    { return dPhiRazor<2.8;                    }});
  analysis_cuts['L'].push_back({ .name="MT",         .func = []    { return MT_vetolep>=30 && MT_vetolep<100; }});

  // Z: Z->ll enriched control sample
  analysis_cuts['Z'].push_back({ .name="1JetAK8",    .func = []    { return nJetAK8>=1;                      }}); // Similar to pt>200, one AK8 jet has pt>200
  analysis_cuts['Z'].push_back({ .name="NJet",       .func = []    { return nJet>=3;                          }}); // Separate cut, so one can exclude (N-1)
  analysis_cuts['Z'].push_back({ .name="MR_R2ll",    .func = [&d]  { return MR>=800 && R2_ll>=0.08;     }});
  analysis_cuts['Z'].push_back({ .name="HLT",   .func = [this,&d]  { return isData ? d.HLT_PFHT1050==1 || d.HLT_AK8PFHT800_TrimMass50==1 || d.HLT_PFHT500_PFMET100_PFMHT100_IDTight==1 || d.HLT_AK8PFJet450==1 || d.HLT_AK8PFJet400_TrimMass30==1 : 1; }});
  //analysis_cuts['Z'].push_back({ .name="HLT",   .func = [this,&d]  { return d.HLT_PFHT1050==1 || d.HLT_AK8PFHT800_TrimMass50==1 || d.HLT_PFHT500_PFMET100_PFMHT100_IDTight==1 || d.HLT_AK8PFJet450==1 || d.HLT_AK8PFJet400_TrimMass30==1; }});
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
  analysis_cuts['G'].push_back({ .name="HLT",   .func = [this,&d]  { return isData ? d.HLT_PFHT1050==1 || d.HLT_AK8PFHT800_TrimMass50==1 || d.HLT_PFHT500_PFMET100_PFMHT100_IDTight==1 || d.HLT_AK8PFJet450==1 || d.HLT_AK8PFJet400_TrimMass30==1 : 1; }});
  //analysis_cuts['G'].push_back({ .name="HLT",   .func = [this,&d]  { return d.HLT_PFHT1050==1 || d.HLT_AK8PFHT800_TrimMass50==1 || d.HLT_PFHT500_PFMET100_PFMHT100_IDTight==1 || d.HLT_AK8PFJet450==1 || d.HLT_AK8PFJet400_TrimMass30==1; }});
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
  analysis_cuts['z'].push_back({ .name="NJet",       .func = []    { return nJet>=3;                          }});
  analysis_cuts['z'].push_back({ .name="MR",         .func = [&d]  { return MR>=800;                    }});
  analysis_cuts['z'].push_back({ .name="R2ll",       .func = [&d]  { return R2_ll>=0.08;                      }});
  analysis_cuts['z'].push_back({ .name="HLT",   .func = [this,&d]  { return isData ? d.HLT_PFHT1050==1 || d.HLT_AK8PFHT800_TrimMass50==1 || d.HLT_PFHT500_PFMET100_PFMHT100_IDTight==1 || d.HLT_AK8PFJet450==1 || d.HLT_AK8PFJet400_TrimMass30==1 : 1; }});
  //analysis_cuts['z'].push_back({ .name="HLT",   .func = [this,&d]  { return d.HLT_PFHT1050==1 || d.HLT_AK8PFHT800_TrimMass50==1 || d.HLT_PFHT500_PFMET100_PFMHT100_IDTight==1 || d.HLT_AK8PFJet450==1 || d.HLT_AK8PFJet400_TrimMass30==1; }});
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
  analysis_cuts['S'].push_back({ .name="HLT",   .func = [this,&d]  { return isData ? d.HLT_PFHT1050==1 || d.HLT_AK8PFHT800_TrimMass50==1 || d.HLT_PFHT500_PFMET100_PFMHT100_IDTight==1 || d.HLT_AK8PFJet450==1 || d.HLT_AK8PFJet400_TrimMass30==1 : 1; }});
  //analysis_cuts['S'].push_back({ .name="HLT",   .func = [this,&d]  { return d.HLT_PFHT1050==1 || d.HLT_AK8PFHT800_TrimMass50==1 || d.HLT_PFHT500_PFMET100_PFMHT100_IDTight==1 || d.HLT_AK8PFJet450==1 || d.HLT_AK8PFJet400_TrimMass30==1; }});
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
  analysis_cuts['s'].push_back({ .name="HLT",   .func = [this,&d]  { return isData ? d.HLT_PFHT1050==1 || d.HLT_AK8PFHT800_TrimMass50==1 || d.HLT_PFHT500_PFMET100_PFMHT100_IDTight==1 || d.HLT_AK8PFJet450==1 || d.HLT_AK8PFJet400_TrimMass30==1 : 1; }});
  //analysis_cuts['s'].push_back({ .name="HLT",   .func = [this,&d]  { return d.HLT_PFHT1050==1 || d.HLT_AK8PFHT800_TrimMass50==1 || d.HLT_PFHT500_PFMET100_PFMHT100_IDTight==1 || d.HLT_AK8PFJet450==1 || d.HLT_AK8PFJet400_TrimMass30==1; }});
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
  analysis_cuts['Q'].push_back({ .name="HLT",   .func = [this,&d]  { return isData ? d.HLT_PFHT1050==1 || d.HLT_AK8PFHT800_TrimMass50==1 || d.HLT_PFHT500_PFMET100_PFMHT100_IDTight==1 || d.HLT_AK8PFJet450==1 || d.HLT_AK8PFJet400_TrimMass30==1 : 1; }});
  //analysis_cuts['Q'].push_back({ .name="HLT",   .func = [this,&d]  { return d.HLT_PFHT1050==1 || d.HLT_AK8PFHT800_TrimMass50==1 || d.HLT_PFHT500_PFMET100_PFMHT100_IDTight==1 || d.HLT_AK8PFJet450==1 || d.HLT_AK8PFJet400_TrimMass30==1; }});
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
  analysis_cuts['q'].push_back({ .name="HLT",   .func = [this,&d]  { return isData ? d.HLT_PFHT1050==1 || d.HLT_AK8PFHT800_TrimMass50==1 || d.HLT_PFHT500_PFMET100_PFMHT100_IDTight==1 || d.HLT_AK8PFJet450==1 || d.HLT_AK8PFJet400_TrimMass30==1 : 1; }});
  //analysis_cuts['q'].push_back({ .name="HLT",   .func = [this,&d]  { return d.HLT_PFHT1050==1 || d.HLT_AK8PFHT800_TrimMass50==1 || d.HLT_PFHT500_PFMET100_PFMHT100_IDTight==1 || d.HLT_AK8PFJet450==1 || d.HLT_AK8PFJet400_TrimMass30==1; }});
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
  analysis_cuts['T'].push_back({ .name="HLT",   .func = [this,&d]  { return isData ? d.HLT_PFHT1050==1 || d.HLT_AK8PFHT800_TrimMass50==1 || d.HLT_PFHT500_PFMET100_PFMHT100_IDTight==1 || d.HLT_AK8PFJet450==1 || d.HLT_AK8PFJet400_TrimMass30==1 : 1; }});
  //analysis_cuts['T'].push_back({ .name="HLT",   .func = [this,&d]  { return d.HLT_PFHT1050==1 || d.HLT_AK8PFHT800_TrimMass50==1 || d.HLT_PFHT500_PFMET100_PFMHT100_IDTight==1 || d.HLT_AK8PFJet450==1 || d.HLT_AK8PFJet400_TrimMass30==1; }});
  analysis_cuts['T'].push_back({ .name="1Lep",       .func = []    { return nLepVeto==1;                      }});
  analysis_cuts['T'].push_back({ .name="1Top",       .func = []   { return nHadTopTag>=1;                    }});
  //analysis_cuts['T'].push_back({ .name="mDPhi",      .func = []    { return minDeltaPhi>=0.5;                 }});
  analysis_cuts['T'].push_back({ .name="mDPhi",      .func = []    { return dPhiRazor<2.8;                 }});
  analysis_cuts['T'].push_back({ .name="MT",         .func = []    { return     MT_vetolep<100;               }});

  // t: Boosted Top W region
  analysis_cuts['W'].push_back({ .name="1JetAK8",    .func = []    { return nJetAK8>=1;                      }});
  analysis_cuts['W'].push_back({ .name="NJet",       .func = []    { return nJet>=3;                          }});
  analysis_cuts['W'].push_back({ .name="MR_R2",      .func = [&d]  { return MR>=800 && R2>=0.08;  }});
  analysis_cuts['W'].push_back({ .name="HLT",   .func = [this,&d]  { return isData ? d.HLT_PFHT1050==1 || d.HLT_AK8PFHT800_TrimMass50==1 || d.HLT_PFHT500_PFMET100_PFMHT100_IDTight==1 || d.HLT_AK8PFJet450==1 || d.HLT_AK8PFJet400_TrimMass30==1 : 1; }});
  //analysis_cuts['W'].push_back({ .name="HLT",   .func = [this,&d]  { return d.HLT_PFHT1050==1 || d.HLT_AK8PFHT800_TrimMass50==1 || d.HLT_PFHT500_PFMET100_PFMHT100_IDTight==1 || d.HLT_AK8PFJet450==1 || d.HLT_AK8PFJet400_TrimMass30==1; }});
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
  analysis_cuts['L'].push_back({ .name="HLT",   .func = [this,&d]  { return isData ? d.HLT_PFHT1050==1 || d.HLT_AK8PFHT800_TrimMass50==1 || d.HLT_PFHT500_PFMET100_PFMHT100_IDTight==1 || d.HLT_AK8PFJet450==1 || d.HLT_AK8PFJet400_TrimMass30==1 : 1; }});
  //analysis_cuts['L'].push_back({ .name="HLT",   .func = [this,&d]  { return d.HLT_PFHT1050==1 || d.HLT_AK8PFHT800_TrimMass50==1 || d.HLT_PFHT500_PFMET100_PFMHT100_IDTight==1 || d.HLT_AK8PFJet450==1 || d.HLT_AK8PFJet400_TrimMass30==1; }});
  analysis_cuts['L'].push_back({ .name="1Lep",       .func = []    { return nLepVeto==1;                      }});
  analysis_cuts['L'].push_back({ .name="0b",         .func = []    { return nLooseBTag==0;                    }});
  analysis_cuts['L'].push_back({ .name="1mTop",      .func = []    { return nHadTop0BMassTag>=1;              }});
  analysis_cuts['L'].push_back({ .name="mDPhi",      .func = []    { return dPhiRazor<2.8;                    }});
  analysis_cuts['L'].push_back({ .name="MT",         .func = []    { return MT_vetolep>=30 && MT_vetolep<100; }});

  // Z: Z->ll enriched control sample
  analysis_cuts['Z'].push_back({ .name="1JetAK8",    .func = []    { return nJetAK8>=1;                      }});
  analysis_cuts['Z'].push_back({ .name="NJet",       .func = []    { return nJet>=3;                          }});
  analysis_cuts['Z'].push_back({ .name="MR_R2ll",    .func = [&d]  { return MR>=800 && R2_ll>=0.08;     }});
  analysis_cuts['Z'].push_back({ .name="HLT",   .func = [this,&d]  { return isData ? d.HLT_PFHT1050==1 || d.HLT_AK8PFHT800_TrimMass50==1 || d.HLT_PFHT500_PFMET100_PFMHT100_IDTight==1 || d.HLT_AK8PFJet450==1 || d.HLT_AK8PFJet400_TrimMass30==1 : 1; }});
  //analysis_cuts['Z'].push_back({ .name="HLT",   .func = [this,&d]  { return d.HLT_PFHT1050==1 || d.HLT_AK8PFHT800_TrimMass50==1 || d.HLT_PFHT500_PFMET100_PFMHT100_IDTight==1 || d.HLT_AK8PFJet450==1 || d.HLT_AK8PFJet400_TrimMass30==1; }});
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
  analysis_cuts['G'].push_back({ .name="HLT",   .func = [this,&d]  { return isData ? d.HLT_PFHT1050==1 || d.HLT_AK8PFHT800_TrimMass50==1 || d.HLT_PFHT500_PFMET100_PFMHT100_IDTight==1 || d.HLT_AK8PFJet450==1 || d.HLT_AK8PFJet400_TrimMass30==1 : 1; }});
  //analysis_cuts['G'].push_back({ .name="HLT",   .func = [this,&d]  { return d.HLT_PFHT1050==1 || d.HLT_AK8PFHT800_TrimMass50==1 || d.HLT_PFHT500_PFMET100_PFMHT100_IDTight==1 || d.HLT_AK8PFJet450==1 || d.HLT_AK8PFJet400_TrimMass30==1; }});
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

#endif

  // G-1: Photon enriched sample (G without boosted object)
  analysis_cuts['g'].push_back({ .name="1JetAK8",    .func = []    { return nJetAK8>=1;                       }});
  analysis_cuts['g'].push_back({ .name="1Pho",       .func = []    { return nPhotonSelect==1;                 }});
  analysis_cuts['g'].push_back({ .name="NJet",       .func = []    { return nJetNoPho>=3;                     }});
  analysis_cuts['g'].push_back({ .name="MR",         .func = [&d]  { return MR_pho>=800;                      }});
  analysis_cuts['g'].push_back({ .name="R2",         .func = [&d]  { return R2_pho>=0.08;                     }});
  analysis_cuts['g'].push_back({ .name="HLT",   .func = [this,&d]  { return isData ? d.HLT_PFHT1050==1 || d.HLT_AK8PFHT800_TrimMass50==1 || d.HLT_PFHT500_PFMET100_PFMHT100_IDTight==1 || d.HLT_AK8PFJet450==1 || d.HLT_AK8PFJet400_TrimMass30==1 : 1; }});
  //analysis_cuts['g'].push_back({ .name="HLT",   .func = [this,&d]  { return d.HLT_PFHT1050==1 || d.HLT_AK8PFHT800_TrimMass50==1 || d.HLT_PFHT500_PFMET100_PFMHT100_IDTight==1 || d.HLT_AK8PFJet450==1 || d.HLT_AK8PFJet400_TrimMass30==1; }});
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
  analysis_cuts['w'].push_back({ .name="HLT",   .func = [this,&d]  { return isData ? d.HLT_PFHT1050==1 || d.HLT_AK8PFHT800_TrimMass50==1 || d.HLT_PFHT500_PFMET100_PFMHT100_IDTight==1 || d.HLT_AK8PFJet450==1 || d.HLT_AK8PFJet400_TrimMass30==1 : 1; }});
  //analysis_cuts['w'].push_back({ .name="HLT",   .func = [this,&d]  { return d.HLT_PFHT1050==1 || d.HLT_AK8PFHT800_TrimMass50==1 || d.HLT_PFHT500_PFMET100_PFMHT100_IDTight==1 || d.HLT_AK8PFJet450==1 || d.HLT_AK8PFJet400_TrimMass30==1; }});
  analysis_cuts['w'].push_back({ .name="1Lep",       .func = []    { return nLepSelect==1;                    }});
  analysis_cuts['w'].push_back({ .name="MET",        .func = [&d]  { return d.MET_pt>=30;                  }});
  analysis_cuts['w'].push_back({ .name="MT",         .func = []    { return MT>=30 && MT<100;                 }});
  analysis_cuts['w'].push_back({ .name="0b",         .func = []    { return nLooseBTag==0;                    }});

  // F: Fake rate measurement region
  analysis_cuts['F'].push_back({ .name="1JetAK8",    .func = []    { return nJetAK8>=1;                       }});
  analysis_cuts['F'].push_back({ .name="MR",         .func = [&d]  { return MR>=800;                    }});
  analysis_cuts['F'].push_back({ .name="NJet",       .func = []    { return nJet>=3;                          }});
  analysis_cuts['F'].push_back({ .name="HLT",   .func = [this,&d]  { return isData ? d.HLT_PFHT1050==1 || d.HLT_AK8PFHT800_TrimMass50==1 || d.HLT_PFHT500_PFMET100_PFMHT100_IDTight==1 || d.HLT_AK8PFJet450==1 || d.HLT_AK8PFJet400_TrimMass30==1 : 1; }});
  //analysis_cuts['F'].push_back({ .name="HLT",   .func = [this,&d]  { return d.HLT_PFHT1050==1 || d.HLT_AK8PFHT800_TrimMass50==1 || d.HLT_PFHT500_PFMET100_PFMHT100_IDTight==1 || d.HLT_AK8PFJet450==1 || d.HLT_AK8PFJet400_TrimMass30==1; }});
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
  analysis_cuts['f'].push_back({ .name="HLT",   .func = [this,&d]  { return isData ? d.HLT_PFHT1050==1 || d.HLT_AK8PFHT800_TrimMass50==1 || d.HLT_PFHT500_PFMET100_PFMHT100_IDTight==1 || d.HLT_AK8PFJet450==1 || d.HLT_AK8PFJet400_TrimMass30==1 : 1; }});
  //analysis_cuts['f'].push_back({ .name="HLT",   .func = [this,&d]  { return d.HLT_PFHT1050==1 || d.HLT_AK8PFHT800_TrimMass50==1 || d.HLT_PFHT500_PFMET100_PFMHT100_IDTight==1 || d.HLT_AK8PFJet450==1 || d.HLT_AK8PFJet400_TrimMass30==1; }});
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
  analysis_cuts['H'].push_back({ .name="HLT",   .func = [this,&d]  { return isData ? d.HLT_PFHT1050==1 || d.HLT_AK8PFHT800_TrimMass50==1 || d.HLT_PFHT500_PFMET100_PFMHT100_IDTight==1 || d.HLT_AK8PFJet450==1 || d.HLT_AK8PFJet400_TrimMass30==1 : 1; }});
  //analysis_cuts['H'].push_back({ .name="HLT",   .func = [this,&d]  { return d.HLT_PFHT1050==1 || d.HLT_AK8PFHT800_TrimMass50==1 || d.HLT_PFHT500_PFMET100_PFMHT100_IDTight==1 || d.HLT_AK8PFJet450==1 || d.HLT_AK8PFJet400_TrimMass30==1; }});
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





void
Analysis::apply_scale_factors(eventBuffer& data, const unsigned int& s, const std::vector<std::vector<double> >& nSigmaSFs)
{

 //bool isFastSim = TString(sample).Contains("FastSim");
  //size_t i = 0;

  // Don't forget to specify the total number of sigmas you use in settings_*.h !

/*
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
*/

double sf_ele_veto=1,  sf_ele_medium=1;
double sf_muon_veto=1, sf_muon_medium=1;
double sf_btag_loose = 1, sf_btag_medium = 1;
double sf_fake_mW=1, sf_fake_aW=1, sf_w=1;
//double sf_top=1, sf_fake_0b_mTop=1, sf_fake_MTop=1, sf_fake_aTop=1;
// // Select scale factors to use
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

  scale_factors['F'].push_back(sf_ele_veto);
  scale_factors['F'].push_back(sf_muon_veto);
  scale_factors['F'].push_back(sf_btag_loose);
  scale_factors['f'].push_back(sf_ele_veto);
  scale_factors['f'].push_back(sf_muon_veto);
  scale_factors['f'].push_back(sf_btag_medium);

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

TH2D* h_MR_R2;
TH1D* h_R2;
TH1D* h_MR;

TH2D* h_S_MRR2;
TH2D* h_S_MRR2_nj3;
TH2D* h_S_MRR2_nj35;
TH2D* h_S_MRR2_nj5;

TH2D* h_s_MRR2;
TH2D* h_s_MRR2_nj3;
TH2D* h_s_MRR2_nj35;
TH2D* h_s_MRR2_nj5;

TH2D* h_Q_MRR2;
TH2D* h_Q_MRR2_nj3;
TH2D* h_Q_MRR2_nj35;
TH2D* h_Q_MRR2_nj5;

TH2D* h_q_MRR2;
TH2D* h_q_MRR2_nj3;
TH2D* h_q_MRR2_nj35;
TH2D* h_q_MRR2_nj5;

TH2D* h_W_MRR2;
TH2D* h_W_MRR2_nj3;
TH2D* h_W_MRR2_nj35;
TH2D* h_W_MRR2_nj5;

TH2D* h_T_MRR2;
TH2D* h_T_MRR2_nj3;
TH2D* h_T_MRR2_nj35;
TH2D* h_T_MRR2_nj5;

TH2D* h_Z_MRR2;
TH2D* h_Z_MRR2_nj3;
TH2D* h_Z_MRR2_nj35;
TH2D* h_Z_MRR2_nj5;

TH2D* h_L_MRR2;
TH2D* h_MRR2_L_anaW;
TH2D* h_G_MRR2;

TH1D* h_MR_Z;
TH1D* h_R2_Z;
TH1D* h_MR_T;
TH1D* h_R2_T;
TH1D* h_MR_W;
TH1D* h_R2_W;
TH1D* h_MR_Q;
TH1D* h_R2_Q;
TH1D* h_MR_q;
TH1D* h_R2_q;
TH1D* h_MR_S;
TH1D* h_R2_S;
TH1D* h_MR_s;
TH1D* h_R2_s;
TH1D* h_MR_L;
TH1D* h_R2_L;
TH1D* h_MR_G;
TH1D* h_R2_G;

TH1D* h_MR_Z_anaW;
TH1D* h_R2_Z_anaW;
TH1D* h_MR_T_anaW;
TH1D* h_R2_T_anaW;
TH1D* h_MR_W_anaW;
TH1D* h_R2_W_anaW;
TH1D* h_MR_Q_anaW;
TH1D* h_R2_Q_anaW;
TH1D* h_MR_q_anaW;
TH1D* h_R2_q_anaW;
TH1D* h_MR_S_anaW;
TH1D* h_R2_S_anaW;
TH1D* h_MR_s_anaW;
TH1D* h_R2_s_anaW;
TH1D* h_MR_L_anaW;
TH1D* h_R2_L_anaW;


TH1D* h_njet_S;
TH1D* h_njet_Q;
TH1D* h_njet_T;
TH1D* h_njet_W;
TH1D* h_njet_Z;
TH1D* h_njet_L;
TH1D* h_njet_G;

TH1D* h_njet_S_anaW;
TH1D* h_njet_Q_anaW;
TH1D* h_njet_T_anaW;
TH1D* h_njet_W_anaW;
TH1D* h_njet_Z_anaW;
TH1D* h_njet_L_anaW;
/*
TH1D* h_S_HT;
TH1D* h_Q_HT;
TH1D* h_T_HT;
TH1D* h_W_HT;
TH1D* h_s_HT;
TH1D* h_q_HT;
TH1D* h_Z_HT;
*/

TH1D* h_S_MET;
TH1D* h_Q_MET;
TH1D* h_T_MET;
TH1D* h_W_MET;
TH1D* h_s_MET;
TH1D* h_q_MET;
TH1D* h_Z_MET;

TH1D* h_S_MET_anaW;
TH1D* h_Q_MET_anaW;
TH1D* h_T_MET_anaW;
TH1D* h_W_MET_anaW;
TH1D* h_s_MET_anaW;
TH1D* h_q_MET_anaW;
TH1D* h_Z_MET_anaW;

TH1D* h_AK8_jet1_pt_Q;
TH1D* h_AK8_jet1_pt_q;
TH1D* h_AK8_jet1_pt_S;
TH1D* h_AK8_jet1_pt_s;
TH1D* h_AK8_jet1_pt_T;
TH1D* h_AK8_jet1_pt_W;
TH1D* h_AK8_jet1_pt_Z;

TH1D* h_AK8_jet1_Eta_Q;
TH1D* h_AK8_jet1_Eta_q;
TH1D* h_AK8_jet1_Eta_S;
TH1D* h_AK8_jet1_Eta_s;
TH1D* h_AK8_jet1_Eta_T;
TH1D* h_AK8_jet1_Eta_W;
TH1D* h_AK8_jet1_Eta_Z;

TH1D* h_AK8_jet1_pt_Q_anaW;
TH1D* h_AK8_jet1_pt_q_anaW;
TH1D* h_AK8_jet1_pt_S_anaW;
TH1D* h_AK8_jet1_pt_s_anaW;
TH1D* h_AK8_jet1_pt_T_anaW;
TH1D* h_AK8_jet1_pt_W_anaW;
TH1D* h_AK8_jet1_pt_Z_anaW;

TH1D* h_AK8_jet1_Eta_Q_anaW;
TH1D* h_AK8_jet1_Eta_q_anaW;
TH1D* h_AK8_jet1_Eta_S_anaW;
TH1D* h_AK8_jet1_Eta_s_anaW;
TH1D* h_AK8_jet1_Eta_T_anaW;
TH1D* h_AK8_jet1_Eta_W_anaW;
TH1D* h_AK8_jet1_Eta_Z_anaW;

TH1D* h_DPhi_Q;
TH1D* h_DPhi_q;
TH1D* h_DPhi_S;
TH1D* h_DPhi_s;
TH1D* h_DPhi_T;
TH1D* h_DPhi_W;
TH1D* h_DPhi_Z;

TH1D* h_MTR_Q;
TH1D* h_MTR_q;
TH1D* h_MTR_S;
TH1D* h_MTR_s;
TH1D* h_MTR_T;
TH1D* h_MTR_W;
TH1D* h_MTR_Z;

TH1D* h_MT_Q;
TH1D* h_MT_q;
TH1D* h_MT_S;
TH1D* h_MT_s;
TH1D* h_MT_T;
TH1D* h_MT_W;
TH1D* h_MT_Z;

TH1D* h_nTop;
TH1D* h_ht_AK4;
TH1D* h_ht_AK8;

TH1D* h_ht_S;
TH1D* h_ht_Q;
TH1D* h_ht_T;
TH1D* h_ht_W;
TH1D* h_ht_Z;
TH1D* h_ht_S_anaW;
TH1D* h_ht_Q_anaW;
TH1D* h_ht_T_anaW;
TH1D* h_ht_W_anaW;
TH1D* h_ht_Z_anaW;

TH1D* h_njet;
TH1D* h_nb_anaW;
TH1D* h_nw_anaW;

//_______________________________________________________
//              Define Histograms here
void
Analysis::init_analysis_histos(const unsigned int& syst_nSyst, const unsigned int& syst_index)
{
 // h_gen_toppt      = new TH1D("h_gen_toppt", "h_gen_toppt", 50, 0, 1000);
  //int nbn_MET = 10;
  int nbn_HT = 19;
  //int nbn_AK8J1pt = 15;
  int nbn_AK8j1toppt = 16;
  //int nbn_MTR = 8;
  int nbn_MR = 7;
  int nbn_R2 = 7;

 // Double_t HT_bins[19] = {0, 200, 300, 400, 500, 600, 650, 700, 750, 800, 900, 1000, 1200, 1500, 2000, 3000};
  //Double_t bn_HTtmp[] = {400.,500.,600.,700.,750.,800.,850.,900.,950.,1000.,1500.};
 // Double_t* bnHT = 0;
 // bnHT = getVariableBinEdges(nbnHT+1,bn_HTtmp);

  Double_t bn_HT_tmp[] = {0.,50.,100.,150.,200.,250.,300.,350.,400.,450.,500.,550.,600.,650.,700.,750.,800.,900.,1000.,2500.};
  Double_t* bn_HT = 0;
  bn_HT = getVariableBinEdges(nbn_HT+1,bn_HT_tmp);

//  Double_t bn_HT_tmp[] = {0.,200.,400.,450.,500.,550.,600.,650.,700.,750.,800.,900.,1000.,1200.,1400.,1600.,1800.,2000.,2500.,3000.,10000.};
 // Double_t* bn_HT = 0;
  //bn_HT = getVariableBinEdges(nbn_HT+1,bn_HT_tmp);

  /*Double_t bn_MET_tmp[] = {0., 100., 200., 300., 400., 500., 600., 800., 1000., 1500., 2000.};
  Double_t* bn_MET = 0;
  bn_ME T=  getVariableBinEdges(nbn_MET+1,bn_MET_tmp); */

 /*Double_t bn_MTR_tmp[] = {200., 300., 400., 600., 800., 1000., 1200., 1600., 2000.};
  Double_t* bn_MTR = 0;
  bn_MTR = getVariableBinEdges(nbn_MTR+1,bn_MTR_tmp); */

  Double_t bn_MR_tmp[] = {0.,600.,800.,1000.,1200.,1600.,2000.,4000.};
  Double_t* bn_MR = 0;
  bn_MR = getVariableBinEdges(nbn_MR+1,bn_MR_tmp);

  Double_t bn_R2_tmp[] = {0.,0.04,0.08,0.12,0.16,0.24,0.5,1.};
  Double_t* bn_R2 = 0;
  bn_R2 = getVariableBinEdges(nbn_R2+1,bn_R2_tmp);

 // Double_t bn_AK8J1pt_tmp[] = {0.,200.,220.,240,260,280,300.,320.,340,360,380,400.,450,500.,700,1000.};
 // Double_t* bn_AK8J1pt = 0;
 // bn_AK8J1pt = getVariableBinEdges(nbn_AK8J1pt+1,bn_AK8J1pt_tmp);

  Double_t bn_AK8j1toppt_tmp[] = {200, 250, 300, 350, 400, 450, 500, 550, 600, 700, 800, 1000, 1400, 2000, 3000, 4000, 5000};
  Double_t* bn_AK8j1toppt = 0;
  bn_AK8j1toppt = getVariableBinEdges(nbn_AK8j1toppt+1,bn_AK8j1toppt_tmp);



  h_MR_R2 = new TH2D("MR_R2", ";MR_{AK4};R2_{AK4}",nbn_MR,bn_MR,nbn_R2,bn_R2);
  h_R2 = new TH1D("R2", ";R2_{AK4}",nbn_R2,bn_R2);
  h_MR = new TH1D("MR", ";MR_{AK4}",nbn_MR,bn_MR);
  h_S_MRR2_nj3     = new TH2D("S_MRR2_nj3", ";MR;R2", nbn_MR, bn_MR, nbn_R2, bn_R2 );
  h_S_MRR2_nj35    = new TH2D("S_MRR2_nj35", ";MR;R2", nbn_MR, bn_MR, nbn_R2, bn_R2 );
  h_S_MRR2_nj5     = new TH2D("S_MRR2_nj5", ";MR;R2", nbn_MR, bn_MR, nbn_R2, bn_R2 );
  h_S_MRR2 = new TH2D("S_MRR2", ";MR;R2",nbn_MR,bn_MR,nbn_R2,bn_R2);
  h_Q_MRR2_nj3     = new TH2D("Q_MRR2_nj3",";MR;R2", nbn_MR, bn_MR, nbn_R2, bn_R2 );
  h_Q_MRR2_nj35    = new TH2D("Q_MRR2_nj35", ";MR;R2", nbn_MR, bn_MR, nbn_R2, bn_R2 );
  h_Q_MRR2_nj5     = new TH2D("Q_MRR2_nj5", ";MR;R2", nbn_MR, bn_MR, nbn_R2, bn_R2 );
  h_Q_MRR2 = new TH2D("Q_MRR2", ";MR;R2",nbn_MR,bn_MR,nbn_R2,bn_R2);
  h_W_MRR2_nj3     = new TH2D("W_MRR2_nj3",";MR;R2", nbn_MR, bn_MR, nbn_R2, bn_R2 );
  h_W_MRR2_nj35    = new TH2D("W_MRR2_nj35", ";MR;R2", nbn_MR, bn_MR, nbn_R2, bn_R2 );
  h_W_MRR2_nj5     = new TH2D("W_MRR2_nj5", ";MR;R2", nbn_MR, bn_MR, nbn_R2, bn_R2 );
  h_W_MRR2 = new TH2D("W_MRR2", ";MR;R2",nbn_MR,bn_MR,nbn_R2,bn_R2);
  h_T_MRR2_nj3     = new TH2D("T_MRR2_nj3",";MR;R2", nbn_MR, bn_MR, nbn_R2, bn_R2 );
  h_T_MRR2_nj35     = new TH2D("T_MRR2_nj35", ";MR;R2", nbn_MR, bn_MR, nbn_R2, bn_R2 );
  h_T_MRR2_nj5     = new TH2D("T_MRR2_nj5", ";MR;R2", nbn_MR, bn_MR, nbn_R2, bn_R2 );
  h_T_MRR2 = new TH2D("T_MRR2", ";MR;R2",nbn_MR,bn_MR,nbn_R2,bn_R2);
  h_q_MRR2_nj3     = new TH2D("q_MRR2_nj3",";MR;R2", nbn_MR, bn_MR, nbn_R2, bn_R2 );
  h_q_MRR2_nj35    = new TH2D("q_MRR2_nj35",";MR;R2", nbn_MR, bn_MR, nbn_R2, bn_R2 );
  h_q_MRR2_nj5     = new TH2D("q_MRR2_nj5",";MR;R2", nbn_MR, bn_MR, nbn_R2, bn_R2 );
  h_q_MRR2 = new TH2D("q_MRR2", ";MR;R2",nbn_MR,bn_MR,nbn_R2,bn_R2);
  h_s_MRR2_nj3     = new TH2D("s_MRR2_nj3", ";MR;R2", nbn_MR, bn_MR, nbn_R2, bn_R2 );
  h_s_MRR2_nj35    = new TH2D("s_MRR2_nj35", ";MR;R2", nbn_MR, bn_MR, nbn_R2, bn_R2 );
  h_s_MRR2_nj5     = new TH2D("s_MRR2_nj5", ";MR;R2", nbn_MR, bn_MR, nbn_R2, bn_R2 );
  h_s_MRR2 = new TH2D("s_MRR2", ";MR;R2",nbn_MR,bn_MR,nbn_R2,bn_R2);
  h_Z_MRR2_nj3     = new TH2D("Z_MRR2_nj3", ";MR;R2", nbn_MR, bn_MR, nbn_R2, bn_R2 );
  h_Z_MRR2_nj35    = new TH2D("Z_MRR2_nj35", ";MR;R2", nbn_MR, bn_MR, nbn_R2, bn_R2 );
  h_Z_MRR2_nj5     = new TH2D("Z_MRR2_nj5", ";MR;R2", nbn_MR, bn_MR, nbn_R2, bn_R2 );
  h_Z_MRR2 = new TH2D("Z_MRR2", ";MR;R2",nbn_MR,bn_MR,nbn_R2,bn_R2);
  h_L_MRR2 = new TH2D("L_MRR2", ";MR;R2",nbn_MR,bn_MR,nbn_R2,bn_R2);
  h_MRR2_L_anaW = new TH2D("MRR2_L_anaW", ";MR;R2",nbn_MR,bn_MR,nbn_R2,bn_R2);
  h_G_MRR2 = new TH2D("G_MRR2", ";MR;R2",nbn_MR,bn_MR,nbn_R2,bn_R2);
  h_MR_Z = new TH1D("MR_Z", ";Z_MR", nbn_MR, bn_MR);
  h_R2_Z = new TH1D("R2_Z", ";Z_R2", nbn_R2,bn_R2);
  h_MR_T = new TH1D("MR_T", ";T_MR", nbn_MR, bn_MR);
  h_R2_T = new TH1D("R2_T", ";T_R2", nbn_R2,bn_R2);
  h_MR_W = new TH1D("MR_W", ";W_MR", nbn_MR, bn_MR);
  h_R2_W = new TH1D("R2_W", ";W_R2", nbn_R2,bn_R2);
  h_MR_Q = new TH1D("MR_Q", ";Q_MR", nbn_MR, bn_MR);
  h_R2_Q = new TH1D("R2_Q", ";Q_R2", nbn_R2,bn_R2);
  h_MR_q = new TH1D("MR_q", ";q_MR", nbn_MR, bn_MR);
  h_R2_q = new TH1D("R2_q", ";q_R2", nbn_R2,bn_R2);
  h_MR_S = new TH1D("MR_S", ";S_MR", nbn_MR, bn_MR);
  h_R2_S = new TH1D("R2_S", ";S_R2", nbn_R2,bn_R2);
  h_MR_s = new TH1D("MR_s", ";s_MR", nbn_MR, bn_MR);
  h_R2_s = new TH1D("R2_s", ";s_R2", nbn_R2,bn_R2);
  h_MR_L = new TH1D("MR_L", ";L_MR", nbn_MR, bn_MR);
  h_R2_L = new TH1D("R2_L", ";L_R2", nbn_R2,bn_R2);
  h_MR_G = new TH1D("MR_G", ";G_MR", nbn_MR, bn_MR);
  h_R2_G = new TH1D("R2_G", ";G_R2", nbn_R2,bn_R2);
  h_MR_Z_anaW = new TH1D("MR_Z_anaW", ";Z_MR", nbn_MR, bn_MR);
  h_R2_Z_anaW = new TH1D("R2_Z_anaW", ";Z_R2", nbn_R2,bn_R2);
  h_MR_T_anaW = new TH1D("MR_T_anaW", ";T_MR", nbn_MR, bn_MR);
  h_R2_T_anaW = new TH1D("R2_T_anaW", ";T_R2", nbn_R2,bn_R2);
  h_MR_W_anaW = new TH1D("MR_W_anaW", ";W_MR", nbn_MR, bn_MR);
  h_R2_W_anaW = new TH1D("R2_W_anaW", ";W_R2", nbn_R2,bn_R2);
  h_MR_Q_anaW = new TH1D("MR_Q_anaW", ";Q_MR", nbn_MR, bn_MR);
  h_R2_Q_anaW = new TH1D("R2_Q_anaW", ";Q_R2", nbn_R2,bn_R2);
  h_MR_q_anaW= new TH1D("MR_q_anaW", ";q_MR", nbn_MR, bn_MR);
  h_R2_q_anaW = new TH1D("R2_q_anaW", ";q_R2", nbn_R2,bn_R2);
  h_MR_S_anaW = new TH1D("MR_S_anaW", ";S_MR", nbn_MR, bn_MR);
  h_R2_S_anaW = new TH1D("R2_S_anaW", ";S_R2", nbn_R2,bn_R2);
  h_MR_s_anaW = new TH1D("MR_s_anaW", ";s_MR", nbn_MR, bn_MR);
  h_R2_s_anaW = new TH1D("R2_s_anaW", ";s_R2", nbn_R2,bn_R2);
  h_MR_L_anaW = new TH1D("MR_L_anaW", ";M_MR", nbn_MR, bn_MR);
  h_R2_L_anaW = new TH1D("R2_L_anaW", ";M_R2", nbn_R2,bn_R2);
  h_njet_S = new TH1D("njet_S",         ";N_{jet}",                20, 0,  20);
  h_njet_Q = new TH1D("njet_Q",         ";N_{jet}",                20, 0,  20);
  h_njet_T = new TH1D("njet_T",         ";N_{jet}",                20, 0,  20);
  h_njet_W = new TH1D("njet_W",         ";N_{jet}",                20, 0,  20);
  h_njet_Z = new TH1D("njet_Z",         ";N_{jet}",                20, 0,  20);
  h_njet_L = new TH1D("njet_L",         ";N_{jet}",                20, 0,  20);
  h_njet_G = new TH1D("njet_G",         ";N_{jet}",                20, 0,  20);
  h_njet_S_anaW = new TH1D("njet_S_anaW",         ";N_{jet}",                20, 0,  20);
  h_njet_Q_anaW = new TH1D("njet_Q_anaW",         ";N_{jet}",                20, 0,  20);
  h_njet_T_anaW = new TH1D("njet_T_anaW",         ";N_{jet}",                20, 0,  20);
  h_njet_W_anaW = new TH1D("njet_W_anaW",         ";N_{jet}",                20, 0,  20);
  h_njet_Z_anaW = new TH1D("njet_Z_anaW",         ";N_{jet}",                20, 0,  20);
  h_njet_L_anaW = new TH1D("njet_L_anaW",         ";N_{jet}",                20, 0,  20);
   /*h_S_HT           = new TH1D("S_HT",";S_H_{T}", 15, HT_bins);
   h_Q_HT           = new TH1D("Q_HT",";Q_H_{T}", 15, HT_bins);
   h_T_HT           = new TH1D("T_HT",";T_H_{T}", 15, HT_bins);
   h_W_HT           = new TH1D("W_HT",";W_H_{T}", 15, HT_bins);
   h_s_HT           = new TH1D("s_HT",";s_H_{T}", 15, HT_bins);
   h_q_HT           = new TH1D("q_HT",";q_H_{T}", 15, HT_bins);
   h_Z_HT           = new TH1D("Z_HT",";Z_H_{T}", 15, HT_bins);
*/
  h_S_MET = new TH1D("S_MET", ";S_#slash{E}_{T} (GeV)",  400,0,2000);
  h_Q_MET = new TH1D("Q_MET", ";Q_#slash{E}_{T} (GeV)",  400,0,2000);
  h_T_MET = new TH1D("T_MET", ";T_#slash{E}_{T} (GeV)",  400,0,2000);
  h_W_MET = new TH1D("W_MET", ";W_#slash{E}_{T} (GeV)",  400,0,2000);
  h_s_MET = new TH1D("s_MET", ";s_#slash{E}_{T} (GeV)",  400,0,2000);
  h_q_MET = new TH1D("q_MET", ";q_#slash{E}_{T} (GeV)",  400,0,2000);
  h_Z_MET = new TH1D("Z_MET", ";Z_#slash{E}_{T} (GeV)",  400,0,2000);
  h_S_MET_anaW = new TH1D("S_MET_anaW", ";S_#slash{E}_{T} (GeV)",  400,0,2000);
  h_Q_MET_anaW = new TH1D("Q_MET_anaW", ";Q_#slash{E}_{T} (GeV)",  400,0,2000);
  h_T_MET_anaW = new TH1D("T_MET_anaW", ";T_#slash{E}_{T} (GeV)",  400,0,2000);
  h_W_MET_anaW = new TH1D("W_MET_anaW", ";W_#slash{E}_{T} (GeV)",  400,0,2000);
  h_s_MET_anaW = new TH1D("s_MET_anaW", ";s_#slash{E}_{T} (GeV)",  400,0,2000);
  h_q_MET_anaW = new TH1D("q_MET_anaW", ";q_#slash{E}_{T} (GeV)",  400,0,2000);
  h_Z_MET_anaW = new TH1D("Z_MET_anaW", ";Z_#slash{E}_{T} (GeV)",  400,0,2000);
  h_AK8_jet1_pt_Q = new TH1D("jet1_AK8_pt_Q",      ";AK8 jet p_{T, jet1}", 200, 0,2000);
  h_AK8_jet1_pt_q = new TH1D("jet1_AK8_pt_q",      ";AK8 jet p_{T, jet1}", 200, 0,2000);
  h_AK8_jet1_pt_S = new TH1D("jet1_AK8_pt_S",      ";AK8 jet p_{T, jet1}", 200, 0,2000);
  h_AK8_jet1_pt_s = new TH1D("jet1_AK8_pt_s",      ";AK8 jet p_{T, jet1}", 200, 0,2000);
  h_AK8_jet1_pt_T = new TH1D("jet1_AK8_pt_T",      ";AK8 jet p_{T, jet1}", 200, 0,2000);
  h_AK8_jet1_pt_W = new TH1D("jet1_AK8_pt_W",      ";AK8 jet p_{T, jet1}", 200, 0,2000);
  h_AK8_jet1_pt_Z = new TH1D("jet1_AK8_pt_Z",      ";AK8 jet p_{T, jet1}", 200, 0,2000);
  h_AK8_jet1_Eta_Q = new TH1D("jet1_AK8_Eta_Q",      ";AK8 jet #eta", 640, -3.2,3.2);
  h_AK8_jet1_Eta_q = new TH1D("jet1_AK8_Eta_q",      ";AK8 jet #eta", 640, -3.2,3.2);
  h_AK8_jet1_Eta_S = new TH1D("jet1_AK8_Eta_S",      ";AK8 jet #eta", 640, -3.2,3.2);
  h_AK8_jet1_Eta_s = new TH1D("jet1_AK8_Eta_s",      ";AK8 jet #eta", 640, -3.2,3.2);
  h_AK8_jet1_Eta_T = new TH1D("jet1_AK8_Eta_T",      ";AK8 jet #eta", 640, -3.2,3.2);
  h_AK8_jet1_Eta_W = new TH1D("jet1_AK8_Eta_W",      ";AK8 jet #eta", 640, -3.2,3.2);
  h_AK8_jet1_Eta_Z = new TH1D("jet1_AK8_Eta_Z",      ";AK8 jet #eta", 640, -3.2,3.2);
  h_AK8_jet1_pt_Q_anaW = new TH1D("jet1_AK8_pt_Q_anaW",      ";AK8 jet p_{T, jet1}", 200, 0,2000);
  h_AK8_jet1_pt_q_anaW = new TH1D("jet1_AK8_pt_q_anaW",      ";AK8 jet p_{T, jet1}", 200, 0,2000);
  h_AK8_jet1_pt_S_anaW = new TH1D("jet1_AK8_pt_S_anaW",      ";AK8 jet p_{T, jet1}", 200, 0,2000);
  h_AK8_jet1_pt_s_anaW = new TH1D("jet1_AK8_pt_s_anaW",      ";AK8 jet p_{T, jet1}", 200, 0,2000);
  h_AK8_jet1_pt_T_anaW = new TH1D("jet1_AK8_pt_T_anaW",      ";AK8 jet p_{T, jet1}", 200, 0,2000);
  h_AK8_jet1_pt_W_anaW = new TH1D("jet1_AK8_pt_W_anaW",      ";AK8 jet p_{T, jet1}", 200, 0,2000);
  h_AK8_jet1_pt_Z_anaW = new TH1D("jet1_AK8_pt_Z_anaW",      ";AK8 jet p_{T, jet1}", 200, 0,2000);
  h_AK8_jet1_Eta_Q_anaW = new TH1D("jet1_AK8_Eta_Q_anaW",      ";AK8 jet #eta", 640, -3.2,3.2);
  h_AK8_jet1_Eta_q_anaW = new TH1D("jet1_AK8_Eta_q_anaW",      ";AK8 jet #eta", 640, -3.2,3.2);
  h_AK8_jet1_Eta_S_anaW = new TH1D("jet1_AK8_Eta_S_anaW",      ";AK8 jet #eta", 640, -3.2,3.2);
  h_AK8_jet1_Eta_s_anaW = new TH1D("jet1_AK8_Eta_s_anaW",      ";AK8 jet #eta", 640, -3.2,3.2);
  h_AK8_jet1_Eta_T_anaW = new TH1D("jet1_AK8_Eta_T_anaW",      ";AK8 jet #eta", 640, -3.2,3.2);
  h_AK8_jet1_Eta_W_anaW = new TH1D("jet1_AK8_Eta_W_anaW",      ";AK8 jet #eta", 640, -3.2,3.2);
  h_AK8_jet1_Eta_Z_anaW = new TH1D("jet1_AK8_Eta_Z_anaW",      ";AK8 jet #eta", 640, -3.2,3.2);
  h_DPhi_Q = new TH1D("DPhi_Q",  ";#Delta#phi_{megajets}", 64,0,3.2);
  h_DPhi_q = new TH1D("DPhi_q",  ";#Delta#phi_{megajets}", 64,0,3.2);
  h_DPhi_S = new TH1D("DPhi_S",  ";#Delta#phi_{megajets}", 64,0,3.2);
  h_DPhi_s = new TH1D("DPhi_s",  ";#Delta#phi_{megajets}", 64,0,3.2);
  h_DPhi_T = new TH1D("DPhi_T",  ";#Delta#phi_{megajets}", 64,0,3.2);
  h_DPhi_W = new TH1D("DPhi_W",  ";#Delta#phi_{megajets}", 64,0,3.2);
  h_DPhi_Z = new TH1D("DPhi_Z",  ";#Delta#phi_{megajets}", 64,0,3.2);
  h_MTR_Q = new TH1D("MTR_Q",  ";Q_MTR_{AK4}", 200, 0 , 2000);
  h_MTR_q = new TH1D("MTR_q",  ";q_MTR_{AK4}", 200, 0 , 2000);
  h_MTR_S = new TH1D("MTR_S",  ";S_MTR_{AK4}", 200, 0 , 2000);
  h_MTR_s = new TH1D("MTR_s",  ";s_MTR_{AK4}", 200, 0 , 2000);
  h_MTR_T = new TH1D("MTR_T",  ";T_MTR_{AK4}", 200, 0 , 2000);
  h_MTR_W = new TH1D("MTR_W",  ";W_MTR_{AK4}", 200, 0 , 2000);
  h_MTR_Z = new TH1D("MTR_Z",  ";Z_MTR_{AK4}", 200, 0 , 2000);
  h_MT_Q = new TH1D("MT_Q",  ";Q_m_{T} (GeV)", 100,0,2000);
  h_MT_q = new TH1D("MT_q",  ";q_m_{T} (GeV)", 100,0,2000);
  h_MT_S = new TH1D("MT_S",  ";S_m_{T} (GeV)", 100,0,2000);
  h_MT_s = new TH1D("MT_s",  ";s_m_{T} (GeV)", 100,0,2000);
  h_MT_T = new TH1D("MT_T",  ";T_m_{T} (GeV)", 100,0,2000);
  h_MT_W = new TH1D("MT_W",  ";W_m_{T} (GeV)", 100,0,2000);
  h_MT_Z = new TH1D("MT_Z",  ";Z_m_{T} (GeV)", 100,0,2000);
  h_nTop           = new TH1D("nTop",           ";N_{Top tag}",              20, 0,  20);
  h_ht_AK4  = new TH1D("ht_AK4",  ";H_{T}",                   nbn_HT, bn_HT);
  h_ht_AK8  = new TH1D("ht_AK8",  ";H_{T}^{AK8}",             nbn_HT, bn_HT);
  h_ht_S  = new TH1D("ht_S",  ";H_{T}",                   nbn_HT, bn_HT);
  h_ht_Q  = new TH1D("ht_Q",  ";H_{T}",                   nbn_HT, bn_HT);
  h_ht_T  = new TH1D("ht_T",  ";H_{T}",                   nbn_HT, bn_HT);
  h_ht_W  = new TH1D("ht_W",  ";H_{T}",                   nbn_HT, bn_HT);
  h_ht_Z  = new TH1D("ht_Z",  ";H_{T}",                   nbn_HT, bn_HT);
  h_ht_S_anaW  = new TH1D("ht_S_anaW",  ";H_{T}",                   nbn_HT, bn_HT);
  h_ht_Q_anaW  = new TH1D("ht_Q_anaW",  ";H_{T}",                   nbn_HT, bn_HT);
  h_ht_T_anaW  = new TH1D("ht_T_anaW",  ";H_{T}",                   nbn_HT, bn_HT);
  h_ht_W_anaW  = new TH1D("ht_W_anaW",  ";H_{T}",                   nbn_HT, bn_HT);
  h_ht_Z_anaW  = new TH1D("ht_Z_anaW",  ";H_{T}",                   nbn_HT, bn_HT);
  h_njet         = new TH1D("njet",         ";N_{jet}",                20, 0,  20);
  h_nw_anaW           = new TH1D("nw_anaW",           ";N_{W tag}",              20, 0,  20);
  h_nb_anaW           = new TH1D("nb_anaW",           ";N_{b tag}",              20, 0,  20);

}



//_______________________________________________________
//               Fill Histograms here
void
Analysis::fill_analysis_histos(eventBuffer& data, const unsigned int& syst_index, const double& weight)
{
    double w = weight;

  if (syst_index == 0) {

    // syst_index should only be non-0 if settings.varySystematics is true
    // in case of studying systematics, one should fill a different histogram for each syst_index
    // this variable can be used to chose the correct vector element in case there is a vector of histograms
    // It makes sense, to cut on syst_index == 0, for all ordinary plots
    // syst_index == 0 always guarantees, there are no variations in any systematics

    // Check what common variables are available in AnalysisBase.h
    // There a good chance a lot of stuff is already calculated!
    // Especially common object selections or variables to cut on in Analysis

    /*
      Weight:
      They now include trigger efficiencies for MC by default
      w is the event weight without any scale factor applied
      Because scale factors are region dependend, then
      in order to apply them, one has to use the sf_weight[region] variable instead
      eg. sf_weight['t']
     */

    // Baseline cuts
    // Additionally, let's apply the trigger selection
    // since the weight contains the trigger scaling in MC
    // no specific region, so don't apply scale factors
    // Especially for comparison plots with Changgi
    // Alternatively, could apply SF of the Signal regio

    //double w = weight; // No scale factor applied
    //double w = sf_weight['t']; // Scale factors applied for the Signal region




    //  // For example this applies the first three cuts in signal region
    //  // HLT, ele/mu veto
    //  if (apply_ncut('t', 3)) {
    //    h_jet1_pt->Fill(d.jetsAK4.Pt[iJet[0]], w);
    //    h_jet2_pt->Fill(d.jetsAK4.Pt[iJet[1]], w);
    //    h_jet3_pt->Fill(d.jetsAK4.Pt[iJet[2]], w);
    //  }

    /*
       Other examples to use analysis_cuts object
       if (apply_cut("S","1W"))                          --> 1 Cut from S region
       if (apply_cut("W","1Wpre"))                       --> 1 Cut from W region
       if (apply_all_cuts("T"))                          --> All cuts in T region
       if (apply_all_cuts_except("Q", "mDPhi<0.25"))     --> N-1 cut
       if (apply_all_cuts_except("S", {"0Ele", "0Mu" })) --> S without Lep veto
       But be aware: Whatever is defined in the baseline_cuts will apply to all histograms
       Also if you use skimmed ntuples (very likely) then those cuts are already applied
       This is because unskimmed ntuple is 4.3 TB in size, and we cannot have them on EOS
    */

  // Vary systematics and save each variation into a different historgam
  //Switch on settings.varySystematics to be effective



  if (apply_all_cuts('P')) h_MR_R2->Fill(MR, R2, weight);
  if (apply_all_cuts('P')) h_R2->Fill(R2, weight);
  if (apply_all_cuts('P')) h_MR->Fill(MR, weight);
w = sf_weight['S'];
   if (apply_all_cuts('S')) {
          if(nJet>=3){
              h_S_MRR2_nj3 -> Fill(MR, R2, w);
          }
          if(nJet>=3 && nJet<5){
              h_S_MRR2_nj35 -> Fill(MR, R2, w);
          }
          if(nJet>5){
              h_S_MRR2_nj5 -> Fill(MR, R2, w);
          }
      }

   if (apply_all_cuts('S')) h_njet_S->Fill(nJet,w);
  // if (apply_all_cuts('S')) h_S_HT -> Fill(AK8_Ht, w);
   if (apply_all_cuts('S')) h_S_MET->Fill(data.MET_pt,w);
   if (apply_all_cuts('S')) h_AK8_jet1_pt_S->Fill(data.FatJet[iJetAK8[0]].pt, w);
   if (apply_all_cuts('S')) h_AK8_jet1_Eta_S->Fill(data.FatJet[iJetAK8[0]].eta, w);
   if (apply_all_cuts_except('S',"mDPhi" )) h_DPhi_S->Fill(dPhiRazor,w);
   if (apply_all_cuts('S')) h_MTR_S->Fill(MTR, w);
   if (apply_all_cuts('S')) h_S_MRR2->Fill(MR, R2, w);
   if (apply_all_cuts('S')) h_MR_S->Fill(MR, w);
   if (apply_all_cuts('S')) h_R2_S->Fill(R2, w);
   if (apply_all_cuts('S')) h_MT_S->Fill(MT, w);

   if (apply_cut('S',"HLT")) {
      h_njet   ->Fill(nJet,        w);
      h_nTop     ->Fill(nHadTopTag,  w);
      h_ht_AK4->Fill(AK4_Ht, w);
      h_ht_AK8->Fill(AK8_Ht, w);
      h_ht_S->Fill(AK4_Ht, w);
    }
    if (apply_all_cuts('S')) h_njet_S_anaW->Fill(nJet, w);
    if (apply_all_cuts('S')) h_S_MET->Fill(data.MET_pt,w);
    if (apply_all_cuts('S')) h_MR_S_anaW->Fill(MR, w);
    if (apply_all_cuts('S')) h_R2_S_anaW->Fill(R2, w);
    if (apply_all_cuts('S')) h_AK8_jet1_pt_S_anaW->Fill(data.FatJet[iJetAK8[0]].pt, w);
    if (apply_all_cuts('S')) h_AK8_jet1_Eta_S_anaW->Fill(data.FatJet[iJetAK8[0]].eta, w);
    if (apply_cut('S',"HLT")) {
          h_nb_anaW     ->Fill(nMediumBTag, w);
          h_nw_anaW     ->Fill(nTightWTag,  w);
          h_ht_S_anaW->Fill(AK4_Ht, w);
        }

w = sf_weight['s'];
      if (apply_all_cuts('s')){
          if(nJet>=3){
              h_s_MRR2_nj3 -> Fill(MR, R2, w);
          }
          if(nJet>=3 && nJet<5){
              h_s_MRR2_nj35 -> Fill(MR, R2, w);
          }
          if(nJet>5){
              h_s_MRR2_nj5 -> Fill(MR, R2, w);
          }
      }
   if (apply_all_cuts('s')) h_s_MET->Fill(data.MET_pt,w);
   if (apply_all_cuts('s')) h_AK8_jet1_pt_s->Fill(data.FatJet[iJetAK8[0]].pt, w);
   if (apply_all_cuts('s')) h_AK8_jet1_Eta_s->Fill(data.FatJet[iJetAK8[0]].eta, w);
   if (apply_all_cuts_except('s',"InvmDPhi" )) h_DPhi_s->Fill(dPhiRazor,w);
   if (apply_all_cuts('s')) h_MTR_s->Fill(MTR, w);
   if (apply_all_cuts('s')) h_s_MRR2->Fill(MR, R2, w);
   if (apply_all_cuts('s')) h_MR_s->Fill(MR, w);
   if (apply_all_cuts('s')) h_R2_s->Fill(R2, w);
   if (apply_all_cuts('s')) h_MT_s->Fill(MT, w);
   if (apply_all_cuts('s')) h_AK8_jet1_pt_s_anaW->Fill(data.FatJet[iJetAK8[0]].pt, w);
   if (apply_all_cuts('s')) h_AK8_jet1_Eta_s_anaW->Fill(data.FatJet[iJetAK8[0]].eta, w);
   if (apply_all_cuts('s')) h_MR_s_anaW->Fill(MR, w);
   if (apply_all_cuts('s')) h_R2_s_anaW->Fill(R2, w);
   if (apply_all_cuts('s')) h_s_MET->Fill(data.MET_pt,w);
w = sf_weight['W'];
      if (apply_all_cuts('W')){
          if(nJet>=3){
              h_W_MRR2_nj3 -> Fill(MR, R2, w);
          }
          if(nJet>=3 && nJet<5){
              h_W_MRR2_nj35 -> Fill(MR, R2, w);
          }
          if(nJet>5){
              h_W_MRR2_nj5 -> Fill(MR, R2, w);
          }
      }
   if (apply_cut('W',"HLT")) h_ht_W->Fill(AK4_Ht, w); // Calculated in AnalysisBase.h
   if (apply_all_cuts('W')) h_njet_W->Fill(nJet,w);
   if (apply_all_cuts('W')) h_W_MET->Fill(data.MET_pt,w);
   if (apply_all_cuts('W')) h_AK8_jet1_pt_W->Fill(data.FatJet[iJetAK8[0]].pt, w);
   if (apply_all_cuts('W')) h_AK8_jet1_Eta_W->Fill(data.FatJet[iJetAK8[0]].eta, w);
   if (apply_all_cuts_except('W',"mDPhi" )) h_DPhi_W->Fill(dPhiRazor,w);
   if (apply_all_cuts('W')) h_MTR_W->Fill(MTR, w);
   if (apply_all_cuts('W')) h_W_MRR2->Fill(MR, R2, w);
   if (apply_all_cuts('W')) h_MR_W->Fill(MR, w);
   if (apply_all_cuts('W')) h_R2_W->Fill(R2, w);
   if (apply_cut('W',"HLT")) h_ht_W_anaW->Fill(AK4_Ht, w); // Calculated in AnalysisBase.h
   if (apply_all_cuts('W')) h_MR_W_anaW->Fill(MR, w);
   if (apply_all_cuts('W')) h_R2_W_anaW->Fill(R2, w);
   if (apply_all_cuts('W')) h_njet_W_anaW->Fill(nJet, w);
   if (apply_all_cuts('W')) h_W_MET->Fill(data.MET_pt,w);
   if (apply_all_cuts('W')) h_AK8_jet1_pt_W_anaW->Fill(data.FatJet[iJetAK8[0]].pt, w);
   if (apply_all_cuts('W')) h_AK8_jet1_Eta_W_anaW->Fill(data.FatJet[iJetAK8[0]].eta, w);

w = sf_weight['Q'];
      if (apply_all_cuts('Q')){
          if(nJet>=3){
              h_Q_MRR2_nj3 -> Fill(MR, R2, w);
          }
          if(nJet>=3 && nJet<5){
              h_Q_MRR2_nj35 -> Fill(MR, R2, w);
          }
          if(nJet>5){
              h_Q_MRR2_nj5 -> Fill(MR, R2, w);
          }
      }
   if (apply_all_cuts('Q')) h_njet_Q->Fill(nJet,w);
   if (apply_all_cuts('Q')) h_Q_MET->Fill(data.MET_pt,w);
   if (apply_all_cuts('Q')) h_AK8_jet1_pt_Q->Fill(data.FatJet[iJetAK8[0]].pt, w);
   if (apply_all_cuts('Q')) h_AK8_jet1_Eta_Q->Fill(data.FatJet[iJetAK8[0]].eta, w);
   if (apply_cut('Q',"HLT")) h_ht_Q->Fill(AK4_Ht, w); // Calculated in AnalysisBase.h
   if (apply_all_cuts_except('Q',"InvmDPhi" )) h_DPhi_Q->Fill(dPhiRazor,w);
   if (apply_all_cuts('Q')) h_MTR_Q->Fill(MTR, w);
   if (apply_all_cuts('Q')) h_Q_MRR2->Fill(MR, R2, w);
   if (apply_all_cuts('Q')) h_MR_Q->Fill(MR, w);
   if (apply_all_cuts('Q')) h_R2_Q->Fill(R2, w);
   if (apply_all_cuts('Q')) h_MT_Q->Fill(MT, w);
   if (apply_all_cuts('Q')) h_AK8_jet1_pt_Q_anaW->Fill(data.FatJet[iJetAK8[0]].pt, w);
   if (apply_all_cuts('Q')) h_AK8_jet1_Eta_Q_anaW->Fill(data.FatJet[iJetAK8[0]].eta, w);
   if (apply_all_cuts('Q')) h_MR_Q_anaW->Fill(MR, w);
   if (apply_all_cuts('Q')) h_R2_Q_anaW->Fill(R2, w);
   if (apply_all_cuts('Q')) h_njet_Q_anaW->Fill(nJet, w);
   if (apply_all_cuts('Q')) h_Q_MET->Fill(data.MET_pt,w);
   if (apply_cut('Q',"HLT")) h_ht_Q_anaW->Fill(AK4_Ht, w); // Calculated in AnalysisBase.h

w = sf_weight['q'];
      if (apply_all_cuts('q')){
          if(nJet>=3){
              h_q_MRR2_nj3 -> Fill(MR, R2, w);
          }
          if(nJet>=3 && nJet<5){
              h_q_MRR2_nj35 -> Fill(MR, R2, w);
          }
          if(nJet>5){
              h_q_MRR2_nj5 -> Fill(MR, R2, w);
          }
      }
   if (apply_all_cuts('q')) h_q_MET->Fill(data.MET_pt,w);
   if (apply_all_cuts('q')) h_AK8_jet1_pt_q->Fill(data.FatJet[iJetAK8[0]].pt, w);
   if (apply_all_cuts('q')) h_AK8_jet1_Eta_q->Fill(data.FatJet[iJetAK8[0]].eta, w);
   if (apply_all_cuts_except('q',"mDPhi" )) h_DPhi_q->Fill(dPhiRazor,w);
   if (apply_all_cuts('q')) h_MTR_q->Fill(MTR, w);
   if (apply_all_cuts('q')) h_q_MRR2->Fill(MR, R2, w);
   if (apply_all_cuts('q')) h_MR_q->Fill(MR, w);
   if (apply_all_cuts('q')) h_R2_q->Fill(R2, w);
   if (apply_all_cuts('q')) h_MT_q->Fill(MT, w);
   if (apply_all_cuts('q')) h_MR_q_anaW->Fill(MR, w);
   if (apply_all_cuts('q')) h_R2_q_anaW->Fill(R2, w);
   if (apply_all_cuts('q')) h_AK8_jet1_pt_q_anaW->Fill(data.FatJet[iJetAK8[0]].pt, w);
   if (apply_all_cuts('q')) h_AK8_jet1_Eta_q_anaW->Fill(data.FatJet[iJetAK8[0]].eta, w);

w = sf_weight['T'];
      if (apply_all_cuts('T')){
          if(nJet>=3){
              h_T_MRR2_nj3 -> Fill(MR, R2, w);
          }
          if(nJet>=3 && nJet<5){
              h_T_MRR2_nj35 -> Fill(MR, R2, w);
          }
          if(nJet>5){
              h_T_MRR2_nj5 -> Fill(MR, R2, w);
          }
      }
   if (apply_all_cuts('T')) h_njet_T->Fill(nJet,w);
   if (apply_all_cuts('T')) h_T_MET->Fill(data.MET_pt,w);
   if (apply_all_cuts('T')) h_AK8_jet1_pt_T->Fill(data.FatJet[iJetAK8[0]].pt, w);
   if (apply_all_cuts('T')) h_AK8_jet1_Eta_T->Fill(data.FatJet[iJetAK8[0]].eta, w);
   if (apply_cut('T',"HLT")) h_ht_T->Fill(AK4_Ht, w); // Calculated in AnalysisBase.h
   if (apply_all_cuts_except('T',"mDPhi" )) h_DPhi_T->Fill(dPhiRazor,w);
   if (apply_all_cuts('T')) h_MTR_T->Fill(MTR, w);
   if (apply_all_cuts('T')) h_T_MRR2->Fill(MR, R2, w);
   if (apply_all_cuts('T')) h_MR_T->Fill(MR, w);
   if (apply_all_cuts('T')) h_R2_T->Fill(R2, w);
   if (apply_all_cuts_except('T',"MT" )) h_MT_T->Fill(MT, w);
   if (apply_all_cuts('T')) h_MR_T_anaW->Fill(MR, w);
   if (apply_all_cuts('T')) h_R2_T_anaW->Fill(R2, w);
   if (apply_all_cuts('T')) h_njet_T_anaW->Fill(nJet, w);
   if (apply_all_cuts('T')) h_T_MET->Fill(data.MET_pt,w);
   if (apply_all_cuts('T')) h_AK8_jet1_pt_T_anaW->Fill(data.FatJet[iJetAK8[0]].pt, w);
   if (apply_all_cuts('T')) h_AK8_jet1_Eta_T_anaW->Fill(data.FatJet[iJetAK8[0]].eta, w);
   if (apply_cut('T',"HLT")) h_ht_T_anaW->Fill(AK4_Ht, w); // Calculated in AnalysisBase.h

w = sf_weight['Z'];

   if (apply_all_cuts('Z')){

          if(nJet>=3){
              h_Z_MRR2_nj3 -> Fill(MR, R2, w);
          }
          if(nJet>=3 && nJet<5){
              h_Z_MRR2_nj35 -> Fill(MR, R2, w);
          }
          if(nJet>5){
              h_Z_MRR2_nj5 -> Fill(MR, R2, w);
        }
      }
   if (apply_cut('Z',"HLT")) h_ht_Z->Fill(AK4_Ht, w); // Calculated in AnalysisBase.h
   if (apply_all_cuts('Z')) h_njet_Z->Fill(nJet,w);
   if (apply_all_cuts('Z')) h_Z_MET->Fill(data.MET_pt,w);
   if (apply_all_cuts('Z')) h_AK8_jet1_pt_Z->Fill(data.FatJet[iJetAK8[0]].pt, w);
   if (apply_all_cuts('Z')) h_AK8_jet1_Eta_Z->Fill(data.FatJet[iJetAK8[0]].eta, w);
   if (apply_all_cuts_except('Z',"mDPhill" )) h_DPhi_Z->Fill(dPhiRazor,w);
   if (apply_all_cuts('Z')) h_MR_Z->Fill(MR, w);
   if (apply_all_cuts('Z')) h_R2_Z->Fill(R2_ll, w);
   if (apply_all_cuts('Z')) h_Z_MRR2-> Fill(MR, R2_ll, w);
   if (apply_all_cuts('Z'))h_MTR_Z->Fill(MTR, w);
   if (apply_all_cuts_except('Z',"Mll" )) h_MT_Z->Fill(MT, w);
   if (apply_cut('Z',"HLT")) h_ht_Z_anaW->Fill(AK4_Ht, w); // Calculated in AnalysisBase.h
   if (apply_all_cuts('Z')) h_MR_Z_anaW->Fill(MR, w);
   if (apply_all_cuts('Z')) h_R2_Z_anaW->Fill(R2_ll, w);
   if (apply_all_cuts('Z')) h_njet_Z_anaW->Fill(nJet, w);
   if (apply_all_cuts('Z')) h_Z_MET->Fill(data.MET_pt,w);
   if (apply_all_cuts('Z')) h_AK8_jet1_pt_Z_anaW->Fill(data.FatJet[iJetAK8[0]].pt, w);
   if (apply_all_cuts('Z')) h_AK8_jet1_Eta_Z_anaW->Fill(data.FatJet[iJetAK8[0]].eta, w);

w = sf_weight['L'];

   if (apply_all_cuts('L')) h_MR_L->Fill(MR, w);
   if (apply_all_cuts('L')) h_R2_L->Fill(R2_1l, w);
   if (apply_all_cuts('L')) h_L_MRR2-> Fill(MR, R2_1l, w);
   if (apply_all_cuts('L')) h_njet_L->Fill(nJet,w);
   if (apply_all_cuts('L')) h_MR_L_anaW->Fill(MR, w);
   if (apply_all_cuts('L')) h_R2_L_anaW->Fill(R2_1l, w);
   if (apply_all_cuts('L')) h_MRR2_L_anaW-> Fill(MR, R2_1l, w);
   if (apply_all_cuts('L')) h_njet_L_anaW->Fill(nJet, w);

w = sf_weight['G'];
   if (apply_all_cuts('G')) h_G_MRR2-> Fill(MR_pho, R2_pho, w);
   if (apply_all_cuts('G')) h_MR_G->Fill(MR_pho, w);
   if (apply_all_cuts('G')) h_R2_G->Fill(R2_pho, w);
   if (apply_all_cuts('G')) h_njet_G->Fill(nJet, w);
}

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
