/*
 * LoRaLib Receive Example
 * 
 * This example listens for LoRa transmissions and tries to receive them.
 * To successfully receive data, the following settings have to be the same
 * on both transmitter and receiver:
 *  - carrier frequency
 *  - bandwidth
 *  - spreading factor
 *  - coding rate
 *  - sync word
 * 
 * For more detailed information, see the LoRaLib Wiki
 * https://github.com/jgromes/LoRaLib/wiki
 */

// include the library
#include <LoRaLib.h>

// create instance of LoRa class using SX1278 module 
// this pinout corresponds to LoRenz shield: https://github.com/jgromes/LoRenz
// NSS pin:   7
// DIO0 pin:  2
// DIO1 pin:  3
SX1278 lora = new LoRa;

void setup() {
  Serial.begin(9600);

  // initialize SX1278 with default settings
  Serial.print(F("Initializing ... "));
  // carrier frequency:                   434.0 MHz
  // bandwidth:                           125.0 kHz
  // spreading factor:                    9
  // coding rate:                         7
  // sync word:                           0x12
  // output power:                        17 dBm
  byte state = lora.begin();
  if(state == ERR_NONE) {
    Serial.println(F("success!"));
  } else {
    Serial.print(F("failed, code 0x"));
    Serial.println(state, HEX);
    while(true);
  }
}

void loop() {
  Serial.print("Waiting for incoming transmission ... ");

  // you can receive data as an Arduino String
  String str;
  byte state = lora.receive(str);

  // you can also receive data as byte array
  /*
  byte byteArr[8];
  byte state = lora.receive(byteArr, 8);
  */

  if(state == ERR_NONE) {
    // packet was successfully received
    Serial.println("success!");

    // print the data of the packet
    Serial.print("Data:\t\t");
    Serial.println(str);

    //print the measured data rate
    Serial.print("Datarate:\t");
    Serial.print(lora.dataRate);
    Serial.println(" bps");

    //print the RSSI (Received Signal Strength Indicator) of the last received packet
    Serial.print("RSSI:\t\t");
    Serial.print(lora.lastPacketRSSI);
    Serial.println(" dBm");

    //print the SNR (Signal-to-Noise Ratio) of the last received packet
    Serial.print("SNR:\t\t");
    Serial.print(lora.lastPacketSNR);
    Serial.println(" dBm");
    
  } else if(state == ERR_RX_TIMEOUT) {
    // timeout occurred while waiting for a packet
    Serial.println("timeout!");
    
  } else if(state == ERR_CRC_MISMATCH) {
    // packet was received, but is malformed
    Serial.println("CRC error!");
    
  }
  
}

