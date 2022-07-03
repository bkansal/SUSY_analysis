void plotsys(TString sys="default",int xmin=100,int xmax=300)
{
  // gStyle->SetOptStat(0);
    gStyle->SetPalette(1);

 bool data_pred=false;
 TFile *f1, *f2,*f3;
 TString lep="LM", year="full_Run2";
 TString path1="rootout/fake_rate_v10_afterbtagSF/FR_using_PhoPtQmulti_csv_cut_EMObjeta_qmulti_METCaloMET_nopxveto_SF_bSF_newbin2/";
 TString path2="rootout/fake_rate_v10_afterbtagSF/FR_using_PhoPtQmulti_csv_cut_EMObjeta_qmulti_METCaloMET_nopxveto_SFuperror_bSF_newbin2/";

 TString varname="PhoPtQMultJet";
 TString varname0=varname+"_elec0";
 TString varname1=varname;
 if(sys=="drmodel")
   {
     path1="rootout/fake_rate_v10_afterbtagSF/FR_using_PhoPtQmulti_csv_cut_EMObjeta_qmulti_METCaloMET_nopxveto_SF_bSF_newbin2/";
     path2="rootoutput/newselec_LM_noISRjet_METfilters_EW_hadjetID_newPU_v18/TF_v7_usingfullRun2_BTagSF_SF_drpt5model/";
   }
 else if(sys=="btagSF")
   {
     path1="rootout/fake_rate_v10_afterbtagSF/FR_using_PhoPtQmulti_csv_cut_EMObjeta_qmulti_METCaloMET_nopxveto_SF_bSF_newbin2/";
     path2="rootout/fake_rate_v10_afterbtagSF/FR_using_PhoPtQmulti_csv_cut_EMObjeta_qmulti_METCaloMET_nopxveto_SF_bSFuperror_newbin2/";
   }
  else if(sys=="JECup")
   {
     path1="rootout/fake_rate_v10_afterJERC/withoutJERC/";
     path2="rootout/fake_rate_v10_afterJERC/withJECup/";
   }
  else if(sys=="JERup")
   {
     path1="rootout/fake_rate_v10_afterJERC/withoutJERC/";
     path2="rootout/fake_rate_v10_afterJERC/withJERup/";

   }
   else if(sys=="lepSF")
   {
     path1="rootout/fake_rate_v10_afterbtagSF/FR_using_PhoPtQmulti_csv_cut_EMObjeta_qmulti_METCaloMET_nopxveto_SF_bSF_newbin2/";
     path2="rootout/fake_rate_v10_afterbtagSF/FR_using_PhoPtQmulti_csv_cut_EMObjeta_qmulti_METCaloMET_nopxveto_SFuperror_bSF_newbin2/";
   }
   else if(sys=="scale")
   {
     path1="rootout/fake_rate_v10_afterbtagSF/FR_using_PhoPtQmulti_csv_cut_EMObjeta_qmulti_METCaloMET_nopxveto_SF_bSF_newbin2/";
     path2="rootout/fake_rate_v10_afterbtagSF/FR_using_PhoPtQmulti_csv_cut_EMObjeta_qmulti_METCaloMET_nopxveto_noSF_bSF_scalepdf_newbin2/";
     varname1="PhoPtQMultJet_scale";
     varname0="PhoPtQMultJet_scale_elec0";
  }
    else if(sys=="pdf")
   {
     path1="rootout/fake_rate_v10_afterbtagSF/FR_using_PhoPtQmulti_csv_cut_EMObjeta_qmulti_METCaloMET_nopxveto_SF_bSF_newbin2/";
     path2="rootout/fake_rate_v10_afterbtagSF/FR_using_PhoPtQmulti_csv_cut_EMObjeta_qmulti_METCaloMET_nopxveto_noSF_bSF_scalepdf_newbin2/";
     varname1="PhoPtQMultJet_pdf";
     varname0="PhoPtQMultJet_pdf_elec0";
   }
 else {
   cout<<" for Modelling of collinear photons : drmodel"<<endl;
   cout<<" for btagSF systematics : btagSF"<<endl;
   cout<<" for JECup systematics : JECup"<<endl;
   cout<<" for JERup systematics : JERup"<<endl;
   cout<<" for lepSF systematics : lepSF"<<endl;

 }
 TLatex textOnTop,intLumiE;
 
 TString filename,filename1,filename2;
 if(year == "full_Run2")
   {
     filename1  = path1+"TTWGJ_CR_v18.root";
     filename2  = path2+"TTWGJ_CR_v18.root";
   }
 else
   {
     filename1= path1+"_"+year+"_CR_v18.root";
     filename2= path2+"_"+year+"_CR_v18.root";
   }
  f2 = new TFile(filename1);
  f3 = new TFile(filename2);

  
  double ymin=0.5 , ymax=1.5, ymin_=0.0001 , ymax_=1000;

  TH2D *cr,*sr,*tf,*pred_sr,*cr1,*sr1,*cr2,*sr2;

  TCanvas *c1;
  double nbin,bin0=0, bin1=46,yset_;
  TH1D *total;
  int rebin=1;
  
  //gStyle->SetOptStat(0);
  c1 = new TCanvas("stackhist","stackhist",800,1000);
  cr1          = (TH2D*)f2->Get("PhoPtQMultJet");
  sr1          = (TH2D*)f2->Get("PhoPtQMultJet_elec0");
  cr2          = (TH2D*)f3->Get("PhoPtQMultJet");
  sr2          = (TH2D*)f3->Get("PhoPtQMultJet_elec0");
  
  sr1->GetXaxis()->SetRangeUser(xmin,xmax);
  sr2->GetXaxis()->SetRangeUser(xmin,xmax);
  sr1->Divide(cr1);
  sr2->Divide(cr2);
  //  sr2->Divide(sr2);
  TH2D *h4 = (TH2D*)sr1->Clone("h4");
  TH2D *h3 = (TH2D*)sr2->Clone("h3");
  h3->Add(h4,-1);
  TH2D *pull = (TH2D*)h3->Clone("pull");
  pull->Sumw2();
  pull->SetStats(0);      // No statistics on lower plot                                                                       

  pull->Divide(h4);
  //  pull->Add(h4,-1);
  pull->Draw("colz text");
  //  sr2->Draw("same");


  TLegend *legend = new TLegend(0.1,0.83,0.35,0.9);

  if(sys=="btagSF"){
    legend->SetHeader("btag SF sys.","C");
    legend->SetTextSize(0.04);
    legend->Draw();
  }
  else if(sys=="lepSF"){
    legend->SetHeader("e SF sys.","C");
    legend->SetTextSize(0.04);
    legend->Draw();
  }
  else if(sys=="JECup"){
    legend->SetHeader("JEC sys.","C");
    legend->SetTextSize(0.04);
    legend->Draw();
  }
  else if(sys=="JERup"){
    legend->SetHeader("JER sys.","C");
    legend->SetTextSize(0.04);
    legend->Draw();
  }
  
}
