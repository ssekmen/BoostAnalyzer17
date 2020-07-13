pair<double, double> PurityFit(TH1D* chisoFake, TH1D* chisoPrompt, TH1D* chiso, string EBEE, string MRR2Bin){
	TH1::SetDefaultSumw2();

	gStyle->SetOptStat(000);
	TCanvas C0("C0", "FractionFitter example", 700, 700);

	TObjArray *mc;
	TFractionFitter* fit;
	TH1F* result;
	double purity=0, error=0;
	mc = new TObjArray(3);
	mc->Add(chisoFake);
	mc->Add(chisoPrompt);
	fit = new TFractionFitter(chiso,mc);
	fit->Constrain(0,0.,0.5);
	fit->Constrain(1,0.5,1.);
	double prompt_value=0., prompt_error=0., fake_value=0., fake_error=0.;
	int status = fit->Fit();
	
	C0.cd();
	auto leg = new TLegend(0.65,0.55,0.85,0.75);
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
		
		chisoPrompt->Scale(prompt_value*result->Integral(1,10)/chisoPrompt->Integral(1,10));
		chisoFake->Scale(fake_value*result->Integral(1,10)/chisoFake->Integral(1,10));

		auto hs1 = new THStack("hs1","CMS #scale[0.7]{#font[52]{Work in progress 2017}}       #scale[0.7]{41.5 fb^{-1} (13 TeV)}");

		//chisoPrompt->Draw("SAME HIST");
		chisoFake->SetFillStyle(1001);
		chisoFake->SetFillColor(2);
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
		chiso->Draw("Same PE0");
		sprintf( texte1, "purity %.2f, error %.4f ", purity, error);
		sprintf(texte2, "MR*R2 Bin: %s - %s ", EBEE.c_str(), MRR2Bin.c_str());
		l1.DrawTextNDC( .45, .30, texte1);
		l2.DrawTextNDC( .30, .80, texte2);

		leg->SetTextSize(0.03);
		leg->AddEntry(chiso, "Data", "lep");
		//leg->AddEntry(result, "Fit", "l");
		leg->AddEntry(chisoPrompt, "Prompt");
		leg->AddEntry(chisoFake,"Fake");
		//leg->AddEntry(result,"fit result" );
		leg->Draw();		
	}
	C0.SaveAs(Form("plot_unskimmed17/Fraction_Test_%s_%s.pdf", EBEE.c_str(), MRR2Bin.c_str()), "recreate");	
	
  TFile* f1 = new TFile("./plot_unskimmed17/test.root", "update");
  C0.Write();
  result->Write();
  f1->Close();
  cout << purity << ", " << error << endl;
	return make_pair(purity,error);
}

