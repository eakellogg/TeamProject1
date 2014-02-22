#include "Engine.h"
#include "Table.h"
#include "TokenStream.h"
#include "Parser.h"
#include "Constants.h"
#include "DBMS.h"

using namespace std;

int main()
{
	DBMS dbms;

	bool hasPrisonerFile = true;
	bool hasSentenceFile = true;
	bool hasSentenceRecordFile = true;
	bool hasGuardFile = true;
	bool hasMealGroupFile = true;

	string prisonerFile = "OPEN prisoner;";
	string sentenceFile = "OPEN sentence;";
	string sentenceRecordFile = "OPEN sentenceRecord";
	string guardFile = "OPEN guard";
	string mealGroupFile = "OPEN mealGroup";
 
	dbms.query(prisonerFile);
	Table prisoner = dbms.query("possPrisoner <- select (prisonerID != 0) prisoner");
	if (prisoner.getTableName() == "EmptyTable")
	{
		hasPrisonerFile = false;
		string newPrisoner = "CREATE TABLE prisoner";
		newPrisoner += "(prisonerID INTEGER, firstName VARCHAR(20), lastName VARCHAR(20), birthMonth INTEGER, birthDay INTEGER,";
		newPrisoner += " birthYear INTEGER, cellBlock VARCHAR(1), cellNumber INTEGER, securityLevel INTEGER) PRIMARY KEY(prisonerID); ";
		dbms.query(newPrisoner);
	}

	dbms.query(sentenceFile);
	Table sentence = dbms.query("possSentence <- select (sentenceID != 0) sentence");
	if (sentence.getTableName() == "EmptyTable")
	{
		hasSentenceFile = false;
		string newSentence = "CREATE TABLE sentence";
		newSentence += "(sentenceID INTEGER, sentenceLength INTEGER, startMonth INTEGER, startDay INTEGER, startYear INTEGER,";
		newSentence += " endMonth INTEGER, endDay INTEGER, endYear INTEGER, securityLevel INTEGER) PRIMARY KEY(sentenceID); ";
		dbms.query(newSentence);
	}

	dbms.query(sentenceRecordFile);
	Table sentenceRecord = dbms.query("possSentenceRecord <- select (sentenceID != 0) sentenceRecord");
	if (sentenceRecord.getTableName() == "EmptyTable")
	{
		hasSentenceRecordFile = false;
		string newSentenceRecord = "CREATE TABLE sentenceRecord (prisonerID INTEGER, sentenceID INTEGER) PRIMARY KEY(prisonerID, sentenceID); ";
		dbms.query(newSentenceRecord);
	}

	dbms.query(guardFile);
	Table guard = dbms.query("possGuard <- select (guardID != 0) guard");
	if (guard.getTableName() == "EmptyTable")
	{
		hasGuardFile = false;
		string newGuard = "CREATE TABLE guard (guardID INTEGER, firstName VARCHAR(20), lastName VARCHAR(20), cellBlock VARCHAR(1),";
		newGuard += " cellNumber INTEGER, securityLevel INTEGER) PRIMARY KEY(guardID); ";
		dbms.query(newGuard);
	}

	dbms.query(mealGroupFile);
	Table mealGroup = dbms.query("possMealGroup <- select (mealGroupID != 0) mealGroup");
	if (mealGroup.getTableName() == "EmptyTable")
	{
		hasMealGroupFile = false;
		string newMealGroup = "CREATE TABLE mealGroup (mealGroupID INTEGER, cellBlock VARCHAR(1), breakfastHour INTEGER,";
		newMealGroup += " lunchHour INTEGER, dinnerHour INTEGER) PRIMARY KEY(mealGroupID, cellBlock); ";
		dbms.query(newMealGroup);
	}

	cout << "\n********************\n";
	cout << "WELCOME TO PRISON_MANAGER!";
	cout << "\n********************\n";

	bool goOn = true;
	while (goOn)
	{
		cout << "\n********************\n";
		cout << "Please enter a command, for a list of commands enter HELP.";
		cout << "\n********************\n";

		string command;
		cin >> command;

		if (command == "HELP")
		{
			cout << "\n********************\n";
			cout << "Commands:";
			cout << "\n********************\n";

			//NEED TO DO:
			//continue to summary commands in this format here
			cout << "SAVE" << setw(16) << "" << "Saves any altered data.\n";
			cout << "EXIT" << setw(16) << "" << "Logs out of Prison-Manager.\n";

			cout << "********************\n";
		}

		//NEED TO DO:
		//FILL IN ALL DATA OPTIONS HERE

		else if(command == "SAVE"){
			hasPrisonerFile = true;
			hasSentenceFile = true;
			hasSentenceRecordFile = true;
			hasGuardFile = true;
			hasMealGroupFile = true;

			dbms.query("WRITE prisoner;");
			dbms.query("WRITE sentence;");
			dbms.query("WRITE sentenceRecord;");
			dbms.query("WRITE guard;");
			dbms.query("WRITE mealGroup;");

			cout << "\n********************\n";
			cout << "Saved.";
			cout << "\n********************\n";
		}

		else if (command == "EXIT"){
			goOn = false;
		}

		else
		{
			cout << "\n********************\n";
			cout << "Not a valid command try again, try again.";
			cout << "\n********************\n";
		}
	} 

	cout << "\n********************\nDo you want to save? (Y or N)\n********************\n";
	char ans;
	cin >> ans;
	if (ans == 'Y' || ans == 'y')
	{
		if (hasPrisonerFile){
			dbms.query("CLOSE prisoner;");
		}
		else{
			dbms.query("WRITE prisoner;");
		}
		if (hasSentenceFile){
			dbms.query("CLOSE sentence;");
		}
		else{
			dbms.query("WRITE sentence;");
		}
		if (hasSentenceRecordFile){
			dbms.query("CLOSE sentenceRecord;");
		}
		else{
			dbms.query("WRITE sentenceRecord;");
		}
		if (hasGuardFile){
			dbms.query("CLOSE guard;");
		}
		else{
			dbms.query("WRITE guard;");
		}
		if (hasMealGroupFile){
			dbms.query("CLOSE mealGroup;");
		}
		else{
			dbms.query("WRITE mealGroup;");
		}
	}

	dbms.query("EXIT;");
	cout << "\nLogging Out.";
	return 0;
}