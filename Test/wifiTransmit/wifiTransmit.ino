#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebSrv.h>

const char* ssid = "TransformRobo";
const char* password = "internet";

AsyncWebServer server(80);

String receivedData;

void setup() {
  Serial.begin(115200);
  delay(1000);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  // Route to serve the HTML form
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(200, "text/html", "<html><body><h1>Enter Commands:</h1><form action='/' method='post'><input type='text' name='data'><input type='submit' value='Send'></form></body></html>");
  });

  // Route to handle incoming POST requests
  server.on("/", HTTP_POST, [](AsyncWebServerRequest *request){
    receivedData = request->arg("data"); // Get the "data" parameter from the POST request
    // Serial.print("Received data: ");
    // Serial.println(receivedData);
    // request->send(200); // Respond with an HTTP 200 OK status
    request->send(200, "text/html", "<html><body><h1>Enter Commands:</h1><form action='/' method='post'><input type='text' name='data'><input type='submit' value='Send'></form></body></html>");
  });

  // Start the server
  server.begin();
}

void loop() {
  // Your code here (if needed)
  if(receivedData.length()!=0)
  {
    Serial.print("Received data: ");
    Serial.println(receivedData);
    receivedData = "";
  }
  else
  {
    Serial.println("Waiting...");
  }
  delay(1000);
}
