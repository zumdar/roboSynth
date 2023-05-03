//peter april
// eddie may 1st
// william may 2nd
#include <MIDI.h>

#include <FastLED.h>

//multitask
//Task 1 - ADC
unsigned long previousTimeADC = millis();
long timeIntervalADC = 100;
//Task 2 - Buttons
unsigned long previousTimeButtons = millis();
long timeIntervalButtons = 100;
//Task 3 - LEDs
unsigned long previousTimeLEDS = millis();
long timeIntervalLEDs = 50;
//Task 4 - MIDI
unsigned long previousTimeMIDI = millis();
long timeIntervalMIDI = 100;

#define DEBUG //comment out when done debugging

//Analog defines
#define slider1 A0 //left vertical
#define slider2 A1 //left horizontal
#define slider3 A2 // right horizontal
#define slider4 A3 //right vertical

#define envelopeSlide1 A6 //attack
#define envelopeSlide2 A7 //decay

int rawSlider1 = 0;
int rawSlider2 = 0;
int rawSlider3 = 0;
int rawSlider4 = 0;

int rawEnvelopeSlide1 = 0;
int rawEnvelopeSlide2 = 0;

//button digitalin defines
#define button1 9 //toggle left vertical 
#define button2 10 //toggle left horizontal
#define button3 11 //toggle right horizontal
#define button4 12 //toggle right vertical

#define button5 5 //toggle 1-shot left vertical
#define button6 6 //toggle 1-shot left horizontal
#define button7 7 //toggle 1-shot right horizontal
#define button8 8 //toggle 1-shot right vertical

//button variables
bool rawButton1 = false;
bool rawButton2 = false;
bool rawButton3 = false;
bool rawButton4 = false;

bool rawButton5 = false;
bool rawButton6 = false;
bool rawButton7 = false;
bool rawButton8 = false;

//LED OUTPUTS
#define LED_PIN1     24
#define LED_PIN2     25
#define LED_PIN3     26
#define LED_PIN4     27
#define NUM_LEDS    100
#define BRIGHTNESS  64
#define LED_TYPE    WS2812
#define COLOR_ORDER GRB
CRGB leds1[NUM_LEDS];
CRGB leds2[NUM_LEDS];
CRGB leds3[NUM_LEDS];
CRGB leds4[NUM_LEDS];

//MIDI SETUP
#define notes 4

MIDI_CREATE_INSTANCE(HardwareSerial, Serial8, MIDI);
const int channel = 1;
int noteVals[notes];


bool envelope1Start = false;
bool envelope2Start = false;
bool envelope3Start = false;
bool envelope4Start = false;

//Global variables
void setup() {
  Serial.begin(115200);
  Serial.println("Beginning the program");
  //ADC variable init
  rawSlider1 = analogRead(slider1);
  rawSlider2 = analogRead(slider2);
  rawSlider3 = analogRead(slider3);
  rawSlider4 = analogRead(slider4);

  rawEnvelopeSlide1 = analogRead(envelopeSlide1);
  rawEnvelopeSlide2 = analogRead(envelopeSlide2);

  //button setup
  //toggle
  pinMode(button1, INPUT_PULLUP);
  pinMode(button2, INPUT_PULLUP);
  pinMode(button3, INPUT_PULLUP);
  pinMode(button4, INPUT_PULLUP);
  //1-shot
  pinMode(button5, INPUT_PULLUP);
  pinMode(button6, INPUT_PULLUP);
  pinMode(button7, INPUT_PULLUP);
  pinMode(button8, INPUT_PULLUP);

  rawButton1 = digitalRead(button1);
  rawButton2 = digitalRead(button2);
  rawButton3 = digitalRead(button3);
  rawButton4 = digitalRead(button4);

  rawButton5 = digitalRead(button5);
  rawButton6 = digitalRead(button6);
  rawButton7 = digitalRead(button7);
  rawButton8 = digitalRead(button8);


  //LED setup
  FastLED.addLeds<WS2812, LED_PIN1, GRB>(leds1, NUM_LEDS);  // GRB ordering is typical
  FastLED.addLeds<WS2812, LED_PIN2, GRB>(leds2, NUM_LEDS);  // GRB ordering is typical
  FastLED.addLeds<WS2812, LED_PIN3, GRB>(leds3, NUM_LEDS);  // GRB ordering is typical
  FastLED.addLeds<WS2812, LED_PIN4, GRB>(leds4, NUM_LEDS);  // GRB ordering is typical

  //MIDI setup
  MIDI.begin();

}

