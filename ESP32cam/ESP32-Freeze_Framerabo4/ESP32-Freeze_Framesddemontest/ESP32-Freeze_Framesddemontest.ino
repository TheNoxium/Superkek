const char* ssid = "Cats_Ass";
const char* password = "12345678s";

#include <WiFi.h>
#include <WiFiClientSecure.h>
#include "esp_camera.h"       
#include "soc/soc.h"           
#include "soc/rtc_cntl_reg.h"  
#include "FS.h"             
#include "SD_MMC.h"    

String Feedback=""; 


String Command="";
String cmd="";
String P1="";
String P2="";
String P3="";
String P4="";
String P5="";
String P6="";
String P7="";
String P8="";
String P9="";

String buffer;

byte ReceiveState=0;
byte cmdState=1;
byte strState=1;
byte questionstate=0;
byte equalstate=0;
byte semicolonstate=0;

#define PWDN_GPIO_NUM     32
#define RESET_GPIO_NUM    -1
#define XCLK_GPIO_NUM      0
#define SIOD_GPIO_NUM     26
#define SIOC_GPIO_NUM     27

#define Y9_GPIO_NUM       35
#define Y8_GPIO_NUM       34
#define Y7_GPIO_NUM       39
#define Y6_GPIO_NUM       36
#define Y5_GPIO_NUM       21
#define Y4_GPIO_NUM       19
#define Y3_GPIO_NUM       18
#define Y2_GPIO_NUM        5
#define VSYNC_GPIO_NUM    25
#define HREF_GPIO_NUM     23
#define PCLK_GPIO_NUM     22

WiFiServer server(80);
WiFiClient client;

void setup() {
  WRITE_PERI_REG(RTC_CNTL_BROWN_OUT_REG, 0);  
  
  Serial.begin(115200);
  Serial.setDebugOutput(true); 
  Serial.println();

  camera_config_t config;
  config.ledc_channel = LEDC_CHANNEL_0;
  config.ledc_timer = LEDC_TIMER_0;
  config.pin_d0 = Y2_GPIO_NUM;
  config.pin_d1 = Y3_GPIO_NUM;
  config.pin_d2 = Y4_GPIO_NUM;
  config.pin_d3 = Y5_GPIO_NUM;
  config.pin_d4 = Y6_GPIO_NUM;
  config.pin_d5 = Y7_GPIO_NUM;
  config.pin_d6 = Y8_GPIO_NUM;
  config.pin_d7 = Y9_GPIO_NUM;
  config.pin_xclk = XCLK_GPIO_NUM;
  config.pin_pclk = PCLK_GPIO_NUM;
  config.pin_vsync = VSYNC_GPIO_NUM;
  config.pin_href = HREF_GPIO_NUM;
  config.pin_sscb_sda = SIOD_GPIO_NUM;
  config.pin_sscb_scl = SIOC_GPIO_NUM;
  config.pin_pwdn = PWDN_GPIO_NUM;
  config.pin_reset = RESET_GPIO_NUM;
  config.xclk_freq_hz = 20000000;
  config.pixel_format = PIXFORMAT_JPEG;
  

  if(psramFound()){
    config.frame_size = FRAMESIZE_UXGA;
    config.jpeg_quality = 10;           // 0-63 качество
    config.fb_count = 2;
  } else {
    config.frame_size = FRAMESIZE_SVGA;
    config.jpeg_quality = 12;           // 0-63 качество
    config.fb_count = 1;
  }  

  esp_err_t err = esp_camera_init(&config);
  if (err != ESP_OK) {
    Serial.printf("Ошибка камеры 0x%x", err);
    delay(1000);
    ESP.restart();
  }
// Дополнительные настройки
  sensor_t * s = esp_camera_sensor_get();
  s->set_framesize(s, FRAMESIZE_SVGA);    //UXGA(1600x1200), SXGA(1280x1024), XGA(1024x768), SVGA(800x600), VGA(640x480), CIF(400x296), QVGA(320x240), HQVGA(240x176), QQVGA(160x120), QXGA(2048x1564 for OV3660)

  
  // светодиод
  ledcAttachPin(4, 4);  
  ledcSetup(4, 5000, 8);    
  
  WiFi.mode(WIFI_AP_STA);  

  for (int i=0;i<2;i++) {
    WiFi.begin(ssid, password);   
  
    delay(1000);
    Serial.println("");
    Serial.print("Подключение к ");
    Serial.println(ssid);
    
    long int StartTime=millis();
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        if ((StartTime+5000) < millis()) break;    
    } 
  
    if (WiFi.status() == WL_CONNECTED) {         
      Serial.println("");
      Serial.println("IP адрес: ");
      Serial.println(WiFi.localIP());
      Serial.println("");
  
      for (int i=0;i<5;i++) {   
        ledcWrite(4,10);
        delay(200);
        ledcWrite(4,0);
        delay(200);    
      }
      break;
    }
  } 

  if (WiFi.status() != WL_CONNECTED) { 
    for (int i=0;i<2;i++) {  
      ledcWrite(4,10);
      delay(1000);
      ledcWrite(4,0);
      delay(1000);    
    }
  } 

  Serial.println("");
  Serial.println("IP адрес: ");
  Serial.println(WiFi.softAPIP());  
  Serial.println("");  

  pinMode(4, OUTPUT);
  digitalWrite(4, LOW);  

  server.begin();  
}

