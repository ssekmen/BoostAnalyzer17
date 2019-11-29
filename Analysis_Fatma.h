#include "TLorentzVector.h"
#include "TMath.h"
#include "include/AnalysisBase.h"
#include <fstream>
#include <map>






using namespace std;
//_______________________________________________________
//                  Calculate variables./eoscp.sh  WJet /eos/cms/store/user/fboran/RazorBoost/191003/background/WJets/


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
  /*int NJetAK8 = 0;
  for (size_t i=0; i<data.FatJet.size(); ++i) {
    // pt cut intentionally removed to accept all jets for systematics
    if ( (data.FatJet[i].jetId == 2 || data.FatJet[i].jetId == 6) &&
         std::abs(data.FatJet[i].eta)  <  JET_AK8_ETA_CUT ) {
      NJetAK8++;
    }
  }
  if (!(NJetAK8>=1)) return 0;
  //if (!(R2>=0.04)) return 0;

  */
  return 1;
}

/*bool
Analysis::pass_duplicate(eventBuffer& data)
{
  bool isMET = TString(sample).Contains("MET");
  if(isMET){
    ifstream f1;
    f1.open("inclue/Duplicate.txt");
    int RunDuplicate, LumiDuplicate;
    ulong EventDuplicate;
    map <pair<int, int>, int> duplicate_map;
    while(1){
      if (!f1.good()) break;
      duplicate_map.insert(make_pair(make_pair(RunDuplicate,LumiDuplicate),EventDuplicate));
    }
    auto it4 = duplicate_map.find(make_pair(data.run,data.luminosityBlock));
    if(it4 != duplicate_map.end()){
      if(data.event == duplicate_map[make_pair(data.run,data.luminosityBlock)]) return 0;
    }
    f1.close();
  }
  return 1;
}

*/

//_______________________________________________________
//          Define Analysis event selection cuts
//     Can define all sorts of Signal/Control regions

