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


// função auxiliar de criação de Nó
static NoArvore* criarNoArvore() {
    NoArvore* novoNo = malloc(sizeof(NoArvore));

    if (novoNo == NULL) {
        return NULL;
    }

    novoNo->livro = NULL;
    novoNo->esquerda = NULL;
    novoNo->direita = NULL;
    novoNo->altura = 0;

    return novoNo;
}

// função auxiliar de contagem de livros
static int contarNosRecursivo(NoArvore* no) {
    if (no == NULL) {
        return 0;
    }

    return 1 + contarNosRecursivo(no->esquerda) + contarNosRecursivo(no->direita);
}

// funções auxiliares de balanceamento

static int maxInt(int a, int b) {
    return (a > b) ? a : b;
}

static int alturaNo(NoArvore* no) {
    if (no == NULL) return -1;
    return no->altura;
}

static int fatorBalanceamento(NoArvore* no) {
    if (no == NULL) return 0;
    return alturaNo(no->esquerda) - alturaNo(no->direita);
}

static NoArvore* rotacaoDireita(NoArvore* y) {
    NoArvore* x = y->esquerda;
    NoArvore* T2 = x->direita;

    x->direita = y;
    y->esquerda = T2;

    y->altura = maxInt(alturaNo(y->esquerda), alturaNo(y->direita)) + 1;
    x->altura = maxInt(alturaNo(x->esquerda), alturaNo(x->direita)) + 1;

    return x;
}

static NoArvore* rotacaoEsquerda(NoArvore* x) {
    NoArvore* y = x->direita;
    NoArvore* T2 = y->esquerda;

    y->esquerda = x;
    x->direita = T2;

    x->altura = maxInt(alturaNo(x->esquerda), alturaNo(x->direita)) + 1;
    y->altura = maxInt(alturaNo(y->esquerda), alturaNo(y->direita)) + 1;

    return y;
}

static NoArvore* inserirNo(NoArvore* no, Livro* livro) {
    if (no == NULL) {
        NoArvore* novoNo = criarNoArvore();
        if (novoNo == NULL) return NULL;
        novoNo->livro = livro;
        novoNo->altura = 0;
        return novoNo;
    }

    if (livro->codigo < no->livro->codigo) {
        no->esquerda = inserirNo(no->esquerda, livro);
    } else if (livro->codigo > no->livro->codigo) {
        no->direita = inserirNo(no->direita, livro);
    } else {
        printf("Erro: Livro com código %d já existe.\n", livro->codigo);
        return no;
    }

    no->altura = maxInt(alturaNo(no->esquerda), alturaNo(no->direita)) + 1;

    int balance = fatorBalanceamento(no);

    // EE
    if (balance > 1 && livro->codigo < no->esquerda->livro->codigo) {
        return rotacaoDireita(no);
    }
    // DD
    if (balance < -1 && livro->codigo > no->direita->livro->codigo) {
        return rotacaoEsquerda(no);
    }
    // ED
    if (balance > 1 && livro->codigo > no->esquerda->livro->codigo) {
        no->esquerda = rotacaoEsquerda(no->esquerda);
        return rotacaoDireita(no);
    }
    // DE
    if (balance < -1 && livro->codigo < no->direita->livro->codigo) {
        no->direita = rotacaoDireita(no->direita);
        return rotacaoEsquerda(no);
    }

    return no;
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
    return arvore->raiz->altura;
}

Arvore* criarArvore() {
    Arvore* novaArvore = malloc(sizeof(Arvore));

    if (novaArvore == NULL) {
        fprintf(stderr, "Erro grave: Falha ao alocar memória para a árvore.\n");
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

    arvore->raiz = inserirNo(arvore->raiz, livro);
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

// helper: encontra nó com menor valor (usado na remoção)
static NoArvore* menorValor(NoArvore* node) {
    NoArvore* cur = node;
    while (cur && cur->esquerda != NULL)
        cur = cur->esquerda;
    return cur;
}

static NoArvore* removerNo(NoArvore* raiz, int codigo) {
    if (raiz == NULL) return NULL;

    if (codigo < raiz->livro->codigo) {
        raiz->esquerda = removerNo(raiz->esquerda, codigo);
    } else if (codigo > raiz->livro->codigo) {
        raiz->direita = removerNo(raiz->direita, codigo);
    } else {
        // nó encontrado
        if (raiz->esquerda == NULL) {
            NoArvore* temp = raiz->direita;
            if (raiz->livro != NULL) free(raiz->livro);
            free(raiz);
            return temp;
        } else if (raiz->direita == NULL) {
            NoArvore* temp = raiz->esquerda;
            if (raiz->livro != NULL) free(raiz->livro);
            free(raiz);
            return temp;
        } else {

            // encontrar o sucessor em-ordem
            NoArvore* temp = menorValor(raiz->direita);

            // salvar o código do sucessor em uma variável segura
            int codigoSucessor = temp->livro->codigo;

            // libera o livro do nó que está sendo removido
            if (raiz->livro != NULL) free(raiz->livro);

            // nó atual recebe livro do sucessor
            raiz->livro = temp->livro;

            // desconecta ponteiro do temp antes de remover
            temp->livro = NULL;

            // remove o sucessor
            raiz->direita = removerNo(raiz->direita, codigoSucessor);
        }
    }

    // atualizar altura
    raiz->altura = maxInt(alturaNo(raiz->esquerda), alturaNo(raiz->direita)) + 1;

    int balanceamento = fatorBalanceamento(raiz);

    // LL
    if (balanceamento > 1 && fatorBalanceamento(raiz->esquerda) >= 0)
        return rotacaoDireita(raiz);

    // LR
    if (balanceamento > 1 && fatorBalanceamento(raiz->esquerda) < 0) {
        raiz->esquerda = rotacaoEsquerda(raiz->esquerda);
        return rotacaoDireita(raiz);
    }

    // RR
    if (balanceamento < -1 && fatorBalanceamento(raiz->direita) <= 0)
        return rotacaoEsquerda(raiz);

    // RL
    if (balanceamento < -1 && fatorBalanceamento(raiz->direita) > 0) {
        raiz->direita = rotacaoDireita(raiz->direita);
        return rotacaoEsquerda(raiz);
    }

    return raiz;
}

void removerLivroArvore(Arvore* arvore, int codigo) {
    if (arvore == NULL) return;
    arvore->raiz = removerNo(arvore->raiz, codigo);
}
