#include "TLorentzVector.h"
#include "TMath.h"
#include "include/AnalysisBase.h"
#include <fstream>
#include <map>

using namespace std;
//_______________________________________________________
//                  Calculate variables

// Cut variables
static size_t cut_index;
std::map<char, unsigned int> cutbits;
std::map<char, bool> pass_all_cuts;

// N-1 weights
std::map<char, std::vector<double> > w_nm1;

	void
Analysis::calculate_variables(eventBuffer& data, const unsigned int& syst_index)
{
	cut_index = -1;
	// Calculate decision of each individual cut
	for (const auto& region : analysis_cuts) {
		cutbits[region.first] = 0;
		for (size_t i=0, n=analysis_cuts[region.first].size(); i<n; ++i)
			if (analysis_cuts[region.first][i].func()) cutbits[region.first] += 1<<i;
		pass_all_cuts[region.first] = (cutbits[region.first]==(unsigned int)((1<<analysis_cuts[region.first].size())-1));
	}
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

	// cut0: signal mass region
	bool isT2tt = TString(sample).Contains("T2tt");
	if(isT2tt){ 
		baseline_cuts.push_back({ .name="signal_mass_selection",   .func = []{ 
				return susy_mass.first==1200 && susy_mass.second==200;
				} });}
	bool isT1tttt = TString(sample).Contains("T1tttt");
	if(isT1tttt){ 
		baseline_cuts.push_back({ .name="signal_mass_selection",   .func = []{ 
				return susy_mass.first==2250 && susy_mass.second==300;
				} });}
	bool isT5ttcc = TString(sample).Contains("T5ttcc");
	if(isT5ttcc){ 
		baseline_cuts.push_back({ .name="signal_mass_selection",   .func = []{ 
				return susy_mass.first==2250 && susy_mass.second==300;
				} });}
	bool isTChi = TString(sample).Contains("TChi");
	if(isTChi){ 
		baseline_cuts.push_back({ .name="signal_mass_selection",   .func = []{ 
				return susy_mass.first==700 && susy_mass.second==200;
				} });}

	bool isMET   = TString(sample).Contains("MET");
	bool isJetHT = TString(sample).Contains("JetHT");
	// preselection
	analysis_cuts['P'].push_back({ .name="1JetAK8",    .func = []    { return nJetAK8>=1;                      }}); // Similar to pt>200, one AK8 jet has pt>200
	analysis_cuts['P'].push_back({ .name="NJet",       .func = []    { return nJet>=3;                          }}); // Separate cut, so one can exclude (N-1)
	analysis_cuts['P'].push_back({ .name="MR_R2",    .func = [&d]  { return MR>=800 && R2>=0.08;     }});
	if(isJetHT) analysis_cuts['P'].push_back({ .name="HLT",.func = [this,&d] { return isData ? d.HLT_PFHT1050==1  : 1; }});
	else if(isMET) analysis_cuts['P'].push_back({ .name="HLT",.func = [this,&d] { return isData ? !(d.HLT_PFHT1050==1 ) && (d.HLT_PFHT500_PFMET100_PFMHT100_IDTight==1 || d.HLT_PFHT500_PFMET110_PFMHT110_IDTight==1 || d.HLT_PFHT700_PFMET85_PFMHT85_IDTight==1 || d.HLT_PFHT700_PFMET95_PFMHT95_IDTight==1 || d.HLT_PFHT800_PFMET75_PFMHT75_IDTight==1 || d.HLT_PFHT800_PFMET85_PFMHT85_IDTight==1) : 1; }});
	else      analysis_cuts['P'].push_back({ .name="HLT",.func = [this,&d] { return isData ? d.HLT_PFHT1050==1  || (d.HLT_PFHT500_PFMET100_PFMHT100_IDTight==1 || d.HLT_PFHT500_PFMET110_PFMHT110_IDTight==1 || d.HLT_PFHT700_PFMET85_PFMHT85_IDTight==1 || d.HLT_PFHT700_PFMET95_PFMHT95_IDTight==1 || d.HLT_PFHT800_PFMET75_PFMHT75_IDTight==1 || d.HLT_PFHT800_PFMET85_PFMHT85_IDTight==1) : 1; }});
	//else      analysis_cuts['P'].push_back({ .name="HLT",.func = [this,&d] { return isData ? d.HLT_PFMET120_PFMHT120_IDTight==1  || (d.HLT_PFHT500_PFMET100_PFMHT100_IDTight==1 || d.HLT_PFHT500_PFMET110_PFMHT110_IDTight==1 || d.HLT_PFHT700_PFMET85_PFMHT85_IDTight==1 || d.HLT_PFHT700_PFMET95_PFMHT95_IDTight==1 || d.HLT_PFHT800_PFMET75_PFMHT75_IDTight==1 || d.HLT_PFHT800_PFMET85_PFMHT85_IDTight==1) : 1; }});

#if TOP == 0
	// S: Signal region
	analysis_cuts['S'].push_back({ .name="1JetAK8",    .func = []    { return nJetAK8>=1;                      }}); // Similar to pt>200, one AK8 jet has pt>200
	analysis_cuts['S'].push_back({ .name="NJet",       .func = []    { return nJet>=3;                          }}); // Separate cut, so one can exclude (N-1)
	analysis_cuts['S'].push_back({ .name="MR_R2",      .func = [&d]  { return MR>=800 && R2>=0.08;  }});
	if(isJetHT) analysis_cuts['S'].push_back({ .name="HLT",.func = [this,&d] { return isData ? d.HLT_PFHT1050==1  : 1; }});
	else if(isMET) analysis_cuts['S'].push_back({ .name="HLT",.func = [this,&d] { return isData ? !(d.HLT_PFHT1050==1 ) && (d.HLT_PFHT500_PFMET100_PFMHT100_IDTight==1 || d.HLT_PFHT500_PFMET110_PFMHT110_IDTight==1 || d.HLT_PFHT700_PFMET85_PFMHT85_IDTight==1 || d.HLT_PFHT700_PFMET95_PFMHT95_IDTight==1 || d.HLT_PFHT800_PFMET75_PFMHT75_IDTight==1 || d.HLT_PFHT800_PFMET85_PFMHT85_IDTight==1) : 1; }});
	else      analysis_cuts['S'].push_back({ .name="HLT",.func = [this,&d] { return isData ? d.HLT_PFHT1050==1  || (d.HLT_PFHT500_PFMET100_PFMHT100_IDTight==1 || d.HLT_PFHT500_PFMET110_PFMHT110_IDTight==1 || d.HLT_PFHT700_PFMET85_PFMHT85_IDTight==1 || d.HLT_PFHT700_PFMET95_PFMHT95_IDTight==1 || d.HLT_PFHT800_PFMET75_PFMHT75_IDTight==1 || d.HLT_PFHT800_PFMET85_PFMHT85_IDTight==1) : 1; }});
	analysis_cuts['S'].push_back({ .name="0Ele",       .func = []    { return nEleVeto==0;                      }});
	analysis_cuts['S'].push_back({ .name="0Mu",        .func = []    { return nMuVeto==0;                       }});
	analysis_cuts['S'].push_back({ .name="0Tau",       .func = []    { return nTauVeto==0;                      }});
	analysis_cuts['S'].push_back({ .name="1b",         .func = []    { return nMediumBTag>=1;                   }});
	analysis_cuts['S'].push_back({ .name="1W",         .func = []    { return nBoostMassTag>=1;                    }});
	//analysis_cuts['S'].push_back({ .name="mDPhi",      .func = []    { return minDeltaPhi>=0.5;                 }});
	analysis_cuts['S'].push_back({ .name="mDPhi",      .func = []    { return dPhiRazor<2.8;                 }});

	// S': DPhi Control region of Signal region
	analysis_cuts['s'].push_back({ .name="1JetAK8",    .func = []    { return nJetAK8>=1;                      }}); // Similar to pt>200, one AK8 jet has pt>200
	analysis_cuts['s'].push_back({ .name="NJet",       .func = []    { return nJet>=3;                          }}); // Separate cut, so one can exclude (N-1)
	analysis_cuts['s'].push_back({ .name="MR_R2",      .func = [&d]  { return MR>=800 && R2>=0.08;  }});
	if(isJetHT) analysis_cuts['s'].push_back({ .name="HLT",.func = [this,&d] { return isData ? d.HLT_PFHT1050==1  : 1; }});
	else if(isMET) analysis_cuts['s'].push_back({ .name="HLT",.func = [this,&d] { return isData ? !(d.HLT_PFHT1050==1 ) && (d.HLT_PFHT500_PFMET100_PFMHT100_IDTight==1 || d.HLT_PFHT500_PFMET110_PFMHT110_IDTight==1 || d.HLT_PFHT700_PFMET85_PFMHT85_IDTight==1 || d.HLT_PFHT700_PFMET95_PFMHT95_IDTight==1 || d.HLT_PFHT800_PFMET75_PFMHT75_IDTight==1 || d.HLT_PFHT800_PFMET85_PFMHT85_IDTight==1) : 1; }});
	else      analysis_cuts['s'].push_back({ .name="HLT",.func = [this,&d] { return isData ? d.HLT_PFHT1050==1  || (d.HLT_PFHT500_PFMET100_PFMHT100_IDTight==1 || d.HLT_PFHT500_PFMET110_PFMHT110_IDTight==1 || d.HLT_PFHT700_PFMET85_PFMHT85_IDTight==1 || d.HLT_PFHT700_PFMET95_PFMHT95_IDTight==1 || d.HLT_PFHT800_PFMET75_PFMHT75_IDTight==1 || d.HLT_PFHT800_PFMET85_PFMHT85_IDTight==1) : 1; }});
	analysis_cuts['s'].push_back({ .name="0Ele",       .func = []    { return nEleVeto==0;                      }});
	analysis_cuts['s'].push_back({ .name="0Mu",        .func = []    { return nMuVeto==0;                       }});
	analysis_cuts['s'].push_back({ .name="0Tau",       .func = []    { return nTauVeto==0;                      }});
	analysis_cuts['s'].push_back({ .name="1b",         .func = []    { return nMediumBTag>=1;                   }});
	analysis_cuts['s'].push_back({ .name="1W",         .func = []    { return nBoostMassTag>=1;                    }});
	//analysis_cuts['s'].push_back({ .name="InvmDPhi",   .func = []    { return minDeltaPhi<0.5;                  }});
	analysis_cuts['s'].push_back({ .name="InvmDPhi",   .func = []    { return dPhiRazor>=2.8;                  }});

	// Q: QCD enriched control sample
	analysis_cuts['Q'].push_back({ .name="1JetAK8",    .func = []    { return nJetAK8>=1;                      }}); // Similar to pt>200, one AK8 jet has pt>200
	analysis_cuts['Q'].push_back({ .name="NJet",       .func = []    { return nJet>=3;                          }});
	analysis_cuts['Q'].push_back({ .name="MR_R2",      .func = [&d]  { return MR>=800 && R2>=0.08;  }});
	if(isJetHT) analysis_cuts['Q'].push_back({ .name="HLT",.func = [this,&d] { return isData ? d.HLT_PFHT1050==1  : 1; }});
	else if(isMET) analysis_cuts['Q'].push_back({ .name="HLT",.func = [this,&d] { return isData ? !(d.HLT_PFHT1050==1 ) && (d.HLT_PFHT500_PFMET100_PFMHT100_IDTight==1 || d.HLT_PFHT500_PFMET110_PFMHT110_IDTight==1 || d.HLT_PFHT700_PFMET85_PFMHT85_IDTight==1 || d.HLT_PFHT700_PFMET95_PFMHT95_IDTight==1 || d.HLT_PFHT800_PFMET75_PFMHT75_IDTight==1 || d.HLT_PFHT800_PFMET85_PFMHT85_IDTight==1) : 1; }});
	else      analysis_cuts['Q'].push_back({ .name="HLT",.func = [this,&d] { return isData ? d.HLT_PFHT1050==1  || (d.HLT_PFHT500_PFMET100_PFMHT100_IDTight==1 || d.HLT_PFHT500_PFMET110_PFMHT110_IDTight==1 || d.HLT_PFHT700_PFMET85_PFMHT85_IDTight==1 || d.HLT_PFHT700_PFMET95_PFMHT95_IDTight==1 || d.HLT_PFHT800_PFMET75_PFMHT75_IDTight==1 || d.HLT_PFHT800_PFMET85_PFMHT85_IDTight==1) : 1; }});
	analysis_cuts['Q'].push_back({ .name="0Ele",       .func = []    { return nEleVeto==0;                      }});
	analysis_cuts['Q'].push_back({ .name="0Mu",        .func = []    { return nMuVeto==0;                       }});
	analysis_cuts['Q'].push_back({ .name="0Tau",       .func = []    { return nTauVeto==0;                      }});
	analysis_cuts['Q'].push_back({ .name="0b",         .func = []    { return nLooseBTag==0;                    }});
	analysis_cuts['Q'].push_back({ .name="1aW",        .func = []    { return nBoostMassTag>=1;                }});
	//analysis_cuts['Q'].push_back({ .name="InvmDPhi",.func = []    { return minDeltaPhi<0.3;                  }});
	analysis_cuts['Q'].push_back({ .name="InvmDPhi",.func = []    { return dPhiRazor>=2.8;                  }});

	// Q': Dphi Control region of QCD enriched sample
	analysis_cuts['q'].push_back({ .name="1JetAK8",    .func = []    { return nJetAK8>=1;                      }}); // Similar to pt>200, one AK8 jet has pt>200
	analysis_cuts['q'].push_back({ .name="NJet",       .func = []    { return nJet>=3;                          }});
	analysis_cuts['q'].push_back({ .name="MR_R2",      .func = [&d]  { return MR>=800 && R2>=0.08;  }});
	if(isJetHT) analysis_cuts['q'].push_back({ .name="HLT",.func = [this,&d] { return isData ? d.HLT_PFHT1050==1  : 1; }});
	else if(isMET) analysis_cuts['q'].push_back({ .name="HLT",.func = [this,&d] { return isData ? !(d.HLT_PFHT1050==1 ) && (d.HLT_PFHT500_PFMET100_PFMHT100_IDTight==1 || d.HLT_PFHT500_PFMET110_PFMHT110_IDTight==1 || d.HLT_PFHT700_PFMET85_PFMHT85_IDTight==1 || d.HLT_PFHT700_PFMET95_PFMHT95_IDTight==1 || d.HLT_PFHT800_PFMET75_PFMHT75_IDTight==1 || d.HLT_PFHT800_PFMET85_PFMHT85_IDTight==1) : 1; }});
	else      analysis_cuts['q'].push_back({ .name="HLT",.func = [this,&d] { return isData ? d.HLT_PFHT1050==1  || (d.HLT_PFHT500_PFMET100_PFMHT100_IDTight==1 || d.HLT_PFHT500_PFMET110_PFMHT110_IDTight==1 || d.HLT_PFHT700_PFMET85_PFMHT85_IDTight==1 || d.HLT_PFHT700_PFMET95_PFMHT95_IDTight==1 || d.HLT_PFHT800_PFMET75_PFMHT75_IDTight==1 || d.HLT_PFHT800_PFMET85_PFMHT85_IDTight==1) : 1; }});
	analysis_cuts['q'].push_back({ .name="0Ele",       .func = []    { return nEleVeto==0;                      }});
	analysis_cuts['q'].push_back({ .name="0Mu",        .func = []    { return nMuVeto==0;                       }});
	analysis_cuts['q'].push_back({ .name="0Tau",       .func = []    { return nTauVeto==0;                      }});
	analysis_cuts['q'].push_back({ .name="0b",         .func = []    { return nLooseBTag==0;                    }});
	analysis_cuts['q'].push_back({ .name="1aW",        .func = []    { return nBoostMassTag>=1;                }});
	//analysis_cuts['q'].push_back({ .name="mDPhi",.func = []    { return minDeltaPhi>=0.5;                  }});
	analysis_cuts['q'].push_back({ .name="mDPhi",      .func = []    { return dPhiRazor<2.8;                 }});

	// T: Top enriched control sample
	analysis_cuts['T'].push_back({ .name="1JetAK8",    .func = []    { return nJetAK8>=1;                      }}); // Similar to pt>200, one AK8 jet has pt>200
	analysis_cuts['T'].push_back({ .name="NJet",       .func = []    { return nJet>=3;                          }});
	analysis_cuts['T'].push_back({ .name="MR_R2",      .func = [&d]  { return MR>=800 && R2>=0.08;  }});
	if(isJetHT) analysis_cuts['T'].push_back({ .name="HLT",.func = [this,&d] { return isData ? d.HLT_PFHT1050==1  : 1; }});
	else if(isMET) analysis_cuts['T'].push_back({ .name="HLT",.func = [this,&d] { return isData ? !(d.HLT_PFHT1050==1 ) && (d.HLT_PFHT500_PFMET100_PFMHT100_IDTight==1 || d.HLT_PFHT500_PFMET110_PFMHT110_IDTight==1 || d.HLT_PFHT700_PFMET85_PFMHT85_IDTight==1 || d.HLT_PFHT700_PFMET95_PFMHT95_IDTight==1 || d.HLT_PFHT800_PFMET75_PFMHT75_IDTight==1 || d.HLT_PFHT800_PFMET85_PFMHT85_IDTight==1) : 1; }});
	else      analysis_cuts['T'].push_back({ .name="HLT",.func = [this,&d] { return isData ? d.HLT_PFHT1050==1  || (d.HLT_PFHT500_PFMET100_PFMHT100_IDTight==1 || d.HLT_PFHT500_PFMET110_PFMHT110_IDTight==1 || d.HLT_PFHT700_PFMET85_PFMHT85_IDTight==1 || d.HLT_PFHT700_PFMET95_PFMHT95_IDTight==1 || d.HLT_PFHT800_PFMET75_PFMHT75_IDTight==1 || d.HLT_PFHT800_PFMET85_PFMHT85_IDTight==1) : 1; }});
	analysis_cuts['T'].push_back({ .name="1Lep",       .func = []    { return nLepVeto==1;                      }});
	analysis_cuts['T'].push_back({ .name="1b",         .func = []    { return nMediumBTag>=1;                   }});
	analysis_cuts['T'].push_back({ .name="1W",         .func = []    { return nBoostMassTag>=1;                    }});
	//analysis_cuts['T'].push_back({ .name="mDPhi",      .func = []    { return minDeltaPhi>=0.5;                 }});
	analysis_cuts['T'].push_back({ .name="mDPhi",      .func = []    { return dPhiRazor<2.8;                 }});
	analysis_cuts['T'].push_back({ .name="MT",         .func = []    { return MT_vetolep<100;                   }});

	// W: W enriched control sample
	analysis_cuts['W'].push_back({ .name="1JetAK8",    .func = []    { return nJetAK8>=1;                      }}); // Similar to pt>200, one AK8 jet has pt>200
	analysis_cuts['W'].push_back({ .name="NJet",       .func = []    { return nJet>=3;                          }});
	analysis_cuts['W'].push_back({ .name="MR_R2",      .func = [&d]  { return MR>=800 && R2>=0.08;  }});
	if(isJetHT) analysis_cuts['W'].push_back({ .name="HLT",.func = [this,&d] { return isData ? d.HLT_PFHT1050==1  : 1; }});
	else if(isMET) analysis_cuts['W'].push_back({ .name="HLT",.func = [this,&d] { return isData ? !(d.HLT_PFHT1050==1 ) && (d.HLT_PFHT500_PFMET100_PFMHT100_IDTight==1 || d.HLT_PFHT500_PFMET110_PFMHT110_IDTight==1 || d.HLT_PFHT700_PFMET85_PFMHT85_IDTight==1 || d.HLT_PFHT700_PFMET95_PFMHT95_IDTight==1 || d.HLT_PFHT800_PFMET75_PFMHT75_IDTight==1 || d.HLT_PFHT800_PFMET85_PFMHT85_IDTight==1) : 1; }});
	else      analysis_cuts['W'].push_back({ .name="HLT",.func = [this,&d] { return isData ? d.HLT_PFHT1050==1  || (d.HLT_PFHT500_PFMET100_PFMHT100_IDTight==1 || d.HLT_PFHT500_PFMET110_PFMHT110_IDTight==1 || d.HLT_PFHT700_PFMET85_PFMHT85_IDTight==1 || d.HLT_PFHT700_PFMET95_PFMHT95_IDTight==1 || d.HLT_PFHT800_PFMET75_PFMHT75_IDTight==1 || d.HLT_PFHT800_PFMET85_PFMHT85_IDTight==1) : 1; }});
	analysis_cuts['W'].push_back({ .name="1Lep",       .func = []    { return nLepVeto==1;                      }});
	analysis_cuts['W'].push_back({ .name="0b",         .func = []    { return nLooseBTag==0;                    }});
	analysis_cuts['W'].push_back({ .name="1mW",        .func = []    { return nBoostMassTag>=1;                     }});
	//analysis_cuts['W'].push_back({ .name="mDPhi",      .func = []    { return minDeltaPhi>=0.5;                 }});
	analysis_cuts['W'].push_back({ .name="mDPhi",      .func = []    { return dPhiRazor<2.8;                 }});
	analysis_cuts['W'].push_back({ .name="MT",         .func = []    { return MT_vetolep>=30 && MT_vetolep<100; }});

	// L: 1-lepton invisible control sample with veto lepton
	analysis_cuts['L'].push_back({ .name="1JetAK8",    .func = []    { return nJetAK8>=1;                       }});
	analysis_cuts['L'].push_back({ .name="NJet",       .func = []    { return nJet>=3;                          }});
	analysis_cuts['L'].push_back({ .name="MR",         .func = [&d]  { return MR>=800;                    }});
	analysis_cuts['L'].push_back({ .name="R2",         .func = [&d]  { return R2_1vl>=0.08;                     }});
	if(isJetHT) analysis_cuts['L'].push_back({ .name="HLT",.func = [this,&d] { return isData ? d.HLT_PFHT1050==1  : 1; }});
	else if(isMET) analysis_cuts['L'].push_back({ .name="HLT",.func = [this,&d] { return isData ? !(d.HLT_PFHT1050==1 ) && (d.HLT_PFHT500_PFMET100_PFMHT100_IDTight==1 || d.HLT_PFHT500_PFMET110_PFMHT110_IDTight==1 || d.HLT_PFHT700_PFMET85_PFMHT85_IDTight==1 || d.HLT_PFHT700_PFMET95_PFMHT95_IDTight==1 || d.HLT_PFHT800_PFMET75_PFMHT75_IDTight==1 || d.HLT_PFHT800_PFMET85_PFMHT85_IDTight==1) : 1; }});
	else      analysis_cuts['L'].push_back({ .name="HLT",.func = [this,&d] { return isData ? d.HLT_PFHT1050==1  || (d.HLT_PFHT500_PFMET100_PFMHT100_IDTight==1 || d.HLT_PFHT500_PFMET110_PFMHT110_IDTight==1 || d.HLT_PFHT700_PFMET85_PFMHT85_IDTight==1 || d.HLT_PFHT700_PFMET95_PFMHT95_IDTight==1 || d.HLT_PFHT800_PFMET75_PFMHT75_IDTight==1 || d.HLT_PFHT800_PFMET85_PFMHT85_IDTight==1) : 1; }});
	analysis_cuts['L'].push_back({ .name="0b",         .func = []    { return nLooseBTag==0;                    }});
	analysis_cuts['L'].push_back({ .name="1Lep",       .func = []    { return nLepVeto==1;                      }});
	analysis_cuts['L'].push_back({ .name="1mW",        .func = []    { return nBoostMassTag>=1;                     }});
	//analysis_cuts['L'].push_back({ .name="mDPhi",      .func = []    { return minDeltaPhi_1vl>=0.5;                 }});
	analysis_cuts['L'].push_back({ .name="mDPhi",      .func = []    { return dPhiRazor<2.8;                    }});
	analysis_cuts['L'].push_back({ .name="MT",         .func = []    { return MT_vetolep>=30 && MT_vetolep<100; }});

	// Z: Z->ll enriched control sample
	analysis_cuts['Z'].push_back({ .name="1JetAK8",    .func = []    { return nJetAK8>=1;                      }}); // Similar to pt>200, one AK8 jet has pt>200
	analysis_cuts['Z'].push_back({ .name="NJet",       .func = []    { return nJet>=3;                          }}); // Separate cut, so one can exclude (N-1)
	analysis_cuts['Z'].push_back({ .name="MR_R2ll",    .func = [&d]  { return MR>=800 && R2_ll>=0.08;     }});
	if(isJetHT) analysis_cuts['Z'].push_back({ .name="HLT",.func = [this,&d] { return isData ? d.HLT_PFHT1050==1  : 1; }});
	else if(isMET) analysis_cuts['Z'].push_back({ .name="HLT",.func = [this,&d] { return isData ? !(d.HLT_PFHT1050==1 ) && (d.HLT_PFHT500_PFMET100_PFMHT100_IDTight==1 || d.HLT_PFHT500_PFMET110_PFMHT110_IDTight==1 || d.HLT_PFHT700_PFMET85_PFMHT85_IDTight==1 || d.HLT_PFHT700_PFMET95_PFMHT95_IDTight==1 || d.HLT_PFHT800_PFMET75_PFMHT75_IDTight==1 || d.HLT_PFHT800_PFMET85_PFMHT85_IDTight==1) : 1; }});
	else      analysis_cuts['Z'].push_back({ .name="HLT",.func = [this,&d] { return isData ? d.HLT_PFHT1050==1  || (d.HLT_PFHT500_PFMET100_PFMHT100_IDTight==1 || d.HLT_PFHT500_PFMET110_PFMHT110_IDTight==1 || d.HLT_PFHT700_PFMET85_PFMHT85_IDTight==1 || d.HLT_PFHT700_PFMET95_PFMHT95_IDTight==1 || d.HLT_PFHT800_PFMET75_PFMHT75_IDTight==1 || d.HLT_PFHT800_PFMET85_PFMHT85_IDTight==1) : 1; }});
	analysis_cuts['Z'].push_back({ .name="2Lep",       .func = []    { return (nEleSelect==2&&nMuVeto==0)||(nMuSelect==2&&nEleVeto==0); }});
	analysis_cuts['Z'].push_back({ .name="OppCharge",  .func = [&d]  { 
			if (nEleSelect==2) return (d.Electron[iEleSelect[0]].charge + d.Electron[iEleSelect[1]].charge)==0;
			else if (nMuSelect==2) return (d.Muon[iMuSelect[0]].charge  + d.Muon[iMuSelect[1]].charge)==0;
			return false;
			}});
	analysis_cuts['Z'].push_back({ .name="1mW",        .func = []    { return nBoostMassTag>=1;                     }});
	analysis_cuts['Z'].push_back({ .name="mDPhi",    .func = []    { return dPhiRazor<2.8;              }});
	//analysis_cuts['Z'].push_back({ .name="mDPhi",    .func = []    { return minDeltaPhi_ll>=0.5;              }});
	analysis_cuts['Z'].push_back({ .name="Mll",        .func = []    { return std::abs(M_ll-91.2)<10;           }});

	// G: Photon enriched sample
	analysis_cuts['G'].push_back({ .name="1JetAK8",    .func = []    { return nJetAK8>=1;                       }});
	analysis_cuts['G'].push_back({ .name="1Pho",       .func = []    { return nPhotonSelect==1;                 }     });
	analysis_cuts['G'].push_back({ .name="NJet",       .func = []    { return nJetNoPho>=3;                     }});
	analysis_cuts['G'].push_back({ .name="MR",         .func = [&d]  { return MR_pho>=800;                    }});
	analysis_cuts['G'].push_back({ .name="R2",         .func = [&d]  { return R2_pho>=0.08;                     }});
	if(isJetHT) analysis_cuts['G'].push_back({ .name="HLT",.func = [this,&d] { return isData ? d.HLT_PFHT1050==1  : 1; }});
	else if(isMET) analysis_cuts['G'].push_back({ .name="HLT",.func = [this,&d] { return isData ? !(d.HLT_PFHT1050==1 ) && (d.HLT_PFHT500_PFMET100_PFMHT100_IDTight==1 || d.HLT_PFHT500_PFMET110_PFMHT110_IDTight==1 || d.HLT_PFHT700_PFMET85_PFMHT85_IDTight==1 || d.HLT_PFHT700_PFMET95_PFMHT95_IDTight==1 || d.HLT_PFHT800_PFMET75_PFMHT75_IDTight==1 || d.HLT_PFHT800_PFMET85_PFMHT85_IDTight==1) : 1; }});
	else      analysis_cuts['G'].push_back({ .name="HLT",.func = [this,&d] { return isData ? d.HLT_PFHT1050==1  || (d.HLT_PFHT500_PFMET100_PFMHT100_IDTight==1 || d.HLT_PFHT500_PFMET110_PFMHT110_IDTight==1 || d.HLT_PFHT700_PFMET85_PFMHT85_IDTight==1 || d.HLT_PFHT700_PFMET95_PFMHT95_IDTight==1 || d.HLT_PFHT800_PFMET75_PFMHT75_IDTight==1 || d.HLT_PFHT800_PFMET85_PFMHT85_IDTight==1) : 1; }});
	analysis_cuts['G'].push_back({ .name="0Ele",       .func = []    { return nEleVeto==0;                      }});
	analysis_cuts['G'].push_back({ .name="0Mu",        .func = []    { return nMuVeto==0;                       }});
	analysis_cuts['G'].push_back({ .name="0Tau",       .func = []    { return nTauVeto==0;                      }});
	analysis_cuts['G'].push_back({ .name="1mW",        .func = []    { return nBoostMassTag>=1;                     }});
	//analysis_cuts['G'].push_back({ .name="mDPhi",      .func = []    { return minDeltaPhi_pho>=0.5;             }});
	analysis_cuts['G'].push_back({ .name="mDPhi",      .func = []    { return dPhiRazorNoPho<2.8;                    }});

	// z: Z->ll enriched control sample (with full tag)
	analysis_cuts['z'].push_back({ .name="1JetAK8",    .func = []    { return nJetAK8>=1;                       }}); 
	analysis_cuts['z'].push_back({ .name="NJet",       .func = []    { return nJet>=3;                          }});
	analysis_cuts['z'].push_back({ .name="MR",         .func = [&d]  { return MR>=800;                    }}); 
	analysis_cuts['z'].push_back({ .name="R2ll",       .func = [&d]  { return R2_ll>=0.08;                      }}); 
	if(isJetHT) analysis_cuts['z'].push_back({ .name="HLT",.func = [this,&d] { return isData ? d.HLT_PFHT1050==1  : 1; }});
	else if(isMET) analysis_cuts['z'].push_back({ .name="HLT",.func = [this,&d] { return isData ? !(d.HLT_PFHT1050==1 ) && (d.HLT_PFHT500_PFMET100_PFMHT100_IDTight==1 || d.HLT_PFHT500_PFMET110_PFMHT110_IDTight==1 || d.HLT_PFHT700_PFMET85_PFMHT85_IDTight==1 || d.HLT_PFHT700_PFMET95_PFMHT95_IDTight==1 || d.HLT_PFHT800_PFMET75_PFMHT75_IDTight==1 || d.HLT_PFHT800_PFMET85_PFMHT85_IDTight==1) : 1; }});
	else      analysis_cuts['z'].push_back({ .name="HLT",.func = [this,&d] { return isData ? d.HLT_PFHT1050==1  || (d.HLT_PFHT500_PFMET100_PFMHT100_IDTight==1 || d.HLT_PFHT500_PFMET110_PFMHT110_IDTight==1 || d.HLT_PFHT700_PFMET85_PFMHT85_IDTight==1 || d.HLT_PFHT700_PFMET95_PFMHT95_IDTight==1 || d.HLT_PFHT800_PFMET75_PFMHT75_IDTight==1 || d.HLT_PFHT800_PFMET85_PFMHT85_IDTight==1) : 1; }});
	analysis_cuts['z'].push_back({ .name="2Lep",       .func = []    { return (nEleSelect==2&&nMuVeto==0)||(nMuSelect==2&&nEleVeto==0); }});
	analysis_cuts['z'].push_back({ .name="OppCharge",  .func = [&d]  { 
			if (nEleSelect==2) return (d.Electron[iEleSelect[0]].charge + d.Electron[iEleSelect[1]].charge)==0;
			else if (nMuSelect==2) return (d.Muon[iMuSelect[0]].charge + d.Muon[iMuSelect[1]].charge)==0;
			return false;
			}}); 
	analysis_cuts['z'].push_back({ .name="1W",         .func = []    { return nBoostMassTag>=1;                    }}); 
	//analysis_cuts['z'].push_back({ .name="1mW",        .func = []    { return nBoostMassTag>=1;                     }});
	analysis_cuts['z'].push_back({ .name="mDPhi",    .func = []    { return dPhiRazor<2.8;                    }}); 
	analysis_cuts['z'].push_back({ .name="Mll",        .func = []    { return std::abs(M_ll-91.2)<10;           }}); 

#else

	// t: Boosted Top Signal region
	analysis_cuts['S'].push_back({ .name="1JetAK8",    .func = []    { return nJetAK8>=1;                      }}); 
	analysis_cuts['S'].push_back({ .name="NJet",       .func = []    { return nJet>=2;                          }});
	//analysis_cuts['S'].push_back({ .name="NJet",       .func = []    { return nJet==2 || nJet==3;                          }});
  analysis_cuts['S'].push_back({ .name="2W",         .func = []    { return nTightWTag==2;                    }});
	analysis_cuts['S'].push_back({ .name="MR_R2",      .func = [&d]  { return MR>=800 && R2>=0.08;  }});
	if(isJetHT) analysis_cuts['S'].push_back({ .name="HLT",.func = [this,&d] { return isData ? d.HLT_PFHT1050==1  : 1; }});
	else if(isMET) analysis_cuts['S'].push_back({ .name="HLT",.func = [this,&d] { return isData ? !(d.HLT_PFHT1050==1 ) && (d.HLT_PFHT500_PFMET100_PFMHT100_IDTight==1 || d.HLT_PFHT500_PFMET110_PFMHT110_IDTight==1 || d.HLT_PFHT700_PFMET85_PFMHT85_IDTight==1 || d.HLT_PFHT700_PFMET95_PFMHT95_IDTight==1 || d.HLT_PFHT800_PFMET75_PFMHT75_IDTight==1 || d.HLT_PFHT800_PFMET85_PFMHT85_IDTight==1) : 1; }});
	else      analysis_cuts['S'].push_back({ .name="HLT",.func = [this,&d] { return isData ? d.HLT_PFHT1050==1  || (d.HLT_PFHT500_PFMET100_PFMHT100_IDTight==1 || d.HLT_PFHT500_PFMET110_PFMHT110_IDTight==1 || d.HLT_PFHT700_PFMET85_PFMHT85_IDTight==1 || d.HLT_PFHT700_PFMET95_PFMHT95_IDTight==1 || d.HLT_PFHT800_PFMET75_PFMHT75_IDTight==1 || d.HLT_PFHT800_PFMET85_PFMHT85_IDTight==1) : 1; }});
	analysis_cuts['S'].push_back({ .name="0Ele",       .func = []    { return nEleVeto==0;                      }});
	analysis_cuts['S'].push_back({ .name="0Mu",        .func = []    { return nMuVeto==0;                       }});
	analysis_cuts['S'].push_back({ .name="0Tau",       .func = []    { return nTauVeto==0;                      }});
  //analysis_cuts['S'].push_back({ .name="1W",         .func = []    { return nTightWTag>=1;                    }});
	analysis_cuts['S'].push_back({ .name="mDPhi",      .func = []    { return dPhiRazor<2.8;                 }});

	// t: Boosted Top Signal region
	analysis_cuts['t'].push_back({ .name="1JetAK8",    .func = []    { return nJetAK8>=1;                      }}); 
	analysis_cuts['t'].push_back({ .name="NJet",       .func = []    { return nJet>=3;                          }});
	analysis_cuts['t'].push_back({ .name="MR_R2",      .func = [&d]  { return MR>=800 && R2>=0.08;  }});
	if(isJetHT) analysis_cuts['t'].push_back({ .name="HLT",.func = [this,&d] { return isData ? d.HLT_PFHT1050==1  : 1; }});
	else if(isMET) analysis_cuts['t'].push_back({ .name="HLT",.func = [this,&d] { return isData ? !(d.HLT_PFHT1050==1 ) && (d.HLT_PFHT500_PFMET100_PFMHT100_IDTight==1 || d.HLT_PFHT500_PFMET110_PFMHT110_IDTight==1 || d.HLT_PFHT700_PFMET85_PFMHT85_IDTight==1 || d.HLT_PFHT700_PFMET95_PFMHT95_IDTight==1 || d.HLT_PFHT800_PFMET75_PFMHT75_IDTight==1 || d.HLT_PFHT800_PFMET85_PFMHT85_IDTight==1) : 1; }});
	else      analysis_cuts['t'].push_back({ .name="HLT",.func = [this,&d] { return isData ? d.HLT_PFHT1050==1  || (d.HLT_PFHT500_PFMET100_PFMHT100_IDTight==1 || d.HLT_PFHT500_PFMET110_PFMHT110_IDTight==1 || d.HLT_PFHT700_PFMET85_PFMHT85_IDTight==1 || d.HLT_PFHT700_PFMET95_PFMHT95_IDTight==1 || d.HLT_PFHT800_PFMET75_PFMHT75_IDTight==1 || d.HLT_PFHT800_PFMET85_PFMHT85_IDTight==1) : 1; }});
	analysis_cuts['t'].push_back({ .name="0Ele",       .func = []    { return nEleVeto==0;                      }});
	analysis_cuts['t'].push_back({ .name="0Mu",        .func = []    { return nMuVeto==0;                       }});
	analysis_cuts['t'].push_back({ .name="0Tau",       .func = []    { return nTauVeto==0;                      }});
	//analysis_cuts['t'].push_back({ .name="1Top",       .func = []    { return nBoostMassBTag>=1;                    }});
  analysis_cuts['t'].push_back({ .name="1Top",       .func = []    { return nHadTopTag>=1;                    }}); 
	analysis_cuts['t'].push_back({ .name="mDPhi",      .func = []    { return dPhiRazor<2.8;                 }});

	// a: Boosted Top' Signal region
	analysis_cuts['s'].push_back({ .name="1JetAK8",    .func = []    { return nJetAK8>=1;                      }}); 
	analysis_cuts['s'].push_back({ .name="NJet",       .func = []    { return nJet>=3;                          }});
	analysis_cuts['s'].push_back({ .name="MR_R2",      .func = [&d]  { return MR>=800 && R2>=0.08;  }});
	if(isJetHT) analysis_cuts['s'].push_back({ .name="HLT",.func = [this,&d] { return isData ? d.HLT_PFHT1050==1  : 1; }});
	else if(isMET) analysis_cuts['s'].push_back({ .name="HLT",.func = [this,&d] { return isData ? !(d.HLT_PFHT1050==1 ) && (d.HLT_PFHT500_PFMET100_PFMHT100_IDTight==1 || d.HLT_PFHT500_PFMET110_PFMHT110_IDTight==1 || d.HLT_PFHT700_PFMET85_PFMHT85_IDTight==1 || d.HLT_PFHT700_PFMET95_PFMHT95_IDTight==1 || d.HLT_PFHT800_PFMET75_PFMHT75_IDTight==1 || d.HLT_PFHT800_PFMET85_PFMHT85_IDTight==1) : 1; }});
	else      analysis_cuts['s'].push_back({ .name="HLT",.func = [this,&d] { return isData ? d.HLT_PFHT1050==1  || (d.HLT_PFHT500_PFMET100_PFMHT100_IDTight==1 || d.HLT_PFHT500_PFMET110_PFMHT110_IDTight==1 || d.HLT_PFHT700_PFMET85_PFMHT85_IDTight==1 || d.HLT_PFHT700_PFMET95_PFMHT95_IDTight==1 || d.HLT_PFHT800_PFMET75_PFMHT75_IDTight==1 || d.HLT_PFHT800_PFMET85_PFMHT85_IDTight==1) : 1; }});
	analysis_cuts['s'].push_back({ .name="0Ele",       .func = []    { return nEleVeto==0;                      }});
	analysis_cuts['s'].push_back({ .name="0Mu",        .func = []    { return nMuVeto==0;                       }});
	analysis_cuts['s'].push_back({ .name="0Tau",       .func = []    { return nTauVeto==0;                      }});
	analysis_cuts['s'].push_back({ .name="1Top",       .func = []    { return nBoostMassBTag>=1;                    }});
	//analysis_cuts['s'].push_back({ .name="InvmDPhi",      .func = []    { return minDeltaPhi<0.5;                 }});
	analysis_cuts['s'].push_back({ .name="InvmDPhi",      .func = []    { return dPhiRazor>=2.8;                 }});

	// t: Boosted Top Q region
	analysis_cuts['Q'].push_back({ .name="1JetAK8",    .func = []    { return nJetAK8>=1;                      }}); 
	analysis_cuts['Q'].push_back({ .name="NJet",       .func = []    { return nJet>=3;                          }});
	analysis_cuts['Q'].push_back({ .name="MR_R2",      .func = [&d]  { return MR>=800 && R2>=0.08;  }});
	if(isJetHT) analysis_cuts['Q'].push_back({ .name="HLT",.func = [this,&d] { return isData ? d.HLT_PFHT1050==1  : 1; }});
	else if(isMET) analysis_cuts['Q'].push_back({ .name="HLT",.func = [this,&d] { return isData ? !(d.HLT_PFHT1050==1 ) && (d.HLT_PFHT500_PFMET100_PFMHT100_IDTight==1 || d.HLT_PFHT500_PFMET110_PFMHT110_IDTight==1 || d.HLT_PFHT700_PFMET85_PFMHT85_IDTight==1 || d.HLT_PFHT700_PFMET95_PFMHT95_IDTight==1 || d.HLT_PFHT800_PFMET75_PFMHT75_IDTight==1 || d.HLT_PFHT800_PFMET85_PFMHT85_IDTight==1) : 1; }});
	else      analysis_cuts['Q'].push_back({ .name="HLT",.func = [this,&d] { return isData ? d.HLT_PFHT1050==1  || (d.HLT_PFHT500_PFMET100_PFMHT100_IDTight==1 || d.HLT_PFHT500_PFMET110_PFMHT110_IDTight==1 || d.HLT_PFHT700_PFMET85_PFMHT85_IDTight==1 || d.HLT_PFHT700_PFMET95_PFMHT95_IDTight==1 || d.HLT_PFHT800_PFMET75_PFMHT75_IDTight==1 || d.HLT_PFHT800_PFMET85_PFMHT85_IDTight==1) : 1; }});
	analysis_cuts['Q'].push_back({ .name="0Ele",       .func = []    { return nEleVeto==0;                      }});
	analysis_cuts['Q'].push_back({ .name="0Mu",        .func = []    { return nMuVeto==0;                       }});
	analysis_cuts['Q'].push_back({ .name="0Tau",       .func = []    { return nTauVeto==0;                      }});
	analysis_cuts['Q'].push_back({ .name="0b",         .func = []    { return nLooseBTag==0;                    }});
	analysis_cuts['Q'].push_back({ .name="1aTop",       .func = []   { return nBoostMassTag>=1;                    }});
	//analysis_cuts['Q'].push_back({ .name="mDPhi",      .func = []    { return minDeltaPhi<0.3;                 }});
	analysis_cuts['Q'].push_back({ .name="InvmDPhi",      .func = []    { return dPhiRazor>=2.8;                 }});

	// t: Boosted Top Q' region
	analysis_cuts['q'].push_back({ .name="1JetAK8",    .func = []    { return nJetAK8>=1;                      }}); 
	analysis_cuts['q'].push_back({ .name="NJet",       .func = []    { return nJet>=3;                          }});
	analysis_cuts['q'].push_back({ .name="MR_R2",      .func = [&d]  { return MR>=800 && R2>=0.08;  }});
	if(isJetHT) analysis_cuts['q'].push_back({ .name="HLT",.func = [this,&d] { return isData ? d.HLT_PFHT1050==1  : 1; }});
	else if(isMET) analysis_cuts['q'].push_back({ .name="HLT",.func = [this,&d] { return isData ? !(d.HLT_PFHT1050==1 ) && (d.HLT_PFHT500_PFMET100_PFMHT100_IDTight==1 || d.HLT_PFHT500_PFMET110_PFMHT110_IDTight==1 || d.HLT_PFHT700_PFMET85_PFMHT85_IDTight==1 || d.HLT_PFHT700_PFMET95_PFMHT95_IDTight==1 || d.HLT_PFHT800_PFMET75_PFMHT75_IDTight==1 || d.HLT_PFHT800_PFMET85_PFMHT85_IDTight==1) : 1; }});
	else      analysis_cuts['q'].push_back({ .name="HLT",.func = [this,&d] { return isData ? d.HLT_PFHT1050==1  || (d.HLT_PFHT500_PFMET100_PFMHT100_IDTight==1 || d.HLT_PFHT500_PFMET110_PFMHT110_IDTight==1 || d.HLT_PFHT700_PFMET85_PFMHT85_IDTight==1 || d.HLT_PFHT700_PFMET95_PFMHT95_IDTight==1 || d.HLT_PFHT800_PFMET75_PFMHT75_IDTight==1 || d.HLT_PFHT800_PFMET85_PFMHT85_IDTight==1) : 1; }});
	analysis_cuts['q'].push_back({ .name="0Ele",       .func = []    { return nEleVeto==0;                      }});
	analysis_cuts['q'].push_back({ .name="0Mu",        .func = []    { return nMuVeto==0;                       }});
	analysis_cuts['q'].push_back({ .name="0Tau",       .func = []    { return nTauVeto==0;                      }});
	analysis_cuts['q'].push_back({ .name="0b",         .func = []    { return nLooseBTag==0;                    }});
	analysis_cuts['q'].push_back({ .name="1aTop",       .func = []   { return nBoostMassTag>=1;                    }});
	//analysis_cuts['q'].push_back({ .name="InvmDPhi",      .func = []    { return minDeltaPhi>=0.5;                 }});
	analysis_cuts['q'].push_back({ .name="mDPhi",      .func = []    { return dPhiRazor<2.8;                 }});

	// t: Boosted Top T region
	analysis_cuts['T'].push_back({ .name="1JetAK8",    .func = []    { return nJetAK8>=1;                      }}); 
	analysis_cuts['T'].push_back({ .name="NJet",       .func = []    { return nJet>=3;                          }});
	analysis_cuts['T'].push_back({ .name="MR_R2",      .func = [&d]  { return MR>=800 && R2>=0.08;  }});
	if(isJetHT) analysis_cuts['T'].push_back({ .name="HLT",.func = [this,&d] { return isData ? d.HLT_PFHT1050==1  : 1; }});
	else if(isMET) analysis_cuts['T'].push_back({ .name="HLT",.func = [this,&d] { return isData ? !(d.HLT_PFHT1050==1 ) && (d.HLT_PFHT500_PFMET100_PFMHT100_IDTight==1 || d.HLT_PFHT500_PFMET110_PFMHT110_IDTight==1 || d.HLT_PFHT700_PFMET85_PFMHT85_IDTight==1 || d.HLT_PFHT700_PFMET95_PFMHT95_IDTight==1 || d.HLT_PFHT800_PFMET75_PFMHT75_IDTight==1 || d.HLT_PFHT800_PFMET85_PFMHT85_IDTight==1) : 1; }});
	else      analysis_cuts['T'].push_back({ .name="HLT",.func = [this,&d] { return isData ? d.HLT_PFHT1050==1  || (d.HLT_PFHT500_PFMET100_PFMHT100_IDTight==1 || d.HLT_PFHT500_PFMET110_PFMHT110_IDTight==1 || d.HLT_PFHT700_PFMET85_PFMHT85_IDTight==1 || d.HLT_PFHT700_PFMET95_PFMHT95_IDTight==1 || d.HLT_PFHT800_PFMET75_PFMHT75_IDTight==1 || d.HLT_PFHT800_PFMET85_PFMHT85_IDTight==1) : 1; }});
	analysis_cuts['T'].push_back({ .name="1Lep",       .func = []    { return nLepVeto==1;                      }});
	analysis_cuts['T'].push_back({ .name="1Top",       .func = []   { return nBoostMassBTag>=1;                    }});
	//analysis_cuts['T'].push_back({ .name="mDPhi",      .func = []    { return minDeltaPhi>=0.5;                 }});
	analysis_cuts['T'].push_back({ .name="mDPhi",      .func = []    { return dPhiRazor<2.8;                 }});
	analysis_cuts['T'].push_back({ .name="MT",         .func = []    { return     MT_vetolep<100;               }});

	// t: Boosted Top W region
	analysis_cuts['W'].push_back({ .name="1JetAK8",    .func = []    { return nJetAK8>=1;                      }}); 
	analysis_cuts['W'].push_back({ .name="NJet",       .func = []    { return nJet>=3;                          }});
	analysis_cuts['W'].push_back({ .name="MR_R2",      .func = [&d]  { return MR>=800 && R2>=0.08;  }});
	if(isJetHT) analysis_cuts['W'].push_back({ .name="HLT",.func = [this,&d] { return isData ? d.HLT_PFHT1050==1  : 1; }});
	else if(isMET) analysis_cuts['W'].push_back({ .name="HLT",.func = [this,&d] { return isData ? !(d.HLT_PFHT1050==1 ) && (d.HLT_PFHT500_PFMET100_PFMHT100_IDTight==1 || d.HLT_PFHT500_PFMET110_PFMHT110_IDTight==1 || d.HLT_PFHT700_PFMET85_PFMHT85_IDTight==1 || d.HLT_PFHT700_PFMET95_PFMHT95_IDTight==1 || d.HLT_PFHT800_PFMET75_PFMHT75_IDTight==1 || d.HLT_PFHT800_PFMET85_PFMHT85_IDTight==1) : 1; }});
	else      analysis_cuts['W'].push_back({ .name="HLT",.func = [this,&d] { return isData ? d.HLT_PFHT1050==1  || (d.HLT_PFHT500_PFMET100_PFMHT100_IDTight==1 || d.HLT_PFHT500_PFMET110_PFMHT110_IDTight==1 || d.HLT_PFHT700_PFMET85_PFMHT85_IDTight==1 || d.HLT_PFHT700_PFMET95_PFMHT95_IDTight==1 || d.HLT_PFHT800_PFMET75_PFMHT75_IDTight==1 || d.HLT_PFHT800_PFMET85_PFMHT85_IDTight==1) : 1; }});
	analysis_cuts['W'].push_back({ .name="1Lep",       .func = []    { return nLepVeto==1;                      }});
	analysis_cuts['W'].push_back({ .name="0b",         .func = []    { return nLooseBTag==0;                    }});
	analysis_cuts['W'].push_back({ .name="1mTop",       .func = []   { return nBoostMassTag>=1;                    }});
	//analysis_cuts['W'].push_back({ .name="mDPhi",      .func = []    { return minDeltaPhi>=0.5;                 }});
	analysis_cuts['W'].push_back({ .name="mDPhi",      .func = []    { return dPhiRazor<2.8;                 }});
	analysis_cuts['W'].push_back({ .name="MT",         .func = []    { return MT_vetolep>=30 && MT_vetolep<100; }});

	// L: 1-lepton invisible control sample with veto lepton
	analysis_cuts['L'].push_back({ .name="1JetAK8",    .func = []    { return nJetAK8>=1;                       }});
	analysis_cuts['L'].push_back({ .name="NJet",       .func = []    { return nJet>=3;                          }});
	analysis_cuts['L'].push_back({ .name="MR",         .func = [&d]  { return MR>=800;                    }});
	analysis_cuts['L'].push_back({ .name="R2",         .func = [&d]  { return R2_1vl>=0.08;                     }});
	if(isJetHT) analysis_cuts['L'].push_back({ .name="HLT",.func = [this,&d] { return isData ? d.HLT_PFHT1050==1  : 1; }});
	else if(isMET) analysis_cuts['L'].push_back({ .name="HLT",.func = [this,&d] { return isData ? !(d.HLT_PFHT1050==1 ) && (d.HLT_PFHT500_PFMET100_PFMHT100_IDTight==1 || d.HLT_PFHT500_PFMET110_PFMHT110_IDTight==1 || d.HLT_PFHT700_PFMET85_PFMHT85_IDTight==1 || d.HLT_PFHT700_PFMET95_PFMHT95_IDTight==1 || d.HLT_PFHT800_PFMET75_PFMHT75_IDTight==1 || d.HLT_PFHT800_PFMET85_PFMHT85_IDTight==1) : 1; }});
	else      analysis_cuts['L'].push_back({ .name="HLT",.func = [this,&d] { return isData ? d.HLT_PFHT1050==1  || (d.HLT_PFHT500_PFMET100_PFMHT100_IDTight==1 || d.HLT_PFHT500_PFMET110_PFMHT110_IDTight==1 || d.HLT_PFHT700_PFMET85_PFMHT85_IDTight==1 || d.HLT_PFHT700_PFMET95_PFMHT95_IDTight==1 || d.HLT_PFHT800_PFMET75_PFMHT75_IDTight==1 || d.HLT_PFHT800_PFMET85_PFMHT85_IDTight==1) : 1; }});
	analysis_cuts['L'].push_back({ .name="1Lep",       .func = []    { return nLepVeto==1;                      }});
	analysis_cuts['L'].push_back({ .name="0b",         .func = []    { return nLooseBTag==0;                    }});
	analysis_cuts['L'].push_back({ .name="1mTop",      .func = []    { return nBoostMassTag>=1;              }});
	analysis_cuts['L'].push_back({ .name="mDPhi",      .func = []    { return dPhiRazor<2.8;                    }});
	analysis_cuts['L'].push_back({ .name="MT",         .func = []    { return MT_vetolep>=30 && MT_vetolep<100; }});

	// Z: Z->ll enriched control sample
	analysis_cuts['Z'].push_back({ .name="1JetAK8",    .func = []    { return nJetAK8>=1;                      }}); 
	analysis_cuts['Z'].push_back({ .name="NJet",       .func = []    { return nJet>=3;                          }});
	analysis_cuts['Z'].push_back({ .name="MR_R2ll",    .func = [&d]  { return MR>=800 && R2_ll>=0.08;     }});
	if(isJetHT) analysis_cuts['Z'].push_back({ .name="HLT",.func = [this,&d] { return isData ? d.HLT_PFHT1050==1  : 1; }});
	else if(isMET) analysis_cuts['Z'].push_back({ .name="HLT",.func = [this,&d] { return isData ? !(d.HLT_PFHT1050==1 ) && (d.HLT_PFHT500_PFMET100_PFMHT100_IDTight==1 || d.HLT_PFHT500_PFMET110_PFMHT110_IDTight==1 || d.HLT_PFHT700_PFMET85_PFMHT85_IDTight==1 || d.HLT_PFHT700_PFMET95_PFMHT95_IDTight==1 || d.HLT_PFHT800_PFMET75_PFMHT75_IDTight==1 || d.HLT_PFHT800_PFMET85_PFMHT85_IDTight==1) : 1; }});
	else      analysis_cuts['Z'].push_back({ .name="HLT",.func = [this,&d] { return isData ? d.HLT_PFHT1050==1  || (d.HLT_PFHT500_PFMET100_PFMHT100_IDTight==1 || d.HLT_PFHT500_PFMET110_PFMHT110_IDTight==1 || d.HLT_PFHT700_PFMET85_PFMHT85_IDTight==1 || d.HLT_PFHT700_PFMET95_PFMHT95_IDTight==1 || d.HLT_PFHT800_PFMET75_PFMHT75_IDTight==1 || d.HLT_PFHT800_PFMET85_PFMHT85_IDTight==1) : 1; }});
	analysis_cuts['Z'].push_back({ .name="2Lep",       .func = []    { return (nEleSelect==2&&nMuVeto==0)||(nMuSelect==2&&nEleVeto==0); }});
	analysis_cuts['Z'].push_back({ .name="OppCharge",  .func = [&d]  { 
			if (nEleSelect==2) return (d.Electron[iEleSelect[0]].charge + d.Electron[iEleSelect[1]].charge)==0;
			else if (nMuSelect==2) return (d.Muon[iMuSelect[0]].charge + d.Muon[iMuSelect[1]].charge)==0;
			return false;
			}});
	analysis_cuts['Z'].push_back({ .name="1mTop",        .func = []    { return nBoostMassTag>=1;                     }});
	analysis_cuts['Z'].push_back({ .name="mDPhi",    .func = []    { return dPhiRazor<2.8;              }});
	analysis_cuts['Z'].push_back({ .name="Mll",        .func = []    { return std::abs(M_ll-91.2)<10;           }});
	// G: Photon enriched sample
	analysis_cuts['G'].push_back({ .name="1JetAK8",    .func = []    { return nJetAK8>=1;                       }});
	analysis_cuts['G'].push_back({ .name="1Pho",       .func = []    { return nPhotonSelect==1;                 }});
	analysis_cuts['G'].push_back({ .name="NJet",       .func = []    { return nJetNoPho>=3;                     }});
	analysis_cuts['G'].push_back({ .name="MR",         .func = [&d]  { return MR_pho>=800;                      }});
	analysis_cuts['G'].push_back({ .name="R2",         .func = [&d]  { return R2_pho>=0.08;                     }});
	if(isJetHT) analysis_cuts['G'].push_back({ .name="HLT",.func = [this,&d] { return isData ? d.HLT_PFHT1050==1  : 1; }});
	else if(isMET) analysis_cuts['G'].push_back({ .name="HLT",.func = [this,&d] { return isData ? !(d.HLT_PFHT1050==1 ) && (d.HLT_PFHT500_PFMET100_PFMHT100_IDTight==1 || d.HLT_PFHT500_PFMET110_PFMHT110_IDTight==1 || d.HLT_PFHT700_PFMET85_PFMHT85_IDTight==1 || d.HLT_PFHT700_PFMET95_PFMHT95_IDTight==1 || d.HLT_PFHT800_PFMET75_PFMHT75_IDTight==1 || d.HLT_PFHT800_PFMET85_PFMHT85_IDTight==1) : 1; }});
	else      analysis_cuts['G'].push_back({ .name="HLT",.func = [this,&d] { return isData ? d.HLT_PFHT1050==1  || (d.HLT_PFHT500_PFMET100_PFMHT100_IDTight==1 || d.HLT_PFHT500_PFMET110_PFMHT110_IDTight==1 || d.HLT_PFHT700_PFMET85_PFMHT85_IDTight==1 || d.HLT_PFHT700_PFMET95_PFMHT95_IDTight==1 || d.HLT_PFHT800_PFMET75_PFMHT75_IDTight==1 || d.HLT_PFHT800_PFMET85_PFMHT85_IDTight==1) : 1; }});
	analysis_cuts['G'].push_back({ .name="0Ele",       .func = []    { return nEleVeto==0;                      }});
	analysis_cuts['G'].push_back({ .name="0Mu",        .func = []    { return nMuVeto==0;                       }});
	analysis_cuts['G'].push_back({ .name="0Tau",       .func = []    { return nTauVeto==0;                      }});
	analysis_cuts['G'].push_back({ .name="1mTop",      .func = []    { return nBoostMassTag>=1;                }});
	//analysis_cuts['G'].push_back({ .name="mDPhi",      .func = []    { return minDeltaPhi_pho>=0.5;             }});
	analysis_cuts['G'].push_back({ .name="mDPhi",      .func = []    { return dPhiRazorNoPho<2.8;               }});

#endif

	// G-1: Photon enriched sample (G without boosted object)
	analysis_cuts['g'].push_back({ .name="1JetAK8",    .func = []    { return nJetAK8>=1;                       }}); 
	analysis_cuts['g'].push_back({ .name="1Pho",       .func = []    { return nPhotonSelect==1;                 }}); 
	analysis_cuts['g'].push_back({ .name="NJet",       .func = []    { return nJetNoPho>=3;                     }}); 
	analysis_cuts['g'].push_back({ .name="MR",         .func = [&d]  { return MR_pho>=800;                      }}); 
	analysis_cuts['g'].push_back({ .name="R2",         .func = [&d]  { return R2_pho>=0.08;                     }}); 
	if(isJetHT) analysis_cuts['g'].push_back({ .name="HLT",.func = [this,&d] { return isData ? d.HLT_PFHT1050==1  : 1; }});
	else if(isMET) analysis_cuts['g'].push_back({ .name="HLT",.func = [this,&d] { return isData ? !(d.HLT_PFHT1050==1 ) && (d.HLT_PFHT500_PFMET100_PFMHT100_IDTight==1 || d.HLT_PFHT500_PFMET110_PFMHT110_IDTight==1 || d.HLT_PFHT700_PFMET85_PFMHT85_IDTight==1 || d.HLT_PFHT700_PFMET95_PFMHT95_IDTight==1 || d.HLT_PFHT800_PFMET75_PFMHT75_IDTight==1 || d.HLT_PFHT800_PFMET85_PFMHT85_IDTight==1) : 1; }});
	else      analysis_cuts['g'].push_back({ .name="HLT",.func = [this,&d] { return isData ? d.HLT_PFHT1050==1  || (d.HLT_PFHT500_PFMET100_PFMHT100_IDTight==1 || d.HLT_PFHT500_PFMET110_PFMHT110_IDTight==1 || d.HLT_PFHT700_PFMET85_PFMHT85_IDTight==1 || d.HLT_PFHT700_PFMET95_PFMHT95_IDTight==1 || d.HLT_PFHT800_PFMET75_PFMHT75_IDTight==1 || d.HLT_PFHT800_PFMET85_PFMHT85_IDTight==1) : 1; }});
	analysis_cuts['g'].push_back({ .name="0Ele",       .func = []    { return nEleVeto==0;                      }}); 
	analysis_cuts['g'].push_back({ .name="0Mu",        .func = []    { return nMuVeto==0;                       }}); 
	analysis_cuts['g'].push_back({ .name="0Tau",       .func = []    { return nTauVeto==0;                      }}); 
	analysis_cuts['g'].push_back({ .name="mDPhi",      .func = []    { return dPhiRazorNoPho<2.8;               }}); 

	// w: Inclusive Razor-like W enriched region
	analysis_cuts['w'].push_back({ .name="1JetAK8",    .func = []    { return nJetAK8>=1;                       }}); 
	analysis_cuts['w'].push_back({ .name="MR",         .func = [&d]  { return MR>=300;                    }}); 
	analysis_cuts['w'].push_back({ .name="R2",         .func = [&d]  { return R2>=0.15;                   }}); 
	if(isJetHT) analysis_cuts['w'].push_back({ .name="HLT",.func = [this,&d] { return isData ? d.HLT_PFHT1050==1  : 1; }});
	else if(isMET) analysis_cuts['w'].push_back({ .name="HLT",.func = [this,&d] { return isData ? !(d.HLT_PFHT1050==1 ) && (d.HLT_PFHT500_PFMET100_PFMHT100_IDTight==1 || d.HLT_PFHT500_PFMET110_PFMHT110_IDTight==1 || d.HLT_PFHT700_PFMET85_PFMHT85_IDTight==1 || d.HLT_PFHT700_PFMET95_PFMHT95_IDTight==1 || d.HLT_PFHT800_PFMET75_PFMHT75_IDTight==1 || d.HLT_PFHT800_PFMET85_PFMHT85_IDTight==1) : 1; }});
	else      analysis_cuts['w'].push_back({ .name="HLT",.func = [this,&d] { return isData ? d.HLT_PFHT1050==1  || (d.HLT_PFHT500_PFMET100_PFMHT100_IDTight==1 || d.HLT_PFHT500_PFMET110_PFMHT110_IDTight==1 || d.HLT_PFHT700_PFMET85_PFMHT85_IDTight==1 || d.HLT_PFHT700_PFMET95_PFMHT95_IDTight==1 || d.HLT_PFHT800_PFMET75_PFMHT75_IDTight==1 || d.HLT_PFHT800_PFMET85_PFMHT85_IDTight==1) : 1; }});
	analysis_cuts['w'].push_back({ .name="1Lep",       .func = []    { return nLepSelect==1;                    }}); 
	analysis_cuts['w'].push_back({ .name="MET",        .func = [&d]  { return d.MET_pt>=30;                  }}); 
	analysis_cuts['w'].push_back({ .name="MT",         .func = []    { return MT>=30 && MT<100;                 }}); 
	
/*analysis_cuts['w'].push_back({ .name="0b",         .func = []    { return nLooseBTag==0;                    }}); 

	// T: Inclusive Razor-like Top enriched control sample
	analysis_cuts['t'].push_back({ .name="1JetAK8",    .func = []    { return nJetAK8>=1;                      }}); // Similar to pt>200, one AK8 jet has pt>200
	analysis_cuts['t'].push_back({ .name="NJet",       .func = []    { return nJet>=3;                          }});
	//analysis_cuts['t'].push_back({ .name="MR_R2",      .func = [&d]  { return MR>=800 && R2>=0.08;  }});
	//if(isJetHT) analysis_cuts['t'].push_back({ .name="HLT",.func = [this,&d] { return isData ? d.HLT_PFHT1050==1  : 1; }});
	//else if(isMET) analysis_cuts['t'].push_back({ .name="HLT",.func = [this,&d] { return isData ? !(d.HLT_PFHT1050==1 ) && (d.HLT_PFHT500_PFMET100_PFMHT100_IDTight==1 || d.HLT_PFHT500_PFMET110_PFMHT110_IDTight==1 || d.HLT_PFHT700_PFMET85_PFMHT85_IDTight==1 || d.HLT_PFHT700_PFMET95_PFMHT95_IDTight==1 || d.HLT_PFHT800_PFMET75_PFMHT75_IDTight==1 || d.HLT_PFHT800_PFMET85_PFMHT85_IDTight==1) : 1; }});
	//else      analysis_cuts['t'].push_back({ .name="HLT",.func = [this,&d] { return isData ? d.HLT_PFHT1050==1  || (d.HLT_PFHT500_PFMET100_PFMHT100_IDTight==1 || d.HLT_PFHT500_PFMET110_PFMHT110_IDTight==1 || d.HLT_PFHT700_PFMET85_PFMHT85_IDTight==1 || d.HLT_PFHT700_PFMET95_PFMHT95_IDTight==1 || d.HLT_PFHT800_PFMET75_PFMHT75_IDTight==1 || d.HLT_PFHT800_PFMET85_PFMHT85_IDTight==1) : 1; }});
	analysis_cuts['t'].push_back({ .name="1Lep",       .func = []    { return nLepVeto==1;                      }});
	analysis_cuts['t'].push_back({ .name="1b",         .func = []    { return nMediumBTag>=1;                   }});
	//analysis_cuts['t'].push_back({ .name="1W",         .func = []    { return nBoostMassTag>=1;                    }});
	//analysis_cuts['t'].push_back({ .name="mDPhi",      .func = []    { return dPhiRazor<2.8;                 }});
	analysis_cuts['t'].push_back({ .name="MT",         .func = []    { return MT_vetolep >=30 && MT_vetolep < 100; }});
*/

	// F: Fake rate measurement region
	analysis_cuts['F'].push_back({ .name="1JetAK8",    .func = []    { return nJetAK8>=1;                       }}); 
	analysis_cuts['F'].push_back({ .name="NJet",       .func = []    { return nJet>=3;                          }}); 
	analysis_cuts['F'].push_back({ .name="MR",         .func = [&d]  { return MR>=800;                    }}); 
	if(isJetHT) analysis_cuts['F'].push_back({ .name="HLT",.func = [this,&d] { return isData ? d.HLT_PFHT1050==1  : 1; }});
	else if(isMET) analysis_cuts['F'].push_back({ .name="HLT",.func = [this,&d] { return isData ? !(d.HLT_PFHT1050==1 ) && (d.HLT_PFHT500_PFMET100_PFMHT100_IDTight==1 || d.HLT_PFHT500_PFMET110_PFMHT110_IDTight==1 || d.HLT_PFHT700_PFMET85_PFMHT85_IDTight==1 || d.HLT_PFHT700_PFMET95_PFMHT95_IDTight==1 || d.HLT_PFHT800_PFMET75_PFMHT75_IDTight==1 || d.HLT_PFHT800_PFMET85_PFMHT85_IDTight==1) : 1; }});
	else      analysis_cuts['F'].push_back({ .name="HLT",.func = [this,&d] { return isData ? d.HLT_PFHT1050==1  || (d.HLT_PFHT500_PFMET100_PFMHT100_IDTight==1 || d.HLT_PFHT500_PFMET110_PFMHT110_IDTight==1 || d.HLT_PFHT700_PFMET85_PFMHT85_IDTight==1 || d.HLT_PFHT700_PFMET95_PFMHT95_IDTight==1 || d.HLT_PFHT800_PFMET75_PFMHT75_IDTight==1 || d.HLT_PFHT800_PFMET85_PFMHT85_IDTight==1) : 1; }});
	analysis_cuts['F'].push_back({ .name="0Ele",       .func = []    { return nEleVeto==0;                      }}); 
	analysis_cuts['F'].push_back({ .name="0Mu",        .func = []    { return nMuVeto==0;                       }}); 
	analysis_cuts['F'].push_back({ .name="0Tau",       .func = []    { return nTauVeto==0;                      }}); 
	analysis_cuts['F'].push_back({ .name="0b",         .func = []    { return nLooseBTag==0;                    }}); 
	//analysis_cuts['F'].push_back({ .name="InvmDPhi",.func = []    { return minDeltaPhi<0.3;                  }});
	analysis_cuts['F'].push_back({ .name="InvmDPhi",.func = []    { return dPhiRazor>=2.8;                   }}); 

	// F: F+1b
	analysis_cuts['f'].push_back({ .name="1JetAK8",    .func = []    { return nJetAK8>=1;                       }}); 
	analysis_cuts['f'].push_back({ .name="NJet",       .func = []    { return nJet>=3;                          }}); 
	analysis_cuts['f'].push_back({ .name="MR",         .func = [&d]  { return MR>=800;                    }}); 
	if(isJetHT) analysis_cuts['f'].push_back({ .name="HLT",.func = [this,&d] { return isData ? d.HLT_PFHT1050==1  : 1; }});
	else if(isMET) analysis_cuts['f'].push_back({ .name="HLT",.func = [this,&d] { return isData ? !(d.HLT_PFHT1050==1 ) && (d.HLT_PFHT500_PFMET100_PFMHT100_IDTight==1 || d.HLT_PFHT500_PFMET110_PFMHT110_IDTight==1 || d.HLT_PFHT700_PFMET85_PFMHT85_IDTight==1 || d.HLT_PFHT700_PFMET95_PFMHT95_IDTight==1 || d.HLT_PFHT800_PFMET75_PFMHT75_IDTight==1 || d.HLT_PFHT800_PFMET85_PFMHT85_IDTight==1) : 1; }});
	else      analysis_cuts['f'].push_back({ .name="HLT",.func = [this,&d] { return isData ? d.HLT_PFHT1050==1  || (d.HLT_PFHT500_PFMET100_PFMHT100_IDTight==1 || d.HLT_PFHT500_PFMET110_PFMHT110_IDTight==1 || d.HLT_PFHT700_PFMET85_PFMHT85_IDTight==1 || d.HLT_PFHT700_PFMET95_PFMHT95_IDTight==1 || d.HLT_PFHT800_PFMET75_PFMHT75_IDTight==1 || d.HLT_PFHT800_PFMET85_PFMHT85_IDTight==1) : 1; }});
	analysis_cuts['f'].push_back({ .name="0Ele",       .func = []    { return nEleVeto==0;                      }}); 
	analysis_cuts['f'].push_back({ .name="0Mu",        .func = []    { return nMuVeto==0;                       }}); 
	analysis_cuts['f'].push_back({ .name="0Tau",       .func = []    { return nTauVeto==0;                      }}); 
	analysis_cuts['f'].push_back({ .name="1b",         .func = []    { return nMediumBTag>=1;                   }}); 
	//analysis_cuts['f'].push_back({ .name="InvmDPhi",.func = []    { return minDeltaPhi<0.3;                  }});
	analysis_cuts['f'].push_back({ .name="InvmDPhi",.func = []    { return dPhiRazor>=2.8;                   }}); 

	// H: HT>=1TeV+1b
	analysis_cuts['H'].push_back({ .name="1JetAK8",    .func = []    { return nJetAK8>=1;                       }}); 
	analysis_cuts['H'].push_back({ .name="NJet",       .func = []    { return nJet>=3;                          }}); 
	analysis_cuts['H'].push_back({ .name="0Ele",       .func = []    { return nEleVeto==0;                      }}); 
	analysis_cuts['H'].push_back({ .name="0Mu",        .func = []    { return nMuVeto==0;                       }}); 
	analysis_cuts['H'].push_back({ .name="0Tau",       .func = []    { return nTauVeto==0;                      }});
	analysis_cuts['H'].push_back({ .name="1b",         .func = []    { return nMediumBTag>=1;                   }});
	analysis_cuts['H'].push_back({ .name="HT",         .func = []    { return AK4_Ht>=1000;                     }});

	// S': DPhi Control region of Signal region
	analysis_cuts['N'].push_back({ .name="1JetAK8",    .func = []    { return nJetAK8>=1;                      }}); // Similar to pt>200, one AK8 jet has pt>200
	analysis_cuts['N'].push_back({ .name="NJet",       .func = []    { return nJet>=3;                          }}); // Separate cut, so one can exclude (N-1)
	analysis_cuts['N'].push_back({ .name="MR_R2",      .func = [&d]  { return MR>=800 && R2>=0.08;  }});
	if(isJetHT) analysis_cuts['N'].push_back({ .name="HLT",.func = [this,&d] { return isData ? d.HLT_PFHT1050==1  : 1; }});
	else if(isMET) analysis_cuts['N'].push_back({ .name="HLT",.func = [this,&d] { return isData ? !(d.HLT_PFHT1050==1 ) && (d.HLT_PFHT500_PFMET100_PFMHT100_IDTight==1 || d.HLT_PFHT500_PFMET110_PFMHT110_IDTight==1 || d.HLT_PFHT700_PFMET85_PFMHT85_IDTight==1 || d.HLT_PFHT700_PFMET95_PFMHT95_IDTight==1 || d.HLT_PFHT800_PFMET75_PFMHT75_IDTight==1 || d.HLT_PFHT800_PFMET85_PFMHT85_IDTight==1) : 1; }});
	else      analysis_cuts['N'].push_back({ .name="HLT",.func = [this,&d] { return isData ? d.HLT_PFHT1050==1  || (d.HLT_PFHT500_PFMET100_PFMHT100_IDTight==1 || d.HLT_PFHT500_PFMET110_PFMHT110_IDTight==1 || d.HLT_PFHT700_PFMET85_PFMHT85_IDTight==1 || d.HLT_PFHT700_PFMET95_PFMHT95_IDTight==1 || d.HLT_PFHT800_PFMET75_PFMHT75_IDTight==1 || d.HLT_PFHT800_PFMET85_PFMHT85_IDTight==1) : 1; }});
	analysis_cuts['N'].push_back({ .name="0Ele",       .func = []    { return nEleVeto==0;                      }});
	analysis_cuts['N'].push_back({ .name="0Mu",        .func = []    { return nMuVeto==0;                       }});
	analysis_cuts['N'].push_back({ .name="0Tau",       .func = []    { return nTauVeto==0;                      }});
	//analysis_cuts['N'].push_back({ .name="1b",         .func = []    { return nMediumBTag>=1;                   }});
	analysis_cuts['N'].push_back({ .name="InvmDPhi",   .func = []    { return dPhiRazor>=2.8;                  }});

	// Q': new Dphi Control region of QCD enriched sample
	analysis_cuts['n'].push_back({ .name="1JetAK8",    .func = []    { return nJetAK8>=1;                      }}); // Similar to pt>200, one AK8 jet has pt>200
	analysis_cuts['n'].push_back({ .name="NJet",       .func = []    { return nJet>=3;                          }});
	analysis_cuts['n'].push_back({ .name="MR_R2",      .func = [&d]  { return MR>=800 && R2>=0.08;  }});
	if(isJetHT) analysis_cuts['n'].push_back({ .name="HLT",.func = [this,&d] { return isData ? d.HLT_PFHT1050==1  : 1; }});
	else if(isMET) analysis_cuts['n'].push_back({ .name="HLT",.func = [this,&d] { return isData ? !(d.HLT_PFHT1050==1 ) && (d.HLT_PFHT500_PFMET100_PFMHT100_IDTight==1 || d.HLT_PFHT500_PFMET110_PFMHT110_IDTight==1 || d.HLT_PFHT700_PFMET85_PFMHT85_IDTight==1 || d.HLT_PFHT700_PFMET95_PFMHT95_IDTight==1 || d.HLT_PFHT800_PFMET75_PFMHT75_IDTight==1 || d.HLT_PFHT800_PFMET85_PFMHT85_IDTight==1) : 1; }});
	else      analysis_cuts['n'].push_back({ .name="HLT",.func = [this,&d] { return isData ? d.HLT_PFHT1050==1  || (d.HLT_PFHT500_PFMET100_PFMHT100_IDTight==1 || d.HLT_PFHT500_PFMET110_PFMHT110_IDTight==1 || d.HLT_PFHT700_PFMET85_PFMHT85_IDTight==1 || d.HLT_PFHT700_PFMET95_PFMHT95_IDTight==1 || d.HLT_PFHT800_PFMET75_PFMHT75_IDTight==1 || d.HLT_PFHT800_PFMET85_PFMHT85_IDTight==1) : 1; }});
	analysis_cuts['n'].push_back({ .name="0Ele",       .func = []    { return nEleVeto==0;                      }});
	analysis_cuts['n'].push_back({ .name="0Mu",        .func = []    { return nMuVeto==0;                       }});
	analysis_cuts['n'].push_back({ .name="0Tau",       .func = []    { return nTauVeto==0;                      }});
	analysis_cuts['n'].push_back({ .name="0b",         .func = []    { return nLooseBTag==0;                    }});
	analysis_cuts['n'].push_back({ .name="mDPhi",      .func = []    { return dPhiRazor<2.8;                 }});

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
	double sf_w = calc_w_tagging_sf(data, nSigmaSFs[i][s], nSigmaSFs[i+1][s], nSigmaSFs[i+2][s], nSigmaSFs[i+3][s], isFastSim);
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
	scale_factors['S'].push_back(sf_w);

	scale_factors['s'] = scale_factors['S'];
	scale_factors['t'] = scale_factors['S'];

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
	scale_factors['f'].push_back(sf_ele_veto);
	scale_factors['f'].push_back(sf_muon_veto);
	scale_factors['f'].push_back(sf_btag_medium);

	scale_factors['N'].push_back(sf_ele_veto);
	scale_factors['N'].push_back(sf_muon_veto);
	//scale_factors['N'].push_back(sf_btag_medium);
	scale_factors['n'].push_back(sf_ele_veto);
	scale_factors['n'].push_back(sf_muon_veto);
	scale_factors['n'].push_back(sf_btag_loose);

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

//_______________________________________________________
//                 List of Histograms

TH1D* h_deepTagMD_WvsQCD_s;
TH1D* h_deepTagMD_WvsQCD_Q;
TH1D* h_deepTagMD_WvsQCD_q;
TH1D* h_deepTagMD_WvsQCD_T;
TH1D* h_deepTagMD_WvsQCD_W;
TH1D* h_deepTagMD_WvsQCD_Z;
TH1D* h_deepTagMD_WvsQCD_G;
TH1D* h_deepTagMD_WvsQCD_L;
TH1D* h_deepTagMD_TvsQCD_s;
TH1D* h_deepTagMD_TvsQCD_Q;
TH1D* h_deepTagMD_TvsQCD_q;
TH1D* h_deepTagMD_TvsQCD_T;
TH1D* h_deepTagMD_TvsQCD_W;
TH1D* h_deepTagMD_TvsQCD_Z;
TH1D* h_deepTagMD_TvsQCD_G;
TH1D* h_deepTagMD_TvsQCD_L;

TH1D* h_deepTag_WvsQCD_s;
TH1D* h_deepTag_WvsQCD_Q;
TH1D* h_deepTag_WvsQCD_q;
TH1D* h_deepTag_WvsQCD_T;
TH1D* h_deepTag_WvsQCD_W;
TH1D* h_deepTag_WvsQCD_Z;
TH1D* h_deepTag_WvsQCD_G;
TH1D* h_deepTag_WvsQCD_L;
TH1D* h_deepTag_TvsQCD_s;
TH1D* h_deepTag_TvsQCD_Q;
TH1D* h_deepTag_TvsQCD_q;
TH1D* h_deepTag_TvsQCD_T;
TH1D* h_deepTag_TvsQCD_W;
TH1D* h_deepTag_TvsQCD_Z;
TH1D* h_deepTag_TvsQCD_G;
TH1D* h_deepTag_TvsQCD_L;

TH1D* h_dR_min;
TH1D* h_rel_pT;
TH2D* h_rel_pT_dR_min;
TH1D* h_dR_min_tag;
TH1D* h_rel_pT_tag;
TH2D* h_rel_pT_dR_min_tag;
TH1D* h_dR_min_untag;
TH1D* h_rel_pT_untag;
TH2D* h_rel_pT_dR_min_untag;

TH1D* h_MR_T_1Lep;
TH1D* h_R2_T_1Lep;
TH2D* h_R2_MR_T_1Lep;
TH1D* h_MR_W_1Lep;
TH1D* h_R2_W_1Lep;
TH2D* h_R2_MR_W_1Lep;

TH1D* h_Megajets_pt_Wjet_S;
TH1D* h_Megajets_eta_Wjet_S;
TH1D* h_Megajets_phi_Wjet_S;
TH1D* h_njet_Wjet_S;
TH1D* h_nAK8jet_Wjet_S;
TH1D* h_ht_AK4_Wjet_S;
TH1D* h_MR_Wjet_S;
TH1D* h_R2_Wjet_S;
TH1D* h_MET_Wjet_S;
TH1D* h_MET_phi_Wjet_S;
TH1D* h_MET_phi_Wjet_S_nj45;
TH1D* h_MET_phi_Wjet_S_nj6;
TH1D* h_ht_AK4_Wjet_S_nj45;
TH1D* h_MR_Wjet_S_nj45;
TH1D* h_R2_Wjet_S_nj45;
TH1D* h_MET_Wjet_S_nj45;
TH1D* h_ht_AK4_Wjet_S_nj6;
TH1D* h_MR_Wjet_S_nj6;
TH1D* h_R2_Wjet_S_nj6;
TH1D* h_MET_Wjet_S_nj6;
TH2D* h_R2_MR_Wjet_S;
TH2D* h_MR_MET_Wjet_S;
TH2D* h_R2_MET_Wjet_S;
TH2D* h_HT_MET_Wjet_S;
TH2D* h_MR_HT_Wjet_S;
TH2D* h_R2_HT_Wjet_S;
TH2D* h_AK8Jet1pT_MET_Wjet_S;
TH2D* h_MR_MET_Wjet_S_nj45;
TH2D* h_R2_MET_Wjet_S_nj45;
TH2D* h_HT_MET_Wjet_S_nj45;
TH2D* h_MR_HT_Wjet_S_nj45;
TH2D* h_R2_HT_Wjet_S_nj45;
TH2D* h_AK8Jet1pT_MET_Wjet_S_nj45;
TH2D* h_MR_MET_Wjet_S_nj6;
TH2D* h_R2_MET_Wjet_S_nj6;
TH2D* h_HT_MET_Wjet_S_nj6;
TH2D* h_MR_HT_Wjet_S_nj6;
TH2D* h_R2_HT_Wjet_S_nj6;
TH2D* h_AK8Jet1pT_MET_Wjet_S_nj6;
TH2D* h_R2_MR_Wjet_S_nj45;
TH2D* h_R2_MR_Wjet_S_nj6;
TH1D* h_deepTagMD_WvsQCD_Wjet_S;
TH1D* h_deepTagMD_TvsQCD_Wjet_S;
TH1D* h_deepTag_WvsQCD_Wjet_S;
TH1D* h_deepTag_TvsQCD_Wjet_S;
TH1D* h_jet1_pt_Wjet_S;
TH1D* h_jet1_eta_Wjet_S;
TH1D* h_jet1_phi_Wjet_S;
TH1D* h_jets_pt_Wjet_S;
TH1D* h_jets_eta_Wjet_S;
TH1D* h_jets_phi_Wjet_S;
TH1D* h_AK8jet1_pt_Wjet_S;
TH1D* h_AK8jet1_eta_Wjet_S;
TH1D* h_AK8jet1_phi_Wjet_S;
TH1D* h_AK8jet1_tau21_Wjet_S;
TH1D* h_AK8jet1_tau32_Wjet_S;
TH1D* h_AK8jets_pt_Wjet_S;
TH1D* h_AK8jets_eta_Wjet_S;
TH1D* h_AK8jets_phi_Wjet_S;
TH1D* h_AK8jets_msoftdrop_Wjet_S;
TH1D* h_AK8jets_tau21_Wjet_S;
TH1D* h_AK8jets_tau32_Wjet_S;
TH1D* h_Wjets_pt_Wjet_S;
TH1D* h_Wjets_eta_Wjet_S;
TH1D* h_Wjets_phi_Wjet_S;
TH1D*	h_Wjets_tau21_Wjet_S;
TH1D*	h_Wjets_tau32_Wjet_S;
TH1D* h_jet1_pt_Wjet_S_nj45;
TH1D* h_jet1_eta_Wjet_S_nj45;
TH1D* h_jet1_phi_Wjet_S_nj45;
TH1D* h_jets_pt_Wjet_S_nj45;
TH1D* h_jets_eta_Wjet_S_nj45;
TH1D* h_jets_phi_Wjet_S_nj45;
TH1D* h_AK8jet1_pt_Wjet_S_nj45;
TH1D* h_AK8jet1_eta_Wjet_S_nj45;
TH1D* h_AK8jet1_phi_Wjet_S_nj45;
TH1D* h_AK8jet1_tau21_Wjet_S_nj45;
TH1D* h_AK8jet1_tau32_Wjet_S_nj45;
TH1D* h_AK8jets_pt_Wjet_S_nj45;
TH1D* h_AK8jets_eta_Wjet_S_nj45;
TH1D* h_AK8jets_phi_Wjet_S_nj45;
TH1D* h_AK8jets_msoftdrop_Wjet_S_nj45;
TH1D* h_AK8jets_tau21_Wjet_S_nj45;
TH1D* h_AK8jets_tau32_Wjet_S_nj45;
TH1D* h_Wjets_pt_Wjet_S_nj45;
TH1D* h_Wjets_eta_Wjet_S_nj45;
TH1D* h_Wjets_phi_Wjet_S_nj45;
TH1D*	h_Wjets_tau21_Wjet_S_nj45;
TH1D*	h_Wjets_tau32_Wjet_S_nj45;
TH1D* h_jet1_pt_Wjet_S_nj6;
TH1D* h_jet1_eta_Wjet_S_nj6;
TH1D* h_jet1_phi_Wjet_S_nj6;
TH1D* h_jets_pt_Wjet_S_nj6;
TH1D* h_jets_eta_Wjet_S_nj6;
TH1D* h_jets_phi_Wjet_S_nj6;
TH1D* h_AK8jet1_pt_Wjet_S_nj6;
TH1D* h_AK8jet1_eta_Wjet_S_nj6;
TH1D* h_AK8jet1_phi_Wjet_S_nj6;
TH1D* h_AK8jet1_tau21_Wjet_S_nj6;
TH1D* h_AK8jet1_tau32_Wjet_S_nj6;
TH1D* h_AK8jets_pt_Wjet_S_nj6;
TH1D* h_AK8jets_eta_Wjet_S_nj6;
TH1D* h_AK8jets_phi_Wjet_S_nj6;
TH1D* h_AK8jets_msoftdrop_Wjet_S_nj6;
TH1D* h_AK8jets_tau21_Wjet_S_nj6;
TH1D* h_AK8jets_tau32_Wjet_S_nj6;
TH1D* h_Wjets_pt_Wjet_S_nj6;
TH1D* h_Wjets_eta_Wjet_S_nj6;
TH1D* h_Wjets_phi_Wjet_S_nj6;
TH1D*	h_Wjets_tau21_Wjet_S_nj6;
TH1D*	h_Wjets_tau32_Wjet_S_nj6;

TH1D* h_Megajets_pt_Topjet_S;
TH1D* h_Megajets_eta_Topjet_S;
TH1D* h_Megajets_phi_Topjet_S;
TH1D* h_njet_Topjet_S;
TH1D* h_nAK8jet_Topjet_S;
TH1D* h_ht_AK4_Topjet_S;
TH1D* h_MR_Topjet_S;
TH1D* h_R2_Topjet_S;
TH1D* h_MET_Topjet_S;
TH1D* h_MET_phi_Topjet_S;
TH1D* h_MET_phi_Topjet_S_nj45;
TH1D* h_MET_phi_Topjet_S_nj6;
TH1D* h_ht_AK4_Topjet_S_nj45;
TH1D* h_MR_Topjet_S_nj45;
TH1D* h_R2_Topjet_S_nj45;
TH1D* h_MET_Topjet_S_nj45;
TH1D* h_ht_AK4_Topjet_S_nj6;
TH1D* h_MR_Topjet_S_nj6;
TH1D* h_R2_Topjet_S_nj6;
TH1D* h_MET_Topjet_S_nj6;
TH2D* h_R2_MR_Topjet_S;
TH2D* h_MR_MET_Topjet_S;
TH2D* h_R2_MET_Topjet_S;
TH2D* h_HT_MET_Topjet_S;
TH2D* h_MR_HT_Topjet_S;
TH2D* h_R2_HT_Topjet_S;
TH2D* h_AK8Jet1pT_MET_Topjet_S;
TH2D* h_MR_MET_Topjet_S_nj45;
TH2D* h_R2_MET_Topjet_S_nj45;
TH2D* h_HT_MET_Topjet_S_nj45;
TH2D* h_MR_HT_Topjet_S_nj45;
TH2D* h_R2_HT_Topjet_S_nj45;
TH2D* h_AK8Jet1pT_MET_Topjet_S_nj45;
TH2D* h_MR_MET_Topjet_S_nj6;
TH2D* h_R2_MET_Topjet_S_nj6;
TH2D* h_HT_MET_Topjet_S_nj6;
TH2D* h_MR_HT_Topjet_S_nj6;
TH2D* h_R2_HT_Topjet_S_nj6;
TH2D* h_AK8Jet1pT_MET_Topjet_S_nj6;
TH2D* h_R2_MR_Topjet_S_nj45;
TH2D* h_R2_MR_Topjet_S_nj6;
TH1D* h_deepTagMD_WvsQCD_Topjet_S;
TH1D* h_deepTagMD_TvsQCD_Topjet_S;
TH1D* h_deepTag_WvsQCD_Topjet_S;
TH1D* h_deepTag_TvsQCD_Topjet_S;
TH1D* h_jet1_pt_Topjet_S;
TH1D* h_jet1_eta_Topjet_S;
TH1D* h_jet1_phi_Topjet_S;
TH1D* h_jets_pt_Topjet_S;
TH1D* h_jets_eta_Topjet_S;
TH1D* h_jets_phi_Topjet_S;
TH1D* h_AK8jet1_pt_Topjet_S;
TH1D* h_AK8jet1_eta_Topjet_S;
TH1D* h_AK8jet1_phi_Topjet_S;
TH1D* h_AK8jet1_tau21_Topjet_S;
TH1D* h_AK8jet1_tau32_Topjet_S;
TH1D* h_AK8jets_pt_Topjet_S;
TH1D* h_AK8jets_eta_Topjet_S;
TH1D* h_AK8jets_phi_Topjet_S;
TH1D* h_AK8jets_msoftdrop_Topjet_S;
TH1D* h_AK8jets_tau21_Topjet_S;
TH1D* h_AK8jets_tau32_Topjet_S;
TH1D* h_Topjets_pt_Topjet_S;
TH1D* h_Topjets_eta_Topjet_S;
TH1D* h_Topjets_phi_Topjet_S;
TH1D*	h_Topjets_tau21_Topjet_S;
TH1D*	h_Topjets_tau32_Topjet_S;
TH1D* h_jet1_pt_Topjet_S_nj45;
TH1D* h_jet1_eta_Topjet_S_nj45;
TH1D* h_jet1_phi_Topjet_S_nj45;
TH1D* h_jets_pt_Topjet_S_nj45;
TH1D* h_jets_eta_Topjet_S_nj45;
TH1D* h_jets_phi_Topjet_S_nj45;
TH1D* h_AK8jet1_pt_Topjet_S_nj45;
TH1D* h_AK8jet1_eta_Topjet_S_nj45;
TH1D* h_AK8jet1_phi_Topjet_S_nj45;
TH1D* h_AK8jet1_tau21_Topjet_S_nj45;
TH1D* h_AK8jet1_tau32_Topjet_S_nj45;
TH1D* h_AK8jets_pt_Topjet_S_nj45;
TH1D* h_AK8jets_eta_Topjet_S_nj45;
TH1D* h_AK8jets_phi_Topjet_S_nj45;
TH1D* h_AK8jets_msoftdrop_Topjet_S_nj45;
TH1D* h_AK8jets_tau21_Topjet_S_nj45;
TH1D* h_AK8jets_tau32_Topjet_S_nj45;
TH1D* h_Topjets_pt_Topjet_S_nj45;
TH1D* h_Topjets_eta_Topjet_S_nj45;
TH1D* h_Topjets_phi_Topjet_S_nj45;
TH1D*	h_Topjets_tau21_Topjet_S_nj45;
TH1D*	h_Topjets_tau32_Topjet_S_nj45;
TH1D* h_jet1_pt_Topjet_S_nj6;
TH1D* h_jet1_eta_Topjet_S_nj6;
TH1D* h_jet1_phi_Topjet_S_nj6;
TH1D* h_jets_pt_Topjet_S_nj6;
TH1D* h_jets_eta_Topjet_S_nj6;
TH1D* h_jets_phi_Topjet_S_nj6;
TH1D* h_AK8jet1_pt_Topjet_S_nj6;
TH1D* h_AK8jet1_eta_Topjet_S_nj6;
TH1D* h_AK8jet1_phi_Topjet_S_nj6;
TH1D* h_AK8jet1_tau21_Topjet_S_nj6;
TH1D* h_AK8jet1_tau32_Topjet_S_nj6;
TH1D* h_AK8jets_pt_Topjet_S_nj6;
TH1D* h_AK8jets_eta_Topjet_S_nj6;
TH1D* h_AK8jets_phi_Topjet_S_nj6;
TH1D* h_AK8jets_msoftdrop_Topjet_S_nj6;
TH1D* h_AK8jets_tau21_Topjet_S_nj6;
TH1D* h_AK8jets_tau32_Topjet_S_nj6;
TH1D* h_Topjets_pt_Topjet_S_nj6;
TH1D* h_Topjets_eta_Topjet_S_nj6;
TH1D* h_Topjets_phi_Topjet_S_nj6;
TH1D*	h_Topjets_tau21_Topjet_S_nj6;
TH1D*	h_Topjets_tau32_Topjet_S_nj6;

TH1D* h_jet1_pt_s;
TH1D* h_jet1_eta_s;
TH1D* h_jet1_phi_s;
TH1D* h_jets_pt_s;
TH1D* h_jets_eta_s;
TH1D* h_jets_phi_s;
TH1D* h_AK8jet1_pt_s;
TH1D* h_AK8jet1_eta_s;
TH1D* h_AK8jet1_phi_s;
TH1D* h_AK8jet1_tau21_s;
TH1D* h_AK8jet1_tau32_s;
TH1D* h_AK8jets_pt_s;
TH1D* h_AK8jets_eta_s;
TH1D* h_AK8jets_phi_s;
TH1D* h_AK8jets_msoftdrop_s;
TH1D* h_AK8jets_tau21_s;
TH1D* h_AK8jets_tau32_s;
#if TOP == 0
TH1D* h_Wjets_pt_s;
TH1D* h_Wjets_eta_s;
TH1D* h_Wjets_phi_s;
TH1D*	h_Wjets_tau21_s;
TH1D*	h_Wjets_tau32_s;
#else
TH1D* h_Topjets_pt_s;
TH1D* h_Topjets_eta_s;
TH1D* h_Topjets_phi_s;
TH1D*	h_Topjets_tau21_s;
TH1D*	h_Topjets_tau32_s;
#endif
TH1D* h_jet1_pt_s_nj45;
TH1D* h_jet1_eta_s_nj45;
TH1D* h_jet1_phi_s_nj45;
TH1D* h_jets_pt_s_nj45;
TH1D* h_jets_eta_s_nj45;
TH1D* h_jets_phi_s_nj45;
TH1D* h_AK8jet1_pt_s_nj45;
TH1D* h_AK8jet1_eta_s_nj45;
TH1D* h_AK8jet1_phi_s_nj45;
TH1D* h_AK8jet1_tau21_s_nj45;
TH1D* h_AK8jet1_tau32_s_nj45;
TH1D* h_AK8jets_pt_s_nj45;
TH1D* h_AK8jets_eta_s_nj45;
TH1D* h_AK8jets_phi_s_nj45;
TH1D* h_AK8jets_msoftdrop_s_nj45;
TH1D* h_AK8jets_tau21_s_nj45;
TH1D* h_AK8jets_tau32_s_nj45;
#if TOP == 0
TH1D* h_Wjets_pt_s_nj45;
TH1D* h_Wjets_eta_s_nj45;
TH1D* h_Wjets_phi_s_nj45;
TH1D*	h_Wjets_tau21_s_nj45;
TH1D*	h_Wjets_tau32_s_nj45;
#else
TH1D* h_Topjets_pt_s_nj45;
TH1D* h_Topjets_eta_s_nj45;
TH1D* h_Topjets_phi_s_nj45;
TH1D*	h_Topjets_tau21_s_nj45;
TH1D*	h_Topjets_tau32_s_nj45;
#endif
TH1D* h_jet1_pt_s_nj6;
TH1D* h_jet1_eta_s_nj6;
TH1D* h_jet1_phi_s_nj6;
TH1D* h_jets_pt_s_nj6;
TH1D* h_jets_eta_s_nj6;
TH1D* h_jets_phi_s_nj6;
TH1D* h_AK8jet1_pt_s_nj6;
TH1D* h_AK8jet1_eta_s_nj6;
TH1D* h_AK8jet1_phi_s_nj6;
TH1D* h_AK8jet1_tau21_s_nj6;
TH1D* h_AK8jet1_tau32_s_nj6;
TH1D* h_AK8jets_pt_s_nj6;
TH1D* h_AK8jets_eta_s_nj6;
TH1D* h_AK8jets_phi_s_nj6;
TH1D* h_AK8jets_msoftdrop_s_nj6;
TH1D* h_AK8jets_tau21_s_nj6;
TH1D* h_AK8jets_tau32_s_nj6;
#if TOP == 0
TH1D* h_Wjets_pt_s_nj6;
TH1D* h_Wjets_eta_s_nj6;
TH1D* h_Wjets_phi_s_nj6;
TH1D*	h_Wjets_tau21_s_nj6;
TH1D*	h_Wjets_tau32_s_nj6;
#else
TH1D* h_Topjets_pt_s_nj6;
TH1D* h_Topjets_eta_s_nj6;
TH1D* h_Topjets_phi_s_nj6;
TH1D*	h_Topjets_tau21_s_nj6;
TH1D*	h_Topjets_tau32_s_nj6;
#endif

TH1D* h_jet1_pt_Q;
TH1D* h_jet1_eta_Q;
TH1D* h_jet1_phi_Q;
TH1D* h_jets_pt_Q;
TH1D* h_jets_eta_Q;
TH1D* h_jets_phi_Q;
TH1D* h_AK8jet1_pt_Q;
TH1D* h_AK8jet1_eta_Q;
TH1D* h_AK8jet1_phi_Q;
TH1D* h_AK8jet1_tau21_Q;
TH1D* h_AK8jet1_tau32_Q;
TH1D* h_AK8jets_pt_Q;
TH1D* h_AK8jets_eta_Q;
TH1D* h_AK8jets_phi_Q;
TH1D* h_AK8jets_msoftdrop_Q;
TH1D* h_AK8jets_tau21_Q;
TH1D* h_AK8jets_tau32_Q;
#if TOP == 0
TH1D* h_Wjets_pt_Q;
TH1D* h_Wjets_eta_Q;
TH1D* h_Wjets_phi_Q;
TH1D*	h_Wjets_tau21_Q;
TH1D*	h_Wjets_tau32_Q;
#else
TH1D* h_Topjets_pt_Q;
TH1D* h_Topjets_eta_Q;
TH1D* h_Topjets_phi_Q;
TH1D*	h_Topjets_tau21_Q;
TH1D*	h_Topjets_tau32_Q;
#endif
TH1D* h_jet1_pt_Q_nj45;
TH1D* h_jet1_eta_Q_nj45;
TH1D* h_jet1_phi_Q_nj45;
TH1D* h_jets_pt_Q_nj45;
TH1D* h_jets_eta_Q_nj45;
TH1D* h_jets_phi_Q_nj45;
TH1D* h_AK8jet1_pt_Q_nj45;
TH1D* h_AK8jet1_eta_Q_nj45;
TH1D* h_AK8jet1_phi_Q_nj45;
TH1D* h_AK8jet1_tau21_Q_nj45;
TH1D* h_AK8jet1_tau32_Q_nj45;
TH1D* h_AK8jets_pt_Q_nj45;
TH1D* h_AK8jets_eta_Q_nj45;
TH1D* h_AK8jets_phi_Q_nj45;
TH1D* h_AK8jets_msoftdrop_Q_nj45;
TH1D* h_AK8jets_tau21_Q_nj45;
TH1D* h_AK8jets_tau32_Q_nj45;
#if TOP == 0
TH1D* h_Wjets_pt_Q_nj45;
TH1D* h_Wjets_eta_Q_nj45;
TH1D* h_Wjets_phi_Q_nj45;
TH1D*	h_Wjets_tau21_Q_nj45;
TH1D*	h_Wjets_tau32_Q_nj45;
#else
TH1D* h_Topjets_pt_Q_nj45;
TH1D* h_Topjets_eta_Q_nj45;
TH1D* h_Topjets_phi_Q_nj45;
TH1D*	h_Topjets_tau21_Q_nj45;
TH1D*	h_Topjets_tau32_Q_nj45;
#endif
TH1D* h_jet1_pt_Q_nj6;
TH1D* h_jet1_eta_Q_nj6;
TH1D* h_jet1_phi_Q_nj6;
TH1D* h_jets_pt_Q_nj6;
TH1D* h_jets_eta_Q_nj6;
TH1D* h_jets_phi_Q_nj6;
TH1D* h_AK8jet1_pt_Q_nj6;
TH1D* h_AK8jet1_eta_Q_nj6;
TH1D* h_AK8jet1_phi_Q_nj6;
TH1D* h_AK8jet1_tau21_Q_nj6;
TH1D* h_AK8jet1_tau32_Q_nj6;
TH1D* h_AK8jets_pt_Q_nj6;
TH1D* h_AK8jets_eta_Q_nj6;
TH1D* h_AK8jets_phi_Q_nj6;
TH1D* h_AK8jets_msoftdrop_Q_nj6;
TH1D* h_AK8jets_tau21_Q_nj6;
TH1D* h_AK8jets_tau32_Q_nj6;
#if TOP == 0
TH1D* h_Wjets_pt_Q_nj6;
TH1D* h_Wjets_eta_Q_nj6;
TH1D* h_Wjets_phi_Q_nj6;
TH1D*	h_Wjets_tau21_Q_nj6;
TH1D*	h_Wjets_tau32_Q_nj6;
#else
TH1D* h_Topjets_pt_Q_nj6;
TH1D* h_Topjets_eta_Q_nj6;
TH1D* h_Topjets_phi_Q_nj6;
TH1D*	h_Topjets_tau21_Q_nj6;
TH1D*	h_Topjets_tau32_Q_nj6;
#endif

TH1D* h_jet1_pt_q;
TH1D* h_jet1_eta_q;
TH1D* h_jet1_phi_q;
TH1D* h_jets_pt_q;
TH1D* h_jets_eta_q;
TH1D* h_jets_phi_q;
TH1D* h_AK8jet1_pt_q;
TH1D* h_AK8jet1_eta_q;
TH1D* h_AK8jet1_phi_q;
TH1D* h_AK8jet1_tau21_q;
TH1D* h_AK8jet1_tau32_q;
TH1D* h_AK8jets_pt_q;
TH1D* h_AK8jets_eta_q;
TH1D* h_AK8jets_phi_q;
TH1D* h_AK8jets_msoftdrop_q;
TH1D* h_AK8jets_tau21_q;
TH1D* h_AK8jets_tau32_q;
#if TOP == 0
TH1D* h_Wjets_pt_q;
TH1D* h_Wjets_eta_q;
TH1D* h_Wjets_phi_q;
TH1D*	h_Wjets_tau21_q;
TH1D*	h_Wjets_tau32_q;
#else
TH1D* h_Topjets_pt_q;
TH1D* h_Topjets_eta_q;
TH1D* h_Topjets_phi_q;
TH1D*	h_Topjets_tau21_q;
TH1D*	h_Topjets_tau32_q;
#endif
TH1D* h_jet1_pt_q_nj45;
TH1D* h_jet1_eta_q_nj45;
TH1D* h_jet1_phi_q_nj45;
TH1D* h_jets_pt_q_nj45;
TH1D* h_jets_eta_q_nj45;
TH1D* h_jets_phi_q_nj45;
TH1D* h_AK8jet1_pt_q_nj45;
TH1D* h_AK8jet1_eta_q_nj45;
TH1D* h_AK8jet1_phi_q_nj45;
TH1D* h_AK8jet1_tau21_q_nj45;
TH1D* h_AK8jet1_tau32_q_nj45;
TH1D* h_AK8jets_pt_q_nj45;
TH1D* h_AK8jets_eta_q_nj45;
TH1D* h_AK8jets_phi_q_nj45;
TH1D* h_AK8jets_msoftdrop_q_nj45;
TH1D* h_AK8jets_tau21_q_nj45;
TH1D* h_AK8jets_tau32_q_nj45;
#if TOP == 0
TH1D* h_Wjets_pt_q_nj45;
TH1D* h_Wjets_eta_q_nj45;
TH1D* h_Wjets_phi_q_nj45;
TH1D*	h_Wjets_tau21_q_nj45;
TH1D*	h_Wjets_tau32_q_nj45;
#else
TH1D* h_Topjets_pt_q_nj45;
TH1D* h_Topjets_eta_q_nj45;
TH1D* h_Topjets_phi_q_nj45;
TH1D*	h_Topjets_tau21_q_nj45;
TH1D*	h_Topjets_tau32_q_nj45;
#endif
TH1D* h_jet1_pt_q_nj6;
TH1D* h_jet1_eta_q_nj6;
TH1D* h_jet1_phi_q_nj6;
TH1D* h_jets_pt_q_nj6;
TH1D* h_jets_eta_q_nj6;
TH1D* h_jets_phi_q_nj6;
TH1D* h_AK8jet1_pt_q_nj6;
TH1D* h_AK8jet1_eta_q_nj6;
TH1D* h_AK8jet1_phi_q_nj6;
TH1D* h_AK8jet1_tau21_q_nj6;
TH1D* h_AK8jet1_tau32_q_nj6;
TH1D* h_AK8jets_pt_q_nj6;
TH1D* h_AK8jets_eta_q_nj6;
TH1D* h_AK8jets_phi_q_nj6;
TH1D* h_AK8jets_msoftdrop_q_nj6;
TH1D* h_AK8jets_tau21_q_nj6;
TH1D* h_AK8jets_tau32_q_nj6;
#if TOP == 0
TH1D* h_Wjets_pt_q_nj6;
TH1D* h_Wjets_eta_q_nj6;
TH1D* h_Wjets_phi_q_nj6;
TH1D*	h_Wjets_tau21_q_nj6;
TH1D*	h_Wjets_tau32_q_nj6;
#else
TH1D* h_Topjets_pt_q_nj6;
TH1D* h_Topjets_eta_q_nj6;
TH1D* h_Topjets_phi_q_nj6;
TH1D*	h_Topjets_tau21_q_nj6;
TH1D*	h_Topjets_tau32_q_nj6;
#endif

TH1D* h_jet1_pt_T;
TH1D* h_jet1_eta_T;
TH1D* h_jet1_phi_T;
TH1D* h_jets_pt_T;
TH1D* h_jets_eta_T;
TH1D* h_jets_phi_T;
TH1D* h_AK8jet1_pt_T;
TH1D* h_AK8jet1_eta_T;
TH1D* h_AK8jet1_phi_T;
TH1D* h_AK8jet1_tau21_T;
TH1D* h_AK8jet1_tau32_T;
TH1D* h_AK8jets_pt_T;
TH1D* h_AK8jets_eta_T;
TH1D* h_AK8jets_phi_T;
TH1D* h_AK8jets_msoftdrop_T;
TH1D* h_AK8jets_tau21_T;
TH1D* h_AK8jets_tau32_T;
#if TOP == 0
TH1D* h_Wjets_pt_T;
TH1D* h_Wjets_eta_T;
TH1D* h_Wjets_phi_T;
TH1D*	h_Wjets_tau21_T;
TH1D*	h_Wjets_tau32_T;
#else
TH1D* h_Topjets_pt_T;
TH1D* h_Topjets_eta_T;
TH1D* h_Topjets_phi_T;
TH1D*	h_Topjets_tau21_T;
TH1D*	h_Topjets_tau32_T;
#endif
TH1D* h_jet1_pt_T_nj45;
TH1D* h_jet1_eta_T_nj45;
TH1D* h_jet1_phi_T_nj45;
TH1D* h_jets_pt_T_nj45;
TH1D* h_jets_eta_T_nj45;
TH1D* h_jets_phi_T_nj45;
TH1D* h_AK8jet1_pt_T_nj45;
TH1D* h_AK8jet1_eta_T_nj45;
TH1D* h_AK8jet1_phi_T_nj45;
TH1D* h_AK8jet1_tau21_T_nj45;
TH1D* h_AK8jet1_tau32_T_nj45;
TH1D* h_AK8jets_pt_T_nj45;
TH1D* h_AK8jets_eta_T_nj45;
TH1D* h_AK8jets_phi_T_nj45;
TH1D* h_AK8jets_msoftdrop_T_nj45;
TH1D* h_AK8jets_tau21_T_nj45;
TH1D* h_AK8jets_tau32_T_nj45;
#if TOP == 0
TH1D* h_Wjets_pt_T_nj45;
TH1D* h_Wjets_eta_T_nj45;
TH1D* h_Wjets_phi_T_nj45;
TH1D*	h_Wjets_tau21_T_nj45;
TH1D*	h_Wjets_tau32_T_nj45;
#else
TH1D* h_Topjets_pt_T_nj45;
TH1D* h_Topjets_eta_T_nj45;
TH1D* h_Topjets_phi_T_nj45;
TH1D*	h_Topjets_tau21_T_nj45;
TH1D*	h_Topjets_tau32_T_nj45;
#endif
TH1D* h_jet1_pt_T_nj6;
TH1D* h_jet1_eta_T_nj6;
TH1D* h_jet1_phi_T_nj6;
TH1D* h_jets_pt_T_nj6;
TH1D* h_jets_eta_T_nj6;
TH1D* h_jets_phi_T_nj6;
TH1D* h_AK8jet1_pt_T_nj6;
TH1D* h_AK8jet1_eta_T_nj6;
TH1D* h_AK8jet1_phi_T_nj6;
TH1D* h_AK8jet1_tau21_T_nj6;
TH1D* h_AK8jet1_tau32_T_nj6;
TH1D* h_AK8jets_pt_T_nj6;
TH1D* h_AK8jets_eta_T_nj6;
TH1D* h_AK8jets_phi_T_nj6;
TH1D* h_AK8jets_msoftdrop_T_nj6;
TH1D* h_AK8jets_tau21_T_nj6;
TH1D* h_AK8jets_tau32_T_nj6;
#if TOP == 0
TH1D* h_Wjets_pt_T_nj6;
TH1D* h_Wjets_eta_T_nj6;
TH1D* h_Wjets_phi_T_nj6;
TH1D*	h_Wjets_tau21_T_nj6;
TH1D*	h_Wjets_tau32_T_nj6;
#else
TH1D* h_Topjets_pt_T_nj6;
TH1D* h_Topjets_eta_T_nj6;
TH1D* h_Topjets_phi_T_nj6;
TH1D*	h_Topjets_tau21_T_nj6;
TH1D*	h_Topjets_tau32_T_nj6;
#endif

TH1D* h_jet1_pt_W;
TH1D* h_jet1_eta_W;
TH1D* h_jet1_phi_W;
TH1D* h_jets_pt_W;
TH1D* h_jets_eta_W;
TH1D* h_jets_phi_W;
TH1D* h_AK8jet1_pt_W;
TH1D* h_AK8jet1_eta_W;
TH1D* h_AK8jet1_phi_W;
TH1D* h_AK8jet1_tau21_W;
TH1D* h_AK8jet1_tau32_W;
TH1D* h_AK8jets_pt_W;
TH1D* h_AK8jets_eta_W;
TH1D* h_AK8jets_phi_W;
TH1D* h_AK8jets_msoftdrop_W;
TH1D* h_AK8jets_tau21_W;
TH1D* h_AK8jets_tau32_W;
#if TOP == 0
TH1D* h_Wjets_pt_W;
TH1D* h_Wjets_eta_W;
TH1D* h_Wjets_phi_W;
TH1D*	h_Wjets_tau21_W;
TH1D*	h_Wjets_tau32_W;
#else
TH1D* h_Topjets_pt_W;
TH1D* h_Topjets_eta_W;
TH1D* h_Topjets_phi_W;
TH1D*	h_Topjets_tau21_W;
TH1D*	h_Topjets_tau32_W;
#endif
TH1D* h_jet1_pt_W_nj45;
TH1D* h_jet1_eta_W_nj45;
TH1D* h_jet1_phi_W_nj45;
TH1D* h_jets_pt_W_nj45;
TH1D* h_jets_eta_W_nj45;
TH1D* h_jets_phi_W_nj45;
TH1D* h_AK8jet1_pt_W_nj45;
TH1D* h_AK8jet1_eta_W_nj45;
TH1D* h_AK8jet1_phi_W_nj45;
TH1D* h_AK8jet1_tau21_W_nj45;
TH1D* h_AK8jet1_tau32_W_nj45;
TH1D* h_AK8jets_pt_W_nj45;
TH1D* h_AK8jets_eta_W_nj45;
TH1D* h_AK8jets_phi_W_nj45;
TH1D* h_AK8jets_msoftdrop_W_nj45;
TH1D* h_AK8jets_tau21_W_nj45;
TH1D* h_AK8jets_tau32_W_nj45;
#if TOP == 0
TH1D* h_Wjets_pt_W_nj45;
TH1D* h_Wjets_eta_W_nj45;
TH1D* h_Wjets_phi_W_nj45;
TH1D*	h_Wjets_tau21_W_nj45;
TH1D*	h_Wjets_tau32_W_nj45;
#else
TH1D* h_Topjets_pt_W_nj45;
TH1D* h_Topjets_eta_W_nj45;
TH1D* h_Topjets_phi_W_nj45;
TH1D*	h_Topjets_tau21_W_nj45;
TH1D*	h_Topjets_tau32_W_nj45;
#endif
TH1D* h_jet1_pt_W_nj6;
TH1D* h_jet1_eta_W_nj6;
TH1D* h_jet1_phi_W_nj6;
TH1D* h_jets_pt_W_nj6;
TH1D* h_jets_eta_W_nj6;
TH1D* h_jets_phi_W_nj6;
TH1D* h_AK8jet1_pt_W_nj6;
TH1D* h_AK8jet1_eta_W_nj6;
TH1D* h_AK8jet1_phi_W_nj6;
TH1D* h_AK8jet1_tau21_W_nj6;
TH1D* h_AK8jet1_tau32_W_nj6;
TH1D* h_AK8jets_pt_W_nj6;
TH1D* h_AK8jets_eta_W_nj6;
TH1D* h_AK8jets_phi_W_nj6;
TH1D* h_AK8jets_msoftdrop_W_nj6;
TH1D* h_AK8jets_tau21_W_nj6;
TH1D* h_AK8jets_tau32_W_nj6;
#if TOP == 0
TH1D* h_Wjets_pt_W_nj6;
TH1D* h_Wjets_eta_W_nj6;
TH1D* h_Wjets_phi_W_nj6;
TH1D*	h_Wjets_tau21_W_nj6;
TH1D*	h_Wjets_tau32_W_nj6;
#else
TH1D* h_Topjets_pt_W_nj6;
TH1D* h_Topjets_eta_W_nj6;
TH1D* h_Topjets_phi_W_nj6;
TH1D*	h_Topjets_tau21_W_nj6;
TH1D*	h_Topjets_tau32_W_nj6;
#endif

TH1D* h_jet1_pt_L;
TH1D* h_jet1_eta_L;
TH1D* h_jet1_phi_L;
TH1D* h_jets_pt_L;
TH1D* h_jets_eta_L;
TH1D* h_jets_phi_L;
TH1D* h_AK8jet1_pt_L;
TH1D* h_AK8jet1_eta_L;
TH1D* h_AK8jet1_phi_L;
TH1D* h_AK8jet1_tau21_L;
TH1D* h_AK8jet1_tau32_L;
TH1D* h_AK8jets_pt_L;
TH1D* h_AK8jets_eta_L;
TH1D* h_AK8jets_phi_L;
TH1D* h_AK8jets_msoftdrop_L;
TH1D* h_AK8jets_tau21_L;
TH1D* h_AK8jets_tau32_L;
#if TOP == 0
TH1D* h_Wjets_pt_L;
TH1D* h_Wjets_eta_L;
TH1D* h_Wjets_phi_L;
TH1D*	h_Wjets_tau21_L;
TH1D*	h_Wjets_tau32_L;
#else
TH1D* h_Topjets_pt_L;
TH1D* h_Topjets_eta_L;
TH1D* h_Topjets_phi_L;
TH1D*	h_Topjets_tau21_L;
TH1D*	h_Topjets_tau32_L;
#endif
TH1D* h_jet1_pt_L_nj45;
TH1D* h_jet1_eta_L_nj45;
TH1D* h_jet1_phi_L_nj45;
TH1D* h_jets_pt_L_nj45;
TH1D* h_jets_eta_L_nj45;
TH1D* h_jets_phi_L_nj45;
TH1D* h_AK8jet1_pt_L_nj45;
TH1D* h_AK8jet1_eta_L_nj45;
TH1D* h_AK8jet1_phi_L_nj45;
TH1D* h_AK8jet1_tau21_L_nj45;
TH1D* h_AK8jet1_tau32_L_nj45;
TH1D* h_AK8jets_pt_L_nj45;
TH1D* h_AK8jets_eta_L_nj45;
TH1D* h_AK8jets_phi_L_nj45;
TH1D* h_AK8jets_msoftdrop_L_nj45;
TH1D* h_AK8jets_tau21_L_nj45;
TH1D* h_AK8jets_tau32_L_nj45;
#if TOP == 0
TH1D* h_Wjets_pt_L_nj45;
TH1D* h_Wjets_eta_L_nj45;
TH1D* h_Wjets_phi_L_nj45;
TH1D*	h_Wjets_tau21_L_nj45;
TH1D*	h_Wjets_tau32_L_nj45;
#else
TH1D* h_Topjets_pt_L_nj45;
TH1D* h_Topjets_eta_L_nj45;
TH1D* h_Topjets_phi_L_nj45;
TH1D*	h_Topjets_tau21_L_nj45;
TH1D*	h_Topjets_tau32_L_nj45;
#endif
TH1D* h_jet1_pt_L_nj6;
TH1D* h_jet1_eta_L_nj6;
TH1D* h_jet1_phi_L_nj6;
TH1D* h_jets_pt_L_nj6;
TH1D* h_jets_eta_L_nj6;
TH1D* h_jets_phi_L_nj6;
TH1D* h_AK8jet1_pt_L_nj6;
TH1D* h_AK8jet1_eta_L_nj6;
TH1D* h_AK8jet1_phi_L_nj6;
TH1D* h_AK8jet1_tau21_L_nj6;
TH1D* h_AK8jet1_tau32_L_nj6;
TH1D* h_AK8jets_pt_L_nj6;
TH1D* h_AK8jets_eta_L_nj6;
TH1D* h_AK8jets_phi_L_nj6;
TH1D* h_AK8jets_msoftdrop_L_nj6;
TH1D* h_AK8jets_tau21_L_nj6;
TH1D* h_AK8jets_tau32_L_nj6;
#if TOP == 0
TH1D* h_Wjets_pt_L_nj6;
TH1D* h_Wjets_eta_L_nj6;
TH1D* h_Wjets_phi_L_nj6;
TH1D*	h_Wjets_tau21_L_nj6;
TH1D*	h_Wjets_tau32_L_nj6;
#else
TH1D* h_Topjets_pt_L_nj6;
TH1D* h_Topjets_eta_L_nj6;
TH1D* h_Topjets_phi_L_nj6;
TH1D*	h_Topjets_tau21_L_nj6;
TH1D*	h_Topjets_tau32_L_nj6;
#endif

TH1D* h_jet1_pt_Z;
TH1D* h_jet1_eta_Z;
TH1D* h_jet1_phi_Z;
TH1D* h_jets_pt_Z;
TH1D* h_jets_eta_Z;
TH1D* h_jets_phi_Z;
TH1D* h_AK8jet1_pt_Z;
TH1D* h_AK8jet1_eta_Z;
TH1D* h_AK8jet1_phi_Z;
TH1D* h_AK8jet1_tau21_Z;
TH1D* h_AK8jet1_tau32_Z;
TH1D* h_AK8jets_pt_Z;
TH1D* h_AK8jets_eta_Z;
TH1D* h_AK8jets_phi_Z;
TH1D* h_AK8jets_msoftdrop_Z;
TH1D* h_AK8jets_tau21_Z;
TH1D* h_AK8jets_tau32_Z;
#if TOP == 0
TH1D* h_Wjets_pt_Z;
TH1D* h_Wjets_eta_Z;
TH1D* h_Wjets_phi_Z;
TH1D*	h_Wjets_tau21_Z;
TH1D*	h_Wjets_tau32_Z;
#else
TH1D* h_Topjets_pt_Z;
TH1D* h_Topjets_eta_Z;
TH1D* h_Topjets_phi_Z;
TH1D*	h_Topjets_tau21_Z;
TH1D*	h_Topjets_tau32_Z;
#endif
TH1D* h_jet1_pt_Z_nj45;
TH1D* h_jet1_eta_Z_nj45;
TH1D* h_jet1_phi_Z_nj45;
TH1D* h_jets_pt_Z_nj45;
TH1D* h_jets_eta_Z_nj45;
TH1D* h_jets_phi_Z_nj45;
TH1D* h_AK8jet1_pt_Z_nj45;
TH1D* h_AK8jet1_eta_Z_nj45;
TH1D* h_AK8jet1_phi_Z_nj45;
TH1D* h_AK8jet1_tau21_Z_nj45;
TH1D* h_AK8jet1_tau32_Z_nj45;
TH1D* h_AK8jets_pt_Z_nj45;
TH1D* h_AK8jets_eta_Z_nj45;
TH1D* h_AK8jets_phi_Z_nj45;
TH1D* h_AK8jets_msoftdrop_Z_nj45;
TH1D* h_AK8jets_tau21_Z_nj45;
TH1D* h_AK8jets_tau32_Z_nj45;
#if TOP == 0
TH1D* h_Wjets_pt_Z_nj45;
TH1D* h_Wjets_eta_Z_nj45;
TH1D* h_Wjets_phi_Z_nj45;
TH1D*	h_Wjets_tau21_Z_nj45;
TH1D*	h_Wjets_tau32_Z_nj45;
#else
TH1D* h_Topjets_pt_Z_nj45;
TH1D* h_Topjets_eta_Z_nj45;
TH1D* h_Topjets_phi_Z_nj45;
TH1D*	h_Topjets_tau21_Z_nj45;
TH1D*	h_Topjets_tau32_Z_nj45;
#endif
TH1D* h_AK8jet1_pt_Z_nj6;
TH1D* h_AK8jet1_eta_Z_nj6;
TH1D* h_AK8jet1_phi_Z_nj6;
TH1D* h_AK8jet1_tau21_Z_nj6;
TH1D* h_AK8jet1_tau32_Z_nj6;
TH1D* h_AK8jets_pt_Z_nj6;
TH1D* h_AK8jets_eta_Z_nj6;
TH1D* h_AK8jets_phi_Z_nj6;
TH1D* h_AK8jets_msoftdrop_Z_nj6;
TH1D* h_AK8jets_tau21_Z_nj6;
TH1D* h_AK8jets_tau32_Z_nj6;
#if TOP == 0
TH1D* h_Wjets_pt_Z_nj6;
TH1D* h_Wjets_eta_Z_nj6;
TH1D* h_Wjets_phi_Z_nj6;
TH1D*	h_Wjets_tau21_Z_nj6;
TH1D*	h_Wjets_tau32_Z_nj6;
#else
TH1D* h_Topjets_pt_Z_nj6;
TH1D* h_Topjets_eta_Z_nj6;
TH1D* h_Topjets_phi_Z_nj6;
TH1D*	h_Topjets_tau21_Z_nj6;
TH1D*	h_Topjets_tau32_Z_nj6;
#endif
TH1D* h_jet1_pt_Z_nj6;
TH1D* h_jet1_eta_Z_nj6;
TH1D* h_jet1_phi_Z_nj6;
TH1D* h_jets_pt_Z_nj6;
TH1D* h_jets_eta_Z_nj6;
TH1D* h_jets_phi_Z_nj6;

TH1D* h_jet1_pt_G;
TH1D* h_jet1_eta_G;
TH1D* h_jet1_phi_G;
TH1D* h_jets_pt_G;
TH1D* h_jets_eta_G;
TH1D* h_jets_phi_G;
TH1D* h_AK8jet1_pt_G;
TH1D* h_AK8jet1_eta_G;
TH1D* h_AK8jet1_phi_G;
TH1D* h_AK8jet1_tau21_G;
TH1D* h_AK8jet1_tau32_G;
TH1D* h_AK8jets_pt_G;
TH1D* h_AK8jets_eta_G;
TH1D* h_AK8jets_phi_G;
TH1D* h_AK8jets_msoftdrop_G;
TH1D* h_AK8jets_tau21_G;
TH1D* h_AK8jets_tau32_G;
#if TOP == 0
TH1D* h_Wjets_pt_G;
TH1D* h_Wjets_eta_G;
TH1D* h_Wjets_phi_G;
TH1D*	h_Wjets_tau21_G;
TH1D*	h_Wjets_tau32_G;
#else
TH1D* h_Topjets_pt_G;
TH1D* h_Topjets_eta_G;
TH1D* h_Topjets_phi_G;
TH1D*	h_Topjets_tau21_G;
TH1D*	h_Topjets_tau32_G;
#endif
TH1D* h_jet1_pt_G_nj45;
TH1D* h_jet1_eta_G_nj45;
TH1D* h_jet1_phi_G_nj45;
TH1D* h_jets_pt_G_nj45;
TH1D* h_jets_eta_G_nj45;
TH1D* h_jets_phi_G_nj45;
TH1D* h_AK8jet1_pt_G_nj45;
TH1D* h_AK8jet1_eta_G_nj45;
TH1D* h_AK8jet1_phi_G_nj45;
TH1D* h_AK8jet1_tau21_G_nj45;
TH1D* h_AK8jet1_tau32_G_nj45;
TH1D* h_AK8jets_pt_G_nj45;
TH1D* h_AK8jets_eta_G_nj45;
TH1D* h_AK8jets_phi_G_nj45;
TH1D* h_AK8jets_msoftdrop_G_nj45;
TH1D* h_AK8jets_tau21_G_nj45;
TH1D* h_AK8jets_tau32_G_nj45;
#if TOP == 0
TH1D* h_Wjets_pt_G_nj45;
TH1D* h_Wjets_eta_G_nj45;
TH1D* h_Wjets_phi_G_nj45;
TH1D*	h_Wjets_tau21_G_nj45;
TH1D*	h_Wjets_tau32_G_nj45;
#else
TH1D* h_Topjets_pt_G_nj45;
TH1D* h_Topjets_eta_G_nj45;
TH1D* h_Topjets_phi_G_nj45;
TH1D*	h_Topjets_tau21_G_nj45;
TH1D*	h_Topjets_tau32_G_nj45;
#endif
TH1D* h_jet1_pt_G_nj6;
TH1D* h_jet1_eta_G_nj6;
TH1D* h_jet1_phi_G_nj6;
TH1D* h_jets_pt_G_nj6;
TH1D* h_jets_eta_G_nj6;
TH1D* h_jets_phi_G_nj6;
TH1D* h_AK8jet1_pt_G_nj6;
TH1D* h_AK8jet1_eta_G_nj6;
TH1D* h_AK8jet1_phi_G_nj6;
TH1D* h_AK8jet1_tau21_G_nj6;
TH1D* h_AK8jet1_tau32_G_nj6;
TH1D* h_AK8jets_pt_G_nj6;
TH1D* h_AK8jets_eta_G_nj6;
TH1D* h_AK8jets_phi_G_nj6;
TH1D* h_AK8jets_msoftdrop_G_nj6;
TH1D* h_AK8jets_tau21_G_nj6;
TH1D* h_AK8jets_tau32_G_nj6;
#if TOP == 0
TH1D* h_Wjets_pt_G_nj6;
TH1D* h_Wjets_eta_G_nj6;
TH1D* h_Wjets_phi_G_nj6;
TH1D*	h_Wjets_tau21_G_nj6;
TH1D*	h_Wjets_tau32_G_nj6;
#else
TH1D* h_Topjets_pt_G_nj6;
TH1D* h_Topjets_eta_G_nj6;
TH1D* h_Topjets_phi_G_nj6;
TH1D*	h_Topjets_tau21_G_nj6;
TH1D*	h_Topjets_tau32_G_nj6;
#endif
TH1D* h_photon_pt_G;
TH1D* h_photon_pt_G_nj45;
TH1D* h_photon_pt_G_nj6;
TH1D* h_photon_eta_G;
TH1D* h_photon_eta_G_nj45;
TH1D* h_photon_eta_G_nj6;
TH1D* h_photon_phi_G;
TH1D* h_photon_phi_G_nj45;
TH1D* h_photon_phi_G_nj6;

TH1D* h_jet1_pt_P;
TH1D* h_jet1_eta_P;
TH1D* h_jet1_phi_P;
TH1D* h_jets_pt_P;
TH1D* h_jets_eta_P;
TH1D* h_jets_phi_P;
TH1D* h_AK8jet1_pt_P;
TH1D* h_AK8jet1_eta_P;
TH1D* h_AK8jet1_phi_P;
TH1D* h_AK8jet1_tau21_P;
TH1D* h_AK8jet1_tau32_P;
TH1D* h_AK8jets_pt_P;
TH1D* h_AK8jets_eta_P;
TH1D* h_AK8jets_phi_P;
TH1D* h_AK8jets_msoftdrop_P;
TH1D* h_AK8jets_tau21_P;
TH1D* h_AK8jets_tau32_P;

TH1D* h_ht_AK4_P;
TH1D* h_MET_P;
TH1D* h_MR_P;
TH1D* h_R2_P;

TH1D* h_njet_P;
TH1D* h_nAK8jet_P;
TH1D* h_nbTight_P;
TH1D* h_nbMedium_P;
TH1D* h_nbLoose_P;
TH1D* h_nw_P;
TH1D* h_nEleVeto_P;
TH1D* h_nEleTight_P;
TH1D* h_nEleMedium_P;
TH1D* h_nEleLoose_P;
TH1D* h_nMuTight_P;
TH1D* h_nMuMedium_P;
TH1D* h_nMuSoft_P;
TH1D* h_nTauVeto_P;
TH1D* h_nIsoTrack_P;
TH1D* h_nPhoMedium_P;

TH1D* h_ele_pt_T;
TH1D* h_ele_pt_W;
TH1D* h_ele_pt_L;
TH1D* h_mu_pt_T;
TH1D* h_mu_pt_W;
TH1D* h_mu_pt_L;

TH1D* h_Megajets_pt_P;
TH1D* h_Megajets_eta_P;
TH1D* h_Megajets_phi_P;
TH1D* h_Megajets_pt_s;
TH1D* h_Megajets_eta_s;
TH1D* h_Megajets_phi_s;
TH1D* h_Megajets_pt_Q;
TH1D* h_Megajets_eta_Q;
TH1D* h_Megajets_phi_Q;
TH1D* h_Megajets_pt_q;
TH1D* h_Megajets_eta_q;
TH1D* h_Megajets_phi_q;
TH1D* h_Megajets_pt_T;
TH1D* h_Megajets_eta_T;
TH1D* h_Megajets_phi_T;
TH1D* h_Megajets_pt_W;
TH1D* h_Megajets_eta_W;
TH1D* h_Megajets_phi_W;
TH1D* h_Megajets_pt_Z;
TH1D* h_Megajets_eta_Z;
TH1D* h_Megajets_phi_Z;
TH1D* h_Megajets_pt_G;
TH1D* h_Megajets_eta_G;
TH1D* h_Megajets_phi_G;
TH1D* h_Megajets_pt_L;
TH1D* h_Megajets_eta_L;
TH1D* h_Megajets_phi_L;

TH1D* h_njet_s;
TH1D* h_nAK8jet_s;
TH1D* h_njet_Q;
TH1D* h_nAK8jet_Q;
TH1D* h_njet_q;
TH1D* h_nAK8jet_q;
TH1D* h_njet_T;
TH1D* h_nAK8jet_T;
TH1D* h_njet_W;
TH1D* h_nAK8jet_W;
TH1D* h_njet_Z;
TH1D* h_nAK8jet_Z;
TH1D* h_njet_G;
TH1D* h_nAK8jet_G;
TH1D* h_njet_L;
TH1D* h_nAK8jet_L;

TH1D* h_ht_AK4_s;
TH1D* h_MR_s;
TH1D* h_R2_s;
TH1D* h_MET_s;
TH1D* h_MET_phi_s;
TH1D* h_MET_phi_s_nj45;
TH1D* h_MET_phi_s_nj6;
TH1D* h_mDPhi_nomDPhi_s;
TH1D* h_mDPhi_nomDPhi_s_nj45;
TH1D* h_mDPhi_nomDPhi_s_nj6;
#if TOP == 0
TH1D* h_nW_nonW_s;
TH1D* h_nW_nonW_s_nj45;
TH1D* h_nW_nonW_s_nj6;

TH1D* h_nb_nonb_s;
TH1D* h_nb_nonb_s_nj45;
TH1D* h_nb_nonb_s_nj6;
#else
TH1D* h_nTop_nonTop_s;
TH1D* h_nTop_nonTop_s_nj45;
TH1D* h_nTop_nonTop_s_nj6;
#endif

#if TOP == 0
TH1D* h_nW_nonW_q;
TH1D* h_nW_nonW_q_nj45;
TH1D* h_nW_nonW_q_nj6;
#else
TH1D* h_nTop_nonTop_q;
TH1D* h_nTop_nonTop_q_nj45;
TH1D* h_nTop_nonTop_q_nj6;
#endif
TH1D* h_nb_nonb_q;
TH1D* h_nb_nonb_q_nj45;
TH1D* h_nb_nonb_q_nj6;

TH1D* h_ht_AK4_s_nj45;
TH1D* h_MR_s_nj45;
TH1D* h_R2_s_nj45;
TH1D* h_MET_s_nj45;

TH1D* h_ht_AK4_s_nj6;
TH1D* h_MR_s_nj6;
TH1D* h_R2_s_nj6;
TH1D* h_MET_s_nj6;

TH1D* h_ht_AK4_G;
TH1D* h_MR_G;
TH1D* h_R2_G;
TH1D* h_MET_G;
TH1D* h_MET_phi_G;
TH1D* h_MET_phi_G_nj45;
TH1D* h_MET_phi_G_nj6;

TH1D* h_ht_AK4_G_nj45;
TH1D* h_MR_G_nj45;
TH1D* h_R2_G_nj45;
TH1D* h_MET_G_nj45;

TH1D* h_ht_AK4_G_nj6;
TH1D* h_MR_G_nj6;
TH1D* h_R2_G_nj6;
TH1D* h_MET_G_nj6;
TH1D* h_MET_pho_G;
TH1D* h_MET_pho_G_nj45;
TH1D* h_MET_pho_G_nj6;

TH1D* h_ht_AK4_no0Lep_G;
TH1D* h_MR_no0Lep_G;
TH1D* h_R2_no0Lep_G;
TH1D* h_MET_no0Lep_G;
TH1D* h_nLep_no0Lep_G;

TH1D* h_ht_AK4_no1Pho_G;
TH1D* h_MR_no1Pho_G;
TH1D* h_R2_no1Pho_G;
TH1D* h_MET_no1Pho_G;
TH1D* h_nPho_no1Pho_G;

TH1D* h_ht_AK4_nomDPhi_G;
TH1D* h_MR_nomDPhi_G;
TH1D* h_R2_nomDPhi_G;
TH1D* h_MET_nomDPhi_G;
TH1D* h_mDPhi_nomDPhi_G;

TH1D* h_ht_AK4_no0Lep_G_nj45;
TH1D* h_MR_no0Lep_G_nj45;
TH1D* h_R2_no0Lep_G_nj45;
TH1D* h_MET_no0Lep_G_nj45;
TH1D* h_nLep_no0Lep_G_nj45;

TH1D* h_ht_AK4_no1Pho_G_nj45;
TH1D* h_MR_no1Pho_G_nj45;
TH1D* h_R2_no1Pho_G_nj45;
TH1D* h_MET_no1Pho_G_nj45;
TH1D* h_nPho_no1Pho_G_nj45;

TH1D* h_ht_AK4_nomDPhi_G_nj45;
TH1D* h_MR_nomDPhi_G_nj45;
TH1D* h_R2_nomDPhi_G_nj45;
TH1D* h_MET_nomDPhi_G_nj45;
TH1D* h_mDPhi_nomDPhi_G_nj45;

TH1D* h_ht_AK4_no0Lep_G_nj6;
TH1D* h_MR_no0Lep_G_nj6;
TH1D* h_R2_no0Lep_G_nj6;
TH1D* h_MET_no0Lep_G_nj6;
TH1D* h_nLep_no0Lep_G_nj6;

TH1D* h_ht_AK4_no1Pho_G_nj6;
TH1D* h_MR_no1Pho_G_nj6;
TH1D* h_R2_no1Pho_G_nj6;
TH1D* h_MET_no1Pho_G_nj6;
TH1D* h_nPho_no1Pho_G_nj6;

TH1D* h_ht_AK4_nomDPhi_G_nj6;
TH1D* h_MR_nomDPhi_G_nj6;
TH1D* h_R2_nomDPhi_G_nj6;
TH1D* h_MET_nomDPhi_G_nj6;
TH1D* h_mDPhi_nomDPhi_G_nj6;

#if TOP == 0
TH1D* h_ht_AK4_nonW_G;
TH1D* h_MR_nonW_G;
TH1D* h_R2_nonW_G;
TH1D* h_MET_nonW_G;
TH1D* h_nW_nonW_G;

TH1D* h_ht_AK4_nonW_G_nj45;
TH1D* h_MR_nonW_G_nj45;
TH1D* h_R2_nonW_G_nj45;
TH1D* h_MET_nonW_G_nj45;
TH1D* h_nW_nonW_G_nj45;

TH1D* h_ht_AK4_nonW_G_nj6;
TH1D* h_MR_nonW_G_nj6;
TH1D* h_R2_nonW_G_nj6;
TH1D* h_MET_nonW_G_nj6;
TH1D* h_nW_nonW_G_nj6;
#else
TH1D* h_ht_AK4_nonTop_G;
TH1D* h_MR_nonTop_G;
TH1D* h_R2_nonTop_G;
TH1D* h_MET_nonTop_G;
TH1D* h_nTop_nonTop_G;

TH1D* h_ht_AK4_nonTop_G_nj45;
TH1D* h_MR_nonTop_G_nj45;
TH1D* h_R2_nonTop_G_nj45;
TH1D* h_MET_nonTop_G_nj45;
TH1D* h_nTop_nonTop_G_nj45;

TH1D* h_ht_AK4_nonTop_G_nj6;
TH1D* h_MR_nonTop_G_nj6;
TH1D* h_R2_nonTop_G_nj6;
TH1D* h_MET_nonTop_G_nj6;
TH1D* h_nTop_nonTop_G_nj6;
#endif
TH1D* h_ht_AK4_Z;
TH1D* h_MR_Z;
TH1D* h_R2_Z;
TH1D* h_MET_Z;
TH1D* h_MET_phi_Z;
TH1D* h_MET_phi_Z_nj45;
TH1D* h_MET_phi_Z_nj6;

TH1D* h_ht_AK4_Z_nj45;
TH1D* h_MR_Z_nj45;
TH1D* h_R2_Z_nj45;
TH1D* h_MET_Z_nj45;

TH1D* h_ht_AK4_Z_nj6;
TH1D* h_MR_Z_nj6;
TH1D* h_R2_Z_nj6;
TH1D* h_MET_Z_nj6;

TH1D* h_ht_AK4_no2Lep_Z;
TH1D* h_MR_no2Lep_Z;
TH1D* h_R2_no2Lep_Z;
TH1D* h_MET_no2Lep_Z;
TH1D* h_nLep_no2Lep_Z;

TH1D* h_ht_AK4_nomDPhi_Z;
TH1D* h_MR_nomDPhi_Z;
TH1D* h_R2_nomDPhi_Z;
TH1D* h_MET_nomDPhi_Z;
TH1D* h_mDPhi_nomDPhi_Z;

TH1D* h_ht_AK4_noMll_Z;
TH1D* h_MR_noMll_Z;
TH1D* h_R2_noMll_Z;
TH1D* h_MET_noMll_Z;
TH1D* h_Mll_noMll_Z;

TH1D* h_ht_AK4_no2Lep_Z_nj45;
TH1D* h_MR_no2Lep_Z_nj45;
TH1D* h_R2_no2Lep_Z_nj45;
TH1D* h_MET_no2Lep_Z_nj45;
TH1D* h_nLep_no2Lep_Z_nj45;

TH1D* h_ht_AK4_nomDPhi_Z_nj45;
TH1D* h_MR_nomDPhi_Z_nj45;
TH1D* h_R2_nomDPhi_Z_nj45;
TH1D* h_MET_nomDPhi_Z_nj45;
TH1D* h_mDPhi_nomDPhi_Z_nj45;

TH1D* h_ht_AK4_noMll_Z_nj45;
TH1D* h_MR_noMll_Z_nj45;
TH1D* h_R2_noMll_Z_nj45;
TH1D* h_MET_noMll_Z_nj45;
TH1D* h_Mll_noMll_Z_nj45;

TH1D* h_ht_AK4_no2Lep_Z_nj6;
TH1D* h_MR_no2Lep_Z_nj6;
TH1D* h_R2_no2Lep_Z_nj6;
TH1D* h_MET_no2Lep_Z_nj6;
TH1D* h_nLep_no2Lep_Z_nj6;

TH1D* h_ht_AK4_noMll_Z_nj6;
TH1D* h_MR_noMll_Z_nj6;
TH1D* h_R2_noMll_Z_nj6;
TH1D* h_MET_noMll_Z_nj6;
TH1D* h_Mll_noMll_Z_nj6;

TH1D* h_ht_AK4_nomDPhi_Z_nj6;
TH1D* h_MR_nomDPhi_Z_nj6;
TH1D* h_R2_nomDPhi_Z_nj6;
TH1D* h_MET_nomDPhi_Z_nj6;
TH1D* h_mDPhi_nomDPhi_Z_nj6;

#if TOP == 0
TH1D* h_ht_AK4_nonW_Z;
TH1D* h_MR_nonW_Z;
TH1D* h_R2_nonW_Z;
TH1D* h_MET_nonW_Z;
TH1D* h_nW_nonW_Z;

TH1D* h_ht_AK4_nonW_Z_nj45;
TH1D* h_MR_nonW_Z_nj45;
TH1D* h_R2_nonW_Z_nj45;
TH1D* h_MET_nonW_Z_nj45;
TH1D* h_nW_nonW_Z_nj45;

TH1D* h_ht_AK4_nonW_Z_nj6;
TH1D* h_MR_nonW_Z_nj6;
TH1D* h_R2_nonW_Z_nj6;
TH1D* h_MET_nonW_Z_nj6;
TH1D* h_nW_nonW_Z_nj6;
#else
TH1D* h_ht_AK4_nonTop_Z;
TH1D* h_MR_nonTop_Z;
TH1D* h_R2_nonTop_Z;
TH1D* h_MET_nonTop_Z;
TH1D* h_nTop_nonTop_Z;

TH1D* h_ht_AK4_nonTop_Z_nj45;
TH1D* h_MR_nonTop_Z_nj45;
TH1D* h_R2_nonTop_Z_nj45;
TH1D* h_MET_nonTop_Z_nj45;
TH1D* h_nTop_nonTop_Z_nj45;

TH1D* h_ht_AK4_nonTop_Z_nj6;
TH1D* h_MR_nonTop_Z_nj6;
TH1D* h_R2_nonTop_Z_nj6;
TH1D* h_MET_nonTop_Z_nj6;
TH1D* h_nTop_nonTop_Z_nj6;
#endif

TH1D* h_ht_AK4_L;
TH1D* h_MR_L;
TH1D* h_R2_L;
TH1D* h_MET_L;
TH1D* h_MET_phi_L;
TH1D* h_MET_phi_L_nj45;
TH1D* h_MET_phi_L_nj6;

TH1D* h_ht_AK4_L_nj45;
TH1D* h_MR_L_nj45;
TH1D* h_R2_L_nj45;
TH1D* h_MET_L_nj45;

TH1D* h_ht_AK4_L_nj6;
TH1D* h_MR_L_nj6;
TH1D* h_R2_L_nj6;
TH1D* h_MET_L_nj6;

TH1D* h_ht_AK4_no1Lep_L;
TH1D* h_MR_no1Lep_L;
TH1D* h_R2_no1Lep_L;
TH1D* h_MET_no1Lep_L;
TH1D* h_nLep_no1Lep_L;

TH1D* h_ht_AK4_no0b_L;
TH1D* h_MR_no0b_L;
TH1D* h_R2_no0b_L;
TH1D* h_MET_no0b_L;
TH1D* h_nb_no0b_L;

TH1D* h_ht_AK4_nomDPhi_L;
TH1D* h_MR_nomDPhi_L;
TH1D* h_R2_nomDPhi_L;
TH1D* h_MET_nomDPhi_L;
TH1D* h_mDPhi_nomDPhi_L;

TH1D* h_ht_AK4_noMT_L;
TH1D* h_MR_noMT_L;
TH1D* h_R2_noMT_L;
TH1D* h_MET_noMT_L;
TH1D* h_MT_noMT_L;

TH1D* h_ht_AK4_no1Lep_L_nj45;
TH1D* h_MR_no1Lep_L_nj45;
TH1D* h_R2_no1Lep_L_nj45;
TH1D* h_MET_no1Lep_L_nj45;
TH1D* h_nLep_no1Lep_L_nj45;

TH1D* h_ht_AK4_no0b_L_nj45;
TH1D* h_MR_no0b_L_nj45;
TH1D* h_R2_no0b_L_nj45;
TH1D* h_MET_no0b_L_nj45;
TH1D* h_nb_no0b_L_nj45;

TH1D* h_ht_AK4_nomDPhi_L_nj45;
TH1D* h_MR_nomDPhi_L_nj45;
TH1D* h_R2_nomDPhi_L_nj45;
TH1D* h_MET_nomDPhi_L_nj45;
TH1D* h_mDPhi_nomDPhi_L_nj45;

TH1D* h_ht_AK4_noMT_L_nj45;
TH1D* h_MR_noMT_L_nj45;
TH1D* h_R2_noMT_L_nj45;
TH1D* h_MET_noMT_L_nj45;
TH1D* h_MT_noMT_L_nj45;

TH1D* h_ht_AK4_no1Lep_L_nj6;
TH1D* h_MR_no1Lep_L_nj6;
TH1D* h_R2_no1Lep_L_nj6;
TH1D* h_MET_no1Lep_L_nj6;
TH1D* h_nLep_no1Lep_L_nj6;

TH1D* h_ht_AK4_no0b_L_nj6;
TH1D* h_MR_no0b_L_nj6;
TH1D* h_R2_no0b_L_nj6;
TH1D* h_MET_no0b_L_nj6;
TH1D* h_nb_no0b_L_nj6;

TH1D* h_ht_AK4_nomDPhi_L_nj6;
TH1D* h_MR_nomDPhi_L_nj6;
TH1D* h_R2_nomDPhi_L_nj6;
TH1D* h_MET_nomDPhi_L_nj6;
TH1D* h_mDPhi_nomDPhi_L_nj6;

TH1D* h_ht_AK4_noMT_L_nj6;
TH1D* h_MR_noMT_L_nj6;
TH1D* h_R2_noMT_L_nj6;
TH1D* h_MET_noMT_L_nj6;
TH1D* h_MT_noMT_L_nj6;

#if TOP == 0
TH1D* h_ht_AK4_nonW_L;
TH1D* h_MR_nonW_L;
TH1D* h_R2_nonW_L;
TH1D* h_MET_nonW_L;
TH1D* h_nW_nonW_L;

TH1D* h_ht_AK4_nonW_L_nj45;
TH1D* h_MR_nonW_L_nj45;
TH1D* h_R2_nonW_L_nj45;
TH1D* h_MET_nonW_L_nj45;
TH1D* h_nW_nonW_L_nj45;

TH1D* h_ht_AK4_nonW_L_nj6;
TH1D* h_MR_nonW_L_nj6;
TH1D* h_R2_nonW_L_nj6;
TH1D* h_MET_nonW_L_nj6;
TH1D* h_nW_nonW_L_nj6;
#else
TH1D* h_ht_AK4_nonTop_L;
TH1D* h_MR_nonTop_L;
TH1D* h_R2_nonTop_L;
TH1D* h_MET_nonTop_L;
TH1D* h_nTop_nonTop_L;

TH1D* h_ht_AK4_nonTop_L_nj45;
TH1D* h_MR_nonTop_L_nj45;
TH1D* h_R2_nonTop_L_nj45;
TH1D* h_MET_nonTop_L_nj45;
TH1D* h_nTop_nonTop_L_nj45;

TH1D* h_ht_AK4_nonTop_L_nj6;
TH1D* h_MR_nonTop_L_nj6;
TH1D* h_R2_nonTop_L_nj6;
TH1D* h_MET_nonTop_L_nj6;
TH1D* h_nTop_nonTop_L_nj6;
#endif
TH1D* h_ht_AK4_Q;
TH1D* h_MR_Q;
TH1D* h_R2_Q;
TH1D* h_MET_Q;
TH1D* h_MET_phi_Q;
TH1D* h_MET_phi_Q_nj45;
TH1D* h_MET_phi_Q_nj6;

TH1D* h_ht_AK4_nomDPhi_Q;
TH1D* h_MR_nomDPhi_Q;
TH1D* h_R2_nomDPhi_Q;
TH1D* h_MET_nomDPhi_Q;
TH1D* h_mDPhi_nomDPhi_Q;

TH1D* h_ht_AK4_no0Lep_Q;
TH1D* h_MR_no0Lep_Q;
TH1D* h_R2_no0Lep_Q;
TH1D* h_MET_no0Lep_Q;
TH1D* h_nLep_no0Lep_Q;

TH1D* h_ht_AK4_nonb_Q;
TH1D* h_MR_nonb_Q;
TH1D* h_R2_nonb_Q;
TH1D* h_MET_nonb_Q;
TH1D* h_nb_nonb_Q;


TH1D* h_ht_AK4_Q_nj45;
TH1D* h_MR_Q_nj45;
TH1D* h_R2_Q_nj45;
TH1D* h_MET_Q_nj45;

TH1D* h_ht_AK4_nomDPhi_Q_nj45;
TH1D* h_MR_nomDPhi_Q_nj45;
TH1D* h_R2_nomDPhi_Q_nj45;
TH1D* h_MET_nomDPhi_Q_nj45;
TH1D* h_mDPhi_nomDPhi_Q_nj45;

TH1D* h_ht_AK4_no0Lep_Q_nj45;
TH1D* h_MR_no0Lep_Q_nj45;
TH1D* h_R2_no0Lep_Q_nj45;
TH1D* h_MET_no0Lep_Q_nj45;
TH1D* h_nLep_no0Lep_Q_nj45;

TH1D* h_ht_AK4_nonb_Q_nj45;
TH1D* h_MR_nonb_Q_nj45;
TH1D* h_R2_nonb_Q_nj45;
TH1D* h_MET_nonb_Q_nj45;
TH1D* h_nb_nonb_Q_nj45;

TH1D* h_ht_AK4_Q_nj6;
TH1D* h_MR_Q_nj6;
TH1D* h_R2_Q_nj6;
TH1D* h_MET_Q_nj6;

TH1D* h_ht_AK4_nomDPhi_Q_nj6;
TH1D* h_MR_nomDPhi_Q_nj6;
TH1D* h_R2_nomDPhi_Q_nj6;
TH1D* h_MET_nomDPhi_Q_nj6;
TH1D* h_mDPhi_nomDPhi_Q_nj6;

TH1D* h_ht_AK4_no0Lep_Q_nj6;
TH1D* h_MR_no0Lep_Q_nj6;
TH1D* h_R2_no0Lep_Q_nj6;
TH1D* h_MET_no0Lep_Q_nj6;
TH1D* h_nLep_no0Lep_Q_nj6;

TH1D* h_ht_AK4_nonb_Q_nj6;
TH1D* h_MR_nonb_Q_nj6;
TH1D* h_R2_nonb_Q_nj6;
TH1D* h_MET_nonb_Q_nj6;
TH1D* h_nb_nonb_Q_nj6;

#if TOP == 0
TH1D* h_ht_AK4_nonW_Q;
TH1D* h_MR_nonW_Q;
TH1D* h_R2_nonW_Q;
TH1D* h_MET_nonW_Q;
TH1D* h_nW_nonW_Q;

TH1D* h_ht_AK4_nonW_Q_nj45;
TH1D* h_MR_nonW_Q_nj45;
TH1D* h_R2_nonW_Q_nj45;
TH1D* h_MET_nonW_Q_nj45;
TH1D* h_nW_nonW_Q_nj45;

TH1D* h_ht_AK4_nonW_Q_nj6;
TH1D* h_MR_nonW_Q_nj6;
TH1D* h_R2_nonW_Q_nj6;
TH1D* h_MET_nonW_Q_nj6;
TH1D* h_nW_nonW_Q_nj6;
#else
TH1D* h_ht_AK4_nonTop_Q;
TH1D* h_MR_nonTop_Q;
TH1D* h_R2_nonTop_Q;
TH1D* h_MET_nonTop_Q;
TH1D* h_nTop_nonTop_Q;

TH1D* h_ht_AK4_nonTop_Q_nj45;
TH1D* h_MR_nonTop_Q_nj45;
TH1D* h_R2_nonTop_Q_nj45;
TH1D* h_MET_nonTop_Q_nj45;
TH1D* h_nTop_nonTop_Q_nj45;

TH1D* h_ht_AK4_nonTop_Q_nj6;
TH1D* h_MR_nonTop_Q_nj6;
TH1D* h_R2_nonTop_Q_nj6;
TH1D* h_MET_nonTop_Q_nj6;
TH1D* h_nTop_nonTop_Q_nj6;
#endif

TH1D* h_ht_AK4_T;
TH1D* h_MR_T;
TH1D* h_R2_T;
TH1D* h_MET_T;
TH1D* h_MET_phi_T;
TH1D* h_MET_phi_T_nj45;
TH1D* h_MET_phi_T_nj6;

#if TOP == 0
TH1D* h_ht_AK4_no1b_T;
TH1D* h_MR_no1b_T;
TH1D* h_R2_no1b_T;
TH1D* h_MET_no1b_T;
TH1D* h_nb_no1b_T;
#endif
TH1D* h_ht_AK4_noMT_T;
TH1D* h_MR_noMT_T;
TH1D* h_R2_noMT_T;
TH1D* h_MET_noMT_T;
TH1D* h_MT_noMT_T;

TH1D* h_ht_AK4_nomDPhi_T;
TH1D* h_MR_nomDPhi_T;
TH1D* h_R2_nomDPhi_T;
TH1D* h_MET_nomDPhi_T;
TH1D* h_mDPhi_nomDPhi_T;

TH1D* h_ht_AK4_no1Lep_T;
TH1D* h_MR_no1Lep_T;
TH1D* h_R2_no1Lep_T;
TH1D* h_MET_no1Lep_T;
TH1D* h_MT_no1Lep_T;
TH1D* h_nLep_no1Lep_T;

TH1D* h_ht_AK4_T_nj45;
TH1D* h_MR_T_nj45;
TH1D* h_R2_T_nj45;
TH1D* h_MET_T_nj45;

#if TOP == 0
TH1D* h_ht_AK4_no1b_T_nj45;
TH1D* h_MR_no1b_T_nj45;
TH1D* h_R2_no1b_T_nj45;
TH1D* h_MET_no1b_T_nj45;
TH1D* h_nb_no1b_T_nj45;
#endif
TH1D* h_ht_AK4_noMT_T_nj45;
TH1D* h_MR_noMT_T_nj45;
TH1D* h_R2_noMT_T_nj45;
TH1D* h_MET_noMT_T_nj45;
TH1D* h_MT_noMT_T_nj45;

TH1D* h_ht_AK4_nomDPhi_T_nj45;
TH1D* h_MR_nomDPhi_T_nj45;
TH1D* h_R2_nomDPhi_T_nj45;
TH1D* h_MET_nomDPhi_T_nj45;
TH1D* h_mDPhi_nomDPhi_T_nj45;

TH1D* h_ht_AK4_no1Lep_T_nj45;
TH1D* h_MR_no1Lep_T_nj45;
TH1D* h_R2_no1Lep_T_nj45;
TH1D* h_MET_no1Lep_T_nj45;
TH1D* h_MT_no1Lep_T_nj45;
TH1D* h_nLep_no1Lep_T_nj45;

TH1D* h_ht_AK4_T_nj6;
TH1D* h_MR_T_nj6;
TH1D* h_R2_T_nj6;
TH1D* h_MET_T_nj6;

#if TOP == 0
TH1D* h_ht_AK4_nonW_T;
TH1D* h_MR_nonW_T;
TH1D* h_R2_nonW_T;
TH1D* h_MET_nonW_T;
TH1D* h_nW_nonW_T;

TH1D* h_ht_AK4_nonW_T_nj45;
TH1D* h_MR_nonW_T_nj45;
TH1D* h_R2_nonW_T_nj45;
TH1D* h_MET_nonW_T_nj45;
TH1D* h_nW_nonW_T_nj45;

TH1D* h_ht_AK4_nonW_T_nj6;
TH1D* h_MR_nonW_T_nj6;
TH1D* h_R2_nonW_T_nj6;
TH1D* h_MET_nonW_T_nj6;
TH1D* h_nW_nonW_T_nj6;
#else
TH1D* h_ht_AK4_nonTop_T;
TH1D* h_MR_nonTop_T;
TH1D* h_R2_nonTop_T;
TH1D* h_MET_nonTop_T;
TH1D* h_nTop_nonTop_T;

TH1D* h_ht_AK4_nonTop_T_nj45;
TH1D* h_MR_nonTop_T_nj45;
TH1D* h_R2_nonTop_T_nj45;
TH1D* h_MET_nonTop_T_nj45;
TH1D* h_nTop_nonTop_T_nj45;

TH1D* h_ht_AK4_nonTop_T_nj6;
TH1D* h_MR_nonTop_T_nj6;
TH1D* h_R2_nonTop_T_nj6;
TH1D* h_MET_nonTop_T_nj6;
TH1D* h_nTop_nonTop_T_nj6;
#endif

#if TOP == 0
TH1D* h_ht_AK4_no1b_T_nj6;
TH1D* h_MR_no1b_T_nj6;
TH1D* h_R2_no1b_T_nj6;
TH1D* h_MET_no1b_T_nj6;
TH1D* h_nb_no1b_T_nj6;
#endif
TH1D* h_ht_AK4_noMT_T_nj6;
TH1D* h_MR_noMT_T_nj6;
TH1D* h_R2_noMT_T_nj6;
TH1D* h_MET_noMT_T_nj6;
TH1D* h_MT_noMT_T_nj6;

TH1D* h_ht_AK4_nomDPhi_T_nj6;
TH1D* h_MR_nomDPhi_T_nj6;
TH1D* h_R2_nomDPhi_T_nj6;
TH1D* h_MET_nomDPhi_T_nj6;
TH1D* h_mDPhi_nomDPhi_T_nj6;

TH1D* h_ht_AK4_no1Lep_T_nj6;
TH1D* h_MR_no1Lep_T_nj6;
TH1D* h_R2_no1Lep_T_nj6;
TH1D* h_MET_no1Lep_T_nj6;
TH1D* h_MT_no1Lep_T_nj6;
TH1D* h_nLep_no1Lep_T_nj6;

TH1D* h_ht_AK4_W;
TH1D* h_MR_W;
TH1D* h_R2_W;
TH1D* h_MET_W;
TH1D* h_MET_phi_W;
TH1D* h_MET_phi_W_nj45;
TH1D* h_MET_phi_W_nj6;

TH1D* h_ht_AK4_noMT_W;
TH1D* h_MR_noMT_W;
TH1D* h_R2_noMT_W;
TH1D* h_MET_noMT_W;
TH1D* h_MT_noMT_W;

TH1D* h_ht_AK4_nonb_W;
TH1D* h_MR_nonb_W;
TH1D* h_R2_nonb_W;
TH1D* h_MET_nonb_W;
TH1D* h_nb_nonb_W;

TH1D* h_ht_AK4_nomDPhi_W;
TH1D* h_MR_nomDPhi_W;
TH1D* h_R2_nomDPhi_W;
TH1D* h_MET_nomDPhi_W;
TH1D* h_mDPhi_nomDPhi_W;

TH1D* h_ht_AK4_no1Lep_W;
TH1D* h_MR_no1Lep_W;
TH1D* h_R2_no1Lep_W;
TH1D* h_MET_no1Lep_W;
TH1D* h_nLep_no1Lep_W;

#if TOP == 0
TH1D* h_ht_AK4_nonW_W;
TH1D* h_MR_nonW_W;
TH1D* h_R2_nonW_W;
TH1D* h_MET_nonW_W;
TH1D* h_nW_nonW_W;

TH1D* h_ht_AK4_nonW_W_nj45;
TH1D* h_MR_nonW_W_nj45;
TH1D* h_R2_nonW_W_nj45;
TH1D* h_MET_nonW_W_nj45;
TH1D* h_nW_nonW_W_nj45;

TH1D* h_ht_AK4_nonW_W_nj6;
TH1D* h_MR_nonW_W_nj6;
TH1D* h_R2_nonW_W_nj6;
TH1D* h_MET_nonW_W_nj6;
TH1D* h_nW_nonW_W_nj6;
#else
TH1D* h_ht_AK4_nonTop_W;
TH1D* h_MR_nonTop_W;
TH1D* h_R2_nonTop_W;
TH1D* h_MET_nonTop_W;
TH1D* h_nTop_nonTop_W;

TH1D* h_ht_AK4_nonTop_W_nj45;
TH1D* h_MR_nonTop_W_nj45;
TH1D* h_R2_nonTop_W_nj45;
TH1D* h_MET_nonTop_W_nj45;
TH1D* h_nTop_nonTop_W_nj45;

TH1D* h_ht_AK4_nonTop_W_nj6;
TH1D* h_MR_nonTop_W_nj6;
TH1D* h_R2_nonTop_W_nj6;
TH1D* h_MET_nonTop_W_nj6;
TH1D* h_nTop_nonTop_W_nj6;
#endif

TH1D* h_ht_AK4_W_nj45;
TH1D* h_MR_W_nj45;
TH1D* h_R2_W_nj45;
TH1D* h_MET_W_nj45;

TH1D* h_ht_AK4_noMT_W_nj45;
TH1D* h_MR_noMT_W_nj45;
TH1D* h_R2_noMT_W_nj45;
TH1D* h_MET_noMT_W_nj45;
TH1D* h_MT_noMT_W_nj45;

TH1D* h_ht_AK4_nonb_W_nj45;
TH1D* h_MR_nonb_W_nj45;
TH1D* h_R2_nonb_W_nj45;
TH1D* h_MET_nonb_W_nj45;
TH1D* h_nb_nonb_W_nj45;

TH1D* h_ht_AK4_nomDPhi_W_nj45;
TH1D* h_MR_nomDPhi_W_nj45;
TH1D* h_R2_nomDPhi_W_nj45;
TH1D* h_MET_nomDPhi_W_nj45;
TH1D* h_mDPhi_nomDPhi_W_nj45;

TH1D* h_ht_AK4_no1Lep_W_nj45;
TH1D* h_MR_no1Lep_W_nj45;
TH1D* h_R2_no1Lep_W_nj45;
TH1D* h_MET_no1Lep_W_nj45;
TH1D* h_nLep_no1Lep_W_nj45;

TH1D* h_ht_AK4_W_nj6;
TH1D* h_MR_W_nj6;
TH1D* h_R2_W_nj6;
TH1D* h_MET_W_nj6;

TH1D* h_ht_AK4_noMT_W_nj6;
TH1D* h_MR_noMT_W_nj6;
TH1D* h_R2_noMT_W_nj6;
TH1D* h_MET_noMT_W_nj6;
TH1D* h_MT_noMT_W_nj6;

TH1D* h_ht_AK4_nonb_W_nj6;
TH1D* h_MR_nonb_W_nj6;
TH1D* h_R2_nonb_W_nj6;
TH1D* h_MET_nonb_W_nj6;
TH1D* h_nb_nonb_W_nj6;

TH1D* h_ht_AK4_nomDPhi_W_nj6;
TH1D* h_MR_nomDPhi_W_nj6;
TH1D* h_R2_nomDPhi_W_nj6;
TH1D* h_MET_nomDPhi_W_nj6;
TH1D* h_mDPhi_nomDPhi_W_nj6;

TH1D* h_ht_AK4_no1Lep_W_nj6;
TH1D* h_MR_no1Lep_W_nj6;
TH1D* h_R2_no1Lep_W_nj6;
TH1D* h_MET_no1Lep_W_nj6;
TH1D* h_nLep_no1Lep_W_nj6;

TH1D* h_ht_AK4_q;
TH1D* h_MR_q;
TH1D* h_R2_q;
TH1D* h_MET_q;
TH1D* h_MET_phi_q;
TH1D* h_MET_phi_q_nj45;
TH1D* h_MET_phi_q_nj6;

TH1D* h_ht_AK4_q_nj45;
TH1D* h_MR_q_nj45;
TH1D* h_R2_q_nj45;
TH1D* h_MET_q_nj45;

TH1D* h_ht_AK4_q_nj6;
TH1D* h_MR_q_nj6;
TH1D* h_R2_q_nj6;
TH1D* h_MET_q_nj6;

TH2D* h_R2_MR_P;

TH2D* h_R2_MR_s;
TH2D* h_MR_MET_s;
TH2D* h_R2_MET_s;
TH2D* h_AK8Jet1pT_MET_s;
TH2D* h_R2_MR_q;
TH2D* h_MR_MET_q;
TH2D* h_R2_MET_q;
TH2D* h_AK8Jet1pT_MET_q;
TH2D* h_R2_MR_Q;
TH2D* h_MR_MET_Q;
TH2D* h_R2_MET_Q;
TH2D* h_AK8Jet1pT_MET_Q;
TH2D* h_R2_MR_T;
TH2D* h_MR_MET_T;
TH2D* h_R2_MET_T;
TH2D* h_AK8Jet1pT_MET_T;
TH2D* h_R2_MR_W;
TH2D* h_MR_MET_W;
TH2D* h_R2_MET_W;
TH2D* h_AK8Jet1pT_MET_W;
TH2D* h_R2_MR_L;
TH2D* h_MR_MET_L;
TH2D* h_R2_MET_L;
TH2D* h_AK8Jet1pT_MET_L;
TH2D* h_R2_MR_Z;
TH2D* h_MR_MET_Z;
TH2D* h_R2_MET_Z;
TH2D* h_AK8Jet1pT_MET_Z;
TH2D* h_R2_MR_G;
TH2D* h_MR_MET_G;
TH2D* h_R2_MET_G;
TH2D* h_AK8Jet1pT_MET_G;

TH2D* h_R2_MR_s_nj45;
TH2D* h_R2_MR_s_nj6;
TH2D* h_R2_MR_q_nj45;
TH2D* h_R2_MR_q_nj6;
TH2D* h_R2_MR_Q_nj45;
TH2D* h_R2_MR_Q_nj6;
TH2D* h_R2_MR_T_nj45;
TH2D* h_R2_MR_T_nj6;
TH2D* h_R2_MR_W_nj45;
TH2D* h_R2_MR_W_nj6;
TH2D* h_R2_MR_Z_nj45;
TH2D* h_R2_MR_Z_nj6;
TH2D* h_R2_MR_L_nj45;
TH2D* h_R2_MR_L_nj6;
TH2D* h_R2_MR_G_nj45;
TH2D* h_R2_MR_G_nj6;

#if TOP == 0
TH2D* h_R2_MR_looseS;
TH2D* h_R2_MR_looseS_nj45;
TH2D* h_R2_MR_looseS_nj6;
TH2D* h_R2_MR_looses;
TH2D* h_R2_MR_looses_nj45;
TH2D* h_R2_MR_looses_nj6;
TH2D* h_R2_MR_looseq;
TH2D* h_R2_MR_looseq_nj45;
TH2D* h_R2_MR_looseq_nj6;
#else
TH2D* h_R2_MR_loose1S;
TH2D* h_R2_MR_loose2S;
TH2D* h_R2_MR_loose3S;
TH2D* h_R2_MR_loose1s;
TH2D* h_R2_MR_loose2s;
TH2D* h_R2_MR_loose3s;
TH2D* h_R2_MR_loose3q;
#endif

TH1D* h_jet1_pt_news;
TH1D* h_jet1_eta_news;
TH1D* h_jet1_phi_news;
TH1D* h_jets_pt_news;
TH1D* h_jets_eta_news;
TH1D* h_jets_phi_news;
TH1D* h_AK8jet1_pt_news;
TH1D* h_AK8jet1_eta_news;
TH1D* h_AK8jet1_phi_news;
TH1D* h_AK8jet1_tau21_news;
TH1D* h_AK8jet1_tau32_news;
TH1D* h_AK8jets_pt_news;
TH1D* h_AK8jets_eta_news;
TH1D* h_AK8jets_phi_news;
TH1D* h_AK8jets_msoftdrop_news;
TH1D* h_AK8jets_tau21_news;
TH1D* h_AK8jets_tau32_news;
TH1D* h_jet1_pt_news_nj45;
TH1D* h_jet1_eta_news_nj45;
TH1D* h_jet1_phi_news_nj45;
TH1D* h_jets_pt_news_nj45;
TH1D* h_jets_eta_news_nj45;
TH1D* h_jets_phi_news_nj45;
TH1D* h_AK8jet1_pt_news_nj45;
TH1D* h_AK8jet1_eta_news_nj45;
TH1D* h_AK8jet1_phi_news_nj45;
TH1D* h_AK8jet1_tau21_news_nj45;
TH1D* h_AK8jet1_tau32_news_nj45;
TH1D* h_AK8jets_pt_news_nj45;
TH1D* h_AK8jets_eta_news_nj45;
TH1D* h_AK8jets_phi_news_nj45;
TH1D* h_AK8jets_msoftdrop_news_nj45;
TH1D* h_AK8jets_tau21_news_nj45;
TH1D* h_AK8jets_tau32_news_nj45;
TH1D* h_jet1_pt_news_nj6;
TH1D* h_jet1_eta_news_nj6;
TH1D* h_jet1_phi_news_nj6;
TH1D* h_jets_pt_news_nj6;
TH1D* h_jets_eta_news_nj6;
TH1D* h_jets_phi_news_nj6;
TH1D* h_AK8jet1_pt_news_nj6;
TH1D* h_AK8jet1_eta_news_nj6;
TH1D* h_AK8jet1_phi_news_nj6;
TH1D* h_AK8jet1_tau21_news_nj6;
TH1D* h_AK8jet1_tau32_news_nj6;
TH1D* h_AK8jets_pt_news_nj6;
TH1D* h_AK8jets_eta_news_nj6;
TH1D* h_AK8jets_phi_news_nj6;
TH1D* h_AK8jets_msoftdrop_news_nj6;
TH1D* h_AK8jets_tau21_news_nj6;
TH1D* h_AK8jets_tau32_news_nj6;
TH1D* h_Megajets_pt_news;
TH1D* h_Megajets_eta_news;
TH1D* h_Megajets_phi_news;
TH1D* h_njet_news;
TH1D* h_nAK8jet_news;
TH1D* h_ht_AK4_news;
TH1D* h_MR_news;
TH1D* h_R2_news;
TH1D* h_MET_news;
TH1D* h_MET_phi_news;
TH1D* h_MET_phi_news_nj45;
TH1D* h_MET_phi_news_nj6;
TH1D* h_ht_AK4_news_nj45;
TH1D* h_MR_news_nj45;
TH1D* h_R2_news_nj45;
TH1D* h_MET_news_nj45;
TH1D* h_ht_AK4_news_nj6;
TH1D* h_MR_news_nj6;
TH1D* h_R2_news_nj6;
TH1D* h_MET_news_nj6;
TH2D* h_R2_MR_news;
TH2D* h_MR_MET_news;
TH2D* h_R2_MET_news;
TH2D* h_AK8Jet1pT_MET_news;
TH2D* h_R2_MR_news_nj45;
TH2D* h_R2_MR_news_nj6;
TH1D* h_nWjet_news;
TH1D* h_nTopjet_news;
TH1D* h_nWjet_news_nj45;
TH1D* h_nTopjet_news_nj45;
TH1D* h_nWjet_news_nj6;
TH1D* h_nTopjet_news_nj6;

TH1D* h_jet1_pt_newq;
TH1D* h_jet1_eta_newq;
TH1D* h_jet1_phi_newq;
TH1D* h_jets_pt_newq;
TH1D* h_jets_eta_newq;
TH1D* h_jets_phi_newq;
TH1D* h_AK8jet1_pt_newq;
TH1D* h_AK8jet1_eta_newq;
TH1D* h_AK8jet1_phi_newq;
TH1D* h_AK8jet1_tau21_newq;
TH1D* h_AK8jet1_tau32_newq;
TH1D* h_AK8jets_pt_newq;
TH1D* h_AK8jets_eta_newq;
TH1D* h_AK8jets_phi_newq;
TH1D* h_AK8jets_msoftdrop_newq;
TH1D* h_AK8jets_tau21_newq;
TH1D* h_AK8jets_tau32_newq;
TH1D* h_jet1_pt_newq_nj45;
TH1D* h_jet1_eta_newq_nj45;
TH1D* h_jet1_phi_newq_nj45;
TH1D* h_jets_pt_newq_nj45;
TH1D* h_jets_eta_newq_nj45;
TH1D* h_jets_phi_newq_nj45;
TH1D* h_AK8jet1_pt_newq_nj45;
TH1D* h_AK8jet1_eta_newq_nj45;
TH1D* h_AK8jet1_phi_newq_nj45;
TH1D* h_AK8jet1_tau21_newq_nj45;
TH1D* h_AK8jet1_tau32_newq_nj45;
TH1D* h_AK8jets_pt_newq_nj45;
TH1D* h_AK8jets_eta_newq_nj45;
TH1D* h_AK8jets_phi_newq_nj45;
TH1D* h_AK8jets_msoftdrop_newq_nj45;
TH1D* h_AK8jets_tau21_newq_nj45;
TH1D* h_AK8jets_tau32_newq_nj45;
TH1D* h_jet1_pt_newq_nj6;
TH1D* h_jet1_eta_newq_nj6;
TH1D* h_jet1_phi_newq_nj6;
TH1D* h_jets_pt_newq_nj6;
TH1D* h_jets_eta_newq_nj6;
TH1D* h_jets_phi_newq_nj6;
TH1D* h_AK8jet1_pt_newq_nj6;
TH1D* h_AK8jet1_eta_newq_nj6;
TH1D* h_AK8jet1_phi_newq_nj6;
TH1D* h_AK8jet1_tau21_newq_nj6;
TH1D* h_AK8jet1_tau32_newq_nj6;
TH1D* h_AK8jets_pt_newq_nj6;
TH1D* h_AK8jets_eta_newq_nj6;
TH1D* h_AK8jets_phi_newq_nj6;
TH1D* h_AK8jets_msoftdrop_newq_nj6;
TH1D* h_AK8jets_tau21_newq_nj6;
TH1D* h_AK8jets_tau32_newq_nj6;
TH1D* h_Megajets_pt_newq;
TH1D* h_Megajets_eta_newq;
TH1D* h_Megajets_phi_newq;
TH1D* h_njet_newq;
TH1D* h_nAK8jet_newq;
TH1D* h_ht_AK4_newq;
TH1D* h_MR_newq;
TH1D* h_R2_newq;
TH1D* h_MET_newq;
TH1D* h_MET_phi_newq;
TH1D* h_MET_phi_newq_nj45;
TH1D* h_MET_phi_newq_nj6;
TH1D* h_ht_AK4_newq_nj45;
TH1D* h_MR_newq_nj45;
TH1D* h_R2_newq_nj45;
TH1D* h_MET_newq_nj45;
TH1D* h_ht_AK4_newq_nj6;
TH1D* h_MR_newq_nj6;
TH1D* h_R2_newq_nj6;
TH1D* h_MET_newq_nj6;
TH2D* h_R2_MR_newq;
TH2D* h_MR_MET_newq;
TH2D* h_R2_MET_newq;
TH2D* h_AK8Jet1pT_MET_newq;
TH2D* h_R2_MR_newq_nj45;
TH2D* h_R2_MR_newq_nj6;
TH1D* h_nWjet_newq;
TH1D* h_nTopjet_newq;
TH1D* h_nWjet_newq_nj45;
TH1D* h_nTopjet_newq_nj45;
TH1D* h_nWjet_newq_nj6;
TH1D* h_nTopjet_newq_nj6;


TH1D *h_HT_TrigNoMass_0;
TH1D *h_HT_TrigNoMass_1;

TH1D *h_AK8HT_TrigNoMass_0;
TH1D *h_AK8HT_TrigNoMass_1;

TH1D *h_AK8JetpT_TrigNoMass_0;
TH1D *h_AK8JetpT_TrigNoMass_1;

TH1D *h_AK8JetMass_TrigNoMass_0;
TH1D *h_AK8JetMass_TrigNoMass_1;

TH1D *h_MET_TrigNoMass_0;
TH1D *h_MET_TrigNoMass_1;

TH1D *h_MR_TrigNoMass_0;
TH1D *h_MR_TrigNoMass_1;

TH1D *h_R2_TrigNoMass_0;
TH1D *h_R2_TrigNoMass_1;

TH2D *h_R2_MR_TrigNoMass_0;
TH2D *h_R2_MR_TrigNoMass_1;

TH2D *h_MET_AK8JetMass_TrigNoMass_0;
TH2D *h_MET_AK8JetMass_TrigNoMass_1;

TH2D *h_HT_MET_TrigNoMass_0;
TH2D *h_HT_MET_TrigNoMass_1;

TH2D *h_HT_AK8JetMass_TrigNoMass_0;
TH2D *h_HT_AK8JetMass_TrigNoMass_1;

TH2D *h_AK8HT_MET_TrigNoMass_0;
TH2D *h_AK8HT_MET_TrigNoMass_1;

TH2D *h_AK8HT_AK8JetMass_TrigNoMass_0;
TH2D *h_AK8HT_AK8JetMass_TrigNoMass_1;

TH3D *h_HT_MET_AK8JetMass_TrigNoMass_0;
TH3D *h_HT_MET_AK8JetMass_TrigNoMass_1;

TH3D *h_AK8HT_MET_AK8JetMass_TrigNoMass_0;
TH3D *h_AK8HT_MET_AK8JetMass_TrigNoMass_1;

TH1D *h_HT_TrigMass_0;
TH1D *h_HT_TrigMass_1;

TH1D *h_AK8HT_TrigMass_0;
TH1D *h_AK8HT_TrigMass_1;

TH1D *h_AK8JetpT_TrigMass_0;
TH1D *h_AK8JetpT_TrigMass_1;

TH1D *h_AK8JetMass_TrigMass_0;
TH1D *h_AK8JetMass_TrigMass_1;

TH1D *h_MET_TrigMass_0;
TH1D *h_MET_TrigMass_1;

TH1D *h_MR_TrigMass_0;
TH1D *h_MR_TrigMass_1;

TH1D *h_R2_TrigMass_0;
TH1D *h_R2_TrigMass_1;

TH2D *h_R2_MR_TrigMass_0;
TH2D *h_R2_MR_TrigMass_1;

TH2D *h_MET_AK8JetMass_TrigMass_0;
TH2D *h_MET_AK8JetMass_TrigMass_1;

TH2D *h_HT_MET_TrigMass_0;
TH2D *h_HT_MET_TrigMass_1;

TH2D *h_HT_AK8JetMass_TrigMass_0;
TH2D *h_HT_AK8JetMass_TrigMass_1;

TH2D *h_AK8HT_MET_TrigMass_0;
TH2D *h_AK8HT_MET_TrigMass_1;

TH2D *h_AK8HT_AK8JetMass_TrigMass_0;
TH2D *h_AK8HT_AK8JetMass_TrigMass_1;

TH3D *h_HT_MET_AK8JetMass_TrigMass_0;
TH3D *h_HT_MET_AK8JetMass_TrigMass_1;

TH3D *h_AK8HT_MET_AK8JetMass_TrigMass_0;
TH3D *h_AK8HT_MET_AK8JetMass_TrigMass_1;

TH2D* h_AK8Jet1Pt_Eta_W_fakerate;
TH2D* h_AK8Jet1Pt_Eta_no_W_fakerate;
TH2D* h_AK8Jet1Pt_Eta_mW_fakerate;
TH2D* h_AK8Jet1Pt_Eta_no_mW_fakerate;
TH2D* h_AK8Jet1Pt_Eta_m0bW_fakerate;
TH2D* h_AK8Jet1Pt_Eta_no_m0bW_fakerate;
TH2D* h_AK8Jet1Pt_Eta_aW_fakerate;
TH2D* h_AK8Jet1Pt_Eta_no_aW_fakerate;

TH2D* h_AK8Jet1Pt_Eta_Top_fakerate;
TH2D* h_AK8Jet1Pt_Eta_no_Top_fakerate;
TH2D* h_AK8Jet1Pt_Eta_mTop_fakerate;
TH2D* h_AK8Jet1Pt_Eta_no_mTop_fakerate;
TH2D* h_AK8Jet1Pt_Eta_m0bTop_fakerate;
TH2D* h_AK8Jet1Pt_Eta_no_m0bTop_fakerate;
TH2D* h_AK8Jet1Pt_Eta_aTop_fakerate;
TH2D* h_AK8Jet1Pt_Eta_no_aTop_fakerate;

TH1D* h_AK8Jet1Pt_Z_fakerate;
TH1D* h_AK8Jet1Pt_no_Z_fakerate;
TH2D* h_AK8Jet1Pt_Eta_Z_fakerate;
TH2D* h_AK8Jet1Pt_Eta_no_Z_fakerate;
TH1D* h_AK8Jet1Pt_WtagZ_fakerate;
TH1D* h_AK8Jet1Pt_no_WtagZ_fakerate;
TH2D* h_AK8Jet1Pt_Eta_WtagZ_fakerate;
TH2D* h_AK8Jet1Pt_Eta_no_WtagZ_fakerate;

TH2D* h_AK8Jet1Pt_eta_GenW_no_W;
TH2D* h_AK8Jet1Pt_eta_GenTop_no_Top;
TH2D* h_AK8Jet1Pt_eta_GenW_W;
TH2D* h_AK8Jet1Pt_eta_GenTop_Top;
TH2D* h_AK8Jet1Pt_eta_FakeW_W;
TH2D* h_AK8Jet1Pt_eta_FakeTop_Top;

std::vector<TH2D*> vh_R2_MR_s_nj45;
std::vector<TH2D*> vh_R2_MR_s_nj6;
std::vector<TH2D*> vh_R2_MR_q_nj45;
std::vector<TH2D*> vh_R2_MR_q_nj6;
std::vector<TH2D*> vh_R2_MR_S_nj45;
std::vector<TH2D*> vh_R2_MR_S_nj6;
std::vector<TH2D*> vh_R2_MR_Q_nj45;
std::vector<TH2D*> vh_R2_MR_Q_nj6;
std::vector<TH2D*> vh_R2_MR_T_nj45;
std::vector<TH2D*> vh_R2_MR_T_nj6;
std::vector<TH2D*> vh_R2_MR_W_nj45;
std::vector<TH2D*> vh_R2_MR_W_nj6;
std::vector<TH2D*> vh_R2_MR_Z_nj45;
std::vector<TH2D*> vh_R2_MR_Z_nj6;
std::vector<TH2D*> vh_R2_MR_L_nj45;
std::vector<TH2D*> vh_R2_MR_L_nj6;
std::vector<TH2D*> vh_R2_MR_G_nj45;
std::vector<TH2D*> vh_R2_MR_G_nj6;

// Histos for the Z(nunu) estimate
TH2D* h_R2_MR_G_EB; // For counts in data
TH2D* h_R2_MR_G_EE;
TH2D* h_R2_MR_G_EB_nj45;
TH2D* h_R2_MR_G_EB_nj6;
TH2D* h_R2_MR_G_EE_nj45;
TH2D* h_R2_MR_G_EE_nj6;

TH2D* h_ChIsoTemplate_Fake_g_MR_EB;
TH2D* h_ChIsoTemplate_Fake_g_R2_EB;
TH2D* h_ChIsoTemplate_Fake_g_MR_EE;
TH2D* h_ChIsoTemplate_Fake_g_R2_EE;
TH2D* h_ChIsoTemplate_Prompt_g_MR_EB;
TH2D* h_ChIsoTemplate_Prompt_g_R2_EB;
TH2D* h_ChIsoTemplate_Prompt_g_MR_EE;
TH2D* h_ChIsoTemplate_Prompt_g_R2_EE;
TH2D* h_ChIsoTemplate_Fake_g_MR_EB_MC;
TH2D* h_ChIsoTemplate_Fake_g_R2_EB_MC;
TH2D* h_ChIsoTemplate_Fake_g_MR_EE_MC;
TH2D* h_ChIsoTemplate_Fake_g_R2_EE_MC;
TH2D* h_MR_ChIso_GNoIso_EB;
TH2D* h_R2_ChIso_GNoIso_EB;
TH2D* h_MR_ChIso_GNoIso_EE;
TH2D* h_R2_ChIso_GNoIso_EE;
TH2D* h_MR_ChIso_GNoIso_EB_nj45;
TH2D* h_R2_ChIso_GNoIso_EB_nj45;
TH2D* h_MR_ChIso_GNoIso_EE_nj45;
TH2D* h_R2_ChIso_GNoIso_EE_nj45;
TH2D* h_MR_ChIso_GNoIso_EB_nj6;
TH2D* h_R2_ChIso_GNoIso_EB_nj6;
TH2D* h_MR_ChIso_GNoIso_EE_nj6;
TH2D* h_R2_ChIso_GNoIso_EE_nj6;
TH2D* h_MR_ChIso_gNoIso_EB;
TH2D* h_R2_ChIso_gNoIso_EB;
TH2D* h_MR_ChIso_gNoIso_EE;
TH2D* h_R2_ChIso_gNoIso_EE;
TH2D* h_MR_ChIso_gNoIso_EB_nj45;
TH2D* h_R2_ChIso_gNoIso_EB_nj45;
TH2D* h_MR_ChIso_gNoIso_EE_nj45;
TH2D* h_R2_ChIso_gNoIso_EE_nj45;
TH2D* h_MR_ChIso_gNoIso_EB_nj6;
TH2D* h_R2_ChIso_gNoIso_EB_nj6;
TH2D* h_MR_ChIso_gNoIso_EE_nj6;
TH2D* h_R2_ChIso_gNoIso_EE_nj6;

TH2D* h_MR_IsDirect_G_EB;
TH2D* h_R2_IsDirect_G_EB;
TH2D* h_MR_IsDirect_G_EE;
TH2D* h_R2_IsDirect_G_EE;

TH3D* h_ChIsoTemplate_Fake_g_EB; // Fake photon templates (data)
TH3D* h_ChIsoTemplate_Fake_g_EE;
TH3D* h_ChIsoTemplate_Fake_g_EB_MC; // Fake photon templates (mc)
TH3D* h_ChIsoTemplate_Fake_g_EE_MC;
TH3D* h_ChIsoTemplate_Prompt_g_EB; // Prompt photon template (GJets)
TH3D* h_ChIsoTemplate_Prompt_g_EE;
TH3D* h_R2_MR_ChIso_GNoIso_EB; // For purity in data
TH3D* h_R2_MR_ChIso_GNoIso_EE;
TH3D* h_R2_MR_ChIso_GNoIso_EB_nj45;
TH3D* h_R2_MR_ChIso_GNoIso_EB_nj6;
TH3D* h_R2_MR_ChIso_GNoIso_EE_nj45;
TH3D* h_R2_MR_ChIso_GNoIso_EE_nj6;
TH3D* h_R2_MR_ChIso_gNoIso_EB; // For purity in data (G-1)
TH3D* h_R2_MR_ChIso_gNoIso_EE;
TH3D* h_R2_MR_ChIso_gNoIso_EB_nj45;
TH3D* h_R2_MR_ChIso_gNoIso_EB_nj6;
TH3D* h_R2_MR_ChIso_gNoIso_EE_nj45;
TH3D* h_R2_MR_ChIso_gNoIso_EE_nj6;
TH3D* h_R2_MR_IsPrompt_G_EB; // MC truth for photon purity
TH3D* h_R2_MR_IsPrompt_G_EE;
TH3D* h_R2_MR_IsDirect_G_EB; // MC truth for direct fraction
TH3D* h_R2_MR_IsDirect_G_EE;
TH2D* h_R2_MR_G_DirectPrompt;
TH2D* h_R2_MR_G_DirectPrompt_nj45;
TH2D* h_R2_MR_G_DirectPrompt_nj6;

//std::vector<TH1D*> vh_jet1_pt;

//_______________________________________________________
//              Define Histograms here
	void
Analysis::init_analysis_histos(const unsigned int& syst_nSyst, const unsigned int& syst_index)
{

	//double htbn = 20;
	//double htmn = 0;
	// double htmx = 1500;

	//double j1ptbn = 20;
	//double j1ptmn = 0;
	//double j1ptmx = 1000;

	//double MRbn = 7;
	//double MRmn = 0;
	//double MRmx = 4000;
	//double Rbn = 7;
	//double Rmn = 0;
	//double Rmx = 1;

	// Variable binning
	//for test
	int nbn_HT = 20;
	int nbn_MET = 16;

	//int nbnHT = 11;
	int nbnHT = 6;
	int nbnMET = 4;
	int nbnj1pt = 7;
	int nbn3DHT = 7;
	int nbn3DMET = 6;
	int nbnjmass = 5;
	//int nbn_j1pt = 12;
	//int nbn_AK8j1pt = 13;
	int nbn_AK8J1pt = 7;
	int nbn_MR = 5;
	int nbn_R2 = 5;
	int nbn_eta = 2;
	//Double_t  HT_bins[20]  = {0, 200, 300, 400, 500, 600, 650, 700, 750, 800, 900, 1000, 1200, 1500, 2000, 4000, 10000};
	//Double_t bn_HTtmp[] = {400.,500.,600.,700.,750.,800.,850.,900.,950.,1000.,1500.,100000.};
	Double_t bn_HTtmp[] = {300.,500,550.,600.,800.,1500.,10000.};
	Double_t* bnHT = 0;
	bnHT = getVariableBinEdges(nbnHT+1,bn_HTtmp);

	Double_t bn_METtmp[] = {50.,150.,200.,400.,10000.};
	Double_t* bnMET = 0;
	bnMET = getVariableBinEdges(nbnMET+1,bn_METtmp);

	Double_t bn_3DHTtmp[] = {200.,400.,500.,550,600.,800.,1500.,10000.};
	Double_t* bn3DHT = 0;
	bn3DHT = getVariableBinEdges(nbn3DHT+1,bn_3DHTtmp);

	Double_t bn_3DMETtmp[] = {0.,70.,110.,150.,200.,400.,10000.};
	Double_t* bn3DMET = 0;
	bn3DMET = getVariableBinEdges(nbn3DMET+1,bn_3DMETtmp);

	Double_t bn_jmasstmp[] = {0.,65.,105.,150.,210.,500.};
	Double_t* bnjmass = 0;
	bnjmass = getVariableBinEdges(nbnjmass+1,bn_jmasstmp);

	Double_t bn_j1pttmp[] = {200.,300.,400.,450.,500.,550.,600.,1000.};
	Double_t* bnj1pt = 0;
	bnj1pt = getVariableBinEdges(nbnj1pt+1,bn_j1pttmp);

	Double_t bn_MET_tmp[] = {0.,50.,100.,150.,200.,250.,300.,350.,400.,450.,500.,600.,700.,800.,1000.,2000.,10000.};
	Double_t* bn_MET = 0;
	bn_MET = getVariableBinEdges(nbn_MET+1,bn_MET_tmp);

	Double_t bn_HT_tmp[] = {0.,200.,400.,450.,500.,550.,600.,650.,700.,750.,800.,900.,1000.,1200.,1400.,1600.,1800.,2000.,2500.,3000.,10000.};
	Double_t* bn_HT = 0;
	bn_HT = getVariableBinEdges(nbn_HT+1,bn_HT_tmp);

	//Double_t bn_j1pt_tmp[] = {0.,50.,100.,150.,200.,250.,300.,350.,400.,450.,500.,700.,1000.};
	//Double_t* bn_j1pt = 0;
	// bn_j1pt = getVariableBinEdges(nbn_j1pt+1,bn_j1pt_tmp);
	//Double_t bn_AK8j1pt_tmp[] = {0.,200.,220.,240,260,280,300.,320.,340,360,380,400.,500.,1000.};
	//Double_t* bn_AK8j1pt = 0;
	//bn_AK8j1pt = getVariableBinEdges(nbn_AK8j1pt+1,bn_AK8j1pt_tmp);
	//Double_t bn_AK8J1pt_tmp[] = {200.,250,350.,1000.};
	Double_t bn_AK8J1pt_tmp[] = {0.,200.,300.,400.,500.,600.,800.,2000.};
	//Double_t bn_AK8J1pt_tmp[] = {0.,200.,220.,240,260,280,300.,350,400.,450,500.,700,1000.,1500.,2000.};
	//Double_t bn_AK8J1pt_tmp[] = {0.,200.,220.,240,260,280,300.,320.,340,360,380.,400.,450,500.,700,1000.,1500.,2000.};
	Double_t* bn_AK8J1pt = 0;
	bn_AK8J1pt = getVariableBinEdges(nbn_AK8J1pt+1,bn_AK8J1pt_tmp);
	Double_t bn_MR_tmp[] = {800.,1000.,1200.,1600.,2000.,4000.};
	Double_t* bn_MR = 0;
	bn_MR = getVariableBinEdges(nbn_MR+1,bn_MR_tmp);
	Double_t bn_R2_tmp[] = {0.08,0.12,0.16,0.24,0.4,1.5};
	Double_t* bn_R2 = 0;
	bn_R2 = getVariableBinEdges(nbn_R2+1,bn_R2_tmp);
	Double_t bn_eta_tmp[] = {0.,1.5,2.5};
	Double_t* bn_eta = 0;
	bn_eta = getVariableBinEdges(nbn_eta+1,bn_eta_tmp);
	/*
		 std::vector<double> MR  = {0, 600, 800, 1000, 1200, 1600, 2000, 4000, 10000};
		 std::vector<double> R2  = {0, 0.04, 0.08, 0.12, 0.16, 0.24, 0.4, 2.0, 5.0};
	// Unrolled bin labels
	std::map<int, std::string> Razor_labels; int bin = 1; size_t n, m;
	for (size_t i=2, n=MR.size(); i<n-2; ++i) for (size_t j=2, m=R2.size(); j<m-2; ++j) {
	std::stringstream ss;
	ss.precision(2);
	if (bin<=18) {
	ss<<fixed<<"["<<R2[j]<<", "<<R2[j+1]<<"]";
	Razor_labels[bin] = ss.str();                                                                                                                                           
	} else if (bin==19) {
	ss<<fixed<<"["<<R2[j]<<", "<<R2[j+2]<<"]";
	Razor_labels[bin] = ss.str();
	} else if (bin>=21&&bin<=22) {
	ss<<fixed<<"["<<R2[j]<<", "<<R2[j+1]<<"]";
	Razor_labels[bin-1] = ss.str();
	} else if (bin==23) {
	ss<<fixed<<"["<<R2[j]<<", "<<R2[j+3]<<"]";
	Razor_labels[bin-1] = ss.str();
	}    
	bin++;
	}

	size_t bin = -1;
	for (size_t i=2, n=MR.size(); i<n-2; ++i) if (MR>=MR[i]&&MR<MR[i+1])
	for (size_t j=2, m=R2.size(); j<m-2; ++j) if (R2>=R2[j]&&R2<R2[j+1])
	bin = (i-2)*(m-4)+j-2;
	if (bin>=19&&bin<=22) bin--;
	if (bin>=23&&bin<=24) bin=21;
	*/

  h_deepTagMD_WvsQCD_s = new TH1D("deepTagMD_WvsQCD_s", ";deepTagMD_{WvsQCD}", 20, 0, 1);
  h_deepTagMD_WvsQCD_Q = new TH1D("deepTagMD_WvsQCD_Q", ";deepTagMD_{WvsQCD}", 20, 0, 1);
  h_deepTagMD_WvsQCD_q = new TH1D("deepTagMD_WvsQCD_q", ";deepTagMD_{WvsQCD}", 20, 0, 1);
  h_deepTagMD_WvsQCD_T = new TH1D("deepTagMD_WvsQCD_T", ";deepTagMD_{WvsQCD}", 20, 0, 1);
  h_deepTagMD_WvsQCD_W = new TH1D("deepTagMD_WvsQCD_W", ";deepTagMD_{WvsQCD}", 20, 0, 1);
  h_deepTagMD_WvsQCD_Z = new TH1D("deepTagMD_WvsQCD_Z", ";deepTagMD_{WvsQCD}", 20, 0, 1);
  h_deepTagMD_WvsQCD_G = new TH1D("deepTagMD_WvsQCD_G", ";deepTagMD_{WvsQCD}", 20, 0, 1);
  h_deepTagMD_WvsQCD_L = new TH1D("deepTagMD_WvsQCD_L", ";deepTagMD_{WvsQCD}", 20, 0, 1);
  h_deepTagMD_TvsQCD_s = new TH1D("deepTagMD_TvsQCD_s", ";deepTagMD_{TvsQCD}", 20, 0, 1);
  h_deepTagMD_TvsQCD_Q = new TH1D("deepTagMD_TvsQCD_Q", ";deepTagMD_{TvsQCD}", 20, 0, 1);
  h_deepTagMD_TvsQCD_q = new TH1D("deepTagMD_TvsQCD_q", ";deepTagMD_{TvsQCD}", 20, 0, 1);
  h_deepTagMD_TvsQCD_T = new TH1D("deepTagMD_TvsQCD_T", ";deepTagMD_{TvsQCD}", 20, 0, 1);
  h_deepTagMD_TvsQCD_W = new TH1D("deepTagMD_TvsQCD_W", ";deepTagMD_{TvsQCD}", 20, 0, 1);
  h_deepTagMD_TvsQCD_Z = new TH1D("deepTagMD_TvsQCD_Z", ";deepTagMD_{TvsQCD}", 20, 0, 1);
  h_deepTagMD_TvsQCD_G = new TH1D("deepTagMD_TvsQCD_G", ";deepTagMD_{TvsQCD}", 20, 0, 1);
  h_deepTagMD_TvsQCD_L = new TH1D("deepTagMD_TvsQCD_L", ";deepTagMD_{TvsQCD}", 20, 0, 1);

  h_deepTag_WvsQCD_s = new TH1D("deepTag_WvsQCD_s", ";deepTag_{WvsQCD}", 20, 0, 1);
  h_deepTag_WvsQCD_Q = new TH1D("deepTag_WvsQCD_Q", ";deepTag_{WvsQCD}", 20, 0, 1);
  h_deepTag_WvsQCD_q = new TH1D("deepTag_WvsQCD_q", ";deepTag_{WvsQCD}", 20, 0, 1);
  h_deepTag_WvsQCD_T = new TH1D("deepTag_WvsQCD_T", ";deepTag_{WvsQCD}", 20, 0, 1);
  h_deepTag_WvsQCD_W = new TH1D("deepTag_WvsQCD_W", ";deepTag_{WvsQCD}", 20, 0, 1);
  h_deepTag_WvsQCD_Z = new TH1D("deepTag_WvsQCD_Z", ";deepTag_{WvsQCD}", 20, 0, 1);
  h_deepTag_WvsQCD_G = new TH1D("deepTag_WvsQCD_G", ";deepTag_{WvsQCD}", 20, 0, 1);
  h_deepTag_WvsQCD_L = new TH1D("deepTag_WvsQCD_L", ";deepTag_{WvsQCD}", 20, 0, 1);
  h_deepTag_TvsQCD_s = new TH1D("deepTag_TvsQCD_s", ";deepTag_{TvsQCD}", 20, 0, 1);
  h_deepTag_TvsQCD_Q = new TH1D("deepTag_TvsQCD_Q", ";deepTag_{TvsQCD}", 20, 0, 1);
  h_deepTag_TvsQCD_q = new TH1D("deepTag_TvsQCD_q", ";deepTag_{TvsQCD}", 20, 0, 1);
  h_deepTag_TvsQCD_T = new TH1D("deepTag_TvsQCD_T", ";deepTag_{TvsQCD}", 20, 0, 1);
  h_deepTag_TvsQCD_W = new TH1D("deepTag_TvsQCD_W", ";deepTag_{TvsQCD}", 20, 0, 1);
  h_deepTag_TvsQCD_Z = new TH1D("deepTag_TvsQCD_Z", ";deepTag_{TvsQCD}", 20, 0, 1);
  h_deepTag_TvsQCD_G = new TH1D("deepTag_TvsQCD_G", ";deepTag_{TvsQCD}", 20, 0, 1);
  h_deepTag_TvsQCD_L = new TH1D("deepTag_TvsQCD_L", ";deepTag_{TvsQCD}", 20, 0, 1);

	h_dR_min = new TH1D("dR_min",	";dR_{min}(l, jet)", 40, 0, 2);
	h_rel_pT = new TH1D("rel_pT", ";p_{T, rel}(l, jet)", 40, 0, 100);
	h_rel_pT_dR_min = new TH2D("rel_pT_dR_min", ";dR_{min}(l, jet);p_{T, rel}(l, jet)", 40,0,2,40,0,100);
	h_dR_min_tag = new TH1D("dR_min_tag",	";dR_{min}(l, jet)", 40, 0, 2);
	h_rel_pT_tag = new TH1D("rel_pT_tag", ";p_{T, rel}(l, jet)", 40, 0, 100);
	h_rel_pT_dR_min_tag = new TH2D("rel_pT_dR_min_tag", ";dR_{min}(l, jet);p_{T, rel}(l, jet)", 40,0,2,40,0,100);
	h_dR_min_untag = new TH1D("dR_min_untag",	";dR_{min}(l, jet)", 40, 0, 2);
	h_rel_pT_untag = new TH1D("rel_pT_untag", ";p_{T, rel}(l, jet)", 40, 0, 100);
	h_rel_pT_dR_min_untag = new TH2D("rel_pT_dR_min_untag", ";dR_{min}(l, jet);p_{T, rel}(l, jet)", 40,0,2,40,0,100);

	h_MR_T_1Lep = new TH1D("MR_T_1Lep",   ";MR_{AK4}",     nbn_MR,    bn_MR);
	h_R2_T_1Lep = new TH1D("R2_T_1Lep",   ";R2_{AK4}",         nbn_R2,bn_R2);
	h_R2_MR_T_1Lep = new TH2D("R2_MR_T_1Lep", ";MR_{AK4};R2_{AK4}",nbn_MR,bn_MR,nbn_R2,bn_R2);
	h_MR_W_1Lep = new TH1D("MR_W_1Lep",   ";MR_{AK4}",     nbn_MR,    bn_MR);
	h_R2_W_1Lep = new TH1D("R2_W_1Lep",   ";R2_{AK4}",         nbn_R2,bn_R2);
	h_R2_MR_W_1Lep = new TH2D("R2_MR_W_1Lep", ";MR_{AK4};R2_{AK4}",nbn_MR,bn_MR,nbn_R2,bn_R2);

	h_Megajets_pt_Wjet_S = new TH1D("Megajets_pt_Wjet_S",";p_{T, Megajets}",200,0,2000);
	h_Megajets_eta_Wjet_S = new TH1D("Megajets_eta_Wjet_S",";#eta_{Megajets}",480,-2.4,2.4);
	h_Megajets_phi_Wjet_S = new TH1D("Megajets_phi_Wjet_S",";#phi_{Megajets}",640,-3.2,3.2);
	h_njet_Wjet_S       = new TH1D("njet_Wjet_S",         ";N_{jet}",                20, 0,  20);
	h_nAK8jet_Wjet_S    = new TH1D("nAK8jet_Wjet_S",      ";N_{jet}",                20, 0,  20);
	h_ht_AK4_Wjet_S = new TH1D("ht_AK4_Wjet_S",  ";H_{T}",                  nbn_HT, bn_HT);
	h_MR_Wjet_S = new TH1D("MR_Wjet_S",   ";MR_{AK4}",     nbn_MR,    bn_MR);
	h_R2_Wjet_S = new TH1D("R2_Wjet_S",   ";R2_{AK4}",         nbn_R2,bn_R2);
	h_MET_Wjet_S = new TH1D("MET_Wjet_S", ";MET", 400,0,2000);
	h_MET_phi_Wjet_S = new TH1D("MET_phi_Wjet_S", ";#phi_{MET}", 640, -3.2,3.2);
	h_MET_phi_Wjet_S_nj45 = new TH1D("MET_phi_Wjet_S_nj45", ";#phi_{MET}", 640, -3.2,3.2);
	h_MET_phi_Wjet_S_nj6 = new TH1D("MET_phi_Wjet_S_nj6", ";#phi_{MET}", 640, -3.2,3.2);

	h_ht_AK4_Wjet_S_nj45 = new TH1D("ht_AK4_Wjet_S_nj45",  ";H_{T}",                  nbn_HT, bn_HT);
	h_MR_Wjet_S_nj45 = new TH1D("MR_Wjet_S_nj45",   ";MR_{AK4}",     nbn_MR,    bn_MR);
	h_R2_Wjet_S_nj45 = new TH1D("R2_Wjet_S_nj45",   ";R2_{AK4}",         nbn_R2,bn_R2);
	h_MET_Wjet_S_nj45 = new TH1D("MET_Wjet_S_nj45", ";MET", 400,0,2000);

	h_ht_AK4_Wjet_S_nj6 = new TH1D("ht_AK4_Wjet_S_nj6",  ";H_{T}",                  nbn_HT, bn_HT);
	h_MR_Wjet_S_nj6 = new TH1D("MR_Wjet_S_nj6",   ";MR_{AK4}",     nbn_MR,    bn_MR);
	h_R2_Wjet_S_nj6 = new TH1D("R2_Wjet_S_nj6",   ";R2_{AK4}",         nbn_R2,bn_R2);
	h_MET_Wjet_S_nj6 = new TH1D("MET_Wjet_S_nj6", ";MET", 400,0,2000);

	h_R2_MR_Wjet_S = new TH2D("R2_MR_Wjet_S", ";MR_{AK4};R2_{AK4}",nbn_MR,bn_MR,nbn_R2,bn_R2);
	h_R2_MET_Wjet_S = new TH2D("R2_MET_Wjet_S", ";MET_{AK4};R2_{AK4}",40,0,2000,nbn_R2,bn_R2);
	h_MR_MET_Wjet_S = new TH2D("MR_MET_Wjet_S", ";MET_{AK4};MR_{AK4}",40,0,2000,nbn_MR,bn_MR);
	h_HT_MET_Wjet_S = new TH2D("HT_MET_Wjet_S", ";MET_{AK4};HT_{AK4}",40,0,2000,40,0,2000);
	h_R2_HT_Wjet_S = new TH2D("R2_HT_Wjet_S", ";HT_{AK4};R2_{AK4}",40,0,2000,nbn_R2,bn_R2);
	h_MR_HT_Wjet_S = new TH2D("MR_HT_Wjet_S", ";HT_{AK4};MR_{AK4}",40,0,2000,nbn_MR,bn_MR);
	h_AK8Jet1pT_MET_Wjet_S = new TH2D("AK8Jet1pT_MET_S", ";MET_{AK4};p_{T,AK8Jet1}",40,0,2000,40,0,2000);
	h_R2_MET_Wjet_S_nj45 = new TH2D("R2_MET_Wjet_S_nj45", ";MET_{AK4};R2_{AK4}",40,0,2000,nbn_R2,bn_R2);
	h_MR_MET_Wjet_S_nj45 = new TH2D("MR_MET_Wjet_S_nj45", ";MET_{AK4};MR_{AK4}",40,0,2000,nbn_MR,bn_MR);
	h_HT_MET_Wjet_S_nj45 = new TH2D("HT_MET_S_nj45", ";MET_{AK4};HT_{AK4}",40,0,2000,40,0,2000);
	h_R2_HT_Wjet_S_nj45 = new TH2D("R2_HT_Wjet_S_nj45", ";HT_{AK4};R2_{AK4}",40,0,2000,nbn_R2,bn_R2);
	h_MR_HT_Wjet_S_nj45 = new TH2D("MR_HT_Wjet_S_nj45", ";HT_{AK4};MR_{AK4}",40,0,2000,nbn_MR,bn_MR);
	h_AK8Jet1pT_MET_Wjet_S_nj45 = new TH2D("AK8Jet1pT_MET_Wjet_S_nj45", ";MET_{AK4};p_{T,AK8Jet1}",40,0,2000,40,0,2000);
	h_R2_MET_Wjet_S_nj6 = new TH2D("R2_MET_Wjet_S_nj6", ";MET_{AK4};R2_{AK4}",40,0,2000,nbn_R2,bn_R2);
	h_MR_MET_Wjet_S_nj6 = new TH2D("MR_MET_Wjet_S_nj6", ";MET_{AK4};MR_{AK4}",40,0,2000,nbn_MR,bn_MR);
	h_HT_MET_Wjet_S_nj6 = new TH2D("HT_MET_Wjet_S_nj6", ";MET_{AK4};HT_{AK4}",40,0,2000,40,0,2000);
	h_R2_HT_Wjet_S_nj6 = new TH2D("R2_HT_Wjet_S_nj6", ";HT_{AK4};R2_{AK4}",40,0,2000,nbn_R2,bn_R2);
	h_MR_HT_Wjet_S_nj6 = new TH2D("MR_HT_Wjet_S_nj6", ";HT_{AK4};MR_{AK4}",40,0,2000,nbn_MR,bn_MR);
	h_AK8Jet1pT_MET_Wjet_S_nj6 = new TH2D("AK8Jet1pT_MET_Wjet_S_nj6", ";MET_{AK4};p_{T,AK8Jet1}",40,0,2000,40,0,2000);
	h_R2_MR_Wjet_S_nj45 = new TH2D("R2_MR_Wjet_S_nj45", ";MR_{AK4};R2_{AK4}",nbn_MR,bn_MR,nbn_R2,bn_R2);
	h_R2_MR_Wjet_S_nj6 = new TH2D("R2_MR_Wjet_S_nj6", ";MR_{AK4};R2_{AK4}",nbn_MR,bn_MR,nbn_R2,bn_R2);
  h_deepTagMD_WvsQCD_Wjet_S = new TH1D("deepTagMD_WvsQCD_Wjet_S", ";deepTagMD_{WvsQCD}", 20, 0, 1);
  h_deepTagMD_TvsQCD_Wjet_S = new TH1D("deepTagMD_TvsQCD_Wjet_S", ";deepTagMD_{TvsQCD}", 20, 0, 1);
  h_deepTag_WvsQCD_Wjet_S = new TH1D("deepTag_WvsQCD_Wjet_S", ";deepTag_{WvsQCD}", 20, 0, 1);
  h_deepTag_TvsQCD_Wjet_S = new TH1D("deepTag_TvsQCD_Wjet_S", ";deepTag_{TvsQCD}", 20, 0, 1);
	h_jet1_pt_Wjet_S = new TH1D("jet1_pt_Wjet_S",";p_{T, jet1}",200,0,2000);
	h_jet1_eta_Wjet_S = new TH1D("jet1_eta_Wjet_S",";#eta_{jet1}",480,-2.4,2.4);
	h_jet1_phi_Wjet_S = new TH1D("jet1_phi_Wjet_S",";#phi_{jet1}",640,-3.2,3.2);
	h_jets_pt_Wjet_S = new TH1D("jets_pt_Wjet_S",";p_{T, jets}",200,0,2000);
	h_jets_eta_Wjet_S = new TH1D("jets_eta_Wjet_S",";#eta_{jets}",480,-2.4,2.4);
	h_jets_phi_Wjet_S = new TH1D("jets_phi_Wjet_S",";#phi_{jets}",640,-3.2,3.2);
	h_AK8jet1_pt_Wjet_S = new TH1D("AK8jet1_pt_Wjet_S",";p_{T, AK8jet1}",200,0,2000);
	h_AK8jet1_eta_Wjet_S = new TH1D("AK8jet1_eta_Wjet_S",";#eta_{AK8jet1}",480,-2.4,2.4);
	h_AK8jet1_phi_Wjet_S = new TH1D("AK8jet1_phi_Wjet_S",";#phi_{AK8jet1}",640,-3.2,3.2);
	h_AK8jet1_tau21_Wjet_S = new TH1D("AK8jet1_tau21_Wjet_S",";tau_{21, AK8jet1}",20,0,1);
	h_AK8jet1_tau32_Wjet_S = new TH1D("AK8jet1_tau32_Wjet_S",";tau_{32, AK8jet1}",20,0,1);
	h_AK8jets_pt_Wjet_S = new TH1D("AK8jets_pt_Wjet_S",";p_{T, AK8jets}",200,0,2000);
	h_AK8jets_eta_Wjet_S = new TH1D("AK8jets_eta_Wjet_S",";#eta_{AK8jets}",480,-2.4,2.4);
	h_AK8jets_phi_Wjet_S = new TH1D("AK8jets_phi_Wjet_S",";#phi_{AK8jets}",640,-3.2,3.2);
	h_AK8jets_msoftdrop_Wjet_S = new TH1D("AK8jets_msoftdrop_Wjet_S",";p_{mass, AK8jets}",100,0,500);
	h_AK8jets_tau21_Wjet_S = new TH1D("AK8jets_tau21_Wjet_S",";tau_{21, AK8jets}",20,0,1);
	h_AK8jets_tau32_Wjet_S = new TH1D("AK8jets_tau32_Wjet_S",";tau_{32, AK8jets}",20,0,1);
	h_Wjets_pt_Wjet_S = new TH1D("Wjets_pt_Wjet_S",";p_{T, Boostjets}",200,0,2000);
	h_Wjets_eta_Wjet_S = new TH1D("Wjets_eta_Wjet_S",";#eta_{Boostjets}",480,-2.4,2.4);
	h_Wjets_phi_Wjet_S = new TH1D("Wjets_phi_Wjet_S",";#phi_{Boostjets}",640,-3.2,3.2);
	h_Wjets_tau21_Wjet_S = new TH1D("Wjets_tau21_Wjet_S",";tau_{21, Boostjets}",20,0,1);
	h_Wjets_tau32_Wjet_S = new TH1D("Wjets_tau32_Wjet_S",";tau_{21, Boostjets}",20,0,1);

	h_jet1_pt_Wjet_S_nj45 = new TH1D("jet1_pt_Wjet_S_nj45",";p_{T, jet1}",200,0,2000);
	h_jet1_eta_Wjet_S_nj45 = new TH1D("jet1_eta_Wjet_S_nj45",";#eta_{jet1}",480,-2.4,2.4);
	h_jet1_phi_Wjet_S_nj45 = new TH1D("jet1_phi_Wjet_S_nj45",";#phi_{jet1}",640,-3.2,3.2);
	h_jets_pt_Wjet_S_nj45 = new TH1D("jets_pt_Wjet_S_nj45",";p_{T, jets}",200,0,2000);
	h_jets_eta_Wjet_S_nj45 = new TH1D("jets_eta_Wjet_S_nj45",";#eta_{jets}",480,-2.4,2.4);
	h_jets_phi_Wjet_S_nj45 = new TH1D("jets_phi_Wjet_S_nj45",";#phi_{jets}",640,-3.2,3.2);
	h_AK8jet1_pt_Wjet_S_nj45 = new TH1D("AK8jet1_pt_Wjet_S_nj45",";p_{T, AK8jet1}",200,0,2000);
	h_AK8jet1_eta_Wjet_S_nj45 = new TH1D("AK8jet1_eta_Wjet_S_nj45",";#eta_{AK8jet1}",480,-2.4,2.4);
	h_AK8jet1_phi_Wjet_S_nj45 = new TH1D("AK8jet1_phi_Wjet_S_nj45",";#phi_{AK8jet1}",640,-3.2,3.2);
	h_AK8jet1_tau21_Wjet_S_nj45 = new TH1D("AK8jet1_tau21_Wjet_S_nj45",";tau_{21, AK8jet1}",20,0,1);
	h_AK8jet1_tau32_Wjet_S_nj45 = new TH1D("AK8jet1_tau32_Wjet_S_nj45",";tau_{32, AK8jet1}",20,0,1);
	h_AK8jets_pt_Wjet_S_nj45 = new TH1D("AK8jets_pt_Wjet_S_nj45",";p_{T, AK8jets}",200,0,2000);
	h_AK8jets_eta_Wjet_S_nj45 = new TH1D("AK8jets_eta_Wjet_S_nj45",";#eta_{AK8jets}",480,-2.4,2.4);
	h_AK8jets_phi_Wjet_S_nj45 = new TH1D("AK8jets_phi_Wjet_S_nj45",";#phi_{AK8jets}",640,-3.2,3.2);
	h_AK8jets_msoftdrop_Wjet_S_nj45 = new TH1D("AK8jets_msoftdrop_Wjet_S_nj45",";p_{mass, AK8jets}",100,0,500);
	h_AK8jets_tau21_Wjet_S_nj45 = new TH1D("AK8jets_tau21_Wjet_S_nj45",";tau_{21, AK8jets}",20,0,1);
	h_AK8jets_tau32_Wjet_S_nj45 = new TH1D("AK8jets_tau32_Wjet_S_nj45",";tau_{32, AK8jets}",20,0,1);
	h_Wjets_pt_Wjet_S_nj45 = new TH1D("Wjets_pt_Wjet_S_nj45",";p_{T, Boostjets}",200,0,2000);
	h_Wjets_eta_Wjet_S_nj45 = new TH1D("Wjets_eta_Wjet_S_nj45",";#eta_{Boostjets}",480,-2.4,2.4);
	h_Wjets_phi_Wjet_S_nj45 = new TH1D("Wjets_phi_Wjet_S_nj45",";#phi_{Boostjets}",640,-3.2,3.2);
	h_Wjets_tau21_Wjet_S_nj45 = new TH1D("Wjets_tau21_Wjet_S_nj45",";tau_{21, Boostjets}",20,0,1);
	h_Wjets_tau32_Wjet_S_nj45 = new TH1D("Wjets_tau32_Wjet_S_nj45",";tau_{21, Boostjets}",20,0,1);
	h_jet1_pt_Wjet_S_nj6 = new TH1D("jet1_pt_Wjet_S_nj6",";p_{T, jet1}",200,0,2000);
	h_jet1_eta_Wjet_S_nj6 = new TH1D("jet1_eta_Wjet_S_nj6",";#eta_{jet1}",480,-2.4,2.4);
	h_jet1_phi_Wjet_S_nj6 = new TH1D("jet1_phi_Wjet_S_nj6",";#phi_{jet1}",640,-3.2,3.2);
	h_jets_pt_Wjet_S_nj6 = new TH1D("jets_pt_Wjet_S_nj6",";p_{T, jets}",200,0,2000);
	h_jets_eta_Wjet_S_nj6 = new TH1D("jets_eta_Wjet_S_nj6",";#eta_{jets}",480,-2.4,2.4);
	h_jets_phi_Wjet_S_nj6 = new TH1D("jets_phi_Wjet_S_nj6",";#phi_{jets}",640,-3.2,3.2);
	h_AK8jet1_pt_Wjet_S_nj6 = new TH1D("AK8jet1_pt_Wjet_S_nj6",";p_{T, AK8jet1}",200,0,2000);
	h_AK8jet1_eta_Wjet_S_nj6 = new TH1D("AK8jet1_eta_Wjet_S_nj6",";#eta_{AK8jet1}",480,-2.4,2.4);
	h_AK8jet1_phi_Wjet_S_nj6 = new TH1D("AK8jet1_phi_Wjet_S_nj6",";#phi_{AK8jet1}",640,-3.2,3.2);
	h_AK8jet1_tau21_Wjet_S_nj6 = new TH1D("AK8jet1_tau21_Wjet_S_nj6",";tau_{21, AK8jet1}",20,0,1);
	h_AK8jet1_tau32_Wjet_S_nj6 = new TH1D("AK8jet1_tau32_Wjet_S_nj6",";tau_{32, AK8jet1}",20,0,1);
	h_AK8jets_pt_Wjet_S_nj6 = new TH1D("AK8jets_pt_Wjet_S_nj6",";p_{T, AK8jets}",200,0,2000);
	h_AK8jets_eta_Wjet_S_nj6 = new TH1D("AK8jets_eta_Wjet_S_nj6",";#eta_{AK8jets}",480,-2.4,2.4);
	h_AK8jets_phi_Wjet_S_nj6 = new TH1D("AK8jets_phi_Wjet_S_nj6",";#phi_{AK8jets}",640,-3.2,3.2);
	h_AK8jets_msoftdrop_Wjet_S_nj6 = new TH1D("AK8jets_msoftdrop_Wjet_S_nj6",";p_{mass, AK8jets}",100,0,500);
	h_AK8jets_tau21_Wjet_S_nj6 = new TH1D("AK8jets_tau21_Wjet_S_nj6",";tau_{21, AK8jets}",20,0,1);
	h_AK8jets_tau32_Wjet_S_nj6 = new TH1D("AK8jets_tau32_Wjet_S_nj6",";tau_{32, AK8jets}",20,0,1);
	h_Wjets_pt_Wjet_S_nj6 = new TH1D("Wjets_pt_Wjet_S_nj6",";p_{T, Boostjets}",200,0,2000);
	h_Wjets_eta_Wjet_S_nj6 = new TH1D("Wjets_eta_Wjet_S_nj6",";#eta_{Boostjets}",480,-2.4,2.4);
	h_Wjets_phi_Wjet_S_nj6 = new TH1D("Wjets_phi_Wjet_S_nj6",";#phi_{Boostjets}",640,-3.2,3.2);
	h_Wjets_tau21_Wjet_S_nj6 = new TH1D("Wjets_tau21_Wjet_S_nj6",";tau_{21, Boostjets}",20,0,1);
	h_Wjets_tau32_Wjet_S_nj6 = new TH1D("Wjets_tau32_Wjet_S_nj6",";tau_{21, Boostjets}",20,0,1);

	h_Megajets_pt_Topjet_S = new TH1D("Megajets_pt_Topjet_S",";p_{T, Megajets}",200,0,2000);
	h_Megajets_eta_Topjet_S = new TH1D("Megajets_eta_Topjet_S",";#eta_{Megajets}",480,-2.4,2.4);
	h_Megajets_phi_Topjet_S = new TH1D("Megajets_phi_Topjet_S",";#phi_{Megajets}",640,-3.2,3.2);
	h_njet_Topjet_S       = new TH1D("njet_Topjet_S",         ";N_{jet}",                20, 0,  20);
	h_nAK8jet_Topjet_S    = new TH1D("nAK8jet_Topjet_S",      ";N_{jet}",                20, 0,  20);
	h_ht_AK4_Topjet_S = new TH1D("ht_AK4_Topjet_S",  ";H_{T}",                  nbn_HT, bn_HT);
	h_MR_Topjet_S = new TH1D("MR_Topjet_S",   ";MR_{AK4}",     nbn_MR,    bn_MR);
	h_R2_Topjet_S = new TH1D("R2_Topjet_S",   ";R2_{AK4}",         nbn_R2,bn_R2);
	h_MET_Topjet_S = new TH1D("MET_Topjet_S", ";MET", 400,0,2000);
	h_MET_phi_Topjet_S = new TH1D("MET_phi_Topjet_S", ";#phi_{MET}", 640, -3.2,3.2);
	h_MET_phi_Topjet_S_nj45 = new TH1D("MET_phi_Topjet_S_nj45", ";#phi_{MET}", 640, -3.2,3.2);
	h_MET_phi_Topjet_S_nj6 = new TH1D("MET_phi_Topjet_S_nj6", ";#phi_{MET}", 640, -3.2,3.2);

	h_ht_AK4_Topjet_S_nj45 = new TH1D("ht_AK4_Topjet_S_nj45",  ";H_{T}",                  nbn_HT, bn_HT);
	h_MR_Topjet_S_nj45 = new TH1D("MR_Topjet_S_nj45",   ";MR_{AK4}",     nbn_MR,    bn_MR);
	h_R2_Topjet_S_nj45 = new TH1D("R2_Topjet_S_nj45",   ";R2_{AK4}",         nbn_R2,bn_R2);
	h_MET_Topjet_S_nj45 = new TH1D("MET_Topjet_S_nj45", ";MET", 400,0,2000);

	h_ht_AK4_Topjet_S_nj6 = new TH1D("ht_AK4_Topjet_S_nj6",  ";H_{T}",                  nbn_HT, bn_HT);
	h_MR_Topjet_S_nj6 = new TH1D("MR_Topjet_S_nj6",   ";MR_{AK4}",     nbn_MR,    bn_MR);
	h_R2_Topjet_S_nj6 = new TH1D("R2_Topjet_S_nj6",   ";R2_{AK4}",         nbn_R2,bn_R2);
	h_MET_Topjet_S_nj6 = new TH1D("MET_Topjet_S_nj6", ";MET", 400,0,2000);

	h_R2_MR_Topjet_S = new TH2D("R2_MR_Topjet_S", ";MR_{AK4};R2_{AK4}",nbn_MR,bn_MR,nbn_R2,bn_R2);
	h_R2_MET_Topjet_S = new TH2D("R2_MET_Topjet_S", ";MET_{AK4};R2_{AK4}",40,0,2000,nbn_R2,bn_R2);
	h_MR_MET_Topjet_S = new TH2D("MR_MET_Topjet_S", ";MET_{AK4};MR_{AK4}",40,0,2000,nbn_MR,bn_MR);
	h_HT_MET_Topjet_S = new TH2D("HT_MET_Topjet_S", ";MET_{AK4};HT_{AK4}",40,0,2000,40,0,2000);
	h_R2_HT_Topjet_S = new TH2D("R2_HT_Topjet_S", ";HT_{AK4};R2_{AK4}",40,0,2000,nbn_R2,bn_R2);
	h_MR_HT_Topjet_S = new TH2D("MR_HT_Topjet_S", ";HT_{AK4};MR_{AK4}",40,0,2000,nbn_MR,bn_MR);
	h_AK8Jet1pT_MET_Topjet_S = new TH2D("AK8Jet1pT_MET_Topjet_S", ";MET_{AK4};p_{T,AK8Jet1}",40,0,2000,40,0,2000);
	h_R2_MET_Topjet_S_nj45 = new TH2D("R2_MET_Topjet_S_nj45", ";MET_{AK4};R2_{AK4}",40,0,2000,nbn_R2,bn_R2);
	h_MR_MET_Topjet_S_nj45 = new TH2D("MR_MET_Topjet_S_nj45", ";MET_{AK4};MR_{AK4}",40,0,2000,nbn_MR,bn_MR);
	h_HT_MET_Topjet_S_nj45 = new TH2D("HT_MET_Topjet_S_nj45", ";MET_{AK4};HT_{AK4}",40,0,2000,40,0,2000);
	h_R2_HT_Topjet_S_nj45 = new TH2D("R2_HT_Topjet_S_nj45", ";HT_{AK4};R2_{AK4}",40,0,2000,nbn_R2,bn_R2);
	h_MR_HT_Topjet_S_nj45 = new TH2D("MR_HT_Topjet_S_nj45", ";HT_{AK4};MR_{AK4}",40,0,2000,nbn_MR,bn_MR);
	h_AK8Jet1pT_MET_Topjet_S_nj45 = new TH2D("AK8Jet1pT_MET_Topjet_S_nj45", ";MET_{AK4};p_{T,AK8Jet1}",40,0,2000,40,0,2000);
	h_R2_MET_Topjet_S_nj6 = new TH2D("R2_MET_Topjet_S_nj6", ";MET_{AK4};R2_{AK4}",40,0,2000,nbn_R2,bn_R2);
	h_MR_MET_Topjet_S_nj6 = new TH2D("MR_MET_Topjet_S_nj6", ";MET_{AK4};MR_{AK4}",40,0,2000,nbn_MR,bn_MR);
	h_HT_MET_Topjet_S_nj6 = new TH2D("HT_MET_Topjet_S_nj6", ";MET_{AK4};HT_{AK4}",40,0,2000,40,0,2000);
	h_R2_HT_Topjet_S_nj6 = new TH2D("R2_HT_Topjet_S_nj6", ";HT_{AK4};R2_{AK4}",40,0,2000,nbn_R2,bn_R2);
	h_MR_HT_Topjet_S_nj6 = new TH2D("MR_HT_Topjet_S_nj6", ";HT_{AK4};MR_{AK4}",40,0,2000,nbn_MR,bn_MR);
	h_AK8Jet1pT_MET_Topjet_S_nj6 = new TH2D("AK8Jet1pT_MET_Topjet_S_nj6", ";MET_{AK4};p_{T,AK8Jet1}",40,0,2000,40,0,2000);
	h_R2_MR_Topjet_S_nj45 = new TH2D("R2_MR_Topjet_S_nj45", ";MR_{AK4};R2_{AK4}",nbn_MR,bn_MR,nbn_R2,bn_R2);
	h_R2_MR_Topjet_S_nj6 = new TH2D("R2_MR_Topjet_S_nj6", ";MR_{AK4};R2_{AK4}",nbn_MR,bn_MR,nbn_R2,bn_R2);
  h_deepTagMD_WvsQCD_Topjet_S = new TH1D("deepTagMD_WvsQCD_Topjet_S", ";deepTagMD_{WvsQCD}", 20, 0, 1);
  h_deepTagMD_TvsQCD_Topjet_S = new TH1D("deepTagMD_TvsQCD_Topjet_S", ";deepTagMD_{TvsQCD}", 20, 0, 1);
  h_deepTag_WvsQCD_Topjet_S = new TH1D("deepTag_WvsQCD_Topjet_S", ";deepTag_{WvsQCD}", 20, 0, 1);
  h_deepTag_TvsQCD_Topjet_S = new TH1D("deepTag_TvsQCD_Topjet_S", ";deepTag_{TvsQCD}", 20, 0, 1);
	h_jet1_pt_Topjet_S = new TH1D("jet1_pt_Topjet_S",";p_{T, jet1}",200,0,2000);
	h_jet1_eta_Topjet_S = new TH1D("jet1_eta_Topjet_S",";#eta_{jet1}",480,-2.4,2.4);
	h_jet1_phi_Topjet_S = new TH1D("jet1_phi_Topjet_S",";#phi_{jet1}",640,-3.2,3.2);
	h_jets_pt_Topjet_S = new TH1D("jets_pt_Topjet_S",";p_{T, jets}",200,0,2000);
	h_jets_eta_Topjet_S = new TH1D("jets_eta_Topjet_S",";#eta_{jets}",480,-2.4,2.4);
	h_jets_phi_Topjet_S = new TH1D("jets_phi_Topjet_S",";#phi_{jets}",640,-3.2,3.2);
	h_AK8jet1_pt_Topjet_S = new TH1D("AK8jet1_pt_Topjet_S",";p_{T, AK8jet1}",200,0,2000);
	h_AK8jet1_eta_Topjet_S = new TH1D("AK8jet1_eta_Topjet_S",";#eta_{AK8jet1}",480,-2.4,2.4);
	h_AK8jet1_phi_Topjet_S = new TH1D("AK8jet1_phi_Topjet_S",";#phi_{AK8jet1}",640,-3.2,3.2);
	h_AK8jet1_tau21_Topjet_S = new TH1D("AK8jet1_tau21_Topjet_S",";tau_{21, AK8jet1}",20,0,1);
	h_AK8jet1_tau32_Topjet_S = new TH1D("AK8jet1_tau32_Topjet_S",";tau_{32, AK8jet1}",20,0,1);
	h_AK8jets_pt_Topjet_S = new TH1D("AK8jets_pt_Topjet_S",";p_{T, AK8jets}",200,0,2000);
	h_AK8jets_eta_Topjet_S = new TH1D("AK8jets_eta_Topjet_S",";#eta_{AK8jets}",480,-2.4,2.4);
	h_AK8jets_phi_Topjet_S = new TH1D("AK8jets_phi_Topjet_S",";#phi_{AK8jets}",640,-3.2,3.2);
	h_AK8jets_msoftdrop_Topjet_S = new TH1D("AK8jets_msoftdrop_Topjet_S",";p_{mass, AK8jets}",100,0,500);
	h_AK8jets_tau21_Topjet_S = new TH1D("AK8jets_tau21_Topjet_S",";tau_{21, AK8jets}",20,0,1);
	h_AK8jets_tau32_Topjet_S = new TH1D("AK8jets_tau32_Topjet_S",";tau_{32, AK8jets}",20,0,1);
	h_Topjets_pt_Topjet_S = new TH1D("Topjets_pt_Topjet_S",";p_{T, Boostjets}",200,0,2000);
	h_Topjets_eta_Topjet_S = new TH1D("Topjets_eta_Topjet_S",";#eta_{Boostjets}",480,-2.4,2.4);
	h_Topjets_phi_Topjet_S = new TH1D("Topjets_phi_Topjet_S",";#phi_{Boostjets}",640,-3.2,3.2);
	h_Topjets_tau21_Topjet_S = new TH1D("Topjets_tau21_Topjet_S",";tau_{21, Boostjets}",20,0,1);
	h_Topjets_tau32_Topjet_S = new TH1D("Topjets_tau32_Topjet_S",";tau_{32, Boostjets}",20,0,1);

	h_jet1_pt_Topjet_S_nj45 = new TH1D("jet1_pt_Topjet_S_nj45",";p_{T, jet1}",200,0,2000);
	h_jet1_eta_Topjet_S_nj45 = new TH1D("jet1_eta_Topjet_S_nj45",";#eta_{jet1}",480,-2.4,2.4);
	h_jet1_phi_Topjet_S_nj45 = new TH1D("jet1_phi_Topjet_S_nj45",";#phi_{jet1}",640,-3.2,3.2);
	h_jets_pt_Topjet_S_nj45 = new TH1D("jets_pt_Topjet_S_nj45",";p_{T, jets}",200,0,2000);
	h_jets_eta_Topjet_S_nj45 = new TH1D("jets_eta_Topjet_S_nj45",";#eta_{jets}",480,-2.4,2.4);
	h_jets_phi_Topjet_S_nj45 = new TH1D("jets_phi_Topjet_S_nj45",";#phi_{jets}",640,-3.2,3.2);
	h_AK8jet1_pt_Topjet_S_nj45 = new TH1D("AK8jet1_pt_Topjet_S_nj45",";p_{T, AK8jet1}",200,0,2000);
	h_AK8jet1_eta_Topjet_S_nj45 = new TH1D("AK8jet1_eta_Topjet_S_nj45",";#eta_{AK8jet1}",480,-2.4,2.4);
	h_AK8jet1_phi_Topjet_S_nj45 = new TH1D("AK8jet1_phi_Topjet_S_nj45",";#phi_{AK8jet1}",640,-3.2,3.2);
	h_AK8jet1_tau21_Topjet_S_nj45 = new TH1D("AK8jet1_tau21_Topjet_S_nj45",";tau_{21, AK8jet1}",20,0,1);
	h_AK8jet1_tau32_Topjet_S_nj45 = new TH1D("AK8jet1_tau32_Topjet_S_nj45",";tau_{32, AK8jet1}",20,0,1);
	h_AK8jets_pt_Topjet_S_nj45 = new TH1D("AK8jets_pt_Topjet_S_nj45",";p_{T, AK8jets}",200,0,2000);
	h_AK8jets_eta_Topjet_S_nj45 = new TH1D("AK8jets_eta_Topjet_S_nj45",";#eta_{AK8jets}",480,-2.4,2.4);
	h_AK8jets_phi_Topjet_S_nj45 = new TH1D("AK8jets_phi_Topjet_S_nj45",";#phi_{AK8jets}",640,-3.2,3.2);
	h_AK8jets_msoftdrop_Topjet_S_nj45 = new TH1D("AK8jets_msoftdrop_Topjet_S_nj45",";p_{mass, AK8jets}",100,0,500);
	h_AK8jets_tau21_Topjet_S_nj45 = new TH1D("AK8jets_tau21_Topjet_S_nj45",";tau_{21, AK8jets}",20,0,1);
	h_AK8jets_tau32_Topjet_S_nj45 = new TH1D("AK8jets_tau32_Topjet_S_nj45",";tau_{32, AK8jets}",20,0,1);
	h_Topjets_pt_Topjet_S_nj45 = new TH1D("Topjets_pt_Topjet_S_nj45",";p_{T, Boostjets}",200,0,2000);
	h_Topjets_eta_Topjet_S_nj45 = new TH1D("Topjets_eta_Topjet_S_nj45",";#eta_{Boostjets}",480,-2.4,2.4);
	h_Topjets_phi_Topjet_S_nj45 = new TH1D("Topjets_phi_Topjet_S_nj45",";#phi_{Boostjets}",640,-3.2,3.2);
	h_Topjets_tau21_Topjet_S_nj45 = new TH1D("Topjets_tau21_Topjet_S_nj45",";tau_{21, Boostjets}",20,0,1);
	h_Topjets_tau32_Topjet_S_nj45 = new TH1D("Topjets_tau32_Topjet_S_nj45",";tau_{32, Boostjets}",20,0,1);
	h_jet1_pt_Topjet_S_nj6 = new TH1D("jet1_pt_Topjet_S_nj6",";p_{T, jet1}",200,0,2000);
	h_jet1_eta_Topjet_S_nj6 = new TH1D("jet1_eta_Topjet_S_nj6",";#eta_{jet1}",480,-2.4,2.4);
	h_jet1_phi_Topjet_S_nj6 = new TH1D("jet1_phi_Topjet_S_nj6",";#phi_{jet1}",640,-3.2,3.2);
	h_jets_pt_Topjet_S_nj6 = new TH1D("jets_pt_Topjet_S_nj6",";p_{T, jets}",200,0,2000);
	h_jets_eta_Topjet_S_nj6 = new TH1D("jets_eta_Topjet_S_nj6",";#eta_{jets}",480,-2.4,2.4);
	h_jets_phi_Topjet_S_nj6 = new TH1D("jets_phi_Topjet_S_nj6",";#phi_{jets}",640,-3.2,3.2);
	h_AK8jet1_pt_Topjet_S_nj6 = new TH1D("AK8jet1_pt_Topjet_S_nj6",";p_{T, AK8jet1}",200,0,2000);
	h_AK8jet1_eta_Topjet_S_nj6 = new TH1D("AK8jet1_eta_Topjet_S_nj6",";#eta_{AK8jet1}",480,-2.4,2.4);
	h_AK8jet1_phi_Topjet_S_nj6 = new TH1D("AK8jet1_phi_Topjet_S_nj6",";#phi_{AK8jet1}",640,-3.2,3.2);
	h_AK8jet1_tau21_Topjet_S_nj6 = new TH1D("AK8jet1_tau21_Topjet_S_nj6",";tau_{21, AK8jet1}",20,0,1);
	h_AK8jet1_tau32_Topjet_S_nj6 = new TH1D("AK8jet1_tau32_Topjet_S_nj6",";tau_{32, AK8jet1}",20,0,1);
	h_AK8jets_pt_Topjet_S_nj6 = new TH1D("AK8jets_pt_Topjet_S_nj6",";p_{T, AK8jets}",200,0,2000);
	h_AK8jets_eta_Topjet_S_nj6 = new TH1D("AK8jets_eta_Topjet_S_nj6",";#eta_{AK8jets}",480,-2.4,2.4);
	h_AK8jets_phi_Topjet_S_nj6 = new TH1D("AK8jets_phi_Topjet_S_nj6",";#phi_{AK8jets}",640,-3.2,3.2);
	h_AK8jets_msoftdrop_Topjet_S_nj6 = new TH1D("AK8jets_msoftdrop_Topjet_S_nj6",";p_{mass, AK8jets}",100,0,500);
	h_AK8jets_tau21_Topjet_S_nj6 = new TH1D("AK8jets_tau21_Topjet_S_nj6",";tau_{21, AK8jets}",20,0,1);
	h_AK8jets_tau32_Topjet_S_nj6 = new TH1D("AK8jets_tau32_Topjet_S_nj6",";tau_{32, AK8jets}",20,0,1);
	h_Topjets_pt_Topjet_S_nj6 = new TH1D("Topjets_pt_Topjet_S_nj6",";p_{T, Boostjets}",200,0,2000);
	h_Topjets_eta_Topjet_S_nj6 = new TH1D("Topjets_eta_Topjet_S_nj6",";#eta_{Boostjets}",480,-2.4,2.4);
	h_Topjets_phi_Topjet_S_nj6 = new TH1D("Topjets_phi_Topjet_S_nj6",";#phi_{Boostjets}",640,-3.2,3.2);
	h_Topjets_tau21_Topjet_S_nj6 = new TH1D("Topjets_tau21_Topjet_S_nj6",";tau_{21, Boostjets}",20,0,1);
	h_Topjets_tau32_Topjet_S_nj6 = new TH1D("Topjets_tau32_Topjet_S_nj6",";tau_{32, Boostjets}",20,0,1);

	h_jet1_pt_s = new TH1D("jet1_pt_s",";p_{T, jet1}",200,0,2000);
	h_jet1_eta_s = new TH1D("jet1_eta_s",";#eta_{jet1}",480,-2.4,2.4);
	h_jet1_phi_s = new TH1D("jet1_phi_s",";#phi_{jet1}",640,-3.2,3.2);
	h_jets_pt_s = new TH1D("jets_pt_s",";p_{T, jets}",200,0,2000);
	h_jets_eta_s = new TH1D("jets_eta_s",";#eta_{jets}",480,-2.4,2.4);
	h_jets_phi_s = new TH1D("jets_phi_s",";#phi_{jets}",640,-3.2,3.2);
	h_AK8jet1_pt_s = new TH1D("AK8jet1_pt_s",";p_{T, AK8jet1}",200,0,2000);
	h_AK8jet1_eta_s = new TH1D("AK8jet1_eta_s",";#eta_{AK8jet1}",480,-2.4,2.4);
	h_AK8jet1_phi_s = new TH1D("AK8jet1_phi_s",";#phi_{AK8jet1}",640,-3.2,3.2);
	h_AK8jet1_tau21_s = new TH1D("AK8jet1_tau21_s",";tau_{21, AK8jet1}",20,0,1);
	h_AK8jet1_tau32_s = new TH1D("AK8jet1_tau32_s",";tau_{32, AK8jet1}",20,0,1);
	h_AK8jets_pt_s = new TH1D("AK8jets_pt_s",";p_{T, AK8jets}",200,0,2000);
	h_AK8jets_eta_s = new TH1D("AK8jets_eta_s",";#eta_{AK8jets}",480,-2.4,2.4);
	h_AK8jets_phi_s = new TH1D("AK8jets_phi_s",";#phi_{AK8jets}",640,-3.2,3.2);
	h_AK8jets_msoftdrop_s = new TH1D("AK8jets_msoftdrop_s",";p_{mass, AK8jets}",100,0,500);
	h_AK8jets_tau21_s = new TH1D("AK8jets_tau21_s",";tau_{21, AK8jets}",20,0,1);
	h_AK8jets_tau32_s = new TH1D("AK8jets_tau32_s",";tau_{32, AK8jets}",20,0,1);
#if TOP == 0
	h_Wjets_pt_s = new TH1D("Wjets_pt_s",";p_{T, Boostjets}",200,0,2000);
	h_Wjets_eta_s = new TH1D("Wjets_eta_s",";#eta_{Boostjets}",480,-2.4,2.4);
	h_Wjets_phi_s = new TH1D("Wjets_phi_s",";#phi_{Boostjets}",640,-3.2,3.2);
	h_Wjets_tau21_s = new TH1D("Wjets_tau21_s",";tau_{21, Boostjets}",20,0,1);
	h_Wjets_tau32_s = new TH1D("Wjets_tau32_s",";tau_{21, Boostjets}",20,0,1);
#else
	h_Topjets_pt_s = new TH1D("Topjets_pt_s",";p_{T, Boostjets}",200,0,2000);
	h_Topjets_eta_s = new TH1D("Topjets_eta_s",";#eta_{Boostjets}",480,-2.4,2.4);
	h_Topjets_phi_s = new TH1D("Topjets_phi_s",";#phi_{Boostjets}",640,-3.2,3.2);
	h_Topjets_tau21_s = new TH1D("Topjets_tau21_s",";tau_{21, Boostjets}",20,0,1);
	h_Topjets_tau32_s = new TH1D("Topjets_tau32_s",";tau_{32, Boostjets}",20,0,1);
#endif
	h_jet1_pt_s_nj45 = new TH1D("jet1_pt_s_nj45",";p_{T, jet1}",200,0,2000);
	h_jet1_eta_s_nj45 = new TH1D("jet1_eta_s_nj45",";#eta_{jet1}",480,-2.4,2.4);
	h_jet1_phi_s_nj45 = new TH1D("jet1_phi_s_nj45",";#phi_{jet1}",640,-3.2,3.2);
	h_jets_pt_s_nj45 = new TH1D("jets_pt_s_nj45",";p_{T, jets}",200,0,2000);
	h_jets_eta_s_nj45 = new TH1D("jets_eta_s_nj45",";#eta_{jets}",480,-2.4,2.4);
	h_jets_phi_s_nj45 = new TH1D("jets_phi_s_nj45",";#phi_{jets}",640,-3.2,3.2);
	h_AK8jet1_pt_s_nj45 = new TH1D("AK8jet1_pt_s_nj45",";p_{T, AK8jet1}",200,0,2000);
	h_AK8jet1_eta_s_nj45 = new TH1D("AK8jet1_eta_s_nj45",";#eta_{AK8jet1}",480,-2.4,2.4);
	h_AK8jet1_phi_s_nj45 = new TH1D("AK8jet1_phi_s_nj45",";#phi_{AK8jet1}",640,-3.2,3.2);
	h_AK8jet1_tau21_s_nj45 = new TH1D("AK8jet1_tau21_s_nj45",";tau_{21, AK8jet1}",20,0,1);
	h_AK8jet1_tau32_s_nj45 = new TH1D("AK8jet1_tau32_s_nj45",";tau_{32, AK8jet1}",20,0,1);
	h_AK8jets_pt_s_nj45 = new TH1D("AK8jets_pt_s_nj45",";p_{T, AK8jets}",200,0,2000);
	h_AK8jets_eta_s_nj45 = new TH1D("AK8jets_eta_s_nj45",";#eta_{AK8jets}",480,-2.4,2.4);
	h_AK8jets_phi_s_nj45 = new TH1D("AK8jets_phi_s_nj45",";#phi_{AK8jets}",640,-3.2,3.2);
	h_AK8jets_msoftdrop_s_nj45 = new TH1D("AK8jets_msoftdrop_s_nj45",";p_{mass, AK8jets}",100,0,500);
	h_AK8jets_tau21_s_nj45 = new TH1D("AK8jets_tau21_s_nj45",";tau_{21, AK8jets}",20,0,1);
	h_AK8jets_tau32_s_nj45 = new TH1D("AK8jets_tau32_s_nj45",";tau_{32, AK8jets}",20,0,1);
#if TOP == 0
	h_Wjets_pt_s_nj45 = new TH1D("Wjets_pt_s_nj45",";p_{T, Boostjets}",200,0,2000);
	h_Wjets_eta_s_nj45 = new TH1D("Wjets_eta_s_nj45",";#eta_{Boostjets}",480,-2.4,2.4);
	h_Wjets_phi_s_nj45 = new TH1D("Wjets_phi_s_nj45",";#phi_{Boostjets}",640,-3.2,3.2);
	h_Wjets_tau21_s_nj45 = new TH1D("Wjets_tau21_s_nj45",";tau_{21, Boostjets}",20,0,1);
	h_Wjets_tau32_s_nj45 = new TH1D("Wjets_tau32_s_nj45",";tau_{21, Boostjets}",20,0,1);
#else
	h_Topjets_pt_s_nj45 = new TH1D("Topjets_pt_s_nj45",";p_{T, Boostjets}",200,0,2000);
	h_Topjets_eta_s_nj45 = new TH1D("Topjets_eta_s_nj45",";#eta_{Boostjets}",480,-2.4,2.4);
	h_Topjets_phi_s_nj45 = new TH1D("Topjets_phi_s_nj45",";#phi_{Boostjets}",640,-3.2,3.2);
	h_Topjets_tau21_s_nj45 = new TH1D("Topjets_tau21_s_nj45",";tau_{21, Boostjets}",20,0,1);
	h_Topjets_tau32_s_nj45 = new TH1D("Topjets_tau32_s_nj45",";tau_{32, Boostjets}",20,0,1);
#endif
	h_jet1_pt_s_nj6 = new TH1D("jet1_pt_s_nj6",";p_{T, jet1}",200,0,2000);
	h_jet1_eta_s_nj6 = new TH1D("jet1_eta_s_nj6",";#eta_{jet1}",480,-2.4,2.4);
	h_jet1_phi_s_nj6 = new TH1D("jet1_phi_s_nj6",";#phi_{jet1}",640,-3.2,3.2);
	h_jets_pt_s_nj6 = new TH1D("jets_pt_s_nj6",";p_{T, jets}",200,0,2000);
	h_jets_eta_s_nj6 = new TH1D("jets_eta_s_nj6",";#eta_{jets}",480,-2.4,2.4);
	h_jets_phi_s_nj6 = new TH1D("jets_phi_s_nj6",";#phi_{jets}",640,-3.2,3.2);
	h_AK8jet1_pt_s_nj6 = new TH1D("AK8jet1_pt_s_nj6",";p_{T, AK8jet1}",200,0,2000);
	h_AK8jet1_eta_s_nj6 = new TH1D("AK8jet1_eta_s_nj6",";#eta_{AK8jet1}",480,-2.4,2.4);
	h_AK8jet1_phi_s_nj6 = new TH1D("AK8jet1_phi_s_nj6",";#phi_{AK8jet1}",640,-3.2,3.2);
	h_AK8jet1_tau21_s_nj6 = new TH1D("AK8jet1_tau21_s_nj6",";tau_{21, AK8jet1}",20,0,1);
	h_AK8jet1_tau32_s_nj6 = new TH1D("AK8jet1_tau32_s_nj6",";tau_{32, AK8jet1}",20,0,1);
	h_AK8jets_pt_s_nj6 = new TH1D("AK8jets_pt_s_nj6",";p_{T, AK8jets}",200,0,2000);
	h_AK8jets_eta_s_nj6 = new TH1D("AK8jets_eta_s_nj6",";#eta_{AK8jets}",480,-2.4,2.4);
	h_AK8jets_phi_s_nj6 = new TH1D("AK8jets_phi_s_nj6",";#phi_{AK8jets}",640,-3.2,3.2);
	h_AK8jets_msoftdrop_s_nj6 = new TH1D("AK8jets_msoftdrop_s_nj6",";p_{mass, AK8jets}",100,0,500);
	h_AK8jets_tau21_s_nj6 = new TH1D("AK8jets_tau21_s_nj6",";tau_{21, AK8jets}",20,0,1);
	h_AK8jets_tau32_s_nj6 = new TH1D("AK8jets_tau32_s_nj6",";tau_{32, AK8jets}",20,0,1);
#if TOP == 0
	h_Wjets_pt_s_nj6 = new TH1D("Wjets_pt_s_nj6",";p_{T, Boostjets}",200,0,2000);
	h_Wjets_eta_s_nj6 = new TH1D("Wjets_eta_s_nj6",";#eta_{Boostjets}",480,-2.4,2.4);
	h_Wjets_phi_s_nj6 = new TH1D("Wjets_phi_s_nj6",";#phi_{Boostjets}",640,-3.2,3.2);
	h_Wjets_tau21_s_nj6 = new TH1D("Wjets_tau21_s_nj6",";tau_{21, Boostjets}",20,0,1);
	h_Wjets_tau32_s_nj6 = new TH1D("Wjets_tau32_s_nj6",";tau_{21, Boostjets}",20,0,1);
#else
	h_Topjets_pt_s_nj6 = new TH1D("Topjets_pt_s_nj6",";p_{T, Boostjets}",200,0,2000);
	h_Topjets_eta_s_nj6 = new TH1D("Topjets_eta_s_nj6",";#eta_{Boostjets}",480,-2.4,2.4);
	h_Topjets_phi_s_nj6 = new TH1D("Topjets_phi_s_nj6",";#phi_{Boostjets}",640,-3.2,3.2);
	h_Topjets_tau21_s_nj6 = new TH1D("Topjets_tau21_s_nj6",";tau_{21, Boostjets}",20,0,1);
	h_Topjets_tau32_s_nj6 = new TH1D("Topjets_tau32_s_nj6",";tau_{32, Boostjets}",20,0,1);
#endif

	h_jet1_pt_Q = new TH1D("jet1_pt_Q",";p_{T, jet1}",200,0,2000);
	h_jet1_eta_Q = new TH1D("jet1_eta_Q",";#eta_{jet1}",480,-2.4,2.4);
	h_jet1_phi_Q = new TH1D("jet1_phi_Q",";#phi_{jet1}",640,-3.2,3.2);
	h_jets_pt_Q = new TH1D("jets_pt_Q",";p_{T, jets}",200,0,2000);
	h_jets_eta_Q = new TH1D("jets_eta_Q",";#eta_{jets}",480,-2.4,2.4);
	h_jets_phi_Q = new TH1D("jets_phi_Q",";#phi_{jets}",640,-3.2,3.2);
	h_AK8jet1_pt_Q = new TH1D("AK8jet1_pt_Q",";p_{T, AK8jet1}",200,0,2000);
	h_AK8jet1_eta_Q = new TH1D("AK8jet1_eta_Q",";#eta_{AK8jet1}",480,-2.4,2.4);
	h_AK8jet1_phi_Q = new TH1D("AK8jet1_phi_Q",";#phi_{AK8jet1}",640,-3.2,3.2);
	h_AK8jet1_tau21_Q = new TH1D("AK8jet1_tau21_Q",";tau_{21, AK8jet1}",20,0,1);
	h_AK8jet1_tau32_Q = new TH1D("AK8jet1_tau32_Q",";tau_{32, AK8jet1}",20,0,1);
	h_AK8jets_pt_Q = new TH1D("AK8jets_pt_Q",";p_{T, AK8jets}",200,0,2000);
	h_AK8jets_eta_Q = new TH1D("AK8jets_eta_Q",";#eta_{AK8jets}",480,-2.4,2.4);
	h_AK8jets_phi_Q = new TH1D("AK8jets_phi_Q",";#phi_{AK8jets}",640,-3.2,3.2);
	h_AK8jets_msoftdrop_Q = new TH1D("AK8jets_msoftdrop_Q",";p_{mass, AK8jets}",100,0,500);
	h_AK8jets_tau21_Q = new TH1D("AK8jets_tau21_Q",";tau_{21, AK8jets}",20,0,1);
	h_AK8jets_tau32_Q = new TH1D("AK8jets_tau32_Q",";tau_{32, AK8jets}",20,0,1);
#if TOP == 0
	h_Wjets_pt_Q = new TH1D("Wjets_pt_Q",";p_{T, Boostjets}",200,0,2000);
	h_Wjets_eta_Q = new TH1D("Wjets_eta_Q",";#eta_{Boostjets}",480,-2.4,2.4);
	h_Wjets_phi_Q = new TH1D("Wjets_phi_Q",";#phi_{Boostjets}",640,-3.2,3.2);
	h_Wjets_tau21_Q = new TH1D("Wjets_tau21_Q",";tau_{21, Boostjets}",20,0,1);
	h_Wjets_tau32_Q = new TH1D("Wjets_tau32_Q",";tau_{21, Boostjets}",20,0,1);
#else
	h_Topjets_pt_Q = new TH1D("Topjets_pt_Q",";p_{T, Boostjets}",200,0,2000);
	h_Topjets_eta_Q = new TH1D("Topjets_eta_Q",";#eta_{Boostjets}",480,-2.4,2.4);
	h_Topjets_phi_Q = new TH1D("Topjets_phi_Q",";#phi_{Boostjets}",640,-3.2,3.2);
	h_Topjets_tau21_Q = new TH1D("Topjets_tau21_Q",";tau_{21, Boostjets}",20,0,1);
	h_Topjets_tau32_Q = new TH1D("Topjets_tau32_Q",";tau_{32, Boostjets}",20,0,1);
#endif
	h_jet1_pt_Q_nj45 = new TH1D("jet1_pt_Q_nj45",";p_{T, jet1}",200,0,2000);
	h_jet1_eta_Q_nj45 = new TH1D("jet1_eta_Q_nj45",";#eta_{jet1}",480,-2.4,2.4);
	h_jet1_phi_Q_nj45 = new TH1D("jet1_phi_Q_nj45",";#phi_{jet1}",640,-3.2,3.2);
	h_jets_pt_Q_nj45 = new TH1D("jets_pt_Q_nj45",";p_{T, jets}",200,0,2000);
	h_jets_eta_Q_nj45 = new TH1D("jets_eta_Q_nj45",";#eta_{jets}",480,-2.4,2.4);
	h_jets_phi_Q_nj45 = new TH1D("jets_phi_Q_nj45",";#phi_{jets}",640,-3.2,3.2);
	h_AK8jet1_pt_Q_nj45 = new TH1D("AK8jet1_pt_Q_nj45",";p_{T, AK8jet1}",200,0,2000);
	h_AK8jet1_eta_Q_nj45 = new TH1D("AK8jet1_eta_Q_nj45",";#eta_{AK8jet1}",480,-2.4,2.4);
	h_AK8jet1_phi_Q_nj45 = new TH1D("AK8jet1_phi_Q_nj45",";#phi_{AK8jet1}",640,-3.2,3.2);
	h_AK8jet1_tau21_Q_nj45 = new TH1D("AK8jet1_tau21_Q_nj45",";tau_{21, AK8jet1}",20,0,1);
	h_AK8jet1_tau32_Q_nj45 = new TH1D("AK8jet1_tau32_Q_nj45",";tau_{32, AK8jet1}",20,0,1);
	h_AK8jets_pt_Q_nj45 = new TH1D("AK8jets_pt_Q_nj45",";p_{T, AK8jets}",200,0,2000);
	h_AK8jets_eta_Q_nj45 = new TH1D("AK8jets_eta_Q_nj45",";#eta_{AK8jets}",480,-2.4,2.4);
	h_AK8jets_phi_Q_nj45 = new TH1D("AK8jets_phi_Q_nj45",";#phi_{AK8jets}",640,-3.2,3.2);
	h_AK8jets_msoftdrop_Q_nj45 = new TH1D("AK8jets_msoftdrop_Q_nj45",";p_{mass, AK8jets}",100,0,500);
	h_AK8jets_tau21_Q_nj45 = new TH1D("AK8jets_tau21_Q_nj45",";tau_{21, AK8jets}",20,0,1);
	h_AK8jets_tau32_Q_nj45 = new TH1D("AK8jets_tau32_Q_nj45",";tau_{32, AK8jets}",20,0,1);
#if TOP == 0
	h_Wjets_pt_Q_nj45 = new TH1D("Wjets_pt_Q_nj45",";p_{T, Boostjets}",200,0,2000);
	h_Wjets_eta_Q_nj45 = new TH1D("Wjets_eta_Q_nj45",";#eta_{Boostjets}",480,-2.4,2.4);
	h_Wjets_phi_Q_nj45 = new TH1D("Wjets_phi_Q_nj45",";#phi_{Boostjets}",640,-3.2,3.2);
	h_Wjets_tau21_Q_nj45 = new TH1D("Wjets_tau21_Q_nj45",";tau_{21, Boostjets}",20,0,1);
	h_Wjets_tau32_Q_nj45 = new TH1D("Wjets_tau32_Q_nj45",";tau_{21, Boostjets}",20,0,1);
#else
	h_Topjets_pt_Q_nj45 = new TH1D("Topjets_pt_Q_nj45",";p_{T, Boostjets}",200,0,2000);
	h_Topjets_eta_Q_nj45 = new TH1D("Topjets_eta_Q_nj45",";#eta_{Boostjets}",480,-2.4,2.4);
	h_Topjets_phi_Q_nj45 = new TH1D("Topjets_phi_Q_nj45",";#phi_{Boostjets}",640,-3.2,3.2);
	h_Topjets_tau21_Q_nj45 = new TH1D("Topjets_tau21_Q_nj45",";tau_{21, Boostjets}",20,0,1);
	h_Topjets_tau32_Q_nj45 = new TH1D("Topjets_tau32_Q_nj45",";tau_{32, Boostjets}",20,0,1);
#endif
	h_jet1_pt_Q_nj6 = new TH1D("jet1_pt_Q_nj6",";p_{T, jet1}",200,0,2000);
	h_jet1_eta_Q_nj6 = new TH1D("jet1_eta_Q_nj6",";#eta_{jet1}",480,-2.4,2.4);
	h_jet1_phi_Q_nj6 = new TH1D("jet1_phi_Q_nj6",";#phi_{jet1}",640,-3.2,3.2);
	h_jets_pt_Q_nj6 = new TH1D("jets_pt_Q_nj6",";p_{T, jets}",200,0,2000);
	h_jets_eta_Q_nj6 = new TH1D("jets_eta_Q_nj6",";#eta_{jets}",480,-2.4,2.4);
	h_jets_phi_Q_nj6 = new TH1D("jets_phi_Q_nj6",";#phi_{jets}",640,-3.2,3.2);
	h_AK8jet1_pt_Q_nj6 = new TH1D("AK8jet1_pt_Q_nj6",";p_{T, AK8jet1}",200,0,2000);
	h_AK8jet1_eta_Q_nj6 = new TH1D("AK8jet1_eta_Q_nj6",";#eta_{AK8jet1}",480,-2.4,2.4);
	h_AK8jet1_phi_Q_nj6 = new TH1D("AK8jet1_phi_Q_nj6",";#phi_{AK8jet1}",640,-3.2,3.2);
	h_AK8jet1_tau21_Q_nj6 = new TH1D("AK8jet1_tau21_Q_nj6",";tau_{21, AK8jet1}",20,0,1);
	h_AK8jet1_tau32_Q_nj6 = new TH1D("AK8jet1_tau32_Q_nj6",";tau_{32, AK8jet1}",20,0,1);
	h_AK8jets_pt_Q_nj6 = new TH1D("AK8jets_pt_Q_nj6",";p_{T, AK8jets}",200,0,2000);
	h_AK8jets_eta_Q_nj6 = new TH1D("AK8jets_eta_Q_nj6",";#eta_{AK8jets}",480,-2.4,2.4);
	h_AK8jets_phi_Q_nj6 = new TH1D("AK8jets_phi_Q_nj6",";#phi_{AK8jets}",640,-3.2,3.2);
	h_AK8jets_msoftdrop_Q_nj6 = new TH1D("AK8jets_msoftdrop_Q_nj6",";p_{mass, AK8jets}",100,0,500);
	h_AK8jets_tau21_Q_nj6 = new TH1D("AK8jets_tau21_Q_nj6",";tau_{21, AK8jets}",20,0,1);
	h_AK8jets_tau32_Q_nj6 = new TH1D("AK8jets_tau32_Q_nj6",";tau_{32, AK8jets}",20,0,1);
#if TOP == 0
	h_Wjets_pt_Q_nj6 = new TH1D("Wjets_pt_Q_nj6",";p_{T, Boostjets}",200,0,2000);
	h_Wjets_eta_Q_nj6 = new TH1D("Wjets_eta_Q_nj6",";#eta_{Boostjets}",480,-2.4,2.4);
	h_Wjets_phi_Q_nj6 = new TH1D("Wjets_phi_Q_nj6",";#phi_{Boostjets}",640,-3.2,3.2);
	h_Wjets_tau21_Q_nj6 = new TH1D("Wjets_tau21_Q_nj6",";tau_{21, Boostjets}",20,0,1);
	h_Wjets_tau32_Q_nj6 = new TH1D("Wjets_tau32_Q_nj6",";tau_{21, Boostjets}",20,0,1);
#else
	h_Topjets_pt_Q_nj6 = new TH1D("Topjets_pt_Q_nj6",";p_{T, Boostjets}",200,0,2000);
	h_Topjets_eta_Q_nj6 = new TH1D("Topjets_eta_Q_nj6",";#eta_{Boostjets}",480,-2.4,2.4);
	h_Topjets_phi_Q_nj6 = new TH1D("Topjets_phi_Q_nj6",";#phi_{Boostjets}",640,-3.2,3.2);
	h_Topjets_tau21_Q_nj6 = new TH1D("Topjets_tau21_Q_nj6",";tau_{21, Boostjets}",20,0,1);
	h_Topjets_tau32_Q_nj6 = new TH1D("Topjets_tau32_Q_nj6",";tau_{32, Boostjets}",20,0,1);
#endif

	h_jet1_pt_q = new TH1D("jet1_pt_q",";p_{T, jet1}",200,0,2000);
	h_jet1_eta_q = new TH1D("jet1_eta_q",";#eta_{jet1}",480,-2.4,2.4);
	h_jet1_phi_q = new TH1D("jet1_phi_q",";#phi_{jet1}",640,-3.2,3.2);
	h_jets_pt_q = new TH1D("jets_pt_q",";p_{T, jets}",200,0,2000);
	h_jets_eta_q = new TH1D("jets_eta_q",";#eta_{jets}",480,-2.4,2.4);
	h_jets_phi_q = new TH1D("jets_phi_q",";#phi_{jets}",640,-3.2,3.2);
	h_AK8jet1_pt_q = new TH1D("AK8jet1_pt_q",";p_{T, AK8jet1}",200,0,2000);
	h_AK8jet1_eta_q = new TH1D("AK8jet1_eta_q",";#eta_{AK8jet1}",480,-2.4,2.4);
	h_AK8jet1_phi_q = new TH1D("AK8jet1_phi_q",";#phi_{AK8jet1}",640,-3.2,3.2);
	h_AK8jet1_tau21_q = new TH1D("AK8jet1_tau21_q",";tau_{21, AK8jet1}",20,0,1);
	h_AK8jet1_tau32_q = new TH1D("AK8jet1_tau32_q",";tau_{32, AK8jet1}",20,0,1);
	h_AK8jets_pt_q = new TH1D("AK8jets_pt_q",";p_{T, AK8jets}",200,0,2000);
	h_AK8jets_eta_q = new TH1D("AK8jets_eta_q",";#eta_{AK8jets}",480,-2.4,2.4);
	h_AK8jets_phi_q = new TH1D("AK8jets_phi_q",";#phi_{AK8jets}",640,-3.2,3.2);
	h_AK8jets_msoftdrop_q = new TH1D("AK8jets_msoftdrop_q",";p_{mass, AK8jets}",100,0,500);
	h_AK8jets_tau21_q = new TH1D("AK8jets_tau21_q",";tau_{21, AK8jets}",20,0,1);
	h_AK8jets_tau32_q = new TH1D("AK8jets_tau32_q",";tau_{32, AK8jets}",20,0,1);
#if TOP == 0
	h_Wjets_pt_q = new TH1D("Wjets_pt_q",";p_{T, Boostjets}",200,0,2000);
	h_Wjets_eta_q = new TH1D("Wjets_eta_q",";#eta_{Boostjets}",480,-2.4,2.4);
	h_Wjets_phi_q = new TH1D("Wjets_phi_q",";#phi_{Boostjets}",640,-3.2,3.2);
	h_Wjets_tau21_q = new TH1D("Wjets_tau21_q",";tau_{21, Boostjets}",20,0,1);
	h_Wjets_tau32_q = new TH1D("Wjets_tau32_q",";tau_{21, Boostjets}",20,0,1);
#else
	h_Topjets_pt_q = new TH1D("Topjets_pt_q",";p_{T, Boostjets}",200,0,2000);
	h_Topjets_eta_q = new TH1D("Topjets_eta_q",";#eta_{Boostjets}",480,-2.4,2.4);
	h_Topjets_phi_q = new TH1D("Topjets_phi_q",";#phi_{Boostjets}",640,-3.2,3.2);
	h_Topjets_tau21_q = new TH1D("Topjets_tau21_q",";tau_{21, Boostjets}",20,0,1);
	h_Topjets_tau32_q = new TH1D("Topjets_tau32_q",";tau_{32, Boostjets}",20,0,1);
#endif
	h_jet1_pt_q_nj45 = new TH1D("jet1_pt_q_nj45",";p_{T, jet1}",200,0,2000);
	h_jet1_eta_q_nj45 = new TH1D("jet1_eta_q_nj45",";#eta_{jet1}",480,-2.4,2.4);
	h_jet1_phi_q_nj45 = new TH1D("jet1_phi_q_nj45",";#phi_{jet1}",640,-3.2,3.2);
	h_jets_pt_q_nj45 = new TH1D("jets_pt_q_nj45",";p_{T, jets}",200,0,2000);
	h_jets_eta_q_nj45 = new TH1D("jets_eta_q_nj45",";#eta_{jets}",480,-2.4,2.4);
	h_jets_phi_q_nj45 = new TH1D("jets_phi_q_nj45",";#phi_{jets}",640,-3.2,3.2);
	h_AK8jet1_pt_q_nj45 = new TH1D("AK8jet1_pt_q_nj45",";p_{T, AK8jet1}",200,0,2000);
	h_AK8jet1_eta_q_nj45 = new TH1D("AK8jet1_eta_q_nj45",";#eta_{AK8jet1}",480,-2.4,2.4);
	h_AK8jet1_phi_q_nj45 = new TH1D("AK8jet1_phi_q_nj45",";#phi_{AK8jet1}",640,-3.2,3.2);
	h_AK8jet1_tau21_q_nj45 = new TH1D("AK8jet1_tau21_q_nj45",";tau_{21, AK8jet1}",20,0,1);
	h_AK8jet1_tau32_q_nj45 = new TH1D("AK8jet1_tau32_q_nj45",";tau_{32, AK8jet1}",20,0,1);
	h_AK8jets_pt_q_nj45 = new TH1D("AK8jets_pt_q_nj45",";p_{T, AK8jets}",200,0,2000);
	h_AK8jets_eta_q_nj45 = new TH1D("AK8jets_eta_q_nj45",";#eta_{AK8jets}",480,-2.4,2.4);
	h_AK8jets_phi_q_nj45 = new TH1D("AK8jets_phi_q_nj45",";#phi_{AK8jets}",640,-3.2,3.2);
	h_AK8jets_msoftdrop_q_nj45 = new TH1D("AK8jets_msoftdrop_q_nj45",";p_{mass, AK8jets}",100,0,500);
	h_AK8jets_tau21_q_nj45 = new TH1D("AK8jets_tau21_q_nj45",";tau_{21, AK8jets}",20,0,1);
	h_AK8jets_tau32_q_nj45 = new TH1D("AK8jets_tau32_q_nj45",";tau_{32, AK8jets}",20,0,1);
#if TOP == 0
	h_Wjets_pt_q_nj45 = new TH1D("Wjets_pt_q_nj45",";p_{T, Boostjets}",200,0,2000);
	h_Wjets_eta_q_nj45 = new TH1D("Wjets_eta_q_nj45",";#eta_{Boostjets}",480,-2.4,2.4);
	h_Wjets_phi_q_nj45 = new TH1D("Wjets_phi_q_nj45",";#phi_{Boostjets}",640,-3.2,3.2);
	h_Wjets_tau21_q_nj45 = new TH1D("Wjets_tau21_q_nj45",";tau_{21, Boostjets}",20,0,1);
	h_Wjets_tau32_q_nj45 = new TH1D("Wjets_tau32_q_nj45",";tau_{21, Boostjets}",20,0,1);
#else
	h_Topjets_pt_q_nj45 = new TH1D("Topjets_pt_q_nj45",";p_{T, Boostjets}",200,0,2000);
	h_Topjets_eta_q_nj45 = new TH1D("Topjets_eta_q_nj45",";#eta_{Boostjets}",480,-2.4,2.4);
	h_Topjets_phi_q_nj45 = new TH1D("Topjets_phi_q_nj45",";#phi_{Boostjets}",640,-3.2,3.2);
	h_Topjets_tau21_q_nj45 = new TH1D("Topjets_tau21_q_nj45",";tau_{21, Boostjets}",20,0,1);
	h_Topjets_tau32_q_nj45 = new TH1D("Topjets_tau32_q_nj45",";tau_{32, Boostjets}",20,0,1);
#endif
	h_jet1_pt_q_nj6 = new TH1D("jet1_pt_q_nj6",";p_{T, jet1}",200,0,2000);
	h_jet1_eta_q_nj6 = new TH1D("jet1_eta_q_nj6",";#eta_{jet1}",480,-2.4,2.4);
	h_jet1_phi_q_nj6 = new TH1D("jet1_phi_q_nj6",";#phi_{jet1}",640,-3.2,3.2);
	h_jets_pt_q_nj6 = new TH1D("jets_pt_q_nj6",";p_{T, jets}",200,0,2000);
	h_jets_eta_q_nj6 = new TH1D("jets_eta_q_nj6",";#eta_{jets}",480,-2.4,2.4);
	h_jets_phi_q_nj6 = new TH1D("jets_phi_q_nj6",";#phi_{jets}",640,-3.2,3.2);
	h_AK8jet1_pt_q_nj6 = new TH1D("AK8jet1_pt_q_nj6",";p_{T, AK8jet1}",200,0,2000);
	h_AK8jet1_eta_q_nj6 = new TH1D("AK8jet1_eta_q_nj6",";#eta_{AK8jet1}",480,-2.4,2.4);
	h_AK8jet1_phi_q_nj6 = new TH1D("AK8jet1_phi_q_nj6",";#phi_{AK8jet1}",640,-3.2,3.2);
	h_AK8jet1_tau21_q_nj6 = new TH1D("AK8jet1_tau21_q_nj6",";tau_{21, AK8jet1}",20,0,1);
	h_AK8jet1_tau32_q_nj6 = new TH1D("AK8jet1_tau32_q_nj6",";tau_{32, AK8jet1}",20,0,1);
	h_AK8jets_pt_q_nj6 = new TH1D("AK8jets_pt_q_nj6",";p_{T, AK8jets}",200,0,2000);
	h_AK8jets_eta_q_nj6 = new TH1D("AK8jets_eta_q_nj6",";#eta_{AK8jets}",480,-2.4,2.4);
	h_AK8jets_phi_q_nj6 = new TH1D("AK8jets_phi_q_nj6",";#phi_{AK8jets}",640,-3.2,3.2);
	h_AK8jets_msoftdrop_q_nj6 = new TH1D("AK8jets_msoftdrop_q_nj6",";p_{mass, AK8jets}",100,0,500);
	h_AK8jets_tau21_q_nj6 = new TH1D("AK8jets_tau21_q_nj6",";tau_{21, AK8jets}",20,0,1);
	h_AK8jets_tau32_q_nj6 = new TH1D("AK8jets_tau32_q_nj6",";tau_{32, AK8jets}",20,0,1);
#if TOP == 0
	h_Wjets_pt_q_nj6 = new TH1D("Wjets_pt_q_nj6",";p_{T, Boostjets}",200,0,2000);
	h_Wjets_eta_q_nj6 = new TH1D("Wjets_eta_q_nj6",";#eta_{Boostjets}",480,-2.4,2.4);
	h_Wjets_phi_q_nj6 = new TH1D("Wjets_phi_q_nj6",";#phi_{Boostjets}",640,-3.2,3.2);
	h_Wjets_tau21_q_nj6 = new TH1D("Wjets_tau21_q_nj6",";tau_{21, Boostjets}",20,0,1);
	h_Wjets_tau32_q_nj6 = new TH1D("Wjets_tau32_q_nj6",";tau_{21, Boostjets}",20,0,1);
#else
	h_Topjets_pt_q_nj6 = new TH1D("Topjets_pt_q_nj6",";p_{T, Boostjets}",200,0,2000);
	h_Topjets_eta_q_nj6 = new TH1D("Topjets_eta_q_nj6",";#eta_{Boostjets}",480,-2.4,2.4);
	h_Topjets_phi_q_nj6 = new TH1D("Topjets_phi_q_nj6",";#phi_{Boostjets}",640,-3.2,3.2);
	h_Topjets_tau21_q_nj6 = new TH1D("Topjets_tau21_q_nj6",";tau_{21, Boostjets}",20,0,1);
	h_Topjets_tau32_q_nj6 = new TH1D("Topjets_tau32_q_nj6",";tau_{32, Boostjets}",20,0,1);
#endif

	h_jet1_pt_T = new TH1D("jet1_pt_T",";p_{T, jet1}",200,0,2000);
	h_jet1_eta_T = new TH1D("jet1_eta_T",";#eta_{jet1}",480,-2.4,2.4);
	h_jet1_phi_T = new TH1D("jet1_phi_T",";#phi_{jet1}",640,-3.2,3.2);
	h_jets_pt_T = new TH1D("jets_pt_T",";p_{T, jets}",200,0,2000);
	h_jets_eta_T = new TH1D("jets_eta_T",";#eta_{jets}",480,-2.4,2.4);
	h_jets_phi_T = new TH1D("jets_phi_T",";#phi_{jets}",640,-3.2,3.2);
	h_AK8jet1_pt_T = new TH1D("AK8jet1_pt_T",";p_{T, AK8jet1}",200,0,2000);
	h_AK8jet1_eta_T = new TH1D("AK8jet1_eta_T",";#eta_{AK8jet1}",480,-2.4,2.4);
	h_AK8jet1_phi_T = new TH1D("AK8jet1_phi_T",";#phi_{AK8jet1}",640,-3.2,3.2);
	h_AK8jet1_tau21_T = new TH1D("AK8jet1_tau21_T",";tau_{21, AK8jet1}",20,0,1);
	h_AK8jet1_tau32_T = new TH1D("AK8jet1_tau32_T",";tau_{32, AK8jet1}",20,0,1);
	h_AK8jets_pt_T = new TH1D("AK8jets_pt_T",";p_{T, AK8jets}",200,0,2000);
	h_AK8jets_eta_T = new TH1D("AK8jets_eta_T",";#eta_{AK8jets}",480,-2.4,2.4);
	h_AK8jets_phi_T = new TH1D("AK8jets_phi_T",";#phi_{AK8jets}",640,-3.2,3.2);
	h_AK8jets_msoftdrop_T = new TH1D("AK8jets_msoftdrop_T",";p_{mass, AK8jets}",100,0,500);
	h_AK8jets_tau21_T = new TH1D("AK8jets_tau21_T",";tau_{21, AK8jets}",20,0,1);
	h_AK8jets_tau32_T = new TH1D("AK8jets_tau32_T",";tau_{32, AK8jets}",20,0,1);
#if TOP == 0
	h_Wjets_pt_T = new TH1D("Wjets_pt_T",";p_{T, Boostjets}",200,0,2000);
	h_Wjets_eta_T = new TH1D("Wjets_eta_T",";#eta_{Boostjets}",480,-2.4,2.4);
	h_Wjets_phi_T = new TH1D("Wjets_phi_T",";#phi_{Boostjets}",640,-3.2,3.2);
	h_Wjets_tau21_T = new TH1D("Wjets_tau21_T",";tau_{21, Boostjets}",20,0,1);
	h_Wjets_tau32_T = new TH1D("Wjets_tau32_T",";tau_{21, Boostjets}",20,0,1);
#else
	h_Topjets_pt_T = new TH1D("Topjets_pt_T",";p_{T, Boostjets}",200,0,2000);
	h_Topjets_eta_T = new TH1D("Topjets_eta_T",";#eta_{Boostjets}",480,-2.4,2.4);
	h_Topjets_phi_T = new TH1D("Topjets_phi_T",";#phi_{Boostjets}",640,-3.2,3.2);
	h_Topjets_tau21_T = new TH1D("Topjets_tau21_T",";tau_{21, Boostjets}",20,0,1);
	h_Topjets_tau32_T = new TH1D("Topjets_tau32_T",";tau_{32, Boostjets}",20,0,1);
#endif
	h_jet1_pt_T_nj45 = new TH1D("jet1_pt_T_nj45",";p_{T, jet1}",200,0,2000);
	h_jet1_eta_T_nj45 = new TH1D("jet1_eta_T_nj45",";#eta_{jet1}",480,-2.4,2.4);
	h_jet1_phi_T_nj45 = new TH1D("jet1_phi_T_nj45",";#phi_{jet1}",640,-3.2,3.2);
	h_jets_pt_T_nj45 = new TH1D("jets_pt_T_nj45",";p_{T, jets}",200,0,2000);
	h_jets_eta_T_nj45 = new TH1D("jets_eta_T_nj45",";#eta_{jets}",480,-2.4,2.4);
	h_jets_phi_T_nj45 = new TH1D("jets_phi_T_nj45",";#phi_{jets}",640,-3.2,3.2);
	h_AK8jet1_pt_T_nj45 = new TH1D("AK8jet1_pt_T_nj45",";p_{T, AK8jet1}",200,0,2000);
	h_AK8jet1_eta_T_nj45 = new TH1D("AK8jet1_eta_T_nj45",";#eta_{AK8jet1}",480,-2.4,2.4);
	h_AK8jet1_phi_T_nj45 = new TH1D("AK8jet1_phi_T_nj45",";#phi_{AK8jet1}",640,-3.2,3.2);
	h_AK8jet1_tau21_T_nj45 = new TH1D("AK8jet1_tau21_T_nj45",";tau_{21, AK8jet1}",20,0,1);
	h_AK8jet1_tau32_T_nj45 = new TH1D("AK8jet1_tau32_T_nj45",";tau_{32, AK8jet1}",20,0,1);
	h_AK8jets_pt_T_nj45 = new TH1D("AK8jets_pt_T_nj45",";p_{T, AK8jets}",200,0,2000);
	h_AK8jets_eta_T_nj45 = new TH1D("AK8jets_eta_T_nj45",";#eta_{AK8jets}",480,-2.4,2.4);
	h_AK8jets_phi_T_nj45 = new TH1D("AK8jets_phi_T_nj45",";#phi_{AK8jets}",640,-3.2,3.2);
	h_AK8jets_msoftdrop_T_nj45 = new TH1D("AK8jets_msoftdrop_T_nj45",";p_{mass, AK8jets}",100,0,500);
	h_AK8jets_tau21_T_nj45 = new TH1D("AK8jets_tau21_T_nj45",";tau_{21, AK8jets}",20,0,1);
	h_AK8jets_tau32_T_nj45 = new TH1D("AK8jets_tau32_T_nj45",";tau_{32, AK8jets}",20,0,1);
#if TOP == 0
	h_Wjets_pt_T_nj45 = new TH1D("Wjets_pt_T_nj45",";p_{T, Boostjets}",200,0,2000);
	h_Wjets_eta_T_nj45 = new TH1D("Wjets_eta_T_nj45",";#eta_{Boostjets}",480,-2.4,2.4);
	h_Wjets_phi_T_nj45 = new TH1D("Wjets_phi_T_nj45",";#phi_{Boostjets}",640,-3.2,3.2);
	h_Wjets_tau21_T_nj45 = new TH1D("Wjets_tau21_T_nj45",";tau_{21, Boostjets}",20,0,1);
	h_Wjets_tau32_T_nj45 = new TH1D("Wjets_tau32_T_nj45",";tau_{21, Boostjets}",20,0,1);
#else
	h_Topjets_pt_T_nj45 = new TH1D("Topjets_pt_T_nj45",";p_{T, Boostjets}",200,0,2000);
	h_Topjets_eta_T_nj45 = new TH1D("Topjets_eta_T_nj45",";#eta_{Boostjets}",480,-2.4,2.4);
	h_Topjets_phi_T_nj45 = new TH1D("Topjets_phi_T_nj45",";#phi_{Boostjets}",640,-3.2,3.2);
	h_Topjets_tau21_T_nj45 = new TH1D("Topjets_tau21_T_nj45",";tau_{21, Boostjets}",20,0,1);
	h_Topjets_tau32_T_nj45 = new TH1D("Topjets_tau32_T_nj45",";tau_{32, Boostjets}",20,0,1);
#endif
	h_jet1_pt_T_nj6 = new TH1D("jet1_pt_T_nj6",";p_{T, jet1}",200,0,2000);
	h_jet1_eta_T_nj6 = new TH1D("jet1_eta_T_nj6",";#eta_{jet1}",480,-2.4,2.4);
	h_jet1_phi_T_nj6 = new TH1D("jet1_phi_T_nj6",";#phi_{jet1}",640,-3.2,3.2);
	h_jets_pt_T_nj6 = new TH1D("jets_pt_T_nj6",";p_{T, jets}",200,0,2000);
	h_jets_eta_T_nj6 = new TH1D("jets_eta_T_nj6",";#eta_{jets}",480,-2.4,2.4);
	h_jets_phi_T_nj6 = new TH1D("jets_phi_T_nj6",";#phi_{jets}",640,-3.2,3.2);
	h_AK8jet1_pt_T_nj6 = new TH1D("AK8jet1_pt_T_nj6",";p_{T, AK8jet1}",200,0,2000);
	h_AK8jet1_eta_T_nj6 = new TH1D("AK8jet1_eta_T_nj6",";#eta_{AK8jet1}",480,-2.4,2.4);
	h_AK8jet1_phi_T_nj6 = new TH1D("AK8jet1_phi_T_nj6",";#phi_{AK8jet1}",640,-3.2,3.2);
	h_AK8jet1_tau21_T_nj6 = new TH1D("AK8jet1_tau21_T_nj6",";tau_{21, AK8jet1}",20,0,1);
	h_AK8jet1_tau32_T_nj6 = new TH1D("AK8jet1_tau32_T_nj6",";tau_{32, AK8jet1}",20,0,1);
	h_AK8jets_pt_T_nj6 = new TH1D("AK8jets_pt_T_nj6",";p_{T, AK8jets}",200,0,2000);
	h_AK8jets_eta_T_nj6 = new TH1D("AK8jets_eta_T_nj6",";#eta_{AK8jets}",480,-2.4,2.4);
	h_AK8jets_phi_T_nj6 = new TH1D("AK8jets_phi_T_nj6",";#phi_{AK8jets}",640,-3.2,3.2);
	h_AK8jets_msoftdrop_T_nj6 = new TH1D("AK8jets_msoftdrop_T_nj6",";p_{mass, AK8jets}",100,0,500);
	h_AK8jets_tau21_T_nj6 = new TH1D("AK8jets_tau21_T_nj6",";tau_{21, AK8jets}",20,0,1);
	h_AK8jets_tau32_T_nj6 = new TH1D("AK8jets_tau32_T_nj6",";tau_{32, AK8jets}",20,0,1);
#if TOP == 0
	h_Wjets_pt_T_nj6 = new TH1D("Wjets_pt_T_nj6",";p_{T, Boostjets}",200,0,2000);
	h_Wjets_eta_T_nj6 = new TH1D("Wjets_eta_T_nj6",";#eta_{Boostjets}",480,-2.4,2.4);
	h_Wjets_phi_T_nj6 = new TH1D("Wjets_phi_T_nj6",";#phi_{Boostjets}",640,-3.2,3.2);
	h_Wjets_tau21_T_nj6 = new TH1D("Wjets_tau21_T_nj6",";tau_{21, Boostjets}",20,0,1);
	h_Wjets_tau32_T_nj6 = new TH1D("Wjets_tau32_T_nj6",";tau_{21, Boostjets}",20,0,1);
#else
	h_Topjets_pt_T_nj6 = new TH1D("Topjets_pt_T_nj6",";p_{T, Boostjets}",200,0,2000);
	h_Topjets_eta_T_nj6 = new TH1D("Topjets_eta_T_nj6",";#eta_{Boostjets}",480,-2.4,2.4);
	h_Topjets_phi_T_nj6 = new TH1D("Topjets_phi_T_nj6",";#phi_{Boostjets}",640,-3.2,3.2);
	h_Topjets_tau21_T_nj6 = new TH1D("Topjets_tau21_T_nj6",";tau_{21, Boostjets}",20,0,1);
	h_Topjets_tau32_T_nj6 = new TH1D("Topjets_tau32_T_nj6",";tau_{32, Boostjets}",20,0,1);
#endif

	h_jet1_pt_W = new TH1D("jet1_pt_W",";p_{T, jet1}",200,0,2000);
	h_jet1_eta_W = new TH1D("jet1_eta_W",";#eta_{jet1}",480,-2.4,2.4);
	h_jet1_phi_W = new TH1D("jet1_phi_W",";#phi_{jet1}",640,-3.2,3.2);
	h_jets_pt_W = new TH1D("jets_pt_W",";p_{T, jets}",200,0,2000);
	h_jets_eta_W = new TH1D("jets_eta_W",";#eta_{jets}",480,-2.4,2.4);
	h_jets_phi_W = new TH1D("jets_phi_W",";#phi_{jets}",640,-3.2,3.2);
	h_AK8jet1_pt_W = new TH1D("AK8jet1_pt_W",";p_{T, AK8jet1}",200,0,2000);
	h_AK8jet1_eta_W = new TH1D("AK8jet1_eta_W",";#eta_{AK8jet1}",480,-2.4,2.4);
	h_AK8jet1_phi_W = new TH1D("AK8jet1_phi_W",";#phi_{AK8jet1}",640,-3.2,3.2);
	h_AK8jet1_tau21_W = new TH1D("AK8jet1_tau21_W",";tau_{21, AK8jet1}",20,0,1);
	h_AK8jet1_tau32_W = new TH1D("AK8jet1_tau32_W",";tau_{32, AK8jet1}",20,0,1);
	h_AK8jets_pt_W = new TH1D("AK8jets_pt_W",";p_{T, AK8jets}",200,0,2000);
	h_AK8jets_eta_W = new TH1D("AK8jets_eta_W",";#eta_{AK8jets}",480,-2.4,2.4);
	h_AK8jets_phi_W = new TH1D("AK8jets_phi_W",";#phi_{AK8jets}",640,-3.2,3.2);
	h_AK8jets_msoftdrop_W = new TH1D("AK8jets_msoftdrop_W",";p_{mass, AK8jets}",100,0,500);
	h_AK8jets_tau21_W = new TH1D("AK8jets_tau21_W",";tau_{21, AK8jets}",20,0,1);
	h_AK8jets_tau32_W = new TH1D("AK8jets_tau32_W",";tau_{32, AK8jets}",20,0,1);
#if TOP == 0
	h_Wjets_pt_W = new TH1D("Wjets_pt_W",";p_{T, Boostjets}",200,0,2000);
	h_Wjets_eta_W = new TH1D("Wjets_eta_W",";#eta_{Boostjets}",480,-2.4,2.4);
	h_Wjets_phi_W = new TH1D("Wjets_phi_W",";#phi_{Boostjets}",640,-3.2,3.2);
	h_Wjets_tau21_W = new TH1D("Wjets_tau21_W",";tau_{21, Boostjets}",20,0,1);
	h_Wjets_tau32_W = new TH1D("Wjets_tau32_W",";tau_{21, Boostjets}",20,0,1);
#else
	h_Topjets_pt_W = new TH1D("Topjets_pt_W",";p_{T, Boostjets}",200,0,2000);
	h_Topjets_eta_W = new TH1D("Topjets_eta_W",";#eta_{Boostjets}",480,-2.4,2.4);
	h_Topjets_phi_W = new TH1D("Topjets_phi_W",";#phi_{Boostjets}",640,-3.2,3.2);
	h_Topjets_tau21_W = new TH1D("Topjets_tau21_W",";tau_{21, Boostjets}",20,0,1);
	h_Topjets_tau32_W = new TH1D("Topjets_tau32_W",";tau_{32, Boostjets}",20,0,1);
#endif
	h_jet1_pt_W_nj45 = new TH1D("jet1_pt_W_nj45",";p_{T, jet1}",200,0,2000);
	h_jet1_eta_W_nj45 = new TH1D("jet1_eta_W_nj45",";#eta_{jet1}",480,-2.4,2.4);
	h_jet1_phi_W_nj45 = new TH1D("jet1_phi_W_nj45",";#phi_{jet1}",640,-3.2,3.2);
	h_jets_pt_W_nj45 = new TH1D("jets_pt_W_nj45",";p_{T, jets}",200,0,2000);
	h_jets_eta_W_nj45 = new TH1D("jets_eta_W_nj45",";#eta_{jets}",480,-2.4,2.4);
	h_jets_phi_W_nj45 = new TH1D("jets_phi_W_nj45",";#phi_{jets}",640,-3.2,3.2);
	h_AK8jet1_pt_W_nj45 = new TH1D("AK8jet1_pt_W_nj45",";p_{T, AK8jet1}",200,0,2000);
	h_AK8jet1_eta_W_nj45 = new TH1D("AK8jet1_eta_W_nj45",";#eta_{AK8jet1}",480,-2.4,2.4);
	h_AK8jet1_phi_W_nj45 = new TH1D("AK8jet1_phi_W_nj45",";#phi_{AK8jet1}",640,-3.2,3.2);
	h_AK8jet1_tau21_W_nj45 = new TH1D("AK8jet1_tau21_W_nj45",";tau_{21, AK8jet1}",20,0,1);
	h_AK8jet1_tau32_W_nj45 = new TH1D("AK8jet1_tau32_W_nj45",";tau_{32, AK8jet1}",20,0,1);
	h_AK8jets_pt_W_nj45 = new TH1D("AK8jets_pt_W_nj45",";p_{T, AK8jets}",200,0,2000);
	h_AK8jets_eta_W_nj45 = new TH1D("AK8jets_eta_W_nj45",";#eta_{AK8jets}",480,-2.4,2.4);
	h_AK8jets_phi_W_nj45 = new TH1D("AK8jets_phi_W_nj45",";#phi_{AK8jets}",640,-3.2,3.2);
	h_AK8jets_msoftdrop_W_nj45 = new TH1D("AK8jets_msoftdrop_W_nj45",";p_{mass, AK8jets}",100,0,500);
	h_AK8jets_tau21_W_nj45 = new TH1D("AK8jets_tau21_W_nj45",";tau_{21, AK8jets}",20,0,1);
	h_AK8jets_tau32_W_nj45 = new TH1D("AK8jets_tau32_W_nj45",";tau_{32, AK8jets}",20,0,1);
#if TOP == 0
	h_Wjets_pt_W_nj45 = new TH1D("Wjets_pt_W_nj45",";p_{T, Boostjets}",200,0,2000);
	h_Wjets_eta_W_nj45 = new TH1D("Wjets_eta_W_nj45",";#eta_{Boostjets}",480,-2.4,2.4);
	h_Wjets_phi_W_nj45 = new TH1D("Wjets_phi_W_nj45",";#phi_{Boostjets}",640,-3.2,3.2);
	h_Wjets_tau21_W_nj45 = new TH1D("Wjets_tau21_W_nj45",";tau_{21, Boostjets}",20,0,1);
	h_Wjets_tau32_W_nj45 = new TH1D("Wjets_tau32_W_nj45",";tau_{21, Boostjets}",20,0,1);
#else
	h_Topjets_pt_W_nj45 = new TH1D("Topjets_pt_W_nj45",";p_{T, Boostjets}",200,0,2000);
	h_Topjets_eta_W_nj45 = new TH1D("Topjets_eta_W_nj45",";#eta_{Boostjets}",480,-2.4,2.4);
	h_Topjets_phi_W_nj45 = new TH1D("Topjets_phi_W_nj45",";#phi_{Boostjets}",640,-3.2,3.2);
	h_Topjets_tau21_W_nj45 = new TH1D("Topjets_tau21_W_nj45",";tau_{21, Boostjets}",20,0,1);
	h_Topjets_tau32_W_nj45 = new TH1D("Topjets_tau32_W_nj45",";tau_{32, Boostjets}",20,0,1);
#endif
	h_jet1_pt_W_nj6 = new TH1D("jet1_pt_W_nj6",";p_{T, jet1}",200,0,2000);
	h_jet1_eta_W_nj6 = new TH1D("jet1_eta_W_nj6",";#eta_{jet1}",480,-2.4,2.4);
	h_jet1_phi_W_nj6 = new TH1D("jet1_phi_W_nj6",";#phi_{jet1}",640,-3.2,3.2);
	h_jets_pt_W_nj6 = new TH1D("jets_pt_W_nj6",";p_{T, jets}",200,0,2000);
	h_jets_eta_W_nj6 = new TH1D("jets_eta_W_nj6",";#eta_{jets}",480,-2.4,2.4);
	h_jets_phi_W_nj6 = new TH1D("jets_phi_W_nj6",";#phi_{jets}",640,-3.2,3.2);
	h_AK8jet1_pt_W_nj6 = new TH1D("AK8jet1_pt_W_nj6",";p_{T, AK8jet1}",200,0,2000);
	h_AK8jet1_eta_W_nj6 = new TH1D("AK8jet1_eta_W_nj6",";#eta_{AK8jet1}",480,-2.4,2.4);
	h_AK8jet1_phi_W_nj6 = new TH1D("AK8jet1_phi_W_nj6",";#phi_{AK8jet1}",640,-3.2,3.2);
	h_AK8jet1_tau21_W_nj6 = new TH1D("AK8jet1_tau21_W_nj6",";tau_{21, AK8jet1}",20,0,1);
	h_AK8jet1_tau32_W_nj6 = new TH1D("AK8jet1_tau32_W_nj6",";tau_{32, AK8jet1}",20,0,1);
	h_AK8jets_pt_W_nj6 = new TH1D("AK8jets_pt_W_nj6",";p_{T, AK8jets}",200,0,2000);
	h_AK8jets_eta_W_nj6 = new TH1D("AK8jets_eta_W_nj6",";#eta_{AK8jets}",480,-2.4,2.4);
	h_AK8jets_phi_W_nj6 = new TH1D("AK8jets_phi_W_nj6",";#phi_{AK8jets}",640,-3.2,3.2);
	h_AK8jets_msoftdrop_W_nj6 = new TH1D("AK8jets_msoftdrop_W_nj6",";p_{mass, AK8jets}",100,0,500);
	h_AK8jets_tau21_W_nj6 = new TH1D("AK8jets_tau21_W_nj6",";tau_{21, AK8jets}",20,0,1);
	h_AK8jets_tau32_W_nj6 = new TH1D("AK8jets_tau32_W_nj6",";tau_{32, AK8jets}",20,0,1);
#if TOP == 0
	h_Wjets_pt_W_nj6 = new TH1D("Wjets_pt_W_nj6",";p_{T, Boostjets}",200,0,2000);
	h_Wjets_eta_W_nj6 = new TH1D("Wjets_eta_W_nj6",";#eta_{Boostjets}",480,-2.4,2.4);
	h_Wjets_phi_W_nj6 = new TH1D("Wjets_phi_W_nj6",";#phi_{Boostjets}",640,-3.2,3.2);
	h_Wjets_tau21_W_nj6 = new TH1D("Wjets_tau21_W_nj6",";tau_{21, Boostjets}",20,0,1);
	h_Wjets_tau32_W_nj6 = new TH1D("Wjets_tau32_W_nj6",";tau_{21, Boostjets}",20,0,1);
#else
	h_Topjets_pt_W_nj6 = new TH1D("Topjets_pt_W_nj6",";p_{T, Boostjets}",200,0,2000);
	h_Topjets_eta_W_nj6 = new TH1D("Topjets_eta_W_nj6",";#eta_{Boostjets}",480,-2.4,2.4);
	h_Topjets_phi_W_nj6 = new TH1D("Topjets_phi_W_nj6",";#phi_{Boostjets}",640,-3.2,3.2);
	h_Topjets_tau21_W_nj6 = new TH1D("Topjets_tau21_W_nj6",";tau_{21, Boostjets}",20,0,1);
	h_Topjets_tau32_W_nj6 = new TH1D("Topjets_tau32_W_nj6",";tau_{32, Boostjets}",20,0,1);
#endif

	h_jet1_pt_L = new TH1D("jet1_pt_L",";p_{T, jet1}",200,0,2000);
	h_jet1_eta_L = new TH1D("jet1_eta_L",";#eta_{jet1}",480,-2.4,2.4);
	h_jet1_phi_L = new TH1D("jet1_phi_L",";#phi_{jet1}",640,-3.2,3.2);
	h_jets_pt_L = new TH1D("jets_pt_L",";p_{T, jets}",200,0,2000);
	h_jets_eta_L = new TH1D("jets_eta_L",";#eta_{jets}",480,-2.4,2.4);
	h_jets_phi_L = new TH1D("jets_phi_L",";#phi_{jets}",640,-3.2,3.2);
	h_AK8jet1_pt_L = new TH1D("AK8jet1_pt_L",";p_{T, AK8jet1}",200,0,2000);
	h_AK8jet1_eta_L = new TH1D("AK8jet1_eta_L",";#eta_{AK8jet1}",480,-2.4,2.4);
	h_AK8jet1_phi_L = new TH1D("AK8jet1_phi_L",";#phi_{AK8jet1}",640,-3.2,3.2);
	h_AK8jet1_tau21_L = new TH1D("AK8jet1_tau21_L",";tau_{21, AK8jet1}",20,0,1);
	h_AK8jet1_tau32_L = new TH1D("AK8jet1_tau32_L",";tau_{32, AK8jet1}",20,0,1);
	h_AK8jets_pt_L = new TH1D("AK8jets_pt_L",";p_{T, AK8jets}",200,0,2000);
	h_AK8jets_eta_L = new TH1D("AK8jets_eta_L",";#eta_{AK8jets}",480,-2.4,2.4);
	h_AK8jets_phi_L = new TH1D("AK8jets_phi_L",";#phi_{AK8jets}",640,-3.2,3.2);
	h_AK8jets_msoftdrop_L = new TH1D("AK8jets_msoftdrop_L",";p_{mass, AK8jets}",100,0,500);
	h_AK8jets_tau21_L = new TH1D("AK8jets_tau21_L",";tau_{21, AK8jets}",20,0,1);
	h_AK8jets_tau32_L = new TH1D("AK8jets_tau32_L",";tau_{32, AK8jets}",20,0,1);
#if TOP == 0
	h_Wjets_pt_L = new TH1D("Wjets_pt_L",";p_{T, Boostjets}",200,0,2000);
	h_Wjets_eta_L = new TH1D("Wjets_eta_L",";#eta_{Boostjets}",480,-2.4,2.4);
	h_Wjets_phi_L = new TH1D("Wjets_phi_L",";#phi_{Boostjets}",640,-3.2,3.2);
	h_Wjets_tau21_L = new TH1D("Wjets_tau21_L",";tau_{21, Boostjets}",20,0,1);
	h_Wjets_tau32_L = new TH1D("Wjets_tau32_L",";tau_{21, Boostjets}",20,0,1);
#else
	h_Topjets_pt_L = new TH1D("Topjets_pt_L",";p_{T, Boostjets}",200,0,2000);
	h_Topjets_eta_L = new TH1D("Topjets_eta_L",";#eta_{Boostjets}",480,-2.4,2.4);
	h_Topjets_phi_L = new TH1D("Topjets_phi_L",";#phi_{Boostjets}",640,-3.2,3.2);
	h_Topjets_tau21_L = new TH1D("Topjets_tau21_L",";tau_{21, Boostjets}",20,0,1);
	h_Topjets_tau32_L = new TH1D("Topjets_tau32_L",";tau_{32, Boostjets}",20,0,1);
#endif
	h_jet1_pt_L_nj45 = new TH1D("jet1_pt_L_nj45",";p_{T, jet1}",200,0,2000);
	h_jet1_eta_L_nj45 = new TH1D("jet1_eta_L_nj45",";#eta_{jet1}",480,-2.4,2.4);
	h_jet1_phi_L_nj45 = new TH1D("jet1_phi_L_nj45",";#phi_{jet1}",640,-3.2,3.2);
	h_jets_pt_L_nj45 = new TH1D("jets_pt_L_nj45",";p_{T, jets}",200,0,2000);
	h_jets_eta_L_nj45 = new TH1D("jets_eta_L_nj45",";#eta_{jets}",480,-2.4,2.4);
	h_jets_phi_L_nj45 = new TH1D("jets_phi_L_nj45",";#phi_{jets}",640,-3.2,3.2);
	h_AK8jet1_pt_L_nj45 = new TH1D("AK8jet1_pt_L_nj45",";p_{T, AK8jet1}",200,0,2000);
	h_AK8jet1_eta_L_nj45 = new TH1D("AK8jet1_eta_L_nj45",";#eta_{AK8jet1}",480,-2.4,2.4);
	h_AK8jet1_phi_L_nj45 = new TH1D("AK8jet1_phi_L_nj45",";#phi_{AK8jet1}",640,-3.2,3.2);
	h_AK8jet1_tau21_L_nj45 = new TH1D("AK8jet1_tau21_L_nj45",";tau_{21, AK8jet1}",20,0,1);
	h_AK8jet1_tau32_L_nj45 = new TH1D("AK8jet1_tau32_L_nj45",";tau_{32, AK8jet1}",20,0,1);
	h_AK8jets_pt_L_nj45 = new TH1D("AK8jets_pt_L_nj45",";p_{T, AK8jets}",200,0,2000);
	h_AK8jets_eta_L_nj45 = new TH1D("AK8jets_eta_L_nj45",";#eta_{AK8jets}",480,-2.4,2.4);
	h_AK8jets_phi_L_nj45 = new TH1D("AK8jets_phi_L_nj45",";#phi_{AK8jets}",640,-3.2,3.2);
	h_AK8jets_msoftdrop_L_nj45 = new TH1D("AK8jets_msoftdrop_L_nj45",";p_{mass, AK8jets}",100,0,500);
	h_AK8jets_tau21_L_nj45 = new TH1D("AK8jets_tau21_L_nj45",";tau_{21, AK8jets}",20,0,1);
	h_AK8jets_tau32_L_nj45 = new TH1D("AK8jets_tau32_L_nj45",";tau_{32, AK8jets}",20,0,1);
#if TOP == 0
	h_Wjets_pt_L_nj45 = new TH1D("Wjets_pt_L_nj45",";p_{T, Boostjets}",200,0,2000);
	h_Wjets_eta_L_nj45 = new TH1D("Wjets_eta_L_nj45",";#eta_{Boostjets}",480,-2.4,2.4);
	h_Wjets_phi_L_nj45 = new TH1D("Wjets_phi_L_nj45",";#phi_{Boostjets}",640,-3.2,3.2);
	h_Wjets_tau21_L_nj45 = new TH1D("Wjets_tau21_L_nj45",";tau_{21, Boostjets}",20,0,1);
	h_Wjets_tau32_L_nj45 = new TH1D("Wjets_tau32_L_nj45",";tau_{21, Boostjets}",20,0,1);
#else
	h_Topjets_pt_L_nj45 = new TH1D("Topjets_pt_L_nj45",";p_{T, Boostjets}",200,0,2000);
	h_Topjets_eta_L_nj45 = new TH1D("Topjets_eta_L_nj45",";#eta_{Boostjets}",480,-2.4,2.4);
	h_Topjets_phi_L_nj45 = new TH1D("Topjets_phi_L_nj45",";#phi_{Boostjets}",640,-3.2,3.2);
	h_Topjets_tau21_L_nj45 = new TH1D("Topjets_tau21_L_nj45",";tau_{21, Boostjets}",20,0,1);
	h_Topjets_tau32_L_nj45 = new TH1D("Topjets_tau32_L_nj45",";tau_{32, Boostjets}",20,0,1);
#endif
	h_jet1_pt_L_nj6 = new TH1D("jet1_pt_L_nj6",";p_{T, jet1}",200,0,2000);
	h_jet1_eta_L_nj6 = new TH1D("jet1_eta_L_nj6",";#eta_{jet1}",480,-2.4,2.4);
	h_jet1_phi_L_nj6 = new TH1D("jet1_phi_L_nj6",";#phi_{jet1}",640,-3.2,3.2);
	h_jets_pt_L_nj6 = new TH1D("jets_pt_L_nj6",";p_{T, jets}",200,0,2000);
	h_jets_eta_L_nj6 = new TH1D("jets_eta_L_nj6",";#eta_{jets}",480,-2.4,2.4);
	h_jets_phi_L_nj6 = new TH1D("jets_phi_L_nj6",";#phi_{jets}",640,-3.2,3.2);
	h_AK8jet1_pt_L_nj6 = new TH1D("AK8jet1_pt_L_nj6",";p_{T, AK8jet1}",200,0,2000);
	h_AK8jet1_eta_L_nj6 = new TH1D("AK8jet1_eta_L_nj6",";#eta_{AK8jet1}",480,-2.4,2.4);
	h_AK8jet1_phi_L_nj6 = new TH1D("AK8jet1_phi_L_nj6",";#phi_{AK8jet1}",640,-3.2,3.2);
	h_AK8jet1_tau21_L_nj6 = new TH1D("AK8jet1_tau21_L_nj6",";tau_{21, AK8jet1}",20,0,1);
	h_AK8jet1_tau32_L_nj6 = new TH1D("AK8jet1_tau32_L_nj6",";tau_{32, AK8jet1}",20,0,1);
	h_AK8jets_pt_L_nj6 = new TH1D("AK8jets_pt_L_nj6",";p_{T, AK8jets}",200,0,2000);
	h_AK8jets_eta_L_nj6 = new TH1D("AK8jets_eta_L_nj6",";#eta_{AK8jets}",480,-2.4,2.4);
	h_AK8jets_phi_L_nj6 = new TH1D("AK8jets_phi_L_nj6",";#phi_{AK8jets}",640,-3.2,3.2);
	h_AK8jets_msoftdrop_L_nj6 = new TH1D("AK8jets_msoftdrop_L_nj6",";p_{mass, AK8jets}",100,0,500);
	h_AK8jets_tau21_L_nj6 = new TH1D("AK8jets_tau21_L_nj6",";tau_{21, AK8jets}",20,0,1);
	h_AK8jets_tau32_L_nj6 = new TH1D("AK8jets_tau32_L_nj6",";tau_{32, AK8jets}",20,0,1);
#if TOP == 0
	h_Wjets_pt_L_nj6 = new TH1D("Wjets_pt_L_nj6",";p_{T, Boostjets}",200,0,2000);
	h_Wjets_eta_L_nj6 = new TH1D("Wjets_eta_L_nj6",";#eta_{Boostjets}",480,-2.4,2.4);
	h_Wjets_phi_L_nj6 = new TH1D("Wjets_phi_L_nj6",";#phi_{Boostjets}",640,-3.2,3.2);
	h_Wjets_tau21_L_nj6 = new TH1D("Wjets_tau21_L_nj6",";tau_{21, Boostjets}",20,0,1);
	h_Wjets_tau32_L_nj6 = new TH1D("Wjets_tau32_L_nj6",";tau_{21, Boostjets}",20,0,1);
#else
	h_Topjets_pt_L_nj6 = new TH1D("Topjets_pt_L_nj6",";p_{T, Boostjets}",200,0,2000);
	h_Topjets_eta_L_nj6 = new TH1D("Topjets_eta_L_nj6",";#eta_{Boostjets}",480,-2.4,2.4);
	h_Topjets_phi_L_nj6 = new TH1D("Topjets_phi_L_nj6",";#phi_{Boostjets}",640,-3.2,3.2);
	h_Topjets_tau21_L_nj6 = new TH1D("Topjets_tau21_L_nj6",";tau_{21, Boostjets}",20,0,1);
	h_Topjets_tau32_L_nj6 = new TH1D("Topjets_tau32_L_nj6",";tau_{32, Boostjets}",20,0,1);
#endif

	h_jet1_pt_Z = new TH1D("jet1_pt_Z",";p_{T, jet1}",200,0,2000);
	h_jet1_eta_Z = new TH1D("jet1_eta_Z",";#eta_{jet1}",480,-2.4,2.4);
	h_jet1_phi_Z = new TH1D("jet1_phi_Z",";#phi_{jet1}",640,-3.2,3.2);
	h_jets_pt_Z = new TH1D("jets_pt_Z",";p_{T, jets}",200,0,2000);
	h_jets_eta_Z = new TH1D("jets_eta_Z",";#eta_{jets}",480,-2.4,2.4);
	h_jets_phi_Z = new TH1D("jets_phi_Z",";#phi_{jets}",640,-3.2,3.2);
	h_AK8jet1_pt_Z = new TH1D("AK8jet1_pt_Z",";p_{T, AK8jet1}",200,0,2000);
	h_AK8jet1_eta_Z = new TH1D("AK8jet1_eta_Z",";#eta_{AK8jet1}",480,-2.4,2.4);
	h_AK8jet1_phi_Z = new TH1D("AK8jet1_phi_Z",";#phi_{AK8jet1}",640,-3.2,3.2);
	h_AK8jet1_tau21_Z = new TH1D("AK8jet1_tau21_Z",";tau_{21, AK8jet1}",20,0,1);
	h_AK8jet1_tau32_Z = new TH1D("AK8jet1_tau32_Z",";tau_{32, AK8jet1}",20,0,1);
	h_AK8jets_pt_Z = new TH1D("AK8jets_pt_Z",";p_{T, AK8jets}",200,0,2000);
	h_AK8jets_eta_Z = new TH1D("AK8jets_eta_Z",";#eta_{AK8jets}",480,-2.4,2.4);
	h_AK8jets_phi_Z = new TH1D("AK8jets_phi_Z",";#phi_{AK8jets}",640,-3.2,3.2);
	h_AK8jets_msoftdrop_Z = new TH1D("AK8jets_msoftdrop_Z",";p_{mass, AK8jets}",100,0,500);
	h_AK8jets_tau21_Z = new TH1D("AK8jets_tau21_Z",";tau_{21, AK8jets}",20,0,1);
	h_AK8jets_tau32_Z = new TH1D("AK8jets_tau32_Z",";tau_{32, AK8jets}",20,0,1);
#if TOP == 0
	h_Wjets_pt_Z = new TH1D("Wjets_pt_Z",";p_{T, Boostjets}",200,0,2000);
	h_Wjets_eta_Z = new TH1D("Wjets_eta_Z",";#eta_{Boostjets}",480,-2.4,2.4);
	h_Wjets_phi_Z = new TH1D("Wjets_phi_Z",";#phi_{Boostjets}",640,-3.2,3.2);
	h_Wjets_tau21_Z = new TH1D("Wjets_tau21_Z",";tau_{21, Boostjets}",20,0,1);
	h_Wjets_tau32_Z = new TH1D("Wjets_tau32_Z",";tau_{21, Boostjets}",20,0,1);
#else
	h_Topjets_pt_Z = new TH1D("Topjets_pt_Z",";p_{T, Boostjets}",200,0,2000);
	h_Topjets_eta_Z = new TH1D("Topjets_eta_Z",";#eta_{Boostjets}",480,-2.4,2.4);
	h_Topjets_phi_Z = new TH1D("Topjets_phi_Z",";#phi_{Boostjets}",640,-3.2,3.2);
	h_Topjets_tau21_Z = new TH1D("Topjets_tau21_Z",";tau_{21, Boostjets}",20,0,1);
	h_Topjets_tau32_Z = new TH1D("Topjets_tau32_Z",";tau_{32, Boostjets}",20,0,1);
#endif
	h_jet1_pt_Z_nj45 = new TH1D("jet1_pt_Z_nj45",";p_{T, jet1}",200,0,2000);
	h_jet1_eta_Z_nj45 = new TH1D("jet1_eta_Z_nj45",";#eta_{jet1}",480,-2.4,2.4);
	h_jet1_phi_Z_nj45 = new TH1D("jet1_phi_Z_nj45",";#phi_{jet1}",640,-3.2,3.2);
	h_jets_pt_Z_nj45 = new TH1D("jets_pt_Z_nj45",";p_{T, jets}",200,0,2000);
	h_jets_eta_Z_nj45 = new TH1D("jets_eta_Z_nj45",";#eta_{jets}",480,-2.4,2.4);
	h_jets_phi_Z_nj45 = new TH1D("jets_phi_Z_nj45",";#phi_{jets}",640,-3.2,3.2);
	h_AK8jet1_pt_Z_nj45 = new TH1D("AK8jet1_pt_Z_nj45",";p_{T, AK8jet1}",200,0,2000);
	h_AK8jet1_eta_Z_nj45 = new TH1D("AK8jet1_eta_Z_nj45",";#eta_{AK8jet1}",480,-2.4,2.4);
	h_AK8jet1_phi_Z_nj45 = new TH1D("AK8jet1_phi_Z_nj45",";#phi_{AK8jet1}",640,-3.2,3.2);
	h_AK8jet1_tau21_Z_nj45 = new TH1D("AK8jet1_tau21_Z_nj45",";tau_{21, AK8jet1}",20,0,1);
	h_AK8jet1_tau32_Z_nj45 = new TH1D("AK8jet1_tau32_Z_nj45",";tau_{32, AK8jet1}",20,0,1);
	h_AK8jets_pt_Z_nj45 = new TH1D("AK8jets_pt_Z_nj45",";p_{T, AK8jets}",200,0,2000);
	h_AK8jets_eta_Z_nj45 = new TH1D("AK8jets_eta_Z_nj45",";#eta_{AK8jets}",480,-2.4,2.4);
	h_AK8jets_phi_Z_nj45 = new TH1D("AK8jets_phi_Z_nj45",";#phi_{AK8jets}",640,-3.2,3.2);
	h_AK8jets_msoftdrop_Z_nj45 = new TH1D("AK8jets_msoftdrop_Z_nj45",";p_{mass, AK8jets}",100,0,500);
	h_AK8jets_tau21_Z_nj45 = new TH1D("AK8jets_tau21_Z_nj45",";tau_{21, AK8jets}",20,0,1);
	h_AK8jets_tau32_Z_nj45 = new TH1D("AK8jets_tau32_Z_nj45",";tau_{32, AK8jets}",20,0,1);
#if TOP == 0
	h_Wjets_pt_Z_nj45 = new TH1D("Wjets_pt_Z_nj45",";p_{T, Boostjets}",200,0,2000);
	h_Wjets_eta_Z_nj45 = new TH1D("Wjets_eta_Z_nj45",";#eta_{Boostjets}",480,-2.4,2.4);
	h_Wjets_phi_Z_nj45 = new TH1D("Wjets_phi_Z_nj45",";#phi_{Boostjets}",640,-3.2,3.2);
	h_Wjets_tau21_Z_nj45 = new TH1D("Wjets_tau21_Z_nj45",";tau_{21, Boostjets}",20,0,1);
	h_Wjets_tau32_Z_nj45 = new TH1D("Wjets_tau32_Z_nj45",";tau_{21, Boostjets}",20,0,1);
#else
	h_Topjets_pt_Z_nj45 = new TH1D("Topjets_pt_Z_nj45",";p_{T, Boostjets}",200,0,2000);
	h_Topjets_eta_Z_nj45 = new TH1D("Topjets_eta_Z_nj45",";#eta_{Boostjets}",480,-2.4,2.4);
	h_Topjets_phi_Z_nj45 = new TH1D("Topjets_phi_Z_nj45",";#phi_{Boostjets}",640,-3.2,3.2);
	h_Topjets_tau21_Z_nj45 = new TH1D("Topjets_tau21_Z_nj45",";tau_{21, Boostjets}",20,0,1);
	h_Topjets_tau32_Z_nj45 = new TH1D("Topjets_tau32_Z_nj45",";tau_{32, Boostjets}",20,0,1);
#endif
	h_jet1_pt_Z_nj6 = new TH1D("jet1_pt_Z_nj6",";p_{T, jet1}",200,0,2000);
	h_jet1_eta_Z_nj6 = new TH1D("jet1_eta_Z_nj6",";#eta_{jet1}",480,-2.4,2.4);
	h_jet1_phi_Z_nj6 = new TH1D("jet1_phi_Z_nj6",";#phi_{jet1}",640,-3.2,3.2);
	h_jets_pt_Z_nj6 = new TH1D("jets_pt_Z_nj6",";p_{T, jets}",200,0,2000);
	h_jets_eta_Z_nj6 = new TH1D("jets_eta_Z_nj6",";#eta_{jets}",480,-2.4,2.4);
	h_jets_phi_Z_nj6 = new TH1D("jets_phi_Z_nj6",";#phi_{jets}",640,-3.2,3.2);
	h_AK8jet1_pt_Z_nj6 = new TH1D("AK8jet1_pt_Z_nj6",";p_{T, AK8jet1}",200,0,2000);
	h_AK8jet1_eta_Z_nj6 = new TH1D("AK8jet1_eta_Z_nj6",";#eta_{AK8jet1}",480,-2.4,2.4);
	h_AK8jet1_phi_Z_nj6 = new TH1D("AK8jet1_phi_Z_nj6",";#phi_{AK8jet1}",640,-3.2,3.2);
	h_AK8jet1_tau21_Z_nj6 = new TH1D("AK8jet1_tau21_Z_nj6",";tau_{21, AK8jet1}",20,0,1);
	h_AK8jet1_tau32_Z_nj6 = new TH1D("AK8jet1_tau32_Z_nj6",";tau_{32, AK8jet1}",20,0,1);
	h_AK8jets_pt_Z_nj6 = new TH1D("AK8jets_pt_Z_nj6",";p_{T, AK8jets}",200,0,2000);
	h_AK8jets_eta_Z_nj6 = new TH1D("AK8jets_eta_Z_nj6",";#eta_{AK8jets}",480,-2.4,2.4);
	h_AK8jets_phi_Z_nj6 = new TH1D("AK8jets_phi_Z_nj6",";#phi_{AK8jets}",640,-3.2,3.2);
	h_AK8jets_msoftdrop_Z_nj6 = new TH1D("AK8jets_msoftdrop_Z_nj6",";p_{mass, AK8jets}",100,0,500);
	h_AK8jets_tau21_Z_nj6 = new TH1D("AK8jets_tau21_Z_nj6",";tau_{21, AK8jets}",20,0,1);
	h_AK8jets_tau32_Z_nj6 = new TH1D("AK8jets_tau32_Z_nj6",";tau_{32, AK8jets}",20,0,1);
#if TOP == 0
	h_Wjets_pt_Z_nj6 = new TH1D("Wjets_pt_Z_nj6",";p_{T, Boostjets}",200,0,2000);
	h_Wjets_eta_Z_nj6 = new TH1D("Wjets_eta_Z_nj6",";#eta_{Boostjets}",480,-2.4,2.4);
	h_Wjets_phi_Z_nj6 = new TH1D("Wjets_phi_Z_nj6",";#phi_{Boostjets}",640,-3.2,3.2);
	h_Wjets_tau21_Z_nj6 = new TH1D("Wjets_tau21_Z_nj6",";tau_{21, Boostjets}",20,0,1);
	h_Wjets_tau32_Z_nj6 = new TH1D("Wjets_tau32_Z_nj6",";tau_{21, Boostjets}",20,0,1);
#else
	h_Topjets_pt_Z_nj6 = new TH1D("Topjets_pt_Z_nj6",";p_{T, Boostjets}",200,0,2000);
	h_Topjets_eta_Z_nj6 = new TH1D("Topjets_eta_Z_nj6",";#eta_{Boostjets}",480,-2.4,2.4);
	h_Topjets_phi_Z_nj6 = new TH1D("Topjets_phi_Z_nj6",";#phi_{Boostjets}",640,-3.2,3.2);
	h_Topjets_tau21_Z_nj6 = new TH1D("Topjets_tau21_Z_nj6",";tau_{21, Boostjets}",20,0,1);
	h_Topjets_tau32_Z_nj6 = new TH1D("Topjets_tau32_Z_nj6",";tau_{32, Boostjets}",20,0,1);
#endif

	h_jet1_pt_G = new TH1D("jet1_pt_G",";p_{T, jet1}",200,0,2000);
	h_jet1_eta_G = new TH1D("jet1_eta_G",";#eta_{jet1}",480,-2.4,2.4);
	h_jet1_phi_G = new TH1D("jet1_phi_G",";#phi_{jet1}",640,-3.2,3.2);
	h_jets_pt_G = new TH1D("jets_pt_G",";p_{T, jets}",200,0,2000);
	h_jets_eta_G = new TH1D("jets_eta_G",";#eta_{jets}",480,-2.4,2.4);
	h_jets_phi_G = new TH1D("jets_phi_G",";#phi_{jets}",640,-3.2,3.2);
	h_AK8jet1_pt_G = new TH1D("AK8jet1_pt_G",";p_{T, AK8jet1}",200,0,2000);
	h_AK8jet1_eta_G = new TH1D("AK8jet1_eta_G",";#eta_{AK8jet1}",480,-2.4,2.4);
	h_AK8jet1_phi_G = new TH1D("AK8jet1_phi_G",";#phi_{AK8jet1}",640,-3.2,3.2);
	h_AK8jet1_tau21_G = new TH1D("AK8jet1_tau21_G",";tau_{21, AK8jet1}",20,0,1);
	h_AK8jet1_tau32_G = new TH1D("AK8jet1_tau32_G",";tau_{32, AK8jet1}",20,0,1);
	h_AK8jets_pt_G = new TH1D("AK8jets_pt_G",";p_{T, AK8jets}",200,0,2000);
	h_AK8jets_eta_G = new TH1D("AK8jets_eta_G",";#eta_{AK8jets}",480,-2.4,2.4);
	h_AK8jets_phi_G = new TH1D("AK8jets_phi_G",";#phi_{AK8jets}",640,-3.2,3.2);
	h_AK8jets_msoftdrop_G = new TH1D("AK8jets_msoftdrop_G",";p_{mass, AK8jets}",100,0,500);
	h_AK8jets_tau21_G = new TH1D("AK8jets_tau21_G",";tau_{21, AK8jets}",20,0,1);
	h_AK8jets_tau32_G = new TH1D("AK8jets_tau32_G",";tau_{32, AK8jets}",20,0,1);
#if TOP == 0
	h_Wjets_pt_G = new TH1D("Wjets_pt_G",";p_{T, Boostjets}",200,0,2000);
	h_Wjets_eta_G = new TH1D("Wjets_eta_G",";#eta_{Boostjets}",480,-2.4,2.4);
	h_Wjets_phi_G = new TH1D("Wjets_phi_G",";#phi_{Boostjets}",640,-3.2,3.2);
	h_Wjets_tau21_G = new TH1D("Wjets_tau21_G",";tau_{21, Boostjets}",20,0,1);
	h_Wjets_tau32_G = new TH1D("Wjets_tau32_G",";tau_{21, Boostjets}",20,0,1);
#else
	h_Topjets_pt_G = new TH1D("Topjets_pt_G",";p_{T, Boostjets}",200,0,2000);
	h_Topjets_eta_G = new TH1D("Topjets_eta_G",";#eta_{Boostjets}",480,-2.4,2.4);
	h_Topjets_phi_G = new TH1D("Topjets_phi_G",";#phi_{Boostjets}",640,-3.2,3.2);
	h_Topjets_tau21_G = new TH1D("Topjets_tau21_G",";tau_{21, Boostjets}",20,0,1);
	h_Topjets_tau32_G = new TH1D("Topjets_tau32_G",";tau_{32, Boostjets}",20,0,1);
#endif
	h_jet1_pt_G_nj45 = new TH1D("jet1_pt_G_nj45",";p_{T, jet1}",200,0,2000);
	h_jet1_eta_G_nj45 = new TH1D("jet1_eta_G_nj45",";#eta_{jet1}",480,-2.4,2.4);
	h_jet1_phi_G_nj45 = new TH1D("jet1_phi_G_nj45",";#phi_{jet1}",640,-3.2,3.2);
	h_jets_pt_G_nj45 = new TH1D("jets_pt_G_nj45",";p_{T, jets}",200,0,2000);
	h_jets_eta_G_nj45 = new TH1D("jets_eta_G_nj45",";#eta_{jets}",480,-2.4,2.4);
	h_jets_phi_G_nj45 = new TH1D("jets_phi_G_nj45",";#phi_{jets}",640,-3.2,3.2);
	h_AK8jet1_pt_G_nj45 = new TH1D("AK8jet1_pt_G_nj45",";p_{T, AK8jet1}",200,0,2000);
	h_AK8jet1_eta_G_nj45 = new TH1D("AK8jet1_eta_G_nj45",";#eta_{AK8jet1}",480,-2.4,2.4);
	h_AK8jet1_phi_G_nj45 = new TH1D("AK8jet1_phi_G_nj45",";#phi_{AK8jet1}",640,-3.2,3.2);
	h_AK8jet1_tau21_G_nj45 = new TH1D("AK8jet1_tau21_G_nj45",";tau_{21, AK8jet1}",20,0,1);
	h_AK8jet1_tau32_G_nj45 = new TH1D("AK8jet1_tau32_G_nj45",";tau_{32, AK8jet1}",20,0,1);
	h_AK8jets_pt_G_nj45 = new TH1D("AK8jets_pt_G_nj45",";p_{T, AK8jets}",200,0,2000);
	h_AK8jets_eta_G_nj45 = new TH1D("AK8jets_eta_G_nj45",";#eta_{AK8jets}",480,-2.4,2.4);
	h_AK8jets_phi_G_nj45 = new TH1D("AK8jets_phi_G_nj45",";#phi_{AK8jets}",640,-3.2,3.2);
	h_AK8jets_msoftdrop_G_nj45 = new TH1D("AK8jets_msoftdrop_G_nj45",";p_{mass, AK8jets}",100,0,500);
	h_AK8jets_tau21_G_nj45 = new TH1D("AK8jets_tau21_G_nj45",";tau_{21, AK8jets}",20,0,1);
	h_AK8jets_tau32_G_nj45 = new TH1D("AK8jets_tau32_G_nj45",";tau_{32, AK8jets}",20,0,1);
#if TOP == 0
	h_Wjets_pt_G_nj45 = new TH1D("Wjets_pt_G_nj45",";p_{T, Boostjets}",200,0,2000);
	h_Wjets_eta_G_nj45 = new TH1D("Wjets_eta_G_nj45",";#eta_{Boostjets}",480,-2.4,2.4);
	h_Wjets_phi_G_nj45 = new TH1D("Wjets_phi_G_nj45",";#phi_{Boostjets}",640,-3.2,3.2);
	h_Wjets_tau21_G_nj45 = new TH1D("Wjets_tau21_G_nj45",";tau_{21, Boostjets}",20,0,1);
	h_Wjets_tau32_G_nj45 = new TH1D("Wjets_tau32_G_nj45",";tau_{21, Boostjets}",20,0,1);
#else
	h_Topjets_pt_G_nj45 = new TH1D("Topjets_pt_G_nj45",";p_{T, Boostjets}",200,0,2000);
	h_Topjets_eta_G_nj45 = new TH1D("Topjets_eta_G_nj45",";#eta_{Boostjets}",480,-2.4,2.4);
	h_Topjets_phi_G_nj45 = new TH1D("Topjets_phi_G_nj45",";#phi_{Boostjets}",640,-3.2,3.2);
	h_Topjets_tau21_G_nj45 = new TH1D("Topjets_tau21_G_nj45",";tau_{21, Boostjets}",20,0,1);
	h_Topjets_tau32_G_nj45 = new TH1D("Topjets_tau32_G_nj45",";tau_{32, Boostjets}",20,0,1);
#endif
	h_jet1_pt_G_nj6 = new TH1D("jet1_pt_G_nj6",";p_{T, jet1}",200,0,2000);
	h_jet1_eta_G_nj6 = new TH1D("jet1_eta_G_nj6",";#eta_{jet1}",480,-2.4,2.4);
	h_jet1_phi_G_nj6 = new TH1D("jet1_phi_G_nj6",";#phi_{jet1}",640,-3.2,3.2);
	h_jets_pt_G_nj6 = new TH1D("jets_pt_G_nj6",";p_{T, jets}",200,0,2000);
	h_jets_eta_G_nj6 = new TH1D("jets_eta_G_nj6",";#eta_{jets}",480,-2.4,2.4);
	h_jets_phi_G_nj6 = new TH1D("jets_phi_G_nj6",";#phi_{jets}",640,-3.2,3.2);
	h_AK8jet1_pt_G_nj6 = new TH1D("AK8jet1_pt_G_nj6",";p_{T, AK8jet1}",200,0,2000);
	h_AK8jet1_eta_G_nj6 = new TH1D("AK8jet1_eta_G_nj6",";#eta_{AK8jet1}",480,-2.4,2.4);
	h_AK8jet1_phi_G_nj6 = new TH1D("AK8jet1_phi_G_nj6",";#phi_{AK8jet1}",640,-3.2,3.2);
	h_AK8jet1_tau21_G_nj6 = new TH1D("AK8jet1_tau21_G_nj6",";tau_{21, AK8jet1}",20,0,1);
	h_AK8jet1_tau32_G_nj6 = new TH1D("AK8jet1_tau32_G_nj6",";tau_{32, AK8jet1}",20,0,1);
	h_AK8jets_pt_G_nj6 = new TH1D("AK8jets_pt_G_nj6",";p_{T, AK8jets}",200,0,2000);
	h_AK8jets_eta_G_nj6 = new TH1D("AK8jets_eta_G_nj6",";#eta_{AK8jets}",480,-2.4,2.4);
	h_AK8jets_phi_G_nj6 = new TH1D("AK8jets_phi_G_nj6",";#phi_{AK8jets}",640,-3.2,3.2);
	h_AK8jets_msoftdrop_G_nj6 = new TH1D("AK8jets_msoftdrop_G_nj6",";p_{mass, AK8jets}",100,0,500);
	h_AK8jets_tau21_G_nj6 = new TH1D("AK8jets_tau21_G_nj6",";tau_{21, AK8jets}",20,0,1);
	h_AK8jets_tau32_G_nj6 = new TH1D("AK8jets_tau32_G_nj6",";tau_{32, AK8jets}",20,0,1);
#if TOP == 0
	h_Wjets_pt_G_nj6 = new TH1D("Wjets_pt_G_nj6",";p_{T, Boostjets}",200,0,2000);
	h_Wjets_eta_G_nj6 = new TH1D("Wjets_eta_G_nj6",";#eta_{Boostjets}",480,-2.4,2.4);
	h_Wjets_phi_G_nj6 = new TH1D("Wjets_phi_G_nj6",";#phi_{Boostjets}",640,-3.2,3.2);
	h_Wjets_tau21_G_nj6 = new TH1D("Wjets_tau21_G_nj6",";tau_{21, Boostjets}",20,0,1);
	h_Wjets_tau32_G_nj6 = new TH1D("Wjets_tau32_G_nj6",";tau_{21, Boostjets}",20,0,1);
#else
	h_Topjets_pt_G_nj6 = new TH1D("Topjets_pt_G_nj6",";p_{T, Boostjets}",200,0,2000);
	h_Topjets_eta_G_nj6 = new TH1D("Topjets_eta_G_nj6",";#eta_{Boostjets}",480,-2.4,2.4);
	h_Topjets_phi_G_nj6 = new TH1D("Topjets_phi_G_nj6",";#phi_{Boostjets}",640,-3.2,3.2);
	h_Topjets_tau21_G_nj6 = new TH1D("Topjets_tau21_G_nj6",";tau_{21, Boostjets}",20,0,1);
	h_Topjets_tau32_G_nj6 = new TH1D("Topjets_tau32_G_nj6",";tau_{32, Boostjets}",20,0,1);
#endif
	h_photon_pt_G = new TH1D("photon_pt_G",";p_{T, photon}",100,0,1000);
	h_photon_pt_G_nj45 = new TH1D("photon_pt_G_nj45",";p_{T, photon}",100,0,1000);
	h_photon_pt_G_nj6 = new TH1D("photon_pt_G_nj6",";p_{T, photon}",100,0,1000);
	h_photon_eta_G = new TH1D("photon_eta_G",";#eta_{photon}",480,-2.4,2.4);
	h_photon_eta_G_nj45 = new TH1D("photon_eta_G_nj45",";#eta_{photon}",480,-2.4,2.4);
	h_photon_eta_G_nj6 = new TH1D("photon_eta_G_nj6",";#eta_{photon}",480,-2.4,2.4);
	h_photon_phi_G = new TH1D("photon_phi_G",";#phi_{photon}",640,-3.2,3.2);
	h_photon_phi_G_nj45 = new TH1D("photon_phi_G_nj45",";#phi_{photon}",640,-3.2,3.2);
	h_photon_phi_G_nj6 = new TH1D("photon_phi_G_nj6",";#phi_{photon}",640,-3.2,3.2);

	h_jet1_pt_P = new TH1D("jet1_pt_P",";p_{T, jet1}",200,0,2000);
	h_jet1_eta_P = new TH1D("jet1_eta_P",";#eta_{jet1}",480,-2.4,2.4);
	h_jet1_phi_P = new TH1D("jet1_phi_P",";#phi_{jet1}",640,-3.2,3.2);
	h_jets_pt_P = new TH1D("jets_pt_P",";p_{T, jets}",200,0,2000);
	h_jets_eta_P = new TH1D("jets_eta_P",";#eta_{jets}",480,-2.4,2.4);
	h_jets_phi_P = new TH1D("jets_phi_P",";#phi_{jets}",640,-3.2,3.2);
	h_AK8jet1_pt_P = new TH1D("AK8jet1_pt_P",";p_{T, AK8jet1}",200,0,2000);
	h_AK8jet1_eta_P = new TH1D("AK8jet1_eta_P",";#eta_{AK8jet1}",480,-2.4,2.4);
	h_AK8jet1_phi_P = new TH1D("AK8jet1_phi_P",";#phi_{AK8jet1}",640,-3.2,3.2);
	h_AK8jet1_tau21_P = new TH1D("AK8jet1_tau21_P",";tau_{21, AK8jet1}",20,0,1);
	h_AK8jet1_tau32_P = new TH1D("AK8jet1_tau32_P",";tau_{32, AK8jet1}",20,0,1);
	h_AK8jets_pt_P = new TH1D("AK8jets_pt_P",";p_{T, AK8jets}",200,0,2000);
	h_AK8jets_eta_P = new TH1D("AK8jets_eta_P",";#eta_{AK8jets}",480,-2.4,2.4);
	h_AK8jets_phi_P = new TH1D("AK8jets_phi_P",";#phi_{AK8jets}",640,-3.2,3.2);
	h_AK8jets_msoftdrop_P = new TH1D("AK8jets_msoftdrop_P",";p_{mass, AK8jets}",100,0,500);
	h_AK8jets_tau21_P = new TH1D("AK8jets_tau21_P",";tau_{21, AK8jets}",20,0,1);
	h_AK8jets_tau32_P = new TH1D("AK8jets_tau32_P",";tau_{32, AK8jets}",20,0,1);

	h_njet_P       = new TH1D("njet_P",         ";N_{jet}",                20, 0,  20);
	h_nAK8jet_P    = new TH1D("nAK8jet_P",      ";N_{jet}",                20, 0,  20);
	h_nbTight_P    = new TH1D("nbTight_P",     ";N_{jet}",                20, 0,  20);
	h_nbMedium_P   = new TH1D("nbMedium_P",     ";N_{jet}",                20, 0,  20);
	h_nbLoose_P    = new TH1D("nbLoose_P",     ";N_{jet}",                20, 0,  20);
	h_nEleVeto_P   = new TH1D("nEleVeto_P",     ";N_{jet}",                20, 0,  20);
	h_nEleTight_P  = new TH1D("nEleTight_P",     ";N_{jet}",                20, 0,  20);
	h_nEleMedium_P = new TH1D("nEleMedium_P",     ";N_{jet}",                20, 0,  20);
	h_nEleLoose_P  = new TH1D("nEleLoose_P",     ";N_{jet}",                20, 0,  20);
	h_nMuTight_P   = new TH1D("nMuTight_P",     ";N_{jet}",                20, 0,  20);
	h_nMuMedium_P  = new TH1D("nMuMedium_P",     ";N_{jet}",                20, 0,  20);
	h_nMuSoft_P    = new TH1D("nMuSoft_P",     ";N_{jet}",                20, 0,  20);
	h_nTauVeto_P   = new TH1D("nTauVeto_P",     ";N_{jet}",                20, 0,  20);
	h_nIsoTrack_P  = new TH1D("nIsoTrack_P",     ";N_{jet}",                20, 0,  20);
	h_nPhoMedium_P = new TH1D("nPhoMedium_P",     ";N_{jet}",                20, 0,  20);
	h_nw_P         = new TH1D("nw_P",           ";N_{W tag}",              20, 0,  20);
	h_ht_AK4_P= new TH1D("ht_AK4_P",  ";H_{T}",                  nbn_HT, bn_HT);
	h_MET_P= new TH1D("MET_P",  ";H_{T}",    400,0,2000);
	h_MR_P= new TH1D("MR_P",  ";H_{T}",      nbn_MR, bn_MR);
	h_R2_P= new TH1D("R2_P",  ";H_{T}",      nbn_R2, bn_R2);

	h_Megajets_pt_P = new TH1D("Megajets_pt_P",";p_{T, Megajets}",200,0,2000);
	h_Megajets_eta_P = new TH1D("Megajets_eta_P",";#eta_{Megajets}",480,-2.4,2.4);
	h_Megajets_phi_P = new TH1D("Megajets_phi_P",";#phi_{Megajets}",640,-3.2,3.2);
	h_Megajets_pt_s = new TH1D("Megajets_pt_s",";p_{T, Megajets}",200,0,2000);
	h_Megajets_eta_s = new TH1D("Megajets_eta_s",";#eta_{Megajets}",480,-2.4,2.4);
	h_Megajets_phi_s = new TH1D("Megajets_phi_s",";#phi_{Megajets}",640,-3.2,3.2);
	h_Megajets_pt_Q = new TH1D("Megajets_pt_Q",";p_{T, Megajets}",200,0,2000);
	h_Megajets_eta_Q = new TH1D("Megajets_eta_Q",";#eta_{Megajets}",480,-2.4,2.4);
	h_Megajets_phi_Q = new TH1D("Megajets_phi_Q",";#phi_{Megajets}",640,-3.2,3.2);
	h_Megajets_pt_q = new TH1D("Megajets_pt_q",";p_{T, Megajets}",200,0,2000);
	h_Megajets_eta_q = new TH1D("Megajets_eta_q",";#eta_{Megajets}",480,-2.4,2.4);
	h_Megajets_phi_q = new TH1D("Megajets_phi_q",";#phi_{Megajets}",640,-3.2,3.2);
	h_Megajets_pt_T = new TH1D("Megajets_pt_T",";p_{T, Megajets}",200,0,2000);
	h_Megajets_eta_T = new TH1D("Megajets_eta_T",";#eta_{Megajets}",480,-2.4,2.4);
	h_Megajets_phi_T = new TH1D("Megajets_phi_T",";#phi_{Megajets}",640,-3.2,3.2);
	h_Megajets_pt_W = new TH1D("Megajets_pt_W",";p_{T, Megajets}",200,0,2000);
	h_Megajets_eta_W = new TH1D("Megajets_eta_W",";#eta_{Megajets}",480,-2.4,2.4);
	h_Megajets_phi_W = new TH1D("Megajets_phi_W",";#phi_{Megajets}",640,-3.2,3.2);
	h_Megajets_pt_Z = new TH1D("Megajets_pt_Z",";p_{T, Megajets}",200,0,2000);
	h_Megajets_eta_Z = new TH1D("Megajets_eta_Z",";#eta_{Megajets}",480,-2.4,2.4);
	h_Megajets_phi_Z = new TH1D("Megajets_phi_Z",";#phi_{Megajets}",640,-3.2,3.2);
	h_Megajets_pt_G = new TH1D("Megajets_pt_G",";p_{T, Megajets}",200,0,2000);
	h_Megajets_eta_G = new TH1D("Megajets_eta_G",";#eta_{Megajets}",480,-2.4,2.4);
	h_Megajets_phi_G = new TH1D("Megajets_phi_G",";#phi_{Megajets}",640,-3.2,3.2);
	h_Megajets_pt_L = new TH1D("Megajets_pt_L",";p_{T, Megajets}",200,0,2000);
	h_Megajets_eta_L = new TH1D("Megajets_eta_L",";#eta_{Megajets}",480,-2.4,2.4);
	h_Megajets_phi_L = new TH1D("Megajets_phi_L",";#phi_{Megajets}",640,-3.2,3.2);

	h_njet_s       = new TH1D("njet_s",         ";N_{jet}",                20, 0,  20);
	h_nAK8jet_s    = new TH1D("nAK8jet_s",      ";N_{jet}",                20, 0,  20);
	h_njet_Q       = new TH1D("njet_Q",         ";N_{jet}",                20, 0,  20);
	h_nAK8jet_Q    = new TH1D("nAK8jet_Q",      ";N_{jet}",                20, 0,  20);
	h_njet_q       = new TH1D("njet_q",         ";N_{jet}",                20, 0,  20);
	h_nAK8jet_q    = new TH1D("nAK8jet_q",      ";N_{jet}",                20, 0,  20);
	h_njet_T       = new TH1D("njet_T",         ";N_{jet}",                20, 0,  20);
	h_nAK8jet_T    = new TH1D("nAK8jet_T",      ";N_{jet}",                20, 0,  20);
	h_njet_W       = new TH1D("njet_W",         ";N_{jet}",                20, 0,  20);
	h_nAK8jet_W    = new TH1D("nAK8jet_W",      ";N_{jet}",                20, 0,  20);
	h_njet_Z       = new TH1D("njet_Z",         ";N_{jet}",                20, 0,  20);
	h_nAK8jet_Z    = new TH1D("nAK8jet_Z",      ";N_{jet}",                20, 0,  20);
	h_njet_G       = new TH1D("njet_G",         ";N_{jet}",                20, 0,  20);
	h_nAK8jet_G    = new TH1D("nAK8jet_G",      ";N_{jet}",                20, 0,  20);
	h_njet_L       = new TH1D("njet_L",         ";N_{jet}",                20, 0,  20);
	h_nAK8jet_L    = new TH1D("nAK8jet_L",      ";N_{jet}",                20, 0,  20);

	h_ele_pt_T = new TH1D("ele_pt_T", ";p_{T, ele}", 20, 0,400);
	h_ele_pt_W = new TH1D("ele_pt_W", ";p_{T, ele}", 20, 0,400);
	h_ele_pt_L = new TH1D("ele_pt_L", ";p_{T, ele}", 20, 0,400);
	h_mu_pt_T = new TH1D("mu_pt_T", ";p_{T, mu}", 20, 0,400);
	h_mu_pt_W = new TH1D("mu_pt_W", ";p_{T, mu}", 20, 0,400);
	h_mu_pt_L = new TH1D("mu_pt_L", ";p_{T, mu}", 20, 0,400);

	h_ht_AK4_s = new TH1D("ht_AK4_s",  ";H_{T}",                  nbn_HT, bn_HT);
	h_MR_s = new TH1D("MR_s",   ";MR_{AK4}",     nbn_MR,    bn_MR);
	h_R2_s = new TH1D("R2_s",   ";R2_{AK4}",         nbn_R2,bn_R2);
	h_MET_s = new TH1D("MET_s", ";MET", 400,0,2000);
	h_MET_phi_s = new TH1D("MET_phi_s", ";#phi_{MET}", 640, -3.2,3.2);
	h_MET_phi_s_nj45 = new TH1D("MET_phi_s_nj45", ";#phi_{MET}", 640, -3.2,3.2);
	h_MET_phi_s_nj6 = new TH1D("MET_phi_s_nj6", ";#phi_{MET}", 640, -3.2,3.2);
	h_mDPhi_nomDPhi_s = new TH1D("mDPhi_nomDPhi_s", ";#Delta#phi_{megajets}", 64,0,3.2);
	h_mDPhi_nomDPhi_s_nj45 = new TH1D("mDPhi_nomDPhi_s_nj45", ";#Delta#phi_{megajets}", 64,0,3.2);
	h_mDPhi_nomDPhi_s_nj6 = new TH1D("mDPhi_nomDPhi_s_nj6", ";#Delta#phi_{megajets}", 64,0,3.2);
#if TOP == 0
	h_nW_nonW_s = new TH1D("nW_nonW_s", ";# of Wjet", 10,0,10);
	h_nW_nonW_s_nj45 = new TH1D("nW_nonW_s_nj45", ";# of Wjet", 10,0,10);
	h_nW_nonW_s_nj6 = new TH1D("nW_nonW_s_nj6", ";# of Wjet", 10,0,10);
	h_nb_nonb_s = new TH1D("nb_nonb_s", ";# of bjet", 10,0,10);
	h_nb_nonb_s_nj45 = new TH1D("nb_nonb_s_nj45", ";# of bjet", 10,0,10);
	h_nb_nonb_s_nj6 = new TH1D("nb_nonb_s_nj6", ";# of bjet", 10,0,10);
#else
	h_nTop_nonTop_s = new TH1D("nTop_nonTop_s", ";# of Topjet", 10,0,10);
	h_nTop_nonTop_s_nj45 = new TH1D("nTop_nonTop_s_nj45", ";# of Topjet", 10,0,10);
	h_nTop_nonTop_s_nj6 = new TH1D("nTop_nonTop_s_nj6", ";# of Topjet", 10,0,10);
#endif

#if TOP == 0
	h_nW_nonW_q = new TH1D("nW_nonW_q", ";# of Wjet", 10,0,10);
	h_nW_nonW_q_nj45 = new TH1D("nW_nonW_q_nj45", ";# of Wjet", 10,0,10);
	h_nW_nonW_q_nj6 = new TH1D("nW_nonW_q_nj6", ";# of Wjet", 10,0,10);
#else
	h_nTop_nonTop_q = new TH1D("nTop_nonTop_q", ";# of Topjet", 10,0,10);
	h_nTop_nonTop_q_nj45 = new TH1D("nTop_nonTop_q_nj45", ";# of Topjet", 10,0,10);
	h_nTop_nonTop_q_nj6 = new TH1D("nTop_nonTop_q_nj6", ";# of Topjet", 10,0,10);
#endif
	h_nb_nonb_q = new TH1D("nb_nonb_q", ";# of bjet", 10,0,10);
	h_nb_nonb_q_nj45 = new TH1D("nb_nonb_q_nj45", ";# of bjet", 10,0,10);
	h_nb_nonb_q_nj6 = new TH1D("nb_nonb_q_nj6", ";# of bjet", 10,0,10);

	h_ht_AK4_s_nj45 = new TH1D("ht_AK4_s_nj45",  ";H_{T}",                  nbn_HT, bn_HT);
	h_MR_s_nj45 = new TH1D("MR_s_nj45",   ";MR_{AK4}",     nbn_MR,    bn_MR);
	h_R2_s_nj45 = new TH1D("R2_s_nj45",   ";R2_{AK4}",         nbn_R2,bn_R2);
	h_MET_s_nj45 = new TH1D("MET_s_nj45", ";MET", 400,0,2000);

	h_ht_AK4_s_nj6 = new TH1D("ht_AK4_s_nj6",  ";H_{T}",                  nbn_HT, bn_HT);
	h_MR_s_nj6 = new TH1D("MR_s_nj6",   ";MR_{AK4}",     nbn_MR,    bn_MR);
	h_R2_s_nj6 = new TH1D("R2_s_nj6",   ";R2_{AK4}",         nbn_R2,bn_R2);
	h_MET_s_nj6 = new TH1D("MET_s_nj6", ";MET", 400,0,2000);

	h_ht_AK4_Z = new TH1D("ht_AK4_Z",  ";H_{T}",                  nbn_HT, bn_HT);
	h_MR_Z = new TH1D("MR_Z",   ";MR_{AK4}",     nbn_MR,    bn_MR);
	h_R2_Z = new TH1D("R2_Z",   ";R2_{AK4}",         nbn_R2,bn_R2);
	h_MET_Z = new TH1D("MET_Z", ";MET", 400,0,2000);
	h_MET_phi_Z = new TH1D("MET_phi_Z", ";#phi_{MET}", 640, -3.2,3.2);
	h_MET_phi_Z_nj45 = new TH1D("MET_phi_Z_nj45", ";#phi_{MET}", 640, -3.2,3.2);
	h_MET_phi_Z_nj6 = new TH1D("MET_phi_Z_nj6", ";#phi_{MET}", 640, -3.2,3.2);

	h_ht_AK4_Z_nj45 = new TH1D("ht_AK4_Z_nj45",  ";H_{T}",                  nbn_HT, bn_HT);
	h_MR_Z_nj45 = new TH1D("MR_Z_nj45",   ";MR_{AK4}",     nbn_MR,    bn_MR);
	h_R2_Z_nj45 = new TH1D("R2_Z_nj45",   ";R2_{AK4}",         nbn_R2,bn_R2);
	h_MET_Z_nj45 = new TH1D("MET_Z_nj45", ";MET", 400,0,2000);

	h_ht_AK4_Z_nj6 = new TH1D("ht_AK4_Z_nj6",  ";H_{T}",                  nbn_HT, bn_HT);
	h_MR_Z_nj6 = new TH1D("MR_Z_nj6",   ";MR_{AK4}",     nbn_MR,    bn_MR);
	h_R2_Z_nj6 = new TH1D("R2_Z_nj6",   ";R2_{AK4}",         nbn_R2,bn_R2);
	h_MET_Z_nj6 = new TH1D("MET_Z_nj6", ";MET", 400,0,2000);

	h_ht_AK4_no2Lep_Z = new TH1D("ht_AK4_no2Lep_Z",  ";H_{T}",                  nbn_HT, bn_HT);
	h_MR_no2Lep_Z = new TH1D("MR_no2Lep_Z",   ";MR_{AK4}",         nbn_MR,bn_MR);
	h_R2_no2Lep_Z = new TH1D("R2_no2Lep_Z",   ";R2_{AK4}",         nbn_R2,bn_R2);
	h_MET_no2Lep_Z = new TH1D("MET_no2Lep_Z", ";MET", 400,0,2000);
	h_nLep_no2Lep_Z = new TH1D("nLep_no2Lep_Z", ";# of Lepton", 10,0,10);

	h_ht_AK4_nomDPhi_Z = new TH1D("ht_AK4_nomDPhi_Z",  ";H_{T}",                  nbn_HT, bn_HT);
	h_MR_nomDPhi_Z = new TH1D("MR_nomDPhi_Z",   ";MR_{AK4}",         nbn_MR,bn_MR);
	h_R2_nomDPhi_Z = new TH1D("R2_nomDPhi_Z",   ";R2_{AK4}",         nbn_R2,bn_R2);
	h_MET_nomDPhi_Z = new TH1D("MET_nomDPhi_Z", ";MET", 400,0,2000);
	h_mDPhi_nomDPhi_Z = new TH1D("mDPhi_nomDPhi_Z", ";#Delta#phi_{megajets}", 64,0,3.2);

	h_ht_AK4_noMll_Z = new TH1D("ht_AK4_noMll_Z",  ";H_{T}",                  nbn_HT, bn_HT);
	h_MR_noMll_Z = new TH1D("MR_noMll_Z",   ";MR_{AK4}",         nbn_MR,bn_MR);
	h_R2_noMll_Z = new TH1D("R2_noMll_Z",   ";R2_{AK4}",         nbn_R2,bn_R2);
	h_MET_noMll_Z = new TH1D("MET_noMll_Z", ";MET", 400,0,2000);
	h_Mll_noMll_Z = new TH1D("Mll_noMll_Z", ";Mass_{two leptons}", 50,50,150);

	h_ht_AK4_no2Lep_Z_nj45 = new TH1D("ht_AK4_no2Lep_Z_nj45",  ";H_{T}",                  nbn_HT, bn_HT);
	h_MR_no2Lep_Z_nj45 = new TH1D("MR_no2Lep_Z_nj45",   ";MR_{AK4}",         nbn_MR,bn_MR);
	h_R2_no2Lep_Z_nj45 = new TH1D("R2_no2Lep_Z_nj45",   ";R2_{AK4}",         nbn_R2,bn_R2);
	h_MET_no2Lep_Z_nj45 = new TH1D("MET_no2Lep_Z_nj45", ";MET", 400,0,2000);
	h_nLep_no2Lep_Z_nj45 = new TH1D("nLep_no2Lep_Z_nj45", ";# of Lepton", 10,0,10);

	h_ht_AK4_noMll_Z_nj45 = new TH1D("ht_AK4_noMll_Z_nj45",  ";H_{T}",                  nbn_HT, bn_HT);
	h_MR_noMll_Z_nj45 = new TH1D("MR_noMll_Z_nj45",   ";MR_{AK4}",         nbn_MR,bn_MR);
	h_R2_noMll_Z_nj45 = new TH1D("R2_noMll_Z_nj45",   ";R2_{AK4}",         nbn_R2,bn_R2);
	h_MET_noMll_Z_nj45 = new TH1D("MET_noMll_Z_nj45", ";MET", 400,0,2000);
	h_Mll_noMll_Z_nj45 = new TH1D("Mll_noMll_Z_nj45", ";Mass_{two leptons}", 50,50,150);

	h_ht_AK4_nomDPhi_Z_nj45 = new TH1D("ht_AK4_nomDPhi_Z_nj45",  ";H_{T}",                  nbn_HT, bn_HT);
	h_MR_nomDPhi_Z_nj45 = new TH1D("MR_nomDPhi_Z_nj45",   ";MR_{AK4}",         nbn_MR,bn_MR);
	h_R2_nomDPhi_Z_nj45 = new TH1D("R2_nomDPhi_Z_nj45",   ";R2_{AK4}",         nbn_R2,bn_R2);
	h_MET_nomDPhi_Z_nj45 = new TH1D("MET_nomDPhi_Z_nj45", ";MET", 400,0,2000);
	h_mDPhi_nomDPhi_Z_nj45 = new TH1D("mDPhi_nomDPhi_Z_nj45", ";#Delta#phi_{megajets}", 64,0,3.2);

	h_ht_AK4_no2Lep_Z_nj6 = new TH1D("ht_AK4_no2Lep_Z_nj6",  ";H_{T}",                  nbn_HT, bn_HT);
	h_MR_no2Lep_Z_nj6 = new TH1D("MR_no2Lep_Z_nj6",   ";MR_{AK4}",         nbn_MR,bn_MR);
	h_R2_no2Lep_Z_nj6 = new TH1D("R2_no2Lep_Z_nj6",   ";R2_{AK4}",         nbn_R2,bn_R2);
	h_MET_no2Lep_Z_nj6 = new TH1D("MET_no2Lep_Z_nj6", ";MET", 400,0,2000);
	h_nLep_no2Lep_Z_nj6 = new TH1D("nLep_no2Lep_Z_nj6", ";# of Lepton", 10,0,10);

	h_ht_AK4_noMll_Z_nj6 = new TH1D("ht_AK4_noMll_Z_nj6",  ";H_{T}",                  nbn_HT, bn_HT);
	h_MR_noMll_Z_nj6 = new TH1D("MR_noMll_Z_nj6",   ";MR_{AK4}",         nbn_MR,bn_MR);
	h_R2_noMll_Z_nj6 = new TH1D("R2_noMll_Z_nj6",   ";R2_{AK4}",         nbn_R2,bn_R2);
	h_MET_noMll_Z_nj6 = new TH1D("MET_noMll_Z_nj6", ";MET", 400,0,2000);
	h_Mll_noMll_Z_nj6 = new TH1D("Mll_noMll_Z_nj6", ";Mass_{two leptons}", 50,50,150);

	h_ht_AK4_nomDPhi_Z_nj6 = new TH1D("ht_AK4_nomDPhi_Z_nj6",  ";H_{T}",                  nbn_HT, bn_HT);
	h_MR_nomDPhi_Z_nj6 = new TH1D("MR_nomDPhi_Z_nj6",   ";MR_{AK4}",         nbn_MR,bn_MR);
	h_R2_nomDPhi_Z_nj6 = new TH1D("R2_nomDPhi_Z_nj6",   ";R2_{AK4}",         nbn_R2,bn_R2);
	h_MET_nomDPhi_Z_nj6 = new TH1D("MET_nomDPhi_Z_nj6", ";MET", 400,0,2000);
	h_mDPhi_nomDPhi_Z_nj6 = new TH1D("mDPhi_nomDPhi_Z_nj6", ";#Delta#phi_{megajets}", 64,0,3.2);

#if TOP == 0
	h_ht_AK4_nonW_Z = new TH1D("ht_AK4_nonW_Z",  ";H_{T}",                  nbn_HT, bn_HT);
	h_MR_nonW_Z = new TH1D("MR_nonW_Z",   ";MR_{AK4}",         nbn_MR,bn_MR);
	h_R2_nonW_Z = new TH1D("R2_nonW_Z",   ";R2_{AK4}",         nbn_R2,bn_R2);
	h_MET_nonW_Z = new TH1D("MET_nonW_Z", ";MET", 400,0,2000);
	h_nW_nonW_Z = new TH1D("nW_nonW_Z", ";# of Wjet", 10,0,10);

	h_ht_AK4_nonW_Z_nj45 = new TH1D("ht_AK4_nonW_Z_nj45",  ";H_{T}",                  nbn_HT, bn_HT);
	h_MR_nonW_Z_nj45 = new TH1D("MR_nonW_Z_nj45",   ";MR_{AK4}",         nbn_MR,bn_MR);
	h_R2_nonW_Z_nj45 = new TH1D("R2_nonW_Z_nj45",   ";R2_{AK4}",         nbn_R2,bn_R2);
	h_MET_nonW_Z_nj45 = new TH1D("MET_nonW_Z_nj45", ";MET", 400,0,2000);
	h_nW_nonW_Z_nj45 = new TH1D("nW_nonW_Z_nj45", ";# of Wjet", 10,0,10);

	h_ht_AK4_nonW_Z_nj6 = new TH1D("ht_AK4_nonW_Z_nj6",  ";H_{T}",                  nbn_HT, bn_HT);
	h_MR_nonW_Z_nj6 = new TH1D("MR_nonW_Z_nj6",   ";MR_{AK4}",         nbn_MR,bn_MR);
	h_R2_nonW_Z_nj6 = new TH1D("R2_nonW_Z_nj6",   ";R2_{AK4}",         nbn_R2,bn_R2);
	h_MET_nonW_Z_nj6 = new TH1D("MET_nonW_Z_nj6", ";MET", 400,0,2000);
	h_nW_nonW_Z_nj6 = new TH1D("nW_nonW_Z_nj6", ";# of Wjet", 10,0,10);
#else
	h_ht_AK4_nonTop_Z = new TH1D("ht_AK4_nonTop_Z",  ";H_{T}",                  nbn_HT, bn_HT);
	h_MR_nonTop_Z = new TH1D("MR_nonTop_Z",   ";MR_{AK4}",         nbn_MR,bn_MR);
	h_R2_nonTop_Z = new TH1D("R2_nonTop_Z",   ";R2_{AK4}",         nbn_R2,bn_R2);
	h_MET_nonTop_Z = new TH1D("MET_nonTop_Z", ";MET", 400,0,2000);
	h_nTop_nonTop_Z = new TH1D("nTop_nonTop_Z", ";# of Topjet", 10,0,10);

	h_ht_AK4_nonTop_Z_nj45 = new TH1D("ht_AK4_nonTop_Z_nj45",  ";H_{T}",                  nbn_HT, bn_HT);
	h_MR_nonTop_Z_nj45 = new TH1D("MR_nonTop_Z_nj45",   ";MR_{AK4}",         nbn_MR,bn_MR);
	h_R2_nonTop_Z_nj45 = new TH1D("R2_nonTop_Z_nj45",   ";R2_{AK4}",         nbn_R2,bn_R2);
	h_MET_nonTop_Z_nj45 = new TH1D("MET_nonTop_Z_nj45", ";MET", 400,0,2000);
	h_nTop_nonTop_Z_nj45 = new TH1D("nTop_nonTop_Z_nj45", ";# of Topjet", 10,0,10);

	h_ht_AK4_nonTop_Z_nj6 = new TH1D("ht_AK4_nonTop_Z_nj6",  ";H_{T}",                  nbn_HT, bn_HT);
	h_MR_nonTop_Z_nj6 = new TH1D("MR_nonTop_Z_nj6",   ";MR_{AK4}",         nbn_MR,bn_MR);
	h_R2_nonTop_Z_nj6 = new TH1D("R2_nonTop_Z_nj6",   ";R2_{AK4}",         nbn_R2,bn_R2);
	h_MET_nonTop_Z_nj6 = new TH1D("MET_nonTop_Z_nj6", ";MET", 400,0,2000);
	h_nTop_nonTop_Z_nj6 = new TH1D("nTop_nonTop_Z_nj6", ";# of Topjet", 10,0,10);
#endif

	h_ht_AK4_L = new TH1D("ht_AK4_L",  ";H_{T}",                  nbn_HT, bn_HT);
	h_MR_L = new TH1D("MR_L",   ";MR_{AK4}",     nbn_MR,    bn_MR);
	h_R2_L = new TH1D("R2_L",   ";R2_{AK4}",         nbn_R2,bn_R2);
	h_MET_L = new TH1D("MET_L", ";MET", 400,0,2000);
	h_MET_phi_L = new TH1D("MET_phi_L", ";#phi_{MET}", 640, -3.2,3.2);
	h_MET_phi_L_nj45 = new TH1D("MET_phi_L_nj45", ";#phi_{MET}", 640, -3.2,3.2);
	h_MET_phi_L_nj6 = new TH1D("MET_phi_L_nj6", ";#phi_{MET}", 640, -3.2,3.2);

	h_ht_AK4_L_nj45 = new TH1D("ht_AK4_L_nj45",  ";H_{T}",                  nbn_HT, bn_HT);
	h_MR_L_nj45 = new TH1D("MR_L_nj45",   ";MR_{AK4}",     nbn_MR,    bn_MR);
	h_R2_L_nj45 = new TH1D("R2_L_nj45",   ";R2_{AK4}",         nbn_R2,bn_R2);
	h_MET_L_nj45 = new TH1D("MET_L_nj45", ";MET", 400,0,2000);

	h_ht_AK4_L_nj6 = new TH1D("ht_AK4_L_nj6",  ";H_{T}",                  nbn_HT, bn_HT);
	h_MR_L_nj6 = new TH1D("MR_L_nj6",   ";MR_{AK4}",     nbn_MR,    bn_MR);
	h_R2_L_nj6 = new TH1D("R2_L_nj6",   ";R2_{AK4}",         nbn_R2,bn_R2);
	h_MET_L_nj6 = new TH1D("MET_L_nj6", ";MET", 400,0,2000);

	h_ht_AK4_no1Lep_L = new TH1D("ht_AK4_no1Lep_L",  ";H_{T}",                  nbn_HT, bn_HT);
	h_MR_no1Lep_L = new TH1D("MR_no1Lep_L",   ";MR_{AK4}",         nbn_MR,bn_MR);
	h_R2_no1Lep_L = new TH1D("R2_no1Lep_L",   ";R2_{AK4}",         nbn_R2,bn_R2);
	h_MET_no1Lep_L = new TH1D("MET_no1Lep_L", ";MET", 400,0,2000);
	h_nLep_no1Lep_L = new TH1D("nLep_no1Lep_L", ";# of Lepton", 10,0,10);

	h_ht_AK4_no0b_L = new TH1D("ht_AK4_no0b_L",  ";H_{T}",                  nbn_HT, bn_HT);
	h_MR_no0b_L = new TH1D("MR_no0b_L",   ";MR_{AK4}",         nbn_MR,bn_MR);
	h_R2_no0b_L = new TH1D("R2_no0b_L",   ";R2_{AK4}",         nbn_R2,bn_R2);
	h_MET_no0b_L = new TH1D("MET_no0b_L", ";MET", 400,0,2000);
	h_nb_no0b_L = new TH1D("nb_no0b_L", ";# of b jet", 10,0,10);

	h_ht_AK4_nomDPhi_L = new TH1D("ht_AK4_nomDPhi_L",  ";H_{T}",                  nbn_HT, bn_HT);
	h_MR_nomDPhi_L = new TH1D("MR_nomDPhi_L",   ";MR_{AK4}",         nbn_MR,bn_MR);
	h_R2_nomDPhi_L = new TH1D("R2_nomDPhi_L",   ";R2_{AK4}",         nbn_R2,bn_R2);
	h_MET_nomDPhi_L = new TH1D("MET_nomDPhi_L", ";MET", 400,0,2000);
	h_mDPhi_nomDPhi_L = new TH1D("mDPhi_nomDPhi_L", ";#Delta#phi_{megajets}", 64,0,3.2);

	h_ht_AK4_noMT_L = new TH1D("ht_AK4_noMT_L",  ";H_{T}",                  nbn_HT, bn_HT);
	h_MR_noMT_L = new TH1D("MR_noMT_L",   ";MR_{AK4}",         nbn_MR,bn_MR);
	h_R2_noMT_L = new TH1D("R2_noMT_L",   ";R2_{AK4}",         nbn_R2,bn_R2);
	h_MET_noMT_L = new TH1D("MET_noMT_L", ";MET", 400,0,2000);
	h_MT_noMT_L = new TH1D("MT_noMT_L", ";MT", 20,0,500);

	h_ht_AK4_no1Lep_L_nj45 = new TH1D("ht_AK4_no1Lep_L_nj45",  ";H_{T}",                  nbn_HT, bn_HT);
	h_MR_no1Lep_L_nj45 = new TH1D("MR_no1Lep_L_nj45",   ";MR_{AK4}",         nbn_MR,bn_MR);
	h_R2_no1Lep_L_nj45 = new TH1D("R2_no1Lep_L_nj45",   ";R2_{AK4}",         nbn_R2,bn_R2);
	h_MET_no1Lep_L_nj45 = new TH1D("MET_no1Lep_L_nj45", ";MET", 400,0,2000);
	h_nLep_no1Lep_L_nj45 = new TH1D("nLep_no1Lep_L_nj45", ";# of Lepton", 10,0,10);

	h_ht_AK4_no0b_L_nj45 = new TH1D("ht_AK4_no0b_L_nj45",  ";H_{T}",                  nbn_HT, bn_HT);
	h_MR_no0b_L_nj45 = new TH1D("MR_no0b_L_nj45",   ";MR_{AK4}",         nbn_MR,bn_MR);
	h_R2_no0b_L_nj45 = new TH1D("R2_no0b_L_nj45",   ";R2_{AK4}",         nbn_R2,bn_R2);
	h_MET_no0b_L_nj45 = new TH1D("MET_no0b_L_nj45", ";MET", 400,0,2000);
	h_nb_no0b_L_nj45 = new TH1D("nb_no0b_L_nj45", ";# of b jet", 10,0,10);

	h_ht_AK4_nomDPhi_L_nj45 = new TH1D("ht_AK4_nomDPhi_L_nj45",  ";H_{T}",                  nbn_HT, bn_HT);
	h_MR_nomDPhi_L_nj45 = new TH1D("MR_nomDPhi_L_nj45",   ";MR_{AK4}",         nbn_MR,bn_MR);
	h_R2_nomDPhi_L_nj45 = new TH1D("R2_nomDPhi_L_nj45",   ";R2_{AK4}",         nbn_R2,bn_R2);
	h_MET_nomDPhi_L_nj45 = new TH1D("MET_nomDPhi_L_nj45", ";MET", 400,0,2000);
	h_mDPhi_nomDPhi_L_nj45 = new TH1D("mDPhi_nomDPhi_L_nj45", ";#Delta#phi_{megajets}", 64,0,3.2);

	h_ht_AK4_noMT_L_nj45 = new TH1D("ht_AK4_noMT_L_nj45",  ";H_{T}",                  nbn_HT, bn_HT);
	h_MR_noMT_L_nj45 = new TH1D("MR_noMT_L_nj45",   ";MR_{AK4}",         nbn_MR,bn_MR);
	h_R2_noMT_L_nj45 = new TH1D("R2_noMT_L_nj45",   ";R2_{AK4}",         nbn_R2,bn_R2);
	h_MET_noMT_L_nj45 = new TH1D("MET_noMT_L_nj45", ";MET", 400,0,2000);
	h_MT_noMT_L_nj45 = new TH1D("MT_noMT_L_nj45", ";MT", 20,0,500);

	h_ht_AK4_no1Lep_L_nj6 = new TH1D("ht_AK4_no1Lep_L_nj6",  ";H_{T}",                  nbn_HT, bn_HT);
	h_MR_no1Lep_L_nj6 = new TH1D("MR_no1Lep_L_nj6",   ";MR_{AK4}",         nbn_MR,bn_MR);
	h_R2_no1Lep_L_nj6 = new TH1D("R2_no1Lep_L_nj6",   ";R2_{AK4}",         nbn_R2,bn_R2);
	h_MET_no1Lep_L_nj6 = new TH1D("MET_no1Lep_L_nj6", ";MET", 400,0,2000);
	h_nLep_no1Lep_L_nj6 = new TH1D("nLep_no1Lep_L_nj6", ";# of Lepton", 10,0,10);

	h_ht_AK4_no0b_L_nj6 = new TH1D("ht_AK4_no0b_L_nj6",  ";H_{T}",                  nbn_HT, bn_HT);
	h_MR_no0b_L_nj6 = new TH1D("MR_no0b_L_nj6",   ";MR_{AK4}",         nbn_MR,bn_MR);
	h_R2_no0b_L_nj6 = new TH1D("R2_no0b_L_nj6",   ";R2_{AK4}",         nbn_R2,bn_R2);
	h_MET_no0b_L_nj6 = new TH1D("MET_no0b_L_nj6", ";MET", 400,0,2000);
	h_nb_no0b_L_nj6 = new TH1D("nb_no0b_L_nj6", ";# of b jet", 10,0,10);

	h_ht_AK4_nomDPhi_L_nj6 = new TH1D("ht_AK4_nomDPhi_L_nj6",  ";H_{T}",                  nbn_HT, bn_HT);
	h_MR_nomDPhi_L_nj6 = new TH1D("MR_nomDPhi_L_nj6",   ";MR_{AK4}",         nbn_MR,bn_MR);
	h_R2_nomDPhi_L_nj6 = new TH1D("R2_nomDPhi_L_nj6",   ";R2_{AK4}",         nbn_R2,bn_R2);
	h_MET_nomDPhi_L_nj6 = new TH1D("MET_nomDPhi_L_nj6", ";MET", 400,0,2000);
	h_mDPhi_nomDPhi_L_nj6 = new TH1D("mDPhi_nomDPhi_L_nj6", ";#Delta#phi_{megajets}", 64,0,3.2);

	h_ht_AK4_noMT_L_nj6 = new TH1D("ht_AK4_noMT_L_nj6",  ";H_{T}",                  nbn_HT, bn_HT);
	h_MR_noMT_L_nj6 = new TH1D("MR_noMT_L_nj6",   ";MR_{AK4}",         nbn_MR,bn_MR);
	h_R2_noMT_L_nj6 = new TH1D("R2_noMT_L_nj6",   ";R2_{AK4}",         nbn_R2,bn_R2);
	h_MET_noMT_L_nj6 = new TH1D("MET_noMT_L_nj6", ";MET", 400,0,2000);
	h_MT_noMT_L_nj6 = new TH1D("MT_noMT_L_nj6", ";MT", 20,0,500);

#if TOP == 0
	h_ht_AK4_nonW_L = new TH1D("ht_AK4_nonW_L",  ";H_{T}",                  nbn_HT, bn_HT);
	h_MR_nonW_L = new TH1D("MR_nonW_L",   ";MR_{AK4}",         nbn_MR,bn_MR);
	h_R2_nonW_L = new TH1D("R2_nonW_L",   ";R2_{AK4}",         nbn_R2,bn_R2);
	h_MET_nonW_L = new TH1D("MET_nonW_L", ";MET", 400,0,2000);
	h_nW_nonW_L = new TH1D("nW_nonW_L", ";# of Wjet", 10,0,10);

	h_ht_AK4_nonW_L_nj45 = new TH1D("ht_AK4_nonW_L_nj45",  ";H_{T}",                  nbn_HT, bn_HT);
	h_MR_nonW_L_nj45 = new TH1D("MR_nonW_L_nj45",   ";MR_{AK4}",         nbn_MR,bn_MR);
	h_R2_nonW_L_nj45 = new TH1D("R2_nonW_L_nj45",   ";R2_{AK4}",         nbn_R2,bn_R2);
	h_MET_nonW_L_nj45 = new TH1D("MET_nonW_L_nj45", ";MET", 400,0,2000);
	h_nW_nonW_L_nj45 = new TH1D("nW_nonW_L_nj45", ";# of Wjet", 10,0,10);

	h_ht_AK4_nonW_L_nj6 = new TH1D("ht_AK4_nonW_L_nj6",  ";H_{T}",                  nbn_HT, bn_HT);
	h_MR_nonW_L_nj6 = new TH1D("MR_nonW_L_nj6",   ";MR_{AK4}",         nbn_MR,bn_MR);
	h_R2_nonW_L_nj6 = new TH1D("R2_nonW_L_nj6",   ";R2_{AK4}",         nbn_R2,bn_R2);
	h_MET_nonW_L_nj6 = new TH1D("MET_nonW_L_nj6", ";MET", 400,0,2000);
	h_nW_nonW_L_nj6 = new TH1D("nW_nonW_L_nj6", ";# of Wjet", 10,0,10);
#else
	h_ht_AK4_nonTop_L = new TH1D("ht_AK4_nonTop_L",  ";H_{T}",                  nbn_HT, bn_HT);
	h_MR_nonTop_L = new TH1D("MR_nonTop_L",   ";MR_{AK4}",         nbn_MR,bn_MR);
	h_R2_nonTop_L = new TH1D("R2_nonTop_L",   ";R2_{AK4}",         nbn_R2,bn_R2);
	h_MET_nonTop_L = new TH1D("MET_nonTop_L", ";MET", 400,0,2000);
	h_nTop_nonTop_L = new TH1D("nTop_nonTop_L", ";# of Topjet", 10,0,10);

	h_ht_AK4_nonTop_L_nj45 = new TH1D("ht_AK4_nonTop_L_nj45",  ";H_{T}",                  nbn_HT, bn_HT);
	h_MR_nonTop_L_nj45 = new TH1D("MR_nonTop_L_nj45",   ";MR_{AK4}",         nbn_MR,bn_MR);
	h_R2_nonTop_L_nj45 = new TH1D("R2_nonTop_L_nj45",   ";R2_{AK4}",         nbn_R2,bn_R2);
	h_MET_nonTop_L_nj45 = new TH1D("MET_nonTop_L_nj45", ";MET", 400,0,2000);
	h_nTop_nonTop_L_nj45 = new TH1D("nTop_nonTop_L_nj45", ";# of Topjet", 10,0,10);

	h_ht_AK4_nonTop_L_nj6 = new TH1D("ht_AK4_nonTop_L_nj6",  ";H_{T}",                  nbn_HT, bn_HT);
	h_MR_nonTop_L_nj6 = new TH1D("MR_nonTop_L_nj6",   ";MR_{AK4}",         nbn_MR,bn_MR);
	h_R2_nonTop_L_nj6 = new TH1D("R2_nonTop_L_nj6",   ";R2_{AK4}",         nbn_R2,bn_R2);
	h_MET_nonTop_L_nj6 = new TH1D("MET_nonTop_L_nj6", ";MET", 400,0,2000);
	h_nTop_nonTop_L_nj6 = new TH1D("nTop_nonTop_L_nj6", ";# of Topjet", 10,0,10);
#endif

	h_ht_AK4_G = new TH1D("ht_AK4_G",  ";H_{T}",                  nbn_HT, bn_HT);
	h_MR_G = new TH1D("MR_G",   ";MR_{AK4}",     nbn_MR,    bn_MR);
	h_R2_G = new TH1D("R2_G",   ";R2_{AK4}",         nbn_R2,bn_R2);
	h_MET_G = new TH1D("MET_G", ";MET", 400,0,2000);
	h_MET_phi_G = new TH1D("MET_phi_G", ";#phi_{MET}", 640, -3.2,3.2);
	h_MET_phi_G_nj45 = new TH1D("MET_phi_G_nj45", ";#phi_{MET}", 640, -3.2,3.2);
	h_MET_phi_G_nj6 = new TH1D("MET_phi_G_nj6", ";#phi_{MET}", 640, -3.2,3.2);

	h_ht_AK4_G_nj45 = new TH1D("ht_AK4_G_nj45",  ";H_{T}",                  nbn_HT, bn_HT);
	h_MR_G_nj45 = new TH1D("MR_G_nj45",   ";MR_{AK4}",     nbn_MR,    bn_MR);
	h_R2_G_nj45 = new TH1D("R2_G_nj45",   ";R2_{AK4}",         nbn_R2,bn_R2);
	h_MET_G_nj45 = new TH1D("MET_G_nj45", ";MET", 400,0,2000);

	h_ht_AK4_G_nj6 = new TH1D("ht_AK4_G_nj6",  ";H_{T}",                  nbn_HT, bn_HT);
	h_MR_G_nj6 = new TH1D("MR_G_nj6",   ";MR_{AK4}",     nbn_MR,    bn_MR);
	h_R2_G_nj6 = new TH1D("R2_G_nj6",   ";R2_{AK4}",         nbn_R2,bn_R2);
	h_MET_G_nj6 = new TH1D("MET_G_nj6", ";MET", 400,0,2000);
	h_MET_pho_G = new TH1D("MET_pho_G", ";MET", 400,0,2000);
	h_MET_pho_G_nj45 = new TH1D("MET_pho_G_nj45", ";MET", 400,0,2000);
	h_MET_pho_G_nj6 = new TH1D("MET_pho_G_nj6", ";MET", 400,0,2000);

	h_ht_AK4_no0Lep_G = new TH1D("ht_AK4_0Lep_G",  ";H_{T}",                  nbn_HT, bn_HT);
	h_MR_no0Lep_G = new TH1D("MR_0Lep_G",   ";MR_{AK4}",         nbn_MR,bn_MR);
	h_R2_no0Lep_G = new TH1D("R2_0Lep_G",   ";R2_{AK4}",         nbn_R2,bn_R2);
	h_MET_no0Lep_G = new TH1D("MET_0Lep_G", ";MET", 400,0,2000);
	h_nLep_no0Lep_G = new TH1D("nLep_0Lep_G", ";# of Lepton", 10,0,10);

	h_ht_AK4_no1Pho_G = new TH1D("ht_AK4_1Pho_G",  ";H_{T}",                  nbn_HT, bn_HT);
	h_MR_no1Pho_G = new TH1D("MR_1Pho_G",   ";MR_{AK4}",         nbn_MR,bn_MR);
	h_R2_no1Pho_G = new TH1D("R2_1Pho_G",   ";R2_{AK4}",         nbn_R2,bn_R2);
	h_MET_no1Pho_G = new TH1D("MET_1Pho_G", ";MET", 400,0,2000);
	h_nPho_no1Pho_G = new TH1D("nPho_1Pho_G", ";# of photon", 10,0,10);

	h_ht_AK4_nomDPhi_G = new TH1D("ht_AK4_nomDPhi_G",  ";H_{T}",                  nbn_HT, bn_HT);
	h_MR_nomDPhi_G = new TH1D("MR_nomDPhi_G",   ";MR_{AK4}",         nbn_MR,bn_MR);
	h_R2_nomDPhi_G = new TH1D("R2_nomDPhi_G",   ";R2_{AK4}",         nbn_R2,bn_R2);
	h_MET_nomDPhi_G = new TH1D("MET_nomDPhi_G", ";MET", 400,0,2000);
	h_mDPhi_nomDPhi_G = new TH1D("mDPhi_nomDPhi_G", ";#Delta#phi_{megajets}", 64,0,3.2);

	h_ht_AK4_no0Lep_G_nj45 = new TH1D("ht_AK4_0Lep_G_nj45",  ";H_{T}",                  nbn_HT, bn_HT);
	h_MR_no0Lep_G_nj45 = new TH1D("MR_0Lep_G_nj45",   ";MR_{AK4}",         nbn_MR,bn_MR);
	h_R2_no0Lep_G_nj45 = new TH1D("R2_0Lep_G_nj45",   ";R2_{AK4}",         nbn_R2,bn_R2);
	h_MET_no0Lep_G_nj45 = new TH1D("MET_0Lep_G_nj45", ";MET", 400,0,2000);
	h_nLep_no0Lep_G_nj45 = new TH1D("nLep_0Lep_G_nj45", ";# of Lepton", 10,0,10);

	h_ht_AK4_no1Pho_G_nj45 = new TH1D("ht_AK4_1Pho_G_nj45",  ";H_{T}",                  nbn_HT, bn_HT);
	h_MR_no1Pho_G_nj45 = new TH1D("MR_1Pho_G_nj45",   ";MR_{AK4}",         nbn_MR,bn_MR);
	h_R2_no1Pho_G_nj45 = new TH1D("R2_1Pho_G_nj45",   ";R2_{AK4}",         nbn_R2,bn_R2);
	h_MET_no1Pho_G_nj45 = new TH1D("MET_1Pho_G_nj45", ";MET", 400,0,2000);
	h_nPho_no1Pho_G_nj45 = new TH1D("nPho_1Pho_G_nj45", ";# of photon", 10,0,10);

	h_ht_AK4_nomDPhi_G_nj45 = new TH1D("ht_AK4_nomDPhi_G_nj45",  ";H_{T}",                  nbn_HT, bn_HT);
	h_MR_nomDPhi_G_nj45 = new TH1D("MR_nomDPhi_G_nj45",   ";MR_{AK4}",         nbn_MR,bn_MR);
	h_R2_nomDPhi_G_nj45 = new TH1D("R2_nomDPhi_G_nj45",   ";R2_{AK4}",         nbn_R2,bn_R2);
	h_MET_nomDPhi_G_nj45 = new TH1D("MET_nomDPhi_G_nj45", ";MET", 400,0,2000);
	h_mDPhi_nomDPhi_G_nj45 = new TH1D("mDPhi_nomDPhi_G_nj45", ";#Delta#phi_{megajets}", 64,0,3.2);

	h_ht_AK4_no0Lep_G_nj6 = new TH1D("ht_AK4_0Lep_G_nj6",  ";H_{T}",                  nbn_HT, bn_HT);
	h_MR_no0Lep_G_nj6 = new TH1D("MR_0Lep_G_nj6",   ";MR_{AK4}",         nbn_MR,bn_MR);
	h_R2_no0Lep_G_nj6 = new TH1D("R2_0Lep_G_nj6",   ";R2_{AK4}",         nbn_R2,bn_R2);
	h_MET_no0Lep_G_nj6 = new TH1D("MET_0Lep_G_nj6", ";MET", 400,0,2000);
	h_nLep_no0Lep_G_nj6 = new TH1D("nLep_0Lep_G_nj6", ";# of Lepton", 10,0,10);

	h_ht_AK4_no1Pho_G_nj6 = new TH1D("ht_AK4_1Pho_G_nj6",  ";H_{T}",                  nbn_HT, bn_HT);
	h_MR_no1Pho_G_nj6 = new TH1D("MR_1Pho_G_nj6",   ";MR_{AK4}",         nbn_MR,bn_MR);
	h_R2_no1Pho_G_nj6 = new TH1D("R2_1Pho_G_nj6",   ";R2_{AK4}",         nbn_R2,bn_R2);
	h_MET_no1Pho_G_nj6 = new TH1D("MET_1Pho_G_nj6", ";MET", 400,0,2000);
	h_nPho_no1Pho_G_nj6 = new TH1D("nPho_1Pho_G_nj6", ";# of photon", 10,0,10);

	h_ht_AK4_nomDPhi_G_nj6 = new TH1D("ht_AK4_nomDPhi_G_nj6",  ";H_{T}",                  nbn_HT, bn_HT);
	h_MR_nomDPhi_G_nj6 = new TH1D("MR_nomDPhi_G_nj6",   ";MR_{AK4}",         nbn_MR,bn_MR);
	h_R2_nomDPhi_G_nj6 = new TH1D("R2_nomDPhi_G_nj6",   ";R2_{AK4}",         nbn_R2,bn_R2);
	h_MET_nomDPhi_G_nj6 = new TH1D("MET_nomDPhi_G_nj6", ";MET", 400,0,2000);
	h_mDPhi_nomDPhi_G_nj6 = new TH1D("mDPhi_nomDPhi_G_nj6", ";#Delta#phi_{megajets}", 64,0,3.2);

#if TOP == 0
	h_ht_AK4_nonW_G = new TH1D("ht_AK4_nonW_G",  ";H_{T}",                  nbn_HT, bn_HT);
	h_MR_nonW_G = new TH1D("MR_nonW_G",   ";MR_{AK4}",         nbn_MR,bn_MR);
	h_R2_nonW_G = new TH1D("R2_nonW_G",   ";R2_{AK4}",         nbn_R2,bn_R2);
	h_MET_nonW_G = new TH1D("MET_nonW_G", ";MET", 400,0,2000);
	h_nW_nonW_G = new TH1D("nW_nonW_G", ";# of Wjet", 10,0,10);

	h_ht_AK4_nonW_G_nj45 = new TH1D("ht_AK4_nonW_G_nj45",  ";H_{T}",                  nbn_HT, bn_HT);
	h_MR_nonW_G_nj45 = new TH1D("MR_nonW_G_nj45",   ";MR_{AK4}",         nbn_MR,bn_MR);
	h_R2_nonW_G_nj45 = new TH1D("R2_nonW_G_nj45",   ";R2_{AK4}",         nbn_R2,bn_R2);
	h_MET_nonW_G_nj45 = new TH1D("MET_nonW_G_nj45", ";MET", 400,0,2000);
	h_nW_nonW_G_nj45 = new TH1D("nW_nonW_G_nj45", ";# of Wjet", 10,0,10);

	h_ht_AK4_nonW_G_nj6 = new TH1D("ht_AK4_nonW_G_nj6",  ";H_{T}",                  nbn_HT, bn_HT);
	h_MR_nonW_G_nj6 = new TH1D("MR_nonW_G_nj6",   ";MR_{AK4}",         nbn_MR,bn_MR);
	h_R2_nonW_G_nj6 = new TH1D("R2_nonW_G_nj6",   ";R2_{AK4}",         nbn_R2,bn_R2);
	h_MET_nonW_G_nj6 = new TH1D("MET_nonW_G_nj6", ";MET", 400,0,2000);
	h_nW_nonW_G_nj6 = new TH1D("nW_nonW_G_nj6", ";# of Wjet", 10,0,10);
#else
	h_ht_AK4_nonTop_G = new TH1D("ht_AK4_nonTop_G",  ";H_{T}",                  nbn_HT, bn_HT);
	h_MR_nonTop_G = new TH1D("MR_nonTop_G",   ";MR_{AK4}",         nbn_MR,bn_MR);
	h_R2_nonTop_G = new TH1D("R2_nonTop_G",   ";R2_{AK4}",         nbn_R2,bn_R2);
	h_MET_nonTop_G = new TH1D("MET_nonTop_G", ";MET", 400,0,2000);
	h_nTop_nonTop_G = new TH1D("nTop_nonTop_G", ";# of Topjet", 10,0,10);

	h_ht_AK4_nonTop_G_nj45 = new TH1D("ht_AK4_nonTop_G_nj45",  ";H_{T}",                  nbn_HT, bn_HT);
	h_MR_nonTop_G_nj45 = new TH1D("MR_nonTop_G_nj45",   ";MR_{AK4}",         nbn_MR,bn_MR);
	h_R2_nonTop_G_nj45 = new TH1D("R2_nonTop_G_nj45",   ";R2_{AK4}",         nbn_R2,bn_R2);
	h_MET_nonTop_G_nj45 = new TH1D("MET_nonTop_G_nj45", ";MET", 400,0,2000);
	h_nTop_nonTop_G_nj45 = new TH1D("nTop_nonTop_G_nj45", ";# of Topjet", 10,0,10);

	h_ht_AK4_nonTop_G_nj6 = new TH1D("ht_AK4_nonTop_G_nj6",  ";H_{T}",                  nbn_HT, bn_HT);
	h_MR_nonTop_G_nj6 = new TH1D("MR_nonTop_G_nj6",   ";MR_{AK4}",         nbn_MR,bn_MR);
	h_R2_nonTop_G_nj6 = new TH1D("R2_nonTop_G_nj6",   ";R2_{AK4}",         nbn_R2,bn_R2);
	h_MET_nonTop_G_nj6 = new TH1D("MET_nonTop_G_nj6", ";MET", 400,0,2000);
	h_nTop_nonTop_G_nj6 = new TH1D("nTop_nonTop_G_nj6", ";# of Topjet", 10,0,10);
#endif

	//h_MR_S_nj6 = new TH1D("MR_S_nj6",";MR_{AK4}",nbn_MR,bn_MR);
	//h_MR_S_nj45 = new TH1D("MR_S_nj45",";MR_{AK4}",nbn_MR,bn_MR);
	//h_R2_S_nj6 = new TH1D("R2_S_nj6",";R2_{AK4}",nbn_R2,bn_R2);
	//h_R2_S_nj45 = new TH1D("R2_S_nj45",";R2_{AK4}",nbn_R2,bn_R2);

	//h_MR_Q_nj6 = new TH1D("MR_Q_nj6",";MR_{AK4}",nbn_MR,bn_MR);
	//h_MR_Q_nj45 = new TH1D("MR_Q_nj45",";MR_{AK4}",nbn_MR,bn_MR);
	//h_R2_Q_nj45 = new TH1D("R2_Q_nj45",";R2_{AK4}",nbn_R2,bn_R2);
	//h_R2_Q_nj6 = new TH1D("R2_Q_nj6",";R2_{AK4}",nbn_R2,bn_R2);

	//h_MR_T_nj6 = new TH1D("MR_T_nj6",";MR_{AK4}",nbn_MR,bn_MR);
	//h_MR_T_nj45 = new TH1D("MR_T_nj45",";MR_{AK4}",nbn_MR,bn_MR);
	//h_R2_T_nj45 = new TH1D("R2_T_nj45",";R2_{AK4}",nbn_R2,bn_R2);
	//h_R2_T_nj6 = new TH1D("R2_T_nj6",";R2_{AK4}",nbn_R2,bn_R2);

	//h_MR_W_nj6 = new TH1D("MR_W_nj6",";MR_{AK4}",nbn_MR,bn_MR);
	//h_MR_W_nj45 = new TH1D("MR_W_nj45",";MR_{AK4}",nbn_MR,bn_MR);
	//h_R2_W_nj45 = new TH1D("R2_W_nj45",";R2_{AK4}",nbn_R2,bn_R2);
	//h_R2_W_nj6 = new TH1D("R2_W_nj6",";R2_{AK4}",nbn_R2,bn_R2);

	h_ht_AK4_Q = new TH1D("ht_AK4_Q",  ";H_{T}",                  nbn_HT, bn_HT);
	h_MR_Q = new TH1D("MR_Q",   ";MR_{AK4}",         nbn_MR,bn_MR);
	h_R2_Q = new TH1D("R2_Q",   ";R2_{AK4}",         nbn_R2,bn_R2);
	h_MET_Q = new TH1D("MET_Q", ";MET", 400,0,2000);
	h_MET_phi_Q = new TH1D("MET_phi_Q", ";#phi_{MET}", 640, -3.2,3.2);
	h_MET_phi_Q_nj45 = new TH1D("MET_phi_Q_nj45", ";#phi_{MET}", 640, -3.2,3.2);
	h_MET_phi_Q_nj6 = new TH1D("MET_phi_Q_nj6", ";#phi_{MET}", 640, -3.2,3.2);

	h_ht_AK4_nomDPhi_Q = new TH1D("ht_AK4_nomDPhi_Q",  ";H_{T}",                  nbn_HT, bn_HT);
	h_MR_nomDPhi_Q = new TH1D("MR_nomDPhi_Q",   ";MR_{AK4}",         nbn_MR,bn_MR);
	h_R2_nomDPhi_Q = new TH1D("R2_nomDPhi_Q",   ";R2_{AK4}",         nbn_R2,bn_R2);
	h_MET_nomDPhi_Q = new TH1D("MET_nomDPhi_Q", ";MET", 400,0,2000);
	h_mDPhi_nomDPhi_Q = new TH1D("mDPhi_nomDPhi_Q", ";#Delta#phi_{megajets}", 64,0,3.2);

	h_ht_AK4_no0Lep_Q = new TH1D("ht_AK4_no0Lep_Q",  ";H_{T}",                  nbn_HT, bn_HT);
	h_MR_no0Lep_Q = new TH1D("MR_no0Lep_Q",   ";MR_{AK4}",         nbn_MR,bn_MR);
	h_R2_no0Lep_Q = new TH1D("R2_no0Lep_Q",   ";R2_{AK4}",         nbn_R2,bn_R2);
	h_MET_no0Lep_Q = new TH1D("MET_no0Lep_Q", ";MET", 400,0,2000);
	h_nLep_no0Lep_Q = new TH1D("nLep_no0Lep_Q", ";# of lepton", 10,0,10);

	h_ht_AK4_nonb_Q = new TH1D("ht_AK4_nonb_Q",  ";H_{T}",                  nbn_HT, bn_HT);
	h_MR_nonb_Q = new TH1D("MR_nonb_Q",   ";MR_{AK4}",         nbn_MR,bn_MR);
	h_R2_nonb_Q = new TH1D("R2_nonb_Q",   ";R2_{AK4}",         nbn_R2,bn_R2);
	h_MET_nonb_Q = new TH1D("MET_nonb_Q", ";MET", 400,0,2000);
	h_nb_nonb_Q = new TH1D("nb_nonb_Q", ";# of b jet", 10,0,10);

	h_ht_AK4_Q_nj45 = new TH1D("ht_AK4_Q_nj45",  ";H_{T}",                  nbn_HT, bn_HT);
	h_MR_Q_nj45 = new TH1D("MR_Q_nj45",   ";MR_{AK4}",         nbn_MR,bn_MR);
	h_R2_Q_nj45 = new TH1D("R2_Q_nj45",   ";R2_{AK4}",         nbn_R2,bn_R2);
	h_MET_Q_nj45 = new TH1D("MET_Q_nj45", ";MET", 400,0,2000);

	h_ht_AK4_nomDPhi_Q_nj45 = new TH1D("ht_AK4_nomDPhi_Q_nj45",  ";H_{T}",                  nbn_HT, bn_HT);
	h_MR_nomDPhi_Q_nj45 = new TH1D("MR_nomDPhi_Q_nj45",   ";MR_{AK4}",         nbn_MR,bn_MR);
	h_R2_nomDPhi_Q_nj45 = new TH1D("R2_nomDPhi_Q_nj45",   ";R2_{AK4}",         nbn_R2,bn_R2);
	h_MET_nomDPhi_Q_nj45 = new TH1D("MET_nomDPhi_Q_nj45", ";MET", 400,0,2000);
	h_mDPhi_nomDPhi_Q_nj45 = new TH1D("mDPhi_nomDPhi_Q_nj45", ";#Delta#phi_{megajets}", 64,0,3.2);

	h_ht_AK4_no0Lep_Q_nj45 = new TH1D("ht_AK4_no0Lep_Q_nj45",  ";H_{T}",                  nbn_HT, bn_HT);
	h_MR_no0Lep_Q_nj45 = new TH1D("MR_no0Lep_Q_nj45",   ";MR_{AK4}",         nbn_MR,bn_MR);
	h_R2_no0Lep_Q_nj45 = new TH1D("R2_no0Lep_Q_nj45",   ";R2_{AK4}",         nbn_R2,bn_R2);
	h_MET_no0Lep_Q_nj45 = new TH1D("MET_no0Lep_Q_nj45", ";MET", 400,0,2000);
	h_nLep_no0Lep_Q_nj45 = new TH1D("nLep_no0Lep_Q_nj45", ";# of lepton", 10,0,10);

	h_ht_AK4_nonb_Q_nj45 = new TH1D("ht_AK4_nonb_Q_nj45",  ";H_{T}",                  nbn_HT, bn_HT);
	h_MR_nonb_Q_nj45 = new TH1D("MR_nonb_Q_nj45",   ";MR_{AK4}",         nbn_MR,bn_MR);
	h_R2_nonb_Q_nj45 = new TH1D("R2_nonb_Q_nj45",   ";R2_{AK4}",         nbn_R2,bn_R2);
	h_MET_nonb_Q_nj45 = new TH1D("MET_nonb_Q_nj45", ";MET", 400,0,2000);
	h_nb_nonb_Q_nj45 = new TH1D("nb_nonb_Q_nj45", ";# of b jet", 10,0,10);

	h_ht_AK4_Q_nj6 = new TH1D("ht_AK4_Q_nj6",  ";H_{T}",                  nbn_HT, bn_HT);
	h_MR_Q_nj6 = new TH1D("MR_Q_nj6",   ";MR_{AK4}",         nbn_MR,bn_MR);
	h_R2_Q_nj6 = new TH1D("R2_Q_nj6",   ";R2_{AK4}",         nbn_R2,bn_R2);
	h_MET_Q_nj6 = new TH1D("MET_Q_nj6", ";MET", 400,0,2000);

	h_ht_AK4_nomDPhi_Q_nj6 = new TH1D("ht_AK4_nomDPhi_Q_nj6",  ";H_{T}",                  nbn_HT, bn_HT);
	h_MR_nomDPhi_Q_nj6 = new TH1D("MR_nomDPhi_Q_nj6",   ";MR_{AK4}",         nbn_MR,bn_MR);
	h_R2_nomDPhi_Q_nj6 = new TH1D("R2_nomDPhi_Q_nj6",   ";R2_{AK4}",         nbn_R2,bn_R2);
	h_MET_nomDPhi_Q_nj6 = new TH1D("MET_nomDPhi_Q_nj6", ";MET", 400,0,2000);
	h_mDPhi_nomDPhi_Q_nj6 = new TH1D("mDPhi_nomDPhi_Q_nj6", ";#Delta#phi_{megajets}", 64,0,3.2);

	h_ht_AK4_no0Lep_Q_nj6 = new TH1D("ht_AK4_no0Lep_Q_nj6",  ";H_{T}",                  nbn_HT, bn_HT);
	h_MR_no0Lep_Q_nj6 = new TH1D("MR_no0Lep_Q_nj6",   ";MR_{AK4}",         nbn_MR,bn_MR);
	h_R2_no0Lep_Q_nj6 = new TH1D("R2_no0Lep_Q_nj6",   ";R2_{AK4}",         nbn_R2,bn_R2);
	h_MET_no0Lep_Q_nj6 = new TH1D("MET_no0Lep_Q_nj6", ";MET", 400,0,2000);
	h_nLep_no0Lep_Q_nj6 = new TH1D("nLep_no0Lep_Q_nj6", ";# of lepton", 10,0,10);

	h_ht_AK4_nonb_Q_nj6 = new TH1D("ht_AK4_nonb_Q_nj6",  ";H_{T}",                  nbn_HT, bn_HT);
	h_MR_nonb_Q_nj6 = new TH1D("MR_nonb_Q_nj6",   ";MR_{AK4}",         nbn_MR,bn_MR);
	h_R2_nonb_Q_nj6 = new TH1D("R2_nonb_Q_nj6",   ";R2_{AK4}",         nbn_R2,bn_R2);
	h_MET_nonb_Q_nj6 = new TH1D("MET_nonb_Q_nj6", ";MET", 400,0,2000);
	h_nb_nonb_Q_nj6 = new TH1D("nb_nonb_Q_nj6", ";# of b jet", 10,0,10);

#if TOP == 0
	h_ht_AK4_nonW_Q = new TH1D("ht_AK4_nonW_Q",  ";H_{T}",                  nbn_HT, bn_HT);
	h_MR_nonW_Q = new TH1D("MR_nonW_Q",   ";MR_{AK4}",         nbn_MR,bn_MR);
	h_R2_nonW_Q = new TH1D("R2_nonW_Q",   ";R2_{AK4}",         nbn_R2,bn_R2);
	h_MET_nonW_Q = new TH1D("MET_nonW_Q", ";MET", 400,0,2000);
	h_nW_nonW_Q = new TH1D("nW_nonW_Q", ";# of Wjet", 10,0,10);

	h_ht_AK4_nonW_Q_nj45 = new TH1D("ht_AK4_nonW_Q_nj45",  ";H_{T}",                  nbn_HT, bn_HT);
	h_MR_nonW_Q_nj45 = new TH1D("MR_nonW_Q_nj45",   ";MR_{AK4}",         nbn_MR,bn_MR);
	h_R2_nonW_Q_nj45 = new TH1D("R2_nonW_Q_nj45",   ";R2_{AK4}",         nbn_R2,bn_R2);
	h_MET_nonW_Q_nj45 = new TH1D("MET_nonW_Q_nj45", ";MET", 400,0,2000);
	h_nW_nonW_Q_nj45 = new TH1D("nW_nonW_Q_nj45", ";# of Wjet", 10,0,10);

	h_ht_AK4_nonW_Q_nj6 = new TH1D("ht_AK4_nonW_Q_nj6",  ";H_{T}",                  nbn_HT, bn_HT);
	h_MR_nonW_Q_nj6 = new TH1D("MR_nonW_Q_nj6",   ";MR_{AK4}",         nbn_MR,bn_MR);
	h_R2_nonW_Q_nj6 = new TH1D("R2_nonW_Q_nj6",   ";R2_{AK4}",         nbn_R2,bn_R2);
	h_MET_nonW_Q_nj6 = new TH1D("MET_nonW_Q_nj6", ";MET", 400,0,2000);
	h_nW_nonW_Q_nj6 = new TH1D("nW_nonW_Q_nj6", ";# of Wjet", 10,0,10);
#else
	h_ht_AK4_nonTop_Q = new TH1D("ht_AK4_nonTop_Q",  ";H_{T}",                  nbn_HT, bn_HT);
	h_MR_nonTop_Q = new TH1D("MR_nonTop_Q",   ";MR_{AK4}",         nbn_MR,bn_MR);
	h_R2_nonTop_Q = new TH1D("R2_nonTop_Q",   ";R2_{AK4}",         nbn_R2,bn_R2);
	h_MET_nonTop_Q = new TH1D("MET_nonTop_Q", ";MET", 400,0,2000);
	h_nTop_nonTop_Q = new TH1D("nTop_nonTop_Q", ";# of Topjet", 10,0,10);

	h_ht_AK4_nonTop_Q_nj45 = new TH1D("ht_AK4_nonTop_Q_nj45",  ";H_{T}",                  nbn_HT, bn_HT);
	h_MR_nonTop_Q_nj45 = new TH1D("MR_nonTop_Q_nj45",   ";MR_{AK4}",         nbn_MR,bn_MR);
	h_R2_nonTop_Q_nj45 = new TH1D("R2_nonTop_Q_nj45",   ";R2_{AK4}",         nbn_R2,bn_R2);
	h_MET_nonTop_Q_nj45 = new TH1D("MET_nonTop_Q_nj45", ";MET", 400,0,2000);
	h_nTop_nonTop_Q_nj45 = new TH1D("nTop_nonTop_Q_nj45", ";# of Topjet", 10,0,10);

	h_ht_AK4_nonTop_Q_nj6 = new TH1D("ht_AK4_nonTop_Q_nj6",  ";H_{T}",                  nbn_HT, bn_HT);
	h_MR_nonTop_Q_nj6 = new TH1D("MR_nonTop_Q_nj6",   ";MR_{AK4}",         nbn_MR,bn_MR);
	h_R2_nonTop_Q_nj6 = new TH1D("R2_nonTop_Q_nj6",   ";R2_{AK4}",         nbn_R2,bn_R2);
	h_MET_nonTop_Q_nj6 = new TH1D("MET_nonTop_Q_nj6", ";MET", 400,0,2000);
	h_nTop_nonTop_Q_nj6 = new TH1D("nTop_nonTop_Q_nj6", ";# of Topjet", 10,0,10);
#endif

	h_ht_AK4_T = new TH1D("ht_AK4_T",  ";H_{T}",                  nbn_HT, bn_HT);
	h_MR_T = new TH1D("MR_T",   ";MR_{AK4}",         nbn_MR,bn_MR);
	h_R2_T = new TH1D("R2_T",   ";R2_{AK4}",         nbn_R2,bn_R2);
	h_MET_T = new TH1D("MET_T", ";MET", 400,0,2000);
	h_MET_phi_T = new TH1D("MET_phi_T", ";#phi_{MET}", 640, -3.2,3.2);
	h_MET_phi_T_nj45 = new TH1D("MET_phi_T_nj45", ";#phi_{MET}", 640, -3.2,3.2);
	h_MET_phi_T_nj6 = new TH1D("MET_phi_T_nj6", ";#phi_{MET}", 640, -3.2,3.2);

#if TOP == 0
	h_ht_AK4_no1b_T = new TH1D("ht_AK4_no1b_T",  ";H_{T}",                  nbn_HT, bn_HT);
	h_MR_no1b_T = new TH1D("MR_no1b_T",   ";MR_{AK4}",         nbn_MR,bn_MR);
	h_R2_no1b_T = new TH1D("R2_no1b_T",   ";R2_{AK4}",         nbn_R2,bn_R2);
	h_MET_no1b_T = new TH1D("MET_no1b_T", ";MET", 400,0,2000);
	h_nb_no1b_T = new TH1D("nb_no1b_T", ";# of b jet", 10,0,10);
#endif
	h_ht_AK4_noMT_T = new TH1D("ht_AK4_noMT_T",  ";H_{T}",                  nbn_HT, bn_HT);
	h_MR_noMT_T = new TH1D("MR_noMT_T",   ";MR_{AK4}",         nbn_MR,bn_MR);
	h_R2_noMT_T = new TH1D("R2_noMT_T",   ";R2_{AK4}",         nbn_R2,bn_R2);
	h_MET_noMT_T = new TH1D("MET_noMT_T", ";MET", 400,0,2000);
	h_MT_noMT_T = new TH1D("MT_noMT_T", ";MT", 25,0,500);

	h_ht_AK4_nomDPhi_T = new TH1D("ht_AK4_nomDPhi_T",  ";H_{T}",                  nbn_HT, bn_HT);
	h_MR_nomDPhi_T = new TH1D("MR_nomDPhi_T",   ";MR_{AK4}",         nbn_MR,bn_MR);
	h_R2_nomDPhi_T = new TH1D("R2_nomDPhi_T",   ";R2_{AK4}",         nbn_R2,bn_R2);
	h_MET_nomDPhi_T = new TH1D("MET_nomDPhi_T", ";MET", 400,0,2000);
	h_mDPhi_nomDPhi_T = new TH1D("mDPhi_nomDPhi_T", ";#Delta#phi_{megajets}", 64,0,3.2);

	h_ht_AK4_no1Lep_T = new TH1D("ht_AK4_no1Lep_T",  ";H_{T}",                  nbn_HT, bn_HT);
	h_MR_no1Lep_T = new TH1D("MR_no1Lep_T",   ";MR_{AK4}",         nbn_MR,bn_MR);
	h_R2_no1Lep_T = new TH1D("R2_no1Lep_T",   ";R2_{AK4}",         nbn_R2,bn_R2);
	h_MET_no1Lep_T = new TH1D("MET_no1Lep_T", ";MET", 400,0,2000);
	h_nLep_no1Lep_T = new TH1D("nLep_no1Lep_T", ";# of Lepton", 10,0,10);

	h_ht_AK4_T_nj45 = new TH1D("ht_AK4_T_nj45",  ";H_{T}",                  nbn_HT, bn_HT);
	h_MR_T_nj45 = new TH1D("MR_T_nj45",   ";MR_{AK4}",         nbn_MR,bn_MR);
	h_R2_T_nj45 = new TH1D("R2_T_nj45",   ";R2_{AK4}",         nbn_R2,bn_R2);
	h_MET_T_nj45 = new TH1D("MET_T_nj45", ";MET", 400,0,2000);

#if TOP == 0
	h_ht_AK4_no1b_T_nj45 = new TH1D("ht_AK4_no1b_T_nj45",  ";H_{T}",                  nbn_HT, bn_HT);
	h_MR_no1b_T_nj45 = new TH1D("MR_no1b_T_nj45",   ";MR_{AK4}",         nbn_MR,bn_MR);
	h_R2_no1b_T_nj45 = new TH1D("R2_no1b_T_nj45",   ";R2_{AK4}",         nbn_R2,bn_R2);
	h_MET_no1b_T_nj45 = new TH1D("MET_no1b_T_nj45", ";MET", 400,0,2000);
	h_nb_no1b_T_nj45 = new TH1D("nb_no1b_T_nj45", ";# of b jet", 10,0,10);
#endif
	h_ht_AK4_noMT_T_nj45 = new TH1D("ht_AK4_noMT_T_nj45",  ";H_{T}",                  nbn_HT, bn_HT);
	h_MR_noMT_T_nj45 = new TH1D("MR_noMT_T_nj45",   ";MR_{AK4}",         nbn_MR,bn_MR);
	h_R2_noMT_T_nj45 = new TH1D("R2_noMT_T_nj45",   ";R2_{AK4}",         nbn_R2,bn_R2);
	h_MET_noMT_T_nj45 = new TH1D("MET_noMT_T_nj45", ";MET", 400,0,2000);
	h_MT_noMT_T_nj45 = new TH1D("MT_noMT_T_nj45", ";MT", 25,0,500);

	h_ht_AK4_nomDPhi_T_nj45 = new TH1D("ht_AK4_nomDPhi_T_nj45",  ";H_{T}",                  nbn_HT, bn_HT);
	h_MR_nomDPhi_T_nj45 = new TH1D("MR_nomDPhi_T_nj45",   ";MR_{AK4}",         nbn_MR,bn_MR);
	h_R2_nomDPhi_T_nj45 = new TH1D("R2_nomDPhi_T_nj45",   ";R2_{AK4}",         nbn_R2,bn_R2);
	h_MET_nomDPhi_T_nj45 = new TH1D("MET_nomDPhi_T_nj45", ";MET", 400,0,2000);
	h_mDPhi_nomDPhi_T_nj45 = new TH1D("mDPhi_nomDPhi_T_nj45", ";#Delta#phi_{megajets}", 64,0,3.2);

	h_ht_AK4_no1Lep_T_nj45 = new TH1D("ht_AK4_no1Lep_T_nj45",  ";H_{T}",                  nbn_HT, bn_HT);
	h_MR_no1Lep_T_nj45 = new TH1D("MR_no1Lep_T_nj45",   ";MR_{AK4}",         nbn_MR,bn_MR);
	h_R2_no1Lep_T_nj45 = new TH1D("R2_no1Lep_T_nj45",   ";R2_{AK4}",         nbn_R2,bn_R2);
	h_MET_no1Lep_T_nj45 = new TH1D("MET_no1Lep_T_nj45", ";MET", 400,0,2000);
	h_nLep_no1Lep_T_nj45 = new TH1D("nLep_no1Lep_T_nj45", ";# of Lepton", 10,0,10);

	h_ht_AK4_T_nj6 = new TH1D("ht_AK4_T_nj6",  ";H_{T}",                  nbn_HT, bn_HT);
	h_MR_T_nj6 = new TH1D("MR_T_nj6",   ";MR_{AK4}",         nbn_MR,bn_MR);
	h_R2_T_nj6 = new TH1D("R2_T_nj6",   ";R2_{AK4}",         nbn_R2,bn_R2);
	h_MET_T_nj6 = new TH1D("MET_T_nj6", ";MET", 400,0,2000);

#if TOP == 0
	h_ht_AK4_no1b_T_nj6 = new TH1D("ht_AK4_no1b_T_nj6",  ";H_{T}",                  nbn_HT, bn_HT);
	h_MR_no1b_T_nj6 = new TH1D("MR_no1b_T_nj6",   ";MR_{AK4}",         nbn_MR,bn_MR);
	h_R2_no1b_T_nj6 = new TH1D("R2_no1b_T_nj6",   ";R2_{AK4}",         nbn_R2,bn_R2);
	h_MET_no1b_T_nj6 = new TH1D("MET_no1b_T_nj6", ";MET", 400,0,2000);
	h_nb_no1b_T_nj6 = new TH1D("nb_no1b_T_nj6", ";# of b jet", 10,0,10);
#endif
	h_ht_AK4_noMT_T_nj6 = new TH1D("ht_AK4_noMT_T_nj6",  ";H_{T}",                  nbn_HT, bn_HT);
	h_MR_noMT_T_nj6 = new TH1D("MR_noMT_T_nj6",   ";MR_{AK4}",         nbn_MR,bn_MR);
	h_R2_noMT_T_nj6 = new TH1D("R2_noMT_T_nj6",   ";R2_{AK4}",         nbn_R2,bn_R2);
	h_MET_noMT_T_nj6 = new TH1D("MET_noMT_T_nj6", ";MET", 400,0,2000);
	h_MT_noMT_T_nj6 = new TH1D("MT_noMT_T_nj6", ";MT", 25,0,500);

	h_ht_AK4_nomDPhi_T_nj6 = new TH1D("ht_AK4_nomDPhi_T_nj6",  ";H_{T}",                  nbn_HT, bn_HT);
	h_MR_nomDPhi_T_nj6 = new TH1D("MR_nomDPhi_T_nj6",   ";MR_{AK4}",         nbn_MR,bn_MR);
	h_R2_nomDPhi_T_nj6 = new TH1D("R2_nomDPhi_T_nj6",   ";R2_{AK4}",         nbn_R2,bn_R2);
	h_MET_nomDPhi_T_nj6 = new TH1D("MET_nomDPhi_T_nj6", ";MET", 400,0,2000);
	h_mDPhi_nomDPhi_T_nj6 = new TH1D("mDPhi_nomDPhi_T_nj6", ";#Delta#phi_{megajets}", 64,0,3.2);

	h_ht_AK4_no1Lep_T_nj6 = new TH1D("ht_AK4_no1Lep_T_nj6",  ";H_{T}",                  nbn_HT, bn_HT);
	h_MR_no1Lep_T_nj6 = new TH1D("MR_no1Lep_T_nj6",   ";MR_{AK4}",         nbn_MR,bn_MR);
	h_R2_no1Lep_T_nj6 = new TH1D("R2_no1Lep_T_nj6",   ";R2_{AK4}",         nbn_R2,bn_R2);
	h_MET_no1Lep_T_nj6 = new TH1D("MET_no1Lep_T_nj6", ";MET", 400,0,2000);
	h_nLep_no1Lep_T_nj6 = new TH1D("nLep_no1Lep_T_nj6", ";# of Lepton", 10,0,10);

#if TOP == 0
	h_ht_AK4_nonW_T = new TH1D("ht_AK4_nonW_T",  ";H_{T}",                  nbn_HT, bn_HT);
	h_MR_nonW_T = new TH1D("MR_nonW_T",   ";MR_{AK4}",         nbn_MR,bn_MR);
	h_R2_nonW_T = new TH1D("R2_nonW_T",   ";R2_{AK4}",         nbn_R2,bn_R2);
	h_MET_nonW_T = new TH1D("MET_nonW_T", ";MET", 400,0,2000);
	h_nW_nonW_T = new TH1D("nW_nonW_T", ";# of Wjet", 10,0,10);

	h_ht_AK4_nonW_T_nj45 = new TH1D("ht_AK4_nonW_T_nj45",  ";H_{T}",                  nbn_HT, bn_HT);
	h_MR_nonW_T_nj45 = new TH1D("MR_nonW_T_nj45",   ";MR_{AK4}",         nbn_MR,bn_MR);
	h_R2_nonW_T_nj45 = new TH1D("R2_nonW_T_nj45",   ";R2_{AK4}",         nbn_R2,bn_R2);
	h_MET_nonW_T_nj45 = new TH1D("MET_nonW_T_nj45", ";MET", 400,0,2000);
	h_nW_nonW_T_nj45 = new TH1D("nW_nonW_T_nj45", ";# of Wjet", 10,0,10);

	h_ht_AK4_nonW_T_nj6 = new TH1D("ht_AK4_nonW_T_nj6",  ";H_{T}",                  nbn_HT, bn_HT);
	h_MR_nonW_T_nj6 = new TH1D("MR_nonW_T_nj6",   ";MR_{AK4}",         nbn_MR,bn_MR);
	h_R2_nonW_T_nj6 = new TH1D("R2_nonW_T_nj6",   ";R2_{AK4}",         nbn_R2,bn_R2);
	h_MET_nonW_T_nj6 = new TH1D("MET_nonW_T_nj6", ";MET", 400,0,2000);
	h_nW_nonW_T_nj6 = new TH1D("nW_nonW_T_nj6", ";# of Wjet", 10,0,10);
#else
	h_ht_AK4_nonTop_T = new TH1D("ht_AK4_nonTop_T",  ";H_{T}",                  nbn_HT, bn_HT);
	h_MR_nonTop_T = new TH1D("MR_nonTop_T",   ";MR_{AK4}",         nbn_MR,bn_MR);
	h_R2_nonTop_T = new TH1D("R2_nonTop_T",   ";R2_{AK4}",         nbn_R2,bn_R2);
	h_MET_nonTop_T = new TH1D("MET_nonTop_T", ";MET", 400,0,2000);
	h_nTop_nonTop_T = new TH1D("nTop_nonTop_T", ";# of Topjet", 10,0,10);

	h_ht_AK4_nonTop_T_nj45 = new TH1D("ht_AK4_nonTop_T_nj45",  ";H_{T}",                  nbn_HT, bn_HT);
	h_MR_nonTop_T_nj45 = new TH1D("MR_nonTop_T_nj45",   ";MR_{AK4}",         nbn_MR,bn_MR);
	h_R2_nonTop_T_nj45 = new TH1D("R2_nonTop_T_nj45",   ";R2_{AK4}",         nbn_R2,bn_R2);
	h_MET_nonTop_T_nj45 = new TH1D("MET_nonTop_T_nj45", ";MET", 400,0,2000);
	h_nTop_nonTop_T_nj45 = new TH1D("nTop_nonTop_T_nj45", ";# of Topjet", 10,0,10);

	h_ht_AK4_nonTop_T_nj6 = new TH1D("ht_AK4_nonTop_T_nj6",  ";H_{T}",                  nbn_HT, bn_HT);
	h_MR_nonTop_T_nj6 = new TH1D("MR_nonTop_T_nj6",   ";MR_{AK4}",         nbn_MR,bn_MR);
	h_R2_nonTop_T_nj6 = new TH1D("R2_nonTop_T_nj6",   ";R2_{AK4}",         nbn_R2,bn_R2);
	h_MET_nonTop_T_nj6 = new TH1D("MET_nonTop_T_nj6", ";MET", 400,0,2000);
	h_nTop_nonTop_T_nj6 = new TH1D("nTop_nonTop_T_nj6", ";# of Topjet", 10,0,10);
#endif

	h_ht_AK4_W = new TH1D("ht_AK4_W",  ";H_{T}",                  nbn_HT, bn_HT);
	h_MR_W = new TH1D("MR_W",   ";MR_{AK4}",         nbn_MR,bn_MR);
	h_R2_W = new TH1D("R2_W",   ";R2_{AK4}",         nbn_R2,bn_R2);
	h_MET_W = new TH1D("MET_W", ";MET", 400,0,2000);
	h_MET_phi_W = new TH1D("MET_phi_W", ";#phi_{MET}", 640, -3.2,3.2);
	h_MET_phi_W_nj45 = new TH1D("MET_phi_W_nj45", ";#phi_{MET}", 640, -3.2,3.2);
	h_MET_phi_W_nj6 = new TH1D("MET_phi_W_nj6", ";#phi_{MET}", 640, -3.2,3.2);

	h_ht_AK4_noMT_W = new TH1D("ht_AK4_noMT_W",  ";H_{T}",                  nbn_HT, bn_HT);
	h_MR_noMT_W = new TH1D("MR_noMT_W",   ";MR_{AK4}",         nbn_MR,bn_MR);
	h_R2_noMT_W = new TH1D("R2_noMT_W",   ";R2_{AK4}",         nbn_R2,bn_R2);
	h_MET_noMT_W = new TH1D("MET_noMT_W", ";MET", 400,0,2000);
	h_MT_noMT_W = new TH1D("MT_noMT_W", ";MET", 25,0,500);

	h_ht_AK4_nonb_W = new TH1D("ht_AK4_nonb_W",  ";H_{T}",                  nbn_HT, bn_HT);
	h_MR_nonb_W = new TH1D("MR_nonb_W",   ";MR_{AK4}",         nbn_MR,bn_MR);
	h_R2_nonb_W = new TH1D("R2_nonb_W",   ";R2_{AK4}",         nbn_R2,bn_R2);
	h_MET_nonb_W = new TH1D("MET_nonb_W", ";MET", 400,0,2000);
	h_nb_nonb_W = new TH1D("nb_nonb_W", ";# of bjet", 10,0,10);

	h_ht_AK4_nomDPhi_W = new TH1D("ht_AK4_nomDPhi_W",  ";H_{T}",                  nbn_HT, bn_HT);
	h_MR_nomDPhi_W = new TH1D("MR_nomDPhi_W",   ";MR_{AK4}",         nbn_MR,bn_MR);
	h_R2_nomDPhi_W = new TH1D("R2_nomDPhi_W",   ";R2_{AK4}",         nbn_R2,bn_R2);
	h_MET_nomDPhi_W = new TH1D("MET_nomDPhi_W", ";MET", 400,0,2000);
	h_mDPhi_nomDPhi_W = new TH1D("mDPhi_nomDPhi_W", ";#Delta#phi_{megajets}", 64,0,3.2);

	h_ht_AK4_no1Lep_W = new TH1D("ht_AK4_no1Lep_W",  ";H_{T}",                  nbn_HT, bn_HT);
	h_MR_no1Lep_W = new TH1D("MR_no1Lep_W",   ";MR_{AK4}",         nbn_MR,bn_MR);
	h_R2_no1Lep_W = new TH1D("R2_no1Lep_W",   ";R2_{AK4}",         nbn_R2,bn_R2);
	h_MET_no1Lep_W = new TH1D("MET_no1Lep_W", ";MET", 400,0,2000);
	h_nLep_no1Lep_W = new TH1D("nLep_no1Lep_W", ";# of Lepton", 10,0,10);

	h_ht_AK4_W_nj45 = new TH1D("ht_AK4_W_nj45",  ";H_{T}",                  nbn_HT, bn_HT);
	h_MR_W_nj45 = new TH1D("MR_W_nj45",   ";MR_{AK4}",         nbn_MR,bn_MR);
	h_R2_W_nj45 = new TH1D("R2_W_nj45",   ";R2_{AK4}",         nbn_R2,bn_R2);
	h_MET_W_nj45 = new TH1D("MET_W_nj45", ";MET", 400,0,2000);

	h_ht_AK4_noMT_W_nj45 = new TH1D("ht_AK4_noMT_W_nj45",  ";H_{T}",                  nbn_HT, bn_HT);
	h_MR_noMT_W_nj45 = new TH1D("MR_noMT_W_nj45",   ";MR_{AK4}",         nbn_MR,bn_MR);
	h_R2_noMT_W_nj45 = new TH1D("R2_noMT_W_nj45",   ";R2_{AK4}",         nbn_R2,bn_R2);
	h_MET_noMT_W_nj45 = new TH1D("MET_noMT_W_nj45", ";MET", 400,0,2000);
	h_MT_noMT_W_nj45 = new TH1D("MT_noMT_W_nj45", ";MET", 25,0,500);

	h_ht_AK4_nonb_W_nj45 = new TH1D("ht_AK4_nonb_W_nj45",  ";H_{T}",                  nbn_HT, bn_HT);
	h_MR_nonb_W_nj45 = new TH1D("MR_nonb_W_nj45",   ";MR_{AK4}",         nbn_MR,bn_MR);
	h_R2_nonb_W_nj45 = new TH1D("R2_nonb_W_nj45",   ";R2_{AK4}",         nbn_R2,bn_R2);
	h_MET_nonb_W_nj45 = new TH1D("MET_nonb_W_nj45", ";MET", 400,0,2000);
	h_nb_nonb_W_nj45 = new TH1D("nb_nonb_W_nj45", ";# of bjet", 10,0,10);

	h_ht_AK4_nomDPhi_W_nj45 = new TH1D("ht_AK4_nomDPhi_W_nj45",  ";H_{T}",                  nbn_HT, bn_HT);
	h_MR_nomDPhi_W_nj45 = new TH1D("MR_nomDPhi_W_nj45",   ";MR_{AK4}",         nbn_MR,bn_MR);
	h_R2_nomDPhi_W_nj45 = new TH1D("R2_nomDPhi_W_nj45",   ";R2_{AK4}",         nbn_R2,bn_R2);
	h_MET_nomDPhi_W_nj45 = new TH1D("MET_nomDPhi_W_nj45", ";MET", 400,0,2000);
	h_mDPhi_nomDPhi_W_nj45 = new TH1D("mDPhi_nomDPhi_W_nj45", ";#Delta#phi_{megajets}", 64,0,3.2);

	h_ht_AK4_no1Lep_W_nj45 = new TH1D("ht_AK4_no1Lep_W_nj45",  ";H_{T}",                  nbn_HT, bn_HT);
	h_MR_no1Lep_W_nj45 = new TH1D("MR_no1Lep_W_nj45",   ";MR_{AK4}",         nbn_MR,bn_MR);
	h_R2_no1Lep_W_nj45 = new TH1D("R2_no1Lep_W_nj45",   ";R2_{AK4}",         nbn_R2,bn_R2);
	h_MET_no1Lep_W_nj45 = new TH1D("MET_no1Lep_W_nj45", ";MET", 400,0,2000);
	h_nLep_no1Lep_W_nj45 = new TH1D("nLep_no1Lep_W_nj45", ";# of Lepton", 10,0,10);

	h_ht_AK4_W_nj6 = new TH1D("ht_AK4_W_nj6",  ";H_{T}",                  nbn_HT, bn_HT);
	h_MR_W_nj6 = new TH1D("MR_W_nj6",   ";MR_{AK4}",         nbn_MR,bn_MR);
	h_R2_W_nj6 = new TH1D("R2_W_nj6",   ";R2_{AK4}",         nbn_R2,bn_R2);
	h_MET_W_nj6 = new TH1D("MET_W_nj6", ";MET", 400,0,2000);

	h_ht_AK4_noMT_W_nj6 = new TH1D("ht_AK4_noMT_W_nj6",  ";H_{T}",                  nbn_HT, bn_HT);
	h_MR_noMT_W_nj6 = new TH1D("MR_noMT_W_nj6",   ";MR_{AK4}",         nbn_MR,bn_MR);
	h_R2_noMT_W_nj6 = new TH1D("R2_noMT_W_nj6",   ";R2_{AK4}",         nbn_R2,bn_R2);
	h_MET_noMT_W_nj6 = new TH1D("MET_noMT_W_nj6", ";MET", 400,0,2000);
	h_MT_noMT_W_nj6 = new TH1D("MT_noMT_W_nj6", ";MET", 25,0,500);

	h_ht_AK4_nonb_W_nj6 = new TH1D("ht_AK4_nonb_W_nj6",  ";H_{T}",                  nbn_HT, bn_HT);
	h_MR_nonb_W_nj6 = new TH1D("MR_nonb_W_nj6",   ";MR_{AK4}",         nbn_MR,bn_MR);
	h_R2_nonb_W_nj6 = new TH1D("R2_nonb_W_nj6",   ";R2_{AK4}",         nbn_R2,bn_R2);
	h_MET_nonb_W_nj6 = new TH1D("MET_nonb_W_nj6", ";MET", 400,0,2000);
	h_nb_nonb_W_nj6 = new TH1D("nb_nonb_W_nj6", ";# of bjet", 10,0,10);

	h_ht_AK4_nomDPhi_W_nj6 = new TH1D("ht_AK4_nomDPhi_W_nj6",  ";H_{T}",                  nbn_HT, bn_HT);
	h_MR_nomDPhi_W_nj6 = new TH1D("MR_nomDPhi_W_nj6",   ";MR_{AK4}",         nbn_MR,bn_MR);
	h_R2_nomDPhi_W_nj6 = new TH1D("R2_nomDPhi_W_nj6",   ";R2_{AK4}",         nbn_R2,bn_R2);
	h_MET_nomDPhi_W_nj6 = new TH1D("MET_nomDPhi_W_nj6", ";MET", 400,0,2000);
	h_mDPhi_nomDPhi_W_nj6 = new TH1D("mDPhi_nomDPhi_W_nj6_nj6", ";#Delta#phi_{megajets}", 64,0,3.2);

	h_ht_AK4_no1Lep_W_nj6 = new TH1D("ht_AK4_no1Lep_W_nj6",  ";H_{T}",                  nbn_HT, bn_HT);
	h_MR_no1Lep_W_nj6 = new TH1D("MR_no1Lep_W_nj6",   ";MR_{AK4}",         nbn_MR,bn_MR);
	h_R2_no1Lep_W_nj6 = new TH1D("R2_no1Lep_W_nj6",   ";R2_{AK4}",         nbn_R2,bn_R2);
	h_MET_no1Lep_W_nj6 = new TH1D("MET_no1Lep_W_nj6", ";MET", 400,0,2000);
	h_nLep_no1Lep_W_nj6 = new TH1D("nLep_no1Lep_W_nj6", ";# of Lepton", 10,0,10);

#if TOP == 0
	h_ht_AK4_nonW_W = new TH1D("ht_AK4_nonW_W",  ";H_{T}",                  nbn_HT, bn_HT);
	h_MR_nonW_W = new TH1D("MR_nonW_W",   ";MR_{AK4}",         nbn_MR,bn_MR);
	h_R2_nonW_W = new TH1D("R2_nonW_W",   ";R2_{AK4}",         nbn_R2,bn_R2);
	h_MET_nonW_W = new TH1D("MET_nonW_W", ";MET", 400,0,2000);
	h_nW_nonW_W = new TH1D("nW_nonW_W", ";# of Wjet", 10,0,10);

	h_ht_AK4_nonW_W_nj45 = new TH1D("ht_AK4_nonW_W_nj45",  ";H_{T}",                  nbn_HT, bn_HT);
	h_MR_nonW_W_nj45 = new TH1D("MR_nonW_W_nj45",   ";MR_{AK4}",         nbn_MR,bn_MR);
	h_R2_nonW_W_nj45 = new TH1D("R2_nonW_W_nj45",   ";R2_{AK4}",         nbn_R2,bn_R2);
	h_MET_nonW_W_nj45 = new TH1D("MET_nonW_W_nj45", ";MET", 400,0,2000);
	h_nW_nonW_W_nj45 = new TH1D("nW_nonW_W_nj45", ";# of Wjet", 10,0,10);

	h_ht_AK4_nonW_W_nj6 = new TH1D("ht_AK4_nonW_W_nj6",  ";H_{T}",                  nbn_HT, bn_HT);
	h_MR_nonW_W_nj6 = new TH1D("MR_nonW_W_nj6",   ";MR_{AK4}",         nbn_MR,bn_MR);
	h_R2_nonW_W_nj6 = new TH1D("R2_nonW_W_nj6",   ";R2_{AK4}",         nbn_R2,bn_R2);
	h_MET_nonW_W_nj6 = new TH1D("MET_nonW_W_nj6", ";MET", 400,0,2000);
	h_nW_nonW_W_nj6 = new TH1D("nW_nonW_W_nj6", ";# of Wjet", 10,0,10);
#else
	h_ht_AK4_nonTop_W = new TH1D("ht_AK4_nonTop_W",  ";H_{T}",                  nbn_HT, bn_HT);
	h_MR_nonTop_W = new TH1D("MR_nonTop_W",   ";MR_{AK4}",         nbn_MR,bn_MR);
	h_R2_nonTop_W = new TH1D("R2_nonTop_W",   ";R2_{AK4}",         nbn_R2,bn_R2);
	h_MET_nonTop_W = new TH1D("MET_nonTop_W", ";MET", 400,0,2000);
	h_nTop_nonTop_W = new TH1D("nTop_nonTop_W", ";# of Topjet", 10,0,10);

	h_ht_AK4_nonTop_W_nj45 = new TH1D("ht_AK4_nonTop_W_nj45",  ";H_{T}",                  nbn_HT, bn_HT);
	h_MR_nonTop_W_nj45 = new TH1D("MR_nonTop_W_nj45",   ";MR_{AK4}",         nbn_MR,bn_MR);
	h_R2_nonTop_W_nj45 = new TH1D("R2_nonTop_W_nj45",   ";R2_{AK4}",         nbn_R2,bn_R2);
	h_MET_nonTop_W_nj45 = new TH1D("MET_nonTop_W_nj45", ";MET", 400,0,2000);
	h_nTop_nonTop_W_nj45 = new TH1D("nTop_nonTop_W_nj45", ";# of Topjet", 10,0,10);

	h_ht_AK4_nonTop_W_nj6 = new TH1D("ht_AK4_nonTop_W_nj6",  ";H_{T}",                  nbn_HT, bn_HT);
	h_MR_nonTop_W_nj6 = new TH1D("MR_nonTop_W_nj6",   ";MR_{AK4}",         nbn_MR,bn_MR);
	h_R2_nonTop_W_nj6 = new TH1D("R2_nonTop_W_nj6",   ";R2_{AK4}",         nbn_R2,bn_R2);
	h_MET_nonTop_W_nj6 = new TH1D("MET_nonTop_W_nj6", ";MET", 400,0,2000);
	h_nTop_nonTop_W_nj6 = new TH1D("nTop_nonTop_W_nj6", ";# of Topjet", 10,0,10);
#endif

	h_ht_AK4_q = new TH1D("ht_AK4_q",  ";H_{T}",                  nbn_HT, bn_HT);
	h_MR_q = new TH1D("MR_q",   ";MR_{AK4}",         nbn_MR,bn_MR);
	h_R2_q = new TH1D("R2_q",   ";R2_{AK4}",         nbn_R2,bn_R2);
	h_MET_q = new TH1D("MET_q", ";MET", 400,0,2000);
	h_MET_phi_q = new TH1D("MET_phi_q", ";#phi_{MET}", 640, -3.2,3.2);
	h_MET_phi_q_nj45 = new TH1D("MET_phi_q_nj45", ";#phi_{MET}", 640, -3.2,3.2);
	h_MET_phi_q_nj6 = new TH1D("MET_phi_q_nj6", ";#phi_{MET}", 640, -3.2,3.2);

	h_ht_AK4_q_nj45 = new TH1D("ht_AK4_q_nj45",  ";H_{T}",                  nbn_HT, bn_HT);
	h_MR_q_nj45 = new TH1D("MR_q_nj45",   ";MR_{AK4}",         nbn_MR,bn_MR);
	h_R2_q_nj45 = new TH1D("R2_q_nj45",   ";R2_{AK4}",         nbn_R2,bn_R2);
	h_MET_q_nj45 = new TH1D("MET_q_nj45", ";MET", 400,0,2000);

	h_ht_AK4_q_nj6 = new TH1D("ht_AK4_q_nj6",  ";H_{T}",                  nbn_HT, bn_HT);
	h_MR_q_nj6 = new TH1D("MR_q_nj6",   ";MR_{AK4}",         nbn_MR,bn_MR);
	h_R2_q_nj6 = new TH1D("R2_q_nj6",   ";R2_{AK4}",         nbn_R2,bn_R2);
	h_MET_q_nj6 = new TH1D("MET_q_nj6", ";MET", 400,0,2000);

	h_R2_MR_P = new TH2D("R2_MR_P", ";MR_{AK4};R2_{AK4}",nbn_MR,bn_MR,nbn_R2,bn_R2);

	h_R2_MR_s = new TH2D("R2_MR_s", ";MR_{AK4};R2_{AK4}",nbn_MR,bn_MR,nbn_R2,bn_R2);
	h_R2_MET_s = new TH2D("R2_MET_s", ";MET_{AK4};R2_{AK4}",40,0,2000,nbn_R2,bn_R2);
	h_MR_MET_s = new TH2D("MR_MET_s", ";MET_{AK4};MR_{AK4}",40,0,2000,nbn_MR,bn_MR);
	h_AK8Jet1pT_MET_s = new TH2D("AK8Jet1pT_MET_s", ";MET_{AK4};p_{T,AK8Jet1}",40,0,2000,40,0,2000);
	h_R2_MR_q = new TH2D("R2_MR_q", ";MR_{AK4};R2_{AK4}",nbn_MR,bn_MR,nbn_R2,bn_R2);
	h_R2_MET_q = new TH2D("R2_MET_q", ";MET_{AK4};R2_{AK4}",40,0,2000,nbn_R2,bn_R2);
	h_MR_MET_q = new TH2D("MR_MET_q", ";MET_{AK4};MR_{AK4}",40,0,2000,nbn_MR,bn_MR);
	h_AK8Jet1pT_MET_q = new TH2D("AK8Jet1pT_MET_q", ";MET_{AK4};p_{T,AK8Jet1}",40,0,2000,40,0,2000);
	h_R2_MR_Q = new TH2D("R2_MR_Q", ";MR_{AK4};R2_{AK4}",nbn_MR,bn_MR,nbn_R2,bn_R2);
	h_R2_MET_Q = new TH2D("R2_MET_Q", ";MET_{AK4};R2_{AK4}",40,0,2000,nbn_R2,bn_R2);
	h_MR_MET_Q = new TH2D("MR_MET_Q", ";MET_{AK4};MR_{AK4}",40,0,2000,nbn_MR,bn_MR);
	h_AK8Jet1pT_MET_Q = new TH2D("AK8Jet1pT_MET_Q", ";MET_{AK4};p_{T,AK8Jet1}",40,0,2000,40,0,2000);
	h_R2_MR_T = new TH2D("R2_MR_T", ";MR_{AK4};R2_{AK4}",nbn_MR,bn_MR,nbn_R2,bn_R2);
	h_R2_MET_T = new TH2D("R2_MET_T", ";MET_{AK4};R2_{AK4}",40,0,2000,nbn_R2,bn_R2);
	h_MR_MET_T = new TH2D("MR_MET_T", ";MET_{AK4};MR_{AK4}",40,0,2000,nbn_MR,bn_MR);
	h_AK8Jet1pT_MET_T = new TH2D("AK8Jet1pT_MET_T", ";MET_{AK4};p_{T,AK8Jet1}",40,0,2000,40,0,2000);
	h_R2_MR_W = new TH2D("R2_MR_W", ";MR_{AK4};R2_{AK4}",nbn_MR,bn_MR,nbn_R2,bn_R2);
	h_R2_MET_W = new TH2D("R2_MET_W", ";MET_{AK4};R2_{AK4}",40,0,2000,nbn_R2,bn_R2);
	h_MR_MET_W = new TH2D("MR_MET_W", ";MET_{AK4};MR_{AK4}",40,0,2000,nbn_MR,bn_MR);
	h_AK8Jet1pT_MET_W = new TH2D("AK8Jet1pT_MET_W", ";MET_{AK4};p_{T,AK8Jet1}",40,0,2000,40,0,2000);
	h_R2_MR_Z = new TH2D("R2_MR_Z", ";MR_{AK4};R2_{AK4}",nbn_MR,bn_MR,nbn_R2,bn_R2);
	h_R2_MET_Z = new TH2D("R2_MET_Z", ";MET_{AK4};R2_{AK4}",40,0,2000,nbn_R2,bn_R2);
	h_MR_MET_Z = new TH2D("MR_MET_Z", ";MET_{AK4};MR_{AK4}",40,0,2000,nbn_MR,bn_MR);
	h_AK8Jet1pT_MET_Z = new TH2D("AK8Jet1pT_MET_Z", ";MET_{AK4};p_{T,AK8Jet1}",40,0,2000,40,0,2000);
	h_R2_MR_L = new TH2D("R2_MR_L", ";MR_{AK4};R2_{AK4}",nbn_MR,bn_MR,nbn_R2,bn_R2);
	h_R2_MET_L = new TH2D("R2_MET_L", ";MET_{AK4};R2_{AK4}",40,0,2000,nbn_R2,bn_R2);
	h_MR_MET_L = new TH2D("MR_MET_L", ";MET_{AK4};MR_{AK4}",40,0,2000,nbn_MR,bn_MR);
	h_AK8Jet1pT_MET_L = new TH2D("AK8Jet1pT_MET_L", ";MET_{AK4};p_{T,AK8Jet1}",40,0,2000,40,0,2000);
	h_R2_MR_G = new TH2D("R2_MR_G", ";MR_{AK4};R2_{AK4}",nbn_MR,bn_MR,nbn_R2,bn_R2);
	h_R2_MET_G = new TH2D("R2_MET_G", ";MET_{AK4};R2_{AK4}",40,0,2000,nbn_R2,bn_R2);
	h_MR_MET_G = new TH2D("MR_MET_G", ";MET_{AK4};MR_{AK4}",40,0,2000,nbn_MR,bn_MR);
	h_AK8Jet1pT_MET_G = new TH2D("AK8Jet1pT_MET_G", ";MET_{AK4};p_{T,AK8Jet1}",40,0,2000,40,0,2000);
	h_R2_MR_s_nj45 = new TH2D("R2_MR_s_nj45", ";MR_{AK4};R2_{AK4}",nbn_MR,bn_MR,nbn_R2,bn_R2);
	h_R2_MR_s_nj6 = new TH2D("R2_MR_s_nj6", ";MR_{AK4};R2_{AK4}",nbn_MR,bn_MR,nbn_R2,bn_R2);
	h_R2_MR_q_nj45 = new TH2D("R2_MR_q_nj45", ";MR_{AK4};R2_{AK4}",nbn_MR,bn_MR,nbn_R2,bn_R2);
	h_R2_MR_q_nj6 = new TH2D("R2_MR_q_nj6", ";MR_{AK4};R2_{AK4}",nbn_MR,bn_MR,nbn_R2,bn_R2);
	h_R2_MR_Q_nj45 = new TH2D("R2_MR_Q_nj45", ";MR_{AK4};R2_{AK4}",nbn_MR,bn_MR,nbn_R2,bn_R2);
	h_R2_MR_Q_nj6 = new TH2D("R2_MR_Q_nj6", ";MR_{AK4};R2_{AK4}",nbn_MR,bn_MR,nbn_R2,bn_R2);
	h_R2_MR_T_nj45 = new TH2D("R2_MR_T_nj45", ";MR_{AK4};R2_{AK4}",nbn_MR,bn_MR,nbn_R2,bn_R2);
	h_R2_MR_T_nj6 = new TH2D("R2_MR_T_nj6", ";MR_{AK4};R2_{AK4}",nbn_MR,bn_MR,nbn_R2,bn_R2);
	h_R2_MR_W_nj45 = new TH2D("R2_MR_W_nj45", ";MR_{AK4};R2_{AK4}",nbn_MR,bn_MR,nbn_R2,bn_R2);
	h_R2_MR_W_nj6 = new TH2D("R2_MR_W_nj6", ";MR_{AK4};R2_{AK4}",nbn_MR,bn_MR,nbn_R2,bn_R2);
	h_R2_MR_Z_nj45 = new TH2D("R2_MR_Z_nj45", ";MR_{AK4};R2_{AK4}",nbn_MR,bn_MR,nbn_R2,bn_R2);
	h_R2_MR_Z_nj6 = new TH2D("R2_MR_Z_nj6", ";MR_{AK4};R2_{AK4}",nbn_MR,bn_MR,nbn_R2,bn_R2);
	h_R2_MR_L_nj45 = new TH2D("R2_MR_L_nj45", ";MR_{AK4};R2_{AK4}",nbn_MR,bn_MR,nbn_R2,bn_R2);
	h_R2_MR_L_nj6 = new TH2D("R2_MR_L_nj6", ";MR_{AK4};R2_{AK4}",nbn_MR,bn_MR,nbn_R2,bn_R2);
	h_R2_MR_G_nj45 = new TH2D("R2_MR_G_nj45", ";MR_{AK4};R2_{AK4}",nbn_MR,bn_MR,nbn_R2,bn_R2);
	h_R2_MR_G_nj6 = new TH2D("R2_MR_G_nj6", ";MR_{AK4};R2_{AK4}",nbn_MR,bn_MR,nbn_R2,bn_R2);

	h_jet1_pt_news = new TH1D("jet1_pt_news",";p_{T, jet1}",200,0,2000);
	h_jet1_eta_news = new TH1D("jet1_eta_news",";#eta_{jet1}",480,-2.4,2.4);
	h_jet1_phi_news = new TH1D("jet1_phi_news",";#phi_{jet1}",640,-3.2,3.2);
	h_jets_pt_news = new TH1D("jets_pt_news",";p_{T, jets}",200,0,2000);
	h_jets_eta_news = new TH1D("jets_eta_news",";#eta_{jets}",480,-2.4,2.4);
	h_jets_phi_news = new TH1D("jets_phi_news",";#phi_{jets}",640,-3.2,3.2);
	h_AK8jet1_pt_news = new TH1D("AK8jet1_pt_news",";p_{T, AK8jet1}",200,0,2000);
	h_AK8jet1_eta_news = new TH1D("AK8jet1_eta_news",";#eta_{AK8jet1}",480,-2.4,2.4);
	h_AK8jet1_phi_news = new TH1D("AK8jet1_phi_news",";#phi_{AK8jet1}",640,-3.2,3.2);
	h_AK8jet1_tau21_news = new TH1D("AK8jet1_tau21_news",";tau_{21, AK8jet1}",20,0,1);
	h_AK8jet1_tau32_news = new TH1D("AK8jet1_tau32_news",";tau_{32, AK8jet1}",20,0,1);
	h_AK8jets_pt_news = new TH1D("AK8jets_pt_news",";p_{T, AK8jets}",200,0,2000);
	h_AK8jets_eta_news = new TH1D("AK8jets_eta_news",";#eta_{AK8jets}",480,-2.4,2.4);
	h_AK8jets_phi_news = new TH1D("AK8jets_phi_news",";#phi_{AK8jets}",640,-3.2,3.2);
	h_AK8jets_msoftdrop_news = new TH1D("AK8jets_msoftdrop_news",";p_{mass, AK8jets}",100,0,500);
	h_AK8jets_tau21_news = new TH1D("AK8jets_tau21_news",";tau_{21, AK8jets}",20,0,1);
	h_AK8jets_tau32_news = new TH1D("AK8jets_tau32_news",";tau_{32, AK8jets}",20,0,1);
	h_jet1_pt_news_nj45 = new TH1D("jet1_pt_news_nj45",";p_{T, jet1}",200,0,2000);
	h_jet1_eta_news_nj45 = new TH1D("jet1_eta_news_nj45",";#eta_{jet1}",480,-2.4,2.4);
	h_jet1_phi_news_nj45 = new TH1D("jet1_phi_news_nj45",";#phi_{jet1}",640,-3.2,3.2);
	h_jets_pt_news_nj45 = new TH1D("jets_pt_news_nj45",";p_{T, jets}",200,0,2000);
	h_jets_eta_news_nj45 = new TH1D("jets_eta_news_nj45",";#eta_{jets}",480,-2.4,2.4);
	h_jets_phi_news_nj45 = new TH1D("jets_phi_news_nj45",";#phi_{jets}",640,-3.2,3.2);
	h_AK8jet1_pt_news_nj45 = new TH1D("AK8jet1_pt_news_nj45",";p_{T, AK8jet1}",200,0,2000);
	h_AK8jet1_eta_news_nj45 = new TH1D("AK8jet1_eta_news_nj45",";#eta_{AK8jet1}",480,-2.4,2.4);
	h_AK8jet1_phi_news_nj45 = new TH1D("AK8jet1_phi_news_nj45",";#phi_{AK8jet1}",640,-3.2,3.2);
	h_AK8jet1_tau21_news_nj45 = new TH1D("AK8jet1_tau21_news_nj45",";tau_{21, AK8jet1}",20,0,1);
	h_AK8jet1_tau32_news_nj45 = new TH1D("AK8jet1_tau32_news_nj45",";tau_{32, AK8jet1}",20,0,1);
	h_AK8jets_pt_news_nj45 = new TH1D("AK8jets_pt_news_nj45",";p_{T, AK8jets}",200,0,2000);
	h_AK8jets_eta_news_nj45 = new TH1D("AK8jets_eta_news_nj45",";#eta_{AK8jets}",480,-2.4,2.4);
	h_AK8jets_phi_news_nj45 = new TH1D("AK8jets_phi_news_nj45",";#phi_{AK8jets}",640,-3.2,3.2);
	h_AK8jets_msoftdrop_news_nj45 = new TH1D("AK8jets_msoftdrop_news_nj45",";p_{mass, AK8jets}",100,0,500);
	h_AK8jets_tau21_news_nj45 = new TH1D("AK8jets_tau21_news_nj45",";tau_{21, AK8jets}",20,0,1);
	h_AK8jets_tau32_news_nj45 = new TH1D("AK8jets_tau32_news_nj45",";tau_{32, AK8jets}",20,0,1);
	h_jet1_pt_news_nj6 = new TH1D("jet1_pt_news_nj6",";p_{T, jet1}",200,0,2000);
	h_jet1_eta_news_nj6 = new TH1D("jet1_eta_news_nj6",";#eta_{jet1}",480,-2.4,2.4);
	h_jet1_phi_news_nj6 = new TH1D("jet1_phi_news_nj6",";#phi_{jet1}",640,-3.2,3.2);
	h_jets_pt_news_nj6 = new TH1D("jets_pt_news_nj6",";p_{T, jets}",200,0,2000);
	h_jets_eta_news_nj6 = new TH1D("jets_eta_news_nj6",";#eta_{jets}",480,-2.4,2.4);
	h_jets_phi_news_nj6 = new TH1D("jets_phi_news_nj6",";#phi_{jets}",640,-3.2,3.2);
	h_AK8jet1_pt_news_nj6 = new TH1D("AK8jet1_pt_news_nj6",";p_{T, AK8jet1}",200,0,2000);
	h_AK8jet1_eta_news_nj6 = new TH1D("AK8jet1_eta_news_nj6",";#eta_{AK8jet1}",480,-2.4,2.4);
	h_AK8jet1_phi_news_nj6 = new TH1D("AK8jet1_phi_news_nj6",";#phi_{AK8jet1}",640,-3.2,3.2);
	h_AK8jet1_tau21_news_nj6 = new TH1D("AK8jet1_tau21_news_nj6",";tau_{21, AK8jet1}",20,0,1);
	h_AK8jet1_tau32_news_nj6 = new TH1D("AK8jet1_tau32_news_nj6",";tau_{32, AK8jet1}",20,0,1);
	h_AK8jets_pt_news_nj6 = new TH1D("AK8jets_pt_news_nj6",";p_{T, AK8jets}",200,0,2000);
	h_AK8jets_eta_news_nj6 = new TH1D("AK8jets_eta_news_nj6",";#eta_{AK8jets}",480,-2.4,2.4);
	h_AK8jets_phi_news_nj6 = new TH1D("AK8jets_phi_news_nj6",";#phi_{AK8jets}",640,-3.2,3.2);
	h_AK8jets_msoftdrop_news_nj6 = new TH1D("AK8jets_msoftdrop_news_nj6",";p_{mass, AK8jets}",100,0,500);
	h_AK8jets_tau21_news_nj6 = new TH1D("AK8jets_tau21_news_nj6",";tau_{21, AK8jets}",20,0,1);
	h_AK8jets_tau32_news_nj6 = new TH1D("AK8jets_tau32_news_nj6",";tau_{32, AK8jets}",20,0,1);
	h_Megajets_pt_news = new TH1D("Megajets_pt_news",";p_{T, Megajets}",200,0,2000);
	h_Megajets_eta_news = new TH1D("Megajets_eta_news",";#eta_{Megajets}",480,-2.4,2.4);
	h_Megajets_phi_news = new TH1D("Megajets_phi_news",";#phi_{Megajets}",640,-3.2,3.2);
	h_njet_news       = new TH1D("njet_news",         ";N_{jet}",                20, 0,  20);
	h_nAK8jet_news    = new TH1D("nAK8jet_news",      ";N_{jet}",                20, 0,  20);
	h_ht_AK4_news = new TH1D("ht_AK4_news",  ";H_{T}",                  nbn_HT, bn_HT);
	h_MR_news = new TH1D("MR_news",   ";MR_{AK4}",         nbn_MR,bn_MR);
	h_R2_news = new TH1D("R2_news",   ";R2_{AK4}",         nbn_R2,bn_R2);
	h_MET_news = new TH1D("MET_news", ";MET", 400,0,2000);
	h_MET_phi_news = new TH1D("MET_phi_news", ";#phi_{MET}", 640, -3.2,3.2);
	h_MET_phi_news_nj45 = new TH1D("MET_phi_news_nj45", ";#phi_{MET}", 640, -3.2,3.2);
	h_MET_phi_news_nj6 = new TH1D("MET_phi_news_nj6", ";#phi_{MET}", 640, -3.2,3.2);
	h_ht_AK4_news_nj45 = new TH1D("ht_AK4_news_nj45",  ";H_{T}",                  nbn_HT, bn_HT);
	h_MR_news_nj45 = new TH1D("MR_news_nj45",   ";MR_{AK4}",         nbn_MR,bn_MR);
	h_R2_news_nj45 = new TH1D("R2_news_nj45",   ";R2_{AK4}",         nbn_R2,bn_R2);
	h_MET_news_nj45 = new TH1D("MET_news_nj45", ";MET", 400,0,2000);
	h_ht_AK4_news_nj6 = new TH1D("ht_AK4_news_nj6",  ";H_{T}",                  nbn_HT, bn_HT);
	h_MR_news_nj6 = new TH1D("MR_news_nj6",   ";MR_{AK4}",         nbn_MR,bn_MR);
	h_R2_news_nj6 = new TH1D("R2_news_nj6",   ";R2_{AK4}",         nbn_R2,bn_R2);
	h_MET_news_nj6 = new TH1D("MET_news_nj6", ";MET", 400,0,2000);
	h_R2_MR_news = new TH2D("R2_MR_news", ";MR_{AK4};R2_{AK4}",nbn_MR,bn_MR,nbn_R2,bn_R2);
	h_R2_MET_news = new TH2D("R2_MET_news", ";MET_{AK4};R2_{AK4}",40,0,2000,nbn_R2,bn_R2);
	h_MR_MET_news = new TH2D("MR_MET_news", ";MET_{AK4};MR_{AK4}",40,0,2000,nbn_MR,bn_MR);
	h_AK8Jet1pT_MET_news = new TH2D("AK8Jet1pT_MET_news", ";MET_{AK4};p_{T,AK8Jet1}",40,0,2000,40,0,2000);
	h_R2_MR_news_nj45 = new TH2D("R2_MR_news_nj45", ";MR_{AK4};R2_{AK4}",nbn_MR,bn_MR,nbn_R2,bn_R2);
	h_R2_MR_news_nj6 = new TH2D("R2_MR_news_nj6", ";MR_{AK4};R2_{AK4}",nbn_MR,bn_MR,nbn_R2,bn_R2);
	h_nWjet_news = new TH1D("nWjet_news",";N_{W}", 10,0,10);
	h_nTopjet_news = new TH1D("nTopjet_news",";N_{Top}", 10,0,10);;
	h_nWjet_news_nj45 = new TH1D("nWjet_news_nj45",";N_{W}", 10,0,10);;
	h_nTopjet_news_nj45 = new TH1D("nTopjet_news_nj45",";N_{Top}", 10,0,10);;;
	h_nWjet_news_nj6 = new TH1D("nWjet_news_nj6",";N_{W}", 10,0,10);;
	h_nTopjet_news_nj6 = new TH1D("nTopjet_news_nj6",";N_{Top}", 10,0,10);;;

	h_jet1_pt_newq = new TH1D("jet1_pt_newq",";p_{T, jet1}",200,0,2000);
	h_jet1_eta_newq = new TH1D("jet1_eta_newq",";#eta_{jet1}",480,-2.4,2.4);
	h_jet1_phi_newq = new TH1D("jet1_phi_newq",";#phi_{jet1}",640,-3.2,3.2);
	h_jets_pt_newq = new TH1D("jets_pt_newq",";p_{T, jets}",200,0,2000);
	h_jets_eta_newq = new TH1D("jets_eta_newq",";#eta_{jets}",480,-2.4,2.4);
	h_jets_phi_newq = new TH1D("jets_phi_newq",";#phi_{jets}",640,-3.2,3.2);
	h_AK8jet1_pt_newq = new TH1D("AK8jet1_pt_newq",";p_{T, AK8jet1}",200,0,2000);
	h_AK8jet1_eta_newq = new TH1D("AK8jet1_eta_newq",";#eta_{AK8jet1}",480,-2.4,2.4);
	h_AK8jet1_phi_newq = new TH1D("AK8jet1_phi_newq",";#phi_{AK8jet1}",640,-3.2,3.2);
	h_AK8jet1_tau21_newq = new TH1D("AK8jet1_tau21_newq",";tau_{21, AK8jet1}",20,0,1);
	h_AK8jet1_tau32_newq = new TH1D("AK8jet1_tau32_newq",";tau_{32, AK8jet1}",20,0,1);
	h_AK8jets_pt_newq = new TH1D("AK8jets_pt_newq",";p_{T, AK8jets}",200,0,2000);
	h_AK8jets_eta_newq = new TH1D("AK8jets_eta_newq",";#eta_{AK8jets}",480,-2.4,2.4);
	h_AK8jets_phi_newq = new TH1D("AK8jets_phi_newq",";#phi_{AK8jets}",640,-3.2,3.2);
	h_AK8jets_msoftdrop_newq = new TH1D("AK8jets_msoftdrop_newq",";p_{mass, AK8jets}",100,0,500);
	h_AK8jets_tau21_newq = new TH1D("AK8jets_tau21_newq",";tau_{21, AK8jets}",20,0,1);
	h_AK8jets_tau32_newq = new TH1D("AK8jets_tau32_newq",";tau_{32, AK8jets}",20,0,1);
	h_jet1_pt_newq_nj45 = new TH1D("jet1_pt_newq_nj45",";p_{T, jet1}",200,0,2000);
	h_jet1_eta_newq_nj45 = new TH1D("jet1_eta_newq_nj45",";#eta_{jet1}",480,-2.4,2.4);
	h_jet1_phi_newq_nj45 = new TH1D("jet1_phi_newq_nj45",";#phi_{jet1}",640,-3.2,3.2);
	h_jets_pt_newq_nj45 = new TH1D("jets_pt_newq_nj45",";p_{T, jets}",200,0,2000);
	h_jets_eta_newq_nj45 = new TH1D("jets_eta_newq_nj45",";#eta_{jets}",480,-2.4,2.4);
	h_jets_phi_newq_nj45 = new TH1D("jets_phi_newq_nj45",";#phi_{jets}",640,-3.2,3.2);
	h_AK8jet1_pt_newq_nj45 = new TH1D("AK8jet1_pt_newq_nj45",";p_{T, AK8jet1}",200,0,2000);
	h_AK8jet1_eta_newq_nj45 = new TH1D("AK8jet1_eta_newq_nj45",";#eta_{AK8jet1}",480,-2.4,2.4);
	h_AK8jet1_phi_newq_nj45 = new TH1D("AK8jet1_phi_newq_nj45",";#phi_{AK8jet1}",640,-3.2,3.2);
	h_AK8jet1_tau21_newq_nj45 = new TH1D("AK8jet1_tau21_newq_nj45",";tau_{21, AK8jet1}",20,0,1);
	h_AK8jet1_tau32_newq_nj45 = new TH1D("AK8jet1_tau32_newq_nj45",";tau_{32, AK8jet1}",20,0,1);
	h_AK8jets_pt_newq_nj45 = new TH1D("AK8jets_pt_newq_nj45",";p_{T, AK8jets}",200,0,2000);
	h_AK8jets_eta_newq_nj45 = new TH1D("AK8jets_eta_newq_nj45",";#eta_{AK8jets}",480,-2.4,2.4);
	h_AK8jets_phi_newq_nj45 = new TH1D("AK8jets_phi_newq_nj45",";#phi_{AK8jets}",640,-3.2,3.2);
	h_AK8jets_msoftdrop_newq_nj45 = new TH1D("AK8jets_msoftdrop_newq_nj45",";p_{mass, AK8jets}",100,0,500);
	h_AK8jets_tau21_newq_nj45 = new TH1D("AK8jets_tau21_newq_nj45",";tau_{21, AK8jets}",20,0,1);
	h_AK8jets_tau32_newq_nj45 = new TH1D("AK8jets_tau32_newq_nj45",";tau_{32, AK8jets}",20,0,1);
	h_jet1_pt_newq_nj6 = new TH1D("jet1_pt_newq_nj6",";p_{T, jet1}",200,0,2000);
	h_jet1_eta_newq_nj6 = new TH1D("jet1_eta_newq_nj6",";#eta_{jet1}",480,-2.4,2.4);
	h_jet1_phi_newq_nj6 = new TH1D("jet1_phi_newq_nj6",";#phi_{jet1}",640,-3.2,3.2);
	h_jets_pt_newq_nj6 = new TH1D("jets_pt_newq_nj6",";p_{T, jets}",200,0,2000);
	h_jets_eta_newq_nj6 = new TH1D("jets_eta_newq_nj6",";#eta_{jets}",480,-2.4,2.4);
	h_jets_phi_newq_nj6 = new TH1D("jets_phi_newq_nj6",";#phi_{jets}",640,-3.2,3.2);
	h_AK8jet1_pt_newq_nj6 = new TH1D("AK8jet1_pt_newq_nj6",";p_{T, AK8jet1}",200,0,2000);
	h_AK8jet1_eta_newq_nj6 = new TH1D("AK8jet1_eta_newq_nj6",";#eta_{AK8jet1}",480,-2.4,2.4);
	h_AK8jet1_phi_newq_nj6 = new TH1D("AK8jet1_phi_newq_nj6",";#phi_{AK8jet1}",640,-3.2,3.2);
	h_AK8jet1_tau21_newq_nj6 = new TH1D("AK8jet1_tau21_newq_nj6",";tau_{21, AK8jet1}",20,0,1);
	h_AK8jet1_tau32_newq_nj6 = new TH1D("AK8jet1_tau32_newq_nj6",";tau_{32, AK8jet1}",20,0,1);
	h_AK8jets_pt_newq_nj6 = new TH1D("AK8jets_pt_newq_nj6",";p_{T, AK8jets}",200,0,2000);
	h_AK8jets_eta_newq_nj6 = new TH1D("AK8jets_eta_newq_nj6",";#eta_{AK8jets}",480,-2.4,2.4);
	h_AK8jets_phi_newq_nj6 = new TH1D("AK8jets_phi_newq_nj6",";#phi_{AK8jets}",640,-3.2,3.2);
	h_AK8jets_msoftdrop_newq_nj6 = new TH1D("AK8jets_msoftdrop_newq_nj6",";p_{mass, AK8jets}",100,0,500);
	h_AK8jets_tau21_newq_nj6 = new TH1D("AK8jets_tau21_newq_nj6",";tau_{21, AK8jets}",20,0,1);
	h_AK8jets_tau32_newq_nj6 = new TH1D("AK8jets_tau32_newq_nj6",";tau_{32, AK8jets}",20,0,1);
	h_Megajets_pt_newq = new TH1D("Megajets_pt_newq",";p_{T, Megajets}",200,0,2000);
	h_Megajets_eta_newq = new TH1D("Megajets_eta_newq",";#eta_{Megajets}",480,-2.4,2.4);
	h_Megajets_phi_newq = new TH1D("Megajets_phi_newq",";#phi_{Megajets}",640,-3.2,3.2);
	h_njet_newq       = new TH1D("njet_newq",         ";N_{jet}",                20, 0,  20);
	h_nAK8jet_newq    = new TH1D("nAK8jet_newq",      ";N_{jet}",                20, 0,  20);
	h_ht_AK4_newq = new TH1D("ht_AK4_newq",  ";H_{T}",                  nbn_HT, bn_HT);
	h_MR_newq = new TH1D("MR_newq",   ";MR_{AK4}",         nbn_MR,bn_MR);
	h_R2_newq = new TH1D("R2_newq",   ";R2_{AK4}",         nbn_R2,bn_R2);
	h_MET_newq = new TH1D("MET_newq", ";MET", 400,0,2000);
	h_MET_phi_newq = new TH1D("MET_phi_newq", ";#phi_{MET}", 640, -3.2,3.2);
	h_MET_phi_newq_nj45 = new TH1D("MET_phi_newq_nj45", ";#phi_{MET}", 640, -3.2,3.2);
	h_MET_phi_newq_nj6 = new TH1D("MET_phi_newq_nj6", ";#phi_{MET}", 640, -3.2,3.2);
	h_ht_AK4_newq_nj45 = new TH1D("ht_AK4_newq_nj45",  ";H_{T}",                  nbn_HT, bn_HT);
	h_MR_newq_nj45 = new TH1D("MR_newq_nj45",   ";MR_{AK4}",         nbn_MR,bn_MR);
	h_R2_newq_nj45 = new TH1D("R2_newq_nj45",   ";R2_{AK4}",         nbn_R2,bn_R2);
	h_MET_newq_nj45 = new TH1D("MET_newq_nj45", ";MET", 400,0,2000);
	h_ht_AK4_newq_nj6 = new TH1D("ht_AK4_newq_nj6",  ";H_{T}",                  nbn_HT, bn_HT);
	h_MR_newq_nj6 = new TH1D("MR_newq_nj6",   ";MR_{AK4}",         nbn_MR,bn_MR);
	h_R2_newq_nj6 = new TH1D("R2_newq_nj6",   ";R2_{AK4}",         nbn_R2,bn_R2);
	h_MET_newq_nj6 = new TH1D("MET_newq_nj6", ";MET", 400,0,2000);
	h_R2_MR_newq = new TH2D("R2_MR_newq", ";MR_{AK4};R2_{AK4}",nbn_MR,bn_MR,nbn_R2,bn_R2);
	h_R2_MET_newq = new TH2D("R2_MET_newq", ";MET_{AK4};R2_{AK4}",40,0,2000,nbn_R2,bn_R2);
	h_MR_MET_newq = new TH2D("MR_MET_newq", ";MET_{AK4};MR_{AK4}",40,0,2000,nbn_MR,bn_MR);
	h_AK8Jet1pT_MET_newq = new TH2D("AK8Jet1pT_MET_newq", ";MET_{AK4};p_{T,AK8Jet1}",40,0,2000,40,0,2000);
	h_R2_MR_newq_nj45 = new TH2D("R2_MR_newq_nj45", ";MR_{AK4};R2_{AK4}",nbn_MR,bn_MR,nbn_R2,bn_R2);
	h_R2_MR_newq_nj6 = new TH2D("R2_MR_newq_nj6", ";MR_{AK4};R2_{AK4}",nbn_MR,bn_MR,nbn_R2,bn_R2);
	h_nWjet_newq = new TH1D("nWjet_newq",";N_{W}", 10,0,10);
	h_nTopjet_newq = new TH1D("nTopjet_newq",";N_{Top}", 10,0,10);;
	h_nWjet_newq_nj45 = new TH1D("nWjet_newq_nj45",";N_{W}", 10,0,10);;
	h_nTopjet_newq_nj45 = new TH1D("nTopjet_newq_nj45",";N_{Top}", 10,0,10);;;
	h_nWjet_newq_nj6 = new TH1D("nWjet_newq_nj6",";N_{W}", 10,0,10);;
	h_nTopjet_newq_nj6 = new TH1D("nTopjet_newq_nj6",";N_{Top}", 10,0,10);;;

#if TOP == 0
	h_R2_MR_looseS = new TH2D("R2_MR_looseS", ";MR_{AK4};R2_{AK4}",nbn_MR,bn_MR,nbn_R2,bn_R2);
	h_R2_MR_looseS_nj45 = new TH2D("R2_MR_looseS_nj45", ";MR_{AK4};R2_{AK4}",nbn_MR,bn_MR,nbn_R2,bn_R2);
	h_R2_MR_looseS_nj6 = new TH2D("R2_MR_looseS_nj6", ";MR_{AK4};R2_{AK4}",nbn_MR,bn_MR,nbn_R2,bn_R2);
	h_R2_MR_looses = new TH2D("R2_MR_looses", ";MR_{AK4};R2_{AK4}",nbn_MR,bn_MR,nbn_R2,bn_R2);
	h_R2_MR_looses_nj45 = new TH2D("R2_MR_looses_nj45", ";MR_{AK4};R2_{AK4}",nbn_MR,bn_MR,nbn_R2,bn_R2);
	h_R2_MR_looses_nj6 = new TH2D("R2_MR_looses_nj6", ";MR_{AK4};R2_{AK4}",nbn_MR,bn_MR,nbn_R2,bn_R2);
	h_R2_MR_looseq = new TH2D("R2_MR_looseq", ";MR_{AK4};R2_{AK4}",nbn_MR,bn_MR,nbn_R2,bn_R2);
	h_R2_MR_looseq_nj45 = new TH2D("R2_MR_looseq_nj45", ";MR_{AK4};R2_{AK4}",nbn_MR,bn_MR,nbn_R2,bn_R2);
	h_R2_MR_looseq_nj6 = new TH2D("R2_MR_looseq_nj6", ";MR_{AK4};R2_{AK4}",nbn_MR,bn_MR,nbn_R2,bn_R2);
#else
	h_R2_MR_loose1S = new TH2D("R2_MR_loose1S", ";MR_{AK4};R2_{AK4}",nbn_MR,bn_MR,nbn_R2,bn_R2);
	h_R2_MR_loose2S = new TH2D("R2_MR_loose2S", ";MR_{AK4};R2_{AK4}",nbn_MR,bn_MR,nbn_R2,bn_R2);
	h_R2_MR_loose3S = new TH2D("R2_MR_loose3S", ";MR_{AK4};R2_{AK4}",nbn_MR,bn_MR,nbn_R2,bn_R2);
	h_R2_MR_loose1s = new TH2D("R2_MR_loose1s", ";MR_{AK4};R2_{AK4}",nbn_MR,bn_MR,nbn_R2,bn_R2);
	h_R2_MR_loose2s = new TH2D("R2_MR_loose2s", ";MR_{AK4};R2_{AK4}",nbn_MR,bn_MR,nbn_R2,bn_R2);
	h_R2_MR_loose3s = new TH2D("R2_MR_loose3s", ";MR_{AK4};R2_{AK4}",nbn_MR,bn_MR,nbn_R2,bn_R2);
	h_R2_MR_loose3q = new TH2D("R2_MR_loose3q", ";MR_{AK4};R2_{AK4}",nbn_MR,bn_MR,nbn_R2,bn_R2);
#endif

	for (unsigned int i=0; i<=syst_nSyst; ++i) {
		std::stringstream histoname, title;
		title<<"Systematic variation #="<<i;

		histoname<<"R2_MR_S_nj45_syst"<<i;
		vh_R2_MR_S_nj45.push_back(new TH2D(histoname.str().c_str(), (title.str()+";MR_{AK4};R2_{AK4}").c_str(),nbn_MR,bn_MR,nbn_R2, bn_R2));
		histoname.str("");
		histoname<<"R2_MR_s_nj45_syst"<<i;
		vh_R2_MR_s_nj45.push_back(new TH2D(histoname.str().c_str(), (title.str()+";MR_{AK4};R2_{AK4}").c_str(),nbn_MR,bn_MR,nbn_R2, bn_R2));
		histoname.str("");
		histoname<<"R2_MR_Q_nj45_syst"<<i;
		vh_R2_MR_Q_nj45.push_back(new TH2D(histoname.str().c_str(), (title.str()+";MR_{AK4};R2_{AK4}").c_str(),nbn_MR,bn_MR,nbn_R2, bn_R2));
		histoname.str("");
		histoname<<"R2_MR_q_nj45_syst"<<i;
		vh_R2_MR_q_nj45.push_back(new TH2D(histoname.str().c_str(), (title.str()+";MR_{AK4};R2_{AK4}").c_str(),nbn_MR,bn_MR,nbn_R2, bn_R2));
		histoname.str("");
		histoname<<"R2_MR_T_nj45_syst"<<i;
		vh_R2_MR_T_nj45.push_back(new TH2D(histoname.str().c_str(), (title.str()+";MR_{AK4};R2_{AK4}").c_str(),nbn_MR,bn_MR,nbn_R2, bn_R2));
		histoname.str("");
		histoname<<"R2_MR_W_nj45_syst"<<i;
		vh_R2_MR_W_nj45.push_back(new TH2D(histoname.str().c_str(), (title.str()+";MR_{AK4};R2_{AK4}").c_str(),nbn_MR,bn_MR,nbn_R2, bn_R2));
		histoname.str("");
		histoname<<"R2_MR_Z_nj45_syst"<<i;
		vh_R2_MR_Z_nj45.push_back(new TH2D(histoname.str().c_str(), (title.str()+";MR_{AK4};R2_{AK4}").c_str(),nbn_MR,bn_MR,nbn_R2, bn_R2));
		histoname.str("");
		histoname<<"R2_MR_L_nj45_syst"<<i;
		vh_R2_MR_L_nj45.push_back(new TH2D(histoname.str().c_str(), (title.str()+";MR_{AK4};R2_{AK4}").c_str(),nbn_MR,bn_MR,nbn_R2, bn_R2));
		histoname.str("");
		histoname<<"R2_MR_G_nj45_syst"<<i;
		vh_R2_MR_G_nj45.push_back(new TH2D(histoname.str().c_str(), (title.str()+";MR_{AK4};R2_{AK4}").c_str(),nbn_MR,bn_MR,nbn_R2, bn_R2));
		histoname.str("");
		histoname<<"R2_MR_S_nj6_syst"<<i;
		vh_R2_MR_S_nj6.push_back(new TH2D(histoname.str().c_str(), (title.str()+";MR_{AK4};R2_{AK4}").c_str(),nbn_MR,bn_MR,nbn_R2, bn_R2));
		histoname.str("");
		histoname<<"R2_MR_s_nj6_syst"<<i;
		vh_R2_MR_s_nj6.push_back(new TH2D(histoname.str().c_str(), (title.str()+";MR_{AK4};R2_{AK4}").c_str(),nbn_MR,bn_MR,nbn_R2, bn_R2));
		histoname.str("");
		histoname<<"R2_MR_Q_nj6_syst"<<i;
		vh_R2_MR_Q_nj6.push_back(new TH2D(histoname.str().c_str(), (title.str()+";MR_{AK4};R2_{AK4}").c_str(),nbn_MR,bn_MR,nbn_R2, bn_R2));
		histoname.str("");
		histoname<<"R2_MR_q_nj6_syst"<<i;
		vh_R2_MR_q_nj6.push_back(new TH2D(histoname.str().c_str(), (title.str()+";MR_{AK4};R2_{AK4}").c_str(),nbn_MR,bn_MR,nbn_R2, bn_R2));
		histoname<<"R2_MR_T_nj6_syst"<<i;
		vh_R2_MR_T_nj6.push_back(new TH2D(histoname.str().c_str(), (title.str()+";MR_{AK4};R2_{AK4}").c_str(),nbn_MR,bn_MR,nbn_R2, bn_R2));
		histoname.str("");
		histoname<<"R2_MR_W_nj6_syst"<<i;
		vh_R2_MR_W_nj6.push_back(new TH2D(histoname.str().c_str(), (title.str()+";MR_{AK4};R2_{AK4}").c_str(),nbn_MR,bn_MR,nbn_R2, bn_R2));
		histoname.str("");
		histoname<<"R2_MR_Z_nj6_syst"<<i;
		vh_R2_MR_Z_nj6.push_back(new TH2D(histoname.str().c_str(), (title.str()+";MR_{AK4};R2_{AK4}").c_str(),nbn_MR,bn_MR,nbn_R2, bn_R2));
		histoname.str("");
		histoname<<"R2_MR_L_nj6_syst"<<i;
		vh_R2_MR_L_nj6.push_back(new TH2D(histoname.str().c_str(), (title.str()+";MR_{AK4};R2_{AK4}").c_str(),nbn_MR,bn_MR,nbn_R2, bn_R2));
		histoname.str("");
		histoname<<"R2_MR_G_nj6_syst"<<i;
		vh_R2_MR_G_nj6.push_back(new TH2D(histoname.str().c_str(), (title.str()+";MR_{AK4};R2_{AK4}").c_str(),nbn_MR,bn_MR,nbn_R2, bn_R2));

	}

	h_HT_TrigMass_0 = new TH1D("h_HT_TrigMass_0", ";H_{T} [GeV]", nbn_HT, bn_HT);
	h_HT_TrigMass_1 = new TH1D("h_HT_TrigMass_1", ";H_{T} [GeV]", nbn_HT, bn_HT);

	h_AK8HT_TrigMass_0 = new TH1D("h_AK8HT_TrigMass_0", ";H_{T} [GeV]", nbn_HT, bn_HT);
	h_AK8HT_TrigMass_1 = new TH1D("h_AK8HT_TrigMass_1", ";H_{T} [GeV]", nbn_HT, bn_HT);

	h_AK8JetpT_TrigMass_0 = new TH1D("h_AK8JetpT_TrigMass_0", ";p_{T} [GeV]", nbn_AK8J1pt, bn_AK8J1pt);
	h_AK8JetpT_TrigMass_1 = new TH1D("h_AK8JetpT_TrigMass_1", ";p_{T} [GeV]", nbn_AK8J1pt, bn_AK8J1pt);

	h_AK8JetMass_TrigMass_0 = new TH1D("h_AK8JetMass_TrigMass_0", ";mass_{Jet}", 6, 60, 300);
	h_AK8JetMass_TrigMass_1 = new TH1D("h_AK8JetMass_TrigMass_1", ";mass_{Jet}", 6, 60, 300);

	h_MET_TrigMass_0 = new TH1D("h_MET_TrigMass_0", ";MET", nbn_MET, bn_MET);
	h_MET_TrigMass_1 = new TH1D("h_MET_TrigMass_1", ";MET", nbn_MET, bn_MET);

	h_MR_TrigMass_0 = new TH1D("h_MR_TrigMass_0", ";MR", nbn_MR, bn_MR);
	h_MR_TrigMass_1 = new TH1D("h_MR_TrigMass_1", ";MR", nbn_MR, bn_MR);

	h_R2_TrigMass_0 = new TH1D("h_R2_TrigMass_0", ";R2", 20, 0., 2.);
	h_R2_TrigMass_1 = new TH1D("h_R2_TrigMass_1", ";R2", 20, 0., 2.);

	h_R2_MR_TrigMass_0 = new TH2D("h_R2_MR_TrigMass_0", ";MR_{AK4};R2_{AK4}",nbn_MR,bn_MR,nbn_R2,bn_R2);
	h_R2_MR_TrigMass_1 = new TH2D("h_R2_MR_TrigMass_1", ";MR_{AK4};R2_{AK4}",nbn_MR,bn_MR,nbn_R2,bn_R2);

	h_HT_MET_TrigMass_0 = new TH2D("h_HT_MET_TrigMass_0", ";MET;H_{T}",nbnMET,bnMET,nbnHT,bnHT);
	h_HT_MET_TrigMass_1 = new TH2D("h_HT_MET_TrigMass_1", ";MET;H_{T}",nbnMET,bnMET,nbnHT,bnHT);

	h_HT_AK8JetMass_TrigMass_0 = new TH2D("h_HT_AK8JetMass_TrigMass_0", ";Mass_{AK8 leading Jet};H_{T}",nbnjmass,bnjmass,nbnHT,bnHT);
	h_HT_AK8JetMass_TrigMass_1 = new TH2D("h_HT_AK8JetMass_TrigMass_1", ";Mass_{AK8 leading Jet};H_{T}",nbnjmass,bnjmass,nbnHT,bnHT);

	h_MET_AK8JetMass_TrigMass_0 = new TH2D("h_MET_AK8JetMass_TrigMass_0", ";Mass_{AK8 leading Jet};MET",nbnjmass,bnjmass,nbnMET,bnMET);
	h_MET_AK8JetMass_TrigMass_1 = new TH2D("h_MET_AK8JetMass_TrigMass_1", ";Mass_{AK8 leading Jet};MET",nbnjmass,bnjmass,nbnMET,bnMET);

	h_AK8HT_MET_TrigMass_0 = new TH2D("h_AK8HT_MET_TrigMass_0", ";MET;H_{T}",nbnMET,bnMET,nbnHT,bnHT);
	h_AK8HT_MET_TrigMass_1 = new TH2D("h_AK8HT_MET_TrigMass_1", ";MET;H_{T}",nbnMET,bnMET,nbnHT,bnHT);

	h_AK8HT_AK8JetMass_TrigMass_0 = new TH2D("h_AK8HT_AK8JetMass_TrigMass_0", ";Mass_{AK8 leading Jet};H_{T}",nbnjmass,bnjmass,nbnHT,bnHT);
	h_AK8HT_AK8JetMass_TrigMass_1 = new TH2D("h_AK8HT_AK8JetMass_TrigMass_1", ";Mass_{AK8 leading Jet};H_{T}",nbnjmass,bnjmass,nbnHT,bnHT);

	h_HT_MET_AK8JetMass_TrigMass_0 = new TH3D("h_HT_MET_AK8JetMass_TrigMass_0", ";Mass_{AK8 leading Jet};MET;H_{T}",nbnjmass,bnjmass,nbn3DMET,bn3DMET,nbn3DHT,bn3DHT);
	h_HT_MET_AK8JetMass_TrigMass_1 = new TH3D("h_HT_MET_AK8JetMass_TrigMass_1", ";Mass_{AK8 leading Jet};MET;H_{T}",nbnjmass,bnjmass,nbn3DMET,bn3DMET,nbn3DHT,bn3DHT);

	h_AK8HT_MET_AK8JetMass_TrigMass_0 = new TH3D("h_AK8HT_MET_AK8JetMass_TrigMass_0", ";Mass_{AK8 leading Jet};MET;H_{T}",nbnjmass,bnjmass,nbn3DMET,bn3DMET,nbn3DHT,bn3DHT);
	h_AK8HT_MET_AK8JetMass_TrigMass_1 = new TH3D("h_AK8HT_MET_AK8JetMass_TrigMass_1", ";Mass_{AK8 leading Jet};MET;H_{T}",nbnjmass,bnjmass,nbn3DMET,bn3DMET,nbn3DHT,bn3DHT);

	h_HT_TrigNoMass_0 = new TH1D("h_HT_TrigNoMass_0", ";H_{T} [GeV]", nbn_HT, bn_HT);
	h_HT_TrigNoMass_1 = new TH1D("h_HT_TrigNoMass_1", ";H_{T} [GeV]", nbn_HT, bn_HT);

	h_AK8HT_TrigNoMass_0 = new TH1D("h_AK8HT_TrigNoMass_0", ";H_{T} [GeV]", nbn_HT, bn_HT);
	h_AK8HT_TrigNoMass_1 = new TH1D("h_AK8HT_TrigNoMass_1", ";H_{T} [GeV]", nbn_HT, bn_HT);

	h_AK8JetpT_TrigNoMass_0 = new TH1D("h_AK8JetpT_TrigNoMass_0", ";p_{T} [GeV]", nbn_AK8J1pt, bn_AK8J1pt);
	h_AK8JetpT_TrigNoMass_1 = new TH1D("h_AK8JetpT_TrigNoMass_1", ";p_{T} [GeV]", nbn_AK8J1pt, bn_AK8J1pt);

	h_AK8JetMass_TrigNoMass_0 = new TH1D("h_AK8JetMass_TrigNoMass_0", ";mass_{Jet}", 6, 60, 300);
	h_AK8JetMass_TrigNoMass_1 = new TH1D("h_AK8JetMass_TrigNoMass_1", ";mass_{Jet}", 6, 60, 300);

	h_MET_TrigNoMass_0 = new TH1D("h_MET_TrigNoMass_0", ";MET", nbn_MET, bn_MET);
	h_MET_TrigNoMass_1 = new TH1D("h_MET_TrigNoMass_1", ";MET", nbn_MET, bn_MET);

	h_MR_TrigNoMass_0 = new TH1D("h_MR_TrigNoMass_0", ";MR", nbn_MR, bn_MR);
	h_MR_TrigNoMass_1 = new TH1D("h_MR_TrigNoMass_1", ";MR", nbn_MR, bn_MR);

	h_R2_TrigNoMass_0 = new TH1D("h_R2_TrigNoMass_0", ";R2", 20, 0., 2.);
	h_R2_TrigNoMass_1 = new TH1D("h_R2_TrigNoMass_1", ";R2", 20, 0., 2.);

	h_R2_MR_TrigNoMass_0 = new TH2D("h_R2_MR_TrigNoMass_0", ";MR_{AK4};R2_{AK4}",nbn_MR,bn_MR,nbn_R2,bn_R2);
	h_R2_MR_TrigNoMass_1 = new TH2D("h_R2_MR_TrigNoMass_1", ";MR_{AK4};R2_{AK4}",nbn_MR,bn_MR,nbn_R2,bn_R2);

	h_HT_MET_TrigNoMass_0 = new TH2D("h_HT_MET_TrigNoMass_0", ";MET;H_{T}",nbnMET,bnMET,nbnHT,bnHT);
	h_HT_MET_TrigNoMass_1 = new TH2D("h_HT_MET_TrigNoMass_1", ";MET;H_{T}",nbnMET,bnMET,nbnHT,bnHT);

	h_HT_AK8JetMass_TrigNoMass_0 = new TH2D("h_HT_AK8JetMass_TrigNoMass_0", ";Mass_{AK8 leading Jet};H_{T}",nbnjmass,bnjmass,nbnHT,bnHT);
	h_HT_AK8JetMass_TrigNoMass_1 = new TH2D("h_HT_AK8JetMass_TrigNoMass_1", ";Mass_{AK8 leading Jet};H_{T}",nbnjmass,bnjmass,nbnHT,bnHT);

	h_MET_AK8JetMass_TrigNoMass_0 = new TH2D("h_MET_AK8JetMass_TrigNoMass_0", ";Mass_{AK8 leading Jet};MET",nbnjmass,bnjmass,nbnMET,bnMET);
	h_MET_AK8JetMass_TrigNoMass_1 = new TH2D("h_MET_AK8JetMass_TrigNoMass_1", ";Mass_{AK8 leading Jet};MET",nbnjmass,bnjmass,nbnMET,bnMET);

	h_AK8HT_MET_TrigNoMass_0 = new TH2D("h_AK8HT_MET_TrigNoMass_0", ";MET;H_{T}",nbnMET,bnMET,nbnHT,bnHT);
	h_AK8HT_MET_TrigNoMass_1 = new TH2D("h_AK8HT_MET_TrigNoMass_1", ";MET;H_{T}",nbnMET,bnMET,nbnHT,bnHT);

	h_AK8HT_AK8JetMass_TrigNoMass_0 = new TH2D("h_AK8HT_AK8JetMass_TrigNoMass_0", ";Mass_{AK8 leading Jet};H_{T}",nbnjmass,bnjmass,nbnHT,bnHT);
	h_AK8HT_AK8JetMass_TrigNoMass_1 = new TH2D("h_AK8HT_AK8JetMass_TrigNoMass_1", ";Mass_{AK8 leading Jet};H_{T}",nbnjmass,bnjmass,nbnHT,bnHT);

	h_HT_MET_AK8JetMass_TrigNoMass_0 = new TH3D("h_HT_MET_AK8JetMass_TrigNoMass_0", ";Mass_{AK8 leading Jet};MET;H_{T}",nbnjmass,bnjmass,nbn3DMET,bn3DMET,nbn3DHT,bn3DHT);
	h_HT_MET_AK8JetMass_TrigNoMass_1 = new TH3D("h_HT_MET_AK8JetMass_TrigNoMass_1", ";Mass_{AK8 leading Jet};MET;H_{T}",nbnjmass,bnjmass,nbn3DMET,bn3DMET,nbn3DHT,bn3DHT);

	h_AK8HT_MET_AK8JetMass_TrigNoMass_0 = new TH3D("h_AK8HT_MET_AK8JetMass_TrigNoMass_0", ";Mass_{AK8 leading Jet};MET;H_{T}",nbnjmass,bnjmass,nbn3DMET,bn3DMET,nbn3DHT,bn3DHT);
	h_AK8HT_MET_AK8JetMass_TrigNoMass_1 = new TH3D("h_AK8HT_MET_AK8JetMass_TrigNoMass_1", ";Mass_{AK8 leading Jet};MET;H_{T}",nbnjmass,bnjmass,nbn3DMET,bn3DMET,nbn3DHT,bn3DHT);

	h_AK8Jet1Pt_Eta_W_fakerate = new TH2D("AK8Jet1Pt_Eta_W_fakerate",";p_{T, AK8 jet} [GeV];#eta_{AK8 jet}",nbn_AK8J1pt,bn_AK8J1pt,nbn_eta,bn_eta);
	h_AK8Jet1Pt_Eta_no_W_fakerate = new TH2D("AK8Jet1Pt_Eta_no_W_fakerate",";p_{T, AK8 jet} [GeV];#eta_{AK8 jet}",nbn_AK8J1pt,bn_AK8J1pt,nbn_eta,bn_eta);
	h_AK8Jet1Pt_Eta_mW_fakerate = new TH2D("AK8Jet1Pt_Eta_mW_fakerate",";p_{T, AK8 jet} [GeV];#eta_{AK8 jet}",nbn_AK8J1pt,bn_AK8J1pt,nbn_eta,bn_eta);
	h_AK8Jet1Pt_Eta_no_mW_fakerate = new TH2D("AK8Jet1Pt_Eta_no_mW_fakerate",";p_{T, AK8 jet} [GeV];#eta_{AK8 jet}",nbn_AK8J1pt,bn_AK8J1pt,nbn_eta,bn_eta);
	h_AK8Jet1Pt_Eta_m0bW_fakerate = new TH2D("AK8Jet1Pt_Eta_m0bW_fakerate",";p_{T, AK8 jet} [GeV];#eta_{AK8 jet}",nbn_AK8J1pt,bn_AK8J1pt,nbn_eta,bn_eta);
	h_AK8Jet1Pt_Eta_no_m0bW_fakerate = new TH2D("AK8Jet1Pt_Eta_no_m0bW_fakerate",";p_{T, AK8 jet} [GeV];#eta_{AK8 jet}",nbn_AK8J1pt,bn_AK8J1pt,nbn_eta,bn_eta);
	h_AK8Jet1Pt_Eta_aW_fakerate = new TH2D("AK8Jet1Pt_Eta_aW_fakerate",";p_{T, AK8 jet} [GeV];#eta_{AK8 jet}",nbn_AK8J1pt,bn_AK8J1pt,nbn_eta,bn_eta);
	h_AK8Jet1Pt_Eta_no_aW_fakerate = new TH2D("AK8Jet1Pt_Eta_no_aW_fakerate",";p_{T, AK8 jet} [GeV];#eta_{AK8 jet}",nbn_AK8J1pt,bn_AK8J1pt,nbn_eta,bn_eta);

	h_AK8Jet1Pt_Eta_Top_fakerate = new TH2D("AK8Jet1Pt_Eta_Top_fakerate",";p_{T, AK8 jet} [GeV];#eta_{AK8 jet}",nbn_AK8J1pt,bn_AK8J1pt,nbn_eta,bn_eta);
	h_AK8Jet1Pt_Eta_no_Top_fakerate = new TH2D("AK8Jet1Pt_Eta_no_Top_fakerate",";p_{T, AK8 jet} [GeV];#eta_{AK8 jet}",nbn_AK8J1pt,bn_AK8J1pt,nbn_eta,bn_eta);
	h_AK8Jet1Pt_Eta_mTop_fakerate = new TH2D("AK8Jet1Pt_Eta_mTop_fakerate",";p_{T, AK8 jet} [GeV];#eta_{AK8 jet}",nbn_AK8J1pt,bn_AK8J1pt,nbn_eta,bn_eta);
	h_AK8Jet1Pt_Eta_no_mTop_fakerate = new TH2D("AK8Jet1Pt_Eta_no_mTop_fakerate",";p_{T, AK8 jet} [GeV];#eta_{AK8 jet}",nbn_AK8J1pt,bn_AK8J1pt,nbn_eta,bn_eta);
	h_AK8Jet1Pt_Eta_m0bTop_fakerate = new TH2D("AK8Jet1Pt_Eta_m0bTop_fakerate",";p_{T, AK8 jet} [GeV];#eta_{AK8 jet}",nbn_AK8J1pt,bn_AK8J1pt,nbn_eta,bn_eta);
	h_AK8Jet1Pt_Eta_no_m0bTop_fakerate = new TH2D("AK8Jet1Pt_Eta_no_m0bTop_fakerate",";p_{T, AK8 jet} [GeV];#eta_{AK8 jet}",nbn_AK8J1pt,bn_AK8J1pt,nbn_eta,bn_eta);
	h_AK8Jet1Pt_Eta_aTop_fakerate = new TH2D("AK8Jet1Pt_Eta_aTop_fakerate",";p_{T, AK8 jet} [GeV];#eta_{AK8 jet}",nbn_AK8J1pt,bn_AK8J1pt,nbn_eta,bn_eta);
	h_AK8Jet1Pt_Eta_no_aTop_fakerate = new TH2D("AK8Jet1Pt_Eta_no_aTop_fakerate",";p_{T, AK8 jet} [GeV];#eta_{AK8 jet}",nbn_AK8J1pt,bn_AK8J1pt,nbn_eta,bn_eta);

	h_AK8Jet1Pt_Z_fakerate = new TH1D("AK8Jet1Pt_Z_fakerate",";p_{T, AK8 jet} [GeV]",nbn_AK8J1pt,bn_AK8J1pt);
	h_AK8Jet1Pt_no_Z_fakerate = new TH1D("AK8Jet1Pt_no_Z_fakerate",";p_{T, AK8 jet} [GeV]",nbn_AK8J1pt,bn_AK8J1pt);
	h_AK8Jet1Pt_Eta_Z_fakerate = new TH2D("AK8Jet1Pt_Eta_Z_fakerate",";p_{T, AK8 jet} [GeV];#eta_{AK8 jet}",nbn_AK8J1pt,bn_AK8J1pt,nbn_eta,bn_eta);
	h_AK8Jet1Pt_Eta_no_Z_fakerate = new TH2D("AK8Jet1Pt_Eta_no_Z_fakerate",";p_{T, AK8 jet} [GeV];#eta_{AK8 jet}",nbn_AK8J1pt,bn_AK8J1pt,nbn_eta,bn_eta);
	h_AK8Jet1Pt_WtagZ_fakerate = new TH1D("AK8Jet1Pt_WtagZ_fakerate",";p_{T, AK8 jet} [GeV]",nbn_AK8J1pt,bn_AK8J1pt);
	h_AK8Jet1Pt_no_WtagZ_fakerate = new TH1D("AK8Jet1Pt_no_WtagZ_fakerate",";p_{T, AK8 jet} [GeV]",nbn_AK8J1pt,bn_AK8J1pt);
	h_AK8Jet1Pt_Eta_WtagZ_fakerate = new TH2D("AK8Jet1Pt_Eta_WtagZ_fakerate",";p_{T, AK8 jet} [GeV];#eta_{AK8 jet}",nbn_AK8J1pt,bn_AK8J1pt,nbn_eta,bn_eta);
	h_AK8Jet1Pt_Eta_no_WtagZ_fakerate = new TH2D("AK8Jet1Pt_Eta_no_WtagZ_fakerate",";p_{T, AK8 jet} [GeV];#eta_{AK8 jet}",nbn_AK8J1pt,bn_AK8J1pt,nbn_eta,bn_eta);

	h_AK8Jet1Pt_eta_GenW_no_W = new TH2D("AK8Jet1Pt_eta_GenW_no_W",";p_{T, AK8 jet} [GeV];#eta_{jet}",nbn_AK8J1pt,bn_AK8J1pt,nbn_eta,bn_eta);
	h_AK8Jet1Pt_eta_GenTop_no_Top = new TH2D("AK8Jet1Pt_eta_GenTop_no_Top",";p_{T, AK8 jet} [GeV];#eta_{jet}",nbn_AK8J1pt,bn_AK8J1pt,nbn_eta,bn_eta);
	h_AK8Jet1Pt_eta_GenW_W = new TH2D("AK8Jet1Pt_eta_GenW_W",";p_{T, AK8 jet} [GeV];#eta_{jet}",nbn_AK8J1pt,bn_AK8J1pt,nbn_eta,bn_eta);
	h_AK8Jet1Pt_eta_GenTop_Top = new TH2D("AK8Jet1Pt_eta_GenTop_Top",";p_{T, AK8 jet} [GeV];#eta_{jet}",nbn_AK8J1pt,bn_AK8J1pt,nbn_eta,bn_eta);
	h_AK8Jet1Pt_eta_FakeW_W = new TH2D("AK8Jet1Pt_eta_FakeW_W",";p_{T, AK8 jet} [GeV];#eta_{jet}",nbn_AK8J1pt,bn_AK8J1pt,nbn_eta,bn_eta);
	h_AK8Jet1Pt_eta_FakeTop_Top = new TH2D("AK8Jet1Pt_eta_FakeTop_Top",";p_{T, AK8 jet} [GeV];#eta_{jet}",nbn_AK8J1pt,bn_AK8J1pt,nbn_eta,bn_eta);

	double mrbins[6]  = { 800, 1000, 1200, 1600, 2000, 4000 };
	double r2bins[6]  = { 0.08, 0.12, 0.16, 0.24, 0.4, 1.5 };
	double isdirectbins[3] = {-0.5,0.5,1.5};
	double chisobins[21] = { 0 };
	for (int i=0; i<21; ++i) chisobins[i] = float(i)/10.;

	// Histos for the Z(nunu) estimate
	h_R2_MR_G_EB                 = new TH2D("R2_MR_G_EB",                 "G region, EB;M_{R} (GeV);R^{2}",       5,mrbins, 5,r2bins);
	h_R2_MR_G_EE                 = new TH2D("R2_MR_G_EE",                 "G region, EE;M_{R} (GeV);R^{2}",       5,mrbins, 5,r2bins);
	h_R2_MR_G_EB_nj45            = new TH2D("R2_MR_G_EB_nj45",            "G region, EB, nj45;M_{R} (GeV);R^{2}", 5,mrbins, 5,r2bins);
	h_R2_MR_G_EB_nj6             = new TH2D("R2_MR_G_EB_nj6",             "G region, EB, nj6-;M_{R} (GeV);R^{2}", 5,mrbins, 5,r2bins);
	h_R2_MR_G_EE_nj45            = new TH2D("R2_MR_G_EE_nj45 ",           "G region, EE, nj45;M_{R} (GeV);R^{2}", 5,mrbins, 5,r2bins);
	h_R2_MR_G_EE_nj6             = new TH2D("R2_MR_G_EE_nj6",             "G region, EE, nj6-;M_{R} (GeV);R^{2}", 5,mrbins, 5,r2bins);

	h_ChIsoTemplate_Fake_g_MR_EB = new TH2D("ChIsoTemplate_Fake_g_MR_EB", "G-1 region, EB;M_{R} (GeV);Photon Charged Isolation (GeV)", 5,mrbins,20,chisobins);
	h_ChIsoTemplate_Fake_g_R2_EB = new TH2D("ChIsoTemplate_Fake_g_R2_EB", "G-1 region, EB;R^{2};Photon Charged Isolation (GeV)", 5,r2bins,20,chisobins);
	h_ChIsoTemplate_Fake_g_MR_EE = new TH2D("ChIsoTemplate_Fake_g_MR_EE", "G-1 region, EE;M_{R} (GeV);Photon Charged Isolation (GeV)", 5,mrbins,20,chisobins);
	h_ChIsoTemplate_Fake_g_R2_EE = new TH2D("ChIsoTemplate_Fake_g_R2_EE", "G-1 region, EE;R^{2};Photon Charged Isolation (GeV)", 5,r2bins,20,chisobins);
	h_ChIsoTemplate_Prompt_g_MR_EB = new TH2D("ChIsoTemplate_Prompt_g_MR_EB", "G-1 region, EB;M_{R} (GeV);Photon Charged Isolation (GeV)", 5,mrbins,20,chisobins);
	h_ChIsoTemplate_Prompt_g_R2_EB = new TH2D("ChIsoTemplate_Prompt_g_R2_EB", "G-1 region, EB;R^{2};Photon Charged Isolation (GeV)", 5,r2bins,20,chisobins);
	h_ChIsoTemplate_Prompt_g_MR_EE = new TH2D("ChIsoTemplate_Prompt_g_MR_EE", "G-1 region, EE;M_{R} (GeV);Photon Charged Isolation (GeV)", 5,mrbins,20,chisobins);
	h_ChIsoTemplate_Prompt_g_R2_EE = new TH2D("ChIsoTemplate_Prompt_g_R2_EE", "G-1 region, EE;R^{2};Photon Charged Isolation (GeV)", 5,r2bins,20,chisobins);
	h_ChIsoTemplate_Fake_g_MR_EB_MC = new TH2D("ChIsoTemplate_Fake_g_MR_EB_MC", "G-1 region, EB MC;M_{R} (GeV);Photon Charged Isolation (GeV)", 5,mrbins,20,chisobins);
	h_ChIsoTemplate_Fake_g_R2_EB_MC = new TH2D("ChIsoTemplate_Fake_g_R2_EB_MC", "G-1 region, EB MC;R^{2};Photon Charged Isolation (GeV)", 5,r2bins,20,chisobins);
	h_ChIsoTemplate_Fake_g_MR_EE_MC = new TH2D("ChIsoTemplate_Fake_g_MR_EE_MC", "G-1 region, EE MC;M_{R} (GeV);Photon Charged Isolation (GeV)", 5,mrbins,20,chisobins);
	h_ChIsoTemplate_Fake_g_R2_EE_MC = new TH2D("ChIsoTemplate_Fake_g_R2_EE_MC", "G-1 region, EE MC;R^{2};Photon Charged Isolation (GeV)", 5,r2bins,20,chisobins);
	h_MR_ChIso_GNoIso_EB      = new TH2D("MR_ChIso_GNoIso_EB",      "G region (w/o CH iso.), EB;M_{R} (GeV);Photon Charged Isolation (GeV)",5,mrbins, 20,chisobins);
	h_R2_ChIso_GNoIso_EB      = new TH2D("R2_ChIso_GNoIso_EB",      "G region (w/o CH iso.), EB;R^{2};Photon Charged Isolation (GeV)",5,r2bins, 20,chisobins);
	h_MR_ChIso_GNoIso_EE      = new TH2D("MR_ChIso_GNoIso_EE",      "G region (w/o CH iso.), EE;M_{R} (GeV);Photon Charged Isolation (GeV)",5,mrbins, 20,chisobins);
	h_R2_ChIso_GNoIso_EE      = new TH2D("R2_ChIso_GNoIso_EE",      "G region (w/o CH iso.), EE;R^{2};Photon Charged Isolation (GeV)",5,r2bins, 20,chisobins);
	h_MR_ChIso_GNoIso_EB_nj45      = new TH2D("MR_ChIso_GNoIso_EB_nj45",      "G region (w/o CH iso.), EB_nj45;M_{R} (GeV);Photon Charged Isolation (GeV)",5,mrbins, 20,chisobins);
	h_R2_ChIso_GNoIso_EB_nj45      = new TH2D("R2_ChIso_GNoIso_EB_nj45",      "G region (w/o CH iso.), EB_nj45;R^{2};Photon Charged Isolation (GeV)",5,r2bins, 20,chisobins);
	h_MR_ChIso_GNoIso_EE_nj45      = new TH2D("MR_ChIso_GNoIso_EE_nj45",      "G region (w/o CH iso.), EE_nj45;M_{R} (GeV);Photon Charged Isolation (GeV)",5,mrbins, 20,chisobins);
	h_R2_ChIso_GNoIso_EE_nj45      = new TH2D("R2_ChIso_GNoIso_EE_nj45",      "G region (w/o CH iso.), EE_nj45;R^{2};Photon Charged Isolation (GeV)",5,r2bins, 20,chisobins);
	h_MR_ChIso_GNoIso_EB_nj6      = new TH2D("MR_ChIso_GNoIso_EB_nj6",      "G region (w/o CH iso.), EB_nj6;M_{R} (GeV);Photon Charged Isolation (GeV)",5,mrbins, 20,chisobins);
	h_R2_ChIso_GNoIso_EB_nj6      = new TH2D("R2_ChIso_GNoIso_EB_nj6",      "G region (w/o CH iso.), EB_nj6;R^{2};Photon Charged Isolation (GeV)",5,r2bins, 20,chisobins);
	h_MR_ChIso_GNoIso_EE_nj6      = new TH2D("MR_ChIso_GNoIso_EE_nj6",      "G region (w/o CH iso.), EE_nj6;M_{R} (GeV);Photon Charged Isolation (GeV)",5,mrbins, 20,chisobins);
	h_R2_ChIso_GNoIso_EE_nj6      = new TH2D("R2_ChIso_GNoIso_EE_nj6",      "G region (w/o CH iso.), EE_nj6;R^{2};Photon Charged Isolation (GeV)",5,r2bins, 20,chisobins);
	h_MR_ChIso_gNoIso_EB      = new TH2D("MR_ChIso_gNoIso_EB",      "g region (w/o CH iso.), EB;M_{R} (GeV);Photon Charged Isolation (GeV)",5,mrbins, 20,chisobins);
	h_R2_ChIso_gNoIso_EB      = new TH2D("R2_ChIso_gNoIso_EB",      "g region (w/o CH iso.), EB;R^{2};Photon Charged Isolation (GeV)",5,r2bins, 20,chisobins);
	h_MR_ChIso_gNoIso_EE      = new TH2D("MR_ChIso_gNoIso_EE",      "g region (w/o CH iso.), EE;M_{R} (GeV);Photon Charged Isolation (GeV)",5,mrbins, 20,chisobins);
	h_R2_ChIso_gNoIso_EE      = new TH2D("R2_ChIso_gNoIso_EE",      "g region (w/o CH iso.), EE;R^{2};Photon Charged Isolation (GeV)",5,r2bins, 20,chisobins);
	h_MR_ChIso_gNoIso_EB_nj45      = new TH2D("MR_ChIso_gNoIso_EB_nj45",      "g region (w/o CH iso.), EB_nj45;M_{R} (GeV);Photon Charged Isolation (GeV)",5,mrbins, 20,chisobins);
	h_R2_ChIso_gNoIso_EB_nj45      = new TH2D("R2_ChIso_gNoIso_EB_nj45",      "g region (w/o CH iso.), EB_nj45;R^{2};Photon Charged Isolation (GeV)",5,r2bins, 20,chisobins);
	h_MR_ChIso_gNoIso_EE_nj45      = new TH2D("MR_ChIso_gNoIso_EE_nj45",      "g region (w/o CH iso.), EE_nj45;M_{R} (GeV);Photon Charged Isolation (GeV)",5,mrbins, 20,chisobins);
	h_R2_ChIso_gNoIso_EE_nj45      = new TH2D("R2_ChIso_gNoIso_EE_nj45",      "g region (w/o CH iso.), EE_nj45;R^{2};Photon Charged Isolation (GeV)",5,r2bins, 20,chisobins);
	h_MR_ChIso_gNoIso_EB_nj6      = new TH2D("MR_ChIso_gNoIso_EB_nj6",      "g region (w/o CH iso.), EB_nj6;M_{R} (GeV);Photon Charged Isolation (GeV)",5,mrbins, 20,chisobins);
	h_R2_ChIso_gNoIso_EB_nj6      = new TH2D("R2_ChIso_gNoIso_EB_nj6",      "g region (w/o CH iso.), EB_nj6;R^{2};Photon Charged Isolation (GeV)",5,r2bins, 20,chisobins);
	h_MR_ChIso_gNoIso_EE_nj6      = new TH2D("MR_ChIso_gNoIso_EE_nj6",      "g region (w/o CH iso.), EE_nj6;M_{R} (GeV);Photon Charged Isolation (GeV)",5,mrbins, 20,chisobins);
	h_R2_ChIso_gNoIso_EE_nj6      = new TH2D("R2_ChIso_gNoIso_EE_nj6",      "g region (w/o CH iso.), EE_nj6;R^{2};Photon Charged Isolation (GeV)",5,r2bins, 20,chisobins);

	h_MR_IsDirect_G_EB        = new TH2D("MR_IsDirect_G_EB",        "G region, EB;M_{R} (GeV)", 5,mrbins, 2,isdirectbins);
	h_R2_IsDirect_G_EB        = new TH2D("R2_IsDirect_G_EB",        "G region, EB;R^{2}", 5,r2bins, 2,isdirectbins);
	h_MR_IsDirect_G_EE        = new TH2D("MR_IsDirect_G_EE",        "G region, EE;M_{R} (GeV)", 5,mrbins, 2,isdirectbins);
	h_R2_IsDirect_G_EE        = new TH2D("R2_IsDirect_G_EE",        "G region, EE;R^{2}", 5,r2bins, 2,isdirectbins);

	h_ChIsoTemplate_Fake_g_EB    = new TH3D("ChIsoTemplate_Fake_g_EB",    "G-1 region, EB;M_{R} (GeV);R^{2};Photon Charged Isolation (GeV)", 5,mrbins, 5,r2bins, 20,chisobins);
	h_ChIsoTemplate_Fake_g_EE    = new TH3D("ChIsoTemplate_Fake_g_EE",    "G-1 region, EE;M_{R} (GeV);R^{2};Photon Charged Isolation (GeV)", 5,mrbins, 5,r2bins, 20,chisobins);
	h_ChIsoTemplate_Fake_g_EB_MC = new TH3D("ChIsoTemplate_Fake_g_EB_MC", "G-1 region, EB (MC);M_{R} (GeV);R^{2};Photon Charged Isolation (GeV)", 5,mrbins, 5,r2bins, 20,chisobins);
	h_ChIsoTemplate_Fake_g_EE_MC = new TH3D("ChIsoTemplate_Fake_g_EE_MC", "G-1 region, EE (MC);M_{R} (GeV);R^{2};Photon Charged Isolation (GeV)", 5,mrbins, 5,r2bins, 20,chisobins);
	h_ChIsoTemplate_Prompt_g_EB  = new TH3D("ChIsoTemplate_Prompt_g_EB",  "G-1 region, EB;M_{R} (GeV);R^{2};Photon Charged Isolation (GeV)", 5,mrbins, 5,r2bins, 20,chisobins);
	h_ChIsoTemplate_Prompt_g_EE  = new TH3D("ChIsoTemplate_Prompt_g_EE",  "G-1 region, EE;M_{R} (GeV);R^{2};Photon Charged Isolation (GeV)", 5,mrbins, 5,r2bins, 20,chisobins);
	h_R2_MR_ChIso_GNoIso_EB      = new TH3D("R2_MR_ChIso_GNoIso_EB",      "G region (w/o CH iso.), EB;M_{R} (GeV);R^{2};Photon Charged Isolation (GeV)",      5,mrbins, 5,r2bins, 20,chisobins);
	h_R2_MR_ChIso_GNoIso_EE      = new TH3D("R2_MR_ChIso_GNoIso_EE",      "G region (w/o CH iso.), EE;M_{R} (GeV);R^{2};Photon Charged Isolation (GeV)",      5,mrbins, 5,r2bins, 20,chisobins);
	h_R2_MR_ChIso_GNoIso_EB_nj45 = new TH3D("R2_MR_ChIso_GNoIso_EB_nj45", "G region (w/o CH iso.), EB nj45;M_{R} (GeV);R^{2};Photon Charged Isolation (GeV)", 5,mrbins, 5,r2bins, 20,chisobins);
	h_R2_MR_ChIso_GNoIso_EB_nj6  = new TH3D("R2_MR_ChIso_GNoIso_EB_nj6",  "G region (w/o CH iso.), EB nj6-;M_{R} (GeV);R^{2};Photon Charged Isolation (GeV)", 5,mrbins, 5,r2bins, 20,chisobins);
	h_R2_MR_ChIso_GNoIso_EE_nj45 = new TH3D("R2_MR_ChIso_GNoIso_EE_nj45 ","G region (w/o CH iso.), EE nj45;M_{R} (GeV);R^{2};Photon Charged Isolation (GeV)", 5,mrbins, 5,r2bins, 20,chisobins);
	h_R2_MR_ChIso_GNoIso_EE_nj6  = new TH3D("R2_MR_ChIso_GNoIso_EE_nj6",  "G region (w/o CH iso.), EE nj6-;M_{R} (GeV);R^{2};Photon Charged Isolation (GeV)", 5,mrbins, 5,r2bins, 20,chisobins);
	h_R2_MR_ChIso_gNoIso_EB      = new TH3D("R2_MR_ChIso_gNoIso_EB",      "G-1 region (w/o CH iso.), EB;M_{R} (GeV);R^{2};Photon Charged Isolation (GeV)",      5,mrbins, 5,r2bins, 20,chisobins);
	h_R2_MR_ChIso_gNoIso_EE      = new TH3D("R2_MR_ChIso_gNoIso_EE",      "G-1 region (w/o CH iso.), EE;M_{R} (GeV);R^{2};Photon Charged Isolation (GeV)",      5,mrbins, 5,r2bins, 20,chisobins);
	h_R2_MR_ChIso_gNoIso_EB_nj45 = new TH3D("R2_MR_ChIso_gNoIso_EB_nj45", "G-1 region (w/o CH iso.), EB nj45;M_{R} (GeV);R^{2};Photon Charged Isolation (GeV)", 5,mrbins, 5,r2bins, 20,chisobins);
	h_R2_MR_ChIso_gNoIso_EB_nj6  = new TH3D("R2_MR_ChIso_gNoIso_EB_nj6",  "G-1 region (w/o CH iso.), EB nj6-;M_{R} (GeV);R^{2};Photon Charged Isolation (GeV)", 5,mrbins, 5,r2bins, 20,chisobins);
	h_R2_MR_ChIso_gNoIso_EE_nj45 = new TH3D("R2_MR_ChIso_gNoIso_EE_nj45 ","G-1 region (w/o CH iso.), EE nj45;M_{R} (GeV);R^{2};Photon Charged Isolation (GeV)", 5,mrbins, 5,r2bins, 20,chisobins);
	h_R2_MR_ChIso_gNoIso_EE_nj6  = new TH3D("R2_MR_ChIso_gNoIso_EE_nj6",  "G-1 region (w/o CH iso.), EE nj6-;M_{R} (GeV);R^{2};Photon Charged Isolation (GeV)", 5,mrbins, 5,r2bins, 20,chisobins);
	h_R2_MR_IsPrompt_G_EB        = new TH3D("R2_MR_IsPrompt_G_EB",        "G region, EB;M_{R} (GeV);R^{2}", 5,mrbins, 5,r2bins, 2,isdirectbins);
	h_R2_MR_IsPrompt_G_EE        = new TH3D("R2_MR_IsPrompt_G_EE",        "G region, EE;M_{R} (GeV);R^{2}", 5,mrbins, 5,r2bins, 2,isdirectbins);
	h_R2_MR_IsDirect_G_EB        = new TH3D("R2_MR_IsDirect_G_EB",        "G region, EB;M_{R} (GeV);R^{2}", 5,mrbins, 5,r2bins, 2,isdirectbins);
	h_R2_MR_IsDirect_G_EE        = new TH3D("R2_MR_IsDirect_G_EE",        "G region, EE;M_{R} (GeV);R^{2}", 5,mrbins, 5,r2bins, 2,isdirectbins);
	h_R2_MR_G_DirectPrompt       = new TH2D("R2_MR_G_DirectPrompt",       "G region (direct,prompt #gamma);M_{R} (GeV);R^{2}",       5,mrbins, 5,r2bins);
	h_R2_MR_G_DirectPrompt_nj45  = new TH2D("R2_MR_G_DirectPrompt_nj45",  "G region (direct,prompt #gamma), nj45;M_{R} (GeV);R^{2}", 5,mrbins, 5,r2bins);
	h_R2_MR_G_DirectPrompt_nj6   = new TH2D("R2_MR_G_DirectPrompt_nj6",   "G region (direct,prompt #gamma), nj6-;M_{R} (GeV);R^{2}", 5,mrbins, 5,r2bins);
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


		/*
			 float sinangle=0;
			 TLorentzVector LepTag;
			 TLorentzVector JetTag;
			 if(apply_all_cuts('p')){
			 if(nEleTest==1)LepTag.SetPtEtaPhiE(data.ele.pt[iLepTest[0]], data.ele.eta[iLepTest[0]], data.ele.phi[iLepTest[0]], data.ele.E[iLepTest[0]]);
			 if(nMuTest==1) LepTag.SetPtEtaPhiE(data.mu.pt[iLepTest[0]], data.mu.eta[iLepTest[0]], data.mu.phi[iLepTest[0]], data.mu.E[iLepTest[0]]);
			 JetTag.SetPtEtaPhiE(data.jetsAK4.pt[iJetTest[std::distance(dR_test.begin(), std::min_element(dR_test.begin(),dR_test.end()))]], data.jetsAK4.eta[iJetTest[std::distance(dR_test.begin(), std::min_element(dR_test.begin(),dR_test.end()))]], data.jetsAK4.phi[iJetTest[std::distance(dR_test.begin(), std::min_element(dR_test.begin(),dR_test.end()))]], data.jetsAK4.E[iJetTest[std::distance(dR_test.begin(), std::min_element(dR_test.begin(),dR_test.end()))]]);

			 TVector3 test1 = LepTag.Vect();
			 TVector3 test2 = JetTag.Vect();
			 sinangle = sqrt(abs(1-(test1.Dot(test2)*test1.Dot(test2)/test1.Mag2()/test2.Mag2())));


		//h_dR_min->Fill(*std::min_element(dR_test.begin(),dR_test.end()), w);
		//h_rel_pT->Fill(sinangle*data.ele.pt[iLepTest[0]], w);
		//h_rel_pT_dR_min	->Fill(*std::min_element(dR_test.begin(),dR_test.end()), sinangle*data.ele.pt[iLepTest[0]], w);
		//std::std::cout << *std::min_element(dR_test.begin(),dR_test.end()) << std::std::endl;
		//std::std::cout << sinangle*data.ele.pt[iLepTest[0]] << std::std::endl;
		if(nGenLep == 1){
		if(selected_genlep[0].DeltaR(LepTag) < 0.4){
		h_dR_min_tag->Fill(*std::min_element(dR_test.begin(),dR_test.end()), w);
		h_rel_pT_tag->Fill(sinangle*data.ele.pt[iLepTest[0]], w);
		h_rel_pT_dR_min_tag->Fill(*std::min_element(dR_test.begin(),dR_test.end()), sinangle*data.ele.pt[iLepTest[0]], w);
		}
		else if(selected_genlep[0].DeltaR(LepTag) >= 0.4){
		h_dR_min_untag->Fill(*std::min_element(dR_test.begin(),dR_test.end()), w);
		h_rel_pT_untag->Fill(sinangle*data.ele.pt[iLepTest[0]], w);
		h_rel_pT_dR_min_untag->Fill(*std::min_element(dR_test.begin(),dR_test.end()), sinangle*data.ele.pt[iLepTest[0]], w);
		}
		}

		//std::std::cout << dR_2D << std::std::endl;
		//std::std::cout << rel_pT_2D << std::std::endl;
		h_dR_min->Fill(dR_2D, w);
		h_rel_pT->Fill(rel_pT_2D, w);
		h_rel_pT_dR_min	->Fill(dR_2D, rel_pT_2D, w);
		h_MR_S_1Lep->Fill(MR, w);
		h_R2_S_1Lep->Fill(R2, w);
		h_R2_MR_S_1Lep->Fill(MR, R2, w);
		}
		if(apply_all_cuts('D')){
		h_MR_T_1Lep->Fill(MR, w);
		h_R2_T_1Lep->Fill(R2, w);
		h_R2_MR_T_1Lep->Fill(MR, R2, w);
		}
		if(apply_all_cuts('d')){
		h_MR_W_1Lep->Fill(MR, w);
		h_R2_W_1Lep->Fill(R2, w);
		h_R2_MR_W_1Lep->Fill(MR, R2, w);
		}
		*/

		if (apply_all_cuts('P')) {
			h_njet_P    ->Fill(nJet,        w);
			h_nAK8jet_P ->Fill(nJetAK8,     w);
			h_nbTight_P ->Fill(nTightBTag, w);
			h_nbMedium_P->Fill(nMediumBTag, w);
			h_nbLoose_P ->Fill(nLooseBTag, w);
			h_nw_P      ->Fill(nBoostMassTag,  w);
			h_nEleVeto_P  ->Fill(nEleVeto,	w); //cut based
			h_nEleTight_P ->Fill(nEleTight,	w); //MVA
			h_nEleMedium_P->Fill(nEleSelect,w); //MVA
			h_nEleLoose_P ->Fill(nEleLoose,	w); //MVA
			h_nMuTight_P ->Fill(nMuTight,	w); //cut
			h_nMuMedium_P->Fill(nMuSelect,w); //cut
			h_nMuSoft_P  ->Fill(nMuVeto,	w); //cut
			h_nTauVeto_P ->Fill(nTauVeto, w);
			//h_nIsoTrack_P->Fill(data.IsoTrack.size(), w);
			h_nPhoMedium_P->Fill(nPhotonSelect, w);

			h_MR_P->Fill(MR, w);
			h_R2_P->Fill(R2, w);
			h_ht_AK4_P->Fill(AK4_Ht, w); // Calculated in AnalysisBase.h
			h_MET_P->Fill(data.MET_pt,w);
			h_R2_MR_P->Fill(MR, R2, w);

			for (size_t i=0; i<2; ++i) {
				h_Megajets_pt_P->Fill(hemis_AK4[i].Pt(), w);
				h_Megajets_eta_P->Fill(hemis_AK4[i].Eta(), w);
				h_Megajets_phi_P->Fill(hemis_AK4[i].Phi(), w);
			}

			h_jet1_pt_P->Fill(data.Jet[iJet[0]].pt, w);
			h_jet1_eta_P->Fill(data.Jet[iJet[0]].eta, w);
			h_jet1_phi_P->Fill(data.Jet[iJet[0]].phi, w);
			for (size_t i=0; i<iJet.size(); ++i) {
				h_jets_pt_P->Fill(data.Jet[iJet[i]].pt, w);
				h_jets_eta_P->Fill(data.Jet[iJet[i]].eta, w);
				h_jets_phi_P->Fill(data.Jet[iJet[i]].phi, w);
			}
			h_AK8jet1_pt_P->Fill(data.FatJet[iJetAK8[0]].pt, w);
			h_AK8jet1_eta_P->Fill(data.FatJet[iJetAK8[0]].eta, w);
			h_AK8jet1_phi_P->Fill(data.FatJet[iJetAK8[0]].phi, w);
			h_AK8jet1_tau21_P->Fill(tau21.at(iJetAK8[0]),w);
			h_AK8jet1_tau32_P->Fill(tau32.at(iJetAK8[0]),w);
			for (size_t i=0; i<iJetAK8.size(); ++i) {
				h_AK8jets_pt_P->Fill(data.FatJet[iJetAK8[i]].pt, w);
				h_AK8jets_eta_P->Fill(data.FatJet[iJetAK8[i]].eta, w);
				h_AK8jets_phi_P->Fill(data.FatJet[iJetAK8[i]].phi, w);
				h_AK8jets_msoftdrop_P->Fill(data.FatJet[iJetAK8[i]].msoftdrop, w);
				h_AK8jets_tau21_P->Fill(tau21.at(iJetAK8[i]),w);
				h_AK8jets_tau32_P->Fill(tau32.at(iJetAK8[i]),w);
			}
		}

		w = sf_weight['F'];
		if (apply_all_cuts('F')){
			for (size_t i=0; i<data.FatJet.size(); ++i) {
				h_AK8Jet1Pt_Eta_no_W_fakerate->Fill(data.FatJet[i].pt, std::abs(data.FatJet[i].eta), w); 
				h_AK8Jet1Pt_Eta_no_m0bW_fakerate->Fill(data.FatJet[i].pt, std::abs(data.FatJet[i].eta), w); 
				h_AK8Jet1Pt_Eta_no_aW_fakerate->Fill(data.FatJet[i].pt, std::abs(data.FatJet[i].eta), w); 
				if(passBoostMassTag[i]) h_AK8Jet1Pt_Eta_W_fakerate->Fill(data.FatJet[i].pt, std::abs(data.FatJet[i].eta), w);
				if(passBoostMassTag[i])  h_AK8Jet1Pt_Eta_m0bW_fakerate->Fill(data.FatJet[i].pt, std::abs(data.FatJet[i].eta), w); 
				if(passBoostMassTag[i])h_AK8Jet1Pt_Eta_aW_fakerate->Fill(data.FatJet[i].pt, std::abs(data.FatJet[i].eta), w); 

				h_AK8Jet1Pt_no_Z_fakerate->Fill(data.FatJet[i].pt, w); 
				h_AK8Jet1Pt_Eta_no_Z_fakerate->Fill(data.FatJet[i].pt, std::abs(data.FatJet[i].eta), w); 
				h_AK8Jet1Pt_no_WtagZ_fakerate->Fill(data.FatJet[i].pt, w); 
				h_AK8Jet1Pt_Eta_no_WtagZ_fakerate->Fill(data.FatJet[i].pt, std::abs(data.FatJet[i].eta), w); 
			}
			for (size_t i=0; i<iGenZ.size(); ++i) {
				h_AK8Jet1Pt_Eta_Z_fakerate->Fill(data.FatJet[itGenZ[i]].pt, std::abs(data.FatJet[itGenZ[i]].eta), w);
				h_AK8Jet1Pt_Z_fakerate->Fill(data.FatJet[itGenZ[i]].pt, w);
			}
			for (size_t i=0; i<iGenWtagZ.size(); ++i) {
				h_AK8Jet1Pt_WtagZ_fakerate->Fill(data.FatJet[itGenWtagZ[i]].pt, w);
				h_AK8Jet1Pt_Eta_WtagZ_fakerate->Fill(data.FatJet[itGenWtagZ[i]].pt, std::abs(data.FatJet[itGenWtagZ[i]].eta), w);
			}
		}
		w = w_nm1['F'][4];
		if (apply_all_cuts_except('F', "0b")) {
			for (size_t i=0; i<data.FatJet.size(); ++i) {
				h_AK8Jet1Pt_Eta_no_Top_fakerate->Fill(data.FatJet[i].pt, std::abs(data.FatJet[i].eta), w); 
				h_AK8Jet1Pt_Eta_no_m0bTop_fakerate->Fill(data.FatJet[i].pt, std::abs(data.FatJet[i].eta), w); 
				h_AK8Jet1Pt_Eta_no_aTop_fakerate->Fill(data.FatJet[i].pt, std::abs(data.FatJet[i].eta), w); 
				if(passBoostMassTag[i]) h_AK8Jet1Pt_Eta_Top_fakerate->Fill(data.FatJet[i].pt, std::abs(data.FatJet[i].eta), w); 
				if(passBoostMassTag[i])h_AK8Jet1Pt_Eta_m0bTop_fakerate->Fill(data.FatJet[i].pt, std::abs(data.FatJet[i].eta), w); 
				if(passBoostMassTag[i])h_AK8Jet1Pt_Eta_aTop_fakerate->Fill(data.FatJet[i].pt, std::abs(data.FatJet[i].eta), w); 
			}
		}

		w = sf_weight['f'];
		if (apply_all_cuts('f')){
			for (size_t i=0; i<data.FatJet.size(); ++i) {
				h_AK8Jet1Pt_Eta_no_mW_fakerate->Fill(data.FatJet[i].pt, std::abs(data.FatJet[i].eta), w); 
				if(passBoostMassTag[i])  h_AK8Jet1Pt_Eta_mW_fakerate->Fill(data.FatJet[i].pt, std::abs(data.FatJet[i].eta), w); 
				h_AK8Jet1Pt_Eta_no_mTop_fakerate->Fill(data.FatJet[i].pt, std::abs(data.FatJet[i].eta), w); 
				if(passBoostMassTag[i])h_AK8Jet1Pt_Eta_mTop_fakerate->Fill(data.FatJet[i].pt, std::abs(data.FatJet[i].eta), w); 
			}
		}
		// W enriched region
		w = sf_weight['W'];
		if (apply_all_cuts('W')) {
			h_njet_W    ->Fill(nJet,        w);
			h_nAK8jet_W ->Fill(nJetAK8,     w);
			h_ht_AK4_W->Fill(AK4_Ht, w);
			h_MR_W->Fill(MR, w);
			h_R2_W->Fill(R2, w);
			h_MET_W->Fill(data.MET_pt,w);
			h_R2_MR_W->Fill(MR, R2, w);
			h_R2_MET_W->Fill(data.MET_pt, R2, w);
			h_MR_MET_W->Fill(data.MET_pt, MR, w);
			h_AK8Jet1pT_MET_W->Fill(data.MET_pt, data.FatJet[iJetAK8[0]].pt, w);
			h_MET_phi_W->Fill(data.MET_phi,w);
			if(nEleVeto==1) h_ele_pt_W->Fill(data.Electron[iEleVeto[0]].pt,w);
			else h_mu_pt_W->Fill(data.Muon[iMuVeto[0]].pt,w);

			for (size_t i=0; i<2; ++i) {
				h_Megajets_pt_W->Fill(hemis_AK4[i].Pt(), w);
				h_Megajets_eta_W->Fill(hemis_AK4[i].Eta(), w);
				h_Megajets_phi_W->Fill(hemis_AK4[i].Phi(), w);
			}

			h_jet1_pt_W->Fill(data.Jet[iJet[0]].pt, w);
			h_jet1_eta_W->Fill(data.Jet[iJet[0]].eta, w);
			h_jet1_phi_W->Fill(data.Jet[iJet[0]].phi, w);
			for (size_t i=0; i<iJet.size(); ++i) {
				h_jets_pt_W->Fill(data.Jet[iJet[i]].pt, w);
				h_jets_eta_W->Fill(data.Jet[iJet[i]].eta, w);
				h_jets_phi_W->Fill(data.Jet[iJet[i]].phi, w);
			}
			h_AK8jet1_pt_W->Fill(data.FatJet[iJetAK8[0]].pt, w);
			h_AK8jet1_eta_W->Fill(data.FatJet[iJetAK8[0]].eta, w);
			h_AK8jet1_phi_W->Fill(data.FatJet[iJetAK8[0]].phi, w);
			h_AK8jet1_tau21_W->Fill(tau21.at(iJetAK8[0]),w);
			h_AK8jet1_tau32_W->Fill(tau32.at(iJetAK8[0]),w);
			for (size_t i=0; i<iJetAK8.size(); ++i) {
				h_AK8jets_pt_W->Fill(data.FatJet[iJetAK8[i]].pt, w);
				h_AK8jets_eta_W->Fill(data.FatJet[iJetAK8[i]].eta, w);
				h_AK8jets_phi_W->Fill(data.FatJet[iJetAK8[i]].phi, w);
				h_AK8jets_msoftdrop_W->Fill(data.FatJet[iJetAK8[i]].msoftdrop, w);
				h_AK8jets_tau21_W->Fill(tau21.at(iJetAK8[i]),w);
				h_AK8jets_tau32_W->Fill(tau32.at(iJetAK8[i]),w);
			}
#if TOP == 0
			for (size_t i=0; i<iBoostMassTag.size(); ++i) {
				h_Wjets_pt_W->Fill(data.FatJet[iBoostMassTag[i]].pt, w);
				h_Wjets_eta_W->Fill(data.FatJet[iBoostMassTag[i]].eta, w);
				h_Wjets_phi_W->Fill(data.FatJet[iBoostMassTag[i]].phi, w);
				h_Wjets_tau21_W->Fill(tau21.at(iBoostMassTag[i]), w);
				h_Wjets_tau32_W->Fill(tau32.at(iBoostMassTag[i]), w);
        h_deepTagMD_WvsQCD_W->Fill(data.FatJet[iBoostMassTag[i]].deepTagMD_WvsQCD, w);
        h_deepTagMD_TvsQCD_W->Fill(data.FatJet[iBoostMassTag[i]].deepTagMD_TvsQCD, w);
        h_deepTag_WvsQCD_W->Fill(data.FatJet[iBoostMassTag[i]].deepTag_WvsQCD, w);
        h_deepTag_TvsQCD_W->Fill(data.FatJet[iBoostMassTag[i]].deepTag_TvsQCD, w);
			}
#else
			for (size_t i=0; i<iBoostMassTag.size(); ++i) {
				h_Topjets_pt_W->Fill(data.FatJet[iBoostMassTag[i]].pt, w);
				h_Topjets_eta_W->Fill(data.FatJet[iBoostMassTag[i]].eta, w);
				h_Topjets_phi_W->Fill(data.FatJet[iBoostMassTag[i]].phi, w);
				h_Topjets_tau21_W->Fill(tau21.at(iBoostMassTag[i]), w);
				h_Topjets_tau32_W->Fill(tau32.at(iBoostMassTag[i]), w);
        h_deepTagMD_WvsQCD_W->Fill(data.FatJet[iBoostMassTag[i]].deepTagMD_WvsQCD, w);
        h_deepTagMD_TvsQCD_W->Fill(data.FatJet[iBoostMassTag[i]].deepTagMD_TvsQCD, w);
        h_deepTag_WvsQCD_W->Fill(data.FatJet[iBoostMassTag[i]].deepTag_WvsQCD, w);
        h_deepTag_TvsQCD_W->Fill(data.FatJet[iBoostMassTag[i]].deepTag_TvsQCD, w);
			}
#endif

			if(nJet>=4 && nJet<6){
				h_ht_AK4_W_nj45->Fill(AK4_Ht, w);
				h_MR_W_nj45->Fill(MR, w);
				h_R2_W_nj45->Fill(R2, w);
				h_MET_W_nj45->Fill(data.MET_pt,w);
				h_R2_MR_W_nj45->Fill(MR, R2, w);
				h_MET_phi_W_nj45->Fill(data.MET_phi,w);

				h_jet1_pt_W_nj45->Fill(data.Jet[iJet[0]].pt, w);
				h_jet1_eta_W_nj45->Fill(data.Jet[iJet[0]].eta, w);
				h_jet1_phi_W_nj45->Fill(data.Jet[iJet[0]].phi, w);
				for (size_t i=0; i<iJet.size(); ++i) {
					h_jets_pt_W_nj45->Fill(data.Jet[iJet[i]].pt, w);
					h_jets_eta_W_nj45->Fill(data.Jet[iJet[i]].eta, w);
					h_jets_phi_W_nj45->Fill(data.Jet[iJet[i]].phi, w);
				}
				h_AK8jet1_pt_W_nj45->Fill(data.FatJet[iJetAK8[0]].pt, w);
				h_AK8jet1_eta_W_nj45->Fill(data.FatJet[iJetAK8[0]].eta, w);
				h_AK8jet1_phi_W_nj45->Fill(data.FatJet[iJetAK8[0]].phi, w);
				h_AK8jet1_tau21_W_nj45->Fill(tau21.at(iJetAK8[0]),w);
				h_AK8jet1_tau32_W_nj45->Fill(tau32.at(iJetAK8[0]),w);
				for (size_t i=0; i<iJetAK8.size(); ++i) {
					h_AK8jets_pt_W_nj45->Fill(data.FatJet[iJetAK8[i]].pt, w);
					h_AK8jets_eta_W_nj45->Fill(data.FatJet[iJetAK8[i]].eta, w);
					h_AK8jets_phi_W_nj45->Fill(data.FatJet[iJetAK8[i]].phi, w);
					h_AK8jets_msoftdrop_W_nj45->Fill(data.FatJet[iJetAK8[i]].msoftdrop, w);
					h_AK8jets_tau21_W_nj45->Fill(tau21.at(iJetAK8[i]),w);
					h_AK8jets_tau32_W_nj45->Fill(tau32.at(iJetAK8[i]),w);
				}
#if TOP == 0
				for (size_t i=0; i<iBoostMassTag.size(); ++i) {
					h_Wjets_pt_W_nj45->Fill(data.FatJet[iBoostMassTag[i]].pt, w);
					h_Wjets_eta_W_nj45->Fill(data.FatJet[iBoostMassTag[i]].eta, w);
					h_Wjets_phi_W_nj45->Fill(data.FatJet[iBoostMassTag[i]].phi, w);
					h_Wjets_tau21_W_nj45->Fill(tau21.at(iBoostMassTag[i]), w);
					h_Wjets_tau32_W_nj45->Fill(tau32.at(iBoostMassTag[i]), w);
				}
#else
				for (size_t i=0; i<iBoostMassTag.size(); ++i) {
					h_Topjets_pt_W_nj45->Fill(data.FatJet[iBoostMassTag[i]].pt, w);
					h_Topjets_eta_W_nj45->Fill(data.FatJet[iBoostMassTag[i]].eta, w);
					h_Topjets_phi_W_nj45->Fill(data.FatJet[iBoostMassTag[i]].phi, w);
					h_Topjets_tau21_W_nj45->Fill(tau21.at(iBoostMassTag[i]), w);
					h_Topjets_tau32_W_nj45->Fill(tau32.at(iBoostMassTag[i]), w);
				}
#endif

			}
			if(nJet>=6){
				h_ht_AK4_W_nj6->Fill(AK4_Ht, w);
				h_MR_W_nj6->Fill(MR, w);
				h_R2_W_nj6->Fill(R2, w);
				h_MET_W_nj6->Fill(data.MET_pt,w);
				h_R2_MR_W_nj6->Fill(MR, R2, w);
				h_MET_phi_W_nj6->Fill(data.MET_phi,w);

				h_jet1_pt_W_nj6->Fill(data.Jet[iJet[0]].pt, w);
				h_jet1_eta_W_nj6->Fill(data.Jet[iJet[0]].eta, w);
				h_jet1_phi_W_nj6->Fill(data.Jet[iJet[0]].phi, w);
				for (size_t i=0; i<iJet.size(); ++i) {
					h_jets_pt_W_nj6->Fill(data.Jet[iJet[i]].pt, w);
					h_jets_eta_W_nj6->Fill(data.Jet[iJet[i]].eta, w);
					h_jets_phi_W_nj6->Fill(data.Jet[iJet[i]].phi, w);
				}
				h_AK8jet1_pt_W_nj6->Fill(data.FatJet[iJetAK8[0]].pt, w);
				h_AK8jet1_eta_W_nj6->Fill(data.FatJet[iJetAK8[0]].eta, w);
				h_AK8jet1_phi_W_nj6->Fill(data.FatJet[iJetAK8[0]].phi, w);
				h_AK8jet1_tau21_W_nj6->Fill(tau21.at(iJetAK8[0]),w);
				h_AK8jet1_tau32_W_nj6->Fill(tau32.at(iJetAK8[0]),w);
				for (size_t i=0; i<iJetAK8.size(); ++i) {
					h_AK8jets_pt_W_nj6->Fill(data.FatJet[iJetAK8[i]].pt, w);
					h_AK8jets_eta_W_nj6->Fill(data.FatJet[iJetAK8[i]].eta, w);
					h_AK8jets_phi_W_nj6->Fill(data.FatJet[iJetAK8[i]].phi, w);
					h_AK8jets_msoftdrop_W_nj6->Fill(data.FatJet[iJetAK8[i]].msoftdrop, w);
					h_AK8jets_tau21_W_nj6->Fill(tau21.at(iJetAK8[i]),w);
					h_AK8jets_tau32_W_nj6->Fill(tau32.at(iJetAK8[i]),w);
				}
#if TOP == 0
				for (size_t i=0; i<iBoostMassTag.size(); ++i) {
					h_Wjets_pt_W_nj6->Fill(data.FatJet[iBoostMassTag[i]].pt, w);
					h_Wjets_eta_W_nj6->Fill(data.FatJet[iBoostMassTag[i]].eta, w);
					h_Wjets_phi_W_nj6->Fill(data.FatJet[iBoostMassTag[i]].phi, w);
					h_Wjets_tau21_W_nj6->Fill(tau21.at(iBoostMassTag[i]), w);
					h_Wjets_tau32_W_nj6->Fill(tau32.at(iBoostMassTag[i]), w);
				}
#else
				for (size_t i=0; i<iBoostMassTag.size(); ++i) {
					h_Topjets_pt_W_nj6->Fill(data.FatJet[iBoostMassTag[i]].pt, w);
					h_Topjets_eta_W_nj6->Fill(data.FatJet[iBoostMassTag[i]].eta, w);
					h_Topjets_phi_W_nj6->Fill(data.FatJet[iBoostMassTag[i]].phi, w);
					h_Topjets_tau21_W_nj6->Fill(tau21.at(iBoostMassTag[i]), w);
					h_Topjets_tau32_W_nj6->Fill(tau32.at(iBoostMassTag[i]), w);
				}
#endif
			}
		}
#if TOP == 0
		if (apply_all_cuts_except('W', "1mW")) {
			h_ht_AK4_nonW_W->Fill(AK4_Ht, w);
			h_MR_nonW_W->Fill(MR, w);
			h_R2_nonW_W->Fill(R2, w);
			h_MET_nonW_W->Fill(data.MET_pt,w);
			h_nW_nonW_W->Fill(nBoostMassTag,w);
			if(nJet>=4 && nJet<6){
				h_ht_AK4_nonW_W_nj45->Fill(AK4_Ht, w);
				h_MR_nonW_W_nj45->Fill(MR, w);
				h_R2_nonW_W_nj45->Fill(R2, w);
				h_MET_nonW_W_nj45->Fill(data.MET_pt,w);
				h_nW_nonW_W_nj45->Fill(nBoostMassTag,w);
			}
			if(nJet>=6){
				h_ht_AK4_nonW_W_nj6->Fill(AK4_Ht, w);
				h_MR_nonW_W_nj6->Fill(MR, w);
				h_R2_nonW_W_nj6->Fill(R2, w);
				h_MET_nonW_W_nj6->Fill(data.MET_pt,w);
				h_nW_nonW_W_nj6->Fill(nBoostMassTag,w);
			}
		}
#else
		if (apply_all_cuts_except('W', "1mTop")) {
			h_ht_AK4_nonTop_W->Fill(AK4_Ht, w);
			h_MR_nonTop_W->Fill(MR, w);
			h_R2_nonTop_W->Fill(R2, w);
			h_MET_nonTop_W->Fill(data.MET_pt,w);
			h_nTop_nonTop_W->Fill(nBoostMassTag,w);
			if(nJet>=4 && nJet<6){
				h_ht_AK4_nonTop_W_nj45->Fill(AK4_Ht, w);
				h_MR_nonTop_W_nj45->Fill(MR, w);
				h_R2_nonTop_W_nj45->Fill(R2, w);
				h_MET_nonTop_W_nj45->Fill(data.MET_pt,w);
				h_nTop_nonTop_W_nj45->Fill(nBoostMassTag,w);
			}
			if(nJet>=6){
				h_ht_AK4_nonTop_W_nj6->Fill(AK4_Ht, w);
				h_MR_nonTop_W_nj6->Fill(MR, w);
				h_R2_nonTop_W_nj6->Fill(R2, w);
				h_MET_nonTop_W_nj6->Fill(data.MET_pt,w);
				h_nTop_nonTop_W_nj6->Fill(nBoostMassTag,w);
			}
		}
#endif
		if (apply_all_cuts_except('W', "0b")) {
			h_ht_AK4_nonb_W->Fill(AK4_Ht, w);
			h_MR_nonb_W->Fill(MR, w);
			h_R2_nonb_W->Fill(R2, w);
			h_MET_nonb_W->Fill(data.MET_pt,w);
			h_nb_nonb_W->Fill(nLooseBTag,w);
			if(nJet>=4 && nJet<6){
				h_ht_AK4_nonb_W_nj45->Fill(AK4_Ht, w);
				h_MR_nonb_W_nj45->Fill(MR, w);
				h_R2_nonb_W_nj45->Fill(R2, w);
				h_MET_nonb_W_nj45->Fill(data.MET_pt,w);
				h_nb_nonb_W_nj45->Fill(nLooseBTag,w);
			}
			if(nJet>=6){
				h_ht_AK4_nonb_W_nj6->Fill(AK4_Ht, w);
				h_MR_nonb_W_nj6->Fill(MR, w);
				h_R2_nonb_W_nj6->Fill(R2, w);
				h_MET_nonb_W_nj6->Fill(data.MET_pt,w);
				h_nb_nonb_W_nj6->Fill(nLooseBTag,w);
			}
		}
		if (apply_all_cuts_except('W', "MT")) {
			h_ht_AK4_noMT_W->Fill(AK4_Ht, w);
			h_MR_noMT_W->Fill(MR, w);
			h_R2_noMT_W->Fill(R2, w);
			h_MET_noMT_W->Fill(data.MET_pt,w);
			h_MT_noMT_W->Fill(MT_vetolep,w);
			if(nJet>=4 && nJet<6){
				h_ht_AK4_noMT_W_nj45->Fill(AK4_Ht, w);
				h_MR_noMT_W_nj45->Fill(MR, w);
				h_R2_noMT_W_nj45->Fill(R2, w);
				h_MET_noMT_W_nj45->Fill(data.MET_pt,w);
				h_MT_noMT_W_nj45->Fill(MT_vetolep,w);
			}
			if(nJet>=6){
				h_ht_AK4_noMT_W_nj6->Fill(AK4_Ht, w);
				h_MR_noMT_W_nj6->Fill(MR, w);
				h_R2_noMT_W_nj6->Fill(R2, w);
				h_MET_noMT_W_nj6->Fill(data.MET_pt,w);
				h_MT_noMT_W_nj6->Fill(MT_vetolep,w);
			}
		}
		if (apply_all_cuts_except('W', "mDPhi")) {
			h_ht_AK4_nomDPhi_W->Fill(AK4_Ht, w);
			h_MR_nomDPhi_W->Fill(MR, w);
			h_R2_nomDPhi_W->Fill(R2, w);
			h_MET_nomDPhi_W->Fill(data.MET_pt,w);
			h_mDPhi_nomDPhi_W->Fill(dPhiRazor,w);
			if(nJet>=4 && nJet<6){
				h_ht_AK4_nomDPhi_W_nj45->Fill(AK4_Ht, w);
				h_MR_nomDPhi_W_nj45->Fill(MR, w);
				h_R2_nomDPhi_W_nj45->Fill(R2, w);
				h_MET_nomDPhi_W_nj45->Fill(data.MET_pt,w);
				h_mDPhi_nomDPhi_W_nj45->Fill(dPhiRazor,w);
			}
			if(nJet>=6){
				h_ht_AK4_nomDPhi_W_nj6->Fill(AK4_Ht, w);
				h_MR_nomDPhi_W_nj6->Fill(MR, w);
				h_R2_nomDPhi_W_nj6->Fill(R2, w);
				h_MET_nomDPhi_W_nj6->Fill(data.MET_pt,w);
				h_mDPhi_nomDPhi_W_nj6->Fill(dPhiRazor,w);
			}
		}
		std::vector<std::string> vect = {"1Lep", "MT" };
		if (apply_all_cuts_except('W', vect)) {
			h_ht_AK4_no1Lep_W->Fill(AK4_Ht, w);
			h_MR_no1Lep_W->Fill(MR, w);
			h_R2_no1Lep_W->Fill(R2, w);
			h_MET_no1Lep_W->Fill(data.MET_pt,w);
			h_nLep_no1Lep_W->Fill(nLepVeto,w);
			if(nJet>=4 && nJet<6){
				h_ht_AK4_no1Lep_W_nj45->Fill(AK4_Ht, w);
				h_MR_no1Lep_W_nj45->Fill(MR, w);
				h_R2_no1Lep_W_nj45->Fill(R2, w);
				h_MET_no1Lep_W_nj45->Fill(data.MET_pt,w);
				h_nLep_no1Lep_W_nj45->Fill(nLepVeto,w);
			}
			if(nJet>=6){
				h_ht_AK4_no1Lep_W_nj6->Fill(AK4_Ht, w);
				h_MR_no1Lep_W_nj6->Fill(MR, w);
				h_R2_no1Lep_W_nj6->Fill(R2, w);
				h_MET_no1Lep_W_nj6->Fill(data.MET_pt,w);
				h_nLep_no1Lep_W_nj6->Fill(nLepVeto,w);
			}
		}

		// top enriched region
		w = sf_weight['T'];
		if (apply_all_cuts('T')) {
			h_njet_T    ->Fill(nJet,        w);
			h_nAK8jet_T ->Fill(nJetAK8,     w);
			h_ht_AK4_T->Fill(AK4_Ht, w);
			h_MR_T->Fill(MR, w);
			h_R2_T->Fill(R2, w);
			h_MET_T->Fill(data.MET_pt,w);
			h_R2_MR_T->Fill(MR, R2, w);
			h_R2_MET_T->Fill(data.MET_pt, R2, w);
			h_MR_MET_T->Fill(data.MET_pt, MR, w);
			h_AK8Jet1pT_MET_T->Fill(data.MET_pt, data.FatJet[iJetAK8[0]].pt, w);
			h_MET_phi_T->Fill(data.MET_phi,w);
			if(nEleVeto==1) h_ele_pt_T->Fill(data.Electron[iEleVeto[0]].pt,w);
			else h_mu_pt_T->Fill(data.Muon[iMuVeto[0]].pt,w);

			for (size_t i=0; i<2; ++i) {
				h_Megajets_pt_T->Fill(hemis_AK4[i].Pt(), w);
				h_Megajets_eta_T->Fill(hemis_AK4[i].Eta(), w);
				h_Megajets_phi_T->Fill(hemis_AK4[i].Phi(), w);
			}

			h_jet1_pt_T->Fill(data.Jet[iJet[0]].pt, w);
			h_jet1_eta_T->Fill(data.Jet[iJet[0]].eta, w);
			h_jet1_phi_T->Fill(data.Jet[iJet[0]].phi, w);
			for (size_t i=0; i<iJet.size(); ++i) {
				h_jets_pt_T->Fill(data.Jet[iJet[i]].pt, w);
				h_jets_eta_T->Fill(data.Jet[iJet[i]].eta, w);
				h_jets_phi_T->Fill(data.Jet[iJet[i]].phi, w);
			}
			h_AK8jet1_pt_T->Fill(data.FatJet[iJetAK8[0]].pt, w);
			h_AK8jet1_eta_T->Fill(data.FatJet[iJetAK8[0]].eta, w);
			h_AK8jet1_phi_T->Fill(data.FatJet[iJetAK8[0]].phi, w);
			h_AK8jet1_tau21_T->Fill(tau21.at(iJetAK8[0]),w);
			h_AK8jet1_tau32_T->Fill(tau32.at(iJetAK8[0]),w);
			for (size_t i=0; i<iJetAK8.size(); ++i) {
				h_AK8jets_pt_T->Fill(data.FatJet[iJetAK8[i]].pt, w);
				h_AK8jets_eta_T->Fill(data.FatJet[iJetAK8[i]].eta, w);
				h_AK8jets_phi_T->Fill(data.FatJet[iJetAK8[i]].phi, w);
				h_AK8jets_msoftdrop_T->Fill(data.FatJet[iJetAK8[i]].msoftdrop, w);
				h_AK8jets_tau21_T->Fill(tau21.at(iJetAK8[i]),w);
				h_AK8jets_tau32_T->Fill(tau32.at(iJetAK8[i]),w);
			}
#if TOP == 0
			for (size_t i=0; i<iBoostMassTag.size(); ++i) {
				h_Wjets_pt_T->Fill(data.FatJet[iBoostMassTag[i]].pt, w);
				h_Wjets_eta_T->Fill(data.FatJet[iBoostMassTag[i]].eta, w);
				h_Wjets_phi_T->Fill(data.FatJet[iBoostMassTag[i]].phi, w);
				h_Wjets_tau21_T->Fill(tau21.at(iBoostMassTag[i]), w);
				h_Wjets_tau32_T->Fill(tau32.at(iBoostMassTag[i]), w);
        h_deepTagMD_WvsQCD_T->Fill(data.FatJet[iBoostMassTag[i]].deepTagMD_WvsQCD, w);
        h_deepTagMD_TvsQCD_T->Fill(data.FatJet[iBoostMassTag[i]].deepTagMD_TvsQCD, w);
        h_deepTag_WvsQCD_T->Fill(data.FatJet[iBoostMassTag[i]].deepTag_WvsQCD, w);
        h_deepTag_TvsQCD_T->Fill(data.FatJet[iBoostMassTag[i]].deepTag_TvsQCD, w);
			}
#else
			for (size_t i=0; i<iBoostMassTag.size(); ++i) {
				h_Topjets_pt_T->Fill(data.FatJet[iBoostMassTag[i]].pt, w);
				h_Topjets_eta_T->Fill(data.FatJet[iBoostMassTag[i]].eta, w);
				h_Topjets_phi_T->Fill(data.FatJet[iBoostMassTag[i]].phi, w);
				h_Topjets_tau21_T->Fill(tau21.at(iBoostMassTag[i]), w);
				h_Topjets_tau32_T->Fill(tau32.at(iBoostMassTag[i]), w);
        h_deepTagMD_WvsQCD_T->Fill(data.FatJet[iBoostMassTag[i]].deepTagMD_WvsQCD, w);
        h_deepTagMD_TvsQCD_T->Fill(data.FatJet[iBoostMassTag[i]].deepTagMD_TvsQCD, w);
        h_deepTag_WvsQCD_T->Fill(data.FatJet[iBoostMassTag[i]].deepTag_WvsQCD, w);
        h_deepTag_TvsQCD_T->Fill(data.FatJet[iBoostMassTag[i]].deepTag_TvsQCD, w);
			}
#endif

			if(nJet>=4 && nJet<6){
				h_ht_AK4_T_nj45->Fill(AK4_Ht, w);
				h_MR_T_nj45->Fill(MR, w);
				h_R2_T_nj45->Fill(R2, w);
				h_MET_T_nj45->Fill(data.MET_pt,w);
				h_R2_MR_T_nj45->Fill(MR, R2, w);
				h_MET_phi_T_nj45->Fill(data.MET_phi,w);

				h_jet1_pt_T_nj45->Fill(data.Jet[iJet[0]].pt, w);
				h_jet1_eta_T_nj45->Fill(data.Jet[iJet[0]].eta, w);
				h_jet1_phi_T_nj45->Fill(data.Jet[iJet[0]].phi, w);
				for (size_t i=0; i<iJet.size(); ++i) {
					h_jets_pt_T_nj45->Fill(data.Jet[iJet[i]].pt, w);
					h_jets_eta_T_nj45->Fill(data.Jet[iJet[i]].eta, w);
					h_jets_phi_T_nj45->Fill(data.Jet[iJet[i]].phi, w);
				}
				h_AK8jet1_pt_T_nj45->Fill(data.FatJet[iJetAK8[0]].pt, w);
				h_AK8jet1_eta_T_nj45->Fill(data.FatJet[iJetAK8[0]].eta, w);
				h_AK8jet1_phi_T_nj45->Fill(data.FatJet[iJetAK8[0]].phi, w);
				h_AK8jet1_tau21_T_nj45->Fill(tau21.at(iJetAK8[0]),w);
				h_AK8jet1_tau32_T_nj45->Fill(tau32.at(iJetAK8[0]),w);
				for (size_t i=0; i<iJetAK8.size(); ++i) {
					h_AK8jets_pt_T_nj45->Fill(data.FatJet[iJetAK8[i]].pt, w);
					h_AK8jets_eta_T_nj45->Fill(data.FatJet[iJetAK8[i]].eta, w);
					h_AK8jets_phi_T_nj45->Fill(data.FatJet[iJetAK8[i]].phi, w);
					h_AK8jets_msoftdrop_T_nj45->Fill(data.FatJet[iJetAK8[i]].msoftdrop, w);
					h_AK8jets_tau21_T_nj45->Fill(tau21.at(iJetAK8[i]),w);
					h_AK8jets_tau32_T_nj45->Fill(tau32.at(iJetAK8[i]),w);
				}
#if TOP == 0
				for (size_t i=0; i<iBoostMassTag.size(); ++i) {
					h_Wjets_pt_T_nj45->Fill(data.FatJet[iBoostMassTag[i]].pt, w);
					h_Wjets_eta_T_nj45->Fill(data.FatJet[iBoostMassTag[i]].eta, w);
					h_Wjets_phi_T_nj45->Fill(data.FatJet[iBoostMassTag[i]].phi, w);
					h_Wjets_tau21_T_nj45->Fill(tau21.at(iBoostMassTag[i]), w);
					h_Wjets_tau32_T_nj45->Fill(tau32.at(iBoostMassTag[i]), w);
				}
#else
				for (size_t i=0; i<iBoostMassTag.size(); ++i) {
					h_Topjets_pt_T_nj45->Fill(data.FatJet[iBoostMassTag[i]].pt, w);
					h_Topjets_eta_T_nj45->Fill(data.FatJet[iBoostMassTag[i]].eta, w);
					h_Topjets_phi_T_nj45->Fill(data.FatJet[iBoostMassTag[i]].phi, w);
					h_Topjets_tau21_T_nj45->Fill(tau21.at(iBoostMassTag[i]), w);
					h_Topjets_tau32_T_nj45->Fill(tau32.at(iBoostMassTag[i]), w);
				}
#endif
			}
			if(nJet>=6){
				h_ht_AK4_T_nj6->Fill(AK4_Ht, w);
				h_MR_T_nj6->Fill(MR, w);
				h_R2_T_nj6->Fill(R2, w);
				h_MET_T_nj6->Fill(data.MET_pt,w);
				h_R2_MR_T_nj6->Fill(MR, R2, w);
				h_MET_phi_T_nj6->Fill(data.MET_phi,w);

				h_jet1_pt_T_nj6->Fill(data.Jet[iJet[0]].pt, w);
				h_jet1_eta_T_nj6->Fill(data.Jet[iJet[0]].eta, w);
				h_jet1_phi_T_nj6->Fill(data.Jet[iJet[0]].phi, w);
				for (size_t i=0; i<iJet.size(); ++i) {
					h_jets_pt_T_nj6->Fill(data.Jet[iJet[i]].pt, w);
					h_jets_eta_T_nj6->Fill(data.Jet[iJet[i]].eta, w);
					h_jets_phi_T_nj6->Fill(data.Jet[iJet[i]].phi, w);
				}
				h_AK8jet1_pt_T_nj6->Fill(data.FatJet[iJetAK8[0]].pt, w);
				h_AK8jet1_eta_T_nj6->Fill(data.FatJet[iJetAK8[0]].eta, w);
				h_AK8jet1_phi_T_nj6->Fill(data.FatJet[iJetAK8[0]].phi, w);
				h_AK8jet1_tau21_T_nj6->Fill(tau21.at(iJetAK8[0]),w);
				h_AK8jet1_tau32_T_nj6->Fill(tau32.at(iJetAK8[0]),w);
				for (size_t i=0; i<iJetAK8.size(); ++i) {
					h_AK8jets_pt_T_nj6->Fill(data.FatJet[iJetAK8[i]].pt, w);
					h_AK8jets_eta_T_nj6->Fill(data.FatJet[iJetAK8[i]].eta, w);
					h_AK8jets_phi_T_nj6->Fill(data.FatJet[iJetAK8[i]].phi, w);
					h_AK8jets_msoftdrop_T_nj6->Fill(data.FatJet[iJetAK8[i]].msoftdrop, w);
					h_AK8jets_tau21_T_nj6->Fill(tau21.at(iJetAK8[i]),w);
					h_AK8jets_tau32_T_nj6->Fill(tau32.at(iJetAK8[i]),w);
				}
#if TOP == 0
				for (size_t i=0; i<iBoostMassTag.size(); ++i) {
					h_Wjets_pt_T_nj6->Fill(data.FatJet[iBoostMassTag[i]].pt, w);
					h_Wjets_eta_T_nj6->Fill(data.FatJet[iBoostMassTag[i]].eta, w);
					h_Wjets_phi_T_nj6->Fill(data.FatJet[iBoostMassTag[i]].phi, w);
					h_Wjets_tau21_T_nj6->Fill(tau21.at(iBoostMassTag[i]), w);
					h_Wjets_tau32_T_nj6->Fill(tau32.at(iBoostMassTag[i]), w);
				}
#else
				for (size_t i=0; i<iBoostMassTag.size(); ++i) {
					h_Topjets_pt_T_nj6->Fill(data.FatJet[iBoostMassTag[i]].pt, w);
					h_Topjets_eta_T_nj6->Fill(data.FatJet[iBoostMassTag[i]].eta, w);
					h_Topjets_phi_T_nj6->Fill(data.FatJet[iBoostMassTag[i]].phi, w);
					h_Topjets_tau21_T_nj6->Fill(tau21.at(iBoostMassTag[i]), w);
					h_Topjets_tau32_T_nj6->Fill(tau32.at(iBoostMassTag[i]), w);
				}
#endif
			}
		}
		if (apply_all_cuts_except('T', "MT")) {
			h_ht_AK4_noMT_T->Fill(AK4_Ht, w);
			h_MR_noMT_T->Fill(MR, w);
			h_R2_noMT_T->Fill(R2, w);
			h_MET_noMT_T->Fill(data.MET_pt,w);
			h_MT_noMT_T->Fill(MT_vetolep,w);

			if(nJet>=4 && nJet<6){
				h_ht_AK4_noMT_T_nj45->Fill(AK4_Ht, w);
				h_MR_noMT_T_nj45->Fill(MR, w);
				h_R2_noMT_T_nj45->Fill(R2, w);
				h_MET_noMT_T_nj45->Fill(data.MET_pt,w);
				h_MT_noMT_T_nj45->Fill(MT_vetolep,w);
			}
			if(nJet>=6){
				h_ht_AK4_noMT_T_nj6->Fill(AK4_Ht, w);
				h_MR_noMT_T_nj6->Fill(MR, w);
				h_R2_noMT_T_nj6->Fill(R2, w);
				h_MET_noMT_T_nj6->Fill(data.MET_pt,w);
				h_MT_noMT_T_nj6->Fill(MT_vetolep,w);
			}
		}
		vect = {"1Lep", "MT" };
		if (apply_all_cuts_except('T', vect)) {
			h_ht_AK4_no1Lep_T->Fill(AK4_Ht, w);
			h_MR_no1Lep_T->Fill(MR, w);
			h_R2_no1Lep_T->Fill(R2, w);
			h_MET_no1Lep_T->Fill(data.MET_pt,w);
			h_nLep_no1Lep_T->Fill(nLepVeto,w);

			if(nJet>=4 && nJet<6){
				h_ht_AK4_no1Lep_T_nj45->Fill(AK4_Ht, w);
				h_MR_no1Lep_T_nj45->Fill(MR, w);
				h_R2_no1Lep_T_nj45->Fill(R2, w);
				h_MET_no1Lep_T_nj45->Fill(data.MET_pt,w);
				h_nLep_no1Lep_T_nj45->Fill(nLepVeto,w);
			}
			if(nJet>=6){
				h_ht_AK4_no1Lep_T_nj6->Fill(AK4_Ht, w);
				h_MR_no1Lep_T_nj6->Fill(MR, w);
				h_R2_no1Lep_T_nj6->Fill(R2, w);
				h_MET_no1Lep_T_nj6->Fill(data.MET_pt,w);
				h_nLep_no1Lep_T_nj6->Fill(nLepVeto,w);
			}
		}
		if (apply_all_cuts_except('T', "mDPhi")) {
			h_ht_AK4_nomDPhi_T->Fill(AK4_Ht, w);
			h_MR_nomDPhi_T->Fill(MR, w);
			h_R2_nomDPhi_T->Fill(R2, w);
			h_MET_nomDPhi_T->Fill(data.MET_pt,w);
			h_mDPhi_nomDPhi_T->Fill(dPhiRazor,w);

			if(nJet>=4 && nJet<6){
				h_ht_AK4_nomDPhi_T_nj45->Fill(AK4_Ht, w);
				h_MR_nomDPhi_T_nj45->Fill(MR, w);
				h_R2_nomDPhi_T_nj45->Fill(R2, w);
				h_MET_nomDPhi_T_nj45->Fill(data.MET_pt,w);
				h_mDPhi_nomDPhi_T_nj45->Fill(dPhiRazor,w);
			}
			if(nJet>=6){
				h_ht_AK4_nomDPhi_T_nj6->Fill(AK4_Ht, w);
				h_MR_nomDPhi_T_nj6->Fill(MR, w);
				h_R2_nomDPhi_T_nj6->Fill(R2, w);
				h_MET_nomDPhi_T_nj6->Fill(data.MET_pt,w);
				h_mDPhi_nomDPhi_T_nj6->Fill(dPhiRazor,w);
			}
		}
#if TOP == 0
		if (apply_all_cuts_except('T', "1W")) {
			h_ht_AK4_nonW_T->Fill(AK4_Ht, w);
			h_MR_nonW_T->Fill(MR, w);
			h_R2_nonW_T->Fill(R2, w);
			h_MET_nonW_T->Fill(data.MET_pt,w);
			h_nW_nonW_T->Fill(nBoostMassTag,w);
			if(nJet>=4 && nJet<6){
				h_ht_AK4_nonW_T_nj45->Fill(AK4_Ht, w);
				h_MR_nonW_T_nj45->Fill(MR, w);
				h_R2_nonW_T_nj45->Fill(R2, w);
				h_MET_nonW_T_nj45->Fill(data.MET_pt,w);
				h_nW_nonW_T_nj45->Fill(nBoostMassTag,w);
			}
			if(nJet>=6){
				h_ht_AK4_nonW_T_nj6->Fill(AK4_Ht, w);
				h_MR_nonW_T_nj6->Fill(MR, w);
				h_R2_nonW_T_nj6->Fill(R2, w);
				h_MET_nonW_T_nj6->Fill(data.MET_pt,w);
				h_nW_nonW_T_nj6->Fill(nBoostMassTag,w);
			}
		}
#else
		if (apply_all_cuts_except('T', "1Top")) {
			h_ht_AK4_nonTop_T->Fill(AK4_Ht, w);
			h_MR_nonTop_T->Fill(MR, w);
			h_R2_nonTop_T->Fill(R2, w);
			h_MET_nonTop_T->Fill(data.MET_pt,w);
			h_nTop_nonTop_T->Fill(nBoostMassBTag,w);
			if(nJet>=4 && nJet<6){
				h_ht_AK4_nonTop_T_nj45->Fill(AK4_Ht, w);
				h_MR_nonTop_T_nj45->Fill(MR, w);
				h_R2_nonTop_T_nj45->Fill(R2, w);
				h_MET_nonTop_T_nj45->Fill(data.MET_pt,w);
				h_nTop_nonTop_T_nj45->Fill(nBoostMassBTag,w);
			}
			if(nJet>=6){
				h_ht_AK4_nonTop_T_nj6->Fill(AK4_Ht, w);
				h_MR_nonTop_T_nj6->Fill(MR, w);
				h_R2_nonTop_T_nj6->Fill(R2, w);
				h_MET_nonTop_T_nj6->Fill(data.MET_pt,w);
				h_nTop_nonTop_T_nj6->Fill(nBoostMassBTag,w);
			}
		}
#endif
#if TOP == 0
		if (apply_all_cuts_except('T', "1b")) {
			h_ht_AK4_no1b_T->Fill(AK4_Ht, w);
			h_MR_no1b_T->Fill(MR, w);
			h_R2_no1b_T->Fill(R2, w);
			h_MET_no1b_T->Fill(data.MET_pt,w);
			h_nb_no1b_T->Fill(nMediumBTag,w);

			if(nJet>=4 && nJet<6){
				h_ht_AK4_no1b_T_nj45->Fill(AK4_Ht, w);
				h_MR_no1b_T_nj6->Fill(MR, w);
				h_R2_no1b_T_nj6->Fill(R2, w);
				h_MET_no1b_T_nj6->Fill(data.MET_pt,w);
				h_nb_no1b_T_nj6->Fill(nMediumBTag,w);
			}
		}
#endif


		// Z enriched region
		w = sf_weight['Z'];
		if (apply_all_cuts('Z')) {
			h_njet_Z    ->Fill(nJet,        w);
			h_nAK8jet_Z ->Fill(nJetAK8,     w);
			h_ht_AK4_Z->Fill(AK4_Ht, w);
			h_MR_Z->Fill(MR, w);
			h_R2_Z->Fill(R2_ll, w);
			h_MET_Z->Fill(MET_ll,w);
			h_R2_MR_Z->Fill(MR, R2_ll, w);
			h_R2_MET_Z->Fill(MET_ll, R2_ll, w);
			h_MR_MET_Z->Fill(MET_ll, MR, w);
			h_AK8Jet1pT_MET_Z->Fill(MET_ll, data.FatJet[iJetAK8[0]].pt, w);
			h_MET_phi_Z->Fill(data.MET_phi,w);

			for (size_t i=0; i<2; ++i) {
				h_Megajets_pt_Z->Fill(hemis_AK4[i].Pt(), w);
				h_Megajets_eta_Z->Fill(hemis_AK4[i].Eta(), w);
				h_Megajets_phi_Z->Fill(hemis_AK4[i].Phi(), w);
			}

			h_jet1_pt_Z->Fill(data.Jet[iJet[0]].pt, w);
			h_jet1_eta_Z->Fill(data.Jet[iJet[0]].eta, w);
			h_jet1_phi_Z->Fill(data.Jet[iJet[0]].phi, w);
			for (size_t i=0; i<iJet.size(); ++i) {
				h_jets_pt_Z->Fill(data.Jet[iJet[i]].pt, w);
				h_jets_eta_Z->Fill(data.Jet[iJet[i]].eta, w);
				h_jets_phi_Z->Fill(data.Jet[iJet[i]].phi, w);
			}
			h_AK8jet1_pt_Z->Fill(data.FatJet[iJetAK8[0]].pt, w);
			h_AK8jet1_eta_Z->Fill(data.FatJet[iJetAK8[0]].eta, w);
			h_AK8jet1_phi_Z->Fill(data.FatJet[iJetAK8[0]].phi, w);
			h_AK8jet1_tau21_Z->Fill(tau21.at(iJetAK8[0]),w);
			h_AK8jet1_tau32_Z->Fill(tau32.at(iJetAK8[0]),w);
			for (size_t i=0; i<iJetAK8.size(); ++i) {
				h_AK8jets_pt_Z->Fill(data.FatJet[iJetAK8[i]].pt, w);
				h_AK8jets_eta_Z->Fill(data.FatJet[iJetAK8[i]].eta, w);
				h_AK8jets_phi_Z->Fill(data.FatJet[iJetAK8[i]].phi, w);
				h_AK8jets_msoftdrop_Z->Fill(data.FatJet[iJetAK8[i]].msoftdrop, w);
				h_AK8jets_tau21_Z->Fill(tau21.at(iJetAK8[i]),w);
				h_AK8jets_tau32_Z->Fill(tau32.at(iJetAK8[i]),w);
			}
#if TOP == 0
			for (size_t i=0; i<iBoostMassTag.size(); ++i) {
				h_Wjets_pt_Z->Fill(data.FatJet[iBoostMassTag[i]].pt, w);
				h_Wjets_eta_Z->Fill(data.FatJet[iBoostMassTag[i]].eta, w);
				h_Wjets_phi_Z->Fill(data.FatJet[iBoostMassTag[i]].phi, w);
				h_Wjets_tau21_Z->Fill(tau21.at(iBoostMassTag[i]), w);
				h_Wjets_tau32_Z->Fill(tau32.at(iBoostMassTag[i]), w);
        h_deepTagMD_WvsQCD_Z->Fill(data.FatJet[iBoostMassTag[i]].deepTagMD_WvsQCD, w);
        h_deepTagMD_TvsQCD_Z->Fill(data.FatJet[iBoostMassTag[i]].deepTagMD_TvsQCD, w);
        h_deepTag_WvsQCD_Z->Fill(data.FatJet[iBoostMassTag[i]].deepTag_WvsQCD, w);
        h_deepTag_TvsQCD_Z->Fill(data.FatJet[iBoostMassTag[i]].deepTag_TvsQCD, w);
			}
#else
			for (size_t i=0; i<iBoostMassTag.size(); ++i) {
				h_Topjets_pt_Z->Fill(data.FatJet[iBoostMassTag[i]].pt, w);
				h_Topjets_eta_Z->Fill(data.FatJet[iBoostMassTag[i]].eta, w);
				h_Topjets_phi_Z->Fill(data.FatJet[iBoostMassTag[i]].phi, w);
				h_Topjets_tau21_Z->Fill(tau21.at(iBoostMassTag[i]), w);
				h_Topjets_tau32_Z->Fill(tau32.at(iBoostMassTag[i]), w);
        h_deepTagMD_WvsQCD_Z->Fill(data.FatJet[iBoostMassTag[i]].deepTagMD_WvsQCD, w);
        h_deepTagMD_TvsQCD_Z->Fill(data.FatJet[iBoostMassTag[i]].deepTagMD_TvsQCD, w);
        h_deepTag_WvsQCD_Z->Fill(data.FatJet[iBoostMassTag[i]].deepTag_WvsQCD, w);
        h_deepTag_TvsQCD_Z->Fill(data.FatJet[iBoostMassTag[i]].deepTag_TvsQCD, w);
			}
#endif

			if(nJet>=4 && nJet<6){
				h_ht_AK4_Z_nj45->Fill(AK4_Ht, w);
				h_MR_Z_nj45->Fill(MR, w);
				h_R2_Z_nj45->Fill(R2_ll, w);
				h_MET_Z_nj45->Fill(MET_ll,w);
				h_R2_MR_Z_nj45->Fill(MR, R2_ll, w);
				h_MET_phi_Z_nj45->Fill(data.MET_phi,w);

				h_jet1_pt_Z_nj45->Fill(data.Jet[iJet[0]].pt, w);
				h_jet1_eta_Z_nj45->Fill(data.Jet[iJet[0]].eta, w);
				h_jet1_phi_Z_nj45->Fill(data.Jet[iJet[0]].phi, w);
				for (size_t i=0; i<iJet.size(); ++i) {
					h_jets_pt_Z_nj45->Fill(data.Jet[iJet[i]].pt, w);
					h_jets_eta_Z_nj45->Fill(data.Jet[iJet[i]].eta, w);
					h_jets_phi_Z_nj45->Fill(data.Jet[iJet[i]].phi, w);
				}
				h_AK8jet1_pt_Z_nj45->Fill(data.FatJet[iJetAK8[0]].pt, w);
				h_AK8jet1_eta_Z_nj45->Fill(data.FatJet[iJetAK8[0]].eta, w);
				h_AK8jet1_phi_Z_nj45->Fill(data.FatJet[iJetAK8[0]].phi, w);
				h_AK8jet1_tau21_Z_nj45->Fill(tau21.at(iJetAK8[0]),w);
				h_AK8jet1_tau32_Z_nj45->Fill(tau32.at(iJetAK8[0]),w);
				for (size_t i=0; i<iJetAK8.size(); ++i) {
					h_AK8jets_pt_Z_nj45->Fill(data.FatJet[iJetAK8[i]].pt, w);
					h_AK8jets_eta_Z_nj45->Fill(data.FatJet[iJetAK8[i]].eta, w);
					h_AK8jets_phi_Z_nj45->Fill(data.FatJet[iJetAK8[i]].phi, w);
					h_AK8jets_msoftdrop_Z_nj45->Fill(data.FatJet[iJetAK8[i]].msoftdrop, w);
					h_AK8jets_tau21_Z_nj45->Fill(tau21.at(iJetAK8[i]),w);
					h_AK8jets_tau32_Z_nj45->Fill(tau32.at(iJetAK8[i]),w);
				}
#if TOP == 0
				for (size_t i=0; i<iBoostMassTag.size(); ++i) {
					h_Wjets_pt_Z_nj45->Fill(data.FatJet[iBoostMassTag[i]].pt, w);
					h_Wjets_eta_Z_nj45->Fill(data.FatJet[iBoostMassTag[i]].eta, w);
					h_Wjets_phi_Z_nj45->Fill(data.FatJet[iBoostMassTag[i]].phi, w);
					h_Wjets_tau21_Z_nj45->Fill(tau21.at(iBoostMassTag[i]), w);
					h_Wjets_tau32_Z_nj45->Fill(tau32.at(iBoostMassTag[i]), w);
				}
#else
				for (size_t i=0; i<iBoostMassTag.size(); ++i) {
					h_Topjets_pt_Z_nj45->Fill(data.FatJet[iBoostMassTag[i]].pt, w);
					h_Topjets_eta_Z_nj45->Fill(data.FatJet[iBoostMassTag[i]].eta, w);
					h_Topjets_phi_Z_nj45->Fill(data.FatJet[iBoostMassTag[i]].phi, w);
					h_Topjets_tau21_Z_nj45->Fill(tau21.at(iBoostMassTag[i]), w);
					h_Topjets_tau32_Z_nj45->Fill(tau32.at(iBoostMassTag[i]), w);
				}
#endif
			}
			if(nJet>=6){
				h_ht_AK4_Z_nj6->Fill(AK4_Ht, w);
				h_MR_Z_nj6->Fill(MR, w);
				h_R2_Z_nj6->Fill(R2_ll, w);
				h_MET_Z_nj6->Fill(MET_ll,w);
				h_R2_MR_Z_nj6->Fill(MR, R2_ll, w);
				h_MET_phi_Z_nj6->Fill(data.MET_phi,w);

				h_jet1_pt_Z_nj6->Fill(data.Jet[iJet[0]].pt, w);
				h_jet1_eta_Z_nj6->Fill(data.Jet[iJet[0]].eta, w);
				h_jet1_phi_Z_nj6->Fill(data.Jet[iJet[0]].phi, w);
				for (size_t i=0; i<iJet.size(); ++i) {
					h_jets_pt_Z_nj6->Fill(data.Jet[iJet[i]].pt, w);
					h_jets_eta_Z_nj6->Fill(data.Jet[iJet[i]].eta, w);
					h_jets_phi_Z_nj6->Fill(data.Jet[iJet[i]].phi, w);
				}
				h_AK8jet1_pt_Z_nj6->Fill(data.FatJet[iJetAK8[0]].pt, w);
				h_AK8jet1_eta_Z_nj6->Fill(data.FatJet[iJetAK8[0]].eta, w);
				h_AK8jet1_phi_Z_nj6->Fill(data.FatJet[iJetAK8[0]].phi, w);
				h_AK8jet1_tau21_Z_nj6->Fill(tau21.at(iJetAK8[0]),w);
				h_AK8jet1_tau32_Z_nj6->Fill(tau32.at(iJetAK8[0]),w);
				for (size_t i=0; i<iJetAK8.size(); ++i) {
					h_AK8jets_pt_Z_nj6->Fill(data.FatJet[iJetAK8[i]].pt, w);
					h_AK8jets_eta_Z_nj6->Fill(data.FatJet[iJetAK8[i]].eta, w);
					h_AK8jets_phi_Z_nj6->Fill(data.FatJet[iJetAK8[i]].phi, w);
					h_AK8jets_msoftdrop_Z_nj6->Fill(data.FatJet[iJetAK8[i]].msoftdrop, w);
					h_AK8jets_tau21_Z_nj6->Fill(tau21.at(iJetAK8[i]),w);
					h_AK8jets_tau32_Z_nj6->Fill(tau32.at(iJetAK8[i]),w);
				}
#if TOP == 0
				for (size_t i=0; i<iBoostMassTag.size(); ++i) {
					h_Wjets_pt_Z_nj6->Fill(data.FatJet[iBoostMassTag[i]].pt, w);
					h_Wjets_eta_Z_nj6->Fill(data.FatJet[iBoostMassTag[i]].eta, w);
					h_Wjets_phi_Z_nj6->Fill(data.FatJet[iBoostMassTag[i]].phi, w);
					h_Wjets_tau21_Z_nj6->Fill(tau21.at(iBoostMassTag[i]), w);
					h_Wjets_tau32_Z_nj6->Fill(tau32.at(iBoostMassTag[i]), w);
				}
#else
				for (size_t i=0; i<iBoostMassTag.size(); ++i) {
					h_Topjets_pt_Z_nj6->Fill(data.FatJet[iBoostMassTag[i]].pt, w);
					h_Topjets_eta_Z_nj6->Fill(data.FatJet[iBoostMassTag[i]].eta, w);
					h_Topjets_phi_Z_nj6->Fill(data.FatJet[iBoostMassTag[i]].phi, w);
					h_Topjets_tau21_Z_nj6->Fill(tau21.at(iBoostMassTag[i]), w);
					h_Topjets_tau32_Z_nj6->Fill(tau32.at(iBoostMassTag[i]), w);
				}
#endif
			}
		}
		if (apply_all_cuts_except('Z', "mDPhi")) {
			h_ht_AK4_nomDPhi_Z->Fill(AK4_Ht, w);
			h_MR_nomDPhi_Z->Fill(MR, w);
			h_R2_nomDPhi_Z->Fill(R2_ll, w);
			h_MET_nomDPhi_Z->Fill(MET_ll,w);
			h_mDPhi_nomDPhi_Z->Fill(dPhiRazor,w);
			if(nJet>=4 && nJet<6){
				h_ht_AK4_nomDPhi_Z_nj45->Fill(AK4_Ht, w);
				h_MR_nomDPhi_Z_nj45->Fill(MR, w);
				h_R2_nomDPhi_Z_nj45->Fill(R2_ll, w);
				h_MET_nomDPhi_Z_nj45->Fill(MET_ll,w);
				h_mDPhi_nomDPhi_Z_nj45->Fill(dPhiRazor,w);
			}
			if(nJet>=6){
				h_ht_AK4_nomDPhi_Z_nj6->Fill(AK4_Ht, w);
				h_MR_nomDPhi_Z_nj6->Fill(MR, w);
				h_R2_nomDPhi_Z_nj6->Fill(R2_ll, w);
				h_MET_nomDPhi_Z_nj6->Fill(MET_ll,w);
				h_mDPhi_nomDPhi_Z_nj6->Fill(dPhiRazor,w);
			}
		}
#if TOP == 0
		if (apply_all_cuts_except('Z', "1mW")) {
			h_ht_AK4_nonW_Z->Fill(AK4_Ht, w);
			h_MR_nonW_Z->Fill(MR, w);
			h_R2_nonW_Z->Fill(R2, w);
			h_MET_nonW_Z->Fill(data.MET_pt,w);
			h_nW_nonW_Z->Fill(nBoostMassTag,w);
			if(nJet>=4 && nJet<6){
				h_ht_AK4_nonW_Z_nj45->Fill(AK4_Ht, w);
				h_MR_nonW_Z_nj45->Fill(MR, w);
				h_R2_nonW_Z_nj45->Fill(R2, w);
				h_MET_nonW_Z_nj45->Fill(data.MET_pt,w);
				h_nW_nonW_Z_nj45->Fill(nBoostMassTag,w);
			}
			if(nJet>=6){
				h_ht_AK4_nonW_Z_nj6->Fill(AK4_Ht, w);
				h_MR_nonW_Z_nj6->Fill(MR, w);
				h_R2_nonW_Z_nj6->Fill(R2, w);
				h_MET_nonW_Z_nj6->Fill(data.MET_pt,w);
				h_nW_nonW_Z_nj6->Fill(nBoostMassTag,w);
			}
		}
#else
		if (apply_all_cuts_except('Z', "1mTop")) {
			h_ht_AK4_nonTop_Z->Fill(AK4_Ht, w);
			h_MR_nonTop_Z->Fill(MR, w);
			h_R2_nonTop_Z->Fill(R2, w);
			h_MET_nonTop_Z->Fill(data.MET_pt,w);
			h_nTop_nonTop_Z->Fill(nBoostMassTag,w);
			if(nJet>=4 && nJet<6){
				h_ht_AK4_nonTop_Z_nj45->Fill(AK4_Ht, w);
				h_MR_nonTop_Z_nj45->Fill(MR, w);
				h_R2_nonTop_Z_nj45->Fill(R2, w);
				h_MET_nonTop_Z_nj45->Fill(data.MET_pt,w);
				h_nTop_nonTop_Z_nj45->Fill(nBoostMassTag,w);
			}
			if(nJet>=6){
				h_ht_AK4_nonTop_Z_nj6->Fill(AK4_Ht, w);
				h_MR_nonTop_Z_nj6->Fill(MR, w);
				h_R2_nonTop_Z_nj6->Fill(R2, w);
				h_MET_nonTop_Z_nj6->Fill(data.MET_pt,w);
				h_nTop_nonTop_Z_nj6->Fill(nBoostMassTag,w);
			}
		}
#endif
		if (apply_all_cuts_except('Z', "Mll")) {
			h_ht_AK4_noMll_Z->Fill(AK4_Ht, w);
			h_MR_noMll_Z->Fill(MR, w);
			h_R2_noMll_Z->Fill(R2_ll, w);
			h_MET_noMll_Z->Fill(MET_ll,w);
			h_Mll_noMll_Z->Fill(M_ll,w);
			if(nJet>=4 && nJet<6){
				h_ht_AK4_noMll_Z_nj45->Fill(AK4_Ht, w);
				h_MR_noMll_Z_nj45->Fill(MR, w);
				h_R2_noMll_Z_nj45->Fill(R2_ll, w);
				h_MET_noMll_Z_nj45->Fill(MET_ll,w);
				h_Mll_noMll_Z->Fill(M_ll,w);
			}
			if(nJet>=6){
				h_ht_AK4_noMll_Z_nj6->Fill(AK4_Ht, w);
				h_MR_noMll_Z_nj6->Fill(MR, w);
				h_R2_noMll_Z_nj6->Fill(R2_ll, w);
				h_MET_noMll_Z_nj6->Fill(MET_ll,w);
				h_Mll_noMll_Z->Fill(M_ll,w);
			}
		}
		vect = {"2Lep", "OppCharge", "Mll" };
		if (apply_all_cuts_except('Z', vect)) {
			h_ht_AK4_no2Lep_Z->Fill(AK4_Ht, w);
			h_MR_no2Lep_Z->Fill(MR, w);
			h_R2_no2Lep_Z->Fill(R2_ll, w);
			h_MET_no2Lep_Z->Fill(MET_ll,w);
			h_nLep_no2Lep_Z->Fill(nEleSelect+nMuSelect,w);
			if(nJet>=4 && nJet<6){
				h_ht_AK4_no2Lep_Z_nj45->Fill(AK4_Ht, w);
				h_MR_no2Lep_Z_nj45->Fill(MR, w);
				h_R2_no2Lep_Z_nj45->Fill(R2_ll, w);
				h_MET_no2Lep_Z_nj45->Fill(MET_ll,w);
				h_nLep_no2Lep_Z_nj45->Fill(nEleSelect+nMuSelect,w);
			}
			if(nJet>=6){
				h_ht_AK4_no2Lep_Z_nj6->Fill(AK4_Ht, w);
				h_MR_no2Lep_Z_nj6->Fill(MR, w);
				h_R2_no2Lep_Z_nj6->Fill(R2_ll, w);
				h_MET_no2Lep_Z_nj6->Fill(MET_ll,w);
				h_nLep_no2Lep_Z_nj6->Fill(nEleSelect+nMuSelect,w);
			}
		}

		// L enriched region
		w = sf_weight['L'];
		if (apply_all_cuts('L')) {
			h_njet_L    ->Fill(nJet,        w);
			h_nAK8jet_L ->Fill(nJetAK8,     w);
			h_ht_AK4_L->Fill(AK4_Ht, w);
			h_MR_L->Fill(MR, w);
			h_R2_L->Fill(R2_1vl, w);
			h_MET_L->Fill(data.MET_pt,w);
			h_R2_MR_L->Fill(MR,R2_1vl, w);
			h_R2_MET_L->Fill(MET_1vl, R2_1vl, w);
			h_MR_MET_L->Fill(MET_1vl, MR, w);
			h_AK8Jet1pT_MET_L->Fill(MET_1vl, data.FatJet[iJetAK8[0]].pt, w);
			h_MET_phi_L->Fill(data.MET_phi,w);
			if(nEleVeto==1) h_ele_pt_L->Fill(data.Electron[iEleVeto[0]].pt,w);
			else h_mu_pt_L->Fill(data.Muon[iMuVeto[0]].pt,w);

			for (size_t i=0; i<2; ++i) {
				h_Megajets_pt_L->Fill(hemis_AK4[i].Pt(), w);
				h_Megajets_eta_L->Fill(hemis_AK4[i].Eta(), w);
				h_Megajets_phi_L->Fill(hemis_AK4[i].Phi(), w);
			}

			h_jet1_pt_L->Fill(data.Jet[iJet[0]].pt, w);
			h_jet1_eta_L->Fill(data.Jet[iJet[0]].eta, w);
			h_jet1_phi_L->Fill(data.Jet[iJet[0]].phi, w);
			for (size_t i=0; i<iJet.size(); ++i) {
				h_jets_pt_L->Fill(data.Jet[iJet[i]].pt, w);
				h_jets_eta_L->Fill(data.Jet[iJet[i]].eta, w);
				h_jets_phi_L->Fill(data.Jet[iJet[i]].phi, w);
			}
			h_AK8jet1_pt_L->Fill(data.FatJet[iJetAK8[0]].pt, w);
			h_AK8jet1_eta_L->Fill(data.FatJet[iJetAK8[0]].eta, w);
			h_AK8jet1_phi_L->Fill(data.FatJet[iJetAK8[0]].phi, w);
			h_AK8jet1_tau21_L->Fill(tau21.at(iJetAK8[0]),w);
			h_AK8jet1_tau32_L->Fill(tau32.at(iJetAK8[0]),w);
			for (size_t i=0; i<iJetAK8.size(); ++i) {
				h_AK8jets_pt_L->Fill(data.FatJet[iJetAK8[i]].pt, w);
				h_AK8jets_eta_L->Fill(data.FatJet[iJetAK8[i]].eta, w);
				h_AK8jets_phi_L->Fill(data.FatJet[iJetAK8[i]].phi, w);
				h_AK8jets_msoftdrop_L->Fill(data.FatJet[iJetAK8[i]].msoftdrop, w);
				h_AK8jets_tau21_L->Fill(tau21.at(iJetAK8[i]),w);
				h_AK8jets_tau32_L->Fill(tau32.at(iJetAK8[i]),w);
			}
#if TOP == 0
			for (size_t i=0; i<iBoostMassTag.size(); ++i) {
				h_Wjets_pt_L->Fill(data.FatJet[iBoostMassTag[i]].pt, w);
				h_Wjets_eta_L->Fill(data.FatJet[iBoostMassTag[i]].eta, w);
				h_Wjets_phi_L->Fill(data.FatJet[iBoostMassTag[i]].phi, w);
				h_Wjets_tau21_L->Fill(tau21.at(iBoostMassTag[i]), w);
				h_Wjets_tau32_L->Fill(tau32.at(iBoostMassTag[i]), w);
        h_deepTagMD_WvsQCD_L->Fill(data.FatJet[iBoostMassTag[i]].deepTagMD_WvsQCD, w);
        h_deepTagMD_TvsQCD_L->Fill(data.FatJet[iBoostMassTag[i]].deepTagMD_TvsQCD, w);
        h_deepTag_WvsQCD_L->Fill(data.FatJet[iBoostMassTag[i]].deepTag_WvsQCD, w);
        h_deepTag_TvsQCD_L->Fill(data.FatJet[iBoostMassTag[i]].deepTag_TvsQCD, w);
			}
#else
			for (size_t i=0; i<iBoostMassTag.size(); ++i) {
				h_Topjets_pt_L->Fill(data.FatJet[iBoostMassTag[i]].pt, w);
				h_Topjets_eta_L->Fill(data.FatJet[iBoostMassTag[i]].eta, w);
				h_Topjets_phi_L->Fill(data.FatJet[iBoostMassTag[i]].phi, w);
				h_Topjets_tau21_L->Fill(tau21.at(iBoostMassTag[i]), w);
				h_Topjets_tau32_L->Fill(tau32.at(iBoostMassTag[i]), w);
        h_deepTagMD_WvsQCD_L->Fill(data.FatJet[iBoostMassTag[i]].deepTagMD_WvsQCD, w);
        h_deepTagMD_TvsQCD_L->Fill(data.FatJet[iBoostMassTag[i]].deepTagMD_TvsQCD, w);
        h_deepTag_WvsQCD_L->Fill(data.FatJet[iBoostMassTag[i]].deepTag_WvsQCD, w);
        h_deepTag_TvsQCD_L->Fill(data.FatJet[iBoostMassTag[i]].deepTag_TvsQCD, w);
			}
#endif
			if(nJet>=4 && nJet<6){
				h_ht_AK4_L_nj45->Fill(AK4_Ht, w);
				h_MR_L_nj45->Fill(MR, w);
				h_R2_L_nj45->Fill(R2_1vl, w);
				h_MET_L_nj45->Fill(MET_1vl,w);
				h_R2_MR_L_nj45->Fill(MR, R2_1vl, w);
				h_MET_phi_L_nj45->Fill(data.MET_phi,w);

				h_jet1_pt_L_nj45->Fill(data.Jet[iJet[0]].pt, w);
				h_jet1_eta_L_nj45->Fill(data.Jet[iJet[0]].eta, w);
				h_jet1_phi_L_nj45->Fill(data.Jet[iJet[0]].phi, w);
				for (size_t i=0; i<iJet.size(); ++i) {
					h_jets_pt_L_nj45->Fill(data.Jet[iJet[i]].pt, w);
					h_jets_eta_L_nj45->Fill(data.Jet[iJet[i]].eta, w);
					h_jets_phi_L_nj45->Fill(data.Jet[iJet[i]].phi, w);
				}
				h_AK8jet1_pt_L_nj45->Fill(data.FatJet[iJetAK8[0]].pt, w);
				h_AK8jet1_eta_L_nj45->Fill(data.FatJet[iJetAK8[0]].eta, w);
				h_AK8jet1_phi_L_nj45->Fill(data.FatJet[iJetAK8[0]].phi, w);
				h_AK8jet1_tau21_L_nj45->Fill(tau21.at(iJetAK8[0]),w);
				h_AK8jet1_tau32_L_nj45->Fill(tau32.at(iJetAK8[0]),w);
				for (size_t i=0; i<iJetAK8.size(); ++i) {
					h_AK8jets_pt_L_nj45->Fill(data.FatJet[iJetAK8[i]].pt, w);
					h_AK8jets_eta_L_nj45->Fill(data.FatJet[iJetAK8[i]].eta, w);
					h_AK8jets_phi_L_nj45->Fill(data.FatJet[iJetAK8[i]].phi, w);
					h_AK8jets_msoftdrop_L_nj45->Fill(data.FatJet[iJetAK8[i]].msoftdrop, w);
					h_AK8jets_tau21_L_nj45->Fill(tau21.at(iJetAK8[i]),w);
					h_AK8jets_tau32_L_nj45->Fill(tau32.at(iJetAK8[i]),w);
				}
#if TOP == 0
				for (size_t i=0; i<iBoostMassTag.size(); ++i) {
					h_Wjets_pt_L_nj45->Fill(data.FatJet[iBoostMassTag[i]].pt, w);
					h_Wjets_eta_L_nj45->Fill(data.FatJet[iBoostMassTag[i]].eta, w);
					h_Wjets_phi_L_nj45->Fill(data.FatJet[iBoostMassTag[i]].phi, w);
					h_Wjets_tau21_L_nj45->Fill(tau21.at(iBoostMassTag[i]), w);
					h_Wjets_tau32_L_nj45->Fill(tau32.at(iBoostMassTag[i]), w);
				}
#else
				for (size_t i=0; i<iBoostMassTag.size(); ++i) {
					h_Topjets_pt_L_nj45->Fill(data.FatJet[iBoostMassTag[i]].pt, w);
					h_Topjets_eta_L_nj45->Fill(data.FatJet[iBoostMassTag[i]].eta, w);
					h_Topjets_phi_L_nj45->Fill(data.FatJet[iBoostMassTag[i]].phi, w);
					h_Topjets_tau21_L_nj45->Fill(tau21.at(iBoostMassTag[i]), w);
					h_Topjets_tau32_L_nj45->Fill(tau32.at(iBoostMassTag[i]), w);
				}
#endif
			}
			if(nJet>=6){
				h_ht_AK4_L_nj6->Fill(AK4_Ht, w);
				h_MR_L_nj6->Fill(MR, w);
				h_R2_L_nj6->Fill(R2_1vl, w);
				h_MET_L_nj6->Fill(MET_1vl,w);
				h_R2_MR_L_nj6->Fill(MR, R2_1vl, w);
				h_MET_phi_L_nj6->Fill(data.MET_phi,w);

				h_jet1_pt_L_nj6->Fill(data.Jet[iJet[0]].pt, w);
				h_jet1_eta_L_nj6->Fill(data.Jet[iJet[0]].eta, w);
				h_jet1_phi_L_nj6->Fill(data.Jet[iJet[0]].phi, w);
				for (size_t i=0; i<iJet.size(); ++i) {
					h_jets_pt_L_nj6->Fill(data.Jet[iJet[i]].pt, w);
					h_jets_eta_L_nj6->Fill(data.Jet[iJet[i]].eta, w);
					h_jets_phi_L_nj6->Fill(data.Jet[iJet[i]].phi, w);
				}
				h_AK8jet1_pt_L_nj6->Fill(data.FatJet[iJetAK8[0]].pt, w);
				h_AK8jet1_eta_L_nj6->Fill(data.FatJet[iJetAK8[0]].eta, w);
				h_AK8jet1_phi_L_nj6->Fill(data.FatJet[iJetAK8[0]].phi, w);
				h_AK8jet1_tau21_L_nj6->Fill(tau21.at(iJetAK8[0]),w);
				h_AK8jet1_tau32_L_nj6->Fill(tau32.at(iJetAK8[0]),w);
				for (size_t i=0; i<iJetAK8.size(); ++i) {
					h_AK8jets_pt_L_nj6->Fill(data.FatJet[iJetAK8[i]].pt, w);
					h_AK8jets_eta_L_nj6->Fill(data.FatJet[iJetAK8[i]].eta, w);
					h_AK8jets_phi_L_nj6->Fill(data.FatJet[iJetAK8[i]].phi, w);
					h_AK8jets_msoftdrop_L_nj6->Fill(data.FatJet[iJetAK8[i]].msoftdrop, w);
					h_AK8jets_tau21_L_nj6->Fill(tau21.at(iJetAK8[i]),w);
					h_AK8jets_tau32_L_nj6->Fill(tau32.at(iJetAK8[i]),w);
				}
#if TOP == 0
				for (size_t i=0; i<iBoostMassTag.size(); ++i) {
					h_Wjets_pt_L_nj6->Fill(data.FatJet[iBoostMassTag[i]].pt, w);
					h_Wjets_eta_L_nj6->Fill(data.FatJet[iBoostMassTag[i]].eta, w);
					h_Wjets_phi_L_nj6->Fill(data.FatJet[iBoostMassTag[i]].phi, w);
					h_Wjets_tau21_L_nj6->Fill(tau21.at(iBoostMassTag[i]), w);
					h_Wjets_tau32_L_nj6->Fill(tau32.at(iBoostMassTag[i]), w);
				}
#else
				for (size_t i=0; i<iBoostMassTag.size(); ++i) {
					h_Topjets_pt_L_nj6->Fill(data.FatJet[iBoostMassTag[i]].pt, w);
					h_Topjets_eta_L_nj6->Fill(data.FatJet[iBoostMassTag[i]].eta, w);
					h_Topjets_phi_L_nj6->Fill(data.FatJet[iBoostMassTag[i]].phi, w);
					h_Topjets_tau21_L_nj6->Fill(tau21.at(iBoostMassTag[i]), w);
					h_Topjets_tau32_L_nj6->Fill(tau32.at(iBoostMassTag[i]), w);
				}
#endif
			}
		}
		vect = {"1Lep", "MT" };
		if (apply_all_cuts_except('L', vect)) {
			h_ht_AK4_no1Lep_L->Fill(AK4_Ht, w);
			h_MR_no1Lep_L->Fill(MR, w);
			h_R2_no1Lep_L->Fill(R2_1vl, w);
			h_MET_no1Lep_L->Fill(MET_1vl,w);
			h_nLep_no1Lep_L->Fill(nLepVeto,w);
			if(nJet>=4 && nJet<6){
				h_ht_AK4_no1Lep_L_nj45->Fill(AK4_Ht, w);
				h_MR_no1Lep_L_nj45->Fill(MR, w);
				h_R2_no1Lep_L_nj45->Fill(R2_1vl, w);
				h_MET_no1Lep_L_nj45->Fill(MET_1vl,w);
				h_nLep_no1Lep_L_nj45->Fill(nLepVeto,w);
			}
			if(nJet>=6){
				h_ht_AK4_no1Lep_L_nj6->Fill(AK4_Ht, w);
				h_MR_no1Lep_L_nj6->Fill(MR, w);
				h_R2_no1Lep_L_nj6->Fill(R2_1vl, w);
				h_MET_no1Lep_L_nj6->Fill(MET_1vl,w);
				h_nLep_no1Lep_L_nj6->Fill(nLepVeto,w);
			}
		}
#if TOP == 0
		if (apply_all_cuts_except('L', "1mW")) {
			h_ht_AK4_nonW_L->Fill(AK4_Ht, w);
			h_MR_nonW_L->Fill(MR, w);
			h_R2_nonW_L->Fill(R2, w);
			h_MET_nonW_L->Fill(data.MET_pt,w);
			h_nW_nonW_L->Fill(nBoostMassTag,w);
			if(nJet>=4 && nJet<6){
				h_ht_AK4_nonW_L_nj45->Fill(AK4_Ht, w);
				h_MR_nonW_L_nj45->Fill(MR, w);
				h_R2_nonW_L_nj45->Fill(R2, w);
				h_MET_nonW_L_nj45->Fill(data.MET_pt,w);
				h_nW_nonW_L_nj45->Fill(nBoostMassTag,w);
			}
			if(nJet>=6){
				h_ht_AK4_nonW_L_nj6->Fill(AK4_Ht, w);
				h_MR_nonW_L_nj6->Fill(MR, w);
				h_R2_nonW_L_nj6->Fill(R2, w);
				h_MET_nonW_L_nj6->Fill(data.MET_pt,w);
				h_nW_nonW_L_nj6->Fill(nBoostMassTag,w);
			}
		}
#else
		if (apply_all_cuts_except('L', "1mTop")) {
			h_ht_AK4_nonTop_L->Fill(AK4_Ht, w);
			h_MR_nonTop_L->Fill(MR, w);
			h_R2_nonTop_L->Fill(R2, w);
			h_MET_nonTop_L->Fill(data.MET_pt,w);
			h_nTop_nonTop_L->Fill(nBoostMassTag,w);
			if(nJet>=4 && nJet<6){
				h_ht_AK4_nonTop_L_nj45->Fill(AK4_Ht, w);
				h_MR_nonTop_L_nj45->Fill(MR, w);
				h_R2_nonTop_L_nj45->Fill(R2, w);
				h_MET_nonTop_L_nj45->Fill(data.MET_pt,w);
				h_nTop_nonTop_L_nj45->Fill(nBoostMassTag,w);
			}
			if(nJet>=6){
				h_ht_AK4_nonTop_L_nj6->Fill(AK4_Ht, w);
				h_MR_nonTop_L_nj6->Fill(MR, w);
				h_R2_nonTop_L_nj6->Fill(R2, w);
				h_MET_nonTop_L_nj6->Fill(data.MET_pt,w);
				h_nTop_nonTop_L_nj6->Fill(nBoostMassTag,w);
			}
		}
#endif
		if (apply_all_cuts_except('L', "0b")) {
			h_ht_AK4_no0b_L->Fill(AK4_Ht, w);
			h_MR_no0b_L->Fill(MR, w);
			h_R2_no0b_L->Fill(R2_1vl, w);
			h_MET_no0b_L->Fill(MET_1vl,w);
			h_nb_no0b_L->Fill(nLooseBTag,w);
			if(nJet>=4 && nJet<6){
				h_ht_AK4_no0b_L_nj45->Fill(AK4_Ht, w);
				h_MR_no0b_L_nj45->Fill(MR, w);
				h_R2_no0b_L_nj45->Fill(R2_1vl, w);
				h_MET_no0b_L_nj45->Fill(MET_1vl,w);
				h_nb_no0b_L_nj45->Fill(nLooseBTag,w);
			}
			if(nJet>=6){
				h_ht_AK4_no0b_L_nj6->Fill(AK4_Ht, w);
				h_MR_no0b_L_nj6->Fill(MR, w);
				h_R2_no0b_L_nj6->Fill(R2_1vl, w);
				h_MET_no0b_L_nj6->Fill(MET_1vl,w);
				h_nb_no0b_L_nj6->Fill(nLooseBTag,w);
			}
		}
		if (apply_all_cuts_except('L', "mDPhi")) {
			h_ht_AK4_nomDPhi_L->Fill(AK4_Ht, w);
			h_MR_nomDPhi_L->Fill(MR, w);
			h_R2_nomDPhi_L->Fill(R2_1vl, w);
			h_MET_nomDPhi_L->Fill(MET_1vl,w);
			h_mDPhi_nomDPhi_L->Fill(dPhiRazor,w);
			if(nJet>=4 && nJet<6){
				h_ht_AK4_nomDPhi_L_nj45->Fill(AK4_Ht, w);
				h_MR_nomDPhi_L_nj45->Fill(MR, w);
				h_R2_nomDPhi_L_nj45->Fill(R2_1vl, w);
				h_MET_nomDPhi_L_nj45->Fill(MET_1vl,w);
				h_mDPhi_nomDPhi_L_nj45->Fill(dPhiRazor,w);
			}
			if(nJet>=6){
				h_ht_AK4_nomDPhi_L_nj6->Fill(AK4_Ht, w);
				h_MR_nomDPhi_L_nj6->Fill(MR, w);
				h_R2_nomDPhi_L_nj6->Fill(R2_1vl, w);
				h_MET_nomDPhi_L_nj6->Fill(MET_1vl,w);
				h_mDPhi_nomDPhi_L_nj6->Fill(dPhiRazor,w);
			}
		}
		if (apply_all_cuts_except('L', "MT")) {
			h_ht_AK4_noMT_L->Fill(AK4_Ht, w);
			h_MR_noMT_L->Fill(MR, w);
			h_R2_noMT_L->Fill(R2_1vl, w);
			h_MET_noMT_L->Fill(MET_1vl,w);
			h_MT_noMT_L->Fill(MT_vetolep,w);
			if(nJet>=4 && nJet<6){
				h_ht_AK4_noMT_L_nj45->Fill(AK4_Ht, w);
				h_MR_noMT_L_nj45->Fill(MR, w);
				h_R2_noMT_L_nj45->Fill(R2_1vl, w);
				h_MET_noMT_L_nj45->Fill(MET_1vl,w);
				h_MT_noMT_L_nj45->Fill(MT_vetolep,w);
			}
			if(nJet>=6){
				h_ht_AK4_noMT_L_nj6->Fill(AK4_Ht, w);
				h_MR_noMT_L_nj6->Fill(MR, w);
				h_R2_noMT_L_nj6->Fill(R2_1vl, w);
				h_MET_noMT_L_nj6->Fill(MET_1vl,w);
				h_MT_noMT_L_nj6->Fill(MT_vetolep,w);
			}
		}
		// G enriched region
		w = sf_weight['G'];
		if (apply_all_cuts('G')) {
			h_njet_G    ->Fill(nJet,        w);
			h_nAK8jet_G ->Fill(nJetAK8,     w);
			h_ht_AK4_G->Fill(AK4_Ht, w);
			h_MR_G->Fill(MR, w);
			h_R2_G->Fill(R2_pho, w);
			h_MET_pho_G->Fill(MET_pho,w);
			h_MET_G->Fill(data.MET_pt,w);
			h_R2_MR_G->Fill(MR, R2_pho, w);
			h_R2_MET_G->Fill(MET_pho, R2_pho, w);
			h_MR_MET_G->Fill(MET_pho, MR, w);
			h_MET_phi_G->Fill(data.MET_phi,w);

			for (size_t i=0; i<2; ++i) {
				h_Megajets_pt_G->Fill(hemis_AK4[i].Pt(), w);
				h_Megajets_eta_G->Fill(hemis_AK4[i].Eta(), w);
				h_Megajets_phi_G->Fill(hemis_AK4[i].Phi(), w);
			}

			h_jet1_pt_G->Fill(data.Jet[iJet[0]].pt, w);
			h_jet1_eta_G->Fill(data.Jet[iJet[0]].eta, w);
			h_jet1_phi_G->Fill(data.Jet[iJet[0]].phi, w);
			for (size_t i=0; i<iJet.size(); ++i) {
				h_jets_pt_G->Fill(data.Jet[iJet[i]].pt, w);
				h_jets_eta_G->Fill(data.Jet[iJet[i]].eta, w);
				h_jets_phi_G->Fill(data.Jet[iJet[i]].phi, w);
			}
			h_photon_pt_G->Fill(data.Photon[iPhotonSelect[0]].pt, w);
			h_photon_eta_G->Fill(data.Photon[iPhotonSelect[0]].eta, w);
			h_photon_phi_G->Fill(data.Photon[iPhotonSelect[0]].phi, w);
			h_AK8jet1_pt_G->Fill(data.FatJet[iJetAK8[0]].pt, w);
			h_AK8jet1_eta_G->Fill(data.FatJet[iJetAK8[0]].eta, w);
			h_AK8jet1_phi_G->Fill(data.FatJet[iJetAK8[0]].phi, w);
			h_AK8jet1_tau21_G->Fill(tau21.at(iJetAK8[0]),w);
			h_AK8jet1_tau32_G->Fill(tau32.at(iJetAK8[0]),w);
			for (size_t i=0; i<iJetAK8.size(); ++i) {
				h_AK8jets_pt_G->Fill(data.FatJet[iJetAK8[i]].pt, w);
				h_AK8jets_eta_G->Fill(data.FatJet[iJetAK8[i]].eta, w);
				h_AK8jets_phi_G->Fill(data.FatJet[iJetAK8[i]].phi, w);
				h_AK8jets_msoftdrop_G->Fill(data.FatJet[iJetAK8[i]].msoftdrop, w);
				h_AK8jets_tau21_G->Fill(tau21.at(iJetAK8[i]),w);
				h_AK8jets_tau32_G->Fill(tau32.at(iJetAK8[i]),w);
			}
#if TOP == 0
			for (size_t i=0; i<iBoostMassTag.size(); ++i) {
				h_Wjets_pt_G->Fill(data.FatJet[iBoostMassTag[i]].pt, w);
				h_Wjets_eta_G->Fill(data.FatJet[iBoostMassTag[i]].eta, w);
				h_Wjets_phi_G->Fill(data.FatJet[iBoostMassTag[i]].phi, w);
				h_Wjets_tau21_G->Fill(tau21.at(iBoostMassTag[i]), w);
				h_Wjets_tau32_G->Fill(tau32.at(iBoostMassTag[i]), w);
        h_deepTagMD_WvsQCD_G->Fill(data.FatJet[iBoostMassTag[i]].deepTagMD_WvsQCD, w);
        h_deepTagMD_TvsQCD_G->Fill(data.FatJet[iBoostMassTag[i]].deepTagMD_TvsQCD, w);
        h_deepTag_WvsQCD_G->Fill(data.FatJet[iBoostMassTag[i]].deepTag_WvsQCD, w);
        h_deepTag_TvsQCD_G->Fill(data.FatJet[iBoostMassTag[i]].deepTag_TvsQCD, w);
			}
#else
			for (size_t i=0; i<iBoostMassTag.size(); ++i) {
				h_Topjets_pt_G->Fill(data.FatJet[iBoostMassTag[i]].pt, w);
				h_Topjets_eta_G->Fill(data.FatJet[iBoostMassTag[i]].eta, w);
				h_Topjets_phi_G->Fill(data.FatJet[iBoostMassTag[i]].phi, w);
				h_Topjets_tau21_G->Fill(tau21.at(iBoostMassTag[i]), w);
				h_Topjets_tau32_G->Fill(tau32.at(iBoostMassTag[i]), w);
        h_deepTagMD_WvsQCD_G->Fill(data.FatJet[iBoostMassTag[i]].deepTagMD_WvsQCD, w);
        h_deepTagMD_TvsQCD_G->Fill(data.FatJet[iBoostMassTag[i]].deepTagMD_TvsQCD, w);
        h_deepTag_WvsQCD_G->Fill(data.FatJet[iBoostMassTag[i]].deepTag_WvsQCD, w);
        h_deepTag_TvsQCD_G->Fill(data.FatJet[iBoostMassTag[i]].deepTag_TvsQCD, w);
			}
#endif
			if(nJet>=4 && nJet<6){
				h_ht_AK4_G_nj45->Fill(AK4_Ht, w);
				h_MR_G_nj45->Fill(MR, w);
				h_R2_G_nj45->Fill(R2_pho, w);
				h_MET_pho_G_nj45->Fill(MET_pho,w);
				h_MET_G_nj45->Fill(data.MET_pt,w);
				h_R2_MR_G_nj45->Fill(MR, R2_pho, w);
				h_MET_phi_G_nj45->Fill(data.MET_phi,w);

				h_jet1_pt_G_nj45->Fill(data.Jet[iJet[0]].pt, w);
				h_jet1_eta_G_nj45->Fill(data.Jet[iJet[0]].eta, w);
				h_jet1_phi_G_nj45->Fill(data.Jet[iJet[0]].phi, w);
				for (size_t i=0; i<iJet.size(); ++i) {
					h_jets_pt_G_nj45->Fill(data.Jet[iJet[i]].pt, w);
					h_jets_eta_G_nj45->Fill(data.Jet[iJet[i]].eta, w);
					h_jets_phi_G_nj45->Fill(data.Jet[iJet[i]].phi, w);
				}
				h_photon_pt_G_nj45->Fill(data.Photon[iPhotonSelect[0]].pt, w);
				h_photon_eta_G_nj45->Fill(data.Photon[iPhotonSelect[0]].eta, w);
				h_photon_phi_G_nj45->Fill(data.Photon[iPhotonSelect[0]].phi, w);
				h_AK8jet1_pt_G_nj45->Fill(data.FatJet[iJetAK8[0]].pt, w);
				h_AK8jet1_eta_G_nj45->Fill(data.FatJet[iJetAK8[0]].eta, w);
				h_AK8jet1_phi_G_nj45->Fill(data.FatJet[iJetAK8[0]].phi, w);
				h_AK8jet1_tau21_G_nj45->Fill(tau21.at(iJetAK8[0]),w);
				h_AK8jet1_tau32_G_nj45->Fill(tau32.at(iJetAK8[0]),w);
				for (size_t i=0; i<iJetAK8.size(); ++i) {
					h_AK8jets_pt_G_nj45->Fill(data.FatJet[iJetAK8[i]].pt, w);
					h_AK8jets_eta_G_nj45->Fill(data.FatJet[iJetAK8[i]].eta, w);
					h_AK8jets_phi_G_nj45->Fill(data.FatJet[iJetAK8[i]].phi, w);
					h_AK8jets_msoftdrop_G_nj45->Fill(data.FatJet[iJetAK8[i]].msoftdrop, w);
					h_AK8jets_tau21_G_nj45->Fill(tau21.at(iJetAK8[i]),w);
					h_AK8jets_tau32_G_nj45->Fill(tau32.at(iJetAK8[i]),w);
				}
#if TOP == 0
				for (size_t i=0; i<iBoostMassTag.size(); ++i) {
					h_Wjets_pt_G_nj45->Fill(data.FatJet[iBoostMassTag[i]].pt, w);
					h_Wjets_eta_G_nj45->Fill(data.FatJet[iBoostMassTag[i]].eta, w);
					h_Wjets_phi_G_nj45->Fill(data.FatJet[iBoostMassTag[i]].phi, w);
					h_Wjets_tau21_G_nj45->Fill(tau21.at(iBoostMassTag[i]), w);
					h_Wjets_tau32_G_nj45->Fill(tau32.at(iBoostMassTag[i]), w);
				}
#else
				for (size_t i=0; i<iBoostMassTag.size(); ++i) {
					h_Topjets_pt_G_nj45->Fill(data.FatJet[iBoostMassTag[i]].pt, w);
					h_Topjets_eta_G_nj45->Fill(data.FatJet[iBoostMassTag[i]].eta, w);
					h_Topjets_phi_G_nj45->Fill(data.FatJet[iBoostMassTag[i]].phi, w);
					h_Topjets_tau21_G_nj45->Fill(tau21.at(iBoostMassTag[i]), w);
					h_Topjets_tau32_G_nj45->Fill(tau32.at(iBoostMassTag[i]), w);
				}
#endif
			}
			if(nJet>=6){
				h_ht_AK4_G_nj6->Fill(AK4_Ht, w);
				h_MR_G_nj6->Fill(MR, w);
				h_R2_G_nj6->Fill(R2_pho, w);
				h_MET_pho_G_nj6->Fill(MET_pho,w);
				h_MET_G_nj6->Fill(data.MET_pt,w);
				h_R2_MR_G_nj6->Fill(MR, R2_pho, w);
				h_MET_phi_G_nj6->Fill(data.MET_phi,w);

				h_jet1_pt_G_nj6->Fill(data.Jet[iJet[0]].pt, w);
				h_jet1_eta_G_nj6->Fill(data.Jet[iJet[0]].eta, w);
				h_jet1_phi_G_nj6->Fill(data.Jet[iJet[0]].phi, w);
				for (size_t i=0; i<iJet.size(); ++i) {
					h_jets_pt_G_nj6->Fill(data.Jet[iJet[i]].pt, w);
					h_jets_eta_G_nj6->Fill(data.Jet[iJet[i]].eta, w);
					h_jets_phi_G_nj6->Fill(data.Jet[iJet[i]].phi, w);
				}
				h_photon_pt_G_nj6->Fill(data.Photon[iPhotonSelect[0]].pt, w);
				h_photon_eta_G_nj6->Fill(data.Photon[iPhotonSelect[0]].eta, w);
				h_photon_phi_G_nj6->Fill(data.Photon[iPhotonSelect[0]].phi, w);
				h_AK8jet1_pt_G_nj6->Fill(data.FatJet[iJetAK8[0]].pt, w);
				h_AK8jet1_eta_G_nj6->Fill(data.FatJet[iJetAK8[0]].eta, w);
				h_AK8jet1_phi_G_nj6->Fill(data.FatJet[iJetAK8[0]].phi, w);
				h_AK8jet1_tau21_G_nj6->Fill(tau21.at(iJetAK8[0]),w);
				h_AK8jet1_tau32_G_nj6->Fill(tau32.at(iJetAK8[0]),w);
				for (size_t i=0; i<iJetAK8.size(); ++i) {
					h_AK8jets_pt_G_nj6->Fill(data.FatJet[iJetAK8[i]].pt, w);
					h_AK8jets_eta_G_nj6->Fill(data.FatJet[iJetAK8[i]].eta, w);
					h_AK8jets_phi_G_nj6->Fill(data.FatJet[iJetAK8[i]].phi, w);
					h_AK8jets_msoftdrop_G_nj6->Fill(data.FatJet[iJetAK8[i]].msoftdrop, w);
					h_AK8jets_tau21_G_nj6->Fill(tau21.at(iJetAK8[i]),w);
					h_AK8jets_tau32_G_nj6->Fill(tau32.at(iJetAK8[i]),w);
				}
#if TOP == 0
				for (size_t i=0; i<iBoostMassTag.size(); ++i) {
					h_Wjets_pt_G_nj6->Fill(data.FatJet[iBoostMassTag[i]].pt, w);
					h_Wjets_eta_G_nj6->Fill(data.FatJet[iBoostMassTag[i]].eta, w);
					h_Wjets_phi_G_nj6->Fill(data.FatJet[iBoostMassTag[i]].phi, w);
					h_Wjets_tau21_G_nj6->Fill(tau21.at(iBoostMassTag[i]), w);
					h_Wjets_tau32_G_nj6->Fill(tau32.at(iBoostMassTag[i]), w);
				}
#else
				for (size_t i=0; i<iBoostMassTag.size(); ++i) {
					h_Topjets_pt_G_nj6->Fill(data.FatJet[iBoostMassTag[i]].pt, w);
					h_Topjets_eta_G_nj6->Fill(data.FatJet[iBoostMassTag[i]].eta, w);
					h_Topjets_phi_G_nj6->Fill(data.FatJet[iBoostMassTag[i]].phi, w);
					h_Topjets_tau21_G_nj6->Fill(tau21.at(iBoostMassTag[i]), w);
					h_Topjets_tau32_G_nj6->Fill(tau32.at(iBoostMassTag[i]), w);
				}
#endif
			}
		}
		vect = {"0Ele", "0Mu"};
		if (apply_all_cuts_except('G', vect)) {
			h_ht_AK4_no0Lep_G->Fill(AK4_Ht, w);
			h_MR_no0Lep_G->Fill(MR, w);
			h_R2_no0Lep_G->Fill(R2_pho, w);
			h_MET_no0Lep_G->Fill(MET_pho,w);
			h_nLep_no0Lep_G->Fill(nLepVeto,w);
			if(nJet>=4 && nJet<6){
				h_ht_AK4_no0Lep_G_nj45->Fill(AK4_Ht, w);
				h_MR_no0Lep_G_nj45->Fill(MR, w);
				h_R2_no0Lep_G_nj45->Fill(R2_pho, w);
				h_MET_no0Lep_G_nj45->Fill(MET_pho,w);
				h_nLep_no0Lep_G_nj45->Fill(nLepVeto,w);
			}
			if(nJet>=6){
				h_ht_AK4_no0Lep_G_nj6->Fill(AK4_Ht, w);
				h_MR_no0Lep_G_nj6->Fill(MR, w);
				h_R2_no0Lep_G_nj6->Fill(R2_pho, w);
				h_MET_no0Lep_G_nj6->Fill(MET_pho,w);
				h_nLep_no0Lep_G_nj6->Fill(nLepVeto,w);
			}
		}
#if TOP == 0
		if (apply_all_cuts_except('G', "1mW")) {
			h_ht_AK4_nonW_G->Fill(AK4_Ht, w);
			h_MR_nonW_G->Fill(MR, w);
			h_R2_nonW_G->Fill(R2, w);
			h_MET_nonW_G->Fill(data.MET_pt,w);
			h_nW_nonW_G->Fill(nBoostMassTag,w);
			if(nJet>=4 && nJet<6){
				h_ht_AK4_nonW_G_nj45->Fill(AK4_Ht, w);
				h_MR_nonW_G_nj45->Fill(MR, w);
				h_R2_nonW_G_nj45->Fill(R2, w);
				h_MET_nonW_G_nj45->Fill(data.MET_pt,w);
				h_nW_nonW_G_nj45->Fill(nBoostMassTag,w);
			}
			if(nJet>=6){
				h_ht_AK4_nonW_G_nj6->Fill(AK4_Ht, w);
				h_MR_nonW_G_nj6->Fill(MR, w);
				h_R2_nonW_G_nj6->Fill(R2, w);
				h_MET_nonW_G_nj6->Fill(data.MET_pt,w);
				h_nW_nonW_G_nj6->Fill(nBoostMassTag,w);
			}
		}
#else
		if (apply_all_cuts_except('G', "1mTop")) {
			h_ht_AK4_nonTop_G->Fill(AK4_Ht, w);
			h_MR_nonTop_G->Fill(MR, w);
			h_R2_nonTop_G->Fill(R2, w);
			h_MET_nonTop_G->Fill(data.MET_pt,w);
			h_nTop_nonTop_G->Fill(nBoostMassTag,w);
			if(nJet>=4 && nJet<6){
				h_ht_AK4_nonTop_G_nj45->Fill(AK4_Ht, w);
				h_MR_nonTop_G_nj45->Fill(MR, w);
				h_R2_nonTop_G_nj45->Fill(R2, w);
				h_MET_nonTop_G_nj45->Fill(data.MET_pt,w);
				h_nTop_nonTop_G_nj45->Fill(nBoostMassTag,w);
			}
			if(nJet>=6){
				h_ht_AK4_nonTop_G_nj6->Fill(AK4_Ht, w);
				h_MR_nonTop_G_nj6->Fill(MR, w);
				h_R2_nonTop_G_nj6->Fill(R2, w);
				h_MET_nonTop_G_nj6->Fill(data.MET_pt,w);
				h_nTop_nonTop_G_nj6->Fill(nBoostMassTag,w);
			}
		}
#endif
		if (apply_all_cuts_except('G', "1Pho")) {
			h_ht_AK4_no1Pho_G->Fill(AK4_Ht, w);
			h_MR_no1Pho_G->Fill(MR, w);
			h_R2_no1Pho_G->Fill(R2_pho, w);
			h_MET_no1Pho_G->Fill(MET_pho,w);
			h_nPho_no1Pho_G->Fill(nPhotonSelect,w);
			if(nJet>=4 && nJet<6){
				h_ht_AK4_no1Pho_G_nj45->Fill(AK4_Ht, w);
				h_MR_no1Pho_G_nj45->Fill(MR, w);
				h_R2_no1Pho_G_nj45->Fill(R2_pho, w);
				h_MET_no1Pho_G_nj45->Fill(MET_pho,w);
				h_nPho_no1Pho_G_nj45->Fill(nPhotonSelect,w);
			}
			if(nJet>=6){
				h_ht_AK4_no1Pho_G_nj6->Fill(AK4_Ht, w);
				h_MR_no1Pho_G_nj6->Fill(MR, w);
				h_R2_no1Pho_G_nj6->Fill(R2_pho, w);
				h_MET_no1Pho_G_nj6->Fill(MET_pho,w);
				h_nPho_no1Pho_G_nj6->Fill(nPhotonSelect,w);
			}
		}
		if (apply_all_cuts_except('G', "mDPhi")) {
			h_ht_AK4_nomDPhi_G->Fill(AK4_Ht, w);
			h_MR_nomDPhi_G->Fill(MR, w);
			h_R2_nomDPhi_G->Fill(R2_pho, w);
			h_MET_nomDPhi_G->Fill(MET_pho,w);
			h_mDPhi_nomDPhi_G->Fill(dPhiRazor,w);
			if(nJet>=4 && nJet<6){
				h_ht_AK4_nomDPhi_G_nj45->Fill(AK4_Ht, w);
				h_MR_nomDPhi_G_nj45->Fill(MR, w);
				h_R2_nomDPhi_G_nj45->Fill(R2_pho, w);
				h_MET_nomDPhi_G_nj45->Fill(MET_pho,w);
				h_mDPhi_nomDPhi_G_nj45->Fill(dPhiRazor,w);
			}
			if(nJet>=6){
				h_ht_AK4_nomDPhi_G_nj6->Fill(AK4_Ht, w);
				h_MR_nomDPhi_G_nj6->Fill(MR, w);
				h_R2_nomDPhi_G_nj6->Fill(R2_pho, w);
				h_MET_nomDPhi_G_nj6->Fill(MET_pho,w);
				h_mDPhi_nomDPhi_G_nj6->Fill(dPhiRazor,w);
			}
		}

		// QCD enriched region
		w = sf_weight['q'];
		if (apply_all_cuts('q')) {
			h_njet_q    ->Fill(nJet,        w);
			h_nAK8jet_q ->Fill(nJetAK8,     w);
			h_ht_AK4_q->Fill(AK4_Ht, w);
			h_MR_q->Fill(MR, w);
			h_R2_q->Fill(R2, w);
			h_MET_q->Fill(data.MET_pt,w);
			h_R2_MR_q->Fill(MR, R2, w);
			h_R2_MET_q->Fill(data.MET_pt, R2, w);
			h_MR_MET_q->Fill(data.MET_pt, MR, w);
			h_AK8Jet1pT_MET_q->Fill(data.MET_pt, data.FatJet[iJetAK8[0]].pt, w);
			h_MET_phi_q->Fill(data.MET_phi,w);

			for (size_t i=0; i<2; ++i) {
				h_Megajets_pt_q->Fill(hemis_AK4[i].Pt(), w);
				h_Megajets_eta_q->Fill(hemis_AK4[i].Eta(), w);
				h_Megajets_phi_q->Fill(hemis_AK4[i].Phi(), w);
			}

			h_jet1_pt_q->Fill(data.Jet[iJet[0]].pt, w);
			h_jet1_eta_q->Fill(data.Jet[iJet[0]].eta, w);
			h_jet1_phi_q->Fill(data.Jet[iJet[0]].phi, w);
			for (size_t i=0; i<iJet.size(); ++i) {
				h_jets_pt_q->Fill(data.Jet[iJet[i]].pt, w);
				h_jets_eta_q->Fill(data.Jet[iJet[i]].eta, w);
				h_jets_phi_q->Fill(data.Jet[iJet[i]].phi, w);
			}
			h_AK8jet1_pt_q->Fill(data.FatJet[iJetAK8[0]].pt, w);
			h_AK8jet1_eta_q->Fill(data.FatJet[iJetAK8[0]].eta, w);
			h_AK8jet1_phi_q->Fill(data.FatJet[iJetAK8[0]].phi, w);
			h_AK8jet1_tau21_q->Fill(tau21.at(iJetAK8[0]),w);
			h_AK8jet1_tau32_q->Fill(tau32.at(iJetAK8[0]),w);
			for (size_t i=0; i<iJetAK8.size(); ++i) {
				h_AK8jets_pt_q->Fill(data.FatJet[iJetAK8[i]].pt, w);
				h_AK8jets_eta_q->Fill(data.FatJet[iJetAK8[i]].eta, w);
				h_AK8jets_phi_q->Fill(data.FatJet[iJetAK8[i]].phi, w);
				h_AK8jets_msoftdrop_q->Fill(data.FatJet[iJetAK8[i]].msoftdrop, w);
				h_AK8jets_tau21_q->Fill(tau21.at(iJetAK8[i]),w);
				h_AK8jets_tau32_q->Fill(tau32.at(iJetAK8[i]),w);
			}
#if TOP == 0
			for (size_t i=0; i<iBoostMassTag.size(); ++i) {
				h_Wjets_pt_q->Fill(data.FatJet[iBoostMassTag[i]].pt, w);
				h_Wjets_eta_q->Fill(data.FatJet[iBoostMassTag[i]].eta, w);
				h_Wjets_phi_q->Fill(data.FatJet[iBoostMassTag[i]].phi, w);
				h_Wjets_tau21_q->Fill(tau21.at(iBoostMassTag[i]), w);
				h_Wjets_tau32_q->Fill(tau32.at(iBoostMassTag[i]), w);
        h_deepTagMD_WvsQCD_q->Fill(data.FatJet[iBoostMassTag[i]].deepTagMD_WvsQCD, w);
        h_deepTagMD_TvsQCD_q->Fill(data.FatJet[iBoostMassTag[i]].deepTagMD_TvsQCD, w);
        h_deepTag_WvsQCD_q->Fill(data.FatJet[iBoostMassTag[i]].deepTag_WvsQCD, w);
        h_deepTag_TvsQCD_q->Fill(data.FatJet[iBoostMassTag[i]].deepTag_TvsQCD, w);
			}
#else
			for (size_t i=0; i<iBoostMassTag.size(); ++i) {
				h_Topjets_pt_q->Fill(data.FatJet[iBoostMassTag[i]].pt, w);
				h_Topjets_eta_q->Fill(data.FatJet[iBoostMassTag[i]].eta, w);
				h_Topjets_phi_q->Fill(data.FatJet[iBoostMassTag[i]].phi, w);
				h_Topjets_tau21_q->Fill(tau21.at(iBoostMassTag[i]), w);
				h_Topjets_tau32_q->Fill(tau32.at(iBoostMassTag[i]), w);
        h_deepTagMD_WvsQCD_q->Fill(data.FatJet[iBoostMassTag[i]].deepTagMD_WvsQCD, w);
        h_deepTagMD_TvsQCD_q->Fill(data.FatJet[iBoostMassTag[i]].deepTagMD_TvsQCD, w);
        h_deepTag_WvsQCD_q->Fill(data.FatJet[iBoostMassTag[i]].deepTag_WvsQCD, w);
        h_deepTag_TvsQCD_q->Fill(data.FatJet[iBoostMassTag[i]].deepTag_TvsQCD, w);
			}
#endif
			if(nJet>=4 && nJet<6){
				h_ht_AK4_q_nj45->Fill(AK4_Ht, w);
				h_MR_q_nj45->Fill(MR, w);
				h_R2_q_nj45->Fill(R2, w);
				h_MET_q_nj45->Fill(data.MET_pt,w);
				h_R2_MR_q_nj45->Fill(MR, R2, w);
				h_MET_phi_q_nj45->Fill(data.MET_phi,w);

				h_jet1_pt_q_nj45->Fill(data.Jet[iJet[0]].pt, w);
				h_jet1_eta_q_nj45->Fill(data.Jet[iJet[0]].eta, w);
				h_jet1_phi_q_nj45->Fill(data.Jet[iJet[0]].phi, w);
				for (size_t i=0; i<iJet.size(); ++i) {
					h_jets_pt_q_nj45->Fill(data.Jet[iJet[i]].pt, w);
					h_jets_eta_q_nj45->Fill(data.Jet[iJet[i]].eta, w);
					h_jets_phi_q_nj45->Fill(data.Jet[iJet[i]].phi, w);
				}
				h_AK8jet1_pt_q_nj45->Fill(data.FatJet[iJetAK8[0]].pt, w);
				h_AK8jet1_eta_q_nj45->Fill(data.FatJet[iJetAK8[0]].eta, w);
				h_AK8jet1_phi_q_nj45->Fill(data.FatJet[iJetAK8[0]].phi, w);
				h_AK8jet1_tau21_q_nj45->Fill(tau21.at(iJetAK8[0]),w);
				h_AK8jet1_tau32_q_nj45->Fill(tau32.at(iJetAK8[0]),w);
				for (size_t i=0; i<iJetAK8.size(); ++i) {
					h_AK8jets_pt_q_nj45->Fill(data.FatJet[iJetAK8[i]].pt, w);
					h_AK8jets_eta_q_nj45->Fill(data.FatJet[iJetAK8[i]].eta, w);
					h_AK8jets_phi_q_nj45->Fill(data.FatJet[iJetAK8[i]].phi, w);
					h_AK8jets_msoftdrop_q_nj45->Fill(data.FatJet[iJetAK8[i]].msoftdrop, w);
					h_AK8jets_tau21_q_nj45->Fill(tau21.at(iJetAK8[i]),w);
					h_AK8jets_tau32_q_nj45->Fill(tau32.at(iJetAK8[i]),w);
				}
#if TOP == 0
				for (size_t i=0; i<iBoostMassTag.size(); ++i) {
					h_Wjets_pt_q_nj45->Fill(data.FatJet[iBoostMassTag[i]].pt, w);
					h_Wjets_eta_q_nj45->Fill(data.FatJet[iBoostMassTag[i]].eta, w);
					h_Wjets_phi_q_nj45->Fill(data.FatJet[iBoostMassTag[i]].phi, w);
					h_Wjets_tau21_q_nj45->Fill(tau21.at(iBoostMassTag[i]), w);
					h_Wjets_tau32_q_nj45->Fill(tau32.at(iBoostMassTag[i]), w);
				}
#else
				for (size_t i=0; i<iBoostMassTag.size(); ++i) {
					h_Topjets_pt_q_nj45->Fill(data.FatJet[iBoostMassTag[i]].pt, w);
					h_Topjets_eta_q_nj45->Fill(data.FatJet[iBoostMassTag[i]].eta, w);
					h_Topjets_phi_q_nj45->Fill(data.FatJet[iBoostMassTag[i]].phi, w);
					h_Topjets_tau21_q_nj45->Fill(tau21.at(iBoostMassTag[i]), w);
					h_Topjets_tau32_q_nj45->Fill(tau32.at(iBoostMassTag[i]), w);
				}
#endif
			}
			if(nJet>=6){
				h_ht_AK4_q_nj6->Fill(AK4_Ht, w);
				h_MR_q_nj6->Fill(MR, w);
				h_R2_q_nj6->Fill(R2, w);
				h_MET_q_nj6->Fill(data.MET_pt,w);
				h_R2_MR_q_nj6->Fill(MR, R2, w);
				h_MET_phi_q_nj6->Fill(data.MET_phi,w);

				h_jet1_pt_q_nj6->Fill(data.Jet[iJet[0]].pt, w);
				h_jet1_eta_q_nj6->Fill(data.Jet[iJet[0]].eta, w);
				h_jet1_phi_q_nj6->Fill(data.Jet[iJet[0]].phi, w);
				for (size_t i=0; i<iJet.size(); ++i) {
					h_jets_pt_q_nj6->Fill(data.Jet[iJet[i]].pt, w);
					h_jets_eta_q_nj6->Fill(data.Jet[iJet[i]].eta, w);
					h_jets_phi_q_nj6->Fill(data.Jet[iJet[i]].phi, w);
				}
				h_AK8jet1_pt_q_nj6->Fill(data.FatJet[iJetAK8[0]].pt, w);
				h_AK8jet1_eta_q_nj6->Fill(data.FatJet[iJetAK8[0]].eta, w);
				h_AK8jet1_phi_q_nj6->Fill(data.FatJet[iJetAK8[0]].phi, w);
				h_AK8jet1_tau21_q_nj6->Fill(tau21.at(iJetAK8[0]),w);
				h_AK8jet1_tau32_q_nj6->Fill(tau32.at(iJetAK8[0]),w);
				for (size_t i=0; i<iJetAK8.size(); ++i) {
					h_AK8jets_pt_q_nj6->Fill(data.FatJet[iJetAK8[i]].pt, w);
					h_AK8jets_eta_q_nj6->Fill(data.FatJet[iJetAK8[i]].eta, w);
					h_AK8jets_phi_q_nj6->Fill(data.FatJet[iJetAK8[i]].phi, w);
					h_AK8jets_msoftdrop_q_nj6->Fill(data.FatJet[iJetAK8[i]].msoftdrop, w);
					h_AK8jets_tau21_q_nj6->Fill(tau21.at(iJetAK8[i]),w);
					h_AK8jets_tau32_q_nj6->Fill(tau32.at(iJetAK8[i]),w);
				}
#if TOP == 0
				for (size_t i=0; i<iBoostMassTag.size(); ++i) {
					h_Wjets_pt_q_nj6->Fill(data.FatJet[iBoostMassTag[i]].pt, w);
					h_Wjets_eta_q_nj6->Fill(data.FatJet[iBoostMassTag[i]].eta, w);
					h_Wjets_phi_q_nj6->Fill(data.FatJet[iBoostMassTag[i]].phi, w);
					h_Wjets_tau21_q_nj6->Fill(tau21.at(iBoostMassTag[i]), w);
					h_Wjets_tau32_q_nj6->Fill(tau32.at(iBoostMassTag[i]), w);
				}
#else
				for (size_t i=0; i<iBoostMassTag.size(); ++i) {
					h_Topjets_pt_q_nj6->Fill(data.FatJet[iBoostMassTag[i]].pt, w);
					h_Topjets_eta_q_nj6->Fill(data.FatJet[iBoostMassTag[i]].eta, w);
					h_Topjets_phi_q_nj6->Fill(data.FatJet[iBoostMassTag[i]].phi, w);
					h_Topjets_tau21_q_nj6->Fill(tau21.at(iBoostMassTag[i]), w);
					h_Topjets_tau32_q_nj6->Fill(tau32.at(iBoostMassTag[i]), w);
				}
#endif
			}
		}

		// QCD enriched region
		w = sf_weight['Q'];
		if (apply_all_cuts('Q')) {
			h_njet_Q    ->Fill(nJet,        w);
			h_nAK8jet_Q ->Fill(nJetAK8,     w);
			h_ht_AK4_Q->Fill(AK4_Ht, w);
			h_MR_Q->Fill(MR, w);
			h_R2_Q->Fill(R2, w);
			h_MET_Q->Fill(data.MET_pt,w);
			h_R2_MR_Q->Fill(MR, R2, w);
			h_R2_MET_Q->Fill(data.MET_pt, R2, w);
			h_MR_MET_Q->Fill(data.MET_pt, MR, w);
			h_AK8Jet1pT_MET_Q->Fill(data.MET_pt, data.FatJet[iJetAK8[0]].pt, w);
			h_MET_phi_Q->Fill(data.MET_phi,w);

			for (size_t i=0; i<2; ++i) {
				h_Megajets_pt_Q->Fill(hemis_AK4[i].Pt(), w);
				h_Megajets_eta_Q->Fill(hemis_AK4[i].Eta(), w);
				h_Megajets_phi_Q->Fill(hemis_AK4[i].Phi(), w);
			}

			h_jet1_pt_Q->Fill(data.Jet[iJet[0]].pt, w);
			h_jet1_eta_Q->Fill(data.Jet[iJet[0]].eta, w);
			h_jet1_phi_Q->Fill(data.Jet[iJet[0]].phi, w);
			for (size_t i=0; i<iJet.size(); ++i) {
				h_jets_pt_Q->Fill(data.Jet[iJet[i]].pt, w);
				h_jets_eta_Q->Fill(data.Jet[iJet[i]].eta, w);
				h_jets_phi_Q->Fill(data.Jet[iJet[i]].phi, w);
			}
			h_AK8jet1_pt_Q->Fill(data.FatJet[iJetAK8[0]].pt, w);
			h_AK8jet1_eta_Q->Fill(data.FatJet[iJetAK8[0]].eta, w);
			h_AK8jet1_phi_Q->Fill(data.FatJet[iJetAK8[0]].phi, w);
			h_AK8jet1_tau21_Q->Fill(tau21.at(iJetAK8[0]),w);
			h_AK8jet1_tau32_Q->Fill(tau32.at(iJetAK8[0]),w);
			for (size_t i=0; i<iJetAK8.size(); ++i) {
				h_AK8jets_pt_Q->Fill(data.FatJet[iJetAK8[i]].pt, w);
				h_AK8jets_eta_Q->Fill(data.FatJet[iJetAK8[i]].eta, w);
				h_AK8jets_phi_Q->Fill(data.FatJet[iJetAK8[i]].phi, w);
				h_AK8jets_msoftdrop_Q->Fill(data.FatJet[iJetAK8[i]].msoftdrop, w);
				h_AK8jets_tau21_Q->Fill(tau21.at(iJetAK8[i]),w);
				h_AK8jets_tau32_Q->Fill(tau32.at(iJetAK8[i]),w);
			}
#if TOP == 0
			for (size_t i=0; i<iBoostMassTag.size(); ++i) {
				h_Wjets_pt_Q->Fill(data.FatJet[iBoostMassTag[i]].pt, w);
				h_Wjets_eta_Q->Fill(data.FatJet[iBoostMassTag[i]].eta, w);
				h_Wjets_phi_Q->Fill(data.FatJet[iBoostMassTag[i]].phi, w);
				h_Wjets_tau21_Q->Fill(tau21.at(iBoostMassTag[i]), w);
				h_Wjets_tau32_Q->Fill(tau32.at(iBoostMassTag[i]), w);
        h_deepTagMD_WvsQCD_Q->Fill(data.FatJet[iBoostMassTag[i]].deepTagMD_WvsQCD, w);
        h_deepTagMD_TvsQCD_Q->Fill(data.FatJet[iBoostMassTag[i]].deepTagMD_TvsQCD, w);
        h_deepTag_WvsQCD_Q->Fill(data.FatJet[iBoostMassTag[i]].deepTag_WvsQCD, w);
        h_deepTag_TvsQCD_Q->Fill(data.FatJet[iBoostMassTag[i]].deepTag_TvsQCD, w);
			}
#else
			for (size_t i=0; i<iBoostMassTag.size(); ++i) {
				h_Topjets_pt_Q->Fill(data.FatJet[iBoostMassTag[i]].pt, w);
				h_Topjets_eta_Q->Fill(data.FatJet[iBoostMassTag[i]].eta, w);
				h_Topjets_phi_Q->Fill(data.FatJet[iBoostMassTag[i]].phi, w);
				h_Topjets_tau21_Q->Fill(tau21.at(iBoostMassTag[i]), w);
				h_Topjets_tau32_Q->Fill(tau32.at(iBoostMassTag[i]), w);
        h_deepTagMD_WvsQCD_Q->Fill(data.FatJet[iBoostMassTag[i]].deepTagMD_WvsQCD, w);
        h_deepTagMD_TvsQCD_Q->Fill(data.FatJet[iBoostMassTag[i]].deepTagMD_TvsQCD, w);
        h_deepTag_WvsQCD_Q->Fill(data.FatJet[iBoostMassTag[i]].deepTag_WvsQCD, w);
        h_deepTag_TvsQCD_Q->Fill(data.FatJet[iBoostMassTag[i]].deepTag_TvsQCD, w);
			}
#endif

			if(nJet>=4 && nJet<6){
				h_ht_AK4_Q_nj45->Fill(AK4_Ht, w);
				h_MR_Q_nj45->Fill(MR, w);
				h_R2_Q_nj45->Fill(R2, w);
				h_MET_Q_nj45->Fill(data.MET_pt,w);
				h_R2_MR_Q_nj45->Fill(MR, R2, w);
				h_MET_phi_Q_nj45->Fill(data.MET_phi,w);

				h_jet1_pt_Q_nj45->Fill(data.Jet[iJet[0]].pt, w);
				h_jet1_eta_Q_nj45->Fill(data.Jet[iJet[0]].eta, w);
				h_jet1_phi_Q_nj45->Fill(data.Jet[iJet[0]].phi, w);
				for (size_t i=0; i<iJet.size(); ++i) {
					h_jets_pt_Q_nj45->Fill(data.Jet[iJet[i]].pt, w);
					h_jets_eta_Q_nj45->Fill(data.Jet[iJet[i]].eta, w);
					h_jets_phi_Q_nj45->Fill(data.Jet[iJet[i]].phi, w);
				}
				h_AK8jet1_pt_Q_nj45->Fill(data.FatJet[iJetAK8[0]].pt, w);
				h_AK8jet1_eta_Q_nj45->Fill(data.FatJet[iJetAK8[0]].eta, w);
				h_AK8jet1_phi_Q_nj45->Fill(data.FatJet[iJetAK8[0]].phi, w);
				h_AK8jet1_tau21_Q_nj45->Fill(tau21.at(iJetAK8[0]),w);
				h_AK8jet1_tau32_Q_nj45->Fill(tau32.at(iJetAK8[0]),w);
				for (size_t i=0; i<iJetAK8.size(); ++i) {
					h_AK8jets_pt_Q_nj45->Fill(data.FatJet[iJetAK8[i]].pt, w);
					h_AK8jets_eta_Q_nj45->Fill(data.FatJet[iJetAK8[i]].eta, w);
					h_AK8jets_phi_Q_nj45->Fill(data.FatJet[iJetAK8[i]].phi, w);
					h_AK8jets_msoftdrop_Q_nj45->Fill(data.FatJet[iJetAK8[i]].msoftdrop, w);
					h_AK8jets_tau21_Q_nj45->Fill(tau21.at(iJetAK8[i]),w);
					h_AK8jets_tau32_Q_nj45->Fill(tau32.at(iJetAK8[i]),w);
				}
#if TOP == 0
				for (size_t i=0; i<iBoostMassTag.size(); ++i) {
					h_Wjets_pt_Q_nj45->Fill(data.FatJet[iBoostMassTag[i]].pt, w);
					h_Wjets_eta_Q_nj45->Fill(data.FatJet[iBoostMassTag[i]].eta, w);
					h_Wjets_phi_Q_nj45->Fill(data.FatJet[iBoostMassTag[i]].phi, w);
					h_Wjets_tau21_Q_nj45->Fill(tau21.at(iBoostMassTag[i]), w);
					h_Wjets_tau32_Q_nj45->Fill(tau32.at(iBoostMassTag[i]), w);
				}
#else
				for (size_t i=0; i<iBoostMassTag.size(); ++i) {
					h_Topjets_pt_Q_nj45->Fill(data.FatJet[iBoostMassTag[i]].pt, w);
					h_Topjets_eta_Q_nj45->Fill(data.FatJet[iBoostMassTag[i]].eta, w);
					h_Topjets_phi_Q_nj45->Fill(data.FatJet[iBoostMassTag[i]].phi, w);
					h_Topjets_tau21_Q_nj45->Fill(tau21.at(iBoostMassTag[i]), w);
					h_Topjets_tau32_Q_nj45->Fill(tau32.at(iBoostMassTag[i]), w);
				}
#endif
			}
			if(nJet>=6){
				h_ht_AK4_Q_nj6->Fill(AK4_Ht, w);
				h_MR_Q_nj6->Fill(MR, w);
				h_R2_Q_nj6->Fill(R2, w);
				h_MET_Q_nj6->Fill(data.MET_pt,w);
				h_R2_MR_Q_nj6->Fill(MR, R2, w);
				h_MET_phi_Q_nj6->Fill(data.MET_phi,w);

				h_jet1_pt_Q_nj6->Fill(data.Jet[iJet[0]].pt, w);
				h_jet1_eta_Q_nj6->Fill(data.Jet[iJet[0]].eta, w);
				h_jet1_phi_Q_nj6->Fill(data.Jet[iJet[0]].phi, w);
				for (size_t i=0; i<iJet.size(); ++i) {
					h_jets_pt_Q_nj6->Fill(data.Jet[iJet[i]].pt, w);
					h_jets_eta_Q_nj6->Fill(data.Jet[iJet[i]].eta, w);
					h_jets_phi_Q_nj6->Fill(data.Jet[iJet[i]].phi, w);
				}
				h_AK8jet1_pt_Q_nj6->Fill(data.FatJet[iJetAK8[0]].pt, w);
				h_AK8jet1_eta_Q_nj6->Fill(data.FatJet[iJetAK8[0]].eta, w);
				h_AK8jet1_phi_Q_nj6->Fill(data.FatJet[iJetAK8[0]].phi, w);
				h_AK8jet1_tau21_Q_nj6->Fill(tau21.at(iJetAK8[0]),w);
				h_AK8jet1_tau32_Q_nj6->Fill(tau32.at(iJetAK8[0]),w);
				for (size_t i=0; i<iJetAK8.size(); ++i) {
					h_AK8jets_pt_Q_nj6->Fill(data.FatJet[iJetAK8[i]].pt, w);
					h_AK8jets_eta_Q_nj6->Fill(data.FatJet[iJetAK8[i]].eta, w);
					h_AK8jets_phi_Q_nj6->Fill(data.FatJet[iJetAK8[i]].phi, w);
					h_AK8jets_msoftdrop_Q_nj6->Fill(data.FatJet[iJetAK8[i]].msoftdrop, w);
					h_AK8jets_tau21_Q_nj6->Fill(tau21.at(iJetAK8[i]),w);
					h_AK8jets_tau32_Q_nj6->Fill(tau32.at(iJetAK8[i]),w);
				}
#if TOP == 0
				for (size_t i=0; i<iBoostMassTag.size(); ++i) {
					h_Wjets_pt_Q_nj6->Fill(data.FatJet[iBoostMassTag[i]].pt, w);
					h_Wjets_eta_Q_nj6->Fill(data.FatJet[iBoostMassTag[i]].eta, w);
					h_Wjets_phi_Q_nj6->Fill(data.FatJet[iBoostMassTag[i]].phi, w);
					h_Wjets_tau21_Q_nj6->Fill(tau21.at(iBoostMassTag[i]), w);
					h_Wjets_tau32_Q_nj6->Fill(tau32.at(iBoostMassTag[i]), w);
				}
#else
				for (size_t i=0; i<iBoostMassTag.size(); ++i) {
					h_Topjets_pt_Q_nj6->Fill(data.FatJet[iBoostMassTag[i]].pt, w);
					h_Topjets_eta_Q_nj6->Fill(data.FatJet[iBoostMassTag[i]].eta, w);
					h_Topjets_phi_Q_nj6->Fill(data.FatJet[iBoostMassTag[i]].phi, w);
					h_Topjets_tau21_Q_nj6->Fill(tau21.at(iBoostMassTag[i]), w);
					h_Topjets_tau32_Q_nj6->Fill(tau32.at(iBoostMassTag[i]), w);
				}
#endif
			}
		}
		if (apply_all_cuts_except('Q', "InvmDPhi")) {
			h_ht_AK4_nomDPhi_Q->Fill(AK4_Ht, w);
			h_MR_nomDPhi_Q->Fill(MR, w);
			h_R2_nomDPhi_Q->Fill(R2, w);
			h_MET_nomDPhi_Q->Fill(data.MET_pt,w);
			h_mDPhi_nomDPhi_Q->Fill(dPhiRazor,w);
			if(nJet>=4 && nJet<6){
				h_ht_AK4_nomDPhi_Q_nj45->Fill(AK4_Ht, w);
				h_MR_nomDPhi_Q_nj45->Fill(MR, w);
				h_R2_nomDPhi_Q_nj45->Fill(R2, w);
				h_MET_nomDPhi_Q_nj45->Fill(data.MET_pt,w);
				h_mDPhi_nomDPhi_Q_nj45->Fill(dPhiRazor,w);
			}
			if(nJet>=6){
				h_ht_AK4_nomDPhi_Q_nj6->Fill(AK4_Ht, w);
				h_MR_nomDPhi_Q_nj6->Fill(MR, w);
				h_R2_nomDPhi_Q_nj6->Fill(R2, w);
				h_MET_nomDPhi_Q_nj6->Fill(data.MET_pt,w);
				h_mDPhi_nomDPhi_Q_nj6->Fill(dPhiRazor,w);
			}
		}
#if TOP == 0
		if (apply_all_cuts_except('Q', "1aW")) {
			h_ht_AK4_nonW_Q->Fill(AK4_Ht, w);
			h_MR_nonW_Q->Fill(MR, w);
			h_R2_nonW_Q->Fill(R2, w);
			h_MET_nonW_Q->Fill(data.MET_pt,w);
			h_nW_nonW_Q->Fill(nBoostMassTag,w);
			if(nJet>=4 && nJet<6){
				h_ht_AK4_nonW_Q_nj45->Fill(AK4_Ht, w);
				h_MR_nonW_Q_nj45->Fill(MR, w);
				h_R2_nonW_Q_nj45->Fill(R2, w);
				h_MET_nonW_Q_nj45->Fill(data.MET_pt,w);
				h_nW_nonW_Q_nj45->Fill(nBoostMassTag,w);
			}
			if(nJet>=6){
				h_ht_AK4_nonW_Q_nj6->Fill(AK4_Ht, w);
				h_MR_nonW_Q_nj6->Fill(MR, w);
				h_R2_nonW_Q_nj6->Fill(R2, w);
				h_MET_nonW_Q_nj6->Fill(data.MET_pt,w);
				h_nW_nonW_Q_nj6->Fill(nBoostMassTag,w);
			}
		}
#else
		if (apply_all_cuts_except('Q', "1aTop")) {
			h_ht_AK4_nonTop_Q->Fill(AK4_Ht, w);
			h_MR_nonTop_Q->Fill(MR, w);
			h_R2_nonTop_Q->Fill(R2, w);
			h_MET_nonTop_Q->Fill(data.MET_pt,w);
			h_nTop_nonTop_Q->Fill(nBoostMassTag,w);
			if(nJet>=4 && nJet<6){
				h_ht_AK4_nonTop_Q_nj45->Fill(AK4_Ht, w);
				h_MR_nonTop_Q_nj45->Fill(MR, w);
				h_R2_nonTop_Q_nj45->Fill(R2, w);
				h_MET_nonTop_Q_nj45->Fill(data.MET_pt,w);
				h_nTop_nonTop_Q_nj45->Fill(nBoostMassTag,w);
			}
			if(nJet>=6){
				h_ht_AK4_nonTop_Q_nj6->Fill(AK4_Ht, w);
				h_MR_nonTop_Q_nj6->Fill(MR, w);
				h_R2_nonTop_Q_nj6->Fill(R2, w);
				h_MET_nonTop_Q_nj6->Fill(data.MET_pt,w);
				h_nTop_nonTop_Q_nj6->Fill(nBoostMassTag,w);
			}
		}
#endif
		if (apply_all_cuts_except('Q', "0b")) {
			h_ht_AK4_nonb_Q->Fill(AK4_Ht, w);
			h_MR_nonb_Q->Fill(MR, w);
			h_R2_nonb_Q->Fill(R2, w);
			h_MET_nonb_Q->Fill(data.MET_pt,w);
			h_nb_nonb_Q->Fill(nLooseBTag,w);
			if(nJet>=4 && nJet<6){
				h_ht_AK4_nonb_Q_nj45->Fill(AK4_Ht, w);
				h_MR_nonb_Q_nj45->Fill(MR, w);
				h_R2_nonb_Q_nj45->Fill(R2, w);
				h_MET_nonb_Q_nj45->Fill(data.MET_pt,w);
				h_nb_nonb_Q_nj45->Fill(nLooseBTag,w);
			}
			if(nJet>=6){
				h_ht_AK4_nonb_Q_nj6->Fill(AK4_Ht, w);
				h_MR_nonb_Q_nj6->Fill(MR, w);
				h_R2_nonb_Q_nj6->Fill(R2, w);
				h_MET_nonb_Q_nj6->Fill(data.MET_pt,w);
				h_nb_nonb_Q_nj6->Fill(nLooseBTag,w);
			}
		}
		vect = {"0Ele", "0Mu"};
		if (apply_all_cuts_except('Q', vect)) {
			h_ht_AK4_no0Lep_Q->Fill(AK4_Ht, w);
			h_MR_no0Lep_Q->Fill(MR, w);
			h_R2_no0Lep_Q->Fill(R2, w);
			h_MET_no0Lep_Q->Fill(data.MET_pt,w);
			h_nLep_no0Lep_Q->Fill(nLepVeto,w);
			if(nJet>=4 && nJet<6){
				h_ht_AK4_no0Lep_Q_nj45->Fill(AK4_Ht, w);
				h_MR_no0Lep_Q_nj45->Fill(MR, w);
				h_R2_no0Lep_Q_nj45->Fill(R2, w);
				h_MET_no0Lep_Q_nj45->Fill(data.MET_pt,w);
				h_nLep_no0Lep_Q_nj45->Fill(nLepVeto,w);
			}
			if(nJet>=6){
				h_ht_AK4_no0Lep_Q_nj6->Fill(AK4_Ht, w);
				h_MR_no0Lep_Q_nj6->Fill(MR, w);
				h_R2_no0Lep_Q_nj6->Fill(R2, w);
				h_MET_no0Lep_Q_nj6->Fill(data.MET_pt,w);
				h_nLep_no0Lep_Q_nj6->Fill(nLepVeto,w);
			}
		}


		// Signal' region
		w = sf_weight['s'];
		//if (apply_all_cuts_except('s', "HLT")) {
		if (apply_all_cuts('s')) {
			h_njet_s    ->Fill(nJet,        w);
			h_nAK8jet_s ->Fill(nJetAK8,     w);
			h_ht_AK4_s->Fill(AK4_Ht, w);
			h_MR_s->Fill(MR, w);
			h_R2_s->Fill(R2, w);
			h_MET_s->Fill(data.MET_pt,w);
			h_R2_MR_s->Fill(MR, R2, w);
			h_R2_MET_s->Fill(data.MET_pt, R2, w);
			h_MR_MET_s->Fill(data.MET_pt, MR, w);
			h_AK8Jet1pT_MET_s->Fill(data.MET_pt, data.FatJet[iJetAK8[0]].pt, w);
			h_MET_phi_s->Fill(data.MET_phi,w);

			for (size_t i=0; i<2; ++i) {
				h_Megajets_pt_s->Fill(hemis_AK4[i].Pt(), w);
				h_Megajets_eta_s->Fill(hemis_AK4[i].Eta(), w);
				h_Megajets_phi_s->Fill(hemis_AK4[i].Phi(), w);
			}

			h_jet1_pt_s->Fill(data.Jet[iJet[0]].pt, w);
			h_jet1_eta_s->Fill(data.Jet[iJet[0]].eta, w);
			h_jet1_phi_s->Fill(data.Jet[iJet[0]].phi, w);
			for (size_t i=0; i<iJet.size(); ++i) {
				h_jets_pt_s->Fill(data.Jet[iJet[i]].pt, w);
				h_jets_eta_s->Fill(data.Jet[iJet[i]].eta, w);
				h_jets_phi_s->Fill(data.Jet[iJet[i]].phi, w);
			}
			h_AK8jet1_pt_s->Fill(data.FatJet[iJetAK8[0]].pt, w);
			h_AK8jet1_eta_s->Fill(data.FatJet[iJetAK8[0]].eta, w);
			h_AK8jet1_phi_s->Fill(data.FatJet[iJetAK8[0]].phi, w);
			h_AK8jet1_tau21_s->Fill(tau21.at(iJetAK8[0]),w);
			h_AK8jet1_tau32_s->Fill(tau32.at(iJetAK8[0]),w);
			for (size_t i=0; i<iJetAK8.size(); ++i) {
				h_AK8jets_pt_s->Fill(data.FatJet[iJetAK8[i]].pt, w);
				h_AK8jets_eta_s->Fill(data.FatJet[iJetAK8[i]].eta, w);
				h_AK8jets_phi_s->Fill(data.FatJet[iJetAK8[i]].phi, w);
				h_AK8jets_msoftdrop_s->Fill(data.FatJet[iJetAK8[i]].msoftdrop, w);
				h_AK8jets_tau21_s->Fill(tau21.at(iJetAK8[i]),w);
				h_AK8jets_tau32_s->Fill(tau32.at(iJetAK8[i]),w);
			}
#if TOP == 0
			for (size_t i=0; i<iBoostMassTag.size(); ++i) {
				h_Wjets_pt_s->Fill(data.FatJet[iBoostMassTag[i]].pt, w);
				h_Wjets_eta_s->Fill(data.FatJet[iBoostMassTag[i]].eta, w);
				h_Wjets_phi_s->Fill(data.FatJet[iBoostMassTag[i]].phi, w);
				h_Wjets_tau21_s->Fill(tau21.at(iBoostMassTag[i]), w);
				h_Wjets_tau32_s->Fill(tau32.at(iBoostMassTag[i]), w);
        h_deepTagMD_WvsQCD_s->Fill(data.FatJet[iBoostMassTag[i]].deepTagMD_WvsQCD, w);
        h_deepTagMD_TvsQCD_s->Fill(data.FatJet[iBoostMassTag[i]].deepTagMD_TvsQCD, w);
        h_deepTag_WvsQCD_s->Fill(data.FatJet[iBoostMassTag[i]].deepTag_WvsQCD, w);
        h_deepTag_TvsQCD_s->Fill(data.FatJet[iBoostMassTag[i]].deepTag_TvsQCD, w);
			}
#else
			for (size_t i=0; i<iBoostMassTag.size(); ++i) {
				h_Topjets_pt_s->Fill(data.FatJet[iBoostMassTag[i]].pt, w);
				h_Topjets_eta_s->Fill(data.FatJet[iBoostMassTag[i]].eta, w);
				h_Topjets_phi_s->Fill(data.FatJet[iBoostMassTag[i]].phi, w);
				h_Topjets_tau21_s->Fill(tau21.at(iBoostMassTag[i]), w);
				h_Topjets_tau32_s->Fill(tau32.at(iBoostMassTag[i]), w);
        h_deepTagMD_WvsQCD_s->Fill(data.FatJet[iBoostMassTag[i]].deepTagMD_WvsQCD, w);
        h_deepTagMD_TvsQCD_s->Fill(data.FatJet[iBoostMassTag[i]].deepTagMD_TvsQCD, w);
        h_deepTag_WvsQCD_s->Fill(data.FatJet[iBoostMassTag[i]].deepTag_WvsQCD, w);
        h_deepTag_TvsQCD_s->Fill(data.FatJet[iBoostMassTag[i]].deepTag_TvsQCD, w);
			}
#endif
			if(nJet>=4 && nJet<6){
				h_ht_AK4_s_nj45->Fill(AK4_Ht, w);
				h_MR_s_nj45->Fill(MR, w);
				h_R2_s_nj45->Fill(R2, w);
				h_MET_s_nj45->Fill(data.MET_pt,w);
				h_R2_MR_s_nj45->Fill(MR, R2, w);
				h_MET_phi_s_nj45->Fill(data.MET_phi,w);

				h_jet1_pt_s_nj45->Fill(data.Jet[iJet[0]].pt, w);
				h_jet1_eta_s_nj45->Fill(data.Jet[iJet[0]].eta, w);
				h_jet1_phi_s_nj45->Fill(data.Jet[iJet[0]].phi, w);
				for (size_t i=0; i<iJet.size(); ++i) {
					h_jets_pt_s_nj45->Fill(data.Jet[iJet[i]].pt, w);
					h_jets_eta_s_nj45->Fill(data.Jet[iJet[i]].eta, w);
					h_jets_phi_s_nj45->Fill(data.Jet[iJet[i]].phi, w);
				}
				h_AK8jet1_pt_s_nj45->Fill(data.FatJet[iJetAK8[0]].pt, w);
				h_AK8jet1_eta_s_nj45->Fill(data.FatJet[iJetAK8[0]].eta, w);
				h_AK8jet1_phi_s_nj45->Fill(data.FatJet[iJetAK8[0]].phi, w);
				h_AK8jet1_tau21_s_nj45->Fill(tau21.at(iJetAK8[0]),w);
				h_AK8jet1_tau32_s_nj45->Fill(tau32.at(iJetAK8[0]),w);
				for (size_t i=0; i<iJetAK8.size(); ++i) {
					h_AK8jets_pt_s_nj45->Fill(data.FatJet[iJetAK8[i]].pt, w);
					h_AK8jets_eta_s_nj45->Fill(data.FatJet[iJetAK8[i]].eta, w);
					h_AK8jets_phi_s_nj45->Fill(data.FatJet[iJetAK8[i]].phi, w);
					h_AK8jets_msoftdrop_s_nj45->Fill(data.FatJet[iJetAK8[i]].msoftdrop, w);
					h_AK8jets_tau21_s_nj45->Fill(tau21.at(iJetAK8[i]),w);
					h_AK8jets_tau32_s_nj45->Fill(tau32.at(iJetAK8[i]),w);
				}
#if TOP == 0
				for (size_t i=0; i<iBoostMassTag.size(); ++i) {
					h_Wjets_pt_s_nj45->Fill(data.FatJet[iBoostMassTag[i]].pt, w);
					h_Wjets_eta_s_nj45->Fill(data.FatJet[iBoostMassTag[i]].eta, w);
					h_Wjets_phi_s_nj45->Fill(data.FatJet[iBoostMassTag[i]].phi, w);
					h_Wjets_tau21_s_nj45->Fill(tau21.at(iBoostMassTag[i]), w);
					h_Wjets_tau32_s_nj45->Fill(tau32.at(iBoostMassTag[i]), w);
				}
#else
				for (size_t i=0; i<iBoostMassTag.size(); ++i) {
					h_Topjets_pt_s_nj45->Fill(data.FatJet[iBoostMassTag[i]].pt, w);
					h_Topjets_eta_s_nj45->Fill(data.FatJet[iBoostMassTag[i]].eta, w);
					h_Topjets_phi_s_nj45->Fill(data.FatJet[iBoostMassTag[i]].phi, w);
					h_Topjets_tau21_s_nj45->Fill(tau21.at(iBoostMassTag[i]), w);
					h_Topjets_tau32_s_nj45->Fill(tau32.at(iBoostMassTag[i]), w);
				}
#endif
			}
			if(nJet>=6){
				h_ht_AK4_s_nj6->Fill(AK4_Ht, w);
				h_MR_s_nj6->Fill(MR, w);
				h_R2_s_nj6->Fill(R2, w);
				h_MET_s_nj6->Fill(data.MET_pt,w);
				h_R2_MR_s_nj6->Fill(MR, R2, w);
				h_MET_phi_s_nj6->Fill(data.MET_phi,w);

				h_jet1_pt_s_nj6->Fill(data.Jet[iJet[0]].pt, w);
				h_jet1_eta_s_nj6->Fill(data.Jet[iJet[0]].eta, w);
				h_jet1_phi_s_nj6->Fill(data.Jet[iJet[0]].phi, w);
				for (size_t i=0; i<iJet.size(); ++i) {
					h_jets_pt_s_nj6->Fill(data.Jet[iJet[i]].pt, w);
					h_jets_eta_s_nj6->Fill(data.Jet[iJet[i]].eta, w);
					h_jets_phi_s_nj6->Fill(data.Jet[iJet[i]].phi, w);
				}
				h_AK8jet1_pt_s_nj6->Fill(data.FatJet[iJetAK8[0]].pt, w);
				h_AK8jet1_eta_s_nj6->Fill(data.FatJet[iJetAK8[0]].eta, w);
				h_AK8jet1_phi_s_nj6->Fill(data.FatJet[iJetAK8[0]].phi, w);
				h_AK8jet1_tau21_s_nj6->Fill(tau21.at(iJetAK8[0]),w);
				h_AK8jet1_tau32_s_nj6->Fill(tau32.at(iJetAK8[0]),w);
				for (size_t i=0; i<iJetAK8.size(); ++i) {
					h_AK8jets_pt_s_nj6->Fill(data.FatJet[iJetAK8[i]].pt, w);
					h_AK8jets_eta_s_nj6->Fill(data.FatJet[iJetAK8[i]].eta, w);
					h_AK8jets_phi_s_nj6->Fill(data.FatJet[iJetAK8[i]].phi, w);
					h_AK8jets_msoftdrop_s_nj6->Fill(data.FatJet[iJetAK8[i]].msoftdrop, w);
					h_AK8jets_tau21_s_nj6->Fill(tau21.at(iJetAK8[i]),w);
					h_AK8jets_tau32_s_nj6->Fill(tau32.at(iJetAK8[i]),w);
				}
#if TOP == 0
				for (size_t i=0; i<iBoostMassTag.size(); ++i) {
					h_Wjets_pt_s_nj6->Fill(data.FatJet[iBoostMassTag[i]].pt, w);
					h_Wjets_eta_s_nj6->Fill(data.FatJet[iBoostMassTag[i]].eta, w);
					h_Wjets_phi_s_nj6->Fill(data.FatJet[iBoostMassTag[i]].phi, w);
					h_Wjets_tau21_s_nj6->Fill(tau21.at(iBoostMassTag[i]), w);
					h_Wjets_tau32_s_nj6->Fill(tau32.at(iBoostMassTag[i]), w);
				}
#else
				for (size_t i=0; i<iBoostMassTag.size(); ++i) {
					h_Topjets_pt_s_nj6->Fill(data.FatJet[iBoostMassTag[i]].pt, w);
					h_Topjets_eta_s_nj6->Fill(data.FatJet[iBoostMassTag[i]].eta, w);
					h_Topjets_phi_s_nj6->Fill(data.FatJet[iBoostMassTag[i]].phi, w);
					h_Topjets_tau21_s_nj6->Fill(tau21.at(iBoostMassTag[i]), w);
					h_Topjets_tau32_s_nj6->Fill(tau32.at(iBoostMassTag[i]), w);
				}
#endif
			}
		}
#if TOP == 0
		if (apply_all_cuts_except('s', "1W")) {
			h_nW_nonW_s->Fill(nBoostMassTag,w);
			if(nJet>=4 && nJet<6) h_nW_nonW_s_nj45->Fill(nBoostMassTag,w);
			if(nJet>=6) h_nW_nonW_s_nj6->Fill(nBoostMassTag,w);
		}
		if (apply_all_cuts_except('s', "1b")) {
			h_nb_nonb_s->Fill(nMediumBTag,w);
			if(nJet>=4 && nJet<6) h_nb_nonb_s_nj45->Fill(nMediumBTag,w);
			if(nJet>=6) h_nb_nonb_s_nj6->Fill(nMediumBTag,w);
		}
#else
		if (apply_all_cuts_except('s', "1Top")) {
			h_nTop_nonTop_s->Fill(nBoostMassTag,w);
			if(nJet>=4 && nJet<6) h_nTop_nonTop_s_nj45->Fill(nBoostMassTag,w);
			if(nJet>=6) h_nTop_nonTop_s_nj6->Fill(nBoostMassTag,w);
		}
#endif
		if (apply_all_cuts_except('s', "InvmDPhi")) {
			h_mDPhi_nomDPhi_s->Fill(dPhiRazor,w);
			if(nJet>=4 && nJet<6) h_mDPhi_nomDPhi_s_nj45->Fill(dPhiRazor,w);
			if(nJet>=6) h_mDPhi_nomDPhi_s_nj6->Fill(dPhiRazor,w);
		}
#if TOP == 0
		if (apply_all_cuts_except('q', "1aW")) {
			h_nW_nonW_q->Fill(nBoostMassTag,w);
			if(nJet>=4 && nJet<6) h_nW_nonW_q_nj45->Fill(nBoostMassTag,w);
			if(nJet>=6) h_nW_nonW_q_nj6->Fill(nBoostMassTag,w);
		}
#else
		if (apply_all_cuts_except('q', "1aTop")) {
			h_nTop_nonTop_q->Fill(nBoostMassTag,w);
			if(nJet>=4 && nJet<6) h_nTop_nonTop_q_nj45->Fill(nBoostMassTag,w);
			if(nJet>=6) h_nTop_nonTop_q_nj6->Fill(nBoostMassTag,w);
		}
#endif
		if (apply_all_cuts_except('q', "0b")) {
			h_nb_nonb_q->Fill(nMediumBTag,w);
			if(nJet>=4 && nJet<6) h_nb_nonb_q_nj45->Fill(nMediumBTag,w);
			if(nJet>=6) h_nb_nonb_q_nj6->Fill(nMediumBTag,w);
		}

		// New Signal enriched region -w/o W, Top tag
		w = sf_weight['N'];
		if (apply_all_cuts('N')) {
			h_njet_newq    ->Fill(nJet,        w);
			h_nAK8jet_newq ->Fill(nJetAK8,     w);
			h_ht_AK4_newq->Fill(AK4_Ht, w);
			h_MR_newq->Fill(MR, w);
			h_R2_newq->Fill(R2, w);
			h_MET_newq->Fill(data.MET_pt,w);
			h_R2_MR_newq->Fill(MR, R2, w);
			h_R2_MET_newq->Fill(data.MET_pt, R2, w);
			h_MR_MET_newq->Fill(data.MET_pt, MR, w);
			h_AK8Jet1pT_MET_newq->Fill(data.MET_pt, data.FatJet[iJetAK8[0]].pt, w);
			h_MET_phi_newq->Fill(data.MET_phi,w);
			h_nWjet_newq -> Fill(nBoostMassTag,w);
			h_nTopjet_newq -> Fill(nBoostMassTag,w);

			for (size_t i=0; i<2; ++i) {
				h_Megajets_pt_newq->Fill(hemis_AK4[i].Pt(), w);
				h_Megajets_eta_newq->Fill(hemis_AK4[i].Eta(), w);
				h_Megajets_phi_newq->Fill(hemis_AK4[i].Phi(), w);
			}

			h_jet1_pt_newq->Fill(data.Jet[iJet[0]].pt, w);
			h_jet1_eta_newq->Fill(data.Jet[iJet[0]].eta, w);
			h_jet1_phi_newq->Fill(data.Jet[iJet[0]].phi, w);
			for (size_t i=0; i<iJet.size(); ++i) {
				h_jets_pt_newq->Fill(data.Jet[iJet[i]].pt, w);
				h_jets_eta_newq->Fill(data.Jet[iJet[i]].eta, w);
				h_jets_phi_newq->Fill(data.Jet[iJet[i]].phi, w);
			}
			h_AK8jet1_pt_newq->Fill(data.FatJet[iJetAK8[0]].pt, w);
			h_AK8jet1_eta_newq->Fill(data.FatJet[iJetAK8[0]].eta, w);
			h_AK8jet1_phi_newq->Fill(data.FatJet[iJetAK8[0]].phi, w);
			h_AK8jet1_tau21_newq->Fill(tau21.at(iJetAK8[0]),w);
			h_AK8jet1_tau32_newq->Fill(tau32.at(iJetAK8[0]),w);
			for (size_t i=0; i<iJetAK8.size(); ++i) {
				h_AK8jets_pt_newq->Fill(data.FatJet[iJetAK8[i]].pt, w);
				h_AK8jets_eta_newq->Fill(data.FatJet[iJetAK8[i]].eta, w);
				h_AK8jets_phi_newq->Fill(data.FatJet[iJetAK8[i]].phi, w);
				h_AK8jets_msoftdrop_newq->Fill(data.FatJet[iJetAK8[i]].msoftdrop, w);
				h_AK8jets_tau21_newq->Fill(tau21.at(iJetAK8[i]),w);
				h_AK8jets_tau32_newq->Fill(tau32.at(iJetAK8[i]),w);
			}
			if(nJet>=4 && nJet<6){
				h_ht_AK4_newq_nj45->Fill(AK4_Ht, w);
				h_MR_newq_nj45->Fill(MR, w);
				h_R2_newq_nj45->Fill(R2, w);
				h_MET_newq_nj45->Fill(data.MET_pt,w);
				h_R2_MR_newq_nj45->Fill(MR, R2, w);
				h_MET_phi_newq_nj45->Fill(data.MET_phi,w);
				h_nWjet_newq_nj45 -> Fill(nBoostMassTag,w);
				h_nTopjet_newq_nj45 -> Fill(nBoostMassTag,w);

				h_jet1_pt_newq_nj45->Fill(data.Jet[iJet[0]].pt, w);
				h_jet1_eta_newq_nj45->Fill(data.Jet[iJet[0]].eta, w);
				h_jet1_phi_newq_nj45->Fill(data.Jet[iJet[0]].phi, w);
				for (size_t i=0; i<iJet.size(); ++i) {
					h_jets_pt_newq_nj45->Fill(data.Jet[iJet[i]].pt, w);
					h_jets_eta_newq_nj45->Fill(data.Jet[iJet[i]].eta, w);
					h_jets_phi_newq_nj45->Fill(data.Jet[iJet[i]].phi, w);
				}
				h_AK8jet1_pt_newq_nj45->Fill(data.FatJet[iJetAK8[0]].pt, w);
				h_AK8jet1_eta_newq_nj45->Fill(data.FatJet[iJetAK8[0]].eta, w);
				h_AK8jet1_phi_newq_nj45->Fill(data.FatJet[iJetAK8[0]].phi, w);
				h_AK8jet1_tau21_newq_nj45->Fill(tau21.at(iJetAK8[0]),w);
				h_AK8jet1_tau32_newq_nj45->Fill(tau32.at(iJetAK8[0]),w);
				for (size_t i=0; i<iJetAK8.size(); ++i) {
					h_AK8jets_pt_newq_nj45->Fill(data.FatJet[iJetAK8[i]].pt, w);
					h_AK8jets_eta_newq_nj45->Fill(data.FatJet[iJetAK8[i]].eta, w);
					h_AK8jets_phi_newq_nj45->Fill(data.FatJet[iJetAK8[i]].phi, w);
					h_AK8jets_msoftdrop_newq_nj45->Fill(data.FatJet[iJetAK8[i]].msoftdrop, w);
					h_AK8jets_tau21_newq_nj45->Fill(tau21.at(iJetAK8[i]),w);
					h_AK8jets_tau32_newq_nj45->Fill(tau32.at(iJetAK8[i]),w);
				}
			}
			if(nJet>=6){
				h_ht_AK4_newq_nj6->Fill(AK4_Ht, w);
				h_MR_newq_nj6->Fill(MR, w);
				h_R2_newq_nj6->Fill(R2, w);
				h_MET_newq_nj6->Fill(data.MET_pt,w);
				h_R2_MR_newq_nj6->Fill(MR, R2, w);
				h_MET_phi_newq_nj6->Fill(data.MET_phi,w);
				h_nWjet_newq_nj6 -> Fill(nBoostMassTag,w);
				h_nTopjet_newq_nj6 -> Fill(nBoostMassTag,w);

				h_jet1_pt_newq_nj6->Fill(data.Jet[iJet[0]].pt, w);
				h_jet1_eta_newq_nj6->Fill(data.Jet[iJet[0]].eta, w);
				h_jet1_phi_newq_nj6->Fill(data.Jet[iJet[0]].phi, w);
				for (size_t i=0; i<iJet.size(); ++i) {
					h_jets_pt_newq_nj6->Fill(data.Jet[iJet[i]].pt, w);
					h_jets_eta_newq_nj6->Fill(data.Jet[iJet[i]].eta, w);
					h_jets_phi_newq_nj6->Fill(data.Jet[iJet[i]].phi, w);
				}
				h_AK8jet1_pt_newq_nj6->Fill(data.FatJet[iJetAK8[0]].pt, w);
				h_AK8jet1_eta_newq_nj6->Fill(data.FatJet[iJetAK8[0]].eta, w);
				h_AK8jet1_phi_newq_nj6->Fill(data.FatJet[iJetAK8[0]].phi, w);
				h_AK8jet1_tau21_newq_nj6->Fill(tau21.at(iJetAK8[0]),w);
				h_AK8jet1_tau32_newq_nj6->Fill(tau32.at(iJetAK8[0]),w);
				for (size_t i=0; i<iJetAK8.size(); ++i) {
					h_AK8jets_pt_newq_nj6->Fill(data.FatJet[iJetAK8[i]].pt, w);
					h_AK8jets_eta_newq_nj6->Fill(data.FatJet[iJetAK8[i]].eta, w);
					h_AK8jets_phi_newq_nj6->Fill(data.FatJet[iJetAK8[i]].phi, w);
					h_AK8jets_msoftdrop_newq_nj6->Fill(data.FatJet[iJetAK8[i]].msoftdrop, w);
					h_AK8jets_tau21_newq_nj6->Fill(tau21.at(iJetAK8[i]),w);
					h_AK8jets_tau32_newq_nj6->Fill(tau32.at(iJetAK8[i]),w);
				}
			}
		}

		// New QCD enriched region -w/o W, Top tag
		w = sf_weight['n'];
		if (apply_all_cuts('n')) {
			h_njet_news    ->Fill(nJet,        w);
			h_nAK8jet_news ->Fill(nJetAK8,     w);
			h_ht_AK4_news->Fill(AK4_Ht, w);
			h_MR_news->Fill(MR, w);
			h_R2_news->Fill(R2, w);
			h_MET_news->Fill(data.MET_pt,w);
			h_R2_MR_news->Fill(MR, R2, w);
			h_R2_MET_news->Fill(data.MET_pt, R2, w);
			h_MR_MET_news->Fill(data.MET_pt, MR, w);
			h_AK8Jet1pT_MET_news->Fill(data.MET_pt, data.FatJet[iJetAK8[0]].pt, w);
			h_MET_phi_news->Fill(data.MET_phi,w);
			h_nWjet_news -> Fill(nBoostMassTag,w);
			h_nTopjet_news -> Fill(nBoostMassTag,w);

			for (size_t i=0; i<2; ++i) {
				h_Megajets_pt_news->Fill(hemis_AK4[i].Pt(), w);
				h_Megajets_eta_news->Fill(hemis_AK4[i].Eta(), w);
				h_Megajets_phi_news->Fill(hemis_AK4[i].Phi(), w);
			}

			h_jet1_pt_news->Fill(data.Jet[iJet[0]].pt, w);
			h_jet1_eta_news->Fill(data.Jet[iJet[0]].eta, w);
			h_jet1_phi_news->Fill(data.Jet[iJet[0]].phi, w);
			for (size_t i=0; i<iJet.size(); ++i) {
				h_jets_pt_news->Fill(data.Jet[iJet[i]].pt, w);
				h_jets_eta_news->Fill(data.Jet[iJet[i]].eta, w);
				h_jets_phi_news->Fill(data.Jet[iJet[i]].phi, w);
			}
			h_AK8jet1_pt_news->Fill(data.FatJet[iJetAK8[0]].pt, w);
			h_AK8jet1_eta_news->Fill(data.FatJet[iJetAK8[0]].eta, w);
			h_AK8jet1_phi_news->Fill(data.FatJet[iJetAK8[0]].phi, w);
			h_AK8jet1_tau21_news->Fill(tau21.at(iJetAK8[0]),w);
			h_AK8jet1_tau32_news->Fill(tau32.at(iJetAK8[0]),w);
			for (size_t i=0; i<iJetAK8.size(); ++i) {
				h_AK8jets_pt_news->Fill(data.FatJet[iJetAK8[i]].pt, w);
				h_AK8jets_eta_news->Fill(data.FatJet[iJetAK8[i]].eta, w);
				h_AK8jets_phi_news->Fill(data.FatJet[iJetAK8[i]].phi, w);
				h_AK8jets_msoftdrop_news->Fill(data.FatJet[iJetAK8[i]].msoftdrop, w);
				h_AK8jets_tau21_news->Fill(tau21.at(iJetAK8[i]),w);
				h_AK8jets_tau32_news->Fill(tau32.at(iJetAK8[i]),w);
			}
			if(nJet>=4 && nJet<6){
				h_ht_AK4_news_nj45->Fill(AK4_Ht, w);
				h_MR_news_nj45->Fill(MR, w);
				h_R2_news_nj45->Fill(R2, w);
				h_MET_news_nj45->Fill(data.MET_pt,w);
				h_R2_MR_news_nj45->Fill(MR, R2, w);
				h_MET_phi_news_nj45->Fill(data.MET_phi,w);
				h_nWjet_news_nj45 -> Fill(nBoostMassTag,w);
				h_nTopjet_news_nj45 -> Fill(nBoostMassTag,w);

				h_jet1_pt_news_nj45->Fill(data.Jet[iJet[0]].pt, w);
				h_jet1_eta_news_nj45->Fill(data.Jet[iJet[0]].eta, w);
				h_jet1_phi_news_nj45->Fill(data.Jet[iJet[0]].phi, w);
				for (size_t i=0; i<iJet.size(); ++i) {
					h_jets_pt_news_nj45->Fill(data.Jet[iJet[i]].pt, w);
					h_jets_eta_news_nj45->Fill(data.Jet[iJet[i]].eta, w);
					h_jets_phi_news_nj45->Fill(data.Jet[iJet[i]].phi, w);
				}
				h_AK8jet1_pt_news_nj45->Fill(data.FatJet[iJetAK8[0]].pt, w);
				h_AK8jet1_eta_news_nj45->Fill(data.FatJet[iJetAK8[0]].eta, w);
				h_AK8jet1_phi_news_nj45->Fill(data.FatJet[iJetAK8[0]].phi, w);
				h_AK8jet1_tau21_news_nj45->Fill(tau21.at(iJetAK8[0]),w);
				h_AK8jet1_tau32_news_nj45->Fill(tau32.at(iJetAK8[0]),w);
				for (size_t i=0; i<iJetAK8.size(); ++i) {
					h_AK8jets_pt_news_nj45->Fill(data.FatJet[iJetAK8[i]].pt, w);
					h_AK8jets_eta_news_nj45->Fill(data.FatJet[iJetAK8[i]].eta, w);
					h_AK8jets_phi_news_nj45->Fill(data.FatJet[iJetAK8[i]].phi, w);
					h_AK8jets_msoftdrop_news_nj45->Fill(data.FatJet[iJetAK8[i]].msoftdrop, w);
					h_AK8jets_tau21_news_nj45->Fill(tau21.at(iJetAK8[i]),w);
					h_AK8jets_tau32_news_nj45->Fill(tau32.at(iJetAK8[i]),w);
				}
			}
			if(nJet>=6){
				h_ht_AK4_news_nj6->Fill(AK4_Ht, w);
				h_MR_news_nj6->Fill(MR, w);
				h_R2_news_nj6->Fill(R2, w);
				h_MET_news_nj6->Fill(data.MET_pt,w);
				h_R2_MR_news_nj6->Fill(MR, R2, w);
				h_MET_phi_news_nj6->Fill(data.MET_phi,w);
				h_nWjet_news_nj6 -> Fill(nBoostMassTag,w);
				h_nTopjet_news_nj6 -> Fill(nBoostMassTag,w);

				h_jet1_pt_news_nj6->Fill(data.Jet[iJet[0]].pt, w);
				h_jet1_eta_news_nj6->Fill(data.Jet[iJet[0]].eta, w);
				h_jet1_phi_news_nj6->Fill(data.Jet[iJet[0]].phi, w);
				for (size_t i=0; i<iJet.size(); ++i) {
					h_jets_pt_news_nj6->Fill(data.Jet[iJet[i]].pt, w);
					h_jets_eta_news_nj6->Fill(data.Jet[iJet[i]].eta, w);
					h_jets_phi_news_nj6->Fill(data.Jet[iJet[i]].phi, w);
				}
				h_AK8jet1_pt_news_nj6->Fill(data.FatJet[iJetAK8[0]].pt, w);
				h_AK8jet1_eta_news_nj6->Fill(data.FatJet[iJetAK8[0]].eta, w);
				h_AK8jet1_phi_news_nj6->Fill(data.FatJet[iJetAK8[0]].phi, w);
				h_AK8jet1_tau21_news_nj6->Fill(tau21.at(iJetAK8[0]),w);
				h_AK8jet1_tau32_news_nj6->Fill(tau32.at(iJetAK8[0]),w);
				for (size_t i=0; i<iJetAK8.size(); ++i) {
					h_AK8jets_pt_news_nj6->Fill(data.FatJet[iJetAK8[i]].pt, w);
					h_AK8jets_eta_news_nj6->Fill(data.FatJet[iJetAK8[i]].eta, w);
					h_AK8jets_phi_news_nj6->Fill(data.FatJet[iJetAK8[i]].phi, w);
					h_AK8jets_msoftdrop_news_nj6->Fill(data.FatJet[iJetAK8[i]].msoftdrop, w);
					h_AK8jets_tau21_news_nj6->Fill(tau21.at(iJetAK8[i]),w);
					h_AK8jets_tau32_news_nj6->Fill(tau32.at(iJetAK8[i]),w);
				}
			}
		}

		// Signal region
		w = sf_weight['t'];
		//if (apply_all_cuts_except('S', "HLT")) {
		if (apply_all_cuts('t')) {
			h_njet_Topjet_S    ->Fill(nJet,        w);
			h_nAK8jet_Topjet_S ->Fill(nJetAK8,     w);
			h_ht_AK4_Topjet_S->Fill(AK4_Ht, w);
			h_MR_Topjet_S->Fill(MR, w);
			h_R2_Topjet_S->Fill(R2, w);
			h_MET_Topjet_S->Fill(data.MET_pt,w);
			h_R2_MR_Topjet_S->Fill(MR, R2, w);
			h_R2_MET_Topjet_S->Fill(data.MET_pt, R2, w);
			h_MR_MET_Topjet_S->Fill(data.MET_pt, MR, w);
			h_R2_HT_Topjet_S->Fill(AK4_Ht, R2, w);
			h_MR_HT_Topjet_S->Fill(AK4_Ht, MR, w);
			h_HT_MET_Topjet_S->Fill(data.MET_pt, AK4_Ht, w);
			h_MET_phi_Topjet_S->Fill(data.MET_phi,w);

			for (size_t i=0; i<2; ++i) {
				h_Megajets_pt_Topjet_S->Fill(hemis_AK4[i].Pt(), w);
				h_Megajets_eta_Topjet_S->Fill(hemis_AK4[i].Eta(), w);
				h_Megajets_phi_Topjet_S->Fill(hemis_AK4[i].Phi(), w);
			}

			h_jet1_pt_Topjet_S->Fill(data.Jet[iJet[0]].pt, w);
			h_jet1_eta_Topjet_S->Fill(data.Jet[iJet[0]].eta, w);
			h_jet1_phi_Topjet_S->Fill(data.Jet[iJet[0]].phi, w);
			for (size_t i=0; i<iJet.size(); ++i) {
				h_jets_pt_Topjet_S->Fill(data.Jet[iJet[i]].pt, w);
				h_jets_eta_Topjet_S->Fill(data.Jet[iJet[i]].eta, w);
				h_jets_phi_Topjet_S->Fill(data.Jet[iJet[i]].phi, w);
			}
			h_AK8jet1_pt_Topjet_S->Fill(data.FatJet[iJetAK8[0]].pt, w);
			h_AK8jet1_eta_Topjet_S->Fill(data.FatJet[iJetAK8[0]].eta, w);
			h_AK8jet1_phi_Topjet_S->Fill(data.FatJet[iJetAK8[0]].phi, w);
			h_AK8jet1_tau21_Topjet_S->Fill(tau21.at(iJetAK8[0]),w);
			h_AK8jet1_tau32_Topjet_S->Fill(tau32.at(iJetAK8[0]),w);
			for (size_t i=0; i<iJetAK8.size(); ++i) {
				h_AK8jets_pt_Topjet_S->Fill(data.FatJet[iJetAK8[i]].pt, w);
				h_AK8jets_eta_Topjet_S->Fill(data.FatJet[iJetAK8[i]].eta, w);
				h_AK8jets_phi_Topjet_S->Fill(data.FatJet[iJetAK8[i]].phi, w);
				h_AK8jets_msoftdrop_Topjet_S->Fill(data.FatJet[iJetAK8[i]].msoftdrop, w);
				h_AK8jets_tau21_Topjet_S->Fill(tau21.at(iJetAK8[i]),w);
				h_AK8jets_tau32_Topjet_S->Fill(tau32.at(iJetAK8[i]),w);
			}
			for (size_t i=0; i<iHadTopTag.size(); ++i) {
				h_Topjets_pt_Topjet_S->Fill(data.FatJet[iHadTopTag[i]].pt, w);
				h_Topjets_eta_Topjet_S->Fill(data.FatJet[iHadTopTag[i]].eta, w);
				h_Topjets_phi_Topjet_S->Fill(data.FatJet[iHadTopTag[i]].phi, w);
				h_Topjets_tau21_Topjet_S->Fill(tau21.at(iHadTopTag[i]), w);
				h_Topjets_tau32_Topjet_S->Fill(tau32.at(iHadTopTag[i]), w);
        h_deepTagMD_WvsQCD_Topjet_S->Fill(data.FatJet[iHadTopTag[i]].deepTagMD_WvsQCD, w);
        h_deepTagMD_TvsQCD_Topjet_S->Fill(data.FatJet[iHadTopTag[i]].deepTagMD_TvsQCD, w);
        h_deepTag_WvsQCD_Topjet_S->Fill(data.FatJet[iHadTopTag[i]].deepTag_WvsQCD, w);
        h_deepTag_TvsQCD_Topjet_S->Fill(data.FatJet[iHadTopTag[i]].deepTag_TvsQCD, w);
			}

			if(nJet>=4 && nJet<6){
				h_ht_AK4_Topjet_S_nj45->Fill(AK4_Ht, w);
				h_MR_Topjet_S_nj45->Fill(MR, w);
				h_R2_Topjet_S_nj45->Fill(R2, w);
				h_MET_Topjet_S_nj45->Fill(data.MET_pt,w);
				h_R2_MR_Topjet_S_nj45->Fill(MR, R2, w);
				h_R2_MET_Topjet_S_nj45->Fill(data.MET_pt, R2, w);
				h_MR_MET_Topjet_S_nj45->Fill(data.MET_pt, MR, w);
				h_R2_HT_Topjet_S_nj45->Fill(AK4_Ht, R2, w);
				h_MR_HT_Topjet_S_nj45->Fill(AK4_Ht, MR, w);
				h_HT_MET_Topjet_S_nj45->Fill(data.MET_pt, AK4_Ht, w);
				h_AK8Jet1pT_MET_Topjet_S_nj45->Fill(data.MET_pt, data.FatJet[iJetAK8[0]].pt, w);
				h_MET_phi_Topjet_S_nj45->Fill(data.MET_phi,w);

				h_jet1_pt_Topjet_S_nj45->Fill(data.Jet[iJet[0]].pt, w);
				h_jet1_eta_Topjet_S_nj45->Fill(data.Jet[iJet[0]].eta, w);
				h_jet1_phi_Topjet_S_nj45->Fill(data.Jet[iJet[0]].phi, w);
				for (size_t i=0; i<iJet.size(); ++i) {
					h_jets_pt_Topjet_S_nj45->Fill(data.Jet[iJet[i]].pt, w);
					h_jets_eta_Topjet_S_nj45->Fill(data.Jet[iJet[i]].eta, w);
					h_jets_phi_Topjet_S_nj45->Fill(data.Jet[iJet[i]].phi, w);
				}
				h_AK8jet1_pt_Topjet_S_nj45->Fill(data.FatJet[iJetAK8[0]].pt, w);
				h_AK8jet1_eta_Topjet_S_nj45->Fill(data.FatJet[iJetAK8[0]].eta, w);
				h_AK8jet1_phi_Topjet_S_nj45->Fill(data.FatJet[iJetAK8[0]].phi, w);
				h_AK8jet1_tau21_Topjet_S_nj45->Fill(tau21.at(iJetAK8[0]),w);
				h_AK8jet1_tau32_Topjet_S_nj45->Fill(tau32.at(iJetAK8[0]),w);
				for (size_t i=0; i<iJetAK8.size(); ++i) {
					h_AK8jets_pt_Topjet_S_nj45->Fill(data.FatJet[iJetAK8[i]].pt, w);
					h_AK8jets_eta_Topjet_S_nj45->Fill(data.FatJet[iJetAK8[i]].eta, w);
					h_AK8jets_phi_Topjet_S_nj45->Fill(data.FatJet[iJetAK8[i]].phi, w);
					h_AK8jets_msoftdrop_Topjet_S_nj45->Fill(data.FatJet[iJetAK8[i]].msoftdrop, w);
					h_AK8jets_tau21_Topjet_S_nj45->Fill(tau21.at(iJetAK8[i]),w);
					h_AK8jets_tau32_Topjet_S_nj45->Fill(tau32.at(iJetAK8[i]),w);
				}
				for (size_t i=0; i<iHadTopTag.size(); ++i) {
					h_Topjets_pt_Topjet_S_nj45->Fill(data.FatJet[iHadTopTag[i]].pt, w);
					h_Topjets_eta_Topjet_S_nj45->Fill(data.FatJet[iHadTopTag[i]].eta, w);
					h_Topjets_phi_Topjet_S_nj45->Fill(data.FatJet[iHadTopTag[i]].phi, w);
					h_Topjets_tau21_Topjet_S_nj45->Fill(tau21.at(iHadTopTag[i]), w);
					h_Topjets_tau32_Topjet_S_nj45->Fill(tau32.at(iHadTopTag[i]), w);
				}
			}
			if(nJet>=6){
				h_ht_AK4_Topjet_S_nj6->Fill(AK4_Ht, w);
				h_MR_Topjet_S_nj6->Fill(MR, w);
				h_R2_Topjet_S_nj6->Fill(R2, w);
				h_MET_Topjet_S_nj6->Fill(data.MET_pt,w);
				h_R2_MR_Topjet_S_nj6->Fill(MR, R2, w);
				h_R2_MET_Topjet_S_nj6->Fill(data.MET_pt, R2, w);
				h_MR_MET_Topjet_S_nj6->Fill(data.MET_pt, MR, w);
				h_R2_HT_Topjet_S_nj6->Fill(AK4_Ht, R2, w);
				h_MR_HT_Topjet_S_nj6->Fill(AK4_Ht, MR, w);
				h_HT_MET_Topjet_S_nj6->Fill(data.MET_pt, AK4_Ht, w);
				h_AK8Jet1pT_MET_Topjet_S_nj6->Fill(data.MET_pt, data.FatJet[iJetAK8[0]].pt, w);
				h_MET_phi_Topjet_S_nj6->Fill(data.MET_phi,w);

				h_jet1_pt_Topjet_S_nj6->Fill(data.Jet[iJet[0]].pt, w);
				h_jet1_eta_Topjet_S_nj6->Fill(data.Jet[iJet[0]].eta, w);
				h_jet1_phi_Topjet_S_nj6->Fill(data.Jet[iJet[0]].phi, w);
				for (size_t i=0; i<iJet.size(); ++i) {
					h_jets_pt_Topjet_S_nj6->Fill(data.Jet[iJet[i]].pt, w);
					h_jets_eta_Topjet_S_nj6->Fill(data.Jet[iJet[i]].eta, w);
					h_jets_phi_Topjet_S_nj6->Fill(data.Jet[iJet[i]].phi, w);
				}
				h_AK8jet1_pt_Topjet_S_nj6->Fill(data.FatJet[iJetAK8[0]].pt, w);
				h_AK8jet1_eta_Topjet_S_nj6->Fill(data.FatJet[iJetAK8[0]].eta, w);
				h_AK8jet1_phi_Topjet_S_nj6->Fill(data.FatJet[iJetAK8[0]].phi, w);
				h_AK8jet1_tau21_Topjet_S_nj6->Fill(tau21.at(iJetAK8[0]),w);
				h_AK8jet1_tau32_Topjet_S_nj6->Fill(tau32.at(iJetAK8[0]),w);
				for (size_t i=0; i<iJetAK8.size(); ++i) {
					h_AK8jets_pt_Topjet_S_nj6->Fill(data.FatJet[iJetAK8[i]].pt, w);
					h_AK8jets_eta_Topjet_S_nj6->Fill(data.FatJet[iJetAK8[i]].eta, w);
					h_AK8jets_phi_Topjet_S_nj6->Fill(data.FatJet[iJetAK8[i]].phi, w);
					h_AK8jets_msoftdrop_Topjet_S_nj6->Fill(data.FatJet[iJetAK8[i]].msoftdrop, w);
					h_AK8jets_tau21_Topjet_S_nj6->Fill(tau21.at(iJetAK8[i]),w);
					h_AK8jets_tau32_Topjet_S_nj6->Fill(tau32.at(iJetAK8[i]),w);
				}
				for (size_t i=0; i<iHadTopTag.size(); ++i) {
					h_Topjets_pt_Topjet_S_nj6->Fill(data.FatJet[iHadTopTag[i]].pt, w);
					h_Topjets_eta_Topjet_S_nj6->Fill(data.FatJet[iHadTopTag[i]].eta, w);
					h_Topjets_phi_Topjet_S_nj6->Fill(data.FatJet[iHadTopTag[i]].phi, w);
					h_Topjets_tau21_Topjet_S_nj6->Fill(tau21.at(iHadTopTag[i]), w);
					h_Topjets_tau32_Topjet_S_nj6->Fill(tau32.at(iHadTopTag[i]), w);
				}
			}
		}

		// Signal region
		w = sf_weight['S'];
		//if (apply_all_cuts_except('S', "HLT")) {
		if (apply_all_cuts('S')) {
			h_njet_Wjet_S    ->Fill(nJet,        w);
			h_nAK8jet_Wjet_S ->Fill(nJetAK8,     w);
			h_ht_AK4_Wjet_S->Fill(AK4_Ht, w);
			h_MR_Wjet_S->Fill(MR, w);
			h_R2_Wjet_S->Fill(R2, w);
			h_MET_Wjet_S->Fill(data.MET_pt,w);
			h_R2_MR_Wjet_S->Fill(MR, R2, w);
			h_R2_MET_Wjet_S->Fill(data.MET_pt, R2, w);
			h_MR_MET_Wjet_S->Fill(data.MET_pt, MR, w);
			h_R2_HT_Wjet_S->Fill(AK4_Ht, R2, w);
			h_MR_HT_Wjet_S->Fill(AK4_Ht, MR, w);
			h_HT_MET_Wjet_S->Fill(data.MET_pt, AK4_Ht, w);
			h_MET_phi_Wjet_S->Fill(data.MET_phi,w);

			for (size_t i=0; i<2; ++i) {
				h_Megajets_pt_Wjet_S->Fill(hemis_AK4[i].Pt(), w);
				h_Megajets_eta_Wjet_S->Fill(hemis_AK4[i].Eta(), w);
				h_Megajets_phi_Wjet_S->Fill(hemis_AK4[i].Phi(), w);
			}

			h_jet1_pt_Wjet_S->Fill(data.Jet[iJet[0]].pt, w);
			h_jet1_eta_Wjet_S->Fill(data.Jet[iJet[0]].eta, w);
			h_jet1_phi_Wjet_S->Fill(data.Jet[iJet[0]].phi, w);
			for (size_t i=0; i<iJet.size(); ++i) {
				h_jets_pt_Wjet_S->Fill(data.Jet[iJet[i]].pt, w);
				h_jets_eta_Wjet_S->Fill(data.Jet[iJet[i]].eta, w);
				h_jets_phi_Wjet_S->Fill(data.Jet[iJet[i]].phi, w);
			}
			h_AK8jet1_pt_Wjet_S->Fill(data.FatJet[iJetAK8[0]].pt, w);
			h_AK8jet1_eta_Wjet_S->Fill(data.FatJet[iJetAK8[0]].eta, w);
			h_AK8jet1_phi_Wjet_S->Fill(data.FatJet[iJetAK8[0]].phi, w);
			h_AK8jet1_tau21_Wjet_S->Fill(tau21.at(iJetAK8[0]),w);
			h_AK8jet1_tau32_Wjet_S->Fill(tau32.at(iJetAK8[0]),w);
			for (size_t i=0; i<iJetAK8.size(); ++i) {
				h_AK8jets_pt_Wjet_S->Fill(data.FatJet[iJetAK8[i]].pt, w);
				h_AK8jets_eta_Wjet_S->Fill(data.FatJet[iJetAK8[i]].eta, w);
				h_AK8jets_phi_Wjet_S->Fill(data.FatJet[iJetAK8[i]].phi, w);
				h_AK8jets_msoftdrop_Wjet_S->Fill(data.FatJet[iJetAK8[i]].msoftdrop, w);
				h_AK8jets_tau21_Wjet_S->Fill(tau21.at(iJetAK8[i]),w);
				h_AK8jets_tau32_Wjet_S->Fill(tau32.at(iJetAK8[i]),w);
			}
			for (size_t i=0; i<iBoostMassTag.size(); ++i) {
				h_Wjets_pt_Wjet_S->Fill(data.FatJet[iBoostMassTag[i]].pt, w);
				h_Wjets_eta_Wjet_S->Fill(data.FatJet[iBoostMassTag[i]].eta, w);
				h_Wjets_phi_Wjet_S->Fill(data.FatJet[iBoostMassTag[i]].phi, w);
				h_Wjets_tau21_Wjet_S->Fill(tau21.at(iBoostMassTag[i]), w);
				h_Wjets_tau32_Wjet_S->Fill(tau32.at(iBoostMassTag[i]), w);
        h_deepTagMD_WvsQCD_Wjet_S->Fill(data.FatJet[iBoostMassTag[i]].deepTagMD_WvsQCD, w);
        h_deepTagMD_TvsQCD_Wjet_S->Fill(data.FatJet[iBoostMassTag[i]].deepTagMD_TvsQCD, w);
        h_deepTag_WvsQCD_Wjet_S->Fill(data.FatJet[iBoostMassTag[i]].deepTag_WvsQCD, w);
        h_deepTag_TvsQCD_Wjet_S->Fill(data.FatJet[iBoostMassTag[i]].deepTag_TvsQCD, w);
			}

			if(nJet>=4 && nJet<6){
				h_ht_AK4_Wjet_S_nj45->Fill(AK4_Ht, w);
				h_MR_Wjet_S_nj45->Fill(MR, w);
				h_R2_Wjet_S_nj45->Fill(R2, w);
				h_MET_Wjet_S_nj45->Fill(data.MET_pt,w);
				h_R2_MR_Wjet_S_nj45->Fill(MR, R2, w);
				h_R2_MET_Wjet_S_nj45->Fill(data.MET_pt, R2, w);
				h_MR_MET_Wjet_S_nj45->Fill(data.MET_pt, MR, w);
				h_R2_HT_Wjet_S_nj45->Fill(AK4_Ht, R2, w);
				h_MR_HT_Wjet_S_nj45->Fill(AK4_Ht, MR, w);
				h_HT_MET_Wjet_S_nj45->Fill(data.MET_pt, AK4_Ht, w);
				h_AK8Jet1pT_MET_Wjet_S_nj45->Fill(data.MET_pt, data.FatJet[iJetAK8[0]].pt, w);
				h_MET_phi_Wjet_S_nj45->Fill(data.MET_phi,w);

				h_jet1_pt_Wjet_S_nj45->Fill(data.Jet[iJet[0]].pt, w);
				h_jet1_eta_Wjet_S_nj45->Fill(data.Jet[iJet[0]].eta, w);
				h_jet1_phi_Wjet_S_nj45->Fill(data.Jet[iJet[0]].phi, w);
				for (size_t i=0; i<iJet.size(); ++i) {
					h_jets_pt_Wjet_S_nj45->Fill(data.Jet[iJet[i]].pt, w);
					h_jets_eta_Wjet_S_nj45->Fill(data.Jet[iJet[i]].eta, w);
					h_jets_phi_Wjet_S_nj45->Fill(data.Jet[iJet[i]].phi, w);
				}
				h_AK8jet1_pt_Wjet_S_nj45->Fill(data.FatJet[iJetAK8[0]].pt, w);
				h_AK8jet1_eta_Wjet_S_nj45->Fill(data.FatJet[iJetAK8[0]].eta, w);
				h_AK8jet1_phi_Wjet_S_nj45->Fill(data.FatJet[iJetAK8[0]].phi, w);
				h_AK8jet1_tau21_Wjet_S_nj45->Fill(tau21.at(iJetAK8[0]),w);
				h_AK8jet1_tau32_Wjet_S_nj45->Fill(tau32.at(iJetAK8[0]),w);
				for (size_t i=0; i<iJetAK8.size(); ++i) {
					h_AK8jets_pt_Wjet_S_nj45->Fill(data.FatJet[iJetAK8[i]].pt, w);
					h_AK8jets_eta_Wjet_S_nj45->Fill(data.FatJet[iJetAK8[i]].eta, w);
					h_AK8jets_phi_Wjet_S_nj45->Fill(data.FatJet[iJetAK8[i]].phi, w);
					h_AK8jets_msoftdrop_Wjet_S_nj45->Fill(data.FatJet[iJetAK8[i]].msoftdrop, w);
					h_AK8jets_tau21_Wjet_S_nj45->Fill(tau21.at(iJetAK8[i]),w);
					h_AK8jets_tau32_Wjet_S_nj45->Fill(tau32.at(iJetAK8[i]),w);
				}
				for (size_t i=0; i<iBoostMassTag.size(); ++i) {
					h_Wjets_pt_Wjet_S_nj45->Fill(data.FatJet[iBoostMassTag[i]].pt, w);
					h_Wjets_eta_Wjet_S_nj45->Fill(data.FatJet[iBoostMassTag[i]].eta, w);
					h_Wjets_phi_Wjet_S_nj45->Fill(data.FatJet[iBoostMassTag[i]].phi, w);
					h_Wjets_tau21_Wjet_S_nj45->Fill(tau21.at(iBoostMassTag[i]), w);
					h_Wjets_tau32_Wjet_S_nj45->Fill(tau32.at(iBoostMassTag[i]), w);
				}
			}
			if(nJet>=6){
				h_ht_AK4_Wjet_S_nj6->Fill(AK4_Ht, w);
				h_MR_Wjet_S_nj6->Fill(MR, w);
				h_R2_Wjet_S_nj6->Fill(R2, w);
				h_MET_Wjet_S_nj6->Fill(data.MET_pt,w);
				h_R2_MR_Wjet_S_nj6->Fill(MR, R2, w);
				h_R2_MET_Wjet_S_nj6->Fill(data.MET_pt, R2, w);
				h_MR_MET_Wjet_S_nj6->Fill(data.MET_pt, MR, w);
				h_R2_HT_Wjet_S_nj6->Fill(AK4_Ht, R2, w);
				h_MR_HT_Wjet_S_nj6->Fill(AK4_Ht, MR, w);
				h_HT_MET_Wjet_S_nj6->Fill(data.MET_pt, AK4_Ht, w);
				h_AK8Jet1pT_MET_Wjet_S_nj6->Fill(data.MET_pt, data.FatJet[iJetAK8[0]].pt, w);
				h_MET_phi_Wjet_S_nj6->Fill(data.MET_phi,w);

				h_jet1_pt_Wjet_S_nj6->Fill(data.Jet[iJet[0]].pt, w);
				h_jet1_eta_Wjet_S_nj6->Fill(data.Jet[iJet[0]].eta, w);
				h_jet1_phi_Wjet_S_nj6->Fill(data.Jet[iJet[0]].phi, w);
				for (size_t i=0; i<iJet.size(); ++i) {
					h_jets_pt_Wjet_S_nj6->Fill(data.Jet[iJet[i]].pt, w);
					h_jets_eta_Wjet_S_nj6->Fill(data.Jet[iJet[i]].eta, w);
					h_jets_phi_Wjet_S_nj6->Fill(data.Jet[iJet[i]].phi, w);
				}
				h_AK8jet1_pt_Wjet_S_nj6->Fill(data.FatJet[iJetAK8[0]].pt, w);
				h_AK8jet1_eta_Wjet_S_nj6->Fill(data.FatJet[iJetAK8[0]].eta, w);
				h_AK8jet1_phi_Wjet_S_nj6->Fill(data.FatJet[iJetAK8[0]].phi, w);
				h_AK8jet1_tau21_Wjet_S_nj6->Fill(tau21.at(iJetAK8[0]),w);
				h_AK8jet1_tau32_Wjet_S_nj6->Fill(tau32.at(iJetAK8[0]),w);
				for (size_t i=0; i<iJetAK8.size(); ++i) {
					h_AK8jets_pt_Wjet_S_nj6->Fill(data.FatJet[iJetAK8[i]].pt, w);
					h_AK8jets_eta_Wjet_S_nj6->Fill(data.FatJet[iJetAK8[i]].eta, w);
					h_AK8jets_phi_Wjet_S_nj6->Fill(data.FatJet[iJetAK8[i]].phi, w);
					h_AK8jets_msoftdrop_Wjet_S_nj6->Fill(data.FatJet[iJetAK8[i]].msoftdrop, w);
					h_AK8jets_tau21_Wjet_S_nj6->Fill(tau21.at(iJetAK8[i]),w);
					h_AK8jets_tau32_Wjet_S_nj6->Fill(tau32.at(iJetAK8[i]),w);
				}
				for (size_t i=0; i<iBoostMassTag.size(); ++i) {
					h_Wjets_pt_Wjet_S_nj6->Fill(data.FatJet[iBoostMassTag[i]].pt, w);
					h_Wjets_eta_Wjet_S_nj6->Fill(data.FatJet[iBoostMassTag[i]].eta, w);
					h_Wjets_phi_Wjet_S_nj6->Fill(data.FatJet[iBoostMassTag[i]].phi, w);
					h_Wjets_tau21_Wjet_S_nj6->Fill(tau21.at(iBoostMassTag[i]), w);
					h_Wjets_tau32_Wjet_S_nj6->Fill(tau32.at(iBoostMassTag[i]), w);
				}
			}
		}

#if TOP == 0
		if (apply_all_cuts_except('S', "1W")) {
			if(nBoostMassTag >= 1) {
				h_R2_MR_looseS->Fill(MR, R2, w);
				if(nJet>=4 && nJet<6) h_R2_MR_looseS_nj45->Fill(MR, R2, w);
				if(nJet>=6)           h_R2_MR_looseS_nj6->Fill(MR, R2, w);
			}
		}
		if (apply_all_cuts_except('s', "1W")) {
			if(nBoostMassTag >= 1) {
				h_R2_MR_looseS->Fill(MR, R2, w);
				if(nJet>=4 && nJet<6) h_R2_MR_looses_nj45->Fill(MR, R2, w);
				if(nJet>=6)           h_R2_MR_looses_nj6->Fill(MR, R2, w);
			}
		}
		if (apply_all_cuts_except('q', "1aW")) {
			if(nBoostMassTag >= 1) {
				h_R2_MR_looseS->Fill(MR, R2, w);
				if(nJet>=4 && nJet<6) h_R2_MR_looseq_nj45->Fill(MR, R2, w);
				if(nJet>=6)           h_R2_MR_looseq_nj6->Fill(MR, R2, w);
			}
		}
#else
		//if (apply_all_cuts_except('S', "1Top")) {
			//if(nBoostMassTag2 >= 1) h_R2_MR_loose1S->Fill(MR, R2, w);
			//if(nBoostMassTag3 >= 1) h_R2_MR_loose2S->Fill(MR, R2, w);
			//if(nBoostMassTag4 >= 1) h_R2_MR_loose3S->Fill(MR, R2, w);
		//	if(nBoostMassTag >= 1) h_R2_MR_loose3S->Fill(MR, R2, w);
		//}
		if (apply_all_cuts_except('s', "1Top")) {
			//if(nBoostMassTag2 >= 1) h_R2_MR_loose1s->Fill(MR, R2, w);
			//if(nBoostMassTag3 >= 1) h_R2_MR_loose2s->Fill(MR, R2, w);
			//if(nBoostMassTag4 >= 1) h_R2_MR_loose3s->Fill(MR, R2, w);
			if(nBoostMassTag >= 1) h_R2_MR_loose3s->Fill(MR, R2, w);
		}
		if (apply_all_cuts_except('q', "1aTop")) {
			if(nBoostMassTag >= 1) h_R2_MR_loose3q->Fill(MR, R2, w);
		}
#endif

		// Trigger efficiencies
		// No weighting

		// I guess these histots are for data only (trigger efficiencies)
		// One could just use the normal weight  for that ( = 1)
		// Since MC already has trigger efficiency weight applied already
		// one could use simply 1 as the weight there also
		// N-1 weights are not currently supported

		//w = isData ? 1 : sf_weight['S'];
		w = 1;


		bool iscomFFsim = TString(sample).Contains("TTJets_madgraphMLM");
		if(iscomFFsim){ 
			for (size_t i=0; i<data.FatJet.size(); ++i) {
				if (passBoostMassTag[i]) {
					h_AK8Jet1Pt_eta_GenW_no_W->Fill(data.FatJet[i].pt,std::abs(data.FatJet[i].eta),w);
					h_AK8Jet1Pt_eta_GenTop_no_Top->Fill(data.FatJet[i].pt,std::abs(data.FatJet[i].eta),w);
					if (hasGenW[i])    h_AK8Jet1Pt_eta_GenW_W->Fill(data.FatJet[i].pt,std::abs(data.FatJet[i].eta),w);
					if (hasGenTop[i])  h_AK8Jet1Pt_eta_GenTop_Top->Fill(data.FatJet[i].pt,std::abs(data.FatJet[i].eta),w);
					if (!hasGenW[i])   h_AK8Jet1Pt_eta_FakeW_W->Fill(data.FatJet[i].pt,std::abs(data.FatJet[i].eta),w);
					if (!hasGenTop[i]) h_AK8Jet1Pt_eta_FakeTop_Top->Fill(data.FatJet[i].pt,std::abs(data.FatJet[i].eta),w);
				}
			}
		}

		w=1;

		bool isSingleElectron	= TString(sample).Contains("SingleElectron");
		bool isSingleMuon			= TString(sample).Contains("SingleMuon");
		bool isSinglePhoton	  = TString(sample).Contains("SinglePhoton");
		//bool isMET						= TString(sample).Contains("MET");

		bool OR_HLT_Photon = data.HLT_Photon200==1 || data.HLT_Photon300_NoHE==1 || data.HLT_Photon25==1 || data.HLT_Photon33==1 || data.HLT_Photon50==1 || data.HLT_Photon75==1 || data.HLT_Photon90==1 || data.HLT_Photon120==1 || data.HLT_Photon150==1 || data.HLT_Photon175==1;
		//bool OR_HLT_Photon = data.HLT_Photon200==1 || data.HLT_Photon300_NoHE==1;

		bool trigger = false;
		double MET = data.MET_pt;

		if(isSingleElectron && (data.HLT_Ele32_WPTight_Gsf==1 || data.HLT_Ele32_WPTight_Gsf_L1DoubleEG==1 || data.HLT_Ele35_WPTight_Gsf==1) && nEleTight==1 && nMuVeto==0) trigger = true;
		else if(isSingleMuon			&& data.HLT_IsoMu27==1 && nMuTight==1 && nEleVeto==0) trigger= true;
		else if(isSinglePhoton && OR_HLT_Photon && nPhotonSelect==1 && nLepVeto==0 && nTauVeto==0) { trigger = true;  }
		//else if(isSinglePhoton && OR_HLT_Photon && nPhotonSelect==1 && nLepVeto==0 && nTauVeto==0 && nJetNoPho>=3 && MR_pho >= 800 && R2_pho>=0.08) { trigger = true;  }
		//else if(isMET						&& data.HLT_PFMET120_PFMHT120_IDTight==1 && nLepVeto==0 && data.IsoTrack.size()==0) trigger = true;
		//else if(!isSingleElectron && !isSingleMuon && !isMET) trigger = true;
		//else if(!isSingleElectron && !isSingleMuon && !isSinglePhoton) trigger = true;

		if(trigger && isSinglePhoton){
			if(nJetAK8>=1 && nJetNoPho>=3 && R2_pho>=0.08 && MR_pho>=0.08) {
				h_HT_MET_TrigNoMass_0->Fill(MET,AK4_Ht,w);
				if (apply_cut('P',"HLT")) h_HT_MET_TrigNoMass_1->Fill(MET,AK4_Ht,w);
			}
		}

		else if(trigger){
			if (apply_all_cuts_except('P', "HLT"))	h_HT_TrigNoMass_0->Fill(AK4_Ht,w);
			if (apply_all_cuts('P'))	h_HT_TrigNoMass_1->Fill(AK4_Ht,w);

			if (apply_all_cuts_except('P', "HLT"))	h_AK8JetpT_TrigNoMass_0->Fill(data.FatJet[iJetAK8[0]].pt,w);
			if (apply_all_cuts('P'))	h_AK8JetpT_TrigNoMass_1->Fill(data.FatJet[iJetAK8[0]].pt,w);

			if (apply_all_cuts_except('P', "HLT"))	h_AK8JetMass_TrigNoMass_0->Fill(data.FatJet[iJetAK8[0]].msoftdrop,w);
			if (apply_all_cuts('P'))	h_AK8JetMass_TrigNoMass_1->Fill(data.FatJet[iJetAK8[0]].msoftdrop,w);

			if (apply_all_cuts_except('P', "HLT"))	h_MET_TrigNoMass_0->Fill(MET,w);
			if (apply_all_cuts('P'))	h_MET_TrigNoMass_1->Fill(MET,w);

			if (apply_all_cuts_except('P', "HLT"))	h_MR_TrigNoMass_0->Fill(MR,w);
			if (apply_all_cuts('P'))	h_MR_TrigNoMass_1->Fill(MR,w);

			if (apply_all_cuts_except('P', "HLT"))	h_R2_TrigNoMass_0->Fill(R2,w);
			if (apply_all_cuts('P'))	h_R2_TrigNoMass_1->Fill(R2,w);

			if (apply_all_cuts_except('P', "HLT"))	h_R2_MR_TrigNoMass_0->Fill(MR,R2,w);
			if (apply_all_cuts('P'))	h_R2_MR_TrigNoMass_1->Fill(MR,R2,w);

			if (apply_all_cuts_except('P', "HLT"))	h_HT_MET_TrigNoMass_0->Fill(MET,AK4_Ht,w);
			if (apply_all_cuts('P'))	h_HT_MET_TrigNoMass_1->Fill(MET,AK4_Ht,w);

			if (apply_all_cuts_except('P', "HLT"))	h_HT_AK8JetMass_TrigNoMass_0->Fill(data.FatJet[iJetAK8[0]].msoftdrop,AK4_Ht,w);
			if (apply_all_cuts('P'))	h_HT_AK8JetMass_TrigNoMass_1->Fill(data.FatJet[iJetAK8[0]].msoftdrop,AK4_Ht,w);

			if (apply_all_cuts_except('P', "HLT"))	h_MET_AK8JetMass_TrigNoMass_0->Fill(data.FatJet[iJetAK8[0]].msoftdrop,MET,w);
			if (apply_all_cuts('P'))	h_MET_AK8JetMass_TrigNoMass_1->Fill(data.FatJet[iJetAK8[0]].msoftdrop,MET,w);

			if (apply_all_cuts_except('P', "HLT"))	h_HT_MET_AK8JetMass_TrigNoMass_0->Fill(data.FatJet[iJetAK8[0]].msoftdrop,MET,AK4_Ht,w);
			if (apply_all_cuts('P'))	h_HT_MET_AK8JetMass_TrigNoMass_1->Fill(data.FatJet[iJetAK8[0]].msoftdrop,MET,AK4_Ht,w);

			if (apply_all_cuts_except('P', "HLT"))	h_AK8HT_TrigNoMass_0->Fill(AK8_Ht,w);
			if (apply_all_cuts('P'))			h_AK8HT_TrigNoMass_1->Fill(AK8_Ht,w);

			if (apply_all_cuts_except('P', "HLT"))	h_AK8HT_MET_TrigNoMass_0->Fill(MET,AK8_Ht,w);
			if (apply_all_cuts('P'))			h_AK8HT_MET_TrigNoMass_1->Fill(MET,AK8_Ht,w);

			if (apply_all_cuts_except('P', "HLT"))	h_AK8HT_AK8JetMass_TrigNoMass_0->Fill(data.FatJet[iJetAK8[0]].msoftdrop,AK8_Ht,w);
			if (apply_all_cuts('P'))			h_AK8HT_AK8JetMass_TrigNoMass_1->Fill(data.FatJet[iJetAK8[0]].msoftdrop,AK8_Ht,w);

			if (apply_all_cuts_except('P', "HLT"))	h_AK8HT_MET_AK8JetMass_TrigNoMass_0->Fill(data.FatJet[iJetAK8[0]].msoftdrop,MET,AK8_Ht,w);
			if (apply_all_cuts('P'))			h_AK8HT_MET_AK8JetMass_TrigNoMass_1->Fill(data.FatJet[iJetAK8[0]].msoftdrop,MET,AK8_Ht,w);

			if (apply_all_cuts_except('P', "HLT") && data.FatJet[iJetAK8[0]].msoftdrop > 65.)	h_HT_TrigMass_0->Fill(AK4_Ht,w);
			if (apply_all_cuts('P') && data.FatJet[iJetAK8[0]].msoftdrop > 65.)			h_HT_TrigMass_1->Fill(AK4_Ht,w);

			if (apply_all_cuts_except('P', "HLT") && data.FatJet[iJetAK8[0]].msoftdrop > 65.)	h_AK8HT_TrigMass_0->Fill(AK8_Ht,w);
			if (apply_all_cuts('P') && data.FatJet[iJetAK8[0]].msoftdrop > 65.)			h_AK8HT_TrigMass_1->Fill(AK8_Ht,w);

			if (apply_all_cuts_except('P', "HLT") && data.FatJet[iJetAK8[0]].msoftdrop > 65.)	h_AK8JetpT_TrigMass_0->Fill(data.FatJet[iJetAK8[0]].pt,w);
			if (apply_all_cuts('P') && data.FatJet[iJetAK8[0]].msoftdrop > 65.)			h_AK8JetpT_TrigMass_1->Fill(data.FatJet[iJetAK8[0]].pt,w);

			if (apply_all_cuts_except('P', "HLT") && data.FatJet[iJetAK8[0]].msoftdrop > 65.)	h_AK8JetMass_TrigMass_0->Fill(data.FatJet[iJetAK8[0]].msoftdrop,w);
			if (apply_all_cuts('P') && data.FatJet[iJetAK8[0]].msoftdrop > 65.)			h_AK8JetMass_TrigMass_1->Fill(data.FatJet[iJetAK8[0]].msoftdrop,w);

			if (apply_all_cuts_except('P', "HLT") && data.FatJet[iJetAK8[0]].msoftdrop > 65.)	h_MET_TrigMass_0->Fill(MET,w);
			if (apply_all_cuts('P') && data.FatJet[iJetAK8[0]].msoftdrop > 65.)			h_MET_TrigMass_1->Fill(MET,w);

			if (apply_all_cuts_except('P', "HLT") && data.FatJet[iJetAK8[0]].msoftdrop > 65.)	h_MR_TrigMass_0->Fill(MR,w);
			if (apply_all_cuts('P') && data.FatJet[iJetAK8[0]].msoftdrop > 65.)			h_MR_TrigMass_1->Fill(MR,w);

			if (apply_all_cuts_except('P', "HLT") && data.FatJet[iJetAK8[0]].msoftdrop > 65.)	h_R2_TrigMass_0->Fill(R2,w);
			if (apply_all_cuts('P') && data.FatJet[iJetAK8[0]].msoftdrop > 65.)			h_R2_TrigMass_1->Fill(R2,w);

			if (apply_all_cuts_except('P', "HLT") && data.FatJet[iJetAK8[0]].msoftdrop > 65.)	h_R2_MR_TrigMass_0->Fill(MR,R2,w);
			if (apply_all_cuts('P') && data.FatJet[iJetAK8[0]].msoftdrop > 65.)			h_R2_MR_TrigMass_1->Fill(MR,R2,w);

			if (apply_all_cuts_except('P', "HLT") && data.FatJet[iJetAK8[0]].msoftdrop > 65.)	h_HT_MET_TrigMass_0->Fill(MET,AK4_Ht,w);
			if (apply_all_cuts('P') && data.FatJet[iJetAK8[0]].msoftdrop > 65.)			h_HT_MET_TrigMass_1->Fill(MET,AK4_Ht,w);

			if (apply_all_cuts_except('P', "HLT") && data.FatJet[iJetAK8[0]].msoftdrop > 65.)	h_HT_AK8JetMass_TrigMass_0->Fill(data.FatJet[iJetAK8[0]].msoftdrop,AK4_Ht,w);
			if (apply_all_cuts('P') && data.FatJet[iJetAK8[0]].msoftdrop > 65.)			h_HT_AK8JetMass_TrigMass_1->Fill(data.FatJet[iJetAK8[0]].msoftdrop,AK4_Ht,w);

			if (apply_all_cuts_except('P', "HLT") && data.FatJet[iJetAK8[0]].msoftdrop > 65.)	h_AK8HT_MET_TrigMass_0->Fill(MET,AK8_Ht,w);
			if (apply_all_cuts('P') && data.FatJet[iJetAK8[0]].msoftdrop > 65.)			h_AK8HT_MET_TrigMass_1->Fill(MET,AK8_Ht,w);

			if (apply_all_cuts_except('P', "HLT") && data.FatJet[iJetAK8[0]].msoftdrop > 65.)	h_AK8HT_AK8JetMass_TrigMass_0->Fill(data.FatJet[iJetAK8[0]].msoftdrop,AK8_Ht,w);
			if (apply_all_cuts('P') && data.FatJet[iJetAK8[0]].msoftdrop > 65.)			h_AK8HT_AK8JetMass_TrigMass_1->Fill(data.FatJet[iJetAK8[0]].msoftdrop,AK8_Ht,w);

			if (apply_all_cuts_except('P', "HLT") && data.FatJet[iJetAK8[0]].msoftdrop > 65.)	h_MET_AK8JetMass_TrigMass_0->Fill(data.FatJet[iJetAK8[0]].msoftdrop,MET,w);
			if (apply_all_cuts('P') && data.FatJet[iJetAK8[0]].msoftdrop > 65.)			h_MET_AK8JetMass_TrigMass_1->Fill(data.FatJet[iJetAK8[0]].msoftdrop,MET,w);

			if (apply_all_cuts_except('P', "HLT") && data.FatJet[iJetAK8[0]].msoftdrop > 65.)	h_HT_MET_AK8JetMass_TrigMass_0->Fill(data.FatJet[iJetAK8[0]].msoftdrop,MET,AK4_Ht,w);
			if (apply_all_cuts('P') && data.FatJet[iJetAK8[0]].msoftdrop > 65.)			h_HT_MET_AK8JetMass_TrigMass_1->Fill(data.FatJet[iJetAK8[0]].msoftdrop,MET,AK4_Ht,w);

			if (apply_all_cuts_except('P', "HLT") && data.FatJet[iJetAK8[0]].msoftdrop > 65.)	h_AK8HT_MET_AK8JetMass_TrigMass_0->Fill(data.FatJet[iJetAK8[0]].msoftdrop,MET,AK8_Ht,w);
			if (apply_all_cuts('P') && data.FatJet[iJetAK8[0]].msoftdrop > 65.)			h_AK8HT_MET_AK8JetMass_TrigMass_1->Fill(data.FatJet[iJetAK8[0]].msoftdrop,MET,AK8_Ht,w);
		}

		if (isData) {
			// All photon counts in G (data.ta)
			if (apply_all_cuts('G')) {
				bool EB = data.Photon[0].isScEtaEB;
				if (EB) h_R2_MR_G_EB->Fill(MR_pho, R2_pho);
				else    h_R2_MR_G_EE->Fill(MR_pho, R2_pho);
				if (nJetNoPho>=4) {
					if (nJetNoPho<6) {
						if (EB) h_R2_MR_G_EB_nj45->Fill(MR_pho, R2_pho);
						else    h_R2_MR_G_EE_nj45->Fill(MR_pho, R2_pho);
					} else {
						if (EB) h_R2_MR_G_EB_nj6->Fill(MR_pho, R2_pho);
						else    h_R2_MR_G_EE_nj6->Fill(MR_pho, R2_pho);
					}
				}
			}
			// Fake photon templates
			if (apply_all_cuts_except('g',"1Pho")) {
				if (nPhotonFake==1) {
					bool EB = data.Photon[iPhotonFake[0]].isScEtaEB;
					if (EB){ 
						h_ChIsoTemplate_Fake_g_EB->Fill(MR_pho, R2_pho, data.Photon[iPhotonFake[0]].pfRelIso03_chg, sf_weight['g']);
						h_ChIsoTemplate_Fake_g_MR_EB->Fill(MR_pho, data.Photon[iPhotonFake[0]].pfRelIso03_chg, sf_weight['g']);
						h_ChIsoTemplate_Fake_g_R2_EB->Fill(R2_pho, data.Photon[iPhotonFake[0]].pfRelIso03_chg, sf_weight['g']);
					}
					else   {
						h_ChIsoTemplate_Fake_g_EE->Fill(MR_pho, R2_pho, data.Photon[iPhotonFake[0]].pfRelIso03_chg, sf_weight['g']);
						h_ChIsoTemplate_Fake_g_MR_EE->Fill(MR_pho, data.Photon[iPhotonFake[0]].pfRelIso03_chg, sf_weight['g']);
						h_ChIsoTemplate_Fake_g_R2_EE->Fill(R2_pho, data.Photon[iPhotonFake[0]].pfRelIso03_chg, sf_weight['g']);
					}
				}
			}
		} else if (isBackground) {
			// Prompt photon templates
			if (apply_all_cuts_except('g',"1Pho")) {
				if (nPhotonPreSelect==1) {
					if (data.Photon[iPhotonPreSelect[0]].sieie < (data.Photon[iPhotonPreSelect[0]].isScEtaEB ? 0.01015 : 0.0272)) {
						bool EB = data.Photon[iPhotonPreSelect[0]].isScEtaEB;
						if (nDirectPromptPhoton>=1||nFragmentationPromptPhoton>=1) {
							if (EB){
								h_ChIsoTemplate_Prompt_g_EB->Fill(MR_pho, R2_pho, data.Photon[iPhotonPreSelect[0]].pfRelIso03_chg, sf_weight['g']);
								h_ChIsoTemplate_Prompt_g_MR_EB->Fill(MR_pho, data.Photon[iPhotonPreSelect[0]].pfRelIso03_chg, sf_weight['g']);
								h_ChIsoTemplate_Prompt_g_R2_EB->Fill(R2_pho, data.Photon[iPhotonPreSelect[0]].pfRelIso03_chg, sf_weight['g']);
							}
							else   {
								h_ChIsoTemplate_Prompt_g_EE->Fill(MR_pho, R2_pho, data.Photon[iPhotonPreSelect[0]].pfRelIso03_chg, sf_weight['g']);
								h_ChIsoTemplate_Prompt_g_MR_EE->Fill(MR_pho, data.Photon[iPhotonPreSelect[0]].pfRelIso03_chg, sf_weight['g']);
								h_ChIsoTemplate_Prompt_g_R2_EE->Fill(R2_pho, data.Photon[iPhotonPreSelect[0]].pfRelIso03_chg, sf_weight['g']);
							}
						} else {
							if (EB){
								h_ChIsoTemplate_Fake_g_EB_MC->Fill(MR_pho, R2_pho, data.Photon[iPhotonPreSelect[0]].pfRelIso03_chg, sf_weight['g']);
								h_ChIsoTemplate_Fake_g_MR_EB_MC->Fill(MR_pho, data.Photon[iPhotonPreSelect[0]].pfRelIso03_chg, sf_weight['g']);
								h_ChIsoTemplate_Fake_g_R2_EB_MC->Fill(R2_pho, data.Photon[iPhotonPreSelect[0]].pfRelIso03_chg, sf_weight['g']);
							}
							else   {
								h_ChIsoTemplate_Fake_g_EE_MC->Fill(MR_pho, R2_pho, data.Photon[iPhotonPreSelect[0]].pfRelIso03_chg, sf_weight['g']);
								h_ChIsoTemplate_Fake_g_MR_EE_MC->Fill(MR_pho, data.Photon[iPhotonPreSelect[0]].pfRelIso03_chg, sf_weight['g']);
								h_ChIsoTemplate_Fake_g_R2_EE_MC->Fill(R2_pho, data.Photon[iPhotonPreSelect[0]].pfRelIso03_chg, sf_weight['g']);
							}
						}
					}
				}
			}
		}
		// Chargedata.Hadata.on Isolation data.stributions for Purity measurement
		if (isData) {
			if (apply_all_cuts_except('G',"1Pho")) {
				if (nPhotonPreSelect==1) {
					if (data.Photon[iPhotonPreSelect[0]].sieie < (data.Photon[iPhotonPreSelect[0]].isScEtaEB ? 0.01015 : 0.0272)) {
						// Select 1 photon with ChIso N-1 cuts
						bool EB = data.Photon[iPhotonPreSelect[0]].isScEtaEB;
						if (EB){
							h_R2_MR_ChIso_GNoIso_EB->Fill(MR_pho, R2_pho, data.Photon[iPhotonPreSelect[0]].pfRelIso03_chg);
							h_MR_ChIso_GNoIso_EB->Fill(MR_pho, data.Photon[iPhotonPreSelect[0]].pfRelIso03_chg);
							h_R2_ChIso_GNoIso_EB->Fill(R2_pho, data.Photon[iPhotonPreSelect[0]].pfRelIso03_chg);
						}
						else   {
							h_R2_MR_ChIso_GNoIso_EE->Fill(MR_pho, R2_pho, data.Photon[iPhotonPreSelect[0]].pfRelIso03_chg);
							h_MR_ChIso_GNoIso_EE->Fill(MR_pho, data.Photon[iPhotonPreSelect[0]].pfRelIso03_chg);
							h_R2_ChIso_GNoIso_EE->Fill(R2_pho, data.Photon[iPhotonPreSelect[0]].pfRelIso03_chg);
						}
						if (nJetNoPho>=4) {
							if (nJetNoPho<6) {
								if (EB){
									h_R2_MR_ChIso_GNoIso_EB_nj45->Fill(MR_pho, R2_pho, data.Photon[iPhotonPreSelect[0]].pfRelIso03_chg);
									h_MR_ChIso_GNoIso_EB_nj45->Fill(MR_pho, data.Photon[iPhotonPreSelect[0]].pfRelIso03_chg);
									h_R2_ChIso_GNoIso_EB_nj45->Fill(R2_pho, data.Photon[iPhotonPreSelect[0]].pfRelIso03_chg);
								}
								else   {
									h_R2_MR_ChIso_GNoIso_EE_nj45->Fill(MR_pho, R2_pho, data.Photon[iPhotonPreSelect[0]].pfRelIso03_chg);
									h_MR_ChIso_GNoIso_EE_nj45->Fill(MR_pho, data.Photon[iPhotonPreSelect[0]].pfRelIso03_chg);
									h_R2_ChIso_GNoIso_EE_nj45->Fill(R2_pho, data.Photon[iPhotonPreSelect[0]].pfRelIso03_chg);
								}
							} else {
								if (EB){
									h_R2_MR_ChIso_GNoIso_EB_nj6->Fill(MR_pho, R2_pho, data.Photon[iPhotonPreSelect[0]].pfRelIso03_chg);
									h_MR_ChIso_GNoIso_EB_nj6->Fill(MR_pho, data.Photon[iPhotonPreSelect[0]].pfRelIso03_chg);
									h_R2_ChIso_GNoIso_EB_nj6->Fill(R2_pho, data.Photon[iPhotonPreSelect[0]].pfRelIso03_chg);
								}
								else   {
									h_R2_MR_ChIso_GNoIso_EE_nj6->Fill(MR_pho, R2_pho, data.Photon[iPhotonPreSelect[0]].pfRelIso03_chg);
									h_MR_ChIso_GNoIso_EE_nj6->Fill(MR_pho, data.Photon[iPhotonPreSelect[0]].pfRelIso03_chg);
									h_R2_ChIso_GNoIso_EE_nj6->Fill(R2_pho, data.Photon[iPhotonPreSelect[0]].pfRelIso03_chg);
								}
							}
						}
					}
				}
			}
			// G-1 region
			if (apply_all_cuts_except('g',"1Pho")) {
				if (nPhotonPreSelect==1) {
					if (data.Photon[iPhotonPreSelect[0]].sieie < (data.Photon[iPhotonPreSelect[0]].isScEtaEB ? 0.01015 : 0.0272)) {
						// Select 1 photon with ChIso N-1 cuts
						bool EB = data.Photon[iPhotonPreSelect[0]].isScEtaEB;
						if (EB){
							h_R2_MR_ChIso_gNoIso_EB->Fill(MR_pho, R2_pho, data.Photon[iPhotonPreSelect[0]].pfRelIso03_chg);
							h_MR_ChIso_gNoIso_EB->Fill(MR_pho, data.Photon[iPhotonPreSelect[0]].pfRelIso03_chg);
							h_R2_ChIso_gNoIso_EB->Fill(R2_pho, data.Photon[iPhotonPreSelect[0]].pfRelIso03_chg);
						}
						else   {
							h_R2_MR_ChIso_gNoIso_EE->Fill(MR_pho, R2_pho, data.Photon[iPhotonPreSelect[0]].pfRelIso03_chg);
							h_MR_ChIso_gNoIso_EE->Fill(MR_pho, data.Photon[iPhotonPreSelect[0]].pfRelIso03_chg);
							h_R2_ChIso_gNoIso_EE->Fill(R2_pho, data.Photon[iPhotonPreSelect[0]].pfRelIso03_chg);
						}
						if (nJetNoPho>=4) {
							if (nJetNoPho<6) {
								if (EB){
									h_R2_MR_ChIso_gNoIso_EB_nj45->Fill(MR_pho, R2_pho, data.Photon[iPhotonPreSelect[0]].pfRelIso03_chg);
									h_MR_ChIso_gNoIso_EB_nj45->Fill(MR_pho, data.Photon[iPhotonPreSelect[0]].pfRelIso03_chg);
									h_R2_ChIso_gNoIso_EB_nj45->Fill(R2_pho, data.Photon[iPhotonPreSelect[0]].pfRelIso03_chg);
								}
								else   {
									h_R2_MR_ChIso_gNoIso_EE_nj45->Fill(MR_pho, R2_pho, data.Photon[iPhotonPreSelect[0]].pfRelIso03_chg);
									h_MR_ChIso_gNoIso_EE_nj45->Fill(MR_pho, data.Photon[iPhotonPreSelect[0]].pfRelIso03_chg);
									h_R2_ChIso_gNoIso_EE_nj45->Fill(R2_pho, data.Photon[iPhotonPreSelect[0]].pfRelIso03_chg);
								}
							} else {
								if (EB){
									h_R2_MR_ChIso_gNoIso_EB_nj6->Fill(MR_pho, R2_pho, data.Photon[iPhotonPreSelect[0]].pfRelIso03_chg);
									h_MR_ChIso_gNoIso_EB_nj6->Fill(MR_pho, data.Photon[iPhotonPreSelect[0]].pfRelIso03_chg);
									h_R2_ChIso_gNoIso_EB_nj6->Fill(R2_pho, data.Photon[iPhotonPreSelect[0]].pfRelIso03_chg);
								}
								else   {
									h_R2_MR_ChIso_gNoIso_EE_nj6->Fill(MR_pho, R2_pho, data.Photon[iPhotonPreSelect[0]].pfRelIso03_chg);
									h_MR_ChIso_gNoIso_EE_nj6->Fill(MR_pho, data.Photon[iPhotonPreSelect[0]].pfRelIso03_chg);
									h_R2_ChIso_gNoIso_EE_nj6->Fill(R2_pho, data.Photon[iPhotonPreSelect[0]].pfRelIso03_chg);
								}
							}
						}
					}
				}
			}
		} else if (isBackground) {
			// Direct photon ratio from MC
			if (apply_all_cuts('G')) {
				//stdata.:cout<<"Pass G: "<<MR_pho<<" "<<R2_pho<<" "<<data.evt.RunNumber<<" "<<data.evt.LumiBlock<<" "<<data.evt.EventNumber<<stdata.:endata.;
				bool EB = data.Photon[iPhotonSelect[0]].isScEtaEB;
				bool isPrompt = nDirectPromptPhoton>=1||nFragmentationPromptPhoton>=1;
				bool isPromptDirect = nDirectPromptPhoton>=1;
				// Prompt photon fraction
				if (EB) h_R2_MR_IsPrompt_G_EB->Fill(MR_pho, R2_pho, isPrompt, sf_weight['G']);
				else    h_R2_MR_IsPrompt_G_EE->Fill(MR_pho, R2_pho, isPrompt, sf_weight['G']);
				// Direct photon fraction of prompt photons
				if (isPrompt) {
					if (EB){
						h_R2_MR_IsDirect_G_EB->Fill(MR_pho, R2_pho, isPromptDirect, sf_weight['G']);
						h_MR_IsDirect_G_EB->Fill(MR_pho, isPromptDirect, sf_weight['G']);
						h_R2_IsDirect_G_EB->Fill(R2_pho, isPromptDirect, sf_weight['G']);
					}
					else   {
						h_R2_MR_IsDirect_G_EE->Fill(MR_pho, R2_pho, isPromptDirect, sf_weight['G']);
						h_MR_IsDirect_G_EE->Fill(MR_pho, isPromptDirect, sf_weight['G']);
						h_R2_IsDirect_G_EE->Fill(R2_pho, isPromptDirect, sf_weight['G']);
					}
				}
				// Prompt data.rect photons in G control region
				if (isPromptDirect==1) {
					h_R2_MR_G_DirectPrompt->Fill(MR_pho, R2_pho, sf_weight['G']);
					if (nJetNoPho>=4) {
						if (nJetNoPho<6) h_R2_MR_G_DirectPrompt_nj45->Fill(MR_pho, R2_pho, sf_weight['G']);
						else             h_R2_MR_G_DirectPrompt_nj6 ->Fill(MR_pho, R2_pho, sf_weight['G']);
					}
				}
			}
		}

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

	/*
		 h_njet_pre[syst_index]->Fill(nJet,        w);
		 h_nb_pre[syst_index]->Fill(nMediumBTag, w);
		 h_nw_pre[syst_index]->Fill(nBoostMassTag,  w);
		 h_j1_pt_pre[syst_index]->Fill(data.FatJet[iJetAK8[0]].pt,w);
		 h_j2_pt_pre[syst_index]->Fill(data.Jet[iJet[1]].pt, w);
		 h_j3_pt_pre[syst_index]->Fill(data.Jet[iJet[2]].pt, w);
		 h_MR_pre[syst_index]->Fill(MR, w);
		 h_R2_pre[syst_index]->Fill(R2, w);
		 h_tau21_pre[syst_index]->Fill(tau21.at(iJetAK8[0]),w);
		 h_MET_pre[syst_index]->Fill(data.MET_pt,w);
		 h_HT_pre[syst_index]->Fill(AK4_Ht,w);
		 h_HT_j1pt_pre[syst_index]->Fill(AK4_Ht,data.FatJet[iJetAK8[0]].pt,w);

*/

	// Vary systematics and save each variation into a different historgam
	// Switch on settings.varySystematics to be effective
	//if (apply_all_cuts('S')) vh_jet1_pt[syst_index]->Fill(data.Jet[iJet[0]].pt, w);

	w = sf_weight['S'];
	if (apply_all_cuts('S')) {
		if(nJet>=4 && nJet<6) vh_R2_MR_S_nj45[syst_index]->Fill(MR, R2, w);
		if(nJet>=6)						vh_R2_MR_S_nj6[syst_index]->Fill(MR, R2, w);
	}
	w = sf_weight['s'];
	if (apply_all_cuts('s')) {
		if(nJet>=4 && nJet<6) vh_R2_MR_s_nj45[syst_index]->Fill(MR, R2, w);
		if(nJet>=6)						vh_R2_MR_s_nj6[syst_index]->Fill(MR, R2, w);
	}
	w = sf_weight['Q'];
	if (apply_all_cuts('Q')) {
		if(nJet>=4 && nJet<6) vh_R2_MR_Q_nj45[syst_index]->Fill(MR, R2, w);
		if(nJet>=6)						vh_R2_MR_Q_nj6[syst_index]->Fill(MR, R2, w);
	}
	w = sf_weight['q'];
	if (apply_all_cuts('q')) {
		if(nJet>=4 && nJet<6) vh_R2_MR_q_nj45[syst_index]->Fill(MR, R2, w);
		if(nJet>=6)						vh_R2_MR_q_nj6[syst_index]->Fill(MR, R2, w);
	}
	w = sf_weight['T'];
	if (apply_all_cuts('T')) {
		if(nJet>=4 && nJet<6) vh_R2_MR_T_nj45[syst_index]->Fill(MR, R2, w);
		if(nJet>=6)						vh_R2_MR_T_nj6[syst_index]->Fill(MR, R2, w);
	}
	w = sf_weight['W'];
	if (apply_all_cuts('W')) {
		if(nJet>=4 && nJet<6) vh_R2_MR_W_nj45[syst_index]->Fill(MR, R2, w);
		if(nJet>=6)						vh_R2_MR_W_nj6[syst_index]->Fill(MR, R2, w);
	}
	w = sf_weight['Z'];
	if (apply_all_cuts('Z')) {
		if(nJet>=4 && nJet<6) vh_R2_MR_Z_nj45[syst_index]->Fill(MR, R2, w);
		if(nJet>=6)						vh_R2_MR_Z_nj6[syst_index]->Fill(MR, R2, w);
	}
	w = sf_weight['G'];
	if (apply_all_cuts('G')) {
		if(nJet>=4 && nJet<6) vh_R2_MR_G_nj45[syst_index]->Fill(MR, R2, w);
		if(nJet>=6)						vh_R2_MR_G_nj6[syst_index]->Fill(MR, R2, w);
	}
	w = sf_weight['L'];
	if (apply_all_cuts('L')) {
		if(nJet>=4 && nJet<6) vh_R2_MR_L_nj45[syst_index]->Fill(MR, R2, w);
		if(nJet>=6)						vh_R2_MR_L_nj6[syst_index]->Fill(MR, R2, w);
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