void readFile(fs::FS &fs, const char * path){
    Serial.printf("Reading file: %s\n", path);

    File filele = fs.open(path);
    
    if (filele) {
        // считываем все байты из файла и выводим их в COM-порт
       while (filele.available()) //Читаем содержимое файла
  {
    buffer = filele.readStringUntil('\n');//Считываем с карты весь дотекст в строку до символа окончания.
    Serial.println(buffer); // для отладки отправляем по UART все что прочитали с карты.
  }
    filele.close();
    SD_MMC.end();
    delay(10000);
   } else {
        // выводим ошибку если не удалось открыть файл
        Serial.println("error opening test.txt");
        //listenConnection();  
        // SD_MMC.end();
         listenConnection();
    }
        
       
    
}

void loop() {

 
 
 
  if (SD_MMC.begin()){
  uint8_t cardType = SD_MMC.cardType();
  readFile(SD_MMC, "/test.txt");
  SD_MMC.end();
  } else {
     listenConnection();  
  }
}


void ExecuteCommand() {
  if (cmd!="getstill") {
    Serial.println("cmd= "+cmd+" ,P1= "+P1+" ,P2= "+P2+" ,P3= "+P3+" ,P4= "+P4+" ,P5= "+P5+" ,P6= "+P6+" ,P7= "+P7+" ,P8= "+P8+" ,P9= "+P9);
    Serial.println("");
  }

  // get запрос http://192.168.xxx.xxx?cmd=P1;P2;P3;P4;P5;P6;P7;P8;P9
  if (cmd=="your cmd") {
  } else if (cmd=="restart") {            // Перезагрузка платы
    ESP.restart();
  } else if (cmd=="flash") {              // Свечение светодиода подсветки  
    ledcAttachPin(4, 4);  
    ledcSetup(4, 5000, 8);   
    int val = P1.toInt();
    ledcWrite(4,val);  
  } else if (cmd=="resetwifi") {          // Перезагрузка WIFI 
    for (int i=0;i<2;i++) {
      WiFi.begin(P1.c_str(), P2.c_str());
      Serial.print("Подключение к ");
      Serial.println(P1);
      long int StartTime=millis();
      while (WiFi.status() != WL_CONNECTED) {
          delay(500);
          if ((StartTime+5000) < millis()) break;
      } 
      Serial.println("");
      Serial.println("IP: "+WiFi.localIP().toString());
      Feedback="IP: "+WiFi.localIP().toString();

      if (WiFi.status() == WL_CONNECTED) {
        WiFi.softAP((WiFi.localIP().toString()+"_"+P1).c_str(), P2.c_str());
        for (int i=0;i<2;i++) {  
          ledcWrite(4,10);
          delay(300);
          ledcWrite(4,0);
          delay(300);    
        }
        break;
      }
    }
  } else if (cmd=="framesize") {              // Разрешение картинки
    int val = P1.toInt();
    sensor_t * s = esp_camera_sensor_get(); 
    s->set_framesize(s, (framesize_t)val);    
  } else if (cmd=="quality") {                // Качество
    sensor_t * s = esp_camera_sensor_get();
    s->set_quality(s, P1.toInt());     
  } else if (cmd=="contrast") {               // Контрастность
    sensor_t * s = esp_camera_sensor_get();
    s->set_contrast(s, P1.toInt());          
  } else if (cmd=="brightness") {             // Яркость
    sensor_t * s = esp_camera_sensor_get();
    s->set_brightness(s, P1.toInt());   
  } else if (cmd=="saturation") {             //Насыщенность
    sensor_t * s = esp_camera_sensor_get();
    s->set_saturation(s, P1.toInt());          
  } else if (cmd=="saveimage") {              // Сохранить картинку
    saveCapturedImage(P1);
    Feedback=ListImages();
  } else if (cmd=="listimages") {             // Список файлов
    Feedback=ListImages();
  } else if (cmd=="deleteimage") {            // Удалить файл
    Feedback=deleteimage(P1)+"<br>"+ListImages();
  } else {
    Feedback="Команда не определена.";
  }
  if (Feedback=="") Feedback=Command;  
}


