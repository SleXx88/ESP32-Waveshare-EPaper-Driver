#include <WiFi.h>
#include <WiFiClient.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>

#include <esp_wifi.h>
#include <esp_sleep.h>
#include "driver/adc.h"
#include <esp_bt.h>

#include <pgmspace.h>

#include "icons_16px.h"
#include "icons_24px.h"
#include "icons_bat_24px.h"
#include "icons_weather.h"
#include "icons_weather_64px.h"

// EPaper Pinout
#define PIN_BUSY  4
#define PIN_RST   16
#define PIN_DC    17
#define PIN_CS    5
#define PIN_CLK   18
#define PIN_DIN   23

// ESP32
#define PIN_DIO0          0
#define ADC_BAT_ON_PIN    33
#define ADC_BAT_PIN       32
#define ADC_5V_PIN        34

//#define DEBUG                 // define for Serial Debug

#ifdef  DEBUG
#define DEBUG_PRINT(x)    Serial.print(x)
#define DEBUG_PRINTLN(x)  Serial.println(x)
#else
#define DEBUG_PRINT(x)
#define DEBUG_PRINTLN(x)
#endif

#define REFRESH_EPAPER        // comment out to not update the epaper -> for DEBUG purposes
#define DeepSleep             // define for deep sleep

#ifdef  REFRESH_EPAPER
  int time_to_sleep =     60 * 15;  // DeepSleep in Seconds -> default = 60s * 15s = 15min
#else
  int time_to_sleep =     120;      // DeepSleep in Seconds
#endif

#define LifeSign          3000      // in milliseconds

const char* ssid          = "";        // Set your WiFi SSID
const char* password      = "";        // Set your WiFi password

const char* mqtt_server   = "192.168.1.10";     // Set your MQTT Server IP adress
const char* mqttClientID  = "";                 // Set your MQTT Client ID
const char* mqttUser      = "";                 // Set your MQTT Username
const char* mqttPW        = "";                 // Set your MQTT password

IPAddress local_IP(192, 168, 1, 13);    // Set your Static IP address
IPAddress gateway(192, 168, 1, 1);      // Set your Gateway IP address

IPAddress subnet(255, 255, 255, 0);     // Set your subnet mask
IPAddress primaryDNS(8, 8, 8, 8);       // optional
IPAddress secondaryDNS(8, 8, 4, 4);     // optional


WiFiClient espClient;
PubSubClient client(espClient);
unsigned long lastMsg         = 0;
unsigned long counting        = 0;
#define MSG_BUFFER_SIZE       4096      // Buffersize for MQTT MSG

String  NetworkIP;

const char* currentTime;

const char* weather_temp;
const char* weather_hum;
const char* weather_wind;
const char* weather_uv;
const char* weather_sunrise;
const char* weather_sunset;
const char* weather_icon;
const char* weather_desc;

const char* day1_time;
float day1_tempMin;
float day1_tempMax;
const char* day1_icon;

const char* day2_time;
float day2_tempMin;
float day2_tempMax;
const char* day2_icon;

const char* day3_time;
float day3_tempMin;
float day3_tempMax;
const char* day3_icon;

// Area 0
const char*  Area0Line0desc;
int8_t       Area0Line0Icon0;
const char*  Area0Line0Text0;
int8_t       Area0Line0Icon1;
const char*  Area0Line0Text1;
int8_t       Area0Line0Icon2;
const char*  Area0Line0Text2;
int8_t       Area0Line0color;

const char*  Area0Line1desc;
int8_t       Area0Line1Icon0;
const char*  Area0Line1Text0;
int8_t       Area0Line1Icon1;
const char*  Area0Line1Text1;
int8_t       Area0Line1Icon2;
const char*  Area0Line1Text2;
int8_t       Area0Line1color;

const char*  Area0Line2desc;
int8_t       Area0Line2Icon0;
const char*  Area0Line2Text0;
int8_t       Area0Line2Icon1;
const char*  Area0Line2Text1;
int8_t       Area0Line2Icon2;
const char*  Area0Line2Text2;
int8_t       Area0Line2color;

