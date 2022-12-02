#include <ArduinoJson.h>
#include "WiFi.h"
#include <HTTPClient.h>
#include <iostream>
#include <string>
using namespace std;
const char *ssid = "Esp32-teste";
const char * pass = "10224455";
const char *equipamento = "notebook"; 
const char *patrimonio = "209802";
String predio = "";
String local ="";
void postDataToServer() {
  Serial.println("Posting JSON data to server...");
  // Block until we are able to connect to the WiFi access point
  HTTPClient http;
    http.begin("https://euot7j-3001.preview.csb.app/dispositivos/create");
    http.addHeader("Content-Type", "application/json");
    StaticJsonDocument<1024> doc;
    // Add values in the document
    //
    doc["nome"] = equipamento;
    doc["predio"] = predio;
    doc["codigo_patrimonio"] = patrimonio;
    doc["sala"] = local;
    
    // Add an array.
    //
//    JsonArray data = doc.createNestedArray("data");
//    for(int i=0; i<3; i++)
//    {
//      data.add(distancia[i]);
//    }
    String requestBody;
    serializeJson(doc, requestBody);
    int httpResponseCode = http.POST(requestBody);
    if(httpResponseCode>0){
      String response = http.getString();
      Serial.println(httpResponseCode);
      Serial.println(response);
    }
    else {
      //Serial.println("Error occurred while sending HTTP POST: %s\n", httpClient.errorToString(statusCode).c_str());
    }
}
void getDataToServer() {
  Serial.println("getting JSON data from server...");
  // Block until we are able to connect to the WiFi access point
  HTTPClient http;
  http.begin("https://euot7j-3001.preview.csb.app/dispositivos/");
  http.addHeader("Content-Type", "application/json");
  int httpCode = http.GET();  //send request
  String dataJSON = http.getString(); //get the response payload from server
  Serial.print("Response Code:"); //200 is OK
  Serial.println(httpCode);   //Print HTTP return code
  Serial.print("Returned data from Server:");
  Serial.println(dataJSON);    //Print request response payload
  if(httpCode == 200)
  {
    //create json object
    // Allocate JsonBuffer
    // Use arduinojson.org/assistant to compute the capacity.
    StaticJsonDocument<1024> doc;
    // Parse JSON object
    DeserializationError error = deserializeJson(doc, dataJSON);
    if (error) {
        Serial.print(F("deserializeJson() failed with code "));
        Serial.println(error.c_str());
        return;
    }
    // Decode JSON/Extract values
    Serial.println(F("Response:"));
    }
    else
    {
      Serial.println("Error in response");
    }
    http.end();  //Close connection
    delay(5000);  //GET Data at every 5 seconds
}
void setup()
{
  Serial.begin(115200);

    // Set WiFi to station mode and disconnect from an AP if it was previously connected
  WiFi.mode(WIFI_STA);
  // WiFi.disconnect();
  WiFi.begin(ssid,pass);
  delay(1000);

  Serial.println("Setup done");
}

void loop()
{
  Serial.println("scan start");
    
    // WiFi.scanNetworks will return the number of networks found
  int n = WiFi.scanNetworks();
  String stringOne = WiFi.SSID();
  Serial.println("scan done");
  if (n == 0) {
    Serial.println("no networks found");
  } else {
      Serial.print(n);
      Serial.println(" networks found");

      for (int i = 0; stringOne.startsWith("Finders") != true; ++i) {
        if (stringOne.startsWith("Finders") == true){
            // Print SSID and RSSI for each network found
              
          // local = WiFi.SSID(0);
          // predio = WiFi.SSID(0);
          // predio.remove(0,8);
          // predio.remove(3);
          // local.remove(0,12);
          Serial.println(predio);
          Serial.println(local);
          Serial.println(equipamento);
          Serial.println(patrimonio);
          // postDataToServer();
          getDataToServer();
        }else{
          Serial.println("erro");
        }
        delay(5000);
        break;
      }
    }
    
    // Wait a bit before scanning again
    delay(5000);
    const int deep_sleep_sec = 60;
    ESP_LOGI(TAG, "Entering deep sleep for %d seconds", deep_sleep_sec);
    esp_deep_sleep(1000000LL * deep_sleep_sec);
}
