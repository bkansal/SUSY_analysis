#define SkimmingSR_cxx
#include "SkimmingSR.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <iostream>
#include <vector>
#include <cstring>
#include <string>
#include <fstream>

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

  SkimmingSR ana(inputFileList, outFileName, data);
  cout << "dataset " << data << " " << endl;

  ana.EventLoop(data,inputFileList);

  return 0;
}

void SkimmingSR::EventLoop(const char *data,const char *inputFileList) {
  if (fChain == 0) return;

  Long64_t nentries = fChain->GetEntriesFast();
  cout << "nentries " << nentries << endl;
  cout << "Analyzing dataset " << data << " " << endl;

  Long64_t nbytes = 0, nb = 0;
  int decade = 0;
  //---------- deactivate unwanted branches ---------------
  // fChain->SetBranchStatus("*AK8*",0);
  fChain->SetBranchStatus("*clean*",0);
  fChain->SetBranchStatus("*Clean*",0);
  fChain->SetBranchStatus("*DeltaPhi*",0);

  TTree *newtree = fChain->CloneTree(0);
  TString s_data = data;
  float xsec1;
  cout<<"Key words for if dataset is special: TTJets_DiLept, TTJets_SingleLeptFromT, V12"<<endl;
  Long64_t nSurvived = 0,phopt_rej=0,MET_rej=0,nocut=0;
  double wt = 1.0;
  int lep=0,nele=0,npho=0,npho_px=0,nele_px=0,remain=0;
  // for (Long64_t jentry=0; jentry<10000;jentry++) {
   for (Long64_t jentry=0; jentry<nentries;jentry++) {

    // ==============print number of events done == == == == == == == =
    double progress = 10.0 * jentry / (1.0 * nentries);
    int k = int (progress);
    if (k > decade)
      cout << 10 * k << " %" <<endl;
    decade = k;
    // ===============read this entry == == == == == == == == == == == 
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);   nbytes += nb;
  
    NumEvents = nentries;

    //    Weight = CrossSection/NumEvents;    
    wt = Weight*1000.0;


    h_selectBaselineYields_->Fill("No cuts, evt in 1/fb",wt);
    nocut++;
    //------ putting a cut on madHT for SingleLept and DiLept samples of TTbar. Do not use for other samples.
    if((s_data.Contains("TTJets_DiLept") 
	|| s_data.Contains("TTJets_SingleLeptFromT") )
       && madHT>600) continue;
    h_selectBaselineYields_->Fill("madHT cut",wt);
   

    if(NMuons==0) h_selectBaselineYields_->Fill("0 #mu",wt);
    else continue;

   // //apply iso track veto                                                                                                                
    if(isoMuonTracks ==0 && isoPionTracks==0)
      {
        h_selectBaselineYields_->Fill("Iso track",wt);
      }
    else continue;

    lep++;



    if( MET > 200 )        h_selectBaselineYields_->Fill("MET > 200",wt);
    else 
      {
	continue;
      }    //---------------------------------------------------------------------------------
    MET_rej++;
	

    //about photons
    int hasEle=0, hasPho=0, hasPho_px=0;
    TLorentzVector bestPhoton=getBestPhoton();
    bool bestPhoHasPxlSeed=true;
    bool eMatchedG=check_eMatchedtoGamma(bestPhoton);
    if(bestPhotonIndxAmongPhotons>=0){
      if((*Photons_hasPixelSeed)[bestPhotonIndxAmongPhotons]<0.001) bestPhoHasPxlSeed=false;
      //     if(!eMatchedG && !bestPhoHasPxlSeed && bestPhoton.Pt()>100) hasPho=1;
      if(!bestPhoHasPxlSeed && bestPhoton.Pt()>100) {hasPho=1;hasPho_px=0; }//npho++;}
      else if(bestPhoHasPxlSeed) {hasPho_px=1;hasPho=0;}// npho_px++;}
      else
	{
	  hasPho_px=0;
	  hasPho=0;
	}
    }

    //about Electrons
    int nlep=0, e_index=-1;
    TLorentzVector v_lep1;
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

	if(nlep>1) cout<<jentry<<endl;      
	if(nlep==1 && v_lep1.Pt()>100)
	  {
	    hasEle=1;
	    //	    nele++;
	  }
      }


    bool bestEMObjIsEle=false, bestEMObjIsEle_px=false,bestEMobj=false;
    TLorentzVector bestEMObj;


    if(hasPho_px==1)
      {bestEMObjIsEle=true; bestEMObjIsEle_px=true; bestEMObj = bestPhoton; npho_px++; bestEMobj=true;
      }
    if (hasEle==1 && hasPho==0) {bestEMObjIsEle=true; bestEMObjIsEle_px=false;bestEMObj = (*Electrons)[e_index]; nele++;bestEMobj=true;}
    if(hasEle==0 &&  hasPho==1) {bestEMObjIsEle=false;  bestEMObjIsEle_px=false;bestEMObj = bestPhoton; npho++;bestEMobj=true;}
    if ((hasEle==1 && hasPho==0)|| hasPho_px==1) {nele_px++;bestEMobj=true;}
    if(bestEMobj==false) {remain++; continue;}

	int minDRindx=-100,phoMatchingJetIndx=-100,nHadJets=0,nHadJets_ele=0,nHadJets_px=0;
    double minDR=99999,ST=0,ST_ele=0,ST_px=0;
    vector<TLorentzVector> hadJets, hadJets_ele, hadJets_px;

    //ST and hadJet calculation for photon as a EM object
    if(!bestEMObjIsEle_px && !bestEMObjIsEle)
      {
	for(int i=0;i<Jets->size();i++){
	  if( ((*Jets)[i].Pt() > 30.0) && (abs((*Jets)[i].Eta()) <= 2.4) ){
	    double dR=bestEMObj.DeltaR((*Jets)[i]);
	    if(dR<minDR){minDR=dR;minDRindx=i;}
	  }
	}    
	for(int i=0;i<Jets->size();i++){
	  if( ((*Jets)[i].Pt() > 30.0) && (abs((*Jets)[i].Eta()) <= 2.4) ){
	    if( !(minDR < 0.3 && i==minDRindx) )
	      hadJets.push_back((*Jets)[i]);
	  }
	}


	if( minDR<0.3 ) phoMatchingJetIndx=minDRindx;
	for(int i=0;i<hadJets.size();i++){
	  if( (abs(hadJets[i].Eta()) < 2.4) ){ST=ST+(hadJets[i].Pt());}
	  if( (abs(hadJets[i].Eta()) < 2.4) ){nHadJets++;}
	}
	if( minDR<0.3 )  ST=ST+bestEMObj.Pt();
      }
   
    //ST and hadJet calculation for electron as a EM object
    else if(!bestEMObjIsEle_px && bestEMObjIsEle)
      {
	for(int i=0;i<Jets->size();i++){
	  if( ((*Jets)[i].Pt() > 30.0) && (abs((*Jets)[i].Eta()) <= 2.4) ){
	    double dR=bestEMObj.DeltaR((*Jets)[i]);
	    if(dR<minDR){minDR=dR;minDRindx=i;}
	  }
	}    
	for(int i=0;i<Jets->size();i++){
	  if( ((*Jets)[i].Pt() > 30.0) && (abs((*Jets)[i].Eta()) <= 2.4) ){
	    if( !(minDR < 0.3 && i==minDRindx) )
	      hadJets_ele.push_back((*Jets)[i]);
	  }
	}


	if( minDR<0.3 ) phoMatchingJetIndx=minDRindx;
	for(int i=0;i<hadJets_ele.size();i++){
	  if( (abs(hadJets_ele[i].Eta()) < 2.4) ){ST_ele=ST_ele+(hadJets_ele[i].Pt());}
	  if( (abs(hadJets_ele[i].Eta()) < 2.4) ){nHadJets_ele++;}
	}
	if( minDR<0.3 )  ST_ele=ST_ele+bestEMObj.Pt();
      }

    //ST and hadJet calculation for photon with pixel seed as a EM object
    else if(bestEMObjIsEle_px && bestEMObjIsEle)
      {
	for(int i=0;i<Jets->size();i++){
	  if( ((*Jets)[i].Pt() > 30.0) && (abs((*Jets)[i].Eta()) <= 2.4) ){
	    double dR=bestEMObj.DeltaR((*Jets)[i]);
	    if(dR<minDR){minDR=dR;minDRindx=i;}
	  }
	}    
	for(int i=0;i<Jets->size();i++){
	  if( ((*Jets)[i].Pt() > 30.0) && (abs((*Jets)[i].Eta()) <= 2.4) ){
	    if( !(minDR < 0.3 && i==minDRindx) )
	      hadJets_px.push_back((*Jets)[i]);
	  }
	}


	if( minDR<0.3 ) phoMatchingJetIndx=minDRindx;
	for(int i=0;i<hadJets_px.size();i++){
	  if( (abs(hadJets_px[i].Eta()) < 2.4) ){ST_px=ST_px+(hadJets_px[i].Pt());}
	  if( (abs(hadJets_px[i].Eta()) < 2.4) ){nHadJets_px++;}
	}

	if( minDR<0.3 )  ST_px=ST_px+bestEMObj.Pt();
      }

    //-----------------------------------------------------------------------
    if( nHadJets >= 2 ||  nHadJets_ele >= 2 || nHadJets_px >= 2)  h_selectBaselineYields_->Fill("nJets >=2",wt);
    else continue;
    if(ST>300 || ST_ele > 300 || ST_px>300)  h_selectBaselineYields_->Fill("ST >300",wt);
    else continue;

    //end of select skimming parameters
    nSurvived++;
    newtree->Fill();
 
  } // loop over entries
  //  newtree->AutoSave();
  // cout<<"No. of events rejected by Photon Pt > 100 : "<<phopt_rej<<endl;
  // cout<<"No. of events rejected by MET > 100 : "<<MET_rej<<endl;

  cout<<"No. of events passed by Muon veto and iso muon and pion track veto : "<<lep<<endl;
  cout<<"No. of events passed by MET > 200 : "<<MET_rej<<endl;
  cout<<"EM object is photon : "<<npho<<endl;
  cout<<"EM object is photon with pixel seed veto : "<<npho_px<<endl;
  cout<<"EM object is electron : "<<nele<<endl;
  cout<<"EM object is electron or photon with pixel seed veto : "<<nele_px<<endl;
  cout<<"Remaining EM object : "<<remain<<endl;
  cout<<"No. of entries survived: "<<nSurvived<<endl;
  cout<<"========================================"<<endl;
  cout<<"Cross-section : "<<CrossSection<<endl;
  cout<<"Weight ib pb-1 : "<<Weight<<endl;
}


TLorentzVector SkimmingSR::getBestPhoton(){
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

bool SkimmingSR::check_eMatchedtoGamma(TLorentzVector bestPhoton){
  for(int i=0;i<Electrons->size();i++)
    {
      if( bestPhoton.DeltaR((*Electrons)[i]) < 0.1)
        return true;
    }
  return false;
}