const char*  Area0Line3desc;
int8_t       Area0Line3Icon0;
const char*  Area0Line3Text0;
int8_t       Area0Line3Icon1;
const char*  Area0Line3Text1;
int8_t       Area0Line3Icon2;
const char*  Area0Line3Text2;
int8_t       Area0Line3color;

// Area 1
int8_t       Area1Line0Icon0;
const char*  Area1Line0Text0;
int8_t       Area1Line0Icon1;
const char*  Area1Line0Text1;
int8_t       Area1Line0color;
int8_t       Area1Line1Icon0;
const char*  Area1Line1Text0;
int8_t       Area1Line1Icon1;
const char*  Area1Line1Text1;
int8_t       Area1Line1color;
int8_t       Area1Line2Icon0;
const char*  Area1Line2Text0;
int8_t       Area1Line2Icon1;
const char*  Area1Line2Text1;
int8_t       Area1Line2color;
int8_t       Area1Line3Icon0;
const char*  Area1Line3Text0;
int8_t       Area1Line3Icon1;
const char*  Area1Line3Text1;
int8_t       Area1Line3color;

// Area 2
int8_t       Area2Icon0;
const char*  Area2Text0;
int8_t       Area2Icon1;
const char*  Area2Text1;
int8_t       Area2Text1color;
// Area 3
int8_t       Area3Icon0;
const char*  Area3Text0;
const char*  Area3Text1;
int8_t       Area3Icon1;
const char*  Area3Text2;
const char*  Area3Text3;
// Area 4
int8_t       Area4Icon0;
const char*  Area4Text0;
int8_t       Area4Icon1;
const char*  Area4Text1;
int8_t       Area4Icon2;
const char*  Area4Text2;
int8_t       Area4Icon3;
const char*  Area4Text3;

const char*  cal1_titel;
const char*  cal1_start;
const char*  cal1_end;

const char*  cal2_titel;
const char*  cal2_start;
const char*  cal2_end;

const char*  cal3_titel;
const char*  cal3_start;
const char*  cal3_end;

const char*  cal4_titel;
const char*  cal4_start;
const char*  cal4_end;

const char*  cal5_titel;
const char*  cal5_start;
const char*  cal5_end;

const char*   em3day[7];
float         em3e[7];
const char*   em3total;
int           em3emax;

const char*   watertotal;

// Battery
float         VCC_USB = 0;
float         VCC_BAT = 0;
bool          USB_POWER = true;
// RSSI
int16_t       RSSIValue;

int           countCallback = 0;

void setModemSleep();
void wakeModemSleep();

void setup_wifi() 
{
  delay(10);
  // We start by connecting to a WiFi network

  DEBUG_PRINTLN();
  DEBUG_PRINT("Connecting to ");
  DEBUG_PRINTLN(ssid);


  // Configures static IP address
  if (!WiFi.config(local_IP, gateway, subnet, primaryDNS, secondaryDNS)) {
    DEBUG_PRINTLN("STA Failed to configure");
  }

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    DEBUG_PRINT(".");
  }

  DEBUG_PRINTLN("");
  DEBUG_PRINTLN("WiFi connected");
  DEBUG_PRINTLN("IP address: ");
  DEBUG_PRINTLN(WiFi.localIP());

  char buff[16];
  sprintf(buff, "%d.%d.%d.%d", WiFi.localIP()[0], WiFi.localIP()[1], WiFi.localIP()[2], WiFi.localIP()[3]);
  NetworkIP = buff;
  
  DEBUG_PRINTLN(NetworkIP);
}

