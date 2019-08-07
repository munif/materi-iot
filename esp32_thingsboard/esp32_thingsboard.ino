#include <WiFi.h>
#include <HTTPClient.h>
 
const char* ssid = "S7-5695";
const char* password =  "password123";


void setup() {
  Serial.begin(115200);
  delay(4000);   //Delay needed before calling the WiFi.begin
 
  WiFi.begin(ssid, password); 
 
  while (WiFi.status() != WL_CONNECTED) { //Check for the connection
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }
 
  Serial.println("Connected to the WiFi network");
}

void loop() {
  if(WiFi.status()== WL_CONNECTED){   //Check WiFi connection status
    HTTPClient http;
    http.begin("http://demo.thingsboard.io/api/v1/GvlrxHWpL0SYfDtmtgkU/telemetry");
    
    http.addHeader("Content-Type", "application/json");

    Serial.println("Sending requests");

    // Generate random temperature
    long randNumber = random(10);
    double randTemp = randNumber * 0.5 + 25.0;
    Serial.println("Random temperature: " + String(randTemp));

    // Send POST data
    int httpResponseCode = http.POST("{\"temperature\": " + String(randTemp) + "}");   //Send the actual POST request
    
    if(httpResponseCode > 0) {
      String response = http.getString();
      Serial.println(httpResponseCode);
      Serial.println(response);
    } else {
      Serial.print("Error on sending POST: ");
      Serial.print(httpResponseCode);
    }
    
    http.end();
  }
  else
  {
      Serial.println("Error in WiFi connection");   
  }
 
  delay(3000);  //Send a request every 10 seconds

}