void
Analysis::define_selections(const eventBuffer& d)
{
  analysis_cuts.clear();



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




 // Define here cuts that are include in all Signal/Control regions
  // MET Filters, etc. are already applied in AnalysisBase.h, See baseline_cuts

  // cut0: signal mass region

    // cut0: signal mass region

    bool isT6bbZH = TString(sample).Contains("T6bbZH");
       if(isT6bbZH){
         baseline_cuts.push_back({ .name="signal_mass_selection",   .func = []{
             return susy_mass.at(0)==1200 && susy_mass.at(1)==200 && susy_mass.at(2)==700;
             } });}


    //bool isT6bbZH = TString(sample).Contains("T6bbZH");
    //if(isT6bbZH){
        //	baseline_cuts.push_back({ .name="signal_mass_selection",   .func = []{
            //	return susy_mass.at(0)==1100 && susy_mass.at(1)==300 && susy_mass.at(2)==700;
            //	} });}



   // bool isT6bbZH = TString(sample).Contains("T6bbZH");
    // if(isT6bbZH){
      //	baseline_cuts.push_back({ .name="signal_mass_selection",   .func = []{
      //      return susy_mass.at(0)==1200 && susy_mass.at(1)==700 && susy_mass.at(2)==1100;
      //	    } });}



   // bool isT6bbZH = TString(sample).Contains("T6bbZH");
    //if(isT6bbZH){
     //baseline_cuts.push_back({ .name="signal_mass_selection",   .func = []{
          //return susy_mass.at(0)==1200 && susy_mass.at(1)==200 && susy_mass.at(2)==1000;
         // } });}




	bool isTChiWH = TString(sample).Contains("TChiWH");
	if(isTChiWH){
		baseline_cuts.push_back({ .name="signal_mass_selection",   .func = []{
				return susy_mass.at(0)==900 && susy_mass.at(1)==200;
				} });}



bool isT5qqqqZH = TString(sample).Contains("T5qqqqZH");
if(isT5qqqqZH){
baseline_cuts.push_back({ .name="signal_mass_selection",   .func = []{
return susy_mass.at(0)==2000 && susy_mass.at(1)==1950;
 } });}

 bool isTChiHH = TString(sample).Contains("TChiHH");
 if(isTChiHH){
 baseline_cuts.push_back({ .name="signal_mass_selection",   .func = []{
 return susy_mass.at(0)==900 && susy_mass.at(1)==200;
  } });}


// {
   analysis_cuts.clear();

  // Define here cuts that are include in all Signal/Control regions
  // MET Filters, etc. are already applied in AnalysisBase.h, See baseline_cuts




      // New (Z - Higgs)  signal regions
       // Hadronic selection
       // 0: had 1H b 4-5 jet
       // 1: had 1H b 6+ jet
       // 2: had 2H b 5+ jet
       // 3: had HV b 5+ jet
       // 4: had 1H 0b 3-4 jet
       // 5: had 1H 0b 5+ jet
       // 6: had 2H 0b 2-4 jet
       // 7: had 2H 0b 5+ jet
       // 8: had HV 0b 2-4 jet
       // 9: had HV 0b 5+ jet

       // Leptonic selection
       // A: lep 1H b 3+ jet
       // B: lep 1H 0b 2+ jet
       // C: lepjet 1H






       // had H b 4-5 jet
  analysis_cuts['0'].push_back({ .name="1JetAK8",    .func = []    { return nJetAK8>=1;                       }});
  analysis_cuts['0'].push_back({ .name="NJet",       .func = []    { return nJet==4||nJet==5;                 }}); // Tighter than presel
  analysis_cuts['0'].push_back({ .name="MR",         .func = []    { return MR>=800;                          }});
  analysis_cuts['0'].push_back({ .name="R2",         .func = []    { return R2>=0.08;                         }});
  analysis_cuts['0'].push_back({ .name="HLT",        .func =                boost_triggers                     });
  analysis_cuts['0'].push_back({ .name="0Ele",       .func = []    { return nEleVeto==0;                      }});
  analysis_cuts['0'].push_back({ .name="0Mu",        .func = []    { return nMuVeto==0;                       }});
  analysis_cuts['0'].push_back({ .name="0Tau",       .func = []    { return nTauVeto==0;                      }});
  analysis_cuts['0'].push_back({ .name="0LepJet",    .func = []    { return nLepJet==0;                       }});
  analysis_cuts['0'].push_back({ .name="0LepTop",    .func = []    { return nLepTop==0;                       }});
  analysis_cuts['0'].push_back({ .name="dPhi",       .func = []    { return dPhiRazor<2.8;                    }});
  analysis_cuts['0'].push_back({ .name="0HadTop",    .func = []    { return nHadTop==0;                       }}); // Additional
  analysis_cuts['0'].push_back({ .name="1b",         .func = []    { return nMediumIsoBTag>=1;                }}); // Additional
  analysis_cuts['0'].push_back({ .name="1HadH",      .func = []    { return nHadH>=1;                         }}); // Additional



  // had H b 6+ jet
analysis_cuts['1'].push_back({ .name="1JetAK8",    .func = []    { return nJetAK8>=1;                       }});
analysis_cuts['1'].push_back({ .name="NJet",       .func = []    { return nJet>=6;                          }}); // Tighter than presel
analysis_cuts['1'].push_back({ .name="MR",         .func = []    { return MR>=800;                          }});
analysis_cuts['1'].push_back({ .name="R2",         .func = []    { return R2>=0.08;                         }});
analysis_cuts['1'].push_back({ .name="HLT",        .func =                boost_triggers                     });
analysis_cuts['1'].push_back({ .name="0Ele",       .func = []    { return nEleVeto==0;                      }});
analysis_cuts['1'].push_back({ .name="0Mu",        .func = []    { return nMuVeto==0;                       }});
analysis_cuts['1'].push_back({ .name="0Tau",       .func = []    { return nTauVeto==0;                      }});
analysis_cuts['1'].push_back({ .name="0LepJet",    .func = []    { return nLepJet==0;                       }});
analysis_cuts['1'].push_back({ .name="0LepTop",    .func = []    { return nLepTop==0;                       }});
analysis_cuts['1'].push_back({ .name="dPhi",       .func = []    { return dPhiRazor<2.8;                    }});
analysis_cuts['1'].push_back({ .name="0HadTop",    .func = []    { return nHadTop==0;                       }}); // Additional
analysis_cuts['1'].push_back({ .name="1b",         .func = []    { return nMediumIsoBTag>=1;                }}); // Additional
analysis_cuts['1'].push_back({ .name="1HadH",      .func = []    { return nHadH==1;                          }}); // Additional


// had 2H b 5+ jet
analysis_cuts['2'].push_back({ .name="1JetAK8",    .func = []    { return nJetAK8>=1;                       }});
analysis_cuts['2'].push_back({ .name="NJet",       .func = []    { return nJet>=5;                          }}); // Tighter than presel
analysis_cuts['2'].push_back({ .name="MR",         .func = []    { return MR>=800;                          }});
analysis_cuts['2'].push_back({ .name="R2",         .func = []    { return R2>=0.08;                         }});
analysis_cuts['2'].push_back({ .name="HLT",        .func =                boost_triggers                     });
analysis_cuts['2'].push_back({ .name="0Ele",       .func = []    { return nEleVeto==0;                      }});
analysis_cuts['2'].push_back({ .name="0Mu",        .func = []    { return nMuVeto==0;                       }});
analysis_cuts['2'].push_back({ .name="0Tau",       .func = []    { return nTauVeto==0;                      }});
analysis_cuts['2'].push_back({ .name="0LepJet",    .func = []    { return nLepJet==0;                       }});
analysis_cuts['2'].push_back({ .name="0LepTop",    .func = []    { return nLepTop==0;                       }});
analysis_cuts['2'].push_back({ .name="dPhi",       .func = []    { return dPhiRazor<2.8;                    }});
analysis_cuts['2'].push_back({ .name="0HadTop",    .func = []    { return nHadTop==0;                       }}); // Additional
analysis_cuts['2'].push_back({ .name="1b",         .func = []    { return nMediumIsoBTag>=1;                }}); // Additional
analysis_cuts['2'].push_back({ .name="1HadH",      .func = []    { return nHadH>=2;                         }}); // Additional

// had HV b 5+ jet
analysis_cuts['3'].push_back({ .name="1JetAK8",    .func = []    { return nJetAK8>=1;                       }});
analysis_cuts['3'].push_back({ .name="NJet",       .func = []    { return nJet>=5;                          }}); // Tighter than presel
analysis_cuts['3'].push_back({ .name="MR",         .func = []    { return MR>=800;                          }});
analysis_cuts['3'].push_back({ .name="R2",         .func = []    { return R2>=0.08;                         }});
analysis_cuts['3'].push_back({ .name="HLT",        .func =                boost_triggers                     });
analysis_cuts['3'].push_back({ .name="0Ele",       .func = []    { return nEleVeto==0;                      }});
analysis_cuts['3'].push_back({ .name="0Mu",        .func = []    { return nMuVeto==0;                       }});
analysis_cuts['3'].push_back({ .name="0Tau",       .func = []    { return nTauVeto==0;                      }});
analysis_cuts['3'].push_back({ .name="0LepJet",    .func = []    { return nLepJet==0;                       }});
analysis_cuts['3'].push_back({ .name="0LepTop",    .func = []    { return nLepTop==0;                       }});
analysis_cuts['3'].push_back({ .name="dPhi",       .func = []    { return dPhiRazor<2.8;                    }});
analysis_cuts['3'].push_back({ .name="0HadTop",    .func = []    { return nHadTop==0;                       }}); // Additional
analysis_cuts['3'].push_back({ .name="1b",         .func = []    { return nMediumIsoBTag>=1;                }}); // Additional
analysis_cuts['3'].push_back({ .name="1HadV",      .func = []    { return nHadV==1;                         }}); // Additional
analysis_cuts['3'].push_back({ .name="1HadH",      .func = []    { return nHadH==1;                          }}); // Additional

// had 1H 0b 3-4 jet
analysis_cuts['4'].push_back({ .name="1JetAK8",    .func = []    { return nJetAK8>=1;                       }});
analysis_cuts['4'].push_back({ .name="NJet",       .func = []    { return nJet==3||nJet==4;                 }}); // Tighter than presel
analysis_cuts['4'].push_back({ .name="MR",         .func = []    { return MR>=800;                          }});
analysis_cuts['4'].push_back({ .name="R2",         .func = []    { return R2>=0.08;                         }});
analysis_cuts['4'].push_back({ .name="HLT",        .func =                boost_triggers                    });
analysis_cuts['4'].push_back({ .name="0Ele",       .func = []    { return nEleVeto==0;                      }});
analysis_cuts['4'].push_back({ .name="0Mu",        .func = []    { return nMuVeto==0;                       }});
analysis_cuts['4'].push_back({ .name="0Tau",       .func = []    { return nTauVeto==0;                      }});
analysis_cuts['4'].push_back({ .name="0LepJet",    .func = []    { return nLepJet==0;                       }});
analysis_cuts['4'].push_back({ .name="0LepTop",    .func = []    { return nLepTop==0;                       }});
analysis_cuts['4'].push_back({ .name="dPhi",       .func = []    { return dPhiRazor<2.8;                    }});
analysis_cuts['4'].push_back({ .name="0HadTop",    .func = []    { return nHadTop==0;                       }}); // Additional
analysis_cuts['4'].push_back({ .name="0isob",      .func = []    { return nLooseIsoBTag==0;                 }});
analysis_cuts['4'].push_back({ .name="1HadH",      .func = []    { return nHadH==1;                          }}); // Additional


// had 1H 0b 5+ jet
analysis_cuts['5'].push_back({ .name="1JetAK8",    .func = []    { return nJetAK8>=1;                       }});
analysis_cuts['5'].push_back({ .name="NJet",       .func = []    { return nJet>=5;                           }}); // Tighter than presel
analysis_cuts['5'].push_back({ .name="MR",         .func = []    { return MR>=800;                          }});
analysis_cuts['5'].push_back({ .name="R2",         .func = []    { return R2>=0.08;                         }});
analysis_cuts['5'].push_back({ .name="HLT",        .func =                boost_triggers                    });
analysis_cuts['5'].push_back({ .name="0Ele",       .func = []    { return nEleVeto==0;                      }});
analysis_cuts['5'].push_back({ .name="0Mu",        .func = []    { return nMuVeto==0;                       }});
analysis_cuts['5'].push_back({ .name="0Tau",       .func = []    { return nTauVeto==0;                      }});
analysis_cuts['5'].push_back({ .name="0LepJet",    .func = []    { return nLepJet==0;                       }});
analysis_cuts['5'].push_back({ .name="0LepTop",    .func = []    { return nLepTop==0;                       }});
analysis_cuts['5'].push_back({ .name="dPhi",       .func = []    { return dPhiRazor<2.8;                    }});
analysis_cuts['5'].push_back({ .name="0HadTop",    .func = []    { return nHadTop==0;                       }}); // Additional
analysis_cuts['5'].push_back({ .name="0isob",      .func = []    { return nLooseIsoBTag==0;                 }});
analysis_cuts['5'].push_back({ .name="1HadH",      .func = []    { return nHadH==1;                          }}); // Additional

// had 2H 0b 2-4 jet
analysis_cuts['6'].push_back({ .name="1JetAK8",    .func = []    { return nJetAK8>=1;                       }});
analysis_cuts['6'].push_back({ .name="NJet",       .func = []    { return nJet==2||nJet==4;                 }}); // Tighter than presel
analysis_cuts['6'].push_back({ .name="MR",         .func = []    { return MR>=800;                          }});
analysis_cuts['6'].push_back({ .name="R2",         .func = []    { return R2>=0.08;                         }});
analysis_cuts['6'].push_back({ .name="HLT",        .func =                boost_triggers                    });
analysis_cuts['6'].push_back({ .name="0Ele",       .func = []    { return nEleVeto==0;                      }});
analysis_cuts['6'].push_back({ .name="0Mu",        .func = []    { return nMuVeto==0;                       }});
analysis_cuts['6'].push_back({ .name="0Tau",       .func = []    { return nTauVeto==0;                      }});
analysis_cuts['6'].push_back({ .name="0LepJet",    .func = []    { return nLepJet==0;                       }});
analysis_cuts['6'].push_back({ .name="0LepTop",    .func = []    { return nLepTop==0;                       }});
analysis_cuts['6'].push_back({ .name="dPhi",       .func = []    { return dPhiRazor<2.8;                    }});
analysis_cuts['6'].push_back({ .name="0HadTop",    .func = []    { return nHadTop==0;                       }}); // Additional
analysis_cuts['6'].push_back({ .name="0isob",      .func = []    { return nLooseIsoBTag==0;                 }});
analysis_cuts['6'].push_back({ .name="1HadH",      .func = []    { return nHadH>=2;                         }}); // Additional

// had 2H 0b 5+ jet
analysis_cuts['7'].push_back({ .name="1JetAK8",    .func = []    { return nJetAK8>=1;                       }});
analysis_cuts['7'].push_back({ .name="NJet",       .func = []    { return nJet>=5;                           }}); // Tighter than presel
analysis_cuts['7'].push_back({ .name="MR",         .func = []    { return MR>=800;                          }});
analysis_cuts['7'].push_back({ .name="R2",         .func = []    { return R2>=0.08;                         }});
analysis_cuts['7'].push_back({ .name="HLT",        .func =                boost_triggers                    });
analysis_cuts['7'].push_back({ .name="0Ele",       .func = []    { return nEleVeto==0;                      }});
analysis_cuts['7'].push_back({ .name="0Mu",        .func = []    { return nMuVeto==0;                       }});
analysis_cuts['7'].push_back({ .name="0Tau",       .func = []    { return nTauVeto==0;                      }});
analysis_cuts['7'].push_back({ .name="0LepJet",    .func = []    { return nLepJet==0;                       }});
analysis_cuts['7'].push_back({ .name="0LepTop",    .func = []    { return nLepTop==0;                       }});
analysis_cuts['7'].push_back({ .name="dPhi",       .func = []    { return dPhiRazor<2.8;                    }});
analysis_cuts['7'].push_back({ .name="0HadTop",    .func = []    { return nHadTop==0;                       }}); // Additional
analysis_cuts['7'].push_back({ .name="0isob",      .func = []    { return nLooseIsoBTag==0;                 }});
analysis_cuts['7'].push_back({ .name="1HadH",      .func = []    { return nHadH>=2;                         }}); // Additional

// had HV 0b 2-4 jet
analysis_cuts['8'].push_back({ .name="1JetAK8",    .func = []    { return nJetAK8>=1;                       }});
analysis_cuts['8'].push_back({ .name="NJet",       .func = []    { return nJet==2||nJet==4;                 }}); // Tighter than presel
analysis_cuts['8'].push_back({ .name="MR",         .func = []    { return MR>=800;                          }});
analysis_cuts['8'].push_back({ .name="R2",         .func = []    { return R2>=0.08;                         }});
analysis_cuts['8'].push_back({ .name="HLT",        .func =                boost_triggers                    });
analysis_cuts['8'].push_back({ .name="0Ele",       .func = []    { return nEleVeto==0;                      }});
analysis_cuts['8'].push_back({ .name="0Mu",        .func = []    { return nMuVeto==0;                       }});
analysis_cuts['8'].push_back({ .name="0Tau",       .func = []    { return nTauVeto==0;                      }});
analysis_cuts['8'].push_back({ .name="0LepJet",    .func = []    { return nLepJet==0;                       }});
analysis_cuts['8'].push_back({ .name="0LepTop",    .func = []    { return nLepTop==0;                       }});
analysis_cuts['8'].push_back({ .name="dPhi",       .func = []    { return dPhiRazor<2.8;                    }});
analysis_cuts['8'].push_back({ .name="0HadTop",    .func = []    { return nHadTop==0;                       }}); // Additional
analysis_cuts['8'].push_back({ .name="0isob",      .func = []    { return nLooseIsoBTag==0;                 }});
analysis_cuts['8'].push_back({ .name="1HadV",      .func = []    { return nHadV>=1;                         }}); // Additional
analysis_cuts['8'].push_back({ .name="1HadH",      .func = []    { return nHadH>=1;                         }}); // Additional




// had HV 0b 5+ jet
analysis_cuts['9'].push_back({ .name="1JetAK8",    .func = []    { return nJetAK8>=1;                       }});
analysis_cuts['9'].push_back({ .name="NJet",       .func = []    { return nJet>=5;                           }}); // Tighter than presel
analysis_cuts['9'].push_back({ .name="MR",         .func = []    { return MR>=800;                          }});
analysis_cuts['9'].push_back({ .name="R2",         .func = []    { return R2>=0.08;                         }});
analysis_cuts['9'].push_back({ .name="HLT",        .func =                boost_triggers                    });
analysis_cuts['9'].push_back({ .name="0Ele",       .func = []    { return nEleVeto==0;                      }});
analysis_cuts['9'].push_back({ .name="0Mu",        .func = []    { return nMuVeto==0;                       }});
analysis_cuts['9'].push_back({ .name="0Tau",       .func = []    { return nTauVeto==0;                      }});
analysis_cuts['9'].push_back({ .name="0LepJet",    .func = []    { return nLepJet==0;                       }});
analysis_cuts['9'].push_back({ .name="0LepTop",    .func = []    { return nLepTop==0;                       }});
analysis_cuts['9'].push_back({ .name="dPhi",       .func = []    { return dPhiRazor<2.8;                    }});
analysis_cuts['9'].push_back({ .name="0HadTop",    .func = []    { return nHadTop==0;                       }}); // Additional
analysis_cuts['9'].push_back({ .name="0isob",      .func = []    { return nLooseIsoBTag==0;                 }});
analysis_cuts['9'].push_back({ .name="1HadV",      .func = []    { return nHadV>=1;                         }}); // Additional
analysis_cuts['9'].push_back({ .name="1HadH",      .func = []    { return nHadH>=1;                         }}); // Additional


// Lep H b 3+ jet
analysis_cuts['A'].push_back({ .name="1JetAK8",    .func = []    { return nJetAK8>=1;                       }});
analysis_cuts['A'].push_back({ .name="NJet",       .func = []    { return nJet>=3;                           }}); // Tighter than presel
analysis_cuts['A'].push_back({ .name="MR",         .func = []    { return MR>=800;                          }});
analysis_cuts['A'].push_back({ .name="R2",         .func = []    { return R2>=0.08;                         }});
analysis_cuts['A'].push_back({ .name="HLT",        .func =                boost_triggers                    });
analysis_cuts['A'].push_back({ .name="1Lep",       .func = []    { return nLepSelect==1;                    }});
analysis_cuts['A'].push_back({ .name="0LepJet",    .func = []    { return nLepJet==0;                       }});
analysis_cuts['A'].push_back({ .name="0LepTop",    .func = []    { return nLepTop==0;                       }});
analysis_cuts['A'].push_back({ .name="MT",         .func = []    { return MT>=120;                          }});
analysis_cuts['A'].push_back({ .name="0HadTop",    .func = []    { return nHadTop==0;                       }}); // Additional
analysis_cuts['A'].push_back({ .name="1b",         .func = []    { return nMediumIsoBTag>=1;                }}); // Additional
analysis_cuts['A'].push_back({ .name="1HadH",      .func = []    { return nHadH>=1;                         }}); // Additional



// Lep H 0b 2+ jet
analysis_cuts['B'].push_back({ .name="1JetAK8",    .func = []    { return nJetAK8>=1;                       }});
analysis_cuts['B'].push_back({ .name="NJet",       .func = []    { return nJet>=2;                           }}); // Tighter than presel
analysis_cuts['B'].push_back({ .name="MR",         .func = []    { return MR>=800;                          }});
analysis_cuts['B'].push_back({ .name="R2",         .func = []    { return R2>=0.08;                         }});
analysis_cuts['B'].push_back({ .name="HLT",        .func =                boost_triggers                    });
analysis_cuts['B'].push_back({ .name="1Lep",       .func = []    { return nLepSelect==1;                    }});
analysis_cuts['B'].push_back({ .name="0LepJet",    .func = []    { return nLepJet==0;                       }});
analysis_cuts['B'].push_back({ .name="0LepTop",    .func = []    { return nLepTop==0;                       }});
analysis_cuts['B'].push_back({ .name="MT",         .func = []    { return MT>=120;                          }});
analysis_cuts['B'].push_back({ .name="0HadTop",    .func = []    { return nHadTop==0;                       }}); // Additional
analysis_cuts['B'].push_back({ .name="0isob",      .func = []    { return nLooseIsoBTag==0;                 }});
analysis_cuts['B'].push_back({ .name="1HadH",      .func = []    { return nHadH>=1;                         }}); // Additional


// LepJet H 0b 3+ jet
// TODO
analysis_cuts['C'].push_back({ .name="1JetAK8",    .func = []    { return nJetAK8>=1;                       }});
analysis_cuts['C'].push_back({ .name="NJet",       .func = []    { return nJet>=3;                           }}); // Tighter than presel
analysis_cuts['C'].push_back({ .name="MR",         .func = []    { return MR>=800;                          }});
analysis_cuts['C'].push_back({ .name="R2",         .func = []    { return R2>=0.08;                         }});
analysis_cuts['C'].push_back({ .name="HLT",        .func =                boost_triggers                    });
analysis_cuts['C'].push_back({ .name="0LepJet",    .func = []    { return nLepJet==0;                       }});
analysis_cuts['C'].push_back({ .name="1LepTop",    .func = []    { return nLepTop>=1;                       }}); // Additional
//analysis_cuts['C'].push_back({ .name="MT",         .func = []    { return MT>=120;                          }});
analysis_cuts['C'].push_back({ .name="1HadTop",    .func = []    { return nHadTop>=1;                       }}); // Additional
analysis_cuts['C'].push_back({ .name="0isob",      .func = []    { return nLooseIsoBTag==0;                 }});
//analysis_cuts['C'].push_back({ .name="1HadH",      .func = []    { return nHadH>=1;                         }}); // Additional


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












}




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
//#if TOP == 0
  // W tagging SF  (4 sigma - fullsim, fastsim, mistag, mistag fastsim)
