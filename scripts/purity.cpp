#include "CMS_lumi.C"

pair<double, double> PurityFit(TH1D* chisoFake, TH1D* chisoPrompt, TH1D* chiso, string EBEE, string MRR2Bin){
	TH1::SetDefaultSumw2();

	gStyle->SetOptStat(000);
	TCanvas* C0 = new TCanvas("C0", "FractionFitter example", 700, 700);

	TObjArray *mc;
	TFractionFitter* fit;
	TH1F* result;
	double purity=0, error=0;
	mc = new TObjArray(2);
	mc->Add(chisoFake);
	mc->Add(chisoPrompt);
	fit = new TFractionFitter(chiso,mc);
	fit->Constrain(0,0.,0.5);
	fit->Constrain(1,0.5,1.);
	double prompt_value=0., prompt_error=0., fake_value=0., fake_error=0.;
	int status = fit->Fit();
	
	C0->cd();
	auto leg = new TLegend(0.65,0.55,0.85,0.75);
	C0->SetLogy();
	TLatex l1, l2;
	l1.SetTextSize(.035);
	l2.SetTextSize(.035);
	Char_t texte1[200];
	Char_t texte2[200];
	if(status == 0){
		result = (TH1F*)fit->GetPlot();
		fit->GetResult(0, fake_value, fake_error);
		fit->GetResult(1, prompt_value, prompt_error);

		//cout << "prmpt : " << prompt_value << " fake_value : " << fake_value << endl;
		purity = (prompt_value/(prompt_value+fake_value));
		double temp = TMath::Power(fake_value,2)/(TMath::Power(fake_value,2) + TMath::Power(prompt_value,2));
		cout << "purity ---->" <<purity << "           error------->  " << error <<endl;
		error = TMath::Sqrt(temp*(TMath::Power(prompt_error,2)+TMath::Power(fake_error,2)));
		
		chisoPrompt->Scale(prompt_value*result->Integral()/chisoPrompt->Integral());
		chisoFake->Scale(fake_value*result->Integral()/chisoFake->Integral());

		//auto hs1 = new THStack("hs1","CMS #scale[0.7]{#font[52]{Work in progress 2017}}       #scale[0.7]{41.5 fb^{-1} (13 TeV)}");

		auto hs1 = new THStack("hs1","");		

		//chisoPrompt->Draw("SAME HIST");
		chisoFake->SetFillStyle(1001);
		chisoFake->SetFillColor(2);
		chisoFake->GetXaxis()->SetTitle("Photon Charged Isolation GeV");
		hs1->Add(chisoFake);
		chisoPrompt->SetLineStyle(1001);
		chisoPrompt->SetFillColor(8);
		//chisoPrompt->GetXaxis()->SetTitle("Photon Charged Isolation GeV");
		//chisoPrompt->SetFillWidth(8);
		hs1->Add(chisoPrompt);
		chiso->GetXaxis()->SetTitle("Photon Charged Isolation GeV");
		chiso->GetYaxis()->SetTitle("Photons - Barrel");
		chiso->SetMarkerStyle(20);
		hs1->Draw("HIST");
		chiso->Draw("SAME PE0");
		result->Draw("SAME");
		sprintf( texte1, "purity %.2f, error %.4f ", purity, error);
		sprintf(texte2, "MR*R2 Bin: %s - %s ", EBEE.c_str(), MRR2Bin.c_str());
		l1.DrawTextNDC( .45, .50, texte1);
		l2.DrawTextNDC( .37, .77, texte2);

		leg->SetTextSize(0.03);
		leg->AddEntry(chiso, "Data", "lep");
		leg->AddEntry(result, "Fit", "l");
		leg->AddEntry(chisoPrompt, "Prompt");
		leg->AddEntry(chisoFake,"Fake");
		leg->Draw();		
	}
	CMS_lumi(C0, 2, 1);
	C0->SaveAs(Form("Plot2017_September_preselectphotonpt_g/Fraction_Test_%s_%s.pdf", EBEE.c_str(), MRR2Bin.c_str()), "recreate");	
	
  TFile* f1 = new TFile("./Plot2017_September_preselectphotonpt_g/test.root", "update");
  C0->Write();
  result->Write();
  f1->Close();
  C0->Close();
  cout << purity << ", " << error << endl;
	return make_pair(purity,error);
}

