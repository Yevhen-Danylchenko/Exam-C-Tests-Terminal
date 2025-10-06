#pragma once

#ifndef STRUCTS_H
#define STRUCTS_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

struct Question {
	std::string text;
	std::string options[4];
	int correct_answer;
};

struct Test {
private:
	std::string category;
	std::string sub_category;
	std::vector<Question> questions;
public:
	Test() {}
	Test(std::string category, std::string sub_category, std::vector<Question> questions)
		: category(category), sub_category(sub_category), questions(questions) {
	}

	std::string getCategory() const {
		return category;
	}
	std::string getSubCategory() const {
		return sub_category;
	}
	const std::vector<Question>& getQuestions() const {
		return questions;
	}


	void setCategory(const std::string& category) {
		this->category = category;
	}
	void setSubCategory(const std::string& sub_category) {
		this->sub_category = sub_category;
	}

	void addQuestion(const Question& q) {
		questions.push_back(q);
	}
};

#endif // STRUCTS_H
