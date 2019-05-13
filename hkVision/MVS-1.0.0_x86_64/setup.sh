#/bin/sh

DIRNAME=`dirname $0`

cd $DIRNAME

#sed -i "s/export LD_LIBRARY_PATH/#export LD_LIBRARY_PATH/g" ~/.bashrc
source ~/.bashrc
if [ ! -d "/opt/MVS" ]; then
	echo "Install MVS,Please wait..."
	tar -C /opt -xzf ./MVS_x86_64.tar.gz
else
	echo "Uninstall MVS,Please wait..."
	rm -rf /opt/MVS
	echo "Install MVS,Please wait..."
	tar -C /opt -xzf ./MVS_x86_64.tar.gz
fi
#
if [ ! -d "/usr/local/Qt-5.6.3/lib/fonts" ]; then
	mkdir -p /usr/local/Qt-5.6.3/lib/fonts
	cp -r /opt/MVS/bin/fonts/* /usr/local/Qt-5.6.3/lib/fonts
else
	echo "path exist..."
fi
#

#if  cat ~/.bashrc | grep -c "export LD_LIBRARY_PATH=/opt/MVS/bin" > /dev/null
#then
#	echo "Include path exist"
#else
#  	echo   "export LD_LIBRARY_PATH=/opt/MVS/bin" >> ~/.bashrc
#fi

#source ~/.bashrc

echo "Install MVS complete!"

#tar zxvf ./MVS_x86_64.tar.gz
#tar zxvf ./demo.tar.gz

#chmod 777 ./MVS
#chmod 777 ./MVS/bin/*
#cp ./MVS/bin/libGCBase_gcc421_v3_0.so /opt/MVS/lib
#cp ./MVS/bin/libGenApi_gcc421_v3_0.so /opt/MVS/lib
#cp ./MVS/bin/liblog4cpp_gcc421_v3_0.so /opt/MVS/lib
#cp ./MVS/bin/libLog_gcc421_v3_0.so /opt/MVS/lib
#cp ./MVS/bin/libMathParser_gcc421_v3_0.so /opt/MVS/lib
#cp ./MVS/bin/libMediaProcess.so /opt/MVS/lib
#cp ./MVS/bin/libMvCameraControl.so /opt/MVS/lib
#cp ./MVS/bin/libMVGigEVisionSDK.so /opt/MVS/lib
#cp ./MVS/bin/libMVRender.so /opt/MVS/lib
#cp ./MVS/bin/libMvUsb3vTL.so /opt/MVS/lib
#cp ./MVS/bin/libNodeMapData_gcc421_v3_0.so /opt/MVS/lib
#cp ./MVS/bin/libXmlParser_gcc421_v3_0.so /opt/MVS/lib


#cp ./MVS/bin/libQt5Core.so.5.6.3 /opt/MVS/lib
#cp ./MVS/bin/libQt5Gui.so.5.6.3 /opt/MVS/lib
#cp ./MVS/bin/libQt5Network.so.5.6.3 /opt/MVS/lib
#cp ./MVS/bin/libQt5Xml.so.5.6.3 /opt/MVS/lib
#cp ./MVS/bin/libQt5Widgets.so.5.6.3 /opt/MVS/lib

#cp ./MVS/bin/libQt5DBus.so.5.6.3 /opt/MVS/lib
#cp ./MVS/bin/libQt5XcbQpa.so.5.6.3 /opt/MVS/lib

#cp ./MVS/bin/libicudata.so.56.1 /opt/MVS/lib
#cp ./MVS/bin/libicui18n.so.56.1 /opt/MVS/lib
#cp ./MVS/bin/libicuuc.so.56.1 /opt/MVS/lib

#cp ./MVS/bin/libQt5Core.so.5 /usr/MVS/lib
#cp ./MVS/bin/libQt5Gui.so.5 /usr/MVS/lib
#cp ./MVS/bin/libQt5Network.so.5 /usr/MVS/lib
#cp ./MVS/bin/libQt5Xml.so.5 /usr/MVS/lib
#cp ./MVS/bin/libQt5Widgets.so.5 /usr/MVS/lib

#cp ./MVS/bin/libQt5DBus.so.5 /usr/MVS/lib
#cp ./MVS/bin/libQt5XcbQpa.so.5 /usr/MVS/lib

#cp ./MVS/bin/libicudata.so.56 /opt/MVS/lib
#cp ./MVS/bin/libicui18n.so.56 /opt/MVS/lib
#cp ./MVS/bin/libicuuc.so.56 /opt/MVS/lib

#cp ./MVS/bin/libQt5Core.so.5.6.3 /usr/lib/x86_64-linux-gnu
#cp ./MVS/bin/libQt5Gui.so.5.6.3 /usr/lib/x86_64-linux-gnu
#cp ./MVS/bin/libQt5Network.so.5.6.3 /usr/lib/x86_64-linux-gnu
#cp ./MVS/bin/libQt5Xml.so.5.6.3 /usr/lib/x86_64-linux-gnu
#cp ./MVS/bin/libQt5Widgets.so.5.6.3 /usr/lib/x86_64-linux-gnu

#ln -s /opt/MVS/lib/libQt5Core.so.5.6.3 /opt/MVS/lib/libQt5Core.so.5
#ln -s /opt/MVS/lib/libQt5Gui.so.5.6.3 /opt/MVS/lib/libQt5Gui.so.5
#ln -s /opt/MVS/lib/libQt5Xml.so.5.6.3 //opt/MVS/lib/libQt5Network.so.5
#ln -s /opt/MVS/lib/libQt5Network.so.5.6.3 /opt/MVS/lib/libQt5Xml.so.5
#ln -s /opt/MVS/lib/libQt5Widgets.so.5.6.3 /opt/MVS/lib/libQt5Widgets.so.5

#ln -s /opt/MVS/lib/libQt5DBus.so.5.6.3 /opt/MVS/lib/libQt5DBus.so.5
#ln -s /opt/MVS/lib/llibQt5XcbQpa.so.5.6.3 /opt/MVS/lib/libQt5XcbQpa.so.5

#ln -s /usr/MVS/lib/libicudata.so.56.1 /usr/local/lib/libicudata.so.56
#ln -s /usr/MVS/lib/libicui18n.so.56.1 /usr/local/lib/libicui18n.so.56
#ln -s /usr/MVS/lib/libicuuc.so.56.1 /usr/local/lib/libicuuc.so.56

#chmod 777 ./MVS/bin/*
#ln -s /usr/lib/libQtCore.so.4.8.7 /usr/lib/libQtCore.so.4
#ln -s /usr/lib/libQtGui.so.4.8.7 /usr/lib/libQtGui.so.4
#ln -s /usr/lib/libQtNetwork.so.4.8.7 /usr/lib/libQtNetwork.so.4
#ln -s /usr/lib/libQtXml.so.4.8.7 /usr/lib/libQtXml.so.4
#cp ./MVS/bin/libQt5Core.so.5 /usr/MVS/lib
#cp ./MVS/bin/libQt5Gui.so.5 /usr/MVS/lib
#cp ./MVS/bin/libQt5Network.so.5 /usr/MVS/lib
#cp ./MVS/bin/libQt5Xml.so.5 /usr/MVS/lib
#cp ./MVS/bin/libQt5Widgets.so.5 /usr/MVS/lib

#cp ./MVS/bin/libQt5Core.so.5 /usr/lib/x86_64-linux-gnu
#cp ./MVS/bin/llibQt5Gui.so.5 /usr/lib/x86_64-linux-gnu
#cp ./MVS/bin/libQt5Network.so.5 /usr/lib/x86_64-linux-gnu
#cp ./MVS/bin/libQt5Xml.so.5 /usr/lib/x86_64-linux-gnu
#cd ./MVS

#tar zxvf ./libusb-1.0.9.tar.gz

#cd ./libusb-1.0.9
#chmod 777 ./*
#./configure
#make 
#make install

#if  cat /etc/ld.so.conf | grep -c "/usr/local/lib" > /dev/null
#then
#	echo "Include path exist"
#else
#  	echo   "/usr/local/lib" >> /etc/ld.so.conf
#fi


#ldconfig


