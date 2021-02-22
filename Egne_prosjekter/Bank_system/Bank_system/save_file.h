#ifndef SAVE_FILE_H
#define SAVE_FILE_H

#include <fstream>
#include <string>
#include <vector>

#include "User.h"

int read_save_file(std::vector<User>& user_list, std::fstream& save_file, std::string& file_name);

void write_save_file(std::vector<User>& user_list, std::fstream& save_file, std::string& file_name);

#endif