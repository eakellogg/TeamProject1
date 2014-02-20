#pragma once

#include "dbConnection.h"
#include "Table.h"


	/*
	This class wraps the DBMS provide by another group into a neat litle package that
	endeavers to behave just like our own DBMS
	*/


		class FAKE_DBMS{

		public:
			Table query(std::string query); 
		private:
			FAKE_DBMS::DBConnection  connection;


		};

