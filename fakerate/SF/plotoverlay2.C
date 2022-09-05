void plotoverlay(TString varName,  TString year,  TString ntuples, int rebin, bool data=false)
{
    gStyle->SetOptStat(kFALSE);

    TFile *f1, *f2,*f, *f3,*f4,*f6;
  TString path, path1,path2;
  path="./rootoutput/v1/withsimpleselections_ST200_pxveto/";
  path1="./rootoutput/v1/withsimpleselections_ST200/";
  path2="./rootoutput/v1/withsimpleselections_ST200_tt/";
  TLatex textOnTop,intLumiE;
  TString filename,filename1,filename2,title,filename3,filename4,filename6;
  double ymin=0,ymax=1.99,xmin=0,xmax=0, ymin_=0.5, ymax_=100000;
  //  bool data=false;
  //  filename= path+"DYJets_"+year+"_CR_v18.root";
  //  filename= path1+"DYJets_"+year+"_CR_v18.root";
  // filename1= path1+"ZGJets_"+year+"_CR_v18.root";
  //  filename1= path1+"WJets_"+year+"_CR_v18.root";
  // filename2=path1+"ZGJ_"+year+"_CR_v18.root";
  if(!data){
    filename= path1+"TTWDYG_2016_CR_v18.root";
    filename1= path1+"TTWDYG_2017_CR_v18.root";
    filename2= path1+"TTWDYG_2018_CR_v18.root";
    //    filename= path1+"TTGJ_2016_CR_v18.root";
    //   filename1= path1+"TTGJ_2017_CR_v18.root";
    //    filename2=path1+"TTGJ_2018_CR_v18.root"; 
  }
   if(data){
    filename= path1+"Run2016_CR_v18.root";
    filename1= path1+"Run2017_CR_v18.root";
    filename2= path1+"Run2018_CR_v18.root";
  }
  f = new TFile(filename);
  f1 = new TFile(filename1);
  if(ntuples=="v3") f2 = new TFile(filename2);

  //  f3 = new TFile(filename3);
  // f4 = new TFile(filename4);
  //if(ntuples=="v3") f6 = new TFile(filename6);
  
  TCanvas *c1;
 
  TH1D *h_DY,*h_tt,*h_w, *h_DY_sr,*h_tt_sr,*h_w_sr, *h_DY_cr,*h_tt_cr,*h_w_cr;
  c1 = new TCanvas("stackhist","stackhist",900,1000);
    TString varName1=varName + "_elec0";
    varName1=varName;
  h_DY_cr = (TH1D*)f->Get(varName);
  h_tt_cr = (TH1D*)f1->Get(varName);
  if(ntuples=="v3") h_w_cr  = (TH1D*)f2->Get(varName);

  h_DY_sr = (TH1D*)f->Get(varName1);
  h_tt_sr = (TH1D*)f1->Get(varName1);
  if(ntuples=="v3")   h_w_sr  = (TH1D*)f2->Get(varName1);

  ///=====================
  if(varName=="Qmulti")
    {
      xmin=0,xmax=50;
      title="Qmulti";
    }
  if(varName=="nJets")
    {
      xmin=0,xmax=20;
      title="nJets";
    }
  if(varName=="EMObj_Pt")
    {
      xmin=0,xmax=1400;
      title="probe/e pT";
    }
  if(varName=="invMass")
    {
      xmin=80,xmax=100;
      title="M(e,e)";
    }
  if(varName=="ElectronPhi" || varName=="BestPhotonPhi" || varName=="ElectronEta" || varName=="BestPhotonEta")
    {
      ymin_=0 , ymax_=1500*rebin/2;      
      xmin=-4,xmax=4;
      if(varName=="ElectronPhi") title="tag e #phi";
      if(varName=="BestPhotonPhi") title="probe e #phi";
      if(varName=="ElectronEta") title="tag e #eta";
      if(varName=="BestPhotonEta") title="probe e #eta";

    }



  ////============
  int tmp=rebin;
  rebin=1;
  h_DY_sr->Rebin(rebin);
  h_tt_sr->Rebin(rebin);
  if(ntuples=="v3")   h_w_sr->Rebin(rebin);
  rebin=tmp;
  h_DY_cr->Rebin(rebin);
  h_tt_cr->Rebin(rebin);
  if(ntuples=="v3")   h_w_cr->Rebin(rebin);

   
  h_DY = (TH1D*)h_DY_sr->Clone("h_DY");
  h_tt = (TH1D*)h_tt_sr->Clone("h_tt");
  if(ntuples=="v3")   h_w = (TH1D*)h_w_sr->Clone("h_w");

  
  h_DY->Divide(h_DY_cr);
  h_tt->Divide(h_tt_cr);
  TPad *pad1 = new TPad("pad1","pad1",0,0.325,1,1);
  pad1->SetBottomMargin(0);
  pad1->SetBottomMargin(0.3);
  TPad *pad2 = new TPad("pad1","pad1",0,0.0,1,0.3);
  pad2->SetTopMargin(0);
  pad2->SetBottomMargin(0.3);

  TLegend *legend = new TLegend(0.55,0.8,0.9,0.9);
  legend->SetNColumns(1);
  legend->SetBorderSize(1);
  legend->SetTextSize(0.04);
  if(ntuples!="v3")
    {
  
      pad1->Draw();pad1->SetGridx();
      pad1->cd();

      h_DY->GetXaxis()->SetRangeUser(xmin,xmax);
      h_tt->GetXaxis()->SetRangeUser(xmin,xmax);
      h_DY->SetLineColor(kRed);
      h_tt->SetLineColor(kBlue);
      h_DY->Draw();
      h_tt->Draw("sames");
      h_DY->SetTitle(0);
      h_tt->SetTitle(0);
      legend->AddEntry(h_DY,"DY","lp");
      legend->AddEntry(h_tt,"tt","lp");
      }
  if(ntuples=="v3") 
    {
      pad1 = new TPad("pad1","pad1",0,0,1,1);
      pad1->SetBottomMargin(0);
      pad1->SetBottomMargin(0.3);
      pad1->Draw();pad1->SetGridx();
      pad1->cd();
      if(!(varName=="ElectronPhi" || varName=="BestPhotonPhi" || varName=="ElectronEta" || varName=="BestPhotonEta" ) )
	pad1->SetLogy();
      h_DY_cr->GetXaxis()->SetRangeUser(xmin,xmax);
      h_tt_cr->GetXaxis()->SetRangeUser(xmin,xmax);
      //      h_DY_cr->GetYaxis()->SetRangeUser(0.5,100000);
      //      h_tt_cr->GetYaxis()->SetRangeUser(0.5,100000);
      h_DY_cr->GetYaxis()->SetRangeUser(ymin_,ymax_);
      h_tt_cr->GetYaxis()->SetRangeUser(ymin_,ymax_);

      h_DY_cr->SetLineColor(kRed);
      h_tt_cr->SetLineColor(kBlue);
      h_w_cr->SetLineColor(kGreen);
      //      h_DY_sr->SetLineColor(kRed);
      //      h_tt_sr->SetLineColor(kBlue);
      //      h_w_sr->SetLineColor(kGreen);
      //      h_DY_sr->SetLineStyle(2);
      //      h_tt_sr->SetLineStyle(2);
      //      h_w_sr->SetLineStyle(2);
      //      h_DY_sr->SetLineWidth(2);
      //      h_DY_sr->SetLineWidth(2);
      //      h_DY_sr->SetLineWidth(2);
      if(!data)
	{
	  h_DY_cr->Draw("hist");
	  h_w_cr->Draw("hist sames");
	  h_tt_cr->Draw("hist sames");
	}
      if(data)
        {
          h_DY_cr->Draw();
          h_w_cr->Draw("sames");
          h_tt_cr->Draw("sames");
        }

	  //      h_DY_sr->Draw("hist sames");
      //      h_w_sr->Draw("hist sames");
      //      h_tt_sr->Draw("hist sames");

      h_DY_cr->SetTitle(0);
      h_tt_cr->SetTitle(0);
      h_w_cr->SetTitle(0);
      //      legend->AddEntry(h_DY_cr,"DY","lp");
      //      legend->AddEntry(h_w_cr,"W Jets","lp");
      //      legend->AddEntry(h_tt_cr,"TT Jets","lp");
      //      legend->AddEntry(h_DY_cr,"TT + Jets","lp");
      //      legend->AddEntry(h_tt_cr,"TT + g","lp");
      //      legend->AddEntry(h_w_cr,"TTG Jets","lp");

      legend->AddEntry(h_DY_cr,"2016","lp");
      legend->AddEntry(h_tt_cr,"2017","lp");
      legend->AddEntry(h_w_cr,"2018","lp");
      h_DY_cr->GetXaxis()->SetTitle(title);

    }


  legend->Draw();

  textOnTop.SetTextSize(0.04);
  intLumiE.SetTextSize(0.04);
  //  if(isPaper) textOnTop.DrawLatexNDC(0.12,0.91,"CMS #it{#bf{Simulation Supplementary}}");                                                                               
  textOnTop.DrawLatexNDC(0.1,0.91,"CMS #it{#bf{Simulation Preliminary}}");
  if(year=="2016")
    intLumiE.DrawLatexNDC(0.7,0.91,"#bf{35.9 fb^{-1} (13 TeV)}");
  if(year=="2017")
    intLumiE.DrawLatexNDC(0.7,0.91,"#bf{41.5 fb^{-1} (13 TeV)}");
  if(year=="2018")
    intLumiE.DrawLatexNDC(0.7,0.91,"#bf{58.7 fb^{-1} (13 TeV)}");
  //    intLumiE.DrawLatexNDC(0.7,0.91,"#bf{59.6 fb^{-1} (13 TeV)}");
  if(year=="full_Run2")
    intLumiE.DrawLatexNDC(0.7,0.91,"#bf{137 fb^{-1} (13 TeV)}");

  if(ntuples!="v3"){
  //============= ratio plot ============//  
  pad2->Draw();
  pad2->SetTopMargin(0);
  pad2->SetBottomMargin(0.3);
  pad2->cd();
  pad2->SetGrid(1);
  TH1D *h1 = (TH1D*)h_DY->Clone("h1");
  TH1D *h2 = (TH1D*)h_tt->Clone("h2");
  if(ntuples=="v3")  h2 = (TH1D*)h_w->Clone("h2");
  h2->Divide(h1);
  h2->SetMinimum(ymin);  // Define Y ..                                                                                                                                
  h2->SetMaximum(ymax); // .. range                                                                                                                                    

  h2->Draw("ep");
  h2->SetTitle(0);
  h2->GetXaxis()->SetTitleOffset(0.88);
  h2->GetXaxis()->SetTitle(title);
  h2->GetXaxis()->SetTitleSize(0.17);
  h2->GetXaxis()->SetLabelSize(0.22);

  //  h2->GetYaxis()->SetTitle("DY/tt");
  h2->GetYaxis()->SetTitle("DY/W");
  TLine *line;

  line = new TLine(xmin,1,xmax,1);
  h2->GetYaxis()->SetNdivisions(5);

  line->SetLineColor(1);
  line->SetLineStyle(1);
  line->SetLineWidth(1);
  line->Draw();

  h2->GetYaxis()->SetTitleOffset(0.17);
  h2->GetYaxis()->SetTitleSize(0.25);
  h2->GetYaxis()->SetLabelSize(0.21);
  }
}
