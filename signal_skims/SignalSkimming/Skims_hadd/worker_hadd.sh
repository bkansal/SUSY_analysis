#!/bin/sh

mGl=$1
mNLSP=$2
# mGl=$1
# mNLSP=$2
#inputFileTag=$1
#outputFileTag=$2
#1;95;0ccommitHash=$4
#datasetName=$4
currDir=$(pwd)
######################################
# SETUP CMSSW STUFF...
######################################
source /cvmfs/cms.cern.ch/cmsset_default.sh
export SCRAM_ARCH=slc6_amd64_gcc630
scram p CMSSW CMSSW_10_1_7
cd CMSSW_10_1_7/src
eval `scramv1 runtime -sh`
cmsenv
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



#hadd -f Autumn18_T5bbbbZg_$mGl\_$mNLSP\_unSkimmed.root `xrdfs root://cmseos.fnal.gov ls -u /store/group/lpcsusyhad/SusyPhotonMET/Run2ProductionV17/signals/unskimmed_SortedSignalscans/scan_2018/ | grep 'T5bbbbZg_'$mGl'_'$mNLSP'_Autumn18Fast.SMS-T5bbbbZg_TuneCP2_13TeV-madgraphMLM-pythia8_job'`
#
#echo "----------------hadd done--------------"
#ls
#xrdcp -f Autumn18_T5bbbbZg_$mGl\_$mNLSP\_unSkimmed.root root://cmseos.fnal.gov//store/group/lpcsusyhad/SusyPhotonMET/Run2ProductionV17/signals/unskimmed_SortedSignalscans/scan/
#echo "-------------xrdcp done------------"
#ls
#rm Autumn18_T5bbbbZg_$mGl\_$mNLSP\_unSkimmed.root

#hadd -f Summer16v3_TChiNG_$mGl\_$mNLSP\_unSkimmed.root `xrdfs root://cmseos.fnal.gov ls -u /store/group/lpcsusyhad/SusyPhotonMET/Run2ProductionV17/signals/unskimmed_SortedSignalscans/tmp1/TChiNG_N2N1_2016/ | grep 'TChiNG_'$mGl'_'$mNLSP'_Summer16v3Fast.SMS-TChiNG_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_job'`

# hadd -f Summer16v3_T5ttttZg_$mGl\_$mNLSP\_unSkimmed.root `xrdfs root://cmseos.fnal.gov ls -u /store/group/lpcsusyhad/SusyPhotonMET/Run2ProductionV17/signals/unskimmed_SortedSignalscans/tmp1/T5ttttZg_2016/ | grep 'T5ttttZg_'$mGl'_'$mNLSP'_Summer16v3Fast.SMS-T5ttttZg_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_job'`

hadd -f Summer16v3_T6ttZg_$mGl\_$mNLSP\_unSkimmed.root `xrdfs root://cmseos.fnal.gov ls -u /store/group/lpcsusyhad/SusyPhotonMET/Run2ProductionV17/signals/unskimmed_SortedSignalscans/tmp1/T6ttZg_2016/ | grep 'T6ttZg_'$mGl'_'$mNLSP'_Summer16v3Fast.SMS-T6ttZg_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_job'`



# xrdcp -f TChiNG_$mGl\_$mNLSP\_unSkimmed.root root://cmseos.fnal.gov//store/group/lpcsusyhad/SusyPhotonMET/Run2ProductionV17/signals/unskimmed_SortedSignalscans/scan_2017/

# root -l -b -q 'numEventsComp.C("root://cmseos.fnal.gov//store/group/lpcsusyhad/SusyPhotonMET/Run2ProductionV17/signals/unskimmed_SortedSignalscans/scan_2017/TChiNG_'$mGl'_'$mNLSP'_unSkimmed.root",'$mGl','$mNLSP')'

# echo "processed. ls"
# ls


#hadd -f Summer16v3_T5qqqqHg_$mGl\_$mNLSP\_unSkimmed.root `xrdfs root://cmseos.fnal.gov ls -u /store/group/lpcsusyhad/SusyPhotonMET/Run2ProductionV17/signals/unskimmed_SortedSignalscans/tmp1/scan_2016/ | grep 'T5qqqqHg_'$mGl'_'$mNLSP'_Summer16v3Fast.SMS-T5qqqqHg_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_job'`

# hadd -f Summer16v3_T5qqqqHg_$mGl\_$mNLSP\_unSkimmed.root `xrdfsls -u /store/group/lpcsusyhad/SusyPhotonMET/Run2ProductionV17/signals/unskimmed_SortedSignalscans/tmp1/scan_2016/ | grep 'T5qqqHg_'$mGl'_'$mNLSP'_'`



#-=====================
# hadd -f Summer16v3_T5qqqqHg_$mGl\_$mNLSP\_unSkimmed.root `xrdfsls -u /store/group/lpcsusyhad/SusyPhotonMET/Run2ProductionV17/signals/unskimmed_SortedSignalscans/tmp1/scan_2016/ | grep 'T5qqqqHg_'$mGl'_'$mNLSP'_'`

# xrdcp -f Summer16v3_T5qqqqHg_$mGl\_$mNLSP\_unSkimmed.root root://cmseos.fnal.gov//store/group/lpcsusyhad/SusyPhotonMET/Run2ProductionV17/signals/unskimmed_SortedSignalscans/scan/T5qqqqHg/
#xrdcp -f Summer16v3_T5qqqqHg_$mGl\_$mNLSP\_unSkimmed.root root://cmseos.fnal.gov//store/user/bkansal/myProduction/scans/T5qqqqHg/
# xrdcp -f Summer16v3_TChiNG_$mGl\_$mNLSP\_unSkimmed.root root://cmseos.fnal.gov//store/group/lpcsusyhad/SusyPhotonMET/Run2ProductionV17/signals/unskimmed_SortedSignalscans/scan/TChiNG_N2N1/
xrdcp -f Summer16v3_T6ttZg_$mGl\_$mNLSP\_unSkimmed.root root://cmseos.fnal.gov//store/group/lpcsusyhad/SusyPhotonMET/Run2ProductionV17/signals/unskimmed_SortedSignalscans/scan/T6ttZg/


rm Summer16v3_T6ttZg_$mGl\_$mNLSP\_unSkimmed.root
# xrdcp -f Summer16v3_T5ttttZg_$mGl\_$mNLSP\_unSkimmed.root root://cmseos.fnal.gov//store/group/lpcsusyhad/SusyPhotonMET/Run2ProductionV17/signals/unskimmed_SortedSignalscans/scan/T5ttttZg/


# rm Summer16v3_T5ttttZg_$mGl\_$mNLSP\_unSkimmed.root
# root -l -b -q 'numEventsComp.C("root://cmseos.fnal.gov//store/group/lpcsusyhad/SusyPhotonMET/Run2ProductionV17/signals/unskimmed_SortedSignalscans/scan/T5qqqqHg/Summer16v3_T5qqqqHg_'$mGl'_'$mNLSP'_unSkimmed.root",'$mGl','$mNLSP')'

# echo "processed. ls"
# ls

