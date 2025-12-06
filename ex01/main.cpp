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
#include "RPN.hpp"

int main(int argc, char **argv) {
    if (argc != 2) {
        std::cerr << "Error: wrong number of arguments" << std::endl;
        return 1;
    }
    RPN rpn;
    try {
        int result = rpn.evaluate(argv[1]);
        std::cout << result << std::endl;
    } catch (const std::runtime_error& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}