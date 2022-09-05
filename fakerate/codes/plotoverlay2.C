///////// Overlay plot betwrrn tt jets & Wjets
void plotoverlay2(TString varname="Qmulti",TString year="full_Run2")
{
  TString fname[2];
  fname[0]="WJets_CR_v18.root";
  fname[1]="TTJets_CR_v18.root";
  gStyle->SetOptStat(0);
  TCanvas *  c1 = new TCanvas("stackhist","stackhist",1000,600);
  c1->SetLogy();
  TString path="rootout/fake_rate_v10_afterbtagSF_overlap/",path_[2];
  /*
  TString path1=path+fname[0];
  TString path2=path+fname[1];
  */
  TFile *f[2];
  /*
  f[0] = new TFile(path1);
  f[1] = new TFile(path2);
  */  
  TH1D *sr[2];
  vector<int> col={kRed,kBlue};
  TLegend *legend = new TLegend(0.45,0.7,0.9,0.9);
  legend->SetNColumns(1);
  legend->SetBorderSize(1);

  for(int i=0; i<2; i++)
    {
      path_[i]=path+fname[i];
      f[i] = new TFile(path_[i]);
      int rebin=1;
      sr[i]  = (TH1D*)f[i]->Get(varname);
      sr[i]->Scale(1/sr[i]->Integral());
      
      sr[i]->SetLineColor(col[i]);
      if(varname.Contains("Phi") || varname.Contains("Eta") ||varname.Contains("MET")) rebin=5;
      if(varname.Contains("Pt")) rebin=10;

      sr[i]->Rebin(rebin); 
      if(i==0) {
	sr[i]->Draw("hist");
        sr[i]->GetXaxis()->SetTitle(varname);
      }
      else sr[i]->Draw("hist sames");

      TString name;
      if(fname[i].Contains("TTJets")) name="t#bar{t}(l#nu)+jets"; 
      else if(fname[i].Contains("WJets")) name="W(l#nu)+jets";

      legend->AddEntry(sr[i],name,"lp");
    }
  legend->Draw();
}
