#define Fakerate_cxx
#include "Fakerate.h"
#include <TH2.h>
#include <TH3.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <iostream>
#include <vector>
#include <cstring>
#include <string>
#include <fstream>
#include"TGraphErrors.h"
#include"TGraphAsymmErrors.h"

using namespace std;
//TString Tf="sBin6";
//TString Tf="nHadJets";
//TString Tf="MET";
//TString Tf="METvBin2";
bool old=true;
bool applISRWtsTottbar=true;
//bool applISRWtsTottbar=false;
bool full_Run2=true;
bool apply_METfilters=true;
bool apply_L1=true;
bool apply_HEMveto=true;
bool do_prediction=true;
bool applyPUwt=true;
TString puwt="central";
bool highdphi=true;
bool apply_pixelveto=false;
bool applySF=true;
bool applytrg=true;
bool EWKsub=false;
bool applysys=false;
int jec2Use = 0;//-1 for JEC down, 0 for CV, 1 for JEC up                                                                                                                 
int jer2Use = 1;//-1 for JER down, 0 for CV, 1 for JER up                                                                                                                 
int jet2Vary = 48;//4: only AK4 jets, 8: only AK8 jets, 48 or 84: both AK4 and AK8.                                                                                       
bool varyMasswithJEC = 1;//scale the SD mass according to JEC/JER Pt factor?                                     


int main(int argc, char* argv[])
{

  if (argc < 2) {
    cerr << "Please give 3 arguments " << "runList " << " " << "outputFileName" << " " << "dataset" << endl;
    return -1;
  }
  const char *inputFileList = argv[1];
  const char *outFileName   = argv[2];
  const char *data          = argv[3];

  Fakerate ana(inputFileList, outFileName, data);
  cout << "dataset " << data << " " << endl;

  ana.EventLoop(data,inputFileList);

  return 0;
}

