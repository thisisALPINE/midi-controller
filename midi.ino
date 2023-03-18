#include <MIDI.h>
MIDI_CREATE_DEFAULT_INSTANCE();

int POT_PIN = A2;
int potCurrentState = 0;
int potPreviousState = 0;
int midiCurrentState = 0;
int midiPreviousState = 0;
const int threshold = 2;

// Midi variables
byte midiChannel = 1;
byte note = 36;
byte cc = 22;

void setup() {
  // MIDI_BAUD_RATE = 31250
  // DEBUG_BAUD_RATE = 115200
  Serial.begin(31250);
}

void loop() {
  potCurrentState = analogRead(POT_PIN);
  if (abs(potCurrentState - potPreviousState) > threshold) {
    // Do stuff
    midiCurrentState = map(potCurrentState, 0, 1023, 0, 127);
      if (midiCurrentState != midiPreviousState) {
        MIDI.sendControlChange(cc, midiCurrentState, midiChannel);
        Serial.print("Knob value: ");
        Serial.print(midiCurrentState);
        Serial.print(" //");
        Serial.print("Midi channel: ");
        Serial.print(midiChannel);
        Serial.print(" //");
        Serial.print("Control change number: ");
        Serial.println(cc);
      }
    // Then
    potPreviousState = potCurrentState;
  }
}