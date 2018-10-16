//---------------------------------------------------------------------------
// File:        BoostAnalyzer.cc
// Description: Analyzer for simple ntuples, such as those created by
//              TheNtupleMaker
// Created:     Thu Jul 26 16:24:24 2018 by mkanalyzer.py
// Author:      Sezen Sekmen
//----------------------------------------------------------------------------
#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <vector>

#include "tnm.h"
#include "TLorentzVector.h"
#include "include/AnalysisBase.h"

//#include "settings_Changgi.h"

using namespace std;
//----------------------------------------------------------------------------
int main(int argc, char** argv)
{
  const int debug = 0;
  if (debug) cout<<"Analyzer::main: start"<<endl;

  std::vector<std::string> vname_data = { "Run2015", "Run2016", "Run2017", "Run2018" };
  std::vector<std::string> vname_signal = { "SMS" };

  // If you want canvases to be visible during program execution, just
  // uncomment the line below
  //TApplication app("BoostAnalyzer", &argc, argv);

  // Get command line arguments
  commandLine cl(argc, argv);

  // Get names of ntuple files to be processed
  vector<string> filenames = getFilenames(cl.filelist);

  // Create tree reader
  itreestream stream(filenames, "Events");
  if ( !stream.good() ) error("can't read root input files");

  // Create a buffer to receive events from the stream
  // The default is to select all branches
  // Use second argument to select specific branches
  // Example:
  //   varlist = 'Jet_PT Jet_Eta Jet_Phi'
  //   ev = eventBuffer(stream, varlist)

  eventBuffer ev(stream);

  int nevents = ev.size();
  cout << "number of events: " << nevents << endl;

  // Create output file for histograms; see notes in header 
  outputFile of(cl.outputfilename);

  // -------------------------------------------------------------------------
  // Define histograms
  // -------------------------------------------------------------------------

  TH1::SetDefaultSumw2();

  //setStyle();
  TH1D *jetpt = new TH1D("jetpt", ";p_{T}", 200, 0, 1000);
  TH1D *jetmass = new TH1D("jetmass", ";mass_{jet}", 200, 0, 1000);
  //TH1D *htau21 = new TH1D("htau21", ";tau21", 100, 0, 1);
  TH1D *htau32 = new TH1D("htau32", ";tau32", 100, 0, 1);
  TH1D *htau42 = new TH1D("htau42", ";tau42", 100, 0, 1);

  TH1D *Elept = new TH1D("Elept", ";p_{T}", 200, 0, 1000);
  TH1D *Mupt  = new TH1D("Mupt",  ";p_{T}", 200, 0, 1000);

  TH1D *nEle = new TH1D("nEle", ";nEle", 10, 0, 10);
  TH1D *nMu  = new TH1D("nMu",  ";nMu",  10, 0, 10);

  TH1D *ElectronPairMass = new TH1D("ElectronPairMass", ";Mass_{ee}", 100, 0, 500);
  TH1D *MuonPairMass = new TH1D("MuonPairMass", ";Mass_{#mu#mu}", 100, 0, 500);

  TH1D *hMR	= new TH1D("hMR",	";MR",	200, 0, 2000);
  TH1D *hMTR= new TH1D("hMTR", ";MTR", 200, 0, 2000);
  TH1D *hR	= new TH1D("hR",		";R",		10, 0, 2);
  TH1D *hR2	= new TH1D("hR2",	";R2",	10, 0, 2);
  // -------------------------------------------------------------------------
  // Loop over events
  // -------------------------------------------------------------------------

  TLorentzVector lep1, lep2, lep, jet;
  std::vector<TLorentzVector> selected_Jets;
  std::vector<TLorentzVector> selected_Electrons;
  std::vector<TLorentzVector> selected_Muons;
  //std::vector<TLorentzVector> selected_leptons;
  //std::vector<TLorentzVector> hemis_AK4;
  //TVector3 shifted_met;

  //float MR, MTR, R, R2;

  //for(int entry=0; entry < nevents; entry++)
  for(int entry=0; entry < 1e4; entry++)
    {
      ev.read(entry);
      ev.fillObjects();

      // analysis
      if (entry % 100000 == 0) cout << entry << " is running, " << (float)entry/nevents*100 << " [%] is finished" << endl;
      if (!ev.Flag_goodVertices) continue;
      if (!ev.Flag_globalTightHalo2016Filter) continue;
      if (!ev.Flag_HBHENoiseFilter) continue;
      if (!ev.Flag_HBHENoiseIsoFilter) continue;
      if (!ev.Flag_EcalDeadCellTriggerPrimitiveFilter) continue;
      if (!ev.Flag_eeBadScFilter) continue;
      if (!ev.Flag_BadPFMuonFilter) continue;
      if (!ev.Flag_BadChargedCandidateFilter) continue;
      //if (!) continue;
      selected_Electrons.clear();
      selected_Muons.clear();
      //selected_leptons.clear();
      selected_Jets.clear();
      //hemis_AK4.clear();
      lep1.SetPxPyPzE(0,0,0,0);
      lep2.SetPxPyPzE(0,0,0,0);
      lep.SetPxPyPzE(0,0,0,0);
      jet.SetPxPyPzE(0,0,0,0);
      //MR = -9999;
      //MTR = -9999;
      //R = -9999;
      //R2 = -9999;

      for (size_t i=0; i<ev.FatJet.size(); ++i) {
        jetpt->Fill(ev.FatJet[i].pt);
        //tau21->Fill(ev.FatJet[i].tau2/ev.FatJet[i].tau1);
        htau32->Fill(ev.FatJet[i].tau3/ev.FatJet[i].tau2);
        htau42->Fill(ev.FatJet[i].tau4/ev.FatJet[i].tau2);
        if(ev.FatJet[i].pt > 400 && ev.FatJet[i].tau3/ev.FatJet[i].tau2 < 0.46) jetmass->Fill(ev.FatJet[i].msoftdrop);
      }
      if(tau21.size()) cout << tau21.size() << endl;

      for(size_t i=0; i<ev.Jet.size(); ++i) {
				if(ev.Jet[i].jetId != 2) continue;
				if(ev.Jet[i].pt <= 30) continue;
				if(ev.Jet[i].eta > 2.4) continue;
        jet.SetPtEtaPhiM(ev.Jet[i].pt, ev.Jet[i].eta, ev.Jet[i].phi, ev.Jet[i].mass);
        selected_Jets.push_back(jet);  
			}
      if(selected_Jets.size() < 2) continue;

/*
      if(selected_Jets.size() >= 2) hemis_AK4 = Razor::CombineJets(selected_Jets);
      if(hemis_AK4.size() == 2) {
        shifted_met.SetPtEtaPhi(ev.MET_pt, 0, ev.MET_phi);
        MR	= Razor::CalcMR(hemis_AK4[0], hemis_AK4[1]);
        MTR = Razor::CalcMTR(hemis_AK4[0], hemis_AK4[1], shifted_met);
        R   = MTR/MR; 
        R2  = R*R;
      }
*/
      hMR->Fill(MR);
      hMTR->Fill(MTR);
      hR->Fill(R);
      hR2->Fill(R2);

      for (size_t i=0; i<ev.Electron.size(); ++i) {
        lep1.SetPtEtaPhiM(ev.Electron[i].pt, ev.Electron[i].eta, ev.Electron[i].phi, ev.Electron[i].mass);
        if((ev.Electron[i].mvaFall17Iso_WPL) && ev.Electron[i].pt >= 10 && ev.Electron[i].miniPFRelIso_all/ ev.Electron[i].pt < 0.1 && abs(ev.Electron[i].dxy) < 0.05 && abs(ev.Electron[i].dz) < 0.1){
          Elept->Fill(ev.Electron[i].pt);
          selected_Electrons.push_back(lep1);  
        }
      }
			nEle->Fill(selected_Electrons.size());
      for(size_t i=0, n=selected_Electrons.size(); i<n; ++i) {
				lep += selected_Electrons[i];
      }
      if(selected_Electrons.size() == 2) ElectronPairMass->Fill(lep.M()); // Need to fix

      for (size_t i=0; i<ev.Muon.size(); ++i) {
        lep2.SetPtEtaPhiM(ev.Muon[i].pt, ev.Muon[i].eta, ev.Muon[i].phi, ev.Muon[i].mass);
        if((ev.Muon[i].softId) && ev.Muon[i].pt >= 5 && ev.Muon[i].miniPFRelIso_all/ev.Muon[i].pt < 0.2 && abs(ev.Muon[i].dxy) < 0.2 && abs(ev.Muon[i].dz) < 0.5 && ev.Muon[i].eta < 2.4){
          Mupt->Fill(ev.Muon[i].pt);
          selected_Muons.push_back(lep2);  
        }
      }
      nMu->Fill(selected_Muons.size());
      for(size_t i=0, n=selected_Muons.size(); i<n; ++i){
			  lep += selected_Muons[i];
      }
      if(selected_Muons.size() == 2) MuonPairMass->Fill(lep.M()); // Need to fix
    }

  ev.close();
  of.close();
  return 0;
}
