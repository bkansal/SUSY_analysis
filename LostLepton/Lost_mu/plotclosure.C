void plotclosure()
{
  TFile *f1, *f2,*f3;

  //  f1 = new TFile("rootoutput/newselec_LE_v3/Run2018_METdata.root");
  //  f1 = new TFile("TTWGJ_2016_CR.root");

  //  f1 = new TFile("rootoutput/newselec_LM_v3/Run2_METdata.root");
  //   f1 = new TFile("rootoutput/oldselec_LM_v2/TTWGJ_CR.root");
   //  f2 = new TFile("Run2016_TF_LE_v6_CD.root");
  //  f2 = new TFile("Run2_TF_LE_v6_CD_SP.root");
  //   f1 = new TFile("Run2_METdata.root");
  f2 = new TFile("rootoutput/newselec_LE_v3/Run2016_METdata_CR.root");
  f1 = new TFile("rootoutput/newselec_LE_v3/TTWGJ_2016_CR.root");
  // f1 = new TFile("rootoutput/newselec_LE_v3/WJets_CR.root");
  /* f3 = new TFile("rootoutput/newselec_LE_v3/TTWGJ_SR.root"); */
  //f = new TFile("rootoutput/newselec_LM_v3/WJets_CR.root");
  /* f1 = new TFile("rootoutput/tmp/TTWGJ_CR.root"); */
  /* f2 = new TFile("rootoutput/tmp/Run2_METdata_CR.root"); */

  /* f1 = new TFile("rootoutput/newselec_LM_v3/TTWGJ_2016_CR.root"); */
  /* f2 = new TFile("rootoutput/newselec_LM_v3/Run2016_METdata_CR.root"); */

  
  double xmin,xmax,bin,xmin_,xmax_;
  double ymin=0.5 , ymax=1.5, ymin_=0.0001 , ymax_=1000;

  TH1D *cr,*sr,*tf,*pred_sr;
  
  //  string varName="AllSBins_v7_CD_SP";
  // TString varName="AllSBins_v6_CD_SP";
  // string varName="AllSBins_v6_CD";
  //  string varName="AllSBins_v7_CD";
  //  TString varName="AllSBins_v6_CD_EW_50bin";
  TString varName="MET";
  //  TString varName="BestPhotonPt";
  //TString varName="nJets";
  bool ExpvsPred,DatavsMC;
  ExpvsPred=false,DatavsMC=true;
  //  ExpvsPred=true,DatavsMC=false;
  
  double nbin,bin0, bin1,yset_;
  TH1D *total;
  int rebin=1;
  if(varName=="AllSBins_v6_CD_SP"){
    pred_sr          = (TH1D*)f1->Get("AllSBins_v6_CD_SP_elec1_closure");
    sr          = (TH1D*)f1->Get("AllSBins_v6_CD_SP_elec0");
    cr          = (TH1D*)f1->Get("AllSBins_v6_CD_SP_elec1");
    //    xmin=0,xmax = 37,bin=40;
    xmin=-100000,xmax = 100000,xmin_=0,xmax_=37;
    ymin=-0.5 , ymax=2.5, ymin_=0.0001 , ymax_=1000;
  }
  else if(varName=="AllSBins_v7_CD_SP"){
    cr          = (TH1D*)f1->Get("AllSBins_v7_CD_SP_elec1");
    sr          = (TH1D*)f1->Get("AllSBins_v7_CD_SP_elec1");
  }
 else if(varName=="AllSBins_v7_CD"){
    cr          = (TH1D*)f1->Get("AllSBins_v7_CD_elec1");
    sr          = (TH1D*)f1->Get("AllSBins_v7_CD_elec0");
  }
  else if(varName=="AllSBins_v6_CD"){
    //cr          = (TH1D*)f1->Get("AllSBins_v6_CD_elec1");
    sr          = (TH1D*)f1->Get("AllSBins_v6_CD_elec0");
    pred_sr     = (TH1D*)f1->Get("AllSBins_v6_CD_elec1_closure");
    xmin_=1,xmax_=8,xmin=1,xmax = 9,bin=8;
   ymin=0.5 , ymax=1.5, ymin_=0.01 , ymax_=1000;
  }  
 else if(varName=="AllSBins_v6_CD_EW_50bin"){
    cr          = (TH1D*)f1->Get("AllSBins_v6_CD_EW_50bin_elec1");
    if(DatavsMC)
      {
	sr          = (TH1D*)f1->Get("AllSBins_v6_CD_EW_50bin_elec1");
	pred_sr     = (TH1D*)f2->Get("AllSBins_v6_CD_EW_50bin_elec1");
      }
    if(ExpvsPred)
      {
	sr          = (TH1D*)f1->Get("AllSBins_v6_CD_EW_50bin_elec0");
	pred_sr     = (TH1D*)f1->Get("AllSBins_v6_CD_EW_50bin_elec1_closure");
      }
    bin=51.5;
    //    xmin=-100000,xmax = 100000,xmin_=0,xmax_=50;
    xmin=-1,xmax = 50,xmin_=-1,xmax_=50;
    ymin=0 , ymax=2, ymin_=0.005 , ymax_=100000, yset_=200;
  }
 else if(varName=="BestPhotonPt" || varName=="MET" )
    {
    cr          = (TH1D*)f1->Get(varName);
    sr          = (TH1D*)f1->Get(varName);
    pred_sr     = (TH1D*)f2->Get(varName);
    xmin_=200,xmax_=1200,xmin=200,xmax=1200;
    rebin=10;
    pred_sr->Rebin(rebin);
    sr->Rebin(rebin);
    ymin=0 , ymax=2.6, ymin_=0.01 , ymax_=10000000;
    pred_sr->GetXaxis()->SetRangeUser(xmin,xmax);
    sr->GetXaxis()->SetRangeUser(xmin,xmax);
    }
 else if(varName=="nJets" )
    {
    cr          = (TH1D*)f1->Get(varName);
    sr          = (TH1D*)f1->Get(varName);
    pred_sr     = (TH1D*)f2->Get(varName);
    xmin_=2,xmax_=11,xmin=2,xmax=11;
    rebin=1;
    ymin=0 , ymax=2.6, ymin_=0.01 , ymax_=1000000;
    pred_sr->Rebin(rebin);
    sr->Rebin(rebin);
    pred_sr->GetXaxis()->SetRangeUser(xmin,xmax);
    sr->GetXaxis()->SetRangeUser(xmin,xmax);
    }
  /* for(int i=xmin_;i<=xmax_;i++) */
  /*   { cout<<cr->GetBinContent(i)<<endl;} */
  /* cout<<"The cr error in bin"<<endl; */
  /* for(int i=xmin_;i<=xmax_;i++) */
  /*   { cout<<cr->GetBinError(i)<<endl;} */
  /* cout<<"==============="<<endl; */

  for(int i=0;i<=53;i++)
    { cout<<i<<" , CR : "<<cr->GetBinContent(i)<<" , Pred : SR : "<<pred_sr->GetBinContent(i)<<" ,  SR : "<<sr->GetBinContent(i)<<endl;}

  cout<<"==============="<<endl;
  gStyle->SetOptStat(0);

  TPad *pad1 = new TPad("pad1","pad1",0,0.3,1,1);
  //  pad1->SetBottomMargin(0);
  pad1->SetBottomMargin(0.3);

  pad1->Draw();pad1->SetGridx();

  pad1->cd();
  pad1->SetLogy();
  pred_sr->GetXaxis()->SetRangeUser(xmin,xmax);
  sr->GetXaxis()->SetRangeUser(xmin,xmax);
  pred_sr->SetLabelSize(0.01);
  sr->SetLabelSize(0.01);
  sr->GetYaxis()->SetRangeUser(ymin_,ymax_);
  pred_sr->GetYaxis()->SetRangeUser(ymin_,ymax_);
  pred_sr->SetMarkerStyle(20);
  pred_sr->SetMarkerSize(0.7);
  pred_sr->SetMarkerColor(kRed);
  pred_sr->SetLineColor(kRed);
  sr->SetMarkerStyle(20);
  sr->SetMarkerSize(0.7);
  sr->SetMarkerColor(kBlue);
  sr->SetLineColor(kBlue);

  //  pred_sr->SetLineStyle(kBlue);  
  pred_sr->Draw("e1");
  sr->Draw("e1 same");

  if(varName=="AllSBins_v6_CD_EW_50bin"  ){
    TLine *line1V6=new TLine( 6.5,ymin_,  6.5,ymax_);
    TLine *line2V6=new TLine(12.5,ymin_, 12.5,ymax_);
    TLine *line3V6=new TLine(18.5,ymin_, 18.5,ymax_);
    TLine *line4V6=new TLine(24.5,ymin_, 24.5,ymax_);
    TLine *line5V6=new TLine(30.5,ymin_, 30.5,ymax_);
    TLine *line6V6=new TLine(36.5,ymin_, 36.5,ymax_);
    TLine *line7V6=new TLine(43.5,ymin_, 43.5,ymax_);
    
    pad1->cd(); pad1->SetGridx(0); pad1->SetGridy(0);

    line1V6->Draw();      line2V6->Draw();  line3V6->Draw();
    line4V6->Draw();      line5V6->Draw();
    line6V6->Draw();      line7V6->Draw();
    TArrow *arrow1 = new TArrow( -0.5,yset_, 6.5,yset_,0.01,"<|>");
    TArrow *arrow2 = new TArrow( 6.5,yset_,12.5,yset_,0.01,"<|>");
    TArrow *arrow3 = new TArrow(12.5,yset_,18.5,yset_,0.01,"<|>");
    TArrow *arrow4 = new TArrow(18.5,yset_, 24.5,yset_,0.01,"<|>");
    TArrow *arrow5 = new TArrow(24.5,yset_, 30.5,yset_,0.01,"<|>");
    TArrow *arrow6 = new TArrow(30.5,yset_, 36.5,yset_,0.01,"<|>");
    TArrow *arrow7 = new TArrow(36.5,yset_, 43.5,yset_,0.01,"<|>");
    TArrow *arrow8 = new TArrow(43.5,yset_, 50.5,yset_,0.01,"<|>");

    arrow1->Draw(); arrow2->Draw(); arrow3->Draw();
    arrow4->Draw(); arrow5->Draw(); arrow6->Draw();
    arrow7->Draw(); arrow8->Draw();
    TLatex Tl;
    Tl.SetTextSize(0.04);
    Tl.DrawLatex(3.0,2*yset_,"N^{ 0}_{ 2-4}");
    Tl.DrawLatex(9.5,2*yset_,"N^{ 0}_{ 5-6}");
    Tl.DrawLatex(15.5,2*yset_,"N^{ 0}_{ #geq7}");
    Tl.DrawLatex(21.5,2*yset_,"N^{ #geq1}_{ 2-4}");
    Tl.DrawLatex(26.5,2*yset_,"N^{ #geq1}_{ 5-6}");
    Tl.DrawLatex(32.5,2*yset_,"N^{ #geq1}_{ #geq7}");
    Tl.SetTextSize(0.03);
    Tl.DrawLatex(37.5,2*yset_,"EW : W tag");
    Tl.DrawLatex(44.5,2*yset_,"EW : H tag");
  }
  
  if(varName=="AllSBins_v7_CD_SP"){
    TLine *line1V7=new TLine( 7,0,  6.5,1000);
    TLine *line2V7=new TLine(12,0, 11.5,1000);
    TLine *line3V7=new TLine(16.5,0, 16.5,1000);
    TLine *line4V7=new TLine(21.5,0, 21.5,1000);
    TLine *line5V7=new TLine(26.5,0, 26.5,1000);

    pad1->cd(); pad1->SetGridx(0); pad1->SetGridy(0);
    line1V7->Draw();      line2V7->Draw();  line3V7->Draw();
    line4V7->Draw();      line5V7->Draw();

    TArrow *arrow1 = new TArrow( -0.5,0.4, 6.5,0.4,0.01,"<|>");
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
  if(varName=="AllSBins_v7_CD"){
    TLine *line1V7=new TLine( 7,0,  7,100);
    TLine *line2V7=new TLine(12,0, 12,100);
    TLine *line3V7=new TLine(17,0, 17,100);
    TLine *line4V7=new TLine(22,0, 22,100);
    TLine *line5V7=new TLine(27,0, 27,100);

    pad1->cd(); pad1->SetGridx(0); pad1->SetGridy(0);
    line1V7->Draw();      line2V7->Draw();  line3V7->Draw();
    line4V7->Draw();      line5V7->Draw();

    TArrow *arrow1 = new TArrow( -0.5,0.4, 7,0.4,0.01,"<|>");
    TArrow *arrow2 = new TArrow(7,0.4,12,0.4,0.01,"<|>");
    TArrow *arrow3 = new TArrow(12,0.4,17,0.4,0.01,"<|>");
    TArrow *arrow4 = new TArrow(17,0.4, 22,0.4,0.01,"<|>");
    TArrow *arrow5 = new TArrow(22,0.4, 27,0.4,0.01,"<|>");
    TArrow *arrow6 = new TArrow(27,0.4, 32,0.4,0.01,"<|>");
    
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
    TLine *line1V6=new TLine( 6.5,0,  6.5,100);
    TLine *line2V6=new TLine(12.5,0, 12.5,100);
    TLine *line3V6=new TLine(18.5,0, 18.5,100);
    TLine *line4V6=new TLine(24.5,0, 24.5,100);
    TLine *line5V6=new TLine(30.5,0, 30.5,100);
    pad1->cd(); pad1->SetGridx(0); pad1->SetGridy(0);
    line1V6->Draw();      line2V6->Draw();  line3V6->Draw();
    line4V6->Draw();      line5V6->Draw();

    TArrow *arrow1 = new TArrow( 0.5,0.1, 6.5,0.1,0.01,"<|>");
    TArrow *arrow2 = new TArrow( 6.5,0.1,12.5,0.1,0.01,"<|>");
    TArrow *arrow3 = new TArrow(12.5,0.1,18.5,0.1,0.01,"<|>");
    TArrow *arrow4 = new TArrow(18.5,0.1, 24.5,0.1,0.01,"<|>");
    TArrow *arrow5 = new TArrow(24.5,0.1, 30.5,0.1,0.01,"<|>");
    TArrow *arrow6 = new TArrow(30.5,0.1, 35.5,0.1,0.01,"<|>");

    arrow1->Draw(); arrow2->Draw(); arrow3->Draw();
    arrow4->Draw(); arrow5->Draw(); arrow6->Draw();
    TLatex Tl;
    Tl.SetTextSize(0.04);
    Tl.DrawLatex(2.0,0.007,"N^{ 0}_{ 2-4}");
    Tl.DrawLatex(8.5,0.007,"N^{ 0}_{ 5-6}");
    Tl.DrawLatex(14.5,0.007,"N^{ 0}_{ #geq7}");
    Tl.DrawLatex(20.5,0.007,"N^{ #geq1}_{ 2-4}");
    Tl.DrawLatex(25.5,0.007,"N^{ #geq1}_{ 5-6}");
    Tl.DrawLatex(31.5,0.007,"N^{ #geq1}_{ #geq7}");
  }


  if(varName=="AllSBins_v6_CD"){

    TLine *line1V6=new TLine( 1,0,  1,1000);
    TLine *line2V6=new TLine( 2,0,  2,1000);
    TLine *line3V6=new TLine( 3,0,  3,1000);
    TLine *line4V6=new TLine( 4,0,  4,1000);
    TLine *line5V6=new TLine( 5,0,  5,1000);
    TLine *line6V6=new TLine( 6,0,  6,1000);
    TLine *line7V6=new TLine( 7,0,  7,1000);
    TLine *line8V6=new TLine( 8,0,  8,1000);

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
  TLegend *legend = new TLegend(0.4,0.76,0.9,0.9);
  legend->SetNColumns(1);
  legend->SetBorderSize(1);


  if(DatavsMC)
    {
      legend->AddEntry(pred_sr,"Data : Lost Lepton (CR region)","lp");
      legend->AddEntry(sr,"MC : Lost Lepton (CR region)","lp");
    }

  if(ExpvsPred)
    {
      legend->AddEntry(sr,"Exp : (0e + photon )","lp");
      legend->AddEntry(pred_sr,"Pred : TF x (1e + photon)","lp");
      /* legend->AddEntry(sr,"Exp : (0mu,had tau + photon )","lp"); */
      /* legend->AddEntry(pred_sr,"Pred : TF x (1mu + photon)","lp"); */
    }
  legend->SetTextSize(0.04);

  legend->Draw();

  TH1D *h4 = (TH1D*)pred_sr->Clone("h4");
  TH1D *h3 = (TH1D*)sr->Clone("h3");

  TPad *pad2 = new TPad("pad1","pad1",0,0.0,1,0.3);
  pad2->Draw();
  pad2->SetTopMargin(0);
  pad2->SetBottomMargin(0.3);
  pad2->cd();
  pad2->SetGrid(1);

  h3->GetYaxis()->SetRangeUser(0.5,1.5);
  /* h3->GetXaxis()->SetRangeUser(xmin,xmax); */
  /* h4->GetXaxis()->SetRangeUser(xmin,xmax); */

  h3->SetLineColor(kGreen);
  h3->SetMinimum(ymin);  // Define Y ..                                                                                                       
  h3->SetMaximum(ymax); // .. range                                                                                                           
  h3->Sumw2();
  h3->SetStats(0);      // No statistics on lower plot                                                                                        
  h3->Divide(h4);
  h3->SetMarkerStyle(20);
  h3->SetMarkerSize(0.6);
  // gStyle->SetOptStat(0);                                                                                                                   
  h3->Draw("ep");       // Draw the ratio plot                                                                                                

  h3->SetTitle(0);

  h3->GetXaxis()->SetTitle(0);
  h3->GetXaxis()->SetLabelSize(0.20);

  if(ExpvsPred) h3->GetYaxis()->SetTitle("Exp/Pred");
  if(DatavsMC) h3->GetYaxis()->SetTitle("Data/MC");
  h3->GetYaxis()->SetTitleOffset(0.18);
  h3->GetYaxis()->SetTitleSize(0.13);
  h3->GetYaxis()->SetLabelSize(0.09);
  
  TLine *line= new TLine(xmin_,1.0,xmax_,1.0);
  
  line->SetLineColor(1);
  line->SetLineWidth(2);
  line->Draw();

  
  
  /* TH1D *TF = new TH1D("tf","Transfer factor",nbin,bin0,bin1); */
  /* TF->Add(sr); */
  /* TF->GetYaxis()->SetRangeUser(0,2); */
  /* TF->Sumw2(); */
  /* TF->SetStats(0); */
  /* TF->Divide(cr); */
  /* TF->Draw("ep"); */
  /* TF->SetTitle(0); */

  /* TF->GetXaxis()->SetTitle(0); */
  /* TF->GetXaxis()->SetLabelSize(0.20); */

  /* TF->GetYaxis()->SetTitle("Transfer factor"); */
  /* TF->GetYaxis()->SetTitleOffset(0.18); */
  /* TF->GetYaxis()->SetTitleSize(0.13); */
  /* TF->GetYaxis()->SetLabelSize(0.09); */

  /* TF->SetLineWidth(3); */
  /* //TF->SetMaximum(1.99); */
  /* //TF->SetMinimum(0.01); */

  if(varName=="AllSBins_v6_CD_EW_50bin"  ){
    TLine *line1V6=new TLine( 6.5,ymin,  6.5,ymax);
    TLine *line2V6=new TLine(12.5,ymin, 12.5,ymax);
    TLine *line3V6=new TLine(18.5,ymin, 18.5,ymax);
    TLine *line4V6=new TLine(24.5,ymin, 24.5,ymax);
    TLine *line5V6=new TLine(30.5,ymin, 30.5,ymax);
    TLine *line6V6=new TLine(36.5,ymin, 36.5,ymax);
    TLine *line7V6=new TLine(43.5,ymin, 43.5,ymax);
    
    pad2->cd(); pad2->SetGridx(0);

    line1V6->Draw();      line2V6->Draw();  line3V6->Draw();
    line4V6->Draw();      line5V6->Draw();
    line6V6->Draw();      line7V6->Draw();
  }
  
  if(varName=="AllSBins_v6_CD"){
    TLine *line1V7=new TLine( 1,ymin,  1,ymax);
    TLine *line2V7=new TLine( 2,ymin,  2,ymax);
    TLine *line3V7=new TLine( 3,ymin,  3,ymax);
    TLine *line4V7=new TLine( 4,ymin,  4,ymax);
    TLine *line5V7=new TLine( 5,ymin,  5,ymax);
    TLine *line6V7=new TLine( 6,ymin,  6,ymax);
    TLine *line7V7=new TLine( 7,ymin,  7,ymax);
    TLine *line8V7=new TLine( 8,ymin,  8,ymax);


    pad2->cd(); pad2->SetGridx(0);// pad2->SetGridy(0);
    line1V7->Draw();      line2V7->Draw();  line3V7->Draw();
    line4V7->Draw();      line5V7->Draw(); line6V7->Draw();
    line7V7->Draw(); line8V7->Draw();
  }
  if(varName=="AllSBins_v6_CD_SP"){
    TLine *line1V6=new TLine( 6.5,ymin,  6.5,ymax);
    TLine *line2V6=new TLine(12.5,ymin, 12.5,ymax);
    TLine *line3V6=new TLine(18.5,ymin, 18.5,ymax);
    TLine *line4V6=new TLine(24.5,ymin, 24.5,ymax);
    TLine *line5V6=new TLine(30.5,ymin, 30.5,ymax);
    pad2->cd(); pad2->SetGridx(0);// pad1->SetGridy(0);
    line1V6->Draw();      line2V6->Draw();  line3V6->Draw();
    line4V6->Draw();      line5V6->Draw();

  }

  if(varName=="AllSBins_v7_CD_SP"){
    TLine *line1V7=new TLine( 6.5,ymin,  6.5,ymax);
    TLine *line2V7=new TLine(11.5,ymin, 11.5,ymax);
    TLine *line3V7=new TLine(16.5,ymin, 16.5,ymax);
    TLine *line4V7=new TLine(21.5,ymin, 21.5,ymax);
    TLine *line5V7=new TLine(26.5,ymin, 26.5,ymax);

    pad2->cd(); pad2->SetGridx(0); //pad1->SetGridy(0);
    line1V7->Draw();      line2V7->Draw();  line3V7->Draw();
    line4V7->Draw();      line5V7->Draw();
  }
  /* /\* for(int i=bin0;i<=bin1;i++) *\/ */
  /* /\*   { cout<<TF->GetBinContent(i)<<" +- "<<TF->GetBinError(i)<<endl;} *\/ */
  /* /\* cout<<"The TF content in bin"<<endl; *\/ */
  /* /\* for(int i=bin0;i<=bin1;i++) *\/ */
  /* /\*   { cout<<TF->GetBinContent(i)<<endl;} *\/ */
  /* /\* cout<<"The Transfer Factor error in bin"<<endl; *\/ */
  /* /\* for(int i=bin0;i<=bin1;i++) *\/ */
  /* /\*   { cout<<TF->GetBinError(i)<<endl;} *\/ */
  /* /\* cout<<"==============="<<endl; *\/ */

}

