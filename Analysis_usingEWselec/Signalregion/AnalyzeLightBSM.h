#ifndef AnalyzeLightBSM_H
#define AnalyzeLightBSM_H
#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include "NtupleVariables.h"
#include "TH1F.h"
#include "TH2.h"
#include <TProfile.h>
#include "TFile.h"
#include "TLorentzVector.h"
#include "TDirectory.h"
#include"TGraphErrors.h"
#include"TGraphAsymmErrors.h"

class AnalyzeLightBSM : public NtupleVariables{

 public:
  AnalyzeLightBSM(const TString &inputFileList="foo.txt", const char *outFileName="histo.root",const char *dataset="data");
  ~AnalyzeLightBSM();
  Bool_t   FillChain(TChain *chain, const TString &inputFileList);
  Long64_t LoadTree(Long64_t entry);
  void     EventLoop(const char *,const char *);
  void     BookHistogram(const char *);
  TLorentzVector getBestPhoton();
  int getBinNoV4(int);
  int getBinNoV7(int);
  int getBinNoV6(int);
  double getGendRLepPho();
  bool check_eMatchedtoGamma();
  void print(Long64_t);
  void findObjMatchedtoG(TLorentzVector);

  //Variables defined
  int bestPhotonIndxAmongPhotons=-100;
  float HT_PtCut=30;
  float MHT_PtCut=30;//keep MHT_PtCut <= HT_PtCut and <= Njets_PtCut
  float Njets_PtCut=30;

  float HT_EtaCut=2.4;
  float MHT_EtaCut=5;
  float Njets_EtaCut=2.4;
  double wt=0,lumiInfb=35.9;//35.86;//36.814;//35.862824;//36.814;
  bool isSignal=false;
  //vector<double> HTBinLowEdge ={0,500,550,600,650,700,750,800,900,1000,1100,1200,1400,1600,1800,2000,2400,2800,3200};
  //  vector<double> HTBinLowEdge ={0,100,200,300,400,500,600,700,800,900,1000,1200,1500,2000,2500};
  //  vector<double> MHTBinLowEdge={0,20,40,60,80,100,120,160,200,270,350,500};
  vector<double> STBinLowEdge ={0,200,220,240,260,300,360,420,500,600,700,850,1000,1200,1500,2000,2500,3000};
  // vector<double> METLowEdge={0,20,40,60,80,100,120,160,200,220,240,260,300,340,380,420,480,520,560,600,660,720,800,900,1000,1200};
  vector<double> METLowEdge={200,270,350,450,750,2000};
  vector<double> METLowEdge1={100,200,270,350,450,750,2000};
  vector<double> METLowEdge2={100,200,270,350,450,2000};
  /* vector<double> METLowEdge1={200,270,350,450,750,2000}; */
  /* vector<double> METLowEdge2={200,270,350,450,2000}; */
  // vector<double> METLowEdge1={0,20,40,60,80,100,120,160,200,220,240,260,300,340,380,420,460,520,580,640,700,780,860,940,1000,1200};
  // vector<double> METLowEdge2={0,20,40,60,80,100,120,160,200,220,240,260,280,300,340,380,420,480,540,600,700,800,900,1000,1200};
  // vector<double> METLowEdge={0,200,210,220,240,260,280,300,320,340,360,380,400,450,500,600,1000,1400};
  vector<double> METBinLowEdgeV4_njLow={0,100,125,160,200,270,350,450,750,900};//{0,100,200,270,350,450,750,900}; 
  vector<double> METBinLowEdgeV4={0,100,125,160,200,270,350,450,750};
  vector<double> METBinLowEdgeV7_njLow={0,100,200,270,350,450,750,900};
  vector<double> METBinLowEdgeV7={0,100,200,270,350,450,750};

  vector<double> METBinLowEdge={0,20,40,60,80,100,125,160,200,270,350,500,600};
  vector<double> METBinLowEdge2bJ={0,20,40,60,80,100,125,160,200,270,350,500};
  vector<double> METBinLowEdge2={0,20,40,60,80,100,120,160,200,270,350,450,500};
  vector<double> PhoLowEdge={0,100,120,140,160,180,200,220,250,280,320,380,450,550,650,750};
  vector<double> PhoLowEdge1={0,100,120,140,160,180,200,220,250,280,320,380,450,550,650,750,800,1000,1200};
  vector<double> PhoLowEdge2={0,100,120,140,160,180,200,220,250,280,320,380,450,550,650,750,800,900,1000,1100,1200};
  //vector<double> BestPhotonPtBinLowEdge={0,100,120,140,160,200,250,300,350,400,500,600};
  vector<TLorentzVector> allBestPhotons;
  //histograms

  TH1D *h_nEvts;
  TH1I *h_RunNum;
  TH1D *h_intLumi;
  TH1D *h_ST;
  TH1D *h_MET;
  TH1D *h_BTags;
  TH1D *h_BestPhotonPt;
  TH1D *h_nJets;

  TH1D *h_intLumi_EW;
  TH1D *h_ST_EW;
  TH1D *h_MET_EW;
  TH1D *h_BTags_EW;
  TH1D *h_BestPhotonPt_EW;
  TH1D *h_nJets_EW;

  TH1D *h_intLumi_SP;
  TH1D *h_ST_SP;
  TH1D *h_MET_SP;
  TH1D *h_BTags_SP;
  TH1D *h_BestPhotonPt_SP;
  TH1D *h_nJets_SP;

  TH1D *h_intLumi_2018;
  TH1D *h_ST_2018;
  TH1D *h_MET_2018;
  TH1D *h_BTags_2018;
  TH1D *h_BestPhotonPt_2018;
  TH1D *h_nJets_2018;

