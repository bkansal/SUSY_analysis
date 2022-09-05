void plotsys_pred(TString sys="JECup",TString year="full_Run2",int xmin=1,int xmax=5)
{
  // gStyle->SetOptStat(0);
    gStyle->SetPalette(1);

 bool data_pred=false;
 TFile *f1, *f2,*f3, *fout;
 TString lep="LM";
 TString path1;
 TString path2;
 TString rootout;
 TCanvas *c1;
 if(sys=="EWKcorr")
   {
     c1 = new TCanvas("stackhist","stackhist",800,600);
     path1="rootoutput/v6/withphicut_zmass60to120/";
     TString varName="AllSBins_v6_CD_EW_50bin_elec1_closure"; xmin=0,xmax=51;
     TString filename1  = path1+"ZJZGTo2Nu_CR_v18.root";
     f2 = new TFile(filename1);
     TH1D *sr1= (TH1D*)f2->Get(varName);
     TH1D *JERC = new TH1D("JERC","JERC systematics",52,0,52) ;
     rootout="Zinvi_EWKcorr_v2.root";
     fout =new TFile(rootout,"recreate");
     fout->cd();
     for(int i=1; i<=46; i++)
       {
         if(i==1 || i==8 || i==14 || i==19 || i==24 || i==29 || i==34 || i==40 ) {JERC->SetBinContent(i+1,sr1->GetBinContent(i+1));JERC->SetBinError(i+1,0.18*sr1->GetBinContent(i+1));}
         else if(i==2 || i==9 || i==15 || i==20 || i==25 || i==30 || i==35 || i==41) {JERC->SetBinContent(i+1,sr1->GetBinContent(i+1));JERC->SetBinError(i+1,0.20*sr1->GetBinContent(i+1));}
         else if(i==3 || i==10 || i==16 || i==21 || i==26 || i==31 || i==36 || i==42) {JERC->SetBinContent(i+1,sr1->GetBinContent(i+1));JERC->SetBinError(i+1,0.25*sr1->GetBinContent(i+1));}
         else if(i==4 || i==5 || i==11 || i==12 || i==17 || i==18 || i==22 || i==23 || i==27 || i==28 || i==32 || i==33 || i==37 || i==38 || i==43 || i==44) {JERC->SetBinContent(i+1,sr1->GetBinContent(i+1));JERC->SetBinError(i+1,0.35*sr1->GetBinContent(i+1));}
         else if(i==6 || i==7 || i==13 || i==39 || i==45) {JERC->SetBinContent(i+1,sr1->GetBinContent(i+1));JERC->SetBinError(i+1,0.4*sr1->GetBinContent(i+1));}
         else {JERC->SetBinContent(i+1,0);JERC->SetBinError(i+1,0*sr1->GetBinContent(i+1));}
       }
     JERC->Write();
     sr1->Print("all");
     JERC->Print("all");
   }
 else if(sys=="lepSF"|| sys=="JECup" || sys=="JERup")
   {
     
     if(sys=="JECup")
       {
	 path1="rootoutput/noJERC/withphicut_zmass60to120_data_PF/";
	 path2="rootoutput/JECup/withphicut_zmass60to120_data_PF/";
	 rootout="Zinvi_JECup_v2.root";
       }
     else if(sys=="JERup")
       {
	 path1="rootoutput/noJERC/withphicut_zmass60to120_data_PF/";
	 path2="rootoutput/JERup/withphicut_zmass60to120_data_PF/";
	 rootout="Zinvi_JERup_v2.root";
       }
     else if(sys=="lepSF")
       {
	 path1="rootoutput/v6/withphicut_zmass60to120/";
	 path2="rootoutput/v6_puritysys/withphicut_zmass60to120_data_PF/";
	 rootout="Zinvi_PFup_v2.root";
	 
       }
     
     else {
       cout<<" for JECup systematics : JECup"<<endl;
       cout<<" for JERup systematics : JERup"<<endl;
       cout<<" for lepSF systematics : lepSF"<<endl;
       
     }
     TLatex textOnTop,intLumiE;
     
     TString filename,filename1,filename2;
     if(year == "full_Run2")
       {
	 filename1  = path1+"ZJZGTo2Nu_CR_v18.root";
	 filename2  = path2+"ZJZGTo2Nu_CR_v18.root";
       }
     else
       {
	 filename1= path1+"ZJZGTo2Nu_"+year+"_CR_v18.root";
	 filename2= path2+"ZJZGTo2Nu_"+year+"_CR_v18.root";
       }
     f2 = new TFile(filename1);
     f3 = new TFile(filename2);
     
     double ymin=-0.2 , ymax=0.2, ymin_=-200 , ymax_=1600;
     
     TH1D *cr,*sr,*tf,*pred_sr,*cr1,*sr1,*cr2,*sr2;
     
     double nbin,bin0=0, bin1=46,yset_;
     TH1D *total;
     int rebin=1;
  //  TString varName="AllSBins_v6_CD";
  //   TString varName="AllSBins_v6_CD_EW_7bin_elec1_closure";
     TString varName="AllSBins_v6_CD_EW_50bin_elec1_closure"; xmin=0,xmax=51;
     //  TString varName="METvBin2"; xmin=200,xmax=2000;
     //  TString varName="nJets"; xmin=2,xmax=20;
     
     gStyle->SetOptStat(0);
     c1 = new TCanvas("stackhist","stackhist",800,600);
     sr1          = (TH1D*)f2->Get(varName);
     sr2          = (TH1D*)f3->Get(varName);
  

     //AllSBins_v6_CD_EW_7bin_elec1_closure  
  //  sr2->Divide(sr2);
     TPad *pad1 = new TPad("pad1","pad1",0,0,1,1);
     pad1->SetBottomMargin(0);
     pad1->SetBottomMargin(0.3);
  pad1->Draw();pad1->SetGridx();
  pad1->cd();
  //  pad1->SetLogy();
  
  //  sr->GetXaxis()->SetRangeUser(xmin,xmax);
  sr1->GetXaxis()->SetRangeUser(xmin,xmax);
  sr2->GetYaxis()->SetLabelSize(0.07);
  sr1->GetYaxis()->SetTitle("N(Pred.)");
  sr1->GetYaxis()->SetTitleSize(0.04);
  sr1->GetYaxis()->SetTitleOffset(0.92);
  sr1->GetYaxis()->SetRangeUser(ymin_,ymax_);
  //  sr2->GetYaxis()->SetRangeUser(ymin_,ymax_);
  sr2->SetMarkerStyle(20);
  sr2->SetMarkerSize(0.7);
  sr2->SetMarkerColor(kRed);
  sr2->SetLineColor(kRed);
  sr1->SetMarkerStyle(20);
  sr1->SetMarkerSize(0.7);
  sr1->SetMarkerColor(kBlue);
  sr1->SetLineColor(kBlue);
  sr1->SetTitle(0);
  sr1->GetXaxis()->SetNdivisions(5);

  sr1->Draw();
  sr2->Draw("same");

  textOnTop.SetTextSize(0.04);
  intLumiE.SetTextSize(0.04);
  textOnTop.DrawLatexNDC(0.12,0.91,"CMS #it{#bf{Simulation Preliminary}}");
  intLumiE.DrawLatexNDC(0.7,0.91,"#bf{137 fb^{-1} (13 TeV)}");

  double yset=(ymax_+ymin_)/1.8;
  cout<<"yset = "<<yset<<endl;
  TArrow *arrow1 = new TArrow( 1, yset, 2, yset,0.01,"<|>");
  TArrow *arrow2 = new TArrow( 2, yset, 3, yset,0.01,"<|>");
  TArrow *arrow3 = new TArrow( 3, yset, 4, yset,0.01,"<|>");
  TArrow *arrow4 = new TArrow( 4, yset, 5, yset,0.01,"<|>");
  TArrow *arrow5 = new TArrow( 1, yset*1.25, 3, yset*1.25,0.01,"<|>");
  TArrow *arrow6 = new TArrow( 3, yset*1.25, 5, yset*1.25,0.01,"<|>");
  arrow1->Draw(); arrow2->Draw(); arrow3->Draw();
  arrow4->Draw();
  arrow5->Draw(); arrow6->Draw();

  yset=(ymax_+ymin_)/1.6;
  cout<<"yset = "<<yset<<endl;
  TLatex Tl,T2;
  Tl.SetTextSize(0.04);
  T2.SetTextSize(0.04);
  Tl.DrawLatex(1.25,yset,"N_{0 b-Tag}");
  Tl.DrawLatex(2.25,yset,"N_{>0 b-Tag}");
  Tl.DrawLatex(3.25,yset,"W tag");
  Tl.DrawLatex(4.25,yset,"H tag");
  T2.DrawLatex(1.5,yset*1.15,"SP region");
  T2.DrawLatex(3.5,yset*1.15,"EW region");
  
  
  TLegend *legend = new TLegend(0.1,0.83,0.35,0.9);
  TString title,title1;
  title1="#frac{#Delta TF(sys)}{TF_{nominal}}";

  if (sys=="lepSF") title="Scale factor sys.";
  else if(sys=="JECup")title="JEC sys.";
  else if(sys=="JERup")title="JER sys.";
  legend->SetHeader(title,"C");
  legend->SetTextSize(0.04);
  legend->Draw();
  
  TLegend *legend1 = new TLegend(0.6,0.78,0.9,0.9);
  legend1->AddEntry(sr1,"nominal","lp");
  legend1->AddEntry(sr2,"nominal + sys","lp");
  legend1->SetTextSize(0.04);
  legend1->Draw();
  
  TH1D *h3 = (TH1D*)sr1->Clone("h3");
  TH1D *h4 = (TH1D*)sr2->Clone("h4");
  h3->Add(h4,-1);
  TH1D *pull = (TH1D*)h3->Clone("pull");
  TH1D *sr1_ = (TH1D*)sr1->Clone("sr1_");                                                                                                                                                                  
  TH1D *pull2 = (TH1D*)h3->Clone("pull2");
  for(int i=0 ; i<xmax; i++)
    pull->SetBinContent(i,0);
  
  TPad *pad2 = new TPad("pad2","pad2",0,0.0,1,0.35);
  pad2->Draw();
  pad2->SetTopMargin(0);
  pad2->SetBottomMargin(0.35);
  pad2->cd();
  pad2->SetGridx();
  
  pull->Sumw2();
  pull->SetStats(0);      // No statistics on lower plot                                                                       
  pull->SetTitle(0);
  pull2->Divide(sr1_);
      
  //  pull->Add(h4,-1);
  for(int i=0 ; i<xmax; i++)
    {
      pull->SetBinError(i,sr1->GetBinError(i)/sr1->GetBinContent(i));
      pull2->SetBinError(i,0);
    }
  pull->SetMarkerColor(kBlack);
  pull->SetLineColor(kBlack);
  pull->GetXaxis()->SetTitle("Bin no.");
  pull->GetXaxis()->SetTitleOffset(0.8);
  pull->GetXaxis()->SetTitleSize(0.18);
  pull->GetXaxis()->SetLabelSize(0.12);
  pull->GetYaxis()->SetTitle(title1);
  pull->GetYaxis()->SetTitleSize(0.08);
  pull->GetYaxis()->SetTitleOffset(0.50);
  pull->GetYaxis()->SetLabelSize(0.09);

  pull->GetYaxis()->SetNdivisions(5);
  pull->GetXaxis()->SetNdivisions(5);
  pull->SetFillColor(kGray);
 
  pull->SetFillColor(kGray);
  pull->SetMarkerColor(kGray);

  //      pull->SetLineColor(0);
  pull->Draw("E2");
  pull2->SetMarkerColor(kBlack);


  pull2->Draw("same ep");



  TLine *line= new TLine(xmin,0,xmax,0);
  line->SetLineColor(1);
  line->SetLineStyle(1);
  line->SetLineWidth(1);
  line->Draw();
  //  sr2->Draw("same");

  cout<<"Systematics : "<<endl;
  for(int i=0 ; i<47; i++)
    cout<<abs(pull2->GetBinContent(i))<<endl;
  TH1D *JERC = new TH1D("JERC","JERC systematics",52,0,52) ;
  if((sys=="JECup" || sys=="JERup" || sys=="lepSF"))
    {
      fout =new TFile(rootout,"recreate");
      fout->cd();
      for(int i=1; i<=46; i++)
	{JERC->SetBinContent(i,abs(sr1->GetBinContent(i))); JERC->SetBinError(i,abs(h3->GetBinContent(i)));}
	
      JERC->Write();

    }
   }
 TString name="pdf/Zin_"+sys+".pdf";
 c1->SaveAs(name);
 name="png/Zin_"+sys+".png";
 c1->SaveAs(name);

}
