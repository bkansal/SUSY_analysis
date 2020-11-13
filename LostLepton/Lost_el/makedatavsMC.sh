#!/bin/sh

 for i in AllSBins_v6_CD_EW_50bin_elec1 MET nJets BestPhotonPt ST nBTags h_minDr_bestphoEle h_minDr_bestphoJets BestPhotonEta BestPhotonPhi leadJetPt leadJetPhi leadJetEta dPhi_METjet1 dPhi_METjet2 leadElectronPt leadElectronEta leadElectronPhi

do
    root -l -q 'plotdatavsMC.C("'${i}'","2016","v18")'
    root -l -q 'plotdatavsMC.C("'${i}'","2017","v18")'
    root -l -q 'plotdatavsMC.C("'${i}'","2018","v18")'
    root -l -q 'plotdatavsMC.C("'${i}'","full_Run2","v18")'
done

# for i in leadElectronEta_Phi h2_dPhivseta_jet1 h2_dPhivseta_jet2 h2_dPhivseta_jet3 h2_dPhivseta_jet4 h2_Phivseta_jet1 h2_Phivseta_jet2 h2_Phivseta_jet3 h2_Phivseta_jet4 BestPhotonPt_jetmatchphoratio BestPhotonPt_jetphoratio
# do
#     root -l -q 'plot2d.C("'${i}'","2016",false)'
#     root -l -q 'plot2d.C("'${i}'","2016",true)'
#     root -l -q 'plot2d.C("'${i}'","2017",false)'
#     root -l -q 'plot2d.C("'${i}'","2017",true)'
#     root -l -q 'plot2d.C("'${i}'","2018",false)'
#     root -l -q 'plot2d.C("'${i}'","2018",true)'
#     root -l -q 'plot2d.C("'${i}'","full_Run2",false)'
#     root -l -q 'plot2d.C("'${i}'","full_Run2",true)'
# done	 

# for i in h2_dPhivseta_jet1 h2_dPhivseta_jet2 h2_dPhivseta_jet3 h2_dPhivseta_jet4 h2_Phivseta_jet1 h2_Phivseta_jet2 h2_Phivseta_jet3 h2_Phivseta_jet4 leadElectronEta_Phi BestPhotonPt_jetmatchphoratio BestPhotonPt_jetphoratio
# do
#     root -l -q 'plot2ddatavsMC.C("'${i}'","2016","v18")'
#     root -l -q 'plot2ddatavsMC.C("'${i}'","2017","v18")'
#     root -l -q 'plot2ddatavsMC.C("'${i}'","2018","v18")'
#     root -l -q 'plot2ddatavsMC.C("'${i}'","full_Run2","v18")'
# done	 

for i in dPhi_METlep1 METPhi h_minDr_EleJets h_minDr_Elejet1 h_minDr_Elejet2 h_minDr_Elejet3 h_minDr_Elejet4 dPhi_phojet4 dPhi_phojet3 dPhi_phojet2 dPhi_phojet1 dPhi_METjet1 dPhi_METjet2 dPhi_METjet3 dPhi_METjet4
do
    root -l -q 'plotdatavsMC.C("'${i}'","2016","v18")'
    root -l -q 'plotdatavsMC.C("'${i}'","2017","v18")'
    root -l -q 'plotdatavsMC.C("'${i}'","2018","v18")'
    root -l -q 'plotdatavsMC.C("'${i}'","full_Run2","v18")'
done

	 
