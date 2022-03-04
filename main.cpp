#include <Arduino.h>



#define LEDC_CHANNEL_0     0        // 0-15 (16 canais)
#define LEDC_TIMER_13_BIT  13       // 13 bits de resolução
#define LEDC_BASE_FREQ     5000     // 5 kHz de clock base para o LED
#define LED_PIN            2        // led pin

int ledBrightness = 0;    // variavel para definir o brilho do led
int stepIncrement = 20;    // degrau de incremento ou decremento para o brilho do led

void ledcAnalogWrite(uint8_t channel, uint32_t value, uint32_t valueMax = 255) {
  // calcula o duty cycle
  uint32_t duty = (8191 / valueMax) * min(value, valueMax);
  ledcWrite(channel, duty);  // escreve as mudanças ao pino associado ao canal
}



void setup() {
  //configura qual canal, frequência e resolução
  ledcSetup(LEDC_CHANNEL_0, LEDC_BASE_FREQ, LEDC_TIMER_13_BIT);
  //configura associação do pino ao canal
  ledcAttachPin(LED_PIN, LEDC_CHANNEL_0);
}


void loop() {
  // chama função para calcular o duty e alterar o brilho
  ledcAnalogWrite(LEDC_CHANNEL_0, ledBrightness);

  // altera variável brightness de acordo com os steps selecionados
  ledBrightness = ledBrightness + stepIncrement;

  // logica para mudar a direção do efeito de "fading"
  if (ledBrightness <= 0 || ledBrightness >= 255) {
    stepIncrement = -stepIncrement;
  }

  // altere este delay para um efeito mais rápido
  delay(30);
}