pair<TH1D*, TH1D*> Purity2D(TFile* data, TFile* mc){
	TH1::SetDefaultSumw2();
	//template - fake
	TH2D* htemp0_EB = (TH2D*)data->Get(Form("MRR2NoPho_vs_PhotonCHIso_preslectphopt/Data_FailSIEIE_Barrel_2017_CR_1PhoInv_g")); 	//Barrel
	TH2D* htemp0_EE = (TH2D*)data->Get(Form("MRR2NoPho_vs_PhotonCHIso_preslectphopt/Data_FailSIEIE_Endcap_2017_CR_1PhoInv_g")); 	//Endcap
	TH2D* htemp1_EB = (TH2D*)mc->Get(Form("MRR2NoPho_vs_PhotonCHIso_preslectphopt/MC_FailSIEIE_Barrel_2017_CR_1PhoInv_g"));	//Barrel
	TH2D* htemp1_EE = (TH2D*)mc->Get(Form("MRR2NoPho_vs_PhotonCHIso_preslectphopt/MC_FailSIEIE_Endcap_2017_CR_1PhoInv_g"));	//Barrel
	//template - prompt
	TH2D* htemp2_EB = (TH2D*)mc->Get(Form("MRR2NoPho_vs_PhotonCHIso_preslectphopt/MC_PassSIEIE_Barrel_2017_CR_1PhoInv_g"));	//Barrel
	TH2D* htemp2_EE = (TH2D*)mc->Get(Form("MRR2NoPho_vs_PhotonCHIso_preslectphopt/MC_PassSIEIE_Endcap_2017_CR_1PhoInv_g"));	//Endcap
	//fitting target
	TH2D* htemp3_EB = (TH2D*)data->Get(Form("MRR2NoPho_vs_PhotonCHIso_preslectphopt/Data_PassSIEIE_Barrel_2017_CR_1PhoInv_g"));	//Barrel (Template)
	TH2D* htemp3_EE = (TH2D*)data->Get(Form("MRR2NoPho_vs_PhotonCHIso_preslectphopt/Data_PassSIEIE_Endcap_2017_CR_1PhoInv_g"));	//Endcap (Template)

	std::vector<TH1D*> chisoFake_R2_EB;
	std::vector<TH1D*> chisoFakeMC_R2_EB;
	std::vector<TH1D*> chisoPrompt_R2_EB;
	std::vector<TH1D*> chiso_R2_EB;

	std::vector<TH1D*> chisoFake_R2_EE;
	std::vector<TH1D*> chisoFakeMC_R2_EE;
	std::vector<TH1D*> chisoPrompt_R2_EE;
	std::vector<TH1D*> chiso_R2_EE;

	for(int i=1;i<=htemp0_EB->GetNbinsY();i++){
	//Barrel	
	    chisoFake_R2_EB.push_back(new TH1D((std::string("chisoFake_R2_EB_"+to_string(i))).c_str(), "", 20,0,20));
	    chisoFakeMC_R2_EB.push_back(new TH1D((std::string("chisoFakeMC_R2_EB_"+to_string(i))).c_str(), "", 20,0,20));
	    chisoPrompt_R2_EB.push_back(new TH1D((std::string("chisoPrompt_R2_EB_"+to_string(i))).c_str(), "", 20,0,20));
	    chiso_R2_EB.push_back(new TH1D((std::string("chiso_R2_EB_"+to_string(i))).c_str(), "", 20,0,20));
	    //Endcap
	    chisoFake_R2_EE.push_back(new TH1D((std::string("chisoFake_R2_EE_"+to_string(i))).c_str(), "", 20,0,20));
	    chisoFakeMC_R2_EE.push_back(new TH1D((std::string("chisoFakeMC_R2_EE_"+to_string(i))).c_str(), "", 20,0,20));
	    chisoPrompt_R2_EE.push_back(new TH1D((std::string("chisoPrompt_R2_EE_"+to_string(i))).c_str(), "", 20,0,20));
	    chiso_R2_EE.push_back(new TH1D((std::string("chiso_R2_EE_"+to_string(i))).c_str(), "", 20,0,20));
	}
	
	cout << "Bins of fake X  " << htemp0_EB->GetNbinsX()<< endl;
	cout << "Bins of fake Y  " << htemp0_EB->GetNbinsY()<< endl;

	for(int i=1;i<=htemp0_EB->GetNbinsY();i++){ 							// 5 bins from MR*R2
	   for(int j=1;j<=htemp0_EB->GetNbinsX();j++){							// 20 bins from Chiso
	      // Barrel	
	      chisoFake_R2_EB[i-1]->SetBinContent(j,htemp0_EB->GetBinContent(j,i));
	      chisoFake_R2_EB[i-1]->SetBinError(j,htemp0_EB->GetBinError(j,i));

	      chisoFakeMC_R2_EB[i-1]->SetBinContent(j,htemp1_EB->GetBinContent(j,i));
	      chisoFakeMC_R2_EB[i-1]->SetBinError(j,htemp1_EB->GetBinError(j,i));

	      chisoPrompt_R2_EB[i-1]->SetBinContent(j,htemp2_EB->GetBinContent(j,i));
	      chisoPrompt_R2_EB[i-1]->SetBinError(j,htemp2_EB->GetBinError(j,i));

	      chiso_R2_EB[i-1]->SetBinContent(j,htemp3_EB->GetBinContent(j,i));
	      chiso_R2_EB[i-1]->SetBinError(j,htemp3_EB->GetBinError(j,i));

	      // Endcap 
	      chisoFake_R2_EE[i-1]->SetBinContent(j,htemp0_EE->GetBinContent(j,i));
	      chisoFake_R2_EE[i-1]->SetBinError(j,htemp0_EE->GetBinError(j,i));

	      chisoFakeMC_R2_EE[i-1]->SetBinContent(j,htemp1_EE->GetBinContent(j,i));
	      chisoFakeMC_R2_EE[i-1]->SetBinError(j,htemp1_EE->GetBinError(j,i));

	      chisoPrompt_R2_EE[i-1]->SetBinContent(j,htemp2_EE->GetBinContent(j,i));
	      chisoPrompt_R2_EE[i-1]->SetBinError(j,htemp2_EE->GetBinError(j,i));

	      chiso_R2_EE[i-1]->SetBinContent(j,htemp3_EE->GetBinContent(j,i));
	      chiso_R2_EE[i-1]->SetBinError(j,htemp3_EE->GetBinError(j,i));

	  //cout << "Bin content "<<i << " " << j << "  "<< htemp0_EB->GetBinContent(j,i)<< endl;
   	  }  
  	}

  	//std::vector<TH1D*> TemplateFit;
	std::vector<double> purity_R2_EB;
	std::vector<double> purity_R2_EE;
	std::vector<double> purity_R2_EB_MC;
	std::vector<double> purity_R2_EE_MC;
	std::vector<double> error_R2_EB;
	std::vector<double> error_R2_EE;
	std::vector<double> error_R2_EB_MC;
	std::vector<double> error_R2_EE_MC;
	pair<double, double> result;

	string MRR2Bins[5] = {"0-100", "100-200", "200-300", "300-400", "400-3000"};
	string EBEEs[2] = {"EB", "EE"};
  	cout << "Chiso Fit" << endl;
  	cout << "Size " << chisoFake_R2_EB.size() << endl;
	for(int i=0; i<chisoFake_R2_EB.size(); ++i){

		result = PurityFit(chisoFakeMC_R2_EB[i], chisoPrompt_R2_EB[i], chiso_R2_EB[i],EBEEs[0], MRR2Bins[i]);
		purity_R2_EB_MC.push_back(result.first); error_R2_EB_MC.push_back(result.second);

		result = PurityFit(chisoFake_R2_EB[i], chisoPrompt_R2_EB[i], chiso_R2_EB[i], EBEEs[0], MRR2Bins[i]);
		purity_R2_EB.push_back(result.first); error_R2_EB.push_back(result.second);

		result = PurityFit(chisoFakeMC_R2_EE[i], chisoPrompt_R2_EE[i], chiso_R2_EE[i], EBEEs[1], MRR2Bins[i]);
		purity_R2_EE_MC.push_back(result.first); error_R2_EE_MC.push_back(result.second);

		result = PurityFit(chisoFake_R2_EE[i], chisoPrompt_R2_EE[i], chiso_R2_EE[i], EBEEs[1], MRR2Bins[i]);
		purity_R2_EE.push_back(result.first); error_R2_EE.push_back(result.second);

	}

	//result = PurityFit(chisoFakeMC_R2_EB[4], chisoPrompt_R2_EB[4], chiso_R2_EB[4]);

  cout << "end Fit" << endl;

	TH1D* hist_R2_EB = new TH1D("hist_R2_EB", ";M_{R}*R^{2} (GeV);Photon purity", 5, 0, 5.5);
	TH1D* hist_R2_EE = new TH1D("hist_R2_EE", "", 5, 0, 5.5);
	TH1D* hist_R2_EB_MC = new TH1D("hist_R2_EB_MC", "", 5, 0, 5.5);
	TH1D* hist_R2_EE_MC = new TH1D("hist_R2_EE_MC", "", 5, 0, 5.5);

	for(int i=1;i<=5;i++){
		hist_R2_EB->SetBinContent(i,purity_R2_EB[i-1]);
		hist_R2_EB->SetBinError(i,error_R2_EB[i-1]);
		hist_R2_EB_MC->SetBinContent(i,purity_R2_EB_MC[i-1]);
		hist_R2_EB_MC->SetBinError(i,error_R2_EB_MC[i-1]);
		hist_R2_EE->SetBinContent(i,purity_R2_EE[i-1]);
		hist_R2_EE->SetBinError(i,error_R2_EE[i-1]);
		hist_R2_EE_MC->SetBinContent(i,purity_R2_EE_MC[i-1]);
		hist_R2_EE_MC->SetBinError(i,error_R2_EE_MC[i-1]);
	}

	TCanvas* C1 = new TCanvas("C1", "Purity Results", 700, 700);
	C1->cd();
	hist_R2_EB->GetXaxis()->SetNdivisions(505);
	hist_R2_EB->GetYaxis()->SetRangeUser(0.45,2);
	for(int i=1; i<=5; i++) hist_R2_EB->GetXaxis()->SetBinLabel(i, MRR2Bins[i-1].c_str());
	hist_R2_EB->GetXaxis()->SetLabelSize(0.05);
	hist_R2_EB->GetXaxis()->SetTitleOffset(1);
	hist_R2_EB->Draw("PE");
	hist_R2_EE->SetLineColor(2);
	hist_R2_EE->SetMarkerColor(2);
	hist_R2_EB_MC->SetMarkerStyle(25);
	hist_R2_EB_MC->SetMarkerSize (2);
	hist_R2_EE_MC->SetLineColor(2);
	hist_R2_EE_MC->SetMarkerColor(2);
	hist_R2_EE_MC->SetMarkerStyle(25);
	hist_R2_EE_MC->SetMarkerSize (2);
	hist_R2_EE->Draw("SAME PE");
	hist_R2_EB_MC->Draw("SAME PE");
	hist_R2_EE_MC->Draw("SAME PE");

	auto leg = new TLegend(0.38,0.65,0.8,0.8);
	leg->SetNColumns(2);
	leg->SetTextSize(0.04);
	leg->AddEntry(hist_R2_EB,    "Barrel - Data", "LPE");
	leg->AddEntry(hist_R2_EB_MC, "MC",            "PE");
	leg->AddEntry(hist_R2_EE,    "Endcap - Data", "LPE");
	leg->AddEntry(hist_R2_EE_MC, "MC",            "PE");
	leg->SetFillColor(0);
	leg->SetFillStyle(0);
	leg->SetBorderSize(0);
	leg->Draw("SAME");
	CMS_lumi(C1, 2, 1);
	C1->SaveAs(Form("Plot2017_September_preselectphotonpt_g/PurityResults.pdf"), "recreate");

	return make_pair(hist_R2_EB, hist_R2_EE);
}

