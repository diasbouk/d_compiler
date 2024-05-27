#pragma once
#include <iostream>
#include <optional>
#include <ostream>
#include <string>
#include <vector>
#include <sstream>

/* Enum class for token types
it'll hold exit, integer and semicol <;> */
enum class TokenType {
  _exit,
  int_lat,
  semicol,
};

/* Struct of token */
struct Token {
  TokenType type;
  std::optional<std::string> value = {};
};

class Tokenizer {
private:
  const std::string m_src;

public:
  inline Tokenizer(const std::string &src) : m_src(src) {}

  /* isnum - Checks if a string is a number
   * @:s String reference
   * Return: true if it is | false otherwise
   */

  inline bool isnum(const std::string &s) {
    std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it))
      ++it;
    return !s.empty() && it == s.end();
  }

  /* Tokenizer function
   * tokenizer - iterates through the content of source file
   * @content: content to handle
   * Return: ?
   */

  inline std::vector<Token> tokenizer(const std::string &content) {

    /* Declaring some vars needed
     * tokens: List of tokens
     * token: string holding a word each time
     * iss:  string stream of content
     * buffer: lsit holding tokens keywords
     */

    std::vector<Token> tokens;
    std::string token;
    std::istringstream iss(content);
    std::vector<std::string> buffer;

    /* Loop through the contenet to find tokens */
    while (std::getline(iss, token, ' ')) {
      buffer.push_back(token);
    }

    /* if buffer items aren't enough just quit */
    if (buffer.size() != 4) {
      std::cout << "Dumped" << std::endl;
      exit(EXIT_FAILURE);
    } else {
      for (int i = 0; i < buffer.size() - 1; i++) {
        if (buffer.at(i) == "exit")
          tokens.push_back({.type = TokenType::_exit});
        else if (isnum(buffer.at(i)))
          tokens.push_back({.type = TokenType::int_lat, .value = buffer.at(i)});
        else if (buffer.at(i) == ";")
          tokens.push_back({.type = TokenType::semicol});
        /* In case of any syntax issues */
        else {
          std::cout << "Wrong token passed" << std::endl;
        }
      }
    }

    return tokens;
  }
};
