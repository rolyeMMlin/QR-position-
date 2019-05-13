#!bin/bash
cd lib
for i in `ls *.2.4.9`;
do
 cp ${i} ../libsLink/${i};
 echo ${i}
 ln -s ../libsLink/${i}  ../libsLink/${i%%.*}.so
 ln -s ../libsLink/${i} ../libsLink/${i%%.*}.so.2.4
done
