#define Lostlepton_cxx
#include "Lostlepton.h"
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

int main(int argc, char* argv[])
{

  if (argc < 2) {
    cerr << "Please give 3 arguments " << "runList " << " " << "outputFileName" << " " << "dataset" << endl;
    return -1;
  }
  const char *inputFileList = argv[1];
  const char *outFileName   = argv[2];
  const char *data          = argv[3];

  Lostlepton ana(inputFileList, outFileName, data);
  cout << "dataset " << data << " " << endl;

  ana.EventLoop(data,inputFileList);

  return 0;
}

void Lostlepton::EventLoop(const char *data,const char *inputFileList) {
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

  TFile *pufile,*TF;
  if(s_data.Contains("v17_2016")){
    pufile = TFile::Open("PileupHistograms_0121_69p2mb_pm4p6.root","READ");
    TF = TFile::Open("Run2016_TF_LE_v6_CD.root","READ");
  }
  if(s_data.Contains("v17_2017")){
    pufile = TFile::Open("PileupHistograms_0328_63mb_pm5.root","READ");
    TF = TFile::Open("Run2017_TF_LE_v6_CD.root","READ");
  }
  if(s_data.Contains("v17_2018")){
    pufile = TFile::Open("PileupHistograms_0118_63mb_pm5.root","READ");
    TF = TFile::Open("Run2018_TF_LE_v6_CD.root","READ");
  }

  TH1* puhist;
  TH1D* tf;

  if(s_data.Contains("2017")){
    TF = TFile::Open("Run2017_TF_LE_v6_CD.root","READ");
    tf = (TH1D*)TF->Get("tf");
  }
  if(s_data.Contains("2018")){
    TF = TFile::Open("Run2018_TF_LE_v6_CD.root","READ");
    tf = (TH1D*)TF->Get("tf");
  }
  if(s_data.Contains("2016")){
    TF = TFile::Open("Run2016_TF_LE_v6_CD.root","READ");
    tf = (TH1D*)TF->Get("tf");
  }

  if(s_data.Contains("v17"))
    {
      puhist = (TH1*)pufile->Get("pu_weights_down");
    }

  bool v17=true, v12=false;
  // bool v17=false, v12=true;
  bool EWselection=true;
  int elec_reco=0,elec_reco0_before=0,elec_reco1_before=0,muon_reco=0,elec_gen3=0,elec_gen2=0, elec_gen=0, muon_gen=0,elec_reco0=0,elec_reco1=0,evtSurvived_preselec=0,elec_reco2=0,elec2_reco=0,survived_vetohad=0,elec_reco1_CR=0,survived_elecge1=0,events_cr=0,events_sr=0,total=0,remain=0,elec_reco0_genel=0,efakepho=0,ele=0,genphomatch_after=0,genphomatch_before=0,elec_gen4=0,gentauhad2=0;
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
    int total_lost_el = 0,cr_el=0,sr_el;

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

    if(s_data.Contains("2016")) lumiInfb=35.9;
    if(s_data.Contains("2017")) lumiInfb=41.59;
    if(s_data.Contains("2018")) lumiInfb=59.74;
    if(s_data.Contains("FastSim") && s_data.Contains("2016")) lumiInfb=137.19;
    if(s_data=="ZG_v17_2017") lumiInfb=77.49;

    if(s_data.Contains("v17_2016") || s_data.Contains("v17_2017")){
      wt=Weight*1000.0*NonPrefiringProb*lumiInfb*(puhist->GetBinContent(puhist->GetXaxis()->FindBin(min(TrueNumInteractions,puhist->GetBinLowEdge(puhist->GetNbinsX()+1)))));
      h_nEvts->Fill(1,wt);
      }

    if(s_data.Contains("v17_2018")){
      wt=Weight*1000.0*lumiInfb*(puhist->GetBinContent(puhist->GetXaxis()->FindBin(min(TrueNumInteractions,puhist->GetBinLowEdge(puhist->GetNbinsX()+1)))));
      h_nEvts->Fill(1,wt);
      }


    if(s_data.Contains("2018")){
      for(int i=0; i<Electrons->size();i++)
        if((*Electrons)[i].Pt() >30 && (*Electrons)[i].Eta() > -3.0 && (*Electrons)[i].Eta() < -1.4 && (*Electrons)[i].Phi() > -1.57 && (*Electrons)[i].Phi() < -0.87) continue;
      for(int i=0; i<Jets->size();i++)
        if((*Jets)[i].Pt() > 30 && (*Jets)[i].Eta() > -3.2 && (*Jets)[i].Eta() < -1.2 && (*Jets)[i].Phi() > -1.77 && (*Jets)[i].Phi() < -0.67 && DeltaPhi((*Jets)[i].Pt(),MHTPhi)<0.5) continue;
    }

    if(s_data.Contains("data")){
      wt=1*0.97;
      h_nEvts->Fill(1,wt);
    }


    //ISR weighting, end.

    if(PFCaloMETRatio >=  5) continue;

    // if(wt<0)
    //   wt=abs(wt);

    //=================================================================================================
    if(s_data.Contains("TTJets2"))
      {//cout<<" correct "<<endl;
	if ( madHT>600) continue;
      }				    
    if(!s_data.Contains("FastSim")){

      if(!(CSCTightHaloFilter==1 && HBHENoiseFilter==1 && HBHEIsoNoiseFilter==1 && eeBadScFilter==1 && EcalDeadCellTriggerPrimitiveFilter==1 && BadPFMuonFilter && NVtx > 0) ) continue;
    }
   
    //-----------------------------------------cutflows--------------------------------------    
    h_selectBaselineYields_->Fill("No cuts, evt in 35.9/fb",wt);
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

   TLorentzVector bestPhoton=getBestPhoton();
   if(bestPhotonIndxAmongPhotons<0) continue;
   bool bestPhoHasPxlSeed=true;
   if((*Photons_hasPixelSeed)[bestPhotonIndxAmongPhotons]<0.001) bestPhoHasPxlSeed=false;
   if( bestPhoHasPxlSeed ) continue;

   if(s_data.Contains("v17_2016"))
     {
       if((s_data.Contains("TTJets")||s_data.Contains("TTJets_v17")||s_data.Contains("TTJets2_v17"))){
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
     }
  
    //=========================================================================//

    //photon pt cut
    if(bestPhoton.Pt()>100)
      {
	h_selectBaselineYields_->Fill("Good #gamma with Pt > 100",wt);

      }
    else continue;

    
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
    
    
    double mt_ele=0,mt_pho=0,mt_ele1=0;

    if (Electrons->size() == 1) {
      mt_ele=sqrt(2*(*Electrons)[0].Pt()*MET*(1-cos(DeltaPhi(METPhi,(*Electrons)[0].Phi()))));
      if(mt_ele>100) continue;
      if( ((*Electrons)[0].Pt() < 10) || abs((*Electrons)[0].Eta()) > 2.5 ) continue;
      elec_reco++;
    }
    
    if( bestPhoHasPxlSeed || (bestPhoton.Pt()<100)  )
      continue;

    //========= hadjet -> removing jets which are matched with photon within mindr 0.3 =====//
    bool hadJetID=true;
 
    int minDRindx=-100,photonMatchingJetIndx=-100,nHadJets=0;
    double minDR=99999,ST=0;
    vector<TLorentzVector> hadJets;

    for(int i=0;i<Jets->size();i++){
      if( ((*Jets)[i].Pt() > 30.0) && (abs((*Jets)[i].Eta()) <= 2.4) )
	{
            {
	      double dR=bestPhoton.DeltaR((*Jets)[i]);
	      if(dR<minDR){minDR=dR;minDRindx=i;}
	    }
	}
    }

    for(int i=0;i<Jets->size();i++){
      if( ((*Jets)[i].Pt() > 30.0) && (abs((*Jets)[i].Eta()) <= 2.4) ){
        if( !(minDR < 0.3 && i==minDRindx) ){
          if((*Jets_neutralHadronEnergyFraction)[i] < 0.90 && (*Jets_neutralEmEnergyFraction)[i] < 0.90 && (*Jets_chargedHadronEnergyFraction)[i] > 0 && (*Jets_multiplicity)[i] > 1 && (*Jets_chargedMultiplicity)[i] > 0)
            {
	      hadJets.push_back((*Jets)[i]);
	      if(hadJetID) hadJetID=(*Jets_ID)[i];
	    }
	}
      }
    }
    
    if( minDR<0.3 ) photonMatchingJetIndx=minDRindx;

    if(hadJets.size() == 0) continue;  
    for(int i=0;i<hadJets.size();i++)
      {
	if( (abs(hadJets[i].Eta()) < 2.4) ){ST=ST+(hadJets[i].Pt());}
	if( (abs(hadJets[i].Eta()) < 2.4) ){nHadJets++;}
      }
    
    if( minDR<0.3 ){
      ST=ST+bestPhoton.Pt();
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
    double mT=0, dPhi_METjet1=3.8,dPhi_METjet2=3.8, dPhi_phojet1=3.8, dPhi_phojet2=3.8, dPhi_phoMET=3.8;
    Met.SetPtEtaPhiE(MET,0,METPhi,0);
    if(hadJets.size() > 0)    dPhi_phojet1 = abs(bestPhoton.DeltaPhi(hadJets[0])); 
    if(hadJets.size() > 1)    dPhi_phojet2 = abs(bestPhoton.DeltaPhi(hadJets[1]));
    dPhi_phoMET = abs(bestPhoton.DeltaPhi(Met));
    dPhi_METjet1 = abs(DeltaPhi(METPhi,(hadJets)[0].Phi())); 
    dPhi_METjet2 = abs(DeltaPhi(METPhi,(hadJets)[1].Phi()));
    double mTPhoMET=sqrt(2*(bestPhoton.Pt())*MET*(1-cos(DeltaPhi(METPhi,bestPhoton.Phi()))));

    //Minimum dPhi cut between MET and leading two jets
    if(dPhi_METjet1 > 0.3 && dPhi_METjet2 > 0.3 )
      {
	h_selectBaselineYields_->Fill("dPhi1 & dPhi2 >= 0.3",wt);
      }
    else continue;
    
    if(photonMatchingJetIndx>=0 && ((*Jets)[photonMatchingJetIndx].Pt())/(bestPhoton.Pt()) < 1.0) continue;
    if(photonMatchingJetIndx<0) continue;

    // //============== New Trigger selections ================				     
    if( (ST <= 300) ) continue;

    if( !((MET>200 && bestPhoton.Pt()>100) ) )continue;
    else 
    h_selectBaselineYields_->Fill("MET>250 & photon pt>100 selec",wt);
    bool process= false;
    if(!bestPhoHasPxlSeed && bestPhoton.Pt()>=100 && ST>300 && nHadJets>=2 && MET > 200 && dPhi_METjet1 > 0.3 && dPhi_METjet2 > 0.3 && NMuons==0 &&((isoMuonTracks==0)&&(isoPionTracks==0)))
      process =true;
    else continue;

    //============== Old Trigger selections ================                                                                                  
    // if( (ST <= 500) ) continue;

    // if( !((ST>800 && bestPhoton.Pt()>100) || (bestPhoton.Pt()>190)) ) continue;
    // else    
    //  h_selectBaselineYields_->Fill("ST & photon pt selec",wt);
    // bool process= false;
    // if(!bestPhoHasPxlSeed && bestPhoton.Pt()>=100 && ST>500 && nHadJets>=2 && MET > 100 && dPhi_METjet1 > 0.3 && dPhi_METjet2 > 0.3 && NMuons==0 &&((isoMuonTracks==0)&&(isoPionTracks==0))){
    //    process =true;
    //    evtSurvived++;      
    //    h_selectBaselineYields_->Fill("Before Pre-Selections",wt);
       
    // }
    // else continue;
    
     ///////////////-========After Baseline Selections ////////////
    
    //    evtSurvived_preselec++;     

    //============== EWkino selections ===============

  
    //===============Ak8 Jets =====================
    bool hadAK8JetID =true;
    int minDR4indx=-100,minDR5indx , Ak8ID=-100;//photonMatchingJetIndx=-100,nHadJets=0;
    double minDR4=99999,minDR5;
    vector<TLorentzVector> hadAK8Jets;
    vector<TLorentzVector> hadAK8Jets_matchedW;
    vector<double> hadAK8Mass, hadAK8Mass_matchedW;
    double Ak8Mass,max=0.0,Ak8Mass1;
    for(int i=0;i<JetsAK8->size();i++)
      if( ((*JetsAK8)[i].Pt() > 30.0) && (abs((*JetsAK8)[i].Eta()) <= 2.4) ){
	double dR4=bestPhoton.DeltaR((*JetsAK8)[i]);
	if(dR4<minDR4){minDR4=dR4;minDR4indx=i;}
      }
    
    for(int i=0;i<JetsAK8->size();i++)
      if( ((*JetsAK8)[i].Pt() > 30.0) && (abs((*JetsAK8)[i].Eta()) <= 2.4) ){
	if( !(minDR4 < 0.3 && i==minDR4indx) ){
	  hadAK8Jets.push_back((*JetsAK8)[i]);
	  if(hadAK8JetID)
	    {
	      hadAK8JetID=(*JetsAK8_ID)[i];
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


    if(process && EWselection)
      {
	if(NElectrons>0){
	  double dr2=MinDr(bestPhoton,*Electrons);
	  if(dr2<=0.2) continue;
	}
	if(NElectrons==1) ele++;

	if(!s_data.Contains("data") ){


	  //==================================== After Baseline Events selection ========================
	  int nGenMu=0,nGenEle=0,nGenTau=0,nGenHad=0,nGenLep=0,nGenEle_tau=0,nGenMu_tau=0,nGentau_lep=0,nGentau_had=0,nGentau_had1=0,nGenTau1=0,nGenEle1=0,nGenEle_tau1=0,nGenMu1=0,nGenMu_tau1=0;
	  TLorentzVector genPho1,genEle1,neutr,genMu1,genTau1,genHad1,genLep1,gentau_lep1,gentau_had1;
	  vector<TLorentzVector> v_genEle1, v_genPho1, v_genMu1,v_genTau1,v_genHad1,v_genLep1,v_gentau_lep1,v_gentau_had1,v_gentau_had2,v_genTau2,v_genEle2,v_genMu2,v_genLep2;
	  int leadGenPhoIdx=-100;
	  // cout<<"++++++++++++++++"<<endl;
	  for(int i=0;i<GenParticles->size();i++){
	    if((*GenParticles)[i].Pt()!=0){
	      if((abs((*GenParticles_PdgId)[i])==22) && ((abs((*GenParticles_ParentId)[i])<=25) || ((*GenParticles_ParentId)[i]==2212) ) && (*GenParticles_Status)[i]==1 ){
		leadGenPhoIdx = i;
		genPho1 = ((*GenParticles)[i]);
		v_genPho1.push_back(genPho1);
	      }	
	    }
	  }
	  bool hadtau = false;
       
	  for(int i=0 ; i < GenElectrons->size(); i++)
	    {
	      if((*GenElectrons)[i].Pt()!=0)
		{
		  nGenEle1++;
		  genEle1 = ((*GenElectrons)[i]);
		  v_genEle2.push_back(genEle1);
		  v_genLep2.push_back(genEle1);
		  if((*GenElectrons_fromTau)[i])
		    nGenEle_tau1++;
		}
	    }
	  for(int i=0 ; i < GenMuons->size(); i++)
	    {
	      if((*GenMuons)[i].Pt()!=0)
		{
		  nGenMu1++;
		  genMu1 = ((*GenMuons)[i]);
		  v_genMu2.push_back(genMu1);
		  v_genLep2.push_back(genMu1);
		  if((*GenMuons_fromTau)[i])
		    nGenMu_tau1++;
		}
	    }
       
	  for(int i=0 ; i < GenTaus->size(); i++)
	    {
	      if((*GenTaus)[i].Pt()!=0)
		{
		  nGenTau1++;
		  genTau1 = ((*GenTaus)[i]);
		  v_genTau2.push_back(genTau1);
		  v_genLep2.push_back(genTau1);
		  if((*GenTaus_had)[i])
		    nGentau_had1++;
		}
	    }
	  
	  for(int i=0;i<nGenEle1;i++)
	    { h_mindr_lep_goodph->Fill(MinDr(v_genEle2[i],*Photons),wt);
	    }
	  { h_mindr_goodph_lep->Fill(MinDr(bestPhoton,v_genEle2),wt);
	  }
	  for(int i=0;i<v_genPho1.size();i++)
	    { h_mindr_ph_lep->Fill(MinDr(v_genPho1[i],v_genEle2),wt);
	      h_mindr_genph_lep->Fill(MinDr(v_genPho1[i],v_genLep2),wt);
	      //  h_mindr_genph_had->Fill(MinDr(v_genPho1[i], v_genHad1),wt);

	    }
	  h_madminphotonDR->Fill(madMinPhotonDeltaR,wt);
	  //	  h_mindr_goodph_had->Fill(MinDr(bestPhoton, v_genHad1),wt);
	  h_mindr_goodph_ph->Fill(MinDr(bestPhoton,v_genPho1),wt);

	  /////////////// prompt photon check //////////////////
	  genphomatch_before++;
	  double gendRLepPho = getGendRLepPho();
	 
	  if(s_data=="genprompt" || s_data.Contains("TTG") ){
	    if(!hasGenPromptPhoton){
	      if(jentry==0)cout<<"**********processing "<<s_data<<" with non-prompt Gen photon"<<endl;
	    }
	    else if(hasGenPromptPhoton){
	      if(!(madMinPhotonDeltaR >= 0.3 && MinDr(bestPhoton,v_genLep2) >=0.5 ))continue;	   
	    }
	  }//Gen prompt

       
	  if(s_data=="genprompt" || s_data.Contains("WG")){
	    if(!hasGenPromptPhoton){
	      if(jentry==0)cout<<"**********processing "<<s_data<<" with non-prompt Gen photon"<<endl;
	    }
	    else if(hasGenPromptPhoton){
	      if(!(madMinPhotonDeltaR >= 0.5 && MinDr(bestPhoton,v_genLep2) >=0.5 ))continue;
	    }
	  }//Gen prompt                                                                                                                         
     	
	  if(s_data.Contains("WJets")){
	    if(!hasGenPromptPhoton){
	      if(jentry==0)cout<<"**********processing "<<s_data<<" with non-prompt Gen photon"<<endl;
	    }
	    else if(hasGenPromptPhoton){
	      if(!(madMinPhotonDeltaR < 0.5 || MinDr(bestPhoton,v_genLep2) < 0.5)) continue;
	    }
	  }
	  if(s_data.Contains("TTJets") || s_data.Contains("TTJets_v17") || s_data.Contains("TTJets2_v17"))
	    {
	      if(!hasGenPromptPhoton){
		if(jentry==0)cout<<"**********processing "<<s_data<<" with non-prompt Gen photon"<<endl;
	      }
	      else if(hasGenPromptPhoton){
		if(!(madMinPhotonDeltaR < 0.3 || MinDr(bestPhoton,v_genLep2) < 0.5)) continue;
	      }	     
	    }//Gen non-prompt
	 	   
	  genphomatch_after++;

	  
	  if(NElectrons==0 ){
	     
	     
	    if(nGenMu1==0 && nGenEle1==0 && v_genTau2.size()==0) continue;//to reject W->qq' type of events
	    if(nGentau_had1>1) continue;                                                                                                   
	    survived_vetohad++;
	    if(nGenMu1>0) continue;
	    survived_elecge1++;

	    total++;
	       
	    if(!(*Photons_electronFakes)[bestPhotonIndxAmongPhotons])
	      { h_mindr_lep_goodph->Fill(MinDr(bestPhoton,v_genEle2),wt);
		//h_mindr_goodph_lep->Fill(MinDr((*Photons)[bestPhotonIndxAmongPhotons],v_genEle1),wt);
		pass_realphoton++;
	      }
	    else
	      {
		fail_realphoton++;
		continue;
	      }
	 
	    if(isoElectronTracks!=0 || isoMuonTracks!=0 || isoPionTracks!=0) continue;	 
	    if(v_genEle2.size()==0) {TLorentzVector v1;v_genEle2.push_back(v1);}
	    sortTLorVec(&v_genEle2);
	 
	    if(nGenEle1 == 1) elec_gen++;
	    if(nGenTau1 > 0) elec_gen2++; 
	    if(nGenMu_tau1 > 0) elec_gen3++; 
	    if(nGenEle_tau1 > 0) elec_gen4++;
	    if(nGentau_had1 > 0) gentauhad2++; 

	    int n=0,l=0,m=0,o=0;
	 
	    elec_reco0_before++;
      
	    cr_el=0,m=0;
	    int q=0,u=0;


	    bool acceptance=true,id=true,iso=true,cr=true,sr=true;  
	    for(int i=0; i<nGenEle1; i++){
	      if (NElectrons == 0 && q<1) {
		elec_reco0_genel++;
		q++;
		elec_reco0++;
		h_selectBaselineYields_->Fill("SR : Electrons = 0",wt);
		int sBin6 = getBinNoV7_le(nHadJets);
		h_SBins_v6_CD_elec0->Fill(sBin6,wt);	
		int sBin7_SP_elec0 = getBinNoV7(nHadJets);
		h_SBins_v7_CD_SP_elec0->Fill(sBin7_SP_elec0,wt);
		int sBin6_SP_elec0 = getBinNoV6(nHadJets);
		h_SBins_v6_CD_SP_elec0->Fill(sBin6_SP_elec0,wt);
		int sBin6_50bin= getBinNoV6_EWplusSP_CR(EWselec,EWselec1 ,EWselec_Htag,EWselec_Wtag,nHadJets);
		h_SBins_v6_CD_EW_50bin_elec0->Fill(sBin6_50bin,wt);

	      }

	      if(nGenEle1==1 || (acceptance & id & nGenEle1>1)){
		////acceptance check
		acceptance=true;
		if(((abs(v_genEle2[i].Eta())>2.5)||(v_genEle2[i].Pt()<10) ||(Electrons->size()==0)))
		  {     
		    fail_acceptance++;
		    acceptance=false;
		    int sBin6 = getBinNoV7_le(nHadJets);
		    h_SBins_v6_CD_elec0_acc->Fill(sBin6,wt);	
		    int sBin7_SP_elec0_acc = getBinNoV7(nHadJets);
		    h_SBins_v7_CD_SP_elec0_acc->Fill(sBin7_SP_elec0_acc,wt);
		    int sBin6_SP_elec0_acc = getBinNoV6(nHadJets);
		    h_SBins_v6_CD_SP_elec0_acc->Fill(sBin6_SP_elec0_acc,wt);
	       
		  }
	     
		if(acceptance)
		  {
		    pass_acceptance++;
		    id=true;
		    if(NElectrons==0)
		      {
			fail_id++;
			id=false;
		     
			int sBin6 = getBinNoV7_le(nHadJets);
			h_SBins_v6_CD_elec0_id->Fill(sBin6,wt);	
			int sBin7_SP_elec0_id = getBinNoV7(nHadJets);
			h_SBins_v7_CD_SP_elec0_id->Fill(sBin7_SP_elec0_id,wt);
			int sBin6_SP_elec0_id = getBinNoV6(nHadJets);
			h_SBins_v6_CD_SP_elec0_id->Fill(sBin6_SP_elec0_id,wt);

		      }
		  }

		if(id && acceptance) pass_id++;

		if(!id || !acceptance) 
		  elec_reco1++;
	      }
	   
	    }// gen electron loop
	  }// NElectron = 0
	}//MC for SR
  
	//CR region for MC and data
	if((NElectrons==1 && (cr_el < 1)))
	  {
	    events_cr = events_cr+ 1 ; 
	    cr_el++;
	    h_selectBaselineYields_->Fill("CR : Electrons = 1",wt);
	    int sBin6 = getBinNoV7_le(nHadJets);
	    h_SBins_v6_CD_elec1->Fill(sBin6,wt);	
	    int sBin7_SP_elec1 = getBinNoV7(nHadJets);
	    h_SBins_v7_CD_SP_elec1->Fill(sBin7_SP_elec1,wt);
	    int sBin6_SP_elec1 = getBinNoV6(nHadJets);
	    h_SBins_v6_CD_SP_elec1->Fill(sBin6_SP_elec1,wt);
	    int sBin6_50bin= getBinNoV6_EWplusSP_CR(EWselec,EWselec1 ,EWselec_Htag,EWselec_Wtag,nHadJets);
	    h_SBins_v6_CD_EW_50bin_elec1->Fill(sBin6_50bin,wt);
     
	    h_BestPhotonPt->Fill(bestPhoton.Pt(),wt);    
	    h_MET->Fill(MET,wt);
	    h_METvBin->Fill(MET,wt);
	    h_METvBin1->Fill(MET,wt);
	    h_METvBin2->Fill(MET,wt);
	    h_nJets->Fill(nHadJets,wt);
	    h_ST->Fill(ST,wt);
	    h_BTags->Fill(BTags,wt);
	    h_minDr_bestphoEle->Fill(MinDr(bestPhoton,*Electrons),wt);
	    h_minDr_bestphoJets->Fill(MinDr(bestPhoton,hadJets),wt);
	    h_mTPhoMET->Fill(mTPhoMET,wt); 
	    h_dPhi_METjet1->Fill(dPhi_METjet1,wt);
	    h_dPhi_METjet2->Fill(dPhi_METjet2,wt);
	    h_dPhi_phojet1->Fill(dPhi_phojet1,wt);
	    h_dPhi_phojet2->Fill(dPhi_phojet2,wt);
	    h_dPhi_phoMET->Fill(dPhi_phoMET,wt);
	    
	    h2_PtPhotonvsMET->Fill(bestPhoton.Pt(),MET,wt);
	    h_PhovBin->Fill(bestPhoton.Pt(),wt);
	    h_PhovBin1->Fill(bestPhoton.Pt(),wt);
	    h_PhovBin2->Fill(bestPhoton.Pt(),wt);
	    h_hadAk8Mass->Fill(Ak8Mass,wt);
	    h_hadAk8Mass_vBin->Fill(Ak8Mass,wt);
	    h_intLumi->Fill(lumiInfb,wt);
	    if(process && EWselection && (EWselec && EWselec1))
	      {
		EW_evtSurvived++;
		h_BestPhotonPt_EW->Fill(bestPhoton.Pt(),wt);
		h_MET_EW->Fill(MET,wt);
		h_nJets_EW->Fill(nHadJets,wt);
		h_METvBin_EW->Fill(MET,wt);
		h_METvBin_EW_v1->Fill(MET,wt);
		h_METvBin_EW_v2->Fill(MET,wt);
		h_ST_EW->Fill(ST,wt);
		h_BTags_EW->Fill(BTags,wt);
		h_intLumi_EW->Fill(lumiInfb,wt);
		h_hadAk8Mass_EW->Fill(Ak8Mass,wt);
		h_hadAk8Mass_EW_vBin->Fill(Ak8Mass,wt);
		h_minDr_bestphoEle_EW->Fill(MinDr(bestPhoton,*Electrons),wt);
		h_minDr_bestphoJets_EW->Fill(MinDr(bestPhoton,hadJets),wt);
	      }
	    if(process && EWselection && !(EWselec && EWselec1))
	      {
		SP_evtSurvived++;
		h_BestPhotonPt_SP->Fill(bestPhoton.Pt(),wt);
		h_MET_SP->Fill(MET,wt);
		h_METvBin_SP->Fill(MET,wt);
		h_METvBin_SP_v1->Fill(MET,wt);
		h_METvBin_SP_v2->Fill(MET,wt);
		h_nJets_SP->Fill(nHadJets,wt);
		h_ST_SP->Fill(ST,wt);
		h_BTags_SP->Fill(BTags,wt);
		h_intLumi_SP->Fill(lumiInfb,wt);
		h_hadAk8Mass_SP->Fill(Ak8Mass,wt);
		h_hadAk8Mass_SP_vBin->Fill(Ak8Mass,wt);
		h_minDr_bestphoEle_SP->Fill(MinDr(bestPhoton,*Electrons),wt);
		h_minDr_bestphoJets_SP->Fill(MinDr(bestPhoton,hadJets),wt);
	      }

	    
	    //////////////////////// for reweighting the CR region events with Transfer factors //////////////////////
	    if(BTags==0){
	      if(nHadJets==2)     { wt2=wt*tf->GetBinContent(1);}
	      else if(nHadJets==3)     { wt2=wt*tf->GetBinContent(2);}
	      else if(nHadJets==4)     { wt2=wt*tf->GetBinContent(3);}
	      else if((nHadJets==5 || nHadJets==6)){ wt2=wt*tf->GetBinContent(4);}
	      else if(nHadJets>=7)   { wt2=wt*tf->GetBinContent(5);}
	    }
	    else{
	      if(nHadJets>=2 && nHadJets<=4)      { wt2=wt*tf->GetBinContent(6);}
	      else if((nHadJets==5 || nHadJets==6)){ wt2=wt*tf->GetBinContent(7);}
	      else if(nHadJets>=7)   { wt2=wt*tf->GetBinContent(8);}
	    }
            int sBin6_closure = getBinNoV7_le(nHadJets);
            h_SBins_v6_CD_elec1_closure->Fill(sBin6_closure,wt2);
	    int sBin6_SP_elec1_closure = getBinNoV6(nHadJets);
            h_SBins_v6_CD_SP_elec1_closure->Fill(sBin6_SP_elec1_closure,wt2);
	    int sBin6_50bin_closure= getBinNoV6_EWplusSP_CR(EWselec,EWselec1 ,EWselec_Htag,EWselec_Wtag,nHadJets);
	    h_SBins_v6_CD_EW_50bin_elec1_closure->Fill(sBin6_50bin_closure,wt2);


	  }
      }

    
                                                    
  }  // loop over entries
  cout<<"Cross-section : "<<CrossSection<<endl;
  cout<<"Weight ib pb-1 : "<<Weight<<endl;
    
  cout<<"Events Survived after PreSelection : "<<evtSurvived_preselec<<endl;
  cout<<"Events having NElectrons=1 : "<<ele<<endl;
  cout<<"Events Survived before genphomatch : "<<genphomatch_before<<endl;
  cout<<"Events Survived after genphomatch : "<<genphomatch_after<<endl;
  cout<<"=========for NElectron = 0 ========"<<endl;
  cout<<"Events Survived after PreSelection : "<<evtSurvived_preselec<<endl;
  cout<<"Events having NElectrons=1 : "<<ele<<endl;
  cout<<"Events Survived veto had : "<<survived_vetohad<<endl;
  cout<<"total events before real photon check --> "<<total<<endl;
  cout<<"pass realphoton --> "<<pass_realphoton<<endl;
  cout<<"fail realphoton --> "<<fail_realphoton<<endl;
  //  cout<<"Events with no muon or 1 muon + 1 electron : "<<survived_elecge1<<endl;
  cout<<"Events with 1 electron gen : "<<elec_gen<<endl;
  cout<<"Events with gen tau > 0  : "<<elec_gen2<<endl;
  cout<<"Events with gen mu from tau > 0 : "<<elec_gen3<<endl;
  cout<<"Events with gen ele from tau > 0 : "<<elec_gen4<<endl;
  cout<<"Events with jets from tau > 0 : "<<gentauhad2<<endl;
  cout<<"Events with 0 electron reco before check : "<<elec_reco0_before<<endl;
  cout<<"Events with 0 electron reco & gen e- > 0 before check : "<<elec_reco0_genel<<endl;
  // cout<<"Events with >=2 electron reco before check : "<<elec_reco2<<endl;
  cout<<"Acceptance Check : check gen e in detector accept"<<endl;
  cout<<"pass acceptance --> "<<pass_acceptance<<endl;
  cout<<"fail acceptance --> "<<fail_acceptance<<endl;
  cout<<"ID + iso check : NElectrons = 0 : "<<endl;
  cout<<"pass id + iso --> "<<pass_id<<endl;
  cout<<"fail id + iso --> "<<fail_id<<endl;
  cout<<"=============================================================="<<endl;
  cout<<"Events in SR (fail accept + fail id + fail iso): "<<elec_reco0<<endl;
  cout<<"Events in CR passing accept x id x iso check : "<<events_cr<<endl;
  cout<<"Events Survived after SP Selections in CR region : "<<SP_evtSurvived<<endl;
  cout<<"Events Survived after EW Selections in CR region : "<<EW_evtSurvived<<endl;
   
}

TLorentzVector Lostlepton::getBestPhoton(){
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

int Lostlepton::getBinNoV7(int nHadJets){
  int sBin=-100,m_i=0;
  if(BTags==0){
    if(nHadJets>=2 && nHadJets<=4)     { sBin=0;}
    else if(nHadJets==5 || nHadJets==6){ sBin=6;}
    else if(nHadJets>=7)               { sBin=11;}
  }
  else{
    if(nHadJets>=2 && nHadJets<=4)     { sBin=16;}
    else if(nHadJets==5 || nHadJets==6){ sBin=21;}
    else if(nHadJets>=7)               { sBin=26;}
  }
  if(sBin==0){
    for(int i=0;i<METLowEdge1.size()-1;i++){
      if(METLowEdge1[i]<99.99) continue;
      m_i++;
      if(MET >= METLowEdge1[i] && MET < METLowEdge1[i+1]){ sBin = sBin+m_i;break; }
      else if(MET >= METLowEdge1[METLowEdge1.size()-1])  { sBin = 6         ;break; }
    }
  }
  else{
    for(int i=0;i<METLowEdge2.size()-1;i++){
      if(METLowEdge2[i]<99.99) continue;
      m_i++;
      if(MET >= METLowEdge2[i] && MET < METLowEdge2[i+1]){ sBin = sBin+m_i;break; }
      else if(MET >= METLowEdge2[METLowEdge2.size()-1])  { sBin = sBin+5   ;break; }
    }
  }
  return sBin;
}

int Lostlepton::getBinNoV7_le(int nHadJets){
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

int Lostlepton::getBinNoV7_le2(int nHadJets){
  int sBin=-100,m_i=0;
  if(BTags==0){
    if(nHadJets==2 && MET >=100 && MET<150)     { sBin=1;}
    else if(nHadJets==2 && MET >= 150 )     { sBin=2;}
    else if(nHadJets==3 && MET >=100 && MET<150)     { sBin=3;}
    else if(nHadJets==3 && MET >= 150)     { sBin=4;}
    else if(nHadJets==4 && MET >=100 && MET<150)     { sBin=5;}
    else if(nHadJets==4 && MET>=150)     { sBin=6;}
    else if((nHadJets==5 || nHadJets==6) && MET >=100 && MET<150){ sBin=7;}
    else if((nHadJets==5 || nHadJets==6) && MET>=150){ sBin=8;}
    else if(nHadJets>=7 && MET >=100 && MET<150)   { sBin=9;}
    else if(nHadJets>=7 && MET>=150)   { sBin=10;}
  }
  else{
    if(nHadJets>=2 && nHadJets<=4 && MET >=100 && MET<150)     { sBin=11;}
    else if(nHadJets>=2 && nHadJets<=4 && MET>=150)      { sBin=12;}
    else if((nHadJets==5 || nHadJets==6)  && MET >=100 && MET<150){ sBin=13;}
    else if((nHadJets==5 || nHadJets==6) && MET>=150){ sBin=14;}
    else if(nHadJets>=7  && MET >=100 && MET<150)               { sBin=15;}
    else if(nHadJets>=7 && MET>=150)               { sBin=16;}
  }
  return sBin;
}

int Lostlepton::getBinNoV6(int nHadJets){
  int sBin=-100,m_i=0;
  if(BTags==0){
    if(nHadJets>=2 && nHadJets<=4)     { sBin=0;}
    else if(nHadJets==5 || nHadJets==6){ sBin=7;}
    else if(nHadJets>=7)               { sBin=13;}
  }
  else{
    if(nHadJets>=2 && nHadJets<=4)     { sBin=19;}
    else if(nHadJets==5 || nHadJets==6){ sBin=25;}
    else if(nHadJets>=7)               { sBin=31;}
  }
  if(sBin==0){
    for(int i=0;i<METLowEdge_v2.size()-1;i++){
      if(METLowEdge_v2[i]<249.99) continue;
      m_i++;
      if(MET >= METLowEdge_v2[i] && MET < METLowEdge_v2[i+1]){ sBin = sBin+m_i;break; }
      else if(MET >= METLowEdge_v2[METLowEdge_v2.size()-1])  { sBin = 7         ;break; }
    }
  }
  else{
    for(int i=0;i<METLowEdge_v2_1.size()-1;i++){
      if(METLowEdge_v2_1[i]<249.99) continue;
      m_i++;
      if(MET >= METLowEdge_v2_1[i] && MET < METLowEdge_v2_1[i+1]){ sBin = sBin+m_i;break; }
      else if(MET >= METLowEdge_v2_1[METLowEdge_v2_1.size()-1])  { sBin = sBin+6   ;break; }
    }
  }
  return sBin;
}


int Lostlepton::getBinNoV6_EW(bool EWselec_Htag , bool EWselec_Wtag){
  int sBin=-100,m_i=0;
  if(EWselec_Wtag && !EWselec_Htag){
    sBin=0;
  }
  else if(!EWselec_Wtag && EWselec_Htag){
    sBin=7;
  }
  if(sBin==0){
    for(int i=0;i<METLowEdge_v2.size()-1;i++){
      if(METLowEdge_v2[i]<249.99) continue;
      m_i++;
      if(MET >= METLowEdge_v2[i] && MET < METLowEdge_v2[i+1]){ sBin = sBin+m_i;break; }
      else if(MET >= METLowEdge_v2[METLowEdge_v2.size()-1])  { sBin = 7         ;break; }
    }
  }
  else if(sBin==7){
    for(int i=0;i<METLowEdge_v2.size()-1;i++){
      if(METLowEdge_v2[i]<249.99) continue;
      m_i++;
      if(MET >= METLowEdge_v2[i] && MET < METLowEdge_v2[i+1]){ sBin = sBin+m_i;break; }
      else if(MET >= METLowEdge_v2[METLowEdge_v2.size()-1])  { sBin = sBin+7   ;break; }
    }
  }
  return sBin;
}

int Lostlepton::getBinNoV6_EW1(bool EWselec){
  int sBin=-100,m_i=0;
  if(EWselec){
    sBin=0;
  }
  if(sBin==0){
    for(int i=0;i<METLowEdge_v2.size()-1;i++){
      if(METLowEdge_v2[i]<249.99) continue;
      m_i++;
      if(MET >= METLowEdge_v2[i] && MET < METLowEdge_v2[i+1]){ sBin = sBin+m_i;break; }
      else if(MET >= METLowEdge_v2[METLowEdge_v2.size()-1])  { sBin = 7         ;break; }
    }
  }
 
  return sBin;
}

int Lostlepton::getBinNoV6_EWplusSP_CR(bool EWselec, bool EWselec1, bool EWselec_Htag , bool EWselec_Wtag,int nHadJets){

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

 int Lostlepton::getBinNoV6_EWplusSP_SR(bool EWselec1, bool EWselec_Htag , bool EWselec_Wtag,int nHadJets){

  int sBin=-100,m_i=0;


  if(!(EWselec_Wtag || EWselec_Htag || EWselec1))
    {
      if(BTags==0){
	if(nHadJets>=2 && nHadJets<=4)     { sBin=0;}
	else if(nHadJets==5 || nHadJets==6){ sBin=6;}
	else if(nHadJets>=7)               { sBin=11;}
      }
      else{
	if(nHadJets>=2 && nHadJets<=4)     { sBin=16;}
	else if(nHadJets==5 || nHadJets==6){ sBin=21;}
	else if(nHadJets>=7)               { sBin=26;}
      }
    }
  if((EWselec_Wtag && !EWselec_Htag) &&  EWselec1){
    sBin=31;
  }
  else if((!EWselec_Wtag && EWselec_Htag) && EWselec1){
    sBin=37;
  }
  if(sBin==0){
    for(int i=0;i<METLowEdge_v3.size()-1;i++){
      if(METLowEdge_v3[i]<299.99) continue;
      m_i++;
      if(MET >= METLowEdge_v3[i] && MET < METLowEdge_v3[i+1]){ sBin = sBin+m_i;break; }
      else if(MET >= METLowEdge_v3[METLowEdge_v3.size()-1])  { sBin = 6         ;break; }
    }
  }

  else if(sBin==6 || sBin==11 || sBin ==16 || sBin ==21 || sBin == 26){
    for(int i=0;i<METLowEdge_v3_1.size()-1;i++){
      if(METLowEdge_v3_1[i]<299.99) continue;
      m_i++;
      if(MET >= METLowEdge_v3_1[i] && MET < METLowEdge_v3_1[i+1]){ sBin = sBin+m_i;break; }
      else if(MET >= METLowEdge_v3_1[METLowEdge_v3_1.size()-1])  { sBin = sBin+5   ;break; }
      //   else if(MET >= METLowEdge_v3_1[METLowEdge_v3_1.size()-1])  { sBin = 31   ;break; }

    }
  }


  else if(sBin==31){
    for(int i=0;i<METLowEdge_v3.size()-1;i++){
      if(METLowEdge_v3[i]<299.99) continue;
      m_i++;
      if(MET >= METLowEdge_v3[i] && MET < METLowEdge_v3[i+1]){ sBin = sBin+m_i;break; }
      else if(MET >= METLowEdge_v3[METLowEdge_v3.size()-1])  { sBin = sBin+6   ;break; }
      //      else if(MET >= METLowEdge_v3[METLowEdge_v3.size()-1])  { sBin = 37   ;break; }

   }
  }

  else if(sBin==37){
    for(int i=0;i<METLowEdge_v3.size()-1;i++){
      if(METLowEdge_v3[i]<299.99) continue;
      m_i++;
      if(MET >= METLowEdge_v3[i] && MET < METLowEdge_v3[i+1]){ sBin = sBin+m_i;break; }
      else if(MET >= METLowEdge_v3[METLowEdge_v3.size()-1])  { sBin = sBin+6   ;break; }
 
   }
  }
  return sBin;
}





bool Lostlepton::check_eMatchedtoGamma(){
  for(int i=0;i<Electrons->size();i++){
    for(int j=0;j<Photons->size();j++){
      if( (DeltaR( (*Electrons)[i].Eta(),(*Electrons)[i].Phi(),(*Photons)[j].Eta(),(*Photons)[j].Phi()) ) < 0.01){
	//cout<<(*Electrons)[i].Pt()<<" "<<(*Electrons)[i].Eta()<<" "<<(*Electrons)[i].Phi()<<" "<<(*Photons)[i].Pt()<<" "<<(*Photons)[i].Eta()<<" "<<(*Photons)[i].Phi()<<endl;
	//print(0);
	return true;
      }
    }
  }
  return false;
}

double Lostlepton::getGendRLepPho(){//MC only
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
