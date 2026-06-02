#ifndef TRABALHO_BIBLIOTECA_LIVRO_H
#define TRABALHO_BIBLIOTECA_LIVRO_H

typedef struct {
    int codigo;
    char titulo[100];
    char autor[100];
    int ano;
    int quantidadeTotal;
    int quantidadeDisponivel;
} Livro;

Livro* criarLivro (int codigo, char titulo [], char autor [], int ano, int quantidadeTotal);

void exibirLivro(Livro* livro);

int obterCodigoLivro(Livro* livro);

int obterQuantidadeDisponivel(Livro* livro);

void emprestarExemplar(Livro* livro);

void devolverExemplar(Livro* livro);

#endif //TRABALHO_BIBLIOTECA_LIVRO_H
