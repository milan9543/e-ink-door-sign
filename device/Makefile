TINYPICO=/dev/cu.usbserial-020AAF78
EMSYS_COMPILE=arduino-cli compile --fqbn esp32:esp32:tinypico
EMSYS_UPLOAD=arduino-cli upload --fqbn esp32:esp32:tinypico
EMSYS_SCREEN=screen $(TINYPICO) 115200

.PHONY: StaticDoorSign WebsocketDoorSign 

StaticDoorSign: StaticDoorSign/StaticDoorSign.ino
	$(EMSYS_COMPILE) StaticDoorSign 
	$(EMSYS_UPLOAD) -p $(TINYPICO) StaticDoorSign 

WebsocketDoorSign: WebsocketDoorSign/WebsocketDoorSign.ino
	$(EMSYS_COMPILE) WebsocketDoorSign 
	$(EMSYS_UPLOAD) -p $(TINYPICO) WebsocketDoorSign 
	$(EMSYS_SCREEN)
