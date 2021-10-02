#!/bin/sh
#analyzeLightBSM 800 127 FastSim T5qqqqHg
executable=$1
gluinoMass=$2
nlspMass=$3
anaArg=$4
outName=$5
ext=$6
hist=AllSBins_v6_CD_EW_50bin
hist1=$7
currDir=$(pwd)

echo "root://cmseos.fnal.gov//store/group/lpcsusyhad/SusyPhotonMET/Run2ProductionV18/signals/unskimmed_SortedSignalscans/scan/T5bbbbZg/${ext}_${outName}_${gluinoMass}_${nlspMass}_unSkimmed.root" 

echo "root://cmseos.fnal.gov//store/group/lpcsusyhad/SusyPhotonMET/Run2ProductionV18/signals/unskimmed_SortedSignalscans/scan/T5bbbbZg/${ext}_${outName}_${gluinoMass}_${nlspMass}_unSkimmed.root" > runFileList.txt

######################################
# SETUP CMSSW STUFF...
######################################


echo "======== ${PWD} ==============="

source /cvmfs/cms.cern.ch/cmsset_default.sh
export SCRAM_ARCH=slc7_amd64_gcc700
scram p CMSSW CMSSW_10_2_21
cd CMSSW_10_2_21/src
eval `scramv1 runtime -sh`
echo $CMSSW_RELEASE_BASE
cd $currDir
echo $currDir

outRootFile="${anaArg}_${outName}_${gluinoMass}_${nlspMass}_v18"
./$executable runFileList.txt ${outRootFile}.root ${anaArg}_${outName}_2016

rm runFileList.txt
# mv runFileList.txt tmp/runFileList.txt

echo "========== HiggsAnalysis/CombinedLimit ==============="
echo "${PWD}"

export SCRAM_ARCH=slc7_amd64_gcc700
cmsrel CMSSW_10_2_13
cd CMSSW_10_2_13/src
eval `scramv1 runtime -sh`
cmsenv
echo "${PWD}"
tar -xvf ${currDir}/higgsAnalysis.tar
cd HiggsAnalysis/CombinedLimit
scram b clean
scram b -j4
				
cd ${currDir}

rm -rf dataCards

echo "making datacards"
mkdir dataCards
mkdir dataCards/${outRootFile}_${hist1}
echo "mkdir dataCards/${outRootFile}_${hist1}"
root -l -q -b 'makeDatacard_SBins.C('${gluinoMass}','${nlspMass}',"'${outRootFile}'.root","'${hist1}'","'${hist}'")'

rm dataCards/${outRootFile}_${hist1}/${outRootFile}_${hist}_bin1.txt
rm dataCards/${outRootFile}_${hist1}/${outRootFile}_${hist}_bin47.txt
rm dataCards/${outRootFile}_${hist1}/${outRootFile}_${hist}_bin48.txt
rm dataCards/${outRootFile}_${hist1}/${outRootFile}_${hist}_bin49.txt
rm dataCards/${outRootFile}_${hist1}/${outRootFile}_${hist}_bin50.txt
rm dataCards/${outRootFile}_${hist1}/${outRootFile}_${hist}_bin51.txt
rm dataCards/${outRootFile}_${hist1}/${outRootFile}_${hist}_bin52.txt
rm dataCards/${outRootFile}_${hist1}/${outRootFile}_${hist}_bin53.txt
#rm dataCards/${outRootFile}_${hist1}/${outRootFile}_${hist}_bin37.txt
# for i in {38..51}
# do
#     rm dataCards/${outRootFile}_${hist1}/${outRootFile}_${hist}_bin${i}.txt
# done
#rm dataCards/${outRootFile}_${hist1}/${outRootFile}_${hist}_bin38.txt
#rm dataCards/${outRootFile}_${hist1}/${outRootFile}_${hist}_bin45.txt

echo "ls dataCards/${outRootFile}_${hist1}/*"
ls dataCards/${outRootFile}_${hist1}/*


rm ${outRootFile}.root                                                                                                                                      
                                            
 

cd CMSSW_10_2_13/src/HiggsAnalysis/CombinedLimit
eval `scramv1 runtime -sh`
echo $CMSSW_RELEASE_BASE


echo "combineCards.py ${currDir}/dataCards/${outRootFile}_${hist1}/*.txt > dataCard_${outName}_${gluinoMass}_${nlspMass}_${hist}.txt"
combineCards.py ${currDir}/dataCards/${outRootFile}_${hist1}/*.txt > dataCard_${outName}_${gluinoMass}_${nlspMass}_${hist}.txt

echo "calculating limit"
mH="$(echo "${gluinoMass}+${nlspMass}*0.0001" | bc)"
echo $mH

echo "combine -M AsymptoticLimits dataCard_${outName}_${gluinoMass}_${nlspMass}_${hist}.txt -t -1 -n ${outName}_${gluinoMass}_${nlspMass}_${hist} -m ${mH}"
combine -M AsymptoticLimits dataCard_${outName}_${gluinoMass}_${nlspMass}_${hist}.txt -t -1 -n ${outName}_${gluinoMass}_${nlspMass}_${hist} -m ${mH}



#xrdcp -f higgsCombine${outName}_${gluinoMass}_${nlspMass}_${hist}*.root root://cmseos.fnal.gov//store/user/bkansal/myProduction/limits_rootout/T5qqqqHg/${hist1}/
#xrdcp -f higgsCombine${outName}_${gluinoMass}_${nlspMass}_${hist}*.root root://cmseos.fnal.gov//store/user/bkansal/myProduction/limits_rootout/T6ttZg/${hist1}/
xrdcp -f higgsCombine${outName}_${gluinoMass}_${nlspMass}_${hist}*.root root://cmseos.fnal.gov//store/user/bkansal/myProduction/limits_rootout/T5bbbbZg/njet6/${hist1}/

rm higgsCombine${outName}_${gluinoMass}_${nlspMass}_${hist}*.root


rm *.txt
cd ${currDir}
rm -rf dataCards
cd ${currDir}
rm FastSim_T5bbbbZg_*.root


