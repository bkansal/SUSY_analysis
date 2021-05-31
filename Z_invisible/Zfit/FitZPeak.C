#include "TF1.h"
#include "TH1.h"
#include "TMath.h"
//Gaussian                                                                                                                                                   
Double_t mygauss(Double_t * x, Double_t * par)
{
  Double_t arg = 0;
  if (par[2]<0) par[2]=-par[2];  // par[2]: sigma                                                                                                           
  if (par[2] != 0) arg = (x[0] - par[1])/par[2];  // par[1]: mean                                                                                           
  //return par[0]*BIN_SIZE*TMath::Exp(-0.5*arg*arg)/                                                                                                        
  //   (TMath::Sqrt(2*TMath::Pi())*par[2]);                                                                                                                
   return par[0]*TMath::Exp(-0.5*arg*arg)/
     (TMath::Sqrt(2*TMath::Pi())*par[2]); // par[0] is constant                                                                                             
}

//Breit-Wigner function                                                                                                                                     
Double_t mybw(Double_t* x, Double_t* par)
{
  Double_t arg1 = 14.0/22.0; // 2 over pi                                                                                                                  
  Double_t arg2 = par[1]*par[1]*par[2]*par[2]; //Gamma=par[1]  M=par[2]                                                                                     
  Double_t arg3 = ((x[0]*x[0]) - (par[2]*par[2]))*((x[0]*x[0]) - (par[2]*par[2]));
  Double_t arg4 = x[0]*x[0]*x[0]*x[0]*((par[1]*par[1])/(par[2]*par[2]));
  return par[0]*arg1*arg2/(arg3 + arg4);
}


void FitZPeak(){
  //  gROOT->LoadMacro("BW.C");
  gStyle->SetOptFit(111111);

  TString path="../rootoutput/withphicut_zmass60to120_btagSF_tmp/";
  TString filename= path+"TTG_CR_v18.root";
  TString filename1= path+"ZJZGToLL_CR_v18.root";
  TString filename2= path+"Run2_METdata_CR_v18.root";
  TString varName="invMass";
 TFile *f=new TFile(filename2);

 /* TH1D *Z_mass=new TH1D("invMass","invariant mass from e- & e+",2000,0,500); */
 /*  Z_mass=(TH1D*)invMass->Clone(); */
  TH1D *Z_mass=(TH1D*)f->FindObjectAny(varName);

  int   division = Z_mass->GetNbinsX();
 /* float massMIN = Z_mass->GetBinLowEdge(0); */
  float massMIN = Z_mass->GetBinLowEdge(1);
  float massMAX = Z_mass->GetBinLowEdge(division+1);

 /* float massMAX = Z_mass->GetBinLowEdge(150); */
 float BIN_SIZE = Z_mass->GetBinWidth(1);

////////////////
//For Gaussian//
///////////////

//TF1 *func = new TF1("mygauss",mygauss,massMIN, massMAX,3);
/* TF1 *func = new TF1("mygauss",mygauss,10, 150,3); */
/* /\* func->SetParameter(0,1.0);   func->SetParName(0,"const"); *\/ */
/* /\* func->SetParameter(2,5.0);   func->SetParName(2,"sigma"); *\/ */
/* /\* func->SetParameter(1,95.0);     func->SetParName(1,"mean"); *\/ */
/* // func->SetParameters(1,2,200);  */
/*  func->SetParameters(5,90,500);  */

/* Z_mass->Fit("mygauss","QR"); */
/* TF1 *fit = Z_mass->GetFunction("mygauss"); */

/////////////////////
// For Breit-Wigner//
////////////////////

//TF1 *func = new TF1("mybw",mybw,massMIN, massMAX,3);
TF1 *func = new TF1("mybw",mybw,10, 150,3);
/* func->SetParameter(0,1.0);   func->SetParName(0,"const"); */
/* func->SetParameter(2,5.0);     func->SetParName(1,"sigma"); */
/* func->SetParameter(1,95.0);    func->SetParName(2,"mean"); */
// func->SetParameters(5,90,500); 
func->SetParameters(1,2,100);  
Z_mass->Fit("mybw","QR");
TF1 *fit = Z_mass->GetFunction("mybw");




  fit->SetLineColor(2);
  fit->SetLineWidth(3);

 /* Z_mass->SetMarkerStyle(20); */
 /* Z_mass->SetMarkerSize(1.0); */
 /* Z_mass->SetMarkerColor(2); */
 Z_mass->SetLineWidth(2.0);
 Z_mass->SetXTitle("Z Mass (in GeV/c^{2})"); 
// Z_mass->GetXaxis()->SetTitleOffset(1.0);
 Z_mass->GetXaxis()->SetRangeUser(10,150);


Z_mass->Draw("PE0");
 // c1->Print("myZmass_BWfitted.eps");
 // c1->Print ("myZmass_Gausfitted.eps");
}
