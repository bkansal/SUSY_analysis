#!/bin/sh

for sample in A B C 
do
#    echo "grep $sample inputFiles.txt_main > $sample.txt"
#    grep $sample inputFiles.txt_main > $sample.txt
    echo "$sample"
#    grep 'Run2016'$sample'-17Jul2018.*JetHT*' inputfiles_v18.txt > inputlist_v18/Run2016$sample\_JetHT_17Jul2018.txt
#    grep 'Run2017'$sample'-31Mar2018.*JetHT*' inputfiles_v18.txt > inputlist_v18/Run2017$sample\_JetHT_17Jul2018.txt
    grep 'Run2018'$sample'-17Sep2018-v1.*JetHT*' inputfiles_v18.txt > inputlist_v18/Run2018$sample\_JetHT_17Jul2018.txt

done
    grep 'Run2018D-PromptReco-v2.JetHT*' inputfiles_v18.txt > inputlist_v18/Run2018D_JetHT_17Jul2018.txt

sed -i "s#Run#root://cmseos.fnal.gov//store/user/lpcsusyhad/SusyRA2Analysis2015/Run2ProductionV18/Run#" inputlist_v18/*.txt
