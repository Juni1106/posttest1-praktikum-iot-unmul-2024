#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

#define LED1 16  // Pemilihan Pin D0
#define LED2 4  // Pemilihan Pin D2

const char* ssid = "Infinix NOTE 30";       // Nama SSID AP/Hotspot
const char* password = "2209106013";    // Password Wifi

ESP8266WebServer server(80); //Menyatakan Webserver pada port 80
String webpage;

void setup() {  //Pengaturan Pin
  Serial.begin(38400);
  delay(100);

  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);

  // Connect ke WiFi
  Serial.println();
  Serial.print("Configuring access point...");

  // Mengatur WiFi 
  WiFi.mode(WIFI_AP);                     // Mode AP Access point yang di tetapkan ( Wifi pribadi )
  WiFi.begin(ssid, password);            // Mencocokan SSID dan Password
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print("Connecting to WiFi..");
  }
  
  // Print status Connect 
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  digitalWrite(LED1, LOW); // LED kuning
  digitalWrite(LED2, LOW); // LED merah
  digitalWrite(LED_BUILTIN, LOW);
  
  // Isi dari Webpage 
  webpage += "<h1><center>POSTTEST 1 iOT </h1></center>";
  webpage += "<h1><center> WEB CONTROL LED ESP8266</h1></center>";
  webpage += "LED 1 : ";
  webpage += "<a href=\"LED1ON\"\"><button>ON</button></a><a href=\"LED1OFF\"\"><button>OFF</button></a></center><br>";
  webpage += "LED 2 : ";
  webpage += "<a href=\"LED2ON\"\"><button>ON</button></a><a href=\"LED2OFF\"\"><button>OFF</button></a></center><br>";

  // Membuat file webpage 
  server.on("/", []() {
    server.send(200, "text/html", webpage);
  });

  // Bagian untuk merespon perintah yang masuk 
  server.on("/LED1ON", []() {
    server.send(200, "text/html", webpage);
    digitalWrite(LED1, HIGH);
    digitalWrite(LED2, LOW);

  });
  server.on("/LED2ON", []() {
    server.send(200, "text/html", webpage);
    digitalWrite(LED2, HIGH);
    digitalWrite(LED1, LOW);
  });

  server.on("/LED1OFF", []() {
    server.send(200, "text/html", webpage);
    digitalWrite(LED1, LOW);
  });

  server.on("/LED2OFF", []() {
    server.send(200, "text/html", webpage);
    digitalWrite(LED2, LOW);
  });

  server.begin();
  Serial.println("Server starts");
}

void loop() {             //Perulangan Program
  server.handleClient();
}