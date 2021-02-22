#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>
#include <vector>
#include <iostream>


class Account
{
public:
	//==================== Constructors ====================
	Account();
	Account(std::string account_name, int account_number);
	~Account();

	// ==================== Accessors ====================
	std::string get_account_name();
	void set_account_name(std::string account_name);
	double get_balance();

	// ==================== Functions ====================
	void edit();
	void add_funds(double amount);
	void print_account();

private:

	std::string account_name;
	int account_number;
	double account_balance;

};

void add_account(std::vector<Account>& account_list, int account_id);

#endif