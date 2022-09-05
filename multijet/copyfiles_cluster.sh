#!/bin/sh                                                                                                                                                                   

scp -r ../lostlepton/Lostlepton_highdphi.root bkansal@cmslpc-sl7.fnal.gov:/uscms_data/d3/bkansal/SUSY_Photon_using_v17/SignalRegion_GetLimits_new/CD/LL.root
scp -r ../lostlepton/Lostlepton_lowdphi.root bkansal@cmslpc-sl7.fnal.gov:/uscms_data/d3/bkansal/SUSY_Photon_using_v17/SignalRegion_GetLimits_new/CD/EWK_LL.root

scp -r ../fakerate/Fakerate_highdphi.root bkansal@cmslpc-sl7.fnal.gov:/uscms_data/d3/bkansal/SUSY_Photon_using_v17/SignalRegion_GetLimits_new/CD/FR.root
scp -r ../fakerate/Fakerate_lowdphi.root bkansal@cmslpc-sl7.fnal.gov:/uscms_data/d3/bkansal/SUSY_Photon_using_v17/SignalRegion_GetLimits_new/CD/EWK_FR.root

scp -r ../Z_invisible/Zinvi_highdphi.root bkansal@cmslpc-sl7.fnal.gov:/uscms_data/d3/bkansal/SUSY_Photon_using_v17/SignalRegion_GetLimits_new/CD/Zin.root
scp -r ../Z_invisible/Zinvi_lowdphi.root bkansal@cmslpc-sl7.fnal.gov:/uscms_data/d3/bkansal/SUSY_Photon_using_v17/SignalRegion_GetLimits_new/CD/EWK_Zin.root

scp -r RK_lowMET_data.root bkansal@cmslpc-sl7.fnal.gov:/uscms_data/d3/bkansal/SUSY_Photon_using_v17/SignalRegion_GetLimits_new/CD/QCD.root

hadd -f Data.root ../lostlepton/Lostlepton_highdphi.root ../fakerate/Fakerate_highdphi.root  ../Z_invisible/Zinvi_highdphi.root RK_lowMET_data.root

scp -r Data.root bkansal@cmslpc-sl7.fnal.gov:/uscms_data/d3/bkansal/SUSY_Photon_using_v17/SignalRegion_GetLimits_new/CD/.

scp -r rootoutput/v2_btagSF/ST300_Rfactor_applied_noRK/Run2_METdata_CR_v18.root bkansal@cmslpc-sl7.fnal.gov:/uscms_data/d3/bkansal/SUSY_Photon_using_v17/SignalRegion_GetLimits_new/CD/Data_lowdphi.root
