#ifndef ANALYZER_UTILS_H
#define ANALYZER_UTILS_H
//-----------------------------------------------------------------------------
// File:        Analyzer.h
// Description: Analyzer header for ntuples created by B2GTTreeMaker
// Created:     Tue Nov 24 2015
// Author:      Sezen Sekmen, Janos Karancsi
//-----------------------------------------------------------------------------
// -- System

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <fstream>

#include "treestream.h"
#include "treestream.cc"

// -- Root

#include "TROOT.h"
#include "TApplication.h"
#include "TDirectory.h"
#include "TCanvas.h"
#include "TFile.h"
#include "TKey.h"
#include "TH2.h"
#include "TGraphAsymmErrors.h"

//-----------------------------------------------------------------------------
// -- Utilities
//-----------------------------------------------------------------------------
namespace utils {
  
  //___________________________________________________
  //                Run I top-pt reweighting
  
  // SUSY group recommendation for Run II - use Run I recipe:
  // https://hypernews.cern.ch/HyperNews/CMS/get/susy/2112.html

  // Scalefactor for top pt reweighting
  // Taken from this twiki: https://twiki.cern.ch/twiki/bin/view/CMS/TopPtReweighting#Studies
  // Values used are the ones for the 8 TeV, all combined measurement
  double GetTopPtScaleFactor(double toppt){ // toppt is generator top(antitop) pt
    double a = 0.156;
    double b = -0.00137;
    return exp(a+b*toppt);
  }
  
  //___________________________________________________
  //                     Other

  void
  error(std::string message)
  {
    std::cout << "** error ** " << message << std::endl;
    exit(0);
  }
  
  std::string 
  strip(std::string line)
  {
    int l = line.size();
    if ( l == 0 ) return std::string("");
    int n = 0;
    while (((line[n] == 0)    ||
  	  (line[n] == ' ' ) ||
  	  (line[n] == '\n') ||
  	  (line[n] == '\t')) && n < l) n++;
  
    int m = l-1;
    while (((line[m] == 0)    ||
  	  (line[m] == ' ')  ||
  	  (line[m] == '\n') ||
  	  (line[m] == '\t')) && m > 0) m--;
    return line.substr(n,m-n+1);
  }
  
  std::string
  nameonly(std::string filename)
  {
    int i = filename.rfind("/");
    int j = filename.rfind(".");
    if ( j < 0 ) j = filename.size();
    return filename.substr(i+1,j-i-1);
  }
  //-----------------------------------------------------------------------------
  struct outputFile
  {
    outputFile(std::string filename)
      : filename_(filename),
        file_(new TFile(filename_.c_str(), "recreate")),
        tree_(0),
        b_weight_(0),
        entry_(0),
        SAVECOUNT_(50000)
    {
      file_->cd();
      hist_ = new TH1D("counts", "", 1,0,1);
      //hist_->SetBit(TH1::kCanRebin);
      hist_->SetCanExtend(TH1::kAllAxes);
      hist_->SetStats(0);
    }
    
    outputFile(std::string filename, itreestream& stream, int savecount=50000) 
      : filename_(filename),
        file_(new TFile(filename.c_str(), "recreate")),
        tree_(stream.tree()->CloneTree(0)),
        b_weight_(tree_->Branch("eventWeight", &weight_, "eventWeight/D")),
        entry_(0),
        SAVECOUNT_(savecount)
    {
      std::cout << "events will be skimmed to file "
  	      << filename_ << std::endl;
      file_->cd();
      hist_ = new TH1D("counts", "", 1,0,1);
      //hist_->SetBit(TH1::kCanRebin);
      hist_->SetCanExtend(TH1::kAllAxes);
      hist_->SetStats(0);
    }
    
    void addEvent(double weight=1)
    {
      if ( tree_ == 0 ) return;
      
      weight_ = weight;
      file_   = tree_->GetCurrentFile();
      file_->cd();
      tree_->Fill();
      
      entry_++;
      if ( entry_ % SAVECOUNT_ == 0 )
        tree_->AutoSave("SaveSelf");
    }
    
    void count(std::string cond, double w=1.0)
    {
      hist_->Fill(cond.c_str(), w);
    }
    
    void close()
    {
      std::cout << "==> histograms saved to file " << filename_ << std::endl;
      if ( tree_ != 0 )
        {
  	std::cout << "==> events skimmed to file " << filename_ << std::endl;
  	file_ = tree_->GetCurrentFile();
        }
      file_->cd();
      //file_->Write("", TObject::kWriteDelete);
      file_->Write();
      //file_->ls();
      file_->Close();
    }
    
