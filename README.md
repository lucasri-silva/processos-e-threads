<h1 align="center">SO - Processos e Threads</h1>

<h3 align ="center">Escalonamento e Gestão de Memória Primária</h3>

<p align="justify">Trabalho da disciplina Sistemas Operacionais. A atividade propõe a construção de um sistema de classificação cujas características nos permitirão observar os conceitos de Escalonamento e Gestão de Memória Primária. Neste sistema, vamos considerar duas bases de dados D e T - ambas se referem ao famoso Iris dataset utilizado em análise exploratória de dados. A base D será utilizada para simular a inicialização, fornecendo assim o conceito de bootstrapping, tal como no sistema operacional. A base T representará os processos a serem executados.</p>

<h2 align="left">Compilação e Execução</h2>

- OS: Ubuntu 22.04.1 LTS | Compilador: g++ version 11.2.0

- Para executar abra o diretório do arquivo desejado e execute o MakeFile.

| Comando    | Função                                                                                  |
| ---------- | --------------------------------------------------------------------------------------- |
| make clean | Apaga a última compilação realizada contida na pasta bin                                |
| make       | Executa a compilação do programa utilizando o g++, e o resultado vai para a pasta bin   |
| make run   | Executa o programa da pasta bin após a realização da compilação                         |
                
<h2 align ="left">Etapa I</h2>

<p align="justify">A primeira etapa constitui na elaboração das tabelas hash para itens e classes a partir do arquivo D. Dada uma linha do arquivo D, consideraremos item as colunas de 0 a n - 1 e classe a coluna n. Os itens serão armazenados na hash <code>itensD</code>, no qual a chave será representada por (coluna, medida) e o valor será representado pelos índices de todas as linhas onde a chave aparece. Para itens de mesmo valor, a indexação ocorrerá da seguinte maneira: se um item aparece na coluna 1 e 3 com valor 23.4, consideraremos como chave da hash (1, 23.4) e (3,23.4), respectivamente. De maneira análoga, a classe será armazenada na hash "classes", no qual a chave será representada por (espécie) e o valor será representado por suas indexações.</p>

| ![e1-itensD.png](./images/e1-itensD.png?width="400") | 
|:--:| 
| Imagem representa a hash itens, do arquivo D. |

| ![e1-classes.png](./images/e1-classes.png?width="400") | 
|:--:| 
| Imagem representa a hash classes, do arquivo D. |

<h2 align ="left">Etapa II</h2>

<p align="justify">Na segunda etapa é realizado a leitura do arquivo T, geração dos itens de T e em sua comparação com o itens criado na etapa anterior. Inicialmente, o conteúdo de T será armazenado na fila <code>itensT</code>, em que cada posição armazena uma linha inteira do arquivo T. Para cada valor decimal presente na linha esse deve ser armazenado junto a sua coluna correspondente (semelhante a chave de itens). Em seguida, é feito a comparação dos itens de T com a tabela hash de itens, do arquivo D. Os itens comuns entre eles serão armazenados no vector <code>commonItens</code>. Feito isso, para toda linha em commonItens é realizada a combinação entre seus elementos, sendo armazenados no arquivo "combinations.txt".</p>

| ![e2-itensT.png](./images/e2-itensT.png?width="400") | 
|:--:| 
| Imagem representa a fila itensT. Cada posição da fila armazena uma linha do arquivo T, que corresponde às chaves (coluna, medida). |

| ![e2-intersectionDeT.png](./images/e2-intersectionDeT.png?width="400") | 
|:--:| 
| Imagem representa o vetor commonItens gerado a partir da interseção dos itens D e T. |

| ![e2-combinations.png](./images/e2-combinations.png?width="400") | 
|:--:| 
| Arquivo com combinações geradas do vetor commonItens. Note que as combinações representadas acima correspondem a primeira linha do vetor commonItens (imagem acima). | 

<h2 align ="left">Etapa III</h2>

<p align="justify">Na terceira etapa, para cada conjunto de combinação gerado é realizada a busca na hash itens. Em seguida, para cada valor encontrado é realizada a interseção, gerando um vetor de interseção. Por fim, é realizada novamente a interseção do vetor de interseção com os valores de cada classe, computando o tamanho da interseção entre eles à classe em questão. Após o processamento a classe que apresentar um valor de sobreposição maior será apresentada como classe da tarefa em T.</p>

* Exemplo:

![e3-combinations-example.png](./images/e3-combinations-example.png?width="400")

