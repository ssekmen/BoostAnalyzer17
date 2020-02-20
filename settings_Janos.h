// SKIM - 1: save skimmed ntuple, 0: run on already skimmed ntuple
#define SYST  0
#define SKIM  0

#ifndef PLOTTER
#include "include/treestream.h"
#endif

#if SKIM == 0
//#include "Plotting_Janos.h" // Specify here the implementations for your Analysis
#include "Plotting_Changgi.h" // Specify here the implementations for your Analysis
#else 
#include "Analysis_Skim.h" // Specify here the implementations for your Analysis
#endif

struct settings {

  //-----------------------------------------------------------------------------
  // -- Constants
  //-----------------------------------------------------------------------------
  settings() :
    runOnSkim                ( 1-SKIM  ),
    saveSkimmedNtuple        ( SKIM ),
    doTopPtReweighting       ( true  ),
    doISRReweighting         ( false  ),
    doPileupReweighting      ( true  ),
    doAK8JetPtRescaling      ( false  ),
    applySmearing            ( false  ),
    applyScaleFactors        ( false  ),
    nSigmaScaleFactors       ( 22    ), // Count the number of sigmas you use in Analysis_*.h - 4 ele, 3 mu, 6 W, 2b, 7 top
    varySystematics          ( SYST  ),
    systematicsFileName      ( "systematics/2018_05_02_1SigmaUpDown_NoPdf.txt" ),
//  systematicsFileName      ( "systematics/2017_12_26_AllUpDown_NoPdf.txt" ),
//  systematicsFileName      ( "systematics/2018_03_19_JESOnly.txt" ),
    useJSON                  ( false ), // by default: no need to apply, but can be useful if some lumisections need to be excluded additionally
    jsonFileName             ( "/afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions16/13TeV/ReReco/Final/"
			       "Cert_271036-284044_13TeV_23Sep2016ReReco_Collisions16_JSON.txt" ),
    pileupDir                ( "pileup/EOY2017ReReco_Collisions17_JSON/" ),
    //intLumi                  ( 41529 /* brilcalc - Dec02 Golden JSON */ ), // Tot int lumi in (pb^-1),
    //lumiUncertainty          ( 0.025  ),
    lumiUncertainty          ( 0.  ),
    useXSecFileForBkg        ( true   ) {}; // true: use file below, false: use value in the ntuple (evt_XSec)
    //xSecFileName             ( "include/BackGroundXSec.txt" ) {};
  ~settings(){};

  const bool runOnSkim;
  const bool saveSkimmedNtuple;
  const bool doTopPtReweighting;
  const bool doISRReweighting;
  const bool doPileupReweighting;
  const bool doAK8JetPtRescaling;
  const bool applySmearing;
  const bool applyScaleFactors;
  const int  nSigmaScaleFactors;
  const bool varySystematics;
  const std::string systematicsFileName;
  const bool useJSON;
  const std::string jsonFileName;
  const std::string pileupDir;
  //const double intLumi;
  const double lumiUncertainty;
  const bool useXSecFileForBkg;
  //const std::string xSecFileName;

} settings;
