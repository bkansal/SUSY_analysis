mGl = $1
for mNLSP in 150 800 1750
do
    hadd -f T5bbbbZg_$mGl\_$mNLSP\_unSkimmed.root `xrdfs root://cmseos.fnal.gov ls -u /store/user/bkansal/myProduction/T5bbbbZg_/ | grep 'T5bbbbZg_'$mGl'_'$mNLSP'_Summer16v3Fast.SMS-T5bbbbZg_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_job'`

    echo "----------------hadd done--------------"
    ls
    xrdcp -f T5bbbbZg_$mGl\_$mNLSP\_unSkimmed.root root://cmseos.fnal.gov//store/group/lpcsusyhad/SusyPhotonMET/Run2ProductionV17/signals/unskimmed_SortedSignalscans/
    echo "-------------xrdcp done------------"
    ls
    rm T5bbbbZg_$mGl\_$mNLSP\_unSkimmed.root
done