//  double sf_w = calc_w_tagging_sf(data, nSigmaSFs[i][s], nSigmaSFs[i+1][s], nSigmaSFs[i+2][s], nSigmaSFs[i+3][s], isFastSim);
  // fake W tagging SFs (2 sigma)
 /* double sf_fake_mW = calc_fake_w_mass_tagging_sf(data, nSigmaSFs[i+4][s]);
  double sf_fake_aW = calc_fake_w_anti_tagging_sf(data, nSigmaSFs[i+5][s]);
#endif
  i+=6;
  */

//#if TOP != 0
  // top tagging SF (4 sigma - fullsim, fastsim, mistag, mistag fastsim)
  //   double sf_top = calc_top_tagging_sf(data, nSigmaSFs[i][s], nSigmaSFs[i+1][s], nSigmaSFs[i+2][s], nSigmaSFs[i+3][s], isFastSim);
  // fake top tagging SFs (3 sigmas)

/*  double sf_fake_0b_mTop = calc_fake_top_0b_mass_tagging_sf(data, nSigmaSFs[i+4][s]);
  double sf_fake_MTop = calc_fake_top_mass_tagging_sf(data, nSigmaSFs[i+5][s]);
  double sf_fake_aTop = calc_fake_top_anti_tagging_sf(data, nSigmaSFs[i+6][s]);
//#endif
  i+=7; */

  //double sf_ele_veto=1,  sf_ele_medium=1;
  //double sf_muon_veto=1, sf_muon_medium=1;
  //double sf_btag_loose = 1, sf_btag_medium = 1;
  //double sf_fake_mW=1, sf_fake_aW=1, sf_w=1;
  //double sf_top=1, sf_fake_0b_mTop=1, sf_fake_MTop=1, sf_fake_aTop=1;

