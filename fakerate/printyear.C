void printyear(bool lowdphi=false, TString year="2016",int nbin=52, int xmin=0, int xmax=52)
{
  TFile *f1, *f2,*f3,*TF,*f4,*f5,*f6,*f7,*f3_,*f3_old;
  TString filename,filename1,filename2,filename3,filename4,filename5,filename6,filename2_;
  TH2D *cr_fr,*crdata_fr,*pred_sr_fr;
  TH1D *cr,*sr,*pred_sr, *crdata_sf,*pred_fr,*esf,*bsf,*nobsf,*pred_sr_esf,*pred_sr_bsf,*pred_sr_jec,*pred_sr_jer,*pred_sr_nojerc;
  TH2D *tf;
  double tf_51[55],tf_err[55], cr_51[55], crdata_51[55], fr_mjb[55],sr_51[55],frerr_mjb[55],sf_mjb[55],sferr_mjb[55],esf_mjb[55],bsf_mjb[55];
  bool Tf=true, sys=true;
  TString path,path1,path_esf,path_bsf,path_jerc,path_jec,path_jer,path2;
  if(lowdphi) {
    path1="rootout/fake_rate_v10_afterbtagSF/FR_using_PhoPtQmulti_csv_cut_EMObjeta_qmulti_METCaloMET_nopxveto_noSF_bSF_lowdphi_newbin2/";
    path="rootout/fake_rate_v10_afterbtagSF/FR_using_PhoPtQmulti_csv_cut_EMObjeta_qmulti_METCaloMET_nopxveto_SF_bSF_lowdphi_newbin2/";
    path2=path;
    path_esf="rootout/fake_rate_v10_afterbtagSF/FR_using_PhoPtQmulti_csv_cut_EMObjeta_qmulti_METCaloMET_nopxveto_SFuperror_bSF_lowdphi_newbin2/";
    path_bsf="rootout/fake_rate_v10_afterbtagSF/FR_using_PhoPtQmulti_csv_cut_EMObjeta_qmulti_METCaloMET_nopxveto_noSF_bSFuperror_lowdphi_newbin2/";
    path_jec="rootout/fake_rate_v10_afterJERC/withJECup/";
    path_jer="rootout/fake_rate_v10_afterJERC/withJERup/";
    path_jerc="rootout/fake_rate_v10_afterJERC/withoutJERC/";

    sys=false;
  }
  if(!lowdphi) {
    //    path="rootout/fake_rate_v10_afterbtagSF/FR_using_PhoPtQmulti_csv_cut_EMObjeta_qmulti_METCaloMET_nopxveto_SF_bSF_newbin2/";
    path2="rootout/fake_rate_v10_afterbtagSF/FR_using_PhoPtQmulti_csv_cut_EMObjeta_qmulti_METCaloMET_nopxveto_SF_bSF_newbin2/Run"+year+"_METdata_CR_v18.root";

    //    path1="rootout/fake_rate_v10_afterbtagSF/FR_using_PhoPtQmulti_csv_cut_EMObjeta_qmulti_METCaloMET_nopxveto_SF_bSF_newbin2/";
    
    path1="rootout/new_noSF_v2/";
    path="rootout/new_v2/";

    //    path1="rootout/fake_rate_v10_afterbtagSF_overlap/";
    //path="rootout/fake_rate_v10_afterbtagSF_overlap_SF/";
    //    path="rootout";
    //    path1="rootout/new_v2/";
    path_esf="rootout/fake_rate_v10_afterbtagSF/FR_using_PhoPtQmulti_csv_cut_EMObjeta_qmulti_METCaloMET_nopxveto_SFuperror_bSF_newbin2/";
    path_bsf="rootout/fake_rate_v10_afterbtagSF/FR_using_PhoPtQmulti_csv_cut_EMObjeta_qmulti_METCaloMET_nopxveto_SF_bSFuperror_newbin2/";
    path_bsf="rootout/fake_rate_v10_afterbtagSF/tmp/";
    path_jec="rootout/fake_rate_v10_afterJERC/withJECup/";
    path_jer="rootout/fake_rate_v10_afterJERC/withJERup/";
    path_jerc="rootout/fake_rate_v10_afterJERC/withoutJERC/";
    sys=true;
  }
  
  int n=10;
  bool print=true;
  TString fname;
  if(!lowdphi) fname="fake_rate_highdphi.root";  
  if(lowdphi) fname="fake_rate_lowdphi.root";
  TF = TFile::Open(fname,"READ");
  tf=(TH2D*)TF->Get("fr");
  
  filename  = path+"TTWGJ_"+year+"_CR_v18.root";
  filename1  = path+"Run"+year+"_METdata_CR_v18.root";
  //  filename1  = "rootout/Run2_METdata_CR_v18.root";
  filename2  = path1+"Run"+year+"_METdata_CR_v18.root";
  filename2_  = path1+"TTWGJ_"+year+"_CR_v18.root";

  f1 = new TFile(filename); //new fakerate with sf in MC  
  f2 = new TFile(filename1); //new fakerate with sf in data   
  f3 = new TFile(filename2); //new fakerate without sf in data
  f3_ = new TFile(filename2_); //new fakerate without sf in MC
  f3_old = new TFile(path2); //old fakerate with sf for sys

  if(sys)
    {
      filename3  = path_esf+"Run"+year+"_METdata_CR_v18.root";
      filename4  = path_bsf+"Run"+year+"_METdata_CR_v18.root";
      filename5  = path_jec+"Run"+year+"_METdata_CR_v18.root";
      filename6  = path_jer+"Run"+year+"_METdata_CR_v18.root";
      //      filename7  = path_jerc+"Run"+year+"_METdata_CR_v18.root";

      f4 = new TFile(filename3);
      f5 = new TFile(filename4); //bsfup
      f6 = new TFile(filename5); //jecup
      f7 = new TFile(filename6); //jerup

    }
    if(sys){
    pred_sr_esf     = (TH1D*)f4->Get("AllSBins_v6_CD_EW_50bin_elec1_closure");
    pred_sr_bsf     = (TH1D*)f5->Get("AllSBins_v6_CD_EW_50bin_elec1_closure");
    pred_sr_jec     = (TH1D*)f6->Get("AllSBins_v6_CD_EW_50bin_elec1_closure");
    pred_sr_jer     = (TH1D*)f7->Get("AllSBins_v6_CD_EW_50bin_elec1_closure");                                                                                        
    //    pred_sr_nojerc     = (TH1D*)f8->Get("AllSBins_v6_CD_EW_50bin_elec1_closure");                                                                                     
  }

    pred_sr_jer->Print("all");
 
  TFile *fout;


  
  TH1D *h_fr= new TH1D("fr","FR in 51 SR bins",nbin,xmin,xmax);
  TH1D *h_sf= new TH1D("sf","FR in 51 SR bins",nbin,xmin,xmax);
  TH1D *h_fr_nosf= new TH1D("fr_nosf","FR in 51 SR bins",nbin,xmin,xmax);
  TH1D *h_esfsys= new TH1D("esfsys","e SF sys in 51 SR bins",nbin,xmin,xmax);
  TH1D *h_bsfsys= new TH1D("bsfsys","b SF sys in 51 SR bins",nbin,xmin,xmax);
  TH1D *h_jecsys= new TH1D("jecsys","JEC sys in 51 SR bins",nbin,xmin,xmax);
  TH1D *h_jersys= new TH1D("jersys","JER sys in 51 SR bins",nbin,xmin,xmax);
  TH1D *h_preddata= new TH1D("Preddata","Predicted events in 51 SR bins",nbin,xmin,xmax);
  TH1D *h_preddata_err= new TH1D("Preddata_err","Error in Predicted events in 51 SR bins",nbin,xmin,xmax);
  TH1D *AllSBins_v6_CD_EW_50bin_elec1_closure = new TH1D("AllSBins_v6_CD_EW_50bin_elec1_closure","search bins v6:[(WTag : [65,105]),(HTag : [105,140])]",52,0,52);
  TH1D *AllSBins_v6_CD_EW_50bin_elec1 = new TH1D("AllSBins_v6_CD_EW_50bin_elec1","search bins v6:[(WTag : [65,105]),(HTag : [105,140])]",52,0,52);
  TH1D *h_SRmc= new TH1D("SRmc","Expected events in 51 SR bins",nbin,xmin,xmax);
  TH1D *h_ST=new TH1D("ST","ST",400,0,4000);
  TH1D *h_MET=new TH1D("MET","MET",200,0,2000);
  TH1D *h_BTags=new TH1D("nBTags","no. of B tags",10,0,10);
  TH1D *h_BestPhotonPt=new TH1D("BestPhotonPt","Pt of the Best Photon",150,0,1500);
  TH1D *h_hadAk8Mass=new TH1D("hadAk8Mass","Soft dropped Mass of AK8 Jet",1000,0,300);
  TH1D *h_nJets=new TH1D("nJets","no. of hadronic jets",10,0,10);

  h_ST  = (TH1D*)f2->Get("ST_elec1_closure");
  h_MET  = (TH1D*)f2->Get("MET_elec1_closure");
  h_nJets  = (TH1D*)f2->Get("nJets_elec1_closure");
  h_BTags  = (TH1D*)f2->Get("nBTags_elec1_closure");
  h_BestPhotonPt  = (TH1D*)f2->Get("BestPhotonPt_elec1_closure");
  h_hadAk8Mass  = (TH1D*)f2->Get("hadAk8Mass_elec1_closure");
  
  
  cr     = (TH1D*)f3->Get("AllSBins_v6_CD_EW_50bin_elec1");
  pred_sr     = (TH1D*)f2->Get("AllSBins_v6_CD_EW_50bin_elec1_closure"); //SF x FR x N(Data:CR)                                                                             
  sr     = (TH1D*)f1->Get("AllSBins_v6_CD_EW_50bin_elec0");
  pred_fr     = (TH1D*)f3->Get("AllSBins_v6_CD_EW_50bin_elec1_closure"); //FR x N(Data:CR)                                                                                  
  //  pred_sr_jer->Print("all");  
  char* sname = new char[200];
  ///////////////// SF error calculation //////////
  fname="rootout/new_noSF_v2/Run"+year+"_METdata_CR_v18.root";
  TFile *fa = new TFile(fname);
  TH1D *cr_a     = (TH1D*)fa->Get("AllSBins_v6_CD_EW_50bin_elec1");
  double a[10]={1.6244,2.8378,1.7967};
  double aerr[10]={0.0621575,0.0893453,0.0501307};

  for(int q=1; q<=46; q++)
    {
     if(year=="2016") sf_mjb[q]=a[0], sferr_mjb[q]=aerr[0];
     if(year=="2017") sf_mjb[q]=a[1], sferr_mjb[q]=aerr[1];
     if(year=="2018") sf_mjb[q]=a[2], sferr_mjb[q]=aerr[2];

    }
  ///////////////// FR error calculation //////////
  cout<<"manual fake rate : "<<endl;
  for(int q=1; q<=46; q++)
    {
      int k=1;
      double sum=0,sum2=0,err=0,err2=0;
      sprintf(sname,"PhoPtQMultJet_fr_%d",q);
      cr_fr     = (TH2D*)f3_->Get(sname);
      crdata_fr     = (TH2D*)f3->Get(sname);
      
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

      for(int i=1;i<k;i++)
	{
	  //	  cout<<"tf_51[i] : "<<tf_51[i]<<endl;
	  sum+=(tf_51[i]*crdata_51[i]);
	  sum2+=crdata_51[i];
	  err+=(tf_err[i]*tf_err[i]*crdata_51[i]);
	  err2+=crdata_51[i];
	 
	}
      //      cout<<sum<<" : "<<sum2<<endl;
      fr_mjb[q]=sum/sum2;
      frerr_mjb[q]=pow(err/err2,0.5);
      //      cout<<fr_mjb[q]*sf_mjb[q]<<" +- "<<frerr_mjb[q]*sferr_mjb[q]<<endl;

    }
  
  cout<<"////// SF x FR : ////////"<<endl;
  for(int q=1; q<=46; q++)
    {

      fr_mjb[q]=pred_fr->GetBinContent(q+1)/cr->GetBinContent(q+1);      
      sf_mjb[q]=(pred_sr->GetBinContent(q+1)/pred_fr->GetBinContent(q+1));
      // sf_mjb[q]=1;

      if(sys){
	esf_mjb[q]=(pred_sr_esf->GetBinContent(q+1)/cr->GetBinContent(q+1));
	bsf_mjb[q]=(pred_sr_bsf->GetBinContent(q+1)/cr->GetBinContent(q+1));
      }
      cout<<fr_mjb[q]<<" +- "<<frerr_mjb[q]<<endl;

    }
  
  if(!lowdphi)fname="Fakerate_highdphi_"+year+".root"; 
  if(lowdphi)fname="Fakerate_lowdphi_"+year+".root";	
  fout=new TFile(fname,"recreate");
  fout->cd();
  
  n=46;
  print=true;
  if(print)
    {

      cout<<"Fr(MET, nj, nb) : "<<endl;
      for(int i=1;i<n;i++)
	{
          h_fr_nosf->SetBinContent(i+1,fr_mjb[i]);
	  cout<<fr_mjb[i]<<endl;
	}
      cout<<"dFr(MET, nj, nb) : "<<endl;
      for(int i=1;i<n;i++)
	{
	  h_fr_nosf->SetBinError(i+1,frerr_mjb[i]);
	  cout<<frerr_mjb[i]<<endl;
	}
      cout<<"SF(MET, nj, nb) : "<<endl;
      for(int i=1;i<n;i++)
	{
	  h_sf->SetBinContent(i+1,sf_mjb[i]);
	  cout<<sf_mjb[i]<<endl;
	}
      cout<<"dSF(MET, nj, nb) : "<<endl;
      for(int i=1;i<n;i++)
	{
	  h_sf->SetBinError(i+1,sferr_mjb[i]);
	  cout<<sferr_mjb[i]<<endl;
	}
      
      cout<<"SFxFr(MET, nj, nb) : "<<endl;
      for(int i=1;i<n;i++)
	{
	  cout<<sf_mjb[i]*fr_mjb[i]<<endl;
           h_fr->SetBinContent(i+1,sf_mjb[i]*fr_mjb[i]);
	}
      cout<<"SdFr(MET, nj, nb) : "<<endl;
      for(int i=1;i<n;i++)
	{
	  h_fr->SetBinError(i+1,sqrt(pow(sf_mjb[i]*frerr_mjb[i],2) + pow(sferr_mjb[i]*fr_mjb[i],2)));
	  cout<< h_fr->GetBinError(i)<<endl;		     
	}

      cout<<"Ndata in CR region"<<endl;
      for(int i=1;i<n;i++)
	{
	  cout<<cr->GetBinContent(i+1)<<endl;
	  AllSBins_v6_CD_EW_50bin_elec1->Fill(i,cr->GetBinContent(i+1));
          AllSBins_v6_CD_EW_50bin_elec1->SetBinContent(i+1,cr->GetBinContent(i+1));

	}
      cout<<"dNdata in CR region"<<endl;
      for(int i=1;i<n;i++)
	{
	  cout<<cr->GetBinError(i+1)<<endl;
	  AllSBins_v6_CD_EW_50bin_elec1->SetBinError(i+1,cr->GetBinError(i+1));

	}

      cout<<"NPredicted in SR region"<<endl;
      for(int i=0;i<n;i++)
	{
	  h_preddata->Fill(i,sf_mjb[i]*cr->GetBinContent(i+1)*fr_mjb[i]);
	  h_preddata->SetBinContent(i+1,pred_sr->GetBinContent(i+1));
	  cout<<pred_sr->GetBinContent(i+1)<<endl;//" : "<<fr_mjb[i]*sf_mjb[i]*cr->GetBinContent(i+1)<<endl;
	}
      cout<<"dNPredicted in SR region"<<endl;
      for(int i=1;i<n;i++)
	{
	  cout<<sf_mjb[i]*pow((pow(cr->GetBinContent(i+1)*frerr_mjb[i],2) + pow(cr->GetBinError(i+1)*fr_mjb[i],2)),0.5)<<endl;
	  h_preddata_err->Fill(i,sf_mjb[i]*pow((pow(cr->GetBinContent(i+1)*frerr_mjb[i],2) + pow(cr->GetBinError(i+1)*fr_mjb[i],2)),0.5));
	  h_preddata->SetBinError(i+1,sf_mjb[i]*pow((pow(cr->GetBinContent(i+1)*frerr_mjb[i],2) + pow(cr->GetBinError(i+1)*fr_mjb[i],2)),0.5));
	}
    }
  cout<<"N exp. using MC in SR region"<<endl;
  for(int i=1;i<n;i++)
    h_SRmc->Fill(i,sr->GetBinContent(i+1));
      
  for(int i=1;i<n;i++)
    {
      cout<<i<<" & "<<setprecision(5)<<cr->GetBinContent(i+1)<<" &  "<<setprecision(3)<<h_fr->GetBinContent(i+1)<<" $\pm$  "<<setprecision(3)<<h_fr->GetBinError(i+1)<<" & "<<setprecision(3)<<h_preddata->GetBinContent(i+1)<<" $\pm$  "<<setprecision(3)<<h_preddata->GetBinError(i+1)<<" \\ "<<endl;  
    }

  if(sys)
    {
      for(int i=1;i<=n;i++)
	{
	  /*
          h_esfsys->SetBinContent(i+1,pow(pow(h_preddata->GetBinError(i+1),2)+pow(pred_sr_esf->GetBinContent(i+1)-h_preddata->GetBinContent(i+1),2),0.5)/h_preddata->GetBinContent(i+1));
          h_bsfsys->SetBinContent(i+1,pow(pow(h_preddata->GetBinError(i+1),2)+pow(pred_sr_bsf->GetBinContent(i+1)-h_preddata->GetBinContent(i+1),2),0.5)/h_preddata->GetBinContent(i+1));
          h_jecsys->SetBinContent(i+1,(pow(pow(h_preddata->GetBinError(i+1),2)+pow(pred_sr_jec->GetBinContent(i+1)-h_preddata->GetBinContent(i+1),2),0.5))/h_preddata->GetBinContent(i+1));
         h_jersys->SetBinContent(i+1,(pow(pow(h_preddata->GetBinError(i+1),2)+pow(pred_sr_jer->GetBinContent(i+1)-h_preddata->GetBinContent(i+1),2),0.5))/h_preddata->GetB\
inContent(i+1));
	  */
	  pred_fr     = (TH1D*)f3_old->Get("AllSBins_v6_CD_EW_50bin_elec1_closure"); //FR x N(Data:CR)                                                                        
	  h_esfsys->SetBinContent(i+1,abs(pred_fr->GetBinContent(i+1)-pred_sr_esf->GetBinContent(i+1))/pred_fr->GetBinContent(i+1));
	  h_bsfsys->SetBinContent(i+1,abs(pred_fr->GetBinContent(i+1)-pred_sr_bsf->GetBinContent(i+1))/pred_fr->GetBinContent(i+1));
	  h_jecsys->SetBinContent(i+1,abs(pred_sr_jec->GetBinContent(i+1)-pred_fr->GetBinContent(i+1))/pred_fr->GetBinContent(i+1));

          h_jersys->SetBinContent(i+1,abs(pred_sr_jer->GetBinContent(i+1)-pred_fr->GetBinContent(i+1))/pred_fr->GetBinContent(i+1));
	 
	}
      cout<<"systematics : "<<sys<<endl;
      cout<<"///////  ======= Systematics for electron SF ==============//"<<endl;
      for(int i=1;i<=n;i++)
	//	cout<<setprecision(6)<<pred_sr_bsf->GetBinContent(i+1)<<endl;  
		cout<<setprecision(6)<<h_esfsys->GetBinContent(i+1)<<endl;
      //cout<<setprecision(6)<<h_preddata->GetBinContent(i+1)<<" : "<<pred_sr_esf->GetBinContent(i+1)<<" : "<<h_esfsys->GetBinContent(i+1)<<endl;

      cout<<"///////  ======= Systematics for bTag SF ==============//"<<endl;
      for(int i=1;i<=n;i++)
	cout<<setprecision(6)<<h_bsfsys->GetBinContent(i+1)<<endl;
	//cout<<setprecision(6)<<h_preddata->GetBinContent(i+1)<<" : "<<pred_sr_bsf->GetBinContent(i+1)<<" : "<<h_bsfsys->GetBinContent(i+1)<<endl;
      cout<<"///////  ======= Systematics for JEC up ==============//"<<endl;
      vector<double> max;
      for(int i=1;i<n;i++)
	{
	 	  cout<<setprecision(6)<<h_jecsys->GetBinContent(i+1)<<endl;
          //cout<<setprecision(6)<<pred_sr_jec->GetBinContent(i+1)<<" : "<<pred_fr->GetBinContent(i+1)<<endl;
	}
      cout<<"///////  ======= Systematics for JER up ==============//"<<endl;

      for(int i=1;i<n;i++)
	{
	  // cout<<setprecision(6)<<pred_sr_jer->GetBinContent(i+1)<<" : "<<pred_fr->GetBinContent(i+1)<<endl;
	  cout<<setprecision(6)<<h_jersys->GetBinContent(i+1)<<endl;
	}

      /*
	  max.push_back(h_jersys->GetBinContent(i+1));
	}
      float average = accumulate( max.begin(), max.end(), 0.0)/max.size();
      cout<<" Maximum uncertainty = "<<*max_element(max.begin(), max.end())<<endl;
      cout<<" Average uncertainty = "<<average<<endl;
      */
      
      
    }

  h_preddata->Write();
  h_preddata_err->Write();
  h_SRmc->Write();
  h_fr->Write();
  h_sf->Write();
  h_fr_nosf->Write();
  h_esfsys->Write();
  h_bsfsys->Write();
  h_jecsys->Write();
  h_jersys->Write();
  h_MET->Write("MET");
  h_nJets->Write("nJets");
  h_ST->Write("ST");
  h_BTags->Write("nBTags");
  h_BestPhotonPt->Write("BestPhotonPt");
  h_hadAk8Mass->Write("hadAk8Mass");

  AllSBins_v6_CD_EW_50bin_elec1->Write();
  AllSBins_v6_CD_EW_50bin_elec1_closure = (TH1D*)h_preddata->Clone("AllSBins_v6_CD_EW_50bin_elec1_closure");
  AllSBins_v6_CD_EW_50bin_elec1_closure->Write();
      
  TString METbin[7]={"200 - 300","300 - 370","370 - 450","450 - 600","600 - 750","750 - 900"," $\\ge$900 "};
  TString METbin2[6]={"200 - 300","300 - 370","370 - 450","450 - 600","600 - 750"," $\\ge$750 "};
  TString METbin3[5]={"200 - 300","300 - 370","370 - 450","450 - 600"," $\\ge$600 "};

  TString Nbj[8]={ "2 $\\leq N_{jets} \\leq$ 4 , $N_{b-jets}$ = 0 ","5 $\\leq N_{jets} \\leq$ 6 , $N_{b-jets}$ = 0 "," $ N_{jets} \\geq$ 7 , $N_{b-jets}$ = 0 ", "2 $\\leq N_{jets} \\leq$ 4 , $N_{b-jets} > $ 0 ","5 $\\leq N_{jets} \\leq$ 6 , $N_{b-jets} > $ 0 "," $ N_{jets} \\geq$ 7 , $N_{b-jets} > $  0 ","EW : W tag"," EW : H tag"};
  int k=1;
  int t=3;
  for(int i=0;i<8;i++)
    {
      if(i==0){
	cout<<"\\hline"<<endl;
	cout<<"\\multirow{7}{*}{"<<Nbj[i]<<"}"<<endl;
	for(int j=0 ; j<7 ; j++)
	  {
	    k=k+1;
	    if(j<4) t=5;
	    else t=3;
	    cout<<" & "<<setprecision(t)<<METbin[j]<<" & "<<AllSBins_v6_CD_EW_50bin_elec1->GetBinContent(k)<<" & "<<setprecision(3)<<h_fr->GetBinContent(k)<<" $\\pm$ "<<h_fr->GetBinError(k)<<" & "<<AllSBins_v6_CD_EW_50bin_elec1_closure->GetBinContent(k)<<" $\\pm$ "<<AllSBins_v6_CD_EW_50bin_elec1_closure->GetBinError(k)<<" \\ "<<endl;
	  }
      }
      else if(i==1){
        cout<<"\\multirow{6}{*}{"<<Nbj[i]<<"}"<<endl;
        for(int j=0 ; j<6 ; j++)
	  {
	    if(j<1) t=5;
            else t=3;
            k=k+1;
            cout<<" & "<<setprecision(t)<<METbin2[j]<<" & "<<AllSBins_v6_CD_EW_50bin_elec1->GetBinContent(k)<<" & "<<setprecision(3)<<h_fr->GetBinContent(k)<<" $\\pm$ "<<h_fr->GetBinError(k)<<" & "<<AllSBins_v6_CD_EW_50bin_elec1_closure->GetBinContent(k)<<" $\\pm$ "<<AllSBins_v6_CD_EW_50bin_elec1_closure->GetBinError(k)<<" \\ "<<endl;

	  }
      }
      else if(i<6){
        cout<<"\\multirow{5}{*}{"<<Nbj[i]<<"}"<<endl;
        for(int j=0 ; j<5 ; j++)
          {
	    if(j<4) t=5;
            else t=3;
            k=k+1;
            cout<<" & "<<setprecision(t)<<METbin3[j]<<" & "<<AllSBins_v6_CD_EW_50bin_elec1->GetBinContent(k)<<" & "<<setprecision(3)<<h_fr->GetBinContent(k)<<" $\\pm$ "<<h_fr->GetBinError(k)<<" & "<<AllSBins_v6_CD_EW_50bin_elec1_closure->GetBinContent(k)<<" $\\pm$ "<<AllSBins_v6_CD_EW_50bin_elec1_closure->GetBinError(k)<<" \\ "<<endl;
	  }
      }
      else{
        cout<<"\\multirow{6}{*}{"<<Nbj[i]<<"}"<<endl;
        for(int j=0 ; j<6 ; j++)
          {
	    if(j<4) t=5;
            else t=3;
            k=k+1;
            cout<<" & "<<setprecision(t)<<METbin2[j]<<" & "<<AllSBins_v6_CD_EW_50bin_elec1->GetBinContent(k)<<" & "<<setprecision(3)<<h_fr->GetBinContent(k)<<" $\\pm$ "<<h_fr->GetBinError(k)<<" & "<<AllSBins_v6_CD_EW_50bin_elec1_closure->GetBinContent(k)<<" $\\pm$ "<<AllSBins_v6_CD_EW_50bin_elec1_closure->GetBinError(k)<<" \\ "<<endl;

	  }
      }
      cout<<"\\hline"<<endl;
    }


}
