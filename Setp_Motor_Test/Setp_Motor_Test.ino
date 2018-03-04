#include <SPI.h>
#include "MsTimer2/MsTimer2.h"


// Define pins.
#define PIN_SPI_MOSI 11
#define PIN_SPI_MISO 12
#define PIN_SPI_SCK 13
#define PIN_SPI_SS 10
#define PIN_BUSY 9
 
void setup()
{
delay(1000);
pinMode(PIN_SPI_MOSI, OUTPUT);
pinMode(PIN_SPI_MISO, INPUT);
pinMode(PIN_SPI_SCK, OUTPUT);
pinMode(PIN_SPI_SS, OUTPUT);
pinMode(PIN_BUSY, INPUT);
SPI.begin();
SPI.setDataMode(SPI_MODE3);
SPI.setBitOrder(MSBFIRST);
Serial.begin(9600);
digitalWrite(PIN_SPI_SS, HIGH);
 
L6470_resetdevice(); //L6470 Reset
L6470_setup(); //L6470 Setup
 
MsTimer2::set(50, fulash); //Interrupt serial monitor timer
MsTimer2::start();
delay(4000);
}
 
void loop(){
<span style="color: #ff0000;"> L6470_move(1,500); //Normal
L6470_busydelay(500);</span> //Wait 2 seconds
}
 
void L6470_setup(){
L6470_setparam_acc(0x40); //[R, WS] Accelerate default 0x08A (12bit) (14.55*val+14.55[step/s^2])
L6470_setparam_dec(0x40); //[R, WS] Decelerate default 0x08A (12bit) (14.55*val+14.55[step/s^2])
L6470_setparam_maxspeed(0x40); //[R, WR] Maximum speed default 0x041 (10bit) (15.25*val+15.25[step/s])
L6470_setparam_minspeed(0x01); //[R, WS] Minimum speed default 0x000 (1+12bit) (0.238*val[step/s])
L6470_setparam_fsspd(0x3ff); //[R, WR] μ Step to full-step conversion speed default 0x027 (10bit) (15.25*val+7.63[step/s])
L6470_setparam_kvalhold(0x20); //[R, WR] Stopped excitation voltage default 0x29 (8bit) (Vs[V]*val/256)
L6470_setparam_kvalrun(0x20); //[R, WR] Fixed rotation excitation voltage default 0x29 (8bit) (Vs[V]*val/256)
L6470_setparam_kvalacc(0x20); //[R, WR] Acceleration excitation voltage default 0x29 (8bit) (Vs[V]*val/256)
L6470_setparam_kvaldec(0x20); //[R, WR] Deceleration excitation voltage default 0x29 (8bit) (Vs[V]*val/256)
 
L6470_setparam_stepmood(0x03); //Step mood default 0x07 (1+3+1+3bit)
}
 
void fulash(){
Serial.print("0x");
Serial.print( L6470_getparam_abspos(),HEX);
Serial.print(" ");
Serial.print("0x");
Serial.println( L6470_getparam_speed(),HEX);
}

