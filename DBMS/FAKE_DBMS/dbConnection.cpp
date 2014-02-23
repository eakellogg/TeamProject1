#pragma once

#include "rdbms.h"
#include "parser.h"
#include "fakelexer.h"
#include "dbConnection.h"



using namespace std;
using namespace FAKE_DBMS;

DBConnection::DBConnection()
{
	par.setDatabasePtr(&db);
}

void DBConnection::cmdLineInterface()
{
	

	vector<Token> tokens;
	string command = "";
	cout << "Type a DML command.\nUse 'EXIT' to close." << endl;
	
	//get first command
	cout << "DML-Interface$ ";
	cin >> command;

	//iteratively get, lex, parse, and execute commands on the database
	while(command != "EXIT")
	{
		//fill vector of tokens with lexed command
		tokens = lexInputLine(command);

		//parse command
		par.command(tokens);

		command = "";
		cout << "DML-Interface$ ";
		cin >> command;
		
	}
	
	//commands have been executed on db
	//the parser modifies the actual datbase object stored within the DBConnection class (via a pointer)
	//no updating the db should be necessary
}

void DBConnection::executeCommand(string command)
{

	cout << "About to lex " << command << endl;
	vector<Token> tokens = lexInputLine(command);
	cout << "Finished lexing " << endl;

	cout << "Parsing command " << endl;
	par.command(tokens);
	cout << "Finished parsing command " << endl;
}

Table DBConnection::getTempTable(const string& tableName)
{
	return par.getTempTable(tableName);
}

