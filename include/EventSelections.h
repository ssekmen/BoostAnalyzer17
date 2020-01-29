#ifndef EVENTSELECTIONS_H
#define EVENTSELECTIONS_H

// Private headers
#include "Variables.h"
#include "Weighting.h"

// 3rd party headers
#include "tnm.h"
#include "magic_enum.h"
#include "TString.h"

// common libraries
#include <iostream>
#include <functional>
#include <map>
#include <vector>

class EventSelections
{
public:
  EventSelections(Variables& var) :
    v(var) {}
  ~EventSelections() {}

  typedef struct Cut { std::string name; std::function<bool()> func; } Cut;
  std::vector<Cut> baseline_cuts;

  void define_preselections();
  
  void define_event_selections();

  enum Regions : size_t {
    // Preection regions
    Pre,
      Pre_Had,
      Pre_Lep,
      Pre_NonIso,
    
    // Control regions
      CR_QCD16_W,     // Previously Q
      CR_Top16_W,     // Previously T
      CR_W16_W,       // Previously W
      CR_QCD16_Top,     // Previously Q
      CR_Top16_Top,     // Previously T
      CR_W16_Top,       // Previously W
      CR_QCD16_Z,     // Previously Q
      CR_Top16_Z,     // Previously T
      CR_W16_Z,       // Previously W
      CR_QCD16_V,     // Previously Q
      CR_Top16_V,     // Previously T
      CR_W16_V,       // Previously W
      CR_QCD17_1Boost,     // Previously Q
      CR_Top17_1Boost,     // Previously T
      CR_W17_1Boost,       // Previously W
      CR_QCD17_2Boost,     // Previously Q
      CR_Top17_2Boost,     // Previously T
      CR_W17_2Boost,       // Previously W
      CR_1LepInv, // Previously L
      CR_2LepInv, // Previously Z
      CR_1PhoInv, // Previously G
      CR_Fake,    // Previously F
      // Validation regions
      Val_Signal,      // Previously S'
      Val_QCD,         // Previously Q'
      
    // Fully hadronic signal regions
      SR_Had_1htop,
      SR_Had_2htop,
      SR_Had_V_b_45j,
      SR_Had_V_b_6j,
      SR_Had_1V_0b_34j,
      SR_Had_1V_0b_5j,
      SR_Had_2V_0b_24j,
      SR_Had_2V_0b_5j,
      SR_Had_H_b_45j,
      SR_Had_H_b_6j,
      SR_Had_2H_b_6j,
      SR_Had_HV_b_6j,
      SR_Had_1H_0b_34j,
      SR_Had_1H_0b_5j,
      SR_Had_2H_0b_34j,
      SR_Had_2H_0b_5j,
      SR_Had_HV_0b_24j,
      SR_Had_HV_0b_5j,
      
    // Isolated lepton signal regions
      SR_Lep_1htop,
      SR_Lep_V_b,
      SR_Lep_V_0b,
      SR_Lep_H_b,
      SR_Lep_H_0b,
      
    // Non-isolated lepton signal regions
      SR_Leptop_0htop,
      SR_Leptop_1htop,
      SR_Lepjet_0V_24j,
      SR_Lepjet_0V_5j,
      SR_Lepjet_1V_24j,
      SR_Lepjet_1V_5j,
      };
  typedef Regions Region;

  void define_region(Region, Region, std::vector<Cut>);

  std::vector<std::vector<Cut> > analysis_cuts;
  std::vector<bool> pass_all_cuts;
  std::vector<unsigned int> cutbits;

  bool apply_cut(Region, std::string);
  bool apply_cut(Region, unsigned int);
  bool apply_ncut(Region, std::string);
  bool apply_ncut(Region, unsigned int);
  bool apply_cuts(Region, std::vector<std::string>);
  bool apply_cuts(Region, std::vector<unsigned int>);
  bool apply_all_cuts(Region);
  bool apply_all_cuts_except(Region, std::string);
  bool apply_all_cuts_except(Region, unsigned int);
  bool apply_all_cuts_except(Region, std::vector<std::string>);
  bool apply_all_cuts_except(Region, std::vector<unsigned int>);

  bool pass_skimming();

  void apply_event_selections();

private:

  Variables& v;  
  
};




//_______________________________________________________
//  Apply analysis cuts in the specified search region

bool
EventSelections::apply_all_cuts(Region region) {
  return apply_ncut(region, analysis_cuts[region].size());
}

bool
EventSelections::apply_ncut(Region region, unsigned int ncut) {
  if (ncut>analysis_cuts[region].size()) return 0;
  for (unsigned int i=0; i<ncut; ++i) if ( ! analysis_cuts[region][i].func() ) return 0;
  return 1;
}

// Cuts to apply/exclude by cut name
bool
EventSelections::apply_cut(Region region, std::string cut_name) {
  for (const auto& cut : analysis_cuts[region]) if (cut_name == cut.name) return cut.func();
  return 0;
}

bool
EventSelections::apply_cuts(Region region, std::vector<std::string> cuts) {
  for (const auto& cut_in_region : analysis_cuts[region]) for (const auto& cut : cuts)
    if (cut == cut_in_region.name) if (!cut_in_region.func()) return 0;
  return 1;
}

bool
EventSelections::apply_all_cuts_except(Region region, std::string cut_to_skip) {
  bool result = true, found = false;
  for (const auto& cut : analysis_cuts[region]) {
    if (cut.name == cut_to_skip) {
      found = true;
      continue;
    }
    if (!cut.func()) result = false;
  }
  // If a certain cut meant to be skipped (N-1) is not found for some reason
  // eg. mistyped, then end the job with ar error
  // This is for safety: We do not want to fill histograms wrongly by mistake
  if (!found) {
    std::cout<<"No cut to be skipped exsists in search region \""<<magic_enum::enum_name(region)<<"\" with name: \""<<cut_to_skip<<"\""<<std::endl;
    error("EventSelections - the second argument for apply_all_cuts_except() is a non-sensical cut");
  }
  return result;
}

