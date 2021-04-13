// Aliaksandra Hrechka
// CSC 160
// 12/11/2020
//Final Project
// DocumentEstimationModel.h 

#pragma once

#include <string>
#include "EstimationType.h"
#include "ProjectInfo.h"


using namespace std;

class DocumentEstimationModel
{
private:
	int estimationID;
	string author;
	string date; // TODO: change to day/time type
	string accuracy;
	EstimationType type;
	ProjectInfo projectInfo;

public:
	void setEstimationID(int num) { estimationID = num; }
	void setAuthor(string a) { author = a; }
	void setDate(string d) { date = d; }
	void setAccuracy(string str) { accuracy = str; }
	void setEstimationType(EstimationType t);
	void setProjectInfo(ProjectInfo pt);

	int getEstimationID() const { return estimationID; }
	string getAuthor() const { return author; }
	string getDate() const { return date; }
	string getAccuracy() const { return accuracy; }
	EstimationType getEstimationType() const { return type; }
	ProjectInfo getProjectInfo() const { return projectInfo; }

	string getEstimationTypeString();
	string getProjectPhaseString();
	void IncreaseEstimationID();
	// will be overrided in derived classes:
	void PrintDocument();

	// Constructors
	DocumentEstimationModel();
	DocumentEstimationModel(int id, string author, string date, string acc, EstimationType et);

};