void Fakerate::EventLoop(const char *data,const char *inputFileList) {
  if (fChain == 0) return;

  Long64_t nentries = fChain->GetEntriesFast();
  cout << "nentries " << nentries << endl;
  cout << "Analyzing dataset " << data << " " << endl;

  TString s_data=data;
  Long64_t nbytes = 0, nb = 0;
  int decade = 0;
  TCanvas *cA = new TCanvas("METEff","Signal efficiency",1500,850);
  int evtSurvived=0;  
  int EW_evtSurvived=0;
  int EW_evtSurvived_SB=0;  
  int EW_evtSurvived_htag=0;  
  int EW_evtSurvived_wtag=0;  
  int SP_evtSurvived=0;  
  int EW_noSB_evtSurvived=0;

  TFile *pufile,*TF,*TF2,*E_SF,*Egamma_SF,*TF3;
  cout<<"Applying electron scale factors ? "<<applySF<<endl;
  cout<<"Applying MET filters ? "<<apply_METfilters<<endl;
  if(s_data.Contains("v17_2016")){
    pufile = TFile::Open("../PileupHistograms_2016_69mb_pm5.root","READ");
    cout<<"Applying L1 prefiring prob.? "<<apply_L1<<endl;
  }
  if(s_data.Contains("v17_2017")){
    pufile = TFile::Open("../PileupHistograms_2017_69mb_pm5.root","READ");
    cout<<"Applying L1 prefiring prob.? "<<apply_L1<<endl;
  }
  if(s_data.Contains("v17_2018")){
    pufile = TFile::Open("../PileupHistograms_2018_69mb_pm5.root","READ");
    cout<<"Applying HEM veto? "<<apply_HEMveto<<endl;
  }

  double puWtNom = 1.0, puWtup = 1.0, puWtdown = 1.0;


  TH2D *tf,*tf2;
  TH3D *tf1;//\,*tf_SP,*tf_SP_2,*tf_SP_3;
  TH2F *e_id, *e_iso, *e_SF;
  TH1D *mj_wt;
  if(highdphi)
    {
      if(!full_Run2)
	{
	  if(s_data.Contains("2016")){
	    if(apply_pixelveto) TF = TFile::Open("fake_rate_2016_highdphi_pxveto.root","READ");
            if(!apply_pixelveto) TF = TFile::Open("fake_rate_2016_highdphi.root","READ");
	    tf=(TH2D*)TF->FindObjectAny("fr");
	  }
	  if(s_data.Contains("2017")){
	    if(apply_pixelveto) TF = TFile::Open("fake_rate_2017_highdphi_pxveto.root","READ");
            if(!apply_pixelveto) TF = TFile::Open("fake_rate_2017_highdphi.root","READ");
	    tf=(TH2D*)TF->FindObjectAny("fr");
	  }
	  if(s_data.Contains("2018")){
	    if(apply_pixelveto) TF = TFile::Open("fake_rate_2018_highdphi_pxveto.root","READ");
            if(!apply_pixelveto) TF = TFile::Open("fake_rate_2018_highdphi.root","READ");
	    tf=(TH2D*)TF->FindObjectAny("fr");
	  }
	}
      else
	{
	  if(apply_pixelveto)  TF = TFile::Open("fake_rate_highdphi_pxveto.root","READ");
	  if(!apply_pixelveto) TF = TFile::Open("fake_rate_highdphi.root","READ");
	  tf=(TH2D*)TF->FindObjectAny("fr");
	} 
    }
  else
    {
      if(!full_Run2)
	{
	  if(s_data.Contains("2016")){
	    TF = TFile::Open("fake_rate_2016_lowdphi.root","READ");
	    tf=(TH2D*)TF->FindObjectAny("fr");
	  }
	  if(s_data.Contains("2017")){
	    TF = TFile::Open("fake_rate_2017_lowdphi.root","READ");
	    tf=(TH2D*)TF->FindObjectAny("fr");
	  }
	  if(s_data.Contains("2018")){
	    TF = TFile::Open("fake_rate_2018_lowdphi.root","READ");
	    tf=(TH2D*)TF->FindObjectAny("fr");
	  }
	}	
      else
	{
	  TF = TFile::Open("fake_rate_lowdphi.root","READ");
	  tf=(TH2D*)TF->FindObjectAny("fr");
	  //          TF3= TFile::Open("RK_lowMET_data.root","READ");
	  //	  mj_wt= (TH1D*)TF3->Get("h3");
	}
      if(EWKsub){
	TF3= TFile::Open("RK_lowMET_data.root","READ");
	mj_wt= (TH1D*)TF3->Get("h3");
      }  
    }
  TH1* puhist ;
  TH1* puhistUp;  
  TH1* puhistDown;

  if(s_data.Contains("v17"))
    {
      //      puhist = (TH1*)pufile->Get("pu_weights_down");
      puhist     = (TH1*)pufile->Get("pu_weights_central");
      puhistUp   = (TH1*)pufile->Get("pu_weights_up");
      puhistDown = (TH1*)pufile->Get("pu_weights_down");
    }

  int fListIndxOld=-1;
  double prob0=-100,prob1=-100;
  double prob2=-100,prob3=-100;
  double total_prob0=0,total_prob1=0;
  double total_prob2=0,total_prob3=0;

  /*
  vector<TString> inFileName;
  TString sampleName;
  //  TString sampleName="CR_Summer16v3.DYJetsToLL_M-50_HT-100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_v18.root";           
  string str1;
  ifstream runListFile(inputFileList);
  TFile *currFile;
  while (std::getline(runListFile, str1)) {
    inFileName.push_back(str1);
  }runListFile.close();
  cout<<"applying b-tag SFs for MC? "<<applybTagSFs<<endl;
  BTagCorrector btagcorr;
  */
  bool v17=true, v12=false;
  // bool v17=false, v12=true;
  bool EWselection=true;
  double qmulti=0,leadjet_qmulti=-1,leadjet_Pt=-1,leadbjet_tag=-1;
  int elec_reco=0,elec_reco0_before=0,elec_reco1_before=0,muon_reco=0,elec_gen3=0,elec_gen2=0, elec_gen=0, muon_gen=0,elec_reco0=0,elec_reco1=0,evtSurvived_preselec=0,elec_reco2=0,elec2_reco=0,survived_vetohad=0,elec_reco1_CR=0,survived_elecge1=0,events_cr=0,events_sr=0,total=0,remain=0,elec_reco0_genel=0,efakepho=0,ele=0,genphomatch_after=0,genphomatch_before=0,elec_gen4=0,gentauhad2=0,lep2=0,lep=0,nele=0,npho=0,nele_pho=0,nele_pho_0=0,npho_px=0,nele_px=0,Jete=0;

  int fail_realphoton=0;
  int pass_realphoton=0;
  int fail_acceptance=0;
  int pass_acceptance=0;
  int fail_id=0;
  int pass_id=0;
  int fail_iso=0;
  int pass_iso=0;
  int a=0,b=0,c=0,d=0,e=0,f=0,g=0,h=0;
  for (Long64_t jentry=0; jentry<nentries;jentry++) {
    //  for (Long64_t jentry=0; jentry<1000;jentry++) {
    int total_lost_el = 0,cr_el=0,sr_el,e_index=-1,nlep=0,qmulti=0;

    // ==============print number of events done == == == == == == == =
    double progress = 10.0 * jentry / (1.0 * nentries);
    int k = int (progress);
    if (k > decade)
      cout << 10 * k << " %" << endl;
    decade = k;
    

    // ===============read this entry == == == == == == == == == == == 
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);   nbytes += nb;

    bool EWselec=false;
    bool EWselec_Wtag=false;
    bool EWselec_Htag=false;
    bool EWselec_SB1=false;
    bool EWselec_SB2=false;
    bool EWselec1=false;

    double p0=-100, p1=-100, p2=-100;
    if(!s_data.Contains("data"))
      {

        if(s_data.Contains("2016") && highdphi) {lumiInfb=35.922; p0=1.66539e+02; p1=8.13254e+01; p2=9.71152e-01; deepCSVvalue = 0.6321;}
        if(s_data.Contains("2017") && highdphi) {lumiInfb=41.529; p0=1.86744e+02; p1=6.74978e+01; p2=9.65333e-01; deepCSVvalue = 0.4941;}
        if(s_data.Contains("2018") && highdphi) {lumiInfb=59.74; p0=1.89868e+02; p1=6.60434e+01; p2=9.79618e-01; deepCSVvalue = 0.4184;}

        if(s_data.Contains("2016") && !highdphi) {lumiInfb=35.922; p0=1.67229e+02; p1=8.52729e+01; p2=8.29784e-01; deepCSVvalue = 0.6321;}
        if(s_data.Contains("2017") && !highdphi) {lumiInfb=41.529; p0=1.67641e+02; p1=1.21487e+02; p2=9.23864e-01; deepCSVvalue = 0.4941;}
        if(s_data.Contains("2018") && !highdphi) {lumiInfb=59.74; p0=1.45529e+02; p1=1.08431e+02; p2=9.27220e-01; deepCSVvalue = 0.4184;}

        if(s_data.Contains("FastSim") && s_data.Contains("2016")) lumiInfb=137.19;
      }
    if(s_data.Contains("data"))
      {
        if(s_data.Contains("2016")) {deepCSVvalue = 0.6321;}
        if(s_data.Contains("2017")) {deepCSVvalue = 0.4941;}
        if(s_data.Contains("2018")) {deepCSVvalue = 0.4184;}
      }

    
    if(s_data.Contains("data")) 
      {	wt=1;
      }
    // float dphi1AK8 = 3.5, dphi2AK8 = 3.5;
    // if(!(JetsAK8->size()>0 && (*JetsAK8)[0].Pt() > 200 && abs((*JetsAK8)[0].Eta()) < 2.4)) continue;
    //    h_cutflow->Fill("nAK8Jets>0",wt);

    ///////=======  L1 Prefiring issue ===========/////////
 
    if(applyPUwt && s_data.Contains("v17")){
      puWtNom = (puhist->GetBinContent(puhist->GetXaxis()->FindBin(min(TrueNumInteractions,puhist->GetBinLowEdge(puhist->GetNbinsX()+1)))));
      if(puWtNom > 1e-10 && puWtNom < 100){
	wt = wt * puWtNom;
	puWtup = (puhistUp->GetBinContent(puhistUp->GetXaxis()->FindBin(min(TrueNumInteractions,puhistUp->GetBinLowEdge(puhistUp->GetNbinsX()+1)))))/puWtNom;
	puWtdown = (puhistDown->GetBinContent(puhistDown->GetXaxis()->FindBin(min(TrueNumInteractions,puhistDown->GetBinLowEdge(puhistDown->GetNbinsX()+1)))))/puWtNom;
	if(puWtup/puWtNom > 100) puWtup = 1.0;
	if(puWtdown/puWtNom > 100) puWtdown = 1.0;
      }
    }
    else {puWtup = 1.0; puWtdown = 1.0;}

   if((s_data.Contains("v17_2016") || s_data.Contains("v17_2017") ) && apply_L1){
     if(puwt=="up") wt=Weight*1000.0*NonPrefiringProb*lumiInfb*puWtup; 
     if(puwt=="down") wt=Weight*1000.0*NonPrefiringProb*lumiInfb*puWtdown; 
     else wt=Weight*1000.0*NonPrefiringProb*lumiInfb*puWtNom;
     h_nEvts->Fill(1,wt);
     }
    if((s_data.Contains("v17_2016") || s_data.Contains("v17_2017") ) && !apply_L1){
      if(puwt=="up") wt=Weight*1000.0*lumiInfb*puWtup; 
      if(puwt=="down") wt=Weight*1000.0*lumiInfb*puWtdown; 
      else wt=Weight*1000.0*lumiInfb*puWtNom;
      
      h_nEvts->Fill(1,wt);

      // if(s_data.Contains("v17_2017")) wt=wt;
      }


    if(s_data.Contains("v17_2018")){
      wt=Weight*1000.0*lumiInfb*(puhist->GetBinContent(puhist->GetXaxis()->FindBin(min(TrueNumInteractions,puhist->GetBinLowEdge(puhist->GetNbinsX()+1)))));
      h_nEvts->Fill(1,wt);
      if(puwt=="up") wt=Weight*1000.0*lumiInfb*puWtup; 
      if(puwt=="down") wt=Weight*1000.0*lumiInfb*puWtdown; 
      else wt=Weight*1000.0*lumiInfb*puWtNom;
      //      if(s_data.Contains("v17_2018")) wt=wt;
    }


    if(s_data.Contains("data")) { jec2Use=0; jer2Use=0;}
    //^^^^^^^^^^^^ Original/Nominal JEC/JER jets
    if(jec2Use!=0 || jer2Use!=0) changeJets(jec2Use, jer2Use, jet2Vary, varyMasswithJEC);

    ///////////////////////////////////////////////////////////////////////////////////////



     float dphi1=4, dphi2=4, dphi3=4, dphi4=4, dphi1AK8 = 3.5, dphi2AK8 = 3.5;
    if(Jets->size() > 0 && (*Jets)[0].Pt() > 30 && abs((*Jets)[0].Eta()) < 5.0)
      dphi1 = (abs(DeltaPhi(METPhi,(*Jets)[0].Phi())));
    if(Jets->size() > 1 && (*Jets)[1].Pt() > 30 && abs((*Jets)[1].Eta()) < 5.0)
      dphi2 = (abs(DeltaPhi(METPhi,(*Jets)[1].Phi())));
    if(Jets->size() > 2 && (*Jets)[2].Pt() > 30 && abs((*Jets)[2].Eta()) < 5.0)
      dphi3 = (abs(DeltaPhi(METPhi,(*Jets)[2].Phi())));
    if(Jets->size() > 3 && (*Jets)[3].Pt() > 30 && abs((*Jets)[3].Eta()) < 5.0)
      dphi4 = (abs(DeltaPhi(METPhi,(*Jets)[3].Phi())));
    //    if((dphi1 < 1.5) || (dphi2 < 0.5) || (dphi3 < 0.3) || (dphi4 < 0.3)) continue; 
    //    if((dphi1 < 1.5)|| (dphi2 < 0.5) )continue;
    // if(!(JetsAK8->size()>0 && (*JetsAK8)[0].Pt() > 200 && abs((*JetsAK8)[0].Eta()) < 2.4)) continue;

    // if(JetsAK8->size() > 0 && (*JetsAK8)[0].Pt() > 200) dphi1AK8 = abs(DeltaPhi((*JetsAK8)[0].Phi(),METPhi));
    // if(JetsAK8->size() > 1 && (*JetsAK8)[1].Pt() > 200) dphi2AK8 = abs(DeltaPhi((*JetsAK8)[1].Phi(),METPhi));

    // if(dphi1AK8 < 1.5 || dphi2AK8 < 0.5) continue;

    if(MET/CaloMET > 2.0) continue;
    //    if(HT5/HT > 1.2) continue; 
   //=========================================

     bool HEMaffected = false;
    //////-======== HEM issue ==================//////////////
    if(s_data.Contains("2018") && apply_HEMveto){
      for(int i=0; i<Electrons->size();i++)
        if((*Electrons)[i].Pt() >30 && (*Electrons)[i].Eta() > -3.0 && (*Electrons)[i].Eta() < -1.4 && (*Electrons)[i].Phi() > -1.57 && (*Electrons)[i].Phi() < -0.87) {HEMaffected = true; break;}
      for(int i=0; i<Jets->size();i++)
        if((*Jets)[i].Pt() > 30 && (*Jets)[i].Eta() > -3.2 && (*Jets)[i].Eta() < -1.2 && (*Jets)[i].Phi() > -1.77 && (*Jets)[i].Phi() < -0.67 && DeltaPhi((*Jets)[i].Pt(),METPhi)<0.5) {HEMaffected = true; break;}
     if(HEMaffected == true) continue;
   }

    /*
    if(s_data.Contains("data") )
      applybTagSFs=false;

    //-------------- btag SFs                                                                                                   
    if(fListIndxOld!=fCurrent){
      fListIndxOld = fCurrent;
      sampleName = inFileName[fCurrent];

      if(applybTagSFs && s_data.Contains("v17")){
        currFile = TFile::Open(sampleName);
        btagcorr.SetEffs(currFile);
        if(s_data.Contains("v17_2016")) btagcorr.SetCalib("btag/DeepCSV_Moriond17_B_H_mod.csv");
        if(s_data.Contains("v17_2017")) btagcorr.SetCalib("btag/DeepCSV_94XSF_V3_B_F_mod.csv");
        if(s_data.Contains("v17_2018")) btagcorr.SetCalib("btag/DeepCSV_102XSF_V1_mod.csv");
      }
    }
    */
    bool tighte_trgpass=true; 
    if(s_data.Contains("data") && applytrg)      
      {
	if(TriggerPass->size()!=148) continue; 
	if((*TriggerPass)[124]==1 || (*TriggerPass)[110]==1 || (*TriggerPass)[112]==1 || (*TriggerPass)[116]==1 || (*TriggerPass)[118]==1 || (*TriggerPass)[120]==1 ) tighte_trgpass=true; 
	else tighte_trgpass=false; 

	if(tighte_trgpass==false)  continue;
      }
    

    if(!s_data.Contains("data") && !s_data.Contains("FastSim") && applytrg)
      {
	wt = wt * (((TMath::Erf((MET - p0)/p1)+1)/2.0)*p2);
	
	/*
	  if(MET>200 && MET<300)
	  wt=wt*0.9;
	  else wt=wt*0.97;
	*/
      }


    if(s_data.Contains("TTJets2"))
      {//cout<<" correct "<<endl;
   	if ( madHT>600) continue;
      }				    
    if(!s_data.Contains("FastSim") && apply_METfilters){
     
      if(s_data.Contains("data"))
	if(!(PrimaryVertexFilter==1 && globalSuperTightHalo2016Filter == 1 && HBHENoiseFilter==1 && HBHEIsoNoiseFilter==1 && EcalDeadCellTriggerPrimitiveFilter == 1 && BadPFMuonFilter && ecalBadCalibReducedExtraFilter && eeBadScFilter==1 && NVtx>0 && eeBadScFilter)) continue;

      if(s_data.Contains("v17"))
	if(!(PrimaryVertexFilter==1 && globalSuperTightHalo2016Filter == 1 && HBHENoiseFilter==1 && HBHEIsoNoiseFilter==1 && EcalDeadCellTriggerPrimitiveFilter == 1 && BadPFMuonFilter && ecalBadCalibReducedExtraFilter && NVtx>0 && eeBadScFilter)) continue;

      // if(s_data.Contains("data_2016"))
      // 	if(!(PrimaryVertexFilter==1 && globalSuperTightHalo2016Filter == 1 && HBHENoiseFilter==1 && HBHEIsoNoiseFilter==1 && EcalDeadCellTriggerPrimitiveFilter == 1 && BadPFMuonFilter  && eeBadScFilter==1 && NVtx>0)) continue;

      // if(s_data.Contains("v17_2016"))
      // 	if(!(PrimaryVertexFilter==1 && globalSuperTightHalo2016Filter == 1 && HBHENoiseFilter==1 && HBHEIsoNoiseFilter==1 && EcalDeadCellTriggerPrimitiveFilter == 1 && BadPFMuonFilter && NVtx>0)) continue;
      
      // if(s_data.Contains("data_2018") || s_data.Contains("data_2017"))
      // 	if(!(PrimaryVertexFilter==1 && globalSuperTightHalo2016Filter==1 && HBHENoiseFilter==1 && HBHEIsoNoiseFilter==1 && EcalDeadCellTriggerPrimitiveFilter == 1 && BadPFMuonFilter && ecalBadCalibReducedFilter && ecalBadCalibReducedExtraFilter && eeBadScFilter==1)) continue;

      // if(s_data.Contains("v17_2018") || s_data.Contains("v17_2017"))
      // 	if(!(PrimaryVertexFilter==1 && globalSuperTightHalo2016Filter==1 && HBHENoiseFilter==1 && HBHEIsoNoiseFilter==1 && EcalDeadCellTriggerPrimitiveFilter == 1 && BadPFMuonFilter && ecalBadCalibReducedFilter && ecalBadCalibReducedExtraFilter)) continue;

           // if(!(CSCTightHaloFilter==1 && HBHENoiseFilter==1 && HBHEIsoNoiseFilter==1 && eeBadScFilter==1 && EcalDeadCellTriggerPrimitiveFilter==1 && BadPFMuonFilter && NVtx > 0) ) continue;
    

      // if(s_data.Contains("data"))
      // 	{
      // 	  //	  if(s_data.Contains("2016")) //ecalBadCalibReducedExtraFilter = 1;

      // 	  if(!(globalSuperTightHalo2016Filter == 1 && HBHENoiseFilter==1 && HBHEIsoNoiseFilter==1 && EcalDeadCellTriggerPrimitiveFilter == 1 && BadPFMuonFilter  && eeBadScFilter==1 && NVtx>0  && JetID && JetIDAK8 && ecalBadCalibReducedExtraFilter)) continue;
      // 	}
      // if(s_data.Contains("v17"))
      // 	{
      // 	  //	  eeBadScFilter = 1;
      // 	  if(!(globalSuperTightHalo2016Filter == 1 && HBHENoiseFilter==1 && HBHEIsoNoiseFilter==1 && EcalDeadCellTriggerPrimitiveFilter == 1 && BadPFMuonFilter && NVtx>0 && eeBadScFilter==1 && JetID && JetIDAK8 && ecalBadCalibReducedExtraFilter)) continue;
      // 	}
    if(PFCaloMETRatio >=  5) continue;

    }
    if(globalSuperTightHalo2016Filter) a++;
    if(HBHENoiseFilter) b++;
    if(HBHEIsoNoiseFilter) c++;
    if(EcalDeadCellTriggerPrimitiveFilter) d++;
    if(ecalBadCalibReducedExtraFilter) e++;
    if(BadPFMuonFilter) f++;
    if(PrimaryVertexFilter) g++;
    if(NVtx>0) h++;
   
 
    //-----------------------------------------cutflows--------------------------------------    
    h_selectBaselineYields_->Fill("No cuts, evt in 35.9/fb",1);
    h_selectBaselineYields_2->Fill("No cuts, evt in 35.9/fb",wt);
    h_selectBaselineYields_2->Fill("Good #gamma with Pt > 100",wt);
    h_selectBaselineYields_2->Fill("veto electron Muon",wt);
    h_selectBaselineYields_2->Fill("veto electron > 1",wt);
    h_selectBaselineYields_2->Fill("Iso track",wt);
    h_selectBaselineYields_2->Fill("MET>100",wt);
    h_selectBaselineYields_2->Fill("nJets >= 2",wt);
    //h_selectBaselineYields_2->Fill("ST & photon pt selec",wt);
    h_selectBaselineYields_2->Fill("MET & photon pt selec",wt);
    h_selectBaselineYields_2->Fill("dPhi1 & dPhi2 >= 0.3",wt);
    h_selectBaselineYields_2->Fill("Before Pre-Selections",wt);
    h_selectBaselineYields_2->Fill("real photon",wt);
    h_selectBaselineYields_2->Fill("Pass Acceptance",wt);
    h_selectBaselineYields_2->Fill("Pass el^{-} ID",wt);
    h_selectBaselineYields_2->Fill("Pass Isolation",wt);

    h_selectBaselineYields_2->Fill("SR : Electrons = 0",wt);
    h_selectBaselineYields_2->Fill("CR : Electrons = 1",wt);

    // h_selectBaselineYields_2->Fill("MET>200",wt);
    // h_selectBaselineYields_2->Fill("BTags >= 1",wt);
    // h_selectBaselineYields_2->Fill("BTags = 0",wt);

   bool event_passed_old=false, event_passed_new=false;



   //============== Baseline Selections====================//

   vector<TLorentzVector> goodPho_;
   // vector<int> goodPhoIndx;
   for(int iPho=0;iPho<Photons->size();iPho++){
     if( (*Photons_fullID)[iPho] ) 
       {
	 goodPho_.push_back( (*Photons)[iPho] );
	 // goodPhoIndx.push_back(iPho);
       }
   }

   int hasEle=0, hasPho=0, hasPho_px=0;
   TLorentzVector bestPhoton=getBestPhoton();
   TLorentzVector nobestPhoton=getPhoton_withoutfullID();

   bool bestPhoHasPxlSeed=true, noPhoHasPxlSeed=true;
   bool eMatchedG=check_eMatchedtoGamma(bestPhoton);
   ////////========== ISR weighting ////////////////.
 
   if(applISRWtsTottbar && ((s_data.Contains("TTJets_v17_2016")||s_data.Contains("TTJets2_v17_2016")||s_data.Contains("TTG_v17_2016")))){
     double isrWt = 0;
     vector<double> D_values={1.0697, 1.0150, 0.9917, 0.9435, 0.95};
     vector<double> isrwt_arr={1., 0.920, 0.821, 0.715, 0.662, 0.561, 0.511};
     if(NJetsISR>=6) isrWt = isrwt_arr[6];
     else isrWt = isrwt_arr[NJetsISR];
     
     if(madHT<600) isrWt = isrWt*D_values[0];
     else if(madHT < 800) isrWt = isrWt*D_values[1];
     else if(madHT < 1200) isrWt = isrWt*D_values[2];
     else if(madHT < 2500) isrWt = isrWt*D_values[3];
     else isrWt = isrWt*D_values[4];
     wt = wt*isrWt;
   }
   

   //// Stitching TTJets & TTGamma samples. Similarly WJets & WGamma samples 
   if(!s_data.Contains("data"))
     {
       genphomatch_before++;
       double mindr_Pho_genlep=getGenLep(bestPhoton);
       if(s_data=="genprompt" || s_data.Contains("TTG") )
     	 {
     	   if(!hasGenPromptPhoton)
     	     {
     	       if(jentry==0)cout<<"**********processing "<<s_data<<" with non-prompt Gen photon"<<endl;
     	     }
     	   else if(hasGenPromptPhoton)
     	     {
     	       if(!(madMinPhotonDeltaR >= 0.3 && mindr_Pho_genlep >=0.5 ))continue;	   
     	       else
     		 h_mindr_genph_lep->Fill(mindr_Pho_genlep,wt);
     	     }
     	 }//Gen prompt       
       if(s_data=="genprompt" || s_data.Contains("WG"))
     	 {
     	   if(!hasGenPromptPhoton)
     	     {
     	       if(jentry==0)cout<<"**********processing "<<s_data<<" with non-prompt Gen photon"<<endl;
     	     }
     	   else if(hasGenPromptPhoton)
     	     {
     	       if(!(madMinPhotonDeltaR >= 0.5 && mindr_Pho_genlep >=0.5 ))continue;
     	     }
     	 }//Gen prompt                                                                                                                         
     	
       if(s_data.Contains("WJets"))
     	 {
     	   if(!hasGenPromptPhoton)
     	     {
     	       if(jentry==0)cout<<"**********processing "<<s_data<<" with non-prompt Gen photon"<<endl;
     	     }
     	   else if(hasGenPromptPhoton)
     	     {
     	       if(!(madMinPhotonDeltaR < 0.5 || mindr_Pho_genlep < 0.5)) continue;
     	     }
     	 }

       if(s_data.Contains("TTJets") || s_data.Contains("TTJets_v17") || s_data.Contains("TTJets2_v17"))
     	    {
     	      if(!hasGenPromptPhoton)
     		{
     		  if(jentry==0)cout<<"**********processing "<<s_data<<" with non-prompt Gen photon"<<endl;
     		}
     	      else if(hasGenPromptPhoton)
     		{
     		  if(!(madMinPhotonDeltaR < 0.3 || mindr_Pho_genlep < 0.5)) continue;
     		}	     
     	    }
       //Gen non-prompt
     }	  
   
   genphomatch_after++;





  
   
    //=========================================================================//

    // //veto Muon    
    if (NMuons > 0) continue;
    else
      h_selectBaselineYields_->Fill("veto Muon",wt);                                                                           

    if(isoMuonTracks ==0 && isoPionTracks==0)
      {
    	int a;
    	h_selectBaselineYields_->Fill("Iso track",wt);
      }
    else continue;                                   
        // //exactly 1 reco electron or 0 reco electron
    if (NElectrons > 1) continue;
    else
      h_selectBaselineYields_2->Fill("veto electron > 1",wt);     


    //    cout<<NElectrons<<endl;
    
    //=============================================================
    //=============================================================
    //Fake rate/////////////
    //=============================================================
    //=============================================================
       
   if(bestPhotonIndxAmongPhotons>=0){
     if((*Photons_hasPixelSeed)[bestPhotonIndxAmongPhotons]<0.001) bestPhoHasPxlSeed=false;
     //     if(!eMatchedG && !bestPhoHasPxlSeed && bestPhoton.Pt()>100) hasPho=1;                                                                                                             
     if(!bestPhoHasPxlSeed && bestPhoton.Pt()>100)
       {
	 hasPho=1;hasPho_px=0; 
	 //	 cout<<jentry<<(*Photons_passElectronVeto)[bestPhotonIndxAmongPhotons]<<endl;
       }                                                                                    
                   
     else if(bestPhoHasPxlSeed && bestPhoton.Pt()>100) {hasPho_px=1;hasPho=0;}// npho_px++;}                                                                                        
                           
     else
       {
          hasPho_px=0;
          hasPho=0;
        }
   }

   // if(eIndxAmongPhotons>=0)
   //   {
    
   //     if((*Photons_hasPixelSeed)[eIndxAmongPhotons]<0.001) noPhoHasPxlSeed=false;
   //     if(noPhoHasPxlSeed && nobestPhoton.Pt()>100) {hasEle=1;}     
   //   }

   double mt_ele=0,mt_pho=0,mt_ele1=0;
	
   TLorentzVector v_lep1,v_lep2;

   if(NElectrons==1)
     {
       for(int i=0 ; i<Electrons->size() ; i++)
   	 {
   	   if((*Electrons_passIso)[i]==1)
   	     {
   	       nlep++;
   	       e_index=i;
   	       v_lep1=(*Electrons)[i];
   	     }
   	 }
     }

   if(nlep==1 && v_lep1.Pt()>100 && tighte_trgpass && (s_data.Contains("data")))
     {
       hasEle=1;
       lep++;	    
     }
   if(nlep==1 && v_lep1.Pt()>100 && !(s_data.Contains("data")))
     {
       hasEle=1;
       lep++;	    
     }
     

   
    bool bestEMObjIsEle=false, bestEMObjIsEle_px=false,bestEMobj=false;
    TLorentzVector bestEMObj;
    if (hasEle==1 && hasPho==0) {bestEMObjIsEle=true; bestEMObjIsEle_px=false;bestEMObj = (*Electrons)[e_index]; bestEMobj=true;}
    if(hasEle==0 &&  hasPho==1) {bestEMObjIsEle=false;  bestEMObjIsEle_px=false;bestEMObj = bestPhoton; bestEMobj=true;}
    if(bestEMobj==false) { continue;}

    if(apply_pixelveto){

      if(s_data.Contains("2017") && ((bestEMObj.Eta() > 0.0 && bestEMObj.Eta() < 1.5 && bestEMObj.Phi() > 2.7))) continue;						  
      if(s_data.Contains("2018") && ((bestEMObj.Eta() > 0.0 && bestEMObj.Eta() < 1.5 && bestEMObj.Phi() > 0.4 && bestEMObj.Phi() < 0.8))) continue;
    }


   if(bestEMObjIsEle)  
     {
       mt_ele=sqrt(2*bestEMObj.Pt()*MET*(1-cos(DeltaPhi(METPhi,bestEMObj.Phi()))));
       if(mt_ele>100 ) continue;
       elec_reco++;	    
     }

   bool fakePhoton=false;


   int nGenEle1=0, nGenPho1=0;
   TLorentzVector genEle1, genPho1;
   vector<TLorentzVector> v_genEle2,v_genPho2;
   if(!s_data.Contains("data")){
     for(int i=0 ; i < GenParticles->size(); i++)
       {
	 if((*GenParticles)[i].Pt()!=0 && (abs((*GenParticles_PdgId)[i])==11) && (abs((*GenParticles_ParentId)[i])<=24))
	   {
	     nGenEle1++;
	     genEle1 = ((*GenParticles)[i]);
	     v_genEle2.push_back(genEle1);
	   }
	 if((*GenParticles)[i].Pt()!=0 && (abs((*GenParticles_PdgId)[i])==22))
	   {
	     nGenPho1++;
	     genPho1 = ((*GenParticles)[i]);
	     v_genPho2.push_back(genPho1);
	   }
       }
   }
	

   
   if(!bestEMObjIsEle && bestEMobj)
     {
       if(!s_data.Contains("data")){
	 if(!(*Photons_electronFakes)[bestPhotonIndxAmongPhotons])
	   { //h_mindr_lep_goodph->Fill(MinDr(bestPhoton,v_genEle2),wt);
	     //h_mindr_goodph_lep->Fill(MinDr((*Photons)[bestPhotonIndxAmongPhotons],v_genEle1),wt);                                                                                                             
	     pass_realphoton++;
	     fakePhoton=false;
	   }
	 else
	   {
	     //	     h_mindr_lep_goodph->Fill(MinDr(bestPhoton,v_genEle2),wt);
	     fail_realphoton++;
	     fakePhoton=true;
	   }

	 if(!fakePhoton)
	   continue;
	 
       }
       if(isoElectronTracks!=0 || isoMuonTracks!=0 || isoPionTracks!=0) continue;
       // //exactly 1 reco electron or 0 reco electron
       if (NElectrons != 0) continue;
       else
	 h_selectBaselineYields_2->Fill("veto electron > 0",wt);     


     }
    //=============================================================
    //=============================================================
      

    //========= hadjet -> removing jets which are matched with photon within mindr 0.3 =====//
    bool hadJetID=false;
 
    int minDRindx=-100,photonMatchingJetIndx=-100,nHadJets=0;
    double minDR=99999,ST=0,remJetPt=0;
    vector<TLorentzVector> hadJets, remJets;
    double nbjets=0;
    int bJet1Idx = -1;

    vector<TLorentzVector> nonbjets,bjets;

    for(int i=0;i<Jets->size();i++){
      if( ((*Jets)[i].Pt() > 30.0) && (abs((*Jets)[i].Eta()) <= 2.4) )
	{
            {
	      double dR=bestEMObj.DeltaR((*Jets)[i]);
	      if(dR<minDR){minDR=dR;minDRindx=i;}
	    }
	}
    }

    int q=0;
    for(int i=0;i<Jets->size();i++){
      if( ((*Jets)[i].Pt() > 30.0) && (abs((*Jets)[i].Eta()) <= 2.4) ){
	//	q++;
	if( !(minDR < 0.3 && i==minDRindx) )
	  {
	    hadJetID=(*Jets_ID)[i];
	    if(hadJetID)
	      {
		q++;
		hadJets.push_back((*Jets)[i]);
		if(q==1) leadjet_qmulti=(*Jets_chargedMultiplicity)[q];
		if(q==1) leadjet_Pt=(*Jets)[q].Pt();	
		if((*Jets_bJetTagDeepCSVBvsAll)[i] > deepCSVvalue){
		  bjets.push_back((*Jets)[i]); bJet1Idx = i;}
	      }
	  }      
      }  
    }
    //    cout<<jentry<<" ====== break ========"<<endl;
    if( minDR<0.3)
      {
	photonMatchingJetIndx=minDRindx;
	qmulti=(*Jets_chargedMultiplicity)[photonMatchingJetIndx];
	leadbjet_tag=(*Jets_bJetTagDeepCSVBvsAll)[photonMatchingJetIndx];
      }
     
      
    //now hadJets contains all jets except the one matched to emObject. check whether there is energy near emObj or not. If yes then add it as a jet.
    if( photonMatchingJetIndx>=0 ){
      if( ((*Jets)[photonMatchingJetIndx].Pt()) > 1.1*(bestEMObj.Pt()) ){
	if( (((*Jets)[photonMatchingJetIndx] - bestEMObj).Pt())>30){
	  hadJets.push_back( (*Jets)[photonMatchingJetIndx] - bestEMObj );
	  remJetPt=((*Jets)[photonMatchingJetIndx] - bestEMObj).Pt();
	  remJets.push_back( (*Jets)[photonMatchingJetIndx] - bestEMObj );
	}
      }
    }

    
    if(hadJets.size() == 0) continue;  

    for(int i=0;i<hadJets.size();i++)
      {
	if( (abs(hadJets[i].Eta()) < 2.4) ){ST=ST+(hadJets[i].Pt());}
	if( (abs(hadJets[i].Eta()) < 2.4) ){nHadJets++;}
      }
    
    for(int i=0;i<bjets.size();i++)
      if( (abs(bjets[i].Eta()) < 2.4) ){nbjets++;}

    if( minDR<0.3 ){
      ST=ST+bestEMObj.Pt();
    }
    sortTLorVec(&hadJets);

    
    //Minimum MET
    if( MET>200)  
      {
	h_selectBaselineYields_->Fill("MET>200",wt);
      }
    else continue;

    // Minimum 2 jets (photon is not counted as jet)
    if( nHadJets >= 2 )
      {
      	h_selectBaselineYields_->Fill("nJets >= 2",wt);
      }

    else
      {
      continue;
      }
    

    TLorentzVector Met;
    double mT=0, dPhi_METjet1=10,dPhi_METjet2=10, dPhi_phojet1=10, dPhi_phojet2=10, dPhi_phoMET=10;
    double dPhi_METjet3=10,dPhi_METjet4=10, dPhi_phojet3=10, dPhi_phojet4=10;
    Met.SetPtEtaPhiE(MET,0,METPhi,0);
    if(hadJets.size() > 0)    dPhi_phojet1 = abs(bestPhoton.DeltaPhi(hadJets[0]));
    if(hadJets.size() > 1)    dPhi_phojet2 = abs(bestPhoton.DeltaPhi(hadJets[1]));
    dPhi_phoMET = abs(bestPhoton.DeltaPhi(Met));

    double mindphi=1000;
    if(hadJets.size() > 0) {   dPhi_METjet1 = abs(Met.DeltaPhi(hadJets[0]));mindphi=dPhi_METjet1;}
    if(hadJets.size() > 1)  {  dPhi_METjet2 = abs(Met.DeltaPhi(hadJets[1])); if(dPhi_METjet2<mindphi) mindphi=dPhi_METjet2;}

    double mTPhoMET=sqrt(2*(bestEMObj.Pt())*MET*(1-cos(DeltaPhi(METPhi,bestEMObj.Phi()))));

    //Minimum dPhi cut between MET and leading two jets
    if(highdphi)
      {
	if(dPhi_METjet1 > 0.3 && dPhi_METjet2 > 0.3 )
	  {
	    h_selectBaselineYields_->Fill("dPhi1 & dPhi2 >= 0.3",wt);
	  }
	else continue;
      }
    if(!highdphi)
      { 
        if(!(dPhi_METjet1 > 0.3 && dPhi_METjet2 > 0.3 ))
          {
            h_selectBaselineYields_->Fill("dPhi1 & dPhi2 >= 0.3",wt);
          }
	//        else continue;
      } 
    
      
    // //============== New Trigger selections ================				     
    if( (ST <= 300) ) continue;
    bool process= false;
    if(highdphi && ST>300 && nHadJets>=2 && MET > 200 && dPhi_METjet1 > 0.3 && dPhi_METjet2 > 0.3)
      process =true;
    if(!highdphi && ST>300 && nHadJets>=2 && MET > 200  && !(dPhi_METjet1 > 0.3 && dPhi_METjet2 > 0.3))
      //if(!highdphi && ST>300 && nHadJets>=2 && MET > 200)
      process =true;
   if(!process) continue;
   //   if(MET<=300) continue;
    //============== EWkino selections ===============

  
    //===============Ak8 Jets =====================
    bool hadAK8JetID =false;
    int minDR4indx=-100,minDR5indx , Ak8ID=-100;//photonMatchingJetIndx=-100,nHadJets=0;
    double minDR4=99999,minDR5;
    vector<TLorentzVector> hadAK8Jets;
    vector<TLorentzVector> hadAK8Jets_matchedW;
    vector<double> hadAK8Mass, hadAK8Mass_matchedW;
    double Ak8Mass,max=0.0,Ak8Mass1;
    for(int i=0;i<JetsAK8->size();i++)
      if( ((*JetsAK8)[i].Pt() > 200.0) && (abs((*JetsAK8)[i].Eta()) <= 2.4) ){
	double dR4=bestEMObj.DeltaR((*JetsAK8)[i]);
	if(dR4<minDR4){minDR4=dR4;minDR4indx=i;}
      }
    
    for(int i=0;i<JetsAK8->size();i++)
      if( ((*JetsAK8)[i].Pt() > 200.0) && (abs((*JetsAK8)[i].Eta()) <= 2.4) ){
	if( !(minDR4 < 0.8 && i==minDR4indx) ){
	  hadAK8JetID=(*JetsAK8_ID)[i];
	  if(hadAK8JetID)
	    {
	      hadAK8Jets.push_back((*JetsAK8)[i]);
	      hadAK8Mass.push_back((*JetsAK8_softDropMass)[i]);
	    }
	}
      }
  

    if(hadAK8Jets.size() == 0)
      {
	Ak8Mass=0;
      }
    else if (hadAK8Jets.size() != 0)
      {
	Ak8Mass=hadAK8Mass[0];
      }

    
    //==============Ak8 EW selection=====================//
    if(EWselection)
      {
	//for(int i=0;i<hadAK8Jets.size();i++)
	EWselec=false;
	EWselec_Htag=false;
	EWselec_Wtag=false;
	EWselec_SB1=false;
	EWselec_SB2=false;

	if(hadAK8Jets.size() != 0)
	  {
	    if ((hadAK8Mass[0] < 105 && hadAK8Mass[0] >= 65))// || (hadAK8Mass[0] < 110 && hadAK8Mass[0] > 140))
	      {
		EWselec=true;
		EWselec_Wtag=true;
		EWselec_Htag=false;
		EWselec_SB1=false;
		EWselec_SB2=false;
	      }

	    else if ((hadAK8Mass[0] < 140 && hadAK8Mass[0] >= 105))
	      {
		EWselec=true;
		EWselec_Htag=true;
		EWselec_Wtag=false;
		EWselec_SB1=false;
		EWselec_SB2=false;

	      }


	    else
	      {
		EWselec=false;
		EWselec_Htag=false;
		EWselec_Wtag=false;
		EWselec_SB1=false;
		EWselec_SB2=false;

	      }
	  }


	if(hadJets.size()<=6)
	  EWselec1=true;
	else
	  EWselec1=false;
      }

	

    vector<TLorentzVector> v_genb,v_gene;
    vector<TLorentzVector> v_btag;
    vector<int> Parent_id , id;
    vector<double> dR_bandjets; 
    if(process && EWselection && hadJetID)
      {
	evtSurvived_preselec++;     
 	Jete++;
	if(bestEMObjIsEle )
	  {
	    nele++;
	    //	    if((s_data.Contains("2016")) && leadbjet_tag>0.6321) continue;
	    //	    if((s_data.Contains("2017")) && leadbjet_tag>0.4941) continue;
	    //	    if((s_data.Contains("2018")) && leadbjet_tag>0.4184) continue;
	    
	    h_deepcsv->Fill(leadbjet_tag,wt);

	    h_selectBaselineYields_->Fill("CR : Electrons = 1",wt);

	    int sBin6 = getBinNoV7(bestEMObj,qmulti,minDRindx);
	    if(sBin6 != -999)
	      h_SBins_v6_CD_elec1->Fill(sBin6,wt);
	    int sBin7_SP_elec1 = getBinNoV7_le2(EWselec,EWselec1 ,EWselec_Htag,EWselec_Wtag,nHadJets);
	    h_SBins_v7_CD_SP_elec1->Fill(sBin7_SP_elec1,wt);
	    int sBin6_SP_elec1 = getBinNoV6(bestEMObj,nHadJets);
	    h_SBins_v6_CD_SP_elec1->Fill(sBin6_SP_elec1,wt);
	    int sBin6_50bin= getBinNoV6_EWplusSP_CR(EWselec,EWselec1 ,EWselec_Htag,EWselec_Wtag,nbjets,nHadJets);
	    h_SBins_v6_CD_EW_50bin_elec1->Fill(sBin6_50bin,wt);


	    h_MET->Fill(MET,wt);
	    h_METPhi->Fill(METPhi,wt);
	    h_METvBin2->Fill(MET,wt);
	    h_nJets->Fill(nHadJets,wt);
	    h_ST->Fill(ST,wt);
	    h_BTags->Fill(nbjets,wt);
	    h_DBTags->Fill(abs(nbjets-BTags),wt);
	    //	    h_NEMobj->Fill(NElectrons,wt);
	    h_NEMobj->Fill(goodPho_.size(),wt);

	    // h_minDr_bestphoEle->Fill(MinDr2(hadJets,bestEMObj),wt);
	    h_minDr_bestphoEle->Fill(MinDr(bestEMObj,remJets),wt);
	    h_minDr_bestphoJets->Fill(MinDr(bestEMObj,hadJets),wt);
	  
	    h_CM_Ele->Fill(qmulti,wt);
	    h_EMObj_pT->Fill(bestEMObj.Pt(),wt);
	    h2_PhoPtQMultJet->Fill(bestEMObj.Pt(),qmulti,wt);
	    h2_PhoPtQMultJet_v2->Fill(bestEMObj.Pt(),qmulti,wt);
	    h2_PhoPtQMultJet_v3->Fill(bestEMObj.Pt(),qmulti,wt);
	    h2_METQMultJet->Fill(MET,qmulti,wt);
	    h2_PhoPtMET->Fill(bestEMObj.Pt(),MET,wt);
	    h2_nJetsMET->Fill(nHadJets,MET,wt);
	    h2_PhoPtnJets->Fill(bestEMObj.Pt(),nHadJets,wt);
	    h3_PhoPtnJetsbtags->Fill(bestEMObj.Pt(),nHadJets,BTags,wt);
	    h3_PhoPtnJetsQmult->Fill(bestEMObj.Pt(),nHadJets,qmulti,wt);
	    h2_nJetsQMultJet->Fill(nHadJets,qmulti,wt);
	    h_nvtx->Fill(NVtx,wt);
	    h2_MET_dPhiMETj->Fill(MET,mindphi,wt);
	    h2_MET_dPhiMETj1->Fill(MET,dPhi_METjet1,wt);
	    h2_MET_dPhiMETj2->Fill(MET,dPhi_METjet2,wt);
	        
	    /////////////////
	    int sBin7_50bin= getBinNoV6_EWplusSP_CR(EWselec,EWselec1 ,EWselec_Htag,EWselec_Wtag,nbjets,nHadJets);
	    h2_PhoPtQMultJet_fr[sBin7_50bin]->Fill(bestEMObj.Pt(),qmulti,wt);
            h2_PhoPtQMultJet_SF[sBin7_50bin]->Fill(qmulti,wt);

	    ////////////
	    if(photonMatchingJetIndx<0) 
	      {
		h2_QMultlleadbJet_v2->Fill(bestEMObj.Pt(),(*Jets)[photonMatchingJetIndx].Pt()/bestEMObj.Pt(),wt);
	      }
	    else
	      h2_BestPhotonPt_jetmatchphoratio->Fill(bestEMObj.Pt(),(*Jets)[photonMatchingJetIndx].Pt()/bestEMObj.Pt(),wt);

	    for(int j=0; j<hadJets.size();j++){
              h_JetPt->Fill(hadJets[j].Pt(),wt);
              h_JetEta->Fill(hadJets[j].Eta(),wt);
              h_JetPhi->Fill(hadJets[j].Phi(),wt);
              h2_JetEta_Phi->Fill(hadJets[j].Eta(),hadJets[j].Phi(),wt);
              h2_BestPhotonPt_jetphoratio->Fill(bestPhoton.Pt(),hadJets[j].Pt()/bestEMObj.Pt(),wt);
	      h2_JetEta_Pt->Fill(hadJets[j].Eta(),hadJets[j].Pt(),wt);          
	    }


	    if(hadJets.size()>0)
	      {
		h_JetPt1->Fill(hadJets[0].Pt(),wt);
		h_JetEta1->Fill(hadJets[0].Eta(),wt);
		h_JetPhi1->Fill(hadJets[0].Phi(),wt);
		h2_JetEta_Phi1->Fill(hadJets[0].Eta(),hadJets[0].Phi(),wt);
		h2_JetEta_Pt1->Fill(hadJets[0].Eta(),hadJets[0].Pt(),wt);          
	      }
	    if(hadJets.size()>1)
	      {
		h_JetPt2->Fill(hadJets[1].Pt(),wt);
		h_JetEta2->Fill(hadJets[1].Eta(),wt);
		h_JetPhi2->Fill(hadJets[1].Phi(),wt);
		h2_JetEta_Phi2->Fill(hadJets[1].Eta(),hadJets[1].Phi(),wt);
		h2_JetEta_Pt2->Fill(hadJets[1].Eta(),hadJets[1].Pt(),wt);          
	      }
	    if(hadJets.size()>2)
	      {
		h_JetPt3->Fill(hadJets[2].Pt(),wt);
		h_JetEta3->Fill(hadJets[2].Eta(),wt);
		h_JetPhi3->Fill(hadJets[2].Phi(),wt);
		h2_JetEta_Phi3->Fill(hadJets[2].Eta(),hadJets[2].Phi(),wt);
		h2_JetEta_Pt3->Fill(hadJets[2].Eta(),hadJets[2].Pt(),wt);          
	      }
	    if(hadJets.size()>3)
	      {
		h_JetPt4->Fill(hadJets[3].Pt(),wt);
		h_JetEta4->Fill(hadJets[3].Eta(),wt);
		h_JetPhi4->Fill(hadJets[3].Phi(),wt);
		h2_JetEta_Phi4->Fill(hadJets[3].Eta(),hadJets[3].Phi(),wt);
		h2_JetEta_Pt4->Fill(hadJets[3].Eta(),hadJets[3].Pt(),wt);          
	      }
	    h_dPhi_phoMET->Fill(dPhi_phoMET,wt);
 	    h_BestPhotonPhi->Fill((bestEMObj.Phi()),wt);
	    h_BestPhotonEta->Fill((bestEMObj.Eta()),wt);
	    h2_BestPhotonEta_Qmulti->Fill(bestEMObj.Eta(),qmulti,wt);
	    h2_BestPhotonEta_nJets->Fill(bestEMObj.Eta(),nHadJets,wt);
	    h2_BestPhotonEta_MET->Fill(bestEMObj.Eta(),MET,wt);

	    h2_nbjets_nJets->Fill(hadJets.size(),BTags,wt);
	    h2_leadElectronEta_Phi->Fill(bestEMObj.Eta(),bestEMObj.Phi(),wt);
	    h2_leadElectronPt_Eta->Fill(bestEMObj.Pt(),bestEMObj.Eta(),wt);
	    h2_leadElectronPt_Phi->Fill(bestEMObj.Pt(),bestEMObj.Phi(),wt);
	    h2_QMultlleadJetPt->Fill(leadjet_Pt,leadjet_qmulti,wt);
	    h2_QMultlleadbJet->Fill(qmulti,leadbjet_tag,wt);
	    h_MET_CaloMET->Fill(MET/CaloMET,wt);
	    h_dPhi_MET_CaloMET->Fill(abs(DeltaPhi(METPhi,CaloMETPhi)),wt);
	    h_HT5HT->Fill(HT5/HT,wt);
	    h_dPhi_METjet1->Fill(dphi1,wt);
	    h_dPhi_METjet2->Fill(dphi2,wt);
	    h_dPhi_METjet3->Fill(dphi3,wt);
	    h_dPhi_METjet4->Fill(dphi4,wt);
	    vector<TLorentzVector> v_jet;
	    for(int i=0;i<Jets->size();i++)
	      if(((*Jets)[i].Pt() > 30.0) && (abs((*Jets)[i].Eta()) <= 5))
		v_jet.push_back((*Jets)[i]);
	    if(v_jet.size()>0)
	      {
		h2_leadJetEta_Pt->Fill(v_jet[0].Eta(),v_jet[0].Pt(),wt);
		h2_HT5HT_dPhiMETj1->Fill(dphi1,HT5/HT,wt);
		h2_JPt_dPhiMETj1->Fill(dphi1,v_jet[0].Pt(),wt);
	      }
	    if(v_jet.size()>1)
	      {
		h2_2leadJetEta_Pt->Fill(v_jet[1].Eta(),v_jet[1].Pt(),wt);
		h2_HT5HT_dPhiMETj2->Fill(dphi2,HT5/HT,wt);
		h2_JPt_dPhiMETj2->Fill(dphi2,v_jet[1].Pt(),wt);
	    }
	    if(v_jet.size()>2)
	      {
		h2_3leadJetEta_Pt->Fill(v_jet[2].Eta(),v_jet[2].Pt(),wt);
		h2_HT5HT_dPhiMETj3->Fill(dphi3,HT5/HT,wt);
		h2_JPt_dPhiMETj3->Fill(dphi3,v_jet[2].Pt(),wt);
	      }

	    if(v_jet.size()>3)
	      {
		h2_4leadJetEta_Pt->Fill(v_jet[3].Eta(),v_jet[3].Pt(),wt);
		h2_HT5HT_dPhiMETj4->Fill(dphi4,HT5/HT,wt);
		h2_JPt_dPhiMETj4->Fill(dphi4,v_jet[3].Pt(),wt);
	      }
	    //	    cout<<jentry<<" : "<<leadbjet_tag<<" , "<<MinDr(bestEMObj,v_genb)<<endl;    
	    if(do_prediction && bestEMObjIsEle)
	      {
		double wt2=wt;
		double parX=-1,parY=-1,parZ=-1;
		if(minDRindx>=0)
		  {
		    parX=bestEMObj.Pt();
		    //parX=bestEMObj.Eta();           
		    //		    parY=nHadJets;
		    // parZ=BTags;
		    // parX=nHadJets;
		    parY=qmulti;
		    // parX=bestEMObj.Pt();
		    //parZ=qmulti;
		  }
		double fakerate=0;

	       
		//		fakerate=tf1->GetBinContent(tf1->FindBin(parX,parY,parZ));
		if(!old)
		  {
		    if(parX>0 && parX<300)
		      fakerate=tf->GetBinContent(tf->FindBin(parX,parY));
		    else if(parX>=300)
		      fakerate=tf2->GetBinContent(tf2->FindBin(parX,parY));
		  }
		if(old)		fakerate=tf->GetBinContent(tf->FindBin(parX,parY));
		
		//else{ cout<<"hist not found"<<endl; return;}

		wt2=fakerate*wt;
	    
		if(applySF && !applysys)
		  {
		    if(s_data.Contains("2016")) 
		      {

			if(parY==0 || parY==1) wt2=1.16*wt2;
			else  
			  wt2=(1.624*wt2);//1.6*wt2;
		      }
                    if(s_data.Contains("2017")) 
		      {
			wt2=2.837*wt2;//2.83*wt2;
		      }
                    if(s_data.Contains("2018")) wt2=1.797*wt2;//1.799*wt2;
		  }
                if(applySF && applysys)
                  {
                    if(s_data.Contains("2016"))
                      {
                        if(parY==0 || parY==1) wt2=1.16*wt2;
                        else
                          wt2=(1.624 + 0.062)*wt2;//1.6*wt2;                                                                                                                        
                      }
                    if(s_data.Contains("2017"))
                      {
                        wt2=(2.837 + 0.089)*wt2;//2.83*wt2;                                                                                                                           
                      }
                    if(s_data.Contains("2018")) wt2=(1.797 + 0.05)*wt2;//1.799*wt2;                                                                             
                     
                  }


		if(EWKsub)
		  {
		    if(!(EWselec && EWselec1)){
		      if(nbjets==0){
			if(nHadJets>=2 && nHadJets<=4 && MET<=300)     { wt2=wt2*mj_wt->GetBinContent(2);}
			else if(nHadJets>=2 && nHadJets<=4 && MET>300)     { wt2=wt2*mj_wt->GetBinContent(3);}
			else if((nHadJets==5 || nHadJets==6) && MET<=300){ wt2=wt2*mj_wt->GetBinContent(9);}
			else if((nHadJets==5 || nHadJets==6) && MET>300){ wt2=wt2*mj_wt->GetBinContent(10);}
			else if(nHadJets>=7  && MET<=300)   { wt2=wt2*mj_wt->GetBinContent(15);}
			else if(nHadJets>=7 && MET>300)   { wt2=wt2*mj_wt->GetBinContent(16);}
		      }
		      else{
			if(nHadJets>=2 && nHadJets<=4 && MET<=300)      { wt2=wt2*mj_wt->GetBinContent(20);}
			else if(nHadJets>=2 && nHadJets<=4 && MET>300)      { wt2=wt2*mj_wt->GetBinContent(21);}
			else if((nHadJets==5 || nHadJets==6) && MET<=300){ wt2=wt2*mj_wt->GetBinContent(25);}
			else if((nHadJets==5 || nHadJets==6) && MET>300){ wt2=wt2*mj_wt->GetBinContent(26);}
			else if(nHadJets>=7 && MET<=300)   { wt2=wt2*mj_wt->GetBinContent(30);}
			else if(nHadJets>=7 && MET>300)   { wt2=wt2*mj_wt->GetBinContent(31);}
		      }
		    }
		    else if((EWselec && EWselec1)){
		      if(EWselec_Wtag && !EWselec_Htag && MET<=300)     { wt2=wt2*mj_wt->GetBinContent(35);}
		      else if(EWselec_Wtag && !EWselec_Htag && MET>300)     { wt2=wt2*mj_wt->GetBinContent(36);}
		      else if(EWselec_Htag && !EWselec_Wtag  && MET<=300)      { wt2=wt2*mj_wt->GetBinContent(41);}
		      else if(EWselec_Htag && !EWselec_Wtag && MET>300)      { wt2=wt2*mj_wt->GetBinContent(42);}
		    }
		  }
	      
		int sBin6 = getBinNoV7(bestEMObj,qmulti,minDRindx);
		if(sBin6 != -999)
		  h_SBins_v6_CD_elec1_closure->Fill(sBin6,wt2);
		int sBin7_SP_elec1_closure = getBinNoV7_le2(EWselec,EWselec1 ,EWselec_Htag,EWselec_Wtag,nHadJets);
		h_SBins_v7_CD_SP_elec1_closure->Fill(sBin7_SP_elec1_closure,wt2);
		int sBin6_SP_elec1_closure = getBinNoV6(bestEMObj,nHadJets);
		h_SBins_v6_CD_SP_elec1_closure->Fill(sBin6_SP_elec1_closure,wt2);
		int sBin6_50bin= getBinNoV6_EWplusSP_CR(EWselec,EWselec1 ,EWselec_Htag,EWselec_Wtag,nbjets,nHadJets);
		h_SBins_v6_CD_EW_50bin_elec1_closure->Fill(sBin6_50bin,wt2);

		h_MET_elec1_closure->Fill(MET,wt2);
		//	    h_METPhi_elec1_closure->Fill(METPhi,wt2);
		h_METvBin2_elec1_closure->Fill(MET,wt2);
		h_nJets_elec1_closure->Fill(nHadJets,wt2);
		h_ST_elec1_closure->Fill(ST,wt2);
		h_BTags_elec1_closure->Fill(nbjets,wt2);
		h_DBTags_elec1_closure->Fill(abs(nbjets-BTags),wt2);
		//h_NEMobj_elec1_closure->Fill(NElectrons,wt2);
		h_NEMobj_elec1_closure->Fill(goodPho_.size(),wt2);
		//h_minDr_bestphoEle_elec1_closure->Fill(minDRindx,wt2);
		h_minDr_bestphoEle_elec1_closure->Fill(MinDr(bestEMObj,remJets),wt2);
		h_minDr_bestphoJets_elec1_closure->Fill(MinDr(bestEMObj,hadJets),wt2);
		//qmulti
	        h_CM_elec1_closure->Fill(qmulti,wt2);
           
		h_EMObj_pT_elec1_closure->Fill(bestEMObj.Pt(),wt2);
		h3_PhoPtnJetsbtags_elec1_closure->Fill(bestEMObj.Pt(),nHadJets,BTags,wt2);
		h3_PhoPtnJetsQmult_elec1_closure->Fill(bestEMObj.Pt(),nHadJets,qmulti,wt2);
		h2_PhoPtQMultJet_elec1_closure->Fill(bestEMObj.Pt(),qmulti,wt2);
		h2_PhoPtQMultJet_v2_elec1_closure->Fill(bestEMObj.Pt(),qmulti,wt2);
		h2_nJetsQMultJet_elec1_closure->Fill(nHadJets,qmulti,wt2);
		//cout<<nHadJets<<" : "<<BTags<<" : "<<qmulti<<" : "<<wt2<<endl;
		h2_PhoPtnJets_elec1_closure->Fill(bestEMObj.Pt(),nHadJets,wt2);
		h2_PhoPtQMultJet_v3_elec1_closure->Fill(bestEMObj.Pt(),qmulti,wt2);
		h2_METQMultJet_elec1_closure->Fill(MET,qmulti,wt2);
		h2_PhoPtMET_elec1_closure->Fill(bestEMObj.Pt(),MET,wt2);
		h2_nJetsMET_elec1_closure->Fill(nHadJets,MET,wt2);
		h_nvtx_elec1_closure->Fill(NVtx,wt2);

		h2_MET_dPhiMETj_elec1_closure->Fill(MET,mindphi,wt2);
		h2_MET_dPhiMETj1_elec1_closure->Fill(MET,dPhi_METjet1,wt2);
		h2_MET_dPhiMETj2_elec1_closure->Fill(MET,dPhi_METjet2,wt2);

 		h2_BestPhotonPt_jetmatchphoratio_elec1_closure->Fill(bestEMObj.Pt(),(*Jets)[photonMatchingJetIndx].Pt()/bestEMObj.Pt(),wt2);
		for(int j=0; j<hadJets.size();j++){
		  h_JetPt_elec1_closure->Fill(hadJets[j].Pt(),wt2);
		  h_JetEta_elec1_closure->Fill(hadJets[j].Eta(),wt2);
		  h_JetPhi_elec1_closure->Fill(hadJets[j].Phi(),wt2);
		}

	    if(hadJets.size()>0)
	      {
		h_JetPt1_elec1_closure->Fill(hadJets[0].Pt(),wt2);
		h_JetEta1_elec1_closure->Fill(hadJets[0].Eta(),wt2);
		h_JetPhi1_elec1_closure->Fill(hadJets[0].Phi(),wt2);
		h2_JetEta_Phi1_elec1_closure->Fill(hadJets[0].Eta(),hadJets[0].Phi(),wt2);
		h2_JetEta_Pt1_elec1_closure->Fill(hadJets[0].Eta(),hadJets[0].Pt(),wt2);          
	      }
	    if(hadJets.size()>1)
	      {
		h_JetPt2_elec1_closure->Fill(hadJets[1].Pt(),wt2);
		h_JetEta2_elec1_closure->Fill(hadJets[1].Eta(),wt2);
		h_JetPhi2_elec1_closure->Fill(hadJets[1].Phi(),wt2);
		h2_JetEta_Phi2_elec1_closure->Fill(hadJets[1].Eta(),hadJets[1].Phi(),wt2);
		h2_JetEta_Pt2_elec1_closure->Fill(hadJets[1].Eta(),hadJets[1].Pt(),wt2);          
	      }
	    if(hadJets.size()>2)
	      {
		h_JetPt3_elec1_closure->Fill(hadJets[2].Pt(),wt2);
		h_JetEta3_elec1_closure->Fill(hadJets[2].Eta(),wt2);
		h_JetPhi3_elec1_closure->Fill(hadJets[2].Phi(),wt2);
		h2_JetEta_Phi3_elec1_closure->Fill(hadJets[2].Eta(),hadJets[2].Phi(),wt2);
		h2_JetEta_Pt3_elec1_closure->Fill(hadJets[2].Eta(),hadJets[2].Pt(),wt2);          
	      }
	    if(hadJets.size()>3)
	      {
		h_JetPt4_elec1_closure->Fill(hadJets[3].Pt(),wt2);
		h_JetEta4_elec1_closure->Fill(hadJets[3].Eta(),wt2);
		h_JetPhi4_elec1_closure->Fill(hadJets[3].Phi(),wt2);
		h2_JetEta_Phi4_elec1_closure->Fill(hadJets[3].Eta(),hadJets[3].Phi(),wt2);
		h2_JetEta_Pt4_elec1_closure->Fill(hadJets[3].Eta(),hadJets[3].Pt(),wt2);          
	      }

		h_dPhi_phoMET_elec1_closure->Fill(dPhi_phoMET,wt2);
		h_BestPhotonPhi_elec1_closure->Fill((bestEMObj.Phi()),wt2);
		h_BestPhotonEta_elec1_closure->Fill((bestEMObj.Eta()),wt2);
		h2_nbjets_nJets_elec1_closure->Fill(hadJets.size(),BTags,wt2);
		h2_BestPhotonEta_Qmulti_elec1_closure->Fill(bestEMObj.Eta(),qmulti,wt2);
		h2_BestPhotonEta_nJets_elec1_closure->Fill(bestEMObj.Eta(),nHadJets,wt2);
		h2_BestPhotonEta_MET_elec1_closure->Fill(bestEMObj.Eta(),MET,wt2);		

		h2_leadElectronEta_Phi_elec1_closure->Fill(bestEMObj.Eta(),bestEMObj.Phi(),wt2);
		h2_leadElectronPt_Eta_elec1_closure->Fill(bestEMObj.Pt(),bestEMObj.Eta(),wt2);
	      }
	  }
	else if(!bestEMObjIsEle)
	  {
	    npho++;
	    h_selectBaselineYields_->Fill("SR : Electrons = 0",wt);

	    int sBin6 = getBinNoV7(bestEMObj,qmulti,minDRindx);
	    if(sBin6 != -999)
	      h_SBins_v6_CD_elec0->Fill(sBin6,wt);
	    int sBin7_SP_elec0 = getBinNoV7_le2(EWselec,EWselec1 ,EWselec_Htag,EWselec_Wtag,nHadJets);
	    h_SBins_v7_CD_SP_elec0->Fill(sBin7_SP_elec0,wt);
	    int sBin6_SP_elec0 = getBinNoV6(bestEMObj,nHadJets);
	    h_SBins_v6_CD_SP_elec0->Fill(sBin6_SP_elec0,wt);
	    int sBin6_50bin= getBinNoV6_EWplusSP_CR(EWselec,EWselec1 ,EWselec_Htag,EWselec_Wtag,nbjets,nHadJets);
	    h_SBins_v6_CD_EW_50bin_elec0->Fill(sBin6_50bin,wt);
               
	    h_MET_elec0->Fill(MET,wt);
	    h_METvBin2_elec0->Fill(MET,wt);
	    h_nJets_elec0->Fill(nHadJets,wt);
	    h_ST_elec0->Fill(ST,wt);
	    //	    h_BestPhotonPt_elec0->Fill()
	    h_BTags_elec0->Fill(nbjets,wt);
	    h_DBTags_elec0->Fill(abs(nbjets-BTags),wt);

	    //	    if(goodPho_.size() < 2)
	    h_NEMobj_elec0->Fill(goodPho_.size(),wt);
	    //	    h_minDr_bestphoEle_elec0->Fill(MinDr2(hadJets,bestEMObj),wt);
	    h_minDr_bestphoEle_elec0->Fill(MinDr(bestEMObj,remJets),wt);
	    h_minDr_bestphoJets_elec0->Fill(MinDr(bestEMObj,hadJets),wt);		
	    
	    h_CM_Pho->Fill(qmulti,wt);
	    h_EMObj_pT_elec0->Fill(bestEMObj.Pt(),wt);
	    h2_PhoPtQMultJet_elec0->Fill(bestEMObj.Pt(),qmulti,wt);
	    h2_PhoPtQMultJet_v2_elec0->Fill(bestEMObj.Pt(),qmulti,wt);
	    h3_PhoPtnJetsbtags_elec0->Fill(bestEMObj.Pt(),nHadJets,BTags,wt);
	    h3_PhoPtnJetsQmult_elec0->Fill(bestEMObj.Pt(),nHadJets,qmulti,wt);
	    h2_nJetsQMultJet_elec0->Fill(nHadJets,qmulti,wt);
	    h2_PhoPtnJets_elec0->Fill(bestEMObj.Pt(),nHadJets,wt);
	    h2_PhoPtQMultJet_v3_elec0->Fill(bestEMObj.Pt(),qmulti,wt);
	    h2_METQMultJet_elec0->Fill(MET,qmulti,wt);
	    h2_PhoPtMET_elec0->Fill(bestEMObj.Pt(),MET,wt);
	    h2_nJetsMET_elec0->Fill(nHadJets,MET,wt);
	    h_nvtx_elec0->Fill(NVtx,wt);
	    h2_BestPhotonPt_jetmatchphoratio_elec0->Fill(bestEMObj.Pt(),(*Jets)[photonMatchingJetIndx].Pt()/bestEMObj.Pt(),wt);
	    for(int j=0; j<hadJets.size();j++){
	      h_JetPt_elec0->Fill(hadJets[j].Pt(),wt);
	      h_JetEta_elec0->Fill(hadJets[j].Eta(),wt);
	      h_JetPhi_elec0->Fill(hadJets[j].Phi(),wt);
	    }
	    if(hadJets.size()>0)
	      {
		h_JetPt1_elec0->Fill(hadJets[0].Pt(),wt);
		h_JetEta1_elec0->Fill(hadJets[0].Eta(),wt);
		h_JetPhi1_elec0->Fill(hadJets[0].Phi(),wt);
		h2_JetEta_Phi1_elec0->Fill(hadJets[0].Eta(),hadJets[0].Phi(),wt);
		h2_JetEta_Pt1_elec0->Fill(hadJets[0].Eta(),hadJets[0].Pt(),wt);          
	      }
	    if(hadJets.size()>1)
	      {
		h_JetPt2_elec0->Fill(hadJets[1].Pt(),wt);
		h_JetEta2_elec0->Fill(hadJets[1].Eta(),wt);
		h_JetPhi2_elec0->Fill(hadJets[1].Phi(),wt);
		h2_JetEta_Phi2_elec0->Fill(hadJets[1].Eta(),hadJets[1].Phi(),wt);
		h2_JetEta_Pt2_elec0->Fill(hadJets[1].Eta(),hadJets[1].Pt(),wt);          
	      }
	    if(hadJets.size()>2)
	      {
		h_JetPt3_elec0->Fill(hadJets[2].Pt(),wt);
		h_JetEta3_elec0->Fill(hadJets[2].Eta(),wt);
		h_JetPhi3_elec0->Fill(hadJets[2].Phi(),wt);
		h2_JetEta_Phi3_elec0->Fill(hadJets[2].Eta(),hadJets[2].Phi(),wt);
		h2_JetEta_Pt3_elec0->Fill(hadJets[2].Eta(),hadJets[2].Pt(),wt);          
	      }
	    if(hadJets.size()>3)
	      {
		h_JetPt4_elec0->Fill(hadJets[3].Pt(),wt);
		h_JetEta4_elec0->Fill(hadJets[3].Eta(),wt);
		h_JetPhi4_elec0->Fill(hadJets[3].Phi(),wt);
		h2_JetEta_Phi4_elec0->Fill(hadJets[3].Eta(),hadJets[3].Phi(),wt);
		h2_JetEta_Pt4_elec0->Fill(hadJets[3].Eta(),hadJets[3].Pt(),wt);          
	      }

	    h_dPhi_phoMET_elec0->Fill(dPhi_phoMET,wt);
	    h_BestPhotonPhi_elec0->Fill((bestEMObj.Phi()),wt);
	    h_BestPhotonEta_elec0->Fill((bestEMObj.Eta()),wt);
	    h2_nbjets_nJets_elec0->Fill(hadJets.size(),BTags,wt);
	    h2_leadElectronEta_Phi_elec0->Fill(bestEMObj.Eta(),bestEMObj.Phi(),wt);
	    h2_leadElectronPt_Eta_elec0->Fill(bestEMObj.Pt(),bestEMObj.Eta(),wt);
	    h2_leadElectronPt_Phi_elec0->Fill(bestEMObj.Pt(),bestEMObj.Phi(),wt);
	    h2_QMultlleadJetPt_elec0->Fill(leadjet_Pt,leadjet_qmulti,wt);
	    h2_QMultlleadbJet_elec0->Fill(leadjet_qmulti,leadbjet_tag,wt);
	    h2_BestPhotonEta_Qmulti_elec0->Fill(bestEMObj.Eta(),qmulti,wt);
	    h2_BestPhotonEta_nJets_elec0->Fill(bestEMObj.Eta(),nHadJets,wt);
	    h2_BestPhotonEta_MET_elec0->Fill(bestEMObj.Eta(),MET,wt);

	    h_MET_CaloMET_elec0->Fill(MET/CaloMET,wt);
	    h_dPhi_MET_CaloMET_elec0->Fill(abs(DeltaPhi(METPhi,CaloMETPhi)),wt);
	    h_HT5HT_elec0->Fill(HT5/HT,wt);
	    h_dPhi_METjet1_elec0->Fill(dphi1,wt);
	    h_dPhi_METjet2_elec0->Fill(dphi2,wt);
	    h_dPhi_METjet3_elec0->Fill(dphi3,wt);
	    h_dPhi_METjet4_elec0->Fill(dphi4,wt);

	    // if(v_btag.size()>0)
	    //   {
	    // 	TLorentzVector btag1=v_btag[0];
	    // 	h_dR_bandjets->Fill(bestEMObj.DeltaR(btag1),wt);
	    // 	h2_QMultlleadbJet_v2->Fill(qmulti,bestEMObj.DeltaR(btag1),wt);
	    //   }
	    // if(v_btag.size()>1)
	    //   {
	    // 	TLorentzVector btag1=v_btag[1];
	    // 	h_dR_bandjets->Fill(bestEMObj.DeltaR(btag1),wt);
	    // 	h2_QMultlleadbJet_v2->Fill(qmulti,bestEMObj.DeltaR(btag1),wt);
	    //   }

	    // h2_QMultlleadbJet_v2_elec0->Fill(qmulti,bestEMObj.DeltaR(v_btag),wt);
	  }
	else
	  {
	    remain++;
	  }
      }
  }
  cout<<"Cross-section : "<<CrossSection<<endl;
  cout<<"Weight ib pb-1 : "<<Weight<<endl;

  cout<<"globalSuperTightHalo2016Filter : "<<a<<endl;
  cout<<"HBHENoiseFilter : "<<b<<endl;
  cout<<"HBHEIsoNoiseFilter : "<<c<<endl;
  cout<<"EcalDeadCellTriggerPrimitiveFilter : "<<d<<endl;
  cout<<"ecalBadCalibReducedFilter : "<<e<<endl;
  cout<<"BadPFMuonFilter : "<<f<<endl;
  cout<<"PrimaryVertexFilter : "<<g<<endl;
  cout<<"NVtx>0 : "<<h<<endl;
  
  cout<<"Events Survived before genphomatch : "<<genphomatch_before<<endl;
  cout<<"Events Survived after genphomatch : "<<genphomatch_after<<endl;
  //  cout<<"Events having NElectrons=1 : "<<ele<<endl;
  //  cout<<"Events passing reco electron pass id : "<<lep2<<endl;                                                                                                                                                  
  cout<<"Events passing reco electron pass id & iso : "<<lep<<endl;

  cout<<"pass realphoton --> "<<pass_realphoton<<endl;
  cout<<"fail realphoton --> "<<fail_realphoton<<endl;
  cout<<"CR Events passing mt cut : "<<elec_reco<<endl;
  
  cout<<"Events Survived after PreSelection : "<<evtSurvived_preselec<<endl;
  cout<<"Events having Jet matched to photon : "<<Jete<<endl;
  cout<<" Events with 0 e & 1 photon : "<<npho<<endl;
  cout<<" Events with 1 e & 0 photon : "<<nele<<endl;
  cout<<" Events with 0 e & 1 photon and having pixel id  : "<<nele_px<<endl;
  // cout<<" Events with 0 e & 0 photon : "<<nele_pho_0<<endl;
  cout<<"remaining : "<<remain<<endl;
  
  cout<<"================="<<endl;

 
}
TLorentzVector Fakerate::getBestPhoton(){
  vector<TLorentzVector> goodPho;
  vector<int> goodPhoIndx;
  for(int iPho=0;iPho<Photons->size();iPho++){
    if( (*Photons_fullID)[iPho] ) 
      {
      goodPho.push_back( (*Photons)[iPho] );
      goodPhoIndx.push_back(iPho);
    }
  }

  int highPtIndx=-100;
  for(int i=0;i<goodPho.size();i++){
    if(i==0) highPtIndx=0;
    else if( (goodPho[highPtIndx].Pt()) < (goodPho[i].Pt()) ){highPtIndx=i;}
  }

  if(highPtIndx>=0){
   bestPhotonIndxAmongPhotons = goodPhoIndx[highPtIndx];
  }
  else bestPhotonIndxAmongPhotons = -100;

  if(highPtIndx==-100){TLorentzVector v0;return v0;}
  else return goodPho[highPtIndx];
}
TLorentzVector Fakerate::getPhoton_withoutfullID(){
  vector<TLorentzVector> nogoodPho;
  vector<int> nogoodPhoIndx;
  for(int iPho=0;iPho<Photons->size();iPho++){
    if( !(*Photons_fullID)[iPho] ) 
      {
      nogoodPho.push_back( (*Photons)[iPho] );
      nogoodPhoIndx.push_back(iPho);
    }
  }

  int highPtIndx=-100;
  for(int i=0;i<nogoodPho.size();i++){
    if(i==0) highPtIndx=0;
    else if( (nogoodPho[highPtIndx].Pt()) < (nogoodPho[i].Pt()) ){highPtIndx=i;}
  }

  if(highPtIndx>=0){
    eIndxAmongPhotons = nogoodPhoIndx[highPtIndx];
  }
  else eIndxAmongPhotons = -100;

  if(highPtIndx==-100){TLorentzVector v0;return v0;}
  else return nogoodPho[highPtIndx];
}

