//root -l 'plotsys(2300,1000,"btagSF","FastSim_T5bbbbZg")'
void plotsys(int mGl,int mNLSP,TString sys,TString signal)
{
  gStyle->SetOptStat(0);

  TFile *f1, *f2,*f3, *fout;
  TString path1;
  TString path2;
  TString rootout;
  TString sample="FastSim_"+signal+"_"+to_string(mGl)+"_"+to_string(mNLSP);
  int xmin=1;
  int xmax=5;
  if(sys=="btagSF"){
    path1=sample+"_v18.root";
    path2=sample+"_up_v18.root";                                                                                                                                                                  
    rootout=sample+"_btagsys.root";
  }
  else if(sys=="JECup"){
    path1=sample+"_v18.root";
    path2=sample+"_JECup_v18.root";
    rootout=sample+"_JECsys.root";
  }
  else if(sys=="JERup"){
    path1=sample+"_v18.root";
    path2=sample+"_JERup_v18.root";
    rootout=sample+"_JERsys.root";
  }


  TString varName="AllSBins_v6_CD_EW_50bin_elec1_closure"; xmin=0,xmax=46;
  TH1D *sr1, *sr2;
  f1 = new TFile(path1);
  f2 = new TFile(path2);

  sr1          = (TH1D*)f1->Get(varName);
  sr2          = (TH1D*)f2->Get(varName);
  //   sr1->Print("all");
  //   sr2->Print("all");

  TH1D *h3 = (TH1D*)sr1->Clone("h3");
  TH1D *h4 = (TH1D*)sr2->Clone("h4");
  h3->Add(h4,-1);
  h3->Divide(sr1);
  TH1D *h5 = (TH1D*)h3->Clone("h5");
  /*
  for(int i=0; i<=46; i++){
    if(sr1->GetBinContent(i)!=0) h3->SetBinContent(i,h3->GetBinContent(i)/sr1->GetBinContent(i));
    else h3->SetBinContent(i,0);
  }
  */
  fout =new TFile(rootout,"recreate");
  fout->cd();
  if(sys=="btagSF") h3->Write("btagsys");
  if(sys=="JECup") h3->Write("JECsys");
  if(sys=="JERup") h3->Write("JERsys");
  h5->Write("diff");
}

