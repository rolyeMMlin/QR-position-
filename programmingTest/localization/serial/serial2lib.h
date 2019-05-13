#ifndef SERIAL2LIB_H_
#define SERIAL2LIB_H_
#include <string>
#include <iostream>
#include <cstdio>
#include <vector>
// OS Specific sleep
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif
#include "serial/serial.h"

using std::string;
using std::exception;
using std::cout;
using std::cerr;
using std::endl;
using std::vector;

void TransportPosition(serial::Serial& my_serial, int positionInfor[]);

void redaTty(serial::Serial& my_serial, string& readResults);

#endif