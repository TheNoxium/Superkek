#define BUTTON_PIN  12
#define LED1_PIN    7   // 7  green
#define LED2_PIN    10  // 10 blue
#define LED3_PIN    8   // 8  red 
#define MOTO_PIN    5
#define TONE_PIN    3

int b = 0;



void setup() { 
    pinMode(LED1_PIN, OUTPUT);
    pinMode(LED2_PIN, OUTPUT);
    pinMode(LED3_PIN, OUTPUT); // Инициализируем цифровой вход/выход в режиме выхода.
    pinMode(BUTTON_PIN, INPUT); // Инициализируем цифровой вход/выход в режиме входа.
   
}


void loop() {
   digitalWrite(LED3_PIN, HIGH);
   digitalWrite(LED2_PIN, HIGH);
   
   if (digitalRead(BUTTON_PIN) == HIGH) { // Если кнопка нажата 
      int b = 1;
       if (int b = 1) {
           digitalWrite(LED3_PIN, LOW);
           digitalWrite(LED2_PIN, LOW);
           digitalWrite(LED3_PIN, HIGH);
           delay (2000); 
           digitalWrite(LED3_PIN, LOW);
           while(true){
            
 digitalWrite(LED2_PIN, HIGH);
 delay (100); 
 digitalWrite(LED2_PIN, LOW);

}
            }
 }  else { 
      digitalWrite(LED1_PIN, LOW);
      digitalWrite(LED2_PIN, LOW);
      digitalWrite(LED2_PIN, HIGH);
  }
  
}