// Select scale factors to use
 for (auto& sf : scale_factors) sf.second.clear();



// veto lep 1b
 scale_factors['0'].push_back(sf_ele_veto);
 scale_factors['0'].push_back(sf_muon_veto);
 scale_factors['0'].push_back(sf_btag_medium);
 scale_factors['1'] = scale_factors['2'] = scale_factors['3'] = scale_factors['0'];

 // veto lep, 0b
  scale_factors['4'].push_back(sf_ele_veto);
  scale_factors['4'].push_back(sf_muon_veto);
  scale_factors['4'].push_back(sf_btag_loose);
  scale_factors['5'] = scale_factors['6'] = scale_factors['7'] = scale_factors['8'] = scale_factors['9'] = scale_factors['4'];

  // lep, 1b
  scale_factors['A'].push_back(sf_ele_medium);
  scale_factors['A'].push_back(sf_muon_medium);
  scale_factors['A'].push_back(sf_btag_medium);

  // lep, 0b
  scale_factors['B'].push_back(sf_ele_medium);
  scale_factors['B'].push_back(sf_muon_medium);
  scale_factors['B'].push_back(sf_btag_loose);

  // Lepjet 0b
  scale_factors['C'].push_back(sf_btag_loose);










}
//_______________________________________________________
//                 Signal Region
//     Must define it, because we blind it in data!