void callback(char* topic, byte* payload, unsigned int length) 
{
  // READ ADC VOLTAGE
  #ifndef  DeepSleep
    readVoltage();
  #endif


  #ifdef  DeepSleep
    setModemSleep();
  #endif
  
  #ifdef  DEBUG
    Serial.begin(115200);
  #endif

  // char str[length + 1];
  // int i = 0;
  // for (i = 0; i < length; i++) {
  //   DEBUG_PRINT((char)payload[i]);
  //   str[i] = (char)payload[i];
  // }
  // str[i] = 0;  // Null termination

  const size_t capacity = MSG_BUFFER_SIZE;
  DynamicJsonDocument doc(capacity);

  deserializeJson(doc, payload);

  currentTime       = doc["time"]["current"];

  // Current Weather
  weather_temp      = doc["weather"]["temp"];
  weather_hum       = doc["weather"]["hum"];
  weather_wind      = doc["weather"]["wind"];
  weather_uv        = doc["weather"]["uv"];
  weather_sunrise   = doc["weather"]["sunrise"];
  weather_sunset    = doc["weather"]["sunset"];
  weather_icon      = doc["weather"]["icon"];
  weather_desc      = doc["weather"]["desc"];

  // Daily Weather 1
  day1_time         = doc["weather"]["daily"]["0"]["date"];
  day1_tempMin      = doc["weather"]["daily"]["0"]["tempMin"];
  day1_tempMax      = doc["weather"]["daily"]["0"]["tempMax"];
  day1_icon         = doc["weather"]["daily"]["0"]["icon"];

  day2_time         = doc["weather"]["daily"]["1"]["date"];
  day2_tempMin      = doc["weather"]["daily"]["1"]["tempMin"];
  day2_tempMax      = doc["weather"]["daily"]["1"]["tempMax"];
  day2_icon         = doc["weather"]["daily"]["1"]["icon"];

  day3_time         = doc["weather"]["daily"]["2"]["date"];
  day3_tempMin      = doc["weather"]["daily"]["2"]["tempMin"];
  day3_tempMax      = doc["weather"]["daily"]["2"]["tempMax"];
  day3_icon         = doc["weather"]["daily"]["2"]["icon"];

  // Area 0
  Area0Line0desc    = doc["area0"]["0"]["desc"];
  Area0Line0Icon0   = doc["area0"]["0"]["icon0"];
  Area0Line0Text0   = doc["area0"]["0"]["text0"];
  Area0Line0Icon1   = doc["area0"]["0"]["icon1"];
  Area0Line0Text1   = doc["area0"]["0"]["text1"];
  Area0Line0Icon2   = doc["area0"]["0"]["icon2"];
  Area0Line0Text2   = doc["area0"]["0"]["text2"];
  Area0Line0color   = doc["area0"]["0"]["color"];

  Area0Line1desc    = doc["area0"]["1"]["desc"];
  Area0Line1Icon0   = doc["area0"]["1"]["icon0"];
  Area0Line1Text0   = doc["area0"]["1"]["text0"];
  Area0Line1Icon1   = doc["area0"]["1"]["icon1"];
  Area0Line1Text1   = doc["area0"]["1"]["text1"];
  Area0Line1Icon2   = doc["area0"]["1"]["icon2"];
  Area0Line1Text2   = doc["area0"]["1"]["text2"];
  Area0Line1color   = doc["area0"]["1"]["color"];

  Area0Line2desc    = doc["area0"]["2"]["desc"];
  Area0Line2Icon0   = doc["area0"]["2"]["icon0"];
  Area0Line2Text0   = doc["area0"]["2"]["text0"];
  Area0Line2Icon1   = doc["area0"]["2"]["icon1"];
  Area0Line2Text1   = doc["area0"]["2"]["text1"];
  Area0Line2Icon2   = doc["area0"]["2"]["icon2"];
  Area0Line2Text2   = doc["area0"]["2"]["text2"];
  Area0Line2color   = doc["area0"]["2"]["color"];

  Area0Line3desc    = doc["area0"]["3"]["desc"];
  Area0Line3Icon0   = doc["area0"]["3"]["icon0"];
  Area0Line3Text0   = doc["area0"]["3"]["text0"];
  Area0Line3Icon1   = doc["area0"]["3"]["icon1"];
  Area0Line3Text1   = doc["area0"]["3"]["text1"];
  Area0Line3Icon2   = doc["area0"]["3"]["icon2"];
  Area0Line3Text2   = doc["area0"]["3"]["text2"];
  Area0Line3color   = doc["area0"]["3"]["color"];

  // Area 1
  Area1Line0Icon0   = doc["area1"]["0"]["icon0"];
  Area1Line0Text0   = doc["area1"]["0"]["text0"];
  Area1Line0Icon1   = doc["area1"]["0"]["icon1"];
  Area1Line0Text1   = doc["area1"]["0"]["text1"];
  Area1Line0color   = doc["area1"]["0"]["color"];

  Area1Line1Icon0   = doc["area1"]["1"]["icon0"];
  Area1Line1Text0   = doc["area1"]["1"]["text0"];
  Area1Line1Icon1   = doc["area1"]["1"]["icon1"];
  Area1Line1Text1   = doc["area1"]["1"]["text1"];
  Area1Line1color   = doc["area1"]["1"]["color"];

  Area1Line2Icon0   = doc["area1"]["2"]["icon0"];
  Area1Line2Text0   = doc["area1"]["2"]["text0"];
  Area1Line2Icon1   = doc["area1"]["2"]["icon1"];
  Area1Line2Text1   = doc["area1"]["2"]["text1"];
  Area1Line2color   = doc["area1"]["2"]["color"];

  Area1Line3Icon0   = doc["area1"]["3"]["icon0"];
  Area1Line3Text0   = doc["area1"]["3"]["text0"];
  Area1Line3Icon1   = doc["area1"]["3"]["icon1"];
  Area1Line3Text1   = doc["area1"]["3"]["text1"];
  Area1Line3color   = doc["area1"]["3"]["color"];

  // Area 2
  Area2Icon0        = doc["area2"]["0"]["icon"];
  Area2Text0        = doc["area2"]["0"]["text"];
  Area2Icon1        = doc["area2"]["1"]["icon"];
  Area2Text1        = doc["area2"]["1"]["text"];
  Area2Text1color   = doc["area2"]["1"]["color"];

  // Area 3
  Area3Icon0        = doc["area3"]["0"]["icon"];
  Area3Text0        = doc["area3"]["0"]["text0"];
  Area3Text1        = doc["area3"]["0"]["text1"];
  Area3Icon1        = doc["area3"]["1"]["icon"];
  Area3Text2        = doc["area3"]["1"]["text0"];
  Area3Text3        = doc["area3"]["1"]["text1"];

  // Area 4
  Area4Icon0        = doc["area4"]["0"]["icon"];
  Area4Text0        = doc["area4"]["0"]["text"];
  Area4Icon1        = doc["area4"]["1"]["icon"];
  Area4Text1        = doc["area4"]["1"]["text"];
  Area4Icon2        = doc["area4"]["2"]["icon"];
  Area4Text2        = doc["area4"]["2"]["text"];
  Area4Icon3        = doc["area4"]["3"]["icon"];
  Area4Text3        = doc["area4"]["3"]["text"];

  // Energy
  em3day[0]         = doc["em3"]["d1"];
  em3e[0]           = doc["em3"]["e1"];
  em3day[1]         = doc["em3"]["d2"];
  em3e[1]           = doc["em3"]["e2"];
  em3day[2]         = doc["em3"]["d3"];
  em3e[2]           = doc["em3"]["e3"];
  em3day[3]         = doc["em3"]["d4"];
  em3e[3]           = doc["em3"]["e4"];
  em3day[4]         = doc["em3"]["d5"];
  em3e[4]           = doc["em3"]["e5"];
  em3day[5]         = doc["em3"]["d6"];
  em3e[5]           = doc["em3"]["e6"];
  em3day[6]         = doc["em3"]["d7"];
  em3e[6]           = doc["em3"]["e7"];
  em3emax           = doc["em3"]["emax"];

  // Calendar
  cal1_titel        = doc["cal"]["event1"]["titel"];
  cal1_start        = doc["cal"]["event1"]["start"];
  cal1_end          = doc["cal"]["event1"]["end"];

  cal2_titel        = doc["cal"]["event2"]["titel"];
  cal2_start        = doc["cal"]["event2"]["start"];
  cal2_end          = doc["cal"]["event2"]["end"];

  cal3_titel        = doc["cal"]["event3"]["titel"];
  cal3_start        = doc["cal"]["event3"]["start"];
  cal3_end          = doc["cal"]["event3"]["end"];

  cal4_titel        = doc["cal"]["event4"]["titel"];
  cal4_start        = doc["cal"]["event4"]["start"];
  cal4_end          = doc["cal"]["event4"]["end"];

  cal5_titel        = doc["cal"]["event5"]["titel"];
  cal5_start        = doc["cal"]["event5"]["start"];
  cal5_end          = doc["cal"]["event5"]["end"];

  #ifdef  REFRESH_EPAPER
    DEBUG_PRINT("Update Display ...");
    refresh_epaper();
  #else
    DEBUG_PRINTLN("no Display Update!");
  #endif

   #ifdef  DEBUG
    DEBUG_PRINTLN(" finish!");
    Serial.flush();
  #endif

  #ifdef  DeepSleep
    startDeepSleep();
  #endif
}

