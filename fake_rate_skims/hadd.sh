#!/bin/bash                                                                                                                                    

path=/eos/uscms/store/user/bkansal/GMSB_skims_TreesV17/SignalRegion/skims/


year=Summer16v3
   
ls ${path}/SR_${year}.TTGJets_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8.root 
ls ${path}/SR_${year}.TTJets_HT*.root 
ls ${path}/SR_${year}.TTJets_*Lept*.root 
ls ${path}/SR_${year}.WGJets_MonoPhoton_PtG-*_TuneCUETP8M1_13TeV-madgraph.root 
ls ${path}/SR_${year}.WJetsToLNu_HT-*.root 
ls ${path}/SR_${year}.ZJetsToNuNu_HT*.root 
ls ${path}/SR_${year}.ZNuNuGJets_MonoPhoton_PtG-*.root 
ls ${path}/SR_${year}.QCD_HT*.root 
ls ${path}/SR_${year}.GJets_DR*.root 


ls ${path}/SR_${year}.TTGJets_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8.root > runList_TTGJets_${year}_v17.txt
ls ${path}/SR_${year}.TTJets_HT*.root > runList_TTJets-HT_${year}_v17.txt
ls ${path}/SR_${year}.TTJets_*Lept*.root > runList_TTJets-inc_${year}_v17.txt
ls ${path}/SR_${year}.WGJets_MonoPhoton_PtG-*_TuneCUETP8M1_13TeV-madgraph.root > runList_WGJets_${year}_v17.txt
ls ${path}/SR_${year}.WJetsToLNu_HT-*.root > runList_WJets_${year}_v17.txt
ls ${path}/SR_${year}.ZJetsToNuNu_HT*.root > runList_ZJets_${year}_v17.txt
ls ${path}/SR_${year}.ZNuNuGJets_MonoPhoton_PtG-*.root > runList_ZGJets_${year}_v17.txt
ls ${path}/SR_${year}.QCD_HT*.root > runList_QCD_${year}_v17.txt
ls ${path}/SR_${year}.GJets_DR*.root > runList_GJets_${year}_v17.txt


# for year in Fall17 Autumn18
# do
#     ls ${path}/SR_${year}.TTGJets_TuneCP5_13TeV-amcatnloFXFX-madspin-pythia8.root > runList_TTGJets_${year}_v17.txt
#     ls ${path}/SR_${year}.TTJets_HT*.root > runList_TTJets-HT_${year}_v17.txt
#     ls ${path}/SR_${year}.TTJets_*Lept*.root > runList_TTJets-inc_${year}_v17.txt
#     ls ${path}/SR_${year}.WGJets_MonoPhoton_PtG-*_TuneCP5_13TeV-madgraph.root > runList_WGJets_${year}_v17.txt
#     ls ${path}/SR_${year}.WJetsToLNu_HT-*.root > runList_WJets_${year}_v17.txt
#     ls ${path}/SR_${year}.ZJetsToNuNu_HT*.root > runList_ZJets_${year}_v17.txt
#     ls ${path}/SR_${year}.ZNuNuGJets_MonoPhoton_PtG-*.root > runList_ZGJets_${year}_v17.txt
#     ls ${path}/SR_${year}.QCD_HT*.root > runList_QCD_${year}_v17.txt
#     ls ${path}/SR_${year}.GJets_DR*.root > runList_GJets_${year}_v17.txt
# done
