#!/bin/sh                                                                                                                                                     
for i in {36200247..36200569}
do 
    condor_rm -name lpcschedd2.fnal.gov ${i}.0
done

# for i in {300..1600..25}
# do 
#    ./worker_hadd.sh 0 ${i}
# done