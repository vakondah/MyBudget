// Aliaksandra Hrechka
// CSC 160
// 12/11/2020
// Final Project
// DocumentEstimationModel.cpp

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include "DocumentEstimationModel.h"
#include "ProjectInfo.h"

using namespace std;

//TODO: do I need to include EstimationType.h?

void DocumentEstimationModel::setEstimationType(EstimationType t)
{

}
void DocumentEstimationModel::setProjectInfo(ProjectInfo pt)
{
	projectInfo = pt;
}

string DocumentEstimationModel::getEstimationTypeString()
{
	switch (type)
	{
	case EstimationType::PERT:
		return "PERT Estimation";
		break;
	case EstimationType::Avg3Point:
		return "3 Point Average Estimation";
		break;
	case EstimationType::Analogous:
		return "Analogous Estimation";
		break;
	case EstimationType::Parametric:
		return "Parametric Estimation";
		break;
	default:
		break;
	}
}

string DocumentEstimationModel::getProjectPhaseString()
{

	switch (projectInfo.pPhase)
	{
	case ProjectPhase::Initial:
		return "Initial";
		break;
	case ProjectPhase::Planning:
		return "Planning";
		break;
	case ProjectPhase::Executing:
		return "Executing";
		break;
	case ProjectPhase::Monitoring:
		return "Monitoring and Control";
		break;
	case ProjectPhase::Closing:
		return "Closing";
		break;
	case ProjectPhase::COMPLETED:
		return "COMPLETED";
		break;
	}
}


void DocumentEstimationModel::PrintDocument()
{
	// Header
	cout << endl;
	cout << setw(50);
	cout << "BUDGET ESTIMATION DOCUMENT" << endl;

	for (int i = 0; i < 90; i++)
	{
		cout << "*";
	}
	cout << endl;

	// Project and estimation info lines:
	cout << setw(20) << "Estimation ID: " << setw(20) << estimationID << setw(20) << "Project: " << setw(20) << projectInfo.projectName << endl;
	cout << setw(20) << "Estimation type: " << setw(20) << getProjectPhaseString() << setw(20) << "Organization: " << setw(20) << projectInfo.organization << endl;
	cout << setw(20) << "Accuracy: " << setw(20) << accuracy << setw(20) << "Project phase: " << setw(20) << getProjectPhaseString() << endl;
	cout << setw(20) << "Estimated by: " << setw(20) << author << setw(20) << "Date: " << setw(20) << date << endl;
	for (int i = 0; i < 90; i++)
	{
		cout << "*";
	}
	cout << endl;


}


// Constructors
DocumentEstimationModel::DocumentEstimationModel()
{

}
DocumentEstimationModel::DocumentEstimationModel(int id, string author, string date, string acc, EstimationType et)
{
	estimationID = id;
	this->author = author;
	this->date = date;
	acc = accuracy;
	type = et;
}

void DocumentEstimationModel::IncreaseEstimationID()
{
	estimationID += 6;
	ofstream outData;
	outData.open("estimationIDt.txt");
	outData << estimationID;
	outData.close();

}