void reconnect() 
{
  // Loop until we're reconnected
  while (!client.connected()) 
  {
    while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    DEBUG_PRINT(".");
  }
    DEBUG_PRINT("Attempting MQTT connection...");

    if (client.connect(mqttClientID, mqttUser, mqttPW)) 
    {
      DEBUG_PRINTLN("connected");

      client.subscribe("/epaper/data");
      client.publish("/epaper/onlinestate", "true");

      RSSIValue = WiFi.RSSI();
      char buffer[100];
      sprintf(buffer, "{\"USB\":%.2f,\"USB_POWER\":%d,\"BAT\":%.2f,\"IP\":\"%s\",\"RSSI\":%d}", VCC_USB, USB_POWER, VCC_BAT, NetworkIP, RSSIValue);
      client.publish("/epaper/info", buffer);

      delay(10);
    } else 
    {
      DEBUG_PRINT("failed, rc=");
      DEBUG_PRINT(client.state());
      DEBUG_PRINTLN(" try again in 500 ms");
      delay(500);
    }
  }
}

// Deep Sleep
void startDeepSleep() {

  #ifdef  DEBUG
    DEBUG_PRINTLN("Going to sleep...");
    Serial.flush();
  #endif

  pinMode(PIN_DIO0,       INPUT);       // DIO0
  pinMode(PIN_RST,        INPUT);       // RST Pin EPaper

  pinMode(ADC_BAT_PIN,    INPUT);       // ADC BAT PIN
  pinMode(ADC_BAT_ON_PIN, OUTPUT);      // ADC ON VBAT PIN
  pinMode(ADC_5V_PIN,     INPUT);       // ADC 5V

  digitalWrite(PIN_DIO0,        HIGH);  // DIO0
  digitalWrite(PIN_RST,         HIGH);  // RST Pin EPaper
  digitalWrite(ADC_BAT_PIN,     HIGH);  // ADC BAT PIN
  digitalWrite(ADC_BAT_ON_PIN,  LOW);   // ADC ON VBAT PIN
  digitalWrite(ADC_5V_PIN,      HIGH);  // ADC 5V

  gpio_hold_en(GPIO_NUM_16);            // RST Pin EPaper
  gpio_hold_en(GPIO_NUM_32);            // ADC BAT PIN
  gpio_hold_en(GPIO_NUM_33);            // ADC ON VBAT PIN
  gpio_hold_en(GPIO_NUM_34);            // ADC 5V

  gpio_deep_sleep_hold_en();

  esp_sleep_enable_timer_wakeup(time_to_sleep * 1000000);
  esp_deep_sleep_start();
}