void listenConnection() {
  Feedback="";Command="";cmd="";P1="";P2="";P3="";P4="";P5="";P6="";P7="";P8="";P9="";
  ReceiveState=0,cmdState=1,strState=1,questionstate=0,equalstate=0,semicolonstate=0;
  
  client = server.available();

  if (client) { 
    String currentLine = "";

    while (client.connected()) {
      if (client.available()) {
        char c = client.read();             
        
        getCommand(c);   
                
        if (c == '\n') {
          if (currentLine.length() == 0) {    
            
            if (cmd=="getstill") {  
              getStill(); 
            } else if (cmd=="showimage") {  
              showimage();            
            } else if (cmd=="status") {            
              status();           
            } else { 
              mainpage();
            }
                        
            Feedback="";
            break;
          } else {
            currentLine = "";
          }
        } 
        else if (c != '\r') {
          currentLine += c;
        }

        if ((currentLine.indexOf("/?")!=-1)&&(currentLine.indexOf(" HTTP")!=-1)) {
          if (Command.indexOf("stop")!=-1) {  // -> http://192.168.xxx.xxx/?cmd=aaa;bbb;ccc;stop
            client.println();
            client.println();
            client.stop();
          }
          currentLine="";
          Feedback="";
          ExecuteCommand();
        }
      }
    }
    delay(1);
    client.stop();
  }
  
}

