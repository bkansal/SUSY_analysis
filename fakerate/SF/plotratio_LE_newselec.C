\1;95;0c#include<iostream>
#include<iomanip>
#include"TH1.h"
#include"TROOT.h"
#include"TH2.h"
#include"TFile.h"
#include"TDirectory.h"
#include"TTree.h"
#include"TBrowser.h"
#include"TF1.h"
#include<string>
#include<vector>
#include"TGraphErrors.h"
#include"TGraph.h"
#include"TLegend.h"
#include"TLatex.h"
#include"TCanvas.h"
#include"THStack.h"
#include"TStyle.h"

//bool ExpvsPred=true,SRvsCR=false;
//bool ExpvsPred=false,SRvsCR=true;
//vector<int> col={kGray,kTeal+9,kRed,kCyan-1,kBlack};
vector<int> col={kGray,kTeal+9,kOrange,kCyan-1,kPink};
//vector<int> col={kOrange,kCyan-1,kBlack};

vector<double> METLowEdge_v2={200,250,300,370,450,600,750,900,2000};
vector<double> PhoLowEdge={0,100,120,140,160,180,200,220,250,280,320,380,450,550,650,750};
void decorate(TH1D*,int,const char*);

void plotratio_LE_newselec(TString varname,TString title1,bool ExpvsPred, bool SRvsCR, bool MC)
{
  TFile *f1,*f_0,*f_1,*f_2,*f_3,*f_4,*f2;
  //  bool LE=true;
  string lep="LM";
  //  bool LE=false;

    TString path = "./rootoutput/SF/";
   path="./rootoutput/SF_withtrgprescale_HLTmatch_M60to120/";
   //   path="./rootoutput/SF_withtrgprescale_HLTmatch_M80to100/";
    //path="rootoutput/SF_with_csv_cut/";
   //   path="rootoutput/SF_without_csv_cut/";
  path="./rootoutput/v1/withsimpleselections_ST200_zpt600/";
  path="rootoutput/tmp/";
  TString path1;

  //  path="./";
  if(title1=="full_Run2"){
    /* path1=path+"Run2_METdata_CR_v18.root"; */
    path1=path+"Run2_CR_v18.root";
    // f1 = new TFile(path1);
    //    path1=path+"TTWDY_CR_v18.root";
    //    path1=path+"TTGJets_"+title1+"_CR_v18_v2.root";
    f1 = new TFile(path1);
    path1=path+"TTGJets_CR_v18.root";
    f_0 = new TFile(path1);
    path1=path+"TTJets_CR_v18.root";
    f_1 = new TFile(path1);
    path1=path+"WJets_CR_v18.root";
    f_2 = new TFile(path1);
    path1=path+"WGJets_CR_v18.root";
    f_3 = new TFile(path1);
    path1=path+"DYJets_CR_v18.root";
    f_4 = new TFile(path1);
    }
  

  else
    {

      //      path1=path+"Run"+title1+"_METdata_CR_v18.root";
      if(!MC)   path1=path+"Run"+title1+"_CR_v18.root";
      // f1 = new TFile(path1);
          if(MC) path1=path+"TTWDY_"+title1+"_CR_v18.root";
      //            if(MC) path1=path+"DYJets_"+title1+"_CR_v18.root";
      //path1=path+"TTGJets_"+title1+"_CR_v18_v2.root";
      f1 = new TFile(path1);
      path1=path+"TTGJets_"+title1+"_CR_v18.root";
      f_0 = new TFile(path1);
      path1=path+"TTJets_"+title1+"_CR_v18.root";
      f_1 = new TFile(path1);
      path1=path+"WJets_"+title1+"_CR_v18.root";
      f_2 = new TFile(path1);
      path1=path+"WGJets_"+title1+"_CR_v18.root";
      f_3 = new TFile(path1);
      path1=path+"DYJets_"+title1+"_CR_v18.root";
      f_4 = new TFile(path1);
    }
  

  
  
  TLatex textOnTop,intLumiE;
  TString name;
  if(MC)  name="Run"+title1+"_SF_FR_mc";
  if(!MC) name="Run"+title1+"_SF_FR_data";
  //  TString name="Run_SF_FR";
  TString rootout = name + ".root";

  TString title="Tranfer factors using NJets x Nbjets binning";
  double xMin=-100000,xMax = 100000, xmin_=0, xmax_=0;
  TString png,pdf;
  if(ExpvsPred)
    {
      pdf = path+"/PDF/closure/"+varname+"_"+title1+"_v2.pdf";
      png= path+"/PDF/closure/"+varname+"_"+title1+"_v2.png";
    }
  else if(SRvsCR)
    {
      pdf = path+"/PDF/FR/"+varname+"_"+title1+"_v2.pdf";
      png= path+"/PDF/FR/"+varname+"_"+title1+"_v2.png";
    
      cout<<"root file name : "<<rootout<<endl;
      TFile *fout =new TFile(rootout,"recreate");
      fout->cd();
    }

  
  int k=1;

  TString varName2_,varname_elec1,varname_elec0;
  TLegend *legend; 
  TLegend *legend1; 

    {
      legend= new TLegend(0.6,0.7,0.9,0.99);
      legend1= new TLegend(0.6,0.7,0.9,0.99);
      varname_elec1=varname;
      varname_elec0=varname+"_elec0";
    }

  TString  varName[1]={varname};
  TString varName1[1]={varname_elec0};
  if(ExpvsPred)  varName2_=varname+"_elec1_closure";
  else if(SRvsCR)  varName2_=varname_elec1;
  
  TString varName2[1]={varName2_};
  TString name1;
  double nbin,bin0, yset_,bin1,ymin_,ymax_;
  //  double nbin,bin0, bin1;
  TH1D *total;
  TH1D *TF[k];
  THStack *stack[k];
  TCanvas *c1[k];
  TString pdf1;
  for(int i=0; i<k;i++)
    {
      TH1D *fail_accept,*fail_id,*fail_iso,*cr,*fake_photon,*sr,*h_0_cr,*h_1_cr,*h_2_cr,*h_3_cr,*h_4_cr,*h_0_sr,*h_1_sr,*h_2_sr,*h_3_sr,*h_4_sr;
      THStack *hs_var=new THStack("var_Stack",varName[i]);
      THStack *hs_var_cr=new THStack("var_Stack_cr",varName[i]);

      cout<<varName[i]<<endl;

      name1=varname;
      cr          = (TH1D*)f1->Get(varName2[i]);
      sr          = (TH1D*)f1->Get(varName1[i]);
      h_0_cr=(TH1D*)f_0->FindObjectAny(varName2[i]);
      h_1_cr=(TH1D*)f_1->FindObjectAny(varName2[i]);
      h_2_cr=(TH1D*)f_2->FindObjectAny(varName2[i]);
      h_3_cr=(TH1D*)f_3->FindObjectAny(varName2[i]);
      h_4_cr=(TH1D*)f_4->FindObjectAny(varName2[i]);
      h_0_sr=(TH1D*)f_0->FindObjectAny(varName1[i]);
      h_1_sr=(TH1D*)f_1->FindObjectAny(varName1[i]);
      h_2_sr=(TH1D*)f_2->FindObjectAny(varName1[i]);
      h_3_sr=(TH1D*)f_3->FindObjectAny(varName1[i]);
      h_4_sr=(TH1D*)f_4->FindObjectAny(varName1[i]);
      
      cr->SetStats(111);
      sr->SetStats(111);
      int rebin=1;
      if(varName[i]=="invMass")
	{
	  ymin_=0.1, ymax_=100000;
	  rebin=5;
	  nbin=2000/rebin, bin0=0, bin1=500;
	  xmin_=60,xmax_=120;
		 //xmin_=0,xmax_=200;
	}

      if(varName[i]=="Qmulti")
	{
	  nbin=50, bin0=0, bin1=50;
	  xmin_=0,xmax_=50;
	  ymin_=0.1, ymax_=100000;
	  rebin=2;
	}
      if(varName[i]=="nJets")
	{
	  nbin=25, bin0=0, bin1=25;
	  xmin_=2,xmax_=15;
	  ymin_=0.1, ymax_=100000;
	}
      if( varName[i]=="nvtx")
	{
	  nbin=100, bin0=0, bin1=100;
	  xmin_=0,xmax_=100;
	  ymin_=0.1, ymax_=100000;
	  rebin=2;
	  
	}
      if(varName[i]=="nBTags" || varName[i]=="NEMobj")
	{
	  nbin=10, bin0=0, bin1=10;
	  xmin_=0,xmax_=10;
	  ymin_=0.1, ymax_=100000;
	  rebin=1;
	}
      if(varName[i]=="ST")
	{
	  rebin=10;
	  nbin=1000/rebin, bin0=0, bin1=2000;
	  xmin_=300,xmax_=1400;
          ymin_=0.1, ymax_=100000;
	}
      if(varName[i]=="EMObj_Pt")
	{
	  rebin=10;
	  nbin=300/rebin, bin0=0, bin1=1500;
	  xmin_=100,xmax_=1000;
          ymin_=0.1, ymax_=100000;
	}
      if(varName[i]=="MET")
	{
	  rebin=1;
	  nbin=200/rebin, bin0=0, bin1=2000;
	  xmin_=0,xmax_=200;
          ymin_=0.1, ymax_=100000;
	}
      if(varName[i]=="BestPhotonEta")
	{
	  rebin=5;
	  nbin=400/rebin, bin0=-5, bin1=5;
	  xmin_=-5,xmax_=5;
          ymin_=0.1, ymax_=100000;
	}
      if(varName[i]=="BestPhotonPhi")
	{
	  rebin=5;
	  nbin=400/rebin, bin0=-5, bin1=5;
	  xmin_=-5,xmax_=5;
          ymin_=0.1, ymax_=100000;
	}

      TF[i]= new TH1D(varName[i],"Transfer factor for SP : NJets x Nbtag & EW : wtag & htag",nbin,bin0,bin1);
      
      cr->Rebin(rebin);
      sr->Rebin(rebin);
      h_0_cr->Rebin(rebin);
      h_1_cr->Rebin(rebin);
      h_2_cr->Rebin(rebin);
      h_3_cr->Rebin(rebin);
      h_4_cr->Rebin(rebin);
      h_0_sr->Rebin(rebin);
      h_1_sr->Rebin(rebin);
      h_2_sr->Rebin(rebin);
      h_3_sr->Rebin(rebin);
      h_4_sr->Rebin(rebin);
    
      
      
      c1[i] = new TCanvas("stackhist","stackhist",900,1200);
      c1[i]->cd();
      /* cr->Divide(sr); */
      /* cr->Draw(); */
      gStyle->SetOptStat(0);
      legend->SetNColumns(2);
      legend1->SetNColumns(2);

      textOnTop.SetTextSize(0.03);
      intLumiE.SetTextSize(0.03);
      //  if(isPaper) textOnTop.DrawLatexNDC(0.12,0.91,"CMS #it{#bf{Simulation Supplementary}}");
      textOnTop.DrawLatexNDC(0.1,0.9,"CMS #it{#bf{Simulation Preliminary}}");
      if(title1=="2016")
	intLumiE.DrawLatexNDC(0.7,0.9,"#bf{35.9 fb^{-1} (13 TeV)}");
      if(title1=="2017")
	intLumiE.DrawLatexNDC(0.7,0.9,"#bf{41.5 fb^{-1} (13 TeV)}");
      if(title1=="2018")
	intLumiE.DrawLatexNDC(0.7,0.9,"#bf{59.6 fb^{-1} (13 TeV)}");
      if(title1=="full_Run2")
	intLumiE.DrawLatexNDC(0.7,0.9,"#bf{137 fb^{-1} (13 TeV)}");

      TPad *pad1 = new TPad("pad1","pad1",0,0.6,1,0.96);
      //  pad1->SetBottomMargin(0);
      TPad *pad2 = new TPad("pad2","pad2",0,0.3,1,0.6);
      TPad *pad3 = new TPad("pad3","pad3",0,0,1,0.3);
      /* TPad *pad1 = new TPad("pad1","pad1",0,0.75,1,0.99); */
      /* //  pad1->SetBottomMargin(0); */
      /* TPad *pad2 = new TPad("pad2","pad2",0,0.5,1,0.75); */
      /* TPad *pad3 = new TPad("pad3","pad3",0,0,1,0.5); */
      pad3->SetTopMargin(0);
      pad1->SetTopMargin(0);
      pad2->SetTopMargin(0);
      pad1->SetBottomMargin(0);
      pad2->SetBottomMargin(0);
      pad1->Draw();pad1->SetGridx();
      pad2->Draw();pad2->SetGridx();
      pad3->Draw();pad3->SetGridx();pad3->SetGridy();

      pad1->cd();
      pad1->SetLogy();

      gStyle->SetPalette(kOcean);
      sr->SetFillStyle(3008);
      sr->SetFillColor(kGray);      
      sr->SetTitle(0);
      sr->GetYaxis()->SetRangeUser(1,100000);
      sr->GetYaxis()->SetLabelSize(0.07);
      sr->GetYaxis()->SetTitle("Events");
      sr->GetYaxis()->SetTitleSize(0.07);
      sr->GetYaxis()->SetTitleOffset(0.72);
      sr->SetLineColor(kBlack);

      h_0_sr->GetXaxis()->SetRangeUser(xmin_,xmax_);
      h_1_sr->GetXaxis()->SetRangeUser(xmin_,xmax_);
      h_2_sr->GetXaxis()->SetRangeUser(xmin_,xmax_);
      h_3_sr->GetXaxis()->SetRangeUser(xmin_,xmax_);
      h_4_sr->GetXaxis()->SetRangeUser(xmin_,xmax_);
      decorate(h_0_sr,0,f_0->GetName());
      decorate(h_1_sr,1,f_1->GetName());
      decorate(h_2_sr,2,f_2->GetName());
      decorate(h_3_sr,3,f_3->GetName());
      decorate(h_4_sr,4,f_4->GetName());
      hs_var->Add(h_0_sr);
      hs_var->Add(h_1_sr);
      hs_var->Add(h_2_sr);
      hs_var->Add(h_3_sr);
      hs_var->Add(h_4_sr);
      hs_var->Draw("hist");
      hs_var->GetYaxis()->SetLabelSize(0.10);
      hs_var->SetTitle(0);

      hs_var->GetXaxis()->SetLimits(xmin_,xmax_);
      hs_var->SetMinimum(ymin_);
      hs_var->SetMaximum(ymax_);
      sr->Draw("sames");
 
      if(ExpvsPred)   legend->SetHeader("Expected","C"); 
      else if(SRvsCR) legend->SetHeader("SR : 0 probe e & 1 probe photon","C"); 
      legend->AddEntry(h_0_sr,"t #bar{t} + #gamma","f");
      legend->AddEntry(h_1_sr,"t #bar{t}","f");
      legend->AddEntry(h_2_sr,"W(l#nu) + jets","f");
      legend->AddEntry(h_3_sr,"W(l#nu) + #gamma","f");
      legend->AddEntry(h_4_sr,"Z(ee) + jets","f");
      legend->Draw();
      
      pad2->cd();
      pad2->SetLogy();
      gStyle->SetPalette(kOcean);
      cr->SetFillStyle(3008);
      cr->SetFillColor(kGreen);      
      cr->SetTitle(0);
      cr->GetYaxis()->SetRangeUser(0.9,1000);
      cr->GetYaxis()->SetLabelSize(0.07);
      cr->GetYaxis()->SetTitle("Events");
      cr->GetYaxis()->SetTitleSize(0.07);
      cr->GetYaxis()->SetTitleOffset(0.72);
      cr->SetLineColor(kBlack);
      h_0_cr->GetXaxis()->SetRangeUser(xmin_,xmax_);
      h_1_cr->GetXaxis()->SetRangeUser(xmin_,xmax_); 
      h_2_cr->GetXaxis()->SetRangeUser(xmin_,xmax_);
      h_3_cr->GetXaxis()->SetRangeUser(xmin_,xmax_);
      h_4_cr->GetXaxis()->SetRangeUser(xmin_,xmax_);

      decorate(h_0_cr,0,f_0->GetName());
      decorate(h_1_cr,1,f_1->GetName());
      decorate(h_2_cr,2,f_2->GetName());
      decorate(h_3_cr,3,f_3->GetName());
      decorate(h_4_cr,4,f_4->GetName());
      hs_var_cr->Add(h_0_cr);
      hs_var_cr->Add(h_1_cr);
      hs_var_cr->Add(h_2_cr);
      hs_var_cr->Add(h_3_cr);
      hs_var_cr->Add(h_4_cr);
      hs_var_cr->Draw("hist");
      hs_var_cr->GetYaxis()->SetLabelSize(0.10);
      hs_var_cr->SetTitle("Events");
      hs_var_cr->GetXaxis()->SetLimits(xmin_,xmax_);

      hs_var_cr->SetMinimum(ymin_);
      hs_var_cr->SetMaximum(ymax_);
      cr->Draw("sames");

      if(SRvsCR)  legend1->SetHeader("CR : 1 probe e & 0 probe photon","C"); 
      else if(ExpvsPred) legend1->SetHeader("Predicted","C"); 
      legend1->AddEntry(h_0_cr,"t #bar{t} + #gamma","f");
      legend1->AddEntry(h_1_cr,"t #bar{t}","f");
      legend1->AddEntry(h_2_cr,"W(l#nu) + jets","f");
      legend1->AddEntry(h_3_cr,"W(l#nu) + #gamma","f");
      legend1->AddEntry(h_4_cr,"Z(ee) + jets","f");
      legend1->Draw();

      pad3->cd();

      pad3->Range(-1.221914,-0.6163887,21.19695,1);
      pad3->SetBottomMargin(0.3813369);

      pad3->SetGrid(1);

      TF[i]->Add(sr);
      TF[i]->Sumw2();
      TF[i]->SetStats(0);
      TF[i]->Divide(cr);
      TF[i]->Draw("ep");
      TF[i]->SetTitle(0);

      TF[i]->GetYaxis()->SetNdivisions(5);
      TF[i]->GetXaxis()->SetRangeUser(xmin_,xmax_);

     TLine *line;
      if(ExpvsPred)
	{
	  TF[i]->GetYaxis()->SetRangeUser(0,2);
	  line= new TLine(xmin_,1,xmax_,1);
	}
      else if(SRvsCR)
	{
	  if (varName[i]=="AllSBins_v6_CD" || varName[i]=="Qmulti" )
	    {
	      TF[i]->GetYaxis()->SetRangeUser(-0.005,0.04);
	      line= new TLine(xmin_,0.02,xmax_,0.02);
	    }
	  else
	    {
	      TF[i]->GetYaxis()->SetRangeUser(0,.02);
	      line= new TLine(xmin_,0.01,xmax_,0.01);
	    }
	}
	  
      //TF[i]->GetYaxis()->SetLabelSize(0.17);
       
      //      fout->cd();
  
      TF[i]->GetXaxis()->SetTitle(name1);
      TF[i]->GetXaxis()->SetLabelSize(0.14);
      TF[i]->GetXaxis()->SetTitleOffset(0.9);
      TF[i]->GetXaxis()->SetTitleSize(0.17);

      
      if(SRvsCR) TF[i]->GetYaxis()->SetTitle("SR/CR");
      else if(ExpvsPred) TF[i]->GetYaxis()->SetTitle("Exp/Pred");
      TF[i]->GetYaxis()->SetLabelSize(0.11);
      TF[i]->SetLineWidth(3);
      TF[i]->GetYaxis()->SetTitleOffset(0.38);
      TF[i]->GetYaxis()->SetTitleSize(0.12);
 
      line->SetLineColor(1);
      line->SetLineStyle(1);
      line->SetLineWidth(1);
      line->Draw();

      /* cout<<"The TF content in bin"<<endl; */
      /* /\* cout<<"The SR content in bin"<<endl; *\/ */
      /* for(int j=bin0;j<=bin1;j++) */
      /* 	{ cout<<TF[i]->GetBinContent(j)<<endl;} */
      /* /\* cout<<"==============="<<endl; *\/ */

      /* if(varName[i]=="METvBin2") */
      /* 	for(int j=bin0;j<=METLowEdge_v2.size()-1;j++) */
      /* 	  { cout<<TF[i]->GetBinContent(j)<<endl;} */

      if(SRvsCR) TF[i]->Write();
      
      c1[i]->SaveAs(pdf);
      c1[i]->SaveAs(png);

      
    }
  /* TString command="cp "+rootout+" "+path+"/."; */
  /* //  sprintf(command,"cp %s %s/.",rootout,path); */
  /* system(command); */
  /* cout<<command<<endl; */
}

void decorate(TH1D* hist,int i,const char* fname){
  hist->SetLineColor(col[i]);
  hist->SetFillColor(col[i]);
  hist->SetLineColor(kBlack);
  hist->SetLineWidth(1);
  hist->SetTitle(0);
  /* hist->GetXaxis()->SetLabelSize(.06); */
  /* hist->GetYaxis()->SetLabelSize(.10); */
  hist->GetXaxis()->SetTitleSize(0.06);
  gStyle->SetOptStat(0);
}
