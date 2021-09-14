void printerror(TString varName,  TString year)
{
  TFile *f1, *f2,*f3,*TF;
  TString filename,filename1;
  TH1D *cr,*sr,*tf,*pred_sr;
  double tf_51[53],tf_err[53];
  bool Tf=true;
  bool print=true;
  TString path="rootoutput/newselec_LL_noISRjet_METfilters_EW_hadjetID_newPU_v18/TF_v5_usingfullRun2_BTagDeepCSV_lowdphi/";
  int n=10;
  filename  = path+"Run2_METdata_CR_v18.root";
  filename1  = path+"TTWGJ_CR_v18.root";
  
  TF = TFile::Open("Runfull_Run2_TF_lowdphi_LL_v6_CD.root","READ");
  tf=(TH1D*)TF->Get("tf_SP_2");
  
  f1 = new TFile(filename);
  f2 = new TFile(filename1);

   if(Tf)
      {
        filename  = path+"Run2_METdata_CR_v18.root";
        cr     = (TH1D*)f1->Get("AllSBins_v7_CD_SP_elec1");
        for(int i=1;i<=52;i++)
          {
	    //	    cout<<i<<" , NMC(CR) =  "<<cr->GetBinContent(i)<<" , tf = "<<tf->GetBinContent(i)<<endl;
            if(i<8) tf_51[i]=((cr->GetBinContent(1)*tf->GetBinContent(1))+(cr->GetBinContent(2)*tf->GetBinContent(2))+(cr->GetBinContent(3)*tf->GetBinContent(3)))/(cr->GetBinContent(1) + cr->GetBinContent(2) + cr->GetBinContent(3));
            if(i>=8 && i<14) tf_51[i]=tf->GetBinContent(4);
            if(i>=14 && i<20) tf_51[i]=tf->GetBinContent(5);
            if(i>=20 && i<26) tf_51[i]=tf->GetBinContent(6);
            if(i>=26 && i<32) tf_51[i]=tf->GetBinContent(7);
            if(i>=32 && i<38) tf_51[i]=tf->GetBinContent(8);
            if(i>=38 && i<45) tf_51[i]=tf->GetBinContent(9);
            if(i>=45 && i<52) tf_51[i]=tf->GetBinContent(10);
          }
        filename  = path+"Run2_METdata_CR_v18.root";
        cr     = (TH1D*)f1->Get("AllSBins_v7_CD_SP_elec1");
        for(int i=1;i<=52;i++)
          {
            if(i<8) tf_err[i]=pow((((cr->GetBinContent(1)*tf->GetBinError(1)*tf->GetBinError(1))+(cr->GetBinContent(2)*tf->GetBinError(2)*tf->GetBinError(2))+(cr->GetBinContent(3)*tf->GetBinError(3)*tf->GetBinError(3)))/(cr->GetBinContent(1) + cr->GetBinContent(2) + cr->GetBinContent(3))),0.5);
            if(i>=8 && i<14) tf_err[i]=tf->GetBinError(4);
            if(i>=14 && i<20) tf_err[i]=tf->GetBinError(5);
            if(i>=20 && i<26) tf_err[i]=tf->GetBinError(6);
            if(i>=26 && i<32) tf_err[i]=tf->GetBinError(7);
            if(i>=32 && i<38) tf_err[i]=tf->GetBinError(8);
            if(i>=38 && i<45) tf_err[i]=tf->GetBinError(9);
            if(i>=45 && i<52) tf_err[i]=tf->GetBinError(10);
          }
      }  
  if(varName=="AllSBins_v7_CD_SP"){

    pred_sr     = (TH1D*)f1->Get("AllSBins_v7_CD_SP_elec1_closure");
    sr     = (TH1D*)f2->Get("AllSBins_v7_CD_SP_elec0");
    cr     = (TH1D*)f1->Get("AllSBins_v7_CD_SP_elec1");
    n=10;
 
  }
  
  else if(varName=="AllSBins_v6_CD_EW_50bin"){
    pred_sr     = (TH1D*)f1->Get("AllSBins_v6_CD_EW_50bin_elec1_closure");
    sr     = (TH1D*)f2->Get("AllSBins_v6_CD_EW_50bin_elec0");
    cr     = (TH1D*)f1->Get("AllSBins_v6_CD_EW_50bin_elec1");
    n=54;
  }
  
  if(print)
    {
      
      cout<<"N(MC : SR) "<<endl;
      for(int i=1;i<=n;i++)
	cout<<sr->GetBinContent(i)<<endl;
      cout<<"N(MC : CR) "<<endl;
      for(int i=1;i<=n;i++)
	cout<<cr->GetBinContent(i)<<endl;
      cout<<"N(MC : SR)/N(MC : CR) "<<endl;
      for(int i=1;i<=52;i++)
	cout<<tf_51[i]<<endl;
      
      cout<<"N(MC : Pred) "<<endl;
      for(int i=0;i<=n;i++)
	cout<<pred_sr->GetBinContent(i)<<endl;
      
      cout<<"N(data : CR) "<<endl;
      for(int i=1;i<=n;i++)
	cout<<cr->GetBinContent(i+1)<<endl;
      
      cout<<"N(data : Pred) "<<endl;
      for(int i=1;i<=n;i++)
	cout<<cr->GetBinError(i+1)<<endl;

      cout<<" TF : "<<endl;
      for(int i=1;i<=52;i++)
	cout<<tf_51[i]<<endl;

      cout<<" TF error : "<<endl;
      for(int i=1;i<=52;i++)
        cout<<tf_err[i]<<endl;

      cout<<"prediction : "<<endl;
      for(int i=1;i<=52;i++)
	cout<<cr->GetBinContent(i+1)*tf_51[i]<<endl;

      cout<<"Error in prediction : "<<endl;
      for(int i=1;i<=52;i++)
	cout<<pow((pow(cr->GetBinContent(i+1)*tf_err[i],2) + pow(cr->GetBinError(i+1)*tf_51[i],2)),0.5)<<endl;
		
    }
}
