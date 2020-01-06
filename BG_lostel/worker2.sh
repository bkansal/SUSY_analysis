#!/bin/sh

executable=$1
inputFileTag=$2
outputFileTag=$3
#commitHash=$4
datasetName=$4
currDir=$(pwd)
######################################
# SETUP CMSSW STUFF...
######################################
source /cvmfs/cms.cern.ch/cmsset_default.sh
export SCRAM_ARCH=slc6_amd64_gcc530
scram p CMSSW CMSSW_10_1_7
cd CMSSW_10_1_7/src
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
./$executable $inputFileTag $outputFileTag $datasetName
echo "processed. ls"
ls
echo "COPYING OUTPUT"

#xrdcp -f $datasetName'_'$outputFileTag root://cmseos.fnal.gov//store/user/vhegde/myProduction_V12/
xrdcp -f $datasetName'_'$outputFileTag root://cmseos.fnal.gov//store/user/bkansal/GMSB_skims_TreesV17/for_bkg_estimation/lost_electron/
rm $datasetName'_'$outputFileTag
