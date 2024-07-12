#include <WiFi.h>
#include <AsyncTCP.h>

// #include <ESP8266WiFi.h>
// #include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <ESP32Servo.h>

Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;
const int servoPin1 = 25;
const int servoPin2 = 33;
const int servoPin3 = 32;
const int servoPin4 = 35;
const int trigPin = 5;
const int echoPin = 16;
#define SOUND_SPEED 0.034
float distance = 0;

const char* ssid = "Lan Duy";
const char* password = "landuy1004";
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

void servoHandler(String servo, int value) {
  if(servo == "1") {
    servo1.write(value);
  } else if(servo == "2") {
    servo2.write(value);
  } else if(servo == "3") {
    servo3.write(value);
  } else if(servo == "4") {
    servo4.write(value);
  }
}

void setup() {
  // put your setup code here, to run once:
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  servo1.attach(servoPin1);
  servo2.attach(servoPin2);
  servo3.attach(servoPin3);
  servo4.attach(servoPin4);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

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
      servoHandler(servo, value.toInt());
      request->send(200, "text/plain", "Success");
    } else {
      request->send(400, "text/plain", "Fail");
    }
  });

  server.on("/api/get/ultraSonic", HTTP_GET, [](AsyncWebServerRequest* request) {
    // Serial.println(srf05());
    AsyncWebServerResponse *response = request->beginResponse(200, "text/plain", String(distance));
    response->addHeader("Access-Control-Allow-Origin", "*");
    request->send(response);
  });

  server.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
}
