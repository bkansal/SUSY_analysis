#!/bin/sh

rm *CR.root
rm *CR_v18.root

./mulijet runlist_GJets_DR_2016_v18.txt GJets_DR_2016_CR_v18.root GJetsDR_v17_2016
#./mulijet runlist_GJets_HT_2016_v18.txt GJets_HT_2016_CR_v18.root GJets_v17_2016
./mulijet runlist_QCD_2016_v18.txt QCD_2016_CR_v18.root QCD_v17_2016
hadd -f GJetsQCD_new_2016_v18.root GJets_DR_2016_CR_v18.root QCD_2016_CR_v18.root

./mulijet runlist_GJets_DR_2017_v18.txt GJets_DR_2017_CR_v18.root GJetsDR_v17_2017
#./mulijet runlist_GJets_HT_2017_v18.txt GJets_HT_2017_CR_v18.root GJets_v17_2017
./mulijet runlist_QCD_2017_v18.txt QCD_2017_CR_v18.root QCD_v17_2017
hadd -f GJetsQCD_new_2017_v18.root GJets_DR_2017_CR_v18.root QCD_2017_CR_v18.root

./mulijet runlist_GJets_DR_2018_v18.txt GJets_DR_2018_CR_v18.root GJetsDR_v17_2018
#./mulijet runlist_GJets_HT_2018_v18.txt GJets_HT_2018_CR_v18.root GJets_v17_2018
./mulijet runlist_QCD_2018_v18.txt QCD_2018_CR_v18.root QCD_v17_2018
hadd -f GJetsQCD_new_2018_v18.root GJets_DR_2018_CR_v18.root  QCD_2018_CR_v18.root

hadd -f GJetsQCD_new_v18.root GJetsQCD_new_201*_v18.root



#./mulijet runlist_TTG_2016_v18.txt TTGJets_2016_CR_v18.root TTG_v17_2016
#./mulijet runlist_TTJets_HT_2016_v18.txt TTJets_HT_2016_CR_v18.root TTJets_v17_2016
#./mulijet runlist_TTJets_inc_2016_v18.txt TTJets_inc_2016_CR_v18.root TTJets2_v17_2016
#hadd -f TTJetsHT_2016_CR_v18.root  TTJets_*_2016_CR_v18.root
#./mulijet runlist_WJets_2016_v18.txt WJetsToLNu_2016_v18.root  WJets_v17_2016
#./mulijet runlist_WG_2016_v18.txt WGJetsToLNuG_2016_v18.root  WG_v17_2016
#hadd -f WGJets_2016_CR_v18.root WJets_2016_CR_v18.root WG_2016_CR_v18.root
#./mulijet runlist_ZGToNuNuG_2016_v18.txt    ZGToNuNuG_2016_CR_v18.root  ZGToNuNuG_v17_2016
#./mulijet runlist_ZJetsToNuNu_2016_v18.txt  ZJetsToNuNu_2016_CR_v18.root ZJetsToNuNu_v17_2016
#hadd -f ZGZJ_NuNuG_2016_v18.root ZGToNuNuG_2016_CR_v18.root ZJetsToNuNu_2016_CR_v18.root
#./mulijet runlist_DYJetsToLL_2016_v18.txt   DYJetsToLL_2016_CR_v18.root  DYJetsToLL_v17_2016
#./mulijet runlist_ZGToLLG_2016_v18.txt	ZGToLLG_2016_CR_v18.root    ZGToLLG_v17_2016

#hadd -f ZJZGToLL_2016_CR_v18.root DYJetsToLL_2016_CR_v18.root ZGToLLG_2016_CR_v18.root 
#hadd -f TTWZJZGToLL_2016_CR_v18.root  ZJZGToLL_2016_CR_v18.root TTG_2016_CR_v18.root WG_2016_CR_v18.root


