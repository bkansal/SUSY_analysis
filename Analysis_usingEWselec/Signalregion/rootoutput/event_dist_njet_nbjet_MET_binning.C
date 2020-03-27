#include<iostream>
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

string getfname(const char *fname1){string fname=fname1;fname.pop_back();fname.pop_back();fname.pop_back();fname.pop_back();fname.pop_back();return fname;}
void SetSBinHist(TH1D*,TH1D*);
int METbins, njet_bjet_bins=6;
bool total_bins_25=false;
bool total_bins_30=false;
bool total_bins_30_MET100=true;
bool v_17=false;
bool v_12=true;
void tmp()
{
  const int nfiles=8,nBGs=6,nHists=8,nSig=nfiles-nBGs;    //Specify no. of files
  // int col[11]={kOrange,kGray,kRed,kTeal+9,kCyan,kYellow,kBlue,kMagenta+2,kPink+1,kMagenta,kBlack}; 
  TLine *line1V7,*line2V7,*line3V7,*line4V7,*line5V7;
  TFile *f[nfiles];
  TH1D *h_hist[nfiles], *h_histOrg[100];
  TCanvas *c[8];
  TArrow *arrow1,*arrow2,*arrow3,*arrow4,*arrow5,*arrow6;
  TLatex textOnTop,intLumiE;
  TLatex Tl;
  THStack *hs_BG[7];
  double binS;
  int nbins;
  TLegend *legend1=new TLegend(0.6253672,0.5899145,0.85247,0.7296337);
  TLegend *legend2=new TLegend(0.15,0.7550427,0.7990921,0.8869109);
  char name2[100];
// f[2] = new TFile("ZGZJ_NuNuG_v17.root");
  if(v_17){
  f[0] = new TFile("TTGJets_v17.root");
  f[1] = new TFile("TTJetsHT_v17.root");
  f[2] = new TFile("ZGJetsToNuNuG_v12.root");
  // f[2] = new TFile("ZGZJ_NuNuG.root");
  f[3] = new TFile("WGJetsToLNuG_v17.root");
  f[4] = new TFile("WJetsToLNu_v17.root");
  f[5] = new TFile("GJetsQCD_new_v17.root");
  f[6] = new TFile("T5bbbbZg_1800_150_FastSim_v17.root");
  f[7] = new TFile("T5bbbbZg_1800_1750_FastSim_v17.root");
  }
  if(v_12){
    f[0] = new TFile("TTGJets_v12_vinay.root");
  f[1] = new TFile("TTJetsHT_v12_vinay.root");
  f[2] = new TFile("ZGZJ_NuNuG_v12_vinay.root");
  f[3] = new TFile("WGJetsToLNuG_v12_vinay.root");
  f[4] = new TFile("WJetsToLNu_v12_vinay.root");
  f[5] = new TFile("GJetsQCD_new_v12_vinay.root");
  f[6] = new TFile("T5bbbbZg_1800_150_FastSim_v12_vinay.root");
  f[7] = new TFile("T5bbbbZg_1800_1750_FastSim_v12_vinay.root");
  }
    
  vector<TString> histName ;
  if (total_bins_25 || total_bins_30_MET100)
    histName={"METvBin1_nj2to4_nbjet0","METvBin2_nj5to6_nbjet0","METvBin2_nj7toinf_nbjet0","METvBin2_nj2to4_nbjetnot0","METvBin2_nj5to6_nbjetnot0","METvBin2_nj7toinf_nbjetnot0"};
  else if (total_bins_30)
    histName={"METvBin1_nj2to4_nbjet0","METvBin1_nj5to6_nbjet0","METvBin1_nj7toinf_nbjet0","METvBin1_nj2to4_nbjetnot0","METvBin1_nj5to6_nbjetnot0","METvBin1_nj7toinf_nbjetnot0"};
    
  TH1D *h_totBG[nfiles];  

  // for(int i=0;i < njet_bjet_bins;i++){
  vector<vector<double>> v_METbins;

  hs_BG[0]= new THStack("event_dist","Event Distribution");
  hs_BG[0]->SetMaximum(1000000);
  hs_BG[0]->SetMinimum(0.5);
  vector<int> col={kGray,kTeal+9,kOrange,kRed,kCyan-1,kCyan,kBlue,kMagenta+2,kPink+1,kMagenta,kBlack};
  c[0]= new TCanvas("event_dist","event_dist",1500,800);
  c[0]->cd();
  c[0]->SetLogy();
  //   cout<<"histName["<<i<<"] ===> "<<histName[i]<<endl;

  for(int j=0; j<nfiles; j++){
    cout<<"f["<<j<<"] ===> "<<getfname(f[j]->GetName())<<endl;
    std::vector<double> v_binS;
    nbins=0;
    for(int i=0;i < njet_bjet_bins;i++){
     //  if(total_bins_25){
     //  	if (i==0) METbins=5;
     //  	else METbins =4;
     //  }
     //  else if(total_bins_30)
     // METbins=5;
 
      cout<<"histName["<<i<<"] ===> "<<histName[i]<<endl;
      h_histOrg[j] = (TH1D*)f[j]->Get(histName[i]);
      METbins=h_histOrg[j]->GetNbinsX();
     
      if(j<nBGs)
	{
	  for(int k=1; k<=METbins; k++)
	    {
	      binS=h_histOrg[j]->GetBinContent(k);
	      v_binS.push_back(binS);
	      cout<<"Bin content for bin "<<k<<" --> "<<binS<<endl;
	      nbins++;
	    }
	}  
      if(j>=nBGs){
	// std::vector<double> v_binS;
	for(int k=1; k<=METbins; k++)
	  {
	    binS=h_histOrg[j]->GetBinContent(k);
	    v_binS.push_back(binS);
	    cout<<"Bin content for bin "<<k<<" --> "<<binS<<endl;
	    nbins++;
	  }
      }
   
       }
    v_METbins.push_back(v_binS);
    cout<<"====================>Filled vectors, now making plot"<<endl;
    cout<<"====================> column colour  ==> "<<col[j]<<endl;
    //   v_nbins.push_back(nbins);
  }
  
  for(int j=0; j<nfiles; j++){
    cout<<"f["<<j<<"] ===> "<<getfname(f[j]->GetName())<<endl;
    h_totBG[j] = new TH1D("totBG","totBG",nbins,0,nbins);
    //   cout<<"=> no. of bins  ==> "<<col[j]<<endl;
    if(j<nBGs){
      for(int k=0; k<nbins; k++)
	{
	  h_totBG[j]->SetBinContent(k+1,v_METbins[j][k]);
	  cout<<"Bin content for bin "<<k+1<<" --> "<<v_METbins[j][k]<<endl;
	}
	// h_totBG[j]->SetFillColor(col[j]);
      h_totBG[j]->SetFillColor(col[j]);
      h_totBG[j]->SetLineWidth(1);
      h_totBG[j]->SetLineColor(kBlack);
      hs_BG[0]->Add(h_totBG[j]);
    }
    if(j==nBGs){
      cout<<"====================> Draw bkg stack plot"<<endl;

      hs_BG[0]->Draw("hist");
    }
    if(j>=nBGs){
      for(int k=0; k<nbins; k++)
	{
	  h_totBG[j]->SetBinContent(k+1,v_METbins[j][k]);
	  cout<<"Bin content for bin "<<k+1<<" --> "<<v_METbins[j][k]<<endl;
	}
      h_totBG[j]->SetLineColor(col[j]);
      h_totBG[j]->SetLineWidth(2);
      h_totBG[j]->Draw("same hist");
    }

  TString lName=getfname(f[j]->GetName());
  if(lName.Contains("ZGZJ")){lName="Z(#nu#bar{#nu}) + #gamma";}
  else if(lName.Contains("ZJets")){lName="Z(#nu#bar{#nu}) + jets";}
  else if(lName.Contains("DYJetsToLL")){lName="DY(l^{+}l^{-})";}
  else if(lName.Contains("WJetsToLNu")){lName="W(l#nu) + jets";}
  else if(lName.Contains("RareProcess")){}
  else if(lName.Contains("TTJetsHT")){lName="t #bar{t}";}
  else if(lName.Contains("WGJetsToLNuG")){lName="W(l#nu) + #gamma";}
  else if(lName.Contains("ZGJetsToNuNuG")){lName="Z(#nu#bar{#nu}) + #gamma";}
  else if(lName.Contains("TTGJets")){lName="t #bar{t} + #gamma";}
  //  else if(lName.Contains("QCD")){lName="QCD";}
  else if(lName.Contains("GJets")){lName="#gamma + jets";}
  else if(lName.Contains("Run2016")){lName="Data";}
  
  if(lName.Contains("T5bbbbZg_1800_150_FastSim")){lName = "#tilde{g} #rightarrow b #bar{b} #tilde{#chi}_{1}^{0}, #tilde{#chi}_{1}^{0} #rightarrow #gamma/Z #tilde{G} (m_{#tilde{g}} = 1800 GeV, m_{#tilde{#chi}_{1}^{0}} = 150 GeV)";}
  else if(lName.Contains("T5bbbbZg_1800_1750_FastSim")){lName = "#tilde{g} #rightarrow b #bar{b} #tilde{#chi}_{1}^{0}, #tilde{#chi}_{1}^{0} #rightarrow #gamma/Z #tilde{G} (m_{#tilde{g}} = 1800 GeV, m_{#tilde{#chi}_{1}^{0}} = 1750 GeV)";}
  else if(lName.Contains("T5bbbbZg_1800_1000")){lName = "#tilde{g} #rightarrow b #bar{b} #tilde{#chi}_{1}^{0}, #tilde{#chi}_{1}^{0} #rightarrow #gamma/Z #tilde{G} (m_{#tilde{g}} = 1800 GeV, m_{#tilde{#chi}_{1}^{0}} = 1000 GeV)";}


  if(j<nBGs)legend1->AddEntry( h_totBG[j],lName,"f");
  else
    legend2->AddEntry( h_totBG[j],lName,"l");

  legend1->SetFillStyle(0); legend2->SetFillStyle(0);  
  legend1->SetNColumns(2);
  legend1->SetBorderSize(0);
  legend2->SetBorderSize(0);
  legend2->SetMargin(0.12);
  legend2->SetTextSize(0.04);
  legend1->Draw();
  legend2->Draw();

  // legend2->AddEntry( h_totBG[j],lName,"l");

  }
  // float intLumi=35.9;
  textOnTop.SetTextSize(0.04);
  intLumiE.SetTextSize(0.04);
  // if(isPaper) textOnTop.DrawLatexNDC(0.12,0.91,"CMS #it{#bf{Simulation Supplementary}}");
  textOnTop.DrawLatexNDC(0.12,0.91,"CMS #it{#bf{Simulation Preliminary}}");
  // sprintf(name2,"#bf{%0.1f fb^{-1} (13 TeV)}",intLumi);
  intLumiE.DrawLatexNDC(0.7,0.91,"#bf{35.9 fb^{-1} (13 TeV)}");

  if(total_bins_25){
  line1V7=new TLine( 5.0,0.0,  5.0,330);
  line1V7->SetLineWidth(2);
  line2V7=new TLine( 9.0,0.0,  9.0,330);
  line2V7->SetLineWidth(2);
  line3V7=new TLine(13.0,0.0, 13.0,330);
  line3V7->SetLineWidth(2);
  line4V7=new TLine(17.0,0.0, 17.0,330);
  line4V7->SetLineWidth(2);
  line5V7=new TLine(21.0,0.0, 21.0,330);
  line5V7->SetLineWidth(2);
  arrow1 = new TArrow( 0.0,1000, 5.0,1000,0.01,"<|>");
  arrow2 = new TArrow( 5.0,1000,9.0,1000,0.01,"<|>");
  arrow3 = new TArrow(9.0,1000,13.0,1000,0.01,"<|>");
  arrow4 = new TArrow(13.0,300, 17.0,300,0.01,"<|>");
  arrow5 = new TArrow(17.0,300, 21.0,300,0.01,"<|>");
  arrow6 = new TArrow(21.0,300, 25.0,300,0.01,"<|>");
  Tl.SetTextSize(0.04);
  Tl.DrawLatex(2.5,1500,"N^{ 0}_{ 2-4}");
  Tl.DrawLatex(7.0,1500,"N^{ 0}_{ 5-6}");
  Tl.DrawLatex(11.0,1500,"N^{ 0}_{ #geq7}");
  Tl.DrawLatex(15.0,400,"N^{ #geq1}_{ 2-4}");
  Tl.DrawLatex(19.0,400,"N^{ #geq1}_{ 5-6}");
  Tl.DrawLatex(23.0,400,"N^{ #geq1}_{ #geq7}");
 }
  else if(total_bins_30){
   line1V7=new TLine( 5.0,0.0,  5.0,330);
   line1V7->SetLineWidth(2);
   line2V7=new TLine( 10.0,0.0,  10.0,330);
   line2V7->SetLineWidth(2);
   line3V7=new TLine(15.0,0.0, 15.0,330);
   line3V7->SetLineWidth(2);
   line4V7=new TLine(20.0,0.0, 20.0,330);
   line4V7->SetLineWidth(2);
   line5V7=new TLine(25.0,0.0, 25.0,330);
  line5V7->SetLineWidth(2);
   arrow1 = new TArrow( 0.0,1000, 5.0,1000,0.01,"<|>");
   arrow2 = new TArrow( 5.0,1000,10.0,1000,0.01,"<|>");
   arrow3 = new TArrow(10.0,1000,15.0,1000,0.01,"<|>");
   arrow4 = new TArrow(15.0,300, 20.0,300,0.01,"<|>");
   arrow5 = new TArrow(20.0,300, 25.0,300,0.01,"<|>");
   arrow6 = new TArrow(25.0,300, 30.0,300,0.01,"<|>");
   Tl.SetTextSize(0.04);
   Tl.DrawLatex(2.5,1500,"N^{ 0}_{ 2-4}");
   Tl.DrawLatex(7.5,1500,"N^{ 0}_{ 5-6}");
   Tl.DrawLatex(12.5,1500,"N^{ 0}_{ #geq7}");
   Tl.DrawLatex(17.5,400,"N^{ #geq1}_{ 2-4}");
   Tl.DrawLatex(22.5,400,"N^{ #geq1}_{ 5-6}");
   Tl.DrawLatex(27.5,400,"N^{ #geq1}_{ #geq7}");
 }

  else if(total_bins_30_MET100){
  line1V7=new TLine(6.0,0.0,  6.0,330);
  line1V7->SetLineWidth(2);
  line2V7=new TLine(11.0,0.0, 11.0,330);
  line2V7->SetLineWidth(2);
  line3V7=new TLine(16.0,0.0, 16.0,330);
  line3V7->SetLineWidth(2);
  line4V7=new TLine(21.0,0.0, 21.0,330);
  line4V7->SetLineWidth(2);
  line5V7=new TLine(26.0,0.0, 26.0,330);
  line5V7->SetLineWidth(2);
  arrow1 = new TArrow( 0.0,1000, 6.0,1000,0.01,"<|>");
  arrow2 = new TArrow( 6.0,1000,11.0,1000,0.01,"<|>");
  arrow3 = new TArrow(11.0,1000,16.0,1000,0.01,"<|>");
  arrow4 = new TArrow(16.0,300, 21.0,300,0.01,"<|>");
  arrow5 = new TArrow(21.0,300, 26.0,300,0.01,"<|>");
  arrow6 = new TArrow(26.0,300, 31.0,300,0.01,"<|>");
  Tl.SetTextSize(0.04);
  Tl.DrawLatex(3.0,1500,"N^{ 0}_{ 2-4}");
  Tl.DrawLatex(8.5,1500,"N^{ 0}_{ 5-6}");
  Tl.DrawLatex(13.5,1500,"N^{ 0}_{ #geq7}");
  Tl.DrawLatex(18.5,400,"N^{ #geq1}_{ 2-4}");
  Tl.DrawLatex(23.5,400,"N^{ #geq1}_{ 5-6}");
  Tl.DrawLatex(28.5,400,"N^{ #geq1}_{ #geq7}");
 }

  line1V7->Draw();	line2V7->Draw();	line3V7->Draw();	line4V7->Draw();	line5V7->Draw();

    arrow1->Draw(); arrow2->Draw(); arrow3->Draw();
    arrow4->Draw(); arrow5->Draw(); arrow6->Draw();



}



