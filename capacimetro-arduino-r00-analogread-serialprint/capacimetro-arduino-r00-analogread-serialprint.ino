/*
 * Capacimetro (medidor de capacitância em nF e uF) com Arduino UNO (ATMEGA328)
 * ________________________________________________________
 * Funcionamento:
 * 
 * - Ao acionar a saída digital 'pin' (2) o capacitor é carregado atraves do resistor
 * definido na variável "resistor"
 * - É contado o tempo entre o acionamento do pino 2 e a tensão sobre o capacitor
 * atingir 63,2% da tensão total (que é 5V), portanto 3,16V
 * A capacitância é então calculada: C(Farads)= T(segundos) / R(ohms)
 * - A saída 'pin' (2) é então colocada em '0' (LOW) para descarregar o capacitor
 * - O valor de capacitância (já com a unidade correta) é exibido em um monitor serial,
 * portanto é necessário conectar o Arduino à um computador
 * 
 * LIMITACOES: 
 * - Não mede capacitâncias abaixo de 44nF
 * - É lento para ler capacitâncias acima de 100uF
 * - Testado com: 100nF, 1uF, 10uF e 470uF
 * ________________________________________________________
 * 
 * Desenvolvido por: Clovis Fritzen em 04/11/2016
 * Mais informações: http://www.FritzenLab.com.br
 * 
 * ** caso REDISTRIBUIR/COPIAR este código, FAVOR ENVIAR ESTE CABEÇALHO !!! **
 * 

*/
#define analogica A0
#define pin 2


long t0, t;
int leituraAnalogica;
int constanteTau = 647; // 63.2% of 1024 !! (capacitor "Tau" constant)
String unidade = String("uF");
boolean escritaTela = false;
boolean contando = false;
float tempoEscrita = 0.00;
float tempoAnterior = 0.00;
float capacitancia = 0.000000;
float resistor = 3280;

void setup()
{
  Serial.begin(115200);
  pinMode(pin, OUTPUT);
  digitalWrite(pin, LOW);
  
}

void loop()
{
  leituraAnalogica= analogRead(analogica);
  
  if ((contando == false) && (leituraAnalogica <= 10)){
    digitalWrite(pin, HIGH);
    contando= true;
    t0 = micros();
  } else {
    //digitalWrite(pin, LOW);
  }

    
  if (leituraAnalogica >= constanteTau){
    t = micros()-t0;  // calculate elapsed time
    contando = false;
    capacitancia = t / resistor;
    if (capacitancia <= 1.0) {
      capacitancia *= 1000;
      if (capacitancia < 44){
        t= 0;
        capacitancia = 0;
      }
      unidade = " nF";
    } else {
      unidade = " uF";
    }
    
      digitalWrite(pin, LOW);
      escritaTela= true;
      /*Serial.print("tempo= ");
      Serial.print(t);
      Serial.println(" uS");*/
          
    } else {
    
  } 

tempoEscrita = micros() - tempoAnterior;
if ((escritaTela == true) && tempoEscrita > 1000000){
  tempoAnterior = micros();  
  escritaTela = false;
  Serial.print("Capacitancia= ");
  Serial.print(capacitancia,2);
  Serial.println(unidade);
       
}
  

}