  TH1D *h_dR_q_b_matched;
  TH1D *h_GenWpt;
  TH1D *h_GenWeta;
  TH1D *h_GenWpt1;
  TH1D *h_GenWpt1_1;
  TH1D *h_GenWM1_1;
  TH1D *h_GenWeta1;
  TH1D *h_GenWpt2_1;
  TH1D *h_GenWeta2_1;
  TH1D *h_GenWM2_1;
  TH1D *h_GenWpt2_2;
  TH1D *h_GenWM2_2;
  TH1D *h_GenWeta2_2;
  TH1D *h_GenWpt2;
  TH1D *h_GenWeta2;

  TH2D *h2_PtPhotonvsMET;
  TH2D *h2_GenPhotonvsGenMET;
  TH2D *h2_GenWvsnjet;
  TH1D *h_mTPhoMET;
  TH1D *h_METvBin;
  TH1D *h_METvBin_EW;
  TH1D *h_METvBin_SP;
  TH1D *h_METvBin_nocut;
  TH1D *h_METvBin1;
  TH1D *h_METvBin_nocut1;
  TH1D *h_METvBin2;
  TH1D *h_METvBin_nocut2;
  TH1D *h_MET_nj1;
  TH1D *h_METvBin_nj1;
  TH1D *h_METvBin1_nj1;
  TH1D *h_METvBin2_nj1;
  TH1D *h_MET_nj2to4_nbjet0;
  TH1D *h_METvBin_nj2to4_nbjet0;
  TH1D *h_METvBin1_nj2to4_nbjet0;
  TH1D *h_METvBin2_nj2to4_nbjet0;
  TH1D *h_MET_nj5to6_nbjet0;
  TH1D *h_METvBin_nj5to6_nbjet0;
  TH1D *h_METvBin1_nj5to6_nbjet0;
  TH1D *h_METvBin2_nj5to6_nbjet0;
  TH1D *h_MET_nj7toinf_nbjet0;
  TH1D *h_METvBin_nj7toinf_nbjet0;
  TH1D *h_METvBin1_nj7toinf_nbjet0;
  TH1D *h_METvBin2_nj7toinf_nbjet0;

  TH1D *h_MET_nj2to4_nbjet1;
  TH1D *h_METvBin_nj2to4_nbjet1;
  TH1D *h_METvBin1_nj2to4_nbjet1;
  TH1D *h_METvBin2_nj2to4_nbjet1;
  TH1D *h_MET_nj5to6_nbjet1;
  TH1D *h_METvBin_nj5to6_nbjet1;
  TH1D *h_METvBin1_nj5to6_nbjet1;
  TH1D *h_METvBin2_nj5to6_nbjet1;
  TH1D *h_MET_nj7toinf_nbjet1;
  TH1D *h_METvBin_nj7toinf_nbjet1;
  TH1D *h_METvBin1_nj7toinf_nbjet1;
  TH1D *h_METvBin2_nj7toinf_nbjet1;

  TH1D *h_MET_nj2to4_nbjetnot0;
  TH1D *h_METvBin_nj2to4_nbjetnot0;
  TH1D *h_METvBin1_nj2to4_nbjetnot0;
  TH1D *h_METvBin2_nj2to4_nbjetnot0;
  TH1D *h_MET_nj5to6_nbjetnot0;
  TH1D *h_METvBin_nj5to6_nbjetnot0;
  TH1D *h_METvBin1_nj5to6_nbjetnot0;
  TH1D *h_METvBin2_nj5to6_nbjetnot0;
  TH1D *h_MET_nj7toinf_nbjetnot0;
  TH1D *h_METvBin_nj7toinf_nbjetnot0;
  TH1D *h_METvBin1_nj7toinf_nbjetnot0;
  TH1D *h_METvBin2_nj7toinf_nbjetnot0;

  TH1D *h_PhovBin;
  TH1D *h_PhovBin_nocut;
  TH1D *h_PhovBin1;
  TH1D *h_PhovBin_nocut1;
  TH1D *h_PhovBin2;
  TH1D *h_PhovBin_nocut2;
  TH1D *h_hadAk8Mass;
  TH1D *h_hadAk8Mass_matchedW;
  TH1D *h_hadAk8Mass_EW_nAk8jet_ge1;
  TH1D *h_hadAk8Mass_EW;
  TH1D *h_hadAk8Mass_SP;
  TH1D *h_hadAk8Mass_Ak8jet0;
  TH1D *h_hadAk8Pt;
  TH1D *h_hadAk8Pt_matchedW;
  TH1D *h_hadAk8Pt_EW_nAk8jet_ge1;
  TH1D *h_hadAk8Pt_EW;
  TH1D *h_hadAk8Pt_SP;
  TH1D *h_hadAk8Pt_Ak8jet0;
  TH1D *h_nHadJets_nAk8jet_ge1;
  TH1D *h_nHadAk8Jets_nAk8jet_ge1;
  TH1D *h_BTags_nAk8jet_ge1;
  TH1D *h_BTags_nAk8jet1;
  TH1D *h_BTags_nAk8jet2;
  TH1D *h_BTags_nAk8jet3;
  /* TH2D *h2_STvsHT; */

  /* TH1D *h_dPhi_METBestPhoton; */
  TH1D *h_dPhi_METjet1;
  TH1D *h_dPhi_METjet2;
  TH1D *h_dPhi_phojet1;
  TH1D *h_dPhi_phojet2;
  TH1D *h_dPhi_phoMET;

