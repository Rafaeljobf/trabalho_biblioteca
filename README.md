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

**Cadastrando um livro:**

```
Escolha uma opcao: 1
Codigo: 101
Titulo: O Senhor dos Anéis
Autor: J.R.R. Tolkien
Ano de Publicacao: 1954
Quantidade Total de Exemplares: 2

Livro cadastrado com sucesso.
```

**Realizando um empréstimo com fila de reserva:**

```
Escolha uma opcao: 6
Nome do usuario: João
Codigo do livro: 101

Emprestimo realizado com sucesso.

Escolha uma opcao: 6
Nome do usuario: Maria
Codigo do livro: 101

Nao ha exemplares disponiveis.
Deseja entrar na fila de reservas? (1 = Sim / 0 = Nao): 1

Reserva realizada com sucesso.
```

**Devolvendo com atendimento automático da fila:**

```
Escolha uma opcao: 7
Codigo: 101

Livro devolvido com sucesso.
Ha usuarios aguardando esse livro na fila de reservas.
Atendendo o primeiro da fila: Maria
Emprestimo automatico realizado para Maria!
```

---

## 🔎 Observações sobre as Funcionalidades Implementadas

Todas as funcionalidades obrigatórias do sistema foram implementadas com sucesso. Além disso, algumas funcionalidades extras foram desenvolvidas como diferencial:

- **Remoção de livro da árvore:** implementada com rebalanceamento AVL completo, garantindo que a árvore permaneça balanceada após qualquer remoção. Essa é uma das funcionalidades mais complexas do trabalho e foi tratada com cuidado para cobrir todos os casos — nó folha, nó com um filho e nó com dois filhos, usando o sucessor em-ordem.
- **Atendimento automático da fila de reservas na devolução:** ao devolver um livro, o sistema verifica automaticamente se há usuários aguardando na fila e realiza o empréstimo para o primeiro da fila, registrando também no histórico.
- **Liberação adequada de memória:** ao encerrar o sistema pela opção 0, toda a memória alocada dinamicamente é liberada corretamente.

---

## ⚠️ Limitações Conhecidas

- **Fila global de reservas:** a fila de reservas é única para todos os livros, e cada reserva armazena o código do livro correspondente. No atendimento automático da devolução, o sistema percorre a fila em busca da primeira reserva referente ao livro devolvido. Porém, a remoção da fila sempre retira o elemento do início — ou seja, se houver reservas de livros diferentes antes da reserva do livro devolvido, o usuário removido pode não ser o correto. Para o escopo do trabalho isso é aceitável, mas uma solução mais robusta exigiria uma função de remoção por posição na fila.
- **Busca apenas por código:** o sistema não permite busca por título ou autor, apenas pelo código do livro.
- **Sem persistência de dados:** os dados não são salvos em arquivo, então ao encerrar o programa todas as informações são perdidas.