#include<stdio.h>
//#include<iostream.h>
#include<iostream>
void tmp()
{
  // int r[1000][1000];
  // printf("ROWS\n");
  // FILE *f2=fopen("mEWeakino_N2C1Xsecfb_absUnc_C1C1Xsecfb_absUnc.txt" , "r");
  // for(int i=0;i<100;i++)
  //   {
  //     for(int k=0;k<1;k++)
  // 	{
  // 	  fscanf(f2,"%d", &r[k][i]);
  // 	  printf("r[%d][%d]=%d\t",k,i,r[k][i]);
  // 	  //r[k]=c[i][k];
  // 	}
  //     cout<<endl;
  //   }

  gStyle->SetOptStat(0);
  vector<double> mass,xsec,pcUnc,absUnc;
  //  ifstream infile("mGl_Xsecpb_pcUnc_absUnc.txt");
  ifstream infile("mEWeakino_N2C1Xsecfb_absUnc_C1C1Xsecfb_absUnc.txtt");
  string line;
  while (getline(infile, line)){
    std::istringstream iss(line);
    double mass1,xsec1,pcUnc1,absUnc1;
    iss>>mass1;
    iss>>xsec1;
    iss>>pcUnc1;
    iss>>absUnc1;
    mass.push_back(mass1);
    xsec.push_back(xsec1);
    pcUnc.push_back(pcUnc1);
    absUnc.push_back(absUnc1);
  }
  // TH1D *h1 ;//= new TH1D("mGlXsec","x:mass of gluino in GeV, bin content(y-axis) is xsec in pb and bin error is xsec uncertainty in pb",301\  1,-0.5,3010.5);                                                                                                                               
// TFile *f1 = new TFile("T5bbbbZg_MassScan.root","recreate");                                                                               
TFile *f1 = TFile::Open("T5bbbbZg_MassScan.root");
TH1D *h1 = (TH1D*)f1->FindObjectAny("mGlXsec");
for(int i=0;i<mass.size();i++){
  h1->Fill(mass[i],xsec[i]);
  h1->SetBinError(h1->FindBin(mass[i]),absUnc[i]);
  cout<<mass[i]<<"    "<<xsec[i]<<endl;
 }

h1->GetXaxis()->SetTitle("Gluino Mass(GeV)");
h1->GetYaxis()->SetTitle("#sigma(pb)");
h1->Draw();




}