void setup() 
{

  #ifdef  DeepSleep
    gpio_hold_dis(GPIO_NUM_16);       // RST Pin EPaper
    gpio_hold_dis(GPIO_NUM_32);       // ADC BAT PIN
    gpio_hold_dis(GPIO_NUM_33);       // ADC ON VBAT PIN
    gpio_hold_dis(GPIO_NUM_34);       // ADC 5V

    gpio_deep_sleep_hold_dis();
  #endif

  #ifdef  DEBUG
    Serial.begin(115200);
    delay(100);
    DEBUG_PRINTLN();
    DEBUG_PRINTLN("Start Setup ...");
  #else
  #endif

  readVoltage();
  ePaperSetup();

  if(VCC_USB >= 4.00) USB_POWER = true;
  if(VCC_USB <  4.00) USB_POWER = false;

  #ifdef  DeepSleep
    if(VCC_USB >= 4.00) esp_sleep_enable_ext0_wakeup(GPIO_NUM_34,0); //1 = High, 0 = Low
    if(VCC_USB <  4.00) esp_sleep_enable_ext0_wakeup(GPIO_NUM_34,1); //1 = High, 0 = Low
  #endif

  setup_wifi();

  #ifdef  DeepSleep
    adc_power_off();
    btStop();
    esp_bt_controller_disable();
  #endif

  client.setBufferSize(MSG_BUFFER_SIZE);
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);

  DEBUG_PRINTLN("End Setup!");
}

