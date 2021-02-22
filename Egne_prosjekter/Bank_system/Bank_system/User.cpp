#include "User.h"

// ==================== Constructors ====================
User::User()
{
	this->id = -1;
	this->number_of_accounts = 0;
}

User::User(int id)
{
	this->id = id;
	this->number_of_accounts = 0;
}

User::User(int id, std::string first_name, std::string last_name)
{
	this->id = id;
	this->number_of_accounts = 0;
	this->first_name = first_name;
	this->last_name = last_name;
}

User::~User()
{

}

// ==================== Accessors ====================
std::string User::get_name()
{
	return this->first_name + " " + this->last_name;
}

void User::set_first_name(std::string& first_name)
{
	this->first_name = first_name;
}

void User::set_last_name(std::string& last_name)
{
	this->last_name = last_name;
}

int User::get_id()
{
	return this->id;
}

std::vector<Account>& User::get_account_list()
{
	return this->account_list;
}

// ==================== Functions ====================

// This function is used to add an account to a user
// The account ID is calculated by multiplying the users ID with 1000 and adding the index of the account
// This limits the number of accounts a user can have to 1000
void User::add_account(std::string account_name)
{
	if (this->number_of_accounts >= User::MAX_ACCOUNTS)
	{
		// Error
		return;
	}

	this->account_list.push_back(Account(account_name, User::MAX_ACCOUNTS * this->id + this->number_of_accounts));
	this->number_of_accounts++;
}

// Edit takes in user input and makes the appropriate changes to a user
void User::edit()
{
	std::string new_first_name;
	std::string new_last_name;
	std::string account_name;

	int choice;

	// Loops while the user does not exit
	while (1)
	{
		std::cout << "1. Change first name\n2. Change last name\n3. Create new account\n4. Manage accounts\n5. Print accounts\n6. Exit\n";
		std::cin >> choice;

		switch (choice)
		{
		case 1:
			std::cout << "Enter new first name\n";
			std::cin >> new_first_name;
			this->set_first_name(new_first_name);
			break;

		case 2:
			std::cout << "Enter new last name\n";
			std::cin >> new_last_name;
			this->set_last_name(new_last_name);
			break;

		case 3:
			std::cout << "Enter account name\n";
			std::cin >> std::ws;
			std::getline(std::cin, account_name);
			add_account(account_name);
			break;

		case 4:
			this->manage_accounts();
			break;

		case 5:
			for (auto& it : this->account_list)
				it.print_account();
			break;

		case 6:
			return;

		default:
			std::cout << "Inavlid choice, please enter a valid option\n";
			break;
		}
	}
}

// Prints out a list of the current accounts and takes user input to determine which account is to be edited
void User::manage_accounts()
{
	int index = 1;

	for (auto& it : this->account_list)
		std::cout << index++ << ". " << it.get_account_name() << std::endl;

	std::cin >> index;

	if(index <= this->account_list.size())
		this->account_list[index - 1].edit();
}

void User::print_user()
{
	std::cout << /*"Name: \t\t" + */this->first_name << " " << this->last_name << "\nID: \t\t" << this->id << "\nAccounts: \t" << this->number_of_accounts << std::endl;

	for (auto& it : this->account_list)
	{
		it.print_account();
	}

	std::cout << std::endl;
}

// Takes in user parameters and creates a new user
void add_user(std::vector<User>& user_list, int id)
{
	std::string first_name;
	std::string last_name;

	std::cout << "Enter first name\n";
	std::cin >> first_name;

	std::cout << "Enter last name\n";
	std::cin >> last_name;

	user_list.push_back(User(id, first_name, last_name));
}

// Adds a user with parameters from a txt file
void add_user_from_save_file(std::vector<User>& user_list, int id, std::string first_name, std::string last_name)
{
	user_list.push_back(User(id, first_name, last_name));
}

// Prints out a list of users and takes in user input to select user to be edited
void edit_user(std::vector<User>& user_list)
{
	int index = 1;
	for (auto& it : user_list)
	{
		std::cout << index++ << ". " << it.get_name() << ", ID: " << it.get_id() << std::endl;
	}

	std::cout << index << ". Exit\n";

	std::cin >> index;

	if(index <= user_list.size())
		user_list[index - 1].edit();
}

// Prints out a list of users and deletes the one one selected
void delete_user(std::vector<User>& user_list)
{
	int index = 1;
	for (auto& it : user_list)
	{
		std::cout << "Name: " << index++ << ". " << it.get_name() << ", ID: " << it.get_id() << std::endl;
	}

	std::cin >> index;

	if (index <= user_list.size())
	{
		user_list.erase(user_list.begin() + index - 1);
	}
}