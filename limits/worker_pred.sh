#!/bin/sh
#analyzeLightBSM 800 127 FastSim T5qqqqHg Summer16v3
# analyzeLightBSM 2200 200 FastSim T5bbbbZg Summer16v3 
executable=$1
gluinoMass=$2
nlspMass=$3
anaArg=$4
outName=$5
ext=$6
hist=AllSBins_v6_CD_EW_50bin_elec1_closure
hist1=$7
currDir=$(pwd)
#hist1=tmp
#echo "root://cmseos.fnal.gov//store/group/lpcsusyhad/SusyPhotonMET/Run2ProductionV18/signals/unskimmed_SortedSignalscans/scan/T5bbbbZg/${ext}_${outName}_${gluinoMass}_${nlspMass}_unSkimmed.root" 
echo "root://cmseos.fnal.gov//store/group/lpcsusyhad/SusyPhotonMET/Run2ProductionV18/signals/unskimmed_SortedSignalscans/scan/T5bbbbZg/${ext}_${outName}_${gluinoMass}_${nlspMass}_unSkimmed.root" > runFileList.txt
#echo "root://cmseos.fnal.gov//store/user/bkansal/myProduction/scans/T5qqqqHg/Summer16v3_${outName}_${gluinoMass}_${nlspMass}_unSkimmed.root" > runFileList.txt
#echo "root://cmseos.fnal.gov//store/group/lpcsusyhad/SusyPhotonMET/Run2ProductionV17/signals/unskimmed_SortedSignalscans/scan/T5ttttZg/Summer16v3_${outName}_${gluinoMass}_${nlspMass}_unSkimmed.root" > runFileList.txt                                                                                                                            
#echo "root://cmseos.fnal.gov//store/group/lpcsusyhad/SusyPhotonMET/Run2ProductionV17/signals/unskimmed_SortedSignalscans/scan/T6ttZg/Summer16v3_${outName}_${gluinoMass}_${nlspMass}_unSkimmed.root" > runFileList.txt                                                                                                                               

#echo "root://cmseos.fnal.gov//store/group/lpcsusyhad/SusyPhotonMET/Run2ProductionV17/signals/unskimmed_SortedSignalscans/scan/TChiWG/${outName}_${gluinoMass}_${nlspMass}_unSkimmed.root" > runFileList.txt
#echo "root://cmseos.fnal.gov///store/group/lpcsusyhad/SusyPhotonMET/Run2ProductionV17/signals/unskimmed_SortedSignalscans/scan/TChiNG/${ext}_${outName}_${gluinoMass}_${nlspMass}_unSkimmed.root" > runFileList.txt 
######################################
# SETUP CMSSW STUFF...
######################################


echo "======== ${PWD} ==============="

source /cvmfs/cms.cern.ch/cmsset_default.sh
export SCRAM_ARCH=slc7_amd64_gcc700
cmsrel CMSSW_10_2_13
cd CMSSW_10_2_13/src
#export SCRAM_ARCH=slc7_amd64_gcc900
#scram p CMSSW CMSSW_12_0_0
#cd CMSSW_12_0_0/src
eval `scramv1 runtime -sh`
echo $CMSSW_RELEASE_BASE
cd $currDir
echo $currDir


outRootFile="${anaArg}_${outName}_${gluinoMass}_${nlspMass}_v18"

echo "./$executable runFileList.txt ${outRootFile}.root ${anaArg}_${outName}_2016"

./$executable runFileList.txt ${outRootFile}.root ${anaArg}_${outName}_2016

executable2="${executable}_lowdphi"
outRootFile2="${anaArg}_${outName}_${gluinoMass}_${nlspMass}_v18_lowdphi"
./$executable2 runFileList.txt ${outRootFile2}.root ${anaArg}_${outName}_2016

rm runFileList.txt
# mv runFileList.txt tmp/runFileList.txt
#cp CD/* .
echo "========== HiggsAnalysis/CombinedLimit ==============="
echo "${PWD}"

export SCRAM_ARCH=slc7_amd64_gcc700
cmsrel CMSSW_10_2_13
cd CMSSW_10_2_13/src
eval `scramv1 runtime -sh`
cmsenv
echo "${PWD}"
<<EOF
tar -xvf ${currDir}/higgsAnalysis.tar
cd HiggsAnalysis/CombinedLimit
scram b clean
scram b -j4
EOF
				
