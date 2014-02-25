#include "fakelexer.h"
#include "Token.h"


using namespace std;
using namespace FAKE_DBMS;

bool isNumLiteral(string s){
	for (int i = 0; i < s.size(); i++)
	if (isalpha(s[i]))
		return false;
	return true;
}

//distinguishes a sequence of character between a keyword, numeric literal, and an unknown, then creates appropriate FAKE_DBMS::FAKE_DBMS::Token 
void makeCommVarTok(vector<FAKE_DBMS::Token> & afterRetVecter, string in){
	if (in == "project" || in == "rename" || in == "select" || in == "JOIN" || in == "SHOW" || in == "DELETE" ||
		in == "FROM" || in == "INSERT" || in == "INTO" || in == "UPDATE" || in == "CREATE" || in == "TABLE" ||
		in == "OPEN" || in == "CLOSE" || in == "WRITE" || in == "EXIT" || in == "PRIMARY" || in == "KEY" ||
		in == "VARCHAR" || in == "INTEGER"){
		FAKE_DBMS::Token commandNameTok(FAKE_DBMS::Token::tokenType::KEYWORD);
		commandNameTok.content = in;
		afterRetVecter.push_back(commandNameTok);
	}
	//make sure empty string is not lexed
	else if (in == ""){
		return;
	}
	//and that empty spaces are ignored
	else if (in == " "){
		return;
	}
	else if (isNumLiteral(in)){
		FAKE_DBMS::Token numLiteralTok(FAKE_DBMS::Token::tokenType::LITERAL);
		numLiteralTok.content = in;
		afterRetVecter.push_back(numLiteralTok);
	}
	//check against quotes is to ensure literals do not get lexed twice
	else if (in[0] != '"'){
		FAKE_DBMS::Token tableNameTok(FAKE_DBMS::Token::tokenType::VARIABLE);
		tableNameTok.content = in;
		afterRetVecter.push_back(tableNameTok);
	}
}

