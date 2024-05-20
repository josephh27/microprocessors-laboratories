const int segmentPins[7] = {2, 3, 4, 5, 6, 7, 8}; // Pins connected to segments A-G
const int digitPins[2] = {9, 10}; // Pins connected to common anode of each 7-segment display
const int ldrPin = A0; // Pin connected to the voltage divider output
const int threshold = 500; // Threshold value for LDR

const byte digits[10] = {
  // ABCDEFG
  B0111111, // 0
  B0000110, // 1
  B1011011, // 2
  B1001111, // 3
  B1100110, // 4
  B1101101, // 5
  B1111101, // 6
  B0000111, // 7
  B1111111, // 8
  B1101111  // 9
};

const byte letters[26] = {
  B1110111, // A
  B1111111, // B 
  B0111001, // C
  B1011110, // D
  B1111001, // E
  B1110001, // F
  B0111101, // G
  B1110110, // H
  B0011000, // I
  B0001110, // J
  B1110110, // K
  B0111000, // L
  B1010101, // M (approximation)
  B1010100, // N (approximation)
  B0111111, // O
  B1110011, // P
  B1100111, // Q (approximation)
  B1010000, // R (approximation)
  B1101101, // S
  B1111000, // T
  B0111110, // U
  B0010100, // V (approximation)
  B0011100, // W (approximation)
  B1110110, // X (approximation)
  B1101110, // Y
  B1011011  // Z (approximation)
};

void setup() {
  for (int i = 0; i < 7; i++) {
    pinMode(segmentPins[i], OUTPUT);
  }
  for (int i = 0; i < 2; i++) {
    pinMode(digitPins[i], OUTPUT);
    digitalWrite(digitPins[i], HIGH); // Turn off the display initially
  }
  pinMode(ldrPin, INPUT);
}

void loop() {
  int ldrValue = analogRead(ldrPin);

  if (ldrValue < threshold) {
    displayMessage("BYE", false); // Display "BYE" from right to left
  } else {
    displayMessage("HELLO", true); // Display "HELLO" from left to right
  }
  delay(1000);
}

void displayMessage(const char* message, bool leftToRight) {
  int length = strlen(message);
  for (int i = 0; i < length - 1; i += 1) {
    char ch1 = message[i];
    char ch2 = (i + 1 < length) ? message[i + 1] : ' ';
    displayChars(ch1, ch2, leftToRight);
    delay(500); // Delay to create the marquee effect
  }
}

void displayChars(char ch1, char ch2, bool leftToRight) {
  byte segments1 = getSegments(ch1);
  byte segments2 = getSegments(ch2);
  
  // Display first character on the first display
  for (int i = 0; i < 7; i++) {
    // Choosing which letter segments in the 7-segment should light up
    digitalWrite(segmentPins[i], bitRead(segments1, i) ? LOW : HIGH);
  }
  digitalWrite(digitPins[1], leftToRight ? HIGH : LOW);
  digitalWrite(digitPins[0], leftToRight ? LOW : HIGH);
  delay(400);

  
  // Display second character on the second display
  for (int i = 0; i < 7; i++) {
    digitalWrite(segmentPins[i], bitRead(segments2, i) ? LOW : HIGH);
  }
  digitalWrite(digitPins[1], leftToRight ? LOW : HIGH);
  digitalWrite(digitPins[0], leftToRight ? HIGH : LOW);
  delay(400);
}

byte getSegments(char ch) {
  if (ch >= '0' && ch <= '9') {
    return digits[ch - '0'];
  } else if (ch >= 'A' && ch <= 'Z') {
    return letters[ch - 'A'];
  }
  return 0; // For unsupported characters
}