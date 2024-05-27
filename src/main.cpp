#include <cctype>
#include <cstdlib>
#include <fstream>
#include <ios>
#include <iostream>
#include <optional>
#include <ostream>
#include <sstream>
#include <vector>

/* Enum class for token types
it'll hold return, integer and semicol <;> */
enum class TokenType {
  _return,
  int_lat,
  semicol,
};

/* Struct of token */
struct Token {
  TokenType type;
  std::optional<std::string> value = {};
};

/* Tokenizer function
 * tokenizer - iterates through the content of source file
 * @content: content to handle
 * Return: ?
 */

std::vector<Token> tokenizer(const std::string &content) {
  std::vector<Token> token;
  std::string buffer;
  for (int i = 0; i < content.length(); i++) {
    char c = content.at(i);
    if (std::isalpha(c)) {
      buffer.push_back(c);
      while (std::isalpha(c)) {
        i++;
        c = content.at(i);
        buffer.push_back(c);
      }
      i--;

      buffer.pop_back();
      if (buffer == "return") {
        token.push_back({.type = TokenType::_return});
        buffer.clear();
        continue;
      } else {
        std::cerr << "Dumped buddy" << std::endl;
        exit(EXIT_FAILURE);
      }
    } else if (isspace(c))
      continue;
    else if (std::isdigit(c)) {
      buffer.push_back(c);
      while (std::isdigit(c)) {
        i++;
        c = content.at(i);
        buffer.push_back(c);
      }
      i--;
      buffer.pop_back();
      token.push_back({.type = TokenType::int_lat, .value = buffer});
      buffer.clear();
      continue;

    } else if (c == ';') {
      token.push_back({
          .type = TokenType::semicol,
      });
    } else {
      std::cerr << "Dumped buddy" << std::endl;
      exit(EXIT_FAILURE);
    }
  }
  std::cout << buffer << std::endl;
  return token;
}

int main(int ac, char **av) {

  /* Cheking if the source file exists
  if not an error is raised */

  if (ac != 2) {
    std::cerr << "Wrong num of arguments :" << std::endl;
    std::cerr << "Usage: dias <file_name.ds>" << std::endl;
    exit(EXIT_FAILURE);
  }

  /* Declaring a string to hold the file content
      content is read with fstream input rdbuf function
      reads the whole file content */

  std::string content;
  std::stringstream buffer;
  std::vector<Token> token;
  std::fstream input(av[1], std::ios::in);
  buffer << input.rdbuf();
  content = buffer.str();

  token = tokenizer(content);

  for (int i = 0; i < token.size(); i++) {
    if (token.at(i).type == TokenType::_return)
      std::cout << "Return keyword found" << std::endl;
    if (token.at(i).type == TokenType::int_lat) {
      std::cout << "Integer value keyword found" << std::endl;
    }
    if (token.at(i).type == TokenType::semicol)
      std::cout << "semicol keyword found" << std::endl;
  }
  /* std::cout << content << std::endl; */
  /* Closing the source file after finishing */

  std::cout << av[1] << std::endl;
  return EXIT_SUCCESS;
}
