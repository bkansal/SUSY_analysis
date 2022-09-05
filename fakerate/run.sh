#!/bin/bash

### FR for e/gamma pT range 100 240
root -l -q 'codes/plot2dratio.C("PhoPtQMultJet_v2","full_Run2",false,true,false,false)' #for high dphi
root -l -q 'codes/plot2dratio.C("PhoPtQMultJet_v2","full_Run2",false,true,false,true)' #for low dphi
### FR for e/gamma pT range 240 600
root -l -q 'codes/plot2dratio.C("PhoPtQMultJet_v2","full_Run2",false,true,true,false)' #for high dphi
root -l -q 'codes/plot2dratio.C("PhoPtQMultJet_v2","full_Run2",false,true,true,true)' #for low dphi


### closure & Data vs MC plots in CR region ######
for i in AllSBins_v6_CD_EW_50bin nJets nBTags MET EMObj_Pt Qmulti BestPhotonPhi BestPhotonEta nvtx                                                                        
do
    for j in 2016 2017 2018 full_Run2
    do                                                                                                                                                                     
        root -l -q 'codes/plotclosure.C("'${i}'","'${j}'","v18",true,false)'
	root -l -q 'codes/plotdatavsMC.C("'${i}'","'${j}'","v18",false,true)'
    done
done                 


############ Overlay plot betwrrn tt jets & Wjets   
#root -l plotoverlay2.C

########### Systematics #########################
root -l -q 'codes/plot2dratio_scalepdf.C("_scale")'
root -l -q 'codes/plot2dratio_scalepdf.C("_pdf")'
root -l -q 'codes/plotsys_pred.C("JECup")'
root -l -q 'codes/plotsys_pred.C("JERup")'
root -l -q 'codes/plotsys_pred.C("btagSF")'
root -l -q 'codes/plotsys_pred.C("lepSF")'

hadd -f FR_sys.root FR_*_v2.root
mv *.root factors/.
########### Print predicted events with stat unc. #########
#root -l -q 'codes/printall.C(false)' ###### for SR high dphi 
root -l	-q 'codes/printall.C(true)' #for low dphi 

########### Print predicted events with stat + sys unc. for high dphi #########
root -l -q 'codes/printall.C(false,true)'

########### Print predicted events with stat unc. #########  
root -l -q 'codes/printall.C' ###### for SR high dphi 

rm *~
rm codes/*~
