#include "fila.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Fila* criarFila() {
    Fila* fila = malloc(sizeof(Fila));
    if (fila == NULL) return NULL;
    fila->inicio = NULL;
    fila->fim = NULL;
    return fila;
}

int filaVazia(Fila* fila) {
    if (fila == NULL || fila->inicio == NULL) {
        return 1; // vazia
    }
    return 0; // não vazia
}

// função auxiliar de criação de nós
NoFila* criarNoFila() {
    NoFila* novoNo = (NoFila*) malloc(sizeof(NoFila));
    if (novoNo == NULL) {
        printf("Erro de alocação de memória na fila.\n");
        return NULL;
    }
    return novoNo;
}

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

Reserva desenfileirarReserva(Fila* fila) {
    Reserva reservaVazia = {"", -1};

    if (fila == NULL || filaVazia(fila)) {
        printf("Fila de reservas está vazia.\n");
        return reservaVazia;
    }

    NoFila* temp = fila->inicio;
    
    Reserva reservaRecuperada = temp->reserva;

    fila->inicio = fila->inicio->prox;

    if (fila->inicio == NULL) {
        fila->fim = NULL;
    }

    free(temp);

    return reservaRecuperada;
}

void exibirReservas(Fila* fila) {
    if (fila->inicio == NULL) {
        printf("Nenhuma reserva registrada na fila global.\n");
        return;
    }

    NoFila* atual = fila->inicio;
    printf("\n--- FILA GLOBAL DE RESERVAS ---\n");
    int pos = 1;
    while (atual != NULL) {
        printf("%d. Usuário: %s | Código do Livro: %d\n",
               pos++, atual->reserva.nomeUsuario, atual->reserva.codigoLivro);
        atual = atual->prox;
    }
    printf("-------------------------------\n");
}
