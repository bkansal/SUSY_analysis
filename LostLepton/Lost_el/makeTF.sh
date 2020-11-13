#!/bin/sh                                                                                                                                                     
# root -l -q 'plotratio_LE_newselec.C("2016")'
# root -l -q 'plotratio_LE_newselec.C("2017")'
# root -l -q 'plotratio_LE_newselec.C("2018")'
# root -l -q 'plotratio_LE_newselec.C("full_Run2")'

# area=rootoutput/newselec_LM_noISRjet_METfilters_EW_hadjetID/TF_v3_usingfullRun2
# root -l -q 'plotratio_LE_newselec_v2.C("2016","v17")'
# root -l -q 'plotratio_LE_newselec_v2.C("2017","v17")'
# root -l -q 'plotratio_LE_newselec_v2.C("2018","v17")'
# root -l -q 'plotratio_LE_newselec_v2.C("full_Run2","v17")'
# cp Run*_TF_LE_v6_CD.root ${area}/.

#area=rootoutput/newselec_LL_noISRjet_METfilters_EW_hadjetID_v18/TF_v3_usingfullRun2
area=rootoutput/newselec_LM_noISRjet_METfilters_EW_hadjetID_v18/TF_v3
# area=rootoutput/newselec_LE_noISRjet_METfilters_EW_hadjetID_v18/TF_v3_usingfullRun2
rm Run*_TF_LM_v6_CD.root
#area=rootoutput/newselec_LE_noISRjet_METfilters_EW_hadjetID_v18/TF_v3/WGJets_TF
root -l -q 'plotratio_LE_newselec_v2.C("2016","v18")'
root -l -q 'plotratio_LE_newselec_v2.C("2017","v18")'
root -l -q 'plotratio_LE_newselec_v2.C("2018","v18")'
root -l -q 'plotratio_LE_newselec_v2.C("full_Run2","v18")'

cp Run*_TF_LM_v6_CD.root ${area}/.
scp -r ${area}/Run*_TF_LM_v6_CD.root bkansal@cmslpc-sl7.fnal.gov:/uscms_data/d3/bkansal/SUSY_Photon_using_v17/Analysis/bkg_estimation/lostlepton/.
# cp Run*_TF_LM_v6_CD.root ${area}/.
# scp -r ${area}/Run*_TF_LM_v6_CD.root bkansal@cmslpc-sl7.fnal.gov:/uscms_data/d3/bkansal/SUSY_Photon_using_v17/Analysis/bkg_estimation/lostlepton/.
# cp Run*_TF_LL_v6_CD.root ${area}/.
# scp -r ${area}/Run*_TF_LL_v6_CD.root bkansal@cmslpc-sl7.fnal.gov:/uscms_data/d3/bkansal/SUSY_Photon_using_v17/Analysis/bkg_estimation/lostlepton/.


#scp -r Run*_TF_LE_v6_CD.root bkansal@cmslpc-sl7.fnal.gov:/uscms_data/d3/bkansal/SUSY_Photon_using_v17/Analysis/bkg_estimation/lostlepton/.
