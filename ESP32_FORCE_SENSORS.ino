/*
 * This ESP32 code is created by esp32io.com
 *
 * This ESP32 code is released in the public domain
 *
 * For more detail (instruction and wiring diagram), visit https://esp32io.com/tutorials/esp32-force-sensor
 */

#define FORCE_SENSOR_PIN 32 

void setup() {
  Serial.begin(115200);
  delay(200); 
  // set the ADC attenuation to 11 dB (up to ~3.3V input)
  analogSetPinAttenuation(FORCE_SENSOR_PIN, ADC_11db);
}

int readFSR(int pin) {
  // simple 8-sample average to smooth noise
  const int N = 8;
  int acc = 0;
  for (int i = 0; i < N; ++i) {
    acc = acc + analogRead(pin);  // returns ~0..4095
    delayMicroseconds(300);
  }
  return acc / N;
}

void loop() {
  int value = readFSR(FORCE_SENSOR_PIN);

  // Thresholds tuned for 12-bit (0..4095). Adjust after seeing your raw prints.
  // Roughly scaled from your original 10-bit bins (x4):
  if (value < 40) {
    Serial.printf("FSR = %d -> no pressure\n", value);
  } else if (value < 800) {
    Serial.printf("FSR = %d -> light touch\n", value);
  } else if (value < 2000) {
    Serial.printf("FSR = %d -> light squeeze\n", value);
  } else if (value < 3200) {
    Serial.printf("FSR = %d -> medium squeeze\n", value);
  } else {
    Serial.printf("FSR = %d -> big squeeze\n", value);
  }

  delay(150);  // faster updates; change to 1000 if you prefer once per second
}