//-----------------------------------------------------------------------------
// File:        Analyzer.cc
// Created:     24-Nov-2015
// Author:      Janos Karancsi
//-----------------------------------------------------------------------------
#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <vector>

#include "tnm.h"
#include "settings_Changgi.h" // Define all Analysis specific settings here

using namespace std;

int main(int argc, char** argv) {
  const int debug = 0;
  if (debug) std::cout<<"Analyzer::main: start"<<std::endl;

  // List names in filenames from which the code can decide if it is data or signal
  // For the rest it's assumed it's background MC
  // if .txt file is given as input then from the directory name we can already tell
  //std::vector<std::string> vname_data = { "Run2015", "Run2016", "Run2017", "Run2018" };
  std::vector<std::string> vname_data = { "JetHT", "SingleMuon", "SingleElectron", "MET", "SinglePhoton" };
  std::vector<std::string> vname_signal = { "SMS" }; // SMS

  // ------------------------------
  // -- Parse command line stuff --
  // ------------------------------

  // Get file list and histogram filename from command line
  commandLine cmdline(argc, argv);
  decodeCommandLine(argc, argv, cmdline, vname_data, vname_signal);
  if (debug) std::cout<<"Analyzer::main: decodeCommandLine ok"<<std::endl;

  //itreestream stream(cmdline.fileNames, settings.runOnSkim ? "B2GTree" : "B2GTTreeMaker/B2GTree", 2000);
  vector<string> filenames = getFilenames(cmdline.filelist);
  itreestream stream(filenames, "Events");
  if ( !stream.good() ) error("can't read root input files");

  if ( cmdline.isData ) cout << "Running on Data." << endl;
  else if ( cmdline.isBkg ) cout << "Running on Background MC." << endl;
  else cout << "Running on Signal MC." << endl;

  // Get number of events to be read
  //int nevents = stream.size();
  eventBuffer ev(stream);
  int nevents = ev.size();
  //outputFile ofile(cl.outputfilename);
  outputFile* ofile;// = outputFile(cmdline.outputfilename);

/*
  if (cmdline.quickTest) {
    cout << "quickTest (cmdline): "<<cmdline.quickTest<< endl;
    cout << "--> Doing a quick test on 1/"<<cmdline.quickTest<<" statitics"<< endl;
    nevents /= cmdline.quickTest;
    cout << "Number of events (1/" << cmdline.quickTest << "): " << nevents << endl;
  } else {
    cout << "Number of events: " << nevents << endl;
  }*/

  // Select variables to be read
  //eventBuffer data;
  //settings.selectVariables(stream, data);
  if (debug) std::cout<<"Analyzer::main: selectVariables ok"<<std::endl;

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

  // Constuct the Analysis (specified in settings.h)
  Analysis ana(cmdline.isData, cmdline.isSignal, cmdline.dirname);

  // ---------------------------------------------------------------------------
  // -- output file                                                           --
  // ---------------------------------------------------------------------------

  if ( settings.saveSkimmedNtuple ) {
    cout << "saveSkimmedNtuple (settings): true" << endl;
    ofile = new outputFile(cmdline.outputfilename, ev);
  } else {
    ofile = new outputFile(cmdline.outputfilename);
    cout << "saveSkimmedNtuple (settings): false" << endl;
  }
  TDirectory* out_dir = gDirectory;

  if (cmdline.noPlots) {
    cout << "noPlots (cmdline): true"<< endl;
    cout << "--> Will not save analysis histos"<< endl;
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
    //std::vector<double> nSigmaHT          = std::vector<double>(1,0);
    std::vector<double> nSigmaLostLep  = std::vector<double>(1,0);
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
    cout << "varySystematics    (settings): true" << endl;
    cout << "nSigmaScaleFactors (settings): " << settings.nSigmaScaleFactors << endl;
    cout << "systematicsFileName (settings): " << settings.systematicsFileName << endl;
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
      //nth_line>>dbl; syst.nSigmaHT.push_back(dbl);
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
    cout << "varySystematics (settings): false" << endl;
  }
  if (debug) std::cout<<"Analyzer::main: read systematics ok"<<std::endl;


  // ---------------------------------------------------------------------------
  // -- Read and apply JSON file (Data)                                       --
  // ---------------------------------------------------------------------------

  std::map<int, std::map<int, bool> > json_run_ls;
  if (settings.useJSON) {
    cout << "useJSON (settings): true" << endl;
    cout << "jsonFileName (settings): " << settings.jsonFileName << endl;
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
    cout << "useJSON (settings): false" << endl;
  }
  if (debug) std::cout<<"Analyzer::main: load JSON file ok"<<std::endl;


  // ---------------------------------------------------------------------------
  // -- Declare histograms                                                    --
  // ---------------------------------------------------------------------------

  // Histogram weight
  double w;
  TH1::SetDefaultSumw2();

  // This section is moved and defined in the Analysis class
  // this class specifies what histograms/cuts/methods etc. you want to implement
  // This is useful if someone wants to do quick study/define other search region etc.
  // But also, common methods in all anaylsis are defined in common/AnalysisBase.*

  ana.define_histo_options(w, ev, syst.nSyst, syst.index, settings.runOnSkim);
  if (debug) std::cout<<"Analyzer::main: define_histo_options ok"<<std::endl;

  ana.init_common_histos(settings.varySystematics);
  if (!cmdline.noPlots) ana.init_analysis_histos(syst.nSyst, syst.index);
  if (debug) std::cout<<"Analyzer::main: init_histos ok"<<std::endl;

  // Read histograms for scale factors
  ana.init_syst_input();
  if (debug) std::cout<<"Analyzer::main: init_syst_input ok"<<std::endl;

  // --------------------------------------------------------------
  // -- Calculate the normalization factor for the event weights --
  // -- The original MC weight will be divided by this quantity  --
  // --------------------------------------------------------------

  cout << endl;
  double weightnorm = 1;
  int signal_index = -1;
  TString samplename(cmdline.dirname);
  if ( cmdline.isBkg ) {
    cout << "intLumi (settings): " << settings.intLumi << endl; // given in settings.h

    double xsec = 0, totweight = 0;
    if (settings.useXSecFileForBkg&&settings.runOnSkim) {
      cout << "useXSecFileForBkg (settings): true" << endl; // given in settings.h
      cout << "xSecFileName (settings): " << settings.xSecFileName << endl; // given in settings.h
      std::pair<double, double> values = ana.get_xsec_totweight_from_txt_file(settings.xSecFileName); // xSecFileName given in settings.h
      xsec = values.first;
      totweight = values.second;
      cout << "xsec      (txt file): " << xsec << endl;
      cout << "totweight (txt file): " << totweight << endl;
    } else {
      cout << "useXSecFileForBkg (settings): false" << endl; // given in settings.h
      xsec = ana.get_xsec_from_ntuple(cmdline.fileNames, settings.runOnSkim); // given in settings.h
      cout << "xsec      (ntuple): " << xsec << endl;
      totweight = ana.get_totweight_from_ntuple(cmdline.allFileNames, settings.runOnSkim); // weight histo name given in settings.h
      cout << "totweight (ntuple): " << totweight << endl;
    }
    if ( xsec==0 || totweight==0 ) return 1;

    weightnorm = (settings.intLumi*xsec)/totweight;
    cout << "weightnorm (calc): " << weightnorm << endl;
  } else if ( cmdline.isSignal ) {
    cout << "intLumi (settings): " << settings.intLumi << endl; // given in settings.h

    cout << "Normalization variables:" << endl;
    ana.calc_weightnorm_histo_from_ntuple(cmdline.allFileNames, settings.intLumi, vname_signal, 
					  settings.runOnSkim, settings.varySystematics, out_dir); // histo names given in settings.h

  // Find the index of the current signal
    signal_index = samplename.Contains("T2tt");
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
    cout << "doTopPtReweighting (settings): true" << endl;    
    doTopPtReweighting = true;
  } else {
    cout << "doTopPtReweighting (settings): false" << endl;
  }

/*
  // ISR reweighting
  bool doISRReweighting = false;
  if ( settings.doISRReweighting && cmdline.isSignal) {
    // Only doing for signal, since for ttbar, we do top pt reweighting
    cout << "doISRReweighting (settings): true" << endl;    
    doISRReweighting = true;
  } else {
    cout << "doISRReweighting (settings): false" << endl;
  }

  // Pile-up reweighting
  if ( !cmdline.isData && settings.doPileupReweighting ) {
    cout << "doPileupReweighting (settings): true" << endl;
    ana.init_pileup_reweighting(settings.pileupDir, settings.runOnSkim, cmdline.allFileNames);
  } else cout << "doPileupReweighting (settings): false" << endl;
*/
  if (debug) std::cout<<"Analyzer::main: init_pileup_reweighting ok"<<std::endl;

  // Scale QCD to match data in a QCD dominated region
  //cout << "scaleQCD (settings): " << ( settings.scaleQCD ? "true" : "false" ) << endl;

  // AK8 Jet Pt rescaling
  cout << "doAK8JetPtRescaling (settings): " << ( settings.doAK8JetPtRescaling ? "true" : "false" ) << endl;

  // Scale factors
  cout << "applySmearing (settings): " << ( settings.applySmearing ? "true" : "false" ) << endl;

  // Scale factors
  cout << "applyScaleFactors (settings): " << ( settings.applyScaleFactors ? "true" : "false" ) << endl;

  // ------------------------------------------------------------------------------
  // -- Define the order of cuts (and corresponding bins in the counts histogram --
  // ------------------------------------------------------------------------------

  // Define cuts that are common in all analyses
  // Given in common/AnalysisBase.h
  ana.define_preselections(ev);
  if (debug) std::cout<<"Analyzer::main: define_preselections ok"<<std::endl;

  // Define cuts that specific to this analysis
  // Given in [Name]_Analysis.h specified in setting.h
  ana.define_selections(ev);
  if (debug) std::cout<<"Analyzer::main: define_selections ok"<<std::endl;

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
    ofile->count("w_lostlep",    0);
    ofile->count("w_trigger", 0);
    ana.all_weights.resize(9,1);
  }
  ofile->count("NoCuts",    0);
  cout << endl;
  cout << "Number of events counted after applying" << endl;
  cout << "- Baseline cuts (common for all analysis):" << endl;
  for (const auto& cut : ana.baseline_cuts) {
    ofile->count(cut.name, 0);
    cout << "  "<<cut.name << endl;
  }
  cout << endl;
  cout << "- Analysis specific cuts (and scale factors):\n";
  for (const auto& search_region : ana.analysis_cuts) {
    for (const auto& cut : search_region.second) {
      ofile->count(std::string(1,search_region.first)+"_cut_"+cut.name, 0);
      cout << "  " << std::string(1,search_region.first)+"_cut_"+cut.name << endl;
    }
    // Apply scale factors
    //ana.apply_scale_factors(ev, syst.index, syst.nSigmaSFs);
    for (size_t i=0, n=ana.scale_factors[search_region.first].size(); i<n; ++i)
      ofile->count(std::string(1,search_region.first)+"_sf_"+std::to_string(i+1), 0);
  }
  if (debug) std::cout<<"Analyzer::main: init counts ok"<<std::endl;

  //---------------------------------------------------------------------------
  // Loop over events
  //---------------------------------------------------------------------------

  cout << endl;
  cout << "Start looping on events ..." << endl;
  double nskim = 0;
  int ifirst = 0;
  int ilast = nevents;
  if (cmdline.ifirst != -1) ifirst = cmdline.ifirst;
  if (cmdline.ilast != -1) ilast = cmdline.ilast;
  for(int entry=ifirst; entry < ilast; entry++) {
  //for(int entry=ifirst; entry < 1; entry++) {

    // Read event into memory
    //stream.read(entry);
    ev.read(entry);
    ev.fillObjects();
    if (debug>1) std::cout<<"Analyzer::main: reading entry ok"<<std::endl;

    if ( entry%100000==0 ) cout << entry << " events analyzed, " << (float)entry/ilast*100 << " [%] is finished" << endl;

    ofile->count("nevents", 1);

    if ( cmdline.isData ) {
      syst.index = 0;
      // All weights are 1 for data
      w = 1;
      for (const auto& region : ana.scale_factors)
	ana.sf_weight[region.first] = 1;

      // Only analyze events that are in the JSON file
      //if (settings.useJSON ? json_run_ls[data.evt.RunNumber][data.evt.LumiBlock] : 1) {

	// If option (saveSkimmedNtuple) is specified save all 
	// skimmed events selected by the analysis to the output file
	// tree is copied and current weight is saved as "eventWeight"
	if ( settings.saveSkimmedNtuple ) {
	  ana.fill_common_histos(ev, settings.varySystematics, settings.runOnSkim, syst.index, w);
	  if (debug>1) std::cout<<"Analyzer::main: fill_common_histos ok"<<std::endl;
	  if (ana.pass_skimming(ev)) {
	    ofile->write(w);
	    nskim++;
	  }
	  if (debug>1) std::cout<<"Analyzer::main: adding skimmed event ok"<<std::endl;
	} else {

    //std::cout<<entry<<std::endl;
	  // Calculate variables that do not exist in the ntuple
	  ana.calculate_common_variables(ev, syst.index);
	  if (debug>1) std::cout<<"Analyzer::main: calculate_common_variables ok"<<std::endl;
	  ana.calculate_variables(ev, syst.index);
	  if (debug>1) std::cout<<"Analyzer::main: calculate_variables ok"<<std::endl;

	  // Save counts (after each baseline cuts)
	  ofile->count("NoCuts", w);
	  bool pass_all_baseline_cuts = true;
	  for (const auto& cut : ana.baseline_cuts) {
	    if ( !(pass_all_baseline_cuts = cut.func()) ) break;
	    ofile->count(cut.name, w);
	  }
	  if (debug>1) std::cout<<"Analyzer::main: saving baseline cut counts ok"<<std::endl;

	  // _______________________________________________________
	  //                  BLINDING DATA

	  // Before doing anything serious (eg. filling any histogram)
	  // Define Signal region and blind it!!!!!!!!!!!!!!!!!!!!!!!!
	  bool DATA_BLINDED = ! ( cmdline.isData && ana.signal_selection(ev) );

	  /*
	    Some more warning to make sure :)
	    _   _   _   ____    _        _____   _   _   _____    _____   _   _    _____   _   _   _ 
	    | | | | | | |  _ \  | |      |_   _| | \ | | |  __ \  |_   _| | \ | |  / ____| | | | | | |
	    | | | | | | | |_) | | |        | |   |  \| | | |  | |   | |   |  \| | | |  __  | | | | | |
	    | | | | | | |  _ <  | |        | |   | . ` | | |  | |   | |   | . ` | | | |_ | | | | | | |
	    |_| |_| |_| | |_) | | |____   _| |_  | |\  | | |__| |  _| |_  | |\  | | |__| | |_| |_| |_|
	    (_) (_) (_) |____/  |______| |_____| |_| \_| |_____/  |_____| |_| \_|  \_____| (_) (_) (_)
	  */
	  
	  //________________________________________________________
	  //

	  if (pass_all_baseline_cuts && DATA_BLINDED) {

	    ana.fill_common_histos(ev, settings.varySystematics, settings.runOnSkim, syst.index, w);
	    if (debug>1) std::cout<<"Analyzer::main: fill_common_histos ok"<<std::endl;

	    // Apply analysis cuts and fill histograms
	    // These are all defined in [Name]_Analysis.cc (included from settings.h)
	    // You specify there also which cut is applied for each histo
	    // But all common baseline cuts are alreay applied above
	    if (!cmdline.noPlots) {
	      ana.fill_analysis_histos(ev, syst.index, w);
	      if (debug>1) std::cout<<"Analyzer::main: fill_analysis_histos ok"<<std::endl;
	    }

	    // Save counts for the analysis cuts in each search region (signal/control)
	    for (const auto& search_region : ana.analysis_cuts) {
	      bool pass_all_regional_cuts = true;
	      for (const auto& cut : search_region.second) {
		if ( !(pass_all_regional_cuts = cut.func()) ) break;
		ofile->count(std::string(1,search_region.first)+"_cut_"+cut.name, w);
	      }
	    }
	    if (debug>1) std::cout<<"Analyzer::main: saving analysis cut counts ok"<<std::endl;

	  } // end Blinding

	} // end not skimming

      //} // end JSON file cut

      if (debug>1) std::cout<<"Analyzer::main: end data event"<<std::endl;
    } // End DATA
    else {
      // Background and Signal MCs

      if ( settings.saveSkimmedNtuple ) {
	// Save the total weights
	ana.get_toppt_weight(ev, syst.nSigmaTopPt[syst.index], syst.index, settings.runOnSkim);
	ana.get_isr_weight(ev, syst.nSigmaISR[syst.index], syst.index, settings.runOnSkim);
	ana.get_pileup_weight(ev, syst.nSigmaPU[syst.index], syst.index, settings.runOnSkim);

	ana.fill_common_histos(ev, settings.varySystematics, settings.runOnSkim, syst.index, w);
	if (debug>1) std::cout<<"Analyzer::main: fill_common_histos ok"<<std::endl;

	// If option (saveSkimmedNtuple) is specified save all 
	// skimmed events selected by the analysis to the output file
	// tree is copied and current weight is saved as "eventWeight"
	if (ana.pass_skimming(ev)) {
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
	  //if (cmdline.isSignal) {
	  //  int bin = vh_weightnorm_signal[signal_index]->FindBin(signal_index ? data.evt.SUSY_Stop_Mass : data.evt.SUSY_Gluino_Mass, data.evt.SUSY_LSP_Mass);
	  //  weightnorm = vh_weightnorm_signal[signal_index]->GetBinContent(bin);
	  //}
	  if (debug>1) std::cout<<"Analyzer::main: calculate signal weight ok"<<std::endl;
	  // Normalize to chosen luminosity, also consider symmeteric up/down variation in lumi uncertainty
	  
	  //w *= (ana.all_weights[0] = ana.get_syst_weight(data.evt.Gen_Weight*weightnorm, settings.lumiUncertainty, syst.nSigmaLumi[syst.index]));
	  if (syst.index==0) ofile->count("w_lumi", w);
	  //if (debug==-1) std::cout<<syst.index<<" lumi = "<<ana.get_syst_weight(data.evt.Gen_Weight*weightnorm, settings.lumiUncertainty, syst.nSigmaLumi[syst.index]);
	  if (debug>1) std::cout<<"Analyzer::main: apply lumi weight ok"<<std::endl;

	  // Top pt reweighting
	  if (doTopPtReweighting) {
	    w *= (ana.all_weights[1] = ana.get_toppt_weight(ev, syst.nSigmaTopPt[syst.index], syst.index, settings.runOnSkim));	    
	  }
	  if (syst.index==0) ofile->count("w_toppt", w);

	  // ISR reweighting
	  //if (doISRReweighting) {
	  //  w *= (ana.all_weights[2] = ana.get_isr_weight(data, syst.nSigmaISR[syst.index], syst.index, settings.runOnSkim));
	  //}
	  if (syst.index==0) ofile->count("w_isr", w);
	  

	  // Pileup reweighting
	  if (syst.index == 0) h_nvtx->Fill(ev.PV_npvsGood, w);
	  if ( settings.doPileupReweighting ) {
	    w *= (ana.all_weights[3] = ana.get_pileup_weight(ev, syst.nSigmaPU[syst.index], syst.index, settings.runOnSkim));
	  }
	  if (syst.index==0) {
	    h_nvtx_rw->Fill(ev.PV_npvsGood, w);
	    ofile->count("w_pileup", w);
	  }
	  if (debug==-1) std::cout<<" pileup = "<<ana.all_weights[3];
	  if (debug>1) std::cout<<"Analyzer::main: apply pileup weight ok"<<std::endl;

	  // Theory weights
	  // LHE weight variations
	  // More info about them here:
	  // https://github.com/jkarancs/B2GTTrees/blob/master/plugins/B2GEdmExtraVarProducer.cc#L165-L237

	  // Alpha_s variations
	  // A set of two weights
	  // Only stored for NLO, otherwise vector size==0
	  // If vector was not filled (LO samples), not doing any weighting
	  //if ( data.syst_alphas.Weights.size() == 2 )
	  //  w *= (ana.all_weights[4] = ana.get_alphas_weight(data.syst_alphas.Weights, syst.nSigmaAlphaS[syst.index], data.evt.LHA_PDF_ID));
	  if (syst.index==0) ofile->count("w_alphas", w);
	  //if (debug==-1) std::cout<<" alpha_s = "<<ana.get_alphas_weight(data.syst_alphas.Weights, syst.nSigmaAlphaS[syst.index], data.evt.LHA_PDF_ID);
	  if (debug>1) std::cout<<"Analyzer::main: apply alphas weight ok"<<std::endl;

	  // Scale variations
	  // A set of six weights, unphysical combinations excluded
	  // If numScale=0 is specified, not doing any weighting
	  //if ( syst.numScale[syst.index] >= 1 && syst.numScale[syst.index] <= 3 )
	  //  w *= (ana.all_weights[5] = ana.get_scale_weight(data.syst_scale.Weights, scale_weight_norm, syst.nSigmaScale[syst.index], syst.numScale[syst.index]));
	  if (syst.index==0) ofile->count("w_scale", w);
	  //if (debug==-1) std::cout<<" scale = "<<ana.get_scale_weight(data.syst_scale.Weights, scale_weight_norm, syst.nSigmaScale[syst.index], syst.numScale[syst.index]);
	  // PDF weights
	  // A set of 100 weights for the nominal PDF
	  // If numPdf=0 is specified, not doing any weighting
	  //if ( syst.numPdf[syst.index] >= 1 && syst.numPdf[syst.index] <= data.syst_pdf.Weights.size() )
	  //  w *= (ana.all_weights[6] = data.syst_pdf.Weights[syst.numPdf[syst.index]-1]);
	  //else if ( syst.numPdf[syst.index] > data.syst_pdf.Weights.size() )
	  //  error("numPdf (syst) specified is larger than the number of PDF weights in the ntuple");
	  if (syst.index==0) ofile->count("w_pdf", w);
	  //if (debug==-1) std::cout<<" pdf = "<<(syst.numPdf[syst.index]>0 ? data.syst_pdf.Weights[syst.numPdf[syst.index]-1] : 1);
	  if (debug>1) std::cout<<"Analyzer::main: apply pwd weight ok"<<std::endl;

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
	  //ana.rescale_smear_jet_met(data, settings.applySmearing, syst.index, syst.nSigmaJES[syst.index],
		//		    syst.nSigmaJER[syst.index], syst.nSigmaRestMET[syst.index],
		//		    rescaleAK8, syst.nSigmaRescaleAK8[syst.index]);
	  if (debug>1) std::cout<<"Analyzer::main: rescale_smear_jet_met ok"<<std::endl;

	  // Calculate variables that do not exist in the ntuple
    //std::cout<<entry<<std::endl;
    syst.index = 0;
	  ana.calculate_common_variables(ev, syst.index);
	  if (debug>1) std::cout<<"Analyzer::main: calculate_common_variables ok"<<std::endl;
	  ana.calculate_variables(ev, syst.index);
	  if (debug>1) std::cout<<"Analyzer::main: calculate_variables ok"<<std::endl;

	  // Lost Lepton Systematics
	  w *= (ana.all_weights[7] = ana.calc_lostlep_weight(ev, syst.nSigmaLostLep[syst.index]));
	  if (syst.index==0) ofile->count("w_lostlep", w);
	  if (debug==-1) std::cout<<" lostlep = "<<ana.calc_lostlep_weight(ev, syst.nSigmaLostLep[syst.index]);
	  if (debug>1) std::cout<<"Analyzer::main: apply lostlep weight ok"<<std::endl;

	  // Apply Trigger Efficiency
	  //w *= (ana.all_weights[8] = ana.calc_trigger_efficiency(ev, syst.nSigmaTrigger[syst.index]));
	  //if (syst.index==0) ofile->count("w_trigger", w);
	  if (debug==-1) std::cout<<" trigger = "<<ana.calc_trigger_efficiency(ev, syst.nSigmaTrigger[syst.index]);
	  if (debug>1) std::cout<<"Analyzer::main: apply trigger weight ok"<<std::endl;

	  // Apply Object Scale Factors
	  for (const auto& region : ana.scale_factors)
	    ana.sf_weight[region.first] = w;
	  if (settings.applyScaleFactors) {
	    // Analysis specific scale factors (region dependent)
	    ana.apply_scale_factors(ev, syst.index, syst.nSigmaSFs);
	    // Multiply weight with calculated SFs
	    for (const auto& region : ana.scale_factors)
	      for (const auto& sf : region.second)
		ana.sf_weight[region.first] *= sf;
	  }
	  if (debug>1) std::cout<<"Analyzer::main: apply_scale_factors ok"<<std::endl;

	  // Save counts (after each cuts)
	  // First cuts that are likely to be implemented in all analyses
	  // eg. MET filters, baseline event selection etc.
	  bool pass_all_baseline_cuts = true;
	  if (syst.index==0) ofile->count("NoCuts", w);
	  for (const auto& cut : ana.baseline_cuts) {
	    if ( !(pass_all_baseline_cuts = cut.func()) ) break; 
	    if (syst.index==0) ofile->count(cut.name, w);
	  }
	  if (debug>1) std::cout<<"Analyzer::main: counting baseline events ok"<<std::endl;

	  if (pass_all_baseline_cuts) {
	    ana.fill_common_histos(ev, settings.varySystematics, settings.runOnSkim, syst.index, w);
	    if (debug>1) std::cout<<"Analyzer::main: fill_common_histos ok"<<std::endl;

	    // Apply analysis cuts and fill histograms
	    // These are all defined in [Name]_Analysis.cc (included from settings.h)
	    // You specify there also which cut is applied for each histo
	    // But all common baseline cuts will be already applied above
	    if (!cmdline.noPlots) {
	      ana.fill_analysis_histos(ev, syst.index, w);
	      if (debug>1) std::cout<<"Analyzer::main: fill_analysis_histos ok"<<std::endl;
	    }

	    // Save counts for the analysis cuts in each search region (signal/control)
	    if (syst.index==0) for (const auto& search_region : ana.analysis_cuts) {
	      // First apply cuts
	      bool pass_all_regional_cuts = true;
	      for (const auto& cut : search_region.second) {
		if ( !(pass_all_regional_cuts = cut.func()) ) break;
		if (syst.index==0) ofile->count(std::string(1,search_region.first)+"_cut_"+cut.name, w);
	      }
	      // Then apply scale factors
	      if (settings.applyScaleFactors && pass_all_regional_cuts) {
		double sf_w = w;
		for (size_t i=0, n=ana.scale_factors[search_region.first].size(); i<n; ++i) {
		  sf_w *= ana.scale_factors[search_region.first][i];
		  if (syst.index==0) ofile->count(std::string(1,search_region.first)+"_sf_"+std::to_string(i+1), sf_w);
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
    ana.job_monitoring(entry, nevents, stream.filename());
    if (debug>1) std::cout<<"Analyzer::main: job_monitoring ok, end event"<<std::endl;

  } // end event loop
  if (debug) std::cout<<"Analyzer::main: event loop ok"<<std::endl;

  // Print skimming ratio
  if ( settings.saveSkimmedNtuple ) {
    std::cout<<"SkimmingInfo Nevent: "<<nevents<<" Nskim: "<<nskim<<std::endl;
  }

  stream.close();
  out_dir->cd();
  //if (!cmdline.noPlots)
    //ana.save_analysis_histos();
  ofile->close();
  if (debug) std::cout<<"Analyzer::main: all ok"<<std::endl;
  return 0;
}
