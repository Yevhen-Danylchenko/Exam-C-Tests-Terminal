// Exam C++ Tests.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <locale>
#include "AdminInterface.h"
#include "UserInterface.h"

using namespace AdminInter;
using namespace UserInter;

int main()
{
	setlocale(LC_ALL, "Ukrainian");
	std::string mainChoice = "y";

	while(mainChoice == "y" || mainChoice == "Y")
	{
		std::cout << "\n--- Головне Меню ---\n";
		std::cout << "1. Меню Адмiнiстратора\n";
		std::cout << "2. Меню Користувача\n";
		std::cout << "0. Вийти\n";
		std::cout << "Виберiть опцiю: ";
		int option;
		std::cin >> option;
		switch (option)
		{
		case 1:
			adminMenu();
			break;
		case 2:
			userMenu();
			break;
		case 0:
			std::cout << "Вихiд з програми.\n";
			return 0;
		default:
			std::cout << "Невiрна опцiя. Спробуйте ще раз.\n";
			break;
		}
		std::cout << "Бажаєте повернутися до головного меню? (y/n): ";
		std::cin >> mainChoice;
	}
}


