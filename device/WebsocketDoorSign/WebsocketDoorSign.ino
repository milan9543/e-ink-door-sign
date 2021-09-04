// Adapted from the ArduinoWebsockets client example
// https://github.com/gilmaimon/ArduinoWebsockets/blob/master/examples/Esp32-Client/Esp32-Client.ino
#include <ArduinoWebsockets.h>
#include <WiFi.h>
#include "DEV_Config.h"
#include "EPD.h"
#include "GUI_Paint.h"
#include <stdlib.h>


const char* ssid = "stf_0x2a";
const char* password = "jyrs3CkNqtqy";
const char* websockets_server_host = "192.168.0.28"; //Enter server adress
const uint16_t websockets_server_port = 1234; // Enter server port

using namespace websockets;

UBYTE *BlackImage, *RYImage;

WebsocketsClient client;

void setup() {
    // Connect to wifi
    WiFi.begin(ssid, password);

    // Wait some time to connect to wifi
    for(int i = 0; i < 10 && WiFi.status() != WL_CONNECTED; i++) {
        printf(".");
        delay(1000);
    }

    // Check if connected to wifi
    if(WiFi.status() != WL_CONNECTED) {
        printf("No Wifi!\n");
        return;
    }

    printf("Conneted to Wifi, Connecting to server.\n");
    // try to connect to Websockets server
    bool connected = client.connect(websockets_server_host, websockets_server_port, "/");
    if(connected) {
        printf("Connected!\n");
        client.send("Hello Server");
    } else {
        printf("Not Connected!\n");
    }
    
    // run callback when messages are received
    client.onMessage([&](WebsocketsMessage message){
        printf("Got Message: ");
        printf(message.data().c_str());

        printf("Setting up the display\n");
    	DEV_Module_Init();
    	EPD_7IN5B_V2_Init();

        UWORD Imagesize = ((EPD_7IN5B_V2_WIDTH % 8 == 0) ? (EPD_7IN5B_V2_WIDTH / 8 ) : (EPD_7IN5B_V2_WIDTH / 8 + 1)) * EPD_7IN5B_V2_HEIGHT;
        if ((BlackImage = (UBYTE *)malloc(Imagesize)) == NULL) {
          printf("Failed to apply for black memory...\r\n");
          while(1);
        }
        if ((RYImage = (UBYTE *)malloc(Imagesize)) == NULL) {
          printf("Failed to apply for red memory...\r\n");
          while(1);
        }
        printf("NewImage:BlackImage and RYImage\r\n");
        Paint_NewImage(BlackImage, EPD_7IN5B_V2_WIDTH, EPD_7IN5B_V2_HEIGHT , 0, WHITE);
        Paint_NewImage(RYImage, EPD_7IN5B_V2_WIDTH, EPD_7IN5B_V2_HEIGHT , 0, WHITE);
        
        for(int i=0; i<48000; i++) {
        	BlackImage[i] = 0xFF;
        	RYImage[i] = 0xFF;
        }

        EPD_7IN5B_V2_Display(BlackImage, RYImage);
    });
}

void loop() {
    // let the websockets client check for incoming messages
    if(client.available()) {
        client.poll();
    }
    delay(500);
}