  //for numerator
  TH1D *h_nEvts_num;
  TH1I *h_RunNum_num;
  TH1D *h_intLumi_num;
  TH1D *h_ST_num;
  TH1D *h_MET_num;
  /* TH1D *h_nHadJets_num; */
  TH1D *h_BTags_num;
  TH1D *h_BestPhotonPt_num;

  /* TH1D *h_HT_num; */
  /* TH1D *h_MHT_num; */
  /* TH1D *h_MHTstar_num; */
  TH1D *h_nJets_num;
  TH1D *h_dR_jetandW;
  TH1D *h_dR_jet1andW;
  TH1D *h_dR_jet2andW;
  TH1D *h_dR_jet1andjet2;
  TH1D *h_dR_Genpho_Genjet;
  TH2D *h2_PtPhotonvsMET_num;
  TH1D *h_mTPhoMET_num;

  /* TH2D *h2_STvsHT_num; */

  /* TH1D *h_dPhi_METBestPhoton_num; */
  TH1D *h_dPhi_METjet1_num;
  TH1D *h_dPhi_METjet2_num;
  TH1D *h_dPhi_phojet1_num;
  TH1D *h_dPhi_phojet2_num;
  TH1D *h_dPhi_phoMET_num;
  TGraphAsymmErrors *h_MET_eff;
  TGraphAsymmErrors *h_nJets_eff;
  TGraphAsymmErrors *h_BestPhotonPt_eff;

  //for numerator1
  TH1D *h_nEvts_nocut;
  TH1I *h_RunNum_nocut;
  TH1D *h_intLumi_nocut;
  TH1D *h_ST_nocut;
  TH1D *h_MET_nocut;
  /* TH1D *h_nHadJets_nocut; */
  TH1D *h_BTags_nocut;
  TH1D *h_BestPhotonPt_nocut;

  /* TH1D *h_HT_nocut; */
  /* TH1D *h_MHT_nocut; */
  /* TH1D *h_MHTstar_nocut; */
  TH1D *h_nJets_nocut;

  TH2D *h2_PtPhotonvsMET_nocut;
  TH1D *h_mTPhoMET_nocut;

  /* TH2D *h2_STvsHT_nocut; */

  /* TH1D *h_dPhi_METBestPhoton_nocut; */
  TH1D *h_dPhi_METjet1_nocut;
  TH1D *h_dPhi_METjet2_nocut;
  TH1D *h_dPhi_phojet1_nocut;
  TH1D *h_dPhi_phojet2_nocut;
  TH1D *h_dPhi_phoMET_nocut;
  TGraphAsymmErrors *h_MET_eff1;
  TGraphAsymmErrors *h_nJets_eff1;
  TGraphAsymmErrors *h_BestPhotonPt_eff1;
  TH1F *h_selectBaselineYields_;
  TH1F *h_selectBaselineYields_2;

  TH1D *h_GmatchedObj;
  TH1D *h_PdgIdPhoParent;

  TH1D *h_SBins_v7_CD;
  TH1D *h_SBins_v7_CD_EW;
  TH1D *h_SBins_v7_CD_SP;
  TH1D *h_SBins_v7_CD_2018;
  
  TFile *oFile;
  
};
#endif

#ifdef AnalyzeLightBSM_cxx