// Создаём HTML страницу
static const char PROGMEM INDEX_HTML[] = R"rawliteral(<!doctype html>
<html>
    <head>
        <meta charset="utf-8">
        <meta name="viewport" content="width=device-width,initial-scale=1">
        <title>ESP32 OV2460 Стоп кадр</title>
        <style>
            body {
                font-family: Arial,Helvetica,sans-serif;
                background: #181818;
                color: #EFEFEF;
                font-size: 16px
            }
            h2 {
                font-size: 18px
            }
            section.main {
                display: flex
            }
            #menu,section.main {
                flex-direction: column
            }
            #menu {
                display: none;
                flex-wrap: nowrap;
                min-width: 340px;
                background: #363636;
                padding: 8px;
                border-radius: 4px;
                margin-top: -10px;
                margin-right: 10px;
            }
            #content {
                display: flex;
                flex-wrap: wrap;
                align-items: stretch
            }
            figure {
                padding: 0px;
                margin: 0;
                -webkit-margin-before: 0;
                margin-block-start: 0;
                -webkit-margin-after: 0;
                margin-block-end: 0;
                -webkit-margin-start: 0;
                margin-inline-start: 0;
                -webkit-margin-end: 0;
                margin-inline-end: 0
            }
            figure img {
                display: block;
                width: 100%;
                height: auto;
                border-radius: 4px;
                margin-top: 8px;
            }
            @media (min-width: 800px) and (orientation:landscape) {
                #content {
                    display:flex;
                    flex-wrap: nowrap;
                    align-items: stretch
                }
                figure img {
                    display: block;
                    max-width: 100%;
                    max-height: calc(100vh - 40px);
                    width: auto;
                    height: auto
                }
                figure {
                    padding: 0 0 0 0px;
                    margin: 0;
                    -webkit-margin-before: 0;
                    margin-block-start: 0;
                    -webkit-margin-after: 0;
                    margin-block-end: 0;
                    -webkit-margin-start: 0;
                    margin-inline-start: 0;
                    -webkit-margin-end: 0;
                    margin-inline-end: 0
                }
            }
            section#buttons {
                display: flex;
                flex-wrap: nowrap;
                justify-content: space-between
            }
            #nav-toggle {
                cursor: pointer;
                display: block
            }
            #nav-toggle-cb {
                outline: 0;
                opacity: 0;
                width: 0;
                height: 0
            }
            #nav-toggle-cb:checked+#menu {
                display: flex
            }
            .input-group {
                display: flex;
                flex-wrap: nowrap;
                line-height: 22px;
                margin: 5px 0
            }
            .input-group>label {
                display: inline-block;
                padding-right: 10px;
                min-width: 47%
            }
            .input-group input,.input-group select {
                flex-grow: 1
            }
            .range-max,.range-min {
                display: inline-block;
                padding: 0 5px
            }
            button {
                display: block;
                margin: 5px;
                padding: 0 12px;
                border: 0;
                line-height: 28px;
                cursor: pointer;
                color: #fff;
                background: #ff3034;
                border-radius: 5px;
                font-size: 16px;
                outline: 0
            }
            button:hover {
                background: #ff494d
            }
            button:active {
                background: #f21c21
            }
            button.disabled {
                cursor: default;
                background: #a0a0a0
            }
            input[type=range] {
                -webkit-appearance: none;
                width: 100%;
                height: 22px;
                background: #363636;
                cursor: pointer;
                margin: 0
            }
            input[type=range]:focus {
                outline: 0
            }
            input[type=range]::-webkit-slider-runnable-track {
                width: 100%;
                height: 2px;
                cursor: pointer;
                background: #EFEFEF;
                border-radius: 0;
                border: 0 solid #EFEFEF
            }
            input[type=range]::-webkit-slider-thumb {
                border: 1px solid rgba(0,0,30,0);
                height: 22px;
                width: 22px;
                border-radius: 50px;
                background: #ff3034;
                cursor: pointer;
                -webkit-appearance: none;
                margin-top: -11.5px
            }
            input[type=range]:focus::-webkit-slider-runnable-track {
                background: #EFEFEF
            }
            input[type=range]::-moz-range-track {
                width: 100%;
                height: 2px;
                cursor: pointer;
                background: #EFEFEF;
                border-radius: 0;
                border: 0 solid #EFEFEF
            }
            input[type=range]::-moz-range-thumb {
                border: 1px solid rgba(0,0,30,0);
                height: 22px;
                width: 22px;
                border-radius: 50px;
                background: #ff3034;
                cursor: pointer
            }
            input[type=range]::-ms-track {
                width: 100%;
                height: 2px;
                cursor: pointer;
                background: 0 0;
                border-color: transparent;
                color: transparent
            }
            input[type=range]::-ms-fill-lower {
                background: #EFEFEF;
                border: 0 solid #EFEFEF;
                border-radius: 0
            }
            input[type=range]::-ms-fill-upper {
                background: #EFEFEF;
                border: 0 solid #EFEFEF;
                border-radius: 0
            }
            input[type=range]::-ms-thumb {
                border: 1px solid rgba(0,0,30,0);
                height: 22px;
                width: 22px;
                border-radius: 50px;
                background: #ff3034;
                cursor: pointer;
                height: 2px
            }
            input[type=range]:focus::-ms-fill-lower {
                background: #EFEFEF
            }
            input[type=range]:focus::-ms-fill-upper {
                background: #363636
            }
            .switch {
                display: block;
                position: relative;
                line-height: 22px;
                font-size: 16px;
                height: 22px
            }
            .switch input {
                outline: 0;
                opacity: 0;
                width: 0;
                height: 0
            }
            .slider {
                width: 50px;
                height: 22px;
                border-radius: 22px;
                cursor: pointer;
                background-color: grey
            }
            .slider,.slider:before {
                display: inline-block;
                transition: .4s
            }
            .slider:before {
                position: relative;
                content: "";
                border-radius: 50%;
                height: 16px;
                width: 16px;
                left: 4px;
                top: 3px;
                background-color: #fff
            }
            input:checked+.slider {
                background-color: #ff3034
            }
            input:checked+.slider:before {
                -webkit-transform: translateX(26px);
                transform: translateX(26px)
            }
            select {
                border: 1px solid #363636;
                font-size: 14px;
                height: 22px;
                outline: 0;
                border-radius: 5px
            }
            .image-container {
                position: relative;
                min-width: 160px
            }
            .close {
                position: absolute;
                right: 5px;
                top: 5px;
                background: #ff3034;
                width: 16px;
                height: 16px;
                border-radius: 100px;
                color: #fff;
                text-align: center;
                line-height: 18px;
                cursor: pointer
            }
            .hidden {
                display: none
            }
        </style>
    </head>
    <body>
        <figure>
            <div id="stream-container" class="image-container hidden">
                <div class="close" id="close-stream">×</div>
                <img id="stream" src="">
            </div>
        </figure>
  <!-- Размер и положение списка файлов -->
        <iframe id="ifr" width="410" height="200" style=" position:absolute; left:400px;"></iframe> 
        <section class="main">
            <div id="logo">
                <label for="nav-toggle-cb" id="nav-toggle">&#9776;&nbsp;&nbsp;Настройки камеры</label>
            </div>
            <div id="content">
                <div id="sidebar">
                    <input type="checkbox" id="nav-toggle-cb" checked="checked">
                    <nav id="menu">
                        <section id="buttons">
                            <button id="restart">Перезапуск</button>
                            <button id="get-still" style="display:none">Still</button>
                            <button id="stopStream">Стоп</button>
                            <button id="startStream">Видео</button>                                                        
                        </section>
                        <div class="input-group" id="saveStill-group">
                            <label for="saveStill">Запись на диск</label>
                            <section id="buttons">
                            <button id="saveStill">Сохранить</button>
                            </section>
                        </div> 
                        <div class="input-group" id="imageList-group">
                            <label for="imageList">Список файлов</label>
                            <section id="buttons">
                            <button id="imageList">Получить список</button>
                            </section>
                        </div>                                     
                        <div class="input-group" id="flash-group">
                            <label for="flash">Яркость</label>
                            <div class="range-min">0</div>
                            <input type="range" id="flash" min="0" max="255" value="0" class="default-action">
                            <div class="range-max">255</div>
                        </div>
                        <div class="input-group" id="framesize-group">
                            <label for="framesize">Разрешение</label>
                            <select id="framesize" class="default-action">
                                <option value="10">UXGA(1600x1200)</option>
                                <option value="9">SXGA(1280x1024)</option>
                                <option value="8">XGA(1024x768)</option>
                                <option value="7">SVGA(800x600)</option>
                                <option value="6">VGA(640x480)</option>
                                <option value="5" selected="selected">CIF(400x296)</option>
                                <option value="4">QVGA(320x240)</option>
                                <option value="3">HQVGA(240x176)</option>
                                <option value="0">QQVGA(160x120)</option>
                            </select>
                        </div>
                                               <div class="input-group" id="quality-group">
                            <label for="quality">Качество</label>
                            <div class="range-min">10</div>
                            <input type="range" id="quality" min="10" max="63" value="10" class="default-action">
                            <div class="range-max">63</div>
                        </div>
                        <div class="input-group" id="brightness-group">
                            <label for="brightness">Яркость</label>
                            <div class="range-min">-2</div>
                            <input type="range" id="brightness" min="-2" max="2" value="1" class="default-action">
                            <div class="range-max">2</div>
                        </div>
                        <div class="input-group" id="contrast-group">
                            <label for="contrast">Контрастность</label>
                            <div class="range-min">-2</div>
                            <input type="range" id="contrast" min="-2" max="2" value="1" class="default-action">
                            <div class="range-max">2</div>
                        </div>
                        <div class="input-group" id="saturation-group">
                            <label for="saturation">Насыщенность</label>
                            <div class="range-min">-2</div>
                            <input type="range" id="saturation" min="-2" max="2" value="1" class="default-action">
                            <div class="range-max">2</div>
                        </div>
                    </nav>
                </div>
            </div>
        </section>       
        <span id="message" style="color:red"></span><br>
                
        <script>
