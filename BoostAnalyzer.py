#!/usr/bin/env python
# ----------------------------------------------------------------------------
#  File:        BoostAnalyzer.py
#  Description: Analyzer for simple ntuples, such as those created by
#               TheNtupleMaker
#  Created:     Thu Jul 26 16:24:24 2018 by mkanalyzer.py
#  Author:      Sezen Sekmen
# ----------------------------------------------------------------------------
import os, sys, re
from tnm import *
from ROOT import *
# ----------------------------------------------------------------------------
# -- Constants, procedures and functions
# ----------------------------------------------------------------------------


# ----------------------------------------------------------------------------
def main():

    cl = commandLine()
    
    # Get names of ntuple files to be processed
    filenames = getFilenames(cl.filelist)

    # Create tree reader
    stream = itreestream(filenames, "Events")
    if not stream.good():
        error("can't read input files")

    # Create a buffer to receive events from the stream
    # The default is to select all branches.
    # Use second argument to select specific branches
    # Example:
    #   varlist = 'Jet_PT Jet_Eta Jet_Phi'
    #   ev = eventBuffer(stream, varlist)
    #
    ev = eventBuffer(stream)

    nevents = ev.size()
    #print "number of events:", nevents
    f = open("events.txt", "a+")
    f.write('%d\n' % nevents)
    f.close()

    # Create file to store histograms
    #of = outputFile(cl.outputfilename)

    # ------------------------------------------------------------------------
    # Define histograms
    # ------------------------------------------------------------------------
    #setStyle()

    # ------------------------------------------------------------------------
    # Loop over events
    # ------------------------------------------------------------------------
    
    #for entry in xrange(nevents):
    #    ev.read(entry)

        # Uncomment the following line if you wish to copy variables into
        # structs. See the header eventBuffer.h to find out what structs
        # are available. Alternatively, you can call individual fill
        # functions, such as ev.fillJets().
        #ev.fillObjects();

        # analysis
        
    ev.close()
    #of.close()
# ----------------------------------------------------------------------------
try:
   main()
except KeyboardInterrupt:
   print "bye!"
