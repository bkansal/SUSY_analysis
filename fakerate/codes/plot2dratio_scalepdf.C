////////////////////// For printing scale and pdf systematics /////////////////////
#include <vector>
#include <numeric>
#include <iostream>
void plot2dratio_scalepdf(TString ext,TString year="full_Run2", bool lowdphi=false)
{
  gStyle->SetPalette(1);
  gStyle->SetOptStat(0);
  TString path,path1,name,filename,filename1;
  TString varName;
  double n=1;
  if(ext.Contains("_scale")) {n=9; varName="PhoPtQMultJet";}
  if(ext.Contains("_pdf")) {n=101; varName="PhoPtQMultJet";}
  else varName="PhoPtQMultJet";
  if(lowdphi)
    {
      path="rootout/fake_rate_v10_afterbtagSF/FR_using_PhoPtQmulti_csv_cut_EMObjeta_qmulti_METCaloMET_nopxveto_noSF_bSF_lowdphi_newbin2/";
      path1="rootout/fake_rate_v10_afterbtagSF/FR_using_PhoPtQmulti_csv_cut_EMObjeta_qmulti_METCaloMET_nopxveto_noSF_bSF_lowdphi_scalepdf_newbin2/";
      
      name=year+ext+"_lowdphi";
    }
  else
    {
      //path="rootout/fake_rate_v10_afterbtagSF/FR_using_PhoPtQmulti_csv_cut_EMObjeta_qmulti_METCaloMET_nopxveto_noSF_bSF_newbin2/";
      //      path1="rootout/fake_rate_v10_afterbtagSF/FR_using_PhoPtQmulti_csv_cut_EMObjeta_qmulti_METCaloMET_nopxveto_noSF_bSF_scalepdf_newbin2/";
      path="rootout/new_v2/";
      path1="rootout/scalepdf/";
      name=year+ext;
    }
  TString rootout=name+".root";
  TString pdf=name+".pdf";
      

  if(year=="full_Run2")
    {
      filename=path+"TTWGJ_CR_v18.root";
      filename1=path1+"TTWGJ_CR_v18.root";
    }
  else
    {
      filename=path+"TTWGJ_"+year+"_CR_v18.root";
      filename1=path1+"TTWGJ_"+year+"_CR_v18.root";
    }
  TFile *f1 = new TFile(filename);
  TFile *f2 = new TFile(filename1);

  TFile *fout =new TFile(rootout,"recreate");
  fout->cd();
  int  ext2=2;
  //  TH2D *max= new TH2D("Max","Maximum uncerntainty",10,0,10,10,0,10);
  vector<double> max;
  cout<<"Root file name = "<<rootout<<endl;
  for(int ext2=0; ext2<n; ext2++)
    {
      TString varName0=varName+ext+"_elec0_"+ext2;
      TString varName1=varName+ext+"_"+ext2;
      if(ext=="_scale" || ext=="_pdf"){
	varName0=varName+ext+"_elec0_"+ext2;
	varName1=varName+ext+"_"+ext2;
      }
      else{
	varName0=varName+ext+"_elec0";
        varName1=varName+ext;
      }

 
      cout<<"SR : "<<varName0<<endl;
      cout<<"CR : "<<varName1<<endl;

      TH2D *cr = (TH2D*)f1->Get(varName1);
      TH2D *sr = (TH2D*)f1->Get(varName0);
      TH2D *cr2 = (TH2D*)f2->Get(varName1);
      TH2D *sr2 = (TH2D*)f2->Get(varName0);

      //      if(ext2==0) sr->Print("all");
      //      if(ext2==0) cr->Print("all");
      TH2D *fr = (TH2D*)sr->Clone("fr");
      fr->Divide(cr);
      if(ext2==0) fr->Print("all");    
      TH2D *fr2 = (TH2D*)sr2->Clone("fr2");
      fr2->Divide(cr2);
      
      if(ext2==0) fr2->Print("all");
            
      fr->GetXaxis()->SetTitle("Bin no.");
      if(ext=="_scale")
	{
	  name="FRwithscale_unc"+std::to_string(ext2);
	  //	  fr2->Write(name);

	  fr->GetYaxis()->SetTitle("Scale factor index");
	  fr->GetYaxis()->SetRangeUser(1,9);
	  fr->GetXaxis()->SetRangeUser(1,11);
	  fr->SetMarkerSize(1.3);

	  fr2->GetYaxis()->SetTitle("Scale factor index");
	  fr2->GetYaxis()->SetRangeUser(1,9);
	  fr2->GetXaxis()->SetRangeUser(1,11);
	  fr2->GetYaxis()->SetRangeUser(1,9);
      
	  //	  fr2->GetZaxis()->SetRangeUser(0.8,1.2);
	  fr2->SetMarkerSize(1.3);
	  name="Scaleratio"+ext+ext2;
	}
      if(ext=="_pdf")
	{

	  name="FRwithpdf_unc"+std::to_string(ext2);
	  //	  fr2->Write(name);

	  fr->GetYaxis()->SetTitle("PDF factor index");
	  fr->GetYaxis()->SetRangeUser(1,100);
	  fr->GetXaxis()->SetRangeUser(1,11);
	  
	  fr2->GetYaxis()->SetTitle("PDF factor index");
	  fr2->GetYaxis()->SetRangeUser(1,100);
	  fr2->GetXaxis()->SetRangeUser(1,11);
	  
	  name="PDFratio"+ext+ext2;
	  //	  fr2->GetZaxis()->SetRangeUser(0.8,1.2);
	  fr2->SetMarkerSize(1.3);
	}
  
      fr2->Add(fr,-1);
      fr2->Divide(fr);
      fout->cd();
      fr2->Write(name);
      //      if(ext2==34) fr2->Draw("colz text");
      cout<<"Scale = N(with scale unc.)/N(nominal value) : "<<abs(fr2->GetMaximum())<<endl;
      //      max->Fill(ext2,fr2->GetMaximum());
      if(ext2==34) max.push_back(0);
      else
	max.push_back(abs(fr2->GetMaximum()));

    }

   cout<<" Maximum uncertainty = "<<*max_element(max.begin(), max.end())<<endl;
   float average = accumulate( max.begin(), max.end(), 0.0)/max.size();              
   cout<<" Average uncertainty = "<<average<<endl;

 
}
