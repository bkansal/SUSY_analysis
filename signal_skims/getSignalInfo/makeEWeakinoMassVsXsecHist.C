#include<iostream>
#include<iomanip>
#include<string>
#include"TROOT.h"
#include "TF1.h"
#include "TMath.h"
#include "TH1.h"

void makeEWeakinoMassVsXsecHist(){
  gStyle->SetOptStat(0);
  vector<double> mass,xsec_nn,absUnc_nn;
  ifstream infile("mEWeakino_N2N1Xsecfb.txt");
  string line;
  while (getline(infile, line)){
    std::istringstream iss(line);
    double mass1,xsec1,absUnc1;
    iss>>mass1;
    iss>>xsec1;
    iss>>absUnc1;

    mass.push_back(mass1);
    xsec_nn.push_back(xsec1);
    absUnc_nn.push_back(absUnc1);
  }
  TH1D *h1 = new TH1D("mEWeakino_N2N1Xsec","x:mass of EWeakion in GeV, bin content(y-axis) is N2N1 xsec in pb and bin error is xsec uncertainty in pb",3011,-0.5,3010.5);
  for(int i=0;i<mass.size();i++){
    h1->Fill(mass[i],xsec_nn[i]/1000.0);
    h1->SetBinError(h1->FindBin(mass[i]),absUnc_nn[i]/1000.0);
  }

  h1->GetXaxis()->SetTitle("EWeakino Mass(GeV)");
  h1->GetYaxis()->SetTitle("#sigma_{N2N1}(pb)");
  TFile *f1=new TFile("EWeakino_N2N1Xsec.root","recreate");
  h1->Write();


  if(1){
    int np=mass.size();
    if(np!=xsec_nn.size() || np!=absUnc_nn.size()){ cout<<"problem in getting mass and xsec"<<endl; return;}
    cout<<"mEWeakino"<<endl<<"{";
    for(int i=0;i<np;i++){
      cout<<mass[i]<<",";
    }
    cout<<endl<<"N2N1 xsec"<<endl<<"{";
    for(int i=0;i<np;i++){
      cout<<xsec_nn[i]<<",";
    }
    cout<<endl<<"N2N1 Uncxsec"<<endl<<"{";
    for(int i=0;i<np;i++){
      cout<<absUnc_nn[i]<<",";
    }
    cout<<endl;
  }
}
