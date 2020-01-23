#include"TFile.h"
#include"TH1.h"
#include"TVirtualPad.h"
void cutflow(){
  // TFile *f1=new TFile("/home/vinay/work/ROOT_Files/Physics/GMSB_susy/GMSB_skims_ST_RA2b_TreesV12/SignalRegion_v1/SR_Summer16.WJetsToLNu_HT-400To600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8.root");
  // TFile *f2=new TFile("/home/vinay/work/ROOT_Files/Physics/GMSB_susy/GMSB_skims_ST_RA2b_TreesV11/SignalRegion/SR_Spring16.WJetsToLNu_HT-400To600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8.root");

  // TFile *f1=new TFile("/home/vinay/work/ROOT_Files/Physics/GMSB_susy/GMSB_skims_ST_RA2b_TreesV12/SignalRegion_v1/SR_Summer16.TTGJets_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8.root");
  // TFile *f2=new TFile("/home/vinay/work/ROOT_Files/Physics/GMSB_susy/GMSB_skims_ST_RA2b_TreesV11/SignalRegion/SR_Spring16.TTGJets_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8.root");
// gPad->SetGridx(2);
  char* plot_name = new char[200];
  char* plot_name1 = new char[200];
  char* plot_name2 = new char[200];
  char* ext = new char[200];
  char* rootfile = new char[200];
  char* path = new char[200];
  char* path1 = new char[200];
  char* path2 = new char[200];

  char* rootfile1 = new char[200];
  std::string a[20]={"TTJetsHT","TTGJets","WJetsToLNu","ZJetsToNuNu","ZGZJ_NuNuG","QCD","GJets","WGJetsToLNuG","T5bbbbZg_1800_150_FastSim","T5bbbbZg_1800_1750_FastSim"};
  // std::string a[20]={"TTJetsHT","TTGJets","WJetsToLNu","ZJetsToNuNu","ZGZJ_NuNuG","QCD","GJets","WGJetsToLNuG","T5bbbbZg_1800_150_FastSim","T5bbbbZg_1800_1750_FastSim"};

  for(int i=0;i<10;i++) {
  // sprintf(plot_name,"TTJetsHT");
    //  sprintf(plot_name,"TTGJets");
  // sprintf(plot_name2,"TTGJets (After cut)");
  sprintf(ext,"_v17");
  //  sprintf(rootfile,"rootoutput/%s%s.root",plot_name,ext);
  sprintf(rootfile,"../rootoutput/%s%s.root",a[i].c_str(),ext);
  // sprintf(rootfile1,"rootoutput/%s%s.root",plot_name1,ext);

   TCanvas *c1 = new TCanvas("c1", "c1",65,24,1680,1056);
   c1->Range(-1.981819,-20.70421,12.90736,118.2711);
   c1->SetFillColor(0);
   c1->SetBorderMode(0);
   c1->SetBorderSize(2);
   c1->SetGridx();
   c1->SetBottomMargin(0.1489776);
   c1->SetFrameBorderMode(0);
   c1->SetFrameBorderMode(0);

   c1->cd();
  gStyle->SetOptStat(0);  
  // TFile *f1=new TFile("rootoutput/T5bbbbZg_1800_150_FastSim_new.root");
  // TFile *f2=new TFile("rootoutput/T5bbbbZg_1800_150_FastSim_new.root");
  // TFile *f1=new TFile("rootoutput/TChiWg_0_800_FastSim_new.root");
  // TFile *f2=new TFile("rootoutput/TChiWg_0_800_FastSim_new.root");
  // TFile *f1=new TFile("rootoutput/TTJetsHT.root");
  // TFile *f2=new TFile("rootoutput/TTJetsHT.root");
  TFile *f1=new TFile(rootfile);
   TFile *f2=new TFile(rootfile);
  //  TFile *f2=new TFile("/home/vinay/work/ROOT_Files/Physics/GMSB_susy/GMSB_skims_ST_RA2b_TreesV11/SignalRegion/SR_Spring16.QCD_HT700to1000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8.root");
  

  // TH1F *h1=(TH1F*)f1->FindObjectAny("selectBaselineYields_");
  // // TH1F *h2=(TH1F*)f1->FindObjectAny("selectBaselineYields_");

  TH1F *h1=(TH1F*)f1->FindObjectAny("cutflows");
  TH1F *h2=(TH1F*)f2->FindObjectAny("cutflows2");
  // TH1F *h1=(TH1F*)f1->FindObjectAny("nJets");
  // TH1F *h2=(TH1F*)f2->FindObjectAny("nJets");
  // TH1F *h1=(TH1F*)f1->FindObjectAny("MET");
  // TH1F *h2=(TH1F*)f2->FindObjectAny("MET");
  // TH1F *h1=(TH1F*)f1->FindObjectAny("BestPhotonPt");
  // TH1F *h2=(TH1F*)f2->FindObjectAny("BestPhotonPt");
  // TH1F *h1=(TH1F*)f1->FindObjectAny("nBTags");
  // TH1F *h2=(TH1F*)f2->FindObjectAny("nBTags");
  
  //  TH1F *hnew=(TH1F*)h1->Clone("h1new");
  // hnew->Divide(h2);
  // hnew->Draw("text hist");
  // h1->SetTextColor(1);
  // h2->SetTextColor(2);


   TPaveStats *p = new TPaveStats(0.6303725,0.58,0.8710602,0.68,"brNDC");
   p->SetName("stats");
   p->SetBorderSize(1);
   p->SetFillColor(0);
   p->SetTextAlign(12);
   p->SetTextFont(42);
   // p->GetLineWith("Entries")->SetTextColor(1);
   p->SetTextColor(1);
   p->SetLineColor(1);
   // p->Draw();
   h1->GetListOfFunctions()->Add(p);
   p->SetParent(h1);
   h1->SetLineColor(1);
   h1->GetXaxis()->SetRange(1,10);
   h1->GetXaxis()->SetNdivisions(-510);
   h1->Draw("text");


   TPaveStats *p2 = new TPaveStats(0.6289398,0.467167,0.8724928,0.56,"brNDC");
   p2->SetName("stats");
   p2->SetBorderSize(1);
   p2->SetFillColor(0);
   p2->SetTextAlign(12);
   p2->SetTextFont(42);
   p2->SetTextColor(2);
   p2->SetLineColor(1);
   // p2->GetLineWith("Entries")->SetTextColor(2);
   // p2->Draw();
   h2->GetListOfFunctions()->Add(p2);
   p2->SetParent(h2);
   h2->SetLineColor(2);
   // h2->Draw("hist sames");
  //  TH1F *hnew=(TH1F*)h1->Clone("h1new");
  // hnew->Divide(h2);
  // hnew->Draw("text");
  // gStyle->SetPaintTextFormat(".2f");

   
  TLegend* legends = new TLegend(0.52, 0.70, 0.9, 0.8,"","brNDC"); // the numbers determine the position of the box 
  legends->SetFillColor(0); 
  // legends->SetHeader(legendname); 
  legends->AddEntry(h1,a[i].c_str(),"");//(name of hist,what you want it called in legend, l=line, p=polymarker, f=boxy thing ) 
  //  legends->AddEntry(h2,plot_name1,"l");
  //  legends->AddEntry(h__2,plot_name2,"l");
  legends->SetTextSize(0.035);
   //   legends->SetMarkerStyle(1);
  legends->Draw();

   sprintf(path,"../plots/pdf/%s_%s_cutflow1.pdf",a[i].c_str(),ext);
   sprintf(path1,"../plots/png/%s_%s_cutflow1.png",a[i].c_str(),ext);
   sprintf(path2,"../plots/gif/%s_%s_cutflow1.gif",a[i].c_str(),ext);
   c1->SaveAs(path);
   c1->SaveAs(path1);
   c1->SaveAs(path2);

  }

}

