#include"TH3.h"
#include"TH2.h"
#include"TH1.h"


void plotoverlay1D(TString signal="T5bbbbZg", int mGl = 2200 , int mNLSP =200, TString sys="SclWt",TString year="full_Run2")
{
  TLatex textOnTop,intLumiE;
  TFile *f1, *f2,*f3;
  double ymin_=0 , ymax_=2;
  int ymin=0.0 , ymax=1;
  TString sample="FastSim_"+signal+"_"+to_string(mGl)+"_"+to_string(mNLSP);
  TString path1=sample+"_noscale_v18.root";
  TString path2=sample+"_scale_v18.root";
  TString varname="SclWt";
  if(sys=="pdf") varname="PDFWt"; 
  TString filename,filename1,filename2;
  TString pdf,png;
  f1 = new TFile(path1);
  f2 = new TFile(path2);
  TH2D *cr_,*sr_,*cr1_,*sr1_,*cr2_,*sr2_;
  TCanvas *c1;
  gStyle->SetOptStat(0);
  c1 = new TCanvas("stackhist","stackhist",800,600);
  c1->cd();
  c1->SetGridx();

  sr1_          = (TH2D*)f1->Get(varname);
  sr2_          = (TH2D*)f2->Get(varname);
  //  sr2_->Add(sr1_,-1);
  sr2_->Divide(sr1_);
  sr2_->Print("all");
  sr2_->Draw();
}