void AnalyzeLightBSM::BookHistogram(const char *outFileName) {

  //  char hname[200], htit[200];
  //  double xlow = 0.0,  xhigh = 2000.0;
  //  int nbins = 2000;
  char name[100],title[100];
 
  oFile = new TFile(outFileName, "recreate");
  TH1::SetDefaultSumw2(1);
  h_selectBaselineYields_ = new TH1F("cutflows","cutflows",12,-0.5,12.5);
  h_selectBaselineYields_2 = new TH1F("cutflows2","cutflows2",12,-0.5,12.5);
  h_nEvts=new TH1D("nEvents","no. of events in this tree",4,0,4);
  h_RunNum=new TH1I("runs","Run nos.",300000,0,300000);

  h_intLumi=new TH1D("intLumi","integrated luminosity in /fb",10000,25,200); 
  h_ST=new TH1D("ST","ST",400,0,4000);
  h_MET=new TH1D("MET","MET",200,0,2000);
  h_BTags=new TH1D("nBTags","no. of B tags",10,0,10);
  h_BestPhotonPt=new TH1D("BestPhotonPt","Pt of the Best Photon",150,0,1500);
  h_nJets=new TH1D("nJets","nJets",25,0,25);

  h_intLumi_EW=new TH1D("intLumi_EW","2016 integrated luminosity in /fb",2500,25,50); 
  h_ST_EW=new TH1D("ST_EW","ST 2016",400,0,4000);
  h_MET_EW=new TH1D("MET_EW","MET 2016",200,0,2000);
  h_BTags_EW=new TH1D("nBTags_EW","no. of B tags 2016",10,0,10);
  h_BestPhotonPt_EW=new TH1D("BestPhotonPt_EW","Pt of the Best Photon 2016",150,0,1500);
  h_nJets_EW=new TH1D("nJets_EW","nJets 2016",25,0,25);

  h_intLumi_SP=new TH1D("intLumi_SP","integrated luminosity in /fb",2500,25,50); 
  h_ST_SP=new TH1D("ST_SP","ST",400,0,4000);
  h_MET_SP=new TH1D("MET_SP","MET",200,0,2000);
  h_BTags_SP=new TH1D("nBTags_SP","no. of B tags",10,0,10);
  h_BestPhotonPt_SP=new TH1D("BestPhotonPt_SP","Pt of the Best Photon",150,0,1500);
  h_nJets_SP=new TH1D("nJets_SP","nJets",25,0,25);

  h_intLumi_2018=new TH1D("intLumi_2018","integrated luminosity in /fb",2500,25,50); 
  h_ST_2018=new TH1D("ST_2018","ST",400,0,4000);
  h_MET_2018=new TH1D("MET_2018","MET",200,0,2000);
  h_BTags_2018=new TH1D("nBTags_2018","no. of B tags",10,0,10);
  h_BestPhotonPt_2018=new TH1D("BestPhotonPt_2018","Pt of the Best Photon",150,0,1500);
  h_nJets_2018=new TH1D("nJets_2018","nJets",25,0,25);

  h_GenWpt=new TH1D("GenWpt","Gen W Pt",200,0,2000);
  h_GenWeta=new TH1D("GenWeta","Gen W #eta",200,0,5);
  h_GenWpt1=new TH1D("GenWpt1","Gen W Pt (for events only have 1 had jet)",200,0,2000);
  h_GenWM1_1=new TH1D("GenWM1_1","Jet Mass (for events only have 1 had jet)",200,0,200);
  h_GenWpt1_1=new TH1D("GenWpt1_1","Jet Pt (for events only have 1 had jet)",200,0,2000);
  h_GenWeta1=new TH1D("GenWeta1","Gen W #eta (for events only have 1 had jet)",200,0,5);
  h_GenWpt2_1=new TH1D("GenWpt2_1","Jet1 Pt  (for events only have 2 had jet)",200,0,2000);
  h_GenWeta2_1=new TH1D("GenWeta2_1","Jet1 #eta (for events only have 2 had jet)",200,0,5);
  h_GenWM2_1=new TH1D("GenWM2_1","Jet1 Mass  (for events only have 2 had jet)",200,0,200);
  h_GenWpt2_2=new TH1D("GenWpt2_2","Jet2 Pt (for events only have 2 had jet)",200,0,2000);
  h_GenWeta2_2=new TH1D("GenWeta2_2","Jet2 #eta (for events only have 2 had jet)",200,0,5);
  h_GenWM2_2=new TH1D("GenWM2_2","Jet2 Mass  (for events only have 2 had jet)",200,0,200);
  h_GenWpt2=new TH1D("GenWpt2","Gen W Pt (for events only have 2 had jet)",200,0,2000);
  h_GenWeta2=new TH1D("GenWeta2","Gen W #eta (for events only have 2 had jet)",200,0,5);
  /* h_nHadJets=new TH1D("nHadJets","no. of jets(only hadronic jets,not counting photon)",25,0,25); */
  h_BTags_nAk8jet1=new TH1D("BTags_nAk8jet1","no. of b jets in events having 1 Ak8 jets (atleast 1 Ak8 jet mass in 65 GeV - 100 GeV range)",25,0,25);
  h_BTags_nAk8jet2=new TH1D("BTags_nAk8jet2","no. of b jets in events having 2 Ak8 jets (atleast 1 Ak8 jet mass in 65 GeV - 100 GeV range)",25,0,25);
  h_BTags_nAk8jet3=new TH1D("BTags_nAk8jet3","no. of b jets in events having 3 Ak8 jets (atleast 1 Ak8 jet mass in 65 GeV - 100 GeV range)",25,0,25);
  h_BTags_nAk8jet_ge1=new TH1D("BTags_nAk8jet_ge1","no. of b jets (after atleast 1 Ak8 jet mass in 65 GeV - 100 GeV range)",25,0,25);
  h_nHadJets_nAk8jet_ge1=new TH1D("nHadJets_nAk8jet_ge1","no. of Ak4  jets (after atleast 1 Ak8 jet mass in 65 GeV - 100 GeV range)",25,0,25);
  h_nHadAk8Jets_nAk8jet_ge1=new TH1D("nHadAk8Jets_nAk8jet_ge1","no. of Ak8  jets (after atleast 1 Ak8 jet mass in 65 GeV - 100 GeV range)",25,0,25);
  h_hadAk8Mass=new TH1D("hadAk8Mass","Soft dropped Mass of AK8 Jet",1000,0,200);
  h_hadAk8Mass_matchedW=new TH1D("hadAk8Mass_matchedW","Soft dropped Mass of AK8 Jet which are matched with W ",1000,0,200);
  h_hadAk8Mass_Ak8jet0=new TH1D("hadAk8Mass_Ak8jet0","Soft dropped Mass of leading AK8 Jet",1000,0,200);
  h_hadAk8Mass_EW=new TH1D("hadAk8Mass_EW","Soft dropped Mass of AK8 Jet",1000,0,200);
  h_hadAk8Mass_EW_nAk8jet_ge1=new TH1D("hadAk8Mass_EW_nAk8jet_ge1","Soft dropped Mass of AK8 Jet after atleast 1 Ak8 jet mass in 65 GeV - 100 GeV range",1000,0,200);
  h_hadAk8Mass_SP=new TH1D("hadAk8Mass_SP","Soft dropped Mass of AK8 Jet",1000,0,200);
  h_hadAk8Pt=new TH1D("hadAk8Pt","Soft dropped Pt of AK8 Jet",2000,0,1000);
  h_hadAk8Pt_matchedW=new TH1D("hadAk8Pt_matchedW"," Pt of AK8 Jet which are matched with W",2000,0,1000);
  h_hadAk8Pt_Ak8jet0=new TH1D("hadAk8Pt_Ak8jet0","Soft dropped Pt of leading AK8 Jet",2000,0,1000);
  h_hadAk8Pt_EW=new TH1D("hadAk8Pt_EW","Soft dropped Pt of AK8 Jet",2000,0,1000);
  h_hadAk8Pt_EW_nAk8jet_ge1=new TH1D("hadAk8Pt_EW_nAk8jet_ge1 ","Soft dropped Pt of AK8 Jet after atleast 1 Ak8 jet mass in 65 GeV - 100 GeV range",2000,0,1000);
  h_hadAk8Pt_SP=new TH1D("hadAk8Pt_SP","Soft dropped Pt of AK8 Jet",2000,0,1000);

  /* h_HT=new TH1D("HT","HT",400,0,4000); */
  /* h_MHT=new TH1D("MHT","MHT",200,0,2000); */
  /* h_MHTstar=new TH1D("MHTstar","MHT calculated using ST like definition",200,0,2000); */
  
  h2_PtPhotonvsMET=new TH2D("BestPhotonPtvsMET","Best photon Pt vs MET",150,0,1500,200,0,2000);
  h2_GenPhotonvsGenMET=new TH2D("GenPhotonvsGenMET","Gen photon Pt vs GenMET",150,0,1500,200,0,2000);
  h2_GenWvsnjet=new TH2D("GenWvsnjet","Gen W Pt vs njets",150,0,1500,20,0,20);
  h_mTPhoMET=new TH1D("mTPhoMET","mT b/w bestPhoton and MET",200,0,2000);

  h_dPhi_METjet1=new TH1D("dPhi_METjet1","dphi between MET Vec and Jet1",40,0,4);
  h_dPhi_METjet2=new TH1D("dPhi_METjet2","dphi between MET Vec and Jet2",40,0,4);
  h_dPhi_phojet1=new TH1D("dPhi_phojet1","dphi between photon and Jet1",40,0,4);
  h_dPhi_phojet2=new TH1D("dPhi_phojet2","dphi between photon and Jet2",40,0,4);
  h_dPhi_phoMET=new TH1D("dPhi_phoMET","dphi between photon and MET",40,0,4);
  h_dR_jetandW=new TH1D("dR_jetandW","dR between jet and W (for events only have 1 had jet)",200,0,5);
  h_dR_jet1andW=new TH1D("dR_jet1andW","dR between jet1 and W (for events only have 2 had jet)",200,0,5);
  h_dR_jet2andW=new TH1D("dR_jet2andW","dR between jet2 and W (for events only have 2 had jet)",200,0,5);
  h_dR_jet1andjet2=new TH1D("dR_jet1andjet2","dR between jet1 and jet2 (for events only have 2 had jet)",200,0,5);
  h_dR_Genpho_Genjet=new TH1D("dR_Genpho_Genjet","dR between gen photon and gen jet",100,0,5);
  h_dR_q_b_matched=new TH1D("dR_q_b_matched","dR between gen b quark and gen jet from W",100,0,5);


  // for numerator

  h_nEvts_num=new TH1D("nEvents_num","no. of events in this tree (for numerator)",4,0,4);
  h_RunNum_num=new TH1I("runs_num","Run nos.",300000,0,300000);
  h_intLumi_num=new TH1D("intLumi_num","integrated luminosity in /fb",2500,25,50); 
  h_ST_num=new TH1D("ST_num","ST",400,0,4000);
  h_MET_num=new TH1D("MET_num","MET",200,0,2000);
  /* h_nHadJets_num=new TH1D("nHadJets_num","no. of jets(only hadronic jets,not counting photon)",25,0,25); */
  h_BTags_num=new TH1D("nBTags_num","no. of B tags",10,0,10);
  h_BestPhotonPt_num=new TH1D("BestPhotonPt_num","Pt of the Best Photon",150,0,1500);
  h_METvBin=new TH1D("METvBin","MET in variable bins",METLowEdge.size()-1,&(METLowEdge[0]));
  h_METvBin_EW=new TH1D("METvBin_EW","MET in variable bins after EW selctions",METLowEdge.size()-1,&(METLowEdge[0]));
  h_METvBin_SP=new TH1D("METvBin_SP","MET in variable bins after SP elections",METLowEdge.size()-1,&(METLowEdge[0]));
  h_METvBin_nocut=new TH1D("METvBin_nocut","MET in variable bins without any cut",METLowEdge.size()-1,&(METLowEdge[0]));
  h_METvBin1=new TH1D("METvBin1","MET in variable bins",METLowEdge1.size()-1,&(METLowEdge1[0]));
  h_METvBin_nocut1=new TH1D("METvBin_nocut1","MET in variable bins without any cut",METLowEdge1.size()-1,&(METLowEdge1[0]));
  h_METvBin2=new TH1D("METvBin2","MET in variable bins",METLowEdge2.size()-1,&(METLowEdge2[0]));
  h_METvBin_nocut2=new TH1D("METvBin_nocut2","MET in variable bins without any cut",METLowEdge2.size()-1,&(METLowEdge2[0]));

  h_MET_nj1=new TH1D("MET_nj1","MET",200,0,1200);  
  h_METvBin_nj1=new TH1D("METvBin_nj1","MET in variable bins",METLowEdge.size()-1,&(METLowEdge[0]));
  h_METvBin1_nj1=new TH1D("METvBin1_nj1","MET in variable bins",METLowEdge1.size()-1,&(METLowEdge1[0]));
  h_METvBin2_nj1=new TH1D("METvBin2_nj1","MET in variable bins",METLowEdge2.size()-1,&(METLowEdge2[0]));

  h_MET_nj2to4_nbjet0=new TH1D("MET_nj2to4_nbjet0","MET",200,0,1200);  
  h_METvBin_nj2to4_nbjet0=new TH1D("METvBin_nj2to4_nbjet0","MET in variable bins",METLowEdge.size()-1,&(METLowEdge[0]));
  h_METvBin1_nj2to4_nbjet0=new TH1D("METvBin1_nj2to4_nbjet0","MET in variable bins",METLowEdge1.size()-1,&(METLowEdge1[0]));
  h_METvBin2_nj2to4_nbjet0=new TH1D("METvBin2_nj2to4_nbjet0","MET in variable bins",METLowEdge2.size()-1,&(METLowEdge2[0]));

  h_MET_nj5to6_nbjet0=new TH1D("MET_nj5to6_nbjet0","MET",200,0,1200);  
  h_METvBin_nj5to6_nbjet0=new TH1D("METvBin_nj5to6_nbjet0","MET in variable bins",METLowEdge.size()-1,&(METLowEdge[0]));
  h_METvBin1_nj5to6_nbjet0=new TH1D("METvBin1_nj5to6_nbjet0","MET in variable bins",METLowEdge1.size()-1,&(METLowEdge1[0]));
  h_METvBin2_nj5to6_nbjet0=new TH1D("METvBin2_nj5to6_nbjet0","MET in variable bins",METLowEdge2.size()-1,&(METLowEdge2[0]));

  h_MET_nj7toinf_nbjet0=new TH1D("MET_nj7toinf_nbjet0","MET",200,0,1200);  
  h_METvBin_nj7toinf_nbjet0=new TH1D("METvBin_nj7toinf_nbjet0","MET in variable bins",METLowEdge.size()-1,&(METLowEdge[0]));
  h_METvBin1_nj7toinf_nbjet0=new TH1D("METvBin1_nj7toinf_nbjet0","MET in variable bins",METLowEdge1.size()-1,&(METLowEdge1[0]));
  h_METvBin2_nj7toinf_nbjet0=new TH1D("METvBin2_nj7toinf_nbjet0","MET in variable bins",METLowEdge2.size()-1,&(METLowEdge2[0]));

  h_MET_nj2to4_nbjet1=new TH1D("MET_nj2to4_nbjet1","MET",200,0,1200);  
  h_METvBin_nj2to4_nbjet1=new TH1D("METvBin_nj2to4_nbjet1","MET in variable bins",METLowEdge.size()-1,&(METLowEdge[0]));
  h_METvBin1_nj2to4_nbjet1=new TH1D("METvBin1_nj2to4_nbjet1","MET in variable bins",METLowEdge1.size()-1,&(METLowEdge1[0]));
  h_METvBin2_nj2to4_nbjet1=new TH1D("METvBin2_nj2to4_nbjet1","MET in variable bins",METLowEdge2.size()-1,&(METLowEdge2[0]));

  h_MET_nj5to6_nbjet1=new TH1D("MET_nj5to6_nbjet1","MET",200,0,1200);  
  h_METvBin_nj5to6_nbjet1=new TH1D("METvBin_nj5to6_nbjet1","MET in variable bins",METLowEdge.size()-1,&(METLowEdge[0]));
  h_METvBin1_nj5to6_nbjet1=new TH1D("METvBin1_nj5to6_nbjet1","MET in variable bins",METLowEdge1.size()-1,&(METLowEdge1[0]));
  h_METvBin2_nj5to6_nbjet1=new TH1D("METvBin2_nj5to6_nbjet1","MET in variable bins",METLowEdge2.size()-1,&(METLowEdge2[0]));

  h_MET_nj7toinf_nbjet1=new TH1D("MET_nj7toinf_nbjet1","MET",200,0,1200);  
  h_METvBin_nj7toinf_nbjet1=new TH1D("METvBin_nj7toinf_nbjet1","MET in variable bins",METLowEdge.size()-1,&(METLowEdge[0]));
  h_METvBin1_nj7toinf_nbjet1=new TH1D("METvBin1_nj7toinf_nbjet1","MET in variable bins",METLowEdge1.size()-1,&(METLowEdge1[0]));
  h_METvBin2_nj7toinf_nbjet1=new TH1D("METvBin2_nj7toinf_nbjet1","MET in variable bins",METLowEdge2.size()-1,&(METLowEdge2[0]));

  h_MET_nj2to4_nbjetnot0=new TH1D("MET_nj2to4_nbjetnot0","MET",200,0,1200);  
  h_METvBin_nj2to4_nbjetnot0=new TH1D("METvBin_nj2to4_nbjetnot0","MET in variable bins",METLowEdge.size()-1,&(METLowEdge[0]));
  h_METvBin1_nj2to4_nbjetnot0=new TH1D("METvBin1_nj2to4_nbjetnot0","MET in variable bins",METLowEdge1.size()-1,&(METLowEdge1[0]));
  h_METvBin2_nj2to4_nbjetnot0=new TH1D("METvBin2_nj2to4_nbjetnot0","MET in variable bins",METLowEdge2.size()-1,&(METLowEdge2[0]));

  h_MET_nj5to6_nbjetnot0=new TH1D("MET_nj5to6_nbjetnot0","MET",200,0,1200);  
  h_METvBin_nj5to6_nbjetnot0=new TH1D("METvBin_nj5to6_nbjetnot0","MET in variable bins",METLowEdge.size()-1,&(METLowEdge[0]));
  h_METvBin1_nj5to6_nbjetnot0=new TH1D("METvBin1_nj5to6_nbjetnot0","MET in variable bins",METLowEdge1.size()-1,&(METLowEdge1[0]));
  h_METvBin2_nj5to6_nbjetnot0=new TH1D("METvBin2_nj5to6_nbjetnot0","MET in variable bins",METLowEdge2.size()-1,&(METLowEdge2[0]));

  h_MET_nj7toinf_nbjetnot0=new TH1D("MET_nj7toinf_nbjetnot0","MET",200,0,1200);  
  h_METvBin_nj7toinf_nbjetnot0=new TH1D("METvBin_nj7toinf_nbjetnot0","MET in variable bins",METLowEdge.size()-1,&(METLowEdge[0]));
  h_METvBin1_nj7toinf_nbjetnot0=new TH1D("METvBin1_nj7toinf_nbjetnot0","MET in variable bins",METLowEdge1.size()-1,&(METLowEdge1[0]));
  h_METvBin2_nj7toinf_nbjetnot0=new TH1D("METvBin2_nj7toinf_nbjetnot0","MET in variable bins",METLowEdge2.size()-1,&(METLowEdge2[0]));

  
  h_PhovBin=new TH1D("PhovBin","Pho in variable bins",PhoLowEdge.size()-1,&(PhoLowEdge[0]));
  h_PhovBin_nocut=new TH1D("PhovBin_nocut","Pho in variable bins without any cut",PhoLowEdge.size()-1,&(PhoLowEdge[0]));
  h_PhovBin1=new TH1D("PhovBin1","Pho in variable bins",PhoLowEdge1.size()-1,&(PhoLowEdge1[0]));
  h_PhovBin_nocut1=new TH1D("PhovBin_nocut1","Pho in variable bins without any cut",PhoLowEdge1.size()-1,&(PhoLowEdge1[0]));
  h_PhovBin2=new TH1D("PhovBin2","Pho in variable bins",PhoLowEdge2.size()-1,&(PhoLowEdge2[0]));
  h_PhovBin_nocut2=new TH1D("PhovBin_nocut2","Pho in variable bins without any cut",PhoLowEdge2.size()-1,&(PhoLowEdge2[0]));

  /* h_HT_num=new TH1D("HT_num","HT",400,0,4000); */
  /* h_MHT_num=new TH1D("MHT_num","MHT",200,0,2000); */
  h_nJets_num=new TH1D("nJets_num","nJets",25,0,25);
  /* h_MHTstar_num=new TH1D("MHTstar_num","MHT calculated using ST like definition",200,0,2000); */
  
  /* h2_PtPhotonvsMET_num=new TH2D("BestPhotonPtvsMET_num","Best photon Pt vs MET",150,0,1500,200,0,2000); */
  h_mTPhoMET_num=new TH1D("mTPhoMET_num","mT b/w bestPhoton and MET",200,0,2000);

  h_dPhi_METjet1_num=new TH1D("dPhi_METjet1_num","dphi between MET Vec and Jet1",40,0,4);
  h_dPhi_METjet2_num=new TH1D("dPhi_METjet2_num","dphi between MET Vec and Jet2",40,0,4);
  h_dPhi_phojet1_num=new TH1D("dPhi_phojet1_num","dphi between photon and Jet1",40,0,4);
  h_dPhi_phojet2_num=new TH1D("dPhi_phojet2_num","dphi between photon and Jet2",40,0,4);
  h_dPhi_phoMET_num=new TH1D("dPhi_phoMET_num","dphi between photon and MET",40,0,4);


  // for numerator1

  h_nEvts_nocut=new TH1D("nEvents_nocut","no. of events in this tree (for num1erator)",4,0,4);
  h_RunNum_nocut=new TH1I("runs_nocut","Run nos.",300000,0,300000);
  h_intLumi_nocut=new TH1D("intLumi_nocut","integrated luminosity in /fb",2500,25,50); 
  h_ST_nocut=new TH1D("ST_nocut","ST",400,0,4000);
  h_MET_nocut=new TH1D("MET_nocut","MET",200,0,2000);
  /* h_nHadJets_nocut=new TH1D("nHadJets_nocut","no. of jets(only hadronic jets,not counting photon)",25,0,25); */
  h_BTags_nocut=new TH1D("nBTags_nocut","no. of B tags",10,0,10);
  h_BestPhotonPt_nocut=new TH1D("BestPhotonPt_nocut","Pt of the Best Photon",150,0,1500);

  /* h_HT_nocut=new TH1D("HT_nocut","HT",400,0,4000); */
  /* h_MHT_nocut=new TH1D("MHT_nocut","MHT",200,0,2000); */
  h_nJets_nocut=new TH1D("nJets_nocut","nJets",25,0,25);
  /* h_MHTstar_nocut=new TH1D("MHTstar_nocut","MHT calculated using ST like definition",200,0,2000); */
  
  h2_PtPhotonvsMET_nocut=new TH2D("BestPhotonPtvsMET_nocut","Best photon Pt vs MET",150,0,1500,200,0,2000);
  // h2_PtPhotonvsMET=new TH2D("BestPhotonPtvsMET","Best photon Pt vs MET",150,0,1500,200,0,2000);
  h_mTPhoMET_nocut=new TH1D("mTPhoMET_nocut","mT b/w bestPhoton and MET",200,0,2000);

  h_dPhi_METjet1_nocut=new TH1D("dPhi_METjet1_nocut","dphi between MET Vec and Jet1",40,0,4);
  h_dPhi_METjet2_nocut=new TH1D("dPhi_METjet2_nocut","dphi between MET Vec and Jet2",40,0,4);
  h_dPhi_phojet1_nocut=new TH1D("dPhi_phojet1_nocut","dphi between photon and Jet1",40,0,4);
  h_dPhi_phojet2_nocut=new TH1D("dPhi_phojet2_nocut","dphi between photon and Jet2",40,0,4);
  h_dPhi_phoMET_nocut=new TH1D("dPhi_phoMET_nocut","dphi between photon and MET",40,0,4);
  

  h_GmatchedObj=new TH1D("GmatchedObj","Gen Obj close to Reco-Gamma",62,-0.75,30.25);
  h_PdgIdPhoParent = new TH1D("PdgIdPhoParent","PdgID of the Photon's parent",62,-0.75,30.25);

  h_SBins_v7_CD = new TH1D("AllSBins_v7_CD","search bins v7:[0b,1b] x [(NJ=2to4),(NJ:5or6),(NJ>=7)]_CD",31,0.5,31.5);

  h_SBins_v7_CD_EW = new TH1D("AllSBins_v7_CD_EW","search bins v7:[0b,1b] x [(NJ=2to4),(NJ:5or6),(NJ>=7)]_CD",31,0.5,31.5);
  h_SBins_v7_CD_SP = new TH1D("AllSBins_v7_CD_SP","search bins v7:[0b,1b] x [(NJ=2to4),(NJ:5or6),(NJ>=7)]_CD",31,0.5,31.5 );
  h_SBins_v7_CD_2018 = new TH1D("AllSBins_v7_CD_2018","search bins v7:[0b,1b] x [(NJ=2to4),(NJ:5or6),(NJ>=7)]_CD",31,0.5,31.5);

  //---------------Search Bins ----------------------------
  /* h_MET_R_v2[0] =new TH1D("MET_R1_v2","MET for 0b, NJ=2to4 ",METBinLowEdge.size()-1,&(METBinLowEdge[0])); */
  /* h_MET_R_v2[1] =new TH1D("MET_R2_v2","MET for 0b, NJ>=5 ",METBinLowEdge.size()-1,&(METBinLowEdge[0])); */
  /* h_MET_R_v2[2] =new TH1D("MET_R3_v2","MET for 1b, NJ=2to4 ",METBinLowEdge.size()-1,&(METBinLowEdge[0])); */
  /* h_MET_R_v2[3] =new TH1D("MET_R4_v2","MET for 1b, NJ>=5 ",METBinLowEdge.size()-1,&(METBinLowEdge[0])); */
  /* h_MET_R_v2[4] =new TH1D("MET_R5_v2","MET for b>=2 ",METBinLowEdge2bJ.size()-1,&(METBinLowEdge2bJ[0])); */

  /* h_SBins = new TH1D("AllSBins","all search bins:(0b, NJ=2to4)(0b, NJ>=5)(1b, NJ=2to4)(1b, NJ>=5)(b>=2)",34,0.5,34.5); */
  /* h_SBins_v1 = new TH1D("AllSBins_v1","search bins:(NJ=2to4) (NJ:5or6) (NJ>=7)",21,0.5,21.5); */
  /* h_SBins_v3 = new TH1D("AllSBins_v3","search bins: [ NJ:2-4, NJ:5or6, NJ>=7] x [0b, 1b, >=2b]",63,0.5,63.5); */

  /* h_SBins_v4_CD = new TH1D("AllSBins_v4_CD","search bins:[0b,1b] x [(NJ=2to4),(NJ:5or6),(NJ>=7)]_CD",43,0.5,43.5); */

  /* h_SBins_v7_CD = new TH1D("AllSBins_v7_CD","search bins v7:[0b,1b] x [(NJ=2to4),(NJ:5or6),(NJ>=7)]_CD",31,0.5,31.5); */

}


