void plotratio_LE_newselec()
{
  TFile *f1;
  // f1 = new TFile("Run2017_METdata.root");
  //  f1 = new TFile("Run2018_METdata.root"); 
  //  f1 = new TFile("Run2018_METdata.root");
  //  f1 = new TFile("Run2018_METdata.root");
  //  f1 = new TFile("rootoutput/newselec_LM_v2/TTWGJ_CR.root");
  //  f1 = new TFile("rootoutput/newselec_LM_v3/TTWGJ_CR.root");
  //  f1 = new TFile("rootoutput/newselec_LE_v3/TTWGJ_2018_CR.root");
  f1 = new TFile("rootoutput/newselec_LM_v3/TTWGJ_2018_CR.root");
  //   f1 = new TFile("rootoutput/newselec_LE_v2/TTWGJ_CR.root");
  // f1 = new TFile("TTGJets_2016_CR.root");
  //f1 = new TFile("WGJets_2016_CR.root");
  //  f1 = new TFile("TTWGJ_2016_CR.root");
  //  //  f1 = new TFile("TTJets_2016_CR.root");
  //  f1 = new TFile("TTJets_2017_CR.root");
  //  f1 = new TFile("WJets_2016_CR.root");
  // f1 = new TFile("TTWGJ_CR.root");
  //    f1 = new TFile("TTGJets_2017_CR.root");
  //  f1 = new TFile("WGJets_2017_CR.root");
  //   f1 = new TFile("TTWGJets_2017_CR.root");
  //  f1 = new TFile("TTWGJets_CR.root");
  //f1 = new TFile(fname);
  //  f1 = new TFile("rootoutput/newselec_LM_v3/Run2018_METdata_CR.root");
  //    f1 = new TFile("TTGJets_2018_CR.root");
  //  f1 = new TFile("WGJets_2018_CR.root");
  //  f1 = new TFile("TTWGJets_2018_CR.root");
  //  f1 = new TFile("TTWGJ_2018_CR.root");


  
   int xMin=-100000,xMax = 100000;

  TH1D *fail_accept,*fail_id,*fail_iso,*cr,*fake_photon,*sr;
  
  TFile *fout =new TFile("Run2018_TF_LM_v6_CD.root","recreate");
  // TFile *fout =new TFile("Run2_TF_LE_v6_CD_SP.root","recreate");
  //  TFile *fout =new TFile("Run2_TF_LE_v6_CD.root","recreate");
  // TFile *fout =new TFile("Run2018_TF_LE_v6_CD.root","recreate");
  //  TFile *fout =new TFile("tmp.root","recreate");
  //  TFile *fout =new TFile("Run2_TF_LE_v2.root","recreate");
  //  string varName="AllSBins_v7_CD_SP";
  string varName="AllSBins_v6_CD";
  //string varName="AllSBins_v6_CD_SP";
  //  string varName="AllSBins_v6_CD_closure";
  double nbin,bin0, bin1;
  TH1D *total;
  if(varName=="AllSBins_v6_CD_SP"){
    fail_accept = (TH1D*)f1->Get("AllSBins_v6_CD_SP_elec0_acc");
    fail_id     = (TH1D*)f1->Get("AllSBins_v6_CD_SP_elec0_id");
    //    cr          = (TH1D*)f1->Get("AllSBins_v6_CD_SP_elec1");
    cr          = (TH1D*)f1->Get("AllSBins_v6_CD_SP_elec1_closure");
    sr          = (TH1D*)f1->Get("AllSBins_v6_CD_SP_elec0");
    nbin=37, bin0=1, bin1=38;
   total = new TH1D("total","Total = fail_id+fail_iso+fail_accept+1e_cr",nbin,bin0,bin1);

  }
  if(varName=="AllSBins_v7_CD_SP"){
    fail_accept = (TH1D*)f1->Get("AllSBins_v7_CD_SP_elec0_acc");
    fail_id     = (TH1D*)f1->Get("AllSBins_v7_CD_SP_elec0_id");
    cr          = (TH1D*)f1->Get("AllSBins_v7_CD_SP_elec1");
    sr          = (TH1D*)f1->Get("AllSBins_v7_CD_SP_elec0");
    nbin=31, bin0=0.5, bin1=31.5;
    total = new TH1D("total","Total = fail_id+fail_iso+fail_accept+1e_cr",nbin,bin0,bin1);
  }
  if(varName=="AllSBins_v6_CD"){
    fail_accept = (TH1D*)f1->Get("AllSBins_v6_CD_elec0_acc");
    fail_id     = (TH1D*)f1->Get("AllSBins_v6_CD_elec0_id");
    cr          = (TH1D*)f1->Get("AllSBins_v6_CD_elec1");
    //cr          = (TH1D*)f1->Get("AllSBins_v6_CD_elec1_closure");
    sr          = (TH1D*)f1->Get("AllSBins_v6_CD_elec0");
    nbin=8, bin0=1, bin1=9;
    total = new TH1D("total","Total = fail_id+fail_accept+1e_cr",nbin,bin0,bin1);

  }  

  for(int i=1;i<=9;i++)
    { cout<<cr->GetBinContent(i)<<endl;}
  cout<<"The CR error in bin"<<endl;
  for(int i=1;i<=9;i++)
    { cout<<cr->GetBinError(i)<<endl;}
  cout<<"==============="<<endl;
  
  total->Add(sr);
  total->Add(cr);


  // Making new copy of hist with total divided
  sr->Divide(total);
  cr->Divide(total);
  
  THStack *stack = new THStack("Stack","stack hist");
  TCanvas *c1 = new TCanvas("stackhist","stackhist",1600,900);

  
  TPad *pad1 = new TPad("pad1","pad1",0,0.3,1,1);
  //  pad1->SetBottomMargin(0);

  TPad *pad2 = new TPad("pad1","pad1",0,0.0,1,0.3);
  pad2->SetTopMargin(0);
  pad2->SetBottomMargin(0.3);
  pad1->Draw();pad1->SetGridx();
  pad2->Draw();pad2->SetGridx();pad2->SetGridy();
  pad1->cd();
  
  gStyle->SetPalette(kOcean);
  sr->SetFillStyle(3008);
  sr->SetFillColor(kGreen);
  cr->SetFillColor(kGray);
  
  TLegend *legend = new TLegend(0.1,0.82,0.9,0.9);
  stack->Add(cr);
  stack->Add(sr);
  stack->SetMaximum(1.1);
  stack->Draw("hist");

  if(varName=="AllSBins_v7_CD_SP"){
    TLine *line1V7=new TLine( 6.5,0,  6.5,1);
    TLine *line2V7=new TLine(11.5,0, 11.5,1);
    TLine *line3V7=new TLine(16.5,0, 16.5,1);
    TLine *line4V7=new TLine(21.5,0, 21.5,1);
    TLine *line5V7=new TLine(26.5,0, 26.5,1);

    pad1->cd(); pad1->SetGridx(0); pad1->SetGridy(0);
    line1V7->Draw();      line2V7->Draw();  line3V7->Draw();
    line4V7->Draw();      line5V7->Draw();

    TArrow *arrow1 = new TArrow( 0.5,0.4, 6.5,0.4,0.01,"<|>");
    TArrow *arrow2 = new TArrow( 6.5,0.4,11.5,0.4,0.01,"<|>");
    TArrow *arrow3 = new TArrow(11.5,0.4,16.5,0.4,0.01,"<|>");
    TArrow *arrow4 = new TArrow(16.5,0.4, 21.5,0.4,0.01,"<|>");
    TArrow *arrow5 = new TArrow(21.5,0.4, 26.5,0.4,0.01,"<|>");
    TArrow *arrow6 = new TArrow(26.5,0.4, 31.5,0.4,0.01,"<|>");
    
    arrow1->Draw(); arrow2->Draw(); arrow3->Draw();
    arrow4->Draw(); arrow5->Draw(); arrow6->Draw();

    TLatex Tl;
    Tl.SetTextSize(0.04);
    Tl.DrawLatex(3.,0.47,"N^{ 0}_{ 2-4}");
    Tl.DrawLatex(8.5,0.47,"N^{ 0}_{ 5-6}");
    Tl.DrawLatex(13.5,0.47,"N^{ 0}_{ #geq7}");
    Tl.DrawLatex(18.5,0.47,"N^{ #geq1}_{ 2-4}");
    Tl.DrawLatex(23.5,0.47,"N^{ #geq1}_{ 5-6}");
    Tl.DrawLatex(28.5,0.47,"N^{ #geq1}_{ #geq7}");
  }

  if(varName=="AllSBins_v6_CD_SP"){
    TLine *line1V6=new TLine( 7.5,0,  7.5,1);
    TLine *line2V6=new TLine(13.5,0, 13.5,1);
    TLine *line3V6=new TLine(19.5,0, 19.5,1);
    TLine *line4V6=new TLine(25.5,0, 25.5,1);
    TLine *line5V6=new TLine(31.5,0, 31.5,1);
    pad1->cd(); pad1->SetGridx(0); pad1->SetGridy(0);
    line1V6->Draw();      line2V6->Draw();  line3V6->Draw();
    line4V6->Draw();      line5V6->Draw();

    TArrow *arrow1 = new TArrow( 0.5,0.4, 7.5,0.4,0.01,"<|>");
    TArrow *arrow2 = new TArrow( 7.5,0.4,13.5,0.4,0.01,"<|>");
    TArrow *arrow3 = new TArrow(13.5,0.4,19.5,0.4,0.01,"<|>");
    TArrow *arrow4 = new TArrow(19.5,0.4, 25.5,0.4,0.01,"<|>");
    TArrow *arrow5 = new TArrow(25.5,0.4, 31.5,0.4,0.01,"<|>");
    TArrow *arrow6 = new TArrow(31.5,0.4, 36.5,0.4,0.01,"<|>");

    arrow1->Draw(); arrow2->Draw(); arrow3->Draw();
    arrow4->Draw(); arrow5->Draw(); arrow6->Draw();
    TLatex Tl;
    Tl.SetTextSize(0.04);
    Tl.DrawLatex(4.0,0.47,"N^{ 0}_{ 2-4}");
    Tl.DrawLatex(10.5,0.47,"N^{ 0}_{ 5-6}");
    Tl.DrawLatex(16.5,0.47,"N^{ 0}_{ #geq7}");
    Tl.DrawLatex(22.5,0.47,"N^{ #geq1}_{ 2-4}");
    Tl.DrawLatex(27.5,0.47,"N^{ #geq1}_{ 5-6}");
    Tl.DrawLatex(33.5,0.47,"N^{ #geq1}_{ #geq7}");
  }


  if(varName=="AllSBins_v6_CD"){

    TLine *line1V6=new TLine( 1,0,  1,1);
    TLine *line2V6=new TLine( 2,0,  2,1);
    TLine *line3V6=new TLine( 3,0,  3,1);
    TLine *line4V6=new TLine( 4,0,  4,1);
    TLine *line5V6=new TLine( 5,0,  5,1);
    TLine *line6V6=new TLine( 6,0,  6,1);
    TLine *line7V6=new TLine( 7,0,  7,1);
    TLine *line8V6=new TLine( 8,0,  8,1);

    pad1->cd(); pad1->SetGridx(0); pad1->SetGridy(0);
    line1V6->Draw();      line2V6->Draw();  line3V6->Draw();
    line4V6->Draw();      line5V6->Draw(); line6V6->Draw();
    line7V6->Draw(); line8V6->Draw();
  
    TArrow *arrow1 = new TArrow( 1, 0.4, 2, 0.4,0.01,"<|>");
    TArrow *arrow2 = new TArrow( 2, 0.4, 3, 0.4,0.01,"<|>");
    TArrow *arrow3 = new TArrow( 3, 0.4, 4, 0.4,0.01,"<|>");
    TArrow *arrow4 = new TArrow( 4, 0.4, 5, 0.4,0.01,"<|>");
    TArrow *arrow5 = new TArrow( 5, 0.4, 6, 0.4,0.01,"<|>");
    TArrow *arrow6 = new TArrow( 6,0.4, 7,0.4,0.01,"<|>");
    TArrow *arrow7 = new TArrow( 7,0.4, 8,0.4,0.01,"<|>");
    TArrow *arrow8 = new TArrow( 8,0.4, 9,0.4,0.01,"<|>");

    arrow1->Draw(); arrow2->Draw(); arrow3->Draw();
    arrow4->Draw();
    arrow5->Draw(); arrow6->Draw();
    arrow7->Draw(); arrow8->Draw();

    TLatex Tl;
    Tl.SetTextSize(0.04);
    Tl.DrawLatex(1.5,0.47,"N^{ 0}_{ 2}");
    Tl.DrawLatex(2.5,0.47,"N^{ 0}_{ 3}");
    Tl.DrawLatex(3.5,0.47,"N^{ 0}_{ 4}");
    Tl.DrawLatex(4.5,0.47,"N^{ 0}_{ 5-6}");
    Tl.DrawLatex(5.5,0.47,"N^{ 0}_{ #geq7}");
    Tl.DrawLatex(6.5,0.47,"N^{ #geq1}_{ 2-4}");
    Tl.DrawLatex(7.5,0.47,"N^{ #geq1}_{ 5-6}");
    Tl.DrawLatex(8.5,0.47,"N^{ #geq1}_{ #geq7}");
  }
  legend->SetNColumns(4);
  legend->SetBorderSize(1);


  legend->AddEntry(cr,"1e CR","f");
  legend->AddEntry(sr,"0e SR","f");
  legend->SetTextSize(0.05);
  legend->Draw();


  pad2->cd();

  TH1D *TF = new TH1D("tf","Transfer factor",nbin,bin0,bin1);
  TF->Add(sr);
  TF->GetYaxis()->SetRangeUser(0.5,1.5);
  TF->Sumw2();
  TF->SetStats(0);
  TF->Divide(cr);
  TF->Draw("ep");
  TF->SetTitle(0);

  fout->cd();
  TF->Write();
  
  TF->GetXaxis()->SetTitle(0);
  TF->GetXaxis()->SetLabelSize(0.20);

  TF->GetYaxis()->SetTitle("Transfer factor");
  TF->GetYaxis()->SetTitleOffset(0.18);
  TF->GetYaxis()->SetTitleSize(0.13);
  TF->GetYaxis()->SetLabelSize(0.09);
  TF->SetLineWidth(3);

  if(varName=="AllSBins_v6_CD"){

    TLine *line1V7=new TLine( 1,0,  1,2);
    TLine *line2V7=new TLine( 2,0,  2,2);
    TLine *line3V7=new TLine( 3,0,  3,2);
    TLine *line4V7=new TLine( 4,0,  4,2);
    TLine *line5V7=new TLine( 5,0,  5,2);
    TLine *line6V7=new TLine( 6,0,  6,2);
    TLine *line7V7=new TLine( 7,0,  7,2);
    TLine *line8V7=new TLine( 8,0,  8,2);


    pad2->cd(); pad2->SetGridx(0);// pad2->SetGridy(0);
    line1V7->Draw();      line2V7->Draw();  line3V7->Draw();
    line4V7->Draw();      line5V7->Draw(); line6V7->Draw();
    line7V7->Draw(); line8V7->Draw();
  }
  if(varName=="AllSBins_v6_CD_SP"){
    TLine *line1V6=new TLine( 7.5,0,  7.5,2);
    TLine *line2V6=new TLine(13.5,0, 13.5,2);
    TLine *line3V6=new TLine(19.5,0, 19.5,2);
    TLine *line4V6=new TLine(25.5,0, 25.5,2);
    TLine *line5V6=new TLine(31.5,0, 31.5,2);
    pad2->cd(); pad2->SetGridx(0);// pad1->SetGridy(0);
    line1V6->Draw();      line2V6->Draw();  line3V6->Draw();
    line4V6->Draw();      line5V6->Draw();

  }

  if(varName=="AllSBins_v7_CD_SP"){
    TLine *line1V7=new TLine( 6.5,0,  6.5,1);
    TLine *line2V7=new TLine(11.5,0, 11.5,1);
    TLine *line3V7=new TLine(16.5,0, 16.5,1);
    TLine *line4V7=new TLine(21.5,0, 21.5,1);
    TLine *line5V7=new TLine(26.5,0, 26.5,1);

    pad2->cd(); pad2->SetGridx(0); //pad1->SetGridy(0);
    line1V7->Draw();      line2V7->Draw();  line3V7->Draw();
    line4V7->Draw();      line5V7->Draw();
  }
  cout<<"The TF content in bin"<<endl;
  for(int i=bin0;i<=bin1;i++)
    { cout<<TF->GetBinContent(i)<<endl;}
  cout<<"The Transfer Factor error in bin"<<endl;
  for(int i=bin0;i<=bin1;i++)
    { cout<<TF->GetBinError(i)<<endl;}
  cout<<"==============="<<endl;

}

