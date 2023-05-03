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
long timeIntervalLEDs = 500;
//Task 4 - MIDI
unsigned long previousTimeMIDI = millis();
long timeIntervalMIDI = 100;



//Analog defines
#define slider1 A0
#define slider2 A1
#define slider3 A2
#define slider4 A3
#define envelopeSlide1 A6
#define envelopeSlide2 A7
int rawSlider1 = 0;
int rawSlider2 = 0;
int rawSlider3 = 0;
int rawSlider4 = 0;
int rawEnvelopeSlide1 = 0;
int rawEnvelopeSlide2 = 0;

//button digitalin defines
#define button1 9
#define button2 10
#define button3 11
#define button4 12

//button variables
bool rawButton1 = false;
bool rawButton2 = false;
bool rawButton3 = false;
bool rawButton4 = false;

//LED OUTPUTS
#define LED_PIN1     24
#define LED_PIN2     25
#define LED_PIN3     26
#define LED_PIN4     27
#define NUM_LEDS    100
#define BRIGHTNESS  64
#define LED_TYPE    WS2812
#define COLOR_ORDER GRB
CRGB leds[NUM_LEDS];

bool exampleToggle = false;


//MIDI SETUP
MIDI_CREATE_INSTANCE(HardwareSerial, Serial1, MIDI);
const int channel = 1;


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
  pinMode(button1, INPUT_PULLUP);
  pinMode(button2, INPUT_PULLUP);
  pinMode(button3, INPUT_PULLUP);
  pinMode(button4, INPUT_PULLUP);

  rawButton1 = digitalRead(button1);
  rawButton2 = digitalRead(button2);
  rawButton3 = digitalRead(button3);
  rawButton4 = digitalRead(button4);


  //LED setup
  FastLED.addLeds<WS2812, LED_PIN1, RGB>(leds, NUM_LEDS);  // GRB ordering is typical
  FastLED.addLeds<WS2812, LED_PIN2, RGB>(leds, NUM_LEDS);  // GRB ordering is typical
  FastLED.addLeds<WS2812, LED_PIN3, RGB>(leds, NUM_LEDS);  // GRB ordering is typical
  FastLED.addLeds<WS2812, LED_PIN4, RGB>(leds, NUM_LEDS);  // GRB ordering is typical

  //MIDI setup
  MIDI.begin();

}

void loop() {
  unsigned long currentTime = millis();
  //update ADCs
  if (currentTime - previousTimeADC > timeIntervalADC) {
    previousTimeADC = currentTime;

    Serial.println("Updating ADC values");
    rawSlider1 = analogRead(slider1);
    rawSlider2 = analogRead(slider2);
    rawSlider3 = analogRead(slider3);
    rawSlider4 = analogRead(slider4);
    rawEnvelopeSlide1 = analogRead(envelopeSlide1);
    rawEnvelopeSlide2 = analogRead(envelopeSlide2);

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

    //Impliment logic for ADC -> LED here
  }

  //update buttons
  if (currentTime - previousTimeButtons > timeIntervalButtons) {
    previousTimeButtons = currentTime;

    Serial.println("Updating Button states");
    rawButton1 = digitalRead(button1);
    rawButton2 = digitalRead(button2);
    rawButton3 = digitalRead(button3);
    rawButton4 = digitalRead(button4);

//    Debug Raw print statements
    Serial.print("RAW button 1: ");
    Serial.print(rawButton1);
    Serial.print("\t RAW button 2: ");
    Serial.print(rawButton2);
    Serial.print("\t RAW button 3: ");
    Serial.print(rawButton3);
    Serial.print("\t RAW button 4: ");
    Serial.println(rawButton4);

    //impliment button logic below


  }
  //update LEDs
  if (currentTime - previousTimeLEDS > timeIntervalLEDs) {
    previousTimeLEDS = currentTime;
//    Serial.println("Updating LED state");

    //    if (exampleToggle == true) {
    //      exampleToggle = false;
    //      leds[0] = CRGB::Red;
    //    } else {
    //      exampleToggle = true;
    //      leds[0] = CRGB::Black;
    //    }
    FastLED.show();

  }

  //update LEDs
  if (currentTime - previousTimeMIDI > timeIntervalMIDI) {
    previousTimeMIDI = currentTime;

//    Serial.println("Updating MIDI");

    int note;
//    for (note = 10; note <= 127; note++) {
//      MIDI.sendNoteOn(note, 100, channel);
//      delay(200);
//      MIDI.sendNoteOff(note, 100, channel);
//    }
  }


}
