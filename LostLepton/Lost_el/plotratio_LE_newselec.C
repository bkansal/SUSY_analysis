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

//bool ExpvsPred=true,SRvsCR=false;
//bool ExpvsPred=false,SRvsCR=true;
//vector<int> col={kGray,kTeal+9,kRed,kCyan-1,kBlack};
vector<int> col={kGray,kTeal+9,kOrange,kCyan-1,kBlack};
//vector<int> col={kOrange,kCyan-1,kBlack};

vector<double> METLowEdge_v2={200,250,300,370,450,600,750,900,2000};
vector<double> PhoLowEdge={0,100,120,140,160,180,200,220,250,280,320,380,450,550,650,750};
void decorate(TH1D*,int,const char*);

void plotratio_LE_newselec(TString varname,TString title1,bool ExpvsPred, bool SRvsCR)
{
  TFile *f1,*f_0,*f_1,*f_2,*f_3,*f2;
  //  bool LE=true;
  string lep="LE";
  //  bool LE=false;

  TString ntuple="v18";
  //  TString title1="2018";
  //  TString path = "rootoutput/newselec_LE_v2/";
  /* TString path = "rootoutput/newselec_LE_noISRjet_noHEM/"; */
  //  TString path = "rootoutput/newselec_LM_noISRjet_v2/";
  //  TString path = "rootoutput/newselec_LM_noISRjet_METfilters/";
  //  TString path = "rootoutput/newselec_LEplusLM_noISRjet/";
  //  TString path ="rootoutput/newselec_LM_noISRjet_METfilters_nogenpromptpho_forWGandTTG_EW/";
  //  TString path ="rootoutput/newselec_LL_noISRjet_METfilters_EW_hadjetID/TF_v3/";
  //  TString path ="rootoutput/newselec_LM_noISRjet_METfilters_EW_hadjetID/";
  // TString path ="rootoutput/newselec_LM_noISRjet_METfilters_EW_hadjetID/";
  //  TString path ="rootoutput/newselec_LL_noISRjet_METfilters_nogenpromptpho_forWGandTTG_EW/";
  //  TString path ="rootoutput/newselec_LE_noISRjet_METfilters_nogenpromptpho_forWGandTTG/"
  // TString path = "./";
  //  TString path = "./tmp2/";
  /////  TString path="rootoutput/newselec_LE_noISRjet_METfilters_EW_hadjetID_v18/TF_v3_usingfullRun2/";
  TString path="rootoutput/newselec_LE_noISRjet_METfilters_EW_hadjetID_v18/TF_v3/";
  //  TString path = "rootoutput/newselec_LE_noISRjet_noHEM/";
  /* TString path = "rootoutput/newselec_LE_noISRjet_noHEM_noprefire/"; */
  /* TString path= "rootoutput/newselec_LE_noISRjet_noprefire/"; */
  TString path1;
  /* if(title1=="full_Run2") */
  /*   path1 =path+"TTWGJ_CR.root"; */
  /* else */
  /*   path1 =path+"TTWGJ_"+title1+"_CR_v18.root"; */

  /* f1 = new TFile(path1); */


  if(ntuple=="v18"){  
  if(title1=="full_Run2"){
    path1=path+"Run2_METdata_CR_v18.root";
    f2 = new TFile(path1);
    path1=path+"TTWGJ_CR_v18.root";
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
    }
  
  else
    {
      path1=path+"Run"+title1+"_METdata_CR_v18.root";
      f2 = new TFile(path1);
      path1=path+"TTWGJ_"+title1+"_CR_v18.root";
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
    }
  }

  else{
  if(title1=="full_Run2"){
    path1=path+"Run2_METdata_CR.root";
    f2 = new TFile(path1);
    path1=path+"TTWGJ_CR.root";
    f1 = new TFile(path1);
    path1=path+"TTGJets_CR.root";
    f_0 = new TFile(path1);
    path1=path+"TTJets_CR.root";
    f_1 = new TFile(path1);
    path1=path+"WJets_CR.root";
    f_2 = new TFile(path1);
    path1=path+"WGJets_CR.root";
    f_3 = new TFile(path1);
    }
  
  else
    {
      path1=path+"Run"+title1+"_METdata_CR.root";
      f2 = new TFile(path1);
      path1=path+"TTWGJ_"+title1+"_CR.root";
      f1 = new TFile(path1);
      path1=path+"TTGJets_"+title1+"_CR.root";
      f_0 = new TFile(path1);
      path1=path+"TTJets_"+title1+"_CR.root";
      f_1 = new TFile(path1);
      path1=path+"WJets_"+title1+"_CR.root";
      f_2 = new TFile(path1);
      path1=path+"WGJets_"+title1+"_CR.root";
      f_3 = new TFile(path1);
    }
  }
  
  
  TLatex textOnTop,intLumiE;

  TString name;
  if (lep=="LE")
    name="Run"+title1+"_TF_LE_v6_CD";
  else if (lep=="LM")
    name="Run"+title1+"_TF_LM_v6_CD";
  else if (lep=="LL")
    name="Run"+title1+"_TF_LL_v6_CD";
  //  TString png;
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
      pdf = path+"/PDF/TF/"+varname+"_"+title1+"_v2.pdf";
      png= path+"/PDF/TF/"+varname+"_"+title1+"_v2.png";

      cout<<"root file name : "<<rootout<<endl;
      TFile *fout =new TFile(rootout,"recreate");
      fout->cd();
    }

  
  int k=1;

  TString varName2_,varname_elec1,varname_elec0;
  TLegend *legend; 
  TLegend *legend1; 

  if(varname=="AllSBins_v7_CD_SP" || varname=="AllSBins_v6_CD_EW_50bin")
    {
      legend= new TLegend(0.75,0.75,0.9,0.99);
      legend1= new TLegend(0.6,0.7,0.9,0.99);
      varname_elec1=varname+"_elec1";
      varname_elec0=varname+"_elec0";
    }
  else
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
      TH1D *fail_accept,*fail_id,*fail_iso,*cr,*fake_photon,*sr,*h_0_cr,*h_1_cr,*h_2_cr,*h_3_cr,*h_0_sr,*h_1_sr,*h_2_sr,*h_3_sr;
      THStack *hs_var=new THStack("var_Stack",varName[i]);
      THStack *hs_var_cr=new THStack("var_Stack_cr",varName[i]);

      cout<<varName[i]<<endl;
      /* pdf1= path+"PDF/TF/"+varName[i]+"_"+name+".pdf"; */
      /* png= path+"PDF/TF/"+varName[i]+"_"+name+".png"; */
      if(varName[i]=="AllSBins_v7_CD_SP_tmp"){
	cr          = (TH1D*)f1->Get("AllSBins_v7_CD_SP_tmp_elec1");
	sr          = (TH1D*)f1->Get("AllSBins_v7_CD_SP_tmp_elec0");
	h_0_cr=(TH1D*)f_0->FindObjectAny("AllSBins_v7_CD_SP_tmp_elec1");
	h_1_cr=(TH1D*)f_1->FindObjectAny("AllSBins_v7_CD_SP_tmp_elec1");
	h_2_cr=(TH1D*)f_2->FindObjectAny("AllSBins_v7_CD_SP_tmp_elec1");
	h_3_cr=(TH1D*)f_3->FindObjectAny("AllSBins_v7_CD_SP_tmp_elec1");
	h_0_sr=(TH1D*)f_0->FindObjectAny("AllSBins_v7_CD_SP_tmp_elec0");
	h_1_sr=(TH1D*)f_1->FindObjectAny("AllSBins_v7_CD_SP_tmp_elec0");
	h_2_sr=(TH1D*)f_2->FindObjectAny("AllSBins_v7_CD_SP_tmp_elec0");
	h_3_sr=(TH1D*)f_3->FindObjectAny("AllSBins_v7_CD_SP_tmp_elec0");
	ymin_=1, ymax_=1000;
	nbin=18, bin0=1, bin1=19;
	xmin_=2,xmax_=19;
	total = new TH1D("total","Total = fail_id+fail_iso+fail_accept+1e_cr",nbin,bin0,bin1);
	TF[i]= new TH1D("tf_SP_3","Transfer factor for SP : NJets x Nbtag & EW : wtag & htag",nbin,bin0,bin1);
      }
      else if(varName[i]=="AllSBins_v6_CD_EW_50bin"){
	name1="Bin no.";
	cr          = (TH1D*)f1->Get(varName2[i]);
	sr          = (TH1D*)f1->Get(varName1[i]);
	h_0_cr=(TH1D*)f_0->FindObjectAny(varName2[i]);
	h_1_cr=(TH1D*)f_1->FindObjectAny(varName2[i]);
	h_2_cr=(TH1D*)f_2->FindObjectAny(varName2[i]);
	h_3_cr=(TH1D*)f_3->FindObjectAny(varName2[i]);
	h_0_sr=(TH1D*)f_0->FindObjectAny(varName1[i]);
	h_1_sr=(TH1D*)f_1->FindObjectAny(varName1[i]);
	h_2_sr=(TH1D*)f_2->FindObjectAny(varName1[i]);
	h_3_sr=(TH1D*)f_3->FindObjectAny(varName1[i]);
	/* if(lep=="LE" )	ymin_=0.1, ymax_=1000; */
	/* if(lep=="LL" )	ymin_=1, ymax_=10000; */
	ymin_=0.1, ymax_=100000;

	yset_=200;
	nbin=51, bin0=0.5, bin1=51.5;
	xmin_=-1,xmax_=50;
	/* nbin=51, bin0=-1, bin1=50; */
	/* xmin_=-1,xmax_=50; */
	total = new TH1D("total","Total = fail_id+fail_iso+fail_accept+1e_cr",nbin,bin0,bin1);
	TF[i]= new TH1D("tf_SP_4","Transfer factor for SP : NJets x Nbtag & EW : wtag & htag",nbin,bin0,bin1);
      }
   
      if(varName[i]=="AllSBins_v7_CD_SP"){
	name1="Bin no.";
	cr          = (TH1D*)f1->Get(varName2[i]);
	sr          = (TH1D*)f1->Get(varName1[i]);
	h_0_cr=(TH1D*)f_0->FindObjectAny(varName2[i]);
	h_1_cr=(TH1D*)f_1->FindObjectAny(varName2[i]);
	h_2_cr=(TH1D*)f_2->FindObjectAny(varName2[i]);
	h_3_cr=(TH1D*)f_3->FindObjectAny(varName2[i]);
	h_0_sr=(TH1D*)f_0->FindObjectAny(varName1[i]);
	h_1_sr=(TH1D*)f_1->FindObjectAny(varName1[i]);
	h_2_sr=(TH1D*)f_2->FindObjectAny(varName1[i]);
	h_3_sr=(TH1D*)f_3->FindObjectAny(varName1[i]);
	if(lep=="LE" )	ymin_=0.1, ymax_=1000;
	if(lep=="LL" )	ymin_=1, ymax_=10000;
	//	ymin_=1, ymax_=1000;
	nbin=10, bin0=1, bin1=11;
	xmin_=1,xmax_=11;
	total = new TH1D("total","Total = fail_id+fail_iso+fail_accept+1e_cr",nbin,bin0,bin1);
	TF[i]= new TH1D("tf_SP_2","Transfer factor for SP : NJets x Nbtag & EW : wtag & htag",nbin,bin0,bin1);

      }
      if(varName[i]=="hadAk8Mass"){
	name1=varname;
	cr          = (TH1D*)f1->Get(varName2[i]);
	sr          = (TH1D*)f1->Get(varName1[i]);
	h_0_cr=(TH1D*)f_0->FindObjectAny(varName2[i]);
	h_1_cr=(TH1D*)f_1->FindObjectAny(varName2[i]);
	h_2_cr=(TH1D*)f_2->FindObjectAny(varName2[i]);
	h_3_cr=(TH1D*)f_3->FindObjectAny(varName2[i]);
	h_0_sr=(TH1D*)f_0->FindObjectAny(varName1[i]);
	h_1_sr=(TH1D*)f_1->FindObjectAny(varName1[i]);
	h_2_sr=(TH1D*)f_2->FindObjectAny(varName1[i]);
	h_3_sr=(TH1D*)f_3->FindObjectAny(varName1[i]);
	int rebin=1;

	if(lep=="LE" )	ymin_=0.1, ymax_=1000;
	if(lep=="LL" )	ymin_=1, ymax_=10000;
	
	//	ymin_=1, ymax_=1000;
	nbin=1000/rebin, bin0=0, bin1=300;
	xmin_=0,xmax_=300;
	total = new TH1D("total","Total = fail_id+fail_iso+fail_accept+1e_cr",nbin,bin0,bin1);
	TF[i]= new TH1D("tf_SP_2","Transfer factor for SP : NJets x Nbtag & EW : wtag & htag",nbin,bin0,bin1);

	cr->Rebin(rebin);
	sr->Rebin(rebin);
	h_0_cr->Rebin(rebin);
	h_1_cr->Rebin(rebin);
	h_2_cr->Rebin(rebin);
	h_3_cr->Rebin(rebin);
	h_0_sr->Rebin(rebin);
	h_1_sr->Rebin(rebin);
	h_2_sr->Rebin(rebin);
	h_3_sr->Rebin(rebin);

      }

      if(varName[i]=="nJets" || varName[i]=="nBTags"){
	name1=varname;
	cr          = (TH1D*)f1->Get(varName2[i]);
	sr          = (TH1D*)f1->Get(varName1[i]);
	h_0_cr=(TH1D*)f_0->FindObjectAny(varName2[i]);
	h_1_cr=(TH1D*)f_1->FindObjectAny(varName2[i]);
	h_2_cr=(TH1D*)f_2->FindObjectAny(varName2[i]);
	h_3_cr=(TH1D*)f_3->FindObjectAny(varName2[i]);
	h_0_sr=(TH1D*)f_0->FindObjectAny(varName1[i]);
	h_1_sr=(TH1D*)f_1->FindObjectAny(varName1[i]);
	h_2_sr=(TH1D*)f_2->FindObjectAny(varName1[i]);
	h_3_sr=(TH1D*)f_3->FindObjectAny(varName1[i]);

	if(lep=="LE" )	ymin_=0.1, ymax_=1000;
	if(lep=="LL" )	ymin_=0.1, ymax_=1000;
	//	ymin_=1, ymax_=1000;
	if(varName[i]=="nJets")
	  {
	    nbin=25, bin0=0, bin1=25;
	    xmin_=2,xmax_=15;
	  }
	else if(varName[i]=="nBTags")
	  {
	    nbin=10, bin0=0, bin1=10;
	    xmin_=0,xmax_=10;
	  }
	total = new TH1D("total","Total = fail_id+fail_iso+fail_accept+1e_cr",nbin,bin0,bin1);
	TF[i]= new TH1D("tf_SP_2","Transfer factor for SP : NJets x Nbtag & EW : wtag & htag",nbin,bin0,bin1);
      }

      if(varName[i]=="BestPhotonPt_vBin" || varName[i]=="METvBin2"){
	name1=varname;	
	cr          = (TH1D*)f1->Get(varName2[i]);
	sr          = (TH1D*)f1->Get(varName1[i]);
	h_0_cr=(TH1D*)f_0->FindObjectAny(varName2[i]);
	h_1_cr=(TH1D*)f_1->FindObjectAny(varName2[i]);
	h_2_cr=(TH1D*)f_2->FindObjectAny(varName2[i]);
	h_3_cr=(TH1D*)f_3->FindObjectAny(varName2[i]);
	h_0_sr=(TH1D*)f_0->FindObjectAny(varName1[i]);
	h_1_sr=(TH1D*)f_1->FindObjectAny(varName1[i]);
	h_2_sr=(TH1D*)f_2->FindObjectAny(varName1[i]);
	h_3_sr=(TH1D*)f_3->FindObjectAny(varName1[i]);

	if(lep=="LE" )	ymin_=0.1, ymax_=1000;
	if(lep=="LL" )	ymin_=0.1, ymax_=1000;
	//	ymin_=1, ymax_=1000;
	if(varName[i]=="BestPhotonPt_vBin"){
	  nbin=0, bin0=0, bin1=750;
	  xmin_=0,xmax_=750;
	  total = new TH1D("total","Total = fail_id+fail_iso+fail_accept+1e_cr",PhoLowEdge.size()-1,&(PhoLowEdge[0]));
	  TF[i]= new TH1D("tf_SP_2","Transfer factor for SP : NJets x Nbtag & EW : wtag & htag",PhoLowEdge.size()-1,&(PhoLowEdge[0]));
	}
	if(varName[i]=="METvBin2"){
	  nbin=0, bin0=0, bin1=750;
	  xmin_=METLowEdge_v2[0],xmax_=2000;
	  total = new TH1D("total","Total = fail_id+fail_iso+fail_accept+1e_cr",METLowEdge_v2.size()-1,&(METLowEdge_v2[0]));
	  TF[i]= new TH1D("tf_SP_2","Transfer factor for SP : NJets x Nbtag & EW : wtag & htag",METLowEdge_v2.size()-1,&(METLowEdge_v2[0]));
	}
      }
      if(varName[i]=="hadAk8jetPt" || varName[i]=="MET"){
        name1=varname;
	cr          = (TH1D*)f1->Get(varName2[i]);
	sr          = (TH1D*)f1->Get(varName1[i]);
	h_0_cr=(TH1D*)f_0->FindObjectAny(varName2[i]);
	h_1_cr=(TH1D*)f_1->FindObjectAny(varName2[i]);
	h_2_cr=(TH1D*)f_2->FindObjectAny(varName2[i]);
	h_3_cr=(TH1D*)f_3->FindObjectAny(varName2[i]);
	h_0_sr=(TH1D*)f_0->FindObjectAny(varName1[i]);
	h_1_sr=(TH1D*)f_1->FindObjectAny(varName1[i]);
	h_2_sr=(TH1D*)f_2->FindObjectAny(varName1[i]);
	h_3_sr=(TH1D*)f_3->FindObjectAny(varName1[i]);

	if(lep=="LE" )	ymin_=0.1, ymax_=1000;
	if(lep=="LL" )	ymin_=0.1, ymax_=10000;
	//	ymin_=1, ymax_=1000;
	int rebin;
	if(varName[i]=="hadAk8jetPt")
	  {
	    rebin=50;
	    nbin=2000/rebin, bin0=0, bin1=1000;
	    xmin_=0,xmax_=1000;
	  }
	else if(varName[i]=="MET")
	  {
	    rebin=5;
	    nbin=1000/rebin, bin0=0, bin1=2000;
	    xmin_=0,xmax_=1000;
	  }

	total = new TH1D("total","Total = fail_id+fail_iso+fail_accept+1e_cr",nbin,bin0,bin1);
	TF[i]= new TH1D("tf_SP_2","Transfer factor for SP : NJets x Nbtag & EW : wtag & htag",nbin,bin0,bin1);

	cr->Rebin(rebin);
	sr->Rebin(rebin);
	h_0_cr->Rebin(rebin);
	h_1_cr->Rebin(rebin);
	h_2_cr->Rebin(rebin);
	h_3_cr->Rebin(rebin);
	h_0_sr->Rebin(rebin);
	h_1_sr->Rebin(rebin);
	h_2_sr->Rebin(rebin);
	h_3_sr->Rebin(rebin);

      }
      if(varName[i]=="AllSBins_v6_CD"){
	cr          = (TH1D*)f1->Get("AllSBins_v6_CD_elec1");
	sr          = (TH1D*)f1->Get("AllSBins_v6_CD_elec0");
	nbin=8, bin0=1, bin1=9;
	xmin_=2,xmax_=9;
	total = new TH1D("total","Total = fail_id+fail_accept+1e_cr",nbin,bin0,bin1);
	TF[i]= new TH1D("tf","Transfer factor for NJets x Nbtag",nbin,bin0,bin1);
	
      }  
      if(varName[i]=="AllSBins_v6_CD_SP"){
	cr          = (TH1D*)f1->Get("AllSBins_v6_CD_SP_elec1");
	sr          = (TH1D*)f1->Get("AllSBins_v6_CD_SP_elec0");
	nbin=12, bin0=1, bin1=13;
	xmin_=1,xmax_=13;
	total = new TH1D("total","Total = fail_id+fail_accept+1e_cr",nbin,bin0,bin1);
	TF[i] = new TH1D("tf_SP","Transfer factor for SP : NJets x Nbtag & EW : NJets x Nbtag",nbin,bin0,bin1);

      }  

      /* cout<<"The CR content in bin"<<endl; */
      /* for(int j=bin0;j<=bin1;j++) */
      /* 	{ cout<<cr->GetBinContent(j)<<endl;} */
      /* cout<<"The SR content in bin"<<endl; */
      /* for(int j=bin0;j<=bin1;j++) */
      /* 	{ cout<<sr->GetBinContent(j)<<endl;} */
      /* cout<<"==============="<<endl; */
      
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

      TPad *pad1 = new TPad("pad1","pad1",0,0.6,1,0.9);
      //  pad1->SetBottomMargin(0);
      TPad *pad2 = new TPad("pad2","pad2",0,0.3,1,0.6);
      TPad *pad3 = new TPad("pad3","pad3",0,0,1,0.3);
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
      //      sr->SetLineColor(0);

      sr->Draw();
      h_0_sr->GetXaxis()->SetRangeUser(xmin_,xmax_);
      h_1_sr->GetXaxis()->SetRangeUser(xmin_,xmax_);
      h_2_sr->GetXaxis()->SetRangeUser(xmin_,xmax_);
      h_3_sr->GetXaxis()->SetRangeUser(xmin_,xmax_);
      decorate(h_0_sr,0,f_0->GetName());
      decorate(h_1_sr,1,f_1->GetName());
      decorate(h_2_sr,2,f_2->GetName());
      decorate(h_3_sr,3,f_3->GetName());
      hs_var->Add(h_0_sr);
      hs_var->Add(h_1_sr);
      hs_var->Add(h_2_sr);
      hs_var->Add(h_3_sr);
      hs_var->Draw("hist");
      hs_var->GetYaxis()->SetLabelSize(0.10);
      hs_var->SetTitle(0);

      hs_var->GetXaxis()->SetLimits(xmin_,xmax_);
      hs_var->SetMinimum(ymin_);
      hs_var->SetMaximum(ymax_);

      if(varName[i]=="AllSBins_v7_CD_SP"){
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
	//	TLine *line12V6=new TLine( 12,0,  12,ymax_);

        pad1->cd(); pad1->SetGridx(0); pad1->SetGridy(0);
        line1V6->Draw();      line2V6->Draw();  line3V6->Draw();
        line4V6->Draw();      line5V6->Draw(); line6V6->Draw();
        line7V6->Draw(); line8V6->Draw();
        line9V6->Draw(); line10V6->Draw();
        line11V6->Draw();// line12V6->Draw();

        TArrow *arrow1 = new TArrow( 1,ymax_/10, 9,ymax_/10,0.01,"<|>");
        TArrow *arrow2 = new TArrow( 9,ymax_/10, 11,ymax_/10,0.01,"<|>");

        arrow1->Draw(); arrow2->Draw();
	TLatex Tl,T2;
        Tl.SetTextSize(0.08);
        T2.SetTextSize(0.08);
        Tl.DrawLatex(1.25,2*ymax_/10,"N^{ 0}_{ 2}");
        Tl.DrawLatex(2.25,2*ymax_/10,"N^{ 0}_{ 3}");
        Tl.DrawLatex(3.25,2*ymax_/10,"N^{ 0}_{ 4}");
        Tl.DrawLatex(4.25,2*ymax_/10,"N^{ 0}_{ 5-6}");
        Tl.DrawLatex(5.25,2*ymax_/10,"N^{ 0}_{ #geq7}");
        Tl.DrawLatex(6.25,2*ymax_/10,"N^{ #geq1}_{ 2-4}");
        Tl.DrawLatex(7.25,2*ymax_/10,"N^{ #geq1}_{ 5-6}");
        Tl.DrawLatex(8.25,2*ymax_/10,"N^{ #geq1}_{ #geq7}");
        Tl.DrawLatex(9.25,2,"W tag");
        Tl.DrawLatex(10.25,2,"H tag");
        T2.DrawLatex(4.5,ymax_/20,"SP region");
        T2.DrawLatex(9.5,ymax_/20,"EW region");

      }
      if(varName[i]=="AllSBins_v7_CD_SP_tmp"){

	TLine *line1V6=new TLine( 1,0,  1,100);
	TLine *line2V6=new TLine( 2,0,  2,100);
	TLine *line3V6=new TLine( 3,0,  3,100);
	TLine *line4V6=new TLine( 4,0,  4,1000);
	TLine *line5V6=new TLine( 5,0,  5,100);
	TLine *line6V6=new TLine( 6,0,  6,100);
	TLine *line7V6=new TLine( 7,0,  7,100);
	TLine *line8V6=new TLine( 8,0,  8,1000);
	TLine *line9V6=new TLine( 9,0,  9,100);
	TLine *line10V6=new TLine( 10,0,  10,100);
	TLine *line11V6=new TLine( 11,0,  11,100);
	TLine *line12V6=new TLine( 12,0,  12,1000);
	TLine *line13V6=new TLine( 13,0,  13,100);
	TLine *line14V6=new TLine( 14,0,  14,100);
	TLine *line15V6=new TLine( 15,0,  15,100);
	TLine *line16V6=new TLine( 16,0,  16,1000);
	TLine *line17V6=new TLine( 17,0,  17,100);
 	TLine *line18V6=new TLine( 18,0,  18,100);
 	TLine *line19V6=new TLine( 19,0,  19,1000);
   
	pad1->cd(); pad1->SetGridx(0); pad1->SetGridy(0);
	//	pad2->cd(); pad2->SetGridx(0); pad2->SetGridy(0);
	line1V6->Draw();      line2V6->Draw();  line3V6->Draw();
	line4V6->Draw();      line5V6->Draw(); line6V6->Draw();
	line7V6->Draw(); line8V6->Draw();
	line9V6->Draw(); line10V6->Draw();
	line11V6->Draw(); line15V6->Draw();
	line12V6->Draw(); line16V6->Draw();
	line13V6->Draw(); line17V6->Draw();
	line14V6->Draw(); line18V6->Draw();
	line19V6->Draw();
	
	TLatex Tl,T2;
	Tl.SetTextSize(0.1);
	Tl.DrawLatex(1.75,612,"2 #leq N_{jets} #leq 3");	
	Tl.DrawLatex(2.25,300,"N_{b-jet}");
	Tl.DrawLatex(1.25,175,"0");
	Tl.DrawLatex(2.25,175,"1");
	Tl.DrawLatex(3.25,175,"#geq 2");

	Tl.DrawLatex(4.75,612,"4 #leq N_{jets} #leq 5");	
	Tl.DrawLatex(5.25,300,"N_{b-jet}");
	Tl.DrawLatex(4.25,175,"0");
	Tl.DrawLatex(5.25,175,"1");
	Tl.DrawLatex(6.25,175,"2");
	Tl.DrawLatex(7.25,175,"#geq 3");

	Tl.DrawLatex(8.75,612,"6 #leq N_{jets} #leq 7");	
	Tl.DrawLatex(12.75,612,"8 #leq N_{jets} #leq 9");	
	Tl.DrawLatex(16.75,612,"N_{jets} #geq 10");	
	
      }

      
      if(varName[i]=="AllSBins_v6_CD_EW_50bin"  ){
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
	Tl.SetTextSize(0.08);
	Tl.DrawLatex(2.5,2*yset_,"N^{ 0}_{ 2-4}");
	Tl.DrawLatex(9.0,2*yset_,"N^{ 0}_{ 5-6}");
	Tl.DrawLatex(15.0,2*yset_,"N^{ 0}_{ #geq7}");
	Tl.DrawLatex(21.0,2*yset_,"N^{ #geq1}_{ 2-4}");
	Tl.DrawLatex(26.0,2*yset_,"N^{ #geq1}_{ 5-6}");
	Tl.DrawLatex(32.0,2*yset_,"N^{ #geq1}_{ #geq7}");
	Tl.SetTextSize(0.08);
	Tl.DrawLatex(37.0,2*yset_,"EW : W tag");
	Tl.DrawLatex(44.0,2*yset_,"EW : H tag");
      }


      if(ExpvsPred)   legend->SetHeader("Expected","C"); 
      else if(SRvsCR) legend->SetHeader("Lost lepton","C"); 
      legend->AddEntry(h_0_sr,"t #bar{t} + #gamma","f");
      legend->AddEntry(h_1_sr,"t #bar{t}","f");
      legend->AddEntry(h_2_sr,"W(l#nu) + jets","f");
      legend->AddEntry(h_3_sr,"W(l#nu) + #gamma","f");
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
      cr->SetLineColor(0);
      cr->Draw("hist");
      h_0_cr->GetXaxis()->SetRangeUser(xmin_,xmax_);
      h_1_cr->GetXaxis()->SetRangeUser(xmin_,xmax_); 
      h_2_cr->GetXaxis()->SetRangeUser(xmin_,xmax_);
      h_3_cr->GetXaxis()->SetRangeUser(xmin_,xmax_);

      decorate(h_0_cr,0,f_0->GetName());
      decorate(h_1_cr,1,f_1->GetName());
      decorate(h_2_cr,2,f_2->GetName());
      decorate(h_3_cr,3,f_3->GetName());
      hs_var_cr->Add(h_0_cr);
      hs_var_cr->Add(h_1_cr);
      hs_var_cr->Add(h_2_cr);
      hs_var_cr->Add(h_3_cr);
      hs_var_cr->Draw("hist");
      hs_var_cr->GetYaxis()->SetLabelSize(0.10);
      hs_var_cr->SetTitle("Events");
      hs_var_cr->GetXaxis()->SetLimits(xmin_,xmax_);

      hs_var_cr->SetMinimum(ymin_);
      hs_var_cr->SetMaximum(ymax_);

      if(varName[i]=="AllSBins_v7_CD_SP"){
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
	//	TLine *line12V6=new TLine( 12,0,  12,ymax_);

        pad2->cd(); pad2->SetGridx(0); pad2->SetGridy(0);
        line1V6->Draw();      line2V6->Draw();  line3V6->Draw();
        line4V6->Draw();      line5V6->Draw(); line6V6->Draw();
        line7V6->Draw(); line8V6->Draw();
        line9V6->Draw(); line10V6->Draw();
        line11V6->Draw();// line12V6->Draw();
      }
      if(varName[i]=="AllSBins_v7_CD_SP_tmp"){

	TLine *line1V6=new TLine( 1,0,  1,100);
	TLine *line2V6=new TLine( 2,0,  2,100);
	TLine *line3V6=new TLine( 3,0,  3,100);
	TLine *line4V6=new TLine( 4,0,  4,1000);
	TLine *line5V6=new TLine( 5,0,  5,100);
	TLine *line6V6=new TLine( 6,0,  6,100);
	TLine *line7V6=new TLine( 7,0,  7,100);
	TLine *line8V6=new TLine( 8,0,  8,1000);
	TLine *line9V6=new TLine( 9,0,  9,100);
	TLine *line10V6=new TLine( 10,0,  10,100);
	TLine *line11V6=new TLine( 11,0,  11,100);
	TLine *line12V6=new TLine( 12,0,  12,1000);
	TLine *line13V6=new TLine( 13,0,  13,100);
	TLine *line14V6=new TLine( 14,0,  14,100);
	TLine *line15V6=new TLine( 15,0,  15,100);
	TLine *line16V6=new TLine( 16,0,  16,1000);
	TLine *line17V6=new TLine( 17,0,  17,100);
 	TLine *line18V6=new TLine( 18,0,  18,100);
 	TLine *line19V6=new TLine( 19,0,  19,1000);
   
	//	pad1->cd(); pad1->SetGridx(0); pad1->SetGridy(0);
       	pad2->cd(); pad2->SetGridx(0); pad2->SetGridy(0);
	line1V6->Draw();      line2V6->Draw();  line3V6->Draw();
	line4V6->Draw();      line5V6->Draw(); line6V6->Draw();
	line7V6->Draw(); line8V6->Draw();
	line9V6->Draw(); line10V6->Draw();
	line11V6->Draw(); line15V6->Draw();
	line12V6->Draw(); line16V6->Draw();
	line13V6->Draw(); line17V6->Draw();
	line14V6->Draw(); line18V6->Draw();
	line19V6->Draw();
		
      }
      if(varName[i]=="AllSBins_v6_CD_EW_50bin"  ){
	TLine *line1V6=new TLine( 6.5,ymin_,  6.5,ymax_);
	TLine *line2V6=new TLine(12.5,ymin_, 12.5,ymax_);
	TLine *line3V6=new TLine(18.5,ymin_, 18.5,ymax_);
	TLine *line4V6=new TLine(24.5,ymin_, 24.5,ymax_);
	TLine *line5V6=new TLine(30.5,ymin_, 30.5,ymax_);
	TLine *line6V6=new TLine(36.5,ymin_, 36.5,ymax_);
	TLine *line7V6=new TLine(43.5,ymin_, 43.5,ymax_);

	pad2->cd(); pad2->SetGridx(0); pad2->SetGridy(0);
	
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
	Tl.SetTextSize(0.08);
	Tl.DrawLatex(2.5,2*yset_,"N^{ 0}_{ 2-4}");
	Tl.DrawLatex(9.0,2*yset_,"N^{ 0}_{ 5-6}");
	Tl.DrawLatex(15.0,2*yset_,"N^{ 0}_{ #geq7}");
	Tl.DrawLatex(21.0,2*yset_,"N^{ #geq1}_{ 2-4}");
	Tl.DrawLatex(26.0,2*yset_,"N^{ #geq1}_{ 5-6}");
	Tl.DrawLatex(32.0,2*yset_,"N^{ #geq1}_{ #geq7}");
	Tl.SetTextSize(0.08);
	Tl.DrawLatex(37.0,2*yset_,"EW : W tag");
	Tl.DrawLatex(44.0,2*yset_,"EW : H tag");
      }
      if(SRvsCR)  legend1->SetHeader("Single lepton","C"); 
      else if(ExpvsPred) legend1->SetHeader("Predicted","C"); 
      legend1->AddEntry(h_0_cr,"t #bar{t} + #gamma","f");
      legend1->AddEntry(h_1_cr,"t #bar{t}","f");
      legend1->AddEntry(h_2_cr,"W(l#nu) + jets","f");
      legend1->AddEntry(h_3_cr,"W(l#nu) + #gamma","f");
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
	  TF[i]->GetYaxis()->SetRangeUser(0,2.0);
	  line= new TLine(xmin_,1,xmax_,1);
	}
      else if(SRvsCR)
	{
	  if(lep=="LE")
	    {
	      TF[i]->GetYaxis()->SetRangeUser(0,1.0);
	      line= new TLine(xmin_,0.5,xmax_,0.5);
	    }
	  else if (lep=="LM" || lep=="LL")
	    {
	      TF[i]->GetYaxis()->SetRangeUser(0,2.0);
	      line= new TLine(xmin_,1.0,xmax_,1.0);
	    }
	}
	  
      //TF[i]->GetYaxis()->SetLabelSize(0.17);
       
      //      fout->cd();
  
      TF[i]->GetXaxis()->SetTitle(name1);
      TF[i]->GetXaxis()->SetLabelSize(0.14);
      TF[i]->GetXaxis()->SetTitleOffset(0.8);
      TF[i]->GetXaxis()->SetTitleSize(0.16);

      
      if(SRvsCR) TF[i]->GetYaxis()->SetTitle("SR/CR");
      else if(ExpvsPred) TF[i]->GetYaxis()->SetTitle("Exp/Pred");
      TF[i]->GetYaxis()->SetLabelSize(0.14);
      TF[i]->SetLineWidth(3);
      TF[i]->GetYaxis()->SetTitleOffset(0.30);
      TF[i]->GetYaxis()->SetTitleSize(0.15);
 
      line->SetLineColor(1);
      line->SetLineStyle(1);
      line->SetLineWidth(1);
      line->Draw();

      cout<<"The TF content in bin"<<endl;
      /* cout<<"The SR content in bin"<<endl; */
      for(int j=bin0;j<=bin1;j++)
      	{ cout<<TF[i]->GetBinContent(j)<<endl;}
      /* cout<<"==============="<<endl; */
      if(varName[i]=="METvBin2")
	for(int j=bin0;j<=METLowEdge_v2.size()-1;j++)
	  { cout<<TF[i]->GetBinContent(j)<<endl;}


      if(varName[i]=="AllSBins_v7_CD_SP_tmp"){
      	TF[i]->SetTitle(0);
      	TF[i]->GetXaxis()->SetTitleOffset(0.9);
      	TF[i]->GetXaxis()->SetTitle("Bin no.");
      	TF[i]->GetXaxis()->SetTitleSize(0.17);

      	TLine *line1V6=new TLine( 1,0,  1,100);
      	TLine *line2V6=new TLine( 2,0,  2,100);
      	TLine *line3V6=new TLine( 3,0,  3,100);
      	TLine *line4V6=new TLine( 4,0,  4,1000);
      	TLine *line5V6=new TLine( 5,0,  5,100);
      	TLine *line6V6=new TLine( 6,0,  6,100);
      	TLine *line7V6=new TLine( 7,0,  7,100);
      	TLine *line8V6=new TLine( 8,0,  8,1000);
      	TLine *line9V6=new TLine( 9,0,  9,100);
      	TLine *line10V6=new TLine( 10,0,  10,100);
      	TLine *line11V6=new TLine( 11,0,  11,100);
      	TLine *line12V6=new TLine( 12,0,  12,1000);
      	TLine *line13V6=new TLine( 13,0,  13,100);
      	TLine *line14V6=new TLine( 14,0,  14,100);
      	TLine *line15V6=new TLine( 15,0,  15,100);
      	TLine *line16V6=new TLine( 16,0,  16,1000);
      	TLine *line17V6=new TLine( 17,0,  17,100);
      	TLine *line18V6=new TLine( 18,0,  18,100);
      	TLine *line19V6=new TLine( 19,0,  19,1000);
   
      	//	pad1->cd(); pad1->SetGridx(0); pad1->SetGridy(0);
       	pad3->cd(); pad3->SetGridx(0);
      	line1V6->Draw();      line2V6->Draw();  line3V6->Draw();
      	line4V6->Draw();      line5V6->Draw(); line6V6->Draw();
      	line7V6->Draw(); line8V6->Draw();
      	line9V6->Draw(); line10V6->Draw();
      	line11V6->Draw(); line15V6->Draw();
      	line12V6->Draw(); line16V6->Draw();
      	line13V6->Draw(); line17V6->Draw();
      	line14V6->Draw(); line18V6->Draw();
      	line19V6->Draw();
		
      }

      if(varName[i]=="AllSBins_v6_CD_EW_50bin"  ){
      	TF[i]->SetTitle(0);
      	TF[i]->GetXaxis()->SetTitleOffset(0.9);
      	TF[i]->GetXaxis()->SetTitle("Bin no.");
      	TF[i]->GetXaxis()->SetTitleSize(0.17);
      	TLine *line1V6=new TLine( 6.5,0,  6.5,ymax_);
      	TLine *line2V6=new TLine(12.5,0, 12.5,ymax_);
      	TLine *line3V6=new TLine(18.5,0, 18.5,ymax_);
      	TLine *line4V6=new TLine(24.5,0, 24.5,ymax_);
      	TLine *line5V6=new TLine(30.5,0, 30.5,ymax_);
      	TLine *line6V6=new TLine(36.5,0, 36.5,ymax_);
      	TLine *line7V6=new TLine(43.5,0, 43.5,ymax_);

      	pad3->cd(); pad3->SetGridx(0);
	
      	line1V6->Draw();      line2V6->Draw();  line3V6->Draw();
      	line4V6->Draw();      line5V6->Draw();
      	line6V6->Draw();      line7V6->Draw();
      }

      if(SRvsCR) TF[i]->Write();
 
      
      c1[i]->SaveAs(pdf);
      c1[i]->SaveAs(png);

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
