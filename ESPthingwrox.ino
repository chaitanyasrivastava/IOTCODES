#include <ESP8266HTTPClient.h>
#include<Wire.h>
#define ACCEPT_TYPE "text/csv" //comma seperated value
WiFiClient client;
int relay1 = 2;
const char ssid[] = "GLA-CSED";
const char password[] = "GLACAMPUS";

 

const char appKey[]="57d2019f-5a76-45d2-a433-f399b4f6c1e5";
const char host[] = "172.16.78.20"; 
const int httpPort = 7080;

 


const char Thing[] = "ram-l-1234-thing";
const char get_Property1[] = "relay1";

 


void setup()
{
  pinMode(relay1, OUTPUT);

 

  Serial.begin(115200);  

  Serial.println();
  Serial.print("connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
   while (WiFi.status() != WL_CONNECTED)
  {
     delay(500);
     Serial.print(".");
   }
     Serial.println("");
     Serial.println("WiFi connected");
     Serial.println("IP address: ");
     Serial.println(WiFi.localIP());
      delay(100);


 

}

 

void loop()
{


  String res1 = Get(Thing,get_Property1); 


 

  Serial.println(res1);
  Serial.println(res1[11]);

  if(res1[11]=='f')
  {
    digitalWrite(relay1,HIGH);
    Serial.println("relayoff");
  }
  else if(res1[11]=='t'){
    digitalWrite(relay1,LOW);
    Serial.println("relayon");
  }

}
    String Get(String get_Thing, String get_Property1)
{              
        HTTPClient http;
        int httpCode = -1;
        String fullRequestURL = "http://" + String(host) +":"+ String(httpPort)+ "/Thingworx/Things/" 
                                + Thing + "/Properties/" + get_Property1 + "?appKey=" + appKey;

        Serial.println(fullRequestURL);
        http.begin(client, fullRequestURL);
        http.addHeader("Accept",ACCEPT_TYPE,false,false);        
        httpCode = http.GET();
        Serial.println(httpCode);

        String responses;
        if(httpCode > 0)        
        {             
           responses= http.getString(); 
             //Serial.println(responses);      
             //Serial.print(responses[9]);        
        }
        else         
        {
            Serial.printf("[httpGetPropertry] failed, error: %s\n\n", http.errorToString(httpCode).c_str());
        }
        http.end();
        return responses;        
}
