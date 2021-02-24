#include "serial_port.h"

Serial::Serial()
{
	this->com_port = L"Uninitialized";
	this->handle_port = nullptr;

}

bool Serial::start(LPCWSTR com_port, int com_speed)
{
	this->com_port = com_port;
	this->handle_port = CreateFile(this->com_port, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);

	DWORD dw_serial_error = 0;

	if (!GetCommState(this->handle_port, &this->dcb))
	{
		dw_serial_error = GetLastError();
		std::cout << "Error getting com state: " << dw_serial_error << std::endl;
		return false;
	}

	this->dcb.ByteSize = 8;
	this->dcb.BaudRate = com_speed;
	this->dcb.Parity = NOPARITY;
	this->dcb.StopBits = ONESTOPBIT;

	//return SetCommState(this->handle_port, &this->dcb);

	if (!SetCommState(this->handle_port, &this->dcb))
	{
		dw_serial_error = GetLastError();
		std::cout << "Error setting com state: " << dw_serial_error << std::endl;
		return false;
	}

	return true;
}

bool Serial::write(char* data, int size)
{
	DWORD bytes_written = 0;

	HANDLE handle_port = CreateFile(this->com_port, GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);

	bool ret_val = WriteFile(handle_port, data, size, &bytes_written, NULL);
	//CloseHandle(handle_port);
	return ret_val;
}

bool Serial::read(char* data, int size, DWORD* bytes_read)
{
	DCB dcb;
	//DWORD bytes_read = 0;
	DWORD dw_comm_modem_status = 0;
	DWORD dw_error_flags;
	COMSTAT com_stat;
	bool b_return_state;

	ClearCommError(this->handle_port, &dw_error_flags, &com_stat);

	if (com_stat.cbInQue >= size)
		return ReadFile(this->handle_port, data, size, bytes_read, 0);


	return false;
}

bool Serial::read_byte_until(char* data, char c)
{
	DWORD dw_error_flags;
	COMSTAT com_stat;
	DWORD dw_bytes_read = 0;
	char c_serial_char = '0';
	bool b_ret_val;
	int n_index = 0;



	for(;;)
	{
		ClearCommError(this->handle_port, &dw_error_flags, &com_stat);
		if (com_stat.cbInQue >= 1)
		{
			if (!ReadFile(this->handle_port, &c_serial_char, 1, &dw_bytes_read, 0))
				return false;
			if (c_serial_char == c)
				return true;

			data[n_index] = c_serial_char;
			n_index++;
		}
	}

	//std::cout << data << std::endl;

	return true;
}

Serial::~Serial()
{
	CloseHandle(this->handle_port);
}