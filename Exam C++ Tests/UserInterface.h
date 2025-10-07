#pragma once

#include <iostream>
#include <string>

#include "MyFuncAdmin.h"
#include "MyFuncUsers.h"

using namespace MyFunctionsAdmin;
using namespace MyFuncUsers;

namespace UserInter
{
	void userMenu()
	{
		std::string userChoice = "y";
		while (userChoice == "y" || userChoice == "Y")
		{
			std::cout << "\n--- Меню Користувача ---\n";
			std::cout << "1. Створити акаунт\n";
			std::cout << "2. Пройти тест\n";
			std::cout << "0. Вийти\n";
			std::cout << "Виберiть опцiю: ";
			int option;
			std::cin >> option;
			switch (option)
			{
			case 1:
			{
				std::string login, password, fullName, address, phone;
				int shift = 5; 
				std::cout << "Введiть логiн користувача: ";
				std::cin >> login;
				std::cout << "Введiть пароль користувача: ";
				std::cin >> password;
				std::cout << "Введiть повне iм'я користувача: ";
				std::cin.ignore(); 
				std::getline(std::cin, fullName);
				std::cout << "Введiть адресу користувача: ";
				std::getline(std::cin, address);
				std::cout << "Введiть телефон користувача: ";
				std::getline(std::cin, phone);
				addUser_1("exam_tests.db", login, password, fullName, address, phone, shift);

			}
			break;
			case 2:
				userTakeTest("exam_tests.db");
				break;
			case 0:
				std::cout << "Вихiд з меню користувача.\n";
				return;
			default:
				std::cout << "Невiрна опцiя. Спробуйте ще раз.\n";
				break;
			}
			std::cout << "Бажаєте повернутися до меню користувача? (y/n): ";
			std::cin >> userChoice;

		}
	}
}
