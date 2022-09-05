void plotsys_pred(TString sys="JECup",TString year="full_Run2",int xmin=1,int xmax=5)
{
  // gStyle->SetOptStat(0);
    gStyle->SetPalette(1);

 bool data_pred=false;
 TFile *f1, *f2,*f3, *fout;
 TString lep="LM";
 TString path1;
 TString path2;
 TString rootout;


  if(sys=="JECup")
   {
     path1="rootout/fake_rate_v10_afterbtagSF/FR_using_PhoPtQmulti_csv_cut_EMObjeta_qmulti_METCaloMET_nopxveto_SF_bSF_newbin2/";
     path2="rootout/fake_rate_v10_afterJERC/withJECup/";

     //     path1="rootout/fake_rate_v10_afterJERC/withoutJERC/";
     // path2="rootout/fake_rate_v10_afterJERC/withJECup/";
     rootout="FR_JECup_v2.root";
   }
  else if(sys=="JERup")
   {
     path1="rootout/fake_rate_v10_afterbtagSF/FR_using_PhoPtQmulti_csv_cut_EMObjeta_qmulti_METCaloMET_nopxveto_SF_bSF_newbin2/";
     path2="rootout/fake_rate_v10_afterJERC/withJERup/";
     rootout="FR_JERup_v2.root";
   }
   else if(sys=="btagSF")
   {
     path1="rootout/fake_rate_v10_afterbtagSF/FR_using_PhoPtQmulti_csv_cut_EMObjeta_qmulti_METCaloMET_nopxveto_SF_bSF_newbin2/";
     path2="rootout/fake_rate_v10_afterbtagSF/tmp/";
     //     path2="rootout/fake_rate_v10_afterbtagSF/FR_using_PhoPtQmulti_csv_cut_EMObjeta_qmulti_METCaloMET_nopxveto_SF_bSFuperror_newbin2/";
     rootout="FR_btagSFup_v2.root";

   }
   else if(sys=="lepSF")
   {
     path1="rootout/fake_rate_v10_afterbtagSF/FR_using_PhoPtQmulti_csv_cut_EMObjeta_qmulti_METCaloMET_nopxveto_SF_bSF_newbin2/";
     path2="rootout/fake_rate_v10_afterbtagSF/FR_using_PhoPtQmulti_csv_cut_EMObjeta_qmulti_METCaloMET_nopxveto_SF_bSF_newbin2/";
     rootout="FR_lepSFup_v2.root";

   }

 else {
   cout<<" for JECup systematics : JECup"<<endl;
   cout<<" for JERup systematics : JERup"<<endl;
   cout<<" for lepSF systematics : lepSF"<<endl;

 }
 TLatex textOnTop,intLumiE;
 
 TString filename,filename1,filename2,a="Run2_METdata";
 if(year == "full_Run2")
   {
     filename1  = path1+a+"_CR_v18.root";
     filename2  = path2+a+"_CR_v18.root";
   }
 else
   {
     filename1= path1+a+"_"+year+"_CR_v18.root";
     filename2= path2+a+"_"+year+"_CR_v18.root";
   }
  f2 = new TFile(filename1);
  f3 = new TFile(filename2);

  double ymin=-0.15 , ymax=0.15, ymin_=-80 , ymax_=700;

  TH1D *cr,*sr,*tf,*pred_sr,*cr1,*sr1,*cr2,*sr2;

  TCanvas *c1;
  double nbin,bin0=0, bin1=46,yset_;
  TH1D *total;
  int rebin=1;
  //  TString varName="AllSBins_v6_CD";
  //  TString varName="AllSBins_v6_CD_EW_7bin_elec1_closure";

TString varName="AllSBins_v6_CD_EW_50bin_elec1_closure"; xmin=1,xmax=46; 
//  TString varName="METvBin2"; xmin=200,xmax=2000;
   //  TString varName="nJets"; xmin=2,xmax=20;

  gStyle->SetOptStat(0);
  c1 = new TCanvas("stackhist","stackhist",800,600);
  sr1          = (TH1D*)f2->Get(varName);
  sr2          = (TH1D*)f3->Get(varName);

  if(sys=="lepSF") {
    for(int i=xmin ; i<xmax; i++)
      sr1->SetBinContent(i,1.03*sr1->GetBinContent(i));
  }
  cout<<"Pred. nominal : "<<endl;
  for(int i=xmin ; i<xmax; i++)
    cout<<sr1->GetBinContent(i)<<endl;

  cout<<"Pred. + sys nominal : "<<endl;
  for(int i=xmin ; i<xmax; i++)
    cout<<sr2->GetBinContent(i)<<endl;

  
  //AllSBins_v6_CD_EW_7bin_elec1_closure  
  //  sr2->Divide(sr2);
  TPad *pad1 = new TPad("pad1","pad1",0,0,1,1);
  pad1->SetBottomMargin(0);
  pad1->SetBottomMargin(0.3);
  pad1->Draw();pad1->SetGridx(0);
  pad1->cd();
  //  pad1->SetLogy();
  
  //  sr->GetXaxis()->SetRangeUser(xmin,xmax);
  sr1->GetXaxis()->SetRangeUser(xmin,xmax);
  sr2->GetYaxis()->SetLabelSize(0.07);
  sr1->GetYaxis()->SetTitle("N(Pred.)");
  sr1->GetYaxis()->SetTitleSize(0.04);
  sr1->GetYaxis()->SetTitleOffset(0.92);
  sr1->GetYaxis()->SetRangeUser(ymin_,ymax_);
  //  sr2->GetYaxis()->SetRangeUser(ymin_,ymax_);
  sr2->SetMarkerStyle(20);
  sr2->SetMarkerSize(0.7);
  sr2->SetMarkerColor(kRed);
  sr2->SetLineColor(kRed);
  sr1->SetMarkerStyle(20);
  sr1->SetMarkerSize(0.7);
  sr1->SetMarkerColor(kBlue);
  sr1->SetLineColor(kBlue);
  sr1->SetTitle(0);
  sr1->Draw();
  sr2->Draw("same");
  
  textOnTop.SetTextSize(0.04);
  intLumiE.SetTextSize(0.04);
  textOnTop.DrawLatexNDC(0.12,0.91,"CMS #it{#bf{Simulation Preliminary}}");
  intLumiE.DrawLatexNDC(0.7,0.91,"#bf{137 fb^{-1} (13 TeV)}");

  double yset=(ymax_+ymin_)/1.78;
  cout<<"yset = "<<yset<<endl;
  if(varName=="AllSBins_v6_CD_EW_50bin_elec1_closure"){
    TLine *line1V6=new TLine( 8,ymin_,  8,yset);
    TLine *line2V6=new TLine(14,ymin_, 14,yset);
    TLine *line3V6=new TLine(19,ymin_, 19,yset);
    TLine *line4V6=new TLine(24,ymin_, 24,yset);
    TLine *line5V6=new TLine(29,ymin_, 29,yset);
    TLine *line6V6=new TLine(34,ymin_, 34,yset);
    TLine *line7V6=new TLine(40,ymin_, 40,yset);
  
    line1V6->Draw();      line2V6->Draw();  line3V6->Draw();
    line4V6->Draw();      line5V6->Draw();
    line6V6->Draw();      line7V6->Draw();
  
    TArrow *arrow1 = new TArrow( 1, yset, 8, yset,0.01,"<|>");
    TArrow *arrow2 = new TArrow( 8, yset, 14, yset,0.01,"<|>");
    TArrow *arrow3 = new TArrow( 14, yset, 19, yset,0.01,"<|>");
    TArrow *arrow4 = new TArrow( 19, yset, 24, yset,0.01,"<|>");
    TArrow *arrow5 = new TArrow( 24, yset, 29, yset,0.01,"<|>");
    TArrow *arrow6 = new TArrow( 29,yset, 34,yset,0.01,"<|>");
    TArrow *arrow7 = new TArrow( 34,yset, 40,yset,0.01,"<|>");
    TArrow *arrow8 = new TArrow( 40,yset, 46,yset,0.01,"<|>");
    TArrow *arrow11 = new TArrow( 1,yset*1.16, 33,yset*1.16,0.01,"<|>");
    TArrow *arrow12 = new TArrow( 33,yset*1.16, 46,yset*1.16,0.01,"<|>");
    arrow1->Draw(); arrow2->Draw(); arrow3->Draw();
    arrow4->Draw();
    arrow5->Draw(); arrow6->Draw();
    arrow7->Draw(); arrow8->Draw();
    arrow11->Draw(); arrow12->Draw();

    yset=(ymax_+ymin_)/1.7;
    cout<<"yset = "<<yset<<endl;
    TLatex Tl,T2;
    Tl.SetTextSize(0.035);
    T2.SetTextSize(0.04);
    Tl.DrawLatex(4.25,yset,"N^{ 0}_{ 2-4}");
    Tl.DrawLatex(10.25,yset,"N^{ 0}_{ 5-6}");
    Tl.DrawLatex(15.25,yset,"N^{ 0}_{ #geq7}");
    Tl.DrawLatex(20.25,yset,"N^{ #geq1}_{ 2-4}");
    Tl.DrawLatex(25.25,yset,"N^{ #geq1}_{ 5-6}");
    Tl.DrawLatex(30.25,yset,"N^{ #geq1}_{#geq7}");
    Tl.DrawLatex(35.25,yset,"W tag");
    Tl.DrawLatex(41.25,yset,"H tag");
    T2.DrawLatex(10.5,yset*1.15,"SP region");
    T2.DrawLatex(35.5,yset*1.15,"EW region");
  }
  
  TLegend *legend = new TLegend(0.1,0.83,0.35,0.9);
  TString title, title1;
  title1="#frac{#Delta TF(sys)}{TF_{nominal}}";

  if (sys=="btagSF") {title="btag SF sys.";}//ymin=-0.01 , ymax=0.01;}
  else if(sys=="JECup")title="JEC sys.";
  else if(sys=="JERup")title="JER sys.";
  legend->SetHeader(title,"C");
  legend->SetTextSize(0.04);
  legend->Draw();
  
  TLegend *legend1 = new TLegend(0.6,0.78,0.9,0.9);
  legend1->AddEntry(sr1,"nominal","lp");
  legend1->AddEntry(sr2,"nominal + sys","lp");
  legend1->SetTextSize(0.04);
  legend1->Draw();

  
      TH1D *h3 = (TH1D*)sr1->Clone("h3");
      TH1D *h4 = (TH1D*)sr2->Clone("h4");
      h3->Add(h4,-1);
      TH1D *pull = (TH1D*)h3->Clone("pull");
      TH1D *sr1_ = (TH1D*)sr1->Clone("sr1_");                                                                                                                                                                  
      TH1D *pull2 = (TH1D*)h3->Clone("pull2");
      for(int i=0 ; i<=xmax; i++)
	pull->SetBinContent(i,0);

      TPad *pad2 = new TPad("pad2","pad2",0,0.0,1,0.35);
      pad2->Draw();
      pad2->SetTopMargin(0);
      pad2->SetBottomMargin(0.35);
      pad2->cd();
      //      pad2->SetGrid(0);
      pad2->SetGridx(0);
      //      pull2->Sumw2();
      pull->Sumw2();
      pull->SetStats(0);      // No statistics on lower plot                                                                       
      pull->SetTitle(0);

      //      pull->Divide(pull2);
      pull2->Divide(sr1_);

      //  pull->Add(h4,-1);
     for(int i=0 ; i<=xmax; i++)
	{
	  pull->SetBinError(i,sr1->GetBinError(i)/sr1->GetBinContent(i));
	  pull2->SetBinError(i,0);
	}
      pull->SetMarkerColor(kBlack);
      pull->SetLineColor(kBlack);
      pull->GetXaxis()->SetTitle("Bin no.");
      pull->GetXaxis()->SetTitleOffset(0.8);
      pull->GetXaxis()->SetTitleSize(0.18);
      pull->GetXaxis()->SetLabelSize(0.12);
      pull->GetYaxis()->SetTitle(title1);
      pull->GetYaxis()->SetTitleSize(0.09);
      pull->GetYaxis()->SetTitleOffset(0.50);
      pull->GetYaxis()->SetLabelSize(0.08);

      pull->GetYaxis()->SetNdivisions(5);
      pull->SetFillColor(kGray);

      pull->SetFillColor(kGray);
        pull->SetMarkerColor(kGray);
	
      //      pull->SetLineColor(0);
      pull->Draw("E2");
      pull2->SetMarkerColor(kBlack);
      pull->SetMaximum(ymax);
      pull->SetMinimum(ymin);
				    
      pull2->Draw("same ep");
      if(varName=="AllSBins_v6_CD_EW_50bin_elec1_closure"){
	TLine *line1V6=new TLine( 8,ymin,  8,ymax);
	TLine *line2V6=new TLine(14,ymin, 14,ymax);
	TLine *line3V6=new TLine(19,ymin, 19,ymax);
	TLine *line4V6=new TLine(24,ymin, 24,ymax);
	TLine *line5V6=new TLine(29,ymin, 29,ymax);
	TLine *line6V6=new TLine(34,ymin, 34,ymax);
	TLine *line7V6=new TLine(40,ymin, 40,ymax);
	
	line1V6->Draw();      line2V6->Draw();  line3V6->Draw();
	line4V6->Draw();      line5V6->Draw();
	line6V6->Draw();      line7V6->Draw();
      }

  TLine *line= new TLine(xmin,0,xmax,0);
  line->SetLineColor(1);
  line->SetLineStyle(1);
  line->SetLineWidth(1);
  line->Draw();
  //  sr2->Draw("same");

  cout<<"Systematics : "<<endl;
  for(int i=xmin ; i<=xmax; i++)
    cout<<pull2->GetBinContent(i)<<endl;

  TH1D *JERC = new TH1D("JERC","JERC systematics",52,0,52) ;
  //  if(sys=="JECup" || sys=="JERup")
    {
      fout =new TFile(rootout,"recreate");
      fout->cd();
      for(int i=1; i<46; i++)
	{
	  JERC->SetBinContent(i,abs(sr1->GetBinContent(i+1)));
	  JERC->SetBinError(i,abs(sr2->GetBinContent(i+1)-sr1->GetBinContent(i+1))/sr1->GetBinContent(i+1));
	}
	
      JERC->Write();

    }
    TString sys_name="pdf/FR_"+sys+".pdf";
    c1->SaveAs(sys_name);
    sys_name="png/FR_"+sys+".png";
    c1->SaveAs(sys_name);
}
