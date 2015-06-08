Servo myservo;  // create servo object to control a servo
                // a maximum of eight servo objects can be created
#include <string.h>
#define LIB_DOMAIN "viget.fwd.wf"

TCPClient client;
int buttonPin = D6;
int ledPin = D7;

int min = 20;
int max = 90;

int pos = min;    // variable to store the servo position

void setup()
{
  Spark.function("pour", pour);
  myservo.attach(D0);  // attaches the servo on pin 0 to the servo object
  pinMode(buttonPin, INPUT);
  pinMode(ledPin, OUTPUT);

}

void loop()
{
  myservo.write(min);
  digitalWrite(ledPin, HIGH);

  if (digitalRead(buttonPin) == HIGH) {
      digitalWrite(ledPin, LOW);

      client.connect(LIB_DOMAIN, 80);
      client.println("GET /identify HTTP/1.0");
      client.println("Host: " LIB_DOMAIN);
      client.println("Content-Length: 0");
      client.println();
      client.flush();

      for(pos = min; pos < max; pos += 1)  // goes from 0 degrees to 180 degrees
      {                                  // in steps of 1 degree
        myservo.write(pos);              // tell servo to go to position in variable 'pos'
        delay(15);                       // waits 15ms for the servo to reach the position
      }

      delay(2500);

      for(pos = max; pos > min; pos -= 1)     // goes from 180 degrees to 0 degrees
      {
        myservo.write(pos);              // tell servo to go to position in variable 'pos'
        delay(15);                       // waits 15ms for the servo to reach the position
      }

      NVIC_SystemReset();
  }
}

int pour(String _) {
      for(pos = min; pos < max; pos += 1)  // goes from 0 degrees to 180 degrees
      {                                  // in steps of 1 degree
        myservo.write(pos);              // tell servo to go to position in variable 'pos'
        delay(15);                       // waits 15ms for the servo to reach the position
      }

      delay(2500);

      for(pos = max; pos > min; pos -= 1)     // goes from 180 degrees to 0 degrees
      {
        myservo.write(pos);              // tell servo to go to position in variable 'pos'
        delay(15);                       // waits 15ms for the servo to reach the position
      }
      return 1;
}
