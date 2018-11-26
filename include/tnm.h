#ifndef TNM_H
#define TNM_H
//-----------------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cmath>

#include "TROOT.h"
#include "TFile.h"
#include "TTree.h"
#include "TBranch.h"
#include "TH1.h"
#include "TMath.h"
#include "TString.h"
#include "TStyle.h"
#include "TApplication.h"
#include "TH2.h"
#include "TH3.h"
#include "TGraphAsymmErrors.h"

#ifdef PROJECT_NAME
#include "PhysicsTools/TheNtupleMaker/interface/eventBuffer.h"
#else
#include "eventBuffer.h"
#endif
//-----------------------------------------------------------------------------

struct outputFile
{
  outputFile(std::string filename);
  outputFile(std::string filename, eventBuffer& ev, int savecount=50000); 
  void write(double weight=1);
  void count(std::string cond, double w=1);
  void close();

  std::string filename_;  
  TFile* file_;
  TTree* tree;
  TH1F*  hist_;
  TBranch* b_weight_;
  double     weight_;
  int    entry_;
  int    SAVECOUNT_;
  eventBuffer* ev_;
};

struct commandLine
{
  commandLine();
  commandLine(int argc, char** argv);
  ~commandLine() {}
  std::string progname;
  std::string filelist;
  std::string outputfilename;
  std::vector<std::string> fileNames;
  std::vector<std::string> allFileNames;
  std::string dirname;
  bool isData;
  bool isBkg;
  bool isSignal;
  std::string signalName;
  int quickTest;
  bool noPlots;
  int ifirst;
  int ilast;

  void decode(int argc, char** argv);
};

///
struct matchedPair
{
  int first;
  int second;
  double distance;
  bool operator<(const matchedPair& o) const 
  { return this->distance < o.distance; }
};

/// Collect together standard attributes and permit pT-sorting.
struct ptThing
{
  ptThing();
  ptThing(int index_, int id_,
          double pt_, double eta_, double phi_, std::string name_="");
  ~ptThing();

  /// Copy constructor.
  ptThing(const ptThing& rhs);

  /// Assignment. 
  ptThing& operator=(const ptThing& rhs);

  /** Find $|Delta R = \sqrt{\Delta\phi^2+\Delta\eta^2}$ between this
      PtThing and the given.
  */
  double deltaR(ptThing& thing);

  /// Compare direction of this PtThing with another using deltaR.
  bool matches(ptThing& thing, double drcut=0.4);

  int index;
  int id;
  double pt;
  double eta;
  double phi;
  std::string name;

  /// Map for additional variables.
  std::map<std::string, double> var;

  /// To sort PtThings in descending pt.
  bool operator<(const ptThing& o) const { return o.pt < this->pt; }
};

void decodeCommandLine(int argc, char** argv, commandLine& cl, std::vector<std::string>& vname_data, std::vector<std::string>& vname_signal);
void error(std::string message);
std::string strip(std::string line);
std::vector<std::string> split(std::string str);
std::string change(std::string str,
		   std::string oldstr,
		   std::string newstr);
std::string nameonly(std::string filename);
std::string shell(std::string cmd);

/// Read ntuple filenames from file list
std::vector<std::string> getFilenames(std::string filelist);

double deltaPhi(double phi1, double phi2);

///
double deltaR(double eta1, double phi1, double eta2, double phi2);

double geteff1D(TH1* h, double x, bool use_overflow);
void geteff1D(TH1* h, double x, double& eff, double& err);
void geteff_AE(TGraphAsymmErrors* g, double x, double& eff, double& err_up, double& err_down);
void geteff_AE(const TGraphAsymmErrors& g, double x, double& eff, double& err_up, double& err_down);
double geteff_AE(TGraphAsymmErrors* g, double x);
double geteff2D(TH2* h, double x, double y);
void geteff3D(TH3* h, double x, double y, double z, double& eff, double& err);
double geteff3D(TH3* h, double x, double y, double z);
void geteff2D(TH2* h, double x, double y, double& eff, double& err);
TH1D* getplot_TH1D(const char* filename, const char* histoname, const char* clonename);
TH2F* getplot_TH2F(const char* filename, const char* histoname, const char* clonename);
TH2D* getplot_TH2D(const char* filename, const char* histoname, const char* clonename);
TH3D* getplot_TH3D(const char* filename, const char* histoname, const char* clonename);
TGraphAsymmErrors* getplot_TGraphAsymmErrors(const char* filename, const char* histoname, const char* clonename);
Double_t* getVariableBinEdges(int num_entries, Double_t* tmp_array);
///
//std::vector<matchedPair> deltaR(std::vector<ptThing>& v1, 
//				std::vector<ptThing>& v2);
///
void setStyle();

///
std::string particleName(int pdgid);
#endif