//lex the possibly nested protion of a query
vector<FAKE_DBMS::Token> afterAssignQueryLex(string line){
	vector<FAKE_DBMS::Token> afterRetVecter;
	vector<FAKE_DBMS::Token> emptyRetVecter; //this is returned on bad input. The parser then recognizes this. 

	string curString = ""; //contents of FAKE_DBMS::Token accumulate on this
	int stringPos = 0; //current position in string

	while (stringPos <= line.size()){
		char curChar = line[stringPos];


		if (curChar == ' '){
			makeCommVarTok(afterRetVecter, curString);
			curString = "";
		}

		//needed to get the last FAKE_DBMS::Token in the string
		if (stringPos == line.size()){
			//if end of string is paren then curstring might be empty, so this checks for that
			if (curString != ""){
				makeCommVarTok(afterRetVecter, curString);
			}
		}

		//if it is an alphanumeric or _ add it to our surrent string
		else if (isalnum(curChar) || curChar == '_'){
			curString += curChar;
		}

		else if (curChar == '('){
			//if parenthesis are adjacent the curString might be empty, so this checks for that
			if (curString != ""){
				makeCommVarTok(afterRetVecter, curString);
			}
			curString = "";
			FAKE_DBMS::Token parenTok(FAKE_DBMS::Token::tokenType::OPENPAREN);
			parenTok.content = '(';
			afterRetVecter.push_back(parenTok);
		}

		else if (curChar == ')'){
			if (curString != ""){
				makeCommVarTok(afterRetVecter, curString);
			}
			curString = "";
			FAKE_DBMS::Token parenTok(FAKE_DBMS::Token::tokenType::CLOSEPAREN);
			parenTok.content = ')';
			afterRetVecter.push_back(parenTok);
		}

		else if (curChar == ','){
			if (curString != ""){
				makeCommVarTok(afterRetVecter, curString);
			}
			curString = "";
			FAKE_DBMS::Token commaTok(FAKE_DBMS::Token::tokenType::COMMA);
			commaTok.content = ',';
			afterRetVecter.push_back(commaTok);
		}

		else if (curChar == '+'){
			makeCommVarTok(afterRetVecter, curString);
			curString = "";
			FAKE_DBMS::Token plusTok(FAKE_DBMS::Token::tokenType::SYMBOL);
			plusTok.content = '+';
			afterRetVecter.push_back(plusTok);
		}

		else if (curChar == '-'){
			makeCommVarTok(afterRetVecter, curString);
			curString = "";
			FAKE_DBMS::Token minusTok(FAKE_DBMS::Token::tokenType::SYMBOL);
			minusTok.content = '-';
			afterRetVecter.push_back(minusTok);
		}

		else if (curChar == '*'){
			makeCommVarTok(afterRetVecter, curString);
			curString = "";
			FAKE_DBMS::Token prodTok(FAKE_DBMS::Token::tokenType::SYMBOL);
			prodTok.content = '*';
			afterRetVecter.push_back(prodTok);
		}

		else if (curChar == '<'){
			makeCommVarTok(afterRetVecter, curString);
			curString = "";
			//can be < or <=
			if (line[stringPos + 1] == '='){
				FAKE_DBMS::Token lessEqTok(FAKE_DBMS::Token::tokenType::SYMBOL);
				lessEqTok.content = "<=";
				afterRetVecter.push_back(lessEqTok);
			}
			else if (line[stringPos + 1] == ' '){
				FAKE_DBMS::Token lessTok(FAKE_DBMS::Token::tokenType::SYMBOL);
				lessTok.content = "<";
				afterRetVecter.push_back(lessTok);
			}
			else {
				cout << "ERROR when parsing a <" << endl;
				return emptyRetVecter;
			}
			stringPos++; //skip over next char since we have accounted for it
		}

		else if (curChar == '>'){
			makeCommVarTok(afterRetVecter, curString);
			curString = "";
			//can be > or >=
			if (line[stringPos + 1] == '='){
				FAKE_DBMS::Token greatEqTok(FAKE_DBMS::Token::tokenType::SYMBOL);
				greatEqTok.content = ">=";
				afterRetVecter.push_back(greatEqTok);
			}
			else if (line[stringPos + 1] == ' '){
				FAKE_DBMS::Token greatTok(FAKE_DBMS::Token::tokenType::SYMBOL);
				greatTok.content = ">";
				afterRetVecter.push_back(greatTok);
			}
			else {
				cout << "ERROR when parsing a >" << endl;
				return emptyRetVecter;
			}
			stringPos++; //skip over next char since we have accounted for it
		}

		else if (curChar == '!'){
			makeCommVarTok(afterRetVecter, curString);
			curString = "";
			//can be !=
			if (line[stringPos + 1] == '='){
				FAKE_DBMS::Token greatEqTok(FAKE_DBMS::Token::tokenType::SYMBOL);
				greatEqTok.content = "!=";
				afterRetVecter.push_back(greatEqTok);
			}
			else {
				cout << "ERROR when parsing a !" << endl;
				return emptyRetVecter;
			}
			stringPos++; //skip over next char since we have accounted for it
		}

		else if (curChar == '='){
			makeCommVarTok(afterRetVecter, curString);
			curString = "";
			if (line[stringPos + 1] == '='){
				FAKE_DBMS::Token eqTok(FAKE_DBMS::Token::tokenType::SYMBOL);
				eqTok.content = "==";
				afterRetVecter.push_back(eqTok);
				stringPos++; //skip over next char since we have accounted for it
			}
			else if (line[stringPos + 1] != '='){
				FAKE_DBMS::Token setEqTok(FAKE_DBMS::Token::tokenType::SYMBOL);
				setEqTok.content = "=";
				afterRetVecter.push_back(setEqTok);
			}
			else {
				cout << "ERROR when parsing a =" << endl;
				return emptyRetVecter;
			}
		}

		//if it is surrounded by quotes then it is a literal
		else if (curChar == '"'){
			if (isalnum(line[stringPos + 1])){
				int nextQuotePos;
				curString = "";
				nextQuotePos = line.find('\"', stringPos + 1);
				curString = line.substr(stringPos, (nextQuotePos - stringPos) + 1);
				FAKE_DBMS::Token litTok(FAKE_DBMS::Token::tokenType::LITERAL);
				litTok.content = curString;
				afterRetVecter.push_back(litTok);
				stringPos += (nextQuotePos - stringPos); //skip over the rest of FAKE_DBMS::Token
			}
			else {
				stringPos++;
				continue;
			}
		}

		stringPos++;
	}
	return afterRetVecter;
}

