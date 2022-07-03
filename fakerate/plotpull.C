void plotpull(TString bkg="LL")
{
  TString varname="AllSBins_v6_CD_EW_50bin";
  TString fname[2];
  fname[0]="TTWGJ_CR_v18.root";
  fname[1]="TTJets_CR_v18.root";
  //  gStyle->SetOptStat(0);
  TCanvas *  c1 = new TCanvas("stackhist","stackhist",1000,600);
  //  c1->SetLogy();
  TString path,path_[2];
  TString name="Pull for LL closure";
  TString varname1=varname+"_elec0";
  TString varname2=varname+"_elec1_closure";

  if(bkg=="FR")path="rootout/fake_rate_v10_afterbtagSF_overlap/", name="Pull for FR closure";
  else if(bkg=="LL") path="../lostlepton/rootoutput/new/nominal/LL/";
  else if(bkg=="QCD") {
    path="../multijet/rootoutput/final/RK_MCclosure/", fname[0]="GJetsQCD_new_v18.root", name="Pull for QCD closure";
    varname1=varname+"_AB";varname2=varname+"_CD";
  }
  TFile *f[2];

  TH1D *sr[2],*pred_sr[2];
  vector<int> col={kRed,kBlue};
  TLegend *legend = new TLegend(0.45,0.7,0.9,0.9);
  legend->SetNColumns(1);
  legend->SetBorderSize(1);
  

  for(int i=0; i<1; i++)
    {
      path_[i]=path+fname[i];
      f[i] = new TFile(path_[i]);
      int rebin=1;
      sr[i]  = (TH1D*)f[i]->Get(varname1);
      pred_sr[i] = (TH1D*)f[i]->Get(varname2);
      sr[i]->SetLineColor(col[i]);
      /*
      sr[i]->Rebin(rebin); 
      if(i==0) {
	sr[i]->Draw("hist");
        sr[i]->GetXaxis()->SetTitle(varname);
      }
      else sr[i]->Draw("hist sames");
      */


      TH1D *pred_sr_ = (TH1D*)pred_sr[i]->Clone("pred_sr_");
      TH1D *ratio = (TH1D*)sr[i]->Clone("ratio");
      ratio->Sumw2();
      ratio->SetStats(0);      // No statistics on lower plot                                                                                                             
      ratio->Divide(pred_sr_);
      TH1D *pull = new TH1D("pull","pull",20,-5,5);
      for(int j=1; j<=45; j++)
	{
	  cout<<j<<" : "<<ratio->GetBinContent(j+1)<<" +- "<<ratio->GetBinError(j+1)<<" , 1-R = "<<1-ratio->GetBinContent(j+1)<<" , pull = "<<(1-ratio->GetBinContent(j+1))/ratio->GetBinError(j+1)<<endl; 
	  pull->Fill((1-ratio->GetBinContent(j+1))/ratio->GetBinError(j+1));
	}
      pull->GetXaxis()->SetTitle("1-R/#deltaR");
      pull->Draw("hists");
      

      legend->AddEntry(sr[i],name,"lp");
    }
  legend->Draw();
}
