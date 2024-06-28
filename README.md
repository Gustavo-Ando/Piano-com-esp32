# Piano com ESP32
## Funcionamento

[Falstad](https://tinyurl.com/2j6gxfdj) (Modelo simplificado do piano)

![unnamed](https://github.com/Gustavo-Ando/Piano-com-esp32/assets/174065922/b7291a3e-eb44-44ad-bcd1-662a1aa75948)

O piano foi montado em uma protoboard, a qual foi alimentada pelo positivo e negativo da ESP32 através de jumpers macho-fêmea. Cada tecla do piano foi conectada à placa por esses jumpers nas entradas analógicas, totalizando 12 teclas (1 oitava). A saída foi inicialmente feita através de um buzzer, o qual foi eventualmente substituído por uma alto falante piezoeletronico.

Além disso, foram adicionados à placa resistores de 10 MΩ para que o músico consiga tocar o piano, se tornando um caminho de menor resistência quando em comparação com os resistores e guiando a corrente. Ao tocar as teclas, o pianista precisa também segurar o jumper conectado à fonte negativa, para criar uma diferença de tensão.

Para gerar as ondas sonoras, a ESP32 identifica quais pin estão com uma voltagem abaixo de um certo limite, essas correspondem às teclas pressionadas.

Então criam-se ondas de seno correspondentes a cada frequência, tomando-se como referência A4 = 440HZ e usando o temperamento igual de 12 tons, consideramos a razão de um semitom como sendo $2^{1/12}$, para que as 12 notas sejam igualmente espaçadas dentro de uma oitava com razão 2.

```cpp
for(int i = 0; i < keys; i++){
  keyVoltage[i] = analogRead(keyPin[i]);
  if(keyVoltage[i] < threshold) {
    height += sin(220.0 * pow(2.0, i/12.0) * 6.2831855 * time / 1000000.0);
  }
}
```

Além disso, usamos um envelope (ADSR) para modular o volume da nota ao longo de sua duração, com um tempo de ataque até o pico da nota após ser pressionada, um tempo de decaimento para que a nota chegue a um valor estável (o sustain) e um tempo de liberar para que o som termine. O valor desse envelope então é multiplicado pelo resultado do seno antes de se somar ao height.

```cpp
  if(!released){
    if(time < attack){
      return time/ (float) attack;
    } else if(time < attack + decay){
      float k = (sustain - 1.0)/decay;
      return k * time + sustain - (decay + attack) * k;
    } else {
      return sustain;
    }
  } else {
    if(time < release) return sustain - sustain * time/ (float) release;
    else return 0;
  }
```

Com isso, somamos as ondas para obtermos a pressão do ar desejado no momento para produzir-se o som. Como a ESP32 não consegue produzir voltagens analógicas (entre 0 e 3.3V) para que essa informação seja transferido aos speakers, usamos uma aproximação através de modulação por largura de pulso, ou seja, geramos uma onda quadrada de frequência superior ao limiar da audição humana (acima de 20KHz) e alteramos sua razão cíclica (o período em que a onda fica ativa) para simular diferentes voltagens, visto que em média, a voltagem será igual a porcentagem do tempo que a onda está ativa e o valor máximo (3.3V).

## Materiais
|Valores| Componentes|
|-------|------------|
|R$ 39.10| Breadboard|
|R$0.07 (x20)| Resistor 10M ohm 1/4W|
|R$7.00 (x2)| Jumpers Macho-femea|
|R$ 15.00 (x0.5)| Jumper Macho-macho (Valor dividido com outro grupo)|
|R$ 9.50| Buzzer|
|Grátis |Materiais emprestados do professor|

## Vídeo

https://github.com/Gustavo-Ando/Piano-com-esp32/assets/163079804/b126ed6b-4f8a-4dc9-96e9-458e650c600c

## Alunos participantes
|Nomes|Nº USP|
|-----|------|
|Caio Capocasali | 12541733|
|Driely Fernanda Oliveira de Abreu | 11879575|
|Gustavo Alvares Andó | 15457345|
|Maria Clara de Souza Capato | 15475294|

## Referências

Inspiração: [Manual do Mundo](https://youtu.be/gTU9NunYVnM?si=pZbLGN4s4YTZFQD2)
Pinout: [Circuit State](https://circuitstate.com/wp-content/uploads/2022/12/ESP32-DevKit-V1-Pinout-Diagram-r0.1-CIRCUITSTATE-Electronics-2.png)
