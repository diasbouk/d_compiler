#pragma once

#include <iostream>
#include <optional>
#include <ostream>
#include <string>
#include <vector>

/* Enum class for token types
it'll hold exit, integer and semicol <;> */
enum class TokenType {
    _exit,
    int_lat,
    semicol,
    open_par,
    close_par,
};

/* Struct of token */
struct Token {
    TokenType type;
    std::optional<std::string> value = "";
};

class Tokenizer {
    /* Tokenizer class  */
  private:
    const std::string src_code;

  public:
    inline Tokenizer(const std::string &src) : src_code(src) {}

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

    /* Tokenize function
     * tokenizer - iterates through the content of source file
     * @content: content to handle
     * Return: ?
     */

    inline std::vector<Token> tokenize(const std::string &content) {

        /* Declaring some vars needed
         * tokens: List of tokens
         * token: string holding a word each time
         * iss:  string stream of content
         * buffer: lsit holding tokens keywords
         */

        std::vector<Token> tokens;
        std::string holder;
        std::vector<std::string> buffer;
        int i;

        /* Loop through the contenet to find tokens */

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
        /* if (buffer.size() != 3) {
          std::cout << "Dumped" << std::endl;
          exit(EXIT_FAILURE); */
        /* } else { */
        for (int i = 0; i < buffer.size(); i++) {
            if (buffer.at(i) == "exit")
                tokens.push_back({.type = TokenType::_exit});
            else if (isnum(buffer.at(i))) {
                tokens.push_back(
                    {.type = TokenType::int_lat, .value = buffer.at(i)});
            } else if (buffer.at(i)[0] == ';')
                tokens.push_back({.type = TokenType::semicol});
            else if (buffer.at(i)[0] == '(')
                tokens.push_back({.type = TokenType::open_par});
            else if (buffer.at(i)[0] == ')')
                tokens.push_back({.type = TokenType::close_par});
            /* In case of any syntax issues */
            else {
                std::cout << "Wrong token passed ==> " << buffer.at(i)
                          << std::endl;
            }
        }
        /* } */

        return tokens;
    }
};
