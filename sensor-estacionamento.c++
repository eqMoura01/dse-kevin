// Programa: Conectando Sensor Ultrassonico HC-SR04 ao Arduino
// Autor: MakerHero
 
// Carrega a biblioteca do sensor ultrassonico
#include <Ultrasonic.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
 
LiquidCrystal_I2C lcd(0x27,20,4);
 
// Define os pinos para o trigger e echo
#define pino_trigger 4
#define pino_echo 5
 
// Inicializa o sensor nos pinos definidos acima
Ultrasonic ultrasonic(pino_trigger, pino_echo);
 
// Define os pinos para os LEDs
#define led_vermelho 6
#define led_laranja 7
#define led_verde 8
 
void setup() {
  lcd.init();                      // initialize the lcd
  lcd.init();
  // Print a message to the LCD.
 
  //lcd.backlight();
  lcd.setCursor(3,0);
  lcd.print("");
  lcd.setCursor(2,1);
  lcd.print("");
  lcd.setCursor(0,2);
  lcd.print("");
  lcd.setCursor(2,3);
  lcd.print("");
 
  Serial.begin(9600);
  Serial.println("Lendo dados do sensor...");
 
  // Configura os pinos dos LEDs como saída
  pinMode(led_vermelho, OUTPUT);
  pinMode(led_laranja, OUTPUT);
  pinMode(led_verde, OUTPUT);
}
 
void loop() {
  // Le as informacoes do sensor, em cm e pol
  float cmMsec, inMsec;
  long microsec = ultrasonic.timing();
  cmMsec = ultrasonic.convert(microsec, Ultrasonic::CM);
  inMsec = ultrasonic.convert(microsec, Ultrasonic::IN);
 
  // Exibe informacoes no serial monitor
  Serial.print("Distancia em cm: ");
  Serial.print(cmMsec);
  Serial.print(" - Distancia em polegadas: ");
  Serial.println(inMsec);
 
  lcd.setCursor(0,1);
  lcd.print(cmMsec);
  lcd.print(" cm");
  lcd.print("          ");
 
  // Controla os LEDs com base na distância
  if (cmMsec <= 10) {
    digitalWrite(led_vermelho, HIGH);   // Acende o LED vermelho
    digitalWrite(led_laranja, LOW);     // Apaga o LED laranja
    digitalWrite(led_verde, LOW);       // Apaga o LED verde
  } else if (cmMsec > 10 && cmMsec <= 15) {
    digitalWrite(led_vermelho, LOW);    // Apaga o LED vermelho
    digitalWrite(led_laranja, HIGH);    // Acende o LED laranja
    digitalWrite(led_verde, LOW);       // Apaga o LED verde
  } else {
    digitalWrite(led_vermelho, LOW);    // Apaga o LED vermelho
    digitalWrite(led_laranja, LOW);     // Apaga o LED laranja
    digitalWrite(led_verde, HIGH);      // Acende o LED verde
  }
 
  delay(1000);
}