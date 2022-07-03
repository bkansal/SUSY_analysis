void printfrsf(bool lowdphi)
{
  TString path, path1, filename, filename1;
  TFile *f1,*f2, *fout;
  TH1D *pred,*pred_sffr;
    if(!lowdphi)
      {
	path="/Users/bkansal/work/MET_Analysis/Analysis/fakerate/rootout/fake_rate_v8/FR_using_PhoPtQmulti_csv_cut_EMObjeta_qmulti_METCaloMET_nopxveto_SFnopxveto_newbin2/";
	path1="/Users/bkansal/work/MET_Analysis/Analysis/fakerate/rootout/fake_rate_v8/FR_using_PhoPtQmulti_csv_cut_EMObjeta_qmulti_METCaloMET_nopxveto_noSF_newbin2/";
	fout=new TFile("Fakerate_highdphi.root","recreate");
      }
    if(lowdphi)
      {
        path="/Users/bkansal/work/MET_Analysis/Analysis/fakerate/rootout/fake_rate_v8/FR_using_PhoPtQmulti_csv_cut_EMObjeta_qmulti_METCaloMET_lowdphi_nopxveto_SFnopxveto_newbin2/";
        path1="/Users/bkansal/work/MET_Analysis/Analysis/fakerate/rootout/fake_rate_v8/FR_using_PhoPtQmulti_csv_cut_EMObjeta_qmulti_METCaloMET_lowdphi_nopxveto_noSF_newbin2/";
	fout=new TFile("Fakerate_lowdphi.root","recreate");
      }
    filename  = path+"Run2_METdata_CR_v18.root";
    filename1  = path1+"Run2_METdata_CR_v18.root";

    f1 = new TFile(filename);
    f2 = new TFile(filename1);

    fout->cd();
    TH1D *h_preddata= new TH1D("Preddata","Predicted events in 51 SR bins",nbin,xmin,xmax);
    TH1D *h_preddata_err= new TH1D("Preddata_err","Error in Predicted events in 51 SR bins",nbin,xmin,xmax);
    TH1D *AllSBins_v6_CD_EW_50bin_elec1_closure = new TH1D("AllSBins_v6_CD_EW_50bin_elec1_closure","search bins v6:[(WTag : [65,105]),(HTag : [105,140])]",52,0,52);
    TH1D *h_SBins_v6_CD_EW_50bin_elec1 = new TH1D("AllSBins_v6_CD_EW_50bin_elec1","search bins v6:[(WTag : [65,105]),(HTag : [105,140])]",52,0,52);
    pred     = (TH1D*)f1->Get("AllSBins_v6_CD_EW_50bin_elec1");
    pred_sffr     = (TH1D*)f1->Get("AllSBins_v6_CD_EW_50bin_elec1_closure");

    pred_sffr->Divide(pred);
    pred_sffr->Write();
}
