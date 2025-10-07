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
			std::cout << "\n--- Меню Адмiнiстратора ---\n";
			std::cout << "1. Додати адмiнiстратора\n";
			std::cout << "2. Оновити логiн та пароль адмiнiстратора\n";
			std::cout << "3. Створити базу даних та таблицi (якщо не створенi)\n";
			std::cout << "4. Додати користувача\n";
			std::cout << "5. Керувати користувачами (оновити/видалити)\n";
			std::cout << "6. Керувати тестами (додати питання)\n";
			std::cout << "7. Подивитися статистику\n";
			std::cout << "0. Вийти\n";
			std::cout << "Виберiть опцiю: ";
			int option;
			std::cin >> option;
			switch (option)
			{
				case 1:
				{
					std::string login, password;
					int shift = 7; 
					std::cout << "Введiть логiн нового адмiнiстратора: ";
					std::cin >> login;
					std::cout << "Введiть пароль нового адмiнiстратора: ";
					std::cin >> password;
					addAdmin("exam_tests.db", login, password, shift);
				}
				break;
				case 2:
				{
					std::string newLogin, newPassword;
					int shift = 7; 
					std::cout << "Введiть новий логiн адмiнiстратора: ";
					std::cin >> newLogin;
					std::cout << "Введiть новий пароль адмiнiстратора: ";
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
					addUser("exam_tests.db", login, password, fullName, address, phone, shift);
				}
				break;
				case 5:
				{
					int userOption;
					std::cout << "1. Оновити користувача\n";
					std::cout << "2. Видалити користувача\n";
					std::cout << "Виберiть опцiю: ";
					std::cin >> userOption;
					if (userOption == 1)
					{
						int userID;
						std::string newLogin, newPassword, newFullName, newAddress, newPhone;
						int shift = 5; 
						std::cout << "Введiть ID користувача для оновлення: ";
						std::cin >> userID;
						std::cout << "Введiть новий логiн користувача: ";
						std::cin >> newLogin;
						std::cout << "Введiть новий пароль користувача: ";
						std::cin >> newPassword;
						std::cout << "Введiть нове повне iм'я користувача: ";
						std::cin.ignore(); 
						std::getline(std::cin, newFullName);
						std::cout << "Введiть нову адресу користувача: ";
						std::getline(std::cin, newAddress);
						std::cout << "Введiть новий телефон користувача: ";
						std::getline(std::cin, newPhone);
						adminUpdateUser("exam_tests.db", userID, newLogin, newPassword, newFullName, newAddress, newPhone, shift);
					}
					else if (userOption == 2)
					{
						int userID;
						std::cout << "Введiть ID користувача для видалення: ";
						std::cin >> userID;
						adminDeleteUser("exam_tests.db", userID);
					}
					else
					{
						std::cout << "Невiрна опцiя.\n";
					}
				}
				break;
				case 6:
				{
					std::string category, subCategory, question, option1, option2, option3, option4;
					int correctAnswer;
					std::cout << "Введiть категорiю тесту: ";
					std::cin >> category;
					std::cout << "Введiть пiдкатегорiю тесту: ";
					std::cin >> subCategory;
					for (int i = 0; i < 10; i++) 
					{
						std::cout << "Введiть текст питання: ";
						std::cin.ignore(); 
						std::getline(std::cin, question);
						std::cout << "Введiть варiант вiдповiдi 1: ";
						std::getline(std::cin, option1);
						std::cout << "Введiть варiант вiдповiдi 2: ";
						std::getline(std::cin, option2);
						std::cout << "Введiть варiант вiдповiдi 3: ";
						std::getline(std::cin, option3);
						std::cout << "Введiть варiант вiдповiдi 4: ";
						std::getline(std::cin, option4);
						std::cout << "Введiть номер правильної вiдповiдi (1-4): ";
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
					std::cout << "Вихiд з меню адмiнiстратора.\n";
					return;
				}
				break;
				default:
				{
					std::cout << "Невiрна опцiя. Спробуйте ще раз.\n";
				}
				break;

			}
			std::cout << "Бажаєте повернутися до меню адмiнiстратора? (y/n): ";
			std::cin >> adminChoice;
		}

	}
}
