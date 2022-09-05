void printall(bool lowdphi=false, bool syst=false,TString year="full_Run2", int nbin=52, int xmin=0, int xmax=52)
{

  TFile *f1, *f2,*f3,*f4,*TF,*SF,*bSF,*f5,*f6,*f7,*Jec,*Jer;
  TString filename,filename1,filename2,filename3,filename4, filename5,filename6;
  TH1D *cr_fr,*crdata_fr,*pred_sr_fr;
  TH1D *cr,*sr,*pred_sr,*crdata,*sf,*bsf,*jec,*jer,*nojerc;
  TGraphAsymmErrors *tf;
  double tf_51[53],tf_err[53], cr_51[53], crdata_51[53], fr_mjb[53],sr_51[53],frerr_mjb[53];
  bool Tf=true,sys=true;
  bool old_sys=false;
  TString path,path2,path1,path_bsf,path1_bsf,path_jec,path_jer,path_nojerc;
  if(lowdphi)
    {
      path="rootoutput/v7_btagSF/withphicut_zmass60to120_lowdphi/";
      path1="rootoutput/v7_btagSF/withphicut_zmass60to120_data/";

      path_bsf="rootoutput/v8_btagSFuperr/withphicut_zmass60to120_lowdphi/";
      path1_bsf="rootoutput/v8_btagSFuperr/withphicut_zmass60to120_data/";

      sys=false;
    }
  if(!lowdphi)
    {
      //      path="rootoutput/v7_btagSF/withphicut_zmass60to120/";
      //      path1="rootoutput/v7_btagSF/withphicut_zmass60to120_data/";
      path="rootoutput/v6/withphicut_zmass60to120/";
      path1="rootoutput/v6/withphicut_zmass60to120_data/";

      path_bsf="rootoutput/v8_btagSFuperr/withphicut_zmass60to120/";
      path1_bsf="rootoutput/v8_btagSFuperr/withphicut_zmass60to120_data/";

      path_nojerc="rootoutput/v6/withphicut_zmass60to120_newBin2/";

      if(old_sys){
	path_jec="rootoutput/JECup/withphicut_zmass60to120_data_PF/";
	path_jer="rootoutput/JERup/withphicut_zmass60to120_data_PF/";
      }
      else
	{
	  path_jec="Zinvi_JECup_v2.root";
	  path_jer="Zinvi_JERup_v2.root";
	}
      sys=false;
      
    }

  int n=46;
  bool print=true;
  TFile *f_syserr= new TFile("factors/Zin_sys.root");

  //Put scale factors in root file 
  TF = TFile::Open("factors/purityfactor_v6.root","READ");
  tf=(TGraphAsymmErrors*)TF->Get("data");
  SF = TFile::Open("factors/Zinvisible_SF_v6.root","READ");
  sf=(TH1D*)SF->FindObjectAny("h3");
  Jec = TFile::Open(path_jec,"READ");
  Jer = TFile::Open(path_jer,"READ");
  TH1D *syserr = (TH1D*)f_syserr->Get("JERC");

  
  cout<<" SF +- dSF "<<sf->GetBinContent(1)<<" +- "<<sf->GetBinError(1)<<endl;
 
  filename  = path1+"ZJZGToLL_CR_v18.root";
  filename1  = path+"ZJZGTo2Nu_CR_v18.root";
  filename2 = path1+"Run2_METdata_CR_v18.root";
  if(sys)
    {
      filename3  = path_bsf+"ZJZGTo2Nu_CR_v18.root";
      if(old_sys){
	filename4  = path_jec+"ZJZGTo2Nu_CR_v18.root";
	filename5  = path_jer+"ZJZGTo2Nu_CR_v18.root";
      }
      else
	{
	  filename4  = path_jec;
	  filename5  = path_jer;
	}
      filename6  = path_nojerc+"ZJZGTo2Nu_CR_v18.root";

    }
  f1 = new TFile(filename);
  f2 = new TFile(filename1);
  f3 = new TFile(filename2);
  if(sys)
    {
      f4 = new TFile(filename3);
      
      f5 = new TFile(filename4);
      f6 = new TFile(filename5);
      f7 = new TFile(filename6);
	    
    }
  TFile *fout;
  TString fname;
  if(!lowdphi) fname="Zinvi_highdphi.root";
  if(lowdphi) fname="Zinvi_lowdphi.root";
  if(!lowdphi && syst) fname="Zinvi_highdphi_sys.root";
  fout=new TFile(fname,"recreate");
  fout->cd();

  TH1D *h_fr=new TH1D("fr","FR in 51 SR bins",nbin,xmin,xmax);
  TH1D *h_sf=new TH1D("sf","sF in 51 SR bins",nbin,xmin,xmax);
  TH1D *h_bsfsys=new TH1D("bsfsys","sustematics for btag sf in 51 SR bins",nbin,xmin,xmax);
  TH1D *h_esfsys=new TH1D("bsfsys","sustematics for e sf in 51 SR bins",nbin,xmin,xmax);
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
  
  sr     = (TH1D*)f2->Get("AllSBins_v6_CD_EW_50bin_elec0");
  pred_sr     = (TH1D*)f2->Get("AllSBins_v6_CD_EW_50bin_elec1_closure");
  crdata     = (TH1D*)f3->Get("AllSBins_v6_CD");

  cr     = (TH1D*)f2->Get("AllSBins_v6_CD_EW_50bin_elec0");
  if(sys)
    {
      //      bsf     = (TH1D*)f4->Get("AllSBins_v6_CD_EW_50bin_elec1_closure");
      //jec     = (TH1D*)Jec->Get("JERC");
      //jer     = (TH1D*)Jer->Get("JERC");
      if(old_sys){
	jec=(TH1D*)f5->Get("AllSBins_v6_CD_EW_50bin_elec1_closure");
	jer=(TH1D*)f6->Get("AllSBins_v6_CD_EW_50bin_elec1_closure");
      }
      else{
	jec     = (TH1D*)Jec->Get("JERC");
	jer     = (TH1D*)Jer->Get("JERC");  
      }
      nojerc     = (TH1D*)f7->Get("AllSBins_v6_CD_EW_50bin_elec1_closure");

    }
  char* sname = new char[200];
  for(int q=1; q<=n; q++)
    {
      int k=1;
      double sum=0,sum2=0,err=0,err2=0;
      sprintf(sname,"AllSBins_v7_CD_sf_%d",q);
      crdata_fr     = (TH1D*)f2->Get(sname);
      for(int i=0;i<2;i++)
      	{
	  cout<<i<<" : CR = "<<crdata_fr->GetBinContent(i+1)<<" , SF = "<<sf->GetBinContent(i+1)<<endl;
	  sum+=(crdata_fr->GetBinContent(i+1)*sf->GetBinContent(i+1));

	  sum2+=crdata_fr->GetBinContent(i+1);
	  err+=(crdata_fr->GetBinContent(i+1)*sf->GetBinError(i+1)*sf->GetBinError(i+1));
	  err2+=crdata_fr->GetBinContent(i+1);
      	}
      
      fr_mjb[q]=sum/sum2;
      frerr_mjb[q]=pow(err/err2,0.5);      
      if(sum2==0){fr_mjb[q]=fr_mjb[q-1]; frerr_mjb[q]=frerr_mjb[q-1];}
    }
  //  print=false;
   if(print)
     {
       cout<<"Fr(MET, nj, nb) : "<<endl;
       for(int i=1;i<n;i++)
	 {
	   cout<<fr_mjb[i]<<endl;
	   h_sf->SetBinContent(i+1,fr_mjb[i]);
	 }
       cout<<"dFr(MET, nj, nb) : "<<endl;
       for(int i=1;i<n;i++)
	 {
	   cout<<frerr_mjb[i]<<endl;
           h_sf->SetBinError(i+1,frerr_mjb[i]);

	 }
       
       cout<<"NMC in SR region"<<endl;
       for(int i=1;i<n;i++)
	 {
	   cout<<setprecision(6)<<sr->GetBinContent(i+1)<<endl;
	   h_SRmc->SetBinContent(i+1,sr->GetBinContent(i+1));
	 }
       cout<<"dNMC in SR region"<<endl;
       for(int i=1;i<n;i++)
         {
           h_SRmc->SetBinError(i+1,sr->GetBinError(i+1));
         }
       for(int i=1;i<n;i++)
           cout<<h_SRmc->GetBinError(i+1)<<endl;


       cout<<"N Pred in SR region"<<endl;
       for(int i=1;i<n;i++)
	 {
	   cout<<setprecision(6)<<pred_sr->GetBinContent(i+1)<<endl;
	   h_preddata->SetBinContent(i+1,h_SRmc->GetBinContent(i+1)*h_sf->GetBinContent(i+1));
	   h_preddata->SetBinContent(i+1,pred_sr->GetBinContent(i+1));
	   if(h_SRmc->GetBinContent(i+1)<=0) {
             h_SRmc->SetBinContent(i+1,0.00000000000001);
	     h_preddata->SetBinContent(i+1,0.00000000000001);
	   }
	 }
	   
       cout<<"dN Pred in SR region"<<endl;
       for(int i=1;i<n;i++)
	 {
	   cout<<pred_sr->GetBinContent(i+1)<<" : "<<sr->GetBinError(i+1)/sr->GetBinContent(i+1)<<" : "<<h_sf->GetBinError(i+1)/h_sf->GetBinContent(i+1)<<" : "<<syserr->GetBinError(i+1)/pred_sr->GetBinContent(i+1)<<endl;
	   //h_preddata->SetBinError(i+1,pow(pow(sr->GetBinContent(i+1)*h_sf->GetBinError(i+1),2)+pow(sr->GetBinError(i+1)*h_sf->GetBinContent(i+1),2),0.5));
	   //	   cout<<pred_sr->GetBinContent(i+1)*pow(pow(sr->GetBinError(i+1)/sr->GetBinContent(i+1),2)+pow(h_sf->GetBinError(i+1)/h_sf->GetBinContent(i+1),2) + pow(syserr->GetBinError(i)/pred_sr->GetBinContent(i+1),2),0.5)<<endl;
	   h_preddata->SetBinError(i+1,pred_sr->GetBinContent(i+1)*pow(pow(sr->GetBinError(i+1)/sr->GetBinContent(i+1),2)+pow(h_sf->GetBinError(i+1)/h_sf->GetBinContent(i+1),2),0.5));
	   if(!lowdphi && syst) h_preddata->SetBinError(i+1,pred_sr->GetBinContent(i+1)*pow(pow(sr->GetBinError(i+1)/sr->GetBinContent(i+1),2)+pow(h_sf->GetBinError(i+1)/h_sf->GetBinContent(i+1),2) + pow(syserr->GetBinError(i+1)/pred_sr->GetBinContent(i+1),2),0.5));
		   //h_preddata->SetBinError(i+1,pow(pow(sr->GetBinContent(i+1)*h_sf->GetBinError(i+1),2)+pow(sr->GetBinError(i+1)*h_sf->GetBinContent(i+1),2),0.5));
	   if(h_SRmc->GetBinContent(i+1)==0.00000000000001) h_preddata->SetBinError(i+1,0);
	 }
   
       
       for(int i=1;i<n;i++)
	 cout<<h_preddata->GetBinError(i+1)<<endl;
       


       if(sys)
	 {
	   
	   for(int i=1;i<=n;i++)
	     {
	       h_bsfsys->SetBinContent(i+1,pow(pow(h_preddata->GetBinError(i+1),2)+pow(bsf->GetBinContent(i+1)-h_preddata->GetBinContent(i+1),2),0.5));
	     }
	   for(int i=1;i<=n;i++)
             {
	       if(old_sys) h_jecsys->SetBinContent(i+1,abs(jec->GetBinContent(i+1)-nojerc->GetBinContent(i+1))/nojerc->GetBinContent(i+1));
	       else h_jecsys->SetBinContent(i+1,abs(jec->GetBinContent(i+1)));
             }
           for(int i=1;i<=n;i++)
             {
	       if(old_sys) h_jersys->SetBinContent(i+1,abs(jer->GetBinContent(i+1)-nojerc->GetBinContent(i+1))/nojerc->GetBinContent(i+1));  
	       else h_jersys->SetBinContent(i+1,abs(jer->GetBinContent(i+1))); 
             }


	 }


       ///Data in 52 optimised bins
       cr_fr = (TH1D*)f3->Get("AllSBins_v6_CD_EW_50bin_elec0");
       
       //       cout<<"PF"<<endl;
       for(int q=2; q<=n; q++)
	 {
	   if(q<20) {cr_fr->SetBinContent(q,138); cr_fr->SetBinError(q,sqrt(138));}
	   else if(q>=20 && q<35) {cr_fr->SetBinContent(q,13); cr_fr->SetBinError(q,sqrt(13));}
	   else { cr_fr->SetBinContent(q,5); cr_fr->SetBinError(q,sqrt(5));}
	 }

       cout<<"fr=N(Pred.)/N(Data:CR) : "<<endl;
       for(int i=2;i<=n;i++)
	 {
	   cout<<pred_sr->GetBinContent(i)<<endl;
	   h_fr->SetBinContent(i,pred_sr->GetBinContent(i)/cr_fr->GetBinContent(i));
	   double err=h_fr->GetBinContent(i)*sqrt(pow(cr_fr->GetBinError(i)/cr_fr->GetBinContent(i),2) + pow(pred_sr->GetBinError(i)/pred_sr->GetBinContent(i),2));
	   h_fr->SetBinError(i,err);
	   if(h_fr->GetBinContent(i)==0) h_fr->SetBinError(i,0);
	 }
       
      if(sys)
         {
	   cout<<"///////  ======= Systematics for bTag SF ==============//"<<endl;
           for(int i=0;i<=n;i++)
             {
               cout<<setprecision(6)<<h_bsfsys->GetBinContent(i)<<endl;
             }
	   cout<<"///////  ======= Systematics for JEC ==============//"<<endl;
	   vector<double> max;

	   for(int i=0;i<=n;i++)
             {
               cout<<setprecision(6)<<h_jecsys->GetBinContent(i+1)<<endl;
             }
	   cout<<"///////  ======= Systematics for JER ==============//"<<endl;
          for(int i=1;i<n;i++)
             {
	       //    if(h_jersys->GetBinContent(i+1)>=1) continue;
               cout<<setprecision(6)<<h_jersys->GetBinContent(i+1)<<endl;
	       max.push_back(h_jersys->GetBinContent(i+1));
             }
	  /*
	  float average = accumulate( max.begin(), max.end(), 0.0)/max.size();
	  cout<<" Maximum uncertainty = "<<*max_element(max.begin(), max.end())<<endl;
	  cout<<" Average uncertainty = "<<average<<endl;
	  */

         }

     }
     
  h_preddata->Write();
  h_preddata_err->Write();
  h_SRmc->Write();
  h_fr->Write();
  h_sf->Write();
  h_bsfsys->Write();
  h_esfsys->Write();
  h_jecsys->Write();
  h_jersys->Write();
  h_MET->Write("MET");
  h_nJets->Write("nJets");
  h_ST->Write("ST");
  h_BTags->Write("nBTags");
  h_BestPhotonPt->Write("BestPhotonPt");
  h_hadAk8Mass->Write("hadAk8Mass");


  AllSBins_v6_CD_EW_50bin_elec1_closure = (TH1D*)h_preddata->Clone("AllSBins_v6_CD_EW_50bin_elec1_closure");
  AllSBins_v6_CD_EW_50bin_elec1_closure->Write();
  AllSBins_v6_CD_EW_50bin_elec1 = (TH1D*)cr_fr->Clone("AllSBins_v6_CD_EW_50bin_elec1");
  AllSBins_v6_CD_EW_50bin_elec1->Write();

  cout<<"root file name : "<<fname<<endl;
      
  TString METbin[7]={"200 - 300","300 - 370","370 - 450","450 - 600","600 - 750","750 - 900"," $\\ge$900 "};
  TString METbin2[6]={"200 - 300","300 - 370","370 - 450","450 - 600","600 - 750"," $\\ge$750 "};
  TString METbin3[5]={"200 - 300","300 - 370","370 - 450","450 - 600"," $\\ge$600 "};

  TString Nbj[8]={ "2 $\\leq N_{jets} \\leq$ 4 , $N_{b-jets}$ = 0 ","5 $\\leq N_{jets} \\leq$ 6 , $N_{b-jets}$ = 0 "," $ N_{jets} \\geq$ 7 , $N_{b-jets}$ = 0 ", "2 $\\leq N_{jets} \\leq$ 4 , $N_{b-jets} > $ 0 ","5 $\\leq N_{jets} \\leq$ 6 , $N_{b-jets} > $ 0 "," $ N_{jets} \\geq$ 7 , $N_{b-jets} > $  0 ","EW : W tag"," EW : H tag"};
  int k=1;
  for(int i=0;i<8;i++)
    {
      if(i==0){
	cout<<"\\hline"<<endl;
	cout<<"\\multirow{7}{*}{"<<Nbj[i]<<"}"<<endl;
	for(int j=0 ; j<7 ; j++)
	  {
	    k=k+1;
	    cout<<" & "<<setprecision(3)<<METbin[j]<<" & "<<h_SRmc->GetBinContent(k)<<" $\\pm$ "<<h_SRmc->GetBinError(k)<<" & "<<AllSBins_v6_CD_EW_50bin_elec1_closure->GetBinContent(k)<<" $\\pm$ "<<AllSBins_v6_CD_EW_50bin_elec1_closure->GetBinError(k)<<" \\ "<<endl;
	    //	    cout<<" & "<<setprecision(3)<<METbin[j]<<" & "<<AllSBins_v6_CD_EW_50bin_elec1->GetBinContent(k)<<" & "<<h_fr->GetBinContent(k)<<" $\\pm$ "<<h_fr->GetBinError(k)<<" & "<<AllSBins_v6_CD_EW_50bin_elec1_closure->GetBinContent(k)<<" $\\pm$ "<<AllSBins_v6_CD_EW_50bin_elec1_closure->GetBinError(k)<<" \\ "<<endl;
	  }
      }
      else if(i==1){
        cout<<"\\multirow{6}{*}{"<<Nbj[i]<<"}"<<endl;
        for(int j=0 ; j<6 ; j++)
	  {
            k=k+1;
	    cout<<" & "<<setprecision(3)<<METbin2[j]<<" & "<<h_SRmc->GetBinContent(k)<<" $\\pm$ "<<h_SRmc->GetBinError(k)<<" & "<<AllSBins_v6_CD_EW_50bin_elec1_closure->GetBinContent(k)<<" $\\pm$ "<<AllSBins_v6_CD_EW_50bin_elec1_closure->GetBinError(k)<<" \\ "<<endl;
	    //      cout<<" & "<<setprecision(3)<<METbin2[j]<<" & "<<AllSBins_v6_CD_EW_50bin_elec1->GetBinContent(k)<<" & "<<h_fr->GetBinContent(k)<<" $\\pm$ "<<h_fr->GetBinError(k)<<" & "<<AllSBins_v6_CD_EW_50bin_elec1_closure->GetBinContent(k)<<" $\\pm$ "<<AllSBins_v6_CD_EW_50bin_elec1_closure->GetBinError(k)<<" \\ "<<endl;

	  }
      }
      else if(i<6){
        cout<<"\\multirow{5}{*}{"<<Nbj[i]<<"}"<<endl;
        for(int j=0 ; j<5 ; j++)
          {
            k=k+1;
	    cout<<" & "<<setprecision(3)<<METbin3[j]<<" & "<<h_SRmc->GetBinContent(k)<<" $\\pm$ "<<h_SRmc->GetBinError(k)<<" & "<<AllSBins_v6_CD_EW_50bin_elec1_closure->GetBinContent(k)<<" $\\pm$ "<<AllSBins_v6_CD_EW_50bin_elec1_closure->GetBinError(k)<<" \\ "<<endl;
	    //            cout<<" & "<<setprecision(3)<<METbin3[j]<<" & "<<AllSBins_v6_CD_EW_50bin_elec1->GetBinContent(k)<<" & "<<h_fr->GetBinContent(k)<<" $\\pm$ "<<h_fr->GetBinError(k)<<" & "<<AllSBins_v6_CD_EW_50bin_elec1_closure->GetBinContent(k)<<" $\\pm$ "<<AllSBins_v6_CD_EW_50bin_elec1_closure->GetBinError(k)<<" \\ "<<endl;
	  }
      }
      else{
        cout<<"\\multirow{6}{*}{"<<Nbj[i]<<"}"<<endl;
        for(int j=0 ; j<6 ; j++)
          {
            k=k+1;
	    cout<<" & "<<setprecision(3)<<METbin2[j]<<" & "<<h_SRmc->GetBinContent(k)<<" $\\pm$ "<<h_SRmc->GetBinError(k)<<" & "<<AllSBins_v6_CD_EW_50bin_elec1_closure->GetBinContent(k)<<" $\\pm$ "<<AllSBins_v6_CD_EW_50bin_elec1_closure->GetBinError(k)<<" \\ "<<endl;
	    //    cout<<" & "<<setprecision(3)<<METbin2[j]<<" & "<<AllSBins_v6_CD_EW_50bin_elec1->GetBinContent(k)<<" & "<<h_fr->GetBinContent(k)<<" $\\pm$ "<<h_fr->GetBinError(k)<<" & "<<AllSBins_v6_CD_EW_50bin_elec1_closure->GetBinContent(k)<<" $\\pm$ "<<AllSBins_v6_CD_EW_50bin_elec1_closure->GetBinError(k)<<" \\ "<<endl;

	  }
      }
      cout<<"\\hline"<<endl;
    }


  
}

