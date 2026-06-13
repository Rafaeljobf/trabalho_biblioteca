#include "lista.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Lista* criarLista() {
    Lista* lista = (Lista*) malloc(sizeof(Lista));
    if (lista == NULL) return NULL;
    lista -> inicio = NULL;
    return lista;
}

int listaVazia(Lista* lista) {
    if (lista == NULL || lista -> inicio == NULL) {
        return 1; // vazia
    }
    return 0; // não vazia
}

NoLista* criarNoLista() {
    NoLista* novoNo = (NoLista*) malloc(sizeof(NoLista));
    if (novoNo == NULL) {
        printf("Erro de alocação de memória na lista.\n");
        return NULL;
    }
    return novoNo;
}

void inserirEmprestimo(Lista* lista, Emprestimo emprestimo) {
    if (lista == NULL) return;

    NoLista* novoNo = criarNoLista();
    if (novoNo == NULL) return; 

    novoNo -> emprestimo = emprestimo;// copia os dados do emprestimo
    novoNo -> prox = lista -> inicio;
    lista -> inicio = novoNo;// insere no início da lista
}

void listarEmprestimos(Lista* lista) {
    if (listaVazia(lista)) {
        printf("Nenhum emprestimo registrado no histórico.\n");
        return;
    }

    NoLista* atual = lista -> inicio;
    printf("\n--- HISTORICO DE EMPRESTIMOS ---\n");
    while (atual != NULL) {
        printf("Usuario: %s | Livro: %s (Cod: %d)\n",
            atual -> emprestimo.nomeUsuario,
            atual -> emprestimo.tituloLivro,
            atual -> emprestimo.codigoLivro);
        atual = atual -> prox;
    }
    printf("--------------------------------\n");
}