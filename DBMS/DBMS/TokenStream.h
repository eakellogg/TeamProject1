

class Token{
public:
	string getValue();
	string getType();
};
class TokenStream{

public:
	Token getToken();
	void  pushToken(Token t);
};