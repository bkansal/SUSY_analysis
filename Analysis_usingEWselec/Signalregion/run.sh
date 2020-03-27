#!/bin/bash
# ./analyzeLightBSM unskimmed_SR/runList_unskimmed_T5bbbbZg_1800_150.txt rootoutput/T5bbbbZg_1800_150_FastSim.root FastSim_T5bbbbZg_1800_150
# ./analyzeLightBSM unskimmed_SR/runList_unskimmed_T5bbbbZg_1800_150.txt rootoutput/T5bbbbZg_1800_150_FastSim_nocut.root FastSim_T5bbbbZg_1800_150
# ./analyzeLightBSM unskimmed_SR/runList_unskimmed_T5bbbbZg_1800_1750.txt rootoutput/T5bbbbZg_1800_1750_FastSim_nocut.root FastSim_T5bbbbZg_1800_1750
# ./analyzeLightBSM unskimmed_SR/runList_unskimmed_TChiWg_0_800.txt rootoutput/TChiWg_0_800_FastSim_nocut.root FastSim_TChiWg_0_800
# ./analyzeLightBSM unskimmed_SR/runList_unskimmed_T5bbbbZg_1800_1750.txt rootoutput/T5bbbbZg_1800_1750_FastSim.root FastSim_T5bbbbZg_1800_1750

# ./analyzeLightBSM unskimmed_SR/runList_unskimmed_T5bbbbZg_1800_150.txt rootoutput/T5bbbbZg_1800_150_FastSim_v17.root FastSim_T5bbbbZg_1800_150
# ./analyzeLightBSM unskimmed_SR/runList_unskimmed_T5bbbbZg_1800_1750.txt rootoutput/T5bbbbZg_1800_1750_FastSim_v17.root FastSim_T5bbbbZg_1800_1750
# ./analyzeLightBSM unskimmed_SR/runList_unskimmed_TChiWg_0_800.txt rootoutput/TChiWg_0_800_FastSim_v17.root FastSim_TChiWg_0_800
# ./analyzeLightBSM unskimmed_SR/runList_unskimmed_TChiWg_0_800.txt rootoutput/tmp.root FastSim_TChiWg_0_800
# rm rootoutput/tmp.root

#==================using v12 ntuples=======================================


# ./analyzeLightBSM unskimmed_SR/runList_unskimmed_T5bbbbZg_1800_150.txt rootoutput/T5bbbbZg_1800_150_FastSim_v12.root FastSim_T5bbbbZg
# ./analyzeLightBSM unskimmed_SR/runList_unskimmed_T5bbbbZg_1800_1750.txt rootoutput/T5bbbbZg_1800_1750_FastSim_v12.root FastSim_T5bbbbZg

#./analyzeLightBSM skimmed_BR_v12/runList_ZJetsToNuNu.txt rootoutput/ZJetsToNuNu_v12.root ZJets
#./analyzeLightBSM skimmed_BR_v12/runList_ZGJetsToNuNuG.txt rootoutput/ZGJetsToNuNuG_v12.root ZG_2016_v12
# hadd -f rootoutput/ZGZJ_NuNuG_v12.root rootoutput/ZJetsToNuNu_v12.root rootoutput/ZGJetsToNuNuG_v12.root
# ./analyzeLightBSM skimmed_BR_v12/runList_QCD.txt rootoutput/QCD_v12.root QCD_v12
# ./analyzeLightBSM skimmed_BR_v12/runList_GJets.txt rootoutput/GJets_v12.root GJets_v12
# # ./analyzeLightBSM skimmed_BR_v12/runList_GJets_lowStat.txt rootoutput/GJets_lowStat_v12.root GJets
# hadd -f rootoutput/GJetsQCD_new_v12.root rootoutput/QCD_v12.root rootoutput/GJets_v12.root #rootoutput/GJets_lowStat_v12.root
# ./analyzeLightBSM skimmed_BR_v12/runList_WJetsToLNu.txt rootoutput/WJetsToLNu_v12.root WJets_v12
# ./analyzeLightBSM skimmed_BR_v12/runList_WGToLNuG.txt rootoutput/WGJetsToLNuG_v12.root WG_v12
# ./analyzeLightBSM skimmed_BR_v12/runList_TTJets.txt rootoutput/TTJetsHT_v12.root TTJets_v12
# ./analyzeLightBSM skimmed_BR_v12/runList_TTGJets.txt rootoutput/TTGJets_v12.root TTG_v12
#
#hadd -f rootoutput/Allbkg_v12.root rootoutput/*_v12.root
#
#==================using v17 ntuples=======================================