int Fakerate::getBinNoV7(TLorentzVector bestEMObj,double qmulti, double minDRindx){
  int sBin=0,m_i=-1,sBin1=0,n_i=-1;; 
  for(int i=0;i<BestPhotonPtBinLowEdge.size()-1;i++){
    if(BestPhotonPtBinLowEdge[i]<99.99) continue; 
    //if(qmulti>=10) continue;
    m_i++;  
    if(bestEMObj.Pt() >= BestPhotonPtBinLowEdge[i] && bestEMObj.Pt() < BestPhotonPtBinLowEdge[i+1])
      {
	sBin = sBin+(m_i*4);

	break;

     }
    else if(bestEMObj.Pt() >= BestPhotonPtBinLowEdge[BestPhotonPtBinLowEdge.size()-1])
      {
	sBin = 40;
	break;
      }
  }

  if(sBin%4==0)// || sBin==4 || sBin==8 || sBin==12 || sBin==16 || sBin==20 )
    {
      //	cout<<"bestEMObj : "<<bestEMObj.Pt()<<" , Qmult : "<<qmulti<<" , sBin = "<<sBin1<<endl;

      for(int i=0;i<QMultLowedge.size()-1;i++){
	n_i++;
	if(qmulti>=QMultLowedge[i] && qmulti<QMultLowedge[i+1]) {sBin1=sBin+n_i; break;}
	else if(qmulti>=QMultLowedge[QMultLowedge.size()-1]){sBin1=sBin1+(QMultLowedge.size()-1); break;}
	//	else sBin1=-999;
      }
    }
  
  //   if((qmulti>=7 && qmulti<10) && bestEMObj.Pt()>=100 && bestEMObj.Pt() <120)
  // if(bestEMObj.Pt()>=200 && bestEMObj.Pt() <230)
  //   cout<<"bestEMObj : "<<bestEMObj.Pt()<<" , Qmult : "<<qmulti<<" , sBin = "<<sBin1<<endl;
  return sBin1;  
}


