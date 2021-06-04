#!/bin/sh                                                                                                                                                     


rm Run*_TF_LE_v6_CD.root

root -l -q 'plotratio_LE_newselec_v2.C("2016","v18")'
root -l -q 'plotratio_LE_newselec_v2.C("2017","v18")'
root -l -q 'plotratio_LE_newselec_v2.C("2018","v18")'
root -l -q 'plotratio_LE_newselec_v2.C("full_Run2","v18")'


