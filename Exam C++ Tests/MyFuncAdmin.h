#pragma once

#include <iostream>
#include <string>
#include "Tests.h"
#include "sqlite3.h"
#include <locale>
#include <stdexcept>

namespace MyFunctionsAdmin {	

    std::string caesarEncrypt(const std::string& text, int shift) {
        std::string result;
        for (char ch : text) {
            if (isalpha(ch)) {
                char base = islower(ch) ? 'a' : 'A';
                result += static_cast<char>((ch - base + shift) % 26 + base);
            }
            else if (isdigit(ch)) {
                result += static_cast<char>((ch - '0' + shift) % 10 + '0');
            }
            else {
                result += ch; 
            }
        }
        return result;
    }

    std::string caesarDecrypt(const std::string& text, int shift) {
        std::string result;
        for (char ch : text) {
            if (isalpha(ch)) {
                char base = islower(ch) ? 'a' : 'A';
                result += static_cast<char>((ch - base - shift + 26) % 26 + base);
            }
            else if (isdigit(ch)) {
                result += static_cast<char>((ch - '0' - shift + 10) % 10 + '0');
            }
            else {
                result += ch; 
            }
        }
        return result;
    }

    void createDatabaseAndTable(const std::string& dbName) {
        sqlite3* DB;
        int exit = sqlite3_open(dbName.c_str(), &DB);

        if (exit != SQLITE_OK) {
            std::cerr << "Не вдалося створити або вiдкрити базу даних: " << sqlite3_errmsg(DB) << std::endl;
            sqlite3_close(DB);
            return;
        }
        else {
            std::cout << "Базу даних \"" << dbName << "\" успiшно створено або вiдкрито.\n";
        }

        std::string sql = "CREATE TABLE IF NOT EXISTS Admin ("
            "ID INTEGER PRIMARY KEY AUTOINCREMENT, "
            "LOGIN TEXT NOT NULL, "
            "PASSWORD TEXT NOT NULL);";

        char* messageError = nullptr;
        exit = sqlite3_exec(DB, sql.c_str(), nullptr, 0, &messageError);

        if (exit != SQLITE_OK) {
            std::cerr << "Помилка при створеннi таблицi: " << messageError << std::endl;
            sqlite3_free(messageError);
        }
        else {
            std::cout << "Таблицю Admin успiшно створено або вона вже iснує.\n";
        }

        sqlite3_close(DB);
    }

    void createUserTable(const std::string& dbName) {
        sqlite3* DB;
        int exit = sqlite3_open(dbName.c_str(), &DB);

        if (exit != SQLITE_OK) {
            std::cerr << "Не вдалося створити або вiдкрити базу даних: " << sqlite3_errmsg(DB) << std::endl;
            sqlite3_close(DB);
            return;
        }

        std::string sql = "CREATE TABLE IF NOT EXISTS User ("
            "ID INTEGER PRIMARY KEY AUTOINCREMENT, "
            "LOGIN TEXT NOT NULL UNIQUE, "
            "PASSWORD TEXT NOT NULL, "
            "FULLNAME TEXT NOT NULL, "
            "ADDRESS TEXT NOT NULL, "
            "PHONE TEXT NOT NULL);";

        char* messageError = nullptr;
        exit = sqlite3_exec(DB, sql.c_str(), nullptr, 0, &messageError);

        if (exit != SQLITE_OK) {
            std::cerr << "Помилка при створеннi таблицi: " << messageError << std::endl;
            sqlite3_free(messageError);
        }
        else {
            std::cout << "Таблицю User успiшно створено або вона вже iснує.\n";
        }

        sqlite3_close(DB);
    }

