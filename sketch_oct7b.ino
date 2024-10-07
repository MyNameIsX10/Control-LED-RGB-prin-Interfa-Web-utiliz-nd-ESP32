#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>

const char* ssid = "Orange-57489E45";  // Numele rețelei WiFi
const char* password = "7R563YED1YJ";  // Parola rețelei WiFi

AsyncWebServer server(80);  // Inițializăm serverul web pe portul 80

// Pini pentru LED RGB
#define PIN_RED   25
#define PIN_GREEN 26
#define PIN_BLUE  27

// Variabile pentru a stoca intensitățile curente pentru fiecare canal (PWM)
int redValue = 255;
int greenValue = 255;
int blueValue = 255;
int brightness = 255;  // Luminozitatea generală

// Variabilă pentru starea LED-ului (pornit/oprit)
bool ledOn = true;

// Funcția pentru a actualiza LED-ul RGB în funcție de culoare și luminozitate
void updateLED() {
  if (ledOn) {
    analogWrite(PIN_RED, redValue * brightness / 255);
    analogWrite(PIN_GREEN, greenValue * brightness / 255);
    analogWrite(PIN_BLUE, blueValue * brightness / 255);
  } else {
    analogWrite(PIN_RED, 0);
    analogWrite(PIN_GREEN, 0);
    analogWrite(PIN_BLUE, 0);
  }
}

void setup() {
  // Inițializăm pini LED RGB ca ieșiri PWM
  pinMode(PIN_RED, OUTPUT);
  pinMode(PIN_GREEN, OUTPUT);
  pinMode(PIN_BLUE, OUTPUT);

  // Conectare la rețeaua WiFi
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Se incearca conectarea la WiFi...");
  }
  Serial.println("Conectat la WiFi!");
  Serial.println(WiFi.localIP());

  // Ruta principală (pagina HTML pentru controlul LED-ului)
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(200, "text/html", R"rawliteral(
      <!DOCTYPE html>
      <html>
      <head>
        <title>Control LED RGB</title>
        <style>
                  @import url('https://fonts.googleapis.com/css2?family=Poppins:ital,wght@0,100;0,200;0,300;0,400;0,500;0,600;0,700;0,800;0,900;1,100;1,200;1,300;1,400;1,500;1,600;1,700;1,800;1,900&display=swap');

                    *{
                      margin: 0;
                      padding: 0;
                      box-sizing: border-box;
                      font-family: "Poppins", sans-serif;
                    }

                    body{
                      display: flex;
                      align-items: center;
                      justify-content: center;
                      min-height: 100vh;
                      background: rgb(0, 183, 255);

                    }

                    .container{
                      height: 300px;
                      display: flex;
                      align-items: center;
                      justify-content: center;
                      flex-direction: column;
                      border: 2px solid rgba(0, 0, 0, .1);
                      border-radius: 20px;
                      outline: none;
                      width: 420px;
                      padding: 30px 40px;
                      background-color: lightblue;
                    }

                    h1{
                    font-size: 36px;
                    margin-bottom: 5px;
                    }

                    .text{
                      font-size: 20px;
                      margin-top: 10px;
                    }

                    .btn{
                      padding: 10px;
                      border: none;
                      outline: none;
                      background-color: lightskyblue;
                      color: white;
                      border-radius: 20px;
                      cursor: pointer;
                      margin-top: 10px;
                      transition: background-color 0.15s;
                      transition: scale .2 ease;
                    }

                    .btn:hover{
                    background-color: lightgray;
                    color: black;
                    scale: 1.05;
                    }

                    .btn:active{
                      scale: 0.95;
                    }

                    .RGB {
                      width: 50px;
                      height: 50px;
                      border: 2px solid lightgray; 
                      border-radius: 6px; /* Slightly rounded corners */
                      cursor: pointer;
                      padding: 0;
                      box-shadow: none; 
                      background-color: transparent; 
                      transition: border-color 0.3s ease;
                    }

                    .RGB:hover {
                      border-color: #888; 
                    }

                    .RGB:focus {
                      outline: none;
                      border-color: #0056b3; 
                    }
 
        
         

          
        </style>
      </head>
      <body>
        <div class="container">
          <h1>Control LED RGB</h1>
          
          <label class="text" for="brightness">Intensitate:</label>
          <input type="range" id="brightness" min="0" max="255" value="255" class="slider">
          
          <br><br>
          <label class="text" for="rgbColor">Culoare RGB:</label>
          <input class="RGB" type="color" id="rgbColor" value="#ffffff">

          <br><br>
          <button class="btn "id="toggleBtn">ON/OFF</button>
        </div>
        <script>
          document.getElementById('brightness').addEventListener('input', function() {
            var brightness = this.value;
            fetch('/setBrightness?value=' + brightness);
          });

          document.getElementById('rgbColor').addEventListener('input', function() {
            var rgb = this.value.substring(1);  // Eliminam #
            var red = parseInt(rgb.substring(0, 2), 16);
            var green = parseInt(rgb.substring(2, 4), 16);
            var blue = parseInt(rgb.substring(4, 6), 16);
            fetch('/setColor?red=' + red + '&green=' + green + '&blue=' + blue);
          });

          document.getElementById('toggleBtn').addEventListener('click', function() {
            fetch('/toggleLED');
          });
        </script>
      </body>
      </html>
    )rawliteral");
  });

  // Ruta pentru a seta luminozitatea
  server.on("/setBrightness", HTTP_GET, [](AsyncWebServerRequest *request){
    if (request->hasParam("value")) {
      brightness = request->getParam("value")->value().toInt();
      updateLED();  // Actualizăm LED-ul
    }
    request->send(200, "text/plain", "OK");
  });

  // Ruta pentru a seta culoarea RGB
  server.on("/setColor", HTTP_GET, [](AsyncWebServerRequest *request){
    if (request->hasParam("red") && request->hasParam("green") && request->hasParam("blue")) {
      redValue = request->getParam("red")->value().toInt();
      greenValue = request->getParam("green")->value().toInt();
      blueValue = request->getParam("blue")->value().toInt();
      updateLED();  // Actualizăm LED-ul
    }
    request->send(200, "text/plain", "OK");
  });

  // Ruta pentru a porni/opri LED-ul
  server.on("/toggleLED", HTTP_GET, [](AsyncWebServerRequest *request){
    ledOn = !ledOn;
    updateLED();  // Actualizăm LED-ul
    request->send(200, "text/plain", "OK");
  });

  // Pornim serverul
  server.begin();
}

void loop() {
  // Nimic de făcut aici, serverul web rulează în fundal
}
