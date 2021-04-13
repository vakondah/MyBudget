// Aliaksandra Hrechka
// CSC 160
// 12/11/2020
//Final Project
// Description: Program contains user login functionality, allows to create estimation of the project 
// budget using PERT and Parametric estimation methods, and compare used  estimation (for PERT only) with 
//existing  project. 

#include <iostream>
#include <fstream>
#include <string>
#include "ProjectManager.h"
#include "ProjectInfo.h"
#include "EstimationType.h"
#include "ProjectPhase.h"
#include "DocumentEstimationModel.h"
#include "PERT_EstimationModel.h"
#include "Parametric_EstimationModel.h"

using namespace std;


// prototypes of the functions:
void readManagersFile(string m[], int size);
bool checkLogin(string uname, string pword, string* &p, int size);
void displayMenu();
void startNewProject(ProjectInfo &pi);
void viewAllProjects();
void displayPhases();
void recommendTypeOfEstimation(ProjectInfo pi);
void displayEstimatingType();
void displayAvailableProjects();


int main()
{
	// Variables declarations:
	string managers[18];
	ProjectManager mngr;
	ProjectManager* m;
	m = &mngr;
	string username, password;
	bool isMatch = false;
	string* p = managers;
	ProjectInfo currentProject;

	
	// Login
	cout << "Welcome to EasyBudget" << endl;
	cout << "Please enter your username: ";
	cin >> username;
	cout << endl;

	cout << "Enter your password: ";
	cin >> password;
	cout << endl;
	
	// Populate managers array from file:
	readManagersFile(managers, 18);

	isMatch = checkLogin(username, password, p, 18);

	while (!isMatch)
	{
		cout << "Your username or password is incorrect. Please try again." << endl;
		cout << "Enter your username: ";
		cin >> username;
		cout << endl;

		cout << "Enter your password: ";
		cin >> password;
		cout << endl;
		isMatch = checkLogin(username, password, p, 18);
	}
	
	// Creating object of the ProjectManager class:
	m->setName(*(p - 4));
	m->setOrganization(*(p - 3));
	m->setEmail(*(p - 2));
	m->setPhone(*(p - 1));

	// Welcome message:
	cout << "Hello, " << mngr.getName() << endl;
	cout << "Choose the options below to continue: " << endl;
	for (int i = 0; i < 40; i++)
	{
		cout << "*";
	}
	cout << endl;

	// Display menue:
	displayMenu();
	for (int i = 0; i < 40; i++)
	{
		cout << "*";
	}
	cout << endl;

	int op;
	cout << "Enter your option: ";
	cin >> op;
	cout << endl;

	// cheking user's option:
	switch (op)
	{
	case 1:
		startNewProject(currentProject);
		break;
	case 2:
		viewAllProjects();
	case 3:
		return 0;
		break;
	default:
		break;
	}

	// Here I am deciding what kind of estimation object create:
	
	if (currentProject.estType == EstimationType::PERT)
	{
		// variables:
		string errorMessage = "The input stream is in the fail state";
		int id;
		string* p;// pointer points to string array
		int size;
		string task;

		//	Assigning esimationID number:
		ifstream inData;

		inData.open("estimationIDt.txt");
		inData >> id;
		inData.close();

		PERT_EstimationModel pert(id, mngr.getName(), "12/12/2020", "HIGH", EstimationType::PERT);
		pert.setProjectInfo(currentProject); 
				
		// creating dynamic array of string type:
		cout << "Enter number of activities: ";
		cin >> size;
		cout << endl;

		p = new string[size];// !!!

		for (int i = 0; i < size; i++)
		{
			cout << "Enter task number " << i + 1 << ": ";
			if (i == 0)
			{
				cin.ignore();
			}
			getline(cin, p[i]);
			cout << endl;
		}

		pert.fillActivities(p, size);
		pert.setNumberOfActivities(size);

		// checking user's input:
		try
		{
			pert.fillPERT_Table();
			if (!cin)
			{
				throw errorMessage;
			}
		}
		catch (string s)
		{
			cout << s;
			return 0;
		}
		// printing document:
		pert.PrintDocument();
		pert.IncreaseEstimationID();

		cout << "Estimating compleated." << endl;
		cout << "Would you like to compare your estimation with the other project? Y or N:" << endl; 
		char choice;
		cin >> choice;
		cout << endl;
		if (choice == 'Y')
		{
			char op;
			displayAvailableProjects();
			cout << "You have only one project available. Would you like to continue? Y or N: ";
			cin >> op;
			cout << endl;

			if (op == 'Y')
			{
				// reading project data from text file:
				int estID, duration;
				EstimationType et;
				string acc, author, pname, org, ph, date, pID;
				string* str;
				double** pn;// declared

				ifstream data;
				data.open("wooden_toys_app.txt");

				data >> estID >> acc >> author >> pname >> org >> date >> pID >> duration;

				// Creating new pert object, new manager, estim type:
				PERT_EstimationModel newPERT;
				ProjectInfo prInfo;
				prInfo.pPhase = ProjectPhase::COMPLETED;
				prInfo.projectID = pID;
				prInfo.projectName = pname;
				prInfo.durationInMonths = duration;
				prInfo.organization = org;
				newPERT.setProjectInfo(prInfo);
				newPERT.setEstimationID(estID);
				newPERT.setAccuracy(acc);
				newPERT.setAuthor(author);
				newPERT.setNumberOfActivities(7);
				newPERT.setDate(date);

				str = new string[7];
				pn = new double* [7];// created
				double total = 0;
				// This loop reads project's values from the file 
				// and estimates the last column:
				for (int i = 0; i < 7; i++)
				{
					double sum = 0;
					pn[i] = new double[4]; // columns created
					data >> str[i];

					for (int j = 0; j < 4; j++)
					{
						if (j == 0 || j == 2)
						{
							data >> pn[i][j];
							sum += pn[i][j];
						}
						else if (j == 1)
						{
							data >> pn[i][j];
							sum += pn[i][j] * 4;
						}
						else
						{
							pn[i][j] = sum / 6;
							total += pn[i][j];
						}
					}
				}

				data.close();
				// adding both arrays to newPert object
				newPERT.setEstimatingParameters(str, pn);
				newPERT.setTotal(total);
				newPERT.PrintDocument();
				delete[] pn;//deleted

				cout << "Comparision result:" << endl;
				// Using overridden > operator:
				if (pert > newPERT)
				{
					cout << pert.getProjectInfo().projectName << " costs more than " << newPERT.getProjectInfo().projectName;
				}
				else
				{
					cout << pert.getProjectInfo().projectName << " costs less than " << newPERT.getProjectInfo().projectName;
				}
			}
			else {
				cout << "Program terminated." << endl;
				return 0;
			}
		}
	}
	else if (currentProject.estType == EstimationType::Parametric)
	{
		double size;
		int id;
		//	Assigning esimationID number:
		ifstream inData;

		inData.open("estimationIDt.txt");
		inData >> id;
		inData.close();

		Parametric_EstimationModel pem(id, mngr.getName(), "02/10/2020", "HIGH", EstimationType::Parametric);
		pem.setProjectInfo(currentProject);

		// taking num of units:
		cout << "Enter number of units: ";
		cin >> size;
		cout << endl;

		pem.setNumberOfUnits(size);
		pem.fillParametric_Table();
		pem.PrintDocument(); 
		pem.IncreaseEstimationID();
	}
	

	return 0;
}

