#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include <WiFi.h>
#include "config.h"
#include "jointControl.h"
#include "motorControl.h"
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

#define CAR 0
#define SPIDER 1

int g_currentForm = CAR;

// Replace with your network credentials
const char* ssid = "ESP32_AP";          // SSID (name) of the ESP32's access point
const char* password = "password123";   // Password for the access point
WiFiServer server(80);          // Set web server port number to 80
String header;                  // Variable to store the HTTP request
extern String htmlForm;
extern String htmlFormPart1;
extern String htmlFormPart2;
String receivedString = ""; // Store the received string data

void setup() {
//Start Serial
  Serial.begin(9600);
  Serial.println("Serial test!");

//Start WIFI Access Point
  IPAddress localIP(192, 168, 4, 1);
  IPAddress gateway(192, 168, 4, 1);
  IPAddress subnet(255, 255, 255, 0);
  WiFi.softAPConfig(localIP, gateway, subnet);
  WiFi.softAP(ssid, password);
  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);
  server.begin();

//Start PWM servo
  pwm.begin();
  pwm.setPWMFreq(60);

//Set LED
  pinMode(LED_BUILTIN, OUTPUT);

//Setup pin motor
  pinMode(MOTOR_FR_IN1, OUTPUT);
	pinMode(MOTOR_FR_IN2, OUTPUT);
	pinMode(MOTOR_RR_IN3, OUTPUT);
	pinMode(MOTOR_RR_IN4, OUTPUT);
	pinMode(MOTOR_FL_IN3, OUTPUT);
	pinMode(MOTOR_FL_IN4, OUTPUT);
	pinMode(MOTOR_RL_IN1, OUTPUT);
	pinMode(MOTOR_RL_IN2, OUTPUT);
  
  transformstoCar();
  delay(5000);
}
void executeCommand(String inputString)
{
  int stringLength = inputString.length(); // Get the length of the string
  inputString.toLowerCase();
  for (int i = 0; i < stringLength; i++) {
    char currentChar = inputString.charAt(i);
    Serial.println(currentChar);
    parseAndCallFunction(currentChar);
  }
}
void loop() {
  // String inputString = "wwweowwwweodddossseoqwwwo";

  // int stringLength = inputString.length(); // Get the length of the string
  // inputString.toLowerCase();
  // for (int i = 0; i < stringLength; i++) {
  //   char currentChar = inputString.charAt(i);
  //   Serial.println(currentChar);
  //   parseAndCallFunction(currentChar);
  // }

  // while(1);

  WiFiClient client = server.available();   // Listen for incoming clients

  if (client) {                             // If a new client connects,
    digitalWrite(LED_BUILTIN, HIGH);
    Serial.println("New Client.");          // print a message out in the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) {            // loop while the client's connected
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out to the serial monitor
        header += c;
        if (c == '\n') {                    // if the byte is a newline character
          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();

            // If there's POST data, parse and process it
            if (header.indexOf("POST /") >= 0) {
              while (client.available()) {
                char c = client.read();
                receivedString += c;
              }
              int dataStart = receivedString.indexOf("data="); // Find the "data=" string
              if (dataStart >= 0) {
                // Extract the data portion after "data="
                receivedString = receivedString.substring(dataStart+strlen("data="));
              }
              // Print the received string to the serial monitor
              Serial.print("Received String: ");
              Serial.println(receivedString);

              // Process the received string here
              // For example, you can check its content and take specific actions
            }

            // Display the HTML web page
            client.println(htmlFormPart1 + receivedString + htmlFormPart2);
            // The HTTP response ends with another blank line
            client.println();
            
            executeCommand(receivedString);
            // Break out of the while loop
            break;
          } else { // if you got a newline, then clear currentLine
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
      }
    }
    // Clear the header variable and receivedString
    header = "";
    receivedString = "";
    // Close the connection
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }
  else{
    digitalWrite(LED_BUILTIN, LOW);
  }
}

void parseAndCallFunction(const char letter) {
  switch (letter) {
    case 'o':
      delay(1000);
      break;
    case 'w':
      moveForward();
      break;
    case 's':
      moveBackward();
      break;
    case 'd':
      rotateRight();
      break;
    case 'a':
      rotateLeft();
      break;
    case 'q':
      transformstoCar();
      break;
    case 'e':
      transformstoSpider();
      break;
    case 't':
      test();
    default:
      Serial.println("Invalid input.");
      break;
  }
}