pair<TH1D*, TH1D*> Purity2D(TFile* data, TFile* mc){
	TH1::SetDefaultSumw2();
	//template - fake
	TH2D* htemp0_EB = (TH2D*)data->Get(Form("MRR2Pho_vs_PhotonCHIso/Data_PassSIEIE_Barrel_Fake_CR_1PhoInv_g")); 	//Barrel
	TH2D* htemp0_EE = (TH2D*)data->Get(Form("MRR2Pho_vs_PhotonCHIso/Data_PassSIEIE_Endcap_Fake_CR_1PhoInv_g")); 	//Endcap
	TH2D* htemp1_EB = (TH2D*)mc->Get(Form("MRR2Pho_vs_PhotonCHIso/MC_FailSIEIE_Barrel_Fake_CR_1PhoInv_g"));	//Barrel
	TH2D* htemp1_EE = (TH2D*)mc->Get(Form("MRR2Pho_vs_PhotonCHIso/MC_FailSIEIE_Endcap_Fake_CR_1PhoInv_g"));	//Barrel
	//template - prompt
	TH2D* htemp2_EB = (TH2D*)mc->Get(Form("MRR2Pho_vs_PhotonCHIso/MC_FailSIEIE_Barrel_CR_1PhoInv_g"));	//Barrel
	TH2D* htemp2_EE = (TH2D*)mc->Get(Form("MRR2Pho_vs_PhotonCHIso/MC_FailSIEIE_Endcap_CR_1PhoInv_g"));	//Endcap
	//fitting target
	TH2D* htemp3_EB = (TH2D*)data->Get(Form("MRR2Pho_vs_PhotonCHIso/Data_FailSIEIE_Barrel_CR_1PhoInv_g"));	//Barrel (Template)
	TH2D* htemp3_EE = (TH2D*)data->Get(Form("MRR2Pho_vs_PhotonCHIso/Data_FailSIEIE_Endcap_CR_1PhoInv_g"));	//Endcap (Template)

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
    chisoFake_R2_EB.push_back(new TH1D((std::string("chisoFake_R2_EB_"+to_string(i))).c_str(), "", 10,0,10));
    chisoFakeMC_R2_EB.push_back(new TH1D((std::string("chisoFakeMC_R2_EB_"+to_string(i))).c_str(), "", 10,0,10));
    chisoPrompt_R2_EB.push_back(new TH1D((std::string("chisoPrompt_R2_EB_"+to_string(i))).c_str(), "", 10,0,10));
    chiso_R2_EB.push_back(new TH1D((std::string("chiso_R2_EB_"+to_string(i))).c_str(), "", 10,0,10));
    //Endcap
    chisoFake_R2_EE.push_back(new TH1D((std::string("chisoFake_R2_EE_"+to_string(i))).c_str(), "", 10,0,10));
    chisoFakeMC_R2_EE.push_back(new TH1D((std::string("chisoFakeMC_R2_EE_"+to_string(i))).c_str(), "", 10,0,10));
    chisoPrompt_R2_EE.push_back(new TH1D((std::string("chisoPrompt_R2_EE_"+to_string(i))).c_str(), "", 10,0,10));
    chiso_R2_EE.push_back(new TH1D((std::string("chiso_R2_EE_"+to_string(i))).c_str(), "", 10,0,10));
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

	  cout << "Bin content "<<i << " " << j << "  "<< htemp0_EB->GetBinContent(j,i)<< endl;
   	  }  
  	}

  	//std::vector<TH1D*> TemplateFit;
	std::vector<double> purity_R2_EB;
	std::vector<double> purity_R2_EE;
	//std::vector<double> purity_R2_EB_MC;
	//std::vector<double> purity_R2_EE_MC;
	std::vector<double> error_R2_EB;
	std::vector<double> error_R2_EE;
	//std::vector<double> error_R2_EB_MC;
	//std::vector<double> error_R2_EE_MC;
	pair<double, double> result;

	string MRR2Bins[5] = {"0-200", "200-400", "400-600", "600-1400", "1400-3000"};
	string EBEEs[2] = {"EB", "EE"};
  cout << "Chiso Fit" << endl;
  cout << "Size " << chisoFake_R2_EB.size() << endl;
	for(int i=0;i<chisoFake_R2_EB.size();++i){

		result = PurityFit(chisoFake_R2_EB[i], chisoPrompt_R2_EB[i], chiso_R2_EB[i], EBEEs[0], MRR2Bins[i]);
		purity_R2_EB.push_back(result.first); error_R2_EB.push_back(result.second);


		//result = PurityFit(chisoFakeMC_R2_EB[i], chisoPrompt_R2_EB[i], chiso_R2_EB[i]);
		//purity_R2_EB_MC.push_back(result.first); error_R2_EB_MC.push_back(result.second);

		result = PurityFit(chisoFake_R2_EE[i], chisoPrompt_R2_EE[i], chiso_R2_EE[i], EBEEs[1], MRR2Bins[i]);
		purity_R2_EE.push_back(result.first); error_R2_EE.push_back(result.second);

		//result = PurityFit(chisoFakeMC_R2_EE[i], chisoPrompt_R2_EE[i], chiso_R2_EE[i]);
		//purity_R2_EE_MC.push_back(result.first); error_R2_EE_MC.push_back(result.second);
	}

	//result = PurityFit(chisoFakeMC_R2_EB[4], chisoPrompt_R2_EB[4], chiso_R2_EB[4]);

  cout << "end Fit" << endl;

	TH1D* hist_R2_EB = new TH1D("hist_R2_EB", "", 2, 0, 10);
	TH1D* hist_R2_EE = new TH1D("hist_R2_EE", "", 2, 0, 10);
	//TH1D* hist_R2_EB_MC = new TH1D("hist_R2_EB_MC", "", 2, 0, 10);
	//TH1D* hist_R2_EE_MC = new TH1D("hist_R2_EE_MC", "", 2, 0, 10);

	for(int i=1;i<=4;i++){
		hist_R2_EB->SetBinContent(i,purity_R2_EB[i-1]);
		hist_R2_EB->SetBinError(i,error_R2_EB[i-1]);
		//hist_R2_EB_MC->SetBinContent(i,purity_R2_EB_MC[i-1]);
		//hist_R2_EB_MC->SetBinError(i,error_R2_EB_MC[i-1]);
		hist_R2_EE->SetBinContent(i,purity_R2_EE[i-1]);
		hist_R2_EE->SetBinError(i,error_R2_EE[i-1]);
		//hist_R2_EE_MC->SetBinContent(i,purity_R2_EE_MC[i-1]);
		//hist_R2_EE_MC->SetBinError(i,error_R2_EE_MC[i-1]);
	}

	return make_pair(hist_R2_EB, hist_R2_EE);
}

