#!/bin/sh                                                                                                                                                                                      
for year in 2016 2017 2018 full_Run2
do
    for file in TTWGJ TTGJets TTJets WGJets WJets
    do
	root -l -q 'plotcutflow.C("'${file}'","'${year}'")'
    done
done
