#!/bin/sh

for i in MET nJets BestPhotonPt ST nBTags JetPt h_minDr_bestphoEle h_minDr_bestphoJets METvBin2 ElectronPt JetEta ElectronEta BestPhotonEta JetPhi ElectronPhi BestPhotonPhi leadElectronPt leadJetPt leadJetPhi leadElectronPhi leadJetEta leadElectronEta 

do
    root -l -q 'plotdatavsMC_overlay.C("'${i}'","2016")'
    root -l -q 'plotdatavsMC_overlay.C("'${i}'","2017")'
    root -l -q 'plotdatavsMC_overlay.C("'${i}'","2018")'
    root -l -q 'plotdatavsMC_overlay.C("'${i}'","full_Run2")'
done

for i in dPhi_METjet1 dPhi_METjet2
do
    root -l -q 'plotdatavsMC_overlay.C("'${i}'","2016")'
    root -l -q 'plotdatavsMC_overlay.C("'${i}'","2017")'
    root -l -q 'plotdatavsMC_overlay.C("'${i}'","2018")'
    root -l -q 'plotdatavsMC_overlay.C("'${i}'","full_Run2")'

done
