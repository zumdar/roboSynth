//peter april
// eddie may 1st
// william/peter may 2nd
#include <MIDI.h>
#include <Bounce.h>
#include <FastLED.h>

//multitask
//Task 1 - ADC
unsigned long previousTimeADC = millis();
long timeIntervalADC = 50;
//Task 2 - Buttons
unsigned long previousTimeButtons = millis();
long timeIntervalButtons = 100;
//Task 3 - LEDs
unsigned long previousTimeLEDS = millis();
long timeIntervalLEDs = 50;
//Task 4 - MIDI
unsigned long previousTimeMIDI = millis();
long timeIntervalMIDI = 100;

//comment out when done debugging
#define DEBUGADC
//#define DEBUGBUTTON
//#define DEBUGLED
//#define DEBUGMIDI

//Analog defines
#define slider1 A0 //left vertical
#define slider2 A1 //left horizontal
#define slider3 A2 // right horizontal
#define slider4 A3 //right vertical

#define attackknob1 A8
#define decayknob2 A9


int rawSlider1 = 0;
int rawSlider2 = 0;
int rawSlider3 = 0;
int rawSlider4 = 0;
float EMA_a = 0.2;      //initialization of EMA alpha
int slider1Average = 0;          //initialization of EMA S
int slider2Average = 0;          //initialization of EMA S
int slider3Average = 0;          //initialization of EMA S
int slider4Average = 0;          //initialization of EMA S

int rawKnob1 = 0;
int rawKnob2 = 0;

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
//
//
//bool rawButton1 = false;
//bool rawButton2 = false;
//bool rawButton3 = false;
//bool rawButton4 = false;

bool rawButton5 = false;
bool rawButton6 = false;
bool rawButton7 = false;
bool rawButton8 = false;

Bounce rawButton1 = Bounce(button1, 10);  // 10 ms debounce
Bounce rawButton2 = Bounce(button2, 10);  // 10 ms debounce
Bounce rawButton3 = Bounce(button3, 10);  // 10 ms debounce
Bounce rawButton4 = Bounce(button4, 10);  // 10 ms debounce

bool circleButton1 = true;
bool circleButton2 = true;
bool circleButton3 = true;
bool circleButton4 = true;

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


int env1 = 0;
int env2 = 0;
int env3 = 0;
int env4 = 0;

//Global variables
void setup() {
  Serial.begin(115200);
  Serial.println("Beginning the program");
  //ADC variable init
  rawSlider1 = analogRead(slider1);
  rawSlider2 = analogRead(slider2);
  rawSlider3 = analogRead(slider3);
  rawSlider4 = analogRead(slider4);

  rawKnob1 = analogRead(attackknob1);
  rawKnob2 = analogRead(decayknob2);

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

  rawButton5 = digitalRead(button5);
  rawButton6 = digitalRead(button6);
  rawButton7 = digitalRead(button7);
  rawButton8 = digitalRead(button8);


  //LED setup
  FastLED.addLeds<1, WS2812, LED_PIN1, GRB>(leds1, NUM_LEDS); // GRB ordering is typical
  FastLED.addLeds<1, WS2812, LED_PIN2, GRB>(leds2, NUM_LEDS); // GRB ordering is typical
  FastLED.addLeds<1, WS2812, LED_PIN3, GRB>(leds3, NUM_LEDS); // GRB ordering is typical
  FastLED.addLeds<1, WS2812, LED_PIN4, GRB>(leds4, NUM_LEDS); // GRB ordering is typical

  //MIDI setup
  MIDI.begin();

}