int Fakerate::getBinNoV6(TLorentzVector bestEMObj, int nHadJets){
  int sBin=0,m_i=-1,sBin1=0,n_i=-1;; 
  for(int i=0;i<BestPhotonPtBinLowEdge.size()-1;i++){
    if(BestPhotonPtBinLowEdge[i]<99.99) continue; 
    m_i++;  
    if(bestEMObj.Pt() >= BestPhotonPtBinLowEdge[i] && bestEMObj.Pt() < BestPhotonPtBinLowEdge[i+1])
      {
	sBin = sBin+(m_i*4);

	break;

     }
    else if(bestEMObj.Pt() >= BestPhotonPtBinLowEdge[BestPhotonPtBinLowEdge.size()-1])
      {
	sBin = 40;
	break;
      }
  }

  if(sBin%4==0)// || sBin==4 || sBin==8 || sBin==12 || sBin==16 || sBin==20 )
    {
      for(int i=0;i<nJetsLowedge.size()-1;i++){
	n_i++;
	if(nHadJets>=nJetsLowedge[i] && nHadJets<nJetsLowedge[i+1]) {sBin1=sBin+n_i; break;}
	else if(nHadJets>=nJetsLowedge[nJetsLowedge.size()-1]){sBin1=sBin1+(nJetsLowedge.size()-1); break;}
	//	else sBin1=-999;
      }
    }
  
  //   if((nHadJets>=7 && nHadJets<10) && bestEMObj.Pt()>=100 && bestEMObj.Pt() <120)
  // if(bestEMObj.Pt()>=200 && bestEMObj.Pt() <230)
  //   cout<<"bestEMObj : "<<bestEMObj.Pt()<<" , Qmult : "<<nHadJets<<" , sBin = "<<sBin1<<endl;
  return sBin1;  
}

