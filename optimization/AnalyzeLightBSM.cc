#define AnalyzeLightBSM_cxx
#include "AnalyzeLightBSM.h"
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

  AnalyzeLightBSM ana(inputFileList, outFileName, data);
  cout << "dataset " << data << " " << endl;

  ana.EventLoop(data,inputFileList);

  return 0;
}

void AnalyzeLightBSM::EventLoop(const char *data,const char *inputFileList) {
  if (fChain == 0) return;

  Long64_t nentries = fChain->GetEntriesFast();
  cout << "nentries " << nentries << endl;
  cout << "Analyzing dataset " << data << " " << endl;

  TString s_data=data;
  Long64_t nbytes = 0, nb = 0;
  int decade = 0;
  TCanvas *cA = new TCanvas("METEff","Signal efficiency",1500,850);
  int evtSurvived=0;  
  //  bool applISRWtsTottbar = 1;
  bool applISRWtsTottbar = 1, applyISRWtsFastSim=1;  
  TFile* pufile = TFile::Open("PileupHistograms_0121_69p2mb_pm4p6.root","READ");
  TH1* puhist = (TH1*)pufile->Get("pu_weights_down");
  cout<<"applying PU weights."<<endl
      <<"applying ISR weights to ttbar? "<<applISRWtsTottbar<<endl;

    //set file for getting ISR wts for signal
  TFile *fISR;  TH2D *h2_isrWtCorr;
  if(s_data.Contains("FastSim") && applyISRWtsFastSim){
    if(s_data.Contains("T5bbbb")){ fISR = new TFile("T5bbbbZg_MassScan.root");
    }
    else if(s_data.Contains("T5tttt")) fISR = new TFile("T5ttttZg_MassScan.root");
    else if(s_data.Contains("T5qqqq")) fISR = new TFile("T5qqqqHg_MassScan.root");
    else if(s_data.Contains("T6tt")) fISR = new TFile("T6ttZg_MassScan.root");

    h2_isrWtCorr = (TH2D*)fISR->Get("Nevts_NoISRWt");

    h2_isrWtCorr->Divide((TH2D*)fISR->Get("Nevts_ISRWt"));
  
  }

  // cout<<"sample ===>  "<<s_data<<endl;
  for (Long64_t jentry=0; jentry<nentries;jentry++) {
  // for (Long64_t jentry=0; jentry<10;jentry++) {
    
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
    
    wt=Weight*1000.0*lumiInfb*(puhist->GetBinContent(puhist->GetXaxis()->FindBin(min(TrueNumInteractions,puhist->GetBinLowEdge(puhist->GetNbinsX()+1)))));
    h_nEvts->Fill(1,wt);
    double isrWt=0.;
    vector<double> isrwt_arr={1., 0.920, 0.821, 0.715, 0.662, 0.561, 0.511};
    if(NJetsISR>=6) isrWt = isrwt_arr[6];
    else isrWt = isrwt_arr[NJetsISR];
    h_nEvts->Fill(2,wt*isrWt);
    //ISR weighting, end.

    // if(PFCaloMETRatio >=  5) continue;

    // if(wt<0)
    //   wt=abs(wt);

    //=================================================================================================
    if(s_data.Contains("TTJets2_v17"))
	if ( madHT>600) continue;
    				    
    if(!s_data.Contains("FastSim")){
      if(!(CSCTightHaloFilter==1 && HBHENoiseFilter==1 && HBHEIsoNoiseFilter==1 && eeBadScFilter==1 && EcalDeadCellTriggerPrimitiveFilter==1 && BadChargedCandidateFilter && BadPFMuonFilter && NVtx > 0) ) continue;
    }
   
    //-----------------------------------------cutflows--------------------------------------    
    h_selectBaselineYields_->Fill("No cuts, evt in 35.9/fb",wt);

    h_selectBaselineYields_2->Fill("No cuts, evt in 35.9/fb",wt);
    h_selectBaselineYields_2->Fill("Good #gamma with Pt > 100",wt);
    h_selectBaselineYields_2->Fill("veto electron & Muon",wt);
    h_selectBaselineYields_2->Fill("Iso track",wt);
    h_selectBaselineYields_2->Fill("MET>200",wt);
    h_selectBaselineYields_2->Fill("nJets >= 2",wt);
    // h_selectBaselineYields_2->Fill("ST & photon pt selec",wt);
    h_selectBaselineYields_2->Fill("dPhi1 & dPhi2 >= 0.3",wt);
    //    h_selectBaselineYields_2->Fill("MET>200",wt);
    h_selectBaselineYields_2->Fill("BTags >= 1",wt);
    h_selectBaselineYields_2->Fill("BTags = 0",wt);

   bool event_passed_old=false, event_passed_new=false;


   //============== Baseline Selections====================//

   TLorentzVector bestPhoton=getBestPhoton();


   //================Prompt photon from TTG ZG WG Gjets=========================================//
    if(bestPhotonIndxAmongPhotons<0) continue;
    bool bestPhoHasPxlSeed=true;
    if((*Photons_hasPixelSeed)[bestPhotonIndxAmongPhotons]<0.001) bestPhoHasPxlSeed=false;
    if( bestPhoHasPxlSeed ) continue;
    bool eMatchedG=check_eMatchedtoGamma();
    // bool process=false;
    if(eMatchedG) continue;
    //    if(allBestPhotons.size()<2) continue;
    bool noFakeJet = true;
    double gendRLepPho = getGendRLepPho();

    if(s_data=="genprompt" || s_data=="TTG" || s_data=="WG" || s_data=="ZG"){
      if(jentry==0){cout<<"**********processing "<<s_data<<" with prompt Gen photon"<<endl;}
      // if(hasGenPromptPhoton)
      // 	process=true;
      // else continue;
    }//Gen prompt
    else if( s_data=="WJets" ){
      if(hasGenPromptPhoton && gendRLepPho > 0.5 && madMinPhotonDeltaR > 0.5) continue;
      if(jentry<3) cout<<"Non-Prompt, dR(pho,q/g/lep) < 0.5 ";
    }
    else if((s_data=="gennonprompt") || (s_data=="TTJets") || (s_data=="SingleTop") || (s_data=="ZJets") ){
      if(hasGenPromptPhoton && gendRLepPho > 0.3 && madMinPhotonDeltaR > 0.3) continue;
      if(jentry<3) cout<<"Non-Prompt, dR(pho,q/g/lep) < 0.3 ";
    }//Gen non-prompt
    else if(s_data=="QCD"){
      if(jentry==0){cout<<"**********processing "<<s_data<<" w/o prompt gen photon"<<endl;}
      //      if(hasGenPromptPhoton && madMinDeltaRStatus==1 && madMinPhotonDeltaR > 0.4) continue;
      if(!((*Photons_nonPrompt)[bestPhotonIndxAmongPhotons]) && madMinDeltaRStatus==1 && madMinPhotonDeltaR > 0.4) continue;
    }
    else if(s_data=="GJets"){
      if(jentry==0){cout<<"**********processing "<<s_data<<" with prompt Gen photon"<<endl;}
      //      if(!hasGenPromptPhoton) continue;
      if((*Photons_nonPrompt)[bestPhotonIndxAmongPhotons]) continue;
    }

    else if(s_data.Contains("FastSim")){
      //      //reject events with any jet pt>20, |eta|<2.5 NOT matched to a GenJet (w/in DeltaR<0.3) and chfrac < 0.1
      for(unsigned j = 0; j < Jets->size(); ++j){
      	if(Jets->at(j).Pt() <= 20 || fabs(Jets->at(j).Eta())>=2.5) continue;
      	bool genMatched = false;
      	for(unsigned g = 0; g < GenJets->size(); ++g){
      	  if(GenJets->at(g).DeltaR(Jets->at(j)) < 0.3) {
      	    genMatched = true;
      	    break;
      	  }
      	}
      	if(!genMatched && Jets_chargedHadronEnergyFraction->at(j) < 0.1){
      	  noFakeJet = false;
      	  break;
      	}
      }
      if(applyISRWtsFastSim && s_data.Contains("FastSim")){
	double isrWt = 0,isrWtCorr = h2_isrWtCorr->GetBinContent(h2_isrWtCorr->GetXaxis()->FindBin(SusyMotherMass),h2_isrWtCorr->GetYaxis()->FindBin(SusyLSPMass));
	vector<double> isrwt_arr={1., 0.920, 0.821, 0.715, 0.662, 0.561, 0.511};
	if(NJetsISR>=6) isrWt = isrwt_arr[6];
	else isrWt = isrwt_arr[NJetsISR];
	wt = wt*isrWt*isrWtCorr;
	// cout<<"wt from "<<s_data<<" signals --> "<<wt<<endl;//"\t isrWt --> "<<isrWt<<"\t isrWtCorr --> "<<isrWtCorr<<"\t NJetsISR --> "<<NJetsISR<<endl;
      }
    }


     
    if(applISRWtsTottbar && s_data.Contains("TTJets")){
      double isrWt = 0;
      vector<double> D_values={1.0697, 1.0150, 0.9917, 0.9435, 0.95};
      //      vector<double> D_values={1.071, 0.7838, 0.7600, 0.7365, 0.7254};
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
   
    
    //=========================================================================//

    //photon pt cut
    if(bestPhoton.Pt()>100)     h_selectBaselineYields_->Fill("Good #gamma with Pt > 100",wt);
    else continue;

    // e & muon veto
    // if(s_data.Contains("v12")){
      // if (Electrons->size() == 0 && Muons->size() == 0 ) h_selectBaselineYields_->Fill("veto electron & Muon",wt);
      // else continue;
    // }
    // else if(s_data.Contains("v17")){
    if (NElectrons == 0 && NMuons == 0 ) h_selectBaselineYields_->Fill("veto electron & Muon",wt);
    else continue;
    // }
    // //apply iso track veto
    if(isoElectronTracks==0 && isoMuonTracks ==0 && isoPionTracks==0)
      {
	h_selectBaselineYields_->Fill("Iso track",wt);
      }
    else continue;                                   
    
    if( eMatchedG || bestPhoHasPxlSeed || (bestPhoton.Pt()<100))// || (Electrons->size() > 0) || (Muons->size() > 0) )
      continue;

    //========= hadjet -> removing jets which are matched with photon within mindr 0.3 =====//
    bool hadJetID=true;
 
    int minDRindx=-100,photonMatchingJetIndx=-100,nHadJets=0;
    double minDR=99999,ST=0;
    vector<TLorentzVector> hadJets;

    for(int i=0;i<Jets->size();i++){
      if( ((*Jets)[i].Pt() > 30.0) && (abs((*Jets)[i].Eta()) <= 2.4) ){
        double dR=bestPhoton.DeltaR((*Jets)[i]);
        if(dR<minDR){minDR=dR;minDRindx=i;}
      }
    }

    for(int i=0;i<Jets->size();i++){
      if( ((*Jets)[i].Pt() > 30.0) && (abs((*Jets)[i].Eta()) <= 2.4) ){
        if( !(minDR < 0.3 && i==minDRindx) ){
          hadJets.push_back((*Jets)[i]);
          if(hadJetID) hadJetID=(*Jets_ID)[i];
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

    //===============================================================//
    
    TLorentzVector Met;
    Met.SetPtEtaPhiE(MET,0,METPhi,0);
    double mT= 0.0, dPhi_METjet1=5, dPhi_METjet2=5, dPhi_phojet1=5, dPhi_phojet2=5, dPhi_phoMET=5; 
    if(hadJets.size() > 0) dPhi_phojet1 = abs(bestPhoton.DeltaPhi(hadJets[0])); 
    if(hadJets.size() > 1) dPhi_phojet2 = abs(bestPhoton.DeltaPhi(hadJets[1]));
    dPhi_METjet1 = abs(Met.DeltaPhi(hadJets[0])); 
    dPhi_METjet2 = abs(Met.DeltaPhi(hadJets[1]));
    dPhi_phoMET = abs(bestPhoton.DeltaPhi(Met));
    double mTPhoMET=sqrt(2*(bestPhoton.Pt())*MET*(1-cos(DeltaPhi(METPhi,bestPhoton.Phi()))));

    //----------------- WITHOUT ANY CUT ---------------------//
    if (hadJetID){
    h_BestPhotonPt_nocut->Fill(bestPhoton.Pt(),wt);    
    h_METvBin_nocut->Fill(MET,wt);
    h_METvBin_nocut1->Fill(MET,wt);
    h_METvBin_nocut2->Fill(MET,wt);
    h_PhovBin_nocut->Fill(bestPhoton.Pt(),wt);
    h_PhovBin_nocut1->Fill(bestPhoton.Pt(),wt);
    h_PhovBin_nocut2->Fill(bestPhoton.Pt(),wt);
    h_MET_nocut->Fill(MET,wt);
    h_nJets_nocut->Fill(nHadJets,wt);
    h_ST_nocut->Fill(ST,wt);
    h_BTags_nocut->Fill(BTags,wt);
    h_mTPhoMET_nocut->Fill(mTPhoMET,wt); 
    h_dPhi_METjet1_nocut->Fill(dPhi_METjet1,wt);
    h_dPhi_METjet2_nocut->Fill(dPhi_METjet2,wt);
    h_dPhi_phojet1_nocut->Fill(dPhi_phojet1,wt);
    h_dPhi_phojet2_nocut->Fill(dPhi_phojet2,wt);
    h_dPhi_phoMET_nocut->Fill(dPhi_phoMET,wt);
    h2_PtPhotonvsMET_nocut->Fill(bestPhoton.Pt(),MET,wt);
    }
    //===============Ak8 Jets ======================
    // bool hadAK8JetID =true;
    // int minDR4indx=-100;//photonMatchingJetIndx=-100,nHadJets=0;
    // double minDR4=99999;
    // vector<TLorentzVector> hadAK8Jets;
    // vector<double> hadAK8Mass;
    // double Ak8Mass;
    // for(int i=0;i<JetsAK8->size();i++)
    //   if( ((*JetsAK8)[i].Pt() > 30.0) && (abs((*JetsAK8)[i].Eta()) <= 2.4) ){
    //     double dR4=bestPhoton.DeltaR((*Jets)[i]);
    //     if(dR4<minDR4){minDR4=dR4;minDR4indx=i;}
    //   }

    // for(int i=0;i<JetsAK8->size();i++)
    //   if( ((*JetsAK8)[i].Pt() > 30.0) && (abs((*JetsAK8)[i].Eta()) <= 2.4) ){
    //     if( !(minDR4 < 0.3 && i==minDR4indx) ){
    //       hadAK8Jets.push_back((*JetsAK8)[i]);
    // 	  // hadAK8Mass.push_back((*JetsAK8_softDropMass)[i]);
    //       if(hadAK8JetID)
    // 	    {
    // 	      hadAK8JetID=(*JetsAK8_ID)[i];
    // 	      Ak8Mass = (*JetsAK8_softDropMass)[i];
    // 	      // hadAK8Mass.push_back((*JetsAK8_softDropMass)[i]);
    // 	    }
    // 	}
    // // cout<<jentry<<": "<<i<<"  JetsAK8->size()  --> "<<JetsAK8->size()<<"   (*JetsAK8)[i].Pt() "<<(*JetsAK8)[i].Pt()<<"   (*JetsAK8)[i].M() "<<(*JetsAK8)[i].M()<<endl;
    //   }

    // // for(int i=0;i<hadAK8Jets.size();i++)
    // //   {
    // // 	cout<<jentry<<": "<<i<<" hadAK8Jets.size()  --> "<<hadAK8Jets.size()<<"   hadAK8Jets[i].Pt() --> "<<hadAK8Jets[i].Pt()<<"   hadAK8Mass -->  "<<hadAK8Mass[i]<<endl;
    // //   }
    
    // // if(hadAK8Jets.size() !=0) cout<<jentry<<"   hadAK8Mass -->  "<<hadAK8Mass[0]<<endl;
    // // cout<<jentry<<"   AK8Mass -->  "<<Ak8Mass<<endl;
    

    // if (s_data.Contains("TChiWG") && (Ak8Mass > 100 || Ak8Mass < 65)) continue;
    // if (s_data.Contains("TChiWG")){    
    // // //======================= Boosted W from TChiWg sample having Mnlsp = 800 GeV ================================================
    // for(int i=0;i<GenParticles->size();i++){
    //   if((abs((*GenParticles_PdgId)[i])==24) && (abs((*GenParticles_ParentId)[i])>1000020) )
    // 	{
    // 	  //if( (abs((*GenParticles_ParentId)[i])>1000020 && (abs((*GenParticles_ParentId)[i])<1000025 &&  (abs((*GenParticles_Status)[i])==1))))
    // 	  for(int j=0;j<hadJets.size();j++){
    // 	    double dR= hadJets[j].DeltaR((*GenParticles)[i]);
    // 	    // if(dR<0.4)
    // 	    {
    // 		// h2_GenPhotonvsGenMET->Fill((*GenParticles)[i].Pt(),,wt);
    // 	    h2_GenWvsnjet->Fill((*GenParticles)[i].Pt(),hadJets.size(),wt);
    // 	    h_GenWpt->Fill((*GenParticles)[i].Pt(),wt);
    // 	    h_GenWeta->Fill((*GenParticles)[i].Eta(),wt);
    // 	    double dR1 = 9999.0 , dR2 = 9999.0 , dR3 = 9999.0;
    // 	    if(hadJets.size() == 1) 
    // 	      {
    // 	      dR1=hadJets[0].DeltaR((*GenParticles)[i]);
    // 	      h_dR_jetandW->Fill(dR1,wt);
    // 	      h_GenWpt1->Fill((*GenParticles)[i].Pt(),wt);
    // 	      h_GenWM1_1->Fill(hadJets[0].M(),wt);
    // 	      // h_GenWM1_1->Fill(hadAK8Mass[0],wt);
    // 	      h_GenWpt1_1->Fill(hadJets[0].Pt(),wt);
    // 	      h_GenWeta1->Fill((*GenParticles)[i].Eta(),wt);
    // 	    }
    // 	  if(hadJets.size() == 2) 
    // 	    {
    // 	      dR1=hadJets[0].DeltaR((*GenParticles)[i]);
    // 	      h_dR_jet1andW->Fill(dR1,wt);
    // 	      h_GenWpt2->Fill((*GenParticles)[i].Pt(),wt);
    // 	      h_GenWeta2->Fill((*GenParticles)[i].Eta(),wt);
    // 	      h_GenWpt2_1->Fill(hadJets[0].Pt(),wt);
    // 	      h_GenWeta2_1->Fill(hadJets[0].Eta(),wt);
    // 	      h_GenWM2_1->Fill(hadJets[0].M(),wt);
    // 	      dR2=hadJets[1].DeltaR((*GenParticles)[i]);
    // 	      h_dR_jet2andW->Fill(dR2,wt);
    // 	      h_GenWpt2_2->Fill(hadJets[1].Pt(),wt);
    // 	      h_GenWeta2_2->Fill(hadJets[1].Eta(),wt);
    // 	      h_GenWM2_2->Fill(hadJets[1].M(),wt);
    // 	      dR3=hadJets[0].DeltaR(hadJets[1]);
    // 	      h_dR_jet1andjet2->Fill(dR3,wt);
    // 	    }
    // 	// cout<<jentry<<": "<<i<<"  JetsAK8->size()  --> "<<JetsAK8->size()<<" , GenParticles_ParentId --> "<<abs((*GenParticles_ParentId)[i])<<" GenParticle_Status --> "<<abs((*GenParticles_Status)[i])<<endl;
	    
    // 	    }}}}
    //   }
    //-----------------optional cuts from trigger studies ---------------------//

    //Minimum MET
    if( MET>200)  
      {
    	h_selectBaselineYields_->Fill("MET>200",wt);
      }
    else continue;

    //       Minimum 2 jets (photon is not counted as jet)
    if( nHadJets >= 2 )
      {
    	h_selectBaselineYields_->Fill("nJets >= 2",wt);
      }
    // else if(nHadJets == 1)
    //   {
    // 	Met.SetPtEtaPhiE(MET,0,METPhi,0); 
    // 	dPhi_phojet1 = abs(bestPhoton.DeltaPhi(hadJets[0])); 
    // 	dPhi_METjet1 = abs(Met.DeltaPhi(hadJets[0])); 
    // 	dPhi_phoMET = abs(bestPhoton.DeltaPhi(Met));
    // 	if(dPhi_METjet1 >= 0.3 && dPhi_METjet2 >= 0.3 )
    // 	  {
    // 	    if(MET>200)
    // 	      {
    // 		h_MET_nj1->Fill(MET,wt);
    // 		h_METvBin_nj1->Fill(MET,wt);
    // 		h_METvBin1_nj1->Fill(MET,wt);
    // 		h_METvBin2_nj1->Fill(MET,wt);
    // 		h_intLumi->Fill(lumiInfb,wt);
    // 	      }
    // 	  }
    // 	continue;
    //   }
    else
      {
      // cout<<"nhadjet --> "<<nHadJets<<endl; 
      continue;
      }
    // TLorentzVector Met;
    dPhi_METjet1=3.8,dPhi_METjet2=3.8;//dphi3=3.8,dphi4=3.8,dphiG_MET=3.8;

    Met.SetPtEtaPhiE(MET,0,METPhi,0);
    dPhi_phojet1 = abs(bestPhoton.DeltaPhi(hadJets[0])); 
    dPhi_phojet2 = abs(bestPhoton.DeltaPhi(hadJets[1]));
    // dPhi_METjet1 = abs(Met.DeltaPhi(hadJets[0])); 
    // dPhi_METjet2 = abs(Met.DeltaPhi(hadJets[1]));
    dPhi_phoMET = abs(bestPhoton.DeltaPhi(Met));
    dPhi_METjet1 = abs(DeltaPhi(METPhi,(hadJets)[0].Phi())); 
    dPhi_METjet2 = abs(DeltaPhi(METPhi,(hadJets)[1].Phi()));

    //Minimum dPhi cut between MET and leading two jets
    if(dPhi_METjet1 > 0.3 && dPhi_METjet2 > 0.3 )
      {
	h_selectBaselineYields_->Fill("dPhi1 & dPhi2 >= 0.3",wt);
      }
    else continue;

    // //Minimum MET
    // if( MET>200)  
    //   {
    // 	h_selectBaselineYields_->Fill("MET>200",wt);
    //   }
    // else continue;

    //Minimum Btags
    if (BTags >=1)
      {
	h_selectBaselineYields_->Fill("BTags >= 1",wt);
	// continue;
      }
    else if (BTags ==0) h_selectBaselineYields_->Fill("BTags = 0",wt);

    
    if(photonMatchingJetIndx>=0 && ((*Jets)[photonMatchingJetIndx].Pt())/(bestPhoton.Pt()) < 1.0) continue;
    if(photonMatchingJetIndx<0) continue;
    if(eMatchedG > 0) continue;				     
    // if( (ST <= 500) ) continue;
    if( !((ST>800 && bestPhoton.Pt()>100) || (bestPhoton.Pt()>190)) )
      //      h_selectBaselineYields_->Fill("ST & photon pt selec",wt);
      continue;

    // if(s_data.Contains("FastSim")){
    //   hadJetID = true;
    //   if(!noFakeJet) continue;
    // }

    bool process= false;
    if(!eMatchedG && !bestPhoHasPxlSeed && bestPhoton.Pt()>=100 && (Electrons->size()==0) && (Muons->size()==0) && ST>500 && nHadJets>=2 && MET > 200 && dPhi_METjet1 > 0.3 && dPhi_METjet2 > 0.3)
      process =true;
    else continue;
    if(s_data.Contains("FastSim")){
      hadJetID = true;
      if(!noFakeJet) continue;
    }
    if(process){
    // cout<<"nhadjet --> "<<nHadJets<<endl; 
      evtSurvived++;
      if(hadJetID){
      h_BestPhotonPt->Fill(bestPhoton.Pt(),wt);    
      h_MET->Fill(MET,wt);
      h_METvBin->Fill(MET,wt);
      h_METvBin1->Fill(MET,wt);
      h_METvBin2->Fill(MET,wt);
      h_nJets->Fill(nHadJets,wt);
      h_ST->Fill(ST,wt);
      h_BTags->Fill(BTags,wt);
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
      }
      //    h_hadAk8Mass->Fill(Ak8Mass,wt);

      // for(int i=0;i<hadAK8Jets.size();i++)
      //   {  cout<<jentry<<": "<<i<<" hadAK8Jets.size()  --> "<<hadAK8Jets.size()<<"   hadAK8Jets[i].Pt() --> "<<hadAK8Jets[i].Pt()<<"   hadAK8Mass -->  "<<hadAK8Mass[i]<<endl;
      // h_GenWM2_1->Fill(hadAK8Mass[0],wt);
      // }


      if (BTags ==0){   
	if( nHadJets >= 2 && nHadJets <=  4 )
	  {
	    h_MET_nj2to4_nbjet0->Fill(MET,wt);
	    h_METvBin_nj2to4_nbjet0->Fill(MET,wt);
	    h_METvBin1_nj2to4_nbjet0->Fill(MET,wt);
	    h_METvBin2_nj2to4_nbjet0->Fill(MET,wt);
	  }

	if( nHadJets >= 5 && nHadJets <=  6 )
	  {
	    h_MET_nj5to6_nbjet0->Fill(MET,wt);
	    h_METvBin_nj5to6_nbjet0->Fill(MET,wt);
	    h_METvBin1_nj5to6_nbjet0->Fill(MET,wt);
	    h_METvBin2_nj5to6_nbjet0->Fill(MET,wt);
	  }

	if( nHadJets >= 7 )
	  {
	    h_MET_nj7toinf_nbjet0->Fill(MET,wt);
	    h_METvBin_nj7toinf_nbjet0->Fill(MET,wt);
	    h_METvBin1_nj7toinf_nbjet0->Fill(MET,wt);
	    h_METvBin2_nj7toinf_nbjet0->Fill(MET,wt);
	  }
      }

      if (BTags =1){   
	if( nHadJets >= 2 && nHadJets <=  4 )
	  {
	    h_MET_nj2to4_nbjet1->Fill(MET,wt);
	    h_METvBin_nj2to4_nbjet1->Fill(MET,wt);
	    h_METvBin1_nj2to4_nbjet1->Fill(MET,wt);
	    h_METvBin2_nj2to4_nbjet1->Fill(MET,wt);
	  }

	if( nHadJets >= 5 && nHadJets <=  6 )
	  {
	    h_MET_nj5to6_nbjet1->Fill(MET,wt);
	    h_METvBin_nj5to6_nbjet1->Fill(MET,wt);
	    h_METvBin1_nj5to6_nbjet1->Fill(MET,wt);
	    h_METvBin2_nj5to6_nbjet1->Fill(MET,wt);
	  }

	if( nHadJets >= 7 )
	  {
	    h_MET_nj7toinf_nbjet1->Fill(MET,wt);
	    h_METvBin_nj7toinf_nbjet1->Fill(MET,wt);
	    h_METvBin1_nj7toinf_nbjet1->Fill(MET,wt);
	    h_METvBin2_nj7toinf_nbjet1->Fill(MET,wt);
	  }
      }

      if (BTags >=1){   
	if( nHadJets >= 2 && nHadJets <=  4 )
	  {
	    h_MET_nj2to4_nbjetnot0->Fill(MET,wt);
	    h_METvBin_nj2to4_nbjetnot0->Fill(MET,wt);
	    h_METvBin1_nj2to4_nbjetnot0->Fill(MET,wt);
	    h_METvBin2_nj2to4_nbjetnot0->Fill(MET,wt);
	  }

	if( nHadJets >= 5 && nHadJets <=  6 )
	  {
	    h_MET_nj5to6_nbjetnot0->Fill(MET,wt);
	    h_METvBin_nj5to6_nbjetnot0->Fill(MET,wt);
	    h_METvBin1_nj5to6_nbjetnot0->Fill(MET,wt);
	    h_METvBin2_nj5to6_nbjetnot0->Fill(MET,wt);
	  }

	if( nHadJets >= 7 )
	  {
	    h_MET_nj7toinf_nbjetnot0->Fill(MET,wt);
	    h_METvBin_nj7toinf_nbjetnot0->Fill(MET,wt);
	    h_METvBin1_nj7toinf_nbjetnot0->Fill(MET,wt);
	    h_METvBin2_nj7toinf_nbjetnot0->Fill(MET,wt);
	  }
      }

    
      //-----------------------------------------------------------------------------------------

    
   
    
      h_intLumi->Fill(lumiInfb,wt);
      //    // h_NParticles->Fill(Particle_size);
    
      //    }
    }    
    }// loop over entries
  cout<<"Events Survied:"<<evtSurvived<<endl;

}   
TLorentzVector AnalyzeLightBSM::getBestPhoton(){
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

bool AnalyzeLightBSM::check_eMatchedtoGamma(){
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

double AnalyzeLightBSM::getGendRLepPho(){//MC only
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