./analyzeLightBSM unskimmed_SR_v17/runList_unskimmed_T5bbbbZg_1800_150_2016_v17.txt rootoutput/T5bbbbZg_1800_150_FastSim_2016_v17.root FastSim_T5bbbbZg_2016
./analyzeLightBSM unskimmed_SR_v17/runList_unskimmed_T5bbbbZg_1800_1750_2016_v17.txt rootoutput/T5bbbbZg_1800_1750_FastSim_2016_v17.root FastSim_T5bbbbZg_2016
# ./analyzeLightBSM unskimmed_SR_v17/runList_unskimmed_T5bbbbZg_1800_150_2017_v17.txt rootoutput/T5bbbbZg_1800_150_2017_FastSim_v17.root FastSim_T5bbbbZg_2017
# ./analyzeLightBSM unskimmed_SR_v17/runList_unskimmed_T5bbbbZg_1800_1750_2017_v17.txt rootoutput/T5bbbbZg_1800_1750_2017_FastSim_v17.root FastSim_T5bbbbZg_2017
# ./analyzeLightBSM unskimmed_SR_v17/runList_unskimmed_T5bbbbZg_1800_150_2018_v17.txt rootoutput/T5bbbbZg_1800_150_FastSim_2018_v17.root FastSim_T5bbbbZg_2018
# ./analyzeLightBSM unskimmed_SR_v17/runList_unskimmed_T5bbbbZg_1800_1750_2018_v17.txt rootoutput/T5bbbbZg_1800_1750_FastSim_2018_v17.root FastSim_T5bbbbZg_2018