AnalyzeLightBSM::AnalyzeLightBSM(const TString &inputFileList, const char *outFileName, const char* dataset) {
  string nameData=dataset;//vvv

  TChain *tree = new TChain("PreSelection");
  /* if(nameData=="bkg") tree = new TChain("TreeMaker2/PreSelection");//vvv */
  /* if(nameData=="FastSim_TChiWg_0_400_v17") tree = new TChain("tree");//vvv */
  /* if(nameData=="FastSim_TChiWg_0_800_v17") tree = new TChain("tree");//vvv */
  /* if(nameData=="FastSim_TChiWg_0_1200_v17") tree = new TChain("tree");//vvv */
  if( ! FillChain(tree, inputFileList) ) {
    std::cerr << "Cannot get the tree " << std::endl;
  } else {
    std::cout << "Initiating analysis of dataset " << dataset << std::endl;
  }

  if(nameData!="signalH") nameData="BG";
  if(nameData=="signalH") nameData="signal";
  cout<<"Treating the input files as "<<nameData<<" for setting tree branches"<<endl;
  NtupleVariables::Init(tree,nameData);

  BookHistogram(outFileName);
  
}

Bool_t AnalyzeLightBSM::FillChain(TChain *chain, const TString &inputFileList) {

  ifstream infile(inputFileList, ifstream::in);
  std::string buffer;

  if(!infile.is_open()) {
    std::cerr << "** ERROR: Can't open '" << inputFileList << "' for input" << std::endl;
    return kFALSE;
  }

  std::cout << "TreeUtilities : FillChain " << std::endl;
  while(1) {
    infile >> buffer;
    if(!infile.good()) break;
    //std::cout << "Adding tree from " << buffer.c_str() << std::endl;                                                              
    chain->Add(buffer.c_str());
  }
  std::cout << "No. of Entries in this tree : " << chain->GetEntries() << std::endl;
  return kTRUE;
}

Long64_t AnalyzeLightBSM::LoadTree(Long64_t entry) {
  // Set the environment to read one entry                                                                                          
  if (!fChain) return -5;
  Long64_t centry = fChain->LoadTree(entry);
  if (centry < 0) return centry;
  if (!fChain->InheritsFrom(TChain::Class()))  return centry;
  TChain *chain = (TChain*)fChain;
  if (chain->GetTreeNumber() != fCurrent) {
    fCurrent = chain->GetTreeNumber();
    //    Notify();
  }
  return centry;
}

AnalyzeLightBSM::~AnalyzeLightBSM() { 

  if (!fChain) return;
  delete fChain->GetCurrentFile();
  oFile->cd();
  oFile->Write();
  oFile->Close();

}

#endif

