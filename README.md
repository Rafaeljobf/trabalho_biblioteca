# 📖 Trabalho Sistema de Biblioteca 

Simulação de um sistema de biblioteca, possuindo uma Árvore Binária de Busca para armazenar o acervo de livros, utilizando métodos específicos para a manipulação adequada, presentes nos arquivos arvore.c e arvore.h. O sistema também conta com uma fila de espera e um histórico de empréstimos (lista encadeada simples), ambos implementados em seus respectivos arquivos .c e .h.

---

## ✏️ Dados da Equipe 

**Nome da equipe:** Oráculos do Hexa.

**Componentes:** João Miguel Lourinho Nogueira e Rafael José de Oliveira.

---

## 🚩 Descrição Resumida do Sistema

O sistema é organizado em 5 grupos principais:

### 1. Livro (livro.h e livro.c)

É o coração do sistema, nela estão presentes todas as configurações envolvendo livros, desde a definição da struct (livro.h), até a implementação de métodos de busca, remoção e métodos de acesso aos campos da struct. Nele também está presente funções auxiliares da lógica de empréstimo e devolução.

### 2. Árvore (arvore.h e arvore.c)

De longe o método mais complexo e fundamental para o armazenamento correto de exemplares. Nele estão presentes a definição da árvore e dos seus nós (arvore.h) e métodos de acesso, modificação (rotações), busca, remoção e, no geral, tudo que é necessário para o funcionamento correto da estrutura de dados e sua manipulação. Também estão presentes métodos de listagem para as funcionalidades na função principal.

### 3. Fila (fila.h e fila.c)

Novamente, o armazenamento da struct está no arquivo fila.h e lá também as funções principais estão previamente declaradas. Nesse grupo, há a lógica do funcionamento da lista de espera, possuindo operações de manipulação, organização e de exibições, essencial para determinadas funções do sistema estabelecidos no documento do trabalho.

### 4. Lista (lista.h e lista.c)

É o menor grupo, mas nem por isso, deixa de ser importante, nele estão as declarações da struct e das funções principais (lista.h), e a implementação das funções e a declaração e implementação de métodos auxiliares (lista.c). Ele possui métodos extremamente úteis, com destaque para as opções 6 e 7 do sistema.

### 5. Main (main.c)

A função mais importante de todo o sistema, ela é o orquestador de todos os outros grupos, determinando o fluxo de operação do sistema. Nela, são utilizadas todas as funções estabelecidas previamente, sendo elas implementadas em um grande switch case, com cada opção contendo uma única ou uma combinação de funções implementadas em arquivos distintos. Nela há todo o tratamento de exceção, quando não está presente no código, está encapsulado dentro das declarações.

---

## ⚙️ Instruções para a Compilação

No geral, é uma etapa muito simples, basta rodar o seguinte código no terminal:

```bash
gcc main.c livro.c arvore.c fila.c lista.c -o biblioteca
```

---

## 🚀 Instruções para a Execução

Novamente, é um comando simples, rode-o no terminal:

```bash
./biblioteca
```

---

## 📝 Exemplos de Uso

---

## 🔎 Observações sobre as Funcionalidades Implementadas

---

## ⚠️ Limitações Conhecidas