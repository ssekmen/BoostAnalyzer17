//-----------------------------------------------------------------------------
// File:        Analyzer.cc
// Created:     24-Nov-2015
// Author:      Janos Karancsi
//-----------------------------------------------------------------------------
#include "settings_Janos.h" // Define all Analysis specific settings here
#include "include/tnm.h"

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <signal.h> // To be able to end looping on events earlier (with Ctrl+C), but save all histos and exit normally
#include <unistd.h>
#include <vector>
volatile sig_atomic_t sigint = 0;
void catch_sigint(int sig){ sigint++; if (sigint>1) exit(1); }

int main(int argc, char** argv) {
  std::cout<<"UnixTime-Start: "<<std::time(0)<<std::endl;
  const int debug = 0;
  if (debug) std::cout<<"Analyzer::main: start"<<std::endl;

  signal(SIGINT, catch_sigint);

  // List names in filenames from which the code can decide if it is data or signal
  // For the rest it's assumed it's background MC
  // if .txt file is given as input then from the directory name we can already tell
  //std::vector<std::string> vname_data = { "Run2015", "Run2016", "Run2017", "Run2018" };
  std::vector<std::string> vname_data = { "JetHT", "SingleMuon", "SingleElectron", "MET", "SinglePhoton", "HTMHT", "EGamma", "Run2016", "Run2017", "Run2018"};
  std::vector<std::string> vname_signal = { "SMS", "T1", "T2", "T5", "T6", "TChi" }; // SMS

  // ------------------------------
  // -- Parse command line stuff --
  // ------------------------------

  // Get file list and histogram filename from command line
  commandLine cmdline(argc, argv, vname_data, vname_signal);
  if (debug) std::cout<<"Analyzer::main: decodeCommandLine ok"<<std::endl;
  std::cout<<"Year: "<<cmdline.year<<std::endl;

  //itreestream stream(cmdline.fileNames, settings.runOnSkim ? "B2GTree" : "B2GTTreeMaker/B2GTree", 2000);
  itreestream stream(cmdline.fileNames, "Events");
  if ( !stream.good() ) error("can't read root input files");

  if ( cmdline.isData ) std::cout<<"Running on Data."<<std::endl;
  if ( cmdline.isBkg ) std::cout<<"Running on Background MC."<<std::endl;
  if ( cmdline.isSignal ) std::cout<<"Running on Signal MC."<<std::endl;

  // Get number of events to be read
  //int nevents = stream.size();
  eventBuffer ev(stream);
  Variables   v(ev, cmdline.year, cmdline.isData, cmdline.isSignal, cmdline.dirname);


  // Select variables to be read
  //eventBuffer data;
  //settings.selectVariables(stream, data);
  if (debug) std::cout<<"Analyzer::main: selectVariables ok"<<std::endl;

  // Constuct the Analysis methods (with Plotting specified in settings.h)
  Analysis ana(v);

  // ---------------------------------------------------------------------------
  // -- output file                                                           --
  // ---------------------------------------------------------------------------

  /*
    Notes:

    1. Use
    ofile = outputFile(cmdline.outputfile, stream)

    to skim events to output file in addition to writing out histograms.

    2. Use
    ofile.write(event-weight)

    to specify that the current event is to be added to the output file.
    If omitted, the event-weight is defaulted to 1.

    3. Use
    ofile.count(cut-name, event-weight)

    to keep track, in the count histogram, of the number of events
    passing a given cut. If omitted, the event-weight is taken to be 1.
    If you want the counts in the count histogram to appear in a given
    order, specify the order, before entering the event loop, as in
    the example below

    ofile.count("NoCuts", 0)
    ofile.count("GoodEvent", 0)
    ofile.count("Vertex", 0)
    ofile.count("MET", 0)
  */

  outputFile* ofile;
  if ( settings.saveSkimmedNtuple ) {
    std::cout<<"saveSkimmedNtuple (settings): true"<<std::endl;
    ofile = new outputFile(cmdline.outputfilename, ev);
  } else {
    ofile = new outputFile(cmdline.outputfilename);
    std::cout<<"saveSkimmedNtuple (settings): false"<<std::endl;
  }
  TDirectory* out_dir = gDirectory;

  if (cmdline.noPlots) {
    std::cout<<"noPlots (cmdline): true"<<std::endl;
    std::cout<<"--> Will not save analysis histos"<<std::endl;
  }
  if (debug) std::cout<<"Analyzer::main: output file ok"<<std::endl;

  // ---------------------------------------------------------------------------
  // -- Read systematics file                                                 --
  // ---------------------------------------------------------------------------

  // Initialize all systemtics variables (0 = default/mean, no variation)
  struct Systematics {
    unsigned int index = 0;
    unsigned int nSyst = 0;
    std::vector<double> nSigmaLumi        = std::vector<double>(1,0);
    std::vector<double> nSigmaTopPt       = std::vector<double>(1,0);
    std::vector<double> nSigmaISR         = std::vector<double>(1,0);
    std::vector<double> nSigmaPU          = std::vector<double>(1,0);
    std::vector<double> nSigmaAlphaS      = std::vector<double>(1,0);
    std::vector<double> nSigmaScale       = std::vector<double>(1,0);
    std::vector<double> nSigmaLostLep     = std::vector<double>(1,0);
    std::vector<double> nSigmaTrigger     = std::vector<double>(1,0);
    std::vector<double> nSigmaJES         = std::vector<double>(1,0);
    std::vector<double> nSigmaJER         = std::vector<double>(1,0);
    std::vector<double> nSigmaRestMET     = std::vector<double>(1,0);
    std::vector<double> nSigmaRescaleAK8  = std::vector<double>(1,0);
    std::vector<std::vector<double> > nSigmaSFs = 
      std::vector<std::vector<double> >(settings.nSigmaScaleFactors, std::vector<double>(1,0));
    std::vector<unsigned int> numScale    = std::vector<unsigned int>(1,0);
    std::vector<unsigned int> numPdf      = std::vector<unsigned int>(1,0);
  } syst;

  if (settings.varySystematics) {
    std::cout<<"varySystematics    (settings): true"<<std::endl;
    std::cout<<"nSigmaScaleFactors (settings): "<<settings.nSigmaScaleFactors<<std::endl;
    std::cout<<"systematicsFileName (settings): "<<settings.systematicsFileName<<std::endl;
    std::ifstream systFile(settings.systematicsFileName.c_str());
    if ( !systFile.good() ) error("unable to open systematics file: " + settings.systematicsFileName);

    // Read all nSigmas, nums
    double dbl = 0;
    unsigned int uint = 0;
    std::string line;
    std::cout<<"Systematics read from file:"<<std::endl;
    while ( std::getline(systFile, line) ) {
      ++syst.nSyst;
      std::stringstream nth_line;
      nth_line<<line;
      nth_line>>dbl; syst.nSigmaLumi.push_back(dbl);
      nth_line>>dbl; syst.nSigmaTopPt.push_back(dbl);
      nth_line>>dbl; syst.nSigmaISR.push_back(dbl);
      nth_line>>dbl; syst.nSigmaPU.push_back(dbl);
      nth_line>>dbl; syst.nSigmaAlphaS.push_back(dbl);
      nth_line>>dbl; syst.nSigmaScale.push_back(dbl);
      nth_line>>dbl; syst.nSigmaLostLep.push_back(dbl);
      nth_line>>dbl; syst.nSigmaTrigger.push_back(dbl);
      nth_line>>dbl; syst.nSigmaJES.push_back(dbl);
      nth_line>>dbl; syst.nSigmaJER.push_back(dbl);
      nth_line>>dbl; syst.nSigmaRestMET.push_back(dbl);
      nth_line>>dbl; syst.nSigmaRescaleAK8.push_back(dbl);
      for (int i=0; i<settings.nSigmaScaleFactors; ++i) {
        nth_line>>dbl; syst.nSigmaSFs[i].push_back(dbl);
      }
      nth_line>>uint; syst.numScale.push_back(uint);
      nth_line>>uint; syst.numPdf.push_back(uint);
      std::cout<<" line "<<syst.nSyst<<": "<<line<<std::endl;
    }
    std::cout<<std::endl;

  } else {
    std::cout<<"varySystematics (settings): false"<<std::endl;
  }
  if (debug) std::cout<<"Analyzer::main: read systematics ok"<<std::endl;


  // ---------------------------------------------------------------------------
  // -- Read and apply JSON file (Data)                                       --
  // ---------------------------------------------------------------------------

  std::map<int, std::map<int, bool> > json_run_ls;
  if (settings.useJSON) {
    std::cout<<"useJSON (settings): true"<<std::endl;
    std::cout<<"jsonFileName (settings): "<<settings.jsonFileName<<std::endl;
    std::ifstream jsonFile(settings.jsonFileName.c_str());
    if ( !jsonFile.good() ) error("unable to open systematics file: " + settings.jsonFileName);

    std::string line;
    int run, ls_low, ls_high;
    while ( std::getline(jsonFile, line, ' ') ) {
      if (TString(line).Contains("\"")) {
        std::stringstream run_str;
        run_str<<line.substr(line.find("\"")+1, 6);
        run_str>>run;
      } else {
        if (TString(line).Contains("[")) {
          std::stringstream ls_low_str;
          while (line.find("[")!=std::string::npos) line.erase(line.find("["),1);
          ls_low_str<<line;
          ls_low_str>>ls_low;
        } else if (TString(line).Contains("]")) {
          std::stringstream ls_high_str;
          ls_high_str<<line;
          ls_high_str>>ls_high;
          for (int ls=ls_low; ls<=ls_high; ++ls)
            json_run_ls[run].insert(std::pair<int, bool>(ls, 1));
        }
      }
    }
  } else {
    std::cout<<"useJSON (settings): false"<<std::endl;
  }
  if (debug) std::cout<<"Analyzer::main: load JSON file ok"<<std::endl;


  // ---------------------------------------------------------------------------
  // -- Declare histograms                                                    --
  // ---------------------------------------------------------------------------

  // Histogram weight
  TH1::SetDefaultSumw2();

  // Histograms are defined in Plotting_UserName.h and include/PlottingBase.h
  // The Plotting class uses the SmartHistos class for drawing
  // which has methods to define histogram and their filling/cuts/binning/colors etc
  // Common methods in the analysis (weightin/scale factors etc) are defined in include/Analysis.h
  // and their subclasses

  ana.initialize(settings.varySystematics, syst.nSyst, syst.index);
  if (debug) std::cout<<"Analyzer::main: ana.initialize() ok"<<std::endl;

  // --------------------------------------------------------------
  // -- Calculate the normalization factor for the event weights --
  // -- The original MC weight will be divided by this quantity  --
  // --------------------------------------------------------------

  std::cout<<std::endl;
  double weightnorm = 1;
  std::string xSecFileName;
  double intLumi = 0;
  TString samplename(cmdline.dirname);
  std::cout<<samplename<<std::endl;
  if ( cmdline.isBkg ) {
    if(cmdline.year==2018)      intLumi = 63670;
    else if(cmdline.year==2017) intLumi = 41529;
    else                        intLumi = 35867;
    std::cout<<"intLumi (settings): "<<intLumi<<std::endl; // given in settings.h

    double xsec = 0, totweight = 0;
    //if (settings.useXSecFileForBkg&&settings.runOnSkim) {
    if (settings.useXSecFileForBkg) {
      std::cout<<"useXSecFileForBkg (settings): true"<<std::endl; // given in settings.h
      if(cmdline.year==2018) xSecFileName = "include/BackGroundXSec2018.txt";
      else if(cmdline.year==2017) xSecFileName = "include/BackGroundXSec2017.txt";
      else xSecFileName = "include/BackGroundXSec2016.txt";
      std::pair<double, double> values = ana.weighting.get_xsec_totweight_from_txt_file(xSecFileName);
      xsec = values.first;
      totweight = values.second;
      std::cout<<"xsec      (txt file): "<<xsec<<std::endl;
      std::cout<<"totweight (txt file): "<<totweight<<std::endl;
    } else {
      std::cout<<"useXSecFileForBkg (settings): false"<<std::endl; // given in settings.h
      xsec = ana.weighting.get_xsec_from_ntuple(cmdline.fileNames, settings.runOnSkim); // given in settings.h
      std::cout<<"xsec      (ntuple): "<<xsec<<std::endl;
      totweight = ana.weighting.get_totweight_from_ntuple(cmdline.allFileNames, settings.runOnSkim); // weight histo name given in settings.h
      std::cout<<"totweight (ntuple): "<<totweight<<std::endl;
    }
    if ( xsec==0 || totweight==0 ) return 1;

    weightnorm = (intLumi*xsec)/totweight;
    std::cout<<"weightnorm (calc): "<<weightnorm<<std::endl;
  } else if ( cmdline.isSignal ) {
    std::cout<<"intLumi (settings): "<<intLumi<<std::endl; // given in settings.h
    ana.weighting.calc_signal_weightnorm(cmdline.allFileNames, intLumi, settings.varySystematics, out_dir);
  }
  if (debug) std::cout<<"Analyzer::main: calc lumi weight norm ok"<<std::endl;

  std::vector<double> scale_weight_norm;
  if ( settings.varySystematics ) {
    std::string line;
    std::ifstream scaleNormFile("include/scalenorm.txt");
    while ( std::getline(scaleNormFile, line) ) {
      std::stringstream nth_line;
      nth_line<<line;
      double norm1, norm2, norm3, norm4, norm5, norm6;
      std::string samplename;
      nth_line>>norm1;
      nth_line>>norm2;
      nth_line>>norm3;
      nth_line>>norm4;
      nth_line>>norm5;
      nth_line>>norm6;
      nth_line>>samplename;
      if (cmdline.dirname==samplename) {
        std::cout<<"Scale normalizations found: "<<norm1<<" "<<norm2<<" "<<norm3<<" "<<norm4<<" "<<norm5<<" "<<norm6<<" "<<samplename<<std::endl;
        scale_weight_norm.push_back(norm1);
        scale_weight_norm.push_back(norm2);
        scale_weight_norm.push_back(norm3);
        scale_weight_norm.push_back(norm4);
        scale_weight_norm.push_back(norm5);
        scale_weight_norm.push_back(norm6);
        break;
      }
    }
  }
  if (debug) std::cout<<"Analyzer::main: read factor/renorm scale weight normalization ok"<<std::endl;

  // ---------------------------------------
  // --- ScaleFectors/Reweighting        ---
  // ---------------------------------------

  // Top pt reweighting
  bool doTopPtReweighting = false;
  if ( settings.doTopPtReweighting && samplename.Contains("TT_powheg-pythia8")) {
    std::cout<<"doTopPtReweighting (settings): true"<<std::endl;    
    doTopPtReweighting = true;
  } else {
    std::cout<<"doTopPtReweighting (settings): false"<<std::endl;
  }

  // ISR reweighting
  bool doISRReweighting = false;
  if ( settings.doISRReweighting && cmdline.isSignal) {
    // Only doing for signal, since for ttbar, we do top pt reweighting
    std::cout<<"doISRReweighting (settings): true"<<std::endl;    
    doISRReweighting = true;
  } else {
    std::cout<<"doISRReweighting (settings): false"<<std::endl;
  }

  // Pile-up reweighting
  if ( !cmdline.isData && settings.doPileupReweighting ) {
    std::cout<<"doPileupReweighting (settings): true"<<std::endl;
    ana.weighting.init_pileup_reweighting(settings.pileupDir, settings.runOnSkim, cmdline.allFileNames);
  } else std::cout<<"doPileupReweighting (settings): false"<<std::endl;
  if (debug) std::cout<<"Analyzer::main: init_pileup_reweighting ok"<<std::endl;

  // Scale QCD to match data in a QCD dominated region
  //std::cout<<"scaleQCD (settings): "<<( settings.scaleQCD ? "true" : "false" )<<std::endl;

  // AK8 Jet Pt rescaling
  std::cout<<"doAK8JetPtRescaling (settings): "<<( settings.doAK8JetPtRescaling ? "true" : "false" )<<std::endl;

  // Scale factors
  std::cout<<"applySmearing (settings): "<<( settings.applySmearing ? "true" : "false" )<<std::endl;

  // Scale factors
  std::cout<<"applyScaleFactors (settings): "<<( settings.applyScaleFactors ? "true" : "false" )<<std::endl;

  // ------------------------------------------------------------------------------
  // -- Define the order of cuts (and corresponding bins in the counts histogram --
  // ------------------------------------------------------------------------------

  // Define bin order for counts histogram
  ofile->count("nevents",   0);
  // Counts after each reweighting step
  if ( ! cmdline.isData ) {
    ofile->count("w_lumi",    0);
    ofile->count("w_toppt",   0);
    ofile->count("w_isr",     0);
    ofile->count("w_pileup",  0);
    ofile->count("w_alphas",  0);
    ofile->count("w_scale",   0);
    ofile->count("w_pdf",     0);
    ofile->count("w_lostlep", 0);
    ofile->count("w_trigger", 0);
    ana.weighting.all_weights.resize(9,1);
  }
  ofile->count("NoCuts",    0);
  std::cout<<std::endl;
  //std::cout<<"Number of events counted after applying"<<std::endl;
  //std::cout<<"- Baseline cuts (common for all analysis):"<<std::endl;
  for (const auto& cut : ana.event_selections.baseline_cuts) {
    ofile->count(cut.name, 0);
    //std::cout<<"  "<<cut.name<<std::endl;
  }
  //std::cout<<std::endl;
  //std::cout<<"- Analysis specific cuts (and scale factors):\n";
  for (const auto& region : magic_enum::enum_entries<EventSelections::Regions>()) {
    for (const auto& cut : ana.event_selections.analysis_cuts[region.first]) {
      ofile->count(std::string(region.second)+"_cut_"+cut.name, 0);
      //std::cout<<"  "<<std::string(region.second)+"_cut_"+cut.name<<std::endl;
    }
    // Apply scale factors (no real calculation, just getting the number of SFs for each region)
    ana.scale_factors.apply_scale_factors(ana.weighting.all_weights, ana.weighting.w_nm1, syst.index, syst.nSigmaSFs);
    for (size_t i=0, n=ana.scale_factors.scale_factors[region.first].size(); i<n; ++i)
      ofile->count(std::string(region.second)+"_sf_"+std::to_string(i+1), 0);
  }
  if (debug) std::cout<<"Analyzer::main: init counts ok"<<std::endl;

  //---------------------------------------------------------------------------
  // Loop over events
  //---------------------------------------------------------------------------


  double nskim = 0, w = 0;
  int ifirst = 0;
  int ilast = ev.size();
  if (cmdline.ifirst > 0) ifirst = cmdline.ifirst;
  if (cmdline.ilast != -1 && cmdline.ilast<ev.size()) ilast = cmdline.ilast;
  int nevents = ilast - ifirst;
  std::cout<<"Start looping on events with # of events : "<<nevents<<std::endl;
  std::cout<<std::endl;
  std::cout<<"ifirst="<<ifirst<<std::endl;
  std::cout<<"ilast="<<ilast<<std::endl;
  std::cout<<std::endl;
  for(int entry=ifirst; entry<ilast; entry++) {

    if (sigint) ilast = entry+1; // set this as the last event and terminate program normally

    // Read event into memory
    //stream.read(entry);
    ev.read(entry);
    ev.fillObjects();
    if (debug>1) std::cout<<"Analyzer::main: reading entry ok"<<std::endl;

    ofile->count("nevents", 1);

    if ( cmdline.isData ) {
      syst.index = 0;
      // All weights are 1 for data
      w = 1;
      for (auto& sf_w : ana.weighting.sf_weight) sf_w = 1;

      // Only analyze events that are in the JSON file
      //if (settings.useJSON ? json_run_ls[data.evt.RunNumber][data.evt.LumiBlock] : 1) {

      // If option (saveSkimmedNtuple) is specified save all 
      // skimmed events selected by the analysis to the output file
      // tree is copied and current weight is saved as "eventWeight"
      if ( settings.saveSkimmedNtuple ) {
        ana.fill_histos                 (settings.varySystematics, settings.runOnSkim, syst.index, w);
        ana.weighting.fill_weight_histos(settings.varySystematics, settings.runOnSkim, syst.index, w);
        ana.scale_factors.fill_sf_histos(settings.varySystematics, settings.runOnSkim, syst.index, w);
        if (debug>1) std::cout<<"Analyzer::main: filling common histos ok"<<std::endl;
        if (ana.event_selections.pass_skimming()) {
          ofile->write(w);
          nskim++;
        }
        if (debug>1) std::cout<<"Analyzer::main: adding skimmed event ok"<<std::endl;
      } else {

        //std::cout<<entry<<std::endl;
        // Calculate variables that do not exist in the ntuple
        v.define_lepton_and_photon_variables();
        v.define_jet_variables();
        v.define_event_variables(syst.index);
        if (debug>1) std::cout<<"Analyzer::main: calculating variables ok"<<std::endl;

        // Save counts (after each baseline cuts)
        ofile->count("NoCuts", w);
        bool pass_all_baseline_cuts = true;
        for (const auto& cut : ana.event_selections.baseline_cuts) {
          if ( !(pass_all_baseline_cuts = cut.func()) ) break;
          ofile->count(cut.name, w);
        }
        if (debug>1) std::cout<<"Analyzer::main: saving baseline cut counts ok"<<std::endl;

        if (pass_all_baseline_cuts) {
          ana.event_selections.apply_event_selections();
          
          ana.fill_histos                 (settings.varySystematics, settings.runOnSkim, syst.index, w);
          ana.weighting.fill_weight_histos(settings.varySystematics, settings.runOnSkim, syst.index, w);
          ana.scale_factors.fill_sf_histos(settings.varySystematics, settings.runOnSkim, syst.index, w);
          if (debug>1) std::cout<<"Analyzer::main: filling common histos ok"<<std::endl;

          // Apply analysis cuts and fill histograms
          // These are all defined in [Name]_Analysis.cc (included from settings.h)
          // You specify there also which cut is applied for each histo
          // But all common baseline cuts are alreay applied above
          if (!cmdline.noPlots) {
            ana.plotting.fill_analysis_histos(syst.index, w);
            if (debug>1) std::cout<<"Analyzer::main: fill_analysis_histos ok"<<std::endl;
          }

          // Save counts for the analysis cuts in each search region (signal/control)
          for (const auto& region : magic_enum::enum_entries<EventSelections::Regions>()) {
            bool pass_all_regional_cuts = true;
            for (const auto& cut : ana.event_selections.analysis_cuts[region.first]) {
              if ( !(pass_all_regional_cuts = cut.func()) ) break;
              ofile->count(std::string(region.second)+"_cut_"+cut.name, w);
            }
          }
          if (debug>1) std::cout<<"Analyzer::main: saving analysis cut counts ok"<<std::endl;

        } // end baseline selection

      } // end not skimming

      //} // end JSON file cut

      if (debug>1) std::cout<<"Analyzer::main: end data event"<<std::endl;
    } // End DATA
    else {
      // Background and Signal MCs

      if ( settings.saveSkimmedNtuple ) {
        // Save the total weights (the methods fill a histo with the total weight)
        ana.weighting.get_toppt_weight    (syst.nSigmaTopPt[syst.index], syst.index, settings.runOnSkim);
        ana.weighting.get_isr_weight      (syst.nSigmaISR[syst.index],   syst.index, settings.runOnSkim);
        ana.weighting.get_pileup_weight(1, syst.nSigmaPU[syst.index],    syst.index, settings.runOnSkim);

        ana.fill_histos                 (settings.varySystematics, settings.runOnSkim, syst.index, w);
        ana.weighting.fill_weight_histos(settings.varySystematics, settings.runOnSkim, syst.index, w);
        ana.scale_factors.fill_sf_histos(settings.varySystematics, settings.runOnSkim, syst.index, w);
        if (debug>1) std::cout<<"Analyzer::main: filling common histos ok"<<std::endl;

        // If option (saveSkimmedNtuple) is specified save all 
        // skimmed events selected by the analysis to the output file
        // tree is copied and current weight is saved as "eventWeight"
        if (ana.event_selections.pass_skimming()) {
          ofile->write(w);
          nskim++;
        }
        if (debug>1) std::cout<<"Analyzer::main: adding skimmed event ok"<<std::endl;

      } else {

        // Loop and vary systematics
        for (syst.index = 0; syst.index <= (settings.varySystematics ? syst.nSyst : 0); ++syst.index) {

          w = 1;

          // Event weights
          // Lumi normalization
          // Signals are binned so we get the total weight separately for each bin
          if (cmdline.isSignal) {
            weightnorm = ana.weighting.get_signal_weightnorm();
            if (debug==-1) std::cout<<"weightnorm = "<<weightnorm;
          }
          if (debug>1) std::cout<<"Analyzer::main: calculate signal weight ok"<<std::endl;
          // Normalize to chosen luminosity, also consider symmeteric up/down variation in lumi uncertainty
          w *= (ana.weighting.all_weights[0] = ana.weighting.get_syst_weight(v.Generator_weight/abs(v.Generator_weight)*weightnorm, settings.lumiUncertainty, syst.nSigmaLumi[syst.index]));
          if (syst.index==0) ofile->count("w_lumi", w);
          if (debug==-1) std::cout<<syst.index<<" lumi = "<<ana.weighting.get_syst_weight(v.Generator_weight/abs(v.Generator_weight)*weightnorm, settings.lumiUncertainty, syst.nSigmaLumi[syst.index]);
          if (debug>1) std::cout<<"Analyzer::main: apply lumi weight ok"<<std::endl;

          // Top pt reweighting
          if (doTopPtReweighting) {
            w *= (ana.weighting.all_weights[1] = ana.weighting.get_toppt_weight(syst.nSigmaTopPt[syst.index], syst.index, settings.runOnSkim));	    
          }
          if (syst.index==0) ofile->count("w_toppt", w);
          
          // ISR reweighting
          if (doISRReweighting) {
            w *= (ana.weighting.all_weights[2] = ana.weighting.get_isr_weight(syst.nSigmaISR[syst.index], syst.index, settings.runOnSkim));
          }
          if (syst.index==0) ofile->count("w_isr", w);
          
          
          // Pileup reweighting
          if ( settings.doPileupReweighting ) {
            w *= (ana.weighting.all_weights[3] = ana.weighting.get_pileup_weight(w, syst.nSigmaPU[syst.index], syst.index, settings.runOnSkim));
          }
          if (syst.index==0) ofile->count("w_pileup", w);
          if (debug==-1) std::cout<<" pileup = "<<ana.weighting.all_weights[3];
          if (debug>1) std::cout<<"Analyzer::main: apply pileup weight ok"<<std::endl;
          
          // Theory weights
          // LHE weight variations
          // Alpha_s variations (not available in NanoAOD)
          //w *= (ana.weighting.all_weights[4] = ana.weighting.get_alphas_weight(syst.nSigmaAlphaS[syst.index], 0));
          w *= (ana.weighting.all_weights[4] = 1);
          if (syst.index==0) ofile->count("w_alphas", w);
          //if (debug==-1) std::cout<<" alpha_s = "<<ana.get_alphas_weight(syst.nSigmaAlphaS[syst.index], ev.evt.LHA_PDF_ID);
          if (debug>1) std::cout<<"Analyzer::main: apply alphas weight ok"<<std::endl;
          
          // Scale variations
          // A set of six weights, unphysical combinations excluded
          // If numScale=0 is specified, not doing any weighting
          if ( syst.numScale[syst.index] >= 1 && syst.numScale[syst.index] <= 3 )
            w *= (ana.weighting.all_weights[5] = ana.weighting.get_scale_weight(scale_weight_norm, syst.nSigmaScale[syst.index], syst.numScale[syst.index]));
          if (syst.index==0) ofile->count("w_scale", w);
          if (debug==-1) std::cout<<" scale = "<<ana.weighting.get_scale_weight(scale_weight_norm, syst.nSigmaScale[syst.index], syst.numScale[syst.index]);
          
          // PDF weights
          // A set of weights for the nominal PDF
          // If numPdf=0 is specified, not doing any weighting
          if (syst.numPdf[syst.index]!=0) {
            if (syst.numPdf[syst.index] >= 1 && syst.numPdf[syst.index] <= v.nLHEPdfWeight)
              w *= (ana.weighting.all_weights[6] = v.LHEPdfWeight[syst.numPdf[syst.index]-1]);
            else error("numPdf (syst) specified is larger than the number of PDF weights in the ntuple");
            if (debug==-1) std::cout<<" pdf = "<<(syst.numPdf[syst.index]>0 ? v.LHEPdfWeight[syst.numPdf[syst.index]-1] : 1);
          }
          if (syst.index==0) ofile->count("w_pdf", w);
          if (debug>1) std::cout<<"Analyzer::main: apply pdf weight ok"<<std::endl;
          
          // Scale QCD to match data in QCD dominated region
          //  if (samplename.Contains("QCD")) {
          //    // Scale factor
          //    // value obtained with ROOT macro: scripts/CalcQCDNormFactor.C
          //    if (settings.scaleQCD)
          //      w *= settings.useJSON ? 0.776458 : 0.785087; // Golden/Silver JSON
          //  
          //  }
          //  if (debug>1) std::cout<<"Analyzer::main: apply special weights ok"<<std::endl;
          
          // AK8 jet pt reweighting for madgraph Z/gamma samples
          bool rescaleAK8 = 0;
          if (settings.doAK8JetPtRescaling) {
            if (samplename.Contains("ZJetsToNuNu")||samplename.Contains("DYJetsToLL")||samplename.Contains("GJets_HT")) { 
              rescaleAK8 = 1;
            }
          }
          
          // Scale and Smear Jets and MET
          v.rescale_smear_jet_met(settings.applySmearing, syst.index, syst.nSigmaJES[syst.index],
                                  syst.nSigmaJER[syst.index], syst.nSigmaRestMET[syst.index],
                                  rescaleAK8, syst.nSigmaRescaleAK8[syst.index]);
          if (debug>1) std::cout<<"Analyzer::main: rescale_smear_jet_met ok"<<std::endl;
          
          // Calculate variables that do not exist in the ntuple
          // But first decide if we need to recaulculate them
          // We check if the objects were either changed now
          // or changed in previous cycle, so we need to revert them back
          v.recalc_megajets = (syst.nSigmaJES[syst.index]!=0)||(syst.nSigmaJER[syst.index]!=0);
          v.recalc_jets     = v.recalc_megajets || (syst.nSigmaRescaleAK8[syst.index]!=0);
          v.recalc_met      = v.recalc_megajets || (syst.nSigmaRestMET[syst.index]!=0);
          if (syst.index>1) {
            if ((syst.nSigmaJES[syst.index-1]!=0 ||
                 syst.nSigmaJER[syst.index-1]!=0) &&
                !v.recalc_megajets) v.recalc_megajets = 2;
            if ((syst.nSigmaJES[syst.index-1]!=0 ||
                 syst.nSigmaJER[syst.index-1]!=0 ||
                 syst.nSigmaRescaleAK8[syst.index-1]!=0) &&
                !v.recalc_jets) v.recalc_jets = 2;
            if ((syst.nSigmaJES[syst.index-1]!=0 ||
                 syst.nSigmaJER[syst.index-1]!=0 ||
                 syst.nSigmaRestMET[syst.index-1]!=0) &&
                !v.recalc_met) v.recalc_met = 2;
          }
          //std::cout<<entry<<std::endl;
          if (syst.index==0) v.define_lepton_and_photon_variables();
          if (syst.index==0||v.recalc_jets!=0) v.define_jet_variables();
          if (syst.index==0) v.define_genparticle_variables();
          if (syst.index==0||v.recalc_jets!=0||v.recalc_met!=0||v.recalc_megajets!=0) v.define_event_variables(syst.index);
          if (debug>1) std::cout<<"Analyzer::main: calculating variables ok"<<std::endl;
          
          // Lost Lepton Systematics
          w *= (ana.weighting.all_weights[7] = ana.weighting.calc_lostlep_weight(syst.nSigmaLostLep[syst.index]));
          if (syst.index==0) ofile->count("w_lostlep", w);
          if (debug==-1) std::cout<<" lostlep = "<<ana.weighting.calc_lostlep_weight(syst.nSigmaLostLep[syst.index]);
          if (debug>1) std::cout<<"Analyzer::main: apply lostlep weight ok"<<std::endl;
          
          // Apply Trigger Efficiency
          w *= (ana.weighting.all_weights[8] = ana.weighting.calc_trigger_efficiency(syst.nSigmaTrigger[syst.index]));
          if (syst.index==0) ofile->count("w_trigger", w);
          if (debug==-1) std::cout<<" trigger = "<<ana.weighting.calc_trigger_efficiency(syst.nSigmaTrigger[syst.index]);
          if (debug>1) std::cout<<"Analyzer::main: apply trigger weight ok"<<std::endl;
          
          // Apply Object Scale Factors
          for (auto& sf_w : ana.weighting.sf_weight) sf_w = w;
          if (settings.applyScaleFactors) {
            // Analysis specific scale factors (region dependent)
            ana.scale_factors.apply_scale_factors(ana.weighting.all_weights, ana.weighting.w_nm1, syst.index, syst.nSigmaSFs);
            // Multiply weight with calculated SFs
            for (size_t region=0, nregion=ana.scale_factors.scale_factors.size(); region<nregion; ++region) {
              for (const auto& sf : ana.scale_factors.scale_factors[region]) {
                ana.weighting.sf_weight[region] *= sf;
              }
            }
          }
          if (debug>1) std::cout<<"Analyzer::main: apply_scale_factors ok"<<std::endl;
          
          // Save counts (after each cuts)
          // First cuts that are likely to be implemented in all analyses
          // eg. MET filters, baseline event selection etc.
          bool pass_all_baseline_cuts = true;
          if (syst.index==0) ofile->count("NoCuts", w);
          for (const auto& cut : ana.event_selections.baseline_cuts) {
            if ( !(pass_all_baseline_cuts = cut.func()) ) break; 
            if (syst.index==0) ofile->count(cut.name, w);
          }
          if (debug>1) std::cout<<"Analyzer::main: counting baseline events ok"<<std::endl;
          
          if (pass_all_baseline_cuts) {
            ana.event_selections.apply_event_selections();
            if (debug>1) std::cout<<"Analyzer::main: apply_event_selections() ok"<<std::endl;
          
            ana.fill_histos                 (settings.varySystematics, settings.runOnSkim, syst.index, w);
            if (debug>1) std::cout<<"Analyzer::main: fill_histos() ok"<<std::endl;
            ana.weighting.fill_weight_histos(settings.varySystematics, settings.runOnSkim, syst.index, w);
            if (debug>1) std::cout<<"Analyzer::main: fill_weight_histos() ok"<<std::endl;
            ana.scale_factors.fill_sf_histos(settings.varySystematics, settings.runOnSkim, syst.index, w);
            if (debug>1) std::cout<<"Analyzer::main: fill_sf_histos() ok"<<std::endl;
            
            // Apply analysis cuts and fill histograms
            // These are all defined in [Name]_Analysis.cc (included from settings.h)
            // You specify there also which cut is applied for each histo
            // But all common baseline cuts will be already applied above
            if (!cmdline.noPlots) {
              ana.plotting.fill_analysis_histos(syst.index, w);
              if (debug>1) std::cout<<"Analyzer::main: fill_analysis_histos ok"<<std::endl;
            }
            
            // Save counts for the analysis cuts in each search region (signal/control)
            if (syst.index==0) for (const auto& region : magic_enum::enum_entries<EventSelections::Regions>()) {
              // First apply cuts
              bool pass_all_regional_cuts = true;
              for (const auto& cut : ana.event_selections.analysis_cuts[region.first]) {
                if ( !(pass_all_regional_cuts = cut.func()) ) break;
                ofile->count(std::string(region.second)+"_cut_"+cut.name, w);
              }
              // Then apply scale factors
              if (settings.applyScaleFactors && pass_all_regional_cuts) {
                double sf_w = w;
                for (size_t i=0, n=ana.scale_factors.scale_factors[region.first].size(); i<n; ++i) {
                  sf_w *= ana.scale_factors.scale_factors[region.first][i];
                  ofile->count(std::string(region.second)+"_sf_"+std::to_string(i+1), sf_w);
                  if (debug==-1) std::cout<<", "<<sf_w;
                }
              }
            }
            if (debug>1) std::cout<<"Analyzer::main: counting analysis events, scale factors ok"<<std::endl;
            if (debug==-1) std::cout<<"  w = "<<w<<std::endl;
          }
        } // end systematics loop
      } // end not skimming
      if (debug>1) std::cout<<"Analyzer::main: end mc event"<<std::endl;
    } // end Background/Signal MC
    if (debug==-1) std::cout<<"---------------------------------------"<<std::endl<<std::endl;

    // Measure speed (useful info for batch/parallel jobs)
    ana.job_monitoring(entry, ifirst, ilast, stream.filename());
    if (debug>1) std::cout<<"Analyzer::main: job_monitoring ok, end event"<<std::endl;

  } // end event loop
  if (debug) std::cout<<"Analyzer::main: event loop ok"<<std::endl;


  // Print skimming ratio
  if ( settings.saveSkimmedNtuple ) {
    std::cout<<"SkimmingInfo Nevent: "<<nevents<<" Nskim: "<<nskim<<std::endl;
  }

  stream.close();
  out_dir->cd();
  if (!cmdline.noPlots)
    ana.plotting.save_analysis_histos();
  ofile->close();
  if (debug) std::cout<<"Analyzer::main: all ok"<<std::endl;
  std::cout<<"UnixTime-End: "<<std::time(0)<<std::endl;

  return 0;
}