    std::string filename_;  
    TFile* file_;
    TTree* tree_;
    TH1D*  hist_;
    TBranch* b_weight_;
    double     weight_;
    int    entry_;
    int    SAVECOUNT_;
  };
  
  struct commandLine
  {
    std::string progName;
    std::string outputFileName;            // first non option argument
    std::vector<std::string> fileNames;    // second and rest non optional arguments
    std::vector<std::string> allFileNames; // Needed when splitting to separate jobs
    std::string dirname;                   // extracted from the 1st filename
    bool isData;                           // determined automatically from input file names
    bool isBkg;                            // determined automatically from input file names
    bool isSignal;                         // determined automatically from input file names
    std::string signalName;                // determined automatically from input file names
    int  quickTest;                        // Do a quick test on 1/100th of events
    bool noPlots;                          // Do not make analysis histos (for skimming)
    int ifirst;
    int ilast;
  };
  
  // Read ntuple fileNames from file list
  std::vector<std::string>
  getFilenames(std::string filelist)
  {
    std::vector<std::string> v;
    if (filelist.find(".root")!=std::string::npos) {
      v.push_back(filelist);
    } else {
      std::ifstream stream(filelist.c_str());
      if ( !stream.good() ) error("unable to open file: " + filelist);
      
      // Get list of ntuple files to be processed
      
      std::string filename;
      while ( stream >> filename )
        if ( strip(filename) != "" ) v.push_back(filename);
    }
    return v;
  }
  
  void
  decodeCommandLine(int argc, char** argv, commandLine& cl, std::vector<std::string>& vname_data, std::vector<std::string>& vname_signal)
  {
    cl.progName = std::string(argv[0]);

    if ( argc < 3 ) error("<output filename> and <input file list> was not given!");

    // decide whether input is data
    cl.isData = false;
    cl.isBkg  = false;
    cl.isSignal = false;
    int n_data_arg = 0;
    int n_signal_arg = 0;
    int n_bkg_arg = 0;
    int n_input = 0;

    // Do a quick test on 1/100 statistics
    cl.quickTest = 0;

    // Don't fill any histos (useful for skimmin jobs)
    cl.noPlots = false;

    // Change event loop range (default=-1, all events)
    cl.ifirst = -1;
    cl.ilast = -1;

    for (int iarg=1; iarg<argc; ++iarg) {
      std::string arg = argv[iarg];
      // look for optional arguments (argument has "=" in it)
      size_t f = arg.find("=");
      if (f!=std::string::npos) {
	std::string option=arg.substr(0, f);
	std::stringstream value;
	value<<arg.substr(f+1, arg.size()-f-1);
	// reading option
	if (option=="quickTest") value>>cl.quickTest;
	if (option=="noPlots") value>>cl.noPlots;
	if (option=="fullFileList") {
	  std::string fullFileList;
	  value>>fullFileList;
	  std::vector<std::string> list = getFilenames(fullFileList);
	  cl.allFileNames.insert(cl.allFileNames.end(), list.begin(), list.end());
	}
	if (option=="ifirst") value>>cl.ifirst;
	if (option=="ilast") value>>cl.ilast;
      } else {
	if (cl.outputFileName=="") {
	  // 1st non-optional (i.e xxx=yyy) command line argument is output ifle
	  cl.outputFileName = arg;
	  std::cout<<"output file is: "<<cl.outputFileName<<std::endl;
	} else {
	  // 2nd and rest non-optional argument is input file(s)
	  if (arg.find(".txt")!=std::string::npos) {
	    // if txt file, read it's contents
	    std::vector<std::string> list = getFilenames(arg);
	    cl.fileNames.insert(cl.fileNames.end(), list.begin(), list.end());
	    if (arg.find("/data/")!=std::string::npos) n_data_arg++;
	    else if (arg.find("/signals/")!=std::string::npos) n_signal_arg++;
	    else if (arg.find("/backgrounds/")!=std::string::npos) n_bkg_arg++;
	  } else {
	    // Otherwise add all root files to input file list
	    if (std::string(arg).find(".root")!=std::string::npos) cl.fileNames.push_back(arg);
	    else error(std::string("argument ")+arg+" is not a root file or a list (.txt file)!");
	    // Check if filename is data or signal
	    bool found = false;
	    for (auto data : vname_data) if (!found&&std::string(arg).find(data)!=std::string::npos) { 
	      n_data_arg++;
	      found=1;
	    }
	    for (auto signal : vname_signal) if (!found&&std::string(arg).find(signal)!=std::string::npos) { 
	      n_signal_arg++;
	      cl.signalName = signal;
	      found=1; 
	    }
	    if (!found) n_bkg_arg++;
	  }
	  ++n_input;
	}
      }
    }
    // This list needed to get total weight when splitting jobs
    if (!cl.allFileNames.size())
      cl.allFileNames.insert(cl.allFileNames.end(), cl.fileNames.begin(), cl.fileNames.end());

    // Get the directory name from the first file (used for plotting)
    if (cl.fileNames.size()>0) {
      std::stringstream ss;
      ss<<cl.fileNames[0];
      std::string prev, read, dirname;
      while(std::getline(ss, read, '/')) {
	if (read.find(".")!=std::string::npos)
	  cl.dirname = prev;
	prev = read;
      }
    }

    // check number of input file arguments containing data-like strings
    if (n_data_arg != 0 && n_data_arg != n_input) error(" Data mixed with MC!");
    else if (n_signal_arg != 0 && n_signal_arg != n_input) error(" signal mixed with other samples!");
    else if (n_bkg_arg != 0 && n_bkg_arg != n_input) error(" Background mixed with other samples (OR signal not defined?)!");
    else {
      cl.isData = (n_data_arg == n_input);
      cl.isBkg  = (n_bkg_arg == n_input);
      cl.isSignal = (n_signal_arg == n_input);
    }
  }
  