bool
EventSelections::apply_all_cuts_except(Region region, std::vector<std::string> cuts_to_skip) {
  bool result = true;
  unsigned int found = 0;
  for (const auto& cut : analysis_cuts[region]) {
    for (const auto& cut_to_skip : cuts_to_skip) if (cut.name==cut_to_skip) {
      ++found;
      continue;
    }
    if (!cut.func()) result = false;
  }
  // If a certain cut meant to be skipped is not found for some reason
  // eg. mistyped, then end the job with ar error
  // This is for safety: We do not want to fill histograms wrongly by mistake
  if (found!=cuts_to_skip.size()) {
    std::cout<<"A cut to be skipped does not exsist in seaerch region \""<<magic_enum::enum_name(region)<<"\" with names: ";
    for (const auto& cut : cuts_to_skip) std::cout<<cut<<", "; std::cout<<std::endl;
    error("EventSelections - the second argument for apply_all_cuts_except() contains at least one non-sensical cut");
  }
  return result;
}


// Same functions but with cut index which is faster (can use an enum, to make it nicer)
bool
EventSelections::apply_cut(Region region, unsigned int cut_index) { return analysis_cuts[region][cut_index].func(); }

bool
EventSelections::apply_cuts(Region region, std::vector<unsigned int> cuts) {
  for (const unsigned int& cut : cuts) if ( ! analysis_cuts[region][cut].func() ) return 0;
  return 1;
}

bool
EventSelections::apply_all_cuts_except(Region region, unsigned int cut_to_skip) {
  if (cut_to_skip>=analysis_cuts[region].size()) {
    std::cout<<"Index ("<<cut_to_skip<<") is too high for the cut to be skipped in search region '"<<magic_enum::enum_name(region)<<"'"<<std::endl;
    error("EventSelections::apply_all_cuts_except(Region region, unsigned int cut_to_skip)");
  }
  for (unsigned int i=0, n=analysis_cuts[region].size(); i<n; ++i) {
    if (i==cut_to_skip) continue;
    if ( ! analysis_cuts[region][i].func() ) return 0;
  }
  return 1;
}

bool
EventSelections::apply_all_cuts_except(Region region, std::vector<unsigned int> cuts_to_skip) {
  for (unsigned int i=0, n=analysis_cuts[region].size(); i<n; ++i) {
    for (const unsigned int& cut_to_skip : cuts_to_skip) if (i!=cut_to_skip)
      if ( ! analysis_cuts[region][i].func() ) return 0;
  }
  return 1;
}

void
EventSelections::apply_event_selections()
{
  // Calculate decision of each individual cut
  for (size_t i=0, n=analysis_cuts.size(); i<n; ++i) {
    cutbits[i] = 0;
    for (size_t j=0, m=analysis_cuts[i].size(); j<m; ++j)
      if (analysis_cuts[i][j].func()) cutbits[i] += 1<<j;
    pass_all_cuts[i] = (cutbits[i]==(unsigned int)((1<<analysis_cuts[i].size())-1));
  }
}
//_______________________________________________________
//                Define Skimming cuts
//      Needed, if you want to skim the ntuple

bool
EventSelections::pass_skimming()
{
  return 1;
}



//_______________________________________________________
//              Define event cleaning cuts
void
EventSelections::define_preselections()
{
  baseline_cuts.clear();

  // Apply the same cuts as it is in the ntuple - Only for check
  // cut is an std::function, which we can define easily with a lambda function

  // Recommended event filters by MET group - Updated to 80X Recommendations
  // https://twiki.cern.ch/twiki/bin/view/CMS/MissingETOptionalFiltersRun2?rev=101#Analysis_Recommendations_for_ana
  //
  // Select at least one good vertex (|z|<24, |rho|<2, ndof>=4)
  // NGoodVtx defined in:
  // https://github.com/jkarancs/B2GTTrees/blob/v8.0.x_v2.1_Oct24/plugins/B2GEdmExtraVarProducer.cc#L528-L531
  // baseline_cuts.push_back({ .name="met_filter_NGoodVtx",          .func = [this] { return data.evt.NGoodVtx>0; } });
  baseline_cuts.push_back({ .name="Clean_goodVertices",      .func = [this] { return v.Flag_goodVertices; } });

  // Other filters (in 80X MiniAODv2)
  // https://twiki.cern.ch/twiki/bin/view/CMS/MissingETOptionalFiltersRun2?rev=101#What_is_available_in_MiniAOD
  baseline_cuts.push_back({ .name="Clean_CSC_Halo_SuperTight",    .func = [this] { return v.isSignal ? 1 : v.Flag_globalSuperTightHalo2016Filter; } });
  baseline_cuts.push_back({ .name="Clean_HBHE_Noise",        .func = [this] { return v.Flag_HBHENoiseFilter; } });
  baseline_cuts.push_back({ .name="Clean_HBHE_IsoNoise",     .func = [this] { return v.Flag_HBHENoiseIsoFilter; } });
  baseline_cuts.push_back({ .name="Clean_Ecal_Dead_Cell_TP", .func = [this] { return v.Flag_EcalDeadCellTriggerPrimitiveFilter; } });
  baseline_cuts.push_back({ .name="Clean_EE_Bad_Sc",         .func = [this] { return v.isData ? v.Flag_eeBadScFilter : 1; } });
  // Not in MiniAODv2 (producer added)
  baseline_cuts.push_back({ .name="Clean_Bad_Muon",          .func = [this] { return v.Flag_BadPFMuonFilter; } });
  //baseline_cuts.push_back({ .name="Clean_Bad_Charged",       .func = [this] { return v.Flag_BadChargedCandidateFilter; } });
}

//_______________________________________________________
//          Define Analysis event selection cuts
//     Can define all sorts of Signal/Control regions

