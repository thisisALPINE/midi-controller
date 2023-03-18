#include <MIDI.h>
MIDI_CREATE_DEFAULT_INSTANCE();

int POT_PIN = A2;
int potCurrentState = 0;
int potPreviousState = -1;
int midiCurrentState = 0;
int midiPreviousState = 0;
const int threshold = 1;

// Midi variables
byte midiChannel = 1;
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
      midiPreviousState = midiCurrentState;
    }
    potPreviousState = potCurrentState;
  }
}