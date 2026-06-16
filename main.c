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
        case 1: // cadastro de novo livro
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
        case 2: // busca de livro por código
            int codigoBusca;

            printf("\nInsira o código do livro para busca:");
            printf("\nCodigo: ");
            scanf("%d", &codigoBusca);
            getchar(); // consome o '\n' deixado pelo scanf
            
            Livro *procurado = buscarLivroArvore(colecao, codigoBusca);

            if (procurado == NULL) {
                printf("\nLivro nao encontrado.\n");
            } else {
                exibirLivro(procurado);
            }
            
            break;
        case 3: // listagem dos livros em ordem crescente
                if (contarLivros(colecao) == 0) {
                    printf("\nNenhum livro cadastrado.\n");
                } else {
                    listarLivrosEmOrdem(colecao);
                }
            
            break;
        case 4: // listagem dos livros em pre-ordem
                if (contarLivros(colecao) == 0) {
                    printf("\nNenhum livro cadastrado.\n");
                } else {
                    listarLivrosEmPreOrdem(colecao);
                }

            break;
        case 5: // listagem dos livros em pos-ordem
                if (contarLivros(colecao) == 0) {
                    printf("\nNenhum livro cadastrado.\n");
                } else {
                    listarLivrosEmPosOrdem(colecao);
                }   

            break;
        case 6: // realizar empréstimo
            char nomeUsuario[100];
            int codigoEmprestimo;

            printf("\nInsira o nome do usuario e o codigo do livro desejado:");
            printf("\nNome do usuario: ");
            fgets(nomeUsuario, 100, stdin);
            nomeUsuario[strcspn(nomeUsuario, "\n")] = '\0';
            printf("\nCodigo do livro: ");
            scanf("%d", &codigoEmprestimo);
            getchar();

            Livro* livroEmprestimo = buscarLivroArvore(colecao, codigoEmprestimo);
            
            if (livroEmprestimo == NULL) {
                printf("\nLivro nao encontrado.\n");

            } else if (obterQuantidadeDisponivel(livroEmprestimo) > 0) {
            // livro disponível: empresta e registra no histórico
                emprestarExemplar(livroEmprestimo);
                
                Emprestimo emp;
                emp.codigoLivro = codigoEmprestimo;
                strncpy(emp.nomeUsuario, nomeUsuario, 99);
                emp.nomeUsuario[99] = '\0';
                strncpy(emp.tituloLivro, livroEmprestimo->titulo, 99);
                emp.tituloLivro[99] = '\0';
                inserirEmprestimo(historico, emp);
                printf("\nEmprestimo realizado com sucesso.\n");

            } else {
                // sem exemplares: oferece reserva
                printf("\nNao ha exemplares disponiveis.");
                printf("\nDeseja entrar na fila de reservas? (1 = Sim / 0 = Nao): ");
                int opcaoReserva;
                scanf("%d", &opcaoReserva);
                getchar();
                if (opcaoReserva == 1) {
                    Reserva reserva;
                    reserva.codigoLivro = codigoEmprestimo;
                    strncpy(reserva.nomeUsuario, nomeUsuario, 99);
                    reserva.nomeUsuario[99] = '\0';
                    enfileirarReserva(reservas, reserva);
                    printf("\nReserva realizada com sucesso.\n");
                }
            }

            break;
        case 7: // devolver empréstimo
            int codigoDevolver;

            printf("\nInsira o codigo do livro para devolucao");
            printf("\nCodigo: ");
            scanf("%d", &codigoDevolver);
            getchar();

            Livro *livroDevolver = buscarLivroArvore(colecao, codigoDevolver);

            if (livroDevolver == NULL) {
                printf("\nNenhum livro cadastrado com o codigo.");
                break;
            }
            
            devolverExemplar(livroDevolver);
            printf("\nLivro devolvido com sucesso.");

            // verifica se há reservas na fila para esse livro
            NoFila* atual = reservas->inicio;
            while (atual != NULL) {
                if (atual->reserva.codigoLivro == codigoDevolver) {
                    printf("\nHa usuarios aguardando esse livro na fila de reservas.");
                    printf("\nAtendendo o primeiro da fila: %s\n", atual->reserva.nomeUsuario);
                
                    // remove da fila e registra o empréstimo automático
                    Reserva atendida = desenfileirarReserva(reservas);
                    emprestarExemplar(livroDevolver);
                
                    Emprestimo emp;
                    emp.codigoLivro = codigoDevolver;
                    strncpy(emp.nomeUsuario, atendida.nomeUsuario, 99);
                    emp.nomeUsuario[99] = '\0';
                    strncpy(emp.tituloLivro, livroDevolver->titulo, 99);
                    emp.tituloLivro[99] = '\0';
                
                    inserirEmprestimo(historico, emp);
                    printf("Emprestimo automatico realizado para %s!\n", atendida.nomeUsuario);
                    break;
                }
                atual = atual->prox;
            }
        
            break;
        case 8: // consultar fila de reservas

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