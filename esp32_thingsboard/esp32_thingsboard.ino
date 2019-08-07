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
      
      // Format: http://demo.thingsboard.io/api/v1/$ACCESSTOKEN/telemetry
      // Ganti $ACCESSTOKEN dengan token device yang ingin dikirimi telemetry
      http.begin("http://demo.thingsboard.io/api/v1/GvlrxHWpL0SYfDtmtgkU/telemetry");  //Specify destination for HTTP request
      http.addHeader("Content-Type", "application/json");             //Specify content-type header

      // Generate random temperature
      long randNumber = random(10);
      double randTemp = randNumber * 0.5 + 25.0;
      Serial.println("Random temperature: " + String(randTemp));

      // Send POST data
      int httpResponseCode = http.POST("{\"temperature\": " + String(randTemp) + "}");   //Send the actual POST request
 
      if(httpResponseCode>0){
          String response = http.getString();                       //Get the response to the request
          Serial.println(httpResponseCode);   //Print return code
          Serial.println(response);           //Print request answer
      }
      else
      {
          Serial.print("Error on sending POST: ");
          Serial.println(httpResponseCode);
      }
 
      http.end();  //Free resources
 
  }
  else
  {
 
      Serial.println("Error in WiFi connection");   
 
  }
 
  delay(10000);  //Send a request every 10 seconds

}