pair<TH1D*, TH1D*> Fraction(TFile* f1){
	TH1::SetDefaultSumw2();
	TH2D* fraction[2];

	fraction[0] = (TH2D*)f1->Get(Form("DirectFraction_vs_MRR2NoPho/plus1d_Background_Prompt_Endcap_CR_1PhoInv"));
 	fraction[1] = (TH2D*)f1->Get(Form("DirectFraction_vs_MRR2NoPho/plus1d_Background_Prompt_Barrel_CR_1PhoInv"));


   	TH1D* hist_EB = new TH1D("hist_EB", "", 5,0,5);
	TH1D* hist_EE = new TH1D("hist_EE", "", 5,0,5);
    	double frag_EB, prom_EB, frag_EE, prom_EE, bin=1;
    	double frag_EB_e, prom_EB_e, frag_EE_e, prom_EE_e;
	for(int j=1;j<=fraction[0]->GetNbinsX();j++){
			
			frag_EB   = fraction[1]->GetBinContent(j,1);
			frag_EB_e = fraction[1]->GetBinError(j,1);
			prom_EB   = fraction[1]->GetBinContent(j,2);
			prom_EB_e = fraction[1]->GetBinError(j,2);
      			hist_EB->SetBinContent(bin,prom_EB/(prom_EB+frag_EB));
			hist_EB->SetBinError(bin,frag_EB*sqrt(TMath::Power(frag_EB_e,2) + TMath::Power(prom_EB_e,2)));
			cout<< "prom EB   " <<fraction[1]->GetBinContent(j,2) <<endl;
			cout<< "frag EB   " <<fraction[1]->GetBinContent(j,1) <<endl;

			frag_EE = fraction[0]->GetBinContent(j,1);
			frag_EE_e = fraction[0]->GetBinError(j,1);
			prom_EE = fraction[0]->GetBinContent(j,2);
			prom_EE_e = fraction[0]->GetBinError(j,2);
			hist_EE->SetBinContent(bin,prom_EE/(prom_EE+frag_EE));
			hist_EE->SetBinError(bin,frag_EE*sqrt(TMath::Power(frag_EE_e,2) + TMath::Power(prom_EE_e,2)));
      		/*
      		hist_EB->SetBinContent(j,0.6);
			hist_EB->SetBinError(j,0.01);
      		hist_EE->SetBinContent(j,0.6);
			hist_EE->SetBinError(j,0.01);
			*/
      	bin++;
      	cout << hist_EB->GetBinContent(j) << ", " << hist_EE->GetBinContent(j) << endl;
	}

	return make_pair(hist_EB, hist_EE);
}

