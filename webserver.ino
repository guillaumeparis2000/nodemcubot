#include <ESP8266WebServer.h>
#include <Utilities.h>
#include "globals.h"

ESP8266WebServer server(80);

void initWebServerRouter() {
  server.on("/", handleRoot);
  server.on("/api/v1/weather", handleGetWeatherInfo);
  //server.on("/api/v1/setposition", HTTP_POST, handleSetPosition);
  server.onNotFound(handleNotFound);
  server.begin();
}

void webServerDoStuff() {
    server.handleClient();
}

void handleRoot() {

  String html = "<!DOCTYPE html><html lang=\"en\"><head><title>Weather Station</title><script type=\"text/javascript\" src=\"https://www.gstatic.com/charts/loader.js\"></script></head><body><div id=\"chart_temp\" style=\"width:200px; height:200px;\"></div><div id=\"chart_humd\" style=\"width:200px; height:200px;\"></div><script>google.charts.load('current',{'packages':['gauge']});google.charts.setOnLoadCallback(drawChart);function drawChart(){var dataTemp = google.visualization.arrayToDataTable([['Label', 'Value'],['Temp', 24]]);var dataHumd = google.visualization.arrayToDataTable([['Label', 'Value'],['Humid %', 65]]);var optionsTemp ={width:200,height:200,redFrom:35,redTo:50,yellowFrom:30,yellowTo:35,minorTicks:5,min:-40,max:50};var optionsHumd ={width:200,height:200,redFrom:90,redTo:100,yellowFrom:75,yellowTo:90,minorTicks:5};var chartTemp = new google.visualization.Gauge(document.getElementById('chart_temp'));var chartHumd = new google.visualization.Gauge(document.getElementById('chart_humd'));fetch('api/v1/weather',{method:'GET'}).then(function(response){if (response.status !== 200){return;}response.json().then(function(obj){dataTemp.setValue(0, 1, obj.temperature);chartTemp.draw(dataTemp, optionsTemp);dataHumd.setValue(0, 1, obj.humidity);chartHumd.draw(dataHumd, optionsHumd);});}).catch(function(err){console.error(err);});setInterval(() =>{fetch('api/v1/weather',{method:'GET'}).then(function(response){if (response.status !== 200){return;}response.json().then(function(obj){dataTemp.setValue(0, 1, obj.temperature);chartTemp.draw(dataTemp, optionsTemp);dataHumd.setValue(0, 1, obj.humidity);chartHumd.draw(dataHumd, optionsHumd);});}).catch(function(err){console.error(err);});}, 20000);}</script></body></html>";

  server.send(200, "text/html", html);
}

void handleGetWeatherInfo() {
  String value = "";
  char str[400];

  sprintf(str, "{\"%s\":%4.1f, \"%s\":%2.f, \"%s\":%4.f, \"%s\":%5.f, \"%s\":%2.f}",
    "temperature", temperature,
    "humidity", humidity,
    "pressure", pressure,
    "altitude", altitude,
    "moisture", moisture_level
    );

  server.send(200, "application/json", str);
}

void handleNotFound() {
   server.send(404, "text/plain", "Sorry, Page Not found");
}

/*void handleSetPosition() {
  StaticJsonBuffer<500> jsonBuffer;
  JsonObject& jsonBody = jsonBuffer.parseObject(server.arg("plain"));
  if (!jsonBody.success()) {
    Serial.println("error in parsin json body");
    server.send(400);
  } else {
    Serial.println("Lon & lat");
    //Serial.println(String(jsonBody["longitude"]));
    //Serial.println(String(jsonBody["latitude"]));
    server.send(201);
  }
}*/
