void plotoverlay(TString fname,TString varName,TString year, bool ExpvsPred, bool SRvsCR)
{
  
  TCanvas *c1 = new TCanvas;
  TString pdf,png;
  TLatex textOnTop,intLumiE;
  //  bool SRvsCR=true;
  // bool ExpvsPred=false;
  //  bool forallyears=false;
  bool forallyears=false;
  TFile *f1, *f2 , *f3;
  TString path1, path2, path3;
  TString path;
  path="rootout/fake_rate_v10_afterbtagSF_overlap/";

  if(forallyears)
    {
      path="rootout/fake_rate_v10_afterbtagSF_overlap/";

      if(year != "full_Run2") path2=path+fname+"_"+year+"_CR_v18.root";
      if(year == "full_Run2") path2=path+fname+"_CR_v18.root";

      //blue
      cout<<path2<<endl;

      if(SRvsCR){
	pdf=path+"FR/PDF/"+varName+"_"+year+"_comp.pdf";
	png=path+"FR/PNG/"+varName+"_"+year+"_comp.png";
      }
      if(ExpvsPred){
	pdf=path+"closure/PDF/"+varName+"_"+year+"_comp.pdf";
	png=path+"closure/PNG/"+varName+"_"+year+"_comp.png";
      }

      if(year != "full_Run2") path1=path+fname+"_"+year+"_CR_v18.root";
      if(year == "full_Run2") path1=path+fname+"_CR_v18.root";
      //path2=path+fname+"_2016_CR_v18.root";
      cout<<path1<<endl;
      if(year != "full_Run2") path3=path+fname+"_"+year+"_CR_v18.root";
      if(year == "full_Run2") path3=path+fname+"_CR_v18.root";
      //      path3=path+fname+"_2016_CR_v18.root";

    }
  else
    {
      path1=path+fname+"_2016_CR_v18.root";
      path2=path+fname+"_2016_CR_v18.root";
      path3=path+fname+"_2016_CR_v18.root";
    }
  f1 = new TFile(path1);
  f2 = new TFile(path2);
  f3 = new TFile(path3);


  
  int xMin=-100000,xMax = 100000;

  TH1D *fail_accept,*fail_id,*fail_iso,*cr,*fake_photon,*sr,*pred_sr,*cr_1,*sr_1,*pred_sr_1;
  

  double nbin,bin0, bin1, xmin_=0,xmax_=1500,ymax_=10000;
  TH1D *total;
  // if(varName=="AllSBins_v7_CD")
  TString varname_sr;
  if(forallyears) varname_sr=varName+"_elec0";
  
   TString varname_cr;

   
  if(varName=="AllSBins_v6_CD" || varName=="AllSBins_v6_CD_EW_50bin"){
    if(SRvsCR) varname_cr=varName+"_elec1";
    if(ExpvsPred) varname_cr=varName+"_elec1_closure";
    
    if(!forallyears) varname_sr=varname_cr;
    cr          = (TH1D*)f1->Get(varname_sr);
    sr          = (TH1D*)f2->Get(varname_sr);
    pred_sr     = (TH1D*)f3->Get(varname_sr);
    cr_1          = (TH1D*)f1->Get(varname_cr);
    sr_1          = (TH1D*)f2->Get(varname_cr);
    pred_sr_1     = (TH1D*)f3->Get(varname_cr);
    xmin_=0,xmax_=44,ymax_=10000;
    cr->GetYaxis()->SetRangeUser(0.0001,10000);
    cr->GetXaxis()->SetTitle("Bin no.");
    cr->SetTitle(0);

  }

  if(!(varName=="AllSBins_v6_CD" || varName=="AllSBins_v6_CD_EW_50bin"))
    {
      //      varname_cr=varName;
      if(SRvsCR) varname_cr=varName;
      if(ExpvsPred) varname_cr=varName+"_elec1_closure";

      if(!forallyears)
	{//varname_sr=varName;
	  varname_sr=varName;
	  cr          = (TH1D*)f1->Get(varname_sr);
	  sr          = (TH1D*)f2->Get(varname_sr);
	  pred_sr     = (TH1D*)f3->Get(varname_sr);
	  
	  cr_1          = (TH1D*)f1->Get(varname_cr);
	  sr_1          = (TH1D*)f2->Get(varname_cr);
	  pred_sr_1     = (TH1D*)f3->Get(varname_cr);
	}
      if(forallyears)
	{varname_sr=varName;
	  if(SRvsCR) varname_cr=varName;
	  if(ExpvsPred) varname_cr=varName+"_elec1_closure";
	  cr          = (TH1D*)f1->Get(varname_sr);
	  sr          = (TH1D*)f1->Get(varname_sr);
	  pred_sr     = (TH1D*)f3->Get(varname_sr);
	  
	  cr_1          = (TH1D*)f2->Get(varname_cr);
	  sr_1          = (TH1D*)f2->Get(varname_cr);
	  pred_sr_1     = (TH1D*)f3->Get(varname_cr);
	}

    }
  if(varName=="AllSBins_v6_CD_EW_50bin"){
    xmin_=1,xmax_=51,ymax_=10000;
    cr->GetYaxis()->SetRangeUser(0.0001,10000);

    cr->GetXaxis()->SetTitle("Bin no.");
    cr->SetTitle(0);

  }
  if(varName=="BestPhotonPt_0b" || varName=="BestPhotonPt" || varName=="BestPhotonPt_ge1b" || varName=="EMObj_Pt"){
    int rebin=10;
    cr->Rebin(rebin);
    sr->Rebin(rebin);
    pred_sr->Rebin(rebin);
    cr_1->Rebin(rebin);
    sr_1->Rebin(rebin);
    pred_sr_1->Rebin(rebin);
    xmin_=0,xmax_=1500;
    cr->GetXaxis()->SetTitle("p_{T}^{#gamma}");
    cr->GetYaxis()->SetRangeUser(0.001,1000);
  }  
  if(varName=="BestPhotonEta" || varName=="BestPhotonPhi" ){
    int rebin=5;
    cr->Rebin(rebin);
    sr->Rebin(rebin);
    pred_sr->Rebin(rebin);
    cr_1->Rebin(rebin);
    sr_1->Rebin(rebin);
    pred_sr_1->Rebin(rebin);
    xmin_=-3,xmax_=3;
    cr->GetXaxis()->SetTitle("abs{#Eta}");
    cr->GetYaxis()->SetRangeUser(0.001,100000);
  }  
  if(varName=="BestPhotonPt_vBin"){
    xmin_=0,xmax_=1500;
    cr->GetXaxis()->SetTitle("p_{T}^{#gamma}");
    cr->GetYaxis()->SetRangeUser(0.001,1000);
  }  
  if(varName=="METvBin2"){
    cr->GetXaxis()->SetTitle("p_{T}^{miss}");
    cr->GetYaxis()->SetRangeUser(0.001,1000);
    xmin_=200,xmax_=2000;
  }  
  if(varName=="MET"){
    cr->Rebin(5);
    sr->Rebin(5);
    pred_sr->Rebin(5);
    cr_1->Rebin(5);
    sr_1->Rebin(5);
    pred_sr_1->Rebin(5);    
    cr->GetXaxis()->SetTitle("p_{T}^{miss}");
    cr->GetYaxis()->SetRangeUser(0.001,1000);
  }  
 if(varName=="nJets"){
    xmin_=0,xmax_=14;
    cr->GetXaxis()->SetTitle("N_{Jets}");
    cr->GetYaxis()->SetRangeUser(0.001,1000);
  }  
 if(varName=="Qmulti"){
   int rebin=1;
    cr->Rebin(rebin);
    sr->Rebin(rebin);
    pred_sr->Rebin(rebin);
    cr_1->Rebin(rebin);
    sr_1->Rebin(rebin);
    pred_sr_1->Rebin(rebin);
    xmin_=0,xmax_=20;
    cr->GetXaxis()->SetTitle("Q_{Mutilplicity}");
    cr->GetYaxis()->SetRangeUser(0.001,1000);
  }  
 if(varName=="nvtx"){
    xmin_=0,xmax_=50;
    cr->GetXaxis()->SetTitle("N_{Vertices}");
    cr->GetYaxis()->SetRangeUser(0.001,1000);
  }  
  if(varName=="nBTags"){
    xmin_=0,xmax_=14;
    cr->GetXaxis()->SetTitle("N_{b tags}");
    cr->GetYaxis()->SetRangeUser(0.001,1000);
  }  
  if(varName=="JetPt" || varName=="leadJetPt"){
    cr->Rebin(5);
    sr->Rebin(5);
    pred_sr->Rebin(5);
    cr_1->Rebin(5);
    sr_1->Rebin(5);
    pred_sr_1->Rebin(5);
    xmin_=0,xmax_=2000;
    cr->GetXaxis()->SetTitle("p_{T}^{jets}");
    cr->GetYaxis()->SetRangeUser(0.001,1000);
  }  
  if(varName=="JetPt" || varName=="leadJetPt"){
    cr->Rebin(5);
    sr->Rebin(5);
    pred_sr->Rebin(5);
    cr_1->Rebin(5);
    sr_1->Rebin(5);
    pred_sr_1->Rebin(5);
    xmin_=0,xmax_=2000;
    cr->GetXaxis()->SetTitle("p_{T}^{jets}");
    cr->GetYaxis()->SetRangeUser(0.001,1000);
  }  
  if(varName=="leadElectronPt"){
    int rebin=4;
    cr->Rebin(rebin);
     sr->Rebin(rebin);
    pred_sr->Rebin(rebin);
    cr_1->Rebin(rebin);
    sr_1->Rebin(rebin);
    pred_sr_1->Rebin(rebin);
    xmin_=0,xmax_=800;
    cr->GetXaxis()->SetTitle("p_{T}^{e}");
    cr->GetYaxis()->SetRangeUser(0.001,1000);
  }  

  /* cout<<"The cr content in bin"<<endl; */
  /* for(int i=bin0;i<=bin1;i++) */
  /*   { cout<<cr->GetBinContent(i)<<endl;} */
  /* cout<<"The Transfer Factor error in bin"<<endl; */
  /* for(int i=bin0;i<=bin1;i++) */
  /*   { cout<<cr->GetBinError(i)<<endl;} */
  /* cout<<"==============="<<endl; */


  TPad *pad1 = new TPad("pad1","pad1",0,0,1,1);
  pad1->Draw();pad1->SetGridx();

  pad1->cd();
  pad1->SetLogy();
  cr->SetMarkerStyle(20);
  cr->SetMarkerSize(0.7);
  cr->SetMarkerColor(kRed);
  cr->SetLineColor(kRed);
  cr->GetXaxis()->SetRangeUser(xmin_,xmax_);
  cr->GetYaxis()->SetRangeUser(0.001,100000);
  sr->SetMarkerStyle(20);
  sr->SetMarkerSize(0.7);
  sr->SetMarkerColor(kBlue);
  sr->SetLineColor(kBlue);
  pred_sr->SetMarkerStyle(20);
  pred_sr->SetMarkerSize(0.7);
  pred_sr->SetMarkerColor(kGreen);
  pred_sr->SetLineColor(kGreen);
  cr_1->SetMarkerStyle(20);
  cr_1->SetMarkerSize(0.7);
  if(forallyears)
    {
      cr_1->SetMarkerColor(kRed);
      cr_1->SetLineColor(kRed);
      cr_1->SetLineStyle(2);
    }
  else
    {
      cr_1->SetMarkerColor(kBlue);
      cr_1->SetLineColor(kBlue);
    }
   sr_1->SetMarkerStyle(20);
  sr_1->SetMarkerSize(0.7);
  sr_1->SetMarkerColor(kBlue);
  sr_1->SetLineColor(kBlue);
  sr_1->SetLineStyle(2);
   pred_sr_1->SetMarkerStyle(20);
  pred_sr_1->SetMarkerSize(0.7);
  pred_sr_1->SetMarkerColor(kGreen);
  pred_sr_1->SetLineColor(kGreen);
  /* pred_sr_1->SetMarkerColor(kBlue); */
  /* pred_sr_1->SetLineColor(kBlue); */
  pred_sr->SetMarkerColor(kGreen);
  pred_sr->SetLineColor(kGreen);
  pred_sr_1->SetLineStyle(2);

  cr->Draw("hist");
  cr_1->Draw("hist sames");
  

  if(forallyears)
    {
      sr->Draw("hist sames");
      //      pred_sr->Draw("hist sames");
      sr_1->Draw("hist sames");
      // pred_sr_1->Draw("hist sames");
    }
  c1->Update();
  gPad->Update();
  gStyle->SetOptStat("i");
  //cr->SetStats(0);
  
  if(!(varName=="AllSBins_v6_CD" && varName=="AllSBins_v6_CD_EW_50bin"))
    {

      TPaveStats *cr_stat = (TPaveStats*)cr_1->FindObject("stats");
      cr_stat->SetX1NDC(0.7);
      cr_stat->SetX2NDC(0.9);
      cr_stat->SetY1NDC(0.7);
      cr_stat->SetY2NDC(0.8);
      cr_stat->SetTextColor(kRed);
      cr_stat->SetLineColor(kRed);
      cr_stat->Draw();
      TPaveStats *sr_stat=(TPaveStats*)sr_1->FindObject("stats");
      /* if(!forallyears) sr_stat= (TPaveStats*)cr_1->FindObject("stats"); */
      /* if(forallyears) sr_stat= (TPaveStats*)sr->FindObject("stats"); */
      sr_stat->SetX1NDC(0.7);
      sr_stat->SetX2NDC(0.9);
      sr_stat->SetY1NDC(0.6);
      sr_stat->SetY2NDC(0.7);
      sr_stat->SetTextColor(kBlue);
      sr_stat->SetLineColor(kBlue);
      sr_stat->Draw();

      
      /* if(forallyears) */
      /* 	{ */
      /* 	  TPaveStats *pred_sr_stat = (TPaveStats*)pred_sr->FindObject("stats"); */
      /* 	  pred_sr_stat->SetX1NDC(0.7); */
      /* 	  pred_sr_stat->SetX2NDC(0.9); */
      /* 	  pred_sr_stat->SetY1NDC(0.5); */
      /* 	  pred_sr_stat->SetY2NDC(0.6); */
      /* 	  pred_sr_stat->SetTextColor(kGreen); */
      /* 	  pred_sr_stat->SetLineColor(kGreen); */
	  //      	  pred_sr_stat->Draw();
	  //	  cr_1->SetStats(0);
      //      	}
      
      cr->SetStats(0);
      sr->SetStats(0);
      pred_sr->SetStats(0);
      pred_sr_1->SetStats(0);
      
    }  
  else
    {
      cr->SetStats(0);
      sr->SetStats(0);                                                                                                                                       
      sr->SetStats(0);
      pred_sr->SetStats(0);
      sr_1->SetStats(0);
      pred_sr_1->SetStats(0);
    }
  if(varName=="AllSBins_v6_CD"){

    TLine *line1V6=new TLine( 4,0,  4,1000);
    TLine *line2V6=new TLine( 8,0,  8,1000);
    TLine *line3V6=new TLine( 12,0,  12,1000);
    TLine *line4V6=new TLine( 16,0,  16,1000);
    TLine *line5V6=new TLine( 20,0,  20,1000);
    TLine *line6V6=new TLine( 24,0,  24,1000);
    TLine *line7V6=new TLine( 28,0,  28,1000);
    TLine *line8V6=new TLine( 32,0,  32,1000);
    TLine *line9V6=new TLine( 36,0,  36,1000);
    TLine *line10V6=new TLine( 40,0,  40,1000);
    // TLine *line11V6=new TLine( 44,0,  44,1000);

    pad1->cd(); pad1->SetGridx(0); pad1->SetGridy(0);
    line1V6->Draw();      line2V6->Draw();  line3V6->Draw();
    line4V6->Draw();      line5V6->Draw(); line6V6->Draw();
    line7V6->Draw(); line8V6->Draw();
    line9V6->Draw(); line10V6->Draw();
    // line11V6->Draw();
    TArrow *arrow1 = new TArrow( 0, 100, 4, 100,0.01,"<|>");
    TArrow *arrow2 = new TArrow( 4, 100, 8, 100,0.01,"<|>");
    TArrow *arrow3 = new TArrow( 8, 100, 12, 100,0.01,"<|>");
    TArrow *arrow4 = new TArrow( 12, 100, 16, 100,0.01,"<|>");
    TArrow *arrow5 = new TArrow( 16, 100, 20, 100,0.01,"<|>");
    TArrow *arrow6 = new TArrow( 20,100, 24,100,0.01,"<|>");
    TArrow *arrow7 = new TArrow( 24,100, 28,100,0.01,"<|>");
    TArrow *arrow8 = new TArrow( 28,100, 32,100,0.01,"<|>");
    TArrow *arrow9 = new TArrow( 32,100, 36,100,0.01,"<|>");
    TArrow *arrow10 = new TArrow(36,100, 40,100,0.01,"<|>");
    TArrow *arrow11 = new TArrow(40,100, 44,100,0.01,"<|>");

        arrow1->Draw(); arrow2->Draw(); arrow3->Draw();
    arrow4->Draw();
    arrow5->Draw(); arrow6->Draw();
    arrow7->Draw(); arrow8->Draw();
    arrow9->Draw(); arrow10->Draw();
    arrow11->Draw();
    TLatex Tl;
    Tl.SetTextSize(0.03);
    Tl.DrawLatex(1.5,40,"p_{T}^{EM}");
    Tl.DrawLatex(0.2,10,"[100,120]");
    Tl.DrawLatex(5.5,40,"p_{T}^{EM}");
    Tl.DrawLatex(4.2,10,"[120,140]");
    Tl.DrawLatex(9.5,40,"p_{T}^{EM}");
    Tl.DrawLatex(8.2,10,"[140,160]");
    Tl.DrawLatex(13.5,40,"p_{T}^{EM}");
    Tl.DrawLatex(12.2,10,"[160,180]");
    Tl.DrawLatex(17.5,40,"p_{T}^{EM}");
    Tl.DrawLatex(16.2,10,"[180,200]");
    Tl.DrawLatex(21.5,40,"p_{T}^{EM}");
    Tl.DrawLatex(20.2,10,"[200,230]");
    /* Tl.DrawLatex(25.5,40,"p_{T}^{EM}"); */
    /* Tl.DrawLatex(24.2,10,"[200,230]"); */
    Tl.DrawLatex(25.5,40,"p_{T}^{EM}");
    Tl.DrawLatex(24.2,10,"[230,260]");
    Tl.DrawLatex(29.5,40,"p_{T}^{EM}");
    Tl.DrawLatex(28.2,10,"[260,300]");
    Tl.DrawLatex(33.5,40,"p_{T}^{EM}");
    Tl.DrawLatex(32.2,10,"[300,380]");
    Tl.DrawLatex(37.5,40,"p_{T}^{EM}");
    Tl.DrawLatex(36.2,10,"[380,500]");
    Tl.DrawLatex(41.5,40,"p_{T}^{EM}");
    Tl.DrawLatex(40.2,10,">=500");
    
    /* Tl.DrawLatex(2.5,0.47,"N^{ 0}_{ 3}"); */
    /* Tl.DrawLatex(3.5,0.47,"N^{ 0}_{ 4}"); */
    /* Tl.DrawLatex(4.5,0.47,"N^{ 0}_{ 5-6}"); */
    /* Tl.DrawLatex(5.5,0.47,"N^{ 0}_{ #geq7}"); */
    /* Tl.DrawLatex(6.5,0.47,"N^{ #geq1}_{ 2-4}"); */
    /* Tl.DrawLatex(7.5,0.47,"N^{ #geq1}_{ 5-6}"); */
    /* Tl.DrawLatex(8.5,0.47,"N^{ #geq1}_{ #geq7}"); */
  }
      

      if(varName=="AllSBins_v7_CD_SP"){
    TLine *line1V6=new TLine( 1,0,  1,ymax_);
    TLine *line2V6=new TLine( 2,0,  2,ymax_);
    TLine *line3V6=new TLine( 3,0,  3,ymax_);
    TLine *line4V6=new TLine( 4,0,  4,ymax_);
    TLine *line5V6=new TLine( 5,0,  5,ymax_);
    TLine *line6V6=new TLine( 6,0,  6,ymax_);
    TLine *line7V6=new TLine( 7,0,  7,ymax_);
    TLine *line8V6=new TLine( 8,0,  8,ymax_);
    TLine *line9V6=new TLine( 9,0,  9,ymax_);
    TLine *line10V6=new TLine( 10,0,  10,ymax_);
    TLine *line11V6=new TLine( 11,0,  11,ymax_);


    pad1->cd(); pad1->SetGridx(0); pad1->SetGridy(0);
    line1V6->Draw();      line2V6->Draw();  line3V6->Draw();
    line4V6->Draw();      line5V6->Draw(); line6V6->Draw();
    line7V6->Draw(); line8V6->Draw();
    line9V6->Draw(); line10V6->Draw();
    line11V6->Draw();
    TArrow *arrow1 = new TArrow( 1, 0.1, 2, 0.1,0.01,"<|>");
    TArrow *arrow2 = new TArrow( 2, 0.1, 3, 0.1,0.01,"<|>");
    TArrow *arrow3 = new TArrow( 3, 0.1, 4, 0.1,0.01,"<|>");
    TArrow *arrow4 = new TArrow( 4, 0.1, 5, 0.1,0.01,"<|>");
    TArrow *arrow5 = new TArrow( 5, 0.1, 6, 0.1,0.01,"<|>");
    TArrow *arrow6 = new TArrow( 6,0.1, 7,0.1,0.01,"<|>");
    TArrow *arrow7 = new TArrow( 7,0.1, 8,0.1,0.01,"<|>");
    TArrow *arrow8 = new TArrow( 8,0.1, 9,0.1,0.01,"<|>");
    TArrow *arrow9 = new TArrow( 9, 0.1, 10, 0.1,0.01,"<|>");
    TArrow *arrow10 = new TArrow( 10,0.1, 11,0.1,0.01,"<|>");
    TArrow *arrow11 = new TArrow( 1,1000, 9,1000,0.01,"<|>");
    TArrow *arrow12 = new TArrow( 9,1000, 11,1000,0.01,"<|>");


    arrow1->Draw(); arrow2->Draw(); arrow3->Draw();
    arrow4->Draw();
    arrow5->Draw(); arrow6->Draw();
    arrow7->Draw(); arrow8->Draw();
    arrow9->Draw(); arrow10->Draw();
    arrow11->Draw(); arrow12->Draw();

    TLatex Tl,T2;
    Tl.SetTextSize(0.05);
    Tl.DrawLatex(1.25,0.2,"N^{ 0}_{ 2}");
    Tl.DrawLatex(2.25,0.2,"N^{ 0}_{ 3}");
    Tl.DrawLatex(3.25,0.2,"N^{ 0}_{ 4}");
    Tl.DrawLatex(4.25,0.2,"N^{ 0}_{ 5-6}");
    Tl.DrawLatex(5.25,0.2,"N^{ 0}_{ #geq7}");
    Tl.DrawLatex(6.25,0.2,"N^{ #geq1}_{ 2-4}");
    Tl.DrawLatex(7.25,0.2,"N^{ #geq1}_{ 5-6}");
    Tl.DrawLatex(8.25,0.2,"N^{ #geq1}_{ #geq7}");
    Tl.DrawLatex(9,0.2,"W tag");
    Tl.DrawLatex(10,0.2,"H tag");
    T2.DrawLatex(4.5,1500,"SP region");
    T2.DrawLatex(9.0,1500,"EW region");
    
    
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

  if(varName=="AllSBins_v6_CD_EW_50bin"  ){

    double yset_=700, ymin_=0;
    ymax_=10000;
    TLine *line1V6=new TLine( 8,ymin_,  8,ymax_);
    TLine *line2V6=new TLine(14,ymin_, 14,ymax_);
    TLine *line3V6=new TLine(20,ymin_, 20,ymax_);
    TLine *line4V6=new TLine(26,ymin_, 26,ymax_);
    TLine *line5V6=new TLine(32,ymin_, 32,ymax_);
    TLine *line6V6=new TLine(38,ymin_, 38,ymax_);
    TLine *line7V6=new TLine(45,ymin_, 45,ymax_);

    pad1->cd(); pad1->SetGridx(0); pad1->SetGridy(0);

    line1V6->Draw();      line2V6->Draw();  line3V6->Draw();
    line4V6->Draw();      line5V6->Draw();
    line6V6->Draw();      line7V6->Draw();

    TArrow *arrow1 = new TArrow( 1,yset_, 8,yset_,0.01,"<|>");
    TArrow *arrow2 = new TArrow( 8,yset_, 14,yset_,0.01,"<|>");
    TArrow *arrow3 = new TArrow(14,yset_, 20,yset_,0.01,"<|>");
    TArrow *arrow4 = new TArrow(20,yset_, 26,yset_,0.01,"<|>");
    TArrow *arrow5 = new TArrow(26,yset_, 32,yset_,0.01,"<|>");
    TArrow *arrow6 = new TArrow(32,yset_, 38,yset_,0.01,"<|>");
    TArrow *arrow7 = new TArrow(38,yset_, 45,yset_,0.01,"<|>");
    TArrow *arrow8 = new TArrow(45,yset_, 51,yset_,0.01,"<|>");
    
    arrow1->Draw(); arrow2->Draw(); arrow3->Draw();
    arrow4->Draw(); arrow5->Draw(); arrow6->Draw();
    arrow7->Draw(); arrow8->Draw();
    TLatex Tl;
    Tl.SetTextSize(0.04);
    Tl.DrawLatex(2.5,2*yset_,"N^{ 0}_{ 2-4}");
    Tl.DrawLatex(9.0,2*yset_,"N^{ 0}_{ 5-6}");
    Tl.DrawLatex(15.0,2*yset_,"N^{ 0}_{ #geq7}");
    Tl.DrawLatex(21.0,2*yset_,"N^{ #geq1}_{ 2-4}");
    Tl.DrawLatex(26.0,2*yset_,"N^{ #geq1}_{ 5-6}");
    Tl.DrawLatex(32.0,2*yset_,"N^{ #geq1}_{ #geq7}");
    Tl.SetTextSize(0.03);
    Tl.DrawLatex(37.0,2*yset_,"EW : W tag");
    Tl.DrawLatex(44.0,2*yset_,"EW : H tag");
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

    TArrow *arrow1 = new TArrow( -0.5,0.4, 6.5,0.4,0.01,"<|>");
    TArrow *arrow2 = new TArrow( 6.5,0.4,12.5,0.4,0.01,"<|>");
    TArrow *arrow3 = new TArrow(12.5,0.4,18.5,0.4,0.01,"<|>");
    TArrow *arrow4 = new TArrow(18.5,0.4, 24.5,0.4,0.01,"<|>");
    TArrow *arrow5 = new TArrow(24.5,0.4, 30.5,0.4,0.01,"<|>");
    TArrow *arrow6 = new TArrow(30.5,0.4, 35.5,0.4,0.01,"<|>");

    arrow1->Draw(); arrow2->Draw(); arrow3->Draw();
    arrow4->Draw(); arrow5->Draw(); arrow6->Draw();
    TLatex Tl;
    Tl.SetTextSize(0.04);
    Tl.DrawLatex(2.0,0.47,"N^{ 0}_{ 2-4}");
    Tl.DrawLatex(8.5,0.47,"N^{ 0}_{ 5-6}");
    Tl.DrawLatex(14.5,0.47,"N^{ 0}_{ #geq7}");
    Tl.DrawLatex(20.5,0.47,"N^{ #geq1}_{ 2-4}");
    Tl.DrawLatex(25.5,0.47,"N^{ #geq1}_{ 5-6}");
    Tl.DrawLatex(31.5,0.47,"N^{ #geq1}_{ #geq7}");
  }


  textOnTop.SetTextSize(0.04);
 intLumiE.SetTextSize(0.04);
  //  if(isPaper) textOnTop.DrawLatexNDC(0.12,0.91,"CMS #it{#bf{Simulation Supplementary}}");                                                                                                  
  textOnTop.DrawLatexNDC(0.1,0.91,"CMS #it{#bf{Simulation Preliminary}}");
  if(year=="2016")
    intLumiE.DrawLatexNDC(0.7,0.91,"#bf{35.9 fb^{-1} (13 TeV)}");
  if(year=="2017")
    intLumiE.DrawLatexNDC(0.7,0.91,"#bf{41.5 fb^{-1} (13 TeV)}");
  if(year=="2018")
  intLumiE.DrawLatexNDC(0.7,0.91,"#bf{59.6 fb^{-1} (13 TeV)}");
  if(year=="full_Run2")
    intLumiE.DrawLatexNDC(0.7,0.91,"#bf{137 fb^{-1} (13 TeV)}");
  
  
  TLegend *legend = new TLegend(0.1,0.86,0.7,0.9);
  legend->SetNColumns(2);
  legend->SetBorderSize(1);

  /* legend->AddEntry(cr,"35.9 fb^{-1}","lp"); */
  /* legend->AddEntry(sr,"41.5 fb^{-1}","lp"); */
  /* legend->AddEntry(pred_sr,"59.6 fb^{-1}","lp"); */
  legend->AddEntry(cr,"trial 4","lp");
  legend->AddEntry(sr,"trial 3","lp");
  /* legend->AddEntry(cr,"CR : using pho pT X NJets","lp"); */
  /* legend->AddEntry(sr,"CR : using pho pT X NJets X BTags","lp"); */
  /* legend->AddEntry(cr,"CR : photons with pixel seed","lp"); */
  /* legend->AddEntry(sr,"CR : 1 e & 0 photon","lp"); */
  //  legend->AddEntry(pred_sr,"59.6 fb^{-1}","lp");
  /* legend->AddEntry(pred_sr,"137 fb^{-1}","lp"); */
  legend->SetTextSize(0.03);
  TLegend *legend1 = new TLegend(0.7,0.86,0.9,0.9);
  legend1->SetNColumns(2);
  legend1->SetBorderSize(1);
  if(ExpvsPred)
    {
      legend1->AddEntry(cr,"Exp","l");
      legend1->AddEntry(cr_1,"Pred","l");
    }
  if(SRvsCR)
   {
      legend1->AddEntry(sr,"SR","l");
      legend1->AddEntry(sr_1,"CR","l");
      /* legend1->AddEntry(pred_sr,"SR","l"); */
      /* legend1->AddEntry(pred_sr_1,"CR","l"); */
    }
    
  legend1->SetTextSize(0.04);
  // if(forallyears) legend->Draw();
  legend1->Draw();
  TH1D *h2 = (TH1D*)cr_1->Clone("h2");
  TH1D *h1 = (TH1D*)cr->Clone("h1");
  
  TH1D *h4 = (TH1D*)sr_1->Clone("h4");
  TH1D *h3 = (TH1D*)sr->Clone("h3");

  TH1D *h6 = (TH1D*)pred_sr_1->Clone("h6");
  TH1D *h5 = (TH1D*)pred_sr->Clone("h5");
  
  //TPad *pad2 = new TPad("pad1","pad1",0,0.0,1,0.9);
  TPad *pad2 = new TPad("pad1","pad1",0,0.0,1,0.3);
  pad2->Draw();
  pad2->SetTopMargin(0);
  pad2->SetBottomMargin(0.3);
  pad2->cd();
  pad2->SetGrid(1);

  if(SRvsCR)  h1->GetYaxis()->SetRangeUser(0,2);
  if(ExpvsPred)  h1->GetYaxis()->SetRangeUser(0,2);
  /*h1->GetXaxis()->SetRangeUser(xmin,xmax); */
  /* h4->GetXaxis()->SetRangeUser(xmin,xmax); */


  h1->SetLineColor(kRed);
  h1->SetLineStyle(1);
  h1->SetLineWidth(2);
  /*  h1->SetMinimum(0);  // Define Y .. */
  /* h1->SetMaximum(2); // .. range */
  h1->Sumw2();
  h1->SetStats(0);      // No statistics on lower plot                                                                                                                                                            
  h1->Divide(h2);
  h1->SetMarkerStyle(20);
  h1->SetMarkerSize(0.6);
  h1->Draw("ep");       // Draw the ratio plot
  h1->SetTitle(0);
  if(SRvsCR) h1->GetYaxis()->SetTitle("SR/CR");
  if(ExpvsPred)  h1->GetYaxis()->SetTitle("Exp/Pred");
  //  h1->GetYaxis()->SetTitle("eSF(w/o)/eSF");
  //  h1->GetYaxis()->SetTitle("Data/MC");
  h1->GetXaxis()->SetRangeUser(xmin_,xmax_);
  h1->GetYaxis()->SetNdivisions(5);
   h1->GetYaxis()->SetTitleOffset(0.24);
  h1->GetYaxis()->SetTitleSize(0.16);
  h1->GetYaxis()->SetLabelSize(0.15);
  h1->GetXaxis()->SetTitleOffset(0.9);
  h1->GetXaxis()->SetTitle(varName);
  h1->GetXaxis()->SetTitleSize(0.17);
  h1->GetXaxis()->SetLabelSize(0.22);
  /* h1->GetYaxis()->SetTitleOffset(.91); */
  /* h1->GetYaxis()->SetTitleSize(0.05); */
  /* h1->GetYaxis()->SetLabelSize(0.05); */
  /* h1->GetXaxis()->SetTitleOffset(0.9); */
  /* h1->GetXaxis()->SetTitle(varName); */
  /* h1->GetXaxis()->SetTitleSize(0.06); */
  /* h1->GetXaxis()->SetLabelSize(0.06); */

  if(varName=="AllSBins_v6_CD" || varName=="AllSBins_v6_CD_EW_50bin") h1->GetXaxis()->SetTitle("Bin no.");
  h3->SetLineColor(kBlue);
  h3->SetLineStyle(1);
  h3->SetLineWidth(2);
  h3->SetStats(0);      // No statistics on lower plot                                                                                                                                                            
  h3->SetMinimum(0);  // Define Y ..
  h3->SetMaximum(1); // .. range
  h3->Sumw2();
  h3->Divide(h4);
  h3->SetMarkerStyle(20);
  h3->SetMarkerSize(0.6);
  if(forallyears)  h3->Draw("ep sames");       // Draw the ratio plot
  else h3->Draw("ep sames");
  
  h5->SetLineColor(kGreen);
  h5->SetLineStyle(1);
  h5->SetLineWidth(2);
  h5->SetMinimum(0);  // Define Y ..
  h5->SetMaximum(1); // .. range
  h5->Sumw2();
  h5->SetStats(0);      // No statistics on lower plot                                                                                                                                                            
  h5->Divide(h6);
  h5->SetMarkerStyle(20);
  h5->SetMarkerSize(0.6);
  //  if(forallyears) h5->Draw("ep sames");       // Draw the ratio plot

  cout<<"++++++ 2016 ++++++++ "<<endl;
  for(int i=0;i<=10;i++)
    { cout<<h1->GetBinContent(i)<<" +- "<<h1->GetBinError(i)<<endl;}
  cout<<"++++++ 2017 ++++++++ "<<endl;
  for(int i=0;i<=10;i++)
    { cout<<h3->GetBinContent(i)<<" +- "<<h3->GetBinError(i)<<endl;}
   cout<<"++++++ 2018 ++++++++ "<<endl;
  for(int i=0;i<=10;i++)
    { cout<<h5->GetBinContent(i)<<" +- "<<h5->GetBinError(i)<<endl;}
  
  TLine *line;
  if(SRvsCR)  line = new TLine(xmin_,0.02,xmax_,0.02);
  if(ExpvsPred)  line = new TLine(xmin_,1.0,xmax_,1.0);

  line->SetLineColor(1);
  line->SetLineStyle(1);
  line->SetLineWidth(1);
  line->Draw();

  if(varName=="AllSBins_v6_CD_EW_50bin"  ){

    double yset_=700, ymin_=0;
    ymax_=10000;
    TLine *line1V6=new TLine( 8,ymin_,  8,ymax_);
    TLine *line2V6=new TLine(14,ymin_, 14,ymax_);
    TLine *line3V6=new TLine(20,ymin_, 20,ymax_);
    TLine *line4V6=new TLine(26,ymin_, 26,ymax_);
    TLine *line5V6=new TLine(32,ymin_, 32,ymax_);
    TLine *line6V6=new TLine(38,ymin_, 38,ymax_);
    TLine *line7V6=new TLine(45,ymin_, 45,ymax_);
    pad2->cd(); pad2->SetGridx(0);

    line1V6->Draw();      line2V6->Draw();  line3V6->Draw();
    line4V6->Draw();      line5V6->Draw();
    line6V6->Draw();      line7V6->Draw();
  }
    
  c1->Modified();
  c1->SaveAs(pdf);
  c1->SaveAs(png);

}
