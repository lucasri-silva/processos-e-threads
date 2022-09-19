<h1 align="center">SO - Processos e Threads</h1>

<h3 align ="center">Escalonamento e Gestão de Memória Primária</h3>

Trabalho da disciplina Sistemas Operacionais. A atividade propõe a construção de um sistema de classificação cujas características nos permitirão observar os conceitos de Escalonamento e Gestão de Memória Primária. Neste sistema, vamos considerar duas bases de dados D e T. A base D será utilizada para simular a inicialização, fornecendo assim o conceito de bootstrapping, tal como no sistema operacional. A base T representará os processos a serem executados.

<p>| OS: Ubuntu 22.04.1 LTS | Compilador: gcc version 11.2.0 |</p>
                
                
     - Para executar abra o diretório do arquivo desejado e execute o MakeFile.

        ./make
        ./make run

<h4 align ="left">Etapa I</h4>

<p>A primeira etapa constitui na elaboração das tabelas hash para itens e classes a partir do arquivo D. Dada uma linha do arquivo D, consideraremos item as colunas de 0 a n - 1 e classe a coluna n. Os itens serão armazenados na hash "itens", no qual a chave será representada por (coluna, decimal) e o valor será representado pelos índices de todas as linhas que contém o decimal. Dessa forma, para itens de mesmo valor, a indexação ocorrerá da seguinte maneira: se um item aparece na coluna 1 e 3 com valor 23.4, consideraremos como chave da hash (1, 23.4) e (3,23.4), respectivamente. De maneira análoga, a classe será armazenada na hash "classes", no qual a chave será representada por (descrição) e o valor será representado por suas indexações.</p>


<h4 align ="left">Etapa II</h4>

<p>A segunda etapa constitui na leitura do arquivo T, geração dos itens de T e em sua comparação com o itens criado na etapa anterior. Inicialmente, o conteúdo de T será armazenado na fila "processos" em que cada posição detém uma linha inteira do arquivo. Para cada valor decimal presente na linha esse deve ser armazenado junto a sua coluna correspondente (semelhante a chave de itens). Em seguida, será feito a comparação dos itens de T com a tabela hash de itens, do arquivo D. Os itens comuns entre eles serão armazenados no vector "commonItens". Feito isso, será realizado a combinação dos itens comuns de 1 a N, sendo armazenados no arquivo "combinations.txt".</p>
