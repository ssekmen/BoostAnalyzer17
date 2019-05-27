#include "TLorentzVector.h"
#include "TMath.h"
#include "include/AnalysisBase.h"
#include <fstream>
#include <map>

using namespace std;
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

bool
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


/*  if(isJetHT) analysis_cuts['P'].push_back({ .name="HLT",.func = [this,&d] { return isData ? d.HLT_PFHT1050==1 || d.HLT_AK8PFHT800_TrimMass50==1 : 1; }});
  else if(isMET) analysis_cuts['P'].push_back({ .name="HLT",.func = [this,&d] { return isData ? !(d.HLT_PFHT1050==1 || d.HLT_AK8PFHT800_TrimMass50==1) && d.HLT_PFHT500_PFMET100_PFMHT100_IDTight==1 : 1; }});
  else      analysis_cuts['P'].push_back({ .name="HLT",.func = [this,&d] { return isData ? d.HLT_PFHT1050==1 || d.HLT_AK8PFHT800_TrimMass50==1 || d.HLT_PFHT500_PFMET100_PFMHT100_IDTight==1 : 1; }});
*/



//**************************************************
//       İnclusive Categories
//**************************************************


//************ # inclusive SİGNAL REGIONS # ***********

// region lepton_multijet_S  ***

#if INC == 1
analysis_cuts['A'].push_back({ .name="NJet",    .func = [&d]      { return nJet>=4 || nJet>=6;    }}); // AK4 jets
analysis_cuts['A'].push_back({ .name="1Lep",    .func = []        { return (nMuTight==1 && nEleTight==0 )|| (nEleTight==1 && nMuTight==0);                   }});
analysis_cuts['A'].push_back({ .name="MR_R2",   .func = [&d]      { return MR>=550 && R2>=0.2;    }});
analysis_cuts['A'].push_back({ .name="mDPhi",   .func = []        { return dPhiRazor<2.8;         }});
analysis_cuts['A'].push_back({ .name="1b",      .func = []        { return nMediumBTag>=3;        }});
analysis_cuts['A'].push_back({ .name="HLTSingleMu",       .func = [this,&d] { return isData ? d.HLT_IsoMu20==1 || d.HLT_IsoMu24==1 || d.HLT_IsoMu27==1 || d.HLT_Mu50==1 || d.HLT_IsoMu20_eta2p1_LooseChargedIsoPFTau27_eta2p1_TightID_CrossL1==1 || d.HLT_IsoMu24_eta2p1_LooseChargedIsoPFTau20_TightID_SingleL1==1 || d.HLT_IsoMu27_LooseChargedIsoPFTau20_SingleL1==1 : 1; }});
analysis_cuts['A'].push_back({ .name="HLTSingleElec",     .func = [this,&d] { return isData ? d.HLT_Ele20_WPLoose_Gsf==1 || d.HLT_Ele32_WPTight_Gsf==1 || d.HLT_Ele115_CaloIdVT_GsfTrkIdT==1 || d.HLT_Ele135_CaloIdVT_GsfTrkIdT==1 || d.HLT_Ele24_eta2p1_WPTight_Gsf_LooseChargedIsoPFTau30_eta2p1_CrossL1==1 || d.HLT_Ele20_eta2p1_WPLoose_Gsf==1 : 1; }});
analysis_cuts['A'].push_back({ .name="MT",         .func = []    { return MT_lepTight>120; }});
// region lepton_sevenjets_S
analysis_cuts['B'].push_back({ .name="1Lep",    .func = []        { return (nMuTight==1 && nEleTight==0 )|| (nEleTight==1 && nMuTight==0);                   }});
analysis_cuts['B'].push_back({ .name="NJet",    .func = []        { return nJet>=7;               }}); // AK4 jets
analysis_cuts['B'].push_back({ .name="MR_R2",   .func = [&d]      { return MR>=550 && R2>=0.2;    }});
analysis_cuts['B'].push_back({ .name="1b",      .func = []        { return nMediumBTag>=3;        }});
analysis_cuts['B'].push_back({ .name="HLTSingleMu",       .func = [this,&d] { return isData ? d.HLT_IsoMu20==1 || d.HLT_IsoMu24==1 || d.HLT_IsoMu27==1 || d.HLT_Mu50==1 || d.HLT_IsoMu20_eta2p1_LooseChargedIsoPFTau27_eta2p1_TightID_CrossL1==1 || d.HLT_IsoMu24_eta2p1_LooseChargedIsoPFTau20_TightID_SingleL1==1 || d.HLT_IsoMu27_LooseChargedIsoPFTau20_SingleL1==1 : 1; }});
analysis_cuts['B'].push_back({ .name="HLTSingleElec",     .func = [this,&d] { return isData ? d.HLT_Ele20_WPLoose_Gsf==1 || d.HLT_Ele32_WPTight_Gsf==1 || d.HLT_Ele115_CaloIdVT_GsfTrkIdT==1 || d.HLT_Ele135_CaloIdVT_GsfTrkIdT==1 || d.HLT_Ele24_eta2p1_WPTight_Gsf_LooseChargedIsoPFTau30_eta2p1_CrossL1==1 || d.HLT_Ele20_eta2p1_WPLoose_Gsf==1 : 1; }});
//analysis_cuts['B'].push_back({ .name="mDPhi",   .func = []        { return dPhiRazor<2.8;         }});
analysis_cuts['B'].push_back({ .name="MT",         .func = []    { return MT_lepTight>120; }});


// region dijet_S
analysis_cuts['C'].push_back({ .name="nLepVeto",       .func = []    { return nLepVeto==0;                      }});
analysis_cuts['C'].push_back({ .name="0Tau", .func = [] { return nTauVeto==0; }});
analysis_cuts['C'].push_back({ .name="NJet",       .func = [&d]      { return nJet>=2 || nJet>=3;           }}); // AK4 jets
analysis_cuts['C'].push_back({ .name="0Top",       .func = []    { return nHadTopTag==0;                    }});
analysis_cuts['C'].push_back({ .name="0W",         .func = []    { return nTightWTag==0;                    }});
analysis_cuts['C'].push_back({ .name="MR_R2",      .func = [&d]      { return MR>=650 && R2>=0.30;          }});
analysis_cuts['C'].push_back({ .name="mDPhi",      .func = []        { return dPhiRazor<2.8;                }});
analysis_cuts['C'].push_back({ .name="1b",         .func = []        { return nMediumBTag>=2;               }});
analysis_cuts['C'].push_back({ .name="HLT",        .func = [this,&d] { return isData ? d.HLT_Rsq0p35==1 || d.HLT_Rsq0p40==1 || d.HLT_RsqMR300_Rsq0p09_MR200==1 || d.HLT_RsqMR300_Rsq0p09_MR200_4jet==1 || d.HLT_RsqMR320_Rsq0p09_MR200==1 || d.HLT_RsqMR320_Rsq0p09_MR200_4jet==1 : 1; }});


// region multijet_S
analysis_cuts['D'].push_back({ .name="nLepVeto",       .func = []    { return nLepVeto==0;                      }});
analysis_cuts['D'].push_back({ .name="0Tau", .func = [] { return nTauVeto==0; }});
analysis_cuts['D'].push_back({ .name="NJet",       .func = [&d]      { return nJet>=4 || nJet>=6;           }}); // AK4 jets
analysis_cuts['D'].push_back({ .name="HLT",        .func = [this,&d] { return isData ? d.HLT_Rsq0p35==1 || d.HLT_Rsq0p40==1 || d.HLT_RsqMR300_Rsq0p09_MR200==1 || d.HLT_RsqMR300_Rsq0p09_MR200_4jet==1 || d.HLT_RsqMR320_Rsq0p09_MR200==1 || d.HLT_RsqMR320_Rsq0p09_MR200_4jet==1 : 1; }});
analysis_cuts['D'].push_back({ .name="0Top",       .func = []    { return nHadTopTag==0;                    }});
analysis_cuts['D'].push_back({ .name="0W",         .func = []    { return nTightWTag==0;                    }});
analysis_cuts['D'].push_back({ .name="MR_R2",      .func = [&d]      { return MR>=650 && R2>=0.30;          }});
analysis_cuts['D'].push_back({ .name="mDPhi",      .func = []        { return dPhiRazor<2.8;                }});
analysis_cuts['D'].push_back({ .name="1b",         .func = []        { return nMediumBTag>=3;               }});


// region sevenjet_S-
analysis_cuts['E'].push_back({ .name="nLepVeto",       .func = []    { return nLepVeto==0;                      }});
analysis_cuts['E'].push_back({ .name="0Tau", .func = [] { return nTauVeto==0; }});
analysis_cuts['E'].push_back({ .name="NJet",    .func = []        { return nJet>=7;               }}); // AK4 jets
analysis_cuts['E'].push_back({ .name="HLT",        .func = [this,&d] { return isData ? d.HLT_Rsq0p35==1 || d.HLT_Rsq0p40==1 || d.HLT_RsqMR300_Rsq0p09_MR200==1 || d.HLT_RsqMR300_Rsq0p09_MR200_4jet==1 || d.HLT_RsqMR320_Rsq0p09_MR200==1 || d.HLT_RsqMR320_Rsq0p09_MR200_4jet==1 : 1; }});
analysis_cuts['E'].push_back({ .name="0Top",       .func = []    { return nHadTopTag==0;                    }});
analysis_cuts['E'].push_back({ .name="0W",         .func = []    { return nTightWTag==0;                    }});
analysis_cuts['E'].push_back({ .name="MR_R2",      .func = [&d]      { return MR>=650 && R2>=0.30;          }});
analysis_cuts['E'].push_back({ .name="mDPhi",      .func = []        { return dPhiRazor<2.8;                }});
analysis_cuts['E'].push_back({ .name="1b",         .func = []        { return nMediumBTag>=3;               }});


