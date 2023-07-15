#ifndef PLOTTINGBASE_H
#define PLOTTINGBASE_H

// Private headers
#include "Variables.h"
#include "Weighting.h"
#include "EventSelections.h"
#include "SmartHistos.h"

// 3rd party headers

// common libraries
#include <iostream>
#include <vector>

#define BM_GLU      2000
#define BM_GLU_NEU   200
#define BM_SQU      1200
#define BM_SQU_NEU   200
#define BM_SQU_NEU2 1000
#define BM_EWK       700
#define BM_EWK_NEU   200

class PlottingBase
{
	public:
		PlottingBase(Variables& var) : v(var) {}
		~PlottingBase() {}

		SmartHistos sh;

		void define_histo_settings(const Weighting&, EventSelections&, const unsigned int&, const unsigned int&);

		void define_analysis_histos(const Weighting&, const unsigned int&, const unsigned int&);

		void calculate_plotting_variables(eventBuffer&, const unsigned int&);

		void fill_analysis_histos(EventSelections&, const Weighting&, const unsigned int&, const double&);

		void load_analysis_histos(std::string);

		void save_analysis_histos(bool);

		std::map<std::string, std::function<int()> > top_benchmarks;
		std::map<std::string, std::function<int()> > WZH_benchmarks;
		std::map<std::string, std::function<int()> > all_benchmarks;

		Variables& v;

		std::vector<std::string> all_cuts;

		typedef struct Sample { std::string postfix; std::string legend; std::string color; std::vector<std::string> dirs; } Sample;
		typedef struct PostfixOptions { size_t index; std::string postfixes; std::string legends; std::string colors; } PostfixOptions;

		typedef EventSelections::Regions Region;

		PostfixOptions get_pf_opts_(std::vector<std::vector<Sample> >, const TString&);

		void add_unrolled_bins(std::string, std::string, std::string,
				std::function<double()>, std::function<double()>,
				std::vector<double>, std::vector<double>,
				std::vector<int>, int, int, bool);



		std::map<int, std::vector<TH2D*> > m_vh_signal;
		std::map<int, std::vector<TH2D*> > m_vh_signal_new;
		//std::map<int, std::vector<TH2D*> > m_vh_signal_v2;
		std::vector<TH2D*> vvh_MRR2_bkg;
		std::vector<TH2D*> vvh_MRR2_bkg_new;
		std::vector<TH1D*> vvh_MRR2_data;
		std::vector<TH1D*> vvh_MRR2_data_new;
		std::vector<TH1D*> vvh_MRR2_data_binopt;
		std::vector<TH1D*> vvh_MRR2_data_new_binopt;

		std::map<int, std::vector<TH2D*> > m_vh_signal_binopt;
		std::map<int, std::vector<TH2D*> > m_vh_signal_new_binopt;
		std::vector<TH2D*> vvh_MRR2_bkg_binopt;
		std::vector<TH2D*> vvh_MRR2_bkg_new_binopt;

		// --------------------------------------------------------------------
		//                       Plotting options
		// --------------------------------------------------------------------

		std::string d = "HISTE1";
		// Control region stack plots (only data)
		std::string o_stk_d = "LogStack1AddRatioTwoCol98AddIntApproval15";
		std::string o_stk_s = "LogStack1AddRatioTwoCol98AddIntApproval45";
		std::string O_stk_d = "LogStack1AddRatioTwoCol98Approval15";
		std::string O_stk_s = "LogStack1AddRatioTwoCol98Approval45";
		// Signal region stack plots (data + N signal)
		std::string o_stk_d_S = "LogStack7AddRatioTwoCol108AddIntApproval15";
		std::string o_stk_s_S = "LogStack7AddRatioTwoCol108AddIntApproval45";
		std::string O_stk_d_S = "LogStack7AddRatioTwoCol108Approval15";
		std::string O_stk_s_S = "LogStack7AddRatioTwoCol108Approval45";
		std::string o_stk_d_T = "LogStack4AddRatioTwoCol48AddIntApproval15";
		std::string o_stk_s_T = "LogStack4AddRatioTwoCol48AddIntApproval45";
		std::string o_stk_d_V = "LogStack7AddRatioTwoCol78AddIntApproval15";
		std::string o_stk_s_V = "LogStack7AddRatioTwoCol78AddIntApproval45";
		std::string o_stk_d_H = "LogStack5AddRatioTwoCol58AddIntApproval15";
		std::string o_stk_s_H = "LogStack5AddRatioTwoCol58AddIntApproval45";
		std::string o_1or2d_d = "Approval15";
		std::string o_1or2d_s = "Approval45";
		std::string o_norm_d = "NormApproval15";
		std::string o_norm_s = "NormApproval45";

		std::vector<double> r_Stk4 = {0,0, 1.01e-2,1e4,  0.3,0.86};
		std::vector<double> r_Stk5 = {0,0, 1.01e-2,1e5,  0.3,0.86};
		std::vector<double> r_Stk6 = {0,0, 1.01e-2,1e6,  0.3,0.86};
		std::vector<double> r_Stk7 = {0,0, 1.01e-2,1e7,  0.3,0.86};
		std::vector<double> r_Stk8 = {0,0, 1.01e-2,1e8,  0.3,0.86};
		std::vector<double> r_Stk9 = {0,0, 1.01e-1,1e9,  0.3,0.86};
		std::string Stack = "StackPlot";

		// --------------------------------------------------------------------
		//                            Colors
		// --------------------------------------------------------------------


		/*
			 Complete list of main ROOT colors:
https://root.cern.ch/doc/master/classTColor.html#C02

kWhite  = 0,   kBlack  = 1,   kGray    = 920,  kRed    = 632,  kGreen  = 416,
kBlue   = 600, kYellow = 400, kMagenta = 616,  kCyan   = 432,  kOrange = 800,
kSpring = 820, kTeal   = 840, kAzure   = 860,  kViolet = 880,  kPink   = 900
*/

		std::string Black   = "1,";
		std::string DGray   = "922,";
		std::string DRed    = "634,";
		std::string Red     = "633,";
		std::string DPink   = "902,";
		std::string Pink    = "901,";
		std::string Purple  = "617,";
		std::string DMagen  = "619,";
		std::string FMagen  = "607,"; // Fainter
		std::string Violet  = "881,";
		std::string DViolet = "882,";
		std::string DBlue   = "602,";
		std::string Blue    = "601,";
		std::string FBlue   = "593,"; // Fainter
		std::string DAzure  = "862,";
		std::string Azure   = "861,";
		std::string DCyan   = "435,";
		std::string Cyan    = "433,";
		std::string DTeal   = "844,";
		std::string Teal    = "841,";
		std::string DGreen  = "418,";
		std::string Green   = "417,";
		std::string DSpring = "822,";
		std::string Spring  = "825,";
		std::string DYellow = "402,";
		std::string Yellow  = "401,"; // Beware - might still be faint
		std::string kOrange = "800,"; // Yellowish
		std::string Orange  = "797,";
		std::string DBrown  = "803,";
		std::string Brown   = "793,";
		std::string Carrot  = "807,"; // Reddish orange

		std::string col3_red_to_blue = "633,618,601,"; // red, purple, blue
		std::string col4_red_to_cyan = "633,618,601,434,"; // Red, purple, blue, cyan
		std::string col4_cyan_to_red = "434,601,618,633,"; // Cyan, blue, purple, red
		std::string col5_green_to_red = "418,434,601,618,633,"; // green, cyan, blue, purple, red
		std::string col5_red_to_green = "633,618,601,434,418,"; // red, , purple, blue, cyan, green
		std::string col6_rainbow_dark = "601,434,418,402,633,618,"; // blue, cyan, green, yellow, red, purple
		std::string col8 = "1,601,434,418,402,807,633,618,"; // above plus black and orange
		std::string col10 = "4,6,2,800,402,417,433,9,618,633,";
		std::string col12 = "1,4,6,2,800,402,417,433,9,618,633,924,"; // black, blue, magenta, red, orange, darker yellow, darker green, darker cyan, blue-purple, dark purple, dark red
		std::string col12_rainbow = "402,416,433,600,617,632,802,813,833,863,883,892,"; // Go around first bright and then dark colors
		std::string col16 = DRed+DPink+DMagen+DViolet+DBlue+DAzure+DCyan+DTeal+DGreen+DSpring+DYellow+Orange+Carrot+Brown+Black+DGray;

		// --------------------------------------------------------------------
		//                          Binning
		// --------------------------------------------------------------------

		// Bins
		std::vector<double> E;
		std::vector<double> Pt;
		std::vector<double> PtG;
		std::vector<double> PtF;
		std::vector<double> PtO;
		std::vector<double> PtT;
		std::vector<double> PtFine;
		std::vector<double> PtPho;
		std::vector<double> PtPho2;
		std::vector<double> M;
		std::vector<double> MFine;
		std::vector<double> MW;
		std::vector<double> DeepB;
		std::vector<double> MDP;
		std::vector<double> DP;
		std::vector<double> M2;
		std::vector<double> M3;
		std::vector<double> NVTX;
		std::vector<double> R_bins;
		std::vector<double> MR_bins;
		std::vector<double> MTR_bins;
		std::vector<double> MET;
		std::vector<double> R2_bins;
		std::vector<double> HT;
		std::vector<double> HTB;
		std::vector<double> PtB;
		std::vector<double> LepPt;
		std::vector<double> LepEta;
		// Razor inclusive binning
		std::vector<double> MR_RI;
		std::vector<double> R2_RI;
		// Unrolled bin labels
		std::vector<double> MR_2D_bins;
		std::vector<double> MR_2D_bins_lep;
		std::vector<double> MRR2_2D_bins;
		std::vector<double> SR_2D_bins;
		std::vector<double> R2_2D_bins;
		std::vector<double> HT_2D_bins_old;
		std::vector<double> Pt_2D_bins;
		std::vector<double> PtLow_2D_bins;
		std::vector<double> PtHigh_2D_bins;
		std::vector<double> PtPho_2D_bins;
		std::vector<double> ElePt_2D_bins;
		std::vector<double> MuPt_2D_bins;
		std::vector<double> HT_2D_bins_lep;
		std::vector<double> HT1_2D_bins_lep;
		std::vector<double> HT2_2D_bins_lep;
		std::vector<double> HT3_2D_bins_lep;
		// HT/MET Trigger turnons
		std::vector<double> HT_2D_bins;
		std::vector<double> HT1_2D_bins;
		std::vector<double> HT2_2D_bins;
		std::vector<double> HT3_2D_bins;
		std::vector<double> MET_2D_bins;
		// unrolled bin mergin
		std::vector<int> merged_razor_bins;
		std::vector<int> merged_razor_bins_lep;
		std::vector<int> merged_trigger_bins;
		std::vector<int> merged_trigger1_bins;
		std::vector<int> merged_trigger2_bins;
		std::vector<int> merged_trigger3_bins;


		std::vector<double> MRR2_2D_bins_new;
};

class Plotting : public PlottingBase
{
	public:
		Plotting(Variables& var) : 
			PlottingBase(var),
			v(var)
	{}
		~Plotting() {}

		Variables& v;

		void define_additional_histo_settings(const Weighting&, EventSelections&, const unsigned int&, const unsigned int&);

		void define_additional_histos(const Weighting&, const unsigned int&, const unsigned int&);

};


//_______________________________________________________
//      Define Histo options: Filling/Postfixes


PlottingBase::PostfixOptions
PlottingBase::get_pf_opts_(std::vector<std::vector<Sample> > lists, const TString& sample) {
	std::vector<Sample> samples;
	for (auto list : lists) samples.insert(samples.end(), list.begin(), list.end());
	PostfixOptions opt{ (size_t)-1, "", "", "" };
	for (size_t i=0; i<samples.size(); ++i) {
		// Find index of matching directory
		for (size_t j=0; j<samples[i].dirs.size(); ++j)
			if (samples[i].dirs[j] == sample.Data()) opt.index = i;
		opt.postfixes += samples[i].postfix;
		opt.legends += samples[i].legend;
		opt.colors += samples[i].color;
		if (i+1!=samples.size()) {
			opt.postfixes +=  ";";
			opt.legends += ";";
			opt.colors += ",";
		}
	}
	return opt;
}

void
PlottingBase::add_unrolled_bins(std::string param_name, std::string axis1_title, std::string axis2_title,
		std::function<double()> var1, std::function<double()> var2,
		std::vector<double> bins1, std::vector<double> bins2,
		std::vector<int> merged_bins = {}, int precision1=0, int precision2=0, bool shrink_merged=false) {
	//std::cout<<param_name<<std::endl;
	std::vector<double> xbins = { 0 };
	std::map<int, std::string> bin1_labels, bin2_labels;
	std::stringstream label1, label2;
	size_t bin = 0, actual_bin = 0, big_bin = 0;
	for (size_t i=0, n=bins1.size(); i<n; ++i) {
		if (i!=0) {
			if (precision1) label1<<std::setprecision(precision1);
			label1<<bins1[i]<<"]";
			bin1_labels[big_bin] = label1.str();
		}
		if (i+1!=n){
			label1.str("");
			if (precision1) label1<<std::setprecision(precision1);
			label1<<"["<<bins1[i]<<", ";
			big_bin = shrink_merged ? actual_bin : bin;
			for (size_t j=0, m=bins2.size(); j<m; ++j) {
				if (j!=0) bin++;
				// Check if this bin is meant to be merged with the next one
				bool merge = false;
				for (auto merged_bin : merged_bins) if (bin==merged_bin) merge = true;
				if (!merge) {
					// Create bin label
					if (j!=0) {
						if (precision2) label2<<std::setprecision(precision2);
						label2<<bins2[j]<<"]";
						bin2_labels[++actual_bin] = label2.str();
						if (!merged_bins.empty()) xbins.push_back(shrink_merged ? actual_bin : bin);
					}
					if (j+1!=m){
						label2.str("");
						if (precision2) label2<<std::setprecision(precision2);
						label2<<"["<<bins2[j]<<", ";
					}
				}
			}
		}
	}
	if (merged_bins.empty()) xbins.push_back(bin);
	//for (auto xbin : xbins)
	//  std::cout<<xbin<<", ";
	//std::cout<<std::endl<<std::endl;
	if (shrink_merged) {
		sh.AddNewUnrolledFillParams(param_name, { .nbin=actual_bin, .bins=xbins, .bin_labels=bin2_labels, .unrolled_bin_labels=bin1_labels, .fill=[bins1,bins2,var1,var2,merged_bins] {
				double bin = -1, v1 = var1(), v2 = var2();
				for (size_t i=0, n=bins1.size(); i+1<n; ++i) if (v1>=bins1[i]&&v1<bins1[i+1])
				for (size_t j=0, m=bins2.size(); j+1<m; ++j) if (v2>=bins2[j]&&v2<bins2[j+1])
				bin = i*(m-1)+j;
				for (auto merged_bin : merged_bins) if (bin>=merged_bin) --bin;
				return bin;
				}, .axis_title=axis2_title, .unrolled_axis_title=axis1_title});
	} else {
		sh.AddNewUnrolledFillParams(param_name, { .nbin=actual_bin, .bins=xbins, .bin_labels=bin2_labels, .unrolled_bin_labels=bin1_labels, .fill=[bins1,bins2,var1,var2] {
				double bin = -1, v1 = var1(), v2 = var2();
				for (size_t i=0, n=bins1.size(); i+1<n; ++i) if (v1>=bins1[i]&&v1<bins1[i+1])
				for (size_t j=0, m=bins2.size(); j+1<m; ++j) if (v2>=bins2[j]&&v2<bins2[j+1])
				bin = i*(m-1)+j;
				return bin;
				}, .axis_title=axis2_title, .unrolled_axis_title=axis1_title});
	}
}

	void
PlottingBase::define_histo_settings(const Weighting& w, EventSelections& evt_sel,
		const unsigned int& syst_nSyst, const unsigned int& syst_index)
{
	const int debug = 0;

	if (debug) std::cout<<"PlottingBase::define_histo_settings: start"<<std::endl;

	sh.SetHistoWeights({ [&w] { return w.weight; } });

	// Keep this to be able to use analysis cuts
	//define_preselections(d);
	//define_selections(d);
	//for (const auto& region : evt_sel.analysis_cuts) w_nm1[region.first].resize(20,1);

	if (debug) std::cout<<"PlottingBase::define_histo_settings: weight, selections ok"<<std::endl;


	// --------------------------------------------------------------------
	//                            Cuts
	// --------------------------------------------------------------------

	// Pass each cut
	typedef EventSelections::Regions Region;
	sh.AddNewCut("P", [&evt_sel] { return evt_sel.pass_all_cuts[static_cast<size_t>(Region::Pre)]; });

	//sh.AddNewCut("S", [&evt_sel] { return evt_sel.pass_all_cuts[static_cast<size_t>(Region::SR_Leptop_0htop, Region::SR_Leptop_1htop)]; });






	if (debug) std::cout<<"PlottingBase::define_histo_settings: cuts ok"<<std::endl;

	//__________________________________
	//            Postfixes
	//__________________________________

	// Postfixes are vector definitions for histograms
	// They attach _<string> after histogram names
	// where <string> is chosen from a vector of strings
	// you need to give a natural number (0,1,2,3 ...) as a vector index
	// for the histogram to choose which histo to fill
	// The index should be size_t
	// In case the value is (size_t)-1 - the histogram won't be filled
	// This can effectively be used to define named cuts
	// The advantage over regular "Cuts" is that the postfix is attached to the histogram name
	// and the text is added to the legend (For this reason I prefer to use this over Cuts)

	// Notation:
	// AddNewPostfix("Name of Postfix", lambda function returning non-negative integer, "postfix 1;2;3; ...", "legend text 1;2;3; ...", "ROOT color 1,2,3, ...")

	// Define postfix - which can split the data to multiple plots
	// Parameter should be the index of the postfix vector
	// return (size_t)-1; --> don't fill histo, can be used to define a cut
	// 1st param: name of the postfix
	// 2nd param: lambda capture of the variable we want to fill
	// 3rd param: list of postixes that are attached to the histogram name, separate by ";"
	// 4th param: list of legend entrys, separate also by ";"
	// 3-4th param: can also use ranges for repetitive numbers: Jet[1to4] = "Jet1;Jet2;Jet3;Jet4", [1to10++2] = "1;3;5;7;9"
	// 5th param: list of TColors for each histogram, separated by ","

	// Sample postfixes for stack plots
	// Determine them from the directory names in which the input files are
	// Map directory names to postfix name, legend entry and color

	// ---------------------- Backgrounds ----------------------

	std::vector<Sample> bkg_ttbars;
	bkg_ttbars.push_back({ .postfix= "TT_powheg_pythia8",        .legend="t#bar{t}+jets", .color=DGreen, .dirs={ 
			// 2016
			"TT_TuneCUETP8M2T4_13TeV-powheg-pythia8",
			"TTTo2L2Nu_TuneCP5_PSweights_13TeV-powheg-pythia8",
			"TTToHadronic_TuneCP5_PSweights_13TeV-powheg-pythia8",
			"TTToSemiLeptonic_TuneCP5_PSweights_13TeV-powheg-pythia8",
			// 2017/2018
			"TTTo2L2Nu_TuneCP5_13TeV-powheg-pythia8",
			"TTToHadronic_TuneCP5_13TeV-powheg-pythia8",
			"TTToSemiLeptonic_TuneCP5_13TeV-powheg-pythia8" } });

	if (debug) std::cout<<"PlottingBase::define_histo_settings: ok2"<<std::endl;
	std::vector<Sample> bkg_nonttbars;
	bkg_nonttbars.push_back({ .postfix="Multijet",   .legend="Multijet",                  .color=FMagen, .dirs={ 
			// 2016
			"QCD_HT1000to1500_TuneCP5_PSWeights_13TeV-madgraph-pythia8",
			"QCD_HT100to200_TuneCP5_PSWeights_13TeV-madgraphMLM-pythia8",
			"QCD_HT1500to2000_TuneCP5_PSWeights_13TeV-madgraphMLM-pythia8",
			"QCD_HT2000toInf_TuneCP5_PSWeights_13TeV-madgraphMLM-pythia8",
			"QCD_HT200to300_TuneCP5_PSWeights_13TeV-madgraphMLM-pythia8",
			"QCD_HT300to500_TuneCP5_PSWeights_13TeV-madgraphMLM-pythia8",
			"QCD_HT500to700_TuneCP5_PSWeights_13TeV-madgraphMLM-pythia8",
			"QCD_HT700to1000_TuneCP5_PSWeights_13TeV-madgraphMLM-pythia8",
			"DYJetsToQQ_HT180_13TeV-madgraphMLM-pythia8",
			"WJetsToQQ_HT180_13TeV-madgraphMLM-pythia8",
			"WWTo4Q_13TeV-powheg",
			"ZJetsToQQ_HT600toInf_13TeV-madgraph",
			"ZZTo4Q_13TeV_amcatnloFXFX_madspin_pythia8",
			// 2017/2018
			"QCD_HT1000to1500_TuneCP5_PSWeights_13TeV-madgraph-pythia8",
			"QCD_HT100to200_TuneCP5_PSWeights_13TeV-madgraph-pythia8",
			"QCD_HT1500to2000_TuneCP5_PSWeights_13TeV-madgraph-pythia8",
			"QCD_HT2000toInf_TuneCP5_PSWeights_13TeV-madgraph-pythia8",
			"QCD_HT200to300_TuneCP5_PSWeights_13TeV-madgraph-pythia8",
			"QCD_HT300to500_TuneCP5_PSWeights_13TeV-madgraph-pythia8",
			"QCD_HT500to700_TuneCP5_PSWeights_13TeV-madgraph-pythia8",
			"QCD_HT700to1000_TuneCP5_PSWeights_13TeV-madgraph-pythia8",
			"DYJetsToQQ_HT180_13TeV_TuneCP5-madgraphMLM-pythia8",
			"WJetsToQQ_HT-200to400_TuneCP5_13TeV-madgraphMLM-pythia8",
			"WJetsToQQ_HT-400to600_TuneCP5_13TeV-madgraphMLM-pythia8",
			"WJetsToQQ_HT-600to800_TuneCP5_13TeV-madgraphMLM-pythia8",
			"WJetsToQQ_HT-800toInf_TuneCP5_13TeV-madgraphMLM-pythia8",
			"ZJetsToQQ_HT-200to400_TuneCP5_13TeV-madgraphMLM-pythia8",
			"ZJetsToQQ_HT-400to600_TuneCP5_13TeV-madgraphMLM-pythia8",
			"ZJetsToQQ_HT-600to800_TuneCP5_13TeV-madgraphMLM-pythia8",
			"ZJetsToQQ_HT-800toInf_TuneCP5_13TeV-madgraphMLM-pythia8",
			"WWTo4Q_4f_TuneCP5_13TeV-amcatnloFXFX-pythia8",
			// 2018
			"QCD_HT1000to1500_TuneCP5_PSWeights_13TeV-madgraphMLM-pythia8",
			"QCD_HT100to200_TuneCP5_PSWeights_13TeV-madgraphMLM-pythia8",
			"QCD_HT1500to2000_TuneCP5_PSWeights_13TeV-madgraphMLM-pythia8",
			"QCD_HT2000toInf_TuneCP5_PSWeights_13TeV-madgraphMLM-pythia8",
			"QCD_HT200to300_TuneCP5_PSWeights_13TeV-madgraphMLM-pythia8",
			"QCD_HT300to500_TuneCP5_PSWeights_13TeV-madgraphMLM-pythia8",
			"QCD_HT500to700_TuneCP5_PSWeights_13TeV-madgraphMLM-pythia8",
			"QCD_HT700to1000_TuneCP5_PSWeights_13TeV-madgraphMLM-pythia8",
			"WJetsToQQ_HT400to600_qc19_3j_TuneCP5_13TeV-madgraphMLM-pythia8",
			"WJetsToQQ_HT600to800_qc19_3j_TuneCP5_13TeV-madgraphMLM-pythia8",
			"WJetsToQQ_HT-800toInf_qc19_3j_TuneCP5_13TeV-madgraphMLM-pythia8",
			"WWTo4Q_NNPDF31_TuneCP5_13TeV-powheg-pythia8"
	} });

	bkg_nonttbars.push_back({ .postfix="WToLNu",     .legend="W+jets",                    .color=Red, .dirs={
			// 2016
			"WJetsToLNu_HT-100To200_TuneCP5_13TeV-madgraphMLM-pythia8",
			"WJetsToLNu_HT-1200To2500_TuneCP5_13TeV-madgraphMLM-pythia8",
			"WJetsToLNu_HT-200To400_TuneCP5_13TeV-madgraphMLM-pythia8",
			"WJetsToLNu_HT-2500ToInf_TuneCP5_13TeV-madgraphMLM-pythia8",
			"WJetsToLNu_HT-400To600_TuneCP5_13TeV-madgraphMLM-pythia8",
			"WJetsToLNu_HT-600To800_TuneCP5_13TeV-madgraphMLM-pythia8",
			"WJetsToLNu_HT-70To100_TuneCP5_13TeV-madgraphMLM-pythia8",
			"WJetsToLNu_HT-800To1200_TuneCP5_13TeV-madgraphMLM-pythia8",
			// 2017/2018
			"WJetsToLNu_HT-100To200_TuneCP5_13TeV-madgraphMLM-pythia8",
			"WJetsToLNu_HT-200To400_TuneCP5_13TeV-madgraphMLM-pythia8",
			"WJetsToLNu_HT-400To600_TuneCP5_13TeV-madgraphMLM-pythia8",
			"WJetsToLNu_HT-600To800_TuneCP5_13TeV-madgraphMLM-pythia8",
			"WJetsToLNu_HT-800To1200_TuneCP5_13TeV-madgraphMLM-pythia8",
			"WJetsToLNu_HT-1200To2500_TuneCP5_13TeV-madgraphMLM-pythia8",
			"WJetsToLNu_HT-2500ToInf_TuneCP5_13TeV-madgraphMLM-pythia8"
			} });
	bkg_nonttbars.push_back({ .postfix="ZToNuNu",    .legend="Z#rightarrow#nu#nu", .color=Cyan, .dirs={
			// 2016/2017/2018
			"ZJetsToNuNu_HT-100To200_TuneCP5_13TeV-madgraphMLM-pythia8",
			"ZJetsToNuNu_HT-200To400_TuneCP5_13TeV-madgraphMLM-pythia8",
			"ZJetsToNuNu_HT-400To600_TuneCP5_13TeV-madgraphMLM-pythia8",
			"ZJetsToNuNu_HT-600To800_TuneCP5_13TeV-madgraphMLM-pythia8",
			"ZJetsToNuNu_HT-800To1200_TuneCP5_13TeV-madgraphMLM-pythia8",
			"ZJetsToNuNu_HT-1200To2500_TuneCP5_13TeV-madgraphMLM-pythia8",
			"ZJetsToNuNu_HT-2500ToInf_TuneCP5_13TeV-madgraphMLM-pythia8" } });
	bkg_nonttbars.push_back({ .postfix="Higgs",    .legend="H+jets", .color=Brown, .dirs={
			// 2016/2017/2018
			"WminusH_HToBB_WToLNu_M-125_TuneCP5_13TeV_powheg_pythia8",
			"WminusH_HToBB_WToQQ_M-125_TuneCP5_13TeV_powheg_pythia8",
			"WplusH_HToBB_WToLNu_M-125_TuneCP5_13TeV_powheg_pythia8",
			"WplusH_HToBB_WToQQ_M-125_TuneCP5_13TeV_powheg_pythia8",
			"ZH_HToBB_ZToBB_M-125_TuneCP5_13TeV-powheg-pythia8",
			"ZH_HToBB_ZToLL_M-125_TuneCP5_13TeV_powheg_pythia8",
			"ZH_HToBB_ZToNuNu_M-125_TuneCP5_13TeV_powheg_pythia8",
			"ZH_HToBB_ZToQQ_M-125_TuneCP5_13TeV_powheg_pythia8",
			"ggZH_HToBB_ZToBB_M-125_TuneCP5_13TeV-powheg-pythia8",
			"ggZH_HToBB_ZToLL_M-125_TuneCP5_13TeV_powheg_pythia8",
			"ggZH_HToBB_ZToNuNu_M-125_TuneCP5_13TeV_powheg_pythia8",
			"ggZH_HToBB_ZToQQ_M-125_TuneCP5_13TeV_powheg_pythia8",
			"ttHToNonbb_M125_TuneCP5_13TeV-powheg-pythia8",
			"ttHTobb_M125_TuneCP5_13TeV-powheg-pythia8",
			"ttHJetToNonbb_M125_TuneCP5_13TeV_amcatnloFXFX_madspin_pythia8",
			"ttHJetTobb_M125_TuneCP5_13TeV_amcatnloFXFX_madspin_pythia8",
			// 2016
			"TTHH_TuneCP5_13TeV-amcatnlo-pythia8",
			//"VBFHToBB_M125_13TeV_amcatnlo_pythia8",
			"VBFHToBB_M-125_13TeV_powheg_pythia8_weightfix",
			"VBFHToWWTo2L2Nu_M125_13TeV_powheg_JHUgenv628_pythia8",
			"VBF_HToInvisible_M125_13TeV_powheg_pythia8",
			"TTWH_TuneCP5_13TeV-madgraph-pythia8",
			"TTZH_TuneCP5_13TeV-madgraph-pythia8",
			// 2017/2018
			"TTHH_TuneCP5_13TeV-madgraph-pythia8",
			"VBFHToBB_M-125_TuneCP5_13TeV-powheg-pythia8",
			"VBFHToWWTo2L2Nu_M-125_TuneCP5_13TeV-powheg-jhugen727-pythia8",
			// 2018
			"ZH_HToBB_ZToNuNu_M125_13TeV_powheg_pythia8" } });
	bkg_nonttbars.push_back({ .postfix="Multiboson", .legend="VV(V)+t#bar{t}X",                  .color=DGray, .dirs={
			// 2016
			"WWTo1L1Nu2Q_4f_TuneCP5_13TeV-amcatnloFXFX-pythia8",
			"WWTo2L2Nu_TuneCP5_13TeV-powheg-pythia8",
			"WWTo4Q_4f_TuneCP5_13TeV-amcatnloFXFX-pythia8",
			"WWTo1L1Nu2Q_4f_TuneCP5_13TeV-amcatnloFXFX-pythia8",
			"WZTo1L3Nu_4f_TuneCP5_13TeV-amcatnloFXFX-pythia8",
			"WZTo2Q2Nu_13TeV_amcatnloFXFX_madspin_pythia8",
			"WZTo3LNu_TuneCP5_13TeV-amcatnloFXFX-pythia8",
			"ZZTo2Nu2Q_5f_TuneCP5_13TeV-amcatnloFXFX-pythia8",
			"ZZTo4Q_13TeV_amcatnloFXFX_madspin_pythia8",
			"ZZTo4L_TuneCP5_13TeV_powheg_pythia8",
			"WWW_4F_TuneCUETP8M1_13TeV-amcatnlo-pythia8",
			"WWZ_TuneCUETP8M1_13TeV-amcatnlo-pythia8",
			"WZZ_TuneCUETP8M1_13TeV-amcatnlo-pythia8",
			"ZZZ_TuneCUETP8M1_13TeV-amcatnlo-pythia8",
			"TTWJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8",
			"TTWJetsToQQ_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8",
			"TTZToLLNuNu_M-10_TuneCUETP8M1_13TeV-amcatnlo-pythia8",
			"TTZToQQ_TuneCUETP8M1_13TeV-amcatnlo-pythia8",
			"TTGJets_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8",
			"TTZZ_TuneCUETP8M2T4_13TeV-madgraph-pythia8",
			"TTTT_TuneCUETP8M2T4_13TeV-amcatnlo-pythia8",
			"TTTW_TuneCUETP8M2T4_13TeV-madgraph-pythia8",
			"TTWW_TuneCUETP8M2T4_13TeV-madgraph-pythia8",
			"TTWZ_TuneCUETP8M2T4_13TeV-madgraph-pythia8",
			// 2017
			"WWTo1L1Nu2Q_13TeV_amcatnloFXFX_madspin_pythia8",
			"WWTo2L2Nu_NNPDF31_TuneCP5_13TeV-powheg-pythia8",
			"WWToLNuQQ_NNPDF31_TuneCP5_13TeV-powheg-pythia8",
			"WZTo1L1Nu2Q_13TeV_amcatnloFXFX_madspin_pythia8",
			"WZTo1L3Nu_13TeV_amcatnloFXFX_madspin_pythia8_v2",
			"WZTo2L2Q_13TeV_amcatnloFXFX_madspin_pythia8",
			"WZTo3LNu_TuneCP5_13TeV-amcatnloFXFX-pythia8",
			"ZZTo2L2Nu_13TeV_powheg_pythia8",
			"ZZTo2L2Q_13TeV_amcatnloFXFX_madspin_pythia8",
			"ZZTo2Q2Nu_TuneCP5_13TeV_amcatnloFXFX_madspin_pythia8",
			"ZZTo4L_13TeV_powheg_pythia8",
			"WWW_4F_TuneCP5_13TeV-amcatnlo-pythia8",
			"WWZ_4F_TuneCP5_13TeV-amcatnlo-pythia8",
			"WZZ_TuneCP5_13TeV-amcatnlo-pythia8",
			"ZZZ_TuneCP5_13TeV-amcatnlo-pythia8",
			"TTWJetsToLNu_TuneCP5_13TeV-amcatnloFXFX-madspin-pythia8",
			"TTWJetsToQQ_TuneCP5_13TeV-amcatnloFXFX-madspin-pythia8",
			"TTZToLLNuNu_M-10_TuneCP5_13TeV-amcatnlo-pythia8",
			"TTZToQQ_TuneCP5_13TeV-amcatnlo-pythia8",
			"TTTT_TuneCP5_13TeV-amcatnlo-pythia8",
			// 2018
			"WWZ_TuneCP5_13TeV-amcatnlo-pythia8",
			"WZTo1L3Nu_13TeV_amcatnloFXFX_madspin_pythia8",
			"ZZTo2L2Nu_TuneCP5_13TeV_powheg_pythia8",
			"ZZTo4L_13TeV_powheg_pythia8_TuneCP5"
	} });
	bkg_nonttbars.push_back({ .postfix="Top",        .legend="Single t",                               .color=Orange,   .dirs={
			// 2016
			//"ST_s-channel_4f_InclusiveDecays_13TeV-amcatnlo-pythia8",
			"ST_s-channel_4f_leptonDecays_13TeV-amcatnlo-pythia8",
			"ST_t-channel_antitop_4f_inclusiveDecays_13TeV-powhegV2-madspin-pythia8_TuneCUETP8M1",
			"ST_t-channel_top_4f_inclusiveDecays_13TeV-powhegV2-madspin-pythia8_TuneCUETP8M1",
			"ST_tW_antitop_5f_NoFullyHadronicDecays_13TeV-powheg_TuneCUETP8M1",
			"ST_tW_top_5f_NoFullyHadronicDecays_13TeV-powheg_TuneCUETP8M1",
			// 2017
			"ST_s-channel_4f_leptonDecays_TuneCP5_13TeV-amcatnlo-pythia8",
			"ST_t-channel_antitop_4f_inclusiveDecays_TuneCP5_13TeV-powhegV2-madspin-pythia8",
			"ST_t-channel_top_4f_inclusiveDecays_TuneCP5_13TeV-powhegV2-madspin-pythia8",
			"ST_tW_antitop_5f_NoFullyHadronicDecays_TuneCP5_13TeV-powheg-pythia8",
			"ST_tW_top_5f_NoFullyHadronicDecays_TuneCP5_13TeV-powheg-pythia8",
			// 2018
			"ST_s-channel_4f_leptonDecays_TuneCP5_13TeV-madgraph-pythia8",
			"ST_t-channel_antitop_4f_InclusiveDecays_TuneCP5_13TeV-powheg-madspin-pythia8",
			"ST_t-channel_top_4f_InclusiveDecays_TuneCP5_13TeV-powheg-madspin-pythia8"
			} });
	//bkg_nonttbars.push_back({ .postfix="DYToLL",     .legend="Drell-Yan",                              .color=DBrown, .dirs={ 
	bkg_nonttbars.push_back({ .postfix="DYToLL",     .legend="Z#rightarrowll",                         .color=FBlue,  .dirs={
			// 2016
			"DYJetsToLL_M-5to50_HT-70to100_TuneCUETP8M1_13TeV-madgraphMLM-pythia8",
			"DYJetsToLL_M-5to50_HT-100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8",
			"DYJetsToLL_M-5to50_HT-200to400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8",
			"DYJetsToLL_M-5to50_HT-400to600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8",
			"DYJetsToLL_M-5to50_HT-600toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8",
			"DYJetsToLL_M-50_HT-70to100_TuneCUETP8M1_13TeV-madgraphMLM-pythia8",
			"DYJetsToLL_M-50_HT-100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8",
			"DYJetsToLL_M-50_HT-200to400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8",
			"DYJetsToLL_M-50_HT-400to600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8",
			"DYJetsToLL_M-50_HT-600to800_TuneCUETP8M1_13TeV-madgraphMLM-pythia8",
			"DYJetsToLL_M-50_HT-800to1200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8",
			"DYJetsToLL_M-50_HT-1200to2500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8",
			"DYJetsToLL_M-50_HT-2500toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8",
			// 2017
			"DYJetsToLL_M-4to50_HT-70to100_TuneCP5_13TeV-madgraphMLM-pythia8",
			"DYJetsToLL_M-4to50_HT-100to200_TuneCP5_13TeV-madgraphMLM-pythia8",
			"DYJetsToLL_M-4to50_HT-200to400_TuneCP5_13TeV-madgraphMLM-pythia8",
			"DYJetsToLL_M-4to50_HT-400to600_TuneCP5_13TeV-madgraphMLM-pythia8",
			"DYJetsToLL_M-4to50_HT-600toInf_TuneCP5_13TeV-madgraphMLM-pythia8",
			"DYJetsToLL_M-50_HT-70to100_TuneCP5_13TeV-madgraphMLM-pythia8",
			"DYJetsToLL_M-50_HT-100to200_TuneCP5_13TeV-madgraphMLM-pythia8",
			"DYJetsToLL_M-50_HT-200to400_TuneCP5_13TeV-madgraphMLM-pythia8",
			"DYJetsToLL_M-50_HT-2500toInf_TuneCP5_13TeV-madgraphMLM-pythia8",
			"DYJetsToLL_M-50_HT-400to600_TuneCP5_13TeV-madgraphMLM-pythia8",
			"DYJetsToLL_M-50_HT-600to800_TuneCP5_13TeV-madgraphMLM-pythia8",
			"DYJetsToLL_M-50_HT-800to1200_TuneCP5_13TeV-madgraphMLM-pythia8",
			"DYJetsToLL_M-50_HT-1200to2500_TuneCP5_13TeV-madgraphMLM-pythia8",
			// 2018
			"DYJetsToLL_M-4to50_HT-70to100_TuneCP5_PSweights_13TeV-madgraphMLM-pythia8",
			"DYJetsToLL_M-4to50_HT-100to200_TuneCP5_PSweights_13TeV-madgraphMLM-pythia8",
			"DYJetsToLL_M-4to50_HT-200to400_TuneCP5_PSweights_13TeV-madgraphMLM-pythia8",
			"DYJetsToLL_M-4to50_HT-400to600_TuneCP5_PSweights_13TeV-madgraphMLM-pythia8",
			"DYJetsToLL_M-4to50_HT-600toInf_TuneCP5_PSWeights_13TeV-madgraphMLM-pythia8",
			"DYJetsToLL_M-50_HT-70to100_TuneCP5_PSweights_13TeV-madgraphMLM-pythia8",
			"DYJetsToLL_M-50_HT-100to200_TuneCP5_PSweights_13TeV-madgraphMLM-pythia8",
			"DYJetsToLL_M-50_HT-200to400_TuneCP5_PSweights_13TeV-madgraphMLM-pythia8",
			"DYJetsToLL_M-50_HT-400to600_TuneCP5_PSweights_13TeV-madgraphMLM-pythia8",
			"DYJetsToLL_M-50_HT-600to800_TuneCP5_PSweights_13TeV-madgraphMLM-pythia8",
			"DYJetsToLL_M-50_HT-1200to2500_TuneCP5_PSweights_13TeV-madgraphMLM-pythia8",
			"DYJetsToLL_M-50_HT-2500toInf_TuneCP5_PSweights_13TeV-madgraphMLM-pythia8",
			"DYJetsToLL_M-50_HT-800to1200_TuneCP5_PSweights_13TeV-madgraphMLM-pythia8"
	} });
	//bkg_nonttbars.push_back({ .postfix="GJets",      .legend="#gamma+jets",                            .color=DBrown,.dirs={ 
	bkg_nonttbars.push_back({ .postfix="GJets",      .legend="#gamma+jets",                            .color=kOrange, .dirs={
			// 2016
			"GJets_HT-40To100_TuneCUETP8M1_13TeV-madgraphMLM-pythia8",
			"GJets_HT-100To200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8",
			"GJets_HT-200To400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8",
			"GJets_HT-400To600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8",
			"GJets_HT-600ToInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8",
			// 2017/2018
			"GJets_HT-40To100_TuneCP5_13TeV-madgraphMLM-pythia8",
			"GJets_HT-100To200_TuneCP5_13TeV-madgraphMLM-pythia8",
			"GJets_HT-200To400_TuneCP5_13TeV-madgraphMLM-pythia8",
			"GJets_HT-400To600_TuneCP5_13TeV-madgraphMLM-pythia8",
			"GJets_HT-600ToInf_TuneCP5_13TeV-madgraphMLM-pythia8"
			} });

	std::vector<Sample> bkg_all, bkg_selected, ttbar_selected, multijet, znunu, gjets;
	bkg_all.insert(bkg_all.end(), bkg_ttbars.begin(), bkg_ttbars.end());
	bkg_all.insert(bkg_all.end(), bkg_nonttbars.begin(), bkg_nonttbars.end());
	ttbar_selected.push_back(bkg_ttbars[0]); // powheg
	bkg_selected  .push_back(bkg_ttbars[0]); // powheg
	bkg_selected.insert(bkg_selected.end(), bkg_nonttbars.begin(), bkg_nonttbars.end());
	multijet.push_back(bkg_nonttbars[0]);
	znunu   .push_back(bkg_nonttbars[2]);
	gjets   .push_back(bkg_nonttbars[6]);

	std::vector<std::string> background_dirs;
	for (auto bkg : bkg_selected) for (auto dir : bkg.dirs) background_dirs.push_back(dir);
	std::vector<Sample> background, mc;
	background.push_back({ .postfix="Background", .legend="Background", .color=Black, .dirs=background_dirs });
	mc        .push_back({ .postfix="MC",         .legend="MC",         .color=Black, .dirs=background_dirs });
	static const PostfixOptions background_opt = get_pf_opts_({background}, v.sample);

	// ------------------------- Data --------------------------

	if (debug) std::cout<<"PlottingBase::define_histo_settings: ok3"<<std::endl;
	std::vector<Sample> data_all, data_selected, single_ele, single_mu, single_pho, jetht, met;
	data_all.push_back({ .postfix="Data",      .legend="Data",             .color=Black, .dirs={
			// Signal regions
			"JetHT_Run2016B",
			"JetHT_Run2016C",
			"JetHT_Run2016D",
			"JetHT_Run2016E",
			"JetHT_Run2016F",
			"JetHT_Run2016G",
			"JetHT_Run2016H",
			"JetHT_Run2017B",
			"JetHT_Run2017C",
			"JetHT_Run2017D",
			"JetHT_Run2017E",
			"JetHT_Run2017F",
			"JetHT_Run2018A",
			"JetHT_Run2018B",
			"JetHT_Run2018C",
			"JetHT_Run2018D",
			"MET_Run2016B",
			"MET_Run2016C",
			"MET_Run2016D",
			"MET_Run2016E",
			"MET_Run2016F",
			"MET_Run2016G",
			"MET_Run2016H",
			"MET_Run2017B",
			"MET_Run2017C",
			"MET_Run2017D",
			"MET_Run2017E",
			"MET_Run2017F",
			"MET_Run2018A",
			"MET_Run2018B",
			"MET_Run2018C",
			"MET_Run2018D",
			"HTMHT_Run2016B",
			"HTMHT_Run2016C",
			"HTMHT_Run2016D",
			"HTMHT_Run2016E",
			"HTMHT_Run2016F",
			"HTMHT_Run2016G",
			"HTMHT_Run2016H",
			// Control regions (and maybe leptonic signal)
			"SingleElectron_Run2016B",
			"SingleElectron_Run2016C",
			"SingleElectron_Run2016D",
			"SingleElectron_Run2016E",
			"SingleElectron_Run2016F",
			"SingleElectron_Run2016G",
			"SingleElectron_Run2016H",
			"SingleElectron_Run2017B",
			"SingleElectron_Run2017C",
			"SingleElectron_Run2017D",
			"SingleElectron_Run2017E",
			"SingleElectron_Run2017F",
			"EGamma_Run2018A",
			"EGamma_Run2018B",
			"EGamma_Run2018C",
			"EGamma_Run2018D",
			"SingleMuon_Run2016B",
			"SingleMuon_Run2016C",
			"SingleMuon_Run2016D",
			"SingleMuon_Run2016E",
			"SingleMuon_Run2016F",
			"SingleMuon_Run2016G",
			"SingleMuon_Run2016H",
			"SingleMuon_Run2017B",
			"SingleMuon_Run2017C",
			"SingleMuon_Run2017D",
			"SingleMuon_Run2017E",
			"SingleMuon_Run2017F",
			"SingleMuon_Run2018A",
			"SingleMuon_Run2018B",
			"SingleMuon_Run2018C",
			"SingleMuon_Run2018D"
				"SinglePhoton_Run2016B",
			"SinglePhoton_Run2016C",
			"SinglePhoton_Run2016D",
			"SinglePhoton_Run2016E",
			"SinglePhoton_Run2016F",
			"SinglePhoton_Run2016G",
			"SinglePhoton_Run2016H",
			"SinglePhoton_Run2017B",
			"SinglePhoton_Run2017C",
			"SinglePhoton_Run2017D",
			"SinglePhoton_Run2017E",
			"SinglePhoton_Run2017F"
	} });
	data_all.push_back({ .postfix="SingleEle", .legend="Data", .color=Black, .dirs={
			"SingleElectron_Run2016B",
			"SingleElectron_Run2016C",
			"SingleElectron_Run2016D",
			"SingleElectron_Run2016E",
			"SingleElectron_Run2016F",
			"SingleElectron_Run2016G",
			"SingleElectron_Run2016H",
			"SingleElectron_Run2017B",
			"SingleElectron_Run2017C",
			"SingleElectron_Run2017D",
			"SingleElectron_Run2017E",
			"SingleElectron_Run2017F",
			"EGamma_Run2018A",
			"EGamma_Run2018B",
			"EGamma_Run2018C",
			"EGamma_Run2018D"
			} });
	data_all.push_back({ .postfix="SingleMu",  .legend="Data",  .color=Black, .dirs={
			"SingleMuon_Run2016B",
			"SingleMuon_Run2016C",
			"SingleMuon_Run2016D",
			"SingleMuon_Run2016E",
			"SingleMuon_Run2016F",
			"SingleMuon_Run2016G",
			"SingleMuon_Run2016H",
			"SingleMuon_Run2017B",
			"SingleMuon_Run2017C",
			"SingleMuon_Run2017D",
			"SingleMuon_Run2017E",
			"SingleMuon_Run2017F",
			"SingleMuon_Run2018A",
			"SingleMuon_Run2018B",
			"SingleMuon_Run2018C",
			"SingleMuon_Run2018D"
			} });
	data_all.push_back({ .postfix="SinglePho",  .legend="Data",  .color=Black, .dirs={
			"SinglePhoton_Run2016B",
			"SinglePhoton_Run2016C",
			"SinglePhoton_Run2016D",
			"SinglePhoton_Run2016E",
			"SinglePhoton_Run2016F",
			"SinglePhoton_Run2016G",
			"SinglePhoton_Run2016H",
			"SinglePhoton_Run2017B",
			"SinglePhoton_Run2017C",
			"SinglePhoton_Run2017D",
			"SinglePhoton_Run2017E",
			"SinglePhoton_Run2017F"
			} });
	data_all.push_back({ .postfix="JetHT",       .legend="Data",     .color=Black, .dirs={
			"JetHT_Run2016B",
			"JetHT_Run2016C",
			"JetHT_Run2016D",
			"JetHT_Run2016E",
			"JetHT_Run2016F",
			"JetHT_Run2016G",
			"JetHT_Run2016H",
			"JetHT_Run2017B",
			"JetHT_Run2017C",
			"JetHT_Run2017D",
			"JetHT_Run2017E",
			"JetHT_Run2017F",
			"JetHT_Run2018A",
			"JetHT_Run2018B",
			"JetHT_Run2018C",
			"JetHT_Run2018D"
			} });
	data_all.push_back({ .postfix="MET",       .legend="Data",       .color=Black, .dirs={
			"MET_Run2016B",
			"MET_Run2016C",
			"MET_Run2016D",
			"MET_Run2016E",
			"MET_Run2016F",
			"MET_Run2016G",
			"MET_Run2016H",
			"MET_Run2017B",
			"MET_Run2017C",
			"MET_Run2017D",
			"MET_Run2017E",
			"MET_Run2017F",
			"MET_Run2018A",
			"MET_Run2018B",
			"MET_Run2018C",
			"MET_Run2018D"
			} });
	data_all.push_back({ .postfix="HTMHT",     .legend="Data",     .color=Black, .dirs={
			"HTMHT_Run2016B",
			"HTMHT_Run2016C",
			"HTMHT_Run2016D",
			"HTMHT_Run2016E",
			"HTMHT_Run2016F",
			"HTMHT_Run2016G",
			"HTMHT_Run2016H",
			"HTMHT_Run2017B",
			"HTMHT_Run2017C",
			"HTMHT_Run2017D",
			"HTMHT_Run2017E",
			"HTMHT_Run2017F",
			"HTMHT_Run2018A",
			"HTMHT_Run2018B",
			"HTMHT_Run2018C",
			"HTMHT_Run2018D"
			} });
	data_selected.push_back(data_all[0]);
	single_ele.push_back(data_all[1]);
	single_mu.push_back(data_all[2]);
	single_pho.push_back(data_all[3]);
	jetht.push_back(data_all[4]);
	met.push_back(data_all[5]);

	// Individual Cuts implemented as Postfixes
	sh.AddNewPostfix("Blind",      [this] { 
			if (v.isData) return (size_t)-1;
			return (size_t)0;
			}, "BlindData", "", Black);

	// ------------------------ Signals ------------------------

	if (debug) std::cout<<"PlottingBase::define_histo_settings: ok4"<<std::endl;
	std::vector<Sample> signal_all, signal_selected, signal_fastsim, signal_gluino, signal_squark, signal_ewk, signal_top, signal_V, signal_H, signal_RPV;
	std::vector<Sample> T5ttcc, TChiWW, TChiWZ, TChiWH, TChiHH, TChiZH, TChiZZ, T6ttZH, R5ttbl, R2bbqqlv, T5bbbbZH, T5qqqqWH;

	signal_all.push_back({ .postfix="T5bbbbZH",           .legend="T5bbbbZH",        .color=DCyan,     .dirs={
			"SMS-T5bbbbZH_TuneCP5_13TeV-madgraphMLM-pythia8" } });
	signal_all.push_back({ .postfix="T5qqqqWH",       .legend="T5qqqqWH",      .color=DMagen,  .dirs={ 
			"SMS-T5qqqqWH_TuneCP5_13TeV-madgraphMLM-pythia8" } });
	signal_all.push_back({ .postfix="T5ttcc",         .legend="T5ttcc",      .color=Red,      .dirs={ 
			"SMS-T5ttcc_TuneCP5_13TeV-madgraphMLM-pythia8" } });
	signal_all.push_back({ .postfix="T6ttZH",         .legend="T6ttZH",        .color=Blue,    .dirs={ 
			"SMS-T6ttZH_TuneCP5_13TeV-madgraphMLM-pythia8"			} });

	signal_all.push_back({ .postfix="TChiWW",         .legend="TChiWW",      .color=DGreen,  .dirs={ "SMS-TChiWWpm-mNLSP200To1500_mLSP0To600_TuneCP5_13TeV-madgraphMLM-pythia8" } });
	signal_all.push_back({ .postfix="TChiWZ",         .legend="TChiWZ",        .color=DMagen,   .dirs={
			"SMS-TChiWZ-mNLSP200To1500_mLSP0To600_TuneCP5_13TeV-madgraphMLM-pythia8"} });
	signal_all.push_back({ .postfix="TChiWH",         .legend="TChiWH",        .color=DCyan,   .dirs={ 
			"SMS-TChiWH-mNLSP200To1500_mLSP0To600_TuneCP5_13TeV-madgraphMLM-pythia8"			} });
	signal_all.push_back({ .postfix="TChiHH",         .legend="TChiHH",        .color=Blue,    .dirs={ 
			"SMS-TChiHH-mNLSP200To1500_mLSP0To600_TuneCP5_13TeV-madgraphMLM-pythia8"  		} });
	signal_all.push_back({ .postfix="TChiZH",         .legend="TChiZH",      .color=Orange,    .dirs={ "SMS-TChiZH-mNLSP200To1500_mLSP0To600_TuneCP5_13TeV-madgraphMLM-pythia8" } });
	signal_all.push_back({ .postfix="TChiZZ",         .legend="TChiZZ",      .color=DBrown,    .dirs={ 
			"SMS-TChiZZ-mNLSP200To1500_mLSP0To600_TuneCP5_13TeV-madgraphMLM-pythia8" } });

	signal_all.push_back({ .postfix="R5ttbl",         .legend="R5ttbl",        .color=DMagen,    .dirs={ 
			"SMS-R5tttbl" //Fix
			} });
	signal_all.push_back({ .postfix="R2bbqqlv",         .legend="R2bbqqlv",        .color=Blue,    .dirs={ 
			"SMS-R5tttbl" //Fix
			} });

	signal_selected.push_back(signal_all[2]);
	for (int i=0; i<12; ++i) signal_fastsim .push_back(signal_all[i]);
	for (int i=0; i<3; ++i) signal_gluino  .push_back(signal_all[i]);
	for (int i=3; i<4; ++i) signal_squark  .push_back(signal_all[i]);
	for (int i=4; i<10; ++i) signal_ewk     .push_back(signal_all[i]);
	for (int i=2; i<4; ++i) signal_top     .push_back(signal_all[i]);
	for (int i=0; i<2; ++i) signal_V       .push_back(signal_all[i]);
	for (int i=3; i<10; ++i) signal_V       .push_back(signal_all[i]);
	for (int i=0; i<2; ++i) signal_H       .push_back(signal_all[i]);
	for (int i=3; i<4; ++i) signal_H       .push_back(signal_all[i]);
	for (int i=7; i<10; ++i) signal_H       .push_back(signal_all[i]);
	for (int i=11; i<12; ++i) signal_RPV       .push_back(signal_all[i]);
	T5bbbbZH.push_back(signal_all[0]);
	T5qqqqWH.push_back(signal_all[1]);
	T5ttcc  .push_back(signal_all[2]);
	T6ttZH  .push_back(signal_all[3]);
	TChiWW  .push_back(signal_all[4]);
	TChiWZ  .push_back(signal_all[5]);
	TChiWH  .push_back(signal_all[6]);
	TChiHH  .push_back(signal_all[7]);
	TChiZH  .push_back(signal_all[8]);
	TChiZZ  .push_back(signal_all[9]);
	R5ttbl  .push_back(signal_all[10]);
	R2bbqqlv.push_back(signal_all[11]);


	// ---------------------- Benchmarks -----------------------

	std::string bm_glu, bm_glu_lsp, bm_squ, bm_squ_lsp, bm_squ_neu2, bm_chg, bm_chg_lsp;
	std::stringstream ss; 
	ss.str(""); ss<<BM_GLU;      bm_glu      = ss.str();
	ss.str(""); ss<<BM_GLU_NEU;  bm_glu_lsp  = ss.str();
	ss.str(""); ss<<BM_SQU;      bm_squ      = ss.str();
	ss.str(""); ss<<BM_SQU_NEU;  bm_squ_lsp  = ss.str();
	ss.str(""); ss<<BM_SQU_NEU2; bm_squ_neu2 = ss.str();
	ss.str(""); ss<<BM_EWK;      bm_chg      = ss.str();
	ss.str(""); ss<<BM_EWK_NEU;  bm_chg_lsp  = ss.str();

	static const PostfixOptions plot_samples_opt=get_pf_opts_({data_selected, signal_fastsim, bkg_selected}, v.sample);
	sh.AddNewPostfix("StackPlotSignal", [this] { 
			if (plot_samples_opt.index>=0&&plot_samples_opt.index<2) {
				if (v.susy_mass[0] != 2000 || v.susy_mass[1] != 200) return (size_t)-1; // T5qqqqWH, T5bbbbZH
			} else if (plot_samples_opt.index>=2&&plot_samples_opt.index<3) {
				if (v.susy_mass[0] != BM_GLU  || v.susy_mass[1] != BM_GLU_NEU) return (size_t)-1; // T5ttcc
			} else if (plot_samples_opt.index>=3 && plot_samples_opt.index<4) {
				if (v.susy_mass[0] != BM_SQU || v.susy_mass[1] != BM_SQU_NEU) return (size_t)-1; // T6ttZH
			} else if (plot_samples_opt.index>=4 && plot_samples_opt.index<10) {
				if (v.susy_mass[0] != BM_EWK  || v.susy_mass[1] != BM_EWK_NEU) return (size_t)-1; // TChi
			} else if (plot_samples_opt.index==10) {
				if (v.susy_mass[0] != 1800  || v.susy_mass[1] != 1000) return (size_t)-1; // RPV
			} else if (plot_samples_opt.index==11) {
				if (v.susy_mass[0] != 1400  || v.susy_mass[1] != 1000) return (size_t)-1; // RPV
			}
			return plot_samples_opt.index; 
			}, plot_samples_opt.postfixes, plot_samples_opt.legends, plot_samples_opt.colors);

	static const PostfixOptions top_plot_samples_opt=get_pf_opts_({data_selected, signal_top, bkg_selected}, v.sample);
	sh.AddNewPostfix("StackPlotTopSignal", [this] { 
			if (top_plot_samples_opt.index>=2 && top_plot_samples_opt.index<3) {
				if (v.susy_mass[0] != BM_GLU  || v.susy_mass[1] != BM_GLU_NEU) return (size_t)-1; // T5ttcc
			} else if (top_plot_samples_opt.index>=3 && top_plot_samples_opt.index<4) {
				if (v.susy_mass[0] != BM_SQU || v.susy_mass[1] != BM_SQU_NEU) return (size_t)-1; // T6ttZH
			}
			return top_plot_samples_opt.index; 
			}, top_plot_samples_opt.postfixes, top_plot_samples_opt.legends, top_plot_samples_opt.colors);

	static const PostfixOptions V_plot_samples_opt=get_pf_opts_({data_selected, signal_V, bkg_selected}, v.sample);
	sh.AddNewPostfix("StackPlotVSignal", [this] { 
			if (V_plot_samples_opt.index>=0 && V_plot_samples_opt.index<2) {
				if (v.susy_mass[0] != 2000 || v.susy_mass[1] != 200) return (size_t)-1; // T5qqqqWH, T5bbbbZH
			} else if (V_plot_samples_opt.index>=3 && V_plot_samples_opt.index<4) {
			if (v.susy_mass[0] != BM_SQU || v.susy_mass[1] != BM_SQU_NEU) return (size_t)-1; // 6ttZH
			} else if (V_plot_samples_opt.index>=4 && V_plot_samples_opt.index<10) {
			if (v.susy_mass[0] != BM_EWK  || v.susy_mass[1] != BM_EWK_NEU) return (size_t)-1; // TChi
			}
			return V_plot_samples_opt.index; 
			}, V_plot_samples_opt.postfixes, V_plot_samples_opt.legends, V_plot_samples_opt.colors);

	static const PostfixOptions H_plot_samples_opt=get_pf_opts_({data_selected, signal_H, bkg_selected}, v.sample);
	sh.AddNewPostfix("StackPlotHSignal", [this] { 
			if (H_plot_samples_opt.index>=0 && H_plot_samples_opt.index<2) {
				if (v.susy_mass[0] != 2000 || v.susy_mass[1] != 200) return (size_t)-1; // T5qqqqWH, T5bbbbZH
			} else if (H_plot_samples_opt.index>=3 && H_plot_samples_opt.index<4) {
				if (v.susy_mass[0] != 1200 || v.susy_mass[1] != 200) return (size_t)-1; // T6ttZH
			} else if (H_plot_samples_opt.index>=7 && H_plot_samples_opt.index<10) {
			if (v.susy_mass[0] != BM_EWK  || v.susy_mass[1] != BM_EWK_NEU) return (size_t)-1; // TChi
			}
			return H_plot_samples_opt.index; 
			}, H_plot_samples_opt.postfixes, H_plot_samples_opt.legends, H_plot_samples_opt.colors);


	static const PostfixOptions background_signal_opt = get_pf_opts_({background, signal_selected}, v.sample);
	sh.AddNewPostfix("Background_Signal", [this] { 
			if (background_signal_opt.index==2) {
			if (v.susy_mass[0]!=BM_GLU || v.susy_mass[1] != BM_GLU_NEU) return (size_t)-1;
			}
			return background_signal_opt.index;
			}, background_signal_opt.postfixes, background_signal_opt.legends, "633,601");

	static const PostfixOptions signals_opt = get_pf_opts_({signal_all}, v.sample);
	sh.AddNewPostfix("Signals",  [this] { 
			if (signals_opt.index>=0&&signals_opt.index<3) {
				if (v.susy_mass[0] != BM_GLU  || v.susy_mass[1] != BM_GLU_NEU) return (size_t)-1; // T5ttcc
			} else if (signals_opt.index>=3 && signals_opt.index<4) {
				if (v.susy_mass[0] != BM_SQU || v.susy_mass[1] != BM_SQU_NEU) return (size_t)-1; // T6bbZH/TChiZH
			} else if (signals_opt.index>=5 && signals_opt.index<10) {
				if (v.susy_mass[0] != BM_EWK  || v.susy_mass[1] != BM_EWK_NEU) return (size_t)-1; // TChiWZ/TChiWH/TChiHH
			} else if (signals_opt.index>=10 && signals_opt.index<12) {
				if (v.susy_mass[0] != BM_GLU  || v.susy_mass[1] != BM_GLU-50) return (size_t)-1; // T5qqqqZH
			}
			return signals_opt.index; 
			}, signals_opt.postfixes, signals_opt.legends, signals_opt.colors);

/*
	static const PostfixOptions fast_signals_opt = get_pf_opts_({signal_all}, v.sample);
	sh.AddNewPostfix("FullFastSim",  [this] { 
			if (fast_signals_opt.index==2) {
			if (v.susy_mass[0] != 850 || v.susy_mass[1] != 100) return (size_t)-1; 
			} else if (fast_signals_opt.index==6) {
			if (v.susy_mass[0] != 800 || v.susy_mass[1] != 100) return (size_t)-1;
			} else if (fast_signals_opt.index==7) {
			if (v.susy_mass[0] != 800 || v.susy_mass[1] != 100) return (size_t)-1; 
			}
			return fast_signals_opt.index; 
			}, fast_signals_opt.postfixes, fast_signals_opt.legends, fast_signals_opt.colors);
*/
	static const PostfixOptions signals_background_opt = get_pf_opts_({signal_all, background}, v.sample);
	sh.AddNewPostfix("Signals_Background",  [this] { 
			if (signals_background_opt.index>=0&&signals_background_opt.index<3) {
			if (v.susy_mass[0] != BM_SQU || v.susy_mass[1] != BM_SQU_NEU) return (size_t)-1; // T6bbZH/TChiZH
			} else if (signals_background_opt.index>=3 && signals_background_opt.index<5) {
			if (v.susy_mass[0] != BM_GLU  || v.susy_mass[1] != BM_GLU_NEU) return (size_t)-1; // T5ttcc
			} else if (signals_background_opt.index>=5 && signals_background_opt.index<6) {
			if (v.susy_mass[0] != BM_GLU  || v.susy_mass[1] != BM_GLU-50) return (size_t)-1; // T5qqqqZH
			} else if (signals_background_opt.index>=6 && signals_background_opt.index<9) {
			if (v.susy_mass[0] != BM_EWK  || v.susy_mass[1] != BM_EWK_NEU) return (size_t)-1; // TChiWZ/TChiWH/TChiHH
			}
			return signals_background_opt.index; 
			}, signals_background_opt.postfixes, signals_background_opt.legends, signals_background_opt.colors);

	static const PostfixOptions ttbar_signal_opt = get_pf_opts_({ttbar_selected, signal_selected}, v.sample);
	sh.AddNewPostfix("TT_Signal",  [this] { 
			if (ttbar_signal_opt.index==0) return (size_t)0;
			else if (ttbar_signal_opt.index==1) {
			if (v.susy_mass[0] == BM_GLU  && v.susy_mass[1] == BM_GLU_NEU) return (size_t)1;
			}
			return (size_t)-1;
			}, "TTbar;T5ttcc_Mlsp"+bm_glu_lsp+"_Mglu"+bm_glu, "t#bar{t};T5ttcc m_{#tilde{g}}="+bm_glu+"GeV", "1,633");
	sh.AddNewPostfix("TT_SignalPoints",  [this] { 
			if (ttbar_signal_opt.index==0) return (size_t)0;
			else if (ttbar_signal_opt.index==1) {
			if (v.susy_mass[1] == BM_GLU_NEU) {
			if      (v.susy_mass[0]==1400) return (size_t)1;
			else if (v.susy_mass[0]==1600) return (size_t)2;
			else if (v.susy_mass[0]==1800) return (size_t)3;
			else if (v.susy_mass[0]==2000) return (size_t)4;
			else if (v.susy_mass[0]==2200) return (size_t)5;
			else if (v.susy_mass[0]==2400) return (size_t)6;
			}
			}
			return (size_t)-1;
			}, "TTbar;T5ttcc_Mlsp"+bm_glu_lsp+"_Mglu[1400to2400++200]", "t#bar{t};T5ttcc m_{#tilde{g}}=[1.4to2.4++0.2]TeV m_{#tilde{#chi}^{0}_{1}}="+bm_glu_lsp+"GeV", "1,"+col6_rainbow_dark);


	if (debug) std::cout<<"PlottingBase::define_histo_settings: ok6"<<std::endl;
	static const PostfixOptions mgluinopoints_opt = get_pf_opts_({signal_gluino}, v.sample);
	sh.AddNewPostfix("MGluinoPoints",  [this] { 
			if (mgluinopoints_opt.index==(size_t)-1) return (size_t)-1;
			else {
			if      (v.susy_mass[0]==1400) return (size_t)0;
			else if (v.susy_mass[0]==1600) return (size_t)1;
			else if (v.susy_mass[0]==1800) return (size_t)2;
			else if (v.susy_mass[0]==2000) return (size_t)3;
			else if (v.susy_mass[0]==2200) return (size_t)4;
			else if (v.susy_mass[0]==2400) return (size_t)5;
			else return (size_t)-1;
			}
			}, "Mglu[1400to2400++200]", "m_{#tilde{g}}=[1.4to2.4++0.2]TeV", col6_rainbow_dark);
	static const PostfixOptions msquarkpoints_opt = get_pf_opts_({signal_squark}, v.sample);
	sh.AddNewPostfix("MSquarkPoints",  [this] { 
			if (msquarkpoints_opt.index==(size_t)-1) return (size_t)-1;
			else {
			if      (v.susy_mass[0]== 400) return (size_t)0;
			else if (v.susy_mass[0]== 600) return (size_t)1;
			else if (v.susy_mass[0]== 800) return (size_t)2;
			else if (v.susy_mass[0]==1000) return (size_t)3;
			else if (v.susy_mass[0]==1200) return (size_t)4;
			else if (v.susy_mass[0]==1400) return (size_t)5;
			else return (size_t)-1;
			}
			}, "Msquark[400to1400++200]", "m_{#tilde{t}}=[0.4to1.4++0.2]TeV", col6_rainbow_dark);
	static const PostfixOptions mewpoints_opt = get_pf_opts_({signal_ewk}, v.sample);
	sh.AddNewPostfix("MEWKPoints",  [this] { 
			if (mewpoints_opt.index==(size_t)-1) return (size_t)-1;
			else {
			if      (v.susy_mass[0]== 400) return (size_t)0;
			else if (v.susy_mass[0]== 500) return (size_t)1;
			else if (v.susy_mass[0]== 600) return (size_t)2;
			else if (v.susy_mass[0]== 700) return (size_t)3;
			else if (v.susy_mass[0]== 800) return (size_t)4;
			else if (v.susy_mass[0]== 900) return (size_t)5;
			else return (size_t)-1;
			}
			}, "Mchi[400to900++100]", "m_{#tilde{#chi}^{#pm}_{1}}=[400to900++100]GeV", col6_rainbow_dark);
	static const PostfixOptions mlsppoints_opt = get_pf_opts_({signal_fastsim}, v.sample);
	sh.AddNewPostfix("MLSPPoints",  [this] { 
			if (mlsppoints_opt.index==(size_t)-1) return (size_t)-1;
			else {
			if      (v.susy_mass[1]==   0) return (size_t)0;
			else if (v.susy_mass[1]== 200) return (size_t)1;
			else if (v.susy_mass[1]== 400) return (size_t)2;
			else if (v.susy_mass[1]== 600) return (size_t)3;
			else if (v.susy_mass[1]== 800) return (size_t)4;
			else if (v.susy_mass[1]==1000) return (size_t)5;
			else return (size_t)-1;
			}
			}, "Mlsp[0to1000++200]", "m_{#tilde{#chi}^{0}_{1}}=[0to1000++200]GeV", col6_rainbow_dark);

	std::vector<std::string> fastsim_dirs;
	for (auto sig : signal_all) for (auto dir : sig.dirs) fastsim_dirs.push_back(dir);
	std::vector<Sample> fastsim;
	fastsim.push_back({ .postfix="FASTSIM",         .legend="FASTSIM",         .color=Black, .dirs=fastsim_dirs });

	// Benchmarks for GenTruth
	top_benchmarks["Bkg"]                         = [] { return (int)(background_opt.index==0 ? 1 : -1); };
#if FASTDEBUG > 0
	top_benchmarks["T5ttcc_"+bm_glu+"_"+bm_glu_lsp]   = [] { return (int)(background_opt.index==0 ? 0 : signals_opt.index==2 ? 1 : -1); };
	WZH_benchmarks["T6ttZH_"  +bm_squ+"_"+bm_squ_lsp]  = [] { return (int)(background_opt.index==0 ? 0 : signals_opt.index==3 ? 1 : -1); };
#else
	top_benchmarks["T5ttcc_"+bm_glu+"_"+bm_glu_lsp]   = [this] { return (int)(background_opt.index==0 ? 0 : signals_opt.index==2 && v.susy_mass[0] == BM_GLU  && v.susy_mass[1] == BM_GLU_NEU  ? 1 : -1); };
	top_benchmarks["T5ttcc_"+bm_glu+"_600"]           = [this] { return (int)(background_opt.index==0 ? 0 : signals_opt.index==2 && v.susy_mass[0] == BM_GLU  && v.susy_mass[1] == 600         ? 1 : -1); };
	top_benchmarks["T5ttcc_"+bm_glu+"_1000"]          = [this] { return (int)(background_opt.index==0 ? 0 : signals_opt.index==2 && v.susy_mass[0] == BM_GLU  && v.susy_mass[1] == 1000        ? 1 : -1); };
	WZH_benchmarks["T6bbZH_"  +bm_squ+"_"+bm_squ_lsp]  = [this] { return (int)(background_opt.index==0 ? 0 : signals_opt.index==3 && v.susy_mass[0] == BM_SQU && v.susy_mass[1] == BM_SQU_NEU  ? 1 : -1); };
#endif
	WZH_benchmarks["Bkg"]                             = [] { return (int)(background_opt.index==0 ? 1 : -1); };
#if FASTDEBUG > 0
	WZH_benchmarks["T5qqqqWH_"+bm_glu+"_"+bm_glu_lsp]  = [] { return (int)(background_opt.index==0 ? 0 : signals_opt.index==0 ? 1 : -1); };
	WZH_benchmarks["T5bbbbZH_"+bm_glu]                 = [] { return (int)(background_opt.index==0 ? 0 : signals_opt.index==1 ? 1 : -1); };
	WZH_benchmarks["TChiHH_"  +bm_chg+"_"+bm_chg_lsp]  = [] { return (int)(background_opt.index==0 ? 0 : signals_opt.index==8 ? 1 : -1); };
#else
	WZH_benchmarks["T5qqqqWH_"+bm_glu+"_"+bm_glu_lsp]  = [this] { return (int)(background_opt.index==0 ? 0 : signals_opt.index==0 && v.susy_mass[0] == BM_GLU && v.susy_mass[1] == BM_GLU_NEU ? 1 : -1); };
	WZH_benchmarks["T5qqqqWH_"+bm_glu+"_600"]          = [this] { return (int)(background_opt.index==0 ? 0 : signals_opt.index==0 && v.susy_mass[0] == BM_GLU && v.susy_mass[1] == 600 ? 1 : -1); };
	WZH_benchmarks["T5qqqqWH_"+bm_glu+"_1000"]         = [this] { return (int)(background_opt.index==0 ? 0 : signals_opt.index==0 && v.susy_mass[0] == BM_GLU && v.susy_mass[1] == 1000 ? 1 : -1); };
	WZH_benchmarks["T5bbbbZH_"+bm_glu]                 = [this] { return (int)(background_opt.index==0 ? 0 : signals_opt.index==1 && v.susy_mass[0] == BM_GLU && v.susy_mass[1] == BM_GLU-50 ? 1 : -1); };
	WZH_benchmarks["TChiHH_"  +bm_chg+"_"+bm_chg_lsp]  = [this] { return (int)(background_opt.index==0 ? 0 : signals_opt.index==7 && v.susy_mass[0] == BM_EWK && v.susy_mass[1] == BM_EWK_NEU ? 1 : -1); };
	WZH_benchmarks["TChiHH_"  +bm_chg+"_600"]          = [this] { return (int)(background_opt.index==0 ? 0 : signals_opt.index==7 && v.susy_mass[0] == BM_EWK && v.susy_mass[1] == 600 ? 1 : -1); };
#endif
	WZH_benchmarks["TChiWH_"  +bm_chg+"_"+bm_chg_lsp] = [this] { return (int)(background_opt.index==0 ? 0 : signals_opt.index==6 && v.susy_mass[0] == BM_EWK && v.susy_mass[1] == BM_EWK_NEU ? 1 : -1); };
	WZH_benchmarks["TChiWH_"  +bm_chg+"_600"]         = [this] { return (int)(background_opt.index==0 ? 0 : signals_opt.index==6 && v.susy_mass[0] == BM_EWK && v.susy_mass[1] == 600 ? 1 : -1); };
	WZH_benchmarks["TChiWZ_"  +bm_chg+"_"+bm_chg_lsp] = [this] { return (int)(background_opt.index==0 ? 0 : signals_opt.index==5 && v.susy_mass[0] == BM_EWK && v.susy_mass[1] == BM_EWK_NEU ? 1 : -1); };
	WZH_benchmarks["TChiWZ_"  +bm_chg+"_600"]         = [this] { return (int)(background_opt.index==0 ? 0 : signals_opt.index==5 && v.susy_mass[0] == BM_EWK && v.susy_mass[1] == 600 ? 1 : -1); };

	for (const auto& bm : top_benchmarks) all_benchmarks[bm.first]=bm.second;
	for (const auto& bm : WZH_benchmarks) if (bm.first!="Bkg") all_benchmarks[bm.first]=bm.second;  


	// ---------------------- Combinations ---------------------

	// Sample postfixes
	if (debug) std::cout<<"PlottingBase::define_histo_settings: ok5"<<std::endl;
	static const PostfixOptions all_samples_opt=get_pf_opts_({data_all, bkg_all, signal_all}, v.sample);
	sh.AddNewPostfix("AllSamples", [] { return all_samples_opt.index; }, all_samples_opt.postfixes, all_samples_opt.legends, all_samples_opt.colors);

	static const PostfixOptions plot_samples2_opt=get_pf_opts_({data_selected, bkg_selected}, v.sample);
	sh.AddNewPostfix("StackPlot", [] { 
			return plot_samples2_opt.index; 
			}, plot_samples2_opt.postfixes, plot_samples2_opt.legends, plot_samples2_opt.colors);

	static const PostfixOptions data_opt=get_pf_opts_({data_selected}, v.sample);
	sh.AddNewPostfix("Data", [] { return data_opt.index;  }, data_opt.postfixes, data_opt.legends, data_opt.colors);

	sh.AddNewPostfix("Background",  [] { return background_opt.index; }, background_opt.postfixes, background_opt.legends, background_opt.colors);
	static const PostfixOptions mc_opt = get_pf_opts_({mc}, v.sample);
	sh.AddNewPostfix("MC",  [] { return mc_opt.index; }, mc_opt.postfixes, mc_opt.legends, mc_opt.colors);

	static const PostfixOptions bkgs_opt=get_pf_opts_({bkg_selected}, v.sample);
	sh.AddNewPostfix("Backgrounds", [] { return bkgs_opt.index;  }, bkgs_opt.postfixes, bkgs_opt.legends, bkgs_opt.colors);

	static const PostfixOptions multijet_opt=get_pf_opts_({multijet}, v.sample);
	sh.AddNewPostfix("Multijet", [] { return multijet_opt.index;  }, multijet_opt.postfixes, multijet_opt.legends, multijet_opt.colors);
	static const PostfixOptions znunu_opt=get_pf_opts_({znunu}, v.sample);
	sh.AddNewPostfix("ZToNuNu", [] { return znunu_opt.index;  }, znunu_opt.postfixes, znunu_opt.legends, znunu_opt.colors);
	static const PostfixOptions gjets_opt=get_pf_opts_({gjets}, v.sample);
	sh.AddNewPostfix("GJets", [] { return gjets_opt.index;  }, gjets_opt.postfixes, gjets_opt.legends, gjets_opt.colors);

	static const PostfixOptions gluino_signalscans_opt = get_pf_opts_({signal_gluino}, v.sample);
	sh.AddNewPostfix("GluinoSignalScans",  [] { return gluino_signalscans_opt.index; }, gluino_signalscans_opt.postfixes, gluino_signalscans_opt.legends, gluino_signalscans_opt.colors);

	static const PostfixOptions squark_signalscans_opt = get_pf_opts_({signal_squark}, v.sample);
	sh.AddNewPostfix("SquarkSignalScans",  [] { return squark_signalscans_opt.index; }, squark_signalscans_opt.postfixes, squark_signalscans_opt.legends, squark_signalscans_opt.colors);

	static const PostfixOptions ew_signalscans_opt = get_pf_opts_({signal_ewk}, v.sample);
	sh.AddNewPostfix("EWKSignalScans",  [] { return ew_signalscans_opt.index; }, ew_signalscans_opt.postfixes, ew_signalscans_opt.legends, ew_signalscans_opt.colors);

	static const PostfixOptions Bkg_T5ttcc_opt=get_pf_opts_({background, T5ttcc}, v.sample);
	static const PostfixOptions Bkg_TChiWW_opt=get_pf_opts_({background, TChiWW}, v.sample);
	static const PostfixOptions Bkg_TChiWZ_opt=get_pf_opts_({background, TChiWZ}, v.sample);
	static const PostfixOptions Bkg_TChiZH_opt=get_pf_opts_({background, TChiZH}, v.sample);
	static const PostfixOptions Bkg_R5ttbl_opt=get_pf_opts_({background, R5ttbl}, v.sample);
	static const PostfixOptions Bkg_R2bbqqlv_opt=get_pf_opts_({background, R2bbqqlv}, v.sample);
	static const PostfixOptions Bkg_T5bbbbZH_opt=get_pf_opts_({background, T5bbbbZH}, v.sample);
	static const PostfixOptions Bkg_T5qqqqWH_opt=get_pf_opts_({background, T5qqqqWH}, v.sample);
	static const PostfixOptions Bkg_T6ttZH_opt=get_pf_opts_({background, T6ttZH}, v.sample);


	static const PostfixOptions TChiZH_opt = get_pf_opts_({TChiZH}, v.sample);
	sh.AddNewPostfix("TChiZH",  [] { return TChiZH_opt.index; }, TChiZH_opt.postfixes, TChiZH_opt.legends, TChiZH_opt.colors);
	static const PostfixOptions R5ttbl_opt = get_pf_opts_({R5ttbl}, v.sample);
	sh.AddNewPostfix("R5ttbl",  [] { return R5ttbl_opt.index; }, R5ttbl_opt.postfixes, R5ttbl_opt.legends, R5ttbl_opt.colors);
	static const PostfixOptions R2bbqqlv_opt = get_pf_opts_({R2bbqqlv}, v.sample);
	sh.AddNewPostfix("R2bbqqlv",  [] { return R2bbqqlv_opt.index; }, R2bbqqlv_opt.postfixes, R2bbqqlv_opt.legends, R2bbqqlv_opt.colors);
	static const PostfixOptions T5bbbbZH_opt = get_pf_opts_({T5bbbbZH}, v.sample);
	sh.AddNewPostfix("T5bbbbZH",  [] { return T5bbbbZH_opt.index; }, T5bbbbZH_opt.postfixes, T5bbbbZH_opt.legends, T5bbbbZH_opt.colors);
	static const PostfixOptions T5qqqqWH_opt = get_pf_opts_({T5qqqqWH}, v.sample);
	sh.AddNewPostfix("T5qqqqWH",  [] { return T5qqqqWH_opt.index; }, T5qqqqWH_opt.postfixes, T5qqqqWH_opt.legends, T5qqqqWH_opt.colors);
	static const PostfixOptions T6ttZH_opt = get_pf_opts_({T6ttZH}, v.sample);
	sh.AddNewPostfix("T6ttZH",  [] { return T6ttZH_opt.index; }, T6ttZH_opt.postfixes, T6ttZH_opt.legends, T6ttZH_opt.colors);


	static const PostfixOptions T5ttcc_opt = get_pf_opts_({T5ttcc}, v.sample);
	sh.AddNewPostfix("T5ttcc",  [] { return T5ttcc_opt.index; }, T5ttcc_opt.postfixes, T5ttcc_opt.legends, T5ttcc_opt.colors);
	static const PostfixOptions TChiWW_opt = get_pf_opts_({TChiWW}, v.sample);
	sh.AddNewPostfix("TChiWW",  [] { return TChiWW_opt.index; }, TChiWW_opt.postfixes, TChiWW_opt.legends, TChiWW_opt.colors);
	static const PostfixOptions TChiWZ_opt = get_pf_opts_({TChiWZ}, v.sample);
	sh.AddNewPostfix("TChiWZ",  [] { return TChiWZ_opt.index; }, TChiWZ_opt.postfixes, TChiWZ_opt.legends, TChiWZ_opt.colors);

	if (debug) std::cout<<"PlottingBase::define_histo_settings: ok7"<<std::endl;
	static const PostfixOptions data_mc_opt = get_pf_opts_({data_selected, mc}, v.sample);
	sh.AddNewPostfix("Data_MC",  [] { return data_mc_opt.index; }, data_mc_opt.postfixes, data_mc_opt.legends, "1,633");
	//static const PostfixOptions data_fastsim_opt = get_pf_opts_({data_selected, signal_all}, v.sample);
	static const PostfixOptions data_fastsim_opt = get_pf_opts_({data_selected, fastsim}, v.sample);
	sh.AddNewPostfix("Data_FastSim",  [] { return data_fastsim_opt.index; }, data_fastsim_opt.postfixes, data_fastsim_opt.legends, "1,633");
	static const PostfixOptions fast_signals_opt = get_pf_opts_({mc, fastsim}, v.sample);
	sh.AddNewPostfix("FullFastSim",  [] { return  fast_signals_opt.index; }, fast_signals_opt.postfixes, fast_signals_opt.legends, "1,633");


	static const PostfixOptions triggers_opt = get_pf_opts_({single_ele, single_pho, single_mu, mc}, v.sample);
	sh.AddNewPostfix("HadronicMeasurements", [this]() {
			size_t i = -1;
			if (triggers_opt.index==0) {
			if (v.year<2018) {
			// SingleElectron
			if (!(v.HLT_Ele27_WPTight_Gsf==1||v.HLT_Ele30_WPTight_Gsf==1 ||
						v.HLT_Ele32_WPTight_Gsf==1||v.HLT_Ele35_WPTight_Gsf==1||v.HLT_Ele38_WPTight_Gsf==1||
						v.HLT_Ele105_CaloIdVT_GsfTrkIdT==1||v.HLT_Ele115_CaloIdVT_GsfTrkIdT==1)) return (size_t)-1;
			if (!(v.Electron.Select.n==1&&v.Muon.Veto.n==0)) return (size_t)-1;
			if (v.Jet.Jet.n<2) return (size_t)-1;
			if (v.R2<0.08) return (size_t)-1;
			if (v.MR<800) return (size_t)-1;
			//i = (v.Electron.Select(0).pt>=50);
			i = 0;
			} else {
			// EGamma
			bool OR_HLT_Photon = 
			v.HLT_Photon20==1 ||
			v.HLT_Photon22==1 ||
			//v.HLT_Photon25==1 ||
			v.HLT_Photon30==1 ||
			v.HLT_Photon33==1 ||
			v.HLT_Photon36==1 ||
			v.HLT_Photon50==1 ||
			v.HLT_Photon75==1 ||
			v.HLT_Photon90==1 ||
			v.HLT_Photon120==1 ||
			v.HLT_Photon125==1 ||
			v.HLT_Photon150==1 ||
			v.HLT_Photon165_HE10==1 ||
			v.HLT_Photon165_R9Id90_HE10_IsoM==1 ||
			v.HLT_Photon175==1 ||
			v.HLT_Photon200==1 ||
			v.HLT_Photon250_NoHE==1 ||
			v.HLT_Photon300_NoHE==1;
			if ( (v.HLT_Ele27_WPTight_Gsf==1||v.HLT_Ele30_WPTight_Gsf==1 ||
						v.HLT_Ele32_WPTight_Gsf==1||v.HLT_Ele35_WPTight_Gsf==1||v.HLT_Ele38_WPTight_Gsf==1||
						v.HLT_Ele105_CaloIdVT_GsfTrkIdT==1||v.HLT_Ele115_CaloIdVT_GsfTrkIdT==1) &&
					(v.Electron.Select.n==1&&v.Muon.Veto.n==0) &&
					(v.Jet.Jet.n>=2) &&
					(v.R2>=0.08) &&
					(v.MR>=800) ) {
				i = 0;
			} else if ( (OR_HLT_Photon) &&
					(v.Photon.Select.n==1&&v.nLepVeto==0&&v.Tau.Veto.n==0) &&
					(v.Jet.JetNoPho.n>=2) &&
					(v.R2_pho>=0.08) &&
					(v.MR_pho>=800) ) {
				i = 1;
			}
			}
			} else if (triggers_opt.index==1) { 
				// SinglePhoton
				bool OR_HLT_Photon = 
					v.HLT_Photon20==1 ||
					v.HLT_Photon22==1 ||
					//v.HLT_Photon25==1 ||
					v.HLT_Photon30==1 ||
					v.HLT_Photon33==1 ||
					v.HLT_Photon36==1 ||
					v.HLT_Photon50==1 ||
					v.HLT_Photon75==1 ||
					v.HLT_Photon90==1 ||
					v.HLT_Photon120==1 ||
					v.HLT_Photon125==1 ||
					v.HLT_Photon150==1 ||
					v.HLT_Photon165_HE10==1 ||
					v.HLT_Photon165_R9Id90_HE10_IsoM==1 ||
					v.HLT_Photon175==1 ||
					v.HLT_Photon200==1 ||
					v.HLT_Photon250_NoHE==1 ||
					v.HLT_Photon300_NoHE==1;
				if (!(OR_HLT_Photon)) return (size_t)-1;
				if (!(v.Photon.Select.n==1&&v.nLepVeto==0&&v.Tau.Veto.n==0)) return (size_t)-1;
				if (v.Jet.JetNoPho.n<2) return (size_t)-1;
				if (v.R2_pho<0.08) return (size_t)-1;
				if (v.MR_pho<800) return (size_t)-1;
				i = 1;
			} else if (triggers_opt.index==2) { // SingleMuon
				if (!(v.HLT_IsoMu24==1||v.HLT_IsoTkMu24==1||v.HLT_IsoMu27==1||v.HLT_IsoTkMu27==1||
							v.HLT_Mu50==1||v.HLT_TkMu50==1||v.HLT_Mu55==1||v.HLT_OldMu100==1||v.HLT_TkMu100==1)) return (size_t)-1;
				if (!(v.Muon.Select.n==1&&v.Electron.Veto.n==0)) return (size_t)-1;
				if (v.Jet.Jet.n<2) return (size_t)-1;
				if (v.R2<0.08) return (size_t)-1;
				if (v.MR<800) return (size_t)-1;
				//i = (v.Muon.Select(0).pt>=50)+3;
				i = 2;
			} else if (triggers_opt.index==3) { // Simulation
				if (v.Jet.Jet.n<2) return (size_t)-1;
				if (v.R2<0.08) return (size_t)-1;
				if (v.MR<800) return (size_t)-1;
				//i = 5;
				i = 3;
			}
			return i;
			//}, "SingleElectron_LowPt;SingleElectron_HighPt;SinglePhoton;SingleMuon_LowPt;SingleMuon_HighPt;MC", 
			//"e low;e high;#gamma;#mu low;#mu high;MC", Purple+Red+DYellow+Cyan+Blue+Black);
}, "SingleElectron;SinglePhoton;SingleMuon;MC", 
	"ele;#gamma;#mu;MC", Red+DYellow+Blue+Black);
// Same without R2 cut
sh.AddNewPostfix("HadronicMeasurementsNoR2", [this]() {
		size_t i = -1;
		if (triggers_opt.index==0) {
		if (v.year<2018) {
		// SingleElectron
		if (!(v.HLT_Ele27_WPTight_Gsf==1||v.HLT_Ele30_WPTight_Gsf==1 ||
					v.HLT_Ele32_WPTight_Gsf==1||v.HLT_Ele35_WPTight_Gsf==1||v.HLT_Ele38_WPTight_Gsf==1||
					v.HLT_Ele105_CaloIdVT_GsfTrkIdT==1||v.HLT_Ele115_CaloIdVT_GsfTrkIdT==1)) return (size_t)-1;
		if (!(v.Electron.Select.n==1&&v.Muon.Veto.n==0)) return (size_t)-1;
		if (v.Jet.Jet.n<2) return (size_t)-1;
		if (v.MR<800) return (size_t)-1;
		//i = (v.Electron.Select(0).pt>=50);
		i = 0;
		} else {
		// EGamma
		bool OR_HLT_Photon = 
		v.HLT_Photon20==1 ||
		v.HLT_Photon22==1 ||
		//v.HLT_Photon25==1 ||
		v.HLT_Photon30==1 ||
		v.HLT_Photon33==1 ||
		v.HLT_Photon36==1 ||
		v.HLT_Photon50==1 ||
		v.HLT_Photon75==1 ||
		v.HLT_Photon90==1 ||
		v.HLT_Photon120==1 ||
		v.HLT_Photon125==1 ||
		v.HLT_Photon150==1 ||
		v.HLT_Photon165_HE10==1 ||
		v.HLT_Photon165_R9Id90_HE10_IsoM==1 ||
		v.HLT_Photon175==1 ||
		v.HLT_Photon200==1 ||
		v.HLT_Photon250_NoHE==1 ||
		v.HLT_Photon300_NoHE==1;
		if ( (v.HLT_Ele27_WPTight_Gsf==1||v.HLT_Ele30_WPTight_Gsf==1 ||
					v.HLT_Ele32_WPTight_Gsf==1||v.HLT_Ele35_WPTight_Gsf==1||v.HLT_Ele38_WPTight_Gsf==1||
					v.HLT_Ele105_CaloIdVT_GsfTrkIdT==1||v.HLT_Ele115_CaloIdVT_GsfTrkIdT==1) &&
				(v.Electron.Select.n==1&&v.Muon.Veto.n==0) &&
				(v.Jet.Jet.n>=2) &&
				(v.MR>=800) ) {
			i = 0;
		} else if ( (OR_HLT_Photon) &&
				(v.Photon.Select.n==1&&v.nLepVeto==0&&v.Tau.Veto.n==0) &&
				(v.Jet.JetNoPho.n>=2) &&
				(v.MR_pho>=800) ) {
			i = 1;
		}
		}
		} else if (triggers_opt.index==1) { 
			// SinglePhoton
			bool OR_HLT_Photon = 
				v.HLT_Photon20==1 ||
				v.HLT_Photon22==1 ||
				//v.HLT_Photon25==1 ||
				v.HLT_Photon30==1 ||
				v.HLT_Photon33==1 ||
				v.HLT_Photon36==1 ||
				v.HLT_Photon50==1 ||
				v.HLT_Photon75==1 ||
				v.HLT_Photon90==1 ||
				v.HLT_Photon120==1 ||
				v.HLT_Photon125==1 ||
				v.HLT_Photon150==1 ||
				v.HLT_Photon165_HE10==1 ||
				v.HLT_Photon165_R9Id90_HE10_IsoM==1 ||
				v.HLT_Photon175==1 ||
				v.HLT_Photon200==1 ||
				v.HLT_Photon250_NoHE==1 ||
				v.HLT_Photon300_NoHE==1;
			if (!(OR_HLT_Photon)) return (size_t)-1;
			if (!(v.Photon.Select.n==1&&v.nLepVeto==0&&v.Tau.Veto.n==0)) return (size_t)-1;
			if (v.Jet.JetNoPho.n<2) return (size_t)-1;
			if (v.MR_pho<800) return (size_t)-1;
			i = 1;
		} else if (triggers_opt.index==2) { // SingleMuon
			if (!(v.HLT_IsoMu24==1||v.HLT_IsoTkMu24==1||v.HLT_IsoMu27==1||v.HLT_IsoTkMu27==1||
						v.HLT_Mu50==1||v.HLT_TkMu50==1||v.HLT_Mu55==1||v.HLT_OldMu100==1||v.HLT_TkMu100==1)) return (size_t)-1;
			if (!(v.Muon.Select.n==1&&v.Electron.Veto.n==0)) return (size_t)-1;
			if (v.Jet.Jet.n<2) return (size_t)-1;
			if (v.MR<800) return (size_t)-1;
			//i = (v.Muon.Select(0).pt>=50)+3;
			i = 2;
		} else if (triggers_opt.index==3) { // Simulation
			if (v.Jet.Jet.n<2) return (size_t)-1;
			if (v.MR<800) return (size_t)-1;
			//i = 5;
			i = 3;
		}
		return i;
		//}, "SingleElectron_LowPt;SingleElectron_HighPt;SinglePhoton;SingleMuon_LowPt;SingleMuon_HighPt;MC", 
		//"e low;e high;#gamma;#mu low;#mu high;MC", Purple+Red+DYellow+Cyan+Blue+Black);
		}, "SingleElectron;SinglePhoton;SingleMuon;MC", 
		"ele;#gamma;#mu;MC", Red+DYellow+Blue+Black);
sh.AddNewPostfix("HadronicMeasurementsInvR2", [this]() {
		size_t i = -1;
		if (triggers_opt.index==0) {
		if (v.year<2018) {
		// SingleElectron
		if (!(v.HLT_Ele27_WPTight_Gsf==1||v.HLT_Ele30_WPTight_Gsf==1 ||
					v.HLT_Ele32_WPTight_Gsf==1||v.HLT_Ele35_WPTight_Gsf==1||v.HLT_Ele38_WPTight_Gsf==1||
					v.HLT_Ele105_CaloIdVT_GsfTrkIdT==1||v.HLT_Ele115_CaloIdVT_GsfTrkIdT==1)) return (size_t)-1;
		if (!(v.Electron.Select.n==1&&v.Muon.Veto.n==0)) return (size_t)-1;
		if (v.Jet.Jet.n<2) return (size_t)-1;
		if (v.R2>=0.08) return (size_t)-1;
		if (v.MR<800) return (size_t)-1;
		//i = (v.Electron.Select(0).pt>=50);
		i = 0;
		} else {
		// EGamma
		bool OR_HLT_Photon = 
		v.HLT_Photon20==1 ||
		v.HLT_Photon22==1 ||
		//v.HLT_Photon25==1 ||
		v.HLT_Photon30==1 ||
		v.HLT_Photon33==1 ||
		v.HLT_Photon36==1 ||
		v.HLT_Photon50==1 ||
		v.HLT_Photon75==1 ||
		v.HLT_Photon90==1 ||
		v.HLT_Photon120==1 ||
		v.HLT_Photon125==1 ||
		v.HLT_Photon150==1 ||
		v.HLT_Photon165_HE10==1 ||
		v.HLT_Photon165_R9Id90_HE10_IsoM==1 ||
		v.HLT_Photon175==1 ||
		v.HLT_Photon200==1 ||
		v.HLT_Photon250_NoHE==1 ||
		v.HLT_Photon300_NoHE==1;
		if ( (v.HLT_Ele27_WPTight_Gsf==1||v.HLT_Ele30_WPTight_Gsf==1 ||
					v.HLT_Ele32_WPTight_Gsf==1||v.HLT_Ele35_WPTight_Gsf==1||v.HLT_Ele38_WPTight_Gsf==1||
					v.HLT_Ele105_CaloIdVT_GsfTrkIdT==1||v.HLT_Ele115_CaloIdVT_GsfTrkIdT==1) &&
				(v.Electron.Select.n==1&&v.Muon.Veto.n==0) &&
				(v.Jet.Jet.n>=2) &&
				(v.R2>=0.08) &&
				(v.MR>=800) ) {
			i = 0;
		} else if ( (OR_HLT_Photon) &&
				(v.Photon.Select.n==1&&v.nLepVeto==0&&v.Tau.Veto.n==0) &&
				(v.Jet.JetNoPho.n>=2) &&
				(v.R2_pho>=0.08) &&
				(v.MR_pho>=800) ) {
			i = 1;
		}
		}
		} else if (triggers_opt.index==1) { 
			// SinglePhoton
			bool OR_HLT_Photon = 
				v.HLT_Photon20==1 ||
				v.HLT_Photon22==1 ||
				//v.HLT_Photon25==1 ||
				v.HLT_Photon30==1 ||
				v.HLT_Photon33==1 ||
				v.HLT_Photon36==1 ||
				v.HLT_Photon50==1 ||
				v.HLT_Photon75==1 ||
				v.HLT_Photon90==1 ||
				v.HLT_Photon120==1 ||
				v.HLT_Photon125==1 ||
				v.HLT_Photon150==1 ||
				v.HLT_Photon165_HE10==1 ||
				v.HLT_Photon165_R9Id90_HE10_IsoM==1 ||
				v.HLT_Photon175==1 ||
				v.HLT_Photon200==1 ||
				v.HLT_Photon250_NoHE==1 ||
				v.HLT_Photon300_NoHE==1;
			if (!(OR_HLT_Photon)) return (size_t)-1;
			if (!(v.Photon.Select.n==1&&v.nLepVeto==0&&v.Tau.Veto.n==0)) return (size_t)-1;
			if (v.Jet.JetNoPho.n<2) return (size_t)-1;
			if (v.R2_pho>=0.08) return (size_t)-1;
			if (v.MR_pho<800) return (size_t)-1;
			i = 1;
		} else if (triggers_opt.index==2) { // SingleMuon
			if (!(v.HLT_IsoMu24==1||v.HLT_IsoTkMu24==1||v.HLT_IsoMu27==1||v.HLT_IsoTkMu27==1||
						v.HLT_Mu50==1||v.HLT_TkMu50==1||v.HLT_Mu55==1||v.HLT_OldMu100==1||v.HLT_TkMu100==1)) return (size_t)-1;
			if (!(v.Muon.Select.n==1&&v.Electron.Veto.n==0)) return (size_t)-1;
			if (v.Jet.Jet.n<2) return (size_t)-1;
			if (v.R2>=0.08) return (size_t)-1;
			if (v.MR<800) return (size_t)-1;
			//i = (v.Muon.Select(0).pt>=50)+3;
			i = 2;
		} else if (triggers_opt.index==3) { // Simulation
			if (v.Jet.Jet.n<2) return (size_t)-1;
			if (v.R2>=0.08) return (size_t)-1;
			if (v.MR<800) return (size_t)-1;
			//i = 5;
			i = 3;
		}
		return i;
		//}, "SingleElectron_LowPt;SingleElectron_HighPt;SinglePhoton;SingleMuon_LowPt;SingleMuon_HighPt;MC", 
		//"e low;e high;#gamma;#mu low;#mu high;MC", Purple+Red+DYellow+Cyan+Blue+Black);
		}, "SingleElectron;SinglePhoton;SingleMuon;MC", 
		"ele;#gamma;#mu;MC", Red+DYellow+Blue+Black);
sh.AddNewPostfix("NonIsoLepMeasurements", [this]() {
		size_t i = -1;
		if (triggers_opt.index==0) {
		if (v.year<2018) {
		// SingleElectron
		if (!(v.HLT_Ele15_IsoVVVL_PFHT350==1 ||
					v.HLT_Ele15_IsoVVVL_PFHT400==1 ||
					v.HLT_Ele15_IsoVVVL_PFHT450==1 ||
					v.HLT_Ele15_IsoVVVL_PFHT600==1 ||
					v.HLT_Ele27_WPTight_Gsf==1||v.HLT_Ele30_WPTight_Gsf==1 ||
					v.HLT_Ele32_WPTight_Gsf==1||v.HLT_Ele35_WPTight_Gsf==1||v.HLT_Ele38_WPTight_Gsf==1||
					v.HLT_Ele105_CaloIdVT_GsfTrkIdT==1||v.HLT_Ele115_CaloIdVT_GsfTrkIdT==1)) return (size_t)-1;
		if (!(v.Electron.NonIso.n==1&&v.Muon.Veto.n==0)) return (size_t)-1;
		if (v.Jet.Jet.n<2) return (size_t)-1;
		if (v.R2<0.08) return (size_t)-1;
		if (v.MR<800) return (size_t)-1;
		i = 0;
		} else {
		// EGamma
		if ( (v.HLT_Ele27_WPTight_Gsf==1||v.HLT_Ele30_WPTight_Gsf==1 ||
					v.HLT_Ele32_WPTight_Gsf==1||v.HLT_Ele35_WPTight_Gsf==1||v.HLT_Ele38_WPTight_Gsf==1||
					v.HLT_Ele105_CaloIdVT_GsfTrkIdT==1||v.HLT_Ele115_CaloIdVT_GsfTrkIdT==1) &&
				(v.Electron.NonIso.n==1&&v.Muon.Veto.n==0) &&
				(v.Jet.Jet.n>=2) &&
				(v.R2>=0.08) &&
				(v.MR>=800) ) {
			i = 0;
		}
		}
		} else if (triggers_opt.index==2) { // SingleMuon
			if (!(v.HLT_Mu15_IsoVVVL_PFHT350==1 ||
						v.HLT_Mu15_IsoVVVL_PFHT400==1 ||
						v.HLT_Mu15_IsoVVVL_PFHT450==1 ||
						v.HLT_Mu15_IsoVVVL_PFHT600==1 ||
						v.HLT_IsoMu24==1||v.HLT_IsoTkMu24==1||v.HLT_IsoMu27==1||v.HLT_IsoTkMu27==1||
						v.HLT_Mu50==1||v.HLT_TkMu50==1||v.HLT_Mu55==1||v.HLT_OldMu100==1||v.HLT_TkMu100==1)) return (size_t)-1;
			if (!(v.Muon.NonIso.n==1&&v.Electron.Veto.n==0)) return (size_t)-1;
			if (v.Jet.Jet.n<2) return (size_t)-1;
			if (v.R2<0.08) return (size_t)-1;
			if (v.MR<800) return (size_t)-1;
			i = 1;
		}
		return i;
}, "EleNonIso;MuonNonIso", 
	"non-isol. ele;non-isol. #mu", Carrot+DViolet);

static const PostfixOptions triggers3_opt = get_pf_opts_({jetht, met, mc}, v.sample);
sh.AddNewPostfix("LeptonicMeasurements", [this]()
		{
		if (!(v.nLepTight==1)) return (size_t)-1;
		if (triggers3_opt.index==0) { // JetHT
		bool OR_HLT_Had = 
		v.HLT_PFHT125 ||
		v.HLT_PFHT180 ||
		v.HLT_PFHT200 ||
		v.HLT_PFHT250 ||
		v.HLT_PFHT300 ||
		v.HLT_PFHT350 ||
		v.HLT_PFHT370 ||
		v.HLT_PFHT400 ||
		v.HLT_PFHT430 ||
		v.HLT_PFHT475 ||
		v.HLT_PFHT510 ||
		v.HLT_PFHT590 ||
		v.HLT_PFHT650 ||
		v.HLT_PFHT680 ||
		v.HLT_PFHT780 ||
		v.HLT_PFHT800 ||
		v.HLT_PFHT890 ||
		v.HLT_PFHT900 ||
		v.HLT_PFHT1050 ||
		v.HLT_AK8PFJet40 ||
		v.HLT_AK8PFJet60 ||
		v.HLT_AK8PFJet80 ||
		v.HLT_AK8PFJet140 ||
		v.HLT_AK8PFJet200 ||
		v.HLT_AK8PFJet260 ||
		v.HLT_AK8PFJet320 ||
		v.HLT_AK8PFJet400 ||
		v.HLT_AK8PFJet450 ||
		v.HLT_AK8PFJet500 ||
		v.HLT_AK8PFJet550;
		if (!OR_HLT_Had) return (size_t)-1;
		if (v.Jet.Jet.n<3) return (size_t)-1;
		if (v.R2<0.08) return (size_t)-1;
		if (v.MR<700) return (size_t)-1;
		} else if (triggers3_opt.index==1) { // MET
			if (!(v.HLT_PFMET110_PFMHT110_IDTight==1||v.HLT_PFMETNoMu110_PFMHTNoMu110_IDTight==1||
						v.HLT_PFMET120_PFMHT120_IDTight==1||v.HLT_PFMETNoMu120_PFMHTNoMu120_IDTight==1||
						v.HLT_PFMET120_PFMHT120_IDTight_PFHT60==1||v.HLT_PFMETNoMu120_PFMHTNoMu120_IDTight_PFHT60==1)) return (size_t)-1;
			if (v.Jet.Jet.n<3) return (size_t)-1;
			if (v.R2<0.08) return (size_t)-1;
			if (v.MR<700) return (size_t)-1;
		} else if (triggers3_opt.index==2) { // Simulation
			if (v.Jet.Jet.n<3) return (size_t)-1;
			if (v.R2<0.08) return (size_t)-1;
			if (v.MR<700) return (size_t)-1;
		} else {
			return (size_t)-1;
		}
		return (size_t)triggers3_opt.index; 
		}, "JetHT_1Lep;MET_1Lep;MC_1Lep", "HT;MET;Simulation", Carrot+Green+Black);

static const PostfixOptions trigger_opt = get_pf_opts_({single_ele, met}, v.sample);
sh.AddNewPostfix("EleMETComb", [this]()
		{
		if (trigger_opt.index==0) { // SingleElectron
		if ((v.HLT_Ele27_WPTight_Gsf==1||v.HLT_Ele30_WPTight_Gsf==1 ||
					v.HLT_Ele32_WPTight_Gsf==1||v.HLT_Ele35_WPTight_Gsf==1||v.HLT_Ele35_WPTight_Gsf==1)&&
				v.Electron.Select.n==1&&v.Muon.Veto.n==0&&v.Tau.Veto.n==0) return (size_t)0;
		} else if (trigger_opt.index==1) { // MET
		if (v.HLT_PFMET120_PFMHT120_IDTight==1&&v.nLepVeto==0&&v.Tau.Veto.n==0) return (size_t)0;
		}
		return (size_t)-1; 
		}, "SingleEle_MET", "SingleEle + MET", Black);

static const PostfixOptions data_photruth_opt = get_pf_opts_({data_selected, mc}, v.sample);
sh.AddNewPostfix("Data_PhotonTruth",  [this] { 
		if (data_photruth_opt.index==0) return (size_t)0;
		else if (data_photruth_opt.index==1) {
		if      (v.Photon().matchGenPromptDirect) return (size_t)1;
		else if (v.Photon().matchGenPromptFrag)   return (size_t)2;
		else if (v.Photon().matchGenFake)         return (size_t)3;
		}
		return (size_t)-1; }, "Data;PromptDirect;PromptFrag;Fake", "Data;Prompt;Fragm.;Fakes", "1,418,601,633");
sh.AddNewPostfix("Data_Photon1Truth",  [this] { 
		if (v.Photon.Select.n!=1) return (size_t)-1;
		if (data_photruth_opt.index==0) return (size_t)0;
		else if (data_photruth_opt.index==1) {
		if      (v.Photon.Select(0).matchGenPromptDirect) return (size_t)1;
		else if (v.Photon.Select(0).matchGenPromptFrag)   return (size_t)2;
		else if (v.Photon.Select(0).matchGenFake)         return (size_t)3;
		}
		return (size_t)-1; }, "Data;PromptDirect;PromptFrag;Fake", "Data;Prompt;Fragm.;Fakes", "1,418,601,633");

sh.AddNewPostfix("run2", [] { return  (size_t)0; }, "run2;", "run2;", "418");
sh.AddNewPostfix("Year", [this]() { return (size_t)(v.year-2016); }, "2016;2017;2018", "2016;2017;2018", "418,601,633");
sh.AddNewPostfix("YearSF", [this]() { return v.isAPV ? (size_t)0 : (size_t)(v.year-2016+1); }, "2016APV;2016;2017;2018", "2016APV;2016;2017;2018", "1,418,601,633");
sh.AddNewPostfix("YearFS", [this]() { return (size_t)(v.year-2016); }, "2016;2017;2018", "2016;2017;2018", "418,601,633");


if (debug) std::cout<<"PlottingBase::define_histo_settings: sample postfixes ok"<<std::endl;

// ------------------ Signal/Control regions ---------------

// Cut names
std::map<std::string, std::string> legname;
legname["3Jet"]        = "Njet#geq3";
legname["MR"]          = "MR";
legname["R2"]          = "R^{2}";
legname["HLT"]         = "HLT";
legname["0Ele"]        = "ele veto";
legname["0Mu"]         = "muon veto";
legname["0Tau"]        = "tau veto";
legname["1b"]          = "Nb#geq1";
legname["1W"]          = "NW#geq1";
legname["dPhi"]        = "#Delta#phi";
legname["InvdPhi"]     = "inv. #Delta#phi";
legname["0b"]          = "b-tag veto";
legname["1aW"]         = "NW(anti-tag)#geq1";
legname["1aTop"]       = "NTop(anti-tag)#geq1";
//legname["InvdPhi0p3"]  = "#Delta#phi<0.3";
legname["InvdPhi"]     = "inv. #Delta#phi";
legname["1Lep"]        = "Nlep=1";
legname["MT"]          = "m_{T}";
legname["1mW"]         = "NW(mass-tag)#geq1";
legname["1mTop"]       = "NTop(mass-tag)#geq1";
legname["1MTop"]       = "NTop(mass-tag)#geq1";
legname["R2ll"]        = "R^{2}";
legname["2Lep"]        = "Nlep=2";
legname["OppCharge"]   = "#sumq_{lep}=0";
legname["dPhi"]        = "#Delta#phi";
legname["Mll"]         = "|m_{ll} - m_{Z}| < 10 GeV";
legname["1Top"]        = "Ntop#geq1";
legname["1Pho"]        = "N#gamma=1";
std::map<Region, std::string> regionname;
regionname[Region::Pre]              = "Baseline selection";
regionname[Region::Val_QCD16_W]       = "QW";
regionname[Region::Val_Top16_W]       = "TW";
regionname[Region::Val_W16_W]         = "WW";
regionname[Region::Val_QCD16_Top]     = "Qtop";
regionname[Region::Val_Top16_Top]     = "Ttop";
regionname[Region::Val_W16_Top]       = "Wtop";
regionname[Region::Val_QCD16_Z]       = "QZ";
regionname[Region::Val_Top16_Z]       = "TZ";
regionname[Region::Val_W16_Z]         = "WZ";
regionname[Region::Val_QCD16_V]       = "QV";
regionname[Region::Val_Top16_V]       = "TV";
regionname[Region::Val_W16_V]         = "WV";
regionname[Region::Val_QCD16_H]       = "QH";
regionname[Region::Val_Top16_H]       = "TH";
regionname[Region::Val_W16_H]         = "WH";
regionname[Region::Val_DiLep]         = "Tll";
regionname[Region::CR_QCD17_1Boost]  = "Q1";
regionname[Region::CR_Top17_1Boost]  = "T1";
regionname[Region::CR_W17_1Boost]    = "W1";
regionname[Region::CR_QCD17_2Boost]  = "Q2";
regionname[Region::CR_Top17_2Boost]  = "T2";
regionname[Region::CR_W17_2Boost]    = "W2";
regionname[Region::CoCR_QCD17_1Boost]  = "Q1";
regionname[Region::CoCR_Top17_1Boost]  = "T1";
regionname[Region::CoCR_W17_1Boost]    = "W1";
regionname[Region::CoCR_QCD17_2Boost]  = "Q2";
regionname[Region::CoCR_Top17_2Boost]  = "T2";
regionname[Region::CoCR_W17_2Boost]    = "W2";
regionname[Region::CR_LTop17_1Boost] = "T4Z1";
regionname[Region::CR_L17_1Boost]    = "W4Z1";
regionname[Region::CR_LTop17_2Boost] = "T4Z2";
regionname[Region::CR_L17_2Boost]    = "W4Z2";
regionname[Region::Val_NonIso_RMT]    = "lowM_{T}";
regionname[Region::Val_NonIso_RdPhi]  = "lowd#phi^{*}";
regionname[Region::CR_NonIso_RMTdPhi]= "Non isoLep with revert MT, dPhi*";
regionname[Region::CR_NonIso_0b_RMTdPhi]= "WnI";
regionname[Region::CR_NonIso_b_RMTdPhi]= "TnI";
regionname[Region::CR_1PhoInv]       = "G";
regionname[Region::CR_1LepInv]       = "1 lepton invisible CR";
regionname[Region::CR_1LepInv_LepTrig] = "1 lepton invisible CR (leptonic trigger)";
regionname[Region::CR_2LepInv]       = "DY";
regionname[Region::CR_Fake]          = "Fake tag CR";
regionname[Region::CR_Fake_MET500]   = "Fake tag CR";
regionname[Region::CR_Fake_R2]       = "Fake tag CR";
regionname[Region::Val_Signal_V]     = "V tagged Signal-like validation region";
regionname[Region::Val_Signal_Top]   = "Top tagged Signal-like validation region";
regionname[Region::Val_Signal_H]     = "H tagged Signal-like validation region";
regionname[Region::Val_Signal]       = "S'";
regionname[Region::Val_Signal_LostLep] ="Lost lepton calculation region";
regionname[Region::Val_QCD]          = "Q'";
regionname[Region::Val_Signal_L_V]   = "V tagged Signal-like validation region";
regionname[Region::Val_Signal_L_Top] = "Top tagged Signal-like validation region";
regionname[Region::Val_Signal_L_H]   = "H tagged Signal-like validation region";
regionname[Region::Val_Signal_L]     = "S'";
regionname[Region::Val_QCD_L]        = "Q'";
regionname[Region::Val_Lep]          = "Leptonic validation region";
regionname[Region::Val_Lep_0b]       = "Leptonic 0b validation region";
regionname[Region::Val_Lep_b]        = "Leptonic b validation region";
regionname[Region::Pre_Had]          = "Hadronic preselection";
regionname[Region::SR_Had_1htop]     = "had 1htop SR";
regionname[Region::SR_Had_2htop]     = "Had 2htop SR";
regionname[Region::SR_Had_V_b_45j]   = "Had V b 4-5 jet SR";
regionname[Region::SR_Had_V_b_6j]    = "Had V b 6+ jet SR";
regionname[Region::SR_Had_1V_0b_34j] = "Had 1V 0b 3-4 jet SR";
regionname[Region::SR_Had_1V_0b_5j]  = "Had 1V 0b 5+ jet SR";
regionname[Region::SR_Had_2V_0b_24j] = "Had 2V 0b 2-4 jet SR";
regionname[Region::SR_Had_2V_0b_5j]  = "Had 2V 0b 5+ jet SR";
regionname[Region::SR_Had_H_b_45j]   = "Had H b 4-5 jet SR";
regionname[Region::SR_Had_H_b_6j]    = "Had H b 6 jet SR";
regionname[Region::SR_Had_HV_b_6j]   = "Had HV b 6 jet SR";
regionname[Region::SR_Had_H_0b_34j] = "Had H 0b 3-4 jet SR";
regionname[Region::SR_Had_H_0b_5j]  = "Had H 0b 5+ jet SR";
regionname[Region::SR_Had_HV_0b_24j] = "Had HV 0b 2-4 jet SR";
regionname[Region::SR_Had_HV_0b_5j]  = "Had HV 0b 5+ jet SR";
regionname[Region::Pre_Lep]          = "Isolated lepton preselection";
regionname[Region::SR_Lep_1htop]     = "Lep 1htop SR";
regionname[Region::SR_Lep_V_b]       = "Lep V b SR";
regionname[Region::SR_Lep_V_0b]      = "Lep V 0b SR";
regionname[Region::SR_Lep_H_b]       = "Lep H b 3+ jet SR";
regionname[Region::SR_Lep_H_0b]      = "Lep H 0b 2+ jet SR";
regionname[Region::Pre_NonIso]       = "Non-iso. lepton preselection";
regionname[Region::SR_Leptop_0htop]  = "Leptop 0htop SR";
regionname[Region::SR_Leptop_1htop]  = "Leptop 1htop SR";
regionname[Region::SR_Lepjet_0V_24j] = "Lepjet 0V 2-4 jet SR";
regionname[Region::SR_Lepjet_0V_5j]  = "Lepjet 0V 5+ jet  SR";
regionname[Region::SR_Lepjet_1V_24j] = "Lepjet 1V 2-4 jet SR";
regionname[Region::SR_Lepjet_1V_5j]  = "Lepjet 1V 5+ jet  SR";
if (debug) std::cout<<"PlottingBase::define_histo_settings: region names ok"<<std::endl;

// Cut Postfixes
sh.AddNewPostfix("BaselineCuts", [] { return 0; }, "BaselineCuts", "Baseline cuts", Black);
all_cuts.push_back("BaselineCuts");
for (const auto& region : magic_enum::enum_entries<Region>()) {
	std::string cutflow_str = "";
	std::string name(region.second);
	if (debug>1) std::cout<<"PlottingBase::define_histo_settings: "<<region.first<<" ("<<name<<") start"<<std::endl;
	sh.AddNewPostfix(name, [region,&evt_sel] { return evt_sel.apply_all_cuts(region.first) ? 0 : (size_t)-1; },
			name, regionname[region.first], Black);
	if (debug>1) std::cout<<"PlottingBase::define_histo_settings: "<<region.first<<" ("<<name<<") all cuts ok"<<std::endl;
	for (size_t i=0, n=evt_sel.analysis_cuts[region.first].size(); i<n; ++i) {
		// Cuts in order 1-N: "PassNCuts[search region]"
		if (debug>1) std::cout<<"PlottingBase::define_histo_settings: "<<i<<" start"<<std::endl;
		sh.AddNewPostfix(name+"_"+std::to_string(i+1)+"Cuts", [i,region,&evt_sel] { return evt_sel.apply_ncut(region.first, i) ? 0 : (size_t)-1; },
				name+"_"+std::to_string(i+1)+"Cuts", name+" region, first "+std::to_string(i+1)+" cuts", Black);
		all_cuts.push_back(name+"_"+std::to_string(i+1)+"Cuts");
		if (debug>1) std::cout<<"PlottingBase::define_histo_settings: "<<i<<" n cuts ok"<<std::endl;
		cutflow_str += evt_sel.analysis_cuts[region.first][i].name+name+";";
		// N-1 Cuts: "[search region]_Excl[cut]"
		sh.AddNewPostfix(name+"_Excl"+evt_sel.analysis_cuts[region.first][i].name, [i,region,&evt_sel] { 
				unsigned int mask = (1<<evt_sel.analysis_cuts[region.first].size())-1 - (1<<i); 
				return ((evt_sel.cutbits[region.first] & mask) == mask) ? 0 : (size_t)-1; }, 
				//name+"_Excl"+evt_sel.analysis_cuts[region.first][i].name, regionname[region.first]+", no "+
				//legname[evt_sel.analysis_cuts[region.first][i].name]+" cut", Black);
			name+"_Excl"+evt_sel.analysis_cuts[region.first][i].name, regionname[region.first], Black);
		if (debug>1) std::cout<<"PlottingBase::define_histo_settings: "<<i<<" N-1 cuts ok"<<std::endl;
		// N-2 Cuts: "[search region]_Excl[cut1][cut2]"
		for (size_t j=i+1, n=evt_sel.analysis_cuts[region.first].size(); j<n; ++j)
			sh.AddNewPostfix(name+"_Excl"+evt_sel.analysis_cuts[region.first][i].name+evt_sel.analysis_cuts[region.first][j].name, [i,j,region,&evt_sel] { 
					unsigned int mask = (1<<evt_sel.analysis_cuts[region.first].size())-1 - (1<<i) - (1<<j); 
					return ((evt_sel.cutbits[region.first] & mask) == mask) ? 0 : (size_t)-1; }, 
					name+"_Excl"+evt_sel.analysis_cuts[region.first][i].name+evt_sel.analysis_cuts[region.first][j].name, 
					regionname[region.first]+", no "+legname[evt_sel.analysis_cuts[region.first][i].name]+", "+
					legname[evt_sel.analysis_cuts[region.first][j].name]+" cut", Black);
		if (debug>1) std::cout<<"PlottingBase::define_histo_settings: "<<i<<" N-2 cuts ok"<<std::endl;
		// N-3 Cuts: "[search region]_Excl[cut1][cut2][cut3]"
		for (size_t j=i+1, n=evt_sel.analysis_cuts[region.first].size(); j<n; ++j)
			for (size_t k=j+1; k<n; ++k)
				sh.AddNewPostfix(name+"_Excl"+evt_sel.analysis_cuts[region.first][i].name+
						evt_sel.analysis_cuts[region.first][j].name+evt_sel.analysis_cuts[region.first][k].name, 
						[i,j,k,region,&evt_sel] { 
						unsigned int mask = (1<<evt_sel.analysis_cuts[region.first].size())-1 - (1<<i) - (1<<j) - (1<<k); 
						return ((evt_sel.cutbits[region.first] & mask) == mask) ? 0 : (size_t)-1; }, 
						name+"_Excl"+evt_sel.analysis_cuts[region.first][i].name+
						evt_sel.analysis_cuts[region.first][j].name+evt_sel.analysis_cuts[region.first][k].name, 
						regionname[region.first]+", no "+legname[evt_sel.analysis_cuts[region.first][i].name]+", "+
						legname[evt_sel.analysis_cuts[region.first][j].name]+", "+legname[evt_sel.analysis_cuts[region.first][k].name]+" cut", Black);
		if (debug>1) std::cout<<"PlottingBase::define_histo_settings: "<<i<<" N-3 cuts ok"<<std::endl;
	}
	// Stackable Cut Histos: "CutFlow"
	sh.AddNewPostfix("CutFlow"+name, [region,&evt_sel] { 
			for (size_t i=0, n=evt_sel.analysis_cuts[region.first].size(); i<n; ++i) 
			if (!evt_sel.analysis_cuts[region.first][i].func()) return i; 
			return evt_sel.analysis_cuts[region.first].size();
			}, cutflow_str+"PassAll"+name, cutflow_str+regionname[region.first], col10+col10);
	if (debug>1) std::cout<<"PlottingBase::define_histo_settings: "<<region.first<<" ("<<name<<") end"<<std::endl<<std::endl;
}
sh.AddNewPostfix("Baseline",       [&evt_sel] { return evt_sel.apply_cut(Region::Pre, 0) ? 0 : (size_t)-1; }, "Baseline",      "Baseline selection",               Black);
sh.AddNewPostfix("BaselineNoR2",   [&evt_sel] { return evt_sel.apply_cut(Region::Pre, 0) ? 0 : (size_t)-1; }, "BaselineNoR2",  "Baseline selection, No R^{2} cut", Black);
sh.AddNewPostfix("BaselineInvR2",  [&evt_sel] { return evt_sel.apply_cut(Region::Pre, 0) ? 0 : (size_t)-1; }, "BaselineInvR2", "Baseline selection, Inv. R^{2} cut", Black);
if (debug) std::cout<<"PlottingBase::define_histo_settings: regions ok"<<std::endl<<std::endl;


// ------------------------- Objects -----------------------

// Lepton Postfixes
// Photon Postfixes
sh.AddNewPostfix("SIEIE",          [this] {  return v.Photon().sieie < (v.Photon().isScEtaEB ?  0.01015 : 0.0272); }, "FailSIEIE;PassSIEIE", "Fail #sigma_{i#eta i#eta};Pass #sigma_{i#eta i#eta}", Red+Green);
sh.AddNewPostfix("CHIso",          [this] {  return v.Photon().pfRelIso03_chg < (v.Photon().isScEtaEB ? 0.441 : 0.442); }, "FailCHIso;PassCHIso", "Fail ch. iso.;Pass ch. iso.", Red+Green);
sh.AddNewPostfix("EB",             [this] {  return (size_t)(v.Photon().isScEtaEB ? 0 : -1); }, "Barrel", "Barrel", Black);
sh.AddNewPostfix("EE",             [this] {  return (size_t)(v.Photon().isScEtaEE ? 0 : -1); }, "Endcap", "Endcap", Black);
sh.AddNewPostfix("EB_EE",          [this] {  return v.Photon().isScEtaEE; }, "Barrel;Endcap", "Barrel;Endcap", "601,418");
sh.AddNewPostfix("Fake",           [this] {  return (size_t)(v.Photon().matchGenFake ? 0 : -1); }, "Fake", "Fake", Black);
sh.AddNewPostfix("Prompt",         [this] {  return (size_t)(v.Photon().matchGenPrompt ? 0 : -1); }, "Prompt", "Prompt", Black);
if (debug) std::cout<<"PlottingBase::define_histo_settings: photon pfs ok"<<std::endl<<std::endl;

// AK4 Jet Postfixes
sh.AddNewPostfix("Jets",    [this] { size_t i=v.Jet.Jet.viSel[v.Jet.i];        return (i<4)?i:(size_t)-1; }, "Jet[1to5]",  "1st Jet;2nd Jet;3rd Jet;[4to5]th Jet", col5_red_to_green);
sh.AddNewPostfix("BTags",   [this] { size_t i=v.Jet.MediumBTag.viSel[v.Jet.i]; return (i<4)?i:(size_t)-1; }, "BTag[1to5]", "1st b;2nd b;3rd b;[4to5]th b",         col5_red_to_green);
sh.AddNewPostfix("JetPhotonDR0.05", [this] {  return v.Jet().phoDR<0.05 ? (size_t)0 : (size_t)-1; }, "PhotonDR0p05",  "DR_{#gamma}<0.05", Black);
sh.AddNewPostfix("JetPhotonDR0.4",  [this] {  return v.Jet().phoDR<0.4  ? (size_t)0 : (size_t)-1; }, "PhotonDR0p4",   "DR_{#gamma}<0.4",  Black);
sh.AddNewPostfix("JetEleDR0.05",    [this] {  return v.Jet().eleDR<0.05 ? (size_t)0 : (size_t)-1; }, "EleDR0p05",     "DR_{ele}<0.05", Black);
sh.AddNewPostfix("JetEleDR0.4",     [this] {  return v.Jet().eleDR<0.4  ? (size_t)0 : (size_t)-1; }, "EleDR0p4",      "DR_{ele}<0.4",  Black);
sh.AddNewPostfix("JetMuonDR0.05",   [this] {  return v.Jet().muDR<0.05 ? (size_t)0 : (size_t)-1; },  "MuonDR0p05",    "DR_{muon}<0.05", Black);
sh.AddNewPostfix("JetMuonDR0.4",    [this] {  return v.Jet().muDR<0.4  ? (size_t)0 : (size_t)-1; },  "MuonDR0p4",     "DR_{muon}<0.4",  Black);
if (debug) std::cout<<"PlottingBase::define_histo_settings: AK4 pfs ok"<<std::endl<<std::endl;

// AK8 Jet Postfixes
sh.AddNewPostfix("JetsAK8",  [this] {  size_t i=v.FatJet.JetAK8.viSel[v.FatJet.i]; return (i<4)?i:(size_t)-1; }, "Jet[1to4]",     "1st Jet;2nd Jet;3rd Jet;4th Jet",                     col4_red_to_cyan);
sh.AddNewPostfix("JetAK8PhotonDR0.05", [this] {  return v.FatJet().phoDR<0.05 ? (size_t)0 : (size_t)-1; }, "PhotonDR0p05","DR_{#gamma}<0.05", Black);
sh.AddNewPostfix("JetAK8PhotonDR0.8",  [this] {  return v.FatJet().phoDR<0.8  ? (size_t)0 : (size_t)-1; }, "PhotonDR0p8", "DR_{#gamma}<0.8",  Black);
sh.AddNewPostfix("JetAK8EleDR0.05",    [this] {  return v.FatJet().eleDR<0.05 ? (size_t)0 : (size_t)-1; }, "EleDR0p05",   "DR_{ele}<0.05", Black);
sh.AddNewPostfix("JetAK8EleDR0.8",     [this] {  return v.FatJet().eleDR<0.8  ? (size_t)0 : (size_t)-1; }, "EleDR0p8",    "DR_{ele}<0.8",  Black);
sh.AddNewPostfix("JetAK8MuonDR0.05",   [this] {  return v.FatJet().muDR<0.05 ? (size_t)0 : (size_t)-1; },  "MuonDR0p05",  "DR_{muon}<0.05", Black);
sh.AddNewPostfix("JetAK8MuonDR0.8",    [this] {  return v.FatJet().muDR<0.8  ? (size_t)0 : (size_t)-1; },  "MuonDR0p8",   "DR_{muon}<0.8",  Black);
sh.AddNewPostfix("Jet1AK8Pt450",       [this] {  return v.FatJet.JetAK8(0).pt>450 ? 0 : (size_t)-1; }, "Jet1AK8_Pt450",  "1st jet p_{T} (AK8) > 450", Black);
sh.AddNewPostfix("Jet1AK8Pt500",       [this] {  return v.FatJet.JetAK8(0).pt>500 ? 0 : (size_t)-1; }, "Jet1AK8_Pt500",  "1st jet p_{T} (AK8) > 500", Black);
sh.AddNewPostfix("Jet1AK8Mass65",      [this] {  return v.FatJet.JetAK8(0).msoftdrop>65 ? 0 : (size_t)-1; }, "Jet1AK8_Mass65", "1st jet m_{SD} (AK8) > 65", Black);
sh.AddNewPostfix("Tau21Tagged",        [this] {  return v.FatJet().tau21<HADW_TAU21_TIGHT_CUT; }, "Tau21AntiTag;Tau21Tag", "#tau_{2}/#tau_{1} anti-tagged;#tau_{2}/#tau_{1} tagged", Red+Green);
sh.AddNewPostfix("Tau32Tagged",        [this] {  return v.FatJet().tau32<HADTOP_TAU32_CUT;     }, "Tau32AntiTag;Tau32Tag", "#tau_{3}/#tau_{2} anti-tagged;#tau_{3}/#tau_{2} tagged", Red+Green);
sh.AddNewPostfix("LepJetNoIso",        [this] {  return v.FatJet.LepJetNoIso.pass[v.FatJet.i] ? 0 : (size_t)-1;     }, "LepJetNoIso",          "Lep. jet (no iso.)",              Black);
sh.AddNewPostfix("LepJetNoPt",         [this] {  return v.FatJet.LepJetNoPt.pass[v.FatJet.i] ? 0 : (size_t)-1;      }, "LepJetNoPt",           "Lep. jet (no p_{T})",             Black);
sh.AddNewPostfix("LepJetCand",         [this] {  return v.FatJet.LepJetCand.pass[v.FatJet.i] ? 0 : (size_t)-1;      }, "LepJetCand",           "Lep. jet (no mass)",              Black);
sh.AddNewPostfix("LepJet",             [this] {  return v.FatJet.LepJet.pass[v.FatJet.i] ? 0 : (size_t)-1;          }, "LepJet",               "Lep. jet",                        Black);
sh.AddNewPostfix("LepTopNoIso",        [this] {  return v.FatJet.LepTopNoIso.pass[v.FatJet.i] ? 0 : (size_t)-1;     }, "LepTopNoIso",          "Lep. top (no iso.)",              Black);
sh.AddNewPostfix("LepTopNoPt",         [this] {  return v.FatJet.LepTopNoPt.pass[v.FatJet.i] ? 0 : (size_t)-1;      }, "LepTopNoPt",           "Lep. top (no p_{T})",             Black);
sh.AddNewPostfix("LepTopNoMass",       [this] {  return v.FatJet.LepTopNoMass.pass[v.FatJet.i]  ? 0 : (size_t)-1;   }, "LepTopNoMass",         "Lep. top (no mass)",              Black);
sh.AddNewPostfix("LepTopNoSubJetB",    [this] {  return v.FatJet.LepTopNoSubJetB.pass[v.FatJet.i] ? 0 : (size_t)-1; }, "LepTopNoSubJetB",      "Lep. top (no b)",                 Black);
sh.AddNewPostfix("LepTop",             [this] {  return v.FatJet.LepTop.pass[v.FatJet.i] ? 0 : (size_t)-1;          }, "LepTop",               "Lep. top",                        Black);
sh.AddNewPostfix("LepJetHighMass",     [this] {  return v.FatJet.LepJetHighMass.pass[v.FatJet.i] ? 0 : (size_t)-1;  }, "LepJetHighMass",       "Massive lep. jet",                Black);
sh.AddNewPostfix("LepTopHighMass",     [this] {  return v.FatJet.LepTopHighMass.pass[v.FatJet.i] ? 0 : (size_t)-1;  }, "LepTopHighMass",       "Massive lep. top",                Black);
sh.AddNewPostfix("AK8_EB_EE",          [this] {  return std::abs(v.FatJet().eta)>=1.5; }, "Barrel;Endcap", "Barrel;Endcap", "601,418");
sh.AddNewPostfix("MatchGenHadW",       [this] {  return v.FatJet().matchGenHadW;       }, "NoMatchGenHadW;MatchGenHadW",     "Mistag Ws;Gen-matched Ws",     "601,418");
sh.AddNewPostfix("MatchGenHadZ",       [this] {  return v.FatJet().matchGenHadZ;       }, "NoMatchGenHadZ;MatchGenHadZ",     "Mistag Zs;Gen-matched Zs",     "601,418");
sh.AddNewPostfix("MatchGenHadTop",     [this] {  return v.FatJet().matchGenHadTop;     }, "NoMatchGenHadTop;MatchGenHadTop", "Mistag tops;Gen-matched tops", "601,418");
sh.AddNewPostfix("MatchGenLepTop",     [this] {  return v.FatJet().matchGenLepTop;     }, "NoMatchGenLepTop;MatchGenLepTop", "Mistag tops;Gen-matched tops", "601,418");
sh.AddNewPostfix("MatchedGenLeptonMother", [this] { 
		if (!v.FatJet().matchGenLepton) return (size_t)-1;
		if      (v.FatJet().matchedGenLeptonMotherID==6)  return (size_t)0;
		else if (v.FatJet().matchedGenLeptonMotherID==23) return (size_t)1;
		else if (v.FatJet().matchedGenLeptonMotherID==24) return (size_t)2;
		return (size_t)3;
		}, "MatchGenLepTop;MatchGenLepZ;MatchGenLepW;Other", "Lepton from top;Lepton from Z;Lepton from W;Other", col4_red_to_cyan);
sh.AddNewPostfix("NoMatchGenHadW",     [this] { return (size_t)(!v.FatJet().matchGenHadW   ?  0 : -1); }, "MistagW", "", Black);
sh.AddNewPostfix("NoMatchGenHadZ",     [this] { return (size_t)(!v.FatJet().matchGenHadZ   ?  0 : -1); }, "MistagZ", "", Black);
sh.AddNewPostfix("NoMatchGenHadTop",   [this] { return (size_t)(!v.FatJet().matchGenHadTop ?  0 : -1); }, "MistagTop", "", Black);
sh.AddNewPostfix("MatchGenEleFromTop", [this] { return v.Electron().matchGenEleFromTop;                }, "NoMatchGenEleFromTop;MatchGenEleFromTop", "Misid. e;Gen-matched e", "601,418");
sh.AddNewPostfix("MatchGenMuFromTop",  [this] { return v.Muon().matchGenMuFromTop;                     }, "NoMatchGenMuFromTop;MatchGenMuFromTop",   "Misid. #mu;Gen-matched #mu", "601,418");
//sh.AddNewPostfix("MatchGenTauFromTop", [this] { return v.Tau().matchGenTauFromTop;                     }, "NoMatchGenTauFromTop;MatchGenFromTop",    "Misid. #mu;Gen-matched #mu", "601,418");
if (debug) std::cout<<"PlottingBase::define_histo_settings: AK8 pfs ok"<<std::endl<<std::endl;

// gen Postfixes
sh.AddNewPostfix("GenMatchedAK8_EB_EE",    [this] { return (size_t)(v.GenPart().iMatchedAK8==(size_t)-1 ? -1 : std::abs(v.FatJet(v.GenPart().iMatchedAK8).eta)>=1.5); }, "Barrel;Endcap", "Barrel;Endcap", "601,418");
sh.AddNewPostfix("LostLeptonFlavour", [this] {
		int id = std::abs(v.GenPart().pdgId);
		if (id==11) return (size_t)0;
		if (id==13) return (size_t)1;
		if (id==15) return (size_t)2;
		return (size_t)-1;
		}, "GenEle;GenMu;GenTau", "Electron;Muon;Tau", "417,601,633");
sh.AddNewPostfix("GenLeptonFlavour", [this] {
		int id = std::abs(v.GenPart().pdgId);
		if (id==11) return (size_t)0;
		if (id==13) return (size_t)1;
		if (id==15) return (size_t)2;
		return (size_t)-1;
		}, "GenEle;GenMu;GenTau", "Electron;Muon;Tau", "417,601,633");
sh.AddNewPostfix("GenTopLeptonFlavour", [this] {
		size_t iLep = v.GenPart().iGenLepGrandDaughter;
		if (iLep==(size_t)-1) return (size_t)-1;
		int id = std::abs(v.GenPart(iLep).pdgId);
		if      (id==11) return (size_t)0;
		else if (id==13) return (size_t)1;
		else if (id==15) return (size_t)2;
		return (size_t)-1;
		}, "GenEle;GenMu;GenTau", "Electron;Muon;Tau", "417,601,633");
sh.AddNewPostfix("GenWLeptonFlavour", [this] {
		size_t iLep = v.GenPart().iGenLepDaughter;
		if (iLep==(size_t)-1) return (size_t)-1;
		int id = std::abs(v.GenPart(iLep).pdgId);
		if      (id==11) return (size_t)0;
		else if (id==13) return (size_t)1;
		else if (id==15) return (size_t)2;
		return (size_t)-1;
		}, "GenEle;GenMu;GenTau", "Electron;Muon;Tau", "417,601,633");
sh.AddNewPostfix("GenLepMother", [this] {
		if     (!v.GenPart.Lepton.pass[v.GenPart.i]) return (size_t)-1;
		if      (v.GenPart.LeptonFromTop.pass[v.GenPart.i]) return (size_t)2;
		else if (v.GenPart.LeptonFromW.pass[v.GenPart.i]) return (size_t)1;
		else return (size_t)0;
		}, "Other;FromW;FromTop", "Other;from W decay;from top decay", Red+Green);
if (debug) std::cout<<"PlottingBase::define_histo_settings: gen pfs ok"<<std::endl<<std::endl;

// --------------------- Event Variables -------------------

sh.AddNewPostfix("OtherNonisoLep", [this] { return std::min(v.nLepVetoNoIso-v.nLepSelect,(size_t)1); }, "NoOtherNonisoLep;OtherNonisoLep", "0 other unisol. lepton;#geq1 other unisol. lepton", Green+Red);
sh.AddNewPostfix("OtherLooseLep",  [this] { return std::min(v.nLepVeto     -v.nLepSelect,(size_t)1); }, "NoOtherLep;OtherLep",           "0 other loose lepton;#geq1 other loose lepton", Red+Green);
sh.AddNewPostfix("Ele_Muon",       [this] { return (size_t)(v.Electron.Veto.n==1 ? 0 : v.Muon.Veto.n==1 ? 1 : -1); }, "1VetoEle;1MuVeto", "1e (veto);1#mu (veto)", "1,2");
sh.AddNewPostfix("Ele_or_Muon",    [this] { return (size_t)(v.Electron.Select.n==1 ? 0 : v.Muon.Select.n==1 ? 1 : -1); }, "EleOnly;MuOnly", "1e;1#mu", "1,2");
sh.AddNewPostfix("0Lep",           [this] { return (size_t)(v.Electron.Select.n+v.Muon.Select.n==1 ? 0 : -1); }, "1Lep",  "1 lep",  Black);
sh.AddNewPostfix("Lep",            [this] { return (size_t)((v.nLepVeto+v.Tau.Veto.n)==0 ? 0 : v.Electron.Select.n+v.Muon.Select.n==1 ? 1 : -1); }, "0Lep;1Lep",  "0 lep;1 lep",  Black+Red);
sh.AddNewPostfix("Tau",            [this] { return (size_t)(v.Tau.Veto.n==0 ? 0 : v.Tau.Veto.n==1 ? 1 : -1); }, "0Tau;1Tau",  "0 #tau;1 #tau",  Black+Red);
sh.AddNewPostfix("1Ele",           [this] { return (size_t)(v.Electron.Select.n==1 ? 0 : -1); }, "1Ele",  "1e",  Black);
sh.AddNewPostfix("1Muon",          [this] { return (size_t)(v.Muon.Select.n==1 ?  0 : -1); }, "1Muon", "1#mu", Black);
sh.AddNewPostfix("Pho",            [this] { return (size_t)(v.Photon.Select.n==0 ? 0 : v.Photon.Select.n==1 ? 1 : -1); }, "0Pho;1Pho",  "0#gamma;1#gamma",  Black+Red);
sh.AddNewPostfix("1Pho",           [this] { return (size_t)(v.Photon.Select.n==1 ? 0 : -1); }, "1Pho",  "1#gamma",  Black);
sh.AddNewPostfix("1Fake",          [this] { return (size_t)(v.Photon.Fake.n==1 ? 0 : -1); }, "1FakePho",  "1#gamma",  Black);
sh.AddNewPostfix("1PrePho",        [this] { return (size_t)(v.Photon.PreSelect.n==1 ? 0 : -1); }, "1PrePho",  "1 pre-#gamma",  Black);
sh.AddNewPostfix("FakePhoton",     [this] { return (size_t)(v.Photon.Fake.pass[v.Photon.i] ? 0 : -1); }, "FakePhoton",  "Fake #gamma",  Black);
sh.AddNewPostfix("PromptPhoton",   [this] { return (size_t)(v.Photon.SelectNoIso.pass[v.Photon.i]&&v.Photon().matchGenPrompt ? 0 : -1); }, "PromptPhoton",  "Prompt #gamma",  Black);
sh.AddNewPostfix("SelectNoIsoPhoton", [this] { return (size_t)(v.Photon.SelectNoIso.pass[v.Photon.i] ? 0 : -1); }, "PhotonNoIso",  "#gamma (no iso.)",  Black);
sh.AddNewPostfix("2Ele_2Muon",     [this] { return (size_t)(v.Electron.Select.n==2 ? 0 : v.Muon.Select.n==2 ? 1 : -1); }, "2Ele;2Mu", "2e;2#mu", "1,2");
sh.AddNewPostfix("DiLep",          [this] { return (size_t)((v.Electron.Veto.n+v.Muon.Veto.n)!=2 ? -1 : v.Electron.Veto.n==2 ? 0 : v.Muon.Veto.n==2 ? 1 :  2); }, "2Ele;2Mu;1Ele1Mu", "2e;2#mu;1e+1#mu", Red+Blue+Purple);
sh.AddNewPostfix("NMassTag",       [this] { return (size_t)(v.FatJet.JetAK8Mass.n==1 ? 0 : 1); }, "1MassTag;2MassTag", "1 mass-tag;#geq2 mass-tag", "1,2");
//sh.AddNewPostfix("PromptDirect",   [this] { return (size_t)(v.Photon.Select.n==1 ? (v.Photon.Select(0).matchGenPromptDirect ? 0 : -1) : -1); }, "PromptDirect", "Prompt, direct", Black);
sh.AddNewPostfix("PromptDirect",   [this] { return (size_t)(v.Photon.PreSelect.n==1 ? (v.Photon().matchGenPromptDirect||v.Photon().matchGenPromptFrag ? 0 : -1) : -1); }, "PromptDirect", "Prompt, direct", Black);
sh.AddNewPostfix("1Pho_EB_EE",     [this] { return (size_t)(v.Photon.Select.n==1 ? v.Photon.Select(0).isScEtaEE : -1); }, "Barrel;Endcap", "Barrel;Endcap", "601,418");
sh.AddNewPostfix("1PrePho_EB_EE",  [this] { return (size_t)(v.Photon.PreSelect.n==1 ? v.Photon.PreSelect(0).isScEtaEE : -1); }, "Barrel;Endcap", "Barrel;Endcap", "601,418");
sh.AddNewPostfix("FailedJet",      [this] { return (size_t)(v.Jet.FailID.n>0); }, "NoFailedJet;FailedJet",  "0 bad jet;#geq1 bad jet",  Black+Red);
sh.AddNewPostfix("BadMuonJet",     [this] { return (size_t)(v.dPhiMuonJetMET>=2.74159); }, "NoBadMuonJet;BadMuonJet",  "0 bad #mu jet;#geq1 bad #mu jet",  Black+Red);
sh.AddNewPostfix("BadPFMET2",      [this] { return (size_t)(v.CaloMET_pt>0 ? v.MET_pt/v.CaloMET_pt>=2 : -1); }, "GoodPFMET2;BadPFMET2",  "PFMET/CaloMET<2;PFMET/CaloMET#geq2",  Black+Red);
sh.AddNewPostfix("BadPFMET3",      [this] { return (size_t)(v.CaloMET_pt>0 ? v.MET_pt/v.CaloMET_pt>=3 : -1); }, "GoodPFMET3;BadPFMET3",  "PFMET/CaloMET<3;PFMET/CaloMET#geq3",  Black+Red);
sh.AddNewPostfix("BadPFMET5",      [this] { return (size_t)(v.CaloMET_pt>0 ? v.MET_pt/v.CaloMET_pt>=5 : -1); }, "GoodPFMET5;BadPFMET5",  "PFMET/CaloMET<5;PFMET/CaloMET#geq5",  Black+Red);
sh.AddNewPostfix("NJet35",         [this] { return (size_t)(v.Jet.Jet.n<3 ? -1 : v.Jet.Jet.n>5); }, "NJet3to5;NJet6", "3#leqN_{jet}#leq5;6#leqN_{jet}", "1,2");
sh.AddNewPostfix("NJet46",         [this] { return (size_t)(v.Jet.Jet.n<4 ? -1 : v.Jet.Jet.n>6); }, "NJet4to6;NJet7", "4#leqN_{jet}#leq6;7#leqN_{jet}", "1,2");
sh.AddNewPostfix("NJet45",         [this] { return (size_t)(v.Jet.Jet.n==4||v.Jet.Jet.n==5 ? 0 : 1 ); }, "NJet4to5;NJet6", "4#leqN_{jet}#leq5;6#leqN_{jet}", "1,2");
sh.AddNewPostfix("NJetNoPho35",    [this] { return (size_t)(v.Jet.JetNoPho.n<3 ? -1 : v.Jet.JetNoPho.n>5); }, "NJet3to5;NJet6", "3#leqN_{jet}#leq5;6#leqN_{jet}", "1,2");
sh.AddNewPostfix("NJetNoPho46",    [this] { return (size_t)(v.Jet.JetNoPho.n<4 ? -1 : v.Jet.JetNoPho.n>6); }, "NJet4to6;NJet7", "4#leqN_{jet}#leq6;7#leqN_{jet}", "1,2");
sh.AddNewPostfix("NJetNoPho45",    [this] { return (size_t)(v.Jet.JetNoPho.n==4||v.Jet.JetNoPho.n==5 ? 0 : 1 ); }, "NJet4to5;NJet6", "4#leqN_{jet}#leq5;6#leqN_{jet}", "1,2");
sh.AddNewPostfix("MR800",          [this] { return (size_t)(v.MR>=800 ? 0 : -1); }, "MR800", "M_{R}#geq800", Black);
sh.AddNewPostfix("R2Bins",         [this] { return (size_t)((v.R2>=0.08)+(v.R2>=0.12)+(v.R2>=0.16)+(v.R2>=0.24)+(v.R2>=0.4)); }, 
		"R2_0to0p08;R2_0p08to0p12;R2_0p12to0p16;R2_0p16to0p24;R2_0p24to0p5;R2_0p5", 
		"R^{2}#in[0,0.08[;R^{2}#in[0.08,0.12[;R^{2}#in[0.12,0.16[;R^{2}#in[0.16,0.24[;R^{2}#in[0.24,0.4[;R^{2}#in[0.4,2[", col6_rainbow_dark);
sh.AddNewPostfix("MTBoost800",     [this] {  return (size_t)(v.MT_boost>=800 ? 0 : -1); }, "MTBoost800", "m_{T,Boost+MET}#geq800", Black);

sh.AddNewPostfix("Nb",             [this] {  return (size_t)(v.Jet.LooseBTag.n==0 ? 0 : v.Jet.MediumBTag.n>=1 ? 1: -1); },      "bveto;bincl",       "0b;#geq1b",               col4_cyan_to_red);
sh.AddNewPostfix("Nisob",          [this] {  return (size_t)(v.Jet.LooseIsoBTag.n==0 ? 0 : v.Jet.MediumIsoBTag.n>=1 ? 1: -1); },"isobveto;isobincl", "0b (iso.);#geq1b (iso.)", col4_cyan_to_red);
sh.AddNewPostfix("2b",             [this] {  return (size_t)(v.Jet.MediumBTag.n == 2 ? 0 : -1);          }, "2b",               "2b",                      col4_cyan_to_red);
sh.AddNewPostfix("NW1",            [this] {  return (size_t)(v.FatJet.W1.n         < 3 ? v.FatJet.W1.n         : -1); }, "[0to2]W1",         "[0to2]W Loose",           col4_cyan_to_red);
sh.AddNewPostfix("NW2",            [this] {  return (size_t)(v.FatJet.W2.n         < 3 ? v.FatJet.W2.n         : -1); }, "[0to2]W2",         "[0to2]W Medium",          col4_cyan_to_red);
sh.AddNewPostfix("NW3",            [this] {  return (size_t)(v.FatJet.W3.n         < 3 ? v.FatJet.W3.n         : -1); }, "[0to2]W3",         "[0to2]W Tight",           col4_cyan_to_red);
sh.AddNewPostfix("NWDeep1",        [this] {  return (size_t)(v.FatJet.WDeep1.n     < 3 ? v.FatJet.WDeep1.n     : -1); }, "[0to2]WDeep1",     "[0to2]W (Deep 5%)",       col4_cyan_to_red);
sh.AddNewPostfix("NWDeep2",        [this] {  return (size_t)(v.FatJet.WDeep2.n     < 3 ? v.FatJet.WDeep2.n     : -1); }, "[0to2]WDeep2",     "[0to2]W (Deep 1%)",       col4_cyan_to_red);
sh.AddNewPostfix("NWDeep3",        [this] {  return (size_t)(v.FatJet.WDeep3.n     < 3 ? v.FatJet.WDeep3.n     : -1); }, "[0to2]WDeep3",     "[0to2]W (Deep 0.5%)",     col4_cyan_to_red);
sh.AddNewPostfix("NWDeepMD1",      [this] {  return (size_t)(v.FatJet.WDeepMD1.n   < 3 ? v.FatJet.WDeepMD1.n   : -1); }, "[0to2]WDeepMD1",   "[0to2]W (DeepMD 5%)",     col4_cyan_to_red);
sh.AddNewPostfix("NWDeepMD2",      [this] {  return (size_t)(v.FatJet.WDeepMD2.n   < 3 ? v.FatJet.WDeepMD2.n   : -1); }, "[0to2]WDeepMD2",   "[0to2]W (DeepMD 1%)",     col4_cyan_to_red);
sh.AddNewPostfix("NWDeepMD3",      [this] {  return (size_t)(v.FatJet.WDeepMD3.n   < 3 ? v.FatJet.WDeepMD3.n   : -1); }, "[0to2]WDeepMD3",   "[0to2]W (DeepMD 0.5%)",   col4_cyan_to_red);
sh.AddNewPostfix("NZDeep1",        [this] {  return (size_t)(v.FatJet.ZDeep1.n     < 3 ? v.FatJet.ZDeep1.n     : -1); }, "[0to2]ZDeep1",     "[0to2]Z (Deep 0.8)",      col4_cyan_to_red);
sh.AddNewPostfix("NZDeep2",        [this] {  return (size_t)(v.FatJet.ZDeep2.n     < 3 ? v.FatJet.ZDeep2.n     : -1); }, "[0to2]ZDeep2",     "[0to2]Z (Deep 0.95)",     col4_cyan_to_red);
sh.AddNewPostfix("NZDeep3",        [this] {  return (size_t)(v.FatJet.ZDeep3.n     < 3 ? v.FatJet.ZDeep3.n     : -1); }, "[0to2]ZDeep3",     "[0to2]Z (Deep 0.99)",     col4_cyan_to_red);
sh.AddNewPostfix("NZDeepMD1",      [this] {  return (size_t)(v.FatJet.ZDeepMD1.n   < 3 ? v.FatJet.ZDeepMD1.n   : -1); }, "[0to2]ZDeepMD1",   "[0to2]Z (DeepMD 0.3)",    col4_cyan_to_red);
sh.AddNewPostfix("NZDeepMD2",      [this] {  return (size_t)(v.FatJet.ZDeepMD2.n   < 3 ? v.FatJet.ZDeepMD2.n   : -1); }, "[0to2]ZDeepMD2",   "[0to2]Z (DeepMD 0.8)",    col4_cyan_to_red);
sh.AddNewPostfix("NZDeepMD3",      [this] {  return (size_t)(v.FatJet.ZDeepMD3.n   < 3 ? v.FatJet.ZDeepMD3.n   : -1); }, "[0to2]ZDeepMD3",   "[0to2]Z (DeepMD 0.9)",    col4_cyan_to_red);
sh.AddNewPostfix("NVDeep1",        [this] {  return (size_t)(v.FatJet.VDeep1.n     < 3 ? v.FatJet.VDeep1.n     : -1); }, "[0to2]VDeep1",     "[0to2]V (Deep L)",        col4_cyan_to_red);
sh.AddNewPostfix("NVDeep2",        [this] {  return (size_t)(v.FatJet.VDeep2.n     < 3 ? v.FatJet.VDeep2.n     : -1); }, "[0to2]VDeep2",     "[0to2]V (Deep M)",        col4_cyan_to_red);
sh.AddNewPostfix("NVDeep3",        [this] {  return (size_t)(v.FatJet.VDeep3.n     < 3 ? v.FatJet.VDeep3.n     : -1); }, "[0to2]VDeep3",     "[0to2]V (Deep T)",        col4_cyan_to_red);
sh.AddNewPostfix("NTop1",          [this] {  return (size_t)(v.FatJet.Top1.n       < 3 ? v.FatJet.Top1.n       : -1); }, "[0to2]Top1",       "[0to2]Top VLoose",        col4_cyan_to_red);
sh.AddNewPostfix("NTop2",          [this] {  return (size_t)(v.FatJet.Top2.n       < 3 ? v.FatJet.Top2.n       : -1); }, "[0to2]Top2",       "[0to2]Top Loose",         col4_cyan_to_red);
sh.AddNewPostfix("NTop3",          [this] {  return (size_t)(v.FatJet.Top3.n       < 3 ? v.FatJet.Top3.n       : -1); }, "[0to2]Top3",       "[0to2]Top Medium",        col4_cyan_to_red);
sh.AddNewPostfix("NTop4",          [this] {  return (size_t)(v.FatJet.Top4.n       < 3 ? v.FatJet.Top4.n       : -1); }, "[0to2]Top4",       "[0to2]Top Tight",         col4_cyan_to_red);
sh.AddNewPostfix("NTop5",          [this] {  return (size_t)(v.FatJet.Top5.n       < 3 ? v.FatJet.Top5.n       : -1); }, "[0to2]Top5",       "[0to2]Top VTight",        col4_cyan_to_red);
sh.AddNewPostfix("NTopDeep1",      [this] {  return (size_t)(v.FatJet.TopDeep1.n   < 3 ? v.FatJet.TopDeep1.n   : -1); }, "[0to2]TopDeep1",   "[0to2]Top (Deep 5%)",     col4_cyan_to_red);
sh.AddNewPostfix("NTopDeep2",      [this] {  return (size_t)(v.FatJet.TopDeep2.n   < 3 ? v.FatJet.TopDeep2.n   : -1); }, "[0to2]TopDeep2",   "[0to2]Top (Deep 1%)",     col4_cyan_to_red);
sh.AddNewPostfix("NTopDeep3",      [this] {  return (size_t)(v.FatJet.TopDeep3.n   < 3 ? v.FatJet.TopDeep3.n   : -1); }, "[0to2]TopDeep3",   "[0to2]Top (Deep 0.5%)",   col4_cyan_to_red);
sh.AddNewPostfix("NTopDeep4",      [this] {  return (size_t)(v.FatJet.TopDeep4.n   < 3 ? v.FatJet.TopDeep4.n   : -1); }, "[0to2]TopDeep4",   "[0to2]Top (Deep 0.1%)",   col4_cyan_to_red);
sh.AddNewPostfix("NTopDeepMD1",    [this] {  return (size_t)(v.FatJet.TopDeepMD1.n < 3 ? v.FatJet.TopDeepMD1.n : -1); }, "[0to2]TopDeepMD1", "[0to2]Top (DeepMD 5%)",   col4_cyan_to_red);
sh.AddNewPostfix("NTopDeepMD2",    [this] {  return (size_t)(v.FatJet.TopDeepMD2.n < 3 ? v.FatJet.TopDeepMD2.n : -1); }, "[0to2]TopDeepMD2", "[0to2]Top (DeepMD 1%)",   col4_cyan_to_red);
sh.AddNewPostfix("NTopDeepMD3",    [this] {  return (size_t)(v.FatJet.TopDeepMD3.n < 3 ? v.FatJet.TopDeepMD3.n : -1); }, "[0to2]TopDeepMD3", "[0to2]Top (DeepMD 0.5%)", col4_cyan_to_red);
sh.AddNewPostfix("NTopDeepMD4",    [this] {  return (size_t)(v.FatJet.TopDeepMD4.n < 3 ? v.FatJet.TopDeepMD4.n : -1); }, "[0to2]TopDeepMD4", "[0to2]Top (DeepMD 0.1%)", col4_cyan_to_red);
sh.AddNewPostfix("NVDeep1_Nisob",     [this] {
		size_t i = -1;
		if (v.FatJet.VDeep1.n == 0) i=0;
		else if (v.FatJet.VDeep1.n==1&&v.Jet.LooseIsoBTag.n==0) i=1;
		else if (v.FatJet.VDeep1.n==1&&v.Jet.MediumIsoBTag.n>0) i=2;
		else if (v.FatJet.VDeep1.n==2&&v.Jet.LooseIsoBTag.n==0) i=3;
		else if (v.FatJet.VDeep1.n==2&&v.Jet.MediumIsoBTag.n>0) i=4;
		return i;
		}, "0VDeep1;1VDeep1_isobveto;1VDeep1_isobincl;2VDeep1_isobveto;2VDeep1_isobincl", "0W/Z (Deep);1W/Z (Deep), 0b (iso.);1W/Z (Deep), #geq1b (iso.);2W/Z (Deep 0.8), 0b (iso.);2W/Z (Deep), #geq1b (iso.)", col5_green_to_red);
sh.AddNewPostfix("NVDeep2_Nisob",     [this] {
		size_t i = -1;
		if (v.FatJet.VDeep2.n == 0) i=0;
		else if (v.FatJet.VDeep2.n==1&&v.Jet.LooseIsoBTag.n==0) i=1;
		else if (v.FatJet.VDeep2.n==1&&v.Jet.MediumIsoBTag.n>0) i=2;
		else if (v.FatJet.VDeep2.n==2&&v.Jet.LooseIsoBTag.n==0) i=3;
		else if (v.FatJet.VDeep2.n==2&&v.Jet.MediumIsoBTag.n>0) i=4;
		return i;
		}, "0VDeep2;1VDeep2_isobveto;1VDeep2_isobincl;2VDeep2_isobveto;2VDeep2_isobincl", "0W/Z (Deep);1W/Z (Deep), 0b (iso.);1W/Z (Deep), #geq1b (iso.);2W/Z (Deep 0.8), 0b (iso.);2W/Z (Deep), #geq1b (iso.)", col5_green_to_red);
sh.AddNewPostfix("Nisob_NJet24",     [this] {
		if (v.Jet.Jet.n>=2&&v.Jet.Jet.n<=4) {
		if      (v.Jet.LooseIsoBTag.n==0) return (size_t)0;
		else if (v.Jet.MediumIsoBTag.n>0) return (size_t)1;
		}
		return (size_t)-1;
		}, "isobveto_NJet24;isobincl_NJet24", "0b (iso.), 2-4 jet;#geq1b (iso.), 2-4 jet", Black);
sh.AddNewPostfix("NLepJetCand",     [this] {  return (size_t)(v.FatJet.LepJetCand.n     < 3 ? v.FatJet.LepJetCand.n     : -1); }, "[0to2]LepJetCand",     "[0to2]Lep. jet cand.",      col4_cyan_to_red);
sh.AddNewPostfix("NLepJet",         [this] {  return (size_t)(v.FatJet.LepJet.n         < 3 ? v.FatJet.LepJet.n         : -1); }, "[0to2]LepJet",         "[0to2]Lep. jet",            col4_cyan_to_red);
sh.AddNewPostfix("NLepTop",         [this] {  return (size_t)(v.FatJet.LepTop.n         < 3 ? v.FatJet.LepTop.n         : -1); }, "[0to2]LepTop",         "[0to2]Lep. top",            col4_cyan_to_red);
sh.AddNewPostfix("NLepJetHighMass", [this] {  return (size_t)(v.FatJet.LepJetHighMass.n < 3 ? v.FatJet.LepJetHighMass.n : -1); }, "[0to2]LepJetHighMass", "[0to2]Massive lep. jet",    col4_cyan_to_red);
sh.AddNewPostfix("NLepTopHighMass", [this] {  return (size_t)(v.FatJet.LepTopHighMass.n < 3 ? v.FatJet.LepTopHighMass.n : -1); }, "[0to2]LepTopHighMass", "[0to2]Massive lep. top",    col4_cyan_to_red);
sh.AddNewPostfix("NHadTop",         [this] {  return (size_t)(v.FatJet.HadTop.n         < 3 ? v.FatJet.HadTop.n         : -1); }, "[0to2]HadTop",         "[0to2]Had. top (Deep 1%)",  col4_cyan_to_red);
sh.AddNewPostfix("NHadW",           [this] {  return (size_t)(v.FatJet.HadW.n           < 3 ? v.FatJet.HadW.n           : -1); }, "[0to2]HadW",           "[0to2]Had. W (Deep 1%)",    col4_cyan_to_red);
if (debug) std::cout<<"PlottingBase::define_histo_settings: evt pfs ok"<<std::endl<<std::endl;


// -------------------------- Other ------------------------

// Systematics Postfixes
sh.AddNewPostfix("Syst", [&syst_index] { return syst_index; }, std::string(";syst[1to")+std::to_string(syst_nSyst)+"]", std::string(";systematics [1to")+std::to_string(syst_nSyst)+"]", "1-999");
if (syst_nSyst>998) error("Error: Too large number of systematics, define more colors!");
// Weights
//sh.AddNewPostfix("NoPUWeight",     [] { return 0; }, "NoPUWeight",   "No pile-up reweighting", Black);
//sh.AddNewPostfix("NoTrigWeight",   [] { return 0; }, "NoTrigWeight", "No trigger weighting",   Black);
//sh.AddNewPostfix("NoEleSF",        [] { return 0; }, "NoEleSF",      "No ele SF",              Black);
//sh.AddNewPostfix("NoMuonSF",       [] { return 0; }, "NoMuonSF",     "No muon SF",             Black);
//sh.AddNewPostfix("NoBTagSF",       [] { return 0; }, "NoBTagSF",     "No b-tag SF",            Black);
//sh.AddNewPostfix("NoWTagSF",       [] { return 0; }, "NoWTagSF",     "No W-tag SF",            Black);
//sh.AddNewPostfix("NoTopTagSF",     [] { return 0; }, "NoTopTagSF",   "No top-tag SF",          Black);
//sh.AddNewPostfix("NoWeight",       [] { return 0; }, "NoWeight",     "",                       Black);
if (debug) std::cout<<"PlottingBase::define_histo_settings: all postfixes ok"<<std::endl;


// --------------------------------------------------------------------
//                          Binning
// --------------------------------------------------------------------

// Bins
E     = {0, 100, 200, 400, 600, 800, 1000, 1500, 2000, 10000};
//Pt    = {0, 100, 150, 200, 250, 300, 350, 400, 450, 500, 550, 600, 650, 700, 800, 900,       1200, 2000, 10000};
Pt    = {0, 100, 150, 200,      300,      400,      500,      600,           800,                  2000, 10000};
M3    = {0, 50, 75, 100, 150, 200, 250, 800};
//PtG   = {0, 100, 150, 200, 250, 300, 350, 400,      500,                700,           1000,       2000, 10000};
PtG   = {0, 100, 150, 200,      300,      400,                600,           800,                  2000, 10000};
//PtF   = {0,           200,      300,      400, 450, 500, 550, 600,      700,           1000,       2000, 10000};
PtF   = {0,           200,      300,      400,                600,                     1000,       2000, 10000};
PtO   = {0,                                                                                              10000};
PtT   = {0,                                         500,                                                 10000};
PtPho = {0, 100, 120, 140, 160, 180, 200, 225, 250, 300, 500, 1000, 4000};
PtPho2 = {0, 100, 120, 140, 160, 180, 200, 225, 250, 300, 4000};
for (double x=   0; x< 100; x+= 10) PtFine.push_back(x);
for (double x= 100; x< 500; x+= 20) PtFine.push_back(x);  
for (double x= 500; x<1000; x+= 50) PtFine.push_back(x);  
for (double x=1000; x<2000; x+=100) PtFine.push_back(x);  
for (double x=2000; x<5000; x+=500) PtFine.push_back(x);
M   = {0, 10, 20, 30, 40, 50, 65, 75, 85, 95, 105, 120, 135, 150, 165, 180, 195, 210, 230, 260, 300, 500, 1000};
for (double x=   0; x< 120; x+=  5) MFine.push_back(x);
for (double x= 120; x< 220; x+= 10) MFine.push_back(x);
for (double x= 220; x< 300; x+= 20) MFine.push_back(x);  
for (double x= 300; x< 500; x+= 50) MFine.push_back(x);  
for (double x= 500; x<1000; x+=100) MFine.push_back(x);  
for (double x=1000; x<5000; x+=500) MFine.push_back(x);  
MW  = {65, 75, 85, 95, 105};
DeepB = {0, 0.05, 0.2, 0.4, 0.6, 0.7, 0.8, 0.9, 0.95, 1.0 };
for (double x=0.0; x< 1.8; x+=0.1) MDP.push_back(x);
for (double x=1.8; x< 2.4; x+=0.2) MDP.push_back(x);
for (double x=2.4; x<=3.2; x+=0.4) MDP.push_back(x);
for (double x=0.0; x<1.6; x+=0.4) DP.push_back(x);
for (double x=1.6; x<2.4; x+=0.2) DP.push_back(x);
for (double x=2.4; x<3.2; x+=0.1) DP.push_back(x);
for (double x=  0; x< 250; x+=10) M2.push_back(x);
for (double x=250; x< 500; x+=25) M2.push_back(x);
for (double x=500; x<1000; x+=50) M2.push_back(x);
NVTX.push_back(0);
for (double x=6;  x<  40;  x+=2) NVTX.push_back(x);
for (double x=40; x<=100;  x+=5) NVTX.push_back(x);
R_bins   = {0, 0.05, 0.1, 0.15, 0.2, 0.25, 0.3, 0.35, 0.4, 0.6, 0.7, 0.8, 1.0, 1.2, 2.0 };
MR_bins  = {0, 700, 800, 1000, 1200, 1600, 2000, 4000, 10000};
MTR_bins = {0, 100, 200, 300, 400, 600, 800, 1000, 1200, 1600, 2000, 4000};
//MET = {0,     100,                     200,      300, 400, 500, 600, 700, 800, 1000, 1500, 2000};
MET = {0, 80, 100, 120, 140, 160, 180, 200, 250, 300, 400, 500, 600, 700, 800, 1000, 1500, 2000};
R2_bins  = {0, 0.04, 0.08, 0.12, 0.16, 0.24, 0.4, 1.5};
HT = {0, 200, 300, 400, 500, 600, 650, 700, 750, 800, 850, 900, 950, 1000, 1100, 1200, 1500, 2000, 2500, 3000, 4000, 10000};
HTB = {400, 500, 600, 700, 750, 800, 850, 900, 950, 1000, 1500, 10000}; // 2D Trigger Eff
PtB = {200, 300, 400, 450, 500, 550, 600, 1000, 10000}; // 2D Trigger Eff
LepPt  = { 0, 5, 10, 15, 20, 30, 40, 50, 60, 80, 100, 120, 150, 200, 250, 300, 400, 500, 4000};
//   LepEta = { 0.0, 0.5, 1.0, 1.5, 2.0, 2.5 };
LepEta = { 0.0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0, 1.1, 1.2, 1.3, 1.4, 1.5, 1.6, 1.7, 1.8, 1.9, 2.0, 2.1, 2.2, 2.3, 2.4, 2.5 };
// Razor inclusive binning
MR_RI = {300, 400, 500, 600, 700, 900, 1200, 4000};
R2_RI = {0.15, 0.2, 0.25, 0.3, 0.41, 0.52, 1.5};
// Unrolled bin labels
MR_2D_bins      = {0.8, 1.0, 1.2, 1.6, 2.0, 4.0};
MR_2D_bins_lep  = {0.7, 0.8, 1.0, 1.2, 1.6, 2.0, 4.0};
MRR2_2D_bins    = {0, 200, 400, 600, 800, 5000};
R2_2D_bins      = {0.08, 0.12, 0.16, 0.24, 0.4, 1.5};
HT_2D_bins_old  = {0.4, 0.5, 0.6, 0.7, 0.75, 0.8, 0.85, 0.9, 0.95, 1.0, 1.2, 1.5, 10.0};
Pt_2D_bins      = {200, 300, 400, 450, 500, 550, 600, 700, 1000, 5000};
PtLow_2D_bins   = {200, 300, 400, 450, 500};
PtHigh_2D_bins  = {550, 600, 700, 1000, 5000};
PtPho_2D_bins   = {0, 120, 200, 300, 400, 500, 800, 5000};
ElePt_2D_bins   = {10, 15, 20, 30, 35, 40, 50, 100, 125, 250, 2000};
MuPt_2D_bins    = {10, 15, 20, 25, 30, 35, 40,  50,  60, 100, 250, 2000};
HT_2D_bins_lep  = {200, 300, 400, 500, 600, 10000};
HT1_2D_bins_lep = {200, 300, 400, 500};
HT2_2D_bins_lep = {500, 600, 10000};
// HT/MET Trigger turnons
// HT:   0  500   700   800  1050
// MHT:  0   75    85   100   120
// MET:  0  100   115   136   158
// rat:    1.33  1.35  1.36  1.32
//HT_2D_bins  = {0, 400, 500, 600, 700, 800, 1000, 1200, 1500, 5000}; // 2D Trigger Eff Run2017-18
HT_2D_bins  = {200,  450,  600,  700, 800, 900, 1000, 1200, 10000}; // 2D Trigger Eff Run2017-18
HT1_2D_bins = {200,  450,  600}; // 2D Trigger Eff Run2017-18
HT2_2D_bins = {600,  700,  800,  900}; // 2D Trigger Eff Run2017-18
HT3_2D_bins = {900, 1000, 1200, 10000}; // 2D Trigger Eff Run2017-18
MET_2D_bins = {0, 100, 130, 160, 180, 200, 250, 300, 400, 4000}; // 2D Trigger Eff Run2017-18
// HT,MET Changgi {300, 500, 550, 600, 800, 1500, 10000}, {50, 150, 200, 400, 10000}, {}, 0, 0);
// unrolled bin mergin
merged_razor_bins = {19,23,24};
merged_razor_bins_lep = {24,28,29};
merged_trigger_bins  = {1,3,5,  11,   20, 37,44,  46,52,53, 55,57,59,61,62, 64,65,66,67,68,69,70,71};
merged_trigger1_bins = {1,3,5,  11                                                                 };
merged_trigger2_bins = {               2, 19,26,  28,34,35                                         };
merged_trigger3_bins = {                                    10,12,14,16,17, 19,20,21,22,23,24,25,26};


MRR2_2D_bins_new    = {0, 100, 200, 300, 400, 500, 3000};

// ------------------- Binning with Postfix ----------------

std::stringstream HT_pf, HT_leg;
for (size_t i=0, n=HTB.size(); i<n-1; ++i) {
	HT_pf<<"HT"<<HTB[i]<<"to"<<HTB[i+1];
	HT_leg<<"H_{T} #subset ["<<HTB[i]<<","<<HTB[i+1]<<"[";
	if (i!=n-2) { HT_pf<<";"; HT_leg<<";"; }
}
sh.AddNewPostfix("HTBins", [this] { for (size_t i=0, n=HTB.size(); i<n-1; ++i) if (v.AK4_Ht>=HTB[i]&&v.AK4_Ht<HTB[i+1]) return i; return (size_t)-1; },
		HT_pf.str(), HT_leg.str(), col12+col12);
std::stringstream AK8Pt_pf, AK8Pt_leg;
for (size_t i=0, n=PtB.size(); i<n-1; ++i) {
	AK8Pt_pf<<"Jet1AK8Pt"<<PtB[i]<<"to"<<PtB[i+1];
	AK8Pt_leg<<"AK8 jet1 p_{T} #subset ["<<PtB[i]<<","<<PtB[i+1]<<"[";
	if (i!=n-2) { AK8Pt_pf<<";"; AK8Pt_leg<<";"; }
}
sh.AddNewPostfix("Jet1AK8PtBins", [this] { if (v.FatJet.JetAK8.n<1) return (size_t)-1;
		for (size_t i=0, n=PtB.size(); i<n-1; ++i) if (v.FatJet.JetAK8(0).pt>=PtB[i]&&v.FatJet.JetAK8(0).pt<PtB[i+1]) return i; 
		return (size_t)-1; }, AK8Pt_pf.str(), AK8Pt_leg.str(), col16);


// --------------------------------------------------------------------
//                         Fill Parameters
// --------------------------------------------------------------------

// Define the filling parameters: bins, variable to fill, default plotting range etc.
// Usage:
// AddNewFillParams("Name of fill param", { .nbin= int(number of bins), .bins={vector of bin edges} OR {min,max}, .fill=lambda function which returns the value you want to fill, .axis_title="title and (unit)", .def_range={min,max range to draw}});

sh.AddNewFillParams("Bin", { .nbin=1,   .bins={0,1}, .fill=[] { return 0; }, .axis_title="Bin", .def_range={0,1}}); // Just one bin for averages/counts

// ------------------------- Leptons -----------------------

// Veto Leptons
sh.AddNewFillParams("VetoElePt",       { .nbin=LepPt.size()-1, .bins=LepPt,   .fill=[this] { return v.Electron().pt;                  }, .axis_title="Loose Electron p_{T} (GeV)", .def_range={0,500}});
sh.AddNewFillParams("VetoEleEta",      { .nbin=LepEta.size()-1, .bins=LepEta, .fill=[this] { return std::abs(v.Electron().eta);                 }, .axis_title="Loose Electron |#eta|",  .def_range={-2.5,2.5}});
sh.AddNewFillParams("VetoMuPt",        { .nbin=LepPt.size()-1, .bins=LepPt,   .fill=[this] { return v.Muon().pt;                    }, .axis_title="Loose Muon p_{T} (GeV)",     .def_range={0,500}});
sh.AddNewFillParams("VetoMuEta",       { .nbin=LepEta.size()-1, .bins=LepEta, .fill=[this] { return std::abs(v.Muon().eta);                   }, .axis_title="Loose Muon |#eta|",      .def_range={-2.4,2.4}});
sh.AddNewFillParams("VetoTauPt",       { .nbin=LepPt.size()-1, .bins=LepPt,   .fill=[this] { return v.Tau().pt;                  }, .axis_title="Loose Tau p_{T} (GeV)",     .def_range={0,500}});
sh.AddNewFillParams("VetoTauEta",      { .nbin=LepEta.size()-1, .bins=LepEta, .fill=[this] { return std::abs(v.Tau().eta);                 }, .axis_title="Loose Tau |#eta|",      .def_range={-2.6,2.6}});

// Selected Leptons
// Electrons
sh.AddNewFillParams("ElePt",           { .nbin=LepPt.size()-1, .bins=LepPt,  .fill=[this] { return v.Electron.Select.n<1 ? -9999 : v.Electron.Select(0).pt;  }, .axis_title="Electron p_{T} (GeV)", .def_range={ELE_SELECT_PT_CUT,500}});
sh.AddNewFillParams("EleEta",          { .nbin=LepEta.size()-1, .bins=LepEta,.fill=[this] { return v.Electron.Select.n<1 ? -9999 : std::abs(v.Electron.Select(0).eta); }, .axis_title="Electron |#eta|",  .def_range={-ELE_SELECT_ETA_CUT,ELE_SELECT_ETA_CUT}});
sh.AddNewFillParams("EleJetDR",        { .nbin=  60, .bins={     0,      6}, .fill=[this] { return v.Electron.Select.n<1 ? -9999 : v.Electron.Select(0).jetDR;         }, .axis_title="#DeltaR (ele, jet)",         .def_range={0,4}});
sh.AddNewFillParams("EleJetPt",        { .nbin= 100, .bins={     0,    500}, .fill=[this] { return v.Electron.Select.n<1 ? -9999 : v.Electron.Select(0).iMatchedAK4==(size_t)-1 ? -9999 : v.Jet(v.Electron.Select(0).iMatchedAK4).pt;         }, .axis_title="p_{T, nearest jet to ele}"});
sh.AddNewFillParams("EleJetDPhi",      { .nbin=MDP.size()-1, .bins=MDP,      .fill=[this] { return v.Electron.Select.n<1 ? -9999 : v.Electron.Select(0).jetDPhi;       }, .axis_title="#Delta#phi (ele, jet)"});
sh.AddNewFillParams("Ele1JetDPhi",     { .nbin=MDP.size()-1, .bins=MDP,      .fill=[this] { return v.Electron.Select.n<1 ? -9999 : v.Electron.Select(0).jetDPhi; }, .axis_title="#Delta#phi (1st ele, jet)"});
sh.AddNewFillParams("Ele2JetDPhi",     { .nbin=MDP.size()-1, .bins=MDP,      .fill=[this] { return v.Electron.Select.n<2 ? -9999 : v.Electron.Select(1).jetDPhi; }, .axis_title="#Delta#phi (2nd ele, jet)"});
sh.AddNewFillParams("EleCleanJetDRmin",{ .nbin=  60, .bins={     0,      6}, .fill=[this] { return v.Electron().jetDRmin; }, .axis_title="e, jet #DeltaR_{min}"});
sh.AddNewFillParams("EleCleanJetPtrel",{ .nbin=  40, .bins={     0,    100}, .fill=[this] { return v.Electron().cleanJetPtrel; }, .axis_title="e, cleaned jet p_{T,rel} (GeV)"});
sh.AddNewFillParams("EleTightPt",       { .nbin= 100, .bins={     0,    500}, .fill=[this] { return v.Electron.Tight.n<1 ? -9999 : v.Electron.Tight(0).pt;  }, .axis_title="Electron p_{T} (GeV)", .def_range={ELE_TIGHT_PT_CUT,250}});
sh.AddNewFillParams("EleTightEta",      { .nbin=  40, .bins={    -4,      4}, .fill=[this] { return v.Electron.Tight.n<1 ? -9999 : v.Electron.Tight(0).eta; }, .axis_title="Electron #eta",  .def_range={-ELE_TIGHT_ETA_CUT,ELE_TIGHT_ETA_CUT}});
sh.AddNewFillParams("EleNoIsoPt",       { .nbin= 100, .bins={     0,    500}, .fill=[this] { return v.Electron.NoIso.n<1 ? -9999 : v.Electron.NoIso(0).pt;  }, .axis_title="Electron p_{T} (GeV)", .def_range={ELE_TIGHT_PT_CUT,250}});
sh.AddNewFillParams("EleNoIsoEta",      { .nbin=  40, .bins={    -4,      4}, .fill=[this] { return v.Electron.NoIso.n<1 ? -9999 : v.Electron.NoIso(0).eta; }, .axis_title="Electron #eta",  .def_range={-ELE_TIGHT_ETA_CUT,ELE_TIGHT_ETA_CUT}});
sh.AddNewFillParams("EleNonIsoPt",       { .nbin= 100, .bins={     0,    500}, .fill=[this] { return v.Electron.NonIso.n<1 ? -9999 : v.Electron.NonIso(0).pt;  }, .axis_title="Electron p_{T} (GeV)", .def_range={ELE_TIGHT_PT_CUT,250}});
sh.AddNewFillParams("EleNonIsoEta",      { .nbin=  40, .bins={    -4,      4}, .fill=[this] { return v.Electron.NonIso.n<1 ? -9999 : v.Electron.NonIso(0).eta; }, .axis_title="Electron #eta",  .def_range={-ELE_TIGHT_ETA_CUT,ELE_TIGHT_ETA_CUT}});
// Muons
sh.AddNewFillParams("MuPt",            { .nbin=LepPt.size()-1, .bins=LepPt,   .fill=[this] { return v.Muon.Select.n<1 ? -9999 : v.Muon.Select(0).pt;  }, .axis_title="Muon p_{T} (GeV)", .def_range={MU_SELECT_PT_CUT,500}});
sh.AddNewFillParams("MuEta",           { .nbin=LepEta.size()-1, .bins=LepEta, .fill=[this] { return v.Muon.Select.n<1 ? -9999 : std::abs(v.Muon.Select(0).eta); }, .axis_title="Muon |#eta|",        .def_range={-MU_SELECT_ETA_CUT,MU_SELECT_ETA_CUT}});
sh.AddNewFillParams("MuJetDR",         { .nbin=  60, .bins={     0,      6}, .fill=[this] { return v.Muon.Select.n<1 ? -9999 : v.Muon.Select(0).jetDR;      }, .axis_title="#DeltaR (muon, jet)",        .def_range={0,4}});
sh.AddNewFillParams("MuJetPt",         { .nbin= 100, .bins={     0,    500}, .fill=[this] { return v.Muon.Select.n<1 ? -9999 : v.Muon.Select(0).iMatchedAK4==(size_t)-1 ? -9999 : v.Jet(v.Muon.Select(0).iMatchedAK4).pt;      }, .axis_title="p_{T, nearest jet to muon}"});
sh.AddNewFillParams("MuJetDPhi",       { .nbin=MDP.size()-1, .bins=MDP,      .fill=[this] { return v.Muon.Select.n<1 ? -9999 : v.Muon.Select(0).jetDPhi;    }, .axis_title="#Delta#phi (muon, jet)"});
sh.AddNewFillParams("Mu1JetDPhi",      { .nbin=MDP.size()-1, .bins=MDP,      .fill=[this] { return v.Muon.Select.n<1 ? -9999 : v.Muon.Select(0).jetDPhi; }, .axis_title="#Delta#phi (1st muon, jet)"});
sh.AddNewFillParams("Mu2JetDPhi",      { .nbin=MDP.size()-1, .bins=MDP,      .fill=[this] { return v.Muon.Select.n<2 ? -9999 : v.Muon.Select(1).jetDPhi; }, .axis_title="#Delta#phi (2nd muon, jet)"});
sh.AddNewFillParams("MuCleanJetDRmin",{ .nbin=  60, .bins={     0,      6}, .fill=[this] { return v.Muon().jetDRmin; }, .axis_title="#mu, jet #DeltaR_{min}"});
sh.AddNewFillParams("MuCleanJetPtrel",{ .nbin=  40, .bins={     0,    100}, .fill=[this] { return v.Muon().cleanJetPtrel; }, .axis_title="#mu, cleaned jet p_{T,rel} (GeV)"});
sh.AddNewFillParams("MuTightPt",            { .nbin= 100, .bins={     0,    500}, .fill=[this] { return v.Muon.Tight.n<1 ? -9999 : v.Muon.Tight(0).pt;  }, .axis_title="Muon p_{T} (GeV)", .def_range={MU_TIGHT_PT_CUT,250}});
sh.AddNewFillParams("MuTightEta",           { .nbin=  40, .bins={    -4,      4}, .fill=[this] { return v.Muon.Tight.n<1 ? -9999 : std::abs(v.Muon.Tight(0).eta); }, .axis_title="Muon |#eta|",        .def_range={-MU_TIGHT_ETA_CUT,MU_TIGHT_ETA_CUT}});
sh.AddNewFillParams("MuNoIsoPt",            { .nbin= 100, .bins={     0,    500}, .fill=[this] { return v.Muon.NoIso.n<1 ? -9999 : v.Muon.NoIso(0).pt;  }, .axis_title="Muon p_{T} (GeV)", .def_range={MU_TIGHT_PT_CUT,250}});
sh.AddNewFillParams("MuNoIsoEta",           { .nbin=  40, .bins={    -4,      4}, .fill=[this] { return v.Muon.NoIso.n<1 ? -9999 : std::abs(v.Muon.NoIso(0).eta); }, .axis_title="Muon |#eta|",        .def_range={-MU_TIGHT_ETA_CUT,MU_TIGHT_ETA_CUT}});
sh.AddNewFillParams("MuNonIsoPt",            { .nbin= 100, .bins={     0,    500}, .fill=[this] { return v.Muon.NonIso.n<1 ? -9999 : v.Muon.NonIso(0).pt;  }, .axis_title="Muon p_{T} (GeV)", .def_range={MU_TIGHT_PT_CUT,250}});
sh.AddNewFillParams("MuNonIsoEta",           { .nbin=  40, .bins={    -4,      4}, .fill=[this] { return v.Muon.NonIso.n<1 ? -9999 : std::abs(v.Muon.NonIso(0).eta); }, .axis_title="Muon |#eta|",        .def_range={-MU_TIGHT_ETA_CUT,MU_TIGHT_ETA_CUT}});

// ------------------------- Photons -----------------------

// Photons
sh.AddNewFillParams("PhotonPt",        { .nbin=  25, .bins={     0,   2000}, .fill=[this] { return v.Photon.Select.n==1 ? v.Photon.Select(0).pt  : -9999;  }, .axis_title="Photon p_{T} (GeV)", .def_range={PHOTON_SELECT_PT_CUT,1000}});
sh.AddNewFillParams("PrePhotonPt",     { .nbin=  25, .bins={     0,   2000}, .fill=[this] { return v.Photon.PreSelect.n==1 ? v.Photon.PreSelect(0).pt  : -9999;  }, .axis_title="Preselected #gamma p_{T} (GeV)", .def_range={PHOTON_SELECT_PT_CUT,1000}});
sh.AddNewFillParams("PhotonPtBins",    { .nbin=PtPho.size()-1, .bins=PtPho,  .fill=[this] { return v.Photon.Select.n==1 ? v.Photon.Select(0).pt  : -9999;  }, .axis_title="Photon p_{T} (GeV)", .def_range={0,1000}});
sh.AddNewFillParams("PhotonPtFewBins", { .nbin=PtPho2.size()-1, .bins=PtPho2,  .fill=[this] { return v.Photon.Select.n==1 ? v.Photon.Select(0).pt  : -9999;  }, .axis_title="Photon p_{T} (GeV)", .def_range={0,300}});
sh.AddNewFillParams("PrePhotonPtBins", { .nbin=PtPho.size()-1, .bins=PtPho,  .fill=[this] { return v.Photon.PreSelect.n==1 ? v.Photon.PreSelect(0).pt  : -9999;  }, .axis_title="Preselected #gamma p_{T} (GeV)", .def_range={0,1000}});
sh.AddNewFillParams("PhotonEta",       { .nbin=  40, .bins={    -4,      4}, .fill=[this] { return v.Photon.Select.n==1 ? v.Photon.Select(0).eta : -9999; }, .axis_title="Photon #eta",        .def_range={-PHOTON_SELECT_ETA_CUT,PHOTON_SELECT_PT_CUT}});
sh.AddNewFillParams("PhotonSIEIE",     { .nbin= 100, .bins={     0,    0.1}, .fill=[this] { return v.Photon().sieie;        }, .axis_title="Photon #sigma_{i#eta i#eta}", .def_range={0,0.1}});
sh.AddNewFillParams("PhotonCHIso",     { .nbin=  40, .bins={     0,     20}, .fill=[this] { return v.Photon().pfRelIso03_chg;     }, .axis_title="Photon Charged Isolation (GeV)", .def_range={0,10}});
sh.AddNewFillParams("Photon1Eta",      { .nbin=  25, .bins={  -2.5,    2.5}, .fill=[this] { return v.Photon.Select.n<1 ? -9999 : v.Photon.Select(0).eta; }, .axis_title="Photon #eta"});
sh.AddNewFillParams("PhotonCHIso_preslectphopt",       { .nbin=  40, .bins={     0,     20}, .fill=[this] { return v.Photon().pt*v.Photon().pfRelIso03_chg;     }, .axis_title="Photon Charged Isolation (GeV)", .def_range={0,20}});
sh.AddNewFillParams("PhotonCHIso_preslectphoptREBin",  { .nbin=  10, .bins={0, 0.00001, 1, 1.5, 2, 3, 4, 5, 7, 10, 1000}, .fill=[this] { return v.Photon().pt*v.Photon().pfRelIso03_chg;     }, .axis_title="PhoCHIso_pt (GeV)"});
sh.AddNewFillParams("PhotonCHIso_preslectphoptLog",    { .nbin=  16, .bins={-4, 4}, .fill=[this] { return std::log10(v.Photon().pt*v.Photon().pfRelIso03_chg) ;     }, .axis_title="PhoCHIso_pt (GeV)", .def_range={-4,2}});
sh.AddNewFillParams("PhotonCHIso_preslectphoptLN",     { .nbin=  16, .bins={-8, 8}, .fill=[this] { return std::log(v.Photon().pt*v.Photon().pfRelIso03_chg) ;     }, .axis_title="PhoCHIso_pt (GeV)"});

// --------------------------- Jets ------------------------

// AK4 Jets
sh.AddNewFillParams("JetPtBins",            { .nbin=PtFine.size()-1,.bins=PtFine, .fill=[this] { return v.Jet().pt;           }, .axis_title="Jet p_{T} (GeV)", .def_range={  0,2000} });
sh.AddNewFillParams("JetPtFewBins",         { .nbin=PtF.size()-1,  .bins=PtF,     .fill=[this] { return v.Jet().pt;           }, .axis_title="Jet p_{T} (GeV)", .def_range={200,2000} });
sh.AddNewFillParams("JetPtOneBin",          { .nbin=PtO.size()-1,  .bins=PtO,     .fill=[this] { return v.Jet().pt;           }, .axis_title="Jet p_{T} (GeV)", .def_range={400,2000} });
sh.AddNewFillParams("JetPt",                { .nbin=  80, .bins={     0,   4000}, .fill=[this] { return v.Jet().pt;           }, .axis_title="Jet p_{T} (GeV)", .def_range={0,2000} });
sh.AddNewFillParams("JetEta",               { .nbin=  80, .bins={    -4,      4}, .fill=[this] { return v.Jet().eta;          }, .axis_title="Jet #eta",        .def_range={-2.4,2.4}});
sh.AddNewFillParams("JetPhi",               { .nbin=  16, .bins={-3.142,  3.142}, .fill=[this] { return v.Jet().phi;          }, .axis_title="Jet #phi"});
sh.AddNewFillParams("JetDeepB",             { .nbin=  20, .bins={     0,   1.00}, .fill=[this] { return std::min(v.Jet().btagDeepB,float(0.999)); }, .axis_title="Jet DeepB"});
sh.AddNewFillParams("JetPhotonDR",          { .nbin= 120, .bins={     0,      6}, .fill=[this] { return v.Jet().phoDR;           }, .axis_title="#DeltaR (jet, photon)", .def_range={0,0.8}});
sh.AddNewFillParams("JetPhotonPtRatio",     { .nbin=  40, .bins={     0,      4}, .fill=[this] { return v.Jet().phoPtRatio;      }, .axis_title="p_{T}^{photon}/p_{T}^{jet}", .def_range={0,2}});
sh.AddNewFillParams("JetEleDR",             { .nbin= 120, .bins={     0,      6}, .fill=[this] { return v.Jet().eleDR;           }, .axis_title="#DeltaR (jet, electron)", .def_range={0,0.8}});
sh.AddNewFillParams("JetElePtRatio",        { .nbin=  40, .bins={     0,      4}, .fill=[this] { return v.Jet().elePtRatio;      }, .axis_title="p_{T}^{electron}/p_{T}^{jet}", .def_range={0,2}});
sh.AddNewFillParams("JetMuonDR",            { .nbin= 120, .bins={     0,      6}, .fill=[this] { return v.Jet().muDR;            }, .axis_title="#DeltaR (jet, muon)", .def_range={0,0.8}});
sh.AddNewFillParams("JetMuonPtRatio",       { .nbin=  40, .bins={     0,      4}, .fill=[this] { return v.Jet().muPtRatio;       }, .axis_title="p_{T}^{muon}/p_{T}^{jet}", .def_range={0,2}});
// BJets
sh.AddNewFillParams("BJetPtBins",           { .nbin=PtFine.size()-1,.bins=PtFine, .fill=[this] { return v.Jet().pt;           }, .axis_title="B-jet p_{T} (GeV)", .def_range={0,2000} });
sh.AddNewFillParams("BJetPt",               { .nbin=  80, .bins={     0,   4000}, .fill=[this] { return v.Jet().pt;           }, .axis_title="B-jet p_{T} (GeV)", .def_range={0,2000} });
sh.AddNewFillParams("BJetEta",              { .nbin=  80, .bins={    -4,      4}, .fill=[this] { return v.Jet().eta;          }, .axis_title="B-jet #eta",        .def_range={-2.4,2.4}});
sh.AddNewFillParams("BJetPhi",              { .nbin=  16, .bins={-3.142,  3.142}, .fill=[this] { return v.Jet().phi;          }, .axis_title="B-jet #phi"});
sh.AddNewFillParams("BJetDeepB",              { .nbin=  20, .bins={     0,   1.00}, .fill=[this] { return std::min(v.Jet().btagDeepB,float(0.999)); }, .axis_title="B-jet DeepB"});
// Megajets
sh.AddNewFillParams("MegaJetPt",            { .nbin=  80, .bins={     0,   4000}, .fill=[this] { return v.iMegaJet<v.megajets.size() ? v.megajets[v.iMegaJet].Pt()  : -9999;      }, .axis_title="Megajet p_{T} (GeV)", .def_range={0,2000} });
sh.AddNewFillParams("MegaJetEta",           { .nbin=  80, .bins={    -4,      4}, .fill=[this] { return v.iMegaJet<v.megajets.size() ? v.megajets[v.iMegaJet].Eta() : -9999;     }, .axis_title="Megajet #eta",        .def_range={-2.4,2.4}});
sh.AddNewFillParams("MegaJetPhi",           { .nbin=  16, .bins={-3.142,  3.142}, .fill=[this] { return v.iMegaJet<v.megajets.size() ? v.megajets[v.iMegaJet].Phi() : -9999;     }, .axis_title="Megajet #phi"});

// AK8 Jets
//sh.AddNewFillParams("JetAK8PtOneBin",       { .nbin=   1, .bins={   200,   5000}, .fill=[this] { return v.FatJet().pt;           }, .axis_title="AK8 jet p_{T} (GeV)"});
sh.AddNewFillParams("JetAK8PtOneBin",       { .nbin=PtO.size()-1,  .bins=PtO,     .fill=[this] { return v.FatJet().pt;           }, .axis_title="AK8 Jet p_{T} (GeV)", .def_range={200,2000} });
sh.AddNewFillParams("JetAK8PtTwoBin",       { .nbin=PtT.size()-1,  .bins=PtT,     .fill=[this] { return v.FatJet().pt;           }, .axis_title="AK8 Jet p_{T} (GeV)", .def_range={200,2000} });
sh.AddNewFillParams("JetAK8PtFewBins",      { .nbin=PtF.size()-1, .bins=PtF,      .fill=[this] { return v.FatJet().pt;           }, .axis_title="AK8 jet p_{T} (GeV)", .def_range={200,2000} });
sh.AddNewFillParams("JetAK8PtBins",         { .nbin=Pt.size()-1 , .bins=Pt,       .fill=[this] { return v.FatJet().pt;           }, .axis_title="AK8 jet p_{T} (GeV)", .def_range={200,2000} });
sh.AddNewFillParams("JetAK8Pt",             { .nbin=  80, .bins={     0,   4000}, .fill=[this] { return v.FatJet().pt;           }, .axis_title="AK8 jet p_{T} (GeV)", .def_range={200,2000} });
sh.AddNewFillParams("JetAK8Eta",            { .nbin=  40, .bins={    -4,      4}, .fill=[this] { return v.FatJet().eta;          }, .axis_title="AK8 jet #eta",        .def_range={-2.4,2.4}});
sh.AddNewFillParams("JetAK8Phi",            { .nbin=  16, .bins={-3.142,  3.142}, .fill=[this] { return v.FatJet().phi;          }, .axis_title="AK8 jet #phi"});
sh.AddNewFillParams("JetAK8MassBins",       { .nbin= M3.size()-1, .bins=M3,       .fill=[this] { return v.FatJet().msoftdrop;    }, .axis_title="AK8 jet soft-drop mass (GeV)", .def_range={50,800}});
sh.AddNewFillParams("JetAK8Mass",           { .nbin= M2.size()-1, .bins=M2,       .fill=[this] { return v.FatJet().msoftdrop;    }, .axis_title="AK8 jet soft-drop mass (GeV)", .def_range={0,400}});
sh.AddNewFillParams("JetAK8Tau1",           { .nbin=  50, .bins={     0,      1}, .fill=[this] { return std::min(v.FatJet().tau1, float(0.999));    }, .axis_title="AK8 jet #tau_{1}"});
sh.AddNewFillParams("JetAK8Tau2",           { .nbin=  50, .bins={     0,      1}, .fill=[this] { return std::min(v.FatJet().tau2, float(0.999));    }, .axis_title="AK8 jet #tau_{2}"});
sh.AddNewFillParams("JetAK8Tau3",           { .nbin=  50, .bins={     0,      1}, .fill=[this] { return std::min(v.FatJet().tau3, float(0.999));    }, .axis_title="AK8 jet #tau_{3}"});
sh.AddNewFillParams("JetAK8Index",          { .nbin=  10, .bins={     0,     10}, .fill=[this] { return v.FatJet.JetAK8.viSel[v.FatJet.i];          }, .axis_title="AK8 Jet index", .def_range={0,5} });
sh.AddNewFillParams("MaxAK8SubJetDeepB",    { .nbin=  20, .bins={     0,   1.00}, .fill=[this] { return std::min(v.FatJet().maxSubJetDeepB, double(0.999));      }, .axis_title="Max. AK8 subjet DeepB"});
sh.AddNewFillParams("MaxAK8SubJetDeepBBins",{ .nbin=DeepB.size()-1, .bins=DeepB,      .fill=[this] { return std::min(v.FatJet().maxSubJetDeepB, double(0.999));      }, .axis_title="Max. AK8 subjet DeepB"});
sh.AddNewFillParams("JetAK8Tau21",          { .nbin=  20, .bins={     0,      1}, .fill=[this] { return std::min(v.FatJet().tau21, double(0.999));                       }, .axis_title="AK8 jet #tau_{2}/#tau_{1}"});
sh.AddNewFillParams("JetAK8Tau31",          { .nbin=  20, .bins={     0,      1}, .fill=[this] { return std::min(v.FatJet().tau31, double(0.999));                       }, .axis_title="AK8 jet #tau_{3}/#tau_{1}"});
sh.AddNewFillParams("JetAK8Tau32",          { .nbin=  20, .bins={     0,      1}, .fill=[this] { return std::min(v.FatJet().tau32, double(0.999));                       }, .axis_title="AK8 jet #tau_{3}/#tau_{2}"});
sh.AddNewFillParams("JetAK8DeepTagTvsQCD",    { .nbin=  40, .bins={     0,      2}, .fill=[this] { return v.FatJet().deepTag_TvsQCD;                   }, .axis_title="AK8 jet deepTag TvsQCD", .def_range={0,1}});
sh.AddNewFillParams("JetAK8DeepTagWvsQCD",    { .nbin=  40, .bins={     0,      2}, .fill=[this] { return v.FatJet().deepTag_WvsQCD;                   }, .axis_title="AK8 jet deepTag WvsQCD", .def_range={0,1}});
sh.AddNewFillParams("JetAK8DeepTagZvsQCD",    { .nbin=  40, .bins={     0,      2}, .fill=[this] { return v.FatJet().deepTag_ZvsQCD;                   }, .axis_title="AK8 jet deepTag ZvsQCD", .def_range={0,1}});
sh.AddNewFillParams("JetAK8DeepTagH",         { .nbin=  40, .bins={     0,      2}, .fill=[this] { return v.FatJet().deepTag_H;                        }, .axis_title="AK8 jet deepTag H", .def_range={0,1}});
sh.AddNewFillParams("JetAK8DeepTagMDHbbvsQCD",{ .nbin=  40, .bins={     0,      2}, .fill=[this] { return v.FatJet().deepTagMD_HbbvsQCD;                   }, .axis_title="AK8 jet deepTagMD HbbvsQCD", .def_range={0,1}});
sh.AddNewFillParams("JetAK8DeepTagMDWvsQCD",  { .nbin=  20, .bins={     0,      1}, .fill=[this] { return v.FatJet().deepTagMD_WvsQCD; }, .axis_title="AK8 jet DeepTagMD (W vs. QCD)"});
sh.AddNewFillParams("JetAK8DeepTagMDTvsQCD",  { .nbin=  20, .bins={     0,      1}, .fill=[this] { return v.FatJet().deepTagMD_TvsQCD; }, .axis_title="AK8 jet DeepTagMD (t vs. QCD)"});

sh.AddNewFillParams("JetAK8PhotonDR",       { .nbin= 120, .bins={     0,      6}, .fill=[this] { return v.FatJet().phoDR;           }, .axis_title="#DeltaR (AK8 jet, photon)", .def_range={0,1.6}});
sh.AddNewFillParams("JetAK8PhotonPtRatio",  { .nbin=  40, .bins={     0,      4}, .fill=[this] { return v.FatJet().phoPtRatio;      }, .axis_title="p_{T}^{photon}/p_{T}^{AK8 jet}", .def_range={0,2}});
sh.AddNewFillParams("JetAK8EleDR",          { .nbin= 120, .bins={     0,      6}, .fill=[this] { return v.FatJet().eleDR;              }, .axis_title="#DeltaR (AK8 jet, ele)", .def_range={0,1.6}});
sh.AddNewFillParams("JetAK8ElePtRatio",     { .nbin=  40, .bins={     0,      4}, .fill=[this] { return v.FatJet().elePtRatio;         }, .axis_title="p_{T}^{ele}/p_{T}^{AK8 jet}", .def_range={0,2}});
sh.AddNewFillParams("JetAK8MuonDR",         { .nbin= 120, .bins={     0,      6}, .fill=[this] { return v.FatJet().muDR;             }, .axis_title="#DeltaR (AK8 jet, muon)", .def_range={0,1.6}});
sh.AddNewFillParams("JetAK8MuonPtRatio",    { .nbin=  40, .bins={     0,      4}, .fill=[this] { return v.FatJet().muPtRatio;        }, .axis_title="p_{T}^{muon}/p_{T}^{AK8 jet}", .def_range={0,2}});
// mWs
sh.AddNewFillParams("mWPtBins",        { .nbin=Pt.size()-1 , .bins=Pt,       .fill=[this] { return v.FatJet().pt;           }, .axis_title="Mass-tagged W p_{T} (GeV)", .def_range={0,2000} });
sh.AddNewFillParams("mWPt",            { .nbin= 80, .bins={     0,   4000},  .fill=[this] { return v.FatJet().pt;           }, .axis_title="Mass-tagged W p_{T} (GeV)", .def_range={0,2000} });
sh.AddNewFillParams("mWEta",           { .nbin=  40, .bins={    -4,      4}, .fill=[this] { return v.FatJet().eta;          }, .axis_title="Mass-tagged W #eta",        .def_range={-2.4,2.4}});
sh.AddNewFillParams("mWPhi",           { .nbin=  16, .bins={-3.142,  3.142}, .fill=[this] { return v.FatJet().phi;          }, .axis_title="Mass-tagged W #phi"});
sh.AddNewFillParams("mWTau21",         { .nbin=  20, .bins={     0,      1}, .fill=[this] { return v.FatJet().tau21;                  }, .axis_title="Mass-tagged W #tau_{2}/#tau_{1}"});
sh.AddNewFillParams("mWMass",          { .nbin=M.size()-1, .bins=M,          .fill=[this] { return v.FatJet().msoftdrop;          }, .axis_title="Mass-tagged W m_{Soft-Drop} (GeV)"});
sh.AddNewFillParams("mWDeepTagMDWvsQCD", { .nbin=  20, .bins={     0,      1}, .fill=[this] { return v.FatJet().deepTagMD_WvsQCD; }, .axis_title="Mass-tagged W DeepTagMD (W vs. QCD)"});
// aWs
sh.AddNewFillParams("aWPtBins",        { .nbin=Pt.size()-1 , .bins=Pt,       .fill=[this] { return v.FatJet().pt;           }, .axis_title="Anti-tagged W p_{T} (GeV)", .def_range={0,2000} });
sh.AddNewFillParams("aWPt",            { .nbin=  80, .bins={     0,   4000}, .fill=[this] { return v.FatJet().pt;           }, .axis_title="Anti-tagged W p_{T} (GeV)", .def_range={0,2000} });
sh.AddNewFillParams("aWEta",           { .nbin=  40, .bins={    -4,      4}, .fill=[this] { return v.FatJet().eta;          }, .axis_title="Anti-tagged W #eta",        .def_range={-2.4,2.4}});
sh.AddNewFillParams("aWPhi",           { .nbin=  16, .bins={-3.142,  3.142}, .fill=[this] { return v.FatJet().phi;          }, .axis_title="Anti-tagged W #phi"});
sh.AddNewFillParams("aWTau21",         { .nbin=  20, .bins={     0,      1}, .fill=[this] { return v.FatJet().tau21;                  }, .axis_title="Anti-tagged W #tau_{2}/#tau_{1}"});
sh.AddNewFillParams("aWMass",          { .nbin=M.size()-1, .bins=M,          .fill=[this] { return v.FatJet().msoftdrop;          }, .axis_title="Anti-tagged W m_{Soft-Drop} (GeV)"});
// Ws
sh.AddNewFillParams("WPtBins",         { .nbin=Pt.size()-1, .bins=Pt,        .fill=[this] { return v.FatJet().pt;           }, .axis_title="Tagged W p_{T} (GeV)", .def_range={200,1200} });
sh.AddNewFillParams("WPt",             { .nbin=  80, .bins={     0,   4000}, .fill=[this] { return v.FatJet().pt;           }, .axis_title="Tagged W p_{T} (GeV)", .def_range={200,1200} });
sh.AddNewFillParams("WEta",            { .nbin=  40, .bins={    -4,      4}, .fill=[this] { return v.FatJet().eta;          }, .axis_title="Tagged W #eta",        .def_range={-2.4,2.4}});
sh.AddNewFillParams("WPhi",            { .nbin=  16, .bins={-3.142,  3.142}, .fill=[this] { return v.FatJet().phi;          }, .axis_title="Tagged W #phi"});
sh.AddNewFillParams("WTau21",          { .nbin=  20, .bins={     0,      1}, .fill=[this] { return v.FatJet().tau21;                  }, .axis_title="Tagged W #tau_{2}/#tau_{1}"});
sh.AddNewFillParams("WMass",           { .nbin=M.size()-1, .bins=M,          .fill=[this] { return v.FatJet().msoftdrop;          }, .axis_title="Tagged W m_{Soft-Drop} (GeV)"});
sh.AddNewFillParams("HadWIndex",       { .nbin=  10, .bins={     0,     10}, .fill=[this] { return v.FatJet.HadW.viSel[v.FatJet.i];                 }, .axis_title="W (had.) index", .def_range={0,5} });
// Zs
sh.AddNewFillParams("HadZIndex",       { .nbin=  10, .bins={     0,     10}, .fill=[this] { return v.FatJet.HadZ.viSel[v.FatJet.i];                 }, .axis_title="Z (had.) index", .def_range={0,5} });

// mTops
sh.AddNewFillParams("mTopPtBins",      { .nbin=Pt.size()-1 , .bins=Pt,       .fill=[this] { return v.FatJet().pt;           }, .axis_title="Mass-tagged top p_{T} (GeV)", .def_range={0,2000} });
sh.AddNewFillParams("mTopPt",          { .nbin=  80, .bins={     0,   4000}, .fill=[this] { return v.FatJet().pt;           }, .axis_title="Mass-tagged top p_{T} (GeV)", .def_range={0,2000} });
sh.AddNewFillParams("mTopEta",         { .nbin=  40, .bins={    -4,      4}, .fill=[this] { return v.FatJet().eta;          }, .axis_title="Mass-tagged top #eta",        .def_range={-2.4,2.4}});
sh.AddNewFillParams("mTopPhi",         { .nbin=  16, .bins={-3.142,  3.142}, .fill=[this] { return v.FatJet().phi;          }, .axis_title="Mass-tagged top #phi"});
sh.AddNewFillParams("mTopTau32",       { .nbin=  20, .bins={     0,      1}, .fill=[this] { return v.FatJet().tau32;                  }, .axis_title="Mass-tagged top #tau_{3}/#tau_{2}"});
sh.AddNewFillParams("mTopMass",        { .nbin=M.size()-1, .bins=M,          .fill=[this] { return v.FatJet().msoftdrop;        }, .axis_title="Mass-tagged top m_{Soft-Drop} (GeV)"});
// aTops
sh.AddNewFillParams("aTopPtBins",      { .nbin=Pt.size()-1 , .bins=Pt,       .fill=[this] { return v.FatJet().pt;           }, .axis_title="Anti-tagged top p_{T} (GeV)", .def_range={0,2000} });
sh.AddNewFillParams("aTopPt",          { .nbin=  80, .bins={     0,   4000}, .fill=[this] { return v.FatJet().pt;           }, .axis_title="Anti-tagged top p_{T} (GeV)", .def_range={0,2000} });
sh.AddNewFillParams("aTopEta",         { .nbin=  40, .bins={    -4,      4}, .fill=[this] { return v.FatJet().eta;          }, .axis_title="Anti-tagged top #eta",        .def_range={-2.4,2.4}});
sh.AddNewFillParams("aTopPhi",         { .nbin=  16, .bins={-3.142,  3.142}, .fill=[this] { return v.FatJet().phi;          }, .axis_title="Anti-tagged top #phi"});
sh.AddNewFillParams("aTopTau32",       { .nbin=  20, .bins={     0,      1}, .fill=[this] { return v.FatJet().tau32;                  }, .axis_title="Anti-tagged top #tau_{3}/#tau_{2}"});
sh.AddNewFillParams("aTopMass",        { .nbin=M.size()-1, .bins=M,          .fill=[this] { return v.FatJet().msoftdrop;        }, .axis_title="Anti-tagged top m_{Soft-Drop} (GeV)"});
// Tops
sh.AddNewFillParams("TopPtBins",       { .nbin=Pt.size()-1, .bins=Pt,        .fill=[this] { return v.FatJet().pt;           }, .axis_title="Tagged top p_{T} (GeV)", .def_range={400,1200} });
sh.AddNewFillParams("TopPt",           { .nbin=  80, .bins={     0,   4000}, .fill=[this] { return v.FatJet().pt;           }, .axis_title="Tagged top p_{T} (GeV)", .def_range={400,1200} });
sh.AddNewFillParams("TopEta",          { .nbin=  40, .bins={    -4,      4}, .fill=[this] { return v.FatJet().eta;          }, .axis_title="Tagged top #eta",        .def_range={-2.4,2.4}});
sh.AddNewFillParams("TopPhi",          { .nbin=  16, .bins={-3.142,  3.142}, .fill=[this] { return v.FatJet().phi;          }, .axis_title="Tagged top #phi"});
sh.AddNewFillParams("TopTau32",        { .nbin=  20, .bins={     0,      1}, .fill=[this] { return v.FatJet().tau32;                  }, .axis_title="Tagged top #tau_{3}/#tau_{2}"});
sh.AddNewFillParams("TopMass",         { .nbin=M.size()-1, .bins=M,          .fill=[this] { return v.FatJet().msoftdrop;        }, .axis_title="Tagged top m_{Soft-Drop} (GeV)"});
sh.AddNewFillParams("HadTopIndex",     { .nbin=  10, .bins={     0,     10}, .fill=[this] { return v.FatJet.HadTop.viSel[v.FatJet.i]; }, .axis_title="Top (had.) index", .def_range={0,5} });
sh.AddNewFillParams("LepTopIndex",     { .nbin=  10, .bins={     0,     10}, .fill=[this] { return v.FatJet.LepTop.viSel[v.FatJet.i]; }, .axis_title="Top (lep.) index", .def_range={0,5} });
// Mass tag tops without subjet b veto
sh.AddNewFillParams("MTopPtBins",      { .nbin=Pt.size()-1 , .bins=Pt,       .fill=[this] { return v.FatJet().pt;           }, .axis_title="Mass-tagged top p_{T} (GeV)", .def_range={0,2000} });
sh.AddNewFillParams("MTopPt",          { .nbin=  80, .bins={     0,   4000}, .fill=[this] { return v.FatJet().pt;           }, .axis_title="Mass-tagged top p_{T} (GeV)", .def_range={0,2000} });
sh.AddNewFillParams("MTopEta",         { .nbin=  40, .bins={    -4,      4}, .fill=[this] { return v.FatJet().eta;          }, .axis_title="Mass-tagged top #eta",        .def_range={-2.4,2.4}});
sh.AddNewFillParams("MTopPhi",         { .nbin=  16, .bins={-3.142,  3.142}, .fill=[this] { return v.FatJet().phi;          }, .axis_title="Mass-tagged top #phi"});
sh.AddNewFillParams("MTopTau32",       { .nbin=  20, .bins={     0,      1}, .fill=[this] { return v.FatJet().tau32;                  }, .axis_title="Mass-tagged top #tau_{3}/#tau_{2}"});
sh.AddNewFillParams("MTopMass",        { .nbin=M.size()-1, .bins=M,          .fill=[this] { return v.FatJet().msoftdrop;        }, .axis_title="Mass-tagged top m_{Soft-Drop} (GeV)"});
sh.AddNewFillParams("MTopDeepTagMDTvsQCD", { .nbin=  20, .bins={     0,    1}, .fill=[this] { return v.FatJet().deepTagMD_TvsQCD; }, .axis_title="Mass-tagged top DeepTagMD (t vs. QCD)"});

// --------------------- New Boosted objects ---------------------
sh.AddNewFillParams("HadTopMass",      { .nbin=MFine.size()-1, .bins=MFine, .fill=[this] { return v.FatJet().msoftdrop; }, .axis_title="Top (had.) m_{Soft-Drop} (GeV)", .def_range={0,500} });
sh.AddNewFillParams("LepTopMass",      { .nbin=MFine.size()-1, .bins=MFine, .fill=[this] { return v.FatJet().msoftdrop; }, .axis_title="Top (lep.) m_{Soft-Drop} (GeV)", .def_range={0,500} });
sh.AddNewFillParams("HadWMass",        { .nbin=MFine.size()-1, .bins=MFine, .fill=[this] { return v.FatJet().msoftdrop; }, .axis_title="W (had.) m_{Soft-Drop} (GeV)", .def_range={0,300} });
sh.AddNewFillParams("HadZMass",        { .nbin=MFine.size()-1, .bins=MFine, .fill=[this] { return v.FatJet().msoftdrop; }, .axis_title="Z (had.) m_{Soft-Drop} (GeV)", .def_range={0,300} });
sh.AddNewFillParams("HadHMass",        { .nbin=MFine.size()-1, .bins=MFine, .fill=[this] { return v.FatJet().msoftdrop; }, .axis_title="H(#rightarrowb#bar{b}) m_{Soft-Drop} (GeV)", .def_range={0,500} });

// Leptonic Jets
sh.AddNewFillParams("LepJetPt",             { .nbin=  80, .bins={     0,   4000},  .fill=[this] { return v.FatJet().pt;                             }, .axis_title="Leptonic jet p_{T} (GeV)", .def_range={200,2000} });
sh.AddNewFillParams("LepJetEta",            { .nbin=  40, .bins={    -4,      4},  .fill=[this] { return v.FatJet().eta;                            }, .axis_title="Leptonic jet #eta",        .def_range={-2.4,2.4}});
sh.AddNewFillParams("LepJetPhi",            { .nbin=  16, .bins={-3.142,  3.142},  .fill=[this] { return v.FatJet().phi;                            }, .axis_title="Leptonic jet #phi"});
sh.AddNewFillParams("LepJetMass",           { .nbin= M2.size()-1, .bins=M2,        .fill=[this] { return v.FatJet().msoftdrop;                      }, .axis_title="Leptonic jet soft-drop mass (GeV)", .def_range={0,400}});
sh.AddNewFillParams("LepJetSubJetDeepB",    { .nbin=  20, .bins={     0,   1.00},  .fill=[this] { return std::min(v.FatJet().maxSubJetDeepB, double(0.999)); }, .axis_title="Leptonic jet max. AK8 subjet DeepB"});
sh.AddNewFillParams("LepJetTau21",          { .nbin=  20, .bins={     0,      1},  .fill=[this] { return std::min(v.FatJet().tau21, double(0.999));             }, .axis_title="Leptonic jet #tau_{2}/#tau_{1}"});
sh.AddNewFillParams("LepJetLSF",            { .nbin=  20, .bins={     0,      1},  .fill=[this] { return v.FatJet().LSF;                                   }, .axis_title="Lepton subjet fraction"});
sh.AddNewFillParams("LepJetLSFNoIso",       { .nbin=  20, .bins={     0,      1},  .fill=[this] { return v.FatJet().LSF_NoIso;                             }, .axis_title="Lepton subjet fraction (no iso.)"});
sh.AddNewFillParams("LepJetNSubJet",        { .nbin=   3, .bins={  -0.5,    2.5},  .fill=[this] { return v.FatJet().nSubJet;                               }, .axis_title="Leptonic jet N_{subjet}"});
sh.AddNewFillParams("LepJetDRmin",          { .nbin=  60, .bins={     0,      6}, .fill=[this] { return v.FatJet().matchedNoIsoLepJetDRmin;      }, .axis_title="Lepton, jet #DeltaR_{min}"});
sh.AddNewFillParams("LepJetPtrel",          { .nbin=  40, .bins={     0,    100}, .fill=[this] { return v.FatJet().matchedNoIsoLepCleanJetPtrel; }, .axis_title="Lepton, cleaned jet p_{T,rel} (GeV)"});
// Leptonic Tops
sh.AddNewFillParams("LepTopPt",             { .nbin=  80, .bins={     0,   4000},  .fill=[this] { return v.FatJet().pt;                             }, .axis_title="Leptonic top p_{T} (GeV)", .def_range={200,2000} });
sh.AddNewFillParams("LepTopEta",            { .nbin=  40, .bins={    -4,      4},  .fill=[this] { return v.FatJet().eta;                            }, .axis_title="Leptonic top #eta",        .def_range={-2.4,2.4}});
sh.AddNewFillParams("LepTopPhi",            { .nbin=  16, .bins={-3.142,  3.142},  .fill=[this] { return v.FatJet().phi;                            }, .axis_title="Leptonic top #phi"});
sh.AddNewFillParams("LepTopMass",           { .nbin= M2.size()-1, .bins=M2,        .fill=[this] { return v.FatJet().msoftdrop;                      }, .axis_title="Leptonic top soft-drop mass (GeV)", .def_range={0,400}});
sh.AddNewFillParams("LepTopSubJetDeepB",    { .nbin=  20, .bins={     0,   1.00},  .fill=[this] { return std::min(v.FatJet().maxSubJetDeepB, double(0.999)); }, .axis_title="Leptonic top max. AK8 subjet DeepB"});
sh.AddNewFillParams("LepTopTau21",          { .nbin=  20, .bins={     0,      1}, .fill=[this] { return std::min(v.FatJet().tau21, double(0.999));             }, .axis_title="Leptonic top #tau_{2}/#tau_{1}"});
sh.AddNewFillParams("LepTopLSF",            { .nbin=  20, .bins={     0,      1},  .fill=[this] { return v.FatJet().LSF;                                   }, .axis_title="Lepton subjet fraction"});
sh.AddNewFillParams("LepTopLSFNoIso",       { .nbin=  20, .bins={     0,      1},  .fill=[this] { return v.FatJet().LSF_NoIso;                             }, .axis_title="Lepton subjet fraction (no iso.)"});
sh.AddNewFillParams("LepTopNSubJet",        { .nbin=   3, .bins={  -0.5,    2.5},  .fill=[this] { return v.FatJet().nSubJet;                               }, .axis_title="Leptonic top N_{subjet}"});

// gen
sh.AddNewFillParams("GenLepPt",             { .nbin= 100, .bins={     0,    500},  .fill=[this] { return v.GenPart().pt;            }, .axis_title="Gen. Lepton p_{T} (GeV)", .def_range={5,200}});
sh.AddNewFillParams("GenLepPtBins",         { .nbin=LepPt.size()-1,  .bins=LepPt,  .fill=[this] { return v.GenPart().pt;            }, .axis_title="Gen. Lepton p_{T} (GeV)", .def_range={5,200}});

// Lepton reco+id+iso efficiencies
sh.AddNewFillParams("GenElePt",             { .nbin=LepPt.size()-1,  .bins=LepPt,  .fill=[this] { return abs(v.GenPart().pdgId) == 11 ? v.GenPart().pt : 9999; }, .axis_title="Gen. Ele p_{T} (GeV)", .def_range={5,200}});
sh.AddNewFillParams("GenEleEta",            { .nbin=LepEta.size()-1, .bins=LepEta, .fill=[this] { return abs(v.GenPart().pdgId) == 11 ? fabs(v.GenPart().eta) : 9999; }, .axis_title="Gen. Ele |\eta|", .def_range={0,2.5}});
sh.AddNewFillParams("GenMuPt",              { .nbin=LepPt.size()-1,  .bins=LepPt,  .fill=[this] { return abs(v.GenPart().pdgId) == 13 ? v.GenPart().pt : 9999; }, .axis_title="Gen. Mu p_{T} (GeV)", .def_range={5,200}});
sh.AddNewFillParams("GenMuEta",             { .nbin=LepEta.size()-1, .bins=LepEta, .fill=[this] { return abs(v.GenPart().pdgId) == 13 ? fabs(v.GenPart().eta) : 9999; }, .axis_title="Gen. Mu |\eta|", .def_range={0,2.5}});

sh.AddNewFillParams("GenLepWMatchedGenLepPt",       { .nbin= 100, .bins={     0,    500},  .fill=[this] { return v.GenPart().iGenLepDaughter  == (size_t)-1 ? -9999 : v.GenPart(v.GenPart().iGenLepDaughter).pt; }, .axis_title="Gen. Lepton (from W) p_{T} (GeV)", .def_range={5,200}});
sh.AddNewFillParams("GenLepWMatchedGenLepPtBins",   { .nbin=LepPt.size()-1,  .bins=LepPt,  .fill=[this] { return v.GenPart().iGenLepDaughter  == (size_t)-1 ? -9999 : v.GenPart(v.GenPart().iGenLepDaughter).pt; }, .axis_title="Gen. Lepton (from W) p_{T} (GeV)", .def_range={5,200}});

sh.AddNewFillParams("GenLepTopMatchedGenLepPt",     { .nbin= 100, .bins={     0,    500},  .fill=[this] { return v.GenPart().iGenLepGrandDaughter == (size_t)-1 ? -9999 : v.GenPart(v.GenPart().iGenLepGrandDaughter).pt; }, .axis_title="Gen. Lepton (from top) p_{T} (GeV)", .def_range={5,200}});
sh.AddNewFillParams("GenLepTopMatchedGenLepPtBins", { .nbin=LepPt.size()-1,  .bins=LepPt,  .fill=[this] { return v.GenPart().iGenLepGrandDaughter == (size_t)-1 ? -9999 : v.GenPart(v.GenPart().iGenLepGrandDaughter).pt; }, .axis_title="Gen. Lepton (from top) p_{T} (GeV)", .def_range={5,200}});

sh.AddNewFillParams("GenLepEta",                    { .nbin=LepEta.size()-1, .bins=LepEta, .fill=[this] { return std::abs(v.GenPart().eta); }, .axis_title="Gen. Lepton |#eta|"});
sh.AddNewFillParams("GenLepTopMatchedGenLepEta",    { .nbin=LepEta.size()-1, .bins=LepEta, .fill=[this] { return v.GenPart().iGenLepGrandDaughter == (size_t)-1 ? -9999 : std::abs(v.GenPart(v.GenPart().iGenLepGrandDaughter).eta); }, .axis_title="Gen. Lepton (from top) |#eta|"});
//   sh.AddNewFillParams("NGenLepTopMatchedGenLep",    { .nbin=3, .bins={  -0.5,    2.5}, .fill=[this] { return v.GenPart().iGenLepGrandDaughter == (size_t)-1 ? -9999 : v.GenPart(v.GenPart().iGenLepGrandDaughter).n; }, .axis_title="Number of Gen. Lepton (from top)"});
sh.AddNewFillParams("GenHadWPt",                    { .nbin=   80, .bins={    0,    4000}, .fill=[this] { return v.GenPart().pt;  }, .axis_title="Gen-W (had.) p_{T} (GeV)",   .def_range={0, 2000}});
sh.AddNewFillParams("GenHadWPtBins",                { .nbin=Pt.size()-1, .bins=Pt,         .fill=[this] { return v.GenPart().pt;  }, .axis_title="Gen-W (had.) p_{T} (GeV)",   .def_range={0, 2000}});
sh.AddNewFillParams("GenHadWEta",                   { .nbin=LepEta.size()-1, .bins=LepEta, .fill=[this] { return std::abs(v.GenPart().eta); }, .axis_title="Gen. Had W |#eta|"});

sh.AddNewFillParams("GenTopPt",                     { .nbin=   80, .bins={    0,    4000}, .fill=[this] { return v.GenPart().pt;  }, .axis_title="Gen-top p_{T} (GeV)", .def_range={0, 2000}});
sh.AddNewFillParams("GenTopPtBins",                 { .nbin=Pt.size()-1, .bins=Pt,         .fill=[this] { return v.GenPart().pt;  }, .axis_title="Gen-top p_{T} (GeV)", .def_range={0, 2000}});
sh.AddNewFillParams("GenTopEta",                    { .nbin=LepEta.size()-1, .bins=LepEta, .fill=[this] { return std::abs(v.GenPart().eta); }, .axis_title="Gen. top |#eta|"});

sh.AddNewFillParams("GenHadTopPt",                  { .nbin=   80, .bins={    0,    4000}, .fill=[this] { return v.GenPart().pt;  }, .axis_title="Gen-top (had.) p_{T} (GeV)", .def_range={0, 2000}});
sh.AddNewFillParams("GenHadTopPtBins",              { .nbin=Pt.size()-1, .bins=Pt,         .fill=[this] { return v.GenPart().pt;  }, .axis_title="Gen-top (had.) p_{T} (GeV)", .def_range={0, 2000}});

sh.AddNewFillParams("GenLepTopPt",                  { .nbin=   80, .bins={    0,    4000}, .fill=[this] { return v.GenPart().pt;  }, .axis_title="Gen-top (lep.) p_{T} (GeV)", .def_range={0, 2000}});
sh.AddNewFillParams("GenLepTopPtBins",              { .nbin=Pt.size()-1, .bins=Pt,         .fill=[this] { return v.GenPart().pt;  }, .axis_title="Gen-top (lep.) p_{T} (GeV)", .def_range={0, 2000}});

sh.AddNewFillParams("GenMatchedAK8JetPt",    { .nbin=   80, .bins={    0,    4000}, .fill=[this] { return v.GenPart().iMatchedAK8==(size_t)-1 ? -9999 : v.FatJet(v.GenPart().iMatchedAK8).pt; }, .axis_title="Matched AK8 jet p_{T} (GeV)", .def_range={0, 2000}});
sh.AddNewFillParams("GenMatchedAK8JetPtBins",{ .nbin=PtG.size()-1, .bins=PtG,       .fill=[this] { return v.GenPart().iMatchedAK8==(size_t)-1 ? -9999 : v.FatJet(v.GenPart().iMatchedAK8).pt; }, .axis_title="Matched AK8 jet p_{T} (GeV)", .def_range={0, 2000}});
sh.AddNewFillParams("GenMatchedAK8JetIndex", { .nbin=   10, .bins={    0,    10},   .fill=[this] { return v.GenPart().iMatchedAK8;   }, .axis_title="Gen W (had.) matched AK8 jet index", .def_range={0, 5}});


// --------------------- Event Variables -------------------

// Object counts
sh.AddNewFillParams("NVtx",                 { .nbin=NVTX.size()-1, .bins=NVTX,    .fill=[this] { return v.PV_npvsGood;                  }, .axis_title="N_{Vertices}",         .def_range={0,50}});
sh.AddNewFillParams("NJet",                 { .nbin=  20, .bins={    0,      20}, .fill=[this] { return v.Jet.Jet.n;                    }, .axis_title="N_{Jet}",              .def_range={2,20}});
sh.AddNewFillParams("NJetBins",             { .nbin=   5, .bins={2,3,4,5,6,20},   .fill=[this] { return v.Jet.Jet.n;                    }, .axis_title="N_{Jet}",              .def_range={2,20}});
sh.AddNewFillParams("NJetNoPho",            { .nbin=  20, .bins={    0,      20}, .fill=[this] { return v.Jet.JetNoPho.n;               }, .axis_title="N_{Jet}",              .def_range={2,20}});
sh.AddNewFillParams("NJetNoPhoBins",        { .nbin=  3,  .bins={2,4,6,20},   .fill=[this] { return v.Jet.JetNoPho.n;               }, .axis_title="N_{Jet}",              .def_range={2,20}});  
sh.AddNewFillParams("NJetAK8",              { .nbin=  10, .bins={    0,      10}, .fill=[this] { return v.FatJet.JetAK8.n;              }, .axis_title="N_{AK8 jet}",          .def_range={1,10}});
sh.AddNewFillParams("NW",                   { .nbin=  10, .bins={    0,      10}, .fill=[this] { return v.FatJet.HadW.n;                }, .axis_title="N_{W}",                .def_range={0,10}});
sh.AddNewFillParams("NZ",                   { .nbin=  10, .bins={    0,      10}, .fill=[this] { return v.FatJet.HadZ.n;                }, .axis_title="N_{Z}",                .def_range={0,10}});
sh.AddNewFillParams("NV",                   { .nbin=  10, .bins={    0,      10}, .fill=[this] { return v.FatJet.HadV.n;                }, .axis_title="N_{V}",                .def_range={0,10}});
sh.AddNewFillParams("NTop",                 { .nbin=  10, .bins={    0,      10}, .fill=[this] { return v.FatJet.HadTop.n;              }, .axis_title="N_{Top}",              .def_range={0,10}});
sh.AddNewFillParams("NH",                   { .nbin=  10, .bins={    0,      10}, .fill=[this] { return v.FatJet.HadH.n;                }, .axis_title="N_{H}",                .def_range={0,10}});
sh.AddNewFillParams("NLepTop",              { .nbin=  10, .bins={    0,      10}, .fill=[this] { return v.FatJet.LepTop.n;              }, .axis_title="N_{LepTop}",           .def_range={0,10}});
sh.AddNewFillParams("NLepJet",              { .nbin=  10, .bins={    0,      10}, .fill=[this] { return v.FatJet.LepJet.n;              }, .axis_title="N_{LepJet}",           .def_range={0,10}});
sh.AddNewFillParams("NBTag",                { .nbin=   5, .bins={    0,       5}, .fill=[this] { return v.Jet.MediumBTag.n;             }, .axis_title="N_{b}",                .def_range={0,4}});
sh.AddNewFillParams("NLooseBTag",           { .nbin=   5, .bins={    0,       5}, .fill=[this] { return v.Jet.LooseBTag.n;              }, .axis_title="N_{b, loose tag}",     .def_range={0,4}});
sh.AddNewFillParams("NTightBTag",           { .nbin=   5, .bins={    0,       5}, .fill=[this] { return v.Jet.TightBTag.n;              }, .axis_title="N_{b, tight tag}",     .def_range={0,4}});
sh.AddNewFillParams("NBTagNoPho",           { .nbin=   5, .bins={    0,       5}, .fill=[this] { return v.Jet.MediumBTagNoPho.n;        }, .axis_title="N_{b, no #gamma}",     .def_range={0,4}});
sh.AddNewFillParams("NW1",                  { .nbin=   5, .bins={    0,       5}, .fill=[this] { return v.FatJet.W1.n;                  }, .axis_title="N_{W} Loose",          .def_range={0,4}});
sh.AddNewFillParams("NW2",                  { .nbin=   5, .bins={    0,       5}, .fill=[this] { return v.FatJet.W2.n;                  }, .axis_title="N_{W} Medium",         .def_range={0,4}});
sh.AddNewFillParams("NW3",                  { .nbin=   5, .bins={    0,       5}, .fill=[this] { return v.FatJet.W3.n;                  }, .axis_title="N_{W} Tight",          .def_range={0,4}});
sh.AddNewFillParams("NTop1",                { .nbin=   5, .bins={    0,       5}, .fill=[this] { return v.FatJet.Top1.n;                }, .axis_title="N_{Top} VLoose",       .def_range={0,4}});
sh.AddNewFillParams("NTop2",                { .nbin=   5, .bins={    0,       5}, .fill=[this] { return v.FatJet.Top2.n;                }, .axis_title="N_{Top} Loose",        .def_range={0,4}});
sh.AddNewFillParams("NTop3",                { .nbin=   5, .bins={    0,       5}, .fill=[this] { return v.FatJet.Top3.n;                }, .axis_title="N_{Top} Medium",       .def_range={0,4}});
sh.AddNewFillParams("NTop4",                { .nbin=   5, .bins={    0,       5}, .fill=[this] { return v.FatJet.Top4.n;                }, .axis_title="N_{Top} Tight",        .def_range={0,4}});
sh.AddNewFillParams("NTop5",                { .nbin=   5, .bins={    0,       5}, .fill=[this] { return v.FatJet.Top5.n;                }, .axis_title="N_{Top} VTight",       .def_range={0,4}});
sh.AddNewFillParams("NWDeep1",              { .nbin=   5, .bins={    0,       5}, .fill=[this] { return v.FatJet.WDeep1.n;              }, .axis_title="N_{W} (Deep 5%)",      .def_range={0,4}});
sh.AddNewFillParams("NWDeep2",              { .nbin=   5, .bins={    0,       5}, .fill=[this] { return v.FatJet.WDeep2.n;              }, .axis_title="N_{W} (Deep 1%)",      .def_range={0,4}});
sh.AddNewFillParams("NWDeep3",              { .nbin=   5, .bins={    0,       5}, .fill=[this] { return v.FatJet.WDeep3.n;              }, .axis_title="N_{W} (Deep 0.5%)",    .def_range={0,4}});
sh.AddNewFillParams("NWDeepMD1",            { .nbin=   5, .bins={    0,       5}, .fill=[this] { return v.FatJet.WDeepMD1.n;            }, .axis_title="N_{W} (DeepMD 5%)",    .def_range={0,4}});
sh.AddNewFillParams("NWDeepMD2",            { .nbin=   5, .bins={    0,       5}, .fill=[this] { return v.FatJet.WDeepMD2.n;            }, .axis_title="N_{W} (DeepMD 1%)",    .def_range={0,4}});
sh.AddNewFillParams("NWDeepMD3",            { .nbin=   5, .bins={    0,       5}, .fill=[this] { return v.FatJet.WDeepMD3.n;            }, .axis_title="N_{W} (DeepMD 0.5%)",  .def_range={0,4}});
sh.AddNewFillParams("NZDeep1",              { .nbin=   5, .bins={    0,       5}, .fill=[this] { return v.FatJet.ZDeep1.n;              }, .axis_title="N_{Z} (Deep 0.80)",    .def_range={0,4}});
sh.AddNewFillParams("NZDeep2",              { .nbin=   5, .bins={    0,       5}, .fill=[this] { return v.FatJet.ZDeep2.n;              }, .axis_title="N_{Z} (Deep 0.95)",    .def_range={0,4}});
sh.AddNewFillParams("NZDeep3",              { .nbin=   5, .bins={    0,       5}, .fill=[this] { return v.FatJet.ZDeep3.n;              }, .axis_title="N_{Z} (Deep 0.99)",    .def_range={0,4}});
sh.AddNewFillParams("NZDeepMD1",            { .nbin=   5, .bins={    0,       5}, .fill=[this] { return v.FatJet.ZDeepMD1.n;            }, .axis_title="N_{Z} (DeepMD 0.30)",  .def_range={0,4}});
sh.AddNewFillParams("NZDeepMD2",            { .nbin=   5, .bins={    0,       5}, .fill=[this] { return v.FatJet.ZDeepMD2.n;            }, .axis_title="N_{Z} (DeepMD 0.80)",  .def_range={0,4}});
sh.AddNewFillParams("NZDeepMD3",            { .nbin=   5, .bins={    0,       5}, .fill=[this] { return v.FatJet.ZDeepMD3.n;            }, .axis_title="N_{Z} (DeepMD 0.90)",  .def_range={0,4}});
sh.AddNewFillParams("NTopDeep1",            { .nbin=   5, .bins={    0,       5}, .fill=[this] { return v.FatJet.TopDeep1.n;            }, .axis_title="N_{Top} (Deep 5%)",    .def_range={0,4}});
sh.AddNewFillParams("NTopDeep2",            { .nbin=   5, .bins={    0,       5}, .fill=[this] { return v.FatJet.TopDeep2.n;            }, .axis_title="N_{Top} (Deep 1%)",    .def_range={0,4}});
sh.AddNewFillParams("NTopDeep3",            { .nbin=   5, .bins={    0,       5}, .fill=[this] { return v.FatJet.TopDeep3.n;            }, .axis_title="N_{Top} (Deep 0.5%)",  .def_range={0,4}});
sh.AddNewFillParams("NTopDeep4",            { .nbin=   5, .bins={    0,       5}, .fill=[this] { return v.FatJet.TopDeep4.n;            }, .axis_title="N_{Top} (Deep 0.1%)",  .def_range={0,4}});
sh.AddNewFillParams("NTopDeepMD1",          { .nbin=   5, .bins={    0,       5}, .fill=[this] { return v.FatJet.TopDeepMD1.n;          }, .axis_title="N_{Top} (DeepMD 5%)",  .def_range={0,4}});
sh.AddNewFillParams("NTopDeepMD2",          { .nbin=   5, .bins={    0,       5}, .fill=[this] { return v.FatJet.TopDeepMD2.n;          }, .axis_title="N_{Top} (DeepMD 1%)",  .def_range={0,4}});
sh.AddNewFillParams("NTopDeepMD3",          { .nbin=   5, .bins={    0,       5}, .fill=[this] { return v.FatJet.TopDeepMD3.n;          }, .axis_title="N_{Top} (DeepMD 0.5%)",.def_range={0,4}});
sh.AddNewFillParams("NTopDeepMD4",          { .nbin=   5, .bins={    0,       5}, .fill=[this] { return v.FatJet.TopDeepMD4.n;          }, .axis_title="N_{Top} (DeepMD 0.1%)",.def_range={0,4}});
sh.AddNewFillParams("NLepVeto",             { .nbin=   5, .bins={    0,       5}, .fill=[this] { return v.nLepVeto;                     }, .axis_title="N_{lepton, Veto}",     .def_range={0,4}});
sh.AddNewFillParams("NEleVeto",             { .nbin=   5, .bins={    0,       5}, .fill=[this] { return v.Electron.Veto.n;              }, .axis_title="N_{ele, Veto}",        .def_range={0,4}});
sh.AddNewFillParams("NMuVeto",              { .nbin=   5, .bins={    0,       5}, .fill=[this] { return v.Muon.Veto.n;                  }, .axis_title="N_{muon, Veto}",       .def_range={0,4}});
sh.AddNewFillParams("NTauVeto",             { .nbin=   5, .bins={    0,       5}, .fill=[this] { return v.Tau.Veto.n;                   }, .axis_title="N_{tau, Veto}",        .def_range={0,4}});
sh.AddNewFillParams("NIsoTrk",              { .nbin=   5, .bins={    0,       5}, .fill=[this] { return v.nIsoTrack;                    }, .axis_title="N_{iso trk}",          .def_range={0,4}});
sh.AddNewFillParams("NLep",                 { .nbin=   5, .bins={    0,       5}, .fill=[this] { return v.nLepSelect;                   }, .axis_title="N_{lepton}",           .def_range={0,4}});
sh.AddNewFillParams("NLepTight",            { .nbin=   5, .bins={    0,       5}, .fill=[this] { return v.nLepTight;                    }, .axis_title="N_{e/#mu, tight}",         .def_range={0,5}});
sh.AddNewFillParams("NEleNoIso",            { .nbin=   5, .bins={    0,       5}, .fill=[this] { return v.Electron.NoIso.n;             }, .axis_title="N_{e, tight, no iso}", .def_range={0,5}});
sh.AddNewFillParams("NMuNoIso",             { .nbin=   5, .bins={    0,       5}, .fill=[this] { return v.Muon.NoIso.n;                 }, .axis_title="N_{#mu, tight, no iso}", .def_range={0,5}});
sh.AddNewFillParams("NLepNoIso",            { .nbin=   5, .bins={    0,       5}, .fill=[this] { return v.nLepNoIso;                    }, .axis_title="N_{e/#mu, tight, no iso}", .def_range={0,5}});
sh.AddNewFillParams("NEleNonIso",           { .nbin=   5, .bins={    0,       5}, .fill=[this] { return v.Electron.NonIso.n;            }, .axis_title="N_{e, non-iso.}", .def_range={0,5}});
sh.AddNewFillParams("NMuNonIso",            { .nbin=   5, .bins={    0,       5}, .fill=[this] { return v.Muon.NonIso.n;                }, .axis_title="N_{#mu, non-iso.}", .def_range={0,5}});
sh.AddNewFillParams("NLepNonIso",           { .nbin=   5, .bins={    0,       5}, .fill=[this] { return v.nLepNonIso;                   }, .axis_title="N_{e/#mu, non-iso.}", .def_range={0,5}});
sh.AddNewFillParams("NEle",                 { .nbin=   5, .bins={    0,       5}, .fill=[this] { return v.Electron.Select.n;            }, .axis_title="N_{electron}",         .def_range={0,4}});
sh.AddNewFillParams("NMu",                  { .nbin=   5, .bins={    0,       5}, .fill=[this] { return v.Muon.Select.n;                }, .axis_title="N_{muon}",             .def_range={0,4}});
sh.AddNewFillParams("NPhoton",              { .nbin=   5, .bins={    0,       5}, .fill=[this] { return v.Photon.Select.n;              }, .axis_title="N_{photon}",           .def_range={0,4}});
// Gen truth
sh.AddNewFillParams("NGenEleFromW",         { .nbin=   5, .bins={    0,       5}, .fill=[this] { return v.GenPart.EleFromW.n;      }, .axis_title="N_{e, gen}",   .def_range={0,5}});
sh.AddNewFillParams("NGenMuFromW",          { .nbin=   5, .bins={    0,       5}, .fill=[this] { return v.GenPart.MuFromW.n;       }, .axis_title="N_{#mu, gen}", .def_range={0,5}});
sh.AddNewFillParams("NGenLepFromW",         { .nbin=   5, .bins={    0,       5}, .fill=[this] { return v.GenPart.LeptonFromW.n;   }, .axis_title="N_{lep, gen}", .def_range={0,5}});
sh.AddNewFillParams("NGenEleFromZ",         { .nbin=   5, .bins={    0,       5}, .fill=[this] { return v.GenPart.EleFromZ.n;      }, .axis_title="N_{e, gen}",   .def_range={0,5}});
sh.AddNewFillParams("NGenMuFromZ",          { .nbin=   5, .bins={    0,       5}, .fill=[this] { return v.GenPart.MuFromZ.n;       }, .axis_title="N_{#mu, gen}", .def_range={0,5}});
sh.AddNewFillParams("NGenLepFromZ",         { .nbin=   5, .bins={    0,       5}, .fill=[this] { return v.GenPart.LeptonFromZ.n;   }, .axis_title="N_{lep, gen}", .def_range={0,5}});
sh.AddNewFillParams("NGenEleFromTop",       { .nbin=   5, .bins={    0,       5}, .fill=[this] { return v.GenPart.EleFromTop.n;    }, .axis_title="N_{e, gen}",   .def_range={0,5}});
sh.AddNewFillParams("NGenMuFromTop",        { .nbin=   5, .bins={    0,       5}, .fill=[this] { return v.GenPart.MuFromTop.n;     }, .axis_title="N_{#mu, gen}", .def_range={0,5}});
sh.AddNewFillParams("NGenLepFromTop",       { .nbin=   5, .bins={    0,       5}, .fill=[this] { return v.GenPart.LeptonFromTop.n; }, .axis_title="N_{lep, gen}", .def_range={0,5}});

sh.AddNewFillParams("NGenEleAndMuFrom2Tops",        { .nbin=   3, .bins={    0,       3}, .fill=[this] { return (v.GenPart.EleFromTop.n+v.GenPart.MuFromTop.n); }, .axis_title="N_{ele, gen top}+N_{mu, gen top}", .def_range={}});           
sh.AddNewFillParams("NGenEleAndMuAndTauFrom2Tops",  { .nbin=   3, .bins={    0,       3}, .fill=[this] { return (v.GenPart.EleFromTop.n+v.GenPart.MuFromTop.n+v.GenPart.TauFromTop.n); }, .axis_title="N_{ele, gen top}+N_{mu, gen top}+N_{tau, gen top}", .def_range={}});
sh.AddNewFillParams("NGenEleAndMuFrom1Top",         { .nbin=   2, .bins={    0,       2}, .fill=[this] { return (v.GenPart.EleFromTop.n+v.GenPart.MuFromTop.n); }, .axis_title="N_{ele, gen top}+N_{mu, gen top}", .def_range={}});
sh.AddNewFillParams("NGenEleAndMuAndTauFrom1Top",   { .nbin=   2, .bins={    0,       2}, .fill=[this] { return (v.GenPart.EleFromTop.n+v.GenPart.MuFromTop.n+v.GenPart.TauFromTop.n); }, .axis_title="N_{ele, gen top}+N_{mu, gen top}+N_{tau, gen top}", .def_range={}});
sh.AddNewFillParams("NGenEleAndMuFrom1W",           { .nbin=   2, .bins={    0,       2}, .fill=[this] { return (v.GenPart.EleFromW.n+v.GenPart.MuFromW.n); }, .axis_title="N_{ele, gen W}+N_{mu, gen W}", .def_range={}});
sh.AddNewFillParams("NGenEleAndMuAndTauFrom1W",     { .nbin=   2, .bins={    0,       2}, .fill=[this] { return (v.GenPart.LeptonFromW.n); }, .axis_title="N_{ele, gen W}+N_{mu, gen W}+N_{tau, gen W}", .def_range={}});
sh.AddNewFillParams("NGenHadW",             { .nbin=   5, .bins={    0,       5}, .fill=[this] { return v.GenPart.HadW.n;          }, .axis_title="N_{W (had.), gen}", .def_range={0,5}});
sh.AddNewFillParams("NGenHadZ",             { .nbin=   5, .bins={    0,       5}, .fill=[this] { return v.GenPart.HadZ.n;          }, .axis_title="N_{Z (had.), gen}", .def_range={0,5}});
sh.AddNewFillParams("NGenHadTop",           { .nbin=   5, .bins={    0,       5}, .fill=[this] { return v.GenPart.HadTop.n;        }, .axis_title="N_{top (had.), gen}", .def_range={0,5}});
sh.AddNewFillParams("NGenLepTop",           { .nbin=   5, .bins={    0,       5}, .fill=[this] { return v.GenPart.LepTop.n;        }, .axis_title="N_{top (lep.), gen}", .def_range={0,5}});
// Razor
//sh.AddNewFillParams("MR",                   { .nbin= 100, .bins={    0,   10000}, .fill=[this] { return v.MR;                      }, .axis_title="M_{R} (GeV)",          .def_range={0,2000}});
//sh.AddNewFillParams("R2",                   { .nbin=  80, .bins={    0,     4.0}, .fill=[this] { return v.R2;                      }, .axis_title="R^{2}",                .def_range={0,1}});
sh.AddNewFillParams("MR",                   { .nbin=MR_bins.size()-1, .bins=MR_bins, .fill=[this] { return v.MR;                }, .axis_title="M_{R} (GeV)",          .def_range={0,4000}});
sh.AddNewFillParams("MRFine",               { .nbin=  25, .bins={    0,    5000}, .fill=[this] { return v.MR;                }, .axis_title="M_{R} (GeV)",          .def_range={800,4000}});
sh.AddNewFillParams("MRBins",               { .nbin=MR_RI.size()-1, .bins=MR_RI,  .fill=[this] { return v.MR;                }, .axis_title="M_{R} (GeV)",          .def_range={300,4000}});
//sh.AddNewFillParams("MTR",                  { .nbin=  80, .bins={    0,    4000}, .fill=[this] { return v.MTR;               }, .axis_title="M_{T}^{R} (GeV)",      .def_range={0,2000}});
sh.AddNewFillParams("MTR",                  { .nbin=MTR_bins.size()-1, .bins=MTR_bins,      .fill=[this] { return v.MTR;               }, .axis_title="M_{T}^{R} (GeV)",      .def_range={0,2000}});
sh.AddNewFillParams("R2",                   { .nbin=R2_bins.size()-1, .bins=R2_bins, .fill=[this] { return v.R2;                      }, .axis_title="R^{2}",                .def_range={0,1.5}});
sh.AddNewFillParams("R2Fine",               { .nbin=  40, .bins={    0,     1.6}, .fill=[this] { return v.R2;                      }, .axis_title="R^{2}",                .def_range={0,1.6}});
sh.AddNewFillParams("R2Bins",               { .nbin=R2_RI.size()-1, .bins=R2_RI,  .fill=[this] { return v.R2;                      }, .axis_title="R^{2}",                .def_range={0.15,1.5}});
sh.AddNewFillParams("MTRNo1Lep",            { .nbin=MTR_bins.size()-1, .bins=MTR_bins,      .fill=[this] { return v.MTR_1l;                  }, .axis_title="M_{T, no lep}^{R} (GeV)",   .def_range={0,2000}});
sh.AddNewFillParams("MTRNo1VLep",           { .nbin=MTR_bins.size()-1, .bins=MTR_bins,      .fill=[this] { return v.MTR_1vl;                 }, .axis_title="M_{T, no lep}^{R} (GeV)",   .def_range={0,2000}});
sh.AddNewFillParams("R2No1Lep",             { .nbin=R2_bins.size()-1, .bins=R2_bins, .fill=[this] { return v.R2_1l;                   }, .axis_title="R_{no lep}^{2}",       .def_range={0,1.5}});
sh.AddNewFillParams("R2No1VLep",            { .nbin=R2_bins.size()-1, .bins=R2_bins, .fill=[this] { return v.R2_1vl;                  }, .axis_title="R_{no lep}^{2}",       .def_range={0,1.5}});
sh.AddNewFillParams("MTRNo2Lep",            { .nbin=MTR_bins.size()-1, .bins=MTR_bins,      .fill=[this] { return v.MTR_2l;                  }, .axis_title="M_{T,ll}^{R} (GeV)",   .def_range={0,2000}});
sh.AddNewFillParams("R2No2Lep",             { .nbin=R2_bins.size()-1, .bins=R2_bins, .fill=[this] { return v.R2_2l;                   }, .axis_title="R_{ll}^{2}",           .def_range={0,1.5}});
sh.AddNewFillParams("MTRNoDiLep",           { .nbin=MTR_bins.size()-1, .bins=MTR_bins,      .fill=[this] { return v.MTR_dilep;        }, .axis_title="M_{T}^{R} (GeV)",   .def_range={0,2000}});
sh.AddNewFillParams("R2NoDiLep",            { .nbin=R2_bins.size()-1, .bins=R2_bins, .fill=[this] { return v.R2_dilep;                }, .axis_title="R^{2}",           .def_range={0,1.5}});
add_unrolled_bins("RazorBins",       "M_{R} (TeV)", "R^{2}", [this] { return v.MR/1000;     }, [this] { return v.R2;     }, MR_2D_bins,     R2_2D_bins, merged_razor_bins,     1, 2);
add_unrolled_bins("RazorBinsLep",    "M_{R} (TeV)", "R^{2}", [this] { return v.MR/1000;     }, [this] { return v.R2;     }, MR_2D_bins_lep, R2_2D_bins, merged_razor_bins_lep, 1, 2);
add_unrolled_bins("RazorllBins",     "M_{R} (TeV)", "R^{2}", [this] { return v.MR/1000;     }, [this] { return v.R2_2l;  }, MR_2D_bins,     R2_2D_bins, merged_razor_bins,     1, 2);
add_unrolled_bins("RazorNo1LepBins", "M_{R} (TeV)", "R^{2}", [this] { return v.MR/1000;     }, [this] { return v.R2_1l;  }, MR_2D_bins,     R2_2D_bins, merged_razor_bins,     1, 2);
add_unrolled_bins("RazorNo1VLepBins","M_{R} (TeV)", "R^{2}", [this] { return v.MR/1000;     }, [this] { return v.R2_1vl; }, MR_2D_bins,     R2_2D_bins, merged_razor_bins,     1, 2);
add_unrolled_bins("RazorNoPhoBins",  "M_{R} (TeV)", "R^{2}", [this] { return v.MR_pho/1000; }, [this] { return v.R2_pho; }, MR_2D_bins,     R2_2D_bins, merged_razor_bins,     1, 2);
sh.AddNewFillParams("MRR2",                 { .nbin=  15, .bins={    0,    3000}, .fill=[this] { return v.MR*v.R2;                }, .axis_title="M_{R} #times R^{2} (GeV)",  .def_range={0,2400}});
sh.AddNewFillParams("MRR2No1VLep",          { .nbin=  15, .bins={    0,    3000}, .fill=[this] { return v.MR*v.R2_1vl;            }, .axis_title="M_{R} #times R_{no lep}^{2} (GeV)",  .def_range={0,2400}});
sh.AddNewFillParams("MRR2No2Lep",           { .nbin=   8, .bins={    0,    800}, .fill=[this] { return v.MR*v.R2_2l < 800 ? v.MR*v.R2_2l : 799;             }, .axis_title="M_{R} #times R_{ll}^{2} (GeV)",  .def_range={0,800}});
sh.AddNewFillParams("MRR2NoDiLep",          { .nbin=   8, .bins={    0,    800}, .fill=[this] { return v.MR*v.R2_dilep   < 800 ? v.MR*v.R2_dilep   : 799;        }, .axis_title="M_{R} #times R^{2} (GeV)",  .def_range={0,800}});
sh.AddNewFillParams("MRR2NoPho",            { .nbin=   8, .bins={    0,    800}, .fill=[this] { return v.MR_pho*v.R2_pho < 800 ? v.MR_pho*v.R2_pho : 799;        }, .axis_title="M_{R} #times R^{2} (GeV)",  .def_range={0,800}});
sh.AddNewFillParams("MRR2NoPhoBins",        { .nbin=   3, .bins={0, 150, 300, 3000}, .fill=[this] { return v.MR_pho*v.R2_pho;        }, .axis_title="M_{R} #times R^{2} (GeV)",  .def_range={0,3000}});
sh.AddNewFillParams("1or2Boost",            { .nbin=   2, .bins={1, 2, 100}, .fill=[this] { return v.FatJet.JetAK8Mass.n;        }, .axis_title="N_{AK8 Jet}",  .def_range={1,100}});   
sh.AddNewFillParams("BoostJetPt",             { .nbin=  40, .bins={     0,   4000},  .fill=[this] { return v.FatJet().pt;                             }, .axis_title="Mass tag p_{T} (GeV)", .def_range={200,2000} });
//sh.AddNewFillParams("MRR2Bins",           { .nbin=   4, .bins={0, 200, 400, 600, 3000}, .fill=[this] { return v.MR*v.R2; }, .axis_title="M_{R} #times R^{2} (GeV)",  .def_range={0,3000}});
sh.AddNewFillParams("MRR2Bins",             { .nbin=   6, .bins={0, 100, 200, 300, 400, 500, 3000}, .fill=[this] { return v.MR*v.R2; }, .axis_title="M_{R} #times R^{2} (GeV)",  .def_range={0,3000}});
sh.AddNewFillParams("MRR2Bin",              { .nbin=   6, .bins={0, 100, 200, 300, 400, 500, 600}, .fill=[this] { return v.MR*v.R2 < 600 ? v.MR*v.R2 : 599; }, .axis_title="M_{R} #times R^{2} (GeV)",  .def_range={0,600}});
sh.AddNewFillParams("MRR21vlBin",           { .nbin=   6, .bins={0, 100, 200, 300, 400, 500, 600}, .fill=[this] { return v.MR*v.R2_1vl < 600 ? v.MR*v.R2_1vl : 599; }, .axis_title="M_{R} #times R_{no lep}^{2} (GeV)",  .def_range={0,600}});
sh.AddNewFillParams("newMRR2",              { .nbin=   5, .bins={0,  500}, .fill=[this] { return (v.MR-800)*(v.R2-0.08) < 500 ? (v.MR-800)*(v.R2-0.08) : 490; }, .axis_title="(M_{R}-800) #times (R^{2}-0.08) (GeV)",  .def_range={0,500}});
sh.AddNewFillParams("MRR2_hHP",             { .nbin=  15, .bins={    0,    3000}, .fill=[this] { return v.FatJet.HparticleNet1.n >= 1 ? v.MR*v.R2 : -999;                }, .axis_title="M_{R} #times R^{2} (GeV)",  .def_range={0,2400}});
sh.AddNewFillParams("MRR2_hMP",              { .nbin=  15, .bins={    0,    3000}, .fill=[this] { return v.FatJet.HparticleNet2.n >= 1 ? v.MR*v.R2 : -999;                }, .axis_title="M_{R} #times R^{2} (GeV)",  .def_range={0,2400}});
sh.AddNewFillParams("MRR2_hLP",              { .nbin=  15, .bins={    0,    3000}, .fill=[this] { return v.FatJet.HparticleNet3.n >= 1 ? v.MR*v.R2 : -999;                }, .axis_title="M_{R} #times R^{2} (GeV)",  .def_range={0,2400}});
// New improved version
sh.AddNewFillParams("MRNew",                   { .nbin=MR_bins.size()-1, .bins=MR_bins, .fill=[this] { return v.MR;                }, .axis_title="M_{R} (GeV)",          .def_range={0,4000}});
add_unrolled_bins("RazorBinsNew",    "M_{R} (TeV)", "R^{2}", [this] { return v.MR_new/1000; }, [this] { return v.R2_new; }, MR_2D_bins,     R2_2D_bins, merged_razor_bins,     1, 2);
add_unrolled_bins("RazorBinsNewLep", "M_{R} (TeV)", "R^{2}", [this] { return v.MR_new/1000; }, [this] { return v.R2_new; }, MR_2D_bins_lep, R2_2D_bins, merged_razor_bins_lep, 1, 2);
sh.AddNewFillParams("R2New",                   { .nbin=R2_bins.size()-1, .bins=R2_bins, .fill=[this] { return v.R2;                      }, .axis_title="R^{2}",                .def_range={0,1.5}});
sh.AddNewFillParams("TestMRR2",                 { .nbin=  15, .bins={0, 100, 200, 300, 400, 500, 600, 700, 800, 900, 1000, 1100, 1200, 1300, 1400, 3000}, .fill=[this] { return (v.MR)*(v.R2); }, .axis_title="M_{R} #times R^{2} (GeV)",  .def_range={0,3000}});
sh.AddNewFillParams("TestnewMRR2",              { .nbin=  15, .bins={0, 100, 200, 300, 400, 500, 600, 700, 800, 900, 1000, 1100, 1200, 1300, 1400, 3000}, .fill=[this] { return (v.MR-800)*(v.R2-0.08); }, .axis_title="(M_{R}-800) #times (R^{2}-0.08) (GeV)",  .def_range={0,3000}});
//sh.AddNewFillParams("MRR2",                 { .nbin=  15, .bins={    0,    3000}, .fill=[this] { return v.MR*v.R2;                }, .axis_title="M_{R} #times R^{2} (GeV)",  .def_range={0,2400}});
//add_unrolled_bins("UnrolledSR_MRR2", "M_{R}#timesR^{2} (GeV)", "", [this] { return v.MR*v.R2; }, [this] { return v.R2_new; }, MRR2_2D_bins, SR_2D_bins, {}, 0, 0);
// Razor with removed photon
sh.AddNewFillParams("MRNoPho",              { .nbin=MR_bins.size()-1, .bins=MR_bins, .fill=[this] { return v.MR_pho;                }, .axis_title="M_{R, no #gamma} (GeV)",          .def_range={0,4000}});
sh.AddNewFillParams("MRNoPhoBins",          { .nbin=MR_RI.size()-1, .bins=MR_RI,  .fill=[this] { return v.MR_pho;                }, .axis_title="M_{R, no #gamma} (GeV)",          .def_range={300,4000}});
sh.AddNewFillParams("MTRNoPho",             { .nbin=MTR_bins.size()-1, .bins=MTR_bins,      .fill=[this] { return v.MTR_pho;               }, .axis_title="M_{T, no #gamma}^{R} (GeV)",      .def_range={0,2000}});
sh.AddNewFillParams("R2NoPho",              { .nbin=R2_bins.size()-1, .bins=R2_bins, .fill=[this] { return v.R2_pho;                }, .axis_title="R_{no #gamma}^{2}",                .def_range={0,2}});
sh.AddNewFillParams("R2NoPhoBins",          { .nbin=R2_RI.size()-1, .bins=R2_RI,  .fill=[this] { return v.R2_pho;                }, .axis_title="R_{no #gamma}^{2}",                .def_range={0.15,1.5}});

// HT
//sh.AddNewFillParams("HT",                   { .nbin=HT.size()-1, .bins=HT,        .fill=[this] { return v.AK4_Ht;             }, .axis_title="H_{T} (GeV)",                 .def_range={200, 2000}});
sh.AddNewFillParams("HTFine",               { .nbin=  50, .bins={    0,    5000}, .fill=[this] { return v.AK4_Ht;             }, .axis_title="H_{T} (GeV)",                   .def_range={200, 2000}});
sh.AddNewFillParams("HT",                   { .nbin=HT.size()-1, .bins=HT,        .fill=[this] { return v.AK4_Ht;             }, .axis_title="H_{T} (GeV)",                   .def_range={200, 2000}});
sh.AddNewFillParams("HT2DBins",             { .nbin=HT_2D_bins.size()-1, .bins=HT_2D_bins, .fill=[this] { return v.AK4_Ht;             }, .axis_title="H_{T} (GeV)",          .def_range={200, 1500}});
sh.AddNewFillParams("OnlineHT",             { .nbin= 100, .bins={    0,    5000}, .fill=[this] { return v.AK4_HtOnline;       }, .axis_title="H_{T}^{HLT} (GeV)",             .def_range={200, 2000}});
sh.AddNewFillParams("AK8HT",                { .nbin=HT.size()-1, .bins=HT,        .fill=[this] { return v.AK8_Ht;             }, .axis_title="H_{T}^{AK8} (GeV)",             .def_range={0, 2000}});
// MET
sh.AddNewFillParams("METPhi",               { .nbin=  24, .bins={-3.142,  3.142}, .fill=[this] { return v.MET_phi;             }, .axis_title="MET #phi"});
sh.AddNewFillParams("MET",                  { .nbin=MET.size()-1, .bins=MET,      .fill=[this] { return v.MET_pt;              }, .axis_title="#slash{E}_{T} (GeV)",              .def_range={0,2000}});
sh.AddNewFillParams("MET2DBins",            { .nbin=MET_2D_bins.size()-1, .bins=MET_2D_bins, .fill=[this] { return v.MET_pt;   }, .axis_title="#slash{E}_{T} (GeV)",              .def_range={0,600}});
sh.AddNewFillParams("METNoPho",             { .nbin=MET.size()-1, .bins=MET,      .fill=[this] { return std::sqrt(v.MET_pho.Perp2());   }, .axis_title="#slash{E}_{T, no #gamma} (GeV)", .def_range={0,2000}});
sh.AddNewFillParams("METNo1Lep",            { .nbin=MET.size()-1, .bins=MET,      .fill=[this] { return std::sqrt(v.MET_1l.Perp2());    }, .axis_title="#slash{E}_{T,no lep} (GeV)",     .def_range={0,2000}});
sh.AddNewFillParams("METNo1VLep",           { .nbin=MET.size()-1, .bins=MET,      .fill=[this] { return std::sqrt(v.MET_1vl.Perp2());   }, .axis_title="#slash{E}_{T,no lep} (GeV)",     .def_range={0,2000}});
sh.AddNewFillParams("METNo2Lep",            { .nbin=MET.size()-1, .bins=MET,      .fill=[this] { return std::sqrt(v.MET_2l.Perp2());    }, .axis_title="#slash{E}_{T,ll} (GeV)",         .def_range={0,2000}});
sh.AddNewFillParams("METNoDiLep",           { .nbin=MET.size()-1, .bins=MET,      .fill=[this] { return std::sqrt(v.MET_dilep.Perp2()); }, .axis_title="#slash{E}_{T,1l missing} (GeV)",         .def_range={0,2000}});
sh.AddNewFillParams("METFine",              { .nbin=  40, .bins={    0,    2000}, .fill=[this] { return v.MET_pt;                       }, .axis_title="#slash{E}_{T} (GeV)",            .def_range={0,2000}});
sh.AddNewFillParams("PuppiMET",             { .nbin=MET.size()-1, .bins=MET,      .fill=[this] { return v.PuppiMET_pt;                  }, .axis_title="#slash{E}_{T} (GeV)",            .def_range={0,2000}});
sh.AddNewFillParams("RawMET",               { .nbin=MET.size()-1, .bins=MET,      .fill=[this] { return v.RawMET_pt;                    }, .axis_title="#slash{E}_{T} (GeV)",            .def_range={0,2000}});
//sh.AddNewFillParams("TkMET",                { .nbin=MET.size()-1, .bins=MET,      .fill=[this] { return v.TkMET_pt;                     }, .axis_title="#slash{E}_{T} (GeV)",            .def_range={0,2000}});
sh.AddNewFillParams("PFMETOverCaloMET",     { .nbin=100, .bins={-10,10}, .fill=[this] { return v.CaloMET_pt>0 ? std::log(v.MET_pt/v.CaloMET_pt) : 9999; }, .axis_title="ln(PFMET / CaloMET)"});

// Unrolled HT vs AK8Pt1 - For trigger efficiency
add_unrolled_bins("HTJet1AK8Pt",     "p_{T} (GeV)", "H_{T} (TeV)", [this] { return (v.FatJet.JetAK8.n<1) ? -9999. : v.FatJet.JetAK8(0).pt; }, [this] { return v.AK4_Ht/1000; }, Pt_2D_bins,     HT_2D_bins_old, {}, 0, 2);
add_unrolled_bins("HTJet1AK8PtLow",  "p_{T} (GeV)", "H_{T} (TeV)", [this] { return (v.FatJet.JetAK8.n<1) ? -9999. : v.FatJet.JetAK8(0).pt; }, [this] { return v.AK4_Ht/1000; }, PtLow_2D_bins,  HT_2D_bins_old, {}, 0, 2);
add_unrolled_bins("HTJet1AK8PtHigh", "p_{T} (GeV)", "H_{T} (TeV)", [this] { return (v.FatJet.JetAK8.n<1) ? -9999. : v.FatJet.JetAK8(0).pt; }, [this] { return v.AK4_Ht/1000; }, PtHigh_2D_bins, HT_2D_bins_old, {}, 0, 2);
// Unrolled HT vs MET - For 2017-18 trigger efficiency
add_unrolled_bins("HTMET",           "H_{T} (GeV)", "#slash{E}_{T} (GeV)", [this] { return v.AK4_Ht; }, [this] { return v.MET_pt; }, HT_2D_bins,  MET_2D_bins, merged_trigger_bins);
add_unrolled_bins("HT1MET",          "H_{T} (GeV)", "#slash{E}_{T} (GeV)", [this] { return v.AK4_Ht; }, [this] { return v.MET_pt; }, HT1_2D_bins, MET_2D_bins, merged_trigger1_bins);
add_unrolled_bins("HT2MET",          "H_{T} (GeV)", "#slash{E}_{T} (GeV)", [this] { return v.AK4_Ht; }, [this] { return v.MET_pt; }, HT2_2D_bins, MET_2D_bins, merged_trigger2_bins);
add_unrolled_bins("HT3MET",          "H_{T} (GeV)", "#slash{E}_{T} (GeV)", [this] { return v.AK4_Ht; }, [this] { return v.MET_pt; }, HT3_2D_bins, MET_2D_bins, merged_trigger3_bins);
add_unrolled_bins("HTMETPrev",       "H_{T} (GeV)", "#slash{E}_{T} (GeV)", [this] { return v.AK4_Ht; }, [this] { return v.MET_pt; }, {300, 500, 550, 600, 800, 1500, 10000}, {50, 150, 200, 400, 10000});
// HT vs Photon Pt
add_unrolled_bins("HTPhotonPt",      "H_{T} (GeV)", "Photon p_{T} (GeV)", [this] { return v.AK4_Ht; }, [this] { return v.Photon.Select.n<1? -9999 : v.Photon.Select(0).pt; }, HT_2D_bins,  PtPho_2D_bins, {}, 0, 0);
add_unrolled_bins("HT1PhotonPt",     "H_{T} (GeV)", "Photon p_{T} (GeV)", [this] { return v.AK4_Ht; }, [this] { return v.Photon.Select.n<1? -9999 : v.Photon.Select(0).pt; }, HT1_2D_bins,  PtPho_2D_bins, {}, 0, 0);
add_unrolled_bins("HT2PhotonPt",     "H_{T} (GeV)", "Photon p_{T} (GeV)", [this] { return v.AK4_Ht; }, [this] { return v.Photon.Select.n<1? -9999 : v.Photon.Select(0).pt; }, HT2_2D_bins,  PtPho_2D_bins, {}, 0, 0);
add_unrolled_bins("HT3PhotonPt",     "H_{T} (GeV)", "Photon p_{T} (GeV)", [this] { return v.AK4_Ht; }, [this] { return v.Photon.Select.n<1? -9999 : v.Photon.Select(0).pt; }, HT3_2D_bins,  PtPho_2D_bins, {}, 0, 0);
// Unrolled HT vs LeptonPt - For 2017-18 leptonic trigger efficiencies
add_unrolled_bins("HTElePt",         "H_{T} (GeV)", "Ele p_{T} (GeV)", [this] { return v.AK4_Ht; }, [this] { return v.Electron.Select.n<1 ? -9999 : v.Electron.Select(0).pt; }, HT_2D_bins_lep,  ElePt_2D_bins);
add_unrolled_bins("HT1ElePt",        "H_{T} (GeV)", "Ele p_{T} (GeV)", [this] { return v.AK4_Ht; }, [this] { return v.Electron.Select.n<1 ? -9999 : v.Electron.Select(0).pt; }, HT1_2D_bins_lep, ElePt_2D_bins);
add_unrolled_bins("HT2ElePt",        "H_{T} (GeV)", "Ele p_{T} (GeV)", [this] { return v.AK4_Ht; }, [this] { return v.Electron.Select.n<1 ? -9999 : v.Electron.Select(0).pt; }, HT2_2D_bins_lep, ElePt_2D_bins);
add_unrolled_bins("HTMuPt",          "H_{T} (GeV)", "Mu p_{T} (GeV)",  [this] { return v.AK4_Ht; }, [this] { return v.Muon.Select.n<1 ? -9999 : v.Muon.Select(0).pt;       }, HT_2D_bins_lep,  MuPt_2D_bins);
add_unrolled_bins("HT1MuPt",         "H_{T} (GeV)", "Mu p_{T} (GeV)",  [this] { return v.AK4_Ht; }, [this] { return v.Muon.Select.n<1 ? -9999 : v.Muon.Select(0).pt;       }, HT1_2D_bins_lep, MuPt_2D_bins);
add_unrolled_bins("HT2MuPt",         "H_{T} (GeV)", "Mu p_{T} (GeV)",  [this] { return v.AK4_Ht; }, [this] { return v.Muon.Select.n<1 ? -9999 : v.Muon.Select(0).pt;       }, HT2_2D_bins_lep, MuPt_2D_bins);

// DPhi
sh.AddNewFillParams("DeltaPhi",                 { .nbin=DP.size()-1,  .bins=DP,       .fill=[this] { return v.dPhiRazor;               }, .axis_title="#Delta#phi_{megajets}"});
sh.AddNewFillParams("DeltaPhiNoPho",            { .nbin=DP.size()-1,  .bins=DP,       .fill=[this] { return v.dPhiRazorNoPho;          }, .axis_title="#Delta#phi_{megajets, no #gamma}"});
//sh.AddNewFillParams("MinDeltaPhi",              { .nbin=  64, .bins={    0,     3.2}, .fill=[this] { return v.minDeltaPhi;             }, .axis_title="#Delta#phi_{min}"});
sh.AddNewFillParams("MinDeltaPhi",              { .nbin=MDP.size()-1, .bins=MDP,      .fill=[this] { return v.minDeltaPhi;             }, .axis_title="#Delta#phi_{min}"});
sh.AddNewFillParams("MinDeltaPhiNo1Lep",        { .nbin=MDP.size()-1, .bins=MDP,      .fill=[this] { return v.minDeltaPhi_1l;          }, .axis_title="#Delta#phi_{min,no lep}"});
sh.AddNewFillParams("MinDeltaPhiNo1VLep",       { .nbin=MDP.size()-1, .bins=MDP,      .fill=[this] { return v.minDeltaPhi_1vl;         }, .axis_title="#Delta#phi_{min,no lep}"});
sh.AddNewFillParams("MinDeltaPhiNo2Lep",        { .nbin=MDP.size()-1, .bins=MDP,      .fill=[this] { return v.minDeltaPhi_2l;          }, .axis_title="#Delta#phi_{min,ll}"});
sh.AddNewFillParams("MinDeltaPhiNoPho",         { .nbin=MDP.size()-1, .bins=MDP,      .fill=[this] { return v.minDeltaPhi_pho;         }, .axis_title="#Delta#phi_{min, no #gamma}"});
sh.AddNewFillParams("DeltaPhiLLMET",            { .nbin=MDP.size()-1, .bins=MDP,      .fill=[this] { return v.dPhi_2l_met;             }, .axis_title="#Delta#phi (ll, MET)"});
sh.AddNewFillParams("DeltaPhiLLJet",            { .nbin=MDP.size()-1, .bins=MDP,      .fill=[this] { return v.dPhi_2l_jet;             }, .axis_title="#Delta#phi_{min} (ll, jet)"});
sh.AddNewFillParams("DeltaPhiBoostedJetMET",    { .nbin=DP.size()-1,  .bins=DP,       .fill=[this] { return v.dPhiBoostedJetMET;       }, .axis_title="#Delta#phi (AK8 jet, MET)"});
sh.AddNewFillParams("DeltaPhiBoostedJetLep",    { .nbin=DP.size()-1,  .bins=DP,       .fill=[this] { return v.dPhiBoostedJetLep;       }, .axis_title="#Delta#phi (AK8 jet, lep)"});
sh.AddNewFillParams("DeltaPhiBoostedJetLepMET", { .nbin=DP.size()-1,  .bins=DP,       .fill=[this] { return v.dPhiBoostedJetLepMET;    }, .axis_title="#Delta#phi (AK8 jet, lep+MET)"});
sh.AddNewFillParams("DeltaPhiMuonJetMET",       { .nbin=8, .bins={0, 0.4, 0.8, 1.2, 1.6, 2.0, 2.4, 2.74159, 3.1416}, .fill=[this] { return v.dPhiMuonJetMET; }, .axis_title="#Delta#phi (#mu jet, MET)"});
// MT/Mll/MT2
sh.AddNewFillParams("MT",                   { .nbin=  50, .bins={    0,    1000}, .fill=[this] { return v.MT_lepVeto;              }, .axis_title="m_{T} (GeV)",  .def_range={0,500}});
sh.AddNewFillParams("MTSelect",             { .nbin=  50, .bins={    0,    1000}, .fill=[this] { return v.MT;                      }, .axis_title="m_{T} (GeV)",  .def_range={0,500}});
sh.AddNewFillParams("MTTight",              { .nbin=  50, .bins={    0,    1000}, .fill=[this] { return v.MT_lepTight;             }, .axis_title="m_{T} (GeV)",  .def_range={0,500}});
sh.AddNewFillParams("MTNonIso",             { .nbin=  50, .bins={    0,    1000}, .fill=[this] { return v.MT_lepNonIso;            }, .axis_title="m_{T} (GeV)",  .def_range={0,500}});
sh.AddNewFillParams("MTBoost",              { .nbin=  20, .bins={    0,    4000}, .fill=[this] { return v.MT_boost;                }, .axis_title="m_{T,Boost+MET} (GeV)",  .def_range={0,2000}});
sh.AddNewFillParams("Mll",                  { .nbin=  50, .bins={    0,     500}, .fill=[this] { return v.M_2l;                    }, .axis_title="m_{ll} (GeV)", .def_range={0,200}});
sh.AddNewFillParams("MT2",                  { .nbin=  40, .bins={    0,    2000}, .fill=[this] { return v.MT2;                     }, .axis_title="M_{T2} (GeV)",  .def_range={0,1000}});
// SUSY
sh.AddNewFillParams("MGluino",              { .nbin= 121, .bins={-12.5, 3012.5 }, .fill=[this] { return v.susy_mass[0];      }, .axis_title="m_{#tilde{g}} (GeV)",        .def_range={550,2350}});
sh.AddNewFillParams("MSquark",              { .nbin=  81, .bins={-12.5, 2012.5 }, .fill=[this] { return v.susy_mass[0];      }, .axis_title="m_{#tilde{t}} (GeV)",        .def_range={  0,1650}});
sh.AddNewFillParams("MEWK",                 { .nbin=  81, .bins={-12.5, 2012.5 }, .fill=[this] { return v.susy_mass[0];      }, .axis_title="m_{#tilde{#chi}^{#pm}_{1}} (GeV)",        .def_range={  0,1650}});
sh.AddNewFillParams("MLSP",                 { .nbin=  81, .bins={-12.5, 2012.5 }, .fill=[this] { return v.susy_mass[1];     }, .axis_title="m_{#tilde{#chi}^{0}_{1}} (GeV)", .def_range={  0,1650}});
sh.AddNewFillParams("SquarkLSPMassDiff",    { .nbin= 400, .bins={0, 2000 },       .fill=[this] { return v.susy_mass[0]-v.susy_mass[1]; }, .axis_title="m_{#tilde{t}}-m_{#tilde{#chi}^{0}_{1}} (GeV)"});
// AK8 JetN
sh.AddNewFillParams("Jet1AK8Mass",         { .nbin=M.size()-1, .bins=M,           .fill=[this] { return (v.FatJet.JetAK8.n<1) ? -9999. : v.FatJet.JetAK8(0).msoftdrop;      }, .axis_title="Leading AK8 jet m_{Soft-Drop} (GeV)",    .def_range={0, 300}});
sh.AddNewFillParams("Jet2AK8Mass",         { .nbin=M.size()-1, .bins=M,           .fill=[this] { return (v.FatJet.JetAK8.n<2) ? -9999. : v.FatJet.JetAK8(1).msoftdrop;      }, .axis_title="Subleading AK8 jet m_{Soft-Drop} (GeV)", .def_range={0, 300}});
sh.AddNewFillParams("Jet1AK8Pt",           { .nbin=  100, .bins={    0,   10000}, .fill=[this] { return (v.FatJet.JetAK8.n<1) ? -9999. : v.FatJet.JetAK8(0).pt;             }, .axis_title="Leading AK8 jet p_{T} (GeV)",    .def_range={200, 1000}});
sh.AddNewFillParams("Jet1AK8PtBins",       { .nbin=PtB.size()-1, .bins=PtB,       .fill=[this] { return (v.FatJet.JetAK8.n<1) ? -9999. : v.FatJet.JetAK8(0).pt;             }, .axis_title="Leading AK8 jet p_{T} (GeV)",    .def_range={200, 1000}});
sh.AddNewFillParams("Jet2AK8PtBins",       { .nbin=PtB.size()-1, .bins=PtB,       .fill=[this] { return (v.FatJet.JetAK8.n<2) ? -9999. : v.FatJet.JetAK8(1).pt;             }, .axis_title="Subleading AK8 jet p_{T} (GeV)", .def_range={200, 1000}});
sh.AddNewFillParams("Jet1AK8Eta",          { .nbin=   80, .bins={   -4,       4}, .fill=[this] { return (v.FatJet.JetAK8.n<1) ? -9999. : v.FatJet.JetAK8(0).eta;            }, .axis_title="Leading AK8 jet #eta",    .def_range={-3, 3}});
sh.AddNewFillParams("Jet2AK8Eta",          { .nbin=   80, .bins={   -4,       4}, .fill=[this] { return (v.FatJet.JetAK8.n<2) ? -9999. : v.FatJet.JetAK8(1).eta;            }, .axis_title="Subleading AK8 jet #eta", .def_range={-3, 3}});
sh.AddNewFillParams("Jet1AK8Tau32",        { .nbin=   50, .bins={    0,       1}, .fill=[this] { return (v.FatJet.JetAK8.n<1) ? -9999. : v.FatJet.JetAK8(0).tau32;          }, .axis_title="Leading AK8 jet #tau_{32}"});
sh.AddNewFillParams("Jet2AK8Tau32",        { .nbin=   50, .bins={    0,       1}, .fill=[this] { return (v.FatJet.JetAK8.n<2) ? -9999. : v.FatJet.JetAK8(1).tau32;          }, .axis_title="Subleading AK8 jet #tau_{32}"});
sh.AddNewFillParams("Jet1AK8BTagDeepB",    { .nbin=  101, .bins={    0,    1.01}, .fill=[this] { return (v.FatJet.JetAK8.n<1) ? -9999. : v.FatJet.JetAK8(0).maxSubJetDeepB; }, .axis_title="Leading AK8 jet - Max. SubJet DeepB",    .def_range={0,1}});
sh.AddNewFillParams("Jet2AK8BTagDeepB",    { .nbin=  101, .bins={    0,    1.01}, .fill=[this] { return (v.FatJet.JetAK8.n<2) ? -9999. : v.FatJet.JetAK8(1).maxSubJetDeepB; }, .axis_title="Subleading AK8 jet - Max. SubJet DeepB", .def_range={0,1}});

if (debug) std::cout<<"PlottingBase::define_histo_settings: non-special fillparams ok"<<std::endl;


// --------------------------------------------------------------------
//              Special Fill Parameters (not for binning)
// --------------------------------------------------------------------

// ------------------------- Special -----------------------
//     e.g. Efficiencies, averages, fake rates etc.

// Special Y/Z axis parameters:
// Systematics
sh.AddSpecial({ .name="Counts", .name_plus_1d="Syst", .axis="Events / bin", .axis_plus_1d="Systematics variation index"});
//sh.AddSpecial({ .name="SignalSelectionEfficiency",    .name_plus_1d="PassSignalSelection",    .axis="Signal Selection Efficiency", .axis_plus_1d="Pass Signal Selection"});
sh.AddSpecial({ .name="SignalSignificance_T5ttcc",    .name_plus_1d="Bkg_T5ttcc",             .axis="S/#sqrt{S+B} - T5ttcc",        .axis_plus_1d="Background, Signal - T5ttcc"});
sh.AddSpecial({ .name="SignalSignificance_TChiZH",    .name_plus_1d="Bkg_TChiZH",                 .axis="S/#sqrt{S+B} - TChiZH",        .axis_plus_1d="Background, Signal - TChiZH"});







sh.AddNewFillParams("Counts",                         { .nbin= 1+syst_nSyst, .bins={-0.5, syst_nSyst+0.5}, .fill=[&syst_index] { return syst_index; }, .axis_title="Events / bin"});

//sh.AddNewSpecialFillParams("SignalSelectionEfficiency",    { .nbin=    2, .bins={ -0.5,     1.5}, .fill=[&evt_sel] { return evt_sel.pass_all_cuts[((Region::SR_Had_1htop) || (Region::SR_Had_2htop) || Region::SR_Had_V_b_45j || Region::SR_Had_V_b_6j || Region::SR_Had_1V_0b_34j || Region::SR_Had_1V_0b_5j || Region::SR_Had_2V_0b_24j || Region::SR_Had_2V_0b_5j || Region::SR_Had_H_b_45j || Region::SR_Had_H_b_6j || Region::SR_Had_HV_b_6j || Region::SR_Had_H_0b_34j || Region::SR_Had_H_0b_5j || Region::SR_Had_HV_0b_24j || Region::SR_Had_HV_0b_5j || Region::SR_Lep_1htop || Region::SR_Lep_V_b || Region::SR_Lep_V_0b|| Region::SR_Lep_H_b|| Region::SR_Lep_H_0b || Region::SR_Leptop_0htop|| Region::SR_Leptop_1htop|| Region::SR_Lepjet_0V_24j|| Region::SR_Lepjet_0V_5j|| Region::SR_Lepjet_1V_24j|| Region::SR_Lepjet_1V_5j )];}, .axis_title="Signal Selection Efficiency"});
sh.AddNewSpecialFillParams("SignalSignificance_T5ttcc",    { .nbin=    2, .bins={ -0.5,     1.5}, .fill=[] { return Bkg_T5ttcc_opt.index; }, .axis_title="S/#sqrt{S+B} - T5ttcc", .def_range={0,10}});
sh.AddNewSpecialFillParams("SignalSignificance_TChiZH",    { .nbin=    2, .bins={ -0.5,     1.5}, .fill=[] { return Bkg_TChiZH_opt.index; }, .axis_title="S/#sqrt{S+B} - TChiZH", .def_range={0,10}});




// ------------------------- Objects -----------------------


sh.AddNewSpecialFillParams("LepJetTagFakeRate",              { .nbin=2, .bins={-0.5,1.5}, .fill=[this] { return v.FatJet.LepJet.pass[v.FatJet.i];       }, .axis_title="Lep. jet-tagging fake rate",         .def_range={0,2} });
sh.AddNewSpecialFillParams("LepJetMisTagRate",               { .nbin=2, .bins={-0.5,1.5}, .fill=[this] { return v.FatJet.LepJet.pass[v.FatJet.i];       }, .axis_title="Lep. jet-mistagging rate",           .def_range={0,2} });
sh.AddNewSpecialFillParams("LepTopTagFakeRate",              { .nbin=2, .bins={-0.5,1.5}, .fill=[this] { return v.FatJet.LepTop.pass[v.FatJet.i];       }, .axis_title="Lep. top-tagging fake rate",         .def_range={0,2} });
sh.AddNewSpecialFillParams("LepTopMisTagRate",               { .nbin=2, .bins={-0.5,1.5}, .fill=[this] { return v.FatJet.LepTop.pass[v.FatJet.i];       }, .axis_title="Lep. top-mistagging rate",           .def_range={0,2} });
sh.AddNewSpecialFillParams("HadTopTagFakeRate",              { .nbin=2, .bins={-0.5,1.5}, .fill=[this] { return v.FatJet.HadTop.pass[v.FatJet.i];       }, .axis_title="Had. top-tagging fake rate",         .def_range={0,2} });
sh.AddNewSpecialFillParams("HadTopMisTagRate",               { .nbin=2, .bins={-0.5,1.5}, .fill=[this] { return v.FatJet.HadTop.pass[v.FatJet.i];       }, .axis_title="Had. top-mistagging rate",           .def_range={0,2} });
sh.AddNewSpecialFillParams("HadWTagFakeRate",                { .nbin=2, .bins={-0.5,1.5}, .fill=[this] { return v.FatJet.HadW.pass[v.FatJet.i];         }, .axis_title="Had. W-tagging fake rate",           .def_range={0,2} });
sh.AddNewSpecialFillParams("HadWMisTagRate",                 { .nbin=2, .bins={-0.5,1.5}, .fill=[this] { return v.FatJet.HadW.pass[v.FatJet.i];         }, .axis_title="Had. W-mistagging rate",             .def_range={0,2} });
sh.AddNewSpecialFillParams("HadVTagFakeRate",                { .nbin=2, .bins={-0.5,1.5}, .fill=[this] { return v.FatJet.HadV.pass[v.FatJet.i];         }, .axis_title="Had. V-tagging fake rate",           .def_range={0,2} });
sh.AddNewSpecialFillParams("HadVMisTagRate",                 { .nbin=2, .bins={-0.5,1.5}, .fill=[this] { return v.FatJet.HadV.pass[v.FatJet.i];         }, .axis_title="Had. V-mistagging rate",             .def_range={0,2} });
sh.AddNewSpecialFillParams("HadZTagFakeRate",                { .nbin=2, .bins={-0.5,1.5}, .fill=[this] { return v.FatJet.HadZ.pass[v.FatJet.i];         }, .axis_title="Had. Z-tagging fake rate",           .def_range={0,2} });
sh.AddNewSpecialFillParams("HadZMisTagRate",                 { .nbin=2, .bins={-0.5,1.5}, .fill=[this] { return v.FatJet.HadZ.pass[v.FatJet.i];         }, .axis_title="Had. Z-mistagging rate",             .def_range={0,2} });
sh.AddNewSpecialFillParams("HadHTagFakeRate",                { .nbin=2, .bins={-0.5,1.5}, .fill=[this] { return v.FatJet.HadH.pass[v.FatJet.i];         }, .axis_title="Had. h-tagging fake rate",           .def_range={0,2} });
sh.AddNewSpecialFillParams("HadHMisTagRate",                 { .nbin=2, .bins={-0.5,1.5}, .fill=[this] { return v.FatJet.HadH.pass[v.FatJet.i];         }, .axis_title="Had. h-mistagging rate",             .def_range={0,2} });
sh.AddNewSpecialFillParams("MassTagFakeRate",                { .nbin=2, .bins={-0.5,1.5}, .fill=[this] { return v.FatJet.JetAK8Mass.pass[v.FatJet.i];   }, .axis_title="Mass-tagging fake rate",             .def_range={0,2} });
//sh.AddNewSpecialFillParams("NoIsoElectronFakeRate",         { .nbin=2, .bins={-0.5,1.5}, .fill=[this] { return (v.Electron.NoIso.n==0) ? -9999. : v.Electron.NoIso.pass[v.Electron.i];   }, .axis_title="Non isolated electron fake rate",             .def_range={0,2} });
//sh.AddNewSpecialFillParams("NoIsoMuonFakeRate",         { .nbin=2, .bins={-0.5,1.5}, .fill=[this] { return (v.Muon.NoIso.n==0) ? -9999. : v.Muon.NoIso.pass[v.Muon.i];   }, .axis_title="Non isolated muon fake rate",             .def_range={0,2} });
//sh.AddNewSpecialFillParams("NonIsoElectronFakeRate",         { .nbin=2, .bins={-0.5,1.5}, .fill=[this] { return (v.Electron.NonIso.n==0) ? -9999. : v.Electron.NonIso.pass[v.Electron.i];   }, .axis_title="Nonn isolated electron fake rate",             .def_range={0,2} });
//sh.AddNewSpecialFillParams("NonIsoMuonFakeRate",         { .nbin=2, .bins={-0.5,1.5}, .fill=[this] { return (v.Muon.NonIso.n==0) ? -9999. : v.Muon.NonIso.pass[v.Muon.i];   }, .axis_title="Nonn isolated muon fake rate",             .def_range={0,2} });

//sh.AddNewSpecialFillParams("WMassTagFakeRate",            { .nbin=2, .bins={-0.5,1.5}, .fill=[this] { return v.FatJet.WMassTag.pass[v.FatJet.i];        }, .axis_title="W mass-tagging fake rate",      .def_range={0,2} });
//sh.AddNewSpecialFillParams("W0BMassTagFakeRate",          { .nbin=2, .bins={-0.5,1.5}, .fill=[this] { return v.FatJet.WMassTag.pass[v.FatJet.i];        }, .axis_title="W 0b mass-tagging fake rate",   .def_range={0,2} });
//sh.AddNewSpecialFillParams("WAntiTagFakeRate",            { .nbin=2, .bins={-0.5,1.5}, .fill=[this] { return v.FatJet.TightWAntiTag.pass[v.FatJet.i];   }, .axis_title="W anti-tagging fake rate",      .def_range={0,2} });
//sh.AddNewSpecialFillParams("TopMassTagFakeRate",          { .nbin=2, .bins={-0.5,1.5}, .fill=[this] { return v.FatJet.HadTopMassTag.pass[v.FatJet.i];   }, .axis_title="Top mass-tagging fake rate",    .def_range={0,2} });
//sh.AddNewSpecialFillParams("Top0BMassTagFakeRate",        { .nbin=2, .bins={-0.5,1.5}, .fill=[this] { return v.FatJet.HadTop0BMassTag.pass[v.FatJet.i]; }, .axis_title="Top 0b mass-tagging fake rate", .def_range={0,2} });
//sh.AddNewSpecialFillParams("TopAntiTagFakeRate",          { .nbin=2, .bins={-0.5,1.5}, .fill=[this] { return v.FatJet.HadTop0BAntiTag.pass[v.FatJet.i]; }, .axis_title="Top anti-tagging fake rate",    .def_range={0,2} });
//sh.AddNewSpecialFillParams("TopTagEfficiency",            { .nbin=2, .bins={-0.5,1.5}, .fill=[this] { return v.FatJet.HadTopTag.pass[v.FatJet.i];            }, .axis_title="Top-tagging Efficiency" });
//// Same with other JES correction
//sh.AddNewSpecialFillParams("WTagOtherFakeRate",           { .nbin=2, .bins={-0.5,1.5}, .fill=[this] { return v.FatJet.OtherTightWTag.pass[v.FatJet.i];       }, .axis_title="W-tagging uncorr fake rate",           .def_range={0,2} });
//sh.AddNewSpecialFillParams("W0BMassTagOtherFakeRate",     { .nbin=2, .bins={-0.5,1.5}, .fill=[this] { return v.FatJet.OtherWMassTag.pass[v.FatJet.i];        }, .axis_title="W 0b mass-tagging uncorr fake rate",   .def_range={0,2} });
//sh.AddNewSpecialFillParams("WAntiTagOtherFakeRate",       { .nbin=2, .bins={-0.5,1.5}, .fill=[this] { return v.FatJet.OtherTightWAntiTag.pass[v.FatJet.i];   }, .axis_title="W anti-tagging uncorr fake rate",      .def_range={0,2} });
//sh.AddNewSpecialFillParams("TopTagOtherFakeRate",         { .nbin=2, .bins={-0.5,1.5}, .fill=[this] { return v.FatJet.OtherHadTopTag.pass[v.FatJet.i];       }, .axis_title="Top-tagging L2L3 corr fake rate",         .def_range={0,2} });
//sh.AddNewSpecialFillParams("TopMassTagOtherFakeRate",     { .nbin=2, .bins={-0.5,1.5}, .fill=[this] { return v.FatJet.OtherHadTopMassTag.pass[v.FatJet.i];   }, .axis_title="Top mass-tagging L2L3 corr fake rate",    .def_range={0,2} });
//sh.AddNewSpecialFillParams("Top0BMassTagOtherFakeRate",   { .nbin=2, .bins={-0.5,1.5}, .fill=[this] { return v.FatJet.OtherHadTop0BMassTag.pass[v.FatJet.i]; }, .axis_title="Top 0b mass-tagging L2L3 corr fake rate", .def_range={0,2} });
//sh.AddNewSpecialFillParams("TopAntiTagOtherFakeRate",     { .nbin=2, .bins={-0.5,1.5}, .fill=[this] { return v.FatJet.OtherHadTop0BAntiTag.pass[v.FatJet.i]; }, .axis_title="Top anti-tagging L2L3 corr fake rate",    .def_range={0,2} });

// Photons
sh.AddNewSpecialFillParams("DirectFraction",       { .nbin=    2, .bins={ -0.5,     1.5}, .fill=[this] { return v.Photon().matchGenPromptDirect; }, .axis_title="#splitline{Direct}{Direct+Fragmentation}",        .def_range={0,1} });
// MC purity
sh.AddNewSpecialFillParams("PhotonPurity",         { .nbin=    2, .bins={ -0.5,     1.5}, .fill=[this] {
		if (!v.isData&&v.Photon.Select.n==1) return int(!v.Photon.Select(0).matchGenFake);
		return -9999;
		}, .axis_title="Photon purity",        .def_range={0,1} });

// Gen particle truth
sh.AddNewSpecialFillParams("HadWTaggingEfficiency",       { .nbin=2, .bins={-0.5,1.5}, .fill=[this] { return  v.GenPart().passHadWTag;            }, .axis_title="Had. W-tagging efficiency",   .def_range={0,2} });
sh.AddNewSpecialFillParams("HadZTaggingEfficiency",       { .nbin=2, .bins={-0.5,1.5}, .fill=[this] { return  v.GenPart().passHadZTag;            }, .axis_title="Had. Z-tagging efficiency",   .def_range={0,2} });
sh.AddNewSpecialFillParams("HadVTaggingEfficiency",       { .nbin=2, .bins={-0.5,1.5}, .fill=[this] { return  (v.GenPart().passHadZTag||v.GenPart().passHadWTag);   }, .axis_title="Had. V-tagging efficiency",   .def_range={0,2} });
sh.AddNewSpecialFillParams("HadHTaggingEfficiency",       { .nbin=2, .bins={-0.5,1.5}, .fill=[this] { return  v.GenPart().passHadHTag;            }, .axis_title="Had. H-tagging efficiency",   .def_range={0,2} });
sh.AddNewSpecialFillParams("HadTopTaggingEfficiency",     { .nbin=2, .bins={-0.5,1.5}, .fill=[this] { return  v.GenPart().passHadTopTag;          }, .axis_title="Had. top-tagging efficiency", .def_range={0,2} });
sh.AddNewSpecialFillParams("LepTopTaggingEfficiency",     { .nbin=2, .bins={-0.5,1.5}, .fill=[this] { return  v.GenPart().passLepTopTag;          }, .axis_title="Lep. top-tagging efficiency", .def_range={0,2} });
//sh.AddNewSpecialFillParams("WMassTaggingEfficiency",      { .nbin=2, .bins={-0.5,1.5}, .fill=[this] { return  v.GenPart().passHadWMassTag;        }, .axis_title="Hadronic W mass-tagging Efficiency", .def_range={0,2} });
//sh.AddNewSpecialFillParams("HadTopMassTaggingEfficiency", { .nbin=2, .bins={-0.5,1.5}, .fill=[this] { return  v.GenPart().passHadTopMassTag;      }, .axis_title="Top mass-tagging Efficiency",        .def_range={0,2} });
sh.AddNewSpecialFillParams("LostLeptonRate",              { .nbin=2, .bins={-0.5,1.5}, .fill=[this] { return !v.GenPart().passLepVeto;            }, .axis_title="Lost lepton rate", .def_range={0,3} });
sh.AddNewSpecialFillParams("LepNoIsoEfficiency",          { .nbin=2, .bins={-0.5,1.5}, .fill=[this] { return  v.GenPart().passLepNoIso;           }, .axis_title="Tight lepton efficiency (no iso.)", .def_range={0,3} });
sh.AddNewSpecialFillParams("LepNonIsoEfficiency",         { .nbin=2, .bins={-0.5,1.5}, .fill=[this] { return  v.GenPart().passLepNonIso;          }, .axis_title="Tight lepton efficiency", .def_range={0,3} });
sh.AddNewSpecialFillParams("JetFindingEfficiency",        { .nbin=2, .bins={-0.5,1.5}, .fill=[this] { return  v.GenPart().matchAK8;               }, .axis_title="Jet finding Efficiency" });
sh.AddNewSpecialFillParams("EleCBVetoEfficiency",         { .nbin=2, .bins={-0.5,1.5}, .fill=[this] { return  v.GenPart().passEleCBVeto;          }, .axis_title="Electron (CB-Veto) efficiency",   .def_range={0,2} });
sh.AddNewSpecialFillParams("EleCBVetoNoIsoEfficiency",    { .nbin=2, .bins={-0.5,1.5}, .fill=[this] { return  v.GenPart().passEleCBVetoNoIso;     }, .axis_title="Electron (CB-Veto-NoIso) efficiency",   .def_range={0,2} });
sh.AddNewSpecialFillParams("MuonCBLooseEfficiency",       { .nbin=2, .bins={-0.5,1.5}, .fill=[this] { return  v.GenPart().passMuoCBLoose;         }, .axis_title="Muon (CB-Loose) efficiency",   .def_range={0,2} });
sh.AddNewSpecialFillParams("MuonCBLooseNoIsoEfficiency",  { .nbin=2, .bins={-0.5,1.5}, .fill=[this] { return  v.GenPart().passMuoCBLooseNoIso;    }, .axis_title="Muon (CB-Loose-NoIso) efficiency",   .def_range={0,2} });
sh.AddNewSpecialFillParams("MuonCBMediumEfficiency",      { .nbin=2, .bins={-0.5,1.5}, .fill=[this] { return  v.GenPart().passMuoCBMedium;        }, .axis_title="Muon (CB-Medium) efficiency",   .def_range={0,2} });
sh.AddNewSpecialFillParams("MuonCBMediumNoIsoEfficiency", { .nbin=2, .bins={-0.5,1.5}, .fill=[this] { return  v.GenPart().passMuoCBMediumNoIso;   }, .axis_title="Muon (CB-Medium-NoIso) efficiency",   .def_range={0,2} });

// ---------------------- Event variables ------------------

// Event vairables





sh.AddNewSpecialFillParams("SignalSignificance_TChiWW",  { .nbin=    2, .bins={ -0.5,     1.5}, .fill=[] { return Bkg_TChiWW_opt.index; }, .axis_title="S/#sqrt{S+B} - TChiWW", .def_range={0,10}});
//sh.AddNewSpecialFillParams("SignalSignificance_T5tttt",    { .nbin=    2, .bins={ -0.5,     1.5}, .fill=[] { return Bkg_T5tttt_opt.index; }, .axis_title="S/#sqrt{S+B} - T5tttt", .def_range={0,10}});
//sh.AddNewSpecialFillParams("SignalSignificance_T1tttt",    { .nbin=    2, .bins={ -0.5,     1.5}, .fill=[] { return Bkg_T1tttt_opt.index; }, .axis_title="S/#sqrt{S+B} - T1tttt", .def_range={0,10}});
sh.AddNewSpecialFillParams("SignalSignificance_TChiWZ",    { .nbin=    2, .bins={ -0.5,     1.5}, .fill=[] { return Bkg_TChiWZ_opt.index; }, .axis_title="S/#sqrt{S+B} - TChiWZ", .def_range={0,10}});
//sh.AddNewSpecialFillParams("SignalSignificance_T1ttbb",    { .nbin=    2, .bins={ -0.5,     1.5}, .fill=[] { return Bkg_T1ttbb_opt.index; }, .axis_title="S/#sqrt{S+B} - T1ttbb", .def_range={0,10}});
sh.AddNewSpecialFillParams("SignalSignificance_T5ttcc",      { .nbin=    2, .bins={ -0.5,     1.5}, .fill=[] { return Bkg_T5ttcc_opt.index;   }, .axis_title="S/#sqrt{S+B} - T5ttcc",   .def_range={0,10}});

// ------------------------- Trigger -----------------------

sh.AddNewSpecialFillParams("HLTEff_AK8PFJet360",             { .nbin=    2, .bins={ -0.5,     1.5}, .fill=[this] { return v.HLT_AK8PFJet360_TrimMass30;                     }, .axis_title="#epsilon_{HLT_AK8PFJet360_TrimMass30}",                   .def_range={0,1} });
sh.AddNewSpecialFillParams("HLTEff_AK8PFJet450",             { .nbin=    2, .bins={ -0.5,     1.5}, .fill=[this] { return v.HLT_AK8PFJet450;                                }, .axis_title="#epsilon_{HLT_AK8PFJet450}",                              .def_range={0,1} });
sh.AddNewSpecialFillParams("HLTEff_AK8PFHT750_TrimMass50",   { .nbin=    2, .bins={ -0.5,     1.5}, .fill=[this] { return v.HLT_AK8PFHT750_TrimMass50;                      }, .axis_title="#epsilon_{HLT_AK8PFHT750_TrimMass50}",          .def_range={0,1} });
sh.AddNewSpecialFillParams("HLTEff_PFHT1050",                 { .nbin=    2, .bins={ -0.5,     1.5}, .fill=[this] { return v.HLT_PFHT1050==1;                               }, .axis_title="#epsilon_{HLT_PFHT1050}",                                  .def_range={0,1} });
//sh.AddNewSpecialFillParams("HLTEff_AK8DiPFJet250_200",       { .nbin=    2, .bins={ -0.5,     1.5}, .fill=[this] { return v.HLT_AK8DiPFJet250_200_TrimMass30_BTagCSV_p20; }, .axis_title="#epsilon_{HLT_AK8DiPFJet250_200_TrimMass30_BTagCSV_p20}", .def_range={0,1} });
//sh.AddNewSpecialFillParams("HLTEff_Rsq0p25",                 { .nbin=    2, .bins={ -0.5,     1.5}, .fill=[this] { return v.HLT_Rsq0p25;                                  }, .axis_title="#epsilon_{HLT_Rsq0p25}",                                  .def_range={0,1} });
//sh.AddNewSpecialFillParams("HLTEff_RsqMR270_Rsq0p09_MR200",  { .nbin=    2, .bins={ -0.5,     1.5}, .fill=[this] { return v.HLT_RsqMR270_Rsq0p09_MR200;                   }, .axis_title="#epsilon_{HLT_RsqMR270_Rsq0p09_MR200}",                   .def_range={0,1} });
sh.AddNewSpecialFillParams("HLTEff_AK8PFHT750orPFHT1050",     { .nbin=    2, .bins={ -0.5,     1.5}, .fill=[this] { return v.HLT_AK8PFHT750_TrimMass50==1 || v.HLT_PFHT1050==1;                }, .axis_title="#epsilon_{HLT_AK8PFHT750 OR HLT_PFHT1050}",  .def_range={0,1} });
//sh.AddNewSpecialFillParams("HLTEff_PFJet450orPFHT1050",       { .nbin=    2, .bins={ -0.5,     1.5}, .fill=[this] { return v.HLT_PFJet450==1 || v.HLT_PFHT1050==1;                                       }, .axis_title="#epsilon_{HLT_PFJet450 OR HLT_PFHT1050}",    .def_range={0,1} });
sh.AddNewSpecialFillParams("HLTEff_AK8PFJet450orPFHT1050",    { .nbin=    2, .bins={ -0.5,     1.5}, .fill=[this] { return v.HLT_AK8PFJet450==1 || v.HLT_PFHT1050==1;                                    }, .axis_title="#epsilon_{HLT_AK8PFJet450 OR HLT_PFHT1050}", .def_range={0,1} });
sh.AddNewSpecialFillParams("HLTEff_AK8PFJet450orAK8PFHT750", { .nbin=    2, .bins={ -0.5,     1.5}, .fill=[this] { return v.HLT_AK8PFJet450==1 || v.HLT_AK8PFHT750_TrimMass50==1;                                    }, .axis_title="#epsilon_{HLT_AK8PFJet450 OR HLT_AK8PFHT750}", .def_range={0,1} });
sh.AddNewSpecialFillParams("HLTEff_AK8PFJet360orPFHT1050",    { .nbin=    2, .bins={ -0.5,     1.5}, .fill=[this] { return v.HLT_AK8PFJet360_TrimMass30==1 || v.HLT_PFHT1050==1;                         }, .axis_title="#epsilon_{HLT_AK8PFJet360 OR HLT_PFHT1050}",     .def_range={0,1} });
sh.AddNewSpecialFillParams("HLTEff_AK8PFJet360orAK8PFHT750", { .nbin=    2, .bins={ -0.5,     1.5}, .fill=[this] { return v.HLT_AK8PFJet360_TrimMass30==1 || v.HLT_AK8PFHT750_TrimMass50==1; }, .axis_title="#epsilon_{HLT_AK8PFJet360 OR HLT_AK8PFHT750}",  .def_range={0,1} });
sh.AddNewSpecialFillParams("HLTEff_PFHT1050",                  { .nbin=    2, .bins={ -0.5,     1.5}, .fill=[this] { return v.HLT_PFHT1050==1;                             }, .axis_title="#epsilon_{HLT_PFHT1050}",                 .def_range={0,1} });
sh.AddNewSpecialFillParams("HLTEff_PFMET120_PFMHT120",         { .nbin=    2, .bins={ -0.5,     1.5}, .fill=[this] { return v.HLT_PFMET120_PFMHT120_IDTight==1;            }, .axis_title="#epsilon_{HLT_PFMET120_PFMHT120}",        .def_range={0,1} });
sh.AddNewSpecialFillParams("HLTEff_PFMETNoMu120_PFMHTNoMu120", { .nbin=    2, .bins={ -0.5,     1.5}, .fill=[this] { return v.HLT_PFMETNoMu120_PFMHTNoMu120_IDTight==1;    }, .axis_title="#epsilon_{HLT_PFMETNoMu120_PFMHTNoMu120}",.def_range={0,1} });
sh.AddNewSpecialFillParams("HLTEff_PFMETTypeOne120_PFMHT120",  { .nbin=    2, .bins={ -0.5,     1.5}, .fill=[this] { return v.HLT_PFMETTypeOne120_PFMHT120_IDTight==1;     }, .axis_title="#epsilon_{HLT_PFMETTypeOne120_PFMHT120}", .def_range={0,1} });
sh.AddNewSpecialFillParams("HLTEff_PFHT500_PFMET100_PFMHT100", { .nbin=    2, .bins={ -0.5,     1.5}, .fill=[this] { return v.HLT_PFHT500_PFMET100_PFMHT100_IDTight==1;    }, .axis_title="#epsilon_{HLT_PFHT500_PFMET100_PFMHT100}",.def_range={0,1} });
sh.AddNewSpecialFillParams("HLTEff_PFHT700_PFMET85_PFMHT85",   { .nbin=    2, .bins={ -0.5,     1.5}, .fill=[this] { return v.HLT_PFHT700_PFMET85_PFMHT85_IDTight==1;      }, .axis_title="#epsilon_{HLT_PFHT700_PFMET85_PFMHT85}",  .def_range={0,1} });
sh.AddNewSpecialFillParams("HLTEff_PFHT800_PFMET75_PFMHT75",   { .nbin=    2, .bins={ -0.5,     1.5}, .fill=[this] { return v.HLT_PFHT800_PFMET75_PFMHT75_IDTight==1;      }, .axis_title="#epsilon_{HLT_PFHT800_PFMET75_PFMHT75}",  .def_range={0,1} });
sh.AddNewSpecialFillParams("HLTEff_HT_MET_or_HT",           { .nbin=    2, .bins={ -0.5,     1.5}, .fill=[this] {
		return 
		v.HLT_PFHT1050==1 ||
		//v.HLT_PFMET120_PFMHT120_IDTight==1 ||
		//v.HLT_PFMETNoMu120_PFMHTNoMu120_IDTight==1 ||
		//v.HLT_PFMETTypeOne120_PFMHT120_IDTight==1 ||
		v.HLT_PFHT500_PFMET100_PFMHT100_IDTight==1 || 
		v.HLT_PFHT700_PFMET85_PFMHT85_IDTight==1 ||
		v.HLT_PFHT800_PFMET75_PFMHT75_IDTight==1;
		}, .axis_title="#epsilon_{HT*_MET* OR HT1050}",               .def_range={0,1} });
sh.AddNewSpecialFillParams("HLTEff_AllMET_or_HT_MET_or_HT", { .nbin=    2, .bins={ -0.5,     1.5}, .fill=[this] { 
		return 
		v.HLT_PFHT1050==1 ||
		v.HLT_PFMET120_PFMHT120_IDTight==1 ||
		v.HLT_PFMETNoMu120_PFMHTNoMu120_IDTight==1 ||
		v.HLT_PFMETTypeOne120_PFMHT120_IDTight==1 ||
		v.HLT_PFHT500_PFMET100_PFMHT100_IDTight==1 || 
		v.HLT_PFHT700_PFMET85_PFMHT85_IDTight==1 ||
		v.HLT_PFHT800_PFMET75_PFMHT75_IDTight==1;    
		}, .axis_title="#epsilon_{AllMET120 OR HT*_MET* OR HT1050}",  .def_range={0,1} });
// Leptonic triggers
sh.AddNewSpecialFillParams("HLTEff_Mu15_HT450",      { .nbin=    2, .bins={ -0.5,     1.5}, .fill=[this] { return v.HLT_Mu15_IsoVVVL_PFHT450==1;      }, .axis_title="#epsilon_{Mu15_HT450}",  .def_range={0,1} });
sh.AddNewSpecialFillParams("HLTEff_IsoMu27",         { .nbin=    2, .bins={ -0.5,     1.5}, .fill=[this] { return v.HLT_IsoMu27==1;                   }, .axis_title="#epsilon_{IsoMu27}",     .def_range={0,1} });
sh.AddNewSpecialFillParams("HLTEff_Mu50",            { .nbin=    2, .bins={ -0.5,     1.5}, .fill=[this] { return v.HLT_Mu50==1;                      }, .axis_title="#epsilon_{Mu50}",        .def_range={0,1} });
sh.AddNewSpecialFillParams("HLTEff_Ele15_HT450",     { .nbin=    2, .bins={ -0.5,     1.5}, .fill=[this] { return v.HLT_Ele15_IsoVVVL_PFHT450==1;     }, .axis_title="#epsilon_{Ele15_HT450}", .def_range={0,1} });
sh.AddNewSpecialFillParams("HLTEff_Ele35",           { .nbin=    2, .bins={ -0.5,     1.5}, .fill=[this] { return v.HLT_Ele35_WPTight_Gsf==1;         }, .axis_title="#epsilon_{Ele35}",       .def_range={0,1} });
sh.AddNewSpecialFillParams("HLTEff_Ele115",          { .nbin=    2, .bins={ -0.5,     1.5}, .fill=[this] { return v.HLT_Ele115_CaloIdVT_GsfTrkIdT==1; }, .axis_title="#epsilon_{Ele115}",      .def_range={0,1} });
sh.AddNewSpecialFillParams("HLTEff_IsoMu27_or_Mu50", { .nbin=    2, .bins={ -0.5,     1.5}, .fill=[this] { return 
		v.HLT_IsoMu27==1 ||
		v.HLT_Mu50==1;
		}, .axis_title="#epsilon_{IsoMu27 OR Mu50}",                .def_range={0,1} });
sh.AddNewSpecialFillParams("HLTEff_IsoMu27_or_Mu50_or_Mu15_HT450",  { .nbin=    2, .bins={ -0.5,     1.5}, .fill=[this] { return
		v.HLT_IsoMu27==1 ||
		v.HLT_Mu50==1 ||
		v.HLT_Mu15_IsoVVVL_PFHT450==1;
		}, .axis_title="#epsilon_{IsoMu27 OR Mu50 OR Mu15_HT450}",  .def_range={0,1} });
sh.AddNewSpecialFillParams("HLTEff_Ele35_or_Ele115",                { .nbin=    2, .bins={ -0.5,     1.5}, .fill=[this] { return 
		v.HLT_Ele35_WPTight_Gsf==1 ||
		v.HLT_Ele115_CaloIdVT_GsfTrkIdT==1;
		}, .axis_title="#epsilon_{Ele35 OR Ele115}",                .def_range={0,1} });
sh.AddNewSpecialFillParams("HLTEff_Ele35_or_Ele115_or_Ele15_HT450", { .nbin=    2, .bins={ -0.5,     1.5}, .fill=[this] { return 
		v.HLT_Ele35_WPTight_Gsf==1 ||
		v.HLT_Ele115_CaloIdVT_GsfTrkIdT==1 ||
		v.HLT_Ele15_IsoVVVL_PFHT450==1;
		}, .axis_title="#epsilon_{Ele35 OR Ele115 OR Ele15_HT450}", .def_range={0,1} });
sh.AddNewSpecialFillParams("HLTEff_Hadronic", { .nbin=    2, .bins={ -0.5,     1.5}, .fill=[this] {
		if (v.year==2016) {
		return
		// JetHT
		v.HLT_PFHT800==1 ||
		v.HLT_PFHT900==1 ||
		v.HLT_AK8PFJet450==1 ||
		// MET
		v.HLT_PFMET110_PFMHT110_IDTight==1 ||
		v.HLT_PFMETNoMu110_PFMHTNoMu110_IDTight==1 ||
		// HTMHT
		v.HLT_PFHT300_PFMET110==1;
		} else {
		return
		// JetHT
		v.HLT_PFHT1050==1 ||
		v.HLT_AK8PFJet500==1 ||
		// MET
		v.HLT_PFMET120_PFMHT120_IDTight==1 ||
		v.HLT_PFMET120_PFMHT120_IDTight_PFHT60==1 ||
		v.HLT_PFMETNoMu120_PFMHTNoMu120_IDTight==1 ||
		v.HLT_PFMETNoMu120_PFMHTNoMu120_IDTight_PFHT60==1 ||
		v.HLT_PFHT500_PFMET100_PFMHT100_IDTight==1 || 
		v.HLT_PFHT700_PFMET85_PFMHT85_IDTight==1 ||
		v.HLT_PFHT800_PFMET75_PFMHT75_IDTight==1;
		}
}, .axis_title="#epsilon_{MET120 OR HT*_MET* OR HT*}",     .def_range={0,1} });
sh.AddNewSpecialFillParams("HLTEff_SingleMu", { .nbin=    2, .bins={ -0.5,     1.5}, .fill=[this] { 
		if (v.year==2016) return
		v.HLT_Mu15_IsoVVVL_PFHT350==1 ||
		v.HLT_Mu15_IsoVVVL_PFHT400==1 ||
		v.HLT_Mu15_IsoVVVL_PFHT450==1 ||
		v.HLT_Mu15_IsoVVVL_PFHT600==1 ||
		v.HLT_IsoMu24==1 ||
		v.HLT_IsoTkMu24==1 ||
		v.HLT_Mu50==1 ||
		v.HLT_TkMu50==1 ||
		v.HLT_Mu55==1;
		else return
		v.HLT_Mu15_IsoVVVL_PFHT350==1 ||
		v.HLT_Mu15_IsoVVVL_PFHT400==1 ||
		v.HLT_Mu15_IsoVVVL_PFHT450==1 ||
		v.HLT_Mu15_IsoVVVL_PFHT600==1 ||
		v.HLT_IsoMu27==1 ||
		v.HLT_IsoTkMu27==1 ||
		v.HLT_Mu50==1 ||
		v.HLT_TkMu50==1||
		v.HLT_Mu55==1 ||
		v.HLT_OldMu100==1 ||
		v.HLT_TkMu100==1;
}, .axis_title="#epsilon_{Single muon}", .def_range={0,1} });
sh.AddNewSpecialFillParams("HLTEff_SingleEle", { .nbin=    2, .bins={ -0.5,     1.5}, .fill=[this] { 
		if (v.year==2016) return
		v.HLT_Ele15_IsoVVVL_PFHT350==1 ||
		v.HLT_Ele15_IsoVVVL_PFHT400==1 ||
		v.HLT_Ele15_IsoVVVL_PFHT450==1 ||
		v.HLT_Ele15_IsoVVVL_PFHT600==1 ||
		v.HLT_Ele27_WPTight_Gsf==1 ||
		v.HLT_Ele30_WPTight_Gsf==1 ||
		v.HLT_Ele32_WPTight_Gsf==1 ||
		v.HLT_Ele105_CaloIdVT_GsfTrkIdT==1 ||
		v.HLT_Ele115_CaloIdVT_GsfTrkIdT==1;
		else return
		v.HLT_Ele15_IsoVVVL_PFHT350==1 ||
		v.HLT_Ele15_IsoVVVL_PFHT400==1 ||
		v.HLT_Ele15_IsoVVVL_PFHT450==1 ||
		v.HLT_Ele15_IsoVVVL_PFHT600==1 ||
		v.HLT_Ele32_WPTight_Gsf==1 ||
		v.HLT_Ele35_WPTight_Gsf==1 ||
		v.HLT_Ele38_WPTight_Gsf==1 ||
		v.HLT_Ele105_CaloIdVT_GsfTrkIdT==1 ||
		v.HLT_Ele115_CaloIdVT_GsfTrkIdT==1;
}, .axis_title="#epsilon_{Single electron}", .def_range={0,1} });
sh.AddNewSpecialFillParams("HLTEff_SinglePho", { .nbin=    2, .bins={ -0.5,     1.5}, .fill=[this] { 
		if (v.year==2016) return v.HLT_Photon175==1;
		else return v.HLT_Photon200==1;
		}, .axis_title="#epsilon_{Single photon}", .def_range={0,1} });

if (debug) std::cout<<"PlottingBase::define_histo_settings: special fillparams ok"<<std::endl;

// ----------------------- ROC Curves ----------------------

// Leptons
// GenParticles for GenTruth matching
std::map<std::string, std::function<int()> > gen_leptons;
gen_leptons["EleFromW"]           = [this] { return (int)v.Electron().matchGenEleFromW; };
gen_leptons["MuFromW"]            = [this] { return (int)v.Muon().matchGenMuFromW; };
gen_leptons["EleFromTop"]         = [this] { return (int)v.Electron().matchGenEleFromTop; };
gen_leptons["EleNuFromTop"]       = [this] { return (int)v.Electron().nuMatchGenEleNuFromTop; };
gen_leptons["MuFromTop"]          = [this] { return (int)v.Muon().matchGenMuFromTop; };
//   gen_leptons["TauFromTop"]         = [this] { return (int)v.Tau().matchGenTauFromTop; };
gen_leptons["MuNuFromTop"]        = [this] { return (int)v.Muon().nuMatchGenMuNuFromTop; };
gen_leptons["EleFromHardProcess"] = [this] { return (int)v.Electron().matchGenEleFromHardProcess; };
gen_leptons["MuFromHardProcess"]  = [this] { return (int)v.Muon().matchGenMuFromHardProcess; };
// GenTruth for Leptons
for (const auto& genp : gen_leptons) for (const auto& bm : all_benchmarks)
	sh.AddNewFillParams(genp.first+"_"+bm.first, { .nbin= 2, .bins={-0.5,1.5}, .fill=[genp,bm] { int signal = bm.second(); return signal==1 ? genp.second() : signal; }});

	// cuts not for comparison
	sh.AddNewFillParams("elept5_cut",           { .nbin=1,  .bins={5, 5000}, .fill=[this] { return v.Electron().pt; }, .axis_title="p_{T}^{e}", .def_range={5, 5000}});
	sh.AddNewFillParams("elept10_cut",          { .nbin=1,  .bins={10,5000}, .fill=[this] { return v.Electron().pt; }, .axis_title="p_{T}^{e}", .def_range={10,5000}});
	sh.AddNewFillParams("elept30_cut",          { .nbin=1,  .bins={30,5000}, .fill=[this] { return v.Electron().pt; }, .axis_title="p_{T}^{e}", .def_range={30,5000}});
	sh.AddNewFillParams("mupt5_cut",            { .nbin=1,  .bins={5 ,5000}, .fill=[this] { return v.Muon().pt; }, .axis_title="p_{T}^{#mu}", .def_range={5, 5000}});
	sh.AddNewFillParams("mupt10_cut",           { .nbin=1,  .bins={10,5000}, .fill=[this] { return v.Muon().pt; }, .axis_title="p_{T}^{#mu}", .def_range={10,5000}});
	sh.AddNewFillParams("mupt30_cut",           { .nbin=1,  .bins={30,5000}, .fill=[this] { return v.Muon().pt; }, .axis_title="p_{T}^{#mu}", .def_range={30,5000}});
	sh.AddNewFillParams("eleeta_veto_cut",      { .nbin=1,  .bins={1,2}, .fill=[this]     { return std::abs(v.Electron().eta)<2.5; }, .axis_title="#eta_{e}", .def_range={1,2}});
	sh.AddNewFillParams("eleeta_cut",           { .nbin=1,  .bins={2,3}, .fill=[this] { 
			double abseta = std::abs(v.Electron().eta);
			if      (abseta>=2.5)                 return 0;
			else if (abseta>=1.442&&abseta<1.556) return 1;
			else return 2; }, .axis_title="#eta_{e}", .def_range={2,3}});
	sh.AddNewFillParams("mueta_cut",            { .nbin=1,  .bins={1,2}, .fill=[this] { return std::abs(v.Muon().eta)<2.4; }, .axis_title="#eta_{#mu}", .def_range={1,2}});
	sh.AddNewFillParams("eleip_loose_cut",      { .nbin=1,  .bins={1,2}, .fill=[this] { return std::abs(v.Electron().dz)<0.50&&std::abs(v.Electron().dxy)<0.2; }, .axis_title="vtx. d_{xy,e}/d_{z,e}", .def_range={1,2}});
	sh.AddNewFillParams("eleip_medium_cut",     { .nbin=1,  .bins={1,2}, .fill=[this] { return std::abs(v.Electron().dz)<0.10&&std::abs(v.Electron().dxy)<0.05; }, .axis_title="vtx. d_{xy,e}/d_{z,e}", .def_range={1,2}});
	sh.AddNewFillParams("eleip_tight_cut",      { .nbin=1,  .bins={1,2}, .fill=[this] { return std::abs(v.Electron().dz)<0.10&&std::abs(v.Electron().dxy)<0.05&&v.Electron().sip3d<4; }, .axis_title="vtx. d_{xy,e}/d_{z,e}", .def_range={1,2}});
	sh.AddNewFillParams("muip_loose_cut",       { .nbin=1,  .bins={1,2}, .fill=[this] { return std::abs(v.Muon().dz)<0.50&&std::abs(v.Muon().dxy)<0.2; }, .axis_title="vtx. d_{xy,#mu}/d_{z,#mu}", .def_range={1,2}});
	sh.AddNewFillParams("muip_medium_cut",      { .nbin=1,  .bins={1,2}, .fill=[this] { return std::abs(v.Muon().dz)<0.10&&std::abs(v.Muon().dxy)<0.05; }, .axis_title="vtx. d_{xy,#mu}/d_{z,#mu}", .def_range={1,2}});
	sh.AddNewFillParams("muip_tight_cut",       { .nbin=1,  .bins={1,2}, .fill=[this] { return std::abs(v.Muon().dz)<0.10&&std::abs(v.Muon().dxy)<0.05&&v.Muon().sip3d<4; }, .axis_title="vtx. d_{xy,#mu}/d_{z,#mu}", .def_range={1,2}});
	sh.AddNewFillParams("muminiiso_loose_cut",  { .nbin=1,  .bins={1,2}, .fill=[this] { return v.Muon().miniPFRelIso_all<0.4; }, .axis_title="#mu Mini iso.", .def_range={1,2}});
	sh.AddNewFillParams("muminiiso_medium_cut", { .nbin=1,  .bins={1,2}, .fill=[this] { return v.Muon().miniPFRelIso_all<0.2; }, .axis_title="#mu Mini iso.", .def_range={1,2}});
	sh.AddNewFillParams("mu2diso15_cut",        { .nbin=1,  .bins={1,2}, .fill=[this] { return !(v.Muon().jetDRmin<0.4&&v.Muon().cleanJetPtrel<15); }, .axis_title="#mu 2D iso.", .def_range={1,2}});
	sh.AddNewFillParams("muid_soft_cut",        { .nbin=1,  .bins={1,2}, .fill=[this] { return v.Muon().softId; }, .axis_title="Soft (Cut-based) ID", .def_range={1,2}});
	sh.AddNewFillParams("muid_medium_cut",      { .nbin=1,  .bins={1,2}, .fill=[this] { return v.Muon().mediumId; }, .axis_title="Medium (Cut-based) ID", .def_range={1,2}});
	sh.AddNewFillParams("muid_mediumprompt_cut",{ .nbin=1,  .bins={1,2}, .fill=[this] { return v.Muon().mediumPromptId; }, .axis_title="Medium (Cut-based) ID", .def_range={1,2}});
	sh.AddNewFillParams("muid_tight_cut",       { .nbin=1,  .bins={1,2}, .fill=[this] { return v.Muon().tightId; }, .axis_title="Tight (Cut-based) ID", .def_range={1,2}});
	sh.AddNewFillParams("muid_mva_loose_cut",   { .nbin=1,  .bins={1,2}, .fill=[this] { return v.Muon().mvaId>0; }, .axis_title="#mu MVA Loose ID", .def_range={1,2}});
	sh.AddNewFillParams("muid_mva_medium_cut",  { .nbin=1,  .bins={1,2}, .fill=[this] { return v.Muon().mvaId>1; }, .axis_title="#mu MVA Medium ID", .def_range={1,2}});
	sh.AddNewFillParams("eleid_mva_loose_cut",  { .nbin=1,  .bins={1,2}, .fill=[this] { return v.Electron().mvaFall17V2noIso_WPL; }, .axis_title="e MVA Loose ID (no iso.)", .def_range={1,2}});
	sh.AddNewFillParams("eleid_mva_medium_cut", { .nbin=1,  .bins={1,2}, .fill=[this] { return v.Electron().mvaFall17V2noIso_WP90; }, .axis_title="e MVA Medium ID (no iso.)", .def_range={1,2}});
	// pt/eta - can easily be tuned
	// pt      - black 1
	// eta     - green 418
	sh.AddNewFillParams("elept5",                  { .nbin=23,  .bins={0,5,10,15,20,25,30,35,40,45,50,60,70,80,100,125,150,200,250,300,400,500,1000,5000}, .fill=[this] { return v.Electron().pt; }, .axis_title="p_{T}^{e}", .def_range={5, 5000, 1}});
	sh.AddNewFillParams("elept10",                 { .nbin=23,  .bins={0,5,10,15,20,25,30,35,40,45,50,60,70,80,100,125,150,200,250,300,400,500,1000,5000}, .fill=[this] { return v.Electron().pt; }, .axis_title="p_{T}^{e}", .def_range={10,5000, 1}});
	sh.AddNewFillParams("elept30",                 { .nbin=23,  .bins={0,5,10,15,20,25,30,35,40,45,50,60,70,80,100,125,150,200,250,300,400,500,1000,5000}, .fill=[this] { return v.Electron().pt; }, .axis_title="p_{T}^{e}", .def_range={30,5000, 1}});
	sh.AddNewFillParams("mupt5",                   { .nbin=23,  .bins={0,5,10,15,20,25,30,35,40,45,50,60,70,80,100,125,150,200,250,300,400,500,1000,5000}, .fill=[this] { return v.Muon().pt; }, .axis_title="p_{T}^{#mu}", .def_range={5, 5000, 1}});
	sh.AddNewFillParams("mupt10",                  { .nbin=23,  .bins={0,5,10,15,20,25,30,35,40,45,50,60,70,80,100,125,150,200,250,300,400,500,1000,5000}, .fill=[this] { return v.Muon().pt; }, .axis_title="p_{T}^{#mu}", .def_range={10,5000, 1}});
	sh.AddNewFillParams("mupt30",                  { .nbin=23,  .bins={0,5,10,15,20,25,30,35,40,45,50,60,70,80,100,125,150,200,250,300,400,500,1000,5000}, .fill=[this] { return v.Muon().pt; }, .axis_title="p_{T}^{#mu}", .def_range={30,5000, 1}});
	sh.AddNewFillParams("eleeta_veto",             { .nbin=4, .bins={0,4}, .fill=[this] {
			double abseta = std::abs(v.Electron().eta);
			if      (abseta>=2.5)                 return 0;
			else if (abseta>=1.442&&abseta<1.556) return 1;
			else if (abseta>=2.1)                 return 2;
			else                                  return 3;
			}, .axis_title="#eta_{e}", .def_range={1,4, 1}});
sh.AddNewFillParams("eleeta",                  { .nbin=4,  .bins={0,4}, .fill=[this] { 
		double abseta = std::abs(v.Electron().eta);
		if      (abseta>=2.5)                 return 0;
		else if (abseta>=1.442&&abseta<1.556) return 1;
		else if (abseta>=2.1)                 return 2;
		else                                  return 3;
		}, .axis_title="#eta_{#mu}", .def_range={2,4, 1}});
sh.AddNewFillParams("mueta",                   { .nbin=3,   .bins={0,3}, .fill=[this] { 
		double abseta = std::abs(v.Muon().eta);
		if      (abseta>=2.4) return 0;
		else if (abseta>=2.1) return 1;
		else                  return 2; 
		}, .axis_title="#eta_{#mu}", .def_range={1,3, 1}});
// impact parameters - simple pick
// ip      - green 418;
sh.AddNewFillParams("eleip_loose",             { .nbin=3, .bins={1,4}, .fill=[this] {
		if      (std::abs(v.Electron().dz)>=0.50||std::abs(v.Electron().dxy)>=0.20) return 0;
		else if (std::abs(v.Electron().dz)>=0.10||std::abs(v.Electron().dxy)>=0.05) return 1;
		else if (v.Electron().sip3d>=4) return 2;
		else                                      return 3; 
		}, .axis_title="Impact param.", .def_range={0.9,4, 418}});
sh.AddNewFillParams("eleip_medium",            { .nbin=3, .bins={1,4}, .fill=[this] {
		if      (std::abs(v.Electron().dz)>=0.50||std::abs(v.Electron().dxy)>=0.20) return 0;
		else if (std::abs(v.Electron().dz)>=0.10||std::abs(v.Electron().dxy)>=0.05) return 1;
		else if (v.Electron().sip3d>=4) return 2;
		else                                      return 3; 
		}, .axis_title="Impact param.", .def_range={2,4, 418}});
sh.AddNewFillParams("eleip_tight",             { .nbin=3, .bins={1,4}, .fill=[this] {
		if      (std::abs(v.Electron().dz)>=0.50||std::abs(v.Electron().dxy)>=0.20) return 0;
		else if (std::abs(v.Electron().dz)>=0.10||std::abs(v.Electron().dxy)>=0.05) return 1;
		else if (v.Electron().sip3d>=4) return 2;
		else                                      return 3; 
		}, .axis_title="Impact param.", .def_range={3,4, 418}});
sh.AddNewFillParams("muip_loose",              { .nbin=3, .bins={1,4}, .fill=[this] {
		if      (std::abs(v.Muon().dz)>=0.50||std::abs(v.Muon().dxy)>=0.20) return 0;
		else if (std::abs(v.Muon().dz)>=0.10||std::abs(v.Muon().dxy)>=0.05) return 1;
		else if (v.Muon().sip3d>=4) return 2;
		else                              return 3; 
		}, .axis_title="Impact param.", .def_range={0.9,4, 418}});
sh.AddNewFillParams("muip_medium",             { .nbin=3, .bins={1,4}, .fill=[this] {
		if      (std::abs(v.Muon().dz)>=0.50||std::abs(v.Muon().dxy)>=0.20) return 0;
		else if (std::abs(v.Muon().dz)>=0.10||std::abs(v.Muon().dxy)>=0.05) return 1;
		else if (v.Muon().sip3d>=4) return 2;
		else                              return 3; 
		}, .axis_title="Impact param.", .def_range={2,4, 418}});
sh.AddNewFillParams("muip_tight",              { .nbin=3, .bins={1,4}, .fill=[this] {
		if      (std::abs(v.Muon().dz)>=0.50||std::abs(v.Muon().dxy)>=0.20) return 0;
		else if (std::abs(v.Muon().dz)>=0.10||std::abs(v.Muon().dxy)>=0.05) return 1;
		else if (v.Muon().sip3d>=4) return 2;
		else                              return 3; 
		}, .axis_title="Impact param.", .def_range={3,4, 418}});
// isolations - mini iso recommended, but we can cross-check others
// pfiso   - yellow 402
// miniiso - orange 801
// 2diso   - gray   921
sh.AddNewFillParams("elepfiso",                { .nbin=4, .bins={1,5}, .fill=[this] { 
		// https://twiki.cern.ch/twiki/bin/view/CMS/CutBasedElectronIdentificationRun2#Offline_selection_criteria_for_V
		float pt = v.Electron().pt, pfiso = v.Electron().pfRelIso03_all;
		if (std::abs(v.Electron().eta+v.Electron().deltaEtaSC)<=1.479) {
		if      (pfiso>=0.1980+0.506/pt) return 0;
		else if (pfiso>=0.1120+0.506/pt) return 1;
		else if (pfiso>=0.0478+0.506/pt) return 2;
		else if (pfiso>=0.0287+0.506/pt) return 3;
		else                             return 4;
		} else {
		if      (pfiso>=0.2030+0.963/pt) return 0;
		else if (pfiso>=0.1080+0.963/pt) return 1;
		else if (pfiso>=0.0658+0.963/pt) return 2;
		else if (pfiso>=0.0445+0.963/pt) return 3;
		else                             return 4;
		} }, .axis_title="PF iso.", .def_range={0,5, 402}});
sh.AddNewFillParams("eleminiiso",              { .nbin=4, .bins={1,5}, .fill=[this] {
		float miniIso = v.Electron().miniPFRelIso_all;
		if      (miniIso>=0.40) return 0;
		else if (miniIso>=0.20) return 1;
		else if (miniIso>=0.10) return 2;
		else if (miniIso>=0.05) return 3;
		else                    return 4;
		}, .axis_title="Mini iso.", .def_range={0,5, 801}});
sh.AddNewFillParams("eleminiiso_loose",        { .nbin=4, .bins={1,5}, .fill=[this] {
		float miniIso = v.Electron().miniPFRelIso_all;
		if      (miniIso>=0.40) return 0;
		else if (miniIso>=0.20) return 1;
		else if (miniIso>=0.10) return 2;
		else if (miniIso>=0.05) return 3;
		else                    return 4;
		}, .axis_title="Mini iso.", .def_range={0.9,5, 801}});
sh.AddNewFillParams("eleminiiso_tight",        { .nbin=4, .bins={1,5}, .fill=[this] {
		float miniIso = v.Electron().miniPFRelIso_all;
		if      (miniIso>=0.40) return 0;
		else if (miniIso>=0.20) return 1;
		else if (miniIso>=0.10) return 2;
		else if (miniIso>=0.05) return 3;
		else                    return 4;
		}, .axis_title="Mini iso.", .def_range={3,5, 402}});
sh.AddNewFillParams("ele2diso15",              { .nbin=10, .bins={1,11}, .fill=[this] {
		if (v.Electron().jetDRmin<0.4) for (int i=0; i<10; ++i) 
		if (v.Electron().cleanJetPtrel<(i+1)*5) return i;
		return 10;
		}, .axis_title="2D iso.", .def_range={3,11, 921}});
sh.AddNewFillParams("ele2diso",                { .nbin=10, .bins={1,11}, .fill=[this] {
		if (v.Electron().jetDRmin<0.4) for (int i=0; i<10; ++i) 
		if (v.Electron().cleanJetPtrel<(i+1)*5) return i;
		return 10;
		}, .axis_title="2D iso.", .def_range={0,11, 921}});
sh.AddNewFillParams("mupfiso",                 { .nbin=8, .bins={-1,7}, .fill=[this] { return v.Muon().pfIsoId; }, .axis_title="#mu PF iso.", .def_range={0,7}}); 
//sh.AddNewFillParams("mumultiiso",              { .nbin=4, .bins={-1,3}, .fill=[this] { return v.Muon().multiIsoId; }, .axis_title="#mu Multi iso.", .def_range={0,7}});// currently unavailable
sh.AddNewFillParams("muminiiso",               { .nbin=4, .bins={1,5}, .fill=[this] {
		float miniIso = v.Muon().miniPFRelIso_all;
		if      (miniIso>=0.40) return 0;
		else if (miniIso>=0.20) return 1;
		else if (miniIso>=0.10) return 2;
		else if (miniIso>=0.05) return 3;
		else                    return 4;
		}, .axis_title="Mini iso.", .def_range={0,5, 801}});
sh.AddNewFillParams("muminiiso_loose",         { .nbin=4, .bins={1,5}, .fill=[this] {
		float miniIso = v.Muon().miniPFRelIso_all;
		if      (miniIso>=0.40) return 0;
		else if (miniIso>=0.20) return 1;
		else if (miniIso>=0.10) return 2;
		else if (miniIso>=0.05) return 3;
		else                    return 4;
		}, .axis_title="Mini iso.", .def_range={0.9,5, 801}});
sh.AddNewFillParams("muminiiso_medium",        { .nbin=4, .bins={1,5}, .fill=[this] {
		float miniIso = v.Muon().miniPFRelIso_all;
		if      (miniIso>=0.40) return 0;
		else if (miniIso>=0.20) return 1;
		else if (miniIso>=0.10) return 2;
		else if (miniIso>=0.05) return 3;
		else                    return 4;
		}, .axis_title="Mini iso.", .def_range={2,5, 801}});
sh.AddNewFillParams("mu2diso",                 { .nbin=10, .bins={1,11}, .fill=[this] {
		if (v.Muon().jetDRmin<0.4) for (int i=0; i<10; ++i) 
		if (v.Muon().cleanJetPtrel<(i+1)*5) return i;
		return 10;
		}, .axis_title="2D iso.", .def_range={0,11, 921}});
sh.AddNewFillParams("mu2diso15",               { .nbin=10, .bins={1,11}, .fill=[this] {
		if (v.Muon().jetDRmin<0.4) for (int i=0; i<10; ++i) 
		if (v.Muon().cleanJetPtrel<(i+1)*5) return i;
		return 10;
		}, .axis_title="2D iso.", .def_range={3,11, 921}});
// id with/without isolation
// id      - cyan to red 434,601,618,633
sh.AddNewFillParams("eleid_cut_iso",           { .nbin=4, .bins={1,5}, .fill=[this] { return v.Electron().cutBased; }, .axis_title="Cut-based ID", .def_range={0,  5, 601}});
sh.AddNewFillParams("eleid_cut_iso_veto",      { .nbin=4, .bins={1,5}, .fill=[this] { return v.Electron().cutBased; }, .axis_title="Cut-based ID", .def_range={0.9,5, 601}});
sh.AddNewFillParams("eleid_cut_iso_loose",     { .nbin=4, .bins={1,5}, .fill=[this] { return v.Electron().cutBased; }, .axis_title="Cut-based ID", .def_range={2,  5, 601}});
sh.AddNewFillParams("eleid_cut_iso_medium",    { .nbin=4, .bins={1,5}, .fill=[this] { return v.Electron().cutBased; }, .axis_title="Cut-based ID", .def_range={3,  5, 601}});
sh.AddNewFillParams("eleid_cut_iso_tight",     { .nbin=4, .bins={1,5}, .fill=[this] { return v.Electron().cutBased; }, .axis_title="Cut-based ID", .def_range={4,  5, 601}});
sh.AddNewFillParams("eleid_mva",               { .nbin=3, .bins={1,4}, .fill=[this] {
		if (!v.Electron().mvaFall17V2noIso_WPL)  return 0;
		if (!v.Electron().mvaFall17V2noIso_WP90) return 1;
		if (!v.Electron().mvaFall17V2noIso_WP80) return 2;
		else                                               return 3;
		}, .axis_title="MVA ID (no iso.)", .def_range={0,4, 633}});
sh.AddNewFillParams("eleid_mva_loose",         { .nbin=3, .bins={1,4}, .fill=[this] {
		if (!v.Electron().mvaFall17V2noIso_WPL)  return 0;
		if (!v.Electron().mvaFall17V2noIso_WP90) return 1;
		if (!v.Electron().mvaFall17V2noIso_WP80) return 2;
		else                                               return 3;
		}, .axis_title="MVA ID (no iso.)", .def_range={0.9,4, 633}});
sh.AddNewFillParams("eleid_mva_medium",        { .nbin=3, .bins={1,4}, .fill=[this] {
		if (!v.Electron().mvaFall17V2noIso_WPL)  return 0;
		if (!v.Electron().mvaFall17V2noIso_WP90) return 1;
		if (!v.Electron().mvaFall17V2noIso_WP80) return 2;
		else                                               return 3;
		}, .axis_title="MVA ID (no iso.)", .def_range={2,4, 633}});
sh.AddNewFillParams("eleid_mva_tight",         { .nbin=3, .bins={1,4}, .fill=[this] {
		if (!v.Electron().mvaFall17V2noIso_WPL)  return 0;
		if (!v.Electron().mvaFall17V2noIso_WP90) return 1;
		if (!v.Electron().mvaFall17V2noIso_WP80) return 2;
		else                                               return 3;
		}, .axis_title="MVA ID (no iso.)", .def_range={3,4, 633}});
sh.AddNewFillParams("eleid_mva_iso",           { .nbin=3, .bins={1,4}, .fill=[this] {
		if (!v.Electron().mvaFall17V2Iso_WPL)  return 0;
		if (!v.Electron().mvaFall17V2Iso_WP90) return 1;
		if (!v.Electron().mvaFall17V2Iso_WP80) return 2;
		else                                             return 3;
		}, .axis_title="MVA ID (w/ iso.)", .def_range={0,4, 618}});
sh.AddNewFillParams("eleid_mva_iso_loose",     { .nbin=3, .bins={1,4}, .fill=[this] {
		if (!v.Electron().mvaFall17V2Iso_WPL)  return 0;
		if (!v.Electron().mvaFall17V2Iso_WP90) return 1;
		if (!v.Electron().mvaFall17V2Iso_WP80) return 2;
		else                                             return 3;
		}, .axis_title="MVA ID (w/ iso.)", .def_range={0.9,4, 618}});
sh.AddNewFillParams("eleid_mva_iso_medium",    { .nbin=3, .bins={1,4}, .fill=[this] {
		if (!v.Electron().mvaFall17V2Iso_WPL)  return 0;
		if (!v.Electron().mvaFall17V2Iso_WP90) return 1;
		if (!v.Electron().mvaFall17V2Iso_WP80) return 2;
		else                                             return 3;
		}, .axis_title="MVA ID (w/ iso.)", .def_range={2,4, 618}});
sh.AddNewFillParams("eleid_mva_iso_tight",     { .nbin=3, .bins={1,4}, .fill=[this] {
		if (!v.Electron().mvaFall17V2Iso_WPL)  return 0;
		if (!v.Electron().mvaFall17V2Iso_WP90) return 1;
		if (!v.Electron().mvaFall17V2Iso_WP80) return 2;
		else                                             return 3;
		}, .axis_title="MVA ID (w/ iso.)", .def_range={3,4, 618}});
sh.AddNewFillParams("eleid_mva_miniiso",       { .nbin=6, .bins={2,8}, .fill=[this] {
		float miniIso = v.Electron().miniPFRelIso_all;
		if      (!v.Electron().mvaFall17V2noIso_WPL)  return 0;
		else if (miniIso>=0.40)                                 return 1;
		else if (!v.Electron().mvaFall17V2noIso_WP90) return 2;
		else if (miniIso>=0.20)                                 return 3;
		else if (miniIso>=0.10)                                 return 4;
		else if (!v.Electron().mvaFall17V2noIso_WP80) return 5;
		else if (miniIso>=0.05)                                 return 6;
		else                                                    return 7;
		}, .axis_title="MVA ID (w/ Mini iso.)", .def_range={0,8, 633}});
sh.AddNewFillParams("eleid_mva_2diso",         { .nbin=11, .bins={1,12}, .fill=[this] {
		if      (!v.Electron().mvaFall17V2noIso_WPL)                      return 0;
		else if (v.Electron().jetDRmin<0.4&&v.Electron().cleanJetPtrel<5)  return 1;
		else if (v.Electron().jetDRmin<0.4&&v.Electron().cleanJetPtrel<10) return 2;
		else if (!v.Electron().mvaFall17V2noIso_WP90)                     return 3;
		else if (v.Electron().jetDRmin<0.4&&v.Electron().cleanJetPtrel<15) return 4;
		else if (v.Electron().jetDRmin<0.4&&v.Electron().cleanJetPtrel<20) return 5;
		else if (v.Electron().jetDRmin<0.4&&v.Electron().cleanJetPtrel<25) return 6;
		else if (!v.Electron().mvaFall17V2noIso_WP80)                     return 7;
		else if (v.Electron().jetDRmin<0.4&&v.Electron().cleanJetPtrel<30) return 8;
		else if (v.Electron().jetDRmin<0.4&&v.Electron().cleanJetPtrel<40) return 9;
		else if (v.Electron().jetDRmin<0.4&&v.Electron().cleanJetPtrel<50) return 10;
		else                                                                        return 11;
		}, .axis_title="MVA ID (w/ 2D iso.)", .def_range={0,12, 921}}); // Gray
sh.AddNewFillParams("eleid_mva_miniiso_loose", { .nbin=6, .bins={2,8}, .fill=[this] {
		float miniIso = v.Electron().miniPFRelIso_all;
		if (!v.Electron().mvaFall17V2noIso_WPL)       return 0;
		else if (miniIso>=0.40)                                 return 1;
		else if (!v.Electron().mvaFall17V2noIso_WP90) return 2;
		else if (miniIso>=0.20)                                 return 3;
		else if (miniIso>=0.10)                                 return 4;
		else if (!v.Electron().mvaFall17V2noIso_WP80) return 5;
		else if (miniIso>=0.05)                                 return 6;
		else                                                    return 7;
		}, .axis_title="MVA ID (w/ Mini iso.)", .def_range={1.9,8, 633}});
sh.AddNewFillParams("muid_soft_comp",          { .nbin=1, .bins={1,2}, .fill=[this] { return v.Muon().softId; }, .axis_title="Soft (Cut-based) ID", .def_range={0,  2, 434}});
sh.AddNewFillParams("muid_soft",               { .nbin=1, .bins={1,2}, .fill=[this] { return v.Muon().softId; }, .axis_title="Soft (Cut-based) ID", .def_range={0.9,2, 434}});
sh.AddNewFillParams("muid_medium_comp",        { .nbin=2, .bins={1,3}, .fill=[this] { 
		if      (!v.Muon().mediumId)       return 0;
		else if (!v.Muon().mediumPromptId) return 1;
		else                                     return 2;
		}, .axis_title="Medium (Cut-based) ID", .def_range={0,3, 601}});
sh.AddNewFillParams("muid_medium",             { .nbin=2, .bins={1,3}, .fill=[this] { 
		if      (!v.Muon().mediumId)       return 0;
		else if (!v.Muon().mediumPromptId) return 1;
		else                                     return 2;
		}, .axis_title="Medium (Cut-based) ID", .def_range={0.9,3, 601}});
sh.AddNewFillParams("muid_mediumprompt",       { .nbin=2, .bins={1,3}, .fill=[this] { 
		if      (!v.Muon().mediumId)       return 0;
		else if (!v.Muon().mediumPromptId) return 1;
		else                                     return 2;
		}, .axis_title="Medium (Cut-based) ID", .def_range={2,3, 601}});
sh.AddNewFillParams("muid_tight_comp",         { .nbin=1, .bins={1,2}, .fill=[this] { return v.Muon().tightId; }, .axis_title="Tight (Cut-based) ID", .def_range={0,  2, 618}});
sh.AddNewFillParams("muid_tight",              { .nbin=1, .bins={1,2}, .fill=[this] { return v.Muon().tightId; }, .axis_title="Tight (Cut-based) ID", .def_range={0.9,2, 618}});
sh.AddNewFillParams("muid_mva",                { .nbin=3, .bins={1,4}, .fill=[this] { return v.Muon().mvaId; }, .axis_title="MVA ID", .def_range={0,  4, 633}});
sh.AddNewFillParams("muid_mva_loose",          { .nbin=3, .bins={1,4}, .fill=[this] { return v.Muon().mvaId; }, .axis_title="MVA ID", .def_range={0.9,4, 633}});
sh.AddNewFillParams("muid_mva_medium",         { .nbin=3, .bins={1,4}, .fill=[this] { return v.Muon().mvaId; }, .axis_title="MVA ID", .def_range={2,  4, 633}});
sh.AddNewFillParams("muid_mva_tight",          { .nbin=3, .bins={1,4}, .fill=[this] { return v.Muon().mvaId; }, .axis_title="MVA ID", .def_range={3,  4, 633}});
// Rest of the muon IDs don't work currently or not available for 2017
// softMva   - 2018
// softMvaId - 0
// looseId   - 2018
// mvaLowPt  - bugged
// mvaTTH    - Not ID, but TTH vs HH discriminator


// Boosted objects
// GenTruth for hadronic boosted tops
// NB. Since we loop on leptons, all of their variables can be used
std::map<std::string, std::function<int()> > gen_tops;
gen_tops["EleLepTop"] = [this] {
	if (!v.Electron().matchGenEleFromTop) return (int)0;
	if (v.Electron().iMatchedAK8==(size_t)-1) return (int)0;
	return (int)v.FatJet(v.Electron().iMatchedAK8).matchGenLepTop; };
gen_tops["EleNuFromLepTop"] = [this] { return v.Electron().nuMatchGenEleNuFromTop; };
gen_tops["MuLepTop"] = [this] {
	if (!v.Muon().matchGenMuFromTop) return (int)0;
	if (v.Muon().iMatchedAK8==(size_t)-1) return (int)0;
	return (int)v.FatJet(v.Muon().iMatchedAK8).matchGenLepTop; };
//   gen_tops["TauLepTop"] = [this] {
//     if (!v.Tau().matchGenTauFromTop) return (int)0;
//     if (v.Tau().iMatchedAK8==(size_t)-1) return (int)0;
//     return (int)v.FatJet(v.Tau().iMatchedAK8).matchGenLepTop; };
gen_tops["MuNuFromLepTop"] = [this] { return v.Muon().nuMatchGenMuNuFromTop; };
gen_tops["HadTop"] = [this] { return (int)v.FatJet().matchGenHadTop; };
for (const auto& genp : gen_tops) for (const auto& bm : top_benchmarks)
	sh.AddNewFillParams(genp.first+"_"+bm.first, { .nbin= 2, .bins={-0.5,1.5}, .fill=[genp,bm] { int signal = bm.second(); return signal==1 ? genp.second() : signal; }});
	// GenTruth for hadronic boosted W/Z/H
	std::map<std::string, std::function<int()> > gen_hadVs;
	gen_hadVs["HadW"] = [this] { return (int)v.FatJet().matchGenHadW; };
gen_hadVs["HadZ"] = [this] { return (int)v.FatJet().matchGenHadZ; };
gen_hadVs["HadH"] = [this] { return (int)v.FatJet().matchGenHadH; };
for (const auto& genp : gen_hadVs) for (const auto& bm : all_benchmarks)
	sh.AddNewFillParams(genp.first+"_"+bm.first, { .nbin= 2, .bins={-0.5,1.5}, .fill=[genp,bm] { int signal = bm.second(); return signal==1 ? genp.second() : signal; }});
	// Cuts not to be shown
	sh.AddNewFillParams("ak8pt200_cut",           { .nbin=1,  .bins={200,10000}, .fill=[this] { return v.FatJet().pt; }, .axis_title="p_{T}", .def_range={200,10000}});
	sh.AddNewFillParams("ak8pt300_cut",           { .nbin=1,  .bins={300,10000}, .fill=[this] { return v.FatJet().pt; }, .axis_title="p_{T}", .def_range={300,10000}});
	sh.AddNewFillParams("ak8pt400_cut",           { .nbin=1,  .bins={400,10000}, .fill=[this] { return v.FatJet().pt; }, .axis_title="p_{T}", .def_range={400,10000}});
	sh.AddNewFillParams("ak8pt500_cut",           { .nbin=1,  .bins={400,10000}, .fill=[this] { return v.FatJet().pt; }, .axis_title="p_{T}", .def_range={400,10000}});
	sh.AddNewFillParams("ele_ak8pt200_cut",       { .nbin=1,  .bins={200,10000}, .fill=[this] { if (v.Electron().iMatchedAK8==(size_t)-1) return (float)-1; return v.FatJet(v.Electron().iMatchedAK8).pt; }, .axis_title="p_{T}^{AK8}", .def_range={200,10000}});
	sh.AddNewFillParams("ele_ak8pt300_cut",       { .nbin=1,  .bins={300,10000}, .fill=[this] { if (v.Electron().iMatchedAK8==(size_t)-1) return (float)-1; return v.FatJet(v.Electron().iMatchedAK8).pt; }, .axis_title="p_{T}^{AK8}", .def_range={300,10000}});
	sh.AddNewFillParams("mu_ak8pt200_cut",        { .nbin=1,  .bins={200,10000}, .fill=[this] { if (v.Muon().iMatchedAK8==(size_t)-1)     return (float)-1; return v.FatJet(v.Muon().iMatchedAK8).pt;      }, .axis_title="p_{T}^{AK8}", .def_range={200,10000}});
	sh.AddNewFillParams("mu_ak8pt300_cut",        { .nbin=1,  .bins={300,10000}, .fill=[this] { if (v.Muon().iMatchedAK8==(size_t)-1)     return (float)-1; return v.FatJet(v.Muon().iMatchedAK8).pt;      }, .axis_title="p_{T}^{AK8}", .def_range={300,10000}});
	sh.AddNewFillParams("ele_ak8eta_cut",         { .nbin=1,  .bins={1,2},       .fill=[this] { if (v.Electron().iMatchedAK8==(size_t)-1) return (bool)0; return std::abs(v.FatJet(v.Electron().iMatchedAK8).eta)<2.4; }, .axis_title="#eta_{AK8}", .def_range={1,2}});
	sh.AddNewFillParams("mu_ak8eta_cut",          { .nbin=1,  .bins={1,2},       .fill=[this] { if (v.Muon().iMatchedAK8==(size_t)-1)     return (bool)0; return std::abs(v.FatJet(v.Muon().iMatchedAK8).eta)<2.4;      }, .axis_title="#eta_{AK8}", .def_range={1,2}});
	sh.AddNewFillParams("ele_msoftdrop50_cut",    { .nbin=1, .bins={1,2},        .fill=[this] { if (v.Electron().iMatchedAK8==(size_t)-1) return (bool)0; return v.FatJet(v.Electron().iMatchedAK8).msoftdrop>=50; }, .axis_title="m_{soft-drop}^{AK8}", .def_range={1,2}});
	sh.AddNewFillParams("mu_msoftdrop50_cut",     { .nbin=1, .bins={1,2},        .fill=[this] { if (v.Muon().iMatchedAK8==(size_t)-1)     return (bool)0; return v.FatJet(v.Muon().iMatchedAK8).msoftdrop>=50;      }, .axis_title="m_{soft-drop}^{AK8}", .def_range={1,2}});
	sh.AddNewFillParams("ele_sjbtag_loose_cut",   { .nbin=1, .bins={1,2},        .fill=[this] { if (v.Electron().iMatchedAK8==(size_t)-1) return (bool)0; return v.FatJet(v.Electron().iMatchedAK8).maxSubJetDeepB>=0.1522; }, .axis_title="subjet b-tag", .def_range={1,2}});
	sh.AddNewFillParams("mu_sjbtag_loose_cut",    { .nbin=1, .bins={1,2},        .fill=[this] { if (v.Muon().iMatchedAK8==(size_t)-1)     return (bool)0; return v.FatJet(v.Muon().    iMatchedAK8).maxSubJetDeepB>=0.1522; }, .axis_title="subjet b-tag", .def_range={1,2}});
	// pt/mass
	sh.AddNewFillParams("ak8pt200",               { .nbin=12, .bins={200,250,300,350,400,450,500,550,600,800,1000,2000,10000}, .fill=[this] { return v.FatJet().pt; }, .axis_title="p_{T}", .def_range={200-1e-10, 10000, 418}}); // Green
	sh.AddNewFillParams("ak8pt300",               { .nbin=12, .bins={200,250,300,350,400,450,500,550,600,800,1000,2000,10000}, .fill=[this] { return v.FatJet().pt; }, .axis_title="p_{T}", .def_range={300,10000, 418}}); // Green
	sh.AddNewFillParams("ak8pt400",               { .nbin=12, .bins={200,250,300,350,400,450,500,550,600,800,1000,2000,10000}, .fill=[this] { return v.FatJet().pt; }, .axis_title="p_{T}", .def_range={400,10000, 418}}); // Green
	sh.AddNewFillParams("ak8pt500",               { .nbin=12, .bins={200,250,300,350,400,450,500,550,600,800,1000,2000,10000}, .fill=[this] { return v.FatJet().pt; }, .axis_title="p_{T}", .def_range={400,10000, 418}}); // Green
	sh.AddNewFillParams("msoftdrop65",            { .nbin=22, .bins={0, 25, 50, 55, 60, 65, 70, 75, 80, 90, 100, 105, 120, 140, 170, 200, 250, 300, 350, 400, 600, 1000, 10000}, .fill=[this] { return v.FatJet().msoftdrop; }, .axis_title="min m_{soft-drop}", .def_range={65,10000, 401}}); // Yellow
	sh.AddNewFillParams("msoftdrop80",            { .nbin=22, .bins={0, 25, 50, 65, 70, 75, 80, 85, 90, 95, 100, 110, 120, 140, 170, 200, 250, 300, 350, 400, 600, 1000, 10000}, .fill=[this] { return v.FatJet().msoftdrop; }, .axis_title="min m_{soft-drop}", .def_range={80,10000, 401}}); // Yellow
	sh.AddNewFillParams("msoftdrop100",           { .nbin=20, .bins={0, 25, 50, 65, 80, 90, 95, 100, 105, 110, 120, 140, 170, 200, 250, 300, 350, 400, 600, 1000, 10000}, .fill=[this] { return v.FatJet().msoftdrop; }, .axis_title="min m_{soft-drop}",     .def_range={100,10000, 401}}); // Yellow
	sh.AddNewFillParams("msoftdrop105",           { .nbin=12, .bins={0, 50, 105, 140, 175, 210, 250, 300, 350, 400, 600, 1000, 10000}, .fill=[this] { return v.FatJet().msoftdrop; }, .axis_title="min m_{soft-drop}", .def_range={105,10000, 401}}); // Yellow
	sh.AddNewFillParams("msoftdrop_min",          { .nbin=28, .bins={-1, 0, 50, 60, 70, 80, 90, 100, 105, 110, 120, 130, 140, 150, 160, 175, 190, 200, 210, 220, 240, 260, 280, 300, 350, 400, 600, 1000, 10000}, .fill=[this] { return v.FatJet().msoftdrop; }, .axis_title="min m_{soft-drop}", .def_range={-2,10000, 401}}); // Yellow - has a noval of -1
	sh.AddNewFillParams("msoftdrop_max",          { .nbin=23, .bins={-1, 0, 50, 65, 80, 90, 100, 105, 120, 140, 150, 160, 170, 180, 200, 210, 225, 250, 300, 350, 400, 600, 1000, 10000}, .fill=[this] { return v.FatJet().msoftdrop; }, .axis_title="max m_{soft-drop}", .def_range={-1,10000-1, 891}}); // Pink - has a noval of -1
	sh.AddNewFillParams("ele_ak8pt200",           { .nbin=12, .bins={200,250,300,350,400,450,500,550,600,800,1000,2000,10000}, .fill=[this] { if (v.Electron().iMatchedAK8==(size_t)-1) return (float)-1; return v.FatJet(v.Electron().iMatchedAK8).pt; }, .axis_title="p_{T}^{AK8}", .def_range={200,10000, 412}}); // Light Green
	sh.AddNewFillParams("ele_ak8pt300",           { .nbin=12, .bins={200,250,300,350,400,450,500,550,600,800,1000,2000,10000}, .fill=[this] { if (v.Electron().iMatchedAK8==(size_t)-1) return (float)-1; return v.FatJet(v.Electron().iMatchedAK8).pt; }, .axis_title="p_{T}^{AK8}", .def_range={300,10000, 412}}); // Light Green
	sh.AddNewFillParams("mu_ak8pt200",            { .nbin=12, .bins={200,250,300,350,400,450,500,550,600,800,1000,2000,10000}, .fill=[this] { if (v.Muon().iMatchedAK8==(size_t)-1)      return (float)-1; return v.FatJet(v.Muon().iMatchedAK8).pt;      }, .axis_title="p_{T}^{AK8}", .def_range={200,10000, 412}}); // Light Green
	sh.AddNewFillParams("mu_ak8pt300",            { .nbin=12, .bins={200,250,300,350,400,450,500,550,600,800,1000,2000,10000}, .fill=[this] { if (v.Muon().iMatchedAK8==(size_t)-1)      return (float)-1; return v.FatJet(v.Muon().iMatchedAK8).pt;      }, .axis_title="p_{T}^{AK8}", .def_range={300,10000, 412}}); // Light Green
	sh.AddNewFillParams("ele_msoftdrop50",        { .nbin=15, .bins={0, 25, 50, 75, 100, 125, 150, 175, 200, 250, 300, 350, 400, 600, 1000, 10000}, .fill=[this] { if (v.Electron().iMatchedAK8==(size_t)-1) return (float)-1; return v.FatJet(v.Electron().iMatchedAK8).msoftdrop; }, .axis_title="m_{soft-drop}^{AK8}", .def_range={50,10000, 401}}); // Yellow
	sh.AddNewFillParams("ele_msoftdrop0",        { .nbin=15, .bins={0, 25, 50, 75, 100, 125, 150, 175, 200, 250, 300, 350, 400, 600, 1000, 10000}, .fill=[this] { if (v.Electron().iMatchedAK8==(size_t)-1) return (float)-1; return v.FatJet(v.Electron().iMatchedAK8).msoftdrop; }, .axis_title="m_{soft-drop}^{AK8}", .def_range={-1,10000, 401}}); // Yellow
	sh.AddNewFillParams("mu_msoftdrop50",         { .nbin=15, .bins={0, 25, 50, 75, 100, 125, 150, 175, 200, 250, 300, 350, 400, 600, 1000, 10000}, .fill=[this] { if (v.Muon().iMatchedAK8==(size_t)-1)      return (float)-1; return v.FatJet(v.Muon().iMatchedAK8).msoftdrop;      }, .axis_title="m_{soft-drop}^{AK8}", .def_range={50,10000, 401}}); // Yellow
	sh.AddNewFillParams("mu_msoftdrop0",         { .nbin=15, .bins={0, 25, 50, 75, 100, 125, 150, 175, 200, 250, 300, 350, 400, 600, 1000, 10000}, .fill=[this] { if (v.Muon().iMatchedAK8==(size_t)-1)      return (float)-1; return v.FatJet(v.Muon().iMatchedAK8).msoftdrop;      }, .axis_title="m_{soft-drop}^{AK8}", .def_range={-1,10000, 401}}); // Yellow
	// Taggers
	// subjet b
	sh.AddNewFillParams("sjbtag",                      { .nbin=5, .bins={-2, 0, 0.1522, 0.4941, 0.8001, 1.0000}, .fill=[this] { return v.FatJet().maxSubJetDeepB; }, .axis_title="subjet b-tag", .def_range={-2,    1.0000, 434}}); // Cyan - noval at -2
	sh.AddNewFillParams("sjbtag_loose",                { .nbin=4, .bins={-2,    0.1522, 0.4941, 0.8001, 1.0000}, .fill=[this] { return v.FatJet().maxSubJetDeepB; }, .axis_title="subjet b-tag", .def_range={0.1522,1.0000, 434}}); // Cyan
	sh.AddNewFillParams("ele_sjbtag_loose",            { .nbin=4, .bins={-2,    0.1522, 0.4941, 0.8001, 1.0000}, .fill=[this] { if (v.Electron().iMatchedAK8==(size_t)-1) return (double)-1; return v.FatJet(v.Electron().iMatchedAK8).maxSubJetDeepB; }, .axis_title="subjet b-tag", .def_range={0.1522,1.0000, 434}}); // Cyan
	sh.AddNewFillParams("mu_sjbtag_loose",             { .nbin=4, .bins={-2,    0.1522, 0.4941, 0.8001, 1.0000}, .fill=[this] { if (v.Muon().    iMatchedAK8==(size_t)-1) return (double)-1; return v.FatJet(v.Muon().    iMatchedAK8).maxSubJetDeepB;      }, .axis_title="subjet b-tag", .def_range={0.1522,1.0000, 434}}); // Cyan
	// Neutrino distance (from lepton+MET and W mass constraint)
	sh.AddNewFillParams("ele_neutrinojetdr",           { .nbin=14, .bins={0, 0.4, 0.8, 1.0, 1.2, 1.4, 1.6, 2.0, 2.4, 2.8, 3.2, 4.0, 5.0, 6.0, 10}, .fill=[this] { return v.Electron().nuMatchedAK8DR; }, .axis_title="#DeltaR (#nu, AK8 jet)", .def_range={-1, 10, 617}}); // Magenta
	sh.AddNewFillParams("ele_neutrinodr",              { .nbin=14, .bins={0, 0.4, 0.8, 1.0, 1.2, 1.4, 1.6, 2.0, 2.4, 2.8, 3.2, 4.0, 5.0, 6.0, 10}, .fill=[this] { return v.Electron().nuDR;           }, .axis_title="#DeltaR (#nu, e)", .def_range={-1, 10, 807}}); // Carrot
	sh.AddNewFillParams("mu_neutrinojetdr",            { .nbin=14, .bins={0, 0.4, 0.8, 1.0, 1.2, 1.4, 1.6, 2.0, 2.4, 2.8, 3.2, 4.0, 5.0, 6.0, 10}, .fill=[this] { return v.Muon().nuMatchedAK8DR;     }, .axis_title="#DeltaR (#nu, AK8 jet)", .def_range={-1, 10, 617}}); // Magenta
	sh.AddNewFillParams("mu_neutrinodr",               { .nbin=14, .bins={0, 0.4, 0.8, 1.0, 1.2, 1.4, 1.6, 2.0, 2.4, 2.8, 3.2, 4.0, 5.0, 6.0, 10}, .fill=[this] { return v.Muon().nuDR;               }, .axis_title="#DeltaR (#nu, #mu)", .def_range={-1, 10, 807}}); // Carrot
	// top
	sh.AddNewFillParams("tau32_softdrop_sjbtag",       { .nbin=10, .bins={0, 0.40, 0.46, 0.54, 0.65, 0.8, 2, 3, 4, 5, 6}, .fill=[this] { 
			if (v.FatJet().msoftdrop<HADTOP_SD_MASS_CUT_LOW)  return (double)4;
			if (v.FatJet().msoftdrop>=HADTOP_SD_MASS_CUT_HIGH) return (double)3;
			if (!v.FatJet().passSubJetBTag) return (double)2;
			return v.FatJet().tau32;
			}, .axis_title="#tau_{32}, m_{sd}, b_{sj}", .def_range={0,5, 434}}); // Cyan
sh.AddNewFillParams("deepTagMD_top",               { .nbin=4,  .bins={0.054, 0.391, 0.578, 0.843, 1.000}, .fill=[this] { return v.FatJet().deepTagMD_TvsQCD; }, .axis_title="deepTagMD", .def_range={-10,1.0, 601}}); // Blue - noval at -10
sh.AddNewFillParams("deepTagMD_top_minsd",         { .nbin=4,  .bins={0.054, 0.391, 0.578, 0.843, 1.000}, .fill=[this] { 
		if (v.FatJet().msoftdrop< HADTOP_SD_MASS_CUT_LOW)  return (double)-12;
		//if (v.FatJet().msoftdrop>=HADTOP_SD_MASS_CUT_HIGH) return (double)-11;
		return (double)v.FatJet().deepTagMD_TvsQCD; }, .axis_title="deepTagMD + min m_{sd}", .def_range={-12,1, 901}}); // Light Pink
sh.AddNewFillParams("deepTagMD_top_WP1",           { .nbin=4,  .bins={0.054, 0.391, 0.578, 0.843, 1.000}, .fill=[this] { return v.FatJet().deepTagMD_TvsQCD; }, .axis_title="deepTag (MD)", .def_range={0.054-1e-10, 1, 601}}); // Blue
sh.AddNewFillParams("deepTagMD_top_minsd_WP1",     { .nbin=4,  .bins={0.054, 0.391, 0.578, 0.843, 1.000}, .fill=[this] { 
		if (v.FatJet().msoftdrop<HADTOP_SD_MASS_CUT_LOW)  return (double)-12;
		//if (v.FatJet().msoftdrop>=HADTOP_SD_MASS_CUT_HIGH) return (double)-11;
		return (double)v.FatJet().deepTagMD_TvsQCD; }, .axis_title="deepTagMD + min m_{sd}", .def_range={0.054-1e-10,1, 901}}); // Light Pink
sh.AddNewFillParams("deepTag_top",                 { .nbin=4,  .bins={0.093, 0.745, 0.895, 0.986, 1.000}, .fill=[this] { return v.FatJet().deepTag_TvsQCD; }, .axis_title="deepTag", .def_range={-10,1, 633}}); // Red - noval at -10
sh.AddNewFillParams("deepTag_top_WP1",             { .nbin=4,  .bins={0.093, 0.745, 0.895, 0.986, 1.000}, .fill=[this] { return v.FatJet().deepTag_TvsQCD; }, .axis_title="deepTag",   .def_range={0.093-1e-10,1, 633}}); // Red
// W
sh.AddNewFillParams("tau21_softdrop",              { .nbin=8, .bins={0, 0.35, 0.45, 0.55, 0.75, 2, 3, 4, 5}, .fill=[this] { 
		if (v.FatJet().msoftdrop< HADW_SD_MASS_CUT_LOW)  return (double)3;
		if (v.FatJet().msoftdrop>=HADW_SD_MASS_CUT_HIGH) return (double)2;
		return v.FatJet().tau21;
		}, .axis_title="#tau_{32}, m_{sd}, b_{sj}", .def_range={0,5, 434}}); // Cyan
sh.AddNewFillParams("deepTagMD_W",                 { .nbin=3,  .bins={0.313, 0.802, 0.884, 1.000}, .fill=[this] { return v.FatJet().deepTagMD_WvsQCD; }, .axis_title="W deepTagMD", .def_range={-10,1.0, 600}}); // Blue - noval at -10
sh.AddNewFillParams("deepTagMD_W_minsd",           { .nbin=3,  .bins={0.313, 0.802, 0.884, 1.000}, .fill=[this] { 
		if (v.FatJet().msoftdrop< HADW_SD_MASS_CUT_LOW)  return (double)-12;
		//if (v.FatJet().msoftdrop>=HADW_SD_MASS_CUT_HIGH) return (double)-11;
		return (double)v.FatJet().deepTagMD_WvsQCD; }, .axis_title="W deepTagMD + min m_{sd}", .def_range={-12,1, 607}}); // Light Purple
sh.AddNewFillParams("deepTagMD_W_sd",              { .nbin=3,  .bins={0.313, 0.802, 0.884, 1.000}, .fill=[this] { 
		if (v.FatJet().msoftdrop< HADW_SD_MASS_CUT_LOW)  return (double)-12;
		if (v.FatJet().msoftdrop>=HADW_SD_MASS_CUT_HIGH) return (double)-11;
		return (double)v.FatJet().deepTagMD_WvsQCD; }, .axis_title="W deepTagMD + m_{sd}", .def_range={-12,1, 616}}); // Purple
sh.AddNewFillParams("deepTagMD_W_WP1",             { .nbin=3,  .bins={0.313, 0.802, 0.884, 1.000}, .fill=[this] { return v.FatJet().deepTagMD_WvsQCD; }, .axis_title="deepTag (MD)", .def_range={0.313-1e-10, 1, 600}}); // Blue
sh.AddNewFillParams("deepTagMD_W_WP2",             { .nbin=3,  .bins={0.313, 0.802, 0.884, 1.000}, .fill=[this] { return v.FatJet().deepTagMD_WvsQCD; }, .axis_title="deepTag (MD)", .def_range={0.802, 1, 600}}); // Blue
sh.AddNewFillParams("deepTagMD_W_minsd_WP1",       { .nbin=3,  .bins={0.313, 0.802, 0.884, 1.000}, .fill=[this] { 
		if (v.FatJet().msoftdrop<HADW_SD_MASS_CUT_LOW)  return (double)-12;
		//if (v.FatJet().msoftdrop>=HADW_SD_MASS_CUT_HIGH)  return (double)-11;
		return (double)v.FatJet().deepTagMD_WvsQCD; }, .axis_title="W deepTagMD + min m_{sd}", .def_range={0.313-1e-10,1, 607}}); // Light Purple
sh.AddNewFillParams("deepTagMD_W_minsd_WP2",       { .nbin=3,  .bins={0.313, 0.802, 0.884, 1.000}, .fill=[this] { 
		if (v.FatJet().msoftdrop<HADW_SD_MASS_CUT_LOW)  return (double)-12;
		//if (v.FatJet().msoftdrop>=HADW_SD_MASS_CUT_HIGH)  return (double)-11;
		return (double)v.FatJet().deepTagMD_WvsQCD; }, .axis_title="W deepTagMD + min m_{sd}", .def_range={0.802,1, 607}}); // Light Purple
sh.AddNewFillParams("deepTagMD_W_sd_WP1",          { .nbin=3,  .bins={0.313, 0.802, 0.884, 1.000}, .fill=[this] { 
		if (v.FatJet().msoftdrop<HADW_SD_MASS_CUT_LOW) return (double)-12;
		if (v.FatJet().msoftdrop>=HADW_SD_MASS_CUT_HIGH) return (double)-11;
		return (double)v.FatJet().deepTagMD_WvsQCD; }, .axis_title="W deepTagMD + m_{sd}", .def_range={0.313-1e-10,1, 616}}); // Purple
sh.AddNewFillParams("deepTagMD_W_sd_WP2",          { .nbin=3,  .bins={0.313, 0.802, 0.884, 1.000}, .fill=[this] { 
		if (v.FatJet().msoftdrop<HADW_SD_MASS_CUT_LOW) return (double)-12;
		if (v.FatJet().msoftdrop>=HADW_SD_MASS_CUT_HIGH) return (double)-11;
		return (double)v.FatJet().deepTagMD_WvsQCD; }, .axis_title="W deepTagMD + m_{sd}", .def_range={0.802,1, 616}}); // Purple
sh.AddNewFillParams("deepTag_W",                   { .nbin=3,  .bins={0.779, 0.981, 0.991, 1.000}, .fill=[this] { return v.FatJet().deepTag_WvsQCD; }, .axis_title="W deepTag", .def_range={-10,  1, 625}}); // Lighter Red - noval at -10
sh.AddNewFillParams("deepTag_W_WP1",               { .nbin=3,  .bins={0.779, 0.981, 0.991, 1.000}, .fill=[this] { return v.FatJet().deepTag_WvsQCD; }, .axis_title="W deepTag", .def_range={0.779-1e-10,1, 625}}); // Lighter Red
sh.AddNewFillParams("deepTag_W_WP2",               { .nbin=3,  .bins={0.779, 0.981, 0.991, 1.000}, .fill=[this] { return v.FatJet().deepTag_WvsQCD; }, .axis_title="W deepTag", .def_range={0.981,1, 625}}); // Lighter Red
// Z
sh.AddNewFillParams("deepTagMD_Z",                 { .nbin=10, .bins={0.20, 0.40, 0.50, 0.60, 0.70, 0.80, 0.85, 0.90, 0.95, 0.98, 1.00}, .fill=[this] { return v.FatJet().deepTagMD_ZvsQCD; }, .axis_title="Z deepTagMD", .def_range={-10,1.0, 602}}); // Dark Blue - noval at -10
sh.AddNewFillParams("deepTagMD_Z_minsd",           { .nbin=10, .bins={0.20, 0.40, 0.50, 0.60, 0.70, 0.80, 0.85, 0.90, 0.95, 0.98, 1.00}, .fill=[this] { 
		if (v.FatJet().msoftdrop< HADZ_SD_MASS_CUT_LOW)  return (double)-12;
		//if (v.FatJet().msoftdrop>=HADZ_SD_MASS_CUT_HIGH) return (double)-11;
		return (double)v.FatJet().deepTagMD_ZvsQCD; }, .axis_title="Z deepTagMD + min m_{sd}", .def_range={-12,1, 901}}); // Light Pink
sh.AddNewFillParams("deepTagMD_Z_sd",              { .nbin=10, .bins={0.20, 0.40, 0.50, 0.60, 0.70, 0.80, 0.85, 0.90, 0.95, 0.98, 1.00}, .fill=[this] { 
		if (v.FatJet().msoftdrop< HADZ_SD_MASS_CUT_LOW)  return (double)-12;
		if (v.FatJet().msoftdrop>=HADZ_SD_MASS_CUT_HIGH) return (double)-11;
		return (double)v.FatJet().deepTagMD_ZvsQCD; }, .axis_title="Z deepTagMD + m_{sd}", .def_range={-12,1, 615}}); // Deep Purple
sh.AddNewFillParams("deepTagMD_Z_WP1",             { .nbin=3,  .bins={0.3, 0.8, 0.9, 1.000}, .fill=[this] { return v.FatJet().deepTagMD_ZvsQCD; }, .axis_title="Z deepTag (MD)", .def_range={0.3-1e-10, 1, 602}}); // Dark Blue
sh.AddNewFillParams("deepTagMD_Z_WP2",             { .nbin=3,  .bins={0.3, 0.8, 0.9, 1.000}, .fill=[this] { return v.FatJet().deepTagMD_ZvsQCD; }, .axis_title="Z deepTag (MD)", .def_range={0.8, 1, 602}}); // Dark Blue
sh.AddNewFillParams("deepTagMD_Z_minsd_WP1",       { .nbin=3,  .bins={0.3, 0.8, 0.9, 1.000}, .fill=[this] { 
		if (v.FatJet().msoftdrop<HADZ_SD_MASS_CUT_LOW)  return (double)-12;
		//if (v.FatJet().msoftdrop>=HADZ_SD_MASS_CUT_HIGH)  return (double)-11;
		return (double)v.FatJet().deepTagMD_ZvsQCD; }, .axis_title="Z deepTagMD + min m_{sd}", .def_range={0.3-1e-10,1, 901}}); // Light Pink
sh.AddNewFillParams("deepTagMD_Z_minsd_WP2",       { .nbin=3,  .bins={0.3, 0.8, 0.9, 1.000}, .fill=[this] { 
		if (v.FatJet().msoftdrop<HADZ_SD_MASS_CUT_LOW)  return (double)-12;
		//if (v.FatJet().msoftdrop>=HADZ_SD_MASS_CUT_HIGH)  return (double)-11;
		return (double)v.FatJet().deepTagMD_ZvsQCD; }, .axis_title="Z deepTagMD + min m_{sd}", .def_range={0.8,1, 901}}); // Light Pink
sh.AddNewFillParams("deepTagMD_Z_sd_WP1",          { .nbin=3,  .bins={0.3, 0.8, 0.9, 1.000}, .fill=[this] { 
		if (v.FatJet().msoftdrop<HADZ_SD_MASS_CUT_LOW) return (double)-12;
		if (v.FatJet().msoftdrop>=HADZ_SD_MASS_CUT_HIGH) return (double)-11;
		return (double)v.FatJet().deepTagMD_ZvsQCD; }, .axis_title="Z deepTagMD + m_{sd}", .def_range={0.3-1e-10,1, 618}}); // Deep Purple
sh.AddNewFillParams("deepTagMD_Z_sd_WP2",          { .nbin=3,  .bins={0.3, 0.8, 0.9, 1.000}, .fill=[this] { 
		if (v.FatJet().msoftdrop<HADZ_SD_MASS_CUT_LOW) return (double)-12;
		if (v.FatJet().msoftdrop>=HADZ_SD_MASS_CUT_HIGH) return (double)-11;
		return (double)v.FatJet().deepTagMD_ZvsQCD; }, .axis_title="Z deepTagMD + m_{sd}", .def_range={0.8,1, 618}}); // Deep Purple
sh.AddNewFillParams("deepTag_Z",                   { .nbin=10, .bins={0.2, 0.40, 0.60, 0.70, 0.80, 0.85, 0.90, 0.95, 0.98, 0.99, 1.00}, .fill=[this] { return v.FatJet().deepTag_ZvsQCD; }, .axis_title="Z deepTag", .def_range={-10, 1, 634}}); // Dark Red - noval at -10
sh.AddNewFillParams("deepTag_Z_WP1",               { .nbin=3,  .bins={0.8, 0.95, 0.99, 1.000}, .fill=[this] { return v.FatJet().deepTag_ZvsQCD; }, .axis_title="Z deepTag", .def_range={0.80-1e-10,1, 634}}); // Dark Red
sh.AddNewFillParams("deepTag_Z_WP2",               { .nbin=3,  .bins={0.8, 0.95, 0.99, 1.000}, .fill=[this] { return v.FatJet().deepTag_ZvsQCD; }, .axis_title="Z deepTag", .def_range={0.95,1, 634}}); // Dark Red
// Higgs
sh.AddNewFillParams("deepTagMD_H",                 { .nbin=9, .bins={0.20, 0.40, 0.50, 0.60, 0.70, 0.80, 0.90, 0.95, 0.98, 1.00}, .fill=[this] { return v.FatJet().deepTagMD_HbbvsQCD; }, .axis_title="H deepTagMD", .def_range={-10,1.0, 601}}); // Blue - noval at -10
sh.AddNewFillParams("deepTagMD_H_minsd",           { .nbin=9, .bins={0.20, 0.40, 0.50, 0.60, 0.70, 0.80, 0.90, 0.95, 0.98, 1.00}, .fill=[this] { 
		if (v.FatJet().msoftdrop< HADH_SD_MASS_CUT_LOW)  return (double)-12;
		//if (v.FatJet().msoftdrop>=HADH_SD_MASS_CUT_HIGH) return (double)-11;
		return (double)v.FatJet().deepTagMD_HbbvsQCD; }, .axis_title="H deepTagMD + min m_{sd}", .def_range={-12,1, 901}}); // Light Pink
sh.AddNewFillParams("deepTagMD_H_sd",              { .nbin=9, .bins={0.20, 0.40, 0.50, 0.60, 0.70, 0.80, 0.90, 0.95, 0.98, 1.00}, .fill=[this] { 
		if (v.FatJet().msoftdrop< HADH_SD_MASS_CUT_LOW)  return (double)-12;
		if (v.FatJet().msoftdrop>=HADH_SD_MASS_CUT_HIGH) return (double)-11;
		return (double)v.FatJet().deepTagMD_HbbvsQCD; }, .axis_title="H deepTagMD + m_{sd}", .def_range={-12,1, 618}}); // Deep Purple
sh.AddNewFillParams("deepTagMD_H_WP2",             { .nbin=6,  .bins={0.3, 0.6, 0.65, 0.7, 0.8, 0.9, 1.000}, .fill=[this] { return v.FatJet().deepTagMD_HbbvsQCD; }, .axis_title="H deepTag (MD)", .def_range={0.6, 1, 601}}); // Blue
sh.AddNewFillParams("deepTagMD_H_minsd_WP2",       { .nbin=6,  .bins={0.3, 0.6, 0.6, 0.7, 0.8, 0.9, 1.000}, .fill=[this] { 
		if (v.FatJet().msoftdrop<HADH_SD_MASS_CUT_LOW)  return (double)-12;
		//if (v.FatJet().msoftdrop>=HADH_SD_MASS_CUT_HIGH)  return (double)-11;
		return (double)v.FatJet().deepTagMD_HbbvsQCD; }, .axis_title="H deepTagMD + min m_{sd}", .def_range={0.6,1, 901}}); // Light Pink
sh.AddNewFillParams("deepTagMD_H_sd_WP2",          { .nbin=6,  .bins={0.3, 0.6, 0.65, 0.7, 0.8, 0.9, 1.000}, .fill=[this] { 
		if (v.FatJet().msoftdrop<HADH_SD_MASS_CUT_LOW) return (double)-12;
		if (v.FatJet().msoftdrop>=HADH_SD_MASS_CUT_HIGH) return (double)-11;
		return (double)v.FatJet().deepTagMD_HbbvsQCD; }, .axis_title="H deepTagMD + m_{sd}", .def_range={0.6,1, 618}}); // Deep Purple
sh.AddNewFillParams("deepTag_H",                   { .nbin=10, .bins={0.2, 0.40, 0.60, 0.70, 0.80, 0.85, 0.90, 0.95, 0.98, 0.99, 1.00}, .fill=[this] { return v.FatJet().deepTag_H; }, .axis_title="H deepTag", .def_range={-10, 1, 633}}); // Red - noval at -10
sh.AddNewFillParams("deepTag_H_WP1",               { .nbin=4,  .bins={0.40, 0.8, 0.95, 0.99, 1.000}, .fill=[this] { return v.FatJet().deepTag_H; }, .axis_title="H deepTag", .def_range={0.4,1, 633}}); // Red
sh.AddNewFillParams("btagHbb",                     { .nbin=9, .bins={0.15, 0.3, 0.45, 0.60, 0.70, 0.80, 0.85, 0.90, 0.95, 1.00}, .fill=[this] { return v.FatJet().btagHbb; }, .axis_title="btag Hbb", .def_range={-2, 1, 841}}); // Teal - minimum at -1
sh.AddNewFillParams("btagHbb_WP2",                 { .nbin=4,  .bins={0.3, 0.6, 0.8, 0.9, 1.0},                                  .fill=[this] { return v.FatJet().btagHbb; }, .axis_title="btag Hbb", .def_range={0.6,1, 841}}); // Teal
sh.AddNewFillParams("btagDDBvLV2",                   { .nbin=9, .bins={0.15, 0.3, 0.45, 0.60, 0.70, 0.80, 0.85, 0.90, 0.95, 1.00}, .fill=[this] { return v.FatJet().btagDDBvLV2; }, .axis_title="DeepDoubleB", .def_range={-2, 1, 922}}); // DGray - minimum at -1


if (debug) std::cout<<"PlottingBase::define_histo_settings: ROC curve fillparams ok"<<std::endl;
if (debug) std::cout<<"PlottingBase::define_histo_settings: all fillparams ok"<<std::endl;

// Define histo types (for different object to loop on, and different cuts to apply)
// A new type should be defined for all different objects, depending on what we loop on
sh.AddHistoType("ele",                 "Electrons");
sh.AddHistoType("ele select",          "Electrons");
sh.AddHistoType("ele veto",            "Veto electrons");
sh.AddHistoType("ele tight noiso",     "Electrons");
sh.AddHistoType("syst ele",            "Electrons");
sh.AddHistoType("syst ele select",     "Electrons");
sh.AddHistoType("syst ele veto",       "Veto electrons");
sh.AddHistoType("mu",                  "Muons");
sh.AddHistoType("mu select",           "Muons");
sh.AddHistoType("mu veto",             "Veto muons");
sh.AddHistoType("mu tight noiso",      "Muons");
sh.AddHistoType("syst mu",             "Muons");
sh.AddHistoType("syst mu select",      "Muons");
sh.AddHistoType("syst mu veto",        "Veto muons");
sh.AddHistoType("syst mu tight noiso", "Muons");
sh.AddHistoType("tau veto",            "Veto taus");
sh.AddHistoType("syst tau veto",       "Veto taus");
sh.AddHistoType("pho",                 "Photons");
sh.AddHistoType("prepho",              "Pre-selected photons");
sh.AddHistoType("syst pho",            "Photons");
sh.AddHistoType("syst prepho",         "Pre-selected photons");
sh.AddHistoType("AK4",                 "Jets");
sh.AddHistoType("syst AK4",            "Jets");
sh.AddHistoType("b",                   "b-tagged jets");
sh.AddHistoType("b loose",             "Loose b-tagged jets");
sh.AddHistoType("syst b",              "b-tagged jets");
sh.AddHistoType("syst b loose",        "Loose b-tagged jets");
sh.AddHistoType("megajet",             "Megajets");
sh.AddHistoType("syst megajet",        "Megajets");
sh.AddHistoType("AK8",                 "AK8 jets");
sh.AddHistoType("AK8Mass",                 "AK8Mass jets");
sh.AddHistoType("syst AK8",            "AK8 jets");
sh.AddHistoType("hadtop",              "Tops (had.)");
sh.AddHistoType("leptop",              "Tops (lep.)");
sh.AddHistoType("leptop cand",         "Top candidates (lep.)");
sh.AddHistoType("hadw",                "Ws (had.)");
sh.AddHistoType("hadz",                "Zs (had.)");
sh.AddHistoType("hadh",                "Hs (H#rightarrowb#bar{b})");
sh.AddHistoType("syst hadtop",         "Tops (had.)");
sh.AddHistoType("syst leptop",         "Tops (lep.)");
sh.AddHistoType("syst leptop cand",    "Top candidates (lep.)");
sh.AddHistoType("syst hadw",           "Ws (had.)");
sh.AddHistoType("syst hadz",           "Zs (had.)");
sh.AddHistoType("syst hadh",           "Hs (H#rightarrowb#bar{b})");
sh.AddHistoType("gen lep",             "Gen-leptons");
sh.AddHistoType("gen ele",             "Gen-electrons");
sh.AddHistoType("gen mu",              "Gen-muons");
sh.AddHistoType("gen hadW",            "Gen-Ws (had.)");
sh.AddHistoType("gen hadZ",            "Gen-Zs (had.)");
sh.AddHistoType("gen hadV",            "Gen-Vs (had.)");
sh.AddHistoType("gen hadH",            "Gen-Hs (had.)");
sh.AddHistoType("gen top",             "Gen-tops");
sh.AddHistoType("gen hadtop",          "Gen-tops (had.)");
sh.AddHistoType("gen leptop",          "Gen-tops (lep.)");
sh.AddHistoType("evt",                 "Events / bin");
sh.AddHistoType("syst evt",            "Events / bin");

}

//_______________________________________________________
//              Define Histograms here
void
PlottingBase::define_analysis_histos(const Weighting& w, const unsigned int& syst_nSyst, const unsigned int& syst_index) {

	//__________________________________
	//        Define Smarthistos
	//__________________________________

	// Usage of AddHistos:
	// sh.AddHistos(type, { .fill=fill parameter(s), .pfs={list of posfix names}, .cuts={list of cuts},.draw="ROOT Draw() options", .opt="SmartHistos options", .ranges={plot ranges and overridden legend location}});
	// 1st param: string, the object/event type defined by the first parameter in AddHistoType()
	// 2nd param (.fill): string, either the name of a FillParam using the first parameter of AddNeFillParams() for a 1D histo, or two fillparams separated by "_vs_" for a 2D one
	// 3rd param (.pfs):  vector of strings for each Postfix name defined by the first parameter in AddNewPostfix(), supports up to 5 Postfix
	//                    N.B: for 1D plots, the first postfix is used to draw different plots on the same canvas, while creating multiple plots with the rest
	// 4th param (.cuts): vector of cuts before filling (I do not encourage the usage, because usually postfixes work nicer by attaching a string to the plot name)
	// 5th param (.draw): The option to use when using the TH1D/TH2D.Draw() method
	// 6th param (.opt):  SmartHistos specific options, some common examples:
	//   "Stack"+"N"   : Make a stack histo for all postfix, except the first N (can be data, signals, etc.)
	//   "Log"         : Log Y or Z scale
	//   "LogX"        : Log X scale
	//   "TwoCol"+"XY" : Split legend to two columns, and specify how many rows should each hav maximum
	//   "AddInt"      : Add integral of the histogram to the legend
	//   "AddRatio"    : Create a ratio of either 1st pf / 2nd pf, or 1st and pf/stacked histo
	//   There are many more, please peek into source code for complete list or see other examples
	// 7th .ranges: List of axis ranges in order: xlow,xhigh, ylow,yhigh, then  zlow,zhigh for 2D plot 
	//              OR the location of the top left edge of the legend (x1,y2), the legend size is auto adjusted 
	//              (by setting x2 and y1 depending on the number of entries)

	/*

Examples:

	// Single stack plot
	sh.AddHistos("evt", { .fill="MRR2", .pfs={"StackPlotTopSignal","Blind","SR_Had_1htop"}, .cuts={},.draw="",.opt="LogStack4AddRatioTwoCol48AddIntApproval45",.ranges={0,0, 1.01e-2,1e6, 0.3,0.86}});

	// Multiple stack plots in multiple regions (hadronic Higgs)
	for (const auto& enum_and_name : magic_enum::enum_entries<Region>()) {
	Region region = region.first;
	std::string cut(region.second);
	if (TString(cut).BeginsWith("SR_Had_")&&TString(cut).Constains("H")) {
	sh.SetHistoWeights({ [&w,region] { return w.sf_weight[region]; } });
	for (auto std_plot : {"HT", "MET", "MR", "R2", "MRR2"})
	sh.AddHistos(s+"evt", { .fill=c+std_plot, .pfs={"StackPlotHSignal","Blind",cut},  .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
	}
	}

*/

	// Systematics:

	// The systematics of the plot are hidden in an additional dimension added to the histogram
	// eg.  a TH1D and it's systematic variations are stored in a TH2D
	// Each extra dimensional bin contain a variation of the underlying distribution
	// To enable this, a special dummy axis needs to be added which is called "Counts"
	// The string "Counts_vs_" is added to the plot name
	// and the "syst " is attached to the histogram type so the code knows to fill this
	// additional axis

	bool doSyst = (syst_nSyst>0);
	bool systematics = 1;

	std::string s = "";
	std::string c = "";
	if (systematics) {
		s = "syst ";
		c = "Counts_vs_";
	}

	std::vector<std::string> standard_plots;
	if (doSyst) standard_plots = {"HT", "MET", "HTMET", "MRFine", "MR", "R2Fine", "R2", "MRR2", "newMRR2", "MRR2Bin"};
	else        standard_plots = {"HT", "HTFine", "METPhi", "METFine", "MET", "HTMET", "MRFine", "MR", "R2Fine", "R2", "MRR2", "newMRR2", "MRR2Bin"};

	// -------------------------------------------------------------------------
	//                                   Trigger

	// Hadronic triggers
	sh.SetHistoWeights({ [] { return 1; } });
	for (auto plot : {"HadronicMeasurements", "HadronicMeasurementsNoR2", "HadronicMeasurementsInvR2", "NonIsoLepMeasurements"}) {
		std::string cut = "Baseline";
		if (std::string(plot)=="HadronicMeasurementsNoR2") cut = "BaselineNoR2";
		if (std::string(plot)=="HadronicMeasurementsInvR2") cut = "BaselineInvR2";

		// Efficiency
		for (auto trigger : std::vector<std::string>({ "HLTEff_Hadronic" })) {
			for (auto std_plot : standard_plots)
				sh.AddHistos("evt", { .fill=trigger+"_vs_"+std_plot,             .pfs={                plot,"Year",cut}, .cuts={}, .draw="PE1",  .opt=o_1or2d_d+"TwoCol22", .ranges={0,0, 0,1, 0.5,0.5} });
			sh.AddHistos("evt", { .fill=trigger+"_vs_Bin",                     .pfs={                plot,"Year",cut}, .cuts={}, .draw="PE1",  .opt=o_1or2d_d+"TwoCol22", .ranges={0,0, 0,1, 0.5,0.5} });
			sh.AddHistos("evt", { .fill=trigger+"_vs_HT2DBins",                .pfs={                plot,"Year",cut}, .cuts={}, .draw="PE1",  .opt=o_1or2d_d+"TwoCol22", .ranges={0,0, 0,1, 0.5,0.5} });
			sh.AddHistos("evt", { .fill=trigger+"_vs_MET2DBins",               .pfs={                plot,"Year",cut}, .cuts={}, .draw="PE1",  .opt=o_1or2d_d+"TwoCol22", .ranges={0,0, 0,1, 0.5,0.5} });
			sh.AddHistos("evt", { .fill=trigger+"_vs_HT1MET",                  .pfs={                plot,"Year",cut}, .cuts={}, .draw="PE1",  .opt=o_1or2d_d+"TwoCol22", .ranges={0,0, 0,1, 0.5,0.5} });
			sh.AddHistos("evt", { .fill=trigger+"_vs_HT2MET",                  .pfs={                plot,"Year",cut}, .cuts={}, .draw="PE1",  .opt=o_1or2d_d+"TwoCol22", .ranges={0,0, 0,1, 0.5,0.5} });
			sh.AddHistos("evt", { .fill=trigger+"_vs_HT3MET",                  .pfs={                plot,"Year",cut}, .cuts={}, .draw="PE1",  .opt=o_1or2d_d+"TwoCol22", .ranges={0,0, 0,1, 0.5,0.5} });
			sh.AddHistos("evt", { .fill=trigger+"_vs_HTMETPrev",               .pfs={                plot,"Year",cut}, .cuts={}, .draw="PE1",  .opt=o_1or2d_d+"TwoCol22", .ranges={0,0, 0,1, 0.5,0.5} });
			sh.AddHistos("evt", { .fill=trigger+"_vs_MRR2NoPho",               .pfs={                plot,"Year",cut}, .cuts={}, .draw="PE1",  .opt=o_1or2d_d+"TwoCol22", .ranges={0,0, 0,1, 0.5,0.5} });
			sh.AddHistos("evt", { .fill=trigger+"_vs_METNoPho",                .pfs={                plot,"Year",cut}, .cuts={}, .draw="PE1",  .opt=o_1or2d_d+"TwoCol22", .ranges={0,0, 0,1, 0.5,0.5} });
			sh.AddHistos("evt", { .fill=trigger+"_vs_HTJet1AK8Pt",             .pfs={                plot,"Year",cut}, .cuts={}, .draw="PE1",  .opt=o_1or2d_d+"TwoCol22", .ranges={0,0, 0,1, 0.5,0.5} });
			sh.AddHistos("evt", { .fill=trigger+"_vs_HTJet1AK8PtLow",          .pfs={                plot,"Year",cut}, .cuts={}, .draw="PE1",  .opt=o_1or2d_d+"TwoCol22", .ranges={0,0, 0,1, 0.5,0.5} });
			sh.AddHistos("evt", { .fill=trigger+"_vs_HTJet1AK8PtHigh",         .pfs={                plot,"Year",cut}, .cuts={}, .draw="PE1",  .opt=o_1or2d_d+"TwoCol22", .ranges={0,0, 0,1, 0.5,0.5} });
			sh.AddHistos("evt", { .fill=trigger+"_vs_PhotonPtBins",            .pfs={                plot,"Year",cut}, .cuts={}, .draw="PE1",  .opt=o_1or2d_d+"TwoCol22", .ranges={0,0, 0,1, 0.5,0.5} });
			sh.AddHistos("evt", { .fill=trigger+"_vs_HTPhotonPt",              .pfs={                plot,"Year",cut}, .cuts={}, .draw="PE1",  .opt=o_1or2d_d+"TwoCol22", .ranges={0,0, 0,1, 0.5,0.5} });
			sh.AddHistos("evt", { .fill=trigger+"_vs_HT1PhotonPt",             .pfs={                plot,"Year",cut}, .cuts={}, .draw="PE1",  .opt=o_1or2d_d+"TwoCol22", .ranges={0,0, 0,1, 0.5,0.5} });
			sh.AddHistos("evt", { .fill=trigger+"_vs_HT2PhotonPt",             .pfs={                plot,"Year",cut}, .cuts={}, .draw="PE1",  .opt=o_1or2d_d+"TwoCol22", .ranges={0,0, 0,1, 0.5,0.5} });
			sh.AddHistos("evt", { .fill=trigger+"_vs_HT3PhotonPt",             .pfs={                plot,"Year",cut}, .cuts={}, .draw="PE1",  .opt=o_1or2d_d+"TwoCol22", .ranges={0,0, 0,1, 0.5,0.5} });      
		}

		// Denumerator
		for (auto std_plot : standard_plots)
			sh.AddHistos("evt", { .fill=std_plot,             .pfs={plot,"Year",cut},          .cuts={}, .draw="HIST", .opt=o_1or2d_d+"LogTwoCol22", .ranges={0,0, 1e-1,1e8, 0.35,0.86} });
		sh.AddHistos(s+"evt", { .fill=c+"MRR2NoPho",        .pfs={plot,"Year",cut},          .cuts={}, .draw="HIST", .opt=o_1or2d_d+"LogTwoCol22", .ranges={0,0, 1e-1,1e8, 0.35,0.86} });
		sh.AddHistos("evt", { .fill="METFine_vs_HTFine",    .pfs={plot,"Year",cut},          .cuts={}, .draw="COLZ", .opt=o_1or2d_d+"Log",         .ranges={0,0, 0,0} });
		sh.AddHistos("evt", { .fill="MET_vs_HT",            .pfs={plot,"Year",cut},          .cuts={}, .draw="COLZ", .opt=o_1or2d_d+"Log",         .ranges={0,0, 0,0} });
		sh.AddHistos("evt", { .fill="MET2DBins_vs_HT2DBins",.pfs={plot,"Year",cut},          .cuts={}, .draw="COLZ", .opt=o_1or2d_d+"Log",         .ranges={0,0, 0,0} });
		sh.AddHistos("evt", { .fill="HT2DBins",             .pfs={plot,"Year",cut},          .cuts={}, .draw="HIST", .opt=o_1or2d_d+"LogTwoCol22", .ranges={0,0, 1e-1,1e8, 0.35,0.86} });
		sh.AddHistos("evt", { .fill="MET2DBins",            .pfs={plot,"Year",cut},          .cuts={}, .draw="HIST", .opt=o_1or2d_d+"LogTwoCol22", .ranges={0,0, 1e-1,1e8, 0.35,0.86} });
		sh.AddHistos("evt", { .fill="HT1MET",               .pfs={plot,"Year",cut},          .cuts={}, .draw="HIST", .opt=o_1or2d_d+"LogTwoCol22", .ranges={0,0, 1e-1,1e8, 0.35,0.86} });
		sh.AddHistos("evt", { .fill="HT2MET",               .pfs={plot,"Year",cut},          .cuts={}, .draw="HIST", .opt=o_1or2d_d+"LogTwoCol22", .ranges={0,0, 1e-1,1e8, 0.35,0.86} });
		sh.AddHistos("evt", { .fill="HT3MET",               .pfs={plot,"Year",cut},          .cuts={}, .draw="HIST", .opt=o_1or2d_d+"LogTwoCol22", .ranges={0,0, 1e-1,1e8, 0.35,0.86} });
		sh.AddHistos("evt", { .fill="HTMETPrev",            .pfs={plot,"Year",cut},          .cuts={}, .draw="HIST", .opt=o_1or2d_d+"LogTwoCol22", .ranges={0,0, 1e-1,1e8, 0.35,0.86} });
	}

	// -------------------------------------------------------------------------
	//                                 Photons

	for (auto region : {Region::CR_1PhoInv}){
		sh.SetHistoWeights({ [&w,region] { return w.w_nm1[region][9]*w.triggereff_pho;} });
		std::string cut(magic_enum::enum_name(region));
    // Data fake template ------------------------------------
    sh.AddHistos("prepho", {.fill="MRR2NoPhoBins_vs_PhotonCHIso_preslectphoptREBin", .pfs={"Data_MC","FakePhoton",cut+"_Excl1Pho","Year","EB_EE"}, .cuts={}, .draw=d, .opt={"COLZLogX"}, .ranges={}});
    //sh.AddHistos("prepho", {.fill="NJetNoPhoBins_vs_PhotonCHIso_preslectphoptREBin", .pfs={"Data_MC","FakePhoton",cut+"_Excl1Pho","Year","EB_EE"}, .cuts={}, .draw=d, .opt={"COLZLogX"}, .ranges={}});    
    //sh.AddHistos("prepho", {.fill="1or2Boost_vs_PhotonCHIso_preslectphoptREBin", .pfs={"Data_MC","FakePhoton",cut+"_Excl1Pho","Year","EB_EE"}, .cuts={}, .draw=d, .opt={"COLZLogX"}, .ranges={}});    
    sh.AddHistos("prepho", {.fill="MRR2NoPhoBins_vs_PhotonCHIso_preslectphoptREBin", .pfs={"Data_MC","FakePhoton",cut+"_Excl1Pho1M","Year","EB_EE"}, .cuts={}, .draw=d, .opt={"COLZLogX"}, .ranges={}});
    //sh.AddHistos("prepho", {.fill="NJetNoPhoBins_vs_PhotonCHIso_preslectphoptREBin", .pfs={"Data_MC","FakePhoton",cut+"_Excl1Pho1M","Year","EB_EE"}, .cuts={}, .draw=d, .opt={"COLZLogX"}, .ranges={}});
    //sh.AddHistos("prepho", {.fill="1or2Boost_vs_PhotonCHIso_preslectphoptREBin", .pfs={"Data_MC","FakePhoton",cut+"_Excl1Pho1M","Year","EB_EE"}, .cuts={}, .draw=d, .opt={"COLZLogX"}, .ranges={}});    
    // MC prompt template ------------------------------------
    sh.AddHistos("prepho", {.fill="MRR2NoPhoBins_vs_PhotonCHIso_preslectphoptREBin", .pfs={"Data_MC","PromptPhoton",cut+"_Excl1Pho","Year","EB_EE"}, .cuts={}, .draw=d, .opt={"COLZLogX"}, .ranges={}});
    //sh.AddHistos("prepho", {.fill="NJetNoPhoBins_vs_PhotonCHIso_preslectphoptREBin", .pfs={"Data_MC","PromptPhoton",cut+"_Excl1Pho","Year","EB_EE"}, .cuts={}, .draw=d, .opt={"COLZLogX"}, .ranges={}});
    //sh.AddHistos("prepho", {.fill="1or2Boost_vs_PhotonCHIso_preslectphoptREBin", .pfs={"Data_MC","PromptPhoton",cut+"_Excl1Pho","Year","EB_EE"}, .cuts={}, .draw=d, .opt={"COLZLogX"}, .ranges={}});
    sh.AddHistos("prepho", {.fill="MRR2NoPhoBins_vs_PhotonCHIso_preslectphoptREBin", .pfs={"Data_MC","PromptPhoton",cut+"_Excl1Pho1M","Year","EB_EE"}, .cuts={}, .draw=d, .opt={"COLZLogX"}, .ranges={}});
    //sh.AddHistos("prepho", {.fill="NJetNoPhoBins_vs_PhotonCHIso_preslectphoptREBin", .pfs={"Data_MC","PromptPhoton",cut+"_Excl1Pho1M","Year","EB_EE"}, .cuts={}, .draw=d, .opt={"COLZLogX"}, .ranges={}});
    //sh.AddHistos("prepho", {.fill="1or2Boost_vs_PhotonCHIso_preslectphoptREBin", .pfs={"Data_MC","PromptPhoton",cut+"_Excl1Pho1M","Year","EB_EE"}, .cuts={}, .draw=d, .opt={"COLZLogX"}, .ranges={}});   
    // Data chiso distribution for fit ------------------------------------
    sh.AddHistos("prepho", {.fill="MRR2NoPhoBins_vs_PhotonCHIso_preslectphoptREBin", .pfs={"Data_MC","SelectNoIsoPhoton",cut+"_Excl1Pho","Year","EB_EE"}, .cuts={}, .draw=d, .opt={"COLZLogX"}, .ranges={}});
    //sh.AddHistos("prepho", {.fill="NJetNoPhoBins_vs_PhotonCHIso_preslectphoptREBin", .pfs={"Data_MC","SelectNoIsoPhoton",cut+"_Excl1Pho","Year","EB_EE"}, .cuts={}, .draw=d, .opt={"COLZLogX"}, .ranges={}});
    //sh.AddHistos("prepho", {.fill="1or2Boost_vs_PhotonCHIso_preslectphoptREBin", .pfs={"Data_MC","SelectNoIsoPhoton",cut+"_Excl1Pho","Year","EB_EE"}, .cuts={}, .draw=d, .opt={"COLZLogX"}, .ranges={}});       
    
    sh.AddHistos("prepho", { .fill="DirectFraction_vs_MRR2NoPhoBins",                .pfs={"Background","Prompt","EB","Year",cut}, .cuts={},.draw="PE1",.opt=o_1or2d_s,.ranges={0,0, 0,1, 0.4,0.5}});
    sh.AddHistos("prepho", { .fill="DirectFraction_vs_MRR2NoPhoBins",                .pfs={"Background","Prompt","EE","Year",cut}, .cuts={},.draw="PE1",.opt=o_1or2d_s,.ranges={0,0, 0,1, 0.4,0.5}});
    //sh.AddHistos("prepho", { .fill="DirectFraction_vs_NJetNoPhoBins",                .pfs={"Background","Prompt","EB","Year",cut}, .cuts={},.draw="PE1",.opt=o_1or2d_s,.ranges={0,0, 0,1, 0.4,0.5}});
    //sh.AddHistos("prepho", { .fill="DirectFraction_vs_NJetNoPhoBins",                .pfs={"Background","Prompt","EE","Year",cut}, .cuts={},.draw="PE1",.opt=o_1or2d_s,.ranges={0,0, 0,1, 0.4,0.5}});
    //sh.AddHistos("prepho", { .fill="DirectFraction_vs_1or2Boost",                .pfs={"Background","Prompt","EB","Year",cut}, .cuts={},.draw="PE1",.opt=o_1or2d_s,.ranges={0,0, 0,1, 0.4,0.5}});
    //sh.AddHistos("prepho", { .fill="DirectFraction_vs_1or2Boost",                .pfs={"Background","Prompt","EE","Year",cut}, .cuts={},.draw="PE1",.opt=o_1or2d_s,.ranges={0,0, 0,1, 0.4,0.5}});
    
    }

	// ----------------------------------------------------------------------------------------------
	//                                    New preselection segions
	//-----------------------------------------------------------------------------------------------

	if (doSyst) {
		standard_plots = {"HT", "METPhi", "MET", "MR", "R2"};
	} else {
		standard_plots = {"HT", "METPhi", "METFine", "MET", "PFMETOverCaloMET", "MRFine",
			"MR", "R2Fine", "R2", "HT1MET", "HT2MET", "HT3MET"};
	}
	//standard_plots.push_back("HTFine");
	//standard_plots.push_back("HTMET");

	for (auto region : {Region::Pre}) {
		sh.SetHistoWeights({ [&w,region] { return w.sf_weight[region]; } });
		std::string cut(magic_enum::enum_name(region));
		// Stack plots
		std::string opt  = o_stk_d;
		for (auto std_plot : standard_plots)
			sh.AddHistos("evt",     { .fill=std_plot,                  .pfs={"StackPlot","Year",cut}, .cuts={},.draw=d,.opt=opt,.ranges=r_Stk9});
		sh.AddHistos(s+"evt",     { .fill=c+"MRR2",                  .pfs={"StackPlot","Year",cut}, .cuts={},.draw=d,.opt=opt,.ranges=r_Stk9});
		sh.AddHistos(s+"evt",     { .fill=c+"MRR2",                  .pfs={"StackPlot","run2",cut}, .cuts={},.draw=d,.opt=opt,.ranges=r_Stk9});
		sh.AddHistos(s+"evt",     { .fill=c+"newMRR2",               .pfs={"StackPlot","Year",cut}, .cuts={},.draw=d,.opt=opt,.ranges=r_Stk9});
		sh.AddHistos(s+"evt",     { .fill=c+"newMRR2",               .pfs={"StackPlot","run2",cut}, .cuts={},.draw=d,.opt=opt,.ranges=r_Stk9});
		sh.AddHistos(  "evt",     { .fill="NJet",                    .pfs={"StackPlot","Year",cut}, .cuts={},.draw=d,.opt=opt,.ranges=r_Stk9});
		sh.AddHistos(  "evt",     { .fill="NJet",                    .pfs={"StackPlot","run2",cut}, .cuts={},.draw=d,.opt=opt,.ranges=r_Stk9});
		sh.AddHistos(  "evt",     { .fill="MTBoost",                 .pfs={"StackPlot","Year",cut}, .cuts={},.draw=d,.opt=opt,.ranges=r_Stk9});
		sh.AddHistos(  "evt",     { .fill="DeltaPhi",                .pfs={"StackPlot","Year",cut}, .cuts={},.draw=d,.opt=opt,.ranges=r_Stk9});
		sh.AddHistos(  "evt",     { .fill="MinDeltaPhi",             .pfs={"StackPlot","Year",cut}, .cuts={},.draw=d,.opt=opt,.ranges=r_Stk9});
		sh.AddHistos(  "evt",     { .fill="DeltaPhiMuonJetMET",      .pfs={"StackPlot","Year",cut}, .cuts={},.draw=d,.opt=opt,.ranges=r_Stk9});
		sh.AddHistos(  "evt",     { .fill="ElePt",                   .pfs={"StackPlot","Year",cut}, .cuts={},.draw=d,.opt=opt,.ranges=r_Stk9});
		sh.AddHistos(  "evt",     { .fill="MuPt",                    .pfs={"StackPlot","Year",cut}, .cuts={},.draw=d,.opt=opt,.ranges=r_Stk9});
		sh.AddHistos(  "tau veto",{ .fill="VetoTauPt",               .pfs={"StackPlot","Year",cut}, .cuts={},.draw=d,.opt=opt,.ranges=r_Stk9});
		sh.AddHistos(  "tau veto",{ .fill="VetoTauEta",              .pfs={"StackPlot","Year",cut}, .cuts={},.draw=d,.opt=opt,.ranges=r_Stk9});
		sh.AddHistos(  "evt",     { .fill="PhotonPtBins",            .pfs={"StackPlot","Year",cut}, .cuts={},.draw=d,.opt=opt,.ranges=r_Stk9});
		sh.AddHistos(  "evt",     { .fill="PrePhotonPtBins",         .pfs={"StackPlot","Year",cut}, .cuts={},.draw=d,.opt=opt,.ranges=r_Stk9});
		sh.AddHistos(  "evt",     { .fill="HTPhotonPt",              .pfs={"StackPlot","Year",cut}, .cuts={},.draw=d,.opt=opt,.ranges=r_Stk9});
		sh.AddHistos(  "AK4",     { .fill="JetPtBins",               .pfs={"StackPlot","Year",cut}, .cuts={},.draw=d,.opt=opt,.ranges=r_Stk9});
		sh.AddHistos(  "AK4",     { .fill="JetPt",                   .pfs={"StackPlot","Year",cut}, .cuts={},.draw=d,.opt=opt,.ranges=r_Stk9});
		sh.AddHistos(  "AK4",     { .fill="JetEta",                  .pfs={"StackPlot","Year",cut}, .cuts={},.draw=d,.opt=opt,.ranges=r_Stk9});
		sh.AddHistos(  "AK4",     { .fill="JetPhi",                  .pfs={"StackPlot","Year",cut}, .cuts={},.draw=d,.opt=opt,.ranges=r_Stk9});
		sh.AddHistos(  "AK4",     { .fill="JetDeepB",                .pfs={"StackPlot","Year",cut}, .cuts={},.draw=d,.opt=opt,.ranges=r_Stk9});
		sh.AddHistos(  "megajet", { .fill="MegaJetPt",               .pfs={"StackPlot","Year",cut}, .cuts={},.draw=d,.opt=opt,.ranges=r_Stk9});
		sh.AddHistos(  "megajet", { .fill="MegaJetEta",              .pfs={"StackPlot","Year",cut}, .cuts={},.draw=d,.opt=opt,.ranges=r_Stk9});
		sh.AddHistos(  "megajet", { .fill="MegaJetPhi",              .pfs={"StackPlot","Year",cut}, .cuts={},.draw=d,.opt=opt,.ranges=r_Stk9});
		sh.AddHistos(  "evt",     { .fill="NW",                      .pfs={"StackPlot","Year",cut}, .cuts={},.draw=d,.opt=opt,.ranges=r_Stk9});
		sh.AddHistos(  "evt",     { .fill="NZ",                      .pfs={"StackPlot","Year",cut}, .cuts={},.draw=d,.opt=opt,.ranges=r_Stk9});
		sh.AddHistos(  "evt",     { .fill="NV",                      .pfs={"StackPlot","Year",cut}, .cuts={},.draw=d,.opt=opt,.ranges=r_Stk9});
		sh.AddHistos(  "evt",     { .fill="NTop",                    .pfs={"StackPlot","Year",cut}, .cuts={},.draw=d,.opt=opt,.ranges=r_Stk9});
		sh.AddHistos(  "evt",     { .fill="NH",                      .pfs={"StackPlot","Year",cut}, .cuts={},.draw=d,.opt=opt,.ranges=r_Stk9});
		sh.AddHistos(  "evt",     { .fill="NLepTop",                 .pfs={"StackPlot","Year",cut}, .cuts={},.draw=d,.opt=opt,.ranges=r_Stk9});
		sh.AddHistos(  "evt",     { .fill="NLepJet",                 .pfs={"StackPlot","Year",cut}, .cuts={},.draw=d,.opt=opt,.ranges=r_Stk9});
    sh.AddHistos(  "hadtop",  { .fill="HadTopMass",              .pfs={"StackPlot","Year",cut}, .cuts={},.draw=d,.opt=opt,.ranges=r_Stk9});
    sh.AddHistos(  "leptop",  { .fill="LepTopMass",              .pfs={"StackPlot","Year",cut}, .cuts={},.draw=d,.opt=opt,.ranges=r_Stk9});
    sh.AddHistos(  "hadw",    { .fill="HadWMass",                .pfs={"StackPlot","Year",cut}, .cuts={},.draw=d,.opt=opt,.ranges=r_Stk9});
    sh.AddHistos(  "hadz",    { .fill="HadZMass",                .pfs={"StackPlot","Year",cut}, .cuts={},.draw=d,.opt=opt,.ranges=r_Stk9});
    sh.AddHistos(  "hadh",    { .fill="HadHMass",                .pfs={"StackPlot","Year",cut}, .cuts={},.draw=d,.opt=opt,.ranges=r_Stk9});
		sh.SetHistoWeights({ [&w,region] { return w.w_nm1[region][9]*w.triggereff_had_nor2; } });
		for (auto std_plot : standard_plots)
			sh.AddHistos("evt",     { .fill=std_plot,                  .pfs={"StackPlot","Year",cut+"_ExclR2"}, .cuts={},.draw=d,.opt=opt,.ranges=r_Stk9});
		sh.AddHistos(s+"evt",     { .fill=c+"MRR2",                  .pfs={"StackPlot","Year",cut+"_ExclR2"}, .cuts={},.draw=d,.opt=opt,.ranges=r_Stk9});
		sh.AddHistos(s+"evt",     { .fill=c+"MRR2",                  .pfs={"StackPlot","run2",cut+"_ExclR2"}, .cuts={},.draw=d,.opt=opt,.ranges=r_Stk9});
		sh.AddHistos(  "evt",     { .fill="NJet",                    .pfs={"StackPlot","Year",cut+"_ExclR2"}, .cuts={},.draw=d,.opt=opt,.ranges=r_Stk9});
		sh.AddHistos(  "evt",     { .fill="MTBoost",                 .pfs={"StackPlot","Year",cut+"_ExclR2"}, .cuts={},.draw=d,.opt=opt,.ranges=r_Stk9});
		sh.AddHistos(  "evt",     { .fill="DeltaPhi",                .pfs={"StackPlot","Year",cut+"_ExclR2"}, .cuts={},.draw=d,.opt=opt,.ranges=r_Stk9});
		sh.AddHistos(  "evt",     { .fill="MinDeltaPhi",             .pfs={"StackPlot","Year",cut+"_ExclR2"}, .cuts={},.draw=d,.opt=opt,.ranges=r_Stk9});
		sh.AddHistos(  "AK4",     { .fill="JetPtBins",               .pfs={"StackPlot","Year",cut+"_ExclR2"}, .cuts={},.draw=d,.opt=opt,.ranges=r_Stk9});
		sh.AddHistos(  "AK4",     { .fill="JetPt",                   .pfs={"StackPlot","Year",cut+"_ExclR2"}, .cuts={},.draw=d,.opt=opt,.ranges=r_Stk9});
		sh.AddHistos(  "AK4",     { .fill="JetEta",                  .pfs={"StackPlot","Year",cut+"_ExclR2"}, .cuts={},.draw=d,.opt=opt,.ranges=r_Stk9});
		sh.AddHistos(  "AK4",     { .fill="JetPhi",                  .pfs={"StackPlot","Year",cut+"_ExclR2"}, .cuts={},.draw=d,.opt=opt,.ranges=r_Stk9});
		sh.AddHistos(  "AK4",     { .fill="JetDeepB",                .pfs={"StackPlot","Year",cut+"_ExclR2"}, .cuts={},.draw=d,.opt=opt,.ranges=r_Stk9});
		sh.AddHistos(  "megajet", { .fill="MegaJetPt",               .pfs={"StackPlot","Year",cut+"_ExclR2"}, .cuts={},.draw=d,.opt=opt,.ranges=r_Stk9});
		sh.AddHistos(  "megajet", { .fill="MegaJetEta",              .pfs={"StackPlot","Year",cut+"_ExclR2"}, .cuts={},.draw=d,.opt=opt,.ranges=r_Stk9});
		sh.AddHistos(  "megajet", { .fill="MegaJetPhi",              .pfs={"StackPlot","Year",cut+"_ExclR2"}, .cuts={},.draw=d,.opt=opt,.ranges=r_Stk9});
		// Non-hadronic object selections - can be used to validate trigger efficiencies
		for (std::string nohad : {"Lep", "Tau", "1Ele", "1Muon", "Pho", "1PrePho", "2Ele_2Muon", "DiLep"}) {
			for (auto std_plot : standard_plots)
				sh.AddHistos("evt",     { .fill=std_plot,                  .pfs={"StackPlot","Year",cut,nohad}, .cuts={},.draw=d,.opt=opt,.ranges=r_Stk9});
			sh.AddHistos(s+"evt",     { .fill=c+"MRR2",                  .pfs={"StackPlot","Year",cut,nohad}, .cuts={},.draw=d,.opt=opt,.ranges=r_Stk9});
			sh.AddHistos(s+"evt",     { .fill=c+"MRR2",                  .pfs={"StackPlot","run2",cut,nohad}, .cuts={},.draw=d,.opt=opt,.ranges=r_Stk9});
			sh.AddHistos(s+"evt",     { .fill=c+"newMRR2",               .pfs={"StackPlot","Year",cut,nohad}, .cuts={},.draw=d,.opt=opt,.ranges=r_Stk9});
			sh.AddHistos(s+"evt",     { .fill=c+"newMRR2",               .pfs={"StackPlot","run2",cut,nohad}, .cuts={},.draw=d,.opt=opt,.ranges=r_Stk9});
			sh.AddHistos(  "evt",     { .fill="NJet",                    .pfs={"StackPlot","Year",cut,nohad}, .cuts={},.draw=d,.opt=opt,.ranges=r_Stk9});
			sh.AddHistos(  "evt",     { .fill="MTBoost",                 .pfs={"StackPlot","Year",cut,nohad}, .cuts={},.draw=d,.opt=opt,.ranges=r_Stk9});
			sh.AddHistos(  "evt",     { .fill="DeltaPhi",                .pfs={"StackPlot","Year",cut,nohad}, .cuts={},.draw=d,.opt=opt,.ranges=r_Stk9});
			sh.AddHistos(  "evt",     { .fill="MinDeltaPhi",             .pfs={"StackPlot","Year",cut,nohad}, .cuts={},.draw=d,.opt=opt,.ranges=r_Stk9});
			sh.AddHistos(  "AK4",     { .fill="JetPtBins",               .pfs={"StackPlot","Year",cut,nohad}, .cuts={},.draw=d,.opt=opt,.ranges=r_Stk9});
			sh.AddHistos(  "AK4",     { .fill="JetPt",                   .pfs={"StackPlot","Year",cut,nohad}, .cuts={},.draw=d,.opt=opt,.ranges=r_Stk9});
			sh.AddHistos(  "AK4",     { .fill="JetEta",                  .pfs={"StackPlot","Year",cut,nohad}, .cuts={},.draw=d,.opt=opt,.ranges=r_Stk9});
			sh.AddHistos(  "AK4",     { .fill="JetPhi",                  .pfs={"StackPlot","Year",cut,nohad}, .cuts={},.draw=d,.opt=opt,.ranges=r_Stk9});
			sh.AddHistos(  "AK4",     { .fill="JetDeepB",                .pfs={"StackPlot","Year",cut,nohad}, .cuts={},.draw=d,.opt=opt,.ranges=r_Stk9});
			sh.AddHistos(  "megajet", { .fill="MegaJetPt",               .pfs={"StackPlot","Year",cut,nohad}, .cuts={},.draw=d,.opt=opt,.ranges=r_Stk9});
			sh.AddHistos(  "megajet", { .fill="MegaJetEta",              .pfs={"StackPlot","Year",cut,nohad}, .cuts={},.draw=d,.opt=opt,.ranges=r_Stk9});
			sh.AddHistos(  "megajet", { .fill="MegaJetPhi",              .pfs={"StackPlot","Year",cut,nohad}, .cuts={},.draw=d,.opt=opt,.ranges=r_Stk9});
			if (nohad=="Pho") {
				sh.AddHistos(s+"evt",     { .fill=c+"MRR2NoPho",           .pfs={"StackPlot","Year",cut,nohad}, .cuts={},.draw=d,.opt=opt,.ranges=r_Stk9});
				sh.AddHistos(  "evt",     { .fill="PhotonPtBins",          .pfs={"StackPlot","Year",cut,nohad}, .cuts={},.draw=d,.opt=opt,.ranges=r_Stk9});
				sh.AddHistos(  "evt",     { .fill="HTPhotonPt",            .pfs={"StackPlot","Year",cut,nohad}, .cuts={},.draw=d,.opt=opt,.ranges=r_Stk9});
				sh.AddHistos(  "evt",     { .fill="MinDeltaPhiNoPho",      .pfs={"StackPlot","Year",cut,nohad}, .cuts={},.draw=d,.opt=opt,.ranges=r_Stk9});
			}
			if (nohad=="1Ele"||nohad=="1Muon")
				sh.AddHistos(  "evt",     { .fill="MinDeltaPhiNo1Lep",     .pfs={"StackPlot","Year",cut,nohad}, .cuts={},.draw=d,.opt=opt,.ranges=r_Stk9});
			if (nohad=="DiLep") {
				sh.AddHistos(s+"evt",     { .fill=c+"MRR2NoDiLep",           .pfs={"StackPlot","Year",cut,nohad}, .cuts={},.draw=d,.opt=opt,.ranges=r_Stk9});
				sh.AddHistos(  "evt",     { .fill="METNoDiLep",              .pfs={"StackPlot","Year",cut,nohad}, .cuts={},.draw=d,.opt=opt,.ranges=r_Stk9});
			}
		}
		// N-1 plots
		for (std::string nm1 : {"_ExclMR", "_ExclR2", "_Excl1JetAK8", "_ExclHLT"}) {
			if (nm1=="_ExclHLT") 
				sh.SetHistoWeights({ [&w,region] { return w.w_nm1[region][9]*1.0; } });
			for (auto std_plot : standard_plots)
				sh.AddHistos("evt",     { .fill=std_plot,                  .pfs={"StackPlot","Year",cut+nm1}, .cuts={},.draw=d,.opt=opt,.ranges=r_Stk9});
			sh.AddHistos(s+"evt",     { .fill=c+"MRR2",                  .pfs={"StackPlot","Year",cut+nm1}, .cuts={},.draw=d,.opt=opt,.ranges=r_Stk9});
			sh.AddHistos(  "evt",     { .fill="NJet",                    .pfs={"StackPlot","Year",cut+nm1}, .cuts={},.draw=d,.opt=opt,.ranges=r_Stk9});
			sh.AddHistos(  "evt",     { .fill="MTBoost",                 .pfs={"StackPlot","Year",cut+nm1}, .cuts={},.draw=d,.opt=opt,.ranges=r_Stk9});
			sh.AddHistos(  "evt",     { .fill="DeltaPhi",                .pfs={"StackPlot","Year",cut+nm1}, .cuts={},.draw=d,.opt=opt,.ranges=r_Stk9});
			sh.AddHistos(  "evt",     { .fill="MinDeltaPhi",             .pfs={"StackPlot","Year",cut+nm1}, .cuts={},.draw=d,.opt=opt,.ranges=r_Stk9});
			sh.AddHistos(  "AK4",     { .fill="JetPtBins",               .pfs={"StackPlot","Year",cut+nm1}, .cuts={},.draw=d,.opt=opt,.ranges=r_Stk9});
			sh.AddHistos(  "AK4",     { .fill="JetPt",                   .pfs={"StackPlot","Year",cut+nm1}, .cuts={},.draw=d,.opt=opt,.ranges=r_Stk9});
			sh.AddHistos(  "AK4",     { .fill="JetEta",                  .pfs={"StackPlot","Year",cut+nm1}, .cuts={},.draw=d,.opt=opt,.ranges=r_Stk9});
			sh.AddHistos(  "AK4",     { .fill="JetPhi",                  .pfs={"StackPlot","Year",cut+nm1}, .cuts={},.draw=d,.opt=opt,.ranges=r_Stk9});
			sh.AddHistos(  "AK4",     { .fill="JetDeepB",                .pfs={"StackPlot","Year",cut+nm1}, .cuts={},.draw=d,.opt=opt,.ranges=r_Stk9});
		}
	}

	for (auto region : {Region::Pre_Had}) {
		sh.SetHistoWeights({ [&w,region] { return w.sf_weight[region]; } });
		std::string cut(magic_enum::enum_name(region));
		// Stack plots
		std::string opt  = o_stk_d_S;
		for (auto std_plot : standard_plots)
			sh.AddHistos("evt",     { .fill=std_plot,                  .pfs={"StackPlotSignal","Year",cut},             .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
		sh.AddHistos(s+"evt",     { .fill=c+"MRR2",                  .pfs={"StackPlotSignal","Year",cut},             .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
		sh.AddHistos(s+"evt",     { .fill=c+"newMRR2",               .pfs={"StackPlotSignal","Year",cut},             .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
		sh.AddHistos(  "evt",     { .fill="NJet",                    .pfs={"StackPlotSignal","Year",cut},             .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
		sh.AddHistos(  "evt",     { .fill="MTBoost",                 .pfs={"StackPlotSignal","Year",cut},             .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
		sh.AddHistos(  "evt",     { .fill="MinDeltaPhi",             .pfs={"StackPlotSignal","Year",cut},             .cuts={},.draw=d,.opt=opt,.ranges=r_Stk9});
		sh.AddHistos(  "evt",     { .fill="MinDeltaPhi",             .pfs={"StackPlotSignal","Year",cut+"_ExcldPhi"}, .cuts={},.draw=d,.opt=opt,.ranges=r_Stk9});
		sh.AddHistos(  "evt",     { .fill="DeltaPhi",                .pfs={"StackPlotSignal","Year",cut+"_ExcldPhi"}, .cuts={},.draw=d,.opt=opt,.ranges=r_Stk9});
		sh.AddHistos(  "megajet", { .fill="MegaJetPt",               .pfs={"StackPlotSignal","Year",cut+"_ExcldPhi"}, .cuts={},.draw=d,.opt=opt,.ranges=r_Stk9});
		sh.AddHistos(  "megajet", { .fill="MegaJetEta",              .pfs={"StackPlotSignal","Year",cut+"_ExcldPhi"}, .cuts={},.draw=d,.opt=opt,.ranges=r_Stk9});
		sh.AddHistos(  "megajet", { .fill="MegaJetPhi",              .pfs={"StackPlotSignal","Year",cut+"_ExcldPhi"}, .cuts={},.draw=d,.opt=opt,.ranges=r_Stk9});
	}

	for (auto region : {Region::Pre_NonIso}) {
		sh.SetHistoWeights({ [&w,region] { return w.sf_weight[region]; } });
		std::string cut(magic_enum::enum_name(region));
		// Stack plots
		std::string opt = o_stk_d_S;
		for (auto std_plot : standard_plots)
			sh.AddHistos("evt",{ .fill=std_plot,                       .pfs={"StackPlotSignal","Year",cut},                    .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
		sh.AddHistos(s+"evt",{ .fill=c+"MRR2",                       .pfs={"StackPlotSignal","Year",cut},                    .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
		sh.AddHistos(s+"evt",{ .fill=c+"newMRR2",                    .pfs={"StackPlotSignal","Year",cut},                    .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
		sh.AddHistos("evt",  { .fill="NJet",                         .pfs={"StackPlotSignal","Year",cut},                    .cuts={},.draw=d,.opt=opt,.ranges=r_Stk5});
		sh.AddHistos("evt",  { .fill="MTBoost",                      .pfs={"StackPlotSignal","Year",cut},                    .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
		sh.AddHistos("evt",  { .fill="DeltaPhi",                     .pfs={"StackPlotSignal","Year",cut},                    .cuts={},.draw=d,.opt=opt,.ranges=r_Stk9});
		sh.AddHistos("evt",  { .fill="MinDeltaPhi",                  .pfs={"StackPlotSignal","Year",cut},             .cuts={},.draw=d,.opt=opt,.ranges=r_Stk9});
		sh.AddHistos("megajet", { .fill="MegaJetPt",                 .pfs={"StackPlotSignal","Year",cut}, .cuts={},.draw=d,.opt=opt,.ranges=r_Stk9});
		sh.AddHistos("megajet", { .fill="MegaJetEta",                .pfs={"StackPlotSignal","Year",cut}, .cuts={},.draw=d,.opt=opt,.ranges=r_Stk9});
		sh.AddHistos("megajet", { .fill="MegaJetPhi",                .pfs={"StackPlotSignal","Year",cut}, .cuts={},.draw=d,.opt=opt,.ranges=r_Stk9});
		sh.AddHistos("evt",  { .fill="DeltaPhi",                     .pfs={"StackPlotSignal","Year",cut+"_ExclMT"},             .cuts={},.draw=d,.opt=opt,.ranges=r_Stk9});
		sh.AddHistos("evt",  { .fill="MinDeltaPhi",                  .pfs={"StackPlotSignal","Year",cut+"_ExclMT"},             .cuts={},.draw=d,.opt=opt,.ranges=r_Stk9});
		sh.AddHistos("evt",  { .fill="EleNoIsoPt",                   .pfs={"StackPlotSignal","Year",cut+"_Excl1LepMTdPhiJet"},         .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
		sh.AddHistos("evt",  { .fill="MuNoIsoPt",                    .pfs={"StackPlotSignal","Year",cut+"_Excl1LepMTdPhiJet"},         .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
		sh.AddHistos("evt",  { .fill="EleNonIsoPt",                  .pfs={"StackPlotSignal","Year",cut+"_Excl1LepMTdPhiJet"},         .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
		sh.AddHistos("evt",  { .fill="MuNonIsoPt",                   .pfs={"StackPlotSignal","Year",cut+"_Excl1LepMTdPhiJet"},         .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
		sh.AddHistos("evt",  { .fill="MTNonIso",                     .pfs={"StackPlotSignal","Year",cut+"_ExclMT"},             .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
		sh.AddHistos("evt",  { .fill="DeltaPhiBoostedJetMET",        .pfs={"StackPlotSignal","Year",cut},                    .cuts={},.draw=d,.opt=opt,.ranges=r_Stk5});
		sh.AddHistos("evt",  { .fill="DeltaPhiBoostedJetLep",        .pfs={"StackPlotSignal","Year",cut},                    .cuts={},.draw=d,.opt=opt,.ranges=r_Stk5});
		sh.AddHistos("evt",  { .fill="DeltaPhiBoostedJetMET",        .pfs={"StackPlotSignal","Year",cut+"_ExcldPhiJet"},     .cuts={},.draw=d,.opt=opt,.ranges=r_Stk5});
		sh.AddHistos("evt",  { .fill="DeltaPhiBoostedJetLep",        .pfs={"StackPlotSignal","Year",cut+"_ExcldPhiJet"},     .cuts={},.draw=d,.opt=opt,.ranges=r_Stk5});
		sh.AddHistos("evt",  { .fill="DeltaPhiBoostedJetLepMET",     .pfs={"StackPlotSignal","Year",cut+"_ExcldPhiJet"},     .cuts={},.draw=d,.opt=opt,.ranges=r_Stk5});
	}

	// ----------------------------------------------------------------------------------------------
	//                                New Control/Validation regions
	//-----------------------------------------------------------------------------------------------

	for (const auto& regions : magic_enum::enum_entries<Region>()) {
		Region region = regions.first;
		std::string cut(regions.second);
		if (TString(cut).BeginsWith("TR_")) {
		  std::vector<std::string> showdata = {"Blind"};
			for (auto data : showdata ) {
				std::string opt    = (data=="Blind") ? o_stk_s_H : o_stk_d_H;
		  	sh.AddHistos(s+"evt",    { .fill="MRR2_hHP",                  .pfs={"StackPlotHSignal",data,"Year",cut},                  .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
		  	sh.AddHistos(s+"evt",    { .fill="MRR2_hMP",                  .pfs={"StackPlotHSignal",data,"Year",cut},                  .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
		  	sh.AddHistos(s+"evt",    { .fill="MRR2_hLP",                 .pfs={"StackPlotHSignal",data,"Year",cut},                  .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
			}
		}
		if (TString(cut).Contains("CR_")||TString(cut).Contains("Val_")) {
			if (cut=="CR_Fake"||cut=="CR_Fake_MET500"||(cut=="CR_1PhoInv" && v.year==2016))
				sh.SetHistoWeights({ [&w,region] { return w.w_nm1[region][9]*w.triggereff_had_nor2; } });
			else if (cut=="CR_2LepInv"||cut=="CR_1LepInv_LepTrig")
				sh.SetHistoWeights({ [&w,region] { return w.w_nm1[region][9]*w.triggereff_lep; } });
			else if (cut=="CR_1PhoInv" && v.year!=2016)
				sh.SetHistoWeights({ [&w,region] { return w.w_nm1[region][9]*w.triggereff_pho; } });
			else
				sh.SetHistoWeights({ [&w,region] { return w.sf_weight[region]; } });
			// Stack plots
			std::string opt  = o_stk_d;
			for (auto std_plot : standard_plots)
				sh.AddHistos("evt",     { .fill=std_plot,                  .pfs={"StackPlot","Year",cut},             .cuts={},.draw=d,.opt=opt,.ranges=r_Stk8});
			sh.AddHistos(s+"evt",     { .fill=c+"MRR2",                  .pfs={"StackPlot","Year",cut},             .cuts={},.draw=d,.opt=opt,.ranges=r_Stk8});
			sh.AddHistos(s+"evt",     { .fill=c+"MRR2",                  .pfs={"StackPlot","run2",cut},             .cuts={},.draw=d,.opt=opt,.ranges=r_Stk8});
			if(TString(cut).Contains("Boost")) sh.AddHistos(  "evt",     { .fill=c+"MRR2",             .pfs={"StackPlot","Year",cut+"_Excl1M"}, .cuts={},.draw=d,.opt=opt,.ranges=r_Stk8});
			sh.AddHistos(s+"evt",     { .fill=c+"MRR2Bins",              .pfs={"StackPlot","Year",cut},             .cuts={},.draw=d,.opt=opt,.ranges=r_Stk8}); 
			//sh.AddHistos(s+"evt",     { .fill=c+"MRR2Bins",              .pfs={"StackPlot","Year","NMassTag",cut},             .cuts={},.draw=d,.opt=opt,.ranges=r_Stk8});
			sh.AddHistos(s+"evt",     { .fill=c+"MRR2Bin",              .pfs={"StackPlot","Year",cut},             .cuts={},.draw=d,.opt=opt,.ranges=r_Stk8}); 
			sh.AddHistos(s+"evt",     { .fill=c+"MRR21vlBin",           .pfs={"StackPlot","Year",cut},             .cuts={},.draw=d,.opt=opt,.ranges=r_Stk8}); 
			sh.AddHistos(s+"evt",     { .fill=c+"MRR2NoDiLep",          .pfs={"StackPlot","Year",cut},             .cuts={},.draw=d,.opt=opt,.ranges=r_Stk8}); 
			sh.AddHistos(s+"evt",     { .fill=c+"newMRR2",              .pfs={"StackPlot","Year",cut},             .cuts={},.draw=d,.opt=opt,.ranges=r_Stk8}); 
			sh.AddHistos(s+"evt",     { .fill=c+"MRR2Bins",             .pfs={"StackPlot","run2",cut},             .cuts={},.draw=d,.opt=opt,.ranges=r_Stk8}); 
			sh.AddHistos(s+"evt",     { .fill=c+"MRR2Bin",              .pfs={"StackPlot","run2",cut},             .cuts={},.draw=d,.opt=opt,.ranges=r_Stk8}); 
			sh.AddHistos(s+"evt",     { .fill=c+"newMRR2",              .pfs={"StackPlot","run2",cut},             .cuts={},.draw=d,.opt=opt,.ranges=r_Stk8}); 
			sh.AddHistos(s+"evt",     { .fill=c+"MRR21vlBin",           .pfs={"StackPlot","run2",cut},             .cuts={},.draw=d,.opt=opt,.ranges=r_Stk8}); 
			if (TString(cut).Contains("16_H")) {
				opt  = o_stk_d_H;
				sh.AddHistos(s+"evt",     { .fill=c+"MRR2Bins",              .pfs={"StackPlotHSignal","Year",cut},             .cuts={},.draw=d,.opt=opt,.ranges=r_Stk8});
				sh.AddHistos(s+"evt",     { .fill=c+"MRR2Bin",              .pfs={"StackPlotHSignal","Year",cut},             .cuts={},.draw=d,.opt=opt,.ranges=r_Stk8});
				sh.AddHistos(s+"evt",     { .fill=c+"newMRR2",              .pfs={"StackPlotHSignal","Year",cut},             .cuts={},.draw=d,.opt=opt,.ranges=r_Stk8});
				sh.AddHistos(s+"evt",     { .fill=c+"MRR2Bins",              .pfs={"StackPlotHSignal","run2",cut},             .cuts={},.draw=d,.opt=opt,.ranges=r_Stk8});
				sh.AddHistos(s+"evt",     { .fill=c+"MRR2Bin",              .pfs={"StackPlotHSignal","run2",cut},             .cuts={},.draw=d,.opt=opt,.ranges=r_Stk8});
				sh.AddHistos(s+"evt",     { .fill=c+"newMRR2",              .pfs={"StackPlotHSignal","run2",cut},             .cuts={},.draw=d,.opt=opt,.ranges=r_Stk8});
			} else {
				opt  = o_stk_d_S;
				sh.AddHistos(s+"evt",     { .fill=c+"MRR2Bins",              .pfs={"StackPlotSignal","Year",cut},             .cuts={},.draw=d,.opt=opt,.ranges=r_Stk8});
				//sh.AddHistos(s+"evt",     { .fill=c+"MRR2Bins",              .pfs={"StackPlotSignal","Year","NMassTag",cut},             .cuts={},.draw=d,.opt=opt,.ranges=r_Stk8});
				sh.AddHistos(s+"evt",     { .fill=c+"MRR2Bin",              .pfs={"StackPlotSignal","Year",cut},             .cuts={},.draw=d,.opt=opt,.ranges=r_Stk8});
				sh.AddHistos(s+"evt",     { .fill=c+"newMRR2",              .pfs={"StackPlotSignal","Year",cut},             .cuts={},.draw=d,.opt=opt,.ranges=r_Stk8});
				sh.AddHistos(s+"evt",     { .fill=c+"MRR2Bins",              .pfs={"StackPlotSignal","run2",cut},             .cuts={},.draw=d,.opt=opt,.ranges=r_Stk8});
				sh.AddHistos(s+"evt",     { .fill=c+"MRR2Bin",              .pfs={"StackPlotSignal","run2",cut},             .cuts={},.draw=d,.opt=opt,.ranges=r_Stk8});
				sh.AddHistos(s+"evt",     { .fill=c+"newMRR2",              .pfs={"StackPlotSignal","run2",cut},             .cuts={},.draw=d,.opt=opt,.ranges=r_Stk8});
			}
			opt  = o_stk_d;
			//sh.AddHistos(s+"evt",     { .fill=c+"MRR2Bins",              .pfs={"StackPlot","Year",cut,"NMassTag"},  .cuts={},.draw=d,.opt=opt,.ranges=r_Stk8});
			sh.AddHistos(  "AK8Mass", { .fill="BoostJetPt",              .pfs={"StackPlot","Year",cut},             .cuts={},.draw=d,.opt=opt,.ranges=r_Stk8});
			sh.AddHistos(  "AK8Mass", { .fill="JetAK8Mass",              .pfs={"StackPlot","Year",cut},             .cuts={},.draw=d,.opt=opt,.ranges=r_Stk8});
			sh.AddHistos(  "evt",     { .fill="NJet",                    .pfs={"StackPlot","Year",cut},             .cuts={},.draw=d,.opt=opt,.ranges=r_Stk8});
			sh.AddHistos(  "evt",     { .fill="NJetBins",                .pfs={"StackPlot","Year",cut},             .cuts={},.draw=d,.opt=opt,.ranges=r_Stk8});
			sh.AddHistos(  "evt",     { .fill="NJetBins",                .pfs={"StackPlot","run2",cut},             .cuts={},.draw=d,.opt=opt,.ranges=r_Stk8});
			sh.AddHistos(  "evt",     { .fill="NW",                      .pfs={"StackPlot","Year",cut},             .cuts={},.draw=d,.opt=opt,.ranges=r_Stk8});
			sh.AddHistos(  "evt",     { .fill="NZ",                      .pfs={"StackPlot","Year",cut},             .cuts={},.draw=d,.opt=opt,.ranges=r_Stk8});
			sh.AddHistos(  "evt",     { .fill="NV",                      .pfs={"StackPlot","Year",cut},             .cuts={},.draw=d,.opt=opt,.ranges=r_Stk8});
			sh.AddHistos(  "evt",     { .fill="NTop",                    .pfs={"StackPlot","Year",cut},             .cuts={},.draw=d,.opt=opt,.ranges=r_Stk8});
			sh.AddHistos(  "evt",     { .fill="NH",                      .pfs={"StackPlot","Year",cut},             .cuts={},.draw=d,.opt=opt,.ranges=r_Stk8});
			sh.AddHistos(  "evt",     { .fill="MTBoost",                 .pfs={"StackPlot","Year",cut},             .cuts={},.draw=d,.opt=opt,.ranges=r_Stk8});
			sh.AddHistos(  "evt",     { .fill="MinDeltaPhi",             .pfs={"StackPlot","Year",cut},             .cuts={},.draw=d,.opt=opt,.ranges=r_Stk9});
			if(!(TString(cut).Contains("NonIso")||TString(cut).Contains("CR_Real")||TString(cut).Contains("2LepInv")||TString(cut).Contains("Val_Lep")||TString(cut).Contains("Val_Signal_LostLep"))) {
				sh.AddHistos(  "evt",     { .fill="MinDeltaPhi",             .pfs={"StackPlot","Year",cut+"_ExcldPhi"}, .cuts={},.draw=d,.opt=opt,.ranges=r_Stk9});
				sh.AddHistos(  "evt",     { .fill="DeltaPhi",                .pfs={"StackPlot","Year",cut+"_ExcldPhi"}, .cuts={},.draw=d,.opt=opt,.ranges=r_Stk9});
				sh.AddHistos(  "megajet", { .fill="MegaJetPt",               .pfs={"StackPlot","Year",cut+"_ExcldPhi"}, .cuts={},.draw=d,.opt=opt,.ranges=r_Stk9});
				sh.AddHistos(  "megajet", { .fill="MegaJetEta",              .pfs={"StackPlot","Year",cut+"_ExcldPhi"}, .cuts={},.draw=d,.opt=opt,.ranges=r_Stk9});
				sh.AddHistos(  "megajet", { .fill="MegaJetPhi",              .pfs={"StackPlot","Year",cut+"_ExcldPhi"}, .cuts={},.draw=d,.opt=opt,.ranges=r_Stk9});
			}

			// Lepton related plots (to validate trigger efficiency)
			if (TString(cut).Contains("CR_Top")||TString(cut).Contains("CR_W")) {
				for (auto nohad : {"1Ele", "1Muon"}) {
					for (auto std_plot : standard_plots)
						sh.AddHistos("evt", { .fill=std_plot,                  .pfs={"StackPlot","Year",cut,nohad},       .cuts={},.draw=d,.opt=opt,.ranges=r_Stk8});
					sh.AddHistos(s+"evt", { .fill=c+"MRR2",                  .pfs={"StackPlot","Year",cut,nohad},       .cuts={},.draw=d,.opt=opt,.ranges=r_Stk8});
					sh.AddHistos(s+"evt", { .fill=c+"MRR2Bins",              .pfs={"StackPlot","Year",cut,nohad},       .cuts={},.draw=d,.opt=opt,.ranges=r_Stk8}); 
					sh.AddHistos(s+"evt", { .fill=c+"MRR2Bin",              .pfs={"StackPlot","Year",cut,nohad},       .cuts={},.draw=d,.opt=opt,.ranges=r_Stk8}); 
					sh.AddHistos(s+"evt", { .fill=c+"newMRR2",              .pfs={"StackPlot","Year",cut,nohad},       .cuts={},.draw=d,.opt=opt,.ranges=r_Stk8}); 
					sh.AddHistos(s+"evt", { .fill=c+"MRR2",                  .pfs={"StackPlot","run2",cut,nohad},       .cuts={},.draw=d,.opt=opt,.ranges=r_Stk8});
					sh.AddHistos(s+"evt", { .fill=c+"MRR2Bins",              .pfs={"StackPlot","run2",cut,nohad},       .cuts={},.draw=d,.opt=opt,.ranges=r_Stk8}); 
					sh.AddHistos(s+"evt", { .fill=c+"MRR2Bin",              .pfs={"StackPlot","run2",cut,nohad},       .cuts={},.draw=d,.opt=opt,.ranges=r_Stk8}); 
					sh.AddHistos(s+"evt", { .fill=c+"newMRR2",              .pfs={"StackPlot","run2",cut,nohad},       .cuts={},.draw=d,.opt=opt,.ranges=r_Stk8}); 
					//sh.AddHistos(s+"evt", { .fill=c+"MRR2",              .pfs={"StackPlot","Year",cut},             .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
					//sh.AddHistos(s+"evt", { .fill=c+"newMRR2",           .pfs={"StackPlot","Year",cut},             .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
					sh.AddHistos(  "evt", { .fill="NJet",                    .pfs={"StackPlot","Year",cut,nohad},       .cuts={},.draw=d,.opt=opt,.ranges=r_Stk8});
					sh.AddHistos(  "evt", { .fill="NJetBins",                .pfs={"StackPlot","Year",cut,nohad},       .cuts={},.draw=d,.opt=opt,.ranges=r_Stk8});
					sh.AddHistos(  "evt", { .fill="MTBoost",                 .pfs={"StackPlot","Year",cut,nohad},       .cuts={},.draw=d,.opt=opt,.ranges=r_Stk8});
					sh.AddHistos(  "evt", { .fill="MinDeltaPhiNo1Lep",       .pfs={"StackPlot","Year",cut,nohad},       .cuts={},.draw=d,.opt=opt,.ranges=r_Stk8});
				}
				sh.AddHistos(  "evt",   { .fill="ElePt",                   .pfs={"StackPlot","Year",cut},             .cuts={},.draw=d,.opt=opt,.ranges=r_Stk8});
				sh.AddHistos(  "evt",   { .fill="MuPt",                    .pfs={"StackPlot","Year",cut},             .cuts={},.draw=d,.opt=opt,.ranges=r_Stk8});
			}

			if (cut=="CR_1LepInv_LepTrig"||cut=="CR_1LepInv"||TString(cut).Contains("Val_Signal_LostLep")) {
				sh.AddHistos("evt",  { .fill="METNo1VLep",              .pfs={"StackPlot","Year",cut},                  .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
				sh.AddHistos("evt",  { .fill="R2No1VLep",               .pfs={"StackPlot","Year",cut},                  .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
				sh.AddHistos(s+"evt",  { .fill=c+"MRR2No1VLep",         .pfs={"StackPlot","Year",cut},                  .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
				sh.AddHistos(s+"evt",  { .fill=c+"MRR2No1VLep",         .pfs={"StackPlot","run2",cut},                  .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
				sh.AddHistos(s+"evt",  { .fill=c+"MRR2No1VLep",         .pfs={"StackPlot","Year",cut,"Ele_Muon"},       .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
				sh.AddHistos("evt",  { .fill="MinDeltaPhiNo1VLep",      .pfs={"StackPlot","Year",cut},                   .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
				sh.AddHistos("evt",  { .fill="NJet",                    .pfs={"StackPlot","Year",cut,"Ele_Muon"},       .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
				sh.AddHistos("ele veto",  { .fill="VetoElePt",          .pfs={"StackPlot","Year",cut},       .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
				sh.AddHistos("ele veto",  { .fill="VetoEleEta",         .pfs={"StackPlot","Year",cut},       .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
				sh.AddHistos("mu veto",   { .fill="VetoMuPt",           .pfs={"StackPlot","Year",cut},       .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
				sh.AddHistos("mu veto",   { .fill="VetoMuEta",          .pfs={"StackPlot","Year",cut},       .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
			} else if (cut=="CR_2LepInv") {
				sh.AddHistos("evt",  { .fill="METNo2Lep",               .pfs={"StackPlot","Year",cut},                   .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
				sh.AddHistos("evt",  { .fill="R2No2Lep",                .pfs={"StackPlot","Year",cut},                   .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
				sh.AddHistos(s+"evt",{ .fill=c+"MRR2No2Lep",            .pfs={"StackPlot","Year",cut},                   .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
				sh.AddHistos(s+"evt",{ .fill=c+"MRR2No2Lep",            .pfs={"StackPlot","run2",cut},                   .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
				sh.AddHistos(s+"evt",{ .fill=c+"MRR2No2Lep",            .pfs={"StackPlot","Year",cut,"2Ele_2Muon"},      .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
				sh.AddHistos("evt",  { .fill="MinDeltaPhiNo2Lep",       .pfs={"StackPlot","Year",cut},                   .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
				sh.AddHistos("evt",  { .fill="NJet",                    .pfs={"StackPlot","Year",cut,"2Ele_2Muon"},      .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
				sh.AddHistos("evt",  { .fill="Mll",                     .pfs={"StackPlot","Year",cut+"_ExclMll"},        .cuts={},.draw=d,.opt=opt,.ranges={0,0, 1.01e-2,1e6, 0.3,0.86}});
				sh.AddHistos("evt",  { .fill="Mll",                     .pfs={"StackPlot","run2",cut+"_ExclMll"},        .cuts={},.draw=d,.opt=opt,.ranges={0,0, 1.01e-2,1e6, 0.3,0.86}});
				sh.AddHistos("evt",  { .fill="ElePt",                   .pfs={"StackPlot","Year",cut,"2Ele_2Muon"},      .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
				sh.AddHistos("evt",  { .fill="EleEta",                  .pfs={"StackPlot","Year",cut,"2Ele_2Muon"},      .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
				sh.AddHistos("evt",  { .fill="MuPt",                    .pfs={"StackPlot","Year",cut,"2Ele_2Muon"},      .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
				sh.AddHistos("evt",  { .fill="MuEta",                   .pfs={"StackPlot","Year",cut,"2Ele_2Muon"},      .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
			} else if (cut=="CR_1PhoInv") {
				sh.AddHistos("evt",  { .fill="METNoPho",                .pfs={"StackPlot","Year",cut},                   .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
				sh.AddHistos("evt",  { .fill="R2NoPho",                 .pfs={"StackPlot","Year",cut},                   .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
				sh.AddHistos(s+"evt",{ .fill=c+"MRR2NoPho",             .pfs={"StackPlot","Year",cut},                   .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
				sh.AddHistos(s+"evt",{ .fill=c+"MRR2NoPho",             .pfs={"StackPlot","run2",cut},                   .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
				sh.AddHistos("evt",  { .fill="MinDeltaPhiNoPho",        .pfs={"StackPlot","Year",cut},                   .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
				sh.AddHistos("evt",  { .fill="PhotonEta",               .pfs={"StackPlot","Year",cut},                   .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
				sh.AddHistos("evt",  { .fill="PhotonPt",                .pfs={"StackPlot","Year",cut},                   .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
				sh.AddHistos("evt",  { .fill="PhotonPt",                .pfs={"StackPlot","Year",cut,"1Pho_EB_EE"},      .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
				sh.AddHistos("evt",  { .fill="PhotonPtBins",            .pfs={"StackPlot","Year",cut},                   .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
				sh.AddHistos("evt",  { .fill="PhotonPtBins",            .pfs={"StackPlot","Year",cut,"1Pho_EB_EE"},      .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
				sh.AddHistos("evt",  { .fill="PrePhotonPt",             .pfs={"StackPlot","Year",cut},                   .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
				sh.AddHistos("evt",  { .fill="PrePhotonPtBins",         .pfs={"StackPlot","Year",cut},                   .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
				sh.AddHistos("evt",  { .fill="PrePhotonPt",             .pfs={"StackPlot","Year",cut,"1PrePho_EB_EE"},   .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
				sh.AddHistos("evt",  { .fill="PrePhotonPtBins",         .pfs={"StackPlot","Year",cut,"1PrePho_EB_EE"},   .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
			} else if (cut=="CR_DiLep") {
				for (auto cut2 : {cut, cut+"_ExclMT2", cut+"_ExcldPhi"}) {
					sh.AddHistos("evt",  { .fill="METNoDiLep",            .pfs={"StackPlot","Year",cut2},                  .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
					sh.AddHistos("evt",  { .fill="METNoDiLep",            .pfs={"StackPlot","Year",cut2,"DiLep"},          .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
					sh.AddHistos("evt",  { .fill="R2NoDiLep",             .pfs={"StackPlot","Year",cut2},                  .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
					sh.AddHistos(s+"evt",{ .fill=c+"MRR2NoDiLep",         .pfs={"StackPlot","Year",cut2},                  .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
					sh.AddHistos(s+"evt",{ .fill=c+"MRR2NoDiLep",         .pfs={"StackPlot","run2",cut2},                  .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
					sh.AddHistos(s+"evt",{ .fill=c+"MRR2NoDiLep",         .pfs={"StackPlot","Year",cut2,"DiLep"},          .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
					sh.AddHistos("ele veto",  { .fill="VetoElePt",        .pfs={"StackPlot","Year",cut2},                  .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
					sh.AddHistos("mu veto",   { .fill="VetoMuPt",         .pfs={"StackPlot","Year",cut2},                  .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
				}
				sh.AddHistos(s+"evt",{ .fill=c+"MRR2",                  .pfs={"StackPlotSignal","Year",cut},             .cuts={},.draw=d,.opt=o_stk_s_S,.ranges=r_Stk6});
				sh.AddHistos(s+"evt",{ .fill=c+"MRR2",                  .pfs={"StackPlotSignal","Year",cut+"_ExclMT2"},  .cuts={},.draw=d,.opt=o_stk_s_S,.ranges=r_Stk6});
				sh.AddHistos("evt",  { .fill="MT",                      .pfs={"StackPlotSignal","Year",cut+"_ExclMT2"},  .cuts={},.draw=d,.opt=o_stk_s_S,.ranges=r_Stk6});
				sh.AddHistos("evt",  { .fill="MT2",                     .pfs={"StackPlotSignal","Year",cut+"_ExclMT2"},  .cuts={},.draw=d,.opt=o_stk_s_S,.ranges=r_Stk6});
				sh.AddHistos("evt",  { .fill="MT",                      .pfs={"StackPlot","Year",cut+"_ExcldPhiMT2"},    .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
				sh.AddHistos("evt",  { .fill="MT2",                     .pfs={"StackPlot","Year",cut+"_ExcldPhiMT2"},    .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
			}
		}
	}

	// ----------------------------------------------------------------------------------------------
	//                                         Scale Factors
	//-----------------------------------------------------------------------------------------------

	for (auto region : {Region::Pre, Region::CR_Fake, Region::CR_Fake_MET500, Region::CR_Fake_R2, Region::Val_Fake, Region::CR_Real}) {
		std::string cut(magic_enum::enum_name(region));
		if (cut=="CR_Fake")
			sh.SetHistoWeights({ [&w,region] { return w.w_nm1[region][9]*w.triggereff_had_nor2; } });
		else
			sh.SetHistoWeights({ [&w,region] { return w.sf_weight[region]; } });


		//sh.AddHistos("evt", { .fill="NoIsoElectronFakeRate_vs_EleNoIsoPt",              .pfs={"Data_MC","Year",cut,"Syst"},                     .cuts={},.draw="PE1",.opt=o_1or2d_d+"AddRatio",.ranges={}});
		//sh.AddHistos("evt", { .fill="NoIsoMuonFakeRate_vs_MuNoIsoPt",              .pfs={"Data_MC","Year",cut,"Syst"},                     .cuts={},.draw="PE1",.opt=o_1or2d_d+"AddRatio",.ranges={}});
		//sh.AddHistos("evt", { .fill="NonIsoElectronFakeRate_vs_EleNonIsoPt",              .pfs={"Data_MC","Year",cut,"Syst"},                     .cuts={},.draw="PE1",.opt=o_1or2d_d+"AddRatio",.ranges={}});
		//sh.AddHistos("evt", { .fill="NonIsoMuonFakeRate_vs_MuNonIsoPt",              .pfs={"Data_MC","Year",cut,"Syst"},                     .cuts={},.draw="PE1",.opt=o_1or2d_d+"AddRatio",.ranges={}});


		sh.AddHistos("AK8", { .fill="MassTagFakeRate_vs_JetAK8MassBins",            .pfs={"Data_MC","YearSF",cut,"Syst"},                     .cuts={},.draw="PE1",.opt=o_1or2d_d+"AddRatio",.ranges={}});
		sh.AddHistos("AK8", { .fill="MassTagFakeRate_vs_JetAK8MassBins",            .pfs={"Data_MC","YearSF",cut,"Syst","AK8_EB_EE"},         .cuts={},.draw="PE1",.opt=o_1or2d_d+"AddRatio",.ranges={}});
		sh.AddHistos("AK8", { .fill="MassTagFakeRate_vs_JetAK8PtBins",              .pfs={"Data_MC","YearSF",cut,"Syst"},                     .cuts={},.draw="PE1",.opt=o_1or2d_d+"AddRatio",.ranges={}});
		sh.AddHistos("AK8", { .fill="MassTagFakeRate_vs_JetAK8PtBins",              .pfs={"Data_MC","YearSF",cut,"Syst","AK8_EB_EE"},         .cuts={},.draw="PE1",.opt=o_1or2d_d+"AddRatio",.ranges={}});
		sh.AddHistos("AK8", { .fill="MassTagFakeRate_vs_JetAK8PtFewBins",           .pfs={"Data_MC","YearSF",cut,"Syst","AK8_EB_EE"},         .cuts={},.draw="PE1",.opt=o_1or2d_d+"AddRatio",.ranges={}});

		// Data/MC Scale factors - Fakes
		sh.AddHistos("AK8", { .fill="LepJetTagFakeRate_vs_JetAK8PtBins",          .pfs={"Data_MC","YearSF",cut,"Syst"},                     .cuts={},.draw="PE1",.opt=o_1or2d_d+"AddRatio",.ranges={}});
		sh.AddHistos("AK8", { .fill="LepJetTagFakeRate_vs_JetAK8PtBins",          .pfs={"Data_MC","YearSF",cut,"Syst","AK8_EB_EE"},         .cuts={},.draw="PE1",.opt=o_1or2d_d+"AddRatio",.ranges={}});
		sh.AddHistos("AK8", { .fill="LepJetTagFakeRate_vs_JetAK8PtFewBins",       .pfs={"Data_MC","YearSF",cut,"Syst","AK8_EB_EE"},         .cuts={},.draw="PE1",.opt=o_1or2d_d+"AddRatio",.ranges={}});
		sh.AddHistos("AK8", { .fill="LepJetTagFakeRate_vs_JetAK8PtOneBin",        .pfs={"Data_MC","YearSF",cut,"Syst","AK8_EB_EE"},         .cuts={},.draw="PE1",.opt=o_1or2d_d+"AddRatio",.ranges={}});
		sh.AddHistos("AK8", { .fill="LepTopTagFakeRate_vs_JetAK8PtBins",          .pfs={"Data_MC","YearSF",cut,"Syst"},                     .cuts={},.draw="PE1",.opt=o_1or2d_d+"AddRatio",.ranges={}});
		sh.AddHistos("AK8", { .fill="LepTopTagFakeRate_vs_JetAK8PtBins",          .pfs={"Data_MC","YearSF",cut,"Syst","AK8_EB_EE"},         .cuts={},.draw="PE1",.opt=o_1or2d_d+"AddRatio",.ranges={}});
		sh.AddHistos("AK8", { .fill="LepTopTagFakeRate_vs_JetAK8PtFewBins",       .pfs={"Data_MC","YearSF",cut,"Syst","AK8_EB_EE"},         .cuts={},.draw="PE1",.opt=o_1or2d_d+"AddRatio",.ranges={}});
		sh.AddHistos("AK8", { .fill="LepTopTagFakeRate_vs_JetAK8PtOneBin",        .pfs={"Data_MC","YearSF",cut,"Syst","AK8_EB_EE"},         .cuts={},.draw="PE1",.opt=o_1or2d_d+"AddRatio",.ranges={}});
		sh.AddHistos("AK8", { .fill="HadTopTagFakeRate_vs_JetAK8PtBins",          .pfs={"Data_MC","YearSF",cut,"Syst"},                     .cuts={},.draw="PE1",.opt=o_1or2d_d+"AddRatio",.ranges={}});
		sh.AddHistos("AK8", { .fill="HadTopTagFakeRate_vs_JetAK8PtBins",          .pfs={"Data_MC","YearSF",cut,"Syst","AK8_EB_EE"},         .cuts={},.draw="PE1",.opt=o_1or2d_d+"AddRatio",.ranges={}});
		sh.AddHistos("AK8", { .fill="HadTopTagFakeRate_vs_JetAK8PtFewBins",       .pfs={"Data_MC","YearSF",cut,"Syst","AK8_EB_EE"},         .cuts={},.draw="PE1",.opt=o_1or2d_d+"AddRatio",.ranges={}});
		sh.AddHistos("AK8", { .fill="HadVTagFakeRate_vs_JetAK8PtBins",            .pfs={"Data_MC","YearSF",cut,"Syst"},                     .cuts={},.draw="PE1",.opt=o_1or2d_d+"AddRatio",.ranges={}});
		sh.AddHistos("AK8", { .fill="HadVTagFakeRate_vs_JetAK8PtBins",            .pfs={"Data_MC","YearSF",cut,"Syst","AK8_EB_EE"},         .cuts={},.draw="PE1",.opt=o_1or2d_d+"AddRatio",.ranges={}});
		sh.AddHistos("AK8", { .fill="HadVTagFakeRate_vs_JetAK8PtFewBins",         .pfs={"Data_MC","YearSF",cut,"Syst","AK8_EB_EE"},         .cuts={},.draw="PE1",.opt=o_1or2d_d+"AddRatio",.ranges={}});
		sh.AddHistos("AK8", { .fill="HadWTagFakeRate_vs_JetAK8PtBins",            .pfs={"Data_MC","YearSF",cut,"Syst"},                     .cuts={},.draw="PE1",.opt=o_1or2d_d+"AddRatio",.ranges={}});
		sh.AddHistos("AK8", { .fill="HadWTagFakeRate_vs_JetAK8PtBins",            .pfs={"Data_MC","YearSF",cut,"Syst","AK8_EB_EE"},         .cuts={},.draw="PE1",.opt=o_1or2d_d+"AddRatio",.ranges={}});
		sh.AddHistos("AK8", { .fill="HadWTagFakeRate_vs_JetAK8PtFewBins",         .pfs={"Data_MC","YearSF",cut,"Syst","AK8_EB_EE"},         .cuts={},.draw="PE1",.opt=o_1or2d_d+"AddRatio",.ranges={}});
		sh.AddHistos("AK8", { .fill="HadZTagFakeRate_vs_JetAK8PtBins",            .pfs={"Data_MC","YearSF",cut,"Syst"},                     .cuts={},.draw="PE1",.opt=o_1or2d_d+"AddRatio",.ranges={}});
		sh.AddHistos("AK8", { .fill="HadZTagFakeRate_vs_JetAK8PtBins",            .pfs={"Data_MC","YearSF",cut,"Syst","AK8_EB_EE"},         .cuts={},.draw="PE1",.opt=o_1or2d_d+"AddRatio",.ranges={}});
		sh.AddHistos("AK8", { .fill="HadZTagFakeRate_vs_JetAK8PtFewBins",         .pfs={"Data_MC","YearSF",cut,"Syst","AK8_EB_EE"},         .cuts={},.draw="PE1",.opt=o_1or2d_d+"AddRatio",.ranges={}});
		sh.AddHistos("AK8", { .fill="HadHTagFakeRate_vs_JetAK8PtBins",            .pfs={"Data_MC","YearSF",cut,"Syst"},                     .cuts={},.draw="PE1",.opt=o_1or2d_d+"AddRatio",.ranges={}});
		sh.AddHistos("AK8", { .fill="HadHTagFakeRate_vs_JetAK8PtOneBin",          .pfs={"Data_MC","YearSF",cut,"Syst"},                     .cuts={},.draw="PE1",.opt=o_1or2d_d+"AddRatio",.ranges={}});
		sh.AddHistos("AK8", { .fill="HadHTagFakeRate_vs_JetAK8PtTwoBin",          .pfs={"Data_MC","YearSF",cut,"Syst"},                     .cuts={},.draw="PE1",.opt=o_1or2d_d+"AddRatio",.ranges={}});
		sh.AddHistos("AK8", { .fill="HadHTagFakeRate_vs_JetAK8PtBins",            .pfs={"Data_MC","YearSF",cut,"Syst","AK8_EB_EE"},         .cuts={},.draw="PE1",.opt=o_1or2d_d+"AddRatio",.ranges={}});
		sh.AddHistos("AK8", { .fill="HadHTagFakeRate_vs_JetAK8PtFewBins",         .pfs={"Data_MC","YearSF",cut,"Syst","AK8_EB_EE"},         .cuts={},.draw="PE1",.opt=o_1or2d_d+"AddRatio",.ranges={}});
		sh.AddHistos("AK8", { .fill="HadHTagFakeRate_vs_JetAK8PtTwoBin",          .pfs={"Data_MC","YearSF",cut,"Syst","AK8_EB_EE"},         .cuts={},.draw="PE1",.opt=o_1or2d_d+"AddRatio",.ranges={}});
		sh.AddHistos("AK8", { .fill="HadHTagFakeRate_vs_JetAK8PtOneBin",          .pfs={"Data_MC","YearSF",cut,"Syst","AK8_EB_EE"},         .cuts={},.draw="PE1",.opt=o_1or2d_d+"AddRatio",.ranges={}});

		// Data/FastMC Scale factors - Fakes
		sh.AddHistos("AK8", { .fill="LepJetTagFakeRate_vs_JetAK8PtBins",          .pfs={"Data_FastSim","YearFS",cut,"Syst"},                     .cuts={},.draw="PE1",.opt=o_1or2d_d+"AddRatio",.ranges={}});
		sh.AddHistos("AK8", { .fill="LepJetTagFakeRate_vs_JetAK8PtBins",          .pfs={"Data_FastSim","YearFS",cut,"Syst","AK8_EB_EE"},         .cuts={},.draw="PE1",.opt=o_1or2d_d+"AddRatio",.ranges={}});
		sh.AddHistos("AK8", { .fill="LepJetTagFakeRate_vs_JetAK8PtFewBins",       .pfs={"Data_FastSim","YearFS",cut,"Syst","AK8_EB_EE"},         .cuts={},.draw="PE1",.opt=o_1or2d_d+"AddRatio",.ranges={}});
		sh.AddHistos("AK8", { .fill="LepJetTagFakeRate_vs_JetAK8PtOneBin",        .pfs={"Data_FastSim","YearFS",cut,"Syst","AK8_EB_EE"},         .cuts={},.draw="PE1",.opt=o_1or2d_d+"AddRatio",.ranges={}});
		sh.AddHistos("AK8", { .fill="LepTopTagFakeRate_vs_JetAK8PtBins",          .pfs={"Data_FastSim","YearFS",cut,"Syst"},                     .cuts={},.draw="PE1",.opt=o_1or2d_d+"AddRatio",.ranges={}});
		sh.AddHistos("AK8", { .fill="LepTopTagFakeRate_vs_JetAK8PtBins",          .pfs={"Data_FastSim","YearFS",cut,"Syst","AK8_EB_EE"},         .cuts={},.draw="PE1",.opt=o_1or2d_d+"AddRatio",.ranges={}});
		sh.AddHistos("AK8", { .fill="LepTopTagFakeRate_vs_JetAK8PtFewBins",       .pfs={"Data_FastSim","YearFS",cut,"Syst","AK8_EB_EE"},         .cuts={},.draw="PE1",.opt=o_1or2d_d+"AddRatio",.ranges={}});
		sh.AddHistos("AK8", { .fill="LepTopTagFakeRate_vs_JetAK8PtOneBin",        .pfs={"Data_FastSim","YearFS",cut,"Syst","AK8_EB_EE"},         .cuts={},.draw="PE1",.opt=o_1or2d_d+"AddRatio",.ranges={}});
		sh.AddHistos("AK8", { .fill="HadTopTagFakeRate_vs_JetAK8PtBins",          .pfs={"Data_FastSim","YearFS",cut,"Syst"},                     .cuts={},.draw="PE1",.opt=o_1or2d_d+"AddRatio",.ranges={}});
		sh.AddHistos("AK8", { .fill="HadTopTagFakeRate_vs_JetAK8PtBins",          .pfs={"Data_FastSim","YearFS",cut,"Syst","AK8_EB_EE"},         .cuts={},.draw="PE1",.opt=o_1or2d_d+"AddRatio",.ranges={}});
		sh.AddHistos("AK8", { .fill="HadTopTagFakeRate_vs_JetAK8PtFewBins",       .pfs={"Data_FastSim","YearFS",cut,"Syst","AK8_EB_EE"},         .cuts={},.draw="PE1",.opt=o_1or2d_d+"AddRatio",.ranges={}});
		sh.AddHistos("AK8", { .fill="HadVTagFakeRate_vs_JetAK8PtBins",            .pfs={"Data_FastSim","YearFS",cut,"Syst"},                     .cuts={},.draw="PE1",.opt=o_1or2d_d+"AddRatio",.ranges={}});
		sh.AddHistos("AK8", { .fill="HadVTagFakeRate_vs_JetAK8PtBins",            .pfs={"Data_FastSim","YearFS",cut,"Syst","AK8_EB_EE"},         .cuts={},.draw="PE1",.opt=o_1or2d_d+"AddRatio",.ranges={}});
		sh.AddHistos("AK8", { .fill="HadVTagFakeRate_vs_JetAK8PtFewBins",         .pfs={"Data_FastSim","YearFS",cut,"Syst","AK8_EB_EE"},         .cuts={},.draw="PE1",.opt=o_1or2d_d+"AddRatio",.ranges={}});
		sh.AddHistos("AK8", { .fill="HadWTagFakeRate_vs_JetAK8PtBins",            .pfs={"Data_FastSim","YearFS",cut,"Syst"},                     .cuts={},.draw="PE1",.opt=o_1or2d_d+"AddRatio",.ranges={}});
		sh.AddHistos("AK8", { .fill="HadWTagFakeRate_vs_JetAK8PtBins",            .pfs={"Data_FastSim","YearFS",cut,"Syst","AK8_EB_EE"},         .cuts={},.draw="PE1",.opt=o_1or2d_d+"AddRatio",.ranges={}});
		sh.AddHistos("AK8", { .fill="HadWTagFakeRate_vs_JetAK8PtFewBins",         .pfs={"Data_FastSim","YearFS",cut,"Syst","AK8_EB_EE"},         .cuts={},.draw="PE1",.opt=o_1or2d_d+"AddRatio",.ranges={}});
		sh.AddHistos("AK8", { .fill="HadZTagFakeRate_vs_JetAK8PtBins",            .pfs={"Data_FastSim","YearFS",cut,"Syst"},                     .cuts={},.draw="PE1",.opt=o_1or2d_d+"AddRatio",.ranges={}});
		sh.AddHistos("AK8", { .fill="HadZTagFakeRate_vs_JetAK8PtBins",            .pfs={"Data_FastSim","YearFS",cut,"Syst","AK8_EB_EE"},         .cuts={},.draw="PE1",.opt=o_1or2d_d+"AddRatio",.ranges={}});
		sh.AddHistos("AK8", { .fill="HadZTagFakeRate_vs_JetAK8PtFewBins",         .pfs={"Data_FastSim","YearFS",cut,"Syst","AK8_EB_EE"},         .cuts={},.draw="PE1",.opt=o_1or2d_d+"AddRatio",.ranges={}});
		sh.AddHistos("AK8", { .fill="HadHTagFakeRate_vs_JetAK8PtBins",            .pfs={"Data_FastSim","YearFS",cut,"Syst"},                     .cuts={},.draw="PE1",.opt=o_1or2d_d+"AddRatio",.ranges={}});
		sh.AddHistos("AK8", { .fill="HadHTagFakeRate_vs_JetAK8PtOneBin",          .pfs={"Data_FastSim","YearFS",cut,"Syst"},                     .cuts={},.draw="PE1",.opt=o_1or2d_d+"AddRatio",.ranges={}});
		sh.AddHistos("AK8", { .fill="HadHTagFakeRate_vs_JetAK8PtTwoBin",          .pfs={"Data_FastSim","YearFS",cut,"Syst"},                     .cuts={},.draw="PE1",.opt=o_1or2d_d+"AddRatio",.ranges={}});
		sh.AddHistos("AK8", { .fill="HadHTagFakeRate_vs_JetAK8PtBins",            .pfs={"Data_FastSim","YearFS",cut,"Syst","AK8_EB_EE"},         .cuts={},.draw="PE1",.opt=o_1or2d_d+"AddRatio",.ranges={}});
		sh.AddHistos("AK8", { .fill="HadHTagFakeRate_vs_JetAK8PtFewBins",         .pfs={"Data_FastSim","YearFS",cut,"Syst","AK8_EB_EE"},         .cuts={},.draw="PE1",.opt=o_1or2d_d+"AddRatio",.ranges={}});
		sh.AddHistos("AK8", { .fill="HadHTagFakeRate_vs_JetAK8PtTwoBin",          .pfs={"Data_FastSim","YearFS",cut,"Syst","AK8_EB_EE"},         .cuts={},.draw="PE1",.opt=o_1or2d_d+"AddRatio",.ranges={}});
		sh.AddHistos("AK8", { .fill="HadHTagFakeRate_vs_JetAK8PtOneBin",          .pfs={"Data_FastSim","YearFS",cut,"Syst","AK8_EB_EE"},         .cuts={},.draw="PE1",.opt=o_1or2d_d+"AddRatio",.ranges={}});

		// Full/FastSim scale factors
		//sh.AddHistos("gen W",   { .fill="WTaggingEfficiency_vs_GenMatchedAK8JetPtBins",       .pfs={"FullFastSim"},                          .cuts={}, .draw="PE1",.opt=o_1or2d_"AddRatio", .ranges={}});
		//sh.AddHistos("gen W",   { .fill="WTaggingEfficiency_vs_GenMatchedAK8JetPtBins",       .pfs={"FullFastSim","GenMatchedAK8_EB_EE"},   .cuts={}, .draw="PE1",.opt=o_1or2d_"AddRatio", .ranges={}});
		//sh.AddHistos("gen top", { .fill="TopTaggingEfficiency_vs_GenMatchedAK8JetPtBins",     .pfs={"FullFastSim"},                          .cuts={}, .draw="PE1",.opt=o_1or2d_"AddRatio", .ranges={}});
		//sh.AddHistos("gen top", { .fill="TopTaggingEfficiency_vs_GenMatchedAK8JetPtBins",     .pfs={"FullFastSim","GenMatchedAK8_EB_EE"}, .cuts={}, .draw="PE1",.opt=o_1or2d_"AddRatio", .ranges={}});
		sh.AddHistos("gen hadW",   { .fill="HadWTaggingEfficiency_vs_GenMatchedAK8JetPtBins",    .pfs={"FullFastSim","YearFS",cut,"Syst"},                       .cuts={}, .draw="PE1",.opt=o_1or2d_d+"AddRatio", .ranges={}});
		sh.AddHistos("gen hadW",   { .fill="HadWTaggingEfficiency_vs_GenMatchedAK8JetPtBins",    .pfs={"FullFastSim","YearFS",cut,"Syst","GenMatchedAK8_EB_EE"}, .cuts={}, .draw="PE1",.opt=o_1or2d_d+"AddRatio", .ranges={}});
		sh.AddHistos("gen hadZ",   { .fill="HadZTaggingEfficiency_vs_GenMatchedAK8JetPtBins",    .pfs={"FullFastSim","YearFS",cut,"Syst"},                       .cuts={}, .draw="PE1",.opt=o_1or2d_d+"AddRatio", .ranges={}});
		sh.AddHistos("gen hadZ",   { .fill="HadZTaggingEfficiency_vs_GenMatchedAK8JetPtBins",    .pfs={"FullFastSim","YearFS",cut,"Syst","GenMatchedAK8_EB_EE"}, .cuts={}, .draw="PE1",.opt=o_1or2d_d+"AddRatio", .ranges={}});
		sh.AddHistos("gen hadV",   { .fill="HadVTaggingEfficiency_vs_GenMatchedAK8JetPtBins",    .pfs={"FullFastSim","YearFS",cut,"Syst"},                       .cuts={}, .draw="PE1",.opt=o_1or2d_d+"AddRatio", .ranges={}});
		sh.AddHistos("gen hadV",   { .fill="HadVTaggingEfficiency_vs_GenMatchedAK8JetPtBins",    .pfs={"FullFastSim","YearFS",cut,"Syst","GenMatchedAK8_EB_EE"}, .cuts={}, .draw="PE1",.opt=o_1or2d_d+"AddRatio", .ranges={}});
		sh.AddHistos("gen hadH",   { .fill="HadHTaggingEfficiency_vs_GenMatchedAK8JetPtBins",    .pfs={"FullFastSim","YearFS",cut,"Syst"},                       .cuts={}, .draw="PE1",.opt=o_1or2d_d+"AddRatio", .ranges={}});
		sh.AddHistos("gen hadH",   { .fill="HadHTaggingEfficiency_vs_GenMatchedAK8JetPtBins",    .pfs={"FullFastSim","YearFS",cut,"Syst","GenMatchedAK8_EB_EE"}, .cuts={}, .draw="PE1",.opt=o_1or2d_d+"AddRatio", .ranges={}});
		sh.AddHistos("gen hadtop", { .fill="HadTopTaggingEfficiency_vs_GenMatchedAK8JetPtBins",  .pfs={"FullFastSim","YearFS",cut,"Syst"},                       .cuts={}, .draw="PE1",.opt=o_1or2d_d+"AddRatio", .ranges={}});
		sh.AddHistos("gen hadtop", { .fill="HadTopTaggingEfficiency_vs_GenMatchedAK8JetPtBins",  .pfs={"FullFastSim","YearFS",cut,"Syst","GenMatchedAK8_EB_EE"}, .cuts={}, .draw="PE1",.opt=o_1or2d_d+"AddRatio", .ranges={}});
		sh.AddHistos("gen leptop", { .fill="LepTopTaggingEfficiency_vs_GenMatchedAK8JetPtBins",  .pfs={"FullFastSim","YearFS",cut,"Syst"},                       .cuts={}, .draw="PE1",.opt=o_1or2d_d+"AddRatio", .ranges={}});
		sh.AddHistos("gen leptop", { .fill="LepTopTaggingEfficiency_vs_GenMatchedAK8JetPtBins",  .pfs={"FullFastSim","YearFS",cut,"Syst","GenMatchedAK8_EB_EE"}, .cuts={}, .draw="PE1",.opt=o_1or2d_d+"AddRatio", .ranges={}});
		//sh.AddHistos("gen top", { .fill="LepJetTaggingEfficiency_vs_GenMatchedAK8JetPtBins",     .pfs={"FullFastSim"},                          .cuts={}, .draw="PE1",.opt=o_1or2d_d+"AddRatio", .ranges={}});
		//sh.AddHistos("gen top", { .fill="LepJetTaggingEfficiency_vs_GenMatchedAK8JetPtBins",     .pfs={"FullFastSim","GenMatchedAK8_EB_EE"}, .cuts={}, .draw="PE1",.opt=o_1or2d_d+"AddRatio", .ranges={}});
		sh.AddHistos("gen lep",    { .fill="LostLeptonRate_vs_GenLepPtBins", .pfs={"FullFastSim","YearFS",cut,"Syst"},                     .cuts={}, .draw="PE1",.opt=o_1or2d_d+"AddRatio", .ranges={}});
		sh.AddHistos("gen lep",    { .fill="LostLeptonRate_vs_GenLepPtBins", .pfs={"FullFastSim","YearFS",cut,"Syst","LostLeptonFlavour"}, .cuts={}, .draw="PE1",.opt=o_1or2d_d+"AddRatio", .ranges={}});
		sh.AddHistos("gen lep",    { .fill="LostLeptonRate_vs_GenLepEta",    .pfs={"FullFastSim","YearFS",cut,"Syst"},                     .cuts={}, .draw="PE1",.opt=o_1or2d_d+"AddRatio", .ranges={}});
		sh.AddHistos("gen lep",    { .fill="LostLeptonRate_vs_GenLepEta",    .pfs={"FullFastSim","YearFS",cut,"Syst","LostLeptonFlavour"}, .cuts={}, .draw="PE1",.opt=o_1or2d_d+"AddRatio", .ranges={}});
	}

	// ----------------------------------------------------------------------------------------------
	//                                     New signal segions
	//-----------------------------------------------------------------------------------------------





	//-----------------------------------------------------------------------------------------------
	// signal Efficiency for all regions

	/*
		 for (auto region : {Region::SR_Had_1htop, Region::SR_Had_2htop, Region::SR_Had_V_b_45j, Region::SR_Had_V_b_6j, Region::SR_Had_1V_0b_34j, Region::SR_Had_1V_0b_5j, Region::SR_Had_2V_0b_24j, Region::SR_Had_2V_0b_5j, 
		 Region::SR_Had_H_b_45j, Region::SR_Had_H_b_6j, Region::SR_Had_HV_b_6j, Region::SR_Had_H_0b_34j, Region::SR_Had_H_0b_5j, Region::SR_Had_HV_0b_24j, Region::SR_Had_HV_0b_5j,Region::SR_Lep_1htop, Region::SR_Lep_V_b, Region::SR_Lep_V_0b, Region::SR_Lep_H_b, Region::SR_Lep_H_0b,Region::SR_Leptop_0htop, Region::SR_Leptop_1htop, Region::SR_Lepjet_0V_24j, Region::SR_Lepjet_0V_5j, Region::SR_Lepjet_1V_24j, Region::SR_Lepjet_1V_5j}) {
		 sh.SetHistoWeights({ [&w,region] { return w.sf_weight[region]; } });

		 sh.AddHistos("evt",   { .fill="SignalSelectionEfficiency_vs_MLSP_vs_MGluino",    .pfs={"T5ttcc"},  .cuts={},.draw="COLZ",.opt=o_1or2d_s, .ranges={600,2800, 0,1900, 0,0, 0.02,0.95}});
		 sh.AddHistos("evt",   { .fill="SignalSelectionEfficiency_vs_MLSP_vs_MSquark",    .pfs={"TChiZH"},  .cuts={},.draw="COLZ",.opt=o_1or2d_s, .ranges={200,1500, 0,650, 0,0, 0.02,0.95}});
		 }
		 */


	//-----------------------------------------------------------------------------------------------


	// Fully hadronic Signal Regions
	for (auto region : {Region::SR_Had_1htop, Region::SR_Had_2htop, Region::SR_Had_V_b_45j, Region::SR_Had_V_b_6j, Region::SR_Had_1V_0b_34j, Region::SR_Had_1V_0b_5j, Region::SR_Had_2V_0b_24j, Region::SR_Had_2V_0b_5j, 
			Region::SR_Had_H_b_45j, Region::SR_Had_H_b_6j, Region::SR_Had_HV_b_6j, Region::SR_Had_H_0b_34j, Region::SR_Had_H_0b_5j, Region::SR_Had_HV_0b_24j, Region::SR_Had_HV_0b_5j}) {
		sh.SetHistoWeights({ [&w,region] { return w.sf_weight[region]; } });


		std::string cut(magic_enum::enum_name(region));


		// Signal Significance plots 

		sh.AddHistos("evt",   { .fill="SignalSignificance_T5ttcc_vs_MLSP_vs_MGluino",         .pfs={cut},               .cuts={},.draw="COLZ",.opt=o_1or2d_s, .ranges={600,2800, 0,1900, 0,0, 0.02,0.95}});
		sh.AddHistos("evt",   { .fill="SignalSignificance_TChiZH_vs_MLSP_vs_MSquark",           .pfs={cut},               .cuts={},.draw="COLZ",.opt=o_1or2d_s, .ranges={200,1500, 0,650, 0,0, 0.02,0.95}});





		std::vector<std::string> showdata = {"Blind"};
		// Stack plots
		for (auto data : showdata ) {
			std::string signal = "StackPlotSignal";
			std::string opt  = (data=="Blind") ? o_stk_s_S : o_stk_d_S;
			if (region==Region::SR_Had_1htop||region==Region::SR_Had_2htop||region==Region::SR_Had_V_b_45j||region==Region::SR_Had_V_b_6j) {
				opt    = (data=="Blind") ? o_stk_s_T : o_stk_d_T;
				signal = "StackPlotTopSignal";
			} else if (region==Region::SR_Had_1V_0b_34j||region==Region::SR_Had_1V_0b_5j||region==Region::SR_Had_2V_0b_24j||region==Region::SR_Had_2V_0b_5j) {
				opt    = (data=="Blind") ? o_stk_s_V : o_stk_d_V;
				signal = "StackPlotVSignal";
			} else if (region==Region::SR_Had_H_b_45j||region==Region::SR_Had_H_b_6j||region==Region::SR_Had_HV_b_6j||
					region==Region::SR_Had_H_0b_34j||region==Region::SR_Had_H_0b_5j||
					region==Region::SR_Had_HV_0b_24j||region==Region::SR_Had_HV_0b_5j) {
				opt    = (data=="Blind") ? o_stk_s_H : o_stk_d_H;
				signal = "StackPlotHSignal";
			}
			for (auto std_plot : standard_plots)
				sh.AddHistos("evt",    { .fill=std_plot,                    .pfs={signal,data,"Year",cut},                  .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
			sh.AddHistos(s+"evt",    { .fill=c+"MRR2",                  .pfs={signal,data,"Year",cut},                  .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
			sh.AddHistos(s+"evt",    { .fill=c+"MRR2",                  .pfs={signal,data,"run2",cut},                  .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
			sh.AddHistos(  "evt",    { .fill="NJet",                    .pfs={signal,data,"Year",cut},                  .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
			sh.AddHistos(  "evt",    { .fill="NJet",                    .pfs={signal,data,"Year",cut+"_ExclNJet"},      .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
			sh.AddHistos(  "evt",    { .fill="MTBoost",                 .pfs={signal,data,"Year",cut},                  .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
			sh.AddHistos(  "evt",    { .fill="DeltaPhi",                .pfs={signal,data,"Year",cut+"_ExcldPhi"},      .cuts={},.draw=d,.opt=opt,.ranges=r_Stk9});


		}
		// debug (Set FASTDEBUG 1 in SmartHistos)
		//if (region == Region::SR_Had_H_0b_34j)
		//  sh.AddHistos(1, s+"evt", { .fill=c+"MRR2",                    .pfs={"StackPlotHSignal","Blind","Year",cut},      .cuts={},.draw=d,.opt=o_stk_s_H,.ranges=r_Stk6});
	}


	// Isolated lepton Signal Regions
	for (auto region : {Region::SR_Lep_1htop, Region::SR_Lep_V_b, Region::SR_Lep_V_0b, Region::SR_Lep_H_b, Region::SR_Lep_H_0b}) {
		sh.SetHistoWeights({ [&w,region] { return w.sf_weight[region]; } });
		std::string cut(magic_enum::enum_name(region));

		// Signal Significance plots 

		sh.AddHistos("evt",   { .fill="SignalSignificance_T5ttcc_vs_MLSP_vs_MGluino",         .pfs={cut},               .cuts={},.draw="COLZ",.opt=o_1or2d_s, .ranges={600,2800, 0,1900, 0,0, 0.02,0.95}});
		sh.AddHistos("evt",   { .fill="SignalSignificance_TChiZH_vs_MLSP_vs_MSquark",           .pfs={cut},               .cuts={},.draw="COLZ",.opt=o_1or2d_s, .ranges={200,1500, 0,650, 0,0, 0.02,0.95}});




		std::vector<std::string> showdata = {"Blind"};
		// Stack plots
		for (auto data : showdata ) {
			std::string signal = "StackPlotSignal";
			std::string opt  = (data=="Blind") ? o_stk_s_S : o_stk_d_S;
			if (region==Region::SR_Lep_1htop) {
				opt    = (data=="Blind") ? o_stk_s_T : o_stk_d_T;
				signal = "StackPlotTopSignal";
			} else if (region==Region::SR_Lep_V_0b) {
				opt    = (data=="Blind") ? o_stk_s_V : o_stk_d_V;
				signal = "StackPlotVSignal";
			} else if (region==Region::SR_Lep_H_b||region==Region::SR_Lep_H_0b) {
				opt    = (data=="Blind") ? o_stk_s_H : o_stk_d_H;
				signal = "StackPlotHSignal";
			}
			for (auto std_plot : standard_plots)
				sh.AddHistos("evt",   { .fill=std_plot,                    .pfs={signal,data,"Year",cut},                  .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
			sh.AddHistos(s+"evt",   { .fill=c+"MRR2",                    .pfs={signal,data,"Year",cut},                  .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
			sh.AddHistos(s+"evt",   { .fill=c+"MRR2",                    .pfs={signal,data,"run2",cut},                  .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
			sh.AddHistos("evt",  { .fill="NJet",                         .pfs={signal,data,"Year",cut},                  .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
			if (region!=Region::SR_Lep_1htop&&region!=Region::SR_Lep_H_0b)
				sh.AddHistos("evt",  { .fill="NJet",                         .pfs={signal,data,"Year",cut+"_ExclNJet"},      .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
			sh.AddHistos("evt",  { .fill="MTBoost",                      .pfs={signal,data,"Year",cut},                  .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
			sh.AddHistos("evt",  { .fill="DeltaPhi",                     .pfs={signal,data,"Year",cut},                  .cuts={},.draw=d,.opt=opt,.ranges=r_Stk9});
			sh.AddHistos("evt",  { .fill="MTBoost",                      .pfs={signal,data,"Year",cut},                    .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
			sh.AddHistos("evt",  { .fill="DeltaPhi",                     .pfs={signal,data,"Year",cut},                    .cuts={},.draw=d,.opt=opt,.ranges=r_Stk9});
			sh.AddHistos("evt",  { .fill="DeltaPhi",                     .pfs={signal,data,"Year",cut+"_ExclMT"},             .cuts={},.draw=d,.opt=opt,.ranges=r_Stk9});
			sh.AddHistos("evt",  { .fill="MT",                           .pfs={signal,data,"Year",cut+"_ExclMT"},             .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
			sh.AddHistos("evt",  { .fill="MT2",                          .pfs={signal,data,"Year",cut+"_ExclMT"},             .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
			// TODO: Add leptonic discriminators similar to non-iso leptons (dphi etc)
			//sh.AddHistos("evt",  { .fill="DeltaPhiBoostedJetMET",        .pfs={signal,data,"Year",cut},                    .cuts={},.draw=d,.opt=opt,.ranges=r_Stk5});
			//sh.AddHistos("evt",  { .fill="DeltaPhiBoostedJetLep",        .pfs={signal,data,"Year",cut},                    .cuts={},.draw=d,.opt=opt,.ranges=r_Stk5});
			//sh.AddHistos("evt",  { .fill="DeltaPhiBoostedJetMET",        .pfs={signal,data,"Year",cut},                    .cuts={},.draw=d,.opt=opt,.ranges=r_Stk5});


		}
	}


	// Non-isolated lepton Signal Regions
	for (auto region : {Region::SR_Leptop_0htop, Region::SR_Leptop_1htop, Region::SR_Lepjet_0V_24j, Region::SR_Lepjet_0V_5j, Region::SR_Lepjet_1V_24j, Region::SR_Lepjet_1V_5j}) {
		sh.SetHistoWeights({ [&w,region] { return w.sf_weight[region]; } });
		std::string cut(magic_enum::enum_name(region));

		// Signal Significance plots 

		sh.AddHistos("evt",   { .fill="SignalSignificance_T5ttcc_vs_MLSP_vs_MGluino",         .pfs={cut},               .cuts={},.draw="COLZ",.opt=o_1or2d_s, .ranges={600,2800, 0,1900, 0,0, 0.02,0.95}});
		//sh.AddHistos("evt",   { .fill="SignalSignificance_TChiZH_vs_MLSP_vs_MSquark",           .pfs={cut},               .cuts={},.draw="COLZ",.opt=o_1or2d_s, .ranges={200,1500, 0,650, 0,0, 0.02,0.95}});



		std::vector<std::string> showdata = {"Blind"};
		// Stack plots
		for (auto data : showdata ) {
			std::string signal = "StackPlotSignal";
			std::string opt  = (data=="Blind") ? o_stk_s_S : o_stk_d_S;
			if (region==Region::SR_Leptop_0htop||region==Region::SR_Leptop_1htop) {
				opt    = (data=="Blind") ? o_stk_s_T : o_stk_d_T;
				signal = "StackPlotTopSignal";
			} else if (region==Region::SR_Lepjet_0V_24j||region==Region::SR_Lepjet_0V_5j||region==Region::SR_Lepjet_1V_24j||region==Region::SR_Lepjet_1V_5j) {
				opt    = (data=="Blind") ? o_stk_s_V : o_stk_d_V;
				signal = "StackPlotVSignal";
			}
			for (auto std_plot : standard_plots)
				sh.AddHistos("evt",   { .fill=std_plot,                    .pfs={signal,data,"Year",cut},                  .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
			sh.AddHistos(s+"evt",   { .fill=c+"MRR2",                    .pfs={signal,data,"Year",cut},                  .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
			sh.AddHistos(s+"evt",   { .fill=c+"MRR2",                    .pfs={signal,data,"run2",cut},                  .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
			sh.AddHistos(s+"evt",   { .fill=c+"newMRR2",                 .pfs={signal,data,"Year",cut},                  .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
			sh.AddHistos(s+"evt",   { .fill=c+"newMRR2",                 .pfs={signal,data,"run2",cut},                  .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
			//sh.AddHistos("evt",  { .fill="TestMRR2",                     .pfs={signal,data,"run2",cut},                  .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
			//sh.AddHistos("evt",  { .fill="TestnewMRR2",                  .pfs={signal,data,"run2",cut},                  .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
			sh.AddHistos("evt",  { .fill="NJet",                         .pfs={signal,data,"Year",cut},                  .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
			sh.AddHistos("evt",  { .fill="NJet",                         .pfs={signal,data,"Year",cut+"_ExclNJet"},      .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
			sh.AddHistos("evt",  { .fill="MTBoost",                      .pfs={signal,data,"Year",cut},                  .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
			sh.AddHistos("evt",  { .fill="DeltaPhi",                     .pfs={signal,data,"Year",cut},                  .cuts={},.draw=d,.opt=opt,.ranges=r_Stk9});
			sh.AddHistos("evt",  { .fill="NJet",                         .pfs={signal,data,"Year",cut},                    .cuts={},.draw=d,.opt=opt,.ranges=r_Stk5});
			sh.AddHistos("evt",  { .fill="NJet",                         .pfs={signal,data,"Year",cut+"_ExclNJet"},           .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
			sh.AddHistos("evt",  { .fill="MTBoost",                      .pfs={signal,data,"Year",cut},                    .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
			sh.AddHistos("evt",  { .fill="DeltaPhi",                     .pfs={signal,data,"Year",cut},                    .cuts={},.draw=d,.opt=opt,.ranges=r_Stk9});
			sh.AddHistos("evt",  { .fill="DeltaPhi",                     .pfs={signal,data,"Year",cut+"_ExclMT"},             .cuts={},.draw=d,.opt=opt,.ranges=r_Stk9});
			sh.AddHistos("evt",  { .fill="MT",                           .pfs={signal,data,"Year",cut+"_ExclMT"},             .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
			sh.AddHistos("evt",  { .fill="MT2",                          .pfs={signal,data,"Year",cut+"_ExclMT"},             .cuts={},.draw=d,.opt=opt,.ranges=r_Stk6});
			sh.AddHistos("evt",  { .fill="DeltaPhiBoostedJetMET",        .pfs={signal,data,"Year",cut},                    .cuts={},.draw=d,.opt=opt,.ranges=r_Stk5});
			sh.AddHistos("evt",  { .fill="DeltaPhiBoostedJetLep",        .pfs={signal,data,"Year",cut},                    .cuts={},.draw=d,.opt=opt,.ranges=r_Stk5});
			sh.AddHistos("evt",  { .fill="DeltaPhiBoostedJetMET",        .pfs={signal,data,"Year",cut+"_ExcldPhiJet"},     .cuts={},.draw=d,.opt=opt,.ranges=r_Stk5});
			sh.AddHistos("evt",  { .fill="DeltaPhiBoostedJetLep",        .pfs={signal,data,"Year",cut+"_ExcldPhiJet"},     .cuts={},.draw=d,.opt=opt,.ranges=r_Stk5});
			sh.AddHistos("evt",  { .fill="DeltaPhiBoostedJetLepMET",     .pfs={signal,data,"Year",cut+"_ExcldPhiJet"},     .cuts={},.draw=d,.opt=opt,.ranges=r_Stk5});

		}
	}

	int nbin_MRR2 = 15;
	Double_t* bn_MRR2 = 0;
	Double_t bn_MRR2_tmp[] = {0., 100., 200., 300., 400., 500., 600., 700., 800., 900., 1000., 1100., 1200., 1300., 1400., 3000.};
	bn_MRR2 = getVariableBinEdges(nbin_MRR2+1,bn_MRR2_tmp);
	int nbin_newMRR2 = 20;
	Double_t* bn_newMRR2 = 0;
	Double_t bn_newMRR2_tmp[] = {0, 30, 40, 50, 75, 100, 150, 200, 250, 300, 350, 400, 450, 500, 550, 600, 650, 700, 750, 800, 3000.};
	bn_newMRR2 = getVariableBinEdges(nbin_newMRR2+1,bn_newMRR2_tmp);

	// Normal histograms (not SmartHistos)
	// Signal systematics
	for (const auto& massbin : w.signal_bins) {
		std::vector<TH2D*> vh;
		std::vector<TH2D*> vh_new;
		if(!(massbin.first%25==0 && massbin.first/10000%25==0)) continue;

		for (const auto& regions : magic_enum::enum_entries<Region>()) {
			//Region region = regions.first;
			std::string regionname(regions.second);
			if (!TString(regionname).BeginsWith("SR_")) continue;
			//std::string name  = std::string(v.sample.Data())+"_"+regionname+"_"+massbin.second;
			//std::string name_new  = std::string(v.sample.Data())+"_"+regionname+"_"+massbin.second+"_new";
			//std::string title = std::string(v.sample.Data())+" "+regionname+" "+massbin.second+";M_{R} #times R^{2} (GeV);Systematic variations";
			std::string name  = std::string("MRR2_signal")+"_"+regionname+"_"+massbin.second;
			std::string name_new  = std::string("MRR2_signal")+"_"+regionname+"_"+massbin.second+"_new";
			std::string title = std::string("MRR2_signal")+" "+regionname+" "+massbin.second+";M_{R} #times R^{2} (GeV);Systematic variations";
			vh.push_back(new TH2D(name.c_str(), title.c_str(), nbin_MRR2, bn_MRR2, 1+syst_nSyst,-0.5,syst_nSyst+0.5));
			vh_new.push_back(new TH2D(name_new.c_str(), title.c_str(), nbin_newMRR2, bn_newMRR2, 1+syst_nSyst,-0.5,syst_nSyst+0.5));
		}
		m_vh_signal_binopt.insert({massbin.first, vh});
		m_vh_signal_new_binopt.insert({massbin.first, vh_new});
	}

	int nbn_MR = 0, nbn_MR_new = 0;
	Double_t* bn_MR = 0, *bn_MR_new = 0;

	for (auto region : {Region::SR_Had_1htop, Region::SR_Had_2htop, Region::SR_Had_V_b_45j, Region::SR_Had_V_b_6j, Region::SR_Had_1V_0b_34j, Region::SR_Had_1V_0b_5j, Region::SR_Had_2V_0b_24j,Region::SR_Had_2V_0b_5j, Region::SR_Had_H_b_45j, Region::SR_Had_H_b_6j, Region::SR_Had_HV_b_6j, Region::SR_Had_H_0b_34j, Region::SR_Had_H_0b_5j, Region::SR_Had_HV_0b_24j, Region::SR_Had_HV_0b_5j ,Region::SR_Lep_1htop, Region::SR_Lep_V_b, Region::SR_Lep_V_0b, Region::SR_Lep_H_b, Region::SR_Lep_H_0b, Region::SR_Leptop_0htop, Region::SR_Leptop_1htop, Region::SR_Lepjet_0V_24j, Region::SR_Lepjet_0V_5j, Region::SR_Lepjet_1V_24j, Region::SR_Lepjet_1V_5j}){

		if (region==Region::SR_Had_1htop) {
			//nbn_MR = ;
			//Double_t bn_MR_tmp[] = {};
			//bn_MR = getVariableBinEdges(nbn_MR+1,bn_MR_tmp);
			//nbn_MR_new = ;
			//Double_t bn_MR_new_tmp[] = {};
			//bn_MR_new = getVariableBinEdges(nbn_MR_new+1,bn_MR_new_tmp);
			nbn_MR = 15;
			Double_t bn_MR_tmp[] = {0, 100, 200, 300, 400, 500, 600, 700, 800, 900, 1000, 1100, 1200, 1300, 1400, 3000};
			bn_MR = getVariableBinEdges(nbn_MR+1,bn_MR_tmp);
			nbn_MR_new = 16;
			Double_t bn_MR_new_tmp[] = {0, 30, 40, 50, 75, 100, 150, 200, 250, 300, 350, 400, 450, 500, 600, 700, 3000};
			bn_MR_new = getVariableBinEdges(nbn_MR_new+1,bn_MR_new_tmp);

		} else if (region==Region::SR_Had_2htop) {
			nbn_MR = 9;
			Double_t bn_MR_tmp[] = {0, 100, 200, 300, 400, 500, 600, 700, 800, 3000};
			bn_MR = getVariableBinEdges(nbn_MR+1,bn_MR_tmp);
			nbn_MR_new = 11;
			Double_t bn_MR_new_tmp[] = {0, 30, 40, 50, 75, 100, 150, 200, 250, 300, 350, 3000};
			bn_MR_new = getVariableBinEdges(nbn_MR_new+1,bn_MR_new_tmp);

		} else if (region==Region::SR_Had_V_b_45j) {
			nbn_MR = 12;
			Double_t bn_MR_tmp[] = {0, 100, 200, 300, 400, 500, 600, 700, 800, 900, 1000, 1100, 3000};
			bn_MR = getVariableBinEdges(nbn_MR+1,bn_MR_tmp);
			nbn_MR_new = 13;
			Double_t bn_MR_new_tmp[] = {0, 30, 40, 50, 75, 100, 150, 200, 250, 300, 350, 400, 450, 3000};
			bn_MR_new = getVariableBinEdges(nbn_MR_new+1,bn_MR_new_tmp);

		} else if (region==Region::SR_Had_V_b_6j) {
			nbn_MR = 11;
			Double_t bn_MR_tmp[] = {0, 100, 200, 300, 400, 500, 600, 700, 800, 900, 1000, 3000};
			bn_MR = getVariableBinEdges(nbn_MR+1,bn_MR_tmp);
			nbn_MR_new = 12;
			Double_t bn_MR_new_tmp[] = {0, 30, 40, 50, 75, 100, 150, 200, 250, 300, 350, 400, 3000};
			bn_MR_new = getVariableBinEdges(nbn_MR_new+1,bn_MR_new_tmp);

		} else if (region==Region::SR_Had_1V_0b_34j) {
			nbn_MR = 14;
			Double_t bn_MR_tmp[] = {0, 100, 200, 300, 400, 500, 600, 700, 800, 900, 1000, 1100, 1200, 1300, 3000};
			bn_MR = getVariableBinEdges(nbn_MR+1,bn_MR_tmp);
			nbn_MR_new = 15;
			Double_t bn_MR_new_tmp[] = {0, 30, 40, 50, 75, 100, 150, 200, 250, 300, 350, 400, 450, 500, 550, 3000};
			bn_MR_new = getVariableBinEdges(nbn_MR_new+1,bn_MR_new_tmp);

		} else if (region==Region::SR_Had_1V_0b_5j) {
			nbn_MR = 11;
			Double_t bn_MR_tmp[] = {0, 100, 200, 300, 400, 500, 600, 700, 800, 900, 1000, 3000};
			bn_MR = getVariableBinEdges(nbn_MR+1,bn_MR_tmp);
			nbn_MR_new = 13;
			Double_t bn_MR_new_tmp[] = {0, 30, 40, 50, 75, 100, 150, 200, 250, 300, 350, 400, 450, 3000};
			bn_MR_new = getVariableBinEdges(nbn_MR_new+1,bn_MR_new_tmp);

		} else if (region==Region::SR_Had_2V_0b_24j) {
			nbn_MR = 8;
			Double_t bn_MR_tmp[] = {0, 100, 200, 300, 400, 500, 600, 700, 3000};
			bn_MR = getVariableBinEdges(nbn_MR+1,bn_MR_tmp);
			nbn_MR_new = 8;
			Double_t bn_MR_new_tmp[] = {0, 30, 40, 50, 75, 100, 150, 200, 3000};
			bn_MR_new = getVariableBinEdges(nbn_MR_new+1,bn_MR_new_tmp);

		} else if (region==Region::SR_Had_2V_0b_5j) {
			nbn_MR = 7;
			Double_t bn_MR_tmp[] = {0, 100, 200, 300, 400, 500, 600, 3000};
			bn_MR = getVariableBinEdges(nbn_MR+1,bn_MR_tmp);
			nbn_MR_new = 8;
			Double_t bn_MR_new_tmp[] = {0, 30, 40, 50, 75, 100, 150, 200, 3000};
			bn_MR_new = getVariableBinEdges(nbn_MR_new+1,bn_MR_new_tmp);

		} else if (region==Region::SR_Had_H_b_45j) {
			nbn_MR = 10;
			Double_t bn_MR_tmp[] = {0, 100, 200, 300, 400, 500, 600, 700, 800, 900, 3000};
			bn_MR = getVariableBinEdges(nbn_MR+1,bn_MR_tmp);
			nbn_MR_new = 10;
			Double_t bn_MR_new_tmp[] = {0, 30, 40, 50, 75, 100, 150, 200, 250, 300, 3000};
			bn_MR_new = getVariableBinEdges(nbn_MR_new+1,bn_MR_new_tmp);

		} else if (region==Region::SR_Had_H_b_6j) {
			nbn_MR = 7;
			Double_t bn_MR_tmp[] = {0, 100, 200, 300, 400, 500, 600, 3000};
			bn_MR = getVariableBinEdges(nbn_MR+1,bn_MR_tmp);
			nbn_MR_new = 8;
			Double_t bn_MR_new_tmp[] = {0, 30, 40, 50, 75, 100, 150, 200, 3000};
			bn_MR_new = getVariableBinEdges(nbn_MR_new+1,bn_MR_new_tmp);

		} else if (region==Region::SR_Had_HV_b_6j) {
			nbn_MR = 5;
			Double_t bn_MR_tmp[] = {0, 100, 200, 300, 400, 3000};
			bn_MR = getVariableBinEdges(nbn_MR+1,bn_MR_tmp);
			nbn_MR_new = 5;
			Double_t bn_MR_new_tmp[] = {0, 30, 50, 75, 150, 3000};
			bn_MR_new = getVariableBinEdges(nbn_MR_new+1,bn_MR_new_tmp);

		} else if (region==Region::SR_Had_H_0b_34j) {
			nbn_MR = 10;
			Double_t bn_MR_tmp[] = {0, 100, 200, 300, 400, 500, 600, 700, 800, 900, 3000};
			bn_MR = getVariableBinEdges(nbn_MR+1,bn_MR_tmp);
			nbn_MR_new = 9;
			Double_t bn_MR_new_tmp[] = {0, 30, 40, 50, 75, 100, 150, 200, 250, 3000};
			bn_MR_new = getVariableBinEdges(nbn_MR_new+1,bn_MR_new_tmp);

		} else if (region==Region::SR_Had_H_0b_5j) {
			nbn_MR = 8;
			Double_t bn_MR_tmp[] = {0, 100, 200, 300, 400, 500, 600, 700, 3000};
			bn_MR = getVariableBinEdges(nbn_MR+1,bn_MR_tmp);
			nbn_MR_new = 8;
			Double_t bn_MR_new_tmp[] = {0, 30, 40, 50, 75, 100, 150, 200, 3000};
			bn_MR_new = getVariableBinEdges(nbn_MR_new+1,bn_MR_new_tmp);

		} else if (region==Region::SR_Had_HV_0b_24j) {
			nbn_MR = 4;
			Double_t bn_MR_tmp[] = {0, 200, 300, 500, 3000};
			bn_MR = getVariableBinEdges(nbn_MR+1,bn_MR_tmp);
			nbn_MR_new = 3;
			Double_t bn_MR_new_tmp[] = {0, 30, 40, 3000};
			bn_MR_new = getVariableBinEdges(nbn_MR_new+1,bn_MR_new_tmp);

		} else if (region==Region::SR_Had_HV_0b_5j) {
			nbn_MR = 4;
			Double_t bn_MR_tmp[] = {0, 200, 300, 500, 3000};
			bn_MR = getVariableBinEdges(nbn_MR+1,bn_MR_tmp);
			nbn_MR_new = 4;
			Double_t bn_MR_new_tmp[] = {0, 30, 40, 50, 3000};
			bn_MR_new = getVariableBinEdges(nbn_MR_new+1,bn_MR_new_tmp);

		} else if (region==Region::SR_Lep_H_b) {
			nbn_MR = 6;
			Double_t bn_MR_tmp[] = {0, 100, 200, 300, 400, 500, 3000};
			bn_MR = getVariableBinEdges(nbn_MR+1,bn_MR_tmp);
			nbn_MR_new = 7;
			Double_t bn_MR_new_tmp[] = {0, 30, 40, 50, 75, 100, 150, 3000};
			bn_MR_new = getVariableBinEdges(nbn_MR_new+1,bn_MR_new_tmp);

		} else if (region==Region::SR_Lep_H_0b) {
			nbn_MR = 6;
			Double_t bn_MR_tmp[] = {0, 100, 200, 300, 400, 500, 3000};
			bn_MR = getVariableBinEdges(nbn_MR+1,bn_MR_tmp);
			nbn_MR_new = 7;
			Double_t bn_MR_new_tmp[] = {0, 30, 40, 50, 75, 150, 250, 3000};
			bn_MR_new = getVariableBinEdges(nbn_MR_new+1,bn_MR_new_tmp);

		} else if (region==Region::SR_Lep_1htop) {
			nbn_MR = 12;
			Double_t bn_MR_tmp[] = {0, 100, 200, 300, 400, 500, 600, 700, 800, 900, 1000, 1100, 3000};
			bn_MR = getVariableBinEdges(nbn_MR+1,bn_MR_tmp);
			nbn_MR_new = 13;
			Double_t bn_MR_new_tmp[] = {0, 30, 40, 50, 75, 100, 150, 200, 250, 300, 350, 400, 450, 3000};
			bn_MR_new = getVariableBinEdges(nbn_MR_new+1,bn_MR_new_tmp);

		} else if (region==Region::SR_Lep_V_b) {
			nbn_MR = 9;
			Double_t bn_MR_tmp[] = {0, 100, 200, 300, 400, 500, 600, 700, 800, 3000};
			bn_MR = getVariableBinEdges(nbn_MR+1,bn_MR_tmp);
			nbn_MR_new = 11;
			Double_t bn_MR_new_tmp[] = {0, 30, 40, 50, 75, 100, 150, 200, 250, 300, 350, 3000};
			bn_MR_new = getVariableBinEdges(nbn_MR_new+1,bn_MR_new_tmp);

		} else if (region==Region::SR_Lep_V_0b) {
			nbn_MR = 9;
			Double_t bn_MR_tmp[] = {0, 100, 200, 300, 400, 500, 600, 700, 800, 3000};
			bn_MR = getVariableBinEdges(nbn_MR+1,bn_MR_tmp);
			nbn_MR_new = 9;
			Double_t bn_MR_new_tmp[] = {0, 30, 40, 50, 75, 100, 150, 200, 250, 3000};
			bn_MR_new = getVariableBinEdges(nbn_MR_new+1,bn_MR_new_tmp);

		} else if (region==Region::SR_Leptop_0htop) {
			nbn_MR = 15;
			Double_t bn_MR_tmp[] = {0, 100, 200, 300, 400, 500, 600, 700, 800, 900, 1000, 1100, 1200, 1300, 1400, 3000};
			bn_MR = getVariableBinEdges(nbn_MR+1,bn_MR_tmp);
			nbn_MR_new = 17;
			Double_t bn_MR_new_tmp[] = {0, 30, 40, 50, 75, 100, 150, 200, 250, 300, 350, 400, 450, 500, 550, 600, 650, 3000};
			bn_MR_new = getVariableBinEdges(nbn_MR_new+1,bn_MR_new_tmp);

		} else if (region==Region::SR_Leptop_1htop) {
			nbn_MR = 8;
			Double_t bn_MR_tmp[] = {0, 100, 200, 300, 400, 500, 600, 700, 3000};
			bn_MR = getVariableBinEdges(nbn_MR+1,bn_MR_tmp);
			nbn_MR_new = 11;
			Double_t bn_MR_new_tmp[] = {0, 30, 40, 50, 75, 100, 150, 200, 250, 300, 350, 3000};
			bn_MR_new = getVariableBinEdges(nbn_MR_new+1,bn_MR_new_tmp);

		} else if (region==Region::SR_Lepjet_0V_24j) {
			nbn_MR = 15;
			Double_t bn_MR_tmp[] = {0, 100, 200, 300, 400, 500, 600, 700, 800, 900, 1000, 1100, 1200, 1300, 1400, 3000};
			bn_MR = getVariableBinEdges(nbn_MR+1,bn_MR_tmp);
			nbn_MR_new = 17;
			Double_t bn_MR_new_tmp[] = {0, 30, 40, 50, 75, 100, 150, 200, 250, 300, 350, 400, 450, 500, 550, 650, 750, 3000};
			bn_MR_new = getVariableBinEdges(nbn_MR_new+1,bn_MR_new_tmp);

		} else if (region==Region::SR_Lepjet_0V_5j) {
			nbn_MR = 12;
			Double_t bn_MR_tmp[] = {0, 100, 200, 300, 400, 500, 600, 700, 800, 900, 1000, 1100, 3000};
			bn_MR = getVariableBinEdges(nbn_MR+1,bn_MR_tmp);
			nbn_MR_new = 14;
			Double_t bn_MR_new_tmp[] = {0, 30, 40, 50, 75, 100, 150, 200, 250, 300, 350, 400, 450, 500, 3000};
			bn_MR_new = getVariableBinEdges(nbn_MR_new+1,bn_MR_new_tmp);

		} else if (region==Region::SR_Lepjet_1V_24j) {
			nbn_MR = 8;
			Double_t bn_MR_tmp[] = {0, 100, 200, 300, 400, 500, 600, 700, 3000};
			bn_MR = getVariableBinEdges(nbn_MR+1,bn_MR_tmp);
			nbn_MR_new = 10;
			Double_t bn_MR_new_tmp[] = {0, 30, 40, 50, 75, 100, 150, 200, 250, 300, 3000};
			bn_MR_new = getVariableBinEdges(nbn_MR_new+1,bn_MR_new_tmp);

		} else if (region==Region::SR_Lepjet_1V_5j) {
			nbn_MR = 7;
			Double_t bn_MR_tmp[] = {0, 100, 200, 300, 400, 500, 600, 3000};
			bn_MR = getVariableBinEdges(nbn_MR+1,bn_MR_tmp);
			nbn_MR_new = 8;
			Double_t bn_MR_new_tmp[] = {0, 30, 40, 50, 75, 100, 150, 200, 3000};
			bn_MR_new = getVariableBinEdges(nbn_MR_new+1,bn_MR_new_tmp);
		} 
		std::string regionname(magic_enum::enum_name(region));

		//Background
		if (!v.isSignal&&!v.isData) {
			std::string name1  = std::string("MRR2_S_bkg")+"_"+regionname;
			std::string title1 = std::string("MRR2_S_bkg")+" "+regionname+";M_{R} #times R^{2} (GeV);Systematic variations";
			vvh_MRR2_bkg.push_back(new TH2D(name1.c_str(), title1.c_str(), nbn_MR,bn_MR, 1+syst_nSyst,-0.5,syst_nSyst+0.5));
			name1  = std::string("MRR2_bkg")+"_"+regionname;
			title1 = std::string("MRR2_bkg")+" "+regionname+";M_{R} #times R^{2} (GeV);Systematic variations";
			vvh_MRR2_bkg_binopt.push_back(new TH2D(name1.c_str(), title1.c_str(), nbin_MRR2,bn_MRR2, 1+syst_nSyst,-0.5,syst_nSyst+0.5));
			name1  = std::string("MRR2_S_bkg")+"_"+regionname+"_new";
			title1 = std::string("MRR2_S_bkg")+" "+regionname+";M_{R} #times R^{2} (GeV);Systematic variations";
			vvh_MRR2_bkg_new.push_back(new TH2D(name1.c_str(), title1.c_str(), nbn_MR_new, bn_MR_new, 1+syst_nSyst,-0.5,syst_nSyst+0.5));
			name1  = std::string("MRR2_bkg")+"_"+regionname+"_new";
			title1 = std::string("MRR2_bkg")+" "+regionname+";M_{R} #times R^{2} (GeV);Systematic variations";
			vvh_MRR2_bkg_new_binopt.push_back(new TH2D(name1.c_str(), title1.c_str(), nbin_newMRR2, bn_newMRR2, 1+syst_nSyst,-0.5,syst_nSyst+0.5));
		}
		//Data
		if (v.isData) {
			std::string name2  = std::string("MRR2_S_data")+"_"+regionname;
			std::string title2 = std::string("MRR2_S_data")+" "+regionname+";M_{R} #times R^{2} (GeV)";
			vvh_MRR2_data.push_back(new TH1D(name2.c_str(), title2.c_str(), nbn_MR,bn_MR));
			name2  = std::string("MRR2_data")+"_"+regionname;
			title2 = std::string("MRR2_data")+" "+regionname+";M_{R} #times R^{2} (GeV)";
			vvh_MRR2_data_binopt.push_back(new TH1D(name2.c_str(), title2.c_str(), nbin_newMRR2, bn_newMRR2));
			name2  = std::string("MRR2_S_data")+"_"+regionname+"_new";
			title2 = std::string("MRR2_S_data")+" "+regionname+";M_{R} #times R^{2} (GeV);Systematic variations";
			vvh_MRR2_data_new.push_back(new TH1D(name2.c_str(), title2.c_str(), nbn_MR_new, bn_MR_new));
			name2  = std::string("MRR2_data")+"_"+regionname+"_new";
			title2 = std::string("MRR2_data")+" "+regionname+";M_{R} #times R^{2} (GeV);Systematic variations";
			vvh_MRR2_data_new_binopt.push_back(new TH1D(name2.c_str(), title2.c_str(), nbin_newMRR2, bn_newMRR2));
		}
	}


	for (const auto& massbin : w.signal_bins) { 
		std::vector<TH2D*> vh;
		std::vector<TH2D*> vh_new;
		if(!(massbin.first%25==0 && massbin.first/10000%25==0)) continue;

		int nbn_MR = 11;
		Double_t* bn_MR = 0;

		for (auto region : {Region::SR_Had_1htop, Region::SR_Had_2htop, Region::SR_Had_V_b_45j, Region::SR_Had_V_b_6j, Region::SR_Had_1V_0b_34j, Region::SR_Had_1V_0b_5j, Region::SR_Had_2V_0b_24j,Region::SR_Had_2V_0b_5j, Region::SR_Had_H_b_45j, Region::SR_Had_H_b_6j, Region::SR_Had_HV_b_6j, Region::SR_Had_H_0b_34j, Region::SR_Had_H_0b_5j, Region::SR_Had_HV_0b_24j, Region::SR_Had_HV_0b_5j ,Region::SR_Lep_1htop, Region::SR_Lep_V_b, Region::SR_Lep_V_0b, Region::SR_Lep_H_b, Region::SR_Lep_H_0b, Region::SR_Leptop_0htop, Region::SR_Leptop_1htop, Region::SR_Lepjet_0V_24j, Region::SR_Lepjet_0V_5j, Region::SR_Lepjet_1V_24j, Region::SR_Lepjet_1V_5j}){

			if (region==Region::SR_Had_1htop) {
				//nbn_MR = ;
				//Double_t bn_MR_tmp[] = {};
				//bn_MR = getVariableBinEdges(nbn_MR+1,bn_MR_tmp);
				//nbn_MR_new = ;
				//Double_t bn_MR_new_tmp[] = {};
				//bn_MR_new = getVariableBinEdges(nbn_MR_new+1,bn_MR_new_tmp);
				nbn_MR = 15;
				Double_t bn_MR_tmp[] = {0, 100, 200, 300, 400, 500, 600, 700, 800, 900, 1000, 1100, 1200, 1300, 1400, 3000};
				bn_MR = getVariableBinEdges(nbn_MR+1,bn_MR_tmp);
				nbn_MR_new = 16;
				Double_t bn_MR_new_tmp[] = {0, 30, 40, 50, 75, 100, 150, 200, 250, 300, 350, 400, 450, 500, 600, 700, 3000};
				bn_MR_new = getVariableBinEdges(nbn_MR_new+1,bn_MR_new_tmp);
	
			} else if (region==Region::SR_Had_2htop) {
				nbn_MR = 9;
				Double_t bn_MR_tmp[] = {0, 100, 200, 300, 400, 500, 600, 700, 800, 3000};
				bn_MR = getVariableBinEdges(nbn_MR+1,bn_MR_tmp);
				nbn_MR_new = 11;
				Double_t bn_MR_new_tmp[] = {0, 30, 40, 50, 75, 100, 150, 200, 250, 300, 350, 3000};
				bn_MR_new = getVariableBinEdges(nbn_MR_new+1,bn_MR_new_tmp);
	
			} else if (region==Region::SR_Had_V_b_45j) {
				nbn_MR = 12;
				Double_t bn_MR_tmp[] = {0, 100, 200, 300, 400, 500, 600, 700, 800, 900, 1000, 1100, 3000};
				bn_MR = getVariableBinEdges(nbn_MR+1,bn_MR_tmp);
				nbn_MR_new = 13;
				Double_t bn_MR_new_tmp[] = {0, 30, 40, 50, 75, 100, 150, 200, 250, 300, 350, 400, 450, 3000};
				bn_MR_new = getVariableBinEdges(nbn_MR_new+1,bn_MR_new_tmp);
	
			} else if (region==Region::SR_Had_V_b_6j) {
				nbn_MR = 11;
				Double_t bn_MR_tmp[] = {0, 100, 200, 300, 400, 500, 600, 700, 800, 900, 1000, 3000};
				bn_MR = getVariableBinEdges(nbn_MR+1,bn_MR_tmp);
				nbn_MR_new = 12;
				Double_t bn_MR_new_tmp[] = {0, 30, 40, 50, 75, 100, 150, 200, 250, 300, 350, 400, 3000};
				bn_MR_new = getVariableBinEdges(nbn_MR_new+1,bn_MR_new_tmp);
	
			} else if (region==Region::SR_Had_1V_0b_34j) {
				nbn_MR = 14;
				Double_t bn_MR_tmp[] = {0, 100, 200, 300, 400, 500, 600, 700, 800, 900, 1000, 1100, 1200, 1300, 3000};
				bn_MR = getVariableBinEdges(nbn_MR+1,bn_MR_tmp);
				nbn_MR_new = 15;
				Double_t bn_MR_new_tmp[] = {0, 30, 40, 50, 75, 100, 150, 200, 250, 300, 350, 400, 450, 500, 550, 3000};
				bn_MR_new = getVariableBinEdges(nbn_MR_new+1,bn_MR_new_tmp);
	
			} else if (region==Region::SR_Had_1V_0b_5j) {
				nbn_MR = 11;
				Double_t bn_MR_tmp[] = {0, 100, 200, 300, 400, 500, 600, 700, 800, 900, 1000, 3000};
				bn_MR = getVariableBinEdges(nbn_MR+1,bn_MR_tmp);
				nbn_MR_new = 13;
				Double_t bn_MR_new_tmp[] = {0, 30, 40, 50, 75, 100, 150, 200, 250, 300, 350, 400, 450, 3000};
				bn_MR_new = getVariableBinEdges(nbn_MR_new+1,bn_MR_new_tmp);
	
			} else if (region==Region::SR_Had_2V_0b_24j) {
				nbn_MR = 8;
				Double_t bn_MR_tmp[] = {0, 100, 200, 300, 400, 500, 600, 700, 3000};
				bn_MR = getVariableBinEdges(nbn_MR+1,bn_MR_tmp);
				nbn_MR_new = 8;
				Double_t bn_MR_new_tmp[] = {0, 30, 40, 50, 75, 100, 150, 200, 3000};
				bn_MR_new = getVariableBinEdges(nbn_MR_new+1,bn_MR_new_tmp);
	
			} else if (region==Region::SR_Had_2V_0b_5j) {
				nbn_MR = 7;
				Double_t bn_MR_tmp[] = {0, 100, 200, 300, 400, 500, 600, 3000};
				bn_MR = getVariableBinEdges(nbn_MR+1,bn_MR_tmp);
				nbn_MR_new = 8;
				Double_t bn_MR_new_tmp[] = {0, 30, 40, 50, 75, 100, 150, 200, 3000};
				bn_MR_new = getVariableBinEdges(nbn_MR_new+1,bn_MR_new_tmp);
	
			} else if (region==Region::SR_Had_H_b_45j) {
				nbn_MR = 10;
				Double_t bn_MR_tmp[] = {0, 100, 200, 300, 400, 500, 600, 700, 800, 900, 3000};
				bn_MR = getVariableBinEdges(nbn_MR+1,bn_MR_tmp);
				nbn_MR_new = 10;
				Double_t bn_MR_new_tmp[] = {0, 30, 40, 50, 75, 100, 150, 200, 250, 300, 3000};
				bn_MR_new = getVariableBinEdges(nbn_MR_new+1,bn_MR_new_tmp);
	
			} else if (region==Region::SR_Had_H_b_6j) {
				nbn_MR = 7;
				Double_t bn_MR_tmp[] = {0, 100, 200, 300, 400, 500, 600, 3000};
				bn_MR = getVariableBinEdges(nbn_MR+1,bn_MR_tmp);
				nbn_MR_new = 8;
				Double_t bn_MR_new_tmp[] = {0, 30, 40, 50, 75, 100, 150, 200, 3000};
				bn_MR_new = getVariableBinEdges(nbn_MR_new+1,bn_MR_new_tmp);
	
			} else if (region==Region::SR_Had_HV_b_6j) {
				nbn_MR = 5;
				Double_t bn_MR_tmp[] = {0, 100, 200, 300, 400, 3000};
				bn_MR = getVariableBinEdges(nbn_MR+1,bn_MR_tmp);
				nbn_MR_new = 5;
				Double_t bn_MR_new_tmp[] = {0, 30, 50, 75, 150, 3000};
				bn_MR_new = getVariableBinEdges(nbn_MR_new+1,bn_MR_new_tmp);
	
			} else if (region==Region::SR_Had_H_0b_34j) {
				nbn_MR = 10;
				Double_t bn_MR_tmp[] = {0, 100, 200, 300, 400, 500, 600, 700, 800, 900, 3000};
				bn_MR = getVariableBinEdges(nbn_MR+1,bn_MR_tmp);
				nbn_MR_new = 9;
				Double_t bn_MR_new_tmp[] = {0, 30, 40, 50, 75, 100, 150, 200, 250, 3000};
				bn_MR_new = getVariableBinEdges(nbn_MR_new+1,bn_MR_new_tmp);
	
			} else if (region==Region::SR_Had_H_0b_5j) {
				nbn_MR = 8;
				Double_t bn_MR_tmp[] = {0, 100, 200, 300, 400, 500, 600, 700, 3000};
				bn_MR = getVariableBinEdges(nbn_MR+1,bn_MR_tmp);
				nbn_MR_new = 8;
				Double_t bn_MR_new_tmp[] = {0, 30, 40, 50, 75, 100, 150, 200, 3000};
				bn_MR_new = getVariableBinEdges(nbn_MR_new+1,bn_MR_new_tmp);
	
			} else if (region==Region::SR_Had_HV_0b_24j) {
				nbn_MR = 4;
				Double_t bn_MR_tmp[] = {0, 200, 300, 500, 3000};
				bn_MR = getVariableBinEdges(nbn_MR+1,bn_MR_tmp);
				nbn_MR_new = 3;
				Double_t bn_MR_new_tmp[] = {0, 30, 40, 3000};
				bn_MR_new = getVariableBinEdges(nbn_MR_new+1,bn_MR_new_tmp);
	
			} else if (region==Region::SR_Had_HV_0b_5j) {
				nbn_MR = 4;
				Double_t bn_MR_tmp[] = {0, 200, 300, 500, 3000};
				bn_MR = getVariableBinEdges(nbn_MR+1,bn_MR_tmp);
				nbn_MR_new = 4;
				Double_t bn_MR_new_tmp[] = {0, 30, 40, 50, 3000};
				bn_MR_new = getVariableBinEdges(nbn_MR_new+1,bn_MR_new_tmp);
	
			} else if (region==Region::SR_Lep_H_b) {
				nbn_MR = 6;
				Double_t bn_MR_tmp[] = {0, 100, 200, 300, 400, 500, 3000};
				bn_MR = getVariableBinEdges(nbn_MR+1,bn_MR_tmp);
				nbn_MR_new = 7;
				Double_t bn_MR_new_tmp[] = {0, 30, 40, 50, 75, 100, 150, 3000};
				bn_MR_new = getVariableBinEdges(nbn_MR_new+1,bn_MR_new_tmp);
	
			} else if (region==Region::SR_Lep_H_0b) {
				nbn_MR = 6;
				Double_t bn_MR_tmp[] = {0, 100, 200, 300, 400, 500, 3000};
				bn_MR = getVariableBinEdges(nbn_MR+1,bn_MR_tmp);
				nbn_MR_new = 7;
				Double_t bn_MR_new_tmp[] = {0, 30, 40, 50, 75, 150, 250, 3000};
				bn_MR_new = getVariableBinEdges(nbn_MR_new+1,bn_MR_new_tmp);
	
			} else if (region==Region::SR_Lep_1htop) {
				nbn_MR = 12;
				Double_t bn_MR_tmp[] = {0, 100, 200, 300, 400, 500, 600, 700, 800, 900, 1000, 1100, 3000};
				bn_MR = getVariableBinEdges(nbn_MR+1,bn_MR_tmp);
				nbn_MR_new = 13;
				Double_t bn_MR_new_tmp[] = {0, 30, 40, 50, 75, 100, 150, 200, 250, 300, 350, 400, 450, 3000};
				bn_MR_new = getVariableBinEdges(nbn_MR_new+1,bn_MR_new_tmp);
	
			} else if (region==Region::SR_Lep_V_b) {
				nbn_MR = 9;
				Double_t bn_MR_tmp[] = {0, 100, 200, 300, 400, 500, 600, 700, 800, 3000};
				bn_MR = getVariableBinEdges(nbn_MR+1,bn_MR_tmp);
				nbn_MR_new = 11;
				Double_t bn_MR_new_tmp[] = {0, 30, 40, 50, 75, 100, 150, 200, 250, 300, 350, 3000};
				bn_MR_new = getVariableBinEdges(nbn_MR_new+1,bn_MR_new_tmp);
	
			} else if (region==Region::SR_Lep_V_0b) {
				nbn_MR = 9;
				Double_t bn_MR_tmp[] = {0, 100, 200, 300, 400, 500, 600, 700, 800, 3000};
				bn_MR = getVariableBinEdges(nbn_MR+1,bn_MR_tmp);
				nbn_MR_new = 9;
				Double_t bn_MR_new_tmp[] = {0, 30, 40, 50, 75, 100, 150, 200, 250, 3000};
				bn_MR_new = getVariableBinEdges(nbn_MR_new+1,bn_MR_new_tmp);
	
			} else if (region==Region::SR_Leptop_0htop) {
				nbn_MR = 15;
				Double_t bn_MR_tmp[] = {0, 100, 200, 300, 400, 500, 600, 700, 800, 900, 1000, 1100, 1200, 1300, 1400, 3000};
				bn_MR = getVariableBinEdges(nbn_MR+1,bn_MR_tmp);
				nbn_MR_new = 17;
				Double_t bn_MR_new_tmp[] = {0, 30, 40, 50, 75, 100, 150, 200, 250, 300, 350, 400, 450, 500, 550, 600, 650, 3000};
				bn_MR_new = getVariableBinEdges(nbn_MR_new+1,bn_MR_new_tmp);
	
			} else if (region==Region::SR_Leptop_1htop) {
				nbn_MR = 8;
				Double_t bn_MR_tmp[] = {0, 100, 200, 300, 400, 500, 600, 700, 3000};
				bn_MR = getVariableBinEdges(nbn_MR+1,bn_MR_tmp);
				nbn_MR_new = 11;
				Double_t bn_MR_new_tmp[] = {0, 30, 40, 50, 75, 100, 150, 200, 250, 300, 350, 3000};
				bn_MR_new = getVariableBinEdges(nbn_MR_new+1,bn_MR_new_tmp);
	
			} else if (region==Region::SR_Lepjet_0V_24j) {
				nbn_MR = 15;
				Double_t bn_MR_tmp[] = {0, 100, 200, 300, 400, 500, 600, 700, 800, 900, 1000, 1100, 1200, 1300, 1400, 3000};
				bn_MR = getVariableBinEdges(nbn_MR+1,bn_MR_tmp);
				nbn_MR_new = 17;
				Double_t bn_MR_new_tmp[] = {0, 30, 40, 50, 75, 100, 150, 200, 250, 300, 350, 400, 450, 500, 550, 650, 750, 3000};
				bn_MR_new = getVariableBinEdges(nbn_MR_new+1,bn_MR_new_tmp);
	
			} else if (region==Region::SR_Lepjet_0V_5j) {
				nbn_MR = 12;
				Double_t bn_MR_tmp[] = {0, 100, 200, 300, 400, 500, 600, 700, 800, 900, 1000, 1100, 3000};
				bn_MR = getVariableBinEdges(nbn_MR+1,bn_MR_tmp);
				nbn_MR_new = 14;
				Double_t bn_MR_new_tmp[] = {0, 30, 40, 50, 75, 100, 150, 200, 250, 300, 350, 400, 450, 500, 3000};
				bn_MR_new = getVariableBinEdges(nbn_MR_new+1,bn_MR_new_tmp);
	
			} else if (region==Region::SR_Lepjet_1V_24j) {
				nbn_MR = 8;
				Double_t bn_MR_tmp[] = {0, 100, 200, 300, 400, 500, 600, 700, 3000};
				bn_MR = getVariableBinEdges(nbn_MR+1,bn_MR_tmp);
				nbn_MR_new = 10;
				Double_t bn_MR_new_tmp[] = {0, 30, 40, 50, 75, 100, 150, 200, 250, 300, 3000};
				bn_MR_new = getVariableBinEdges(nbn_MR_new+1,bn_MR_new_tmp);
	
			} else if (region==Region::SR_Lepjet_1V_5j) {
				nbn_MR = 7;
				Double_t bn_MR_tmp[] = {0, 100, 200, 300, 400, 500, 600, 3000};
				bn_MR = getVariableBinEdges(nbn_MR+1,bn_MR_tmp);
				nbn_MR_new = 8;
				Double_t bn_MR_new_tmp[] = {0, 30, 40, 50, 75, 100, 150, 200, 3000};
				bn_MR_new = getVariableBinEdges(nbn_MR_new+1,bn_MR_new_tmp);
			}
			std::string regionname(magic_enum::enum_name(region));

			std::string name  = std::string("MRR2_S_signal")+"_"+regionname+"_"+massbin.second;
			std::string title = std::string("MRR2_S_signal")+" "+regionname+" "+massbin.second+";M_{R} #times R^{2} (GeV);Systematic variations";
			vh.push_back(new TH2D(name.c_str(), title.c_str(), nbn_MR,bn_MR, 1+syst_nSyst,-0.5,syst_nSyst+0.5));
			name  = std::string("MRR2_S_signal")+"_"+regionname+"_new_"+massbin.second;
			title = std::string("MRR2_S_signal")+" "+regionname+"_new "+massbin.second+";M_{R} #times R^{2} (GeV);Systematic variations";
			vh_new.push_back(new TH2D(name.c_str(), title.c_str(), nbn_MR_new, bn_MR_new, 1+syst_nSyst,-0.5,syst_nSyst+0.5));
		} // For loops of SR regions
		m_vh_signal.insert({massbin.first, vh});
		m_vh_signal_new.insert({massbin.first, vh_new});
	} // For loop of massbins
}

	void
PlottingBase::fill_analysis_histos(EventSelections& evt_sel, const Weighting& w, const unsigned int& syst_index, const double& weight)
{
	// SmartHistos
	if (syst_index == 0) { // Default (no systematic variation)
		//__________________________________ 
		//         Fill Smarthistos
		//__________________________________
		while(v.Electron.Loop())                                           sh.Fill("ele");
		while(v.Electron.Loop()) if (v.Electron.Select.pass[v.Electron.i]) sh.Fill("ele select");
		while(v.Electron.Loop()) if (v.Electron.Veto.  pass[v.Electron.i]) sh.Fill("ele veto");
		while(v.Electron.Loop()) if (v.Electron.NoIso. pass[v.Electron.i]) sh.Fill("ele tight noiso");
		while(v.Muon.Loop())                                       sh.Fill("mu");
		while(v.Muon.Loop())     if (v.Muon.Select.pass[v.Muon.i]) sh.Fill("mu select");
		while(v.Muon.Loop())     if (v.Muon.Veto.  pass[v.Muon.i]) sh.Fill("mu veto");
		while(v.Muon.Loop())     if (v.Muon.NoIso. pass[v.Muon.i]) sh.Fill("mu tight noiso");
		while(v.Tau.Loop())      if (v.Tau.Veto.   pass[v.Tau.i])  sh.Fill("tau veto");
		while(v.Photon.Loop())   if (v.Photon.Select.   pass[v.Photon.i]) sh.Fill("pho");
		while(v.Photon.Loop())   if (v.Photon.PreSelect.pass[v.Photon.i]) sh.Fill("prepho");
		while(v.Jet.Loop())      if (v.Jet.Jet.       pass[v.Jet.i]) sh.Fill("AK4");
		while(v.Jet.Loop())      if (v.Jet.MediumBTag.pass[v.Jet.i]) sh.Fill("b");
		while(v.Jet.Loop())      if (v.Jet.LooseBTag. pass[v.Jet.i]) sh.Fill("b loose");
		for (v.iMegaJet=0; v.iMegaJet<v.megajets.size(); ++v.iMegaJet) sh.Fill("megajet");
		while(v.FatJet.Loop())   if (v.FatJet.JetAK8.pass[v.FatJet.i]) sh.Fill("AK8");
		while(v.FatJet.Loop())   if (v.FatJet.JetAK8Mass.pass[v.FatJet.i]) sh.Fill("AK8Mass");
		while(v.FatJet.Loop())   if (v.FatJet.HadW.  pass[v.FatJet.i]) sh.Fill("hadw");
		while(v.FatJet.Loop())   if (v.FatJet.HadZ.  pass[v.FatJet.i]) sh.Fill("hadz");
		while(v.FatJet.Loop())   if (v.FatJet.HadH.  pass[v.FatJet.i]) sh.Fill("hadh");
		while(v.FatJet.Loop())   if (v.FatJet.HadTop.pass[v.FatJet.i]) sh.Fill("hadtop");
		while(v.FatJet.Loop())   if (v.FatJet.LepTop.pass[v.FatJet.i]) sh.Fill("leptop");
		while(v.FatJet.Loop())   if (v.FatJet.LepJet.pass[v.FatJet.i]) sh.Fill("lepjet");
		if (!v.isData) {
			while(v.GenPart.Loop())  if (v.GenPart.Lepton.pass[v.GenPart.i])  sh.Fill("gen lep");
			while(v.GenPart.Loop())  if (v.GenPart.Ele.   pass[v.GenPart.i])  sh.Fill("gen ele");
			while(v.GenPart.Loop())  if (v.GenPart.Mu.    pass[v.GenPart.i])  sh.Fill("gen mu");
			while(v.GenPart.Loop())  if (v.GenPart.HadW.  pass[v.GenPart.i])  sh.Fill("gen hadW");
			while(v.GenPart.Loop())  if (v.GenPart.HadZ.  pass[v.GenPart.i])  sh.Fill("gen hadZ");
			while(v.GenPart.Loop())  if (v.GenPart.HadZ.  pass[v.GenPart.i] || v.GenPart.HadW.  pass[v.GenPart.i])  sh.Fill("gen hadV");
			while(v.GenPart.Loop())  if (v.GenPart.HadH.  pass[v.GenPart.i])  sh.Fill("gen hadH");
			while(v.GenPart.Loop())  if (v.GenPart.Top.   pass[v.GenPart.i])  sh.Fill("gen top");
			while(v.GenPart.Loop())  if (v.GenPart.HadTop.pass[v.GenPart.i])  sh.Fill("gen hadtop");
			while(v.GenPart.Loop())  if (v.GenPart.LepTop.pass[v.GenPart.i])  sh.Fill("gen leptop");
		}
		sh.Fill("evt");

	}

	// Do the same for systematics plots:
	while(v.Electron.Loop())                                           sh.Fill("syst ele");
	while(v.Electron.Loop()) if (v.Electron.Select.pass[v.Electron.i]) sh.Fill("syst ele select");
	while(v.Electron.Loop()) if (v.Electron.Veto.  pass[v.Electron.i]) sh.Fill("syst ele veto");
	while(v.Electron.Loop()) if (v.Electron.NoIso. pass[v.Electron.i]) sh.Fill("syst ele tight noiso");
	while(v.Muon.Loop())                                       sh.Fill("syst mu");
	while(v.Muon.Loop())     if (v.Muon.Select.pass[v.Muon.i]) sh.Fill("syst mu select");
	while(v.Muon.Loop())     if (v.Muon.Veto.  pass[v.Muon.i]) sh.Fill("syst mu veto");
	while(v.Muon.Loop())     if (v.Muon.NoIso. pass[v.Muon.i]) sh.Fill("syst mu tight noiso");
	while(v.Tau.Loop())      if (v.Tau.Veto.   pass[v.Tau.i])  sh.Fill("syst tau veto");
	while(v.Photon.Loop())   if (v.Photon.Select.   pass[v.Photon.i]) sh.Fill("syst pho");
	while(v.Photon.Loop())   if (v.Photon.PreSelect.pass[v.Photon.i]) sh.Fill("syst prepho");
	while(v.Jet.Loop())      if (v.Jet.Jet.       pass[v.Jet.i]) sh.Fill("syst AK4");
	while(v.Jet.Loop())      if (v.Jet.MediumBTag.pass[v.Jet.i]) sh.Fill("syst b");
	while(v.Jet.Loop())      if (v.Jet.LooseBTag. pass[v.Jet.i]) sh.Fill("syst b loose");
	for (v.iMegaJet=0; v.iMegaJet<2; ++v.iMegaJet) sh.Fill("syst megajet");
	while(v.FatJet.Loop())   if (v.FatJet.JetAK8.pass[v.FatJet.i]) sh.Fill("syst AK8");
	while(v.FatJet.Loop())   if (v.FatJet.HadW.  pass[v.FatJet.i]) sh.Fill("syst hadw");
	while(v.FatJet.Loop())   if (v.FatJet.HadZ.  pass[v.FatJet.i]) sh.Fill("syst hadz");
	while(v.FatJet.Loop())   if (v.FatJet.HadH.  pass[v.FatJet.i]) sh.Fill("syst hadh");
	while(v.FatJet.Loop())   if (v.FatJet.HadTop.pass[v.FatJet.i]) sh.Fill("syst hadtop");
	while(v.FatJet.Loop())   if (v.FatJet.LepTop.pass[v.FatJet.i]) sh.Fill("syst leptop");
	while(v.FatJet.Loop())   if (v.FatJet.LepJet.pass[v.FatJet.i]) sh.Fill("syst lepjet");
	sh.Fill("syst evt");

	if (v.isSignal) {
	  int binx = w.vh_weightnorm_signal[v.signal_index]->GetXaxis()->FindBin(v.susy_mass[0]);
	  int biny = w.vh_weightnorm_signal[v.signal_index]->GetYaxis()->FindBin(v.susy_mass[1]);
	  double mMother = w.vh_weightnorm_signal[v.signal_index]->GetXaxis()->GetBinCenter(binx);
	  double mLSP    = w.vh_weightnorm_signal[v.signal_index]->GetYaxis()->GetBinCenter(biny);
	  uint32_t massbin = mMother * 10000 + mLSP;
	  if (m_vh_signal.count(massbin)) {
	    const auto& vh_signal = m_vh_signal[massbin];
	    const auto& vh_signal_new = m_vh_signal_new[massbin];
	    const auto& vh_signal_binopt = m_vh_signal_binopt[massbin];
	    const auto& vh_signal_new_binopt = m_vh_signal_new_binopt[massbin];
	    for (const auto& region : magic_enum::enum_values<Region>()) {
				if (region<Region::SR_Had_1htop || region>Region::SR_Lepjet_1V_5j) continue;
	      if (evt_sel.apply_all_cuts(region)) vh_signal[region-Region::SR_Had_1htop]->Fill(v.MR*v.R2, syst_index, w.sf_weight[region]);
	      if (evt_sel.apply_all_cuts(region)) vh_signal_new[region-Region::SR_Had_1htop]->Fill((v.MR-800)*(v.R2-0.08), syst_index, w.sf_weight[region]);
	      if (evt_sel.apply_all_cuts(region)) vh_signal_binopt[region-Region::SR_Had_1htop]->Fill(v.MR*v.R2, syst_index, w.sf_weight[region]);
	      if (evt_sel.apply_all_cuts(region)) vh_signal_new_binopt[region-Region::SR_Had_1htop]->Fill((v.MR-800)*(v.R2-0.08), syst_index, w.sf_weight[region]);
	    }
	  }
	}

	// Background
	if (!v.isSignal&&!v.isData) {
		for (const auto& region : magic_enum::enum_values<Region>()) {
			if (region<Region::SR_Had_1htop || region>Region::SR_Lepjet_1V_5j) continue;
			if (evt_sel.apply_all_cuts(region)) vvh_MRR2_bkg[region-Region::SR_Had_1htop]->Fill(v.MR*v.R2, syst_index, w.sf_weight[region]);
			if (evt_sel.apply_all_cuts(region)) vvh_MRR2_bkg_new[region-Region::SR_Had_1htop]->Fill((v.MR-800)*(v.R2-0.08), syst_index, w.sf_weight[region]);
			if (evt_sel.apply_all_cuts(region)) vvh_MRR2_bkg_binopt[region-Region::SR_Had_1htop]->Fill(v.MR*v.R2, syst_index, w.sf_weight[region]);
			if (evt_sel.apply_all_cuts(region)) vvh_MRR2_bkg_new_binopt[region-Region::SR_Had_1htop]->Fill((v.MR-800)*(v.R2-0.08), syst_index, w.sf_weight[region]);
		} 
	}
	//Data
	if (v.isData) {
		for (const auto& region : magic_enum::enum_values<Region>()) {
			if (region<Region::SR_Had_1htop || region>Region::SR_Lepjet_1V_5j) continue;
			if (evt_sel.apply_all_cuts(region)) vvh_MRR2_data[region-Region::SR_Had_1htop]->Fill(v.MR*v.R2, w.sf_weight[region]);
			if (evt_sel.apply_all_cuts(region)) vvh_MRR2_data_new[region-Region::SR_Had_1htop]->Fill((v.MR-800)*(v.R2-0.08), w.sf_weight[region]);
			if (evt_sel.apply_all_cuts(region)) vvh_MRR2_data_binopt[region-Region::SR_Had_1htop]->Fill(v.MR*v.R2, w.sf_weight[region]);
			if (evt_sel.apply_all_cuts(region)) vvh_MRR2_data_new_binopt[region-Region::SR_Had_1htop]->Fill((v.MR-800)*(v.R2-0.08), w.sf_weight[region]);
		} 
	}

}


	void
PlottingBase::load_analysis_histos(std::string inputfile)
{
	sh.Add(inputfile.c_str());
}

	void
PlottingBase::save_analysis_histos(bool draw=0)
{
	if (draw) sh.DrawPlots();
	else sh.Write();

	gDirectory->mkdir("Signal");
	gDirectory->cd("Signal");
	for (const auto& vh : m_vh_signal)
		for (const auto& h : vh.second) h->Write(h->GetName());
	for (const auto& vh : m_vh_signal_new)
		for (const auto& h : vh.second) h->Write(h->GetName());
	gDirectory->cd("..");
	gDirectory->mkdir("Background");
	gDirectory->cd("Background");
	for (const auto& h2 : vvh_MRR2_bkg) h2->Write(h2->GetName());
	for (const auto& h2 : vvh_MRR2_bkg_new) h2->Write(h2->GetName());
	gDirectory->cd("..");
	gDirectory->mkdir("Data");
	gDirectory->cd("Data");
	for (const auto& h3 : vvh_MRR2_data) h3->Write(h3->GetName());
	for (const auto& h3 : vvh_MRR2_data_new) h3->Write(h3->GetName());
	gDirectory->cd("..");
	gDirectory->mkdir("BinOpt");
	gDirectory->cd("BinOpt");
	for (const auto& h3 : vvh_MRR2_data_binopt) h3->Write(h3->GetName());
	for (const auto& h3 : vvh_MRR2_data_new_binopt) h3->Write(h3->GetName());
	for (const auto& h2 : vvh_MRR2_bkg_binopt) h2->Write(h2->GetName());
	for (const auto& h2 : vvh_MRR2_bkg_new_binopt) h2->Write(h2->GetName());
	for (const auto& vh : m_vh_signal_binopt)
		for (const auto& h : vh.second) h->Write(h->GetName());
	for (const auto& vh : m_vh_signal_new_binopt)
		for (const auto& h : vh.second) h->Write(h->GetName());
	gDirectory->cd("..");


}

#endif // End header guard
