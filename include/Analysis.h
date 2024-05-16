#ifndef ANALYSIS_H
#define ANALYSIS_H

// Private headers
#include "tnm.h"
#include "Variables.h"
#include "Weighting.h"
#include "EventSelections.h"
#include "ScaleFactors.h"
#include "PlottingBase.h"

// 3rd party headers
#include "TH3.h"
#include "TStopwatch.h"
#include "TString.h"

// common libraries
#include <iostream>
#include <vector>

// _____________________________________________________________
//        Analysis: Methods common in all analysis

class Analysis
{
public:
  Analysis(Variables& var) :
    weighting(Weighting(var)),
    event_selections(EventSelections(var)),
    scale_factors(ScaleFactors(var)),
    plotting(Plotting(var))
    //v(var)
  {
    sw_1_  = new TStopwatch;
    sw_1k_  = new TStopwatch;
    sw_10k_ = new TStopwatch;
    sw_job_ = new TStopwatch;

    syst = {
      "lumi", "toppt", "isr", "pileup",
      "alphas", "facscale", "renscale", "facrenscale", "lostlep",
      "trigger", "jes", "jer", "met", "ak8scale",
      "elereco", "eleid", "eleiso", "elefastsim",
      "muontrk", "muonidiso", "muonfastsim",
      "btag", "btagfastsim",
      "wtag", "wtagfastsim", "wmistag", "wmistagfastsim", "wmasstag","wantitag",
      "toptag", "toptagfastsim", "topmistag", "topmistagfastsim",
      "top0bmasstag","topmasstag","topantitag"
    };
  }
  ~Analysis() {
    delete sw_1_;
    delete sw_1k_;
    delete sw_10k_;
    delete sw_job_;
  }

  Weighting weighting;
  
  EventSelections event_selections;
  
  ScaleFactors scale_factors;
  
  Plotting plotting;

  void job_monitoring(const int&, const int&, const int&, const std::string&, const float);

  void init_histos(const bool&);

  void fill_histos(const bool&, const bool&, const unsigned int&, const double&);

  std::vector<std::string> syst;

  void initialize1(const bool&, const unsigned int&, const unsigned int&);

  void initialize2(const bool&, const unsigned int&, const unsigned int&);

private:

  TStopwatch *sw_1_, *sw_1k_, *sw_10k_, *sw_job_;
  std::map<std::string, int> bad_files;

  TH1D* h_read_speed_1k;
  TH1D* h_read_speed_10k;
  TH1D* h_read_speed_job;
  TH2D* h_read_speed_vs_nevt_10k;
  TH2D* h_read_speed_vs_nevt_job;
  TH1D* h_runtime_job;
  TH2D* h_runtime_vs_nevt_job;
};




//_______________________________________________________
//              Define Histograms here
void
Analysis::init_histos(const bool& varySystematics)
{
  // job_monitoring histos
  h_read_speed_1k              = new TH1D("read_speed_1k",          ";Read speed (Events/s);Measurement/1k Event",  1000,0,10000);
  h_read_speed_10k             = new TH1D("read_speed_10k",         ";Read speed (Events/s);Measurement/10k Event", 1000,0,10000);
  h_read_speed_job             = new TH1D("read_speed_job",         ";Read speed (Events/s);Measurement/Job",       1000,0,10000);
  h_read_speed_vs_nevt_10k     = new TH2D("read_speed_vs_nevt_10k", ";Entry;Read speed (Events/s)/10k Event",       100,0,10000000, 200,0,10000);
  h_read_speed_vs_nevt_job     = new TH2D("read_speed_vs_nevt_job", ";Total Entries;Read speed (Events/s)/Job",     100,0,10000000, 200,0,10000);
  h_runtime_job                = new TH1D("runtime_job",            ";Total job run-time (min)",                    600,0,600);
  h_runtime_vs_nevt_job        = new TH2D("runtime_vs_nevt_job",    ";Total Entries;Total job run-time (min)",      100,0,10000000, 600,0,600);
}

