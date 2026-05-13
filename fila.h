#ifndef TRABALHO_BIBLIOTECA_FILA_H
#define TRABALHO_BIBLIOTECA_FILA_H

typedef struct {
    char nomeUsuario[100];
    int codigoLivro;
} Reserva;

typedef struct NoFila {
    Reserva reserva;
    struct NoFila* prox;
} NoFila;

typedef struct Fila {
    NoFila* inicio;
    NoFila* fim;
} Fila;

Fila* criarFila();

void enfileirarReserva(Fila* fila, Reserva reserva);

Reserva desenfileirarReserva(Fila* fila);

int filaVazia(Fila* fila);

void exibirReservas(Fila* fila);

#endif //TRABALHO_BIBLIOTECA_FILA_H
