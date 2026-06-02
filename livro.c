#include "livro.h"

#include <stdio.h>

void exibirLivro(Livro* livro) {
    printf("[ID: %04d] %-30s | Autor: %-20s | Ano: %d | Total: %d | Disp: %d\n",
           livro->codigo,
           livro->titulo,
           livro->autor,
           livro->ano,
           livro->quantidadeTotal,
           livro->quantidadeDisponivel);
}