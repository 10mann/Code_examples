#ifndef SERIAL_PORT_POLL_H
#define SERIAL_PORT_POLL_H

#include "serial_port.h"
#include <string>
#include <stdexcept>
#include <iostream>

void poll_serial_data(int* serial_buffer, int serial_buffer_size);

#endif