//************ # inclusive CONTROL REGIONS # ***********


//  region onelepton
analysis_cuts['F'].push_back({ .name="NJet",    .func = []        { return nJet>=2;               }}); // AK4 jets
analysis_cuts['F'].push_back({ .name="1Lep",    .func = []        { return (nMuTight==1 && nEleTight==0 )|| (nEleTight==1 && nMuTight==0);                   }});
analysis_cuts['F'].push_back({ .name="MT",         .func = []    { return MT_lepTight>=30 && MT_lepTight<100; }});
analysis_cuts['F'].push_back({ .name="MR_R2",      .func = [&d]      { return MR>=300 && R2>=0.15;          }});
analysis_cuts['F'].push_back({ .name="HLTSingleMu",       .func = [this,&d] { return isData ? d.HLT_IsoMu20==1 || d.HLT_IsoMu24==1 || d.HLT_IsoMu27==1 || d.HLT_Mu50==1 || d.HLT_IsoMu20_eta2p1_LooseChargedIsoPFTau27_eta2p1_TightID_CrossL1==1 || d.HLT_IsoMu24_eta2p1_LooseChargedIsoPFTau20_TightID_SingleL1==1 || d.HLT_IsoMu27_LooseChargedIsoPFTau20_SingleL1==1 : 1; }});
analysis_cuts['F'].push_back({ .name="HLTSingleElec",     .func = [this,&d] { return isData ? d.HLT_Ele20_WPLoose_Gsf==1 || d.HLT_Ele32_WPTight_Gsf==1 || d.HLT_Ele115_CaloIdVT_GsfTrkIdT==1 || d.HLT_Ele135_CaloIdVT_GsfTrkIdT==1 || d.HLT_Ele24_eta2p1_WPTight_Gsf_LooseChargedIsoPFTau30_eta2p1_CrossL1==1 || d.HLT_Ele20_eta2p1_WPLoose_Gsf==1 : 1; }});
analysis_cuts['F'].push_back({ .name="MET", .func = [&d] { return d.MET_pt>30; }});


//  region onelepton_W
analysis_cuts['I'].push_back({ .name="0b",         .func = []        { return nMediumBTag==0;               }});
analysis_cuts['I'].push_back({ .name="NJet",    .func = []        { return nJet>=2;               }}); // AK4 jets
analysis_cuts['I'].push_back({ .name="1Lep",    .func = []        { return (nMuTight==1 && nEleTight==0 )|| (nEleTight==1 && nMuTight==0);                   }});
analysis_cuts['I'].push_back({ .name="MT",         .func = []    { return MT_lepTight>=30 && MT_lepTight<100; }});
analysis_cuts['I'].push_back({ .name="MR_R2",      .func = [&d]      { return MR>=300 && R2>=0.15;          }});
analysis_cuts['I'].push_back({ .name="HLTSingleMu",       .func = [this,&d] { return isData ? d.HLT_IsoMu20==1 || d.HLT_IsoMu24==1 || d.HLT_IsoMu27==1 || d.HLT_Mu50==1 || d.HLT_IsoMu20_eta2p1_LooseChargedIsoPFTau27_eta2p1_TightID_CrossL1==1 || d.HLT_IsoMu24_eta2p1_LooseChargedIsoPFTau20_TightID_SingleL1==1 || d.HLT_IsoMu27_LooseChargedIsoPFTau20_SingleL1==1 : 1; }});
analysis_cuts['I'].push_back({ .name="HLTSingleElec",     .func = [this,&d] { return isData ? d.HLT_Ele20_WPLoose_Gsf==1 || d.HLT_Ele32_WPTight_Gsf==1 || d.HLT_Ele115_CaloIdVT_GsfTrkIdT==1 || d.HLT_Ele135_CaloIdVT_GsfTrkIdT==1 || d.HLT_Ele24_eta2p1_WPTight_Gsf_LooseChargedIsoPFTau30_eta2p1_CrossL1==1 || d.HLT_Ele20_eta2p1_WPLoose_Gsf==1 : 1; }});
analysis_cuts['I'].push_back({ .name="MET", .func = [&d] { return d.MET_pt>30; }});

//  region onelepton_tt
analysis_cuts['H'].push_back({ .name="1b",      .func = []        { return nMediumBTag>=1;                 }});
analysis_cuts['H'].push_back({ .name="NJet",    .func = []        { return nJet>=2;               }}); // AK4 jets
analysis_cuts['H'].push_back({ .name="1Lep",    .func = []        { return (nMuTight==1 && nEleTight==0 )|| (nEleTight==1 && nMuTight==0);                   }});
analysis_cuts['H'].push_back({ .name="MT",         .func = []    { return MT_lepTight>=30 && MT_lepTight<100; }});
analysis_cuts['H'].push_back({ .name="MR_R2",      .func = [&d]      { return MR>=300 && R2>=0.15;          }});
analysis_cuts['H'].push_back({ .name="HLTSingleMu",       .func = [this,&d] { return isData ? d.HLT_IsoMu20==1 || d.HLT_IsoMu24==1 || d.HLT_IsoMu27==1 || d.HLT_Mu50==1 || d.HLT_IsoMu20_eta2p1_LooseChargedIsoPFTau27_eta2p1_TightID_CrossL1==1 || d.HLT_IsoMu24_eta2p1_LooseChargedIsoPFTau20_TightID_SingleL1==1 || d.HLT_IsoMu27_LooseChargedIsoPFTau20_SingleL1==1 : 1; }});
analysis_cuts['H'].push_back({ .name="HLTSingleElec",     .func = [this,&d] { return isData ? d.HLT_Ele20_WPLoose_Gsf==1 || d.HLT_Ele32_WPTight_Gsf==1 || d.HLT_Ele115_CaloIdVT_GsfTrkIdT==1 || d.HLT_Ele135_CaloIdVT_GsfTrkIdT==1 || d.HLT_Ele24_eta2p1_WPTight_Gsf_LooseChargedIsoPFTau30_eta2p1_CrossL1==1 || d.HLT_Ele20_eta2p1_WPLoose_Gsf==1 : 1; }});
analysis_cuts['H'].push_back({ .name="MET", .func = [&d] { return d.MET_pt>30; }});


//  region dilepton
analysis_cuts['K'].push_back({ .name="HLTSingleMu",       .func = [this,&d] { return isData ? d.HLT_IsoMu20==1 || d.HLT_IsoMu24==1 || d.HLT_IsoMu27==1 || d.HLT_Mu50==1 || d.HLT_IsoMu20_eta2p1_LooseChargedIsoPFTau27_eta2p1_TightID_CrossL1==1 || d.HLT_IsoMu24_eta2p1_LooseChargedIsoPFTau20_TightID_SingleL1==1 || d.HLT_IsoMu27_LooseChargedIsoPFTau20_SingleL1==1 : 1; }});
analysis_cuts['K'].push_back({ .name="HLTSingleElec",     .func = [this,&d] { return isData ? d.HLT_Ele20_WPLoose_Gsf==1 || d.HLT_Ele32_WPTight_Gsf==1 || d.HLT_Ele115_CaloIdVT_GsfTrkIdT==1 || d.HLT_Ele135_CaloIdVT_GsfTrkIdT==1 || d.HLT_Ele24_eta2p1_WPTight_Gsf_LooseChargedIsoPFTau30_eta2p1_CrossL1==1 || d.HLT_Ele20_eta2p1_WPLoose_Gsf==1 : 1; }});
analysis_cuts['K'].push_back({ .name="2Lep",       .func = []    { return (nEleTight==2&&nMuVeto==0)||(nMuTight==2&&nEleVeto==0); }});
analysis_cuts['K'].push_back({ .name="Mll",        .func = []    { return M_ll_lepTight>20;           }});
analysis_cuts['K'].push_back({ .name="1b",         .func = []        { return nMediumBTag>=1;               }});
analysis_cuts['K'].push_back({ .name="MR_R2",      .func = [&d]      { return MR>=300 && R2>=0.15;          }});
analysis_cuts['K'].push_back({ .name="MET", .func = [&d] { return d.MET_pt>30; }});
analysis_cuts['K'].push_back({ .name="OppCharge",  .func = [&d]  {
         if (nEleTight==2) return  std::abs(M_ll_lepTight)>76 && std::abs(M_ll_lepTight)<106 && (d.Electron[iEleTight[0]].charge + d.Electron[iEleTight[1]].charge)==0;
         else if (nMuTight==2) return std::abs(M_ll_lepTight)>76 && std::abs(M_ll_lepTight)<106 &&  (d.Muon[iMuTight[0]].charge  + d.Muon[iMuTight[1]].charge)==0;
         return false;
       }});


//  region vetolepton
analysis_cuts['M'].push_back({ .name="1Lep",       .func = []    { return (nEleTight==1&&nMuVeto==0)||(nMuTight==1&&nEleVeto==0); }});
analysis_cuts['M'].push_back({ .name="MT",         .func = []    { return MT_vetolep>=30 && MT_vetolep<100; }});
analysis_cuts['M'].push_back({ .name="MR_R2",      .func = [&d]      { return MR>=400 && R2>=0.25;          }});
analysis_cuts['M'].push_back({ .name="NJet",       .func = []    { return nJet>=2;                          }});  // NJet80 yani 80 GeV olması gerekiyor inc de. Ama bizde ole bir tanimlama yoktu.


