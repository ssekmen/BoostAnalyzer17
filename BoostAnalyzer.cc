//---------------------------------------------------------------------------
// File:        BoostAnalyzer.cc
// Description: Analyzer for simple ntuples, such as those created by
//              TheNtupleMaker
// Created:     Thu Jul 26 16:24:24 2018 by mkanalyzer.py
// Author:      Sezen Sekmen
//----------------------------------------------------------------------------
#include "tnm.h"
using namespace std;
//----------------------------------------------------------------------------
int main(int argc, char** argv)
{
  // If you want canvases to be visible during program execution, just
  // uncomment the line below
  //TApplication app("BoostAnalyzer", &argc, argv);

  // Get command line arguments
  commandLine cl(argc, argv);

  // Get names of ntuple files to be processed
  vector<string> filenames = fileNames(cl.filelist);

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
  //setStyle();
  TH1D *jetpt = new TH1D("jetpt", "jetpt", 50, 0, 1000);

  // -------------------------------------------------------------------------
  // Loop over events
  // -------------------------------------------------------------------------

  for(int entry=0; entry < nevents; entry++)
    {
      // read an event into event buffer
      ev.read(entry);

      // Uncomment the following line if you wish to copy variables into
      // structs. See the file eventBuffer.h to find out what structs
      // are available. Alternatively, you can call individual fill functions,
      // such as, ev.fillElectrons().
      ev.fillObjects();

      // analysis
      if (entry % 100 == 0) cout << entry << endl;

      for (int i=0; i<ev.FatJet.size(); i++) {
        jetpt->Fill(ev.FatJet[i].pt);
      }

    }

  ev.close();
  of.close();
  return 0;
}
