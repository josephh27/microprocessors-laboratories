// Define the pins for each segment of the 7-segment display
const int a = 2;
const int b = 3;
const int c = 4;
const int d = 5;
const int e = 6;
const int f = 7;
const int g = 8;

// Define the pin for the toggle switch
const int toggleSwitch = 9;

// Array to store the segment codes for digits 0-9
const int digitCodes[10][7] = {
  {LOW, LOW, LOW, LOW, LOW, LOW, HIGH},    // 0
  {HIGH, LOW, LOW, HIGH, HIGH, HIGH, HIGH},// 1
  {LOW, LOW, HIGH, LOW, LOW, HIGH, LOW},   // 2
  {LOW, LOW, LOW, LOW, HIGH, HIGH, LOW},   // 3
  {HIGH, LOW, LOW, HIGH, HIGH, LOW, LOW},  // 4
  {LOW, HIGH, LOW, LOW, HIGH, LOW, LOW},   // 5
  {LOW, HIGH, LOW, LOW, LOW, LOW, LOW},    // 6
  {LOW, LOW, LOW, HIGH, HIGH, HIGH, HIGH}, // 7
  {LOW, LOW, LOW, LOW, LOW, LOW, LOW},     // 8
  {LOW, LOW, LOW, LOW, HIGH, LOW, LOW}     // 9
};

void setup() {
  // Set all segment pins as output
  pinMode(a, OUTPUT);
  pinMode(b, OUTPUT);
  pinMode(c, OUTPUT);
  pinMode(d, OUTPUT);
  pinMode(e, OUTPUT);
  pinMode(f, OUTPUT);
  pinMode(g, OUTPUT);

  // Set the toggle switch pin as input
  pinMode(toggleSwitch, INPUT_PULLUP);

  // Initialize all segments to HIGH (off)
  displayDigit(10);  // Turn off all segments initially

  // Initialize serial communication for debugging (optional)
  Serial.begin(9600);
}

void loop() {
  // Initialize the current digit to be displayed
  static int currentDigit = 0;
  static bool countingUp = true;

  // Read the state of the toggle switch
  bool countUp = digitalRead(toggleSwitch) == HIGH;

  // Update the counting direction based on the switch state
  if (countUp != countingUp) {
    countingUp = countUp;
    Serial.println(countingUp ? "Switch to counting up" : "Switch to counting down");
  }

  // Display the current digit
  displayDigit(currentDigit);

  // Update the current digit based on the counting direction
  if (countingUp) {
    currentDigit++;
    if (currentDigit > 9) {
      currentDigit = 0;
    }
  } else {
    currentDigit--;
    if (currentDigit < 0) {
      currentDigit = 9;
    }
  }

  // Wait for 0.75 seconds
  delay(750);
}

// Function to display a digit on the 7-segment display
void displayDigit(int digit) {
  if (digit >= 0 && digit <= 9) {
    // Set each segment according to the digit code
    digitalWrite(a, digitCodes[digit][0]);
    digitalWrite(b, digitCodes[digit][1]);
    digitalWrite(c, digitCodes[digit][2]);
    digitalWrite(d, digitCodes[digit][3]);
    digitalWrite(e, digitCodes[digit][4]);
    digitalWrite(f, digitCodes[digit][5]);
    digitalWrite(g, digitCodes[digit][6]);
  } else {
    // If digit is out of bounds, turn off all segments
    digitalWrite(a, HIGH);
    digitalWrite(b, HIGH);
    digitalWrite(c, HIGH);
    digitalWrite(d, HIGH);
    digitalWrite(e, HIGH);
    digitalWrite(f, HIGH);
    digitalWrite(g, HIGH);
  }
}