document.addEventListener('DOMContentLoaded', function (event) {
  var baseHost = document.location.origin
  const hide = el => {
    el.classList.add('hidden')
  }
  const show = el => {
    el.classList.remove('hidden')
  }
  const disable = el => {
    el.classList.add('disabled')
    el.disabled = true
  }
  const enable = el => {
    el.classList.remove('disabled')
    el.disabled = false
  }
  const updateValue = (el, value, updateRemote) => {
    updateRemote = updateRemote == null ? true : updateRemote
    let initialValue
    if (el.type === 'checkbox') {
      initialValue = el.checked
      value = !!value
      el.checked = value
    } else {
      initialValue = el.value
      el.value = value
    }
    if (updateRemote && initialValue !== value) {
      updateConfig(el);
    }
  }
  function updateConfig (el) {
    let value
    switch (el.type) {
      case 'checkbox':
        value = el.checked ? 1 : 0
        break
      case 'range':
      case 'select-one':
        value = el.value
        break
      case 'button':
      case 'submit':
        value = '1'
        break
      default:
        return
    }
    var query = `${baseHost}/?${el.id}=${value}`
    fetch(query)
      .then(response => {
        console.log(`request to ${query} finished, status: ${response.status}`)
      })
  }
  document
    .querySelectorAll('.close')
    .forEach(el => {
      el.onclick = () => {
        hide(el.parentNode)
      }
    })
  // read initial values
  fetch(`${baseHost}/?status`)
    .then(function (response) {
      return response.json()
    })
    .then(function (state) {
      document
        .querySelectorAll('.default-action')
        .forEach(el => {
          if (el.id=="flash") {  
            flash.value=0;
            fetch(baseHost+"/?flash=0");
          } else {    
            updateValue(el, state[el.id], false)
          }
        })
    })
  const view = document.getElementById('stream')
  const viewContainer = document.getElementById('stream-container')
  const stillButton = document.getElementById('get-still')
  const streamButton = document.getElementById('startStream')
  const stopButton = document.getElementById('stopStream')
  const closeButton = document.getElementById('close-stream')
  const message = document.getElementById('message');
  const restartButton = document.getElementById('restart')            
  const flash = document.getElementById('flash')
  const saveStill = document.getElementById('saveStill');
  const imageList = document.getElementById('imageList');
  const ifr = document.getElementById('ifr');
              
   var myTimer;
  var restartCount=0;    
  var streamState = false;
  
   streamButton.onclick = function (event) {
    clearInterval(myTimer);
    streamState=true;
    myTimer = setInterval(function(){error_handle();},5000); 
    view.src = location.origin+'/?getstill='+Math.random();
    show(viewContainer);
    //ifr.style.display="none";
  }
  function error_handle() {
    restartCount++;
    clearInterval(myTimer);
    if (restartCount<=2) {
      message.innerHTML = "Получена ошибка. <br> Попробуйте через "+restartCount+" минут.";
      myTimer = setInterval(function(){streamButton.click();},10000);
    }
    else
      message.innerHTML = "Ошибка. <br>Перезагрузите плату ESP32-cAM.";
  }
  
  view.onload = function (event) {
    clearInterval(myTimer);
    restartCount=0;      
    if (streamState==false) return;
    streamButton.click();
  }        
  
  stopButton.onclick = function (event) {
    clearInterval(myTimer);    
    streamState=false;    
    window.stop();
    message.innerHTML = "";
//    ifr.style.display="none";
  }
  imageList.onclick = function (event) {
    show(viewContainer);
    ifr.style.display="block";
    ifr.src = baseHost+'?listimages';
  }
  saveStill.onclick = function (event) {
    show(viewContainer);
    ifr.style.display="block";
    ifr.src =baseHost+'?saveimage='+(new Date().getFullYear()*10000000000+(new Date().getMonth()+1)*100000000+new Date().getDate()*1000000+new Date().getHours()*10000+new Date().getMinutes()*100+new Date().getSeconds()+new Date().getSeconds()*0.001).toString();
  }      
   
  stillButton.onclick = () => {
    stopButton.click();
    view.src = `${baseHost}/?getstill=${Date.now()}`
    show(viewContainer);     
  }
  closeButton.onclick = () => {
    hide(viewContainer)
  }
  restartButton.onclick = () => {
    fetch(baseHost+"/?restart");
  }    
  document
    .querySelectorAll('.default-action')
    .forEach(el => {
      el.onchange = () => updateConfig(el)
    })
  const framesize = document.getElementById('framesize')
  framesize.onchange = () => {
    updateConfig(framesize)
  }
})
        </script>
    </body>
