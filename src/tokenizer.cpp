#include <vector>
#include <istream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <iostream>

#include "tokens.h"
#include "tokenclasses.h"

std::vector<Token*> tokenize(std::istream& input) {
	std::vector<Token*> tokens;
	std::string tempToken;
	bool inString = false;
	char c = 'a';

	while (!input.eof()) {
		input >> c;
		std::cout << c;
		bool switchSuccess = false;

		if (!inString) {
			switchSuccess = true;
			char val;

			switch (c) {
				case ';':
					tokens.push_back(new KeywordToken(EOL));
					break;

				case '+':
					tokens.push_back(new KeywordToken(ADD));
					break;

				case '-':
					tokens.push_back(new KeywordToken(SUB));
					break;

				case '*':
					tokens.push_back(new KeywordToken(MUL));
					break;

				case '/':
					if (input.peek() == '/') {
						while (val != '\n') {
							input >> val;
						}
					}

					else {
						tokens.push_back(new KeywordToken(DIV));
					}

					break;

				case '%':
					tokens.push_back(new KeywordToken(MOD));
					break;

				case '>':
					tokens.push_back(new KeywordToken(GREATER));
					break;

				case '<':
					tokens.push_back(new KeywordToken(LESS));
					break;

				case '=':
					tokens.push_back(new KeywordToken(ASSIGNMENT));
					break;

				case '@':
					tokens.push_back(new KeywordToken(DECORATOR));
					break;

				case '\"':
					if (inString) {
						tokens.push_back(new StringToken(-1, tempToken));
						tempToken = "";
					}

					inString = !inString;
					break;

				case '\'':
					input >> val;

					if (input.peek() != '\'') {
						throw std::exception();
					}

					tokens.push_back(new CharToken(-1, val));
					input >> val;
					break;

				case '(':
					tokens.push_back(new KeywordToken(OPEN_PAREN));
					break;

				case ')':
					tokens.push_back(new KeywordToken(CLOSED_PAREN));
					break;

				case '{':
					tokens.push_back(new KeywordToken(CURLY_OPEN));
					break;

				case '}':
					tokens.push_back(new KeywordToken(CURLY_CLOSED));
					break;

				case '.':
					tokens.push_back(new KeywordToken(METHOD_CALL));
					break;

				case ' ':
					break;

				case '\n':
					break;

				case '\t':
					break;

				default:
					switchSuccess = false;
			}

			if (switchSuccess) {
				if (!(tempToken.compare("") == 0)) {
					tokens.push_back(new NamedToken(-3, tempToken));
					tempToken = "";
				}
			}
		}

		if (!switchSuccess) {
			tempToken += c;

			// Types

			if (tempToken.compare("string") == 0) {
				tokens.push_back(new KeywordToken(T_STRING));
			}

			else if (tempToken.compare("char") == 0) {
				tokens.push_back(new KeywordToken(T_CHAR));
			}

			else if (tempToken.compare("byte") == 0) {
				tokens.push_back(new KeywordToken(T_BYTE));
			}

			else if (tempToken.compare("bool") == 0) {
				tokens.push_back(new KeywordToken(T_BOOL));
			}

			else if (tempToken.compare("null") == 0) {
				tokens.push_back(new KeywordToken(T_NULL));
			}

			else if (tempToken.compare("int") == 0) {
				tokens.push_back(new KeywordToken(T_INT));
			}

			else if (tempToken.compare("int8") == 0) {
				tokens.push_back(new KeywordToken(T_INT8));
			}

			else if (tempToken.compare("int16") == 0) {
				tokens.push_back(new KeywordToken(T_INT16));
			}

			else if (tempToken.compare("int64") == 0) {
				tokens.push_back(new KeywordToken(T_INT64));
			}

			else if (tempToken.compare("unsigned") == 0) {
				tokens.push_back(new KeywordToken(T_UNSIGNED));
			}

			else if (tempToken.compare("float") == 0) {
				tokens.push_back(new KeywordToken(T_FLOAT));
			}

			else if (tempToken.compare("var") == 0) {
				tokens.push_back(new KeywordToken(T_VAR));
			}

			else if (tempToken.compare("class") == 0) {
				tokens.push_back(new KeywordToken(CLASS));
			}

			else if (tempToken.compare("func") == 0) {
				tokens.push_back(new KeywordToken(T_FUNC));
			}

			// Bytes

			else if (tempToken.compare("inv") == 0) {
				tokens.push_back(new KeywordToken(INV));
			}

			else if (tempToken.compare("com") == 0) {
				tokens.push_back(new KeywordToken(COM));
			}

			// Additives

			else if (tempToken.compare("static") == 0) {
				tokens.push_back(new KeywordToken(STATIC));
			}

			else if (tempToken.compare("ref") == 0) {
				tokens.push_back(new KeywordToken(REF));
			}

			else if (tempToken.compare("deref") == 0) {
				tokens.push_back(new KeywordToken(DEREF));
			}

			else if (tempToken.compare("new") == 0) {
				tokens.push_back(new KeywordToken(NEW));
			}

			else if (tempToken.compare("delete") == 0) {
				tokens.push_back(new KeywordToken(DELETE));
			}

			else if (tempToken.compare("final") == 0) {
				tokens.push_back(new KeywordToken(FINAL));
			}

			else if (tempToken.compare("global") == 0) {
				tokens.push_back(new KeywordToken(GLOBAL));
			}

			else if (tempToken.compare("def") == 0) {
				tokens.push_back(new KeywordToken(DEF));
			}

			else if (tempToken.compare("get") == 0) {
				tokens.push_back(new KeywordToken(GET));
			}

			else if (tempToken.compare("set") == 0) {
				tokens.push_back(new KeywordToken(SET));
			}

			else if (tempToken.compare("extends") == 0) {
				tokens.push_back(new KeywordToken(EXTENDS));
			}

			else if (tempToken.compare("self") == 0) {
				tokens.push_back(new KeywordToken(SELF));
			}

			else if (tempToken.compare("super") == 0) {
				tokens.push_back(new KeywordToken(SUPER));
			}

			else if (tempToken.compare("abstract") == 0) {
				tokens.push_back(new KeywordToken(ABSTRACT));
			}

			else if (tempToken.compare("interface") == 0) {
				tokens.push_back(new KeywordToken(INTERFACE));
			}

			else if (tempToken.compare("implements") == 0) {
				tokens.push_back(new KeywordToken(IMPLEMENTS));
			}

			else if (tempToken.compare("return") == 0) {
				tokens.push_back(new KeywordToken(RETURN));
			}

			else if (tempToken.compare("halt") == 0) {
				tokens.push_back(new KeywordToken(HALT));
			}

			// Conditionals

			else if (tempToken.compare("if") == 0) {
				tokens.push_back(new KeywordToken(IF));
			}

			else if (tempToken.compare("else") == 0) {
				tokens.push_back(new KeywordToken(ELSE));
			}

			else if (tempToken.compare("elif") == 0) {
				tokens.push_back(new KeywordToken(ELIF));
			}

			else if (tempToken.compare("and") == 0) {
				tokens.push_back(new KeywordToken(AND));
			}

			else if (tempToken.compare("or") == 0) {
				tokens.push_back(new KeywordToken(OR));
			}

			else if (tempToken.compare("xor") == 0) {
				tokens.push_back(new KeywordToken(XOR));
			}

			else if (tempToken.compare("is") == 0) {
				tokens.push_back(new KeywordToken(IS));
			}

			else if (tempToken.compare("in") == 0) {
				tokens.push_back(new KeywordToken(IN));
			}

			// Loops

			else if (tempToken.compare("for") == 0) {
				tokens.push_back(new KeywordToken(FOR));
			}

			else if (tempToken.compare("while") == 0) {
				tokens.push_back(new KeywordToken(WHILE));
			}

			// Errors

			else if (tempToken.compare("error") == 0) {
				tokens.push_back(new KeywordToken(ERROR));
			}

			else if (tempToken.compare("raise") == 0) {
				tokens.push_back(new KeywordToken(RAISE));
			}

			else if (tempToken.compare("try") == 0) {
				tokens.push_back(new KeywordToken(TRY));
			}

			else if (tempToken.compare("except") == 0) {
				tokens.push_back(new KeywordToken(EXCEPT));
			}

			// Miscellaneous

			else if (tempToken.compare("import") == 0) {
				tokens.push_back(new KeywordToken(IMPORT));
			}

			else if (tempToken.compare("as") == 0) {
				tokens.push_back(new KeywordToken(AS));
			}
		}

		else {
			if (tempToken.compare("") != 0) {
				tokens.push_back(new NamedToken(-1, tempToken));
				tempToken = "";
			}
		}
	}

	tokens.push_back(new KeywordToken(T_EOF));

	return tokens;
}

int main(int argc, char **argv) {
	std::string test =  "class Foo extends Bar {	\
							string foo;				 \
							unsigned int8 zoo;		  \
							int64 boo;				   \
														\
							set zoo(int8 newval) {		 \
								self.zoo += zoo;		  \
								self.zoo++;				   \
							}								\
						}";

	std::stringstream s;
	s << test;
	std::cout << '\n';

	std::vector<Token*> tokens = tokenize(s);

	for (int i = 0; i < tokens.size(); i++) {
		Token *token = tokens.at(i); ///// its a pointer dangit, you cant complain!!!!!!
		std::cout << token->ts();
	}

	for (int i = 0; i < tokens.size(); i++) {
		delete tokens.at(i); ///// its a pointer dangit, you cant complain!!!!!!
	}

	tokens.clear();
}