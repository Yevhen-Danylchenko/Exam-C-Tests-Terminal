#pragma once

#include <iostream>
#include <string>

#include "MyFuncAdmin.h"
#include "Tests.h"


using namespace MyFunctionsAdmin;
using namespace MyTestFunctions;

namespace AdminInter
{
	void adminMenu()
	{
		std::string adminChoice = "y";

		while (adminChoice == "y" || adminChoice == "Y")
		{
			std::cout << "\n--- ���� ���i�i�������� ---\n";
			std::cout << "1. ������ ���i�i��������\n";
			std::cout << "2. ������� ���i� �� ������ ���i�i��������\n";
			std::cout << "3. �������� ���� ����� �� ������i (���� �� �������i)\n";
			std::cout << "4. ������ �����������\n";
			std::cout << "5. �������� ������������� (�������/��������)\n";
			std::cout << "6. �������� ������� (������ �������)\n";
			std::cout << "7. ���������� ����������\n";
			std::cout << "0. �����\n";
			std::cout << "�����i�� ���i�: ";
			int option;
			std::cin >> option;
			switch (option)
			{
				case 1:
				{
					std::string login, password;
					int shift = 7; 
					std::cout << "����i�� ���i� ������ ���i�i��������: ";
					std::cin >> login;
					std::cout << "����i�� ������ ������ ���i�i��������: ";
					std::cin >> password;
					addAdmin("exam_tests.db", login, password, shift);
				}
				break;
				case 2:
				{
					std::string newLogin, newPassword;
					int shift = 7; 
					std::cout << "����i�� ����� ���i� ���i�i��������: ";
					std::cin >> newLogin;
					std::cout << "����i�� ����� ������ ���i�i��������: ";
					std::cin >> newPassword;
					updateAdminLoginPassword("exam_tests.db", newLogin, newPassword, shift);
				}
				break;
				case 3:
				{
					createDatabaseAndTable("exam_tests.db");
					createUserTable("exam_tests.db");
					createTestsTable("exam_tests.db");
					createTestResultsTable("exam_tests.db");
					std::vector<Test> tests = createTest();
					for (const auto& test : tests) {
						addTestToDatabase("exam_tests.db", test);
					}
				}
				break;
				case 4:
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
					addUser("exam_tests.db", login, password, fullName, address, phone, shift);
				}
				break;
				case 5:
				{
					int userOption;
					std::cout << "1. ������� �����������\n";
					std::cout << "2. �������� �����������\n";
					std::cout << "�����i�� ���i�: ";
					std::cin >> userOption;
					if (userOption == 1)
					{
						int userID;
						std::string newLogin, newPassword, newFullName, newAddress, newPhone;
						int shift = 5; 
						std::cout << "����i�� ID ����������� ��� ���������: ";
						std::cin >> userID;
						std::cout << "����i�� ����� ���i� �����������: ";
						std::cin >> newLogin;
						std::cout << "����i�� ����� ������ �����������: ";
						std::cin >> newPassword;
						std::cout << "����i�� ���� ����� i�'� �����������: ";
						std::cin.ignore(); 
						std::getline(std::cin, newFullName);
						std::cout << "����i�� ���� ������ �����������: ";
						std::getline(std::cin, newAddress);
						std::cout << "����i�� ����� ������� �����������: ";
						std::getline(std::cin, newPhone);
						adminUpdateUser("exam_tests.db", userID, newLogin, newPassword, newFullName, newAddress, newPhone, shift);
					}
					else if (userOption == 2)
					{
						int userID;
						std::cout << "����i�� ID ����������� ��� ���������: ";
						std::cin >> userID;
						adminDeleteUser("exam_tests.db", userID);
					}
					else
					{
						std::cout << "���i��� ���i�.\n";
					}
				}
				break;
				case 6:
				{
					std::string category, subCategory, question, option1, option2, option3, option4;
					int correctAnswer;
					std::cout << "����i�� �������i� �����: ";
					std::cin >> category;
					std::cout << "����i�� �i��������i� �����: ";
					std::cin >> subCategory;
					for (int i = 0; i < 10; i++) 
					{
						std::cout << "����i�� ����� �������: ";
						std::cin.ignore(); 
						std::getline(std::cin, question);
						std::cout << "����i�� ���i��� �i����i�i 1: ";
						std::getline(std::cin, option1);
						std::cout << "����i�� ���i��� �i����i�i 2: ";
						std::getline(std::cin, option2);
						std::cout << "����i�� ���i��� �i����i�i 3: ";
						std::getline(std::cin, option3);
						std::cout << "����i�� ���i��� �i����i�i 4: ";
						std::getline(std::cin, option4);
						std::cout << "����i�� ����� ��������� �i����i�i (1-4): ";
						std::cin >> correctAnswer;
						adminAddTestQuestion("exam_tests.db", category, subCategory, question, option1, option2, option3, option4, correctAnswer);
					}
				}
				break;
				case 7:
				{
					adminReadeResults("exam_tests.db");
				}
				break;
				case 0:
				{
					std::cout << "���i� � ���� ���i�i��������.\n";
					return;
				}
				break;
				default:
				{
					std::cout << "���i��� ���i�. ��������� �� ���.\n";
				}
				break;

			}
			std::cout << "������ ����������� �� ���� ���i�i��������? (y/n): ";
			std::cin >> adminChoice;
		}

	}
}
