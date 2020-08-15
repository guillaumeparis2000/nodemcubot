// Home Automation project
// Get information of sensors
// etc...

#include "peripherals.h"
#include "scheduler.h"
#include "display.h"
#include "mqtt.h"
#include "secrets.h"
#include "globals.h"


// Global objects
uint ticks=0;

void setup() {

  Serial.begin(SERIAL_BAUD);

  initConfig();

  initDisplay();
  initNTPClient();
  initSensors();

  initMDNS();

  updateNTPClientTime();
  getInfoFromSensors();
  getMoistureMesures();
  printWeatherInfo();

  initConfig();

}

void loop() {

    if ((ticks % EVERY_30_MINUTES)==0) {
      getInfoFromSensors();
      getMoistureMesures();
      connect_MQTT();
      printWeatherInfo();

      publishData();

      // Serial.println("Closing WiFi connection...");
      // WiFi.disconnect();

      // delay(100);

      // Serial.println("Entering deep sleep mode for " + SLEEP_DELAY_IN_SECONDS);
      // ESP.deepSleep(SLEEP_DELAY_IN_SECONDS * 1000000, WAKE_RF_DEFAULT);
      // delay(500);   // wait for deep sleep to happen
    }

    if ((ticks % EVERY_1_HOUR)==0) {
      updateNTPClientTime();
      Serial.println("Get time from internet " +getTimeFormatted());
    }

  ticks ++;
  delay(LOOPSLEEP);
}
