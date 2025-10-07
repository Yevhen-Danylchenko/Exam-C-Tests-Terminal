#pragma once

#include <iostream>

#include <string>
#include "Tests.h"
#include "sqlite3.h"
#include "MyFuncAdmin.h"

namespace MyFuncUsers {
	using namespace MyFunctionsAdmin;

    bool chekUserLoginPassword(const std::string& dbName, const std::string& login, const std::string& password, int shift) {
        sqlite3* DB;
        int exit = sqlite3_open(dbName.c_str(), &DB);
        if (exit != SQLITE_OK) {
            std::cerr << "�� ������� �i������ ���� �����: " << sqlite3_errmsg(DB) << std::endl;
            sqlite3_close(DB);
            return false;
        }
        std::string encryptedLogin = caesarEncrypt(login, shift);
        std::string encryptedPassword = caesarEncrypt(password, shift);
        std::string sql = "SELECT * FROM User WHERE LOGIN = ? AND PASSWORD = ?;";
        sqlite3_stmt* stmt;
        exit = sqlite3_prepare_v2(DB, sql.c_str(), -1, &stmt, nullptr);
        if (exit != SQLITE_OK) {
            std::cerr << "������� ��� �i�������i ������: " << sqlite3_errmsg(DB) << std::endl;
            sqlite3_close(DB);
            return false;
        }
        sqlite3_bind_text(stmt, 1, encryptedLogin.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 2, encryptedPassword.c_str(), -1, SQLITE_STATIC);
        exit = sqlite3_step(stmt);
        bool userExists = (exit == SQLITE_ROW);
        sqlite3_finalize(stmt);
        sqlite3_close(DB);
        return userExists;
	}

	void addUser_1(const std::string& dbName, const std::string& login, const std::string& password, const std::string& fullName, const std::string& address, const std::string& phone, int shift) {
		addUser(dbName, login, password, fullName, address, phone, shift);
	}

