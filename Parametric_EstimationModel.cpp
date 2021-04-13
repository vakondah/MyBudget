// Aliaksandra Hrechka
// CSC 160
// 12/11/2020
// Final Project
// Parametric_EstimationModel.cpp

#include "Parametric_EstimationModel.h"
#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;


void Parametric_EstimationModel::fillParametric_Table()
{
	double pricePerUnit;
	double unitTotal;
	double numberOfUnits;

	// Specifying the number of rows in 2D dynamic array:
	patametric_table = new double* [numOfUnits];
	units = new string[numOfUnits];

	for (int i = 0; i < numOfUnits; i++)
	{
		cout << "Unit " << (i + 1) << " title : ";
		cin.ignore();
		getline(cin, units[i]);
		cout << endl;
		
		// Creating columns:
		patametric_table[i] = new double[3];

		for (int j = 0; j < 3; j++)
		{
			if (j == 0)
			{
				cout << "Price per unit: ";
				cin >> pricePerUnit;
				cout << endl;
				patametric_table[i][j] = pricePerUnit;
			}
			if (j == 1)
			{
				cout << "Number of units: ";
				cin >> numberOfUnits;
				cout << endl;
				patametric_table[i][j] = numberOfUnits;
			}
			if (j == 2)
			{
				unitTotal = pricePerUnit * numberOfUnits;
				patametric_table[i][j] = unitTotal;
			}
		}
		total += unitTotal;
	}
	cout << "Total parametric: " << total;
}
void Parametric_EstimationModel::PrintDocument()
{
	DocumentEstimationModel::PrintDocument();

	cout << endl;
	cout << setw(50) << "PARAMETRIC ESTIMATION" << endl;
	for (int i = 0; i < 90; i++)
	{
		cout << "*";
	}
	cout << endl;

	// Header:
	cout << setw(10) << "UNIT" << setw(10) << "PRICE" << setw(10) << "NUM" << setw(10) << "TOTAL" << endl;

	for (int i = 0; i < numOfUnits; i++)
	{
		cout << setw(10) << units[i];

		for (int j = 0; j < 3; j++)
		{
			if (j == 1)
			{
				cout << setprecision(0) << setw(10) << patametric_table[i][j];
			}
			else {
				cout << fixed << showpoint << setprecision(2);
				cout << setw(10) << patametric_table[i][j];
			}
			
		}
		cout << endl;
	}
	for (int i = 0; i < 90; i++)
	{
		cout << "*";
	}
	cout << endl;
	cout << setw(50) << "TOTAL: $" << total << endl;

	// Write in file:
	ofstream outData;
	outData.open("result.txt");
	outData << "EstimationID: " << this->getEstimationID() << endl;
	outData << "Prodject Name: " << this->getProjectInfo().projectName << endl;
	outData << "Estimating Type: " << this->getEstimationTypeString() << endl;
	outData << "Author: " << this->getAuthor() << endl;
	outData << "Date: " << this->getDate() << endl;
	
	for (int i = 0; i < numOfUnits; i++)
	{
		outData << units[i] << ": ";
		for (int j = 0; j < 3; j++)
		{
			outData << patametric_table[i][j] << " ";
		}
		outData << endl;
	}
	outData << "Total: " << this->getTotal() << endl;

	outData.close();

}



// Constructors:
Parametric_EstimationModel::Parametric_EstimationModel()
{

}
Parametric_EstimationModel::Parametric_EstimationModel(int id, string author, string date, string acc, EstimationType et)
	:DocumentEstimationModel(id, author, date, acc, et)
{

}
