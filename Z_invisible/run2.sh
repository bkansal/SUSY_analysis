#!/bin/sh

rm *CR.root
rm *CR_v18.root


./z_invisible runlist_DYJetsToLL_2016_v18.txt   DYJetsToLL_2016_CR_v18.root  DYJetsToLL_v17_2016
./z_invisible runlist_ZGToLLG_2016_v18.txt	ZGToLLG_2016_CR_v18.root    ZGToLLG_v17_2016
hadd -f ZJZGToLL_2016_CR_v18.root DYJetsToLL_2016_CR_v18.root ZGToLLG_2016_CR_v18.root 
./z_invisible runlist_ZGToNuNuG_2016_v18.txt	ZGToNuNuG_2016_CR_v18.root  ZGToNuNuG_v17_2016
./z_invisible runlist_ZJetsToNuNu_2016_v18.txt	ZJetsToNuNu_2016_CR_v18.root ZJetsToNuNu_v17_2016
hadd -f ZJZGToNuNu_2016_CR_v18.root ZGToNuNuG_2016_CR_v18.root ZJetsToNuNu_2016_CR_v18.root

./z_invisible runlist_DYJetsToLL_2017_v18.txt   DYJetsToLL_2017_CR_v18.root  DYJetsToLL_v17_2017
./z_invisible runlist_ZGToLLG_2017_v18.txt	ZGToLLG_2017_CR_v18.root    ZGToLLG_v17_2017
hadd -f ZJZGToLL_2017_CR_v18.root DYJetsToLL_2017_CR_v18.root ZGToLLG_2017_CR_v18.root 
./z_invisible runlist_ZGToNuNuG_2017_v18.txt	ZGToNuNuG_2017_CR_v18.root  ZGToNuNuG_v17_2017
./z_invisible runlist_ZJetsToNuNu_2017_v18.txt	ZJetsToNuNu_2017_CR_v18.root ZJetsToNuNu_v17_2017
hadd -f ZJZGToNuNu_2017_CR_v18.root ZGToNuNuG_2017_CR_v18.root ZJetsToNuNu_2017_CR_v18.root


./z_invisible runlist_DYJetsToLL_2018_v18.txt   DYJetsToLL_2018_CR_v18.root  DYJetsToLL_v17_2018
./z_invisible runlist_ZGToLLG_2018_v18.txt	ZGToLLG_2018_CR_v18.root    ZGToLLG_v17_2018
hadd -f ZJZGToLL_2018_CR_v18.root DYJetsToLL_2018_CR_v18.root ZGToLLG_2018_CR_v18.root 
./z_invisible runlist_ZGToNuNuG_2018_v18.txt	ZGToNuNuG_2018_CR_v18.root  ZGToNuNuG_v17_2018
./z_invisible runlist_ZJetsToNuNu_2018_v18.txt	ZJetsToNuNu_2018_CR_v18.root ZJetsToNuNu_v17_2018
hadd -f ZJZGToNuNu_2018_CR_v18.root ZGToNuNuG_2018_CR_v18.root ZJetsToNuNu_2018_CR_v18.root

hadd -f ZJZGToNuNu_CR_v18.root ZJZGToNuNu_201*_CR_v18.root
hadd -f ZJZGToLL_CR_v18.root ZJZGToLL_201*_CR_v18.root
# ./fakerate Run2016_METdata.txt Run2016_METdata_CR_v18.root data_2016
# ./fakerate Run2017_METdata.txt Run2017_METdata_CR_v18.root data_2017
# ./fakerate Run2018_METdata.txt Run2018_METdata_CR_v18.root data_2018