##./analyzeLightBSM unskimmed_SR_v17/runList_unskimmed_T5bbbbZg_1800_1000_v17.txt rootoutput/T5bbbbZg_1800_1000_FastSim_v17.root FastSim_T5
##./analyzeLightBSM unskimmed_SR_v17/runList_unskimmed_T5bbbbZg_2000_200_v17.txt rootoutput/T5bbbbZg_2000_200_FastSim_v17.root FastSim_T5
##./analyzeLightBSM unskimmed_SR_v17/runList_unskimmed_T5bbbbZg_2000_500_v17.txt rootoutput/T5bbbbZg_2000_500_FastSim_v17.root FastSim_T5
##./analyzeLightBSM unskimmed_SR_v17/runList_unskimmed_T5bbbbZg_2000_1000_v17.txt rootoutput/T5bbbbZg_2000_1000_FastSim_v17.root FastSim_T5
## # # # ./analyzeLightBSM unskimmed_SR_v17/runList_unskimmed_TChiWg_0_800_v17.txt rootoutput/TChiWg_0_800_FastSim_v17.root FastSim_TChi
# ./analyzeLightBSM unskimmed_SR_v17/runList_unskimmed_TChiWg_0_800_v17.txt rootoutput/TChiWg_0_800_FastSim_v17.root FastSim_TChiWG_2016
# ### # # # ./analyzeLightBSM unskimmed_SR_v17/runList_unskimmed_TChiWg_0_1300_v17.txt rootoutput/TChiWg_0_1300_FastSim_v17.root FastSim_TChi
# ./analyzeLightBSM unskimmed_SR_v17/runList_unskimmed_TChiWg_0_1200_v17.txt rootoutput/TChiWg_0_1200_FastSim_v17.root FastSim_TChiWG_2016
# ### # # # ./analyzeLightBSM unskimmed_SR_v17/runList_unskimmed_TChiWg_0_1600_v17.txt rootoutput/TChiWg_0_1600_FastSim_v17.root FastSim_TChi
# ./analyzeLightBSM unskimmed_SR_v17/runList_unskimmed_TChiNg_0_800_v17.txt rootoutput/TChiNg_0_800_FastSim_v17.root FastSim_TChiNG_2016
# ./analyzeLightBSM unskimmed_SR_v17/runList_unskimmed_TChiNg_0_1200_v17.txt rootoutput/TChiNg_0_1200_FastSim_v17.root FastSim_TChiNG_2016
# #
# ./analyzeLightBSM skimmed_BR_v17/runList_ZJetsToNuNu_2016.txt rootoutput/ZJetsToNuNu_2016_v17.root ZJets_v17_2016
# ./analyzeLightBSM skimmed_BR_v17/runList_ZJetsToNuNu_2017.txt rootoutput/ZJetsToNuNu_2017_v17.root ZJets_v17_2017
# ./analyzeLightBSM skimmed_BR_v17/runList_ZJetsToNuNu_2018.txt rootoutput/ZJetsToNuNu_2018_v17.root ZJets_v17_2018
# #./analyzeLightBSM skimmed_BR_v17/runList_ZGJetsToNuNuG_2016.txt rootoutput/ZGJetsToNuNuG_2016_v17.root ZG_v17_2016
# ./analyzeLightBSM skimmed_BR_v17/runList_ZGJetsToNuNuG_2017.txt rootoutput/ZGJetsToNuNuG_2017_v17.root ZG_v17_2017
# ./analyzeLightBSM skimmed_BR_v17/runList_ZGJetsToNuNuG_2018.txt rootoutput/ZGJetsToNuNuG_2018_v17.root ZG_v17_2018
# hadd -f rootoutput/ZGZJ_NuNuG_v17.root rootoutput/ZJetsToNuNu_*_v17.root rootoutput/ZGJetsToNuNuG_*_v17.root


# ./analyzeLightBSM skimmed_BR_v17/runList_QCD_2016.txt rootoutput/QCD_2016_v17.root QCD_v17_2016
# ./analyzeLightBSM skimmed_BR_v17/runList_QCD_2017.txt rootoutput/QCD_2017_v17.root QCD_v17_2017
# ./analyzeLightBSM skimmed_BR_v17/runList_QCD_2018.txt rootoutput/QCD_2018_v17.root QCD_v17_2018
# ./analyzeLightBSM skimmed_BR_v17/runList_GJets_2016.txt rootoutput/GJets_2016_v17.root GJets_v17_2016
# ./analyzeLightBSM skimmed_BR_v17/runList_GJets_2017.txt rootoutput/GJets_2017_v17.root GJets_v17_2017
# ./analyzeLightBSM skimmed_BR_v17/runList_GJets_2018.txt rootoutput/GJets_2018_v17.root GJets_v17_2018
# hadd -f rootoutput/GJetsQCD_new_v17.root rootoutput/QCD_*_v17.root rootoutput/GJets_*_v17.root
# # ./analyzeLightBSM skimmed_BR_v17/runList_GJets.txt rootoutput/GJets_v17.root GJets_v17
# # ./analyzeLightBSM skimmed_BR_v17/runList_GJets_lowstats.txt rootoutput/GJets_lowstats_v17.root GJets_v17
# # hadd -f rootoutput/GJetsQCD_new_v17.root rootoutput/QCD_v17.root rootoutput/GJets_v17.root