int Fakerate::getBinNoV7_le(int nHadJets){
  int sBin=-100,m_i=0;
  if(BTags==0){
    if(nHadJets==2)     { sBin=1;}
    else if(nHadJets==3)     { sBin=2;}
    else if(nHadJets==4)     { sBin=3;}
    else if((nHadJets==5 || nHadJets==6)){ sBin=4;}
    else if(nHadJets>=7)   { sBin=5;}
  }
  else{
    if(nHadJets>=2 && nHadJets<=4)      { sBin=6;}
    else if((nHadJets==5 || nHadJets==6)){ sBin=7;}
    else if(nHadJets>=7)   { sBin=8;}
  }
  return sBin;
}

int Fakerate::getBinNoV7_le2(bool EWselec, bool EWselec1, bool EWselec_Htag , bool EWselec_Wtag,int nHadJets){
  int sBin=-100,m_i=0;
  if(!(EWselec && EWselec1))
    {
      if(BTags==0){
        if(nHadJets==2)     { sBin=1;}
        else if(nHadJets==3)     { sBin=2;}
        else if(nHadJets==4)     { sBin=3;}
        else if((nHadJets==5 || nHadJets==6)){ sBin=4;}
        else if(nHadJets>=7)   { sBin=5;}
      }
      else{
        if(nHadJets>=2 && nHadJets<=4)      { sBin=6;}
        else if((nHadJets==5 || nHadJets==6)){ sBin=7;}
        else if(nHadJets>=7)   { sBin=8;}
      }
    }
  else if ((EWselec && EWselec1))
    {
      if(EWselec_Wtag)
	sBin=9;
      if(EWselec_Htag)
	sBin=10;
    }
  
  return sBin;
}




