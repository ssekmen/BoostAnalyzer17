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
    if ( (data.FatJet[i].jetId == 2 || data.FatJet[i].jetId == 6) && std::abs(data.FatJet[i].eta)  <  JET_AK8_ETA_CUT ) { NJetAK8++; }    
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

  // preselection
  analysis_cuts['P'].push_back({ .name="1JetAK8",    .func = []    { return nJetAK8>=1;                      }}); // Similar to pt>200, one AK8 jet has pt>200
  analysis_cuts['P'].push_back({ .name="NJet",       .func = []    { return nJet>=3;                          }}); // Separate cut, so one can exclude (N-1)
  analysis_cuts['P'].push_back({ .name="MR_R2",      .func = [&d]  { return MR>=800 && R2>=0.08;     }});
  analysis_cuts['P'].push_back({ .name="HLT",        .func = [this,&d]  { return isData ? d.HLT_PFHT1050==1 || d.HLT_AK8PFHT800_TrimMass50==1 || d.HLT_PFHT500_PFMET100_PFMHT100_IDTight==1 || d.HLT_AK8PFJet450==1 || d.HLT_AK8PFJet400_TrimMass30==1 : 1; }});
  
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
  //analysis_cuts['Q'].push_back({ .name="InvmDPhi",.func = []     { return minDeltaPhi<0.3;                  }});
  analysis_cuts['Q'].push_back({ .name="InvmDPhi",   .func = []    { return dPhiRazor>=2.8;                   }});

  // Q': Dphi Control region of QCD enriched sample
  analysis_cuts['q'].push_back({ .name="1JetAK8",    .func = []    { return nJetAK8>=1;                       }}); // Similar to pt>200, one AK8 jet has pt>200
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
  analysis_cuts['q'].push_back({ .name="mDPhi",      .func = []    { return dPhiRazor<2.8;                    }});

  // T: Top enriched control sample
  analysis_cuts['T'].push_back({ .name="1JetAK8",    .func = []    { return nJetAK8>=1;                       }}); // Similar to pt>200, one AK8 jet has pt>200
  analysis_cuts['T'].push_back({ .name="NJet",       .func = []    { return nJet>=3;                          }});
  analysis_cuts['T'].push_back({ .name="MR_R2",      .func = [&d]  { return MR>=800 && R2>=0.08;  }});
  analysis_cuts['T'].push_back({ .name="HLT",   .func = [this,&d]  { return isData ? d.HLT_PFHT1050==1 || d.HLT_AK8PFHT800_TrimMass50==1 || d.HLT_PFHT500_PFMET100_PFMHT100_IDTight==1 || d.HLT_AK8PFJet450==1 || d.HLT_AK8PFJet400_TrimMass30==1 : 1; }});
  //analysis_cuts['T'].push_back({ .name="HLT",   .func = [this,&d]  { return d.HLT_PFHT1050==1 || d.HLT_AK8PFHT800_TrimMass50==1 || d.HLT_PFHT500_PFMET100_PFMHT100_IDTight==1 || d.HLT_AK8PFJet450==1 || d.HLT_AK8PFJet400_TrimMass30==1; }});
  analysis_cuts['T'].push_back({ .name="1Lep",       .func = []    { return nLepVeto==1;                      }});
  analysis_cuts['T'].push_back({ .name="1b",         .func = []    { return nMediumBTag>=1;                   }});
  analysis_cuts['T'].push_back({ .name="1W",         .func = []    { return nTightWTag>=1;                    }});
  analysis_cuts['T'].push_back({ .name="mDPhi",      .func = []    { return dPhiRazor<2.8;                    }});
  analysis_cuts['T'].push_back({ .name="MT",         .func = []    { return MT_vetolep<100;                   }});

  // W: W enriched control sample
  analysis_cuts['W'].push_back({ .name="1JetAK8",    .func = []    { return nJetAK8>=1;                       }}); // Similar to pt>200, one AK8 jet has pt>200
  analysis_cuts['W'].push_back({ .name="NJet",       .func = []    { return nJet>=3;                          }});
  analysis_cuts['W'].push_back({ .name="MR_R2",      .func = [&d]  { return MR>=800 && R2>=0.08;  }});
  analysis_cuts['W'].push_back({ .name="HLT",   .func = [this,&d]  { return isData ? d.HLT_PFHT1050==1 || d.HLT_AK8PFHT800_TrimMass50==1 || d.HLT_PFHT500_PFMET100_PFMHT100_IDTight==1 || d.HLT_AK8PFJet450==1 || d.HLT_AK8PFJet400_TrimMass30==1 : 1; }});
  //analysis_cuts['W'].push_back({ .name="HLT",   .func = [this,&d]  { return d.HLT_PFHT1050==1 || d.HLT_AK8PFHT800_TrimMass50==1 || d.HLT_PFHT500_PFMET100_PFMHT100_IDTight==1 || d.HLT_AK8PFJet450==1 || d.HLT_AK8PFJet400_TrimMass30==1; }});
  analysis_cuts['W'].push_back({ .name="1Lep",       .func = []    { return nLepVeto==1;                      }});
  analysis_cuts['W'].push_back({ .name="0b",         .func = []    { return nLooseBTag==0;                    }});
  analysis_cuts['W'].push_back({ .name="1mW",        .func = []    { return nWMassTag>=1;                     }});
  analysis_cuts['W'].push_back({ .name="mDPhi",      .func = []    { return dPhiRazor<2.8;                    }});
  analysis_cuts['W'].push_back({ .name="MT",         .func = []    { return MT_vetolep>=30 && MT_vetolep<100; }});

  // L: 1-lepton invisible control sample with veto lepton
  analysis_cuts['L'].push_back({ .name="1JetAK8",    .func = []    { return nJetAK8>=1;                       }});
  analysis_cuts['L'].push_back({ .name="NJet",       .func = []    { return nJet>=3;                          }});
  analysis_cuts['L'].push_back({ .name="MR",         .func = [&d]  { return MR>=800;                          }});
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
  analysis_cuts['w'].push_back({ .name="MR",         .func = [&d]  { return MR>=300;                          }}); 
  analysis_cuts['w'].push_back({ .name="R2",         .func = [&d]  { return R2>=0.15;                         }}); 
  analysis_cuts['w'].push_back({ .name="HLT",   .func = [this,&d]  { return isData ? d.HLT_PFHT1050==1 || d.HLT_AK8PFHT800_TrimMass50==1 || d.HLT_PFHT500_PFMET100_PFMHT100_IDTight==1 || d.HLT_AK8PFJet450==1 || d.HLT_AK8PFJet400_TrimMass30==1 : 1; }}); 
  //analysis_cuts['w'].push_back({ .name="HLT",   .func = [this,&d]  { return d.HLT_PFHT1050==1 || d.HLT_AK8PFHT800_TrimMass50==1 || d.HLT_PFHT500_PFMET100_PFMHT100_IDTight==1 || d.HLT_AK8PFJet450==1 || d.HLT_AK8PFJet400_TrimMass30==1; }});
  analysis_cuts['w'].push_back({ .name="1Lep",       .func = []    { return nLepSelect==1;                    }}); 
  analysis_cuts['w'].push_back({ .name="MET",        .func = [&d]  { return d.MET_pt>=30;                     }}); 
  analysis_cuts['w'].push_back({ .name="MT",         .func = []    { return MT>=30 && MT<100;                 }}); 
  analysis_cuts['w'].push_back({ .name="0b",         .func = []    { return nLooseBTag==0;                    }}); 

  // F: Fake rate measurement region
  analysis_cuts['F'].push_back({ .name="1JetAK8",    .func = []    { return nJetAK8>=1;                       }}); 
  analysis_cuts['F'].push_back({ .name="MR",         .func = [&d]  { return MR>=800;                          }}); 
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
  analysis_cuts['f'].push_back({ .name="MR",         .func = [&d]  { return MR>=800;                          }}); 
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