void moveBackward()
{
  if(g_currentForm == SPIDER)
  {
    controlArmFR(STAND_ANGLE_ARM_FR);
    controlArmFL(RAISE_ANGLE_ARM_FL);
    controlArmRR(RAISE_ANGLE_ARM_RR);
    controlArmRL(STAND_ANGLE_ARM_RL);
    delay(500);
    controlShoulderFR(MIDDLE_ANGLE_SHOULDER_FR);
    controlShoulderFL(OPEN_ANGLE_SHOULDER_FL);
    controlShoulderRR(MIDDLE_ANGLE_SHOULDER_RR);
    controlShoulderRL(OPEN_ANGLE_SHOULDER_RL);
    delay(300);
    controlArmFR(RAISE_ANGLE_ARM_FR);
    controlArmFL(STAND_ANGLE_ARM_FL);
    controlArmRR(STAND_ANGLE_ARM_RR);
    controlArmRL(RAISE_ANGLE_ARM_RL);
    delay(500);
    controlShoulderFR(OPEN_ANGLE_SHOULDER_FR);
    controlShoulderFL(MIDDLE_ANGLE_SHOULDER_FL);
    controlShoulderRR(OPEN_ANGLE_SHOULDER_RR);
    controlShoulderRL(MIDDLE_ANGLE_SHOULDER_RL);
    delay(300);
  }
  else
  {
    motor_BACKWARD(255);
  }
}

void moveForward()
{
  if(g_currentForm == SPIDER)
  {
    controlArmFR(STAND_ANGLE_ARM_FR);
    controlArmFL(RAISE_ANGLE_ARM_FL);
    controlArmRR(RAISE_ANGLE_ARM_RR);
    controlArmRL(STAND_ANGLE_ARM_RL);
    delay(500);
    controlShoulderFR(OPEN_ANGLE_SHOULDER_FR);
    controlShoulderFL(MIDDLE_ANGLE_SHOULDER_FL);
    controlShoulderRR(OPEN_ANGLE_SHOULDER_RR);
    controlShoulderRL(MIDDLE_ANGLE_SHOULDER_RL);
    delay(300);
    controlArmFR(RAISE_ANGLE_ARM_FR);
    controlArmFL(STAND_ANGLE_ARM_FL);
    controlArmRR(STAND_ANGLE_ARM_RR);
    controlArmRL(RAISE_ANGLE_ARM_RL);
    delay(500);
    controlShoulderFR(MIDDLE_ANGLE_SHOULDER_FR);
    controlShoulderFL(OPEN_ANGLE_SHOULDER_FL);
    controlShoulderRR(MIDDLE_ANGLE_SHOULDER_RR);
    controlShoulderRL(OPEN_ANGLE_SHOULDER_RL);
    delay(300);
  }
  else
  {
    motor_FORWARD(255);
  }
}

void transformstoCar() //e
{
  controlShoulderFR(CLOSE_ANGLE_SHOULDER_FR);
  controlShoulderFL(CLOSE_ANGLE_SHOULDER_FL);
  controlShoulderRR(CLOSE_ANGLE_SHOULDER_RR);
  controlShoulderRL(CLOSE_ANGLE_SHOULDER_RL);
  delay(200);
  controlArmFR(CLOSE_ANGLE_ARM_FR);
  controlArmRL(CLOSE_ANGLE_ARM_RL);
  controlArmFL(CLOSE_ANGLE_ARM_FL);
  controlArmRR(CLOSE_ANGLE_ARM_RR);
  g_currentForm = CAR;
}

void transformstoSpider() //f
{
  controlArmFR(STAND_ANGLE_ARM_FR);
  controlArmRL(STAND_ANGLE_ARM_RL);
  controlArmFL(STAND_ANGLE_ARM_FL);
  controlArmRR(STAND_ANGLE_ARM_RR);
  // delay(400);
  controlShoulderFR(MIDDLE_ANGLE_SHOULDER_FR);
  controlShoulderFL(MIDDLE_ANGLE_SHOULDER_FL);
  controlShoulderRR(MIDDLE_ANGLE_SHOULDER_RR);
  controlShoulderRL(MIDDLE_ANGLE_SHOULDER_RL);
  g_currentForm = SPIDER;
}