</html>)rawliteral";

//json
void status(){
  sensor_t * s = esp_camera_sensor_get();
  String json = "{";
  json += "\"framesize\":"+String(s->status.framesize)+",";
  json += "\"quality\":"+String(s->status.quality)+",";
  json += "\"brightness\":"+String(s->status.brightness)+",";
  json += "\"contrast\":"+String(s->status.contrast)+",";
  json += "\"saturation\":"+String(s->status.saturation)+",";
  json += "\"special_effect\":"+String(s->status.special_effect)+",";
  json += "\"vflip\":"+String(s->status.vflip)+",";
  json += "\"hmirror\":"+String(s->status.hmirror);
  json += "}";
  
  client.println("HTTP/1.1 200 OK");
  client.println("Access-Control-Allow-Headers: Origin, X-Requested-With, Content-Type, Accept");
  client.println("Access-Control-Allow-Methods: GET,POST,PUT,DELETE,OPTIONS");
  client.println("Content-Type: application/json; charset=utf-8");
  client.println("Access-Control-Allow-Origin: *");
  client.println("Connection: close");
  client.println();
  
  for (int Index = 0; Index < json.length(); Index = Index+1024) {
    client.print(json.substring(Index, Index+1024));
  }
}

// Feedback
void mainpage() {
  client.println("HTTP/1.1 200 OK");
  client.println("Access-Control-Allow-Headers: Origin, X-Requested-With, Content-Type, Accept");
  client.println("Access-Control-Allow-Methods: GET,POST,PUT,DELETE,OPTIONS");
  client.println("Content-Type: text/html; charset=utf-8");
  client.println("Access-Control-Allow-Origin: *");
  client.println("Connection: close");
  client.println();
  
  String Data="";
  if (cmd!="")
    Data = Feedback;
  else
    Data = String((const char *)INDEX_HTML);
  
  for (int Index = 0; Index < Data.length(); Index = Index+1024) {
    client.print(Data.substring(Index, Index+1024));
  } 
}


