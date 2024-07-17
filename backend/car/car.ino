#include <DHT.h>
#include <DHT_U.h>

#include <WiFi.h>
#include <AsyncTCP.h>

// #include <ESP8266WiFi.h>
// #include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <ESP32Servo.h>

#define DHTPIN 17
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);
Servo servos[4];
const int servoPins[4] = {25, 33, 32, 35};
const int trigPin = 5;
const int echoPin = 16;
#define SOUND_SPEED 0.034
float distance = 0;
float temp = 0;
float humi = 0;

const char* ssid = "tailoc";
const char* password = "malochtailoc";
AsyncWebServer server(80);

int in1 = 13;
int in2 = 12;
int in3 = 14;
int in4 = 27;

void move(String direction) {
  if (direction == "down") {
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
  } else if (direction == "up") {
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
  } else if (direction == "left") {
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);
  } else if (direction == "right") {
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
  } else {
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);
  }
}
float srf05() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  float duration = pulseIn(echoPin, HIGH);
  return duration * SOUND_SPEED / 2;
}

void servoHandler(int servoIndex, int value) {
  servoIndex = servoIndex - 1;
  if (servoIndex >= 0 && servoIndex < 4) {
    servos[servoIndex].attach(servoPins[servoIndex]);
    servos[servoIndex].write(value);
    delay(2000);
    servos[servoIndex].detach();
  }
}

void setup() {
  // put your setup code here, to run once:
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  servos[0].attach(servoPins[0]);
  servos[1].attach(servoPins[1]);
  servos[2].attach(servoPins[2]);
  servos[3].attach(servoPins[3]);

  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
  }
  Serial.println(WiFi.localIP());

  server.on("/api/post/move", HTTP_POST, [](AsyncWebServerRequest* request) {
    if (request->hasParam("direction")) {
      String direction = request->getParam("direction")->value();
      Serial.println(direction);
      move(direction);
      request->send(200, "text/plain", "Success");
      delay(200);
      move("stop");
    } else {
      request->send(400, "text/plain", "Fail");
    }
  });

  server.on("/api/post/arm", HTTP_POST, [](AsyncWebServerRequest* request) {
    if (request->hasParam("servo") && request->hasParam("value")) {
      String servo = request->getParam("servo")->value();
      String value = request->getParam("value")->value();
      Serial.print("servo: ");
      Serial.print(servo);
      Serial.print("; value: ");
      Serial.println(value);
      servoHandler(servo.toInt(), value.toInt());
      request->send(200, "text/plain", "Success");
    } else {
      request->send(400, "text/plain", "Fail");
    }
  });

  server.on("/api/get/ultraSonic", HTTP_GET, [](AsyncWebServerRequest* request) {
    // Serial.println(srf05());
    AsyncWebServerResponse* response = request->beginResponse(200, "text/plain", String(distance));
    response->addHeader("Access-Control-Allow-Origin", "*");
    request->send(response);
  });

  server.on("/api/get/temp", HTTP_GET, [](AsyncWebServerRequest* request) {
    temp = dht.readTemperature();
    AsyncWebServerResponse* response = request->beginResponse(200, "text/plain", String(temp));
    response->addHeader("Access-Control-Allow-Origin", "*");
    request->send(response);
  });

  server.on("/api/get/humi", HTTP_GET, [](AsyncWebServerRequest* request) {
    humi = dht.readHumidity();
    AsyncWebServerResponse* response = request->beginResponse(200, "text/plain", String(humi));
    response->addHeader("Access-Control-Allow-Origin", "*");
    request->send(response);
  });

  server.begin();
}
void loop() {
  // put your main code here, to run repeatedly:
}
