#include "CMS_lumi.C"


 double div_err(double b1, double e1, double b2, double e2){

 	return ( (e1*e1*b2*b2 + e2*e2*b1*b1) / (b2*b2*b2*b2) )*0.5;
 }

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
	fit->Constrain(0,0.0,0.5);
	fit->Constrain(1,0.5,1.0);
	double prompt_value=0., prompt_error=0., fake_value=0., fake_error=0.;
	int status = fit->Fit();
	
	C0->cd();
	chiso->Draw("PE0");
	auto leg = new TLegend(0.65,0.55,0.85,0.75);
	//C0->SetLogy();
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
		char legentry[3];

		//chisoPrompt->Draw("SAME HIST");
		chisoFake->SetFillStyle(1001);
		chisoFake->SetFillColor(2);
		hs1->Add(chisoFake);
		chisoPrompt->SetLineStyle(1001);
		chisoPrompt->SetFillColor(8);
		//chisoPrompt->GetXaxis()->SetTitle("Photon Charged Isolation GeV");
		//chisoPrompt->SetFillWidth(8);
		hs1->Add(chisoPrompt);
		chiso->SetMarkerStyle(20);
		hs1->Draw("SAME HIST");
		chiso->Draw("SAME PE0");
		result->Draw("SAME");
		sprintf( texte1, "purity %.2f, error %.4f ", purity, error);
		sprintf(texte2, "MRR2Bins %s ", MRR2Bin.c_str());
		l1.DrawTextNDC( .45, .50, texte1);
		l2.DrawTextNDC( .37, .77, texte2);

		sprintf(legentry, "#font[82]{%7.1f}",chiso->Integral());
		leg->SetTextSize(0.028);
		leg->AddEntry(chiso, "Data", "lep");
		leg->AddEntry((TObject*)0,legentry,"");

		sprintf(legentry, "#font[82]{%7.1f}",result->Integral());		
		leg->AddEntry(result, "Fit", "l");
		leg->AddEntry((TObject*)0,legentry,"");

		sprintf(legentry, "#font[82]{%7.1f}",chisoPrompt->Integral());
		leg->AddEntry(chisoPrompt, "Prompt");
		leg->AddEntry((TObject*)0,legentry,"");

		sprintf(legentry, "#font[82]{%7.1f}",chisoFake->Integral());
		leg->AddEntry(chisoFake,"Fake");
		leg->AddEntry((TObject*)0,legentry,"");
		leg->Draw();		
	}
	CMS_lumi(C0, 2, 1);
	//C0->SetLogx();
	C0->SaveAs(Form("MRR2Template_2016/Fraction_2016_Test_%s_%s.pdf", EBEE.c_str(), MRR2Bin.c_str()), "recreate");	
	
  TFile* f1 = new TFile("./MRR2Template_2016/test.root", "update");
  C0->Write();
  result->Write();
  f1->Close();
  C0->Close();
  cout << purity << ", " << error << endl;
	return make_pair(purity,error);
}

