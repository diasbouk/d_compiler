#include "./parser.hpp"
#include "tokenizer.hpp"
#include <cstddef>
#include <sstream>
#include <unordered_map>
#include <variant>

class Generator {
  public:
    /* Public stuff , funcs and attributes */

    /* Class constructor */
    inline Generator(NodeProgr node) : m_node(node) {}

    /* string_to_asm - Converts string to assembly code
     * @tooken: Token struct that hold some code (line)
     * Return: A strin (ouput) holding the asm code
     */
    void gen_expr(const NodeExpr expr) {
        struct exprVisitor {
            Generator *gen;
            exprVisitor(Generator *gen) : gen(gen) {}
            void operator()(const NodeExprInt int_lit) {
                gen->m_output << "    mov rax, "
                              << int_lit.int_lat.value.value() << "\n";
                gen->push("rax");
            }
            void operator()(const NodeExprIdent ident) {}
        };
        exprVisitor visitor(this);
        std::visit(visitor, expr.var);
    }

    /* string_to_asm - Converts string to assembly code
     * @tooken: Token struct that hold some code (line)
     * Return: A strin (ouput) holding the asm code
     */

    void gen_stmt(NodeStmt stmt) {
        std::stringstream output;
        struct stmtVisitor {
            Generator *gen;
            stmtVisitor(Generator *gen) : gen(gen) {}
            void operator()(const NodeStmtExit stmt_exit) {
                gen->gen_expr(stmt_exit.expr);
                gen->m_output << "    mov rax, 60\n";
                gen->pop("rdi");
                gen->m_output << "    syscall\n";
            }
            void operator()(const NodeStmtLet stmt_let) {}
        };
        stmtVisitor visitor(this);
        std::visit(visitor, stmt.var);
    }

    /* string_to_asm - Converts string to assembly code
     * @tooken: Token struct that hold some code (line)
     * Return: A strin (ouput) holding the asm code
     */

    std::string generate_progr() {

        m_output << "global _start\n_start:\n";

        for (const NodeStmt &stmt : m_node.stmts) {
            gen_stmt(stmt);
        }

        m_output << "    mov rax, 60\n";
        m_output << "    mov rdi, 0"
                 << "\n";
        m_output << "    syscall\n";
        return m_output.str();
    }

  private:
    /* Private stuff here */

    void push(std::string reg) {
        m_output << "push" << reg << "\n";
        stack_count += 1;
    }

    void pop(std::string reg) {
        m_output << "pop" << reg << "\n";
        stack_count -= 1;
    }

    struct Var {
        size_t stack_loc;
    };
    NodeProgr m_node;
    std::stringstream m_output;
    size_t stack_count;
    std::unordered_map<std::string, Var> m_vars {};
};
