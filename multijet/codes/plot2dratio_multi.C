void plot2dratio_multi(TString varName, TString year,bool ExpvsPred,bool SRvsCR, bool data=false)
{

  
  TString varName1,varName0;
  TFile *f1,*f2;
  TString path;
  path="../multijet/rootoutput/final/noRK/";
  TString filename;
  TString rootout;

  TString pdf,png;
  //  gStyle->SetPalette(1);
  gStyle->SetOptStat(0);
  TLegend *legend1 = new TLegend(0.1,0.82,0.2,0.9);
  legend1->SetHeader("MC","C");                               // option "C" allows to center the header
  TLegend *legend2 = new TLegend(0.4,0.82,0.9,0.9);
  //  legend2->SetHeader("Muon in CR region","C");                               // option "C" allows to center the header
  if(SRvsCR)  legend2->SetHeader("R=high-#Delta#Phi/low-#Delta#Phi (nbjets = 0)","C");                               // option "C" allows to center the header
  if(ExpvsPred)  legend2->SetHeader("R=high-#Delta#Phi/low-#Delta#Phi (nbjets > 0)","C");                               // option "C" allows to center the header
  TCanvas *c1 = new TCanvas("stackhist","stackhist",1000,1000);
  c1->SetLogx();

  TLatex textOnTop,intLumiE;

  if(data)
    {
      pdf = path+"PDF/datavsMC_"+varName+"_"+year+"_datavsMC.pdf";
      if(year=="full_Run2")
	{
	  filename=path+"Run2_METdata_CR.root";
	  f1 = new TFile(filename);
	}
      else
	{
	  filename=path+"Run"+year+"_METdata_CR.root";
	  f1 = new TFile(filename);
	}
    }
  else
    {
      pdf = path+"PDF/FR_"+varName+"_"+year+"_data.pdf";
      if(year=="full_Run2")
	{
	filename=path+"GJetsQCD_new_v18.root";
	f2 = new TFile(filename);
	}
      else
	{
	  filename=path+"GJetsQCD_new_"+year+"_v18.root";
	  f2 = new TFile(filename);
	}
    }
  
  if(SRvsCR)
    {
      varName0=varName+"_C";
      varName1=varName+"_A";
      if(year == "full_Run2")    rootout="Kfactor_nbj0.root";
      else     rootout="Kfactor_nbj0_"+year+".root";
      png="png/Multi_"+varName+"_"+year+"_nbj0.png";
      pdf="pdf/Multi_"+varName+"_"+year+"_nbj0.pdf";
    }
  if(ExpvsPred)
    {
      varName0=varName+"_D";
      varName1=varName+"_B";
      if(year == "full_Run2")    rootout="Kfactor.root";
      else     rootout="Kfactor_"+year+".root";
      png="png/Multi_"+varName+"_"+year+"_nbj1.png";
      pdf="pdf/Multi_"+varName+"_"+year+"_nbj1.pdf";
    }
    
  
  TH2D *cr_1,*cr_2,*cr;
  //  TH2D *cr_3,*cr_4;  
  TFile *fout =new TFile(rootout,"recreate");
  fout->cd();
    
  cr_2 = (TH2D*)f2->Get(varName1);
  /* if (data) cr = (TH2D*)f1->Get(varName1); */
  /* else */
  cr = (TH2D*)f2->Get(varName0);
  //cr->Divide(cr_2);

  if(varName=="nJetsMET" || varName=="nJetsMET_v2" )
    {
      cr->SetMarkerSize(1.3);
      cr->GetYaxis()->SetTitle("nJets");
      cr->GetXaxis()->SetTitle("MET");
      
      fout =new TFile(rootout,"recreate");
      fout->cd();
      cout<<"root file name : "<<rootout<<endl;
    }
 
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
      cr->RebinY(10);
      cr->RebinX(10);
      cr_2->RebinY(10);
      cr_2->RebinX(10);
      cr->GetYaxis()->SetRangeUser(-5,5);
      cr->GetXaxis()->SetRangeUser(-3,3);
      cr->GetZaxis()->SetRangeUser(0,5);
      cr->GetXaxis()->SetTitle("Eta");
      cr->GetYaxis()->SetTitle("Phi");
    }
  if(varName=="leadElectronPt_Eta")
    {
      cr->RebinY(1);
      cr->RebinX(1);
      cr_2->RebinY(1);
      cr_2->RebinX(1);
      cr->GetYaxis()->SetRangeUser(-3.5,3.5);
      cr->GetXaxis()->SetRangeUser(0,1000);
      //      cr->GetZaxis()->SetRangeUser(0,5);
      cr->GetXaxis()->SetTitle("EM object Pt");
      cr->GetYaxis()->SetTitle("EM object Eta");
    }
  if(varName=="BestPhotonEta_Qmulti")
    {
      cr->RebinY(1);
      cr->RebinX(1);
      cr_2->RebinY(1);
      cr_2->RebinX(1);
      /* cr->GetYaxis()->SetRangeUser(-3.5,3.5); */
      /* cr->GetXaxis()->SetRangeUser(0,1000); */
      //      cr->GetZaxis()->SetRangeUser(0,5);
      cr->GetXaxis()->SetTitle("EM object Eta");
      cr->GetYaxis()->SetTitle("EM object Qmulti");
    }
  if(varName=="BestPhotonEta_nJets")
    {
      cr->RebinY(1);
      cr->RebinX(1);
      cr_2->RebinY(1);
      cr_2->RebinX(1);
      /* cr->GetYaxis()->SetRangeUser(-3.5,3.5); */
      /* cr->GetXaxis()->SetRangeUser(0,1000); */
      //      cr->GetZaxis()->SetRangeUser(0,5);
      cr->GetXaxis()->SetTitle("EM object Eta");
      cr->GetYaxis()->SetTitle("EM object nJets");
    }
  if(varName=="BestPhotonEta_MET")
    {
      cr->RebinY(5);
      cr->RebinX(1);
      cr_2->RebinY(5);
      cr_2->RebinX(1);
      /* cr->GetYaxis()->SetRangeUser(-3.5,3.5); */
      /* cr->GetXaxis()->SetRangeUser(0,1000); */
      //      cr->GetZaxis()->SetRangeUser(0,5);
      cr->GetXaxis()->SetTitle("EM object Eta");
      cr->GetYaxis()->SetTitle("EM object MET");
    }
  if(varName=="nbjets_nJets")
    {
      /* cr->RebinY(10); */
      /* cr->RebinX(10); */
      /* cr_2->RebinY(10); */
      /* cr_2->RebinX(10); */
      cr->GetYaxis()->SetRangeUser(0,10);
      cr->GetXaxis()->SetRangeUser(0,15);
      cr->GetZaxis()->SetRangeUser(0,0.01);
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
      cr->RebinY(10);
      cr->RebinX(20);
      //      cr->GetYaxis()->SetRangeUser(-5,5);
      cr->GetXaxis()->SetRangeUser(-3,3);
      cr->GetXaxis()->SetTitle("Eta");
      cr->GetYaxis()->SetTitle("Pt");
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
    else if(varName=="PhoPtQMultJet" || varName=="PhoPtQMultJet_v2")
    {
      cr->GetXaxis()->SetTitle("EM object Pt");
      cr->GetYaxis()->SetTitle("Qmultiplicity");
      //   cr->Divide(cr_2);
    }
    else if(varName=="PhoPtnJets")
    {
      cr->RebinY(5);
      cr->RebinX(10);
      /* cr->Divide(cr_2); */
      /* cr->GetYaxis()->SetRangeUser(0,20); */
      cr->GetXaxis()->SetRangeUser(250,1500);
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
  cr->Write();
  int z=0,p=0,q=0;
  if(varName=="BestPhotonEta_Qmulti")
    {
      cout<<z<<setw(3)<<" :    EM Eta   ::    Qmulti   ::  fake rate  : "<<endl;
      cout<<"=================================================="<<endl;

      for(int i=1;i<=8;i++)
	{
	  for(int j=1;j<=5;j++)
	  { z++;
	    cout<<z<<setw(p)<<": "<<cr->GetXaxis()->GetBinLowEdge(i)<<" - "<<cr->GetXaxis()->GetBinLowEdge(i+1)<<"  ::    "<<cr->GetYaxis()->GetBinLowEdge(j)<<" - "<<cr->GetYaxis()->GetBinLowEdge(j+1)<<"    ::   "<<cr->GetBinContent(i,j)<<endl;
	  /*   if(z<10) p=3; */
	  /*   else p=2; */

	   
	  /*   if(cr->GetXaxis()->GetBinLowEdge(i)>=0 && cr->GetYaxis()->GetBinLowEdge(j)>=0) */
	  /*     { */
	  /* 	if(j<4) cout<<z<<setw(p)<<": "<<cr->GetXaxis()->GetBinLowEdge(i)<<" - "<<cr->GetXaxis()->GetBinLowEdge(i+1)<<"  ::    "<<cr->GetYaxis()->GetBinLowEdge(j)<<" - "<<cr->GetYaxis()->GetBinLowEdge(j+1)<<"    ::   "<<cr->GetBinContent(i,j)<<endl; */
	  /* 	if(j>=4) cout<<z<<setw(p)<<": "<<cr->GetXaxis()->GetBinLowEdge(i)<<" - "<<cr->GetXaxis()->GetBinLowEdge(i+1)<<"  ::    "<<cr->GetYaxis()->GetBinLowEdge(j)<<" - "<<cr->GetYaxis()->GetBinLowEdge(j+1)<<"  ::   "<<cr->GetBinContent(i,j)<<endl; */
	  /*     } */
	  } 
	  cout<<"---------------------------------------------"<<endl;
	}
    }
  else if(varName=="PhoPtQMultJet"||varName=="nJetsMET_v2")
    {z=0;
      cout<<"bin"<<setw(3)<<" :    EM Pt   ::    Qmulti   ::  fake rate  : "<<endl;
      cout<<"=================================================="<<endl;
      for(int i=1;i<=11;i++)
	{
	  for(int j=1;j<=4;j++)
	  { z++;
	    if(z<10) p=3;
	    else p=2;

	   
	    if(cr->GetXaxis()->GetBinLowEdge(i)>=0 && cr->GetYaxis()->GetBinLowEdge(j)>=0)
	      {
		cout<<setprecision(2)<<cr->GetBinContent(i,j)<<" +- "<<cr->GetBinError(i,j)<<endl;
		//		cout<<cr->GetYaxis()->GetBinLowEdge(j)<<" - "<<cr->GetYaxis()->GetBinLowEdge(j+1)<<endl;
		/* if(j<4) cout<<z<<setw(p)<<"  : "<<cr->GetXaxis()->GetBinLowEdge(i)<<" - "<<cr->GetXaxis()->GetBinLowEdge(i+1)<<"  ::    "<<cr->GetYaxis()->GetBinLowEdge(j)<<" - "<<cr->GetYaxis()->GetBinLowEdge(j+1)<<"    ::   "<<cr->GetBinContent(i,j)<<endl; */
		/* if(j>=4) cout<<z<<setw(p)<<"  : "<<cr->GetXaxis()->GetBinLowEdge(i)<<" - "<<cr->GetXaxis()->GetBinLowEdge(i+1)<<"  ::    "<<cr->GetYaxis()->GetBinLowEdge(j)<<" - "<<cr->GetYaxis()->GetBinLowEdge(j+1)<<"  ::   "<<cr->GetBinContent(i,j)<<endl; */
	      }
	  }
	  //	  cout<<"---------------------------------------------"<<endl;
	}
    }
  else if(varName=="leadElectronPt_Eta")
    {
      cout<<z<<setw(5)<<" :    EM Pt   ::    EM Eta   ::  fake rate  : "<<endl;
      cout<<"=================================================="<<endl;
      for(int i=2;i<=10;i++)
	{
	  if(cr->GetXaxis()->GetBinLowEdge(i)>=100)
	    for(int j=1;j<=20;j++)
	      {		
		
		if(cr->GetYaxis()->GetBinLowEdge(j)>=-2.5 && cr->GetYaxis()->GetBinLowEdge(j)<=2.5)//0 && cr->GetYaxis()->GetBinLowEdge(j)>=0)
		{
		  z++;
		  if(z<10) p=5;
		  else p=4;

		  if(j<10) q=5;
		  else if(j==10) q=6;
		  else if(j>10) q=7;
		  if(j<10) cout<<z<<setw(p)<<": "<<cr->GetXaxis()->GetBinLowEdge(i)<<" - "<<cr->GetXaxis()->GetBinLowEdge(i+1)<<"  ::    "<<cr->GetYaxis()->GetBinLowEdge(j)<<" - "<<cr->GetYaxis()->GetBinLowEdge(j+1)<<setw(q)<<"::   "<<cr->GetBinContent(i,j)<<endl;
		  else cout<<z<<setw(p)<<": "<<cr->GetXaxis()->GetBinLowEdge(i)<<" - "<<cr->GetXaxis()->GetBinLowEdge(i+1)<<"  ::    "<<cr->GetYaxis()->GetBinLowEdge(j)<<" - "<<cr->GetYaxis()->GetBinLowEdge(j+1)<<setw(q)<<"::   "<<cr->GetBinContent(i,j)<<endl;
		}
	      }
	  cout<<"---------------------------------------------"<<endl;
	}
    }
  else if(varName=="PhoPtnJetsQMult_v2")
    {
      cout<<z<<setw(3)<<" :    EM Pt   ::    nJets"<<setw(3)<<"  ::    Qmulti   ::  fake rate  : "<<endl;
      cout<<"========================================================================"<<endl;
      for(int i=1;i<=10;i++)
	{
	for(int j=1;j<=2;j++)
	  for(int k=1;k<=4;k++)
	    {z++;
	      if(z<10) p=3;
	      else p=2;

	      if(j==1) q=3;
	      else q=2;
	      if(cr->GetXaxis()->GetBinLowEdge(i)>=0 && cr->GetYaxis()->GetBinLowEdge(j)>=0 && cr->GetZaxis()->GetBinLowEdge(k)>=0)
		{
		  if(k<4 && j==1) cout<<z<<setw(p)<<": "<<cr->GetXaxis()->GetBinLowEdge(i)<<" - "<<cr->GetXaxis()->GetBinLowEdge(i+1)<<"  ::    "<<cr->GetYaxis()->GetBinLowEdge(j)<<" - "<<cr->GetYaxis()->GetBinLowEdge(j+1)<<setw(q)<<"  ::    "<<cr->GetZaxis()->GetBinLowEdge(k)<<" - "<<cr->GetZaxis()->GetBinLowEdge(k+1)<<"    ::   "<<cr->GetBinContent(i,j,k)<<endl;
		  if(k==4 && j==1) cout<<z<<setw(p)<<": "<<cr->GetXaxis()->GetBinLowEdge(i)<<" - "<<cr->GetXaxis()->GetBinLowEdge(i+1)<<"  ::    "<<cr->GetYaxis()->GetBinLowEdge(j)<<" - "<<cr->GetYaxis()->GetBinLowEdge(j+1)<<setw(q)<<"  ::    >="<<cr->GetZaxis()->GetBinLowEdge(k)<<"      ::   "<<cr->GetBinContent(i,j,k)<<endl;
		  if(k<4 && j==2) cout<<z<<setw(p)<<": "<<cr->GetXaxis()->GetBinLowEdge(i)<<" - "<<cr->GetXaxis()->GetBinLowEdge(i+1)<<"  ::    "<<cr->GetYaxis()->GetBinLowEdge(j)<<" - "<<cr->GetYaxis()->GetBinLowEdge(j+1)<<setw(q)<<" ::    "<<cr->GetZaxis()->GetBinLowEdge(k)<<" - "<<cr->GetZaxis()->GetBinLowEdge(k+1)<<"    ::   "<<cr->GetBinContent(i,j,k)<<endl;
		  if(k==4 && j==2) cout<<z<<setw(p)<<": "<<cr->GetXaxis()->GetBinLowEdge(i)<<" - "<<cr->GetXaxis()->GetBinLowEdge(i+1)<<"  ::    "<<cr->GetYaxis()->GetBinLowEdge(j)<<" - "<<cr->GetYaxis()->GetBinLowEdge(j+1)<<setw(q)<<" ::    >="<<cr->GetZaxis()->GetBinLowEdge(k)<<"      ::   "<<cr->GetBinContent(i,j,k)<<endl;
		  /* if(k<4 && j==2) cout<<z<<setw(p)<<": "<<cr->GetXaxis()->GetBinLowEdge(i)<<" - "<<cr->GetXaxis()->GetBinLowEdge(i+1)<<"  ::    >="<<cr->GetYaxis()->GetBinLowEdge(j)<<"     ::    >="<<cr->GetZaxis()->GetBinLowEdge(k)<<"      ::   "<<cr->GetBinContent(i,j,k)<<endl; */
	      //		cout<<z<<" : EM Pt = "<<cr->GetXaxis()->GetBinLowEdge(i)<<" : NJets = "<<cr->GetYaxis()->GetBinLowEdge(j)<<" : Qmulti = "<<cr->GetZaxis()->GetBinLowEdge(k)<<" : bin content = "<<cr->GetBinContent(i,j,k)<<endl;
		}
	    }
	cout<<"---------------------------------------------"<<endl;
	
	}
    }
  cr->SetTitle(0);
  cr->Draw("colz text");
  legend2->SetTextSize(0.05);
  legend1->Draw();
  legend2->Draw();
  textOnTop.SetTextSize(0.04);
  intLumiE.SetTextSize(0.04);
  //  if(isPaper) textOnTop.DrawLatexNDC(0.12,0.91,"CMS #it{#bf{Simulation Supplementary}}");                                                                 
  //  textOnTop.DrawLatexNDC(0.12,0.91,"Work in progress");
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

  fr->Write();
  fout->cd();
               
  c1->SaveAs(pdf);
  c1->SaveAs(png);

}