pair<TH1D*, TH1D*> Fraction(TFile* f1){
	TH1::SetDefaultSumw2();
	TH2D* htemp_EB = (TH2D*)f1->Get(Form("MRR2Pho_vs_PhotonCHIso/MC_PassSIEIE_Barrel_Prompt_CR_1PhoInv_g"));
	TH2D* htemp_EE = (TH2D*)f1->Get(Form("MRR2Pho_vs_PhotonCHIso/MC_PassSIEIE_Endcap_Prompt_CR_1PhoInv_g"));
	TH1D* hist_EB = new TH1D("hist_EB", "", 25,0,25);
	TH1D* hist_EE = new TH1D("hist_EE", "", 25,0,25);
	double frag, prom;
	double frag_e, prom_e, bin=1;
	const char *name[2] = {"htemp_EB", "htemp_EE"};
	//Make 1D hist
	for(int i=1;i<=htemp_EB->GetNbinsX();i++){
		for(int j=1;j<=htemp_EB->GetNbinsY();j++){
			frag   = htemp_EB->GetBinContent(i,j,1);
			frag_e = htemp_EB->GetBinError(i,j,1);
			prom   = htemp_EB->GetBinContent(i,j,2);
			prom_e = htemp_EB->GetBinError(i,j,2);
			frag = htemp_EE->GetBinContent(i,j,1);
			frag_e = htemp_EE->GetBinError(i,j,1);
			prom = htemp_EE->GetBinContent(i,j,2);
			prom_e = htemp_EE->GetBinError(i,j,2);
    	    hist_EB->SetBinContent(bin,1);
			hist_EB->SetBinError(bin,0.01);
      		hist_EE->SetBinContent(bin,1);
			hist_EE->SetBinError(bin,0.01);
    	bin++;
      //cout << hist_EB->GetBinContent(bin) << ", " << hist_EE->GetBinContent(bin) << endl;
		}
	}
	return make_pair(hist_EB, hist_EE);
}

void results(){
	TCanvas* C1 = new TCanvas("C1", "", 700, 700);
	TCanvas* C2 = new TCanvas("C2", "", 700, 700);

	inputfile1 = TFile::Open("SinglePhotonUnskimmed5.root");
	inputfile2 = TFile::Open("GJetsUnskimmed5.root");

    TFile* f1  = new TFile("plot_unskimmed17/results.root","recreate");
	f1->mkdir("purity");
	f1->mkdir("fraction");

	pair<TH1D*, TH1D*> frac = Fraction(inputfile2);
	TH1D* frac_EB = frac.first;
	TH1D* frac_EE = frac.second;

    f1->cd("fraction");
    frac_EB->Write();
    frac_EE->Write();

	cout << "purity calculation" << endl;

  	pair<TH1D*, TH1D*> purity = Purity2D(inputfile1, inputfile2);
  	TH1D* purity_R2_EB = std::get<0>(purity);
	TH1D* purity_R2_EE = std::get<1>(purity);

	TH1D* purity_EB = new TH1D("purity_EB","", 25,0,25);
  TH1D* purity_EE = new TH1D("purity_EE","", 25,0,25);
  for(int i=1;i<=25;i++){
    purity_EB->SetBinContent(i,purity_R2_EB->GetBinContent((int)(i+4)/5));
    purity_EE->SetBinContent(i,purity_R2_EE->GetBinContent((int)(i+4)/5));
    purity_EB->SetBinError(i,purity_R2_EB->GetBinError((int)(i+4)/5));
    purity_EE->SetBinError(i,purity_R2_EE->GetBinError((int)(i+4)/5));
	}
  //for(int i=1;i<=25;i++) cout << purity_EB->GetBinContent(i) << ", " << purity_EE->GetBinContent(i) << endl;
  f1->cd("purity"); 
  purity_EB->Write();
  purity_EE->Write();
  f1->Close();


  C1->cd();
  purity_EE->Draw("EP");
  C1->SaveAs("plot_unskimmed17/Purity_EE.pdf", "recreate");
  C1->Close();

  C2->cd();
  purity_EB->Draw("EP");
  C2->SaveAs("plot_unskimmed17/Purity_EB.pdf", "recreate");
  C2->Close();

  

}

void purity(){
	results();

}