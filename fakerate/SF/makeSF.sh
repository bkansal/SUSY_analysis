#!/bin/sh                                                                                                                                                     

a=$1
b=$2
c=$3
root -l 'plotFR.C("'${a}'","'${b}'","v17",true,'${c}')'
root -l 'plotFR.C("'${a}'","'${b}'","v17",false,'${c}')'
root -l 'plotFR.C("'${a}'","'${b}'","v18",false,1)'

# for b in 2016
# do
#     for a in Qmulti nJets nvtx nBTags MET EMObj_Pt ST invMass BestPhotonEta
#     do
# 	root -l -q 'plotratio_LE_newselec.C("'${a}'","'${b}'",false,true,true)'
# 	root -l -q 'plotratio_LE_newselec.C("'${a}'","'${b}'",false,true,false)'
# 	root -l -q 'plotclosure.C("'${a}'","'${b}'","v18",false,true)'
#     done
# done