  // Get efficiency from a 2D histogram (for error use 2nd)
  double geteff1D(TH1* h, double x, bool use_overflow=false) {
    double eff = 0;
    for (int i=1, n=h->GetNbinsX(); i<=n; i++) {
      eff = h->GetBinContent(i);
      if (h->GetXaxis()->GetBinUpEdge(i)>x) break;
    }
    if (use_overflow&&x>=h->GetXaxis()->GetBinUpEdge(h->GetNbinsX())) 
      eff = h->GetBinContent(h->GetNbinsX()+1);
    return eff;
  }
  void geteff1D(TH1* h, double x, double& eff, double& err) {
    //++  int binx = h->GetXaxis()->FindBin(x);
    //++  /*
    //++  // If the bin is out of range, use the closest bin and double the error
    //++  bool double_error = 0;
    //++  if (binx==0) { double_error = 1; binx = 1; }
    //++  if (binx>h->GetNbinsX()) { double_error = 1; binx = h->GetNbinsX(); }
    //++  eff = h->GetBinContent(binx);
    //++  err = h->GetBinError  (binx);
    //++  if (double_error) err *= 2;
    //++  */
    //++  // If the bin is out of range, use the closest bin
    //++  if (binx==0) binx = 1;
    //++  if (binx>h->GetNbinsX()) binx = h->GetNbinsX();
    //++  eff = h->GetBinContent(binx);
    //++  err = h->GetBinError  (binx);
    // If the bin is out of range, use the closest bin
    eff = 0, err = 0;
    for (int i=1, n=h->GetNbinsX(); i<=n; i++) {
      eff = h->GetBinContent(i);
      err = h->GetBinError(i);
      if (h->GetXaxis()->GetBinUpEdge(i)>x) break;
    }
  }
  // Get efficiency (and assymmetric errors) from TGraph
  void geteff_AE(TGraphAsymmErrors* g, double x, double& eff, double& err_up, double& err_down) {
    double X;
    // If the bin is out of range, use the closest bin
    for (int i=0, n=g->GetN(); i<n; ++i) {
      g->GetPoint(i,X,eff);
      err_up = g->GetErrorYhigh(i);
      err_down = g->GetErrorYlow(i);
      if (x<X+g->GetErrorXhigh(i)) break;
    }
  }
  void geteff_AE(const TGraphAsymmErrors& g, double x, double& eff, double& err_up, double& err_down) {
    double X;
    // If the bin is out of range, use the closest bin
    for (int i=0, n=g.GetN(); i<n; ++i) {
      g.GetPoint(i,X,eff);
      err_up = g.GetErrorYhigh(i);
      err_down = g.GetErrorYlow(i);
      if (x<X+g.GetErrorXhigh(i)) break;
    }
  }
  double geteff_AE(TGraphAsymmErrors* g, double x) {
    double X, Y;
    // If the bin is out of range, use the closest bin
    for (int i=0, n=g->GetN(); i<n; ++i) {
      g->GetPoint(i,X,Y);
      if (x<X+g->GetErrorXhigh(i)) break;
    }
    return Y;
  }

