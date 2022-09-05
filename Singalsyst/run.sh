#root -l 'plotsys.C("ISRsys","T5ttttZg")'
rm -rf plots/*

for i in T5bbbbZg T5qqqqHg T5ttttZg T6ttZg TChiWG TChiNG
do
    mkdir plots/${i}
    cp -r res plots/${i}/.
    cp index.php plots/${i}/.
    for j in btagsys JECsys JERsys ISRsys  PUsys L1sys
    do
	root -l -q 'plotsys.C("'$j'","'$i'")'
    done
done

for j in T5bbbbZg T5qqqqHg T5ttttZg TChiWG TChiNG
do
    for i in scale #pdf
    do
        root -l -q 'plotoverlay.C("'$j'",2200,200,"'$i'")'
        root -l -q 'plotoverlay.C("'$j'",2200,1000,"'$i'")'
	root -l -q 'plotoverlay.C("'$j'",2200,2100,"'$i'")'
    done
done

j=T6ttZg
for i in scale #pdf
do
    root -l -q 'plotoverlay.C("'$j'",1200,200,"'$i'")'
    root -l -q 'plotoverlay.C("'$j'",1200,600,"'$i'")'
    root -l -q 'plotoverlay.C("'$j'",1200,1100,"'$i'")'
done

j=T5ttttZg
for i in scale #pdf
do
    root -l -q 'plotoverlay.C("'$j'",2000,200,"'$i'")'
    root -l -q 'plotoverlay.C("'$j'",2000,1000,"'$i'")'
    root -l -q 'plotoverlay.C("'$j'",2000,1775,"'$i'")'
done

for j in TChiWG TChiNG
do
    for i in scale #pdf
    do
        root -l -q 'plotoverlay.C("'$j'",0,800,"'$i'")'
	root -l -q 'plotoverlay.C("'$j'",0,1000,"'$i'")'
        root -l -q 'plotoverlay.C("'$j'",0,1200,"'$i'")'
    done
done


    
	 
