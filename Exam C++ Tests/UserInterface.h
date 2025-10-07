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
			std::cout << "\n--- ���� ����������� ---\n";
			std::cout << "1. �������� ������\n";
			std::cout << "2. ������ ����\n";
			std::cout << "0. �����\n";
			std::cout << "�����i�� ���i�: ";
			int option;
			std::cin >> option;
			switch (option)
			{
			case 1:
			{
				std::string login, password, fullName, address, phone;
				int shift = 5; 
				std::cout << "����i�� ���i� �����������: ";
				std::cin >> login;
				std::cout << "����i�� ������ �����������: ";
				std::cin >> password;
				std::cout << "����i�� ����� i�'� �����������: ";
				std::cin.ignore(); 
				std::getline(std::cin, fullName);
				std::cout << "����i�� ������ �����������: ";
				std::getline(std::cin, address);
				std::cout << "����i�� ������� �����������: ";
				std::getline(std::cin, phone);
				addUser_1("exam_tests.db", login, password, fullName, address, phone, shift);

			}
			break;
			case 2:
				userTakeTest("exam_tests.db");
				break;
			case 0:
				std::cout << "���i� � ���� �����������.\n";
				return;
			default:
				std::cout << "���i��� ���i�. ��������� �� ���.\n";
				break;
			}
			std::cout << "������ ����������� �� ���� �����������? (y/n): ";
			std::cin >> userChoice;

		}
	}
}