- Considerando o conjunto de combinações, do arquivo "combinations.txt", na imagem acima, temos as seguintes chaves e valores:
  -  <code>(1, 5.1) : 23 77 90 92 97</code>
  -  <code>(2, 3.5) : 17 77 95</code>
  -  <code>(3, 1.4) : 11 13 31 72 77 82 85 88</code>
  -  <code>(4, 0.2) : 6 10 11 13 17 30 31 39 48 56 60 68 78 82 83 84 88 90 94 97</code>
  
<p align="justify">As chaves (1, 5.1)(2, 3.5)(3, 1.4)(4, 0.2) estão presentes em alguma linha do vetor "commonItens". Essas chaves geram um total de 15 combinações. Para combinações com apenas uma chave é realizado a interseção direta entre seu valor com as classes. Para combinações com mais de uma chave, por outro lado, é realizado primeiramente a interseção entre os valores das chaves para, em seguida, ser realizado a interseção do vetor interseção com os valores das classes.</p>
  
<p align="justify">Dessa forma, para as combinações (3, 1.4)(4, 0.2) temos o vetor de interseção <code>11 13 31 82 88</code> e para as combinações (1, 5.1)(2, 3.5)(3, 1.4) temos o vetor de interseção <code>77</code>. Assim que o vetor de interseção é gerado é chamada a função <code>computeClassIntersection</code>, que, por sua vez, recebe como parâmetro o vetor de interseção. Essa função então realiza a interseção do vetor de interseção com os valores das classes, computando o tamanho da nova interseção às seguintes variáveis: </p>
  
  - <code>unsigned int irisVersicolor = 0;</code>
  - <code>unsigned int irisVirginica = 0;</code>
  - <code>unsigned int irisSetosa = 0;</code>
  
<p align="justify">No fim de cada interseção do vetor de interseção com os valores das classes o vetor é limpado. As computações das variáveis classes, por sua vez, são acumulativas. Ao final é imprimido na tela a classe com maior número de sobreposições.</p>

| ![e3-sobreposicao.png](./images/e3-sobreposicao.png?width="400") | 
|:--:| 
| Resultado da interseção entre o vetor de interseção, gerado a partir da interseção das combinações, e os valores de cada classe. Podemos notar que a Iris-setosa obteve o maior número de interseções (573) entre as classes. |

<h2 align ="left">Etapa IV</h2>

<p align="justify">Essa etapa tem como objetivo a elaboração de um cache para armazenar o resultado das interseções já realizadas, de modo que para cada nova combinação é feita primeiramente a verificação se o resultado da interseção já foi processado, isto é, se o resultado está em cache. Em caso afirmativo, o resultado da interseção é retirado da cache para, em seguida, ser realizado sua interseção com as classes.</p>

* Exemplo:

<code>(3, 1.5) : 1 8 10 23 51 58 60 87 90</code>
<br><code>(4, 0.1) : 8 51 55 85 87</code>

<p align="justify">Para as combinações acima a hash terá como chave (3, 1.5)(4, 0.1) e valor a interseção dessas combinações, que será <code>8 51 87</code>. Dessa forma, caso existir uma nova ocorrência dessas combinações no futuro o resultado da interseção será buscado em cache - em vez de ser recomputado.</p>


| ![e4-cache.png](./images/e4-cache.png?width="400") | 
|:--:| 
| Hash cache criada para armazenar o resultado das interseções entre as combinações. |

<h2 align ="left">Etapa V</h2>

<p align="justify">Essa etapa propõe a criação de uma política que organize melhor as tarefas em T para que a sequência de execução aproveite melhor as computações realizadas, isto é, para que a cache seja melhor utilizada.</p>

<h4 align="left">Antiga Política</h4>

<p align="justify">Podemos dizer que a antiga política de escalonamento é FCFS (First-Come, First-Served), uma vez que não há nenhum critério de organização da ordem de execução das tarefas (combinações), isto é, à medida que as tarefas chegam elas são adicionadas na última posição (tail) do vetor <code>combinations</code>. Uma vez na CPU o processo não pode ser interrompido. A simplicidade dessa política impossibilita a otimização do grau de sobreposição das tarefas e a redução do número de computações a serem realizadas.</p>

<h4 align="left">Nova Política</h4>

<p align="justify">Para melhor organizar as tarefas em T o vetor que armazena as combinações foi reestruturado. A estrutura anterior do vetor <code>combinations</code> armazenava as combinações de forma desordenada, com as tarefas variando de tamanho de 1 à 4 (representado pela quantidade de keys). Na nova política, o vetor combinações é um vetor de vetores com a seguinte forma <code>combinations(numberOfColumns - 1)</code>. A nova estrutura organiza as combinações por tamanho. O vetor <code>combinations</code> tem tamanho do número de colunas da base de dados T - 1 (exclui-se a coluna que contém as classes). Para cada posição do vector é armazenado um tamanho de combinação, como pode ser observado na imagem abaixo.</p>

