First look at the background samples at following directories :
on TIFR cluster : /home/bkansal/t3store3/work/MET_analysis/v17_samples/
on CMSLPC cluster : /eos/uscms/store/user/bkansal/GMSB_skims_TreesV17/SignalRegion/skims/


Now make the text files containg the full path of the above samples using following command :
./maketxtfiles.sh
*you may need to changee the path of the directory in maketxtfiles.sh.


To run the Analyzer code, follow these Commands :
make
./analyzeLightBSM <txt file name> <output rootfile name> <dataset name>
for example, ./analyzeLightBSM runList_TTGJets_2017_v17.txt TTGJets_2017_v17.root TTG_v17_2016

