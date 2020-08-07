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

char name[100];
char name2[100];
TString name3;
TLatex textOnTop,intLumiE;
const int nfiles=5,nBG=4;    //Specify no. of files
TFile *f[nfiles];
bool savePlots=1;
bool isPaper=0;

vector<int> col={kPink+1,kTeal+9,kYellow,kGray,kOrange,kCyan,kBlue,kRed,kBlue+2,kMagenta,kCyan};  //Specify Colors b's

TCanvas *c_cA=new TCanvas("kinVar","plot of a kin var",1500,900);
string getfname(const char *fname1){string fname=fname1;fname.pop_back();fname.pop_back();fname.pop_back();fname.pop_back();fname.pop_back();return fname;}
void decorate(TH1D*,int,const char*);
void decorate(THStack*,int,const char*);
void drawlegend(TH1D*,int,const char*);
void printInt(TH1D*,int,const char*);
TLegend *legend1=new TLegend(0.5253672,0.5299145,0.85247,0.6996337);
TLegend *legend2=new TLegend(0.2,0.7350427,0.8190921,0.8669109);

void setLastBinAsOverFlow(TH1D*);
TH1D* setMyRange(TH1D*,double,double);

void plotKinStack(){
  double sr_Integral=0,cr_Integral=0;
  TH1::SetDefaultSumw2(1);
  gStyle->SetOptStat(0);
  gStyle->SetTitle(0);
  // gPad->SetLogy(1); 
  double yMin=0.1,yMax = 1000;
  double xMin=0.0,xMax = 2000;
  //TString year = "2016";
  // TString year = "2017";
  //  TString year = "2018";
  TString year = "all";
  //  TString varName = "ST"; TString xLabel = "H_{T}^{#gamma} (GeV)";   int rebin=25; yMin=0.5,yMax = 1100; xMin=300.0,xMax = 3000;
  // TString varName = "METvBin2_nj2to4_nbjetnot0"; TString xLabel = "p_{T}^{miss} (GeV)";   int rebin=1; yMin=0.005,yMax = 15000; xMin=200.0,xMax = 1000;
  TString varName = "MET"; TString xLabel = "p_{T}^{miss} (GeV)";   int rebin=5; yMin=0.1,yMax = 10000; xMin=200.0,xMax = 1200;
  //   TString varName = "MET_EW_htag"; TString xLabel = "p_{T}^{miss} (GeV)";   int rebin=5; yMin=0.1,yMax = 10000; xMin=200.0,xMax = 1200;
  // TString varName = "MET_SP"; TString xLabel = "p_{T}^{miss} (GeV)";   int rebin=5; yMin=0.1,yMax = 10000; xMin=200.0,xMax = 1200;

  //   TString varName = "METvBin2"; TString xLabel = "p_{T}^{miss} (GeV)";   int rebin=1; yMin=0.1,yMax = 100000; xMin=200.0,xMax = 1400;
  //   TString varName = "hadAk8Mass_EW"; TString xLabel = "Mass_{Leading Ak8Jet} (GeV)";   int rebin=25; yMin=0.01,yMax = 100000; xMin=0,xMax = 300;
  //  TString varName = "hadAk8Mass_Ak8jet2to5"; TString xLabel = "Mass_{Ak8Jet} (GeV)";   int rebin=25; yMin=0.01,yMax = 100000; xMin=0,xMax = 300;
  // TString varName = "hadAk8Mass_Ak8jetge6"; TString xLabel = "Mass_{Ak8Jet} (GeV)";   int rebin=25; yMin=0.01,yMax = 100000; xMin=0,xMax = 300;
  // TString varName = "hadAk8Mass_Ak8jet0_EW_SP"; TString xLabel = "Mass_{Ak8Jet} (GeV)";   int rebin=25; yMin=0.001,yMax = 100000; xMin=0,xMax = 300;
  //     TString varName = "hadAk8Mass_Ak8jet0_EW_noSB"; TString xLabel = "Mass_{Ak8Jet} (GeV)";   int rebin=25; yMin=0.001,yMax = 100000; xMin=0,xMax = 300;

  //   TString varName = "hadAk8Mass"; TString xLabel = "Mass_{Ak8Jet} (GeV)";   int rebin=25; yMin=0.01,yMax = 100000; xMin=0,xMax = 300;
  // TString varName = "hadAk8Mass_EW"; TString xLabel = "Mass_{Ak8Jet} (GeV)";   int rebin=25; yMin=0.01,yMax = 100000; xMin=0,xMax = 300;
  // TString varName = "hadAk8Mass_SP"; TString xLabel = "Mass_{Ak8Jet} (GeV)";   int rebin=25; yMin=0.01,yMax = 1000; xMin=0,xMax = 200;
   // TString varName = "BestPhotonPt"; TString xLabel = "p_{T}^{#gamma} (GeV)";   int rebin=10; yMin=0.5,yMax = 100000; xMin=0.0,xMax = 1200;
  //  TString varName = "BestPhotonPt"; TString xLabel = "p_{T}^{#gamma} (GeV)";   int rebin=5; yMin=0.1,yMax = 10000; xMin=0.0,xMax = 1200;
  // TString varName = "PhovBin2"; TString xLabel = "p_{T}^{#gamma} (GeV)";   int rebin=1; yMin=0.4,yMax = 1000000; xMin=0.0,xMax = 1200;
  // TString varName = "nHadJets"; TString xLabel = "N_{ jets}";   int rebin=1; yMin=0.1,yMax = 1000; xMin=0.0,xMax = 14;
  //  TString varName = "nJets"; TString xLabel = "N_{ jets}";   int rebin=1; yMin=0.1,yMax = 100000; xMin=1,xMax = 12;
  //  TString varName = "nHadAk8Jets_nAk8jet_ge1"; TString xLabel = "N_{ jets}";   int rebin=1; yMin=0.1,yMax = 100000; xMin=0,xMax = 14;
  // TString varName = "nHadJets_nAk8jet_jet2to5"; TString xLabel = "N_{ jets}";   int rebin=1; yMin=0.1,yMax = 100000; xMin=1,xMax = 14;
  //  TString varName = "nHadJets_nAk8jet_jetge6"; TString xLabel = "N_{ jets}";   int rebin=1; yMin=0.1,yMax = 100000; xMin=1,xMax = 14;
  //  TString varName = "nHadJets_nAk8jet0_SP"; TString xLabel = "N_{ jets}";   int rebin=1; yMin=0.1,yMax = 100000; xMin=1,xMax = 14;
  // TString varName = ""; TString xLabel = "N_{ jets}";   int rebin=1; yMin=0.1,yMax = 100000; xMin=1,xMax = 14;
  //     TString varName = "nBTags"; TString xLabel = "N_{ b-jets}";   int rebin=1; yMin=0.1,yMax = 100000; xMin=1.0,xMax = 5;
   // TString varName = "mindPhi1dPhi2"; TString xLabel = "min(#Delta#phi_{1}, #Delta#phi_{2})";   int rebin=10; yMin=0.3,yMax = 1500; xMin=-100000.0,xMax = 100000;
  //"mindPhi1dPhi2";//"AllSBins_v7_CD";
  //  TString varName = "AllSBins_v7_CD_SP"; TString xLabel = "Bin no.";   int rebin=1; yMin=0.5,yMax = 1000000; xMin=-100000,xMax = 100000;
  //  TString varName = "AllSBins_v6_CD_EW_14bin"; TString xLabel = "Bin no.";   int rebin=1; yMin=0.5,yMax = 1000000; xMin=-100000,xMax = 100000;
  //    TString varName = "AllSBins_v7_CD_EW_7bin_noSB"; TString xLabel = "Bin no.";   int rebin=1; yMin=0.5,yMax = 1000000; xMin=-100000,xMax = 100000;
  //  TString varName = "AllSBins_v6_CD_EW_43bin"; TString xLabel = "Bin no.";   int rebin=1; yMin=0.5,yMax = 1000000; xMin=-100000,xMax = 100000;
   //  TString varName = "AllSBins_v6_CD_EW_50bin_elec1"; TString xLabel = "Bin no.";   int rebin=1; yMin=0.5,yMax = 10000; xMin=-10000000000000,xMax = 10000000000000;
  //    TString varName = "AllSBins_v6_CD_EW_50bin"; TString xLabel = "Bin no.";   int rebin=1; yMin=0.01,yMax = 100000000; xMin=-100000,xMax = 100000;
  //  TString varName = "AllSBins_v7_CD_EW_14bin"; TString xLabel = "Bin no.";   int rebin=1; yMin=0.01,yMax = 100000000; xMin=-100000,xMax = 100000;
  //TString varName = "METvarBin";
  //  TString xLabel = "p_{T}^{miss} (GeV)";//min(#Delta#Phi_{1},#Delta#Phi_{2})
  //TString varName = "dPhi_METjet1"; TString xLabel = "dPhi b/w Met & Jet1";   int rebin=1;  yMin=0.3,yMax = 15000; xMin=-100000,xMax = 100000;
  //  // "mindPhi1dPhi2";//"AllSBins_v7_CD";
  //   TString varName = "dPhi_METjet2"; TString xLabel = "dPhi b/w Met & Jet2";   int rebin=1; yMin=0.3,yMax = 15000; xMin=-100000,xMax = 100000;
  //   TString varName = "dPhi_phojet1"; TString xLabel = "dPhi b/w pho & Jet1";   int rebin=1; yMin=0.3,yMax = 15000; xMin=-100000,xMax = 100000;
   // TString varName = "dPhi_phojet2"; TString xLabel = "dPhi b/w pho & Jet2";   int rebin=1; yMin=0.3,yMax = 15000; xMin=-100000,xMax = 100000;
   // TString varName = "dPhi_phoMET"; TString xLabel = "dPhi b/w pho & MET";   int rebin=1; yMin=0.3,yMax = 15000; xMin=-100000,xMax = 100000;
   // TString varName = "mTPhoMET"; TString xLabel = "mT b/w pho & MET";   int rebin=10; yMin=0.3,yMax = 15000; xMin=-100000,xMax = 100000;

  if(year == "all")
    {

      f[0] = new TFile("./rootoutput/newselec_LE_v3/TTGJets_CR.root");
      f[1] = new TFile("./rootoutput/newselec_LE_v3/TTJets_CR.root");
      f[2] = new TFile("./rootoutput/newselec_LE_v3/WJets_CR.root");
      f[3] = new TFile("./rootoutput/newselec_LE_v3/WGJets_CR.root");                                                                                          

      col.resize(0);
      col={kGray,kTeal+9,kRed,kCyan-1,kBlack};//,kMagenta+2,kBlack,kPink+1,kMagenta};
      f[4] = new TFile("./rootoutput/newselec_LE_v3/Run2_METdata_CR.root");
    }

    if(year == "2016")
    {

      f[0] = new TFile("./rootoutput/newselec_LE_v3/TTGJets_2016_CR.root");
      f[1] = new TFile("./rootoutput/newselec_LE_v3/TTJets_2016_CR.root");
      f[2] = new TFile("./rootoutput/newselec_LE_v3/WJets_2016_CR.root");
      f[3] = new TFile("./rootoutput/newselec_LE_v3/WGJets_2016_CR.root");
      col.resize(0);
      col={kGray,kTeal+9,kRed,kCyan-1,kBlack};//,kMagenta+2,kBlack,kPink+1,kMagenta};
      f[4] = new TFile("./rootoutput/newselec_LE_v3/Run2016_METdata_CR.root");
    }
    if(year == "2017")
    {

      f[0] = new TFile("./rootoutput/newselec_LE_v3/TTGJets_2017_CR.root");
      f[1] = new TFile("./rootoutput/newselec_LE_v3/TTJets_2017_CR.root");
      f[2] = new TFile("./rootoutput/newselec_LE_v3/WJets_2017_CR.root");
      f[3] = new TFile("./rootoutput/newselec_LE_v3/WGJets_2017_CR.root");
      col.resize(0);
      col={kGray,kTeal+9,kRed,kCyan-1,kBlack};//,kMagenta+2,kBlack,kPink+1,kMagenta};
      f[4] = new TFile("./rootoutput/newselec_LE_v3/Run2017_METdata_CR.root");
    }
    if(year == "2018")
    {

      f[0] = new TFile("./rootoutput/newselec_LE_v3/TTGJets_2018_CR.root");
      f[1] = new TFile("./rootoutput/newselec_LE_v3/TTJets_2018_CR.root");
      f[2] = new TFile("./rootoutput/newselec_LE_v3/WJets_2018_CR.root");
      f[3] = new TFile("./rootoutput/newselec_LE_v3/WGJets_2018_CR.root");
      col.resize(0);
      col={kGray,kTeal+9,kRed,kCyan-1,kBlack};//,kMagenta+2,kBlack,kPink+1,kMagenta};
      f[4] = new TFile("./rootoutput/newselec_LE_v3/Run2018_METdata_CR.root");
    }

    
  gStyle->SetTextSize(2);
  THStack *hs_var=new THStack("var_Stack","MET Stacked");
  //TH1D *h_R;
  TH1D *h_MET_R[nfiles];
  for(int i=0;i<nfiles;i++){
    sprintf(name,"hist_file%i",i);
    h_MET_R[i]=new TH1D(name,name,21,0.5,21.5);
  }

  vector<double> Bcnt;
  double intLumi=0.0;
  TLatex tl1;
  for(int i=0;i<nfiles;i++){
    TH1D *h_intLumi=(TH1D*)f[i]->FindObjectAny("intLumi");
    if(i==0) {
      intLumi=h_intLumi->GetMean();
      sprintf(name2, "%.2f fb^{-1}",137.19);
    }
    else{
      if(abs(intLumi-h_intLumi->GetMean())>0.0001)
	cout<<"Integarted lumi for "<<f[i]->GetName()<<" is "<<h_intLumi->GetMean()<<" and for other files it is different"<<endl;
    }
    
    TH1D *h_MET;
    if(i<=nBG-1) h_MET=(TH1D*)f[i]->FindObjectAny(varName);
    if(i>=nBG) h_MET=(TH1D*)f[i]->FindObjectAny(varName);
    h_MET->Rebin(rebin);
    
    /* if ((varName=="AllSBins_v7_CD" || varName=="AllSBins_v6_CD_SP" || varName=="AllSBins_v7_CD_EW" || varName=="hadAk8Mass" || varName=="hadAk8Mass_EW" || varName=="hadAk8Mass_SP"|| varName=="METvBin_EW_v2" || varName=="METvBin_SP_v2" || varName == "AllSBins_v6_CD_EW_43bin" || varName == "AllSBins_v6_CD_EW_50bin" || varName == "AllSBins_v6_CD_EW_50bin_elec1" || varName=="hadAk8Mass_Ak8jetge6" || varName=="hadAk8Mass_Ak8jet2to5" || varName=="hadAk8Mass_Ak8jet0_EW_SP" || varName=="hadAk8Mass_Ak8jet2to5_noEW" || varName=="hadAk8Mass_Ak8jetge6_EW" || varName=="hadAk8Mass_Ak8jetge6_noEW" || varName=="MET"  || varName=="MET_SP")){ */
    /*   cout<<"filename ------->  "<<getfname(f[i]->GetName())<<endl; */
    /*   for(int k=0; k<h_MET->GetSize()-2; k++) */
    /* 	{ */
    /*   	  cout<<"Bin content for bin "<<k<<" having lowedge : "<<h_MET->GetBinLowEdge(k)<<" ---->  "<<h_MET->GetBinContent(k)<<endl; */
    /* 	  //  cout<<"Bin content for bin "<<k<<" having lowedge : "<<h_MET->GetBinCenter(k)<<" ---->  "<<h_MET->GetBinContent(k)<<endl; */
    /* 	} */
    /*   cout<<"==========================================="<<endl; */
    /* } */

    decorate(h_MET,i,f[i]->GetName());
    h_MET = setMyRange(h_MET,xMin,xMax);
    //    h_MET->GetXaxis()->SetRangeUser(xMin,xMax);
    
    if(i<=(nBG-1))  hs_var->Add(h_MET);

    if(i==nBG-1) {
      c_cA->cd();
      //      hs_var->Draw("BAR HIST");
      hs_var->Draw("hist");
      hs_var->SetMinimum(yMin);
      hs_var->SetMaximum(yMax);
      decorate(hs_var,i,f[i]->GetName()); 
      if(xMin > -10000 && xMax < 10000) hs_var->GetXaxis()->SetRangeUser(xMin-0.1,0.1+xMax);
    }
    /* if(i>=nBG && i<8){  */
    /*   c_cA->cd();  */
    /*   h_MET->SetMarkerStyle(20); */
    /*   h_MET->SetMarkerColor(col[i]); */
    /*   h_MET->SetLineColor(col[i]); */
    /*   h_MET->SetLineWidth(3); */
    /*   h_MET->Draw(" hist same"); */
    /* } */
    if(i >= nBG)
      {
	c_cA->cd();
	h_MET->SetMarkerStyle(20);
	h_MET->SetMarkerColor(col[i]);
	h_MET->SetLineColor(col[i]);
	h_MET->SetLineWidth(3);
	h_MET->SetLineStyle(1);
	h_MET->Draw("e1 same");
      }
      // if(i==8)
      //	{
	 
      //  h_MET->SetLineStyle(1);
      //  h_MET->SetLineColor(1);
      //  h_MET->SetMarkerColor(col[i]);
      //  h_MET->Draw("e1 same");}
            //      h_MET->GetYaxis()->SetRangeUser(0.5,20000);
      //      h_MET->GetYaxis()->SetRangeUser(100.5,20000);
    
    drawlegend(h_MET,i,f[i]->GetName());
    if(i==nfiles-1){ 
      hs_var->GetXaxis()->SetTitleOffset(1.0);
      hs_var->GetXaxis()->SetTitle(xLabel); hs_var->GetYaxis()->SetTitle("Events");hs_var->SetTitle(0);
      hs_var->GetYaxis()->SetTitleOffset(.90);
      TString temp=h_MET->GetName(),temp2;
      if(temp.Contains("Jets") || temp.Contains("nBTags")){
	gPad->SetTickx(0);
	hs_var->GetXaxis()->SetLabelSize(0.08);
	for(int i=1;i<=h_MET->GetNbinsX();i++){
	  temp2 = to_string(i-1);
	  if(i%2==0 && temp.Contains("nHadJets")) continue;
	    hs_var->GetXaxis()->SetBinLabel(i,temp2);
	}
	//      cout<<hist->GetName()<<endl;
      }
    }
    
  }

  legend1->SetFillStyle(0); legend2->SetFillStyle(0);  
  legend1->SetNColumns(2);
  legend1->SetBorderSize(0);
  legend2->SetBorderSize(0);
  legend2->SetMargin(0.12);
  c_cA->cd(); gPad->SetLogy();legend1->Draw();
  c_cA->cd(); gPad->SetLogy();legend2->Draw();
  //  gPad->RedrawAxis();
  //  hs_var->GetXaxis()->SetTitle(xLabel);
 
  textOnTop.SetTextSize(0.04);
  intLumiE.SetTextSize(0.04);
  /* if(isPaper) textOnTop.DrawLatexNDC(0.12,0.91,"CMS #it{#bf{Simulation Supplementary}}"); */
  /* else textOnTop.DrawLatexNDC(0.12,0.91,"CMS #it{#bf{Simulation Preliminary}}"); */
  sprintf(name2,"#bf{%0.1f fb^{-1} (13 TeV)}",137.19);
  intLumiE.DrawLatexNDC(0.7,0.91,name2);
  TLatex Tl;
  Tl.SetTextSize(0.04);

  c_cA->cd(); c_cA->SetGridx(0); c_cA->SetGridy(0);
  
  if(varName=="AllSBins_v7_CD" || varName=="AllSBins_v7_CD_SP" || varName=="AllSBins_v7_CD_EW"  ){
    TLine *line1V7=new TLine( 6.5,0.5,  6.5,3000);
    TLine *line2V7=new TLine(11.5,0.5, 11.5,3000);
    TLine *line3V7=new TLine(16.5,0.5, 16.5,1000);
    TLine *line4V7=new TLine(21.5,0.5, 21.5,300);
    TLine *line5V7=new TLine(26.5,0.5, 26.5,300);
    

    c_cA->cd(); c_cA->SetGridx(0); c_cA->SetGridy(0);
    line1V7->Draw();      line2V7->Draw();  line3V7->Draw();
    line4V7->Draw();      line5V7->Draw();

    TArrow *arrow1 = new TArrow( 0.5,1000, 6.5,1000,0.01,"<|>");
    TArrow *arrow2 = new TArrow( 6.5,1000,11.5,1000,0.01,"<|>");
    TArrow *arrow3 = new TArrow(11.5,650,16.5,650,0.01,"<|>");
    TArrow *arrow4 = new TArrow(16.5,300, 21.5,300,0.01,"<|>");
    TArrow *arrow5 = new TArrow(21.5,300, 26.5,300,0.01,"<|>");
    TArrow *arrow6 = new TArrow(26.5,300, 31.5,300,0.01,"<|>");

    arrow1->Draw(); arrow2->Draw(); arrow3->Draw();
    arrow4->Draw(); arrow5->Draw(); arrow6->Draw();

    TLatex Tl;
    Tl.SetTextSize(0.04);
    Tl.DrawLatex(3.,1500,"N^{ 0}_{ 2-4}");
    Tl.DrawLatex(8.5,1500,"N^{ 0}_{ 5-6}");
    Tl.DrawLatex(13.5,850,"N^{ 0}_{ #geq7}");
    Tl.DrawLatex(18.5,400,"N^{ #geq1}_{ 2-4}");
    Tl.DrawLatex(23.5,400,"N^{ #geq1}_{ 5-6}");
    Tl.DrawLatex(28.5,400,"N^{ #geq1}_{ #geq7}");
  }

  if(varName=="AllSBins_v6_CD" || varName=="AllSBins_v6_CD_SP" || varName=="AllSBins_v6_CD_EW"  ){
    TLine *line1V6=new TLine( 7.5,0.5,  7.5,3000);
    TLine *line2V6=new TLine(13.5,0.5, 13.5,3000);
    TLine *line3V6=new TLine(19.5,0.5, 19.5,1000);
    TLine *line4V6=new TLine(25.5,0.5, 25.5,300);
    TLine *line5V6=new TLine(31.5,0.5, 31.5,300);
    

    c_cA->cd(); c_cA->SetGridx(0); c_cA->SetGridy(0);
    line1V6->Draw();      line2V6->Draw();  line3V6->Draw();
    line4V6->Draw();      line5V6->Draw();

     TArrow *arrow1 = new TArrow( 0.5,1000, 7.5,1000,0.01,"<|>");
     TArrow *arrow2 = new TArrow( 7.5,1000,13.5,1000,0.01,"<|>");
     TArrow *arrow3 = new TArrow(13.5,650,19.5,650,0.01,"<|>");
     TArrow *arrow4 = new TArrow(19.5,300, 25.5,300,0.01,"<|>");
     TArrow *arrow5 = new TArrow(25.5,300, 31.5,300,0.01,"<|>");
     TArrow *arrow6 = new TArrow(31.5,300, 36.5,300,0.01,"<|>");

    arrow1->Draw(); arrow2->Draw(); arrow3->Draw();
    arrow4->Draw(); arrow5->Draw(); arrow6->Draw();

    TLatex Tl;
    Tl.SetTextSize(0.04);
    Tl.DrawLatex(4.0,1500,"N^{ 0}_{ 2-4}");
    Tl.DrawLatex(10.5,1500,"N^{ 0}_{ 5-6}");
    Tl.DrawLatex(16.5,850,"N^{ 0}_{ #geq7}");
    Tl.DrawLatex(22.5,400,"N^{ #geq1}_{ 2-4}");
    Tl.DrawLatex(27.5,400,"N^{ #geq1}_{ 5-6}");
    Tl.DrawLatex(33.5,400,"N^{ #geq1}_{ #geq7}");
  }

  if(varName=="AllSBins_v6_CD_EW_14bin"  ){
    TLine *line1V6=new TLine( 7.5,0.5,  7.5,3000);
    TLine *line2V6=new TLine(14.5,0.5, 14.5,3000);
    c_cA->cd(); c_cA->SetGridx(0); c_cA->SetGridy(0);
    line1V6->Draw();      line2V6->Draw(); 

     TArrow *arrow1 = new TArrow( 0.5,650, 7.5,650,0.01,"<|>");
     TArrow *arrow2 = new TArrow( 7.5,300,14.5,300,0.01,"<|>");
     arrow1->Draw(); arrow2->Draw();// arrow3->Draw();
    //    arrow4->Draw(); arrow5->Draw(); arrow6->Draw();

    TLatex Tl;
    Tl.SetTextSize(0.04);
    Tl.DrawLatex(1.5,850,"Mass_{leading Ak8jet} : [65,105]");
    Tl.DrawLatex(8.5,400,"Mass_{leading Ak8jet} : [105,140]");
  }

  if(varName=="AllSBins_v6_CD_EW_7bin"  ){
    TLine *line1V6=new TLine( 7.5,0.5,  7.5,3000);
    c_cA->cd(); c_cA->SetGridx(0); c_cA->SetGridy(0);
    line1V6->Draw();     

     TArrow *arrow1 = new TArrow( 0.5,650, 7.5,650,0.01,"<|>");
     arrow1->Draw(); // arrow2->Draw();

    TLatex Tl;
    Tl.SetTextSize(0.04);
    Tl.DrawLatex(1.5,850,"Mass_{leading Ak8jet} : [65,105]");
    //    Tl.DrawLatex(8.5,400,"Mass_{leading Ak8jet} : [105,140]");
  }

  if(varName=="AllSBins_v6_CD_EW_50bin"  ){
    TLine *line1V6=new TLine( 7.5,0.5,  7.5,3000);
    TLine *line2V6=new TLine(13.5,0.5, 13.5,3000);
    TLine *line3V6=new TLine(19.5,0.5, 19.5,1000);
    TLine *line4V6=new TLine(25.5,0.5, 25.5,300);
    TLine *line5V6=new TLine(31.5,0.5, 31.5,300);
    TLine *line6V6=new TLine(37.5,0.5, 37.5,300);
    TLine *line7V6=new TLine(44.5,0.5, 44.5,300);
    

    c_cA->cd(); c_cA->SetGridx(0); c_cA->SetGridy(0);
    line1V6->Draw();      line2V6->Draw();  line3V6->Draw();
    line4V6->Draw();      line5V6->Draw();
    line6V6->Draw();      line7V6->Draw();

     TArrow *arrow1 = new TArrow( 0.5,1000, 7.5,1000,0.01,"<|>");
     TArrow *arrow2 = new TArrow( 7.5,1000,13.5,1000,0.01,"<|>");
     TArrow *arrow3 = new TArrow(13.5,650,19.5,650,0.01,"<|>");
     TArrow *arrow4 = new TArrow(19.5,300, 25.5,300,0.01,"<|>");
     TArrow *arrow5 = new TArrow(25.5,300, 31.5,300,0.01,"<|>");
     TArrow *arrow6 = new TArrow(31.5,300, 37.5,300,0.01,"<|>");
     TArrow *arrow7 = new TArrow(37.5,300, 44.5,300,0.01,"<|>");
     TArrow *arrow8 = new TArrow(44.5,300, 51.5,300,0.01,"<|>");

    arrow1->Draw(); arrow2->Draw(); arrow3->Draw();
    arrow4->Draw(); arrow5->Draw(); arrow6->Draw();
    arrow7->Draw(); arrow8->Draw();
    TLatex Tl;
    Tl.SetTextSize(0.04);
    Tl.DrawLatex(4.0,1500,"N^{ 0}_{ 2-4}");
    Tl.DrawLatex(10.5,1500,"N^{ 0}_{ 5-6}");
    Tl.DrawLatex(16.5,850,"N^{ 0}_{ #geq7}");
    Tl.DrawLatex(22.5,400,"N^{ #geq1}_{ 2-4}");
    Tl.DrawLatex(27.5,400,"N^{ #geq1}_{ 5-6}");
    Tl.DrawLatex(33.5,400,"N^{ #geq1}_{ #geq7}");
    Tl.SetTextSize(0.03);
    Tl.DrawLatex(39.5,400,"EW : W tag");
    Tl.DrawLatex(45.5,400,"EW : H tag");
  }

  if(varName=="AllSBins_v6_CD_EW_50bin_elec1"  ){
    TLine *line1V6=new TLine( 6.5,0.1,  6.5,3000);
    TLine *line2V6=new TLine(12.5,0.1, 12.5,3000);
    TLine *line3V6=new TLine(18.5,0.1, 18.5,1000);
    TLine *line4V6=new TLine(24.5,0.1, 24.5,300);
    TLine *line5V6=new TLine(30.5,0.1, 30.5,300);
    TLine *line6V6=new TLine(36.5,0.1, 36.5,300);
    TLine *line7V6=new TLine(43.5,0.1, 43.5,300);
    

    c_cA->cd(); c_cA->SetGridx(0); c_cA->SetGridy(0);
    line1V6->Draw();      line2V6->Draw();  line3V6->Draw();
    line4V6->Draw();      line5V6->Draw();
    line6V6->Draw();      line7V6->Draw();

     TArrow *arrow1 = new TArrow( 0.5,1000, 6.5,1000,0.01,"<|>");
     TArrow *arrow2 = new TArrow( 6.5,1000,12.5,1000,0.01,"<|>");
     TArrow *arrow3 = new TArrow(12.5,650,18.5,650,0.01,"<|>");
     TArrow *arrow4 = new TArrow(18.5,300, 24.5,300,0.01,"<|>");
     TArrow *arrow5 = new TArrow(24.5,300, 30.5,300,0.01,"<|>");
     TArrow *arrow6 = new TArrow(30.5,300, 36.5,300,0.01,"<|>");
     TArrow *arrow7 = new TArrow(36.5,300, 43.5,300,0.01,"<|>");
     TArrow *arrow8 = new TArrow(43.5,300, 50.5,300,0.01,"<|>");

    arrow1->Draw(); arrow2->Draw(); arrow3->Draw();
    arrow4->Draw(); arrow5->Draw(); arrow6->Draw();
    arrow7->Draw(); arrow8->Draw();
    TLatex Tl;
    Tl.SetTextSize(0.04);
    Tl.DrawLatex(3.0,1500,"N^{ 0}_{ 2-4}");
    Tl.DrawLatex(9.5,1500,"N^{ 0}_{ 5-6}");
    Tl.DrawLatex(15.5,850,"N^{ 0}_{ #geq7}");
    Tl.DrawLatex(21.5,400,"N^{ #geq1}_{ 2-4}");
    Tl.DrawLatex(26.5,400,"N^{ #geq1}_{ 5-6}");
    Tl.DrawLatex(32.5,400,"N^{ #geq1}_{ #geq7}");
    Tl.SetTextSize(0.03);
    Tl.DrawLatex(38.5,400,"EW : W tag");
    Tl.DrawLatex(44.5,400,"EW : H tag");
  }
  
  if(varName=="AllSBins_v6_CD_EW_43bin"  ){
    TLine *line1V6=new TLine( 6.5,0.5,  6.5,3000);
    TLine *line2V6=new TLine(11.5,0.5, 11.5,3000);
    TLine *line3V6=new TLine(16.5,0.5, 16.5,1000);
    TLine *line4V6=new TLine(21.5,0.5, 21.5,300);
    TLine *line5V6=new TLine(26.5,0.5, 26.5,300);
    TLine *line6V6=new TLine(31.5,0.5, 31.5,300);
    TLine *line7V6=new TLine(37.5,0.5, 37.5,300);
    

    c_cA->cd(); c_cA->SetGridx(0); c_cA->SetGridy(0);
    line1V6->Draw();      line2V6->Draw();  line3V6->Draw();
    line4V6->Draw();      line5V6->Draw();
    line6V6->Draw();      line7V6->Draw();

     TArrow *arrow1 = new TArrow( 0.5,1000, 6.5,1000,0.01,"<|>");
     TArrow *arrow2 = new TArrow( 6.5,1000,11.5,1000,0.01,"<|>");
     TArrow *arrow3 = new TArrow(11.5,650,16.5,650,0.01,"<|>");
     TArrow *arrow4 = new TArrow(16.5,300, 21.5,300,0.01,"<|>");
     TArrow *arrow5 = new TArrow(21.5,300, 26.5,300,0.01,"<|>");
     TArrow *arrow6 = new TArrow(26.5,300, 31.5,300,0.01,"<|>");
     TArrow *arrow7 = new TArrow(31.5,250, 37.5,250,0.01,"<|>");
     TArrow *arrow8 = new TArrow(37.5,250, 43.5,250,0.01,"<|>");

    arrow1->Draw(); arrow2->Draw(); arrow3->Draw();
    arrow4->Draw(); arrow5->Draw(); arrow6->Draw();
    arrow7->Draw(); arrow8->Draw();
    TLatex Tl;
    Tl.SetTextSize(0.04);
    Tl.DrawLatex(2.0,1500,"N^{ 0}_{ 2-4}");
    Tl.DrawLatex(8.5,1500,"N^{ 0}_{ 5-6}");
    Tl.DrawLatex(13.5,850,"N^{ 0}_{ #geq7}");
    Tl.DrawLatex(18.5,400,"N^{ #geq1}_{ 2-4}");
    Tl.DrawLatex(23.5,400,"N^{ #geq1}_{ 5-6}");
    Tl.DrawLatex(28.5,400,"N^{ #geq1}_{ #geq7}");
    Tl.DrawLatex(30.5,300,"EW : W tag");
    Tl.DrawLatex(35.5,300,"EW : H tag");
  }
  
  //------------------------------------
  /* if(savePlots){ */
  /*   TString saveName = "supp_Sim_"+varName; */
  /*   TString modelName = f[6]->GetName(); */
  /*   if(modelName.Contains("T5bbbb")) modelName = "T5bbbbZG"; */
  /*   else if(modelName.Contains("T5qqqq")) modelName = "T5qqqqHG"; */
  /*   else if(modelName.Contains("T5tttt")) modelName = "T5ttttZG"; */
  /*   else if(modelName.Contains("T6tt")) modelName = "T6ttZG"; */
  /*   saveName = saveName+"_"+modelName+".pdf"; */
  /*   c_cA->SaveAs(saveName); */
  /* } */
}

