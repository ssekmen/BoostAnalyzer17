# BoostAnalyzer17

Razor Boost and Inclusive analysis targeting the full Run2 dataset

## Recipe

```Shell
export SCRAM_ARCH=slc7_amd64_gcc700
cmsrel CMSSW_10_2_16_UL
cd CMSSW_10_2_16_UL/src
cmsenv
git clone git@github.com:ssekmen/BoostAnalyzer17.git
git clone git@github.com:cghuh/RazorBoost-CMS-Connect.git
git clone https://github.com/cms-nanoAOD/nanoAOD-tools.git PhysicsTools/NanoAODTools
scram b -j 20
cd BoostAnalyzer17
ln -sfT ../RazorBoost-CMS-Connect condor
ln -sf ../PhysicsTools/NanoAODTools nano
source setup.sh
python condor/setup.py
```

## Run

edit the settings_*.h and Plotting_*.h file which is included in Analyzer.cc and then run the code

```Shell
cmsenv
source setup.sh
make clean
make -j8 Analyzer
./Analyzer test.root root://eoscms.cern.ch//eos/cms/store/group/phys_susy/razor/RazorBoostNtuple/2017/backgrounds/TTToSemiLeptonic_TuneCP5_13TeV-powheg-pythia8/0E2C37BF-4630-DB40-AB8F-BE75DA1F2B3B.root
```

The condor scripts are in 
https://github.com/cghuh/RazorBoost-CMS-Connect

The filelist of 2017 NANOAOD ntuple is locate in
https://github.com/cghuh/RazorBoost-CMS-Connect/blob/master/filelist_2017.txt