cd ${currDir}

rm -rf dataCards

echo "making datacards"
mkdir dataCards
#hist1=SB
mkdir dataCards/${outRootFile}_${hist1}

echo "mkdir dataCards/${outRootFile}_${hist1}"
root -l -q -b 'makeDatacard_SBins_predSB_sys.C('${gluinoMass}','${nlspMass}',"'${outRootFile}'.root","'${hist1}'","'${hist}'")'
#root -l -q -b 'makeDatacard_SBins_predSB.C('${gluinoMass}','${nlspMass}',"'${outRootFile}'.root","'${hist1}'","'${hist}'")'
#root -l -q -b 'makeDatacard_SBins.C('${gluinoMass}','${nlspMass}',"'${outRootFile}'.root","'${hist1}'","'${hist}'")'
rm dataCards/${outRootFile}_${hist1}/${outRootFile}_${hist}_bin1.txt
#rm dataCards/${outRootFile}_${hist1}/${outRootFile}_${hist}_bin34.txt

<<EOF 
for i in {2..34}
do
    rm dataCards/${outRootFile}_${hist1}/${outRootFile}_${hist}_bin${i}.txt
done
EOF
for i in {47..52}
do
    rm dataCards/${outRootFile}_${hist1}/${outRootFile}_${hist}_bin${i}.txt
done

#rm ${outRootFile}.root                                                                                                          
ls dataCards/${outRootFile}_${hist1}/*
                                            
cd CMSSW_10_2_13/src/HiggsAnalysis/CombinedLimit
eval `scramv1 runtime -sh`
echo $CMSSW_RELEASE_BASE

echo "combineCards.py ${currDir}/dataCards/${outRootFile}_${hist1}/${outRootFile}_${hist}_bin2.txt"
echo "combineCards.py ${currDir}/dataCards/${outRootFile}_${hist1}/*.txt > dataCard_${outName}_${gluinoMass}_${nlspMass}_${hist}.txt"

combineCards.py -S ${currDir}/dataCards/${outRootFile}_${hist1}/*.txt  > dataCard_${outName}_${gluinoMass}_${nlspMass}_${hist}.txt
echo "calculating limit"
mH="$(echo "${gluinoMass}+${nlspMass}*0.0001" | bc)"
echo $mH

echo "combine -M AsymptoticLimits dataCard_${outName}_${gluinoMass}_${nlspMass}_${hist}.txt -t -1 -n ${outName}_${gluinoMass}_${nlspMass}_${hist} -m ${mH}"

#combine -M AsymptoticLimits dataCard_${outName}_${gluinoMass}_${nlspMass}_${hist}.txt -t -1 -n ${outName}_${gluinoMass}_${nlspMass}_${hist} -m ${mH}
combine -M AsymptoticLimits dataCard_${outName}_${gluinoMass}_${nlspMass}_${hist}.txt -n ${outName}_${gluinoMass}_${nlspMass}_${hist} -m ${mH}
#combine -M AsymptoticLimits dataCard_${outName}_${gluinoMass}_${nlspMass}_${hist}.txt --bypassFrequentistFit -n ${outName}_${gluinoMass}_${nlspMass}_${hist} -m ${mH}



#xrdcp -f higgsCombine${outName}_${gluinoMass}_${nlspMass}_${hist}*.root root://cmseos.fnal.gov//store/user/bkansal/myProduction/limits_rootout/T5qqqqHg/${hist1}/
#xrdcp -f higgsCombine${outName}_${gluinoMass}_${nlspMass}_${hist}*.root root://cmseos.fnal.gov//store/user/bkansal/myProduction/limits_rootout/T6ttZg/${hist1}/
xrdcp -f higgsCombine${outName}_${gluinoMass}_${nlspMass}_${hist}*.root root://cmseos.fnal.gov//store/user/bkansal/myProduction/limits_rootout/${outName}/Final/${hist1}/
#xrdcp -rf ${currDir}/dataCards/${outRootFile}_${hist1} root://cmseos.fnal.gov//store/user/bkansal/myProduction/limits_rootout/T5bbbbZg/njet6/${hist1}/dataCards/

rm higgsCombine${outName}_${gluinoMass}_${nlspMass}_${hist}*.root


rm *.txt
cd ${currDir}

#rm -rf dataCards
cd ${currDir}
rm FastSim_${outName}_*.root


