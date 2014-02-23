#include "Engine.h"
#include "Table.h"
#include "TokenStream.h"
#include "Parser.h"
#include "Constants.h"
#include "DBMS.h"
#include "FAKE_DBMS.h"

using namespace std;

int main()
{
	//DBMS dbms;
	Fake_DBMS dbms;

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
		newGuard += " securityLevel INTEGER) PRIMARY KEY(guardID); ";
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
		getline(cin, command);

		if (command == "HELP")
		{
			cout << "\n********************\n";
			cout << "Commands:";
			cout << "\n--------------------\n";

			int width = 25;

			//NEED TO DO:
			//continue to summary commands in this format here
			//change all \n to endl ???
			cout << left << setw(width) << "SAVE" << "Saves any altered data.\n";
			cout << left << setw(width) << "EXIT" << "Logs out of Prison-Manager.\n";
			cout << endl;
			cout << left << setw(width) << "ADD PRISONER" << "Adds a new prisoner to the database.\n";	//insert into
			cout << left << setw(width) << "ADD SENTENCE" << "Adds a new sentence.\n";
			cout << left << setw(width) << "ADD SENTENCE RECORD" << "Adds a new sentence record.\n";
			cout << left << setw(width) << "ADD GUARD" << "Adds a new guard.\n";
			cout << left << setw(width) << "ADD MEAL GROUP" << "Adds a new meal group.\n";
			cout << endl;
			cout << left << setw(width) << "UPDATE PRISONER" << "Update a prisoner's record.\n";	//update
			cout << left << setw(width) << "UPDATE GUARD" << "Update a guard's record.\n";
			cout << left << setw(width) << "UPDATE SENTENCE RECORD" << "Update a sentence record.\n";
			cout << left << setw(width) << "UPDATE SENTENCE" << "Update a sentence.\n";
			cout << endl;
			//list prisoners
			//list guards
			cout << left << setw(width) << "LOOK UP PRISONER" << "Search for a prisoner by id #.\n";	//select
			cout << left << setw(width) << "LOOK UP SENTENCE" << "Search for a sentence by id #.\n";
			cout << left << setw(width) << "LOOK UP SENTENCE RECORD" << "Show the sentence record for a prisoner.\n";
			cout << left << setw(width) << "LOOK UP GUARD" << "Search for a guard by id #.\n";
			cout << left << setw(width) << "SHOW MEAL GROUP" << "Shows the details of a meal group.\n";	//will then ask for meal group id
			cout << left << setw(width) << "SHOW SECURITY LEVEL" << "Shows prisoners and guards with a given security level\n";	//select, project, update, rename, and union
			//list sentences of a given security level??? I think it's better with prisoners by security level
			//show all sentences by length ?
			cout << left << setw(width) << "SHOW CELL BLOCK" << "Lists the names of the prisoners in a given cell block.\n";	//project
			cout << endl;
			cout << left << setw(width) << "DELETE PRISONER" << "Deletes the record of a prisoner with the given id #.\n";	//delete
			cout << left << setw(width) << "DELETE SENTENCE" << "Deletes the sentence with the given id #.\n";
			cout << left << setw(width) << "DELETE GUARD" << "Deletes record of the guard with the given id #.\n";
			cout << left << setw(width) << "DELETE MEAL GROUP" << "Deletes a meal group.\n";


			//set difference
			//cross product

			cout << "********************\n";
		}

		//NEED TO DO:
		//FILL IN ALL DATA OPTIONS HERE

		else if (command == "SAVE" || command == "save" || command == "Save"){
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
		else if (command == "EXIT" || command == "exit" || command == "Exit"){
			goOn = false;
		}
		else if (command == "ADD PRISONER") {

		}
		else if (command == "ADD SENTENCE RECORD") {

		}
		else if (command == "ADD SENTENCE") {
			//also add it to sentence record (prisoner id and sentence id)
		}
		else if (command == "ADD GUARD") {

		}
		else if (command == "ADD MEAL GROUP") {

		}
		else if (command == "UPDATE PRISONER") {

		}
		else if (command == "UPDATE GUARD") {

		}
		else if (command == "UPDATE SENTENCE RECORD") {

		}
		else if (command == "SENTENCE") {

		}
		else if (command == "LOOK UP PRISONER") {

		}
		else if (command == "LOOK UP SENTENCE RECORD") {
			//find all entries in sentence record that match the given prisoner id number
			//take the sentence id number from those entries and show all of those sentences (from the sentence table)
		}
		else if (command == "LOOK UP SENTENCE") {

		}
		else if (command == "LOOK UP GUARD") {

		}
		else if (command == "SHOW MEAL GROUP") {

		}
		else if (command == "SHOW SECURITY LEVEL") {

			// prisoners -> project : id, first name, last name, cell block, security level
			//update security level -> 0
			// guards
			//update security level -> 1
			// union of guards and prisoners with the specified security level
			// rename security level (0=prisoner, 1=guard
		}
		else if (command == "SHOW CELL BLOCK") {
			//projection - so for each prisoner show: id, first and last name, cell block, cell number, security level (basically everything except birthday stuff)

		}
		else if (command == "DELETE PRISONER") {
			//delete their corresponding sentences and sentence record
		}
		else if (command == "DELETE SENTENCE") {

		}
		else if (command == "DELETE GUARD") {

		}
		else if (command == "DELETE MEAL GROUP") {

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