#include "arvore.h"
#include "livro.h"

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

// Funções auxiliares de listagem em pre ordem, ordem e pos ordem

// (esquerda -> raiz -> direita)
static void emOrdemNo(NoArvore* raiz) {
    if (raiz != NULL) {
        emOrdemNo(raiz->esquerda);
        exibirLivro(raiz->livro);
        emOrdemNo(raiz->direita);
    }
}

// (raiz -> esquerda -> direita)
static void preOrdemNo(NoArvore* raiz) {
    if (raiz != NULL) {
        exibirLivro(raiz->livro);
        preOrdemNo(raiz->esquerda);
        preOrdemNo(raiz->direita);
    }
}

// (esquerda -> direita -> raiz)
static void posOrdemNo(NoArvore* raiz) {
    if (raiz != NULL) {
        posOrdemNo(raiz->esquerda);
        posOrdemNo(raiz->direita);
        exibirLivro(raiz->livro);
    }
}


// Função auxiliar de criação de Nó
/* Cria um novo nó da árvore, inicializando ponteiros e altura.
   Retorna NULL se a alocação falhar. Não associa o Livro aqui;
   o chamador deve atribuir novoNo->livro após a criação. */
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

// Função auxiliar de contagem de livros
static int contarNosRecursivo(NoArvore* no) {
    if (no == NULL) {
        return 0;
    }

    return 1 + contarNosRecursivo(no->esquerda) + contarNosRecursivo(no->direita);
}

// Funções auxiliares de balanceamento

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
    /* Rotação à direita: eleva o filho esquerdo (x) e reencaixa y como
       filho direito de x. Atualiza alturas de y e x. Preserva ordem in-order. */
    NoArvore* x = y->esquerda;
    NoArvore* T2 = x->direita;

    x->direita = y;
    y->esquerda = T2;

    y->altura = maxInt(alturaNo(y->esquerda), alturaNo(y->direita)) + 1;
    x->altura = maxInt(alturaNo(x->esquerda), alturaNo(x->direita)) + 1;

    return x;
}

static NoArvore* rotacaoEsquerda(NoArvore* x) {
    /* Rotação à esquerda: eleva o filho direito (y) e reencaixa x como
       filho esquerdo de y. Atualiza alturas de x e y. Preserva ordem in-order. */
    NoArvore* y = x->direita;
    NoArvore* T2 = y->esquerda;

    y->esquerda = x;
    x->direita = T2;

    x->altura = maxInt(alturaNo(x->esquerda), alturaNo(x->direita)) + 1;
    y->altura = maxInt(alturaNo(y->esquerda), alturaNo(y->direita)) + 1;

    return y;
}

static NoArvore* inserirNo(NoArvore* no, Livro* livro, int* inserido) {
    /* Insere recursivamente um Livro na subárvore apontada por 'no'.
       Mantém propriedades de árvore AVL: atualiza alturas e aplica rotações
       quando necessário. Retorna o novo ponteiro raiz da subárvore.
       Usa 'inserido' para indicar sucesso ou falha sem perder subárvores. */
    if (no == NULL) {
        NoArvore* novoNo = criarNoArvore();
        if (novoNo == NULL) {
            *inserido = 0;
            return NULL;
        }
        novoNo->livro = livro;
        novoNo->altura = 0;
        *inserido = 1;
        return novoNo;
    }

    if (livro->codigo < no->livro->codigo) {
        no->esquerda = inserirNo(no->esquerda, livro, inserido);
    } else if (livro->codigo > no->livro->codigo) {
        no->direita = inserirNo(no->direita, livro, inserido);
    } else {
        printf("Erro: Livro com código %d já existe.\n", livro->codigo);
        *inserido = 0;
        return no;
    }

    if (!*inserido) {
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


// Funções principais

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

/* Aloca e inicializa uma nova estrutura de árvore.
   Em caso de falha na alocação, termina o programa com erro crítico. */
Arvore* criarArvore() {
    Arvore* novaArvore = malloc(sizeof(Arvore));

    if (novaArvore == NULL) {
        fprintf(stderr, "Erro grave: Falha ao alocar memória para a árvore.\n");
        exit(EXIT_FAILURE);
    }

    novaArvore->raiz = NULL;

    return novaArvore;
}

/* Insere um Livro na árvore pública. Retorna 1 em sucesso, 0 em falha.
   Possíveis falhas: ponteiros inválidos, duplicata (já existe código) ou
   falha de memória durante inserção. */
int inserirLivroArvore(Arvore* arvore, Livro* livro) {
    if (arvore == NULL || livro == NULL) {
        printf("ERRO: Dados inválidos!");
        return 0; // dados inválidos
    }

    int inserido = 0;
    arvore->raiz = inserirNo(arvore->raiz, livro, &inserido);
    return inserido;
}

/* Busca iterativamente um Livro pelo código na árvore.
   Percorre como em uma busca binária: à esquerda se menor, à direita se maior.
   Retorna ponteiro para o Livro se encontrado, ou NULL caso contrário. */
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

/* Retorna o nó com o menor valor (mais à esquerda) na subárvore.
   Útil para encontrar o sucessor in-order durante remoção. */
static NoArvore* menorValor(NoArvore* node) {
    NoArvore* cur = node;
    while (cur && cur->esquerda != NULL)
        cur = cur->esquerda;
    return cur;
}

/* Remove recursivamente o nó com 'codigo' na subárvore.
   Casos:
   - Nó folha ou com um único filho: libera a memória do Livro (se houver)
     e do nó, retornando o filho (ou NULL).
   - Nó com dois filhos: encontra o sucessor in-order (menor da direita),
     copia os dados do Livro do sucessor para o nó atual e remove o sucessor
     recursivamente.
   Após remoção, atualiza alturas e aplica rotações para manter o balanceamento AVL.
*/
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
            liberarLivro(raiz->livro);
            free(raiz);
            return temp;
        } else if (raiz->direita == NULL) {
            NoArvore* temp = raiz->esquerda;
            liberarLivro(raiz->livro);
            free(raiz);
            return temp;
        } else {

            // encontrar o sucessor em-ordem
            NoArvore* temp = menorValor(raiz->direita);

            // salvar o código do sucessor em uma variável segura
            int codigoSucessor = temp->livro->codigo;

            // copia os dados do sucessor para o nó atual
            *(raiz->livro) = *(temp->livro);

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
