// -----------------------------------------------------------------------------------
// Polling serial IP for ESP32
#pragma once

#include "../../Common.h"

#ifndef SERIAL_IP_MODE
#define SERIAL_IP_MODE OFF
#endif

#if (SERIAL_IP_MODE == STATION || SERIAL_IP_MODE == ACCESS_POINT) && !defined(SERIAL_IP_CLIENT) && \
    OPERATIONAL_MODE == WIFI

  #include "../wifi/WifiManager.h"

  #if defined(ESP32)
    #include <WiFi.h>
    #include <WiFiClient.h>
    #include <WiFiAP.h>
  #elif defined(ESP8266)
    #include <ESP8266WiFi.h>
    #include <WiFiClient.h>
    #include <ESP8266WiFiAP.h>
  #else
    #error "Configuration (Config.h): No Wifi support is present for this device"
  #endif

  class IPSerial : public Stream {
    public:
      void begin(long port, unsigned long clientTimeoutMs = 2000, bool persist = false);
      
      void end();

      int read(void);

      int available(void);

      int peek(void);

      void flush(void);

      size_t write(uint8_t data);

      size_t write(const uint8_t* data, size_t count);

      inline size_t write(unsigned long n) { return write((uint8_t)n); }
      inline size_t write(long n) { return write((uint8_t)n); }
      inline size_t write(unsigned int n) { return write((uint8_t)n); }
      inline size_t write(int n) { return write((uint8_t)n); }

      using Print::write;

    private:
      WiFiServer *cmdSvr;
      WiFiClient cmdSvrClient;

      int port = -1;
      unsigned long clientTimeoutMs;
      unsigned long clientEndTimeMs = 0;
      bool active = false;
      bool persist = false;
  };

  #if defined(STANDARD_IPSERIAL_CHANNEL) && STANDARD_IPSERIAL_CHANNEL == ON
    extern IPSerial ipSerial;
    #define SERIAL_IP ipSerial
  #endif

  #if defined(PERSISTENT_IPSERIAL_CHANNEL) && PERSISTENT_IPSERIAL_CHANNEL == ON
    extern IPSerial pipSerial;
    #define SERIAL_PIP pipSerial
  #endif
#endif