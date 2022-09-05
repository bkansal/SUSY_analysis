void plot2dratio(TString varName, TString year,bool ExpvsPred,bool SRvsCR)
{

  bool data=true;
  //  bool data=false;
  
  TString varName1,varName0;
  TFile *f1,*f2;
  //  TString path="rootout/fake_rate_v1/FR_v1/FR_Full/";
  //  TString path="rootout/fake_rate_v1/FR_v1/FR_foryearwise/";
  TString path="./";
  //  TString path="/Users/bkansal/work/MET_Analysis/Analysis/fakerate/rootout/fake_rate_v4/FR_using_PhoPtQmultinJets/";
  //  TString path="./rootout/fake_rate_v3/FR_using_PhoPtEta/"; 
  //  TString path="/Users/bkansal/work/MET_Analysis/Analysis/fakerate/rootout/fake_rate_v2/FR_for2016_wopx_mindr_lpt3_jetsandemobject/";
  //  TString path="/Users/bkansal/work/MET_Analysis/Analysis/fakerate/rootout/fake_rate_v2/FR_for2016_pxonly/";
  // TString path="/Users/bkansal/work/MET_Analysis/Analysis/fakerate/rootout/fake_rate_v2/FR_for2016_wopx/";
   path="./rootoutput/v1/withsimpleselections_ST200_nopxveto/";
  TString filename;
  TString rootout;
  if(year=="full_Run2")
    rootout="fake_rate.root";
  else
    rootout="fake_rate_"+year+".root";
  cout<<rootout<<endl;

  
  TString pdf;
  gStyle->SetOptStat(0);
  TLegend *legend1 = new TLegend(0.1,0.82,0.4,0.9);
  legend1->SetHeader(year,"C");                               // option "C" allows to center the header
  TLegend *legend2 = new TLegend(0.6,0.82,0.9,0.9);
  //  legend2->SetHeader("Muon in CR region","C");                               // option "C" allows to center the header
  if(SRvsCR)  legend2->SetHeader("fake rate (SR/CR)","C");                               // option "C" allows to center the header
  if(ExpvsPred)  legend2->SetHeader("SR/(FR x CR)","C");                               // option "C" allows to center the header
  TCanvas *c1 = new TCanvas("stackhist","stackhist",1000,1000);

  TLatex textOnTop,intLumiE;

  //  if(data)
    {
      pdf = path+"PDF/datavsMC/"+varName+"_"+year+"_datavsMC.pdf";
      if(year=="full_Run2")
	{
	  filename=path+"Run2_METdata_CR.root";
	  f1 = new TFile(filename);
	}
      else
	{
	  //	  filename=path+"Run"+year+"_METdata_CR.root";
	  filename=path+"Run"+year+"_CR_v18.root";
	  f1 = new TFile(filename);
	}
    }
    //  else
    {
      pdf = path+"PDF/FR/"+varName+"_"+year+"_data.pdf";
      if(year=="full_Run2")
	{
	filename=path+"TTWGJ_CR_v18.root";
	f2 = new TFile(filename);
	}
      else
	{
	  //	  filename=path+"TTWGJ_"+year+"_CR_v18.root";
	  filename=path+"TTWDY_"+year+"_CR_v18.root";
	  f2 = new TFile(filename);
	}
      if(SRvsCR) varName1=varName;
      if(ExpvsPred) varName1=varName+"_elec1_closure";
      varName0=varName+"_elec0";
    }


  
  TH2D *cr_1,*cr_2,*cr_0,*cr;
  //  TH2D *cr_3,*cr_4;  
  TFile *fout =new TFile(rootout,"recreate");
  fout->cd();
    
  cr_2 = (TH2D*)f2->Get(varName1);
  cr_1 = (TH2D*)f1->Get(varName1);
  cr_0 = (TH2D*)f1->Get(varName0); 
  /* else */
  cr = (TH2D*)f2->Get(varName0);
  //cr->Divide(cr_2);

 
  if(varName=="BestPhotonPt_jetmatchphoratio" || varName=="BestPhotonPt_jetphoratio")
    {
      cr->RebinY(5);
      cr->RebinX(5);
      cr_2->RebinY(5);
      cr_2->RebinX(5);
      cr->GetYaxis()->SetRangeUser(0,2.5);
      cr->GetXaxis()->SetRangeUser(0,600);
      cr->GetZaxis()->SetRangeUser(0,5);
      cr->GetYaxis()->SetTitle("Jet Pt/ Best Photon Pt");
      cr->GetXaxis()->SetTitle("Best Photon Pt");
    }
  if(varName=="ElectronEta_Phi" || varName=="leadElectronEta_Phi" || varName=="JetEta_Phi" || varName=="leadJetEta_Phi")
    {
      cr->RebinY(20);
      cr->RebinX(20);
      cr_2->RebinY(20);
      cr_2->RebinX(20);
      cr->GetYaxis()->SetRangeUser(-5,5);
      cr->GetXaxis()->SetRangeUser(-3,3);
      cr->GetZaxis()->SetRangeUser(0,5);
      cr->GetXaxis()->SetTitle("Eta");
      cr->GetYaxis()->SetTitle("Phi");
    }
  if(varName=="leadElectronPt_Eta"|| varName=="BestPhoEta_Pt")
    {
      cr->RebinY(10);
      cr->RebinX(10);
      cr_2->RebinY(10);
      cr_2->RebinX(10);
      cr->GetYaxis()->SetRangeUser(-5,5);
      cr->GetXaxis()->SetRangeUser(0,500);
      //      cr->GetZaxis()->SetRangeUser(0,5);
      cr->GetXaxis()->SetTitle("EM object Pt");
      cr->GetYaxis()->SetTitle("EM object Eta");
    }
  if(varName=="nbjets_nJets")
    {
      /* cr->RebinY(10); */
      /* cr->RebinX(10); */
      /* cr_2->RebinY(10); */
      /* cr_2->RebinX(10); */
      cr->GetYaxis()->SetRangeUser(0,10);
      cr->GetXaxis()->SetRangeUser(0,15);
      // cr->GetZaxis()->SetRangeUser(0,5);
      cr->GetXaxis()->SetTitle("nJets");
      cr->GetYaxis()->SetTitle("BTags");
    }

  if(varName=="h2_Phivseta_jet1" || varName=="h2_Phivseta_jet2" || varName=="h2_Phivseta_jet3" || varName=="h2_Phivseta_jet4" )
    {
      cr->RebinY(10);
      cr->RebinX(10);
      cr_2->RebinY(10);
      cr_2->RebinX(10);
      cr->GetYaxis()->SetRangeUser(-3,3);
      cr->GetXaxis()->SetRangeUser(-5,5);
      cr->GetZaxis()->SetRangeUser(0,5);
      cr->GetXaxis()->SetTitle("Phi");
      cr->GetYaxis()->SetTitle("Eta");
    }
  if(varName=="h2_dPhivseta_jet1" || varName=="h2_dPhivseta_jet2" || varName=="h2_dPhivseta_jet3" || varName=="h2_dPhivseta_jet4" )
    {
      cr->RebinY(10);
      cr->RebinX(10);
      cr_2->RebinY(10);
      cr_2->RebinX(10);
      cr->GetYaxis()->SetRangeUser(-3,3);
      cr->GetXaxis()->SetRangeUser(0,5);
      cr->GetZaxis()->SetRangeUser(0,5);
      cr->GetXaxis()->SetTitle("dPhi(MET,JET)");
      cr->GetYaxis()->SetTitle("Eta");
    }


  else if(varName=="BestPhoEta_Pt" || varName=="leadJetEta_Pt" || varName=="JetEta_Pt")
    {
      int rebin=4;
      cr->RebinY(rebin);
      cr->RebinX(2*rebin);
      cr_2->RebinY(rebin);
      cr_2->RebinX(2*rebin);
      //      cr->GetYaxis()->SetRangeUser(-5,5);
      cr->GetXaxis()->SetRangeUser(-3,3);
      cr->GetXaxis()->SetTitle("Eta");
      cr->GetYaxis()->SetTitle("Pt");
      cr->GetYaxis()->SetRangeUser(100,200);

      cr_0->RebinY(rebin);
      cr_0->RebinX(2*rebin);
      cr_1->RebinY(rebin);
      cr_1->RebinX(2*rebin);
      //      cr->GetYaxis()->SetRangeUser(-5,5);
      cr_0->GetXaxis()->SetRangeUser(-3,3);
      cr_0->GetXaxis()->SetTitle("Eta");
      cr_0->GetYaxis()->SetTitle("Pt");
      cr_0->GetYaxis()->SetRangeUser(100,400);
    }
  else if(varName=="BestPhotonPt_jetphoratio")
    {
      /* cr->RebinY(10); */
      /* cr->RebinX(5); */
      //      cr->GetYaxis()->SetRangeUser(-5,5);
      //      cr->GetXaxis()->SetRangeUser(-3,3);
      cr->GetXaxis()->SetTitle("Pt");
      cr->GetYaxis()->SetTitle("Pt");
    }
  else if(varName=="PhoPtQMultJet")
    {
      /* cr->RebinY(10); */
      /* cr->RebinX(5); */
      /* cr->Divide(cr_2); */
      /* cr->GetYaxis()->SetRangeUser(0,20); */
      /* cr->GetXaxis()->SetRangeUser(100,300); */
      cr->GetXaxis()->SetTitle("EM object Pt");
      cr->GetYaxis()->SetTitle("Qmultiplicity");
      //   cr->Divide(cr_2);
    }
    else if(varName=="PhoPtnJets")
    {
      /* cr->RebinY(10); */
      /* cr->RebinX(5); */
      /* cr->Divide(cr_2); */
      /* cr->GetYaxis()->SetRangeUser(0,20); */
      /* cr->GetXaxis()->SetRangeUser(100,300); */
      cr->GetXaxis()->SetTitle("EM object Pt");
      cr->GetYaxis()->SetTitle("nJets");
      //   cr->Divide(cr_2);
    }
    else if(varName=="PhoPtnJetsbtags")
    {
      /* cr->RebinY(10); */
      /* cr->RebinX(5); */
      /* cr->Divide(cr_2); */
      /* cr->GetYaxis()->SetRangeUser(0,20); */
      /* cr->GetXaxis()->SetRangeUser(100,300); */
      cr->GetXaxis()->SetTitle("EM object Pt");
      cr->GetYaxis()->SetTitle("nJets");
      cr->GetZaxis()->SetTitle("nBTags");

      //   cr->Divide(cr_2);
    }
    else if(varName=="PhoPtnJetsQMult")
    {
      /* cr->RebinY(10); */
      /* cr->RebinX(5); */
      /* cr->Divide(cr_2); */
      /* cr->GetYaxis()->SetRangeUser(0,20); */
      /* cr->GetXaxis()->SetRangeUser(100,300); */
      cr->GetXaxis()->SetTitle("EM object Pt");
      cr->GetYaxis()->SetTitle("nJets");
      cr->GetZaxis()->SetTitle("Qmultiplicity");

      //   cr->Divide(cr_2);
    }
  else if(varName=="nJetsQMultJet")
    {
      /* cr->RebinY(10); */
      /* cr->RebinX(5); */
      cr->GetYaxis()->SetRangeUser(0,20);
      cr->GetXaxis()->SetRangeUser(2,14);
      cr->GetXaxis()->SetTitle("nJets");
      cr->GetYaxis()->SetTitle("Qmultiplicity");
      //      cr->Divide(cr_2);
    }
  /* else if(varName=="QMultJet") */
  /*   { */
  /*     /\* cr->RebinY(10); *\/ */
  /*     /\* cr->RebinX(5); *\/ */
  /*     cr->GetYaxis()->SetRangeUser(4,20); */
  /*     cr->GetXaxis()->SetRangeUser(7,20); */

  /*     cr->GetXaxis()->SetTitle("nJets"); */
  /*     cr->GetYaxis()->SetTitle("Qmultiplicity"); */
  /*     //      cr->Divide(cr_2); */
  /*   } */

  cr->Divide(cr_2);
  cr_0->Divide(cr_1);
 for(int i=0;i<=10;i++)
   for(int j=0;j<=3;j++)
     for(int k=0;k<=4;k++)
       {
	 if(cr->GetXaxis()->GetBinLowEdge(i)>=0 && cr->GetYaxis()->GetBinLowEdge(j)>=0 && cr->GetZaxis()->GetBinLowEdge(k)>=0)
	   cout<<i<<" : EM Pt = "<<cr->GetXaxis()->GetBinLowEdge(i)<<" : NJets = "<<cr->GetYaxis()->GetBinLowEdge(j)<<" : Qmulti = "<<cr->GetZaxis()->GetBinLowEdge(k)<<" : bin content = "<<cr->GetBinContent(i,j,k)<<endl;
       }
 cr->SetTitle(0);
  legend1->Draw();
  legend2->Draw();
  textOnTop.SetTextSize(0.04);
  intLumiE.SetTextSize(0.04);
  //  if(isPaper) textOnTop.DrawLatexNDC(0.12,0.91,"CMS #it{#bf{Simulation Supplementary}}");                                                                 
  textOnTop.DrawLatexNDC(0.12,0.91,"CMS #it{#bf{Preliminary}}");
  if(year=="2016")
    intLumiE.DrawLatexNDC(0.75,0.91,"#bf{35.9 fb^{-1} (13 TeV)}");
  if(year=="2017")
    intLumiE.DrawLatexNDC(0.75,0.91,"#bf{41.5 fb^{-1} (13 TeV)}");
  if(year=="2018")
    intLumiE.DrawLatexNDC(0.75,0.91,"#bf{59.6 fb^{-1} (13 TeV)}");
  if(year=="full_Run2")
    intLumiE.DrawLatexNDC(0.75,0.91,"#bf{137 fb^{-1} (13 TeV)}");
   TH2D *fr = (TH2D*)cr->Clone("fr");
   TH2D *fr1 = (TH2D*)cr_0->Clone("fr1");
   TH2D* SF = (TH2D*)cr_0->Clone("SF");
   SF->Divide(fr);
  SF->Draw("colz");
  fr->Write();
  fr1->Write();
  SF->Write();
  fout->cd();
               
  c1->SaveAs(pdf);
  
}