int Fakerate::getBinNoV6_EWplusSP_CR(bool EWselec, bool EWselec1, bool EWselec_Htag , bool EWselec_Wtag,int nbjets, int nHadJets){

  int sBin=-100,m_i=0;

  //  if(!((EWselec_Wtag || EWselec_Htag) && EWselec1))
   if(!(EWselec && EWselec1))
    { 
      if(nbjets==0 ){
	if(nHadJets>=2 && nHadJets<=4)     { sBin=0;}
	else if(nHadJets==5 || nHadJets==6){ sBin=7;}
	else if(nHadJets>=7)               { sBin=13;}
      }
      else{
	if(nHadJets>=2 && nHadJets<=4)     { sBin=18;}
	else if(nHadJets==5 || nHadJets==6){ sBin=23;}
	else if(nHadJets>=7)               { sBin=28;}
      }
    }
   if((EWselec_Wtag && !EWselec_Htag) && EWselec1){
    sBin=33;
   }
   else if((!EWselec_Wtag && EWselec_Htag) && EWselec1){
     sBin=39;
   }
  if(sBin==0){
    for(int i=0;i<METLowEdge_v3.size()-1;i++){
      if(METLowEdge_v3[i]<199.99) continue;
      int sBin1=sBin;
      m_i++;
      if(MET >= METLowEdge_v3[i] && MET < METLowEdge_v3[i+1]){ sBin = sBin+m_i;
break; }
      else if(MET >= METLowEdge_v3[METLowEdge_v3.size()-1])  { sBin = 7         ;
	break; }
    }
  }
  else if(sBin==7 || sBin==33 || sBin==39){
    int sBin1=sBin;
    for(int i=0;i<METLowEdge_v3_1.size()-1;i++){
      if(METLowEdge_v3_1[i]<199.99) continue;
      m_i++;
      if(MET >= METLowEdge_v3_1[i] && MET < METLowEdge_v3_1[i+1]){ sBin = sBin+m_i; break;}
      else if(MET >= METLowEdge_v3_1[METLowEdge_v3_1.size()-1])  { sBin = sBin+6;   break; }
    }
  }

  else{
    for(int i=0;i<METLowEdge_v3_2.size()-1;i++){
      if(METLowEdge_v3_2[i]<199.99) continue;
      m_i++;
      if(MET >= METLowEdge_v3_2[i] && MET < METLowEdge_v3_2[i+1]){ sBin = sBin+m_i;break; }
      else if(MET >= METLowEdge_v3_2[METLowEdge_v3_2.size()-1])  { sBin = sBin+5;  break; }
      // else if(MET >= METLowEdge_v3[METLowEdge_v3.size()-1])  { sBin = 44   ;break; }

   }
  }
  return sBin;
}




