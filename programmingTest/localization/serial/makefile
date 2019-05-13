project = serial

CC = g++

CXXFLAGS = -c -O3 -fPIC
CPPFLAGS = -I ./ -I /home/firefly/Work/mylibs/serial/include/
LDFLAGS = -L /home/firefly/Work/mylibs/serial/lib/
LIBS = -lserial -lstdc++

all:serali clean

serali:serial2lib.ro
	$(CC) -shared -fPIC $^ -o libserial2lib.so $(LDFLAGS) $(LIBS)
	rm -f /home/firefly/Work/programmingTest/localization/localizationAll/libserial2lib.so
	cp ./libserial2lib.so /home/firefly/Work/programmingTest/localization/localizationAll/libserial2lib.so

serial2lib.ro:serial2lib.cpp
	$(CC) $(CXXFLAGS) $< -o $@ $(CPPFLAGS) $(LDFLAGS) $(LIBS)
	
.PHONY:clean

clean:
	rm -f ./*.ro
