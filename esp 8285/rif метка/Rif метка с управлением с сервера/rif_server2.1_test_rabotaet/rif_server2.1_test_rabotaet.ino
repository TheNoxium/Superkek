#include <ESP8266WiFi.h>
#include <SPI.h>
#include <MFRC522.h>

const char* ssid = "Cats_Ass";
const char* password = "12345678s";

const char* host = "192.168.1.94";

int buff=0;


int led =  D0;    //зеленый
int led2 = D1;    //красны
int led3 = D2;    //синий
int tonepin = D8; //динамик
int rad = 15;


constexpr uint8_t RST_PIN = D3;     
constexpr uint8_t SS_PIN = D4;    

MFRC522 rfid(SS_PIN, RST_PIN); 
MFRC522::MIFARE_Key key;
String tag;



void setup()
{ Serial.begin(115200);

  Serial.printf("Здорова отец ");
  
  SPI.begin(); // Init SPI bus
  rfid.PCD_Init(); 
  
  pinMode(led, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(tonepin, OUTPUT);
  pinMode(rad  , OUTPUT); 
  
 
  Serial.println();

  Serial.printf("Connecting to %s ", ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println(" connected");

}


void loop()
{

 WiFiClient client;

  Serial.printf("\n[Connecting to %s ... ", host);
  if (client.connect(host, 80))
  {
    Serial.println("connected]");
    client.print( "GET /data.php?");
    client.println( " HTTP/1.1");
    client.print( "Host: " );
    client.println(host);
    client.println( "Connection: close" );
    client.println();
    client.println();
    
   
    delay(50);
         
      while (client.available())
 {
      String line = client.readStringUntil('\n');
      //Serial.print(line);
    
    
      char c = client.read();
        if ( c=='1')
        {
        buff=1;
        }
        if ( c=='0')
        {
         buff=0;
        }
      } 
    
      client.stop();
      client.flush();
      delay(50); 
  }
  else 
  {
   client.stop();
   Serial.println("Я обосрался ошибка подключения");    
   delay(1000);
   client.connect(host, 80);
  }




  if ( buff==1)
        {
        digitalWrite (led, HIGH);
        digitalWrite (led2, LOW);
        digitalWrite (rad, HIGH);
         tone (tonepin,700); 
         delay(200);
         noTone(tonepin);
         delay(1000);
        }
        else
        {
           digitalWrite(led, LOW);
           digitalWrite(led2, HIGH);
           digitalWrite (rad, LOW);
           delay(500);
        }

 
  Serial.println(buff);
  Serial.print( " значение ");

 
  
   if ( ! rfid.PICC_IsNewCardPresent())
    return;
  if (rfid.PICC_ReadCardSerial()) {
    for (byte i = 0; i < 4; i++) {
      tag += rfid.uid.uidByte[i];
    }
    Serial.println(tag);
    if (tag == "5113184173") {

      if ( buff==0)
        {
      Serial.println("Access Granted!");
      digitalWrite(led2, LOW);
      digitalWrite(led, HIGH);
           tone (tonepin,700); 
           delay(200);
           noTone(tonepin); 
           
     
  Serial.printf("\n[Connecting to %s ... ", host);
  client.connect(host, 80);
  
    Serial.println("connected к открыть]");
    client.print( "GET /controlop1.php?");
    client.println( " HTTP/1.1");
    client.print( "Host: " );
    client.println(host);
    client.println( "Connection: close" );
    client.println();
    client.println();
    client.stop();
    client.flush();
    
      
     delay(5000);
    tone (tonepin,500); 
    delay(200);
    noTone(tonepin);
    digitalWrite(led, LOW);
    
  Serial.printf("\n[Connecting to %s ... ", host);
  client.connect(host, 80);
   
    Serial.println("connected к закрыть]");
    client.print( "GET /controlcl1.php?");
    client.println( " HTTP/1.1");
    client.print( "Host: " );
    client.println(host);
    client.println( "Connection: close" );
    client.println();
    client.println();
    client.stop();
    client.flush();
      delay(100); 
        }
          else
        {
           tone (tonepin,500); 
    delay(200);
    noTone(tonepin);
    digitalWrite(led, LOW);
    
  Serial.printf("\n[Connecting to %s ... ", host);
  client.connect(host, 80);
   
    Serial.println("connected к закрыть]");
    client.print( "GET /controlcl1.php?");
    client.println( " HTTP/1.1");
    client.print( "Host: " );
    client.println(host);
    client.println( "Connection: close" );
    client.println();
    client.println();
    client.stop();
    client.flush();
      delay(50); 
        }
      
  
    } else if (tag == "2402816514") {
                if ( buff==0)
        {
      Serial.println("Access Granted!");
      digitalWrite(led2, LOW);
      digitalWrite(led, HIGH);
           tone (tonepin,700); 
           delay(200);
           noTone(tonepin); 
           
     
  Serial.printf("\n[Connecting to %s ... ", host);
  client.connect(host, 80);
  
    Serial.println("connected к открыть]");
    client.print( "GET /controlop1.php?");
    client.println( " HTTP/1.1");
    client.print( "Host: " );
    client.println(host);
    client.println( "Connection: close" );
    client.println();
    client.println();
    client.stop();
    client.flush();
      
      
     delay(5000);
    tone (tonepin,500); 
    delay(200);
    noTone(tonepin);
    digitalWrite(led, LOW);
    
  Serial.printf("\n[Connecting to %s ... ", host);
  client.connect(host, 80);
   
    Serial.println("connected к закрыть]");
    client.print( "GET /controlcl1.php?");
    client.println( " HTTP/1.1");
    client.print( "Host: " );
    client.println(host);
    client.println( "Connection: close" );
    client.println();
    client.println();
    client.stop();
    client.flush();
      delay(50); 
        }
          else
        {
           tone (tonepin,500); 
    delay(200);
    noTone(tonepin);
    digitalWrite(led, LOW);
    
  Serial.printf("\n[Connecting to %s ... ", host);
  client.connect(host, 80);
   
    Serial.println("connected к закрыть]");
    client.print( "GET /controlcl1.php?");
    client.println( " HTTP/1.1");
    client.print( "Host: " );
    client.println(host);
    client.println( "Connection: close" );
    client.println();
    client.println();
    client.stop();
    client.flush();
      delay(50); 
        }
    
    
    } else {
      Serial.println("Access Denied!");
      digitalWrite(tonepin, HIGH);
      delay(2000);
      digitalWrite(tonepin, LOW);
    }
    tag = "";
    rfid.PICC_HaltA();
    rfid.PCD_StopCrypto1();
  }
}
