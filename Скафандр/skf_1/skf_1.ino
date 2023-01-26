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
    pinMode(BUTTON_PIN, INPUT);
    pinMode(TONE_PIN  , OUTPUT);
    pinMode(MOTO_PIN  , OUTPUT);
  
    digitalWrite(MOTO_PIN, HIGH);
    tone (TONE_PIN,400); 
    delay(200);
    tone (TONE_PIN,300); 
    delay(200);
    noTone(TONE_PIN);
    digitalWrite(MOTO_PIN, LOW); 
   
}


void loop() {
   digitalWrite(LED3_PIN, HIGH);
   digitalWrite(LED2_PIN, HIGH);
  
   
   
   if (digitalRead(BUTTON_PIN) == HIGH) { // Если кнопка нажата 
      int b = 1;
       digitalWrite(MOTO_PIN, HIGH);
       tone (TONE_PIN,300); 
       delay(500);
       noTone(TONE_PIN);
       digitalWrite(MOTO_PIN, LOW);  
   
       if (int b = 1) {
             
             
           digitalWrite(LED3_PIN, LOW);
           digitalWrite(LED2_PIN, LOW);
           digitalWrite(LED1_PIN, HIGH);
            delay (600000);
           digitalWrite(MOTO_PIN, HIGH);
           tone (TONE_PIN,280);
           delay(500);
           noTone(TONE_PIN); 
            digitalWrite(MOTO_PIN, LOW); 
           digitalWrite(LED3_PIN, HIGH);
            delay (420000);
           tone (TONE_PIN,250);
           digitalWrite(MOTO_PIN, HIGH);
           delay(500);
           noTone(TONE_PIN); 
           digitalWrite(MOTO_PIN, LOW);   
           digitalWrite(LED1_PIN, LOW);
            delay (180000 );
           digitalWrite(MOTO_PIN, HIGH); 
           tone (TONE_PIN,230);
           delay(500);
           noTone(TONE_PIN); 
           digitalWrite(MOTO_PIN, LOW);  
           digitalWrite(LED3_PIN, LOW);

           
           while(true){
  digitalWrite(MOTO_PIN, HIGH);           
  digitalWrite(LED2_PIN, HIGH);
  tone (TONE_PIN,350); // turn the LED on (HIGH is the voltage level)
  delay(500);                       // wait for a second
  digitalWrite(LED2_PIN, LOW);
  tone (TONE_PIN,300); // turn the LED off by making the voltage LOW
  delay(500); 
  noTone(TONE_PIN); 

}
            }
  
}
}
