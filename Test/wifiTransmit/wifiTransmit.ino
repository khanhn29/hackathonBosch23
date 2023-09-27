#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebSrv.h>

const char* ssid = "TransformRobo";
const char* password = "internet";

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

String htmlFormPart1 = "<html>\
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
      <p>Last command: ";
String htmlFormPart2 = "<p/></form>\
</body>\
</html>";

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
}

void loop() {
  // Your code here (if needed)
  if(WiFi.status() != WL_CONNECTED) {
    // delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  else
  {
      // Route to serve the HTML form
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
      request->send(200, "text/html", htmlForm);
    });

    // Route to handle incoming POST requests
    server.on("/", HTTP_POST, [](AsyncWebServerRequest *request){
      receivedData = request->arg("data"); // Get the "data" parameter from the POST request
      // Serial.print("Received data: ");
      // Serial.println(receivedData);
      // request->send(200); // Respond with an HTTP 200 OK status
      request->send(200, "text/html", htmlFormPart1 + receivedData + htmlFormPart2);
    });

    // Start the server
    server.begin();
    // Serial.println("Connected to WiFi");
    if(receivedData.length()!=0)
    {
      Serial.print("Received data: ");
      Serial.println(receivedData);
      receivedData = "";
    }
    else
    {
      // Serial.println("Waiting...");
    }
  }
  delay(1000);
}

