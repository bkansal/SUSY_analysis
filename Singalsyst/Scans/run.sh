#root -l 'plotsys.C("ISRsys","T5ttttZg")'
rm plots/*

for i in T5bbbbZg TChiWG T5qqqqHg T5ttttZg TChiNG T6ttZg
do
    mkdir plots/${i}
    cp -r ../res plots/${i}/.
    cp ../index.php plots/${i}/.
    cp /Users/bkansal/work/MET_Analysis/Analysis_14Mar2020/plotLimits/${i}_exclusion.pdf plots/${i}/.
    cp /Users/bkansal/work/MET_Analysis/Analysis_14Mar2020/plotLimits/${i}_exclusion.png plots/${i}/.
    for j in Efficiency yield Crosssection
    do
	root -l -q 'plotSMS.C("'$i'","'$j'")'
    done
done

scp -r plots/* bkansal@lxplus7.cern.ch:/eos/user/b/bkansal/www/SUSYGMSB-analysis/SigScan/.


    
	 