TH1D* Correction(TH1D* purity_EB, TH1D* purity_EE, TH1D* frac_EB, TH1D* frac_EE, TFile* inputfile){
  //bckgrnd_0gStyle->SetOptStat(0);
  //delete gROOT->FindObject("c1");	
  gStyle->SetOptTitle(0);
  TH1::SetDefaultSumw2();

  //inputfile = TFile::Open("run_08102020.root");

  TH2D* bkg2D[11];

  bkg2D[0] = (TH2D*)inputfile->Get(Form("Counts_vs_MRR2/Syst_vs_MRR2/Data_2017_Endcap_CR_1PhoInv"));
  bkg2D[1] = (TH2D*)inputfile->Get(Form("Counts_vs_MRR2/Syst_vs_MRR2/Data_2017_Barrel_CR_1PhoInv"));
  bkg2D[2] = (TH2D*)inputfile->Get(Form("Counts_vs_MRR2/Syst_vs_MRR2/DYToLL_2017_CR_1PhoInv"));
  bkg2D[3] = (TH2D*)inputfile->Get(Form("Counts_vs_MRR2/Syst_vs_MRR2/Multiboson_2017_CR_1PhoInv"));
  bkg2D[4] = (TH2D*)inputfile->Get(Form("Counts_vs_MRR2/Syst_vs_MRR2/TT_powheg_pythia8_2017_CR_1PhoInv"));
  bkg2D[5] = (TH2D*)inputfile->Get(Form("Counts_vs_MRR2/Syst_vs_MRR2/WToLNu_2017_CR_1PhoInv"));
  bkg2D[6] = (TH2D*)inputfile->Get(Form("Counts_vs_MRR2/Syst_vs_MRR2/ZToNuNu_2017_CR_1PhoInv"));	
  bkg2D[7] = (TH2D*)inputfile->Get(Form("Counts_vs_MRR2/Syst_vs_MRR2/Top_2017_CR_1PhoInv"));	
  bkg2D[8] = (TH2D*)inputfile->Get(Form("Counts_vs_MRR2/Syst_vs_MRR2/GJets_2017_CR_1PhoInv")); //Exclude this from other BG
  bkg2D[9] = (TH2D*)inputfile->Get(Form("Counts_vs_MRR2/Syst_vs_MRR2/Multijet_2017_CR_1PhoInv"));	
  bkg2D[10] = (TH2D*)inputfile->Get(Form("Counts_vs_MRR2/Syst_vs_MRR2/Data_2017_CR_1PhoInv"));	

  int binsize = bkg2D[0]->GetNbinsX();
  double bin[binsize+1];
  //cout << "----------Binsize-------------------->  " << binsize <<endl;
  for(int i=1;i<=bkg2D[0]->GetNbinsX()+1;i++) bin[i-1] = bkg2D[0]->GetXaxis()->GetBinLowEdge(i);
  TH1D* bkg[10]; //1D MR*R2 data and background histograms
  // TH1D* Npromptdirect = new TH1D("promptdirect", ";Prompt Direct (GeV)", 5,0,5);
  string name;

  for (int i = 0; i <11; ++i){		
  	name = "bckgrnd_"+to_string(i);
  	bkg[i] = new TH1D(name.c_str(), "MR*R2 (GeV)", binsize, bin);
  	for (int j = 1; j <= bkg2D[0]->GetNbinsX(); ++j){
  		bkg[i]->SetBinContent(j, bkg2D[i]->GetBinContent(j,1));
  		bkg[i]->SetBinError(j, bkg2D[i]->GetBinError(j,1));  
		
  	}
  }

  //cout <<"----------Size of 1D ---------------------------->  " << bkg[0]->GetNbinsX()<< endl;

  TH1D * h_Npromptdirect = new TH1D("Promptdirect", ";MRR2 (GeV)", binsize ,bin);
  double Npromptdirect[binsize];
  double Npromptdirect_err[binsize];
  
  for (int i = 1; i <= bkg[0]->GetNbinsX(); ++i){

  	double purity_count_EB = purity_EB->GetBinContent(i);
  	double purity_count_EE = purity_EE->GetBinContent(i);
  	double frag_count_EB = frac_EB->GetBinContent(i);
  	double frag_count_EE = frac_EE->GetBinContent(i);
  	//double data_EB = bkg[1]->GetBinContent(i);
  	//double data_EE = bkg[0]->GetBinContent(i);

  	Npromptdirect[i] = purity_count_EB*frag_count_EB;
  	Npromptdirect[i] += purity_count_EE*frag_count_EE;

  	Npromptdirect_err[i] = pow((purity_count_EB*frag_count_EB),2);
  	Npromptdirect_err[i] += pow((purity_count_EE*frag_count_EE),2);

  	Npromptdirect_err[i] = pow((Npromptdirect_err[i]),0.5);

  	h_Npromptdirect->SetBinContent(i,Npromptdirect[i]);
  	h_Npromptdirect->SetBinError(i,Npromptdirect_err[i]);

  	cout << "FractionEB*PurityEB*data_EB " << i << " counts  " << frag_count_EB*purity_count_EB << endl;
  	//cout << "PurityEB" << i << " counts  " << purity_count_EB << endl;

  }

  TH1D* CF = (TH1D*)bkg[10]->Clone(); // Correction Factor calculation. ((Npromptdirect-OtherBg)/BG_Gjets)
  for (int i = 2; i < 4; ++i){
  	CF->Add(bkg[i], -1);
  	//for (int j = 1; j <= bkg[0]->GetNbinsX()+1; ++j){
  	//	cout<< "Bin " << j << " of background " << i << " "<< bkg[i]->GetBinContent(j)<< endl;
  	//}
  }
  
  //CF->Scale(bkg[10]->Integral()/bkg[8]->Integral());

  TH1D* CF_denominator = (TH1D*)bkg[8]->Clone();

  CF->Multiply(h_Npromptdirect);
  CF->Divide(CF_denominator);

  for (int i = 1; i <= bkg[0]->GetNbinsX(); ++i)  {
  	cout<< "Promptdirect " << i << " Count  " << h_Npromptdirect->GetBinContent(i)<<endl;
  	//cout<< "Multijet count  "<< bkg[9]->GetBinContent(i)<<endl;
  }

  TCanvas* c1 = new TCanvas("c1","",700,700);
  
  c1->SetGridx();
  c1->SetGridy();
  //CF->SetMaximum(40);
  //CF->SetMinimum(0);
  CF->SetMarkerStyle(25);
  CF->GetYaxis()->SetTitle("Correction Factor");
  CF->GetYaxis()->SetTitleOffset(0.9);
  CF->GetXaxis()->SetTitle("MR*R2 (GeV)");
  CF->Draw("EP");
  CMS_lumi(c1, 2, 1);

  c1->SaveAs(Form("Plot2017_September_preselectphotonpt_g/CorrectionFactor_fraction.pdf"), "recreate");

  return CF;	
}

