void plot2dratio_scalepdf(TString varName,TString ext,TString year="full_Run2", bool lowdphi=false)
{
  gStyle->SetPalette(1);
  gStyle->SetOptStat(0);
  TString path,path1,name,filename,filename1,filename2,filename3,path2;
  
  if(lowdphi)
    {
      path="../rootoutput/v8_btagSF_scalepdf/withphicut_zmass60to120_data/";
      path1="../rootoutput/v8_btagSF_scalepdf/withphicut_zmass60to120_data/";


      name=ext+"_"+year+"_lowdphi";
    }
  else
    {
      path="../rootoutput/v7_btagSFv2/withphicut_zmass60to120_data_PF/";
      path1="../rootoutput/v8_btagSF_scalepdf/withphicut_zmass60to120_data_PF/";

      name=ext+"_"+year;
    }
  TString rootout=name+".root";
  TString pdf=name+".pdf";
  int n=1;
  TFile *fout =new TFile(rootout,"recreate");
  fout->cd();
  if(year=="full_Run2")
    {
      
      filename1=path+"ZJZGToLL_CR_v18.root";
      filename3=path1+"ZJZGToLL_CR_v18.root";
      filename=path+"Run2_METdata_CR_v18.root";                                                                                                                           
      filename2=path1+"Run2_METdata_CR_v18.root";                                    
      
      /*
      filename=path+"ZJZGToLL_CR_v18.root";
      filename2=path1+"ZJZGToLL_CR_v18.root";
      filename1=path+"TTWZJZGToLL_CR_v18.root";
      filename3=path1+"TTWZJZGToLL_CR_v18.root";                                       
      */
    }
  else
    {
      /*
      filename1=path+"ZJZGToLL_"+year+"_CR_v18.root";
      filename3=path1+"ZJZGToLL_"+year+"_CR_v18.root";
      filename=path+"Run"+year+"_METdata_CR_v18.root";
      filename2=path1+"Run"+year+"_METdata_CR_v18.root";
      */
        
      filename=path+"ZJZGToLL_"+year+"_CR_v18.root";
      filename2=path1+"ZJZGToLL_"+year+"_CR_v18.root";
      filename1=path+"TTWZJZGToLL_"+year+"_CR_v18.root";
      filename3=path1+"TTWZJZGToLL_"+year+"_CR_v18.root";
      
    }
  TFile *f1 = new TFile(filename);
  TFile *f2 = new TFile(filename1);
  TFile *f3 = new TFile(filename2);
  TFile *f4 = new TFile(filename3);

  TString varName0=varName+"_"+ext;
  TString varName1=varName+"_"+ext;

  TH2D *cr = (TH2D*)f2->Get(varName1);
  TH2D *sr = (TH2D*)f1->Get(varName0);
  TH2D *cr2 = (TH2D*)f4->Get(varName1);
  TH2D *sr2 = (TH2D*)f3->Get(varName0);


  fout->cd();
  name="CR_no"+ext;
  cr->Write(name);
  name="SR_no"+ext;
  sr->Write(name);
  name="CR_"+ext;
  cr2->Write(name);
  name="SR_"+ext;
  sr2->Write(name);

  //  cr->Draw();

  TH2D *fr = (TH2D*)sr->Clone("fr");
  fr->Divide(cr);
  name="TFratio";
  fr->Write(name);
  TH2D *fr2 = (TH2D*)sr2->Clone("fr2");
  fr2->Divide(cr2);
  name="TFratio_"+ext;
  fr2->Write(name);

  fr->GetXaxis()->SetTitle("Bin no.");
  if(ext=="scale")
    {
      fr->GetYaxis()->SetTitle("Scale factor index");
      fr->GetYaxis()->SetRangeUser(0,9);
      fr->GetXaxis()->SetRangeUser(1,3);
      fr->SetMarkerSize(1.3);

      fr2->GetYaxis()->SetTitle("Scale factor index");
      fr2->GetYaxis()->SetRangeUser(0,9);
      fr2->GetXaxis()->SetRangeUser(1,3);

      //      fr2->GetZaxis()->SetRangeUser(0.8,1.2);
      fr2->SetMarkerSize(1.3);


      name="Scaleratio_"+ext;

      n=10;
    }
  if(ext=="pdf")
    {
      fr->GetYaxis()->SetTitle("PDF factor index");
      fr->GetYaxis()->SetRangeUser(1,100);
      fr->GetXaxis()->SetRangeUser(1,3);

      fr2->GetYaxis()->SetTitle("PDF factor index");
      fr2->GetYaxis()->SetRangeUser(1,100);
      fr2->GetXaxis()->SetRangeUser(1,3);
      name="PDFratio_"+ext;
      fr2->GetZaxis()->SetRangeUser(0.8,1.2);
      fr2->SetMarkerSize(1.3);
      n=100;
    }
  
  fr2->Divide(fr);
  fr2->Write(name);
  fr->Draw();

  vector<float> max;
  for(int i=1; i<3 ; i++)
    for(int j=1; j<n ; j++)
      {
	cout<<i<<" : "<< j<<" : "<<abs(1-fr2->GetBinContent(i,j))<<endl;
	max.push_back(abs(1-fr2->GetBinContent(i,j)));
      }
  float average = accumulate( max.begin(), max.end(), 0.0)/max.size();
  cout<<" Maximum uncertainty = "<<*max_element(max.begin(), max.end())<<endl;
  cout<<" Average uncertainty = "<<average<<endl;

  fr2->Draw("colz text");  
    
}