    void addAdmin(const std::string& dbName, const std::string& login, const std::string& password, int shift) {
        sqlite3* DB;
        int exit = sqlite3_open(dbName.c_str(), &DB);

        if (exit != SQLITE_OK) {
            std::cerr << "Не вдалося вiдкрити базу даних: " << sqlite3_errmsg(DB) << std::endl;
            sqlite3_close(DB);
            return;
        }

        std::string checkSQL = "SELECT COUNT(*) FROM Admin;";
        sqlite3_stmt* checkStmt;
        exit = sqlite3_prepare_v2(DB, checkSQL.c_str(), -1, &checkStmt, nullptr);
        if (exit != SQLITE_OK) {
            std::cerr << "Помилка при перевiрцi таблицi: " << sqlite3_errmsg(DB) << std::endl;
            sqlite3_close(DB);
            return;
        }

        int adminCount = 0;
        if (sqlite3_step(checkStmt) == SQLITE_ROW) {
            adminCount = sqlite3_column_int(checkStmt, 0);
        }
        sqlite3_finalize(checkStmt);

        if (adminCount > 0) {
            std::cout << "Адмiнiстратор вже iснує. Створення нового не дозволено.\n";
            sqlite3_close(DB);
            return;
        }

        std::string encryptedLogin = caesarEncrypt(login, shift);
        std::string encryptedPassword = caesarEncrypt(password, shift);

        std::string insertSQL = "INSERT INTO Admin (LOGIN, PASSWORD) VALUES (?, ?);";
        sqlite3_stmt* stmt;
        exit = sqlite3_prepare_v2(DB, insertSQL.c_str(), -1, &stmt, nullptr);
        if (exit != SQLITE_OK) {
            std::cerr << "Помилка при пiдготовцi запиту: " << sqlite3_errmsg(DB) << std::endl;
            sqlite3_close(DB);
            return;
        }

        sqlite3_bind_text(stmt, 1, encryptedLogin.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 2, encryptedPassword.c_str(), -1, SQLITE_STATIC);

        exit = sqlite3_step(stmt);
        if (exit != SQLITE_DONE) {
            std::cerr << "Помилка при виконаннi запиту: " << sqlite3_errmsg(DB) << std::endl;
        }
        else {
            std::cout << "Адмiнiстратора успiшно додано.\n";
        }

        sqlite3_finalize(stmt);
        sqlite3_close(DB);
    }

    void updateAdminLoginPassword(const std::string& dbName, const std::string& newLogin, const std::string& newPassword, int shift) {
        sqlite3* DB;
        int exit = sqlite3_open(dbName.c_str(), &DB);
        if (exit != SQLITE_OK) {
            std::cerr << "Не вдалося вiдкрити базу даних: " << sqlite3_errmsg(DB) << std::endl;
            sqlite3_close(DB);
            return;
        }
        std::string encryptedLogin = caesarEncrypt(newLogin, shift);
        std::string encryptedPassword = caesarEncrypt(newPassword, shift);
        std::string updateSQL = "UPDATE Admin SET LOGIN = ?, PASSWORD = ? WHERE ID = 1;";
        sqlite3_stmt* stmt;
        exit = sqlite3_prepare_v2(DB, updateSQL.c_str(), -1, &stmt, nullptr);
        if (exit != SQLITE_OK) {
            std::cerr << "Помилка при пiдготовцi запиту: " << sqlite3_errmsg(DB) << std::endl;
            sqlite3_close(DB);
            return;
        }
        sqlite3_bind_text(stmt, 1, encryptedLogin.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 2, encryptedPassword.c_str(), -1, SQLITE_STATIC);
        exit = sqlite3_step(stmt);
        if (exit != SQLITE_DONE) {
            std::cerr << "Помилка при виконаннi запиту: " << sqlite3_errmsg(DB) << std::endl;
        }
        else {
            std::cout << "Данi адмiнiстратора успiшно оновлено.\n";
        }
        sqlite3_finalize(stmt);
        sqlite3_close(DB);
	}

