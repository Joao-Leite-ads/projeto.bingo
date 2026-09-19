#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define LINHAS 5
#define COLUNAS 5
typedef enum
{
    B = 0,
    I,
    N,
    G,
    O
} Coluna;

typedef struct
{
    int numeros[LINHAS][COLUNAS];
} Cartela;

const char *nomesColunas[COLUNAS] = {"B", "I", "N", "G", "O"};
const int faixaMinima[COLUNAS] = {1, 16, 31, 46, 61};
const int faixaMaxima[COLUNAS] = {15, 30, 45, 60, 75};

/* Protótipos das funções */
int gerarNumero(int minimo, int maximo);
int numeroExiste(int valores[], int quantidade, int numero);
void ordenarColuna(int valores[], int quantidade);
void gerarCartela(Cartela *cartela);
void imprimirCartela(const Cartela *cartela, int numeroDaCartela);
int cartelasIguais(const Cartela *c1, const Cartela *c2);
int cartelaDuplicada(const Cartela cartelas[], int quantidadeAtual, const Cartela *nova);

int gerarNumero(int minimo, int maximo)
{
    return minimo + rand() % (maximo - minimo + 1);
}

int numeroExiste(int valores[], int quantidade, int numero)
{
    for (int i = 0; i < quantidade; i++)
    {
        if (valores[i] == numero)
        {
            return 1;
        }
    }
    return 0;
}

void ordenarColuna(int valores[], int quantidade)
{
    for (int i = 0; i < quantidade - 1; i++)
    {
        for (int j = 0; j < quantidade - 1 - i; j++)
        {
            if (valores[j] > valores[j + 1])
            {
                int aux = valores[j];
                valores[j] = valores[j + 1];
                valores[j + 1] = aux;
            }
        }
    }
}

void gerarCartela(Cartela *cartela)
{
    for (int col = 0; col < COLUNAS; col++)
    {
        int valores[LINHAS];
        int quantidadeGerada = 0;

        for (int lin = 0; lin < LINHAS; lin++)
        {
            if (lin == 2 && col == 2)
            {
                continue;
            }

            int numero;
            do
            {
                numero = gerarNumero(faixaMinima[col], faixaMaxima[col]);
            } while (numeroExiste(valores, quantidadeGerada, numero));

            valores[quantidadeGerada] = numero;
            quantidadeGerada++;
        }

        ordenarColuna(valores, quantidadeGerada);

        int idx = 0;
        for (int lin = 0; lin < LINHAS; lin++)
        {
            if (lin == 2 && col == 2)
            {
                cartela->numeros[lin][col] = 0;
            }
            else
            {
                cartela->numeros[lin][col] = valores[idx];
                idx++;
            }
        }
    }
}

void imprimirCartela(const Cartela *cartela, int numeroDaCartela)
{
    printf("Cartela %d:\n", numeroDaCartela);

    for (int col = 0; col < COLUNAS; col++)
    {
        printf(" %-3s", nomesColunas[col]);
    }
    printf("\n");

    for (int lin = 0; lin < LINHAS; lin++)
    {
        for (int col = 0; col < COLUNAS; col++)
        {
            if (lin == 2 && col == 2)
            {
                printf(" %3s", "X");
            }
            else
            {
                printf(" %3d", cartela->numeros[lin][col]);
            }
        }
        printf("\n");
    }
    printf("\n");
}

int cartelasIguais(const Cartela *c1, const Cartela *c2)
{
    for (int lin = 0; lin < LINHAS; lin++)
    {
        for (int col = 0; col < COLUNAS; col++)
        {
            if (c1->numeros[lin][col] != c2->numeros[lin][col])
            {
                return 0;
            }
        }
    }
    return 1;
}

int cartelaDuplicada(const Cartela cartelas[], int quantidadeAtual, const Cartela *nova)
{
    for (int i = 0; i < quantidadeAtual; i++)
    {
        if (cartelasIguais(&cartelas[i], nova))
        {
            return 1;
        }
    }
    return 0;
}

int main(void)
{
    srand((unsigned int)time(NULL));

    int quantidade;

    printf("=== Gerador de Cartelas de Bingo ===\n\n");
    printf("Quantas cartelas deseja gerar? ");

    if (scanf("%d", &quantidade) != 1 || quantidade <= 0)
    {
        printf("Quantidade invalida.\n");
        return 1;
    }

    Cartela *cartelas = (Cartela *)malloc((size_t)quantidade * sizeof(Cartela));
    if (cartelas == NULL)
    {
        printf("Erro ao alocar memoria.\n");
        return 1;
    }

    for (int i = 0; i < quantidade; i++)
    {
        Cartela nova;

        do
        {
            gerarCartela(&nova);
        } while (cartelaDuplicada(cartelas, i, &nova));

        cartelas[i] = nova;
    }

    printf("\n");
    for (int i = 0; i < quantidade; i++)
    {
        imprimirCartela(&cartelas[i], i + 1);
    }

    free(cartelas);
    return 0;
}