void loop() {
  unsigned long currentTime = millis();
  //update ADCs
  if (currentTime - previousTimeADC > timeIntervalADC) {
    previousTimeADC = currentTime;
#ifdef DEBUGADC
    Serial.println("Updating ADC values");
    Serial.println();
#endif
    rawSlider1 = analogRead(slider1);
    rawSlider2 = analogRead(slider2);
    rawSlider3 = analogRead(slider3);
    rawSlider4 = analogRead(slider4);

    slider1Average = (EMA_a * rawSlider1) + ((1 - EMA_a) * slider1Average); //run the EMA
    slider2Average = (EMA_a * rawSlider2) + ((1 - EMA_a) * slider2Average); //run the EMA
    slider3Average = (EMA_a * rawSlider3) + ((1 - EMA_a) * slider3Average); //run the EMA
    slider4Average = (EMA_a * rawSlider4) + ((1 - EMA_a) * slider4Average); //run the EMA

    rawKnob1 = analogRead(attackknob1);
    rawKnob2 = analogRead(decayknob2);


#ifdef DEBUGADC
    //Debug Raw print statements
    Serial.print("RAW slider 1: ");
    Serial.print(rawSlider1);
    Serial.print("\t RAW slider 2: ");
    Serial.print(rawSlider2);
    Serial.print("\t RAW slider 3: ");
    Serial.print(rawSlider3);
    Serial.print("\t RAW slider 4: ");
    Serial.println(rawSlider4);
    Serial.println();
    Serial.print("RAW Knob ATTACK 1: ");
    Serial.print(rawKnob1);
    Serial.print("\t RAW Knob DECAY 2: ");
    Serial.println(rawKnob2);
    Serial.println();


#endif

    //Impliment logic for ADC -> LED here
  }

  //update buttons
  if (currentTime - previousTimeButtons > timeIntervalButtons) {
    previousTimeButtons = currentTime;

#ifdef DEBUGBUTTON
    Serial.println("Updating Button states");
#endif

    if (rawButton1.update()) {
      if (rawButton1.fallingEdge()) {
        circleButton1 = !circleButton1;
      }
    }
    if (rawButton2.update()) {
      if (rawButton2.fallingEdge()) {
        circleButton2 = !circleButton2;
      }
    }
    if (rawButton3.update()) {
      if (rawButton3.fallingEdge()) {
        circleButton3 = !circleButton3;
      }
    }
    if (rawButton4.update()) {
      if (rawButton4.fallingEdge()) {
        circleButton4 = !circleButton4;
      }
    }

    rawButton5 = digitalRead(button5);
    rawButton6 = digitalRead(button6);
    rawButton7 = digitalRead(button7);
    rawButton8 = digitalRead(button8);


#ifdef DEBUGBUTTON
    //    Debug Raw print statements
    Serial.print("RAW button 1 toggle: ");
    Serial.print(circleButton1);
    Serial.print("\t RAW button 2 toggle: ");
    Serial.print(circleButton2);
    Serial.print("\t RAW button 3 toggle: ");
    Serial.print(circleButton3);
    Serial.print("\t RAW button 4 toggle: ");
    Serial.print(circleButton4);
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

    //    if (rawButton5 == 0) {
    //      MIDI.sendPitchBend(8000, 1);
    //    } else {
    //      MIDI.sendPitchBend(-8000, 1);
    //    }

    if (circleButton1 == 0 || rawButton5 == 0 ) {
      if (env1 < 120) {
        env1 = env1 + 10;
      } else {
        env1 = 127;
      }
      MIDI.sendPitchBend(int(NewMap(env1, 0, 127, -8000, 8000)), 1);
    } else {
      if (env1 > 10) {
        env1 = env1 - 10;
      } else {
        env1 = 0;
      }
      MIDI.sendPitchBend(int(NewMap(env1, 0, 127, -8000, 8000)), 1);
    }

    if (circleButton2 == 0 || rawButton6 == 0 ) {
      if (env2 < 120) {
        env2 = env2 + 10;
      } else {
        env2 = 127;
      }
      MIDI.sendControlChange(1, env2, 1);
    } else {
      if (env2 > 10) {
        env2 = env2 - 10;
      } else {
        env2 = 0;
      }
      MIDI.sendControlChange(1, env2, 1);
    }

    if (circleButton3 == 0 || rawButton7 == 0 ) {
      if (env3 < 120) {
        env3 = env3 + 10;
      } else {
        env3 = 127;
      }
      MIDI.sendControlChange(71, env3, 1);
    } else {
      if (env3 > 10) {
        env3 = env3 - 10;
      } else {
        env3 = 0;
      }
      MIDI.sendControlChange(71, env3, 1);
    }


    if (circleButton4 == 0 || rawButton8 == 0 ) {
      if (env4 < 120) {
        env4 = env4 + 10;
      } else {
        env4 = 127;
      }
      MIDI.sendControlChange(74, env4, 1);
    } else {
      if (env4 > 10) {
        env4 = env4 - 10;
      } else {
        env4 = 0;
      }
      MIDI.sendControlChange(74, env4, 1);
    }

    //    if (rawButton6 == 0) {
    //      MIDI.sendControlChange(1, 127, 1);
    //    } else {
    //      MIDI.sendControlChange(1, 0, 1);
    //    }
    //    if (rawButton8 == 0) {
    //      MIDI.sendControlChange(74, 127, 1);
    //    } else {
    //      MIDI.sendControlChange(74, 0, 1);
    //    }

  }
  //update LEDs
  if (currentTime - previousTimeLEDS > timeIntervalLEDs) {
    previousTimeLEDS = currentTime;
#ifdef DEBUGLED
    Serial.println("Updating LED state");
#endif
    for (int i = 0; i < NUM_LEDS; i++) {

      leds1[i] = CHSV(mappedSliderLED(slider1Average, 428, 1018), 255, env1 * 2);
      leds2[i] = CHSV(mappedSliderLED(slider2Average, 34, 599), 255, env2 * 2);
      leds3[i] = CHSV(mappedSliderLED(slider3Average, 420, 956), 255, env3 * 2);
      leds4[i] = CHSV(mappedSliderLED(slider4Average, 67, 615), 255, env4 * 2);
      //      leds4[i] = CRGB( 0, 255, 255);
    }
    FastLED.show();
  }
  //update MIDI
  if (currentTime - previousTimeMIDI > timeIntervalMIDI) {
    previousTimeMIDI = currentTime;
#ifdef DEBUGMIDI
    Serial.println("Updating MIDI");
#endif
    noteVals[0] = mappedSliderMIDI(slider1Average, 428, 1018);
    noteVals[1] = mappedSliderMIDI(slider2Average, 34, 599);
    noteVals[2] = mappedSliderMIDI(slider3Average, 420, 956);
    noteVals[3] = mappedSliderMIDI(slider4Average, 67, 615);
#ifdef DEBUGMIDI
    Serial.print("Voice 1 NOTE: ");
    Serial.println(noteVals[0]);
#endif
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

#define MAXLONG 2147483647

long NewMap(long val, long in_min, long in_max, long out_min, long out_max)
{
  // TEST: in_min must be lower than in_max => flip the ranges
  // must be done before out of range test
  if (in_min > in_max) return NewMap(val, in_max, in_min, out_max, out_min);

  // TEST: if input value out of range it is mapped to border values. By choice.
  if (val <= in_min) return out_min;
  if (val >= in_max) return out_max;

  // TEST: special range cases
  if (out_min == out_max) return out_min;
  if (in_min == in_max) return out_min / 2 + out_max / 2; // out_min or out_max? better

  // test if there will be an overflow with well known (unbalanced) formula
  if (( (MAXLONG / abs(out_max - out_min)) < (val - in_min) )  // multiplication overflow test
      || ((MAXLONG - in_max) < -in_min ))                        // division overflow test
  {
    // if overflow would occur that means the ranges are too big
    // To solve this we divide both the input & output range in two
    // alternative is to throw an error.
    // Serial.print(" >> "); // just to see the dividing
    long mid = in_min / 2 + in_max / 2;
    long Tmid = out_min / 2 + out_max / 2;
    if (val > mid)
    {
      // map with upper half of original range
      return NewMap(val, mid, in_max, Tmid, out_max);
    }
    // map with lower half of original range
    return NewMap(val, in_min, mid, out_min, Tmid);
  }

  // finally we have a range that can be calculated
  // unbalanced
  // return out_min + ((out_max - out_min) * (val - in_min)) / (in_max - in_min);

  // or balanced
  // return BalancedMap(val, in_min, in_max, out_min, out_max);
  unsigned long niv = in_max - in_min + 1;          // number input valuer
  unsigned long nov = abs(out_max - out_min) + 1;   // number output values
  unsigned long pos = val - in_min + 1;             // position of val

  unsigned long newpos = ((pos * nov) + niv - 1) / niv; // new position with rounding
  if (out_min < out_max) return out_min + newpos - 1;
  return out_min - newpos + 1;
}
