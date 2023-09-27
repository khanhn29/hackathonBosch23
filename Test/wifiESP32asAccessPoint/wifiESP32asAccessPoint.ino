/*********
  Rui Santos
  Complete project details at https://randomnerdtutorials.com  
*********/

// Load Wi-Fi library
#include <WiFi.h>

// Replace with your network credentials
const char* ssid = "ESP32_AP";       // SSID (name) of the ESP32's access point
const char* password = "password123"; // Password for the access point

// Set web server port number to 80
WiFiServer server(80);

// Variable to store the HTTP request
String header;

const char* htmlForm = "<html>\
<head>\
<style>\
table, th, td {\
  border:1px solid black;\
}\
</style>\
</head>\
<body>\
<h1>Enter Commands:</h1>\
<form action='/' method='post'>\
    <input type='text' name='data'>\
    <input type='submit' value='Send'><br/>\
    <table style=\"width:50%\">\
        <tr>\
          <td>Q: Transform to Car</td>\
          <td>W: Move Forward</td>\
          <td>E: Transform to Spider</td>\
        </tr>\
        <tr>\
          <td>A: Turn left</td>\
          <td>S: Move Backward</td>\
          <td>D: Turn Right</td>\
        </tr>\
        <tr>\
          <td></td>\
          <td>O: Stop for 1 second</td>\
          <td></td>\
        </tr>\
      </table>\
</form>\
</body>\
</html>";

String receivedString = ""; // Store the received string data

void setup() {
  Serial.begin(115200);

  // Set a fixed IP address for the access point
  IPAddress localIP(192, 168, 4, 1);
  IPAddress gateway(192, 168, 4, 1);
  IPAddress subnet(255, 255, 255, 0);

  Serial.print("Setting AP (Access Point) with fixed IP address...");
  WiFi.softAPConfig(localIP, gateway, subnet);
  WiFi.softAP(ssid, password);

  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);

  server.begin();
}

void loop() {
  WiFiClient client = server.available();   // Listen for incoming clients

  if (client) {                             // If a new client connects,
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
            client.println(htmlForm);

            // The HTTP response ends with another blank line
            client.println();
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
}
