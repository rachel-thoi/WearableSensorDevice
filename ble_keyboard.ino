#include <BleKeyboard.h>
#define FORCE_SENSOR_PIN1 34

const int MAX_THRESHOLD = 500;
const int MIN_THRESHOLD = 200;
bool isPressed = false;

//Set the name of the bluetooth keyboard (that shows up in the bluetooth menu of your device)
BleKeyboard bleKeyboard("ESP_KEYBOARD");

void setup() {
  //Start the Serial communication (with the computer at 115200 bits per second)
  Serial.begin(115200);
  //Send this message to the computer
  Serial.println("Starting BLE work!");
  //Begin the BLE keyboard/start advertising the keyboard (so phones can find it)
  bleKeyboard.begin();
  // set the ADC attenuation to 11 dB (up to ~3.3V input)
  analogSetAttenuation(ADC_11db);
}

void loop() {
  int analogReading = analogRead(FORCE_SENSOR_PIN1);
  Serial.print("Baseline Reading: ");
  Serial.println(analogReading);



  if (bleKeyboard.isConnected()) {        
    //if the keyboard is connected to a device
    if (analogReading > MIN_THRESHOLD && isPressed == false) {

      // //Press the 'A' key
      // bleKeyboard.print("A");
      // isPressed = true;
      // Serial.println("key: A, analog reading: "+ analogReading);
      //Press the Space key
      bleKeyboard.print(" ");
      isPressed = true;
      Serial.println("key: Space Bar, analog reading: "+ analogReading);

    }
   
    else{
      if(isPressed && analogReading < MIN_THRESHOLD){
        bleKeyboard.releaseAll();
        Serial.println("key release");
        isPressed = false;
      }
    }   }
   
 
  delay(10);
}