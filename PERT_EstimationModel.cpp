// Aliaksandra Hrechka
// CSC 160
// 12/11/2020
//Final Project
// PERT_EstimationModel.cpp

#include "PERT_EstimationModel.h"
#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;

// Constructors:
PERT_EstimationModel::PERT_EstimationModel()
{
	//total = 0.0;
}
PERT_EstimationModel::PERT_EstimationModel(int id, string author, string date, string acc, EstimationType et)
	: DocumentEstimationModel(id, author, date, acc, et)
{
	//total = ttl;
}

// Implementations:
void PERT_EstimationModel::fillActivities(string* p, int size)
{
	activities = new string[size];
	for (int i = 0; i < size; i++)
	{
		activities[i] = p[i];
	}
}

void PERT_EstimationModel::fillPERT_Table()
{
	double pessimistic;
	double mostLikely;
	double optimistic;
	double averagePERT;

	// Specifying the number of rows in 2D dynamic array:
	PERT_Table = new double* [numberOfActivities];
	
		for (int i = 0; i < numberOfActivities; i++)
		{	// Creating columns:
			PERT_Table[i] = new double[4];

			cout << "Enter values for activity " << activities[i] << ". " << endl;

			for (int j = 0; j < 4; j++)
			{
				if (j == 0)
				{
					cout << "Pessimistic: ";
					cin >> pessimistic;
					cout << endl;
					PERT_Table[i][j] = pessimistic;
				}
				else if (j == 1)
				{
					cout << "Most likely: ";
					cin >> mostLikely;
					cout << endl;
					PERT_Table[i][j] = mostLikely;
				}
				else if (j == 2)
				{
					cout << "Optimistic: ";
					cin >> optimistic;
					cout << endl;
					PERT_Table[i][j] = optimistic;
				}
				else if (j == 3)
				{
					// column average:
					averagePERT = (pessimistic + optimistic + 4 * mostLikely) / 6.0;
					PERT_Table[i][j] = averagePERT;
				}
			}

			total += averagePERT;
		}

		

	
}

void PERT_EstimationModel::PrintDocument() 
{
	DocumentEstimationModel::PrintDocument();

	cout << endl;
	cout << setw(20) << "PERT ESTIMATION" << endl;
	for (int i = 0; i < 90; i++)
	{
		cout << "*";
	}
	cout << endl;
	
	// Header:
	cout << setw(15) << "Activity" << setw(15) << "Pessimistic" << setw(15) << "Most Likely" << setw(15) << "Optimistic" << setw(15) << "PERT Result" << endl;

	for (int i = 0; i < numberOfActivities; i++)
	{
		cout << setw(15) << activities[i];
		
		for (int j = 0; j < 4; j++)
		{
			cout << fixed << showpoint  << setprecision(2);
			cout << setw(15) << PERT_Table[i][j];
		}
		cout << endl;
	}
	for (int i = 0; i < 90; i++)
	{
		cout << "*";
	}
	cout << setw(60) << "TOTAL: $" << total << endl;

	// Write in file:
	ofstream outData;
	outData.open("result.txt");
	outData << "EstimationID: " << this->getEstimationID() << endl;
	outData << "Prodject Name: " << this->getProjectInfo().projectName << endl;
	outData << "Estimating Type: " << this->getEstimationTypeString() << endl;
	outData << "Author: " << this->getAuthor() << endl;
	outData << "Date: " << this->getDate() << endl;
	outData << "Total: " << this->getTotal() << endl;

	for (int i = 0; i < numberOfActivities; i++)
	{
		outData << activities[i] << ": ";
		for (int j = 0; j < 3; j++)
		{
			outData << PERT_Table[i][j] << " ";
		}
		outData << endl;
	}
	outData << "Total: " << this->getTotal() << endl;

	outData.close();

}

void PERT_EstimationModel::setEstimatingParameters(string* acts, double** table)
{
	for (int i = 0; i < 7; i++)
	{
		
	}
	activities = acts;
	PERT_Table = table;
}

// operator overriding function definition
bool PERT_EstimationModel::operator> (const PERT_EstimationModel& obj) const
{
	return (total > obj.getTotal());
	
}

