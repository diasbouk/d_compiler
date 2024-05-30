#include "./parser.hpp"
#include "tokenizer.hpp"

class Generator {
public:
  /* Public stuff , funcs and attributes */

  /* Class constructor */
  inline Generator(NodeExit node) : m_node(std::move(node)) {}

  /* string_to_asm - Converts string to assembly code
   * @tooken: Token struct that hold some code (line)
   * Return: A strin (ouput) holding the asm code
   */

  std::string tokens_to_asm() {
    std::stringstream output;

    output << "global _start\n_start:\n";
    output << "    mov rax, 60\n";
    output << "    mov rdi, " << m_node.expr.int_lat.value.value() << "\n";
    output << "    syscall";
    return output.str();
  }

private:
  /* Private stuff here */
  NodeExit m_node;
};