bool
Analysis::signal_selection(const eventBuffer& data) {
 //return apply_all_cuts('S');
 return 0;
}


TH2D* h_R2_MR_0_S;
TH1D* h_R2_0_S;
TH1D* h_MR_0_S;
TH1D* h_MRR2_0_S;
TH2D* h_R2_MR_1_S;
TH1D* h_R2_1_S;
TH1D* h_MR_1_S;
TH1D* h_MRR2_1_S;
TH2D* h_R2_MR_2_S;
TH1D* h_R2_2_S;
TH1D* h_MR_2_S;
TH1D* h_MRR2_2_S;

TH2D* h_R2_MR_3_S;
TH1D* h_R2_3_S;
TH1D* h_MR_3_S;
TH1D* h_MRR2_3_S;

TH2D* h_R2_MR_4_S;
TH1D* h_R2_4_S;
TH1D* h_MR_4_S;
TH1D* h_MRR2_4_S;

TH2D* h_R2_MR_5_S;
TH1D* h_R2_5_S;
TH1D* h_MR_5_S;
TH1D* h_MRR2_5_S;

TH2D* h_R2_MR_6_S;
TH1D* h_R2_6_S;
TH1D* h_MR_6_S;
TH1D* h_MRR2_6_S;

TH2D* h_R2_MR_7_S;
TH1D* h_R2_7_S;
TH1D* h_MR_7_S;
TH1D* h_MRR2_7_S;

