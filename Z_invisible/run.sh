dir2=v6

root -l -q 'codes/getpurity.C("'${dir2}'")'
root -l -q 'codes/plotclosure.C("AllSBins_v6_CD","full_Run2","v17","'${dir2}'",false,true)'


for i in AllSBins_v6_CD nJets nBTags MET BestPhotonPt invMass METvBin2
do
    root -l -q 'codes/plotdatavsMC_Zin.C("'${i}'","full_Run2","v18",false,true)'
done

##########systematics ############3
root -l -q 'codes/plotsys_pred.C("EWKcorr")'
root -l	-q 'codes/plotsys_pred.C("lepSF")'
root -l -q 'codes/plotsys_pred.C("JECup")'
root -l -q 'codes/plotsys_pred.C("JERup")'

hadd -f Zinvi_sys.root Zinvi_*_v2.root
mv *.root factors/.
mv *.pdf pdf/.
mv *.png png/.

########### Print predicted events with stat unc. #########
#root -l -q 'codes/printall.C(false)'
root -l	-q 'codes/printall.C(true)'

########### Print predicted events with stat + sys unc. for high dphi #########
root -l -q 'codes/printall.C(false,true)'
root -l -q 'codes/printall.C(false)'
