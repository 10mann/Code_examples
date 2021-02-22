#include "user_interface.h"

// Prints out the menu
void print_menu()
{
	std::cout << "***Menu***\n1. Add user \n2. Edit user \n3. Delete user\n4. Print users\n5. Exit\n";
}

// Prints out all users and accounts
void print_all_users(std::vector<User> user_list)
{
	for (auto& it : user_list)
		it.print_user();
}