# ./analyzeLightBSM skimmed_BR_v17/runList_WJetsToLNu_2016.txt rootoutput/WJetsToLNu_2016_v17.root WJets_v17_2016
# ./analyzeLightBSM skimmed_BR_v17/runList_WJetsToLNu_2017.txt rootoutput/WJetsToLNu_2017_v17.root WJets_v17_2017
# ./analyzeLightBSM skimmed_BR_v17/runList_WJetsToLNu_2018.txt rootoutput/WJetsToLNu_2018_v17.root WJets_v17_2018
# hadd -f rootoutput/WJetsToLNu_v17.root rootoutput/WJetsToLNu_*_v17.root

# ./analyzeLightBSM skimmed_BR_v17/runList_WGToLNuG_2016.txt rootoutput/WGJetsToLNuG_2016_v17.root WG_v17_2016
# ./analyzeLightBSM skimmed_BR_v17/runList_WGToLNuG_2017.txt rootoutput/WGJetsToLNuG_2017_v17.root WG_v17_2017
# ./analyzeLightBSM skimmed_BR_v17/runList_WGToLNuG_2018.txt rootoutput/WGJetsToLNuG_2018_v17.root WG_v17_2018
# hadd -f rootoutput/WGJetsToLNuG_v17.root rootoutput/WGJetsToLNuG_*_v17.root

# ./analyzeLightBSM skimmed_BR_v17/runList_TTJets_2016.txt rootoutput/TTJetsHT1_2016_v17.root TTJets_v17_2016
# ./analyzeLightBSM skimmed_BR_v17/runList_TTJets_2017.txt rootoutput/TTJetsHT1_2017_v17.root TTJets_v17_2017
# ./analyzeLightBSM skimmed_BR_v17/runList_TTJets_2018.txt rootoutput/TTJetsHT1_2018_v17.root TTJets_v17_2018
# ./analyzeLightBSM skimmed_BR_v17/runList_TTJets2_2016.txt rootoutput/TTJetsHT2_2016_v17.root TTJets2_v17_2016
# ./analyzeLightBSM skimmed_BR_v17/runList_TTJets2_2017.txt rootoutput/TTJetsHT2_2017_v17.root TTJets2_v17_2017
# ./analyzeLightBSM skimmed_BR_v17/runList_TTJets2_2018.txt rootoutput/TTJetsHT2_2018_v17.root TTJets2_v17_2018
# hadd -f rootoutput/TTJetsHT_v17.root rootoutput/TTJetsHT1_*_v17.root rootoutput/TTJetsHT2_*_v17.root

# ./analyzeLightBSM skimmed_BR_v17/runList_TTGJets_2016.txt rootoutput/TTGJets_2016_v17.root  TTG_v17_2016
# ./analyzeLightBSM skimmed_BR_v17/runList_TTGJets_2017.txt rootoutput/TTGJets_2017_v17.root  TTG_v17_2017
# ./analyzeLightBSM skimmed_BR_v17/runList_TTGJets_2018.txt rootoutput/TTGJets_2018_v17.root  TTG_v17_2018
# hadd -f rootoutput/TTGJets_v17.root rootoutput/TTGJets_*_v17.root



####==================using v16 ntuples=======================================

# ./analyzeLightBSM skimmed_BR_v16/runList_ZJetsToNuNu.txt rootoutput/ZJetsToNuNu_v16.root ZJets_v16
# # ./analyzeLightBSM skimmed_BR_v16/runList_ZGJetsToNuNuG.txt rootoutput/ZGJetsToNuNuG_v16.root ZG_v16
# # hadd -f rootoutput/ZGZJ_NuNuG_v16.root rootoutput/ZJetsToNuNu_v16.root rootoutput/ZGJetsToNuNuG_v16.root
# ./analyzeLightBSM skimmed_BR_v16/runList_QCD.txt rootoutput/QCD_v16.root QCD_v16
# ./analyzeLightBSM skimmed_BR_v16/runList_GJets.txt rootoutput/GJets_v16.root GJets_v16
# hadd -f rootoutput/GJetsQCD_new_v16.root rootoutput/QCD_v16.root rootoutput/GJets_v16.root
# ./analyzeLightBSM skimmed_BR_v16/runList_WJetsToLNu.txt rootoutput/WJetsToLNu_v16.root WJets_v16
# ./analyzeLightBSM skimmed_BR_v16/runList_WGToLNuG.txt rootoutput/WGJetsToLNuG_v16.root WG_v16
# ./analyzeLightBSM skimmed_BR_v16/runList_TTJets.txt rootoutput/TTJetsHT_v16.root TTJets_v16
# ./analyzeLightBSM skimmed_BR_v16/runList_TTGJets.txt rootoutput/TTGJets_v16.root  TTG_v16


