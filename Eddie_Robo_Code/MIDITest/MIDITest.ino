#include <MIDI.h>

MIDI_CREATE_INSTANCE(HardwareSerial, Serial8, MIDI);
const int channel = 1;

void setup() {
  MIDI.begin();
  Serial.begin(9600);
  Serial.println("hi test code for midi");


}

void loop() {
  int note;
  for (note = 10; note <= 127; note++) {
    MIDI.sendNoteOn(note, 100, 1);
    MIDI.sendNoteOn(note, 100, 2);
    MIDI.sendNoteOn(note, 100, 3);
    MIDI.sendNoteOn(note, 100, 4);
    Serial.println("noteOn");
    delay(200);
    MIDI.sendNoteOff(note, 100, 1);
    MIDI.sendNoteOff(note, 100, 2);
    MIDI.sendNoteOff(note, 100, 3);
    MIDI.sendNoteOff(note, 100, 4);
    Serial.println("note OFF");

  }
  delay(200);
}
