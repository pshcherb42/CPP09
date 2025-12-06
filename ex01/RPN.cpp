#include "RPN.hpp"

RPN::RPN() {}
RPN::~RPN() {}

std::string RPN::trim(const std::string& s) const {
    std::string::size_type start = s.find_first_not_of(" \t");
    if (start == std::string::npos) return "";
    std::string::size_type end = s.find_last_not_of(" \t");
    return s.substr(start, end - start + 1);
}

int RPN::parseSingleDigit(const std::string& tok) const {
    if (tok.empty())
        throw std::runtime_error("invalid character");
    // token must be exactly one char and a digit
    if (tok.size() != 1 || !std::isdigit(static_cast<unsigned char>(tok[0])))
        throw std::runtime_error("number must be < 10");
    return tok[0] - '0';
}

void RPN::applyOperator(std::stack<int>& st, char op) const {
    if (st.size() < 2)
        throw std::runtime_error("not enough operands");
    int b = st.top(); st.pop();
    int a = st.top(); st.pop();
    switch (op) {
        case '+': st.push(a + b); break;
        case '-': st.push(a - b); break;
        case '*': st.push(a * b); break;
        case '/':
            if (b == 0) throw std::runtime_error("division by zero");
            st.push(a / b);
            break;
        default:
            throw std::runtime_error("invalid character");
    }
}

int RPN::evaluate(const std::string& expr) {
    std::stack<int> st;
    std::stringstream ss(expr);
    std::string tok;

    while (std::getline(ss, tok, ' ')) {
        tok = trim(tok);
        if (tok.empty()) continue; // skip extra spaces

        // token must be a single digit or an operator
        if (tok.size() == 1 && (tok[0] == '+' || tok[0] == '-' || tok[0] == '*' || tok[0] == '/')) {
            applyOperator(st, tok[0]);
        } else if (tok.size() == 1 && std::isdigit(static_cast<unsigned char>(tok[0]))) {
            int num = parseSingleDigit(tok);
            st.push(num);
        } else {
            // Any other form (multi-char number, negative, etc.) is invalid per spec
            if (tok.size() != 1 && std::isdigit(static_cast<unsigned char>(tok[0])))
                throw std::runtime_error("number must be < 10");
            throw std::runtime_error("invalid character");
        }
    }

    if (st.empty())
        throw std::runtime_error("no operands");
    if (st.size() != 1)
        throw std::runtime_error("too many operands");
    return st.top();
}