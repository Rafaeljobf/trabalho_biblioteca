#include "fila.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Aloca uma fila vazia e inicializa o ponteiro inicial.
Fila* criarFila() {
    Fila* fila = malloc(sizeof(Fila));
    if (fila == NULL) return NULL;
    fila->inicio = NULL;
    fila->fim = NULL;
    return fila;
}

// Retorna 1 se a fila for nula ou não tiver nós; caso contrário, retorna 0.
int filaVazia(Fila* fila) {
    if (fila == NULL || fila->inicio == NULL) {
        return 1; // vazia
    }
    return 0; // não vazia
}

// Função auxiliar de criação de nós
NoFila* criarNoFila() {
    NoFila* novoNo = (NoFila*) malloc(sizeof(NoFila));
    if (novoNo == NULL) {
        printf("Erro de alocação de memória na fila.\n");
        return NULL;
    }
    return novoNo;
}

// Função usada para enfileirar os dados.
void enfileirarReserva(Fila* fila, Reserva reserva) {
    if (fila == NULL) return;

    NoFila* novoNo = criarNoFila();
    if (novoNo == NULL) return; 

    // Copia os dados da reserva de forma segura
    novoNo->reserva.codigoLivro = reserva.codigoLivro;
    strncpy(novoNo->reserva.nomeUsuario, reserva.nomeUsuario, 99);
    novoNo->reserva.nomeUsuario[99] = '\0';
    novoNo->prox = NULL;

    // Lógica FIFO (First In, First Out)
    if (filaVazia(fila)) {
        fila->inicio = novoNo;
        fila->fim = novoNo;
    } else {
        fila->fim->prox = novoNo;
        fila->fim = novoNo;
    }
}

// Remove e retorna o primeiro elemento da fila (política FIFO).
// Caso a fila esteja vazia, retorna uma reserva com valores padrão.
Reserva desenfileirarReserva(Fila* fila) {
    Reserva reservaVazia = {"", -1};

    if (fila == NULL || filaVazia(fila)) {
        printf("Fila de reservas está vazia.\n");
        return reservaVazia;
    }

    NoFila* temp = fila->inicio;
    
    Reserva reservaRecuperada = temp->reserva; // salva os dados antes de liberar

    fila->inicio = fila->inicio->prox; // avança o início para o próximo nó

    if (fila->inicio == NULL) {
        fila->fim = NULL; // fila ficou vazia, atualiza o fim também
    }

    free(temp);

    return reservaRecuperada;
}

// Remove e retorna a primeira reserva da fila que corresponde ao código do livro informado.
// Diferente de desenfileirarReserva, não remove necessariamente o início da fila —
// percorre os nós até encontrar a reserva correta, mantendo a ordem dos demais.
// Caso não encontre nenhuma reserva com o código informado, retorna uma reserva com valores padrão.
Reserva removerReservaPorCodigo(Fila* fila, int codigoLivro) {
    Reserva reservaVazia = {"", -1};

    if (fila == NULL || filaVazia(fila)) {
        return reservaVazia;
    }

    NoFila* anterior = NULL;
    NoFila* atual = fila->inicio;

    while (atual != NULL && atual->reserva.codigoLivro != codigoLivro) {
        anterior = atual;
        atual = atual->prox;
    }

    if (atual == NULL) {
        return reservaVazia;
    }

    Reserva reservaRecuperada = atual->reserva;

    if (anterior == NULL) {
        fila->inicio = atual->prox; // reserva estava no início da fila
    } else {
        anterior->prox = atual->prox; // reserva estava no meio ou fim, reconecta os nós
    }

    if (fila->fim == atual) {
        fila->fim = anterior;
    }

    free(atual);

    return reservaRecuperada;
}

// Percorre a fila e exibe todas as reservas com sua posição, usuário e código do livro.
void exibirReservas(Fila* fila) {
    if (fila->inicio == NULL) {
        printf("Nenhuma reserva registrada na fila global.\n");
        return;
    }

    NoFila* atual = fila->inicio;
    printf("\n--- FILA GLOBAL DE RESERVAS ---\n");
    int pos = 1;
    while (atual != NULL) {
        printf("%d. Usuario: %s | Codigo do Livro: %d\n",
               pos++, atual->reserva.nomeUsuario, atual->reserva.codigoLivro);
        atual = atual->prox;
    }
    printf("-------------------------------\n");
}
