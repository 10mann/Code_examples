#ifndef USER_H
#define USER_H

#include <string>
#include <vector>
#include <iostream>
#include "Account.h"

class User
{
public:
	// ==================== Constructors ====================
	User();
	User(int id);
	User(int id, std::string first_name, std::string last_name);
	~User();

	// ==================== Accessors ====================
	void set_first_name(std::string& first_name);
	void set_last_name(std::string& last_name);
	std::string get_name();
	int get_id();
	std::vector<Account>& get_account_list();

	// ==================== Functions ====================
	void add_account(std::string account_name);
	void edit();
	void manage_accounts();
	void print_user();

	// ==================== Static variables ====================
	const static int MAX_ACCOUNTS = 1000;

private:
	std::string first_name;
	std::string last_name;
	int id;
	int number_of_accounts;
	std::vector<Account> account_list;

};


void add_user(std::vector<User>& user_list, int id);

void add_user_from_save_file(std::vector<User>& user_list, int id, std::string first_name, std::string last_name);

void edit_user(std::vector<User>& user_list);

void delete_user(std::vector<User>& user_list);

#endif