// Aliaksandra Hrechka
// CSC 160
// 12/11/2020
//Final Project
// Parametric_EstimationModel.h

#pragma once

#include <string>
#include "DocumentEstimationModel.h"

using namespace std;

class Parametric_EstimationModel : public DocumentEstimationModel
{
private:
	string* units;
	double** patametric_table;
	double numOfUnits;
	double total;

public:
	// Getters and setters functions:
	void setNumberOfUnits(double num) { numOfUnits = num; }


	double getTotal() const { return total; }
	int getNumberOfActivities() const { return numOfUnits; }

	// Member functions:
	void fillParametric_Table();
	void PrintDocument();

	// Constructors:
	Parametric_EstimationModel();
	Parametric_EstimationModel(int id, string author, string date, string acc, EstimationType et);
};

