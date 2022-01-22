#include <Arduino.h>
#include <Keyboard.h>
#include <Bounce.h>
#include <Fsm.h>

/**
 * These are the pins that each component is connected to.
 */
#define BUTTON_PIN 0
#define GREEN_LED_PIN 5
#define YELLOW_LED_1_PIN 4
#define YELLOW_LED_2_PIN 3
#define YELLOW_LED_3_PIN 2
#define RED_LED_PIN 1
#define BUZZER_PIN 23

 /**
  * The debounce interval in millis.
  */
#define DEBOUNCE_MS 10

  /**
   * The interval between each State transition.
   */
#define INTERVAL_MS 500

   /**
    * The tone to play for 3 - 2 - 1
    */
#define TONE_FREQ 97.999

    /**
     * The tone to play for clap
     */
#define HIGH_TONE_FREQ 196

     /**
      * States
      */
enum {
    READY_TO_START_OFF,
    READY_TO_START_ON,
    COUNTDOWN_3_BEEP_ON,
    COUNTDOWN_3_BEEP_OFF,
    COUNTDOWN_2_BEEP_ON,
    COUNTDOWN_2_BEEP_OFF,
    COUNTDOWN_1_BEEP_ON,
    COUNTDOWN_1_BEEP_OFF,
    CLAP_BEEP_ON,
    CLAP_BEEP_OFF
};

void tick();

int currentState = READY_TO_START_OFF;
int previousMillis = 0;

Bounce pushButton = Bounce(BUTTON_PIN, DEBOUNCE_MS);

/**
 * Handle clicking the button.
 *
 * When in the READY_TO_START state the button starts the countdown.
 * In other states it resets back to READY_TO_START.
 *
 */
void handleButton()
{
    if (pushButton.update() && pushButton.fallingEdge()) {
        switch (currentState) {
        case READY_TO_START_OFF:
            currentState = READY_TO_START_ON;
            break;
        default:
            currentState = READY_TO_START_OFF;
            break;
        }
    }
}

void handleState()
{
    switch (currentState) {
    case READY_TO_START_OFF:
        digitalWrite(GREEN_LED_PIN, LOW);
        digitalWrite(YELLOW_LED_1_PIN, LOW);
        digitalWrite(YELLOW_LED_2_PIN, LOW);
        digitalWrite(YELLOW_LED_3_PIN, LOW);
        digitalWrite(RED_LED_PIN, LOW);

        noTone(BUZZER_PIN);
        break;
    case READY_TO_START_ON:
        digitalWrite(GREEN_LED_PIN, HIGH);
        digitalWrite(YELLOW_LED_1_PIN, LOW);
        digitalWrite(YELLOW_LED_2_PIN, LOW);
        digitalWrite(YELLOW_LED_3_PIN, LOW);
        digitalWrite(RED_LED_PIN, LOW);

        noTone(BUZZER_PIN);
        currentState++;
        break;
    case COUNTDOWN_3_BEEP_ON:
        digitalWrite(GREEN_LED_PIN, HIGH);
        digitalWrite(YELLOW_LED_1_PIN, HIGH);
        digitalWrite(YELLOW_LED_2_PIN, HIGH);
        digitalWrite(YELLOW_LED_3_PIN, HIGH);
        digitalWrite(RED_LED_PIN, LOW);

        tone(BUZZER_PIN, TONE_FREQ);
        currentState++;
        break;
    case COUNTDOWN_3_BEEP_OFF:
        digitalWrite(GREEN_LED_PIN, HIGH);
        digitalWrite(YELLOW_LED_1_PIN, HIGH);
        digitalWrite(YELLOW_LED_2_PIN, HIGH);
        digitalWrite(YELLOW_LED_3_PIN, HIGH);
        digitalWrite(RED_LED_PIN, LOW);

        noTone(BUZZER_PIN);
        currentState++;
        break;
    case COUNTDOWN_2_BEEP_ON:
        digitalWrite(GREEN_LED_PIN, HIGH);
        digitalWrite(YELLOW_LED_1_PIN, LOW);
        digitalWrite(YELLOW_LED_2_PIN, HIGH);
        digitalWrite(YELLOW_LED_3_PIN, HIGH);
        digitalWrite(RED_LED_PIN, LOW);

        tone(BUZZER_PIN, TONE_FREQ);
        currentState++;
        break;
    case COUNTDOWN_2_BEEP_OFF:
        digitalWrite(GREEN_LED_PIN, HIGH);
        digitalWrite(YELLOW_LED_1_PIN, LOW);
        digitalWrite(YELLOW_LED_2_PIN, HIGH);
        digitalWrite(YELLOW_LED_3_PIN, HIGH);
        digitalWrite(RED_LED_PIN, LOW);

        noTone(BUZZER_PIN);
        currentState++;
        break;
    case COUNTDOWN_1_BEEP_ON:
        digitalWrite(GREEN_LED_PIN, HIGH);
        digitalWrite(YELLOW_LED_1_PIN, LOW);
        digitalWrite(YELLOW_LED_2_PIN, LOW);
        digitalWrite(YELLOW_LED_3_PIN, HIGH);
        digitalWrite(RED_LED_PIN, LOW);

        tone(BUZZER_PIN, TONE_FREQ);
        currentState++;
        break;
    case COUNTDOWN_1_BEEP_OFF:
        digitalWrite(GREEN_LED_PIN, HIGH);
        digitalWrite(YELLOW_LED_1_PIN, LOW);
        digitalWrite(YELLOW_LED_2_PIN, LOW);
        digitalWrite(YELLOW_LED_3_PIN, HIGH);
        digitalWrite(RED_LED_PIN, LOW);

        noTone(BUZZER_PIN);
        currentState++;
        break;
    case CLAP_BEEP_ON:
        digitalWrite(GREEN_LED_PIN, HIGH);
        digitalWrite(YELLOW_LED_1_PIN, LOW);
        digitalWrite(YELLOW_LED_2_PIN, LOW);
        digitalWrite(YELLOW_LED_3_PIN, LOW);
        digitalWrite(RED_LED_PIN, HIGH);

        tone(BUZZER_PIN, HIGH_TONE_FREQ);
        currentState = READY_TO_START_OFF;
        break;
    case CLAP_BEEP_OFF:
        digitalWrite(GREEN_LED_PIN, HIGH);
        digitalWrite(YELLOW_LED_1_PIN, LOW);
        digitalWrite(YELLOW_LED_2_PIN, LOW);
        digitalWrite(YELLOW_LED_3_PIN, LOW);
        digitalWrite(RED_LED_PIN, HIGH);

        currentState = READY_TO_START_OFF;
        noTone(BUZZER_PIN);
        break;
    }
}

void setup()
{
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

void loop()
{
    int currentMillis = millis();

    handleButton();

    if (currentMillis - previousMillis > INTERVAL_MS) {
        handleState();
        previousMillis = currentMillis;
    }
}