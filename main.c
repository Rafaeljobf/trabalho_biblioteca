#include <stdio.h>
#include <stdlib.h>
#include "livro.h"
#include "arvore.h"
#include "fila.h"
#include "lista.h"

void exibirMenu() {
    printf("\n//==== SISTEMA DE BIBLIOTECA - BIBLIOTECH ====//\n");
    printf("1. Cadastrar Livro\n");
    printf("2. Buscar Livro por Codigo\n");
    printf("3. Listar Livros (Em-ordem)\n");
    printf("4. Listar Livros (Pre-ordem)\n");
    printf("5. Listar Livros (Pos-ordem)\n");
    printf("6. Realizar Emprestimo\n");
    printf("7. Devolver Livro\n");
    printf("8. Consultar Fila de Reservas\n");
    printf("9. Exibir Historico de Emprestimos\n");
    printf("10. Contar Total de Livros\n");
    printf("11. Exibir Altura da Arvore\n");
    printf("0. Sair\n");
    printf("Escolha uma opcao: ");

    //TODO: adicionar as funcionalidades optativas pra ficar impecável
}
int main() {
    int opcao;

    Fila reservas;
    Arvore colecao;
    Lista historico;

    do {
        exibirMenu();
        scanf("%d", &opcao);

    } while (opcao != 0);

    return 0;
}