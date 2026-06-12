#include "livro.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Livro* criarLivro(int codigo, char titulo[], char autor[], int ano, int quantidadeTotal) {
    Livro* novoLivro = malloc(sizeof(Livro));

    if (novoLivro == NULL) {
        printf("Erro crônico: Falha ao alocar memória para o livro.\n");
        return NULL;
    }

    novoLivro->codigo = codigo;
    novoLivro->ano = ano;
    novoLivro->quantidadeTotal = quantidadeTotal;
    novoLivro->quantidadeDisponivel = quantidadeTotal; // inicialmente são iguais

    strncpy(novoLivro->titulo, titulo, 99);
    novoLivro->titulo[99] = '\0';

    strncpy(novoLivro->autor, autor, 99);
    novoLivro->autor[99] = '\0';

    return novoLivro;
}

void exibirLivro(Livro* livro) {
    if (livro == NULL) {
        printf("Erro: Ponteiro de livro nulo.\n");
        return;
    }
    printf("========================================\n");
    printf("Código: %d\n", livro->codigo);
    printf("Título: %s\n", livro->titulo);
    printf("Autor:  %s\n", livro->autor);
    printf("Ano:    %d\n", livro->ano);
    printf("Total:  %d | Disponível: %d\n", livro->quantidadeTotal, livro->quantidadeDisponivel);
    printf("========================================\n");
}

int obterCodigoLivro(Livro* livro) {
    if (livro != NULL) {
        return livro->codigo;
    }
    return -1; // código de erro caso o ponteiro seja nulo
}

int obterQuantidadeDisponivel(Livro* livro) {
    if (livro != NULL) {
        return livro->quantidadeDisponivel;
    }
    return -1;
}

void emprestarExemplar(Livro* livro) {
    if (livro != NULL && livro->quantidadeDisponivel > 0) {
        livro->quantidadeDisponivel--;
        return;
    }
    printf("Não foi possível emprestar o exemplar!");
}

void devolverExemplar(Livro* livro) {
    if (livro != NULL && livro->quantidadeDisponivel < livro->quantidadeTotal) {
        livro->quantidadeDisponivel++;
        return;
    }
    printf("Não foi possível devolver o exemplar!");
}

void liberarLivro(Livro* livro) {
    if (livro != NULL) {
        free(livro); 
    }
}