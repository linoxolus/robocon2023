#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <AsyncTCP.h>

const char* ssid = "HOAN";
const char* password = "13122008";
AsyncWebServer server(80);

int in1 = 15;
int in2 = 16;
int in3 = 17;
int in4 = 18;

void move(String direction) {
  if (direction == "up") {
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
  } else if (direction == "down") {
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
  } else if (direction == "left") {
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
  } else if (direction == "right") {
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);
  } else {
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);
  }
}

void setup() {
  // put your setup code here, to run once:
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
  }
  Serial.println(WiFi.localIP());

  server.on("/move/", HTTP_POST, [](AsyncWebServerRequest* request) {
          if (request->hasParam("direction")) {
            String direction = request->getParam("direction")->value();
            Serial.println(direction);
            move(direction);
            request->send(200, "text/plain", "Success");
            delay(10);
            move("stop");
          } else {
            request->send(400, "text/plain", "Fail");
          }
        });

    server.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
}