    void addUser(const std::string& dbName, const std::string& login, const std::string& password, const std::string& fullName, const std::string& address, const std::string& phone, int shift) {
        sqlite3* DB;
        int exit = sqlite3_open(dbName.c_str(), &DB);
        if (exit != SQLITE_OK) {
            std::cerr << "Не вдалося вiдкрити базу даних: " << sqlite3_errmsg(DB) << std::endl;
            sqlite3_close(DB);
            return;
        }

        std::string encryptedLogin = caesarEncrypt(login, shift);

        std::string checkSQL = "SELECT COUNT(*) FROM User WHERE LOGIN = ?;";
        sqlite3_stmt* checkStmt;
        exit = sqlite3_prepare_v2(DB, checkSQL.c_str(), -1, &checkStmt, nullptr);
        if (exit != SQLITE_OK) {
            std::cerr << "Помилка при перевiрцi логiна: " << sqlite3_errmsg(DB) << std::endl;
            sqlite3_close(DB);
            return;
        }

        sqlite3_bind_text(checkStmt, 1, encryptedLogin.c_str(), -1, SQLITE_STATIC);
        int userCount = 0;
        if (sqlite3_step(checkStmt) == SQLITE_ROW) {
            userCount = sqlite3_column_int(checkStmt, 0);
        }
        sqlite3_finalize(checkStmt);

        if (userCount > 0) {
            std::cout << "Користувач з таким логiном вже iснує. Реєстрацiя неможлива.\n";
            sqlite3_close(DB);
            return;
        }

        std::string encryptedPassword = caesarEncrypt(password, shift);

        std::string insertSQL = "INSERT INTO User (LOGIN, PASSWORD, FULLNAME, ADDRESS, PHONE) VALUES (?, ?, ?, ?, ?);";
        sqlite3_stmt* stmt;
        exit = sqlite3_prepare_v2(DB, insertSQL.c_str(), -1, &stmt, nullptr);
        if (exit != SQLITE_OK) {
            std::cerr << "Помилка при пiдготовцi запиту: " << sqlite3_errmsg(DB) << std::endl;
            sqlite3_close(DB);
            return;
        }

        sqlite3_bind_text(stmt, 1, encryptedLogin.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 2, encryptedPassword.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 3, fullName.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 4, address.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 5, phone.c_str(), -1, SQLITE_STATIC);

        exit = sqlite3_step(stmt);
        if (exit != SQLITE_DONE) {
            std::cerr << "Помилка при виконаннi запиту: " << sqlite3_errmsg(DB) << std::endl;
        }
        else {
            std::cout << "Користувача успiшно зареєстровано.\n";
        }

        sqlite3_finalize(stmt);
        sqlite3_close(DB);
    }

    void adminAddUser(const std::string& dbName, const std::string& login, const std::string& password, const std::string& fullName, const std::string& address, const std::string& phone, int shift) {
        addUser(dbName, login, password, fullName, address, phone, shift);
	}

