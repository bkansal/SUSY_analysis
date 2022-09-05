void plotsys_pred(TString signal="T5bbbbZg", int mGl = 2200 , int mNLSP =200, TString sys="scale",TString year="full_Run2",int xmin=1,int xmax=46)
{
  // gStyle->SetOptStat(0);
  gStyle->SetPalette(1);
  TLatex textOnTop,intLumiE;
  
  bool data_pred=false;
  TFile *f1, *f2,*f3;
  TString lep="LM";
  TString path1;
  TString path2;
  TString varname="AllSBins_v7_CD_SP";
  double ymin=0.5 , ymax=1.5, ymin_=0.0 , ymax_=2;
  TString sample="FastSim_"+signal+"_"+to_string(mGl)+"_"+to_string(mNLSP);
  if(sys=="scale")
    {
      path1=sample+"_noscale_v18.root";
      path2=sample+"_scale_v18.root";     
      
      varname="AllSBins_v7_CD_SP_scale";
    }
  else if(sys=="pdf")
    {
      path1=sample+"_noscale_v18.root";
      path2=sample+"_scale_v18.root";

     varname="AllSBins_v7_CD_SP_pdf";
    }


 TString pdf = signal+"_"+sys+".pdf";
 TString png = signal+"_"+sys+".png";

 TString filename,filename1,filename2;
  f2 = new TFile(path1);
  f3 = new TFile(path2);

  TH1D *cr,*sr,*tf,*pred_sr,*cr1,*sr1,*cr2,*sr2;
  TH2D *cr_,*sr_,*tf_,*pred_sr_,*cr1_,*sr1_,*cr2_,*sr2_;
  TCanvas *c1;
  double nbin,bin0=0, bin1=46,yset_;
  TH1D *total;
  int rebin=1;
  TString varname0=varname+"_elec0";
  gStyle->SetOptStat(0);
  
  if(sys == "scale" || sys == "pdf")
    {
      c1 = new TCanvas("stackhist","stackhist",800,600);
      c1->cd();
      sr1_          = (TH2D*)f2->Get(varname0);
      sr2_          = (TH2D*)f3->Get(varname0);
      sr1_->GetXaxis()->SetRangeUser(xmin,xmax);
      sr2_->GetXaxis()->SetRangeUser(xmin,xmax);
      if(sys=="scale") ymin=0,ymax=8;
      if(sys=="pdf") ymin=0,ymax=100;
      sr1_->GetYaxis()->SetRangeUser(ymin,ymax);
      sr2_->GetYaxis()->SetRangeUser(ymin,ymax+1);
      sr2_->Add(sr1_,-1);
      sr2_->Divide(sr1_);
      if(sys=="pdf") sr2_->GetYaxis()->SetTitle("PDF factor index");
      if(sys=="scale") sr2_->GetYaxis()->SetTitle("SCALE factor index");
      sr2_->SetMarkerSize(1.3);
      //      sr2_->GetZaxis()->SetRangeUser(-0.1,0.1);

      if(sys=="scale") sr2_->Draw("colz text");
      if(sys=="pdf") sr2_->Draw("colz");
      //cout<<"Scale = 1 - N(with scale unc.)/N(nominal value) : "<<abs(sr1_->GetMaximum())<<endl;
      cout<<"Max PDF uncertainty = 1 - N(with scale unc.)/N(nominal value) : "<<abs(sr2_->GetMaximum())<<endl;
      //      max->Fill(ext2,fr2->GetMaximum());                                                                                                                            

    }

}
