#!/bin/bash

##### TF plots ##########
root -l -q codes/plotratio_LE_newselec_v2.C
root -l -q 'codes/plotratio_LE_newselec_v2.C("full_Run2","v18",true)'
###### closure tests & Data vs MC plots in CR region ######
root -l -q codes/plotclosure_LL.C
root -l -q codes/plotdatavsMC_LL.C
for i in nJets MET hadAk8Mass BestPhotonPt
do
    root -l -q 'codes/plotclosure_LL.C("'$i'")'
    root -l -q 'codes/plotdatavsMC_LL.C("'$i'")'
done

root -l -q codes/plotstack_SR.C
root -l -q codes/plotstack_LM.C
root -l -q 'codes/plotstack_accid.C("rootoutput/closure/LL/TTWGJ_CR_v18.root")'

##### for systematics ##########
root -l -q 'codes/plotoverlay.C("scale")'
root -l -q 'codes/plotoverlay.C("scale","avgTF")'
root -l -q 'codes/plotoverlay.C("pdf")'
root -l -q 'codes/plotoverlay.C("pdf","avgTF")'

root -l -q 'codes/plotsys_pred.C("lepSF")'
root -l -q 'codes/plotsys_pred.C("btagSF")'
root -l -q 'codes/plotsys_pred.C("JECup")'
root -l -q 'codes/plotsys_pred.C("JERup")'

######## Adding all systematics quadratically ########
hadd -f LL_sys_v1.root LL*_v2.root 
mv LL_sys_v1.root LL*_v2.root factors/.
mv *.pdf pdf/.
mv *.png png/.

########### Print predicted events with stat unc. #########  
root -l -q 'codes/printall.C(true,false)'
root -l	-q 'codes/printall.C(false,false)'

########### Print predicted events with stat + sys unc. for high dphi #########                                                                                            
root -l -q 'codes/printall.C(false,true)'

root -l -q 'codes/printall.C'