    void adminUpdateUser(const std::string& dbName, int userID, const std::string& newLogin, const std::string& newPassword, const std::string& newFullName, const std::string& newAddress, const std::string& newPhone, int shift) {
        sqlite3* DB;
        int exit = sqlite3_open(dbName.c_str(), &DB);
        if (exit != SQLITE_OK) {
            std::cerr << "Не вдалося вiдкрити базу даних: " << sqlite3_errmsg(DB) << std::endl;
            sqlite3_close(DB);
            return;
        }
        std::string encryptedLogin = caesarEncrypt(newLogin, shift);
        std::string encryptedPassword = caesarEncrypt(newPassword, shift);
        std::string updateSQL = "UPDATE User SET LOGIN = ?, PASSWORD = ?, FULLNAME = ?, ADDRESS = ?, PHONE = ? WHERE ID = ?;";
        sqlite3_stmt* stmt;
        exit = sqlite3_prepare_v2(DB, updateSQL.c_str(), -1, &stmt, nullptr);
        if (exit != SQLITE_OK) {
            std::cerr << "Помилка при пiдготовцi запиту: " << sqlite3_errmsg(DB) << std::endl;
            sqlite3_close(DB);
            return;
        }
        sqlite3_bind_text(stmt, 1, encryptedLogin.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 2, encryptedPassword.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 3, newFullName.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 4, newAddress.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 5, newPhone.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_int(stmt, 6, userID);
        exit = sqlite3_step(stmt);
        if (exit != SQLITE_DONE) {
            std::cerr << "Помилка при виконаннi запиту: " << sqlite3_errmsg(DB) << std::endl;
        }
        else {
            std::cout << "Данi користувача успiшно оновлено.\n";
        }
        sqlite3_finalize(stmt);
        sqlite3_close(DB);
	}

    void adminDeleteUser(const std::string& dbName, int userID) {
        sqlite3* DB;
        int exit = sqlite3_open(dbName.c_str(), &DB);
        if (exit != SQLITE_OK) {
            std::cerr << "Не вдалося вiдкрити базу даних: " << sqlite3_errmsg(DB) << std::endl;
            sqlite3_close(DB);
            return;
        }
        std::string deleteSQL = "DELETE FROM User WHERE ID = ?;";
        sqlite3_stmt* stmt;
        exit = sqlite3_prepare_v2(DB, deleteSQL.c_str(), -1, &stmt, nullptr);
        if (exit != SQLITE_OK) {
            std::cerr << "Помилка при пiдготовцi запиту: " << sqlite3_errmsg(DB) << std::endl;
            sqlite3_close(DB);
            return;
        }
        sqlite3_bind_int(stmt, 1, userID);
        exit = sqlite3_step(stmt);
        if (exit != SQLITE_DONE) {
            std::cerr << "Помилка при виконаннi запиту: " << sqlite3_errmsg(DB) << std::endl;
        }
        else {
            std::cout << "Користувача успiшно видалено.\n";
        }
        sqlite3_finalize(stmt);
        sqlite3_close(DB);
    }

    void createTestsTable(const std::string& dbName) {
        setlocale(LC_ALL, "Ukrainian");

        sqlite3* DB;
        int exit = sqlite3_open(dbName.c_str(), &DB);
        if (exit != SQLITE_OK) {
            std::cerr << "Не вдалося створити або вiдкрити базу даних: " << sqlite3_errmsg(DB) << std::endl;
            sqlite3_close(DB);
            return;
        }
        std::string sql = "CREATE TABLE IF NOT EXISTS Tests ("
            "ID INTEGER PRIMARY KEY AUTOINCREMENT, "
            "CATEGORY TEXT NOT NULL, "
            "SUBCATEGORY TEXT NOT NULL, "
            "QUESTION TEXT NOT NULL, "
            "OPTION1 TEXT NOT NULL, "
            "OPTION2 TEXT NOT NULL, "
            "OPTION3 TEXT NOT NULL, "
			"OPTION4 TEXT NOT NULL, "
            "CORRECT_ANSWER INTEGER NOT NULL);";
        char* messageError = nullptr;
        exit = sqlite3_exec(DB, sql.c_str(), nullptr, 0, &messageError);
        if (exit != SQLITE_OK) {
            std::cerr << "Помилка при створеннi таблицi: " << messageError << std::endl;
            sqlite3_free(messageError);
        }
        else {
            std::cout << "Таблицю Tests успiшно створено або вона вже iснує.\n";
        }
        sqlite3_close(DB);
	}

    void adminAddTestQuestion(const std::string& dbName, const std::string& category, const std::string& subCategory, const std::string& question, const std::string& option1, const std::string& option2, const std::string& option3, const std::string& option4, int correctAnswer) {
        setlocale(LC_ALL, "Ukrainian");
        
        sqlite3* DB;
        int exit = sqlite3_open(dbName.c_str(), &DB);
        if (exit != SQLITE_OK) {
            std::cerr << "Не вдалося вiдкрити базу даних: " << sqlite3_errmsg(DB) << std::endl;
            sqlite3_close(DB);
            return;
        }
        std::string insertSQL = "INSERT INTO Tests (CATEGORY, SUBCATEGORY, QUESTION, OPTION1, OPTION2, OPTION3, OPTION4, CORRECT_ANSWER) VALUES (?, ?, ?, ?, ?, ?, ?, ?);";
        sqlite3_stmt* stmt;
        exit = sqlite3_prepare_v2(DB, insertSQL.c_str(), -1, &stmt, nullptr);
        if (exit != SQLITE_OK) {
            std::cerr << "Помилка при пiдготовцi запиту: " << sqlite3_errmsg(DB) << std::endl;
            sqlite3_close(DB);
            return;
        }

        sqlite3_bind_text(stmt, 1, category.c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(stmt, 2, subCategory.c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(stmt, 3, question.c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(stmt, 4, option1.c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(stmt, 5, option2.c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(stmt, 6, option3.c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(stmt, 7, option4.c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_int(stmt, 8, correctAnswer);
        exit = sqlite3_step(stmt);
        if (exit != SQLITE_DONE) {
            std::cerr << "Помилка при виконаннi запиту: " << sqlite3_errmsg(DB) << std::endl;
        }
        else {
            std::cout << "Питання успiшно додано до тестiв.\n";
        } 
		
        sqlite3_finalize(stmt);
        sqlite3_close(DB);
	}

    void addTestToDatabase(const std::string& dbName, const Test& test) {
        setlocale(LC_ALL, "Ukrainian");

        for (const auto& question : test.getQuestions()) {
            adminAddTestQuestion(dbName, test.getCategory(), test.getSubCategory(), question.text, question.options[0], question.options[1], question.options[2], question.options[3], question.correct_answer);
        }
    }

    void createTestResultsTable(const std::string& dbName) {
        sqlite3* DB;
        int exit = sqlite3_open(dbName.c_str(), &DB);
        if (exit != SQLITE_OK) {
            std::cerr << "Не вдалося створити або вiдкрити базу даних: " << sqlite3_errmsg(DB) << std::endl;
            sqlite3_close(DB);
            return;
        }
        std::string sql = "CREATE TABLE IF NOT EXISTS TestResults ("
            "ID INTEGER PRIMARY KEY AUTOINCREMENT, "
            "LOGIN TEXT NOT NULL, "
            "TEST_NAME TEXT NOT NULL, "
            "CORRECT_ANSWERS INTEGER NOT NULL, "
            "SCORE REAL NOT NULL);";
        char* messageError = nullptr;
        exit = sqlite3_exec(DB, sql.c_str(), nullptr, 0, &messageError);
        if (exit != SQLITE_OK) {
            std::cerr << "Помилка при створеннi таблицi: " << messageError << std::endl;
            sqlite3_free(messageError);
        }
        else {
            std::cout << "Таблицю TestResults успiшно створено або вона вже iснує.\n";
        }
        sqlite3_close(DB);
    }

    void adminReadeResults(const std::string& dbName) {
        sqlite3* DB;
        int exit = sqlite3_open(dbName.c_str(), &DB);
        if (exit != SQLITE_OK) {
            std::cerr << "Не вдалося вiдкрити базу даних: " << sqlite3_errmsg(DB) << std::endl;
            sqlite3_close(DB);
            return;
        }
        std::string selectSQL = "SELECT LOGIN, TEST_NAME, CORRECT_ANSWERS, SCORE FROM TestResults;";
        sqlite3_stmt* stmt;
        exit = sqlite3_prepare_v2(DB, selectSQL.c_str(), -1, &stmt, nullptr);
        if (exit != SQLITE_OK) {
            std::cerr << "Помилка при пiдготовцi запиту: " << sqlite3_errmsg(DB) << std::endl;
            sqlite3_close(DB);
            return;
        }
        std::cout << "Результати тестування:\n";
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            std::string login = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
            std::string testName = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
            int correctAnswers = sqlite3_column_int(stmt, 2);
            double score = sqlite3_column_double(stmt, 3);
            std::cout << "Логiн: " << login << ", Назва тесту: " << testName
                << ", Кiлькiсть правильних вiдповiдей: " << correctAnswers
                << ", Оцiнка: " << score << "%\n";
        }
        sqlite3_finalize(stmt);
        sqlite3_close(DB);
	}
}