void loop() {
  unsigned long currentTime = millis();
  //update ADCs
  if (currentTime - previousTimeADC > timeIntervalADC) {
    previousTimeADC = currentTime;
#ifdef DEBUG
    Serial.println("Updating ADC values");
#endif
    rawSlider1 = analogRead(slider1);
    rawSlider2 = analogRead(slider2);
    rawSlider3 = analogRead(slider3);
    rawSlider4 = analogRead(slider4);
    rawEnvelopeSlide1 = analogRead(envelopeSlide1);
    rawEnvelopeSlide2 = analogRead(envelopeSlide2);

#ifdef DEBUG
    //Debug Raw print statements
    Serial.print("RAW slider 1: ");
    Serial.print(rawSlider1);
    Serial.print("\t RAW slider 2: ");
    Serial.print(rawSlider2);
    Serial.print("\t RAW slider 3: ");
    Serial.print(rawSlider3);
    Serial.print("\t RAW slider 4: ");
    Serial.print(rawSlider4);
    Serial.print("\t RAW Envelope 1: ");
    Serial.print(rawEnvelopeSlide1);
    Serial.print("\t RAW Envelope 2: ");
    Serial.println(rawEnvelopeSlide2);

#endif

    //Impliment logic for ADC -> LED here
  }

  //update buttons
  if (currentTime - previousTimeButtons > timeIntervalButtons) {
    previousTimeButtons = currentTime;

#ifdef DEBUG
    Serial.println("Updating Button states");
#endif
    rawButton1 = digitalRead(button1);
    rawButton2 = digitalRead(button2);
    rawButton3 = digitalRead(button3);
    rawButton4 = digitalRead(button4);
    rawButton5 = digitalRead(button5);
    rawButton6 = digitalRead(button6);
    rawButton7 = digitalRead(button7);
    rawButton8 = digitalRead(button8);

#ifdef DEBUG
    //    Debug Raw print statements
    Serial.print("RAW button 1: ");
    Serial.print(rawButton1);
    Serial.print("\t RAW button 2: ");
    Serial.print(rawButton2);
    Serial.print("\t RAW button 3: ");
    Serial.print(rawButton3);
    Serial.print("\t RAW button 4: ");
    Serial.print(rawButton4);
    Serial.print("\t RAW button 5: ");
    Serial.print(rawButton5);
    Serial.print("\t RAW button 6: ");
    Serial.print(rawButton6);
    Serial.print("\t RAW button 7: ");
    Serial.print(rawButton7);
    Serial.print("\t RAW button 8: ");
    Serial.println(rawButton8);
#endif
    //impliment button logic below

    if (rawButton5 == 0) {
      MIDI.sendPitchBend(8000,1);
    } else if (rawButton6 == 1) {
      MIDI.sendPitchBend(-8000,1);
    }

    if (rawButton6 == 0) {
      MIDI.sendControlChange(1,127,1);
    } else if (rawButton6 == 1) {
      MIDI.sendControlChange(1,0,1);
    }

    if (rawButton7 == 0) {
      MIDI.sendControlChange(71,127,1);
    } else if (rawButton6 == 1) {
      MIDI.sendControlChange(71,0,1);
    }

    if (rawButton8 == 0) {
      MIDI.sendControlChange(74,127,1);
    } else if (rawButton6 == 1) {
      MIDI.sendControlChange(74,0,1);
    }

  }
  //update LEDs
  if (currentTime - previousTimeLEDS > timeIntervalLEDs) {
    previousTimeLEDS = currentTime;
    Serial.println("Updating LED state");
    for (int i = 0; i < NUM_LEDS; i++) {
      leds1[i] = CHSV(mappedSliderLED(rawSlider1, 428, 1018), 255, 255);
      leds2[i] = CHSV(mappedSliderLED(rawSlider2, 34, 599), 255, 255);
      leds3[i] = CHSV(mappedSliderLED(rawSlider3, 420, 956), 255, 255);
      leds4[i] = CHSV(mappedSliderLED(rawSlider4, 67, 615), 255, 255);
    }
    FastLED.show();
  }

  //update MIDI
  if (currentTime - previousTimeMIDI > timeIntervalMIDI) {
    previousTimeMIDI = currentTime;

    Serial.println("Updating MIDI");

    noteVals[0] = mappedSliderMIDI(rawSlider1, 428, 1018);
    noteVals[1] = mappedSliderMIDI(rawSlider2, 34, 599);
    noteVals[2] = mappedSliderMIDI(rawSlider3, 420, 956);
    noteVals[3] = mappedSliderMIDI(rawSlider4, 67, 615);
    Serial.print("Voice 1 NOTE: ");
    Serial.println(noteVals[0]);
    MIDI.sendNoteOn(noteVals[0], 100, 1);
    MIDI.sendNoteOn(noteVals[1], 100, 2);
    MIDI.sendNoteOn(noteVals[2], 100, 3);
    MIDI.sendNoteOn(noteVals[3], 100, 4);

  }
}

//helper functions
int mappedSliderLED(int val, int minVal, int maxVal) {
  int mappedVal = constrain(map(val, minVal, maxVal, 255, 0), 0, 255);
  return mappedVal;
}

int mappedSliderMIDI(int val, int minVal, int maxVal) {
  int mappedVal = constrain(map(val, minVal, maxVal, 0, 127), 0, 127);
  return mappedVal;
}
