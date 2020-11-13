#!/bin/sh

#for i in MET nJets AllSBins_v7_CD_SP AllSBins_v6_CD_EW_50bin BestPhotonPt_vBin nBTags 
for i in MET
do
    for j in full_Run2 2016 2017 2018
    do 
	root -l -q 'plotratio_LE_newselec.C("'${i}'","'${j}'",false,true)'
	root -l -q 'plotratio_LE_newselec.C("'${i}'","'${j}'",true,false)'
    done
done
