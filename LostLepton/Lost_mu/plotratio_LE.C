void plotratio_LE()
{
  TFile *f1, *f2;
  //  f1 = new TFile("TTWGJets_CR.root");
  //  f1 = new TFile("TTGJets_2016_CR.root");
  //   f1 = new TFile("WGJets_2016_CR.root");
  f1 = new TFile("TTWGJ_2016_CR.root");
  //  f1 = new TFile("Run2_METdata.root");
  //f1 = new TFile("TTWGJ_2016_CR.root");
  //  f1 = new TFile("TTJets_2017_CR.root");
  //  f1 = new TFile("WJets_2016_CR.root");
  // f1 = new TFile("TTJets_2016_CR.root");
  //    f1 = new TFile("TTGJets_2017_CR.root");
  //  f1 = new TFile("WGJets_2017_CR.root");
  //   f1 = new TFile("TTWGJets_CR.root");
  //  f1 = new TFile("rootoutput/oldselec_LE_v3/TTWGJ_2016_CR.root");
  //  f1 = new TFile("rootoutput/oldselec_LM_v3/TTWGJets_2016_CR.root");
  // f1 = new TFile("rootoutput/tmp/TTWGJ_2016_CR.root");
  //   f1 = new TFile("rootoutput/oldselec_LM_v3/TTWGJ_2016_CR.root");
  //  f1 = new TFile("tmp.root");
  //    f1 = new TFile("TTGJets_2018_CR.root");
  //  f1 = new TFile("WGJets_2018_CR.root");
  //f1 = new TFile("TTWGJets_2018_CR.root");
  //  f1 = new TFile("TTWGJ_2018_CR.root");

   f2 = new TFile("Run2_METdata.root");
   //   f2 = new TFile("rootoutput/oldselec_LE_v3/Run2_METdata.root");


  // const char* str[9] = {"NJets_{=0}^{2-4}","NJets_{= 1}^{2-4}","NJets_{#geq 2}^{2-4}","NJets_{=0}^{5-6}","NJets_{= 1}^{5-6}","NJets_{#geq 2}^{5-6}","NJets_{=0}^{#geq 7}","NJets_{= 1}^{#geq 7}","NJets_{#geq 2}^{#geq 7}"};
  
  const char* str[6] = {"NJets_{=0}^{2-4}","NJets_{#geq 1}^{2-4}","NJets_{=0}^{5-6}","NJets_{#geq 1}^{5-6}","NJets_{=0}^{#geq 7}","NJets_{#geq 1}^{#geq 7}"};
  
  int xMin=-100000,xMax = 100000;

  TH1D *fail_accept,*fail_id,*fail_iso,*cr,*fake_photon,*sr,*data,*cr1;
  
  string varName="AllSBins_v7_1_CD";
  //  string varName="AllSBins_v7_CD";
  double nbin,bin0, bin1;
  TH1D *total;
  if(varName=="AllSBins_v7_CD"){
    fail_accept = (TH1D*)f1->Get("AllSBins_v7_CD_elec0_acc");
    fail_id     = (TH1D*)f1->Get("AllSBins_v7_CD_elec0_id");
    fail_iso    = (TH1D*)f1->Get("AllSBins_v7_CD_elec0_iso");
    cr          = (TH1D*)f1->Get("AllSBins_v7_CD_elec1");
    sr          = (TH1D*)f1->Get("AllSBins_v7_CD_elec0");
    nbin=31, bin0=1, bin1=32;
    total = new TH1D("total","Total = fail_id+fail_iso+fail_accept+1e_cr",nbin,bin0,bin1);
  }
  if(varName=="AllSBins_v7_1_CD"){
    fail_accept = (TH1D*)f1->Get("AllSBins_v7_1_CD_elec0_acc");
    fail_id     = (TH1D*)f1->Get("AllSBins_v7_1_CD_elec0_id");
    fail_iso    = (TH1D*)f1->Get("AllSBins_v7_1_CD_elec0_iso");
    cr          = (TH1D*)f1->Get("AllSBins_v7_1_CD_elec1");
    sr          = (TH1D*)f1->Get("AllSBins_v7_1_CD_elec0");
    nbin=16, bin0=1, bin1=17;
    total = new TH1D("total","Total = fail_id+fail_iso+fail_accept+1e_cr",nbin,bin0,bin1);
  }

 
  for(int i=bin0;i<=bin1;i++)
    { cout<<cr->GetBinContent(i)<<endl;}
  cout<<"The CR error in bin"<<endl;
  for(int i=bin0;i<=bin1;i++)
    { cout<<cr->GetBinError(i)<<endl;}
  cout<<"==============="<<endl;
  
  /* for(int i=1;i<=16;i++) */
  /*   { total->GetXaxis()->SetBinLabel(i,str[i-1]);} */
  /* total->Add(fail_accept); */
  /* total->Add(fail_id); */
  /* total->Add(fail_iso); */
  total->Add(sr);
  total->Add(cr);


  // Making new copy of hist with total divided

  //  fake_photon->Divide(total);
  /* fail_accept->Divide(total); */
  /* fail_id->Divide(total); */
  /* fail_iso->Divide(total); */
  sr->Divide(total);
  cr->Divide(total);
  
  THStack *stack = new THStack("Stack","stack hist");
  TCanvas *c1 = new TCanvas("stackhist","stackhist",1600,900);

  
  TPad *pad1 = new TPad("pad1","pad1",0,0.3,1,1);
  //  pad1->SetBottomMargin(0);

  TPad *pad2 = new TPad("pad2","pad2",0,0.0,1,0.3);
  pad2->SetTopMargin(0);
  pad2->SetBottomMargin(0.3);
  pad1->Draw();pad1->SetGridx();
  pad2->Draw();pad2->SetGridx();pad2->SetGridy();
  pad1->cd();
  
  gStyle->SetPalette(kOcean);
  sr->SetFillStyle(3008);
  sr->SetFillColor(kGreen);
  /* fail_accept->SetFillStyle(3008); */
  /* fail_accept->SetFillColor(kGreen); */
  /* fail_id->SetFillStyle(3021); */
  /* fail_id->SetFillColor(kRed); */
  /* fail_iso->SetFillStyle(3144); */
  /* fail_iso->SetFillColor(kBlue+3); */
  //  fake_photon->SetFillColor(kBlue-9);
  cr->SetFillColor(kGray);
  
  TLegend *legend = new TLegend(0.1,0.82,0.9,0.9);
   stack->Add(cr);
   stack->Add(sr);
  /* stack->Add(fail_accept); */
  /* stack->Add(fail_id); */
  /* stack->Add(fail_iso); */
  // stack->Add(fake_photon);
  //  stack->GetYAxis->SetRangeUser(0,1.2);
  stack->SetMaximum(1.1);
  stack->Draw("hist");
  // cr1->SetLineColor(kBlack);
  //  cr1->SetMarkerStyle(20);
  /* cr1->Draw("hist"); */
  
  if(varName=="AllSBins_v7_1_CD")
    {
      TLine *line1V6=new TLine( 1,0,  1,1);
      TLine *line2V6=new TLine( 3,0,  3,1);
      TLine *line3V6=new TLine( 5,0,  5,1);
      TLine *line4V6=new TLine( 7,0,  7,1);
      TLine *line5V6=new TLine( 9,0,  9,1);
      TLine *line6V6=new TLine( 11,0,  11,1);
      TLine *line7V6=new TLine( 13,0,  13,1);
      TLine *line8V6=new TLine( 15,0,  15,1);

      TLine *line1V5=new TLine( 2,0,  2,0.38);
      TLine *line2V5=new TLine( 4,0,  4,0.38);
      TLine *line3V5=new TLine( 6,0,  6,0.38);
      TLine *line4V5=new TLine( 8,0,  8,0.38);
      TLine *line5V5=new TLine( 10,0,  10,0.38);
      TLine *line6V5=new TLine( 12,0,  12,0.38);
      TLine *line7V5=new TLine( 14,0,  14,0.38);
      TLine *line8V5=new TLine( 16,0,  16,0.38);
  

      pad1->cd(); pad1->SetGridx(0); pad1->SetGridy(0);
      line1V6->Draw();      line2V6->Draw();  line3V6->Draw();
      line4V6->Draw();      line5V6->Draw(); line6V6->Draw();
      line7V6->Draw(); line8V6->Draw();
      line1V5->Draw();      line2V5->Draw();  line3V5->Draw();
      line4V5->Draw();      line5V5->Draw(); line6V5->Draw();
      line7V5->Draw(); line8V5->Draw();
  
      TArrow *arrow1 = new TArrow( 1, 0.4, 3, 0.4,0.01,"<|>");
      TArrow *arrow2 = new TArrow( 3, 0.4, 5, 0.4,0.01,"<|>");
      TArrow *arrow3 = new TArrow( 5, 0.4, 7, 0.4,0.01,"<|>");
      TArrow *arrow4 = new TArrow( 7, 0.4, 9, 0.4,0.01,"<|>");
      TArrow *arrow5 = new TArrow( 9, 0.4, 11, 0.4,0.01,"<|>");
      TArrow *arrow6 = new TArrow( 11,0.4, 13,0.4,0.01,"<|>");
      TArrow *arrow7 = new TArrow( 13,0.4, 15,0.4,0.01,"<|>");
      TArrow *arrow8 = new TArrow( 15,0.4, 17,0.4,0.01,"<|>");

      arrow1->Draw(); arrow2->Draw(); arrow3->Draw();
      arrow4->Draw(); arrow5->Draw(); arrow6->Draw();
      arrow7->Draw(); arrow8->Draw();

      TLatex Tl;
      Tl.SetTextSize(0.04);
      Tl.DrawLatex(2.0,0.47,"N^{ 0}_{ 2}");
      Tl.DrawLatex(4.0,0.47,"N^{ 0}_{ 3}");
      Tl.DrawLatex(6.0,0.47,"N^{ 0}_{ 4}");
      Tl.DrawLatex(8.0,0.47,"N^{ 0}_{ 5-6}");
      Tl.DrawLatex(10.0,0.47,"N^{ 0}_{ #geq7}");
      Tl.DrawLatex(12.0,0.47,"N^{ #geq1}_{ 2-4}");
      Tl.DrawLatex(14.0,0.47,"N^{ #geq1}_{ 5-6}");
      Tl.DrawLatex(16.0,0.47,"N^{ #geq1}_{ #geq7}");

      Tl.SetTextSize(0.023);
      Tl.DrawLatex(1.0,0.42,"100<MET<150");
      Tl.DrawLatex(2.1,0.42,"MET>=150");
      Tl.DrawLatex(3.0,0.42,"100<MET<150");
      Tl.DrawLatex(4.1,0.42,"MET>=150");
      Tl.DrawLatex(5.0,0.42,"100<MET<150");
      Tl.DrawLatex(6.1,0.42,"MET>=150");
      Tl.DrawLatex(7.0,0.42,"100<MET<150");
      Tl.DrawLatex(8.1,0.42,"MET>=150");
      Tl.DrawLatex(9.0,0.42,"100<MET<150");
      Tl.DrawLatex(10.1,0.42,"MET>=150");
      Tl.DrawLatex(11.0,0.42,"100<MET<150");
      Tl.DrawLatex(12.1,0.42,"MET>=150");
      Tl.DrawLatex(13.0,0.42,"100<MET<150");
      Tl.DrawLatex(14.1,0.42,"MET>=150");
      Tl.DrawLatex(15.0,0.42,"100<MET<150");
      Tl.DrawLatex(16.1,0.42,"MET>=150");
    }
  if(varName=="AllSBins_v7_CD")
    {
    TLine *line1V7=new TLine( 7,0,  7,1);
    TLine *line2V7=new TLine(12,0, 12,1);
    TLine *line3V7=new TLine(17,0, 17,1);
    TLine *line4V7=new TLine(22,0, 22,1);
    TLine *line5V7=new TLine(27,0, 27,1);

    pad1->cd(); pad1->SetGridx(0); pad1->SetGridy(0);
    line1V7->Draw();      line2V7->Draw();  line3V7->Draw();
    line4V7->Draw();      line5V7->Draw();

    TArrow *arrow1 = new TArrow( 1,0.4, 7,0.4,0.01,"<|>");
    TArrow *arrow2 = new TArrow( 7,0.4, 12,0.4,0.01,"<|>");
    TArrow *arrow3 = new TArrow(12,0.4, 17,0.4,0.01,"<|>");
    TArrow *arrow4 = new TArrow(17,0.4, 22,0.4,0.01,"<|>");
    TArrow *arrow5 = new TArrow(22,0.4, 27,0.4,0.01,"<|>");
    TArrow *arrow6 = new TArrow(27,0.4, 32,0.4,0.01,"<|>");

    arrow1->Draw(); arrow2->Draw(); arrow3->Draw();
    arrow4->Draw(); arrow5->Draw(); arrow6->Draw();

    TLatex Tl;
    Tl.SetTextSize(0.04);
    Tl.DrawLatex(3.5,0.5,"N^{ 0}_{ 2-4}");
    Tl.DrawLatex(9,0.5,"N^{ 0}_{ 5-6}");
    Tl.DrawLatex(14,0.5,"N^{ 0}_{ #geq7}");
    Tl.DrawLatex(19,0.5,"N^{ #geq1}_{ 2-4}");
    Tl.DrawLatex(24,0.5,"N^{ #geq1}_{ 5-6}");
    Tl.DrawLatex(29,0.5,"N^{ #geq1}_{ #geq7}");
    }

  legend->SetNColumns(4);
  legend->SetBorderSize(1);

  //  TLegend *legend = new TLegend(0.7,0.2,0.9,0.4);
  legend->AddEntry(cr,"1e CR","f");
  legend->AddEntry(sr,"0e SR","f");
  /* legend->AddEntry(fail_accept,"Fail Accept","f"); */
  /* legend->AddEntry(fail_id,"Fail Id","f"); */
  /* legend->AddEntry(fail_iso,"Fail Iso","f"); */
  //legend->AddEntry(fake_photon,"Fake photon","f");
  legend->SetTextSize(0.05);
  legend->Draw();


  pad2->cd();

  TH1D *TF = new TH1D("tf","Transfer factor",16,1,17);
  //  for(int i=1;i<=16;i++)
  //{ TF->GetXaxis()->SetBinLabel(i,str[i-1]);}
  /* TF->Add(fail_accept); */
  /* TF->Add(fail_id); */
  /* TF->Add(fail_iso); */
  TF->Add(sr);
  //TF->Add(fake_photon_1);
  TF->GetYaxis()->SetRangeUser(0,1.5);
  TF->Sumw2();
  TF->SetStats(0);
  TF->Divide(cr);
  TF->Draw("ep");
  TF->SetTitle(0);

  TF->GetXaxis()->SetTitle(0);
  TF->GetXaxis()->SetLabelSize(0.20);

  TF->GetYaxis()->SetTitle("Transfer factor");
  TF->GetYaxis()->SetTitleOffset(0.18);
  TF->GetYaxis()->SetTitleSize(0.13);
  TF->GetYaxis()->SetLabelSize(0.09);
  TF->SetLineWidth(3);
  //TF->SetMaximum(1.99);
  //TF->SetMinimum(0.01);

  if(varName=="AllSBins_v7_CD"){  
    TLine *line1V7=new TLine( 7,0,  7,1);
    TLine *line2V7=new TLine(12,0, 12,1);
    TLine *line3V7=new TLine(17,0, 17,1);
    TLine *line4V7=new TLine(22,0, 22,1);
    TLine *line5V7=new TLine(27,0, 27,1);

    pad2->cd(); pad2->SetGridx(0);// pad2->SetGridy(0);                                                                                       
    line1V7->Draw();      line2V7->Draw();  line3V7->Draw();
    line4V7->Draw();      line5V7->Draw();
    for(int i=1;i<=32;i++)
    { cout<<"The Transfer Factor in bin"<<i<<" = "<<TF->GetBinContent(i)<<" +- "<<TF->GetBinError(i)<<endl;}
  }  
  if(varName=="AllSBins_v7_1_CD"){  
    TLine *line1V7=new TLine( 1,0,  1,2);
    TLine *line2V7=new TLine( 3,0,  3,2);
    TLine *line3V7=new TLine( 5,0,  5,2);
    TLine *line4V7=new TLine( 7,0,  7,2);
    TLine *line5V7=new TLine( 9,0,  9,2);
    TLine *line6V7=new TLine( 11,0,  11,2);
    TLine *line7V7=new TLine( 13,0,  13,2);
    TLine *line8V7=new TLine( 15,0,  15,2);
    pad2->cd(); pad2->SetGridx(0);// pad2->SetGridy(0);
    line1V7->Draw();      line2V7->Draw();  line3V7->Draw();
    line4V7->Draw();      line5V7->Draw(); line6V7->Draw();
    line7V7->Draw(); line8V7->Draw();

  }
  cout<<"==============="<<endl;
  /* for(int i=1;i<=17;i++) */
  /*   { cout<<TF->GetBinContent(i)<<" +- "<<TF->GetBinError(i)<<endl;} */
  for(int i=bin0;i<=bin1;i++)
    { cout<<TF->GetBinContent(i)<<endl;}
  cout<<"The Transfer Factor error in bin"<<endl;
  for(int i=bin0;i<=bin1;i++)
    { cout<<TF->GetBinError(i)<<endl;}
  
}

