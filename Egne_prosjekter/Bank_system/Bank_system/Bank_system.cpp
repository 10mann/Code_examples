#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <fstream>

#include "User.h"
#include "Account.h"
#include "user_interface.h"
#include "save_file.h"

int main()
{
    int user_id = 0;
    int choice = 0;
    std::vector<User> user_list;

    std::string file_name = "save_file.txt";
    std::fstream save_file;

    user_id = read_save_file(user_list, save_file, file_name);


    while (1)
    {
        // Prints selection menu
        print_menu();

        std::cin >> choice;

        switch (choice)
        {
        case 1:
            // Add an account 
            add_user(user_list, user_id++);
            
            break;

        case 2:
            // Edit user
            edit_user(user_list);
            break;

        case 3:
            // Delete user
            delete_user(user_list);
            break;

        case 4:
            print_all_users(user_list);
            break;

        case 5:
            return 0;

        default:
            break;
        }



        write_save_file(user_list, save_file, file_name);
    }
}
