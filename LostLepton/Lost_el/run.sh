#!/bin/bash

rm TTWGJets_*_CR.root
rm TTJets_*_CR.root
rm TTWGJ_*_CR.root
rm *_CR.root
./lostlepton runList_TTGJets_2016_CR.txt TTGJets_2016_CR.root TTG_v17_2016
./lostlepton runList_WGJets_2016_CR.txt WGJets_2016_CR.root WG_v17_2016
hadd -f TTWGJets_2016_CR.root TTGJets_2016_CR.root WGJets_2016_CR.root
./lostlepton runList_TTJets-inc_2016_CR.txt TTJetsinc_2016_CR.root TTJets2_v17_2016
./lostlepton runList_TTJets-HT_2016_CR.txt TTJetsHT_2016_CR.root TTJets_v17_2016
./lostlepton runList_WJets_2016_CR.txt WJets_2016_CR.root WJets_v17_2016
hadd -f TTJets_2016_CR.root TTJetsHT_2016_CR.root TTJetsinc_2016_CR.root
hadd -f TTWGJ_2016_CR.root TTGJets_2016_CR.root  WGJets_2016_CR.root TTJets_2016_CR.root WJets_2016_CR.root
./lostlepton Run2016_METdata_CR.txt Run2016_METdata_CR.root data_2016


# ./lostlepton runList_TTGJets_2017_CR.txt TTGJets_2017_CR.root TTG_v17_2017
# ./lostlepton runList_WGJets_2017_CR.txt WGJets_2017_CR.root WG_v17_2017
# hadd -f TTWGJets_2017_CR.root TTGJets_2017_CR.root WGJets_2017_CR.root
# ./lostlepton runList_TTJets-inc_2017_CR.txt TTJetsinc_2017_CR.root TTJets2_v17_2017
# ./lostlepton runList_TTJets-HT_2017_CR.txt TTJetsHT_2017_CR.root TTJets_v17_2017
# ./lostlepton runList_WJets_2017_CR.txt WJets_2017_CR.root WJets_v17_2017
# hadd -f TTJets_2017_CR.root TTJetsHT_2017_CR.root TTJetsinc_2017_CR.root
# hadd -f TTWGJ_2017_CR.root TTGJets_2017_CR.root  WGJets_2017_CR.root TTJets_2017_CR.root WJets_2017_CR.root
# ./lostlepton Run2017_METdata_CR.txt Run2017_METdata_CR.root data_2017

# ./lostlepton runList_TTGJets_2018_CR.txt TTGJets_2018_CR.root TTG_v17_2018
# ./lostlepton runList_WGJets_2018_CR.txt WGJets_2018_CR.root WG_v17_2018
# hadd -f TTWGJets_2018_CR.root TTGJets_2018_CR.root WGJets_2018_CR.root
# ./lostlepton runList_TTJets-inc_2018_CR.txt TTJetsinc_2018_CR.root TTJets2_v17_2018
# ./lostlepton runList_TTJets-HT_2018_CR.txt TTJetsHT_2018_CR.root TTJets_v17_2018
# ./lostlepton runList_WJets_2018_CR.txt WJets_2018_CR.root WJets_v17_2018
# hadd -f TTJets_2018_CR.root TTJetsHT_2018_CR.root TTJetsinc_2018_CR.root
# hadd -f TTWGJ_2018_CR.root TTGJets_2018_CR.root  WGJets_2018_CR.root TTJets_2018_CR.root WJets_2018_CR.root
# ./lostlepton Run2018_METdata_CR.txt Run2018_METdata_CR.root data_2018

# hadd -f TTJets_CR.root TTJets_201*_CR.root 
# hadd -f TTGJets_CR.root TTGJets_201*_CR.root 
# hadd -f WGJets_CR.root WGJets_201*_CR.root 
# hadd -f WJets_CR.root WJets_201*_CR.root 

# hadd -f TTWGJets_CR.root TTWGJets_201*_CR.root 
# hadd -f TTWGJ_CR.root TTWGJ_201*_CR.root

# hadd -f Run2_METdata_CR.root Run201*_METdata_CR.root
