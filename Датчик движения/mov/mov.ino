
int ledPin = D2;                // Выбираем пин для светодиода
int inputPin = D1;               // Выбираем пин для входа датчика
int pirState = LOW;             // Переменная состояния датчика
int val = 0;                    // Переменная для чтения статуса состояния датчика
 
void setup() {
  pinMode(ledPin, OUTPUT);      // Объявляем контакт светодиода как выходной
  pinMode(inputPin, INPUT);     // Объявляем контакт датчика как входной
 
  Serial.begin(9600);
}
 
void loop(){
  val = digitalRead(inputPin);
  
  if (val == HIGH)
  {            
    digitalWrite(ledPin, HIGH);
  
    if (pirState == LOW) 
  {
      Serial.println("Motion detected!");
      pirState = HIGH;
    }
  } 
  else 
  {
    digitalWrite(ledPin, LOW);
  
    if (pirState == HIGH)
  {
      Serial.println("Motion ended!");
      pirState = LOW;
    }
  }
}
