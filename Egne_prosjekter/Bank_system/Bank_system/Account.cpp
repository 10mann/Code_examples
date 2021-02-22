#include "Account.h"

// ==================== Constructors ====================
Account::Account()
{
	// Initializes account ID to -1 to make it invalid
	this->account_number = -1;
	this->account_balance = 0;
}

Account::Account(std::string account_name, int account_number)
{
	this->account_number = account_number;
	this->account_balance = 0;

	this->account_name = account_name;
}

Account::~Account()
{

}

// ==================== Accessors ====================
std::string Account::get_account_name()
{
	return this->account_name;
}

void Account::set_account_name(std::string account_name)
{
	this->account_name = account_name;
}

double Account::get_balance()
{
	return this->account_balance;
}

// ==================== Functions ====================
void Account::edit()
{
	std::string new_account_name;
	double funds;
	int choice;

	// Loops until user wants to exit
	while(1)
	{ 
		std::cout << "1. Rename account\n2. Add funds\n3. Exit\n";
		std::cin >> choice;

		switch (choice)
		{
		case 1:
			std::cout << "Please enter new account_name\n";
			
			std::cin >> new_account_name;
			this->set_account_name(new_account_name);
			break;

		case 2:
			std::cout << "Enter the amount you would like to add\n";

			std::cin >> funds;
			this->add_funds(funds);
			break;

		case 3:
			return;

		default:
			std::cout << "Invalid selection, please enter valid option\n";
			break;
		}
	}
}

void Account::add_funds(double amount)
{
	this->account_balance += amount;
}

void Account::print_account()
{
	std::cout << /*"Account name: " <<*/ this->account_name << "\n\tID: " << this->account_number << "\n\tBalance: " << this->account_balance << "$\n";
}

void add_account(std::vector<Account>& account_list, int id)
{
	std::cout << "Enter account name\n";

	std::string account_name;
	std::cin >> account_name;

	account_list.push_back(Account(account_name, id));
}