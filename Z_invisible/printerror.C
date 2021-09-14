void printerror(TString year)
{
  TFile *f1, *f2,*f3,*TF;
  TString filename,filename1,filename2;
  TH1D *cr_fr,*crdata_fr,*pred_sr_fr;
  TH1D *cr,*sr,*pred_sr,*crdata;
  TGraphAsymmErrors *tf;
  double tf_51[53],tf_err[53], cr_51[53], crdata_51[53], fr_mjb[53],sr_51[53],frerr_mjb[53];
  bool Tf=true;
  TString path="rootoutput/v6/withphicut_zmass60to120/";
  TString path1="rootoutput/v6/withphicut_zmass60to120_data/";

  int n=53;
  bool print=true;
  //Put scale factors in root file 
  TF = TFile::Open("Zfit/purityfactor.root","READ");
  tf=(TGraphAsymmErrors*)TF->Get("data");

  tf->Draw();
  
  double SF[2],SFerr[2];
  SF[0]=1.074389599,SF[1]=1.007009331;
  SFerr[0]=0.09,SFerr[1]=0.3;
  char* sname = new char[200];

  if(year == "full_Run2")
    {
      filename  = path1+"ZJZGToLL_CR_v18.root";
      filename1  = path+"ZJZGToNuNu_CR_v18.root";
      filename2 = path1+"Run2_METdata_CR_v18.root";
    }
  else
    {
      filename  = path1+"ZJZGToLL_"+year+"_CR_v18.root";
      filename1  = path+"ZJZGToNuNu_"+year+"_CR_v18.root";
      filename2 = path1+"Run"+year+"_METdata_CR_v18.root";

    }
  f1 = new TFile(filename);
  f2 = new TFile(filename1);
  f3 = new TFile(filename2);
  sr     = (TH1D*)f2->Get("AllSBins_v6_CD_EW_50bin_elec0");
  crdata     = (TH1D*)f3->Get("AllSBins_v6_CD");
  cr = (TH1D*)f1->Get("AllSBins_v6_CD"); 
  for(int q=1; q<=52; q++)
    {
      int k=1;
      double sum=0,sum2=0,err=0,err2=0;
      sprintf(sname,"AllSBins_v7_CD_sf_%d",q);
      crdata_fr     = (TH1D*)f2->Get(sname);
      //cout<<sname<<endl;
      //crdata     = (TH1D*)f2->Get("AllSBins_v6_CD");
      //cr = (TH1D*)f1->Get("AllSBins_v6_CD");
      Double_t *yg = tf->GetY();
      for(int i=0;i<2;i++)
      	{
	  cout<<"PF(nbj) = "<<yg[i]<<" , Ndata(nbj : CR) = "<<crdata->GetBinContent(i+1)<<" , NMC(nbj : CR) = "<<cr->GetBinContent(i+1)<<" , NMC(SR) = "<<crdata_fr->GetBinContent(i+1)<<endl;
	  sum+=(crdata_fr->GetBinContent(i+1)*SF[i]);
	  sum2+=crdata_fr->GetBinContent(i+1);
	  err+=(crdata_fr->GetBinContent(i+1)*SFerr[i]*SFerr[i]);
	  err2+=crdata_fr->GetBinContent(i+1);
      	}
      fr_mjb[q]=sum/sum2;
      frerr_mjb[q]=pow(err/err2,0.5);
      if(!print)
	cout<<q<<" , file Name = "<<sname<<" having SF(MET, nj, nb) = "<<fr_mjb[q]<<" +- "<<frerr_mjb[q]<<" , Ndata = "<<sr->GetBinContent(q+1)<<" , FR x Ndata  = "<< fr_mjb[q]*sr->GetBinContent(q+1)<<endl;

    }

   if(print)
     {
       cout<<"Fr(MET, nj, nb) : "<<endl;
       for(int i=1;i<n;i++)
         cout<<fr_mjb[i]<<endl;
       cout<<"Fr(MET, nj, nb) : "<<endl;
       for(int i=1;i<n;i++)
         cout<<frerr_mjb[i]<<endl;
       cout<<"NMC in SR region"<<endl;
       for(int i=1;i<n;i++)
         cout<<sr->GetBinContent(i+1)<<endl;
       cout<<"N Pred in SR region"<<endl;
       for(int i=1;i<n;i++)
         cout<<sr->GetBinContent(i+1)*fr_mjb[i]<<endl;
       cout<<"dN Pred in SR region"<<endl;
       for(int i=1;i<n;i++)
         cout<<sr->GetBinContent(i+1)*frerr_mjb[i]<<endl;

     }
  
}

