#pragma once

#include "tokenizer.hpp"
#include <cstdlib>
#include <variant>
#include <vector>

/* Expressions nodes */

struct NodeExprInt {
    Token int_lat;
};
struct NodeExprIdent {
    Token ident;
};

/* Union | vriant for expressions nodes */

struct NodeExpr {
    std::variant<NodeExprInt, NodeExprIdent> var;
};

/* Statments nodes */
struct NodeStmtExit {
    NodeExpr expr = {.var = NodeExprInt {}};
};

struct NodeStmtLet {
    Token ident;
    NodeExpr expr;
};

struct NodeStmt {
    std::variant<NodeStmtExit, NodeStmtLet> var;
};

/* Programm full statements Node (vect) */
struct NodeProgr {
    std::vector<NodeStmt> stmts;
};

class Parser {
  public:
    /* Public constructor of our class */
    inline explicit Parser(std::vector<Token> tokens) : m_tokens(tokens) {}

    /* parse - function to parse expressions
     * It takes m_tokens and it generates a tree
     * for a single line or expression
     * Return: NodeExit tree
     */

    std::optional<NodeProgr> parse() {
        NodeStmt tree;
        NodeProgr progrm;
        for (int i = 0; i < m_tokens.size(); i++) {
            if (m_tokens.at(i).type == TokenType::_exit) {
                if (!(m_tokens.at(i + 1).type == TokenType::open_par)) {
                    std::cout << "Expected `(`" << std::endl;
                    exit(EXIT_FAILURE);
                }
                if (m_tokens.at(i + 2).type == TokenType::int_lat) {
                    if (!(m_tokens.at(i + 3).type == TokenType::close_par)) {
                        std::cout << "Expected `)`" << std::endl;
                        exit(EXIT_FAILURE);
                    }
                    tree = {
                        .var = NodeStmtExit{
                            .expr = {.var = NodeExprInt{
                                         .int_lat = {
                                             .value = m_tokens.at(i + 2)
                                                          .value.value()}}}}};
                    progrm.stmts.push_back(tree);
                } else {
                    std::cout << "Invalid expression" << std::endl;
                    exit(EXIT_FAILURE);
                }
                if (m_tokens.at(i + 4).type == TokenType::semicol) {
                    break;
                } else {
                    std::cout << "Invalid Syntax : ';' expected" << std::endl;
                    exit(EXIT_FAILURE);
                }
            } else if (m_tokens.at(i).type == TokenType::ident) {

                if (!(m_tokens.at(i + 1).type == TokenType::eq)) {
                    std::cout << "Expected `=`" << std::endl;
                    exit(EXIT_FAILURE);
                }
                tree = {
                    .var = NodeStmtLet{
                        .expr = {.var = NodeExprIdent{
                                     .ident = {TokenType::ident,
                                               .value = m_tokens.at(i + 2)
                                                            .value.value()}}}}};
                progrm.stmts.push_back(tree);
                if (m_tokens.at(i + 3).type != TokenType::semicol) {
                    std::cout << "Invalid syntax expr or ; expected"
                              << std::endl;
                    exit(EXIT_FAILURE);
                }

            } else {
                std::cout << "Invalid syntax expr or ; expected" << std::endl;
                exit(EXIT_FAILURE);
            }
        }
        return progrm;
    }

    /* Private properties stuff here */
  private:
    const std::vector<Token> m_tokens;
};