pair<TH1D*, TH1D*> Purity2D(TFile* file, TString year){
	TH1::SetDefaultSumw2();
	//template - fake
	TH2D* htemp0_EB = (TH2D*)file->Get("MRR2NoPhoBins1_vs_PhotonCHIso_preslectphoptREBin/Data_FakePhoton_CR_1PhoInv_Excl1Pho1M_"+year+"_Barrel"); 	//Barrel
	TH2D* htemp0_EE = (TH2D*)file->Get("MRR2NoPhoBins1_vs_PhotonCHIso_preslectphoptREBin/Data_FakePhoton_CR_1PhoInv_Excl1Pho1M_"+year+"_Endcap"); 	//Endcap
	TH2D* htemp1_EB = (TH2D*)file->Get("MRR2NoPhoBins1_vs_PhotonCHIso_preslectphoptREBin/MC_FakePhoton_CR_1PhoInv_Excl1Pho1M_"+year+"_Barrel");	//Barrel
	TH2D* htemp1_EE = (TH2D*)file->Get("MRR2NoPhoBins1_vs_PhotonCHIso_preslectphoptREBin/MC_FakePhoton_CR_1PhoInv_Excl1Pho1M_"+year+"_Endcap");	//Barrel
	//template - prompt
	TH2D* htemp2_EB = (TH2D*)file->Get("MRR2NoPhoBins1_vs_PhotonCHIso_preslectphoptREBin/MC_PromptPhoton_CR_1PhoInv_Excl1Pho1M_"+year+"_Barrel");	//Barrel
	TH2D* htemp2_EE = (TH2D*)file->Get("MRR2NoPhoBins1_vs_PhotonCHIso_preslectphoptREBin/MC_PromptPhoton_CR_1PhoInv_Excl1Pho1M_"+year+"_Endcap");	//Endcap
	//fitting target
	TH2D* htemp3_EB = (TH2D*)file->Get("MRR2NoPhoBins1_vs_PhotonCHIso_preslectphoptREBin/Data_PhotonNoIso_CR_1PhoInv_Excl1Pho_"+year+"_Barrel");	//Barrel (Template)
	TH2D* htemp3_EE = (TH2D*)file->Get("MRR2NoPhoBins1_vs_PhotonCHIso_preslectphoptREBin/Data_PhotonNoIso_CR_1PhoInv_Excl1Pho_"+year+"_Endcap");	//Endcap (Template)

	std::vector<TH1D*> chisoFake_R2_EB;
	std::vector<TH1D*> chisoFakeMC_R2_EB;
	std::vector<TH1D*> chisoPrompt_R2_EB;
	std::vector<TH1D*> chiso_R2_EB;

	std::vector<TH1D*> chisoFake_R2_EE;
	std::vector<TH1D*> chisoFakeMC_R2_EE;
	std::vector<TH1D*> chisoPrompt_R2_EE;
	std::vector<TH1D*> chiso_R2_EE;


	int nbn_CHIS;
	float bn_CHISOptRebin[] = {0.,0.00001,1.,1.5,2.,3.,4.,5.,7.,10.,20.,50}; 	//First
	const char *CHISOptRebin[] = {"0.00001","1","1.5","2","3","4","5","7","10","20","50"};
	//float bn_CHISOptRebin[] = {0.,0.001,1.5,2.,5.,7.,9.,10.,20.};				//Second
	//const char *CHISOptRebin[] = {"0.00001","1.5","2","5","7","9","10","20"};
	//float bn_CHISOptRebin[] = {0.,0.0001,1.,2.,4.,10.,50.,100};				//Third
	//const char *CHISOptRebin[] = {"0.0001","1","2","4","10","50","100"};
	//float bn_CHISOptRebin[] = {0.,0.0001,1.,1.5,2.,2.5,3.,5.,7.,10.,20.};		//Fourth
	//const char *CHISOptRebin[] = {"0.0001","1","1.5","2","2.5","3","5","7","10","20"};
	//float bn_CHISOptRebin[] = {0.,0.01,1.,3.,7.,10.,20.,50.};
	//const char *CHISOptRebin[] = {"0.01","1","3","7","10","20","50"};
	for(int i=1;i<=htemp0_EB->GetNbinsY();i++){
	//Barrel	
    chisoFake_R2_EB.push_back(new TH1D((std::string("chisoFake_R2_EB_"+to_string(i))).c_str(), "", 11,0,11));
    chisoFakeMC_R2_EB.push_back(new TH1D((std::string("chisoFakeMC_R2_EB_"+to_string(i))).c_str(), "", 11,0,11));
    chisoPrompt_R2_EB.push_back(new TH1D((std::string("chisoPrompt_R2_EB_"+to_string(i))).c_str(), "", 11,0,11));
    chiso_R2_EB.push_back(new TH1D((std::string("chiso_R2_EB_"+to_string(i))).c_str(), "", 11,0,11));
    //Endcap
    chisoFake_R2_EE.push_back(new TH1D((std::string("chisoFake_R2_EE_"+to_string(i))).c_str(), "", 11,0,11));
    chisoFakeMC_R2_EE.push_back(new TH1D((std::string("chisoFakeMC_R2_EE_"+to_string(i))).c_str(), "", 11,0,11));
    chisoPrompt_R2_EE.push_back(new TH1D((std::string("chisoPrompt_R2_EE_"+to_string(i))).c_str(), "", 11,0,11));
    chiso_R2_EE.push_back(new TH1D((std::string("chiso_R2_EE_"+to_string(i))).c_str(), "", 11,0,11));
	}
	
	cout << "Bins of fake X  " << htemp0_EB->GetNbinsX()<< endl;
	cout << "Bins of fake Y  " << htemp0_EB->GetNbinsY()<< endl;

	for(int i=1;i<=htemp0_EB->GetNbinsY();i++){ 							// 5 bins from MR*R2
	  for(int j=1;j<=htemp0_EB->GetNbinsX();j++){							// 20 bins from Chiso
	  // Barrel	
      chisoFake_R2_EB[i-1]->SetBinContent(j,(htemp0_EB->GetBinContent(j,i)));
      chisoFake_R2_EB[i-1]->SetBinError(j,(htemp0_EB->GetBinError(j,i)));

      chisoFakeMC_R2_EB[i-1]->SetBinContent(j,(htemp1_EB->GetBinContent(j,i)));
      chisoFakeMC_R2_EB[i-1]->SetBinError(j,(htemp1_EB->GetBinError(j,i)));

      chisoPrompt_R2_EB[i-1]->SetBinContent(j,(htemp2_EB->GetBinContent(j,i)));
      chisoPrompt_R2_EB[i-1]->SetBinError(j,(htemp2_EB->GetBinError(j,i)));

      chiso_R2_EB[i-1]->SetBinContent(j,(htemp3_EB->GetBinContent(j,i)));
      chiso_R2_EB[i-1]->SetBinError(j,(htemp3_EB->GetBinError(j,i)));
      chiso_R2_EB[i-1]->GetXaxis()->SetTitle("Photon Charged Isolation (GeV)");
      chiso_R2_EB[i-1]->GetYaxis()->SetTitle("Events - Barrel");
      chiso_R2_EB[i-1]->GetXaxis()->LabelsOption("v");
      chiso_R2_EB[i-1]->GetXaxis()->SetBinLabel(j+1, CHISOptRebin[j]);

      // Endcap 
      chisoFake_R2_EE[i-1]->SetBinContent(j,(htemp0_EE->GetBinContent(j,i)));
      chisoFake_R2_EE[i-1]->SetBinError(j,(htemp0_EE->GetBinError(j,i)));

      chisoFakeMC_R2_EE[i-1]->SetBinContent(j,(htemp1_EE->GetBinContent(j,i)));
      chisoFakeMC_R2_EE[i-1]->SetBinError(j,(htemp1_EE->GetBinError(j,i)));

      chisoPrompt_R2_EE[i-1]->SetBinContent(j,(htemp2_EE->GetBinContent(j,i)));
      chisoPrompt_R2_EE[i-1]->SetBinError(j,(htemp2_EE->GetBinError(j,i)));

      chiso_R2_EE[i-1]->SetBinContent(j,(htemp3_EE->GetBinContent(j,i)));
      chiso_R2_EE[i-1]->SetBinError(j,(htemp3_EE->GetBinError(j,i)));
      chiso_R2_EE[i-1]->GetXaxis()->SetTitle("Photon Charged Isolation (GeV)");
      chiso_R2_EE[i-1]->GetYaxis()->SetTitle("Events - Endcap");
      chiso_R2_EE[i-1]->GetXaxis()->LabelsOption("v");
      chiso_R2_EE[i-1]->GetXaxis()->SetBinLabel(j+1, CHISOptRebin[j]);


	  //cout << "Bin content "<<i << " " << j << "  "<< log10(htemp0_EB->GetBinContent(j,i))<< endl;
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

	//string MRR2Bins[5] = {"0-150", "150-200", "200-250", "250-300", "300-3000"};
	//string MRR2Bins[3] = {"=1", "=>2"};
	string MRR2Bins[3] = {"0-150", "150-300", "300-3000"};
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

	TH1D* hist_R2_EB = new TH1D("hist_R2_EB", ";;M_{R}*R^{2} (GeV);Photon purity", 3, 0, 3.5);
	TH1D* hist_R2_EE = new TH1D("hist_R2_EE", "", 3, 0, 3.5);
	TH1D* hist_R2_EB_MC = new TH1D("hist_R2_EB_MC", "", 3, 0, 3.5);
	TH1D* hist_R2_EE_MC = new TH1D("hist_R2_EE_MC", "", 3, 0, 3.5);

	for(int i=1;i<=3;i++){
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
	C1->SaveAs(Form("MRR2Template_2016/PurityResults.pdf"), "recreate");

	return make_pair(hist_R2_EB, hist_R2_EE);
}

pair<TH1D*, TH1D*> Fraction(TFile* f1, TString year){
	TH1::SetDefaultSumw2();
	TH2D* fraction[2];

	fraction[0] = (TH2D*)f1->Get("DirectFraction_vs_MRR2NoPhoBins1/plus1d_Background_Prompt_Endcap_"+year+"_CR_1PhoInv");
    fraction[1] = (TH2D*)f1->Get("DirectFraction_vs_MRR2NoPhoBins1/plus1d_Background_Prompt_Barrel_"+year+"_CR_1PhoInv");

/*
    int binsize = fraction[0]->GetNbinsX();
    double bin[binsize+1];
    for(int i=1;i<=fraction[0]->GetNbinsX()+1;i++) bin[i-1] = fraction[0]->GetXaxis()->GetBinLowEdge(i);

    TH1D* fractionEBEE[2];
	string name;

	for (int i = 0; i <2; ++i){		
  		name = "frac_"+to_string(i);
  		fractionEBEE[i] = new TH1D(name.c_str(), "", binsize, bin);
  		for (int j = 1; j <= fraction[0]->GetNbinsX(); ++j){
  			fractionEBEE[i]->SetBinContent(j, fraction[i]->GetBinContent(j,1));
  			fractionEBEE[i]->SetBinError(j, fraction[i]->GetBinError(j,1));  		
  		}
  	}

	//double frac_EB = fraction_EB->GetMean();
	//double frac_EE = fraction_EE->GetMean();
	
	//cout << "Mean of Fraction counts-EB  " << fraction_EB << endl;
   
    for (int i = 0; i < fraction[0]->GetNbinsX(); ++i){
    		cout<< "EB.  " << fractionEBEE[1]->GetBinContent(i)<<endl;
    		cout<< "EE.  " << fractionEBEE[0]->GetBinContent(i)<<endl;  	
    }
*/

    TH1D* hist_EB = new TH1D("hist_EB", "", 4,0,4);
	TH1D* hist_EE = new TH1D("hist_EE", "", 4,0,4);
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

TGraphAsymmErrors* Correction(TH1D* purity_EB, TH1D* purity_EE, TH1D* frac_EB, TH1D* frac_EE, TFile* inputfile, TString year){

  gStyle->SetOptTitle(0);
  TH1::SetDefaultSumw2();

  TH2D* bkg2D[12];

  bkg2D[0] = (TH2D*)inputfile->Get("Counts_vs_MRR2NoPhoBins1/Syst_vs_MRR2NoPhoBins1/Data_"+year+"_Endcap_CR_1PhoInv");
  bkg2D[1] = (TH2D*)inputfile->Get("Counts_vs_MRR2NoPhoBins1/Syst_vs_MRR2NoPhoBins1/Data_"+year+"_Barrel_CR_1PhoInv");
  bkg2D[2] = (TH2D*)inputfile->Get("Counts_vs_MRR2NoPhoBins1/Syst_vs_MRR2NoPhoBins1/DYToLL_"+year+"_CR_1PhoInv");
  bkg2D[3] = (TH2D*)inputfile->Get("Counts_vs_MRR2NoPhoBins1/Syst_vs_MRR2NoPhoBins1/Higgs_"+year+"_CR_1PhoInv");
  bkg2D[4] = (TH2D*)inputfile->Get("Counts_vs_MRR2NoPhoBins1/Syst_vs_MRR2NoPhoBins1/Multiboson_"+year+"_CR_1PhoInv");
  bkg2D[5] = (TH2D*)inputfile->Get("Counts_vs_MRR2NoPhoBins1/Syst_vs_MRR2NoPhoBins1/TT_powheg_pythia8_"+year+"_CR_1PhoInv");
  bkg2D[6] = (TH2D*)inputfile->Get("Counts_vs_MRR2NoPhoBins1/Syst_vs_MRR2NoPhoBins1/WToLNu_"+year+"_CR_1PhoInv");
  bkg2D[7] = (TH2D*)inputfile->Get("Counts_vs_MRR2NoPhoBins1/Syst_vs_MRR2NoPhoBins1/ZToNuNu_"+year+"_CR_1PhoInv");	
  bkg2D[8] = (TH2D*)inputfile->Get("Counts_vs_MRR2NoPhoBins1/Syst_vs_MRR2NoPhoBins1/Top_"+year+"_CR_1PhoInv");	
  bkg2D[9] = (TH2D*)inputfile->Get("Counts_vs_MRR2NoPhoBins1/Syst_vs_MRR2NoPhoBins1/Multijet_"+year+"_CR_1PhoInv"); //Exclude this from other BG
  bkg2D[10] = (TH2D*)inputfile->Get("Counts_vs_MRR2NoPhoBins1/Syst_vs_MRR2NoPhoBins1/GJets_"+year+"_CR_1PhoInv");	
  bkg2D[11] = (TH2D*)inputfile->Get("Counts_vs_MRR2NoPhoBins1/Syst_vs_MRR2NoPhoBins1/Data_"+year+"_CR_1PhoInv");	

  int binsize = bkg2D[0]->GetNbinsX();
  double bin[binsize+1];
  //cout << "----------Binsize-------------------->  " << binsize <<endl;
  for(int i=1;i<=bkg2D[0]->GetNbinsX()+1;i++) bin[i-1] = bkg2D[0]->GetXaxis()->GetBinLowEdge(i);
  TH1D* bkg[10]; //1D MR*R2 data and background histograms
  // TH1D* Npromptdirect = new TH1D("promptdirect", ";Prompt Direct (GeV)", 5,0,5);
  string name;

  for (int i = 0; i <12; ++i){		
  	name = "bckgrnd_"+to_string(i);
  	bkg[i] = new TH1D(name.c_str(), "mass-tag", binsize, bin);
  	for (int j = 1; j <= bkg2D[0]->GetNbinsX(); ++j){
  		bkg[i]->SetBinContent(j, bkg2D[i]->GetBinContent(j,1));
  		bkg[i]->SetBinError(j, bkg2D[i]->GetBinError(j,1));  
		
  	}
  }

  //cout <<"----------Size of 1D ---------------------------->  " << bkg[0]->GetNbinsX()<< endl;
  
  TH1D * h_Npromptdirect = new TH1D("CorrectionFactor", ";mass-tag", binsize ,bin);
  double Npromptdirect[binsize];
  double Npromptdirect_err[binsize];
  double DR;							//		   ***DR***
  double DR_up; 						//		-Double  Ratio-
  double DR_down;						//		-Calculation-
  double eG;							//		Error of PromptDirect photons
  double eG_GJ;							//   	Erro of Direct photons in MC (GJets)
  double Nominal[binsize];
  double Plus[binsize];
  double Plus_err[binsize];
  double Minus[binsize];
  double Minus_err[binsize];	
  double CF_G_down[binsize];
  double CF_G_up[binsize];
 
  for (int i = 1; i <= bkg[0]->GetNbinsX(); ++i){

  	double purity_count_EB = purity_EB->GetBinContent(i);
  	double purity_count_EE = purity_EE->GetBinContent(i);
  	double purity_EB_err = purity_EB->GetBinError(i);
  	double purity_EE_err = purity_EE->GetBinError(i);
  	double frag_EB_err = frac_EB->GetBinError(i);
  	double frag_EE_err = frac_EE->GetBinError(i);
  	double frag_count_EB = frac_EB->GetBinContent(i);
  	double frag_count_EE = frac_EE->GetBinContent(i);
  	double data_EB = bkg[1]->GetBinContent(i); // data on Barrel region
  	double data_EE = bkg[0]->GetBinContent(i); // data on Endcap region
  	double data_EB_err = bkg[1]->GetBinError(i);
  	double data_EE_err = bkg[0]->GetBinError(i);

	Nominal[i] = data_EB*purity_count_EB*frag_count_EB;
  	Nominal[i] += data_EE*purity_count_EE*frag_count_EE;

  	Plus[i] = data_EB*(purity_count_EB+purity_EB_err)*frag_count_EB;
  	Plus[i] += data_EE*(purity_count_EE+purity_EE_err)*frag_count_EE;

  	Plus_err[i]  = data_EE_err*(purity_count_EB+purity_EB_err)*frag_EB_err;
  	Plus_err[i] += data_EE_err*(purity_count_EE+purity_EE_err)*frag_EE_err;

  	Minus[i] = data_EB*(purity_count_EB-purity_EB_err)*frag_count_EB;
  	Minus[i] += data_EE*(purity_count_EE-purity_EE_err)*frag_count_EE;

  	Minus_err[i]  = data_EE_err*(purity_count_EB-purity_EB_err)*frag_EB_err;
  	Minus_err[i] += data_EE_err*(purity_count_EE-purity_EE_err)*frag_EE_err;
	  
  	Npromptdirect[i] = data_EB*purity_count_EB*frag_count_EB;
  	Npromptdirect[i] += data_EE*purity_count_EE*frag_count_EE;

  	Npromptdirect_err[i] = pow((data_EB_err*purity_count_EB*frag_count_EB),2);
  	Npromptdirect_err[i] += pow((data_EE_err*purity_count_EE*frag_count_EE),2);

  	Npromptdirect_err[i] = pow((Npromptdirect_err[i]),0.5);

  	h_Npromptdirect->SetBinContent(i,Npromptdirect[i]);
  	h_Npromptdirect->SetBinError(i,Npromptdirect_err[i]);
	h_Nominal->SetBinContent(i,Nominal[i]);
  	h_Nominal->SetBinError(i,Npromptdirect_err[i]);
  	h_Plus->SetBinContent(i,Plus[i]);
  	h_Plus->SetBinError(i,Plus_err[i]);
  	h_Minus->SetBinContent(i,Minus[i]);
  	h_Minus->SetBinError(i,Minus_err[i]);
	  
  	CF_G_up[i-1] = std::sqrt(pow(abs(H_plus[i]-H_nominal[i]),2)+pow(Npromptdirect_err[i],2));

  	CF_G_down[i-1] = std::sqrt(pow(abs(H_nominal[i]-H_minus[i]),2)+pow(Npromptdirect_err[i],2));

  	cout << "H_nominal " << i << " counts  " << H_nominal[i] << endl;
  	cout << "H_plus " << i << " counts  " << H_plus[i] << endl;
  	cout << "H_minus " << i << " counts  " << H_minus[i] << endl;
  	cout << "H_err " << i << " counts  " << Npromptdirect_err[i] << endl;

  }

  TH1D* CF = (TH1D*)h_Npromptdirect->Clone(); // Correction Factor calculation. ((Npromptdirect-OtherBg)/BG_Gjets)
  TH1D* CF_UP 	= (TH1D*)h_Plus->Clone();
  TH1D* CF_DW  	= (TH1D*)h_Minus->Clone();
	
  DR_up = CF->IntegralAndError(0,-1,eG);

  for (int i = 2; i < 10; ++i){
  	CF->Add(bkg[i], -1); // Substraction of otherBG
	CF_UP->Add(bkg[i], -1);
  	CF_DW->Add(bkg[i], -1);  
  	for (int j = 1; j <= bkg[0]->GetNbinsX(); ++j){
  		cout<< "Bin " << j << " of background " << i << " "<< bkg[i]->GetBinContent(j)<< endl;
  	}
  }
  
  //CF->Scale(bkg[10]->Integral()/bkg[8]->Integral());


  // Double Ratio Calculation
  
  TH1D* CF_denominator = (TH1D*)bkg[10]->Clone();
  //CF_denominator->Add(bkg[9]);

  DR_down = CF_denominator->IntegralAndError(0,-1,eG_GJ);

  DR = DR_up/DR_down;

  ek_G = div_err(DR_up, eG, DR_down, eG_GJ);

  //cout<<"G_data (prompt, direct): "+str(DR_up) +" +- "+str(eG)
  //cout<<"G_GJ   (prompt, direct): "+str(DR_down)+" +- "+str(eG_GJ)
  printf("k_G = %4.3f +- %4.3f (%4.3f / %4.3f) (2016) \n", DR, ek_G, DR_up, DR_down);
  printf("error_G = %4.3f, error_GJet %4.3f (2016) \n", ek_G, eG_GJ);
  
  //CF->Multiply(h_Npromptdirect);
  CF->Divide(CF_denominator);
  CF_UP->Divide(CF_denominator);
  CF_DW->Divide(CF_denominator);

  for (int i = 1; i <= bkg[0]->GetNbinsX(); ++i)  {
  	cout<< "Correction Factor " << i << " Count  " << CF->GetBinContent(i)<<endl;
  	//cout<< "Multijet count  "<< bkg[9]->GetBinContent(i)<<endl;
  }

// TGraphAsymmErrors *. ------------------------------------------------------

double binx[binsize];
double binerr_x[binsize];
double Cf_G[binsize];
double Cf_G_up[binsize];
double Cf_G_down[binsize];

for(int i=1; i<= binsize;i++){
	binx[i-1] = CF->GetXaxis()->GetBinCenter(i);
	binerr_x[i-1] = CF->GetXaxis()->GetBinWidth(i)/2;
	Cf_G[i-1] = CF->GetBinContent(i);
	Cf_G_up[i-1] = (std::sqrt(pow(abs(CF_UP->GetBinContent(i)-CF->GetBinContent(i)),2)+pow(CF->GetBinContent(i),2)));
	Cf_G_down[i-1] = (std::sqrt(pow(abs(CF->GetBinContent(i))+CF_DW->GetBinContent(i),2)+pow(CF->GetBinContent(i),2)));	
}

auto CF_GJets = new TGraphAsymmErrors(binsize, binx, Cf_G, binerr_x, binerr_x, CF_G_down, CF_G_up);

CF_GJets->SetName("CorrectionFactor");

// TGraphAsymmErrors *. -------------------------------------------------------

  TCanvas* c1 = new TCanvas("c1","",700,700);
  
  c1->SetGridx();
  c1->SetGridy();
  //CF->SetMaximum(40);
  //CF->SetMinimum(0);
  CF->SetMarkerStyle(25);
  CF->GetYaxis()->SetTitle("Correction Factor");
  CF->GetYaxis()->SetTitleOffset(0.9);
  CF->GetXaxis()->SetTitle("M_{R}*R^{2} (GeV)");
  CF->Draw("EP");
  CMS_lumi(c1, 2, 1);

  c1->SaveAs(Form("MRR2Template_2016/CorrectionFactor_fraction.pdf"), "recreate");

  return CF_GJets;	
}

void results(){
	TCanvas* C1 = new TCanvas("C1", "", 700, 700);
	TCanvas* C2 = new TCanvas("C2", "", 700, 700);

	inputfile = TFile::Open("RootFiles/run_2021_09_09.root");

    TFile* f1  = new TFile("MRR2Template_2016/CF_GJets2016.root","recreate");
	//f1->mkdir("purity");
	//f1->mkdir("fraction");
	//f1->mkdir("correction");

	pair<TH1D*, TH1D*> frac = Fraction(inputfile, "2016");
	TH1D* frac_EB = frac.first;
	TH1D* frac_EE = frac.second;
/*
    f1->cd("fraction");
    frac_EB->Write();
    frac_EE->Write();
*/
	cout << "purity calculation" << endl;

  	pair<TH1D*, TH1D*> purity_2017 = Purity2D(inputfile, "2016");
  	TH1D* purity_MRR2_EB_2017 = std::get<0>(purity_2017);
	TH1D* purity_MRR2_EE_2017 = std::get<1>(purity_2017);
	
  //for(int i=1;i<=25;i++) cout << purity_EB->GetBinContent(i) << ", " << purity_EE->GetBinContent(i) << endl;

  TGraphAsymmErrors* CorFac2017 = Correction(purity_MRR2_EB_2017, purity_MRR2_EE_2017, frac_EB, frac_EE, inputfile, "2016");

  f1->cd();
  CorFac2017->Write();

  //f1->cd("purity"); 
  //purity_MRR2_EB_2017->Write();
  //purity_MRR2_EE_2017->Write();
  //f1->Close();


  C1->cd();
  purity_MRR2_EE_2017->Draw("EP");
  C1->SaveAs("MRR2Template_2016/Purity_EE.pdf", "recreate");
  C1->Close();

  C2->cd();
  purity_MRR2_EB_2017->Draw("EP");
  C2->SaveAs("MRR2Template_2016/Purity_EB.pdf", "recreate");
  C2->Close();

}

void purity(){
	results();

}
