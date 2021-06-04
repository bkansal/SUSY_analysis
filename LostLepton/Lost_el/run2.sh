#!/bin/bash


rm TTWGJets_*_CR_v18.root
rm TTJets_*_CR_v18.root
rm TTWGJ_*_CR_v18.root
rm *_CR_v18.root
./lostlepton runList_TTGJets_2016_CR_v18.txt TTGJets_2016_CR_v18.root TTG_v17_2016
./lostlepton runList_WGJets_2016_CR_v18.txt WGJets_2016_CR_v18.root WG_v17_2016
hadd -f TTWGJets_2016_CR_v18.root TTGJets_2016_CR_v18.root WGJets_2016_CR_v18.root
./lostlepton runList_TTJets-inc_2016_CR_v18.txt TTJetsinc_2016_CR_v18.root TTJets2_v17_2016
./lostlepton runList_TTJets-HT_2016_CR_v18.txt TTJetsHT_2016_CR_v18.root TTJets_v17_2016
./lostlepton runList_WJets_2016_CR_v18.txt WJets_2016_CR_v18.root WJets_v17_2016
hadd -f TTJets_2016_CR_v18.root TTJetsHT_2016_CR_v18.root TTJetsinc_2016_CR_v18.root
hadd -f TTWGJ_2016_CR_v18.root TTGJets_2016_CR_v18.root  WGJets_2016_CR_v18.root TTJets_2016_CR_v18.root WJets_2016_CR_v18.root
./lostlepton Run2016_METdata_CR_v18.txt Run2016_METdata_CR_v18.root data_2016

./lostlepton runList_TTGJets_2017_CR_v18.txt TTGJets_2017_CR_v18.root TTG_v17_2017
./lostlepton runList_WGJets_2017_CR_v18.txt WGJets_2017_CR_v18.root WG_v17_2017
hadd -f TTWGJets_2017_CR_v18.root TTGJets_2017_CR_v18.root WGJets_2017_CR_v18.root
./lostlepton runList_TTJets-inc_2017_CR_v18.txt TTJetsinc_2017_CR_v18.root TTJets2_v17_2017
./lostlepton runList_TTJets-HT_2017_CR_v18.txt TTJetsHT_2017_CR_v18.root TTJets_v17_2017
./lostlepton runList_WJets_2017_CR_v18.txt WJets_2017_CR_v18.root WJets_v17_2017
hadd -f TTJets_2017_CR_v18.root TTJetsHT_2017_CR_v18.root TTJetsinc_2017_CR_v18.root
hadd -f TTWGJ_2017_CR_v18.root TTGJets_2017_CR_v18.root  WGJets_2017_CR_v18.root TTJets_2017_CR_v18.root WJets_2017_CR_v18.root
./lostlepton Run2017_METdata_CR_v18.txt Run2017_METdata_CR_v18.root data_2017

./lostlepton runList_TTGJets_2018_CR_v18.txt TTGJets_2018_CR_v18.root TTG_v17_2018
./lostlepton runList_WGJets_2018_CR_v18.txt WGJets_2018_CR_v18.root WG_v17_2018
hadd -f TTWGJets_2018_CR_v18.root TTGJets_2018_CR_v18.root WGJets_2018_CR_v18.root
./lostlepton runList_TTJets-inc_2018_CR_v18.txt TTJetsinc_2018_CR_v18.root TTJets2_v17_2018
./lostlepton runList_TTJets-HT_2018_CR_v18.txt TTJetsHT_2018_CR_v18.root TTJets_v17_2018
./lostlepton runList_WJets_2018_CR_v18.txt WJets_2018_CR_v18.root WJets_v17_2018
hadd -f TTJets_2018_CR_v18.root TTJetsHT_2018_CR_v18.root TTJetsinc_2018_CR_v18.root
hadd -f TTWGJ_2018_CR_v18.root TTGJets_2018_CR_v18.root  WGJets_2018_CR_v18.root TTJets_2018_CR_v18.root WJets_2018_CR_v18.root
./lostlepton Run2018_METdata_CR_v18.txt Run2018_METdata_CR_v18.root data_2018

hadd -f TTJets_CR_v18.root TTJets_201*_CR_v18.root 
hadd -f TTGJets_CR_v18.root TTGJets_201*_CR_v18.root 
hadd -f WGJets_CR_v18.root WGJets_201*_CR_v18.root 
hadd -f WJets_CR_v18.root WJets_201*_CR_v18.root 

hadd -f TTWGJets_CR_v18.root TTWGJets_201*_CR_v18.root 
hadd -f TTWGJ_CR_v18.root TTWGJ_201*_CR_v18.root

hadd -f Run2_METdata_CR_v18.root Run201*_METdata_CR_v18.root