void getStill() {
  camera_fb_t * fb = NULL;
  fb = esp_camera_fb_get();  
  if(!fb) {
    Serial.println("Сбой захвата камеры");
    delay(1000);
    ESP.restart();
  }

  client.println("HTTP/1.1 200 OK");
  client.println("Access-Control-Allow-Origin: *");              
  client.println("Access-Control-Allow-Headers: Origin, X-Requested-With, Content-Type, Accept");
  client.println("Access-Control-Allow-Methods: GET,POST,PUT,DELETE,OPTIONS");
  client.println("Content-Type: image/jpeg");
  client.println("Content-Disposition: form-data; name=\"imageFile\"; filename=\"picture.jpg\""); 
  client.println("Content-Length: " + String(fb->len));             
  client.println("Connection: close");
  client.println();
  
  uint8_t *fbBuf = fb->buf;
  size_t fbLen = fb->len;
  for (size_t n=0;n<fbLen;n=n+1024) {
    if (n+1024<fbLen) {
      client.write(fbBuf, 1024);
      fbBuf += 1024;
    }
    else if (fbLen%1024>0) {
      size_t remainder = fbLen%1024;
      client.write(fbBuf, remainder);
    }
  }  
  esp_camera_fb_return(fb);

  pinMode(4, OUTPUT);
  digitalWrite(4, LOW);              
}

String saveCapturedImage(String filename) {    
  String response = ""; 
  String path_jpg = "/"+filename+".jpg";

  camera_fb_t * fb = NULL;
  fb = esp_camera_fb_get();  
  if(!fb) {
    Serial.println("Сбой захвата камеры");
    return "<font color=Red>Сбой захвата камеры</font>";
  }

  //SD Card
  if(!SD_MMC.begin()){
    response = "Не установлена Карта памяти";
    return "<font color=yellow>Не установлена Карта памяти</font>";
  }  
  
  fs::FS &fs = SD_MMC; 
  Serial.printf("Имя файла-картинки: %s\n", path_jpg.c_str());

  File file = fs.open(path_jpg.c_str(), FILE_WRITE);
  if(!file){
    esp_camera_fb_return(fb);
    SD_MMC.end();
    return "<font color=Red>Не удалось открыть файл в режиме записи</font>";
  } 
  else {
    file.write(fb->buf, fb->len);
    Serial.printf("Файл записан по адресу: %s\n", path_jpg.c_str());
  }
  file.close();
  SD_MMC.end();

  esp_camera_fb_return(fb);
  Serial.println("");

  pinMode(4, OUTPUT);
  digitalWrite(4, LOW);  
  
  return response;
}

String ListImages() {
  //SD Card
  if(!SD_MMC.begin()){
    Serial.println("Не установлена Карта памяти");
    return "<font color=Red>Не установлена Карта памяти</font>";
  }  
  
  fs::FS &fs = SD_MMC; 
  File root = fs.open("/");
  if(!root){
    Serial.println("Не удалось открыть каталог");
    return "<font color=Red>Не удалось открыть каталог</font>";
  }

  String list="";
  File file = root.openNextFile();
  while(file){
    if(!file.isDirectory()){
      String filename=String(file.name());
      if (filename=="/"+P1+".jpg"){
        
        list = "<tr style=\"border: 2px solid red\"><td><button onclick=\'location.href = location.origin+\"?deleteimage="+String(file.name())+"\";\'>Удалить</button></td><td><font color=Green>"+String(file.name())+"</font></td><td align=\'right\'><font color=Green>"+String(file.size())+"</font></td><td><button onclick=\'parent.document.getElementById(\"stream\").src=location.origin+\"?showimage="+String(file.name())+"\";\'>Смотреть</button></td></tr>"+list;
      } else
        list = "<tr><td><button onclick=\'location.href = location.origin+\"?deleteimage="+String(file.name())+"\";\'>Удалить</button></td><td><font color=Green>"+String(file.name())+"</font></td><td align=\'right\'><font color=Green>"+String(file.size())+"</font></td><td><button onclick=\'parent.document.getElementById(\"stream\").src=location.origin+\"?showimage="+String(file.name())+"\";\'>Смотреть</button></td></tr>"+list;        
    }
    file = root.openNextFile();
  }
  list="<table border=1><tr><td align=\'center\'><font color=Silver>Удалить</font></td><td align=\'center\'><font color=White>Имя файла</font></td><td align=\'center\'><font color=White>Размер</font></td><td align=\'center\'><font color=Silver>Смотреть</font></td></tr>"+list+"</table>";

  file.close();
  SD_MMC.end();

  pinMode(4, OUTPUT);
  digitalWrite(4, LOW);   
  
  return list;
}

