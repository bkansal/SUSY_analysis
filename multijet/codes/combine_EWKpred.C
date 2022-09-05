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
#include"TGraphAsymmErrors.h"

vector<int> col={kGray,kOrange,kTeal+9,kCyan-1,kCyan-1,kBlack};
void decorate(TH1D*,int,const char*);
void combine_EWKpred()
{
  TFile *f1, *f2,*f3,*f4,*TF,*f5,*f6;
  TString name,name1;
  TH1D *cr,*cr1,*cr2,*cr3,*cr4,*cr5,*ewk1,*ewk2,*ewk3,*ewk4,*data,*cr6,*cr7;
  TString path,path1,path2,path3,path4,path5;
  THStack *hs_var[10];
  THStack *zin  =new THStack("Z invi","Z invi");
  int rebin=1;
  double xmin_,xmax_,xmin,xmax,ymin,ymax,ymin_,ymax_;
  bool lowdphi=false;
  double tf_51[50];
  TCanvas *c1;
  c1 = new TCanvas("stackhist","stackhist",900,1000);

  ////////////////// Before Multi Jet predioctions /////////////////
  if(lowdphi){
    //    path="/Users/bkansal/work/MET_Analysis/Analysis/lostlepton/rootoutput/newselec_LL_noISRjet_METfilters_EW_hadjetID_newPU_v18/TF_v5_usingfullRun2_BTagDeepCSV_lowdphi_newBin2/Run2_METdata_CR_v18.root";
    //  path1="/Users/bkansal/work/MET_Analysis/Analysis/fakerate/rootout/fake_rate_v8/FR_using_PhoPtQmulti_csv_cut_EMObjeta_qmulti_METCaloMET_lowdphi_nopxveto_SFnopxveto_newbin2/Run2_METdata_CR_v18.root";
    // path2="/Users/bkansal/work/MET_Analysis/Analysis/Z_invisible/rootoutput/v6/withphicut_zmass60to120_lowdphi_newBin2/ZJZGToNuNu_CR_v18.root";
    path="/Users/bkansal/work/MET_Analysis/Analysis/multijet/rootoutput/v1/ST300_Rfactor_notapplied/EWK_LL.root";
    path1="/Users/bkansal/work/MET_Analysis/Analysis/multijet/rootoutput/v1/ST300_Rfactor_notapplied/EWK_FR.root";
    path2="/Users/bkansal/work/MET_Analysis/Analysis/multijet/rootoutput/v1/ST300_Rfactor_notapplied/EWK_Zin.root";
    path3="/Users/bkansal/work/MET_Analysis/Analysis/multijet/rootoutput/v1/ST300_Rfactor_notapplied/Run2_METdata_CR_v18.root";
    path4="/Users/bkansal/work/MET_Analysis/Analysis/multijet/rootoutput/v1/ST300_Rfactor_notapplied/EWK.root";
    path5="/Users/bkansal/work/MET_Analysis/Analysis/rootoutput/root_withMET250andphocut100_EWselec_njet6_leadAk8_wtag_htag_noSB_PUISR_HEML1_newBin2/Run2_METdata.root";

  }

  //////////////////// After Multi Jet predictions /////////////////
  if(!lowdphi){
    //    path="/Users/bkansal/work/MET_Analysis/Analysis/lostlepton/rootoutput/newselec_LL_noISRjet_METfilters_EW_hadjetID_newPU_v18/TF_v5_usingfullRun2_BTagDeepCSV_newBin2/Run2_METdata_CR_v18.root";
    // path1="/Users/bkansal/work/MET_Analysis/Analysis/fakerate/rootout/fake_rate_v8/FR_using_PhoPtQmulti_csv_cut_EMObjeta_qmulti_METCaloMET_nopxveto_SFnopxveto_newbin2/Run2_METdata_CR_v18.root";
    // path2="/Users/bkansal/work/MET_Analysis/Analysis/Z_invisible/rootoutput/v6/withphicut_zmass60to120_newBin2/ZJZGToNuNu_CR_v18.root";
    path="/Users/bkansal/work/MET_Analysis/Analysis/multijet/rootoutput/v1/ST300_Rfactor_notapplied/CD/EWK_LL.root";
    path1="/Users/bkansal/work/MET_Analysis/Analysis/multijet/rootoutput/v1/ST300_Rfactor_notapplied/CD/EWK_FR.root";
    path2="/Users/bkansal/work/MET_Analysis/Analysis/multijet/rootoutput/v1/ST300_Rfactor_notapplied/CD/EWK_Zin.root";
    path3="/Users/bkansal/work/MET_Analysis/Analysis/multijet/rootoutput/v1/ST300_Rfactor_applied_data/Run2_METdata_CR_v18.root";
    path4="/Users/bkansal/work/MET_Analysis/Analysis/multijet/rootoutput/v1/ST300_Rfactor_applied_data/EWK.root";
    path5="/Users/bkansal/work/MET_Analysis/Analysis/rootoutput/root_withMET250andphocut100_EWselec_njet6_leadAk8_wtag_htag_noSB_PUISR_HEML1_newBin2/Run2_METdata.root";
    //    path5="/Users/bkansal/work/MET_Analysis/Analysis/rootoutput/root_withMET250andphocut100_EWselec_njet6_leadAk8_wtag_htag_noSB_PUISR_HEML1_highdphi_lowMET_newBin2/Run2_METdata.root";
  }

  f1 = new TFile(path); 
  f2 = new TFile(path1);
  f3 = new TFile(path2);
  f4 = new TFile(path3);
  f5 = new TFile(path4);
  f6 = new TFile(path5);

  TString varName[10]={"AllSBins_v6_CD_EW_50bin","MET","nJets","nBTags","ST","BestPhotonPt","BestPhotonPhi","BestPhotonEta"};
  //  TString varName[10]={"MET","nJets","nBTags","ST","BestPhotonPt","BestPhotonPhi","BestPhotonEta"};

  c1->SetLogy();
  c1->cd();
  //    for(int i=0; i<varName.size();i++)
  for(int i=0; i<1;i++)
    {
        name=varName[i]+"_elec1_closure";
	name1=varName[i]+"_B";

	cr1 = (TH1D*)f1->Get(name);
	cr2 = (TH1D*)f2->Get(name);
	cr3 = (TH1D*)f3->Get(name);
        cr4 = (TH1D*)f4->Get(name1);
	name1=varName[i]+"_A";
        cr5 = (TH1D*)f4->Get(name1);
	cr6 = (TH1D*)f5->Get(name);
       	cr7 = (TH1D*)f6->Get(varName[i]);
	//cr4->Add(cr5);
       	cr4->Add(cr6,-1);
	//	for(int i=0;i<30;i++)
	//  cout<<i<<" : "<<cr4->GetBinContent(i)<<" : "<<cr6->GetBinContent(i)<<endl;	
	cr1->SetLineColor(1);
	cr2->SetLineColor(2);
        cr3->SetLineColor(3);
        cr4->SetLineColor(4);	
	cr7->SetLineColor(kBlack);
	cr7->SetMarkerColor(kBlack);

	hs_var[i]  =new THStack(varName[i],varName[i]);

	if(varName[i]=="MET" || varName[i]=="BestPhotonPt"){xmin_=200,xmax_=1000,xmin=200,xmax=1000,rebin=5, ymin=0 , ymax=2.99, ymin_=0.5 , ymax_=100000;}
	else if(varName[i]=="nJets" || varName[i]=="nBTags"){rebin=1,xmin_=0,xmax_=10,xmin=0,xmax=10 , ymin=0 , ymax=2.99, ymin_=0.5 , ymax_=100000;}
	else if(varName[i]=="ST") { rebin=10, xmin_=0,xmax_=4000,xmin=0,xmax=4000,ymin=0 , ymax=2.99, ymin_=0.1 , ymax_=10000;}
	else if(varName[i]=="BestPhotonPhi" || varName[i]=="BestPhotonEta"){rebin=10, xmin_=-4.5,xmax_=4.5,xmin=-4.5,xmax=4.5, ymin=0 , ymax=3.99, ymin_=0.5 , ymax_=100000;}
	else if(varName[i]=="AllSBins_v6_CD_EW_50bin"){rebin=1,xmin_=0,xmax_=48,xmin=0,xmax=48, ymin=0 , ymax=3.99, ymin_=0.5 , ymax_=100000;}
	cr1->Rebin(rebin);
        cr2->Rebin(rebin);
        cr3->Rebin(rebin);
	cr4->Rebin(rebin);
	cr7->Rebin(rebin);
	cr1->GetXaxis()->SetRangeUser(xmin,xmax);
	cr2->GetXaxis()->SetRangeUser(xmin,xmax);
        cr3->GetXaxis()->SetRangeUser(xmin,xmax);
        cr4->GetXaxis()->SetRangeUser(xmin,xmax);
	cr7->GetXaxis()->SetRangeUser(xmin,xmax);

	decorate(cr1,0,f1->GetName());
	decorate(cr2,1,f2->GetName());
	decorate(cr3,2,f3->GetName());
        decorate(cr4,3,f4->GetName());
        //decorate(cr5,4,f4->GetName());

	hs_var[i]->Add(cr1);
	hs_var[i]->Add(cr2);
        hs_var[i]->Add(cr3);
        hs_var[i]->Add(cr4);
	// hs_var[i]->Add(cr5);

	hs_var[i]->Draw("hist");
	hs_var[i]->SetMinimum(ymin_);
	hs_var[i]->SetMaximum(ymax_);
	hs_var[i]->GetXaxis()->SetRangeUser(xmin,xmax);
	hs_var[i]->Draw("hist");
	cr7->Draw("same");
	name1=varName[i]+".pdf";
	c1->SaveAs(name1);
	//	cr2->Draw("sames");
	//        cr3->Draw("sames");

    }

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