void readVoltage()
{
  pinMode(ADC_BAT_PIN, INPUT);      // ADC BAT PIN
  pinMode(ADC_BAT_ON_PIN, OUTPUT);  // ADC ON VBAT PIN
  pinMode(ADC_5V_PIN, INPUT);       // ADC 5V

  digitalWrite(ADC_BAT_ON_PIN, HIGH);
  delay(10);

  VCC_USB = float(analogReadMilliVolts(ADC_5V_PIN)) * 2 / 1000;
  VCC_BAT = (float(analogReadMilliVolts(ADC_BAT_PIN)) * 2 / 1000) - 0.08;

  DEBUG_PRINTLN();
  DEBUG_PRINT("Analog Read USB Voltage = "); DEBUG_PRINT(VCC_USB); DEBUG_PRINTLN("V");
  DEBUG_PRINT("Analog Read BAT Voltage = "); DEBUG_PRINT(VCC_BAT); DEBUG_PRINTLN("V");

  digitalWrite(ADC_BAT_ON_PIN, LOW);
  digitalWrite(ADC_BAT_PIN, HIGH);
}

void loop() 
{

  if (!client.connected()) 
  {
    counting = millis();
    reconnect();
    lastMsg = millis();
  }
  client.loop();


  unsigned long now = millis();
  if (now - lastMsg > LifeSign) {
    lastMsg = now;

    readVoltage();  // READ ADC VOLTAGE
    if(VCC_USB >= 4.00) USB_POWER = true;
    if(VCC_USB <  4.00) USB_POWER = false;
 
    DEBUG_PRINTLN("Send onlinestate = true");
    
    client.publish("/epaper/onlinestate/repeat", "true");

    RSSIValue = WiFi.RSSI();
    char buffer[100];
    sprintf(buffer, "{\"USB\":%.2f,\"USB_POWER\":%d,\"BAT\":%.2f,\"IP\":\"%s\",\"RSSI\":%d}", VCC_USB, USB_POWER, VCC_BAT, NetworkIP, RSSIValue);
    client.publish("/epaper/info", buffer);
  }
}

void disableWiFi() {
  adc_power_off();
  WiFi.disconnect(true);  // Disconnect from the network
  WiFi.mode(WIFI_OFF);    // Switch WiFi off
  DEBUG_PRINTLN("");
  DEBUG_PRINTLN("WiFi disconnected!");
}

void setModemSleep() {
  disableWiFi();
  setCpuFrequencyMhz(40);   
  DEBUG_PRINTLN("SET CPU 40MHz");
}

void enableWiFi() {
  adc_power_on();
  delay(200);

  WiFi.disconnect(false);  // Reconnect the network
  WiFi.mode(WIFI_STA);     // Switch WiFi off

  delay(200);

  DEBUG_PRINTLN("START WIFI");
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    DEBUG_PRINT(".");
  }

  DEBUG_PRINTLN("");
  DEBUG_PRINTLN("WiFi connected");
  DEBUG_PRINTLN("IP address: ");
  char buff[16];
  sprintf(buff, "%d.%d.%d.%d", WiFi.localIP()[0], WiFi.localIP()[1], WiFi.localIP()[2], WiFi.localIP()[3]);
  NetworkIP = buff;
  DEBUG_PRINTLN(NetworkIP);
}

void wakeModemSleep() {
  setCpuFrequencyMhz(80);
  DEBUG_PRINTLN("SET CPU 80MHz");
  enableWiFi();
}
