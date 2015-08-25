/*
 * Joystick Surveillance Camera - Client
 * 
 * This sketch gets the x-coordinate value stored on the Host Galileo
 * to determine when to move and how fast to move the Camera that 
 * is mounted on the Servo Motor connected to the Intel Galileo Gen 2
 * 
 * created 24 August 2015
 * by Andrew Nava-Juarez
 */
 
#include <SPI.h>
#include <Ethernet.h>
#include <Servo.h>

Servo myservo;

int pos = 100;
int verticalRead = 400;

String reading = "";
int value = 0;

byte mac[] = {  0x98, 0x4F, 0xEE, 0x00, 0x0B, 0xD3 };
IPAddress server(10,0,0,4); // Ip Address of Host Galileo
EthernetClient client;

void setup() {
  Serial.begin(9600);
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
    while(1) {}
  }
  // give the Ethernet shield a second to initialize:
  delay(1000);

  myservo.attach(6);
  myservo.write(pos);
}

void boundaryCheck(){
  if(pos > 180)
    pos = 180;
  if(pos < 5)
    pos = 5;
}

int getReading(){
  int readingValue = 0;
  if (client.connect(server, 80)) {
    client.println("GET /request.txt HTTP/1.1");
    client.print( "Host: " );
    client.println( "10.0.0.4" );
    
    client.println();
    client.println();
  } 
  else {
    // if you didn't get a connection to the server:
    Serial.println("connection failed");
  }

  if (client.available()) {
    client.find("Joystick: ");
    while(1){
      
      char c = client.read();
      if(c == 'E')
        break;

      else if(isDigit(c))
        reading.concat(c);
      
      else
        break;
    }
    readingValue = reading.toInt();
    reading = "";
    client.stop();
  }
  return readingValue;
}

void loop()
{
  value = getReading();
  if(value > 800){
    while(getReading() > 800){
      pos = pos + 3;
      boundaryCheck();
      myservo.write(pos);
    }
  }
  else if(value > 420){
    while(getReading() > 420){
      boundaryCheck();
      myservo.write(++pos);
    }
  }
  else if(value < 100){
    while(getReading() < 100){
      pos = pos - 3;
      boundaryCheck();
      myservo.write(pos);
    }
  }
  else if(value < 380){
    while(getReading() < 380){
      boundaryCheck();
      myservo.write(--pos);
    }
  }
  delay(500);
}