//lex queries
vector<FAKE_DBMS::Token> queryLex(string line){
	vector<FAKE_DBMS::Token> retRow;
	vector<FAKE_DBMS::Token> afterAssignRow;

	//trim possible newline characters
	if (line[0] == '\n'){
		line.erase(line.begin());
	}
	if (line[0] == '\n'){
		line.erase(line.begin());
	}

	//name of variable we return to
	FAKE_DBMS::Token varTok(FAKE_DBMS::Token::tokenType::VARIABLE);
	varTok.content = line.substr(0, line.find(' '));
	retRow.push_back(varTok);

	FAKE_DBMS::Token assignTok(FAKE_DBMS::Token::tokenType::SYMBOL);
	assignTok.content = "<-";
	retRow.push_back(assignTok);

	string afterAssign(line);
	afterAssign.erase(0, afterAssign.find("<-") + 3);

	//lex rest of line
	afterAssignRow = afterAssignQueryLex(afterAssign);

	//concatonate the two vectors
	retRow.insert(retRow.end(), afterAssignRow.begin(), afterAssignRow.end());

	return retRow;
}

//lex commands
vector<FAKE_DBMS::Token> commandLex(string line){
	vector<FAKE_DBMS::Token> retRow;

	//trim possible newline characters
	if (line[0] == '\n'){
		line.erase(line.begin());
	}
	if (line[0] == '\n'){
		line.erase(line.begin());
	}

	string curString = ""; //contents of FAKE_DBMS::Token accumulate on this
	int stringPos = 0; //current position in string

	while (stringPos <= line.size()){
		char curChar = line[stringPos];

		//ignore repeated spaces
		if (curChar == ' ' && line[stringPos + 1] != ' '){
			makeCommVarTok(retRow, curString);
			curString = "";
		}

		//needed to get the last FAKE_DBMS::Token in the string
		else if (stringPos == line.size()){
			//if end of string is paren then curstring mught be empty, so this checks for that
			if (curString != "")
				makeCommVarTok(retRow, curString);
		}

		//if it is an alphanumeric or _ add it to our surrent string
		else if (isalnum(curChar) || curChar == '_'){
			curString += curChar;
		}

		//if it is surrounded by quotes then it is a literal
		else if (curChar == '"'){
			if (isalnum(line[stringPos + 1])){
				int nextQuotePos;
				curString = "";
				nextQuotePos = line.find('\"', stringPos + 1);
				curString = line.substr(stringPos, (nextQuotePos - stringPos) + 1);
				FAKE_DBMS::Token litTok(FAKE_DBMS::Token::tokenType::LITERAL);
				litTok.content = curString;
				retRow.push_back(litTok);
				stringPos += (nextQuotePos - stringPos); //skip over the rest of FAKE_DBMS::Token
			}
			else {
				stringPos++;
				continue;
			}
		}

		else if (curChar == '('){
			//if parenthesis are adjacent the curString might be empty, so this checks for that
			if (curString != ""){
				makeCommVarTok(retRow, curString);
			}
			curString = "";
			FAKE_DBMS::Token parenTok(FAKE_DBMS::Token::tokenType::OPENPAREN);
			parenTok.content = '(';
			retRow.push_back(parenTok);
		}

		else if (curChar == ')'){
			if (curString != ""){
				makeCommVarTok(retRow, curString);
			}
			curString = "";
			FAKE_DBMS::Token parenTok(FAKE_DBMS::Token::tokenType::CLOSEPAREN);
			parenTok.content = ')';
			retRow.push_back(parenTok);
		}

		else if (curChar == ','){
			if (curString != ""){
				makeCommVarTok(retRow, curString);
			}
			curString = "";
			FAKE_DBMS::Token commaTok(FAKE_DBMS::Token::tokenType::SYMBOL);
			commaTok.content = ',';
			retRow.push_back(commaTok);
		}

		else if (curChar == '+'){
			makeCommVarTok(retRow, curString);
			curString = "";
			FAKE_DBMS::Token plusTok(FAKE_DBMS::Token::tokenType::SYMBOL);
			plusTok.content = '+';
			retRow.push_back(plusTok);
		}

		else if (curChar == '-'){
			makeCommVarTok(retRow, curString);
			curString = "";
			FAKE_DBMS::Token minusTok(FAKE_DBMS::Token::tokenType::SYMBOL);
			minusTok.content = '-';
			retRow.push_back(minusTok);
		}

		else if (curChar == '*'){
			makeCommVarTok(retRow, curString);
			curString = "";
			FAKE_DBMS::Token prodTok(FAKE_DBMS::Token::tokenType::SYMBOL);
			prodTok.content = '*';
			retRow.push_back(prodTok);
		}

		else if (curChar == '<'){
			makeCommVarTok(retRow, curString);
			curString = "";
			//can be < or <=
			if (line[stringPos + 1] == '='){
				FAKE_DBMS::Token lessEqTok(FAKE_DBMS::Token::tokenType::SYMBOL);
				lessEqTok.content = "<=";
				retRow.push_back(lessEqTok);
			}
			else if (line[stringPos + 1] == ' '){
				FAKE_DBMS::Token lessTok(FAKE_DBMS::Token::tokenType::SYMBOL);
				lessTok.content = "<";
				retRow.push_back(lessTok);
			}
			else {
				cout << "ERROR when parsing a <" << endl;
				break;
			}
			stringPos++; //skip over next char since we have accounted for it
		}

		else if (curChar == '>'){
			makeCommVarTok(retRow, curString);
			curString = "";
			//can be > or >=
			if (line[stringPos + 1] == '='){
				FAKE_DBMS::Token greatEqTok(FAKE_DBMS::Token::tokenType::SYMBOL);
				greatEqTok.content = ">=";
				retRow.push_back(greatEqTok);
			}
			else if (line[stringPos + 1] == ' '){
				FAKE_DBMS::Token greatTok(FAKE_DBMS::Token::tokenType::SYMBOL);
				greatTok.content = ">";
				retRow.push_back(greatTok);
			}
			else {
				cout << "ERROR when parsing a >" << endl;
				break;
			}
			stringPos++; //skip over next char since we have accounted for it
		}

		else if (curChar == '!'){
			makeCommVarTok(retRow, curString);
			curString = "";
			//can be !=
			if (line[stringPos + 1] == '='){
				FAKE_DBMS::Token greatEqTok(FAKE_DBMS::Token::tokenType::SYMBOL);
				greatEqTok.content = "!=";
				retRow.push_back(greatEqTok);
			}
			else {
				cout << "ERROR when parsing a !" << endl;
				break;
			}
			stringPos++; //skip over next char since we have accounted for it
		}

		else if (curChar == '='){
			makeCommVarTok(retRow, curString);
			curString = "";
			if (line[stringPos + 1] == '='){
				FAKE_DBMS::Token eqTok(FAKE_DBMS::Token::tokenType::SYMBOL);
				eqTok.content = "==";
				retRow.push_back(eqTok);
				stringPos++; //skip over next char since we have accounted for it
			}
			else if (line[stringPos + 1] != '='){
				FAKE_DBMS::Token setEqTok(FAKE_DBMS::Token::tokenType::SYMBOL);
				setEqTok.content = "=";
				retRow.push_back(setEqTok);
			}
			else {
				cout << "ERROR when parsing a =" << endl;
				break;
			}
		}


		stringPos++;
	}


	return retRow;
}

