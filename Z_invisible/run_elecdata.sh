#!/bin/sh

rm *CR.root
rm *CR_v18.root

./z_invisible runlist_TTG_2016_v18.txt TTG_2016_CR_v18.root TTG_v17_2016
./z_invisible runlist_WG_2016_v18.txt WG_2016_CR_v18.root  WG_v17_2016
./z_invisible runlist_DYJetsToLL_2016_v18.txt   DYJetsToLL_2016_CR_v18.root  DYJetsToLL_v17_2016
./z_invisible runlist_ZGToLLG_2016_v18.txt	ZGToLLG_2016_CR_v18.root    ZGToLLG_v17_2016
hadd -f ZJZGToLL_2016_CR_v18.root DYJetsToLL_2016_CR_v18.root ZGToLLG_2016_CR_v18.root 
hadd -f TTWZJZGToLL_2016_CR_v18.root  ZJZGToLL_2016_CR_v18.root TTG_2016_CR_v18.root WG_2016_CR_v18.root


./z_invisible Run2016_SingleElectron_data.txt Run2016_elecdata_CR_v18.root elec_data_2016
./z_invisible Run2017_SingleElectron_data.txt Run2017_elecdata_CR_v18.root elec_data_2017
./z_invisible Run2018_SingleElectron_data.txt Run2018_elecdata_CR_v18.root elec_data_2018
hadd -f Run2_elecdata_CR_v18.root Run201*_elecdata_CR_v18.root

./z_invisible runlist_TTG_2017_v18.txt TTG_2017_CR_v18.root TTG_v17_2017
./z_invisible runlist_WG_2017_v18.txt WG_2017_CR_v18.root  WG_v17_2017
./z_invisible runlist_DYJetsToLL_2017_v18.txt   DYJetsToLL_2017_CR_v18.root  DYJetsToLL_v17_2017
./z_invisible runlist_ZGToLLG_2017_v18.txt	ZGToLLG_2017_CR_v18.root    ZGToLLG_v17_2017
hadd -f ZJZGToLL_2017_CR_v18.root DYJetsToLL_2017_CR_v18.root ZGToLLG_2017_CR_v18.root 
hadd -f TTWZJZGToLL_2017_CR_v18.root  ZJZGToLL_2017_CR_v18.root TTG_2017_CR_v18.root WG_2017_CR_v18.root


./z_invisible runlist_TTG_2018_v18.txt TTG_2018_CR_v18.root TTG_v17_2018
./z_invisible runlist_WG_2018_v18.txt WG_2018_CR_v18.root  WG_v17_2018
./z_invisible runlist_DYJetsToLL_2018_v18.txt   DYJetsToLL_2018_CR_v18.root  DYJetsToLL_v17_2018
./z_invisible runlist_ZGToLLG_2018_v18.txt	ZGToLLG_2018_CR_v18.root    ZGToLLG_v17_2018
hadd -f ZJZGToLL_2018_CR_v18.root DYJetsToLL_2018_CR_v18.root ZGToLLG_2018_CR_v18.root 
hadd -f TTWZJZGToLL_2018_CR_v18.root  ZJZGToLL_2018_CR_v18.root TTG_2018_CR_v18.root WG_2018_CR_v18.root

hadd -f ZJZGToLL_CR_v18.root ZJZGToLL_201*_CR_v18.root
hadd -f TTWZJZGToLL_CR_v18.root TTWZJZGToLL_201*_CR_v18.root
hadd -f TTG_CR_v18.root TTG_201*_CR_v18.root
hadd -f WG_CR_v18.root WG_201*_CR_v18.root
hadd -f DYJetsToLL_CR_v18.root DYJetsToLL_201*_CR_v18.root
hadd -f ZGToLLG_CR_v18.root ZGToLLG_201*_CR_v18.root