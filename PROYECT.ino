#include "Keypad.h"

const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
const int buzzerPin = 3;
const int rojoPin = 2;
const int verdePin = 12;
//define the cymbols on the buttons of the keypads
char hexaKeys[ROWS][COLS] = {
  {1,2,3,4},
  {5,6,7,8},
  {9,10,11,12},
  {13,14,15,16}
};


byte rowPins[ROWS] = {7,6,5,4}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {8,9,10,11}; //connect to the column pinouts of the keypad

//initialize an instance of class NewKeypad
Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 

void setup(){
  Serial.begin(9600);
  pinMode(buzzerPin,OUTPUT);
  pinMode(rojoPin,OUTPUT);
  pinMode(verdePin,OUTPUT);
  digitalWrite(buzzerPin,0);
  digitalWrite(rojoPin,0);
  digitalWrite(verdePin,0);
  customKeypad.setHoldTime(1);
}
  
unsigned int lastFrequency =0;
unsigned int frequency;

unsigned  int  frequencies[]={
0,262,294,330,349,
392,440,494,523,
587,659,698,784,
880,988,1046,0
};

char c;
char counter =0;
void loop(){
  
        delay(20);
        c = customKeypad.getKey();

        lastFrequency = frequency;
        frequency =frequencies[c];

    
  
        switch (customKeypad.getState()){
        case PRESSED:
        Serial.println(frequency);
        /*
         if (frequency!=lastFrequency) {
            tone(buzzerPin,frequency);
                    // Remember LED state, lit or unlit.
        }
        */
        if (frequency != 0){
          tone(buzzerPin,frequency);
        }
        break;

    case RELEASED:
        noTone(buzzerPin);
       
        break;

    case HOLD:
        digitalWrite(verdePin, HIGH);
        digitalWrite(rojoPin, LOW);
        break;
    
    case IDLE:
        digitalWrite(rojoPin, HIGH);
        digitalWrite(verdePin, LOW);
        break;
  }
}
