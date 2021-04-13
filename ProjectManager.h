// Aliaksandra Hrechka
// CSC 160
// 12/11/2020
//Final Project
// ProjectManager.h

#pragma once

#include <string>

using namespace std;

class ProjectManager
{
private:
	string name;
	string organization;
	string email;
	string phone;

public:

	// Getters and setters functions:
	void setName(string n) { name = n; }
	void setOrganization(string org) { organization = org; }
	void setEmail(string e) { email = e; }
	void setPhone(string p) { phone = p; }

	string getName() const { return name; }
	string getOrganization() const { return organization; }
	string getEmail() const { return email; }
	string getPhone() const { return phone; }

};

