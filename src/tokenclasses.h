#pragma once
#include <string>

class Token {
	public:
		int tokn_val;

		Token(int tokn_val) {
			this->tokn_val = tokn_val;
		}

		virtual std::string ts () = 0;
};

class KeywordToken : public Token {
	public:
		KeywordToken(int tokn_val) : Token(tokn_val) {}

		~KeywordToken() {}

		virtual std::string ts() {
			return std::string("KeywordToken: ") + std::to_string(this->tokn_val) + std::string("\n");
		}
};

class NamedToken : public Token {
	public:
		std::string tokn_name;

		NamedToken(int tokn_val, std::string tokn_name) : Token(tokn_val) {
			this->tokn_name = tokn_name;
		}

		virtual ~NamedToken() {}

		virtual std::string ts() {
			return std::string("NamedToken: ") + this->tokn_name + std::string("\n");
		}
};

class StringToken : public Token {
	public:
		std::string value;

		StringToken(int tokn_val, std::string value) : Token(tokn_val) {
			this->value = value;
		}

		virtual ~StringToken() {}

		virtual std::string ts() {
			return std::string("StringToken: ") + this->value + std::string("\n");
		}
};

class CharToken : public Token {
	public:
		char value;

		CharToken(int tokn_val, char& value) : Token(tokn_val) {
			this->value = value;
		}

		virtual ~CharToken() {}

		virtual std::string ts() {
			return std::string("CharToken: ") + this->value + std::string("\n");
		}
};