#define COMBINE_MRR2_BINS 1
#include "TLorentzVector.h"
#include "TMath.h"
#include "include/AnalysisBase.h"
#include <fstream>
#include <map>
#include "include/SmartHistos.h"


SmartHistos sh;

using namespace std;
//_______________________________________________________
//                  Calculate variables

// Cut variables
static size_t cut_index;
std::map<char, unsigned int> cutbits;
std::map<char, bool> pass_all_cuts;

// N-1 weights
std::map<char, std::vector<double> > w_nm1;

size_t i_Electron;
size_t i_Muon;
size_t i_Tau;
size_t i_Photon;
size_t i_Jet;
size_t i_FatJet;
size_t i_SubJet;
size_t i_GenPart;

bool LoopElectron(eventBuffer& d) { ++i_Electron; if (i_Electron<d.Electron.size()) { return 1; } else { i_Electron=-1; return 0; } }
bool LoopMuon(eventBuffer& d) { ++i_Muon; if (i_Muon<d.Muon.size()) { return 1; } else { i_Muon=-1; return 0; } }
bool LoopTau(eventBuffer& d) { ++i_Tau; if (i_Tau<d.Tau.size()) { return 1; } else { i_Tau=-1; return 0; } }
bool LoopPhoton(eventBuffer& d) { ++i_Photon; if (i_Photon<d.Photon.size()) { return 1; } else { i_Photon=-1; return 0; } }
bool LoopJet(eventBuffer& d) { ++i_Jet; if (i_Jet<d.Jet.size()) { return 1; } else { i_Jet=-1; return 0; } }
bool LoopFatJet(eventBuffer& d) { ++i_FatJet; if (i_FatJet<d.FatJet.size()) { return 1; } else { i_FatJet=-1; return 0; } }
bool LoopSubJet(eventBuffer& d) { ++i_SubJet; if (i_SubJet<d.SubJet.size()) { return 1; } else { i_SubJet=-1; return 0; } }
bool LoopGenPart(eventBuffer& d) { ++i_GenPart; if (i_GenPart<d.GenPart.size()) { return 1; } else { i_GenPart=-1; return 0; } }

void
Analysis::calculate_variables(eventBuffer& d, const unsigned int& syst_index)
{
  cut_index = -1;
  // Calculate decision of each individual cut
  for (const auto& region : analysis_cuts) {
    cutbits[region.first] = 0;
    for (size_t i=0, n=analysis_cuts[region.first].size(); i<n; ++i)
      if (analysis_cuts[region.first][i].func()) cutbits[region.first] += 1<<i;
    pass_all_cuts[region.first] = (cutbits[region.first]==(unsigned int)((1<<analysis_cuts[region.first].size())-1));
  }

  i_Electron = -1;
  i_Muon     = -1;
  i_Tau      = -1;
  i_Photon   = -1;
  i_Jet      = -1;
  i_FatJet   = -1;
  i_SubJet   = -1;
  i_GenPart  = -1;

}

//_______________________________________________________
//                Define Skimming cuts
//   (Not needed, unless you want to skim the ntuple)

bool
Analysis::pass_skimming(eventBuffer& data)
{
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

  std::function<bool()> boost_triggers;
  if (TString(sample).Contains("JetHT")) {
    boost_triggers = [this,&d] { return isData ? d.HLT_PFHT1050==1  : 1; };
  } else if (TString(sample).Contains("MET")) {
    boost_triggers = [this,&d] { return isData ? 
                                 !(d.HLT_PFHT1050==1) && 
                                 ( 
                                  //d.HLT_PFMET120_PFMHT120_IDTight==1 ||
                                  //d.HLT_PFMETNoMu120_PFMHTNoMu120_IDTight==1 ||
                                  //d.HLT_PFMETTypeOne120_PFMHT120_IDTight==1 ||
                                  d.HLT_PFHT500_PFMET100_PFMHT100_IDTight==1 || 
                                  d.HLT_PFHT700_PFMET85_PFMHT85_IDTight==1 ||
                                  d.HLT_PFHT800_PFMET75_PFMHT75_IDTight==1 
                                  ) : 1; };
  } else {
    // Data histos should not contain events from other datasets
    boost_triggers = [this] { return isData ? 0 : 1; }; 
  }

  // p: Preselection + 1 photon added to MET + 0 lep
  analysis_cuts['R'].push_back({ .name="1JetAK8",    .func = []    { return nJetAK8>=1;                       }});
  analysis_cuts['R'].push_back({ .name="NJet",       .func = []    { return nJet>=3;                          }}); // Separate cut, so one can exclude (N-1)
  analysis_cuts['R'].push_back({ .name="MR",         .func = []    { return MR_pho>=800;                      }});
  analysis_cuts['R'].push_back({ .name="R2",         .func = []    { return R2_pho>=0.08;                     }});
  analysis_cuts['R'].push_back({ .name="HLT",        .func =                boost_triggers                     });
  analysis_cuts['R'].push_back({ .name="1Pho",       .func = []    { return nPhotonSelect==1;                 }});
  analysis_cuts['R'].push_back({ .name="0Ele",       .func = []    { return nEleVeto==0;                      }});
  analysis_cuts['R'].push_back({ .name="0Mu",        .func = []    { return nMuVeto==0;                       }});
  analysis_cuts['R'].push_back({ .name="0Tau",       .func = []    { return nTauVeto==0;                      }});

#if TOP == 0
  // S: Signal region
  analysis_cuts['S'].push_back({ .name="1JetAK8",    .func = []    { return nJetAK8>=1;                       }});
  analysis_cuts['S'].push_back({ .name="NJet",       .func = []    { return nJet>=3;                          }});
  analysis_cuts['S'].push_back({ .name="MR",         .func = []    { return MR>=800;                          }});
  analysis_cuts['S'].push_back({ .name="R2",         .func = []    { return R2>=0.08;                         }});
  analysis_cuts['S'].push_back({ .name="HLT",        .func =                boost_triggers                     });
  analysis_cuts['S'].push_back({ .name="0Ele",       .func = []    { return nEleVeto==0;                      }});
  analysis_cuts['S'].push_back({ .name="0Mu",        .func = []    { return nMuVeto==0;                       }});
  analysis_cuts['S'].push_back({ .name="0Tau",       .func = []    { return nTauVeto==0;                      }});
  analysis_cuts['S'].push_back({ .name="1b",         .func = []    { return nMediumBTag>=1;                   }});
  //analysis_cuts['S'].push_back({ .name="1W",         .func = []    { return nTightWTag>=1;                    }});
  analysis_cuts['S'].push_back({ .name="1W",         .func = []    { return nWDeep1>=1;                       }});
  analysis_cuts['S'].push_back({ .name="dPhi",       .func = []    { return dPhiRazor<2.8;                    }});

  // S': DPhi Control region of Signal region
  analysis_cuts['s'].push_back({ .name="1JetAK8",    .func = []    { return nJetAK8>=1;                       }});
  analysis_cuts['s'].push_back({ .name="NJet",       .func = []    { return nJet>=3;                          }});
  analysis_cuts['s'].push_back({ .name="MR",         .func = []    { return MR>=800;                          }});
  analysis_cuts['s'].push_back({ .name="R2",         .func = []    { return R2>=0.08;                         }});
  analysis_cuts['s'].push_back({ .name="HLT",        .func =                boost_triggers                     });
  analysis_cuts['s'].push_back({ .name="0Ele",       .func = []    { return nEleVeto==0;                      }});
  analysis_cuts['s'].push_back({ .name="0Mu",        .func = []    { return nMuVeto==0;                       }});
  analysis_cuts['s'].push_back({ .name="0Tau",       .func = []    { return nTauVeto==0;                      }});
  analysis_cuts['s'].push_back({ .name="1b",         .func = []    { return nMediumBTag>=1;                   }});
  analysis_cuts['s'].push_back({ .name="1W",         .func = []    { return nBoostMassTag>=1;                 }});
  analysis_cuts['s'].push_back({ .name="InvdPhi",    .func = []    { return dPhiRazor>=2.8;                   }});

  // Q: QCD enriched control sample
  analysis_cuts['Q'].push_back({ .name="1JetAK8",    .func = []    { return nJetAK8>=1;                       }});
  analysis_cuts['Q'].push_back({ .name="NJet",       .func = []    { return nJet>=3;                          }});
  analysis_cuts['Q'].push_back({ .name="MR",         .func = []    { return MR>=800;                          }});
  analysis_cuts['Q'].push_back({ .name="R2",         .func = []    { return R2>=0.08;                         }});
  analysis_cuts['Q'].push_back({ .name="HLT",        .func =                boost_triggers                     });
  analysis_cuts['Q'].push_back({ .name="0Ele",       .func = []    { return nEleVeto==0;                      }});
  analysis_cuts['Q'].push_back({ .name="0Mu",        .func = []    { return nMuVeto==0;                       }});
  analysis_cuts['Q'].push_back({ .name="0Tau",       .func = []    { return nTauVeto==0;                      }});
  analysis_cuts['Q'].push_back({ .name="0b",         .func = []    { return nLooseBTag==0;                    }});
  analysis_cuts['Q'].push_back({ .name="1aW",        .func = []    { return nBoostMassTag>=1;                 }});
  analysis_cuts['Q'].push_back({ .name="InvdPhi",    .func = []    { return dPhiRazor>=2.8;                   }});

  // Q': Dphi Control region of QCD enriched sample
  analysis_cuts['q'].push_back({ .name="1JetAK8",    .func = []    { return nJetAK8>=1;                       }});
  analysis_cuts['q'].push_back({ .name="NJet",       .func = []    { return nJet>=3;                          }});
  analysis_cuts['q'].push_back({ .name="MR",         .func = []    { return MR>=800;                          }});
  analysis_cuts['q'].push_back({ .name="R2",         .func = []    { return R2>=0.08;                         }});
  analysis_cuts['q'].push_back({ .name="HLT",        .func =                boost_triggers                    });
  analysis_cuts['q'].push_back({ .name="0Ele",       .func = []    { return nEleVeto==0;                      }});
  analysis_cuts['q'].push_back({ .name="0Mu",        .func = []    { return nMuVeto==0;                       }});
  analysis_cuts['q'].push_back({ .name="0Tau",       .func = []    { return nTauVeto==0;                      }});
  analysis_cuts['q'].push_back({ .name="0b",         .func = []    { return nLooseBTag==0;                    }});
  analysis_cuts['q'].push_back({ .name="1aW",        .func = []    { return nBoostMassTag>=1;                 }});
  analysis_cuts['q'].push_back({ .name="dPhi",       .func = []    { return dPhiRazor<2.8;                    }});

  // T: Top enriched control sample
  analysis_cuts['T'].push_back({ .name="1JetAK8",    .func = []    { return nJetAK8>=1;                       }});
  analysis_cuts['T'].push_back({ .name="NJet",       .func = []    { return nJet>=3;                          }});
  analysis_cuts['T'].push_back({ .name="MR",         .func = []    { return MR>=800;                          }});
  analysis_cuts['T'].push_back({ .name="R2",         .func = []    { return R2>=0.08;                         }});
  analysis_cuts['T'].push_back({ .name="HLT",        .func =                boost_triggers                     });
  analysis_cuts['T'].push_back({ .name="1Lep",       .func = []    { return nLepVeto==1;                      }});
  analysis_cuts['T'].push_back({ .name="1b",         .func = []    { return nMediumBTag>=1;                   }});
  analysis_cuts['T'].push_back({ .name="1W",         .func = []    { return nBoostMassTag>=1;                 }});
  analysis_cuts['T'].push_back({ .name="dPhi",       .func = []    { return dPhiRazor<2.8;                    }});
  analysis_cuts['T'].push_back({ .name="MT",         .func = []    { return MT_vetolep<100;                   }});

  // W: W enriched control sample
  analysis_cuts['W'].push_back({ .name="1JetAK8",    .func = []    { return nJetAK8>=1;                       }});
  analysis_cuts['W'].push_back({ .name="NJet",       .func = []    { return nJet>=3;                          }});
  analysis_cuts['W'].push_back({ .name="MR",         .func = []    { return MR>=800;                          }});
  analysis_cuts['W'].push_back({ .name="R2",         .func = []    { return R2>=0.08;                         }});
  analysis_cuts['W'].push_back({ .name="HLT",        .func =                boost_triggers                     });
  analysis_cuts['W'].push_back({ .name="1Lep",       .func = []    { return nLepVeto==1;                      }});
  analysis_cuts['W'].push_back({ .name="0b",         .func = []    { return nLooseBTag==0;                    }});
  analysis_cuts['W'].push_back({ .name="1mW",        .func = []    { return nBoostMassTag>=1;                 }});
  analysis_cuts['W'].push_back({ .name="dPhi",       .func = []    { return dPhiRazor<2.8;                    }});
  analysis_cuts['W'].push_back({ .name="MT",         .func = []    { return MT_vetolep>=30 && MT_vetolep<100; }});

  // L: 1-lepton invisible control sample with veto lepton
  analysis_cuts['L'].push_back({ .name="1JetAK8",    .func = []    { return nJetAK8>=1;                       }});
  analysis_cuts['L'].push_back({ .name="NJet",       .func = []    { return nJet>=3;                          }});
  analysis_cuts['L'].push_back({ .name="MR",         .func = []    { return MR>=800;                          }});
  analysis_cuts['L'].push_back({ .name="R2",         .func = []    { return R2_1vl>=0.08;                     }});
  analysis_cuts['L'].push_back({ .name="HLT",        .func =                boost_triggers                     });
  analysis_cuts['L'].push_back({ .name="0b",         .func = []    { return nLooseBTag==0;                    }});
  analysis_cuts['L'].push_back({ .name="1Lep",       .func = []    { return nLepVeto==1;                      }});
  analysis_cuts['L'].push_back({ .name="1mW",        .func = []    { return nBoostMassTag>=1;                 }});
  analysis_cuts['L'].push_back({ .name="dPhi",       .func = []    { return dPhiRazor<2.8;                    }});
  analysis_cuts['L'].push_back({ .name="MT",         .func = []    { return MT_vetolep>=30 && MT_vetolep<100; }});

  // Z: Z->ll enriched control sample
  analysis_cuts['Z'].push_back({ .name="1JetAK8",    .func = []    { return nJetAK8>=1;                       }});
  analysis_cuts['Z'].push_back({ .name="NJet",       .func = []    { return nJet>=3;                          }});
  analysis_cuts['Z'].push_back({ .name="MR",         .func = []    { return MR>=800;                          }});
  analysis_cuts['Z'].push_back({ .name="R2ll",       .func = []    { return R2_ll>=0.08;                      }});
  analysis_cuts['Z'].push_back({ .name="HLT",        .func =                boost_triggers                     });
  analysis_cuts['Z'].push_back({ .name="2Lep",       .func = []    { return (nEleSelect==2&&nMuVeto==0) ||
                                                                     (nMuSelect==2&&nEleVeto==0);             }});
  analysis_cuts['Z'].push_back({ .name="OppCharge",  .func = [&d]  { 
                                   if (nEleSelect==2) return (d.Electron[iEleSelect[0]].charge + d.Electron[iEleSelect[1]].charge)==0;
                                   else if (nMuSelect==2) return (d.Muon[iMuSelect[0]].charge  + d.Muon[iMuSelect[1]].charge)==0;
                                   return false;
                                 }});
  analysis_cuts['Z'].push_back({ .name="1mW",        .func = []    { return nBoostMassTag>=1;                 }});
  analysis_cuts['Z'].push_back({ .name="dPhi",       .func = []    { return dPhiRazor<2.8;                    }});
  analysis_cuts['Z'].push_back({ .name="Mll",        .func = []    { return std::abs(M_ll-91.2)<10;           }});

  // G: Photon enriched sample
  analysis_cuts['G'].push_back({ .name="1JetAK8",    .func = []    { return nJetAK8>=1;                       }});
  analysis_cuts['G'].push_back({ .name="1Pho",       .func = []    { return nPhotonSelect==1;                 }});
  analysis_cuts['G'].push_back({ .name="NJet",       .func = []    { return nJetNoPho>=3;                     }});
  analysis_cuts['G'].push_back({ .name="MR",         .func = []    { return MR_pho>=800;                      }});
  analysis_cuts['G'].push_back({ .name="R2",         .func = []    { return R2_pho>=0.08;                     }});
  analysis_cuts['G'].push_back({ .name="HLT",        .func =                boost_triggers                     });
  analysis_cuts['G'].push_back({ .name="0Ele",       .func = []    { return nEleVeto==0;                      }});
  analysis_cuts['G'].push_back({ .name="0Mu",        .func = []    { return nMuVeto==0;                       }});
  analysis_cuts['G'].push_back({ .name="0Tau",       .func = []    { return nTauVeto==0;                      }});
  analysis_cuts['G'].push_back({ .name="1mW",        .func = []    { return nBoostMassTag>=1;                 }});
  analysis_cuts['G'].push_back({ .name="dPhi",       .func = []    { return dPhiRazorNoPho<2.8;               }});

  // z: Z->ll enriched control sample (with full tag)
  analysis_cuts['z'].push_back({ .name="1JetAK8",    .func = []    { return nJetAK8>=1;                       }}); 
  analysis_cuts['z'].push_back({ .name="NJet",       .func = []    { return nJet>=3;                          }});
  analysis_cuts['z'].push_back({ .name="MR",         .func = []    { return MR>=800;                          }}); 
  analysis_cuts['z'].push_back({ .name="R2ll",       .func = []    { return R2_ll>=0.08;                      }}); 
  analysis_cuts['z'].push_back({ .name="HLT",        .func =                boost_triggers                     });
  analysis_cuts['z'].push_back({ .name="2Lep",       .func = []    { return (nEleSelect==2&&nMuVeto==0) ||
                                                                     (nMuSelect==2&&nEleVeto==0);             }});
  analysis_cuts['z'].push_back({ .name="OppCharge",  .func = [&d]  { 
                                   if (nEleSelect==2) return (d.Electron[iEleSelect[0]].charge + d.Electron[iEleSelect[1]].charge)==0;
                                   else if (nMuSelect==2) return (d.Muon[iMuSelect[0]].charge + d.Muon[iMuSelect[1]].charge)==0;
                                   return false;
                                 }}); 
  analysis_cuts['z'].push_back({ .name="1W",         .func = []    { return nBoostMassTag>=1;                 }}); 
  analysis_cuts['z'].push_back({ .name="dPhi",       .func = []    { return dPhiRazor<2.8;                    }}); 
  analysis_cuts['z'].push_back({ .name="Mll",        .func = []    { return std::abs(M_ll-91.2)<10;           }}); 

#else

  // t: Boosted Top Signal region
  analysis_cuts['S'].push_back({ .name="1JetAK8",    .func = []    { return nJetAK8>=1;                       }}); 
  analysis_cuts['S'].push_back({ .name="NJet",       .func = []    { return nJet>=3;                          }});
  analysis_cuts['S'].push_back({ .name="MR",         .func = []    { return MR>=800;                          }});
  analysis_cuts['S'].push_back({ .name="R2",         .func = []    { return R2>=0.08;                         }});
  analysis_cuts['S'].push_back({ .name="HLT",        .func =                boost_triggers                     });
  analysis_cuts['S'].push_back({ .name="0Ele",       .func = []    { return nEleVeto==0;                      }});
  analysis_cuts['S'].push_back({ .name="0Mu",        .func = []    { return nMuVeto==0;                       }});
  analysis_cuts['S'].push_back({ .name="0Tau",       .func = []    { return nTauVeto==0;                      }});
  //analysis_cuts['S'].push_back({ .name="1Top",       .func = []    { return nHadTopTag>=1;                    }});
  analysis_cuts['S'].push_back({ .name="1Top",       .func = []    { return nTopDeep3>=1;                     }});
  analysis_cuts['S'].push_back({ .name="dPhi",       .func = []    { return dPhiRazor<2.8;                    }});

  // a: Boosted Top' Signal region
  analysis_cuts['s'].push_back({ .name="1JetAK8",    .func = []    { return nJetAK8>=1;                       }}); 
  analysis_cuts['s'].push_back({ .name="NJet",       .func = []    { return nJet>=3;                          }});
  analysis_cuts['s'].push_back({ .name="MR",         .func = []    { return MR>=800;                          }});
  analysis_cuts['s'].push_back({ .name="R2",         .func = []    { return R2>=0.08;                         }});
  analysis_cuts['s'].push_back({ .name="HLT",        .func =                boost_triggers                     });
  analysis_cuts['s'].push_back({ .name="0Ele",       .func = []    { return nEleVeto==0;                      }});
  analysis_cuts['s'].push_back({ .name="0Mu",        .func = []    { return nMuVeto==0;                       }});
  analysis_cuts['s'].push_back({ .name="0Tau",       .func = []    { return nTauVeto==0;                      }});
  analysis_cuts['s'].push_back({ .name="1Top",       .func = []    { return nBoostMassBTag>=1;                }});
  analysis_cuts['s'].push_back({ .name="InvdPhi",    .func = []    { return dPhiRazor>=2.8;                   }});

  // t: Boosted Top Q region
  analysis_cuts['Q'].push_back({ .name="1JetAK8",    .func = []    { return nJetAK8>=1;                       }}); 
  analysis_cuts['Q'].push_back({ .name="NJet",       .func = []    { return nJet>=3;                          }});
  analysis_cuts['Q'].push_back({ .name="MR",         .func = []    { return MR>=800;                          }});
  analysis_cuts['Q'].push_back({ .name="R2",         .func = []    { return R2>=0.08;                         }});
  analysis_cuts['Q'].push_back({ .name="HLT",        .func =                boost_triggers                     });
  analysis_cuts['Q'].push_back({ .name="0Ele",       .func = []    { return nEleVeto==0;                      }});
  analysis_cuts['Q'].push_back({ .name="0Mu",        .func = []    { return nMuVeto==0;                       }});
  analysis_cuts['Q'].push_back({ .name="0Tau",       .func = []    { return nTauVeto==0;                      }});
  analysis_cuts['Q'].push_back({ .name="0b",         .func = []    { return nLooseBTag==0;                    }});
  analysis_cuts['Q'].push_back({ .name="1aTop",      .func = []    { return nBoostMassTag>=1;                 }});
  analysis_cuts['Q'].push_back({ .name="InvdPhi",    .func = []    { return dPhiRazor>=2.8;                   }});

  // t: Boosted Top Q' region
  analysis_cuts['q'].push_back({ .name="1JetAK8",    .func = []    { return nJetAK8>=1;                       }}); 
  analysis_cuts['q'].push_back({ .name="NJet",       .func = []    { return nJet>=3;                          }});
  analysis_cuts['q'].push_back({ .name="MR",         .func = []    { return MR>=800;                          }});
  analysis_cuts['q'].push_back({ .name="R2",         .func = []    { return R2>=0.08;                         }});
  analysis_cuts['q'].push_back({ .name="HLT",        .func =                boost_triggers                     });
  analysis_cuts['q'].push_back({ .name="0Ele",       .func = []    { return nEleVeto==0;                      }});
  analysis_cuts['q'].push_back({ .name="0Mu",        .func = []    { return nMuVeto==0;                       }});
  analysis_cuts['q'].push_back({ .name="0Tau",       .func = []    { return nTauVeto==0;                      }});
  analysis_cuts['q'].push_back({ .name="0b",         .func = []    { return nLooseBTag==0;                    }});
  analysis_cuts['q'].push_back({ .name="1aTop",      .func = []    { return nBoostMassTag>=1;                 }});
  analysis_cuts['q'].push_back({ .name="dPhi",       .func = []    { return dPhiRazor<2.8;                    }});

  // t: Boosted Top T region
  analysis_cuts['T'].push_back({ .name="1JetAK8",    .func = []    { return nJetAK8>=1;                       }}); 
  analysis_cuts['T'].push_back({ .name="NJet",       .func = []    { return nJet>=3;                          }});
  analysis_cuts['T'].push_back({ .name="MR",         .func = []    { return MR>=800;                          }});
  analysis_cuts['T'].push_back({ .name="R2",         .func = []    { return R2>=0.08;                         }});
  analysis_cuts['T'].push_back({ .name="HLT",        .func =                boost_triggers                     });
  analysis_cuts['T'].push_back({ .name="1Lep",       .func = []    { return nLepVeto==1;                      }});
  analysis_cuts['T'].push_back({ .name="1Top",       .func = []    { return nBoostMassBTag>=1;                }});
  analysis_cuts['T'].push_back({ .name="dPhi",       .func = []    { return dPhiRazor<2.8;                    }});
  analysis_cuts['T'].push_back({ .name="MT",         .func = []    { return MT_vetolep<100;                   }});

  // t: Boosted Top W region
  analysis_cuts['W'].push_back({ .name="1JetAK8",    .func = []    { return nJetAK8>=1;                       }}); 
  analysis_cuts['W'].push_back({ .name="NJet",       .func = []    { return nJet>=3;                          }});
  analysis_cuts['W'].push_back({ .name="MR",         .func = []    { return MR>=800;                          }});
  analysis_cuts['W'].push_back({ .name="R2",         .func = []    { return R2>=0.08;                         }});
  analysis_cuts['W'].push_back({ .name="HLT",        .func =                boost_triggers                     });
  analysis_cuts['W'].push_back({ .name="1Lep",       .func = []    { return nLepVeto==1;                      }});
  analysis_cuts['W'].push_back({ .name="0b",         .func = []    { return nLooseBTag==0;                    }});
  analysis_cuts['W'].push_back({ .name="1mTop",      .func = []    { return nBoostMassTag>=1;                 }});
  analysis_cuts['W'].push_back({ .name="dPhi",       .func = []    { return dPhiRazor<2.8;                    }});
  analysis_cuts['W'].push_back({ .name="MT",         .func = []    { return MT_vetolep>=30 && MT_vetolep<100; }});

  // L: 1-lepton invisible control sample with veto lepton
  analysis_cuts['L'].push_back({ .name="1JetAK8",    .func = []    { return nJetAK8>=1;                       }});
  analysis_cuts['L'].push_back({ .name="NJet",       .func = []    { return nJet>=3;                          }});
  analysis_cuts['L'].push_back({ .name="MR",         .func = []    { return MR>=800;                          }});
  analysis_cuts['L'].push_back({ .name="R2",         .func = []    { return R2_1vl>=0.08;                     }});
  analysis_cuts['L'].push_back({ .name="HLT",        .func =                boost_triggers                     });
  analysis_cuts['L'].push_back({ .name="1Lep",       .func = []    { return nLepVeto==1;                      }});
  analysis_cuts['L'].push_back({ .name="0b",         .func = []    { return nLooseBTag==0;                    }});
  analysis_cuts['L'].push_back({ .name="1mTop",      .func = []    { return nBoostMassTag>=1;                 }});
  analysis_cuts['L'].push_back({ .name="dPhi",       .func = []    { return dPhiRazor<2.8;                    }});
  analysis_cuts['L'].push_back({ .name="MT",         .func = []    { return MT_vetolep>=30 && MT_vetolep<100; }});

  // Z: Z->ll enriched control sample
  analysis_cuts['Z'].push_back({ .name="1JetAK8",    .func = []    { return nJetAK8>=1;                       }}); 
  analysis_cuts['Z'].push_back({ .name="NJet",       .func = []    { return nJet>=3;                          }});
  analysis_cuts['Z'].push_back({ .name="MR",         .func = []    { return MR>=800;                          }});
  analysis_cuts['Z'].push_back({ .name="R2ll",       .func = []    { return R2_ll>=0.08;                      }});
  analysis_cuts['Z'].push_back({ .name="HLT",        .func =                boost_triggers                     });
  analysis_cuts['Z'].push_back({ .name="2Lep",       .func = []    { return (nEleSelect==2&&nMuVeto==0) ||
                                                                     (nMuSelect==2&&nEleVeto==0);             }});
  analysis_cuts['Z'].push_back({ .name="OppCharge",  .func = [&d]  { 
                                   if (nEleSelect==2) return (d.Electron[iEleSelect[0]].charge + d.Electron[iEleSelect[1]].charge)==0;
                                   else if (nMuSelect==2) return (d.Muon[iMuSelect[0]].charge + d.Muon[iMuSelect[1]].charge)==0;
                                   return false;
                                 }});
  analysis_cuts['Z'].push_back({ .name="1mTop",      .func = []    { return nBoostMassTag>=1;                 }});
  analysis_cuts['Z'].push_back({ .name="dPhi",       .func = []    { return dPhiRazor<2.8;                    }});
  analysis_cuts['Z'].push_back({ .name="Mll",        .func = []    { return std::abs(M_ll-91.2)<10;           }});

  // G: Photon enriched sample
  analysis_cuts['G'].push_back({ .name="1JetAK8",    .func = []    { return nJetAK8>=1;                       }});
  analysis_cuts['G'].push_back({ .name="1Pho",       .func = []    { return nPhotonSelect==1;                 }});
  analysis_cuts['G'].push_back({ .name="NJet",       .func = []    { return nJetNoPho>=3;                     }});
  analysis_cuts['G'].push_back({ .name="MR",         .func = []    { return MR_pho>=800;                      }});
  analysis_cuts['G'].push_back({ .name="R2",         .func = []    { return R2_pho>=0.08;                     }});
  analysis_cuts['G'].push_back({ .name="HLT",        .func =                boost_triggers                     });
  analysis_cuts['G'].push_back({ .name="0Ele",       .func = []    { return nEleVeto==0;                      }});
  analysis_cuts['G'].push_back({ .name="0Mu",        .func = []    { return nMuVeto==0;                       }});
  analysis_cuts['G'].push_back({ .name="0Tau",       .func = []    { return nTauVeto==0;                      }});
  analysis_cuts['G'].push_back({ .name="1mTop",      .func = []    { return nBoostMassTag>=1;                 }});
  analysis_cuts['G'].push_back({ .name="dPhi",       .func = []    { return dPhiRazorNoPho<2.8;               }});

#endif

  // H: Photon enriched sample (G without boosted object)
  analysis_cuts['H'].push_back({ .name="1JetAK8",    .func = []    { return nJetAK8>=1;                       }}); 
  analysis_cuts['H'].push_back({ .name="1Pho",       .func = []    { return nPhotonSelect==1;                 }}); 
  analysis_cuts['H'].push_back({ .name="NJet",       .func = []    { return nJetNoPho>=3;                     }}); 
  analysis_cuts['H'].push_back({ .name="MR",         .func = []    { return MR_pho>=800;                      }}); 
  analysis_cuts['H'].push_back({ .name="R2",         .func = []    { return R2_pho>=0.08;                     }}); 
  analysis_cuts['H'].push_back({ .name="HLT",        .func =                boost_triggers                     });
  analysis_cuts['H'].push_back({ .name="0Ele",       .func = []    { return nEleVeto==0;                      }}); 
  analysis_cuts['H'].push_back({ .name="0Mu",        .func = []    { return nMuVeto==0;                       }}); 
  analysis_cuts['H'].push_back({ .name="0Tau",       .func = []    { return nTauVeto==0;                      }}); 
  analysis_cuts['H'].push_back({ .name="dPhi",       .func = []    { return dPhiRazorNoPho<2.8;               }}); 

  // F: Fake rate measurement region
  analysis_cuts['F'].push_back({ .name="1JetAK8",    .func = []    { return nJetAK8>=1;                       }}); 
  analysis_cuts['F'].push_back({ .name="NJet",       .func = []    { return nJet>=3;                          }}); 
  analysis_cuts['F'].push_back({ .name="MR",         .func = []    { return MR>=800;                          }}); 
  analysis_cuts['F'].push_back({ .name="HLT",        .func =                boost_triggers                     });
  analysis_cuts['F'].push_back({ .name="0Ele",       .func = []    { return nEleVeto==0;                      }}); 
  analysis_cuts['F'].push_back({ .name="0Mu",        .func = []    { return nMuVeto==0;                       }}); 
  analysis_cuts['F'].push_back({ .name="0Tau",       .func = []    { return nTauVeto==0;                      }}); 
  analysis_cuts['F'].push_back({ .name="0b",         .func = []    { return nLooseBTag==0;                    }}); 
  //analysis_cuts['F'].push_back({ .name="InvdPhi",    .func = []    { return minDeltaPhi<0.3;                  }});
  analysis_cuts['F'].push_back({ .name="InvdPhi",    .func = []    { return dPhiRazor>=2.8;                      }}); 

  // B: F+1b
  analysis_cuts['B'].push_back({ .name="1JetAK8",    .func = []    { return nJetAK8>=1;                       }}); 
  analysis_cuts['B'].push_back({ .name="NJet",       .func = []    { return nJet>=3;                          }}); 
  analysis_cuts['B'].push_back({ .name="MR",         .func = []    { return MR>=800;                          }}); 
  analysis_cuts['B'].push_back({ .name="HLT",        .func =                boost_triggers                     });
  analysis_cuts['B'].push_back({ .name="0Ele",       .func = []    { return nEleVeto==0;                      }}); 
  analysis_cuts['B'].push_back({ .name="0Mu",        .func = []    { return nMuVeto==0;                       }}); 
  analysis_cuts['B'].push_back({ .name="0Tau",       .func = []    { return nTauVeto==0;                      }}); 
  analysis_cuts['B'].push_back({ .name="1b",         .func = []    { return nMediumBTag>=1;                   }}); 
  analysis_cuts['B'].push_back({ .name="InvdPhi",    .func = []    { return dPhiRazor>=2.8;                   }}); 






  // New signal regions
  // Fully hadronic
  // a: had 1top
  // b: had 2top
  // c: had b+W, 4-5 jet
  // d: had b+W, 6+ jet
  // e: had 0b, 1V, 3-4jet
  // f: had 0b, 1V, 5+ jet
  // g: had 0b, 2V, 2-4 jet
  // h: had 0b, 2V, 5+ jet

  // 1 Isolated lepton
  // i: lep 1hadtop
  // j: lep 1V+b
  // k: lep 1V+0b

  // Non-isolated lepton-jets
  // l: 1leptop 0hadtop
  // m: 1leptop 1hadtop
  // n: 1lepjet 0b, 0V, 2-4 jet
  // o: 1lepjet 0b, 0V, 5+ jet
  // p: 1lepjet 0b, 1V, 2-4 jet
  // q: 1lepjet 0b, 1V, 5+ jet

  // Preselection --> Test object performance
  analysis_cuts['P'].push_back({ .name="1JetAK8",    .func = []    { return nJetAK8>=1;                       }});
  analysis_cuts['P'].push_back({ .name="NJet",       .func = []    { return nJet>=2;                          }});
  analysis_cuts['P'].push_back({ .name="MR",         .func = []    { return MR>=800;                          }});
  analysis_cuts['P'].push_back({ .name="R2",         .func = []    { return R2>=0.08;                         }});
  analysis_cuts['P'].push_back({ .name="HLT",        .func =                boost_triggers                     });

  // Fully hadronic
  // 0 Lepton Preselection + DPhi --> Test event selection
  analysis_cuts['0'].push_back({ .name="1JetAK8",    .func = []    { return nJetAK8>=1;                       }});
  analysis_cuts['0'].push_back({ .name="NJet",       .func = []    { return nJet>=2;                          }});
  analysis_cuts['0'].push_back({ .name="MR",         .func = []    { return MR>=800;                          }});
  analysis_cuts['0'].push_back({ .name="R2",         .func = []    { return R2>=0.08;                         }});
  analysis_cuts['0'].push_back({ .name="HLT",        .func =                boost_triggers                     });
  analysis_cuts['0'].push_back({ .name="0IsoEle",    .func = []    { return nEleVeto==0;                      }});
  analysis_cuts['0'].push_back({ .name="0IsoMu",     .func = []    { return nMuVeto==0;                       }});
  analysis_cuts['0'].push_back({ .name="0IsoTau",    .func = []    { return nTauVeto==0;                      }});
  analysis_cuts['0'].push_back({ .name="0LepJet",    .func = []    { return nLepJet==0;                       }});
  analysis_cuts['0'].push_back({ .name="0LepTop",    .func = []    { return nLepTop==0;                       }});
  analysis_cuts['0'].push_back({ .name="dPhi",       .func = []    { return dPhiRazor<2.8;                    }});
  // had 1top
  analysis_cuts['a'].push_back({ .name="1JetAK8",    .func = []    { return nJetAK8>=1;                       }});
  analysis_cuts['a'].push_back({ .name="NJet",       .func = []    { return nJet>=3;                          }}); // Tighter than presel
  analysis_cuts['a'].push_back({ .name="MR",         .func = []    { return MR>=800;                          }});
  analysis_cuts['a'].push_back({ .name="R2",         .func = []    { return R2>=0.08;                         }});
  analysis_cuts['a'].push_back({ .name="HLT",        .func =                boost_triggers                     });
  analysis_cuts['a'].push_back({ .name="0Ele",       .func = []    { return nEleVeto==0;                      }});
  analysis_cuts['a'].push_back({ .name="0Mu",        .func = []    { return nMuVeto==0;                       }});
  analysis_cuts['a'].push_back({ .name="0Tau",       .func = []    { return nTauVeto==0;                      }});
  analysis_cuts['a'].push_back({ .name="0LepJet",    .func = []    { return nLepJet==0;                       }});
  analysis_cuts['a'].push_back({ .name="0LepTop",    .func = []    { return nLepTop==0;                       }});
  analysis_cuts['a'].push_back({ .name="dPhi",       .func = []    { return dPhiRazor<2.8;                    }});
  analysis_cuts['a'].push_back({ .name="1HadTop",    .func = []    { return nHadTop==1;                       }}); // Additional
  // had 2top
  analysis_cuts['b'].push_back({ .name="1JetAK8",    .func = []    { return nJetAK8>=1;                       }});
  analysis_cuts['b'].push_back({ .name="NJet",       .func = []    { return nJet>=3;                          }}); // Tighter than presel
  analysis_cuts['b'].push_back({ .name="MR",         .func = []    { return MR>=800;                          }});
  analysis_cuts['b'].push_back({ .name="R2",         .func = []    { return R2>=0.08;                         }});
  analysis_cuts['b'].push_back({ .name="HLT",        .func =                boost_triggers                     });
  analysis_cuts['b'].push_back({ .name="0Ele",       .func = []    { return nEleVeto==0;                      }});
  analysis_cuts['b'].push_back({ .name="0Mu",        .func = []    { return nMuVeto==0;                       }});
  analysis_cuts['b'].push_back({ .name="0Tau",       .func = []    { return nTauVeto==0;                      }});
  analysis_cuts['b'].push_back({ .name="0LepJet",    .func = []    { return nLepJet==0;                       }});
  analysis_cuts['b'].push_back({ .name="0LepTop",    .func = []    { return nLepTop==0;                       }});
  analysis_cuts['b'].push_back({ .name="dPhi",       .func = []    { return dPhiRazor<2.8;                    }});
  analysis_cuts['b'].push_back({ .name="2HadTop",    .func = []    { return nHadTop>=2;                       }}); // Additional
  // had b+V, 4-5 jet
  analysis_cuts['c'].push_back({ .name="1JetAK8",    .func = []    { return nJetAK8>=1;                       }});
  analysis_cuts['c'].push_back({ .name="NJet",       .func = []    { return nJet==4||nJet==5;                 }}); // Tighter than presel
  analysis_cuts['c'].push_back({ .name="MR",         .func = []    { return MR>=800;                          }});
  analysis_cuts['c'].push_back({ .name="R2",         .func = []    { return R2>=0.08;                         }});
  analysis_cuts['c'].push_back({ .name="HLT",        .func =                boost_triggers                     });
  analysis_cuts['c'].push_back({ .name="0Ele",       .func = []    { return nEleVeto==0;                      }});
  analysis_cuts['c'].push_back({ .name="0Mu",        .func = []    { return nMuVeto==0;                       }});
  analysis_cuts['c'].push_back({ .name="0Tau",       .func = []    { return nTauVeto==0;                      }});
  analysis_cuts['c'].push_back({ .name="0LepJet",    .func = []    { return nLepJet==0;                       }});
  analysis_cuts['c'].push_back({ .name="0LepTop",    .func = []    { return nLepTop==0;                       }});
  analysis_cuts['c'].push_back({ .name="dPhi",       .func = []    { return dPhiRazor<2.8;                    }});
  analysis_cuts['c'].push_back({ .name="0HadTop",    .func = []    { return nHadTop==0;                       }}); // Additional
  analysis_cuts['c'].push_back({ .name="1b",         .func = []    { return nMediumIsoBTag>=1;                }}); // Additional
  analysis_cuts['c'].push_back({ .name="1HadV",      .func = []    { return nHadV>=1;                         }}); // Additional
  // had b+V, 6+ jet
  analysis_cuts['d'].push_back({ .name="1JetAK8",    .func = []    { return nJetAK8>=1;                       }});
  analysis_cuts['d'].push_back({ .name="NJet",       .func = []    { return nJet>=6;                          }}); // Tighter than presel
  analysis_cuts['d'].push_back({ .name="MR",         .func = []    { return MR>=800;                          }});
  analysis_cuts['d'].push_back({ .name="R2",         .func = []    { return R2>=0.08;                         }});
  analysis_cuts['d'].push_back({ .name="HLT",        .func =                boost_triggers                     });
  analysis_cuts['d'].push_back({ .name="0Ele",       .func = []    { return nEleVeto==0;                      }});
  analysis_cuts['d'].push_back({ .name="0Mu",        .func = []    { return nMuVeto==0;                       }});
  analysis_cuts['d'].push_back({ .name="0Tau",       .func = []    { return nTauVeto==0;                      }});
  analysis_cuts['d'].push_back({ .name="0LepJet",    .func = []    { return nLepJet==0;                       }});
  analysis_cuts['d'].push_back({ .name="0LepTop",    .func = []    { return nLepTop==0;                       }});
  analysis_cuts['d'].push_back({ .name="dPhi",       .func = []    { return dPhiRazor<2.8;                    }});
  analysis_cuts['d'].push_back({ .name="0HadTop",    .func = []    { return nHadTop==0;                       }}); // Additional
  analysis_cuts['d'].push_back({ .name="1b",         .func = []    { return nMediumIsoBTag>=1;                }}); // Additional
  analysis_cuts['d'].push_back({ .name="1HadV",      .func = []    { return nHadV>=1;                         }}); // Additional
  // had 0b, 1V, 3-4jet
  analysis_cuts['e'].push_back({ .name="1JetAK8",    .func = []    { return nJetAK8>=1;                       }});
  analysis_cuts['e'].push_back({ .name="NJet",       .func = []    { return nJet==3||nJet==4;                 }}); // Tighter than presel
  analysis_cuts['e'].push_back({ .name="MR",         .func = []    { return MR>=800;                          }});
  analysis_cuts['e'].push_back({ .name="R2",         .func = []    { return R2>=0.08;                         }});
  analysis_cuts['e'].push_back({ .name="HLT",        .func =                boost_triggers                     });
  analysis_cuts['e'].push_back({ .name="0Ele",       .func = []    { return nEleVeto==0;                      }});
  analysis_cuts['e'].push_back({ .name="0Mu",        .func = []    { return nMuVeto==0;                       }});
  analysis_cuts['e'].push_back({ .name="0Tau",       .func = []    { return nTauVeto==0;                      }});
  analysis_cuts['e'].push_back({ .name="0isob",      .func = []    { return nLooseIsoBTag==0;                 }}); 
  analysis_cuts['e'].push_back({ .name="0LepJet",    .func = []    { return nLepJet==0;                       }});
  analysis_cuts['e'].push_back({ .name="0LepTop",    .func = []    { return nLepTop==0;                       }});
  analysis_cuts['e'].push_back({ .name="dPhi",       .func = []    { return dPhiRazor<2.8;                    }});
  analysis_cuts['e'].push_back({ .name="0HadTop",    .func = []    { return nHadTop==0;                       }}); // Additional
  analysis_cuts['e'].push_back({ .name="1HadV",      .func = []    { return nHadV==1;                         }}); // Additional
  // had 0b, 1V, 5+ jet
  analysis_cuts['f'].push_back({ .name="1JetAK8",    .func = []    { return nJetAK8>=1;                       }});
  analysis_cuts['f'].push_back({ .name="NJet",       .func = []    { return nJet>=5;                          }}); // Tighter than presel
  analysis_cuts['f'].push_back({ .name="MR",         .func = []    { return MR>=800;                          }});
  analysis_cuts['f'].push_back({ .name="R2",         .func = []    { return R2>=0.08;                         }});
  analysis_cuts['f'].push_back({ .name="HLT",        .func =                boost_triggers                     });
  analysis_cuts['f'].push_back({ .name="0Ele",       .func = []    { return nEleVeto==0;                      }});
  analysis_cuts['f'].push_back({ .name="0Mu",        .func = []    { return nMuVeto==0;                       }});
  analysis_cuts['f'].push_back({ .name="0Tau",       .func = []    { return nTauVeto==0;                      }});
  analysis_cuts['f'].push_back({ .name="0isob",      .func = []    { return nLooseIsoBTag==0;                 }}); 
  analysis_cuts['f'].push_back({ .name="0LepJet",    .func = []    { return nLepJet==0;                       }});
  analysis_cuts['f'].push_back({ .name="0LepTop",    .func = []    { return nLepTop==0;                       }});
  analysis_cuts['f'].push_back({ .name="dPhi",       .func = []    { return dPhiRazor<2.8;                    }});
  analysis_cuts['f'].push_back({ .name="0HadTop",    .func = []    { return nHadTop==0;                       }}); // Additional
  analysis_cuts['f'].push_back({ .name="1HadV",      .func = []    { return nHadV==1;                         }}); // Additional
  // had 0b, 2V, 2-4 jet
  analysis_cuts['g'].push_back({ .name="1JetAK8",    .func = []    { return nJetAK8>=1;                       }});
  analysis_cuts['g'].push_back({ .name="NJet",       .func = []    { return nJet>=2&&nJet<=4;                 }}); // Tighter than presel
  analysis_cuts['g'].push_back({ .name="MR",         .func = []    { return MR>=800;                          }});
  analysis_cuts['g'].push_back({ .name="R2",         .func = []    { return R2>=0.08;                         }});
  analysis_cuts['g'].push_back({ .name="HLT",        .func =                boost_triggers                     });
  analysis_cuts['g'].push_back({ .name="0Ele",       .func = []    { return nEleVeto==0;                      }});
  analysis_cuts['g'].push_back({ .name="0Mu",        .func = []    { return nMuVeto==0;                       }});
  analysis_cuts['g'].push_back({ .name="0Tau",       .func = []    { return nTauVeto==0;                      }});
  analysis_cuts['g'].push_back({ .name="0isob",      .func = []    { return nLooseIsoBTag==0;                 }}); 
  analysis_cuts['g'].push_back({ .name="0LepJet",    .func = []    { return nLepJet==0;                       }});
  analysis_cuts['g'].push_back({ .name="0LepTop",    .func = []    { return nLepTop==0;                       }});
  analysis_cuts['g'].push_back({ .name="dPhi",       .func = []    { return dPhiRazor<2.8;                    }});
  analysis_cuts['g'].push_back({ .name="0HadTop",    .func = []    { return nHadTop==0;                       }}); // Additional
  analysis_cuts['g'].push_back({ .name="1HadV",      .func = []    { return nHadV==2;                         }}); // Additional
  // had 0b, 2V, 5+ jet
  analysis_cuts['h'].push_back({ .name="1JetAK8",    .func = []    { return nJetAK8>=1;                       }});
  analysis_cuts['h'].push_back({ .name="NJet",       .func = []    { return nJet>=5;                          }}); // Tighter than presel
  analysis_cuts['h'].push_back({ .name="MR",         .func = []    { return MR>=800;                          }});
  analysis_cuts['h'].push_back({ .name="R2",         .func = []    { return R2>=0.08;                         }});
  analysis_cuts['h'].push_back({ .name="HLT",        .func =                boost_triggers                     });
  analysis_cuts['h'].push_back({ .name="0Ele",       .func = []    { return nEleVeto==0;                      }});
  analysis_cuts['h'].push_back({ .name="0Mu",        .func = []    { return nMuVeto==0;                       }});
  analysis_cuts['h'].push_back({ .name="0Tau",       .func = []    { return nTauVeto==0;                      }});
  analysis_cuts['h'].push_back({ .name="0isob",      .func = []    { return nLooseIsoBTag==0;                 }}); 
  analysis_cuts['h'].push_back({ .name="0LepJet",    .func = []    { return nLepJet==0;                       }});
  analysis_cuts['h'].push_back({ .name="0LepTop",    .func = []    { return nLepTop==0;                       }});
  analysis_cuts['h'].push_back({ .name="dPhi",       .func = []    { return dPhiRazor<2.8;                    }});
  analysis_cuts['h'].push_back({ .name="0HadTop",    .func = []    { return nHadTop==0;                       }}); // Additional
  analysis_cuts['h'].push_back({ .name="1HadV",      .func = []    { return nHadV==2;                         }}); // Additional

  // 1 Isolated lepton signal regions
  // 1 Isolated Lepton Preselection + MT  --> Test event selection
  analysis_cuts['1'].push_back({ .name="1JetAK8",    .func = []    { return nJetAK8>=1;                       }});
  analysis_cuts['1'].push_back({ .name="NJet",       .func = []    { return nJet>=2;                          }});
  analysis_cuts['1'].push_back({ .name="MR",         .func = []    { return MR>=800;                          }});
  analysis_cuts['1'].push_back({ .name="R2",         .func = []    { return R2>=0.08;                         }});
  analysis_cuts['1'].push_back({ .name="HLT",        .func =                boost_triggers                     });
  analysis_cuts['1'].push_back({ .name="1Lep",       .func = []    { return nLepSelect==1;                    }});
  analysis_cuts['1'].push_back({ .name="0LepJet",    .func = []    { return nLepJet==0;                       }});
  analysis_cuts['1'].push_back({ .name="0LepTop",    .func = []    { return nLepTop==0;                       }});
  analysis_cuts['1'].push_back({ .name="MT",         .func = []    { return MT>=120;                          }});
  // lep 1hadtop
  analysis_cuts['i'].push_back({ .name="1JetAK8",    .func = []    { return nJetAK8>=1;                       }});
  analysis_cuts['i'].push_back({ .name="NJet",       .func = []    { return nJet>=2;                          }});
  analysis_cuts['i'].push_back({ .name="MR",         .func = []    { return MR>=800;                          }});
  analysis_cuts['i'].push_back({ .name="R2",         .func = []    { return R2>=0.08;                         }});
  analysis_cuts['i'].push_back({ .name="HLT",        .func =                boost_triggers                     });
  analysis_cuts['i'].push_back({ .name="1Lep",       .func = []    { return nLepSelect==1;                    }}); 
  analysis_cuts['i'].push_back({ .name="0LepJet",    .func = []    { return nLepJet==0;                       }});
  analysis_cuts['i'].push_back({ .name="0LepTop",    .func = []    { return nLepTop==0;                       }});
  analysis_cuts['i'].push_back({ .name="MT",         .func = []    { return MT>=120;                          }});
  analysis_cuts['i'].push_back({ .name="1HadTop",    .func = []    { return nHadTop>=1;                       }}); // Additional
  // lep 1V+b
  analysis_cuts['j'].push_back({ .name="1JetAK8",    .func = []    { return nJetAK8>=1;                       }});
  analysis_cuts['j'].push_back({ .name="NJet",       .func = []    { return nJet>=3;                          }}); // Tighter than presel
  analysis_cuts['j'].push_back({ .name="MR",         .func = []    { return MR>=800;                          }});
  analysis_cuts['j'].push_back({ .name="R2",         .func = []    { return R2>=0.08;                         }});
  analysis_cuts['j'].push_back({ .name="HLT",        .func =                boost_triggers                     });
  analysis_cuts['j'].push_back({ .name="1Lep",       .func = []    { return nLepSelect==1;                    }}); 
  analysis_cuts['j'].push_back({ .name="0LepJet",    .func = []    { return nLepJet==0;                       }});
  analysis_cuts['j'].push_back({ .name="0LepTop",    .func = []    { return nLepTop==0;                       }});
  analysis_cuts['j'].push_back({ .name="MT",         .func = []    { return MT>=120;                          }});
  analysis_cuts['j'].push_back({ .name="0HadTop",    .func = []    { return nHadTop==0;                       }}); // Additional
  analysis_cuts['j'].push_back({ .name="1b",         .func = []    { return nMediumIsoBTag>=1;                }}); // Additional
  analysis_cuts['j'].push_back({ .name="1HadV",      .func = []    { return nHadV>=1;                         }}); // Additional
  // lep 1V+0b
  analysis_cuts['k'].push_back({ .name="1JetAK8",    .func = []    { return nJetAK8>=1;                       }});
  analysis_cuts['k'].push_back({ .name="NJet",       .func = []    { return nJet>=3;                          }}); // Tighter than presel
  analysis_cuts['k'].push_back({ .name="MR",         .func = []    { return MR>=800;                          }});
  analysis_cuts['k'].push_back({ .name="R2",         .func = []    { return R2>=0.08;                         }});
  analysis_cuts['k'].push_back({ .name="HLT",        .func =                boost_triggers                     });
  analysis_cuts['k'].push_back({ .name="1Lep",       .func = []    { return nLepSelect==1;                    }}); 
  analysis_cuts['k'].push_back({ .name="0LepJet",    .func = []    { return nLepJet==0;                       }});
  analysis_cuts['k'].push_back({ .name="0LepTop",    .func = []    { return nLepTop==0;                       }});
  analysis_cuts['k'].push_back({ .name="MT",         .func = []    { return MT>=120;                          }});
  analysis_cuts['k'].push_back({ .name="0HadTop",    .func = []    { return nHadTop==0;                       }}); // Additional
  analysis_cuts['k'].push_back({ .name="0isob",      .func = []    { return nLooseIsoBTag==0;                 }}); // Additional
  analysis_cuts['k'].push_back({ .name="1HadV",      .func = []    { return nHadV>=1;                         }}); // Additional

  // Non-isolated lepton signal regions
  // >=1 Nonisolated Preselection + MT + dPhi --> Test event selection
  analysis_cuts['N'].push_back({ .name="1JetAK8",    .func = []    { return nJetAK8>=1;                       }});
  analysis_cuts['N'].push_back({ .name="NJet",       .func = []    { return nJet>=2;                          }});
  analysis_cuts['N'].push_back({ .name="MR",         .func = []    { return MR>=800;                          }});
  analysis_cuts['N'].push_back({ .name="R2",         .func = []    { return R2>=0.08;                         }});
  analysis_cuts['N'].push_back({ .name="HLT",        .func =                boost_triggers                     });
  analysis_cuts['N'].push_back({ .name="1Lep",       .func = []    { return nLepTight2D>=1;                   }});
  analysis_cuts['N'].push_back({ .name="MT",         .func = []    { return MT_lepTight2D>=140;               }});
  analysis_cuts['N'].push_back({ .name="dPhiJet",    .func = []    { return dPhiBoostedJetLepMET>=0.8;        }});
  // 1leptop 0hadtop
  analysis_cuts['l'].push_back({ .name="1JetAK8",    .func = []    { return nJetAK8>=1;                       }});
  analysis_cuts['l'].push_back({ .name="NJet",       .func = []    { return nJet>=3;                          }}); // Tighter than presel
  analysis_cuts['l'].push_back({ .name="MR",         .func = []    { return MR>=800;                          }});
  analysis_cuts['l'].push_back({ .name="R2",         .func = []    { return R2>=0.08;                         }});
  analysis_cuts['l'].push_back({ .name="HLT",        .func =                boost_triggers                     });
  analysis_cuts['l'].push_back({ .name="1LepTop",    .func = []    { return nLepTop>=1;                       }}); // Additional
  analysis_cuts['l'].push_back({ .name="0LepJet",    .func = []    { return nLepJet==0;                       }}); // Additional
  analysis_cuts['l'].push_back({ .name="MT",         .func = []    { return MT_lepTight2D>=140;               }});
  analysis_cuts['l'].push_back({ .name="dPhiJet",    .func = []    { return dPhiBoostedJetLepMET>=0.8;        }});
  analysis_cuts['l'].push_back({ .name="0HadTop",    .func = []    { return nHadTop==0;                       }}); // Additional
  // 1leptop 1hadtop
  analysis_cuts['m'].push_back({ .name="1JetAK8",    .func = []    { return nJetAK8>=1;                       }});
  analysis_cuts['m'].push_back({ .name="NJet",       .func = []    { return nJet>=3;                          }}); // Tighter than presel
  analysis_cuts['m'].push_back({ .name="MR",         .func = []    { return MR>=800;                          }});
  analysis_cuts['m'].push_back({ .name="R2",         .func = []    { return R2>=0.08;                         }});
  analysis_cuts['m'].push_back({ .name="HLT",        .func =                boost_triggers                     });
  analysis_cuts['m'].push_back({ .name="1LepTop",    .func = []    { return nLepTop>=1;                       }}); // Additional
  analysis_cuts['m'].push_back({ .name="0LepJet",    .func = []    { return nLepJet==0;                       }}); // Additional
  analysis_cuts['m'].push_back({ .name="MT",         .func = []    { return MT_lepTight2D>=140;               }});
  analysis_cuts['m'].push_back({ .name="dPhiJet",    .func = []    { return dPhiBoostedJetLepMET>=0.8;        }});
  analysis_cuts['m'].push_back({ .name="1HadTop",    .func = []    { return nHadTop>=1;                       }}); // Additional
  // 1lepjet 0V, 2-4 jet
  analysis_cuts['n'].push_back({ .name="1JetAK8",    .func = []    { return nJetAK8>=1;                       }});
  analysis_cuts['n'].push_back({ .name="NJet",       .func = []    { return nJet>=2&&nJet<=4;                 }}); // Tighter than presel
  analysis_cuts['n'].push_back({ .name="MR",         .func = []    { return MR>=800;                          }});
  analysis_cuts['n'].push_back({ .name="R2",         .func = []    { return R2>=0.08;                         }});
  analysis_cuts['n'].push_back({ .name="HLT",        .func =                boost_triggers                     });
  analysis_cuts['n'].push_back({ .name="0LepTop",    .func = []    { return nLepTop==0;                       }}); // Additional
  analysis_cuts['n'].push_back({ .name="0HadTop",    .func = []    { return nHadTop==0;                       }}); // Additional
  analysis_cuts['n'].push_back({ .name="1LepJet",    .func = []    { return nLepJet>=1;                       }}); // Additional
  analysis_cuts['n'].push_back({ .name="MT",         .func = []    { return MT_lepTight2D>=140;               }});
  analysis_cuts['n'].push_back({ .name="dPhiJet",    .func = []    { return dPhiBoostedJetLepMET>=0.8;        }});
  analysis_cuts['n'].push_back({ .name="0HadV",      .func = []    { return nHadV==0;                         }}); // Additional
  // 1lepjet 0V, 5+ jet
  analysis_cuts['o'].push_back({ .name="1JetAK8",    .func = []    { return nJetAK8>=1;                       }});
  analysis_cuts['o'].push_back({ .name="NJet",       .func = []    { return nJet>=5;                          }}); // Tighter than presel
  analysis_cuts['o'].push_back({ .name="MR",         .func = []    { return MR>=800;                          }});
  analysis_cuts['o'].push_back({ .name="R2",         .func = []    { return R2>=0.08;                         }});
  analysis_cuts['o'].push_back({ .name="HLT",        .func =                boost_triggers                     });
  analysis_cuts['o'].push_back({ .name="0LepTop",    .func = []    { return nLepTop==0;                       }}); // Additional
  analysis_cuts['o'].push_back({ .name="0HadTop",    .func = []    { return nHadTop==0;                       }}); // Additional
  analysis_cuts['o'].push_back({ .name="1LepJet",    .func = []    { return nLepJet>=1;                       }}); // Additional
  analysis_cuts['o'].push_back({ .name="MT",         .func = []    { return MT_lepTight2D>=140;               }});
  analysis_cuts['o'].push_back({ .name="dPhiJet",    .func = []    { return dPhiBoostedJetLepMET>=0.8;        }});
  analysis_cuts['o'].push_back({ .name="0HadV",      .func = []    { return nHadV==0;                         }}); // Additional
  // 1lepjet 1V, 2-4 jet
  analysis_cuts['p'].push_back({ .name="1JetAK8",    .func = []    { return nJetAK8>=1;                       }});
  analysis_cuts['p'].push_back({ .name="NJet",       .func = []    { return nJet>=2&&nJet<=4;                 }}); // Tighter than presel
  analysis_cuts['p'].push_back({ .name="MR",         .func = []    { return MR>=800;                          }});
  analysis_cuts['p'].push_back({ .name="R2",         .func = []    { return R2>=0.08;                         }});
  analysis_cuts['p'].push_back({ .name="HLT",        .func =                boost_triggers                     });
  analysis_cuts['p'].push_back({ .name="0LepTop",    .func = []    { return nLepTop==0;                       }}); // Additional
  analysis_cuts['p'].push_back({ .name="0HadTop",    .func = []    { return nHadTop==0;                       }}); // Additional
  analysis_cuts['p'].push_back({ .name="1LepJet",    .func = []    { return nLepJet>=1;                       }}); // Additional
  analysis_cuts['p'].push_back({ .name="MT",         .func = []    { return MT_lepTight2D>=140;               }});
  analysis_cuts['p'].push_back({ .name="dPhiJet",    .func = []    { return dPhiBoostedJetLepMET>=0.8;        }});
  analysis_cuts['p'].push_back({ .name="0HadV",      .func = []    { return nHadV==1;                         }}); // Additional
  // 1lepjet 1V, 5+ jet
  analysis_cuts['q'].push_back({ .name="1JetAK8",    .func = []    { return nJetAK8>=1;                       }});
  analysis_cuts['q'].push_back({ .name="NJet",       .func = []    { return nJet>=5;                          }}); // Tighter than presel
  analysis_cuts['q'].push_back({ .name="MR",         .func = []    { return MR>=800;                          }});
  analysis_cuts['q'].push_back({ .name="R2",         .func = []    { return R2>=0.08;                         }});
  analysis_cuts['q'].push_back({ .name="HLT",        .func =                boost_triggers                     });
  analysis_cuts['q'].push_back({ .name="0LepTop",    .func = []    { return nLepTop==0;                       }}); // Additional
  analysis_cuts['q'].push_back({ .name="0HadTop",    .func = []    { return nHadTop==0;                       }}); // Additional
  analysis_cuts['q'].push_back({ .name="1LepJet",    .func = []    { return nLepJet>=1;                       }}); // Additional
  analysis_cuts['q'].push_back({ .name="MT",         .func = []    { return MT_lepTight2D>=140;               }});
  analysis_cuts['q'].push_back({ .name="dPhiJet",    .func = []    { return dPhiBoostedJetLepMET>=0.8;        }});
  analysis_cuts['q'].push_back({ .name="1HadV",      .func = []    { return nHadV==1;                         }}); // Additional
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
  double sf_btag_loose = sf_btag.first, sf_btag_medium = sf_btag.second;
  i+=2;

#if TOP == 0
  // W tagging SF  (4 sigma - fullsim, fastsim, mistag, mistag fastsim)
  //double sf_w = calc_w_tagging_sf(data, nSigmaSFs[i][s], nSigmaSFs[i+1][s], nSigmaSFs[i+2][s], nSigmaSFs[i+3][s], isFastSim);
  // fake W tagging SFs (2 sigma)
  //double sf_fake_mW = calc_fake_w_mass_tagging_sf(data, nSigmaSFs[i+4][s]);
  //double sf_fake_aW = calc_fake_w_anti_tagging_sf(data, nSigmaSFs[i+5][s]);
#endif
  i+=6;

#if TOP != 0
  // top tagging SF (4 sigma - fullsim, fastsim, mistag, mistag fastsim)
  //double sf_top = calc_top_tagging_sf(data, nSigmaSFs[i][s], nSigmaSFs[i+1][s], nSigmaSFs[i+2][s], nSigmaSFs[i+3][s], isFastSim);
  // fake top tagging SFs (3 sigmas)
  //double sf_fake_0b_mTop = calc_fake_top_0b_mass_tagging_sf(data, nSigmaSFs[i+4][s]);
  //double sf_fake_MTop = calc_fake_top_mass_tagging_sf(data, nSigmaSFs[i+5][s]);
  //double sf_fake_aTop = calc_fake_top_anti_tagging_sf(data, nSigmaSFs[i+6][s]);
#endif
  i+=7;

  //double sf_ele_veto=1,  sf_ele_medium=1;
  //double sf_muon_veto=1, sf_muon_medium=1;
  //double sf_btag_loose = 1, sf_btag_medium = 1;
  /*
    #if TOP == 0
    double sf_fake_mW=1, sf_fake_aW=1, sf_w=1;
    #else
    double sf_top=1, sf_fake_0b_mTop=1, sf_fake_MTop=1, sf_fake_aTop=1;
    #endif
    i+=13;
  */
  // Select scale factors to use
  for (auto& sf : scale_factors) sf.second.clear();

#if TOP == 0

  scale_factors['S'].push_back(sf_ele_veto);
  scale_factors['S'].push_back(sf_muon_veto);
  scale_factors['S'].push_back(sf_btag_medium);

  scale_factors['s'] = scale_factors['S'];

  scale_factors['Q'].push_back(sf_ele_veto);
  scale_factors['Q'].push_back(sf_muon_veto);
  scale_factors['Q'].push_back(sf_btag_loose);

  scale_factors['q'] = scale_factors['Q'];

  scale_factors['T'].push_back(sf_ele_veto);
  scale_factors['T'].push_back(sf_muon_veto);
  scale_factors['T'].push_back(sf_btag_medium);

  scale_factors['W'].push_back(sf_ele_veto);
  scale_factors['W'].push_back(sf_muon_veto);
  scale_factors['W'].push_back(sf_btag_loose);

  scale_factors['L'] = scale_factors['W'];

  scale_factors['Z'].push_back(sf_ele_medium);
  scale_factors['Z'].push_back(sf_muon_medium);

  scale_factors['G'].push_back(sf_ele_veto);
  scale_factors['G'].push_back(sf_muon_veto);

  scale_factors['z'].push_back(sf_ele_medium);
  scale_factors['z'].push_back(sf_muon_medium);

#else

  // Top Analysis
  scale_factors['S'].push_back(sf_ele_veto);
  scale_factors['S'].push_back(sf_muon_veto);

  scale_factors['s'] = scale_factors['S'];

  scale_factors['Q'].push_back(sf_ele_veto);
  scale_factors['Q'].push_back(sf_muon_veto);
  scale_factors['Q'].push_back(sf_btag_loose);

  scale_factors['q'] = scale_factors['Q'];

  scale_factors['T'].push_back(sf_ele_veto);
  scale_factors['T'].push_back(sf_muon_veto);

  scale_factors['W'].push_back(sf_ele_veto);
  scale_factors['W'].push_back(sf_muon_veto);
  scale_factors['W'].push_back(sf_btag_loose);

  scale_factors['G'].push_back(sf_ele_veto);
  scale_factors['G'].push_back(sf_muon_veto);

  scale_factors['Z'].push_back(sf_ele_medium);
  scale_factors['Z'].push_back(sf_muon_medium);

  scale_factors['L'] = scale_factors['W'];

#endif

  scale_factors['F'].push_back(sf_ele_veto);
  scale_factors['F'].push_back(sf_muon_veto);
  scale_factors['F'].push_back(sf_btag_loose);
  scale_factors['B'].push_back(sf_ele_veto);
  scale_factors['B'].push_back(sf_muon_veto);
  scale_factors['B'].push_back(sf_btag_medium);

  scale_factors['H'].push_back(sf_ele_veto);
  scale_factors['H'].push_back(sf_muon_veto);
  scale_factors['H'].push_back(sf_btag_medium);

  // veto lep
  scale_factors['a'].push_back(sf_ele_veto);
  scale_factors['a'].push_back(sf_muon_veto);
  scale_factors['b'] = scale_factors['a'];

  // veto lep, 1b
  scale_factors['0'].push_back(sf_ele_veto);
  scale_factors['0'].push_back(sf_muon_veto);
  scale_factors['0'].push_back(sf_btag_medium);
  scale_factors['c'] = scale_factors['d'] = scale_factors['0'];

  // veto lep, 0b
  scale_factors['e'].push_back(sf_ele_veto);
  scale_factors['e'].push_back(sf_muon_veto);
  scale_factors['e'].push_back(sf_btag_loose);
  scale_factors['f'] = scale_factors['g'] = scale_factors['g'] = scale_factors['e'];
  
  // lep
  scale_factors['1'].push_back(sf_ele_medium);
  scale_factors['1'].push_back(sf_muon_medium);
  scale_factors['i'] = scale_factors['1'];

  // lep, 1b
  scale_factors['j'].push_back(sf_ele_medium);
  scale_factors['j'].push_back(sf_muon_medium);
  scale_factors['j'].push_back(sf_btag_medium);
  
  // lep, 0b
  scale_factors['k'].push_back(sf_ele_medium);
  scale_factors['k'].push_back(sf_muon_medium);
  scale_factors['k'].push_back(sf_btag_loose);
  
  // 0b
  scale_factors['n'].push_back(sf_btag_loose);
  scale_factors['o'] = scale_factors['p'] = scale_factors['q'] = scale_factors['n'];
  
  // N-1 weights
  // Calculate weight for all search regions, but without a specific weight
  for (const auto& region : analysis_cuts) w_nm1[region.first].resize(20,1);
  if (!isData) for (const auto& region : analysis_cuts) {
    size_t n=all_weights.size()+scale_factors[region.first].size();
    // [i] is the index of the weight to exclude
    for (size_t i=0; i<n; ++i) {
      w_nm1[region.first][i] = 1;
      // [j] all the rest is applied
      for (size_t j=0; j<n; ++j) if (j!=i) {
        if (j<all_weights.size()) w_nm1[region.first][i] *= all_weights[j];
        else  w_nm1[region.first][i] *= scale_factors[region.first][j-all_weights.size()];
      }
    }
  }
}

//_______________________________________________________
//                 Signal Region
//     Must define it, because we blind it in data!

bool
Analysis::signal_selection(const eventBuffer& data) {
  //return apply_all_cuts('S');
 return 0;
}

// Methods used by SmartHistos (Plotter)
// Can leave them empty

//_______________________________________________________
//      Define Histo options: Filling/Postfixes

std::vector<std::string> all_cuts;

Analysis::PostfixOptions
Analysis::get_pf_opts_(std::vector<std::vector<Sample> > lists, std::string dirname) {
  std::vector<Sample> samples;
  for (auto list : lists) samples.insert(samples.end(), list.begin(), list.end());
  PostfixOptions opt{ (size_t)-1, "", "", "" };
  for (size_t i=0; i<samples.size(); ++i) {
    // Find index of matching directory
    for (size_t j=0; j<samples[i].dirs.size(); ++j)
      if (samples[i].dirs[j] == dirname) opt.index = i;
    opt.postfixes += samples[i].postfix;
    opt.legends += samples[i].legend;
    opt.colors += samples[i].color;
    if (i+1!=samples.size()) {
      opt.postfixes +=  ";";
      opt.legends += ";";
      opt.colors += ",";
    }
  }
  return opt;
}

void add_unrolled_bins(SmartHistos& sh,
                       std::string param_name, std::string axis1_title, std::string axis2_title,
                       std::function<double()> var1, std::function<double()> var2,
                       std::vector<double> bins1, std::vector<double> bins2,
                       std::vector<int> merged_bins = {}, int precision1=0, int precision2=0, bool shrink_merged=false) {
  //std::cout<<param_name<<std::endl;
  std::vector<double> xbins = { 0 };
  std::map<int, std::string> bin1_labels, bin2_labels;
  std::stringstream label1, label2;
  size_t bin = 0, actual_bin = 0, big_bin = 0;
  for (size_t i=0, n=bins1.size(); i<n; ++i) {
    if (i!=0) {
      if (precision1) label1<<std::setprecision(precision1);
      label1<<bins1[i]<<"]";
      bin1_labels[big_bin] = label1.str();
    }
    if (i+1!=n){
      label1.str("");
      if (precision1) label1<<std::setprecision(precision1);
      label1<<"["<<bins1[i]<<", ";
      big_bin = shrink_merged ? actual_bin : bin;
      for (size_t j=0, m=bins2.size(); j<m; ++j) {
        if (j!=0) bin++;
        // Check if this bin is meant to be merged with the next one
        bool merge = false;
        for (auto merged_bin : merged_bins) if (bin==merged_bin) merge = true;
        if (!merge) {
          // Create bin label
          if (j!=0) {
            if (precision2) label2<<std::setprecision(precision2);
            label2<<bins2[j]<<"]";
            bin2_labels[++actual_bin] = label2.str();
            if (!merged_bins.empty()) xbins.push_back(shrink_merged ? actual_bin : bin);
          }
          if (j+1!=m){
            label2.str("");
            if (precision2) label2<<std::setprecision(precision2);
            label2<<"["<<bins2[j]<<", ";
          }
        }
      }
    }
  }
  if (merged_bins.empty()) xbins.push_back(bin);
  //for (auto xbin : xbins)
  //  std::cout<<xbin<<", ";
  //std::cout<<std::endl<<std::endl;
  if (shrink_merged) {
    sh.AddNewUnrolledFillParams(param_name, { .nbin=actual_bin, .bins=xbins, .bin_labels=bin2_labels, .unrolled_bin_labels=bin1_labels, .fill=[bins1,bins2,var1,var2,merged_bins] {
                                    double bin = -1, v1 = var1(), v2 = var2();
                                    for (size_t i=0, n=bins1.size(); i+1<n; ++i) if (v1>=bins1[i]&&v1<bins1[i+1])
                                      for (size_t j=0, m=bins2.size(); j+1<m; ++j) if (v2>=bins2[j]&&v2<bins2[j+1])
                                        bin = i*(m-1)+j;
                                    for (auto merged_bin : merged_bins) if (bin>=merged_bin) --bin;
                                    return bin;
                                  }, .axis_title=axis2_title, .unrolled_axis_title=axis1_title});
  } else {
    sh.AddNewUnrolledFillParams(param_name, { .nbin=actual_bin, .bins=xbins, .bin_labels=bin2_labels, .unrolled_bin_labels=bin1_labels, .fill=[bins1,bins2,var1,var2] {
                                    double bin = -1, v1 = var1(), v2 = var2();
                                    for (size_t i=0, n=bins1.size(); i+1<n; ++i) if (v1>=bins1[i]&&v1<bins1[i+1])
                                      for (size_t j=0, m=bins2.size(); j+1<m; ++j) if (v2>=bins2[j]&&v2<bins2[j+1])
                                        bin = i*(m-1)+j;
                                    return bin;
                                  }, .axis_title=axis2_title, .unrolled_axis_title=axis1_title});
  }
}

void
Analysis::define_histo_options(const double& weight, const eventBuffer& d, const unsigned int& syst_nSyst,
                               const unsigned int& syst_index, bool runOnSkim=false)
{
  const int debug = 0;

  if (debug) std::cout<<"Analysis::define_histo_options: start"<<std::endl;

  sh.SetHistoWeights({ [&weight] { return weight; } });

  // Keep this to be able to use analysis cuts
  define_preselections(d);
  define_selections(d);
  if (debug) std::cout<<"Analysis::define_histo_options: weight, selections ok"<<std::endl;

  // Initialize containers for N-1 weights
  for (const auto& region : analysis_cuts) w_nm1[region.first].resize(20,1);

  if (debug) std::cout<<"Analysis::define_histo_options: set containers ok"<<std::endl;

  // --------------------------------------------------------------------
  //                            Colors
  // --------------------------------------------------------------------

  // Common Histo colorings
  // 400 kYellow  800 kOrange
  // 416 kGreen	  820 kSpring
  // 432 kCyan	  840 kTeal
  // 600 kBlue	  860 kAzure
  // 616 kMagenta 880 kViolet
  // 632 kRed     900 kPink

  std::string col3_red_to_blue = "633,618,601,"; // red, purple, blue
  std::string col4_red_to_cyan = "633,618,601,434,"; // Red, purple, blue, cyan
  std::string col4_cyan_to_red = "434,601,618,633,"; // Cyan, blue, purple, red
  std::string col5_green_to_red = "418,434,601,618,633,"; // green, cyan, blue, purple, red
  std::string col5_red_to_green = "633,618,601,434,418,"; // red, , purple, blue, cyan, green
  std::string col6_rainbow_dark = "601,434,418,402,633,618,"; // blue, cyan, green, yellow, red, purple
  std::string col8 = "1,601,434,418,402,807,633,618,"; // above plus black and orange
  std::string col10 = "4,6,2,800,402,417,433,9,618,633,";
  std::string col12 = "1,4,6,2,800,402,417,433,9,618,633,924,"; // black, blue, magenta, red, orange, darker yellow, darker green, darker cyan, blue-purple, dark purple, dark red
  std::string col12_rainbow = "402,416,433,600,617,632,802,813,833,863,883,892,"; // Go around first bright and then dark colors

  // --------------------------------------------------------------------
  //                            Cuts
  // --------------------------------------------------------------------

  // Pass each cut
  //sh.AddNewCut("PassAnaSelection",    [this] { return analysis_cuts['S'][cut_index].func(); });
  sh.AddNewCut("P", [] { return pass_all_cuts['P']; });

  //__________________________________
  //            Postfixes
  //__________________________________

  // Postfixes are vector definitions for histograms
  // They attach _<string> after histogram names
  // where <string> is chosen from a vector of strings
  // you need to give a natural number as a vector index
  // for the histogram to choose which histo to fill

  // Notation:
  // AddNewPostfix("Name of Postfix", lambda function returning non-negative integer, "postfix 1;2;3; ...", "legend text 1;2;3; ...", "ROOT color 1,2,3, ...")


  // Sample postfixes
  // Determine them from the directory names in which the input files are
  // Map directory names to postfix name, legend entry and color
  std::vector<Sample> bkg_ttbars;
  bkg_ttbars.push_back({ .postfix="TT_powheg_pythia8",        .legend="t#bar{t}+jets",                       .color="418",/*DGreen*/
                           .dirs={ "TTTo2L2Nu_TuneCP5_13TeV-powheg-pythia8",
                                   "TTToHadronic_TuneCP5_13TeV-powheg-pythia8",
                                   "TTToSemiLeptonic_TuneCP5_13TeV-powheg-pythia8" } });

  if (debug) std::cout<<"Analysis::define_histo_options: ok1"<<std::endl;
  std::vector<Sample> bkg_nonttbars;
  /*
    Signal colors:
    "12"  //DarkGrey
    "862" //Azure
    "841" //Teal
    "804" //DarkOrange
    "403" //DarkYellow

    Free colors:
  */

  if (debug) std::cout<<"Analysis::define_histo_options: ok2"<<std::endl;
  bkg_nonttbars.push_back({ .postfix="Multijet",   .legend="Multijet",                                .color="607",/*DMagen*/ .dirs={ 
                              "QCD_HT1000to1500_TuneCP5_13TeV-madgraph-pythia8",
                              "QCD_HT100to200_TuneCP5_13TeV-madgraph-pythia8",
                              "QCD_HT1500to2000_TuneCP5_13TeV-madgraph-pythia8",
                              "QCD_HT2000toInf_TuneCP5_13TeV-madgraph-pythia8",
                              "QCD_HT200to300_TuneCP5_13TeV-madgraph-pythia8",
                              "QCD_HT300to500_TuneCP5_13TeV-madgraph-pythia8",
                              "QCD_HT500to700_TuneCP5_13TeV-madgraph-pythia8",
                              "QCD_HT700to1000_TuneCP5_13TeV-madgraph-pythia8",
                              "DYJetsToQQ_HT180_13TeV_TuneCP5-madgraphMLM-pythia8",
                              "WJetsToQQ_HT400to600_TuneCP5_13TeV-madgraphMLM-pythia8",
                              "WJetsToQQ_HT600to800_TuneCP5_13TeV-madgraphMLM-pythia8",
                              "ZJetsToQQ_HT400to600_TuneCP5_13TeV-madgraphMLM-pythia8",
                              "ZJetsToQQ_HT-800toInf_TuneCP5_13TeV-madgraphMLM-pythia8",
                              "WWTo4Q_NNPDF31_TuneCP5_13TeV-powheg-pythia8" } });

  bkg_nonttbars.push_back({ .postfix="WToLNu",     .legend="W+jets",                      .color="633",/*DRed*/  .dirs={
                              "WJetsToLNu_HT-100To200_TuneCP5_13TeV-madgraphMLM-pythia8",
                              "WJetsToLNu_HT-200To400_TuneCP5_13TeV-madgraphMLM-pythia8",
                              "WJetsToLNu_HT-400To600_TuneCP5_13TeV-madgraphMLM-pythia8",
                              "WJetsToLNu_HT-600To800_TuneCP5_13TeV-madgraphMLM-pythia8",
                              "WJetsToLNu_HT-800To1200_TuneCP5_13TeV-madgraphMLM-pythia8",
                              "WJetsToLNu_HT-1200To2500_TuneCP5_13TeV-madgraphMLM-pythia8",
                              "WJetsToLNu_HT-2500ToInf_TuneCP5_13TeV-madgraphMLM-pythia8"
			    } });
  bkg_nonttbars.push_back({ .postfix="ZToNuNu",    .legend=/*"#gamma*"/*/"Z#rightarrow#nu#nu",      .color="433",/*Cyan*/ .dirs={ 
                              "ZJetsToNuNu_HT-100To200_13TeV-madgraph",
                              "ZJetsToNuNu_HT-200To400_13TeV-madgraph",
                              "ZJetsToNuNu_HT-400To600_13TeV-madgraph",
                              "ZJetsToNuNu_HT-600To800_13TeV-madgraph",
                              "ZJetsToNuNu_HT-800To1200_13TeV-madgraph",
                              "ZJetsToNuNu_HT-1200To2500_13TeV-madgraph",
                              "ZJetsToNuNu_HT-2500ToInf_13TeV-madgraph" } });
  bkg_nonttbars.push_back({ .postfix="Multiboson", .legend="VV(V)+t#bar{t}X",                         .color="922",/*DGray*/   .dirs={
                              "WWTo1L1Nu2Q_13TeV_amcatnloFXFX_madspin_pythia8",
                              "WWTo2L2Nu_NNPDF31_TuneCP5_13TeV-powheg-pythia8",
                              "WWToLNuQQ_NNPDF31_TuneCP5_13TeV-powheg-pythia8",
                              "WZTo1L1Nu2Q_13TeV_amcatnloFXFX_madspin_pythia8",
                              "WZTo2L2Q_13TeV_amcatnloFXFX_madspin_pythia8",
                              "WZTo3LNu_TuneCP5_13TeV-amcatnloFXFX-pythia8",
                              "ZZTo2L2Nu_13TeV_powheg_pythia8",
                              "ZZTo2L2Q_13TeV_amcatnloFXFX_madspin_pythia8",
                              "ZZTo2Q2Nu_TuneCP5_13TeV_amcatnloFXFX_madspin_pythia8",
                              "ZZTo4L_13TeV_powheg_pythia8",
                              "WWW_4F_TuneCP5_13TeV-amcatnlo-pythia8",
                              "WWZ_4F_TuneCP5_13TeV-amcatnlo-pythia8",
                              "WZZ_TuneCP5_13TeV-amcatnlo-pythia8",
                              "ZZZ_TuneCP5_13TeV-amcatnlo-pythia8",
                              "TTWJetsToLNu_TuneCP5_13TeV-amcatnloFXFX-madspin-pythia8",
                              "TTWJetsToQQ_TuneCP5_13TeV-amcatnloFXFX-madspin-pythia8",
                              "TTZToLLNuNu_M-10_TuneCP5_13TeV-amcatnlo-pythia8",
                              "TTZToQQ_TuneCP5_13TeV-amcatnlo-pythia8",
                              "TTTT_TuneCP5_13TeV-amcatnlo-pythia8",
			    } });
  bkg_nonttbars.push_back({ .postfix="Top",        .legend="Single t",                              .color="797",/*Orange*/   .dirs={
                              "ST_s-channel_4f_leptonDecays_TuneCP5_13TeV-amcatnlo-pythia8",
                              "ST_t-channel_antitop_4f_inclusiveDecays_TuneCP5_13TeV-powhegV2-madspin-pythia8",
                              "ST_t-channel_top_4f_inclusiveDecays_TuneCP5_13TeV-powhegV2-madspin-pythia8",
                              "ST_tW_antitop_5f_NoFullyHadronicDecays_TuneCP5_13TeV-powheg-pythia8",
                              "ST_tW_top_5f_NoFullyHadronicDecays_TuneCP5_13TeV-powheg-pythia8"
			    } });
  //bkg_nonttbars.push_back({ .postfix="DYToLL",     .legend="Drell-Yan",                               .color="803",/*Brown*/  .dirs={ 
  bkg_nonttbars.push_back({ .postfix="DYToLL",     .legend="Z#rightarrowll",                            .color="593",/*Blue*/  .dirs={
                              ",DYJetsToLL_M-4to50_HT-200to400_TuneCP5_13TeV-madgraphMLM-pythia8",
                              ",DYJetsToLL_M-4to50_HT-400to600_TuneCP5_13TeV-madgraphMLM-pythia8",
                              ",DYJetsToLL_M-4to50_HT-600toInf_TuneCP5_13TeV-madgraphMLM-pythia8",
                              ",DYJetsToLL_M-50_HT-100to200_TuneCP5_13TeV-madgraphMLM-pythia8",
                              ",DYJetsToLL_M-50_HT-200to400_TuneCP5_13TeV-madgraphMLM-pythia8",
                              ",DYJetsToLL_M-50_HT-2500toInf_TuneCP5_13TeV-madgraphMLM-pythia8",
                              ",DYJetsToLL_M-50_HT-400to600_TuneCP5_13TeV-madgraphMLM-pythia8",
                              ",DYJetsToLL_M-50_HT-600to800_TuneCP5_13TeV-madgraphMLM-pythia8",
                              ",DYJetsToLL_M-50_HT-800to1200_TuneCP5_13TeV-madgraphMLM-pythia8",
                              ",DYJetsToLL_M-50_HT-1200to2500_TuneCP5_13TeV-madgraphMLM-pythia8"
			    } });
  //bkg_nonttbars.push_back({ .postfix="GJets",      .legend="#gamma+jets",                             .color="803",/*Brown*/  .dirs={ 
  bkg_nonttbars.push_back({ .postfix="GJets",      .legend="#gamma+jets",                             .color="800",/*Orange*/  .dirs={
                              "GJets_HT-40To100_TuneCP5_13TeV-madgraphMLM-pythia8",
                              "GJets_HT-100To200_TuneCP5_13TeV-madgraphMLM-pythia8",
                              "GJets_HT-200To400_TuneCP5_13TeV-madgraphMLM-pythia8",
                              "GJets_HT-400To600_TuneCP5_13TeV-madgraphMLM-pythia8",
                              "GJets_HT-600ToInf_TuneCP5_13TeV-madgraphMLM-pythia8"
			    } });

  std::vector<Sample> bkg_all, bkg_selected, ttbar_selected, multijet, znunu, gjets;
  bkg_all.insert(bkg_all.end(), bkg_ttbars.begin(), bkg_ttbars.end());
  bkg_all.insert(bkg_all.end(), bkg_nonttbars.begin(), bkg_nonttbars.end());
  ttbar_selected.push_back(bkg_ttbars[0]); // powheg
  bkg_selected  .push_back(bkg_ttbars[0]); // powheg
  bkg_selected.insert(bkg_selected.end(), bkg_nonttbars.begin(), bkg_nonttbars.end());
  multijet.push_back(bkg_nonttbars[0]);
  znunu   .push_back(bkg_nonttbars[2]);
  gjets   .push_back(bkg_nonttbars[6]);

  if (debug) std::cout<<"Analysis::define_histo_options: ok3"<<std::endl;
  std::vector<Sample> data_all, data_selected, single_ele, single_mu, single_pho, jetht, met;
  data_all.push_back({ .postfix="Data",      .legend="Data",             .color="1", .dirs={
                         "JetHT_Run2017B",
                         "JetHT_Run2017C",
                         "JetHT_Run2017D",
                         "JetHT_Run2017E",
                         "JetHT_Run2017F",
                         "MET_Run2017B",
                         "MET_Run2017C",
                         "MET_Run2017D",
                         "MET_Run2017E",
                         "MET_Run2017F"
		       } });
  data_all.push_back({ .postfix="SingleEle", .legend="Data (SingleEle)", .color="1", .dirs={
                         "SingleElectron_Run2017B",
                         "SingleElectron_Run2017C",
                         "SingleElectron_Run2017D",
                         "SingleElectron_Run2017E",
                         "SingleElectron_Run2017F"
		       } });
  data_all.push_back({ .postfix="SingleMu",  .legend="Data (SingleMu)",  .color="1", .dirs={
                         "SingleMuon_Run2017B",
                         "SingleMuon_Run2017C",
                         "SingleMuon_Run2017D",
                         "SingleMuon_Run2017E",
                         "SingleMuon_Run2017F"
		       } });
  data_all.push_back({ .postfix="SinglePho",  .legend="Data (SinglePho)",  .color="1", .dirs={
                         "SinglePhoton_Run2017B",
                         "SinglePhoton_Run2017C",
                         "SinglePhoton_Run2017D",
                         "SinglePhoton_Run2017E",
                         "SinglePhoton_Run2017F"
		       } });
  data_all.push_back({ .postfix="JetHT",       .legend="Data (JetHT)",     .color="1", .dirs={
                         "JetHT_Run2017B",
                         "JetHT_Run2017C",
                         "JetHT_Run2017D",
                         "JetHT_Run2017E",
                         "JetHT_Run2017F"
		       } });
  data_all.push_back({ .postfix="MET",       .legend="Data (MET)",       .color="1", .dirs={
                         "MET_Run2017B",
                         "MET_Run2017C",
                         "MET_Run2017D",
                         "MET_Run2017E",
                         "MET_Run2017F"
		       } });
  data_all.push_back({ .postfix="HTMHT",     .legend="Data (HTMHT)",     .color="1", .dirs={
                         "HTMHT_Run2017B",
                         "HTMHT_Run2017C",
                         "HTMHT_Run2017D",
                         "HTMHT_Run2017E",
                         "HTMHT_Run2017F"
		       } });
  data_selected.push_back(data_all[0]);
  single_ele.push_back(data_all[1]);
  single_mu.push_back(data_all[2]);
  single_pho.push_back(data_all[3]);
  jetht.push_back(data_all[4]);
  met.push_back(data_all[5]);

  if (debug) std::cout<<"Analysis::define_histo_options: ok4"<<std::endl;
  std::vector<Sample> signal_all, signal_selected, signal_fastsim, signal_gluino, signal_stop, signal_chargino, signal_top, signal_V;
  std::vector<Sample> T2tt, T1tttt, T5ttcc, T5qqqqVV, TChiWZ;
  signal_all.push_back({ .postfix="T2tt",           .legend="T2tt",        .color="435",/*DCyan*/  .dirs={ 
                           "SMS-T2tt_mStop-250to350_TuneCP2_13TeV-madgraphMLM-pythia8_RunIIFall17NanoAODv4",
                           "SMS-T2tt_mStop-350to400_TuneCP2_13TeV-madgraphMLM-pythia8_RunIIFall17NanoAODv4",
                           "SMS-T2tt_mStop-400to1200_TuneCP2_13TeV-madgraphMLM-pythia8_RunIIFall17NanoAODv4",
                           "SMS-T2tt_mStop-1200to2000_TuneCP2_13TeV-madgraphMLM-pythia8_RunIIFall17NanoAODv4" } });
  signal_all.push_back({ .postfix="T1tttt",         .legend="T1tttt",      .color="601",/*Blue*/  .dirs={ "SMS-T1tttt_TuneCP2_13TeV-madgraphMLM-pythia8_RunIIFall17NanoAODv4" } });
  signal_all.push_back({ .postfix="T5ttcc",         .legend="T5ttcc",      .color="633",/*Red*/   .dirs={ 
                           "SMS-T5ttcc_TuneCP2_13TeV-madgraphMLM-pythia8_RunIIFall17NanoAODv4",
                           "SMS-T5ttcc_mGluino1750to2800_TuneCP2_13TeV-madgraphMLM-pythia8_RunIIFall17NanoAODv4" } });
  signal_all.push_back({ .postfix="T5qqqqVV",       .legend="T5qqqqVV",      .color="619",/*DMagen*/  .dirs={ "SMS-T5qqqqVV_TuneCP2_13TeV-madgraphMLM-pythia8" } });
  signal_all.push_back({ .postfix="TChiWZ",         .legend="TChiWZ",        .color="1",/*Black*/     .dirs={ "TChiWZ_NANOAODSIM" } });
  //signal_all.push_back({ .postfix="T5tttt",         .legend="T5tttt",      .color="619",/*DMagen*/.dirs={ "FastSim_SMS-T5tttt" } });
  
  signal_selected.push_back(signal_all[2]);
  for (int i=0; i<5; ++i) signal_fastsim .push_back(signal_all[i]);
  for (int i=0; i<1; ++i) signal_stop    .push_back(signal_all[i]);
  for (int i=1; i<4; ++i) signal_gluino  .push_back(signal_all[i]);
  for (int i=4; i<5; ++i) signal_chargino.push_back(signal_all[i]);
  for (int i=0; i<3; ++i) signal_top     .push_back(signal_all[i]);
  for (int i=3; i<5; ++i) signal_V       .push_back(signal_all[i]);
  T2tt    .push_back(signal_all[0]);
  T1tttt  .push_back(signal_all[1]);
  T5ttcc  .push_back(signal_all[2]);
  T5qqqqVV.push_back(signal_all[3]);
  TChiWZ  .push_back(signal_all[4]);
  //T5tttt.push_back(signal_all[1]);
  //T1ttbb.push_back(signal_all[3]);
  //T1ttbb_dM5to25.push_back(signal_all[4]);

  //"T5ttttDeg (m_{#tilde{g}}=1TeV)","1",/*Black*/
  //"T1tttt (m_{#tilde{g}}=1.5TeV)", "862",/*Azure*/
  //"T1tttt (m_{#tilde{g}}=1.5TeV, m_{#tilde{#chi}^{0}_{1}}=100GeV)", "841",/*Teal*/     
  //"T1tttt (m_{#tilde{g}}=1.2TeV, m_{#tilde{#chi}^{0}_{1}}=800GeV)", "843",/*DarkTeal*/ 
  //"T5ttttDeg (m_{#tilde{g}}=1TeV, 2,3-body)",                   "12", /*DarkGrey*/ 
  //"T2ttDeg (m_{#tilde{t}}=350GeV)",                             "434",/*Cyan*/     

  // Sample postfixes
  if (debug) std::cout<<"Analysis::define_histo_options: ok5"<<std::endl;
  static const PostfixOptions all_samples_opt=get_pf_opts_({data_all, bkg_all, signal_all}, sample);
  sh.AddNewPostfix("AllSamples", [] { return all_samples_opt.index; }, all_samples_opt.postfixes, all_samples_opt.legends, all_samples_opt.colors);

  static const PostfixOptions plot_samples_opt=get_pf_opts_({data_selected, signal_fastsim, bkg_selected}, sample);
  sh.AddNewPostfix("StackPlotSignal", [] { 
                     if (plot_samples_opt.index==1) {
		       if (susy_mass.first != 1200 || susy_mass.second != 200) return (size_t)-1; // T2tt
                     } else if (plot_samples_opt.index>=2 && plot_samples_opt.index<5) {
		       if (susy_mass.first != 2000 || susy_mass.second != 200) return (size_t)-1; // T1ttt/T5ttcc/T5qqqqVV
                     } else if (plot_samples_opt.index==5) {
		       if (susy_mass.first !=  700 || susy_mass.second != 200) return (size_t)-1; // TChiWZ
		     }
		     return plot_samples_opt.index; 
		   }, plot_samples_opt.postfixes, plot_samples_opt.legends, plot_samples_opt.colors);

  static const PostfixOptions top_plot_samples_opt=get_pf_opts_({data_selected, signal_top, bkg_selected}, sample);
  sh.AddNewPostfix("StackPlotTopSignal", [] { 
                     if (top_plot_samples_opt.index==1) {
		       if (susy_mass.first != 1200 || susy_mass.second != 200) return (size_t)-1; // T2tt
                     } else if (top_plot_samples_opt.index>=2 && top_plot_samples_opt.index<4) {
		       if (susy_mass.first != 2000 || susy_mass.second != 200) return (size_t)-1; // T1ttt/T5ttcc
		     }
		     return top_plot_samples_opt.index; 
		   }, top_plot_samples_opt.postfixes, top_plot_samples_opt.legends, top_plot_samples_opt.colors);

  static const PostfixOptions V_plot_samples_opt=get_pf_opts_({data_selected, signal_V, bkg_selected}, sample);
  sh.AddNewPostfix("StackPlotVSignal", [] { 
                     if (V_plot_samples_opt.index==1) {
		       if (susy_mass.first != 2000 || susy_mass.second != 200) return (size_t)-1; // T5qqqqVV
                     } else if (V_plot_samples_opt.index==2) {
		       if (susy_mass.first !=  700 || susy_mass.second != 200) return (size_t)-1; // TChiWZ
		     }
		     return V_plot_samples_opt.index; 
		   }, V_plot_samples_opt.postfixes, V_plot_samples_opt.legends, V_plot_samples_opt.colors);

  static const PostfixOptions plot_samples2_opt=get_pf_opts_({data_selected, bkg_selected}, sample);
  sh.AddNewPostfix("StackPlot", [] { 
		     return plot_samples2_opt.index; 
		   }, plot_samples2_opt.postfixes, plot_samples2_opt.legends, plot_samples2_opt.colors);

  static const PostfixOptions data_opt=get_pf_opts_({data_selected}, sample);
  sh.AddNewPostfix("Data", [] { return data_opt.index;  }, data_opt.postfixes, data_opt.legends, data_opt.colors);

  std::vector<std::string> background_dirs;
  for (auto bkg : bkg_selected) for (auto dir : bkg.dirs) background_dirs.push_back(dir);
  std::vector<Sample> background, mc;
  background.push_back({ .postfix="Background", .legend="Background", .color="1", .dirs=background_dirs });
  mc.push_back({ .postfix="MC", .legend="MC", .color="1", .dirs=background_dirs });
  static const PostfixOptions background_opt = get_pf_opts_({background}, sample);
  sh.AddNewPostfix("Background",  [] { return background_opt.index; }, background_opt.postfixes, background_opt.legends, background_opt.colors);
  static const PostfixOptions mc_opt = get_pf_opts_({mc}, sample);
  sh.AddNewPostfix("MC",  [] { return mc_opt.index; }, mc_opt.postfixes, mc_opt.legends, mc_opt.colors);

  static const PostfixOptions bkgs_opt=get_pf_opts_({bkg_selected}, sample);
  sh.AddNewPostfix("Backgrounds", [] { return bkgs_opt.index;  }, bkgs_opt.postfixes, bkgs_opt.legends, bkgs_opt.colors);

  static const PostfixOptions multijet_opt=get_pf_opts_({multijet}, sample);
  sh.AddNewPostfix("Multijet", [] { return multijet_opt.index;  }, multijet_opt.postfixes, multijet_opt.legends, multijet_opt.colors);
  static const PostfixOptions znunu_opt=get_pf_opts_({znunu}, sample);
  sh.AddNewPostfix("ZToNuNu", [] { return znunu_opt.index;  }, znunu_opt.postfixes, znunu_opt.legends, znunu_opt.colors);
  static const PostfixOptions gjets_opt=get_pf_opts_({gjets}, sample);
  sh.AddNewPostfix("GJets", [] { return gjets_opt.index;  }, gjets_opt.postfixes, gjets_opt.legends, gjets_opt.colors);

  static const PostfixOptions gluino_signalscans_opt = get_pf_opts_({signal_gluino}, sample);
  sh.AddNewPostfix("GluinoSignalScans",  [] { return gluino_signalscans_opt.index; }, gluino_signalscans_opt.postfixes, gluino_signalscans_opt.legends, gluino_signalscans_opt.colors);

  static const PostfixOptions stop_signalscans_opt = get_pf_opts_({signal_stop}, sample);
  sh.AddNewPostfix("StopSignalScans",  [] { return stop_signalscans_opt.index; }, stop_signalscans_opt.postfixes, stop_signalscans_opt.legends, stop_signalscans_opt.colors);

  static const PostfixOptions chargino_signalscans_opt = get_pf_opts_({signal_chargino}, sample);
  sh.AddNewPostfix("CharginoSignalScans",  [] { return chargino_signalscans_opt.index; }, chargino_signalscans_opt.postfixes, chargino_signalscans_opt.legends, chargino_signalscans_opt.colors);

  static const PostfixOptions Bkg_T2tt_opt  =get_pf_opts_({background, T2tt},   sample);
  static const PostfixOptions Bkg_T1tttt_opt=get_pf_opts_({background, T1tttt}, sample);
  static const PostfixOptions Bkg_T5ttcc_opt=get_pf_opts_({background, T5ttcc}, sample);
  static const PostfixOptions Bkg_T5qqqqVV_opt=get_pf_opts_({background, T5qqqqVV}, sample);
  static const PostfixOptions Bkg_TChiWZ_opt=get_pf_opts_({background, TChiWZ}, sample);
  //static const PostfixOptions Bkg_T5tttt_opt=get_pf_opts_({background, T5tttt}, sample);
  //static const PostfixOptions Bkg_T1ttbb_opt=get_pf_opts_({background, T1ttbb}, sample);
  //static const PostfixOptions Bkg_T1ttbb_dM5to25_opt=get_pf_opts_({background, T1ttbb_dM5to25}, sample);

  static const PostfixOptions T2tt_opt = get_pf_opts_({T2tt}, sample);
  sh.AddNewPostfix("T2tt",  [] { return T2tt_opt.index; }, T2tt_opt.postfixes, T2tt_opt.legends, T2tt_opt.colors);
  static const PostfixOptions T1tttt_opt = get_pf_opts_({T1tttt}, sample);
  sh.AddNewPostfix("T1tttt",  [] { return T1tttt_opt.index; }, T1tttt_opt.postfixes, T1tttt_opt.legends, T1tttt_opt.colors);
  //static const PostfixOptions T1ttbb_opt = get_pf_opts_({T1ttbb}, sample);
  //sh.AddNewPostfix("T1ttbb",  [] { return T1ttbb_opt.index; }, T1ttbb_opt.postfixes, T1ttbb_opt.legends, T1ttbb_opt.colors);
  //static const PostfixOptions T1ttbb_opt = get_pf_opts_({T1ttbb_dM5to25}, sample);
  //sh.AddNewPostfix("T1ttbb_dM5to25",  [] { return T1ttbb_dM5to25_opt.index; }, T1ttbb_dM5to25_opt.postfixes, T1ttbb_dM5to25_opt.legends, T1ttbb_dM5to25_opt.colors);
  static const PostfixOptions T5ttcc_opt = get_pf_opts_({T5ttcc}, sample);
  sh.AddNewPostfix("T5ttcc",  [] { return T5ttcc_opt.index; }, T5ttcc_opt.postfixes, T5ttcc_opt.legends, T5ttcc_opt.colors);
  static const PostfixOptions T5qqqqVV_opt = get_pf_opts_({T5qqqqVV}, sample);
  sh.AddNewPostfix("T5qqqqVV",  [] { return T5qqqqVV_opt.index; }, T5qqqqVV_opt.postfixes, T5qqqqVV_opt.legends, T5qqqqVV_opt.colors);
  static const PostfixOptions TChiWZ_opt = get_pf_opts_({TChiWZ}, sample);
  sh.AddNewPostfix("TChiWZ",  [] { return TChiWZ_opt.index; }, TChiWZ_opt.postfixes, TChiWZ_opt.legends, TChiWZ_opt.colors);
  //static const PostfixOptions T5tttt_opt = get_pf_opts_({T5tttt}, sample);
  //sh.AddNewPostfix("T5tttt",  [] { return T5tttt_opt.index; }, T5tttt_opt.postfixes, T5tttt_opt.legends, T5tttt_opt.colors);

  static const PostfixOptions background_signal_opt = get_pf_opts_({background, signal_selected}, sample);
  sh.AddNewPostfix("Background_Signal", [] { 
		     if (background_signal_opt.index==1) {
		       if (susy_mass.first!=2000 || susy_mass.second != 200) return (size_t)-1;
		     }
		     return background_signal_opt.index;
		   }, background_signal_opt.postfixes, background_signal_opt.legends, "633,601");

  static const PostfixOptions signals_opt = get_pf_opts_({signal_all}, sample);
  sh.AddNewPostfix("Signals",  [] { 
		     // Select gluino/stop mass to give ~1k events with 40 fb^-1
                     if (signals_opt.index==0) {
		       if (susy_mass.first != 1200 || susy_mass.second != 200) return (size_t)-1; // T2tt
                     } else if (signals_opt.index<4) {
		       if (susy_mass.first != 2000 || susy_mass.second != 200) return (size_t)-1; // T1tttt/T5ttcc/T5qqqqVV
                     } else if (signals_opt.index==4) {
		       if (susy_mass.first !=  700 || susy_mass.second != 200) return (size_t)-1; // TChiWZ
		     }
		     return signals_opt.index; 
		   }, signals_opt.postfixes, signals_opt.legends, signals_opt.colors);

  static const PostfixOptions signals_background_opt = get_pf_opts_({signal_all, background}, sample);
  sh.AddNewPostfix("Signals_Background",  [] { 
                     if (signals_background_opt.index==0) {
		       if (susy_mass.first != 1200 || susy_mass.second != 200) return (size_t)-1; // T2tt
                     } else if (signals_background_opt.index<4) {
		       if (susy_mass.first != 2000 || susy_mass.second != 200) return (size_t)-1; // T1ttt/T5ttcc/T5qqqqVV
                     } else if (signals_background_opt.index==4) {
		       if (susy_mass.first !=  700 || susy_mass.second != 200) return (size_t)-1; // TChiWZ
		     }
		     return signals_background_opt.index; 
		   }, signals_background_opt.postfixes, signals_background_opt.legends, signals_background_opt.colors);

  static const PostfixOptions ttbar_signal_opt = get_pf_opts_({ttbar_selected, signal_selected}, sample);
  sh.AddNewPostfix("TT_Signal",  [] { 
		     if (ttbar_signal_opt.index==0) return (size_t)0;
		     else if (ttbar_signal_opt.index==1) {
		       if (susy_mass.first == 2000 && susy_mass.second == 200) return (size_t)1;
		     }
		     return (size_t)-1;
		   }, "TTbar;T5ttcc_Mlsp200_Mglu2000", "t#bar{t};T5ttcc m_{#tilde{g}}=2.0TeV", "1,633");
  sh.AddNewPostfix("TT_SignalPoints",  [] { 
		     if (ttbar_signal_opt.index==0) return (size_t)0;
		     else if (ttbar_signal_opt.index==1) {
		       if (susy_mass.second == 200) {
			 if      (susy_mass.first==1400) return (size_t)1;
			 else if (susy_mass.first==1600) return (size_t)2;
			 else if (susy_mass.first==1800) return (size_t)3;
			 else if (susy_mass.first==2000) return (size_t)4;
			 else if (susy_mass.first==2200) return (size_t)5;
			 else if (susy_mass.first==2400) return (size_t)6;
		       }
		     }
		     return (size_t)-1;
		   }, "TTbar;T5ttcc_Mlsp300_Mglu[1400to2400++200]", "t#bar{t};T5ttcc m_{#tilde{g}}=[1.4to2.4++0.2]TeV m_{#tilde{#chi}^{0}_{1}}=200GeV", "1,"+col6_rainbow_dark);


  if (debug) std::cout<<"Analysis::define_histo_options: ok6"<<std::endl;
  static const PostfixOptions mgluinopoints_opt = get_pf_opts_({signal_gluino}, sample);
  sh.AddNewPostfix("MGluinoPoints",  [] { 
		     if (mgluinopoints_opt.index==(size_t)-1) return (size_t)-1;
		     else {
		       if      (susy_mass.first==1400) return (size_t)0;
		       else if (susy_mass.first==1600) return (size_t)1;
		       else if (susy_mass.first==1800) return (size_t)2;
		       else if (susy_mass.first==2000) return (size_t)3;
		       else if (susy_mass.first==2200) return (size_t)4;
		       else if (susy_mass.first==2400) return (size_t)5;
		       else return (size_t)-1;
		     }
		   }, "Mglu[1400to2400++200]", "m_{#tilde{g}}=[1.4to2.4++0.2]TeV", col6_rainbow_dark);
  static const PostfixOptions mstoppoints_opt = get_pf_opts_({signal_stop}, sample);
  sh.AddNewPostfix("MStopPoints",  [] { 
		     if (mstoppoints_opt.index==(size_t)-1) return (size_t)-1;
		     else {
		       if      (susy_mass.first== 400) return (size_t)0;
		       else if (susy_mass.first== 600) return (size_t)1;
		       else if (susy_mass.first== 800) return (size_t)2;
		       else if (susy_mass.first==1000) return (size_t)3;
		       else if (susy_mass.first==1200) return (size_t)4;
		       else if (susy_mass.first==1400) return (size_t)5;
		       else return (size_t)-1;
		     }
		   }, "Mstop[400to1400++200]", "m_{#tilde{t}}=[0.4to1.4++0.2]TeV", col6_rainbow_dark);
  static const PostfixOptions mcharginopoints_opt = get_pf_opts_({signal_chargino}, sample);
  sh.AddNewPostfix("MCharginoPoints",  [] { 
		     if (mcharginopoints_opt.index==(size_t)-1) return (size_t)-1;
		     else {
		       if      (susy_mass.first== 400) return (size_t)0;
		       else if (susy_mass.first== 500) return (size_t)1;
		       else if (susy_mass.first== 600) return (size_t)2;
		       else if (susy_mass.first== 700) return (size_t)3;
		       else if (susy_mass.first== 800) return (size_t)4;
		       else if (susy_mass.first== 900) return (size_t)5;
		       else return (size_t)-1;
		     }
		   }, "Mchi[400to900++100]", "m_{#tilde{#chi}^{#pm}_{1}}=[400to900++100]GeV", col6_rainbow_dark);
  static const PostfixOptions mlsppoints_opt = get_pf_opts_({signal_fastsim}, sample);
  sh.AddNewPostfix("MLSPPoints",  [] { 
		     if (mlsppoints_opt.index==(size_t)-1) return (size_t)-1;
		     else {
		       if      (susy_mass.second==   0) return (size_t)0;
		       else if (susy_mass.second== 200) return (size_t)1;
		       else if (susy_mass.second== 400) return (size_t)2;
		       else if (susy_mass.second== 600) return (size_t)3;
		       else if (susy_mass.second== 800) return (size_t)4;
		       else if (susy_mass.second==1000) return (size_t)5;
		       else return (size_t)-1;
		     }
		   }, "Mlsp[0to1000++200]", "m_{#tilde{#chi}^{0}_{1}}=[0to1000++200]GeV", col6_rainbow_dark);

  if (debug) std::cout<<"Analysis::define_histo_options: ok7"<<std::endl;
  static const PostfixOptions data_mc_opt = get_pf_opts_({data_selected, mc}, sample);
  sh.AddNewPostfix("Data_MC",  [] { return data_mc_opt.index; }, data_mc_opt.postfixes, data_mc_opt.legends, "1,633");

  static const PostfixOptions single_lep_opt = get_pf_opts_({single_ele, single_mu}, sample);
  sh.AddNewPostfix("SingleEle_SingleMu", [] { return single_lep_opt.index; }, single_lep_opt.postfixes, single_lep_opt.legends, "1,633");
  
  static const PostfixOptions triggers_opt = get_pf_opts_({single_ele, single_pho, single_mu, mc}, sample);
  sh.AddNewPostfix("HadronicMeasurements", [&d]() {
                     size_t i = -1;
                     if (triggers_opt.index==0) { // SingleElectron
		       if (!(d.HLT_Ele27_WPTight_Gsf==1||d.HLT_Ele32_WPTight_Gsf==1||d.HLT_Ele35_WPTight_Gsf==1)) return (size_t)-1;
		       if (!(nEleTight==1&&nMuVeto==0)) return (size_t)-1;
		       if (nJet<3) return (size_t)-1;
		       if (R2<0.08) return (size_t)-1;
		       if (MR<800) return (size_t)-1;
                       i = (tight_leptons[0].Pt()>=50);
		     } else if (triggers_opt.index==1) { // SinglePhoton
                       bool OR_HLT_Photon = 
                         d.HLT_Photon25==1 ||
                         d.HLT_Photon33==1 ||
                         d.HLT_Photon50==1 ||
                         d.HLT_Photon75==1 ||
                         d.HLT_Photon90==1 ||
                         d.HLT_Photon120==1 ||
                         d.HLT_Photon150==1 ||
                         d.HLT_Photon175==1 ||
                         d.HLT_Photon200==1 ||
                         d.HLT_Photon300_NoHE==1;
		       if (!(OR_HLT_Photon)) return (size_t)-1;
		       if (!(nPhotonSelect==1&&nLepVeto==0&&nTauVeto==0)) return (size_t)-1;
		       if (nJetNoPho<3) return (size_t)-1;
		       if (R2_pho<0.08) return (size_t)-1;
		       if (MR_pho<800) return (size_t)-1;
                       i = 2;
                     } else if (triggers_opt.index==2) { // SingleMuon
		       if (!(d.HLT_IsoMu20==1|d.HLT_IsoMu24==1||d.HLT_IsoMu27==1)) return (size_t)-1;
		       if (!(nMuTight==1&&nEleVeto==0)) return (size_t)-1;
		       if (nJet<3) return (size_t)-1;
		       if (R2<0.08) return (size_t)-1;
		       if (MR<800) return (size_t)-1;
                       i = tight_leptons[0].Pt()>=50+3;
		     } else if (triggers_opt.index==3) { // Simulation
		       if (nJet<3) return (size_t)-1;
		       if (R2<0.08) return (size_t)-1;
		       if (MR<800) return (size_t)-1;
                       i = 5;
		     }
                     return i;
		   }, "SingleElectron_LowPt;SingleElectron_HighPt;SinglePhoton;SingleMuon_LowPt;SingleMuon_HighPt;MC", 
                   "e low;e high;#gamma;#mu low;#mu high;MC", "617,632,402,433,601,1"); // purple, red, yellow cyan, blue, black
  // Same without R2 cut
  sh.AddNewPostfix("HadronicMeasurementsNoR2", [&d]() {
                     size_t i = -1;
                     if (triggers_opt.index==0) { // SingleElectron
		       if (!(d.HLT_Ele27_WPTight_Gsf==1||d.HLT_Ele32_WPTight_Gsf==1||d.HLT_Ele35_WPTight_Gsf==1)) return (size_t)-1;
		       if (!(nEleTight==1&&nMuVeto==0)) return (size_t)-1;
		       if (nJet<3) return (size_t)-1;
		       if (MR<800) return (size_t)-1;
                       i = (tight_leptons[0].Pt()>=50);
		     } else if (triggers_opt.index==1) { // SinglePhoton
                       bool OR_HLT_Photon = 
                         d.HLT_Photon25==1 ||
                         d.HLT_Photon33==1 ||
                         d.HLT_Photon50==1 ||
                         d.HLT_Photon75==1 ||
                         d.HLT_Photon90==1 ||
                         d.HLT_Photon120==1 ||
                         d.HLT_Photon150==1 ||
                         d.HLT_Photon175==1 ||
                         d.HLT_Photon200==1 ||
                         d.HLT_Photon300_NoHE==1;
		       if (!(OR_HLT_Photon)) return (size_t)-1;
		       if (!(nPhotonSelect==1&&nLepVeto==0&&nTauVeto==0)) return (size_t)-1;
		       if (nJetNoPho<3) return (size_t)-1;
		       if (MR_pho<800) return (size_t)-1;
                       i = 2;
                     } else if (triggers_opt.index==2) { // SingleMuon
		       if (!(d.HLT_IsoMu20==1|d.HLT_IsoMu24==1||d.HLT_IsoMu27==1)) return (size_t)-1;
		       if (!(nMuTight==1&&nEleVeto==0)) return (size_t)-1;
		       if (nJet<3) return (size_t)-1;
		       if (MR<800) return (size_t)-1;
                       i = tight_leptons[0].Pt()>=50+3;
		     } else if (triggers_opt.index==3) { // Simulation
		       if (nJet<3) return (size_t)-1;
		       if (MR<800) return (size_t)-1;
                       i = 5;
		     }
                     return i;
		   }, "SingleElectron_LowPt;SingleElectron_HighPt;SinglePhoton;SingleMuon_LowPt;SingleMuon_HighPt;MC", 
                   "e low;e high;#gamma;#mu low;#mu high;MC", "617,632,402,433,601,1"); // purple, red, yellow cyan, blue, black
  
  static const PostfixOptions triggers3_opt = get_pf_opts_({jetht, met, mc}, sample);
  sh.AddNewPostfix("LeptonicMeasurements", [&d]()
		   {
                     if (!(nLepTight==1)) return (size_t)-1;
		     if (triggers3_opt.index==0) { // JetHT
                       bool OR_HLT_PFHT = 
                         d.HLT_PFHT180 ||
                         d.HLT_PFHT250 ||
                         d.HLT_PFHT350 ||
                         d.HLT_PFHT370 ||
                         d.HLT_PFHT430 ||
                         d.HLT_PFHT510 ||
                         d.HLT_PFHT590 ||
                         d.HLT_PFHT680 ||
                         d.HLT_PFHT780 ||
                         d.HLT_PFHT890 ||
                         d.HLT_PFHT1050;
		       if (!OR_HLT_PFHT) return (size_t)-1;
		       if (nJet<3) return (size_t)-1;
		       if (R2<0.08) return (size_t)-1;
		       if (MR<700) return (size_t)-1;
		     } else if (triggers3_opt.index==1) { // MET
		       if (!(d.HLT_PFMET120_PFMHT120_IDTight==1)) return (size_t)-1;
		       if (nJet<3) return (size_t)-1;
		       if (R2<0.08) return (size_t)-1;
		       if (MR<700) return (size_t)-1;
		     } else if (triggers3_opt.index==2) { // Simulation
		       if (nJet<3) return (size_t)-1;
		       if (R2<0.08) return (size_t)-1;
		       if (MR<700) return (size_t)-1;
		     } else {
		       return (size_t)-1;
		     }
		     return (size_t)triggers3_opt.index; 
		   }, "JetHT_1Lep;MET_1Lep;MC_1Lep", "HT;MET;Simulation", "807,417,1"); // orange, green, black

  static const PostfixOptions trigger_opt = get_pf_opts_({single_ele, met}, sample);
  sh.AddNewPostfix("EleMETComb", [&d]()
		   {
		     if (trigger_opt.index==0) { // SingleElectron
		       if ((d.HLT_Ele32_WPTight_Gsf==1||d.HLT_Ele35_WPTight_Gsf==1)&&nEleTight==1&&nMuVeto==0&&nTauVeto==0) return (size_t)0;
		     } else if (trigger_opt.index==1) { // MET
		       if (d.HLT_PFMET120_PFMHT120_IDTight==1&&nLepVeto==0&&nTauVeto==0) return (size_t)0;
		     }
		     return (size_t)-1; 
		   }, "SingleEle_MET", "SingleEle + MET", "1");

  static const PostfixOptions data_photruth_opt = get_pf_opts_({data_selected, mc}, sample);
  sh.AddNewPostfix("Data_PhotonTruth",  [] { 
		     if (data_photruth_opt.index==0) return (size_t)0;
		     else if (data_photruth_opt.index==1) {
		       //if (d.pho.isPromptDirect[i_Photon]==1) return (size_t)1;
		       //else if (d.pho.isPromptFrag[i_Photon]==1) return (size_t)2;
		       //else if (d.pho.isFake[i_Photon]==1) return (size_t)3;
		     }
		     return (size_t)-1; }, "Data;PromptDirect;PromptFrag;Fake", "Data;Prompt;Fragm.;Fakes", "1,418,601,633");
  sh.AddNewPostfix("Data_Photon1Truth",  [] { 
		     if (nPhotonSelect!=1) return (size_t)-1;
		     if (data_photruth_opt.index==0) return (size_t)0;
		     else if (data_photruth_opt.index==1) {
		       //if (d.pho.isPromptDirect[iPhotonSelect[0]]==1) return (size_t)1;
		       //else if (d.pho.isPromptFrag[iPhotonSelect[0]]==1) return (size_t)2;
		       //else if (d.pho.isFake[iPhotonSelect[0]]==1) return (size_t)3;
		     }
		     return (size_t)-1; }, "Data;PromptDirect;PromptFrag;Fake", "Data;Prompt;Fragm.;Fakes", "1,418,601,633");

  // Systematics Postfixes
  sh.AddNewPostfix("Syst", [&syst_index] { return syst_index; }, std::string(";syst[1to")+std::to_string(syst_nSyst)+"]", std::string(";systematics [1to")+std::to_string(syst_nSyst)+"]", "1-999");
  if (syst_nSyst>998) error("Error: Too large number of systematics, define more colors!");
  if (debug) std::cout<<"Analysis::define_histo_options: sample postfixes ok"<<std::endl;

  // Cut names
  std::map<std::string, std::string> legname;
  legname["3Jet"]        = "Njet#geq3";
  legname["MR"]          = "MR";
  legname["R2"]          = "R^{2}";
  legname["HLT"]         = "HLT";
  legname["0Ele"]        = "ele veto";
  legname["0Mu"]         = "muon veto";
  legname["0Tau"]        = "tau veto";
  legname["1b"]          = "Nb#geq1";
  legname["1W"]          = "NW#geq1";
  legname["dPhi"]        = "#Delta#phi";
  legname["InvdPhi"]     = "inv. #Delta#phi";
  legname["0b"]          = "b-tag veto";
  legname["1aW"]         = "NW(anti-tag)#geq1";
  legname["1aTop"]       = "NTop(anti-tag)#geq1";
//legname["InvdPhi0p3"]  = "#Delta#phi<0.3";
  legname["InvdPhi"]     = "inv. #Delta#phi";
  legname["1Lep"]        = "Nlep=1";
  legname["MT"]          = "m_{T}";
  legname["1mW"]         = "NW(mass-tag)#geq1";
  legname["1mTop"]       = "NTop(mass-tag)#geq1";
  legname["1MTop"]       = "NTop(mass-tag)#geq1";
  legname["R2ll"]        = "R^{2}";
  legname["2Lep"]        = "Nlep=2";
  legname["OppCharge"]   = "#sumq_{lep}=0";
  legname["dPhi"]        = "#Delta#phi";
  legname["Mll"]         = "|m_{ll} - m_{Z}| < 10 GeV";
  legname["1Top"]        = "Ntop#geq1";
  legname["1Pho"]        = "N#gamma=1";
  std::map<char, std::string> regionname;
  regionname['P'] = "Baseline selection";
  regionname['R'] = "Baseline, 1#gamma, 0lepton";
  regionname['S'] = "Signal region";
  regionname['s'] = "Signal-like validation region";
  regionname['Q'] = "Multijet control region";
  regionname['q'] = "Multijet validation region";
  regionname['T'] = "t#bar{t} control region";
  regionname['W'] = "W+jets control region";
  //regionname['w'] = "Razor Incl. W enriched region";
  regionname['L'] = "1 lepton invisible region";
  regionname['Z'] = "Z(ll) control region";
  regionname['G'] = "#gamma+jets control region";
  regionname['H'] = "#gamma+jets control region, no W/top";
  regionname['z'] = "Z(ll) control region (full tag)";
  regionname['F'] = "Fake tag region";
  regionname['B'] = "Fake tag region + 1b";
  //regionname['H'] = "HT#geq1TeV + 1b";
  regionname['0'] = "0 lepton SR";
  regionname['N'] = "Non-iso. lepton SR";
  regionname['a'] = "had. 1top SR";
  regionname['b'] = "had. 2top SR";
  regionname['c'] = "had. b+W, 4-5 jet SR";
  regionname['d'] = "had. b+W, 6+ jet SR";
  regionname['e'] = "had. 0b, 1V, 3-4jet SR";
  regionname['f'] = "had. 0b, 1V, 5+ jet SR";
  regionname['g'] = "had. 0b, 2V, 2-4 jet SR";
  regionname['h'] = "had. 0b, 2V, 5+ jet SR";
  regionname['i'] = "1 iso. lep, 1hadtop SR";
  regionname['j'] = "1 iso. lep, 1V+b SR";
  regionname['k'] = "1 iso. lep, 1V+0b SR";
  regionname['l'] = "1leptop, 0hadtop SR";
  regionname['m'] = "1leptop, 1hadtop SR";
  regionname['n'] = "1lepjet, 0b, 0V, 2-4 jet SR";
  regionname['o'] = "1lepjet, 0b, 0V, 5+ jet  SR";
  regionname['p'] = "1lepjet, 0b, 1V, 2-4 jet SR";
  regionname['q'] = "1lepjet, 0b, 1V, 5+ jet  SR";

  // lep jet search copy paste error
  // tell benchmar points

  // Cut Postfixes
  sh.AddNewPostfix("BaselineCuts", [] { return 0; }, "BaselineCuts", "Baseline cuts", "1");
  all_cuts.push_back("BaselineCuts");
  for (const auto& region : analysis_cuts) {
    std::string cutflow_str = "";
    sh.AddNewPostfix(std::string(1,region.first), [this,region] { return apply_all_cuts(region.first) ? 0 : (size_t)-1; },
		     std::string(1,region.first), regionname[region.first], "1");
    for (size_t i=0, n=region.second.size(); i<n; ++i) {

      // Cuts in order 1-N: "PassNCuts[search region]"
      sh.AddNewPostfix(std::string(1,region.first)+"_"+std::to_string(i+1)+"Cuts", [this,i,region] { return apply_ncut(region.first, i) ? 0 : (size_t)-1; },
		       std::string(1,region.first)+"_"+std::to_string(i+1)+"Cuts", std::string(1,region.first)+" region, first "+std::to_string(i+1)+" cuts", "1");
      all_cuts.push_back(std::string(1,region.first)+"_"+std::to_string(i+1)+"Cuts");
      cutflow_str += region.second[i].name+std::string(1,region.first)+";";
      // N-1 Cuts: "[search region]_Excl[cut]"
      sh.AddNewPostfix(std::string(1,region.first)+"_Excl"+region.second[i].name, [i,region] { 
			 unsigned int mask = (1<<region.second.size())-1 - (1<<i); 
			 return ((cutbits[region.first] & mask) == mask) ? 0 : (size_t)-1; }, 
		       //std::string(1,region.first)+"_Excl"+region.second[i].name, regionname[region.first]+", no "+legname[region.second[i].name]+" cut", "1");
		       std::string(1,region.first)+"_Excl"+region.second[i].name, regionname[region.first], "1");
      // N-2 Cuts: "[search region]_Excl[cut1][cut2]"
      for (size_t j=i+1, n=region.second.size(); j<n; ++j)
	sh.AddNewPostfix(std::string(1,region.first)+"_Excl"+region.second[i].name+region.second[j].name, [i,j,region] { 
			   unsigned int mask = (1<<region.second.size())-1 - (1<<i) - (1<<j); 
			   return ((cutbits[region.first] & mask) == mask) ? 0 : (size_t)-1; }, 
		         std::string(1,region.first)+"_Excl"+region.second[i].name+region.second[j].name, regionname[region.first]+", no "+legname[region.second[i].name]+", "+legname[region.second[j].name]+" cut", "1");
      // N-3 Cuts: "[search region]_Excl[cut1][cut2][cut3]"
      for (size_t j=i+1, n=region.second.size(); j<n; ++j)
	for (size_t k=j+1; k<n; ++k)
	  sh.AddNewPostfix(std::string(1,region.first)+"_Excl"+region.second[i].name+region.second[j].name+region.second[k].name, [i,j,k,region] { 
			     unsigned int mask = (1<<region.second.size())-1 - (1<<i) - (1<<j) - (1<<k); 
			     return ((cutbits[region.first] & mask) == mask) ? 0 : (size_t)-1; }, 
			   std::string(1,region.first)+"_Excl"+region.second[i].name+region.second[j].name+region.second[k].name, regionname[region.first]+", no "+legname[region.second[i].name]+", "+legname[region.second[j].name]+", "+legname[region.second[k].name]+" cut", "1");
    }
    // Stackable Cut Histos: "CutFlow"
    sh.AddNewPostfix("CutFlow"+std::string(1,region.first), [region] { for (size_t i=0, n=region.second.size(); i<n; ++i) if (!region.second[i].func()) return i; return region.second.size(); }, 
		     cutflow_str+"PassAll"+std::string(1,region.first), cutflow_str+regionname[region.first], col10+col10);
  }
  sh.AddNewPostfix("Baseline",       [this] { return apply_cut('P', 0) ? 0 : (size_t)-1; },         "Baseline",     "Baseline selection",               "1");
  sh.AddNewPostfix("BaselineNoR2",   [this] { return apply_cut('P', 0) ? 0 : (size_t)-1; },         "BaselineNoR2", "Baseline selection, No R^{2} cut", "1");
  
  // Signal region with 1 veto lepton
  size_t iEle=0, iMu=0, iTau=0, iDPhi=0;
  for (size_t i=0; i<analysis_cuts['S'].size(); ++i) {
    if (analysis_cuts['S'][i].name=="0Ele")  iEle=i;
    if (analysis_cuts['S'][i].name=="0Mu")   iMu=i;
    if (analysis_cuts['S'][i].name=="0Tau")  iTau=i;
    if (analysis_cuts['S'][i].name=="dPhi")  iDPhi=i;
  }
  sh.AddNewPostfix("S_1VetoLep", [this,iEle,iMu,iTau,iDPhi] {
		     size_t ele = (1<<analysis_cuts['S'].size())-1 - (1<<iEle) - (1<<iDPhi); // Ele allowed 
		     if ((cutbits['S'] & ele)==ele && nEleVeto==1 && MT_allvetolep<100) return (size_t)0;
		     size_t mu = (1<<analysis_cuts['S'].size())-1 - (1<<iMu) - (1<<iDPhi);  // Mu allowed 
		     if ((cutbits['S'] & mu)==mu   && nMuVeto==1  && MT_allvetolep<100) return (size_t)0;
		     size_t tau = (1<<analysis_cuts['S'].size())-1 - (1<<iTau) - (1<<iDPhi); // Tau allowed 
		     if ((cutbits['S'] & tau)==tau && nTauVeto==1 && MT_allvetolep<100) return (size_t)0;
		     return (size_t)-1;
		   }, "S_1VetoLep", "S +1 Lepton, MT<100, No #Delta#phi", "1");  
  sh.AddNewPostfix("LeptonFlavour", [this,iEle,iMu,iTau,iDPhi] {
		     size_t ele = (1<<analysis_cuts['S'].size())-1 - (1<<iEle) - (1<<iDPhi); // Ele allowed 
		     if ((cutbits['S'] & ele)==ele && nEleVeto==1 && MT_allvetolep<100) return (size_t)0;
		     size_t mu = (1<<analysis_cuts['S'].size())-1 - (1<<iMu) - (1<<iDPhi);  // Mu allowed 
		     if ((cutbits['S'] & mu)==mu   && nMuVeto==1  && MT_allvetolep<100) return (size_t)1;
		     size_t tau = (1<<analysis_cuts['S'].size())-1 - (1<<iTau) - (1<<iDPhi); // Tau allowed 
		     if ((cutbits['S'] & tau)==tau && nTauVeto==1 && MT_allvetolep<100) return (size_t)2;
		     return (size_t)-1;
		   }, "S_1VetoEle;S_1VetoMu;S_1VetoTau", "Electron;Muon;Tau", "417,601,633");
  sh.AddNewPostfix("LostLeptonFlavour", [&d] {
		     int id = std::abs(d.GenPart[i_GenPart].pdgId);
		     if (id==11) return (size_t)0;
		     if (id==13) return (size_t)1;
		     if (id==15) return (size_t)2;
		     return (size_t)-1;
		   }, "GenEle;GenMu;GenTau", "Electron;Muon;Tau", "417,601,633");
  sh.AddNewPostfix("GenLeptonFlavour", [&d] {
		     int id = std::abs(d.GenPart[i_GenPart].pdgId);
		     if (id==11) return (size_t)0;
		     if (id==13) return (size_t)1;
		     if (id==15) return (size_t)2;
		     return (size_t)-1;
		   }, "GenEle;GenMu;GenTau", "Electron;Muon;Tau", "417,601,633");
  sh.AddNewPostfix("GenTopLeptonFlavour", [&d] {
                     size_t iLep = iGenLepTopMatchedGenLep[i_GenPart];
                     if (iLep==(size_t)-1) return (size_t)-1;
		     int id = std::abs(d.GenPart[iLep].pdgId);
		     if (id==11) return (size_t)0;
		     if (id==13) return (size_t)1;
		     if (id==15) return (size_t)2;
		     return (size_t)-1;
		   }, "GenEle;GenMu;GenTau", "Electron;Muon;Tau", "417,601,633");
  sh.AddNewPostfix("GenWLeptonFlavour", [&d] {
                     size_t iLep = iGenLepWMatchedGenLep[i_GenPart];
                     if (iLep==(size_t)-1) return (size_t)-1;
		     int id = std::abs(d.GenPart[iLep].pdgId);
		     if (id==11) return (size_t)0;
		     if (id==13) return (size_t)1;
		     if (id==15) return (size_t)2;
		     return (size_t)-1;
		   }, "GenEle;GenMu;GenTau", "Electron;Muon;Tau", "417,601,633");
  sh.AddNewPostfix("GenLepMother", [] {
		     if (!passGenLepton[i_GenPart]) return (size_t)-1;
                     if (passGenLeptonFromTop[i_GenPart]) return (size_t)2;
                     else if (passGenLeptonFromW[i_GenPart]) return (size_t)1;
                     else return (size_t)0;
		   }, "Other;FromW;FromTop", "Other;from W decay;from top decay", "633,417");
  
  // Individual Cuts implemented as Postfixes
  // Triggers
  sh.AddNewPostfix("JetHTMET",  [this] { 
		     if (sample.find("SingleElectron")!=std::string::npos) return (size_t)-1;
		     else if (sample.find("SingleMuon")!=std::string::npos) return (size_t)-1;
		     else if (sample.find("SinglePhoton")!=std::string::npos) return (size_t)-1;
		     else if (sample.find("MET")!=std::string::npos) return (size_t)0;
		     else if (sample.find("JetHT")!=std::string::npos) return (size_t)0;
		     else if (sample.find("HTMHT")!=std::string::npos) return (size_t)-1;
		     else if (sample.find("EGamma")!=std::string::npos) return (size_t)-1;
		     else return (size_t)0;
		   }, "JetHTMET", "", "1");
  sh.AddNewPostfix("JetHT",      [this] { 
		     if (sample.find("SingleElectron")!=std::string::npos) return (size_t)-1;
		     else if (sample.find("SingleMuon")!=std::string::npos) return (size_t)-1;
		     else if (sample.find("SinglePhoton")!=std::string::npos) return (size_t)-1;
		     else if (sample.find("MET")!=std::string::npos) return (size_t)-1;
		     else if (sample.find("JetHT")!=std::string::npos) return (size_t)0;
		     else if (sample.find("HTMHT")!=std::string::npos) return (size_t)-1;
		     else if (sample.find("EGamma")!=std::string::npos) return (size_t)-1;
		     else return (size_t)0;
		   }, "JetHT", "", "1");
  sh.AddNewPostfix("Blind",      [this] { 
		     if (sample.find("SingleElectron")!=std::string::npos) return (size_t)-1;
		     else if (sample.find("SingleMuon")!=std::string::npos) return (size_t)-1;
		     else if (sample.find("SinglePhoton")!=std::string::npos) return (size_t)-1;
		     else if (sample.find("MET")!=std::string::npos) return (size_t)-1;
		     else if (sample.find("JetHT")!=std::string::npos) return (size_t)-1;
		     else if (sample.find("HTMHT")!=std::string::npos) return (size_t)-1;
		     else if (sample.find("EGamma")!=std::string::npos) return (size_t)-1;
		     else return (size_t)0;
		   }, "BlindData", "", "1");
		   //}, "BlindData", "", "1");

  // Lepton Postfixes
  // Photon Postfixes
  sh.AddNewPostfix("SIEIE",          [&d] {  return d.Photon[i_Photon].sieie < (d.Photon[i_Photon].isScEtaEB ? 0.01022 : 0.03001); }, "FailSIEIE;PassSIEIE", "Fail #sigma_{i#eta i#eta};Pass #sigma_{i#eta i#eta}", "633,418");
  sh.AddNewPostfix("CHIso",          [&d] {  return ChargedHadronIsoEACorr[i_Photon] < (d.Photon[i_Photon].isScEtaEB ? 0.441 : 0.442); }, "FailCHIso;PassCHIso", "Fail ch. iso.;Pass ch. iso.", "633,418");
  sh.AddNewPostfix("EB",             [&d] {  return (size_t)(d.Photon[i_Photon].isScEtaEB ? 0 : -1); }, "Barrel", "Barrel", "1");
  sh.AddNewPostfix("EE",             [&d] {  return (size_t)(d.Photon[i_Photon].isScEtaEE ? 0 : -1); }, "Endcap", "Endcap", "1");
  sh.AddNewPostfix("EB_EE",          [&d] {  return d.Photon[i_Photon].isScEtaEE; }, "Barrel;Endcap", "Barrel;Endcap", "601,418");
  //sh.AddNewPostfix("Fake",           [&d] {  return (size_t)(d.Photon.isFake[i_Photon]==1 ? 0 : -1); }, "Fake", "Fake", "1");
  //sh.AddNewPostfix("Prompt",         [&d] {  return (size_t)(d.Photon.isPromptDirect[i_Photon]==1||d.Photon.isPromptFrag[i_Photon]==1 ? 0 : -1); }, "Prompt", "Prompt", "1");

  // AK4 Jet Postfixes
  sh.AddNewPostfix("Jets",    [] {  size_t i=itJet[i_Jet];        return (i<4)?i:(size_t)-1; }, "Jet[1to5]",  "1st Jet;2nd Jet;3rd Jet;[4to5]th Jet", col5_red_to_green);
  sh.AddNewPostfix("BTags",   [] {  size_t i=itMediumBTag[i_Jet]; return (i<4)?i:(size_t)-1; }, "BTag[1to5]", "1st b;2nd b;3rd b;[4to5]th b",         col5_red_to_green);
  sh.AddNewPostfix("JetPhotonDR0.05", [] {  return AK4_photonDR[i_Jet]<0.05 ? (size_t)0 : (size_t)-1; }, "PhotonDR0p05",  "DR_{#gamma}<0.05", "1");
  sh.AddNewPostfix("JetPhotonDR0.4",  [] {  return AK4_photonDR[i_Jet]<0.4  ? (size_t)0 : (size_t)-1; }, "PhotonDR0p4",   "DR_{#gamma}<0.4",  "1");
  sh.AddNewPostfix("JetEleDR0.05",    [] {  return AK4_eleDR[i_Jet]<0.05 ? (size_t)0 : (size_t)-1; },    "EleDR0p05",     "DR_{ele}<0.05", "1");
  sh.AddNewPostfix("JetEleDR0.4",     [] {  return AK4_eleDR[i_Jet]<0.4  ? (size_t)0 : (size_t)-1; },    "EleDR0p4",      "DR_{ele}<0.4",  "1");
  sh.AddNewPostfix("JetMuonDR0.05",   [] {  return AK4_muonDR[i_Jet]<0.05 ? (size_t)0 : (size_t)-1; },   "MuonDR0p05",    "DR_{muon}<0.05", "1");
  sh.AddNewPostfix("JetMuonDR0.4",    [] {  return AK4_muonDR[i_Jet]<0.4  ? (size_t)0 : (size_t)-1; },   "MuonDR0p4",     "DR_{muon}<0.4",  "1");

  // AK8 Jet Postfixes
  sh.AddNewPostfix("JetsAK8",  [] {  size_t i=itJetAK8[i_FatJet];    return (i<4)?i:(size_t)-1; }, "Jet[1to4]",     "1st Jet;2nd Jet;3rd Jet;4th Jet",                     col4_red_to_cyan);
  sh.AddNewPostfix("JetAK8PhotonDR0.05", [] {  return AK8_photonDR[i_FatJet]<0.05 ? (size_t)0 : (size_t)-1; }, "PhotonDR0p05",  "DR_{#gamma}<0.05", "1");
  sh.AddNewPostfix("JetAK8PhotonDR0.8",  [] {  return AK8_photonDR[i_FatJet]<0.8  ? (size_t)0 : (size_t)-1; }, "PhotonDR0p8",   "DR_{#gamma}<0.8",  "1");
  sh.AddNewPostfix("JetAK8EleDR0.05",    [] {  return AK8_eleDR[i_FatJet]<0.05 ? (size_t)0 : (size_t)-1; },    "EleDR0p05",  "DR_{ele}<0.05", "1");
  sh.AddNewPostfix("JetAK8EleDR0.8",     [] {  return AK8_eleDR[i_FatJet]<0.8  ? (size_t)0 : (size_t)-1; },    "EleDR0p8",   "DR_{ele}<0.8",  "1");
  sh.AddNewPostfix("JetAK8MuonDR0.05",   [] {  return AK8_muonDR[i_FatJet]<0.05 ? (size_t)0 : (size_t)-1; },   "MuonDR0p05",  "DR_{muon}<0.05", "1");
  sh.AddNewPostfix("JetAK8MuonDR0.8",    [] {  return AK8_muonDR[i_FatJet]<0.8  ? (size_t)0 : (size_t)-1; },   "MuonDR0p8",   "DR_{muon}<0.8",  "1");
  sh.AddNewPostfix("mWs",      [] {  size_t i=itWMassTag[i_FatJet];  return (i<4)?i:(size_t)-1; }, "mW[1to4]", "1st W-masstag;2nd W-masstag;3rd W-masstag;4th W-masstag", col4_red_to_cyan);
  sh.AddNewPostfix("aWs",      [] {  size_t i=itTightWAntiTag[i_FatJet];   return (i<4)?i:(size_t)-1; }, "aW[1to4]", "1st W-antitag;2nd W-antitag;3rd W-antitag;4th W-antitag", col4_red_to_cyan);
  sh.AddNewPostfix("Ws",       [] {  size_t i=itTightWTag[i_FatJet]; return (i<4)?i:(size_t)-1; }, "W[1to4]",       "1st W;2nd W;3rd W;4th W",                             col4_red_to_cyan);
  sh.AddNewPostfix("Jet1AK8Pt450",  [&d] {  return d.FatJet[iJetAK8[0]].pt>450 ? 0 : (size_t)-1; }, "Jet1AK8_Pt450",  "1st jet p_{T} (AK8) > 450", "1");
  sh.AddNewPostfix("Jet1AK8Pt500",  [&d] {  return d.FatJet[iJetAK8[0]].pt>500 ? 0 : (size_t)-1; }, "Jet1AK8_Pt500",  "1st jet p_{T} (AK8) > 500", "1");
  sh.AddNewPostfix("Jet1AK8Mass65", [] {  return softDropMassW[iJetAK8[0]]>65 ? 0 : (size_t)-1; }, "Jet1AK8_Mass65", "1st jet m_{SD} (AK8) > 65", "1");
  sh.AddNewPostfix("Tau21Tagged",   [] {  return tau21[i_FatJet]<W_TAU21_TIGHT_CUT; }, "Tau21AntiTag;Tau21Tag", "#tau_{2}/#tau_{1} anti-tagged;#tau_{2}/#tau_{1} tagged", "633,418");
  sh.AddNewPostfix("Tau32Tagged",   [] {  return tau32[i_FatJet]<HADTOP_TAU32_CUT;     }, "Tau32AntiTag;Tau32Tag", "#tau_{3}/#tau_{2} anti-tagged;#tau_{3}/#tau_{2} tagged", "633,418");
  sh.AddNewPostfix("LepJetNoIso",          [] {  return passLepJetNoIso[i_FatJet]==1 ? 0 : (size_t)-1;          }, "LepJetNoIso",          "Lep. jet (no iso.)",              "1");
  sh.AddNewPostfix("LepJetNoPt",           [] {  return passLepJetNoPt[i_FatJet]==1 ? 0 : (size_t)-1;           }, "LepJetNoPt",           "Lep. jet (no p_{T})",             "1");
  sh.AddNewPostfix("LepJetCand",           [] {  return passLepJetCand[i_FatJet]==1 ? 0 : (size_t)-1;           }, "LepJetCand",           "Lep. jet (no mass)",              "1");
  sh.AddNewPostfix("LepJet",               [] {  return passLepJet[i_FatJet]==1 ? 0 : (size_t)-1;               }, "LepJet",               "Lep. jet",                        "1");
  sh.AddNewPostfix("LepTopNoIso",          [] {  return passLepTopNoIso[i_FatJet]==1 ? 0 : (size_t)-1;          }, "LepTopNoIso",          "Lep. top (no iso.)",              "1");
  sh.AddNewPostfix("LepTopNoPt",           [] {  return passLepTopNoPt[i_FatJet]==1 ? 0 : (size_t)-1;           }, "LepTopNoPt",           "Lep. top (no p_{T})",             "1");
  sh.AddNewPostfix("LepTopNoMass",         [] {  return passLepTopNoMass[i_FatJet]==1 ? 0 : (size_t)-1;         }, "LepTopNoMass",         "Lep. top (no mass)",              "1");
  sh.AddNewPostfix("LepTopNoSubJetB",      [] {  return passLepTopNoSubJetB[i_FatJet]==1 ? 0 : (size_t)-1;      }, "LepTopNoSubJetB",      "Lep. top (no b)",                 "1");
  sh.AddNewPostfix("LepTop",               [] {  return passLepTop[i_FatJet]==1 ? 0 : (size_t)-1;               }, "LepTop",               "Lep. top",                        "1");
  sh.AddNewPostfix("LepJetHighMass",       [] {  return passLepJetHighMass[i_FatJet]==1 ? 0 : (size_t)-1;       }, "LepJet",               "Massive lep. jet",                "1");
  sh.AddNewPostfix("LepTopHighMass",       [] {  return passLepTopHighMass[i_FatJet]==1 ? 0 : (size_t)-1;       }, "LepTop",               "Massive lep. top",                "1");
  sh.AddNewPostfix("AK8_EB_EE",     [&d] {  return std::abs(d.FatJet[i_FatJet].eta)>=1.5;    }, "Barrel;Endcap", "Barrel;Endcap", "601,418");
  sh.AddNewPostfix("MatchGenHadW",        [] {  return ak8MatchGenHadW[i_FatJet];                       }, "NoMatchGenHadW;MatchGenHadW",     "Mistag Ws;Gen-matched Ws",     "601,418");
  sh.AddNewPostfix("MatchGenHadZ",        [] {  return ak8MatchGenHadZ[i_FatJet];                       }, "NoMatchGenHadZ;MatchGenHadZ",     "Mistag Zs;Gen-matched Zs",     "601,418");
  sh.AddNewPostfix("MatchGenHadTop",      [] {  return ak8MatchGenHadTop[i_FatJet];                     }, "NoMatchGenHadTop;MatchGenHadTop", "Mistag tops;Gen-matched tops", "601,418");
  sh.AddNewPostfix("MatchGenLepTop",      [] {  return ak8MatchGenLepTop[i_FatJet];                     }, "NoMatchGenLepTop;MatchGenLepTop", "Mistag tops;Gen-matched tops", "601,418");
  sh.AddNewPostfix("MatchedGenLeptonMother", [] { 
                     if (!ak8MatchGenLepton[i_FatJet]) return (size_t)-1;
                     if      (ak8MatchedGenLeptonMotherID[i_FatJet]==6) return (size_t)0;
                     else if (ak8MatchedGenLeptonMotherID[i_FatJet]==23) return (size_t)1;
                     else if (ak8MatchedGenLeptonMotherID[i_FatJet]==24) return (size_t)2;
                     return (size_t)3;
                   }, "MatchGenLepTop;MatchGenLepZ;MatchGenLepW;Other", "Lepton from top;Lepton from Z;Lepton from W;Other", col4_red_to_cyan);
  sh.AddNewPostfix("NoMatchGenHadW",     [] { return (size_t)(!ak8MatchGenHadW[i_FatJet]   ?  0 : -1); }, "MistagW", "", "1");
  sh.AddNewPostfix("NoMatchGenHadZ",     [] { return (size_t)(!ak8MatchGenHadZ[i_FatJet]   ?  0 : -1); }, "MistagZ", "", "1");
  sh.AddNewPostfix("NoMatchGenHadTop",   [] { return (size_t)(!ak8MatchGenHadTop[i_FatJet] ?  0 : -1); }, "MistagTop", "", "1");
  sh.AddNewPostfix("MatchGenEleFromTop", [] { return eleMatchGenEleFromTop[i_Electron];                }, "NoMatchGenEleFromTop;MatchGenEleFromTop", "Misid. e;Gen-matched e", "601,418");
  sh.AddNewPostfix("MatchGenMuFromTop",  [] { return muMatchGenMuFromTop[i_Muon];                      }, "NoMatchGenMuFromTop;MatchGenMuFromTop",   "Misid. #mu;Gen-matched #mu", "601,418");

  // gen Postfixes
  sh.AddNewPostfix("GenHadWMatchedAK8_EB_EE", [&d] { return (size_t)(iGenHadWMatchedAK8[i_GenPart]==(size_t)-1 ? -1 : std::abs(d.FatJet[iGenHadWMatchedAK8[i_GenPart]].eta)>=1.5); }, "Barrel;Endcap", "Barrel;Endcap", "601,418");
  sh.AddNewPostfix("GenHadTopMatchedAK8_EB_EE",  [&d] { return (size_t)(iGenHadTopMatchedAK8[i_GenPart] ==(size_t)-1 ? -1 : std::abs(d.FatJet[iGenHadTopMatchedAK8 [i_GenPart]].eta)>=1.5); }, "Barrel;Endcap", "Barrel;Endcap", "601,418");

  // Event
  sh.AddNewPostfix("OtherNonisoLep",  [] { return std::min(nLepVetoNoIso-nLepSelect,(size_t)1); }, "NoOtherNonisoLep;OtherNonisoLep", "0 other unisol. lepton;#geq1 other unisol. lepton", "418,633");
  sh.AddNewPostfix("OtherLooseLep",  [] { return std::min(nLepVeto     -nLepSelect,(size_t)1); }, "NoOtherLep;OtherLep",           "0 other loose lepton;#geq1 other loose lepton", "633,418");
  sh.AddNewPostfix("Ele_Muon",       [] {  return (size_t)(nEleVeto==1 ? 0 : nMuVeto==1 ? 1 : -1); }, "EleOnly;MuOnly", "1 ele;1 muon", "1,2");
  sh.AddNewPostfix("Ele_or_Muon",    [] {  return (size_t)(nEleSelect==1 ? 0 : nMuSelect==1 ? 1 : -1); }, "EleOnly;MuOnly", "1 ele;1 muon", "1,2");
  sh.AddNewPostfix("1Ele",           [] {  return (size_t)(nEleTight==1 ? 0 : -1); }, "1Ele",  "1 ele",  "1");
  sh.AddNewPostfix("1Muon",          [] {  return (size_t)(nMuTight==1 ?  0 : -1); }, "1Muon", "1 muon", "1");
  sh.AddNewPostfix("2Ele_2Muon",     [] {  return (size_t)(nEleSelect==2 ? 0 : nMuSelect==2 ? 1 : -1); }, "EleOnly;MuOnly", "2 ele;2 muon", "1,2");
  //sh.AddNewPostfix("PromptDirect",   [&d] {  return (size_t)(nPhotonSelect==1 ? (d.Photon.isPromptDirect[iPhotonSelect[0]]==1 ? 0 : -1) : -1); }, "PromptDirect", "Prompt, direct", "1");
  sh.AddNewPostfix("1Pho_EB_EE",     [&d] {  return (size_t)(nPhotonSelect==1 ? d.Photon[iPhotonSelect[0]].isScEtaEE : -1); }, "Barrel;Endcap", "Barrel;Endcap", "601,418");
  sh.AddNewPostfix("NJet35",         [] {  return (size_t)(nJet<3 ? -1 : nJet>5); }, "NJet3to5;NJet6", "3#leqN_{jet}#leq5;6#leqN_{jet}", "1,2");
  sh.AddNewPostfix("NJet46",         [] {  return (size_t)(nJet<4 ? -1 : nJet>6); }, "NJet4to6;NJet7", "4#leqN_{jet}#leq6;7#leqN_{jet}", "1,2");
  //sh.AddNewPostfix("NJet45",         [] {  return (size_t)(nJet==4||nJet==5 ? 0 : 1 ); }, "NJet4to5;NJet6", "4#leqN_{jet}#leq5;6#leqN_{jet}", "1,2");
  sh.AddNewPostfix("NJet45",         [] {  return (size_t)(nJet==4||nJet==5 ? 0 : 1 ); }, "NJet4to5;NJet6", "#font[[52]]{4-5 jet category};#font[[52]]{W 6 jet category}", "1,2");
  sh.AddNewPostfix("NJetNoPho35",    [] {  return (size_t)(nJetNoPho<3 ? -1 : nJetNoPho>5); }, "NJet3to5;NJet6", "3#leqN_{jet}#leq5;6#leqN_{jet}", "1,2");
  sh.AddNewPostfix("NJetNoPho46",    [] {  return (size_t)(nJetNoPho<4 ? -1 : nJetNoPho>6); }, "NJet4to6;NJet7", "4#leqN_{jet}#leq6;7#leqN_{jet}", "1,2");
  sh.AddNewPostfix("NJetNoPho45",    [] {  return (size_t)(nJetNoPho==4||nJetNoPho==5 ? 0 : 1 ); }, "NJet4to5;NJet6", "4#leqN_{jet}#leq5;6#leqN_{jet}", "1,2");
  sh.AddNewPostfix("MR800",          []   {  return (size_t)(MR>=800 ? 0 : -1); }, "MR800", "M_{R}#geq800", "1");
  sh.AddNewPostfix("RBins",          [] { return (size_t)((R>=0.1)+(R>=0.2)+(R>=0.4)); }, "R0to0p1;R0p1to0p2;R0p2to0p4;R0p4", "0.0<R<0.1;0.1<R<0.2;0.2<R<0.4;R>=0.4", "1,4,418,633");
  sh.AddNewPostfix("R2Bins",         [] { return (size_t)((R2>=0.08)+(R2>=0.12)+(R2>=0.16)+(R2>=0.24)+(R2>=0.4)); }, 
		   "R2_0to0p08;R2_0p08to0p12;R2_0p12to0p16;R2_0p16to0p24;R2_0p24to0p5;R2_0p5", 
		   "R^{2}#in[0,0.08[;R^{2}#in[0.08,0.12[;R^{2}#in[0.12,0.16[;R^{2}#in[0.16,0.24[;R^{2}#in[0.24,0.4[;R^{2}#in[0.4,2[", col6_rainbow_dark);
  sh.AddNewPostfix("R21lBins",       [] { return (size_t)((R2_1l>=0.08)+(R2_1l>=0.12)+(R2_1l>=0.16)+(R2_1l>=0.24)+(R2_1l>=0.4)); }, 
		   "R21l_0to0p08;R21l_0p08to0p12;R21l_0p12to0p16;R21l_0p16to0p24;R21l_0p24to0p5;R21l_0p5", 
		   "R_{1l}^{2}#in[0,0.08[;R_{1l}^{2}#in[0.08,0.12[;R_{1l}^{2}#in[0.12,0.16[;R_{1l}^{2}#in[0.16,0.24[;R_{1l}^{2}#in[0.24,0.4[;R_{1l}^{2}#in[0.4,2[", col6_rainbow_dark);
  sh.AddNewPostfix("R21vlBins",      [] { return (size_t)((R2_1vl>=0.08)+(R2_1vl>=0.12)+(R2_1vl>=0.16)+(R2_1vl>=0.24)+(R2_1vl>=0.4)); }, 
		   "R21vl_0to0p08;R21vl_0p08to0p12;R21vl_0p12to0p16;R21vl_0p16to0p24;R21vl_0p24to0p5;R21vl_0p5", 
		   "R_{1vl}^{2}#in[0,0.08[;R_{1vl}^{2}#in[0.08,0.12[;R_{1vl}^{2}#in[0.12,0.16[;R_{1vl}^{2}#in[0.16,0.24[;R_{1vl}^{2}#in[0.24,0.4[;R_{1vl}^{2}#in[0.4,2[", col6_rainbow_dark);
  sh.AddNewPostfix("R2llBins",       [] { return (size_t)((R2_ll>=0.08)+(R2_ll>=0.12)+(R2_ll>=0.16)+(R2_ll>=0.24)+(R2_ll>=0.4)); }, 
		   "R2ll_0to0p08;R2ll_0p08to0p12;R2ll_0p12to0p16;R2ll_0p16to0p24;R2ll_0p24to0p5;R2ll_0p5", 
		   "R_{ll}^{2}#in[0,0.08[;R_{ll}^{2}#in[0.08,0.12[;R_{ll}^{2}#in[0.12,0.16[;R_{ll}^{2}#in[0.16,0.24[;R_{ll}^{2}#in[0.24,0.4[;R_{ll}^{2}#in[0.4,2[", col6_rainbow_dark);
  sh.AddNewPostfix("MTBoost800",     []   {  return (size_t)(MT_boost>=800 ? 0 : -1); }, "MTBoost800", "m_{T,Boost+MET}#geq800", "1");

  // Other W/Top tag WPs
  sh.AddNewPostfix("WWP1",            [] {  return (size_t)(nHadWTag1>=1        ? 0 : -1); }, "WWP1",   "tau_{21}<0.35", "1");
  sh.AddNewPostfix("WWP3",            [] {  return (size_t)(nHadWTag3>=1        ? 0 : -1); }, "WWP3",   "tau_{21}<0.55", "1");
  sh.AddNewPostfix("WWP4",            [] {  return (size_t)(nWMassTag>=1        ? 0 : -1); }, "WWP4",   "No tau_{21} cut", "1");
  sh.AddNewPostfix("TopWP2",          [] {  return (size_t)(nHadTopTag2>=1      ? 0 : -1); }, "TopWP2", "tau_{32}<0.54", "1");
  sh.AddNewPostfix("TopWP3",          [] {  return (size_t)(nHadTopTag3>=1      ? 0 : -1); }, "TopWP3", "tau_{32}<0.65", "1");
  sh.AddNewPostfix("TopWP4",          [] {  return (size_t)(nHadTopTag4>=1      ? 0 : -1); }, "TopWP4", "tau_{32}<0.80", "1");
  sh.AddNewPostfix("TopWP5",          [] {  return (size_t)(nHadTop1BMassTag>=1 ? 0 : -1); }, "TopWP5", "No tau_{32} cut", "1");

  sh.AddNewPostfix("Nb",             [] {  return (size_t)(nLooseBTag==0 ? 0 : nMediumBTag>=1 ? 1: -1); },      "bveto;bincl",       "0b;#geq1b",               col4_cyan_to_red);
  sh.AddNewPostfix("Nisob",          [] {  return (size_t)(nLooseIsoBTag==0 ? 0 : nMediumIsoBTag>=1 ? 1: -1); },"isobveto;isobincl", "0b (iso.);#geq1b (iso.)", col4_cyan_to_red);
  sh.AddNewPostfix("2b",             [] {  return (size_t)(nMediumBTag == 2 ? 0 : -1);          }, "2b",               "2b",                      col4_cyan_to_red);
  sh.AddNewPostfix("NW1",            [] {  return (size_t)(nW1         < 3 ? nW1         : -1); }, "[0to2]W1",         "[0to2]W Loose",           col4_cyan_to_red);
  sh.AddNewPostfix("NW2",            [] {  return (size_t)(nW2         < 3 ? nW2         : -1); }, "[0to2]W2",         "[0to2]W Medium",          col4_cyan_to_red);
  sh.AddNewPostfix("NW3",            [] {  return (size_t)(nW3         < 3 ? nW3         : -1); }, "[0to2]W3",         "[0to2]W Tight",           col4_cyan_to_red);
  sh.AddNewPostfix("NWDeep1",        [] {  return (size_t)(nWDeep1     < 3 ? nWDeep1     : -1); }, "[0to2]WDeep1",     "[0to2]W (Deep 5%)",       col4_cyan_to_red);
  sh.AddNewPostfix("NWDeep2",        [] {  return (size_t)(nWDeep2     < 3 ? nWDeep2     : -1); }, "[0to2]WDeep2",     "[0to2]W (Deep 1%)",       col4_cyan_to_red);
  sh.AddNewPostfix("NWDeep3",        [] {  return (size_t)(nWDeep3     < 3 ? nWDeep3     : -1); }, "[0to2]WDeep3",     "[0to2]W (Deep 0.5%)",     col4_cyan_to_red);
  sh.AddNewPostfix("NWDeepMD1",      [] {  return (size_t)(nWDeepMD1   < 3 ? nWDeepMD1   : -1); }, "[0to2]WDeepMD1",   "[0to2]W (DeepMD 5%)",     col4_cyan_to_red);
  sh.AddNewPostfix("NWDeepMD2",      [] {  return (size_t)(nWDeepMD2   < 3 ? nWDeepMD2   : -1); }, "[0to2]WDeepMD2",   "[0to2]W (DeepMD 1%)",     col4_cyan_to_red);
  sh.AddNewPostfix("NWDeepMD3",      [] {  return (size_t)(nWDeepMD3   < 3 ? nWDeepMD3   : -1); }, "[0to2]WDeepMD3",   "[0to2]W (DeepMD 0.5%)",   col4_cyan_to_red);
  sh.AddNewPostfix("NZDeep1",        [] {  return (size_t)(nZDeep1     < 3 ? nZDeep1     : -1); }, "[0to2]ZDeep1",     "[0to2]Z (Deep 0.8)",      col4_cyan_to_red);
  sh.AddNewPostfix("NZDeep2",        [] {  return (size_t)(nZDeep2     < 3 ? nZDeep2     : -1); }, "[0to2]ZDeep2",     "[0to2]Z (Deep 0.95)",     col4_cyan_to_red);
  sh.AddNewPostfix("NZDeep3",        [] {  return (size_t)(nZDeep3     < 3 ? nZDeep3     : -1); }, "[0to2]ZDeep3",     "[0to2]Z (Deep 0.99)",     col4_cyan_to_red);
  sh.AddNewPostfix("NZDeepMD1",      [] {  return (size_t)(nZDeepMD1   < 3 ? nZDeepMD1   : -1); }, "[0to2]ZDeepMD1",   "[0to2]Z (DeepMD 0.3)",    col4_cyan_to_red);
  sh.AddNewPostfix("NZDeepMD2",      [] {  return (size_t)(nZDeepMD2   < 3 ? nZDeepMD2   : -1); }, "[0to2]ZDeepMD2",   "[0to2]Z (DeepMD 0.8)",    col4_cyan_to_red);
  sh.AddNewPostfix("NZDeepMD3",      [] {  return (size_t)(nZDeepMD3   < 3 ? nZDeepMD3   : -1); }, "[0to2]ZDeepMD3",   "[0to2]Z (DeepMD 0.9)",    col4_cyan_to_red);
  sh.AddNewPostfix("NVDeep1",        [] {  return (size_t)(nVDeep1     < 3 ? nVDeep1     : -1); }, "[0to2]VDeep1",     "[0to2]V (Deep L)",        col4_cyan_to_red);
  sh.AddNewPostfix("NVDeep2",        [] {  return (size_t)(nVDeep2     < 3 ? nVDeep2     : -1); }, "[0to2]VDeep2",     "[0to2]V (Deep M)",        col4_cyan_to_red);
  sh.AddNewPostfix("NVDeep3",        [] {  return (size_t)(nVDeep3     < 3 ? nVDeep3     : -1); }, "[0to2]VDeep3",     "[0to2]V (Deep T)",        col4_cyan_to_red);
  sh.AddNewPostfix("NTop1",          [] {  return (size_t)(nTop1       < 3 ? nTop1       : -1); }, "[0to2]Top1",       "[0to2]Top VLoose",        col4_cyan_to_red);
  sh.AddNewPostfix("NTop2",          [] {  return (size_t)(nTop2       < 3 ? nTop2       : -1); }, "[0to2]Top2",       "[0to2]Top Loose",         col4_cyan_to_red);
  sh.AddNewPostfix("NTop3",          [] {  return (size_t)(nTop3       < 3 ? nTop3       : -1); }, "[0to2]Top3",       "[0to2]Top Medium",        col4_cyan_to_red);
  sh.AddNewPostfix("NTop4",          [] {  return (size_t)(nTop4       < 3 ? nTop4       : -1); }, "[0to2]Top4",       "[0to2]Top Tight",         col4_cyan_to_red);
  sh.AddNewPostfix("NTop5",          [] {  return (size_t)(nTop5       < 3 ? nTop5       : -1); }, "[0to2]Top5",       "[0to2]Top VTight",        col4_cyan_to_red);
  sh.AddNewPostfix("NTopDeep1",      [] {  return (size_t)(nTopDeep1   < 3 ? nTopDeep1   : -1); }, "[0to2]TopDeep1",   "[0to2]Top (Deep 5%)",     col4_cyan_to_red);
  sh.AddNewPostfix("NTopDeep2",      [] {  return (size_t)(nTopDeep2   < 3 ? nTopDeep2   : -1); }, "[0to2]TopDeep2",   "[0to2]Top (Deep 1%)",     col4_cyan_to_red);
  sh.AddNewPostfix("NTopDeep3",      [] {  return (size_t)(nTopDeep3   < 3 ? nTopDeep3   : -1); }, "[0to2]TopDeep3",   "[0to2]Top (Deep 0.5%)",   col4_cyan_to_red);
  sh.AddNewPostfix("NTopDeep4",      [] {  return (size_t)(nTopDeep4   < 3 ? nTopDeep4   : -1); }, "[0to2]TopDeep4",   "[0to2]Top (Deep 0.1%)",   col4_cyan_to_red);
  sh.AddNewPostfix("NTopDeepMD1",    [] {  return (size_t)(nTopDeepMD1 < 3 ? nTopDeepMD1 : -1); }, "[0to2]TopDeepMD1", "[0to2]Top (DeepMD 5%)",   col4_cyan_to_red);
  sh.AddNewPostfix("NTopDeepMD2",    [] {  return (size_t)(nTopDeepMD2 < 3 ? nTopDeepMD2 : -1); }, "[0to2]TopDeepMD2", "[0to2]Top (DeepMD 1%)",   col4_cyan_to_red);
  sh.AddNewPostfix("NTopDeepMD3",    [] {  return (size_t)(nTopDeepMD3 < 3 ? nTopDeepMD3 : -1); }, "[0to2]TopDeepMD3", "[0to2]Top (DeepMD 0.5%)", col4_cyan_to_red);
  sh.AddNewPostfix("NTopDeepMD4",    [] {  return (size_t)(nTopDeepMD4 < 3 ? nTopDeepMD4 : -1); }, "[0to2]TopDeepMD4", "[0to2]Top (DeepMD 0.1%)", col4_cyan_to_red);
  sh.AddNewPostfix("NVDeep1_Nisob",     [] {
                     size_t i = -1;
                     if (nVDeep1 == 0) i=0;
                     else if (nVDeep1==1&&nLooseIsoBTag==0) i=1;
                     else if (nVDeep1==1&&nMediumIsoBTag>0) i=2;
                     else if (nVDeep1==2&&nLooseIsoBTag==0) i=3;
                     else if (nVDeep1==2&&nMediumIsoBTag>0) i=4;
                     return i;
                   }, "0VDeep1;1VDeep1_isobveto;1VDeep1_isobincl;2VDeep1_isobveto;2VDeep1_isobincl", "0W/Z (Deep);1W/Z (Deep), 0b (iso.);1W/Z (Deep), #geq1b (iso.);2W/Z (Deep 0.8), 0b (iso.);2W/Z (Deep), #geq1b (iso.)", col5_green_to_red);
  sh.AddNewPostfix("NVDeep2_Nisob",     [] {
                     size_t i = -1;
                     if (nVDeep2 == 0) i=0;
                     else if (nVDeep2==1&&nLooseIsoBTag==0) i=1;
                     else if (nVDeep2==1&&nMediumIsoBTag>0) i=2;
                     else if (nVDeep2==2&&nLooseIsoBTag==0) i=3;
                     else if (nVDeep2==2&&nMediumIsoBTag>0) i=4;
                     return i;
                   }, "0VDeep2;1VDeep2_isobveto;1VDeep2_isobincl;2VDeep2_isobveto;2VDeep2_isobincl", "0W/Z (Deep);1W/Z (Deep), 0b (iso.);1W/Z (Deep), #geq1b (iso.);2W/Z (Deep 0.8), 0b (iso.);2W/Z (Deep), #geq1b (iso.)", col5_green_to_red);
  sh.AddNewPostfix("Nisob_NJet24",     [] {
                     if (nJet>=2&&nJet<=4) {
                       if      (nLooseIsoBTag==0) return (size_t)0;
                       else if (nMediumIsoBTag>0) return (size_t)1;
                     }
                     return (size_t)-1;
                   }, "isobveto_NJet24;isobincl_NJet24", "0b (iso.), 2-4 jet;#geq1b (iso.), 2-4 jet", "1");
  sh.AddNewPostfix("NLepJetCand",     [] {  return (size_t)(nLepJetCand     < 3 ? nLepJetCand     : -1); }, "[0to2]LepJetCand",     "[0to2]Lep. jet cand.",      col4_cyan_to_red);
  sh.AddNewPostfix("NLepJet",         [] {  return (size_t)(nLepJet         < 3 ? nLepJet         : -1); }, "[0to2]LepJet",         "[0to2]Lep. jet",            col4_cyan_to_red);
  sh.AddNewPostfix("NLepTop",         [] {  return (size_t)(nLepTop         < 3 ? nLepTop         : -1); }, "[0to2]LepTop",         "[0to2]Lep. top",            col4_cyan_to_red);
  sh.AddNewPostfix("NLepJetHighMass", [] {  return (size_t)(nLepJetHighMass < 3 ? nLepJetHighMass : -1); }, "[0to2]LepJetHighMass", "[0to2]Massive lep. jet",    col4_cyan_to_red);
  sh.AddNewPostfix("NLepTopHighMass", [] {  return (size_t)(nLepTopHighMass < 3 ? nLepTopHighMass : -1); }, "[0to2]LepTopHighMass", "[0to2]Massive lep. top",    col4_cyan_to_red);
  sh.AddNewPostfix("NHadTop",         [] {  return (size_t)(nHadTop         < 3 ? nHadTop         : -1); }, "[0to2]HadTop",         "[0to2]Had. top (Deep 1%)",  col4_cyan_to_red);
  sh.AddNewPostfix("NHadW",           [] {  return (size_t)(nHadW           < 3 ? nHadW           : -1); }, "[0to2]HadW",           "[0to2]Had. W (Deep 1%)",    col4_cyan_to_red);
  if (debug) std::cout<<"Analysis::define_histo_options: postfixes ok"<<std::endl;

  // Weights
  sh.AddNewPostfix("NoPUWeight",     [] { return 0; }, "NoPUWeight",   "No pile-up reweighting", "1");
  sh.AddNewPostfix("NoTrigWeight",   [] { return 0; }, "NoTrigWeight", "No trigger weighting",   "1");
  sh.AddNewPostfix("NoEleSF",        [] { return 0; }, "NoEleSF",      "No ele SF",              "1");
  sh.AddNewPostfix("NoMuonSF",       [] { return 0; }, "NoMuonSF",     "No muon SF",             "1");
  sh.AddNewPostfix("NoBTagSF",       [] { return 0; }, "NoBTagSF",     "No b-tag SF",            "1");
  sh.AddNewPostfix("NoWTagSF",       [] { return 0; }, "NoWTagSF",     "No W-tag SF",            "1");
  sh.AddNewPostfix("NoTopTagSF",     [] { return 0; }, "NoTopTagSF",   "No top-tag SF",          "1");
  sh.AddNewPostfix("NoWeight",       [] { return 0; }, "NoWeight",     "",                       "1");

  // Bins
  std::vector<double> E   = {0, 100, 200, 400, 600, 800, 1000, 1500, 2000, 10000};
//std::vector<double> Pt  = {0, 100, 150, 200, 250, 300, 350, 400, 450, 500, 550, 600, 650, 700, 800, 900,       1200, 2000, 10000};
  std::vector<double> Pt  = {0, 100, 150, 200,      300,      400,      500,      600,           800,                  2000, 10000};
//std::vector<double> PtG = {0, 100, 150, 200, 250, 300, 350, 400,      500,                700,           1000,       2000, 10000};
  std::vector<double> PtG = {0, 100, 150, 200,      300,      400,                600,           800,                  2000, 10000};
//std::vector<double> PtF = {0,           200,      300,      400, 450, 500, 550, 600,      700,           1000,       2000, 10000};
  std::vector<double> PtF = {0,           200,      300,      400,                600,                     1000,       2000, 10000};
  std::vector<double> PtO = {0,                               400,                                                     2000, 10000};
  std::vector<double> M   = {0, 10, 20, 30, 40, 50, 65, 75, 85, 95, 105, 120, 135, 150, 165, 180, 195, 210, 230, 260, 300, 500, 1000};
  std::vector<double> MW  = {65, 75, 85, 95, 105};
  std::vector<double> CSV = {0, 0.05, 0.2, 0.4, 0.6, 0.7, 0.8, 0.9, 0.95, 1.0 };
  std::vector<double> MDP;
  for (double x=0.0; x< 1.8; x+=0.1) MDP.push_back(x);
  for (double x=1.8; x< 2.4; x+=0.2) MDP.push_back(x);
  for (double x=2.4; x<=3.2; x+=0.4) MDP.push_back(x);
  std::vector<double> DP;
  for (double x=0.0; x<1.6; x+=0.4) DP.push_back(x);
  for (double x=1.6; x<2.4; x+=0.2) DP.push_back(x);
  for (double x=2.4; x<3.2; x+=0.1) DP.push_back(x);
  std::vector<double> M2;
  for (double x=  0; x< 250; x+=10) M2.push_back(x);
  for (double x=250; x< 500; x+=25) M2.push_back(x);
  for (double x=500; x<1000; x+=50) M2.push_back(x);
  std::vector<double> NVTX(1,0);
  for (double x=6;  x<  40;  x+=2) NVTX.push_back(x);
  for (double x=40; x<=100;  x+=5) NVTX.push_back(x);
  std::vector<double> R_bins   = {0, 0.05, 0.1, 0.15, 0.2, 0.25, 0.3, 0.35, 0.4, 0.6, 0.7, 0.8, 1.0, 1.2, 2.0 };
  std::vector<double> MR_bins  = {0, 700, 800, 1000, 1200, 1600, 2000, 4000, 10000};
  std::vector<double> MTR_bins = {0, 100, 200, 300, 400, 600, 800, 1000, 1200, 1600, 2000, 4000};
  //std::vector<double> MET = {0,     100,                     200,      300, 400, 500, 600, 700, 800, 1000, 1500, 2000};
  std::vector<double> MET = {0, 80, 100, 120, 140, 160, 180, 200, 250, 300, 400, 500, 600, 700, 800, 1000, 1500, 2000};
  std::vector<double> R2_bins  = {0, 0.04, 0.08, 0.12, 0.16, 0.24, 0.4, 1.5};
  std::vector<double> HT = {0, 200, 300, 400, 500, 600, 650, 700, 750, 800, 850, 900, 950, 1000, 1100, 1200, 1500, 2000, 2500, 3000, 4000, 10000};
  std::vector<double> HTB = {400, 500, 600, 700, 750, 800, 850, 900, 950, 1000, 1500, 10000}; // 2D Trigger Eff
  std::vector<double> PtB = {200, 300, 400, 450, 500, 550, 600, 1000, 10000}; // 2D Trigger Eff
  std::vector<double> LepPt  = { 0, 5, 10, 15, 20, 30, 40, 50, 60, 80, 100, 120, 150, 200, 250, 300, 400, 500, 1000 };
  std::vector<double> LepEta = { 0.0, 0.5, 1.0, 1.5, 2.0, 2.5 };
  // Razor inclusive binning
  std::vector<double> MR_RI = {300, 400, 500, 600, 700, 900, 1200, 4000};
  std::vector<double> R2_RI = {0.15, 0.2, 0.25, 0.3, 0.41, 0.52, 1.5};
  // Unrolled bin labels
  std::vector<double> MR_2D_bins      = {0.8, 1.0, 1.2, 1.6, 2.0, 4.0};
  std::vector<double> MR_2D_bins_lep  = {0.7, 0.8, 1.0, 1.2, 1.6, 2.0, 4.0};
  std::vector<double> R2_2D_bins      = {0.08, 0.12, 0.16, 0.24, 0.4, 1.5};
  std::vector<double> HT_2D_bins_old  = {0.4, 0.5, 0.6, 0.7, 0.75, 0.8, 0.85, 0.9, 0.95, 1.0, 1.5, 10.0};
  std::vector<double> Pt_2D_bins      = {200, 300, 400, 450, 500, 550, 600, 1000, 5000};
  std::vector<double> PtLow_2D_bins   = {200, 300, 400, 450, 500};
  std::vector<double> PtHigh_2D_bins  = {550, 600, 1000, 5000};
  std::vector<double> ElePt_2D_bins   = {10, 15, 20, 30, 35, 40, 50, 100, 125, 250, 500};
  std::vector<double> MuPt_2D_bins    = {10, 15, 20, 25, 30, 35, 40,  50,  60, 100, 250, 500};
  std::vector<double> HT_2D_bins_lep  = {200, 300, 350, 400, 450, 500, 5000};
  std::vector<double> HT1_2D_bins_lep = {200, 300, 350};
  std::vector<double> HT2_2D_bins_lep = {350, 400, 450};
  std::vector<double> HT3_2D_bins_lep = {450, 500, 5000};
  // HT/MET Trigger turnons
  // HT:   0  500   700   800  1050
  // MHT:  0   75    85   100   120
  // MET:  0  100   115   136   158
  // rat:    1.33  1.35  1.36  1.32
  //std::vector<double> HT_2D_bins  = {0, 400, 500, 600, 700, 800, 1000, 1200, 1500, 5000}; // 2D Trigger Eff Run2017-18
  std::vector<double> HT_2D_bins  = {200,  450,  600,  700, 800, 900, 1000, 1200, 10000}; // 2D Trigger Eff Run2017-18
  std::vector<double> HT1_2D_bins = {200,  450,  600}; // 2D Trigger Eff Run2017-18
  std::vector<double> HT2_2D_bins = {600,  700,  800,  900}; // 2D Trigger Eff Run2017-18
  std::vector<double> HT3_2D_bins = {900, 1000, 1200, 10000}; // 2D Trigger Eff Run2017-18
  std::vector<double> MET_2D_bins = {60, 100, 130, 160, 180, 200, 250, 300, 400, 4000}; // 2D Trigger Eff Run2017-18
  // HT,MET Changgi {300, 500, 550, 600, 800, 1500, 10000}, {50, 150, 200, 400, 10000}, {}, 0, 0);
  // unrolled bin mergin
  std::vector<int> merged_razor_bins = {19,23,24};
  std::vector<int> merged_razor_bins_lep = {24,28,29};
  std::vector<int> merged_trigger_bins  = {1,3,5,  11,   20, 37,44,  46,52,53, 55,57,59,61,62, 64,65,66,67,68,69,70,71};
  std::vector<int> merged_trigger1_bins = {1,3,5,  11                                                                 };
  std::vector<int> merged_trigger2_bins = {               2, 19,26,  28,34,35                                         };
  std::vector<int> merged_trigger3_bins = {                                    10,12,14,16,17, 19,20,21,22,23,24,25,26};

  // Bin Postfixes
  std::stringstream HT_pf, HT_leg;
  for (size_t i=0, n=HTB.size(); i<n-1; ++i) {
    HT_pf<<"HT"<<HTB[i]<<"to"<<HTB[i+1];
    HT_leg<<"H_{T} #subset ["<<HTB[i]<<","<<HTB[i+1]<<"[";
    if (i!=n-2) { HT_pf<<";"; HT_leg<<";"; }
  }
  sh.AddNewPostfix("HTBins", [HTB] { for (size_t i=0, n=HTB.size(); i<n-1; ++i) if (AK4_Ht>=HTB[i]&&AK4_Ht<HTB[i+1]) return i; return (size_t)-1; },
		   HT_pf.str(), HT_leg.str(), col12+col12);
  std::stringstream AK8Pt_pf, AK8Pt_leg;
  for (size_t i=0, n=PtB.size(); i<n-1; ++i) {
    AK8Pt_pf<<"Jet1AK8Pt"<<PtB[i]<<"to"<<PtB[i+1];
    AK8Pt_leg<<"AK8 jet1 p_{T} #subset ["<<PtB[i]<<","<<PtB[i+1]<<"[";
    if (i!=n-2) { AK8Pt_pf<<";"; AK8Pt_leg<<";"; }
  }
  sh.AddNewPostfix("Jet1AK8PtBins", [PtB,&d] { if (nJetAK8<1) return (size_t)-1;
		     for (size_t i=0, n=PtB.size(); i<n-1; ++i) if (d.FatJet[iJetAK8[0]].pt>=PtB[i]&&d.FatJet[iJetAK8[0]].pt<PtB[i+1]) return i; 
		     return (size_t)-1; }, AK8Pt_pf.str(), AK8Pt_leg.str(), col8+col8);


  // --------------------------------------------------------------------
  //                         Fill Parameters
  // --------------------------------------------------------------------

  sh.AddNewFillParams("Bin", { .nbin=1,   .bins={0,1}, .fill=[] { return 0; }, .axis_title="Bin", .def_range={0,1}}); // For averages/counts

   // Veto Leptons
  sh.AddNewFillParams("VetoLepPt",       { .nbin=LepPt.size()-1,  .bins=LepPt,  .fill=[] { return vetoLepPt;                           }, .axis_title="Veto Lepton p_{T} (GeV)", .def_range={5,1000}});
  sh.AddNewFillParams("VetoLepEta",      { .nbin=LepEta.size()-1, .bins=LepEta, .fill=[] { return std::abs(vetoLepEta);                }, .axis_title="Veto Lepton |#eta| (GeV)"});
  sh.AddNewFillParams("VetoElePt",       { .nbin=LepPt.size()-1, .bins=LepPt,   .fill=[&d] { return d.Electron[i_Electron].pt;                  }, .axis_title="Loose Electron p_{T} (GeV)", .def_range={0,500}});
  sh.AddNewFillParams("VetoEleEta",      { .nbin=LepEta.size()-1, .bins=LepEta, .fill=[&d] { return d.Electron[i_Electron].eta;                 }, .axis_title="Loose Electron #eta",  .def_range={-2.5,2.5}});
  sh.AddNewFillParams("VetoMuPt",        { .nbin=LepPt.size()-1, .bins=LepPt,   .fill=[&d] { return d.Muon[i_Muon].pt;                    }, .axis_title="Loose Muon p_{T} (GeV)",     .def_range={0,500}});
  sh.AddNewFillParams("VetoMuEta",       { .nbin=LepEta.size()-1, .bins=LepEta, .fill=[&d] { return d.Muon[i_Muon].eta;                   }, .axis_title="Loose Muon #eta",      .def_range={-2.4,2.4}});
  sh.AddNewFillParams("VetoTauPt",       { .nbin=LepPt.size()-1, .bins=LepPt,   .fill=[&d] { return d.Tau[i_Tau].pt;                  }, .axis_title="Loose Tau p_{T} (GeV)",     .def_range={0,500}});
  sh.AddNewFillParams("VetoTauEta",      { .nbin=LepEta.size()-1, .bins=LepEta, .fill=[&d] { return d.Tau[i_Tau].eta;                 }, .axis_title="Loose Tau #eta",      .def_range={-2.6,2.6}});

  // Selected Leptons
  // Electrons
  sh.AddNewFillParams("ElePt",           { .nbin= 100, .bins={     0,    500}, .fill=[&d] { return nEleSelect<1 ? -9999 : d.Electron[iEleSelect[0]].pt;  }, .axis_title="Electron p_{T} (GeV)", .def_range={ELE_SELECT_PT_CUT,250}});
  sh.AddNewFillParams("EleEta",          { .nbin=  40, .bins={    -4,      4}, .fill=[&d] { return nEleSelect<1 ? -9999 : d.Electron[iEleSelect[0]].eta; }, .axis_title="Electron #eta",  .def_range={-ELE_SELECT_ETA_CUT,ELE_SELECT_ETA_CUT}});
  sh.AddNewFillParams("EleJetDR",        { .nbin=  60, .bins={     0,      6}, .fill=[] { return nEleSelect<1 ? -9999 : eleJetDR[iEleSelect[0]];         }, .axis_title="#DeltaR (ele, jet)",         .def_range={0,4}});
  sh.AddNewFillParams("EleJetPt",        { .nbin= 100, .bins={     0,    500}, .fill=[] { return nEleSelect<1 ? -9999 : eleJetPt[iEleSelect[0]];         }, .axis_title="p_{T, nearest jet to ele}"});
  sh.AddNewFillParams("EleJetDPhi",      { .nbin=MDP.size()-1, .bins=MDP,      .fill=[] { return nEleSelect<1 ? -9999 : eleJetDPhi[iEleSelect[0]];       }, .axis_title="#Delta#phi (ele, jet)"});
  sh.AddNewFillParams("Ele1JetDPhi",     { .nbin=MDP.size()-1, .bins=MDP,      .fill=[] { return nEleSelect<1 ? -9999 : eleJetDPhi[iEleSelect[0]]; }, .axis_title="#Delta#phi (1st ele, jet)"});
  sh.AddNewFillParams("Ele2JetDPhi",     { .nbin=MDP.size()-1, .bins=MDP,      .fill=[] { return nEleSelect<2 ? -9999 : eleJetDPhi[iEleSelect[1]]; }, .axis_title="#Delta#phi (2nd ele, jet)"});
  sh.AddNewFillParams("EleCleanJetDRmin",{ .nbin=  60, .bins={     0,      6}, .fill=[] { return eleCleanJetDRmin[i_Electron]; }, .axis_title="e, jet #DeltaR_{min}"});
  sh.AddNewFillParams("EleCleanJetPtrel",{ .nbin=  40, .bins={     0,    100}, .fill=[] { return eleCleanJetPtrel[i_Electron]; }, .axis_title="e, cleaned jet p_{T,rel} (GeV)"});
  sh.AddNewFillParams("EleTightPt",       { .nbin= 100, .bins={     0,    500}, .fill=[&d] { return nEleTight<1 ? -9999 : d.Electron[iEleTight[0]].pt;  }, .axis_title="Electron p_{T} (GeV)", .def_range={ELE_TIGHT_PT_CUT,250}});
  sh.AddNewFillParams("EleTightEta",      { .nbin=  40, .bins={    -4,      4}, .fill=[&d] { return nEleTight<1 ? -9999 : d.Electron[iEleTight[0]].eta; }, .axis_title="Electron #eta",  .def_range={-ELE_TIGHT_ETA_CUT,ELE_TIGHT_ETA_CUT}});
  sh.AddNewFillParams("EleTightNoIsoPt",       { .nbin= 100, .bins={     0,    500}, .fill=[&d] { return nEleTightNoIso<1 ? -9999 : d.Electron[iEleTightNoIso[0]].pt;  }, .axis_title="Electron p_{T} (GeV)", .def_range={ELE_TIGHT_PT_CUT,250}});
  sh.AddNewFillParams("EleTightNoIsoEta",      { .nbin=  40, .bins={    -4,      4}, .fill=[&d] { return nEleTightNoIso<1 ? -9999 : d.Electron[iEleTightNoIso[0]].eta; }, .axis_title="Electron #eta",  .def_range={-ELE_TIGHT_ETA_CUT,ELE_TIGHT_ETA_CUT}});
  sh.AddNewFillParams("EleTight2DPt",       { .nbin= 100, .bins={     0,    500}, .fill=[&d] { return nEleTight2D<1 ? -9999 : d.Electron[iEleTight2D[0]].pt;  }, .axis_title="Electron p_{T} (GeV)", .def_range={ELE_TIGHT_PT_CUT,250}});
  sh.AddNewFillParams("EleTight2DEta",      { .nbin=  40, .bins={    -4,      4}, .fill=[&d] { return nEleTight2D<1 ? -9999 : d.Electron[iEleTight2D[0]].eta; }, .axis_title="Electron #eta",  .def_range={-ELE_TIGHT_ETA_CUT,ELE_TIGHT_ETA_CUT}});
  // Muons
  sh.AddNewFillParams("MuPt",            { .nbin= 100, .bins={     0,    500}, .fill=[&d] { return nMuSelect<1 ? -9999 : d.Muon[iMuSelect[0]].pt;  }, .axis_title="Muon p_{T} (GeV)", .def_range={MU_SELECT_PT_CUT,250}});
  sh.AddNewFillParams("MuEta",           { .nbin=  40, .bins={    -4,      4}, .fill=[&d] { return nMuSelect<1 ? -9999 : d.Muon[iMuSelect[0]].eta; }, .axis_title="Muon #eta",        .def_range={-MU_SELECT_ETA_CUT,MU_SELECT_ETA_CUT}});
  sh.AddNewFillParams("MuJetDR",         { .nbin=  60, .bins={     0,      6}, .fill=[] { return nMuSelect<1 ? -9999 : muJetDR[iMuSelect[0]];      }, .axis_title="#DeltaR (muon, jet)",        .def_range={0,4}});
  sh.AddNewFillParams("MuJetPt",         { .nbin= 100, .bins={     0,    500}, .fill=[] { return nMuSelect<1 ? -9999 : muJetPt[iMuSelect[0]];      }, .axis_title="p_{T, nearest jet to muon}"});
  sh.AddNewFillParams("MuJetDPhi",       { .nbin=MDP.size()-1, .bins=MDP,      .fill=[] { return nMuSelect<1 ? -9999 : muJetDPhi[iMuSelect[0]];    }, .axis_title="#Delta#phi (muon, jet)"});
  sh.AddNewFillParams("Mu1JetDPhi",      { .nbin=MDP.size()-1, .bins=MDP,      .fill=[] { return nMuSelect<1 ? -9999 : muJetDPhi[iMuSelect[0]]; }, .axis_title="#Delta#phi (1st muon, jet)"});
  sh.AddNewFillParams("Mu2JetDPhi",      { .nbin=MDP.size()-1, .bins=MDP,      .fill=[] { return nMuSelect<2 ? -9999 : muJetDPhi[iMuSelect[1]]; }, .axis_title="#Delta#phi (2nd muon, jet)"});
  sh.AddNewFillParams("MuCleanJetDRmin",{ .nbin=  60, .bins={     0,      6}, .fill=[] { return muCleanJetDRmin[i_Muon]; }, .axis_title="#mu, jet #DeltaR_{min}"});
  sh.AddNewFillParams("MuCleanJetPtrel",{ .nbin=  40, .bins={     0,    100}, .fill=[] { return muCleanJetPtrel[i_Muon]; }, .axis_title="#mu, cleaned jet p_{T,rel} (GeV)"});
  sh.AddNewFillParams("MuTightPt",            { .nbin= 100, .bins={     0,    500}, .fill=[&d] { return nMuTight<1 ? -9999 : d.Muon[iMuTight[0]].pt;  }, .axis_title="Muon p_{T} (GeV)", .def_range={MU_TIGHT_PT_CUT,250}});
  sh.AddNewFillParams("MuTightEta",           { .nbin=  40, .bins={    -4,      4}, .fill=[&d] { return nMuTight<1 ? -9999 : d.Muon[iMuTight[0]].eta; }, .axis_title="Muon #eta",        .def_range={-MU_TIGHT_ETA_CUT,MU_TIGHT_ETA_CUT}});
  sh.AddNewFillParams("MuTightNoIsoPt",            { .nbin= 100, .bins={     0,    500}, .fill=[&d] { return nMuTightNoIso<1 ? -9999 : d.Muon[iMuTightNoIso[0]].pt;  }, .axis_title="Muon p_{T} (GeV)", .def_range={MU_TIGHT_PT_CUT,250}});
  sh.AddNewFillParams("MuTightNoIsoEta",           { .nbin=  40, .bins={    -4,      4}, .fill=[&d] { return nMuTightNoIso<1 ? -9999 : d.Muon[iMuTightNoIso[0]].eta; }, .axis_title="Muon #eta",        .def_range={-MU_TIGHT_ETA_CUT,MU_TIGHT_ETA_CUT}});
  sh.AddNewFillParams("MuTight2DPt",            { .nbin= 100, .bins={     0,    500}, .fill=[&d] { return nMuTight2D<1 ? -9999 : d.Muon[iMuTight2D[0]].pt;  }, .axis_title="Muon p_{T} (GeV)", .def_range={MU_TIGHT_PT_CUT,250}});
  sh.AddNewFillParams("MuTight2DEta",           { .nbin=  40, .bins={    -4,      4}, .fill=[&d] { return nMuTight2D<1 ? -9999 : d.Muon[iMuTight2D[0]].eta; }, .axis_title="Muon #eta",        .def_range={-MU_TIGHT_ETA_CUT,MU_TIGHT_ETA_CUT}});


  // GenTruth for Leptons
  sh.AddNewFillParams("EleVeto_Bkg",             { .nbin= 2, .bins={-0.5,1.5}, .fill=[] { return background_opt.index==0 ? (int)eleMatchGenEleFromW[i_Electron] : (int)-1; }});
  sh.AddNewFillParams("MuVeto_Bkg",              { .nbin= 2, .bins={-0.5,1.5}, .fill=[] { return background_opt.index==0 ? (int)muMatchGenMuFromW[i_Muon] : (int)-1; }});
  // cuts not for comparison
  sh.AddNewFillParams("elept5_nocomp",           { .nbin=1,  .bins={5, 5000}, .fill=[&d] { return d.Electron[i_Electron].pt; }, .axis_title="p_{T,e}", .def_range={5, 5000}});
  sh.AddNewFillParams("elept10_nocomp",          { .nbin=1,  .bins={10,5000}, .fill=[&d] { return d.Electron[i_Electron].pt; }, .axis_title="p_{T,e}", .def_range={10,5000}});
  sh.AddNewFillParams("elept30_nocomp",          { .nbin=1,  .bins={30,5000}, .fill=[&d] { return d.Electron[i_Electron].pt; }, .axis_title="p_{T,e}", .def_range={30,5000}});
  sh.AddNewFillParams("mupt5_nocomp",            { .nbin=1,  .bins={5 ,5000}, .fill=[&d] { return d.Muon[i_Muon].pt; }, .axis_title="p_{T,#mu}", .def_range={5, 5000}});
  sh.AddNewFillParams("mupt10_nocomp",           { .nbin=1,  .bins={10,5000}, .fill=[&d] { return d.Muon[i_Muon].pt; }, .axis_title="p_{T,#mu}", .def_range={10,5000}});
  sh.AddNewFillParams("mupt30_nocomp",           { .nbin=1,  .bins={30,5000}, .fill=[&d] { return d.Muon[i_Muon].pt; }, .axis_title="p_{T,#mu}", .def_range={30,5000}});
  sh.AddNewFillParams("eleeta_veto_nocomp",      { .nbin=1,  .bins={1,2}, .fill=[&d]     { return std::abs(d.Electron[i_Electron].eta)<2.5; }, .axis_title="#eta_{e}", .def_range={1,2}});
  sh.AddNewFillParams("eleeta_nocomp",           { .nbin=1,  .bins={2,3}, .fill=[&d] { 
                                                      double abseta = std::abs(d.Electron[i_Electron].eta);
                                                      if      (abseta>=2.5)                 return 0;
                                                      else if (abseta>=1.442&&abseta<1.556) return 1;
                                                      else return 2; }, .axis_title="#eta_{e}", .def_range={2,3}});
  sh.AddNewFillParams("mueta_nocomp",            { .nbin=1,  .bins={1,2}, .fill=[&d] { return std::abs(d.Muon[i_Muon].eta)<2.4; }, .axis_title="#eta_{#mu}", .def_range={1,2}});
  sh.AddNewFillParams("eleip_loose_nocomp",      { .nbin=1,  .bins={1,2}, .fill=[&d] { return std::abs(d.Electron[i_Electron].dz)<0.50&&std::abs(d.Electron[i_Electron].dxy)<0.2; }, .axis_title="vtx. d_{xy,e}/d_{z,e}", .def_range={1,2}});
  sh.AddNewFillParams("eleip_medium_nocomp",     { .nbin=1,  .bins={1,2}, .fill=[&d] { return std::abs(d.Electron[i_Electron].dz)<0.10&&std::abs(d.Electron[i_Electron].dxy)<0.05; }, .axis_title="vtx. d_{xy,e}/d_{z,e}", .def_range={1,2}});
  sh.AddNewFillParams("muip_loose_nocomp",       { .nbin=1,  .bins={1,2}, .fill=[&d] { return std::abs(d.Muon[i_Muon].dz)<0.50&&std::abs(d.Muon[i_Muon].dxy)<0.2; }, .axis_title="vtx. d_{xy,#mu}/d_{z,#mu}", .def_range={1,2}});
  sh.AddNewFillParams("muminiiso_loose_nocomp",  { .nbin=1,  .bins={1,2}, .fill=[&d] { return d.Muon[i_Muon].miniPFRelIso_all<0.4; }, .axis_title="#mu Mini iso.", .def_range={1,2}});
  sh.AddNewFillParams("muid_soft_nocomp",        { .nbin=1,  .bins={1,2}, .fill=[&d] { return d.Muon[i_Muon].softId; }, .axis_title="Soft ID", .def_range={1,2}});
  sh.AddNewFillParams("muid_mva_loose_nocomp",   { .nbin=1,  .bins={1,2}, .fill=[&d] { return d.Muon[i_Muon].mvaId>0; }, .axis_title="#mu MVA Loose ID", .def_range={1,2}});
  sh.AddNewFillParams("eleid_mva_loose_nocomp",  { .nbin=1,  .bins={1,2}, .fill=[&d] { return d.Electron[i_Electron].mvaFall17V2noIso_WPL; }, .axis_title="e MVA Loose ID (no iso.)", .def_range={1,2}});
  // pt/eta - can easily be tuned
  // pt      - green 418;
  // eta     - black 1;
  sh.AddNewFillParams("elept5",                  { .nbin=23,  .bins={0,5,10,15,20,25,30,35,40,45,50,60,70,80,100,125,150,200,250,300,400,500,1000,5000}, .fill=[&d] { return d.Electron[i_Electron].pt; }, .axis_title="p_{T,e}", .def_range={5, 5000, 418}});
  sh.AddNewFillParams("elept10",                 { .nbin=23,  .bins={0,5,10,15,20,25,30,35,40,45,50,60,70,80,100,125,150,200,250,300,400,500,1000,5000}, .fill=[&d] { return d.Electron[i_Electron].pt; }, .axis_title="p_{T,e}", .def_range={10,5000, 418}});
  sh.AddNewFillParams("elept30",                 { .nbin=23,  .bins={0,5,10,15,20,25,30,35,40,45,50,60,70,80,100,125,150,200,250,300,400,500,1000,5000}, .fill=[&d] { return d.Electron[i_Electron].pt; }, .axis_title="p_{T,e}", .def_range={30,5000, 418}});
  sh.AddNewFillParams("mupt5",                   { .nbin=23,  .bins={0,5,10,15,20,25,30,35,40,45,50,60,70,80,100,125,150,200,250,300,400,500,1000,5000}, .fill=[&d] { return d.Muon[i_Muon].pt; }, .axis_title="p_{T,#mu}", .def_range={5, 5000, 418}});
  sh.AddNewFillParams("mupt10",                  { .nbin=23,  .bins={0,5,10,15,20,25,30,35,40,45,50,60,70,80,100,125,150,200,250,300,400,500,1000,5000}, .fill=[&d] { return d.Muon[i_Muon].pt; }, .axis_title="p_{T,#mu}", .def_range={10,5000, 418}});
  sh.AddNewFillParams("mupt30",                  { .nbin=23,  .bins={0,5,10,15,20,25,30,35,40,45,50,60,70,80,100,125,150,200,250,300,400,500,1000,5000}, .fill=[&d] { return d.Muon[i_Muon].pt; }, .axis_title="p_{T,#mu}", .def_range={30,5000, 418}});
  sh.AddNewFillParams("eleeta_veto",             { .nbin=4, .bins={0,4}, .fill=[&d] {
                                                      double abseta = std::abs(d.Electron[i_Electron].eta);
                                                      if      (abseta>=2.5)                 return 0;
                                                      else if (abseta>=1.442&&abseta<1.556) return 1;
                                                      else if (abseta>=2.1)                 return 2;
                                                      else                                  return 3;
                                                    }, .axis_title="#eta_{e}", .def_range={1,4, 1}});
  sh.AddNewFillParams("eleeta",                  { .nbin=4,  .bins={0,4}, .fill=[&d] { 
                                                      double abseta = std::abs(d.Electron[i_Electron].eta);
                                                      if      (abseta>=2.5)                 return 0;
                                                      else if (abseta>=1.442&&abseta<1.556) return 1;
                                                      else if (abseta>=2.1)                 return 2;
                                                      else                                  return 3;
                                                    }, .axis_title="#eta_{#mu}", .def_range={2,4, 1}});
  sh.AddNewFillParams("mueta",                   { .nbin=3,   .bins={0,3}, .fill=[&d] { 
                                                       double abseta = std::abs(d.Muon[i_Muon].eta);
                                                       if      (abseta>=2.4) return 0;
                                                       else if (abseta>=2.1) return 1;
                                                       else                  return 2; 
                                                    }, .axis_title="#eta_{#mu}", .def_range={1,3, 1}});
  // impact parameters - simple pick
  // ip      - brown 418;
  sh.AddNewFillParams("eleip_loose",             { .nbin=6, .bins={0,6}, .fill=[&d] {
                                                      if      (std::abs(d.Electron[i_Electron].dz) >=0.50) return 0;
                                                      else if (std::abs(d.Electron[i_Electron].dxy)>=0.20) return 1;
                                                      else if (std::abs(d.Electron[i_Electron].dz) >=0.10) return 2;
                                                      else if (std::abs(d.Electron[i_Electron].dxy)>=0.05) return 3;
                                                      else if (d.Electron[i_Electron].sip3d>=4)            return 4;
                                                      else                                                 return 5; 
                                                    }, .axis_title="vtx. d_{xy,e}/d_{z,e}", .def_range={2,6, 418}});
  sh.AddNewFillParams("eleip_medium",            { .nbin=6, .bins={0,6}, .fill=[&d] {
                                                      if      (std::abs(d.Electron[i_Electron].dz) >=0.50) return 0;
                                                      else if (std::abs(d.Electron[i_Electron].dxy)>=0.20) return 1;
                                                      else if (std::abs(d.Electron[i_Electron].dz) >=0.10) return 2;
                                                      else if (std::abs(d.Electron[i_Electron].dxy)>=0.05) return 3;
                                                      else if (d.Electron[i_Electron].sip3d>=4)            return 4;
                                                      else                                                 return 5;
                                                    }, .axis_title="vtx. d_{xy,e}/d_{z,e}", .def_range={4,6, 418}});
  sh.AddNewFillParams("eleip_tight",             { .nbin=6, .bins={0,6}, .fill=[&d] {
                                                      if      (std::abs(d.Electron[i_Electron].dz) >=0.50) return 0;
                                                      else if (std::abs(d.Electron[i_Electron].dxy)>=0.20) return 1;
                                                      else if (std::abs(d.Electron[i_Electron].dz) >=0.10) return 2;
                                                      else if (std::abs(d.Electron[i_Electron].dxy)>=0.05) return 3;
                                                      else if (d.Electron[i_Electron].sip3d>=4)            return 4;
                                                      else                                                 return 5;
                                                    }, .axis_title="vtx. d_{xy,e}/d_{z,e}", .def_range={5,6, 418}});
  sh.AddNewFillParams("muip_loose",              { .nbin=6, .bins={0,6}, .fill=[&d] {
                                                      if      (std::abs(d.Muon[i_Muon].dz) >=0.50) return 0;
                                                      else if (std::abs(d.Muon[i_Muon].dxy)>=0.20) return 1;
                                                      else if (std::abs(d.Muon[i_Muon].dz) >=0.10) return 2;
                                                      else if (std::abs(d.Muon[i_Muon].dxy)>=0.05) return 3;
                                                      else if (d.Muon[i_Muon].sip3d>=4)            return 4;
                                                      else                                         return 5;
                                                    }, .axis_title="vtx. d_{xy,#mu}/d_{z,#mu}", .def_range={2,6, 418}});
  sh.AddNewFillParams("muip_medium",             { .nbin=6, .bins={0,6}, .fill=[&d] {
                                                      if      (std::abs(d.Muon[i_Muon].dz) >=0.50) return 0;
                                                      else if (std::abs(d.Muon[i_Muon].dxy)>=0.20) return 1;
                                                      else if (std::abs(d.Muon[i_Muon].dz) >=0.10) return 2;
                                                      else if (std::abs(d.Muon[i_Muon].dxy)>=0.05) return 3;
                                                      else if (d.Muon[i_Muon].sip3d>=4)            return 4;
                                                      else                                         return 5;
                                                    }, .axis_title="vtx. d_{xy,#mu}/d_{z,#mu}", .def_range={4,6, 418}});
  sh.AddNewFillParams("muip_tight",              { .nbin=6, .bins={0,6}, .fill=[&d] {
                                                      if      (std::abs(d.Muon[i_Muon].dz) >=0.50) return 0;
                                                      else if (std::abs(d.Muon[i_Muon].dxy)>=0.20) return 1;
                                                      else if (std::abs(d.Muon[i_Muon].dz) >=0.10) return 2;
                                                      else if (std::abs(d.Muon[i_Muon].dxy)>=0.05) return 3;
                                                      else if (d.Muon[i_Muon].sip3d>=4)            return 4;
                                                      else                                         return 5;
                                                    }, .axis_title="vtx. d_{xy,#mu}/d_{z,#mu}", .def_range={5,6, 418}});
  // isolations - mini iso recommended, but we can cross-check others
  // pfiso   - yellow 402;
  // miniiso - orange 801;
  sh.AddNewFillParams("elepfiso_comp",           { .nbin=6, .bins={-1,5}, .fill=[&d] { 
                                                      // https://twiki.cern.ch/twiki/bin/view/CMS/CutBasedElectronIdentificationRun2#Offline_selection_criteria_for_V
                                                      float pt = d.Electron[i_Electron].pt, pfiso = d.Electron[i_Electron].pfRelIso03_all;
                                                      if (std::abs(d.Electron[i_Electron].eta+d.Electron[i_Electron].deltaEtaSC)<=1.479) {
                                                        if      (pfiso>=0.1980+0.506/pt) return 0;
                                                        else if (pfiso>=0.1120+0.506/pt) return 1;
                                                        else if (pfiso>=0.0478+0.506/pt) return 2;
                                                        else if (pfiso>=0.0287+0.506/pt) return 3;
                                                        else                             return 4;
                                                      } else {
                                                        if      (pfiso>=0.2030+0.963/pt) return 0;
                                                        else if (pfiso>=0.1080+0.963/pt) return 1;
                                                        else if (pfiso>=0.0658+0.963/pt) return 2;
                                                        else if (pfiso>=0.0445+0.963/pt) return 3;
                                                        else                             return 4;
                                                      } }, .axis_title="PF iso.", .def_range={0,5, 402}});
  sh.AddNewFillParams("eleminiiso_comp",         { .nbin=6, .bins={-1,5}, .fill=[&d] {
                                                      float miniIso = d.Electron[i_Electron].miniPFRelIso_all;
                                                      if      (miniIso>=0.40) return 0;
                                                      else if (miniIso>=0.20) return 1;
                                                      else if (miniIso>=0.10) return 2;
                                                      else if (miniIso>=0.05) return 3;
                                                      else                    return 4;
                                                    }, .axis_title="Mini iso.", .def_range={0,5, 801}});
  sh.AddNewFillParams("eleminiiso_loose",        { .nbin=6, .bins={-1,5}, .fill=[&d] {
                                                      float miniIso = d.Electron[i_Electron].miniPFRelIso_all;
                                                      if      (miniIso>=0.40) return 0;
                                                      else if (miniIso>=0.20) return 1;
                                                      else if (miniIso>=0.10) return 2;
                                                      else if (miniIso>=0.05) return 3;
                                                      else                    return 4;
                                                    }, .axis_title="Mini iso.", .def_range={1,5, 801}});
  sh.AddNewFillParams("eleminiiso_tight",        { .nbin=6, .bins={-1,5}, .fill=[&d] {
                                                      float miniIso = d.Electron[i_Electron].miniPFRelIso_all;
                                                      if      (miniIso>=0.40) return 0;
                                                      else if (miniIso>=0.20) return 1;
                                                      else if (miniIso>=0.10) return 2;
                                                      else if (miniIso>=0.05) return 3;
                                                      else                    return 4;
                                                    }, .axis_title="Mini iso.", .def_range={3,5, 402}});
  sh.AddNewFillParams("mupfiso_comp",            { .nbin=8, .bins={-1,7}, .fill=[&d] { return d.Muon[i_Muon].pfIsoId; }, .axis_title="#mu PF iso.", .def_range={0,7}}); 
  //sh.AddNewFillParams("mumultiiso_comp",         { .nbin=4, .bins={-1,3}, .fill=[&d] { return d.Muon[i_Muon].multiIsoId; }, .axis_title="#mu Multi iso.", .def_range={0,7}});// currently unavailable
  sh.AddNewFillParams("muminiiso_comp",          { .nbin=6, .bins={-1,5}, .fill=[&d] {
                                                      float miniIso = d.Muon[i_Muon].miniPFRelIso_all;
                                                      if      (miniIso>=0.40) return 0;
                                                      else if (miniIso>=0.20) return 1;
                                                      else if (miniIso>=0.10) return 2;
                                                      else if (miniIso>=0.05) return 3;
                                                      else                    return 4;
                                                    }, .axis_title="Mini iso.", .def_range={0,5, 801}});
  sh.AddNewFillParams("muminiiso_loose",         { .nbin=6, .bins={-1,5}, .fill=[&d] {
                                                      float miniIso = d.Muon[i_Muon].miniPFRelIso_all;
                                                      if      (miniIso>=0.40) return 0;
                                                      else if (miniIso>=0.20) return 1;
                                                      else if (miniIso>=0.10) return 2;
                                                      else if (miniIso>=0.05) return 3;
                                                      else                    return 4;
                                                    }, .axis_title="Mini iso.", .def_range={1,5, 801}});
  sh.AddNewFillParams("muminiiso_tight",         { .nbin=6, .bins={-1,5}, .fill=[&d] {
                                                      float miniIso = d.Muon[i_Muon].miniPFRelIso_all;
                                                      if      (miniIso>=0.40) return 0;
                                                      else if (miniIso>=0.20) return 1;
                                                      else if (miniIso>=0.10) return 2;
                                                      else if (miniIso>=0.05) return 3;
                                                      else                    return 4;
                                                    }, .axis_title="Mini iso.", .def_range={2,5, 801}});
  // id with/without isolation
  // id      - cyan to red 434,601,618,633;
  sh.AddNewFillParams("eleid_cut_iso_comp",      { .nbin=6, .bins={-1,5}, .fill=[&d] { return d.Electron[i_Electron].cutBased; }, .axis_title="Cut-based ID", .def_range={0,5, 601}});
  sh.AddNewFillParams("eleid_cut_iso_veto",      { .nbin=6, .bins={-1,5}, .fill=[&d] { return d.Electron[i_Electron].cutBased; }, .axis_title="Cut-based ID", .def_range={1,5, 601}});
  sh.AddNewFillParams("eleid_cut_iso_loose",     { .nbin=6, .bins={-1,5}, .fill=[&d] { return d.Electron[i_Electron].cutBased; }, .axis_title="Cut-based ID", .def_range={2,5, 601}});
  sh.AddNewFillParams("eleid_cut_iso_medium",    { .nbin=6, .bins={-1,5}, .fill=[&d] { return d.Electron[i_Electron].cutBased; }, .axis_title="Cut-based ID", .def_range={3,5, 601}});
  sh.AddNewFillParams("eleid_cut_iso_tight",     { .nbin=6, .bins={-1,5}, .fill=[&d] { return d.Electron[i_Electron].cutBased; }, .axis_title="Cut-based ID", .def_range={4,5, 601}});
  sh.AddNewFillParams("eleid_mva_comp",          { .nbin=5, .bins={-1,4}, .fill=[&d] {
                                                      if (!d.Electron[i_Electron].mvaFall17V2noIso_WPL)  return 0;
                                                      if (!d.Electron[i_Electron].mvaFall17V2noIso_WP90) return 1;
                                                      if (!d.Electron[i_Electron].mvaFall17V2noIso_WP80) return 2;
                                                      else                                               return 3;
                                                    }, .axis_title="MVA ID (no iso.)", .def_range={0,4, 633}});
  sh.AddNewFillParams("eleid_mva_loose",         { .nbin=5, .bins={-1,4}, .fill=[&d] {
                                                      if (!d.Electron[i_Electron].mvaFall17V2noIso_WPL)  return 0;
                                                      if (!d.Electron[i_Electron].mvaFall17V2noIso_WP90) return 1;
                                                      if (!d.Electron[i_Electron].mvaFall17V2noIso_WP80) return 2;
                                                      else                                               return 3;
                                                    }, .axis_title="MVA ID (no iso.)", .def_range={1,4, 633}});
  sh.AddNewFillParams("eleid_mva_medium",        { .nbin=5, .bins={-1,4}, .fill=[&d] {
                                                      if (!d.Electron[i_Electron].mvaFall17V2noIso_WPL)  return 0;
                                                      if (!d.Electron[i_Electron].mvaFall17V2noIso_WP90) return 1;
                                                      if (!d.Electron[i_Electron].mvaFall17V2noIso_WP80) return 2;
                                                      else                                               return 3;
                                                    }, .axis_title="MVA ID (no iso.)", .def_range={2,4, 633}});
  sh.AddNewFillParams("eleid_mva_tight",         { .nbin=5, .bins={-1,4}, .fill=[&d] {
                                                      if (!d.Electron[i_Electron].mvaFall17V2noIso_WPL)  return 0;
                                                      if (!d.Electron[i_Electron].mvaFall17V2noIso_WP90) return 1;
                                                      if (!d.Electron[i_Electron].mvaFall17V2noIso_WP80) return 2;
                                                      else                                               return 3;
                                                    }, .axis_title="MVA ID (no iso.)", .def_range={3,4, 633}});
  sh.AddNewFillParams("eleid_mva_iso_comp",      { .nbin=5, .bins={-1,4}, .fill=[&d] {
                                                      if (!d.Electron[i_Electron].mvaFall17V2Iso_WPL)  return 0;
                                                      if (!d.Electron[i_Electron].mvaFall17V2Iso_WP90) return 1;
                                                      if (!d.Electron[i_Electron].mvaFall17V2Iso_WP80) return 2;
                                                      else                                             return 3;
                                                    }, .axis_title="MVA ID (w/ iso.)", .def_range={0,4, 618}});
  sh.AddNewFillParams("eleid_mva_iso_loose",     { .nbin=5, .bins={-1,4}, .fill=[&d] {
                                                      if (!d.Electron[i_Electron].mvaFall17V2Iso_WPL)  return 0;
                                                      if (!d.Electron[i_Electron].mvaFall17V2Iso_WP90) return 1;
                                                      if (!d.Electron[i_Electron].mvaFall17V2Iso_WP80) return 2;
                                                      else                                             return 3;
                                                    }, .axis_title="MVA ID (w/ iso.)", .def_range={1,4, 618}});
  sh.AddNewFillParams("eleid_mva_iso_medium",    { .nbin=5, .bins={-1,4}, .fill=[&d] {
                                                      if (!d.Electron[i_Electron].mvaFall17V2Iso_WPL)  return 0;
                                                      if (!d.Electron[i_Electron].mvaFall17V2Iso_WP90) return 1;
                                                      if (!d.Electron[i_Electron].mvaFall17V2Iso_WP80) return 2;
                                                      else                                             return 3;
                                                    }, .axis_title="MVA ID (w/ iso.)", .def_range={2,4, 618}});
  sh.AddNewFillParams("eleid_mva_iso_tight",     { .nbin=5, .bins={-1,4}, .fill=[&d] {
                                                      if (!d.Electron[i_Electron].mvaFall17V2Iso_WPL)  return 0;
                                                      if (!d.Electron[i_Electron].mvaFall17V2Iso_WP90) return 1;
                                                      if (!d.Electron[i_Electron].mvaFall17V2Iso_WP80) return 2;
                                                      else                                             return 3;
                                                    }, .axis_title="MVA ID (w/ iso.)", .def_range={3,4, 618}});
  sh.AddNewFillParams("eleid_mva_miniiso_comp",  { .nbin=9, .bins={-1,8}, .fill=[&d] {
                                                      float miniIso = d.Electron[i_Electron].miniPFRelIso_all;
                                                      if (!d.Electron[i_Electron].mvaFall17V2noIso_WPL)       return 0;
                                                      else if (miniIso>=0.40)                                 return 1;
                                                      else if (!d.Electron[i_Electron].mvaFall17V2noIso_WP90) return 2;
                                                      else if (miniIso>=0.20)                                 return 3;
                                                      else if (miniIso>=0.10)                                 return 4;
                                                      else if (!d.Electron[i_Electron].mvaFall17V2noIso_WP80) return 5;
                                                      else if (miniIso>=0.05)                                 return 6;
                                                      else                                                    return 7;
                                                    }, .axis_title="MVA ID (w/ Mini iso.)", .def_range={0,8, 633}});
  sh.AddNewFillParams("eleid_mva_miniiso_loose", { .nbin=9, .bins={-1,8}, .fill=[&d] {
                                                      float miniIso = d.Electron[i_Electron].miniPFRelIso_all;
                                                      if (!d.Electron[i_Electron].mvaFall17V2noIso_WPL)       return 0;
                                                      else if (miniIso>=0.40)                                 return 1;
                                                      else if (!d.Electron[i_Electron].mvaFall17V2noIso_WP90) return 2;
                                                      else if (miniIso>=0.20)                                 return 3;
                                                      else if (miniIso>=0.10)                                 return 4;
                                                      else if (!d.Electron[i_Electron].mvaFall17V2noIso_WP80) return 5;
                                                      else if (miniIso>=0.05)                                 return 6;
                                                      else                                                    return 7;
                                                    }, .axis_title="MVA ID (w/ Mini iso.)", .def_range={2,8, 633}});
  sh.AddNewFillParams("muid_soft_comp",          { .nbin=3, .bins={-1,2}, .fill=[&d] { return d.Muon[i_Muon].softId; }, .axis_title="Soft ID", .def_range={0,2, 434}});
  sh.AddNewFillParams("muid_soft",               { .nbin=3, .bins={-1,2}, .fill=[&d] { return d.Muon[i_Muon].softId; }, .axis_title="Soft ID", .def_range={1,2, 434}});
  sh.AddNewFillParams("muid_medium_comp",        { .nbin=4, .bins={-1,3}, .fill=[&d] { 
                                                      if      (!d.Muon[i_Muon].mediumId)       return 0;
                                                      else if (!d.Muon[i_Muon].mediumPromptId) return 1;
                                                      else                                     return 2;
                                                    }, .axis_title="Medium ID", .def_range={0,3, 601}});
  sh.AddNewFillParams("muid_medium",             { .nbin=4, .bins={-1,3}, .fill=[&d] { 
                                                      if      (!d.Muon[i_Muon].mediumId)       return 0;
                                                      else if (!d.Muon[i_Muon].mediumPromptId) return 1;
                                                      else                                     return 2;
                                                    }, .axis_title="Medium ID", .def_range={1,3, 601}});
  sh.AddNewFillParams("muid_tight_comp",         { .nbin=3, .bins={-1,2}, .fill=[&d] { return d.Muon[i_Muon].tightId; }, .axis_title="Tight ID", .def_range={0,2, 618}});
  sh.AddNewFillParams("muid_tight",              { .nbin=3, .bins={-1,2}, .fill=[&d] { return d.Muon[i_Muon].tightId; }, .axis_title="Tight ID", .def_range={1,2, 618}});
  sh.AddNewFillParams("muid_mva_comp",           { .nbin=5, .bins={-1,4}, .fill=[&d] { return d.Muon[i_Muon].mvaId; }, .axis_title="MVA ID", .def_range={0,4, 633}});
  sh.AddNewFillParams("muid_mva_loose",          { .nbin=5, .bins={-1,4}, .fill=[&d] { return d.Muon[i_Muon].mvaId; }, .axis_title="MVA ID", .def_range={1,4, 633}});
  sh.AddNewFillParams("muid_mva_medium",         { .nbin=5, .bins={-1,4}, .fill=[&d] { return d.Muon[i_Muon].mvaId; }, .axis_title="MVA ID", .def_range={2,4, 633}});
  sh.AddNewFillParams("muid_mva_tight",          { .nbin=5, .bins={-1,4}, .fill=[&d] { return d.Muon[i_Muon].mvaId; }, .axis_title="MVA ID", .def_range={3,4, 633}});
  // Rest of the muon IDs don't work currently or not available for 2017
  // softMva   - 2018
  // softMvaId - 0
  // looseId   - 2018
  // mvaLowPt  - bugged
  // mvaTTH    - Not ID, but TTH vs HH discriminator

  // Photons
  sh.AddNewFillParams("PhotonPt",        { .nbin=  25, .bins={     0,   2000}, .fill=[&d] { return nPhotonSelect<1 ? -9999 : d.Photon[i_Photon].pt;  }, .axis_title="Photon p_{T} (GeV)", .def_range={PHOTON_SELECT_PT_CUT,1000}});
  sh.AddNewFillParams("PhotonEta",       { .nbin=  40, .bins={    -4,      4}, .fill=[&d] { return nPhotonSelect<1 ? -9999 : d.Photon[i_Photon].eta; }, .axis_title="Photon #eta",        .def_range={-PHOTON_SELECT_ETA_CUT,PHOTON_SELECT_PT_CUT}});
  sh.AddNewFillParams("PhotonSIEIE",     { .nbin= 100, .bins={     0,    0.1}, .fill=[&d] { return d.Photon[i_Photon].sieie;        }, .axis_title="Photon #sigma_{i#eta i#eta}", .def_range={0,0.1}});
  sh.AddNewFillParams("PhotonCHIso",     { .nbin=  40, .bins={     0,     20}, .fill=[&d] { return d.Photon[i_Photon].pfRelIso03_chg;     }, .axis_title="Photon Charged Isolation (GeV)", .def_range={0,10}});
  sh.AddNewFillParams("Photon1Eta",      { .nbin=  25, .bins={  -2.5,    2.5}, .fill=[&d] { return nPhotonSelect<1 ? -9999 : d.Photon[iPhotonSelect[0]].eta; }, .axis_title="Photon #eta"});

  // AK4 Jets
  sh.AddNewFillParams("JetPtBins",            { .nbin=Pt.size()-1,   .bins=Pt,      .fill=[&d] { return d.Jet[i_Jet].pt;           }, .axis_title="Jet p_{T} (GeV)", .def_range={200,2000} });
  sh.AddNewFillParams("JetPtFewBins",         { .nbin=PtF.size()-1,  .bins=PtF,     .fill=[&d] { return d.Jet[i_Jet].pt;           }, .axis_title="Jet p_{T} (GeV)", .def_range={200,2000} });
  sh.AddNewFillParams("JetPtOneBin",          { .nbin=PtO.size()-1,  .bins=PtO,     .fill=[&d] { return d.Jet[i_Jet].pt;           }, .axis_title="Jet p_{T} (GeV)", .def_range={400,2000} });
  sh.AddNewFillParams("JetPt",                { .nbin=  80, .bins={     0,   4000}, .fill=[&d] { return d.Jet[i_Jet].pt;           }, .axis_title="Jet p_{T} (GeV)", .def_range={0,2000} });
  sh.AddNewFillParams("JetEta",               { .nbin=  40, .bins={    -4,      4}, .fill=[&d] { return d.Jet[i_Jet].eta;          }, .axis_title="Jet #eta",        .def_range={-2.4,2.4}});
  sh.AddNewFillParams("JetPhi",               { .nbin=  16, .bins={-3.142,  3.142}, .fill=[&d] { return d.Jet[i_Jet].phi;          }, .axis_title="Jet #phi"});
  sh.AddNewFillParams("JetCSV",               { .nbin=  20, .bins={     0,   1.00}, .fill=[&d] { return std::min(d.Jet[i_Jet].btagDeepB,float(0.999)); }, .axis_title="Jet CSV"});
  sh.AddNewFillParams("JetPhotonDR",          { .nbin= 120, .bins={     0,      6}, .fill=[] { return AK4_photonDR[i_Jet];           }, .axis_title="#DeltaR (jet, photon)", .def_range={0,0.8}});
  sh.AddNewFillParams("JetPhotonPtRatio",     { .nbin=  40, .bins={     0,      4}, .fill=[] { return AK4_photonPtRatio[i_Jet];      }, .axis_title="p_{T}^{photon}/p_{T}^{jet}", .def_range={0,2}});
  sh.AddNewFillParams("JetEleDR",             { .nbin= 120, .bins={     0,      6}, .fill=[] { return AK4_eleDR[i_Jet];              }, .axis_title="#DeltaR (jet, electron)", .def_range={0,0.8}});
  sh.AddNewFillParams("JetElePtRatio",        { .nbin=  40, .bins={     0,      4}, .fill=[] { return AK4_elePtRatio[i_Jet];         }, .axis_title="p_{T}^{electron}/p_{T}^{jet}", .def_range={0,2}});
  sh.AddNewFillParams("JetMuonDR",            { .nbin= 120, .bins={     0,      6}, .fill=[] { return AK4_muonDR[i_Jet];             }, .axis_title="#DeltaR (jet, muon)", .def_range={0,0.8}});
  sh.AddNewFillParams("JetMuonPtRatio",       { .nbin=  40, .bins={     0,      4}, .fill=[] { return AK4_muonPtRatio[i_Jet];        }, .axis_title="p_{T}^{muon}/p_{T}^{jet}", .def_range={0,2}});
  // BJets
  sh.AddNewFillParams("BJetPtBins",           { .nbin=Pt.size()-1,   .bins=Pt,      .fill=[&d] { return d.Jet[i_Jet].pt;           }, .axis_title="B-jet p_{T} (GeV)", .def_range={0,2000} });
  sh.AddNewFillParams("BJetPt",               { .nbin=  80, .bins={     0,   4000}, .fill=[&d] { return d.Jet[i_Jet].pt;           }, .axis_title="B-jet p_{T} (GeV)", .def_range={0,2000} });
  sh.AddNewFillParams("BJetEta",              { .nbin=  40, .bins={    -4,      4}, .fill=[&d] { return d.Jet[i_Jet].eta;          }, .axis_title="B-jet #eta",        .def_range={-2.4,2.4}});
  sh.AddNewFillParams("BJetPhi",              { .nbin=  16, .bins={-3.142,  3.142}, .fill=[&d] { return d.Jet[i_Jet].phi;          }, .axis_title="B-jet #phi"});
  sh.AddNewFillParams("BJetCSV",              { .nbin=  20, .bins={     0,   1.00}, .fill=[&d] { return std::min(d.Jet[i_Jet].btagDeepB,float(0.999)); }, .axis_title="B-jet CSV"});

  // AK8 Jets
  //sh.AddNewFillParams("JetAK8PtOneBin",       { .nbin=   1, .bins={   200,   5000}, .fill=[&d] { return d.FatJet[i_FatJet].pt;           }, .axis_title="AK8 jet p_{T} (GeV)"});
  sh.AddNewFillParams("JetAK8PtOneBin",       { .nbin=PtO.size()-1,  .bins=PtO,     .fill=[&d] { return d.FatJet[i_FatJet].pt;           }, .axis_title="AK8 Jet p_{T} (GeV)", .def_range={400,2000} });
  sh.AddNewFillParams("JetAK8PtFewBins",      { .nbin=PtF.size()-1, .bins=PtF,      .fill=[&d] { return d.FatJet[i_FatJet].pt;           }, .axis_title="AK8 jet p_{T} (GeV)", .def_range={200+TOP*200,2000} });
  sh.AddNewFillParams("JetAK8PtBins",         { .nbin=Pt.size()-1 , .bins=Pt,       .fill=[&d] { return d.FatJet[i_FatJet].pt;           }, .axis_title="AK8 jet p_{T} (GeV)", .def_range={200+TOP*200,2000} });
  sh.AddNewFillParams("JetAK8Pt",             { .nbin=  80, .bins={     0,   4000}, .fill=[&d] { return d.FatJet[i_FatJet].pt;           }, .axis_title="AK8 jet p_{T} (GeV)", .def_range={200+TOP*200,2000} });
  sh.AddNewFillParams("JetAK8Eta",            { .nbin=  40, .bins={    -4,      4}, .fill=[&d] { return d.FatJet[i_FatJet].eta;          }, .axis_title="AK8 jet #eta",        .def_range={-2.4,2.4}});
  sh.AddNewFillParams("JetAK8Phi",            { .nbin=  16, .bins={-3.142,  3.142}, .fill=[&d] { return d.FatJet[i_FatJet].phi;          }, .axis_title="AK8 jet #phi"});
  sh.AddNewFillParams("JetAK8Mass",           { .nbin= M2.size()-1, .bins=M2,       .fill=[] { return softDropMassW[i_FatJet];          }, .axis_title="AK8 jet soft-drop mass (GeV)", .def_range={0,400}});
  sh.AddNewFillParams("JetAK8MassTop",        { .nbin= M2.size()-1, .bins=M2,       .fill=[] { return softDropMassTop[i_FatJet];        }, .axis_title="AK8 jet soft-drop mass (GeV)", .def_range={0,400}});
  sh.AddNewFillParams("JetAK8Tau1",           { .nbin=  50, .bins={     0,      1}, .fill=[&d] { return std::min(d.FatJet[i_FatJet].tau1, float(0.999));    }, .axis_title="AK8 jet #tau_{1}"});
  sh.AddNewFillParams("JetAK8Tau2",           { .nbin=  50, .bins={     0,      1}, .fill=[&d] { return std::min(d.FatJet[i_FatJet].tau2, float(0.999));    }, .axis_title="AK8 jet #tau_{2}"});
  sh.AddNewFillParams("JetAK8Tau3",           { .nbin=  50, .bins={     0,      1}, .fill=[&d] { return std::min(d.FatJet[i_FatJet].tau3, float(0.999));    }, .axis_title="AK8 jet #tau_{3}"});
  sh.AddNewFillParams("JetAK8Index",          { .nbin=  10, .bins={     0,     10}, .fill=[]   { return i_FatJet;                       }, .axis_title="AK8 Jet index", .def_range={0,5} });
  sh.AddNewFillParams("MaxAK8SubJetCSV",      { .nbin=  20, .bins={     0,   1.00}, .fill=[] { return std::min(AK8_maxSubJetCSV[i_FatJet], double(0.999));      }, .axis_title="Max. AK8 subjet CSV"});
  sh.AddNewFillParams("MaxAK8SubJetCSVBins",  { .nbin=CSV.size()-1, .bins=CSV,      .fill=[] { return std::min(AK8_maxSubJetCSV[i_FatJet], double(0.999));      }, .axis_title="Max. AK8 subjet CSV"});
  sh.AddNewFillParams("JetAK8Tau21",          { .nbin=  20, .bins={     0,      1}, .fill=[] { return std::min(tau21[i_FatJet], double(0.999));                       }, .axis_title="AK8 jet #tau_{2}/#tau_{1}"});
  sh.AddNewFillParams("JetAK8Tau31",          { .nbin=  20, .bins={     0,      1}, .fill=[] { return std::min(tau31[i_FatJet], double(0.999));                       }, .axis_title="AK8 jet #tau_{3}/#tau_{1}"});
  sh.AddNewFillParams("JetAK8Tau32",          { .nbin=  20, .bins={     0,      1}, .fill=[] { return std::min(tau32[i_FatJet], double(0.999));                       }, .axis_title="AK8 jet #tau_{3}/#tau_{2}"});
  sh.AddNewFillParams("JetAK8PhotonDR",       { .nbin= 120, .bins={     0,      6}, .fill=[] { return AK8_photonDR[i_FatJet];           }, .axis_title="#DeltaR (AK8 jet, photon)", .def_range={0,1.6}});
  sh.AddNewFillParams("JetAK8PhotonPtRatio",  { .nbin=  40, .bins={     0,      4}, .fill=[] { return AK8_photonPtRatio[i_FatJet];      }, .axis_title="p_{T}^{photon}/p_{T}^{AK8 jet}", .def_range={0,2}});
  sh.AddNewFillParams("JetAK8EleDR",          { .nbin= 120, .bins={     0,      6}, .fill=[] { return AK8_eleDR[i_FatJet];              }, .axis_title="#DeltaR (AK8 jet, ele)", .def_range={0,1.6}});
  sh.AddNewFillParams("JetAK8ElePtRatio",     { .nbin=  40, .bins={     0,      4}, .fill=[] { return AK8_elePtRatio[i_FatJet];         }, .axis_title="p_{T}^{ele}/p_{T}^{AK8 jet}", .def_range={0,2}});
  sh.AddNewFillParams("JetAK8MuonDR",         { .nbin= 120, .bins={     0,      6}, .fill=[] { return AK8_muonDR[i_FatJet];             }, .axis_title="#DeltaR (AK8 jet, muon)", .def_range={0,1.6}});
  sh.AddNewFillParams("JetAK8MuonPtRatio",    { .nbin=  40, .bins={     0,      4}, .fill=[] { return AK8_muonPtRatio[i_FatJet];        }, .axis_title="p_{T}^{muon}/p_{T}^{AK8 jet}", .def_range={0,2}});
  sh.AddNewFillParams("JetAK8DeepTagWvsQCD",  { .nbin=  20, .bins={     0,      1}, .fill=[&d] { return d.FatJet[i_FatJet].deepTagMD_WvsQCD; }, .axis_title="AK8 jet DeepTagMD (W vs. QCD)"});
  sh.AddNewFillParams("JetAK8DeepTagTvsQCD",  { .nbin=  20, .bins={     0,      1}, .fill=[&d] { return d.FatJet[i_FatJet].deepTagMD_TvsQCD; }, .axis_title="AK8 jet DeepTagMD (t vs. QCD)"});
  // mWs
  sh.AddNewFillParams("mWPtBins",        { .nbin=Pt.size()-1 , .bins=Pt,       .fill=[&d] { return d.FatJet[i_FatJet].pt;           }, .axis_title="Mass-tagged W p_{T} (GeV)", .def_range={0,2000} });
  sh.AddNewFillParams("mWPt",            { .nbin= 80, .bins={     0,   4000}, .fill=[&d] { return d.FatJet[i_FatJet].pt;           }, .axis_title="Mass-tagged W p_{T} (GeV)", .def_range={0,2000} });
  sh.AddNewFillParams("mWEta",           { .nbin=  40, .bins={    -4,      4}, .fill=[&d] { return d.FatJet[i_FatJet].eta;          }, .axis_title="Mass-tagged W #eta",        .def_range={-2.4,2.4}});
  sh.AddNewFillParams("mWPhi",           { .nbin=  16, .bins={-3.142,  3.142}, .fill=[&d] { return d.FatJet[i_FatJet].phi;          }, .axis_title="Mass-tagged W #phi"});
  sh.AddNewFillParams("mWTau21",         { .nbin=  20, .bins={     0,      1}, .fill=[] { return tau21[i_FatJet];                  }, .axis_title="Mass-tagged W #tau_{2}/#tau_{1}"});
  sh.AddNewFillParams("mWMass",          { .nbin=M.size()-1, .bins=M,          .fill=[] { return softDropMassW[i_FatJet];          }, .axis_title="Mass-tagged W m_{Soft-Drop} (GeV)"});
  sh.AddNewFillParams("mWDeepTagWvsQCD", { .nbin=  20, .bins={     0,      1}, .fill=[&d] { return d.FatJet[i_FatJet].deepTagMD_WvsQCD; }, .axis_title="Mass-tagged W DeepTagMD (W vs. QCD)"});
  // aWs
  sh.AddNewFillParams("aWPtBins",        { .nbin=Pt.size()-1 , .bins=Pt,       .fill=[&d] { return d.FatJet[i_FatJet].pt;           }, .axis_title="Anti-tagged W p_{T} (GeV)", .def_range={0,2000} });
  sh.AddNewFillParams("aWPt",            { .nbin=  80, .bins={     0,   4000}, .fill=[&d] { return d.FatJet[i_FatJet].pt;           }, .axis_title="Anti-tagged W p_{T} (GeV)", .def_range={0,2000} });
  sh.AddNewFillParams("aWEta",           { .nbin=  40, .bins={    -4,      4}, .fill=[&d] { return d.FatJet[i_FatJet].eta;          }, .axis_title="Anti-tagged W #eta",        .def_range={-2.4,2.4}});
  sh.AddNewFillParams("aWPhi",           { .nbin=  16, .bins={-3.142,  3.142}, .fill=[&d] { return d.FatJet[i_FatJet].phi;          }, .axis_title="Anti-tagged W #phi"});
  sh.AddNewFillParams("aWTau21",         { .nbin=  20, .bins={     0,      1}, .fill=[] { return tau21[i_FatJet];                  }, .axis_title="Anti-tagged W #tau_{2}/#tau_{1}"});
  sh.AddNewFillParams("aWMass",          { .nbin=M.size()-1, .bins=M,          .fill=[] { return softDropMassW[i_FatJet];          }, .axis_title="Anti-tagged W m_{Soft-Drop} (GeV)"});
  // Ws
  sh.AddNewFillParams("WPtBins",         { .nbin=Pt.size()-1, .bins=Pt,        .fill=[&d] { return d.FatJet[i_FatJet].pt;           }, .axis_title="Tagged W p_{T} (GeV)", .def_range={200,1200} });
  sh.AddNewFillParams("WPt",             { .nbin=  80, .bins={     0,   4000}, .fill=[&d] { return d.FatJet[i_FatJet].pt;           }, .axis_title="Tagged W p_{T} (GeV)", .def_range={200,1200} });
  sh.AddNewFillParams("WEta",            { .nbin=  40, .bins={    -4,      4}, .fill=[&d] { return d.FatJet[i_FatJet].eta;          }, .axis_title="Tagged W #eta",        .def_range={-2.4,2.4}});
  sh.AddNewFillParams("WPhi",            { .nbin=  16, .bins={-3.142,  3.142}, .fill=[&d] { return d.FatJet[i_FatJet].phi;          }, .axis_title="Tagged W #phi"});
  sh.AddNewFillParams("WTau21",          { .nbin=  20, .bins={     0,      1}, .fill=[]   { return tau21[i_FatJet];                  }, .axis_title="Tagged W #tau_{2}/#tau_{1}"});
  sh.AddNewFillParams("WMass",           { .nbin=M.size()-1, .bins=M,          .fill=[]   { return softDropMassW[i_FatJet];          }, .axis_title="Tagged W m_{Soft-Drop} (GeV)"});
  sh.AddNewFillParams("HadWIndex",       { .nbin=  10, .bins={     0,     10}, .fill=[]   { return itHadW[i_FatJet];                 }, .axis_title="W (had.) index", .def_range={0,5} });
  // Zs
  sh.AddNewFillParams("HadZIndex",       { .nbin=  10, .bins={     0,     10}, .fill=[]   { return itHadZ[i_FatJet];                 }, .axis_title="Z (had.) index", .def_range={0,5} });

  // mTops
  sh.AddNewFillParams("mTopPtBins",      { .nbin=Pt.size()-1 , .bins=Pt,       .fill=[&d] { return d.FatJet[i_FatJet].pt;           }, .axis_title="Mass-tagged top p_{T} (GeV)", .def_range={0,2000} });
  sh.AddNewFillParams("mTopPt",          { .nbin=  80, .bins={     0,   4000}, .fill=[&d] { return d.FatJet[i_FatJet].pt;           }, .axis_title="Mass-tagged top p_{T} (GeV)", .def_range={0,2000} });
  sh.AddNewFillParams("mTopEta",         { .nbin=  40, .bins={    -4,      4}, .fill=[&d] { return d.FatJet[i_FatJet].eta;          }, .axis_title="Mass-tagged top #eta",        .def_range={-2.4,2.4}});
  sh.AddNewFillParams("mTopPhi",         { .nbin=  16, .bins={-3.142,  3.142}, .fill=[&d] { return d.FatJet[i_FatJet].phi;          }, .axis_title="Mass-tagged top #phi"});
  sh.AddNewFillParams("mTopTau32",       { .nbin=  20, .bins={     0,      1}, .fill=[] { return tau32[i_FatJet];                  }, .axis_title="Mass-tagged top #tau_{3}/#tau_{2}"});
  sh.AddNewFillParams("mTopMass",        { .nbin=M.size()-1, .bins=M,          .fill=[] { return softDropMassTop[i_FatJet];        }, .axis_title="Mass-tagged top m_{Soft-Drop} (GeV)"});
  // aTops
  sh.AddNewFillParams("aTopPtBins",      { .nbin=Pt.size()-1 , .bins=Pt,       .fill=[&d] { return d.FatJet[i_FatJet].pt;           }, .axis_title="Anti-tagged top p_{T} (GeV)", .def_range={0,2000} });
  sh.AddNewFillParams("aTopPt",          { .nbin=  80, .bins={     0,   4000}, .fill=[&d] { return d.FatJet[i_FatJet].pt;           }, .axis_title="Anti-tagged top p_{T} (GeV)", .def_range={0,2000} });
  sh.AddNewFillParams("aTopEta",         { .nbin=  40, .bins={    -4,      4}, .fill=[&d] { return d.FatJet[i_FatJet].eta;          }, .axis_title="Anti-tagged top #eta",        .def_range={-2.4,2.4}});
  sh.AddNewFillParams("aTopPhi",         { .nbin=  16, .bins={-3.142,  3.142}, .fill=[&d] { return d.FatJet[i_FatJet].phi;          }, .axis_title="Anti-tagged top #phi"});
  sh.AddNewFillParams("aTopTau32",       { .nbin=  20, .bins={     0,      1}, .fill=[] { return tau32[i_FatJet];                  }, .axis_title="Anti-tagged top #tau_{3}/#tau_{2}"});
  sh.AddNewFillParams("aTopMass",        { .nbin=M.size()-1, .bins=M,          .fill=[] { return softDropMassTop[i_FatJet];        }, .axis_title="Anti-tagged top m_{Soft-Drop} (GeV)"});
  // Tops
  sh.AddNewFillParams("TopPtBins",       { .nbin=Pt.size()-1, .bins=Pt,        .fill=[&d] { return d.FatJet[i_FatJet].pt;           }, .axis_title="Tagged top p_{T} (GeV)", .def_range={400,1200} });
  sh.AddNewFillParams("TopPt",           { .nbin=  80, .bins={     0,   4000}, .fill=[&d] { return d.FatJet[i_FatJet].pt;           }, .axis_title="Tagged top p_{T} (GeV)", .def_range={400,1200} });
  sh.AddNewFillParams("TopEta",          { .nbin=  40, .bins={    -4,      4}, .fill=[&d] { return d.FatJet[i_FatJet].eta;          }, .axis_title="Tagged top #eta",        .def_range={-2.4,2.4}});
  sh.AddNewFillParams("TopPhi",          { .nbin=  16, .bins={-3.142,  3.142}, .fill=[&d] { return d.FatJet[i_FatJet].phi;          }, .axis_title="Tagged top #phi"});
  sh.AddNewFillParams("TopTau32",        { .nbin=  20, .bins={     0,      1}, .fill=[] { return tau32[i_FatJet];                  }, .axis_title="Tagged top #tau_{3}/#tau_{2}"});
  sh.AddNewFillParams("TopMass",         { .nbin=M.size()-1, .bins=M,          .fill=[] { return softDropMassTop[i_FatJet];        }, .axis_title="Tagged top m_{Soft-Drop} (GeV)"});
  sh.AddNewFillParams("HadTopIndex",     { .nbin=  10, .bins={     0,     10}, .fill=[]   { return itHadTop[i_FatJet];               }, .axis_title="Top (had.) index", .def_range={0,5} });
  sh.AddNewFillParams("LepTopIndex",     { .nbin=  10, .bins={     0,     10}, .fill=[]   { return itLepTop[i_FatJet];               }, .axis_title="Top (lep.) index", .def_range={0,5} });
  // Mass tag tops without subjet b veto
  sh.AddNewFillParams("MTopPtBins",      { .nbin=Pt.size()-1 , .bins=Pt,       .fill=[&d] { return d.FatJet[i_FatJet].pt;           }, .axis_title="Mass-tagged top p_{T} (GeV)", .def_range={0,2000} });
  sh.AddNewFillParams("MTopPt",          { .nbin=  80, .bins={     0,   4000}, .fill=[&d] { return d.FatJet[i_FatJet].pt;           }, .axis_title="Mass-tagged top p_{T} (GeV)", .def_range={0,2000} });
  sh.AddNewFillParams("MTopEta",         { .nbin=  40, .bins={    -4,      4}, .fill=[&d] { return d.FatJet[i_FatJet].eta;          }, .axis_title="Mass-tagged top #eta",        .def_range={-2.4,2.4}});
  sh.AddNewFillParams("MTopPhi",         { .nbin=  16, .bins={-3.142,  3.142}, .fill=[&d] { return d.FatJet[i_FatJet].phi;          }, .axis_title="Mass-tagged top #phi"});
  sh.AddNewFillParams("MTopTau32",       { .nbin=  20, .bins={     0,      1}, .fill=[] { return tau32[i_FatJet];                  }, .axis_title="Mass-tagged top #tau_{3}/#tau_{2}"});
  sh.AddNewFillParams("MTopMass",        { .nbin=M.size()-1, .bins=M,          .fill=[] { return softDropMassTop[i_FatJet];        }, .axis_title="Mass-tagged top m_{Soft-Drop} (GeV)"});
  sh.AddNewFillParams("MTopDeepTagTvsQCD", { .nbin=  20, .bins={     0,    1}, .fill=[&d] { return d.FatJet[i_FatJet].deepTagMD_TvsQCD; }, .axis_title="Mass-tagged top DeepTagMD (t vs. QCD)"});
  // Leptonic Jets
  sh.AddNewFillParams("LepJetPt",             { .nbin=  80, .bins={     0,   4000},  .fill=[&d] { return d.FatJet[i_FatJet].pt;                             }, .axis_title="Leptonic jet p_{T} (GeV)", .def_range={200+TOP*200,2000} });
  sh.AddNewFillParams("LepJetEta",            { .nbin=  40, .bins={    -4,      4},  .fill=[&d] { return d.FatJet[i_FatJet].eta;                            }, .axis_title="Leptonic jet #eta",        .def_range={-2.4,2.4}});
  sh.AddNewFillParams("LepJetPhi",            { .nbin=  16, .bins={-3.142,  3.142},  .fill=[&d] { return d.FatJet[i_FatJet].phi;                            }, .axis_title="Leptonic jet #phi"});
  sh.AddNewFillParams("LepJetMass",           { .nbin= M2.size()-1, .bins=M2,        .fill=[&d] { return d.FatJet[i_FatJet].msoftdrop;                      }, .axis_title="Leptonic jet soft-drop mass (GeV)", .def_range={0,400}});
  sh.AddNewFillParams("LepJetSubJetCSV",      { .nbin=  20, .bins={     0,   1.00},  .fill=[] { return std::min(AK8_maxSubJetCSV[i_FatJet], double(0.999)); }, .axis_title="Leptonic jet max. AK8 subjet CSV"});
  sh.AddNewFillParams("LepJetTau21",          { .nbin=  20, .bins={     0,      1},  .fill=[] { return std::min(tau21[i_FatJet], double(0.999));             }, .axis_title="Leptonic jet #tau_{2}/#tau_{1}"});
  sh.AddNewFillParams("LepJetLSF",            { .nbin=  20, .bins={     0,      1},  .fill=[] { return AK8_LSF[i_FatJet];                                   }, .axis_title="Lepton subjet fraction"});
  sh.AddNewFillParams("LepJetLSFNoIso",       { .nbin=  20, .bins={     0,      1},  .fill=[] { return AK8_LSF_NoIso[i_FatJet];                             }, .axis_title="Lepton subjet fraction (no iso.)"});
  sh.AddNewFillParams("LepJetNSubJet",        { .nbin=   3, .bins={  -0.5,    2.5},  .fill=[] { return AK8_nSubJet[i_FatJet];                               }, .axis_title="Leptonic jet N_{subjet}"});
  sh.AddNewFillParams("LepJetDRmin",          { .nbin=  60, .bins={     0,      6}, .fill=[] { return ak8MatchedTightNoIsoLepCleanJetDRmin[i_FatJet]; }, .axis_title="Lepton, jet #DeltaR_{min}"});
  sh.AddNewFillParams("LepJetPtrel",          { .nbin=  40, .bins={     0,    100}, .fill=[] { return ak8MatchedTightNoIsoLepCleanJetPtrel[i_FatJet]; }, .axis_title="Lepton, cleaned jet p_{T,rel} (GeV)"});
  // Leptonic Tops
  sh.AddNewFillParams("LepTopPt",             { .nbin=  80, .bins={     0,   4000},  .fill=[&d] { return d.FatJet[i_FatJet].pt;                             }, .axis_title="Leptonic top p_{T} (GeV)", .def_range={200+TOP*200,2000} });
  sh.AddNewFillParams("LepTopEta",            { .nbin=  40, .bins={    -4,      4},  .fill=[&d] { return d.FatJet[i_FatJet].eta;                            }, .axis_title="Leptonic top #eta",        .def_range={-2.4,2.4}});
  sh.AddNewFillParams("LepTopPhi",            { .nbin=  16, .bins={-3.142,  3.142},  .fill=[&d] { return d.FatJet[i_FatJet].phi;                            }, .axis_title="Leptonic top #phi"});
  sh.AddNewFillParams("LepTopMass",           { .nbin= M2.size()-1, .bins=M2,        .fill=[&d] { return d.FatJet[i_FatJet].msoftdrop;                      }, .axis_title="Leptonic top soft-drop mass (GeV)", .def_range={0,400}});
  sh.AddNewFillParams("LepTopSubJetCSV",      { .nbin=  20, .bins={     0,   1.00},  .fill=[] { return std::min(AK8_maxSubJetCSV[i_FatJet], double(0.999)); }, .axis_title="Leptonic top max. AK8 subjet CSV"});
  sh.AddNewFillParams("LepTopTau21",          { .nbin=  20, .bins={     0,      1}, .fill=[] { return std::min(tau21[i_FatJet], double(0.999));             }, .axis_title="Leptonic top #tau_{2}/#tau_{1}"});
  sh.AddNewFillParams("LepTopLSF",            { .nbin=  20, .bins={     0,      1},  .fill=[] { return AK8_LSF[i_FatJet];                                   }, .axis_title="Lepton subjet fraction"});
  sh.AddNewFillParams("LepTopLSFNoIso",       { .nbin=  20, .bins={     0,      1},  .fill=[] { return AK8_LSF_NoIso[i_FatJet];                             }, .axis_title="Lepton subjet fraction (no iso.)"});
  sh.AddNewFillParams("LepTopNSubJet",        { .nbin=   3, .bins={  -0.5,    2.5},  .fill=[] { return AK8_nSubJet[i_FatJet];                               }, .axis_title="Leptonic top N_{subjet}"});
  // GenTruth and cut bins for ROC Curves
  // Cuts not to be shown
  sh.AddNewFillParams("ak8pt400_nocomp",        { .nbin=1,  .bins={400,10000}, .fill=[&d] { return d.FatJet[i_FatJet].pt; }, .axis_title="p_{T}", .def_range={400,10000}});
  // pt/mass
  sh.AddNewFillParams("ak8pt400",               { .nbin=12, .bins={200,250,300,350,400,450,500,550,600,800,1000,2000,10000}, .fill=[&d] { return d.FatJet[i_FatJet].pt; }, .axis_title="p_{T}", .def_range={400,10000, 418}}); // Green
  sh.AddNewFillParams("ak8pt",                  { .nbin=12, .bins={200,250,300,350,400,450,500,550,600,800,1000,2000,10000}, .fill=[&d] { return d.FatJet[i_FatJet].pt; }, .axis_title="p_{T}", .def_range={400,10000, 418}}); // Green
  sh.AddNewFillParams("msoftdrop105",           { .nbin=13, .bins={-2, 0, 50, 105, 140, 175, 210, 250, 300, 350, 400, 600, 1000, 10000}, .fill=[&d] { return d.FatJet[i_FatJet].msoftdrop; }, .axis_title="m_{soft-drop}", .def_range={105,10000, 402}}); // Yellow
  sh.AddNewFillParams("msoftdrop0",             { .nbin=13, .bins={-2, 0, 50, 105, 140, 175, 210, 250, 300, 350, 400, 600, 1000, 10000}, .fill=[&d] { return d.FatJet[i_FatJet].msoftdrop; }, .axis_title="m_{soft-drop}", .def_range={0,10000, 402}}); // Yellow
  // Taggers
  sh.AddNewFillParams("tau32_softdrop_sjbtag_comp",  { .nbin=10, .bins={0, 0.40, 0.46, 0.54, 0.65, 0.8, 2, 3, 4, 5, 6}, .fill=[&d] { 
                                                          if (d.FatJet[i_FatJet].msoftdrop<HADTOP_SD_MASS_CUT_LOW)  return (double)4;
                                                          if (d.FatJet[i_FatJet].msoftdrop>=HADTOP_SD_MASS_CUT_HIGH) return (double)3;
                                                          if (!passSubJetBTag[i_FatJet]) return (double)2;
                                                          return tau32[i_FatJet];
                                                        }, .axis_title="#tau_{32}, m_{sd}, b_{sj}", .def_range={0,5, 434}}); // Cyan
  sh.AddNewFillParams("deepTagMD_top_comp",          { .nbin=7,  .bins={-20, -10, 0, 0.054, 0.391, 0.578, 0.843, 1.000}, .fill=[&d] { return d.FatJet[i_FatJet].deepTagMD_TvsQCD; }, .axis_title="deepTagMD", .def_range={-10,1.0, 601}}); // Blue
  sh.AddNewFillParams("deepTagMD_top_WP1",           { .nbin=7,  .bins={-20, 10, 0, 0.054, 0.391, 0.578, 0.843, 1.000}, .fill=[&d] { return d.FatJet[i_FatJet].deepTagMD_TvsQCD; }, .axis_title="deepTag (MD)", .def_range={0.391,1, 601}}); // Blue
  sh.AddNewFillParams("deepTagMD_top_minsd_comp",    { .nbin=8,  .bins={-20, -12,      -10, 0, 0.054, 0.391, 0.578, 0.843, 1.000}, .fill=[&d] { 
                                                          if (d.FatJet[i_FatJet].msoftdrop<HADTOP_SD_MASS_CUT_LOW)  return (double)-12;
                                                          //if (d.FatJet[i_FatJet].msoftdrop>=HADTOP_SD_MASS_CUT_HIGH) return (double)-11;
                                                          return (double)d.FatJet[i_FatJet].deepTagMD_TvsQCD; }, .axis_title="deepTagMD + min m_{sd}", .def_range={-12,1, 618}}); // Purple
  sh.AddNewFillParams("deepTagMD_top_minsd_WP1",     { .nbin=8,  .bins={-20, -12,      -10, 0, 0.054, 0.391, 0.578, 0.843, 1.000}, .fill=[&d] { 
                                                          if (d.FatJet[i_FatJet].msoftdrop<HADTOP_SD_MASS_CUT_LOW)  return (double)-12;
                                                          //if (d.FatJet[i_FatJet].msoftdrop>=HADTOP_SD_MASS_CUT_HIGH) return (double)-11;
                                                          return (double)d.FatJet[i_FatJet].deepTagMD_TvsQCD; }, .axis_title="deepTagMD + min m_{sd}", .def_range={0.391,1, 618}}); // Purple
  sh.AddNewFillParams("deepTag_top_comp",            { .nbin=7,  .bins={-20, -10, 0, 0.093, 0.745, 0.895, 0.986, 1.000}, .fill=[&d] { return d.FatJet[i_FatJet].deepTag_TvsQCD; }, .axis_title="deep", .def_range={-10,1, 633}}); // Red
  sh.AddNewFillParams("deepTag_top_WP1",         { .nbin=6,  .bins={-10, 0, 0.093, 0.745, 0.895, 0.986, 1.000}, .fill=[&d] { return d.FatJet[i_FatJet].deepTag_TvsQCD;   }, .axis_title="deepTag",   .def_range={0.745,1, 633}}); // Red
  // top vs non-top, signal vs. background
  sh.AddNewFillParams("HadTop_T2tt_1200_200",    { .nbin= 2, .bins={-0.5,1.5}, .fill=[] {
                                                      if (background_opt.index==0) return (int)0; // 0: T2tt
                                                      else if (signals_background_opt.index==0 && ak8MatchGenHadTop[i_FatJet]
                                                               && susy_mass.first == 1200 && susy_mass.second == 200) return (int)1;
                                                      return (int)-1; }});
  sh.AddNewFillParams("HadTop_T2tt_1200_1000",   { .nbin= 2, .bins={-0.5,1.5}, .fill=[] {
                                                      if (background_opt.index==0) return (int)0; // 0: T2tt
                                                      else if (signals_background_opt.index==0 && ak8MatchGenHadTop[i_FatJet]
                                                               && susy_mass.first == 1200 && susy_mass.second == 1000) return (int)1;
                                                      return (int)-1; }});
  sh.AddNewFillParams("HadTop_T1tttt_2000_200",  { .nbin= 2, .bins={-0.5,1.5}, .fill=[] {
                                                      if (background_opt.index==0) return (int)0; // 1: T1tttt
                                                      else if (signals_background_opt.index==1 && ak8MatchGenHadTop[i_FatJet]
                                                               && susy_mass.first == 2000 && susy_mass.second == 200) return (int)1;
                                                      return (int)-1; }});
  sh.AddNewFillParams("HadTop_T1tttt_2000_1000", { .nbin= 2, .bins={-0.5,1.5}, .fill=[] {
                                                      if (background_opt.index==0) return (int)0; // 1: T1tttt
                                                      else if (signals_background_opt.index==1 && ak8MatchGenHadTop[i_FatJet]
                                                               && susy_mass.first == 2000 && susy_mass.second == 1000) return (int)1;
                                                      return (int)-1; }});
  sh.AddNewFillParams("HadTop_T5ttcc_2000_200",  { .nbin= 2, .bins={-0.5,1.5}, .fill=[] {
                                                      if (background_opt.index==0) return (int)0; // 2: T5ttcc
                                                      else if (signals_background_opt.index==2 && ak8MatchGenHadTop[i_FatJet]
                                                               && susy_mass.first == 2000 && susy_mass.second == 200) return (int)1;
                                                      return (int)-1; }});
  sh.AddNewFillParams("HadTop_T5ttcc_2000_1000", { .nbin= 2, .bins={-0.5,1.5}, .fill=[] {
                                                      if (background_opt.index==0) return (int)0; // 2: T5ttcc
                                                      else if (signals_background_opt.index==2 && ak8MatchGenHadTop[i_FatJet]
                                                               && susy_mass.first == 2000 && susy_mass.second == 1000) return (int)1;
                                                      return (int)-1; }});
  sh.AddNewFillParams("HadTop_Bkg",              { .nbin= 2, .bins={-0.5,1.5}, .fill=[] { return background_opt.index==0 ? (int)ak8MatchGenHadTop[i_FatJet] : (int)-1; }});
  
  // gen
  sh.AddNewFillParams("GenLepPt",                     { .nbin= 100, .bins={     0,    500},  .fill=[&d] { return d.GenPart[i_GenPart].pt;            }, .axis_title="Gen. Lepton p_{T} (GeV)", .def_range={5,200}});
  sh.AddNewFillParams("GenLepPtBins",                 { .nbin=LepPt.size()-1,  .bins=LepPt,  .fill=[&d] { return d.GenPart[i_GenPart].pt;            }, .axis_title="Gen. Lepton p_{T} (GeV)", .def_range={5,200}});
  sh.AddNewFillParams("GenLepWMatchedGenLepPt",       { .nbin= 100, .bins={     0,    500},  .fill=[&d] { return iGenLepWMatchedGenLep[i_GenPart] == (size_t)-1 ? -9999 : d.GenPart[iGenLepWMatchedGenLep[i_GenPart]].pt; }, .axis_title="Gen. Lepton (from W) p_{T} (GeV)", .def_range={5,200}});
  sh.AddNewFillParams("GenLepWMatchedGenLepPtBins",   { .nbin=LepPt.size()-1,  .bins=LepPt,  .fill=[&d] { return iGenLepWMatchedGenLep[i_GenPart] == (size_t)-1 ? -9999 : d.GenPart[iGenLepWMatchedGenLep[i_GenPart]].pt; }, .axis_title="Gen. Lepton (from W) p_{T} (GeV)", .def_range={5,200}});
  sh.AddNewFillParams("GenLepTopMatchedGenLepPt",     { .nbin= 100, .bins={     0,    500},  .fill=[&d] { return iGenLepTopMatchedGenLep[i_GenPart] == (size_t)-1 ? -9999 : d.GenPart[iGenLepTopMatchedGenLep[i_GenPart]].pt; }, .axis_title="Gen. Lepton (from top) p_{T} (GeV)", .def_range={5,200}});
  sh.AddNewFillParams("GenLepTopMatchedGenLepPtBins", { .nbin=LepPt.size()-1,  .bins=LepPt,  .fill=[&d] { return iGenLepTopMatchedGenLep[i_GenPart] == (size_t)-1 ? -9999 : d.GenPart[iGenLepTopMatchedGenLep[i_GenPart]].pt; }, .axis_title="Gen. Lepton (from top) p_{T} (GeV)", .def_range={5,200}});
  sh.AddNewFillParams("GenLepEta",                    { .nbin=LepEta.size()-1, .bins=LepEta, .fill=[&d] { return std::abs(d.GenPart[i_GenPart].eta); }, .axis_title="Gen. Lepton |#eta| (GeV)"});
  sh.AddNewFillParams("GenHadWPt",                    { .nbin=   80, .bins={    0,    4000}, .fill=[&d] { return d.GenPart[i_GenPart].pt;  }, .axis_title="Gen-W (had.) p_{T} (GeV)",   .def_range={0, 2000}});
  sh.AddNewFillParams("GenHadWPtBins",                { .nbin=Pt.size()-1, .bins=Pt,         .fill=[&d] { return d.GenPart[i_GenPart].pt;  }, .axis_title="Gen-W (had.) p_{T} (GeV)",   .def_range={0, 2000}});
  sh.AddNewFillParams("GenTopPt",                     { .nbin=   80, .bins={    0,    4000}, .fill=[&d] { return d.GenPart[i_GenPart].pt;  }, .axis_title="Gen-top p_{T} (GeV)", .def_range={0, 2000}});
  sh.AddNewFillParams("GenTopPtBins",                 { .nbin=Pt.size()-1, .bins=Pt,         .fill=[&d] { return d.GenPart[i_GenPart].pt;  }, .axis_title="Gen-top p_{T} (GeV)", .def_range={0, 2000}});
  sh.AddNewFillParams("GenHadTopPt",                  { .nbin=   80, .bins={    0,    4000}, .fill=[&d] { return d.GenPart[i_GenPart].pt;  }, .axis_title="Gen-top (had.) p_{T} (GeV)", .def_range={0, 2000}});
  sh.AddNewFillParams("GenHadTopPtBins",              { .nbin=Pt.size()-1, .bins=Pt,         .fill=[&d] { return d.GenPart[i_GenPart].pt;  }, .axis_title="Gen-top (had.) p_{T} (GeV)", .def_range={0, 2000}});
  sh.AddNewFillParams("GenLepTopPt",                  { .nbin=   80, .bins={    0,    4000}, .fill=[&d] { return d.GenPart[i_GenPart].pt;  }, .axis_title="Gen-top (lep.) p_{T} (GeV)", .def_range={0, 2000}});
  sh.AddNewFillParams("GenLepTopPtBins",              { .nbin=Pt.size()-1, .bins=Pt,         .fill=[&d] { return d.GenPart[i_GenPart].pt;  }, .axis_title="Gen-top (lep.) p_{T} (GeV)", .def_range={0, 2000}});
  sh.AddNewFillParams("GenHadWMatchedAK8JetPt",    { .nbin=   80, .bins={    0,    4000}, .fill=[&d] { return iGenHadWMatchedAK8[i_GenPart]==(size_t)-1 ? -9999 : d.FatJet[iGenHadWMatchedAK8[i_GenPart]].pt; }, .axis_title="Matched AK8 jet p_{T} (GeV)", .def_range={0, 2000}});
  sh.AddNewFillParams("GenHadWMatchedAK8JetPtBins",{ .nbin=PtG.size()-1, .bins=PtG,       .fill=[&d] { return iGenHadWMatchedAK8[i_GenPart]==(size_t)-1 ? -9999 : d.FatJet[iGenHadWMatchedAK8[i_GenPart]].pt; }, .axis_title="Matched AK8 jet p_{T} (GeV)", .def_range={0, 2000}});
  sh.AddNewFillParams("GenHadZMatchedAK8JetPt",    { .nbin=   80, .bins={    0,    4000}, .fill=[&d] { return iGenHadZMatchedAK8[i_GenPart]==(size_t)-1 ? -9999 : d.FatJet[iGenHadZMatchedAK8[i_GenPart]].pt; }, .axis_title="Matched AK8 jet p_{T} (GeV)", .def_range={0, 2000}});
  sh.AddNewFillParams("GenHadZMatchedAK8JetPtBins",{ .nbin=PtG.size()-1, .bins=PtG,       .fill=[&d] { return iGenHadZMatchedAK8[i_GenPart]==(size_t)-1 ? -9999 : d.FatJet[iGenHadZMatchedAK8[i_GenPart]].pt; }, .axis_title="Matched AK8 jet p_{T} (GeV)", .def_range={0, 2000}});
  sh.AddNewFillParams("GenHadTopMatchedAK8JetPt",     { .nbin=   80, .bins={    0,    4000}, .fill=[&d] { return iGenHadTopMatchedAK8[i_GenPart]==(size_t)-1 ? -9999 : d.FatJet[iGenHadTopMatchedAK8[i_GenPart]].pt;   }, .axis_title="Matched AK8 jet p_{T} (GeV)", .def_range={0, 2000}});
  sh.AddNewFillParams("GenHadTopMatchedAK8JetPtBins", { .nbin=PtG.size()-1, .bins=PtG,       .fill=[&d] { return iGenHadTopMatchedAK8[i_GenPart]==(size_t)-1 ? -9999 : d.FatJet[iGenHadTopMatchedAK8[i_GenPart]].pt;   }, .axis_title="Matched AK8 jet p_{T} (GeV)", .def_range={0, 2000}});
  sh.AddNewFillParams("GenLepTopMatchedAK8JetPt",     { .nbin=   80, .bins={    0,    4000}, .fill=[&d] { return iGenLepTopMatchedAK8[i_GenPart]==(size_t)-1 ? -9999 : d.FatJet[iGenLepTopMatchedAK8[i_GenPart]].pt;   }, .axis_title="Matched AK8 jet p_{T} (GeV)", .def_range={0, 2000}});
  sh.AddNewFillParams("GenLepTopMatchedAK8JetPtBins", { .nbin=PtG.size()-1, .bins=PtG,       .fill=[&d] { return iGenLepTopMatchedAK8[i_GenPart]==(size_t)-1 ? -9999 : d.FatJet[iGenLepTopMatchedAK8[i_GenPart]].pt;   }, .axis_title="Matched AK8 jet p_{T} (GeV)", .def_range={0, 2000}});
  sh.AddNewFillParams("GenHadWMatchedAK8JetIndex",    { .nbin=   10, .bins={    0,    10}, .fill=[] { return iGenHadWMatchedAK8[i_GenPart];   }, .axis_title="Gen W (had.) matched AK8 jet index", .def_range={0, 5}});
  sh.AddNewFillParams("GenHadZMatchedAK8JetIndex",    { .nbin=   10, .bins={    0,    10}, .fill=[] { return iGenHadZMatchedAK8[i_GenPart];   }, .axis_title="Gen Z (had.) matched AK8 jet index", .def_range={0, 5}});
  sh.AddNewFillParams("GenHadTopMatchedAK8JetIndex",  { .nbin=   10, .bins={    0,    10}, .fill=[] { return iGenHadTopMatchedAK8[i_GenPart]; }, .axis_title="Gen top (had.) matched AK8 jet index", .def_range={0, 5}});
  sh.AddNewFillParams("GenLepTopMatchedAK8JetIndex",  { .nbin=   10, .bins={    0,    10}, .fill=[] { return iGenLepTopMatchedAK8[i_GenPart]; }, .axis_title="Gen top (lep.) matched AK8 jet index", .def_range={0, 5}});

  // Event
  // Cuts
  // Object counts
  sh.AddNewFillParams("NVtx",                 { .nbin=NVTX.size()-1, .bins=NVTX,    .fill=[&d] { return d.PV_npvsGood;      }, .axis_title="N_{Vertices}",         .def_range={0,50}});
  sh.AddNewFillParams("NJet",                 { .nbin=  20, .bins={    0,      20}, .fill=[]   { return nJet;                 }, .axis_title="N_{Jet}",              .def_range={2,20}});
  sh.AddNewFillParams("NJetNoPho",            { .nbin=  20, .bins={    0,      20}, .fill=[]   { return nJetNoPho;            }, .axis_title="N_{Jet}",              .def_range={2,20}});
  sh.AddNewFillParams("NJetAK8",              { .nbin=  10, .bins={    0,      10}, .fill=[]   { return nJetAK8;              }, .axis_title="N_{AK8 jet}",          .def_range={1,10}});
  sh.AddNewFillParams("NBTag",                { .nbin=   5, .bins={    0,       5}, .fill=[]   { return nMediumBTag;          }, .axis_title="N_{b}",                .def_range={0,4}});
  sh.AddNewFillParams("NLooseBTag",           { .nbin=   5, .bins={    0,       5}, .fill=[]   { return nLooseBTag;           }, .axis_title="N_{b, loose tag}",     .def_range={0,4}});
  sh.AddNewFillParams("NTightBTag",           { .nbin=   5, .bins={    0,       5}, .fill=[]   { return nTightBTag;           }, .axis_title="N_{b, tight tag}",     .def_range={0,4}});
  sh.AddNewFillParams("NBTagNoPho",           { .nbin=   5, .bins={    0,       5}, .fill=[]   { return nMediumBTagNoPho;     }, .axis_title="N_{b, no #gamma}",     .def_range={0,4}});
  sh.AddNewFillParams("NmW",                  { .nbin=   5, .bins={    0,       5}, .fill=[]   { return nWMassTag;            }, .axis_title="N_{W, mass-tag}",      .def_range={0,4}});
  sh.AddNewFillParams("NaW",                  { .nbin=   5, .bins={    0,       5}, .fill=[]   { return nTightWAntiTag;       }, .axis_title="N_{W, anti-tag}",      .def_range={0,4}});
  sh.AddNewFillParams("NLooseW",              { .nbin=   5, .bins={    0,       5}, .fill=[]   { return nLooseWTag;           }, .axis_title="N_{W, loose tag}",     .def_range={0,4}});
  sh.AddNewFillParams("NW",                   { .nbin=   5, .bins={    0,       5}, .fill=[]   { return nTightWTag;           }, .axis_title="N_{W}",                .def_range={0,4}});
  sh.AddNewFillParams("NmTop",                { .nbin=   5, .bins={    0,       5}, .fill=[]   { return nHadTop0BMassTag;     }, .axis_title="N_{top, mass-tag}",    .def_range={0,4}});
  sh.AddNewFillParams("NMTop",                { .nbin=   5, .bins={    0,       5}, .fill=[]   { return nHadTopMassTag;       }, .axis_title="N_{top, mass-tag}",    .def_range={0,4}});
  sh.AddNewFillParams("NaTop",                { .nbin=   5, .bins={    0,       5}, .fill=[]   { return nHadTop0BAntiTag;     }, .axis_title="N_{top, anti-tag}",    .def_range={0,4}});
  sh.AddNewFillParams("NTop",                 { .nbin=   5, .bins={    0,       5}, .fill=[]   { return nHadTopTag;           }, .axis_title="N_{top}",              .def_range={0,4}});
  sh.AddNewFillParams("NW1",                  { .nbin=   5, .bins={    0,       5}, .fill=[]   { return nW1;                  }, .axis_title="N_{W} Loose",          .def_range={0,4}});
  sh.AddNewFillParams("NW2",                  { .nbin=   5, .bins={    0,       5}, .fill=[]   { return nW2;                  }, .axis_title="N_{W} Medium",         .def_range={0,4}});
  sh.AddNewFillParams("NW3",                  { .nbin=   5, .bins={    0,       5}, .fill=[]   { return nW3;                  }, .axis_title="N_{W} Tight",          .def_range={0,4}});
  sh.AddNewFillParams("NTop1",                { .nbin=   5, .bins={    0,       5}, .fill=[]   { return nTop1;                }, .axis_title="N_{Top} VLoose",       .def_range={0,4}});
  sh.AddNewFillParams("NTop2",                { .nbin=   5, .bins={    0,       5}, .fill=[]   { return nTop2;                }, .axis_title="N_{Top} Loose",        .def_range={0,4}});
  sh.AddNewFillParams("NTop3",                { .nbin=   5, .bins={    0,       5}, .fill=[]   { return nTop3;                }, .axis_title="N_{Top} Medium",       .def_range={0,4}});
  sh.AddNewFillParams("NTop4",                { .nbin=   5, .bins={    0,       5}, .fill=[]   { return nTop4;                }, .axis_title="N_{Top} Tight",        .def_range={0,4}});
  sh.AddNewFillParams("NTop5",                { .nbin=   5, .bins={    0,       5}, .fill=[]   { return nTop5;                }, .axis_title="N_{Top} VTight",       .def_range={0,4}});
  sh.AddNewFillParams("NWDeep1",              { .nbin=   5, .bins={    0,       5}, .fill=[]   { return nWDeep1;              }, .axis_title="N_{W} (Deep 5%)",      .def_range={0,4}});
  sh.AddNewFillParams("NWDeep2",              { .nbin=   5, .bins={    0,       5}, .fill=[]   { return nWDeep2;              }, .axis_title="N_{W} (Deep 1%)",      .def_range={0,4}});
  sh.AddNewFillParams("NWDeep3",              { .nbin=   5, .bins={    0,       5}, .fill=[]   { return nWDeep3;              }, .axis_title="N_{W} (Deep 0.5%)",    .def_range={0,4}});
  sh.AddNewFillParams("NWDeepMD1",            { .nbin=   5, .bins={    0,       5}, .fill=[]   { return nWDeepMD1;            }, .axis_title="N_{W} (DeepMD 5%)",    .def_range={0,4}});
  sh.AddNewFillParams("NWDeepMD2",            { .nbin=   5, .bins={    0,       5}, .fill=[]   { return nWDeepMD2;            }, .axis_title="N_{W} (DeepMD 1%)",    .def_range={0,4}});
  sh.AddNewFillParams("NWDeepMD3",            { .nbin=   5, .bins={    0,       5}, .fill=[]   { return nWDeepMD3;            }, .axis_title="N_{W} (DeepMD 0.5%)",  .def_range={0,4}});
  sh.AddNewFillParams("NZDeep1",              { .nbin=   5, .bins={    0,       5}, .fill=[]   { return nZDeep1;              }, .axis_title="N_{Z} (Deep 0.80)",    .def_range={0,4}});
  sh.AddNewFillParams("NZDeep2",              { .nbin=   5, .bins={    0,       5}, .fill=[]   { return nZDeep2;              }, .axis_title="N_{Z} (Deep 0.95)",    .def_range={0,4}});
  sh.AddNewFillParams("NZDeep3",              { .nbin=   5, .bins={    0,       5}, .fill=[]   { return nZDeep3;              }, .axis_title="N_{Z} (Deep 0.99)",    .def_range={0,4}});
  sh.AddNewFillParams("NZDeepMD1",            { .nbin=   5, .bins={    0,       5}, .fill=[]   { return nZDeepMD1;            }, .axis_title="N_{Z} (DeepMD 0.30)",  .def_range={0,4}});
  sh.AddNewFillParams("NZDeepMD2",            { .nbin=   5, .bins={    0,       5}, .fill=[]   { return nZDeepMD2;            }, .axis_title="N_{Z} (DeepMD 0.80)",  .def_range={0,4}});
  sh.AddNewFillParams("NZDeepMD3",            { .nbin=   5, .bins={    0,       5}, .fill=[]   { return nZDeepMD3;            }, .axis_title="N_{Z} (DeepMD 0.90)",  .def_range={0,4}});
  sh.AddNewFillParams("NTopDeep1",            { .nbin=   5, .bins={    0,       5}, .fill=[]   { return nTopDeep1;            }, .axis_title="N_{Top} (Deep 5%)",    .def_range={0,4}});
  sh.AddNewFillParams("NTopDeep2",            { .nbin=   5, .bins={    0,       5}, .fill=[]   { return nTopDeep2;            }, .axis_title="N_{Top} (Deep 1%)",    .def_range={0,4}});
  sh.AddNewFillParams("NTopDeep3",            { .nbin=   5, .bins={    0,       5}, .fill=[]   { return nTopDeep3;            }, .axis_title="N_{Top} (Deep 0.5%)",  .def_range={0,4}});
  sh.AddNewFillParams("NTopDeep4",            { .nbin=   5, .bins={    0,       5}, .fill=[]   { return nTopDeep4;            }, .axis_title="N_{Top} (Deep 0.1%)",  .def_range={0,4}});
  sh.AddNewFillParams("NTopDeepMD1",          { .nbin=   5, .bins={    0,       5}, .fill=[]   { return nTopDeepMD1;          }, .axis_title="N_{Top} (DeepMD 5%)",  .def_range={0,4}});
  sh.AddNewFillParams("NTopDeepMD2",          { .nbin=   5, .bins={    0,       5}, .fill=[]   { return nTopDeepMD2;          }, .axis_title="N_{Top} (DeepMD 1%)",  .def_range={0,4}});
  sh.AddNewFillParams("NTopDeepMD3",          { .nbin=   5, .bins={    0,       5}, .fill=[]   { return nTopDeepMD3;          }, .axis_title="N_{Top} (DeepMD 0.5%)",.def_range={0,4}});
  sh.AddNewFillParams("NTopDeepMD4",          { .nbin=   5, .bins={    0,       5}, .fill=[]   { return nTopDeepMD4;          }, .axis_title="N_{Top} (DeepMD 0.1%)",.def_range={0,4}});
  sh.AddNewFillParams("NLepVeto",             { .nbin=   5, .bins={    0,       5}, .fill=[]   { return nLepVeto;             }, .axis_title="N_{lepton, Veto}",     .def_range={0,4}});
  sh.AddNewFillParams("NEleVeto",             { .nbin=   5, .bins={    0,       5}, .fill=[]   { return nEleVeto;             }, .axis_title="N_{ele, Veto}",        .def_range={0,4}});
  sh.AddNewFillParams("NMuVeto",              { .nbin=   5, .bins={    0,       5}, .fill=[]   { return nMuVeto;              }, .axis_title="N_{muon, Veto}",       .def_range={0,4}});
  sh.AddNewFillParams("NTauVeto",             { .nbin=   5, .bins={    0,       5}, .fill=[]   { return nTauVeto;             }, .axis_title="N_{tau, Veto}",        .def_range={0,4}});
  sh.AddNewFillParams("NLepLoose",            { .nbin=   5, .bins={    0,       5}, .fill=[]   { return nLepLoose;            }, .axis_title="N_{lepton, Loose}",    .def_range={0,4}});
  sh.AddNewFillParams("NEleLoose",            { .nbin=   5, .bins={    0,       5}, .fill=[]   { return nEleLoose;            }, .axis_title="N_{ele, Loose}",       .def_range={0,4}});
  sh.AddNewFillParams("NMuLoose",             { .nbin=   5, .bins={    0,       5}, .fill=[]   { return nMuLoose;             }, .axis_title="N_{muon, Loose}",      .def_range={0,4}});
  sh.AddNewFillParams("NIsoTrk",              { .nbin=   5, .bins={    0,       5}, .fill=[&d] { return d.nIsoTrack;          }, .axis_title="N_{iso trk}",          .def_range={0,4}});
  sh.AddNewFillParams("NLep",                 { .nbin=   5, .bins={    0,       5}, .fill=[]   { return nLepSelect;           }, .axis_title="N_{lepton}",           .def_range={0,4}});
  sh.AddNewFillParams("NLepTight",            { .nbin=   5, .bins={    0,       5}, .fill=[]   { return nLepTight;            }, .axis_title="N_{e/#mu, tight}",         .def_range={0,5}});
  sh.AddNewFillParams("NEleTightNoIso",       { .nbin=   5, .bins={    0,       5}, .fill=[]   { return nEleTightNoIso;       }, .axis_title="N_{e, tight, no iso}", .def_range={0,5}});
  sh.AddNewFillParams("NMuTightNoIso",        { .nbin=   5, .bins={    0,       5}, .fill=[]   { return nMuTightNoIso;        }, .axis_title="N_{#mu, tight, no iso}", .def_range={0,5}});
  sh.AddNewFillParams("NLepTightNoIso",       { .nbin=   5, .bins={    0,       5}, .fill=[]   { return nLepTightNoIso;       }, .axis_title="N_{e/#mu, tight, no iso}", .def_range={0,5}});
  sh.AddNewFillParams("NEleTight2D",          { .nbin=   5, .bins={    0,       5}, .fill=[]   { return nEleTight2D;          }, .axis_title="N_{e, tight, 2D iso}", .def_range={0,5}});
  sh.AddNewFillParams("NMuTight2D",           { .nbin=   5, .bins={    0,       5}, .fill=[]   { return nMuTight2D;           }, .axis_title="N_{#mu, tight, 2D iso}", .def_range={0,5}});
  sh.AddNewFillParams("NLepTight2D",          { .nbin=   5, .bins={    0,       5}, .fill=[]   { return nLepTight2D;          }, .axis_title="N_{e/#mu, tight, 2D iso}", .def_range={0,5}});
  sh.AddNewFillParams("NEle",                 { .nbin=   5, .bins={    0,       5}, .fill=[]   { return nEleSelect;           }, .axis_title="N_{electron}",         .def_range={0,4}});
  sh.AddNewFillParams("NMu",                  { .nbin=   5, .bins={    0,       5}, .fill=[]   { return nMuSelect;            }, .axis_title="N_{muon}",             .def_range={0,4}});
  sh.AddNewFillParams("NPhoton",              { .nbin=   5, .bins={    0,       5}, .fill=[]   { return nPhotonSelect;        }, .axis_title="N_{photon}",           .def_range={0,4}});
  // Gen truth
  sh.AddNewFillParams("NGenEleFromW",         { .nbin=   5, .bins={    0,       5}, .fill=[]   { return nGenEleFromW;    }, .axis_title="N_{e, gen}",   .def_range={0,5}});
  sh.AddNewFillParams("NGenMuFromW",          { .nbin=   5, .bins={    0,       5}, .fill=[]   { return nGenMuFromW;     }, .axis_title="N_{#mu, gen}", .def_range={0,5}});
  sh.AddNewFillParams("NGenLepFromW",         { .nbin=   5, .bins={    0,       5}, .fill=[]   { return nGenLeptonFromW; }, .axis_title="N_{lep, gen}", .def_range={0,5}});
  sh.AddNewFillParams("NGenEleFromZ",         { .nbin=   5, .bins={    0,       5}, .fill=[]   { return nGenEleFromZ;    }, .axis_title="N_{e, gen}",   .def_range={0,5}});
  sh.AddNewFillParams("NGenMuFromZ",          { .nbin=   5, .bins={    0,       5}, .fill=[]   { return nGenMuFromZ;     }, .axis_title="N_{#mu, gen}", .def_range={0,5}});
  sh.AddNewFillParams("NGenLepFromZ",         { .nbin=   5, .bins={    0,       5}, .fill=[]   { return nGenLeptonFromZ; }, .axis_title="N_{lep, gen}", .def_range={0,5}});
  sh.AddNewFillParams("NGenEleFromTop",       { .nbin=   5, .bins={    0,       5}, .fill=[]   { return nGenEleFromTop;    }, .axis_title="N_{e, gen}",   .def_range={0,5}});
  sh.AddNewFillParams("NGenMuFromTop",        { .nbin=   5, .bins={    0,       5}, .fill=[]   { return nGenMuFromTop;     }, .axis_title="N_{#mu, gen}", .def_range={0,5}});
  sh.AddNewFillParams("NGenLepFromTop",       { .nbin=   5, .bins={    0,       5}, .fill=[]   { return nGenLeptonFromTop; }, .axis_title="N_{lep, gen}", .def_range={0,5}});
  sh.AddNewFillParams("NGenHadW",             { .nbin=   5, .bins={    0,       5}, .fill=[]   { return nGenHadW;          }, .axis_title="N_{W (had.), gen}", .def_range={0,5}});
  sh.AddNewFillParams("NGenHadZ",             { .nbin=   5, .bins={    0,       5}, .fill=[]   { return nGenHadZ;          }, .axis_title="N_{Z (had.), gen}", .def_range={0,5}});
  sh.AddNewFillParams("NGenHadTop",           { .nbin=   5, .bins={    0,       5}, .fill=[]   { return nGenHadTop;        }, .axis_title="N_{top (had.), gen}", .def_range={0,5}});
  sh.AddNewFillParams("NGenLepTop",           { .nbin=   5, .bins={    0,       5}, .fill=[]   { return nGenLepTop;        }, .axis_title="N_{top (lep.), gen}", .def_range={0,5}});
  // Razor
  sh.AddNewFillParams("R",                    { .nbin=  40, .bins={    0,     2.0}, .fill=[]   { return R;                 }, .axis_title="R",                    .def_range={0,1}});
  sh.AddNewFillParams("RFine",                { .nbin= 200, .bins={    0,     2.0}, .fill=[]   { return R;                 }, .axis_title="R",                    .def_range={0,1}});
  sh.AddNewFillParams("RBins",                { .nbin=R_bins.size()-1, .bins=R_bins,          .fill=[]   { return R;                 }, .axis_title="R",                    .def_range={0,1}});
  //sh.AddNewFillParams("MR",                   { .nbin= 100, .bins={    0,   10000}, .fill=[]   { return MR;                      }, .axis_title="M_{R} (GeV)",          .def_range={0,2000}});
  //sh.AddNewFillParams("R2",                   { .nbin=  80, .bins={    0,     4.0}, .fill=[]   { return R2;                      }, .axis_title="R^{2}",                .def_range={0,1}});
  sh.AddNewFillParams("MR",                   { .nbin=MR_bins.size()-1, .bins=MR_bins, .fill=[]   { return MR;                }, .axis_title="M_{R} (GeV)",          .def_range={0,4000}});
  sh.AddNewFillParams("MRFine",               { .nbin=  25, .bins={    0,    5000}, .fill=[]   { return MR;                }, .axis_title="M_{R} (GeV)",          .def_range={800,4000}});
  sh.AddNewFillParams("MRBins",               { .nbin=MR_RI.size()-1, .bins=MR_RI,  .fill=[]   { return MR;                }, .axis_title="M_{R} (GeV)",          .def_range={300,4000}});
  //sh.AddNewFillParams("MTR",                  { .nbin=  80, .bins={    0,    4000}, .fill=[]   { return MTR;               }, .axis_title="M_{T}^{R} (GeV)",      .def_range={0,2000}});
  sh.AddNewFillParams("MTR",                  { .nbin=MTR_bins.size()-1, .bins=MTR_bins,      .fill=[]   { return MTR;               }, .axis_title="M_{T}^{R} (GeV)",      .def_range={0,2000}});
  sh.AddNewFillParams("R2",                   { .nbin=R2_bins.size()-1, .bins=R2_bins, .fill=[]   { return R2;                      }, .axis_title="R^{2}",                .def_range={0,1.5}});
  sh.AddNewFillParams("R2Fine",               { .nbin=  40, .bins={    0,     1.6}, .fill=[]   { return R2;                      }, .axis_title="R^{2}",                .def_range={0,1.6}});
  sh.AddNewFillParams("R2Bins",               { .nbin=R2_RI.size()-1, .bins=R2_RI,  .fill=[]   { return R2;                      }, .axis_title="R^{2}",                .def_range={0.15,1.5}});
  sh.AddNewFillParams("MTRll",                { .nbin=MTR_bins.size()-1, .bins=MTR_bins,      .fill=[]   { return MTR_ll;                  }, .axis_title="M_{T,ll}^{R} (GeV)",   .def_range={0,2000}});
  sh.AddNewFillParams("R2ll",                 { .nbin=R2_bins.size()-1, .bins=R2_bins, .fill=[]   { return R2_ll;                   }, .axis_title="R_{ll}^{2}",           .def_range={0,1.5}});
  sh.AddNewFillParams("MTR1l",                { .nbin=MTR_bins.size()-1, .bins=MTR_bins,      .fill=[]   { return MTR_1l;                  }, .axis_title="M_{T, no lep}^{R} (GeV)",   .def_range={0,2000}});
  sh.AddNewFillParams("MTR1vl",               { .nbin=MTR_bins.size()-1, .bins=MTR_bins,      .fill=[]   { return MTR_1vl;                 }, .axis_title="M_{T, no lep}^{R} (GeV)",   .def_range={0,2000}});
  sh.AddNewFillParams("R21l",                 { .nbin=R2_bins.size()-1, .bins=R2_bins, .fill=[]   { return R2_1l;                   }, .axis_title="R_{no lep}^{2}",       .def_range={0,1.5}});
  sh.AddNewFillParams("R21vl",                { .nbin=R2_bins.size()-1, .bins=R2_bins, .fill=[]   { return R2_1vl;                  }, .axis_title="R_{no lep}^{2}",       .def_range={0,1.5}});
  add_unrolled_bins(sh, "RazorBins",       "M_{R} (TeV)", "R^{2}", [] { return MR/1000;     }, [] { return R2;     }, MR_2D_bins,     R2_2D_bins, merged_razor_bins,     1, 2);
  add_unrolled_bins(sh, "RazorBinsLep",    "M_{R} (TeV)", "R^{2}", [] { return MR/1000;     }, [] { return R2;     }, MR_2D_bins_lep, R2_2D_bins, merged_razor_bins_lep, 1, 2);
  add_unrolled_bins(sh, "RazorllBins",     "M_{R} (TeV)", "R^{2}", [] { return MR/1000;     }, [] { return R2_ll;  }, MR_2D_bins,     R2_2D_bins, merged_razor_bins,     1, 2);
  add_unrolled_bins(sh, "Razor1lBins",     "M_{R} (TeV)", "R^{2}", [] { return MR/1000;     }, [] { return R2_1l;  }, MR_2D_bins,     R2_2D_bins, merged_razor_bins,     1, 2);
  add_unrolled_bins(sh, "Razor1vlBins",    "M_{R} (TeV)", "R^{2}", [] { return MR/1000;     }, [] { return R2_1vl; }, MR_2D_bins,     R2_2D_bins, merged_razor_bins,     1, 2);
  add_unrolled_bins(sh, "RazorNoPhoBins",  "M_{R} (TeV)", "R^{2}", [] { return MR_pho/1000; }, [] { return R2_pho; }, MR_2D_bins,     R2_2D_bins, merged_razor_bins,     1, 2);
  sh.AddNewFillParams("MRR2",                 { .nbin=  15, .bins={    0,    3000}, .fill=[]   { return MR*R2;                }, .axis_title="M_{R} #times R^{2} (GeV)",  .def_range={0,2400}});
  // New improved version
  sh.AddNewFillParams("MRNew",                   { .nbin=MR_bins.size()-1, .bins=MR_bins, .fill=[]   { return MR;                }, .axis_title="M_{R} (GeV)",          .def_range={0,4000}});
  add_unrolled_bins(sh, "RazorBinsNew",    "M_{R} (TeV)", "R^{2}", [] { return MR_new/1000; }, [] { return R2_new; }, MR_2D_bins,     R2_2D_bins, merged_razor_bins,     1, 2);
  add_unrolled_bins(sh, "RazorBinsNewLep", "M_{R} (TeV)", "R^{2}", [] { return MR_new/1000; }, [] { return R2_new; }, MR_2D_bins_lep, R2_2D_bins, merged_razor_bins_lep, 1, 2);
  sh.AddNewFillParams("R2New",                   { .nbin=R2_bins.size()-1, .bins=R2_bins, .fill=[]   { return R2;                      }, .axis_title="R^{2}",                .def_range={0,1.5}});
  // Razor with removed photon
  sh.AddNewFillParams("MRNoPho",              { .nbin=MR_bins.size()-1, .bins=MR_bins, .fill=[]   { return MR_pho;                }, .axis_title="M_{R, no #gamma} (GeV)",          .def_range={0,4000}});
  sh.AddNewFillParams("MRNoPhoBins",          { .nbin=MR_RI.size()-1, .bins=MR_RI,  .fill=[]   { return MR_pho;                }, .axis_title="M_{R, no #gamma} (GeV)",          .def_range={300,4000}});
  sh.AddNewFillParams("MTRNoPho",             { .nbin=MTR_bins.size()-1, .bins=MTR_bins,      .fill=[]   { return MTR_pho;               }, .axis_title="M_{T, no #gamma}^{R} (GeV)",      .def_range={0,2000}});
  sh.AddNewFillParams("R2NoPho",              { .nbin=R2_bins.size()-1, .bins=R2_bins, .fill=[]   { return R2_pho;                }, .axis_title="R_{no #gamma}^{2}",                .def_range={0,2}});
  sh.AddNewFillParams("R2NoPhoBins",          { .nbin=R2_RI.size()-1, .bins=R2_RI,  .fill=[]   { return R2_pho;                }, .axis_title="R_{no #gamma}^{2}",                .def_range={0.15,1.5}});

  // HT
  //sh.AddNewFillParams("HT",                   { .nbin=HT.size()-1, .bins=HT,        .fill=[]   { return AK4_Ht;             }, .axis_title="H_{T} (GeV)",                 .def_range={200, 2000}});
  sh.AddNewFillParams("HTFine",               { .nbin=  50, .bins={    0,    5000}, .fill=[]   { return AK4_Ht;             }, .axis_title="H_{T} (GeV)",                   .def_range={200, 2000}});
  sh.AddNewFillParams("HT",                   { .nbin=HT.size()-1, .bins=HT,        .fill=[]   { return AK4_Ht;             }, .axis_title="H_{T} (GeV)",                   .def_range={200, 2000}});
  sh.AddNewFillParams("HT2DBins",             { .nbin=HT_2D_bins.size()-1, .bins=HT_2D_bins, .fill=[]   { return AK4_Ht;             }, .axis_title="H_{T} (GeV)",          .def_range={200, 1500}});
  sh.AddNewFillParams("OnlineHT",             { .nbin= 100, .bins={    0,    5000}, .fill=[]   { return AK4_HtOnline;       }, .axis_title="H_{T}^{HLT} (GeV)",             .def_range={200, 2000}});
  sh.AddNewFillParams("HTNoLep",              { .nbin= 100, .bins={    0,    5000}, .fill=[]   { return AK4_HtNoLep;        }, .axis_title="H_{T} (GeV)",                   .def_range={200, 2000}});
  //sh.AddNewFillParams("GenHT",                { .nbin=HT.size()-1, .bins=HT,        .fill=[&d] { return d.evt.Gen_Ht;            }, .axis_title="H_{T}^{Gen} (GeV)",    .def_range={0, 2000}});
  sh.AddNewFillParams("AK8HT",                { .nbin=HT.size()-1, .bins=HT,        .fill=[]   { return AK8_Ht;             }, .axis_title="H_{T}^{AK8} (GeV)",             .def_range={0, 2000}});
  // MET
  sh.AddNewFillParams("MET",                  { .nbin=MET.size()-1, .bins=MET,      .fill=[&d] { return d.MET_pt;              }, .axis_title="#slash{E}_{T} (GeV)",              .def_range={0,2000}});
  sh.AddNewFillParams("MET2DBins",            { .nbin=MET_2D_bins.size()-1, .bins=MET_2D_bins, .fill=[&d] { return d.MET_pt;   }, .axis_title="#slash{E}_{T} (GeV)",              .def_range={0,600}});
  sh.AddNewFillParams("METNoPho",             { .nbin=MET.size()-1, .bins=MET,      .fill=[]   { return MET_pho;                 }, .axis_title="#slash{E}_{T, no #gamma} (GeV)", .def_range={0,2000}});
  sh.AddNewFillParams("METll",                { .nbin=MET.size()-1, .bins=MET,      .fill=[]   { return MET_ll;                  }, .axis_title="#slash{E}_{T,ll} (GeV)",         .def_range={0,2000}});
  sh.AddNewFillParams("MET1l",                { .nbin=MET.size()-1, .bins=MET,      .fill=[]   { return MET_1l;                  }, .axis_title="#slash{E}_{T,no lep} (GeV)",     .def_range={0,2000}});
  sh.AddNewFillParams("MET1vl",               { .nbin=MET.size()-1, .bins=MET,      .fill=[]   { return MET_1vl;                 }, .axis_title="#slash{E}_{T,no lep} (GeV)",     .def_range={0,2000}});
  sh.AddNewFillParams("METFine",              { .nbin=  40, .bins={    0,    2000}, .fill=[&d] { return d.MET_pt;              }, .axis_title="#slash{E}_{T} (GeV)",              .def_range={0,2000}});

  // Unrolled HT vs AK8Pt1 - For trigger efficiency
  add_unrolled_bins(sh, "HTJet1AK8Pt",     "p_{T} (GeV)", "H_{T} (TeV)", [&d] { return (nJetAK8<1) ? -9999. : d.FatJet[iJetAK8[0]].pt; }, [] { return AK4_Ht/1000; }, Pt_2D_bins,     HT_2D_bins_old, {}, 0, 2);
  add_unrolled_bins(sh, "HTJet1AK8PtLow",  "p_{T} (GeV)", "H_{T} (TeV)", [&d] { return (nJetAK8<1) ? -9999. : d.FatJet[iJetAK8[0]].pt; }, [] { return AK4_Ht/1000; }, PtLow_2D_bins,  HT_2D_bins_old, {}, 0, 2);
  add_unrolled_bins(sh, "HTJet1AK8PtHigh", "p_{T} (GeV)", "H_{T} (TeV)", [&d] { return (nJetAK8<1) ? -9999. : d.FatJet[iJetAK8[0]].pt; }, [] { return AK4_Ht/1000; }, PtHigh_2D_bins, HT_2D_bins_old, {}, 0, 2);
  // Unrolled HT vs MET - For 2017-18 trigger efficiency
  add_unrolled_bins(sh, "HTMET",           "H_{T} (GeV)", "#slash{E}_{T} (GeV)", [] { return AK4_Ht; }, [&d] { return d.MET_pt; }, HT_2D_bins,  MET_2D_bins, merged_trigger_bins);
  add_unrolled_bins(sh, "HT1MET",          "H_{T} (GeV)", "#slash{E}_{T} (GeV)", [] { return AK4_Ht; }, [&d] { return d.MET_pt; }, HT1_2D_bins, MET_2D_bins, merged_trigger1_bins);
  add_unrolled_bins(sh, "HT2MET",          "H_{T} (GeV)", "#slash{E}_{T} (GeV)", [] { return AK4_Ht; }, [&d] { return d.MET_pt; }, HT2_2D_bins, MET_2D_bins, merged_trigger2_bins);
  add_unrolled_bins(sh, "HT3MET",          "H_{T} (GeV)", "#slash{E}_{T} (GeV)", [] { return AK4_Ht; }, [&d] { return d.MET_pt; }, HT3_2D_bins, MET_2D_bins, merged_trigger3_bins);
  add_unrolled_bins(sh, "HTMETPrev",       "H_{T} (GeV)", "#slash{E}_{T} (GeV)", [] { return AK4_Ht; }, [&d] { return d.MET_pt; }, {300, 500, 550, 600, 800, 1500, 10000}, {50, 150, 200, 400, 10000});
  // Unrolled HT vs LeptonPt - For 2017-18 leptonic trigger efficiencies
  add_unrolled_bins(sh, "HTElePt",         "H_{T} (GeV)", "Ele p_{T} (GeV)", [] { return AK4_Ht; }, [&d] { return nEleTight<1 ? -9999 : d.Electron[iEleTight[0]].pt; }, HT_2D_bins_lep,  ElePt_2D_bins);
  add_unrolled_bins(sh, "HT1ElePt",        "H_{T} (GeV)", "Ele p_{T} (GeV)", [] { return AK4_Ht; }, [&d] { return nEleTight<1 ? -9999 : d.Electron[iEleTight[0]].pt; }, HT1_2D_bins_lep, ElePt_2D_bins);
  add_unrolled_bins(sh, "HT2ElePt",        "H_{T} (GeV)", "Ele p_{T} (GeV)", [] { return AK4_Ht; }, [&d] { return nEleTight<1 ? -9999 : d.Electron[iEleTight[0]].pt; }, HT2_2D_bins_lep, ElePt_2D_bins);
  add_unrolled_bins(sh, "HT3ElePt",        "H_{T} (GeV)", "Ele p_{T} (GeV)", [] { return AK4_Ht; }, [&d] { return nEleTight<1 ? -9999 : d.Electron[iEleTight[0]].pt; }, HT3_2D_bins_lep, ElePt_2D_bins);
  add_unrolled_bins(sh, "HTMuPt",          "H_{T} (GeV)", "Mu p_{T} (GeV)",  [] { return AK4_Ht; }, [&d] { return nMuTight<1 ? -9999 : d.Muon[iMuTight[0]].pt;       }, HT_2D_bins_lep,  MuPt_2D_bins);
  add_unrolled_bins(sh, "HT1MuPt",         "H_{T} (GeV)", "Mu p_{T} (GeV)",  [] { return AK4_Ht; }, [&d] { return nMuTight<1 ? -9999 : d.Muon[iMuTight[0]].pt;       }, HT1_2D_bins_lep, MuPt_2D_bins);
  add_unrolled_bins(sh, "HT2MuPt",         "H_{T} (GeV)", "Mu p_{T} (GeV)",  [] { return AK4_Ht; }, [&d] { return nMuTight<1 ? -9999 : d.Muon[iMuTight[0]].pt;       }, HT2_2D_bins_lep, MuPt_2D_bins);
  add_unrolled_bins(sh, "HT3MuPt",         "H_{T} (GeV)", "Mu p_{T} (GeV)",  [] { return AK4_Ht; }, [&d] { return nMuTight<1 ? -9999 : d.Muon[iMuTight[0]].pt;       }, HT3_2D_bins_lep, MuPt_2D_bins);
  
  // DPhi
  sh.AddNewFillParams("DeltaPhi",                 { .nbin=DP.size()-1,  .bins=DP,       .fill=[]   { return dPhiRazor;               }, .axis_title="#Delta#phi_{megajets}"});
  sh.AddNewFillParams("DeltaPhiNoPho",            { .nbin=DP.size()-1,  .bins=DP,       .fill=[]   { return dPhiRazorNoPho;          }, .axis_title="#Delta#phi_{megajets, no #gamma}"});
  //sh.AddNewFillParams("MinDeltaPhi",              { .nbin=  64, .bins={    0,     3.2}, .fill=[]   { return minDeltaPhi;             }, .axis_title="#Delta#phi_{min}"});
  sh.AddNewFillParams("MinDeltaPhi",              { .nbin=MDP.size()-1, .bins=MDP,      .fill=[]   { return minDeltaPhi;             }, .axis_title="#Delta#phi_{min}"});
  sh.AddNewFillParams("MinDeltaPhi1l",            { .nbin=MDP.size()-1, .bins=MDP,      .fill=[]   { return minDeltaPhi_1l;          }, .axis_title="#Delta#phi_{min,no lep}"});
  sh.AddNewFillParams("MinDeltaPhi1vl",           { .nbin=MDP.size()-1, .bins=MDP,      .fill=[]   { return minDeltaPhi_1vl;         }, .axis_title="#Delta#phi_{min,no lep}"});
  sh.AddNewFillParams("MinDeltaPhill",            { .nbin=MDP.size()-1, .bins=MDP,      .fill=[]   { return minDeltaPhi_ll;          }, .axis_title="#Delta#phi_{min,ll}"});
  sh.AddNewFillParams("MinDeltaPhiNoPho",         { .nbin=MDP.size()-1, .bins=MDP,      .fill=[]   { return minDeltaPhi_pho;         }, .axis_title="#Delta#phi_{min, no #gamma}"});
  sh.AddNewFillParams("DeltaPhiLLMET",            { .nbin=MDP.size()-1, .bins=MDP,      .fill=[]   { return dPhi_ll_met;             }, .axis_title="#Delta#phi (ll, MET)"});
  sh.AddNewFillParams("DeltaPhiLLJet",            { .nbin=MDP.size()-1, .bins=MDP,      .fill=[]   { return dPhi_ll_jet;             }, .axis_title="#Delta#phi_{min} (ll, jet)"});
  sh.AddNewFillParams("DeltaRWb",                 { .nbin=  60, .bins={    0,       6}, .fill=[]   { return minDeltaR_W_b;           }, .axis_title="#DeltaR_{min} (W, b)"});
  sh.AddNewFillParams("DeltaPhiBoostedJetMET",    { .nbin=DP.size()-1,  .bins=DP,       .fill=[]   { return dPhiBoostedJetMET;       }, .axis_title="#Delta#phi (AK8 jet, MET)"});
  sh.AddNewFillParams("DeltaPhiBoostedJetLep",    { .nbin=DP.size()-1,  .bins=DP,       .fill=[]   { return dPhiBoostedJetLep;       }, .axis_title="#Delta#phi (AK8 jet, lep)"});
  sh.AddNewFillParams("DeltaPhiBoostedJetLepMET", { .nbin=DP.size()-1,  .bins=DP,       .fill=[]   { return dPhiBoostedJetLepMET;    }, .axis_title="#Delta#phi (AK8 jet, lep+MET)"});
  // MT/Mll
  sh.AddNewFillParams("MT",                   { .nbin=  50, .bins={    0,    1000}, .fill=[]   { return MT_vetolep;              }, .axis_title="m_{T} (GeV)",  .def_range={0,500}});
  sh.AddNewFillParams("MTSelect",             { .nbin=  50, .bins={    0,    1000}, .fill=[]   { return MT;                      }, .axis_title="m_{T} (GeV)",  .def_range={0,500}});
  sh.AddNewFillParams("MTTight",              { .nbin=  50, .bins={    0,    1000}, .fill=[]   { return MT_lepTight;             }, .axis_title="m_{T} (GeV)",  .def_range={0,500}});
  sh.AddNewFillParams("MTTightNoIso",         { .nbin=  50, .bins={    0,    1000}, .fill=[]   { return MT_lepTightNoIso;        }, .axis_title="m_{T} (GeV)",  .def_range={0,500}});
  sh.AddNewFillParams("MTTight2D",            { .nbin=  25, .bins={    0,    1000}, .fill=[]   { return MT_lepTight2D;           }, .axis_title="m_{T} (GeV)",  .def_range={0,500}});
  sh.AddNewFillParams("MTBoost",              { .nbin=  20, .bins={    0,    4000}, .fill=[]   { return MT_boost;                }, .axis_title="m_{T,Boost+MET} (GeV)",  .def_range={0,2000}});
  sh.AddNewFillParams("Mll",                  { .nbin=  50, .bins={    0,     500}, .fill=[]   { return M_ll;                    }, .axis_title="m_{ll} (GeV)", .def_range={0,200}});
  // SUSY
  sh.AddNewFillParams("MGluino",              { .nbin= 121, .bins={-12.5, 3012.5 }, .fill=[]   { return susy_mass.first;      }, .axis_title="m_{#tilde{g}} (GeV)",        .def_range={550,2350}});
  sh.AddNewFillParams("MStop",                { .nbin=  81, .bins={-12.5, 2012.5 }, .fill=[]   { return susy_mass.first;      }, .axis_title="m_{#tilde{t}} (GeV)",        .def_range={  0,1650}});
  sh.AddNewFillParams("MChargino",            { .nbin=  81, .bins={-12.5, 2012.5 }, .fill=[]   { return susy_mass.first;      }, .axis_title="m_{#tilde{#chi}^{#pm}_{1}} (GeV)",        .def_range={  0,1650}});
  sh.AddNewFillParams("MLSP",                 { .nbin=  81, .bins={-12.5, 2012.5 }, .fill=[]   { return susy_mass.second;     }, .axis_title="m_{#tilde{#chi}^{0}_{1}} (GeV)", .def_range={  0,1650}});
  sh.AddNewFillParams("StopLSPMassDiff",      { .nbin= 400, .bins={0, 2000 },       .fill=[]   { return susy_mass.first-susy_mass.second; }, .axis_title="m_{#tilde{t}}-m_{#tilde{#chi}^{0}_{1}} (GeV)"});
  // AK8 JetN
  sh.AddNewFillParams("Jet1AK8Mass",         { .nbin=M.size()-1, .bins=M,           .fill=[]   { return (nJetAK8<1) ? -9999. : softDropMassW[iJetAK8[0]]; }, .axis_title="Leading AK8 jet m_{Soft-Drop} (GeV)",    .def_range={0, 300}});
  sh.AddNewFillParams("Jet2AK8Mass",         { .nbin=M.size()-1, .bins=M,           .fill=[]   { return (nJetAK8<2) ? -9999. : softDropMassW[iJetAK8[1]]; }, .axis_title="Subleading AK8 jet m_{Soft-Drop} (GeV)", .def_range={0, 300}});
  sh.AddNewFillParams("Jet1AK8Pt",           { .nbin=  100, .bins={    0,   10000}, .fill=[&d] { return (nJetAK8<1) ? -9999. : d.FatJet[iJetAK8[0]].pt;           }, .axis_title="Leading AK8 jet p_{T} (GeV)",    .def_range={200, 1000}});
  sh.AddNewFillParams("Jet1AK8PtBins",       { .nbin=PtB.size()-1, .bins=PtB,       .fill=[&d] { return (nJetAK8<1) ? -9999. : d.FatJet[iJetAK8[0]].pt;           }, .axis_title="Leading AK8 jet p_{T} (GeV)",    .def_range={200, 1000}});
  sh.AddNewFillParams("Jet2AK8PtBins",       { .nbin=PtB.size()-1, .bins=PtB,       .fill=[&d] { return (nJetAK8<2) ? -9999. : d.FatJet[iJetAK8[1]].pt;           }, .axis_title="Subleading AK8 jet p_{T} (GeV)", .def_range={200, 1000}});
  sh.AddNewFillParams("Jet1AK8Eta",          { .nbin=   80, .bins={   -4,       4}, .fill=[&d] { return (nJetAK8<1) ? -9999. : d.FatJet[iJetAK8[0]].eta;          }, .axis_title="Leading AK8 jet #eta",    .def_range={-3, 3}});
  sh.AddNewFillParams("Jet2AK8Eta",          { .nbin=   80, .bins={   -4,       4}, .fill=[&d] { return (nJetAK8<2) ? -9999. : d.FatJet[iJetAK8[1]].eta;          }, .axis_title="Subleading AK8 jet #eta", .def_range={-3, 3}});
  sh.AddNewFillParams("Jet1AK8Tau32",        { .nbin=   50, .bins={    0,       1}, .fill=[]   { return (nJetAK8<1) ? -9999. : tau32[iJetAK8[0]];                       }, .axis_title="Leading AK8 jet #tau_{32}"});
  sh.AddNewFillParams("Jet2AK8Tau32",        { .nbin=   50, .bins={    0,       1}, .fill=[]   { return (nJetAK8<2) ? -9999. : tau32[iJetAK8[1]];                       }, .axis_title="Subleading AK8 jet #tau_{32}"});
  sh.AddNewFillParams("mW1Mass",             { .nbin=MW.size()-1, .bins=MW,         .fill=[]   { return (nWMassTag<1)? -9999. : softDropMassW[iWMassTag[0]]; }, .axis_title="Mass-tagged W m_{Soft-Drop} (GeV)"});
  sh.AddNewFillParams("Jet1AK8BTagCSV",      { .nbin=  101, .bins={    0,    1.01}, .fill=[]   { return (nJetAK8<1) ? -9999. : AK8_maxSubJetCSV[iJetAK8[0]];            }, .axis_title="Leading AK8 jet - Max. SubJet CSV",    .def_range={0,1}});
  sh.AddNewFillParams("Jet2AK8BTagCSV",      { .nbin=  101, .bins={    0,    1.01}, .fill=[]   { return (nJetAK8<2) ? -9999. : AK8_maxSubJetCSV[iJetAK8[1]];            }, .axis_title="Subleading AK8 jet - Max. SubJet CSV", .def_range={0,1}});

  if (debug) std::cout<<"Analysis::define_histo_options: non-special fillparams ok"<<std::endl;

  // SPECIAL
  // Special Y/Z axis parameters:

  // Systematics
  sh.AddSpecial({ .name="Counts", .name_plus_1d="Syst", .axis="Events / bin", .axis_plus_1d="Systematics variation index"});
  sh.AddNewFillParams("Counts",                         { .nbin= 1+syst_nSyst, .bins={-0.5, syst_nSyst+0.5}, .fill=[&syst_index] { return syst_index; }, .axis_title="Events / bin"});

  // AK8 Jets
  sh.AddNewSpecialFillParams("WTagFakeRate",                { .nbin=2, .bins={-0.5,1.5}, .fill=[]   { return passTightWTag[i_FatJet];       }, .axis_title="W-tagging fake rate",           .def_range={0,2} });
  sh.AddNewSpecialFillParams("WMisTagRate",                 { .nbin=2, .bins={-0.5,1.5}, .fill=[]   { return passTightWTag[i_FatJet];       }, .axis_title="W-mistagging rate",             .def_range={0,2} });
  sh.AddNewSpecialFillParams("WMassTagFakeRate",            { .nbin=2, .bins={-0.5,1.5}, .fill=[]   { return passWMassTag[i_FatJet];        }, .axis_title="W mass-tagging fake rate",      .def_range={0,2} });
  sh.AddNewSpecialFillParams("W0BMassTagFakeRate",          { .nbin=2, .bins={-0.5,1.5}, .fill=[]   { return passWMassTag[i_FatJet];        }, .axis_title="W 0b mass-tagging fake rate",   .def_range={0,2} });
  sh.AddNewSpecialFillParams("WAntiTagFakeRate",            { .nbin=2, .bins={-0.5,1.5}, .fill=[]   { return passTightWAntiTag[i_FatJet];   }, .axis_title="W anti-tagging fake rate",      .def_range={0,2} });
  sh.AddNewSpecialFillParams("TopTagFakeRate",              { .nbin=2, .bins={-0.5,1.5}, .fill=[]   { return passHadTopTag[i_FatJet];       }, .axis_title="Top-tagging fake rate",         .def_range={0,2} });
  sh.AddNewSpecialFillParams("TopMisTagRate",               { .nbin=2, .bins={-0.5,1.5}, .fill=[]   { return passHadTopTag[i_FatJet];       }, .axis_title="Top-mistagging rate",           .def_range={0,2} });
  sh.AddNewSpecialFillParams("TopMassTagFakeRate",          { .nbin=2, .bins={-0.5,1.5}, .fill=[]   { return passHadTopMassTag[i_FatJet];   }, .axis_title="Top mass-tagging fake rate",    .def_range={0,2} });
  sh.AddNewSpecialFillParams("Top0BMassTagFakeRate",        { .nbin=2, .bins={-0.5,1.5}, .fill=[]   { return passHadTop0BMassTag[i_FatJet]; }, .axis_title="Top 0b mass-tagging fake rate", .def_range={0,2} });
  sh.AddNewSpecialFillParams("TopAntiTagFakeRate",          { .nbin=2, .bins={-0.5,1.5}, .fill=[]   { return passHadTop0BAntiTag[i_FatJet]; }, .axis_title="Top anti-tagging fake rate",    .def_range={0,2} });
  //sh.AddNewSpecialFillParams("MergedTopFraction",              { .nbin=    2, .bins={ -0.5,     1.5}, .fill=[]   { return top_Children_Within_Cone[i_FatJet]; }, .axis_title="Fraction of Merged Tops" });
  //sh.AddNewSpecialFillParams("TopTagEfficiency",               { .nbin=    2, .bins={ -0.5,     1.5}, .fill=[]   { return passHadTopTag[i_FatJet];            }, .axis_title="Top-tagging Efficiency" });
  //// Same with other JES correction
  sh.AddNewSpecialFillParams("WTagOtherFakeRate",           { .nbin=2, .bins={-0.5,1.5}, .fill=[]   { return passOtherTightWTag[i_FatJet];       }, .axis_title="W-tagging uncorr fake rate",           .def_range={0,2} });
  sh.AddNewSpecialFillParams("W0BMassTagOtherFakeRate",     { .nbin=2, .bins={-0.5,1.5}, .fill=[]   { return passOtherWMassTag[i_FatJet];        }, .axis_title="W 0b mass-tagging uncorr fake rate",   .def_range={0,2} });
  sh.AddNewSpecialFillParams("WAntiTagOtherFakeRate",       { .nbin=2, .bins={-0.5,1.5}, .fill=[]   { return passOtherTightWAntiTag[i_FatJet];   }, .axis_title="W anti-tagging uncorr fake rate",      .def_range={0,2} });
  sh.AddNewSpecialFillParams("TopTagOtherFakeRate",         { .nbin=2, .bins={-0.5,1.5}, .fill=[]   { return passOtherHadTopTag[i_FatJet];       }, .axis_title="Top-tagging L2L3 corr fake rate",         .def_range={0,2} });
  sh.AddNewSpecialFillParams("TopMassTagOtherFakeRate",     { .nbin=2, .bins={-0.5,1.5}, .fill=[]   { return passOtherHadTopMassTag[i_FatJet];   }, .axis_title="Top mass-tagging L2L3 corr fake rate",    .def_range={0,2} });
  sh.AddNewSpecialFillParams("Top0BMassTagOtherFakeRate",   { .nbin=2, .bins={-0.5,1.5}, .fill=[]   { return passOtherHadTop0BMassTag[i_FatJet]; }, .axis_title="Top 0b mass-tagging L2L3 corr fake rate", .def_range={0,2} });
  sh.AddNewSpecialFillParams("TopAntiTagOtherFakeRate",     { .nbin=2, .bins={-0.5,1.5}, .fill=[]   { return passOtherHadTop0BAntiTag[i_FatJet]; }, .axis_title="Top anti-tagging L2L3 corr fake rate",    .def_range={0,2} });

  // Photons
  //sh.AddNewSpecialFillParams("DirectFraction",       { .nbin=    2, .bins={ -0.5,     1.5}, .fill=[&d] { return d.Photon.isPromptDirect[i_Photon]==1; }, .axis_title="#splitline{Direct}{Direct+Fragmentation}",        .def_range={0,1} });
  // MC purity
  //sh.AddNewSpecialFillParams("PhotonPurity",         { .nbin=    2, .bins={ -0.5,     1.5}, .fill=[&d,this] {
  //      					  double isPrompt = -9999;
  //      					  if (!isData&&nPhotonSelect==1) isPrompt = d.Photon.isPromptDirect[iPhotonSelect[0]]==1||d.Photon.isPromptFrag[iPhotonSelect[0]]==1;
  //      					  return isPrompt;
  //      					}, .axis_title="Photon purity",        .def_range={0,1} });

  // Gen particle truth
  sh.AddNewSpecialFillParams("WTaggingEfficiency",          { .nbin=2, .bins={-0.5,1.5}, .fill=[]   { return genHadWPassHadWTag[i_GenPart];         }, .axis_title="Hadronic W-tagging Efficiency", .def_range={0,2} });
  sh.AddNewSpecialFillParams("HadTopTaggingEfficiency",     { .nbin=2, .bins={-0.5,1.5}, .fill=[]   { return genHadTopPassHadTopTag[i_GenPart];        }, .axis_title="Top-tagging Efficiency",        .def_range={0,2} });
  sh.AddNewSpecialFillParams("WMassTaggingEfficiency",      { .nbin=2, .bins={-0.5,1.5}, .fill=[]   { return genHadWPassHadWMassTag[i_GenPart];     }, .axis_title="Hadronic W mass-tagging Efficiency", .def_range={0,2} });
  sh.AddNewSpecialFillParams("HadTopMassTaggingEfficiency", { .nbin=2, .bins={-0.5,1.5}, .fill=[]   { return genHadTopPassHadTopMassTag[i_GenPart];    }, .axis_title="Top mass-tagging Efficiency",        .def_range={0,2} });
  sh.AddNewSpecialFillParams("LostLeptonRate",              { .nbin=2, .bins={-0.5,1.5}, .fill=[]   { return !genLepPassLepVeto[i_GenPart];        }, .axis_title="Lost lepton rate", .def_range={0,3} });
  sh.AddNewSpecialFillParams("LepTightNoIsoEfficiency",     { .nbin=2, .bins={-0.5,1.5}, .fill=[]   { return genLepPassLepTightNoIso[i_GenPart];  }, .axis_title="Tight lepton efficiency (no iso.)", .def_range={0,3} });
  sh.AddNewSpecialFillParams("LepTight2DEfficiency",        { .nbin=2, .bins={-0.5,1.5}, .fill=[]   { return genLepPassLepTight2D[i_GenPart];     }, .axis_title="Tight lepton efficiency", .def_range={0,3} });
  //sh.AddNewSpecialFillParams("JetFindingEfficiency",           { .nbin=    2, .bins={ -0.5,     1.5}, .fill=[]   { return has_Matched_Jet[i_GenPart];                   }, .axis_title="Jet finding Efficiency" });
  //sh.AddNewSpecialFillParams("TopFindingEfficiency",           { .nbin=    2, .bins={ -0.5,     1.5}, .fill=[]   { return has_Matched_Tagged_Jet[i_GenPart];            }, .axis_title="Top finding Efficiency" });

  // Event vairables
  sh.AddNewSpecialFillParams("SignalSelectionEfficiency",    { .nbin=    2, .bins={ -0.5,     1.5}, .fill=[]   { return pass_all_cuts['S'];   }, .axis_title="Signal Selection Efficiency - W ana"});
  sh.AddNewSpecialFillParams("SignalSignificance_T5ttcc",    { .nbin=    2, .bins={ -0.5,     1.5}, .fill=[]   { return Bkg_T5ttcc_opt.index; }, .axis_title="S/#sqrt{S+B} - T5ttcc", .def_range={0,10}});
  sh.AddNewSpecialFillParams("SignalSignificance_T5qqqqVV",    { .nbin=    2, .bins={ -0.5,     1.5}, .fill=[]   { return Bkg_T5qqqqVV_opt.index; }, .axis_title="S/#sqrt{S+B} - T5qqqqVV", .def_range={0,10}});
  //sh.AddNewSpecialFillParams("SignalSignificance_T5tttt",    { .nbin=    2, .bins={ -0.5,     1.5}, .fill=[]   { return Bkg_T5tttt_opt.index; }, .axis_title="S/#sqrt{S+B} - T5tttt", .def_range={0,10}});
  sh.AddNewSpecialFillParams("SignalSignificance_T1tttt",    { .nbin=    2, .bins={ -0.5,     1.5}, .fill=[]   { return Bkg_T1tttt_opt.index; }, .axis_title="S/#sqrt{S+B} - T1tttt", .def_range={0,10}});
  sh.AddNewSpecialFillParams("SignalSignificance_TChiWZ",    { .nbin=    2, .bins={ -0.5,     1.5}, .fill=[]   { return Bkg_TChiWZ_opt.index; }, .axis_title="S/#sqrt{S+B} - TChiWZ", .def_range={0,10}});
  //sh.AddNewSpecialFillParams("SignalSignificance_T1ttbb",    { .nbin=    2, .bins={ -0.5,     1.5}, .fill=[]   { return Bkg_T1ttbb_opt.index; }, .axis_title="S/#sqrt{S+B} - T1ttbb", .def_range={0,10}});
  //sh.AddNewSpecialFillParams("SignalSignificance_T1ttbb_dM5to25", { .nbin=    2, .bins={ -0.5,     1.5}, .fill=[]   { return Bkg_T1ttbb_dM5to25_opt.index; }, .axis_title="S/#sqrt{S+B} - T1ttbb (5<#DeltaM<25)", .def_range={0,10}});
  sh.AddNewSpecialFillParams("SignalSignificance_T2tt",      { .nbin=    2, .bins={ -0.5,     1.5}, .fill=[]   { return Bkg_T2tt_opt.index;   }, .axis_title="S/#sqrt{S+B} - T2tt",   .def_range={0,10}});

  sh.AddNewSpecialFillParams("HLTEff_AK8PFJet360",             { .nbin=    2, .bins={ -0.5,     1.5}, .fill=[&d] { return d.HLT_AK8PFJet360_TrimMass30;                   }, .axis_title="#epsilon_{HLT_AK8PFJet360_TrimMass30}",                   .def_range={0,1} });
  sh.AddNewSpecialFillParams("HLTEff_AK8PFJet450",             { .nbin=    2, .bins={ -0.5,     1.5}, .fill=[&d] { return d.HLT_AK8PFJet450;                              }, .axis_title="#epsilon_{HLT_AK8PFJet450}",                              .def_range={0,1} });
  sh.AddNewSpecialFillParams("HLTEff_AK8PFHT750_TrimMass50",   { .nbin=    2, .bins={ -0.5,     1.5}, .fill=[&d] { return d.HLT_AK8PFHT750_TrimMass50;          }, .axis_title="#epsilon_{HLT_AK8PFHT750_TrimMass50}",          .def_range={0,1} });
  sh.AddNewSpecialFillParams("HLTEff_PFHT1050",                 { .nbin=    2, .bins={ -0.5,     1.5}, .fill=[&d] { return d.HLT_PFHT1050==1;           }, .axis_title="#epsilon_{HLT_PFHT1050}",                                  .def_range={0,1} });
  //sh.AddNewSpecialFillParams("HLTEff_AK8DiPFJet250_200",       { .nbin=    2, .bins={ -0.5,     1.5}, .fill=[&d] { return d.HLT_AK8DiPFJet250_200_TrimMass30_BTagCSV_p20; }, .axis_title="#epsilon_{HLT_AK8DiPFJet250_200_TrimMass30_BTagCSV_p20}", .def_range={0,1} });
  //sh.AddNewSpecialFillParams("HLTEff_Rsq0p25",                 { .nbin=    2, .bins={ -0.5,     1.5}, .fill=[&d] { return d.HLT_Rsq0p25;                                  }, .axis_title="#epsilon_{HLT_Rsq0p25}",                                  .def_range={0,1} });
  //sh.AddNewSpecialFillParams("HLTEff_RsqMR270_Rsq0p09_MR200",  { .nbin=    2, .bins={ -0.5,     1.5}, .fill=[&d] { return d.HLT_RsqMR270_Rsq0p09_MR200;                   }, .axis_title="#epsilon_{HLT_RsqMR270_Rsq0p09_MR200}",                   .def_range={0,1} });
  sh.AddNewSpecialFillParams("HLTEff_AK8PFHT750orPFHT1050",     { .nbin=    2, .bins={ -0.5,     1.5}, .fill=[&d] { return d.HLT_AK8PFHT750_TrimMass50==1 || d.HLT_PFHT1050==1;                }, .axis_title="#epsilon_{HLT_AK8PFHT750 OR HLT_PFHT1050}",  .def_range={0,1} });
  sh.AddNewSpecialFillParams("HLTEff_PFJet450orPFHT1050",       { .nbin=    2, .bins={ -0.5,     1.5}, .fill=[&d] { return d.HLT_PFJet450==1 || d.HLT_PFHT1050==1;                                       }, .axis_title="#epsilon_{HLT_PFJet450 OR HLT_PFHT1050}",    .def_range={0,1} });
  sh.AddNewSpecialFillParams("HLTEff_AK8PFJet450orPFHT1050",    { .nbin=    2, .bins={ -0.5,     1.5}, .fill=[&d] { return d.HLT_AK8PFJet450==1 || d.HLT_PFHT1050==1;                                    }, .axis_title="#epsilon_{HLT_AK8PFJet450 OR HLT_PFHT1050}", .def_range={0,1} });
  sh.AddNewSpecialFillParams("HLTEff_AK8PFJet450orAK8PFHT750", { .nbin=    2, .bins={ -0.5,     1.5}, .fill=[&d] { return d.HLT_AK8PFJet450==1 || d.HLT_AK8PFHT750_TrimMass50==1;                                    }, .axis_title="#epsilon_{HLT_AK8PFJet450 OR HLT_AK8PFHT750}", .def_range={0,1} });
  sh.AddNewSpecialFillParams("HLTEff_AK8PFJet360orPFHT1050",    { .nbin=    2, .bins={ -0.5,     1.5}, .fill=[&d] { return d.HLT_AK8PFJet360_TrimMass30==1 || d.HLT_PFHT1050==1;                         }, .axis_title="#epsilon_{HLT_AK8PFJet360 OR HLT_PFHT1050}",     .def_range={0,1} });
  sh.AddNewSpecialFillParams("HLTEff_AK8PFJet360orAK8PFHT750", { .nbin=    2, .bins={ -0.5,     1.5}, .fill=[&d] { return d.HLT_AK8PFJet360_TrimMass30==1 || d.HLT_AK8PFHT750_TrimMass50==1; }, .axis_title="#epsilon_{HLT_AK8PFJet360 OR HLT_AK8PFHT750}",  .def_range={0,1} });
  sh.AddNewSpecialFillParams("HLTEff_PFHT1050",                  { .nbin=    2, .bins={ -0.5,     1.5}, .fill=[&d] { return d.HLT_PFHT1050==1;                             }, .axis_title="#epsilon_{HLT_PFHT1050}",                 .def_range={0,1} });
  sh.AddNewSpecialFillParams("HLTEff_PFMET120_PFMHT120",         { .nbin=    2, .bins={ -0.5,     1.5}, .fill=[&d] { return d.HLT_PFMET120_PFMHT120_IDTight==1;            }, .axis_title="#epsilon_{HLT_PFMET120_PFMHT120}",        .def_range={0,1} });
  sh.AddNewSpecialFillParams("HLTEff_PFMETNoMu120_PFMHTNoMu120", { .nbin=    2, .bins={ -0.5,     1.5}, .fill=[&d] { return d.HLT_PFMETNoMu120_PFMHTNoMu120_IDTight==1;    }, .axis_title="#epsilon_{HLT_PFMETNoMu120_PFMHTNoMu120}",.def_range={0,1} });
  sh.AddNewSpecialFillParams("HLTEff_PFMETTypeOne120_PFMHT120",  { .nbin=    2, .bins={ -0.5,     1.5}, .fill=[&d] { return d.HLT_PFMETTypeOne120_PFMHT120_IDTight==1;     }, .axis_title="#epsilon_{HLT_PFMETTypeOne120_PFMHT120}", .def_range={0,1} });
  sh.AddNewSpecialFillParams("HLTEff_PFHT500_PFMET100_PFMHT100", { .nbin=    2, .bins={ -0.5,     1.5}, .fill=[&d] { return d.HLT_PFHT500_PFMET100_PFMHT100_IDTight==1;    }, .axis_title="#epsilon_{HLT_PFHT500_PFMET100_PFMHT100}",.def_range={0,1} });
  sh.AddNewSpecialFillParams("HLTEff_PFHT700_PFMET85_PFMHT85",   { .nbin=    2, .bins={ -0.5,     1.5}, .fill=[&d] { return d.HLT_PFHT700_PFMET85_PFMHT85_IDTight==1;      }, .axis_title="#epsilon_{HLT_PFHT700_PFMET85_PFMHT85}",  .def_range={0,1} });
  sh.AddNewSpecialFillParams("HLTEff_PFHT800_PFMET75_PFMHT75",   { .nbin=    2, .bins={ -0.5,     1.5}, .fill=[&d] { return d.HLT_PFHT800_PFMET75_PFMHT75_IDTight==1;      }, .axis_title="#epsilon_{HLT_PFHT800_PFMET75_PFMHT75}",  .def_range={0,1} });
  sh.AddNewSpecialFillParams("HLTEff_HT_MET_or_HT",           { .nbin=    2, .bins={ -0.5,     1.5}, .fill=[&d] {
                                                                   return 
                                                                   d.HLT_PFHT1050==1 ||
                                                                   //d.HLT_PFMET120_PFMHT120_IDTight==1 ||
                                                                   //d.HLT_PFMETNoMu120_PFMHTNoMu120_IDTight==1 ||
                                                                   //d.HLT_PFMETTypeOne120_PFMHT120_IDTight==1 ||
                                                                   d.HLT_PFHT500_PFMET100_PFMHT100_IDTight==1 || 
                                                                   d.HLT_PFHT700_PFMET85_PFMHT85_IDTight==1 ||
                                                                   d.HLT_PFHT800_PFMET75_PFMHT75_IDTight==1;
                                                                 }, .axis_title="#epsilon_{HT*_MET* OR HT1050}",               .def_range={0,1} });
  sh.AddNewSpecialFillParams("HLTEff_MET_or_HT_MET_or_HT",    { .nbin=    2, .bins={ -0.5,     1.5}, .fill=[&d] { 
                                                                   return 
                                                                   d.HLT_PFHT1050==1 ||
                                                                   d.HLT_PFMET120_PFMHT120_IDTight==1 ||
                                                                   //d.HLT_PFMETNoMu120_PFMHTNoMu120_IDTight==1 ||
                                                                   //d.HLT_PFMETTypeOne120_PFMHT120_IDTight==1 ||
                                                                   d.HLT_PFHT500_PFMET100_PFMHT100_IDTight==1 || 
                                                                   d.HLT_PFHT700_PFMET85_PFMHT85_IDTight==1 ||
                                                                   d.HLT_PFHT800_PFMET75_PFMHT75_IDTight==1;
                                                                 }, .axis_title="#epsilon_{MET120 OR HT*_MET* OR HT1050}",     .def_range={0,1} });
  sh.AddNewSpecialFillParams("HLTEff_AllMET_or_HT_MET_or_HT", { .nbin=    2, .bins={ -0.5,     1.5}, .fill=[&d] { 
                                                                   return 
                                                                   d.HLT_PFHT1050==1 ||
                                                                   d.HLT_PFMET120_PFMHT120_IDTight==1 ||
                                                                   d.HLT_PFMETNoMu120_PFMHTNoMu120_IDTight==1 ||
                                                                   d.HLT_PFMETTypeOne120_PFMHT120_IDTight==1 ||
                                                                   d.HLT_PFHT500_PFMET100_PFMHT100_IDTight==1 || 
                                                                   d.HLT_PFHT700_PFMET85_PFMHT85_IDTight==1 ||
                                                                   d.HLT_PFHT800_PFMET75_PFMHT75_IDTight==1;    
                                                                 }, .axis_title="#epsilon_{AllMET120 OR HT*_MET* OR HT1050}",  .def_range={0,1} });
  // Leptonic triggers
  sh.AddNewSpecialFillParams("HLTEff_Mu15_HT450",      { .nbin=    2, .bins={ -0.5,     1.5}, .fill=[&d] { return d.HLT_Mu15_IsoVVVL_PFHT450==1;      }, .axis_title="#epsilon_{Mu15_HT450}",  .def_range={0,1} });
  sh.AddNewSpecialFillParams("HLTEff_IsoMu27",         { .nbin=    2, .bins={ -0.5,     1.5}, .fill=[&d] { return d.HLT_IsoMu27==1;                   }, .axis_title="#epsilon_{IsoMu27}",     .def_range={0,1} });
  sh.AddNewSpecialFillParams("HLTEff_Mu50",            { .nbin=    2, .bins={ -0.5,     1.5}, .fill=[&d] { return d.HLT_Mu50==1;                      }, .axis_title="#epsilon_{Mu50}",        .def_range={0,1} });
  sh.AddNewSpecialFillParams("HLTEff_Ele15_HT450",     { .nbin=    2, .bins={ -0.5,     1.5}, .fill=[&d] { return d.HLT_Ele15_IsoVVVL_PFHT450==1;     }, .axis_title="#epsilon_{Ele15_HT450}", .def_range={0,1} });
  sh.AddNewSpecialFillParams("HLTEff_Ele35",           { .nbin=    2, .bins={ -0.5,     1.5}, .fill=[&d] { return d.HLT_Ele35_WPTight_Gsf==1;         }, .axis_title="#epsilon_{Ele35}",       .def_range={0,1} });
  sh.AddNewSpecialFillParams("HLTEff_Ele115",          { .nbin=    2, .bins={ -0.5,     1.5}, .fill=[&d] { return d.HLT_Ele115_CaloIdVT_GsfTrkIdT==1; }, .axis_title="#epsilon_{Ele115}",      .def_range={0,1} });
  sh.AddNewSpecialFillParams("HLTEff_IsoMu27_or_Mu50", { .nbin=    2, .bins={ -0.5,     1.5}, .fill=[&d] { return 
                                                                                                                   d.HLT_IsoMu27==1 ||
                                                                                                                   d.HLT_Mu50==1;
                                                                  }, .axis_title="#epsilon_{IsoMu27 OR Mu50}",                .def_range={0,1} });
  sh.AddNewSpecialFillParams("HLTEff_IsoMu27_or_Mu50_or_Mu15_HT450",  { .nbin=    2, .bins={ -0.5,     1.5}, .fill=[&d] { return
                                                                                                                   d.HLT_IsoMu27==1 ||
                                                                                                                   d.HLT_Mu50==1 ||
                                                                                                                   d.HLT_Mu15_IsoVVVL_PFHT450==1;
                                                                  }, .axis_title="#epsilon_{IsoMu27 OR Mu50 OR Mu15_HT450}",  .def_range={0,1} });
  sh.AddNewSpecialFillParams("HLTEff_Ele35_or_Ele115",                { .nbin=    2, .bins={ -0.5,     1.5}, .fill=[&d] { return 
                                                                                                                   d.HLT_Ele35_WPTight_Gsf==1 ||
                                                                                                                   d.HLT_Ele115_CaloIdVT_GsfTrkIdT==1;
                                                                  }, .axis_title="#epsilon_{Ele35 OR Ele115}",                .def_range={0,1} });
  sh.AddNewSpecialFillParams("HLTEff_Ele35_or_Ele115_or_Ele15_HT450", { .nbin=    2, .bins={ -0.5,     1.5}, .fill=[&d] { return 
                                                                                                                   d.HLT_Ele35_WPTight_Gsf==1 ||
                                                                                                                   d.HLT_Ele115_CaloIdVT_GsfTrkIdT==1 ||
                                                                                                                   d.HLT_Ele15_IsoVVVL_PFHT450==1;
                                                                  }, .axis_title="#epsilon_{Ele35 OR Ele115 OR Ele15_HT450}", .def_range={0,1} });

  if (debug) std::cout<<"Analysis::define_histo_options: fillparams ok"<<std::endl;
}


//_______________________________________________________
//                 List of Histograms

//_______________________________________________________
//              Define Histograms here
void
Analysis::init_analysis_histos(const unsigned int& syst_nSyst, const unsigned int& syst_index)
{

  //__________________________________
  //        Define Smarthistos
  //__________________________________

  bool systematics = 1;

  std::string s = "";
  std::string c = "";
  if (systematics) {
    s = "syst ";
    c = "Counts_vs_";
  }

  // Define histo types (for different object to loop on, and different cuts to apply)
  sh.AddHistoType("ele",       "Electrons");
  sh.AddHistoType("ele select", "Electrons");
  sh.AddHistoType("ele veto","Veto electrons");
  sh.AddHistoType("ele tight noiso", "Electrons");
  sh.AddHistoType("syst ele",     "Electrons");
  sh.AddHistoType("syst ele select", "Electrons");
  sh.AddHistoType("syst ele veto","Veto electrons");
  sh.AddHistoType("mu",      "Muons");
  sh.AddHistoType("mu select",      "Muons");
  sh.AddHistoType("mu veto", "Veto muons");
  sh.AddHistoType("mu tight noiso", "Muons");
  sh.AddHistoType("syst mu",      "Muons");
  sh.AddHistoType("syst mu select",      "Muons");
  sh.AddHistoType("syst mu veto", "Veto muons");
  sh.AddHistoType("tau veto","Veto taus");
  sh.AddHistoType("syst tau veto","Veto taus");
  sh.AddHistoType("pho",     "Photons");
  sh.AddHistoType("prepho",  "Pre-selected photons");
  sh.AddHistoType("syst pho",     "Photons");
  sh.AddHistoType("syst prepho",  "Pre-selected photons");
  sh.AddHistoType("AK4",     "Jets");
  sh.AddHistoType("syst AK4",     "Jets");
  sh.AddHistoType("b",       "b-tagged jets");
  sh.AddHistoType("b loose", "Loose b-tagged jets");
  sh.AddHistoType("syst b",       "b-tagged jets");
  sh.AddHistoType("syst b loose", "Loose b-tagged jets");
  sh.AddHistoType("AK8",     "AK8 jets");
  sh.AddHistoType("syst AK8",     "AK8 jets");
  sh.AddHistoType("mW",      "Mass-tagged Ws");
  sh.AddHistoType("aW",      "Anti-tagged Ws");
  sh.AddHistoType("W",       "Tagged Ws");
  sh.AddHistoType("syst mW",      "Mass-tagged Ws");
  sh.AddHistoType("syst aW",      "Anti-tagged Ws");
  sh.AddHistoType("syst W",       "Tagged Ws");
  sh.AddHistoType("mTop",    "Mass-tagged tops");
  sh.AddHistoType("MTop",    "Mass-tagged tops");
  sh.AddHistoType("aTop",    "Anti-tagged tops");
  sh.AddHistoType("Top",     "Tagged tops");
  sh.AddHistoType("syst mTop",    "Mass-tagged tops");
  sh.AddHistoType("syst MTop",    "Mass-tagged tops");
  sh.AddHistoType("syst aTop",    "Anti-tagged tops");
  sh.AddHistoType("syst Top",     "Tagged tops");
  sh.AddHistoType("hadtop", "Tops (had.)");
  sh.AddHistoType("leptop", "Tops (lep.)");
  sh.AddHistoType("leptop cand", "Top candidates (lep.)");
  sh.AddHistoType("hadw",   "Ws (had.)");
  sh.AddHistoType("hadz",   "Zs (had.)");
  sh.AddHistoType("syst hadtop", "Tops (had.)");
  sh.AddHistoType("syst leptop", "Tops (lep.)");
  sh.AddHistoType("syst leptop cand", "Top candidates (lep.)");
  sh.AddHistoType("syst hadw",   "Ws (had.)");
  sh.AddHistoType("syst hadz",   "Zs (had.)");
  sh.AddHistoType("gen lep",    "Gen-leptons");
  sh.AddHistoType("gen hadW",   "Gen-Ws (had.)");
  sh.AddHistoType("gen top",    "Gen-tops");
  sh.AddHistoType("gen hadtop", "Gen-tops (had.)");
  sh.AddHistoType("gen leptop", "Gen-tops (lep.)");
  sh.AddHistoType("evt",      "Events / bin");
  sh.AddHistoType("syst evt", "Events / bin");

  // Histo options
  std::string d = "HISTE1";
  // Control region stack plots (only data)
  std::string o_stk_d = "LogSumw2Stack1AddRatioTwoCol78AddIntApproval15";
  std::string o_stk_s = "LogSumw2Stack1AddRatioTwoCol78AddIntApproval45";
  std::string O_stk_d = "LogSumw2Stack1AddRatioTwoCol78Approval15";
  std::string O_stk_s = "LogSumw2Stack1AddRatioTwoCol78Approval45";
  O_stk_d = o_stk_d;
  O_stk_s = o_stk_s;
  // Signal region stack plots (data + N signal)
  std::string o_stk_d_S = "LogSumw2Stack6AddRatioTwoCol78AddIntApproval15";
  std::string o_stk_s_S = "LogSumw2Stack6AddRatioTwoCol78AddIntApproval45";
  std::string O_stk_d_S = "LogSumw2Stack6AddRatioTwoCol78Approval15";
  std::string O_stk_s_S = "LogSumw2Stack6AddRatioTwoCol78Approval45";
  O_stk_d_S = o_stk_d_S;
  O_stk_s_S = o_stk_s_S;
  std::string o_stk_d_T = "LogSumw2Stack4AddRatioTwoCol58AddIntApproval15";
  std::string o_stk_s_T = "LogSumw2Stack4AddRatioTwoCol58AddIntApproval45";
  std::string o_stk_d_V = "LogSumw2Stack3AddRatioTwoCol48AddIntApproval15";
  std::string o_stk_s_V = "LogSumw2Stack3AddRatioTwoCol48AddIntApproval45";
  std::string o_1or2d_d = "Sumw2Approval15";
  std::string o_1or2d_s = "Sumw2Approval45";
  std::string o_norm_d = "Sumw2NormApproval15";
  std::string o_norm_s = "Sumw2NormApproval45";

  std::vector<double> r_Stk4 = {0,0, 1.01e-2,1e4,  0.3,0.86};
  std::vector<double> r_Stk5 = {0,0, 1.01e-2,1e5,  0.3,0.86};
  std::vector<double> r_Stk6 = {0,0, 1.01e-2,1e6,  0.3,0.86};
  std::vector<double> r_Stk7 = {0,0, 1.01e-2,1e7,  0.3,0.86};
  std::vector<double> r_Stk8 = {0,0, 1.01e-2,1e8,  0.3,0.86};
  std::vector<double> r_Stk9 = {0,0, 1.01e-1,1e9,  0.3,0.86};
  std::string Stack = "StackPlot";

  // -------------------------------------------------------------------------
  //                                   Trigger

  std::vector<std::string> standard_plots = {"HT", "HTFine", "METFine", "MET", "HTMET", "MRFine", "MR", "R2Fine", "R2", "MRR2"};
  
  sh.SetHistoWeights({ [] { return 1; } });
  
  // Hadronic triggers
  for (auto plot : {"HadronicMeasurements", "HadronicMeasurementsNoR2"}) {
    std::string cut = "Baseline";
    if (std::string(plot)=="HadronicMeasurementsNoR2") cut = "BaselineNoR2";
    for (auto std_plot : standard_plots)
      sh.AddHistos("evt", { .fill=std_plot,             .pfs={plot,cut},          .cuts={}, .draw="HIST", .opt=o_1or2d_d+"LogTwoCol33", .ranges={0,0, 1e-1,1e8, 0.35,0.86} });
    sh.AddHistos("evt", { .fill="RazorNoPhoBins",       .pfs={plot,cut},          .cuts={}, .draw="HIST", .opt=o_1or2d_d+"LogTwoCol33", .ranges={0,0, 1e-1,1e8, 0.35,0.86} });
    sh.AddHistos("evt", { .fill="HT2DBins",             .pfs={plot,cut},          .cuts={}, .draw="HIST", .opt=o_1or2d_d+"LogTwoCol33", .ranges={0,0, 1e-1,1e8, 0.35,0.86} });
    sh.AddHistos("evt", { .fill="MET2DBins",            .pfs={plot,cut},          .cuts={}, .draw="HIST", .opt=o_1or2d_d+"LogTwoCol33", .ranges={0,0, 1e-1,1e8, 0.35,0.86} });
    sh.AddHistos("evt", { .fill="HTMETPrev",            .pfs={plot,cut},          .cuts={}, .draw="HIST", .opt=o_1or2d_d+"LogTwoCol33", .ranges={0,0, 1e-1,1e8, 0.35,0.86} });
    sh.AddHistos("evt", { .fill="METFine_vs_HTFine",    .pfs={plot,cut},          .cuts={}, .draw="COLZ", .opt=o_1or2d_d+"Log",         .ranges={0,0, 0,0} });
    sh.AddHistos("evt", { .fill="MET_vs_HT",            .pfs={plot,cut},          .cuts={}, .draw="COLZ", .opt=o_1or2d_d+"Log",         .ranges={0,0, 0,0} });
    sh.AddHistos("evt", { .fill="MET2DBins_vs_HT2DBins",.pfs={plot,cut},          .cuts={}, .draw="COLZ", .opt=o_1or2d_d+"Log",         .ranges={0,0, 0,0} });
  
    //sh.AddHistos("evt", { .fill="HTJet1AK8Pt",          .pfs={plot,cut},          .cuts={}, .draw="HIST", .opt=o_1or2d_d+"TwoCol33", .ranges={0,0, 0,0, 0.35,0.86} });
    //sh.AddHistos("evt", { .fill="HTJet1AK8PtLow",       .pfs={plot,cut},          .cuts={}, .draw="HIST", .opt=o_1or2d_d+"TwoCol33", .ranges={0,0, 0,0, 0.35,0.86} });
    //sh.AddHistos("evt", { .fill="HTJet1AK8PtHigh",      .pfs={plot,cut},          .cuts={}, .draw="HIST", .opt=o_1or2d_d+"TwoCol33", .ranges={0,0, 0,0, 0.35,0.86} });
    //sh.AddHistos("evt", { .fill="HTNoLep",              .pfs={"Jet1AK8PtBins",plot,cut},          .cuts={}, .draw="HIST", .opt=o_1or2d_d+"TwoCol66", .ranges={0,0, 0,0, 0.35,0.86} });
    //sh.AddHistos("evt", { .fill="Jet1AK8Pt",            .pfs={"HTBins",       plot,cut},          .cuts={}, .draw="HIST", .opt=o_1or2d_d+"TwoCol44", .ranges={0,0, 0,0, 0.35,0.86} });
    //sh.AddHistos("evt", { .fill="Jet1AK8Pt_vs_HTFine",  .pfs={plot,cut},          .cuts={}, .draw="COLZ", .opt=o_1or2d_d, .ranges={0,0, 0,0} });
    //sh.AddHistos("evt", { .fill="Jet1AK8Pt_vs_HTNoLep", .pfs={plot,cut},          .cuts={}, .draw="COLZ", .opt=o_1or2d_d, .ranges={0,0, 0,0} });
    //for (auto njet_bin : {"NJet45"}) {
    //  sh.AddHistos("evt", { .fill="HTJet1AK8Pt",          .pfs={plot,cut,njet_bin}, .cuts={}, .draw="HIST", .opt=o_1or2d_d+"TwoCol33", .ranges={0,0, 0,0, 0.35,0.86} });
    //  sh.AddHistos("evt", { .fill="HTJet1AK8PtLow",       .pfs={plot,cut,njet_bin}, .cuts={}, .draw="HIST", .opt=o_1or2d_d+"TwoCol33", .ranges={0,0, 0,0, 0.35,0.86} });
    //  sh.AddHistos("evt", { .fill="HTJet1AK8PtHigh",      .pfs={plot,cut,njet_bin}, .cuts={}, .draw="HIST", .opt=o_1or2d_d+"TwoCol33", .ranges={0,0, 0,0, 0.35,0.86} });
    //  sh.AddHistos("evt", { .fill="HTFine",               .pfs={"Jet1AK8PtBins",plot,cut,njet_bin}, .cuts={}, .draw="HIST", .opt=o_1or2d_d+"TwoCol66", .ranges={0,0, 0,0, 0.35,0.86} });
    //  sh.AddHistos("evt", { .fill="HTNoLep",              .pfs={"Jet1AK8PtBins",plot,cut,njet_bin}, .cuts={}, .draw="HIST", .opt=o_1or2d_d+"TwoCol66", .ranges={0,0, 0,0, 0.35,0.86} });
    //  sh.AddHistos("evt", { .fill="Jet1AK8Pt",            .pfs={"HTBins",       plot,cut,njet_bin}, .cuts={}, .draw="HIST", .opt=o_1or2d_d+"TwoCol44", .ranges={0,0, 0,0, 0.35,0.86} });
    //  sh.AddHistos("evt", { .fill="Jet1AK8Pt_vs_HTFine",  .pfs={plot,cut,njet_bin}, .cuts={}, .draw="COLZ", .opt=o_1or2d_d, .ranges={0,0, 0,0} });
    //  sh.AddHistos("evt", { .fill="Jet1AK8Pt_vs_HTNoLep", .pfs={plot,cut,njet_bin}, .cuts={}, .draw="COLZ", .opt=o_1or2d_d, .ranges={0,0, 0,0} });
    //}
    for (auto trigger : std::vector<std::string>({"HLTEff_PFHT1050", "HLTEff_PFMET120_PFMHT120", "HLTEff_PFMETNoMu120_PFMHTNoMu120", "HLTEff_PFMETTypeOne120_PFMHT120", "HLTEff_PFHT500_PFMET100_PFMHT100", "HLTEff_PFHT700_PFMET85_PFMHT85", "HLTEff_PFHT800_PFMET75_PFMHT75", "HLTEff_HT_MET_or_HT", "HLTEff_MET_or_HT_MET_or_HT", "HLTEff_AllMET_or_HT_MET_or_HT"})) {
      for (auto std_plot : standard_plots)
        sh.AddHistos("evt", { .fill=trigger+"_vs_"+std_plot,             .pfs={                plot,cut}, .cuts={}, .draw="PE1",  .opt=o_1or2d_d+"TwoCol33", .ranges={0,0, 0,1, 0.5,0.5} });
      sh.AddHistos("evt", { .fill=trigger+"_vs_Bin",                     .pfs={                plot,cut}, .cuts={}, .draw="PE1",  .opt=o_1or2d_d+"TwoCol33", .ranges={0,0, 0,1, 0.5,0.5} });
      sh.AddHistos("evt", { .fill=trigger+"_vs_RazorNoPhoBins",          .pfs={                plot,cut}, .cuts={}, .draw="PE1",  .opt=o_1or2d_d+"TwoCol33", .ranges={0,0, 0,1, 0.5,0.5} });
      sh.AddHistos("evt", { .fill=trigger+"_vs_HT2DBins",                .pfs={                plot,cut}, .cuts={}, .draw="PE1",  .opt=o_1or2d_d+"TwoCol33", .ranges={0,0, 0,1, 0.5,0.53} });
      sh.AddHistos("evt", { .fill=trigger+"_vs_MET2DBins",               .pfs={                plot,cut}, .cuts={}, .draw="PE1",  .opt=o_1or2d_d+"TwoCol33", .ranges={0,0, 0,1, 0.5,0.53} });
      sh.AddHistos("evt", { .fill=trigger+"_vs_HTMET",                   .pfs={                plot,cut}, .cuts={}, .draw="PE1",  .opt=o_1or2d_d+"TwoCol33", .ranges={0,0, 0,1, 0.5,0.53} });
      sh.AddHistos("evt", { .fill=trigger+"_vs_HT1MET",                  .pfs={                plot,cut}, .cuts={}, .draw="PE1",  .opt=o_1or2d_d+"TwoCol33", .ranges={0,0, 0,1, 0.5,0.53} });
      sh.AddHistos("evt", { .fill=trigger+"_vs_HT2MET",                  .pfs={                plot,cut}, .cuts={}, .draw="PE1",  .opt=o_1or2d_d+"TwoCol33", .ranges={0,0, 0,1, 0.5,0.53} });
      sh.AddHistos("evt", { .fill=trigger+"_vs_HT3MET",                  .pfs={                plot,cut}, .cuts={}, .draw="PE1",  .opt=o_1or2d_d+"TwoCol33", .ranges={0,0, 0,1, 0.5,0.53} });
      sh.AddHistos("evt", { .fill=trigger+"_vs_HTMETPrev",               .pfs={                plot,cut}, .cuts={}, .draw="PE1",  .opt=o_1or2d_d+"TwoCol33", .ranges={0,0, 0,1, 0.5,0.53} });
      //sh.AddHistos("evt", { .fill=trigger+"_vs_HTJet1AK8Pt",             .pfs={                plot,cut}, .cuts={}, .draw="PE1",  .opt=o_1or2d_d+"TwoCol33DoubleX", .ranges={0,0, 0,1.0, 0.6,0.45} });
      //sh.AddHistos("evt", { .fill=trigger+"_vs_RazorBins",               .pfs={                plot,cut}, .cuts={}, .draw="PE1",  .opt=o_1or2d_d+"TwoCol33", .ranges={0,0, 0,1, 0.5,0.5} });
      //sh.AddHistos("evt", { .fill=trigger+"_vs_R2_vs_MR",                .pfs={                plot,cut}, .cuts={}, .draw="COLZ", .opt=o_1or2d_d+"TwoCol33", .ranges={0,0, 0,0, 0,1} });
      //sh.AddHistos("evt", { .fill=trigger+"_vs_Jet1AK8PtBins_vs_HT",     .pfs={                plot,cut}, .cuts={}, .draw="COLZ", .opt=o_1or2d_d+"TwoCol33", .ranges={0,0, 0,0, 0,1} });
      //sh.AddHistos("evt", { .fill=trigger+"_vs_Jet1AK8Mass_vs_HT",       .pfs={                plot,cut}, .cuts={}, .draw="COLZ", .opt=o_1or2d_d+"TwoCol33", .ranges={0,0, 0,0, 0,1} });
      //sh.AddHistos("evt", { .fill=trigger+"_vs_mW1Mass_vs_HT",           .pfs={                plot,cut}, .cuts={}, .draw="COLZ", .opt=o_1or2d_d+"TwoCol33", .ranges={0,0, 0,0, 0,1} });
      //sh.AddHistos("evt", { .fill=trigger+"_vs_HTNoLep",                 .pfs={                plot,cut}, .cuts={}, .draw="PE1",  .opt=o_1or2d_d+"TwoCol33", .ranges={0,2000, 0,1, 0.5,0.53} });
      //sh.AddHistos("evt", { .fill=trigger+"_vs_OnlineHT",                .pfs={                plot,cut}, .cuts={}, .draw="PE1",  .opt=o_1or2d_d+"TwoCol33", .ranges={0,2000, 0,1, 0.5,0.53} });
      //sh.AddHistos("evt", { .fill=trigger+"_vs_Jet1AK8Mass",             .pfs={                plot,cut}, .cuts={}, .draw="PE1",  .opt=o_1or2d_d+"TwoCol33", .ranges={0,0, 0,1, 0.5,0.5} });
      //sh.AddHistos("evt", { .fill=trigger+"_vs_Jet1AK8Pt",               .pfs={                plot,cut}, .cuts={}, .draw="PE1",  .opt=o_1or2d_d+"TwoCol33", .ranges={0,0, 0,1, 0.5,0.5} });
      //sh.AddHistos("evt", { .fill=trigger+"_vs_mW1Mass",                 .pfs={                plot,cut}, .cuts={}, .draw="PE1",  .opt=o_1or2d_d+"TwoCol33", .ranges={0,0, 0,1, 0.5,0.5} });
      //sh.AddHistos("evt", { .fill=trigger+"_vs_HT",                      .pfs={"Jet1AK8PtBins",plot,cut}, .cuts={}, .draw="PE1",  .opt=o_1or2d_d+"TwoCol33", .ranges={0,0, 0,1, 0.5,0.5} });
      //sh.AddHistos("evt", { .fill=trigger+"_vs_HTNoLep",                 .pfs={"Jet1AK8PtBins",plot,cut}, .cuts={}, .draw="PE1",  .opt=o_1or2d_d+"TwoCol33", .ranges={0,0, 0,1, 0.5,0.5} });
      //sh.AddHistos("evt", { .fill=trigger+"_vs_Jet1AK8Pt",               .pfs={"HTBins"       ,plot,cut}, .cuts={}, .draw="PE1",  .opt=o_1or2d_d+"TwoCol33", .ranges={0,0, 0,1, 0.5,0.5} });
      //sh.AddHistos("evt", { .fill=trigger+"_vs_HTJet1AK8Pt",             .pfs={                plot,cut}, .cuts={}, .draw="PE1",  .opt=o_1or2d_d+"TwoCol33DoubleX", .ranges={0,0, 0,1.0, 0.6,0.45} });
      //sh.AddHistos("evt", { .fill=trigger+"_vs_HTJet1AK8PtLow",          .pfs={                plot,cut}, .cuts={}, .draw="PE1",  .opt=o_1or2d_d+"TwoCol33DoubleX", .ranges={0,0, 0,1.0, 0.77,0.48} });
      //sh.AddHistos("evt", { .fill=trigger+"_vs_HTJet1AK8PtHigh",         .pfs={                plot,cut}, .cuts={}, .draw="PE1",  .opt=o_1or2d_d+"TwoCol33DoubleX", .ranges={0,0, 0,1.0, 0.77,0.48} });
      //for (auto njet_bin : {"NJet45"}) {
      //  sh.AddHistos("evt", { .fill=trigger+"_vs_Bin",                     .pfs={njet_bin,       plot,cut}, .cuts={}, .draw="PE1",  .opt=o_1or2d_d+"TwoCol33", .ranges={0,0, 0,1, 0.5,0.5} });
      //  sh.AddHistos("evt", { .fill=trigger+"_vs_R2_vs_MR",                .pfs={njet_bin,       plot,cut}, .cuts={}, .draw="COLZ", .opt=o_1or2d_d+"TwoCol33", .ranges={0,0, 0,0, 0,1} });
      //  sh.AddHistos("evt", { .fill=trigger+"_vs_RazorBins",               .pfs={njet_bin,       plot,cut}, .cuts={}, .draw="PE1",  .opt=o_1or2d_d+"TwoCol33", .ranges={0,0, 0,1, 0.5,0.5} });
      //  sh.AddHistos("evt", { .fill=trigger+"_vs_Jet1AK8PtBins_vs_HT",     .pfs={njet_bin,       plot,cut}, .cuts={}, .draw="COLZ", .opt=o_1or2d_d+"TwoCol33", .ranges={0,0, 0,0, 0,1} });
      //  sh.AddHistos("evt", { .fill=trigger+"_vs_Jet1AK8Mass_vs_HT",       .pfs={njet_bin,       plot,cut}, .cuts={}, .draw="COLZ", .opt=o_1or2d_d+"TwoCol33", .ranges={0,0, 0,0, 0,1} });
      //  sh.AddHistos("evt", { .fill=trigger+"_vs_mW1Mass_vs_HT",           .pfs={njet_bin,       plot,cut}, .cuts={}, .draw="COLZ", .opt=o_1or2d_d+"TwoCol33", .ranges={0,0, 0,0, 0,1} });
      //  sh.AddHistos("evt", { .fill=trigger+"_vs_HTFine",                  .pfs={njet_bin,       plot,cut}, .cuts={}, .draw="PE1",  .opt=o_1or2d_d+"TwoCol33", .ranges={0,0, 0,1, 0.5,0.5} });
      //  sh.AddHistos("evt", { .fill=trigger+"_vs_HTNoLep",                 .pfs={njet_bin,       plot,cut}, .cuts={}, .draw="PE1",  .opt=o_1or2d_d+"TwoCol33", .ranges={0,0, 0,1, 0.5,0.5} });
      //  sh.AddHistos("evt", { .fill=trigger+"_vs_OnlineHT",                .pfs={njet_bin,       plot,cut}, .cuts={}, .draw="PE1",  .opt=o_1or2d_d+"TwoCol33", .ranges={0,0, 0,1, 0.5,0.5} });
      //  sh.AddHistos("evt", { .fill=trigger+"_vs_Jet1AK8Pt",               .pfs={njet_bin,       plot,cut}, .cuts={}, .draw="PE1",  .opt=o_1or2d_d+"TwoCol33", .ranges={0,0, 0,1, 0.5,0.5} });
      //  sh.AddHistos("evt", { .fill=trigger+"_vs_Jet1AK8Mass",             .pfs={njet_bin,       plot,cut}, .cuts={}, .draw="PE1",  .opt=o_1or2d_d+"TwoCol33", .ranges={0,0, 0,1, 0.5,0.5} });
      //  sh.AddHistos("evt", { .fill=trigger+"_vs_mW1Mass",                 .pfs={njet_bin,       plot,cut}, .cuts={}, .draw="PE1",  .opt=o_1or2d_d+"TwoCol33", .ranges={0,0, 0,1, 0.5,0.5} });
      //  sh.AddHistos("evt", { .fill=trigger+"_vs_HTFine",                  .pfs={"Jet1AK8PtBins",plot,cut,njet_bin}, .cuts={}, .draw="PE1",  .opt=o_1or2d_d+"TwoCol33", .ranges={0,0, 0,1, 0.5,0.5} });
      //  sh.AddHistos("evt", { .fill=trigger+"_vs_HTNoLep",                 .pfs={"Jet1AK8PtBins",plot,cut,njet_bin}, .cuts={}, .draw="PE1",  .opt=o_1or2d_d+"TwoCol33", .ranges={0,0, 0,1, 0.5,0.5} });
      //  sh.AddHistos("evt", { .fill=trigger+"_vs_Jet1AK8Pt",               .pfs={"HTBins"       ,plot,cut,njet_bin}, .cuts={}, .draw="PE1",  .opt=o_1or2d_d+"TwoCol33", .ranges={0,0, 0,1, 0.5,0.5} });
      //  sh.AddHistos("evt", { .fill=trigger+"_vs_HTJet1AK8Pt",             .pfs={njet_bin,       plot,cut}, .cuts={}, .draw="PE1",  .opt=o_1or2d_d+"TwoCol33DoubleX", .ranges={0,0, 0,1.0, 0.6,0.45} });
      //  sh.AddHistos("evt", { .fill=trigger+"_vs_HTJet1AK8PtLow",          .pfs={njet_bin,       plot,cut}, .cuts={}, .draw="PE1",  .opt=o_1or2d_d+"TwoCol33DoubleX", .ranges={0,0, 0,1.0, 0.6,0.45} });
      //  sh.AddHistos("evt", { .fill=trigger+"_vs_HTJet1AK8PtHigh",         .pfs={njet_bin,       plot,cut}, .cuts={}, .draw="PE1",  .opt=o_1or2d_d+"TwoCol33DoubleX", .ranges={0,0, 0,1.0, 0.6,0.45} });
      //}
    }
  }
  // Single lepton triggers
  for (const auto& cut : {"Baseline"}) {
    for (auto plot : {"LeptonicMeasurements"}) {
      for (auto std_plot : standard_plots)
        sh.AddHistos("evt", { .fill=std_plot,             .pfs={plot,cut},          .cuts={}, .draw="HIST", .opt=o_1or2d_d+"LogTwoCol23", .ranges={0,0, 1e-1,1e8, 0.35,0.86} });
      sh.AddHistos("evt", { .fill="HT2DBins",             .pfs={plot,cut},          .cuts={}, .draw="HIST", .opt=o_1or2d_d+"LogTwoCol23", .ranges={0,0, 1e-1,1e8, 0.35,0.86} });
      sh.AddHistos("evt", { .fill="RazorBinsLep",         .pfs={plot,cut},          .cuts={}, .draw="HIST", .opt=o_1or2d_d+"LogTwoCol23", .ranges={0,0, 1e-1,1e8, 0.35,0.86} });
      sh.AddHistos("evt", { .fill="EleTightNoIsoPt",      .pfs={plot,cut},          .cuts={}, .draw="HIST", .opt=o_1or2d_d+"LogTwoCol23", .ranges={0,0, 1e-1,1e8, 0.35,0.86} });
      sh.AddHistos("evt", { .fill="MuTightNoIsoPt",       .pfs={plot,cut},          .cuts={}, .draw="HIST", .opt=o_1or2d_d+"LogTwoCol23", .ranges={0,0, 1e-1,1e8, 0.35,0.86} });
      sh.AddHistos("evt", { .fill="EleTight2DPt",         .pfs={plot,cut},          .cuts={}, .draw="HIST", .opt=o_1or2d_d+"LogTwoCol23", .ranges={0,0, 1e-1,1e8, 0.35,0.86} });
      sh.AddHistos("evt", { .fill="MuTight2DPt",          .pfs={plot,cut},          .cuts={}, .draw="HIST", .opt=o_1or2d_d+"LogTwoCol23", .ranges={0,0, 1e-1,1e8, 0.35,0.86} });
      for (auto ele_trigger : std::vector<std::string>({"HLTEff_Ele35", "HLTEff_Ele115", "HLTEff_Ele35_or_Ele115"})) {
        for (auto std_plot : standard_plots)
          sh.AddHistos("evt", { .fill=ele_trigger+"_vs_"+std_plot,             .pfs={plot,cut,"1Ele"}, .cuts={}, .draw="PE1",  .opt=o_1or2d_d+"TwoCol23", .ranges={0,0, 0,0, 0.5,0.5} });
        sh.AddHistos("evt", { .fill=ele_trigger+"_vs_Bin",                     .pfs={plot,cut,"1Ele"}, .cuts={}, .draw="PE1",  .opt=o_1or2d_d+"TwoCol23", .ranges={0,0, 0,1, 0.5,0.5} });
        sh.AddHistos("evt", { .fill=ele_trigger+"_vs_RazorBinsLep",            .pfs={plot,cut,"1Ele"}, .cuts={}, .draw="PE1",  .opt=o_1or2d_d+"TwoCol23", .ranges={0,0, 0,1, 0.5,0.5} });
        sh.AddHistos("evt", { .fill=ele_trigger+"_vs_HT2DBins",                .pfs={plot,cut,"1Ele"}, .cuts={}, .draw="PE1",  .opt=o_1or2d_d+"TwoCol23", .ranges={0,0, 0,1, 0.5,0.53} });
      }
      for (auto mu_trigger : std::vector<std::string>({"HLTEff_IsoMu27", "HLTEff_Mu50", "HLTEff_IsoMu27_or_Mu50"})) {
        for (auto std_plot : standard_plots)
          sh.AddHistos("evt", { .fill=mu_trigger+"_vs_"+std_plot,             .pfs={plot,cut,"1Muon"}, .cuts={}, .draw="PE1",  .opt=o_1or2d_d+"TwoCol23", .ranges={0,0, 0,0, 0.5,0.5} });
        sh.AddHistos("evt", { .fill=mu_trigger+"_vs_Bin",                     .pfs={plot,cut,"1Muon"}, .cuts={}, .draw="PE1",  .opt=o_1or2d_d+"TwoCol23", .ranges={0,0, 0,1, 0.5,0.5} });
        sh.AddHistos("evt", { .fill=mu_trigger+"_vs_RazorBinsLep",            .pfs={plot,cut,"1Muon"}, .cuts={}, .draw="PE1",  .opt=o_1or2d_d+"TwoCol23", .ranges={0,0, 0,1, 0.5,0.5} });
        sh.AddHistos("evt", { .fill=mu_trigger+"_vs_HT2DBins",                .pfs={plot,cut,"1Muon"}, .cuts={}, .draw="PE1",  .opt=o_1or2d_d+"TwoCol23", .ranges={0,0, 0,1, 0.5,0.53} });
      }
      for (auto lep_trigger : std::vector<std::string>({"HLTEff_Ele35", "HLTEff_Ele115", "HLTEff_Ele35_or_Ele115"})) {
        for (auto std_plot : standard_plots)
          sh.AddHistos("evt", { .fill=lep_trigger+"_vs_"+std_plot,             .pfs={plot,cut,"1Ele"}, .cuts={}, .draw="PE1",  .opt=o_1or2d_d+"TwoCol23", .ranges={0,0, 0,0, 0.5,0.5} });
        sh.AddHistos("evt", { .fill=lep_trigger+"_vs_Bin",                     .pfs={plot,cut,"1Ele"}, .cuts={}, .draw="PE1",  .opt=o_1or2d_d+"TwoCol23", .ranges={0,0, 0,1, 0.5,0.5} });
        sh.AddHistos("evt", { .fill=lep_trigger+"_vs_RazorBinsLep",            .pfs={plot,cut,"1Ele"}, .cuts={}, .draw="PE1",  .opt=o_1or2d_d+"TwoCol23", .ranges={0,0, 0,1, 0.5,0.5} });
        sh.AddHistos("evt", { .fill=lep_trigger+"_vs_ElePt",                   .pfs={plot,cut,"1Ele"}, .cuts={}, .draw="PE1",  .opt=o_1or2d_d+"TwoCol23", .ranges={0,0, 0,1, 0.5,0.53} });
      }
      for (auto lep_trigger : std::vector<std::string>({"HLTEff_IsoMu27", "HLTEff_Mu50", "HLTEff_IsoMu27_or_Mu50"})) {
        for (auto std_plot : standard_plots)
          sh.AddHistos("evt", { .fill=lep_trigger+"_vs_"+std_plot,             .pfs={plot,cut,"1Muon"}, .cuts={}, .draw="PE1",  .opt=o_1or2d_d+"TwoCol23", .ranges={0,0, 0,0, 0.5,0.5} });
        sh.AddHistos("evt", { .fill=lep_trigger+"_vs_Bin",                     .pfs={plot,cut,"1Muon"}, .cuts={}, .draw="PE1",  .opt=o_1or2d_d+"TwoCol23", .ranges={0,0, 0,1, 0.5,0.5} });
        sh.AddHistos("evt", { .fill=lep_trigger+"_vs_RazorBinsLep",            .pfs={plot,cut,"1Muon"}, .cuts={}, .draw="PE1",  .opt=o_1or2d_d+"TwoCol23", .ranges={0,0, 0,1, 0.5,0.5} });
        sh.AddHistos("evt", { .fill=lep_trigger+"_vs_MuPt",                    .pfs={plot,cut,"1Muon"}, .cuts={}, .draw="PE1",  .opt=o_1or2d_d+"TwoCol23", .ranges={0,0, 0,1, 0.5,0.53} });
      }
      // Hadronic combinations
      for (auto std_plot : standard_plots)
        sh.AddHistos("evt", { .fill=std_plot,             .pfs={plot,cut},          .cuts={}, .draw="HIST", .opt=o_1or2d_d, .ranges={0,0, 0,0, 0.35,0.86} });
      sh.AddHistos("evt", { .fill="RazorBinsLep",         .pfs={plot,cut},          .cuts={}, .draw="HIST", .opt=o_1or2d_d, .ranges={0,0, 0,0, 0.35,0.86} });
      sh.AddHistos("evt", { .fill="HT2DBins",             .pfs={plot,cut},          .cuts={}, .draw="HIST", .opt=o_1or2d_d, .ranges={0,0, 0,0, 0.35,0.86} });
      sh.AddHistos("evt", { .fill="EleTightPt",           .pfs={plot,cut},          .cuts={}, .draw="HIST", .opt=o_1or2d_d, .ranges={0,0, 0,0, 0.35,0.86} });
      sh.AddHistos("evt", { .fill="HTElePt",              .pfs={plot,cut},          .cuts={}, .draw="HIST", .opt=o_1or2d_d, .ranges={0,0, 0,0, 0.35,0.86} });
      sh.AddHistos("evt", { .fill="HT1ElePt",             .pfs={plot,cut},          .cuts={}, .draw="HIST", .opt=o_1or2d_d, .ranges={0,0, 0,0, 0.35,0.86} });
      sh.AddHistos("evt", { .fill="HT2ElePt",             .pfs={plot,cut},          .cuts={}, .draw="HIST", .opt=o_1or2d_d, .ranges={0,0, 0,0, 0.35,0.86} });
      sh.AddHistos("evt", { .fill="HT3ElePt",             .pfs={plot,cut},          .cuts={}, .draw="HIST", .opt=o_1or2d_d, .ranges={0,0, 0,0, 0.35,0.86} });
      sh.AddHistos("evt", { .fill="MuTightPt",            .pfs={plot,cut},          .cuts={}, .draw="HIST", .opt=o_1or2d_d, .ranges={0,0, 0,0, 0.35,0.86} });
      sh.AddHistos("evt", { .fill="HTMuPt",               .pfs={plot,cut},          .cuts={}, .draw="HIST", .opt=o_1or2d_d, .ranges={0,0, 0,0, 0.35,0.86} });
      sh.AddHistos("evt", { .fill="HT1MuPt",              .pfs={plot,cut},          .cuts={}, .draw="HIST", .opt=o_1or2d_d, .ranges={0,0, 0,0, 0.35,0.86} });
      sh.AddHistos("evt", { .fill="HT2MuPt",              .pfs={plot,cut},          .cuts={}, .draw="HIST", .opt=o_1or2d_d, .ranges={0,0, 0,0, 0.35,0.86} });
      sh.AddHistos("evt", { .fill="HT3MuPt",              .pfs={plot,cut},          .cuts={}, .draw="HIST", .opt=o_1or2d_d, .ranges={0,0, 0,0, 0.35,0.86} });
      for (auto ele_trigger : std::vector<std::string>({"HLTEff_Ele15_HT450", "HLTEff_Ele35_or_Ele115_or_Ele15_HT450"})) {
        for (auto std_plot : standard_plots)
          sh.AddHistos("evt", { .fill=ele_trigger+"_vs_"+std_plot,             .pfs={plot,cut,"1Ele"}, .cuts={}, .draw="PE1",  .opt=o_1or2d_d, .ranges={0,0, 0,0, 0.5,0.5} });
        sh.AddHistos("evt", { .fill=ele_trigger+"_vs_Bin",                     .pfs={plot,cut,"1Ele"}, .cuts={}, .draw="PE1",  .opt=o_1or2d_d, .ranges={0,0, 0,1, 0.5,0.5} });
        sh.AddHistos("evt", { .fill=ele_trigger+"_vs_RazorBinsLep",            .pfs={plot,cut,"1Ele"}, .cuts={}, .draw="PE1",  .opt=o_1or2d_d, .ranges={0,0, 0,1, 0.5,0.5} });
        sh.AddHistos("evt", { .fill=ele_trigger+"_vs_HT2DBins",                .pfs={plot,cut,"1Ele"}, .cuts={}, .draw="PE1",  .opt=o_1or2d_d, .ranges={0,0, 0,1, 0.5,0.53} });
        sh.AddHistos("evt", { .fill=ele_trigger+"_vs_ElePt",                   .pfs={plot,cut,"1Ele"}, .cuts={}, .draw="PE1",  .opt=o_1or2d_d, .ranges={0,0, 0,1, 0.5,0.53} });
        sh.AddHistos("evt", { .fill=ele_trigger+"_vs_HTElePt",                 .pfs={plot,cut,"1Ele"}, .cuts={}, .draw="PE1",  .opt=o_1or2d_d, .ranges={0,0, 0,1, 0.5,0.53} });
        sh.AddHistos("evt", { .fill=ele_trigger+"_vs_HT1ElePt",                .pfs={plot,cut,"1Ele"}, .cuts={}, .draw="PE1",  .opt=o_1or2d_d, .ranges={0,0, 0,1, 0.5,0.53} });
        sh.AddHistos("evt", { .fill=ele_trigger+"_vs_HT2ElePt",                .pfs={plot,cut,"1Ele"}, .cuts={}, .draw="PE1",  .opt=o_1or2d_d, .ranges={0,0, 0,1, 0.5,0.53} });
        sh.AddHistos("evt", { .fill=ele_trigger+"_vs_HT3ElePt",                .pfs={plot,cut,"1Ele"}, .cuts={}, .draw="PE1",  .opt=o_1or2d_d, .ranges={0,0, 0,1, 0.5,0.53} });
      }
      for (auto mu_trigger : std::vector<std::string>({"HLTEff_Mu15_HT450", "HLTEff_IsoMu27_or_Mu50_or_Mu15_HT450"})) {
        for (auto std_plot : standard_plots)
          sh.AddHistos("evt", { .fill=mu_trigger+"_vs_"+std_plot,             .pfs={plot,cut,"1Muon"}, .cuts={}, .draw="PE1",  .opt=o_1or2d_d, .ranges={0,0, 0,0, 0.5,0.5} });
        sh.AddHistos("evt", { .fill=mu_trigger+"_vs_Bin",                     .pfs={plot,cut,"1Muon"}, .cuts={}, .draw="PE1",  .opt=o_1or2d_d, .ranges={0,0, 0,1, 0.5,0.5} });
        sh.AddHistos("evt", { .fill=mu_trigger+"_vs_RazorBinsLep",            .pfs={plot,cut,"1Muon"}, .cuts={}, .draw="PE1",  .opt=o_1or2d_d, .ranges={0,0, 0,1, 0.5,0.5} });
        sh.AddHistos("evt", { .fill=mu_trigger+"_vs_HT2DBins",                .pfs={plot,cut,"1Muon"}, .cuts={}, .draw="PE1",  .opt=o_1or2d_d, .ranges={0,0, 0,1, 0.5,0.53} });
        sh.AddHistos("evt", { .fill=mu_trigger+"_vs_MuPt",                    .pfs={plot,cut,"1Muon"}, .cuts={}, .draw="PE1",  .opt=o_1or2d_d, .ranges={0,0, 0,1, 0.5,0.53} });
        sh.AddHistos("evt", { .fill=mu_trigger+"_vs_HTMuPt",                  .pfs={plot,cut,"1Muon"}, .cuts={}, .draw="PE1",  .opt=o_1or2d_d, .ranges={0,0, 0,1, 0.5,0.53} });
        sh.AddHistos("evt", { .fill=mu_trigger+"_vs_HT1MuPt",                 .pfs={plot,cut,"1Muon"}, .cuts={}, .draw="PE1",  .opt=o_1or2d_d, .ranges={0,0, 0,1, 0.5,0.53} });
        sh.AddHistos("evt", { .fill=mu_trigger+"_vs_HT2MuPt",                 .pfs={plot,cut,"1Muon"}, .cuts={}, .draw="PE1",  .opt=o_1or2d_d, .ranges={0,0, 0,1, 0.5,0.53} });
        sh.AddHistos("evt", { .fill=mu_trigger+"_vs_HT3MuPt",                 .pfs={plot,cut,"1Muon"}, .cuts={}, .draw="PE1",  .opt=o_1or2d_d, .ranges={0,0, 0,1, 0.5,0.53} });
      }
    }
  }
  
  // ----------------------------------------------------------------------------------------------
  //                                    New Signal Regions
  //-----------------------------------------------------------------------------------------------

  standard_plots = {"HT", "METFine", "MET", "MRFine", "MR", "R2Fine", "R2", "MRR2", "RazorBins", "RazorBinsNew"};
  //standard_plots.push_back("HTFine");
  //standard_plots.push_back("HTMET");
  
  for (auto region : {'0'}) {
    sh.SetHistoWeights({ [this,region] { return sf_weight[region]*137.0/41.529; } });
    std::string cut = std::string(1,region);
    //std::vector<std::string> showdata = {"JetHTMET"};
    std::vector<std::string> showdata = {"Blind"};
    //showdata.push_back("Blind");
    // Signal discriminators
    sh.AddHistos("evt",    { .fill="MRFine_vs_METFine",         .pfs={"Signals_Background",cut},          .cuts={},.draw="COLZ",.opt=o_1or2d_s+"Log",.ranges={}});
    sh.AddHistos("evt",    { .fill="R2Fine_vs_METFine",         .pfs={"Signals_Background",cut},          .cuts={},.draw="COLZ",.opt=o_1or2d_s+"Log",.ranges={}});
    sh.AddHistos("evt",    { .fill="R2Fine_vs_MRFine",          .pfs={"Signals_Background",cut},          .cuts={},.draw="COLZ",.opt=o_1or2d_s+"Log",.ranges={}});
    sh.AddHistos("evt",    { .fill="MRFine_vs_HTFine",          .pfs={"Signals_Background",cut},          .cuts={},.draw="COLZ",.opt=o_1or2d_s+"Log",.ranges={}});
    sh.AddHistos("evt",    { .fill="METFine_vs_HTFine",         .pfs={"Signals_Background",cut},          .cuts={},.draw="COLZ",.opt=o_1or2d_s+"Log",.ranges={}});
    sh.AddHistos("evt",    { .fill="R2Fine_vs_MRFine",          .pfs={"Signals_Background",cut},          .cuts={},.draw="COLZ",.opt=o_1or2d_s+"Log",.ranges={}});
    sh.AddHistos("evt",    { .fill="MTBoost_vs_METFine",        .pfs={"Signals_Background",cut},          .cuts={},.draw="COLZ",.opt=o_1or2d_s+"Log",.ranges={}});
    sh.AddHistos("evt",    { .fill="MTBoost_vs_R2Fine",         .pfs={"Signals_Background",cut},          .cuts={},.draw="COLZ",.opt=o_1or2d_s+"Log",.ranges={}});
    sh.AddHistos("evt",    { .fill="MTBoost_vs_MRFine",         .pfs={"Signals_Background",cut},          .cuts={},.draw="COLZ",.opt=o_1or2d_s+"Log",.ranges={}});
    // Boosted jet Index
    sh.AddHistos("hadw",       { .fill="JetAK8Index_vs_HadWIndex",                  .pfs={"Signals_Background",cut,"MatchGenHadW"},   .cuts={},.draw="COLZ",.opt=o_1or2d_s+"Log",.ranges={}});
    sh.AddHistos("hadz",       { .fill="JetAK8Index_vs_HadZIndex",                  .pfs={"Signals_Background",cut,"MatchGenHadZ"},   .cuts={},.draw="COLZ",.opt=o_1or2d_s+"Log",.ranges={}});
    sh.AddHistos("hadtop",     { .fill="JetAK8Index_vs_HadTopIndex",                .pfs={"Signals_Background",cut,"MatchGenHadTop"}, .cuts={},.draw="COLZ",.opt=o_1or2d_s+"Log",.ranges={}});
    sh.AddHistos("leptop",     { .fill="JetAK8Index_vs_LepTopIndex",                .pfs={"Signals_Background",cut,"MatchGenLepTop"}, .cuts={},.draw="COLZ",.opt=o_1or2d_s+"Log",.ranges={}});
    sh.AddHistos("gen hadw",   { .fill="GenHadWMatchedAK8JetIndex_vs_NGenHadW",     .pfs={"Signals_Background",cut}, .cuts={},.draw="COLZ",.opt=o_1or2d_s+"Log",.ranges={}});
    sh.AddHistos("gen hadz",   { .fill="GenHadZMatchedAK8JetIndex_vs_NGenHadZ",     .pfs={"Signals_Background",cut}, .cuts={},.draw="COLZ",.opt=o_1or2d_s+"Log",.ranges={}});
    sh.AddHistos("gen hadtop", { .fill="GenHadTopMatchedAK8JetIndex_vs_NGenHadTop", .pfs={"Signals_Background",cut}, .cuts={},.draw="COLZ",.opt=o_1or2d_s+"Log",.ranges={}});
    sh.AddHistos("gen leptop", { .fill="GenLepTopMatchedAK8JetIndex_vs_NGenLepTop", .pfs={"Signals_Background",cut}, .cuts={},.draw="COLZ",.opt=o_1or2d_s+"Log",.ranges={}});
    // MGlunio/MStop plots
    sh.AddHistos("evt",  { .fill="HTFine",             .pfs={"MGluinoPoints",  "MLSPPoints","GluinoSignalScans",  cut}, .cuts={},.draw=d,.opt=o_norm_s,.ranges={}});
    sh.AddHistos("evt",  { .fill="METFine",            .pfs={"MGluinoPoints",  "MLSPPoints","GluinoSignalScans",  cut}, .cuts={},.draw=d,.opt=o_norm_s,.ranges={}});
    sh.AddHistos("evt",  { .fill="R2Fine",             .pfs={"MGluinoPoints",  "MLSPPoints","GluinoSignalScans",  cut}, .cuts={},.draw=d,.opt=o_norm_s,.ranges={}});
    sh.AddHistos("evt",  { .fill="MRFine",             .pfs={"MGluinoPoints",  "MLSPPoints","GluinoSignalScans",  cut}, .cuts={},.draw=d,.opt=o_norm_s,.ranges={}});
    sh.AddHistos("evt",  { .fill="RazorBins",          .pfs={"MGluinoPoints",  "MLSPPoints","GluinoSignalScans",  cut}, .cuts={},.draw=d,.opt=o_norm_s,.ranges={}});
    sh.AddHistos("evt",  { .fill="MRR2",               .pfs={"MGluinoPoints",  "MLSPPoints","GluinoSignalScans",  cut}, .cuts={},.draw=d,.opt=o_norm_s,.ranges={}});
    sh.AddHistos("evt",  { .fill="HTFine",             .pfs={"MStopPoints",    "MLSPPoints","StopSignalScans",    cut}, .cuts={},.draw=d,.opt=o_norm_s,.ranges={}});
    sh.AddHistos("evt",  { .fill="METFine",            .pfs={"MStopPoints",    "MLSPPoints","StopSignalScans",    cut}, .cuts={},.draw=d,.opt=o_norm_s,.ranges={}});
    sh.AddHistos("evt",  { .fill="R2Fine",             .pfs={"MStopPoints",    "MLSPPoints","StopSignalScans",    cut}, .cuts={},.draw=d,.opt=o_norm_s,.ranges={}});
    sh.AddHistos("evt",  { .fill="MRFine",             .pfs={"MStopPoints",    "MLSPPoints","StopSignalScans",    cut}, .cuts={},.draw=d,.opt=o_norm_s,.ranges={}});
    sh.AddHistos("evt",  { .fill="RazorBins",          .pfs={"MStopPoints",    "MLSPPoints","StopSignalScans",    cut}, .cuts={},.draw=d,.opt=o_norm_s,.ranges={}});
    sh.AddHistos("evt",  { .fill="MRR2",               .pfs={"MStopPoints",    "MLSPPoints","StopSignalScans",    cut}, .cuts={},.draw=d,.opt=o_norm_s,.ranges={}});
    sh.AddHistos("evt",  { .fill="MRR2",               .pfs={"MCharginoPoints","MLSPPoints","CharginoSignalScans",cut}, .cuts={},.draw=d,.opt=o_norm_s,.ranges={}});
    sh.AddHistos("evt",  { .fill="HTFine",             .pfs={"MCharginoPoints","MLSPPoints","CharginoSignalScans",cut}, .cuts={},.draw=d,.opt=o_norm_s,.ranges={}});
    sh.AddHistos("evt",  { .fill="METFine",            .pfs={"MCharginoPoints","MLSPPoints","CharginoSignalScans",cut}, .cuts={},.draw=d,.opt=o_norm_s,.ranges={}});
    sh.AddHistos("evt",  { .fill="R2Fine",             .pfs={"MCharginoPoints","MLSPPoints","CharginoSignalScans",cut}, .cuts={},.draw=d,.opt=o_norm_s,.ranges={}});
    sh.AddHistos("evt",  { .fill="MRFine",             .pfs={"MCharginoPoints","MLSPPoints","CharginoSignalScans",cut}, .cuts={},.draw=d,.opt=o_norm_s,.ranges={}});
    sh.AddHistos("evt",  { .fill="RazorBins",          .pfs={"MCharginoPoints","MLSPPoints","CharginoSignalScans",cut}, .cuts={},.draw=d,.opt=o_norm_s,.ranges={}});
    // Stack plots
    for (auto data : showdata ) {
      std::string opt  = (data=="Blind") ? o_stk_s_S : o_stk_d_S;
      for (auto std_plot : standard_plots)
        sh.AddHistos(s+"evt",   { .fill=c+std_plot,                  .pfs={"StackPlotSignal",data,cut},                  .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
      sh.AddHistos(  s+"evt",   { .fill=c+"NJet",                    .pfs={"StackPlotSignal",data,cut},                  .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
      sh.AddHistos(  s+"evt",   { .fill=c+"NJet",                    .pfs={"StackPlotSignal",data,cut+"_ExclNJet"},      .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
      sh.AddHistos(  s+"evt",   { .fill=c+"MTBoost",                 .pfs={"StackPlotSignal",data,cut},                  .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
      sh.AddHistos(  s+"evt",   { .fill=c+"DeltaPhi",                .pfs={"StackPlotSignal",data,cut+"_ExcldPhi"},      .cuts={},.draw=d,.opt=opt,.ranges=r_Stk9});
      for (auto nobj_bin : {"NJet45",
               "NW1", "NW2", "NW3", 
               //"NTop1", "NTop2", "NTop3", "NTop4", "NTop5", 
               //"NWDeepMD1", "NWDeepMD2", "NWDeepMD3", 
               //"NZDeepMD1", "NZDeepMD2", "NZDeepMD3",
               "NTopDeepMD1", "NTopDeepMD2", "NTopDeepMD3", "NTopDeepMD4",
               "NWDeep1",   "NWDeep2",   "NWDeep3", 
               "NZDeep1",   "NZDeep2",   "NZDeep3", 
               "NVDeep1",   "NVDeep2",   "NVDeep3",
               "NTopDeep1",   "NTopDeep2",   "NTopDeep3", "NTopDeep4"}) {
        std::string signal = "StackPlotTopSignal";
        opt  = (data=="Blind") ? o_stk_s_T : o_stk_d_T;
        std::string cut2 = cut, bveto = "Nisob";
        if (TString(nobj_bin).Contains("NZ")||TString(nobj_bin).Contains("NV")) {
          signal = "StackPlotVSignal";
          opt  = (data=="Blind") ? o_stk_s_V : o_stk_d_V;
          cut2 = "0_ExclNJet";
          bveto = "Nisob_NJet24";
        }
        for (auto std_plot : standard_plots) {
          sh.AddHistos(s+"evt", { .fill=c+std_plot,                  .pfs={signal,data,cut2,nobj_bin},         .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
          sh.AddHistos(s+"evt", { .fill=c+std_plot,                  .pfs={signal,data,cut2,nobj_bin,"Nb"},    .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
          sh.AddHistos(s+"evt", { .fill=c+std_plot,                  .pfs={signal,data,cut2,nobj_bin,bveto},   .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
          sh.AddHistos(s+"evt", { .fill=c+std_plot,                  .pfs={signal,data,cut2,nobj_bin,"2b"},    .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
          sh.AddHistos(s+"evt", { .fill=c+std_plot,                  .pfs={signal,data,cut2,nobj_bin,"MTBoost800"},    .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
        }
        if (nobj_bin != std::string("NJet45")) {
          sh.AddHistos(s+"evt", { .fill=c+"NJet",                    .pfs={signal,data,cut2,nobj_bin},         .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
          sh.AddHistos(s+"evt", { .fill=c+"NJet",                    .pfs={signal,data,"0_ExclNJet",nobj_bin}, .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
          sh.AddHistos(s+"evt", { .fill=c+"NJet",                    .pfs={signal,data,cut2,nobj_bin,"Nb"},    .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
          sh.AddHistos(s+"evt", { .fill=c+"NJet",                    .pfs={signal,data,cut2,nobj_bin,bveto},   .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
          sh.AddHistos(s+"evt", { .fill=c+"NJet",                    .pfs={signal,data,cut2,nobj_bin,"2b"},    .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
          sh.AddHistos(s+"evt", { .fill=c+"NJet",                    .pfs={signal,data,cut2,nobj_bin,"MTBoost800"},    .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
        }
        sh.AddHistos(  s+"evt", { .fill=c+"DeltaPhi",                .pfs={signal,data,cut+"_ExcldPhi",nobj_bin},      .cuts={},.draw=d,.opt=opt,.ranges=r_Stk9});
        // MTBoost
        sh.AddHistos(  s+"evt", { .fill=c+"MTBoost",                 .pfs={signal,data,cut2,nobj_bin},                 .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
        sh.AddHistos(  s+"evt", { .fill=c+"MTBoost",                 .pfs={signal,data,cut2,nobj_bin,"Nb"},            .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
        sh.AddHistos(  s+"evt", { .fill=c+"MTBoost",                 .pfs={signal,data,cut2,nobj_bin,bveto},           .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
        sh.AddHistos(  s+"evt", { .fill=c+"MTBoost",                 .pfs={signal,data,cut2,nobj_bin,"2b"},            .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
      }
      // Exclusive W combinations
      for (std::string nobj_bin : {"Nb", "Nisob", "2b", "NHadTop", "NTopDeepMD1", "NTopDeepMD2", "NTopDeep1", "NTopDeep2"}) {
        for (std::string nw_bin : {"NHadW"}) {
          opt  = (data=="Blind") ? o_stk_s_T : o_stk_d_T;
          for (auto std_plot : standard_plots)
            sh.AddHistos(s+"evt", { .fill=c+std_plot,                .pfs={"StackPlotTopSignal",data,cut,nobj_bin,nw_bin},  .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
          sh.AddHistos(s+"evt", { .fill=c+"NJet",                    .pfs={"StackPlotTopSignal",data,cut,nobj_bin,nw_bin},  .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
          sh.AddHistos(s+"evt", { .fill=c+"NJet",                    .pfs={"StackPlotTopSignal",data,"0_ExclNJet",nobj_bin,nw_bin}, .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
          sh.AddHistos(s+"evt", { .fill=c+"MTBoost",                 .pfs={"StackPlotTopSignal",data,cut,nobj_bin,nw_bin},  .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
          sh.AddHistos(s+"evt", { .fill=c+"DeltaPhi",                .pfs={"StackPlotTopSignal",data,cut+"_ExcldPhi",nobj_bin,nw_bin}, .cuts={},.draw=d,.opt=opt,.ranges=r_Stk9});
        }
      }
    }
  }
  
  for (auto region : {'N'}) {
    sh.SetHistoWeights({ [this,region] { return sf_weight[region]*137.0/41.529; } });
    std::string cut = std::string(1,region);
    //std::vector<std::string> showdata = {"JetHTMET"};
    std::vector<std::string> showdata = {"Blind"};
    //showdata.push_back("Blind");
    // Leptons
    sh.AddHistos("evt",    { .fill="NLepTightNoIso_vs_NGenLepFromTop", .pfs={"Signals_Background","N_Excl1LepMTdPhiJet"}, .cuts={},.draw="COLZ",.opt=o_1or2d_s+"Log",.ranges={}});
    sh.AddHistos("evt",    { .fill="NEleTightNoIso_vs_NGenEleFromTop", .pfs={"Signals_Background","N_Excl1LepMTdPhiJet"}, .cuts={},.draw="COLZ",.opt=o_1or2d_s+"Log",.ranges={}});
    sh.AddHistos("evt",    { .fill="NMuTightNoIso_vs_NGenMuFromTop",   .pfs={"Signals_Background","N_Excl1LepMTdPhiJet"}, .cuts={},.draw="COLZ",.opt=o_1or2d_s+"Log",.ranges={}});
    sh.AddHistos("evt",    { .fill="NLepTight2D_vs_NGenLepFromTop",    .pfs={"Signals_Background","N_Excl1LepMTdPhiJet"}, .cuts={},.draw="COLZ",.opt=o_1or2d_s+"Log",.ranges={}});
    sh.AddHistos("evt",    { .fill="NEleTight2D_vs_NGenEleFromTop",    .pfs={"Signals_Background","N_Excl1LepMTdPhiJet"}, .cuts={},.draw="COLZ",.opt=o_1or2d_s+"Log",.ranges={}});
    sh.AddHistos("evt",    { .fill="NMuTight2D_vs_NGenMuFromTop",      .pfs={"Signals_Background","N_Excl1LepMTdPhiJet"}, .cuts={},.draw="COLZ",.opt=o_1or2d_s+"Log",.ranges={}});
    // Boosted leptonic jets
    sh.AddHistos("AK8", { .fill="LepJetPt",                         .pfs={"MatchedGenLeptonMother","Signals_Background",cut,"LepJetNoPt"},           .cuts={},.draw="HIST",.opt=o_1or2d_s,.ranges={0,0, 0,0, 0.5,0.53} });
    sh.AddHistos("AK8", { .fill="LepJetPt",                         .pfs={"MatchedGenLeptonMother","Signals_Background",cut,"LepJetHighMass"},       .cuts={},.draw="HIST",.opt=o_1or2d_s,.ranges={0,0, 0,0, 0.5,0.53} });
    sh.AddHistos("AK8", { .fill="LepJetEta",                        .pfs={"MatchedGenLeptonMother","Signals_Background",cut,"LepJet"},               .cuts={},.draw="HIST",.opt=o_1or2d_s,.ranges={0,0, 0,0, 0.5,0.53} });
    sh.AddHistos("AK8", { .fill="LepJetPhi",                        .pfs={"MatchedGenLeptonMother","Signals_Background",cut,"LepJet"},               .cuts={},.draw="HIST",.opt=o_1or2d_s,.ranges={0,0, 0,0, 0.5,0.53} });
    sh.AddHistos("AK8", { .fill="LepJetMass",                       .pfs={"MatchedGenLeptonMother","Signals_Background",cut,"LepJetCand"},           .cuts={},.draw="HIST",.opt=o_1or2d_s,.ranges={0,0, 0,0, 0.5,0.53} });
    sh.AddHistos("AK8", { .fill="LepJetMass_vs_LepJetPt",           .pfs={"MatchedGenLeptonMother","Signals_Background",cut,"LepJetNoPt"},           .cuts={},.draw="HIST",.opt=o_1or2d_s,.ranges={0,0, 0,0, 0.5,0.53} });
    sh.AddHistos("AK8", { .fill="LepJetSubJetCSV",                  .pfs={"MatchedGenLeptonMother","Signals_Background",cut,"LepTopNoSubJetB"},      .cuts={},.draw="HIST",.opt=o_1or2d_s,.ranges={0,0, 0,0, 0.5,0.53} });
    sh.AddHistos("AK8", { .fill="LepJetTau21",                      .pfs={"MatchedGenLeptonMother","Signals_Background",cut,"LepJet"},               .cuts={},.draw="HIST",.opt=o_1or2d_s,.ranges={0,0, 0,0, 0.5,0.53} });
    sh.AddHistos("AK8", { .fill="LepJetLSF",                        .pfs={"MatchedGenLeptonMother","Signals_Background",cut,"LepJet"},               .cuts={},.draw="HIST",.opt=o_1or2d_s,.ranges={0,0, 0,0, 0.5,0.53} });
    sh.AddHistos("AK8", { .fill="LepJetNSubJet",                    .pfs={"MatchedGenLeptonMother","Signals_Background",cut,"LepJet"},               .cuts={},.draw="HIST",.opt=o_1or2d_s,.ranges={0,0, 0,0, 0.5,0.53} });
    sh.AddHistos("AK8", { .fill="LepJetDRmin",                      .pfs={"MatchedGenLeptonMother","Signals_Background","N_Excl1LepMTdPhiJet","LepJetNoIso"},          .cuts={},.draw="HIST",.opt=o_1or2d_s,.ranges={0,0, 0,0, 0.5,0.53} });
    sh.AddHistos("AK8", { .fill="LepJetPtrel",                      .pfs={"MatchedGenLeptonMother","Signals_Background","N_Excl1LepMTdPhiJet","LepJetNoIso"},          .cuts={},.draw="HIST",.opt=o_1or2d_s,.ranges={0,0, 0,0, 0.5,0.53} });
    sh.AddHistos("AK8", { .fill="LepJetPtrel_vs_LepJetDRmin",       .pfs={"MatchedGenLeptonMother","Signals_Background","N_Excl1LepMTdPhiJet","LepJetNoIso"},          .cuts={},.draw="COLZ",.opt=o_1or2d_s,.ranges={} });
    sh.AddHistos("AK8", { .fill="LepJetLSFNoIso",                   .pfs={"MatchedGenLeptonMother","Signals_Background","N_Excl1LepMTdPhiJet","LepJetNoIso"},          .cuts={},.draw="HIST",.opt=o_1or2d_s,.ranges={0,0, 0,0, 0.5,0.53} });
    sh.AddHistos("AK8", { .fill="LepJetLSFNoIso_vs_LepJetNSubJet",  .pfs={"MatchedGenLeptonMother","Signals_Background","N_Excl1LepMTdPhiJet","LepJetNoIso"},          .cuts={},.draw="COLZ",.opt=o_1or2d_s,.ranges={} });
    // Boosted leptonic tops
    sh.AddHistos("AK8", { .fill="LepTopPt",                         .pfs={"MatchedGenLeptonMother","Signals_Background",cut,"LepTopNoPt"},           .cuts={},.draw="HIST",.opt=o_1or2d_s,.ranges={0,0, 0,0, 0.5,0.53} });
    sh.AddHistos("AK8", { .fill="LepTopPt",                         .pfs={"MatchedGenLeptonMother","Signals_Background",cut,"LepTopHighMass"},       .cuts={},.draw="HIST",.opt=o_1or2d_s,.ranges={0,0, 0,0, 0.5,0.53} });
    sh.AddHistos("AK8", { .fill="LepTopEta",                        .pfs={"MatchedGenLeptonMother","Signals_Background",cut,"LepTop"},               .cuts={},.draw="HIST",.opt=o_1or2d_s,.ranges={0,0, 0,0, 0.5,0.53} });
    sh.AddHistos("AK8", { .fill="LepTopPhi",                        .pfs={"MatchedGenLeptonMother","Signals_Background",cut,"LepTop"},               .cuts={},.draw="HIST",.opt=o_1or2d_s,.ranges={0,0, 0,0, 0.5,0.53} });
    sh.AddHistos("AK8", { .fill="LepTopMass",                       .pfs={"MatchedGenLeptonMother","Signals_Background",cut,"LepTopNoMass"},         .cuts={},.draw="HIST",.opt=o_1or2d_s,.ranges={0,0, 0,0, 0.5,0.53} });
    sh.AddHistos("AK8", { .fill="LepTopMass_vs_LepTopPt",           .pfs={"MatchedGenLeptonMother","Signals_Background",cut,"LepTopNoPt"},           .cuts={},.draw="HIST",.opt=o_1or2d_s,.ranges={0,0, 0,0, 0.5,0.53} });
    sh.AddHistos("AK8", { .fill="LepTopSubJetCSV",                  .pfs={"MatchedGenLeptonMother","Signals_Background",cut,"LepTopNoSubJetB"},      .cuts={},.draw="HIST",.opt=o_1or2d_s,.ranges={0,0, 0,0, 0.5,0.53} });
    sh.AddHistos("AK8", { .fill="LepTopTau21",                      .pfs={"MatchedGenLeptonMother","Signals_Background",cut,"LepTop"},               .cuts={},.draw="HIST",.opt=o_1or2d_s,.ranges={0,0, 0,0, 0.5,0.53} });
    sh.AddHistos("AK8", { .fill="LepTopLSF",                        .pfs={"MatchedGenLeptonMother","Signals_Background",cut,"LepTop"},               .cuts={},.draw="HIST",.opt=o_1or2d_s,.ranges={0,0, 0,0, 0.5,0.53} });
    sh.AddHistos("AK8", { .fill="LepTopNSubJet",                    .pfs={"MatchedGenLeptonMother","Signals_Background",cut,"LepTop"},               .cuts={},.draw="HIST",.opt=o_1or2d_s,.ranges={0,0, 0,0, 0.5,0.53} });
    sh.AddHistos("AK8", { .fill="LepJetDRmin",                      .pfs={"MatchedGenLeptonMother","Signals_Background","N_Excl1LepMTdPhiJet","LepTopNoIso"},          .cuts={},.draw="HIST",.opt=o_1or2d_s,.ranges={0,0, 0,0, 0.5,0.53} });
    sh.AddHistos("AK8", { .fill="LepJetPtrel",                      .pfs={"MatchedGenLeptonMother","Signals_Background","N_Excl1LepMTdPhiJet","LepTopNoIso"},          .cuts={},.draw="HIST",.opt=o_1or2d_s,.ranges={0,0, 0,0, 0.5,0.53} });
    sh.AddHistos("AK8", { .fill="LepJetPtrel_vs_LepJetDRmin",       .pfs={"MatchedGenLeptonMother","Signals_Background","N_Excl1LepMTdPhiJet","LepTopNoIso"},          .cuts={},.draw="COLZ",.opt=o_1or2d_s,.ranges={} });
    sh.AddHistos("AK8", { .fill="LepTopLSFNoIso",                   .pfs={"MatchedGenLeptonMother","Signals_Background","N_Excl1LepMTdPhiJet","LepTopNoIso"},          .cuts={},.draw="HIST",.opt=o_1or2d_s,.ranges={0,0, 0,0, 0.5,0.53} });
    sh.AddHistos("AK8", { .fill="LepTopLSFNoIso_vs_LepTopNSubJet",  .pfs={"MatchedGenLeptonMother","Signals_Background","N_Excl1LepMTdPhiJet","LepTopNoIso"},           .cuts={},.draw="COLZ",.opt=o_1or2d_s,.ranges={} });
    // Boosted jet Index
    sh.AddHistos("hadw",       { .fill="JetAK8Index_vs_HadWIndex",                  .pfs={"Signals_Background",cut,"MatchGenHadW"},   .cuts={},.draw="COLZ",.opt=o_1or2d_s+"Log",.ranges={}});
    sh.AddHistos("hadz",       { .fill="JetAK8Index_vs_HadZIndex",                  .pfs={"Signals_Background",cut,"MatchGenHadZ"},   .cuts={},.draw="COLZ",.opt=o_1or2d_s+"Log",.ranges={}});
    sh.AddHistos("hadtop",     { .fill="JetAK8Index_vs_HadTopIndex",                .pfs={"Signals_Background",cut,"MatchGenHadTop"}, .cuts={},.draw="COLZ",.opt=o_1or2d_s+"Log",.ranges={}});
    sh.AddHistos("leptop",     { .fill="JetAK8Index_vs_LepTopIndex",                .pfs={"Signals_Background",cut,"MatchedGenLeptonMother"}, .cuts={},.draw="COLZ",.opt=o_1or2d_s+"Log",.ranges={}});
    sh.AddHistos("gen hadw",   { .fill="GenHadWMatchedAK8JetIndex_vs_NGenHadW",     .pfs={"Signals_Background",cut}, .cuts={},.draw="COLZ",.opt=o_1or2d_s+"Log",.ranges={}});
    sh.AddHistos("gen hadz",   { .fill="GenHadZMatchedAK8JetIndex_vs_NGenHadZ",     .pfs={"Signals_Background",cut}, .cuts={},.draw="COLZ",.opt=o_1or2d_s+"Log",.ranges={}});
    sh.AddHistos("gen hadtop", { .fill="GenHadTopMatchedAK8JetIndex_vs_NGenHadTop", .pfs={"Signals_Background",cut}, .cuts={},.draw="COLZ",.opt=o_1or2d_s+"Log",.ranges={}});
    sh.AddHistos("gen leptop", { .fill="GenLepTopMatchedAK8JetIndex_vs_NGenLepTop", .pfs={"Signals_Background",cut}, .cuts={},.draw="COLZ",.opt=o_1or2d_s+"Log",.ranges={}});
    // Signal discriminators (2D)
    sh.AddHistos("evt",    { .fill="MRFine_vs_METFine",         .pfs={"Signals_Background",cut},          .cuts={},.draw="COLZ",.opt=o_1or2d_s+"Log",.ranges={}});
    sh.AddHistos("evt",    { .fill="R2Fine_vs_METFine",         .pfs={"Signals_Background",cut},          .cuts={},.draw="COLZ",.opt=o_1or2d_s+"Log",.ranges={}});
    sh.AddHistos("evt",    { .fill="R2Fine_vs_MRFine",          .pfs={"Signals_Background",cut},          .cuts={},.draw="COLZ",.opt=o_1or2d_s+"Log",.ranges={}});
    sh.AddHistos("evt",    { .fill="MRFine_vs_HTFine",          .pfs={"Signals_Background",cut},          .cuts={},.draw="COLZ",.opt=o_1or2d_s+"Log",.ranges={}});
    sh.AddHistos("evt",    { .fill="METFine_vs_HTFine",         .pfs={"Signals_Background",cut},          .cuts={},.draw="COLZ",.opt=o_1or2d_s+"Log",.ranges={}});
    sh.AddHistos("evt",    { .fill="R2Fine_vs_MRFine",          .pfs={"Signals_Background",cut},          .cuts={},.draw="COLZ",.opt=o_1or2d_s+"Log",.ranges={}});
    sh.AddHistos("evt",    { .fill="MTBoost_vs_MTTight2D",      .pfs={"Signals_Background",cut},          .cuts={},.draw="COLZ",.opt=o_1or2d_s+"Log",.ranges={}});
    sh.AddHistos("evt",    { .fill="MTBoost_vs_MTTight2D",      .pfs={"Signals_Background",cut+"_ExclMT"},.cuts={},.draw="COLZ",.opt=o_1or2d_s+"Log",.ranges={}});
    sh.AddHistos("evt",    { .fill="MTBoost_vs_METFine",        .pfs={"Signals_Background",cut},          .cuts={},.draw="COLZ",.opt=o_1or2d_s+"Log",.ranges={}});
    sh.AddHistos("evt",    { .fill="MTBoost_vs_R2Fine",         .pfs={"Signals_Background",cut},          .cuts={},.draw="COLZ",.opt=o_1or2d_s+"Log",.ranges={}});
    sh.AddHistos("evt",    { .fill="MTBoost_vs_MRFine",         .pfs={"Signals_Background",cut},          .cuts={},.draw="COLZ",.opt=o_1or2d_s+"Log",.ranges={}});
    // MGlunio/MStop plots
    sh.AddHistos("evt",  { .fill="HTFine",             .pfs={"MGluinoPoints",  "MLSPPoints","GluinoSignalScans",  cut}, .cuts={},.draw=d,.opt=o_norm_s,.ranges={}});
    sh.AddHistos("evt",  { .fill="METFine",            .pfs={"MGluinoPoints",  "MLSPPoints","GluinoSignalScans",  cut}, .cuts={},.draw=d,.opt=o_norm_s,.ranges={}});
    sh.AddHistos("evt",  { .fill="R2Fine",             .pfs={"MGluinoPoints",  "MLSPPoints","GluinoSignalScans",  cut}, .cuts={},.draw=d,.opt=o_norm_s,.ranges={}});
    sh.AddHistos("evt",  { .fill="MRFine",             .pfs={"MGluinoPoints",  "MLSPPoints","GluinoSignalScans",  cut}, .cuts={},.draw=d,.opt=o_norm_s,.ranges={}});
    sh.AddHistos("evt",  { .fill="RazorBinsLep",       .pfs={"MGluinoPoints",  "MLSPPoints","GluinoSignalScans",  cut}, .cuts={},.draw=d,.opt=o_norm_s,.ranges={}});
    sh.AddHistos("evt",  { .fill="MRR2",               .pfs={"MGluinoPoints",  "MLSPPoints","GluinoSignalScans",  cut}, .cuts={},.draw=d,.opt=o_norm_s,.ranges={}});
    sh.AddHistos("evt",  { .fill="HTFine",             .pfs={"MStopPoints",    "MLSPPoints","StopSignalScans",    cut}, .cuts={},.draw=d,.opt=o_norm_s,.ranges={}});
    sh.AddHistos("evt",  { .fill="METFine",            .pfs={"MStopPoints",    "MLSPPoints","StopSignalScans",    cut}, .cuts={},.draw=d,.opt=o_norm_s,.ranges={}});
    sh.AddHistos("evt",  { .fill="R2Fine",             .pfs={"MStopPoints",    "MLSPPoints","StopSignalScans",    cut}, .cuts={},.draw=d,.opt=o_norm_s,.ranges={}});
    sh.AddHistos("evt",  { .fill="MRFine",             .pfs={"MStopPoints",    "MLSPPoints","StopSignalScans",    cut}, .cuts={},.draw=d,.opt=o_norm_s,.ranges={}});
    sh.AddHistos("evt",  { .fill="RazorBinsLep",       .pfs={"MStopPoints",    "MLSPPoints","StopSignalScans",    cut}, .cuts={},.draw=d,.opt=o_norm_s,.ranges={}});
    sh.AddHistos("evt",  { .fill="MRR2",               .pfs={"MStopPoints",    "MLSPPoints","StopSignalScans",    cut}, .cuts={},.draw=d,.opt=o_norm_s,.ranges={}});
    sh.AddHistos("evt",  { .fill="MRR2",               .pfs={"MCharginoPoints","MLSPPoints","CharginoSignalScans",cut}, .cuts={},.draw=d,.opt=o_norm_s,.ranges={}});
    sh.AddHistos("evt",  { .fill="HTFine",             .pfs={"MCharginoPoints","MLSPPoints","CharginoSignalScans",cut}, .cuts={},.draw=d,.opt=o_norm_s,.ranges={}});
    sh.AddHistos("evt",  { .fill="METFine",            .pfs={"MCharginoPoints","MLSPPoints","CharginoSignalScans",cut}, .cuts={},.draw=d,.opt=o_norm_s,.ranges={}});
    sh.AddHistos("evt",  { .fill="R2Fine",             .pfs={"MCharginoPoints","MLSPPoints","CharginoSignalScans",cut}, .cuts={},.draw=d,.opt=o_norm_s,.ranges={}});
    sh.AddHistos("evt",  { .fill="MRFine",             .pfs={"MCharginoPoints","MLSPPoints","CharginoSignalScans",cut}, .cuts={},.draw=d,.opt=o_norm_s,.ranges={}});
    sh.AddHistos("evt",  { .fill="RazorBinsLep",       .pfs={"MCharginoPoints","MLSPPoints","CharginoSignalScans",cut}, .cuts={},.draw=d,.opt=o_norm_s,.ranges={}});
    // Stack plots
    for (auto data : showdata ) {
      std::string opt = (data=="Blind") ? o_stk_s_S : o_stk_d_S;
      for (auto std_plot : standard_plots)
        sh.AddHistos(s+"evt",{ .fill=c+std_plot,                       .pfs={"StackPlotSignal",data,cut},                    .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
      sh.AddHistos(s+"evt",  { .fill=c+"NJet",                         .pfs={"StackPlotSignal",data,cut},                    .cuts={},.draw=d,.opt=opt,.ranges=r_Stk5});
      sh.AddHistos(s+"evt",  { .fill=c+"NJet",                         .pfs={"StackPlotSignal",data,"N_ExclNJet"},           .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
      sh.AddHistos(s+"evt",  { .fill=c+"MTBoost",                      .pfs={"StackPlotSignal",data,cut},                    .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
      sh.AddHistos(s+"evt",  { .fill=c+"DeltaPhi",                     .pfs={"StackPlotSignal",data,cut},                    .cuts={},.draw=d,.opt=opt,.ranges=r_Stk9});
      sh.AddHistos(s+"evt",  { .fill=c+"DeltaPhi",                     .pfs={"StackPlotSignal",data,"N_ExclMT"},             .cuts={},.draw=d,.opt=opt,.ranges=r_Stk9});
      sh.AddHistos(s+"evt",  { .fill=c+"EleTightNoIsoPt",              .pfs={"StackPlotSignal",data,"N_Excl1LepMTdPhiJet"},         .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
      sh.AddHistos(s+"evt",  { .fill=c+"MuTightNoIsoPt",               .pfs={"StackPlotSignal",data,"N_Excl1LepMTdPhiJet"},         .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
      sh.AddHistos(s+"evt",  { .fill=c+"EleTight2DPt",                 .pfs={"StackPlotSignal",data,"N_Excl1LepMTdPhiJet"},         .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
      sh.AddHistos(s+"evt",  { .fill=c+"MuTight2DPt",                  .pfs={"StackPlotSignal",data,"N_Excl1LepMTdPhiJet"},         .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
      sh.AddHistos(s+"evt",  { .fill=c+"MTTight2D",                    .pfs={"StackPlotSignal",data,"N_ExclMT"},             .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
      sh.AddHistos(s+"evt",  { .fill=c+"DeltaPhiBoostedJetMET",        .pfs={"StackPlotSignal",data,cut},                    .cuts={},.draw=d,.opt=opt,.ranges=r_Stk5});
      sh.AddHistos(s+"evt",  { .fill=c+"DeltaPhiBoostedJetLep",        .pfs={"StackPlotSignal",data,cut},                    .cuts={},.draw=d,.opt=opt,.ranges=r_Stk5});
      sh.AddHistos(s+"evt",  { .fill=c+"DeltaPhiBoostedJetMET",        .pfs={"StackPlotSignal",data,cut+"_ExcldPhiJet"},     .cuts={},.draw=d,.opt=opt,.ranges=r_Stk5});
      sh.AddHistos(s+"evt",  { .fill=c+"DeltaPhiBoostedJetLep",        .pfs={"StackPlotSignal",data,cut+"_ExcldPhiJet"},     .cuts={},.draw=d,.opt=opt,.ranges=r_Stk5});
      sh.AddHistos(s+"evt",  { .fill=c+"DeltaPhiBoostedJetLepMET",     .pfs={"StackPlotSignal",data,cut+"_ExcldPhiJet"},     .cuts={},.draw=d,.opt=opt,.ranges=r_Stk5});
      // Boosted leptonic jets
      sh.AddHistos(s+"AK8", { .fill=c+"LepJetPt",                        .pfs={"StackPlotSignal",data,cut,"LepJetNoPt"},                    .cuts={},.draw=d,.opt=opt,.ranges=r_Stk5});
      sh.AddHistos(s+"AK8", { .fill=c+"LepJetPt",                        .pfs={"StackPlotSignal",data,cut,"LepJetHighMass"},                .cuts={},.draw=d,.opt=opt,.ranges=r_Stk5});
      sh.AddHistos(s+"AK8", { .fill=c+"LepJetEta",                       .pfs={"StackPlotSignal",data,cut,"LepJet"},                        .cuts={},.draw=d,.opt=opt,.ranges=r_Stk5});
      sh.AddHistos(s+"AK8", { .fill=c+"LepJetPhi",                       .pfs={"StackPlotSignal",data,cut,"LepJet"},                        .cuts={},.draw=d,.opt=opt,.ranges=r_Stk5});
      sh.AddHistos(s+"AK8", { .fill=c+"LepJetMass",                      .pfs={"StackPlotSignal",data,cut,"LepJetCand"},                    .cuts={},.draw=d,.opt=opt,.ranges=r_Stk5});
      sh.AddHistos(s+"AK8", { .fill=c+"LepJetSubJetCSV",                 .pfs={"StackPlotSignal",data,cut,"LepTopNoSubJetB"},               .cuts={},.draw=d,.opt=opt,.ranges=r_Stk5});
      sh.AddHistos(s+"AK8", { .fill=c+"LepJetTau21",                     .pfs={"StackPlotSignal",data,cut,"LepJet"},                        .cuts={},.draw=d,.opt=opt,.ranges=r_Stk5});
      sh.AddHistos(s+"AK8", { .fill=c+"LepJetLSF",                       .pfs={"StackPlotSignal",data,cut,"LepJet"},                        .cuts={},.draw=d,.opt=opt,.ranges=r_Stk5});
      sh.AddHistos(s+"AK8", { .fill=c+"LepJetNSubJet",                   .pfs={"StackPlotSignal",data,cut,"LepJet"},                        .cuts={},.draw=d,.opt=opt,.ranges=r_Stk5});
      sh.AddHistos(s+"AK8", { .fill=c+"LepJetLSFNoIso",                  .pfs={"StackPlotSignal",data,"N_Excl1LepMTdPhiJet","LepJetNoIso"}, .cuts={},.draw=d,.opt=opt,.ranges=r_Stk5});
      sh.AddHistos(s+"AK8", { .fill=c+"LepJetDRmin",                     .pfs={"StackPlotSignal",data,"N_Excl1LepMTdPhiJet","LepJetNoIso"}, .cuts={},.draw=d,.opt=opt,.ranges=r_Stk5});
      sh.AddHistos(s+"AK8", { .fill=c+"LepJetPtrel",                     .pfs={"StackPlotSignal",data,"N_Excl1LepMTdPhiJet","LepJetNoIso"}, .cuts={},.draw=d,.opt=opt,.ranges=r_Stk5});
      // Boosted leptonic tops
      sh.AddHistos(s+"AK8", { .fill=c+"LepTopPt",                        .pfs={"StackPlotSignal",data,cut,"LepTopNoPt"},                    .cuts={},.draw=d,.opt=opt,.ranges=r_Stk5});
      sh.AddHistos(s+"AK8", { .fill=c+"LepTopPt",                        .pfs={"StackPlotSignal",data,cut,"LepTopHighMass"},                .cuts={},.draw=d,.opt=opt,.ranges=r_Stk5});
      sh.AddHistos(s+"AK8", { .fill=c+"LepTopEta",                       .pfs={"StackPlotSignal",data,cut,"LepTop"},                        .cuts={},.draw=d,.opt=opt,.ranges=r_Stk5});
      sh.AddHistos(s+"AK8", { .fill=c+"LepTopPhi",                       .pfs={"StackPlotSignal",data,cut,"LepTop"},                        .cuts={},.draw=d,.opt=opt,.ranges=r_Stk5});
      sh.AddHistos(s+"AK8", { .fill=c+"LepTopMass",                      .pfs={"StackPlotSignal",data,cut,"LepTopNoMass"},                  .cuts={},.draw=d,.opt=opt,.ranges=r_Stk5});
      sh.AddHistos(s+"AK8", { .fill=c+"LepTopSubJetCSV",                 .pfs={"StackPlotSignal",data,cut,"LepTopNoSubJetB"},               .cuts={},.draw=d,.opt=opt,.ranges=r_Stk5});
      sh.AddHistos(s+"AK8", { .fill=c+"LepTopTau21",                     .pfs={"StackPlotSignal",data,cut,"LepTop"},                        .cuts={},.draw=d,.opt=opt,.ranges=r_Stk5});
      sh.AddHistos(s+"AK8", { .fill=c+"LepTopLSF",                       .pfs={"StackPlotSignal",data,cut,"LepTop"},                        .cuts={},.draw=d,.opt=opt,.ranges=r_Stk5});
      sh.AddHistos(s+"AK8", { .fill=c+"LepTopNSubJet",                   .pfs={"StackPlotSignal",data,cut,"LepTop"},                        .cuts={},.draw=d,.opt=opt,.ranges=r_Stk5});
      sh.AddHistos(s+"AK8", { .fill=c+"LepTopLSFNoIso",                  .pfs={"StackPlotSignal",data,"N_Excl1LepMTdPhiJet","LepTopNoIso"}, .cuts={},.draw=d,.opt=opt,.ranges=r_Stk5});
      sh.AddHistos(s+"AK8", { .fill=c+"LepJetDRmin",                     .pfs={"StackPlotSignal",data,"N_Excl1LepMTdPhiJet","LepTopNoIso"}, .cuts={},.draw=d,.opt=opt,.ranges=r_Stk5});
      sh.AddHistos(s+"AK8", { .fill=c+"LepJetPtrel",                     .pfs={"StackPlotSignal",data,"N_Excl1LepMTdPhiJet","LepTopNoIso"}, .cuts={},.draw=d,.opt=opt,.ranges=r_Stk5});
      for (auto nobj_bin : {"NJet45",
               //"NTop1", "NTop2", "NTop3", "NTop4", "NTop5", 
               //"NWDeepMD1", "NWDeepMD2", "NWDeepMD3", 
               //"NZDeepMD1", "NZDeepMD2", "NZDeepMD3",
               "NTopDeepMD1", "NTopDeepMD2", "NTopDeepMD3", "NTopDeepMD4",
               "NLepTop",     "NLepTopHighMass",
               "NTopDeep1",   "NTopDeep2", "NTopDeep3",   "NTopDeep4",
               "NW1",         "NW2",       "NW3", 
               "NWDeep1",     "NWDeep2",   "NWDeep3", 
               "NLepJetCand", "NLepJet",   "NLepJetHighMass",
               "NZDeep1",     "NZDeep2",   "NZDeep3", 
               "NVDeep1",     "NVDeep2",   "NVDeep3"}) {
        std::string signal = "StackPlotTopSignal";
        opt  = (data=="Blind") ? o_stk_s_T : o_stk_d_T;
        if (TString(nobj_bin).Contains("NZ")||TString(nobj_bin).Contains("NV")||TString(nobj_bin).Contains("LepJet")) {
          signal = "StackPlotVSignal";
          opt  = (data=="Blind") ? o_stk_s_V : o_stk_d_V;
        }
        for (auto std_plot : standard_plots) {
          sh.AddHistos(s+"evt",  { .fill=c+std_plot,                  .pfs={signal,data,cut,nobj_bin},         .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
          sh.AddHistos(s+"evt",  { .fill=c+std_plot,                  .pfs={signal,data,cut,nobj_bin,"Nb"},    .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
          sh.AddHistos(s+"evt",  { .fill=c+std_plot,                  .pfs={signal,data,cut,nobj_bin,"Nisob"}, .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
          sh.AddHistos(s+"evt",  { .fill=c+std_plot,                  .pfs={signal,data,cut,nobj_bin,"2b"},    .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
          sh.AddHistos(s+"evt",  { .fill=c+std_plot,                  .pfs={signal,data,cut,nobj_bin,"MTBoost800"}, .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
        }
        if (nobj_bin != std::string("NJet45")) {
          sh.AddHistos(s+"evt",  { .fill=c+"NJet",                    .pfs={signal,data,cut,nobj_bin},         .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
          sh.AddHistos(s+"evt",  { .fill=c+"NJet",                    .pfs={signal,data,"N_ExclNJet",nobj_bin},.cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
          sh.AddHistos(s+"evt",  { .fill=c+"NJet",                    .pfs={signal,data,cut,nobj_bin,"Nb"},    .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
          sh.AddHistos(s+"evt",  { .fill=c+"NJet",                    .pfs={signal,data,cut,nobj_bin,"Nisob"}, .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
          sh.AddHistos(s+"evt",  { .fill=c+"NJet",                    .pfs={signal,data,cut,nobj_bin,"2b"},    .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
          sh.AddHistos(s+"evt",  { .fill=c+"NJet",                    .pfs={signal,data,cut,nobj_bin,"MTBoost800"},    .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
        }
        sh.AddHistos(  s+"evt",  { .fill=c+"DeltaPhi",                .pfs={signal,data,cut,nobj_bin},                 .cuts={},.draw=d,.opt=opt,.ranges=r_Stk9});
        sh.AddHistos(  s+"evt",  { .fill=c+"DeltaPhi",                .pfs={signal,data,"N_ExclMT",nobj_bin},          .cuts={},.draw=d,.opt=opt,.ranges=r_Stk9});
        // MTBoost
        sh.AddHistos(  s+"evt",  { .fill=c+"MTBoost",                 .pfs={signal,data,cut,nobj_bin},                 .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
        sh.AddHistos(  s+"evt",  { .fill=c+"MTBoost",                 .pfs={signal,data,cut,nobj_bin,"Nb"},            .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
        sh.AddHistos(  s+"evt",  { .fill=c+"MTBoost",                 .pfs={signal,data,cut,nobj_bin,"Nisob"},         .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
        sh.AddHistos(  s+"evt",  { .fill=c+"MTBoost",                 .pfs={signal,data,cut,nobj_bin,"2b"},            .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
      }
      // Exclusive Leptonic+Hadronic combinations
      for (std::string nhad_bin : {"Nb", "Nisob", "2b", "NHadTop", "NHadW", "NTopDeepMD1", "NTopDeepMD2", "NTopDeep1", "NTopDeep2"}) {
        for (std::string nlep_bin : {"NLepJetCand", "NLepJet", "NLepJetHighMass", "NLepTop", "NLepTopHighMass"}) {
          opt  = (data=="Blind") ? o_stk_s_T : o_stk_d_T;
          for (auto std_plot : standard_plots) {
            sh.AddHistos(s+"evt", { .fill=c+std_plot,                .pfs={"StackPlotTopSignal",data,cut,                  nhad_bin,nlep_bin}, .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
            sh.AddHistos(s+"evt", { .fill=c+std_plot,                .pfs={"StackPlotTopSignal",data,"N_Excl1LepMTdPhiJet",nhad_bin,nlep_bin}, .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
          }
          sh.AddHistos(s+"evt", { .fill=c+"NJet",                    .pfs={"StackPlotTopSignal",data,cut,                  nhad_bin,nlep_bin}, .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
          sh.AddHistos(s+"evt", { .fill=c+"NJet",                    .pfs={"StackPlotTopSignal",data,"N_ExclNJet",         nhad_bin,nlep_bin}, .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
          sh.AddHistos(s+"evt", { .fill=c+"NJet",                    .pfs={"StackPlotTopSignal",data,"N_Excl1LepMTdPhiJet",nhad_bin,nlep_bin}, .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
          sh.AddHistos(s+"evt",    { .fill=c+"MTBoost",              .pfs={"StackPlotTopSignal",data,cut,                  nhad_bin,nlep_bin}, .cuts={},.draw=d,.opt=opt,.ranges=r_Stk5});
          sh.AddHistos(  s+"evt",  { .fill=c+"DeltaPhi",             .pfs={"StackPlotTopSignal",data,cut,       nhad_bin,nlep_bin},            .cuts={},.draw=d,.opt=opt,.ranges=r_Stk9});
          sh.AddHistos(  s+"evt",  { .fill=c+"DeltaPhi",             .pfs={"StackPlotTopSignal",data,"N_ExclMT",nhad_bin,nlep_bin},            .cuts={},.draw=d,.opt=opt,.ranges=r_Stk9});
        }
      }
      for (std::string nhad_bin : {"Nb", "Nisob", "2b", "NHadW", "NZDeep1", "NZDeep2", "NZDeep3", "NVDeep1", "NVDeep2", "NVDeep3"}) {
        for (std::string nlep_bin : {"NLepJetCand", "NLepJet", "NLepJetHighMass"}) {
          opt  = (data=="Blind") ? o_stk_s_V : o_stk_d_V;
          for (auto std_plot : standard_plots) {
            sh.AddHistos(s+"evt", { .fill=c+std_plot,                .pfs={"StackPlotVSignal",data,cut,                  nhad_bin,nlep_bin}, .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
            sh.AddHistos(s+"evt", { .fill=c+std_plot,                .pfs={"StackPlotVSignal",data,"N_Excl1LepMTdPhiJet",nhad_bin,nlep_bin}, .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
          }
          sh.AddHistos(s+"evt", { .fill=c+"NJet",                    .pfs={"StackPlotVSignal",data,cut,                  nhad_bin,nlep_bin}, .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
          sh.AddHistos(s+"evt", { .fill=c+"NJet",                    .pfs={"StackPlotVSignal",data,"N_ExclNJet",         nhad_bin,nlep_bin}, .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
          sh.AddHistos(s+"evt", { .fill=c+"NJet",                    .pfs={"StackPlotVSignal",data,"N_Excl1LepMTdPhiJet",nhad_bin,nlep_bin}, .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
          sh.AddHistos(s+"evt", { .fill=c+"MTBoost",                 .pfs={"StackPlotVSignal",data,cut,                  nhad_bin,nlep_bin}, .cuts={},.draw=d,.opt=opt,.ranges=r_Stk5});
          sh.AddHistos(s+"evt",  { .fill=c+"DeltaPhi",               .pfs={"StackPlotVSignal",data,cut,                  nhad_bin,nlep_bin}, .cuts={},.draw=d,.opt=opt,.ranges=r_Stk9});
          sh.AddHistos(s+"evt",  { .fill=c+"DeltaPhi",               .pfs={"StackPlotVSignal",data,"N_ExclMT",           nhad_bin,nlep_bin}, .cuts={},.draw=d,.opt=opt,.ranges=r_Stk9});
        }
      }
    }
    // Gen Truth plots
    for (const auto& cut : { "N", "N_Excl1LepMTdPhiJet" }) {
      // gen lep/top pt
      sh.AddHistos("gen lep",    { .fill="GenLepPtBins",              .pfs={"Signals_Background",cut,"GenLepMother","GenLeptonFlavour"}, .cuts={}, .draw="HIST", .opt=o_1or2d_s+"Norm", .ranges={0,0, 0,1, 0.5,0.53} });
      //sh.AddHistos("gen leptop", { .fill="GenLepTopMatchedGenLepPt",  .pfs={"Signals_Background",cut,"GenTopLeptonFlavour"},             .cuts={}, .draw="HIST", .opt=o_1or2d_s+"Norm", .ranges={0,0, 0,1, 0.5,0.53} }); // Equivalent with above
      sh.AddHistos("gen lep",    { .fill="GenLepPtBins",  .pfs={"MGluinoPoints",  "MLSPPoints","GluinoSignalScans",  cut,"GenLepMother"}, .cuts={}, .draw="HIST", .opt=o_1or2d_s+"Norm", .ranges={0,0, 0,1, 0.5,0.53} });
      sh.AddHistos("gen lep",    { .fill="GenLepPtBins",  .pfs={"MStopPoints",    "MLSPPoints","StopSignalScans",    cut,"GenLepMother"}, .cuts={}, .draw="HIST", .opt=o_1or2d_s+"Norm", .ranges={0,0, 0,1, 0.5,0.53} });
      sh.AddHistos("gen lep",    { .fill="GenLepPtBins",  .pfs={"MCharginoPoints","MLSPPoints","CharginoSignalScans",cut,"GenLepMother"}, .cuts={}, .draw="HIST", .opt=o_1or2d_s+"Norm", .ranges={0,0, 0,1, 0.5,0.53} });
      sh.AddHistos("gen leptop", { .fill="GenLepTopMatchedGenLepPt_vs_GenLepTopPt",   .pfs={"Signals_Background",cut,"GenTopLeptonFlavour"}, .cuts={},.draw="COLZ",.opt=o_1or2d_s+"Log",.ranges={}});
    }
  }
  
  // ROC Curves
  sh.SetHistoWeights({ [this] { return sf_weight['P']*137.0/41.529; } });
  // Leptons
  // Veto
  // N-1
  sh.AddHistos("ele", { .fill="EleVeto_Bkg", .pfs={"elept5_nocomp",   "eleeta_veto_nocomp",
                                                   "eleip_medium",    "eleid_mva_loose",    "eleminiiso_loose"}, .cuts={"P"},.draw="P",.opt="ROC", .ranges={0.5,1, 0.9,1}});
  sh.AddHistos("mu",  { .fill="MuVeto_Bkg",  .pfs={"mupt5_nocomp",    "mueta_nocomp", 
                                                   "muip_loose",      "muid_soft",          "muminiiso_loose"}, .cuts={"P"},.draw="P",.opt="ROC",  .ranges={0.5,1, 0.9,1}});
  // ID Comp (including isolations for ele)
  sh.AddHistos("ele", { .fill="EleVeto_Bkg", .pfs={"elept5_nocomp",   "eleeta_veto_nocomp", "eleip_medium_nocomp",
                                                   "eleid_mva_miniiso_comp", "eleid_mva_iso_comp", "eleid_cut_iso_comp"},   .cuts={"P"},.draw="P",.opt="ROC",   .ranges={0.5,1, 0.9,1}});
  sh.AddHistos("mu",  { .fill="MuVeto_Bkg",  .pfs={"mupt5_nocomp",    "mueta_nocomp",       "muip_loose_nocomp", "muminiiso_loose_nocomp",
                                                   "muid_mva_comp",   "muid_soft_comp","muid_medium_comp","muid_tight_comp"}, .cuts={"P"},.draw="P",.opt="ROC", .ranges={0.5,1, 0.9,1}});
  // Iso Comp
  sh.AddHistos("ele", { .fill="EleVeto_Bkg", .pfs={"elept5_nocomp",   "eleeta_veto_nocomp", "eleip_medium_nocomp", "eleid_mva_loose_nocomp",
                                                   "eleminiiso_comp", "elepfiso_comp"}, .cuts={"P"},.draw="P",.opt="ROC", .ranges={0.5,1, 0.9,1}});
  sh.AddHistos("mu",  { .fill="MuVeto_Bkg",  .pfs={"mupt5_nocomp",    "mueta_nocomp",       "muip_loose_nocomp",  "muid_soft_nocomp",
                                                   "muminiiso_comp",  "mupfiso_comp"}, .cuts={"P"},.draw="P",.opt="ROC",  .ranges={0.5,1, 0.9,1}});
  // Isolated
  // Non-isolated
  // Hadronic tops
  sh.AddHistos("AK8", { .fill="HadTop_T2tt_1200_200",    .pfs={"ak8pt400_nocomp", "tau32_softdrop_sjbtag_comp", "deepTagMD_top_comp", "deepTagMD_top_minsd_comp", "deepTag_top_comp"},  .cuts={"P"},.draw="P",.opt="ROC", .ranges={0,1, 0,1}});
  sh.AddHistos("AK8", { .fill="HadTop_T2tt_1200_1000",   .pfs={"ak8pt400_nocomp", "tau32_softdrop_sjbtag_comp", "deepTagMD_top_comp", "deepTagMD_top_minsd_comp", "deepTag_top_comp"},  .cuts={"P"},.draw="P",.opt="ROC", .ranges={0,1, 0,1}});
  sh.AddHistos("AK8", { .fill="HadTop_T1tttt_2000_200",  .pfs={"ak8pt400_nocomp", "tau32_softdrop_sjbtag_comp", "deepTagMD_top_comp", "deepTagMD_top_minsd_comp", "deepTag_top_comp"},  .cuts={"P"},.draw="P",.opt="ROC", .ranges={0,1, 0,1}});
  sh.AddHistos("AK8", { .fill="HadTop_T1tttt_2000_1000", .pfs={"ak8pt400_nocomp", "tau32_softdrop_sjbtag_comp", "deepTagMD_top_comp", "deepTagMD_top_minsd_comp", "deepTag_top_comp"},  .cuts={"P"},.draw="P",.opt="ROC", .ranges={0,1, 0,1}});
  sh.AddHistos("AK8", { .fill="HadTop_T5ttcc_2000_200",  .pfs={"ak8pt400_nocomp", "tau32_softdrop_sjbtag_comp", "deepTagMD_top_comp", "deepTagMD_top_minsd_comp", "deepTag_top_comp"},  .cuts={"P"},.draw="P",.opt="ROC", .ranges={0,1, 0,1}});
  sh.AddHistos("AK8", { .fill="HadTop_T5ttcc_2000_1000", .pfs={"ak8pt400_nocomp", "tau32_softdrop_sjbtag_comp", "deepTagMD_top_comp", "deepTagMD_top_minsd_comp", "deepTag_top_comp"},  .cuts={"P"},.draw="P",.opt="ROC", .ranges={0,1, 0,1}});
  sh.AddHistos("AK8", { .fill="HadTop_Bkg",              .pfs={"ak8pt400_nocomp", "tau32_softdrop_sjbtag_comp", "deepTagMD_top_comp", "deepTagMD_top_minsd_comp", "deepTag_top_comp"},  .cuts={"P"},.draw="P",.opt="ROC", .ranges={0,1, 0,1}});
  sh.AddHistos("AK8", { .fill="HadTop_T2tt_1200_200",    .pfs={"ak8pt400", "msoftdrop105", "deepTagMD_top_WP1"},  .cuts={"P"},.draw="P",.opt="ROC", .ranges={0,1, 0,1}});
  sh.AddHistos("AK8", { .fill="HadTop_T2tt_1200_200",    .pfs={"ak8pt",    "msoftdrop0",   "deepTag_top_WP1"},    .cuts={"P"},.draw="P",.opt="ROC", .ranges={0,1, 0,1}});
  sh.AddHistos("AK8", { .fill="HadTop_T2tt_1200_1000",   .pfs={"ak8pt400", "msoftdrop105", "deepTagMD_top_WP1"},  .cuts={"P"},.draw="P",.opt="ROC", .ranges={0,1, 0,1}});
  sh.AddHistos("AK8", { .fill="HadTop_T2tt_1200_1000",   .pfs={"ak8pt",    "msoftdrop0",   "deepTag_top_WP1"},    .cuts={"P"},.draw="P",.opt="ROC", .ranges={0,1, 0,1}});
  sh.AddHistos("AK8", { .fill="HadTop_T1tttt_2000_200",  .pfs={"ak8pt400", "msoftdrop105", "deepTagMD_top_WP1"},  .cuts={"P"},.draw="P",.opt="ROC", .ranges={0,1, 0,1}});
  sh.AddHistos("AK8", { .fill="HadTop_T1tttt_2000_200",  .pfs={"ak8pt",    "msoftdrop0",   "deepTag_top_WP1"},    .cuts={"P"},.draw="P",.opt="ROC", .ranges={0,1, 0,1}});
  sh.AddHistos("AK8", { .fill="HadTop_T1tttt_2000_1000", .pfs={"ak8pt400", "msoftdrop105", "deepTagMD_top_WP1"},  .cuts={"P"},.draw="P",.opt="ROC", .ranges={0,1, 0,1}});
  sh.AddHistos("AK8", { .fill="HadTop_T1tttt_2000_1000", .pfs={"ak8pt",    "msoftdrop0",   "deepTag_top_WP1"},    .cuts={"P"},.draw="P",.opt="ROC", .ranges={0,1, 0,1}});
  sh.AddHistos("AK8", { .fill="HadTop_T5ttcc_2000_200",  .pfs={"ak8pt400", "msoftdrop105", "deepTagMD_top_WP1"},  .cuts={"P"},.draw="P",.opt="ROC", .ranges={0,1, 0,1}});
  sh.AddHistos("AK8", { .fill="HadTop_T5ttcc_2000_200",  .pfs={"ak8pt",    "msoftdrop0",   "deepTag_top_WP1"},    .cuts={"P"},.draw="P",.opt="ROC", .ranges={0,1, 0,1}});
  sh.AddHistos("AK8", { .fill="HadTop_T5ttcc_2000_1000", .pfs={"ak8pt400", "msoftdrop105", "deepTagMD_top_WP1"},  .cuts={"P"},.draw="P",.opt="ROC", .ranges={0,1, 0,1}});
  sh.AddHistos("AK8", { .fill="HadTop_T5ttcc_2000_1000", .pfs={"ak8pt",    "msoftdrop0",   "deepTag_top_WP1"},    .cuts={"P"},.draw="P",.opt="ROC", .ranges={0,1, 0,1}});
  sh.AddHistos("AK8", { .fill="HadTop_Bkg",              .pfs={"ak8pt400", "msoftdrop105", "deepTagMD_top_WP1"},  .cuts={"P"},.draw="P",.opt="ROC", .ranges={0,1, 0,1}});
  sh.AddHistos("AK8", { .fill="HadTop_Bkg",              .pfs={"ak8pt",    "msoftdrop0",   "deepTag_top_WP1"},    .cuts={"P"},.draw="P",.opt="ROC", .ranges={0,1, 0,1}});
  
  //sh.AddNewFillParams("HadW",   { .nbin= 2, .bins={-0.5,1.5}, .fill=[] { return ak8MatchGenHadW[i_FatJet];   }});
  //sh.AddNewFillParams("HadZ",   { .nbin= 2, .bins={-0.5,1.5}, .fill=[] { return ak8MatchGenHadZ[i_FatJet];   }});
  //sh.AddNewFillParams("LepTop", { .nbin= 2, .bins={-0.5,1.5}, .fill=[] { return ak8MatchGenLepTop[i_FatJet]; }});







  // Fully hadronic Signal Regions
  // a: had 1top
  // b: had 2top
  // c: had b+W, 4-5 jet
  // d: had b+W, 6+ jet
  // e: had 0b, 1V, 3-4jet
  // f: had 0b, 1V, 5+ jet
  // g: had 0b, 2V, 2-4 jet
  // h: had 0b, 2V, 5+ jet
  for (auto region : {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'}) {
    sh.SetHistoWeights({ [this,region] { return sf_weight[region]*137.0/41.529; } });
    std::string cut = std::string(1,region);
    std::vector<std::string> showdata = {"Blind"};
    // Signal discriminators
    sh.AddHistos("evt",    { .fill="MRFine_vs_METFine",         .pfs={"Signals_Background",cut},          .cuts={},.draw="COLZ",.opt=o_1or2d_s+"Log",.ranges={}});
    sh.AddHistos("evt",    { .fill="R2Fine_vs_METFine",         .pfs={"Signals_Background",cut},          .cuts={},.draw="COLZ",.opt=o_1or2d_s+"Log",.ranges={}});
    sh.AddHistos("evt",    { .fill="R2Fine_vs_MRFine",          .pfs={"Signals_Background",cut},          .cuts={},.draw="COLZ",.opt=o_1or2d_s+"Log",.ranges={}});
    sh.AddHistos("evt",    { .fill="MRFine_vs_HTFine",          .pfs={"Signals_Background",cut},          .cuts={},.draw="COLZ",.opt=o_1or2d_s+"Log",.ranges={}});
    sh.AddHistos("evt",    { .fill="METFine_vs_HTFine",         .pfs={"Signals_Background",cut},          .cuts={},.draw="COLZ",.opt=o_1or2d_s+"Log",.ranges={}});
    sh.AddHistos("evt",    { .fill="R2Fine_vs_MRFine",          .pfs={"Signals_Background",cut},          .cuts={},.draw="COLZ",.opt=o_1or2d_s+"Log",.ranges={}});
    sh.AddHistos("evt",    { .fill="MTBoost_vs_METFine",        .pfs={"Signals_Background",cut},          .cuts={},.draw="COLZ",.opt=o_1or2d_s+"Log",.ranges={}});
    sh.AddHistos("evt",    { .fill="MTBoost_vs_R2Fine",         .pfs={"Signals_Background",cut},          .cuts={},.draw="COLZ",.opt=o_1or2d_s+"Log",.ranges={}});
    sh.AddHistos("evt",    { .fill="MTBoost_vs_MRFine",         .pfs={"Signals_Background",cut},          .cuts={},.draw="COLZ",.opt=o_1or2d_s+"Log",.ranges={}});
    // Stack plots
    for (auto data : showdata ) {
      std::string signal = "StackPlotSignal";
      std::string opt  = (data=="Blind") ? o_stk_s_S : o_stk_d_S;
      if (region=='a'||region=='b'||region=='c'||region=='d') {
        opt    = (data=="Blind") ? o_stk_s_T : o_stk_d_T;
        signal = "StackPlotTopSignal";
      } else if (region=='e'||region=='f'||region=='g'||region=='h') {
        opt    = (data=="Blind") ? o_stk_s_V : o_stk_d_V;
        signal = "StackPlotVSignal";
      }
      for (auto std_plot : standard_plots)
        sh.AddHistos(s+"evt",   { .fill=c+std_plot,                  .pfs={signal,data,cut},                  .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
      sh.AddHistos(  s+"evt",   { .fill=c+"NJet",                    .pfs={signal,data,cut},                  .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
      sh.AddHistos(  s+"evt",   { .fill=c+"NJet",                    .pfs={signal,data,cut+"_ExclNJet"},      .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
      sh.AddHistos(  s+"evt",   { .fill=c+"MTBoost",                 .pfs={signal,data,cut},                  .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
      sh.AddHistos(  s+"evt",   { .fill=c+"DeltaPhi",                .pfs={signal,data,cut+"_ExcldPhi"},      .cuts={},.draw=d,.opt=opt,.ranges=r_Stk9});
    }
  }
  // Isolated lepton Signal Regions
  // i: lep 1hadtop
  // j: lep 1V+b
  // k: lep 1V+0b
  for (auto region : {'i', 'j', 'k'}) {
    sh.SetHistoWeights({ [this,region] { return sf_weight[region]*137.0/41.529; } });
    std::string cut = std::string(1,region);
    std::vector<std::string> showdata = {"Blind"};
    // Signal discriminators
    sh.AddHistos("evt",    { .fill="MRFine_vs_METFine",         .pfs={"Signals_Background",cut},          .cuts={},.draw="COLZ",.opt=o_1or2d_s+"Log",.ranges={}});
    sh.AddHistos("evt",    { .fill="R2Fine_vs_METFine",         .pfs={"Signals_Background",cut},          .cuts={},.draw="COLZ",.opt=o_1or2d_s+"Log",.ranges={}});
    sh.AddHistos("evt",    { .fill="R2Fine_vs_MRFine",          .pfs={"Signals_Background",cut},          .cuts={},.draw="COLZ",.opt=o_1or2d_s+"Log",.ranges={}});
    sh.AddHistos("evt",    { .fill="MRFine_vs_HTFine",          .pfs={"Signals_Background",cut},          .cuts={},.draw="COLZ",.opt=o_1or2d_s+"Log",.ranges={}});
    sh.AddHistos("evt",    { .fill="METFine_vs_HTFine",         .pfs={"Signals_Background",cut},          .cuts={},.draw="COLZ",.opt=o_1or2d_s+"Log",.ranges={}});
    sh.AddHistos("evt",    { .fill="R2Fine_vs_MRFine",          .pfs={"Signals_Background",cut},          .cuts={},.draw="COLZ",.opt=o_1or2d_s+"Log",.ranges={}});
    sh.AddHistos("evt",    { .fill="MTBoost_vs_METFine",        .pfs={"Signals_Background",cut},          .cuts={},.draw="COLZ",.opt=o_1or2d_s+"Log",.ranges={}});
    sh.AddHistos("evt",    { .fill="MTBoost_vs_R2Fine",         .pfs={"Signals_Background",cut},          .cuts={},.draw="COLZ",.opt=o_1or2d_s+"Log",.ranges={}});
    sh.AddHistos("evt",    { .fill="MTBoost_vs_MRFine",         .pfs={"Signals_Background",cut},          .cuts={},.draw="COLZ",.opt=o_1or2d_s+"Log",.ranges={}});
    // Stack plots
    for (auto data : showdata ) {
      std::string signal = "StackPlotSignal";
      std::string opt  = (data=="Blind") ? o_stk_s_S : o_stk_d_S;
      if (region=='i') {
        opt    = (data=="Blind") ? o_stk_s_T : o_stk_d_T;
        signal = "StackPlotTopSignal";
      } else if (region=='k') {
        opt    = (data=="Blind") ? o_stk_s_V : o_stk_d_V;
        signal = "StackPlotVSignal";
      }
      for (auto std_plot : standard_plots)
        sh.AddHistos(s+"evt",   { .fill=c+std_plot,                    .pfs={signal,data,cut},                  .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
      sh.AddHistos(s+"evt",  { .fill=c+"NJet",                         .pfs={signal,data,cut},                  .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
      sh.AddHistos(s+"evt",  { .fill=c+"NJet",                         .pfs={signal,data,cut+"_ExclNJet"},      .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
      sh.AddHistos(s+"evt",  { .fill=c+"MTBoost",                      .pfs={signal,data,cut},                  .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
      sh.AddHistos(s+"evt",  { .fill=c+"DeltaPhi",                     .pfs={signal,data,cut},                  .cuts={},.draw=d,.opt=opt,.ranges=r_Stk9});
      sh.AddHistos(s+"evt",  { .fill=c+"NJet",                         .pfs={signal,data,cut},                    .cuts={},.draw=d,.opt=opt,.ranges=r_Stk5});
      sh.AddHistos(s+"evt",  { .fill=c+"NJet",                         .pfs={signal,data,cut+"_ExclNJet"},           .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
      sh.AddHistos(s+"evt",  { .fill=c+"MTBoost",                      .pfs={signal,data,cut},                    .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
      sh.AddHistos(s+"evt",  { .fill=c+"DeltaPhi",                     .pfs={signal,data,cut},                    .cuts={},.draw=d,.opt=opt,.ranges=r_Stk9});
      sh.AddHistos(s+"evt",  { .fill=c+"DeltaPhi",                     .pfs={signal,data,cut+"_ExclMT"},             .cuts={},.draw=d,.opt=opt,.ranges=r_Stk9});
      sh.AddHistos(s+"evt",  { .fill=c+"MT",                           .pfs={signal,data,cut+"_ExclMT"},             .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
      // TODO: Add leptonic discriminators similar to non-iso leptons (dphi etc)
      //sh.AddHistos(s+"evt",  { .fill=c+"DeltaPhiBoostedJetMET",        .pfs={signal,data,cut},                    .cuts={},.draw=d,.opt=opt,.ranges=r_Stk5});
      //sh.AddHistos(s+"evt",  { .fill=c+"DeltaPhiBoostedJetLep",        .pfs={signal,data,cut},                    .cuts={},.draw=d,.opt=opt,.ranges=r_Stk5});
      //sh.AddHistos(s+"evt",  { .fill=c+"DeltaPhiBoostedJetMET",        .pfs={signal,data,cut},                    .cuts={},.draw=d,.opt=opt,.ranges=r_Stk5});
    }
  }


  // Non-isolated lepton Signal Regions
  // l: 1leptop 0hadtop
  // m: 1leptop 1hadtop
  // n: 1lepjet 0b, 0V, 2-4 jet
  // o: 1lepjet 0b, 0V, 5+ jet
  // p: 1lepjet 0b, 1V, 2-4 jet
  // q: 1lepjet 0b, 1V, 5+ jet
  for (auto region : {'l', 'm', 'n', 'o', 'p', 'q'}) {
    sh.SetHistoWeights({ [this,region] { return sf_weight[region]*137.0/41.529; } });
    std::string cut = std::string(1,region);
    std::vector<std::string> showdata = {"Blind"};
    // Signal discriminators
    sh.AddHistos("evt",    { .fill="MRFine_vs_METFine",         .pfs={"Signals_Background",cut},          .cuts={},.draw="COLZ",.opt=o_1or2d_s+"Log",.ranges={}});
    sh.AddHistos("evt",    { .fill="R2Fine_vs_METFine",         .pfs={"Signals_Background",cut},          .cuts={},.draw="COLZ",.opt=o_1or2d_s+"Log",.ranges={}});
    sh.AddHistos("evt",    { .fill="R2Fine_vs_MRFine",          .pfs={"Signals_Background",cut},          .cuts={},.draw="COLZ",.opt=o_1or2d_s+"Log",.ranges={}});
    sh.AddHistos("evt",    { .fill="MRFine_vs_HTFine",          .pfs={"Signals_Background",cut},          .cuts={},.draw="COLZ",.opt=o_1or2d_s+"Log",.ranges={}});
    sh.AddHistos("evt",    { .fill="METFine_vs_HTFine",         .pfs={"Signals_Background",cut},          .cuts={},.draw="COLZ",.opt=o_1or2d_s+"Log",.ranges={}});
    sh.AddHistos("evt",    { .fill="R2Fine_vs_MRFine",          .pfs={"Signals_Background",cut},          .cuts={},.draw="COLZ",.opt=o_1or2d_s+"Log",.ranges={}});
    sh.AddHistos("evt",    { .fill="MTBoost_vs_METFine",        .pfs={"Signals_Background",cut},          .cuts={},.draw="COLZ",.opt=o_1or2d_s+"Log",.ranges={}});
    sh.AddHistos("evt",    { .fill="MTBoost_vs_R2Fine",         .pfs={"Signals_Background",cut},          .cuts={},.draw="COLZ",.opt=o_1or2d_s+"Log",.ranges={}});
    sh.AddHistos("evt",    { .fill="MTBoost_vs_MRFine",         .pfs={"Signals_Background",cut},          .cuts={},.draw="COLZ",.opt=o_1or2d_s+"Log",.ranges={}});
    // Stack plots
    for (auto data : showdata ) {
      std::string signal = "StackPlotSignal";
      std::string opt  = (data=="Blind") ? o_stk_s_S : o_stk_d_S;
      if (region=='l'||region=='m') {
        opt    = (data=="Blind") ? o_stk_s_T : o_stk_d_T;
        signal = "StackPlotTopSignal";
      } else if (region=='n'||region=='o'||region=='p'||region=='q') {
        opt    = (data=="Blind") ? o_stk_s_V : o_stk_d_V;
        signal = "StackPlotVSignal";
      }
      for (auto std_plot : standard_plots)
        sh.AddHistos(s+"evt",   { .fill=c+std_plot,                    .pfs={signal,data,cut},                  .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
      sh.AddHistos(s+"evt",  { .fill=c+"NJet",                         .pfs={signal,data,cut},                  .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
      sh.AddHistos(s+"evt",  { .fill=c+"NJet",                         .pfs={signal,data,cut+"_ExclNJet"},      .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
      sh.AddHistos(s+"evt",  { .fill=c+"MTBoost",                      .pfs={signal,data,cut},                  .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
      sh.AddHistos(s+"evt",  { .fill=c+"DeltaPhi",                     .pfs={signal,data,cut},                  .cuts={},.draw=d,.opt=opt,.ranges=r_Stk9});
      sh.AddHistos(s+"evt",  { .fill=c+"NJet",                         .pfs={signal,data,cut},                    .cuts={},.draw=d,.opt=opt,.ranges=r_Stk5});
      sh.AddHistos(s+"evt",  { .fill=c+"NJet",                         .pfs={signal,data,cut+"_ExclNJet"},           .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
      sh.AddHistos(s+"evt",  { .fill=c+"MTBoost",                      .pfs={signal,data,cut},                    .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
      sh.AddHistos(s+"evt",  { .fill=c+"DeltaPhi",                     .pfs={signal,data,cut},                    .cuts={},.draw=d,.opt=opt,.ranges=r_Stk9});
      sh.AddHistos(s+"evt",  { .fill=c+"DeltaPhi",                     .pfs={signal,data,cut+"_ExclMT"},             .cuts={},.draw=d,.opt=opt,.ranges=r_Stk9});
      sh.AddHistos(s+"evt",  { .fill=c+"MT",                           .pfs={signal,data,cut+"_ExclMT"},             .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
      sh.AddHistos(s+"evt",  { .fill=c+"DeltaPhiBoostedJetMET",        .pfs={signal,data,cut},                    .cuts={},.draw=d,.opt=opt,.ranges=r_Stk5});
      sh.AddHistos(s+"evt",  { .fill=c+"DeltaPhiBoostedJetLep",        .pfs={signal,data,cut},                    .cuts={},.draw=d,.opt=opt,.ranges=r_Stk5});
      sh.AddHistos(s+"evt",  { .fill=c+"DeltaPhiBoostedJetMET",        .pfs={signal,data,cut+"_ExcldPhiJet"},     .cuts={},.draw=d,.opt=opt,.ranges=r_Stk5});
      sh.AddHistos(s+"evt",  { .fill=c+"DeltaPhiBoostedJetLep",        .pfs={signal,data,cut+"_ExcldPhiJet"},     .cuts={},.draw=d,.opt=opt,.ranges=r_Stk5});
      sh.AddHistos(s+"evt",  { .fill=c+"DeltaPhiBoostedJetLepMET",     .pfs={signal,data,cut+"_ExcldPhiJet"},     .cuts={},.draw=d,.opt=opt,.ranges=r_Stk5});
    }
  }




  // ----------------------------------------------------------------------------------------------
  //                                       W/Top ANALYSIS
  //-----------------------------------------------------------------------------------------------


  // -------------------------------------------------------------------------
  //                              Selected AK4 Jets

  for (auto region : {'P', 'R', 'S', 's', 'T', 'W', 'Q', 'q', 'L', 'Z', 'G', 'H', 'F', 'B'}) {
    sh.SetHistoWeights({ [this,region] { return sf_weight[region]; } });
    std::string cut = std::string(1,region);
    std::vector<std::string> showdata = {"JetHTMET"};
    if (region=='S') showdata.push_back("Blind");
    for (auto data : showdata ) {
      std::string opt = (data=="Blind") ? o_stk_s : o_stk_d;
      sh.AddHistos(s+"AK4",  { .fill=c+"JetPtBins",                       .pfs={Stack,data,cut}, .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
      sh.AddHistos(s+"AK4",  { .fill=c+"JetPt",                           .pfs={Stack,data,cut}, .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
      sh.AddHistos(s+"AK4",  { .fill=c+"JetEta",                          .pfs={Stack,data,cut}, .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
      sh.AddHistos(s+"AK4",  { .fill=c+"JetPhi",                          .pfs={Stack,data,cut}, .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
      sh.AddHistos(s+"AK4",  { .fill=c+"JetCSV",                          .pfs={Stack,data,cut}, .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
      sh.AddHistos("AK4",    { .fill="JetPhotonDR",                       .pfs={Stack,data,cut}, .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
      sh.AddHistos("AK4",    { .fill="JetPhotonPtRatio",                  .pfs={Stack,data,cut}, .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
      sh.AddHistos("AK4",    { .fill="JetPhotonPtRatio",                  .pfs={Stack,data,cut,"JetPhotonDR0.05"}, .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
      sh.AddHistos("AK4",    { .fill="JetPhotonPtRatio",                  .pfs={Stack,data,cut,"JetPhotonDR0.4"},  .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
      sh.AddHistos("AK4",    { .fill="JetPhotonDR_vs_JetPhotonPtRatio",   .pfs={"Data_MC",cut},  .cuts={},.draw="COLZ",.opt=o_1or2d_d, .ranges={}});
      sh.AddHistos("AK4",    { .fill="JetEleDR",                          .pfs={Stack,data,cut}, .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
      sh.AddHistos("AK4",    { .fill="JetElePtRatio",                     .pfs={Stack,data,cut}, .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
      sh.AddHistos("AK4",    { .fill="JetElePtRatio",                     .pfs={Stack,data,cut,"JetEleDR0.05"}, .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
      sh.AddHistos("AK4",    { .fill="JetElePtRatio",                     .pfs={Stack,data,cut,"JetEleDR0.4"},  .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
      sh.AddHistos("AK4",    { .fill="JetEleDR_vs_JetElePtRatio",         .pfs={"Data_MC",cut},  .cuts={},.draw="COLZ",.opt=o_1or2d_d, .ranges={}});
      sh.AddHistos("AK4",    { .fill="JetMuonDR",                         .pfs={Stack,data,cut}, .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
      sh.AddHistos("AK4",    { .fill="JetMuonPtRatio",                    .pfs={Stack,data,cut}, .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
      sh.AddHistos("AK4",    { .fill="JetMuonPtRatio",                    .pfs={Stack,data,cut,"JetMuonDR0.05"}, .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
      sh.AddHistos("AK4",    { .fill="JetMuonPtRatio",                    .pfs={Stack,data,cut,"JetMuonDR0.4"},  .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
      sh.AddHistos("AK4",    { .fill="JetMuonDR_vs_JetMuonPtRatio",       .pfs={"Data_MC",cut},  .cuts={},.draw="COLZ",.opt=o_1or2d_d, .ranges={}});
    }
  }

  // -------------------------------------------------------------------------
  //                                  Leptons
  
  // Leptons
  for (auto region : {'P', 'S', 's', 'Q', 'q', 'T', 'W', 'L', 'G', 'H'}) {
  //for (auto region : {'S', 's', 'Q', 'q'}) {
    sh.SetHistoWeights({ [this,region] { return sf_weight[region]; } });
    std::string cut = std::string(1,region);
    std::vector<std::string> showdata = {"JetHTMET"};
    if (region=='S') showdata.push_back("Blind");
    for (auto data : showdata)  {
      if (region=='P') {
        sh.AddHistos(s+"evt",      { .fill=c+"NEleVeto",             .pfs={Stack,data,cut},                    .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
        sh.AddHistos(s+"ele veto", { .fill=c+"VetoElePt",            .pfs={Stack,data,cut},                    .cuts={},.draw=d,.opt=o_stk_d+"logX",.ranges=r_Stk6});
        sh.AddHistos(s+"ele veto", { .fill=c+"VetoEleEta",           .pfs={Stack,data,cut},                    .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
        sh.AddHistos(s+"evt",      { .fill=c+"NMuVeto",              .pfs={Stack,data,cut},                    .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
        sh.AddHistos(s+"mu veto",  { .fill=c+"VetoMuPt",             .pfs={Stack,data,cut},                    .cuts={},.draw=d,.opt=o_stk_d+"logX",.ranges=r_Stk6});
        sh.AddHistos(s+"mu veto",  { .fill=c+"VetoMuEta",            .pfs={Stack,data,cut},                    .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
        sh.AddHistos(s+"evt",      { .fill=c+"NLepVeto",             .pfs={Stack,data,cut},                    .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
        sh.AddHistos(s+"evt",      { .fill=c+"NIsoTrk",              .pfs={Stack,data,cut},                    .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
        sh.AddHistos(s+"evt",      { .fill=c+"NTauVeto",             .pfs={Stack,data,cut},                    .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
        sh.AddHistos(s+"tau veto", { .fill=c+"VetoTauPt",            .pfs={Stack,data,cut},                    .cuts={},.draw=d,.opt=o_stk_d+"logX",.ranges=r_Stk6});
        sh.AddHistos(s+"tau veto", { .fill=c+"VetoTauEta",           .pfs={Stack,data,cut},                    .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
        sh.AddHistos("ele tight noiso", { .fill="EleCleanJetDRmin",                     .pfs={"Signals_Background",cut,"MatchGenEleFromTop"},  .cuts={},.draw="HIST",.opt=o_1or2d_s+"Log",.ranges={}});
        sh.AddHistos("ele tight noiso", { .fill="EleCleanJetPtrel",                     .pfs={"Signals_Background",cut,"MatchGenEleFromTop"},  .cuts={},.draw="HIST",.opt=o_1or2d_s+"Log",.ranges={}});
        sh.AddHistos("ele tight noiso", { .fill="EleCleanJetPtrel_vs_EleCleanJetDRmin", .pfs={"Signals_Background",cut,"MatchGenEleFromTop"},  .cuts={},.draw="COLZ",.opt=o_1or2d_s+"Log",.ranges={}});
        sh.AddHistos("mu tight noiso",  { .fill="MuCleanJetDRmin",                      .pfs={"Signals_Background",cut,"MatchGenMuFromTop"},   .cuts={},.draw="HIST",.opt=o_1or2d_s+"Log",.ranges={}});
        sh.AddHistos("mu tight noiso",  { .fill="MuCleanJetPtrel",                      .pfs={"Signals_Background",cut,"MatchGenMuFromTop"},   .cuts={},.draw="HIST",.opt=o_1or2d_s+"Log",.ranges={}});
        sh.AddHistos("mu tight noiso",  { .fill="MuCleanJetPtrel_vs_MuCleanJetDRmin",   .pfs={"Signals_Background",cut,"MatchGenMuFromTop"},   .cuts={},.draw="COLZ",.opt=o_1or2d_s+"Log",.ranges={}});
      } else if (region=='T'||region=='W'||region=='L') {
        sh.AddHistos(s+"evt",      { .fill=c+"NEleVeto",             .pfs={Stack,data,cut+"_Excl1LepMT"},      .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
        sh.AddHistos(s+"ele veto", { .fill=c+"VetoElePt",            .pfs={Stack,data,cut},                    .cuts={},.draw=d,.opt=o_stk_d+"logX",.ranges=r_Stk6});
        sh.AddHistos(s+"ele veto", { .fill=c+"VetoEleEta",           .pfs={Stack,data,cut},                    .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
        sh.AddHistos(s+"evt",      { .fill=c+"NMuVeto",              .pfs={Stack,data,cut+"_Excl1LepMT"},      .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
        sh.AddHistos(s+"mu veto",  { .fill=c+"VetoMuPt",             .pfs={Stack,data,cut},                    .cuts={},.draw=d,.opt=o_stk_d+"logX",.ranges=r_Stk6});
        sh.AddHistos(s+"mu veto",  { .fill=c+"VetoMuEta",            .pfs={Stack,data,cut},                    .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
        sh.AddHistos(s+"evt",      { .fill=c+"NLepVeto",             .pfs={Stack,data,cut+"_Excl1LepMT"},      .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
      } else {
        std::string opt = (data=="Blind") ? o_stk_s : o_stk_d;
        sh.AddHistos(s+"evt",      { .fill=c+"NEleVeto",             .pfs={Stack,data,cut+"_Excl0Ele0Tau"}, .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
        sh.AddHistos(s+"ele veto", { .fill=c+"VetoElePt",            .pfs={Stack,data,cut+"_Excl0Ele0Tau"}, .cuts={},.draw=d,.opt=o_stk_d+"logX",.ranges=r_Stk6});
        sh.AddHistos(s+"ele veto", { .fill=c+"VetoEleEta",           .pfs={Stack,data,cut+"_Excl0Ele0Tau"}, .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
        sh.AddHistos(s+"evt",      { .fill=c+"NMuVeto",              .pfs={Stack,data,cut+"_Excl0Mu0Tau"},  .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
        sh.AddHistos(s+"mu veto",  { .fill=c+"VetoMuPt",             .pfs={Stack,data,cut+"_Excl0Mu0Tau"},  .cuts={},.draw=d,.opt=o_stk_d+"logX",.ranges=r_Stk6});
        sh.AddHistos(s+"mu veto",  { .fill=c+"VetoMuEta",            .pfs={Stack,data,cut+"_Excl0Mu0Tau"},  .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
        sh.AddHistos(s+"evt",      { .fill=c+"NLepVeto",             .pfs={Stack,data,cut+"_Excl0Ele0Mu0Tau"}, .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
        sh.AddHistos(s+"evt",      { .fill=c+"NIsoTrk",              .pfs={Stack,data,cut+"_Excl0Tau"},  .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
        sh.AddHistos(s+"evt",      { .fill=c+"NTauVeto",             .pfs={Stack,data,cut+"_Excl0Tau"},  .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
        sh.AddHistos(s+"tau veto", { .fill=c+"VetoTauPt",            .pfs={Stack,data,cut+"_Excl0Tau"},  .cuts={},.draw=d,.opt=o_stk_d+"logX",.ranges=r_Stk6});
        sh.AddHistos(s+"tau veto", { .fill=c+"VetoTauEta",           .pfs={Stack,data,cut+"_Excl0Tau"},  .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
      }
    }
  }

  // Selected Leptons
  for (auto region : {'P', 'Z'}) {
  //for (auto region : {'Z', 'T', 'W'}) {
    sh.SetHistoWeights({ [this,region] { return sf_weight[region]; } });
    std::string cut = std::string(1,region);
    std::string cut2 = cut;
    if (region=='Z') cut2 += "_ExclR2ll2Lep";
    //else cut2 += "_Excl1LepMT";

    sh.AddHistos(s+"evt",  { .fill=c+"ElePt",                      .pfs={Stack,"JetHTMET",cut},  .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
    sh.AddHistos(s+"evt",  { .fill=c+"EleEta",                     .pfs={Stack,"JetHTMET",cut},  .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
    sh.AddHistos(s+"evt",  { .fill=c+"MuPt",                       .pfs={Stack,"JetHTMET",cut},  .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
    sh.AddHistos(s+"evt",  { .fill=c+"MuEta",                      .pfs={Stack,"JetHTMET",cut},  .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
    
    sh.AddHistos(s+"evt",  { .fill=c+"NLep",                       .pfs={Stack,"JetHTMET",cut2}, .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
    sh.AddHistos(s+"evt",  { .fill=c+"NEle",                       .pfs={Stack,"JetHTMET",cut2}, .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
    sh.AddHistos(s+"evt",  { .fill=c+"NMu",                        .pfs={Stack,"JetHTMET",cut2}, .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
    sh.AddHistos(s+"evt",  { .fill=c+"NLepTight",                  .pfs={Stack,"JetHTMET",cut2}, .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
    sh.AddHistos(s+"evt",  { .fill=c+"NLepTightNoIso",             .pfs={Stack,"JetHTMET",cut2}, .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
    sh.AddHistos(s+"evt",  { .fill=c+"NEleTightNoIso",             .pfs={Stack,"JetHTMET",cut2}, .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
    sh.AddHistos(s+"evt",  { .fill=c+"NMuTightNoIso",              .pfs={Stack,"JetHTMET",cut2}, .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
    sh.AddHistos(s+"evt",  { .fill=c+"NLepTight2D",                .pfs={Stack,"JetHTMET",cut2}, .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
    sh.AddHistos(s+"evt",  { .fill=c+"NEleTight2D",                .pfs={Stack,"JetHTMET",cut2}, .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
    sh.AddHistos(s+"evt",  { .fill=c+"NMuTight2D",                 .pfs={Stack,"JetHTMET",cut2}, .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
  }


  // -------------------------------------------------------------------------
  //                                     bs

  // Selected b-tags
  for (auto region : {'P', 'S', 's', 'T', 'Z', 'G', 'H'}) {
    sh.SetHistoWeights({ [this,region] { return sf_weight[region]; } });
    
    std::string cut1 = std::string(1,region);
    std::string cut2 = cut1;
#if TOP == 0
    if (region=='P'||region=='Z'||region=='G') 
      sh.SetHistoWeights({ [this,region] { return sf_weight[region]*scale_factors['S'][2]; } });
    if (region=='S'||region=='s'||region=='T') cut2 += "_Excl1b";
#else
    if (region=='S'||region=='s'||region=='T') cut2 += "_Excl1Top";
#endif
    std::vector<std::string> showdata = {"JetHTMET"};
    if (region=='S') showdata.push_back("Blind");
    for (auto data : showdata ) {
      std::string opt = (data=="Blind") ? o_stk_s : o_stk_d;
      sh.AddHistos(s+"b",    { .fill=c+"BJetPtBins",          .pfs={Stack,data,cut1}, .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
      sh.AddHistos(s+"b",    { .fill=c+"BJetPt",              .pfs={Stack,data,cut1}, .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
      sh.AddHistos(s+"b",    { .fill=c+"BJetEta",             .pfs={Stack,data,cut1}, .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
      sh.AddHistos(s+"b",    { .fill=c+"BJetPhi",             .pfs={Stack,data,cut1}, .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
      sh.AddHistos(s+"b",    { .fill=c+"BJetCSV",             .pfs={Stack,data,cut1}, .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
      sh.AddHistos(s+"evt",  { .fill=c+"NBTag",               .pfs={Stack,data,cut1}, .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
      if (region!='P'&&region!='Z'&&region!='G'&&region!='H')
	sh.AddHistos(s+"evt",  { .fill=c+"NBTag",               .pfs={Stack,data,cut2}, .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
    }
  }

  // Veto b-tags
  for (auto region : {'P', 'Q', 'q', 'W', 'L', 'Z', 'G', 'H'}) {
    sh.SetHistoWeights({ [this,region] { return sf_weight[region]; } });
    std::string cut1 = std::string(1,region);
    std::string cut2 = cut1;
#if TOP == 0
    if (region=='Q'||region=='q'||region=='W'||region=='L') cut2 += "_Excl0b";
#else
    if      (region=='Q'||region=='q') cut2 += "_Excl0b";
    else if (region=='W'||region=='L') cut2 += "_Excl0b";
#endif
    sh.AddHistos(s+"evt",  { .fill=c+"NLooseBTag",          .pfs={Stack,"JetHTMET",cut1}, .cuts={},.draw=d,.opt=O_stk_d+"NoComb5",.ranges={0,0, 1.01e-2,1e6,  0.5,0.86}});
    if (region!='P'&&region!='Z'&&region!='G'&&region!='H')
      sh.AddHistos(s+"evt",  { .fill=c+"NLooseBTag",          .pfs={Stack,"JetHTMET",cut2}, .cuts={},.draw=d,.opt=O_stk_d+"NoComb5",.ranges={0,0, 1.01e-2,1e6,  0.5,0.86}});
  }

  // -------------------------------------------------------------------------
  //                                 AK8/Ws Jets

  for (auto region : {'P', 'R', 'S', 's', 'T','W','Q', 'q', 'L', 'Z', 'G', 'H', 'F', 'B'}) {
    sh.SetHistoWeights({ [this,region] { return sf_weight[region]; } });
    std::string cut1 = std::string(1,region);
    std::string cut2 = cut1;
#if TOP == 0
    if      (region=='S'||region=='s'||region=='T') cut2 += "_Excl1W";
    else if (region=='Q'||region=='q') cut2 += "_Excl1aW";
    else if (region=='W') cut2 += "_Excl1mW";
    else if (region=='L'||region=='Z'||region=='G') cut2 += "_Excl1mW";
#else
    if      (region=='S'||region=='s'||region=='T') cut2 += "_Excl1Top";
    else if (region=='Q'||region=='q') cut2 += "_Excl1aTop";
    else if (region=='W'||region=='L') cut2 += "_Excl1mTop";
    else if (region=='Z'||region=='G') cut2 += "_Excl1MTop";
#endif
    std::vector<std::string> showdata = {"JetHTMET"};
    if (region=='S') showdata.push_back("Blind");
    std::vector<std::string> cuts;
    cuts.push_back(cut1);
    if (cut2!=cut1) cuts.push_back(cut2);
    for (auto cut : cuts) {
      for (auto data : showdata ) {
	std::string opt = (data=="Blind") ? o_stk_s : o_stk_d;
	std::string Opt = (data=="Blind") ? O_stk_s : O_stk_d;
	// AK8 jets
	sh.AddHistos(s+"evt",  { .fill=c+"NJetAK8",            .pfs={Stack,data,cut},               .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
	sh.AddHistos(s+"AK8",  { .fill=c+"JetAK8PtBins",       .pfs={Stack,data,cut},               .cuts={},.draw=d,.opt=opt,.ranges=r_Stk8});
	sh.AddHistos(s+"AK8",  { .fill=c+"JetAK8Pt",           .pfs={Stack,data,cut},               .cuts={},.draw=d,.opt=opt,.ranges=r_Stk8});
	sh.AddHistos(s+"AK8",  { .fill=c+"JetAK8Eta",          .pfs={Stack,data,cut},               .cuts={},.draw=d,.opt=opt,.ranges=r_Stk8});
	sh.AddHistos(s+"AK8",  { .fill=c+"JetAK8Phi",          .pfs={Stack,data,cut},               .cuts={},.draw=d,.opt=opt,.ranges=r_Stk8});
	sh.AddHistos(s+"AK8",  { .fill=c+"JetAK8Mass",         .pfs={Stack,data,cut},               .cuts={},.draw=d,.opt=opt,.ranges=r_Stk8});
	sh.AddHistos(s+"AK8",  { .fill=c+"JetAK8Mass",         .pfs={Stack,data,cut,"Tau21Tagged"}, .cuts={},.draw=d,.opt=Opt,.ranges={0,0, 1.01e-2,1e8,  0.3,0.86, 0.21}});
	sh.AddHistos(s+"AK8",  { .fill=c+"JetAK8Mass",         .pfs={Stack,data,cut,"Tau32Tagged"}, .cuts={},.draw=d,.opt=Opt,.ranges={0,0, 1.01e-2,1e8,  0.3,0.86}});
	sh.AddHistos(s+"AK8",  { .fill=c+"JetAK8Mass",         .pfs={Stack,data,cut,"AK8_EB_EE"},               .cuts={},.draw=d,.opt=opt,.ranges=r_Stk8});
	sh.AddHistos(s+"AK8",  { .fill=c+"JetAK8Mass",         .pfs={Stack,data,cut,"AK8_EB_EE","Tau21Tagged"}, .cuts={},.draw=d,.opt=opt,.ranges=r_Stk8});
	sh.AddHistos(s+"AK8",  { .fill=c+"JetAK8Mass",         .pfs={Stack,data,cut,"AK8_EB_EE","Tau32Tagged"}, .cuts={},.draw=d,.opt=opt,.ranges=r_Stk8});
	sh.AddHistos(s+"AK8",  { .fill=c+"JetAK8Tau21",        .pfs={Stack,data,cut},               .cuts={},.draw=d,.opt=opt,.ranges=r_Stk8});
	sh.AddHistos(s+"AK8",  { .fill=c+"JetAK8Tau32",        .pfs={Stack,data,cut},               .cuts={},.draw=d,.opt=opt,.ranges=r_Stk8});
	sh.AddHistos(s+"AK8",  { .fill=c+"MaxAK8SubJetCSV",    .pfs={Stack,data,cut},               .cuts={},.draw=d,.opt=opt,.ranges=r_Stk8});
	sh.AddHistos("AK8",    { .fill="JetAK8PhotonDR",       .pfs={Stack,data,cut},               .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
	sh.AddHistos("AK8",    { .fill="JetAK8PhotonPtRatio",  .pfs={Stack,data,cut},               .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
	sh.AddHistos("AK8",    { .fill="JetAK8PhotonPtRatio",  .pfs={Stack,data,cut,"JetAK8PhotonDR0.05"}, .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
	sh.AddHistos("AK8",    { .fill="JetAK8PhotonPtRatio",  .pfs={Stack,data,cut,"JetAK8PhotonDR0.8"}, .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
	sh.AddHistos("AK8",    { .fill="JetAK8PhotonDR_vs_JetAK8PhotonPtRatio", .pfs={"Data_MC",cut},  .cuts={},.draw="COLZ",.opt=o_1or2d_d, .ranges={}});
	sh.AddHistos("AK8",    { .fill="JetAK8EleDR",          .pfs={Stack,data,cut},               .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
	sh.AddHistos("AK8",    { .fill="JetAK8ElePtRatio",     .pfs={Stack,data,cut},               .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
	sh.AddHistos("AK8",    { .fill="JetAK8ElePtRatio",     .pfs={Stack,data,cut,"JetAK8EleDR0.05"}, .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
	sh.AddHistos("AK8",    { .fill="JetAK8ElePtRatio",     .pfs={Stack,data,cut,"JetAK8EleDR0.8"}, .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
	sh.AddHistos("AK8",    { .fill="JetAK8EleDR_vs_JetAK8ElePtRatio", .pfs={"Data_MC",cut},  .cuts={},.draw="COLZ",.opt=o_1or2d_d, .ranges={}});
	sh.AddHistos("AK8",    { .fill="JetAK8MuonDR",         .pfs={Stack,data,cut},               .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
	sh.AddHistos("AK8",    { .fill="JetAK8MuonPtRatio",    .pfs={Stack,data,cut},               .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
	sh.AddHistos("AK8",    { .fill="JetAK8MuonPtRatio",    .pfs={Stack,data,cut,"JetAK8MuonDR0.05"}, .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
	sh.AddHistos("AK8",    { .fill="JetAK8MuonPtRatio",    .pfs={Stack,data,cut,"JetAK8MuonDR0.8"}, .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
	sh.AddHistos("AK8",    { .fill="JetAK8MuonDR_vs_JetAK8MuonPtRatio", .pfs={"Data_MC",cut},  .cuts={},.draw="COLZ",.opt=o_1or2d_d, .ranges={}});

        // Deep AK8 tagger plots
	sh.AddHistos(s+"AK8",  { .fill=c+"JetAK8DeepTagWvsQCD",.pfs={Stack,data,cut},               .cuts={},.draw=d,.opt=opt,.ranges=r_Stk8});
	sh.AddHistos(s+"AK8",  { .fill=c+"JetAK8DeepTagTvsQCD",.pfs={Stack,data,cut},               .cuts={},.draw=d,.opt=opt,.ranges=r_Stk8});
	sh.AddHistos(s+"mW",   { .fill=c+"mWDeepTagWvsQCD",    .pfs={Stack,data,cut},               .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
	sh.AddHistos(s+"MTop", { .fill=c+"MTopDeepTagTvsQCD",  .pfs={Stack,data,cut},               .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});

#if TOP == 0
	// Mass-tagged Ws
	sh.AddHistos(s+"evt",  { .fill=c+"NmW",                .pfs={Stack,data,cut},               .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
	sh.AddHistos(s+"mW",   { .fill=c+"mWPtBins",           .pfs={Stack,data,cut},               .cuts={},.draw=d,.opt=opt,.ranges=r_Stk8});
	sh.AddHistos(s+"mW",   { .fill=c+"mWPt",               .pfs={Stack,data,cut},               .cuts={},.draw=d,.opt=opt,.ranges=r_Stk8});
	sh.AddHistos(s+"mW",   { .fill=c+"mWEta",              .pfs={Stack,data,cut},               .cuts={},.draw=d,.opt=opt,.ranges=r_Stk8});
	sh.AddHistos(s+"mW",   { .fill=c+"mWPhi",              .pfs={Stack,data,cut},               .cuts={},.draw=d,.opt=opt,.ranges=r_Stk8});
	sh.AddHistos(s+"mW",   { .fill=c+"mWTau21",            .pfs={Stack,data,cut},               .cuts={},.draw=d,.opt=Opt+"NoComb5",.ranges={0,0, 1.01e-2,1e6,  0.53,0.86}});
	sh.AddHistos(s+"mW",   { .fill=c+"mWMass",             .pfs={Stack,data,cut},               .cuts={},.draw=d,.opt=opt,.ranges=r_Stk8});

	// Anti-tagged Ws
	sh.AddHistos(s+"evt",  { .fill=c+"NaW",                .pfs={Stack,data,cut},               .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
	sh.AddHistos(s+"aW",   { .fill=c+"aWPtBins",           .pfs={Stack,data,cut},               .cuts={},.draw=d,.opt=opt,.ranges=r_Stk8});
	sh.AddHistos(s+"aW",   { .fill=c+"aWPt",               .pfs={Stack,data,cut},               .cuts={},.draw=d,.opt=opt,.ranges=r_Stk8});
	sh.AddHistos(s+"aW",   { .fill=c+"aWEta",              .pfs={Stack,data,cut},               .cuts={},.draw=d,.opt=opt,.ranges=r_Stk8});
	sh.AddHistos(s+"aW",   { .fill=c+"aWPhi",              .pfs={Stack,data,cut},               .cuts={},.draw=d,.opt=opt,.ranges=r_Stk8});
	sh.AddHistos(s+"aW",   { .fill=c+"aWTau21",            .pfs={Stack,data,cut},               .cuts={},.draw=d,.opt=opt,.ranges=r_Stk8});
	sh.AddHistos(s+"aW",   { .fill=c+"aWMass",             .pfs={Stack,data,cut},               .cuts={},.draw=d,.opt=opt,.ranges=r_Stk8});

	// Tagged Ws
	// Add W scale factor
	if (region=='P') sh.SetHistoWeights({ [this,region] { return sf_weight[region]*scale_factors['S'][3]; } });
	sh.AddHistos(s+"W",    { .fill=c+"WPtBins",            .pfs={Stack,data,cut},               .cuts={},.draw=d,.opt=opt,.ranges=r_Stk4});
	sh.AddHistos(s+"W",    { .fill=c+"WPt",                .pfs={Stack,data,cut},               .cuts={},.draw=d,.opt=opt,.ranges=r_Stk4});
	sh.AddHistos(s+"W",    { .fill=c+"WEta",               .pfs={Stack,data,cut},               .cuts={},.draw=d,.opt=opt,.ranges=r_Stk4});
	sh.AddHistos(s+"W",    { .fill=c+"WPhi",               .pfs={Stack,data,cut},               .cuts={},.draw=d,.opt=opt,.ranges=r_Stk4});
	sh.AddHistos(s+"W",    { .fill=c+"WTau21",             .pfs={Stack,data,cut},               .cuts={},.draw=d,.opt=Opt,.ranges=r_Stk4});
	sh.AddHistos(s+"W",    { .fill=c+"WMass",              .pfs={Stack,data,cut},               .cuts={},.draw=d,.opt=opt,.ranges=r_Stk4});
	if (region!='S')
	  sh.AddHistos(s+"evt",  { .fill=c+"NW",                 .pfs={Stack,data,cut},               .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
	sh.SetHistoWeights({ [this,region] { return sf_weight[region]; } });
#else
	// Mass-tagged tops
	sh.AddHistos(s+"evt",  { .fill=c+"NmTop",              .pfs={Stack,data,cut},               .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
	sh.AddHistos(s+"mTop", { .fill=c+"mTopPtBins",         .pfs={Stack,data,cut},               .cuts={},.draw=d,.opt=opt,.ranges=r_Stk8});
	sh.AddHistos(s+"mTop", { .fill=c+"mTopPt",             .pfs={Stack,data,cut},               .cuts={},.draw=d,.opt=opt,.ranges=r_Stk8});
	sh.AddHistos(s+"mTop", { .fill=c+"mTopEta",            .pfs={Stack,data,cut},               .cuts={},.draw=d,.opt=opt,.ranges=r_Stk8});
	sh.AddHistos(s+"mTop", { .fill=c+"mTopPhi",            .pfs={Stack,data,cut},               .cuts={},.draw=d,.opt=opt,.ranges=r_Stk8});
	sh.AddHistos(s+"mTop", { .fill=c+"mTopTau32",          .pfs={Stack,data,cut},               .cuts={},.draw=d,.opt=Opt+"NoComb5",.ranges={0,0, 1.01e-2,1e6,  0.2,0.86}});
	sh.AddHistos(s+"mTop", { .fill=c+"mTopMass",           .pfs={Stack,data,cut},               .cuts={},.draw=d,.opt=opt,.ranges=r_Stk8});

	// Mass-tagged tops (without subjet b veto)
	sh.AddHistos(s+"evt",  { .fill=c+"NMTop",              .pfs={Stack,data,cut},               .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
	sh.AddHistos(s+"MTop", { .fill=c+"MTopPtBins",         .pfs={Stack,data,cut},               .cuts={},.draw=d,.opt=opt,.ranges=r_Stk8});
	sh.AddHistos(s+"MTop", { .fill=c+"MTopPt",             .pfs={Stack,data,cut},               .cuts={},.draw=d,.opt=opt,.ranges=r_Stk8});
	sh.AddHistos(s+"MTop", { .fill=c+"MTopEta",            .pfs={Stack,data,cut},               .cuts={},.draw=d,.opt=opt,.ranges=r_Stk8});
	sh.AddHistos(s+"MTop", { .fill=c+"MTopPhi",            .pfs={Stack,data,cut},               .cuts={},.draw=d,.opt=opt,.ranges=r_Stk8});
	sh.AddHistos(s+"MTop", { .fill=c+"MTopTau32",          .pfs={Stack,data,cut},               .cuts={},.draw=d,.opt=Opt+"NoComb5",.ranges={0,0, 1.01e-2,1e6,  0.2,0.86}});
	sh.AddHistos(s+"MTop", { .fill=c+"MTopMass",           .pfs={Stack,data,cut},               .cuts={},.draw=d,.opt=opt,.ranges=r_Stk8});

	// Anti-tagged tops
	sh.AddHistos(s+"evt",  { .fill=c+"NaTop",              .pfs={Stack,data,cut},               .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
	sh.AddHistos(s+"aTop", { .fill=c+"aTopPtBins",         .pfs={Stack,data,cut},               .cuts={},.draw=d,.opt=opt,.ranges=r_Stk8});
	sh.AddHistos(s+"aTop", { .fill=c+"aTopPt",             .pfs={Stack,data,cut},               .cuts={},.draw=d,.opt=opt,.ranges=r_Stk8});
	sh.AddHistos(s+"aTop", { .fill=c+"aTopEta",            .pfs={Stack,data,cut},               .cuts={},.draw=d,.opt=opt,.ranges=r_Stk8});
	sh.AddHistos(s+"aTop", { .fill=c+"aTopPhi",            .pfs={Stack,data,cut},               .cuts={},.draw=d,.opt=opt,.ranges=r_Stk8});
	sh.AddHistos(s+"aTop", { .fill=c+"aTopTau32",          .pfs={Stack,data,cut},               .cuts={},.draw=d,.opt=opt,.ranges=r_Stk8});
	sh.AddHistos(s+"aTop", { .fill=c+"aTopMass",           .pfs={Stack,data,cut},               .cuts={},.draw=d,.opt=opt,.ranges=r_Stk8});

	// Tagged tops
	// Add top scale factor
	if (region=='P') sh.SetHistoWeights({ [this,region] { return sf_weight[region]*scale_factors['S'][2]; } });
	if (region!='S')
	  sh.AddHistos(s+"evt",  { .fill=c+"NTop",               .pfs={Stack,data,cut},               .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
	sh.AddHistos(s+"Top",  { .fill=c+"TopPtBins",          .pfs={Stack,data,cut},               .cuts={},.draw=d,.opt=opt,.ranges=r_Stk4});
	sh.AddHistos(s+"Top",  { .fill=c+"TopPt",              .pfs={Stack,data,cut},               .cuts={},.draw=d,.opt=opt,.ranges=r_Stk4});
	sh.AddHistos(s+"Top",  { .fill=c+"TopEta",             .pfs={Stack,data,cut},               .cuts={},.draw=d,.opt=opt,.ranges=r_Stk4});
	sh.AddHistos(s+"Top",  { .fill=c+"TopPhi",             .pfs={Stack,data,cut},               .cuts={},.draw=d,.opt=opt,.ranges=r_Stk4});
	sh.AddHistos(s+"Top",  { .fill=c+"TopTau32",           .pfs={Stack,data,cut},               .cuts={},.draw=d,.opt=opt,.ranges=r_Stk4});
	sh.AddHistos(s+"Top",  { .fill=c+"TopMass",            .pfs={Stack,data,cut},               .cuts={},.draw=d,.opt=opt,.ranges=r_Stk4});
	sh.SetHistoWeights({ [this,region] { return sf_weight[region]; } });
#endif
      }
    }
  }


  // -------------------------------------------------------------------------
  //              Preselection (or Baseline) Region: P
  
  sh.SetHistoWeights({ [this] { return sf_weight['P']; } });

  for (const auto& cut : {"P"}) {
    std::string data = "JetHTMET";
    std::string opt  = o_stk_d;
    sh.AddHistos(s+"evt",  { .fill=c+"HTFine",                  .pfs={Stack,data,cut},                    .cuts={},.draw=d,.opt=opt,.ranges=r_Stk9});
    sh.AddHistos(s+"evt",  { .fill=c+"MET",                     .pfs={Stack,data,cut},                    .cuts={},.draw=d,.opt=opt,.ranges=r_Stk9});
    sh.AddHistos(s+"evt",  { .fill=c+"MR",                      .pfs={Stack,data,cut},                    .cuts={},.draw=d,.opt=opt,.ranges=r_Stk9});
    sh.AddHistos(s+"evt",  { .fill=c+"MTR",                     .pfs={Stack,data,cut},                    .cuts={},.draw=d,.opt=opt,.ranges=r_Stk9});
    sh.AddHistos(s+"evt",  { .fill=c+"R2",                      .pfs={Stack,data,cut},                    .cuts={},.draw=d,.opt=opt,.ranges=r_Stk9});
    sh.AddHistos(s+"evt",  { .fill=c+"RazorBins",               .pfs={Stack,data,cut},                    .cuts={},.draw=d,.opt=opt,.ranges=r_Stk9});
    sh.AddHistos("evt",    { .fill="MR_vs_MET",                 .pfs={"Signals_Background",cut},          .cuts={},.draw="COLZ",.opt=o_1or2d_s+"Log",.ranges={}});
    sh.AddHistos("evt",    { .fill="R2_vs_MET",                 .pfs={"Signals_Background",cut},          .cuts={},.draw="COLZ",.opt=o_1or2d_s+"Log",.ranges={}});
    sh.AddHistos("evt",    { .fill="R2_vs_MR",                  .pfs={"Signals_Background",cut},          .cuts={},.draw="COLZ",.opt=o_1or2d_s+"Log",.ranges={}});
    sh.AddHistos("evt",    { .fill="R2Fine_vs_MRFine",          .pfs={"Signals_Background",cut},          .cuts={},.draw="COLZ",.opt=o_1or2d_s+"Log",.ranges={}});
    sh.AddHistos("evt",    { .fill="MR_vs_HTFine",              .pfs={"Signals_Background",cut},          .cuts={},.draw="COLZ",.opt=o_1or2d_s+"Log",.ranges={}});
    sh.AddHistos("evt",    { .fill="MET_vs_HTFine",             .pfs={"Signals_Background",cut},          .cuts={},.draw="COLZ",.opt=o_1or2d_s+"Log",.ranges={}});
    sh.AddHistos(s+"evt",  { .fill=c+"NJet",                    .pfs={Stack,data,cut},                    .cuts={},.draw=d,.opt=opt,.ranges=r_Stk9});
    //sh.AddHistos(s+"evt",  { .fill=c+"NJetAK8",                 .pfs={Stack,data,cut},                    .cuts={},.draw=d,.opt=opt,.ranges=r_Stk9});
    sh.AddHistos(s+"evt",  { .fill=c+"HT",                      .pfs={Stack,data,cut},                    .cuts={},.draw=d,.opt=opt,.ranges=r_Stk9});
    sh.AddHistos(s+"evt",  { .fill=c+"HTJet1AK8Pt",             .pfs={Stack,data,cut},                    .cuts={},.draw=d,.opt=opt,.ranges=r_Stk9});
    for (auto njet_bin : {"NJet45"}) {
      sh.AddHistos(s+"evt",  { .fill=c+"HTFine",                  .pfs={Stack,data,cut,njet_bin},           .cuts={},.draw=d,.opt=opt,.ranges=r_Stk9});
      sh.AddHistos(s+"evt",  { .fill=c+"MET",                     .pfs={Stack,data,cut,njet_bin},           .cuts={},.draw=d,.opt=opt,.ranges=r_Stk9});
      sh.AddHistos(s+"evt",  { .fill=c+"MR",                      .pfs={Stack,data,cut,njet_bin},           .cuts={},.draw=d,.opt=opt,.ranges=r_Stk9});
      sh.AddHistos(s+"evt",  { .fill=c+"MTR",                     .pfs={Stack,data,cut,njet_bin},           .cuts={},.draw=d,.opt=opt,.ranges=r_Stk9});
      sh.AddHistos(s+"evt",  { .fill=c+"R2",                      .pfs={Stack,data,cut,njet_bin},           .cuts={},.draw=d,.opt=opt,.ranges=r_Stk9});
      sh.AddHistos(s+"evt",  { .fill=c+"RazorBins",               .pfs={Stack,data,cut,njet_bin},           .cuts={},.draw=d,.opt=opt,.ranges=r_Stk9});
      sh.AddHistos("evt",    { .fill="MR_vs_MET",                 .pfs={"Signals_Background",cut,njet_bin}, .cuts={},.draw="COLZ",.opt=o_1or2d_s+"Log",.ranges={}});
      sh.AddHistos("evt",    { .fill="R2_vs_MET",                 .pfs={"Signals_Background",cut,njet_bin}, .cuts={},.draw="COLZ",.opt=o_1or2d_s+"Log",.ranges={}});
      sh.AddHistos("evt",    { .fill="R2_vs_MR",                  .pfs={"Signals_Background",cut,njet_bin}, .cuts={},.draw="COLZ",.opt=o_1or2d_s+"Log",.ranges={}});
      sh.AddHistos("evt",    { .fill="R2Fine_vs_MRFine",          .pfs={"Signals_Background",cut,njet_bin}, .cuts={},.draw="COLZ",.opt=o_1or2d_s+"Log",.ranges={}});
      sh.AddHistos("evt",    { .fill="MR_vs_HTFine",              .pfs={"Signals_Background",cut,njet_bin}, .cuts={},.draw="COLZ",.opt=o_1or2d_s+"Log",.ranges={}});
      sh.AddHistos("evt",    { .fill="MET_vs_HTFine",             .pfs={"Signals_Background",cut,njet_bin}, .cuts={},.draw="COLZ",.opt=o_1or2d_s+"Log",.ranges={}});
      sh.AddHistos(s+"evt",  { .fill=c+"NJetAK8",                 .pfs={Stack,data,cut,njet_bin},           .cuts={},.draw=d,.opt=opt,.ranges=r_Stk9});
      sh.AddHistos(s+"evt",  { .fill=c+"HT",                      .pfs={Stack,data,cut,njet_bin},           .cuts={},.draw=d,.opt=opt,.ranges=r_Stk9});
      sh.AddHistos(s+"evt",  { .fill=c+"HTJet1AK8Pt",             .pfs={Stack,data,cut,njet_bin},           .cuts={},.draw=d,.opt=opt,.ranges=r_Stk9});
    }
  }

  // Unskimmed plots
  sh.AddHistos(s+"evt",  { .fill=c+"NJet",                    .pfs={Stack,"JetHTMET","P_ExclNJet"},              .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk9});
  sh.AddHistos(s+"evt",  { .fill=c+"HTFine",                  .pfs={Stack,"JetHTMET","P_ExclMRR2"},                 .cuts={},.draw=d,.opt=o_stk_s,.ranges=r_Stk9});
  sh.AddHistos(s+"evt",  { .fill=c+"MET",                     .pfs={Stack,"JetHTMET","P_ExclMRR2"},                 .cuts={},.draw=d,.opt=o_stk_s,.ranges=r_Stk9});
  sh.AddHistos(s+"evt",  { .fill=c+"MR",                      .pfs={Stack,"JetHTMET","P_ExclMR"},                   .cuts={},.draw=d,.opt=o_stk_s,.ranges=r_Stk9});
  sh.AddHistos(s+"evt",  { .fill=c+"MTR",                     .pfs={Stack,"JetHTMET","P_ExclR2"},                   .cuts={},.draw=d,.opt=o_stk_s,.ranges=r_Stk9});
  sh.AddHistos(s+"evt",  { .fill=c+"R2",                      .pfs={Stack,"JetHTMET","P_ExclR2"},                   .cuts={},.draw=d,.opt=o_stk_s,.ranges=r_Stk9});
  sh.AddHistos("evt",    { .fill="MR_vs_MET",                 .pfs={"Signals_Background","P_ExclMRR2"},          .cuts={},.draw="COLZ",.opt=o_1or2d_s+"Log",.ranges={}});
  sh.AddHistos("evt",    { .fill="R2_vs_MET",                 .pfs={"Signals_Background","P_ExclMRR2"},          .cuts={},.draw="COLZ",.opt=o_1or2d_s+"Log",.ranges={}});
  sh.AddHistos("evt",    { .fill="R2_vs_MR",                  .pfs={"Signals_Background","P_ExclMRR2"},          .cuts={},.draw="COLZ",.opt=o_1or2d_s+"Log",.ranges={}});
  sh.AddHistos("evt",    { .fill="MR_vs_HTFine",              .pfs={"Signals_Background","P_ExclMRR2"},          .cuts={},.draw="COLZ",.opt=o_1or2d_s+"Log",.ranges={}});
  sh.AddHistos("evt",    { .fill="MET_vs_HTFine",             .pfs={"Signals_Background","P_ExclMRR2"},          .cuts={},.draw="COLZ",.opt=o_1or2d_s+"Log",.ranges={}});
  sh.AddHistos("evt",    { .fill="R2Fine_vs_MRFine",          .pfs={"Signals_Background","P_ExclMRR2"},          .cuts={},.draw="COLZ",.opt=o_1or2d_s+"Log",.ranges={}});

  sh.AddHistos(s+"evt",  { .fill=c+"MinDeltaPhi",               .pfs={Stack,"JetHTMET","P"},           .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk9});
  sh.AddHistos(s+"evt",  { .fill=c+"DeltaPhi",                  .pfs={Stack,"JetHTMET","P"},           .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk9});
  
  // Lost lepton plots
  //sh.AddHistos("gen lep", { .fill="LostLeptonRate_vs_GenLepPtBins",  .pfs={"FullFastSim"},                                     .cuts={},.draw=d,.opt=o_1or2d_s+"AddRatiologX", .ranges={0,0, 0,0}});
  //sh.AddHistos("gen lep", { .fill="LostLeptonRate_vs_GenLepPtBins",  .pfs={"FullFastSim","LostLeptonFlavour"},                 .cuts={},.draw=d,.opt=o_1or2d_s+"AddRatiologX", .ranges={0,0, 0,0}});
  //sh.AddHistos("gen lep", { .fill="LostLeptonRate_vs_GenLepEta", .pfs={"FullFastSim"},                                     .cuts={},.draw=d,.opt=o_1or2d_s+"AddRatio", .ranges={0,0, 0,0}});
  //sh.AddHistos("gen lep", { .fill="LostLeptonRate_vs_GenLepEta", .pfs={"FullFastSim","LostLeptonFlavour"},                 .cuts={},.draw=d,.opt=o_1or2d_s+"AddRatio", .ranges={0,0, 0,0}});
  //sh.AddHistos("gen lep", { .fill="LostLeptonRate_vs_GenLepPtBins",  .pfs={"FullFastSim","P"},                                 .cuts={},.draw=d,.opt=o_1or2d_s+"AddRatiologX", .ranges={0,0, 0,0}});
  //sh.AddHistos("gen lep", { .fill="LostLeptonRate_vs_GenLepPtBins",  .pfs={"FullFastSim","P","LostLeptonFlavour"},             .cuts={},.draw=d,.opt=o_1or2d_s+"AddRatiologX", .ranges={0,0, 0,0}});
  //sh.AddHistos("gen lep", { .fill="LostLeptonRate_vs_GenLepEta", .pfs={"FullFastSim","P"},                                 .cuts={},.draw=d,.opt=o_1or2d_s+"AddRatio", .ranges={0,0, 0,0}});
  //sh.AddHistos("gen lep", { .fill="LostLeptonRate_vs_GenLepEta", .pfs={"FullFastSim","P","LostLeptonFlavour"},             .cuts={},.draw=d,.opt=o_1or2d_s+"AddRatio", .ranges={0,0, 0,0}});
  //sh.AddHistos("gen lep", { .fill="LostLeptonRate_vs_GenLepEta_vs_GenLepPtBins", .pfs={"FullFastSim"},                         .cuts={},.draw="COLZ",.opt=o_1or2d_s+"logX", .ranges={0,0, 0,0, 0,0}});
  //sh.AddHistos("gen lep", { .fill="LostLeptonRate_vs_GenLepEta_vs_GenLepPtBins", .pfs={"FullFastSim","LostLeptonFlavour"},     .cuts={},.draw="COLZ",.opt=o_1or2d_s+"logX", .ranges={0,0, 0,0, 0,0}});
  //sh.AddHistos("gen lep", { .fill="LostLeptonRate_vs_GenLepEta_vs_GenLepPtBins", .pfs={"FullFastSim","P"},                     .cuts={},.draw="COLZ",.opt=o_1or2d_s+"logX", .ranges={0,0, 0,0, 0,0}});
  //sh.AddHistos("gen lep", { .fill="LostLeptonRate_vs_GenLepEta_vs_GenLepPtBins", .pfs={"FullFastSim","P","LostLeptonFlavour"}, .cuts={},.draw="COLZ",.opt=o_1or2d_s+"logX", .ranges={0,0, 0,0, 0,0}});

  // Lepton Efficiencies
  sh.AddHistos("gen lep", { .fill="LepTightNoIsoEfficiency_vs_GenLepPtBins",  .pfs={"Signals_Background","P","GenLepMother","GenLeptonFlavour"}, .cuts={},.draw="HIST",.opt=o_1or2d_s, .ranges={0,0, 0,1}});
  sh.AddHistos("gen lep", { .fill="LepTightNoIsoEfficiency_vs_GenLepPtBins",  .pfs={"GenLeptonFlavour","Signals_Background","P","GenLepMother"}, .cuts={},.draw="HIST",.opt=o_1or2d_s, .ranges={0,0, 0,1}});
  sh.AddHistos("gen lep", { .fill="LepTight2DEfficiency_vs_GenLepPtBins",     .pfs={"Signals_Background","P","GenLepMother","GenLeptonFlavour"}, .cuts={},.draw="HIST",.opt=o_1or2d_s, .ranges={0,0, 0,1}});
  sh.AddHistos("gen lep", { .fill="LepTight2DEfficiency_vs_GenLepPtBins",     .pfs={"GenLeptonFlavour","Signals_Background","P","GenLepMother"}, .cuts={},.draw="HIST",.opt=o_1or2d_s, .ranges={0,0, 0,1}});
  
  for (auto njet_bin : {"NJet45"}) {
    sh.AddHistos(s+"evt",  { .fill=c+"HTFine",                  .pfs={Stack,"JetHTMET","P_ExclMRR2",njet_bin},        .cuts={},.draw=d,.opt=o_stk_s,.ranges=r_Stk9});
    sh.AddHistos(s+"evt",  { .fill=c+"MET",                     .pfs={Stack,"JetHTMET","P_ExclMRR2",njet_bin},        .cuts={},.draw=d,.opt=o_stk_s,.ranges=r_Stk9});
    sh.AddHistos(s+"evt",  { .fill=c+"MR",                      .pfs={Stack,"JetHTMET","P_ExclMR",njet_bin},          .cuts={},.draw=d,.opt=o_stk_s,.ranges=r_Stk9});
    sh.AddHistos(s+"evt",  { .fill=c+"MTR",                     .pfs={Stack,"JetHTMET","P_ExclR2",njet_bin},          .cuts={},.draw=d,.opt=o_stk_s,.ranges=r_Stk9});
    sh.AddHistos(s+"evt",  { .fill=c+"R2",                      .pfs={Stack,"JetHTMET","P_ExclR2",njet_bin},          .cuts={},.draw=d,.opt=o_stk_s,.ranges=r_Stk9});
    sh.AddHistos("evt",    { .fill="MR_vs_MET",                 .pfs={"Signals_Background","P_ExclMRR2",njet_bin}, .cuts={},.draw="COLZ",.opt=o_1or2d_s+"Log",.ranges={}});
    sh.AddHistos("evt",    { .fill="R2_vs_MET",                 .pfs={"Signals_Background","P_ExclMRR2",njet_bin}, .cuts={},.draw="COLZ",.opt=o_1or2d_s+"Log",.ranges={}});
    sh.AddHistos("evt",    { .fill="R2_vs_MR",                  .pfs={"Signals_Background","P_ExclMRR2",njet_bin}, .cuts={},.draw="COLZ",.opt=o_1or2d_s+"Log",.ranges={}});
    sh.AddHistos("evt",    { .fill="MR_vs_HTFine",              .pfs={"Signals_Background","P_ExclMRR2",njet_bin}, .cuts={},.draw="COLZ",.opt=o_1or2d_s+"Log",.ranges={}});
    sh.AddHistos("evt",    { .fill="MET_vs_HTFine",             .pfs={"Signals_Background","P_ExclMRR2",njet_bin}, .cuts={},.draw="COLZ",.opt=o_1or2d_s+"Log",.ranges={}});
    sh.AddHistos("evt",    { .fill="R2Fine_vs_MRFine",          .pfs={"Signals_Background","P_ExclMRR2",njet_bin}, .cuts={},.draw="COLZ",.opt=o_1or2d_s+"Log",.ranges={}});
    sh.AddHistos(s+"evt",  { .fill=c+"NBTag",       .pfs={Stack,"JetHTMET","P",njet_bin},  .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
    sh.AddHistos(s+"evt",  { .fill=c+"MinDeltaPhi", .pfs={Stack,"JetHTMET","P",njet_bin},  .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk9});
    sh.AddHistos(s+"evt",  { .fill=c+"DeltaPhi",    .pfs={Stack,"JetHTMET","P",njet_bin},  .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk9});
  }
  //// FastSim/FullSim Scale Factors (no cuts, no other scale factors)
  //sh.AddHistos(s+"W",    { .fill=c+"WPtBins",                 .pfs={"FullFastSim","MatchGenW"},                 .cuts={},.draw="PE1",.opt=o_1or2d_s+"Log",.ranges={200,2000, 1.01e-1,1e6, 0.5,0.85}});
  //sh.AddHistos(s+"W",    { .fill=c+"WPtBins",                 .pfs={"FullFastSim","MatchGenW","AK8_EB_EE"},     .cuts={},.draw="PE1",.opt=o_1or2d_s+"Log",.ranges={200,2000, 1.01e-1,1e6, 0.5,0.85}});
  //sh.AddHistos(s+"Top",  { .fill=c+"TopPtBins",               .pfs={"FullFastSim","MatchGenTop"},               .cuts={},.draw="PE1",.opt=o_1or2d_s+"Log",.ranges={400,2000, 1.01e-1,1e6, 0.5,0.85}});
  //sh.AddHistos(s+"Top",  { .fill=c+"TopPtBins",               .pfs={"FullFastSim","MatchGenTop","AK8_EB_EE"},   .cuts={},.draw="PE1",.opt=o_1or2d_s+"Log",.ranges={400,2000, 1.01e-1,1e6, 0.5,0.85}});
  //// Tag/Mistag ratio in ttbar
  //sh.AddHistos(s+"W",    { .fill=c+"WPtBins",                 .pfs={"MatchGenW","FullFastSim"},                 .cuts={},.draw="PE1",.opt=o_1or2d_s+"Log",.ranges={200,2000, 1.01e-1,1e6, 0.5,0.85}});
  //sh.AddHistos(s+"W",    { .fill=c+"WPtBins",                 .pfs={"MatchGenW","FullFastSim","AK8_EB_EE"},     .cuts={},.draw="PE1",.opt=o_1or2d_s+"Log",.ranges={200,2000, 1.01e-1,1e6, 0.5,0.85}});
  //sh.AddHistos(s+"Top",  { .fill=c+"TopPtBins",               .pfs={"MatchGenTop","FullFastSim"},               .cuts={},.draw="PE1",.opt=o_1or2d_s+"Log",.ranges={400,2000, 1.01e-1,1e6, 0.5,0.85}});
  //sh.AddHistos(s+"Top",  { .fill=c+"TopPtBins",               .pfs={"MatchGenTop","FullFastSim","AK8_EB_EE"},   .cuts={},.draw="PE1",.opt=o_1or2d_s+"Log",.ranges={400,2000, 1.01e-1,1e6, 0.5,0.85}});
  
//TEMP    // -------------------------------------------------------------------------
//TEMP    //                           Signal Region: S and S'
//TEMP    
//TEMP    sh.SetHistoWeights({ [this] { return sf_weight['S']; } });
//TEMP  
//TEMP    for (const auto& cut : {"S", "s"}) {
//TEMP      std::vector<std::string> showdata = {"JetHTMET"};
//TEMP      if (std::string(cut)=="S") showdata.push_back("Blind");
//TEMP      for (auto data : showdata ) {
//TEMP        std::string opt  = (data=="Blind") ? o_stk_s_S : o_stk_d_S;
//TEMP        std::string Opt  = (data=="Blind") ? O_stk_s_S : O_stk_d_S;
//TEMP        sh.AddHistos("evt",    { .fill="MRFine_vs_METFine",         .pfs={"Signals_Background",cut},          .cuts={},.draw="COLZ",.opt=o_1or2d_s+"Log",.ranges={}});
//TEMP        sh.AddHistos("evt",    { .fill="R2Fine_vs_METFine",         .pfs={"Signals_Background",cut},          .cuts={},.draw="COLZ",.opt=o_1or2d_s+"Log",.ranges={}});
//TEMP        sh.AddHistos("evt",    { .fill="R2Fine_vs_MRFine",          .pfs={"Signals_Background",cut},          .cuts={},.draw="COLZ",.opt=o_1or2d_s+"Log",.ranges={}});
//TEMP        sh.AddHistos("evt",    { .fill="MRFine_vs_HTFine",          .pfs={"Signals_Background",cut},          .cuts={},.draw="COLZ",.opt=o_1or2d_s+"Log",.ranges={}});
//TEMP        sh.AddHistos("evt",    { .fill="METFine_vs_HTFine",         .pfs={"Signals_Background",cut},          .cuts={},.draw="COLZ",.opt=o_1or2d_s+"Log",.ranges={}});
//TEMP        sh.AddHistos("evt",    { .fill="R2Fine_vs_MRFine",          .pfs={"Signals_Background",cut},          .cuts={},.draw="COLZ",.opt=o_1or2d_s+"Log",.ranges={}});
//TEMP        // MGlunio/MStop plots
//TEMP        sh.AddHistos("evt",  { .fill="HTFine",                      .pfs={"MGluinoPoints",  "MLSPPoints","GluinoSignalScans",  cut}, .cuts={},.draw=d,.opt=o_norm_s,.ranges={}});
//TEMP        sh.AddHistos("evt",  { .fill="METFine",                     .pfs={"MGluinoPoints",  "MLSPPoints","GluinoSignalScans",  cut}, .cuts={},.draw=d,.opt=o_norm_s,.ranges={}});
//TEMP        sh.AddHistos("evt",  { .fill="R2Fine",                      .pfs={"MGluinoPoints",  "MLSPPoints","GluinoSignalScans",  cut}, .cuts={},.draw=d,.opt=o_norm_s,.ranges={}});
//TEMP        sh.AddHistos("evt",  { .fill="MRFine",                      .pfs={"MGluinoPoints",  "MLSPPoints","GluinoSignalScans",  cut}, .cuts={},.draw=d,.opt=o_norm_s,.ranges={}});
//TEMP        sh.AddHistos("evt",  { .fill="RazorBins",                   .pfs={"MGluinoPoints",  "MLSPPoints","GluinoSignalScans",  cut}, .cuts={},.draw=d,.opt=o_norm_s,.ranges={}});
//TEMP        sh.AddHistos("evt",  { .fill="MRR2",                        .pfs={"MGluinoPoints",  "MLSPPoints","GluinoSignalScans",  cut}, .cuts={},.draw=d,.opt=o_norm_s,.ranges={}});
//TEMP        sh.AddHistos("evt",  { .fill="HTFine",                      .pfs={"MStopPoints",    "MLSPPoints","StopSignalScans",    cut}, .cuts={},.draw=d,.opt=o_norm_s,.ranges={}});
//TEMP        sh.AddHistos("evt",  { .fill="METFine",                     .pfs={"MStopPoints",    "MLSPPoints","StopSignalScans",    cut}, .cuts={},.draw=d,.opt=o_norm_s,.ranges={}});
//TEMP        sh.AddHistos("evt",  { .fill="R2Fine",                      .pfs={"MStopPoints",    "MLSPPoints","StopSignalScans",    cut}, .cuts={},.draw=d,.opt=o_norm_s,.ranges={}});
//TEMP        sh.AddHistos("evt",  { .fill="MRFine",                      .pfs={"MStopPoints",    "MLSPPoints","StopSignalScans",    cut}, .cuts={},.draw=d,.opt=o_norm_s,.ranges={}});
//TEMP        sh.AddHistos("evt",  { .fill="RazorBins",                   .pfs={"MStopPoints",    "MLSPPoints","StopSignalScans",    cut}, .cuts={},.draw=d,.opt=o_norm_s,.ranges={}});
//TEMP        sh.AddHistos("evt",  { .fill="MRR2",                        .pfs={"MStopPoints",    "MLSPPoints","StopSignalScans",    cut}, .cuts={},.draw=d,.opt=o_norm_s,.ranges={}});
//TEMP        sh.AddHistos("evt",  { .fill="MRR2",                        .pfs={"MCharginoPoints","MLSPPoints","CharginoSignalScans",cut}, .cuts={},.draw=d,.opt=o_norm_s,.ranges={}});
//TEMP        sh.AddHistos("evt",  { .fill="HTFine",                      .pfs={"MCharginoPoints","MLSPPoints","CharginoSignalScans",cut}, .cuts={},.draw=d,.opt=o_norm_s,.ranges={}});
//TEMP        sh.AddHistos("evt",  { .fill="METFine",                     .pfs={"MCharginoPoints","MLSPPoints","CharginoSignalScans",cut}, .cuts={},.draw=d,.opt=o_norm_s,.ranges={}});
//TEMP        sh.AddHistos("evt",  { .fill="R2Fine",                      .pfs={"MCharginoPoints","MLSPPoints","CharginoSignalScans",cut}, .cuts={},.draw=d,.opt=o_norm_s,.ranges={}});
//TEMP        sh.AddHistos("evt",  { .fill="MRFine",                      .pfs={"MCharginoPoints","MLSPPoints","CharginoSignalScans",cut}, .cuts={},.draw=d,.opt=o_norm_s,.ranges={}});
//TEMP        sh.AddHistos("evt",  { .fill="RazorBins",                   .pfs={"MCharginoPoints","MLSPPoints","CharginoSignalScans",cut}, .cuts={},.draw=d,.opt=o_norm_s,.ranges={}});
//TEMP        sh.AddHistos(s+"evt",  { .fill=c+"HTFine",                  .pfs={"StackPlotSignal",data,cut},                    .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
//TEMP        sh.AddHistos(s+"evt",  { .fill=c+"MET",                     .pfs={"StackPlotSignal",data,cut},                    .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
//TEMP        sh.AddHistos(s+"evt",  { .fill=c+"MR",                      .pfs={"StackPlotSignal",data,cut},                    .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
//TEMP        sh.AddHistos(s+"evt",  { .fill=c+"MTR",                     .pfs={"StackPlotSignal",data,cut},                    .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
//TEMP        sh.AddHistos(s+"evt",  { .fill=c+"R2",                      .pfs={"StackPlotSignal",data,cut},                    .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
//TEMP        sh.AddHistos(s+"evt",  { .fill=c+"RazorBins",               .pfs={"StackPlotSignal",data,cut},                    .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
//TEMP        sh.AddHistos("evt",    { .fill="MR_vs_MET",                 .pfs={"Signals_Background",cut},          .cuts={},.draw="COLZ",.opt=o_1or2d_s+"Log",.ranges={}});
//TEMP        sh.AddHistos("evt",    { .fill="R2_vs_MET",                 .pfs={"Signals_Background",cut},          .cuts={},.draw="COLZ",.opt=o_1or2d_s+"Log",.ranges={}});
//TEMP        sh.AddHistos("evt",    { .fill="R2_vs_MR",                  .pfs={"Signals_Background",cut},          .cuts={},.draw="COLZ",.opt=o_1or2d_s+"Log",.ranges={}});
//TEMP        sh.AddHistos("evt",    { .fill="MR_vs_HTFine",              .pfs={"Signals_Background",cut},          .cuts={},.draw="COLZ",.opt=o_1or2d_s+"Log",.ranges={}});
//TEMP        sh.AddHistos("evt",    { .fill="MET_vs_HTFine",             .pfs={"Signals_Background",cut},          .cuts={},.draw="COLZ",.opt=o_1or2d_s+"Log",.ranges={}});
//TEMP        sh.AddHistos("evt",    { .fill="R2Fine_vs_MRFine",          .pfs={"Signals_Background",cut},          .cuts={},.draw="COLZ",.opt=o_1or2d_s+"Log",.ranges={}});
//TEMP        sh.AddHistos(s+"evt",  { .fill=c+"NJet",                    .pfs={"StackPlotSignal",data,cut},                    .cuts={},.draw=d,.opt=Opt,.ranges=r_Stk5});
//TEMP        if (std::string(cut) != "S" && std::string(cut) != "s")
//TEMP          sh.AddHistos(s+"evt",  { .fill=c+"NJetAK8",                 .pfs={"StackPlotSignal",data,cut},                    .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
//TEMP        sh.AddHistos(s+"evt",  { .fill=c+"HT",                      .pfs={"StackPlotSignal",data,cut},                    .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
//TEMP        sh.AddHistos(s+"evt",  { .fill=c+"HTJet1AK8Pt",             .pfs={"StackPlotSignal",data,cut},                    .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
//TEMP        // MGlunio/MStop plots
//TEMP        for (auto njet_bin : {"NJet45"}) {
//TEMP          sh.AddHistos(s+"evt",  { .fill=c+"HTFine",                  .pfs={"StackPlotSignal",data,cut,njet_bin},           .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
//TEMP          sh.AddHistos(s+"evt",  { .fill=c+"MET",                     .pfs={"StackPlotSignal",data,cut,njet_bin},           .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
//TEMP          sh.AddHistos(s+"evt",  { .fill=c+"MR",                      .pfs={"StackPlotSignal",data,cut,njet_bin},           .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
//TEMP          sh.AddHistos(s+"evt",  { .fill=c+"MTR",                     .pfs={"StackPlotSignal",data,cut,njet_bin},           .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
//TEMP          sh.AddHistos(s+"evt",  { .fill=c+"R2",                      .pfs={"StackPlotSignal",data,cut,njet_bin},           .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
//TEMP          sh.AddHistos(s+"evt",  { .fill=c+"RazorBins",               .pfs={"StackPlotSignal",data,cut,njet_bin},           .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
//TEMP          sh.AddHistos("evt",    { .fill="MR_vs_MET",                 .pfs={"Signals_Background",cut,njet_bin}, .cuts={},.draw="COLZ",.opt=o_1or2d_s+"Log",.ranges={}});
//TEMP          sh.AddHistos("evt",    { .fill="R2_vs_MET",                 .pfs={"Signals_Background",cut,njet_bin}, .cuts={},.draw="COLZ",.opt=o_1or2d_s+"Log",.ranges={}});
//TEMP          sh.AddHistos("evt",    { .fill="R2_vs_MR",                  .pfs={"Signals_Background",cut,njet_bin}, .cuts={},.draw="COLZ",.opt=o_1or2d_s+"Log",.ranges={}});
//TEMP          sh.AddHistos("evt",    { .fill="MR_vs_HTFine",              .pfs={"Signals_Background",cut,njet_bin}, .cuts={},.draw="COLZ",.opt=o_1or2d_s+"Log",.ranges={}});
//TEMP          sh.AddHistos("evt",    { .fill="MET_vs_HTFine",             .pfs={"Signals_Background",cut,njet_bin}, .cuts={},.draw="COLZ",.opt=o_1or2d_s+"Log",.ranges={}});
//TEMP          sh.AddHistos("evt",    { .fill="R2Fine_vs_MRFine",          .pfs={"Signals_Background",cut,njet_bin}, .cuts={},.draw="COLZ",.opt=o_1or2d_s+"Log",.ranges={}});
//TEMP          sh.AddHistos(s+"evt",  { .fill=c+"NJetAK8",                 .pfs={"StackPlotSignal",data,cut,njet_bin},           .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
//TEMP          sh.AddHistos(s+"evt",  { .fill=c+"HT",                      .pfs={"StackPlotSignal",data,cut,njet_bin},           .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
//TEMP  	sh.AddHistos(s+"evt",  { .fill=c+"HTJet1AK8Pt",             .pfs={"StackPlotSignal",data,cut,njet_bin},           .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
//TEMP        }
//TEMP      }
//TEMP    }
//TEMP  
//TEMP  
//TEMP    std::string o_d = "LogSumw2Stack0AddIntApproval15";
//TEMP    std::string o_s = "LogSumw2Stack0AddIntApproval45";
//TEMP    sh.AddHistos(s+"evt",  { .fill=c+"VetoLepPt",               .pfs={Stack,"JetHTMET","S_1VetoLep"},                 .cuts={},.draw=d,.opt=o_stk_d+"logX",.ranges=r_Stk8});
//TEMP    sh.AddHistos(s+"evt",  { .fill=c+"VetoLepPt",               .pfs={Stack,"JetHTMET","LeptonFlavour"},              .cuts={},.draw=d,.opt=o_stk_d+"logX",.ranges=r_Stk8});
//TEMP    sh.AddHistos(s+"evt",  { .fill=c+"VetoLepEta",              .pfs={Stack,"JetHTMET","S_1VetoLep"},                 .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk8});
//TEMP    sh.AddHistos(s+"evt",  { .fill=c+"VetoLepEta",              .pfs={Stack,"JetHTMET","LeptonFlavour"},              .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk8});
//TEMP    sh.AddHistos("evt",    { .fill="VetoLepPt",                 .pfs={"LeptonFlavour","JetHTMET","Data"},             .cuts={},.draw=d,.opt=o_d+"logX", .ranges=r_Stk8});
//TEMP    sh.AddHistos("evt",    { .fill="VetoLepPt",                 .pfs={"LeptonFlavour","JetHTMET","Background"},       .cuts={},.draw=d,.opt=o_s+"logX", .ranges=r_Stk8});
//TEMP    sh.AddHistos("evt",    { .fill="VetoLepEta",                .pfs={"LeptonFlavour","JetHTMET","Data"},             .cuts={},.draw=d,.opt=o_d, .ranges=r_Stk8});
//TEMP    sh.AddHistos("evt",    { .fill="VetoLepEta",                .pfs={"LeptonFlavour","JetHTMET","Background"},       .cuts={},.draw=d,.opt=o_s, .ranges=r_Stk8});
//TEMP  
//TEMP    // Plots with looser W/Top tag WPs
//TEMP  #if TOP == 0
//TEMP    sh.AddHistos(s+"evt",  { .fill=c+"RazorBins",               .pfs={Stack,"Blind","S_Excl1W","WWP1"},             .cuts={},.draw=d,.opt=o_stk_s,.ranges=r_Stk6});
//TEMP    sh.AddHistos(s+"evt",  { .fill=c+"RazorBins",               .pfs={Stack,"Blind","S_Excl1W","WWP3"},             .cuts={},.draw=d,.opt=o_stk_s,.ranges=r_Stk6});
//TEMP    sh.AddHistos(s+"evt",  { .fill=c+"RazorBins",               .pfs={Stack,"Blind","S_Excl1W","WWP4"},             .cuts={},.draw=d,.opt=o_stk_s,.ranges=r_Stk6});
//TEMP    sh.AddHistos(s+"evt",  { .fill=c+"RazorBins",               .pfs={Stack,"Blind","S_Excl1W","WWP1","NJet45"},    .cuts={},.draw=d,.opt=o_stk_s,.ranges=r_Stk6});
//TEMP    sh.AddHistos(s+"evt",  { .fill=c+"RazorBins",               .pfs={Stack,"Blind","S_Excl1W","WWP3","NJet45"},    .cuts={},.draw=d,.opt=o_stk_s,.ranges=r_Stk6});
//TEMP    sh.AddHistos(s+"evt",  { .fill=c+"RazorBins",               .pfs={Stack,"Blind","S_Excl1W","WWP4","NJet45"},    .cuts={},.draw=d,.opt=o_stk_s,.ranges=r_Stk6});
//TEMP    sh.AddHistos(s+"evt",  { .fill=c+"RazorBins",               .pfs={Stack,"Blind","s_Excl1W","WWP1"},             .cuts={},.draw=d,.opt=o_stk_s,.ranges=r_Stk6});
//TEMP    sh.AddHistos(s+"evt",  { .fill=c+"RazorBins",               .pfs={Stack,"Blind","s_Excl1W","WWP3"},             .cuts={},.draw=d,.opt=o_stk_s,.ranges=r_Stk6});
//TEMP    sh.AddHistos(s+"evt",  { .fill=c+"RazorBins",               .pfs={Stack,"Blind","s_Excl1W","WWP4"},             .cuts={},.draw=d,.opt=o_stk_s,.ranges=r_Stk6});
//TEMP    sh.AddHistos(s+"evt",  { .fill=c+"RazorBins",               .pfs={Stack,"Blind","s_Excl1W","WWP1","NJet45"},    .cuts={},.draw=d,.opt=o_stk_s,.ranges=r_Stk6});
//TEMP    sh.AddHistos(s+"evt",  { .fill=c+"RazorBins",               .pfs={Stack,"Blind","s_Excl1W","WWP3","NJet45"},    .cuts={},.draw=d,.opt=o_stk_s,.ranges=r_Stk6});
//TEMP    sh.AddHistos(s+"evt",  { .fill=c+"RazorBins",               .pfs={Stack,"Blind","s_Excl1W","WWP4","NJet45"},    .cuts={},.draw=d,.opt=o_stk_s,.ranges=r_Stk6});
//TEMP  #else
//TEMP    sh.AddHistos(s+"evt",  { .fill=c+"RazorBins",               .pfs={Stack,"Blind","S_Excl1Top","TopWP2"},         .cuts={},.draw=d,.opt=o_stk_s,.ranges=r_Stk6});
//TEMP    sh.AddHistos(s+"evt",  { .fill=c+"RazorBins",               .pfs={Stack,"Blind","S_Excl1Top","TopWP3"},         .cuts={},.draw=d,.opt=o_stk_s,.ranges=r_Stk6});
//TEMP    sh.AddHistos(s+"evt",  { .fill=c+"RazorBins",               .pfs={Stack,"Blind","S_Excl1Top","TopWP4"},         .cuts={},.draw=d,.opt=o_stk_s,.ranges=r_Stk6});
//TEMP    sh.AddHistos(s+"evt",  { .fill=c+"RazorBins",               .pfs={Stack,"Blind","S_Excl1Top","TopWP5"},         .cuts={},.draw=d,.opt=o_stk_s,.ranges=r_Stk6});
//TEMP    sh.AddHistos(s+"evt",  { .fill=c+"RazorBins",               .pfs={Stack,"Blind","s_Excl1Top","TopWP2"},         .cuts={},.draw=d,.opt=o_stk_s,.ranges=r_Stk6});
//TEMP    sh.AddHistos(s+"evt",  { .fill=c+"RazorBins",               .pfs={Stack,"Blind","s_Excl1Top","TopWP3"},         .cuts={},.draw=d,.opt=o_stk_s,.ranges=r_Stk6});
//TEMP    sh.AddHistos(s+"evt",  { .fill=c+"RazorBins",               .pfs={Stack,"Blind","s_Excl1Top","TopWP4"},         .cuts={},.draw=d,.opt=o_stk_s,.ranges=r_Stk6});
//TEMP    sh.AddHistos(s+"evt",  { .fill=c+"RazorBins",               .pfs={Stack,"Blind","s_Excl1Top","TopWP5"},         .cuts={},.draw=d,.opt=o_stk_s,.ranges=r_Stk6});
//TEMP  #endif
//TEMP  
//TEMP    // Unskimmed plots
//TEMP    sh.AddHistos(s+"evt",  { .fill=c+"HTFine",                  .pfs={"StackPlotSignal","Blind","S_ExclMRR2"},                 .cuts={},.draw=d,.opt=o_stk_s_S,.ranges=r_Stk6});
//TEMP    sh.AddHistos(s+"evt",  { .fill=c+"MET",                     .pfs={"StackPlotSignal","Blind","S_ExclMRR2"},                 .cuts={},.draw=d,.opt=o_stk_s_S,.ranges=r_Stk6});
//TEMP    sh.AddHistos(s+"evt",  { .fill=c+"MR",                      .pfs={"StackPlotSignal","Blind","S_ExclMR"},                   .cuts={},.draw=d,.opt=o_stk_s_S,.ranges=r_Stk6});
//TEMP    sh.AddHistos(s+"evt",  { .fill=c+"MTR",                     .pfs={"StackPlotSignal","Blind","S_ExclR2"},                   .cuts={},.draw=d,.opt=o_stk_s_S,.ranges=r_Stk6});
//TEMP    sh.AddHistos(s+"evt",  { .fill=c+"R2",                      .pfs={"StackPlotSignal","Blind","S_ExclR2"},                   .cuts={},.draw=d,.opt=o_stk_s_S,.ranges=r_Stk6});
//TEMP    sh.AddHistos(s+"evt",  { .fill=c+"HTFine",                  .pfs={"StackPlotSignal","JetHTMET","S_ExclMRR2"},                 .cuts={},.draw=d,.opt=o_stk_s_S,.ranges=r_Stk6});
//TEMP    sh.AddHistos(s+"evt",  { .fill=c+"MET",                     .pfs={"StackPlotSignal","JetHTMET","S_ExclMRR2"},                 .cuts={},.draw=d,.opt=o_stk_s_S,.ranges=r_Stk6});
//TEMP    sh.AddHistos(s+"evt",  { .fill=c+"MR",                      .pfs={"StackPlotSignal","JetHTMET","S_ExclMR"},                   .cuts={},.draw=d,.opt=o_stk_s_S,.ranges=r_Stk6});
//TEMP    sh.AddHistos(s+"evt",  { .fill=c+"MTR",                     .pfs={"StackPlotSignal","JetHTMET","S_ExclR2"},                   .cuts={},.draw=d,.opt=o_stk_s_S,.ranges=r_Stk6});
//TEMP    sh.AddHistos(s+"evt",  { .fill=c+"R2",                      .pfs={"StackPlotSignal","JetHTMET","S_ExclR2"},                   .cuts={},.draw=d,.opt=o_stk_s_S,.ranges=r_Stk6});
//TEMP    sh.AddHistos("evt",    { .fill="MR_vs_MET",                 .pfs={"Signals_Background","S_ExclMRR2"},            .cuts={},.draw="COLZ",.opt=o_1or2d_s+"Log",.ranges={}});
//TEMP    sh.AddHistos("evt",    { .fill="R2_vs_MET",                 .pfs={"Signals_Background","S_ExclMRR2"},            .cuts={},.draw="COLZ",.opt=o_1or2d_s+"Log",.ranges={}});
//TEMP    sh.AddHistos("evt",    { .fill="R2_vs_MR",                  .pfs={"Signals_Background","S_ExclMRR2"},          .cuts={},.draw="COLZ",.opt=o_1or2d_s+"Log",.ranges={}});
//TEMP    sh.AddHistos("evt",    { .fill="MR_vs_HTFine",              .pfs={"Signals_Background","S_ExclMRR2"},            .cuts={},.draw="COLZ",.opt=o_1or2d_s+"Log",.ranges={}});
//TEMP    sh.AddHistos("evt",    { .fill="MET_vs_HTFine",             .pfs={"Signals_Background","S_ExclMRR2"},            .cuts={},.draw="COLZ",.opt=o_1or2d_s+"Log",.ranges={}});
//TEMP    sh.AddHistos("evt",    { .fill="R2Fine_vs_MRFine",          .pfs={"Signals_Background","S_ExclMRR2"},          .cuts={},.draw="COLZ",.opt=o_1or2d_s+"Log",.ranges={}});
//TEMP    for (auto njet_bin : {"NJet45"}) {
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"HTFine",                  .pfs={"StackPlotSignal","Blind","S_ExclMRR2",njet_bin},        .cuts={},.draw=d,.opt=o_stk_s_S,.ranges=r_Stk6});
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"MET",                     .pfs={"StackPlotSignal","Blind","S_ExclMRR2",njet_bin},        .cuts={},.draw=d,.opt=o_stk_s_S,.ranges=r_Stk6});
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"MR",                      .pfs={"StackPlotSignal","Blind","S_ExclMR",njet_bin},          .cuts={},.draw=d,.opt=o_stk_s_S,.ranges=r_Stk6});
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"MTR",                     .pfs={"StackPlotSignal","Blind","S_ExclR2",njet_bin},          .cuts={},.draw=d,.opt=o_stk_s_S,.ranges=r_Stk6});
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"R2",                      .pfs={"StackPlotSignal","Blind","S_ExclR2",njet_bin},          .cuts={},.draw=d,.opt=o_stk_s_S,.ranges=r_Stk6});
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"HTFine",                  .pfs={"StackPlotSignal","JetHTMET","S_ExclMRR2",njet_bin},        .cuts={},.draw=d,.opt=o_stk_s_S,.ranges=r_Stk6});
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"MET",                     .pfs={"StackPlotSignal","JetHTMET","S_ExclMRR2",njet_bin},        .cuts={},.draw=d,.opt=o_stk_s_S,.ranges=r_Stk6});
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"MR",                      .pfs={"StackPlotSignal","JetHTMET","S_ExclMR",njet_bin},          .cuts={},.draw=d,.opt=o_stk_s_S,.ranges=r_Stk6});
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"MTR",                     .pfs={"StackPlotSignal","JetHTMET","S_ExclR2",njet_bin},          .cuts={},.draw=d,.opt=o_stk_s_S,.ranges=r_Stk6});
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"R2",                      .pfs={"StackPlotSignal","JetHTMET","S_ExclR2",njet_bin},          .cuts={},.draw=d,.opt=o_stk_s_S,.ranges=r_Stk6});
//TEMP      sh.AddHistos("evt",    { .fill="MR_vs_MET",                 .pfs={"Signals_Background","S_ExclMRR2",njet_bin},   .cuts={},.draw="COLZ",.opt=o_1or2d_s+"Log",.ranges={}});
//TEMP      sh.AddHistos("evt",    { .fill="R2_vs_MET",                 .pfs={"Signals_Background","S_ExclMRR2",njet_bin},   .cuts={},.draw="COLZ",.opt=o_1or2d_s+"Log",.ranges={}});
//TEMP      sh.AddHistos("evt",    { .fill="R2_vs_MR",                  .pfs={"Signals_Background","S_ExclMRR2",njet_bin}, .cuts={},.draw="COLZ",.opt=o_1or2d_s+"Log",.ranges={}});
//TEMP      sh.AddHistos("evt",    { .fill="MR_vs_HTFine",              .pfs={"Signals_Background","S_ExclMRR2",njet_bin},   .cuts={},.draw="COLZ",.opt=o_1or2d_s+"Log",.ranges={}});
//TEMP      sh.AddHistos("evt",    { .fill="MET_vs_HTFine",             .pfs={"Signals_Background","S_ExclMRR2",njet_bin},   .cuts={},.draw="COLZ",.opt=o_1or2d_s+"Log",.ranges={}});
//TEMP      sh.AddHistos("evt",    { .fill="R2Fine_vs_MRFine",          .pfs={"Signals_Background","S_ExclMRR2",njet_bin}, .cuts={},.draw="COLZ",.opt=o_1or2d_s+"Log",.ranges={}});
//TEMP    }
//TEMP  #if TOP == 0
//TEMP    sh.AddHistos("evt",    { .fill="NTop_vs_NW",          .pfs={"Data_MC","S_Excl1W"},          .cuts={},.draw="COLZ",.opt=o_1or2d_d,.ranges={}});
//TEMP    sh.AddHistos("evt",    { .fill="NTop_vs_NW",          .pfs={"Signals","S_Excl1W"},          .cuts={},.draw="COLZ",.opt=o_1or2d_s,.ranges={}});
//TEMP    sh.AddHistos("evt",    { .fill="NTop_vs_NW",          .pfs={"Data_MC","S_Excl1b1W"},        .cuts={},.draw="COLZ",.opt=o_1or2d_d,.ranges={}});
//TEMP    sh.AddHistos("evt",    { .fill="NTop_vs_NW",          .pfs={"Signals","S_Excl1b1W"},        .cuts={},.draw="COLZ",.opt=o_1or2d_s,.ranges={}});
//TEMP  #endif
//TEMP    sh.AddHistos(s+"evt",  { .fill=c+"NW",          .pfs={"StackPlotSignal","Blind","S"},       .cuts={},.draw=d,.opt=o_stk_s_S,.ranges=r_Stk6});
//TEMP    sh.AddHistos(s+"evt",  { .fill=c+"NTop",        .pfs={"StackPlotSignal","Blind","S"},       .cuts={},.draw=d,.opt=o_stk_s_S,.ranges=r_Stk6});
//TEMP    sh.AddHistos(s+"evt",  { .fill=c+"NW",          .pfs={"StackPlotSignal","JetHTMET","S"},       .cuts={},.draw=d,.opt=o_stk_s_S,.ranges=r_Stk6});
//TEMP    sh.AddHistos(s+"evt",  { .fill=c+"NTop",        .pfs={"StackPlotSignal","JetHTMET","S"},       .cuts={},.draw=d,.opt=o_stk_s_S,.ranges=r_Stk6});
//TEMP  
//TEMP    // N-1 Cut plots
//TEMP    // S
//TEMP  #if TOP == 0
//TEMP    sh.AddHistos(s+"evt",  { .fill=c+"NW",          .pfs={"StackPlotSignal","Blind","S_Excl1W"},                .cuts={},.draw=d,.opt=o_stk_s_S,.ranges=r_Stk6});
//TEMP    sh.AddHistos(s+"evt",  { .fill=c+"NTop",        .pfs={"StackPlotSignal","Blind","S_Excl1W"},                .cuts={},.draw=d,.opt=o_stk_s_S,.ranges=r_Stk6});
//TEMP    sh.AddHistos(s+"evt",  { .fill=c+"NW",          .pfs={"StackPlotSignal","JetHTMET","S_Excl1W"},                .cuts={},.draw=d,.opt=o_stk_s_S,.ranges=r_Stk6});
//TEMP    sh.AddHistos(s+"evt",  { .fill=c+"NTop",        .pfs={"StackPlotSignal","JetHTMET","S_Excl1W"},                .cuts={},.draw=d,.opt=o_stk_s_S,.ranges=r_Stk6});
//TEMP    sh.AddHistos(s+"W",    { .fill=c+"WPt",         .pfs={"StackPlotSignal","Blind","S"},                       .cuts={},.draw=d,.opt=o_stk_s_S,.ranges=r_Stk4});
//TEMP  #else
//TEMP    sh.AddHistos(s+"evt",  { .fill=c+"NW",          .pfs={"StackPlotSignal","Blind","S_Excl1Top"},              .cuts={},.draw=d,.opt=o_stk_s_S,.ranges=r_Stk6});
//TEMP    sh.AddHistos(s+"evt",  { .fill=c+"NTop",        .pfs={"StackPlotSignal","Blind","S_Excl1Top"},              .cuts={},.draw=d,.opt=o_stk_s_S,.ranges=r_Stk6});
//TEMP    sh.AddHistos(s+"evt",  { .fill=c+"NW",          .pfs={"StackPlotSignal","JetHTMET","S_Excl1Top"},              .cuts={},.draw=d,.opt=o_stk_s_S,.ranges=r_Stk6});
//TEMP    sh.AddHistos(s+"evt",  { .fill=c+"NTop",        .pfs={"StackPlotSignal","JetHTMET","S_Excl1Top"},              .cuts={},.draw=d,.opt=o_stk_s_S,.ranges=r_Stk6});
//TEMP    sh.AddHistos(s+"Top",  { .fill=c+"TopPt",       .pfs={"StackPlotSignal","Blind","S"},                       .cuts={},.draw=d,.opt=o_stk_s_S,.ranges=r_Stk4});
//TEMP  #endif
//TEMP    sh.AddHistos(s+"evt",  { .fill=c+"NJet",        .pfs={"StackPlotSignal","Blind","S_ExclNJet"},              .cuts={},.draw=d,.opt=o_stk_s_S,.ranges=r_Stk6});
//TEMP    sh.AddHistos(s+"evt",  { .fill=c+"DeltaRWb",    .pfs={"StackPlotSignal","Blind","S"},                       .cuts={},.draw=d,.opt=o_stk_s_S,.ranges=r_Stk6});
//TEMP    sh.AddHistos(s+"evt",  { .fill=c+"MinDeltaPhi", .pfs={"StackPlotSignal","Blind","S_ExcldPhi"},              .cuts={},.draw=d,.opt=o_stk_s_S,.ranges=r_Stk6});
//TEMP    sh.AddHistos(s+"evt",  { .fill=c+"DeltaPhi",    .pfs={"StackPlotSignal","Blind","S_ExcldPhi"},              .cuts={},.draw=d,.opt=o_stk_s_S,.ranges=r_Stk6});
//TEMP    sh.AddHistos(s+"evt",  { .fill=c+"NJet",        .pfs={"StackPlotSignal","JetHTMET","S_ExclNJet"},              .cuts={},.draw=d,.opt=o_stk_d_S,.ranges=r_Stk6});
//TEMP    sh.AddHistos(s+"evt",  { .fill=c+"DeltaRWb",    .pfs={"StackPlotSignal","JetHTMET","S"},                       .cuts={},.draw=d,.opt=o_stk_d_S,.ranges=r_Stk6});
//TEMP    sh.AddHistos(s+"evt",  { .fill=c+"MinDeltaPhi", .pfs={"StackPlotSignal","JetHTMET","S_ExcldPhi"},              .cuts={},.draw=d,.opt=o_stk_d_S,.ranges=r_Stk6});
//TEMP    sh.AddHistos(s+"evt",  { .fill=c+"DeltaPhi",    .pfs={"StackPlotSignal","JetHTMET","S_ExcldPhi"},              .cuts={},.draw=d,.opt=o_stk_d_S,.ranges=r_Stk6});
//TEMP    sh.AddHistos(s+"evt",  { .fill=c+"NJet",        .pfs={"StackPlotSignal","JetHTMET","s_ExclNJet"},              .cuts={},.draw=d,.opt=o_stk_d_S,.ranges=r_Stk6});
//TEMP    sh.AddHistos(s+"evt",  { .fill=c+"DeltaRWb",    .pfs={"StackPlotSignal","JetHTMET","s"},                       .cuts={},.draw=d,.opt=o_stk_d_S,.ranges=r_Stk6});
//TEMP    sh.AddHistos(s+"evt",  { .fill=c+"MinDeltaPhi", .pfs={"StackPlotSignal","JetHTMET","s_ExclInvdPhi"},           .cuts={},.draw=d,.opt=o_stk_d_S,.ranges=r_Stk6});
//TEMP    sh.AddHistos(s+"evt",  { .fill=c+"DeltaPhi",    .pfs={"StackPlotSignal","JetHTMET","s_ExclInvdPhi"},           .cuts={},.draw=d,.opt=o_stk_d_S,.ranges=r_Stk6});
//TEMP    for (auto njet_bin : {"NJet45"}) {
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"NEleVeto",    .pfs={"StackPlotSignal","JetHTMET","S_Excl0Ele0Tau",   njet_bin},  .cuts={},.draw=d,.opt=o_stk_d_S,.ranges=r_Stk6});
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"NMuVeto",     .pfs={"StackPlotSignal","JetHTMET","S_Excl0Mu0Tau",    njet_bin},  .cuts={},.draw=d,.opt=o_stk_d_S,.ranges=r_Stk6});
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"NIsoTrk",     .pfs={"StackPlotSignal","JetHTMET","S_Excl0Tau",   njet_bin},  .cuts={},.draw=d,.opt=o_stk_d_S,.ranges=r_Stk6});
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"NTauVeto",    .pfs={"StackPlotSignal","JetHTMET","S_Excl0Tau",   njet_bin},  .cuts={},.draw=d,.opt=o_stk_d_S,.ranges=r_Stk6});
//TEMP  #if TOP == 0
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"NBTag",       .pfs={"StackPlotSignal","Blind","S_Excl1b",     njet_bin},  .cuts={},.draw=d,.opt=o_stk_s_S,.ranges=r_Stk6});
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"NW",          .pfs={"StackPlotSignal","Blind","S_Excl1W",     njet_bin},  .cuts={},.draw=d,.opt=o_stk_s_S,.ranges=r_Stk6});
//TEMP      sh.AddHistos(s+"mW",   { .fill=c+"mWTau21",     .pfs={"StackPlotSignal","Blind","S_Excl1W",     njet_bin},  .cuts={},.draw=d,.opt=o_stk_s_S,.ranges=r_Stk6});
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"NBTag",       .pfs={"StackPlotSignal","JetHTMET","S_Excl1b",     njet_bin},  .cuts={},.draw=d,.opt=o_stk_d_S,.ranges=r_Stk6});
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"NW",          .pfs={"StackPlotSignal","JetHTMET","S_Excl1W",     njet_bin},  .cuts={},.draw=d,.opt=o_stk_d_S,.ranges=r_Stk6});
//TEMP      sh.AddHistos(s+"mW",   { .fill=c+"mWTau21",     .pfs={"StackPlotSignal","JetHTMET","S_Excl1W",     njet_bin},  .cuts={},.draw=d,.opt=o_stk_d_S,.ranges=r_Stk6});
//TEMP  #else
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"NBTag",       .pfs={"StackPlotSignal","Blind","S_Excl1Top",   njet_bin},  .cuts={},.draw=d,.opt=o_stk_s_S,.ranges=r_Stk6});
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"NTop",        .pfs={"StackPlotSignal","Blind","S_Excl1Top",   njet_bin},  .cuts={},.draw=d,.opt=o_stk_s_S,.ranges=r_Stk6});
//TEMP      sh.AddHistos(s+"mTop", { .fill=c+"mTopTau32",   .pfs={"StackPlotSignal","Blind","S_Excl1Top",   njet_bin},  .cuts={},.draw=d,.opt=o_stk_s_S,.ranges=r_Stk6});
//TEMP      sh.AddHistos(s+"MTop", { .fill=c+"MTopTau32",   .pfs={"StackPlotSignal","Blind","S_Excl1Top",   njet_bin},  .cuts={},.draw=d,.opt=o_stk_s_S,.ranges=r_Stk6});
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"NBTag",       .pfs={"StackPlotSignal","JetHTMET","S_Excl1Top",   njet_bin},  .cuts={},.draw=d,.opt=o_stk_d_S,.ranges=r_Stk6});
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"NTop",        .pfs={"StackPlotSignal","JetHTMET","S_Excl1Top",   njet_bin},  .cuts={},.draw=d,.opt=o_stk_d_S,.ranges=r_Stk6});
//TEMP      sh.AddHistos(s+"mTop", { .fill=c+"mTopTau32",   .pfs={"StackPlotSignal","JetHTMET","S_Excl1Top",   njet_bin},  .cuts={},.draw=d,.opt=o_stk_d_S,.ranges=r_Stk6});
//TEMP      sh.AddHistos(s+"MTop", { .fill=c+"MTopTau32",   .pfs={"StackPlotSignal","JetHTMET","S_Excl1Top",   njet_bin},  .cuts={},.draw=d,.opt=o_stk_d_S,.ranges=r_Stk6});
//TEMP  #endif
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"DeltaRWb",    .pfs={"StackPlotSignal","Blind","S",            njet_bin},  .cuts={},.draw=d,.opt=o_stk_s_S,.ranges=r_Stk6});
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"MinDeltaPhi", .pfs={"StackPlotSignal","Blind","S_ExcldPhi",   njet_bin},  .cuts={},.draw=d,.opt=o_stk_s_S,.ranges=r_Stk6});
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"DeltaPhi",    .pfs={"StackPlotSignal","Blind","S_ExcldPhi",   njet_bin},  .cuts={},.draw=d,.opt=o_stk_s_S,.ranges=r_Stk6});
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"DeltaRWb",    .pfs={"StackPlotSignal","JetHTMET","S",            njet_bin},  .cuts={},.draw=d,.opt=o_stk_d_S,.ranges=r_Stk6});
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"MinDeltaPhi", .pfs={"StackPlotSignal","JetHTMET","S_ExcldPhi",   njet_bin},  .cuts={},.draw=d,.opt=o_stk_d_S,.ranges=r_Stk6});
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"DeltaPhi",    .pfs={"StackPlotSignal","JetHTMET","S_ExcldPhi",   njet_bin},  .cuts={},.draw=d,.opt=o_stk_d_S,.ranges=r_Stk6});
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"NEleVeto",    .pfs={"StackPlotSignal","JetHTMET","s_Excl0Ele0Tau",   njet_bin},  .cuts={},.draw=d,.opt=o_stk_d_S,.ranges=r_Stk6});
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"NMuVeto",     .pfs={"StackPlotSignal","JetHTMET","s_Excl0Mu0Tau",    njet_bin},  .cuts={},.draw=d,.opt=o_stk_d_S,.ranges=r_Stk6});
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"NIsoTrk",     .pfs={"StackPlotSignal","JetHTMET","s_Excl0Tau",   njet_bin},  .cuts={},.draw=d,.opt=o_stk_d_S,.ranges=r_Stk6});
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"NTauVeto",    .pfs={"StackPlotSignal","JetHTMET","s_Excl0Tau",   njet_bin},  .cuts={},.draw=d,.opt=o_stk_d_S,.ranges=r_Stk6});
//TEMP  #if TOP == 0
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"NBTag",       .pfs={"StackPlotSignal","JetHTMET","s_Excl1b",      njet_bin}, .cuts={},.draw=d,.opt=o_stk_d_S,.ranges=r_Stk6});
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"NW",          .pfs={"StackPlotSignal","JetHTMET","s_Excl1W",      njet_bin}, .cuts={},.draw=d,.opt=o_stk_d_S,.ranges=r_Stk6});
//TEMP      sh.AddHistos(s+"mW",   { .fill=c+"mWTau21",     .pfs={"StackPlotSignal","JetHTMET","s_Excl1W",      njet_bin}, .cuts={},.draw=d,.opt=o_stk_d_S,.ranges=r_Stk6});
//TEMP  #else
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"NBTag",       .pfs={"StackPlotSignal","JetHTMET","s_Excl1Top",    njet_bin}, .cuts={},.draw=d,.opt=o_stk_d_S,.ranges=r_Stk6});
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"NTop",        .pfs={"StackPlotSignal","JetHTMET","s_Excl1Top",    njet_bin}, .cuts={},.draw=d,.opt=o_stk_d_S,.ranges=r_Stk6});
//TEMP      sh.AddHistos(s+"mTop", { .fill=c+"mTopTau32",   .pfs={"StackPlotSignal","JetHTMET","s_Excl1Top",    njet_bin}, .cuts={},.draw=d,.opt=o_stk_d_S,.ranges=r_Stk6});
//TEMP      sh.AddHistos(s+"MTop", { .fill=c+"MTopTau32",   .pfs={"StackPlotSignal","JetHTMET","s_Excl1Top",    njet_bin}, .cuts={},.draw=d,.opt=o_stk_d_S,.ranges=r_Stk6});
//TEMP  #endif
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"DeltaRWb",    .pfs={"StackPlotSignal","JetHTMET","s",             njet_bin}, .cuts={},.draw=d,.opt=o_stk_d_S,.ranges=r_Stk6});
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"MinDeltaPhi", .pfs={"StackPlotSignal","JetHTMET","s_ExclInvdPhi", njet_bin}, .cuts={},.draw=d,.opt=o_stk_d_S,.ranges=r_Stk6});
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"DeltaPhi",    .pfs={"StackPlotSignal","JetHTMET","s_ExclInvdPhi", njet_bin}, .cuts={},.draw=d,.opt=o_stk_d_S,.ranges=r_Stk6});
//TEMP    }
//TEMP    // Other
//TEMP  #if TOP == 0
//TEMP    sh.AddHistos(s+"evt",  { .fill=c+"HTFine",       .pfs={"StackPlotSignal","Blind","S_Excl1W"},               .cuts={},.draw=d,.opt=o_stk_s_S,.ranges=r_Stk6});
//TEMP    sh.AddHistos(s+"evt",  { .fill=c+"HTFine",       .pfs={"StackPlotSignal","JetHTMET","S_Excl1W"},               .cuts={},.draw=d,.opt=o_stk_d_S,.ranges=r_Stk6});
//TEMP  #else
//TEMP    sh.AddHistos(s+"evt",  { .fill=c+"HTFine",       .pfs={"StackPlotSignal","Blind","S_Excl1Top"},             .cuts={},.draw=d,.opt=o_stk_s_S,.ranges=r_Stk6});
//TEMP    sh.AddHistos(s+"evt",  { .fill=c+"HTFine",       .pfs={"StackPlotSignal","JetHTMET","S_Excl1Top"},             .cuts={},.draw=d,.opt=o_stk_d_S,.ranges=r_Stk6});
//TEMP  #endif
//TEMP  
//TEMP    // N-1 Weights
//TEMP    // Number of vertices
//TEMP    sh.AddHistos(s+"evt",  { .fill=c+"NVtx",        .pfs={"StackPlotSignal","JetHTMET","S_3Cuts"}, .cuts={},.draw=d,.opt=o_stk_d_S,.ranges=r_Stk6});
//TEMP    sh.AddHistos(s+"evt",  { .fill=c+"NVtx",        .pfs={"StackPlotSignal","JetHTMET","S_6Cuts"}, .cuts={},.draw=d,.opt=o_stk_d_S,.ranges=r_Stk6});
//TEMP    sh.AddHistos(s+"evt",  { .fill=c+"NVtx",        .pfs={"StackPlotSignal","JetHTMET","S"},       .cuts={},.draw=d,.opt=o_stk_d_S,.ranges=r_Stk6});
//TEMP    // Same plots with no pile-up reweighting
//TEMP    sh.SetHistoWeights({ [] { return w_nm1['S'][3]; } });
//TEMP    sh.AddHistos("evt",  { .fill="NVtx",        .pfs={"StackPlotSignal","JetHTMET","S_3Cuts","NoPUWeight"}, .cuts={},.draw=d,.opt=o_stk_d_S,.ranges=r_Stk6});
//TEMP    sh.AddHistos("evt",  { .fill="NVtx",        .pfs={"StackPlotSignal","JetHTMET","S_6Cuts","NoPUWeight"}, .cuts={},.draw=d,.opt=o_stk_d_S,.ranges=r_Stk6});
//TEMP    sh.AddHistos("evt",  { .fill="NVtx",        .pfs={"StackPlotSignal","JetHTMET","S"      ,"NoPUWeight"}, .cuts={},.draw=d,.opt=o_stk_d_S,.ranges=r_Stk6});
//TEMP    // No trigger efficiency
//TEMP    sh.SetHistoWeights({ [] { return w_nm1['S'][7]; } });
//TEMP    sh.AddHistos("evt",  { .fill="NJet",        .pfs={"StackPlotSignal","JetHTMET","S_ExclNJetHLT",   "NoTrigWeight"}, .cuts={},.draw=d,.opt=o_stk_d_S,.ranges=r_Stk6});
//TEMP    sh.AddHistos("evt",  { .fill="HTFine",      .pfs={"StackPlotSignal","JetHTMET","S_ExclHLT",       "NoTrigWeight"}, .cuts={},.draw=d,.opt=o_stk_d_S,.ranges=r_Stk6});
//TEMP    sh.AddHistos("evt",  { .fill="MET",         .pfs={"StackPlotSignal","JetHTMET","S_ExclHLT",       "NoTrigWeight"}, .cuts={},.draw=d,.opt=o_stk_d_S,.ranges=r_Stk6});
//TEMP    sh.AddHistos("evt",  { .fill="MR",          .pfs={"StackPlotSignal","JetHTMET","S_ExclHLT",       "NoTrigWeight"}, .cuts={},.draw=d,.opt=o_stk_d_S,.ranges=r_Stk6});
//TEMP    sh.AddHistos("evt",  { .fill="MTR",         .pfs={"StackPlotSignal","JetHTMET","S_ExclHLT",       "NoTrigWeight"}, .cuts={},.draw=d,.opt=o_stk_d_S,.ranges=r_Stk6});
//TEMP    sh.AddHistos("evt",  { .fill="R2",          .pfs={"StackPlotSignal","JetHTMET","S_ExclHLT",       "NoTrigWeight"}, .cuts={},.draw=d,.opt=o_stk_d_S,.ranges=r_Stk6});
//TEMP    sh.AddHistos("evt",  { .fill="RazorBins",   .pfs={"StackPlotSignal","JetHTMET","S_ExclHLT",       "NoTrigWeight"}, .cuts={},.draw=d,.opt=o_stk_d_S,.ranges=r_Stk6});
//TEMP    sh.AddHistos("evt",  { .fill="MET_vs_HTFine",    .pfs={"Signals_Background","S_ExclHLT","NoTrigWeight"}, .cuts={},.draw="COLZ",.opt=o_1or2d_s+"Log",.ranges={}});
//TEMP    sh.AddHistos("evt",  { .fill="MRFine_vs_HTFine", .pfs={"Signals_Background","S_ExclHLT","NoTrigWeight"}, .cuts={},.draw="COLZ",.opt=o_1or2d_s+"Log",.ranges={}});
//TEMP    sh.AddHistos("evt",  { .fill="MRFine_vs_MET",    .pfs={"Signals_Background","S_ExclHLT","NoTrigWeight"}, .cuts={},.draw="COLZ",.opt=o_1or2d_s+"Log",.ranges={}});
//TEMP    sh.AddHistos("evt",  { .fill="R2Fine_vs_HTFine", .pfs={"Signals_Background","S_ExclHLT","NoTrigWeight"}, .cuts={},.draw="COLZ",.opt=o_1or2d_s+"Log",.ranges={}});
//TEMP    sh.AddHistos("evt",  { .fill="R2Fine_vs_MET",    .pfs={"Signals_Background","S_ExclHLT","NoTrigWeight"}, .cuts={},.draw="COLZ",.opt=o_1or2d_s+"Log",.ranges={}});
//TEMP    sh.AddHistos("evt",  { .fill="R2Fine_vs_MRFine", .pfs={"Signals_Background","S_ExclHLT","NoTrigWeight"}, .cuts={},.draw="COLZ",.opt=o_1or2d_s+"Log",.ranges={}});
//TEMP    // No scale factors
//TEMP    sh.SetHistoWeights({ [this] { return w_nm1['S'][all_weights.size()]; } });
//TEMP    sh.AddHistos("evt",  { .fill="NEleVeto",    .pfs={"StackPlotSignal","JetHTMET","S_Excl0Ele0Tau","NoEleSF"}, .cuts={},.draw=d,.opt=o_stk_d_S,.ranges=r_Stk6});
//TEMP    sh.AddHistos("evt",  { .fill="NJet",        .pfs={"StackPlotSignal","JetHTMET","S_ExclNJet","NoEleSF"}, .cuts={},.draw=d,.opt=o_stk_d_S,.ranges=r_Stk6});
//TEMP    sh.AddHistos("evt",  { .fill="HTFine",      .pfs={"StackPlotSignal","JetHTMET","S",         "NoEleSF"}, .cuts={},.draw=d,.opt=o_stk_d_S,.ranges=r_Stk6});
//TEMP    sh.AddHistos("evt",  { .fill="MET",         .pfs={"StackPlotSignal","JetHTMET","S",         "NoEleSF"}, .cuts={},.draw=d,.opt=o_stk_d_S,.ranges=r_Stk6});
//TEMP    sh.AddHistos("evt",  { .fill="MR",          .pfs={"StackPlotSignal","JetHTMET","S",         "NoEleSF"}, .cuts={},.draw=d,.opt=o_stk_d_S,.ranges=r_Stk6});
//TEMP    sh.AddHistos("evt",  { .fill="MTR",         .pfs={"StackPlotSignal","JetHTMET","S",         "NoEleSF"}, .cuts={},.draw=d,.opt=o_stk_d_S,.ranges=r_Stk6});
//TEMP    sh.AddHistos("evt",  { .fill="R2",          .pfs={"StackPlotSignal","JetHTMET","S",         "NoEleSF"}, .cuts={},.draw=d,.opt=o_stk_d_S,.ranges=r_Stk6});
//TEMP    sh.AddHistos("evt",  { .fill="RazorBins",   .pfs={"StackPlotSignal","JetHTMET","S",         "NoEleSF"}, .cuts={},.draw=d,.opt=o_stk_d_S,.ranges=r_Stk6});
//TEMP    sh.AddHistos("evt",  { .fill="R2_vs_MR",    .pfs={"Signals_Background","S",  "NoEleSF"}, .cuts={},.draw="COLZ",.opt=o_1or2d_s+"Log",.ranges={}});
//TEMP    sh.SetHistoWeights({ [this] { return w_nm1['S'][all_weights.size()+1]; } });
//TEMP    sh.AddHistos("evt",  { .fill="NMuVeto",     .pfs={"StackPlotSignal","JetHTMET","S_Excl0Mu0Tau", "NoMuonSF"}, .cuts={},.draw=d,.opt=o_stk_d_S,.ranges=r_Stk6});
//TEMP    sh.AddHistos("evt",  { .fill="NJet",        .pfs={"StackPlotSignal","JetHTMET","S_ExclNJet","NoMuonSF"}, .cuts={},.draw=d,.opt=o_stk_d_S,.ranges=r_Stk6});
//TEMP    sh.AddHistos("evt",  { .fill="HTFine",      .pfs={"StackPlotSignal","JetHTMET","S",         "NoMuonSF"}, .cuts={},.draw=d,.opt=o_stk_d_S,.ranges=r_Stk6});
//TEMP    sh.AddHistos("evt",  { .fill="MET",         .pfs={"StackPlotSignal","JetHTMET","S",         "NoMuonSF"}, .cuts={},.draw=d,.opt=o_stk_d_S,.ranges=r_Stk6});
//TEMP    sh.AddHistos("evt",  { .fill="MR",          .pfs={"StackPlotSignal","JetHTMET","S",         "NoMuonSF"}, .cuts={},.draw=d,.opt=o_stk_d_S,.ranges=r_Stk6});
//TEMP    sh.AddHistos("evt",  { .fill="MTR",         .pfs={"StackPlotSignal","JetHTMET","S",         "NoMuonSF"}, .cuts={},.draw=d,.opt=o_stk_d_S,.ranges=r_Stk6});
//TEMP    sh.AddHistos("evt",  { .fill="R2",          .pfs={"StackPlotSignal","JetHTMET","S",         "NoMuonSF"}, .cuts={},.draw=d,.opt=o_stk_d_S,.ranges=r_Stk6});
//TEMP    sh.AddHistos("evt",  { .fill="RazorBins",   .pfs={"StackPlotSignal","JetHTMET","S",         "NoMuonSF"}, .cuts={},.draw=d,.opt=o_stk_d_S,.ranges=r_Stk6});
//TEMP    sh.AddHistos("evt",  { .fill="R2_vs_MR",    .pfs={"Signals_Background","S",  "NoMuonSF"}, .cuts={},.draw="COLZ",.opt=o_1or2d_s+"Log",.ranges={}});
//TEMP  #if TOP == 0
//TEMP    sh.SetHistoWeights({ [this] { return w_nm1['S'][all_weights.size()+2]; } });
//TEMP    sh.AddHistos("evt",  { .fill="NBTag",       .pfs={"StackPlotSignal","JetHTMET","S_Excl1b",  "NoBTagSF"}, .cuts={},.draw=d,.opt=o_stk_d_S,.ranges=r_Stk6});
//TEMP    sh.AddHistos("evt",  { .fill="NJet",        .pfs={"StackPlotSignal","JetHTMET","S_ExclNJet","NoBTagSF"}, .cuts={},.draw=d,.opt=o_stk_d_S,.ranges=r_Stk6});
//TEMP    sh.AddHistos("evt",  { .fill="HTFine",      .pfs={"StackPlotSignal","JetHTMET","S",         "NoBTagSF"}, .cuts={},.draw=d,.opt=o_stk_d_S,.ranges=r_Stk6});
//TEMP    sh.AddHistos("evt",  { .fill="MET",         .pfs={"StackPlotSignal","JetHTMET","S",         "NoBTagSF"}, .cuts={},.draw=d,.opt=o_stk_d_S,.ranges=r_Stk6});
//TEMP    sh.AddHistos("evt",  { .fill="MR",          .pfs={"StackPlotSignal","JetHTMET","S",         "NoBTagSF"}, .cuts={},.draw=d,.opt=o_stk_d_S,.ranges=r_Stk6});
//TEMP    sh.AddHistos("evt",  { .fill="MTR",         .pfs={"StackPlotSignal","JetHTMET","S",         "NoBTagSF"}, .cuts={},.draw=d,.opt=o_stk_d_S,.ranges=r_Stk6});
//TEMP    sh.AddHistos("evt",  { .fill="R2",          .pfs={"StackPlotSignal","JetHTMET","S",         "NoBTagSF"}, .cuts={},.draw=d,.opt=o_stk_d_S,.ranges=r_Stk6});
//TEMP    sh.AddHistos("evt",  { .fill="RazorBins",   .pfs={"StackPlotSignal","JetHTMET","S",         "NoBTagSF"}, .cuts={},.draw=d,.opt=o_stk_d_S,.ranges=r_Stk6});
//TEMP    sh.AddHistos("evt",  { .fill="R2_vs_MR",    .pfs={"Signals_Background","S",  "NoBTagSF"}, .cuts={},.draw="COLZ",.opt=o_1or2d_s+"Log",.ranges={}});
//TEMP    sh.SetHistoWeights({ [this] { return w_nm1['S'][all_weights.size()+3]; } });
//TEMP    sh.AddHistos("evt",  { .fill="NW",          .pfs={"StackPlotSignal","JetHTMET","S_Excl1W",  "NoWTagSF"}, .cuts={},.draw=d,.opt=o_stk_d_S,.ranges=r_Stk6});
//TEMP    sh.AddHistos("evt",  { .fill="NJet",        .pfs={"StackPlotSignal","JetHTMET","S_ExclNJet","NoWTagSF"}, .cuts={},.draw=d,.opt=o_stk_d_S,.ranges=r_Stk6});
//TEMP    sh.AddHistos("evt",  { .fill="HTFine",      .pfs={"StackPlotSignal","JetHTMET","S",         "NoWTagSF"}, .cuts={},.draw=d,.opt=o_stk_d_S,.ranges=r_Stk6});
//TEMP    sh.AddHistos("evt",  { .fill="MET",         .pfs={"StackPlotSignal","JetHTMET","S",         "NoWTagSF"}, .cuts={},.draw=d,.opt=o_stk_d_S,.ranges=r_Stk6});
//TEMP    sh.AddHistos("evt",  { .fill="MR",          .pfs={"StackPlotSignal","JetHTMET","S",         "NoWTagSF"}, .cuts={},.draw=d,.opt=o_stk_d_S,.ranges=r_Stk6});
//TEMP    sh.AddHistos("evt",  { .fill="MTR",         .pfs={"StackPlotSignal","JetHTMET","S",         "NoWTagSF"}, .cuts={},.draw=d,.opt=o_stk_d_S,.ranges=r_Stk6});
//TEMP    sh.AddHistos("evt",  { .fill="R2",          .pfs={"StackPlotSignal","JetHTMET","S",         "NoWTagSF"}, .cuts={},.draw=d,.opt=o_stk_d_S,.ranges=r_Stk6});
//TEMP    sh.AddHistos("evt",  { .fill="RazorBins",   .pfs={"StackPlotSignal","JetHTMET","S",         "NoWTagSF"}, .cuts={},.draw=d,.opt=o_stk_d_S,.ranges=r_Stk6});
//TEMP    sh.AddHistos("evt",  { .fill="R2_vs_MR",    .pfs={"Signals_Background","S",  "NoWTagSF"}, .cuts={},.draw="COLZ",.opt=o_1or2d_s+"Log",.ranges={}});
//TEMP  #endif
//TEMP  
//TEMP    // -------------------------------------------------------------------------
//TEMP    //                       QCD enriched Region: Q and Q'
//TEMP  
//TEMP    sh.SetHistoWeights({ [this] { return sf_weight['Q']; } });
//TEMP  
//TEMP    for (const auto& cut : 
//TEMP      {   "Q", "q" }) {
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"NJet",                    .pfs={Stack,"JetHTMET",cut},                   .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"HTFine",                  .pfs={Stack,"JetHTMET",cut},                   .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"MET",                     .pfs={Stack,"JetHTMET",cut},                   .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"MR",                      .pfs={Stack,"JetHTMET",cut},                   .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"MTR",                     .pfs={Stack,"JetHTMET",cut},                   .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"R2",                      .pfs={Stack,"JetHTMET",cut},                   .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"RazorBins",               .pfs={Stack,"JetHTMET",cut},                   .cuts={},.draw=d,.opt=O_stk_d+"NoComb5",.ranges=r_Stk8});
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"HT",                      .pfs={Stack,"JetHTMET",cut},                   .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"HTJet1AK8Pt",             .pfs={Stack,"JetHTMET",cut},                   .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP      for (auto njet_bin : {"NJet45"}) {
//TEMP        sh.AddHistos(s+"evt",  { .fill=c+"NJetAK8",                 .pfs={Stack,"JetHTMET",cut,njet_bin},          .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP        sh.AddHistos(s+"evt",  { .fill=c+"HTFine",                  .pfs={Stack,"JetHTMET",cut,njet_bin},          .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP        sh.AddHistos(s+"evt",  { .fill=c+"MET",                     .pfs={Stack,"JetHTMET",cut,njet_bin},          .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP        sh.AddHistos(s+"evt",  { .fill=c+"MR",                      .pfs={Stack,"JetHTMET",cut,njet_bin},          .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP        sh.AddHistos(s+"evt",  { .fill=c+"MTR",                     .pfs={Stack,"JetHTMET",cut,njet_bin},          .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP        sh.AddHistos(s+"evt",  { .fill=c+"R2",                      .pfs={Stack,"JetHTMET",cut,njet_bin},          .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP        sh.AddHistos(s+"evt",  { .fill=c+"RazorBins",               .pfs={Stack,"JetHTMET",cut,njet_bin},          .cuts={},.draw=d,.opt=O_stk_d+"NoComb5",.ranges={0,0, 1.01e-2,1e7,  0.4,0.86, 0.343 }}); // 7th range param: ratio legx1
//TEMP        sh.AddHistos(s+"evt",  { .fill=c+"HT",                      .pfs={Stack,"JetHTMET",cut,njet_bin},          .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP        sh.AddHistos(s+"evt",  { .fill=c+"HTJet1AK8Pt",             .pfs={Stack,"JetHTMET",cut,njet_bin},          .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP      }
//TEMP    }
//TEMP    
//TEMP    // N-1 plots
//TEMP    // Q
//TEMP    sh.AddHistos(s+"evt",  { .fill=c+"NJet",        .pfs={Stack,"JetHTMET","Q_ExclNJet"},                 .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP    sh.AddHistos(s+"evt",  { .fill=c+"MR",          .pfs={Stack,"JetHTMET","Q_ExclMR"},                   .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP    sh.AddHistos(s+"evt",  { .fill=c+"MTR",         .pfs={Stack,"JetHTMET","Q_ExclR2"},                   .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP    sh.AddHistos(s+"evt",  { .fill=c+"R2",          .pfs={Stack,"JetHTMET","Q_ExclR2"},                   .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP    sh.AddHistos(s+"evt",  { .fill=c+"MinDeltaPhi", .pfs={Stack,"JetHTMET","Q_ExclInvdPhi"},           .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP    sh.AddHistos(s+"evt",  { .fill=c+"DeltaPhi",    .pfs={Stack,"JetHTMET","Q_ExclInvdPhi"},           .cuts={},.draw=d,.opt=O_stk_d,.ranges={0,0, 1.01e-2,1e6,  0.2,0.86}});
//TEMP    // Q'
//TEMP    sh.AddHistos(s+"evt",  { .fill=c+"NJet",        .pfs={Stack,"JetHTMET","q_ExclNJet"},                 .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP    sh.AddHistos(s+"evt",  { .fill=c+"MR",          .pfs={Stack,"JetHTMET","q_ExclMR"},                   .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP    sh.AddHistos(s+"evt",  { .fill=c+"MTR",         .pfs={Stack,"JetHTMET","q_ExclR2"},                   .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP    sh.AddHistos(s+"evt",  { .fill=c+"R2",          .pfs={Stack,"JetHTMET","q_ExclR2"},                   .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP    sh.AddHistos(s+"evt",  { .fill=c+"MinDeltaPhi", .pfs={Stack,"JetHTMET","q_ExcldPhi"},                 .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP    sh.AddHistos(s+"evt",  { .fill=c+"DeltaPhi",    .pfs={Stack,"JetHTMET","q_ExcldPhi"},                 .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP    for (auto njet_bin : {"NJet45"}) {
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"NEleVeto",    .pfs={Stack,"JetHTMET","Q_Excl0Ele0Tau",       njet_bin}, .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"NMuVeto",     .pfs={Stack,"JetHTMET","Q_Excl0Mu0Tau",        njet_bin}, .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"NIsoTrk",     .pfs={Stack,"JetHTMET","Q_Excl0Tau",       njet_bin}, .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"NTauVeto",    .pfs={Stack,"JetHTMET","Q_Excl0Tau",       njet_bin}, .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"NLooseBTag",  .pfs={Stack,"JetHTMET","Q_Excl0b",         njet_bin}, .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP  #if TOP == 0
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"NaW",         .pfs={Stack,"JetHTMET","Q_Excl1aW",        njet_bin}, .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP      sh.AddHistos(s+"mW",   { .fill=c+"mWTau21",     .pfs={Stack,"JetHTMET","Q_Excl1aW",        njet_bin}, .cuts={},.draw=d,.opt=o_stk_d,.ranges={0,0, 1.01e-2,1e8,  0.3,0.86}});
//TEMP  #else
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"NaTop",       .pfs={Stack,"JetHTMET","Q_Excl1aTop",      njet_bin}, .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP      sh.AddHistos(s+"mTop", { .fill=c+"mTopTau32",   .pfs={Stack,"JetHTMET","Q_Excl1aTop",      njet_bin}, .cuts={},.draw=d,.opt=o_stk_d,.ranges={0,0, 1.01e-2,1e8,  0.3,0.8}});
//TEMP  #endif
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"MinDeltaPhi", .pfs={Stack,"JetHTMET","Q_ExclInvdPhi",njet_bin}, .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"DeltaPhi",    .pfs={Stack,"JetHTMET","Q_ExclInvdPhi",njet_bin}, .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"NEleVeto",    .pfs={Stack,"JetHTMET","q_Excl0Ele0Tau",       njet_bin}, .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"NMuVeto",     .pfs={Stack,"JetHTMET","q_Excl0Mu0Tau",        njet_bin}, .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"NIsoTrk",     .pfs={Stack,"JetHTMET","q_Excl0Tau",       njet_bin}, .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"NTauVeto",    .pfs={Stack,"JetHTMET","q_Excl0Tau",       njet_bin}, .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"NLooseBTag",  .pfs={Stack,"JetHTMET","q_Excl0b",         njet_bin}, .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP  #if TOP == 0
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"NaW",         .pfs={Stack,"JetHTMET","q_Excl1aW",        njet_bin}, .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP      sh.AddHistos(s+"mW",   { .fill=c+"mWTau21",     .pfs={Stack,"JetHTMET","q_Excl1aW",        njet_bin}, .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP  #else
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"NaTop",       .pfs={Stack,"JetHTMET","q_Excl1aTop",      njet_bin}, .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP      sh.AddHistos(s+"mTop", { .fill=c+"mTopTau32",   .pfs={Stack,"JetHTMET","q_Excl1aTop",      njet_bin}, .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP  #endif
//TEMP    }
//TEMP  
//TEMP    // Other
//TEMP    //sh.AddHistos(s+"evt",  { .fill=c+"HTFine",       .pfs={Stack,"JetHTMET","Q_Excl1aW"},                 .cuts={},.draw=d,.opt=o_stk_s,.ranges=r_Stk6});
//TEMP  
//TEMP    // N-1 weights
//TEMP    sh.SetHistoWeights({ [this] { return w_nm1['Q'][all_weights.size()+2]; } });
//TEMP    sh.AddHistos("evt",  { .fill="NLooseBTag",  .pfs={Stack,"JetHTMET","Q_Excl0b",  "NoBTagSF"}, .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP    sh.AddHistos("evt",  { .fill="NJet",        .pfs={Stack,"JetHTMET","Q_ExclNJet","NoBTagSF"}, .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP    sh.AddHistos("evt",  { .fill="HTFine",      .pfs={Stack,"JetHTMET","Q",         "NoBTagSF"}, .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP    sh.AddHistos("evt",  { .fill="MET",         .pfs={Stack,"JetHTMET","Q",         "NoBTagSF"}, .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP    sh.AddHistos("evt",  { .fill="MR",          .pfs={Stack,"JetHTMET","Q",         "NoBTagSF"}, .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP    sh.AddHistos("evt",  { .fill="MTR",         .pfs={Stack,"JetHTMET","Q",         "NoBTagSF"}, .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP    sh.AddHistos("evt",  { .fill="R2",          .pfs={Stack,"JetHTMET","Q",         "NoBTagSF"}, .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP    sh.AddHistos("evt",  { .fill="RazorBins",   .pfs={Stack,"JetHTMET","Q",         "NoBTagSF"}, .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP    sh.AddHistos("evt",  { .fill="R2_vs_MR",    .pfs={"Signals_Background","Q",  "NoBTagSF"}, .cuts={},.draw="COLZ",.opt=o_1or2d_s+"Log",.ranges={}});
//TEMP    sh.SetHistoWeights({ [this] { return w_nm1['Q'][all_weights.size()]; } });
//TEMP    sh.AddHistos("evt",  { .fill="NEleVeto",    .pfs={Stack,"JetHTMET","Q_Excl0Ele0Tau",       "NoEleSF"}, .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP    sh.AddHistos("evt",  { .fill="NJet",        .pfs={Stack,"JetHTMET","Q_ExclNJet",       "NoEleSF"}, .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP    sh.AddHistos("evt",  { .fill="HTFine",      .pfs={Stack,"JetHTMET","Q",                "NoEleSF"}, .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP    sh.AddHistos("evt",  { .fill="MET",         .pfs={Stack,"JetHTMET","Q",                "NoEleSF"}, .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP    sh.AddHistos("evt",  { .fill="MR",          .pfs={Stack,"JetHTMET","Q",                "NoEleSF"}, .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP    sh.AddHistos("evt",  { .fill="MTR",         .pfs={Stack,"JetHTMET","Q",                "NoEleSF"}, .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP    sh.AddHistos("evt",  { .fill="R2",          .pfs={Stack,"JetHTMET","Q",                "NoEleSF"}, .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP    sh.AddHistos("evt",  { .fill="RazorBins",   .pfs={Stack,"JetHTMET","Q",                "NoEleSF"}, .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP    sh.AddHistos("evt",  { .fill="R2_vs_MR",    .pfs={"Signals_Background","Q",         "NoEleSF"}, .cuts={},.draw="COLZ",.opt=o_1or2d_s+"Log",.ranges={}});
//TEMP  
//TEMP    // -------------------------------------------------------------------------
//TEMP    //                          Top enriched Region: T
//TEMP  
//TEMP    sh.SetHistoWeights({ [this] { return sf_weight['T']; } });
//TEMP  
//TEMP    for (const auto& cut : {"T"}) {
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"NJet",                    .pfs={Stack,"JetHTMET",cut},                   .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"HTFine",                  .pfs={Stack,"JetHTMET",cut},                   .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"MET",                     .pfs={Stack,"JetHTMET",cut},                   .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"MR",                      .pfs={Stack,"JetHTMET",cut},                   .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"MTR",                     .pfs={Stack,"JetHTMET",cut},                   .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"R2",                      .pfs={Stack,"JetHTMET",cut},                   .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"RazorBins",               .pfs={Stack,"JetHTMET",cut},                   .cuts={},.draw=d,.opt=O_stk_d+"NoComb4",.ranges=r_Stk4});
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"HT",                      .pfs={Stack,"JetHTMET",cut},                   .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"HTJet1AK8Pt",             .pfs={Stack,"JetHTMET",cut},                   .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP      for (auto njet_bin : {"NJet45"}) {
//TEMP        sh.AddHistos(s+"evt",  { .fill=c+"NJetAK8",                 .pfs={Stack,"JetHTMET",cut,njet_bin},          .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP        sh.AddHistos(s+"evt",  { .fill=c+"HTFine",                  .pfs={Stack,"JetHTMET",cut,njet_bin},          .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP        sh.AddHistos(s+"evt",  { .fill=c+"MET",                     .pfs={Stack,"JetHTMET",cut,njet_bin},          .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP        sh.AddHistos(s+"evt",  { .fill=c+"MR",                      .pfs={Stack,"JetHTMET",cut,njet_bin},          .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP        sh.AddHistos(s+"evt",  { .fill=c+"MTR",                     .pfs={Stack,"JetHTMET",cut,njet_bin},          .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP        sh.AddHistos(s+"evt",  { .fill=c+"R2",                      .pfs={Stack,"JetHTMET",cut,njet_bin},          .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP        sh.AddHistos(s+"evt",  { .fill=c+"RazorBins",               .pfs={Stack,"JetHTMET",cut,njet_bin},          .cuts={},.draw=d,.opt=O_stk_d+"NoComb4",.ranges=r_Stk4});
//TEMP        sh.AddHistos(s+"evt",  { .fill=c+"HT",                      .pfs={Stack,"JetHTMET",cut,njet_bin},          .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP        sh.AddHistos(s+"evt",  { .fill=c+"HTJet1AK8Pt",             .pfs={Stack,"JetHTMET",cut,njet_bin},          .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP      }
//TEMP      // Ele or Muon
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"NJet",                    .pfs={Stack,"JetHTMET",cut,"Ele_Muon"},        .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"NJetAK8",                 .pfs={Stack,"JetHTMET",cut,"Ele_Muon"},        .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"HTFine",                  .pfs={Stack,"JetHTMET",cut,"Ele_Muon"},        .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"MET",                     .pfs={Stack,"JetHTMET",cut,"Ele_Muon"},        .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"MR",                      .pfs={Stack,"JetHTMET",cut,"Ele_Muon"},        .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"MTR",                     .pfs={Stack,"JetHTMET",cut,"Ele_Muon"},        .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"R2",                      .pfs={Stack,"JetHTMET",cut,"Ele_Muon"},        .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"RazorBins",               .pfs={Stack,"JetHTMET",cut,"Ele_Muon"},        .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"HT",                      .pfs={Stack,"JetHTMET",cut,"Ele_Muon"},        .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"HTJet1AK8Pt",             .pfs={Stack,"JetHTMET",cut,"Ele_Muon"},        .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP    }
//TEMP  
//TEMP    // N-1 plots
//TEMP    sh.AddHistos(s+"evt",  { .fill=c+"NJet",        .pfs={Stack,"JetHTMET","T_ExclNJet"},               .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP    sh.AddHistos(s+"evt",  { .fill=c+"MR",          .pfs={Stack,"JetHTMET","T_ExclMR"},                 .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP    sh.AddHistos(s+"evt",  { .fill=c+"MTR",         .pfs={Stack,"JetHTMET","T_ExclR2"},                 .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP    sh.AddHistos(s+"evt",  { .fill=c+"R2",          .pfs={Stack,"JetHTMET","T_ExclR2"},                 .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP    sh.AddHistos(s+"evt",  { .fill=c+"DeltaRWb",    .pfs={Stack,"JetHTMET","T"},                        .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP    sh.AddHistos(s+"evt",  { .fill=c+"MinDeltaPhi", .pfs={Stack,"JetHTMET","T_ExcldPhi"},               .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP    sh.AddHistos(s+"evt",  { .fill=c+"MinDeltaPhi", .pfs={Stack,"JetHTMET","T_ExcldPhiMT"},             .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP    sh.AddHistos(s+"evt",  { .fill=c+"DeltaPhi",    .pfs={Stack,"JetHTMET","T_ExcldPhi"},               .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP    sh.AddHistos(s+"evt",  { .fill=c+"DeltaPhi",    .pfs={Stack,"JetHTMET","T_ExcldPhiMT"},             .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP    sh.AddHistos(s+"evt",  { .fill=c+"MT",          .pfs={Stack,"JetHTMET","T_ExclMT"},                 .cuts={},.draw=d,.opt=O_stk_d+"NoComb3",.ranges=r_Stk4});
//TEMP    sh.AddHistos(s+"evt",  { .fill=c+"MT",          .pfs={Stack,"JetHTMET","T_ExcldPhiMT"},             .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP    for (auto njet_bin : {"NJet45"}) {
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"NEle",        .pfs={Stack,"JetHTMET","T_Excl1LepMT", njet_bin},   .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"NMu",         .pfs={Stack,"JetHTMET","T_Excl1LepMT", njet_bin},   .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"NLep",        .pfs={Stack,"JetHTMET","T_Excl1LepMT", njet_bin},   .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP  #if TOP == 0
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"NBTag",       .pfs={Stack,"JetHTMET","T_Excl1b",     njet_bin},   .cuts={},.draw=d,.opt=O_stk_d+"NoComb3",.ranges=r_Stk4});
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"NW",          .pfs={Stack,"JetHTMET","T_Excl1W",     njet_bin},   .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP      sh.AddHistos(s+"mW",   { .fill=c+"mWTau21",     .pfs={Stack,"JetHTMET","T_Excl1W",     njet_bin},   .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP  #else
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"NBTag",       .pfs={Stack,"JetHTMET","T_Excl1Top",   njet_bin},   .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"NTop",        .pfs={Stack,"JetHTMET","T_Excl1Top",   njet_bin},   .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP      sh.AddHistos(s+"mTop", { .fill=c+"mTopTau32",   .pfs={Stack,"JetHTMET","T_Excl1Top",   njet_bin},   .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP      sh.AddHistos(s+"MTop", { .fill=c+"MTopTau32",   .pfs={Stack,"JetHTMET","T_Excl1Top",   njet_bin},   .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP  #endif
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"DeltaRWb",    .pfs={Stack,"JetHTMET","T",            njet_bin},   .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"MinDeltaPhi", .pfs={Stack,"JetHTMET","T_ExcldPhi",   njet_bin},   .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"MinDeltaPhi", .pfs={Stack,"JetHTMET","T_ExcldPhiMT", njet_bin},   .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"DeltaPhi",    .pfs={Stack,"JetHTMET","T_ExcldPhi",   njet_bin},   .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"DeltaPhi",    .pfs={Stack,"JetHTMET","T_ExcldPhiMT", njet_bin},   .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"MT",          .pfs={Stack,"JetHTMET","T_ExclMT",     njet_bin},   .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"MT",          .pfs={Stack,"JetHTMET","T_ExcldPhiMT", njet_bin},   .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP    }
//TEMP    // Ele or Muon
//TEMP    sh.AddHistos(s+"evt",  { .fill=c+"NEle",        .pfs={Stack,"JetHTMET","T_Excl1LepMT", "Ele_Muon"}, .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP    sh.AddHistos(s+"evt",  { .fill=c+"NMu",         .pfs={Stack,"JetHTMET","T_Excl1LepMT", "Ele_Muon"}, .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP    sh.AddHistos(s+"evt",  { .fill=c+"NLep",        .pfs={Stack,"JetHTMET","T_Excl1LepMT", "Ele_Muon"}, .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP  #if TOP == 0
//TEMP    sh.AddHistos(s+"evt",  { .fill=c+"NBTag",       .pfs={Stack,"JetHTMET","T_Excl1b",     "Ele_Muon"}, .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP    sh.AddHistos(s+"evt",  { .fill=c+"NW",          .pfs={Stack,"JetHTMET","T_Excl1W",     "Ele_Muon"}, .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP    sh.AddHistos(s+"mW",   { .fill=c+"mWTau21",     .pfs={Stack,"JetHTMET","T_Excl1W",     "Ele_Muon"}, .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP  #else
//TEMP    sh.AddHistos(s+"evt",  { .fill=c+"NBTag",       .pfs={Stack,"JetHTMET","T_Excl1Top",   "Ele_Muon"}, .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP    sh.AddHistos(s+"evt",  { .fill=c+"NTop",        .pfs={Stack,"JetHTMET","T_Excl1Top",   "Ele_Muon"}, .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP    sh.AddHistos(s+"mTop", { .fill=c+"mTopTau32",   .pfs={Stack,"JetHTMET","T_Excl1Top",   "Ele_Muon"}, .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP    sh.AddHistos(s+"MTop", { .fill=c+"MTopTau32",   .pfs={Stack,"JetHTMET","T_Excl1Top",   "Ele_Muon"}, .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP  #endif
//TEMP    sh.AddHistos(s+"evt",  { .fill=c+"DeltaRWb",    .pfs={Stack,"JetHTMET","T",            "Ele_Muon"}, .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP    sh.AddHistos(s+"evt",  { .fill=c+"MinDeltaPhi", .pfs={Stack,"JetHTMET","T_ExcldPhi",   "Ele_Muon"}, .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP    sh.AddHistos(s+"evt",  { .fill=c+"MinDeltaPhi", .pfs={Stack,"JetHTMET","T_ExcldPhiMT", "Ele_Muon"}, .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP    sh.AddHistos(s+"evt",  { .fill=c+"DeltaPhi",    .pfs={Stack,"JetHTMET","T_ExcldPhi",   "Ele_Muon"}, .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP    sh.AddHistos(s+"evt",  { .fill=c+"DeltaPhi",    .pfs={Stack,"JetHTMET","T_ExcldPhiMT", "Ele_Muon"}, .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP    sh.AddHistos(s+"evt",  { .fill=c+"MT",          .pfs={Stack,"JetHTMET","T_ExclMT",     "Ele_Muon"}, .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP    sh.AddHistos(s+"evt",  { .fill=c+"MT",          .pfs={Stack,"JetHTMET","T_ExcldPhiMT", "Ele_Muon"}, .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP  
//TEMP    // Other
//TEMP  #if TOP == 0
//TEMP    sh.AddHistos(s+"evt",  { .fill=c+"HTFine",      .pfs={Stack,"JetHTMET","T_Excl1W"},                 .cuts={},.draw=d,.opt=o_stk_s,.ranges=r_Stk6});
//TEMP  #else
//TEMP    sh.AddHistos(s+"evt",  { .fill=c+"HTFine",      .pfs={Stack,"JetHTMET","T_Excl1Top"},               .cuts={},.draw=d,.opt=o_stk_s,.ranges=r_Stk6});
//TEMP  #endif
//TEMP  
//TEMP    // N-1 weights
//TEMP    sh.SetHistoWeights({ [this] { return w_nm1['T'][all_weights.size()+2]; } });
//TEMP  #if TOP == 0
//TEMP    sh.AddHistos("evt",  { .fill="NBTag",       .pfs={Stack,"JetHTMET","T_Excl1b",  "NoBTagSF"}, .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP  #endif
//TEMP    sh.AddHistos("evt",  { .fill="NJet",        .pfs={Stack,"JetHTMET","T_ExclNJet","NoBTagSF"}, .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP    sh.AddHistos("evt",  { .fill="HTFine",      .pfs={Stack,"JetHTMET","T",         "NoBTagSF"}, .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP    sh.AddHistos("evt",  { .fill="MET",         .pfs={Stack,"JetHTMET","T",         "NoBTagSF"}, .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP    sh.AddHistos("evt",  { .fill="MR",          .pfs={Stack,"JetHTMET","T",         "NoBTagSF"}, .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP    sh.AddHistos("evt",  { .fill="MTR",         .pfs={Stack,"JetHTMET","T",         "NoBTagSF"}, .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP    sh.AddHistos("evt",  { .fill="R2",          .pfs={Stack,"JetHTMET","T",         "NoBTagSF"}, .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP    sh.AddHistos("evt",  { .fill="RazorBins",   .pfs={Stack,"JetHTMET","T",         "NoBTagSF"}, .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP    sh.AddHistos("evt",  { .fill="R2_vs_MR",    .pfs={"Signals_Background","T",  "NoBTagSF"}, .cuts={},.draw="COLZ",.opt=o_1or2d_s+"Log",.ranges={}});
//TEMP    sh.SetHistoWeights({ [this] { return w_nm1['T'][all_weights.size()]; } });
//TEMP    sh.AddHistos("evt",  { .fill="NEle",        .pfs={Stack,"JetHTMET","T_Excl1LepMT","NoEleSF"}, .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP    sh.AddHistos("evt",  { .fill="NJet",        .pfs={Stack,"JetHTMET","T_ExclNJet",  "NoEleSF"}, .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP    sh.AddHistos("evt",  { .fill="HTFine",      .pfs={Stack,"JetHTMET","T",           "NoEleSF"}, .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP    sh.AddHistos("evt",  { .fill="MET",         .pfs={Stack,"JetHTMET","T",           "NoEleSF"}, .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP    sh.AddHistos("evt",  { .fill="MR",          .pfs={Stack,"JetHTMET","T",           "NoEleSF"}, .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP    sh.AddHistos("evt",  { .fill="MTR",         .pfs={Stack,"JetHTMET","T",           "NoEleSF"}, .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP    sh.AddHistos("evt",  { .fill="R2",          .pfs={Stack,"JetHTMET","T",           "NoEleSF"}, .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP    sh.AddHistos("evt",  { .fill="RazorBins",   .pfs={Stack,"JetHTMET","T",           "NoEleSF"}, .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP    sh.AddHistos("evt",  { .fill="R2_vs_MR",    .pfs={"Signals_Background","T",    "NoEleSF"}, .cuts={},.draw="COLZ",.opt=o_1or2d_s+"Log",.ranges={}});
//TEMP  
//TEMP    // -------------------------------------------------------------------------
//TEMP    //                          W enriched Region: W
//TEMP  
//TEMP  
//TEMP    sh.SetHistoWeights({ [this] { return sf_weight['W']; } });
//TEMP  
//TEMP    for (const auto& cut : {"W"}) {
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"NJet",                    .pfs={Stack,"JetHTMET",cut},                   .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"HTFine",                  .pfs={Stack,"JetHTMET",cut},                   .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"MET",                     .pfs={Stack,"JetHTMET",cut},                   .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"MR",                      .pfs={Stack,"JetHTMET",cut},                   .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"MTR",                     .pfs={Stack,"JetHTMET",cut},                   .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"R2",                      .pfs={Stack,"JetHTMET",cut},                   .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"RazorBins",               .pfs={Stack,"JetHTMET",cut},                   .cuts={},.draw=d,.opt=O_stk_d+"NoComb5",.ranges=r_Stk4});
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"HT",                      .pfs={Stack,"JetHTMET",cut},                   .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"HTJet1AK8Pt",             .pfs={Stack,"JetHTMET",cut},                   .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP      // Ele or Muon
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"NJet",                    .pfs={Stack,"JetHTMET",cut,"Ele_Muon"},        .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"NJetAK8",                 .pfs={Stack,"JetHTMET",cut,"Ele_Muon"},        .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"HTFine",                  .pfs={Stack,"JetHTMET",cut,"Ele_Muon"},        .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"MET",                     .pfs={Stack,"JetHTMET",cut,"Ele_Muon"},        .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"MR",                      .pfs={Stack,"JetHTMET",cut,"Ele_Muon"},        .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"MTR",                     .pfs={Stack,"JetHTMET",cut,"Ele_Muon"},        .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"R2",                      .pfs={Stack,"JetHTMET",cut,"Ele_Muon"},        .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"RazorBins",               .pfs={Stack,"JetHTMET",cut,"Ele_Muon"},        .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"HT",                      .pfs={Stack,"JetHTMET",cut,"Ele_Muon"},        .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"HTJet1AK8Pt",             .pfs={Stack,"JetHTMET",cut,"Ele_Muon"},        .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP      for (auto njet_bin : {"NJet45"}) {
//TEMP        sh.AddHistos(s+"evt",  { .fill=c+"NJetAK8",                 .pfs={Stack,"JetHTMET",cut,njet_bin},          .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP        sh.AddHistos(s+"evt",  { .fill=c+"HTFine",                  .pfs={Stack,"JetHTMET",cut,njet_bin},          .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP        sh.AddHistos(s+"evt",  { .fill=c+"MET",                     .pfs={Stack,"JetHTMET",cut,njet_bin},          .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP        sh.AddHistos(s+"evt",  { .fill=c+"MR",                      .pfs={Stack,"JetHTMET",cut,njet_bin},          .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP        sh.AddHistos(s+"evt",  { .fill=c+"MTR",                     .pfs={Stack,"JetHTMET",cut,njet_bin},          .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP        sh.AddHistos(s+"evt",  { .fill=c+"R2",                      .pfs={Stack,"JetHTMET",cut,njet_bin},          .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP        sh.AddHistos(s+"evt",  { .fill=c+"RazorBins",               .pfs={Stack,"JetHTMET",cut,njet_bin},          .cuts={},.draw=d,.opt=O_stk_d+"NoComb5",.ranges=r_Stk4});
//TEMP        sh.AddHistos(s+"evt",  { .fill=c+"HT",                      .pfs={Stack,"JetHTMET",cut,njet_bin},          .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP        sh.AddHistos(s+"evt",  { .fill=c+"HTJet1AK8Pt",             .pfs={Stack,"JetHTMET",cut,njet_bin},          .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP      }
//TEMP    }
//TEMP  
//TEMP    // N-1 plots
//TEMP    sh.AddHistos(s+"evt",  { .fill=c+"NJet",        .pfs={Stack,"JetHTMET","W_ExclNJet"},             .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP    sh.AddHistos(s+"evt",  { .fill=c+"MR",          .pfs={Stack,"JetHTMET","W_ExclMR"},               .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP    sh.AddHistos(s+"evt",  { .fill=c+"MTR",         .pfs={Stack,"JetHTMET","W_ExclR2"},               .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP    sh.AddHistos(s+"evt",  { .fill=c+"R2",          .pfs={Stack,"JetHTMET","W_ExclR2"},               .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP    sh.AddHistos(s+"evt",  { .fill=c+"MinDeltaPhi", .pfs={Stack,"JetHTMET","W_ExcldPhi"},             .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP    sh.AddHistos(s+"evt",  { .fill=c+"MinDeltaPhi", .pfs={Stack,"JetHTMET","W_ExcldPhiMT"},           .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP    sh.AddHistos(s+"evt",  { .fill=c+"DeltaPhi",    .pfs={Stack,"JetHTMET","W_ExcldPhi"},             .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP    sh.AddHistos(s+"evt",  { .fill=c+"DeltaPhi",    .pfs={Stack,"JetHTMET","W_ExcldPhiMT"},           .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP    sh.AddHistos(s+"evt",  { .fill=c+"MT",          .pfs={Stack,"JetHTMET","W_ExclMT"},               .cuts={},.draw=d,.opt=O_stk_d+"NoComb5",.ranges=r_Stk6});
//TEMP    sh.AddHistos(s+"evt",  { .fill=c+"MT",          .pfs={Stack,"JetHTMET","W_ExcldPhiMT"},           .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP    for (auto njet_bin : {"NJet45"}) {
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"NEle",        .pfs={Stack,"JetHTMET","W_Excl1LepMT", njet_bin}, .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"NMu",         .pfs={Stack,"JetHTMET","W_Excl1LepMT", njet_bin}, .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"NLep",        .pfs={Stack,"JetHTMET","W_Excl1LepMT", njet_bin}, .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"NLooseBTag",  .pfs={Stack,"JetHTMET","W_Excl0b",     njet_bin}, .cuts={},.draw=d,.opt=O_stk_d+"NoComb3",.ranges=r_Stk4});
//TEMP  #if TOP == 0
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"NmW",         .pfs={Stack,"JetHTMET","W_Excl1mW",    njet_bin}, .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP      sh.AddHistos(s+"mW",   { .fill=c+"mWTau21",     .pfs={Stack,"JetHTMET","W_Excl1mW",    njet_bin}, .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP  #else
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"NmTop",       .pfs={Stack,"JetHTMET","W_Excl1mTop",  njet_bin}, .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP      sh.AddHistos(s+"mTop", { .fill=c+"mTopTau32",   .pfs={Stack,"JetHTMET","W_Excl1mTop",  njet_bin}, .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP  #endif
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"MinDeltaPhi", .pfs={Stack,"JetHTMET","W_ExcldPhi",   njet_bin}, .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"MinDeltaPhi", .pfs={Stack,"JetHTMET","W_ExcldPhiMT", njet_bin}, .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"DeltaPhi",    .pfs={Stack,"JetHTMET","W_ExcldPhi",   njet_bin}, .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"DeltaPhi",    .pfs={Stack,"JetHTMET","W_ExcldPhiMT", njet_bin}, .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"MT",          .pfs={Stack,"JetHTMET","W_ExclMT",     njet_bin}, .cuts={},.draw=d,.opt=O_stk_d+"NoComb5",.ranges=r_Stk6});
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"MT",          .pfs={Stack,"JetHTMET","W_ExcldPhiMT", njet_bin}, .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP    }
//TEMP    // Ele or Muon
//TEMP    sh.AddHistos(s+"evt",  { .fill=c+"NJet",        .pfs={Stack,"JetHTMET","W_ExclNJet",   "Ele_Muon"}, .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP    sh.AddHistos(s+"evt",  { .fill=c+"MR",          .pfs={Stack,"JetHTMET","W_ExclMR",     "Ele_Muon"}, .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP    sh.AddHistos(s+"evt",  { .fill=c+"MTR",         .pfs={Stack,"JetHTMET","W_ExclR2",     "Ele_Muon"}, .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP    sh.AddHistos(s+"evt",  { .fill=c+"R2",          .pfs={Stack,"JetHTMET","W_ExclR2",     "Ele_Muon"}, .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP    sh.AddHistos(s+"evt",  { .fill=c+"NLooseBTag",  .pfs={Stack,"JetHTMET","W_Excl0b",     "Ele_Muon"}, .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP  #if TOP == 0
//TEMP    sh.AddHistos(s+"evt",  { .fill=c+"NmW",         .pfs={Stack,"JetHTMET","W_Excl1mW",    "Ele_Muon"}, .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP    sh.AddHistos(s+"mW",   { .fill=c+"mWTau21",     .pfs={Stack,"JetHTMET","W_Excl1mW",    "Ele_Muon"}, .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP  #else
//TEMP    sh.AddHistos(s+"evt",  { .fill=c+"NmTop",       .pfs={Stack,"JetHTMET","W_Excl1mTop",  "Ele_Muon"}, .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP    sh.AddHistos(s+"mTop", { .fill=c+"mTopTau32",   .pfs={Stack,"JetHTMET","W_Excl1mTop",  "Ele_Muon"}, .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP  #endif
//TEMP    sh.AddHistos(s+"evt",  { .fill=c+"MinDeltaPhi", .pfs={Stack,"JetHTMET","W_ExcldPhi",   "Ele_Muon"}, .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP    sh.AddHistos(s+"evt",  { .fill=c+"MinDeltaPhi", .pfs={Stack,"JetHTMET","W_ExcldPhiMT", "Ele_Muon"}, .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP    sh.AddHistos(s+"evt",  { .fill=c+"DeltaPhi",    .pfs={Stack,"JetHTMET","W_ExcldPhi",   "Ele_Muon"}, .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP    sh.AddHistos(s+"evt",  { .fill=c+"DeltaPhi",    .pfs={Stack,"JetHTMET","W_ExcldPhiMT", "Ele_Muon"}, .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP    sh.AddHistos(s+"evt",  { .fill=c+"MT",          .pfs={Stack,"JetHTMET","W_ExclMT",     "Ele_Muon"}, .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP    sh.AddHistos(s+"evt",  { .fill=c+"MT",          .pfs={Stack,"JetHTMET","W_ExcldPhiMT", "Ele_Muon"}, .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP  
//TEMP    // Other
//TEMP  #if TOP == 0
//TEMP    sh.AddHistos(s+"evt",  { .fill=c+"HTFine",      .pfs={Stack,"JetHTMET","W_Excl1mW"},              .cuts={},.draw=d,.opt=o_stk_s,.ranges=r_Stk6});
//TEMP  #else
//TEMP    sh.AddHistos(s+"evt",  { .fill=c+"HTFine",      .pfs={Stack,"JetHTMET","W_Excl1mTop"},            .cuts={},.draw=d,.opt=o_stk_s,.ranges=r_Stk6});
//TEMP  #endif
//TEMP  
//TEMP    // N-1 weights
//TEMP    sh.SetHistoWeights({ [this] { return w_nm1['W'][all_weights.size()+2]; } });
//TEMP    sh.AddHistos("evt",  { .fill="NLooseBTag",  .pfs={Stack,"JetHTMET","W_Excl0b",  "NoBTagSF"}, .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP    sh.AddHistos("evt",  { .fill="NJet",        .pfs={Stack,"JetHTMET","W_ExclNJet","NoBTagSF"}, .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP    sh.AddHistos("evt",  { .fill="HTFine",      .pfs={Stack,"JetHTMET","W",         "NoBTagSF"}, .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP    sh.AddHistos("evt",  { .fill="MET",         .pfs={Stack,"JetHTMET","W",         "NoBTagSF"}, .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP    sh.AddHistos("evt",  { .fill="MR",          .pfs={Stack,"JetHTMET","W",         "NoBTagSF"}, .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP    sh.AddHistos("evt",  { .fill="MTR",         .pfs={Stack,"JetHTMET","W",         "NoBTagSF"}, .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP    sh.AddHistos("evt",  { .fill="R2",          .pfs={Stack,"JetHTMET","W",         "NoBTagSF"}, .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP    sh.AddHistos("evt",  { .fill="RazorBins",   .pfs={Stack,"JetHTMET","W",         "NoBTagSF"}, .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP    sh.AddHistos("evt",  { .fill="R2_vs_MR",    .pfs={"Signals_Background","W",  "NoBTagSF"}, .cuts={},.draw="COLZ",.opt=o_1or2d_s+"Log",.ranges={}});
//TEMP    sh.SetHistoWeights({ [this] { return w_nm1['W'][all_weights.size()]; } });
//TEMP    sh.AddHistos("evt",  { .fill="NEle",        .pfs={Stack,"JetHTMET","W_Excl1LepMT","NoEleSF"}, .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP    sh.AddHistos("evt",  { .fill="NJet",        .pfs={Stack,"JetHTMET","W_ExclNJet",  "NoEleSF"}, .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP    sh.AddHistos("evt",  { .fill="HTFine",      .pfs={Stack,"JetHTMET","W",           "NoEleSF"}, .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP    sh.AddHistos("evt",  { .fill="MET",         .pfs={Stack,"JetHTMET","W",           "NoEleSF"}, .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP    sh.AddHistos("evt",  { .fill="MR",          .pfs={Stack,"JetHTMET","W",           "NoEleSF"}, .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP    sh.AddHistos("evt",  { .fill="MTR",         .pfs={Stack,"JetHTMET","W",           "NoEleSF"}, .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP    sh.AddHistos("evt",  { .fill="R2",          .pfs={Stack,"JetHTMET","W",           "NoEleSF"}, .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP    sh.AddHistos("evt",  { .fill="RazorBins",   .pfs={Stack,"JetHTMET","W",           "NoEleSF"}, .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP    sh.AddHistos("evt",  { .fill="R2_vs_MR",    .pfs={"Signals_Background","W",    "NoEleSF"}, .cuts={},.draw="COLZ",.opt=o_1or2d_s+"Log",.ranges={}});
//TEMP  
//TEMP    // -------------------------------------------------------------------------
//TEMP    //                      1 Lepton Invisible region: L
//TEMP  
//TEMP    // Same region but using veto leptons
//TEMP    sh.SetHistoWeights({ [this] { return sf_weight['L']; } });
//TEMP  
//TEMP    for (const auto& cut : {"L"}) {
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"NJet",                    .pfs={Stack,"JetHTMET",cut},                   .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"HTFine",                  .pfs={Stack,"JetHTMET",cut},                   .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"MET1vl",                  .pfs={Stack,"JetHTMET",cut},                   .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"MR",                      .pfs={Stack,"JetHTMET",cut},                   .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"MTR1vl",                  .pfs={Stack,"JetHTMET",cut},                   .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"R21vl",                   .pfs={Stack,"JetHTMET",cut},                   .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"Razor1vlBins",            .pfs={Stack,"JetHTMET",cut},                   .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"HT",                      .pfs={Stack,"JetHTMET",cut},                   .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"HTJet1AK8Pt",             .pfs={Stack,"JetHTMET",cut},                   .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP      // Ele or Muon
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"NJet",                    .pfs={Stack,"JetHTMET",cut,"Ele_or_Muon"},        .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"NJetAK8",                 .pfs={Stack,"JetHTMET",cut,"Ele_or_Muon"},        .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"HTFine",                  .pfs={Stack,"JetHTMET",cut,"Ele_or_Muon"},        .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"MET1vl",                  .pfs={Stack,"JetHTMET",cut,"Ele_or_Muon"},        .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"MR",                      .pfs={Stack,"JetHTMET",cut,"Ele_or_Muon"},        .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"MTR1vl",                  .pfs={Stack,"JetHTMET",cut,"Ele_or_Muon"},        .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"R21vl",                   .pfs={Stack,"JetHTMET",cut,"Ele_or_Muon"},        .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"Razor1vlBins",            .pfs={Stack,"JetHTMET",cut,"Ele_or_Muon"},        .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"HT",                      .pfs={Stack,"JetHTMET",cut,"Ele_or_Muon"},        .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"HTJet1AK8Pt",             .pfs={Stack,"JetHTMET",cut,"Ele_or_Muon"},        .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP      for (auto njet_bin : {"NJet45"}) {
//TEMP        sh.AddHistos(s+"evt",  { .fill=c+"NJetAK8",                 .pfs={Stack,"JetHTMET",cut,njet_bin},          .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP        sh.AddHistos(s+"evt",  { .fill=c+"HTFine",                  .pfs={Stack,"JetHTMET",cut,njet_bin},          .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP        sh.AddHistos(s+"evt",  { .fill=c+"MET1vl",                  .pfs={Stack,"JetHTMET",cut,njet_bin},          .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP        sh.AddHistos(s+"evt",  { .fill=c+"MR",                      .pfs={Stack,"JetHTMET",cut,njet_bin},          .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP        sh.AddHistos(s+"evt",  { .fill=c+"MTR1vl",                  .pfs={Stack,"JetHTMET",cut,njet_bin},          .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP        sh.AddHistos(s+"evt",  { .fill=c+"R21vl",                   .pfs={Stack,"JetHTMET",cut,njet_bin},          .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP        sh.AddHistos(s+"evt",  { .fill=c+"Razor1vlBins",            .pfs={Stack,"JetHTMET",cut,njet_bin},          .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP        sh.AddHistos(s+"evt",  { .fill=c+"HT",                      .pfs={Stack,"JetHTMET",cut,njet_bin},          .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP        sh.AddHistos(s+"evt",  { .fill=c+"HTJet1AK8Pt",             .pfs={Stack,"JetHTMET",cut,njet_bin},          .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP      }
//TEMP    }
//TEMP  
//TEMP    // N-1 plots
//TEMP    sh.AddHistos(s+"evt",  { .fill=c+"NJet",          .pfs={Stack,"JetHTMET","L_ExclNJet"},             .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP    sh.AddHistos(s+"evt",  { .fill=c+"MR",            .pfs={Stack,"JetHTMET","L_ExclMR"},               .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP    sh.AddHistos(s+"evt",  { .fill=c+"MTR1vl",        .pfs={Stack,"JetHTMET","L_ExclR2"},               .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP    sh.AddHistos(s+"evt",  { .fill=c+"R21vl",         .pfs={Stack,"JetHTMET","L_ExclR2"},               .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP    sh.AddHistos(s+"evt",  { .fill=c+"MinDeltaPhi1vl",.pfs={Stack,"JetHTMET","L_ExcldPhi"},             .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP    sh.AddHistos(s+"evt",  { .fill=c+"MinDeltaPhi1vl",.pfs={Stack,"JetHTMET","L_ExcldPhiMT"},           .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP    sh.AddHistos(s+"evt",  { .fill=c+"DeltaPhi",      .pfs={Stack,"JetHTMET","L_ExcldPhi"},             .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP    sh.AddHistos(s+"evt",  { .fill=c+"DeltaPhi",      .pfs={Stack,"JetHTMET","L_ExcldPhiMT"},           .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP    sh.AddHistos(s+"evt",  { .fill=c+"MT",            .pfs={Stack,"JetHTMET","L_ExclMT"},               .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP    sh.AddHistos(s+"evt",  { .fill=c+"MT",            .pfs={Stack,"JetHTMET","L_ExcldPhiMT"},           .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP    for (auto njet_bin : {"NJet45"}) {
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"NEle",          .pfs={Stack,"JetHTMET","L_ExclR21LepMT", njet_bin}, .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"NMu",           .pfs={Stack,"JetHTMET","L_ExclR21LepMT", njet_bin}, .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"NLep",          .pfs={Stack,"JetHTMET","L_ExclR21LepMT", njet_bin}, .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"NLooseBTag",    .pfs={Stack,"JetHTMET","L_Excl0b",       njet_bin}, .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP  #if TOP == 0
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"NW",            .pfs={Stack,"JetHTMET","L_Excl1mW",        njet_bin}, .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"NmW",           .pfs={Stack,"JetHTMET","L_Excl1mW",        njet_bin}, .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP      sh.AddHistos(s+"mW",   { .fill=c+"mWTau21",       .pfs={Stack,"JetHTMET","L_Excl1mW",        njet_bin}, .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP  #else
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"NTop",          .pfs={Stack,"JetHTMET","L_Excl1mTop",      njet_bin}, .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"NmTop",         .pfs={Stack,"JetHTMET","L_Excl1mTop",      njet_bin}, .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP      sh.AddHistos(s+"mTop", { .fill=c+"mTopTau32",     .pfs={Stack,"JetHTMET","L_Excl1mTop",      njet_bin}, .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP  #endif
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"MinDeltaPhi1vl",.pfs={Stack,"JetHTMET","L_ExcldPhi",   njet_bin}, .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"MinDeltaPhi1vl",.pfs={Stack,"JetHTMET","L_ExcldPhiMT", njet_bin}, .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"DeltaPhi",      .pfs={Stack,"JetHTMET","L_ExcldPhi",   njet_bin}, .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"DeltaPhi",      .pfs={Stack,"JetHTMET","L_ExcldPhiMT", njet_bin}, .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"MT",            .pfs={Stack,"JetHTMET","L_ExclMT",     njet_bin}, .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"MT",            .pfs={Stack,"JetHTMET","L_ExcldPhiMT", njet_bin}, .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP    }
//TEMP    // Ele or Muon
//TEMP    sh.AddHistos(s+"evt",  { .fill=c+"NJet",          .pfs={Stack,"JetHTMET","L_ExclNJet",   "Ele_or_Muon"}, .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP    sh.AddHistos(s+"evt",  { .fill=c+"MR",            .pfs={Stack,"JetHTMET","L_ExclMR",     "Ele_or_Muon"}, .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP    sh.AddHistos(s+"evt",  { .fill=c+"MTR1vl",        .pfs={Stack,"JetHTMET","L_ExclR2",     "Ele_or_Muon"}, .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP    sh.AddHistos(s+"evt",  { .fill=c+"R21vl",         .pfs={Stack,"JetHTMET","L_ExclR2",     "Ele_or_Muon"}, .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP    sh.AddHistos(s+"evt",  { .fill=c+"NLooseBTag",    .pfs={Stack,"JetHTMET","L_Excl0b",     "Ele_or_Muon"}, .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP  #if TOP == 0
//TEMP    sh.AddHistos(s+"evt",  { .fill=c+"NW",            .pfs={Stack,"JetHTMET","L_Excl1mW",    "Ele_or_Muon"}, .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP    sh.AddHistos(s+"evt",  { .fill=c+"NmW",           .pfs={Stack,"JetHTMET","L_Excl1mW",    "Ele_or_Muon"}, .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP    sh.AddHistos(s+"mW",   { .fill=c+"mWTau21",       .pfs={Stack,"JetHTMET","L_Excl1mW",    "Ele_or_Muon"}, .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP  #else
//TEMP    sh.AddHistos(s+"evt",  { .fill=c+"NTop",          .pfs={Stack,"JetHTMET","L_Excl1mTop",  "Ele_or_Muon"}, .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP    sh.AddHistos(s+"evt",  { .fill=c+"NmTop",         .pfs={Stack,"JetHTMET","L_Excl1mTop",  "Ele_or_Muon"}, .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP    sh.AddHistos(s+"mTop", { .fill=c+"mTopTau32",     .pfs={Stack,"JetHTMET","L_Excl1mTop",  "Ele_or_Muon"}, .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP  #endif
//TEMP    sh.AddHistos(s+"evt",  { .fill=c+"MinDeltaPhi1vl",.pfs={Stack,"JetHTMET","L_ExcldPhi",   "Ele_or_Muon"}, .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP    sh.AddHistos(s+"evt",  { .fill=c+"MinDeltaPhi1vl",.pfs={Stack,"JetHTMET","L_ExcldPhiMT", "Ele_or_Muon"}, .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP    sh.AddHistos(s+"evt",  { .fill=c+"DeltaPhi",      .pfs={Stack,"JetHTMET","L_ExcldPhi",   "Ele_or_Muon"}, .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP    sh.AddHistos(s+"evt",  { .fill=c+"DeltaPhi",      .pfs={Stack,"JetHTMET","L_ExcldPhiMT", "Ele_or_Muon"}, .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP    sh.AddHistos(s+"evt",  { .fill=c+"MT",            .pfs={Stack,"JetHTMET","L_ExclMT",     "Ele_or_Muon"}, .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP    sh.AddHistos(s+"evt",  { .fill=c+"MT",            .pfs={Stack,"JetHTMET","L_ExcldPhiMT", "Ele_or_Muon"}, .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP  
//TEMP    // -------------------------------------------------------------------------
//TEMP    //                          Z enriched Region: Z
//TEMP  
//TEMP    sh.SetHistoWeights({ [this] { return sf_weight['Z']; } });
//TEMP  
//TEMP    for (const auto& cut : {"Z"}) {
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"NJet",                    .pfs={Stack,"JetHTMET",cut},                   .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"HTFine",                  .pfs={Stack,"JetHTMET",cut},                   .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"METll",                   .pfs={Stack,"JetHTMET",cut},                   .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"MR",                      .pfs={Stack,"JetHTMET",cut},                   .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"MTRll",                   .pfs={Stack,"JetHTMET",cut},                   .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"R2ll",                    .pfs={Stack,"JetHTMET",cut},                   .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"RazorllBins",             .pfs={Stack,"JetHTMET",cut},                   .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"HT",                      .pfs={Stack,"JetHTMET",cut},                   .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"HTJet1AK8Pt",             .pfs={Stack,"JetHTMET",cut},                   .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP      // Ele or Muon
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"NJet",                    .pfs={Stack,"JetHTMET",cut,"2Ele_2Muon"},      .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"NJetAK8",                 .pfs={Stack,"JetHTMET",cut,"2Ele_2Muon"},      .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"HTFine",                  .pfs={Stack,"JetHTMET",cut,"2Ele_2Muon"},      .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"METll",                   .pfs={Stack,"JetHTMET",cut,"2Ele_2Muon"},      .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"MR",                      .pfs={Stack,"JetHTMET",cut,"2Ele_2Muon"},      .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"MTRll",                   .pfs={Stack,"JetHTMET",cut,"2Ele_2Muon"},      .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"R2ll",                    .pfs={Stack,"JetHTMET",cut,"2Ele_2Muon"},      .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"RazorllBins",             .pfs={Stack,"JetHTMET",cut,"2Ele_2Muon"},      .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"HT",                      .pfs={Stack,"JetHTMET",cut,"2Ele_2Muon"},      .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"HTJet1AK8Pt",             .pfs={Stack,"JetHTMET",cut,"2Ele_2Muon"},      .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP      for (auto njet_bin : {"NJet45"}) {
//TEMP        sh.AddHistos(s+"evt",  { .fill=c+"NJetAK8",                 .pfs={Stack,"JetHTMET",cut,njet_bin},          .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP        sh.AddHistos(s+"evt",  { .fill=c+"HTFine",                  .pfs={Stack,"JetHTMET",cut,njet_bin},          .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP        sh.AddHistos(s+"evt",  { .fill=c+"METll",                   .pfs={Stack,"JetHTMET",cut,njet_bin},          .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP        sh.AddHistos(s+"evt",  { .fill=c+"MR",                      .pfs={Stack,"JetHTMET",cut,njet_bin},          .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP        sh.AddHistos(s+"evt",  { .fill=c+"MTRll",                   .pfs={Stack,"JetHTMET",cut,njet_bin},          .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP        sh.AddHistos(s+"evt",  { .fill=c+"R2ll",                    .pfs={Stack,"JetHTMET",cut,njet_bin},          .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP        sh.AddHistos(s+"evt",  { .fill=c+"RazorllBins",             .pfs={Stack,"JetHTMET",cut,njet_bin},          .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP        sh.AddHistos(s+"evt",  { .fill=c+"HT",                      .pfs={Stack,"JetHTMET",cut,njet_bin},          .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP        sh.AddHistos(s+"evt",  { .fill=c+"HTJet1AK8Pt",             .pfs={Stack,"JetHTMET",cut,njet_bin},          .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP      }
//TEMP    }
//TEMP  
//TEMP    // N-1 plots
//TEMP    sh.AddHistos(s+"evt",  { .fill=c+"NJet",          .pfs={Stack,"JetHTMET","Z_ExclNJet"},                 .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP    sh.AddHistos(s+"evt",  { .fill=c+"MR",            .pfs={Stack,"JetHTMET","Z_ExclMR"},                   .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP    sh.AddHistos(s+"evt",  { .fill=c+"MTRll",         .pfs={Stack,"JetHTMET","Z_ExclR2ll"},                 .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP    sh.AddHistos(s+"evt",  { .fill=c+"R2ll",          .pfs={Stack,"JetHTMET","Z_ExclR2ll"},                 .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP    sh.AddHistos(s+"evt",  { .fill=c+"MinDeltaPhi",   .pfs={Stack,"JetHTMET","Z_ExcldPhi"},                 .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP    sh.AddHistos(s+"evt",  { .fill=c+"MinDeltaPhill", .pfs={Stack,"JetHTMET","Z_ExcldPhi"},                 .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP    sh.AddHistos(s+"evt",  { .fill=c+"DeltaPhi",      .pfs={Stack,"JetHTMET","Z_ExcldPhi"},                 .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP    sh.AddHistos(s+"evt",  { .fill=c+"DeltaPhiLLMET", .pfs={Stack,"JetHTMET","Z"},                          .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP    sh.AddHistos(s+"evt",  { .fill=c+"DeltaPhiLLMET", .pfs={Stack,"JetHTMET","Z_ExcldPhi"},                 .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP    sh.AddHistos(s+"evt",  { .fill=c+"DeltaPhiLLJet", .pfs={Stack,"JetHTMET","Z"},                          .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP    sh.AddHistos(s+"evt",  { .fill=c+"DeltaPhiLLJet", .pfs={Stack,"JetHTMET","Z_ExcldPhi"},                 .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP    sh.AddHistos(s+"evt",  { .fill=c+"Mll",           .pfs={Stack,"JetHTMET","Z_ExclMll"},                  .cuts={},.draw=d,.opt=o_stk_d,.ranges={0,0, 1.01e-2,1e6, 0.3,0.86}});
//TEMP    sh.AddHistos(s+"evt",  { .fill=c+"Mll",           .pfs={Stack,"JetHTMET","Z_ExcldPhiMll"},              .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP    for (auto njet_bin : {"NJet45"}) {
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"NEle",          .pfs={Stack,"JetHTMET","Z_ExclR2ll2Lep",njet_bin},    .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"NMu",           .pfs={Stack,"JetHTMET","Z_ExclR2ll2Lep",njet_bin},    .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"NLep",          .pfs={Stack,"JetHTMET","Z_ExclR2ll2Lep",njet_bin},    .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"NLooseBTag",    .pfs={Stack,"JetHTMET","Z",                njet_bin}, .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"NBTag",         .pfs={Stack,"JetHTMET","Z",                njet_bin}, .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP  #if TOP == 0
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"NW",            .pfs={Stack,"JetHTMET","Z_Excl1mW",        njet_bin}, .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"NmW",           .pfs={Stack,"JetHTMET","Z_Excl1mW",        njet_bin}, .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP      sh.AddHistos(s+"mW",   { .fill=c+"mWTau21",       .pfs={Stack,"JetHTMET","Z_Excl1mW",        njet_bin}, .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP  #else
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"NTop",          .pfs={Stack,"JetHTMET","Z_Excl1MTop",      njet_bin}, .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"NMTop",         .pfs={Stack,"JetHTMET","Z_Excl1MTop",      njet_bin}, .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP      sh.AddHistos(s+"MTop", { .fill=c+"MTopTau32",     .pfs={Stack,"JetHTMET","Z_Excl1MTop",      njet_bin}, .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP  #endif
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"MinDeltaPhi",   .pfs={Stack,"JetHTMET","Z_ExcldPhi",       njet_bin}, .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"MinDeltaPhill", .pfs={Stack,"JetHTMET","Z_ExcldPhi",       njet_bin}, .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"DeltaPhi",      .pfs={Stack,"JetHTMET","Z_ExcldPhi",       njet_bin}, .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"Mll",           .pfs={Stack,"JetHTMET","Z_ExclMll",        njet_bin}, .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP    }
//TEMP    // Ele or Muon
//TEMP    sh.AddHistos(s+"evt",  { .fill=c+"NJet",          .pfs={Stack,"JetHTMET","Z_ExclNJet",   "2Ele_2Muon"},   .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP    sh.AddHistos(s+"evt",  { .fill=c+"MR",            .pfs={Stack,"JetHTMET","Z_ExclMR","2Ele_2Muon"},        .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP    sh.AddHistos(s+"evt",  { .fill=c+"MTRll",         .pfs={Stack,"JetHTMET","Z_ExclR2ll","2Ele_2Muon"},      .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP    sh.AddHistos(s+"evt",  { .fill=c+"R2ll",          .pfs={Stack,"JetHTMET","Z_ExclR2ll","2Ele_2Muon"},      .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP    sh.AddHistos(s+"evt",  { .fill=c+"NLooseBTag",    .pfs={Stack,"JetHTMET","Z",            "2Ele_2Muon"},   .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP    sh.AddHistos(s+"evt",  { .fill=c+"NBTag",         .pfs={Stack,"JetHTMET","Z",            "2Ele_2Muon"},   .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP  #if TOP == 0
//TEMP    sh.AddHistos(s+"evt",  { .fill=c+"NW",            .pfs={Stack,"JetHTMET","Z_Excl1mW",    "2Ele_2Muon"},   .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP    sh.AddHistos(s+"evt",  { .fill=c+"NmW",           .pfs={Stack,"JetHTMET","Z_Excl1mW",    "2Ele_2Muon"},   .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP    sh.AddHistos(s+"mW",   { .fill=c+"mWTau21",       .pfs={Stack,"JetHTMET","Z_Excl1mW",    "2Ele_2Muon"},   .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP  #else
//TEMP    sh.AddHistos(s+"evt",  { .fill=c+"NTop",          .pfs={Stack,"JetHTMET","Z_Excl1MTop",  "2Ele_2Muon"},   .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP    sh.AddHistos(s+"evt",  { .fill=c+"NMTop",         .pfs={Stack,"JetHTMET","Z_Excl1MTop",  "2Ele_2Muon"},   .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP    sh.AddHistos(s+"MTop", { .fill=c+"MTopTau32",     .pfs={Stack,"JetHTMET","Z_Excl1MTop",  "2Ele_2Muon"},   .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP  #endif
//TEMP    sh.AddHistos(s+"evt",  { .fill=c+"MinDeltaPhi",   .pfs={Stack,"JetHTMET","Z_ExcldPhi","2Ele_2Muon"},   .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP    sh.AddHistos(s+"evt",  { .fill=c+"MinDeltaPhill", .pfs={Stack,"JetHTMET","Z_ExcldPhi","2Ele_2Muon"},   .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP    sh.AddHistos(s+"evt",  { .fill=c+"DeltaPhi",      .pfs={Stack,"JetHTMET","Z_ExcldPhi","2Ele_2Muon"},   .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP    sh.AddHistos(s+"evt",  { .fill=c+"Mll",           .pfs={Stack,"JetHTMET","Z_ExclMll", "2Ele_2Muon"},   .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP  
//TEMP    // Other
//TEMP  #if TOP == 0
//TEMP    sh.AddHistos(s+"evt",  { .fill=c+"HTFine",      .pfs={Stack,"JetHTMET","Z_Excl1mW"},                      .cuts={},.draw=d,.opt=o_stk_s,.ranges=r_Stk6});
//TEMP  #else
//TEMP    sh.AddHistos(s+"evt",  { .fill=c+"HTFine",      .pfs={Stack,"JetHTMET","Z_Excl1MTop"},                    .cuts={},.draw=d,.opt=o_stk_s,.ranges=r_Stk6});
//TEMP  #endif
//TEMP  
//TEMP    // N-1 weights
//TEMP    sh.SetHistoWeights({ [this] { return w_nm1['Z'][all_weights.size()]; } });
//TEMP    sh.AddHistos("evt",  { .fill="NEle",        .pfs={Stack,"JetHTMET","Z_ExclR2ll2Lep","NoEleSF"}, .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP    sh.AddHistos("evt",  { .fill="NJet",        .pfs={Stack,"JetHTMET","Z_ExclNJet",    "NoEleSF"}, .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP    sh.AddHistos("evt",  { .fill="HTFine",      .pfs={Stack,"JetHTMET","Z",             "NoEleSF"}, .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP    sh.AddHistos("evt",  { .fill="METll",       .pfs={Stack,"JetHTMET","Z",             "NoEleSF"}, .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP    sh.AddHistos("evt",  { .fill="MR",          .pfs={Stack,"JetHTMET","Z",             "NoEleSF"}, .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP    sh.AddHistos("evt",  { .fill="MTRll",       .pfs={Stack,"JetHTMET","Z",             "NoEleSF"}, .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP    sh.AddHistos("evt",  { .fill="R2ll",        .pfs={Stack,"JetHTMET","Z",             "NoEleSF"}, .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP    sh.AddHistos("evt",  { .fill="RazorllBins", .pfs={Stack,"JetHTMET","Z",             "NoEleSF"}, .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP    sh.AddHistos("evt",  { .fill="R2_vs_MR",    .pfs={"Signals_Background","Z",      "NoEleSF"}, .cuts={},.draw="COLZ",.opt=o_1or2d_s+"Log",.ranges={}});
//TEMP  
//TEMP  
//TEMP  
//TEMP  
//TEMP  #if TOP == 0
//TEMP    // Same region but with mass-tag
//TEMP    sh.SetHistoWeights({ [this] { return sf_weight['z']; } });
//TEMP  
//TEMP    for (const auto& cut : {"z"}) {
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"NJet",                    .pfs={Stack,"JetHTMET",cut},                   .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"HTFine",                  .pfs={Stack,"JetHTMET",cut},                   .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"METll",                   .pfs={Stack,"JetHTMET",cut},                   .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"MR",                      .pfs={Stack,"JetHTMET",cut},                   .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"MTRll",                   .pfs={Stack,"JetHTMET",cut},                   .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"R2ll",                    .pfs={Stack,"JetHTMET",cut},                   .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"RazorllBins",             .pfs={Stack,"JetHTMET",cut},                   .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"HT",                      .pfs={Stack,"JetHTMET",cut},                   .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"HTJet1AK8Pt",             .pfs={Stack,"JetHTMET",cut},                   .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP      // Ele or Muon
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"NJet",                    .pfs={Stack,"JetHTMET",cut,"2Ele_2Muon"},      .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"NJetAK8",                 .pfs={Stack,"JetHTMET",cut,"2Ele_2Muon"},      .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"HTFine",                  .pfs={Stack,"JetHTMET",cut,"2Ele_2Muon"},      .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"METll",                   .pfs={Stack,"JetHTMET",cut,"2Ele_2Muon"},      .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"MR",                      .pfs={Stack,"JetHTMET",cut,"2Ele_2Muon"},      .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"MTRll",                   .pfs={Stack,"JetHTMET",cut,"2Ele_2Muon"},      .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"R2ll",                    .pfs={Stack,"JetHTMET",cut,"2Ele_2Muon"},      .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"RazorllBins",             .pfs={Stack,"JetHTMET",cut,"2Ele_2Muon"},      .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"HT",                      .pfs={Stack,"JetHTMET",cut,"2Ele_2Muon"},      .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"HTJet1AK8Pt",             .pfs={Stack,"JetHTMET",cut,"2Ele_2Muon"},      .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP      for (auto njet_bin : {"NJet45"}) {
//TEMP        sh.AddHistos(s+"evt",  { .fill=c+"NJetAK8",                 .pfs={Stack,"JetHTMET",cut,njet_bin},          .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP        sh.AddHistos(s+"evt",  { .fill=c+"HTFine",                  .pfs={Stack,"JetHTMET",cut,njet_bin},          .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP        sh.AddHistos(s+"evt",  { .fill=c+"METll",                   .pfs={Stack,"JetHTMET",cut,njet_bin},          .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP        sh.AddHistos(s+"evt",  { .fill=c+"MR",                      .pfs={Stack,"JetHTMET",cut,njet_bin},          .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP        sh.AddHistos(s+"evt",  { .fill=c+"MTRll",                   .pfs={Stack,"JetHTMET",cut,njet_bin},          .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP        sh.AddHistos(s+"evt",  { .fill=c+"R2ll",                    .pfs={Stack,"JetHTMET",cut,njet_bin},          .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP        sh.AddHistos(s+"evt",  { .fill=c+"RazorllBins",             .pfs={Stack,"JetHTMET",cut,njet_bin},          .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP        sh.AddHistos(s+"evt",  { .fill=c+"HT",                      .pfs={Stack,"JetHTMET",cut,njet_bin},          .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP        sh.AddHistos(s+"evt",  { .fill=c+"HTJet1AK8Pt",             .pfs={Stack,"JetHTMET",cut,njet_bin},          .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP      }
//TEMP    }
//TEMP  
//TEMP    // N-1 plots
//TEMP    sh.AddHistos(s+"evt",  { .fill=c+"NJet",          .pfs={Stack,"JetHTMET","z_ExclNJet"},                 .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP    sh.AddHistos(s+"evt",  { .fill=c+"MR",            .pfs={Stack,"JetHTMET","z_ExclMR"},                   .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP    sh.AddHistos(s+"evt",  { .fill=c+"MTRll",         .pfs={Stack,"JetHTMET","z_ExclR2ll"},                 .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP    sh.AddHistos(s+"evt",  { .fill=c+"R2ll",          .pfs={Stack,"JetHTMET","z_ExclR2ll"},                 .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP    sh.AddHistos(s+"evt",  { .fill=c+"MinDeltaPhi",   .pfs={Stack,"JetHTMET","z_ExcldPhi"},              .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP    sh.AddHistos(s+"evt",  { .fill=c+"MinDeltaPhill", .pfs={Stack,"JetHTMET","z_ExcldPhi"},              .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP    sh.AddHistos(s+"evt",  { .fill=c+"DeltaPhi",      .pfs={Stack,"JetHTMET","z_ExcldPhi"},              .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP    sh.AddHistos(s+"evt",  { .fill=c+"DeltaPhiLLMET", .pfs={Stack,"JetHTMET","z"},                          .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP    sh.AddHistos(s+"evt",  { .fill=c+"DeltaPhiLLMET", .pfs={Stack,"JetHTMET","z_ExcldPhi"},              .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP    sh.AddHistos(s+"evt",  { .fill=c+"DeltaPhiLLJet", .pfs={Stack,"JetHTMET","z"},                          .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP    sh.AddHistos(s+"evt",  { .fill=c+"DeltaPhiLLJet", .pfs={Stack,"JetHTMET","z_ExcldPhi"},              .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP    sh.AddHistos(s+"evt",  { .fill=c+"Mll",           .pfs={Stack,"JetHTMET","z_ExclMll"},                  .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP    sh.AddHistos(s+"evt",  { .fill=c+"Mll",           .pfs={Stack,"JetHTMET","z_ExcldPhiMll"},           .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP    for (auto njet_bin : {"NJet45"}) {
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"NEle",          .pfs={Stack,"JetHTMET","z_ExclR2ll2Lep",njet_bin},    .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"NMu",           .pfs={Stack,"JetHTMET","z_ExclR2ll2Lep",njet_bin},    .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"NLep",          .pfs={Stack,"JetHTMET","z_ExclR2ll2Lep",njet_bin},    .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"NLooseBTag",    .pfs={Stack,"JetHTMET","z",                njet_bin}, .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"NBTag",         .pfs={Stack,"JetHTMET","z",                njet_bin}, .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"NW",            .pfs={Stack,"JetHTMET","z_Excl1W",         njet_bin}, .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"NmW",           .pfs={Stack,"JetHTMET","z_Excl1W",         njet_bin}, .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP      sh.AddHistos(s+"mW",   { .fill=c+"mWTau21",       .pfs={Stack,"JetHTMET","z_Excl1W",         njet_bin}, .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"MinDeltaPhi",   .pfs={Stack,"JetHTMET","z_ExcldPhi",    njet_bin}, .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"MinDeltaPhill", .pfs={Stack,"JetHTMET","z_ExcldPhi",    njet_bin}, .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"DeltaPhi",      .pfs={Stack,"JetHTMET","z_ExcldPhi",    njet_bin}, .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"Mll",           .pfs={Stack,"JetHTMET","z_ExclMll",        njet_bin}, .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP    }
//TEMP    // Ele or Muon
//TEMP    sh.AddHistos(s+"evt",  { .fill=c+"NJet",          .pfs={Stack,"JetHTMET","z_ExclNJet",   "2Ele_2Muon"},   .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP    sh.AddHistos(s+"evt",  { .fill=c+"MR",            .pfs={Stack,"JetHTMET","z_ExclMR","2Ele_2Muon"},        .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP    sh.AddHistos(s+"evt",  { .fill=c+"MTRll",         .pfs={Stack,"JetHTMET","z_ExclR2ll","2Ele_2Muon"},      .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP    sh.AddHistos(s+"evt",  { .fill=c+"R2ll",          .pfs={Stack,"JetHTMET","z_ExclR2ll","2Ele_2Muon"},      .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP    sh.AddHistos(s+"evt",  { .fill=c+"NLooseBTag",    .pfs={Stack,"JetHTMET","z",            "2Ele_2Muon"},   .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP    sh.AddHistos(s+"evt",  { .fill=c+"NBTag",         .pfs={Stack,"JetHTMET","z",            "2Ele_2Muon"},   .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP    sh.AddHistos(s+"evt",  { .fill=c+"NW",            .pfs={Stack,"JetHTMET","z_Excl1W",     "2Ele_2Muon"},   .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP    sh.AddHistos(s+"evt",  { .fill=c+"NmW",           .pfs={Stack,"JetHTMET","z_Excl1W",     "2Ele_2Muon"},   .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP    sh.AddHistos(s+"mW",   { .fill=c+"mWTau21",       .pfs={Stack,"JetHTMET","z_Excl1W",     "2Ele_2Muon"},   .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP    sh.AddHistos(s+"evt",  { .fill=c+"MinDeltaPhi",   .pfs={Stack,"JetHTMET","z_ExcldPhi","2Ele_2Muon"},   .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP    sh.AddHistos(s+"evt",  { .fill=c+"MinDeltaPhill", .pfs={Stack,"JetHTMET","z_ExcldPhi","2Ele_2Muon"},   .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP    sh.AddHistos(s+"evt",  { .fill=c+"DeltaPhi",      .pfs={Stack,"JetHTMET","z_ExcldPhi","2Ele_2Muon"},   .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP    sh.AddHistos(s+"evt",  { .fill=c+"Mll",           .pfs={Stack,"JetHTMET","z_ExclMll",    "2Ele_2Muon"},   .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP  
//TEMP    // Other
//TEMP    sh.AddHistos(s+"evt",  { .fill=c+"HTFine",      .pfs={Stack,"JetHTMET","z_Excl1W"},                        .cuts={},.draw=d,.opt=o_stk_s,.ranges=r_Stk6});
//TEMP  #endif
//TEMP  
//TEMP    // -------------------------------------------------------------------------
//TEMP    //                     Photon enriched Region: G
//TEMP  
//TEMP    sh.SetHistoWeights({ [this] { return sf_weight['G']; } });
//TEMP  
//TEMP    for (const auto& cut : {"G"}) {
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"HTFine",                  .pfs={Stack,"JetHTMET",cut},                    .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"METNoPho",                .pfs={Stack,"JetHTMET",cut},                    .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"MRNoPho",                 .pfs={Stack,"JetHTMET",cut},                    .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"MTRNoPho",                .pfs={Stack,"JetHTMET",cut},                    .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"R2NoPho",                 .pfs={Stack,"JetHTMET",cut},                    .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"RazorNoPhoBins",          .pfs={Stack,"JetHTMET",cut},                    .cuts={},.draw=d,.opt=O_stk_d+"NoComb2",.ranges=r_Stk5});
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"NJet",                    .pfs={Stack,"JetHTMET",cut},                    .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"NJetNoPho",               .pfs={Stack,"JetHTMET",cut},                    .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"HT",                      .pfs={Stack,"JetHTMET",cut},                    .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"HTJet1AK8Pt",             .pfs={Stack,"JetHTMET",cut},                    .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP      for (auto njet_bin : {"NJet45"}) {
//TEMP        sh.AddHistos(s+"evt",  { .fill=c+"HTFine",                  .pfs={Stack,"JetHTMET",cut,njet_bin},           .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP        sh.AddHistos(s+"evt",  { .fill=c+"METNoPho",                .pfs={Stack,"JetHTMET",cut,njet_bin},           .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP        sh.AddHistos(s+"evt",  { .fill=c+"MRNoPho",                 .pfs={Stack,"JetHTMET",cut,njet_bin},           .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP        sh.AddHistos(s+"evt",  { .fill=c+"MTRNoPho",                .pfs={Stack,"JetHTMET",cut,njet_bin},           .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP        sh.AddHistos(s+"evt",  { .fill=c+"R2NoPho",                 .pfs={Stack,"JetHTMET",cut,njet_bin},           .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP        sh.AddHistos(s+"evt",  { .fill=c+"RazorNoPhoBins",          .pfs={Stack,"JetHTMET",cut,njet_bin},           .cuts={},.draw=d,.opt=O_stk_d+"NoComb2",.ranges=r_Stk5});
//TEMP        sh.AddHistos(s+"evt",  { .fill=c+"NJetAK8",                 .pfs={Stack,"JetHTMET",cut,njet_bin},           .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP        sh.AddHistos(s+"evt",  { .fill=c+"HT",                      .pfs={Stack,"JetHTMET",cut,njet_bin},           .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP        sh.AddHistos(s+"evt",  { .fill=c+"HTJet1AK8Pt",             .pfs={Stack,"JetHTMET",cut,njet_bin},           .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP      }
//TEMP    }
//TEMP  
//TEMP    // N-1 Cut plots
//TEMP    sh.AddHistos(s+"evt",  { .fill=c+"NJet",             .pfs={Stack,"JetHTMET","G_ExclNJet"},              .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP    sh.AddHistos(s+"evt",  { .fill=c+"NJetNoPho",        .pfs={Stack,"JetHTMET","G_ExclNJet"},              .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP    sh.AddHistos(s+"evt",  { .fill=c+"MinDeltaPhiNoPho", .pfs={Stack,"JetHTMET","G_ExcldPhi"},              .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP    sh.AddHistos(s+"evt",  { .fill=c+"DeltaPhiNoPho",    .pfs={Stack,"JetHTMET","G_ExcldPhi"},              .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP    sh.AddHistos(s+"evt",  { .fill=c+"NPhoton",          .pfs={Stack,"JetHTMET","G_Excl1Pho"},              .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP    sh.AddHistos(s+"pho",  { .fill=c+"PhotonPt",         .pfs={Stack,"JetHTMET","G_Excl1Pho"},              .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP    sh.AddHistos(s+"pho",  { .fill=c+"PhotonEta",        .pfs={Stack,"JetHTMET","G_Excl1Pho"},              .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP    sh.AddHistos(s+"evt",  { .fill=c+"NBTagNoPho",       .pfs={Stack,"JetHTMET","G"},                            .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP    for (auto njet_bin : {"NJet45"}) {
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"NEleVeto",         .pfs={Stack,"JetHTMET","G_Excl0Ele0Tau",njet_bin},     .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"NMuVeto",          .pfs={Stack,"JetHTMET","G_Excl0Mu0Tau", njet_bin},     .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"NIsoTrk",          .pfs={Stack,"JetHTMET","G_Excl0Tau",njet_bin},     .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"NTauVeto",         .pfs={Stack,"JetHTMET","G_Excl0Tau",njet_bin},     .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"NBTagNoPho",       .pfs={Stack,"JetHTMET","G",            njet_bin},  .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP  #if TOP == 0                                                                                                                                     
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"NmW",              .pfs={Stack,"JetHTMET","G_Excl1mW",    njet_bin},  .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"NW",               .pfs={Stack,"JetHTMET","G_Excl1mW",    njet_bin},  .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP      sh.AddHistos(s+"mW",   { .fill=c+"mWTau21",          .pfs={Stack,"JetHTMET","G_Excl1mW",    njet_bin},  .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP  #else                                                                                                                                            
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"NMTop",            .pfs={Stack,"JetHTMET","G_Excl1MTop",  njet_bin},  .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"NTop",             .pfs={Stack,"JetHTMET","G_Excl1MTop",  njet_bin},  .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP      sh.AddHistos(s+"MTop", { .fill=c+"MTopTau32",        .pfs={Stack,"JetHTMET","G_Excl1MTop",  njet_bin},  .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP  #endif
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"MinDeltaPhiNoPho", .pfs={Stack,"JetHTMET","G_ExcldPhi",   njet_bin},  .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"DeltaPhiNoPho",    .pfs={Stack,"JetHTMET","G_ExcldPhi",   njet_bin},  .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"NPhoton",          .pfs={Stack,"JetHTMET","G_Excl1Pho",   njet_bin},  .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP    }
//TEMP  
//TEMP    std::string truth_opt = "LogSumw2Stack1AddRatioAddIntApproval15";
//TEMP    if (TOP == 1) truth_opt = "LogSumw2Stack1AddRatioAddIntApproval15";
//TEMP    // Plots for the Z(inv) estimate
//TEMP    sh.AddHistos(s+"pho",    { .fill=c+"PhotonPt",                .pfs={Stack,"JetHTMET","G"},           .cuts={},.draw=d,.opt=O_stk_d+"NoComb2",.ranges={80.01,960, 1.01e-1,1e4,  0.4,0.86}});
//TEMP    sh.AddHistos(s+"pho",    { .fill=c+"PhotonPt",                .pfs={Stack,"JetHTMET","G","EB_EE"},   .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk4});
//TEMP    sh.AddHistos(s+"pho",    { .fill=c+"PhotonEta",               .pfs={Stack,"JetHTMET","G"},           .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP    sh.AddHistos(s+"prepho", { .fill=c+"PhotonSIEIE",             .pfs={Stack,"JetHTMET",     "G_Excl1Pho","EB"},  .cuts={},.draw=d,.opt=o_stk_d,.ranges={0,0.03,    1.01e-2,1e6,  0.4,0.86}});
//TEMP    sh.AddHistos(s+"prepho", { .fill=c+"PhotonSIEIE",             .pfs={Stack,"JetHTMET",     "G_Excl1Pho","EE"},  .cuts={},.draw=d,.opt=o_stk_d,.ranges={0.01,0.06, 1.01e-2,1e6,  0.4,0.86}});
//TEMP    sh.AddHistos(s+"prepho", { .fill=c+"PhotonSIEIE",             .pfs={"Data_PhotonTruth","G_Excl1Pho","EB"},  .cuts={},.draw="PE1",.opt=truth_opt,.ranges={0,0, 0,0,  0.4,0.86}});
//TEMP    sh.AddHistos(s+"prepho", { .fill=c+"PhotonSIEIE",             .pfs={"Data_PhotonTruth","G_Excl1Pho","EE"},  .cuts={},.draw="PE1",.opt=truth_opt,.ranges={0,0, 0,0,  0.4,0.86}});
//TEMP    // Photon chiso (for fitting, not templates)
//TEMP    sh.AddHistos(s+"prepho", { .fill=c+"PhotonCHIso",             .pfs={Stack,"JetHTMET",     "G_Excl1Pho","SIEIE","EB_EE"},  .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP    sh.AddHistos(s+"prepho", { .fill=c+"PhotonCHIso",             .pfs={"Data_PhotonTruth","G_Excl1Pho","SIEIE","EB_EE"},  .cuts={},.draw="PE1",.opt=truth_opt,.ranges={}});
//TEMP    sh.AddHistos(s+"prepho", { .fill=c+"PhotonCHIso",             .pfs={"Data_MC",         "G_Excl1Pho","SIEIE","EB_EE"},           .cuts={},.draw="PE1",.opt=o_1or2d_d+"AddRatio",.ranges={}});
//TEMP    // Prompt photons in MC
//TEMP    //sh.AddHistos(s+"prepho", { .fill=c+"PhotonCHIso",             .pfs={"EB_EE",           "G_Excl1Pho","SIEIE","MC",    "Prompt"}, .cuts={},.draw="PE1",.opt=o_1or2d_s,.ranges={}});
//TEMP    // Photon composition
//TEMP  //sh.AddHistos(s+"evt",    { .fill=c+"RazorNoPhoBins",          .pfs={"Data_Photon1Truth","G"},              .cuts={},.draw=d,.opt=truth_opt,.ranges=r_Stk5});
//TEMP  //sh.AddHistos(s+"evt",    { .fill=c+"RazorNoPhoBins",          .pfs={"Data_Photon1Truth","G","1Pho_EB_EE"}, .cuts={},.draw=d,.opt=truth_opt,.ranges=r_Stk5});
//TEMP  //sh.AddHistos(s+"evt",    { .fill=c+"Photon1Eta",              .pfs={"Data_Photon1Truth","G"},              .cuts={},.draw=d,.opt=truth_opt,.ranges=r_Stk5});
//TEMP  
//TEMP    // Direct photon fraction in MC
//TEMP  //  sh.AddHistos("pho",      { .fill="DirectFraction_vs_HTFine",         .pfs={"Background","Prompt","G"}, .cuts={},.draw="PE1",.opt=o_1or2d_s,.ranges={0,0, 0,1, 0.4,0.5}});
//TEMP  //  sh.AddHistos("pho",      { .fill="DirectFraction_vs_HT",             .pfs={"Background","Prompt","G"}, .cuts={},.draw="PE1",.opt=o_1or2d_s,.ranges={0,0, 0,1, 0.4,0.5}});
//TEMP  //  sh.AddHistos("pho",      { .fill="DirectFraction_vs_RazorNoPhoBins", .pfs={"Background","Prompt","G"}, .cuts={},.draw="PE1",.opt=o_1or2d_s,.ranges={0,0, 0,1, 0.4,0.5}});
//TEMP  //  sh.AddHistos("pho",      { .fill="DirectFraction_vs_MRNoPho",        .pfs={"Background","Prompt","G"}, .cuts={},.draw="PE1",.opt=o_1or2d_s,.ranges={0,0, 0,1, 0.4,0.5}});
//TEMP  //  sh.AddHistos("pho",      { .fill="DirectFraction_vs_R2NoPho",        .pfs={"Background","Prompt","G"}, .cuts={},.draw="PE1",.opt=o_1or2d_s,.ranges={0,0, 0,1, 0.4,0.5}});
//TEMP  //  sh.AddHistos("pho",      { .fill="DirectFraction_vs_NJet",           .pfs={"Background","Prompt","G"}, .cuts={},.draw="PE1",.opt=o_1or2d_s,.ranges={0,0, 0,1, 0.4,0.5}});
//TEMP  //  sh.AddHistos("pho",      { .fill="DirectFraction_vs_NJetNoPho",      .pfs={"Background","Prompt","G"}, .cuts={},.draw="PE1",.opt=o_1or2d_s,.ranges={0,0, 0,1, 0.4,0.5}});
//TEMP  //  sh.AddHistos("pho",      { .fill="DirectFraction_vs_NBTagNoPho",     .pfs={"Background","Prompt","G"}, .cuts={},.draw="PE1",.opt=o_1or2d_s,.ranges={0,0, 0,1, 0.4,0.5}});
//TEMP  //#if TOP == 0
//TEMP  //  sh.AddHistos("pho",      { .fill="DirectFraction_vs_NmW",            .pfs={"Background","Prompt","G_Excl1mW"}, .cuts={},.draw="PE1",.opt=o_1or2d_s,.ranges={0,0, 0,1, 0.4,0.5}});
//TEMP  //  sh.AddHistos("pho",      { .fill="DirectFraction_vs_NW",             .pfs={"Background","Prompt","G_Excl1mW"}, .cuts={},.draw="PE1",.opt=o_1or2d_s,.ranges={0,0, 0,1, 0.4,0.5}});
//TEMP  //#else
//TEMP  //  sh.AddHistos("pho",      { .fill="DirectFraction_vs_NMTop",          .pfs={"Background","Prompt","G_Excl1MTop"}, .cuts={},.draw="PE1",.opt=o_1or2d_s,.ranges={0,0, 0,1, 0.4,0.5}});
//TEMP  //  sh.AddHistos("pho",      { .fill="DirectFraction_vs_NTop",           .pfs={"Background","Prompt","G_Excl1MTop"}, .cuts={},.draw="PE1",.opt=o_1or2d_s,.ranges={0,0, 0,1, 0.4,0.5}});
//TEMP  //#endif
//TEMP  //  sh.AddHistos("pho",      { .fill="DirectFraction_vs_PhotonPt",       .pfs={"Background","Prompt","G"}, .cuts={},.draw="PE1",.opt=o_1or2d_s,.ranges={0,0, 0,1, 0.4,0.5}});
//TEMP  //  sh.AddHistos("pho",      { .fill="DirectFraction_vs_PhotonEta",      .pfs={"Background","Prompt","G"}, .cuts={},.draw="PE1",.opt=o_1or2d_s,.ranges={0,0, 0,1, 0.4,0.5}});
//TEMP  //  // Same but vs background types
//TEMP  //  for (const auto& bkg : {"Multijet", "GJets"}) {
//TEMP  //    sh.AddHistos("pho",      { .fill="DirectFraction_vs_HTFine",         .pfs={"G",          "Prompt",bkg}, .cuts={},.draw="PE1",.opt=o_1or2d_s,.ranges={}});
//TEMP  //    sh.AddHistos("pho",      { .fill="DirectFraction_vs_HT",             .pfs={"G",          "Prompt",bkg}, .cuts={},.draw="PE1",.opt=o_1or2d_s,.ranges={}});
//TEMP  //    sh.AddHistos("pho",      { .fill="DirectFraction_vs_RazorNoPhoBins", .pfs={"G",          "Prompt",bkg}, .cuts={},.draw="PE1",.opt=o_1or2d_s,.ranges={}});
//TEMP  //    sh.AddHistos("pho",      { .fill="DirectFraction_vs_MRNoPho",        .pfs={"G",          "Prompt",bkg}, .cuts={},.draw="PE1",.opt=o_1or2d_s,.ranges={}});
//TEMP  //    sh.AddHistos("pho",      { .fill="DirectFraction_vs_R2NoPho",        .pfs={"G",          "Prompt",bkg}, .cuts={},.draw="PE1",.opt=o_1or2d_s,.ranges={}});
//TEMP  //    sh.AddHistos("pho",      { .fill="DirectFraction_vs_NJet",           .pfs={"G",          "Prompt",bkg}, .cuts={},.draw="PE1",.opt=o_1or2d_s,.ranges={}});
//TEMP  //    sh.AddHistos("pho",      { .fill="DirectFraction_vs_NJetNoPho",      .pfs={"G",          "Prompt",bkg}, .cuts={},.draw="PE1",.opt=o_1or2d_s,.ranges={}});
//TEMP  //    sh.AddHistos("pho",      { .fill="DirectFraction_vs_NBTagNoPho",     .pfs={"G",          "Prompt",bkg}, .cuts={},.draw="PE1",.opt=o_1or2d_s,.ranges={}});
//TEMP  //#if TOP == 0
//TEMP  //    sh.AddHistos("pho",      { .fill="DirectFraction_vs_NmW",            .pfs={"G_Excl1mW",  "Prompt",bkg}, .cuts={},.draw="PE1",.opt=o_1or2d_s,.ranges={}});
//TEMP  //    sh.AddHistos("pho",      { .fill="DirectFraction_vs_NW",             .pfs={"G_Excl1mW",  "Prompt",bkg}, .cuts={},.draw="PE1",.opt=o_1or2d_s,.ranges={}});
//TEMP  //#else
//TEMP  //    sh.AddHistos("pho",      { .fill="DirectFraction_vs_NMTop",          .pfs={"G_Excl1MTop","Prompt",bkg}, .cuts={},.draw="PE1",.opt=o_1or2d_s,.ranges={}});
//TEMP  //    sh.AddHistos("pho",      { .fill="DirectFraction_vs_NTop",           .pfs={"G_Excl1MTop","Prompt",bkg}, .cuts={},.draw="PE1",.opt=o_1or2d_s,.ranges={}});
//TEMP  //#endif
//TEMP  //    sh.AddHistos("pho",      { .fill="DirectFraction_vs_PhotonPt",       .pfs={"G",          "Prompt",bkg}, .cuts={},.draw="PE1",.opt=o_1or2d_s,.ranges={}});
//TEMP  //    sh.AddHistos("pho",      { .fill="DirectFraction_vs_PhotonEta",      .pfs={"G",          "Prompt",bkg}, .cuts={},.draw="PE1",.opt=o_1or2d_s,.ranges={}});
//TEMP  //  }
//TEMP  //
//TEMP  //  // MC Truth Photon purity
//TEMP  //  sh.AddHistos("evt",        { .fill="PhotonPurity_vs_R2NoPho_vs_MRNoPho",  .pfs={"Background","G"},              .cuts={},.draw="COLZ",.opt=o_1or2d_s,.ranges={}});
//TEMP  //  sh.AddHistos("evt",        { .fill="PhotonPurity_vs_R2NoPho_vs_MRNoPho",  .pfs={"Background","G","1Pho_EB_EE"}, .cuts={},.draw="COLZ",.opt=o_1or2d_s,.ranges={}});
//TEMP  //  sh.AddHistos("evt",        { .fill="PhotonPurity_vs_MRNoPho",             .pfs={"1Pho_EB_EE","Background","G"}, .cuts={},.draw="PE1",.opt=o_1or2d_s,.ranges={0,0, 0,1, 0.4,0.5}});
//TEMP  //  sh.AddHistos("evt",        { .fill="PhotonPurity_vs_R2NoPho",             .pfs={"1Pho_EB_EE","Background","G"}, .cuts={},.draw="PE1",.opt=o_1or2d_s,.ranges={0,0, 0,1, 0.4,0.5}});
//TEMP  //  sh.AddHistos("evt",        { .fill="PhotonPurity_vs_RazorNoPhoBins",      .pfs={"1Pho_EB_EE","Background","G"}, .cuts={},.draw="PE1",.opt=o_1or2d_s,.ranges={0,0, 0,1, 0.4,0.5}});
//TEMP  
//TEMP    // Plots for the Z(nunu)/G ratio
//TEMP   // sh.AddHistos(s+"evt",  { .fill=c+"NJet",                               .pfs={"G",          "Background","PromptDirect"},  .cuts={},.draw="HIST",.opt=o_1or2d_s,.ranges={}});
//TEMP   // sh.AddHistos(s+"evt",  { .fill=c+"NJetNoPho",                          .pfs={"G",          "Background","PromptDirect"},  .cuts={},.draw="HIST",.opt=o_1or2d_s,.ranges={}});
//TEMP   // sh.AddHistos(s+"evt",  { .fill=c+"RazorNoPhoBins",                     .pfs={"G",          "Background","PromptDirect"},  .cuts={},.draw="HIST",.opt=o_1or2d_s,.ranges={}});
//TEMP   // sh.AddHistos(s+"evt",  { .fill=c+"MRNoPho",                            .pfs={"G",          "Background","PromptDirect"},  .cuts={},.draw="HIST",.opt=o_1or2d_s,.ranges={}});
//TEMP   // sh.AddHistos(s+"evt",  { .fill=c+"R2NoPho",                            .pfs={"G",          "Background","PromptDirect"},  .cuts={},.draw="HIST",.opt=o_1or2d_s,.ranges={}});
//TEMP  #//if TOP == 0
//TEMP   // sh.AddHistos(s+"evt",  { .fill=c+"NW",                                 .pfs={"G_Excl1mW",  "Background","PromptDirect"},  .cuts={},.draw="HIST",.opt=o_1or2d_s,.ranges={}});
//TEMP  #//else
//TEMP   // sh.AddHistos(s+"evt",  { .fill=c+"NTop",                               .pfs={"G_Excl1MTop","Background","PromptDirect"},  .cuts={},.draw="HIST",.opt=o_1or2d_s,.ranges={}});
//TEMP  #//endif
//TEMP    // Same plots in S region for ZToNuNu
//TEMP    sh.SetHistoWeights({ [this] { return sf_weight['S']; } });
//TEMP    sh.AddHistos(s+"evt",  { .fill=c+"NJet",                               .pfs={"S",         "ZToNuNu"},  .cuts={},.draw="HIST",.opt=o_1or2d_s,.ranges={}});
//TEMP    sh.AddHistos(s+"evt",  { .fill=c+"RazorBins",                          .pfs={"S",         "ZToNuNu"},  .cuts={},.draw="HIST",.opt=o_1or2d_s,.ranges={}});
//TEMP    sh.AddHistos(s+"evt",  { .fill=c+"RazorBins",                          .pfs={"S",         "ZToNuNu","NJet45"},  .cuts={},.draw="HIST",.opt=o_1or2d_s,.ranges={}});
//TEMP    sh.AddHistos(s+"evt",  { .fill=c+"MR",                                 .pfs={"S",         "ZToNuNu"},  .cuts={},.draw="HIST",.opt=o_1or2d_s,.ranges={}});
//TEMP    sh.AddHistos(s+"evt",  { .fill=c+"R2",                                 .pfs={"S",         "ZToNuNu"},  .cuts={},.draw="HIST",.opt=o_1or2d_s,.ranges={}});
//TEMP  #if TOP == 0
//TEMP    sh.AddHistos(s+"evt",  { .fill=c+"NW",                                 .pfs={"S_Excl1W",  "ZToNuNu"},  .cuts={},.draw="HIST",.opt=o_1or2d_s,.ranges={}});
//TEMP  #else
//TEMP    sh.AddHistos(s+"evt",  { .fill=c+"NTop",                               .pfs={"S_Excl1Top","ZToNuNu"},  .cuts={},.draw="HIST",.opt=o_1or2d_s,.ranges={}});
//TEMP  #endif
//TEMP  
//TEMP  
//TEMP    // Same plots but without any boosted object
//TEMP    sh.SetHistoWeights({ [this] { return sf_weight['H']; } });
//TEMP  
//TEMP    for (const auto& cut : {"H"}) {
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"HTFine",                  .pfs={Stack,"JetHTMET",cut},                    .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"METNoPho",                .pfs={Stack,"JetHTMET",cut},                    .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"MRNoPho",                 .pfs={Stack,"JetHTMET",cut},                    .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"MTRNoPho",                .pfs={Stack,"JetHTMET",cut},                    .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"R2NoPho",                 .pfs={Stack,"JetHTMET",cut},                    .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"RazorNoPhoBins",          .pfs={Stack,"JetHTMET",cut},                    .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"NJet",                    .pfs={Stack,"JetHTMET",cut},                    .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"NJetNoPho",               .pfs={Stack,"JetHTMET",cut},                    .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"HT",                      .pfs={Stack,"JetHTMET",cut},                    .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"HTJet1AK8Pt",             .pfs={Stack,"JetHTMET",cut},                    .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP      for (auto njet_bin : {"NJet45"}) {
//TEMP        sh.AddHistos(s+"evt",  { .fill=c+"HTFine",                  .pfs={Stack,"JetHTMET",cut,njet_bin},           .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP        sh.AddHistos(s+"evt",  { .fill=c+"METNoPho",                .pfs={Stack,"JetHTMET",cut,njet_bin},           .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP        sh.AddHistos(s+"evt",  { .fill=c+"MRNoPho",                 .pfs={Stack,"JetHTMET",cut,njet_bin},           .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP        sh.AddHistos(s+"evt",  { .fill=c+"MTRNoPho",                .pfs={Stack,"JetHTMET",cut,njet_bin},           .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP        sh.AddHistos(s+"evt",  { .fill=c+"R2NoPho",                 .pfs={Stack,"JetHTMET",cut,njet_bin},           .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP        sh.AddHistos(s+"evt",  { .fill=c+"RazorNoPhoBins",          .pfs={Stack,"JetHTMET",cut,njet_bin},           .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP        sh.AddHistos(s+"evt",  { .fill=c+"NJetAK8",                 .pfs={Stack,"JetHTMET",cut,njet_bin},           .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP        sh.AddHistos(s+"evt",  { .fill=c+"HT",                      .pfs={Stack,"JetHTMET",cut,njet_bin},           .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP        sh.AddHistos(s+"evt",  { .fill=c+"HTJet1AK8Pt",             .pfs={Stack,"JetHTMET",cut,njet_bin},           .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP      }
//TEMP    }
//TEMP  
//TEMP    // N-1 Cut plots
//TEMP    sh.AddHistos(s+"evt",  { .fill=c+"NJet",             .pfs={Stack,"JetHTMET","H_ExclNJet"},              .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP    sh.AddHistos(s+"evt",  { .fill=c+"NJetNoPho",        .pfs={Stack,"JetHTMET","H_ExclNJet"},              .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP    sh.AddHistos(s+"evt",  { .fill=c+"MinDeltaPhiNoPho", .pfs={Stack,"JetHTMET","H_ExcldPhi"},              .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP    sh.AddHistos(s+"evt",  { .fill=c+"DeltaPhiNoPho",    .pfs={Stack,"JetHTMET","H_ExcldPhi"},              .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP    sh.AddHistos(s+"evt",  { .fill=c+"NPhoton",          .pfs={Stack,"JetHTMET","H_Excl1Pho"},              .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP    sh.AddHistos(s+"pho",  { .fill=c+"PhotonPt",         .pfs={Stack,"JetHTMET","H_Excl1Pho"},              .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP    sh.AddHistos(s+"pho",  { .fill=c+"PhotonEta",        .pfs={Stack,"JetHTMET","H_Excl1Pho"},              .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP  
//TEMP    sh.AddHistos(s+"evt",  { .fill=c+"NBTagNoPho",       .pfs={Stack,"JetHTMET","H"},                            .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP    for (auto njet_bin : {"NJet45"}) {
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"NEleVeto",         .pfs={Stack,"JetHTMET","H_Excl0Ele0Tau",njet_bin},.cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"NMuVeto",          .pfs={Stack,"JetHTMET","H_Excl0Mu0Tau", njet_bin},.cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"NIsoTrk",          .pfs={Stack,"JetHTMET","H_Excl0Tau",njet_bin},.cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"NTauVeto",         .pfs={Stack,"JetHTMET","H_Excl0Tau",njet_bin},.cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"NBTagNoPho",       .pfs={Stack,"JetHTMET","H",            njet_bin},  .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"MinDeltaPhiNoPho", .pfs={Stack,"JetHTMET","H_ExcldPhi",   njet_bin},  .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"DeltaPhiNoPho",    .pfs={Stack,"JetHTMET","H_ExcldPhi",   njet_bin},  .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"NPhoton",          .pfs={Stack,"JetHTMET","H_Excl1Pho",   njet_bin},  .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP    }
//TEMP  
//TEMP    sh.AddHistos(s+"pho",  { .fill=c+"PhotonPt",         .pfs={Stack,"JetHTMET","H"},                       .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP    sh.AddHistos(s+"pho",  { .fill=c+"PhotonPt",         .pfs={Stack,"JetHTMET","H","EB_EE"},               .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP    sh.AddHistos(s+"pho",  { .fill=c+"PhotonEta",        .pfs={Stack,"JetHTMET","H"},                       .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP    sh.AddHistos(s+"prepho", { .fill=c+"PhotonSIEIE",             .pfs={Stack,"JetHTMET",     "H_Excl1Pho","EB"},  .cuts={},.draw=d,.opt=o_stk_d,.ranges={0,0.03,    1.01e-2,1e6,  0.4,0.86}});
//TEMP    sh.AddHistos(s+"prepho", { .fill=c+"PhotonSIEIE",             .pfs={Stack,"JetHTMET",     "H_Excl1Pho","EE"},  .cuts={},.draw=d,.opt=o_stk_d,.ranges={0.01,0.06, 1.01e-2,1e6,  0.4,0.86}});
//TEMP    sh.AddHistos(s+"prepho", { .fill=c+"PhotonSIEIE",             .pfs={"Data_PhotonTruth","H_Excl1Pho","EB"},  .cuts={},.draw="PE1",.opt="Sumw2Stack1AddRatioApproval15",.ranges={0,0, 0,0,  0.4,0.86}});
//TEMP    sh.AddHistos(s+"prepho", { .fill=c+"PhotonSIEIE",             .pfs={"Data_PhotonTruth","H_Excl1Pho","EE"},  .cuts={},.draw="PE1",.opt="Sumw2Stack1AddRatioApproval15",.ranges={0,0, 0,0,  0.4,0.86}});
//TEMP    // Photon chiso templates
//TEMP    sh.AddHistos(s+"prepho", { .fill=c+"PhotonCHIso",             .pfs={Stack,"JetHTMET",     "H_Excl1Pho","SIEIE","EB_EE"},  .cuts={},.draw=d,.opt=o_stk_d,.ranges=r_Stk6});
//TEMP    sh.AddHistos(s+"prepho", { .fill=c+"PhotonCHIso",             .pfs={"Data_PhotonTruth","H_Excl1Pho","SIEIE","EB_EE"},  .cuts={},.draw="PE1",.opt="Sumw2Stack1AddRatioApproval15",.ranges={}});
//TEMP    sh.AddHistos(s+"prepho", { .fill=c+"PhotonCHIso",             .pfs={"Data_MC",         "H_Excl1Pho","SIEIE","EB_EE"},           .cuts={},.draw="PE1",.opt=o_1or2d_d+"AddRatio",.ranges={}});
//TEMP    // Fakes
//TEMP    sh.AddHistos(s+"prepho", { .fill=c+"PhotonCHIso",             .pfs={"EB_EE",           "H_Excl1Pho","SIEIE","Data"},   .cuts={},.draw="PE1",.opt=o_1or2d_d,.ranges={}});
//TEMP    // Prompt photons in MC
//TEMP    //sh.AddHistos(s+"prepho", { .fill=c+"PhotonCHIso",             .pfs={"EB_EE",           "H_Excl1Pho","SIEIE","MC",    "Prompt"}, .cuts={},.draw="PE1",.opt=o_1or2d_s,.ranges={}});
//TEMP  
//TEMP    // -------------------------------------------------------------------------
//TEMP    //                 Fake W/Top enriched region: F
//TEMP  
//TEMP    for (auto region : {'F', 'B'}) {
//TEMP      sh.SetHistoWeights({ [this,region] { return w_nm1[region][7]*other_trigger_eff; } });
//TEMP      std::string cut1 = std::string(1,region);
//TEMP      std::string cut2 = cut1;
//TEMP      if (region=='F') cut2 += "_Excl0b";
//TEMP      else             cut2 += "_Excl1b";
//TEMP      std::string data = "JetHTMET";
//TEMP      std::string opt  = o_stk_d;
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"HTFine",                  .pfs={Stack,data,cut1},                    .cuts={},.draw=d,.opt=opt,.ranges=r_Stk9});
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"MET",                     .pfs={Stack,data,cut1},                    .cuts={},.draw=d,.opt=opt,.ranges=r_Stk9});
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"MR",                      .pfs={Stack,data,cut1},                    .cuts={},.draw=d,.opt=opt,.ranges=r_Stk9});
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"MTR",                     .pfs={Stack,data,cut1},                    .cuts={},.draw=d,.opt=opt,.ranges=r_Stk9});
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"R2",                      .pfs={Stack,data,cut1},                    .cuts={},.draw=d,.opt=opt,.ranges=r_Stk9});
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"RazorBins",               .pfs={Stack,data,cut1},                    .cuts={},.draw=d,.opt=opt,.ranges=r_Stk9});
//TEMP      sh.AddHistos("evt",    { .fill="MR_vs_MET",                 .pfs={"Signals_Background",cut1},          .cuts={},.draw="COLZ",.opt=o_1or2d_s+"Log",.ranges={}});
//TEMP      sh.AddHistos("evt",    { .fill="R2_vs_MET",                 .pfs={"Signals_Background",cut1},          .cuts={},.draw="COLZ",.opt=o_1or2d_s+"Log",.ranges={}});
//TEMP      sh.AddHistos("evt",    { .fill="R2_vs_MR",                  .pfs={"Signals_Background",cut1},          .cuts={},.draw="COLZ",.opt=o_1or2d_s+"Log",.ranges={}});
//TEMP      sh.AddHistos("evt",    { .fill="R2Fine_vs_MRFine",          .pfs={"Signals_Background",cut1},          .cuts={},.draw="COLZ",.opt=o_1or2d_s+"Log",.ranges={}});
//TEMP      sh.AddHistos("evt",    { .fill="MR_vs_HTFine",              .pfs={"Signals_Background",cut1},          .cuts={},.draw="COLZ",.opt=o_1or2d_s+"Log",.ranges={}});
//TEMP      sh.AddHistos("evt",    { .fill="MET_vs_HTFine",             .pfs={"Signals_Background",cut1},          .cuts={},.draw="COLZ",.opt=o_1or2d_s+"Log",.ranges={}});
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"NJet",                    .pfs={Stack,data,cut1},                    .cuts={},.draw=d,.opt=opt,.ranges=r_Stk9});
//TEMP      //sh.AddHistos(s+"evt",  { .fill=c+"NJetAK8",                 .pfs={Stack,data,cut1},                    .cuts={},.draw=d,.opt=opt,.ranges=r_Stk9});
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"HT",                      .pfs={Stack,data,cut1},                    .cuts={},.draw=d,.opt=opt,.ranges=r_Stk9});
//TEMP      sh.AddHistos(s+"evt",  { .fill=c+"HTJet1AK8Pt",             .pfs={Stack,data,cut1},                    .cuts={},.draw=d,.opt=opt,.ranges=r_Stk9});
//TEMP  
//TEMP      // Fake rates
//TEMP      // W/Top fakes (with b-tag veto)
//TEMP      sh.AddHistos(s+"AK8", { .fill="WTagFakeRate_vs_JetAK8PtBins",            .pfs={"Data_MC",cut1,"Syst"},                     .cuts={},.draw="PE1",.opt=o_1or2d_d+"AddRatio",.ranges={}});
//TEMP      sh.AddHistos(s+"AK8", { .fill="WTagFakeRate_vs_JetAK8PtBins",            .pfs={"Data_MC",cut1,"Syst","AK8_EB_EE"},         .cuts={},.draw="PE1",.opt=o_1or2d_d+"AddRatio",.ranges={}});
//TEMP      sh.AddHistos(s+"AK8", { .fill="W0BMassTagFakeRate_vs_JetAK8PtBins",      .pfs={"Data_MC",cut1,"Syst"},                     .cuts={},.draw="PE1",.opt=o_1or2d_d+"AddRatio",.ranges={}});
//TEMP      sh.AddHistos(s+"AK8", { .fill="W0BMassTagFakeRate_vs_JetAK8PtBins",      .pfs={"Data_MC",cut1,"Syst","AK8_EB_EE"},         .cuts={},.draw="PE1",.opt=o_1or2d_d+"AddRatio",.ranges={}});
//TEMP      sh.AddHistos(s+"AK8", { .fill="WAntiTagFakeRate_vs_JetAK8PtBins",        .pfs={"Data_MC",cut1,"Syst"},                     .cuts={},.draw="PE1",.opt=o_1or2d_d+"AddRatio",.ranges={}});
//TEMP      sh.AddHistos(s+"AK8", { .fill="WAntiTagFakeRate_vs_JetAK8PtBins",        .pfs={"Data_MC",cut1,"Syst","AK8_EB_EE"},         .cuts={},.draw="PE1",.opt=o_1or2d_d+"AddRatio",.ranges={}});
//TEMP      sh.AddHistos(s+"AK8", { .fill="Top0BMassTagFakeRate_vs_JetAK8PtBins",    .pfs={"Data_MC",cut1,"Syst"},                     .cuts={},.draw="PE1",.opt=o_1or2d_d+"AddRatio",.ranges={400,2000, 0,0}});
//TEMP      sh.AddHistos(s+"AK8", { .fill="Top0BMassTagFakeRate_vs_JetAK8PtBins",    .pfs={"Data_MC",cut1,"Syst","AK8_EB_EE"},         .cuts={},.draw="PE1",.opt=o_1or2d_d+"AddRatio",.ranges={400,2000, 0,0}});
//TEMP      sh.AddHistos(s+"AK8", { .fill="TopAntiTagFakeRate_vs_JetAK8PtBins",      .pfs={"Data_MC",cut1,"Syst"},                     .cuts={},.draw="PE1",.opt=o_1or2d_d+"AddRatio",.ranges={400,2000, 0,0}});
//TEMP      sh.AddHistos(s+"AK8", { .fill="TopAntiTagFakeRate_vs_JetAK8PtBins",      .pfs={"Data_MC",cut1,"Syst","AK8_EB_EE"},         .cuts={},.draw="PE1",.opt=o_1or2d_d+"AddRatio",.ranges={400,2000, 0,0}});
//TEMP      // Other JEC
//TEMP      sh.AddHistos(s+"AK8", { .fill="WTagOtherFakeRate_vs_JetAK8PtBins",            .pfs={"Data_MC",cut1,"Syst"},                     .cuts={},.draw="PE1",.opt=o_1or2d_d+"AddRatio",.ranges={}});
//TEMP      sh.AddHistos(s+"AK8", { .fill="WTagOtherFakeRate_vs_JetAK8PtBins",            .pfs={"Data_MC",cut1,"Syst","AK8_EB_EE"},         .cuts={},.draw="PE1",.opt=o_1or2d_d+"AddRatio",.ranges={}});
//TEMP      sh.AddHistos(s+"AK8", { .fill="W0BMassTagOtherFakeRate_vs_JetAK8PtBins",      .pfs={"Data_MC",cut1,"Syst"},                     .cuts={},.draw="PE1",.opt=o_1or2d_d+"AddRatio",.ranges={}});
//TEMP      sh.AddHistos(s+"AK8", { .fill="W0BMassTagOtherFakeRate_vs_JetAK8PtBins",      .pfs={"Data_MC",cut1,"Syst","AK8_EB_EE"},         .cuts={},.draw="PE1",.opt=o_1or2d_d+"AddRatio",.ranges={}});
//TEMP      sh.AddHistos(s+"AK8", { .fill="WAntiTagOtherFakeRate_vs_JetAK8PtBins",        .pfs={"Data_MC",cut1,"Syst"},                     .cuts={},.draw="PE1",.opt=o_1or2d_d+"AddRatio",.ranges={}});
//TEMP      sh.AddHistos(s+"AK8", { .fill="WAntiTagOtherFakeRate_vs_JetAK8PtBins",        .pfs={"Data_MC",cut1,"Syst","AK8_EB_EE"},         .cuts={},.draw="PE1",.opt=o_1or2d_d+"AddRatio",.ranges={}});
//TEMP      sh.AddHistos(s+"AK8", { .fill="Top0BMassTagOtherFakeRate_vs_JetAK8PtBins",    .pfs={"Data_MC",cut1,"Syst"},                     .cuts={},.draw="PE1",.opt=o_1or2d_d+"AddRatio",.ranges={400,2000, 0,0}});
//TEMP      sh.AddHistos(s+"AK8", { .fill="Top0BMassTagOtherFakeRate_vs_JetAK8PtBins",    .pfs={"Data_MC",cut1,"Syst","AK8_EB_EE"},         .cuts={},.draw="PE1",.opt=o_1or2d_d+"AddRatio",.ranges={400,2000, 0,0}});
//TEMP      sh.AddHistos(s+"AK8", { .fill="TopAntiTagOtherFakeRate_vs_JetAK8PtBins",      .pfs={"Data_MC",cut1,"Syst"},                     .cuts={},.draw="PE1",.opt=o_1or2d_d+"AddRatio",.ranges={400,2000, 0,0}});
//TEMP      sh.AddHistos(s+"AK8", { .fill="TopAntiTagOtherFakeRate_vs_JetAK8PtBins",      .pfs={"Data_MC",cut1,"Syst","AK8_EB_EE"},         .cuts={},.draw="PE1",.opt=o_1or2d_d+"AddRatio",.ranges={400,2000, 0,0}});
//TEMP  
//TEMP      // Top fakes (without b-tag veto)
//TEMP      //sh.SetHistoWeights({ [this,region] { return w_nm1[region][all_weights.size()+2]; } }); // exclude also btag scale factors
//TEMP      sh.SetHistoWeights({ [this,region] { 
//TEMP  			   double w = 1;
//TEMP  			   if (!isData) {
//TEMP  			     for (size_t i=0; i<8; i++) w *= all_weights[i]; // N-1 for trigger eff ([8])
//TEMP  			     for (size_t j=0; j<2; j++) w *= scale_factors[region][j]; // N-1 for btag scale_factor
//TEMP  			     w *= other_trigger_eff;
//TEMP  			   }
//TEMP  			   return w;
//TEMP  			 } });
//TEMP      sh.AddHistos(s+"AK8", { .fill="TopTagFakeRate_vs_JetAK8PtBins",          .pfs={"Data_MC",cut2,"Syst"},              .cuts={},.draw="PE1",.opt=o_1or2d_d+"AddRatio",.ranges={400,2000, 0,0}});
//TEMP      sh.AddHistos(s+"AK8", { .fill="TopTagFakeRate_vs_JetAK8PtBins",          .pfs={"Data_MC",cut2,"Syst","AK8_EB_EE"},  .cuts={},.draw="PE1",.opt=o_1or2d_d+"AddRatio",.ranges={400,2000, 0,0}});
//TEMP      sh.AddHistos(s+"AK8", { .fill="TopMassTagFakeRate_vs_JetAK8PtBins",      .pfs={"Data_MC",cut2,"Syst"},              .cuts={},.draw="PE1",.opt=o_1or2d_d+"AddRatio",.ranges={400,2000, 0,0}});
//TEMP      sh.AddHistos(s+"AK8", { .fill="TopMassTagFakeRate_vs_JetAK8PtBins",      .pfs={"Data_MC",cut2,"Syst","AK8_EB_EE"},  .cuts={},.draw="PE1",.opt=o_1or2d_d+"AddRatio",.ranges={400,2000, 0,0}});
//TEMP      // Other JEC
//TEMP      sh.AddHistos(s+"AK8", { .fill="TopTagOtherFakeRate_vs_JetAK8PtBins",          .pfs={"Data_MC",cut2,"Syst"},              .cuts={},.draw="PE1",.opt=o_1or2d_d+"AddRatio",.ranges={400,2000, 0,0}});
//TEMP      sh.AddHistos(s+"AK8", { .fill="TopTagOtherFakeRate_vs_JetAK8PtBins",          .pfs={"Data_MC",cut2,"Syst","AK8_EB_EE"},  .cuts={},.draw="PE1",.opt=o_1or2d_d+"AddRatio",.ranges={400,2000, 0,0}});
//TEMP      sh.AddHistos(s+"AK8", { .fill="TopMassTagOtherFakeRate_vs_JetAK8PtBins",      .pfs={"Data_MC",cut2,"Syst"},              .cuts={},.draw="PE1",.opt=o_1or2d_d+"AddRatio",.ranges={400,2000, 0,0}});
//TEMP      sh.AddHistos(s+"AK8", { .fill="TopMassTagOtherFakeRate_vs_JetAK8PtBins",      .pfs={"Data_MC",cut2,"Syst","AK8_EB_EE"},  .cuts={},.draw="PE1",.opt=o_1or2d_d+"AddRatio",.ranges={400,2000, 0,0}});
//TEMP    }
//TEMP  
//TEMP    // -------------------------------------------------------------------------
//TEMP    //                               GenInfo
//TEMP  
//TEMP    sh.SetHistoWeights({ [] { return 1; } });
//TEMP    // FullSim/FastSim scale factors
//TEMP  
//TEMP    // No Weight
//TEMP    // Efficiency - gen pt
//TEMP    sh.AddHistos("gen hadW",   { .fill="GenHadWPt",                                         .pfs={"TT_SignalPoints"},                      .cuts={}, .draw=d,    .opt=o_1or2d_s+"Norm",     .ranges={0,2000, 0,0, 0.3,0.86}});
//TEMP    sh.AddHistos("gen hadtop", { .fill="GenHadTopPt",                                          .pfs={"TT_SignalPoints"},                      .cuts={}, .draw=d,    .opt=o_1or2d_s+"Norm",     .ranges={0,2000, 0,0, 0.3,0.86}});
//TEMP    //sh.AddHistos("gen hadW",   { .fill="WTaggingEfficiency_vs_GenHadWPtBins",                  .pfs={"FullFastSim"},                          .cuts={}, .draw="PE1",.opt=o_1or2d_s+"AddRatio", .ranges={0,2000, 0,0}});
//TEMP    //sh.AddHistos("gen hadW",   { .fill="WTaggingEfficiency_vs_GenHadWPtBins",                  .pfs={"FullFastSim","GenHadWMatchedAK8_EB_EE"},   .cuts={}, .draw="PE1",.opt=o_1or2d_s+"AddRatio", .ranges={0,2000, 0,0}});
//TEMP    //sh.AddHistos("gen hadtop", { .fill="HadTopTaggingEfficiency_vs_GenHadTopPtBins",              .pfs={"FullFastSim"},                          .cuts={}, .draw="PE1",.opt=o_1or2d_s+"AddRatio", .ranges={0,2000, 0,0}});
//TEMP    //sh.AddHistos("gen hadtop", { .fill="HadTopTaggingEfficiency_vs_GenHadTopPtBins",              .pfs={"FullFastSim","GenHadTopMatchedAK8_EB_EE"}, .cuts={}, .draw="PE1",.opt=o_1or2d_s+"AddRatio", .ranges={0,2000, 0,0}});
//TEMP    //sh.AddHistos("gen hadW",   { .fill="WTaggingEfficiency_vs_GenHadWPtBins",                  .pfs={"FullFastSim","P","NoWeight"},                          .cuts={}, .draw="PE1",.opt=o_1or2d_s+"AddRatio", .ranges={0,2000, 0,0}});
//TEMP    //sh.AddHistos("gen hadW",   { .fill="WTaggingEfficiency_vs_GenHadWPtBins",                  .pfs={"FullFastSim","P","NoWeight","GenHadWMatchedAK8_EB_EE"},   .cuts={}, .draw="PE1",.opt=o_1or2d_s+"AddRatio", .ranges={0,2000, 0,0}});
//TEMP    //sh.AddHistos("gen hadtop", { .fill="HadTopTaggingEfficiency_vs_GenHadTopPtBins",              .pfs={"FullFastSim","P","NoWeight"},                          .cuts={}, .draw="PE1",.opt=o_1or2d_s+"AddRatio", .ranges={0,2000, 0,0}});
//TEMP    //sh.AddHistos("gen hadtop", { .fill="HadTopTaggingEfficiency_vs_GenHadTopPtBins",              .pfs={"FullFastSim","P","NoWeight","GenHadTopMatchedAK8_EB_EE"}, .cuts={}, .draw="PE1",.opt=o_1or2d_s+"AddRatio", .ranges={0,2000, 0,0}});
//TEMP    //
//TEMP    //// Efficiency - jet pt
//TEMP    //sh.AddHistos("gen hadW",   { .fill="WTaggingEfficiency_vs_GenHadWMatchedAK8JetPtBins",         .pfs={"FullFastSim"},                          .cuts={}, .draw="PE1",.opt=o_1or2d_s+"AddRatio", .ranges={200,2000, 0,0}});
//TEMP    //sh.AddHistos("gen hadW",   { .fill="WTaggingEfficiency_vs_GenHadWMatchedAK8JetPtBins",         .pfs={"FullFastSim","GenHadWMatchedAK8_EB_EE"},   .cuts={}, .draw="PE1",.opt=o_1or2d_s+"AddRatio", .ranges={200,2000, 0,0}});
//TEMP    //sh.AddHistos("gen hadtop", { .fill="HadTopTaggingEfficiency_vs_GenHadTopMatchedAK8JetPtBins",     .pfs={"FullFastSim"},                          .cuts={}, .draw="PE1",.opt=o_1or2d_s+"AddRatio", .ranges={400,2000, 0,0}});
//TEMP    //sh.AddHistos("gen hadtop", { .fill="HadTopTaggingEfficiency_vs_GenHadTopMatchedAK8JetPtBins",     .pfs={"FullFastSim","GenHadTopMatchedAK8_EB_EE"}, .cuts={}, .draw="PE1",.opt=o_1or2d_s+"AddRatio", .ranges={400,2000, 0,0}});
//TEMP    //sh.AddHistos("gen hadW",   { .fill="WTaggingEfficiency_vs_GenHadWMatchedAK8JetPtBins",         .pfs={"FullFastSim","P","NoWeight"},                          .cuts={}, .draw="PE1",.opt=o_1or2d_s+"AddRatio", .ranges={200,2000, 0,0}});
//TEMP    //sh.AddHistos("gen hadW",   { .fill="WTaggingEfficiency_vs_GenHadWMatchedAK8JetPtBins",         .pfs={"FullFastSim","P","NoWeight","GenHadWMatchedAK8_EB_EE"},   .cuts={}, .draw="PE1",.opt=o_1or2d_s+"AddRatio", .ranges={200,2000, 0,0}});
//TEMP    //sh.AddHistos("gen hadtop", { .fill="HadTopTaggingEfficiency_vs_GenHadTopMatchedAK8JetPtBins",     .pfs={"FullFastSim","P","NoWeight"},                          .cuts={}, .draw="PE1",.opt=o_1or2d_s+"AddRatio", .ranges={400,2000, 0,0}});
//TEMP    //sh.AddHistos("gen hadtop", { .fill="HadTopTaggingEfficiency_vs_GenHadTopMatchedAK8JetPtBins",     .pfs={"FullFastSim","P","NoWeight","GenHadTopMatchedAK8_EB_EE"}, .cuts={}, .draw="PE1",.opt=o_1or2d_s+"AddRatio", .ranges={400,2000, 0,0}});
//TEMP    //
//TEMP    //// Mass Tag
//TEMP    //sh.AddHistos("gen hadW",   { .fill="WMassTaggingEfficiency_vs_GenHadWPtBins",              .pfs={"FullFastSim"},                          .cuts={}, .draw="PE1",.opt=o_1or2d_s+"AddRatio", .ranges={0,2000, 0,0}});
//TEMP    //sh.AddHistos("gen hadW",   { .fill="WMassTaggingEfficiency_vs_GenHadWPtBins",              .pfs={"FullFastSim","GenHadWMatchedAK8_EB_EE"},   .cuts={}, .draw="PE1",.opt=o_1or2d_s+"AddRatio", .ranges={0,2000, 0,0}});
//TEMP    //sh.AddHistos("gen hadtop", { .fill="HadTopMassTaggingEfficiency_vs_GenHadTopPtBins",          .pfs={"FullFastSim"},                          .cuts={}, .draw="PE1",.opt=o_1or2d_s+"AddRatio", .ranges={0,2000, 0,0}});
//TEMP    //sh.AddHistos("gen hadtop", { .fill="HadTopMassTaggingEfficiency_vs_GenHadTopPtBins",          .pfs={"FullFastSim","GenHadTopMatchedAK8_EB_EE"}, .cuts={}, .draw="PE1",.opt=o_1or2d_s+"AddRatio", .ranges={0,2000, 0,0}});
//TEMP    //sh.AddHistos("gen hadW",   { .fill="WMassTaggingEfficiency_vs_GenHadWMatchedAK8JetPtBins",     .pfs={"FullFastSim"},                          .cuts={}, .draw="PE1",.opt=o_1or2d_s+"AddRatio", .ranges={200,2000, 0,0}});
//TEMP    //sh.AddHistos("gen hadW",   { .fill="WMassTaggingEfficiency_vs_GenHadWMatchedAK8JetPtBins",     .pfs={"FullFastSim","GenHadWMatchedAK8_EB_EE"},   .cuts={}, .draw="PE1",.opt=o_1or2d_s+"AddRatio", .ranges={200,2000, 0,0}});
//TEMP    //sh.AddHistos("gen hadtop", { .fill="HadTopMassTaggingEfficiency_vs_GenHadTopMatchedAK8JetPtBins", .pfs={"FullFastSim"},                          .cuts={}, .draw="PE1",.opt=o_1or2d_s+"AddRatio", .ranges={400,2000, 0,0}});
//TEMP    //sh.AddHistos("gen hadtop", { .fill="HadTopMassTaggingEfficiency_vs_GenHadTopMatchedAK8JetPtBins", .pfs={"FullFastSim","GenHadTopMatchedAK8_EB_EE"}, .cuts={}, .draw="PE1",.opt=o_1or2d_s+"AddRatio", .ranges={400,2000, 0,0}});
//TEMP    //
//TEMP    //// Mistag
//TEMP    //sh.AddHistos("AK8",     { .fill="WMisTagRate_vs_JetAK8PtBins",                       .pfs={"FullFastSim","NoMatchGenHadW"},               .cuts={},.draw="PE1",.opt=o_1or2d_s+"AddRatio",.ranges={}});
//TEMP    //sh.AddHistos("AK8",     { .fill="WMisTagRate_vs_JetAK8PtBins",                       .pfs={"FullFastSim","NoMatchGenHadW","AK8_EB_EE"},   .cuts={},.draw="PE1",.opt=o_1or2d_s+"AddRatio",.ranges={}});
//TEMP    //sh.AddHistos("AK8",     { .fill="WMisTagRate_vs_JetAK8PtFewBins",                    .pfs={"FullFastSim","NoMatchGenHadW"},               .cuts={},.draw="PE1",.opt=o_1or2d_s+"AddRatio",.ranges={}});
//TEMP    //sh.AddHistos("AK8",     { .fill="WMisTagRate_vs_JetAK8PtFewBins",                    .pfs={"FullFastSim","NoMatchGenHadW","AK8_EB_EE"},   .cuts={},.draw="PE1",.opt=o_1or2d_s+"AddRatio",.ranges={}});
//TEMP    //sh.AddHistos("AK8",     { .fill="TopMisTagRate_vs_JetAK8PtOneBin",                   .pfs={"FullFastSim","NoMatchGenHadTop"},             .cuts={},.draw="PE1",.opt=o_1or2d_s+"AddRatio",.ranges={}});
//TEMP    //sh.AddHistos("AK8",     { .fill="TopMisTagRate_vs_JetAK8PtOneBin",                   .pfs={"FullFastSim","NoMatchGenHadToph","AK8_EB_EE"}, .cuts={},.draw="PE1",.opt=o_1or2d_s+"AddRatio",.ranges={}});
//TEMP    //sh.AddHistos("AK8",     { .fill="WMisTagRate_vs_JetAK8PtBins",                       .pfs={"FullFastSim","P","NoWeight","NoMatchGenHadW"},               .cuts={},.draw="PE1",.opt=o_1or2d_s+"AddRatio",.ranges={}});
//TEMP    //sh.AddHistos("AK8",     { .fill="WMisTagRate_vs_JetAK8PtBins",                       .pfs={"FullFastSim","P","NoWeight","NoMatchGenHadW","AK8_EB_EE"},   .cuts={},.draw="PE1",.opt=o_1or2d_s+"AddRatio",.ranges={}});
//TEMP    //sh.AddHistos("AK8",     { .fill="WMisTagRate_vs_JetAK8PtFewBins",                    .pfs={"FullFastSim","P","NoWeight","NoMatchGenHadW"},               .cuts={},.draw="PE1",.opt=o_1or2d_s+"AddRatio",.ranges={}});
//TEMP    //sh.AddHistos("AK8",     { .fill="WMisTagRate_vs_JetAK8PtFewBins",                    .pfs={"FullFastSim","P","NoWeight","NoMatchGenHadW","AK8_EB_EE"},   .cuts={},.draw="PE1",.opt=o_1or2d_s+"AddRatio",.ranges={}});
//TEMP    //sh.AddHistos("AK8",     { .fill="TopMisTagRate_vs_JetAK8PtOneBin",                   .pfs={"FullFastSim","P","NoWeight","NoMatchGenHadTop"},             .cuts={},.draw="PE1",.opt=o_1or2d_s+"AddRatio",.ranges={}});
//TEMP    //sh.AddHistos("AK8",     { .fill="TopMisTagRate_vs_JetAK8PtOneBin",                   .pfs={"FullFastSim","P","NoWeight","NoMatchGenHadTop","AK8_EB_EE"}, .cuts={},.draw="PE1",.opt=o_1or2d_s+"AddRatio",.ranges={}});
//TEMP    //
//TEMP    //// With Weight - in P
//TEMP    //sh.SetHistoWeights({ [this] { return sf_weight['P']; } });
//TEMP    //sh.AddHistos("gen hadW",   { .fill="WTaggingEfficiency_vs_GenHadWPtBins",                  .pfs={"FullFastSim","P"},                          .cuts={}, .draw="PE1",.opt=o_1or2d_s+"AddRatio", .ranges={0,2000, 0,0}});
//TEMP    //sh.AddHistos("gen hadW",   { .fill="WTaggingEfficiency_vs_GenHadWPtBins",                  .pfs={"FullFastSim","P","GenHadWMatchedAK8_EB_EE"},   .cuts={}, .draw="PE1",.opt=o_1or2d_s+"AddRatio", .ranges={0,2000, 0,0}});
//TEMP    //sh.AddHistos("gen hadtop", { .fill="HadTopTaggingEfficiency_vs_GenHadTopPtBins",              .pfs={"FullFastSim","P"},                          .cuts={}, .draw="PE1",.opt=o_1or2d_s+"AddRatio", .ranges={0,2000, 0,0}});
//TEMP    //sh.AddHistos("gen hadtop", { .fill="HadTopTaggingEfficiency_vs_GenHadTopPtBins",              .pfs={"FullFastSim","P","GenHadTopMatchedAK8_EB_EE"}, .cuts={}, .draw="PE1",.opt=o_1or2d_s+"AddRatio", .ranges={0,2000, 0,0}});
//TEMP    //sh.AddHistos("gen hadW",   { .fill="WTaggingEfficiency_vs_GenHadWMatchedAK8JetPtBins",     .pfs={"FullFastSim","P"},                          .cuts={}, .draw="PE1",.opt=o_1or2d_s+"AddRatio", .ranges={200,2000, 0,0}});
//TEMP    //sh.AddHistos("gen hadW",   { .fill="WTaggingEfficiency_vs_GenHadWMatchedAK8JetPtBins",     .pfs={"FullFastSim","P","GenHadWMatchedAK8_EB_EE"},   .cuts={}, .draw="PE1",.opt=o_1or2d_s+"AddRatio", .ranges={200,2000, 0,0}});
//TEMP    //sh.AddHistos("gen hadtop", { .fill="HadTopTaggingEfficiency_vs_GenHadTopMatchedAK8JetPtBins", .pfs={"FullFastSim","P"},                          .cuts={}, .draw="PE1",.opt=o_1or2d_s+"AddRatio", .ranges={400,2000, 0,0}});
//TEMP    //sh.AddHistos("gen hadtop", { .fill="HadTopTaggingEfficiency_vs_GenHadTopMatchedAK8JetPtBins", .pfs={"FullFastSim","P","GenHadTopMatchedAK8_EB_EE"}, .cuts={}, .draw="PE1",.opt=o_1or2d_s+"AddRatio", .ranges={400,2000, 0,0}});
//TEMP    //
//TEMP    //sh.AddHistos("AK8",     { .fill="WMisTagRate_vs_JetAK8PtBins",                       .pfs={"FullFastSim","P","NoMatchGenHadW"},               .cuts={},.draw="PE1",.opt=o_1or2d_s+"AddRatio",.ranges={}});
//TEMP    //sh.AddHistos("AK8",     { .fill="WMisTagRate_vs_JetAK8PtBins",                       .pfs={"FullFastSim","P","NoMatchGenHadW","AK8_EB_EE"},   .cuts={},.draw="PE1",.opt=o_1or2d_s+"AddRatio",.ranges={}});
//TEMP    //sh.AddHistos("AK8",     { .fill="WMisTagRate_vs_JetAK8PtFewBins",                    .pfs={"FullFastSim","P","NoMatchGenHadW"},               .cuts={},.draw="PE1",.opt=o_1or2d_s+"AddRatio",.ranges={}});
//TEMP    //sh.AddHistos("AK8",     { .fill="WMisTagRate_vs_JetAK8PtFewBins",                    .pfs={"FullFastSim","P","NoMatchGenHadW","AK8_EB_EE"},   .cuts={},.draw="PE1",.opt=o_1or2d_s+"AddRatio",.ranges={}});
//TEMP    //sh.AddHistos("AK8",     { .fill="TopMisTagRate_vs_JetAK8PtOneBin",                   .pfs={"FullFastSim","P","NoMatchGenHadTop"},             .cuts={},.draw="PE1",.opt=o_1or2d_s+"AddRatio",.ranges={}});
//TEMP    //sh.AddHistos("AK8",     { .fill="TopMisTagRate_vs_JetAK8PtOneBin",                   .pfs={"FullFastSim","P","NoMatchGenHadTop","AK8_EB_EE"}, .cuts={},.draw="PE1",.opt=o_1or2d_s+"AddRatio",.ranges={}});
//TEMP  
//TEMP  
//TEMP    // With Weight - in S
//TEMP    sh.SetHistoWeights({ [this] { return sf_weight['S']; } });
//TEMP    sh.AddHistos("evt",   { .fill="SignalSelectionEfficiency_vs_MLSP_vs_MGluino",    .pfs={"T5ttcc"},          .cuts={},.draw="COLZ",.opt=o_1or2d_s, .ranges={600,2300, 0,1400, 0,0, 0.02,0.95}});
//TEMP    sh.AddHistos("evt",   { .fill="SignalSelectionEfficiency_vs_MLSP_vs_MGluino",    .pfs={"T1tttt"},          .cuts={},.draw="COLZ",.opt=o_1or2d_s, .ranges={600,2300, 0,1600, 0,0, 0.02,0.95}});
//TEMP    sh.AddHistos("evt",   { .fill="SignalSelectionEfficiency_vs_MLSP_vs_MStop",      .pfs={"T2tt"},            .cuts={},.draw="COLZ",.opt=o_1or2d_s, .ranges={150,1200, 0, 650, 0,0, 0.02,0.95}});
//TEMP  
//TEMP    sh.AddHistos("evt",   { .fill="SignalSignificance_T5ttcc_vs_MLSP_vs_MGluino",         .pfs={"S"},               .cuts={},.draw="COLZ",.opt=o_1or2d_s, .ranges={600,2300, 0,1400, 0,0, 0.02,0.95}});
//TEMP    sh.AddHistos("evt",   { .fill="SignalSignificance_T1tttt_vs_MLSP_vs_MGluino",         .pfs={"S"},               .cuts={},.draw="COLZ",.opt=o_1or2d_s, .ranges={600,2300, 0,1600, 0,0, 0.02,0.95}});
//TEMP    sh.AddHistos("evt",   { .fill="SignalSignificance_T2tt_vs_MLSP_vs_MStop",             .pfs={"S"},               .cuts={},.draw="COLZ",.opt=o_1or2d_s, .ranges={150,1200, 0, 650, 0,0, 0.02,0.95}});
//TEMP  
//TEMP    for (auto njet_bin : {"NJet45"}) {
//TEMP      sh.AddHistos("evt",   { .fill="SignalSelectionEfficiency_vs_MLSP_vs_MGluino",    .pfs={"T5ttcc",njet_bin}, .cuts={},.draw="COLZ",.opt=o_1or2d_s, .ranges={600,2300, 0,1400, 0,0, 0.02,0.95}});
//TEMP      sh.AddHistos("evt",   { .fill="SignalSelectionEfficiency_vs_MLSP_vs_MGluino",    .pfs={"T1tttt",njet_bin}, .cuts={},.draw="COLZ",.opt=o_1or2d_s, .ranges={600,2300, 0,1600, 0,0, 0.02,0.95}});
//TEMP      sh.AddHistos("evt",   { .fill="SignalSelectionEfficiency_vs_MLSP_vs_MStop",      .pfs={"T2tt"  ,njet_bin}, .cuts={},.draw="COLZ",.opt=o_1or2d_s, .ranges={150,1200, 0, 650, 0,0, 0.02,0.95}});
//TEMP      
//TEMP      sh.AddHistos("evt",   { .fill="SignalSignificance_T5ttcc_vs_MLSP_vs_MGluino",         .pfs={"S",njet_bin},      .cuts={},.draw="COLZ",.opt=o_1or2d_s, .ranges={600,2300, 0,1400, 0,0, 0.02,0.95}});
//TEMP      sh.AddHistos("evt",   { .fill="SignalSignificance_T1tttt_vs_MLSP_vs_MGluino",         .pfs={"S",njet_bin},      .cuts={},.draw="COLZ",.opt=o_1or2d_s, .ranges={600,2300, 0,1600, 0,0, 0.02,0.95}});
//TEMP      sh.AddHistos("evt",   { .fill="SignalSignificance_T2tt_vs_MLSP_vs_MStop",             .pfs={"S",njet_bin},      .cuts={},.draw="COLZ",.opt=o_1or2d_s, .ranges={150,1200, 0, 650, 0,0, 0.02,0.95}});
//TEMP    }
//TEMP  
//TEMP    // ----------------------------------------------------------------------------------------------
//TEMP    //                                        TOP ANALYSIS
//TEMP    //-----------------------------------------------------------------------------------------------
//TEMP  
//TEMP    o_stk_d = "LogSumw2Stack1AddRatioTwoCol58AddIntApproval15";
//TEMP    o_stk_s = "LogSumw2Stack1AddRatioTwoCol58AddIntApproval45";
//TEMP    o_1or2d_d = "Sumw2Approval15";
//TEMP    o_1or2d_s = "Sumw2Approval45";
//TEMP    o_norm_d = "Sumw2NormApproval15";
//TEMP    o_norm_s = "Sumw2NormApproval45";
//TEMP  
//TEMP    // -------------------------------------------------------------------------
//TEMP    //                           Selected tops
//TEMP    
//TEMP    for (auto region : {'S', 's', 'T','W','Q', 'q', 'L', 'Z', 'G'}) {
//TEMP      sh.SetHistoWeights({ [this,region] { return sf_weight[region]; } });
//TEMP      std::string cut1 = std::string(1,region);
//TEMP      std::string cut2 = cut1;
//TEMP  #if TOP == 0
//TEMP      if      (region=='S'||region=='s'||region=='T') cut2 += "_Excl1b1W";
//TEMP      else if (region=='Q'||region=='q') cut2 += "_Excl0b1aW";
//TEMP      else if (region=='W'||region=='L') cut2 += "_Excl0b1mW";
//TEMP      else if (region=='Z'||region=='G') cut2 += "_Excl1mW";
//TEMP  #else
//TEMP      if      (region=='S'||region=='s'||region=='T') cut2 += "_Excl1Top";
//TEMP      else if (region=='Q'||region=='q') cut2 += "_Excl0b1aTop";
//TEMP      else if (region=='W'||region=='L') cut2 += "_Excl0b1mTop";
//TEMP      else if (region=='Z'||region=='G') cut2 += "_Excl1MTop";
//TEMP  #endif
//TEMP      std::vector<std::string> showdata = {"JetHTMET"};
//TEMP      if (region=='S') showdata.push_back("Blind");
//TEMP      for (auto cut : { cut1, cut2 }) {
//TEMP        for (auto data : showdata ) {
//TEMP  	std::string opt = (data=="Blind") ? o_stk_s : o_stk_d;
//TEMP  	sh.AddHistos(s+"evt",  { .fill=c+"NTop",         .pfs={Stack,data,cut},                          .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
//TEMP        }
//TEMP        sh.AddHistos("evt",  { .fill="NTop",         .pfs={"MGluinoPoints",  "MLSPPoints","GluinoSignalScans",  cut}, .cuts={},.draw=d,.opt=o_norm_s,.ranges={0,0, 0,1, 0.32,0.86}});
//TEMP        sh.AddHistos("evt",  { .fill="NTop",         .pfs={"MStopPoints",    "MLSPPoints","StopSignalScans",    cut}, .cuts={},.draw=d,.opt=o_norm_s,.ranges={0,0, 0,1, 0.32,0.86}});
//TEMP        sh.AddHistos("evt",  { .fill="NTop",         .pfs={"MCharginoPoints","MLSPPoints","CharginoSignalScans",cut}, .cuts={},.draw=d,.opt=o_norm_s,.ranges={0,0, 0,1, 0.32,0.86}});
//TEMP      }
//TEMP    }
//TEMP  
//TEMP    //std::cout<<"-------------------------------------------------------"<<std::endl;
//TEMP    //std::cout<<"  Total cell count for each SmartHisto:"<<std::endl;
//TEMP    //sh.GetTotalNCells();
//TEMP    //std::cout<<"-------------------------------------------------------"<<std::endl;
}



void
Analysis::fill_analysis_histos(eventBuffer& d, const unsigned int& syst_index, const double& weight)
{
  // SmartHistos
  if (syst_index == 0) { // Default (no systematic variation)
    //__________________________________ 
    //         Fill Smarthistos
    //__________________________________
    
    while(LoopElectron(d))  sh.Fill("ele");
    while(LoopElectron(d)) if (passEleSelect      [i_Electron]) sh.Fill("ele select");
    while(LoopElectron(d)) if (passEleVeto        [i_Electron]) sh.Fill("ele veto");
    while(LoopElectron(d)) if (passEleTightNoIso  [i_Electron]) sh.Fill("ele tight noiso");
    while(LoopMuon(d))     sh.Fill("mu");
    while(LoopMuon(d))     if (passMuSelect       [i_Muon])     sh.Fill("mu select");
    while(LoopMuon(d))     if (passMuVeto         [i_Muon])     sh.Fill("mu veto");
    while(LoopMuon(d))     if (passMuTightNoIso   [i_Muon])     sh.Fill("mu tight noiso");
    while(LoopPhoton(d))   if (passPhotonSelect   [i_Photon])   sh.Fill("pho");
    while(LoopPhoton(d))   if (passPhotonPreSelect[i_Photon])   sh.Fill("prepho");
    while(LoopTau(d))      if (passTauVeto        [i_Tau])      sh.Fill("tau veto");
    while(LoopJet(d))      if (passLooseJet       [i_Jet])      sh.Fill("AK4");
    while(LoopJet(d))      if (passMediumBTag     [i_Jet])      sh.Fill("b");
    while(LoopJet(d))      if (passLooseBTag      [i_Jet])      sh.Fill("b loose");
    while(LoopFatJet(d))   if (passLooseJetAK8    [i_FatJet])   sh.Fill("AK8");
    while(LoopFatJet(d))   if (passWMassTag       [i_FatJet])   sh.Fill("mW");
    while(LoopFatJet(d))   if (passTightWAntiTag  [i_FatJet])   sh.Fill("aW");
    while(LoopFatJet(d))   if (passTightWTag      [i_FatJet])   sh.Fill("W");
    while(LoopFatJet(d))   if (passHadTop0BMassTag[i_FatJet])   sh.Fill("mTop");
    while(LoopFatJet(d))   if (passHadTopMassTag  [i_FatJet])   sh.Fill("MTop");
    while(LoopFatJet(d))   if (passHadTop0BAntiTag[i_FatJet])   sh.Fill("aTop");
    while(LoopFatJet(d))   if (passHadTopTag      [i_FatJet])   sh.Fill("Top");
    while(LoopFatJet(d))   if (passHadW           [i_FatJet])   sh.Fill("hadw");
    while(LoopFatJet(d))   if (passHadZ           [i_FatJet])   sh.Fill("hadz");
    while(LoopFatJet(d))   if (passHadTop         [i_FatJet])   sh.Fill("hadtop");
    while(LoopFatJet(d))   if (passLepTop         [i_FatJet])   sh.Fill("leptop");
    if (!isData) {
      while(LoopGenPart(d))  if (passGenHadW        [i_GenPart])  sh.Fill("gen hadW");
      while(LoopGenPart(d))  if (passGenTop         [i_GenPart])  sh.Fill("gen top");
      while(LoopGenPart(d))  if (passGenHadTop      [i_GenPart])  sh.Fill("gen hadtop");
      while(LoopGenPart(d))  if (passGenLepTop      [i_GenPart])  sh.Fill("gen leptop");
      while(LoopGenPart(d))  if (passGenLepton      [i_GenPart])  sh.Fill("gen lep");
    }
    sh.Fill("evt");
  }

  // Do the same for systematics plots:
  while(LoopElectron(d)) sh.Fill("syst ele");
  while(LoopElectron(d)) if (passEleSelect      [i_Electron]) sh.Fill("syst ele select");
  while(LoopElectron(d)) if (passEleVeto        [i_Electron]) sh.Fill("syst ele veto");
  while(LoopMuon(d))     sh.Fill("syst mu");
  while(LoopMuon(d))     if (passMuSelect       [i_Muon])     sh.Fill("syst mu select");
  while(LoopMuon(d))     if (passMuVeto         [i_Muon])     sh.Fill("syst mu veto");
  while(LoopTau(d))      if (passTauVeto        [i_Tau])      sh.Fill("syst tau veto");
  while(LoopPhoton(d))   if (passPhotonSelect   [i_Photon])   sh.Fill("syst pho");
  while(LoopPhoton(d))   if (passPhotonPreSelect[i_Photon])   sh.Fill("syst prepho");
  while(LoopJet(d))      if (passLooseJet       [i_Jet])      sh.Fill("syst AK4");
  while(LoopJet(d))      if (passMediumBTag     [i_Jet])      sh.Fill("syst b");
  while(LoopJet(d))      if (passLooseBTag      [i_Jet])      sh.Fill("syst b loose");
  while(LoopFatJet(d))   if (passLooseJetAK8    [i_FatJet])   sh.Fill("syst AK8");
  while(LoopFatJet(d))   if (passWMassTag       [i_FatJet])   sh.Fill("syst mW");
  while(LoopFatJet(d))   if (passTightWAntiTag  [i_FatJet])   sh.Fill("syst aW");
  while(LoopFatJet(d))   if (passTightWTag      [i_FatJet])   sh.Fill("syst W");
  while(LoopFatJet(d))   if (passHadTop0BMassTag[i_FatJet])   sh.Fill("syst mTop");
  while(LoopFatJet(d))   if (passHadTopMassTag  [i_FatJet])   sh.Fill("syst MTop");
  while(LoopFatJet(d))   if (passHadTop0BAntiTag[i_FatJet])   sh.Fill("syst aTop");
  while(LoopFatJet(d))   if (passHadTopTag      [i_FatJet])   sh.Fill("syst Top");
  while(LoopFatJet(d))   if (passHadW           [i_FatJet])   sh.Fill("syst hadw");
  while(LoopFatJet(d))   if (passHadZ           [i_FatJet])   sh.Fill("syst hadz");
  while(LoopFatJet(d))   if (passHadTop         [i_FatJet])   sh.Fill("syst hadtop");
  while(LoopFatJet(d))   if (passLepTop         [i_FatJet])   sh.Fill("syst leptop");
  sh.Fill("syst evt");

}


void
Analysis::load_analysis_histos(std::string inputfile)
{
  sh.Add(inputfile.c_str());
}

void
Analysis::save_analysis_histos(bool draw=0)
{
  if (draw) sh.DrawPlots();
  else sh.Write();
}