// bool Fakerate::check_eMatchedtoGamma(){
//   for(int i=0;i<Electrons->size();i++){
//     for(int j=0;j<Photons->size();j++){
//       if( (DeltaR( (*Electrons)[i].Eta(),(*Electrons)[i].Phi(),(*Photons)[j].Eta(),(*Photons)[j].Phi()) ) < 0.01){
// 	//cout<<(*Electrons)[i].Pt()<<" "<<(*Electrons)[i].Eta()<<" "<<(*Electrons)[i].Phi()<<" "<<(*Photons)[i].Pt()<<" "<<(*Photons)[i].Eta()<<" "<<(*Photons)[i].Phi()<<endl;
// 	//print(0);
// 	return true;
//       }
//     }
//   }
//   return false;
// }

bool Fakerate::check_eMatchedtoGamma(TLorentzVector bestPhoton){
  for(int i=0;i<Electrons->size();i++)
    { 
      if( bestPhoton.DeltaR((*Electrons)[i]) < 0.1)
	return true; 
    }
  return false;
}
  

double Fakerate::getGendRLepPho(){//MC only
  TLorentzVector genPho1,genLep1;
  int leadGenPhoIdx=-100;
  for(int i=0;i<GenParticles->size();i++){
    if((*GenParticles)[i].Pt()!=0){
      if((abs((*GenParticles_PdgId)[i])==22) && ((abs((*GenParticles_ParentId)[i])<=25) || ((*GenParticles_ParentId)[i]==2212) ) && (*GenParticles_Status)[i]==1 ){
	if(genPho1.Pt() < (*GenParticles)[i].Pt()){
	  leadGenPhoIdx = i;
	  genPho1 = ((*GenParticles)[i]);
	}
      }
      if( (abs((*GenParticles_PdgId)[i])==11 || abs((*GenParticles_PdgId)[i])==13 || abs((*GenParticles_PdgId)[i])==15 ) && (abs((*GenParticles_ParentId)[i])<=25) && (abs((*GenParticles_ParentId)[i])!=15) ){
	if(genLep1.Pt() < ((*GenParticles)[i]).Pt()) genLep1 = ((*GenParticles)[i]);
      }
    }
  }//for
  if(genPho1.Pt() > 0. && genLep1.Pt() > 0.) return genLep1.DeltaR(genPho1);
  else return 1000.0;
}

