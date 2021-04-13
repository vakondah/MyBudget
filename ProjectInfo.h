// Aliaksandra Hrechka
// CSC 160
// 12/11/2020
//Final Project
// ProjectInfo.h - struct

#pragma once

#include <string>
#include "EstimationType.h"
#include "ProjectPhase.h"

using namespace std;

struct ProjectInfo
{
	string projectID;
	string projectName;
	ProjectPhase pPhase;
	string organization;
	int durationInMonths;
	EstimationType estType;

};

