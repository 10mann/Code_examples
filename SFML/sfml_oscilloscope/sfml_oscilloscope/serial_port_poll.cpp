#include "serial_port_poll.h"


extern int sample_frequency;

void poll_serial_data(int* serial_buffer, int serial_buffer_size)
{
	Serial serial;
	char serial_data[10];
	int index = 0;

	std::chrono::steady_clock::time_point last_time;

	if (!serial.start(L"COM3", CBR_115200))
	{
		std::cout << "Failed to start serial port\n";
		return;
	}

	for (;;)
	{

		if (serial.read_byte_until(serial_data, '\n'))
		{
			for (int i = 1; i < serial_buffer_size; i++)
			{
				serial_buffer[i - 1] = serial_buffer[i];
			}

			try
			{
				serial_buffer[serial_buffer_size - 1] = std::stoi(serial_data);
			}
			catch (std::invalid_argument& e)
			{

			}

			std::chrono::duration<double> time_diff = (std::chrono::steady_clock::now() - last_time);
			sample_frequency = std::chrono::seconds(1) / time_diff;
			last_time = std::chrono::steady_clock::now();

		}
	}
}