double Fakerate::getGenLep(TLorentzVector bestPhoton){//MC only
  vector<TLorentzVector> v_genLep2;
  TLorentzVector genMu1, genEle1;  
  for(int i=0 ; i < GenElectrons->size(); i++)
    {
      if((*GenElectrons)[i].Pt()!=0)
	{
	  genEle1 = ((*GenElectrons)[i]);
	  v_genLep2.push_back(genEle1);
	}
	      
    }
  for(int i=0 ; i < GenMuons->size(); i++)
    {
      if((*GenMuons)[i].Pt()!=0)
	{
	  genMu1 = ((*GenMuons)[i]);
	  v_genLep2.push_back(genMu1);
	}
    }
  return MinDr(bestPhoton,v_genLep2);
  
}

void Fakerate::changeJets(int jec2Use, int jer2Use, int jet2Vary, bool varyMasswithJEC){
  if((jec2Use*jer2Use)!=0) return;
  if(jet2Vary!=4 && jet2Vary!=8 && jet2Vary!=48 && jet2Vary!=84) return;
  
  if(jet2Vary==4 || jet2Vary==48 || jet2Vary==84){
    TLorentzVector iJet;
    vector<TLorentzVector> jets;
    if(jec2Use==-1){ BTagsDeepCSV = BTagsDeepCSVJECdown; MET = (*METDown)[1]; METPhi = (*METPhiDown)[1]; JetID = JetIDJECdown; NJets = NJetsJECdown; HT = HTJECdown;}
    else if(jec2Use== 1){ BTagsDeepCSV = BTagsDeepCSVJECup; MET = (*METUp)[1]; METPhi = (*METPhiUp)[1]; JetID = JetIDJECup; NJets = NJetsJECup; HT = HTJECup;}
    else if(jer2Use==-1){ BTagsDeepCSV = BTagsDeepCSVJERdown; MET = (*METDown)[0]; METPhi = (*METPhiDown)[0]; JetID = JetIDJERdown; NJets = NJetsJERdown; HT = HTJERdown;}
    else if(jer2Use== 1){ BTagsDeepCSV = BTagsDeepCSVJERup; MET = (*METUp)[0]; METPhi = (*METPhiUp)[0]; JetID = JetIDJERup; NJets = NJetsJERup; HT = HTJERup;}
  
    //---- looking at https://github.com/kpedro88/Analysis/blob/da0bb3e24e04768d3c205b45cbd74b18e638133c/KCode/KSkimmerVariators.h#L409-L436
    const auto& JetsUnc_origIndex = (jec2Use== 1)?*JetsJECup_origIndex:(jec2Use==-1)?*JetsJECdown_origIndex:(jer2Use==1)?*JetsJERup_origIndex:(jer2Use==-1)?*JetsJERdown_origIndex:*Jets_origIndex; //last one is a dummy value
    const auto& JetsUnc_jerFactor = (jec2Use== 1)?*JetsJECup_jerFactor:(jec2Use==-1)?*JetsJECdown_jerFactor:*Jets_jerFactor; //last one is a dummy value
    const auto& Jets_unc = (jec2Use== 1)?*Jets_jecUnc:(jec2Use==-1)?*Jets_jecUnc:(jer2Use==1)?*Jets_jerFactorUp:(jer2Use==-1)?*Jets_jerFactorDown:*Jets_jecFactor; //last one is a dummy value
    
    vector<int> newIndex(Jets_origIndex->size(),-1);
    for(unsigned k = 0; k < Jets_origIndex->size(); ++k){
      //reverse the index vector
      newIndex[(*Jets_origIndex)[k]] = k;
    }
    for(unsigned j = 0; j < JetsUnc_origIndex.size(); ++j){
      //Jets[Unc]_origIndex is sorted in the final order after uncertainty variation is applied
      //go up to common ancestor, then down to central smeared collection
      int i = newIndex[JetsUnc_origIndex[j]];
      //undo central smearing, apply JEC unc, redo smearing w/ new smearing factor
      if(jec2Use== 1)       jets.push_back((*Jets)[i]*(1./(*Jets_jerFactor)[i])*(1+Jets_unc[i])*JetsUnc_jerFactor[j]);
      else if(jec2Use== -1) jets.push_back((*Jets)[i]*(1./(*Jets_jerFactor)[i])*(1-Jets_unc[i])*JetsUnc_jerFactor[j]);
      else if(jer2Use==  1) jets.push_back((*Jets)[i]*(1./(*Jets_jerFactor)[i])*Jets_unc[i]);
      else if(jer2Use== -1) jets.push_back((*Jets)[i]*(1./(*Jets_jerFactor)[i])*Jets_unc[i]);
      p_PtJECJERFac->Fill((*Jets)[i].Pt(),(1./(*Jets_jerFactor)[i])*(1+Jets_unc[i])*JetsUnc_jerFactor[j]);
      p_EtaJECJERFac->Fill((*Jets)[i].Eta(),(1./(*Jets_jerFactor)[i])*(1+Jets_unc[i])*JetsUnc_jerFactor[j]);
      p2_EtaPtJECJERFac->Fill((*Jets)[i].Eta(),(*Jets)[i].Pt(),(1./(*Jets_jerFactor)[i])*(1+Jets_unc[i])*JetsUnc_jerFactor[j]);
    }
    sortTLorVec(&jets);
    if(Jets->size()!=jets.size()){
      cout<<"oooooo.... Jets size:"<<Jets->size()<<" jets size:"<<jets.size()<<endl;
      return;
    }
    for(int i=0;i<jets.size();i++){
      //      if(EvtNum==207632 || EvtNum == 2055901){
      (*Jets)[i] = jets[i];
    }
  }//AK4 jets
  //---------------For AK8 jets
  if(jet2Vary==8 || jet2Vary==48 || jet2Vary==84){
    TLorentzVector iJet;
    vector<TLorentzVector> jets;
    const auto& JetsAK8Unc_origIndex = (jec2Use== 1)?*JetsAK8JECup_origIndex:(jec2Use==-1)?*JetsAK8JECdown_origIndex:(jer2Use==1)?*JetsAK8JERup_origIndex:(jer2Use==-1)?*JetsAK8JERdown_origIndex:*JetsAK8_origIndex; //last one is a dummy value
    const auto& JetsAK8Unc_jerFactor = (jec2Use== 1)?*JetsAK8JECup_jerFactor:(jec2Use==-1)?*JetsAK8JECdown_jerFactor:*JetsAK8_jerFactor; //last one is a dummy value
    const auto& JetsAK8_unc = (jec2Use== 1)?*JetsAK8_jecUnc:(jec2Use==-1)?*JetsAK8_jecUnc:(jer2Use==1)?*JetsAK8_jerFactorUp:(jer2Use==-1)?*JetsAK8_jerFactorDown:*JetsAK8_jecFactor; //last one is a dummy value
    
    // if(EvtNum==207632 || EvtNum == 2055901){
    vector<int> newIndexAK8(JetsAK8_origIndex->size(),-1);
    for(unsigned k = 0; k < JetsAK8_origIndex->size(); ++k){
      //reverse the index vector
      newIndexAK8[(*JetsAK8_origIndex)[k]] = k;
    }
    for(unsigned j = 0; j < JetsAK8Unc_origIndex.size(); ++j){
      //JetsAK8[Unc]_origIndex is sorted in the final order after uncertainty variation is applied
      //go up to common ancestor, then down to central smeared collection
      int i = newIndexAK8[JetsAK8Unc_origIndex[j]];
      //undo central smearing, apply JEC unc, redo smearing w/ new smearing factor
      if(jec2Use== 1)       jets.push_back((*JetsAK8)[i]*(1./(*JetsAK8_jerFactor)[i])*(1+JetsAK8_unc[i])*JetsAK8Unc_jerFactor[j]);
      else if(jec2Use== -1) jets.push_back((*JetsAK8)[i]*(1./(*JetsAK8_jerFactor)[i])*(1-JetsAK8_unc[i])*JetsAK8Unc_jerFactor[j]);
      else if(jer2Use==  1) jets.push_back((*JetsAK8)[i]*(1./(*JetsAK8_jerFactor)[i])*JetsAK8_unc[i]);
      else if(jer2Use== -1) jets.push_back((*JetsAK8)[i]*(1./(*JetsAK8_jerFactor)[i])*JetsAK8_unc[i]);
    }
    sortTLorVec(&jets);
    if(JetsAK8->size()!=jets.size()){
      cout<<"oooooo.... JetsAK8 size:"<<JetsAK8->size()<<" jets AK8 size:"<<jets.size()<<endl;
      return;
    }
    //get corrections for AK8 mass using Pt corrections applied.
    vector<double> ak8SDmass;
    for(int j=0;j<jets.size();j++){
      double mindr = 1000.;
      int mindrIdx = -1;
      for(int J=0;J<JetsAK8->size();J++){
	if(jets[j].DeltaR((*JetsAK8)[J]) < mindr){
	  mindr = jets[j].DeltaR((*JetsAK8)[J]);
	  mindrIdx = J;
	}
      }
      ak8SDmass.push_back(((*JetsAK8_softDropMass)[mindrIdx]) * (jets[j].Pt() / (*JetsAK8)[mindrIdx].Pt()));
    }
    for(int i=0;i<jets.size();i++){
      (*JetsAK8)[i] = jets[i];
      float minDR_boson = 9999.;
      int pdgBoson = 0, bosonIdx = -1;
      for(int j=0;j<GenParticles->size();j++){
	if((abs((*GenParticles_PdgId)[j]) < 6) && (*GenParticles_ParentIdx)[j] >= 0 &&
	   (minDR_boson > (*JetsAK8)[i].DeltaR((*GenParticles)[(*GenParticles_ParentIdx)[j]])) ){
	  minDR_boson = (*JetsAK8)[i].DeltaR((*GenParticles)[(*GenParticles_ParentIdx)[j]]);
	  pdgBoson = abs((*GenParticles_PdgId)[(*GenParticles_ParentIdx)[j]]);
	  bosonIdx = (*GenParticles_ParentIdx)[j];
	}
      }
      if(minDR_boson < 0.8 && (pdgBoson==23 || pdgBoson==24 || pdgBoson==25)){
	//apply JMS & JMR
      }
      else if(varyMasswithJEC) (*JetsAK8_softDropMass)[i] = ak8SDmass[i];
    }
  }
  //---------------------------
}