//____________________________________________________
//          Analysis Specific Scale factors
//    (Defined for each search region separately)

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
TH2D *h2_HT_TrigEff_HLT_AK8PFJet450;
TH2D *h2_HT_TrigEff_HLT_AK8PFJet400_TrimMass30;
TH2D *h2_HT_TrigEff_HLT_AK8PFHT800_TrimMass50;
TH2D *h2_HT_TrigEff_HLT_PFHT1050;
TH2D *h2_HT_TrigEff_HLT_PFHT500_PFMET100_PFMHT100_IDTight;

TH2D *h2_MET_TrigEff_HLT_AK8PFJet450;
TH2D *h2_MET_TrigEff_HLT_AK8PFJet400_TrimMass30;
TH2D *h2_MET_TrigEff_HLT_AK8PFHT800_TrimMass50;
TH2D *h2_MET_TrigEff_HLT_PFHT1050;
TH2D *h2_MET_TrigEff_HLT_PFHT500_PFMET100_PFMHT100_IDTight;

TH3D *h3_HT_MET_TrigEff_HLT_AK8PFJet450;
TH3D *h3_HT_MET_TrigEff_HLT_AK8PFJet400_TrimMass30;
TH3D *h3_HT_MET_TrigEff_HLT_AK8PFHT800_TrimMass50;
TH3D *h3_HT_MET_TrigEff_HLT_PFHT1050;
TH3D *h3_HT_MET_TrigEff_HLT_PFHT500_PFMET100_PFMHT100_IDTight;

TH3D *h3_R2_MR;
TH3D *h3_R2_MR_TrigEff_HLT_AK8PFJet450;
TH3D *h3_R2_MR_TrigEff_HLT_AK8PFJet400_TrimMass30;
TH3D *h3_R2_MR_TrigEff_HLT_AK8PFHT800_TrimMass50;
TH3D *h3_R2_MR_TrigEff_HLT_PFHT1050;
TH3D *h3_R2_MR_TrigEff_HLT_PFHT500_PFMET100_PFMHT100_IDTight;

TH2D* h2_R2_MR;
TH2D *h2_R2_MR_HLT_AK8PFJet450;
TH2D *h2_R2_MR_HLT_AK8PFJet400_TrimMass30;
TH2D *h2_R2_MR_HLT_AK8PFHT800_TrimMass50;
TH2D *h2_R2_MR_HLT_PFHT1050;
TH2D *h2_R2_MR_HLT_PFHT500_PFMET100_PFMHT100_IDTight;

//The extra histos
TH2D *h2_R2_MR_HLT_AK8PFJet450Extra;
TH2D *h2_R2_MR_HLT_AK8PFJet400_TrimMass30Extra;
TH2D *h2_R2_MR_HLT_AK8PFHT800_TrimMass50Extra;
TH2D *h2_R2_MR_HLT_PFHT1050Extra;

TH2D *h2_HT_TrigEffExtra_HLT_AK8PFJet450;
TH2D *h2_HT_TrigEffExtra_HLT_AK8PFJet400_TrimMass30;
TH2D *h2_HT_TrigEffExtra_HLT_AK8PFHT800_TrimMass50;
TH2D *h2_HT_TrigEffExtra_HLT_PFHT1050;

TH2D *h2_MET_TrigEffExtra_HLT_AK8PFJet450;
TH2D *h2_MET_TrigEffExtra_HLT_AK8PFJet400_TrimMass30;
TH2D *h2_MET_TrigEffExtra_HLT_AK8PFHT800_TrimMass50;
TH2D *h2_MET_TrigEffExtra_HLT_PFHT1050;

TH3D *h3_HT_MET_TrigEffExtra_HLT_AK8PFJet450;
TH3D *h3_HT_MET_TrigEffExtra_HLT_AK8PFJet400_TrimMass30;
TH3D *h3_HT_MET_TrigEffExtra_HLT_AK8PFHT800_TrimMass50;
TH3D *h3_HT_MET_TrigEffExtra_HLT_PFHT1050;

