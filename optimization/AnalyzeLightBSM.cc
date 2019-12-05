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

  Long64_t nbytes = 0, nb = 0;
  int decade = 0;
  TCanvas *cA = new TCanvas("METEff","Signal efficiency",1500,850);

  for (Long64_t jentry=0; jentry<nentries;jentry++) {
  // for (Long64_t jentry=0; jentry<1000;jentry++) {

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
    TString s_data=data;
    // Double_t wt2 = 0.002472;
    // h_selectBaselineYields_->Fill("No cuts, evt in 35.9/fb",Weight*1000.0*35.9);
    // h_selectBaselineYields_2->Fill("No cuts, evt in 35.9/fb",wt2);
    if(PFCaloMETRatio >=  5) continue;

    wt=Weight*1000.0*lumiInfb;
    if(wt<0) continue;
    Double_t isrWt=0, isrWtCorr = 1, xsec=0;
    vector<double> isrwt_arr={1., 0.920, 0.821, 0.715, 0.662, 0.561, 0.511};
   if(NJetsISR>=6) isrWt = isrwt_arr[6];                                                                   
    else isrWt = isrwt_arr[NJetsISR];       
   if(s_data.Contains("FastSim_T5bbbbZg_1800_1750"))   isrWtCorr = 1.21; //chi10 mass = 1750
   else if(s_data.Contains("FastSim_T5bbbbZg_1800_150")) isrWtCorr = 1.195; //chi10 mass = 150
   else if(s_data.Contains("FastSim_TChiWg_0_800"))
     {
       isrWtCorr = 1.0;
       isrWt = 1.0;
     }
   wt=wt*isrWtCorr*isrWt;
   if(s_data.Contains("FastSim_TChiWg_0_400_v17"))
     {
       // xsec=0.11822;
       xsec=0.121;
       wt=wt*xsec/nentries;
     }
   else if(s_data.Contains("FastSim_TChiWg_0_800_v17"))
     {
       // xsec= 0.00461 ;
       xsec= 0.004758 ;
       wt=wt*xsec/nentries;
     }
   else if(s_data.Contains("FastSim_TChiWg_0_1200_v17"))
     {
       // xsec=0.00041 ;
       xsec= 0.000415 ;
       wt=wt*xsec/nentries;
     }
       // {
     //   isrWtCorr = 1.0;
     //   isrWt = 1.0;
     // }


    // cout<<"wt --> "<<wt<<"\t isrWt --> "<<isrWt<<"\t isrWtCorr --> "<<isrWtCorr<<"\t NJetsISR --> "<<NJetsISR<<endl;

    //=================================================================================================

    if(!s_data.Contains("FastSim")){
      if(!(CSCTightHaloFilter==1 && HBHENoiseFilter==1 && HBHEIsoNoiseFilter==1 && eeBadScFilter==1 && EcalDeadCellTriggerPrimitiveFilter==1 && BadChargedCandidateFilter && BadPFMuonFilter && NVtx > 0) ) continue;
    }
   
    //-----------------------------------------cutflows--------------------------------------    
    h_selectBaselineYields_->Fill("No cuts, evt in 35.9/fb",wt);

    h_selectBaselineYields_2->Fill("No cuts, evt in 35.9/fb",wt);
    h_selectBaselineYields_2->Fill("Good #gamma with Pt > 100",wt);
    h_selectBaselineYields_2->Fill("veto electron & Muon",wt);
    h_selectBaselineYields_2->Fill("Iso track",wt);
    h_selectBaselineYields_2->Fill("nJets >= 2",wt);
    h_selectBaselineYields_2->Fill("dPhi1 & dPhi2 >= 0.3",wt);
    h_selectBaselineYields_2->Fill("MET>200",wt);
    h_selectBaselineYields_2->Fill("BTags >= 1",wt);
    h_selectBaselineYields_2->Fill("BTags = 0",wt);

   bool event_passed_old=false, event_passed_new=false;


    TLorentzVector bestPhoton=getBestPhoton();

    if(bestPhoton.Pt()>100)     h_selectBaselineYields_->Fill("Good #gamma with Pt > 100",wt);
    else continue;

    // e & muon veto
    if(s_data.Contains("FastSim")){
    if (Electrons->size() == 0 && Muons->size() == 0 ) h_selectBaselineYields_->Fill("veto electron & Muon",wt);
    else continue;
    }
    if(!s_data.Contains("FastSim") || s_data.Contains("_v17")){
    if (NElectrons == 0 && NMuons == 0 ) h_selectBaselineYields_->Fill("veto electron & Muon",wt);
    else continue;
    }

    // //apply iso track veto
    if(isoElectronTracks==0 && isoMuonTracks ==0 && isoPionTracks==0)
      {
	h_selectBaselineYields_->Fill("Iso track",wt);
      }
    else continue;                                   
    

   //------------------------------------------------tmp 7 Nov -----------------------------------------//
       bool hadJetID=true;
    //----------------------if we are also using HT X Photon triggers------------------------                                                                                                                
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

    TLorentzVector Met;
    Met.SetPtEtaPhiE(MET,0,METPhi,0);
    double mT= 0.0, dPhi_METjet1=5, dPhi_METjet2=5, dPhi_phojet1=5, dPhi_phojet2=5, dPhi_phoMET=5; 
    dPhi_phojet1 = abs(bestPhoton.DeltaPhi(hadJets[0])); 
    dPhi_phojet2 = abs(bestPhoton.DeltaPhi(hadJets[1]));
    dPhi_METjet1 = abs(Met.DeltaPhi(hadJets[0])); 
    dPhi_METjet2 = abs(Met.DeltaPhi(hadJets[1]));
    dPhi_phoMET = abs(bestPhoton.DeltaPhi(Met));
    double mTPhoMET=sqrt(2*(bestPhoton.Pt())*MET*(1-cos(DeltaPhi(METPhi,bestPhoton.Phi()))));

    //----------------- WITHOUT ANY CUT ---------------------//
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
    
    //===============Ak8 Jets ======================
    // bool hadAK8JetID =true;
    // int minDR4indx=-100;//photonMatchingJetIndx=-100,nHadJets=0;
    // double minDR4=99999;
    // vector<TLorentzVector> hadAK8Jets;
    // for(int i=0;i<JetsAK8->size();i++)
    //   if( ((*JetsAK8)[i].Pt() > 30.0) && (abs((*JetsAK8)[i].Eta()) <= 2.4) ){
    //     double dR4=bestPhoton.DeltaR((*Jets)[i]);
    //     if(dR4<minDR4){minDR4=dR4;minDR4indx=i;}
    //   }

    // for(int i=0;i<JetsAK8->size();i++)
    //   if( ((*JetsAK8)[i].Pt() > 30.0) && (abs((*JetsAK8)[i].Eta()) <= 2.4) ){
    //     if( !(minDR4 < 0.3 && i==minDR4indx) ){
    //       hadAK8Jets.push_back((*JetsAK8)[i]);
    //       if(hadAK8JetID) hadAK8JetID=(*JetsAK8_ID)[i];
    //     }
    //   }
    // 	// cout<<jentry<<": "<<i<<"  JetsAK8->size()  --> "<<JetsAK8->size()<<"   (*JetsAK8)[i].Pt() "<<(*JetsAK8)[i].Pt()<<endl;
    // // for(int i=0;i<hadAK8Jets.size();i++)
    // //   cout<<jentry<<": "<<i<<" hadAK8Jets.size()  --> "<<hadAK8Jets.size()<<"   hadAK8Jets[i].Pt() --> "<<hadAK8Jets[i].Pt()<<endl;

    // //======================= Boosted W from TChiWg sample having Mnlsp = 800 GeV ================================================
    // for(int i=0;i<GenParticles->size();i++){
    //   if((abs((*GenParticles_PdgId)[i])==24) && (abs((*GenParticles_ParentId)[i])>1000020) )
    // 	{//      if( (abs((*GenParticles_ParentId)[i])>1000020 && (abs((*GenParticles_ParentId)[i])<1000025 &&  (abs((*GenParticles_Status)[i])==1))))
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

      



    //-----------------optional cuts from trigger studies ---------------------//

    // bool nj_2toinf=false;

    //    Minimum 2 jets (photon is not counted as jet)
    if( nHadJets >= 2 )
    // if( nHadJets > 1  )
      {
	// nj_2toinf=true;
    	h_selectBaselineYields_->Fill("nJets >= 2",wt);
      }
    else if(nHadJets == 1)
      {
	Met.SetPtEtaPhiE(MET,0,METPhi,0); 
	dPhi_phojet1 = abs(bestPhoton.DeltaPhi(hadJets[0])); 
	dPhi_METjet1 = abs(Met.DeltaPhi(hadJets[0])); 
	dPhi_phoMET = abs(bestPhoton.DeltaPhi(Met));
	if(dPhi_METjet1 >= 0.3 && dPhi_METjet2 >= 0.3 )
	  {
	    if(MET>200)
	      {
		h_MET_nj1->Fill(MET,wt);
		h_METvBin_nj1->Fill(MET,wt);
		h_METvBin1_nj1->Fill(MET,wt);
		h_METvBin2_nj1->Fill(MET,wt);
		h_intLumi->Fill(lumiInfb,wt);
	      }
	  }
	continue;
      }
    else
      continue;
    // TLorentzVector Met;
    Met.SetPtEtaPhiE(MET,0,METPhi,0);
    dPhi_phojet1 = abs(bestPhoton.DeltaPhi(hadJets[0])); 
    dPhi_phojet2 = abs(bestPhoton.DeltaPhi(hadJets[1]));
    dPhi_METjet1 = abs(Met.DeltaPhi(hadJets[0])); 
    dPhi_METjet2 = abs(Met.DeltaPhi(hadJets[1]));
    dPhi_phoMET = abs(bestPhoton.DeltaPhi(Met));
    //Minimum dPhi cut between MET and leading two jets
    // if(nj_2toinf=true)
    //   {

    if(dPhi_METjet1 >= 0.3 && dPhi_METjet2 >= 0.3 )
      {
	h_selectBaselineYields_->Fill("dPhi1 & dPhi2 >= 0.3",wt);
      }
    else continue;

    //   }
    // else
    //   continue;

    //Minimum MET
    if( MET>200)  
      {
	h_selectBaselineYields_->Fill("MET>200",wt);
      }
    else continue;
    //Minimum Btags
    if (BTags >=1)	h_selectBaselineYields_->Fill("BTags >= 1",wt);

    else if (BTags ==0) h_selectBaselineYields_->Fill("BTags = 0",wt);

 
   
  
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
   
    if( nHadJets >= 2 && nHadJets <=  4 )
      {
	h_MET_nj2to4->Fill(MET,wt);
	h_METvBin_nj2to4->Fill(MET,wt);
	h_METvBin1_nj2to4->Fill(MET,wt);
	h_METvBin2_nj2to4->Fill(MET,wt);
      }

    if( nHadJets >= 5 && nHadJets <=  7 )
      {
	h_MET_nj5to7->Fill(MET,wt);
	h_METvBin_nj5to7->Fill(MET,wt);
	h_METvBin1_nj5to7->Fill(MET,wt);
	h_METvBin2_nj5to7->Fill(MET,wt);
      }

    if( nHadJets >= 8 )
      {
	h_MET_nj8toinf->Fill(MET,wt);
	h_METvBin_nj8toinf->Fill(MET,wt);
	h_METvBin1_nj8toinf->Fill(MET,wt);
	h_METvBin2_nj8toinf->Fill(MET,wt);
      }

    //-----------------------------------------------------------------------------------------

    
   
    
    h_intLumi->Fill(lumiInfb,wt);
 //    // h_NParticles->Fill(Particle_size);
    
    
    }// loop over entries
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