TH2D* h_R2_MR_8_S;
TH1D* h_R2_8_S;
TH1D* h_MR_8_S;
TH1D* h_MRR2_8_S;

TH2D* h_R2_MR_9_S;
TH1D* h_R2_9_S;
TH1D* h_MR_9_S;
TH1D* h_MRR2_9_S;

TH2D* h_R2_MR_A_S;
TH1D* h_R2_A_S;
TH1D* h_MR_A_S;
TH1D* h_MRR2_A_S;

TH2D* h_R2_MR_B_S;
TH1D* h_R2_B_S;
TH1D* h_MR_B_S;
TH1D* h_MRR2_B_S;

TH2D* h_R2_MR_C_S;
TH1D* h_R2_C_S;
TH1D* h_MR_C_S;
TH1D* h_MRR2_C_S;





//_______________________________________________________
//              Define Histograms here
void
Analysis::init_analysis_histos(const unsigned int& syst_nSyst, const unsigned int& syst_index)
{
  int nbn_MR = 5;
  int nbn_R2 = 5;


    Double_t bn_MR_tmp[] = {800.,1000.,1200.,1600.,2000.,4000.};
  	Double_t* bn_MR = 0;
  	bn_MR = getVariableBinEdges(nbn_MR+1,bn_MR_tmp);

  	Double_t bn_R2_tmp[] = {0.08,0.12,0.16,0.24,0.4,1.5};
  	Double_t* bn_R2 = 0;
  	bn_R2 = getVariableBinEdges(nbn_R2+1,bn_R2_tmp);






   h_R2_MR_0_S = new TH2D("R2_MR_0_S", ";MR_{AK4};R2_{AK4}",nbn_MR,bn_MR,nbn_R2,bn_R2);
   h_MR_0_S = new TH1D("MR_0_S",   ";MR_{AK4}",     nbn_MR,    bn_MR);
	 h_R2_0_S = new TH1D("R2_0_S",   ";R2_{AK4}",         nbn_R2,bn_R2);
   h_MRR2_0_S = new TH1D("MRR2_0_S",   ";M_{R} #times R^{2} (GeV)",     210,0,1600);


   h_R2_MR_1_S = new TH2D("R2_MR_1_S", ";MR_{AK4};R2_{AK4}",nbn_MR,bn_MR,nbn_R2,bn_R2);
   h_MR_1_S = new TH1D("MR_1_S",   ";MR_{AK4}",     nbn_MR,    bn_MR);
   h_R2_1_S = new TH1D("R2_1_S",   ";R2_{AK4}",         nbn_R2,bn_R2);
   h_MRR2_1_S = new TH1D("MRR2_1_S",   ";M_{R} #times R^{2} (GeV)",     210,0,1600);

   h_R2_MR_2_S = new TH2D("R2_MR_2_S", ";MR_{AK4};R2_{AK4}",nbn_MR,bn_MR,nbn_R2,bn_R2);
   h_MR_2_S = new TH1D("MR_2_S",   ";MR_{AK4}",     nbn_MR,    bn_MR);
	 h_R2_2_S = new TH1D("R2_2_S",   ";R2_{AK4}",         nbn_R2,bn_R2);
   h_MRR2_2_S = new TH1D("MRR2_2_S",   ";M_{R} #times R^{2} (GeV)",     210,0,1600);

   h_R2_MR_3_S = new TH2D("R2_MR_3_S", ";MR_{AK4};R2_{AK4}",nbn_MR,bn_MR,nbn_R2,bn_R2);
   h_MR_3_S = new TH1D("MR_3_S",   ";MR_{AK4}",     nbn_MR,    bn_MR);
   h_R2_3_S = new TH1D("R2_3_S",   ";R2_{AK4}",         nbn_R2,bn_R2);
   h_MRR2_3_S = new TH1D("MRR2_3_S",   ";M_{R} #times R^{2} (GeV)",     210,0,1600);

   h_R2_MR_4_S = new TH2D("R2_MR_4_S", ";MR_{AK4};R2_{AK4}",nbn_MR,bn_MR,nbn_R2,bn_R2);
   h_MR_4_S = new TH1D("MR_4_S",   ";MR_{AK4}",     nbn_MR,    bn_MR);
	 h_R2_4_S = new TH1D("R2_4_S",   ";R2_{AK4}",         nbn_R2,bn_R2);
   h_MRR2_4_S = new TH1D("MRR2_4_S",   ";M_{R} #times R^{2} (GeV)",     210,0,1600);

	 h_R2_MR_5_S = new TH2D("R2_MR_5_S", ";MR_{AK4};R2_{AK4}",nbn_MR,bn_MR,nbn_R2,bn_R2);
   h_MR_5_S = new TH1D("MR_5_S",   ";MR_{AK4}",     nbn_MR,    bn_MR);
	 h_R2_5_S = new TH1D("R2_5_S",   ";R2_{AK4}",         nbn_R2,bn_R2);
   h_MRR2_5_S = new TH1D("MRR2_5_S",   ";M_{R} #times R^{2} (GeV)",     210,0,1600);

	 h_R2_MR_6_S = new TH2D("R2_MR_6_S", ";MR_{AK4};R2_{AK4}",nbn_MR,bn_MR,nbn_R2,bn_R2);
   h_MR_6_S = new TH1D("MR_6_S",   ";MR_{AK4}",     nbn_MR,    bn_MR);
	 h_R2_6_S = new TH1D("R2_6_S",   ";R2_{AK4}",         nbn_R2,bn_R2);
   h_MRR2_6_S = new TH1D("MRR2_6_S",   ";M_{R} #times R^{2} (GeV)",     210,0,1600);

   h_R2_MR_7_S = new TH2D("R2_MR_7_S", ";MR_{AK4};R2_{AK4}",nbn_MR,bn_MR,nbn_R2,bn_R2);
   h_MR_7_S = new TH1D("MR_7_S",   ";MR_{AK4}",     nbn_MR,    bn_MR);
	 h_R2_7_S = new TH1D("R2_7_S",   ";R2_{AK4}",         nbn_R2,bn_R2);
   h_MRR2_7_S = new TH1D("MRR2_7_S",   ";M_{R} #times R^{2} (GeV)",     210,0,1600);

	 h_R2_MR_8_S = new TH2D("R2_MR_8_S", ";MR_{AK4};R2_{AK4}",nbn_MR,bn_MR,nbn_R2,bn_R2);
   h_MR_8_S = new TH1D("MR_8_S",   ";MR_{AK4}",     nbn_MR,    bn_MR);
	 h_R2_8_S = new TH1D("R2_8_S",   ";R2_{AK4}",         nbn_R2,bn_R2);
   h_MRR2_8_S = new TH1D("MRR2_8_S",   ";M_{R} #times R^{2} (GeV)",     210,0,1600);

   h_R2_MR_9_S = new TH2D("R2_MR_9_S", ";MR_{AK4};R2_{AK4}",nbn_MR,bn_MR,nbn_R2,bn_R2);
   h_MR_9_S = new TH1D("MR_9_S",   ";MR_{AK4}",     nbn_MR,    bn_MR);
	 h_R2_9_S = new TH1D("R2_9_S",   ";R2_{AK4}",         nbn_R2,bn_R2);
   h_MRR2_9_S = new TH1D("MRR2_9_S",   ";M_{R} #times R^{2} (GeV)",     210,0,1600);

   h_R2_MR_A_S = new TH2D("R2_MR_A_S", ";MR_{AK4};R2_{AK4}",nbn_MR,bn_MR,nbn_R2,bn_R2);
   h_MR_A_S = new TH1D("MR_A_S",   ";MR_{AK4}",     nbn_MR,    bn_MR);
	 h_R2_A_S = new TH1D("R2_A_S",   ";R2_{AK4}",         nbn_R2,bn_R2);
   h_MRR2_A_S = new TH1D("MRR2_A_S",   ";M_{R} #times R^{2} (GeV)",     210,0,1600);

   h_R2_MR_B_S = new TH2D("R2_MR_B_S", ";MR_{AK4};R2_{AK4}",nbn_MR,bn_MR,nbn_R2,bn_R2);
   h_MR_B_S = new TH1D("MR_B_S",   ";MR_{AK4}",     nbn_MR,    bn_MR);
	 h_R2_B_S = new TH1D("R2_B_S",   ";R2_{AK4}",         nbn_R2,bn_R2);
   h_MRR2_B_S = new TH1D("MRR2_B_S",   ";M_{R} #times R^{2} (GeV)",     210,0,1600);

   h_R2_MR_C_S = new TH2D("R2_MR_C_S", ";MR_{AK4};R2_{AK4}",nbn_MR,bn_MR,nbn_R2,bn_R2);
   h_MR_C_S = new TH1D("MR_C_S",   ";MR_{AK4}",     nbn_MR,    bn_MR);
	 h_R2_C_S = new TH1D("R2_C_S",   ";R2_{AK4}",         nbn_R2,bn_R2);
   h_MRR2_C_S = new TH1D("MRR2_C_S",   ";M_{R} #times R^{2} (GeV)",     210,0,1600);













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



/*  if (apply_all_cuts('P')) h_R2_MR->Fill(MR, R2, w);
  if (apply_all_cuts('P')) h_R2->Fill(R2, w);
  if (apply_all_cuts('P')) h_MR->Fill(MR, w);
  if (apply_all_cuts('P')) {
        h_njet_P    ->Fill(nJet,        w);
        h_nAK8jet_P ->Fill(nJetAK8,     w);
        h_nbTight_P ->Fill(nTightBTag, w);
        h_nbMedium_P->Fill(nMediumBTag, w);
        h_nbLoose_P ->Fill(nLooseBTag, w);
        h_nw_P      ->Fill(nTightWTag,  w);
        h_nTop_P     ->Fill(nHadTopTag,  w);
        h_nEleVeto_P  ->Fill(nEleVeto,  w);
        h_nEleTight_P ->Fill(nEleTight, w);
        h_nEleMedium_P->Fill(nEleSelect,w);
        h_nEleLoose_P ->Fill(nEleLoose, w);
        h_nMuTight_P ->Fill(nMuTight, w);
        h_nMuMedium_P->Fill(nMuSelect,w);
        h_nMuSoft_P  ->Fill(nMuVeto,  w);
        h_nTauVeto_P ->Fill(nTauVeto, w);
        h_nIsoTrack_P->Fill(data.IsoTrack.size(), w);
        h_nPhoMedium_P ->Fill(nPhotonSelect, w);
        h_ht_AK4_P->Fill(AK4_Ht, w); // Calculated in AnalysisBase.h
        h_ht_AK8_P->Fill(AK8_Ht, w);
        h_MET_P->Fill(data.MET_pt,w);


  }
*/




w = sf_weight['0']*137.0/41.529;
		if (apply_all_cuts('0')) {
			h_MR_0_S->Fill(MR, w);
			h_R2_0_S->Fill(R2, w);
      h_MRR2_0_S->Fill(MR*R2, w);
			h_R2_MR_0_S->Fill(MR, R2, w);

			}

w = sf_weight['1']*137.0/41.529;
    if (apply_all_cuts('1')) {
     h_MR_1_S->Fill(MR, w);
     h_R2_1_S->Fill(R2, w);
     h_R2_MR_1_S->Fill(MR, R2, w);
     h_MRR2_1_S->Fill(MR*R2, w);


    }
  w = sf_weight['2']*137.0/41.529;
  		if (apply_all_cuts('2')) {
  			h_MR_2_S->Fill(MR, w);
  			h_R2_2_S->Fill(R2, w);
  			h_R2_MR_2_S->Fill(MR, R2, w);
        h_MRR2_2_S->Fill(MR*R2, w);


  			}

  w = sf_weight['3']*137.0/41.529;
      if (apply_all_cuts('3')) {
       h_MR_3_S->Fill(MR, w);
       h_R2_3_S->Fill(R2, w);
       h_R2_MR_3_S->Fill(MR, R2, w);
       h_MRR2_3_S->Fill(MR*R2, w);


      }
  w = sf_weight['4']*137.0/41.529;
    	if (apply_all_cuts('4')) {
    			h_MR_4_S->Fill(MR, w);
    			h_R2_4_S->Fill(R2, w);
    			h_R2_MR_4_S->Fill(MR, R2, w);
          h_MRR2_4_S->Fill(MR*R2, w);


    	 }

  w = sf_weight['5']*137.0/41.529;
      if (apply_all_cuts('5')) {
         h_MR_5_S->Fill(MR, w);
         h_R2_5_S->Fill(R2, w);
         h_R2_MR_5_S->Fill(MR, R2, w);
         h_MRR2_5_S->Fill(MR*R2, w);


       }
  w = sf_weight['6']*137.0/41.529;
      if (apply_all_cuts('6')) {
      	 h_MR_6_S->Fill(MR, w);
      	 h_R2_6_S->Fill(R2, w);
      	 h_R2_MR_6_S->Fill(MR, R2, w);
         h_MRR2_6_S->Fill(MR*R2, w);


      	}

  w = sf_weight['7']*137.0/41.529;
      if (apply_all_cuts('7')) {
          h_MR_7_S->Fill(MR, w);
          h_R2_7_S->Fill(R2, w);
          h_R2_MR_7_S->Fill(MR, R2, w);
          h_MRR2_7_S->Fill(MR*R2, w);


        }
  w = sf_weight['8']*137.0/41.529;
      if (apply_all_cuts('8')) {
        	h_MR_8_S->Fill(MR, w);
        	h_R2_8_S->Fill(R2, w);
        	h_R2_MR_8_S->Fill(MR, R2, w);
          h_MRR2_8_S->Fill(MR*R2, w);


        }

  w = sf_weight['9']*137.0/41.529;
      if (apply_all_cuts('9')) {
          h_MR_9_S->Fill(MR, w);
          h_R2_9_S->Fill(R2, w);
          h_R2_MR_9_S->Fill(MR, R2, w);
          h_MRR2_9_S->Fill(MR*R2, w);


        }

  w = sf_weight['A']*137.0/41.529;
      if (apply_all_cuts('A')) {
          h_MR_A_S->Fill(MR, w);
          h_R2_A_S->Fill(R2, w);
          h_R2_MR_A_S->Fill(MR, R2, w);
          h_MRR2_A_S->Fill(MR*R2, w);


        }

  w = sf_weight['B']*137.0/41.529;
      if (apply_all_cuts('B')) {
          h_MR_B_S->Fill(MR, w);
          h_R2_B_S->Fill(R2, w);
          h_R2_MR_B_S->Fill(MR, R2, w);
          h_MRR2_B_S->Fill(MR*R2, w);


      }

  w = sf_weight['C']*137.0/41.529;
    	if (apply_all_cuts('C')) {
        h_MR_C_S->Fill(MR, w);
        h_R2_C_S->Fill(R2, w);
        h_R2_MR_C_S->Fill(MR, R2, w);
        h_MRR2_C_S->Fill(MR*R2, w);


        }



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
