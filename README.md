# BoostAnalyzer17

The event structure can be seen in include/eventBuffer.h

As usual do

source setup.sh

make clean

make -j Analyzer

If you use 2016 implemenation code, you have to fix the Analysis_*.h, This is the same mehtoud as the 2016's.

./Analyzer DY.root filelists/backgrounds/filelist_DY.txt

The condor scripts are in 
https://github.com/cghuh/RazorBoost-CMS-Connect

The filelist of 2017 NANOAOD ntuple is locate in
https://github.com/cghuh/RazorBoost-CMS-Connect/blob/master/filelist.txt