TH3D *h3_R2_MR_TrigEffExtra_HLT_AK8PFJet450;
TH3D *h3_R2_MR_TrigEffExtra_HLT_AK8PFJet400_TrimMass30;
TH3D *h3_R2_MR_TrigEffExtra_HLT_AK8PFHT800_TrimMass50;
TH3D *h3_R2_MR_TrigEffExtra_HLT_PFHT1050;

// Combinations
TH2D *h2_HT_TrigEff_HLT_Combined1;
TH2D *h2_MET_TrigEff_HLT_Combined1;
TH3D *h3_HT_MET_TrigEff_HLT_Combined1;
TH3D *h3_R2_MR_TrigEff_HLT_Combined1;
TH2D *h2_R2_MR_HLT_Combined1;

TH2D *h2_HT_TrigEff_HLT_Combined2;
TH2D *h2_MET_TrigEff_HLT_Combined2;
TH3D *h3_HT_MET_TrigEff_HLT_Combined2;
TH3D *h3_R2_MR_TrigEff_HLT_Combined2;
TH2D *h2_R2_MR_HLT_Combined2;

// AK8 mass and pt and eta efficiencies
TH2D *h2_TrigEff_HLT_Combined2_mass;
TH2D *h2_TrigEff_HLT_Combined2_pt;
TH2D *h2_TrigEff_HLT_Combined2_eta;