# ./analyzeLightBSM runList_T5bbbbZg_1800_150.txt T5bbbbZg_1800_150_FastSim.root FastSim_T5bbbbZg
# ./analyzeLightBSM runList_T5bbbbZg_1800_1750.txt T5bbbbZg_1800_1750_FastSim.root FastSim_T5bbbbZg

#./analyzeLightBSM runList_T5bbbbZg_1600_150.txt T5bbbbZg_1600_150_FastSim.root FastSim_T5bbbbZg
#./analyzeLightBSM runList_T5bbbbZg_1600_1000.txt T5bbbbZg_1600_1000_FastSim.root FastSim_T5bbbbZg
#./analyzeLightBSM runList_T5bbbbZg_1600_1550.txt T5bbbbZg_1600_1550_FastSim.root FastSim_T5bbbbZg

#./analyzeLightBSM runList_T5qqqqHg_1600_150.txt T5qqqqHg_1600_150_FastSim.root FastSim_T5qqqqHg
#./analyzeLightBSM runList_T5qqqqHg_1600_1000.txt T5qqqqHg_1600_1000_FastSim.root FastSim_T5qqqqHg
#./analyzeLightBSM runList_T5qqqqHg_1600_1550.txt T5qqqqHg_1600_1550_FastSim.root FastSim_T5qqqqHg

#./analyzeLightBSM runList_T6ttZg_900_100.txt T6ttZg_900_100_FastSim.root FastSim_T6ttZg
#./analyzeLightBSM runList_T6ttZg_900_750.txt T6ttZg_900_750_FastSim.root FastSim_T6ttZg

#./analyzeLightBSM runList_GGM_M1M3_1100_1000.txt GGM_M1M3_1100_1000_FastSim.root FastSim_GGM_M1M3
#./analyzeLightBSM runList_GGM_M1M3_1100_200.txt GGM_M1M3_1100_200_FastSim.root FastSim_GGM_M1M3
#./analyzeLightBSM runList_GGM_M1M3_1600_200.txt GGM_M1M3_1600_200_FastSim.root FastSim_GGM_M1M3



#./analyzeLightBSM runList_T1bbbb_ZG_mGl1600_NLSP150.txt T1bbbb_ZG_mGl1600_NLSP150.root SignalZ
#./analyzeLightBSM runList_T1bbbb_ZG_mGl1600_NLSP1000.txt T1bbbb_ZG_mGl1600_NLSP1000.root SignalZ
#./analyzeLightBSM runList_T1bbbb_ZG_mGl1600_NLSP1550.txt T1bbbb_ZG_mGl1600_NLSP1550.root SignalZ


#./analyzeLightBSM runList_ZJetsToNuNu.txt ZJetsToNuNu.root nonprompt
#./analyzeLightBSM runList_ZGJetsToNuNuG.txt ZGJetsToNuNuG.root prompt
#./analyzeLightBSM runList_QCD.txt QCD.root nonprompt
#./analyzeLightBSM runList_GJets.txt GJets.root prompt
#./analyzeLightBSM runList_WJetsToLNu.txt WJetsToLNu.root WJetsToLNu
#./analyzeLightBSM runList_WGToLNuG.txt WGJetsToLNuG.root WG
#./analyzeLightBSM runList_TTJets.txt TTJetsHT.root TTJets_HT
#./analyzeLightBSM runList_TTGJets.txt TTGJets.root TTGJets
