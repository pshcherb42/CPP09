/*1. Parsear la expresión (separar números y operadores)
2. Procesar token por token:
   - Si es un número → guardar en estructura
   - Si es un operador → aplicar operación a los últimos 2 números
3. Al final, debería quedar 1 solo número (el resultado)

Para cada token:
  - Si es número: push() al stack
  - Si es operador:
	* pop() dos números (b, a)
	* Calcula: a operador b
	* push() resultado*/
#include <string>
#include <iostream>
#include <sstream>
#include <stack>
#include <cctype>
#include <exception>

int main(int argc, char **argv) {
	if (argc != 2) {
		std::cerr << "Error: wrong number of arguments" << std::endl;
		return 1;
	}
	std::string str;
	std::stack<int> st;
	std::stringstream ss(argv[1]);
	while (std::getline(ss, str, ' ')) {
		if (!std::isdigit(str[0]) && str[0] != '+' && str[0] != '-' && 
    		str[0] != '*' && str[0] != '/') {
    		std::cerr << "Error: invalid character\n";
   			return 1;
		}
		else if (std::isdigit(str[0])) {
			int num = std::stoi(str);
			if (str.length() != 1) {
        		std::cerr << "Error: number must be < 10\n";
        		return 1;
    		}
			st.push(num);
		}
		else if (str[0] == '+') {
			if (st.size() < 2) {
    			std::cerr << "Error: not enough operands\n";
    			return 1;
			}
			int b = st.top(); st.pop();
			int a = st.top(); st.pop();
			st.push(a + b);
		}
		else if (str[0] == '-') {
			if (st.size() < 2) {
    			std::cerr << "Error: not enough operands\n";
    			return 1;
			}
			int b = st.top(); st.pop();
			int a = st.top(); st.pop();
			st.push(a - b);
		}
		else if (str[0] == '*') {
			if (st.size() < 2) {
    			std::cerr << "Error: not enough operands\n";
    			return 1;
			}
			int b = st.top(); st.pop();
            int a = st.top(); st.pop();
            st.push(a * b);
		}
		else if (str[0] == '/') {
			if (st.size() < 2) {
    			std::cerr << "Error: not enough operands\n";
    			return 1;
			}
			int b = st.top(); st.pop();
            int a = st.top(); st.pop();
			if (b == 0) {
				std::cerr << "Error: division by zero\n";
        		return 1;
			}
            st.push(a / b);
		}
	}
	if (st.empty()) {
    std::cerr << "Error: no operands\n";
    return 1;
	}
	if (st.size() != 1) {
	    std::cerr << "Error: too many operands\n";
	    return 1;
	}
	std::cout << st.top() << std::endl;
}