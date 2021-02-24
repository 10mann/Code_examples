#ifndef SERIAL_PORT_H
#define SERIAL_PORT_H

//#include "olcPixelGameEngine.h"
#include <Windows.h>
#include <thread>
#include <iostream>

#define MAX_SERIAL_BUFFER 20
#define MAX_SERIAL_OUTPUT_BUFFER 1024

class Serial
{
public:
	LPCWSTR com_port;
	HANDLE handle_port;
	DCB dcb;

	Serial();
	~Serial();

	bool write(char* data, int size);
	bool read(char* data, int size, DWORD* bytes_read);
	bool read_byte_until(char* data, char c);
	bool start(LPCWSTR com_port, int com_speed);

};

#endif