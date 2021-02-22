#include "save_file.h"

// A simple save function to save all users and accounts to a txt file

int read_save_file(std::vector<User>& user_list, std::fstream& save_file, std::string& file_name)
{
	save_file.open(file_name);
	if (save_file.is_open())
	{
		std::string first_name;
		std::string last_name;
		std::string account_name;

		int number_of_users;
		int funds;
		// Reads number of users saved to the file
		save_file >> number_of_users;

		for (int i = 0; i < number_of_users; i++)
		{
			// Reads names of users and adds them to the list of users
			save_file >> first_name;
			save_file >> last_name;
			add_user_from_save_file(user_list, i, first_name, last_name);

			// Checks how many accounts the user has
			int number_of_accounts;
			save_file >> number_of_accounts;

			for (int j = 0; j < number_of_accounts; j++)
			{
				// Reads whitespace so getline does not stop prematurely
				save_file >> std::ws;
				std::getline(save_file, account_name); 
				user_list[i].add_account(account_name);
				// Reads funds and adds them to the right account using an std::iterator
				save_file >> funds;
				std::next(user_list[i].get_account_list().begin(), j)->add_funds(funds);
			}
		}

		// Closes the file and returns the number of users stored in the file
		save_file.close();
		return number_of_users;
	}
}

// Writes the currently stored users to a txt file to save it to disk
void write_save_file(std::vector<User>& user_list, std::fstream& save_file, std::string& file_name)
{
	save_file.open(file_name, std::ofstream::out | std::ofstream::trunc);
	if (save_file.is_open())
	{
		save_file << user_list.size() << std::endl;

		for (auto& it : user_list)
		{
			save_file << it.get_name() << std::endl << it.get_account_list().size() << std::endl;
			
			for (auto& account_it : it.get_account_list())
			{
				save_file << account_it.get_account_name() << std::endl;
				save_file << account_it.get_balance() << std::endl;
			}
		}

		save_file.close();
	}
}