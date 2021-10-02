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

bool applISRWtsTottbar = true;
bool applyISRWtsFastSim = true;
bool apply_METfilters=true;
bool apply_L1=true;
bool apply_HEMveto=true;
bool apply_PU=true;
bool apply_pixelveto=false;
bool highdphi=true;
bool applytrg=true;
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
  int EW_evtSurvived=0;
  int EW_evtSurvived_SB=0;  
  int EW_evtSurvived_htag=0;  
  int EW_evtSurvived_wtag=0;  
  int SP_evtSurvived=0;  
  int EW_noSB_evtSurvived=0;

  //  bool applISRWtsTottbar = 1;

  TFile *pufile;
  if(s_data.Contains("2016")){
    pufile = TFile::Open("PileupHistograms_2016_69mb_pm5.root","READ");
    cout<<"Applying L1 prefiring prob.? "<<apply_L1<<endl;
  }
  if(s_data.Contains("2017")){
    pufile = TFile::Open("PileupHistograms_2017_69mb_pm5.root","READ");
    cout<<"Applying L1 prefiring prob.? "<<apply_L1<<endl;
  }
  if(s_data.Contains("2018")){
    pufile = TFile::Open("PileupHistograms_2018_69mb_pm5.root","READ");
    cout<<"Applying HEM veto? "<<apply_HEMveto<<endl;
  }

  TH1* puhist = (TH1*)pufile->Get("pu_weights_down");
  cout<<"applying PU weights."<<endl
      <<"applying ISR weights to ttbar? "<<applISRWtsTottbar<<endl;

    //set file for getting ISR wts for signal
  TFile *fISR;  TH2D *h2_isrWtCorr;
  if(s_data.Contains("FastSim") && s_data.Contains("2016") && applyISRWtsFastSim){
    if(s_data.Contains("T5bbbbZg")){ fISR = new TFile("T5bbbbZg_MassScan.root");
    }
    else if(s_data.Contains("T5qqqqHg")){ fISR = new TFile("T5qqqqHg_Summer16v3_MassScan.root");
    }
    else if(s_data.Contains("TChiWG")) fISR = new TFile("TChiWG_MassScan.root");
    else if(s_data.Contains("TChiNG")) fISR = new TFile("TChiNG_MassScan.root");
    else if(s_data.Contains("T5tttt")) fISR = new TFile("T5ttttZG_Summer16v3Fast_MassScan.root");
    //    else if(s_data.Contains("T5qqqq")) fISR = new TFile("T5qqqqHg_MassScan.root");
    else if(s_data.Contains("T6tt")) fISR = new TFile("T6ttZG_Summer16v3_MassScan.root");

    h2_isrWtCorr = (TH2D*)fISR->Get("Nevts_NoISRWt");
  
    h2_isrWtCorr->Divide((TH2D*)fISR->Get("Nevts_ISRWt"));
  }
  // if(s_data.Contains("FastSim_T5bbbbZg_2017") && applyISRWtsFastSim){
  //     fISR = new TFile("T5bbbbZG_Fall17Fast.SMS-T5bbbbZg_TuneCP2_13TeV-madgraphMLM-pythia8_job0.root");
  //     cout<<"2017"<<endl;
  // }
  // if(s_data.Contains("FastSim_T5bbbbZg_2018") && applyISRWtsFastSim){
  //   fISR = new TFile("T5bbbbZG_Autumn18Fast.SMS-T5bbbbZg_TuneCP2_13TeV-madgraphMLM-pythia8_job0.root");
  // }

  

  bool v17=true, v12=false;
  bool EWselection=true;

  int a=0, b=0, c=0, genphomatch_before=0,genphomatch_after=0;
  for (Long64_t jentry=0; jentry<nentries;jentry++) {
    
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
    bool genphocheck=false;
    double p0=-100, p1=-100, p2=-100;
    if(!s_data.Contains("data")){
      if(s_data.Contains("2016")) {lumiInfb=35.9; p0=1.66539e+02; p1=8.13254e+01; p2=9.71152e-01; deepCSVvalue = 0.6321;}
      if(s_data.Contains("2017")) {lumiInfb=41.59; p0=1.86744e+02; p1=6.74978e+01; p2=9.65333e-01;deepCSVvalue = 0.4941;}
      if(s_data.Contains("2018")) {lumiInfb=59.74; p0=1.89868e+02; p1=6.60434e+01; p2=9.79618e-01;deepCSVvalue = 0.4184;}
      if(s_data.Contains("FastSim") && s_data.Contains("2016")) {lumiInfb=137.19;deepCSVvalue = 0.6321;}
    //    if(s_data=="ZG_v17_2017") lumiInfb=77.49;
    }
    if(s_data.Contains("data"))
      {
        if(s_data.Contains("2016")) {deepCSVvalue = 0.6321;}
        if(s_data.Contains("2017")) {deepCSVvalue = 0.4941;}
        if(s_data.Contains("2018")) {deepCSVvalue = 0.4184;}
      }

    //temperory xsec fix
    if(s_data.Contains("FastSim") && s_data.Contains("T6ttZg") )
      { 
	if(SusyMotherMass== 1200) CrossSection =  0.00159844;
	if(SusyMotherMass==  1400 ) CrossSection =  0.00046194;
	if(SusyMotherMass==  1700 ) CrossSection =  8.07774e-05;

	Weight=CrossSection/nentries;
      } 


    if(apply_PU)
      {
	if((s_data.Contains("v17_2016") || s_data.Contains("v17_2017") ) && apply_L1){
	  wt=Weight*1000.0*NonPrefiringProb*lumiInfb*(puhist->GetBinContent(puhist->GetXaxis()->FindBin(min(TrueNumInteractions,puhist->GetBinLowEdge(puhist->GetNbinsX()+1)))));
	  h_nEvts->Fill(1,wt);
	}

	if(s_data.Contains("v17_2018") && apply_HEMveto){
	  wt=Weight*1000.0*lumiInfb*(puhist->GetBinContent(puhist->GetXaxis()->FindBin(min(TrueNumInteractions,puhist->GetBinLowEdge(puhist->GetNbinsX()+1)))));
	  h_nEvts->Fill(1,wt);
	}
	
	bool HEMaffected = false;
	//////-======== HEM issue ==================//////////////                                                                                                       
	if(s_data.Contains("2018") && apply_HEMveto){
	  for(int i=0; i<Electrons->size();i++)
	    if((*Electrons)[i].Pt() >30 && (*Electrons)[i].Eta() > -3.0 && (*Electrons)[i].Eta() < -1.4 && (*Electrons)[i].Phi() > -1.57 && (*Electrons)[i].Phi() < -0.87) {HEMaffected = true; break;}
	  for(int i=0; i<Jets->size();i++)
	    if((*Jets)[i].Pt() > 30 && (*Jets)[i].Eta() > -3.2 && (*Jets)[i].Eta() < -1.2 && (*Jets)[i].Phi() > -1.77 && (*Jets)[i].Phi() < -0.67 && DeltaPhi((*Jets)[i].Pt(),METPhi)<0.5) {HEMaffected = true; break;}
	  if(HEMaffected == true) continue;
	}
	
	if(!apply_HEMveto && !apply_L1 && !s_data.Contains("FastSim"))  wt=Weight*1000.0*lumiInfb*(puhist->GetBinContent(puhist->GetXaxis()->FindBin(min(TrueNumInteractions,puhist->GetBinLowEdge(puhist->GetNbinsX()+1)))));
        if(apply_HEMveto && apply_L1 && s_data.Contains("FastSim"))  wt=Weight*1000.0*lumiInfb;

      }

    if(!apply_PU)    wt=Weight*1000.0*lumiInfb;//*(puhist->GetBinContent(puhist->GetXaxis()->FindBin(min(TrueNumInteractions,puhist->GetBinLowEdge(puhist->GetNbinsX()+1)))));
    h_nEvts->Fill(1,wt);

    if(s_data.Contains("data")) wt=1;
    // if(PFCaloMETRatio >=  5) continue;

    h_selectBaselineYields_->Fill("No cuts, evt in 35.9/fb",wt);

    bool tighte_trgpass=true;
    if(s_data.Contains("data") && applytrg)
      {
	if(TriggerPass->size()!=148) continue;
        if((*TriggerPass)[124]==1 || (*TriggerPass)[110]==1 || (*TriggerPass)[112]==1 || (*TriggerPass)[116]==1 || (*TriggerPass)[118]==1 || (*TriggerPass)[120]==1 ) tighte_trgpass=true;
        else tighte_trgpass=false;

        if(tighte_trgpass==false)  continue;
      }

    if(!s_data.Contains("data") && applytrg)
      {
	//        if(MET>200 && MET<300)
        //  wt=wt*0.9;
	// else wt=wt*0.97;

	wt = wt * (((TMath::Erf((MET - p0)/p1)+1)/2.0)*p2);
      }




    if(!s_data.Contains("FastSim") && apply_METfilters){
      if(!(CSCTightHaloFilter==1 && HBHENoiseFilter==1 && HBHEIsoNoiseFilter==1 && eeBadScFilter==1 && EcalDeadCellTriggerPrimitiveFilter==1 && BadPFMuonFilter && NVtx > 0) ) continue;
    }
   
    //-----------------------------------------cutflows--------------------------------------    

    h_selectBaselineYields_->Fill("After MET filters",wt);

    h_selectBaselineYields_2->Fill("No cuts, evt in 35.9/fb",wt);
    h_selectBaselineYields_2->Fill("Good #gamma with Pt > 100",wt);
    h_selectBaselineYields_2->Fill("veto electron & Muon",wt);
    h_selectBaselineYields_2->Fill("Iso track",wt);
    h_selectBaselineYields_2->Fill("MET>100",wt);
    h_selectBaselineYields_2->Fill("nJets >= 2",wt);
    h_selectBaselineYields_2->Fill("dPhi1 & dPhi2 >= 0.3",wt);
    //    h_selectBaselineYields_2->Fill("MET>200",wt);
    h_selectBaselineYields_2->Fill("BTags >= 1",wt);
    h_selectBaselineYields_2->Fill("BTags = 0",wt);
    h_selectBaselineYields_2->Fill("ST & photon pt selec",wt);
    // h_selectBaselineYields_2->Fill("MET & photon pt selec",wt);


   bool event_passed_old=false, event_passed_new=false;

   //============== Baseline Selections====================//
   if(s_data.Contains("TTJets2"))
     {//cout<<" correct "<<endl;                                                                                                                                           
       if ( madHT>600) continue;
     }
   h_selectBaselineYields_->Fill("madHT>600",wt);

   TLorentzVector bestPhoton=getBestPhoton();


   //================Prompt photon from TTG ZG WG Gjets=========================================//
    if(bestPhotonIndxAmongPhotons<0) continue;
    bool bestPhoHasPxlSeed=true;
    if((*Photons_hasPixelSeed)[bestPhotonIndxAmongPhotons]<0.001) bestPhoHasPxlSeed=false;
    if( bestPhoHasPxlSeed ) continue;
    bool eMatchedG=check_eMatchedtoGamma();
    bool noFakeJet = true;


    if(genphocheck){
      double gendRLepPho = getGendRLepPho();
      if(s_data.Contains("TTG") || s_data.Contains("WG") || s_data.Contains("ZG")){
	if(jentry==0){cout<<"**********processing "<<s_data<<" with prompt Gen photon"<<endl;}
      }//Gen prompt
      else if(s_data.Contains("WJets")){
	if(hasGenPromptPhoton && gendRLepPho > 0.5 && madMinPhotonDeltaR > 0.5) continue;
	if(jentry<3) cout<<"Non-Prompt, dR(pho,q/g/lep) < 0.5 ";
      }
      else if((s_data=="gennonprompt") || s_data.Contains("TTJets") || s_data.Contains("SingleTop") || s_data.Contains("ZJets")|| s_data.Contains("TTJets_v17") || s_data.Contains("TTJets2_v17") || s_data.Contains("ZJets_v12")){
	if(hasGenPromptPhoton && gendRLepPho > 0.3 && madMinPhotonDeltaR > 0.3) continue;
	if(jentry<3) cout<<"Non-Prompt, dR(pho,q/g/lep) < 0.3 ";
      }//Gen non-prompt
      else if(s_data=="QCD"||s_data.Contains("QCD")){
	if(jentry==0){cout<<"**********processing "<<s_data<<" w/o prompt gen photon"<<endl;}
	//      if(hasGenPromptPhoton && madMinDeltaRStatus==1 && madMinPhotonDeltaR > 0.4) continue;
	if(!((*Photons_nonPrompt)[bestPhotonIndxAmongPhotons]) && madMinDeltaRStatus==1 && madMinPhotonDeltaR > 0.4) continue;
      }
      else if(s_data.Contains("GJets")){
	if(jentry==0){cout<<"**********processing "<<s_data<<" with prompt Gen photon"<<endl;}
      //      if(!hasGenPromptPhoton) continue;
	if((*Photons_nonPrompt)[bestPhotonIndxAmongPhotons]) continue;
      }
    }
    if(!genphocheck && !s_data.Contains("data"))
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
	if(hasGenPromptPhoton && (s_data.Contains("GJets")))
	  {
	    if(!(madMinPhotonDeltaR>0.4)) continue;

	  }
	if(hasGenPromptPhoton && (s_data.Contains("QCD")))
	  {
	    if((madMinPhotonDeltaR>0.4 && hasGenPromptPhoton)) continue;
	  }

	if(hasGenPromptPhoton && (s_data.Contains("ZG")))
	  {
	    if(!(madMinPhotonDeltaR>0.5)) continue;
	  }
	if(hasGenPromptPhoton && (s_data.Contains("ZJets")))
	  {
	    if(!(madMinPhotonDeltaR<=0.5)) continue;
	  }
        genphomatch_after++;
	h_selectBaselineYields_->Fill("Gen Prompt photon check ",wt);
  
      }
    if(s_data.Contains("FastSim")){
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
	//	cout<<"wt before ISR reweighting from "<<s_data<<" signals --> "<<wt<<endl;
	double isrWt = 0,isrWtCorr = h2_isrWtCorr->GetBinContent(h2_isrWtCorr->GetXaxis()->FindBin(SusyMotherMass),h2_isrWtCorr->GetYaxis()->FindBin(SusyLSPMass));
	vector<double> isrwt_arr={1., 0.920, 0.821, 0.715, 0.662, 0.561, 0.511};
	if(NJetsISR>=6) isrWt = isrwt_arr[6];
	else isrWt = isrwt_arr[NJetsISR];
	wt = wt*isrWt*isrWtCorr;
	//       cout<<"wt from "<<s_data<<" signals --> "<<wt<<"\t isrWt --> "<<isrWt<<"\t isrWtCorr --> "<<isrWtCorr<<"\t NJetsISR --> "<<NJetsISR<<endl;
      }
    }


   
    if(applISRWtsTottbar && (s_data.Contains("TTJets")||s_data.Contains("TTJets_v17")||s_data.Contains("TTJets2_v17"))){
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
    if(v12){
      if (Electrons->size() == 0 && Muons->size() == 0 ) h_selectBaselineYields_->Fill("veto electron & Muon",wt);
       else continue;
     }
    else if(v17) {
    if (NElectrons == 0 && NMuons == 0 ) h_selectBaselineYields_->Fill("veto electron & Muon",wt);
    else continue;
     }
    // //apply iso track veto
    if(isoElectronTracks==0 && isoMuonTracks ==0 && isoPionTracks==0)
      {
	h_selectBaselineYields_->Fill("Iso track",wt);
      }
    else continue;                                   


    //========= hadjet -> removing jets which are matched with photon within mindr 0.3 =====//
    bool hadJetID=false;
 
    int minDRindx=-100,photonMatchingJetIndx=-100,nHadJets=0;
    double minDR=99999,ST=0;
    vector<TLorentzVector> hadJets;
    double nbjets=0;
    int bJet1Idx = -1;
    vector<TLorentzVector> nonbjets,bjets;

    for(int i=0;i<Jets->size();i++){
      if( ((*Jets)[i].Pt() > 30.0) && (abs((*Jets)[i].Eta()) <= 2.4) ){
	{
	  double dR=bestPhoton.DeltaR((*Jets)[i]);	  
	  if(dR<minDR){minDR=dR;minDRindx=i;}
	}	
      }
    }
    
    for(int i=0;i<Jets->size();i++){
      if( ((*Jets)[i].Pt() > 30.0) && (abs((*Jets)[i].Eta()) <= 2.4) ){
	if( !(minDR < 0.3 && i==minDRindx) ){
	    {
	      hadJetID=(*Jets_ID)[i];
	      if(hadJetID){
		hadJets.push_back((*Jets)[i]);
                if((*Jets_bJetTagDeepCSVBvsAll)[i] > deepCSVvalue){
                  bjets.push_back((*Jets)[i]); bJet1Idx = i;}
	      }
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
    for(int i=0;i<bjets.size();i++)
      if( (abs(bjets[i].Eta()) < 2.4) ){nbjets++;}

    if( minDR<0.3 ){
      ST=ST+bestPhoton.Pt();
    }
    sortTLorVec(&hadJets);

    //===============================================================//
     //cout<<"=================================================="<<endl;
    //-----------------optional cuts from trigger studies ---------------------//

    //Minimum MET
    if( MET>100)  
      {
    	h_selectBaselineYields_->Fill("MET>100",wt);
      }
    else continue;

    //       Minimum 2 jets (photon is not counted as jet)
    if( nHadJets >= 2 )
      {
    	h_selectBaselineYields_->Fill("nJets >= 2",wt);
      }

    else
      {
      // cout<<"nhadjet --> "<<nHadJets<<endl; 
      continue;
      }
    // TLorentzVector Met;
 
    TLorentzVector Met;
    Met.SetPtEtaPhiE(MET,0,METPhi,0);
    double mT= 0.0, dPhi_METjet1=5, dPhi_METjet2=5, dPhi_phojet1=5, dPhi_phojet2=5, dPhi_phoMET=5;
 
    Met.SetPtEtaPhiE(MET,0,METPhi,0);
    double mindphi=1000;

    dPhi_phojet1 = abs(bestPhoton.DeltaPhi(hadJets[0])); 
    dPhi_phojet2 = abs(bestPhoton.DeltaPhi(hadJets[1]));
    dPhi_phoMET = abs(bestPhoton.DeltaPhi(Met));
    dPhi_METjet1 = abs(DeltaPhi(METPhi,(hadJets)[0].Phi())); 
    mindphi=dPhi_METjet1; 
    dPhi_METjet2 = abs(DeltaPhi(METPhi,(hadJets)[1].Phi()));
    if(dPhi_METjet2<mindphi) mindphi=dPhi_METjet2;

    //Minimum dPhi cut between MET and leading two jets
    //    if(dPhi_METjet1 > 0.3 && dPhi_METjet2 > 0.3 )
    //  {
    //	h_selectBaselineYields_->Fill("dPhi1 & dPhi2 >= 0.3",wt);
    //  }
    //    else continue;


    
    if(photonMatchingJetIndx>=0 && ((*Jets)[photonMatchingJetIndx].Pt())/(bestPhoton.Pt()) < 1.0) continue;
    if(photonMatchingJetIndx<0) continue;
    //    if(eMatchedG > 0) continue;				     

    // //============== New Trigger selections ================                                                                                               
    if( (ST <= 300) ) continue;
    h_selectBaselineYields_->Fill("ST>300 GeV",wt);

    if( !((MET>200 && bestPhoton.Pt()>100) ) )continue;
    else
     h_selectBaselineYields_->Fill("MET>200 & photon pt>100 selec",wt);
    bool process= false;

    if(highdphi)
      {
	if(!bestPhoHasPxlSeed && bestPhoton.Pt()>=100 && ST>300 && nHadJets>=2 && MET > 200 && dPhi_METjet1 > 0.3 && dPhi_METjet2 > 0.3 && NElectrons==0 && NMuons==0 &&((isoElectronTracks==0)&&(isoMuonTracks==0)&&(isoPionTracks==0)))
	  process =true;
	if(s_data.Contains("data") && !bestPhoHasPxlSeed && bestPhoton.Pt()>=100 && ST>300 && nHadJets>=2 && MET > 300 && dPhi_METjet1 > 0.3 && dPhi_METjet2> 0.3 && NElectrons==0 && NMuons==0 &&((isoElectronTracks==0)&&(isoMuonTracks==0)&&(isoPionTracks==0)))
	 process =false;
	//if(!bestPhoHasPxlSeed && bestPhoton.Pt()>=100 && ST>300 && nHadJets>=2 && MET > 200 && MET<=300 && dPhi_METjet1 > 0.3 && dPhi_METjet2> 0.3 && NElectrons==0 && NMuons==0 &&((isoElectronTracks==0)&&(isoMuonTracks==0)&&(isoPionTracks==0)))
	// process =true;
	//else
	// process =false; 
      }
    if(!highdphi)
      { 
        if(!bestPhoHasPxlSeed && bestPhoton.Pt()>=100 && ST>300 && nHadJets>=2 && MET > 300 && !(dPhi_METjet1 > 0.3 && dPhi_METjet2> 0.3) && NElectrons==0 && NMuons==0 &&((isoElectronTracks==0)&&(isoMuonTracks==0)&&(isoPionTracks==0)))
          process =true;
	else
          process =false;
      
      }
    //     else continue;
    ////////    ============== Old Trigger selections ================                                                          
    //    if( (ST <= 500) ) continue;                                                                                                //    if( !((ST>800 && bestPhoton.Pt()>100) || (bestPhoton.Pt()>190)) ) continue;                                                //   else                                                                                                                        //    h_selectBaselineYields_->Fill("ST & photon pt selec",wt);                                                                  //    bool process= false;                                                                                                       // if(!bestPhoHasPxlSeed && bestPhoton.Pt()>=100 && ST>300 && nHadJets>=2 && MET > 100 && dPhi_METjet1 > 0.3 && dPhi_METjet2 > 0.3 && NElectrons==0 && NMuons==0  &&((isoElectronTracks==0)&&(isoMuonTracks==0)&&(isoPionTracks==0))){                            //   process =true;                                                                                                              // evtSurvived++;                                                                                                            	 //         h_selectBaselineYields_->Fill("Before Pre-Selections",wt);                                                       
    ///////==============================================

     if (MET>300 )
       h_selectBaselineYields_->Fill("MET > 300",wt);
     //     else continue;
    //Minimum Btags                                                                                                                                                         
     if (BTags >=1)
       {
	 h_selectBaselineYields_->Fill("BTags >= 1",wt);
       }
     else if (BTags ==0) h_selectBaselineYields_->Fill("BTags = 0",wt);

     if(s_data.Contains("FastSim")){
      hadJetID = true;
      if(!noFakeJet) continue;
    }


    //============== EWkino selections ===============

   
    //===============Ak8 Jets =====================
    bool hadAK8JetID =false;
    int minDR4indx=-100,minDR5indx , Ak8ID=-100;//photonMatchingJetIndx=-100,nHadJets=0;
    double minDR4=99999,minDR5;
    vector<TLorentzVector> hadAK8Jets;
    vector<TLorentzVector> hadAK8Jets_matchedW;
    vector<double> hadAK8Mass, hadAK8Mass_matchedW;
    double Ak8Mass,max=0.0,Ak8Mass1,hadAk8Pt;
    for(int i=0;i<JetsAK8->size();i++)
      if( ((*JetsAK8)[i].Pt() > 30.0) && (abs((*JetsAK8)[i].Eta()) <= 2.4) ){
	double dR4=bestPhoton.DeltaR((*JetsAK8)[i]);
	if(dR4<minDR4){minDR4=dR4;minDR4indx=i;}
      }
  
    for(int i=0;i<JetsAK8->size();i++)
      if( ((*JetsAK8)[i].Pt() > 30.0) && (abs((*JetsAK8)[i].Eta()) <= 2.4) ){
	if( !(minDR4 < 0.3 && i==minDR4indx) ){
	  hadAK8JetID=(*JetsAK8_ID)[i];
	  if(hadAK8JetID){          
	    hadAK8Jets.push_back((*JetsAK8)[i]);
	    hadAK8Mass.push_back((*JetsAK8_softDropMass)[i]);
	  }
	}
      }

    //   cout<<"Had Ak8"<<hadAK8Jets.size()<<endl;   

    if(hadAK8Jets.size() == 0)
      {
	Ak8Mass=0;
       	hadAk8Pt=0;
      }
    else if (hadAK8Jets.size() != 0)
      {
	Ak8Mass=hadAK8Mass[0];
	hadAk8Pt=hadAK8Jets[0].Pt();
      }
  //==============Ak8 EW selection=====================//
    if(EWselection) 
      {
	EWselec=false;
	EWselec_Htag=false;
        EWselec_Wtag=false;
	EWselec_SB1=false;
	EWselec_SB2=false;
	if ((Ak8Mass < 105 && Ak8Mass >= 65))
	  {
	    EWselec=true;
	    EWselec_Wtag=true;
	    EWselec_Htag=false;
	    EWselec_SB1=false;
	    EWselec_SB2=false;
	  }

	else if ((Ak8Mass < 140 && Ak8Mass >= 105))
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
	  
	if(hadJets.size()<=6)
	  {     
	    EWselec1=true;
	  }
	else 
	  {
	    EWselec1=false;
	  } 
	   
      }

    if (process){

      evtSurvived++;
      h_BestPhotonPt->Fill(bestPhoton.Pt(),wt);    
      h_MET->Fill(MET,wt);
      h_METvBin->Fill(MET,wt);
      h_METvBin1->Fill(MET,wt);
      h_METvBin2->Fill(MET,wt);
      h_nJets->Fill(nHadJets,wt);
      h_ST->Fill(ST,wt);
      h_BTags->Fill(nbjets,wt);
      //      h_mTPhoMET->Fill(mTPhoMET,wt); 
      h_dPhi_METjet1->Fill(dPhi_METjet1,wt);
      h_dPhi_METjet2->Fill(dPhi_METjet2,wt);
      h_dPhi_phojet1->Fill(dPhi_phojet1,wt);
      h_dPhi_phojet2->Fill(dPhi_phojet2,wt);
      h_dPhi_phoMET->Fill(dPhi_phoMET,wt);
      h2_PtPhotonvsMET->Fill(bestPhoton.Pt(),MET,wt);
      h_PhovBin->Fill(bestPhoton.Pt(),wt);
      h_PhovBin1->Fill(bestPhoton.Pt(),wt);
      h_PhovBin2->Fill(bestPhoton.Pt(),wt);
      h_mindphi1dphi2->Fill(mindphi,wt);
      //      }

      h_hadAk8Mass->Fill(Ak8Mass,wt);
      h_hadAk8Mass_vBin->Fill(Ak8Mass,wt);
      int sBin7 = getBinNoV7(nHadJets);
      h_SBins_v7_CD->Fill(sBin7,wt);
      int sBin6 = getBinNoV6(nHadJets);
      h_SBins_v6_CD->Fill(sBin6,wt);
      int sBin6_50bin= getBinNoV6_EWplusSP_CR(EWselec,EWselec1 ,EWselec_Htag,EWselec_Wtag,nHadJets,nbjets);
      h_SBins_v6_CD_EW_50bin->Fill(sBin6_50bin,wt);


      if (process && EWselection && EWselec)                
	{
	    
	  h_hadAk8Mass_Ak8jet0_EW->Fill(Ak8Mass,wt);
	  h_hadAk8Pt_Ak8jet0_EW->Fill(hadAk8Pt,wt);
	  if((EWselec_Htag && !EWselec_Wtag)||(EWselec_Wtag && !EWselec_Htag)){
	    h_hadAk8Mass_Ak8jet0_EW_noSB->Fill(Ak8Mass,wt);
	    h_hadAk8Pt_Ak8jet0_EW_noSB->Fill(hadAk8Pt,wt);
	  }
	  if(EWselec_SB1 || EWselec_SB2){
	    h_hadAk8Mass_Ak8jet0_EW_SB->Fill(Ak8Mass,wt);
	    h_hadAk8Pt_Ak8jet0_EW_SB->Fill(hadAk8Pt,wt);
	  }
	    
	  h_nHadAk8Jets_nAk8jet_ge1->Fill(hadAK8Jets.size(),wt);
	  h_nHadJets_nAk8jet_ge1->Fill(hadJets.size(),wt);
	  h_BTags_nAk8jet_ge1->Fill(nbjets,wt);

	  if(hadAK8Jets.size() ==1) h_BTags_nAk8jet1->Fill(nbjets,wt);
	  if(hadAK8Jets.size() ==2) h_BTags_nAk8jet2->Fill(nbjets,wt);
	  if(hadAK8Jets.size() ==3) h_BTags_nAk8jet3->Fill(nbjets,wt);
	}


      if (process && EWselection && !EWselec_SB1 && !EWselec_SB2)
	{
	  int sBin6_43bin= getBinNoV6_EWplusSP_SR( EWselec1, EWselec_Htag,EWselec_Wtag,nHadJets);
	  h_SBins_v6_CD_EW_43bin->Fill(sBin6_43bin,wt);
	  ///	  int sBin6_50bin= getBinNoV6_EWplusSP_CR(EWselec,EWselec1 ,EWselec_Htag,EWselec_Wtag,nHadJets);
	  //	  h_SBins_v6_CD_EW_50bin->Fill(sBin6_50bin,wt);

      	}

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
	  h_BTags_EW->Fill(nbjets,wt);
	  h_intLumi_EW->Fill(lumiInfb,wt);
	  h_hadAk8Mass_EW->Fill(Ak8Mass,wt);
	  h_hadAk8Mass_EW_vBin->Fill(Ak8Mass,wt);
	  int sBin7_EW = getBinNoV7(nHadJets);
	  h_SBins_v7_CD_EW->Fill(sBin7_EW,wt);
	  int sBin6_EW = getBinNoV6(nHadJets);
	  h_SBins_v6_CD_EW->Fill(sBin6_EW,wt);

	  if((EWselec_Htag && !EWselec_Wtag)||(EWselec_Wtag && !EWselec_Htag))
	    {
	      int sBin7_14bin= getBinNoV7_EW(EWselec_Htag,EWselec_Wtag);
	      h_SBins_v7_CD_EW_14bin->Fill(sBin7_14bin,wt);
	      int sBin6_14bin= getBinNoV6_EW(EWselec_Htag,EWselec_Wtag);
	      h_SBins_v6_CD_EW_14bin->Fill(sBin6_14bin,wt);

	    }

	  if(EWselec_SB1 || EWselec_SB2)
	    {
	      EW_evtSurvived_SB++; 
	      h_BestPhotonPt_EW_SB->Fill(bestPhoton.Pt(),wt);
	      h_MET_EW_SB->Fill(MET,wt);
	      h_nJets_EW_SB->Fill(nHadJets,wt);
	      h_METvBin_EW_SB_v2->Fill(MET,wt);
	      h_ST_EW_SB->Fill(ST,wt);
	      h_BTags_EW_SB->Fill(nbjets,wt);
	      h_intLumi_EW_SB->Fill(lumiInfb,wt);
	      h_hadAk8Mass_EW_SB->Fill(Ak8Mass,wt);
	    }
	  else  if(!(EWselec_SB1 || EWselec_SB2))
	    {
	      EW_noSB_evtSurvived++;
	      int sBin7_EW_7bin_noSB = getBinNoV7_EW1(EWselec_Wtag);
	      h_SBins_v7_CD_EW_7bin_noSB->Fill(sBin7_EW_7bin_noSB,wt);
	      int sBin6_EW_7bin_noSB = getBinNoV6_EW1(EWselec);
	      h_SBins_v6_CD_EW_7bin_noSB->Fill(sBin6_EW_7bin_noSB,wt);
	      h_BestPhotonPt_EW_noSB->Fill(bestPhoton.Pt(),wt);
	      h_MET_EW_noSB->Fill(MET,wt);
	      h_nJets_EW_noSB->Fill(nHadJets,wt);
	      h_METvBin_EW_noSB_v2->Fill(MET,wt);
	      h_ST_EW_noSB->Fill(ST,wt);
	      h_BTags_EW_noSB->Fill(nbjets,wt);
	      h_intLumi_EW_noSB->Fill(lumiInfb,wt);
	      h_hadAk8Mass_EW_noSB->Fill(Ak8Mass,wt);
	    }

	}


      if(process && EWselection && (EWselec && EWselec1 && EWselec_Htag && !EWselec_Wtag))
	{	//if(process && EWselection && (EWselec1))
	if(!EWselec_SB1 && !EWselec_SB2)
	{ EW_evtSurvived_htag++;
	  h_BestPhotonPt_EW_htag->Fill(bestPhoton.Pt(),wt);    
	  h_MET_EW_htag->Fill(MET,wt);
	  h_nJets_EW_htag->Fill(nHadJets,wt);
	  h_METvBin_EW_htag->Fill(MET,wt);
	  h_METvBin_EW_htag_v1->Fill(MET,wt);
	  h_METvBin_EW_htag_v2->Fill(MET,wt);
	  h_ST_EW_htag->Fill(ST,wt);
	  h_BTags_EW_htag->Fill(nbjets,wt);
	  h_intLumi_EW_htag->Fill(lumiInfb,wt);
	  h_hadAk8Mass_EW_htag->Fill(Ak8Mass,wt);
	  h_hadAk8Mass_EW_htag_vBin->Fill(Ak8Mass,wt);

	  int sBin7_EW_htag = getBinNoV7(nHadJets);
	  h_SBins_v7_CD_EW_htag->Fill(sBin7_EW_htag,wt);
	  int sBin6_EW_htag = getBinNoV6(nHadJets);
	  h_SBins_v6_CD_EW_htag->Fill(sBin6_EW_htag,wt);
	}
	}    

      if(process && EWselection && (EWselec && EWselec1 && EWselec_Wtag && !EWselec_Htag))
	{	//if(process && EWselection && (EWselec1))
      //    if(process && EWselection && (EWselec || EWselec1))
	  // if(EWselec_SB1 || EWselec_SB2)
	{ EW_evtSurvived_wtag++;
	  h_BestPhotonPt_EW_wtag->Fill(bestPhoton.Pt(),wt);    
	  h_MET_EW_wtag->Fill(MET,wt);
	  h_nJets_EW_wtag->Fill(nHadJets,wt);
	  // h_METvBin_EW_wtag->Fill(MET,wt);
	  // h_METvBin_EW_wtag_v1->Fill(MET,wt);
	  h_METvBin_EW_wtag_v2->Fill(MET,wt);
	  h_ST_EW_wtag->Fill(ST,wt);
	  h_BTags_EW_wtag->Fill(nbjets,wt);
	  h_intLumi_EW_wtag->Fill(lumiInfb,wt);
          h_hadAk8Mass_EW_wtag->Fill(Ak8Mass,wt);
	  // int sBin7_EW_wtag = getBinNoV7(nHadJets);
	  //	  h_SBins_v7_CD_EW_wtag->Fill(sBin7_EW_wtag,wt);
	}


	}



       if(process && EWselection && !(EWselec && EWselec1))
	   { SP_evtSurvived++;
	  h_BestPhotonPt_SP->Fill(bestPhoton.Pt(),wt);    
	  h_MET_SP->Fill(MET,wt);
	  h_METvBin_SP->Fill(MET,wt);
	  h_METvBin_SP_v1->Fill(MET,wt);
	  h_METvBin_SP_v2->Fill(MET,wt);
	  //  cout<<"EWselec_Wtag : "<<EWselec_Wtag<<" , EWselec_Htag : "<<EWselec_Htag<<endl;
	  h_nJets_SP->Fill(nHadJets,wt);
	  h_ST_SP->Fill(ST,wt);
	  h_BTags_SP->Fill(nbjets,wt);
	  h_intLumi_SP->Fill(lumiInfb,wt);
	  
	  h_hadAk8Mass_SP->Fill(Ak8Mass,wt);
	  h_hadAk8Mass_SP_vBin->Fill(Ak8Mass,wt);
	  int sBin7_SP = getBinNoV7(nHadJets);
	  h_SBins_v7_CD_SP->Fill(sBin7_SP,wt);
	  int sBin6_SP = getBinNoV6(nHadJets);
	  h_SBins_v6_CD_SP->Fill(sBin6_SP,wt);
	}

	    //===================================================================================        
      //-----------------------------------------------------------------------------------------
      h_intLumi->Fill(lumiInfb,wt);
      //    // h_NParticles->Fill(Particle_size);
    
      //    }
    }       	    
  
    // }loop over if Ewselections
  }   // loop over entries
  //  if(EWselection && EWselec)
//    cout<<"Events Survied with EWselection:"<<EW_evtSurvived<<endl;
//  else   

    cout<<"lumi of "<<s_data<<" : "<<lumiInfb<<endl;
    cout<<"crosssection : "<<CrossSection<<endl;    
    cout<<"Weight : "<<Weight<<endl;
    cout<<"Events Survied : "<<evtSurvived<<endl;
    cout<<"Events Survied in EW selections with W tag: "<<EW_evtSurvived_wtag<<endl;
    cout<<"Events Survied in EW selections with H tag: "<<EW_evtSurvived_htag<<endl;
    cout<<"Events Survied in sidebands for EW selectionns: "<<EW_evtSurvived_SB<<endl;
    cout<<"Events Survied i without EW selections : "<<SP_evtSurvived<<endl;

    cout<<"Events before genprompt photon check condition : "<<genphomatch_before<<endl;
    cout<<"Events after genprompt photon check condition : "<<genphomatch_after<<endl;
    cout<<"b : "<<b<<endl;
    cout<<"c : "<<c<<endl;
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

int AnalyzeLightBSM::getBinNoV7(int nHadJets){
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

int AnalyzeLightBSM::getBinNoV6(int nHadJets){
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


int AnalyzeLightBSM::getBinNoV6_EW(bool EWselec_Htag , bool EWselec_Wtag){
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

int AnalyzeLightBSM::getBinNoV6_EW1(bool EWselec){
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

int AnalyzeLightBSM::getBinNoV7_EW(bool EWselec_Htag , bool EWselec_Wtag){
  int sBin=-100,m_i=0;
  if(EWselec_Wtag && !EWselec_Htag){
    sBin=0;
  }
  else if(!EWselec_Wtag && EWselec_Htag){
    sBin=6;
  }
  if(sBin==0){
    for(int i=0;i<METLowEdge1.size()-1;i++){
      if(METLowEdge1[i]<249.99) continue;
      m_i++;
      if(MET >= METLowEdge1[i] && MET < METLowEdge1[i+1]){ sBin = sBin+m_i;break; }
      else if(MET >= METLowEdge1[METLowEdge1.size()-1])  { sBin = 6         ;break; }
    }
  }
  else if(sBin==6){
    for(int i=0;i<METLowEdge1.size()-1;i++){
      if(METLowEdge1[i]<249.99) continue;
      m_i++;
      if(MET >= METLowEdge1[i] && MET < METLowEdge1[i+1]){ sBin = sBin+m_i;break; }
      else if(MET >= METLowEdge1[METLowEdge1.size()-1])  { sBin = sBin+6   ;break; }
    }
  }
  return sBin;
}

int AnalyzeLightBSM::getBinNoV7_EW1(bool EWselec_wtag){
  int sBin=-100,m_i=0;
  if(EWselec_wtag){
    sBin=0;
  }
  if(sBin==0){
    for(int i=0;i<METLowEdge1.size()-1;i++){
      if(METLowEdge1[i]<249.99) continue;
      m_i++;
      if(MET >= METLowEdge1[i] && MET < METLowEdge1[i+1]){ sBin = sBin+m_i;break; }
      else if(MET >= METLowEdge1[METLowEdge1.size()-1])  { sBin = 6         ;break; }
    }
  }
 
  return sBin;
}

int AnalyzeLightBSM::getBinNoV6_EWplusSP_CR(bool EWselec, bool EWselec1, bool EWselec_Htag , bool EWselec_Wtag,int nHadJets, int nbjets){

  int sBin=-100,m_i=0;

  if(!(EWselec && EWselec1))
    // if(!((EWselec_Wtag && !EWselec_Htag) && EWselec1) && !((!EWselec_Wtag && EWselec_Htag) && EWselec1))
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
    for(int i=0;i<METLowEdge_v2.size()-1;i++){
      if(METLowEdge_v2[i]<199.99) continue;
      m_i++;
      if(MET >= METLowEdge_v2[i] && MET < METLowEdge_v2[i+1]){ sBin = sBin+m_i;break; }
      else if(MET >= METLowEdge_v2[METLowEdge_v2.size()-1])  { sBin = 7         ;break; }
    }
  }

  else if(sBin==7 || sBin==33 || sBin==39){
    for(int i=0;i<METLowEdge_v2_1.size()-1;i++){
      if(METLowEdge_v2_1[i]<199.99) continue;
      m_i++;
      if(MET >= METLowEdge_v2_1[i] && MET < METLowEdge_v2_1[i+1]){ sBin = sBin+m_i;break; }
      else if(MET >= METLowEdge_v2_1[METLowEdge_v2_1.size()-1])  { sBin = sBin+6   ;break; }
      //     else if(MET >= METLowEdge_v2_1[METLowEdge_v2_1.size()-1])  { sBin = 37   ;break; }

    }
  }


  else{
    for(int i=0;i<METLowEdge_v2_2.size()-1;i++){
      if(METLowEdge_v2_2[i]<199.99) continue;
      m_i++;
      if(MET >= METLowEdge_v2_2[i] && MET < METLowEdge_v2_2[i+1]){ sBin = sBin+m_i;break; }
      else if(MET >= METLowEdge_v2_2[METLowEdge_v2_2.size()-1])  { sBin = sBin+5   ;break; }
      // else if(MET >= METLowEdge_v2[METLowEdge_v2.size()-1])  { sBin = 44   ;break; }

   }
  }

  return sBin;
}

 int AnalyzeLightBSM::getBinNoV6_EWplusSP_SR(bool EWselec1, bool EWselec_Htag , bool EWselec_Wtag,int nHadJets){

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

double AnalyzeLightBSM::getGendRLepBestPho(TLorentzVector goodPho){//MC only
  TLorentzVector genPho1,genLep1;
  vector<TLorentzVector> v_genPho1,v_genLep1;
  int leadGenPhoIdx=-100;

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
	  genLep1=(*GenElectrons)[i];
	  v_genLep1.push_back(genLep1);
	}
    }
  for(int i=0 ; i < GenMuons->size(); i++)
    {
      if((*GenMuons)[i].Pt()!=0)
	{
	  genLep1 = ((*GenMuons)[i]);
	  v_genLep1.push_back(genLep1);
	}
    }
  for(int i=0 ; i < GenTaus->size(); i++)
    {
      if((*GenTaus)[i].Pt()!=0)
	{
	  genLep1 = ((*GenTaus)[i]);
	  v_genLep1.push_back(genLep1);
	}
    }

  double mindr=  MinDr(goodPho,v_genLep1);
  if(mindr >= 0) return mindr;
  else 1000;

}
double AnalyzeLightBSM::getGenLep(TLorentzVector bestPhoton){//MC only                                                                                                             
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
