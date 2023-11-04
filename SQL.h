#pragma once
#include "sqlite3.h"
#include "direct.h"
using namespace std;

sqlite3* db;

void initDatabase()
{	
	char* err;

	//get directory to the user profile
	char* docdir = getenv("USERPROFILE");
	string dir = docdir;
	dir += "\\Documents\\Sudoku";

	//make the folder if not there
	ignore = _mkdir(dir.c_str());
	dir += "\\Best_Times.db";

	//make / open database
	sqlite3_open(dir.c_str(), &db);

	//create tables
	string CreateEasyTable =
		"CREATE TABLE IF NOT EXISTS Easy(Time INT);";
	sqlite3_exec(db, CreateEasyTable.c_str(), NULL, 0, &err);

	string CreateMediumTable =
		"CREATE TABLE IF NOT EXISTS Medium(Time INT);";
	sqlite3_exec(db, CreateMediumTable.c_str(), NULL, 0, &err);

	string CreateHardTable =
		"CREATE TABLE IF NOT EXISTS Hard(Time INT);";
	sqlite3_exec(db, CreateHardTable.c_str(), NULL, 0, &err);
}

void insertData(string Table, string Column, int Val)
{
	char* err;

	stringstream ss;
	ss << Val;
	string Value;
	ss >> Value;

	string sql = "INSERT INTO " + Table + " (" + Column + ") Values(" + "'" + Value + "'" + "); ";

	sqlite3_exec(db, sql.c_str(), NULL, 0, &err);
}

vector<int> times;

int callback(void* NotUsed, int argc, char** argv, char** ColName)
{
	for (int i = 0; i < min(argc, 9); i++)
	{
		times.push_back(stoi(argv[i]));
	}
	return 0;
}

void SelectData(unordered_map<string, vector<int>>& TopTimes)
{
	string Easy = "SELECT * FROM Easy ORDER BY Time;";
	times.clear();
	sqlite3_exec(db, Easy.c_str(), callback, NULL, NULL);
	TopTimes["Easy"] = times;

	string Medium = "SELECT * FROM Medium ORDER BY Time;";
	times.clear();
	sqlite3_exec(db, Medium.c_str(), callback, NULL, NULL);
	TopTimes["Medium"] = times;

	string Hard = "SELECT * FROM Hard ORDER BY Time;";
	times.clear();
	sqlite3_exec(db, Hard.c_str(), callback, NULL, NULL);
	TopTimes["Hard"] = times;
}