//  region vetotau
analysis_cuts['N'].push_back({ .name="1Tauveto",       .func = []    { return nTauVeto==1;                      }});
analysis_cuts['N'].push_back({ .name="MT",         .func = []    { return MT_vetolep>=30 && MT_vetolep<100; }});
analysis_cuts['N'].push_back({ .name="MR_R2",      .func = [&d]      { return MR>=400 && R2>=0.25;          }});
analysis_cuts['N'].push_back({ .name="NJet",       .func = []    { return nJet>=2;                          }});  // NJet80 yani 80 GeV olması gerekiyor inc de. Ama bizde ole bir tanimlama yoktu.


//  region oneleptoninv
analysis_cuts['O'].push_back({ .name="HLTSingleMu",       .func = [this,&d] { return isData ? d.HLT_IsoMu20==1 || d.HLT_IsoMu24==1 || d.HLT_IsoMu27==1 || d.HLT_Mu50==1 || d.HLT_IsoMu20_eta2p1_LooseChargedIsoPFTau27_eta2p1_TightID_CrossL1==1 || d.HLT_IsoMu24_eta2p1_LooseChargedIsoPFTau20_TightID_SingleL1==1 || d.HLT_IsoMu27_LooseChargedIsoPFTau20_SingleL1==1 : 1; }});
analysis_cuts['O'].push_back({ .name="HLTSingleElec",     .func = [this,&d] { return isData ? d.HLT_Ele20_WPLoose_Gsf==1 || d.HLT_Ele32_WPTight_Gsf==1 || d.HLT_Ele115_CaloIdVT_GsfTrkIdT==1 || d.HLT_Ele135_CaloIdVT_GsfTrkIdT==1 || d.HLT_Ele24_eta2p1_WPTight_Gsf_LooseChargedIsoPFTau30_eta2p1_CrossL1==1 || d.HLT_Ele20_eta2p1_WPLoose_Gsf==1 : 1; }});
analysis_cuts['O'].push_back({ .name="0b",         .func = []    { return nLooseBTag==0;                    }});
analysis_cuts['O'].push_back({ .name="1Lep",    .func = []        { return (nMuTight==1 && nEleTight==0 )|| (nEleTight==1 && nMuTight==0);                   }});
analysis_cuts['O'].push_back({ .name="MT",         .func = []    { return MT_lepTight>=30 && MT_lepTight<100; }});

//  region dileptoninv
analysis_cuts['R'].push_back({ .name="HLTSingleMu",       .func = [this,&d] { return isData ? d.HLT_IsoMu20==1 || d.HLT_IsoMu24==1 || d.HLT_IsoMu27==1 || d.HLT_Mu50==1 || d.HLT_IsoMu20_eta2p1_LooseChargedIsoPFTau27_eta2p1_TightID_CrossL1==1 || d.HLT_IsoMu24_eta2p1_LooseChargedIsoPFTau20_TightID_SingleL1==1 || d.HLT_IsoMu27_LooseChargedIsoPFTau20_SingleL1==1 : 1; }});
analysis_cuts['R'].push_back({ .name="HLTSingleElec",     .func = [this,&d] { return isData ? d.HLT_Ele20_WPLoose_Gsf==1 || d.HLT_Ele32_WPTight_Gsf==1 || d.HLT_Ele115_CaloIdVT_GsfTrkIdT==1 || d.HLT_Ele135_CaloIdVT_GsfTrkIdT==1 || d.HLT_Ele24_eta2p1_WPTight_Gsf_LooseChargedIsoPFTau30_eta2p1_CrossL1==1 || d.HLT_Ele20_eta2p1_WPLoose_Gsf==1 : 1; }});
analysis_cuts['R'].push_back({ .name="0b",         .func = []    { return nLooseBTag==0;                    }});
analysis_cuts['R'].push_back({ .name="2Lep", .func = [] { return (nEleTight==2&&nMuVeto==0)||(nMuTight==2&&nEleVeto==0); }});
analysis_cuts['R'].push_back({ .name="OppCharge",  .func = [&d]  {
          if (nEleTight==2) return (d.Electron[iEleTight[0]].charge + d.Electron[iEleTight[1]].charge)==0;
          else if (nMuTight==2) return (d.Muon[iMuTight[0]].charge  + d.Muon[iMuTight[1]].charge)==0;
          return false;
          }});
analysis_cuts['R'].push_back({ .name="Mll",        .func = []    { return std::abs(M_ll)> 80 && std::abs(M_ll)<110;         }});


//  region photonjetinv
analysis_cuts['X'].push_back({ .name="1Pho",       .func = []    { return nPhotonSelect==1;                 }     });
analysis_cuts['X'].push_back({ .name="0Mu",        .func = []    { return nMuVeto==0;                       }});
analysis_cuts['X'].push_back({ .name="0Ele",       .func = []    { return nEleVeto==0;                      }});
analysis_cuts['X'].push_back({ .name="HLT",        .func = [this,&d] { return isData ? d.HLT_Photon120_R9Id90_HE10_IsoM==1 || d.HLT_Photon165_R9Id90_HE10_IsoM==1 || d.HLT_Photon50_R9Id90_HE10_IsoM==1 || d.HLT_Photon75_R9Id90_HE10_IsoM==1 || d.HLT_Photon90_R9Id90_HE10_IsoM==1 : 1; }});
analysis_cuts['X'].push_back({ .name="MR",         .func = [&d]  { return MR_pho>=550;                    }});
analysis_cuts['X'].push_back({ .name="R2",         .func = [&d]  { return R2_pho>=0.20;                     }});



//  region qcd_presel
analysis_cuts['Y'].push_back({ .name="nLepVeto",       .func = []    { return nLepVeto==0;                      }});
analysis_cuts['Y'].push_back({ .name="0Tau", .func = [] { return nTauVeto==0; }});
analysis_cuts['Y'].push_back({ .name="NJet",    .func = []        { return nJet>=2;               }}); // AK4 jets
analysis_cuts['Y'].push_back({ .name="HLT",        .func = [this,&d] { return isData ? d.HLT_Rsq0p35==1 || d.HLT_Rsq0p40==1 || d.HLT_RsqMR300_Rsq0p09_MR200==1 || d.HLT_RsqMR300_Rsq0p09_MR200_4jet==1 || d.HLT_RsqMR320_Rsq0p09_MR200==1 || d.HLT_RsqMR320_Rsq0p09_MR200_4jet==1 : 1; }});
analysis_cuts['Y'].push_back({ .name="1W",         .func = []    { return nTightWTag==0;                    }});
analysis_cuts['Y'].push_back({ .name="1Top",       .func = []    { return nHadTopTag==0;                    }});
analysis_cuts['Y'].push_back({ .name="mDPhi",      .func = []        { return dPhiRazor<=2.8;                }});
analysis_cuts['Y'].push_back({ .name="MR",         .func = [&d]  { return MR>=650;                    }});

//  region qcd
analysis_cuts['U'].push_back({ .name="nLepVeto",       .func = []    { return nLepVeto==0;                      }});
analysis_cuts['U'].push_back({ .name="0Tau", .func = [] { return nTauVeto==0; }});
analysis_cuts['U'].push_back({ .name="NJet",    .func = []        { return nJet>=2;               }}); // AK4 jets
analysis_cuts['U'].push_back({ .name="HLT",        .func = [this,&d] { return isData ? d.HLT_Rsq0p35==1 || d.HLT_Rsq0p40==1 || d.HLT_RsqMR300_Rsq0p09_MR200==1 || d.HLT_RsqMR300_Rsq0p09_MR200_4jet==1 || d.HLT_RsqMR320_Rsq0p09_MR200==1 || d.HLT_RsqMR320_Rsq0p09_MR200_4jet==1 : 1; }});
analysis_cuts['U'].push_back({ .name="1W",         .func = []    { return nTightWTag==0;                    }});
analysis_cuts['U'].push_back({ .name="1Top",       .func = []    { return nHadTopTag==0;                    }});
analysis_cuts['U'].push_back({ .name="mDPhi",      .func = []        { return dPhiRazor<=2.8;                }});
analysis_cuts['U'].push_back({ .name="MR",         .func = [&d]  { return MR>=650;                    }});
analysis_cuts['U'].push_back({ .name="R2",         .func = [&d]  { return R2>=0.30;                     }});


//  region qcd_lowR2
analysis_cuts['V'].push_back({ .name="nLepVeto",       .func = []    { return nLepVeto==0;                      }});
analysis_cuts['V'].push_back({ .name="0Tau", .func = [] { return nTauVeto==0; }});
analysis_cuts['V'].push_back({ .name="NJet",    .func = []        { return nJet>=2;               }}); // AK4 jets
analysis_cuts['V'].push_back({ .name="HLT",        .func = [this,&d] { return isData ? d.HLT_Rsq0p35==1 || d.HLT_Rsq0p40==1 || d.HLT_RsqMR300_Rsq0p09_MR200==1 || d.HLT_RsqMR300_Rsq0p09_MR200_4jet==1 || d.HLT_RsqMR320_Rsq0p09_MR200==1 || d.HLT_RsqMR320_Rsq0p09_MR200_4jet==1 : 1; }});
analysis_cuts['V'].push_back({ .name="1W",         .func = []    { return nTightWTag==0;                    }});
analysis_cuts['V'].push_back({ .name="1Top",       .func = []    { return nHadTopTag==0;                    }});
analysis_cuts['V'].push_back({ .name="mDPhi",      .func = []        { return dPhiRazor<=2.8;                }});
analysis_cuts['V'].push_back({ .name="MR",         .func = [&d]  { return MR>=650;                    }});
analysis_cuts['V'].push_back({ .name="R2",         .func = [&d]  { return R2>=0.20 && R2<=0.30;                     }});


