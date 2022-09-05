#!/bin/sh


currdir=/Users/bkansal/work/MET_Analysis/Analysis/Z_invisible
dir=v8_btagSF_noJERC
dir2=v8_btagSF_noJERC
dir2=v6
<<EOF

mkdir rootoutput/${dir2}/
mkdir rootoutput/${dir2}/withphicut_zmass60to120_muon
mkdir rootoutput/${dir2}/withphicut_zmass60to120_elec
mkdir rootoutput/${dir2}/withphicut_zmass60to120_data
mkdir rootoutput/${dir2}/withphicut_zmass60to120_muon_PF
mkdir rootoutput/${dir2}/withphicut_zmass60to120_elec_PF
mkdir rootoutput/${dir2}/withphicut_zmass60to120_data_PF

cp rootoutput/v7_btagSF/withphicut_zmass60to120_data/hadd.sh rootoutput/${dir2}/withphicut_zmass60to120_data/.
cp rootoutput/v7_btagSF/withphicut_zmass60to120_data_PF/hadd.sh rootoutput/${dir2}/withphicut_zmass60to120_data_PF/.

scp -r bkansal@cmslpc-sl7.fnal.gov:/eos/uscms/store/user/bkansal/GMSB_skims_TreesV18/for_bkg_estimation/JEC_JER_sys/Zinvisible/${dir}_muon/* rootoutput/${dir2}/withphicut_zmass60to120_muon/.
scp -r bkansal@cmslpc-sl7.fnal.gov:/eos/uscms/store/user/bkansal/GMSB_skims_TreesV18/for_bkg_estimation/JEC_JER_sys/Zinvisible/${dir}_elec/* rootoutput/${dir2}/withphicut_zmass60to120_elec/.


cd rootoutput/${dir2}/withphicut_zmass60to120_data
./hadd.sh

cd ${currdir}
echo "currdir"
echo "'${currdir}'"


#### PF calc ##############
root -l -q 'codes/getpurity.C("'${dir2}'")'
scp -r purityfactor.root bkansal@cmslpc-sl7.fnal.gov:/uscms_data/d3/bkansal/SUSY_Photon_using_v17/Analysis/bkg_estimation/Z_invisible/jec_sys/.

cp purityfactor.root factors/purityfactor_${dir2}.root


#### SF calc ##############
scp -r bkansal@cmslpc-sl7.fnal.gov:/eos/uscms/store/user/bkansal/GMSB_skims_TreesV18/for_bkg_estimation/JEC_JER_sys/Zinvisible/${dir}_muon/* rootoutput/${dir2}/withphicut_zmass60to120_muon_PF/.
scp -r bkansal@cmslpc-sl7.fnal.gov:/eos/uscms/store/user/bkansal/GMSB_skims_TreesV18/for_bkg_estimation/JEC_JER_sys/Zinvisible/${dir}_elec/* rootoutput/${dir2}/withphicut_zmass60to120_elec_PF/.


cd rootoutput/${dir2}/withphicut_zmass60to120_data_PF
rm *
cp ${currdir}/rootoutput/v7_btagSF/withphicut_zmass60to120_data_PF/hadd.sh .
./hadd.sh

cd ${currdir}

EOF

root -l 'plotclosure.C("AllSBins_v6_CD","full_Run2","v17","'${dir2}'",false,true)'
cp Zinvisible_SF.root factors/Zinvisible_SF_${dir2}.root


scp -r Zinvisible_SF.root bkansal@cmslpc-sl7.fnal.gov:/uscms_data/d3/bkansal/SUSY_Photon_using_v17/Analysis/bkg_estimation/Z_invisible/.

