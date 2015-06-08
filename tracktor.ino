#include "rest_client.h"

RestClient client = RestClient("tracktor.herokuapp.com");

const int button1 = D5;
const int button2 = D4;
const int button3 = D3;
const int button4 = D2;
const int button5 = D1;
const int button6 = D0;

const int led1 = A5;
const int led2 = A4;
const int led3 = A3;
const int led4 = A2;
const int led5 = A1;
const int led6 = A0;

String response;
String pathString;
String token = "not set";
char path[50];
int  led;
int  runningTimer;
bool initialized = false;

void setup() {
    Serial.begin(9600);

    pinMode(button1, INPUT);
    pinMode(button2, INPUT);
    pinMode(button3, INPUT);
    pinMode(button4, INPUT);
    pinMode(button5, INPUT);
    pinMode(button6, INPUT);

    pinMode(led1, OUTPUT);
    pinMode(led2, OUTPUT);
    pinMode(led3, OUTPUT);
    pinMode(led4, OUTPUT);
    pinMode(led5, OUTPUT);
    pinMode(led6, OUTPUT);

    preLightShow();
}

void loop() {
    if (!initialized) {
        delay(3000);
        identify();

        if (token != "not set" && token != "") {
            delay(3000);
            int runningTimer = checkRunningTimer();
            initialized = true;
            lightShow();
            turnOn(runningTimer);
        }
    }

    if (digitalRead(button1) == HIGH) buttonPress(1);
    if (digitalRead(button2) == HIGH) buttonPress(2);
    if (digitalRead(button3) == HIGH) buttonPress(3);
    if (digitalRead(button4) == HIGH) buttonPress(4);
    if (digitalRead(button5) == HIGH) buttonPress(5);
    if (digitalRead(button6) == HIGH) buttonPress(6);
}

void identify() {
    Serial.println("Requesting token");

    response   = "";
    pathString = "/identify?core_id=" + Spark.deviceID();
    pathString.toCharArray(path, 50);

    int _statusCode = client.get(path, &response);

    Serial.println("Token API response: " + response);

    token = response;
}

void buttonPress(int button) {
    Serial.println("Button pressed: " + String(button));

    response   = "";
    pathString = "/toggle?token=" + token + "&button=" + String(button);
    pathString.toCharArray(path, 50);

    int _statusCode = client.get(path, &response);

    Serial.println("Button press API response: " + response);

    if (response == "on") {
        turnOn(button);
    }
    else {
        turnAll(LOW);
    }
}

int checkRunningTimer() {
    Serial.println("Checking running timer");

    response   = "";
    pathString = "/running_timer?token=" + token;
    pathString.toCharArray(path, 50);

    int _statusCode = client.get(path, &response);

    Serial.println("Running timer API response: " + response);

    return response.toInt();
}

void turnOn(int button) {
    switch (button) {
        case 1: led = led1; break;
        case 2: led = led2; break;
        case 3: led = led3; break;
        case 4: led = led4; break;
        case 5: led = led5; break;
        case 6: led = led6; break;
    }

    Serial.println("Turning on: " + String(button) + " (led #" + String(led) + ")");

    turnAll(LOW);
    digitalWrite(led, HIGH);
}

void turnAll(int value) {
    digitalWrite(led1, value);
    digitalWrite(led2, value);
    digitalWrite(led3, value);
    digitalWrite(led4, value);
    digitalWrite(led5, value);
    digitalWrite(led6, value);
}

void preLightShow() {
    Serial.println("Pre Light Show");

    digitalWrite(led1, HIGH);
    delay(400);
    digitalWrite(led2, HIGH);
    delay(400);
    digitalWrite(led3, HIGH);
    delay(400);
    digitalWrite(led4, HIGH);
    delay(400);
    digitalWrite(led5, HIGH);
    delay(400);
    digitalWrite(led6, HIGH);
}

void lightShow() {
    Serial.println("Light Show");

    turnAll(LOW);
    delay(200);
    turnAll(HIGH);
    delay(200);
    turnAll(LOW);
}
