#!/bin/sh                                                                                                                                                     
#for i in MET nJets AllSBins_v7_CD_SP AllSBins_v6_CD AllSBins_v6_CD_SP AllSBins_v6_CD_EW_50bin BestPhotonPt_vBin ST nBTags JetPt h_minDr_bestphoEle h_minDr_bestphoJets leadJetPt hadAk8Mass hadAk8jetPt
# for i in MET
# do	 
#     root -l -q 'plotclosure.C("'${i}'","2016","v18",true,false)'
#     root -l -q 'plotclosure.C("'${i}'","2017","v18",true,false)'
#     root -l -q 'plotclosure.C("'${i}'","2018","v18",true,false)'
#     root -l -q 'plotclosure.C("'${i}'","full_Run2","v18",true,false)'
#     root -l -q 'plotclosure.C("'${i}'","2016","v18",false,true)'
#     root -l -q 'plotclosure.C("'${i}'","2017","v18",false,true)'
#     root -l -q 'plotclosure.C("'${i}'","2018","v18",false,true)'
#     root -l -q 'plotclosure.C("'${i}'","full_Run2","v18",false,true)'

# done
for i in MET
do	 
    root -l -q 'plotclosure.C("'${i}'","2016","v17",true,false)'
    root -l -q 'plotclosure.C("'${i}'","2017","v17",true,false)'
    root -l -q 'plotclosure.C("'${i}'","2018","v17",true,false)'
    root -l -q 'plotclosure.C("'${i}'","full_Run2","v17",true,false)'
    root -l -q 'plotclosure.C("'${i}'","2016","v17",false,true)'
    root -l -q 'plotclosure.C("'${i}'","2017","v17",false,true)'
    root -l -q 'plotclosure.C("'${i}'","2018","v17",false,true)'
    root -l -q 'plotclosure.C("'${i}'","full_Run2","v17",false,true)'

done

# for i in hadAk8Mass hadAk8jetPt
# do	 
#     root -l -q 'plotclosure.C("'${i}'","2016","v18")'
#     root -l -q 'plotclosure.C("'${i}'","2017","v18")'
#     root -l -q 'plotclosure.C("'${i}'","2018","v18")'
#     root -l -q 'plotclosure.C("'${i}'","full_Run2","v18")'

# done

# for i in AllSBins_v6_CD_EW_50bin
# do	 
#     root -l -q 'plotclosure.C("'${i}'","2016")'
#     root -l -q 'plotclosure.C("'${i}'","2017")'
#     root -l -q 'plotclosure.C("'${i}'","2018")'
#     root -l -q 'plotclosure.C("'${i}'","full_Run2")'

# done

