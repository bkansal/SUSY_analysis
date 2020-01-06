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

  cout<<"Key words for if dataset is special: TTJets_DiLept, TTJets_SingleLeptFromT, V12"<<endl;
  Long64_t nSurvived = 0;
  double wt = 1.0;
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
    
    wt = Weight*1000.0;
    h_selectBaselineYields_->Fill("No cuts, evt in 1/fb",wt);

    //------ putting a cut on madHT for SingleLept and DiLept samples of TTbar. Do not use for other samples.
    if((s_data.Contains("TTJets_DiLept") 
	|| s_data.Contains("TTJets_SingleLeptFromT") )
       && madHT>600) continue;
    h_selectBaselineYields_->Fill("madHT cut",wt);
   
    if(s_data.Contains("V12")){//veto procedure if using V12 ntuples
      if(Muons->size()==0) h_selectBaselineYields_->Fill("0 #mu",wt);
      else continue;
      if(Electrons->size() == 0) h_selectBaselineYields_->Fill("0 electrons",wt);
      else continue;
    }
    else{//veto procedure if using V16 or above ntuples
      if(NMuons==0) h_selectBaselineYields_->Fill("0 #mu",wt);
      else continue;
      if(NElectrons==0) h_selectBaselineYields_->Fill("0 electrons",wt);
      else continue;
    }    

    // //apply iso track veto                                                                                                                                                                               
    if(isoElectronTracks==0 && isoMuonTracks ==0 && isoPionTracks==0)
      {
        h_selectBaselineYields_->Fill("Iso track",wt);
      }
    else continue;

    //about photons
    TLorentzVector bestPhoton=getBestPhoton();
    if(bestPhoton.Pt()>100)     h_selectBaselineYields_->Fill("Good #gamma with Pt > 100",wt);
    else continue;
    if( MET > 100 )        h_selectBaselineYields_->Fill("MET > 100",wt);
    else continue;
    //---------------------------------------------------------------------------------
    int minDRindx=-100,phoMatchingJetIndx=-100,nHadJets=0;
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
	if( !(minDR < 0.3 && i==minDRindx) )
	  hadJets.push_back((*Jets)[i]);
      }
    }
    if( minDR<0.3 ) phoMatchingJetIndx=minDRindx;
    for(int i=0;i<hadJets.size();i++){
      if( (abs(hadJets[i].Eta()) < 2.4) ){ST=ST+(hadJets[i].Pt());}
      if( (abs(hadJets[i].Eta()) < 2.4) ){nHadJets++;}
    }
    if( minDR<0.3 ) ST=ST+bestPhoton.Pt();//add the pt of photon if and only if there is a matching jet.
    //-----------------------------------------------------------------------
    // if( (nHadJets >= 2) )  h_selectBaselineYields_->Fill("nJets >=2",wt);
    // else continue;
    // if( (ST > 500) )       h_selectBaselineYields_->Fill("ST > 500",wt);
    // else continue;
    //end of select skimming parameters
    nSurvived++;
    newtree->Fill();
 
  } // loop over entries
  //  newtree->AutoSave();
  cout<<"No. of entries survived: "<<nSurvived<<endl;
}

TLorentzVector SkimmingSR::getBestPhoton(){
  TLorentzVector v1;
  vector<TLorentzVector> goodPho;
  for(int iPhoton=0;iPhoton<Photons->size();iPhoton++){
    if( ((*Photons_fullID)[iPhoton]) && ((*Photons_hasPixelSeed)[iPhoton]<0.001) ) goodPho.push_back( (*Photons)[iPhoton] );
  }

  if(goodPho.size()==0) return v1;
  sortTLorVec(&goodPho);
  return goodPho[0];
  
}