// Implementations:
void readManagersFile(string m[], int size)
{
	ifstream inData;
	inData.open("managers.txt");
	for (int i = 0; i < size; i++)
	{
		getline(inData, m[i]);
	}
	inData.close();
}

void displayMenu()
{
	cout << "EASY BUDGET MENU:" << endl;
	cout << "1. Start new project " << endl;
	cout << "2. View completed projects " << endl;
	cout << "3. Exit program" << endl;
}

void startNewProject(ProjectInfo &pi)
{
	
	int op;

	// Using structure example //

	// TODO: projectID will be generated automatically
	cout << "Enter project name: ";
	cin.ignore();
	getline(cin, pi.projectName);
	cout << endl;

	cout << "Enter organization name: ";
	getline(cin, pi.organization);
	cout << endl;

	cout << "Phases of the project:" << endl;
	displayPhases();
	cout << "Enter the corresponding nuber of the project's phase:";
	cin >> op;
	while (op < 1 || op > 5)
	{
		cout << "Please, choose a valid phase." << endl;
		cout << "Enter the phase of the project:" << endl;
		displayPhases();
		cout << "Enter the corresponding number (from 1 to 5) of the project's phase:";
		cin >> op;
	}

	// checking op:
	switch (op)
	{
	case 1:
		pi.pPhase = ProjectPhase::Initial;
		break;
	case 2:
		pi.pPhase = ProjectPhase::Planning;
		break;
	case 3:
		pi.pPhase = ProjectPhase::Executing;
		break;
	case 4:
		pi.pPhase = ProjectPhase::Monitoring;
		break;
	case 5:
		pi.pPhase = ProjectPhase::Closing;
		break;
	default:
		break;
	}

	cout << "Enter duration of the project in months: ";
	cin >> pi.durationInMonths;
	cout << endl;
	
	// Checking phase and making recommendations:
	recommendTypeOfEstimation(pi);

	// type of the estimation menu:
	displayEstimatingType();
	cout << "Enter the corresponding nuber (1 or 2) of the estimating type:";
	cin >> op;
		
	while (op < 1 || op > 2)
	{
		cout << "Please, choose a valid option from 1 to 2." << endl;
		displayEstimatingType();
		cout << "Enter the corresponding number (1 or 2) of the estimating type:";
		cin >> op;
	}

	// using of enum example //
	switch (op)
	{
	case 1:
		pi.estType = EstimationType::PERT;
		break;
	case 2:
		pi.estType = EstimationType::Parametric;
		break;
	}

}