//take an input file and lex it
vector<vector<FAKE_DBMS::Token> > lexFile(string fileName){
	string line;
	vector<vector<FAKE_DBMS::Token>> lexedInput;
	int i;
	ifstream inFile(fileName);
	while (getline(inFile, line, ';')) {
		vector<FAKE_DBMS::Token> lexedRow;
		if (line.find("<-") != std::string::npos){
			lexedRow = queryLex(line);
			for (int i = 0; i < lexedRow.size(); i++){
				//cout << "'" << lexedRow[i].content << "' ";
			}
			//cout << endl << endl;
		}
		else{
			lexedRow = commandLex(line);
			for (int i = 0; i < lexedRow.size(); i++){
				//cout << "'" << lexedRow[i].content << "' ";
			}
			//cout << endl << endl;
		}
		lexedInput.push_back(lexedRow);
	}
	return lexedInput;
}

//lex a single command or query
vector<FAKE_DBMS::Token> lexInputLine(string inputLine){
	vector<FAKE_DBMS::Token> lexedInput;

	if (inputLine.find("<-") != std::string::npos){
		lexedInput = queryLex(inputLine);
		for (int i = 0; i < lexedInput.size(); i++){
			//cout << "'" << lexedInput[i].content << "' ";
		}
		//cout << endl << endl;
	}
	else{
		lexedInput = commandLex(inputLine);
		for (int i = 0; i < lexedInput.size(); i++){
			//cout << "'" << lexedInput[i].content << "' ";
		}
		//cout << endl << endl;
	}

	return lexedInput;
}

/*
int main(){
lexFile("parser_milestone_good_inputs.txt");
int n;
cin >> n;
}
*/