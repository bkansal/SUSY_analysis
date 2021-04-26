#!/bin/sh                                                                                                           

rm /eos/uscms/store/user/bkansal/GMSB_skims_TreesV18/for_bkg_estimation/Z_invisible/*job*root
ls /eos/uscms/store/user/bkansal/GMSB_skims_TreesV18/for_bkg_estimation/Z_invisible/CR_Summer16v3.DYJetsToLL_M-50_HT* > runlist_DYJetsToLL_2016_v18.txt
ls /eos/uscms/store/user/bkansal/GMSB_skims_TreesV18/for_bkg_estimation/Z_invisible/CR_Summer16v3.ZJetsToNuNu_HT* > runlist_ZJetsToNuNu_2016_v18.txt
ls /eos/uscms/store/user/bkansal/GMSB_skims_TreesV18/for_bkg_estimation/Z_invisible/CR_Summer16v3.ZLLGJets_MonoPhoton_PtG-* > runlist_ZGToLLG_2016_v18.txt
ls /eos/uscms/store/user/bkansal/GMSB_skims_TreesV18/for_bkg_estimation/Z_invisible/CR_Summer16v3.ZNuNuGJets_MonoPhoton_PtG-* > runlist_ZGToNuNuG_2016_v18.txt

ls /eos/uscms/store/user/bkansal/GMSB_skims_TreesV18/for_bkg_estimation/Z_invisible/CR_Fall17.DYJetsToLL_M-50_HT* > runlist_DYJetsToLL_2017_v18.txt
ls /eos/uscms/store/user/bkansal/GMSB_skims_TreesV18/for_bkg_estimation/Z_invisible/CR_Fall17.ZJetsToNuNu_HT* > runlist_ZJetsToNuNu_2017_v18.txt
ls /eos/uscms/store/user/bkansal/GMSB_skims_TreesV18/for_bkg_estimation/Z_invisible/CR_Fall17.ZLLGJets_MonoPhoton_PtG-* > runlist_ZGToLLG_2017_v18.txt
ls /eos/uscms/store/user/bkansal/GMSB_skims_TreesV18/for_bkg_estimation/Z_invisible/CR_Fall17.ZNuNuGJets_MonoPhoton_PtG-* > runlist_ZGToNuNuG_2017_v18.txt

ls /eos/uscms/store/user/bkansal/GMSB_skims_TreesV18/for_bkg_estimation/Z_invisible/CR_Autumn18.DYJetsToLL_M-50_HT* > runlist_DYJetsToLL_2018_v18.txt
ls /eos/uscms/store/user/bkansal/GMSB_skims_TreesV18/for_bkg_estimation/Z_invisible/CR_Autumn18.ZJetsToNuNu_HT* > runlist_ZJetsToNuNu_2018_v18.txt
ls /eos/uscms/store/user/bkansal/GMSB_skims_TreesV18/for_bkg_estimation/Z_invisible/CR_Autumn18.ZLLGJets_MonoPhoton_PtG-* > runlist_ZGToLLG_2018_v18.txt
ls /eos/uscms/store/user/bkansal/GMSB_skims_TreesV18/for_bkg_estimation/Z_invisible/CR_Autumn18.ZNuNuGJets_MonoPhoton_PtG-* > runlist_ZGToNuNuG_2018_v18.txt


sed -i "s#/eos/uscms/store/#root://cmseos.fnal.gov//store/#" runlist*.txt
