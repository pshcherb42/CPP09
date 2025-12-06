#ifndef RPN_HPP
#define RPN_HPP

#include <string>
#include <stack>
#include <stdexcept>
#include <sstream>
#include <cctype>
#include <iostream>

class RPN {
public:
    RPN();
    ~RPN();

    // Evaluates an RPN expression like "8 9 * 9 -"
    // Throws std::runtime_error on any error.
    int evaluate(const std::string& expr);

private:
    // Parses a single token as an integer (only one digit allowed: 0-9).
    // Throws std::runtime_error if invalid.
    int parseSingleDigit(const std::string& tok) const;

    // Applies operator to top two stack values (a op b).
    // Throws std::runtime_error for underflow or division by zero.
    void applyOperator(std::stack<int>& st, char op) const;

    // Utility: trims leading/trailing spaces and tabs from token.
    std::string trim(const std::string& s) const;
};

#endif // RPN_HPP