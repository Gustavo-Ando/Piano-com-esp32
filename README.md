# Piano com ESP32
## Funcionamento

Falstad: https://tinyurl.com/2j6gxfdj (Modelo simplificado do piano)

O piano foi montado em uma protoboard, a qual foi alimentada pelo positivo e negativo da ESP32 através de jumpers macho-fêmea. Cada tecla do piano foi conectada à placa por esses jumpers nas entradas analógicas, totalizando 12 teclas (1 oitava). A saída foi inicialmente feita através de um buzzer, o qual foi eventualmente substituído por uma alto falante piezoeletronico.

Além disso, foram adicionados à placa resistores de 10 MΩ para que o músico consiga tocar o piano, se tornando um caminho de menor resistência quando em comparação com os resistores e guiando a corrente. Ao tocar as teclas, o pianista precisa também segurar o jumper conectado à fonte negativa, para criar uma diferença de tensão.

Para gerar as ondas sonoras, a ESP32 identifica quais pin estão com uma voltagem abaixo de um certo limite, essas correspondem às teclas pressionadas.

Então criam-se ondas de seno correspondentes a cada frequência, tomando-se como referência A4 = 440HZ e usando o temperamento igual de 12 tons, consideramos a razão de um semitom como sendo $2^{1/12}$, para que as 12 notas sejam igualmente espaçadas dentro de uma oitava com razão 2.

Com isso, somamos as ondas para obtermos a pressão do ar desejado no momento para produzir-se o som. Como a ESP32 não consegue produzir voltagens analógicas (entre 0 e 3.3V) para que essa informação seja transferido aos speakers, usamos uma aproximação através de modulação por largura de pulso, ou seja, geramos uma onda quadrada de frequência superior ao limiar da audição humana (acima de 20KHz) e alteramos sua razão cíclica (o período em que a onda fica ativa) para simular diferentes voltagens, visto que em média, a voltagem será igual a porcentagem do tempo que a onda está ativa e o valor máximo (3.3V).

## Materiais
|Valores| Componentes|
|-------|------------|
|R$ 40.00| Breadboard|
|R$0.07 (x20)| Resistor 10M ohm 1/4W|
|R$7.00 (x2)| Jumpers Macho-femea|
|R$ 15.00 (x0.5)| Jumper Macho-macho (Valor dividido com outro grupo)|
|R$ 9.00| Buzzer|
+ Materiais emprestados do professor

## Vídeo
Upload do vídeo

## Alunos participantes
Caio Capocasali - 12541733
Driely Fernanda Oliveira de Abreu - 11879575
Gustavo Alvares Andó - 15457345
Maria Clara de Souza Capato - 15475294



