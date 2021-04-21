void plot2d(TString varName, TString year, bool data)
{
  //     bool CR=true,SR=false, Pred=false;
     bool CR=false,SR=true, Pred=false;
  //  bool CR=false,SR=false, Pred=true;
  TFile *f1;
  //  TString path="rootoutput/newselec_LE_noISRjet_noHEM/";
  //  TString path="rootoutput/newselec_LM_noISRjet_v2/";
  //  TString path="rootoutput/newselec_LE_noISRjet_METfilters_EW_hadjetID/";
  //  TString path="rootoutput/newselec_LM_noISRjet_METfilters_EW_hadjetID/";
  //  TString path="rootoutput/newselec_LE_noISRjet_METfilters_nogenpromptpho_forWGandTTG/";
  //  TString path="rootoutput/newselec_LE_noISRjet_METfilters_nogenpromptpho_forWGandTTG_phoetacut/";
  //TString path="rootoutput/newselec_LE_noISRjet_METfilters_nogenpromptpho_forWGandTTG_phoetaminus_1to0.5/";
  //TString path="rootoutput/newselec_LEplusLM_noISRjet/";
  //  TString path="rootout/fake_rate_v1/FR_v1/";
  //  TString  path="/Users/bkansal/work/MET_Analysis/Analysis/fakerate/rootout/fake_rate_v6/FR_using_PhoPtQmulti_csv_cut_Qmultibin1_phoptbin2/";
  TString path="./rootout/fake_rate_v6/FR_using_PhoPtQmulti_csv_cut_EMObjeta_qmulti/";
  

  //  path="/Users/bkansal/work/MET_Analysis/Analysis/fakerate/rootout/fake_rate_v6/FR_using_PhoPtQmulti_csv_cut_nb_nj_cut/";
  // path="/Users/bkansal/work/MET_Analysis/Analysis/fakerate/rootout/fake_rate_v6/FR_using_PhoPtQmulti_csv_cut_usingtrg_reject_notmatchede_HEM/";
  //   path="/Users/bkansal/work/MET_Analysis/Analysis/fakerate/rootout/fake_rate_v6/FR_using_PhoPtQmulti_csv_cut_usingtrg_reject_notmatchede_EMetage0pt1/";
  //    path="/Users/bkansal/work/MET_Analysis/Analysis/fakerate/rootout/fake_rate_v6/FR_using_PhoPtQmulti_csv_cut_usingtrg_reject_notmatchede_HEM_HTHT5_METCaloMET_pucenter/";
  //   path="/Users/bkansal/work/MET_Analysis/Analysis/fakerate/rootout/fake_rate_v6/FR_using_PhoPtQmulti_csv_cut_usingtrg_reject_notmatchede_HEM_METCaloMET_pucenter/";
    path="/Users/bkansal/work/MET_Analysis/Analysis/fakerate/rootout/fake_rate_v6/FR_using_PhoPtQmulti_csv_cut_usingtrg_reject_notmatchede_HEM_pucenter/";
  //   path="/Users/bkansal/work/MET_Analysis/Analysis/fakerate/rootout/fake_rate_v6/FR_using_PhoPtQmulti_csv_cut_usingtrg_reject_notmatchede/";
  // path="/Users/bkansal/work/MET_Analysis/Analysis/fakerate/rootout/fake_rate_v6/FR_using_PhoPtQmulti_csv_cut_usingtrg_reject_notmatchede_dphiMETjet1cut/";
    //  path="./";
  /* //  path="rootout/fake_rate_v5/FR_using_PhoPtQmulti_csv_cut/"; */
  /* path="rootout/fake_rate_v6/FR_using_PhoPtQmulti_csv_cut/"; */
  TString filename;
  gStyle->SetPalette(1);
  TString pdf;
  gStyle->SetOptStat(0);
  TLegend *legend1 = new TLegend(0.1,0.82,0.4,0.9);
  legend1->SetHeader(year,"C");                               // option "C" allows to center the header
  TLegend *legend2 = new TLegend(0.6,0.82,0.9,0.9);
  //  legend2->SetHeader("Electrons in CR region","C");                               // option "C" allows to center the header
  if(CR) legend2->SetHeader("1 e & 0 photon : CR","C");                               // option "C" allows to center the header
  else if(SR) legend2->SetHeader("0 e & 1 photon : SR","C");
  else if(Pred)  legend2->SetHeader("FR X CR","C");
  legend2->SetTextSize(0.04);
  TCanvas *c1 = new TCanvas("stackhist","stackhist",1000,1000);
  c1->SetLogz();
  TLatex textOnTop,intLumiE;

  if(data)
    {
      //      textOnTop.DrawLatexNDC(0.12,0.91,"CMS #it{#bf{Preliminary}}");
      pdf = path+"PDF/datavsMC/"+varName+"_"+year+"_data.pdf";
      if(year=="full_Run2")
	{
	  filename=path+"Run2_METdata_CR.root";
	  f1 = new TFile(filename);
	}
      else
	{
	  filename=path+"Run"+year+"_METdata_CR_v18.root";
	  f1 = new TFile(filename);
	}
    }
  else
    {
      //      textOnTop.DrawLatexNDC(0.12,0.91,"CMS #it{#bf{Simulation Preliminary}}");

      pdf = path+"PDF/datavsMC/"+varName+"_"+year+"_MC.pdf";
      if(year=="full_Run2")
	{
	filename=path+"TTWGJ_CR_v18.root";
	f1 = new TFile(filename);
	}
      else
	{
	  filename=path+"TTWGJ_"+year+"_CR_v18.root";
	  f1 = new TFile(filename);
	}
    }


  
  TH2D *cr;
  TString varName1;
  if(CR) varName1= varName;
  else if(SR) varName1= varName + "_elec0";
  else if(Pred) varName1= varName + "_elec1_closure";
  cr = (TH2D*)f1->Get(varName1);

  if(varName=="BestPhotonPt_jetmatchphoratio" || varName == "BestPhotonPt_jetphoratio" || varName=="QMultlleadbJet_v2")
    {
      cr->RebinY(5);
      cr->RebinX(5);
      cr->GetYaxis()->SetRangeUser(0,5);
      cr->GetXaxis()->SetRangeUser(0,600);
      cr->GetYaxis()->SetTitle("Jet Pt/ EM Object Pt");
      cr->GetXaxis()->SetTitle("EM Object Pt");
    }

  if(varName=="ElectronEta_Phi" || varName=="leadElectronEta_Phi" || varName=="JetEta_Phi" || varName=="leadJetEta_Phi" || varName=="JetEta_Phi1" || varName=="JetEta_Phi2" || varName=="JetEta_Phi3" || varName=="JetEta_Phi4")
    {
      cr->RebinY(1);
      cr->RebinX(1);
      cr->GetYaxis()->SetRangeUser(-5,5);
      cr->GetXaxis()->SetRangeUser(-3,3);
      //    cr->GetZaxis()->SetRangeUser(0.001,100);
      cr->GetXaxis()->SetTitle("Eta");
      cr->GetYaxis()->SetTitle("Phi");
    }
  if(varName=="h2_Phivseta_jet1" || varName=="h2_Phivseta_jet2" || varName=="h2_Phivseta_jet3" || varName=="h2_Phivseta_jet4" )
    {
      cr->RebinY(10);
      cr->RebinX(10);
      cr->GetYaxis()->SetRangeUser(-3,3);
      cr->GetXaxis()->SetRangeUser(-5,5);
      cr->GetXaxis()->SetTitle("Phi");
      cr->GetYaxis()->SetTitle("Eta");
    }
  if(varName=="h2_dPhivseta_jet1" || varName=="h2_dPhivseta_jet2" || varName=="h2_dPhivseta_jet3" || varName=="h2_dPhivseta_jet4" )
    {
      cr->RebinY(10);
      cr->RebinX(10);
      cr->GetYaxis()->SetRangeUser(-3,3);
      cr->GetXaxis()->SetRangeUser(0,5);
      cr->GetXaxis()->SetTitle("dPhi(MET,JET)");
      cr->GetYaxis()->SetTitle("Eta");
    }
  else if(varName=="BestPhoEta_Pt" || varName=="leadJetEta_Pt" || varName=="JetEta_Pt" || varName=="2leadJetEta_Pt"|| varName=="JetEta_Pt1" || varName=="JetEta_Pt2" || varName=="JetEta_Pt3" || varName=="JetEta_Pt4")
    {
      cr->RebinY(2);
      cr->RebinX(2);
      //      cr->GetYaxis()->SetRangeUser(-5,5);
      //      cr->GetXaxis()->SetRangeUser(-3,3);
      cr->GetXaxis()->SetTitle("lead Jet Eta");
      cr->GetYaxis()->SetTitle("lead Jet Pt");
    }
  else if(varName=="leadElectronPt_Eta" )
    {
      /* cr->RebinY(10); */
      /* cr->RebinX(5); */
      
      cr->GetYaxis()->SetRangeUser(-3,3);                                                                                                             
      cr->GetXaxis()->SetRangeUser(100,700);                                                                                                             
      cr->GetXaxis()->SetTitle("e Pt");
      cr->GetYaxis()->SetTitle("e Eta");
    }

  else if(varName=="leadElectronPt_Phi" )
    {
      /* cr->RebinY(10); */
      /* cr->RebinX(5); */
      
      cr->GetYaxis()->SetRangeUser(-3,3);                                                                                                             
      cr->GetXaxis()->SetRangeUser(100,700);                                                                                                             
      cr->GetXaxis()->SetTitle("e Pt");
      cr->GetYaxis()->SetTitle("e Phi");
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
  else if(varName=="BestPhotonEta_Qmulti")
    {
      cr->RebinY(1);
      cr->RebinX(1);
      //cr_2->RebinY(1);
      //cr_2->RebinX(1);
      /* cr->GetYaxis()->SetRangeUser(-3.5,3.5); */
      /* cr->GetXaxis()->SetRangeUser(0,1000); */
      //      cr->GetZaxis()->SetRangeUser(0,5);                                                                                                              
      cr->GetXaxis()->SetTitle("EM object Eta");
      cr->GetYaxis()->SetTitle("EM object Qmulti");
    }
  else if(varName=="BestPhotonEta_nJets")
    {
      cr->RebinY(1);
      cr->RebinX(1);
      //    cr_2->RebinY(1);
      //cr_2->RebinX(1);
      /* cr->GetYaxis()->SetRangeUser(-3.5,3.5); */
      /* cr->GetXaxis()->SetRangeUser(0,1000); */
      //      cr->GetZaxis()->SetRangeUser(0,5);                                                                                                              
      cr->GetXaxis()->SetTitle("EM object Eta");
      cr->GetYaxis()->SetTitle("EM object nJets");
    }
  else if(varName=="HT5HT_dPhiMETj2" || varName=="HT5HT_dPhiMETj1" || varName=="HT5HT_dPhiMETj3" || varName=="HT5HT_dPhiMETj4")
    {
      cr->RebinY(1);
      cr->RebinX(1);
      //    cr_2->RebinY(1);
      //cr_2->RebinX(1);
      cr->GetYaxis()->SetRangeUser(1,3);
      cr->GetXaxis()->SetRangeUser(0,3.5);
      cr->GetZaxis()->SetRangeUser(0.1,10000);                                                                                                              
      cr->GetYaxis()->SetTitle("HT5/HT");
      if(varName=="HT5HT_dPhiMETj1")      cr->GetXaxis()->SetTitle("dPhi(MET,jet1)");
      if(varName=="HT5HT_dPhiMETj2")      cr->GetXaxis()->SetTitle("dPhi(MET,jet2)");
      if(varName=="HT5HT_dPhiMETj3")      cr->GetXaxis()->SetTitle("dPhi(MET,jet3)");
      if(varName=="HT5HT_dPhiMETj4")      cr->GetXaxis()->SetTitle("dPhi(MET,jet4)");
    }
  else if(varName=="BestPhotonEta_MET")
    {
      cr->RebinY(5);
      cr->RebinX(1);
      /* cr->GetYaxis()->SetRangeUser(-3.5,3.5); */
      /* cr->GetXaxis()->SetRangeUser(0,1000); */
      //      cr->GetZaxis()->SetRangeUser(0,5);                                                                                                              
      cr->GetXaxis()->SetTitle("EM object Eta");
      cr->GetYaxis()->SetTitle("EM object MET");
    }
  else if(varName=="PhoPtQMultJet" || varName=="PhoPtQMultJet_v2")
    {
      /* cr->RebinY(5); */
      /* cr->RebinX(10); */
      //      cr->GetYaxis()->SetRangeUser(-5,5);
      //      cr->GetXaxis()->SetRangeUser(-3,3);
      cr->GetXaxis()->SetTitle("EM object Pt");
      cr->GetYaxis()->SetTitle("Qmultiplicity");
    }
  else if(varName=="PhoPtQMultJet_v3")
    {
      /* cr->RebinY(5); */
      /* cr->RebinX(10); */
      //      cr->GetYaxis()->SetRangeUser(-5,5);
      //      cr->GetXaxis()->SetRangeUser(-3,3);
      cr->GetYaxis()->SetRangeUser(0,30);
           cr->GetXaxis()->SetRangeUser(100,800);
      cr->GetXaxis()->SetTitle("EM object Pt");
      cr->GetYaxis()->SetTitle("Qmultiplicity");
    }
  else if(varName=="METQMultJet")
    {
      /* cr->RebinY(5); */
      /* cr->RebinX(10); */
      cr->GetYaxis()->SetRangeUser(0,30);
           cr->GetXaxis()->SetRangeUser(0,1200);
      cr->GetXaxis()->SetTitle("MET");
      cr->GetYaxis()->SetTitle("Qmultiplicity");
    }
  else if(varName=="nJetsMET")
    {
      /* cr->RebinY(1); */
      /* cr->RebinX(4); */
     cr->GetYaxis()->SetRangeUser(0,1000);
      cr->GetXaxis()->SetRangeUser(7,14);
      cr->GetXaxis()->SetTitle("nJets");
      cr->GetYaxis()->SetTitle("MET");
    }
  else if(varName=="PhoPtMET")
    {
      cr->RebinY(1);
      cr->RebinX(1);
      cr->GetYaxis()->SetRangeUser(0,1000);
      cr->GetXaxis()->SetRangeUser(100,1000);
      cr->GetXaxis()->SetTitle("EM object Pt");
      cr->GetYaxis()->SetTitle("MET");
    }

  else if(varName=="PhoPtnJets")
    {
      cr->RebinY(1);
      cr->RebinX(1);
      cr->GetYaxis()->SetRangeUser(0,14);
      cr->GetXaxis()->SetRangeUser(100,1000);
      cr->GetXaxis()->SetTitle("EM object Pt");
      cr->GetYaxis()->SetTitle("nJets");
    }
  else if(varName=="nJetsQMultJet")
    {
       /* cr->RebinY(10); */

      /* cr->RebinX(2); */
      cr->GetYaxis()->SetRangeUser(0,50);
      cr->GetXaxis()->SetRangeUser(7,14);
      cr->GetXaxis()->SetTitle("nJets");
      cr->GetYaxis()->SetTitle("Qmultiplicity");
    }
  cr->SetTitle(0);
  cr->Draw("colz");
  legend1->Draw();
  legend2->Draw();
  textOnTop.SetTextSize(0.04);
  intLumiE.SetTextSize(0.04);
  int z=0;
  for(int i=1;i<=100;i++)                                                                                                                                  
    {                                                                                                                                                    
      for(int j=1;j<=50;j++)
	{ z++;
	  if(cr->GetBinContent(i,j)>0)
	    cout<<z<<": "<<cr->GetXaxis()->GetBinLowEdge(i)<<" - "<<cr->GetXaxis()->GetBinLowEdge(i+1)<<"  ::    "<<cr->GetYaxis()->GetBinLowEdge(j)
	      <<" - "<<cr->GetYaxis()->GetBinLowEdge(j+1)<<"    ::   "<<cr->GetBinContent(i,j)<<endl;                                                                      
	}
    }
  //  if(isPaper) textOnTop.DrawLatexNDC(0.12,0.91,"CMS #it{#bf{Simulation Supplementary}}");
  if(data)
    {
      textOnTop.DrawLatexNDC(0.12,0.91,"CMS #it{#bf{Preliminary}}");
    }
  else
    textOnTop.DrawLatexNDC(0.12,0.91,"CMS #it{#bf{Simulation Preliminary}}");

  
  if(year=="2016")
    intLumiE.DrawLatexNDC(0.75,0.91,"#bf{35.9 fb^{-1} (13 TeV)}");
  if(year=="2017")
    intLumiE.DrawLatexNDC(0.75,0.91,"#bf{41.5 fb^{-1} (13 TeV)}");
  if(year=="2018")
    intLumiE.DrawLatexNDC(0.75,0.91,"#bf{59.6 fb^{-1} (13 TeV)}");
  if(year=="full_Run2")
    intLumiE.DrawLatexNDC(0.75,0.91,"#bf{137 fb^{-1} (13 TeV)}");
               
  c1->SaveAs(pdf);
  
}
