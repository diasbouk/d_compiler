#include "./parser.hpp"
#include "tokenizer.hpp"
#include <algorithm>
#include <cassert>
#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <unordered_map>
#include <utility>
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
            void operator()(const NodeExprIdent ident) {

                const auto it =
                    std::find_if(gen->m_vars.begin(), gen->m_vars.end(),
                                 [&stoi(ident.ident.value.value()), ident](const Var &var) {
                                     return (int)var.stack_loc ==
                                            stoi(ident.ident.value.value());
                                 });
                if (it == gen->m_vars.cend()) {
                    std::cerr << "Undeclared identifier: "
                              << ident.ident.value.value() << std::endl;
                    exit(EXIT_FAILURE);
                }
                const auto var = gen->m_vars.at(ident.ident.value.value());
                std::stringstream offset;
                offset << "[rsp + " << (gen->stack_count - var.stack_loc)
                       << "]\n";
                gen->push(offset.str());
            }
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
            void operator()(const NodeStmtLet stmt_let) {
                if (gen->m_vars.find(stmt_let.ident.value.value()) ==
                    gen->m_vars.end()) {
                    std::cerr << "Identifier already exists "
                              << stmt_let.ident.value.value() << std::endl;
                    exit(EXIT_FAILURE);
                }
                gen->m_vars.insert(
                    std::make_pair(stmt_let.ident.value.value(),
                                   Var{.stack_loc = gen->stack_count}));
                gen->gen_expr(stmt_let.expr);
                gen->push("");
            }
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
        m_output << "    mov rdi, 0" << "\n";
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

    typedef struct Var {
        size_t stack_loc;
    } Var;
    NodeProgr m_node;
    std::stringstream m_output;
    size_t stack_count = 0;
    std::unordered_map<std::string, Var> m_vars{};
};
