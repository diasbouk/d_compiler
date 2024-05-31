#include <asm-generic/errno.h>
#include <cctype>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

/* isnum - Checks if a string is a number
 * @:s String reference
 * Return: true if it is | false otherwise
 */

bool isnum(const std::string &s) {
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

std::vector<std::string> tokenizer(const std::string &content) {

  /* Declaring some vars needed
   * tokens: List of tokens
   * token: string holding a word each time
   * iss:  string stream of content
   * buffer: lsit holding tokens keywords
   */

  std::vector<std::string> buffer;
  std::string holder;
  int i = 0;

  /* Loop through the contenet to find tokens */
  /* while (std::getline(iss, token, ' ')) {
    buffer.push_back(token);
  } */
  for (i = 0; i < content.length(); i++) {
    if (isdigit(content.at(i))) {
      holder.push_back(content.at(i));
      while (isdigit(content.at(++i))) {
        holder.push_back(content.at(i));
      }
      i--;
      buffer.push_back(holder);
      holder.clear();

    } else if (isalpha(content.at(i))) {
      holder.push_back(content.at(i));
      while (isalpha(content.at(++i))) {
        holder.push_back(content.at(i));
      }
      i--;
      buffer.push_back(holder);
      holder.clear();
    } else if (content.at(i) == '(') {
      buffer.push_back("(");
    } else if (content.at(i) == ')') {
      buffer.push_back(")");
    } else if (content.at(i) == ';') {
      buffer.push_back(";");
    } else if (isspace(content.at(i))) {
      continue;
    } else {
      std::cout << "Wrong token passed !" << std::endl;
      exit(EXIT_FAILURE);
    }
  }

  /* if buffer items aren't enough just quit */

  for (int i = 0; i < buffer.size(); i++) {
    std::cout << buffer.at(i) << std::endl;
  }

  return buffer;
}

int main(int ac, char **av) {
  std::fstream file(av[1], std::ios::in);
  std::stringstream content;
  std::vector<std::string> tokens;
  content << file.rdbuf();
  std::cout << content.str() << std::endl;
  tokens = tokenizer(content.str());
}