void plotsys(TString sys,TString signal)
{
  TString sys_;
  gStyle->SetOptStat(0);

  TCanvas *c1 = new TCanvas("stackhist","stackhist",1000,600);   

  int mGl, mNLSP3,  mNLSP1,  mNLSP2;
  if(signal=="T5bbbbZg") {
    mGl=2200,mNLSP1=200;
    mGl=2200,mNLSP2=1000;
    mGl=2200,mNLSP3=2100;  
  }
  else if(signal=="TChiWG") {
    mGl=0,mNLSP1=800;
    mGl=0,mNLSP2=1000;
    mGl=0,mNLSP3=1200;
  }
  else if(signal=="T5qqqqHg") {
    mGl=2200,mNLSP1=200;
    mGl=2200,mNLSP2=1000;
    mGl=2200,mNLSP3=2100;
  }
  else if(signal=="T5ttttZg") {
    mGl=2000,mNLSP1=200;
    mGl=2000,mNLSP2=1000;
    mGl=2000,mNLSP3=1775;
  }
  else if(signal=="T6ttZg") {
    mGl=1200,mNLSP1=200;
    mGl=1200,mNLSP2=600;
    mGl=1200,mNLSP3=1100;
  }
  else if(signal=="TChiNG") {
    mGl=0,mNLSP1=800;
    mGl=0,mNLSP2=1000;
    mGl=0,mNLSP3=1200;
  }

  TString path1="sys/FastSim_"+signal+"_"+to_string(mGl)+"_"+to_string(mNLSP1)+"_"+sys+".root";
  TString path2="sys/FastSim_"+signal+"_"+to_string(mGl)+"_"+to_string(mNLSP2)+"_"+sys+".root";
  TString path3="sys/FastSim_"+signal+"_"+to_string(mGl)+"_"+to_string(mNLSP3)+"_"+sys+".root";

  TFile  *f1 = new TFile(path1);
  TFile  *f2 = new TFile(path2);
  TFile  *f3 = new TFile(path3);
  TH1D *sr1,*sr2,*sr3,*nominal1,*nominal2,*nominal3,*sys1,*sys2,*sys3;
  TString name=sys, name1="nominal", name2="sys";

  //  TCanvas *c1 = new TCanvas("stackhist","stackhist",1000,600);
  // c1->cd();

  sr1          = (TH1D*)f1->Get(name);
  sr2          = (TH1D*)f2->Get(name);
  sr3          = (TH1D*)f3->Get(name);
  nominal1= (TH1D*)f1->Get(name1);
  nominal2= (TH1D*)f2->Get(name1);
  nominal3= (TH1D*)f3->Get(name1);
  sys1= (TH1D*)f1->Get(name2);
  sys2= (TH1D*)f2->Get(name2);
  sys3= (TH1D*)f3->Get(name2);
  /*
  for(int i=2;i<=46;i++)
    {
      cout<<i-1<<" : "<<sr1->GetBinContent(i)<<" : "<<sr2->GetBinContent(i)<<" : "<<sr3->GetBinContent(i)<<endl;

    }
  */
  cout<<"lower"<<endl;
  for(int i=2;i<=46;i++)
      cout<<sr1->GetBinContent(i)<<endl;
  cout<<"middle"<<endl;
  for(int i=2;i<=46;i++)
      cout<<sr2->GetBinContent(i)<<endl;
  cout<<"higher"<<endl;
  for(int i=2;i<=46;i++)
      cout<<sr3->GetBinContent(i)<<endl;

  cout<<nominal1->Integral()<<" : "<<nominal2->Integral()<<" : "<<nominal3->Integral()<<endl;
  cout<<sys1->Integral()<<" : "<<sys2->Integral()<<" : "<<sys3->Integral()<<endl;
  cout<<1-(sys1->Integral()/nominal1->Integral())<<" : "<<1-(sys2->Integral()/nominal2->Integral())<<" : "<<1-(sys3->Integral()/nominal3->Integral())<<endl;
  sr1->GetYaxis()->SetRangeUser(-1,1);
  sr1->GetYaxis()->SetTitle("#frac{N(up)-N(nom.)}{N(nom.)}");
  sr1->GetXaxis()->SetRangeUser(1,46);
  sr1->GetXaxis()->SetTitle("Bin no.");
  if(sys=="L1sys") {sys_="Prefiring Weight"; sr1->GetYaxis()->SetRangeUser(-0.04,0.04);}
  else if(sys=="btagsys") {sys_="b-Tag efficiency"; sr1->GetYaxis()->SetRangeUser(-0.4,0.4);}
  else if(sys=="PUsys") {sys_="Pileup reweight"; sr1->GetYaxis()->SetRangeUser(-0.4,0.4);}
  else if(sys=="ISRsys") {sys_="ISR reweight"; sr1->GetYaxis()->SetRangeUser(-0.8,0.8);}

  TH1D *nominal_ = (TH1D*)nominal3->Clone("nominal_");
  for(int i=1; i<=46;i++)
    {
      nominal_->SetBinError(i,(nominal3->GetBinError(i)/nominal3->GetBinContent(i)));
      nominal_->SetBinContent(i,0);
    }
  nominal_->SetFillStyle(3009);
  nominal_->SetFillColor(kGray);
  nominal_->Draw("E2");
  sr1->SetMarkerColor(1);
  sr1->SetLineColor(1);
  sr1->Draw("hist");
  sr2->SetMarkerColor(2);
  sr2->SetLineColor(2);
  sr2->Draw("hist same");
  sr3->SetMarkerColor(3);
  sr3->SetLineColor(3);
  sr3->Draw("hist same");
  nominal_->Draw("E2 same");
  TLegend *legend = new TLegend(0.5,0.78,0.9,0.9);
  legend->SetNColumns(1);
  legend->SetBorderSize(1);
  TString title= signal + " : " +sys_;
  legend->SetHeader(title,"C");
  legend->Draw();

  TLegend *legend1 = new TLegend(0.1,0.78,0.45,0.9);
  legend1->SetNColumns(1);
  legend1->SetBorderSize(1);
  if(signal=="T5bbbbZg" || signal=="T5qqqqHg"){
    legend1->AddEntry(sr1,"M(#tilde{g})=2200 GeV , M(#chi^{0}_{1})=200 GeV","l");
    legend1->AddEntry(sr2,"M(#tilde{g})=2200 GeV , M(#chi^{0}_{1})=1000 GeV","l");
    legend1->AddEntry(sr3,"M(#tilde{g})=2200 GeV , M(#chi^{0}_{1})=2100 GeV","l");
  }
  if(signal=="TChiWG" || signal=="TChiNG")
    {
      legend1->AddEntry(sr1,"M(#chi^{0/#pm}_{1}) = 800 GeV","l");
      legend1->AddEntry(sr2,"M(#chi^{0/#pm}_{1}) = 1000 GeV","l");
      legend1->AddEntry(sr3,"M(#chi^{0/#pm}_{1}) = 1200 GeV","l");
    }
  if(signal=="T5ttttZg")
    {
      legend1->AddEntry(sr1,"M(#tilde{g})=2000 GeV , M(#chi^{0}_{1})=200 GeV","l");
      legend1->AddEntry(sr2,"M(#tilde{g})=2000 GeV , M(#chi^{0}_{1})=1000 GeV","l");
      legend1->AddEntry(sr3,"M(#tilde{g})=2000 GeV , M(#chi^{0}_{1})=1775 GeV","l");
    }

    legend1->Draw();
    TString name_="plots/"+signal+"/"+signal+"_"+sys+".pdf";
    c1->SaveAs(name_);
    //    name_="plots/"+signal+"_"+sys+".gif";
    //c1->SaveAs(name_);
    name_="plots/"+signal+"/"+signal+"_"+sys+".png";
    c1->SaveAs(name_);
}