    void userTakeTest(const std::string& dbName) {
        sqlite3* DB;
        int exit = sqlite3_open(dbName.c_str(), &DB);

        if (exit != SQLITE_OK) {
            std::cerr << "�� ������� �i������ ���� �����: " << sqlite3_errmsg(DB) << std::endl;
            sqlite3_close(DB);
            return;
        }

        std::string login;
        std::cout << "����i�� ��� ���i�: ";
        std::cin >> login;

		std::string password;
		std::cout << "����i�� ��� ������: ";
		std::cin >> password;

		int shift = 5;

        if (!chekUserLoginPassword(dbName, login, password, shift)) {
			std::cout << "���i���� ���i� ��� ������. ���������� ���������.\n";
            sqlite3_close(DB);
			return;
        }

        std::string sql = "SELECT DISTINCT CATEGORY, SUBCATEGORY FROM Tests;";
        sqlite3_stmt* stmt;
        exit = sqlite3_prepare_v2(DB, sql.c_str(), -1, &stmt, nullptr);

        if (exit != SQLITE_OK) {
            std::cerr << "������� ��� �i�������i ������: " << sqlite3_errmsg(DB) << std::endl;
            sqlite3_close(DB);
            return;
        }

        std::cout << "�������i �����:\n";
        std::vector<std::pair<std::string, std::string>> testList;
        while ((exit = sqlite3_step(stmt)) == SQLITE_ROW) {
            std::string category = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
            std::string subcategory = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
            testList.emplace_back(category, subcategory);
            std::cout << testList.size() << ") �������i�: " << category << ", �i��������i�: " << subcategory << std::endl;
        }

        sqlite3_finalize(stmt);

        if (testList.empty()) {
            std::cout << "���� ��������� ����i�.\n";
            sqlite3_close(DB);
            return;
        }

        int choice;
        std::cout << "\n����i�� ����� ����� ��� ����������� (��� 0 ��� ������): ";
        std::cin >> choice;
        if (choice <= 0 || choice > testList.size()) {
            std::cout << "���������� ���������.\n";
            sqlite3_close(DB);
            return;
        }

        std::string selectedCategory = testList[choice - 1].first;
        std::string selectedSubcategory = testList[choice - 1].second;
        std::string testName = selectedCategory + " - " + selectedSubcategory;

        std::string questionSQL = "SELECT QUESTION, OPTION1, OPTION2, OPTION3, OPTION4, CORRECT_ANSWER FROM Tests WHERE CATEGORY = ? AND SUBCATEGORY = ?;";
        sqlite3_stmt* questionStmt;
        exit = sqlite3_prepare_v2(DB, questionSQL.c_str(), -1, &questionStmt, nullptr);
        if (exit != SQLITE_OK) {
            std::cerr << "������� ��� �i�������i ������ ������: " << sqlite3_errmsg(DB) << std::endl;
            sqlite3_close(DB);
            return;
        }

        sqlite3_bind_text(questionStmt, 1, selectedCategory.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(questionStmt, 2, selectedSubcategory.c_str(), -1, SQLITE_STATIC);

        int score = 0;
        int totalQuestions = 0;

        while (sqlite3_step(questionStmt) == SQLITE_ROW) {
            std::string questionText = reinterpret_cast<const char*>(sqlite3_column_text(questionStmt, 0));
            std::string options[4];
            for (int i = 0; i < 4; ++i) {
                options[i] = reinterpret_cast<const char*>(sqlite3_column_text(questionStmt, i + 1));
            }
            int correctAnswer = sqlite3_column_int(questionStmt, 5);

            std::cout << "\n�������: " << questionText << std::endl;
            for (int i = 0; i < 4; ++i) {
                std::cout << (i + 1) << ") " << options[i] << std::endl;
            }

            std::cout << "��� ���i��� �i����i�i (1-4 ��� 0 ��� ������): ";
            int userAnswer;
            std::cin >> userAnswer;

            if (userAnswer == 0) {
                std::cout << "���������� �����������. �� ������ ���������� �i��i��.\n";
                break;
            }

            if (userAnswer == correctAnswer) {
                std::cout << "���������!\n";
                score++;
            }
            else {
                std::cout << "�����������. ��������� �i����i��: " << correctAnswer << "\n";
            }

            totalQuestions++;
        }

        sqlite3_finalize(questionStmt);

        if (totalQuestions > 0) {
            double percent = (static_cast<double>(score) / totalQuestions) * 100.0;
            int grade = static_cast<int>((score * 12.0) / totalQuestions + 0.5);

            std::cout << "\n���������� ����������:\n";
            std::cout << "���������� �i����i���: " << score << " � " << totalQuestions << "\n";
            std::cout << "�i������ ����������: " << percent << "%\n";
            std::cout << "��i��� �� 12-������� ��������: " << grade << "/12\n";

            
            std::string insertSQL = "INSERT INTO TestResults (LOGIN, TEST_NAME, CORRECT_ANSWERS, SCORE) VALUES (?, ?, ?, ?);";
            sqlite3_stmt* resultStmt;
            exit = sqlite3_prepare_v2(DB, insertSQL.c_str(), -1, &resultStmt, nullptr);
            if (exit == SQLITE_OK) {
                sqlite3_bind_text(resultStmt, 1, login.c_str(), -1, SQLITE_TRANSIENT);
                sqlite3_bind_text(resultStmt, 2, testName.c_str(), -1, SQLITE_TRANSIENT);
                sqlite3_bind_int(resultStmt, 3, score);
                sqlite3_bind_double(resultStmt, 4, percent);

                if (sqlite3_step(resultStmt) == SQLITE_DONE) {
                    std::cout << "��������� ���i��� ���������.\n";
                }
                else {
                    std::cerr << "������� ��� �����i ����������: " << sqlite3_errmsg(DB) << "\n";
                }

                sqlite3_finalize(resultStmt);
            }
            else {
                std::cerr << "������� ��� �i�������i ������ ������ ����������: " << sqlite3_errmsg(DB) << "\n";
            }
        }
        else {
            std::cout << "\n���� �� ��������� ��� �� �i���� ������.\n";
        }

        sqlite3_close(DB);
    }    
}
