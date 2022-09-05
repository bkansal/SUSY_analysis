void plotFR(TString varName,  TString year,  TString ntuples="v17" , bool data = true, int rebin=1)
{
  
  TFile *f1, *f2,*f3;
  string lep="LL";
  TString path,path1,name,path2;
  double ratio=1;
  //  path="./rootoutput/SF/";
  path="./rootoutput/v1/withsimpleselections_oldfake_MET100/";
  path="./rootoutput/v1/withsimpleselections_nofake/";                                                                                                               
  path="./rootoutput/v1/withsimpleselections_ST200_tt/";
  //  path="./rootoutput/v1/withsimpleselections_ST200_nopxveto/";
  //   path="./rootoutput/v1/withsimpleselections_ST200_nopxveto_trackiso/";
    path="rootoutput/tmp/";
   //   path="./rootoutput/v1/withsimpleselections_ST200_pxveto_higheta_trackiso/";
  //path="./rootoutput/v1/withsimpleselections_ST200_pxveto_higheta_trackiso_trgeff/";
  //   path="./rootoutput/v1/withsimpleselections_ST200_pxveto_higheta/";

   //   path="./rootoutput/v1/withsimpleselections_ST200_px/";
   // path="./";
  //  path="./rootoutput/v1/withsimpleselections_ST200_zpt600/";
  //   path1="./";
  TLatex textOnTop,intLumiE;
  
  TString filename,filename2;
  if(ntuples=="v18")
    {
      filename= path1+"Run"+year+"_SF_FR_data.root";
      filename2= path1+"Run"+year+"_SF_FR_mc.root";
      name="SF_"+year;	  
      TString name_CR,name_SR;
      TFile *PF_CR,*PF_SR;
      TH1D *pf_CR,*pf_SR;
      
      name_CR="purityfactor_"+year+".root";
      name_SR="purityfactor_"+year+"_elec0.root";
      PF_CR = TFile::Open(name_CR,"READ");
      PF_SR = TFile::Open(name_SR,"READ");
      pf_CR=(TH1D*)PF_CR->FindObjectAny("avg_purity");
      pf_SR=(TH1D*)PF_SR->FindObjectAny("avg_purity");
      ratio=pf_SR->GetBinContent(1)/pf_CR->GetBinContent(1);
      cout<<"ratio : "<<ratio<<endl;
  
    }
  else
    {
      //Run2016_SF_FR_data.root
      /* filename= path+"Run2016_SF_FR_data.root"; */
      /* filename2= path+"Run2016_SF_FR_mc.root"; */
      //	  filename= path+"Run2016_CR_v18.root";
      filename= path+"Run"+year+"_CR_v18.root";
      //      filename2= path+"TTWDYG_"+year+"_CR_v18.root";
                filename2= path+"DYJets_"+year+"_CR_v18.root";
      //          filename2= path+"ZGJ_"+year+"_CR_v18.root";

      //      filename2= path+"TTWGJ_"+year+"_CR_v18.root";
      //filename2= path+"DYJets_"+year+"_CR_v18.root";
      if(!data)  name="Run"+year+"_SF_FR_mc";
      if(data) name="Run"+year+"_SF_FR_data";

  
    }

  
  double xmin,xmax,bin,xmin_,xmax_;
  double ymin=0.5 , ymax=1.5, ymin_=0.0001 , ymax_=1000;

  TH1D *cr,*sr,*tf,*pred_sr;
 
  TString title;

  if(varName=="AllSBins_v6_CD_EW_50bin")
    title="closure test using optimized search bins";
  else
    title="closure test using "+ varName +" variable";
  TString png,pdf;
  if(data)
    {
      png = path1+"/PDF/closure/"+varName+"_"+year+".pdf";
      pdf= path1+"/PDF/closure/"+varName+"_"+year+".png";
    }
  else if(!data)
    {
      png = path1+"/PDF/SF/"+varName+"_"+year+".pdf";
      pdf= path1+"/PDF/SF/"+varName+"_"+year+".png";
    }
  //  TCanvas *c1 = new TCanvas("stackhist","stackhist",600,500);
  TCanvas *c1;
  TString varName1,varName2;
  //  if(data)  varName2=varName+"_elec1_closure";
  /* if(data)  varName2=varName+"_elec0"; */
  /* else if(!data) varName2=varName; */
  if(ntuples=="v18")
    {
      //      varName="h3";
      f2 = new TFile(filename2);
      f1 = new TFile(filename);

      TString rootout = name + ".root";
      TFile *fout =new TFile(rootout,"recreate");
      fout->cd();
      cout<<rootout<<endl;

      // cout<<endl;
    }
  else
    {
      if(data)
	{
	  f1 = new TFile(filename);
	  varName2=varName+"_elec0";
	}
      else if(!data)
	{
	  varName2=varName+"_elec0";
	  f1 = new TFile(filename2);
	}

      TString rootout = name + ".root";
      TFile *fout =new TFile(rootout,"recreate");
      fout->cd();
      cout<<rootout<<endl;

    }

  double nbin,bin0, bin1,yset_;
  TH1D *total;

   c1 = new TCanvas("stackhist","stackhist",500,500);
  //  c1 = new TCanvas("stackhist","stackhist",900,1000);
      //  c1 = new TCanvas("stackhist","stackhist",600,500);
  if(ntuples=="v18")
    {
      sr          = (TH1D*)f1->Get("h3");
      pred_sr     = (TH1D*)f2->Get("h3");
    }
  else
    {
      sr          = (TH1D*)f1->Get(varName2);
      pred_sr     = (TH1D*)f1->Get(varName);
    }
 if(varName=="nJets" || varName=="nvtx" || varName=="nJets_EW" ||varName=="nJets_SP"||varName=="Qmulti" ||varName=="Qmulti_SF")
    {
      //    rebin=1;
    if(varName=="Qmulti" || varName=="Qmulti_SF")    xmin_=0,xmax_=16,xmin=0,xmax=16,    ymin=1 , ymax=3.99, ymin_=0.0005 , ymax_=0.09;
    if(varName=="nJets" || varName=="nJets_SP" || varName=="nJets_EW" || varName=="nBTags")    xmin_=0,xmax_=20,xmin=0,xmax=20 , ymin=0 , ymax=2.99, ymin_=0.0005 , ymax_=0.04;
    //    if(varName=="nJets")    rebin=1,xmin_=0,xmax_=15,xmin=0,xmax=15 , ymin=0 , ymax=1.99, ymin_=0.0005 , ymax_=0.04;

    if(varName=="nvtx")    xmin_=0,xmax_=100,xmin=0,xmax=100, ymin=0 , ymax=2.99, ymin_=0.0005 , ymax_=0.04;
    
    // ymin_=0.0005 , ymax_=100000;
    pred_sr->Rebin(rebin);
    sr->Rebin(rebin);
    pred_sr->GetXaxis()->SetRangeUser(xmin,xmax);
    sr->GetXaxis()->SetRangeUser(xmin,xmax);

    // pred_sr->SetTitle(title);
    }

 else if(varName=="nBTags" || varName=="nBTags_EW" || varName=="nBTags_SP"  )
    {
    xmin_=0,xmax_=8,xmin=0,xmax=8;
    ymin=0 , ymax=4.99, ymin_=0 , ymax_=0.1;
    // ymin_=0.0005 , ymax_=100000;
    pred_sr->Rebin(rebin);
    sr->Rebin(rebin);
    pred_sr->GetXaxis()->SetRangeUser(xmin,xmax);
    sr->GetXaxis()->SetRangeUser(xmin,xmax);
   pred_sr->SetTitle(title);
   }
 else if(varName=="invMass" || varName=="invMass_elec0"  )
    {
    xmin_=80,xmax_=100,xmin=80,xmax=100;
    //    rebin=2;
    ymin=0 , ymax=3.99, ymin_=0 , ymax_=0.05;
    //    ymin_=0.0005 , ymax_=100000;
    pred_sr->Rebin(rebin);
    sr->Rebin(rebin);
    pred_sr->GetXaxis()->SetRangeUser(xmin,xmax);
    sr->GetXaxis()->SetRangeUser(xmin,xmax);
   pred_sr->SetTitle(title);
   }

 else if(varName=="ST")
    {
    xmin_=100,xmax_=4000,xmin=100,xmax=4000;
    ymin=0 , ymax=2.99, ymin_=0 , ymax_=0.1;
    pred_sr->Rebin(rebin);
    sr->Rebin(rebin);
    pred_sr->GetXaxis()->SetRangeUser(xmin,xmax);
    sr->GetXaxis()->SetRangeUser(xmin,xmax);
   pred_sr->SetTitle(title);
   }
 else if(varName=="MET")
    {
    xmin_=0,xmax_=200,xmin=0,xmax=200;
    ymin=0 , ymax=2.99, ymin_=0 , ymax_=0.1;
    pred_sr->Rebin(rebin);
    sr->Rebin(rebin);
    pred_sr->GetXaxis()->SetRangeUser(xmin,xmax);
    sr->GetXaxis()->SetRangeUser(xmin,xmax);
   pred_sr->SetTitle(title);
   }
 else if(varName=="BestPhotonEta" || varName=="BestPhotonPhi" || varName=="ElectronEta" || varName=="ElectronPhi" )
   {//rebin=1;
    xmin_=-5,xmax_=5,xmin=-5,xmax=5;
    ymin=0 , ymax=3.99, ymin_=0 , ymax_=0.1;
    pred_sr->Rebin(rebin);
    sr->Rebin(rebin);
    pred_sr->GetXaxis()->SetRangeUser(xmin,xmax);
    sr->GetXaxis()->SetRangeUser(xmin,xmax);
   pred_sr->SetTitle(title);
   }
 else if(varName=="EMObj_Pt" || varName=="tagObj_Pt" || varName=="EMObj_Pt_elec0" || varName=="tagObj_Pt_elec0")
    {
      //      rebin=1;
         xmin_=40,xmax_=1400,xmin=40,xmax=1400;
      //   xmin_=100,xmax_=200,xmin=100,xmax=200;
    ymin=0 , ymax=2.99, ymin_=0 , ymax_=0.05;
    pred_sr->Rebin(rebin);
    sr->Rebin(rebin);
    pred_sr->GetXaxis()->SetRangeUser(xmin,xmax);
    sr->GetXaxis()->SetRangeUser(xmin,xmax);
   pred_sr->SetTitle(title);
   }

 if(ntuples=="v18")
   {
     if(varName=="invMass")    xmin_=80,xmax_=100,xmin=80,xmax=100;
     if(varName=="Qmulti")     xmin_=0,xmax_=16,xmin=0,xmax=16;
     if(varName=="nJets")     xmin_=0,xmax_=25,xmin=0,xmax=25;
     ymin=0 , ymax=3.99, ymin_=0.0005 , ymax_=.2;
       pred_sr->Rebin(rebin);
    sr->Rebin(rebin);
}
 if(ntuples!="v18")
   ymin_=0.5 , ymax_=100000000;

   for(int i=xmin_;i<=3;i++) 
     { cout<<pred_sr->GetBinContent(i)<<" +- "<<pred_sr->GetBinError(i)<<endl;}
   cout<<"The sr content"<<endl; 
   
   for(int i=xmin_;i<=3;i++) 
   { cout<<sr->GetBinContent(i)<<" +- "<<sr->GetBinError(i)<<endl;} 
 /*  cout<<"==============="<<endl; */

  


  TPad *pad1 = new TPad("pad1","pad1",0,0.325,1,1);
  pad1->SetBottomMargin(0);
  pad1->SetBottomMargin(0.3);
  //TPad *pad1 = new TPad("pad1","pad1",0,0.9,1,0.1);                                                                                                         
  TPad *pad2 = new TPad("pad1","pad1",0,0.0,1,0.3);
  pad2->SetTopMargin(0);
  pad2->SetBottomMargin(0.3);

  pad1->Draw();pad1->SetGridx();

  pad1->cd();
  if(ntuples!="v18")
    pad1->SetLogy();
    pred_sr->SetTitle(0);

  pred_sr->GetXaxis()->SetRangeUser(xmin,xmax);
  sr->GetXaxis()->SetRangeUser(xmin,xmax);
  pred_sr->GetYaxis()->SetLabelSize(0.06);
  if(ntuples=="v18")
    {
      pred_sr->GetYaxis()->SetTitle("Fake rate");
      ymin_=0.0005,ymax_=0.09;
      //      pad1->SetLogy();

    }
  else
    pred_sr->GetYaxis()->SetTitle("Entries");

  pred_sr->GetXaxis()->SetTitle(0);
  pred_sr->GetYaxis()->SetTitleSize(0.07);
  pred_sr->GetYaxis()->SetTitleOffset(0.72);
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
  pred_sr->Draw("hist");
  sr->Draw("ep sames");

   TPaveStats *ptstats = new TPaveStats(0.7,0.85,0.9,0.9,"brNDC");
   ptstats->SetName("stats");
   ptstats->SetBorderSize(1);
   ptstats->SetFillColor(0);
   ptstats->SetLineColor(2);
   ptstats->SetTextAlign(12);
   ptstats->SetTextColor(2);
   ptstats->SetTextFont(42);
   //   TText *ptstats_LaTex = ptstats->AddText("Integral =  140.5");
   ptstats->SetOptStat(1000000);
   ptstats->SetOptFit(0);
   pred_sr->GetListOfFunctions()->Add(ptstats);
   ptstats->SetParent(pred_sr);
   TPaveStats *ptstats2 = new TPaveStats(0.7,0.8,0.9,0.85,"brNDC");
   ptstats2->SetName("stats");
   ptstats2->SetBorderSize(1);
   ptstats2->SetFillColor(0);
   ptstats2->SetLineColor(4);
   ptstats2->SetTextAlign(12);
   ptstats2->SetTextColor(4);
   ptstats2->SetTextFont(42);
   //   TText *ptstats2_LaTex = ptstats2->AddText("Integral =  140.5");
   ptstats2->SetOptStat(1000000);
   ptstats2->SetOptFit(0);
   sr->GetListOfFunctions()->Add(ptstats2);
   ptstats2->SetParent(sr);
  double chi=pred_sr->Chi2Test(sr,"WW CHI2");
  int NDF=chi/pred_sr->Chi2Test(sr,"WW CHI2/NDF");
  double p=pred_sr->Chi2Test(sr,"WW p");
  textOnTop.SetTextSize(0.06);
  intLumiE.SetTextSize(0.06);
  //  if(isPaper) textOnTop.DrawLatexNDC(0.12,0.91,"CMS #it{#bf{Simulation Supplementary}}");                                                                 
  textOnTop.DrawLatexNDC(0.1,0.91,"CMS #it{#bf{Simulation Preliminary}}");
  if(year=="2016")
    intLumiE.DrawLatexNDC(0.7,0.91,"#bf{35.9 fb^{-1} (13 TeV)}");
  if(year=="2017")
    intLumiE.DrawLatexNDC(0.7,0.91,"#bf{41.5 fb^{-1} (13 TeV)}");
  if(year=="2018")
    intLumiE.DrawLatexNDC(0.7,0.91,"#bf{58.7 fb^{-1} (13 TeV)}");
    //  intLumiE.DrawLatexNDC(0.6,0.91,"#bf{28 fb^{-1} (13 TeV) (A+B+C)}");
  //   intLumiE.DrawLatexNDC(0.7,0.91,"#bf{59.06 fb^{-1} (13 TeV)}");
  if(year=="full_Run2")
    intLumiE.DrawLatexNDC(0.7,0.91,"#bf{137 fb^{-1} (13 TeV)}");
  char chi2[1000],chi1[1000];
  // sprintf(chi2,"Chi2/NDF = %f",chi_NDF);
  sprintf(chi1,"Chi2/NDF = %f / %d , p = %f",chi,NDF,p);

  TLegend *legend = new TLegend(0.5,0.8,0.9,0.9);
  legend->SetNColumns(1);
  legend->SetBorderSize(1);
  //  TLegend *legend1 = new TLegend(0.1,0.82,0.45,0.9);
  //  legend1->SetHeader("with HEM veto","C");                               // option "C" allows to center the header                                      
  //  legend1->SetHeader(chi2,"C");
  // legend1->SetHeader(chi1,"C");
  //  legend1->SetHeader(p,"C");
  cout<<"CR ===> "<<pred_sr->Integral()<<endl;//"+-"<<pred_sr->ErrorIntegral()<<endl;
  cout<<"SR ===> "<<sr->Integral()<<endl;
  // legend1->SetTextSize(0.04);
 
  legend->SetTextSize(0.04);
  // legend1->Draw();
  if(ntuples=="v18")
    {
      legend = new TLegend(0.65,0.7,0.9,0.9);
      legend->AddEntry(sr,"FR(Data)","lp");
      legend->AddEntry(pred_sr,"FR(MC)","lp");
   legend->SetTextSize(0.06);
    }
  if(ntuples!="v18")
    {
      legend->AddEntry(sr,"SR (1 tag e + 0 probe e + 1 #gamma) ","lp");
      legend->AddEntry(pred_sr,"CR (1 tag e + 1 probe e + 0 #gamma)","lp");
   legend->SetTextSize(0.04);
    }
      //  legend->AddEntry(sr,"MC","lp");

  legend->Draw();
  //  legend1->Draw();
  /* ptstats->Draw(); */
  /* ptstats2->Draw(); */

  TH1D *h4 = (TH1D*)pred_sr->Clone("h4");
  TH1D *h3 = (TH1D*)sr->Clone("h3");

  //  TPad *pad2 = new TPad("pad1","pad1",0,0.0,1,0.3);
  pad2->Draw();
  pad2->SetTopMargin(0);
  pad2->SetBottomMargin(0.3);
  pad2->cd();
  pad2->SetGrid(1);

  h3->GetYaxis()->SetRangeUser(0.5,1.5);
  
  h3->SetLineColor(kBlack);
  h3->SetLineStyle(1);
  h3->SetLineWidth(2);
  if(ntuples=="v18")
    {
      h3->SetMinimum(0.6);  // Define Y ..                                                                                                   
      h3->SetMaximum(4.0); // .. range                                                                                                         
    }
  else
    {
      h3->SetMinimum(0);  // Define Y ..
      h3->SetMaximum(0.1); // .. range                                                                                                                      
    }
  h3->Sumw2();
  h3->SetStats(0);      // No statistics on lower plot                                                                                        
  h3->Divide(h4);
  h3->SetMarkerStyle(20);
  h3->SetMarkerSize(0.6);
  // gStyle->SetOptStat(0);                                                                                                                   
  h3->Draw("ep");       // Draw the ratio plot                                                                                                

  h3->SetTitle(0);
  h3->GetXaxis()->SetTitleOffset(0.88);
  if(varName=="BestPhotonEta")  h3->GetXaxis()->SetTitle("EM Object #eta");
  else if(varName=="ElectronEta")  h3->GetXaxis()->SetTitle("tag Object #eta");
  else h3->GetXaxis()->SetTitle(varName);
  h3->GetXaxis()->SetTitleSize(0.17);
  h3->GetXaxis()->SetLabelSize(0.22);


  if(ntuples == "v18")
    {h3->GetYaxis()->SetTitle("#frac{FR(Data)}{ FR(MC)}");
      h3->GetYaxis()->SetTitleOffset(0.18);
      h3->GetYaxis()->SetTitleSize(0.18);

    }
  else{
    if(data)  h3->GetYaxis()->SetTitle("FR (data)");
    if(!data)  h3->GetYaxis()->SetTitle("FR (MC)");
    h3->GetYaxis()->SetTitleOffset(0.22);
    h3->GetYaxis()->SetTitleSize(0.22);

  }
  TLine *line;
  
  line = new TLine(xmin_,1,xmax_,1);
  h3->GetYaxis()->SetNdivisions(5);

  line->SetLineColor(1);
  line->SetLineStyle(1);
  line->SetLineWidth(1);
  line->Draw();

  

  //  h3->GetYaxis()->SetNdivisions(5);
  /* h3->GetYaxis()->SetTitleOffset(0.22); */
  /* h3->GetYaxis()->SetTitleSize(0.22); */
  h3->GetYaxis()->SetLabelSize(0.18);

  if(ntuples!="v18")
    {
      h3->Write();
      for(int i=0;i<=3;i++) 
	{ //cout<<h3->GetBinLowEdge(i)<<" : "<<h3->GetBinContent(i)<<endl;} 
	  cout<<h3->GetBinContent(i)<<" +- "<<h3->GetBinError(i)<<endl;}
    }
  if(ntuples=="v18")
    {
      
      h3->Scale(ratio);
      h3->Write("SF");
      for(int i=0;i<=3;i++)
        {
          cout<<ratio<<" : "<<h3->GetBinContent(i)<<" +- "<<h3->GetBinError(i)<<endl;
        }
      
      TH1D *avg_SF=new TH1D("avg_SF"," Scale factor for fakerates ",1,-1,1);
      avg_SF->SetBinContent(1,h3->GetBinContent(1));
      avg_SF->SetBinError(1,h3->GetBinError(1));
      avg_SF->Write("SF");
      
    }
  /* cout<<"The TF content in bin"<<endl; */
  /* for(int i=0;i<=45;i++) */
  /*   { cout<<h3->GetBinLowEdge(i)<<" : "<<h3->GetBinContent(i)<<endl;} */
  /* cout<<"==============="<<endl; */
  
  /* /\* for(int i=bin0;i<=bin1;i++) *\/ */
  /* /\*   { cout<<TF->GetBinContent(i)<<endl;} *\/ */
  /* /\* cout<<"The Transfer Factor error in bin"<<endl; *\/ */
  /* for(int i=0;i<=45;i++) */
  /*   { cout<<h3->GetBinError(i)<<endl;} */
  c1->SaveAs(pdf);
  c1->SaveAs(png);


}