//_______________________________________________________
//              Define Histograms here
void
Analysis::init_analysis_histos(const unsigned int& syst_nSyst, const unsigned int& syst_index)
{
  int nbnHT = 10;
  //Double_t bn_HTtmp[] = {400.,500.,600.,700.,800.,900.,1000.,1500.,10000.};
  Double_t bn_HTtmp[] = {400.,500.,600.,700.,800.,900.,1000.,1100.,1200.,1500.,2000.}; 
  Double_t* bnHT = 0;
  bnHT = getVariableBinEdges(nbnHT+1,bn_HTtmp);
  

  h2_HT_TrigEff_HLT_AK8PFJet450 = new TH2D("h2_HT_TrigEff_HLT_AK8PFJet450", ";H_{T} (GeV);Trigger passed?",nbnHT,bnHT,2,-0.5,1.5);
  h2_HT_TrigEff_HLT_AK8PFJet400_TrimMass30 = new TH2D("h2_HT_TrigEff_HLT_AK8PFJet400_TrimMass30", ";H_{T} (GeV);Trigger passed?",nbnHT,bnHT,2,-0.5,1.5);
  h2_HT_TrigEff_HLT_AK8PFHT800_TrimMass50 = new TH2D("h2_HT_TrigEff_HLT_AK8PFHT800_TrimMass50", ";H_{T} (GeV);Trigger passed?",nbnHT,bnHT,2,-0.5,1.5);
  h2_HT_TrigEff_HLT_PFHT1050 = new TH2D("h2_HT_TrigEff_HLT_PFHT1050", ";H_{T} (GeV);Trigger passed?",nbnHT,bnHT,2,-0.5,1.5);
  h2_HT_TrigEff_HLT_PFHT500_PFMET100_PFMHT100_IDTight = new TH2D("h2_HT_TrigEff_HLT_PFHT500_PFMET100_PFMHT100_IDTight", ";H_{T} (GeV);Trigger passed?",nbnHT,bnHT,2,-0.5,1.5);
  
  int nbnMET = 6;
  //int nbnMET = 16;
  Double_t bn_METtmp[] = {0.,100.,200.,300.,400.,600.,2000.};
  //Double_t bn_METtmp[] =  {0.,50.,100.,150.,200.,250.,300.,350.,400.,450.,500.,600.,700.,800.,1000.,2000.,10000.};
  Double_t* bnMET = 0;
  bnMET = getVariableBinEdges(nbnMET+1,bn_METtmp);
  
  h2_MET_TrigEff_HLT_AK8PFJet450 = new TH2D("h2_MET_TrigEff_HLT_AK8PFJet450", ";MET (GeV);Trigger passed?",nbnMET,bnMET,2,-0.5,1.5);
  h2_MET_TrigEff_HLT_AK8PFJet400_TrimMass30 = new TH2D("h2_MET_TrigEff_HLT_AK8PFJet400_TrimMass30", ";MET (GeV);Trigger passed?",nbnMET,bnMET,2,-0.5,1.5);
  h2_MET_TrigEff_HLT_AK8PFHT800_TrimMass50 = new TH2D("h2_MET_TrigEff_HLT_AK8PFHT800_TrimMass50", ";MET (GeV);Trigger passed?",nbnMET,bnMET,2,-0.5,1.5);
  h2_MET_TrigEff_HLT_PFHT1050 = new TH2D("h2_MET_TrigEff_HLT_PFHT1050", ";MET (GeV);Trigger passed?",nbnMET,bnMET,2,-0.5,1.5);
  h2_MET_TrigEff_HLT_PFHT500_PFMET100_PFMHT100_IDTight = new TH2D("h2_MET_TrigEff_HLT_PFHT500_PFMET100_PFMHT100_IDTight", ";MET (GeV);Trigger passed?",nbnMET,bnMET,2,-0.5,1.5);
  
  Double_t bn_Booltmp[] = {-0.5,0.5,1.5};
  Double_t* bn_Bool = 0;
  bn_Bool = getVariableBinEdges(3,bn_Booltmp);
  
  
  h3_HT_MET_TrigEff_HLT_AK8PFJet450 = new TH3D("h3_HT_MET_TrigEff_HLT_AK8PFJet450", ";MET (GeV);H_{T} (GeV);Trigger passed?",nbnMET,bnMET,nbnHT,bnHT,2,bn_Bool);
  h3_HT_MET_TrigEff_HLT_AK8PFJet400_TrimMass30 = new TH3D("h3_HT_MET_TrigEff_HLT_AK8PFJet400_TrimMass30", ";MET (GeV);H_{T} (GeV);Trigger passed?",nbnMET,bnMET,nbnHT,bnHT,2,bn_Bool);
  h3_HT_MET_TrigEff_HLT_AK8PFHT800_TrimMass50  = new TH3D("h3_HT_MET_TrigEff_HLT_AK8PFHT800_TrimMass50", ";MET (GeV);H_{T} (GeV);Trigger passed?",nbnMET,bnMET,nbnHT,bnHT,2,bn_Bool);
  h3_HT_MET_TrigEff_HLT_PFHT1050 = new TH3D("h3_HT_MET_TrigEff_HLT_PFHT1050", ";MET (GeV);H_{T} (GeV);Trigger passed?",nbnMET,bnMET,nbnHT,bnHT,2,bn_Bool);
  h3_HT_MET_TrigEff_HLT_PFHT500_PFMET100_PFMHT100_IDTight = new TH3D("h3_HT_MET_TrigEff_HLT_PFHT500_PFMET100_PFMHT100_IDTight", ";MET (GeV);H_{T} (GeV);Trigger passed?",nbnMET,bnMET,nbnHT,bnHT,2,bn_Bool);
  
  int nbn_MR = 7;
  Double_t bn_MR_tmp[] = {0.,600.,800.,1000.,1200.,1600.,2000.,4000.};
  Double_t* bn_MR = 0;
  bn_MR = getVariableBinEdges(nbn_MR+1,bn_MR_tmp);

  int nbn_R2 = 7;
  Double_t bn_R2_tmp[] = {0.,0.04,0.08,0.12,0.16,0.24,0.4,1.5};
  Double_t* bn_R2 = 0;
  bn_R2 = getVariableBinEdges(nbn_R2+1,bn_R2_tmp);
  
  h3_R2_MR = new TH3D("h3_R2_MR", ";M_{R} (GeV);R^{2};Any trigger passed?",nbn_MR,bn_MR,nbn_R2,bn_R2,2,bn_Bool);
  h3_R2_MR_TrigEff_HLT_AK8PFJet450 = new TH3D("h3_R2_MR_TrigEff_HLT_AK8PFJet450", ";M_{R} (GeV);R^{2};Trigger passed?",nbn_MR,bn_MR,nbn_R2,bn_R2,2,bn_Bool);
  h3_R2_MR_TrigEff_HLT_AK8PFJet400_TrimMass30 = new TH3D("h3_R2_MR_TrigEff_HLT_AK8PFJet400_TrimMass30", ";M_{R} (GeV);R^{2};Trigger passed?",nbn_MR,bn_MR,nbn_R2,bn_R2,2,bn_Bool);
  h3_R2_MR_TrigEff_HLT_AK8PFHT800_TrimMass50 = new TH3D("h3_R2_MR_TrigEff_HLT_AK8PFHT800_TrimMass50", ";M_{R} (GeV);R^{2};Trigger passed?",nbn_MR,bn_MR,nbn_R2,bn_R2,2,bn_Bool);
  h3_R2_MR_TrigEff_HLT_PFHT1050 = new TH3D("h3_R2_MR_TrigEff_HLT_PFHT1050", ";M_{R} (GeV);R^{2};Trigger passed?",nbn_MR,bn_MR,nbn_R2,bn_R2,2,bn_Bool);
  h3_R2_MR_TrigEff_HLT_PFHT500_PFMET100_PFMHT100_IDTight = new TH3D("h3_R2_MR_TrigEff_HLT_PFHT500_PFMET100_PFMHT100_IDTight", ";M_{R} (GeV);R^{2};Trigger passed?",nbn_MR,bn_MR,nbn_R2,bn_R2,2,bn_Bool);
  
  h2_R2_MR = new TH2D("h2_R2_MR", ";M_{R} (GeV);R^{2}",nbn_MR,bn_MR,nbn_R2,bn_R2);
  h2_R2_MR_HLT_AK8PFJet450 = new TH2D("h2_R2_MR_HLT_AK8PFJet450", ";M_{R} (GeV);R^{2}",nbn_MR,bn_MR,nbn_R2,bn_R2);
  h2_R2_MR_HLT_AK8PFJet400_TrimMass30 = new TH2D("h2_R2_MR_HLT_AK8PFJet400_TrimMass30", ";M_{R} (GeV);R^{2}",nbn_MR,bn_MR,nbn_R2,bn_R2);
  h2_R2_MR_HLT_AK8PFHT800_TrimMass50 = new TH2D("h2_R2_MR_HLT_AK8PFHT800_TrimMass50", ";M_{R} (GeV);R^{2}",nbn_MR,bn_MR,nbn_R2,bn_R2);
  h2_R2_MR_HLT_PFHT1050 = new TH2D("h2_R2_MR_HLT_PFHT1050", ";M_{R} (GeV);R^{2}",nbn_MR,bn_MR,nbn_R2,bn_R2);
  h2_R2_MR_HLT_PFHT500_PFMET100_PFMHT100_IDTight = new TH2D("h2_R2_MR_HLT_PFHT500_PFMET100_PFMHT100_IDTight", ";M_{R} (GeV);R^{2}",nbn_MR,bn_MR,nbn_R2,bn_R2);
  
  // Extra starts here
  
  h2_R2_MR_HLT_AK8PFJet450Extra = new TH2D("h2_R2_MR_HLT_AK8PFJet450Extra", ";M_{R} (GeV);R^{2}",nbn_MR,bn_MR,nbn_R2,bn_R2);
  h2_R2_MR_HLT_AK8PFJet400_TrimMass30Extra = new TH2D("h2_R2_MR_HLT_AK8PFJet400_TrimMass30Extra", ";M_{R} (GeV);R^{2}",nbn_MR,bn_MR,nbn_R2,bn_R2);
  h2_R2_MR_HLT_AK8PFHT800_TrimMass50Extra = new TH2D("h2_R2_MR_HLT_AK8PFHT800_TrimMass50Extra", ";M_{R} (GeV);R^{2}",nbn_MR,bn_MR,nbn_R2,bn_R2);
  h2_R2_MR_HLT_PFHT1050Extra = new TH2D("h2_R2_MR_HLT_PFHT1050Extra", ";M_{R} (GeV);R^{2}",nbn_MR,bn_MR,nbn_R2,bn_R2);
  
  h2_HT_TrigEffExtra_HLT_AK8PFJet450 = new TH2D("h2_HT_TrigEffExtra_HLT_AK8PFJet450", ";H_{T} (GeV);Trigger passed?",nbnHT,bnHT,2,-0.5,1.5);
  h2_HT_TrigEffExtra_HLT_AK8PFJet400_TrimMass30 = new TH2D("h2_HT_TrigEffExtra_HLT_AK8PFJet400_TrimMass30", ";H_{T} (GeV);Trigger passed?",nbnHT,bnHT,2,-0.5,1.5);
  h2_HT_TrigEffExtra_HLT_AK8PFHT800_TrimMass50 = new TH2D("h2_HT_TrigEffExtra_HLT_AK8PFHT800_TrimMass50", ";H_{T} (GeV);Trigger passed?",nbnHT,bnHT,2,-0.5,1.5);
  h2_HT_TrigEffExtra_HLT_PFHT1050 = new TH2D("h2_HT_TrigEffExtra_HLT_PFHT1050", ";H_{T} (GeV);Trigger passed?",nbnHT,bnHT,2,-0.5,1.5);

  h2_MET_TrigEffExtra_HLT_AK8PFJet450 = new TH2D("h2_MET_TrigEffExtra_HLT_AK8PFJet450", ";MET (GeV);Trigger passed?",nbnMET,bnMET,2,-0.5,1.5);
  h2_MET_TrigEffExtra_HLT_AK8PFJet400_TrimMass30 = new TH2D("h2_MET_TrigEffExtra_HLT_AK8PFJet400_TrimMass30", ";MET (GeV);Trigger passed?",nbnMET,bnMET,2,-0.5,1.5);
  h2_MET_TrigEffExtra_HLT_AK8PFHT800_TrimMass50 = new TH2D("h2_MET_TrigEffExtra_HLT_AK8PFHT800_TrimMass50", ";MET (GeV);Trigger passed?",nbnMET,bnMET,2,-0.5,1.5);
  h2_MET_TrigEffExtra_HLT_PFHT1050 = new TH2D("h2_MET_TrigEffExtra_HLT_PFHT1050", ";MET (GeV);Trigger passed?",nbnMET,bnMET,2,-0.5,1.5);

  h3_HT_MET_TrigEffExtra_HLT_AK8PFJet450 = new TH3D("h3_HT_MET_TrigEffExtra_HLT_AK8PFJet450", ";MET (GeV);H_{T} (GeV);Trigger passed?",nbnMET,bnMET,nbnHT,bnHT,2,bn_Bool);
  h3_HT_MET_TrigEffExtra_HLT_AK8PFJet400_TrimMass30 = new TH3D("h3_HT_MET_TrigEffExtra_HLT_AK8PFJet400_TrimMass30", ";MET (GeV);H_{T} (GeV);Trigger passed?",nbnMET,bnMET,nbnHT,bnHT,2,bn_Bool);
  h3_HT_MET_TrigEffExtra_HLT_AK8PFHT800_TrimMass50  = new TH3D("h3_HT_MET_TrigEffExtra_HLT_AK8PFHT800_TrimMass50", ";MET (GeV);H_{T} (GeV);Trigger passed?",nbnMET,bnMET,nbnHT,bnHT,2,bn_Bool);
  h3_HT_MET_TrigEffExtra_HLT_PFHT1050 = new TH3D("h3_HT_MET_TrigEffExtra_HLT_PFHT1050", ";MET (GeV);H_{T} (GeV);Trigger passed?",nbnMET,bnMET,nbnHT,bnHT,2,bn_Bool);
  
  h3_R2_MR_TrigEffExtra_HLT_AK8PFJet450 = new TH3D("h3_R2_MR_TrigEffExtra_HLT_AK8PFJet450", ";M_{R} (GeV);R^{2};Trigger passed?",nbn_MR,bn_MR,nbn_R2,bn_R2,2,bn_Bool);
  h3_R2_MR_TrigEffExtra_HLT_AK8PFJet400_TrimMass30 = new TH3D("h3_R2_MR_TrigEffExtra_HLT_AK8PFJet400_TrimMass30", ";M_{R} (GeV);R^{2};Trigger passed?",nbn_MR,bn_MR,nbn_R2,bn_R2,2,bn_Bool);
  h3_R2_MR_TrigEffExtra_HLT_AK8PFHT800_TrimMass50 = new TH3D("h3_R2_MR_TrigEffExtra_HLT_AK8PFHT800_TrimMass50", ";M_{R} (GeV);R^{2};Trigger passed?",nbn_MR,bn_MR,nbn_R2,bn_R2,2,bn_Bool);
  h3_R2_MR_TrigEffExtra_HLT_PFHT1050 = new TH3D("h3_R2_MR_TrigEffExtra_HLT_PFHT1050", ";M_{R} (GeV);R^{2};Trigger passed?",nbn_MR,bn_MR,nbn_R2,bn_R2,2,bn_Bool);
  
  h2_HT_TrigEff_HLT_Combined1  = new TH2D("h2_HT_TrigEff_HLT_Combined1", ";H_{T} (GeV);Trigger passed?",nbnHT,bnHT,2,-0.5,1.5);
  h2_MET_TrigEff_HLT_Combined1  = new TH2D("h2_MET_TrigEff_HLT_Combined1", ";MET (GeV);Trigger passed?",nbnMET,bnMET,2,-0.5,1.5);
  h3_HT_MET_TrigEff_HLT_Combined1  = new TH3D("h3_HT_MET_TrigEff_HLT_Combined1", ";MET (GeV);H_{T} (GeV);Trigger passed?",nbnMET,bnMET,nbnHT,bnHT,2,bn_Bool);
  h3_R2_MR_TrigEff_HLT_Combined1  = new TH3D("h3_R2_MR_TrigEff_HLT_Combined1", ";M_{R} (GeV);R^{2};Trigger passed?",nbn_MR,bn_MR,nbn_R2,bn_R2,2,bn_Bool);
  h2_R2_MR_HLT_Combined1  = new TH2D("h2_R2_MR_HLT_Combined1", ";M_{R} (GeV);R^{2}",nbn_MR,bn_MR,nbn_R2,bn_R2);

  h2_HT_TrigEff_HLT_Combined2  = new TH2D("h2_HT_TrigEff_HLT_Combined2", ";H_{T} (GeV);Trigger passed?",nbnHT,bnHT,2,-0.5,1.5);
  h2_MET_TrigEff_HLT_Combined2  = new TH2D("h2_MET_TrigEff_HLT_Combined2", ";MET (GeV);Trigger passed?",nbnMET,bnMET,2,-0.5,1.5);
  h3_HT_MET_TrigEff_HLT_Combined2  = new TH3D("h3_HT_MET_TrigEff_HLT_Combined2", ";MET (GeV);H_{T} (GeV);Trigger passed?",nbnMET,bnMET,nbnHT,bnHT,2,bn_Bool);
  h3_R2_MR_TrigEff_HLT_Combined2  = new TH3D("h3_R2_MR_TrigEff_HLT_Combined2", ";M_{R} (GeV);R^{2};Trigger passed?",nbn_MR,bn_MR,nbn_R2,bn_R2,2,bn_Bool);
  h2_R2_MR_HLT_Combined2  = new TH2D("h2_R2_MR_HLT_Combined2", ";M_{R} (GeV);R^{2}",nbn_MR,bn_MR,nbn_R2,bn_R2);
  
  int nbn_AK8J1pt = 6;
  Double_t bn_AK8J1pt_tmp[] = {0.,200.,400.,700,1000.,1500.,2000.};
  Double_t* bn_AK8J1pt = 0;
  bn_AK8J1pt = getVariableBinEdges(nbn_AK8J1pt+1,bn_AK8J1pt_tmp);
  
//   int nbn_eta = 2;
//   Double_t bn_eta_tmp[] = {0.,1.5,2.5};
//   Double_t* bn_eta = 0;
//   bn_eta = getVariableBinEdges(nbn_eta+1,bn_eta_tmp);
  
  h2_TrigEff_HLT_Combined2_mass  = new TH2D("h2_TrigEff_HLT_Combined2_mass", ";mass_{AK8 jet} (GeV);Trigger passed?",80, 0, 400,2,-0.5,1.5);
  h2_TrigEff_HLT_Combined2_pt  = new TH2D("h2_TrigEff_HLT_Combined2_pt", ";p_{T, AK8 jet} (GeV);Trigger passed?",nbn_AK8J1pt, bn_AK8J1pt,2,-0.5,1.5);
  h2_TrigEff_HLT_Combined2_eta  = new TH2D("h2_TrigEff_HLT_Combined2_eta", ";#eta_{AK8 jet};Trigger passed?",160, -3.2,3.2,2,-0.5,1.5);
  

    
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

    bool trigger = false;
    if(data.HLT_IsoMu27==1 && nMuTight==1 && nEleVeto==0) trigger= true;
    if(apply_all_cuts('P')&&trigger){
      h2_HT_TrigEff_HLT_AK8PFJet450->Fill(AK4_Ht,data.HLT_AK8PFJet450);
      h2_HT_TrigEff_HLT_AK8PFJet400_TrimMass30->Fill(AK4_Ht,data.HLT_AK8PFJet400_TrimMass30);
      h2_HT_TrigEff_HLT_AK8PFHT800_TrimMass50->Fill(AK4_Ht,data.HLT_AK8PFHT800_TrimMass50);
      h2_HT_TrigEff_HLT_PFHT1050->Fill(AK4_Ht,data.HLT_PFHT1050);
      h2_HT_TrigEff_HLT_PFHT500_PFMET100_PFMHT100_IDTight->Fill(AK4_Ht,data.HLT_PFHT500_PFMET100_PFMHT100_IDTight);
      
      h2_MET_TrigEff_HLT_AK8PFJet450->Fill(data.MET_pt,data.HLT_AK8PFJet450);
      h2_MET_TrigEff_HLT_AK8PFJet400_TrimMass30->Fill(data.MET_pt,data.HLT_AK8PFJet400_TrimMass30);
      h2_MET_TrigEff_HLT_AK8PFHT800_TrimMass50 ->Fill(data.MET_pt,data.HLT_AK8PFHT800_TrimMass50);
      h2_MET_TrigEff_HLT_PFHT1050->Fill(data.MET_pt,data.HLT_PFHT1050);
      h2_MET_TrigEff_HLT_PFHT500_PFMET100_PFMHT100_IDTight->Fill(data.MET_pt,data.HLT_PFHT500_PFMET100_PFMHT100_IDTight);

      h3_HT_MET_TrigEff_HLT_AK8PFJet450->Fill(data.MET_pt,AK4_Ht,data.HLT_AK8PFJet450);
      h3_HT_MET_TrigEff_HLT_AK8PFJet400_TrimMass30->Fill(data.MET_pt,AK4_Ht,data.HLT_AK8PFJet400_TrimMass30);
      h3_HT_MET_TrigEff_HLT_AK8PFHT800_TrimMass50->Fill(data.MET_pt,AK4_Ht,data.HLT_AK8PFHT800_TrimMass50);
      h3_HT_MET_TrigEff_HLT_PFHT1050->Fill(data.MET_pt,AK4_Ht,data.HLT_PFHT1050);
      h3_HT_MET_TrigEff_HLT_PFHT500_PFMET100_PFMHT100_IDTight->Fill(data.MET_pt,AK4_Ht,data.HLT_PFHT500_PFMET100_PFMHT100_IDTight);

      h3_R2_MR->Fill(MR,R2,(data.HLT_AK8PFJet450 || data.HLT_AK8PFJet400_TrimMass30||data.HLT_AK8PFHT800_TrimMass50||data.HLT_PFHT1050||data.HLT_PFHT500_PFMET100_PFMHT100_IDTight));
      h3_R2_MR_TrigEff_HLT_AK8PFJet450->Fill(MR,R2,data.HLT_AK8PFJet450);
      h3_R2_MR_TrigEff_HLT_AK8PFJet400_TrimMass30->Fill(MR,R2,data.HLT_AK8PFJet400_TrimMass30);
      h3_R2_MR_TrigEff_HLT_AK8PFHT800_TrimMass50->Fill(MR,R2,data.HLT_AK8PFHT800_TrimMass50);
      h3_R2_MR_TrigEff_HLT_PFHT1050->Fill(MR,R2,data.HLT_PFHT1050);
      h3_R2_MR_TrigEff_HLT_PFHT500_PFMET100_PFMHT100_IDTight->Fill(MR,R2,data.HLT_PFHT500_PFMET100_PFMHT100_IDTight);
      
      h2_R2_MR->Fill(MR,R2);
      if (data.HLT_AK8PFJet450==1) {  h2_R2_MR_HLT_AK8PFJet450->Fill(MR,R2);  };
      if (data.HLT_AK8PFJet400_TrimMass30==1) {  h2_R2_MR_HLT_AK8PFJet400_TrimMass30->Fill(MR,R2);  };
      if (data.HLT_AK8PFHT800_TrimMass50==1) {  h2_R2_MR_HLT_AK8PFHT800_TrimMass50->Fill(MR,R2);  };
      if (data.HLT_PFHT1050==1) {  h2_R2_MR_HLT_PFHT1050->Fill(MR,R2);  };
      if (data.HLT_PFHT500_PFMET100_PFMHT100_IDTight==1) {  h2_R2_MR_HLT_PFHT500_PFMET100_PFMHT100_IDTight->Fill(MR,R2);  };
      
      // ---------------------------------------------------------------------------
      // Checking everything if HLT_PFHT500_PFMET100_PFMHT100_IDTight is not present
      // ---------------------------------------------------------------------------
      if (data.HLT_AK8PFJet450==1&& data.HLT_PFHT500_PFMET100_PFMHT100_IDTight==0) {  h2_R2_MR_HLT_AK8PFJet450Extra->Fill(MR,R2);  };
      if (data.HLT_AK8PFJet400_TrimMass30==1&& data.HLT_PFHT500_PFMET100_PFMHT100_IDTight==0) {  h2_R2_MR_HLT_AK8PFJet400_TrimMass30Extra->Fill(MR,R2);  };
      if (data.HLT_AK8PFHT800_TrimMass50==1&& data.HLT_PFHT500_PFMET100_PFMHT100_IDTight==0) {  h2_R2_MR_HLT_AK8PFHT800_TrimMass50Extra->Fill(MR,R2);  };
      if (data.HLT_PFHT1050==1&& data.HLT_PFHT500_PFMET100_PFMHT100_IDTight==0) {  h2_R2_MR_HLT_PFHT1050Extra->Fill(MR,R2);  };
      
      h2_HT_TrigEffExtra_HLT_AK8PFJet450->Fill(AK4_Ht,(data.HLT_AK8PFJet450 && ! data.HLT_PFHT500_PFMET100_PFMHT100_IDTight));
      h2_HT_TrigEffExtra_HLT_AK8PFJet400_TrimMass30->Fill(AK4_Ht,(data.HLT_AK8PFJet400_TrimMass30 && ! data.HLT_PFHT500_PFMET100_PFMHT100_IDTight));
      h2_HT_TrigEffExtra_HLT_AK8PFHT800_TrimMass50->Fill(AK4_Ht,(data.HLT_AK8PFHT800_TrimMass50 && ! data.HLT_PFHT500_PFMET100_PFMHT100_IDTight));
      h2_HT_TrigEffExtra_HLT_PFHT1050->Fill(AK4_Ht,(data.HLT_PFHT1050 && ! data.HLT_PFHT500_PFMET100_PFMHT100_IDTight));
      
      h2_MET_TrigEffExtra_HLT_AK8PFJet450->Fill(data.MET_pt,(data.HLT_AK8PFJet450 && ! data.HLT_PFHT500_PFMET100_PFMHT100_IDTight));
      h2_MET_TrigEffExtra_HLT_AK8PFJet400_TrimMass30->Fill(data.MET_pt,(data.HLT_AK8PFJet400_TrimMass30 && ! data.HLT_PFHT500_PFMET100_PFMHT100_IDTight));
      h2_MET_TrigEffExtra_HLT_AK8PFHT800_TrimMass50 ->Fill(data.MET_pt,(data.HLT_AK8PFHT800_TrimMass50 && ! data.HLT_PFHT500_PFMET100_PFMHT100_IDTight));
      h2_MET_TrigEffExtra_HLT_PFHT1050->Fill(data.MET_pt,(data.HLT_PFHT1050 && ! data.HLT_PFHT500_PFMET100_PFMHT100_IDTight));

      h3_HT_MET_TrigEffExtra_HLT_AK8PFJet450->Fill(data.MET_pt,AK4_Ht,(data.HLT_AK8PFJet450 && ! data.HLT_PFHT500_PFMET100_PFMHT100_IDTight));
      h3_HT_MET_TrigEffExtra_HLT_AK8PFJet400_TrimMass30->Fill(data.MET_pt,AK4_Ht,(data.HLT_AK8PFJet400_TrimMass30 && ! data.HLT_PFHT500_PFMET100_PFMHT100_IDTight));
      h3_HT_MET_TrigEffExtra_HLT_AK8PFHT800_TrimMass50->Fill(data.MET_pt,AK4_Ht,(data.HLT_AK8PFHT800_TrimMass50 && ! data.HLT_PFHT500_PFMET100_PFMHT100_IDTight));
      h3_HT_MET_TrigEffExtra_HLT_PFHT1050->Fill(data.MET_pt,AK4_Ht,(data.HLT_PFHT1050 && ! data.HLT_PFHT500_PFMET100_PFMHT100_IDTight));

      h3_R2_MR_TrigEffExtra_HLT_AK8PFJet450->Fill(MR,R2,(data.HLT_AK8PFJet450 && ! data.HLT_PFHT500_PFMET100_PFMHT100_IDTight));
      h3_R2_MR_TrigEffExtra_HLT_AK8PFJet400_TrimMass30->Fill(MR,R2,(data.HLT_AK8PFJet400_TrimMass30 && ! data.HLT_PFHT500_PFMET100_PFMHT100_IDTight));
      h3_R2_MR_TrigEffExtra_HLT_AK8PFHT800_TrimMass50->Fill(MR,R2,(data.HLT_AK8PFHT800_TrimMass50 && ! data.HLT_PFHT500_PFMET100_PFMHT100_IDTight));
      h3_R2_MR_TrigEffExtra_HLT_PFHT1050->Fill(MR,R2,(data.HLT_PFHT1050 && ! data.HLT_PFHT500_PFMET100_PFMHT100_IDTight));
      
      // Combination of two triggers
      h2_HT_TrigEff_HLT_Combined1    ->Fill(AK4_Ht,(data.HLT_AK8PFJet400_TrimMass30 || data.HLT_PFHT500_PFMET100_PFMHT100_IDTight));    
      h2_MET_TrigEff_HLT_Combined1   ->Fill(data.MET_pt,(data.HLT_AK8PFJet400_TrimMass30 || data.HLT_PFHT500_PFMET100_PFMHT100_IDTight));
      h3_HT_MET_TrigEff_HLT_Combined1->Fill(data.MET_pt,AK4_Ht,(data.HLT_AK8PFJet400_TrimMass30 || data.HLT_PFHT500_PFMET100_PFMHT100_IDTight));      
      h3_R2_MR_TrigEff_HLT_Combined1  ->Fill(MR,R2,(data.HLT_AK8PFJet400_TrimMass30 || data.HLT_PFHT500_PFMET100_PFMHT100_IDTight)); 
      if (data.HLT_AK8PFJet400_TrimMass30==1||data.HLT_PFHT500_PFMET100_PFMHT100_IDTight==1) {  h2_R2_MR_HLT_Combined1->Fill(MR,R2);  };
            
      // Combination of three triggers
      h2_HT_TrigEff_HLT_Combined2    ->Fill(AK4_Ht,(data.HLT_AK8PFJet400_TrimMass30 || data.HLT_PFHT500_PFMET100_PFMHT100_IDTight || data.HLT_PFHT1050 )); 
      h2_MET_TrigEff_HLT_Combined2   ->Fill(data.MET_pt,(data.HLT_AK8PFJet400_TrimMass30 || data.HLT_PFHT500_PFMET100_PFMHT100_IDTight||data.HLT_PFHT1050==1));
      h3_HT_MET_TrigEff_HLT_Combined2->Fill(data.MET_pt,AK4_Ht,(data.HLT_AK8PFJet400_TrimMass30 || data.HLT_PFHT500_PFMET100_PFMHT100_IDTight||data.HLT_PFHT1050==1));
      h3_R2_MR_TrigEff_HLT_Combined2 ->Fill(MR,R2,(data.HLT_AK8PFJet400_TrimMass30 || data.HLT_PFHT500_PFMET100_PFMHT100_IDTight||data.HLT_PFHT1050==1));
      if (data.HLT_AK8PFJet400_TrimMass30==1||data.HLT_PFHT500_PFMET100_PFMHT100_IDTight==1||data.HLT_PFHT1050==1) {  h2_R2_MR_HLT_Combined2->Fill(MR,R2);  };

      // Mass, pt, eta dependence for the 3 combined trigger
      h2_TrigEff_HLT_Combined2_mass    ->Fill(data.FatJet[iJetAK8[0]].msoftdrop,(data.HLT_AK8PFJet400_TrimMass30 || data.HLT_PFHT500_PFMET100_PFMHT100_IDTight || data.HLT_PFHT1050 )); 
      h2_TrigEff_HLT_Combined2_pt    ->Fill(data.FatJet[iJetAK8[0]].pt,(data.HLT_AK8PFJet400_TrimMass30 || data.HLT_PFHT500_PFMET100_PFMHT100_IDTight || data.HLT_PFHT1050 )); 
      h2_TrigEff_HLT_Combined2_eta    ->Fill(data.FatJet[iJetAK8[0]].eta,(data.HLT_AK8PFJet400_TrimMass30 || data.HLT_PFHT500_PFMET100_PFMHT100_IDTight || data.HLT_PFHT1050 )); 
      
    }

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

    // Trigger efficiencies
    // No weighting
 
    // I guess these histots are for data only (trigger efficiencies)
    // One could just use the normal weight  for that ( = 1)
    // Since MC already has trigger efficiency weight applied already
    // one could use simply 1 as the weight there also
    // N-1 weights are not currently supported

    //w = isData ? 1 : sf_weight['S'];

    /*
      Other examples to use analysis_cuts object

      if (apply_cut('S',"1W"))                          --> 1 Cut from S region
      if (apply_cut('W',"1Wpre"))                       --> 1 Cut from W region
      if (apply_all_cuts('T'))                          --> All cuts in T region
      if (apply_all_cuts_except('Q', "mDPhi<0.25"))     --> N-1 cut
      if (apply_all_cuts_except('S', {"0Ele", "0Mu" })) --> S without Lep veto

      But be aware: Whatever is defined in the baseline_cuts will apply to all histograms
      Also if you use skimmed ntuples (very likely) then those cuts are already applied
      This is because unskimmed ntuple is 4.3 TB in size, and we cannot have them on EOS
    */
  }
  

  // Vary systematics and save each variation into a different historgam
  // Switch on settings.varySystematics to be effective
  //if (apply_all_cuts('S')) vh_jet1_pt[syst_index]->Fill(data.Jet[iJet[0]].pt, w);

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
