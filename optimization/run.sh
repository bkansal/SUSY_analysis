#!/bin/bash
#==================using v12 ntuples=======================================

# ./analyzeLightBSM unskimmed_SR/runList_unskimmed_T5bbbbZg_1800_150.txt rootoutput/T5bbbbZg_1800_150_FastSim_v12.root FastSim_T5bbbbZg
# ./analyzeLightBSM unskimmed_SR/runList_unskimmed_T5bbbbZg_1800_1750.txt rootoutput/T5bbbbZg_1800_1750_FastSim_v12.root FastSim_T5bbbbZg

# ./analyzeLightBSM skimmed_BR_v12/runList_ZJetsToNuNu.txt rootoutput/ZJetsToNuNu_v12.root ZJets
# ./analyzeLightBSM skimmed_BR_v12/runList_ZGJetsToNuNuG.txt rootoutput/ZGJetsToNuNuG_v12.root ZG
# hadd -f rootoutput/ZGZJ_NuNuG_v12.root rootoutput/ZJetsToNuNu_v12.root rootoutput/ZGJetsToNuNuG_v12.root
# ./analyzeLightBSM skimmed_BR_v12/runList_QCD.txt rootoutput/QCD_v12.root QCD
# ./analyzeLightBSM skimmed_BR_v12/runList_GJets.txt rootoutput/GJets_v12.root GJets
# # ./analyzeLightBSM skimmed_BR_v12/runList_GJets_lowStat.txt rootoutput/GJets_lowStat_v12.root GJets
# hadd -f rootoutput/GJetsQCD_new_v12.root rootoutput/QCD_v12.root rootoutput/GJets_v12.root #rootoutput/GJets_lowStat_v12.root
# ./analyzeLightBSM skimmed_BR_v12/runList_WJetsToLNu.txt rootoutput/WJetsToLNu_v12.root WJets
# ./analyzeLightBSM skimmed_BR_v12/runList_WGToLNuG.txt rootoutput/WGJetsToLNuG_v12.root WG
# ./analyzeLightBSM skimmed_BR_v12/runList_TTJets.txt rootoutput/TTJetsHT_v12.root TTJets
# ./analyzeLightBSM skimmed_BR_v12/runList_TTGJets.txt rootoutput/TTGJets_v12.root TTG


#==================using v17 ntuples=======================================
./analyzeLightBSM unskimmed_SR_v17/runList_unskimmed_T5bbbbZg_1800_150_v17.txt rootoutput/T5bbbbZg_1800_150_FastSim_v17.root FastSim_T5bbbbZg
./analyzeLightBSM unskimmed_SR_v17/runList_unskimmed_T5bbbbZg_1800_1750_v17.txt rootoutput/T5bbbbZg_1800_1750_FastSim_v17.root FastSim_T5bbbbZg
# ./analyzeLightBSM unskimmed_SR_v17/runList_unskimmed_T5bbbbZg_1800_1000_v17.txt rootoutput/T5bbbbZg_1800_1000_FastSim_v17.root FastSim_T5bbbbZg
# ./analyzeLightBSM unskimmed_SR_v17/runList_unskimmed_T5bbbbZg_2000_200_v17.txt rootoutput/T5bbbbZg_2000_200_FastSim_v17.root FastSim_T5bbbbZg
# ./analyzeLightBSM unskimmed_SR_v17/runList_unskimmed_T5bbbbZg_2000_500_v17.txt rootoutput/T5bbbbZg_2000_500_FastSim_v17.root FastSim_T5bbbbZg
# ./analyzeLightBSM unskimmed_SR_v17/runList_unskimmed_T5bbbbZg_2000_1000_v17.txt rootoutput/T5bbbbZg_2000_1000_FastSim_v17.root FastSim_T5bbbbZg
# # ./analyzeLightBSM unskimmed_SR_v17/runList_unskimmed_TChiWg_0_800_v17.txt rootoutput/TChiWg_0_800_FastSim_v17.root FastSim_TChiWg_0_800_v17
# # ./analyzeLightBSM unskimmed_SR_v17/runList_unskimmed_TChiWg_0_400_v17.txt rootoutput/TChiWg_0_400_FastSim_v17.root FastSim_TChiWg_0_400_v17
# # ./analyzeLightBSM unskimmed_SR_v17/runList_unskimmed_TChiWg_0_1300_v17.txt rootoutput/TChiWg_0_1300_FastSim_v17.root FastSim_TChiWg_0_1300_v17
# # ./analyzeLightBSM unskimmed_SR_v17/runList_unskimmed_TChiWg_0_1200_v17.txt rootoutput/TChiWg_0_1200_FastSim_v17.root FastSim_TChiWg_0_1200_v17
# # ./analyzeLightBSM unskimmed_SR_v17/runList_unskimmed_TChiWg_0_1600_v17.txt rootoutput/TChiWg_0_1600_FastSim_v17.root FastSim_TChiWg_0_1600_v17

./analyzeLightBSM skimmed_BR_v17/runList_ZJetsToNuNu.txt rootoutput/ZJetsToNuNu_v17.root ZJets_v17
./analyzeLightBSM skimmed_BR_v17/runList_ZGJetsToNuNuG.txt rootoutput/ZGJetsToNuNuG_v17.root ZGJets_v17
hadd -f rootoutput/ZGZJ_NuNuG_v17.root rootoutput/ZJetsToNuNu_v17.root rootoutput/ZGJetsToNuNuG_v17.root
./analyzeLightBSM skimmed_BR_v17/runList_QCD.txt rootoutput/QCD_v17.root QCD_v17
./analyzeLightBSM skimmed_BR_v17/runList_GJets.txt rootoutput/GJets_v17.root GJets_v17
hadd -f rootoutput/GJetsQCD_new_v17.root rootoutput/QCD_v17.root rootoutput/GJets_v17.root
# ./analyzeLightBSM skimmed_BR_v17/runList_GJets_lowstats.txt rootoutput/GJets_lowstats_v17.root GJets_v17
# hadd -f rootoutput/GJetsQCD_new_v17.root rootoutput/QCD_v17.root rootoutput/GJets_v17.root
./analyzeLightBSM skimmed_BR_v17/runList_WJetsToLNu.txt rootoutput/WJetsToLNu_v17.root WJets_v17
./analyzeLightBSM skimmed_BR_v17/runList_WGToLNuG.txt rootoutput/WGJetsToLNuG_v17.root WG_v17
./analyzeLightBSM skimmed_BR_v17/runList_TTJets.txt rootoutput/TTJetsHT1_v17.root TTJets_v17
./analyzeLightBSM skimmed_BR_v17/runList_TTJets2.txt rootoutput/TTJetsHT2_v17.root TTJets2_v17
hadd -f rootoutput/TTJetsHT_v17.root rootoutput/TTJetsHT1_v17.root rootoutput/TTJetsHT2_v17.root
./analyzeLightBSM skimmed_BR_v17/runList_TTGJets.txt rootoutput/TTGJets_v17.root  TTG_v17

