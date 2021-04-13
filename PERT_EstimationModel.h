// Aliaksandra Hrechka
// CSC 160
// 12/11/2020
//Final Project
// PERT_EstimationModel.h

#pragma once

#include <string>
#include "DocumentEstimationModel.h"

using namespace std;

class PERT_EstimationModel : public DocumentEstimationModel
{
private:
	double total;
	int numberOfActivities;
	
public:
	
	string* activities;
	double** PERT_Table;
	// Getters and setters functions:
	void setNumberOfActivities(int num) { numberOfActivities = num; }
	void setEstimatingParameters(string *acts, double**table);
	// for previous project from the file:
	void setTotal(double ttl) { total = ttl; }

	double getTotal() const { return total; }
	int getNumberOfActivities() const { return numberOfActivities; }

	// operator overriding:
	bool operator> (const PERT_EstimationModel&) const;

	// Member functions:
	void fillActivities(string* p, int size);
	void fillPERT_Table();
	void PrintDocument();
	

	// Constructors
	PERT_EstimationModel();
	PERT_EstimationModel(int id, string author, string date, string acc, EstimationType et);
};

