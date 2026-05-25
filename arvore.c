#include "arvore.h"
#include "livro.h"

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

// funções auxiliares de listagem em pre ordem, ordem e pos ordem

static void emOrdemNo(NoArvore* raiz) {
    if (raiz != NULL) {
        emOrdemNo(raiz->esquerda);
        exibirLivro(raiz->livro);
        emOrdemNo(raiz->direita);
    }
}

static void preOrdemNo(NoArvore* raiz) {
    if (raiz != NULL) {
        exibirLivro(raiz->livro);
        preOrdemNo(raiz->esquerda);
        preOrdemNo(raiz->direita);
    }
}

static void posOrdemNo(NoArvore* raiz) {
    if (raiz != NULL) {
        posOrdemNo(raiz->esquerda);
        posOrdemNo(raiz->direita);
        exibirLivro(raiz->livro);
    }
}



// função auxiliar de calcularAlturaArvore

static int calcularAlturaNo(NoArvore* raiz) {

    if (raiz == NULL) {
        return -1;
    }

    int altEsq = calcularAlturaNo(raiz->esquerda);
    int altDir = calcularAlturaNo(raiz->direita);

    if (altEsq > altDir) {
        return altEsq + 1;
    }

    return altDir + 1;
}



// função auxiliar de criação de Nó
static NoArvore* criarNoArvore() {
    NoArvore* novoNo = malloc(sizeof(NoArvore));

    if (novoNo == NULL) {
        return NULL;
    }

    novoNo->livro = NULL;
    novoNo->esquerda = NULL;
    novoNo->direita = NULL;

    return novoNo;
}

// função auxiliar de contagem de livros
static int contarNosRecursivo(NoArvore* no) {
    if (no == NULL) {
        return 0;
    }

    return 1 + contarNosRecursivo(no->esquerda) + contarNosRecursivo(no->direita);
}

// funções principais

void listarLivrosEmOrdem(Arvore* arvore) {

    if (arvore == NULL || arvore->raiz == NULL) {
        return;
    }

    emOrdemNo(arvore->raiz);
}

void listarLivrosEmPreOrdem(Arvore* arvore) {

    if (arvore == NULL || arvore->raiz == NULL) {
        return;
    }

    preOrdemNo(arvore->raiz);
}

void listarLivrosEmPosOrdem(Arvore* arvore) {

    if (arvore == NULL || arvore->raiz == NULL) {
        return;
    }

    posOrdemNo(arvore->raiz);
}

int calcularAlturaArvore(Arvore* arvore) {

    if (arvore == NULL || arvore->raiz == NULL) {
        return -1;
    }
    return calcularAlturaNo(arvore->raiz);
}

Arvore* criarArvore() {
    Arvore* novaArvore = malloc(sizeof(Arvore));

    if (novaArvore == NULL) {
        printf("Erro ao alocar memória.");
        exit(EXIT_FAILURE);
    }

    novaArvore->raiz = NULL;

    return novaArvore;
}

void inserirLivroArvore(Arvore* arvore, Livro* livro) {
    if (arvore == NULL || livro == NULL) {
        printf("ERRO: Dados inválidos!");
        return;
    }

    // se a arvore estiver vazia, o novo nó se torna a raiz da árvore
    if (arvore->raiz == NULL) {
        NoArvore* novoNo = criarNoArvore();
        if (novoNo == NULL) return;

        novoNo->livro = livro;
        arvore->raiz = novoNo;
        return;
    }

    // ponteiros auxiliares para encontrar espaço em que deve ficar o novo nó
    NoArvore* atual = arvore->raiz;
    NoArvore* pai = NULL;

    while (atual != NULL) {
        pai = atual;

        if (livro->codigo < atual->livro->codigo) {
            atual = atual->esquerda;
        } else if (livro->codigo > atual->livro->codigo) {
            atual = atual->direita;
        } else {
            printf("Erro: Livro com código %d já existe.\n", livro->codigo);
            return;
        }
    }

    // alocação tardia para evitar possíveis erros que já foram tratados
    NoArvore* novoNo = criarNoArvore();
    if (novoNo == NULL) {
        printf("Erro ao alocar memória para o nó. \n");
        return;
    }
    novoNo->livro = livro;

    if (livro->codigo < pai->livro->codigo) {
        pai->esquerda = novoNo;
    } else if (livro->codigo > pai->livro->codigo) {
        pai->direita = novoNo;
    }
}

Livro* buscarLivroArvore(Arvore* arvore, int codigo) {
    if (arvore == NULL || arvore->raiz == NULL) {
        printf("ERRO: Árvore inexistente ou vazia.");
        return NULL;
    }

    NoArvore* atual = arvore->raiz;

    while (atual != NULL) {
        if (codigo == atual->livro->codigo) {
            return atual->livro;
        }
        if (codigo < atual->livro->codigo) {
            atual = atual->esquerda;
        } else if (codigo > atual->livro->codigo) {
            atual = atual->direita;
        }
    }
    return NULL;
}

int contarLivros(Arvore* arvore) {
    if (arvore == NULL) {
        return 0;
    }
    return contarNosRecursivo(arvore->raiz);
}
