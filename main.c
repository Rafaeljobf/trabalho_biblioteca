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

    Fila* reservas = criarFila();
    Arvore* colecao = criarArvore();
    Lista* historico = criarLista();

    do {
        exibirMenu();
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
            int codigo, ano, quantidade;
            char titulo[100], autor[100];

            printf("\nInsira os dados do livro para cadastro:");
            printf("\nCodigo: ");
            scanf("%d", &codigo);
            getchar(); // consome o '\n' deixado pelo scanf
            printf("\nTitulo: ");
            fgets(titulo, 100, stdin);
            printf("\nAutor: ");
            fgets(autor, 100, stdin);
            printf("\nAno de Publicacao: ");
            scanf("%d", &ano);
            getchar();
            printf("\nQuantidade Total de Exemplares: ");
            scanf("%d", &quantidade);
            getchar();

            Livro *livro = criarLivro(codigo, titulo, autor, ano, quantidade);

            if (!inserirLivroArvore(colecao, livro)) {
                liberarLivro(livro);
            } else {
                printf("\nLivro cadastrado com sucesso.\n");
            }
            
            break;
        case 2:
            int codigoBusca;

            printf("Insira o código do livro para busca:\n");
            printf("Codigo: ");
            scanf("%d", &codigoBusca);
            getchar(); // consome o '\n' deixado pelo scanf
            
            Livro *procurado = buscarLivroArvore(colecao, codigoBusca);

            if (procurado == NULL) {
                printf("\nLivro nao encontrado\n");
            } else {
                exibirLivro(procurado);
            }
            
            break;
        case 3:
                if (contarLivros(colecao) == 0) {
                    printf("\nNenhum livro cadastrado.\n");
                } else {
                    listarLivrosEmOrdem(colecao);
                }
            
            break;
        case 4:
                if (contarLivros(colecao) == 0) {
                    printf("\nNenhum livro cadastrado.\n");
                } else {
                    listarLivrosEmPreOrdem(colecao);
                }

            break;
        case 5:
                if (contarLivros(colecao) == 0) {
                    printf("\nNenhum livro cadastrado.\n");
                } else {
                    listarLivrosEmPosOrdem(colecao);
                }   

            break;
        case 6:

            break;
        case 7:
            
            break;
        case 8:

            break;
        case 9:
            
            break;
        case 10:

            break;
        case 11:
            
            break;
        case 0:
            printf("Saindo do sistema.\n");
            break;
        default:
            break;
        }

    } while (opcao != 0);

    return 0;
}