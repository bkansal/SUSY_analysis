#define Fakerate_cxx
#include "Fakerate.h"
#include <TH2.h>
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
TString Tf="sBin7_SP";
//TString Tf="nHadJets";
//TString Tf="MET";
//TString Tf="METvBin2";
bool full_Run2=false;
bool applyE_SF=false;
bool apply_METfilters=true;
bool apply_L1=true;
bool apply_HEMveto=true;
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

  TFile *pufile,*TF,*E_SF,*Egamma_SF;
  cout<<"Applying electron scale factors ? "<<applyE_SF<<endl;
  cout<<"Applying MET filters ? "<<apply_METfilters<<endl;
  if(s_data.Contains("v17_2016")){
    pufile = TFile::Open("PileupHistograms_2016_69mb_pm5.root","READ");
    cout<<"Applying L1 prefiring prob.? "<<apply_L1<<endl;
  }
  if(s_data.Contains("v17_2017")){
    pufile = TFile::Open("PileupHistograms_2017_69mb_pm5.root","READ");
    cout<<"Applying L1 prefiring prob.? "<<apply_L1<<endl;
  }
  if(s_data.Contains("v17_2018")){
    pufile = TFile::Open("PileupHistograms_2018_69mb_pm5.root","READ");
    cout<<"Applying HEM veto? "<<apply_HEMveto<<endl;
  }

  
  TH1* puhist;
  TH1D *tf,*tf_SP,*tf_SP_2,*tf_SP_3;
  TH2F *e_id, *e_iso, *e_SF;

  if(!full_Run2)
    {
      if(s_data.Contains("2017")){
	TF = TFile::Open("Run2017_TF_LE_v6_CD.root","READ");
	// E_SF= TFile::Open("samples/ElectronScaleFactors_Run2017.root","READ");
	// e_id=(TH2F*)E_SF->Get("Run2017_CutBasedVetoNoIso94XV2");
	// e_iso=(TH2F*)E_SF->Get("Run2017_Mini");

	// e_id->Multiply(e_iso);
       }
      if(s_data.Contains("2018")){
	TF = TFile::Open("Run2018_TF_LE_v6_CD.root","READ");
	// E_SF= TFile::Open("samples/ElectronScaleFactors_Run2018.root","READ");
	// e_id=(TH2F*)E_SF->Get("Run2018_CutBasedVetoNoIso94XV2");
	// e_iso=(TH2F*)E_SF->Get("Run2018_Mini");
	// e_id->Multiply(e_iso);
       }
      if(s_data.Contains("2016")){
	TF = TFile::Open("Run2016_TF_LE_v6_CD.root","READ");
 	// E_SF= TFile::Open("samples/ElectronScaleFactors_Run2016.root","READ");
	// Egamma_SF=TFile::Open("samples/2016_ElectronWPVeto_Fall17V2.root","READ");
	// e_id=(TH2F*)E_SF->Get("Run2016_CutBasedVetoNoIso94XV2");
	// e_iso=(TH2F*)E_SF->Get("Run2016_Mini");
	// e_SF=(TH2F*)Egamma_SF->Get("EGamma_SF2D");
	// e_id->Multiply(e_iso);
      }
    }
  else
    {
      if(s_data.Contains("2017")){
	TF = TFile::Open("Runfull_Run2_TF_LE_v6_CD.root","READ");
      }
      if(s_data.Contains("2018")){
	TF = TFile::Open("Runfull_Run2_TF_LE_v6_CD.root","READ");
      }
      if(s_data.Contains("2016")){
	TF = TFile::Open("Runfull_Run2_TF_LE_v6_CD.root","READ");
	// E_SF= TFile::Open("samples/ElectronScaleFactors_Run2016.root","READ");
	// e_id=(TH2F*)E_SF->Get("Run2016_CutBasedVetoNoIso94XV2");
	// e_iso=(TH2F*)E_SF->Get("Run2016_Mini");
	// e_id->Multiply(e_iso);
      }
    }
    
  // if(s_data.Contains("full")){
  //   TF = TFile::Open("Runfull_Run2_TF_LE_v6_CD.root","READ");
  // }
  
  if(Tf=="sBin6")
    tf = (TH1D*)TF->Get("tf");
  if(Tf=="sBin6_SP")
    tf_SP = (TH1D*)TF->Get("tf_SP");
  if(Tf=="sBin7_SP" || Tf=="nHadJets" || Tf=="BTags" || Tf=="MET" || Tf=="METvBin2")
    tf_SP_2 = (TH1D*)TF->Get("tf_SP_2");
  if(Tf=="sBin7_SP_tmp")
    tf_SP_3 = (TH1D*)TF->Get("tf_SP_3");

  
  if(s_data.Contains("v17"))
    {
      puhist = (TH1*)pufile->Get("pu_weights_down");
    }

  bool v17=true, v12=false;
  // bool v17=false, v12=true;
  bool EWselection=true;
  int elec_reco=0,elec_reco0_before=0,elec_reco1_before=0,muon_reco=0,elec_gen3=0,elec_gen2=0, elec_gen=0, muon_gen=0,elec_reco0=0,elec_reco1=0,evtSurvived_preselec=0,elec_reco2=0,elec2_reco=0,survived_vetohad=0,elec_reco1_CR=0,survived_elecge1=0,events_cr=0,events_sr=0,total=0,remain=0,elec_reco0_genel=0,efakepho=0,ele=0,genphomatch_after=0,genphomatch_before=0,elec_gen4=0,gentauhad2=0,lep2=0,lep=0,nele=0,npho=0,nele_pho=0,nele_pho_0=0;
  int fail_realphoton=0;
  int pass_realphoton=0;
  int fail_acceptance=0;
  int pass_acceptance=0;
  int fail_id=0;
  int pass_id=0;
  int fail_iso=0;
  int pass_iso=0;
  for (Long64_t jentry=0; jentry<nentries;jentry++) {
    //  for (Long64_t jentry=0; jentry<1000;jentry++) {
    int total_lost_el = 0,cr_el=0,sr_el,e_index=-1,nlep=0;

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

    if(s_data.Contains("2016")) lumiInfb=35.922;
    if(s_data.Contains("2017")) lumiInfb=41.529;
    if(s_data.Contains("2018")) lumiInfb=59.74;
    if(s_data.Contains("FastSim") && s_data.Contains("2016")) lumiInfb=137.19;
    if(s_data=="ZG_v17_2017") lumiInfb=77.49;


    ///////=======  L1 Prefiring issue ===========/////////
    if((s_data.Contains("v17_2016") || s_data.Contains("v17_2017") ) && apply_L1){
      //      cout<<jentry<<" : NonPrefiringProb ="<<NonPrefiringProb<<" , lumiInfb = "<<lumiInfb<<" , pile up = "<<puhist->GetBinContent(puhist->GetXaxis()->FindBin(min(TrueNumInteractions,puhist->GetBinLowEdge(puhist->GetNbinsX()+1))))<<endl;
      wt=Weight*1000.0*NonPrefiringProb*lumiInfb*(puhist->GetBinContent(puhist->GetXaxis()->FindBin(min(TrueNumInteractions,puhist->GetBinLowEdge(puhist->GetNbinsX()+1)))));
      h_nEvts->Fill(1,wt);
      }

    if(s_data.Contains("v17_2018") && apply_HEMveto){
      wt=Weight*1000.0*lumiInfb*(puhist->GetBinContent(puhist->GetXaxis()->FindBin(min(TrueNumInteractions,puhist->GetBinLowEdge(puhist->GetNbinsX()+1)))));
      h_nEvts->Fill(1,wt);
    }

    //////-======== HEM issue ==================//////////////
    if(s_data.Contains("2018")){
      for(int i=0; i<Electrons->size();i++)
        if((*Electrons)[i].Pt() >30 && (*Electrons)[i].Eta() > -3.0 && (*Electrons)[i].Eta() < -1.4 && (*Electrons)[i].Phi() > -1.57 && (*Electrons)[i].Phi() < -0.87) continue;
      for(int i=0; i<Jets->size();i++)
        if((*Jets)[i].Pt() > 30 && (*Jets)[i].Eta() > -3.2 && (*Jets)[i].Eta() < -1.2 && (*Jets)[i].Phi() > -1.77 && (*Jets)[i].Phi() < -0.67 && DeltaPhi((*Jets)[i].Pt(),MHTPhi)<0.5) continue;
    }

    
    if(s_data.Contains("data")){
      wt=1*0.9;
      h_nEvts->Fill(1,wt);
    }


    if(s_data.Contains("TTJets2"))
      {//cout<<" correct "<<endl;
   	if ( madHT>600) continue;
      }				    
    if(!s_data.Contains("FastSim") && apply_METfilters==true){

      if(s_data.Contains("data_2016"))
      	if(!(PrimaryVertexFilter==1 && globalSuperTightHalo2016Filter == 1 && HBHENoiseFilter==1 && HBHEIsoNoiseFilter==1 && EcalDeadCellTriggerPrimitiveFilter == 1 && BadPFMuonFilter  && eeBadScFilter==1 && NVtx>0)) continue;

      if(s_data.Contains("v17_2016"))
      	if(!(PrimaryVertexFilter==1 && globalSuperTightHalo2016Filter == 1 && HBHENoiseFilter==1 && HBHEIsoNoiseFilter==1 && EcalDeadCellTriggerPrimitiveFilter == 1 && BadPFMuonFilter && NVtx>0)) continue;
      
      if(s_data.Contains("data_2018") || s_data.Contains("data_2017"))
      	if(!(PrimaryVertexFilter==1 && globalSuperTightHalo2016Filter==1 && HBHENoiseFilter==1 && HBHEIsoNoiseFilter==1 && EcalDeadCellTriggerPrimitiveFilter == 1 && BadPFMuonFilter && ecalBadCalibReducedFilter && ecalBadCalibReducedExtraFilter && eeBadScFilter==1)) continue;

      if(s_data.Contains("v17_2018") || s_data.Contains("v17_2017"))
      	if(!(PrimaryVertexFilter==1 && globalSuperTightHalo2016Filter==1 && HBHENoiseFilter==1 && HBHEIsoNoiseFilter==1 && EcalDeadCellTriggerPrimitiveFilter == 1 && BadPFMuonFilter && ecalBadCalibReducedFilter && ecalBadCalibReducedExtraFilter)) continue;

      //      if(!(CSCTightHaloFilter==1 && HBHENoiseFilter==1 && HBHEIsoNoiseFilter==1 && eeBadScFilter==1 && EcalDeadCellTriggerPrimitiveFilter==1 && BadPFMuonFilter && NVtx > 0) ) continue;
    }
    if(PFCaloMETRatio >=  5) continue;

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
   int hasEle=0, hasPho=0;
   TLorentzVector bestPhoton=getBestPhoton();
   bool bestPhoHasPxlSeed=true;
   bool eMatchedG=check_eMatchedtoGamma(bestPhoton);
   ////////========== ISR weighting ////////////////.
 
   //     if((s_data.Contains("TTJets")||s_data.Contains("TTJets_v17")||s_data.Contains("TTJets2_v17"))){
   // 	 double isrWt = 0;
   // 	 vector<double> D_values={1.0697, 1.0150, 0.9917, 0.9435, 0.95};
   // 	 vector<double> isrwt_arr={1., 0.920, 0.821, 0.715, 0.662, 0.561, 0.511};
   // 	 if(NJetsISR>=6) isrWt = isrwt_arr[6];
   // 	 else isrWt = isrwt_arr[NJetsISR];
      
   // 	 if(madHT<600) isrWt = isrWt*D_values[0];
   // 	 else if(madHT < 800) isrWt = isrWt*D_values[1];
   // 	 else if(madHT < 1200) isrWt = isrWt*D_values[2];
   // 	 else if(madHT < 2500) isrWt = isrWt*D_values[3];
   // 	 else isrWt = isrWt*D_values[4];
   // 	 wt = wt*isrWt;
   //     }
   //   }

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

    //photon pt cut
    //  if(bestPhoton.Pt()>100)
    //   {
    // 	h_selectBaselineYields_->Fill("Good #gamma with Pt > 100",wt);

    //   }
    // else continue;

    
    // //veto Muon

    
    if (NMuons > 0) continue;
    else
      h_selectBaselineYields_->Fill("veto Muon",wt);                                                                           

    // //exactly 1 reco electron or 0 reco electron
    if (NElectrons > 1) continue;
    else
      h_selectBaselineYields_2->Fill("veto electron > 1",wt);     

    if(isoMuonTracks ==0 && isoPionTracks==0)
      {
	int a;
	h_selectBaselineYields_->Fill("Iso track",wt);
      }
    else continue;                                   
    
    
    //=============================================================
    //=============================================================
    //Fake rate/////////////
    //=============================================================
    //=============================================================
       
   if(bestPhotonIndxAmongPhotons>=0){
     if((*Photons_hasPixelSeed)[bestPhotonIndxAmongPhotons]<0.001) bestPhoHasPxlSeed=false;
     if(!eMatchedG && !bestPhoHasPxlSeed && bestPhoton.Pt()>100) hasPho=1;
     else
       hasPho=0;
   }

   double mt_ele=0,mt_pho=0,mt_ele1=0;
	
   TLorentzVector v_lep1,v_lep2;
   for(int i=0 ; i<Electrons->size() ; i++)
     {
       if(NElectrons==1 && (*Electrons_passIso)[i]==1)
	 {
	   {
	     nlep++;
	     e_index=i;
	     v_lep1=(*Electrons)[i];
	   }
	 }
     }
   if(nlep==1)  
     {
       mt_ele=sqrt(2*v_lep1.Pt()*MET*(1-cos(DeltaPhi(METPhi,v_lep1.Phi()))));
       if(mt_ele>100 ) continue;
       elec_reco++;	    
       if(v_lep1.Pt()>100)
	 {
	   hasEle=1;
	   lep++;	    
	 }
     }
     
   bool bestEMObjIsEle=0;
   TLorentzVector bestEMObj;
   if (hasEle==1 && hasPho==0) {bestEMObjIsEle=true;  bestEMObj = (*Electrons)[e_index];}
   else if(hasEle==0 &&  hasPho==1) {bestEMObjIsEle=false; bestEMObj = bestPhoton;}
   else 
     {
       // if(hasEle==1 &&  hasPho==1) nele_pho++;
       // else if(hasEle==0 &&  hasPho==0) nele_pho_0++;
       continue;
     }
   bool fakePhoton=false;

   int nGenEle1=0;
   TLorentzVector genEle1;
   vector<TLorentzVector> v_genEle2;
   for(int i=0 ; i < GenElectrons->size(); i++)
     {
       if((*GenElectrons)[i].Pt()!=0)
	 {
	   
	   nGenEle1++;
	   genEle1 = ((*GenElectrons)[i]);
	   v_genEle2.push_back(genEle1);
	 }
       
     }
   

   
   if(!bestEMObjIsEle)
     {
       if(!(*Photons_electronFakes)[bestPhotonIndxAmongPhotons])
	 { //h_mindr_lep_goodph->Fill(MinDr(bestPhoton,v_genEle2),wt);
	   //h_mindr_goodph_lep->Fill(MinDr((*Photons)[bestPhotonIndxAmongPhotons],v_genEle1),wt);                                                                                                             
	   pass_realphoton++;
	   fakePhoton=false;
	 }
       else
	 {
	   h_mindr_lep_goodph->Fill(MinDr(bestPhoton,v_genEle2),wt);
	   fail_realphoton++;
	   fakePhoton=true;
	 }
       if(!fakePhoton) continue;
       if(isoElectronTracks!=0 || isoMuonTracks!=0 || isoPionTracks!=0) continue;

     }
   // if(!bestEMObjIsEle)
   //   {
   //     double minDR_Pho_GenObj=1000;
   //     for(int i=0;i<GenParticles->size();i++){
   // 	 if((*GenParticles)[i].Pt()!=0){
   // 	   double dr1=bestPhoton.DeltaR((*GenParticles)[i]);
   // 	   if(dr1 < 0.2 && (abs((*GenParticles_PdgId)[i])==11) && (abs((*GenParticles_ParentId)[i])<=24) ){
   // 	     fakePhoton=true;
   // 	   }
   // 	   if(minDR_Pho_GenObj > dr1) minDR_Pho_GenObj=dr1;
   // 	 }
   //     }
	
   //     for(int i=0;i<GenParticles->size();i++){
   // 	 if((*GenParticles)[i].Pt()!=0){
   // 	   double dr1=bestPhoton.DeltaR((*GenParticles)[i]);
   // 	   if( dr1<0.2 && (abs((*GenParticles_PdgId)[i])==22) && 
   // 	       ( ((*GenParticles)[i].Pt()/bestPhoton.Pt()) > 0.9) && ((*GenParticles)[i].Pt()/bestPhoton.Pt()) < 1.1 )  fakePhoton=false;
   // 	 }
   //     }
   //     if(!fakePhoton) continue;
   //     if(isoElectronTracks!=0 || isoMuonTracks!=0 || isoPionTracks!=0) continue;
   //   }	
   //	cout<<jentry<<" : bestEMObjIsEle : "<<bestEMObjIsEle<<endl;     
      
    //=============================================================
    //=============================================================
      

    //========= hadjet -> removing jets which are matched with photon within mindr 0.3 =====//
    bool hadJetID=false;
 
    int minDRindx=-100,photonMatchingJetIndx=-100,nHadJets=0;
    double minDR=99999,ST=0,remJetPt=0;
    vector<TLorentzVector> hadJets;

    for(int i=0;i<Jets->size();i++){
      if( ((*Jets)[i].Pt() > 30.0) && (abs((*Jets)[i].Eta()) <= 2.4) )
	{
            {
	      double dR=bestEMObj.DeltaR((*Jets)[i]);
	      if(dR<minDR){minDR=dR;minDRindx=i;}
	    }
	}
    }

    for(int i=0;i<Jets->size();i++){
      if( ((*Jets)[i].Pt() > 30.0) && (abs((*Jets)[i].Eta()) <= 2.4) ){
        if( !(minDR < 0.3 && i==minDRindx) ){
	  hadJetID=(*Jets_ID)[i];
	  if(hadJetID)
	    hadJets.push_back((*Jets)[i]);	    
	}
      }
    }
    
    
    
    if( minDR<0.3 ) photonMatchingJetIndx=minDRindx;
    //now hadJets contains all jets except the one matched to emObject. check whether there is energy near emObj or not. If yes then add it as a jet.
    if( photonMatchingJetIndx>=0 ){
      if( ((*Jets)[photonMatchingJetIndx].Pt()) > 1.1*(bestEMObj.Pt()) ){
	if( (((*Jets)[photonMatchingJetIndx] - bestEMObj).Pt())>30){
	  hadJets.push_back( (*Jets)[photonMatchingJetIndx] - bestEMObj );
	  remJetPt=((*Jets)[photonMatchingJetIndx] - bestEMObj).Pt();
	}
      }
    }

    
    if(hadJets.size() == 0) continue;  
    for(int i=0;i<hadJets.size();i++)
      {
	if( (abs(hadJets[i].Eta()) < 2.4) ){ST=ST+(hadJets[i].Pt());}
	if( (abs(hadJets[i].Eta()) < 2.4) ){nHadJets++;}
      }
    
    if( minDR<0.3 ){
      ST=ST+bestEMObj.Pt();
    }
    sortTLorVec(&hadJets);

    
    //Minimum MET
    if( MET>100)  
      {
	h_selectBaselineYields_->Fill("MET>100",wt);
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
    dPhi_METjet1 = abs(DeltaPhi(METPhi,(hadJets)[0].Phi())); 
    dPhi_METjet2 = abs(DeltaPhi(METPhi,(hadJets)[1].Phi()));
    double mTPhoMET=sqrt(2*(bestEMObj.Pt())*MET*(1-cos(DeltaPhi(METPhi,bestEMObj.Phi()))));

    //Minimum dPhi cut between MET and leading two jets
    if(dPhi_METjet1 > 0.3 && dPhi_METjet2 > 0.3 )
      {
	h_selectBaselineYields_->Fill("dPhi1 & dPhi2 >= 0.3",wt);
      }
    else continue;
    

    // //============== New Trigger selections ================				     
    if( (ST <= 300) ) continue;

    // if( !((MET>200 && bestPhoton.Pt()>100) ) )continue;
    // else 
    // h_selectBaselineYields_->Fill("MET>250 & photon pt>100 selec",wt);
    bool process= false;
    //    if(!bestPhoHasPxlSeed && bestPhoton.Pt()>=100 && ST>300 && nHadJets>=2 && MET > 200 && dPhi_METjet1 > 0.3 && dPhi_METjet2 > 0.3 && NMuons==0 &&((isoMuonTracks==0)&&(isoPionTracks==0)))
    if(ST>300 && nHadJets>=2 && MET > 300 && dPhi_METjet1 > 0.3 && dPhi_METjet2 > 0.3 && NMuons==0 &&((isoMuonTracks==0)&&(isoPionTracks==0)))
      process =true;
    else continue;

     
    // //============== Old Trigger selections ================                                                                                  
    // if( (ST <= 500) ) continue;

    // if( !((ST>800 && bestPhoton.Pt()>100) || (bestPhoton.Pt()>190)) ) continue;
    // else    
    //  h_selectBaselineYields_->Fill("ST & photon pt selec",wt);
    // bool process= false;
    
    // //    if(!bestPhoHasPxlSeed && bestPhoton.Pt()>=100 && ST>500 && nHadJets>=2 && MET > 100 && dPhi_METjet1 > 0.3 && dPhi_METjet2 > 0.3 && NMuons==0 &&((isoMuonTracks==0)&&(isoPionTracks==0))){
    // if(bestPhoton.Pt()>=100 && ST>500 && nHadJets>=2 && MET > 100 && dPhi_METjet1 > 0.3 && dPhi_METjet2 > 0.3 && NMuons==0 &&((isoMuonTracks==0)&&(isoPionTracks==0))){
    //    process =true;
    //    evtSurvived++;      
    //    h_selectBaselineYields_->Fill("Before Pre-Selections",wt);
       
    // }
    // else continue;

    
     ///////////////-========after Baseline Selections ////////////
    
    //    evtSurvived_preselec++;     

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
	double dR4=bestPhoton.DeltaR((*JetsAK8)[i]);
	if(dR4<minDR4){minDR4=dR4;minDR4indx=i;}
      }
    
    for(int i=0;i<JetsAK8->size();i++)
      if( ((*JetsAK8)[i].Pt() > 200.0) && (abs((*JetsAK8)[i].Eta()) <= 2.4) ){
	if( !(minDR4 < 0.3 && i==minDR4indx) ){
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

	
      //   //================================================
    evtSurvived_preselec++;     

    //    getBinNoV7(bestEMObj,minDRindx);
    if(process && EWselection && hadJetID)
      {
	if (hasEle==1 && hasPho==0) nele++;
	else if(hasEle==0 &&  hasPho==1) npho++;
	
	  
	else  if(hasEle==1 &&  hasPho==1) nele_pho++;
	else if(hasEle==0 &&  hasPho==0) nele_pho_0++;
     
     

	if(bestEMObjIsEle)
	  {
	    h_selectBaselineYields_->Fill("CR : Electrons = 1",wt);
	    int sBin6 = getBinNoV7(bestEMObj,minDRindx);
	    h_SBins_v6_CD_elec1->Fill(sBin6,wt);
	    int sBin7_SP_elec1 = getBinNoV7_le2(EWselec,EWselec1 ,EWselec_Htag,EWselec_Wtag,nHadJets);
	    h_SBins_v7_CD_SP_elec1->Fill(sBin7_SP_elec1,wt);
	    int sBin6_SP_elec1 = getBinNoV6(EWselec,EWselec1 ,EWselec_Htag,EWselec_Wtag,nHadJets);
	    h_SBins_v6_CD_SP_elec1->Fill(sBin6_SP_elec1,wt);
	    int sBin6_50bin= getBinNoV6_EWplusSP_CR(EWselec,EWselec1 ,EWselec_Htag,EWselec_Wtag,nHadJets);
	    h_SBins_v6_CD_EW_50bin_elec1->Fill(sBin6_50bin,wt);

	    h_MET->Fill(MET,wt);
	    h_METPhi->Fill(METPhi,wt);
	    h_METvBin2->Fill(MET,wt);
	    h_nJets->Fill(nHadJets,wt);
	    h_ST->Fill(ST,wt);
	    h_BTags->Fill(BTags,wt);
	    h_minDr_bestphoEle->Fill(MinDr(bestPhoton,*Electrons),wt);
	    h_minDr_bestphoJets->Fill(MinDr(bestPhoton,hadJets),wt);
	    //(*Jets_chargedMultiplicity)[minDRindx]
	    h_CM_Ele->Fill((*Jets_chargedMultiplicity)[minDRindx],wt);
           
	    h_EMObj_pT->Fill(bestEMObj.Pt(),wt);
	  }
	else
	  {
	    h_selectBaselineYields_->Fill("SR : Electrons = 0",wt);
	    int sBin6 = getBinNoV7(bestEMObj,minDRindx);
	    h_SBins_v6_CD_elec0->Fill(sBin6,wt);
	    int sBin7_SP_elec0 = getBinNoV7_le2(EWselec,EWselec1 ,EWselec_Htag,EWselec_Wtag,nHadJets);
	    h_SBins_v7_CD_SP_elec0->Fill(sBin7_SP_elec0,wt);
	    int sBin6_SP_elec0 = getBinNoV6(EWselec,EWselec1 ,EWselec_Htag,EWselec_Wtag,nHadJets);
	    h_SBins_v6_CD_SP_elec0->Fill(sBin6_SP_elec0,wt);
	    int sBin6_50bin= getBinNoV6_EWplusSP_CR(EWselec,EWselec1 ,EWselec_Htag,EWselec_Wtag,nHadJets);
	    h_SBins_v6_CD_EW_50bin_elec0->Fill(sBin6_50bin,wt);
               
	    h_MET_elec0->Fill(MET,wt);
	    h_METvBin2_elec0->Fill(MET,wt);
	    h_nJets_elec0->Fill(nHadJets,wt);
	    h_ST_elec0->Fill(ST,wt);
	    h_BTags_elec0->Fill(BTags,wt);
	    h_minDr_bestphoEle_elec0->Fill(MinDr(bestPhoton,*Electrons),wt);
	    h_minDr_bestphoJets_elec0->Fill(MinDr(bestPhoton,hadJets),wt);		
	    h_CM_Pho->Fill((*Jets_chargedMultiplicity)[minDRindx],wt);
	    h_EMObj_pT_elec0->Fill(bestEMObj.Pt(),wt);

	  }
      }
  }
  cout<<"Cross-section : "<<CrossSection<<endl;
  cout<<"Weight ib pb-1 : "<<Weight<<endl;

  cout<<"Events Survived before genphomatch : "<<genphomatch_before<<endl;
  cout<<"Events Survived after genphomatch : "<<genphomatch_after<<endl;
  //  cout<<"Events having NElectrons=1 : "<<ele<<endl;
  //  cout<<"Events passing reco electron pass id : "<<lep2<<endl;                                                                                                                                                  
  cout<<"Events passing mt cut : "<<elec_reco<<endl;
  cout<<"Events passing reco electron pass id & iso : "<<lep<<endl;

  cout<<"pass realphoton --> "<<pass_realphoton<<endl;
  cout<<"fail realphoton --> "<<fail_realphoton<<endl;
  
  cout<<"Events Survived after PreSelection : "<<evtSurvived_preselec<<endl;

  cout<<" Events with 0 e & 1 photon : "<<npho<<endl;
  cout<<" Events with 1 e & 0 photon : "<<nele<<endl;
  cout<<" Events with 1 e & 1 photon : "<<nele_pho<<endl;
  cout<<" Events with 0 e & 0 photon : "<<nele_pho_0<<endl;

  
  cout<<"================="<<endl;

 
}
TLorentzVector Fakerate::getBestPhoton(){
  vector<TLorentzVector> goodPho;
  vector<int> goodPhoIndx;
  for(int iPho=0;iPho<Photons->size();iPho++){
    if( (*Photons_fullID)[iPho] ) {
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

int Fakerate::getBinNoV7(TLorentzVector bestEMObj, double minDRindx){
  int sBin=0,m_i=0,sBin1=0; 
  for(int i=0;i<BestPhotonPtBinLowEdge.size()-1;i++){
    if(BestPhotonPtBinLowEdge[i]<99.99) continue; 
    if(bestEMObj.Pt() >= BestPhotonPtBinLowEdge[i] && bestEMObj.Pt() < BestPhotonPtBinLowEdge[i+1])
      {
	sBin1 = sBin1+m_i;

	if((*Jets_chargedMultiplicity)[minDRindx]==0 || (*Jets_chargedMultiplicity)[minDRindx]==1) sBin=sBin1;
	else if((*Jets_chargedMultiplicity)[minDRindx]>=2 && (*Jets_chargedMultiplicity)[minDRindx]<4) sBin=sBin1+1;
	else if((*Jets_chargedMultiplicity)[minDRindx]>=4 && (*Jets_chargedMultiplicity)[minDRindx]<7) sBin=sBin1+2;
	else sBin=sBin1+3;

	break;


    }
    else if(bestEMObj.Pt() >= BestPhotonPtBinLowEdge[BestPhotonPtBinLowEdge.size()-1])
      {
	sBin1 = 44;
	if((*Jets_chargedMultiplicity)[minDRindx]==0 || (*Jets_chargedMultiplicity)[minDRindx]==1) sBin=sBin1;
	else if((*Jets_chargedMultiplicity)[minDRindx]>=2 && (*Jets_chargedMultiplicity)[minDRindx]<4) sBin=sBin1;
	else if((*Jets_chargedMultiplicity)[minDRindx]>=4 && (*Jets_chargedMultiplicity)[minDRindx]<7) sBin=sBin1;
	else sBin=sBin1+3;
	break;
      }
    m_i=m_i+4;  
  }

  //  for(int i=0;)
  //  cout<<"bestEMObj : "<<bestEMObj.Pt()<<" , Qmult : "<<(*Jets_chargedMultiplicity)[minDRindx]<<" , sBin = "<<sBin<<endl;
  return sBin;  
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

// int Fakerate::getBinNoV6(int nHadJets){
//   int sBin=-100,m_i=0;
//   if(BTags==0){
//     if(nHadJets>=2 && nHadJets<=4)     { sBin=0;}
//     else if(nHadJets==5 || nHadJets==6){ sBin=7;}
//     else if(nHadJets>=7)               { sBin=13;}
//   }
//   else{
//     if(nHadJets>=2 && nHadJets<=4)     { sBin=19;}
//     else if(nHadJets==5 || nHadJets==6){ sBin=25;}
//     else if(nHadJets>=7)               { sBin=31;}
//   }
//   if(sBin==0){
//     for(int i=0;i<METLowEdge_v2.size()-1;i++){
//       if(METLowEdge_v2[i]<249.99) continue;
//       m_i++;
//       if(MET >= METLowEdge_v2[i] && MET < METLowEdge_v2[i+1]){ sBin = sBin+m_i;break; }
//else if(MET >= METLowEdge_v2[METLowEdge_v2.size()-1])  { sBin = 7         ;break; }
//     }
//   }
//   else{
//     for(int i=0;i<METLowEdge_v2_1.size()-1;i++){
//       if(METLowEdge_v2_1[i]<249.99) continue;
//       m_i++;
//       if(MET >= METLowEdge_v2_1[i] && MET < METLowEdge_v2_1[i+1]){ sBin = sBin+m_i;break; }
//       else if(MET >= METLowEdge_v2_1[METLowEdge_v2_1.size()-1])  { sBin = sBin+6   ;break; }
//     }
//   }
//   return sBin;
// }

int Fakerate::getBinNoV6(bool EWselec, bool EWselec1, bool EWselec_Htag , bool EWselec_Wtag,int nHadJets){
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
      if(BTags==0){
        if(nHadJets>=2 && nHadJets<=4 )     { sBin=9;}
        else if((nHadJets==5 || nHadJets==6)){ sBin=10;}
      }
      else{
        if(nHadJets>=2 && nHadJets<=4)      { sBin=11;}
        else if((nHadJets==5 || nHadJets==6)){ sBin=12;}
      }

    }
  return sBin;
}




int Fakerate::getBinNoV6_EWplusSP_CR(bool EWselec, bool EWselec1, bool EWselec_Htag , bool EWselec_Wtag,int nHadJets){

  int sBin=-100,m_i=0;

  //  if(!((EWselec_Wtag || EWselec_Htag) && EWselec1))
   if(!(EWselec && EWselec1))
    { 
      if(BTags==0 ){
	if(nHadJets>=2 && nHadJets<=4)     { sBin=0;}
	else if(nHadJets==5 || nHadJets==6){ sBin=7;}
	else if(nHadJets>=7)               { sBin=13;}
      }
      else{
	if(nHadJets>=2 && nHadJets<=4)     { sBin=19;}
	else if(nHadJets==5 || nHadJets==6){ sBin=25;}
	else if(nHadJets>=7)               { sBin=31;}
      }
    }
   if((EWselec_Wtag && !EWselec_Htag) && EWselec1){
    sBin=37;
   }
   else if((!EWselec_Wtag && EWselec_Htag) && EWselec1){
     sBin=44;
   }
  if(sBin==0){
    for(int i=0;i<METLowEdge_v2.size()-1;i++){
      if(METLowEdge_v2[i]<249.99) continue;
      m_i++;
      if(MET >= METLowEdge_v2[i] && MET < METLowEdge_v2[i+1]){ sBin = sBin+m_i;break; }
      else if(MET >= METLowEdge_v2[METLowEdge_v2.size()-1])  { sBin = 7         ;break; }
    }
  }

  else if(sBin==7 || sBin==13 || sBin==19 || sBin==25 || sBin==31){
    for(int i=0;i<METLowEdge_v2_1.size()-1;i++){
      if(METLowEdge_v2_1[i]<249.99) continue;
      m_i++;
      if(MET >= METLowEdge_v2_1[i] && MET < METLowEdge_v2_1[i+1]){ sBin = sBin+m_i;break; }
      else if(MET >= METLowEdge_v2_1[METLowEdge_v2_1.size()-1])  { sBin = sBin+6   ;break; }
      else if(MET >= METLowEdge_v2_1[METLowEdge_v2_1.size()-1])  { sBin = 37   ;break; }

    }
  }

  else if(sBin==37){
    for(int i=0;i<METLowEdge_v2.size()-1;i++){
      if(METLowEdge_v2[i]<249.99) continue;
      m_i++;
      if(MET >= METLowEdge_v2[i] && MET < METLowEdge_v2[i+1]){ sBin = sBin+m_i;break; }
      else if(MET >= METLowEdge_v2[METLowEdge_v2.size()-1])  { sBin = sBin+7   ;break; }
      else if(MET >= METLowEdge_v2[METLowEdge_v2.size()-1])  { sBin = 44   ;break; }

   }
  }

  else if(sBin==44){
    for(int i=0;i<METLowEdge_v2.size()-1;i++){
      if(METLowEdge_v2[i]<249.99) continue;
      m_i++;
      if(MET >= METLowEdge_v2[i] && MET < METLowEdge_v2[i+1]){ sBin = sBin+m_i;break; }
      else if(MET >= METLowEdge_v2[METLowEdge_v2.size()-1])  { sBin = sBin+7   ;break; }
      else if(MET >= METLowEdge_v2[METLowEdge_v2.size()-1])  { sBin = 51   ;break; }

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

