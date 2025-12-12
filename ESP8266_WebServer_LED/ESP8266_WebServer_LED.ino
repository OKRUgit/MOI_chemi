#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

// === НАСТРОЙКИ ПОДКЛЮЧЕНИЯ К Wi-Fi ===
const char* ssid = "OK_YVS";      // ← Замените на имя вашей сети
const char* password = "OKRUgit"; // ← Замените на пароль

// === НАСТРОЙКА ПИНА СВЕТОДИОДА ===
const int ledPin = D4;  // Встроенный светодиод на NodeMCU (GPIO2)
                        // Можно поменять на D0, D1... при подключении внешнего LED

// === ВЕБ-СЕРВЕР ===
ESP8266WebServer server(80);

// === HTML СТРАНИЦА (встроена в код) ===
String htmlPage = R"html(
<!DOCTYPE html>
<html>
<head>
  <title>ESP8266 Управление Светодиодом</title>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <style>
    body { font-family: Arial; text-align: center; margin: 30px; background: #f4f4f4; }
    h1 { color: #333; }
    .status { font-size: 20px; margin: 20px; }
    .button { 
      padding: 15px 30px; 
      margin: 10px; 
      font-size: 18px; 
      border: none; 
      border-radius: 8px; 
      cursor: pointer; 
    }
    .on  { background: #4CAF50; color: white; }
    .off { background: #f44336; color: white; }
    .toggle { background: #2196F3; color: white; }
    .footer { margin-top: 30px; color: #888; font-size: 14px; }
  </style>
</head>
<body>
  <h1>🌐 ESP8266 Веб-Сервер</h1>
  <p class="status">Светодиод: <strong>)html" + String((digitalRead(ledPin) == HIGH) ? "ВКЛ" : "ВЫКЛ") + R"html(</strong></p>

  <a href="/on"><button class="button on">ВКЛЮЧИТЬ</button></a>
  <a href="/off"><button class="button off">ВЫКЛЮЧИТЬ</button></a>
  <a href="/toggle"><button class="button toggle">ПЕРЕКЛЮЧИТЬ</button></a>

  <div class="footer">
    <p>IP: )html" + WiFi.localIP().toString() + R"html(</p>
    <p>Проект: ESP8266 как автономный сервер</p>
  </div>
</body>
</html>
)html";

// === ОБРАБОТЧИКИ ЗАПРОСОВ ===
void handleRoot() {
  // Обновляем HTML при каждом запросе
  String updatedHtml = htmlPage;
  updatedHtml.replace("ВКЛ", (digitalRead(ledPin) == HIGH) ? "ВКЛ" : "ВЫКЛ");
  updatedHtml.replace("ВЫКЛ", (digitalRead(ledPin) == HIGH) ? "ВКЛ" : "ВЫКЛ");
  updatedHtml.replace("IP: ", "IP: " + WiFi.localIP().toString());

  server.send(200, "text/html", updatedHtml);
}

void handleOn() {
  digitalWrite(ledPin, HIGH);
  server.sendHeader("Location", "/");
  server.send(303); // Перенаправление
}

void handleOff() {
  digitalWrite(ledPin, LOW);
  server.sendHeader("Location", "/");
  server.send(303);
}

void handleToggle() {
  digitalWrite(ledPin, !digitalRead(ledPin));
  server.sendHeader("Location", "/");
  server.send(303);
}

// === ИНИЦИАЛИЗАЦИЯ ===
void setup() {
  // Настройка пина светодиода
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);

  // Запуск последовательного порта
  Serial.begin(115200);
  Serial.println("\n\nЗапуск ESP8266...");

  // Подключение к Wi-Fi
  WiFi.begin(ssid, password);
  Serial.print("Подключение к ");
  Serial.println(ssid);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nПодключено к Wi-Fi");
  Serial.print("IP-адрес: ");
  Serial.println(WiFi.localIP());

  // Настройка маршрутов
  server.on("/", HTTP_GET, handleRoot);
  server.on("/on", HTTP_GET, handleOn);
  server.on("/off", HTTP_GET, handleOff);
  server.on("/toggle", HTTP_GET, handleToggle);

  // Запуск сервера
  server.begin();
  Serial.println("✅ HTTP-сервер запущен на порту 80");
}

// === ОСНОВНОЙ ЦИКЛ ===
void loop() {
  server.handleClient(); // Обработка входящих запросов
}