String deleteimage(String filename) {
  //SD Card
  if(!SD_MMC.begin()){
    Serial.println("Не установлена Карта памяти");
    return "Не установлена Карта памяти";
  }  
  
  fs::FS &fs = SD_MMC;
  File file = fs.open(filename);
  String message="";
  if(fs.remove(filename)){
      message = "<font color=Red>" + filename + " Файл удалён</font>";
  } else {
      message = "<font color=Red>" + filename + " удалён</font>";
  }
  file.close();
  SD_MMC.end();

  pinMode(4, OUTPUT);
  digitalWrite(4, LOW);   

  return message;
}

void showimage() {
  if(!SD_MMC.begin()){
    Serial.println("Не установлена Карта памяти");
  }  
  Serial.println(P1);
  fs::FS &fs = SD_MMC;
  File file = fs.open(P1);
  if(!file){
    Serial.println("Не удалось открыть файл для чтения");
    SD_MMC.end();    
  }
  else {
    Serial.println("Считать файл: "+P1);
    Serial.println("Размер файла: "+String(file.size()));            

    client.println("HTTP/1.1 200 OK");
    client.println("Access-Control-Allow-Origin: *");              
    client.println("Access-Control-Allow-Headers: Origin, X-Requested-With, Content-Type, Accept");
    client.println("Access-Control-Allow-Methods: GET,POST,PUT,DELETE,OPTIONS");
    client.println("Content-Type: image/jpeg");
    P1.replace("/","");
    client.println("Content-Disposition: form-data; name=\"imageFile\"; filename=\""+P1+"\""); 
    client.println("Content-Length: " + String(file.size()));             
    client.println("Connection: close");
    client.println();

    byte buf[1024];
    int i = -1;
    while (file.available()) {
      i++;
      buf[i] = file.read();
      if (i==(sizeof(buf)-1)) {
        client.write((const uint8_t *)buf, sizeof(buf));
        i = -1;
      }
      else if (!file.available())
        client.write((const uint8_t *)buf, (i+1));
    }

    client.println();

    file.close();
    SD_MMC.end();
  }

  pinMode(4, OUTPUT);
  digitalWrite(4, LOW);
}

void getCommand(char c) {
  if (c=='?') ReceiveState=1;
  if ((c==' ')||(c=='\r')||(c=='\n')) ReceiveState=0;
  
  if (ReceiveState==1)
  {
    Command=Command+String(c);
    
    if (c=='=') cmdState=0;
    if (c==';') strState++;
  
    if ((cmdState==1)&&((c!='?')||(questionstate==1))) cmd=cmd+String(c);
    if ((cmdState==0)&&(strState==1)&&((c!='=')||(equalstate==1))) P1=P1+String(c);
    if ((cmdState==0)&&(strState==2)&&(c!=';')) P2=P2+String(c);
    if ((cmdState==0)&&(strState==3)&&(c!=';')) P3=P3+String(c);
    if ((cmdState==0)&&(strState==4)&&(c!=';')) P4=P4+String(c);
    if ((cmdState==0)&&(strState==5)&&(c!=';')) P5=P5+String(c);
    if ((cmdState==0)&&(strState==6)&&(c!=';')) P6=P6+String(c);
    if ((cmdState==0)&&(strState==7)&&(c!=';')) P7=P7+String(c);
    if ((cmdState==0)&&(strState==8)&&(c!=';')) P8=P8+String(c);
    if ((cmdState==0)&&(strState>=9)&&((c!=';')||(semicolonstate==1))) P9=P9+String(c);
    
    if (c=='?') questionstate=1;
    if (c=='=') equalstate=1;
    if ((strState>=9)&&(c==';')) semicolonstate=1;
  }
}
