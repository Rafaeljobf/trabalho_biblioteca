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

Arvore* criarArvore(); // feito

void inserirLivroArvore(Arvore* arvore, Livro* livro); // feito

Livro* buscarLivroArvore(Arvore* arvore, int codigo); // feito

void listarLivrosEmOrdem(Arvore* arvore); // feito

void listarLivrosEmPreOrdem(Arvore* arvore); // feito

void listarLivrosEmPosOrdem(Arvore* arvore); // feito

int contarLivros(Arvore* arvore); // feito

int calcularAlturaArvore(Arvore* arvore); // feito

#endif //TRABALHO_BIBLIOTECA_ARVORE_H
