#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <WiFiClientSecure.h>
#include <LiquidCrystal.h>
#include <cstdlib>

// setup ssid and pwd
// temporarily using phone hotspot for testing
const char *ssid = "AndroidAP4273";
const char *password = "vlsh8655";

// following below schema for publisher-subscriber system
// MC A 	     | MC B
// -------------------------
// Sub to PubB | Sub to PubA
// Pub to PubA | Pub to PubB
// MQTT setup for MC A
const char *mqtt_server = "broker.hivemq.com"; // HiveMQ MQTT broker to use
const int mqtt_port = 1883;                    // default port for MQTT communication over TCP. TDOO: check whether to change port to 8883. I do not think we need to because we are using unsecure TCP.
const char *mqtt_publish = "PubB";             // where to publish signals to
const char *mqtt_subscribe = "PubA";           // where to receive signals from
const char *mqtt_username = std::getenv("MQTT_USERNAME");
const char *mqtt_password = std::getenv("MQTT_PASSWORD");

const int ledPin = 5; // TBD: Set the led pin to light up on request
const int btnPin = 4; // TBD: Set the button pin to receive a signal from
const int rs = 2,
          en = 3,
          d4 = 6,
          d5 = 7,
          d6 = 8,
          d7 = 9; // change later possibly

unsigned long lastMsg = 0; // temp variable to help with testing; I do not have a button RAHHHHHHHH

// set the client using the WiFiClientSecure for TLS
WiFiClient espClient;
PubSubClient client(espClient);
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// callback function
void callback(char *topic, byte *payload, unsigned int length)
{
  Serial.print("Message arrived on topic: ");
  Serial.println(topic);

  // DEBUG: turn on-board light on and off to ensure callback is being called.
  digitalWrite(LED_BUILTIN, LOW);  // Turn LED on
  delay(100);                      // Keep it on for 100 ms
  digitalWrite(LED_BUILTIN, HIGH); // Turn LED off
  delay(100);

  lcd.setCursor(0, 0); // move cursor to the start of the screen
  lcd.blink();         // make a visible curson appear on-screen
  // loop through all characters and print them onto the screen
  for (int i = 0; i < topic.length(); i++)
  {
    lcf.print(topic.charAt(i));
    delay(200)
  }

  // let the message stay on-screen for 10 seconds and clear the screen
  lcd.noBlink();
  delay(10000);
  lcd.clear();

  lcd.setCursor(0, 0); // move cursor to the start of the screen
  lcd.blink();         // make a visible cursor appear on-screen
  // loop through all characters and print them onto the screen
  for (int i = 0; i < topic.length(); i++)
  {
    lcf.print(topic.charAt(i));
    delay(200)
  }

  // let the message stay on-screen for 10 seconds and clear the screen
  lcd.noBlink();
  delay(10000);
  lcd.clear();

  // Check if the message is for LED control
  // if (strcmp(topic, mqtt_subscribe) == 0) {
  //   if (payload[0] == '1') {
  //     digitalWrite(ledPin, HIGH);  // Turn on LED
  //   } else if (payload[0] == '0') {
  //     digitalWrite(ledPin, LOW);   // Turn off LED
  //   }
  // } else {
  //   // do nothing
  // }
}

void setup()
{
  // init serial on 115200 baud
  Serial.begin(115200);

  // init pins
  // pinMode(ledPin, OUTPUT);
  // pinMode(btnPin, INPUT_PULLUP);
  pinMode(LED_BUILTIN, OUTPUT);

  lcd.begin(16, 2);

  // init wifi connection
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  // wait for wifi to connect
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(300);
  }
  // -----------------------
  // here, wifi is connected
  // -----------------------

  // init the client's server, port, and callback function
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback); // what is used on receiving a subscribed topic
}

void reconnect()
{
  // retry connection until we are connected
  while (!client.connected())
  {
    // attempt to connect to the client. If successful, subscribe to the requested topic
    // create random client ID to use
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);

    // on successful connection, subscribe to the topic
    if (client.connect(clientId.c_str()))
    {
      client.subscribe(mqtt_subscribe);
    }
    else
    { // failed to connect, print return code and retry after 3 seconds
      Serial.print("Failed, rc=");
      Serial.print(client.state());
      delay(3000);
    }
  }
}

void loop()
{
  // ensure connection is maintained
  if (!client.connected())
  {
    reconnect();
  }

  client.loop();

  // send a signal every 10 seconds
  unsigned long now = millis();

  if (now - lastMsg > 8000)
  {
    lastMsg = now;
    client.publish(mqtt_publish, "Pinging from B");
    Serial.print("Published message! Client state: ");
    Serial.println(client.state());
    Serial.print("WiFi state: ");
    Serial.print(WiFi.status());
  }

  // // check if button was pressed and, if so, send signal to light the other LED
  // if (digitalRead(btnLed) == LOW) {
  //   // publish onto channel where other microcontroller is listening
  //   client.publish(mqtt_publish, "1");
  //   // apply a debounce delay to prevent one button press being interpreted as multiple
  //   delay(1000);
  // }
}