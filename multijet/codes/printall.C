void printall(bool lowdphi=false)
{
  TFile *f1, *f2,*f3,*f4,*TF,*f5,*f6;
  TString filename,filename1,filename2,filename3,filename4,filename5;
  
  TH1D *cr_fr,*crdata_fr,*pred_sr_fr;
  TH1D *cr,*cr1,*cr2,*cr3,*sr,*pred_sr,*crdata,*cr4;
  TH1D *sr_err,*cr1_err,*cr2_err,*cr3_err;
  TH1D *tf;
  double tf_51[53],tf_err[53], cr_51[53], crdata_51[53], fr_mjb[53],sr_51[53],frerr_mjb[53];
  bool Tf=true;
  TString path,path1,path2,path3,path4,path5;
  if(lowdphi){
    path1="../lostlepton/Lostlepton_lowdphi.root";
    path2="../fakerate/Fakerate_lowdphi.root";
    path3="../Z_invisible/Zinvi_lowdphi.root";
    path4 = "factors/RK_lowMET_data.root";
    path5="factors/Run2_METdata.root";
  }
  if(!lowdphi){
    path1="../lostlepton/Lostlepton_highdphi.root";
    path2="../fakerate/Fakerate_highdphi.root";
    path3="../Z_invisible/Zinvi_highdphi.root";
    path4 = "factors/RK_lowMET_data.root";
    path5="factors/Run2_METdata.root";
  }

  int n=46;
  bool print=true;
  char* sname = new char[200];

  TFile *LL = new TFile(path1);
  TFile *FR = new TFile(path2);
  TFile *Zin = new TFile(path3);
  TFile *Multi = new TFile(path4);
  TFile *Data = new TFile(path5);

  TH1D *ll=(TH1D*)LL->FindObjectAny("AllSBins_v6_CD_EW_50bin_elec1_closure");
  TH1D *fr=(TH1D*)FR->FindObjectAny("AllSBins_v6_CD_EW_50bin_elec1_closure");
  TH1D *zin=(TH1D*)Zin->FindObjectAny("AllSBins_v6_CD_EW_50bin_elec1_closure");
  TH1D *multi=(TH1D*)Multi->FindObjectAny("AllSBins_v6_CD_EW_50bin_elec1_closure");
  TH1D *data_CR=(TH1D*)Data->FindObjectAny("AllSBins_v6_CD_EW_50bin_C");
  TH1D *data=(TH1D*)Data->FindObjectAny("AllSBins_v6_CD_EW_50bin_D");

  TH1D *total = (TH1D*)ll->Clone("total");
  total->Add(fr);
  total->Add(zin);
  total->Add(multi);

  TString METbin[7]={"200 - 300","300 - 370","370 - 450","450 - 600","600 - 750","750 - 900"," $\\geq$900 "};
  TString METbin2[6]={"200 - 300","300 - 370","370 - 450","450 - 600","600 - 750"," $\\geq$750 "};
  TString METbin3[5]={"200 - 300","300 - 370","370 - 450","450 - 600"," $\\geq$600 "};

  TString Nbj[8]={ "2 $\\leq N_{jets} \\leq$ 4 , $N_{b-jets}$ = 0 ","5 $\\leq N_{jets} \\leq$ 6 , $N_{b-jets}$ = 0 "," $ N_{jets} \\geq$ 7 , $N_{b-jets}$ = 0 ", "2 $\\leq N_{jets} \\leq$ 4 , $N_{b-jets} > $ 0 ","5 $\\leq N_{jets} \\leq$ 6 , $N_{b-jets} > $ 0 "," $ N_{jets} \\geq$ 7 , $N_{b-jets} > $  0 ","EW : W tag"," EW : H tag"};
  int k=1;
  for(int i=0;i<8;i++)
    {
      if(i==0){
	cout<<"\\multicolumn{7}{|c|}{"<<Nbj[i]<<"} \\ "<<endl;
	cout<<"\\hline"<<endl;
	for(int j=0 ; j<7 ; j++)
	  {
	    k=k+1;
	    if(j==0) cout<<setprecision(3)<<METbin[j]<<" & "<<ll->GetBinContent(k)<<" $\\pm$ "<<ll->GetBinError(k)<<" & "<<fr->GetBinContent(k)<<" $\\pm$ "<<fr->GetBinError(k)<<" & "<<zin->GetBinContent(k)<<" $\\pm$ "<<zin->GetBinError(k)<<" & "<<multi->GetBinContent(k)<<" $\\pm$ "<<multi->GetBinError(k)<<" & "<<total->GetBinContent(k)<<" $\\pm$ "<<total->GetBinError(k)<<" & "<<data_CR->GetBinContent(k)<<" & \\ "<<endl;
	    else
	      cout<<setprecision(3)<<METbin[j]<<" & "<<ll->GetBinContent(k)<<" $\\pm$ "<<ll->GetBinError(k)<<" & "<<fr->GetBinContent(k)<<" $\\pm$ "<<fr->GetBinError(k)<<" & "<<zin->GetBinContent(k)<<" $\\pm$ "<<zin->GetBinError(k)<<" & "<<multi->GetBinContent(k)<<" $\\pm$ "<<multi->GetBinError(k)<<" & "<<total->GetBinContent(k)<<" $\\pm$ "<<total->GetBinError(k)<<" & "<<data->GetBinContent(k)<<" & \\ "<<endl;
	  }
      }
      else if(i==1){
        cout<<"\\multicolumn{7}{|c|}{"<<Nbj[i]<<"} \\ "<<endl;
        cout<<"\\hline"<<endl;
        for(int j=0 ; j<6 ; j++)
	  {
            k=k+1;
	    if(j==0)
	      cout<<METbin2[j]<<" & "<<ll->GetBinContent(k)<<" $\\pm$ "<<ll->GetBinError(k)<<" & "<<fr->GetBinContent(k)<<" $\\pm$ "<<fr->GetBinError(k)<<" & "<<zin->GetBinContent(k)<<" $\\pm$ "<<zin->GetBinError(k)<<" & "<<multi->GetBinContent(k)<<" $\\pm$ "<<multi->GetBinError(k)<<" & "<<total->GetBinContent(k)<<" $\\pm$ "<<total->GetBinError(k)<<" & "<<data_CR->GetBinContent(k)<<" & \\ "<<endl;
	    else
	      cout<<METbin2[j]<<" & "<<ll->GetBinContent(k)<<" $\\pm$ "<<ll->GetBinError(k)<<" & "<<fr->GetBinContent(k)<<" $\\pm$ "<<fr->GetBinError(k)<<" & "<<zin->GetBinContent(k)<<" $\\pm$ "<<zin->GetBinError(k)<<" & "<<multi->GetBinContent(k)<<" $\\pm$ "<<multi->GetBinError(k)<<" & "<<total->GetBinContent(k)<<" $\\pm$ "<<total->GetBinError(k)<<" & "<<data->GetBinContent(k)<<" & \\ "<<endl;
	  }
      }
      else if(i<6){
        cout<<"\\multicolumn{7}{|c|}{"<<Nbj[i]<<"} \\ "<<endl;
        cout<<"\\hline"<<endl;
        for(int j=0 ; j<5 ; j++)
	  {
            k=k+1;
	    if(j==0) cout<<METbin3[j]<<" & "<<ll->GetBinContent(k)<<" $\\pm$ "<<ll->GetBinError(k)<<" & "<<fr->GetBinContent(k)<<" $\\pm$ "<<fr->GetBinError(k)<<" & "<<zin->GetBinContent(k)<<" $\\pm$ "<<zin->GetBinError(k)<<" & "<<multi->GetBinContent(k)<<" $\\pm$ "<<multi->GetBinError(k)<<" & "<<total->GetBinContent(k)<<" $\\pm$ "<<total->GetBinError(k)<<" & "<<data_CR->GetBinContent(k)<<" & \\ "<<endl;
	    else
	      cout<<METbin3[j]<<" & "<<ll->GetBinContent(k)<<" $\\pm$ "<<ll->GetBinError(k)<<" & "<<fr->GetBinContent(k)<<" $\\pm$ "<<fr->GetBinError(k)<<" & "<<zin->GetBinContent(k)<<" $\\pm$ "<<zin->GetBinError(k)<<" & "<<multi->GetBinContent(k)<<" $\\pm$ "<<multi->GetBinError(k)<<" & "<<total->GetBinContent(k)<<" $\\pm$ "<<total->GetBinError(k)<<" & "<<data->GetBinContent(k)<<" & \\ "<<endl;

	  }
      }
      else{
        cout<<"\\multicolumn{7}{|c|}{"<<Nbj[i]<<"} \\ "<<endl;
        cout<<"\\hline"<<endl;
        for(int j=0 ; j<6 ; j++)
	  {
            k=k+1;
	    if(j==0)
	      cout<<METbin2[j]<<" & "<<ll->GetBinContent(k)<<" $\\pm$ "<<ll->GetBinError(k)<<" & "<<fr->GetBinContent(k)<<" $\\pm$ "<<fr->GetBinError(k)<<" & "<<zin->GetBinContent(k)<<" $\\pm$ "<<zin->GetBinError(k)<<" & "<<multi->GetBinContent(k)<<" $\\pm$ "<<multi->GetBinError(k)<<" & "<<total->GetBinContent(k)<<" $\\pm$ "<<total->GetBinError(k)<<" & "<<data_CR->GetBinContent(k)<<" & \\ "<<endl;

	    else
	      cout<<METbin2[j]<<" & "<<ll->GetBinContent(k)<<" $\\pm$ "<<ll->GetBinError(k)<<" & "<<fr->GetBinContent(k)<<" $\\pm$ "<<fr->GetBinError(k)<<" & "<<zin->GetBinContent(k)<<" $\\pm$ "<<zin->GetBinError(k)<<" & "<<multi->GetBinContent(k)<<" $\\pm$ "<<multi->GetBinError(k)<<" & "<<total->GetBinContent(k)<<" $\\pm$ "<<total->GetBinError(k)<<" & "<<data->GetBinContent(k)<<" & \\ "<<endl;
	  }
      }
      cout<<"\\hline"<<endl;
    }
}
