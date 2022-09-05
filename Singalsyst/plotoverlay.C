#include"TH3.h"
#include"TH2.h"
#include"TH1.h"


void plotoverlay(TString signal="T5bbbbZg", int mGl = 2200 , int mNLSP =200, TString sys="scale",TString sys2="default",TString year="full_Run2",int xmin=1,int xmax=46)
{
  TLatex textOnTop,intLumiE;
  TFile *f1, *f2,*f3;
  double ymin_=0.9 , ymax_=1.1;
  int ymin=0.0 , ymax=1;
  TString sample="FastSim_"+signal+"_"+to_string(mGl)+"_"+to_string(mNLSP);
  TString path1=sample+"_noscale_v18.root";
  TString path2=sample+"_scale_v18.root";
  TString varname="AllSBins_v7_CD_SP";
  TString filename,filename1,filename2;
  TString pdf,png;
  char* sname = new char[200];
  if(sys == "scale") {
    varname="AllSBins_v7_CD_SP_scale";
    ymin=0,ymax=9;
    pdf="../plots/pdf/LL/LL_scale.pdf";
    png="../plots/png/LL/LL_scale.png";
    pdf="plots/"+signal+"/"+signal+"_"+to_string(mGl)+"_"+to_string(mNLSP)+"_scale.pdf";
    png="plots/"+signal+"/"+signal+"_"+to_string(mGl)+"_"+to_string(mNLSP)+"_scale.png";
  }
  if(sys == "pdf") {
    varname="AllSBins_v7_CD_SP_pdf";
    ymin=0,ymax=3;
    pdf="../plots/pdf/LL/LL_PDF_"+to_string(ymin)+"to"+to_string(ymax)+".pdf";
    png="../plots/png/LL/LL_PDF_"+to_string(ymin)+"to"+to_string(ymax)+".png";
    pdf="plots/"+signal+"_"+to_string(mGl)+"_"+to_string(mNLSP)+"_pdf.pdf";
    png="plots/"+signal+"_"+to_string(mGl)+"_"+to_string(mNLSP)+"pdf.png";
  }
  if(year == "full_Run2")
    {
      filename1  = path1;
      filename2  = path2;
    }
  else
    {
      filename1= path1+"TTWGJ_"+year+"_CR_v18.root";
      filename2= path2+"TTWGJ_"+year+"_CR_v18.root";
    }
  f1 = new TFile(filename1);
  f2 = new TFile(filename2);
  TH2D *cr_,*sr_,*cr1_,*sr1_,*cr2_,*sr2_;
  TCanvas *c1;
  double nbin,bin0=0, bin1=46,yset_;
  TH1D *scale_[100],*scale2_[100],*tf;
  int rebin=1;
  TString varname0=varname+"_elec0";
  gStyle->SetOptStat(0);
  c1 = new TCanvas("stackhist","stackhist",800,600);
  c1->cd();
  c1->SetGridx();
  
  sr1_          = (TH2D*)f1->Get(varname0);
  sr2_          = (TH2D*)f2->Get(varname0);

  sr1_->GetXaxis()->SetRangeUser(xmin,xmax);
  sr2_->GetXaxis()->SetRangeUser(xmin,xmax);
  sr1_->GetYaxis()->SetRangeUser(ymin,ymax);
  sr2_->GetYaxis()->SetRangeUser(ymin,ymax);
  
  sprintf(sname,"Px_%d",ymin);
  scale_[ymin]=sr2_->ProjectionX("Px_%d",0,1);
  scale2_[ymin]=sr2_->ProjectionX("Px_%d",0,1);

  for(int i=1; i<46; i++)
    {
      scale_[ymin]->SetBinError(i,sr1_->GetBinError(i));
      scale2_[ymin]->SetBinError(i,sr1_->GetBinError(i));
    }
  ///////////////////////////////// Average TF wrt Scale/PDF //////////////////////////////////////////////
  float average[100];
  double error[100];
  TH1F *avg_TF=new TH1F("avg_TF","Average TF for scale uncertainties",ymax,ymin,ymax);
  //  if(sys2=="avgTF"){
  //  scale2_[0]->Print("all");
  vector<double> max;

  for(int i=ymin;i<ymax;i++)
      {
	sprintf(sname,"Px_%d",i);
	scale2_[i]=sr2_->ProjectionX(sname,i,i+1);
	if(i>ymin) {
	  scale2_[i]->Add(scale2_[i-1],-1);
	}

	//	scale2_[i]->Print("all");
	average[i]=0;
	error[i]=0;                                                                                                                                                         
	for(int j=1; j<46; j++)
	  {

	    average[i] += scale2_[i]->GetBinContent(j);
	    error[i] += scale2_[i]->GetBinError(j);
	  }
	
	cout<<" Average uncertainty = "<<average[i]/10<<" , error = "<<error[0]/10<<endl;    
	avg_TF->Fill(i,average[i]/10);
	//	max.push_back(average[i]/10);
      }

    for(int j=ymin; j<ymax; j++)
      {
	//	avg_TF->SetBinContent(j+1,(average[0]-average[j])/10);
	avg_TF->SetBinContent(j+1,average[j]/10);
	avg_TF->SetBinError(j+1,error[0]/10);
      }
    //  }
    /////////////////////////////////////////////////////////////////////////////////////////

  for(int i=ymin;i<ymax;i++)
    {
      sprintf(sname,"Px_%d",i);
      scale_[i] = (TH1D*)scale2_[i]->Clone(sname);
      scale_[i]->Scale(1.0/scale_[i]->Integral());
      scale2_[i]->Scale(1.0/scale2_[i]->Integral());
      scale_[i]->Divide(scale2_[ymin]);

      if(i==ymin) {
	scale_[i]->GetYaxis()->SetRangeUser(ymin_,ymax_);
	if(sys=="scale") scale_[i]->GetYaxis()->SetTitle("#mu_{R}, #mu_{F} variation wrt nominal");
        if(sys=="pdf") scale_[i]->GetYaxis()->SetTitle("PDF variation wrt nominal");
	scale_[i]->GetXaxis()->SetTitle("TF bins");
	scale_[i]->SetTitle(0);
	scale_[i]->SetMarkerStyle(7);
	scale_[i]->SetFillStyle(3009);
	scale_[i]->SetFillColor(kGray);
	scale_[i]->Draw("E2");
      }
      else {
	if(i==8) scale_[i]->SetLineColor(i+3);
	else  scale_[i]->SetLineColor(i);
	scale_[i]->SetLineWidth(2);
	scale_[i]->Draw("sames hist");
      }
      //      scale_[i]->Print("all");
    }
  
  double total=0;
  for(int j=1;j<46;j++)
    {
      total = 0;
      for(int i=ymin;i<ymax;i++)
	{
	  total += ((1-scale_[i]->GetBinContent(j))/ymax); 
	}
      max.push_back(total);
    }
  float ave = accumulate( max.begin(), max.end(), 0.0)/max.size();
  cout<<" Maximum uncertainty in 45 bins = "<<*max_element(max.begin(), max.end())<<endl;
  cout<<" Average uncertainty in 45 bins = "<<ave<<endl;                                                                                                                   

  double ymin2_=ymin_+ 0.04;
  double ymax2_=ymax_- 0.04;
  TLine *line1V6=new TLine( 8,ymin2_,  8,ymax2_);
  TLine *line2V6=new TLine(14,ymin2_, 14,ymax2_);
  TLine *line3V6=new TLine(19,ymin2_, 19,ymax2_);
  TLine *line4V6=new TLine(24,ymin2_, 24,ymax2_);
  TLine *line5V6=new TLine(29,ymin2_, 29,ymax2_);
  TLine *line6V6=new TLine(34,ymin2_, 34,ymax2_);
  TLine *line7V6=new TLine(40,ymin2_, 40,ymax2_);
  
  
  line1V6->Draw();      line2V6->Draw();  line3V6->Draw();
  line4V6->Draw();      line5V6->Draw();
  line6V6->Draw();      line7V6->Draw();

  
  double yset=(ymax_+ymin_)/2.1;
  cout<<"yset = "<<yset<<endl;
  TArrow *arrow1 = new TArrow( 1, yset, 8, yset,0.01,"<|>");
  TArrow *arrow2 = new TArrow( 8, yset, 14, yset,0.01,"<|>");
  TArrow *arrow3 = new TArrow( 14, yset, 19, yset,0.01,"<|>");
  TArrow *arrow4 = new TArrow( 19, yset, 24, yset,0.01,"<|>");
  TArrow *arrow5 = new TArrow( 24, yset, 29, yset,0.01,"<|>");
  TArrow *arrow6 = new TArrow( 29,yset, 34,yset,0.01,"<|>");
  TArrow *arrow7 = new TArrow( 34,yset, 40,yset,0.01,"<|>");
  TArrow *arrow8 = new TArrow( 40,yset, 46,yset,0.01,"<|>");
  //  TArrow *arrow9 = new TArrow( 45, yset, 10, yset,0.01,"<|>");
  //TArrow *arrow10 = new TArrow( 10,yset, 11,yset,0.01,"<|>");
  TArrow *arrow11 = new TArrow( 1,yset*0.97, 34,yset*0.97,0.01,"<|>");
  TArrow *arrow12 = new TArrow( 34,yset*0.97, 46,yset*0.97,0.01,"<|>");

  arrow1->Draw(); arrow2->Draw(); arrow3->Draw();
  arrow4->Draw();
  arrow5->Draw(); arrow6->Draw();
  arrow7->Draw(); arrow8->Draw();
  //arrow9->Draw(); arrow10->Draw();
  arrow11->Draw(); arrow12->Draw();
  yset=(ymax_+ymin_)/2.085;
  cout<<"yset = "<<yset<<endl;
  TLatex Tl,T2;
  Tl.SetTextSize(0.035);
  T2.SetTextSize(0.035);
  Tl.DrawLatex(3.25,yset,"N^{ 0}_{ 2-4}");
  //  Tl.DrawLatex(8.25,yset,"N^{ 0}_{ 3}");
  //Tl.DrawLatex(14.25,yset,"N^{ 0}_{ 4}");
  Tl.DrawLatex(11.25,yset,"N^{ 0}_{ 5-6}");
  Tl.DrawLatex(16.25,yset,"N^{ 0}_{ #geq7}");
  Tl.DrawLatex(21.25,yset,"N^{ #geq1}_{ 2-4}");
  Tl.DrawLatex(26.25,yset,"N^{ #geq1}_{ 5-6}");
  Tl.DrawLatex(31.25,yset,"N^{ #geq1}_{ #geq7}");
  Tl.DrawLatex(36.25,yset,"W tag");
  Tl.DrawLatex(42.25,yset,"H tag");
  T2.DrawLatex(4.5,yset*0.97,"SP region");
  T2.DrawLatex(39.5,yset*0.97,"EW region");

  TLegend *legend = new TLegend(0.1,0.7,0.38,0.9);
  if(sys=="scale") {
    legend->SetNColumns(3);
    legend->SetTextSize(0.05);
  }
  if(sys=="pdf") {
    legend = new TLegend(0.1,0.65,0.9,0.9);
    legend->SetNColumns(10);
  legend->SetTextSize(0.021);
  }
  TLegend *legend1 = new TLegend(0.6,0.8,0.9,0.9);
  legend1->SetNColumns(1);
  legend1->SetBorderSize(1);
  legend1->SetTextSize(0.035);

  TString title= signal+"_"+to_string(mGl)+"_"+to_string(mNLSP)+" : " +sys;
  legend1->SetHeader(title,"C");
  legend1->Draw();

  for(int i=ymin;i<ymax;i++){
    if(i==ymin) sprintf(sname,"nominal");
    else
      sprintf(sname,"index_%d",i);
    legend->AddEntry(scale_[i],sname,"lp");	  
  }

  //  legend->Draw();

  if(sys2=="avgTF")
    {
      avg_TF->SetTitle(0);
       avg_TF->GetYaxis()->SetRangeUser(0.6,1.4);
      avg_TF->GetYaxis()->SetTitle("Average TF for scale uncertainties");
      if(sys=="pdf") {avg_TF->GetYaxis()->SetTitle("Average TF for PDF uncertainties");avg_TF->GetXaxis()->SetTitle("PDF Weight index"); avg_TF->Draw("E0"); pdf ="LL_avgTFPDF_0to100.pdf"; png ="LL_avgTFPDF_0to100.png";}
      if(sys=="scale") {avg_TF->SetMarkerColor(kRed);avg_TF->SetMarkerSize(1.7);avg_TF->GetXaxis()->SetTitle("scale Weight index"); avg_TF->Draw("E0 text"); pdf ="LL_avgTFscale_0to100.pdf"; png ="LL_avgTFscale_0to100.png";}
    }

  textOnTop.SetTextSize(0.04);
  intLumiE.SetTextSize(0.04);
  textOnTop.DrawLatexNDC(0.12,0.91,"CMS #it{#bf{Simulation Preliminary}}"); 
  intLumiE.DrawLatexNDC(0.7,0.91,"#bf{137 fb^{-1} (13 TeV)}");

  

  c1->SaveAs(pdf);
  c1->SaveAs(png);

}
