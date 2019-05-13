#/bin/sh



chmod 777 *
cp ./libGCBase_gcc421_v3_0.so /usr/lib
cp ./libGenApi_gcc421_v3_0.so /usr/lib
cp ./liblog4cpp_gcc421_v3_0.so /usr/lib
cp ./libLog_gcc421_v3_0.so /usr/lib
cp ./libMathParser_gcc421_v3_0.so /usr/lib
cp ./libMediaProcess.so /usr/lib
cp ./libMvCameraControl.so /usr//lib
cp ./libMVGigEVisionSDK.so /usr/lib
cp ./libMVRender.so /usr/lib
cp ./libMvUsb3vTL.so /usr/lib
cp ./libNodeMapData_gcc421_v3_0.so /usr/lib
cp ./libXmlParser_gcc421_v3_0.so /usr/lib


cp ./libQtCore.so.4.8.7 /usr/lib
cp ./libQtGui.so.4.8.7 /usr/lib
cp ./libQtNetwork.so.4.8.7 /usr/lib
cp ./libQtXml.so.4.8.7 /usr/lib

ln -s ./libQtCore.so.4.8.7 ./libQtCore.so.4
ln -s ./libQtGui.so.4.8.7 ./libQtGui.so.4
ln -s ./libQtNetwork.so.4.8.7 ./libQtNetwork.so.4
ln -s ./libQtXml.so.4.8.7 ./libQtXml.so.4

ln -s /usr/lib/libQtCore.so.4.8.7 /usr/lib/libQtCore.so.4
ln -s /usr/lib/libQtGui.so.4.8.7 /usr/lib/libQtGui.so.4
ln -s /usr/lib/libQtNetwork.so.4.8.7 /usr/lib/libQtNetwork.so.4
ln -s /usr/lib/libQtXml.so.4.8.7 /usr/lib/libQtXml.so.4
