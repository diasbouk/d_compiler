#include <cctype>
#include <cstdlib>
#include <fstream>
#include <ios>
#include <iostream>
#include <optional>
#include <ostream>
#include <sstream>
#include <vector>

#include "./main.hpp"


/* string_to_asm - Converts string to assembly code
 * @tooken: Token struct that hold some code (line)
 * Return: A strin (ouput) holding the asm code
 */

std::stringstream tokens_to_asm(std::vector<Token> token) {
  std::stringstream output;

  output << "global _start\n_start:\n";

  if (token.size() == 3) {
    if (token.at(0).type == TokenType::_exit)
      output << "    mov rax, 60\n";
    if (token.at(1).type == TokenType::int_lat)
      output << "    mov rdi, " << token.at(1).value.value() << "\n";
    if (token.at(2).type == TokenType::semicol)
      output << "    syscall";
  }
  return output;
}
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
  std::vector<Token> token;
  std::fstream input(av[1], std::ios::in);
  buffer << input.rdbuf();
  content = buffer.str();
	Tokenizer Tk(std::move(content));

  /* Tokenizing the content of src file */
  token = Tk.tokenizer(content);

  /* Converting token to assembly code */
  std::stringstream asmCode = tokens_to_asm(token);

  /* Moving asm code to file (Hardcoded but we'll fix it later) */
  std::fstream asmFile("./out.asm", std::ios::out);
  asmFile << asmCode.str();

  /* std::cout << asmCode.str() << std::endl; */
  /* Closing the source file after finishing
   * Should I ? I assume not :_|
   * */

  std::cout << av[1] << std::endl;
  return EXIT_SUCCESS;
}
