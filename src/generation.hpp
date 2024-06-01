#include "./parser.hpp"
#include "tokenizer.hpp"
#include <sstream>

class Generator {
  public:
    /* Public stuff , funcs and attributes */

    /* Class constructor */
    inline Generator(NodeStmtExit node) : m_node(node) {}

    /* string_to_asm - Converts string to assembly code
     * @tooken: Token struct that hold some code (line)
     * Return: A strin (ouput) holding the asm code
     */

    std::string tokens_to_asm() {
        std::stringstream output;

        output << "global _start\n_start:\n";
        output << "    mov rax, 60\n";
        std::cout << "--" << m_node.expr.NodeExprInt.value.value() << "--";
        output << "    mov rdi, " << m_node.expr.int_lat.value.value() << "\n";
        output << "    syscall";
        return output.str();
    }

  private:
    /* Private stuff here */
    NodeStmtExit m_node;
};
