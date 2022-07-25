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
//#include "include/AnalysisBase.h"
#include "include/Razor.h"

//#include "settings_Changgi.h"

using namespace std;
//----------------------------------------------------------------------------
int main(int argc, char** argv)
{
  const int debug = 0;
  if (debug) cout<<"Analyzer::main: start"<<endl;

  std::vector<std::string> vname_data = { "Run2015", "Run2016", "Run2017", "Run2018" };
  std::vector<std::string> vname_signal = { "SMS", "TChi", "T2", "T4", "T5", "T1", "T6" };

  // If you want canvases to be visible during program execution, just
  // uncomment the line below
  //TApplication app("BoostAnalyzer", &argc, argv);

  // Get command line arguments
  commandLine cl(argc, argv);

  // Get names of ntuple files to be processed
  vector<string> filenames = getFilenames(cl.filelist);
  TString samplename(cl.dirname);
  cout << samplename << endl;

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
  //outputFile of(cl.outputfilename);
  outputFile of(cl.outputfilename);

  // -------------------------------------------------------------------------
  // Define histograms
  // -------------------------------------------------------------------------

  TH1::SetDefaultSumw2();
  std::vector<TH2D*> vh_totweight_signal;
  Double_t gluinoBins[202]; for (int i=0; i<202; ++i) gluinoBins[i] = (i-0.5)*25;
  Double_t stopBins[402];   for (int i=0; i<402; ++i) stopBins[i] = (i-0.5)*5;
  vh_totweight_signal.push_back(new TH2D("totweight_T1tttt", "T1tttt or T5ttcc or T5tttt;M_{#tilde{g}} (GeV);M_{#tilde{#chi}^{0}} (GeV);Total Weight", 201,gluinoBins, 201,gluinoBins));
  vh_totweight_signal.push_back(new TH2D("totweight_T2tt", "T2tt;M_{#tilde{s}} (GeV);M_{#tilde{#chi}^{0}} (GeV);Total Weight", 401,stopBins, 401,stopBins));
  vh_totweight_signal.push_back(new TH2D("totweight_TChiHH", "TChiHH;M_{#tilde{#chi}_{2}^{0}} (GeV);M_{#tilde{#chi}_{1}^{0}} (GeV);Total Weight", 401,stopBins, 401,stopBins));
  vh_totweight_signal.push_back(new TH2D("totweight_TChi", "TChi;M_{#tilde{#chi}_{3}^{0}} (GeV);M_{#tilde{#chi}_{2}^{0}} (GeV);Total Weight", 401,stopBins, 401,stopBins));
  int signal_index = 0;
  double m_gors=0, m_lsp=0;
  std::vector<double> mass1, mass2;

  for(int entry=0; entry < nevents; entry++){
      if(entry%2000000 == 0) cout << entry << " was finished, " << (double)entry/nevents*100 << " [%]" << endl;
 
      ev.read(entry);
      ev.fillObjects();

      if(TString(filenames[0]).Contains("T2")) signal_index = 1;
      if(TString(filenames[0]).Contains("TChi")) signal_index = 3;
      if(TString(filenames[0]).Contains("TChiWH")) signal_index = 2;
      m_gors=0, m_lsp=0;
      mass1.clear();
      mass2.clear();

      for(size_t i=0; i<ev.GenPart.size(); ++i) {
        if(signal_index == 1)   {if((abs(ev.GenPart[i].pdgId) == 1000006) || (abs(ev.GenPart[i].pdgId) == 1000005)) mass1.push_back(ev.GenPart[i].mass);}  //stop or chargino
        else if(signal_index==2){if((abs(ev.GenPart[i].pdgId) == 1000023)) mass1.push_back(ev.GenPart[i].mass);}  //neutralino2
        else if(signal_index==3){if((abs(ev.GenPart[i].pdgId) == 1000023)) mass1.push_back(ev.GenPart[i].mass); if((abs(ev.GenPart[i].pdgId) == 1000025)) mass2.push_back(ev.GenPart[i].mass);}  //neutralino2
        else                    {if((abs(ev.GenPart[i].pdgId) == 1000021)) mass1.push_back(ev.GenPart[i].mass);}  //gluino
        //if(TString(filenames[0]).Contains("T5qqqqZH") && abs(ev.GenPart[i].pdgId) == 1000023) mass2.push_back(ev.GenPart[i].mass);
        if(abs(ev.GenPart[i].pdgId) == 1000022) mass2.push_back(ev.GenPart[i].mass);											 //LSP
      }

      m_gors = std::floor(mass1.at(0)/5)*5;
      m_lsp  = std::floor(mass2.at(0)/25)*25;

      vh_totweight_signal[signal_index]->Fill(m_gors, m_lsp, ev.Generator_weight);
  }
  ev.close();
  of.close();
  return 0;
}
