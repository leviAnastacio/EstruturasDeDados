# Árvore Binária de Busca 

Esta é a implmentação de uma Árvore binária de busca (ABB) em linguagem C. Esta estrutura de dados possui certas propriedades para manter seus nós ligados entre si e garantir características peculiares acerca de suas definições.

## Propriedades

**1.** Todo nó em uma ABB possui um chave (id), que serve para facilitar a operação de busca;

**2.** Todo nó na árvore pode ou não possuir nós-filhos, caso possua filhos os nós à esquerda de determinado nó v sempre possuirão chaves cujo valor será menor ou igual ao valor da chave desse nó v. E os nós à direita já possuirão chaves de valor maior ou igual ao valor da chave de v.

**->** v.esquerda.chave ≤ v.chave ≤ v.direita.chave


## Descrição do código

O código está organizado de modo a englobar as principais operações do algoritmo da Árvore binária de busca, tais como: ***Inserção***, ***Remoção***, e ***Busca***. O código possui, também a implementação de "funções-extra", que foram implementadas afim de estruturar um CRUD simples de um sistema de armazenamento de dados de alunos de uma universidade, tomando como base a matrícula do aluno como chave na ABB. Assim código possui as seguintes funcionalidades utilizando das funções bases da ABB: ***Cadastrar aluno***, ***Excluir um aluno***, ***ALterar dados de um aluno***, ***Buscar dados de um aluno***. Além disso, o tipo definido "ALUNO" presente no código, conta com um atributo do tipo definido "DISCIPLINA", que se trata de um vetor que armazenará um número x de disciplinas cursadas por esse aluno, e quando os dados forem buscados e apresentados, as disciplinas serão printadas de modo ordenado, apresentadas da maior nota final até a menor (organizadas de modo decrescente de notas finais).

## Compilação e Execução

Para compilar o código, esteja ciente da necessidade de instalação de um compilador para a linguagem C, e logo após isso, basta abrir o arquivo no terminal e aplicar o seguinte comando: 

```bash
gcc <nome_do_arquivo>.c -o ABB_ALUNOS
```

Para rodar o código, execute o seguinte comando:

```bash
./ABB_ALUNOS
```

