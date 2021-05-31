#define Z_invisible_cxx
#include "Z_invisible.h"
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
#include "btag/BTagCorrector.h"


using namespace std;
bool applISRWtsTottbar=true;
//bool applISRWtsTottbar=false;
bool full_Run2=false;
bool applyE_SF=false;
bool apply_METfilters=true;
bool apply_L1=true;
bool apply_HEMveto=true;
//bool applybTagSFs=true;
bool applybTagSFs=false;
bool do_prediction=true;
bool applyPUwt=true;
//bool elec=false;
bool muon=true;
bool elec=true;
//bool muon=false;
//bool hadj=true;
bool hadj=false;
TString puwt="central";
//TString puwt="up";
int main(int argc, char* argv[])
{

  if (argc < 2) {
    cerr << "Please give 3 arguments " << "runList " << " " << "outputFileName" << " " << "dataset" << endl;
    return -1;
  }
  const char *inputFileList = argv[1];
  const char *outFileName   = argv[2];
  const char *data          = argv[3];

  Z_invisible ana(inputFileList, outFileName, data);
  cout << "dataset " << data << " " << endl;

  ana.EventLoop(data,inputFileList);

  return 0;
}

void Z_invisible::EventLoop(const char *data,const char *inputFileList) {
  if (fChain == 0) return;

  Long64_t nentries = fChain->GetEntriesFast();
  cout << "nentries " << nentries << endl;
  cout << "Analyzing dataset " << data << " " << endl;

  TString s_data=data;
  Long64_t nbytes = 0, nb = 0;
  int decade = 0;
  // if(s_data.Contains("elec_data")) {elec=true,muon=false;}
  // if(s_data.Contains("muon_data")) {elec=false,muon=true;}
  TCanvas *cA = new TCanvas("METEff","Signal efficiency",1500,850);
  int evtSurvived=0;  
  int EW_evtSurvived=0;
  int EW_evtSurvived_SB=0;  
  int EW_evtSurvived_htag=0;  
  int EW_evtSurvived_wtag=0;  
  int SP_evtSurvived=0;  
  int EW_noSB_evtSurvived=0;

  TFile *pufile,*TF,*TF2,*E_SF,*Egamma_SF;
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

  double puWtNom = 1.0, puWtup = 1.0, puWtdown = 1.0;


  TH1D *tf,*tf2;
  TH3D *tf1;//\,*tf_SP,*tf_SP_2,*tf_SP_3;
  TH2F *e_id, *e_iso, *e_SF;

  if(!full_Run2)
    {
      if(s_data.Contains("2016")){
  	TF = TFile::Open("Zinvisible_TF_2016.root","READ");
       	tf=(TH1D*)TF->FindObjectAny("h3");
      }
      if(s_data.Contains("2017")){
  	TF = TFile::Open("Zinvisible_TF_2017.root","READ");
  	tf=(TH1D*)TF->FindObjectAny("h3");
      }
      if(s_data.Contains("2018")){
  	TF = TFile::Open("Zinvisible_TF_2018.root","READ");
  	tf=(TH1D*)TF->FindObjectAny("h3");
      }
    }
  else
    {
      TF = TFile::Open("Zinvisible_TF.root","READ");
      tf=(TH1D*)TF->FindObjectAny("h3");
    }
  
  TH1* puhist ;
  TH1* puhistUp;  
  TH1* puhistDown;

  if(s_data.Contains("v17"))
    {
      puhist     = (TH1*)pufile->Get("pu_weights_central");
      puhistUp   = (TH1*)pufile->Get("pu_weights_up");
      puhistDown = (TH1*)pufile->Get("pu_weights_down");

    
    }
  int fListIndxOld=-1;
  double prob0=-100,prob1=-100;
  double prob2=-100,prob3=-100;
  double total_prob0=0,total_prob1=0;
  double total_prob2=0,total_prob3=0;


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


  bool v17=true, v12=false;
  // bool v17=false, v12=true;
  bool EWselection=true;
  double qmulti=-1,leadjet_qmulti=-1,leadjet_Pt=-1,leadbjet_tag=-1 ,leadbjet_tag1=-1,leadbjet_tag2=-1,leadbjet_tag3=-1,qmulti1=-1,qmulti2=-1,qmulti3=-1;
  int genphomatch_after=0,genphomatch_before=0,remain=0,after_bjetdisc=0;
  int a=0,b=0,c=0,d=0,e=0,f=0,g=0,h=0,met=0,st=0,nbj0=0,nbj1=0,nbj2=0,nbj3=0,lep=0,lep1=0,lep2=0,lep3=0,lep3_v2=0,lep3_v1=0,zwin=0;
  double wt_nbj0=0,wt_nbj1=0,wt_nbj2=0,wt_nbj3=0;
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

    if(!s_data.Contains("data"))
      {
	if(s_data.Contains("2016")) {lumiInfb=35.922;deepCSVvalue = 0.6321;}
	//      if(s_data.Contains("2017")) lumiInfb=27.986;
	if(s_data.Contains("2017")) {lumiInfb=41.529;deepCSVvalue = 0.4941;}
	if(s_data.Contains("2018")) {lumiInfb=59.74;deepCSVvalue = 0.4184;}
	if(s_data.Contains("FastSim") && s_data.Contains("2016")) lumiInfb=137.19;
      }
    if(s_data.Contains("data"))
      {
	if(s_data.Contains("2016")) {deepCSVvalue = 0.6321;}
	if(s_data.Contains("2017")) {deepCSVvalue = 0.4941;}
	if(s_data.Contains("2018")) {deepCSVvalue = 0.4184;}
      }
      
    if(s_data.Contains("data")) wt=1.0;
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


    ///////=======  L1 Prefiring issue ===========/////////
 
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
   }


   if(s_data.Contains("v17_2018")){
      if(puwt=="up") wt=Weight*1000.0*lumiInfb*puWtup; 
      if(puwt=="down") wt=Weight*1000.0*lumiInfb*puWtdown; 
      else wt=Weight*1000.0*lumiInfb*puWtNom;
      h_nEvts->Fill(1,wt);
    }

     bool HEMaffected = false;
    //////-======== HEM issue ==================//////////////
    if(s_data.Contains("2018") && apply_HEMveto){
      for(int i=0; i<Electrons->size();i++)
	{
	  if((*Electrons_passIso)[i]==1 && elec)
	    { 
	      if((*Electrons)[i].Pt() >30 && (*Electrons)[i].Eta() > -3.0 && (*Electrons)[i].Eta() < -1.4 && (*Electrons)[i].Phi() > -1.57 && (*Electrons)[i].Phi() < -0.87) {HEMaffected = true; break;}
	    }      
	}
      for(int i=0; i<Jets->size();i++)
        if((*Jets)[i].Pt() > 30 && (*Jets)[i].Eta() > -3.2 && (*Jets)[i].Eta() < -1.2 && (*Jets)[i].Phi() > -1.77 && (*Jets)[i].Phi() < -0.67 && DeltaPhi((*Jets)[i].Pt(),METPhi)<0.5) {HEMaffected = true; break;}
     if(HEMaffected == true) continue;
   }


    //    if(s_data.Contains("ZGToNuNuG") || s_data.Contains("ZJetsToNuNu") || s_data.Contains("data") )
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
    double corrbtag = 1.0;
    vector<double> prob;
    prob0=0;
    prob1=0;
    prob2=0;
    prob3=0;
    if(applybTagSFs && s_data.Contains("v17")){
      //get prob with SF up 
      prob = btagcorr.GetCorrections(Jets,Jets_hadronFlavor,Jets_HTMask);
      //prob0 = prob[0]; prob1 = prob[1]; prob2 = prob[2]; prob3 = prob[3];
      prob0 = prob[0]; prob1 = prob[1]+prob[2]+prob[3];
      if((prob0+prob1+prob2+prob3)<0.99 || (prob0+prob1+prob2+prob3)>1.01)
	cout<<"prob0+prob1+prob2+prob3 : "<<prob0+prob1+prob2+prob3<<endl;
    }

    //    if(madHT<300) continue;   
    if(!s_data.Contains("FastSim") && apply_METfilters){
     
      // if(!(NVtx > 0 && globalSuperTightHalo2016Filter==1 && HBHENoiseFilter==1 && HBHEIsoNoiseFilter==1 && EcalDeadCellTriggerPrimitiveFilter==1 && BadPFMuonFilter && eeBadScFilter==1 && ecalBadCalibReducedExtraFilter==1 && JetID && JetIDAK8)) continue;
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
      // 	  //  if(s_data.Contains("2016")) //ecalBadCalibReducedExtraFilter = 1;

      // 	  if(!(globalSuperTightHalo2016Filter == 1 && HBHENoiseFilter==1 && HBHEIsoNoiseFilter==1 && EcalDeadCellTriggerPrimitiveFilter == 1 && BadPFMuonFilter  && eeBadScFilter==1 && NVtx>0  && JetID && JetIDAK8 && ecalBadCalibReducedExtraFilter)) continue;
      // 	}
      // if(s_data.Contains("v17"))
      // 	{
      // 	  eeBadScFilter = 1;
      // 	  if(!(globalSuperTightHalo2016Filter == 1 && HBHENoiseFilter==1 && HBHEIsoNoiseFilter==1 && EcalDeadCellTriggerPrimitiveFilter == 1 && BadPFMuonFilter && NVtx>0 && eeBadScFilter==1 && JetID && JetIDAK8 && ecalBadCalibReducedExtraFilter)) continue;
      // 	}

    if(PFCaloMETRatio >=  5) continue;
    if(MET/CaloMET > 2.0) continue;
  
    }
      if(globalSuperTightHalo2016Filter) a++;
    if(HBHENoiseFilter) b++;
    if(HBHEIsoNoiseFilter) c++;
    if(EcalDeadCellTriggerPrimitiveFilter) d++;
    if(ecalBadCalibReducedExtraFilter) e++;
    if(BadPFMuonFilter) f++;
    if(PrimaryVertexFilter) g++;
    if(NVtx>0) h++;
    //    if(wt<0) continue;   

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
   if((*Photons_hasPixelSeed)[bestPhotonIndxAmongPhotons]<0.001) bestPhoHasPxlSeed=false;
   if( bestPhoHasPxlSeed ) continue;
   // bool eMatchedG=check_eMatchedtoGamma(bestPhoton);
   // if(eMatchedG) continue;                                                                                                                                              
   // if(check_muMatchedtoGamma(bestPhoton)) continue;                                                                                                                     

   //=========================================================================//                                                             
   //   //   //photon pt cut                                                                                                                          
   // if(NElectrons != 2 ) continue;
   //   if(NMuons != 0 ) continue;
   if(bestPhoton.Pt()>100)
     {
       h_selectBaselineYields_->Fill("Good #gamma with Pt > 100",wt);
     }
   else continue;
   

      //// Stitching TTJets & TTGamma samples. Similarly WJets & WGamma samples 
      if(!s_data.Contains("data"))
     {
       genphomatch_before++;
       double mindr_Pho_genlep=getGenLep(bestPhoton);
       double mindr_genPho_genlep=getGendRLepPho();

       if(hasGenPromptPhoton && (s_data.Contains("ZGToLLG")))     
	 {
	   if(!(madMinPhotonDeltaR>0.5 && mindr_Pho_genlep>0.5)) continue;
	   h_madminphotonDR->Fill(madMinPhotonDeltaR,wt);
	   h_mindr_ph_lep->Fill(mindr_Pho_genlep,wt);
	   h_mindr_genph_lep->Fill(mindr_genPho_genlep,wt);
 	 }
       if(hasGenPromptPhoton && (s_data.Contains("ZGToNuNuG")))     
	 {
	   if(!(madMinPhotonDeltaR>0.5)) continue;
	   h_madminphotonDR->Fill(madMinPhotonDeltaR,wt);
	   h_mindr_ph_lep->Fill(mindr_Pho_genlep,wt);
	   h_mindr_genph_lep->Fill(mindr_genPho_genlep,wt);
 	 }

       if(hasGenPromptPhoton && (s_data.Contains("DYJetsToLL")))     
	 {
	   if(!(madMinPhotonDeltaR<=0.5 || mindr_Pho_genlep<=0.5) ) continue;
	   h_madminphotonDR->Fill(madMinPhotonDeltaR,wt);
	   h_mindr_ph_lep->Fill(mindr_Pho_genlep,wt);
	   h_mindr_genph_lep->Fill(mindr_genPho_genlep,wt);
	 }
       if(hasGenPromptPhoton && (s_data.Contains("ZJetsToNuNu")))     
	 {
	   if(!(madMinPhotonDeltaR<=0.5)) continue;
	   h_madminphotonDR->Fill(madMinPhotonDeltaR,wt);
	   h_mindr_ph_lep->Fill(mindr_Pho_genlep,wt);
	   h_mindr_genph_lep->Fill(mindr_genPho_genlep,wt);
	 }
       if(jentry<3)
	 if(!hasGenPromptPhoton) cout<<"No gen photon !!!"<<endl;
       //Gen non-prompt
     }
   
   genphomatch_after++;



   bool tighte_trgpass=true;
   bool tightmu_trgpass=true;

   //   if(s_data.Contains("data") && muon) elec=true;

   if(s_data.Contains("data") && elec) 
    {
       if(TriggerPass->size()!=148) continue;
       if((*TriggerPass)[21]==1) tighte_trgpass=true; 
       else if((*TriggerPass)[22]==1) tighte_trgpass=true; 
       else if((*TriggerPass)[23]==1) tighte_trgpass=true; 
       else if((*TriggerPass)[24]==1 || (*TriggerPass)[35]==1 ||(*TriggerPass)[37]==1 ||(*TriggerPass)[33]==1 ||(*TriggerPass)[36]==1 ||(*TriggerPass)[40]==1) tighte_trgpass=true; 
       else if((*TriggerPass)[41]==1 || (*TriggerPass)[32]==1) tighte_trgpass=true;        
       else tighte_trgpass=false;
       //       wt=wt*0.99;
       // if(tighte_trgpass==false)  continue;
       //
       if(NMuons==1 && NElectrons==1) muon=true;
     }

   if(s_data.Contains("data") && muon)
     {
       if(TriggerPass->size()!=148) continue;
       //	 cout<<"No. of Triggers passed : "<<TriggerPass->size()<<endl;
       if((*TriggerPass)[44]==1 || (*TriggerPass)[45]==1 ||(*TriggerPass)[46]==1 ||(*TriggerPass)[47]==1 ||(*TriggerPass)[48]==1 ||(*TriggerPass)[49]==1 ||(*TriggerPass)[50]==1 ||(*TriggerPass)[51]==1 ||(*TriggerPass)[52]==1) tightmu_trgpass=true; 
       // else if((*TriggerPass)[21]==1) tightmu_trgpass=true; 
       // else if((*TriggerPass)[22]==1) tightmu_trgpass=true; 
       // else if((*TriggerPass)[23]==1) tightmu_trgpass=true; 

 
      // else if((*TriggerPass)[24]==1) tightmu_trgpass=true; 
       else if((*TriggerPass)[62]==1) tightmu_trgpass=true; 
       else if((*TriggerPass)[65]==1) tightmu_trgpass=true; 
       else if((*TriggerPass)[66]==1) tightmu_trgpass=true; 
       
       else tightmu_trgpass=false;

     
       //       if(tighte_trgpass==false)  continue;
     }



   TLorentzVector genzvec,zvec,muon1,muon2,elec1,elec2,vlep1,vlep2,vgenl1,vgenl2;
   double zmass= -10,nmuons=0,nelectrons=0;

   if(isoPionTracks!=0) continue;

   if(s_data.Contains("ZGToLLG") || s_data.Contains("DYJetsToLL") || s_data.Contains("data")  || s_data.Contains("WG") || s_data.Contains("TTG")){
     if(jentry<3) cout<<"Processing as Z(G)->LL(G) Decay"<<endl;

     if(NElectrons==2){
       //  if(!(elec && !muon) )continue;
       if(!(elec && tighte_trgpass) )continue;
       if( (NMuons!=0) ) continue;//exactly 0 RECO muons and 2 RECO e                                                   
       if((*Electrons_passIso)[0]!=1 || (*Electrons_passIso)[1]!=1) continue;
       if( (*Electrons_charge)[0] == (*Electrons_charge)[1] ) continue;//opp sign same flav(OSSF)                                
       elec1=(*Electrons)[0];
       elec2=(*Electrons)[1];
       if(elec1.Pt()<20 || elec2.Pt()<20) continue;
       double dR1=bestPhoton.DeltaR((*Electrons)[0]);
       double dR2=bestPhoton.DeltaR((*Electrons)[1]);
       if(!(dR1>0.2 && dR2>0.2)) continue;
       bool eMatchedG=check_eMatchedtoGamma(bestPhoton);                                                                                                                   
       // if(eMatchedG) continue;                                                                                                                                        
       nelectrons=2;
       //zvec =  ((*Electrons)[0] + (*Electrons)[1]);
       zvec =  (elec1 + elec2);
       zmass = zvec.M();
       nmuons=0;
       vlep1=elec1;
       vlep2=elec2;
       lep1++;
     }
     else if(NMuons==2) {
       //if(!(!elec && muon) )continue;       
       //       if(!(!elec && muon && tightmu_trgpass) )continue;
       if(!(muon && tightmu_trgpass) )continue;
       if(NElectrons!=0 ) continue;//exactly 2 RECO muons and 0 RECO e                                                           
       if((*Muons_passIso)[0]!=1 || (*Muons_passIso)[1]!=1) continue;
       if( (*Muons_charge)[0] == (*Muons_charge)[1] ) continue;//opp sign same flav(OSSF)                                        
       muon1=(*Muons)[0];
       muon2=(*Muons)[1];
       if(muon1.Pt()<20 || muon2.Pt()<20) continue;
       double dR1=bestPhoton.DeltaR((*Muons)[0]);
       double dR2=bestPhoton.DeltaR((*Muons)[1]);
       bool muMatchedG=check_muMatchedtoGamma(bestPhoton);                                                                                               
       if(!(dR1>0.2 && dR2>0.2)) continue;
       nmuons=2;
       //zvec =  ((*Muons)[0] + (*Muons)[1]);
       zvec =  muon1 + muon2;
       zmass = zvec.M();
       nelectrons=0;
       vlep1=muon1;
       vlep2=muon2;
       lep2++;
     }

     else if(NMuons==1 && NElectrons==1 ){
       //       if(!(elec && (tighte_trgpass || tightmu_trgpass))) continue;                                                    
       if(!(elec && tighte_trgpass && tightmu_trgpass)) continue;
      //exactly 1 RECO muons and 1 RECO e                                                           
 
       if((*Electrons_passIso)[0]!=1 || (*Muons_passIso)[0]!=1) continue;
       if( (*Electrons_charge)[0] == (*Muons_charge)[0] ) continue;//opp sign same flav(OSSF)                                        
       elec1=(*Electrons)[0];
       muon1=(*Muons)[0];
       if(elec1.Pt()<20 || muon1.Pt()<20) continue;
       double dR1=bestPhoton.DeltaR((*Electrons)[0]);
       double dR2=bestPhoton.DeltaR((*Muons)[0]);
       bool muMatchedG=check_muMatchedtoGamma(bestPhoton);                                                                                                                
       //       if(muMatchedG) continue;                                                                                                                                  
       if(!(dR1>0.2 && dR2>0.2)) continue;
       //zvec =  ((*Muons)[0] + (*Muons)[1]);
       zvec =  muon1 + elec1;
       zmass = zvec.M();
       //       cout<<jentry<<" : "<<zmass<<endl;
       nelectrons=1;
       nmuons=1;
       vlep1=elec1;
       vlep2=muon1;
       lep3++;

     }
     else continue;
     // if(NElectrons != 2 && NMuons!=2 ) continue;
     // // else continue;
     // // //     if(NMuons==2)
     if(!(nelectrons==2 || nmuons==2)) continue;
     //     if(!(nelectrons==2 || nmuons==2 || (nelectrons==1 && nmuons==1))) continue;
     //     if(!(nelectrons==1 && nmuons==1)) continue;
     lep++;
    
     if(zvec.M() < 80 || zvec.M() > 100) continue;
     //     if(zvec.M() < 60 || zvec.M() > 120) continue;
     zwin++;
     h_zpt->Fill(zvec.Pt(),wt);
 
    if(MET>200) continue;
    

    //     cout<<"=========> MET = "<<MET<<" ,Z Pt = "<<zvec.Pt()<<endl;
     //     h_zpt->Fill(zvec.Pt(),wt);
     //     if(lep3>0) lep3_v2++;  
  }
   TLorentzVector metvec, metstar;
   metstar = metvec;
   metvec.SetPtEtaPhiE(MET,0.0,METPhi,0.0);
   metstar = metvec + zvec;
   int genzvec_id=-1;
   TLorentzVector tmp;
   if(s_data.Contains("ZGToNuNuG") || s_data.Contains("ZJetsToNuNu")){
     if(jentry<3) cout<<"Processing as Z(G)->NuNu(G) Decay"<<endl;
     if(isoElectronTracks!=0 || isoMuonTracks!=0 || isoPionTracks!=0) continue;
     if(NElectrons!=0 || NMuons!=0) continue;
     //  else cout<<NElectrons<<endl;
     for(int i=0;i<GenParticles->size();i++){
       if((*GenParticles)[i].Pt()!=0 && abs((*GenParticles_PdgId)[i])==23)
	 {
	   genzvec_id=i;
	   tmp = ((*GenParticles)[i]);
	   // cout<<"Parent id : "<<abs((*GenParticles_ParentId)[i])<<" status : "<<(*GenParticles_Status)[i]<<endl;
	   if(tmp.M()>80 && tmp.M()<100)// && tmp.Pt()>200)
	     {
	       genzvec=tmp;
	       h_zpt->Fill(genzvec.Pt(),wt);
	     }
	 }
     }
   }
   
   
   if( metstar.Pt() > 200 )    
     {    h_selectBaselineYields_->Fill("MET > 200",wt);
       //       cout<<metstar.Pt()<<endl;
     }
   else
     {
       continue;
     }    //---------------------------------------------------------------------------------                                    
   //   cout<<"=========> MET* = "<<metstar.Pt()<<endl;
   met++;   
   float dphi1_=4;

   double nbjets=0;
   int bJet1Idx = -1;

   vector<TLorentzVector> nonbjets,bjets;

   //calulate ST and HadJets by cleaning the matching jet.
   bool hadJetID=true, EMJetID=true;
   int minDRindx=-100,phoMatchingJetIndx=-100,nHadJets=0, minDRindxl1=-100, minDRindxl2=-100, minDRindxl3=-100;
   double minDR=99999, ST=0, remJetPt=0, minDRl1=10000, minDRl2=10000, minDRl3=10000,mt_Pho=0.;
   vector<TLorentzVector> hadJets, EMJets;

   for(int i=0;i<Jets->size();i++){
     if( ((*Jets)[i].Pt() > 30) && (abs((*Jets)[i].Eta()) <= 2.4) ){
       double dR=bestPhoton.DeltaR((*Jets)[i]);
       if(dR<minDR){minDR=dR;minDRindx=i;}
       if(nmuons==2){
	 if( muon1.DeltaR((*Jets)[i]) < minDRl1 ){ minDRl1 = muon1.DeltaR((*Jets)[i]); minDRindxl1=i;}
	 if( muon2.DeltaR((*Jets)[i]) < minDRl2 ){ minDRl2 = muon2.DeltaR((*Jets)[i]); minDRindxl2=i;}       	 
       }
       else if(nelectrons==2){ 
       	 if( elec1.DeltaR((*Jets)[i]) < minDRl1 ){ minDRl1 = elec1.DeltaR((*Jets)[i]); minDRindxl1=i;}
       	 if( elec2.DeltaR((*Jets)[i]) < minDRl2 ){ minDRl2 = elec2.DeltaR((*Jets)[i]); minDRindxl2=i;}
       }
       else if(nelectrons==1 && nmuons==1){
       	 if( elec1.DeltaR((*Jets)[i]) < minDRl1 ){ minDRl1 = elec1.DeltaR((*Jets)[i]); minDRindxl1=i;}
       	 if( muon1.DeltaR((*Jets)[i]) < minDRl2 ){ minDRl2 = muon1.DeltaR((*Jets)[i]); minDRindxl2=i;}
       }
       
     }
   }//loop over jets
   if( minDR > 0.3 )  minDRindx   = -100;
   if( minDRl1 > 0.3) minDRindxl1 = -100;
   if( minDRl2 > 0.3) minDRindxl2 = -100;
   int q=0;
   for(int i=0;i<Jets->size();i++){
     if( ((*Jets)[i].Pt() > 30) && (abs((*Jets)[i].Eta()) <=  2.4) ){
       q++;
       if(q==1){
	 h2_JetEta_Phi->Fill((*Jets)[0].Eta(),(*Jets)[0].Phi(),wt); 
	 h_JetPt->Fill((*Jets)[0].Pt(),wt);
	 h_JetEta->Fill((*Jets)[0].Eta(),wt);
	 h_JetPhi->Fill((*Jets)[0].Phi(),wt);
	 h2_JetEta_Pt->Fill((*Jets)[0].Eta(),(*Jets)[0].Pt(),wt);
       }
       if((i!=minDRindx) && (i!=minDRindxl1) && (i!=minDRindxl2))
	 {
	   hadJets.push_back((*Jets)[i]);
	   if(hadJetID) hadJetID=(*Jets_ID)[i];

	   if((*Jets_bJetTagDeepCSVBvsAll)[i] > deepCSVvalue){                                        
	     //	     if(abs((*Jets_hadronFlavor)[i])==5){                                                               
	       
	     bjets.push_back((*Jets)[i]); bJet1Idx = i;}
	   //else nonbjets.push_back((*Jets)[i]);
	   // }
	 }
       else if(i==minDRindx)
	 {
	   EMJets.push_back((*Jets)[i]);
	   if(EMJetID) EMJetID=(*Jets_ID)[i];
	   // cout<<jentry<<" : "<<i<<" , minDR for photon having idx "<<minDRindx<<" : "<<minDR<<" , minDR for e having idx "<<minDRindxl1<<" : "<<minDRl1<<" , minDR for e having idx "<<minDRindxl2<<" : "<<minDRl2<<endl;
	 }
     }
   }
   for(int i=0;i<hadJets.size();i++){
     if( (abs(hadJets[i].Eta()) < 2.4) ){ST=ST+(hadJets[i].Pt());}
     if( (abs(hadJets[i].Eta()) < 2.4) ){nHadJets++;}
   }

   for(int i=0;i<bjets.size();i++)
     if( (abs(bjets[i].Eta()) < 2.4) ){nbjets++;}

   h_deepcsv->Fill(bjets.size(),wt);


   if( minDR<0.3 )
     {
       phoMatchingJetIndx=minDRindx;
       leadbjet_tag1=(*Jets_bJetTagDeepCSVBvsAll)[phoMatchingJetIndx];
       qmulti1=(*Jets_chargedMultiplicity)[phoMatchingJetIndx];
     }
   if( minDRl1<0.3 )
     {
       leadbjet_tag2=(*Jets_bJetTagDeepCSVBvsAll)[minDRindxl1];
       qmulti2=(*Jets_chargedMultiplicity)[minDRindxl1];
     }
   if( minDRl2<0.3 )
     {
       leadbjet_tag3=(*Jets_bJetTagDeepCSVBvsAll)[minDRindxl2];
       qmulti3=(*Jets_chargedMultiplicity)[minDRindxl2];
     }


   if( minDR<0.3 ){
     ST=ST+bestPhoton.Pt();
   }
   sortTLorVec(&hadJets);

   //ST and HadJets have been determined. Now calulate dPhi b/w MET and leading HadJets.
   double dPhi_METjet1=3.8,dPhi_METjet2=3.8,dPhi_METjet3=3.8,dPhi_METjet4=3.8,dphiPho_MET=3.8,dphi_PhoLep1=3.8,dphi_PhoLep2=3.8,dRphoClstLep=1000.0;
   if(bestPhoton.Pt()>0.1) dphiPho_MET=abs(DeltaPhi(metstar.Phi(),bestPhoton.Phi()));
   if(nHadJets > 0 ) dPhi_METjet1 = abs(DeltaPhi(metstar.Phi(),(hadJets)[0].Phi()));
   if(nHadJets > 1 ) dPhi_METjet2 = abs(DeltaPhi(metstar.Phi(),(hadJets)[1].Phi()));
   if(nHadJets > 2 ) dPhi_METjet3 = abs(DeltaPhi(metstar.Phi(),(hadJets)[2].Phi()));
   if(nHadJets > 3 ) dPhi_METjet4 = abs(DeltaPhi(metstar.Phi(),(hadJets)[3].Phi()));
 
      float dphi1=4, dphi2=4, dphi3=4, dphi4=4;
      if(Jets->size() > 0 && (*Jets)[0].Pt() > 30 && abs((*Jets)[0].Eta()) < 5.0)
      dphi1 = (abs(DeltaPhi(metstar.Phi(),(*Jets)[0].Phi())));
    if(Jets->size() > 1 && (*Jets)[1].Pt() > 30 && abs((*Jets)[1].Eta()) < 5.0)
      dphi2 = (abs(DeltaPhi(metstar.Phi(),(*Jets)[1].Phi())));
    if(Jets->size() > 2 && (*Jets)[2].Pt() > 30 && abs((*Jets)[2].Eta()) < 5.0)
      dphi3 = (abs(DeltaPhi(metstar.Phi(),(*Jets)[2].Phi())));
    if(Jets->size() > 3 && (*Jets)[3].Pt() > 30 && abs((*Jets)[3].Eta()) < 5.0)
      dphi4 = (abs(DeltaPhi(metstar.Phi(),(*Jets)[3].Phi())));
    //    if((dphi1 < 1.5) || (dphi2 < 0.5) || (dphi3 < 0.3) || (dphi4 < 0.3)) continue; 

    if(phoMatchingJetIndx>=0 && ((*Jets)[phoMatchingJetIndx].Pt())/(bestPhoton.Pt()) < 1.0) continue;
    if(phoMatchingJetIndx<0) continue;
  
    bool process=true, cr=false, sr=false; 
    if(s_data.Contains("ZGToNuNuG") || s_data.Contains("ZJetsToNuNu")) 
     {     //     process = process &&  ST>300 && metstar.Pt()>200 && nHadJets >=2 && bestPhoton.Pt() > 100;
       process = process &&  ST>300 && metstar.Pt()>200 && nHadJets >=2 && dPhi_METjet1 > 0.3 && dPhi_METjet2 > 0.3 && bestPhoton.Pt() > 100 ;//&& BTagsDeepCSV>0;
     sr=true;
     } 
    if(s_data.Contains("ZGToLLG") || s_data.Contains("DYJetsToLL") || s_data.Contains("data")   || s_data.Contains("WG") || s_data.Contains("TTG"))
      {
	process = process &&  ST>300 && metstar.Pt()>200 && nHadJets >=2 && dPhi_METjet1 > 0.3 && dPhi_METjet2 > 0.3 && bestPhoton.Pt() > 100; 
     
	cr=true;
      }
    //    if((BTagsDeepCSV==0 && nHadJets >=2 && nHadJets <=4)) continue;
    //      if(!(BTagsDeepCSV==0 && nHadJets >=5 && nHadJets <=6)) continue;
    
    //    if(!(BTagsDeepCSV==0 && nHadJets ==4)) continue;
       // if(!(BTagsDeepCSV>0 && nHadJets >=2 && nHadJets <=4)) continue;
       // if(!(BTagsDeepCSV>0 && nHadJets >=5 && nHadJets <=6)) continue;
       // if(!(BTagsDeepCSV>0 && nHadJets >=7)) continue;


    if(!(hadJetID && process)) continue;
    st++;
    //
   //==============Ak8 EW selection=====================//                                                                                                  

   //===============Ak8 Jets =====================                                                                                                          
   bool hadAK8JetID =false;
   int minDR4indx=-100,minDR4indxl1=-100,minDR4indxl2=-100,minDR5indx , Ak8ID=-100;//photonMatchingJetIndx=-100,nHadJets=0;                                                                     
   double minDR4=99999,minDR4l1=99999,minDR4l2=99999,minDR5;
   double minDPhi4=99999,minDPhi4l1=99999,minDPhi4l2=99999;
   vector<TLorentzVector> hadAK8Jets;
   vector<TLorentzVector> hadAK8Jets_matchedW;
   vector<double> hadAK8Mass, hadAK8Mass_matchedW;
   double Ak8Mass=-100,max=0.0,Ak8Mass1;
   for(int i=0;i<JetsAK8->size();i++)
     {
       if( ((*JetsAK8)[i].Pt() > 200.0) && (abs((*JetsAK8)[i].Eta()) <= 2.4) ){
	 double dR4=bestPhoton.DeltaR((*JetsAK8)[i]);
	 if(dR4<minDR4){minDR4=dR4;minDR4indx=i; minDPhi4=abs(DeltaPhi(bestPhoton.Phi(),(*JetsAK8)[i].Phi()));}
	 if(nmuons==2){

	   if( muon1.DeltaR((*JetsAK8)[i]) < minDR4l1 ){ minDR4l1 = muon1.DeltaR((*JetsAK8)[i]); minDR4indxl1=i; minDPhi4l1=abs(DeltaPhi(muon1.Phi(),(*JetsAK8)[i].Phi()));}
	   if( muon2.DeltaR((*JetsAK8)[i]) < minDR4l2 ){ minDR4l2 = muon2.DeltaR((*JetsAK8)[i]); minDR4indxl2=i; minDPhi4l2=abs(DeltaPhi(muon2.Phi(),(*JetsAK8)[i].Phi()));}
	 }
	 else if(nelectrons==2){	 
	   if( elec1.DeltaR((*JetsAK8)[i]) < minDR4l1 ){ minDR4l1 = elec1.DeltaR((*JetsAK8)[i]); minDR4indxl1=i; minDPhi4l1=abs(DeltaPhi(elec1.Phi(),(*JetsAK8)[i].Phi()));}
	   if( elec2.DeltaR((*JetsAK8)[i]) < minDR4l2 ){ minDR4l2 = elec2.DeltaR((*JetsAK8)[i]); minDR4indxl2=i; minDPhi4l2=abs(DeltaPhi(elec2.Phi(),(*JetsAK8)[i].Phi()));}
	 }
	 else if(nelectrons==1 || nmuons==1){	 
	   if( elec1.DeltaR((*JetsAK8)[i]) < minDR4l1 ){ minDR4l1 = elec1.DeltaR((*JetsAK8)[i]); minDR4indxl1=i;  minDPhi4l1=abs(DeltaPhi(elec1.Phi(),(*JetsAK8)[i].Phi()));}
  	   if( muon1.DeltaR((*JetsAK8)[i]) < minDR4l2 ){ minDR4l2 = muon1.DeltaR((*JetsAK8)[i]); minDR4indxl2=i; minDPhi4l2=abs(DeltaPhi(muon1.Phi(),(*JetsAK8)[i].Phi()));}
	 }
       }
     }

   //abs(DeltaPhi(metstar.Phi(),(hadJets)[0].Phi()))
   //     h_minDr_bestphoJets->Fill(minDR4,wt);
   //   h_minDr_Elejet1->Fill(minDR4l1,wt);
   //   h_minDr_Elejet2->Fill(minDR4l2,wt);
   //  h_minDphi_bestphoJets->Fill(minDPhi4,wt);
   //  h_minDphi_Elejet1->Fill(minDPhi4l1,wt);
   //  h_minDphi_Elejet2->Fill(minDPhi4l2,wt);



   // h2_minDr_Elejet1->Fill(abs(elec1.DeltaR(hadAK8Jets[0])),wt);
   // h2_minDr_Elejet2->Fill(abs(elec2.DeltaR(hadAK8Jets[0])),wt);
   //h2_hadAk8Mass->Fill((*JetsAK8_softDropMass)[0],wt);

   //   if(minDR4indxl2==minDR4indxl1) cout<<"same jet !!! "<<endl;
  if(hadj)
    {
      if(minDR4 > 0.3) minDR4indx=-100;
      if(minDR4l1 > 0.8) minDR4indxl1=-100;
      if(minDR4l2 > 0.8) minDR4indxl2=-100;
    }
  else
    {
      if(minDR4 > 0.5) minDR4indx=-100;
      if(minDR4l1 > 0.8) minDR4indxl1=-100;
      if(minDR4l2 > 0.8) minDR4indxl2=-100;
    }


   for(int i=0;i<JetsAK8->size();i++)
     if( ((*JetsAK8)[i].Pt() > 200.0) && (abs((*JetsAK8)[i].Eta()) <= 2.4) ){

       if( i!=minDR4indx && i!= minDR4indxl1 && i!= minDR4indxl2) {
     
	 hadAK8JetID=(*JetsAK8_ID)[i];

	 if(hadAK8JetID)
	   {
	     hadAK8Jets.push_back((*JetsAK8)[i]);
	     hadAK8Mass.push_back((*JetsAK8_softDropMass)[i]);
	     Ak8ID=i;
	     //  h_minDr_bestphoJets->Fill(minDR4,wt);
	     // h_minDr_Elejet1->Fill(minDR4l1,wt);
	     // h_minDr_Elejet2->Fill(minDR4l2,wt);
	     //	     h_minDphi_bestphoJets->Fill(minDPhi4,wt);
	     //	     h_minDphi_Elejet1->Fill(minDPhi4l1,wt);
	     //	     h_minDphi_Elejet2->Fill(minDPhi4l2,wt);
	     //	     cout<<jentry<<" : "<<i<<" , hadAK8Jets Pt = "<<hadAK8Jets[i].Pt()<<" , hadAK8Mass = "<<hadAK8Mass[i]<<endl;


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

       //       cout<<jentry<<" , hadAK8Jets.size() = "<<hadAK8Jets.size()<<" , hadAK8Mass.size() = "<<hadAK8Mass.size()<<endl;
     }

   //   if (hadAK8Jets.size() == 2)
   //  {
       //       Ak8Mass=hadAK8Mass[0];

   //  cout<<jentry<<" , hadAK8mass = "<<hadAK8Mass[1]<<endl;
   //  }
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



   remain++;

   int btag_org=-1,btag_org2=-1;
   btag_org=nbjets;
   btag_org2=BTagsDeepCSV;


   if(applybTagSFs)
     {

       nbjets=0;
       BTagsDeepCSV=0;

       int sBin6_50bin_btag0= getBinNoV6_EWplusSP_CR(EWselec,EWselec1 ,EWselec_Htag,EWselec_Wtag,nHadJets,nbjets,metstar.Pt());
       h_SBins_v6_CD_EW_50bin_elec0->Fill(sBin6_50bin_btag0,wt*prob0);
       int sBin6_btag0 = getBinNoV7_le(nHadJets,nbjets);
       h_SBins_v6_CD->Fill(sBin6_btag0,wt*prob0);
       int sBin7_btag0= getBinNoV6_EWplusSP_SR(EWselec,EWselec1 ,EWselec_Htag,EWselec_Wtag,nHadJets,nbjets,metstar.Pt());
       h_SBins_v7_CD->Fill(sBin7_btag0,wt*prob0);
       int sBin_TF_btag0=getBinNoV6_SP(EWselec,EWselec1 ,EWselec_Htag,EWselec_Wtag,nHadJets,nbjets,metstar.Pt());
       h_SBins_v6_CD_EW_7bin->Fill(sBin_TF_btag0,wt*prob0);

       h_BTags->Fill(BTagsDeepCSV,wt*prob0);
       h_deepcsv_v4->Fill(nbjets,wt*prob0);
       h2_btag_probwt->Fill(nbjets,leadbjet_tag2,wt*prob0);


       nbjets=1;
       BTagsDeepCSV=1;
       int sBin6_50bin_btag1= getBinNoV6_EWplusSP_CR(EWselec,EWselec1 ,EWselec_Htag,EWselec_Wtag,nHadJets,nbjets,metstar.Pt());
       h_SBins_v6_CD_EW_50bin_elec0->Fill(sBin6_50bin_btag1,wt*prob1);
       int sBin6_btag1 = getBinNoV7_le(nHadJets,nbjets);
       h_SBins_v6_CD->Fill(sBin6_btag1,wt*prob1);
       int sBin7_btag1= getBinNoV6_EWplusSP_SR(EWselec,EWselec1 ,EWselec_Htag,EWselec_Wtag,nHadJets,nbjets,metstar.Pt());
       h_SBins_v7_CD->Fill(sBin7_btag1,wt*prob1);
       int sBin_TF_btag1=getBinNoV6_SP(EWselec,EWselec1 ,EWselec_Htag,EWselec_Wtag,nHadJets,nbjets,metstar.Pt());
       h_SBins_v6_CD_EW_7bin->Fill(sBin_TF_btag1,wt*prob1);

       h_BTags->Fill(BTagsDeepCSV,wt*prob[1]);
       h_deepcsv_v4->Fill(nbjets,wt*prob[1]);
       h2_btag_probwt->Fill(nbjets,leadbjet_tag2,wt*prob[1]);

       nbjets=2;
       BTagsDeepCSV=2;
       h_BTags->Fill(nbjets,wt*prob[2]);
       h_deepcsv_v4->Fill(nbjets,wt*prob[2]);
       h2_btag_probwt->Fill(nbjets,leadbjet_tag2,wt*prob[2]);

       nbjets=3;
       BTagsDeepCSV=3;
       h_BTags->Fill(BTagsDeepCSV,wt*prob[3]);
       h_deepcsv_v4->Fill(nbjets,wt*prob[3]);
       h2_btag_probwt->Fill(nbjets,leadbjet_tag2,wt*prob[3]);
       nbjets=btag_org;
       BTagsDeepCSV=btag_org2;
     }

   // if(nbjets==0) continue;
   // if(nHadJets,nbjets < 2 || nHadJets,nbjets > 4) continue;
   if(!applybTagSFs){

     int sBin6_50bin= getBinNoV6_EWplusSP_CR(EWselec,EWselec1 ,EWselec_Htag,EWselec_Wtag,nHadJets,nbjets,metstar.Pt());
     h_SBins_v6_CD_EW_50bin_elec0->Fill(sBin6_50bin,wt);
     //     if(!(EWselec && EWselec1))
       {
	 int sBin7= getBinNoV6_EWplusSP_SR(EWselec,EWselec1 ,EWselec_Htag,EWselec_Wtag,nHadJets,nbjets,metstar.Pt());
	 h_SBins_v7_CD->Fill(sBin7,wt);
       }

     int sBin6 = getBinNoV7_le(nHadJets,nbjets);
     h_SBins_v6_CD->Fill(sBin6,wt);
     int sBin_TF=getBinNoV6_SP(EWselec,EWselec1 ,EWselec_Htag,EWselec_Wtag,nHadJets,nbjets,metstar.Pt());
     h_SBins_v6_CD_EW_7bin->Fill(sBin_TF,wt);

     h_BTags->Fill(BTagsDeepCSV,wt);
     h_deepcsv_v4->Fill(nbjets,wt);
     h2_btag_probwt->Fill(nbjets,leadbjet_tag2,wt);
   }

   //   if(hadAK8Jets.size()>0)   h_minDphi_bestphoJets->Fill(abs(DeltaPhi(bestPhoton.Phi(),hadAK8Jets[0].Phi())),wt);
   //   h_minDphi_Elejet1->Fill(abs(DeltaPhi(elec1.Phi(),hadAK8Jets[0].Phi())),wt);
   //   h_minDphi_Elejet2->Fill(abs(DeltaPhi(elec2.Phi(),hadAK8Jets[0].Phi())),wt);


     h2_QMultlleadbJet->Fill(qmulti2,leadbjet_tag2,wt);
     h2_METleadbJet->Fill(metstar.Pt(),leadbjet_tag2,wt);
     after_bjetdisc++;
     h_MET_CaloMET->Fill(MET/CaloMET,wt);
     h_dPhi_MET_CaloMET->Fill(abs(DeltaPhi(metstar.Phi(),CaloMETPhi)),wt);
     h_HT5HT->Fill(HT5/HT,wt);
     // if((s_data.Contains("2016")) && leadbjet_tag>0.6321) continue;
     // if((s_data.Contains("2017")) && leadbjet_tag>0.4941) continue;
     // if((s_data.Contains("2018")) && leadbjet_tag>0.4184) continue;


     // h_invMass->Fill(zvec.M());
     // h_invMass->Fill(zvec.M());
     if(cr)
       {
	 h_genzpt->Fill(zvec.Pt(),wt);
	     h_invMass->Fill(zvec.M(),wt);
       }
     if(sr && genzvec_id != -1)
       {
	 //	 h_zpt->Fill(genzvec.Pt(),wt);
	 h_genzpt->Fill(genzvec.Pt(),wt);
	 //	 h_invMass->Fill(genzvec.M(),wt);
	     h_invMass->Fill(genzvec.M(),wt);
       }
     h_nJets->Fill(nHadJets,wt);
     h_HT->Fill(HT,wt);
     h_ST->Fill(ST,wt);
     h_MET->Fill(metstar.Pt(),wt);
     h_METvBin2->Fill(metstar.Pt(),wt);
     h_METPhi->Fill(metstar.Phi(),wt);
     h_BestPhotonPt->Fill(bestPhoton.Pt(),wt);
     h_BestPhotonPhi->Fill((bestPhoton.Phi()),wt);
     h_BestPhotonEta->Fill((bestPhoton.Eta()),wt);
      h_dPhi_METjet1->Fill(dPhi_METjet1,wt);
     h_dPhi_METjet2->Fill(dPhi_METjet2,wt);

     // h_dPhi_METjet3->Fill(dPhi_METjet3,wt);
     // h_dPhi_METjet4->Fill(dPhi_METjet4,wt);
     // h_dPhi_METjet1->Fill(dphi1,wt);
     // h_dPhi_METjet2->Fill(dphi2,wt);
     h_dPhi_METjet3->Fill(dphi1,wt);
     h_dPhi_METjet4->Fill(dphi2,wt);
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
     // h_dPhi_METjet1->Fill(dphi1,wt);
     // h_dPhi_METjet2->Fill(dphi2,wt);
     //   h_dPhi_phoMET->Fill(dPhi_phoMET,wt);
     //   h2_BestPhotonEta_Qmulti2->Fill(bestPhoton.Eta(),qmulti2,wt);
     h2_BestPhotonEta_nJets->Fill(bestPhoton.Eta(),nHadJets,wt);
     h2_BestPhotonEta_MET->Fill(bestPhoton.Eta(),metstar.Pt(),wt);
     h2_nbjets_nJets->Fill(hadJets.size(),BTags,wt);
     h2_leadElectronEta_Phi->Fill(bestPhoton.Eta(),bestPhoton.Phi(),wt);
     h2_leadElectronPt_Eta->Fill(bestPhoton.Pt(),bestPhoton.Eta(),wt);
     h2_leadElectronPt_Phi->Fill(bestPhoton.Pt(),bestPhoton.Phi(),wt);
     if(cr)
       {
       	 if(nelectrons==2 )
       	   {
       	     h_EMObj_pT->Fill(elec2.Pt(),wt);
       	     h_EMObj_Phi->Fill(elec2.Phi(),wt);
       	     h_EMObj_Eta->Fill(elec2.Eta(),wt);
       	     h_ElectronPt->Fill(elec1.Pt(),wt);
       	     h_ElectronPhi->Fill(elec1.Phi(),wt);
       	     h_ElectronEta->Fill(elec1.Eta(),wt);
       	     h2_ElectronEta_Phi->Fill(elec1.Eta(),elec1.Phi(),wt);
	     //	     h_minDphi_bestphoJets->Fill(abs(DeltaPhi(bestPhoton.Phi(),hadAK8Jets[0].Phi())),wt);
	     //h_minDphi_Elejet1->Fill(abs(DeltaPhi(elec1.Phi(),hadAK8Jets[0].Phi())),wt);
	     //h_minDphi_Elejet2->Fill(abs(DeltaPhi(elec2.Phi(),hadAK8Jets[0].Phi())),wt);

       	     //cout<<jentry<<" : "<<elec1.Phi()<<endl;
       	   }
       	 if(nmuons==2)
       	   {
       	     h_EMObj_pT->Fill(muon2.Pt(),wt);
       	     h_EMObj_Phi->Fill(muon2.Phi(),wt);
       	     h_EMObj_Eta->Fill(muon2.Eta(),wt);
       	     h_ElectronPt->Fill(muon1.Pt(),wt);
       	     h_ElectronPhi->Fill(muon1.Phi(),wt);
       	     h_ElectronEta->Fill(muon1.Eta(),wt);
       	     h2_ElectronEta_Phi->Fill(muon1.Eta(),muon1.Phi(),wt);
	     //	     h_minDphi_bestphoJets->Fill(abs(DeltaPhi(bestPhoton.Phi(),hadAK8Jets[0].Phi())),wt);
	     //    h_minDphi_Elejet1->Fill(abs(DeltaPhi(muon1.Phi(),hadAK8Jets[0].Phi())),wt);
	     //h_minDphi_Elejet2->Fill(abs(DeltaPhi(muon2.Phi(),hadAK8Jets[0].Phi())),wt);

       	     // cout<<jentry<<" : "<<muon1.Phi()<<endl;
       	   }


       }

     if(process && EWselection && (EWselec && EWselec1))// && (EWselec_Wtag && !EWselec_Htag))
       {
	 //	 if(abs(DeltaPhi(bestPhoton.Phi(),hadAK8Jets[0].Phi()))<1.0) continue;
	 h_nJets_EW->Fill(nHadJets,wt);
	 h_ST_EW->Fill(ST,wt);
	 h_BTags_EW->Fill(nbjets,wt);
	 h_MET_EW->Fill(metstar.Pt(),wt);
	 h_BestPhotonPt_EW->Fill(bestPhoton.Pt(),wt);
	 h_minDphi_bestphoJets->Fill(abs(DeltaPhi(bestPhoton.Phi(),hadAK8Jets[0].Phi())),wt);
	 //	 h_minDr_bestphoJets->Fill(minDR4,wt);
	 // h_minDr_Elejet1->Fill(minDR4l1,wt);
	 // h_minDr_Elejet2->Fill(minDR4l2,wt);
	 //bestPhoton.DeltaR((*JetsAK8)[i])
	  h_minDr_bestphoJets->Fill(abs(bestPhoton.DeltaR(hadAK8Jets[0])),wt);
	 //	 h_minDr_Elejet1->Fill(abs(elec1.DeltaR(hadAK8Jets[0])),wt);
	 // h_minDr_Elejet2->Fill(abs(elec2.DeltaR(hadAK8Jets[0])),wt);
	 //	 cout<<jentry<<" : "<<0<<" , hadAK8Jets Pt = "<<hadAK8Jets[0].Pt()<<" , hadAK8Mass = "<<hadAK8Mass[0]<<endl;                                            

	  h_hadAk8Mass->Fill(hadAK8Mass[0],wt);
	  if(cr)
	   {
	     h_minDr_Zjet1->Fill(abs(zvec.DeltaR(hadAK8Jets[0])),wt);
	     h_minDphi_Zjet1->Fill(abs(DeltaPhi(zvec.Phi(),hadAK8Jets[0].Phi())),wt);
	   }
	  if(nelectrons==2 ){
	    h_minDphi_Elejet1->Fill(abs(DeltaPhi(elec1.Phi(),hadAK8Jets[0].Phi())),wt);
	    h_minDphi_Elejet2->Fill(abs(DeltaPhi(elec2.Phi(),hadAK8Jets[0].Phi())),wt);
	    h_minDr_Elejet1->Fill(abs(elec1.DeltaR(hadAK8Jets[0])),wt);
	    h_minDr_Elejet2->Fill(abs(elec2.DeltaR(hadAK8Jets[0])),wt);
	  }
	  if(nmuons==2 ){
	    h_minDphi_Elejet1->Fill(abs(DeltaPhi(muon1.Phi(),hadAK8Jets[0].Phi())),wt);
	    h_minDphi_Elejet2->Fill(abs(DeltaPhi(muon2.Phi(),hadAK8Jets[0].Phi())),wt);
	    h_minDr_Elejet1->Fill(abs(muon1.DeltaR(hadAK8Jets[0])),wt);
	    h_minDr_Elejet2->Fill(abs(muon2.DeltaR(hadAK8Jets[0])),wt);
	  }
       }
   

     if(s_data.Contains("ZGToLLG") || s_data.Contains("DYJetsToLL"))
       do_prediction=true;
     else
       do_prediction=false;

       

     double wt2=wt;
     if(do_prediction)
       {
	 if(!(EWselec && EWselec1)){
	   if(nbjets==0)  wt2=wt*tf->GetBinContent(1);
	   else wt2=wt*tf->GetBinContent(2);
	 }
         if((EWselec && EWselec1)){
	   if(EWselec_Wtag && !EWselec_Htag)     { wt2=wt*tf->GetBinContent(3);}
	   if(EWselec_Htag && !EWselec_Wtag)      { wt2=wt*tf->GetBinContent(4);}
	 }
       }
     int sBin7_SP_elec1_closure = getBinNoV6_SP(EWselec,EWselec1 ,EWselec_Htag,EWselec_Wtag,nHadJets,nbjets,metstar.Pt());
     h_SBins_v6_CD_EW_7bin_elec1_closure->Fill(sBin7_SP_elec1_closure,wt2);
     int sBin6_50bin_closure= getBinNoV6_EWplusSP_CR(EWselec,EWselec1 ,EWselec_Htag,EWselec_Wtag,nHadJets,nbjets,metstar.Pt());
     h_SBins_v6_CD_EW_50bin_elec1_closure->Fill(sBin6_50bin_closure,wt2);

     h_MET_elec1_closure->Fill(metstar.Pt(),wt2);
     h_METvBin2_elec1_closure->Fill(metstar.Pt(),wt2);
     h_nJets_elec1_closure->Fill(nHadJets,wt2);
     h_ST_elec1_closure->Fill(ST,wt2);
     h_BTags_elec1_closure->Fill(nbjets,wt2);
     h_BestPhotonPt_elec1_closure->Fill(bestPhoton.Pt(),wt2);
     h_BestPhotonPhi_elec1_closure->Fill(bestPhoton.Phi(),wt2);
     h_BestPhotonEta_elec1_closure->Fill(bestPhoton.Eta(),wt2);
	 
  }

    //=========================================================================//

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

  cout<<"Total Events with NElectrons=2 : "<<lep1<<endl;
  cout<<"Total Events with NMuons=2 : "<<lep2<<endl;
  cout<<"Total Events with NElectrons=1 & NMuons=1 : "<<lep3<<endl;
  cout<<"Total Events with Nleptons=2 : "<<lep<<endl;

  cout<<"Events in Z mass window : "<<zwin<<endl;
  // cout<<"Events Survived before genphomatch : "<<genphomatch_before<<endl;
  // cout<<"Events Survived after genphomatch : "<<genphomatch_after<<endl;
  cout<<"Events survived after MET<200 cut : "<<met<<endl;
  cout<<"Total Events with NElectrons=2 || NMuons=2 : "<<lep3_v1<<endl;
  cout<<"Total Events with NLeptons = 2 : "<<lep3_v2<<endl;
  cout<<"Events survived after ST<300 & nJet<2 cut : "<<st<<endl;
  cout<<"remaining : "<<remain<<endl;
  // cout<<"Events after bjet discriminator : "<<after_bjetdisc<<endl;  
  cout<<"================="<<endl;

  // cout<<"no. of events with bjet=0 : "<<nbj0<<" with wt : "<<wt_nbj0<<" , total prob = "<<total_prob0<<endl;
  // cout<<"no. of events with bjet=1 : "<<nbj1<<" with wt : "<<wt_nbj1<<" , total prob = "<<total_prob1<<endl;
  // cout<<"no. of events with bjet=2 : "<<nbj2<<" with wt : "<<wt_nbj2<<" , total prob = "<<total_prob2<<endl;
  // cout<<"no. of events with bjet>=3 : "<<nbj3<<" with wt : "<<wt_nbj3<<" , total prob = "<<total_prob3<<endl;
  // cout<<"total weighted events = "<<total_prob0+total_prob1+total_prob2+total_prob3<<endl;
}
TLorentzVector Z_invisible::getBestPhoton(){
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
TLorentzVector Z_invisible::getPhoton_withoutfullID(){
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

int Z_invisible::getBinNoV7(TLorentzVector bestPhoton,double qmulti, double minDRindx){
  int sBin=0,m_i=-1,sBin1=0,n_i=-1;; 
  for(int i=0;i<BestPhotonPtBinLowEdge.size()-1;i++){
    if(BestPhotonPtBinLowEdge[i]<99.99) continue; 
    //if(qmulti>=10) continue;
    m_i++;  
    if(bestPhoton.Pt() >= BestPhotonPtBinLowEdge[i] && bestPhoton.Pt() < BestPhotonPtBinLowEdge[i+1])
      {
	sBin = sBin+(m_i*4);

	break;

     }
    else if(bestPhoton.Pt() >= BestPhotonPtBinLowEdge[BestPhotonPtBinLowEdge.size()-1])
      {
	sBin = 40;
	break;
      }
  }

  if(sBin%4==0)// || sBin==4 || sBin==8 || sBin==12 || sBin==16 || sBin==20 )
    {
      //	cout<<"bestPhoton : "<<bestPhoton.Pt()<<" , Qmult : "<<qmulti<<" , sBin = "<<sBin1<<endl;

      for(int i=0;i<QMultLowedge.size()-1;i++){
	n_i++;
	if(qmulti>=QMultLowedge[i] && qmulti<QMultLowedge[i+1]) {sBin1=sBin+n_i; break;}
	else if(qmulti>=QMultLowedge[QMultLowedge.size()-1]){sBin1=sBin1+(QMultLowedge.size()-1); break;}
	//	else sBin1=-999;
      }
    }
  
  //   if((qmulti>=7 && qmulti<10) && bestPhoton.Pt()>=100 && bestPhoton.Pt() <120)
  // if(bestPhoton.Pt()>=200 && bestPhoton.Pt() <230)
  //   cout<<"bestPhoton : "<<bestPhoton.Pt()<<" , Qmult : "<<qmulti<<" , sBin = "<<sBin1<<endl;
  return sBin1;  
}


int Z_invisible::getBinNoV6(TLorentzVector bestPhoton, int nHadJets){
  int sBin=0,m_i=-1,sBin1=0,n_i=-1;; 
  for(int i=0;i<BestPhotonPtBinLowEdge.size()-1;i++){
    if(BestPhotonPtBinLowEdge[i]<99.99) continue; 
    m_i++;  
    if(bestPhoton.Pt() >= BestPhotonPtBinLowEdge[i] && bestPhoton.Pt() < BestPhotonPtBinLowEdge[i+1])
      {
	sBin = sBin+(m_i*4);

	break;

     }
    else if(bestPhoton.Pt() >= BestPhotonPtBinLowEdge[BestPhotonPtBinLowEdge.size()-1])
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
  
  //   if((nHadJets>=7 && nHadJets<10) && bestPhoton.Pt()>=100 && bestPhoton.Pt() <120)
  // if(bestPhoton.Pt()>=200 && bestPhoton.Pt() <230)
  //   cout<<"bestPhoton : "<<bestPhoton.Pt()<<" , Qmult : "<<nHadJets<<" , sBin = "<<sBin1<<endl;
  return sBin1;  
}

int Z_invisible::getBinNoV7_le(int nHadJets, int nbjets){
  int sBin=-100,m_i=0;
  //  if(nbjets==0){
  //  if(BTagsclean==0){
  if(nbjets==0){
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

int Z_invisible::getBinNoV7_le2(bool EWselec, bool EWselec1, bool EWselec_Htag , bool EWselec_Wtag,int nHadJets, int nbjets){
  int sBin=-100,m_i=0;
  if(!(EWselec && EWselec1))
    {
      if(nbjets==0){
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




int Z_invisible::getBinNoV6_EWplusSP_CR(bool EWselec, bool EWselec1, bool EWselec_Htag , bool EWselec_Wtag,int nHadJets, int nbjets, double MET_){

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
    for(int i=0;i<METLowEdge_v3.size()-1;i++){
      if(METLowEdge_v3[i]<199.99) continue;
      int sBin1=sBin;
      m_i++;
      if(MET_ >= METLowEdge_v3[i] && MET_ < METLowEdge_v3[i+1]){ sBin = sBin+m_i;
break; }
      else if(MET_ >= METLowEdge_v3[METLowEdge_v3.size()-1])  { sBin = 7         ;
	break; }
    }
  }


  else if(sBin==7 || sBin==13 || sBin==19 || sBin==25 || sBin==31){
    int sBin1=sBin;
    for(int i=0;i<METLowEdge_v3_1.size()-1;i++){
      if(METLowEdge_v3_1[i]<199.99) continue;
      m_i++;
      if(MET_ >= METLowEdge_v3_1[i] && MET_ < METLowEdge_v3_1[i+1]){ sBin = sBin+m_i;
	break;}
      else if(MET_ >= METLowEdge_v3_1[METLowEdge_v3_1.size()-1])  { sBin = sBin+6;
	break; }
    }
  }

  else if(sBin==37){
    for(int i=0;i<METLowEdge_v3.size()-1;i++){
      if(METLowEdge_v3[i]<199.99) continue;
      m_i++;
      if(MET_ >= METLowEdge_v3[i] && MET_ < METLowEdge_v3[i+1]){ sBin = sBin+m_i;break; }
      else if(MET_ >= METLowEdge_v3[METLowEdge_v3.size()-1])  { sBin = 44   ;break; }
      // else if(MET_ >= METLowEdge_v3[METLowEdge_v3.size()-1])  { sBin = 44   ;break; }

   }
  }

  else if(sBin==44){
    for(int i=0;i<METLowEdge_v3.size()-1;i++){
      if(METLowEdge_v3[i]<199.99) continue;
      m_i++;
      if(MET_ >= METLowEdge_v3[i] && MET_ < METLowEdge_v3[i+1]){ sBin = sBin+m_i;break; }
      else if(MET_ >= METLowEdge_v3[METLowEdge_v3.size()-1])  { sBin = 52   ;break; }
   }
  }

  return sBin;
}

int Z_invisible::getBinNoV6_EWplusSP_SR(bool EWselec, bool EWselec1, bool EWselec_Htag , bool EWselec_Wtag,int nHadJets, int nbjets, double MET_){

  int sBin=-100,m_i=0;

  if(nbjets==0 ){
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
    for(int i=0;i<METLowEdge_v3.size()-1;i++){
      if(METLowEdge_v3[i]<199.99) continue;
      int sBin1=sBin;
      m_i++;
      if(MET_ >= METLowEdge_v3[i] && MET_ < METLowEdge_v3[i+1]){ sBin = sBin+m_i;
	break; }
      else if(MET_ >= METLowEdge_v3[METLowEdge_v3.size()-1])  { sBin = 7         ;
	break; }
    }
  }


  else if(sBin==7 || sBin==13 || sBin==19 || sBin==25 || sBin==31){
    int sBin1=sBin;
    for(int i=0;i<METLowEdge_v3_1.size()-1;i++){
      if(METLowEdge_v3_1[i]<199.99) continue;
      m_i++;
      if(MET_ >= METLowEdge_v3_1[i] && MET_ < METLowEdge_v3_1[i+1]){ sBin = sBin+m_i;
	break;}
      else if(MET_ >= METLowEdge_v3_1[METLowEdge_v3_1.size()-1])  { sBin = sBin+6;
	break; }
    }
  }


  return sBin;
}


int Z_invisible::getBinNoV6_SP
(bool EWselec, bool EWselec1, bool EWselec_Htag , bool EWselec_Wtag,int nHadJets, int nbjets, double MET_)
{
  int sBin=-100,m_i=0;

  //  if(!((EWselec_Wtag || EWselec_Htag) && EWselec1))
   if(!(EWselec && EWselec1))
    { 
      if(nbjets==0 )	sBin=1;
      else sBin = 2;      
    }

   if((EWselec && EWselec1))
     {
       if(EWselec_Wtag && !EWselec_Htag)  sBin=3;
       else if(!EWselec_Wtag && EWselec_Htag)  sBin=4;
     }

  return sBin;
}


int Z_invisible::getBinNoV6_EW(bool EWselec_Htag , bool EWselec_Wtag, double MET_){
  int sBin=-100,m_i=0;
  if(EWselec_Wtag && !EWselec_Htag){
    sBin=0;
  }
  else if(!EWselec_Wtag && EWselec_Htag){
    sBin=7;
  }
  if(sBin==0){
    for(int i=0;i<METLowEdge_v3.size()-1;i++){
      if(METLowEdge_v3[i]<249.99) continue;
      m_i++;
      if(MET_ >= METLowEdge_v3[i] && MET_ < METLowEdge_v3[i+1]){ sBin = sBin+m_i;break; }
      else if(MET_ >= METLowEdge_v3[METLowEdge_v3.size()-1])  { sBin = 7         ;break; }
    }
  }
  else if(sBin==7){
    for(int i=0;i<METLowEdge_v3.size()-1;i++){
      if(METLowEdge_v3[i]<249.99) continue;
      m_i++;
      if(MET_ >= METLowEdge_v3[i] && MET_ < METLowEdge_v3[i+1]){ sBin = sBin+m_i;break; }
      else if(MET_ >= METLowEdge_v3[METLowEdge_v3.size()-1])  { sBin = sBin+7   ;break; }
    }
  }
  return sBin;
}


bool Z_invisible::check_eMatchedtoGamma(TLorentzVector bestPhoton){
  for(int i=0;i<Electrons->size();i++)
    {
      if( bestPhoton.DeltaR((*Electrons)[i]) < 0.1)
        return true;
    }
  return false;
}

bool Z_invisible::check_muMatchedtoGamma(TLorentzVector bestPhoton){
  for(int i=0;i<Muons->size();i++)
    {
      if( bestPhoton.DeltaR((*Muons)[i]) < 0.1)
        return true;
    }
  return false;
}
double Z_invisible::getGenLep(TLorentzVector bestPhoton){//MC only
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

double Z_invisible::getGendRLepPho(){//MC only
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
