void printerror(TString year)
{
  TFile *f1, *f2,*f3,*TF;
  TString filename,filename1;
  TH2D *cr_fr,*crdata_fr,*pred_sr_fr;
  TH1D *cr,*sr,*pred_sr;
  TH2D *tf;
  double tf_51[55],tf_err[55], cr_51[55], crdata_51[55], fr_mjb[55],sr_51[55],frerr_mjb[55];
  bool Tf=true;
  TString path="/Users/bkansal/work/MET_Analysis/Analysis/fakerate/rootout/fake_rate_v8/FR_using_PhoPtQmulti_csv_cut_EMObjeta_qmulti_METCaloMET_nopxveto_SFnopxveto/";
  int n=10;
  bool print=true;
  double SF=1;
  if(year=="2016") SF=1.62;
  else if(year=="2017") SF=2.83;
  else if(year=="2018") SF=1.799;
  else SF=2.068;
  TF = TFile::Open("fake_rate_highdphi.root","READ");
  tf=(TH2D*)TF->Get("fr");
  
  f1 = new TFile(filename);
  char* sname = new char[200];

  if(year == "full_Run2")
    {
      filename  = path+"TTWGJ_CR_v18.root";
      filename1  = path+"Run2_METdata_CR_v18.root";
    }
  else
    {
      filename  = path+"TTWGJ_"+year+"_CR_v18.root";
      filename1  = path+"Run"+year+"_METdata_CR_v18.root";
    }
  f1 = new TFile(filename);
  f2 = new TFile(filename1);
  
  for(int q=1; q<=54; q++)
    {
      int k=1;
      double sum=0,sum2=0,err=0,err2=0;
      sprintf(sname,"PhoPtQMultJet_fr_%d",q);
      cr_fr     = (TH2D*)f1->Get(sname);
      crdata_fr     = (TH2D*)f2->Get(sname);
      for(int i=1;i<=9;i++)
	{
	  for(int j=1;j<=4;j++)
	    {
	      tf_51[k]=tf->GetBinContent(i,j);
	      cr_51[k]=cr_fr->GetBinContent(i,j);
	      crdata_51[k]=crdata_fr->GetBinContent(i,j);
	      tf_err[k]=tf->GetBinError(i,j);
	      k++;
	    }
	}
      //      cout<<k<<endl;
      for(int i=1;i<k;i++)
	{
	  sum+=(tf_51[i]*crdata_51[i]);
	  sum2+=crdata_51[i];
	  err+=(tf_err[i]*tf_err[i]*crdata_51[i]);
	  err2+=crdata_51[i];
	 
	}
      //cr     = (TH1D*)f2->Get("AllSBins_v6_CD_EW_50bin_elec1");
      fr_mjb[q]=sum/sum2;
      frerr_mjb[q]=pow(err/err2,0.5);
      //      if(!print)
      //	cout<<q<<" , file Name = "<<sname<<" having Sum of Fr(Q,ptg) x N(Q,ptg : MET, nj, nb) = "<<fr_mjb[q]<<" +- "<<frerr_mjb[q]<<" , Ndata = "<<cr->GetBinContent(q+1)<<" , FR x Ndata  = "<< fr_mjb[q]*cr->GetBinContent(q+1)<<endl;

    }

  pred_sr     = (TH1D*)f2->Get("AllSBins_v6_CD_EW_50bin_elec1_closure");
  sr     = (TH1D*)f1->Get("AllSBins_v6_CD_EW_50bin_elec1_closure");
  cr     = (TH1D*)f2->Get("AllSBins_v6_CD_EW_50bin_elec1");
  n=55;

  if(print)
    {
      cout<<"Fr(MET, nj, nb) : "<<endl;
      for(int i=1;i<n;i++)
	cout<<fr_mjb[i]<<endl;
      cout<<"Fr(MET, nj, nb) : "<<endl;
      for(int i=1;i<n;i++)
	cout<<frerr_mjb[i]<<endl;
      
      cout<<"Ndata in CR region"<<endl;
      for(int i=1;i<n;i++)
	cout<<cr->GetBinContent(i+1)<<endl;
      cout<<"dNdata in CR region"<<endl;
      for(int i=1;i<n;i++)
	cout<<cr->GetBinError(i+1)<<endl;
      cout<<"FR*Ndata in CR region"<<endl;
      for(int i=1;i<n;i++)
	cout<<cr->GetBinContent(i+1)*fr_mjb[i]<<endl;

      cout<<"NPredicted in SR region"<<endl;
      for(int i=1;i<n;i++)
	cout<<SF*cr->GetBinContent(i+1)*fr_mjb[i]<<endl;
      cout<<"dNPredicted in SR region"<<endl;
      for(int i=1;i<n;i++)
	cout<<SF*pow((pow(cr->GetBinContent(i+1)*frerr_mjb[i],2) + pow(cr->GetBinError(i+1)*fr_mjb[i],2)),0.5)<<endl;
       cout<<"N+dN Predicted in SR region"<<endl;
       for(int i=1;i<n;i++)
	 cout<<SF*cr->GetBinContent(i+1)*fr_mjb[i]<<" +- "<<SF*pow((pow(cr->GetBinContent(i+1)*frerr_mjb[i],2) + pow(cr->GetBinError(i+1)*fr_mjb[i],2)),0.5)<<endl;
       cout<<"Npred using MC in SR region"<<endl;
       for(int i=1;i<n;i++)
         cout<<sr->GetBinContent(i+1)<<endl;
       
    }

}
