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
  int getBinNoV7_EW(bool,bool);
  int getBinNoV7_EW1(bool);
  int getBinNoV6_EW(bool,bool);
  int getBinNoV6_EW1(bool);
  int getBinNoV6_EWplusSP_SR(bool,bool,bool,int);
  int getBinNoV6_EWplusSP_CR(bool,bool,bool,bool,int,int);

  double getGendRLepPho();
  double getGendRLepBestPho(TLorentzVector);
  double getGenLep(TLorentzVector);
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
  double deepCSVvalue=0;
  bool isSignal=false;
  //vector<double> HTBinLowEdge ={0,500,550,600,650,700,750,800,900,1000,1100,1200,1400,1600,1800,2000,2400,2800,3200};
  //  vector<double> HTBinLowEdge ={0,100,200,300,400,500,600,700,800,900,1000,1200,1500,2000,2500};
  //  vector<double> MHTBinLowEdge={0,20,40,60,80,100,120,160,200,270,350,500};
  vector<double> STBinLowEdge ={0,200,220,240,260,300,360,420,500,600,700,850,1000,1200,1500,2000,2500,3000};
  // vector<double> METLowEdge={0,20,40,60,80,100,120,160,200,220,240,260,300,340,380,420,480,520,560,600,660,720,800,900,1000,1200};
  vector<double> METLowEdge={200,270,350,450,750,2000};
  vector<double> METLowEdge1={100,200,270,350,450,750,2000};
  vector<double> METLowEdge3={250,270,350,450,750,2000};
  vector<double> METLowEdge2={100,200,270,350,450,2000};

  vector<double> METLowEdge_v1={100,250,270,350,450,600,750,900,2000};
  vector<double> METLowEdge_v2={200,300,370,450,600,750,900,2000};
  vector<double> METLowEdge_v2_1={200,300,370,450,600,750,2000};
  vector<double> METLowEdge_v3={300,370,450,600,750,900,2000};
  vector<double> METLowEdge_v3_1={300,370,450,600,750,2000};
  vector<double> METLowEdge_v2_2={200,300,370,450,600,2000};

  /* vector<double> METLowEdge1={200,270,350,450,750,2000}; */
  /* vector<double> METLowEdge2={200,270,350,450,2000}; */
  // vector<double> METLowEdge1={0,20,40,60,80,100,120,160,200,220,240,260,300,340,380,420,460,520,580,640,700,780,860,940,1000,1200};
  // vector<double> METLowEdge2={0,20,40,60,80,100,120,160,200,220,240,260,280,300,340,380,420,480,540,600,700,800,900,1000,1200};
  // vector<double> METLowEdge={0,200,210,220,240,260,280,300,320,340,360,380,400,450,500,600,1000,1400};
  vector<double> METBinLowEdgeV4_njLow={0,100,125,160,200,270,350,450,750,900};//{0,100,200,270,350,450,750,900}; 
  vector<double> METBinLowEdgeV4={0,100,125,160,200,270,350,450,750};
  vector<double> METBinLowEdgeV7_njLow={0,100,200,270,350,450,750,900};
  vector<double> METBinLowEdgeV7={0,100,200,270,350,450,750};
  vector<double> Ak8_vMass_EW={30,65,105,200};

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
  TH1D *h_mindphi1dphi2;
  TH1D *h_intLumi_EW;
  TH1D *h_ST_EW;
  TH1D *h_MET_EW;
  TH1D *h_BTags_EW;
  TH1D *h_BestPhotonPt_EW;
  TH1D *h_nJets_EW;
  TH1D *h_JetPt1;
  TH1D *h_JetPhi1;
  TH1D *h_JetEta1;
  TH1D *h_JetPt2;
  TH1D *h_JetPhi2;
  TH1D *h_JetEta2;
  TH1D *h_JetPt3;
  TH1D *h_JetPhi3;
  TH1D *h_JetEta3;
  TH1D *h_JetPt4;
  TH1D *h_JetPhi4;
  TH1D *h_JetEta4;


  TH1D *h_intLumi_EW_noSB;
  TH1D *h_ST_EW_noSB;
  TH1D *h_MET_EW_noSB;
  TH1D *h_BTags_EW_noSB;
  TH1D *h_BestPhotonPt_EW_noSB;
  TH1D *h_nJets_EW_noSB;

  TH1D *h_intLumi_EW_SB;
  TH1D *h_ST_EW_SB;
  TH1D *h_MET_EW_SB;
  TH1D *h_BTags_EW_SB;
  TH1D *h_BestPhotonPt_EW_SB;
  TH1D *h_nJets_EW_SB;

  TH1D *h_intLumi_EW_htag;
  TH1D *h_ST_EW_htag;
  TH1D *h_MET_EW_htag;
  TH1D *h_BTags_EW_htag;
  TH1D *h_BestPhotonPt_EW_htag;
  TH1D *h_nJets_EW_htag;

  TH1D *h_intLumi_EW_wtag;
  TH1D *h_ST_EW_wtag;
  TH1D *h_MET_EW_wtag;
  TH1D *h_BTags_EW_wtag;
  TH1D *h_BestPhotonPt_EW_wtag;
  TH1D *h_nJets_EW_wtag;

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
  TH1D *h_METvBin_EW_htag;
  TH1D *h_METvBin_SP;
  TH1D *h_METvBin_EW_v1;
  TH1D *h_METvBin_EW_htag_v1;
  TH1D *h_METvBin_SP_v1;
  TH1D *h_METvBin_EW_v2;
  TH1D *h_METvBin_EW_noSB_v2;
  TH1D *h_METvBin_EW_SB_v2;
  TH1D *h_METvBin_EW_wtag_v2;
  TH1D *h_METvBin_EW_htag_v2;
  TH1D *h_METvBin_SP_v2;
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
  TH1D *h_hadAk8Mass_vBin;
  TH1D *h_hadAk8Mass_EW_vBin;
  TH1D *h_hadAk8Mass_EW_htag_vBin;
  TH1D *h_hadAk8Mass_EW_wtag_vBin;
  TH1D *h_hadAk8Mass_SP_vBin;
  TH1D *h_hadAk8Mass_matchedW;
  TH1D *h_hadAk8Mass_EW_nAk8jet_ge1;
  TH1D *h_hadAk8Mass_EW;
  TH1D *h_hadAk8Mass_EW_SB;
  TH1D *h_hadAk8Mass_EW_noSB;
  TH1D *h_hadAk8Mass_EW_htag;
  TH1D *h_hadAk8Mass_EW_wtag;
  TH1D *h_hadAk8Mass_SP;
  TH1D *h_hadAk8Mass_Ak8jet2to5;
  TH1D *h_hadAk8Mass_Ak8jetge6;
  TH1D *h_hadAk8Mass_Ak8jet2to5_noEW;
  TH1D *h_hadAk8Mass_Ak8jetge6_EW;
  TH1D *h_hadAk8Mass_Ak8jetge6_noEW;
  TH1D *h_hadAk8Mass_Ak8jet0;
  TH1D *h_hadAk8Mass_Ak8jet0_EW_noSB;
  TH1D *h_hadAk8Mass_Ak8jet0_EW_SB;
  TH1D *h_hadAk8Mass_Ak8jet0_SP;
  TH1D *h_hadAk8Mass_Ak8jet0_EW;
  TH1D *h_hadAk8Pt;
  TH1D *h_hadAk8Pt_matchedW;
  TH1D *h_hadAk8Pt_EW_nAk8jet_ge1;
  TH1D *h_hadAk8Pt_EW;
  TH1D *h_hadAk8Pt_EW_htag;
  TH1D *h_hadAk8Pt_SP;
  TH1D *h_hadAk8Pt_Ak8jet2to5;
  TH1D *h_hadAk8Pt_Ak8jetge6;
  TH1D *h_hadAk8Pt_Ak8jet0;
  TH1D *h_hadAk8Pt_Ak8jet0_EW_noSB;
  TH1D *h_hadAk8Pt_Ak8jet0_EW_SB;
  TH1D *h_hadAk8Pt_Ak8jet0_SP;
  TH1D *h_hadAk8Pt_Ak8jet0_EW;
  TH1D *h_nHadJets_nAk8jet_ge1;
  TH1D *h_nHadAk8Jets_nAk8jet_ge1;
  TH1D *h_BTags_nAk8jet_ge1;
  TH1D *h_nHadJets_nAk8jet_jet2to5;
  TH1D *h_nHadAk8Jets_nAk8jet_jet2to5;
  TH1D *h_BTags_nAk8jet_jet2to5;
  TH1D *h_nHadJets_nAk8jet_jetge6;
  TH1D *h_nHadAk8Jets_nAk8jet_jetge6;
  TH1D *h_nHadJets_nAk8jet0_SP;
  TH1D *h_nHadAk8Jets_nAk8jet0_SP;

  TH1D *h_nHadJets_nAk8jet_jet2to5_noEW;
  TH1D *h_nHadJets_nAk8jet_jetge6_EW;
  TH1D *h_nHadJets_nAk8jet_jetge6_noEW;

  TH1D *h_BTags_nAk8jet_jetge6;
  TH1D *h_BTags_nAk8jet1;
  TH1D *h_BTags_nAk8jet2;
  TH1D *h_BTags_nAk8jet3;
  /* TH2D *h2_STvsHT; */

  /* TH1D *h_dPhi_METBestPhoton; */
  TH1D *h_dPhi_METjet1;
  TH1D *h_dPhi_METjet2;
  TH1D *h_dPhi_METjet3;
  TH1D *h_dPhi_METjet4;
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

  ///// no cut //////
  TH1D *h_ST_nocut;
  TH1D *h_MET_nocut;
  TH1D *h_BTags_nocut;
  TH1D *h_BestPhotonPt_nocut;
  TH1D *h_nJets_nocut;
  TH1D *h_hadAk8Mass_nocut;
  TH1D *h_SBins_v6_CD_EW_50bin_nocut;
  TH1D *h_METvBin_nocut;

  ///// after trg //////                                                                                                                                                                   
  TH1D *h_ST_aftertrg;
  TH1D *h_MET_aftertrg;
  TH1D *h_METvBin_aftertrg;
  TH1D *h_BTags_aftertrg;
  TH1D *h_BestPhotonPt_aftertrg;
  TH1D *h_nJets_aftertrg;
  TH1D *h_hadAk8Mass_aftertrg;
  TH1D *h_SBins_v6_CD_EW_50bin_aftertrg;

  ///// after MET filters //////
  TH1D *h_ST_METfilters;
  TH1D *h_MET_METfilters;
  TH1D *h_METvBin_METfilters;
  TH1D *h_BTags_METfilters;
  TH1D *h_BestPhotonPt_METfilters;
  TH1D *h_nJets_METfilters;
  TH1D *h_hadAk8Mass_METfilters;
  TH1D *h_SBins_v6_CD_EW_50bin_METfilters;

  ///// after nJets >= 2 //////                                                                                                                                                             
  TH1D *h_ST_nj2;
  TH1D *h_MET_nj2;
  TH1D *h_METvBin_nj2;
  TH1D *h_BTags_nj2;
  TH1D *h_BestPhotonPt_nj2;
  TH1D *h_nJets_nj2;
  TH1D *h_hadAk8Mass_nj2;
  TH1D *h_SBins_v6_CD_EW_50bin_nj2;

  ///// after madHT //////                                                                                                                                                                 
  TH1D *h_ST_madHT;
  TH1D *h_MET_madHT;
  TH1D *h_METvBin_madHT;
  TH1D *h_BTags_madHT;
  TH1D *h_BestPhotonPt_madHT;
  TH1D *h_nJets_madHT;
  TH1D *h_hadAk8Mass_madHT;
  TH1D *h_SBins_v6_CD_EW_50bin_madHT;

  ///// after gen pho //////                                                                                                                                                               
  TH1D *h_ST_genpho;
  TH1D *h_MET_genpho;
  TH1D *h_METvBin_genpho;
  TH1D *h_BTags_genpho;
  TH1D *h_BestPhotonPt_genpho;
  TH1D *h_nJets_genpho;
  TH1D *h_hadAk8Mass_genpho;
  TH1D *h_SBins_v6_CD_EW_50bin_genpho;

  ///// after ISR //////                                                                                                                                                                
  TH1D *h_ST_ISR;
  TH1D *h_MET_ISR;
  TH1D *h_METvBin_ISR;
  TH1D *h_BTags_ISR;
  TH1D *h_BestPhotonPt_ISR;
  TH1D *h_nJets_ISR;
  TH1D *h_hadAk8Mass_ISR;
  TH1D *h_SBins_v6_CD_EW_50bin_ISR;

  ///// after photon pt //////                                                                                                                                                             
  TH1D *h_ST_phopt;
  TH1D *h_MET_phopt;
  TH1D *h_METvBin_phopt;
  TH1D *h_BTags_phopt;
  TH1D *h_BestPhotonPt_phopt;
  TH1D *h_nJets_phopt;
  TH1D *h_hadAk8Mass_phopt;
  TH1D *h_SBins_v6_CD_EW_50bin_phopt;

  ///// after lepton veto //////                                                                                                                                                           
  TH1D *h_ST_nolep;
  TH1D *h_MET_nolep;
  TH1D *h_METvBin_nolep;
  TH1D *h_BTags_nolep;
  TH1D *h_BestPhotonPt_nolep;
  TH1D *h_nJets_nolep;
  TH1D *h_hadAk8Mass_nolep;
  TH1D *h_SBins_v6_CD_EW_50bin_nolep;

  ///// after iso track veto //////                                                                                                                                                         
  TH1D *h_ST_noisotrack;
  TH1D *h_MET_noisotrack;
  TH1D *h_METvBin_noisotrack;
  TH1D *h_BTags_noisotrack;
  TH1D *h_BestPhotonPt_noisotrack;
  TH1D *h_nJets_noisotrack;
  TH1D *h_hadAk8Mass_noisotrack;
  TH1D *h_SBins_v6_CD_EW_50bin_noisotrack;

  ///// after MET>200 //////                                                                                                                                                         
  TH1D *h_ST_MET200;
  TH1D *h_MET_MET200;
  TH1D *h_METvBin_MET200;
  TH1D *h_BTags_MET200;
  TH1D *h_BestPhotonPt_MET200;
  TH1D *h_nJets_MET200;
  TH1D *h_hadAk8Mass_MET200;
  TH1D *h_SBins_v6_CD_EW_50bin_MET200;

  ///// after photon pt & jet pt ratio //////                                                                                                                                              
  TH1D *h_ST_phojet;
  TH1D *h_MET_phojet;
  TH1D *h_METvBin_phojet;
  TH1D *h_BTags_phojet;
  TH1D *h_BestPhotonPt_phojet;
  TH1D *h_nJets_phojet;
  TH1D *h_hadAk8Mass_phojet;
  TH1D *h_SBins_v6_CD_EW_50bin_phojet;

  ///// after ST>300 //////                                                                                                                                                         
  TH1D *h_ST_ST300;
  TH1D *h_MET_ST300;
  TH1D *h_METvBin_ST300;
  TH1D *h_BTags_ST300;
  TH1D *h_BestPhotonPt_ST300;
  TH1D *h_nJets_ST300;
  TH1D *h_hadAk8Mass_ST300;
  TH1D *h_SBins_v6_CD_EW_50bin_ST300;

  ///// after dphi cut //////                                                                                                                                                         
  TH1D *h_ST_dphi;
  TH1D *h_MET_dphi;
  TH1D *h_METvBin_dphi;
  TH1D *h_BTags_dphi;
  TH1D *h_BestPhotonPt_dphi;
  TH1D *h_nJets_dphi;
  TH1D *h_hadAk8Mass_dphi;
  TH1D *h_SBins_v6_CD_EW_50bin_dphi;


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

  TH1D *h_SBins_v6_CD;
  TH1D *h_SBins_v6_CD_EW;
  TH1D *h_SBins_v6_CD_EW_htag;
  TH1D *h_SBins_v6_CD_SP;
  TH1D *h_SBins_v7_CD;
  TH1D *h_SBins_v7_CD_EW;
  TH1D *h_SBins_v7_CD_EW_htag;
  TH1D *h_SBins_v7_CD_EW_wtag;
  TH1D *h_SBins_v7_CD_SP;
  TH1D *h_SBins_v7_CD_2018;
  TH1D *h_SBins_v6_CD_EW_14bin;
  TH1D *h_SBins_v7_CD_EW_14bin;
  TH1D *h_SBins_v6_CD_EW_43bin;
  TH1D *h_SBins_v6_CD_EW_50bin;
  TH1D *h_SBins_v6_CD_EW_50bin_elec1_closure;
  TH1D *h_SBins_v6_CD_EW_7bin;
  TH1D *h_SBins_v6_CD_EW_7bin_noSB;
  TH1D *h_SBins_v7_CD_EW_7bin_noSB;
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
  h_JetPt1=new TH1D("JetPt1","Pt of the Jet 1",150,0,1500);
  h_JetPhi1=new TH1D("JetPhi1","Phi of the Jet 1",80,-4,4);
  h_JetEta1=new TH1D("JetEta1","Eta of the Jet 1",80,-4,4);
  h_JetPt2=new TH1D("JetPt2","Pt of the Jet 2",150,0,1500);
  h_JetPhi2=new TH1D("JetPhi2","Phi of the Jet 2",80,-4,4);
  h_JetEta2=new TH1D("JetEta2","Eta of the Jet 2",80,-4,4);
  h_JetPt3=new TH1D("JetPt3","Pt of the Jet 3",150,0,1500);
  h_JetPhi3=new TH1D("JetPhi3","Phi of the Jet 3",80,-4,4);
  h_JetEta3=new TH1D("JetEta3","Eta of the Jet 3",80,-4,4);
  h_JetPt4=new TH1D("JetPt4","Pt of the Jet 4",150,0,1500);
  h_JetPhi4=new TH1D("JetPhi4","Phi of the Jet 4",80,-4,4);
  h_JetEta4=new TH1D("JetEta4","Eta of the Jet 4",80,-4,4);


  h_intLumi_EW=new TH1D("intLumi_EW","2016 integrated luminosity in /fb",2500,25,50); 
  h_ST_EW=new TH1D("ST_EW","ST 2016",400,0,4000);
  h_MET_EW=new TH1D("MET_EW","MET 2016",200,0,2000);
  h_BTags_EW=new TH1D("nBTags_EW","no. of B tags 2016",10,0,10);
  h_BestPhotonPt_EW=new TH1D("BestPhotonPt_EW","Pt of the Best Photon 2016",150,0,1500);
  h_nJets_EW=new TH1D("nJets_EW","nJets 2016",25,0,25);

  h_intLumi_EW_noSB=new TH1D("intLumi_EW_noSB"," integrated luminosity in /fb",2500,25,50); 
  h_ST_EW_noSB=new TH1D("ST_EW_noSB","ST ",400,0,4000);
  h_MET_EW_noSB=new TH1D("MET_EW_noSB","MET ",200,0,2000);
  h_BTags_EW_noSB=new TH1D("nBTags_EW_noSB","no. of B tags ",10,0,10);
  h_BestPhotonPt_EW_noSB=new TH1D("BestPhotonPt_EW_noSB","Pt of the Best Photon ",150,0,1500);
  h_nJets_EW_noSB=new TH1D("nJets_EW_noSB","nJets",25,0,25);

  h_intLumi_EW_SB=new TH1D("intLumi_EW_SB"," integrated luminosity in /fb",2500,25,50); 
  h_ST_EW_SB=new TH1D("ST_EW_SB","ST ",400,0,4000);
  h_MET_EW_SB=new TH1D("MET_EW_SB","MET ",200,0,2000);
  h_BTags_EW_SB=new TH1D("nBTags_EW_SB","no. of B tags ",10,0,10);
  h_BestPhotonPt_EW_SB=new TH1D("BestPhotonPt_EW_SB","Pt of the Best Photon ",150,0,1500);
  h_nJets_EW_SB=new TH1D("nJets_EW_SB ","nJets",25,0,25);


  h_intLumi_EW_wtag=new TH1D("intLumi_EW_wtag"," integrated luminosity in /fb",2500,25,50); 
  h_ST_EW_wtag=new TH1D("ST_EW_wtag","ST ",400,0,4000);
  h_MET_EW_wtag=new TH1D("MET_EW_wtag","MET ",200,0,2000);
  h_BTags_EW_wtag=new TH1D("nBTags_EW_wtag","no. of B tags ",10,0,10);
  h_BestPhotonPt_EW_wtag=new TH1D("BestPhotonPt_EW_wtag","Pt of the Best Photon ",150,0,1500);
  h_nJets_EW_wtag=new TH1D("nJets_EW_wtag","nJets",25,0,25);


  h_intLumi_EW_htag=new TH1D("intLumi_EW_htag","2016 integrated luminosity in /fb",2500,25,50); 
  h_ST_EW_htag=new TH1D("ST_EW_htag","ST 2016",400,0,4000);
  h_MET_EW_htag=new TH1D("MET_EW_htag","MET 2016",200,0,2000);
  h_BTags_EW_htag=new TH1D("nBTags_EW_htag","no. of B tags 2016",10,0,10);
  h_BestPhotonPt_EW_htag=new TH1D("BestPhotonPt_EW_htag","Pt of the Best Photon 2016",150,0,1500);
  h_nJets_EW_htag=new TH1D("nJets_EW_htag","nJets 2016",25,0,25);

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

  h_BTags_nAk8jet_jet2to5=new TH1D("BTags_nAk8jet_jet2to5","no. of b jets  ( 2<=njet<=5 )",25,0,25);
  h_nHadJets_nAk8jet_jet2to5=new TH1D("nHadJets_nAk8jet_jet2to5","no. of Ak4  jets ( 2<=njet<=5 )",25,0,25);
  h_nHadAk8Jets_nAk8jet_jet2to5=new TH1D("nHadAk8Jets_nAk8jet_jet2to5","no. of Ak8  jets ( 2<=njet<=5 )",25,0,25);

  h_BTags_nAk8jet_jetge6=new TH1D("BTags_nAk8jet_jetge6","no. of b jets ( njet>=6 )",25,0,25);
  h_nHadJets_nAk8jet_jetge6=new TH1D("nHadJets_nAk8jet_jetge6","no. of Ak4  jets ( njet>=6 )",25,0,25);
  h_nHadAk8Jets_nAk8jet_jetge6=new TH1D("nHadAk8Jets_nAk8jet_jetge6","no. of Ak8  jets ( njet>=6 )",25,0,25);

  h_nHadJets_nAk8jet0_SP=new TH1D("nHadJets_nAk8jet0_SP","no. of Ak4  jets ( njet>=6 )",25,0,25);
  h_nHadAk8Jets_nAk8jet0_SP=new TH1D("nHadAk8Jets_nAk8jet0_SP","no. of Ak8  jets ( njet>=6 )",25,0,25);

  h_nHadJets_nAk8jet_jet2to5_noEW=new TH1D("nHadJets_nAk8jet_jet2to5_noEW","no. of Ak4  jets ( 2<=njet<=5 )",25,0,25);
  h_nHadJets_nAk8jet_jetge6_EW=new TH1D("nHadJets_nAk8jet_jetge6_EW","no. of Ak4  jets ( njet>=6 )",25,0,25);
  h_nHadJets_nAk8jet_jetge6_noEW=new TH1D("nHadJets_nAk8jet_jetge6_noEW","no. of Ak4  jets ( njet>=6 )",25,0,25);


  h_hadAk8Mass=new TH1D("hadAk8Mass","Soft dropped Mass of AK8 Jet",1000,0,300);
  h_hadAk8Mass_vBin=new TH1D("hadAk8Mass_vBin","Soft dropped Mass of AK8 Jet using variable binning",Ak8_vMass_EW.size()-1,&(Ak8_vMass_EW[0]));
  h_hadAk8Mass_EW_vBin=new TH1D("hadAk8Mass_EW_vBin","Soft dropped Mass of AK8 Jet using variable binning after EW selection",Ak8_vMass_EW.size()-1,&(Ak8_vMass_EW[0]));

  h_hadAk8Mass_EW_htag_vBin=new TH1D("hadAk8Mass_EW_htag_vBin","Soft dropped Mass of AK8 Jet using variable binning after EW selection",Ak8_vMass_EW.size()-1,&(Ak8_vMass_EW[0]));
  h_hadAk8Mass_SP_vBin=new TH1D("hadAk8Mass_SP_vBin","Soft dropped Mass of AK8 Jet using variable binning after SP selection",Ak8_vMass_EW.size()-1,&(Ak8_vMass_EW[0]));
  h_hadAk8Mass_matchedW=new TH1D("hadAk8Mass_matchedW","Soft dropped Mass of AK8 Jet which are matched with W ",1000,0,200);
  h_hadAk8Mass_Ak8jet2to5=new TH1D("hadAk8Mass_Ak8jet2to5","Soft dropped Mass of leading AK8 Jet",1000,0,300);
  h_hadAk8Mass_Ak8jetge6=new TH1D("hadAk8Mass_Ak8jetge6","Soft dropped Mass of leading AK8 Jet",1000,0,300);
  h_hadAk8Mass_Ak8jet2to5_noEW=new TH1D("hadAk8Mass_Ak8jet2to5_noEW","Soft dropped Mass of leading AK8 Jet",1000,0,300);
  h_hadAk8Mass_Ak8jetge6_EW=new TH1D("hadAk8Mass_Ak8jetge6_EW","Soft dropped Mass of leading AK8 Jet",1000,0,300);
  h_hadAk8Mass_Ak8jetge6_noEW=new TH1D("hadAk8Mass_Ak8jetge6_noEW","Soft dropped Mass of leading AK8 Jet",1000,0,300);
  h_hadAk8Mass_Ak8jet0=new TH1D("hadAk8Mass_Ak8jet0","Soft dropped Mass of leading AK8 Jet",1000,0,300);
  h_hadAk8Mass_Ak8jet0_SP=new TH1D("hadAk8Mass_Ak8jet0_EW_SP","Soft dropped Mass of leading AK8 Jet",1000,0,300);
  h_hadAk8Mass_Ak8jet0_EW=new TH1D("hadAk8Mass_Ak8jet0_EW","Soft dropped Mass of leading AK8 Jet",1000,0,300);
  h_hadAk8Mass_Ak8jet0_EW_SB=new TH1D("hadAk8Mass_Ak8jet0_EW_SB","Soft dropped Mass of leading AK8 Jet",1000,0,300);
  h_hadAk8Mass_Ak8jet0_EW_noSB=new TH1D("hadAk8Mass_Ak8jet0_EW_noSB","Soft dropped Mass of leading AK8 Jet",1000,0,300);
  h_hadAk8Mass_EW=new TH1D("hadAk8Mass_EW","Soft dropped Mass of AK8 Jet",1000,0,300);
  h_hadAk8Mass_EW_noSB=new TH1D("hadAk8Mass_EW_noSB","Soft dropped Mass of AK8 Jet",1000,0,300);
  h_hadAk8Mass_EW_SB=new TH1D("hadAk8Mass_EW_SB","Soft dropped Mass of AK8 Jet",1000,0,300);
  h_hadAk8Mass_EW_wtag=new TH1D("hadAk8Mass_EW_wtag","Soft dropped Mass of AK8 Jet",1000,0,300);
  h_hadAk8Mass_EW_htag=new TH1D("hadAk8Mass_EW_htag","Soft dropped Mass of AK8 Jet",1000,0,300);
  h_hadAk8Mass_EW_nAk8jet_ge1=new TH1D("hadAk8Mass_EW_nAk8jet_ge1","Soft dropped Mass of AK8 Jet after atleast 1 Ak8 jet mass in 65 GeV - 100 GeV range",1000,0,200);
  h_hadAk8Mass_SP=new TH1D("hadAk8Mass_SP","Soft dropped Mass of AK8 Jet",1000,0,300);
  h_hadAk8Pt=new TH1D("hadAk8Pt","Soft dropped Pt of AK8 Jet",2000,0,1000);
  h_hadAk8Pt_matchedW=new TH1D("hadAk8Pt_matchedW"," Pt of AK8 Jet which are matched with W",2000,0,1000);
  h_hadAk8Pt_Ak8jet2to5=new TH1D("hadAk8Pt_Ak8jet2to5","Pt of leading AK8 Jet",2000,0,1000);
  h_hadAk8Pt_Ak8jetge6=new TH1D("hadAk8Pt_Ak8jetge6","Pt of leading AK8 Jet",2000,0,1000);
  h_hadAk8Pt_Ak8jet0=new TH1D("hadAk8Pt_Ak8jet0","Pt of leading AK8 Jet",2000,0,1000);
  h_hadAk8Pt_Ak8jet0_EW_noSB=new TH1D("hadAk8Pt_Ak8jet0_EW_noSB","Pt of leading AK8 Jet",2000,0,1000);
  h_hadAk8Pt_Ak8jet0_EW_SB=new TH1D("hadAk8Pt_Ak8jet0_EW_SB","Pt of leading AK8 Jet",2000,0,1000);
  h_hadAk8Pt_Ak8jet0_EW=new TH1D("hadAk8Pt_Ak8jet0_EW","Pt of leading AK8 Jet",2000,0,1000);
  h_hadAk8Pt_Ak8jet0_SP=new TH1D("hadAk8Pt_Ak8jet0_EW_SP","Pt of leading AK8 Jet",2000,0,1000);
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
  h_mindphi1dphi2=new TH1D("mindPhi1dPhi2","mindphi between MET Vec and Jet1 or Jet2",40,0,4);
  h_dPhi_METjet1=new TH1D("dPhi_METjet1","dphi between MET Vec and Jet1",40,0,4);
  h_dPhi_METjet2=new TH1D("dPhi_METjet2","dphi between MET Vec and Jet2",40,0,4);
  h_dPhi_METjet3=new TH1D("dPhi_METjet3","dphi between MET Vec and Jet3",40,0,4);
  h_dPhi_METjet4=new TH1D("dPhi_METjet4","dphi between MET Vec and Jet4",40,0,4);
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
  h_METvBin=new TH1D("METvBin","MET in variable bins",METLowEdge.size()-1,&(METLowEdge[0]));//Ak8_vMass_EW
  h_METvBin_EW=new TH1D("METvBin_EW","MET in variable bins after EW selctions",METLowEdge.size()-1,&(METLowEdge[0]));
  h_METvBin_EW_htag=new TH1D("METvBin_EW_htag","MET in variable bins after EW selctions",METLowEdge.size()-1,&(METLowEdge[0]));
  h_METvBin_SP=new TH1D("METvBin_SP","MET in variable bins after SP elections",METLowEdge.size()-1,&(METLowEdge[0]));
  h_METvBin_EW_v1=new TH1D("METvBin_EW_v1","MET in variable bins after EW selctions",METLowEdge_v1.size()-1,&(METLowEdge_v1[0]));
  h_METvBin_EW_htag_v1=new TH1D("METvBin_EW_htag_v1","MET in variable bins after EW selctions",METLowEdge_v1.size()-1,&(METLowEdge_v1[0]));
  h_METvBin_SP_v1=new TH1D("METvBin_SP_v1","MET in variable bins after SP elections",METLowEdge_v1.size()-1,&(METLowEdge_v1[0]));
  h_METvBin_EW_htag_v2=new TH1D("METvBin_EW_htag_v2","MET in variable bins after EW selctions",METLowEdge_v2.size()-1,&(METLowEdge_v2[0]));
  h_METvBin_EW_v2=new TH1D("METvBin_EW_v2","MET in variable bins after EW selctions",METLowEdge_v2.size()-1,&(METLowEdge_v2[0]));
  h_METvBin_EW_noSB_v2=new TH1D("METvBin_EW_noSB_v2","MET in variable bins after EW selctions",METLowEdge_v2.size()-1,&(METLowEdge_v2[0]));
  h_METvBin_EW_SB_v2=new TH1D("METvBin_EW_SB_v2","MET in variable bins after EW selctions",METLowEdge_v2.size()-1,&(METLowEdge_v2[0]));
  h_METvBin_EW_wtag_v2=new TH1D("METvBin_EW_wtag_v2","MET in variable bins after EW selctions",METLowEdge_v2.size()-1,&(METLowEdge_v2[0]));
  h_METvBin_SP_v2=new TH1D("METvBin_SP_v2","MET in variable bins after SP elections",METLowEdge_v2.size()-1,&(METLowEdge_v2[0]));
  h_METvBin1=new TH1D("METvBin1","MET in variable bins",METLowEdge_v1.size()-1,&(METLowEdge_v1[0]));
  h_METvBin_nocut1=new TH1D("METvBin_nocut1","MET in variable bins without any cut",METLowEdge_v1.size()-1,&(METLowEdge_v1[0]));
  h_METvBin2=new TH1D("METvBin2","MET in variable bins",METLowEdge_v2.size()-1,&(METLowEdge_v2[0]));
  h_METvBin_nocut2=new TH1D("METvBin_nocut2","MET in variable bins without any cut",METLowEdge_v2.size()-1,&(METLowEdge_v2[0]));

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

  //no cut
  h_ST_nocut=new TH1D("ST_nocut","ST",400,0,4000);
  h_MET_nocut=new TH1D("MET_nocut","MET",200,0,2000);
  h_BTags_nocut=new TH1D("nBTags_nocut","no. of B tags",10,0,10);
  h_BestPhotonPt_nocut=new TH1D("BestPhotonPt_nocut","Pt of the Best Photon",150,0,1500);
  h_nJets_nocut=new TH1D("nJets_nocut","nJets",25,0,25);
  h_hadAk8Mass_nocut=new TH1D("hadAk8Mass_nocut","Soft dropped Mass of AK8 Jet",1000,0,300);
  h_SBins_v6_CD_EW_50bin_nocut = new TH1D("AllSBins_v6_CD_EW_50bin_nocut","search bins v6:[(WTag : [65,105]),(HTag : [105,140])]",52,0,52);
  h_METvBin_nocut=new TH1D("METvBin_nocut","MET in variable bins",METLowEdge_v2.size()-1,&(METLowEdge_v2[0]));//Ak8_vMass_EW                                                                                   

  ////////// After triggers //////////////                                                                                                                                                 
  h_ST_aftertrg=new TH1D("ST_aftertrg","ST",400,0,4000);
  h_MET_aftertrg=new TH1D("MET_aftertrg","MET",200,0,2000);
  h_BTags_aftertrg=new TH1D("nBTags_aftertrg","no. of B tags",10,0,10);
  h_BestPhotonPt_aftertrg=new TH1D("BestPhotonPt_aftertrg","Pt of the Best Photon",150,0,1500);
  h_nJets_aftertrg=new TH1D("nJets_aftertrg","nJets",25,0,25);
  h_hadAk8Mass_aftertrg=new TH1D("hadAk8Mass_aftertrg","Soft dropped Mass of AK8 Jet",1000,0,300);
  h_SBins_v6_CD_EW_50bin_aftertrg = new TH1D("AllSBins_v6_CD_EW_50bin_aftertrg","search bins v6:[(WTag : [65,105]),(HTag : [105,140])]",52,0,52);
  h_METvBin_aftertrg=new TH1D("METvBin_aftertrg","MET in variable bins",METLowEdge_v2.size()-1,&(METLowEdge_v2[0]));//Ak8_vMass_EW                                                                \

  ////////// After MET filters ///////////                                                                                                                                                  
  h_ST_METfilters=new TH1D("ST_METfilters","ST",400,0,4000);
  h_MET_METfilters=new TH1D("MET_METfilters","MET",200,0,2000);
  h_BTags_METfilters=new TH1D("nBTags_METfilters","no. of B tags",10,0,10);
  h_BestPhotonPt_METfilters=new TH1D("BestPhotonPt_METfilters","Pt of the Best Photon",150,0,1500);
  h_nJets_METfilters=new TH1D("nJets_METfilters","nJets",25,0,25);
  h_hadAk8Mass_METfilters=new TH1D("hadAk8Mass_METfilters","Soft dropped Mass of AK8 Jet",1000,0,300);
  h_SBins_v6_CD_EW_50bin_METfilters = new TH1D("AllSBins_v6_CD_EW_50bin_METfilters","search bins v6:[(WTag : [65,105]),(HTag : [105,140])]",52,0,52);
  h_METvBin_METfilters=new TH1D("METvBin_METfilters","MET in variable bins",METLowEdge_v2.size()-1,&(METLowEdge_v2[0]));//Ak8_vMass_EW                                                                

  ////////// After nJets >= 2 ///////////                                                                                                                                                  

  h_ST_nj2=new TH1D("ST_nj2","ST",400,0,4000);
  h_MET_nj2=new TH1D("MET_nj2","MET",200,0,2000);
  h_BTags_nj2=new TH1D("nBTags_nj2","no. of B tags",10,0,10);
  h_BestPhotonPt_nj2=new TH1D("BestPhotonPt_nj2","Pt of the Best Photon",150,0,1500);
  h_nJets_nj2=new TH1D("nJets_nj2","nJets",25,0,25);
  h_hadAk8Mass_nj2=new TH1D("hadAk8Mass_nj2","Soft dropped Mass of AK8 Jet",1000,0,300);
  h_SBins_v6_CD_EW_50bin_nj2 = new TH1D("AllSBins_v6_CD_EW_50bin_nj2","search bins v6:[(WTag : [65,105]),(HTag : [105,140])]",52,0,52);
  h_METvBin_madHT=new TH1D("METvBin_madHT","MET in variable bins",METLowEdge_v2.size()-1,&(METLowEdge_v2[0]));//Ak8_vMass_EW                                                                

  ///////// madHT/////////////
  h_ST_madHT=new TH1D("ST_madHT","ST",400,0,4000);
  h_MET_madHT=new TH1D("MET_madHT","MET",200,0,2000);
  h_BTags_madHT=new TH1D("nBTags_madHT","no. of B tags",10,0,10);
  h_BestPhotonPt_madHT=new TH1D("BestPhotonPt_madHT","Pt of the Best Photon",150,0,1500);
  h_nJets_madHT=new TH1D("nJets_madHT","nJets",25,0,25);
  h_hadAk8Mass_madHT=new TH1D("hadAk8Mass_madHT","Soft dropped Mass of AK8 Jet",1000,0,300);
  h_SBins_v6_CD_EW_50bin_madHT = new TH1D("AllSBins_v6_CD_EW_50bin_madHT","search bins v6:[(WTag : [65,105]),(HTag : [105,140])]",52,0,52);
  h_METvBin_nj2=new TH1D("METvBin_nj2","MET in variable bins",METLowEdge_v2.size()-1,&(METLowEdge_v2[0]));//Ak8_vMass_EW                                                                

  //////////gen pho/////                                                                                                                                                               
  h_ST_genpho=new TH1D("ST_genpho","ST",400,0,4000);
  h_MET_genpho=new TH1D("MET_genpho","MET",200,0,2000);
  h_BTags_genpho=new TH1D("nBTags_genpho","no. of B tags",10,0,10);
  h_BestPhotonPt_genpho=new TH1D("BestPhotonPt_genpho","Pt of the Best Photon",150,0,1500);
  h_nJets_genpho=new TH1D("nJets_genpho","nJets",25,0,25);
  h_hadAk8Mass_genpho=new TH1D("hadAk8Mass_genpho","Soft dropped Mass of AK8 Jet",1000,0,300);
  h_SBins_v6_CD_EW_50bin_genpho = new TH1D("AllSBins_v6_CD_EW_50bin_genpho","search bins v6:[(WTag : [65,105]),(HTag : [105,140])]",52,0,52);
  h_METvBin_genpho=new TH1D("METvBin_genpho","MET in variable bins",METLowEdge_v2.size()-1,&(METLowEdge_v2[0]));//Ak8_vMass_EW                                                                

  ///////ISR ///////                                                                                                                                                                       
  h_ST_ISR=new TH1D("ST_ISR","ST",400,0,4000);
  h_MET_ISR=new TH1D("MET_ISR","MET",200,0,2000);
  h_BTags_ISR=new TH1D("nBTags_ISR","no. of B tags",10,0,10);
  h_BestPhotonPt_ISR=new TH1D("BestPhotonPt_ISR","Pt of the Best Photon",150,0,1500);
  h_nJets_ISR=new TH1D("nJets_ISR","nJets",25,0,25);
  h_hadAk8Mass_ISR=new TH1D("hadAk8Mass_ISR","Soft dropped Mass of AK8 Jet",1000,0,300);
  h_SBins_v6_CD_EW_50bin_ISR = new TH1D("AllSBins_v6_CD_EW_50bin_ISR","search bins v6:[(WTag : [65,105]),(HTag : [105,140])]",52,0,52);
  h_METvBin_ISR=new TH1D("METvBin_ISR","MET in variable bins",METLowEdge_v2.size()-1,&(METLowEdge_v2[0]));//Ak8_vMass_EW                                                                

  ////// phopt ///
  h_ST_phopt=new TH1D("ST_phopt","ST",400,0,4000);
  h_MET_phopt=new TH1D("MET_phopt","MET",200,0,2000);
  h_BTags_phopt=new TH1D("nBTags_phopt","no. of B tags",10,0,10);
  h_BestPhotonPt_phopt=new TH1D("BestPhotonPt_phopt","Pt of the Best Photon",150,0,1500);
  h_nJets_phopt=new TH1D("nJets_phopt","nJets",25,0,25);
  h_hadAk8Mass_phopt=new TH1D("hadAk8Mass_phopt","Soft dropped Mass of AK8 Jet",1000,0,300);
  h_SBins_v6_CD_EW_50bin_phopt = new TH1D("AllSBins_v6_CD_EW_50bin_phopt","search bins v6:[(WTag : [65,105]),(HTag : [105,140])]",52,0,52);
  h_METvBin_phopt=new TH1D("METvBin_phopt","MET in variable bins",METLowEdge_v2.size()-1,&(METLowEdge_v2[0]));//Ak8_vMass_EW                                                                

  ////// nolep //////////
  h_ST_nolep=new TH1D("ST_nolep","ST",400,0,4000);
  h_MET_nolep=new TH1D("MET_nolep","MET",200,0,2000);
  h_BTags_nolep=new TH1D("nBTags_nolep","no. of B tags",10,0,10);
  h_BestPhotonPt_nolep=new TH1D("BestPhotonPt_nolep","Pt of the Best Photon",150,0,1500);
  h_nJets_nolep=new TH1D("nJets_nolep","nJets",25,0,25);
  h_hadAk8Mass_nolep=new TH1D("hadAk8Mass_nolep","Soft dropped Mass of AK8 Jet",1000,0,300);
  h_SBins_v6_CD_EW_50bin_nolep = new TH1D("AllSBins_v6_CD_EW_50bin_nolep","search bins v6:[(WTag : [65,105]),(HTag : [105,140])]",52,0,52);
  h_METvBin_nolep=new TH1D("METvBin_nolep","MET in variable bins",METLowEdge_v2.size()-1,&(METLowEdge_v2[0]));//Ak8_vMass_EW                                                                

  ////// noisotrack ////////
  h_ST_noisotrack=new TH1D("ST_noisotrack","ST",400,0,4000);
  h_MET_noisotrack=new TH1D("MET_noisotrack","MET",200,0,2000);
  h_BTags_noisotrack=new TH1D("nBTags_noisotrack","no. of B tags",10,0,10);
  h_BestPhotonPt_noisotrack=new TH1D("BestPhotonPt_noisotrack","Pt of the Best Photon",150,0,1500);
  h_nJets_noisotrack=new TH1D("nJets_noisotrack","nJets",25,0,25);
  h_hadAk8Mass_noisotrack=new TH1D("hadAk8Mass_noisotrack","Soft dropped Mass of AK8 Jet",1000,0,300);
  h_SBins_v6_CD_EW_50bin_noisotrack = new TH1D("AllSBins_v6_CD_EW_50bin_noisotrack","search bins v6:[(WTag : [65,105]),(HTag : [105,140])]",52,0,52);
  h_METvBin_noisotrack=new TH1D("METvBin_noisotrack","MET in variable bins",METLowEdge_v2.size()-1,&(METLowEdge_v2[0]));//Ak8_vMass_EW                                                                

  ////// MET200 ////////
  h_ST_MET200=new TH1D("ST_MET200","ST",400,0,4000);
  h_MET_MET200=new TH1D("MET_MET200","MET",200,0,2000);
  h_BTags_MET200=new TH1D("nBTags_MET200","no. of B tags",10,0,10);
  h_BestPhotonPt_MET200=new TH1D("BestPhotonPt_MET200","Pt of the Best Photon",150,0,1500);
  h_nJets_MET200=new TH1D("nJets_MET200","nJets",25,0,25);
  h_hadAk8Mass_MET200=new TH1D("hadAk8Mass_MET200","Soft dropped Mass of AK8 Jet",1000,0,300);
  h_SBins_v6_CD_EW_50bin_MET200 = new TH1D("AllSBins_v6_CD_EW_50bin_MET200","search bins v6:[(WTag : [65,105]),(HTag : [105,140])]",52,0,52);
  h_METvBin_MET200=new TH1D("METvBin_MET200","MET in variable bins",METLowEdge_v2.size()-1,&(METLowEdge_v2[0]));//Ak8_vMass_EW                                                                

  ///// phojet /////////
  h_ST_phojet=new TH1D("ST_phojet","ST",400,0,4000);
  h_MET_phojet=new TH1D("MET_phojet","MET",200,0,2000);
  h_BTags_phojet=new TH1D("nBTags_phojet","no. of B tags",10,0,10);
  h_BestPhotonPt_phojet=new TH1D("BestPhotonPt_phojet","Pt of the Best Photon",150,0,1500);
  h_nJets_phojet=new TH1D("nJets_phojet","nJets",25,0,25);
  h_hadAk8Mass_phojet=new TH1D("hadAk8Mass_phojet","Soft dropped Mass of AK8 Jet",1000,0,300);
  h_SBins_v6_CD_EW_50bin_phojet = new TH1D("AllSBins_v6_CD_EW_50bin_phojet","search bins v6:[(WTag : [65,105]),(HTag : [105,140])]",52,0,52);
  h_METvBin_phojet=new TH1D("METvBin_phojet","MET in variable bins",METLowEdge_v2.size()-1,&(METLowEdge_v2[0]));//Ak8_vMass_EW                                                                

  ///// ST300 /////////
  h_ST_ST300=new TH1D("ST_ST300","ST",400,0,4000);
  h_MET_ST300=new TH1D("MET_ST300","MET",200,0,2000);
  h_BTags_ST300=new TH1D("nBTags_ST300","no. of B tags",10,0,10);
  h_BestPhotonPt_ST300=new TH1D("BestPhotonPt_ST300","Pt of the Best Photon",150,0,1500);
  h_nJets_ST300=new TH1D("nJets_ST300","nJets",25,0,25);
  h_hadAk8Mass_ST300=new TH1D("hadAk8Mass_ST300","Soft dropped Mass of AK8 Jet",1000,0,300);
  h_SBins_v6_CD_EW_50bin_ST300 = new TH1D("AllSBins_v6_CD_EW_50bin_ST300","search bins v6:[(WTag : [65,105]),(HTag : [105,140])]",52,0,52);
  h_METvBin_ST300=new TH1D("METvBin_ST300","MET in variable bins",METLowEdge_v2.size()-1,&(METLowEdge_v2[0]));//Ak8_vMass_EW                                                                

  ///// dphi /////////
  h_ST_dphi=new TH1D("ST_dphi","ST",400,0,4000);
  h_MET_dphi=new TH1D("MET_dphi","MET",200,0,2000);
  h_BTags_dphi=new TH1D("nBTags_dphi","no. of B tags",10,0,10);
  h_BestPhotonPt_dphi=new TH1D("BestPhotonPt_dphi","Pt of the Best Photon",150,0,1500);
  h_nJets_dphi=new TH1D("nJets_dphi","nJets",25,0,25);
  h_hadAk8Mass_dphi=new TH1D("hadAk8Mass_dphi","Soft dropped Mass of AK8 Jet",1000,0,300);
  h_SBins_v6_CD_EW_50bin_dphi = new TH1D("AllSBins_v6_CD_EW_50bin_dphi","search bins v6:[(WTag : [65,105]),(HTag : [105,140])]",52,0,52);
  h_METvBin_dphi=new TH1D("METvBin_dphi","MET in variable bins",METLowEdge_v2.size()-1,&(METLowEdge_v2[0]));//Ak8_vMass_EW                                                                
  ////////////////////////////////////////////////////////////////////

  
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

  h_SBins_v6_CD = new TH1D("AllSBins_v6_CD","search bins v6:[0b,1b] x [(NJ=2to4),(NJ:5or6),(NJ>=7)]_CD",37,0,37);
 h_SBins_v6_CD_EW_43bin = new TH1D("AllSBins_v6_CD_EW_43bin","search bins v6:[0b,1b] x [(NJ=2to4),(NJ:5or6),(NJ>=7)] [(WTag : [65,105]),(HTag : [105,140])]",43,0.5,43.5);
 h_SBins_v6_CD_EW_50bin = new TH1D("AllSBins_v6_CD_EW_50bin","search bins v6:[(WTag : [65,105]),(HTag : [105,140])]",52,0,52);
 h_SBins_v6_CD_EW_50bin_elec1_closure = new TH1D("AllSBins_v6_CD_EW_50bin_elec1_closure","search bins v6:[(WTag : [65,105]),(HTag : [105,140])]",52,0,52);
 h_SBins_v6_CD_EW_14bin = new TH1D("AllSBins_v6_CD_EW_14bin","search bins v6:[0b,1b] x [(NJ=2to4),(NJ:5or6),(NJ>=7)] [(WTag : [65,105]),(HTag : [105,140])]",14,0.5,14.5);
 h_SBins_v7_CD_EW_14bin = new TH1D("AllSBins_v7_CD_EW_14bin","search bins v6:[0b,1b] x [(NJ=2to4),(NJ:5or6),(NJ>=7)] [(WTag : [65,105]),(HTag : [105,140])]",14,0.5,14.5);
 h_SBins_v6_CD_EW_7bin = new TH1D("AllSBins_v6_CD_EW_7bin","search bins v6:[(WTag : [65,105])]",7,0.5,7.5);
 h_SBins_v6_CD_EW_7bin_noSB = new TH1D("AllSBins_v6_CD_EW_7bin_noSB","search bins v6:[(WTag : [65,105])]",7,0.5,7.5);
 h_SBins_v7_CD_EW_7bin_noSB = new TH1D("AllSBins_v7_CD_EW_7bin_noSB","search bins v7:[(WTag : [65,105])]",7,0.5,7.5);

  h_SBins_v6_CD_EW = new TH1D("AllSBins_v6_CD_EW","search bins v6:[0b,1b] x [(NJ=2to4),(NJ:5or6),(NJ>=7)]_CD",37,0.5,37.5);
  h_SBins_v6_CD_EW_htag = new TH1D("AllSBins_v6_CD_EW_htag","search bins v6:[0b,1b] x [(NJ=2to4),(NJ:5or6),(NJ>=7)]_CD",37,0.5,37.5);
  h_SBins_v6_CD_SP = new TH1D("AllSBins_v6_CD_SP","search bins v6:[0b,1b] x [(NJ=2to4),(NJ:5or6),(NJ>=7)]_CD",37,0.5,37.5 );

  h_SBins_v7_CD = new TH1D("AllSBins_v7_CD","search bins v7:[0b,1b] x [(NJ=2to4),(NJ:5or6),(NJ>=7)]_CD",32,0,32);
  h_SBins_v7_CD_EW = new TH1D("AllSBins_v7_CD_EW","search bins v7:[0b,1b] x [(NJ=2to4),(NJ:5or6),(NJ>=7)]_CD",31,0.5,31.5);
  h_SBins_v7_CD_EW_htag = new TH1D("AllSBins_v7_CD_EW_htag","search bins v7:[0b,1b] x [(NJ=2to4),(NJ:5or6),(NJ>=7)]_CD",31,0.5,31.5);
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

