#include <Arduino.h>
#define CLK 9
#define DBIT 10 // so
#define CS 13
#define Relay 8
#include <SoftwareSerial.h>

int v = 0;
float Ctemp, Ftemp;

void setup()   {
    Serial.begin(9600);
    pinMode(CLK, OUTPUT);
    pinMode(DBIT, INPUT);
    pinMode(CS, OUTPUT);
    pinMode(Relay, OUTPUT);
    digitalWrite(CS, HIGH);
    digitalWrite(CLK, LOW);
}

int spiRead()   {
    int value = 0;
    digitalWrite(CS,LOW);
    delay(2);
    digitalWrite(CS,HIGH);
    delay(220);

    digitalWrite(CS,LOW);

    digitalWrite(CLK,HIGH);
    delay(1);
    digitalWrite(CLK,LOW);



    for (int i=14; i>=0; i--) {
        digitalWrite(CLK,HIGH);
        value += digitalRead(DBIT) << i;
        digitalWrite(CLK,LOW);
    }

    if ((value & 0x04) == 0x04) return -1;


    return value >> 3;
}

void loop()   {
    double high = 160.00, low = 140.00; //PP Melting point
    v = spiRead();
    if (v == -1)   {
        Serial.print("No sensor \n");
    }
    else   {
        Ctemp =  v * 0.25;
        Serial.println(Ctemp);

    }
    delay(100);
    if (Ctemp > high)   {
        Serial.println("Relay Off");
        digitalWrite(Relay, HIGH);
    }
    else if (Ctemp < low)   {
        Serial.println("Relay On");
        digitalWrite(Relay, LOW);
    }
}

