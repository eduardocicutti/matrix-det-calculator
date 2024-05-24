#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <sstream>

// Função para calcular o determinante de uma matriz
double determinant(const std::vector<std::vector<double>>& matrix) 
{
    int n = matrix.size();
    double det = 0.0;

    // Calcular determinante para matrizes 1x1 e 2x2
    if (n == 1)
        return matrix[0][0];
    if (n == 2)
        return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];

    // Laplace para matrizes maiores
    for (int k = 0; k < n; k++) 
    {
        std::vector<std::vector<double>> submatrix(n - 1, std::vector<double>(n - 1));

        // Removendo a linha 0 e a coluna k 
        for (int i = 1; i < n; i++)
        {
            int l = 0;
            for (int j = 0; j < n; j++)
            {
                if (j != k)
                {
                    submatrix[i - 1][l] = matrix[i][j];
                    l++;
                }
            }
        }

        // Determinar a mudança de sinal para o termo corrente da expansão de Laplace
        int sinal = (k % 2 == 0) ? 1 : -1;

        // Calcula o determinante da submatriz
        det += sinal * matrix[0][k] * determinant(submatrix);
    }

    return det;
}

// Função para converter string de fração para double
double parseFraction(const std::string& str) 
{
    std::istringstream iss(str);
    double num;
    char div;
    double denom;

    if (iss >> num && iss >> div && div == '/' && iss >> denom) {
        return num / denom;
    }
    return std::stod(str); // Retorna o valor como double se não for fração
}

int main ()
{
    int n;
    bool matriz_valida = false;

    // Mensagem de boas-vindas e instruções
    std::cout << "--------------- Calculadora de Determinante ---------------\n";
    std::cout << "Este programa calcula o determinante de uma matriz quadrada.\n";
    std::cout << "Por favor, insira a ordem da matriz e os elementos.\n";

    // Loop para garantir que a ordem da matriz seja válida
    while (!matriz_valida) {
        std::cout << "Digite a ordem da matriz (1-10): ";
        std::cin >> n;
        if (std::cin.fail() || n <= 0 || n > 10) {
            std::cout << "Erro: Insira um número inteiro positivo entre 1 e 10 como a ordem da matriz.\n";
            std::cin.clear(); // Limpa o estado de erro
            while (std::cin.get() != '\n'); // Descarta entrada inválida
        } else {
            matriz_valida = true;
        }
    }

    std::vector<std::vector<double>> matrix(n, std::vector<double>(n));
    std::cin.ignore(); // Ignorar qualquer caractere pendente no buffer de entrada

    // Loop para solicitar a entrada de cada elemento da matriz
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            bool elemento_valido = false;
            while (!elemento_valido) {
                std::cout << "Digite o elemento da posição (" << i + 1 << ", " << j + 1 << ") [ex.: 1/2 ou 3]: ";
                std::string input;
                std::getline(std::cin, input);
                try {
                    matrix[i][j] = parseFraction(input);
                    elemento_valido = true;
                } catch (const std::invalid_argument& e) {
                    std::cout << "Erro: Insira um número válido ou uma fração como elementos da matriz.\n";
                }
            }
        }
    }

    std::cout << "--------------- Matriz digitada ---------------\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            std::cout << std::setw(8) << matrix[i][j];
        }
        std::cout << std::endl;
    }

    char confirmacao;
    bool confirmacao_valida = false;

    while (!confirmacao_valida) {
        std::cout << "\nDeseja continuar com o cálculo? (y/n): ";
        std::cin >> confirmacao;

        if (confirmacao == 'y' || confirmacao == 'Y') {
            confirmacao_valida = true;
        } else if (confirmacao == 'n' || confirmacao == 'N') {
            std::cout << "Calculo cancelado pelo usuario.\n";
            return 0;
        } else {
            std::cout << "Erro: Insira 'y' ou 'n' para continuar.\n";
        }
    }

    // Calcular e imprimir o determinante da matriz
    std::cout << "Determinante = " << determinant(matrix) << std::endl;

    return 0;
}