| ![e5-new-combinations.png](./images/e5-new-combinations.png?width="400") | 
|:--:| 
| Nova estrutura do vetor combinations. |

<p align="justify">A nova estrutura é interessante pois ao computar as interseções entre as keys de uma combinação e as classes iremos começar pelas de menor tamanho, ou seja, pelas combinações armazenadas na posição 0 do vetor <code>combinations</code>. As combinações com tamanho 1 apresentam, em geral, maior valor de sobreposição com as classes quando comparado as demais. Outra vantagem de começar a realizar as interseções pelas combinações de menor tamanho para as de maiores tamanho é que à medida que computamos os valores das combinações será possível verificar se determinada combinação terá ou não interseção a partir da verificação em cache das keys que a compõe. Em caso da possibilidade de haver interseção entre as keys que compõem a combinação ainda será possível reduzir o custo das interseções entre elas através da busca em cache.</p>

<p align="justify">Considerando as características da nova política de várias filas, representadas pelas posições do vetor <code>combinations</code>, e sua ordem de execução baseada no tamanho das combinações, podemos dizer que o novo algoritmo de escalonamento é do tipo Múltiplas Filas. A prioridade de execução entre as filas é dada pelo tamanho das combinações que elas armazenam, sendo combinação de tamanho 1 a de maior prioridade. Cada fila implementa FIFO como política interna.</p>

<h4 align="left">Detalhes da Nova Política</h4>

Temos os seguintes cenários:

- <p align="justify">Dada a combinação de tamanho 1 <code>1, 4.9|</code>, se essa for sua primeira ocorrência, então sua key <code>(1, 4.9)</code> e seu valor serão armazenados em cache, do contrário ela será buscada diretamente em cache.</p>

- <p align="justify">Dada a combinação de tamanho 2 <code>1, 4.9|2, 3.1|</code>, se essa for sua primeria ocorrência, então sua key <code>(1, 4.9)(2, 3.1)</code> e o valor da interseção dessas keys será armazenado em cache, do contrário ela será buscada diretamente em cache.</p>

- <p align="justify">Dada a combinação de tamanho 3 <code>1, 4.9|2, 3.1|3, 1.5|</code>, primeiramente será buscado em cache a subkey <code>(1, 4.9)(2, 3.1)</code>. Se o valor de interseção da subkey for maior que zero, isto é, se houver interseção, então o valor dessa interseção será armazenada no vetor <code>intersectionKeysValues</code> para, em seguida, ser feito sua interseção com a última componente da combinação, a key <code>(3, 1.5)</code>. Por outro lado, se o valor da interseção da subkey <code>(1, 4.9)(2, 3.1)</code> for zero, então podemos afirmar que a interseção da combinação é zero, não sendo portanto necessário realizar essa computação.</p>

- <p align="justify">Dada a combinação de tamanho 4 <code>1, 4.9|2, 3.1|3, 1.5|4, 0.1|</code>, primeiramente será buscado em cache a subkey <code>(1, 4.9)(2, 3.1)</code>. Seguindo a lógica acima, se houver interseção da subkey, então seu valor será armazenado no vetor <code>intersectionKeysValues</code>. Em seguida será buscada a próxima subkey <code>(1, 4.9)(2, 3.1)(3, 1.5)</code>. Houvendo interseção dessa subkey, então seu valor será sobrescrito no vetor. Por último, é realizada a busca da key que compõe toda a combinação <code>(1, 4.9)(2, 3.1)(3, 1.5)(4, 0.1)</code>. Se a key já existir em cache seu valor será buscado diretamente, do contrário será realizado a interseção do vetor <code>intersectionKeysValues</code>, que armazena a interseção da subkey <code>(1, 4.9)(2, 3.1)(3, 1.5)</code> com a última componente da combinação, <code>(4, 0.1)</code>. Note que para qualquer subkey que não apresentar interseção podemos concluir que não haverá interseção para a key completa, reduzindo assim custos computacionais.</p>

<h4 align="left">Comparação Entre as Políticas</h4>

<p align="justify">Na antiga política as tarefas em T estavam espalhadas, não havia nenhuma lei de separação entre os diferentes tamanhos das combinações, nem na ordem de realização das interseções. Além do mais, havia somente a busca completa da key em cache - não havia a possibilidade da verificação prévia de interseção através da quebra da key em subkeys e aproveitamento do valor de interseção das subkeys. A nova política busca corrigir os problemas mencionados, o que resultou em uma maior sobreposição das tarefas e uma diminuição da computação de interseções consequência do aumento de busca em cache.</p>