void viewAllProjects()
{
	int op;
	displayAvailableProjects();
	cout << "Please, enter 1 to see this project details: ";
	cin >> op;

	if (op == 1)
	{
		int estID, duration;
		EstimationType et;
		string acc, author, pname, org, ph, date, pID;
		string* str;
		double** pn;

		ifstream data;
		data.open("wooden_toys_app.txt");

		data >> estID >> acc >> author >> pname >> org >> date >> pID >> duration;

		// Creating new pert object, new manager, estim type:
		PERT_EstimationModel newPERT;
		ProjectInfo prInfo;
		prInfo.pPhase = ProjectPhase::COMPLETED;
		prInfo.projectID = pID;
		prInfo.projectName = pname;
		prInfo.durationInMonths = duration;
		prInfo.organization = org;
		newPERT.setProjectInfo(prInfo);
		newPERT.setEstimationID(estID);
		newPERT.setAccuracy(acc);
		newPERT.setAuthor(author);
		newPERT.setNumberOfActivities(7);
		newPERT.setDate(date);

		str = new string[7];
		pn = new double* [7];
		double total = 0;
		// This loop reads project's values from the file 
		// and estimates the last column:
		for (int i = 0; i < 7; i++)
		{
			double sum = 0;
			pn[i] = new double[4];
			data >> str[i];

			for (int j = 0; j < 4; j++)
			{
				if (j == 0 || j == 2)
				{
					data >> pn[i][j];
					sum += pn[i][j];
				}
				else if (j == 1)
				{
					data >> pn[i][j];
					sum += pn[i][j] * 4;
				}
				else
				{
					pn[i][j] = sum / 6;
					total += pn[i][j];
				}
			}
		}

		data.close();
		// adding both arrays to newPert object
		newPERT.setEstimatingParameters(str, pn);
		newPERT.setTotal(total);
		newPERT.PrintDocument();
	}
	else
	{
		cout << "Wrong input. Please, contact developer." << endl;
		
	}

}

void displayPhases()
{
	cout << "1. Initial" << endl;
	cout << "2. Planning" << endl;
	cout << "3. Execution" << endl;
	cout << "4. Monitoring and control" << endl;
	cout << "5. Closing" << endl;

}

void recommendTypeOfEstimation(ProjectInfo pi)
{
	switch (pi.pPhase)
	{
	case ProjectPhase::Initial:
		cout << "Your project is on the Initial phase. The recommended type of estimating" <<
			"is a simple analogous estimation. Please choose an estimating method below to continue" << endl;
		break;
	case ProjectPhase::Planning:
		cout << "Your project is on the Planning stage. The recommended types of estimating are PERT or Parametric" <<
			" method. Please choose an estimating method below to continue" << endl;
		break;
	case ProjectPhase::Executing:
	case ProjectPhase::Monitoring:
	case ProjectPhase::Closing:
			cout << "Your project budget should be ready by this stage of the project. If you want to make changes"
			<< " to existing project, choose Update Existing Project, or any estimating method below to continue" << endl;
	default:
		break;
	}
}

void displayEstimatingType()
{

	cout << "ESTIMATING TYPES" << endl;
	cout << "Chose the option below: " << endl;
	cout << "1. PERT" << endl;
	cout << "2. Parametric" << endl;
}

void displayAvailableProjects() 
{
	cout << "Available projects: " << endl;
	cout << "1. WOODEN TOYS APP (PERT)" << endl;
}

bool checkLogin(string uname, string pword, string* &p, int size)
{
	for (int i = 0; i < 18; i++)
	{
		if (p[i] == uname && p[i + 1] == pword)
		{
			p = &p[i];
			return true;
		}
	}
	return false;
}



