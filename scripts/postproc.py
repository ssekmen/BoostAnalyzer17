#!/usr/bin/env python
import os, sys
import ROOT
ROOT.PyConfig.IgnoreCommandLineOptions = True
from importlib import import_module
from PhysicsTools.NanoAODTools.postprocessing.framework.postprocessor import PostProcessor
from PhysicsTools.NanoAODTools.postprocessing.modules.jme.jetmetHelperRun2 import *
from PhysicsTools.NanoAODTools.postprocessing.modules.common.puWeightProducer import *

from optparse import OptionParser
parser = OptionParser(usage="%prog [options] outputFile inputFile")
parser.add_option("-P", "--prefetch",  dest="prefetch", action="store_true",  default=False, help="Prefetch input files locally instead of accessing them via xrootd")
parser.add_option("-N", "--max-entries", dest="maxEntries", type="long",  default=None, help="Maximum number of entries to process from any single given input tree")
(options, args) = parser.parse_args()

# figure out parameters from filenames
if len(args)!=2:
    print "Error: please provide exactly two filenames as an argument to the script (1st output, other input file)"
    print
    parser.print_help()
else:
    outfname = args[0]
    infnames = args[1:]
    #infnames=[
    #    "root://cms-xrd-global.cern.ch//store/mc/RunIIFall17NanoAODv6/TTToSemiLeptonic_TuneCP5_13TeV-powheg-pythia8/NANOAODSIM/PU2017_12Apr2018_Nano25Oct2019_new_pmx_102X_mc2017_realistic_v7-v1/110000/0E2C37BF-4630-DB40-AB8F-BE75DA1F2B3B.root"
    #    #"/eos/cms/store/mc/RunIISummer16NanoAODv5/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/NANOAODSIM/PUMoriond17_Nano1June2019_102X_mcRun2_asymptotic_v7_ext2-v1/120000/FF69DF6E-2494-F543-95BF-F919B911CD23.root"
    #    ]
    
    # figure out parameters from first filename
    o_isMC = True
    o_isFastSim = False
    o_dataYear=""
    o_runPeriod = ""
    o_metBranchName = "MET"
    if "Run20" in infnames[0]:
        o_isMC = False
        for dirname in infnames[0].split("/"):
            if "Run20" in dirname and len(dirname)>=8:
                o_runPeriod = dirname[7]
                #if "HIPM" in infnames[0]:
                #	o_runPeriod = "_preVFP"+dirname[7]
    elif "Fast" in infnames[0]:
        o_isFastSim = True
    for year in ["16", "17", "18"]:
        if "Run20"+year in infnames[0] or year+"NanoAODv" in infnames[0] or year+"NanoAODAPVv" in infnames[0]:
            o_dataYear = "UL20"+year
            if "HIPM" in infnames[0]:
             	o_dataYear = "UL20"+year+"_preVFP"
    
    print "Automatically deduced options for Jet/MET uncertainties:"
    print "isMC           = "+str(o_isMC)
    print "isFastSim      = "+str(o_isFastSim)
    print "dataYear       = "+str(o_dataYear)
    print "runPeriod      = "+str(o_runPeriod)
    print "metBranchName  = "+str(o_metBranchName)
    
    # ------------ Jet/MET corrections and uncertainties ------------
    # Examples:
    # https://twiki.cern.ch/twiki/bin/view/CMSPublic/WorkBookNanoAOD#JME_jetmet_HelperRun2
    # Function parameters
    # (isMC=True, dataYear=UL2016, runPeriod="B", jesUncert="Total", jetType="AK4PFchs", noGroom=False, metBranchName="MET", applySmearing=True, isFastSim=False):
    # All other parameters will be set in the helper module
    
    jetmetCorrector = createJMECorrector(isMC=o_isMC, dataYear=o_dataYear, runPeriod=o_runPeriod, jesUncert="Total", jetType="AK4PFchs",   isFastSim=o_isFastSim, metBranchName=o_metBranchName)
    fatjetCorrector = createJMECorrector(isMC=o_isMC, dataYear=o_dataYear, runPeriod=o_runPeriod, jesUncert="Total", jetType="AK8PFPuppi", isFastSim=o_isFastSim, metBranchName=o_metBranchName)
    
    # ----------------------- Pileup Weights ------------------------
    if o_dataYear == "UL2016":
        puWeightProducer = puWeight_UL2016
    elif o_dataYear == "UL2017":
        puWeightProducer = puWeight_UL2017
    elif o_dataYear == "UL2018":
        puWeightProducer = puWeight_UL2018
    
    # ----------------------- Postprocessor -------------------------
    modules = [jetmetCorrector(),fatjetCorrector()]
    #modules = [jetmetCorrector()]
    #modules = [fatjetCorrector()]
    if o_isMC:
        modules.append(puWeightProducer())
    
    p=PostProcessor(".",infnames,"",None,modules,provenance=True,prefetch=options.prefetch,maxEntries=options.maxEntries)
    p.run()

if os.path.exists(os.path.basename(infnames[0]).replace(".root","_Skim.root")):
    os.rename(os.path.basename(infnames[0]).replace(".root","_Skim.root"), outfname)
    print "Successfully created postprocessed file: "+outfname
else:
    print "Prostprocessing failed"
