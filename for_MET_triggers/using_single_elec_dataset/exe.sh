#!/bin/sh    
for i in B C D E F G H
do
    echo $i
    mv Run2016$i\_MET_17Jul2018.root Run2016$i\_MET_17Jul2018_ST800.root
done