  // Get efficiency from a 2D histogram (for error use 2nd)
  double geteff2D(TH2* h, double x, double y)
  {
    double eff = 0.0;
    for (int i=1; i<=h->GetNbinsX(); i++) {
      double xmin = h->GetXaxis()->GetBinLowEdge(i);
      double xmax = h->GetXaxis()->GetBinUpEdge(i);
      if (!(x >= xmin && x < xmax)) continue;
      for (int j=1; j<h->GetNbinsY()+1; j++) {
	double ymin = h->GetYaxis()->GetBinLowEdge(j);
	double ymax = h->GetYaxis()->GetBinUpEdge(j);
	if (y >= ymin && y < ymax) {
	  eff = h->GetBinContent(i, j);
	  break;
	}
      }
    }
    return eff;
  }
  void geteff2D(TH2* h, double x, double y, double& eff, double& err)
  {
    int binx = h->GetXaxis()->FindBin(x), biny = h->GetYaxis()->FindBin(y);
    /*
    // If the bin is out of range, use the closest bin and double the error
    bool double_error = 0;
    if (binx==0) { double_error = 1; binx = 1; }
    if (biny==0) { double_error = 1; biny = 1; }
    if (binx>h->GetNbinsX()) { double_error = 1; binx = h->GetNbinsX(); }
    if (biny>h->GetNbinsY()) { double_error = 1; biny = h->GetNbinsY(); }
    eff = h->GetBinContent(binx, biny);
    err = h->GetBinError  (binx, biny);
    if (double_error) err *= 2;
    */
    // If the bin is out of range, use the closest bin
    if (binx==0) binx = 1;
    if (biny==0) biny = 1;
    if (binx>h->GetNbinsX()) binx = h->GetNbinsX();
    if (biny>h->GetNbinsY()) biny = h->GetNbinsY();
    eff = h->GetBinContent(binx, biny);
    err = h->GetBinError  (binx, biny);
  }

  TH1F* getplot_TH1F(const char* filename, const char* histoname, const char* clonename) {
    TFile f(filename, "READ");
    TH1F *h = (TH1F*)f.Get(histoname);
    h = (TH1F*)h->Clone(clonename);
    h->SetDirectory(0);
    return h;
  }

  TH1D* getplot_TH1D(const char* filename, const char* histoname, const char* clonename) {
    TFile f(filename, "READ");
    TH1D *h = (TH1D*)f.Get(histoname);
    h = (TH1D*)h->Clone(clonename);
    h->SetDirectory(0);
    return h;
  }

  TH2F* getplot_TH2F(const char* filename, const char* histoname, const char* clonename) {
    TFile f(filename, "READ");
    TH2F *h = (TH2F*)f.Get(histoname);
    h = (TH2F*)h->Clone(clonename);
    h->SetDirectory(0);
    return h;
  }

  TH2D* getplot_TH2D(const char* filename, const char* histoname, const char* clonename) {
    TFile f(filename, "READ");
    TH2D *h = (TH2D*)f.Get(histoname);
    h = (TH2D*)h->Clone(clonename);
    h->SetDirectory(0);
    return h;
  }

  TGraphAsymmErrors* getplot_TGraphAsymmErrors(const char* filename, const char* histoname, const char* clonename) {
    TFile f(filename, "READ");
    TGraphAsymmErrors *g = (TGraphAsymmErrors*)f.Get(histoname);
    g = (TGraphAsymmErrors*)g->Clone(clonename);
    return g;
  }

  TGraphAsymmErrors* getplot_TGraphAsymmErrors_fromCanvas(const char* filename, const char* canvasname, int index, const char* clonename) {
    TFile f(filename, "READ");
    TCanvas *c = (TCanvas*)f.Get(canvasname);
    TGraphAsymmErrors *g = (TGraphAsymmErrors*)c->GetListOfPrimitives()->At(index);
    g = (TGraphAsymmErrors*)g->Clone(clonename);
    return g;
  }

  Double_t* getVariableBinEdges(int num_entries, Double_t* tmp_array)
  { 
    Double_t* my_array = new Double_t[num_entries];
    for (int i = 0; i != num_entries; ++i) {
      my_array[i] = tmp_array[i];
      //cout << "bin edge " << i << " : " << my_array[i] << endl;
    }
    return my_array;
  }
}

#endif
