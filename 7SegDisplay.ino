// define the LED digit patterns, from 0 - 9
// 1 = LED on, 0 = LED off, in this order:
//                74HC595 pin     Q0,Q1,Q2,Q3,Q4,Q5,Q6,Q7 
//                Mapping to      a, b, c, d, e, f, g    of Seven-Segment LED
byte seven_seg_digits[10] = { B11111100,  // = 0
                              B01100000,  // = 1
                              B11011010,  // = 2
                              B11110010,  // = 3
                              B01100110,  // = 4
                              B10110110,  // = 5
                              B10111110,  // = 6
                              B11100000,  // = 7
                              B11111110,  // = 8
                              B11100110   // = 9
                             };
byte alphabet[26] = { B11101110,  // = a    0
                      B00111110,  // = b    1
                      B10011100,  // = c    2
                      B01111010,  // = d    3
                      B10011110,  // = e    4
                      B10001110,  // = f    5
                      B11100110,  // = g    6
                      B01101110,  // = h    7
                      B00001100,  // = i    8
                      B01111000,  // = j    9
                      B01101110,  // = k    10
                      B00011100,  // = l    11
                      B10101000,  // = m    12
                      B00101010,  // = n    13
                      B11111100,  // = o    14
                      B11001110,  // = p    15
                      B11100110,  // = q    16
                      B00001010,  // = r    17
                      B10110110,  // = s    18
                      B00011110,  // = t    19
                      B01111100,  // = u    20
                      B00111000,  // = v    21
                      B01010100,  // = w    22
                      B01101110,  // = x    23
                      B01110110,  // = y    24
                      B11011010   // = z    25
                    };

// connect to the ST_CP of 74HC595 (pin 12,latch pin)
int latchPin = 8;
// connect to the SH_CP of 74HC595 (pin 11, clock pin)
int clockPin = 12;
// connect to the DS of 74HC595 (pin 14)
int dataPin = 11;
 
void setup() {
  // Set latchPin, clockPin, dataPin as output
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
}
 
// display a number on the digital segment display
void sevenSegWrite(byte digit) {
  // set the latchPin to low potential, before sending data
  digitalWrite(latchPin, LOW);
     
  // the original data (bit pattern)
  shiftOut(dataPin, clockPin, LSBFIRST, seven_seg_digits[digit]);  
 
  // set the latchPin to high potential, after sending data
  digitalWrite(latchPin, HIGH);
}

void charWrite(byte charIndex) {
    digitalWrite(latchPin, LOW);
    shiftOut(dataPin, clockPin, LSBFIRST, alphabet[charIndex]);
    digitalWrite(latchPin, HIGH);
}

void emptyWrite() {
    digitalWrite(latchPin, LOW);
    shiftOut(dataPin, clockPin, LSBFIRST, B00000000);
    digitalWrite(latchPin, HIGH);
}

void loop() {
  
  // count from 9 to 0
  for (byte digit = 10; digit > 0; --digit) {
    delay(500);
    sevenSegWrite(digit - 1); 
  }

  emptyWrite(); delay(1000);

  // loop through alphabet
  for (byte i = 0; i < 26; i++) {
    delay(500);
    charWrite(i);
  }

  emptyWrite(); delay(1000);

  charWrite(3); delay(500);   // d
  charWrite(0); delay(500);   // a
  charWrite(13); delay(500);  // n
  charWrite(6); delay(500);   // g
  emptyWrite(); delay(500);
  charWrite(16); delay(500);  // q
  charWrite(20); delay(500);  // u
  charWrite(14); delay(500);  // o
  charWrite(2); delay(500);   // c
  emptyWrite(); delay(500);
  charWrite(7); delay(500);   // h
  charWrite(20); delay(500);  // u
  charWrite(24); delay(500);  // y
  
  emptyWrite(); delay(1000);
  
}

