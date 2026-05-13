#ifndef TRABALHO_BIBLIOTECA_ARVORE_H
#define TRABALHO_BIBLIOTECA_ARVORE_H
#include "livro.h"

typedef struct NoArvore {
    Livro* livro;
    struct NoArvore* esquerda;
    struct NoArvore* direita;
} NoArvore;

typedef struct {
    NoArvore* raiz;
} Arvore;

Arvore* criarArvore();

void inserirLivroArvore(Arvore* arvore, Livro* livro);

Livro* buscarLivroArvore(Arvore* arvore, int codigo);

void listarLivrosEmOrdem(Arvore* arvore);

void listarLivrosEmPreOrdem(Arvore* arvore);

void listarLivrosEmPosOrdem(Arvore* arvore);

int contarLivros(Arvore* arvore);

int calcularAlturaArvore(Arvore* arvore);

#endif //TRABALHO_BIBLIOTECA_ARVORE_H