#else
#endif








}




void
Analysis::apply_scale_factors(eventBuffer& data, const unsigned int& s, const std::vector<std::vector<double> >& nSigmaSFs)
{
  bool isFastSim = TString(sample).Contains("FastSim");
  size_t i = 0;

  // Don't forget to specify the total number of sigmas you use in settings_*.h !

  // Electron SFs (5 sigmas - reco, fullsim id/iso, fastsim)
  double sf_ele_veto, sf_ele_loose, sf_ele_tight;
  std::tie(sf_ele_veto, sf_ele_loose, sf_ele_tight) = calc_ele_sf(data, nSigmaSFs[i][s], nSigmaSFs[i+1][s], nSigmaSFs[i+2][s], nSigmaSFs[i+3][s], isFastSim);
  i+=4;

  // Muon SFs (3 sigmas - tracking, fullsim, fastsim)
  double sf_muon_veto, sf_muon_loose, sf_muon_tight;
  std::tie(sf_muon_veto, sf_muon_loose, sf_muon_tight) =  calc_muon_sf(data, nSigmaSFs[i][s], nSigmaSFs[i+1][s], nSigmaSFs[i+2][s], isFastSim);
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




    scale_factors['A'].push_back(sf_ele_tight);
    scale_factors['A'].push_back(sf_btag_medium);

    scale_factors['B'].push_back(sf_ele_tight);
    scale_factors['B'].push_back(sf_btag_medium);

    scale_factors['C'].push_back(sf_ele_veto);
    scale_factors['C'].push_back(sf_muon_veto);
    scale_factors['C'].push_back(sf_btag_medium);


    scale_factors['D'].push_back(sf_ele_veto);
    scale_factors['D'].push_back(sf_muon_veto);
    scale_factors['D'].push_back(sf_btag_medium);

    scale_factors['E'].push_back(sf_ele_veto);
    scale_factors['E'].push_back(sf_muon_veto);
    scale_factors['E'].push_back(sf_btag_medium);







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
//Signal Regions
TH2D* h_MR_R2_LepMult_S;
TH1D* h_R2_LepMult_S;
TH1D* h_MR_LepMult_S;
TH2D* h_MR_R2_LepSev_S;
TH1D* h_R2_LepSev_S;
TH1D* h_MR_LepSev_S;
TH2D* h_MR_R2_Dijet_S;
TH1D* h_R2_Dijet_S;
TH1D* h_MR_Dijet_S;
TH2D* h_MR_R2_Mult_S;
TH1D* h_R2_Mult_S;
TH1D* h_MR_Mult_S;
TH2D* h_MR_R2_Sev_S;
TH1D* h_R2_Sev_S;
TH1D* h_MR_Sev_S;

//Signal Regions Ele-muon tight, btag Medium

TH1D* h_nEleTight_LepMult_S;
TH1D* h_nEleTight_LepSev_S;
TH1D* h_nEleTight_Dijet_S;
TH1D* h_nEleTight_Mult_S;
TH1D* h_nEleTight_Sev_S;

TH1D* h_nMuTight_LepMult_S;
TH1D* h_nMuTight_LepSev_S;
TH1D* h_nMuTight_Dijet_S;
TH1D* h_nMuTight_Mult_S;
TH1D* h_nMuTight_Sev_S;

TH1D* h_nbMedium_LepMult_S;
TH1D* h_nbMedium_LepSev_S;
TH1D* h_nbMedium_Dijet_S;
TH1D* h_nbMedium_Mult_S;
TH1D* h_nbMedium_Sev_S;

TH1D* h_nbTight_LepMult_S;
TH1D* h_nbTight_LepSev_S;
TH1D* h_nbTight_Dijet_S;
TH1D* h_nbTight_Mult_S;
TH1D* h_nbTight_Sev_S;

TH1D* h_jets_pt_LepMult_S;
TH1D* h_jets_pt_LepSev_S;
TH1D* h_jets_pt_Dijet_S;
TH1D* h_jets_pt_Mult_S;
TH1D* h_jets_pt_Sev_S;

TH1D* h_jets_eta_LepMult_S;
TH1D* h_jets_eta_LepSev_S;
TH1D* h_jets_eta_Dijet_S;
TH1D* h_jets_eta_Mult_S;
TH1D* h_jets_eta_Sev_S;

TH1D* h_jets_phi_LepMult_S;
TH1D* h_jets_phi_LepSev_S;
TH1D* h_jets_phi_Dijet_S;
TH1D* h_jets_phi_Mult_S;
TH1D* h_jets_phi_Sev_S;

TH1D* h_Megajets_pt_LepMult_S;
TH1D* h_Megajets_pt_LepSev_S;
TH1D* h_Megajets_pt_Dijet_S;
TH1D* h_Megajets_pt_Mult_S;
TH1D* h_Megajets_pt_Sev_S;

TH1D* h_Megajets_eta_LepMult_S;
TH1D* h_Megajets_eta_LepSev_S;
TH1D* h_Megajets_eta_Dijet_S;
TH1D* h_Megajets_eta_Mult_S;
TH1D* h_Megajets_eta_Sev_S;

TH1D* h_Megajets_phi_LepMult_S;
TH1D* h_Megajets_phi_LepSev_S;
TH1D* h_Megajets_phi_Dijet_S;
TH1D* h_Megajets_phi_Mult_S;
TH1D* h_Megajets_phi_Sev_S;

//Control Regions
TH2D* h_MR_R2_onelep;
TH1D* h_R2_onelep;
TH1D* h_MR_onelep;
TH2D* h_MR_R2_onelep_W;
TH1D* h_R2_onelep_W;
TH1D* h_MR_onelep_W;
TH2D* h_MR_R2_onelep_tt;
TH1D* h_R2_onelep_tt;
TH1D* h_MR_onelep_tt;
TH2D* h_MR_R2_dilep;
TH1D* h_R2_dilep;
TH1D* h_MR_dilep;
TH2D* h_MR_R2_vetolep;
TH1D* h_R2_vetolep;
TH1D* h_MR_vetolep;
TH2D* h_MR_R2_vetotau;
TH1D* h_R2_vetotau;
TH1D* h_MR_vetotau;
TH2D* h_MR_R2_onelepinv;
TH1D* h_R2_onelepinv;
TH1D* h_MR_onelepinv;
TH2D* h_MR_R2_dilepinv;
TH1D* h_R2_dilepinv;
TH1D* h_MR_dilepinv;
TH2D* h_MR_R2_photoninv;
TH1D* h_R2_photoninv;
TH1D* h_MR_photoninv;
TH2D* h_MR_R2_qcd;
TH1D* h_R2_qcd;
TH1D* h_MR_qcd;
TH2D* h_MR_R2_qcd_lowR2;
TH1D* h_R2_qcd_lowR2;
TH1D* h_MR_qcd_lowR2;
TH2D* h_MR_R2_qcd_presel;
TH1D* h_R2_qcd_presel;
TH1D* h_MR_qcd_presel;

//Signal Regions nJet/ht-AK4/nAK8jet
TH1D* h_njet_LepMult_S;
TH1D* h_nAK8jet_LepMult_S;
TH1D* h_njet_LepSev_S;
TH1D* h_nAK8jet_LepSev_S;
TH1D* h_njet_Dijet_S;
TH1D* h_nAK8jet_Dijet_S;
TH1D* h_njet_Mult_S;
TH1D* h_nAK8jet_Mult_S;
TH1D* h_njet_Sev_S;
TH1D* h_nAK8jet_Sev_S;

//Control Regions nJet
TH1D* h_njet_onelep;
TH1D* h_nAK8jet_onelep;
TH1D* h_njet_onelep_W;
TH1D* h_nAK8jet_onelep_W;
TH1D* h_njet_onelep_tt;
TH1D* h_nAK8jet_onelep_tt;
TH1D* h_njet_dilep;
TH1D* h_nAK8jet_dilep;
TH1D* h_njet_vetolep;
TH1D* h_nAK8jet_vetolep;
TH1D* h_njet_vetotau;
TH1D* h_nAK8jet_vetotau;
TH1D* h_njet_onelepinv;
TH1D* h_nAK8jet_onelepinv;
TH1D* h_njet_dilepinv;
TH1D* h_nAK8jet_dilepinv;
TH1D* h_njet_photoninv;
TH1D* h_nAK8jet_photoninv;
TH1D* h_njet_qcd;
TH1D* h_nAK8jet_qcd;
TH1D* h_njet_qcd_lowR2;
TH1D* h_nAK8jet_qcd_lowR2;
TH1D* h_njet_qcd_presel;
TH1D* h_nAK8jet_qcd_presel;


// Preselection
/*
TH1D* h_MET_P;
TH1D* h_ht_AK4_P;
TH1D* h_ht_AK8_P;
TH1D* h_njet_P;
TH1D* h_nAK8jet_P;
TH1D* h_nbTight_P;
TH1D* h_nbMedium_P;
TH1D* h_nbLoose_P;
TH1D* h_nw_P;
TH1D* h_nTop_P;
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

*/




//_______________________________________________________
//              Define Histograms here
void
Analysis::init_analysis_histos(const unsigned int& syst_nSyst, const unsigned int& syst_index)
{
 // h_gen_toppt      = new TH1D("h_gen_toppt", "h_gen_toppt", 50, 0, 1000);
   int nbn_MET = 16;
   int nbnMET = 6;
   int nbnHT = 7;
   int nbn_HT = 20;

  //int nbn_MTR = 8;
  int nbn_MR = 7;
  int nbn_R2 = 7;
  //int nbn_AK8J1pt = 17;
  int nbn_AK8J1pt = 7;
  int nbn_eta = 2;

  int nbn3DHT = 7;
  int nbn3DMET = 6;
  int nbnjmass = 5;

 // Double_t HT_bins[19] = {0, 200, 300, 400, 500, 600, 650, 700, 750, 800, 900, 1000, 1200, 1500, 2000, 3000};
  //Double_t bn_HTtmp[] = {400.,500.,600.,700.,750.,800.,850.,900.,950.,1000.,1500.};
 // Double_t* bnHT = 0;
 // bnHT = getVariableBinEdges(nbnHT+1,bn_HTtmp);

  // Double_t bn_HT_tmp[] = {0.,200.,400.,450.,500.,550.,600.,650.,700.,750.,800.,900.,1000.,1200.,1400.,1600.,1800.,2000.,2500.,3000.,10000.};
  // Double_t bn_HT_tmp[] = {400.,500.,600.,800.,1000.,1500.,2000.,2500.,3000.};
  // Double_t* bn_HT = 0;
   //bn_HT = getVariableBinEdges(nbn_HT+1,bn_HT_tmp);

  //Double_t bn_HT_tmp[] = {200.,400.,500.,600.,700.,800.,1000.,1200.,1400.,1600.,1800.,2000.,2500.,3000.,5000.};
  Double_t bn_HT_tmp[] = {0.,200.,400.,450.,500.,550.,600.,650.,700.,750.,800.,900.,1000.,1200.,1400.,1600.,1800.,2000.,2500.,3000.,4000.};
  Double_t* bn_HT = 0;
  bn_HT = getVariableBinEdges(nbn_HT+1,bn_HT_tmp);


  // Double_t bn_HTtmp[] = {400.,500.,600.,700.,800.,900.,1000.,1100.,1200.,1500.,2000.};
  Double_t bn_HTtmp[] = {200.,400.,500.,600.,800.,1000.,1500.,10000.};
  Double_t* bnHT = 0;
  bnHT = getVariableBinEdges(nbnHT+1,bn_HTtmp);


   //Double_t bn_AK8J1pt_tmp[] = {0.,200.,220.,240,260,280,300.,320.,340,360,380,400.,450,500.,700,1000.,1500.,2000.};
    Double_t bn_AK8J1pt_tmp[] = {0.,200.,300.,400.,500.,600.,800.,2000.};
   Double_t* bn_AK8J1pt = 0;
   bn_AK8J1pt = getVariableBinEdges(nbn_AK8J1pt+1,bn_AK8J1pt_tmp);

  Double_t bn_eta_tmp[] = {0.,1.5,2.5};
  Double_t* bn_eta = 0;
  bn_eta = getVariableBinEdges(nbn_eta+1,bn_eta_tmp);

  //Double_t bn_3DHTtmp[] = {400.,500.,600.,800.,1000.,1500.,10000.};
  Double_t bn_3DHTtmp[] = {200.,400.,500.,550,600.,800.,1500.,10000.};
  Double_t* bn3DHT = 0;
  bn3DHT = getVariableBinEdges(nbn3DHT+1,bn_3DHTtmp);

  //Double_t bn_3DMETtmp[] = {0.,100.,200.,300.,600.,1000.,10000.};
  Double_t bn_3DMETtmp[] = {0.,70.,110.,150.,200.,400.,10000.};
  Double_t* bn3DMET = 0;
  bn3DMET = getVariableBinEdges(nbn3DMET+1,bn_3DMETtmp);

  //Double_t bn_jmasstmp[] = {65.,105.,160.,210.,1000.};
    Double_t bn_jmasstmp[] = {0.,65.,105.,150.,210.,500.};
  Double_t* bnjmass = 0;
  bnjmass = getVariableBinEdges(nbnjmass+1,bn_jmasstmp);

  //Double_t bn_METtmp[] = {0.,100.,200.,300.,400.,600.,2000.};
  Double_t bn_METtmp[] = {0.,100.,200.,400.,600.,1000.,10000.};
  Double_t* bnMET = 0;
  bnMET = getVariableBinEdges(nbnMET+1,bn_METtmp);

  Double_t bn_MET_tmp[] = {0.,50.,100.,150.,200.,250.,300.,350.,400.,450.,500.,600.,700.,800.,1000.,2000.,10000.};
  Double_t* bn_MET = 0;
  bn_MET = getVariableBinEdges(nbn_MET+1,bn_MET_tmp);


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


//Signal Regions
  h_MR_R2_LepMult_S         = new TH2D("MR_R2_LepMult_S", ";MR_{AK4};R2_{AK4}",nbn_MR,bn_MR,nbn_R2,bn_R2);
  h_R2_LepMult_S            = new TH1D("R2_LepMult_S", ";R2_{AK4}",nbn_R2,bn_R2);
  h_MR_LepMult_S            = new TH1D("MR_LepMult_S", ";MR_{AK4}",nbn_MR,bn_MR);
  h_MR_R2_LepSev_S          = new TH2D("MR_R2_LepSev_S", ";MR_{AK4};R2_{AK4}",nbn_MR,bn_MR,nbn_R2,bn_R2);
  h_R2_LepSev_S            = new TH1D("R2_LepSev_S", ";R2_{AK4}",nbn_R2,bn_R2);
  h_MR_LepSev_S            = new TH1D("MR_LepSev_S", ";MR_{AK4}",nbn_MR,bn_MR);
  h_MR_R2_Dijet_S           = new TH2D("MR_R2_Dijet_S", ";MR_{AK4};R2_{AK4}",nbn_MR,bn_MR,nbn_R2,bn_R2);
  h_R2_Dijet_S              = new TH1D("R2_Dijet_S", ";R2_{AK4}",nbn_R2,bn_R2);
  h_MR_Dijet_S              = new TH1D("MR_Dijet_S", ";MR_{AK4}",nbn_MR,bn_MR);
  h_MR_R2_Mult_S            = new TH2D("MR_R2_Mult_S", ";MR_{AK4};R2_{AK4}",nbn_MR,bn_MR,nbn_R2,bn_R2);
  h_R2_Mult_S               = new TH1D("R2_Mult_S", ";R2_{AK4}",nbn_R2,bn_R2);
  h_MR_Mult_S               = new TH1D("MR_Mult_S", ";MR_{AK4}",nbn_MR,bn_MR);
  h_MR_R2_Sev_S            = new TH2D("MR_R2_Sev_S", ";MR_{AK4};R2_{AK4}",nbn_MR,bn_MR,nbn_R2,bn_R2);
  h_R2_Sev_S               = new TH1D("R2_Sev_S", ";R2_{AK4}",nbn_R2,bn_R2);
  h_MR_Sev_S               = new TH1D("MR_Sev_S", ";MR_{AK4}",nbn_MR,bn_MR);

  h_nEleTight_LepMult_S    = new TH1D("nEleTight_LepMult_S",     ";N_{jet}",                20, 0,  20);
  h_nEleTight_LepSev_S    = new TH1D("nEleTight_LepSev_S",     ";N_{jet}",                20, 0,  20);
  h_nEleTight_Dijet_S    = new TH1D("nEleTight_Dijet_S",     ";N_{jet}",                20, 0,  20);
  h_nEleTight_Mult_S    = new TH1D("nEleTight_Mult_S",     ";N_{jet}",                20, 0,  20);
  h_nEleTight_Sev_S    = new TH1D("nEleTight_Sev_S",     ";N_{jet}",                20, 0,  20);

  h_nMuTight_LepMult_S    = new TH1D("nMuTight_LepMult_S",     ";N_{jet}",                20, 0,  20);
  h_nMuTight_LepSev_S    = new TH1D("nMuTight_LepSev_S",     ";N_{jet}",                20, 0,  20);
  h_nMuTight_Dijet_S    = new TH1D("nMuTight_Dijet_S",     ";N_{jet}",                20, 0,  20);
  h_nMuTight_Mult_S    = new TH1D("nMuTight_Mult_S",     ";N_{jet}",                20, 0,  20);
  h_nMuTight_Sev_S    = new TH1D("nMuTight_Sev_S",     ";N_{jet}",                20, 0,  20);

  h_nbMedium_LepMult_S    = new TH1D("nbMedium_LepMult_S",     ";N_{jet}",                20, 0,  20);
  h_nbMedium_LepSev_S    = new TH1D("nbMedium_LepSev_S",     ";N_{jet}",                20, 0,  20);
  h_nbMedium_Dijet_S    = new TH1D("nbMedium_Dijet_S",     ";N_{jet}",                20, 0,  20);
  h_nbMedium_Mult_S    = new TH1D("nbMedium_Mult_S",     ";N_{jet}",                20, 0,  20);
  h_nbMedium_Sev_S    = new TH1D("nbMedium_Sev_S",     ";N_{jet}",                20, 0,  20);

  h_nbTight_LepMult_S    = new TH1D("nbTight_LepMult_S",     ";N_{jet}",                20, 0,  20);
  h_nbTight_LepSev_S    = new TH1D("nbTight_LepSev_S",     ";N_{jet}",                20, 0,  20);
  h_nbTight_Dijet_S    = new TH1D("nbTight_Dijet_S",     ";N_{jet}",                20, 0,  20);
  h_nbTight_Mult_S    = new TH1D("nbTight_Mult_S",     ";N_{jet}",                20, 0,  20);
  h_nbTight_Sev_S    = new TH1D("nbTight_Sev_S",     ";N_{jet}",                20, 0,  20);

  h_jets_pt_LepMult_S = new TH1D("jets_pt_LepMult_S",";p_{T, jets}",200,0,2000);
  h_jets_pt_LepSev_S = new TH1D("jets_pt_LepSev_S",";p_{T, jets}",200,0,2000);
  h_jets_pt_Dijet_S = new TH1D("jets_pt_Dijet_S",";p_{T, jets}",200,0,2000);
  h_jets_pt_Mult_S = new TH1D("jets_pt_Mult_S",";p_{T, jets}",200,0,2000);
  h_jets_pt_Sev_S = new TH1D("jets_pt_Sev_S",";p_{T, jets}",200,0,2000);

  h_jets_eta_LepMult_S = new TH1D("jets_eta_LepMult_S",";#eta_{jets}",480,-2.4,2.4);
  h_jets_eta_LepSev_S = new TH1D("jets_eta_LepSev_S",";#eta_{jets}",480,-2.4,2.4);
  h_jets_eta_Dijet_S = new TH1D("jets_eta_Dijet_S",";#eta_{jets}",480,-2.4,2.4);
  h_jets_eta_Mult_S = new TH1D("jets_eta_Mult_S",";#eta_{jets}",480,-2.4,2.4);
  h_jets_eta_Sev_S = new TH1D("jets_eta_Sev_S",";#eta_{jets}",480,-2.4,2.4);

  h_jets_phi_LepMult_S = new TH1D("jets_phi_LepMult_S",";#phi_{jets}",640,-3.2,3.2);
  h_jets_phi_LepSev_S = new TH1D("jets_phi_LepSev_S",";#phi_{jets}",640,-3.2,3.2);
  h_jets_phi_Dijet_S = new TH1D("jets_phi_Dijet_S",";#phi_{jets}",640,-3.2,3.2);
  h_jets_phi_Mult_S = new TH1D("jets_phi_Mult_S",";#phi_{jets}",640,-3.2,3.2);
  h_jets_phi_Sev_S = new TH1D("jets_phi_Sev_S",";#phi_{jets}",640,-3.2,3.2);

  h_Megajets_pt_LepMult_S = new TH1D("Megajets_pt_LepMult_S",";p_{T, Megajets}",200,0,2000);
  h_Megajets_pt_LepSev_S = new TH1D("Megajets_pt_LepSev_S",";p_{T, Megajets}",200,0,2000);
  h_Megajets_pt_Dijet_S = new TH1D("Megajets_pt_Dijet_S",";p_{T, Megajets}",200,0,2000);
  h_Megajets_pt_Mult_S = new TH1D("Megajets_pt_Mult_S",";p_{T, Megajets}",200,0,2000);
  h_Megajets_pt_Sev_S = new TH1D("Megajets_pt_Sev_S",";p_{T, Megajets}",200,0,2000);

  h_Megajets_eta_LepMult_S = new TH1D("Megajets_eta_LepMult_S",";#eta_{Megajets}",480,-2.4,2.4);
  h_Megajets_eta_LepSev_S = new TH1D("Megajets_eta_LepSev_S",";#eta_{Megajets}",480,-2.4,2.4);
  h_Megajets_eta_Dijet_S = new TH1D("Megajets_eta_Dijet_S",";#eta_{Megajets}",480,-2.4,2.4);
  h_Megajets_eta_Mult_S = new TH1D("Megajets_eta_Mult_S",";#eta_{Megajets}",480,-2.4,2.4);
  h_Megajets_eta_Sev_S = new TH1D("Megajets_eta_Sev_S",";#eta_{Megajets}",480,-2.4,2.4);

  h_Megajets_phi_LepMult_S = new TH1D("Megajets_phi_LepMult_S",";#phi_{Megajets}",640,-3.2,3.2);
  h_Megajets_phi_LepSev_S = new TH1D("Megajets_phi_LepSev_S",";#phi_{Megajets}",640,-3.2,3.2);
  h_Megajets_phi_Dijet_S = new TH1D("Megajets_phi_Dijet_S",";#phi_{Megajets}",640,-3.2,3.2);
  h_Megajets_phi_Mult_S = new TH1D("Megajets_phi_Mult_S",";#phi_{Megajets}",640,-3.2,3.2);
  h_Megajets_phi_Sev_S = new TH1D("Megajets_phi_Sev_S",";#phi_{Megajets}",640,-3.2,3.2);




// Control Regions
  h_MR_R2_onelep         = new TH2D("MR_R2_onelep", ";MR_{AK4};R2_{AK4}",nbn_MR,bn_MR,nbn_R2,bn_R2);
  h_R2_onelep            = new TH1D("R2_onelep", ";R2_{AK4}",nbn_R2,bn_R2);
  h_MR_onelep            = new TH1D("MR_onelep", ";MR_{AK4}",nbn_MR,bn_MR);
  h_MR_R2_onelep_W          = new TH2D("MR_R2_onelep_W", ";MR_{AK4};R2_{AK4}",nbn_MR,bn_MR,nbn_R2,bn_R2);
  h_R2_onelep_W            = new TH1D("R2_onelep_W", ";R2_{AK4}",nbn_R2,bn_R2);
  h_MR_onelep_W            = new TH1D("MR_onelep_W", ";MR_{AK4}",nbn_MR,bn_MR);
  h_MR_R2_onelep_tt           = new TH2D("MR_R2_onelep_tt", ";MR_{AK4};R2_{AK4}",nbn_MR,bn_MR,nbn_R2,bn_R2);
  h_R2_onelep_tt              = new TH1D("R2_onelep_tt", ";R2_{AK4}",nbn_R2,bn_R2);
  h_MR_onelep_tt              = new TH1D("MR_onelep_tt", ";MR_{AK4}",nbn_MR,bn_MR);
  h_MR_R2_dilep            = new TH2D("MR_R2_dilep", ";MR_{AK4};R2_{AK4}",nbn_MR,bn_MR,nbn_R2,bn_R2);
  h_R2_dilep               = new TH1D("R2_dilep", ";R2_{AK4}",nbn_R2,bn_R2);
  h_MR_dilep               = new TH1D("MR_dilep", ";MR_{AK4}",nbn_MR,bn_MR);
  h_MR_R2_vetolep            = new TH2D("MR_R2_vetolep", ";MR_{AK4};R2_{AK4}",nbn_MR,bn_MR,nbn_R2,bn_R2);
  h_R2_vetolep               = new TH1D("R2_vetolep", ";R2_{AK4}",nbn_R2,bn_R2);
  h_MR_vetolep              = new TH1D("MR_vetolep", ";MR_{AK4}",nbn_MR,bn_MR);
  h_MR_R2_vetotau         = new TH2D("MR_R2_vetotau", ";MR_{AK4};R2_{AK4}",nbn_MR,bn_MR,nbn_R2,bn_R2);
  h_R2_vetotau            = new TH1D("R2_vetotau", ";R2_{AK4}",nbn_R2,bn_R2);
  h_MR_vetotau            = new TH1D("MR_vetotau", ";MR_{AK4}",nbn_MR,bn_MR);
  h_MR_R2_onelepinv          = new TH2D("MR_R2_onelepinv", ";MR_{AK4};R2_{AK4}",nbn_MR,bn_MR,nbn_R2,bn_R2);
  h_R2_onelepinv            = new TH1D("R2_onelepinv", ";R2_{AK4}",nbn_R2,bn_R2);
  h_MR_onelepinv            = new TH1D("MR_onelepinv", ";MR_{AK4}",nbn_MR,bn_MR);
  h_MR_R2_dilepinv          = new TH2D("MR_R2_dilepinv", ";MR_{AK4};R2_{AK4}",nbn_MR,bn_MR,nbn_R2,bn_R2);
  h_R2_dilepinv              = new TH1D("R2_dilepinv", ";R2_{AK4}",nbn_R2,bn_R2);
  h_MR_dilepinv              = new TH1D("MR_dilepinv", ";MR_{AK4}",nbn_MR,bn_MR);
  h_MR_R2_photoninv            = new TH2D("MR_R2_photoninv", ";MR_{AK4};R2_{AK4}",nbn_MR,bn_MR,nbn_R2,bn_R2);
  h_R2_photoninv               = new TH1D("R2_photoninv", ";R2_{AK4}",nbn_R2,bn_R2);
  h_MR_photoninv               = new TH1D("MR_photoninv", ";MR_{AK4}",nbn_MR,bn_MR);
  h_MR_R2_qcd            = new TH2D("MR_R2_qcd", ";MR_{AK4};R2_{AK4}",nbn_MR,bn_MR,nbn_R2,bn_R2);
  h_R2_qcd               = new TH1D("R2_qcd", ";R2_{AK4}",nbn_R2,bn_R2);
  h_MR_qcd             = new TH1D("MR_qcd", ";MR_{AK4}",nbn_MR,bn_MR);
  h_MR_R2_qcd_lowR2            = new TH2D("MR_R2_qcd_lowR2", ";MR_{AK4};R2_{AK4}",nbn_MR,bn_MR,nbn_R2,bn_R2);
  h_R2_qcd_lowR2               = new TH1D("R2_qcd_lowR2", ";R2_{AK4}",nbn_R2,bn_R2);
  h_MR_qcd_lowR2             = new TH1D("MR_qcd_lowR2", ";MR_{AK4}",nbn_MR,bn_MR);
  h_MR_R2_qcd_presel            = new TH2D("MR_R2_qcd_presel", ";MR_{AK4};R2_{AK4}",nbn_MR,bn_MR,nbn_R2,bn_R2);
  h_R2_qcd_presel               = new TH1D("R2_qcd_presel", ";R2_{AK4}",nbn_R2,bn_R2);
  h_MR_qcd_presel             = new TH1D("MR_qcd_presel", ";MR_{AK4}",nbn_MR,bn_MR);

  //Signal Regions njetak4 ak8 ht
    h_njet_LepMult_S         = new TH1D("njet_LepMult_S",         ";N_{jet}",                20, 0,  20);
    h_nAK8jet_LepMult_S            = new TH1D("nAK8jet_LepMult_S",    ";N_{jet}",                20, 0,  20);
    h_njet_LepSev_S          = new TH1D("njet_LepSev_S",         ";N_{jet}",                20, 0,  20);
    h_nAK8jet_LepSev_S            = new TH1D("nAK8jet_LepSev_S",    ";N_{jet}",                20, 0,  20);
    h_njet_Dijet_S           = new TH1D("njet_Dijet_S",         ";N_{jet}",                20, 0,  20);
    h_nAK8jet_Dijet_S              = new TH1D("nAK8jet_Dijet_S",    ";N_{jet}",                20, 0,  20);
    h_njet_Mult_S            = new TH1D("njet_Mult_S",         ";N_{jet}",                20, 0,  20);
    h_nAK8jet_Mult_S               = new TH1D("nAK8jet_Mult_S",    ";N_{jet}",                20, 0,  20);
    h_njet_Sev_S            = new TH1D("njet_Sev_S",        ";N_{jet}",                20, 0,  20);
    h_nAK8jet_Sev_S               = new TH1D("nAK8jet_Sev_S",    ";N_{jet}",                20, 0,  20);

  // Control Regions
    h_njet_onelep         = new TH1D("njet_onelep",         ";N_{jet}",                20, 0,  20);
    h_nAK8jet_onelep            = new TH1D("nAK8jet_onelep",    ";N_{jet}",                20, 0,  20);
    h_njet_onelep_W          = new TH1D("njet_onelep_W",         ";N_{jet}",                20, 0,  20);
    h_nAK8jet_onelep_W            = new TH1D("nAK8jet_onelep_W",    ";N_{jet}",                20, 0,  20);
    h_njet_onelep_tt           = new TH1D("njet_onelep_tt",        ";N_{jet}",                20, 0,  20);
    h_nAK8jet_onelep_tt              = new TH1D("nAK8jet_onelep_tt",    ";N_{jet}",                20, 0,  20);
    h_njet_dilep            = new TH1D("njet_dilep",         ";N_{jet}",                20, 0,  20);
    h_nAK8jet_dilep               = new TH1D("nAK8jet_dilep",    ";N_{jet}",                20, 0,  20);
    h_njet_vetolep            = new TH1D("njet_vetolep",        ";N_{jet}",                20, 0,  20);
    h_nAK8jet_vetolep              = new TH1D("nAK8jet_vetolep",    ";N_{jet}",                20, 0,  20);
    h_njet_vetotau         = new TH1D("njet_vetotau",        ";N_{jet}",                20, 0,  20);
    h_nAK8jet_vetotau            = new TH1D("nAK8jet_vetotau",    ";N_{jet}",                20, 0,  20);
    h_njet_onelepinv          = new TH1D("njet_onelepinv",         ";N_{jet}",                20, 0,  20);
    h_nAK8jet_onelepinv            = new TH1D("nAK8jet_onelepinv",    ";N_{jet}",                20, 0,  20);
    h_njet_dilepinv          = new TH1D("njet_dilepinv",         ";N_{jet}",                20, 0,  20);
    h_nAK8jet_dilepinv              = new TH1D("nAK8jet_dilepinv",    ";N_{jet}",                20, 0,  20);
    h_njet_photoninv            = new TH1D("njet_photoninv",         ";N_{jet}",                20, 0,  20);
    h_nAK8jet_photoninv               = new TH1D("nAK8jet_photoninv",    ";N_{jet}",                20, 0,  20);
    h_njet_qcd            = new TH1D("njet_qcd",         ";N_{jet}",                20, 0,  20);
    h_nAK8jet_qcd             = new TH1D("nAK8jet_qcd",    ";N_{jet}",                20, 0,  20);
    h_njet_qcd_lowR2            = new TH1D("njet_qcd_lowR2",        ";N_{jet}",                20, 0,  20);
    h_nAK8jet_qcd_lowR2             = new TH1D("nAK8jet_qcd_lowR2",    ";N_{jet}",                20, 0,  20);
    h_njet_qcd_presel            = new TH1D("njet_qcd_presel",         ";N_{jet}",                20, 0,  20);
    h_nAK8jet_qcd_presel             = new TH1D("nAK8jet_qcd_presel",    ";N_{jet}",                20, 0,  20);








  /*  h_njet_P         = new TH1D("njet_P",         ";N_{jet}",                20, 0,  20);
  h_nAK8jet_P      = new TH1D("nAK8jet_P",      ";N_{jet}",                20, 0,  20);
  h_nbTight_P      = new TH1D("nbTight_P",     ";N_{jet}",                20, 0,  20);
  h_nbMedium_P     = new TH1D("nbMedium_P",     ";N_{jet}",                20, 0,  20);
  h_nbLoose_P      = new TH1D("nbLoose_P",     ";N_{jet}",                20, 0,  20);
  h_nEleVeto_P     = new TH1D("nEleVeto_P",     ";N_{jet}",                20, 0,  20);
  h_nEleTight_P    = new TH1D("nEleTight_P",     ";N_{jet}",                20, 0,  20);
  h_nEleMedium_P   = new TH1D("nEleMedium_P",     ";N_{jet}",                20, 0,  20);
  h_nEleLoose_P    = new TH1D("nEleLoose_P",     ";N_{jet}",                20, 0,  20);
  h_nMuTight_P     = new TH1D("nMuTight_P",     ";N_{jet}",                20, 0,  20);
  h_nMuMedium_P    = new TH1D("nMuMedium_P",     ";N_{jet}",                20, 0,  20);
  h_nMuSoft_P      = new TH1D("nMuSoft_P",     ";N_{jet}",                20, 0,  20);
  h_nTauVeto_P     = new TH1D("nTauVeto_P",     ";N_{jet}",                20, 0,  20);
  h_nIsoTrack_P    = new TH1D("nIsoTrack_P",     ";N_{jet}",                20, 0,  20);
  h_nPhoMedium_P   = new TH1D("nPhoMedium_P",     ";N_{jet}",                20, 0,  20);
  h_nw_P           = new TH1D("nw_P",           ";N_{W tag}",              20, 0,  20);
  h_nTop_P         = new TH1D("nTop_P",           ";N_{Top tag}",              20, 0,  20);
  h_ht_AK4_P       = new TH1D("ht_AK4_P",       ";H_{T}", nbn_HT, bn_HT);
  h_ht_AK8_P       = new TH1D("ht_AK8_P",       ";H_{T}", nbn_HT, bn_HT);
  h_MET_P=         new TH1D("MET_P",  ";H_{T}",    400,0,2000);
*/


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



/*  if (apply_all_cuts('P')) h_MR_R2->Fill(MR, R2, w);
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
//*****************************
w = sf_weight['A'];
if (apply_all_cuts('A')){
                      h_MR_R2_LepMult_S->Fill(MR, R2, w);
                      h_R2_LepMult_S->Fill(R2, w);
                      h_MR_LepMult_S->Fill(MR, w);
                      h_njet_LepMult_S->Fill(nJet,        w);
                      h_nAK8jet_LepMult_S->Fill(nJetAK8,     w);
                      h_nEleTight_LepMult_S ->Fill(nEleTight, w);
                      h_nMuTight_LepMult_S ->Fill(nMuTight, w);
                      h_nbMedium_LepMult_S ->Fill(nMediumBTag, w);
                      h_nbTight_LepMult_S ->Fill(nTightBTag, w);
                      for (size_t i=0; i<iJet.size(); ++i) {
                          h_jets_pt_LepMult_S->Fill(data.Jet[iJet[i]].pt_nom, w);
                          h_jets_eta_LepMult_S->Fill(data.Jet[iJet[i]].eta, w);
                          h_jets_phi_LepMult_S->Fill(data.Jet[iJet[i]].phi, w);
                        }

                      for (size_t i=0; i<2; ++i) {
                          h_Megajets_pt_LepMult_S->Fill(hemis_AK4[i].Pt(), w);
                          h_Megajets_eta_LepMult_S->Fill(hemis_AK4[i].Eta(), w);
                          h_Megajets_phi_LepMult_S->Fill(hemis_AK4[i].Phi(), w);
                        }


}

w = sf_weight['B'];
if (apply_all_cuts('B')){
                      h_MR_R2_LepSev_S->Fill(MR, R2, w);
                      h_R2_LepSev_S->Fill(R2, w);
                      h_MR_LepSev_S->Fill(MR, w);
                      h_njet_LepSev_S->Fill(nJet,        w);
                      h_nAK8jet_LepSev_S->Fill(nJetAK8,     w);
                      h_nEleTight_LepSev_S ->Fill(nEleTight, w);
                      h_nMuTight_LepSev_S ->Fill(nMuTight, w);
                      h_nbMedium_LepSev_S ->Fill(nMediumBTag, w);
                      h_nbTight_LepSev_S ->Fill(nTightBTag, w);
                      for (size_t i=0; i<iJet.size(); ++i) {
                          h_jets_pt_LepSev_S->Fill(data.Jet[iJet[i]].pt_nom, w);
                          h_jets_eta_LepSev_S->Fill(data.Jet[iJet[i]].eta, w);
                          h_jets_phi_LepSev_S->Fill(data.Jet[iJet[i]].phi, w);
                        }
                        for (size_t i=0; i<2; ++i) {
                            h_Megajets_pt_LepSev_S->Fill(hemis_AK4[i].Pt(), w);
                            h_Megajets_eta_LepSev_S->Fill(hemis_AK4[i].Eta(), w);
                            h_Megajets_phi_LepSev_S->Fill(hemis_AK4[i].Phi(), w);
                          }


}

w = sf_weight['C'];
if (apply_all_cuts('C')){
                      h_MR_R2_Dijet_S->Fill(MR, R2, w);
                      h_R2_Dijet_S->Fill(R2, w);
                      h_MR_Dijet_S->Fill(MR, w);
                      h_njet_Dijet_S->Fill(nJet,        w);
                      h_nAK8jet_Dijet_S->Fill(nJetAK8,     w);
                      h_nEleTight_Dijet_S ->Fill(nEleTight, w);
                      h_nMuTight_Dijet_S ->Fill(nMuTight, w);
                      h_nbMedium_Dijet_S ->Fill(nMediumBTag, w);
                      h_nbTight_Dijet_S ->Fill(nTightBTag, w);
                      for (size_t i=0; i<iJet.size(); ++i) {
                          h_jets_pt_Dijet_S->Fill(data.Jet[iJet[i]].pt_nom, w);
                          h_jets_eta_Dijet_S->Fill(data.Jet[iJet[i]].eta, w);
                          h_jets_phi_Dijet_S->Fill(data.Jet[iJet[i]].phi, w);
                        }

                        for (size_t i=0; i<2; ++i) {
                            h_Megajets_pt_Dijet_S->Fill(hemis_AK4[i].Pt(), w);
                            h_Megajets_eta_Dijet_S->Fill(hemis_AK4[i].Eta(), w);
                            h_Megajets_phi_Dijet_S->Fill(hemis_AK4[i].Phi(), w);
                          }



}
w = sf_weight['D'];
if (apply_all_cuts('D')){
                      h_MR_R2_Mult_S->Fill(MR, R2, w);
                      h_R2_Mult_S->Fill(R2, w);
                      h_MR_Mult_S->Fill(MR, w);
                      h_njet_Mult_S->Fill(nJet,        w);
                      h_nAK8jet_Mult_S->Fill(nJetAK8,     w);
                      h_nEleTight_Mult_S ->Fill(nEleTight, w);
                      h_nMuTight_Mult_S ->Fill(nMuTight, w);
                      h_nbMedium_Mult_S ->Fill(nMediumBTag, w);
                      h_nbTight_Mult_S ->Fill(nTightBTag, w);
                      for (size_t i=0; i<iJet.size(); ++i) {
                          h_jets_pt_Mult_S->Fill(data.Jet[iJet[i]].pt_nom, w);
                          h_jets_eta_Mult_S->Fill(data.Jet[iJet[i]].eta, w);
                          h_jets_phi_Mult_S->Fill(data.Jet[iJet[i]].phi, w);
                        }

                        for (size_t i=0; i<2; ++i) {
                            h_Megajets_pt_Mult_S->Fill(hemis_AK4[i].Pt(), w);
                            h_Megajets_eta_Mult_S->Fill(hemis_AK4[i].Eta(), w);
                            h_Megajets_phi_Mult_S->Fill(hemis_AK4[i].Phi(), w);
                          }

}

w = sf_weight['E'];
if (apply_all_cuts('E')){
                      h_MR_R2_Sev_S->Fill(MR, R2, w);
                      h_R2_Sev_S->Fill(R2, w);
                      h_MR_Sev_S->Fill(MR, w);
                      h_njet_Sev_S->Fill(nJet,        w);
                      h_nAK8jet_Sev_S->Fill(nJetAK8,     w);
                      h_nEleTight_Sev_S ->Fill(nEleTight, w);
                      h_nMuTight_Sev_S ->Fill(nMuTight, w);
                      h_nbMedium_Sev_S ->Fill(nMediumBTag, w);
                      h_nbTight_Sev_S ->Fill(nTightBTag, w);
                      for (size_t i=0; i<iJet.size(); ++i) {
                          h_jets_pt_Sev_S->Fill(data.Jet[iJet[i]].pt_nom, w);
                          h_jets_eta_Sev_S->Fill(data.Jet[iJet[i]].eta, w);
                          h_jets_phi_Sev_S->Fill(data.Jet[iJet[i]].phi, w);
                        }

                        for (size_t i=0; i<2; ++i) {
                            h_Megajets_pt_Sev_S->Fill(hemis_AK4[i].Pt(), w);
                            h_Megajets_eta_Sev_S->Fill(hemis_AK4[i].Eta(), w);
                            h_Megajets_phi_Sev_S->Fill(hemis_AK4[i].Phi(), w);
                          }

}

w = sf_weight['F'];
if (apply_all_cuts('F')){
                      h_MR_R2_onelep->Fill(MR, R2, w);
                      h_R2_onelep->Fill(R2, w);
                      h_MR_onelep->Fill(MR, w);
                      h_njet_onelep->Fill(nJet,        w);
                      h_nAK8jet_onelep->Fill(nJetAK8,     w);

}

w = sf_weight['I'];
if (apply_all_cuts('I')){
                      h_MR_R2_onelep_W->Fill(MR, R2, w);
                      h_R2_onelep_W->Fill(R2, w);
                      h_MR_onelep_W->Fill(MR, w);
                      h_njet_onelep_W->Fill(nJet,        w);
                      h_nAK8jet_onelep_W->Fill(nJetAK8,     w);
}

w = sf_weight['H'];
if (apply_all_cuts('H')){
                      h_MR_R2_onelep_tt->Fill(MR, R2, w);
                      h_R2_onelep_tt->Fill(R2, w);
                      h_MR_onelep_tt->Fill(MR, w);
                      h_njet_onelep_tt->Fill(nJet,        w);
                      h_nAK8jet_onelep_tt->Fill(nJetAK8,     w);


}

w = sf_weight['K'];
if (apply_all_cuts('K')){
                      h_MR_R2_dilep->Fill(MR, R2, w);
                      h_R2_dilep->Fill(R2, w);
                      h_MR_dilep->Fill(MR, w);
                      h_njet_dilep->Fill(nJet,        w);
                      h_nAK8jet_dilep->Fill(nJetAK8,     w);

}

w = sf_weight['M'];
if (apply_all_cuts('M')){
                      h_MR_R2_vetolep->Fill(MR, R2, w);
                      h_R2_vetolep->Fill(R2, w);
                      h_MR_vetolep->Fill(MR, w);
                      h_njet_vetolep->Fill(nJet,        w);
                      h_nAK8jet_vetolep->Fill(nJetAK8,     w);


}

w = sf_weight['N'];
if (apply_all_cuts('N')){
                      h_MR_R2_vetotau->Fill(MR, R2, w);
                      h_R2_vetotau->Fill(R2, w);
                      h_MR_vetotau->Fill(MR, w);
                      h_njet_vetotau->Fill(nJet,        w);
                      h_nAK8jet_vetotau->Fill(nJetAK8,     w);

}

w = sf_weight['O'];
if (apply_all_cuts('O')){
                      h_MR_R2_onelepinv->Fill(MR, R2, w);
                      h_R2_onelepinv->Fill(R2, w);
                      h_MR_onelepinv->Fill(MR, w);
                      h_njet_onelepinv->Fill(nJet,        w);
                      h_nAK8jet_onelepinv->Fill(nJetAK8,     w);

}

w = sf_weight['R'];
if (apply_all_cuts('R')){
                      h_MR_R2_dilepinv->Fill(MR, R2, w);
                      h_R2_dilepinv->Fill(R2, w);
                      h_MR_dilepinv->Fill(MR, w);
                      h_njet_dilepinv->Fill(nJet,        w);
                      h_nAK8jet_dilepinv->Fill(nJetAK8,     w);

}

w = sf_weight['X'];
if (apply_all_cuts('X')){
                      h_MR_R2_photoninv->Fill(MR, R2, w);
                      h_R2_photoninv->Fill(R2, w);
                      h_MR_photoninv->Fill(MR, w);
                      h_njet_photoninv->Fill(nJet,        w);
                      h_nAK8jet_photoninv->Fill(nJetAK8,     w);

}

w = sf_weight['U'];
if (apply_all_cuts('U')){
                      h_MR_R2_qcd->Fill(MR, R2, w);
                      h_R2_qcd->Fill(R2, w);
                      h_MR_qcd->Fill(MR, w);
                      h_njet_qcd->Fill(nJet,        w);
                      h_nAK8jet_qcd->Fill(nJetAK8,     w);

}

w = sf_weight['V'];
if (apply_all_cuts('V')){
                      h_MR_R2_qcd_lowR2->Fill(MR, R2, w);
                      h_R2_qcd_lowR2->Fill(R2, w);
                      h_MR_qcd_lowR2->Fill(MR, w);
                      h_njet_qcd_lowR2->Fill(nJet,        w);
                      h_nAK8jet_qcd_lowR2->Fill(nJetAK8,     w);

}

w = sf_weight['Y'];
if (apply_all_cuts('Y')){
                      h_MR_R2_qcd_presel->Fill(MR, R2, w);
                      h_R2_qcd_presel->Fill(R2, w);
                      h_MR_qcd_presel->Fill(MR, w);
                      h_njet_qcd_presel->Fill(nJet,        w);
                      h_nAK8jet_qcd_presel->Fill(nJetAK8,     w);

}











//*****************************



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