void
EventSelections::define_region(Region region, Region presel, std::vector<Cut> cuts) {
  for (const auto& presel_cut : analysis_cuts[presel])
    analysis_cuts[region].push_back(presel_cut);
  for (const auto& cut : cuts)
    analysis_cuts[region].push_back(cut);
}

void
EventSelections::define_event_selections()
{
  analysis_cuts.clear();
  analysis_cuts.resize(magic_enum::enum_count<Region>());
  pass_all_cuts.resize(magic_enum::enum_count<Region>());
  cutbits      .resize(magic_enum::enum_count<Region>());

  // Define here cuts that are include in all Signal/Control regions
  // MET Filters, etc. are already applied with baseline_cuts

  std::function<bool()> boost_triggers;
  if (v.sample.Contains("JetHT")) {
    boost_triggers = [this] { return v.isData ? v.HLT_PFHT1050==1  : 1; };
  } else if (v.sample.Contains("MET")) {
    boost_triggers = [this] { return v.isData ? 
                                 !(v.HLT_PFHT1050==1) && 
                                 ( 
                                  //v.HLT_PFMET120_PFMHT120_IDTight==1 ||
                                  //v.HLT_PFMETNoMu120_PFMHTNoMu120_IDTight==1 ||
                                  //v.HLT_PFMETTypeOne120_PFMHT120_IDTight==1 ||
                                  v.HLT_PFHT500_PFMET100_PFMHT100_IDTight==1 || 
                                  v.HLT_PFHT700_PFMET85_PFMHT85_IDTight==1 ||
                                  v.HLT_PFHT800_PFMET75_PFMHT75_IDTight==1 
                                  ) : 1; };
  } else {
    // Data histos should not contain events from other datasets
    boost_triggers = [this] { return v.isData ? 0 : 1; }; 
  }

  // Preselection regions
  analysis_cuts[Region::Pre] = {
    { .name="1JetAK8",    .func = [this] { return v.FatJet.JetAK8.n>=1;        }},
    { .name="NJetPre",    .func = [this] { return v.Jet.Jet.n>=2;              }},
    { .name="MR",         .func = [this] { return v.MR>=800;                   }},
    { .name="R2",         .func = [this] { return v.R2>=0.08;                  }},
    { .name="HLT",        .func =                boost_triggers                 },
  };
  define_region(Region::Pre_Had, Region::Pre, {
    { .name="0IsoEle",    .func = [this] { return v.Electron.Veto.n==0;        }},
    { .name="0IsoMu",     .func = [this] { return v.Muon.Veto.n==0;            }},
    { .name="0IsoTau",    .func = [this] { return v.Tau.Veto.n==0;             }},
    { .name="0LepJet",    .func = [this] { return v.FatJet.LepJet.n==0;        }},
    { .name="0LepTop",    .func = [this] { return v.FatJet.LepTop.n==0;        }},
    { .name="dPhi",       .func = [this] { return v.dPhiRazor<2.8;             }},
  });
  define_region(Region::Pre_Lep, Region::Pre, {
    { .name="1Lep",       .func = [this] { return v.nLepSelect==1;             }},
    { .name="0LepJet",    .func = [this] { return v.FatJet.LepJet.n==0;        }},
    { .name="0LepTop",    .func = [this] { return v.FatJet.LepTop.n==0;        }},
    { .name="MT",         .func = [this] { return v.MT>=120;                   }},
  });
  define_region(Region::Pre_NonIso, Region::Pre, {
    { .name="1Lep",       .func = [this] { return v.nLepNonIso>=1;             }},
    { .name="MT",         .func = [this] { return v.MT_lepNonIso>=140;         }},
    { .name="dPhiJet",    .func = [this] { return v.dPhiBoostedJetLepMET>=0.8; }},
  });

  // QCD Multijet enriched control sample
  define_region(Region::CR_QCD16_W, Region::Pre, {
    { .name="0Ele",       .func = [this] { return v.Electron.Veto.n==0;             }},
    { .name="0Mu",        .func = [this] { return v.Muon.Veto.n==0;                 }},
    { .name="0Tau",       .func = [this] { return v.Tau.Veto.n==0;                  }},
    { .name="0b",         .func = [this] { return v.Jet.LooseBTag.n==0;             }},
    { .name="1M",         .func = [this] { return v.FatJet.WDeep1.n>=1;         }},
    { .name="InvdPhi",    .func = [this] { return v.dPhiRazor>=2.8;                 }},
  });

  // Top enriched control sample
  define_region(Region::CR_Top16_W, Region::Pre, {
    { .name="1Lep",       .func = [this] { return v.nLepVeto==1;                    }},
    { .name="1b",         .func = [this] { return v.Jet.MediumBTag.n>=1;            }},
    { .name="1M",         .func = [this] { return v.FatJet.WDeep1.n>=1;         }},
    { .name="dPhi",       .func = [this] { return v.dPhiRazor<2.8;                  }},
    { .name="MT",         .func = [this] { return v.MT_lepVeto<140;                 }},
  });

  // W enriched control sample
  define_region(Region::CR_W16_W, Region::Pre, {
    { .name="1Lep",       .func = [this] { return v.nLepVeto==1;                      }},
    { .name="0b",         .func = [this] { return v.Jet.LooseBTag.n==0;               }},
    { .name="1M",         .func = [this] { return v.FatJet.WDeep1.n>=1;           }},
    { .name="dPhi",       .func = [this] { return v.dPhiRazor<2.8;                    }},
    { .name="MT",         .func = [this] { return v.MT_lepVeto>=30&&v.MT_lepVeto<100; }},
  });

  // QCD Multijet enriched control sample
  define_region(Region::CR_QCD16_Top, Region::Pre, {
    { .name="0Ele",       .func = [this] { return v.Electron.Veto.n==0;             }},
    { .name="0Mu",        .func = [this] { return v.Muon.Veto.n==0;                 }},
    { .name="0Tau",       .func = [this] { return v.Tau.Veto.n==0;                  }},
    { .name="0b",         .func = [this] { return v.Jet.LooseBTag.n==0;             }},
    { .name="1M",         .func = [this] { return v.FatJet.TopDeep1.n>=1;         }},
    { .name="InvdPhi",    .func = [this] { return v.dPhiRazor>=2.8;                 }},
  });

  // Top enriched control sample
  define_region(Region::CR_Top16_Top, Region::Pre, {
    { .name="1Lep",       .func = [this] { return v.nLepVeto==1;                    }},
    { .name="1b",         .func = [this] { return v.Jet.MediumBTag.n>=1;            }},
    { .name="1M",         .func = [this] { return v.FatJet.TopDeep1.n>=1;         }},
    { .name="dPhi",       .func = [this] { return v.dPhiRazor<2.8;                  }},
    { .name="MT",         .func = [this] { return v.MT_lepVeto<140;                 }},
  });

  // W enriched control sample
  define_region(Region::CR_W16_Top, Region::Pre, {
    { .name="1Lep",       .func = [this] { return v.nLepVeto==1;                      }},
    { .name="0b",         .func = [this] { return v.Jet.LooseBTag.n==0;               }},
    { .name="1M",         .func = [this] { return v.FatJet.TopDeep1.n>=1;           }},
    { .name="dPhi",       .func = [this] { return v.dPhiRazor<2.8;                    }},
    { .name="MT",         .func = [this] { return v.MT_lepVeto>=30&&v.MT_lepVeto<100; }},
  });

  // QCD Multijet enriched control sample
  define_region(Region::CR_QCD16_Z, Region::Pre, {
    { .name="0Ele",       .func = [this] { return v.Electron.Veto.n==0;             }},
    { .name="0Mu",        .func = [this] { return v.Muon.Veto.n==0;                 }},
    { .name="0Tau",       .func = [this] { return v.Tau.Veto.n==0;                  }},
    { .name="0b",         .func = [this] { return v.Jet.LooseBTag.n==0;             }},
    { .name="1M",         .func = [this] { return v.FatJet.ZDeep1.n>=1;         }},
    { .name="InvdPhi",    .func = [this] { return v.dPhiRazor>=2.8;                 }},
  });

  // Top enriched control sample
  define_region(Region::CR_Top16_Z, Region::Pre, {
    { .name="1Lep",       .func = [this] { return v.nLepVeto==1;                    }},
    { .name="1b",         .func = [this] { return v.Jet.MediumBTag.n>=1;            }},
    { .name="1M",         .func = [this] { return v.FatJet.ZDeep1.n>=1;         }},
    { .name="dPhi",       .func = [this] { return v.dPhiRazor<2.8;                  }},
    { .name="MT",         .func = [this] { return v.MT_lepVeto<140;                 }},
  });

  // W enriched control sample
  define_region(Region::CR_W16_Z, Region::Pre, {
    { .name="1Lep",       .func = [this] { return v.nLepVeto==1;                      }},
    { .name="0b",         .func = [this] { return v.Jet.LooseBTag.n==0;               }},
    { .name="1M",         .func = [this] { return v.FatJet.ZDeep1.n>=1;           }},
    { .name="dPhi",       .func = [this] { return v.dPhiRazor<2.8;                    }},
    { .name="MT",         .func = [this] { return v.MT_lepVeto>=30&&v.MT_lepVeto<100; }},
  });

  // QCD Multijet enriched control sample
  define_region(Region::CR_QCD16_V, Region::Pre, {
    { .name="0Ele",       .func = [this] { return v.Electron.Veto.n==0;             }},
    { .name="0Mu",        .func = [this] { return v.Muon.Veto.n==0;                 }},
    { .name="0Tau",       .func = [this] { return v.Tau.Veto.n==0;                  }},
    { .name="0b",         .func = [this] { return v.Jet.LooseBTag.n==0;             }},
    { .name="1M",         .func = [this] { return v.FatJet.VDeep1.n>=1;         }},
    { .name="InvdPhi",    .func = [this] { return v.dPhiRazor>=2.8;                 }},
  });

  // Top enriched control sample
  define_region(Region::CR_Top16_V, Region::Pre, {
    { .name="1Lep",       .func = [this] { return v.nLepVeto==1;                    }},
    { .name="1b",         .func = [this] { return v.Jet.MediumBTag.n>=1;            }},
    { .name="1M",         .func = [this] { return v.FatJet.VDeep1.n>=1;         }},
    { .name="dPhi",       .func = [this] { return v.dPhiRazor<2.8;                  }},
    { .name="MT",         .func = [this] { return v.MT_lepVeto<140;                 }},
  });

  // W enriched control sample
  define_region(Region::CR_W16_V, Region::Pre, {
    { .name="1Lep",       .func = [this] { return v.nLepVeto==1;                      }},
    { .name="0b",         .func = [this] { return v.Jet.LooseBTag.n==0;               }},
    { .name="1M",         .func = [this] { return v.FatJet.VDeep1.n>=1;           }},
    { .name="dPhi",       .func = [this] { return v.dPhiRazor<2.8;                    }},
    { .name="MT",         .func = [this] { return v.MT_lepVeto>=30&&v.MT_lepVeto<100; }},
  });

  // QCD Multijet enriched control sample
  define_region(Region::CR_QCD17_1Boost, Region::Pre, {
    { .name="0Ele",       .func = [this] { return v.Electron.Veto.n==0;             }},
    { .name="0Mu",        .func = [this] { return v.Muon.Veto.n==0;                 }},
    { .name="0Tau",       .func = [this] { return v.Tau.Veto.n==0;                  }},
    //{ .name="0b",         .func = [this] { return v.Jet.LooseBTag.n==0;             }},
    { .name="1M",         .func = [this] { return v.FatJet.JetAK8Mass.n==1;         }},
    { .name="InvdPhi",    .func = [this] { return v.dPhiRazor>=2.8;                 }},
  });

  // Top enriched control sample
  define_region(Region::CR_Top17_1Boost, Region::Pre, {
    { .name="1Lep",       .func = [this] { return v.nLepVeto==1;                    }},
    { .name="1b",         .func = [this] { return v.Jet.MediumBTag.n>=1;            }},
    { .name="1M",         .func = [this] { return v.FatJet.JetAK8Mass.n==1;         }},
    { .name="dPhi",       .func = [this] { return v.dPhiRazor<2.8;                  }},
    { .name="MT",         .func = [this] { return v.MT_lepVeto<140;                 }},
  });

  // W enriched control sample
  define_region(Region::CR_W17_1Boost, Region::Pre, {
    { .name="1Lep",       .func = [this] { return v.nLepVeto==1;                      }},
    { .name="0b",         .func = [this] { return v.Jet.LooseBTag.n==0;               }},
    { .name="1M",         .func = [this] { return v.FatJet.JetAK8Mass.n==1;           }},
    { .name="dPhi",       .func = [this] { return v.dPhiRazor<2.8;                    }},
    { .name="MT",         .func = [this] { return v.MT_lepVeto>=30&&v.MT_lepVeto<100; }},
  });

  // QCD Multijet enriched control sample
  define_region(Region::CR_QCD17_2Boost, Region::Pre, {
    { .name="0Ele",       .func = [this] { return v.Electron.Veto.n==0;             }},
    { .name="0Mu",        .func = [this] { return v.Muon.Veto.n==0;                 }},
    { .name="0Tau",       .func = [this] { return v.Tau.Veto.n==0;                  }},
    //{ .name="0b",         .func = [this] { return v.Jet.LooseBTag.n==0;             }},
    { .name="1M",         .func = [this] { return v.FatJet.JetAK8Mass.n>1;         }},
    { .name="InvdPhi",    .func = [this] { return v.dPhiRazor>=2.8;                 }},
  });

  // Top enriched control sample
  define_region(Region::CR_Top17_2Boost, Region::Pre, {
    { .name="1Lep",       .func = [this] { return v.nLepVeto==1;                    }},
    { .name="1b",         .func = [this] { return v.Jet.MediumBTag.n>=1;            }},
    { .name="1M",         .func = [this] { return v.FatJet.JetAK8Mass.n>1;         }},
    { .name="dPhi",       .func = [this] { return v.dPhiRazor<2.8;                  }},
    { .name="MT",         .func = [this] { return v.MT_lepVeto<140;                 }},
  });

  // W enriched control sample
  define_region(Region::CR_W17_2Boost, Region::Pre, {
    { .name="1Lep",       .func = [this] { return v.nLepVeto==1;                      }},
    { .name="0b",         .func = [this] { return v.Jet.LooseBTag.n==0;               }},
    { .name="1M",         .func = [this] { return v.FatJet.JetAK8Mass.n>1;           }},
    { .name="dPhi",       .func = [this] { return v.dPhiRazor<2.8;                    }},
    { .name="MT",         .func = [this] { return v.MT_lepVeto>=30&&v.MT_lepVeto<100; }},
  });

  // 1-lepton invisible control sample with veto lepton
  analysis_cuts[Region::CR_1LepInv] = {
    { .name="1JetAK8",    .func = [this] { return v.FatJet.JetAK8.n>=1;               }},
    { .name="NJet",       .func = [this] { return v.Jet.Jet.n>=2;                     }},
    { .name="MR",         .func = [this] { return v.MR>=800;                          }},
    { .name="R2",         .func = [this] { return v.R2_1vl>=0.08;                     }},
    { .name="HLT",        .func =                boost_triggers                        },
    { .name="0b",         .func = [this] { return v.Jet.LooseBTag.n==0;               }},
    { .name="1Lep",       .func = [this] { return v.nLepVeto==1;                      }},
    { .name="1M",         .func = [this] { return v.FatJet.JetAK8Mass.n>=1;           }},
    { .name="dPhi",       .func = [this] { return v.dPhiRazor<2.8;                    }},
    { .name="MT",         .func = [this] { return v.MT_lepVeto>=30&&v.MT_lepVeto<100; }},
  };

  // 2-lepton invisible (Z->ll enriched) control sample
  analysis_cuts[Region::CR_2LepInv] = {
    { .name="1JetAK8",    .func = [this] { return v.FatJet.JetAK8.n>=1;                }},
    { .name="NJet",       .func = [this] { return v.Jet.Jet.n>=2;                      }},
    { .name="MR",         .func = [this] { return v.MR>=800;                           }},
    { .name="R2",         .func = [this] { return v.R2_2l>=0.08;                       }},
    { .name="HLT",        .func =                boost_triggers                         },
    { .name="2Lep",       .func = [this] { return 
                                           (v.Electron.Select.n==2&&v.Muon.Veto.n==0) ||
                                           (v.Muon.Select.n==2&&v.Electron.Veto.n==0); }},
    { .name="OppCharge",  .func = [this] { 
        if (v.Electron.Select.n==2) return (v.Electron.Select(0).charge + v.Electron.Select(1).charge)==0;
        else if (v.Muon.Select.n==2) return (v.Muon.Select(0).charge + v.Muon.Select(1).charge)==0;
        return false;
      }},
    { .name="1M",         .func = [this] { return v.FatJet.JetAK8Mass.n>=1;            }},
    { .name="dPhi",       .func = [this] { return v.dPhiRazor<2.8;                     }},
    { .name="Mll",        .func = [this] { return std::abs(v.M_2l-91.2)<10;            }},
  };

  // 1 Photon invisible control sample
  analysis_cuts[Region::CR_1PhoInv] = {
    { .name="1JetAK8",    .func = [this] { return v.FatJet.JetAK8.n>=1;             }},
    { .name="1Pho",       .func = [this] { return v.Photon.Select.n==1;             }},
    { .name="NJet",       .func = [this] { return v.Jet.JetNoPho.n>=2;              }},
    { .name="MR",         .func = [this] { return v.MR_pho>=800;                    }},
    { .name="R2",         .func = [this] { return v.R2_pho>=0.08;                   }},
    { .name="HLT",        .func =                boost_triggers                      },
    { .name="0Ele",       .func = [this] { return v.Electron.Veto.n==0;             }},
    { .name="0Mu",        .func = [this] { return v.Muon.Veto.n==0;                 }},
    { .name="0Tau",       .func = [this] { return v.Tau.Veto.n==0;                  }},
    { .name="1M",         .func = [this] { return v.FatJet.JetAK8Mass.n>=1;         }},
    { .name="dPhi",       .func = [this] { return v.dPhiRazorNoPho<2.8;             }},
  };

  // Fake rate measurement region
  analysis_cuts[Region::CR_Fake] = {
    { .name="1JetAK8",    .func = [this] { return v.FatJet.JetAK8.n>=1;             }},
    { .name="NJet",       .func = [this] { return v.Jet.Jet.n>=2;                   }},
    { .name="MR",         .func = [this] { return v.MR>=800;                        }},
    { .name="HLT",        .func =                boost_triggers                      },
    { .name="0Ele",       .func = [this] { return v.Electron.Veto.n==0;             }},
    { .name="0Mu",        .func = [this] { return v.Muon.Veto.n==0;                 }},
    { .name="0Tau",       .func = [this] { return v.Tau.Veto.n==0;                  }},
    { .name="0b",         .func = [this] { return v.Jet.LooseBTag.n==0;             }},
    { .name="InvdPhi",    .func = [this] { return v.dPhiRazor>=2.8;                 }},
  };

  
  // Signal-like validation region
  define_region(Region::Val_Signal, Region::Pre, {
    { .name="0Ele",       .func = [this] { return v.Electron.Veto.n==0;             }},
    { .name="0Mu",        .func = [this] { return v.Muon.Veto.n==0;                 }},
    { .name="0Tau",       .func = [this] { return v.Tau.Veto.n==0;                  }},
    { .name="1b",         .func = [this] { return v.Jet.MediumBTag.n>=1;            }},
    { .name="1M",         .func = [this] { return v.FatJet.JetAK8Mass.n>=1;         }},
    { .name="InvdPhi",    .func = [this] { return v.dPhiRazor>=2.8;                 }},
  });
  
  // Multijet-like validation region
  define_region(Region::Val_QCD, Region::Pre, {
    { .name="0Ele",       .func = [this] { return v.Electron.Veto.n==0;             }},
    { .name="0Mu",        .func = [this] { return v.Muon.Veto.n==0;                 }},
    { .name="0Tau",       .func = [this] { return v.Tau.Veto.n==0;                  }},
    { .name="0b",         .func = [this] { return v.Jet.LooseBTag.n==0;             }},
    { .name="1M",         .func = [this] { return v.FatJet.JetAK8Mass.n>=1;         }},
    { .name="dPhi",       .func = [this] { return v.dPhiRazor<2.8;                  }},
  });

  // Fully hadronic signal regions
  define_region(Region::SR_Had_1htop, Region::Pre_Had, {
    { .name="1HadTop",    .func = [this] { return v.FatJet.HadTop.n==1;               }},
    { .name="NJet",       .func = [this] { return v.Jet.Jet.n>=3;                     }},
  });

  define_region(Region::SR_Had_2htop, Region::Pre_Had, {
    { .name="2HadTop",    .func = [this] { return v.FatJet.HadTop.n>=2;               }},
    { .name="NJet",       .func = [this] { return v.Jet.Jet.n>=3;                     }},
  });

  define_region(Region::SR_Had_V_b_45j, Region::Pre_Had, {
    { .name="1HadV",      .func = [this] { return v.FatJet.HadV.n>=1;                 }},
    { .name="1b",         .func = [this] { return v.Jet.MediumIsoBTag.n>=1;           }},
    { .name="NJet",       .func = [this] { return v.Jet.Jet.n==4||v.Jet.Jet.n==5;     }},
    { .name="0HadTop",    .func = [this] { return v.FatJet.HadTop.n==0;               }},
  });

  define_region(Region::SR_Had_V_b_6j, Region::Pre_Had, {
    { .name="1HadV",      .func = [this] { return v.FatJet.HadV.n>=1;                 }},
    { .name="1b",         .func = [this] { return v.Jet.MediumIsoBTag.n>=1;           }},
    { .name="NJet",       .func = [this] { return v.Jet.Jet.n>=6;                     }},
    { .name="0HadTop",    .func = [this] { return v.FatJet.HadTop.n==0;               }},
  });

  define_region(Region::SR_Had_1V_0b_34j, Region::Pre_Had, {
    { .name="1HadV",      .func = [this] { return v.FatJet.HadV.n==1;                 }},
    { .name="0isob",      .func = [this] { return v.Jet.LooseIsoBTag.n==0;            }}, 
    { .name="NJet",       .func = [this] { return v.Jet.Jet.n==3||v.Jet.Jet.n==4;     }},
    { .name="0HadTop",    .func = [this] { return v.FatJet.HadTop.n==0;               }},
  });

  define_region(Region::SR_Had_1V_0b_5j, Region::Pre_Had, {
    { .name="1HadV",      .func = [this] { return v.FatJet.HadV.n==1;                 }},
    { .name="0isob",      .func = [this] { return v.Jet.LooseIsoBTag.n==0;            }},
    { .name="NJet",       .func = [this] { return v.Jet.Jet.n>=5;                     }},
    { .name="0HadTop",    .func = [this] { return v.FatJet.HadTop.n==0;               }},
  });

  define_region(Region::SR_Had_2V_0b_24j, Region::Pre_Had, {
    { .name="2HadV",      .func = [this] { return v.FatJet.HadV.n==2;                 }},
    { .name="0isob",      .func = [this] { return v.Jet.LooseIsoBTag.n==0;            }},
    { .name="NJet",       .func = [this] { return v.Jet.Jet.n>=2&&v.Jet.Jet.n<=4;     }},
    { .name="0HadTop",    .func = [this] { return v.FatJet.HadTop.n==0;               }},
  });

  define_region(Region::SR_Had_2V_0b_5j, Region::Pre_Had, {
    { .name="2HadV",      .func = [this] { return v.FatJet.HadV.n==2;                 }},
    { .name="0isob",      .func = [this] { return v.Jet.LooseIsoBTag.n==0;            }},
    { .name="NJet",       .func = [this] { return v.Jet.Jet.n>=5;                     }},
    { .name="0HadTop",    .func = [this] { return v.FatJet.HadTop.n==0;               }},
  });

  define_region(Region::SR_Had_H_b_45j, Region::Pre_Had, {
    { .name="1HadH",      .func = [this] { return v.FatJet.HadH.n>=1;                 }},
    { .name="1b",         .func = [this] { return v.Jet.MediumBTag.n>=1;              }},
    { .name="NJet",       .func = [this] { return v.Jet.Jet.n==4||v.Jet.Jet.n==5;     }},
    { .name="0HadTop",    .func = [this] { return v.FatJet.HadTop.n==0;               }},
  });

  define_region(Region::SR_Had_H_b_6j, Region::Pre_Had, {
    { .name="1HadH",      .func = [this] { return v.FatJet.HadH.n==1;                 }},
    { .name="1b",         .func = [this] { return v.Jet.MediumBTag.n>=1;              }},
    { .name="NJet",       .func = [this] { return v.Jet.Jet.n>=6;                     }},
    { .name="0HadTop",    .func = [this] { return v.FatJet.HadTop.n==0;               }},
  });

  define_region(Region::SR_Had_2H_b_6j, Region::Pre_Had, {
    { .name="2HadH",      .func = [this] { return v.FatJet.HadH.n>=2;                 }},
    { .name="1b",         .func = [this] { return v.Jet.MediumBTag.n>=1;              }},
    { .name="NJet",       .func = [this] { return v.Jet.Jet.n>=6;                     }},
    { .name="0HadTop",    .func = [this] { return v.FatJet.HadTop.n==0;               }},
  });

  define_region(Region::SR_Had_HV_b_6j, Region::Pre_Had, {
    { .name="1HadH",      .func = [this] { return v.FatJet.HadH.n==1;                 }},
    { .name="1HadV",      .func = [this] { return v.FatJet.HadV.n==1;                 }},
    { .name="1b",         .func = [this] { return v.Jet.MediumBTag.n>=1;              }},
    { .name="NJet",       .func = [this] { return v.Jet.Jet.n>=6;                     }},
    { .name="0HadTop",    .func = [this] { return v.FatJet.HadTop.n==0;               }},
  });

  define_region(Region::SR_Had_1H_0b_34j, Region::Pre_Had, {
    { .name="1HadH",      .func = [this] { return v.FatJet.HadH.n==1;                 }},
    { .name="0isob",      .func = [this] { return v.Jet.LooseIsoBTag.n==0;            }},
    { .name="NJet",       .func = [this] { return v.Jet.Jet.n==3||v.Jet.Jet.n==4;     }},
    { .name="0HadTop",    .func = [this] { return v.FatJet.HadTop.n==0;               }},
  });

  define_region(Region::SR_Had_1H_0b_5j, Region::Pre_Had, {
    { .name="1HadH",      .func = [this] { return v.FatJet.HadH.n==1;                 }},
    { .name="0isob",      .func = [this] { return v.Jet.LooseIsoBTag.n==0;            }},
    { .name="NJet",       .func = [this] { return v.Jet.Jet.n>=5;                     }},
    { .name="0HadTop",    .func = [this] { return v.FatJet.HadTop.n==0;               }},
  });

  define_region(Region::SR_Had_2H_0b_34j, Region::Pre_Had, {
    { .name="2HadH",      .func = [this] { return v.FatJet.HadH.n>=2;                 }},
    { .name="0isob",      .func = [this] { return v.Jet.LooseIsoBTag.n==0;            }},
    { .name="NJet",       .func = [this] { return v.Jet.Jet.n==3||v.Jet.Jet.n==4;     }},
    { .name="0HadTop",    .func = [this] { return v.FatJet.HadTop.n==0;               }},
  });

  define_region(Region::SR_Had_2H_0b_5j, Region::Pre_Had, {
    { .name="2HadH",      .func = [this] { return v.FatJet.HadH.n>=2;                 }},
    { .name="0isob",      .func = [this] { return v.Jet.LooseIsoBTag.n==0;            }},
    { .name="NJet",       .func = [this] { return v.Jet.Jet.n>=5;                     }},
    { .name="0HadTop",    .func = [this] { return v.FatJet.HadTop.n==0;               }},
  });

  define_region(Region::SR_Had_HV_0b_24j, Region::Pre_Had, {
    { .name="1HadH",      .func = [this] { return v.FatJet.HadH.n>=1;                 }},
    { .name="1HadV",      .func = [this] { return v.FatJet.HadV.n>=1;                 }},
    { .name="0isob",      .func = [this] { return v.Jet.LooseIsoBTag.n==0;            }},
    { .name="NJet",       .func = [this] { return v.Jet.Jet.n>=2&&v.Jet.Jet.n<=4;     }},
    { .name="0HadTop",    .func = [this] { return v.FatJet.HadTop.n==0;               }},
  });

  define_region(Region::SR_Had_HV_0b_5j, Region::Pre_Had, {
    { .name="1HadH",      .func = [this] { return v.FatJet.HadH.n>=1;                 }},
    { .name="1HadV",      .func = [this] { return v.FatJet.HadV.n>=1;                 }},
    { .name="0isob",      .func = [this] { return v.Jet.LooseIsoBTag.n==0;            }},
    { .name="NJet",       .func = [this] { return v.Jet.Jet.n>=5;                     }},
    { .name="0HadTop",    .func = [this] { return v.FatJet.HadTop.n==0;               }},
  });

  // 1 Isolated lepton signal regions
  define_region(Region::SR_Lep_1htop, Region::Pre_Lep, {
    { .name="1HadTop",    .func = [this] { return v.FatJet.HadTop.n>=1;               }},
  });

  define_region(Region::SR_Lep_V_b, Region::Pre_Lep, {
    { .name="1HadV",      .func = [this] { return v.FatJet.HadV.n>=1;                 }},
    { .name="1b",         .func = [this] { return v.Jet.MediumIsoBTag.n>=1;           }},
    { .name="NJet",       .func = [this] { return v.Jet.Jet.n>=3;                     }},
    { .name="0HadTop",    .func = [this] { return v.FatJet.HadTop.n==0;               }},
  });

  define_region(Region::SR_Lep_V_0b, Region::Pre_Lep, {
    { .name="1HadV",      .func = [this] { return v.FatJet.HadV.n>=1;                 }},
    { .name="0isob",      .func = [this] { return v.Jet.LooseIsoBTag.n==0;            }},
    { .name="NJet",       .func = [this] { return v.Jet.Jet.n>=3;                     }},
    { .name="0HadTop",    .func = [this] { return v.FatJet.HadTop.n==0;               }},
  });

  define_region(Region::SR_Lep_H_b, Region::Pre_Lep, {
    { .name="1HadH",      .func = [this] { return v.FatJet.HadH.n>=1;                 }},
    { .name="1b",         .func = [this] { return v.Jet.MediumIsoBTag.n>=1;           }},
    { .name="NJet",       .func = [this] { return v.Jet.Jet.n>=3;                     }},
    { .name="0HadTop",    .func = [this] { return v.FatJet.HadTop.n==0;               }},
  });

  define_region(Region::SR_Lep_H_0b, Region::Pre_Lep, {
    { .name="1HadH",      .func = [this] { return v.FatJet.HadH.n>=1;                 }},
    { .name="0isob",      .func = [this] { return v.Jet.LooseIsoBTag.n==0;            }},
    { .name="0HadTop",    .func = [this] { return v.FatJet.HadTop.n==0;               }},
  });

  // Non-isolated lepton signal regions
  define_region(Region::SR_Leptop_0htop, Region::Pre_NonIso, {
    { .name="1LepTop",       .func = [this] { return v.FatJet.LepTop.n>=1;            }},
    { .name="lepNuDR",       .func = [this] { return v.lepNeutrinoDR>=1.2;            }},
    { .name="NJet",          .func = [this] { return v.Jet.Jet.n>=3;                  }},
    { .name="0HadTop",       .func = [this] { return v.FatJet.HadTop.n==0;            }},
    { .name="0LepJet",       .func = [this] { return v.FatJet.LepJet.n==0;            }},
  });

  define_region(Region::SR_Leptop_1htop, Region::Pre_NonIso, {
    { .name="1LepTop",       .func = [this] { return v.FatJet.LepTop.n>=1;            }},
    { .name="lepNuDR",       .func = [this] { return v.lepNeutrinoDR>=1.2;            }},
    { .name="1HadTop",       .func = [this] { return v.FatJet.HadTop.n>=1;            }},
    { .name="NJet",          .func = [this] { return v.Jet.Jet.n>=3;                  }},
    { .name="0LepJet",       .func = [this] { return v.FatJet.LepJet.n==0;            }},
  });

  define_region(Region::SR_Lepjet_0V_24j, Region::Pre_NonIso, {
    { .name="1LepJet",       .func = [this] { return v.FatJet.LepJet.n>=1;            }},
    { .name="0HadV",         .func = [this] { return v.FatJet.HadV.n==0;              }},
    { .name="NJet",          .func = [this] { return v.Jet.Jet.n>=2&&v.Jet.Jet.n<=4;  }},
    { .name="0LepTop",       .func = [this] { return v.FatJet.LepTop.n==0;            }},
    { .name="0HadTop",       .func = [this] { return v.FatJet.HadTop.n==0;            }},
  });

  define_region(Region::SR_Lepjet_0V_5j, Region::Pre_NonIso, {
    { .name="1LepJet",       .func = [this] { return v.FatJet.LepJet.n>=1;            }},
    { .name="0HadV",         .func = [this] { return v.FatJet.HadV.n==0;              }},
    { .name="NJet",          .func = [this] { return v.Jet.Jet.n>=5;                  }},
    { .name="0LepTop",       .func = [this] { return v.FatJet.LepTop.n==0;            }},
    { .name="0HadTop",       .func = [this] { return v.FatJet.HadTop.n==0;            }},
  });

  define_region(Region::SR_Lepjet_1V_24j, Region::Pre_NonIso, {
    { .name="1LepJet",       .func = [this] { return v.FatJet.LepJet.n>=1;            }},
    { .name="1HadV",         .func = [this] { return v.FatJet.HadV.n==1;              }},
    { .name="NJet",          .func = [this] { return v.Jet.Jet.n>=2&&v.Jet.Jet.n<=4;  }},
    { .name="0LepTop",       .func = [this] { return v.FatJet.LepTop.n==0;            }},
    { .name="0HadTop",       .func = [this] { return v.FatJet.HadTop.n==0;            }},
  });

  define_region(Region::SR_Lepjet_1V_5j, Region::Pre_NonIso, {
    { .name="1LepJet",       .func = [this] { return v.FatJet.LepJet.n>=1;            }},
    { .name="1HadV",         .func = [this] { return v.FatJet.HadV.n==1;              }},
    { .name="NJet",          .func = [this] { return v.Jet.Jet.n>=5;                  }},
    { .name="0LepTop",       .func = [this] { return v.FatJet.LepTop.n==0;            }},
    { .name="0HadTop",       .func = [this] { return v.FatJet.HadTop.n==0;            }},
  });

}


#endif // End header guard
