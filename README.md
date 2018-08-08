# BoostAnalyzer17

This is a clean analyzer automatically created based on test94X_NANO.root .
The event structure can be seen in include/eventBuffer.h

As usual do

source setup.sh
make clean
make

./BoostAnalyzer filelist.txt

For some reason, currently the compilation takes insanely long.  Will look for a way to fix this.

If you use 2016 implemenation code, you have to fix the Analysis_*.h, This is the same mehtoud as the 2016's.

./Analyzer filelists/backgrounds/filelist_DY.txt DY.root
