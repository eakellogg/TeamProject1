#include "Engine.h"
#include "Table.h"
#include "TokenStream.h"
#include "Parser.h"
#include "Constants.h"
#include "DBMS.h"


int main()
{  
        bool goOn = true;

        DBMS dbms;

        while (goOn)
        {
                try{
                        cout << "Enter in the query" << endl;

                        string word;
                        cin >> word;
                        string line;
                        if (word == "QUIT")
                        {
                                break;
                        }
                        else
                        {
                                getline(cin, line);
                                line = word + line;
                                cout << line << endl;
                                Table table = dbms.query(line);
                        }

                }
                catch (const char* error) {
                        cout << error << endl;
                }
        }
        return 0;
}
