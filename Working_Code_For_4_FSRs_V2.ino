#include <BleKeyboard.h>
#define FORCE_SENSOR_PIN1 39
#define FORCE_SENSOR_PIN2 34
#define FORCE_SENSOR_PIN3 35
#define FORCE_SENSOR_PIN4 36
#define LED 32

const int MIN_THRESHOLD = 4000;
bool isPressed[4] = {false, false, false, false};    

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
 
  pinMode(LED, OUTPUT);
 
}

void loop() {
  int analogReading1 = analogRead(FORCE_SENSOR_PIN1);
  int analogReading2 = analogRead(FORCE_SENSOR_PIN2);
  int analogReading3 = analogRead(FORCE_SENSOR_PIN3);
  int analogReading4 = analogRead(FORCE_SENSOR_PIN4);

  if (bleKeyboard.isConnected()) {        
  isPressed = {analogReading1 < MIN_THRESHOLD, analogReading2 < MIN_THRESHOLD, analogReading3 < MIN_THRESHOLD, analogReading4 < MIN_THRESHOLD};
  sendValues(isPressed);
  }
 
}

void sendValues(bool isPressed[]) {

  for (int i = 0; i < sizeof(isPressed); i++) {
    if (isPressed[i]) {
      switch (i) {
        case 0:
          bleKeyboard.print("w");
            isPressed[i] = false;
            digitalWrite(LED, HIGH);
            delay(10);
            digitalWrite(LED, LOW);
          break;
       
        case 1:
          bleKeyboard.print("a");
            isPressed[i] = false;
            digitalWrite(LED, HIGH);
            delay(10);
            digitalWrite(LED, LOW);
          break;

        case 2:
          bleKeyboard.print("s");
            isPressed[i] = false;
            digitalWrite(LED, HIGH);
            delay(10);
            digitalWrite(LED, LOW);
          break;

        case 3:
          bleKeyboard.print("d");
            isPressed[i] = false;
            digitalWrite(LED, HIGH);
            delay(10);
            digitalWrite(LED, LOW);
          break;
      }
    }
  }
  bleKeyboard.releaseAll();
}

void twoPlayer(bool isPressed[]) {

      // if more fsr's are added much more directions and options can be added for each player
      // the amount of functions of presses it fully dependent on amount of available keys,
      // so each player wears 2 FSRs, so available options are 2! + 1, so if each player wore three FSRs
      // then they have the possibility of 3!+1 = 7 possible controllable functions.
      if (isPressed[0] && isPressed[1]) {
          bleKeyboard.press(KEY_UP_ARROW);
      } else if (isPressed[0]) {
          bleKeyboard.press(KEY_LEFT_ARROW);
      } else if (isPressed[1]) {
          bleKeyboard.press(KEY_RIGHT_ARROW);
      }
      if (isPressed[2] && isPressed[3]) {
          bleKeyboard.print("w");
      } else if (isPressed[2]) {
          bleKeyboard.print("a");
      } else if (isPressed[3]) {
          bleKeyboard.print("d");
      }
      for (int i = 0; i < 4; i++) {
          isPressed[i] = false;
      }
      bleKeyboard.releaseAll();
}