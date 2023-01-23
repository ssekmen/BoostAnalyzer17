//-----------------------------------------------------------------------------
// File:        Analyzer.cc
// Created:     18-Jan-2016
// Author:      Janos Karancsi
//-----------------------------------------------------------------------------
#define PLOTTER
#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <vector>

#include "settings.h" // Define all Analysis specific settings here

int main(int argc, char** argv) {
  std::vector<std::string> vname_data = {};
  std::vector<std::string> vname_signal = {};

  // Get file list and histogram filename from command line
  //commandLine cmdline;
  //decodeCommandLine(argc, argv, cmdline, vname_data, vname_signal);
  bool isData = 0, isSignal = 0, isAPV = 0;
  std::string dirname = "";

  std::string outputfilename = "";
  std::vector<std::string> fileNames;
  for (int iarg=1; iarg<argc; ++iarg) {
    std::string arg = argv[iarg];
    if (outputfilename=="") {
        // 1st non-optional (i.e xxx=yyy) command line argument is output ifle
        outputfilename = arg;
        std::cout<<"output file is: "<<outputfilename<<std::endl;
    } else {
      // Otherwise add all root files to input file list
      if (std::string(arg).find(".root")!=std::string::npos) fileNames.push_back(arg);
      else std::cout<<"argument "<<arg<<" is not a root file"<<std::endl;
    }
  }

  // Read systematics file (only need number of lines)
  struct Systematics {
    unsigned int index = 0;
    unsigned int nSyst = 0;
  } syst;
  if (settings.varySystematics) {
    std::ifstream systFile(settings.systematicsFileName.c_str());
    if ( !systFile.good() ) error("unable to open systematics file: " + settings.systematicsFileName);
    std::string line;
    while ( std::getline(systFile, line) ) ++syst.nSyst;
  }

  eventBuffer ev;
  Variables   v(ev, 2017., isData, isSignal, "", isAPV);
  Analysis ana(v);

  ana.initialize1(settings.varySystematics, syst.nSyst, syst.index);
  ana.initialize2(settings.varySystematics, syst.nSyst, syst.index);

  for (auto in_file : fileNames) {
    std::cout<<"Loading histos from file: "<<in_file<<std::endl;
    ana.plotting.load_analysis_histos(in_file);
  }

  TFile *f = new TFile(outputfilename.c_str(),"RECREATE");
  ana.plotting.save_analysis_histos(1);
  f->Close();
  
  return 0;
}