void decorate(THStack *hs,int i,const char* fname){
  //  hs->SetMinimum(0.5);
  //hs->SetTitle(0);
  hs->GetXaxis()->SetLabelSize(.05);
  hs->GetYaxis()->SetLabelSize(.05);
  hs->GetXaxis()->SetTitleSize(0.05);
  hs->GetYaxis()->SetTitleSize(0.05);
  //  drawlegend(hist,i,fname);
  //  gPad->Update();
  gStyle->SetOptStat(0);
}
void decorate(TH1D* hist,int i,const char* fname){
  hist->SetLineColor(col[i]);
  if(i<nBG) {
    hist->SetFillColor(col[i]);
    hist->SetLineColor(kBlack);
    hist->SetLineWidth(1);
  }
  else hist->SetLineWidth(2);
  hist->SetTitle(0);
  hist->GetXaxis()->SetLabelSize(.06);
  hist->GetYaxis()->SetLabelSize(.06);
  //hist->SetXLabelSize(0.05);
  hist->GetXaxis()->SetTitleSize(0.06);
  // drawlegend(hist,i,fname);
  //  gPad->Update();
  setLastBinAsOverFlow(hist);
  gStyle->SetOptStat(0);
  
  //Hlist.Add(hist);
}


void drawlegend(TH1D *hist,int i,const char* fname){
  gStyle->SetLegendBorderSize(0);
 
  TString lName=fname;
  
  if(lName.Contains("ZGZJ")){lName="Z(#nu#bar{#nu}) + #gamma";}
  else if(lName.Contains("ZJets")){lName="Z(#nu#bar{#nu}) + jets";}
  else if(lName.Contains("DYJetsToLL")){lName="DY(l^{+}l^{-})";}
  else if(lName.Contains("WJetsToLNu")){lName="W(l#nu) + jets";}
  else if(lName.Contains("WJets")){lName="W(l#nu) + jets";}
  else if(lName.Contains("RareProcess")){}
  else if(lName.Contains("TTJetsHT")){lName="t #bar{t}";}
  else if(lName.Contains("TTJets")){lName="t #bar{t}";}
  else if(lName.Contains("WGJetsToLNuG")){lName="W(l#nu) + #gamma";}
  else if(lName.Contains("WGJets")){lName="W(l#nu) + #gamma";}
  else if(lName.Contains("ZGJetsToNuNuG")){lName="Z(#nu#bar{#nu}) + #gamma";}
  else if(lName.Contains("TTGJets")){lName="t #bar{t} + #gamma";}
  //  else if(lName.Contains("QCD")){lName="QCD";}
  else if(lName.Contains("GJets")){lName="#gamma + jets";}
  else if(lName.Contains("Run2")){lName="Data";}
  //  else if(lName.Contains("T5bbbbZg_1600_150")){lName="T5bbbbZg 1600, 150";}
  else if(lName.Contains("T5bbbbZg_1600_150")){lName = "#tilde{g} #rightarrow b #bar{b} #tilde{#chi}_{1}^{0}, #tilde{#chi}_{1}^{0} #rightarrow #gamma/Z #tilde{G} (m_{#tilde{g}} = 1600 GeV, m_{#tilde{#chi}_{1}^{0}} = 150 GeV)";}
  else if(lName.Contains("T5bbbbZg_1600_1550")){lName = "#tilde{g} #rightarrow b #bar{b} #tilde{#chi}_{1}^{0}, #tilde{#chi}_{1}^{0} #rightarrow #gamma/Z #tilde{G} (m_{#tilde{g}} = 1600 GeV, m_{#tilde{#chi}_{1}^{0}} = 1550 GeV)";}
  else if(lName.Contains("T5bbbbZG_1800_150")){lName = "#tilde{g} #rightarrow b #bar{b} #tilde{#chi}_{1}^{0}, #tilde{#chi}_{1}^{0} #rightarrow #gamma/Z #tilde{G} (m_{#tilde{g}} = 1800 GeV, m_{#tilde{#chi}_{1}^{0}} = 150 GeV)";}
  else if(lName.Contains("T5bbbbZG_1800_1750")){lName = "#tilde{g} #rightarrow b #bar{b} #tilde{#chi}_{1}^{0}, #tilde{#chi}_{1}^{0} #rightarrow #gamma/Z #tilde{G} (m_{#tilde{g}} = 1800 GeV, m_{#tilde{#chi}_{1}^{0}} = 1750 GeV)";}

  else if(lName.Contains("T5bbbbZg_2200_200")){lName = "#tilde{g} #rightarrow b #bar{b} #tilde{#chi}_{1}^{0}, #tilde{#chi}_{1}^{0} #rightarrow #gamma/Z #tilde{G} (m_{#tilde{g}} = 2200 GeV, m_{#tilde{#chi}_{1}^{0}} = 200 GeV)";}
  else if(lName.Contains("T5bbbbZg_2200_1800")){lName = "#tilde{g} #rightarrow b #bar{b} #tilde{#chi}_{1}^{0}, #tilde{#chi}_{1}^{0} #rightarrow #gamma/Z #tilde{G} (m_{#tilde{g}} = 2200 GeV, m_{#tilde{#chi}_{1}^{0}} = 1800 GeV)";}
  else if(lName.Contains("T5bbbbZg_2200_2100")){lName = "#tilde{g} #rightarrow b #bar{b} #tilde{#chi}_{1}^{0}, #tilde{#chi}_{1}^{0} #rightarrow #gamma/Z #tilde{G} (m_{#tilde{g}} = 2200 GeV, m_{#tilde{#chi}_{1}^{0}} = 2100 GeV)";}
  else if(lName.Contains("T5bbbbZg_1800_1000")){lName = "#tilde{g} #rightarrow b #bar{b} #tilde{#chi}_{1}^{0}, #tilde{#chi}_{1}^{0} #rightarrow #gamma/Z #tilde{G} (m_{#tilde{g}} = 1800 GeV, m_{#tilde{#chi}_{1}^{0}} = 1000 GeV)";}

 else if(lName.Contains("T5qqqqHg_1800_150")){lName = "#tilde{g} #rightarrow q #bar{q} #tilde{#chi}_{1}^{0}, #tilde{#chi}_{1}^{0} #rightarrow #gamma/H #tilde{G} (m_{#tilde{g}} = 1800 GeV, m_{#tilde{#chi}_{1}^{0}} = 150 GeV)";}
  else if(lName.Contains("T5qqqqHg_1800_1750")){lName = "#tilde{g} #rightarrow q #bar{q} #tilde{#chi}_{1}^{0}, #tilde{#chi}_{1}^{0} #rightarrow #gamma/H #tilde{G} (m_{#tilde{g}} = 1800 GeV, m_{#tilde{#chi}_{1}^{0}} = 1750 GeV)";}
 else if(lName.Contains("T5qqqqHg_2200_200")){lName = "#tilde{g} #rightarrow q #bar{q} #tilde{#chi}_{1}^{0}, #tilde{#chi}_{1}^{0} #rightarrow #gamma/H #tilde{G} (m_{#tilde{g}} = 2200 GeV, m_{#tilde{#chi}_{1}^{0}} = 200 GeV)";}
  else if(lName.Contains("T5qqqqHg_2200_1800")){lName = "#tilde{g} #rightarrow q #bar{q} #tilde{#chi}_{1}^{0}, #tilde{#chi}_{1}^{0} #rightarrow #gamma/H #tilde{G} (m_{#tilde{g}} = 2200 GeV, m_{#tilde{#chi}_{1}^{0}} = 1800 GeV)";}

  else if(lName.Contains("T5ttttZg_1800_150_")){lName = "#tilde{g} #rightarrow t #bar{t} #tilde{#chi}_{1}^{0}, #tilde{#chi}_{1}^{0} #rightarrow #gamma/Z #tilde{G} (m_{#tilde{g}} = 1800 GeV, m_{#tilde{#chi}_{1}^{0}} = 150 GeV)";}
  else if(lName.Contains("T5ttttZg_1800_1500")){lName = "#tilde{g} #rightarrow t #bar{t} #tilde{#chi}_{1}^{0}, #tilde{#chi}_{1}^{0} #rightarrow #gamma/Z #tilde{G} (m_{#tilde{g}} = 1800 GeV, m_{#tilde{#chi}_{1}^{0}} = 1500 GeV)";}
  else if(lName.Contains("T5ttttZg_2200_200_")){lName = "#tilde{g} #rightarrow t #bar{t} #tilde{#chi}_{1}^{0}, #tilde{#chi}_{1}^{0} #rightarrow #gamma/Z #tilde{G} (m_{#tilde{g}} = 2200 GeV, m_{#tilde{#chi}_{1}^{0}} = 200 GeV)";}
  else if(lName.Contains("T5ttttZg_2200_1800")){lName = "#tilde{g} #rightarrow t #bar{t} #tilde{#chi}_{1}^{0}, #tilde{#chi}_{1}^{0} #rightarrow #gamma/Z #tilde{G} (m_{#tilde{g}} = 2200 GeV, m_{#tilde{#chi}_{1}^{0}} = 1800 GeV)";}
  else if(lName.Contains("T5ttttZg_1800_1550")){lName = "#tilde{g} #rightarrow t #bar{t} #tilde{#chi}_{1}^{0}, #tilde{#chi}_{1}^{0} #rightarrow #gamma/Z #tilde{G} (m_{#tilde{g}} = 1800 GeV, m_{#tilde{#chi}_{1}^{0}} = 1550 GeV)";}
  else if(lName.Contains("T5ttttZg_1800_1575")){lName = "#tilde{g} #rightarrow t #bar{t} #tilde{#chi}_{1}^{0}, #tilde{#chi}_{1}^{0} #rightarrow #gamma/Z #tilde{G} (m_{#tilde{g}} = 1800 GeV, m_{#tilde{#chi}_{1}^{0}} = 1575 GeV)";}
  else if(lName.Contains("T5ttttZg_1800_1000")){lName = "#tilde{g} #rightarrow t #bar{t} #tilde{#chi}_{1}^{0}, #tilde{#chi}_{1}^{0} #rightarrow #gamma/Z #tilde{G} (m_{#tilde{g}} = 1800 GeV, m_{#tilde{#chi}_{1}^{0}} = 1000 GeV)";}

  else if(lName.Contains("T6ttZg_1000_100")){lName = "#tilde{t} #rightarrow t #tilde{#chi}_{1}^{0}, #tilde{#chi}_{1}^{0} #rightarrow #gamma/Z #tilde{G} (m_{#tilde{g}} = 1000 GeV, m_{#tilde{#chi}_{1}^{0}} = 100 GeV)";}
  else if(lName.Contains("T6ttZg_1000_900")){lName = "#tilde{t} #rightarrow t #tilde{#chi}_{1}^{0}, #tilde{#chi}_{1}^{0} #rightarrow #gamma/Z #tilde{G} (m_{#tilde{g}} = 1000 GeV, m_{#tilde{#chi}_{1}^{0}} = 900 GeV)";}
  else if(lName.Contains("T6ttZg_1200_200")){lName = "#tilde{t} #rightarrow t #tilde{#chi}_{1}^{0}, #tilde{#chi}_{1}^{0} #rightarrow #gamma/Z #tilde{G} (m_{#tilde{g}} = 1200 GeV, m_{#tilde{#chi}_{1}^{0}} = 200 GeV)";}
  else if(lName.Contains("T6ttZg_1200_1000")){lName = "#tilde{t} #rightarrow t #tilde{#chi}_{1}^{0}, #tilde{#chi}_{1}^{0} #rightarrow #gamma/Z #tilde{G} (m_{#tilde{g}} = 1200 GeV, m_{#tilde{#chi}_{1}^{0}} = 1000 GeV)";}
  else if(lName.Contains("T6ttZg_1400_200")){lName = "#tilde{t} #rightarrow t #tilde{#chi}_{1}^{0}, #tilde{#chi}_{1}^{0} #rightarrow #gamma/Z #tilde{G} (m_{#tilde{g}} = 1400 GeV, m_{#tilde{#chi}_{1}^{0}} = 200 GeV)";}
  else if(lName.Contains("T6ttZg_1400_1200")){lName = "#tilde{t} #rightarrow t #tilde{#chi}_{1}^{0}, #tilde{#chi}_{1}^{0} #rightarrow #gamma/Z #tilde{G} (m_{#tilde{g}} = 1400 GeV, m_{#tilde{#chi}_{1}^{0}} = 1200 GeV)";}
  else if(lName.Contains("T6ttZg_1700_200")){lName = "#tilde{t} #rightarrow t #tilde{#chi}_{1}^{0}, #tilde{#chi}_{1}^{0} #rightarrow #gamma/Z #tilde{G} (m_{#tilde{g}} = 1700 GeV, m_{#tilde{#chi}_{1}^{0}} = 200 GeV)";}
  else if(lName.Contains("T6ttZg_1700_1500")){lName = "#tilde{t} #rightarrow t #tilde{#chi}_{1}^{0}, #tilde{#chi}_{1}^{0} #rightarrow #gamma/Z #tilde{G} (m_{#tilde{g}} = 1700 GeV, m_{#tilde{#chi}_{1}^{0}} = 1500 GeV)";}

  // else if(lName.Contains("T5bbbbZg_1600_150")){lName = "T5bbbbZG (m_{#tilde{g}} = 1600 GeV, m_{#tilde{#chi}_{1}^{0}} = 150 GeV)";}
  // else if(lName.Contains("T5bbbbZg_1600_1550")){lName = "T5bbbbZG (m_{#tilde{g}} = 1600 GeV, m_{#tilde{#chi}_{1}^{0}} = 1550 GeV)";}
  else if(lName.Contains("T5bbbbZg_1600_1550")){lName="T5bbbbZg 1600, 1550";}
  else if(lName.Contains("T5qqqqHg_1600_1550")){lName="T5qqqqHg_1550";}
  else if(lName.Contains("T5qqqqHg_1600_150")){lName="T5qqqqHg_150";}
  else if(lName.Contains("TChiWg_0_400")){lName="TChiWg , M#tilde{#chi}_{1}^{0} = M#tilde{#chi}_{1}^{+/-} = 400 GeV";}
  else if(lName.Contains("TChiWg_0_800")){lName="TChiWg , M#tilde{#chi}_{1}^{0} = M#tilde{#chi}_{1}^{+/-} = 800 GeV";}
  else if(lName.Contains("TChiWg_0_1200")){lName="TChiWg , M#tilde{#chi}_{1}^{0} = M#tilde{#chi}_{1}^{+/-} = 1200 GeV";}
  else if(lName.Contains("TChiNg_N1C2_C1C2_0_400")){lName="TChiNg , M#tilde{#chi}_{1}^{+/-} = M#tilde{#chi}_{1}^{0} = 400 GeV";}
  else if(lName.Contains("TChiNg_N1C2_C1C2_0_800")){lName="TChiNg , M#tilde{#chi}_{1}^{+/-} = M#tilde{#chi}_{1}^{0} = 800 GeV";}
  else if(lName.Contains("TChiNg_N1C2_C1C2_0_1200")){lName="TChiNg , M#tilde{#chi}_{1}^{+/-} = M#tilde{#chi}_{1}^{0} = 1200 GeV";}
  else if(lName.Contains("TChiNg_0_400")){lName="TChiNg , M#tilde{#chi}_{2}^{0} = M#tilde{#chi}_{3}^{0} = 400 GeV";}
  else if(lName.Contains("TChiNg_0_800")){lName="TChiNg , M#tilde{#chi}_{2}^{0} = M#tilde{#chi}_{3}^{0} = 800 GeV";}
  else if(lName.Contains("TChiNg_0_1200")){lName="TChiNg , M#tilde{#chi}_{2}^{0} = M#tilde{#chi}_{3}^{0} = 1200 GeV";}

  // const char *l_name=lName.c_str();
  if(i<nBG)legend1->AddEntry(hist,lName,"f");
  //  if(i<nBG)legend1->AddEntry(hist,lName,"f");
  else legend2->AddEntry(hist,lName,"lp");
  // legend1->SetTextSize(0.04);
}


