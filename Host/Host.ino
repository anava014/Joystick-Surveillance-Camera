/*
 * Joystick Surveillance Camera - Host
 * 
 * This sketch receives the x-coordinate reading on a joystick
 * connected to the Intel Galileo and stores the value in a server
 * hosted on the linux portion of the Galileo.
 * 
 * created 24 August 2015
 * by Andrew Nava-Juarez
 */

String content = "";
char character;
char bufferd[99];

int joystick = A5;
int reading;
bool dataSent = false;

void setup() {
  Serial.begin(9600);

  pinMode(joystick, INPUT);
  
  Serial.println("connecting...");
  system("ifup eth0");
}
 
void loop() {
  reading = analogRead(joystick);
  
  if(reading < 380 || reading > 420){
    content.concat("echo Joystick: ");
    content.concat(reading);
    content.concat("E > /var/www/request.txt");
    content.toCharArray(bufferd, content.length() + 1);
    system(bufferd);
    content = "";
    dataSent = false;
  }
  else if(!dataSent){ //Else if and Boolean to prevent unnecessary writes to SD Card
    content.concat("echo Joystick: ");
    content.concat(reading);
    content.concat("E > /var/www/request.txt");
    content.toCharArray(bufferd, content.length() + 1);
    system(bufferd);
    content = "";
    dataSent = true;
  }

  delay(500);
}
