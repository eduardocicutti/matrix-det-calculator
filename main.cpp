#include <iostream>
#include <iomanip>
#include <vector>

// Implementar função básica para calcular o det de uma matriz
int determinant(std::vector<std::vector<int>>& matrix) 
{
    int n = matrix.size();
    int det = 0;

    // Calcular matrizes 1x1 e 2x2
    if (n == 1)
        return matrix[0][0];
    if (n == 2)
        return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];

    // Laplace para matrizes maiores, usando for loop
    for (int k = 0; k < n; k++) 
    {
        std::vector<std::vector<int>> submatrix(n - 1, std::vector<int>(n - 1));

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

int main ()
{
    int n;
    bool matriz_valida = false;

    // Loop para garantir que a ordem da matriz seja válida
    std::cout << "--------------- Calculadora de Determinante ---------------\n";

    while (!matriz_valida) {
        std::cout << "Digite a ordem da matriz: ";
        std::cin >> n;
        if (std::cin.fail() || n <= 0 || n > 10) {
            std::cout << "Erro: Insira um número inteiro positivo entre 1 e 10 como a ordem da matriz.\n";
            std::cin.clear(); // Limpa o estado de erro
            while (std::cin.get() != '\n'); // Descarta entrada inválida
        } else {
            matriz_valida = true;
        }
    }

    std::vector<std::vector<int>> matrix(n, std::vector<int>(n));

    // Loop para solicitar a entrada de cada elemento da matriz
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            bool elemento_valido = false;
            while (!elemento_valido) {
                std::cout << "Digite o elemento da posição (" << i + 1 << ", " << j + 1 << "): ";
                if (!(std::cin >> matrix[i][j])) {
                    std::cout << "Erro: Insira apenas números inteiros como elementos da matriz.\n";
                    std::cin.clear(); // Limpa o estado de erro
                    while (std::cin.get() != '\n'); // Descarta entrada inválida
                } else {
                    elemento_valido = true;
                }
            }
        }
    }

    std::cout << "--------------- Matriz digitada ---------------\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            std::cout << std::setw(6) << matrix[i][j];
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