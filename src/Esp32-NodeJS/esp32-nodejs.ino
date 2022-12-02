#include <ArduinoJson.h>
#include <HTTPClient.h>
#include <WiFi.h>

#define led 18

//Inteli-COLLEGE  --  QazWsx@123

//Vetores com nomes de rede e senhas dos Access Points
const char* SSIDS[4]={"Redmi 9","Inteli-COLLEGE","baconzitos2","baconzitos3"};
const char* PWD[4]={"12345678","QazWsx@123","baconzitos2","baconzitos3"};
//Variável que continua ou não o MENU 2
int parar=0;
int indice=0;
// Definições para o FTM

int ledStatus = 0;

void postDataToServer() {
 
  Serial.println("Posting JSON data to server...");
  // Block until we are able to connect to the WiFi access point
  HTTPClient http;   
     
    http.begin("https://zudbt6-3081.preview.csb.app/led1");  
    http.addHeader("Content-Type", "application/json");         
     
    StaticJsonDocument<200> doc;
    // Add values in the document
    //
    doc["Nome"] = "IPT-001";
    doc["MAC"] = WiFi.macAddress();
    doc["Data"] = "01/02/2022";
    doc["Hora"] = "18:55:48";
    doc["Em Campo?"] = "NÃO";
    doc["Prédio"] = "P-08";
    doc["Sala"] = "S-15";
    
   
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
     
      //Serial.printf("Error occurred while sending HTTP POST: %s\n", httpClient.errorToString(statusCode).c_str());
       
    }
     
}

void getDataToServer() {
 
  Serial.println("getting JSON data from server...");
  // Block until we are able to connect to the WiFi access point
  HTTPClient http;   
     
  http.begin("https://zudbt6-3081.preview.csb.app/led1");  
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
    StaticJsonDocument<256> doc;

    // Parse JSON object
    DeserializationError error = deserializeJson(doc, dataJSON);
    if (error) {
        Serial.print(F("deserializeJson() failed with code "));
        Serial.println(error.c_str());
        return;
    }

    ledStatus = doc["ledStatus"];
    
    // Decode JSON/Extract values
    Serial.println(F("Response:"));
    Serial.println(ledStatus);
    }
    else
    {
      Serial.println("Error in response");
    }
  
    http.end();  //Close connection
    
    delay(5000);  //GET Data at every 5 seconds
     
}

//Uma função para ler todos os dados da conexão WiFi
void DadosConexao(){
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.println("Subnet Mask: ");
  Serial.println(WiFi.subnetMask());
  Serial.println("Gateway IP: ");
  Serial.println(WiFi.gatewayIP());
  Serial.println("DNS IP: ");
  Serial.println(WiFi.dnsIP());
  Serial.println("BroadCast: ");
  Serial.println(WiFi.broadcastIP());
  Serial.println("MAC address: ");
  Serial.println(WiFi.macAddress());
  Serial.println("Network ID: ");
  Serial.println(WiFi.networkID());
  Serial.println("PSK: ");
  Serial.println(WiFi.psk());
  Serial.println("BSSID: ");
  Serial.println(WiFi.BSSIDstr());
  Serial.println("RSSI: ");
  Serial.println(WiFi.RSSI());
}

//Função para um Menu de escolha cujo intuito é mostrar todas as possibilidades do Wifi.
//Conectar separadamente nos APs e depois fazer a triangulação
int menu()
{
  Serial.println(F("\nEscolha uma opção:"));
  Serial.println(F("0 - Scan de redes"));
  Serial.println(F("1 - Conectar no WIFI e receber dados via JSON \n"));
  Serial.println(F("2 - Conectar no WIFI e enviar dados para o servidor.  \n"));
  //fica aguardando enquanto o usuário nao enviar algum dado
  while(!Serial.available()){};
  //recupera a opção escolhida
  int op = (int)Serial.read();
  //remove os proximos dados (como o 'enter ou \n' por exemplo) que vão por acidente
  while(Serial.available()) {
    if(Serial.read() == '\n') break; 
    Serial.read();
  }
  return (op-48);//do valor lido, subtraimos o 48 que é o ZERO da tabela ascii
}
//Utilizado na função CONECTAR, para continuar mostrando os dados da conexão enquanto permanecer
//conectado. 
int menu2()
{
  Serial.println(F("\nEscolha uma opção 2:"));
  //fica aguardando enquanto o usuário nao enviar algum dado
  while(!Serial.available()){};
  //recupera a opção escolhida
  int op = (int)Serial.read();
  //remove os proximos dados (como o 'enter ou \n' por exemplo) que vão por acidente
  while(Serial.available()) {
    if(Serial.read() == '\n') break; 
    Serial.read();
  }
  return (op-48);//do valor lido, subtraimos o 48 que é o ZERO da tabela ascii
}
//Função para conectar em APs sem medição FTM
void Conectar(int rede, int cmd)
{
  Serial.println("Conectando na rede: ");
  Serial.println(rede);
  WiFi.begin(SSIDS[rede],PWD[rede]);

  if (cmd == 0){
      while (WiFi.status() != WL_CONNECTED) {
        Serial.print("Tentando novamente!");
        delay(500);
      }
      while(parar==0)
      {
        Serial.println("WiFi connected");
        //DadosConexao();
        postDataToServer();      
        parar = menu2();
      }
      parar=0;
      WiFi.disconnect();
      Serial.println("Desconectei!");
  }else if(cmd == 1){
    while (WiFi.status() != WL_CONNECTED) {
        Serial.print("Tentando novamente!");
        delay(500);
      }
      while(parar==0)
      {
        Serial.println("WiFi connected");
        //DadosConexao();
        getDataToServer();      
        parar = menu2();
      }
      parar=0;
      WiFi.disconnect();
      Serial.println("Desconectei!");
    }
  
}

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA); 
  pinMode(led,OUTPUT);
}

void loop() {
  digitalWrite(led,ledStatus);
  int opcao = menu();
  switch(opcao)
  {
    case 0:
    {
      Serial.println("Escaneando redes!");
      int n = WiFi.scanNetworks();
      Serial.println("scan done");
      if (n == 0) {
          Serial.println("no networks found");
      } 
      else {
        Serial.print(n);
        Serial.println(" networks found");
        for (int i = 0; i < n; ++i) {
          // Print SSID and RSSI for each network found
          Serial.print(i + 1);
          Serial.print(": ");
          Serial.print(WiFi.SSID(i));
          Serial.print(" (");
          Serial.print(WiFi.RSSI(i));
          Serial.print(")");
          Serial.println((WiFi.encryptionType(i) == WIFI_AUTH_OPEN)?" ":"*");
          delay(10);
        }
      }
      break;
    }
    case 1:
      Serial.println("Conectar a internet e receber dados via JSON!");
      //rede = 0; cmd = 1 = get
      Conectar(0,1);
      break;
    case 2:
      Serial.println("Conectar na internet e enviar dados para o servidor!");
      //rede = 0; cmd = 0 = Post
      Conectar(0,0);
      break;
    default:
      Serial.println("Opção fora do padrão!");
      break;
  }
}
