/**
 * Token values
 */

#include <iostream>
#include <lex/Lex.hpp>
#include <sstream>

#include "ricc-parser.hpp"

void printErrorMessage(std::string expected, std::string got,
                       bool unexpectedValue = false) {
  std::cerr << "Expected ";
  if (unexpectedValue) {
    std::cerr << "value ";
  }
  std::cerr << expected;
  std::cerr << " got ";
  std::cerr << got;
  std::cerr << std::endl;

  std::cerr << "======================" << std::endl;
  std::cerr << "Test failed" << std::endl;
  std::cerr << "======================" << std::endl;
}

void printSuccessMessage() {
  std::cout << std::endl;
  std::cout << "======================" << std::endl;
  std::cout << "Test passed" << std::endl;
  std::cout << "======================" << std::endl;
}

void printTokenInfo(RICC::Token& token) {
  std::cout << "Token type ";
  std::cout << token.getTokenTypeText();
  if (token.getText().length() > 0) {
    std::cout << " | Token text ";
    std::cout << token.getText();
  }
  std::cout << std::endl;
}

int main() {
  /**
   *  EDIT INPUT PROGRAM HERE
   */
  std::string inputProgram("int i = 10; float fff = 10.5; bool boolVar=true;");
  std::istringstream stream(inputProgram);
  RICC::Lex lex(stream);

  /**
   * EDIT EXPECTED RESULTS HERE
   */
  RICC::Token::tokenType expectedResult[] = {
      RICC::Token::KW_INT,     RICC::Token::IDENTIFIER, RICC::Token::ASSIGNMENT,
      RICC::Token::INTEGER,    RICC::Token::SEMICOLON,  RICC::Token::KW_FLOAT,
      RICC::Token::IDENTIFIER, RICC::Token::ASSIGNMENT, RICC::Token::FLOAT,
      RICC::Token::SEMICOLON,  RICC::Token::KW_BOOL,    RICC::Token::IDENTIFIER,
      RICC::Token::ASSIGNMENT, RICC::Token::BOOL,       RICC::Token::SEMICOLON,
      RICC::Token::END_TOKEN,
  };

  std::map<int, std::string> expectedValues = {
      {1, "i"},    {3, "10"},       {6, "fff"},
      {8, "10.5"}, {11, "boolVar"}, {11, "true"},
  };

  int i = 0;
  while (true) {
    RICC::Token token = lex.getToken();

    if (token.getTokenType() != expectedResult[i]) {
      printErrorMessage(RICC::Token::getTokenTypeByText(expectedResult[i]),
                        token.getTokenTypeText());
      return 1;
    }

    if (expectedValues.find(i) != expectedValues.end()) {
      if (token.getText() != expectedValues.at(i)) {
        printErrorMessage(expectedValues.at(i), token.getText(), true);
        return 1;
      }
    }

    printTokenInfo(token);

    if (token.getTokenType() == RICC::Token::END_TOKEN) {
      break;
    }
    i++;
  };

  printSuccessMessage();
  return 0;
}
