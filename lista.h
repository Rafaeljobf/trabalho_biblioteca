#ifndef TRABALHO_BIBLIOTECA_LISTA_H
#define TRABALHO_BIBLIOTECA_LISTA_H

typedef struct {
    char nomeUsuario[100];
    int codigoLivro;
    char tituloLivro[100];
} Emprestimo;

typedef struct NoLista {
    Emprestimo emprestimo;
    struct NoLista* prox;
} NoLista;

typedef struct Lista {
    NoLista* inicio;
} Lista;

Lista* criarLista();

void inserirEmprestimo(Lista* lista, Emprestimo emprestimo);

void listarEmprestimos(Lista* lista);

int listaVazia(Lista* lista);

#endif //TRABALHO_BIBLIOTECA_LISTA_H