void results(){
	TCanvas* C1 = new TCanvas("C1", "", 700, 700);
	TCanvas* C2 = new TCanvas("C2", "", 700, 700);

	inputfile1 = TFile::Open("2017_SinglePhoton.root");
	inputfile2 = TFile::Open("2017_GJets.root");
	//inputfile3 = TFile::Open("run_08102020.root");
	inputfile3 = TFile::Open("run_20102020.root");

    TFile* f1  = new TFile("Plot2017_September_preselectphotonpt_g/results.root","recreate");
	f1->mkdir("purity");
	//f1->mkdir("fraction");
	f1->mkdir("correction");

	pair<TH1D*, TH1D*> frac = Fraction(inputfile3);
	TH1D* frac_EB = frac.first;
	TH1D* frac_EE = frac.second;

	cout << "purity calculation" << endl;

  	pair<TH1D*, TH1D*> purity = Purity2D(inputfile1, inputfile2);
  	TH1D* purity_MRR2_EB = std::get<0>(purity);
	TH1D* purity_MRR2_EE = std::get<1>(purity);
	
  //for(int i=1;i<=25;i++) cout << purity_EB->GetBinContent(i) << ", " << purity_EE->GetBinContent(i) << endl;

  TH1D* CorFac2017 = Correction(purity_MRR2_EB, purity_MRR2_EE, frac_EB, frac_EE, inputfile3);

  f1->cd("correction");
  CorFac2017->Write();

  f1->cd("purity"); 
  purity_MRR2_EB->Write();
  purity_MRR2_EE->Write();
  f1->Close();


  C1->cd();
  purity_MRR2_EE->Draw("EP");
  C1->SaveAs("Plot2017_September_preselectphotonpt_g/Purity_EE.pdf", "recreate");
  C1->Close();

  C2->cd();
  purity_MRR2_EB->Draw("EP");
  C2->SaveAs("Plot2017_September_preselectphotonpt_g/Purity_EB.pdf", "recreate");
  C2->Close();

}

void purity(){
	results();

}
