//Important to note that security level is an int, cell block is a char

#include "Engine.h"
#include "Table.h"
#include "TokenStream.h"
#include "Parser.h"
#include "Constants.h"
#include "DBMS.h"
#include "FAKE_DBMS.h"
#include <sstream>

using namespace std;

int main()
{
	DBMS dbms;

	//Fake_DBMS dbms;

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
		newPrisoner += "(prisonerID INTEGER, firstName VARCHAR(20), lastName VARCHAR(20), age INTEGER, birthMonth INTEGER, birthDay INTEGER,";
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


		cin.clear();
		string command;
		getline (cin, command);

		if (command == "")
		{
			getline(cin, command);
		}

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
			cout << left << setw(width) << "LIST PRISONERS" << "Prints the records for all prisoners.\n";
			cout << left << setw(width) << "LIST GUARDS" << "Prints the records for all guards.\n";
			cout << left << setw(width) << "LIST MEAL GROUPS" << "Prints all of the meal groups.\n";
			cout << endl;
			cout << left << setw(width) << "ADD PRISONER" << "Adds a new prisoner to the database.\n";								//insert into
			cout << left << setw(width) << "ADD SENTENCE" << "Adds a new sentence.\n";
			cout << left << setw(width) << "ADD GUARD" << "Adds a new guard.\n";
			cout << left << setw(width) << "ADD MEAL GROUP" << "Adds a new meal group.\n";
			cout << endl;
			cout << left << setw(width) << "UPDATE PRISONER" << "Update a prisoner's record.\n";									//update
			cout << left << setw(width) << "UPDATE GUARD" << "Update a guard's record.\n";
			cout << left << setw(width) << "UPDATE MEAL GROUP" << "Update a meal group.\n";
			cout << endl;
			cout << left << setw(width) << "LOOK UP PRISONER" << "Search for a prisoner by id #.\n";								//select
			cout << left << setw(width) << "LOOK UP SENTENCE" << "Search for a sentence by id #.\n";
			cout << left << setw(width) << "LOOK UP GUARD" << "Search for a guard by id #.\n";
			cout << left << setw(width) << "LOOK UP MINORS" << "Search for prisoners under 18 in a cell block.\n";
			cout << left << setw(width) << "LOOK UP ESCORTS" << "Search for possible prisoner-guard combinations.\n";
			cout << endl;
			cout << left << setw(width) << "SHOW SENTENCE RECORD" << "Shows all of a prisoner's sentences.\n";						//uses all the things....
			cout << left << setw(width) << "SHOW MEAL GROUP" << "Shows the details of a meal group.\n";	
			cout << left << setw(width) << "SHOW SECURITY LEVEL" << "Shows prisoners and guards with a given security level\n";	//maybe have guards of that or higher?
			//show all sentences by length ?
			cout << left << setw(width) << "SHOW CELL BLOCK" << "Lists the names of the prisoners in a given cell block\n";		//project		//DOESNT WORK!!! TODO TO DO
			cout << endl;
			cout << left << setw(width) << "DELETE PRISONER" << "Deletes the record of a prisoner with the given id #.\n";			//delete	//not done
			cout << left << setw(width) << "DELETE SENTENCE" << "Deletes the sentence with the given id #.\n";
			cout << left << setw(width) << "DELETE GUARD" << "Deletes record of the guard with the given id #.\n";
			cout << left << setw(width) << "DELETE MEAL GROUP" << "Deletes a meal group.\n";

			cout << "********************\n";
		}


		else if (command == "SAVE"){
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
		else if (command == "LIST PRISONERS") {
			dbms.query("SHOW prisoner;");
		}
		else if (command == "LIST GUARDS") {
			dbms.query("SHOW guard;");
		}
		else if (command == "LIST MEAL GROUPS") {
			dbms.query("SHOW mealGroup;");
		}
		else if (command == "ADD PRISONER") {
			string pid;
			string fname;
			string lname;
			string age;
			string month;
			string day;
			string year;
			string block;
			string cell;
			string security;
			cout << "\nEnter the prisoner's first and last name (separated by a space)" << endl;
			cin >> fname >> lname;
			cout << "Enter the prisoner's ID number:" << endl;
			cin >> pid;
			cout << "Enter the prisoner's age:" << endl;
			cin >> age;
			cout << "Enter the prisoner's birthday in the following format: MM DD YYYY" << endl;
			cin >> month >> day >> year;
			cout << "Enter the prisoner's cell block and number (separated by a space)" << endl;
			cin >> block >> cell;
			cout << "Enter the prisoner's security level:" << endl;
			cin >> security;
			string addPrisoner = "INSERT INTO prisoner VALUES FROM (" + pid + ", \"" + fname +
				"\", \"" + lname + "\", " + age + ", " + month + ", " + day + ", " + year + ", \"" + block +
				"\", " + cell + ", " + security + ");";
			dbms.query(addPrisoner);
		}
		else if (command == "ADD SENTENCE") {
			//also adds it to sentence record (prisoner id and sentence id)
			string prisonerId;
			string sentenceId;
			string length;
			string startMonth;
			string startDay;
			string startYear;
			string endMonth;
			string endDay;
			string endYear;
			string security;
			cout << "\nEnter the prisoner's ID number:" << endl;
			cin >> prisonerId;
			cout << "Enter the sentence ID number:" << endl;
			cin >> sentenceId;
			cout << "Enter the length of the sentence (in days)" << endl;
			cin >> length;
			cout << "Enter the starting date of the sentence in the following format: MM DD YYYY" << endl;
			cin >> startMonth >> startDay >> startYear;
			cout << "Enter the ending date of the sentence in the same format" << endl;
			cin >> endMonth >> endDay >> endYear;
			cout << "Enter the security level associated with the sentence" << endl;
			cin >> security;
			string addRecord = "INSERT INTO sentenceRecord VALUES FROM (" + prisonerId + ", " +
				sentenceId + ");";
			dbms.query(addRecord);
			string addSentence = "INSERT INTO sentence VALUES FROM (" + sentenceId + ", " + length + ", " +
				startMonth + ", " + startDay + ", " + startYear + ", " + endMonth + ", " +
				endDay + ", " + endYear + ", " + security + ");";
			dbms.query(addSentence);
		}
		else if (command == "ADD GUARD") {
			string guardId;
			string fname;
			string lname;
			string cellBlock;
			string security;
			cout << "\nEnter the guard's first and last name (separated by a space)" << endl;
			cin >> fname >> lname;
			cout << "Enter the guard's ID number:" << endl;
			cin >> guardId;
			cout << "Enter the guard's cell block:" << endl;
			cin >> cellBlock;
			cout << "Enter the guard's maximum security level:" << endl;
			cin >> security;
			string addGuard = "INSERT INTO guard VALUES FROM (" + guardId + ", \"" + fname + "\", \"" + 
				lname + "\", \"" + cellBlock + "\", " + security + ");";
			dbms.query(addGuard);
		}
		else if (command == "ADD MEAL GROUP") {
			string mealgroupId;
			string cellBlock;
			string breakfastHour;
			string lunchHour;
			string dinnerHour;
			cout << "\nEnter the meal group's ID number:" << endl;
			cin >> mealgroupId;
			cout << "Enter the corresponding cell block:" << endl;
			cin >> cellBlock;
			cout << "Enter the meal group's designated breakfast hour:" << endl;
			cin >> breakfastHour;
			cout << "Enter the meal group's designated lunch hour:" << endl;
			cin >> lunchHour;
			cout << "Enter the meal group's designated dinner hour:" << endl;
			cin >> dinnerHour;
			string addMealGroup = "INSERT INTO mealGroup VALUES FROM (" + mealgroupId + ", \"" +
				cellBlock + "\", " + breakfastHour + ", " + lunchHour + ", " + dinnerHour + ");";
			dbms.query(addMealGroup);
		}
		else if (command == "UPDATE PRISONER") {
			cout << "\nWhat is the ID of the prisoner?" << endl;

			string ID;
			cin >> ID;

			cout << "Would you like to change their 'CellBlock', 'CellNumber', or 'SecurityLevel'?" << endl;

			string subCommand;
			cin >> subCommand;

			if (subCommand == "CellBlock"){
				cout << "What would you like to change their cell block to? (One Letter)" << endl;

				string block;
				cin >> block;

				string updateBlock = "UPDATE prisoner SET cellBlock = \"" + block + "\" WHERE prisonerID == " + ID + ";";
				dbms.query(updateBlock);
			}
			else if (subCommand == "CellNumber"){
				cout << "What would you like to change their cell number to? (Integer)" << endl;

				string cellNum;
				cin >> cellNum;

				string updateCell = "UPDATE prisoner SET cellNumber = " + cellNum + " WHERE prisonerID == " + ID + ";";
				dbms.query(updateCell);
			}
			else if (subCommand == "SecurityLevel"){
				cout << "What would you like to change their security level to? (Integer)" << endl;

				string securLevel;
				cin >> securLevel;

				string updateSecurity = "UPDATE prisoner SET securityLevel = " + securLevel + " WHERE prisonerID == " + ID + ";";
				dbms.query(updateSecurity);
			}
			else{
				cout << "\n********************\n";
				cout << "That was not a valid option.";
				cout << "\n********************\n";
			}
		}
		else if (command == "UPDATE GUARD") { 
			cout << "\nWhat is the ID of the guard?" << endl;

			string ID; 
			cin >> ID; 

			cout << "Would you like to change their 'CellBlock' or 'SecurityLevel'?" << endl;

			string subCommand; 
			cin >> subCommand; 

			if (subCommand == "CellBlock"){ 
				cout << "What would you like to change their cell block to? (One Letter)" << endl;

				string block; 
				cin >> block; 

				string updateBlock = "UPDATE guard SET cellBlock = \"" + block + "\" WHERE guardID == " + ID + ";"; 
				dbms.query(updateBlock); 
			} 
			else if (subCommand == "SecurityLevel"){ 

				string securLevel; 
				cin >> securLevel; 
				string updateSecurity = "UPDATE guard SET securityLevel = " + securLevel + " WHERE guardID == " + ID + ";"; 
				dbms.query(updateSecurity); 
			} 
			else{ 
				cout << "\n********************\n"; 
				cout << "That was not a valid option.";
				cout << "\n********************\n";
			}
		}
		else if (command == "UPDATE MEAL GROUP") { 
			cout << "\nWhat is the ID of the meal group?" << endl;

			string ID; 
			cin >> ID; 
 
			cout << "Which cell block for the meal group?" << endl;

			string block; 
			cin >> block; 

			cout << "Would you like to change their 'BreakfastHour', 'LunchHour', or 'DinnerHour'?" << endl;

			string subCommand; 
			cin >> subCommand; 

			if (subCommand == "BreakfastHour"){ 
				cout << "What would you like to change their breakfast hour to? (Integer)" << endl;

				string breakfast; 
				cin >> breakfast; 

				string updateBreakfast = "UPDATE mealGroup SET breakfastHour = " + breakfast + " WHERE mealGroupID == " + ID + " && cellBlock == \"" + block + "\";";
				dbms.query(updateBreakfast); 
			} 
			else if (subCommand == "LunchHour"){ 

				string lunch; 
				cin >> lunch; 

				string updateLunch = "UPDATE mealGroup SET lunchHour = " + lunch + " WHERE mealGroupID == " + ID + " && cellBlock == \"" + block + "\";";
				dbms.query(updateLunch); 
			} 
			else if (subCommand == "DinnerHour"){ 
				cout << "What would you like to change their dinner hour to? (Integer)" << endl;

				string dinner; 
				cin >> dinner; 

				string updateDinner = "UPDATE mealGroup SET dinnerHour = " + dinner + " WHERE mealGroupID == " + ID + " && cellBlock == \"" + block + "\";";
				dbms.query(updateDinner); 
			} 
			else{ 
				cout << "\n********************\n"; 
				cout << "That was not a valid option."; 
				cout << "\n********************\n"; 
			} 
		}
		else if (command == "LOOK UP PRISONER") {
			string prisonerId;
			cout << "\nEnter the prisoner's ID number:" << endl;
			cin >> prisonerId;
			string selectPrisoner = "specific_prisoner <- select (prisonerID == " + prisonerId +
				") prisoner;";
			dbms.query(selectPrisoner);
			dbms.query("SHOW specific_prisoner;");
		}
		else if (command == "SHOW SENTENCE RECORD") {
			//find all entries in sentence record that match the given prisoner id number
			//take the sentence id number from those entries and show all of those sentences (from the sentence table)
			string prisonerId;
			cout << "\nEnter the prisoner's ID number:" << endl;
			cin >> prisonerId;
			string first_query = "prisoners_sentences <- rename (prisoner, sID) (select (prisonerID == " + 
				prisonerId + ") sentenceRecord);";
			string second_query = "all_sentences <- prisoners_sentences * sentence;";
			string third_query = "desired_sentences <- select (sID == sentenceID) all_sentences;";
			string fourth_query = "sentences_for_" + prisonerId + " <- project (sentenceID, sentenceLength," +
				" startMonth, startDay, startYear, endMonth, endDay, endYear, securityLevel) desired_sentences;";
			string final_query = "SHOW sentences_for_" + prisonerId + ";";
			dbms.query(first_query);
			dbms.query(second_query);
			dbms.query(third_query);
			dbms.query(fourth_query);
			dbms.query(final_query);
		}
		else if (command == "LOOK UP SENTENCE") {
			string sentenceId;
			cout << "\nEnter the sentece ID number:" << endl;
			cin >> sentenceId;
			string selectSentence = "specific_sentence <- select (sentenceID == " + sentenceId +
				") sentence;";
			dbms.query(selectSentence);
			dbms.query("SHOW specific_sentence;");
		}
		else if (command == "LOOK UP GUARD") {
			string guardId;
			cout << "\nEnter the guard's ID number:" << endl;
			cin >> guardId;
			string selectGuard = "specific_guard <- select (guardID == " + guardId + ") guard;";
			dbms.query(selectGuard);
			dbms.query("SHOW specific_guard;");
		}
		else if (command == "LOOK UP MINORS") {
			cout << "\nList the minors for which cell block?" << endl;

			string block;
			cin >> block;

			string escortQuery = "minor <- (select (cellBlock == \"" + block + "\") prisoner) - (select (age >= 18) prisoner);";
			dbms.query(escortQuery);
			string showCommand = "SHOW minor"; 
			dbms.query(showCommand); 
		}
		else if (command == "LOOK UP ESCORTS"){ 
			cout << "\nList possible escort pairings for which cell block?" << endl;

			string block; 
			cin >> block; 

			string escortQuery = "escort" + block + " <- (select (cellBlock == \"" + block + "\") prisoner) * (select (cellBlock == \"" + block + "\") guard);"; 
			dbms.query(escortQuery); 
			string showCommand = "SHOW escort"; 
			dbms.query(showCommand); 
		} 
		else if (command == "SHOW MEAL GROUP") {
			string mealGroupId;
			cout << "\nEnter the meal group ID number:" << endl;
			cin >> mealGroupId;
			string selectMealGroup = "specific_meal_group <- select (mealGroupID == " + 
				mealGroupId + ") mealGroup;";
			dbms.query(selectMealGroup);
			dbms.query("SHOW specific_meal_group;");
		}
		else if (command == "SHOW SECURITY LEVEL") {
			//make names better, shorten lines of code
			string security;
			cout << "\nEnter the security level:" << endl;
			cin >> security;

			string selectPrisoners = "selected_prisoner <- select (securityLevel == " + security + ") prisoner;";
			string selectGuards = "secure_guard <- select (securityLevel >= " + security + ") guard;";
			string shortenedPrisoners = "secure_prisoner <- project (prisonerID, firstName, lastName, cellBlock, securityLevel) selected_prisoner;";
			string updatedPrisoners = "UPADATE secure_prisoner SET securityLevel = 0 where securityLevel != 0;";
			string updatedGuards = "UPDATE secure_guard SET securityLevel = 1 where securityLevel != 1;";
			string prisonersAndGuards = "total_security_level <- secure_guard + secure_prisoner;";
			string allSecurityLevel = "security_level <- rename (ID, firstName, lastName, cellBlock, isGuard) total_security_level;";

			dbms.query(selectPrisoners);
			dbms.query(selectGuards);
			dbms.query(shortenedPrisoners);
			dbms.query(updatedPrisoners);
			dbms.query(updatedGuards);
			dbms.query(prisonersAndGuards);
			dbms.query(allSecurityLevel);
			dbms.query("SHOW security_level;");

			// select prisoners with that security level and guards with (at least??) that security level
			// prisoners -> project : id, first name, last name, cell block, security level
				//update security level -> 0
			// guards
				//update security level -> 1																		
			// union of guards and prisoners with the specified security level
			// rename security level (0=prisoner, 1=guard
		}
		else if (command == "SHOW CELL BLOCK") {
			//projection - so for each prisoner show: id, first and last name, cell number, security level (basically everything except birthday stuff and cell block)
			string block;
			cout << "\nEnter the cell block:" << endl;
			cin >> block;
			string selectCellBlock = "specific_cell_block <- select (cellBlock == \"" + block + 
				"\") prisoner;";
			string specificCellBlock = "cell_block <- project (prisonerID, firstName, lastName, cellBlock, cellNumber, securityLevel) specific_cell_block;";
			dbms.query(selectCellBlock);
			dbms.query(specificCellBlock);
			dbms.query("SHOW cell_block;");
		}
		else if (command == "DELETE PRISONER") {
			//delete their corresponding sentences and sentence record
			string prisonerId;
			cout << "\nEnter the prisoner's ID number:" << endl;
			cin >> prisonerId;
			string deletePrisoner = "DELETE FROM prisoner WHERE (prisonerID == " + prisonerId + ");";
			dbms.query(deletePrisoner);
			//delete sentences and records																				//NOT DONE --------   TODO TO DO
		}
		else if (command == "DELETE SENTENCE") {
			string sentenceId;
			cout << "\nEnter the sentence ID number:" << endl;
			cin >> sentenceId;
			string deleteSentence = "DELETE FROM sentence WHERE (sentenceID == " + sentenceId + ");";
			dbms.query(deleteSentence);
		}
		else if (command == "DELETE GUARD") {
			string guardId;
			cout << "\nEnter the guards's ID number:" << endl;
			cin >> guardId;
			string deleteGuard = "DELETE FROM guard WHERE (guardID == " + guardId + ");";
			dbms.query(deleteGuard);
		}
		else if (command == "DELETE MEAL GROUP") {
			string mealGroupId;
			cout << "\nEnter the meal group ID number:" << endl;
			cin >> mealGroupId;
			string deleteMealGroup = "DELETE FROM mealGroup WHERE (mealGroupID == " + mealGroupId + ");";
			dbms.query(deleteMealGroup);
		}
		else
		{
			cout << "\n********************\n";
			cout << "Not a valid command, try again.";
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