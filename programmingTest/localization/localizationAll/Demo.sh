#!/bin/bash
cd /home/firefly/Work/programmingTest/localization/localizationAll
cp ./MvSdkLog
rm -f ./MvSdkLog -R
rm -f ./backup/leftCameraImgs -R
cp ./leftCameraImgs ./backup/leftCameraImgs -R
rm -f ./leftCameraImgs -R
mkdir leftCameraImgs
rm -f ./backup/rightCameraImgs -R
cp ./rightCameraImgs ./backup/rightCameraImgs -R
rm -f ./rightCameraImgs -R
mkdir rightCameraImgs
rm -f ./backup/upCameraImgs -R
cp ./upCameraImgs ./backup/upCameraImgs -R
rm -f ./upCameraImgs -R
mkdir upCameraImgs
./main_5_class
