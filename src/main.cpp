#include <cctype>
#include <cstdlib>
#include <fstream>
#include <ios>
#include <iostream>
#include <optional>
#include <ostream>
#include <sstream>
#include <vector>

#include "./generation.hpp"
#include "./tokenizer.hpp"
#include "parser.hpp"

/* main - Entry point of the programm
 * @ac: Number of positional passed argumenst
 * @av: Array of strings containing arguments
 * Return: As always 0 if it all went good
 * Or any other integer
 */

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
  std::vector<Token> tokens;
  std::fstream input(av[1], std::ios::in);
  buffer << input.rdbuf();
  content = buffer.str();

  /* Tokenizing the content of src file */
  Tokenizer tokenizer(std::move(content));
  tokens = tokenizer.tokenize(content);
  /* Parser to pares the tokens */

  Parser parser(std::move(tokens));
  std::optional<NodeExit> tree = parser.parse();
  if (!tree.has_value()) {
    std::cout << "Parsing failed" << std::endl;
    exit(EXIT_FAILURE);
  }

  Generator generator(tree.value());

  /* Converting token to assembly code */

  /* Moving asm code to file (Hardcoded but we'll fix it later) */
  std::fstream asmFile("./out.asm", std::ios::out);
  asmFile << generator.tokens_to_asm();

  /* std::cout << asmCode.str() << std::endl; */
  /* Closing the source file after finishing
   * Should I ? I assume not :_|
   * */

  std::cout << av[1] << std::endl;
  return EXIT_SUCCESS;
}
