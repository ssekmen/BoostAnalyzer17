#ifndef PLOTTING_H
#define PLOTTING_H
#include "include/Analysis.h"

//_______________________________________________________
//                  Calculate variables


//_______________________________________________________
//      Define Histo options: Filling/Postfixes

void
Plotting::define_additional_histo_settings(const Weighting& w, EventSelections& evt_sel,
                                           const unsigned int& syst_nSyst, const unsigned int& syst_index)
{
  
}

//_______________________________________________________
//              Define Histograms here
void
Plotting::define_additional_histos(const Weighting& w, const unsigned int& syst_nSyst, const unsigned int& syst_index) {


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

  // Systematics:

  // The systematics of the plot are hidden in an additional dimension added to the histogram
  // eg.  a TH1D and it's systematic variations are stored in a TH2D
  // Each extra dimensional bin contain a variation of the underlying distribution
  // To enable this, a special dummy axis needs to be added which is called "Counts"
  // The string "Counts_vs_" is added to the plot name
  // and the "syst " is attached to the histogram type so the code knows to fill this
  // additional axis

  
  bool systematics = 1;
  
  std::string s = "";
  std::string c = "";
  if (systematics) {
    s = "syst ";
    c = "Counts_vs_";
  }

  std::vector<std::string> standard_plots = {"HT", "HTFine", "METFine", "MET", "HTMET", "MRFine", "MR", "R2Fine", "R2", "MRR2"};

  	// CONTROL and VALIDATION REGIONS
    standard_plots = {"HT", "METFine", "MET", "MRFine", "MR", "R2Fine", "R2", "MRR2", "RazorBins", "RazorBinsNew", "JetPt", "JetEta", "JetPhi", "MegaJetPt", "MegaJetEta", "MegaJetPhi", "NJet", "NjetNoPho", "NJetAK8", "NBTag", "NLooseBTag", "NTightBTag"};
    for (auto region : {Region::Pre, 
  					  Region::CR_Top16_W, 
  					  Region::CR_W16_W, 
  					  Region::CR_QCD16_W, 
  					  Region::CR_Top16_Top, 
  					  Region::CR_W16_Top, 
  					  Region::CR_QCD16_Top, 
  					  Region::CR_Top16_Z, 
  					  Region::CR_W16_Z, 
  					  Region::CR_QCD16_Z, 
  					  Region::CR_Top16_V, 
  					  Region::CR_W16_V, 
  					  Region::CR_QCD16_V, 
  					  Region::CR_Top17_1Boost, 
  					  Region::CR_W17_1Boost, 
  					  Region::CR_QCD17_1Boost, 
  					  Region::CR_Top17_2Boost, 
  					  Region::CR_W17_2Boost, 
  					  Region::CR_QCD17_2Boost, 
  					  Region::CR_1LepInv, 
  					  Region::CR_2LepInv, 
  					  Region::CR_1PhoInv, 
  					  Region::CR_Fake, 
  					  Region::Val_Signal, 
  					  Region::Val_QCD}) {

    	sh.SetHistoWeights({ [&w,region] { return w.sf_weight[region]; } });
    	std::string cut(magic_enum::enum_name(region));
    	std::vector<std::string> showdata = {"JetHTMET"};
    	for (auto data : showdata ) {
    		std::string opt = (data=="Blind") ? o_stk_s : o_stk_d;
	
    		for (auto std_plot : standard_plots)
    		sh.AddHistos("evt", { .fill=c+std_plot,   .pfs={Stack,data,cut},  .cuts={}, .draw=d, .opt=opt, .ranges=r_Stk6});
		
		}	
    }

    // FULLY HADRONIC SIGNAL REGIONS
    for (auto region : {Region::SR_Had_1htop, 
  				Region::SR_Had_2htop, 
  				Region::SR_Had_V_b_45j, 
  				Region::SR_Had_V_b_6j, 
  				Region::SR_Had_1V_0b_34j, 
  				Region::SR_Had_1V_0b_5j, 
  				Region::SR_Had_2V_0b_24j, 
  				Region::SR_Had_2V_0b_5j, 
           			Region::SR_Had_H_b_45j, 
           			Region::SR_Had_H_b_6j, 
           			Region::SR_Had_2H_b_6j, 
           			Region::SR_Had_HV_b_6j, 
           			Region::SR_Had_1H_0b_34j, 
           			Region::SR_Had_1H_0b_5j, 
           			Region::SR_Had_2H_0b_34j, 
           			Region::SR_Had_2H_0b_5j, 
           			Region::SR_Had_HV_0b_24j, 
           			Region::SR_Had_HV_0b_5j}) {

    	sh.SetHistoWeights({ [&w,region] { return w.sf_weight[region]*137.0/41.529; } });
    	std::string cut(magic_enum::enum_name(region));
    	std::vector<std::string> showdata = {"Blind"};

    	    for (auto data : showdata ) {
      			std::string signal = "StackPlotSignal";
      			std::string opt  = (data=="Blind") ? o_stk_s_S : o_stk_d_S;
      			if (region==Region::SR_Had_1htop||region==Region::SR_Had_2htop||region==Region::SR_Had_V_b_45j||region==Region::SR_Had_V_b_6j) {
        			opt    = (data=="Blind") ? o_stk_s_T : o_stk_d_T;
        			signal = "StackPlotTopSignal";
      			} else if (region==Region::SR_Had_1V_0b_34j||region==Region::SR_Had_1V_0b_5j||region==Region::SR_Had_2V_0b_24j||region==Region::SR_Had_2V_0b_5j) {
       				opt    = (data=="Blind") ? o_stk_s_V : o_stk_d_V;
        			signal = "StackPlotVSignal";
      			} else if (region==Region::SR_Had_H_b_45j||region==Region::SR_Had_H_b_6j||region==Region::SR_Had_2H_b_6j||region==Region::SR_Had_HV_b_6j||
     	            		   region==Region::SR_Had_1H_0b_34j||region==Region::SR_Had_1H_0b_5j||region==Region::SR_Had_2H_0b_34j||region==Region::SR_Had_2H_0b_5j||
        	       		   region==Region::SR_Had_HV_0b_24j||region==Region::SR_Had_HV_0b_5j) {
        			opt    = (data=="Blind") ? o_stk_s_H : o_stk_d_H;
        			signal = "StackPlotHSignal";
      			}
      
      			for (auto std_plot : standard_plots)
      			sh.AddHistos(s+"evt", { .fill=c+std_plot,              .pfs={signal,data,cut},               .cuts={},.draw=d,.opt=opt,.ranges=r_Stk5});
      
    		}		

    }

    // ISOLATED LEPTON SIGNAL REGIONS
  	for (auto region : {Region::SR_Lep_1htop, 
  					  	Region::SR_Lep_V_b, 
  					  	Region::SR_Lep_V_0b, 
  					  	Region::SR_Lep_H_b, 
  					  	Region::SR_Lep_H_0b}) {

  	sh.SetHistoWeights({ [&w,region] { return w.sf_weight[region]*137.0/41.529; } });
    	std::string cut(magic_enum::enum_name(region));
    	std::vector<std::string> showdata = {"Blind"};

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
			sh.AddHistos(s+"evt", { .fill=c+std_plot,     .pfs={signal,data,cut},    .cuts={},.draw=d,.opt=opt,.ranges=r_Stk8});
      
    	}
  	}

  	// NON-ISOLATED SIGNAL REGIONS
  	for (auto region : {Region::SR_Leptop_0htop, 
  			    Region::SR_Leptop_1htop, 
  			    Region::SR_Lepjet_0V_24j, 
  			    Region::SR_Lepjet_0V_5j, 
  			    Region::SR_Lepjet_1V_24j, 
  			    Region::SR_Lepjet_1V_5j}) {

  	sh.SetHistoWeights({ [&w,region] { return w.sf_weight[region]*137.0/41.529; } });
    	std::string cut(magic_enum::enum_name(region));
    	std::vector<std::string> showdata = {"Blind"};

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
      		sh.AddHistos(  s+"evt", { .fill=c+std_plot,     .pfs={signal,data,cut},     .cuts={},.draw=d,.opt=opt,.ranges=r_Stk8});

    	}
  	}

}

#endif // End header guard
