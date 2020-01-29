#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>

const char* ssid = "*"; // 사용할 wifi ssid (수정)
const char* password = "*"; // 사용할 wifi password (수정)

const char* host = "maker.ifttt.com"; // 요청할 host name
const int httpsPort = 80; // 요청할 port

int SensorPin = A0; // sensor a0
int count = 0;
const int buzzerPin= 2;

void setup() {
  Serial.begin(115200); // 상태 모니터링용 시리얼 포트
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  pinMode(buzzerPin,OUTPUT);
}

void loop() {
  WiFiClient client;
  digitalWrite(buzzerPin, HIGH);
  int SensorReading = analogRead(SensorPin); //센서 값
  Serial.print("pressure : ");
  Serial.println(SensorReading);
  if(SensorReading > 9)
  {
  }
  else
  {
    if(count < 10){
      count = count + 1;
      Serial.print("count : ");
      Serial.println(count);
      digitalWrite(buzzerPin, LOW);
    }
    else
    {
      count = 0;
      Serial.print("Connecting to ");
      Serial.println(host);
      if (!client.connect(host, httpsPort)) {
        Serial.println("Connection failed");
        return;
    }
      String url = "*"; // 요청할 주소
      Serial.print("requesting URL: ");
      Serial.println(url);
      client.print(String("GET ") + url + " HTTP/1.1\r\n" +
                "Host: " + host + "\r\n" +
                "Connection: close\r\n\r\n");
      Serial.println("request sent");
      while (client.connected()) {
        String line = client.readStringUntil('\n');
        if (line == "\r") {
          Serial.println("Headers received");
          break;
        }
      }
      String line = client.readStringUntil('\n');
      Serial.println("reply was:");
      Serial.println("==========");
      Serial.println(line);
      Serial.println("==========");
      Serial.println("closing connection"); 
    }
  }
  delay(1000);
}
