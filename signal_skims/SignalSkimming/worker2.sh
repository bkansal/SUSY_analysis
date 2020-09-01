#!/bin/sh

#executable=$1
inputFileTag=$1
outputFileTag=$2
#commitHash=$4
#datasetName=$4
currDir=$(pwd)
######################################
# SETUP CMSSW STUFF...
######################################
source /cvmfs/cms.cern.ch/cmsset_default.sh
export SCRAM_ARCH=slc6_amd64_gcc630
# scram p CMSSW CMSSW_8_0_25
# cd CMSSW_8_0_25/src
scram p CMSSW CMSSW_10_1_0
cd CMSSW_10_1_0/src
eval `scramv1 runtime -sh`
pwd

######################################
# SETUP PRIVATE STUFF...
######################################
echo "ls"
pwd
cd -
#cd $currDir
echo "RUNNING ANALYSIS"
pwd
#root -l -b -q 'processSigFile_T5qqqqHg_.C("'$inputFileTag'","'$outputFileTag'")'
#root -l -b -q 'processSigFile_T5bbbbZg_.C("'$inputFileTag'","'$outputFileTag'")'
#root -l -b -q 'processSigFile_TChiWG_.C("'$inputFileTag'","'$outputFileTag'")'
#root -l -b -q 'processSigFile_TChiNG_.C("'$inputFileTag'","'$outputFileTag'")'
#root -l -b -q 'processSigFile_T5ttttZg_.C("'$inputFileTag'","'$outputFileTag'")'
root -l -b -q 'processSigFile_T6ttZg_.C("'$inputFileTag'","'$outputFileTag'")'
#./$executable $inputFileTag $outputFileTag $datasetName
echo "processed. ls"
ls
echo "COPYING OUTPUT"

# rm T5bbbbZg_MassScan.root T5qqqqHg_MassScan.root T5ttttZg_MassScan.root TChiNG_MassScan.root TChiWG_MassScan.root T6ttZg_MassScan.root GGM_M1M3_MassScan.root 
for FILE in *.root
do
   # xrdcp -f ${FILE} root://cmseos.fnal.gov//store/user/bkansal/myProduction/T5qqqqHg/scan_2016/
    xrdcp -f ${FILE} root://cmseos.fnal.gov//store/group/lpcsusyhad/SusyPhotonMET/Run2ProductionV17/signals/unskimmed_SortedSignalscans/tmp1/T6ttZg_2016/
# ot://cmseos.fnal.gov//store/user/vhegde/GMSB_skims_ST_RA2b_TreesV12/SignalRegion_v1/skimmed_SortedSignal/temp/
    # xrdcp -f ${FILE} root://cmseos.fnal.gov//store/user/vhegde/GMSB_skims_ST_RA2b_TreesV12/SignalRegion_v1/skimmed_SortedSignal_bTagEff/
    rm ${FILE}
done
#xrdcp -f $datasetName'_'$outputFileTag root://cmseos.fnal.gov//store/user/vhegde/GMSB_skims_ST_RA2b_TreesV12/SignalRegion_v1/skimmed_SortedSignal/
#xrdcp -f $datasetName'_'$outputFileTag root://cmseos.fnal.gov//store/user/vhegde/comp_Spring16vsSummer16/
#rm $datasetName'_'$outputFileTag
#/store/group/lpcsusyhad/SusyPhotonMET/Run2ProductionV17/signals/unskimmed_SortedSignalscans/tmp1/T5ttttZg_2016/