| ![e5-comparacao-politicas.png](./images/e5-comparacao-politicas.png?width="400") | 
|:--:| 
| Resultado da alteração na política. Houve um maior número de busca em cache (536) na implementação da nova política. |

<p align="justify">Foi realizado também uma medição de tempo de execução do algoritmo com as diferentes políticas. Realizou-se a média do tempo de execução de 100 execuções de cada política, obtendo os valores abaixo. A partir dos dados é possível concluir que houve uma diminuição no tempo de execução correspondente a 29,8%.</p>

- Tempo médio de execução Antiga Política: 7768 microsegundos
- Tempo médio de execução Nova Política: 5448 microsegundos

<p align="justify">Obs.: Os números finais de sobreposição das classes teve uma pequena divergência como pode ser observado.</p>

<h2 align ="left">Etapa VI</h2>

<p align="justify">A última etapa do projeto propõe a implementação de uma memória primária para chavear processos. Nesse modelo, dado um limite de tempo de execução para uma tarefa, as tarefas que não concluirem por completo sua execução dentro do limite estabelecido serão colocadas em um espaço de memória para aguardar nova submissão.</p>

<h4 align="left">Implementação da Memória Primária</h4>

<p align="justify">Para a implementação da memória primária foi criado a <code>struct Process</code> e uma <code>fila de struct Process</code>. A struct armazena as variáveis necessárias para a retomada da execução da tarefa que não concluiu sua execução no teto estabelecido. Nela são armazenadas as variáveis <code>string task</code> e <code>int priority</code>. A variável <code>task</code> armazena a combinação (key) que será interseccionada com as classes e a variável <code>priority</code> representa seu nível de prioridade.</p>

| ![e6-struct-process.png](./images/e6-struct-process.png?width="400") | 
|:--:| 
| Struct Process. |

<p align="justify">Para determinar o tempo limite de execução para uma tarefa foi realizado a medição do tempo médio de execução individual de todas as tarefas. O intervalo de execução medido corresponde ao tempo de execução de uma tarefa realizar a interseção entre as keys que a compõe, sendo possível sua busca em cache caso a computação já tenha sido realizada. O tempo médio de execução individual de todas as tarefas obtido foi de 8816 nanosegundos. Com base nisso foi estabelecido o tempo limite de execução para uma tarefa de 13200 nanosegundos, que representa a extrapolação de 50% do tempo médio de execução. Isso significa que para qualquer tarefa que exceda esse tempo de execução ela será interrompida, não completando sua interseção com as classes, e armazenada na memória primária, na <code>fila de struct Process</code>, para posterior submissão.</p>

| ![e6-execution-time-limit-13200.png](./images/e6-execution-time-limit-13200.png?width="400") | 
|:--:| 
| Resultado de execução com tempo limite de 13200 nanosegundos. A imagem mostra as tarefas, e suas respectivas prioridades, que excederam o limite estabelecido. |


<h2 align ="left">Etapa Adicional</h2>

<p align="justify">Nessa etapa é proposto a paralelização do algoritmo utilizando threads, rodando múltiplas entradas ao mesmo tempo e comparando qual o número ideal de trheads aplicáveis ao problema.</p>

<p align="justify">Foi implementado o problema do Produtor x Consumidor. O Produtor é representado pela função <code>parametersCombination</code>, responsável por realizar gerar as combinações. Já o Consumidor é representado pela função <code>intersectionsBetweenCombinations</code>, que realiza as interseções entre as combinações e as classes. Assim, à medida que são geradas as combinações essas são consumidas, sendo intersectadas entre si, primeiramente, para posteriormente ser interseccionada com as classes.</p>

<p align="justify">Na implementação foram utilizadas variáveis <code>mutex</code> para ajudar na sincronização das threads e também para proteger os dados compartilhados (região crítica) de serem acessados simultaneamente pelas threads. Na implementação também foi utilizado o <code>sleep</code>. Antes de uma thread realizar o primeiro lock, implementei um sleep por 1 nanosegundo. Notei que se não for feito isso praticamente 1 thread é responsável por realizar, aproximadamente, 70% da computação. Fazendo isso a computação, da geração das combinações e interseções, se distribui entre as threads.</p>

| ![graph-threads.png](./images/graph-threads.png?width="400") | 
|:--:| 
| Resultado da paralelização com múltiplas threads. O tempo de execução tende a se estabilizar na faixa de 13000 microsegundos com 5 threads para produtor e consumidor. O tempo de execução com threads é superior ao tempo de execução sem threads, isso pode ser explicado pelo fato do escalonador ter optado em chavear as threads em um único core, comum em sistemas Linux. |