void setLastBinAsOverFlow(TH1D* h_hist){
  double lastBinCt =h_hist->GetBinContent(h_hist->GetNbinsX()),overflCt =h_hist->GetBinContent(h_hist->GetNbinsX()+1);
  double lastBinErr=h_hist->GetBinError(h_hist->GetNbinsX()),  overflErr=h_hist->GetBinError(h_hist->GetNbinsX()+1);
  
  if(lastBinCt!=0 && overflCt!=0)
    lastBinErr = (lastBinCt+overflCt)* (sqrt( ((lastBinErr/lastBinCt)*(lastBinErr/lastBinCt)) + ((overflErr/overflCt)*(overflErr/overflCt)) ) );
  
  else if(lastBinCt==0 && overflCt!=0)
    lastBinErr = overflErr;
  else if(lastBinCt!=0 && overflCt==0)
    lastBinErr = lastBinErr;
  else lastBinErr=0;

  lastBinCt = lastBinCt+overflCt;
  h_hist->SetBinContent(h_hist->GetNbinsX(),lastBinCt);
  h_hist->SetBinError(h_hist->GetNbinsX(),lastBinErr);
    
}

TH1D* setMyRange(TH1D *h1,double xLow,double xHigh){
  //call it after setting last bin as overflow
  double err=0;
  if(xHigh > 13000) return h1;
  if(xLow < -13000) return h1;
  // h1->Print("all");
  int nMax=h1->FindBin(xHigh);
  h1->SetBinContent(nMax,h1->IntegralAndError(nMax,h1->GetNbinsX(),err));
  h1->SetBinError(nMax,err);
  //  cout<<nMax<<endl;
  for(int i=nMax+1;i<=h1->GetNbinsX()+1;i++){
    h1->SetBinContent(i,0);
    h1->SetBinError(i,0);
    //    cout<<":";
  }
  //  h1->Print("all");
  //  cout<<endl;
  return h1;
  //  h1->GetXaxis()->SetRangeUser(xLow,xHigh);                                                                                                                      
}
