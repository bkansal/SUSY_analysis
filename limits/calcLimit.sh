#!/bin/sh
input_Scan=$1
anaExe="analyzeLightBSM_old"
anaExe2="analyzeLightBSM_old_lowdphi"
anaArg="FastSim"
#exeAtWorker="worker_SP.sh"
exeAtWorker="worker_pred_tmp.sh"
#dataSetType="T6ttZg"
#dataSetType="T5ttttZg"
#dataSetType="T5qqqqHg"
#dataSetType="TChiNG"
#dataSetType="TChiWG"
dataSetType="T5bbbbZg"
ext="Summer16v3"
#cp rootoutput_newbin/*.root . 
#cp rootfiles_MCcutflow_MET200/*.root .

cp rootfiles_MCcutflow_oldselec/*.root .
hist1=MC_32bin_oldselec
mkdir /eos/uscms/store/user/bkansal/myProduction/limits_rootout/${dataSetType}/Final/
mkdir /eos/uscms/store/user/bkansal/myProduction/limits_rootout/${dataSetType}/Final//${hist1}


filesToTransfer="makeDatacard_SBins.C,higgsAnalysis.tar,GJetsQCD_new_v18.root,TTGJets_v18.root,TTJetsHT_v18.root,WGJetsToLNuG_v18.root,WJetsToLNu_v18.root,ZGZJ_NuNuG_v18.root,${anaExe},PileupHistograms_2018_69mb_pm5.root,PileupHistograms_2016_69mb_pm5.root,PileupHistograms_2017_69mb_pm5.root,T5bbbbZg_MassScan.root,T5qqqqHg_Summer16v3_MassScan.root,TChiWG_MassScan.root,TChiNG_MassScan.root,T5ttttZG_Summer16v3Fast_MassScan.root,T6ttZG_Summer16v3_MassScan.root"
#,TChiWG_MassScan.root,T5qqqqHg_Summer16v3_MassScan.root,TChiNG_MassScan.root,T5ttttZG_Summer16v3Fast_MassScan.root,T6ttZG_Summer16v3_MassScan.root"

#filesToTransfer="makeDatacard_SBins.C,higgsCombine.tar,GJets_v12.root,QCD_v12.root,TTGJets_v12.root,TTJetsHT_v12.root,WGJetsToLNuG_v12.root,WJetsToLNu_v12.root,ZJetsToNuNu_v12.root,ZGJetsToNuNuG_v12.root,ZGZJ_NuNuG_v12.root,${anaExe},PileupHistograms_0121_69p2mb_pm4p6.root,T5bbbbZg_MassScan.root"

#filesToTransfer="makeDatacard_SBins_predall.C,higgsAnalysis.tar,EWK_LL.root,EWK_FR.root,EWK_Zin.root,QCD.root,LL.root,FR.root,Zin.root,Data.root,Data_lowdphi.root,Data_lowMET.root,${anaExe},${anaExe2},PileupHistograms_2018_69mb_pm5.root,PileupHistograms_2016_69mb_pm5.root,PileupHistograms_2017_69mb_pm5.root,T5bbbbZg_MassScan.root"

#filesToTransfer="makeDatacard_SBins_pred.C,higgsAnalysis.tar,Lostlepton_highdphi.root,Fakerate_highdphi.root,Zinvi_highdphi.root,QCD_Multi.root,${anaExe},PileupHistograms_2018_69mb_pm5.root,PileupHistograms_2016_69mb_pm5.root,PileupHistograms_2017_69mb_pm5.root,T5bbbbZg_MassScan.root"

while read -a massP
do 
    echo ${massP[0]} ${massP[1]}
    jdl_file="condor_${dataSetType}_${anaArg}_${massP[0]}_${massP[1]}_job.jdl"
    log_prefix="condor_${dataSetType}_${anaArg}_${massP[0]}_${massP[1]}_job"
    echo "universe = vanilla">$jdl_file
    echo "Executable = $exeAtWorker">>$jdl_file
    echo "Should_Transfer_Files = YES">>$jdl_file
    echo "WhenToTransferOutput = ON_EXIT_OR_EVICT">>$jdl_file
    echo "Transfer_Input_Files = ${filesToTransfer}">>$jdl_file
    echo "Output = ${log_prefix}.stdout">>$jdl_file
    echo "Error = ${log_prefix}.stderr">>$jdl_file
    echo "Log = ${log_prefix}.condor">>$jdl_file
    echo "notification = never">>$jdl_file
    echo "Arguments = ${anaExe} ${massP[0]} ${massP[1]} ${anaArg} ${dataSetType} ${ext} ${hist1}">>$jdl_file
    echo "Queue">>$jdl_file
    condor_submit $jdl_file
done < $input_Scan