void rotateLeft()
{
  if(g_currentForm == SPIDER)
  {
    controlArmFR(STAND_ANGLE_ARM_FR);
    controlArmFL(STAND_ANGLE_ARM_FL);
    controlArmRR(STAND_ANGLE_ARM_RR);
    controlArmRL(STAND_ANGLE_ARM_RL);
    controlShoulderFR(MIDDLE_ANGLE_SHOULDER_FR);
    controlShoulderFL(MIDDLE_ANGLE_SHOULDER_FL);
    controlShoulderRR(MIDDLE_ANGLE_SHOULDER_RR);
    controlShoulderRL(MIDDLE_ANGLE_SHOULDER_RL);
    delay(260);
    controlArmFR(STAND_ANGLE_ARM_FR);
    controlArmFL(RAISE_ANGLE_ARM_FL);
    controlArmRR(RAISE_ANGLE_ARM_RR);
    controlArmRL(STAND_ANGLE_ARM_RL);
    delay(265);
    controlShoulderFR(OPEN_ANGLE_SHOULDER_FR);
    controlShoulderFL(OPEN_ANGLE_SHOULDER_FL);
    controlShoulderRR(OPEN_ANGLE_SHOULDER_RR);
    controlShoulderRL(OPEN_ANGLE_SHOULDER_RL);
    delay(260);
    controlArmFR(STAND_ANGLE_ARM_FR);
    controlArmFL(STAND_ANGLE_ARM_FL);
    controlArmRR(STAND_ANGLE_ARM_RR);
    controlArmRL(STAND_ANGLE_ARM_RL);
    controlShoulderFR(OPEN_ANGLE_SHOULDER_FR);
    controlShoulderFL(OPEN_ANGLE_SHOULDER_FL);
    controlShoulderRR(OPEN_ANGLE_SHOULDER_RR);
    controlShoulderRL(OPEN_ANGLE_SHOULDER_RL);
    delay(260);
    controlArmFR(RAISE_ANGLE_ARM_FR);
    controlArmFL(STAND_ANGLE_ARM_FL);
    controlArmRR(STAND_ANGLE_ARM_RR);
    controlArmRL(RAISE_ANGLE_ARM_RL);
    delay(265);
    controlShoulderFR(MIDDLE_ANGLE_SHOULDER_FR);
    controlShoulderFL(MIDDLE_ANGLE_SHOULDER_FL);
    controlShoulderRR(MIDDLE_ANGLE_SHOULDER_RR);
    controlShoulderRL(MIDDLE_ANGLE_SHOULDER_RL);
    delay(260);
    transformstoSpider();
  }
  else
  {
    
  }
}
void rotateRight()
{
  if(g_currentForm == SPIDER)
  {
    controlArmFR(STAND_ANGLE_ARM_FR);
    controlArmFL(STAND_ANGLE_ARM_FL);
    controlArmRR(STAND_ANGLE_ARM_RR);
    controlArmRL(STAND_ANGLE_ARM_RL);
    controlShoulderFR(MIDDLE_ANGLE_SHOULDER_FR);
    controlShoulderFL(MIDDLE_ANGLE_SHOULDER_FL);
    controlShoulderRR(MIDDLE_ANGLE_SHOULDER_RR);
    controlShoulderRL(MIDDLE_ANGLE_SHOULDER_RL);
    delay(260);
    controlArmFR(RAISE_ANGLE_ARM_FR);
    controlArmFL(STAND_ANGLE_ARM_FL);
    controlArmRR(STAND_ANGLE_ARM_RR);
    controlArmRL(RAISE_ANGLE_ARM_RL);
    delay(265);
    controlShoulderFR(OPEN_ANGLE_SHOULDER_FR);
    controlShoulderFL(OPEN_ANGLE_SHOULDER_FL);
    controlShoulderRR(OPEN_ANGLE_SHOULDER_RR);
    controlShoulderRL(OPEN_ANGLE_SHOULDER_RL);
    delay(260);
    controlArmFR(STAND_ANGLE_ARM_FR);
    controlArmFL(STAND_ANGLE_ARM_FL);
    controlArmRR(STAND_ANGLE_ARM_RR);
    controlArmRL(STAND_ANGLE_ARM_RL);
    controlShoulderFR(OPEN_ANGLE_SHOULDER_FR);
    controlShoulderFL(OPEN_ANGLE_SHOULDER_FL);
    controlShoulderRR(OPEN_ANGLE_SHOULDER_RR);
    controlShoulderRL(OPEN_ANGLE_SHOULDER_RL);
    delay(260);
    controlArmFR(STAND_ANGLE_ARM_FR);
    controlArmFL(RAISE_ANGLE_ARM_FL);
    controlArmRR(RAISE_ANGLE_ARM_RR);
    controlArmRL(STAND_ANGLE_ARM_RL);
    delay(265);
    controlShoulderFR(MIDDLE_ANGLE_SHOULDER_FR);
    controlShoulderFL(MIDDLE_ANGLE_SHOULDER_FL);
    controlShoulderRR(MIDDLE_ANGLE_SHOULDER_RR);
    controlShoulderRL(MIDDLE_ANGLE_SHOULDER_RL);
    delay(260);
    transformstoSpider();
  }
  else
  {

  }
}

void test()
{
  controlShoulderFR(MIDDLE_ANGLE_SHOULDER_FR);
  controlShoulderFL(MIDDLE_ANGLE_SHOULDER_FL);
  controlShoulderRR(MIDDLE_ANGLE_SHOULDER_RR);
  controlShoulderRL(MIDDLE_ANGLE_SHOULDER_RL);
  controlArmFR(CLOSE_ANGLE_ARM_FR);
  controlArmRL(CLOSE_ANGLE_ARM_RL);
  controlArmFL(CLOSE_ANGLE_ARM_FL);
  controlArmRR(CLOSE_ANGLE_ARM_RR);
}
