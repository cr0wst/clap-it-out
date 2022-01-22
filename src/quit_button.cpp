#include <Arduino.h>
#include <Bounce.h>
#include <Keyboard.h>

// Pins
const int BUTTON_PIN = 0;
const int GREEN_LED_PIN = 5;
const int YELLOW_LED_1_PIN = 4;
const int YELLOW_LED_2_PIN = 3;
const int YELLOW_LED_3_PIN = 2;
const int RED_LED_PIN = 1;
const int BUZZER_PIN = 23;

const int DEBOUNCE_MS = 10;

// 500ms interval = 1s between each count with 500ms of buzzer
const int INTERVAL_MS = 500;

bool isCountingDown = false;
int currentCount = 0;
unsigned long prevMillis = 0;

Bounce pushButton = Bounce(BUTTON_PIN, DEBOUNCE_MS);

void setup() {
  Serial.begin(38400);

  // Button
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  // LEDs
  pinMode(GREEN_LED_PIN, OUTPUT);
  pinMode(YELLOW_LED_1_PIN, OUTPUT);
  pinMode(YELLOW_LED_2_PIN, OUTPUT);
  pinMode(YELLOW_LED_3_PIN, OUTPUT);
  pinMode(RED_LED_PIN, OUTPUT);
}

void loop() {

  if (pushButton.update() && pushButton.fallingEdge()) {
    if (isCountingDown) {
      Serial.println("Aborting Countdown. Resetting.");
      resetCountdown();
    } else {
      isCountingDown = true;
      initialState();
    }
  }

  // Handle Countdown Update
  if (isCountingDown) {
    unsigned long currentMillis = millis();
    if (currentMillis - prevMillis > INTERVAL_MS) {
      Serial.println("Counting Down");
      switch (currentCount) {
        case 0:
          initialState();
          break;
        case 2: // 3
          digitalWrite(GREEN_LED_PIN, HIGH);
          digitalWrite(YELLOW_LED_1_PIN, HIGH);
          digitalWrite(YELLOW_LED_2_PIN, HIGH);
          digitalWrite(YELLOW_LED_3_PIN, HIGH);
          digitalWrite(RED_LED_PIN, LOW);
          tone(BUZZER_PIN, 97.999);
          break;
        case 3:
          noTone(BUZZER_PIN);
          break;
        case 4: // 2
          digitalWrite(GREEN_LED_PIN, HIGH);
          digitalWrite(YELLOW_LED_1_PIN, LOW);
          digitalWrite(YELLOW_LED_2_PIN, HIGH);
          digitalWrite(YELLOW_LED_3_PIN, HIGH);
          digitalWrite(RED_LED_PIN, LOW);
          tone(BUZZER_PIN, 97.999);
          break;
        case 5:
          noTone(BUZZER_PIN);
          break;
        case 6: // 1
          digitalWrite(GREEN_LED_PIN, HIGH);
          digitalWrite(YELLOW_LED_1_PIN, LOW);
          digitalWrite(YELLOW_LED_2_PIN, LOW);
          digitalWrite(YELLOW_LED_3_PIN, HIGH);
          digitalWrite(RED_LED_PIN, LOW);
          tone(BUZZER_PIN, 97.999);
          break;
        case 7:
          noTone(BUZZER_PIN);
          break;
        case 8: // Clap
          digitalWrite(GREEN_LED_PIN, HIGH);
          digitalWrite(YELLOW_LED_1_PIN, LOW);
          digitalWrite(YELLOW_LED_2_PIN, LOW);
          digitalWrite(YELLOW_LED_3_PIN, LOW);
          digitalWrite(RED_LED_PIN, HIGH);
          tone(BUZZER_PIN, 196);
          sendQuit();
          break;
        case 9:
          noTone(BUZZER_PIN);
          resetCountdown();
          break;
      }

      currentCount++;
      prevMillis = currentMillis;
    }
  } else {
    allOff();
  }
}

void sendQuit() {
  Keyboard.press(MODIFIERKEY_GUI);
  delay(100);
  Keyboard.press(KEY_W);
  delay(100);
  Keyboard.release(MODIFIERKEY_GUI);
  Keyboard.release(KEY_W);
  delay(100);
  Keyboard.press(KEY_ENTER);
  Keyboard.release(KEY_ENTER);
}

void resetCountdown() {
  isCountingDown = false;
  currentCount = 0;
  prevMillis = 0;
  noTone(BUZZER_PIN);
  initialState();
}

// various functions for setting the LED states
void allOff() {
  digitalWrite(GREEN_LED_PIN, LOW);
  digitalWrite(YELLOW_LED_1_PIN, LOW);
  digitalWrite(YELLOW_LED_2_PIN, LOW);
  digitalWrite(YELLOW_LED_3_PIN, LOW);
  digitalWrite(RED_LED_PIN, LOW);
}
void initialState() {
  digitalWrite(GREEN_LED_PIN, HIGH);
  digitalWrite(YELLOW_LED_1_PIN, LOW);
  digitalWrite(YELLOW_LED_2_PIN, LOW);
  digitalWrite(YELLOW_LED_3_PIN, LOW);
  digitalWrite(RED_LED_PIN, LOW);
}

void finalState() {
  digitalWrite(GREEN_LED_PIN, HIGH);
  digitalWrite(YELLOW_LED_1_PIN, HIGH);
  digitalWrite(YELLOW_LED_2_PIN, HIGH);
  digitalWrite(YELLOW_LED_3_PIN, HIGH);
  digitalWrite(RED_LED_PIN, HIGH);
}

void countDown() {

}