//_______________________________________________________
//               Fill Histograms here
void
Analysis::fill_histos(const bool& varySystematics, const bool& runOnSkim, const unsigned int& syst_index, const double& weight)
{
}



//_______________________________________________________
//                Benchmarking (batch) jobs

void
Analysis::job_monitoring(const int& entry, const int& ifirst, const int& ilast, const std::string& curr_file, const float threshold=5)
{
  int curr_entry = entry - ifirst;
  if (curr_entry==0) {
    sw_1k_ ->Reset();
    sw_10k_->Reset();
    sw_job_->Reset();
    sw_1k_ ->Start(kFALSE);
    sw_10k_->Start(kFALSE);
    sw_job_->Start(kFALSE);
    std::cout<<"UnixTime-FirstEvent: "<<std::time(0)<<std::endl;
  } else {
    double time_1 = sw_1_->RealTime();
    sw_1_->Reset(); sw_1_->Start(kFALSE);
    if (time_1>threshold&&curr_entry!=1) {
      ++bad_files[curr_file];
    }
    if (curr_entry%1000==0) {
      double meas_1k = 1000/sw_1k_->RealTime();
      h_read_speed_1k->Fill(meas_1k);
      sw_1k_->Reset();
      sw_1k_->Start(kFALSE);
      //std::cout<<"Meas  1k: "<<meas_1k<<std::endl;
    }
    if (curr_entry%10000==0) {
      double meas_10k = 10000/sw_10k_->RealTime();
      h_read_speed_10k->Fill(meas_10k);
      h_read_speed_vs_nevt_10k->Fill(curr_entry, meas_10k);
      sw_10k_->Reset();
      sw_10k_->Start(kFALSE);
      double time_job = sw_job_->RealTime();
      sw_job_->Start(kFALSE);
      //std::cout<<"Meas 10k: "<<meas_10k<<std::endl;
      std::cout <<"UnixTime: "<< std::time(0) << "  JobTime(s): " << time_job << "  Nevent: " << curr_entry << " (" << ((float)curr_entry)/(ilast-ifirst)*100 
                << " %)  ReadSpeed(event/s): " << (curr_entry+1)/time_job <<"        "<< std::endl;
    }
    if (entry+1==ilast) {
      sw_job_->Stop();
      double meas_job = (ilast-ifirst)/sw_job_->RealTime();
      h_read_speed_job->Fill(meas_job);
      h_read_speed_vs_nevt_job->Fill((ilast-ifirst), meas_job);
      h_runtime_job->Fill(sw_job_->RealTime()/60.);
      h_runtime_vs_nevt_job->Fill((ilast-ifirst), sw_job_->RealTime()/60.);
      std::cout<<"JobMonitoringReport RunTime(s): "<<sw_job_->RealTime()<<" Nevents: "<<(ilast-ifirst)<<" Nevt/s: "<<meas_job<<std::endl;
      for (const auto& bad_file : bad_files)
        std::cout<<"Badly readable file found: "<<bad_file.first<<" N_occurence: "<<bad_file.second<<std::endl;
      std::cout<<"UnixTime-LastEvent: "<<std::time(0)<<std::endl;
    }
  }
}

void
Analysis::initialize1(const bool& varySystematics, const unsigned int& syst_nSyst, const unsigned int& syst_index) {
  // Setup histograms and read input histograms for weighting/scale_factors
  init_histos(varySystematics);
  weighting.init_weight_histos();
  scale_factors.init_sf_histos();
  event_selections.define_preselections();
  event_selections.define_event_selections();
  plotting.define_histo_settings           (weighting, event_selections, syst_nSyst, syst_index);
  plotting.define_additional_histo_settings(weighting, event_selections, syst_nSyst, syst_index);
  weighting.init_input();
  scale_factors.init_input();
}

void
Analysis::initialize2(const bool& varySystematics, const unsigned int& syst_nSyst, const unsigned int& syst_index) {
  plotting.define_analysis_histos  (weighting, syst_nSyst, syst_index);
  plotting.define_additional_histos(weighting, syst_nSyst, syst_index);
}

#endif // End header guard
