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
  std::vector<std::string> vname_signal = { "SMS" };

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
  int signal_index = 0;
  double m_gors=0, m_lsp=0;//, m_lsp1=0, m_lsp2=0;
  std::vector<double> mass1, mass2;
  //std::vector<double> mass3, mass4;

  for(int entry=0; entry < nevents; entry++){
  //for(int entry=0; entry < 3e2; entry++){
      if(entry%2000000 == 0) cout << entry << " was finished, " << (double)entry/nevents*100 << " [%]" << endl;
 
      ev.read(entry);
      ev.fillObjects();

      //signal_index = TString(filenames[0]).Contains("T2tt");
      if(TString(filenames[0]).Contains("T2tt") || TString(filenames[0]).Contains("TChi")) signal_index = 1;
      m_gors=0, m_lsp=0;//, m_lsp1=0, m_lsp2=0;
      mass1.clear();
      mass2.clear();
      //mass3.clear();
      //mass4.clear();
      for(size_t i=0; i<ev.GenPart.size(); ++i) {
        if(signal_index) {if((abs(ev.GenPart[i].pdgId) == 1000006) || (abs(ev.GenPart[i].pdgId) == 1000024)) mass1.push_back(ev.GenPart[i].mass);}  //stop or chargino
        else             {if((abs(ev.GenPart[i].pdgId) == 1000021)) mass1.push_back(ev.GenPart[i].mass);}  //gluino
        if(abs(ev.GenPart[i].pdgId) == 1000022) mass2.push_back(ev.GenPart[i].mass);											 //LSP
        //if(abs(ev.GenPart[i].pdgId) == 1000023) mass3.push_back(ev.GenPart[i].mass);										 //chi2
        //if(abs(ev.GenPart[i].pdgId) == 1000024) mass4.push_back(ev.GenPart[i].mass);											 //Chargino
      }

      m_gors = std::floor(mass1.at(0)/5)*5;
      m_lsp  = std::floor(mass2.at(0)/25)*25;
      //if(mass3.size()) m_lsp1  = std::floor(mass3.at(0)/5)*5;
      //if(mass4.size()) m_lsp2  = std::floor(mass4.at(0)/5)*5;

      //cout << "LSP : " << m_lsp << ", NLSP : " << m_lsp1 << ", mg : " << m_gors << ", mchargino : " << m_lsp2 << endl;

      //cout << m_gors << ", " << m_lsp << ", " << ev.Generator_weight << endl;
      vh_totweight_signal[signal_index]->Fill(m_gors, m_lsp, ev.Generator_weight);
  }
  //vh_totweight_signal.Write();
  ev.close();
  of.close();
  return 0;
}
