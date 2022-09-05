##########
#for K factors calc. using MC
#btag > 0                                                                                                                                                                  
root -l -q 'codes/plot2dratio_multi.C("nJetsMET","full_Run2",true,false,false)'
#btag = 0                                                                                                                                                                  
root -l -q 'codes/plot2dratio_multi.C("nJetsMET","full_Run2",false,true,false)'
#HTag                                                                                                                                                                      
root -l -q 'codes/plotclosure_multi.C("nJetsMET","full_Run2","v18",true,false)'
#Wtag
root -l -q 'codes/plotclosure_multi.C("nJetsMET","full_Run2","v18",false,true)'


#for R factors for low MET calc. using MC for closure
root -l -q 'codes/plotclosure_multi.C("AllSBins_v7_CD_SP","full_Run2","v18",false,true)'
#for closure
root -l -q 'codes/plotclosure_multi.C("AllSBins_v6_CD_EW_50bin","full_Run2","v18",true,false)'


## for K validation
root -l -q codes/printRK_0pho.C

mv *.root factors/.
########### Print predicted events with stat unc. ######### 
root -l -q 'codes/printRK.C(true,false,false)' #plot R factor in data
root -l -q 'codes/printRK.C(true,false,true)' #plot K factor in MC

########### Print predicted events with stat + sys unc. for high dphi #########
root -l -q 'codes/printRK.C(true,true,false)' 
