#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <FastLED.h>

#define PIN_R 6
#define PIN_G 3
#define PIN_B 9
byte r, g, b;

// the setup function runs once when you press reset or power the board
void setup() {
  Serial.begin(115200);
  analogWrite(PIN_R, 255);
  analogWrite(PIN_G, 255);
  analogWrite(PIN_B, 255);
}

// the loop function runs over and over again forever
void loop() {
  byte hue;
  struct CRGB crgb;
  for (hue = 0; hue<=255; hue++) {
    hsv2rgb_rainbow( CHSV(hue, 255, 255), crgb);
    analogWrite(PIN_R, crgb.r);
    analogWrite(PIN_G, crgb.g);
    analogWrite(PIN_B, crgb.b);
    delay(50);
  }
}

void readInstruction() {
  char buf[12];
  if (Serial.available()) {
    Serial.println("Bytes available\n");
    if (Serial.readBytesUntil('\n', buf, 12)) {
      Serial.println("Found terminator\n");
      char *bufptr = buf;
      char *nxtptr;
      int r,g,b;
      if (nxtptr = strchr(bufptr, '.')) {
        *nxtptr++ = '\0';
        r = atoi(bufptr);
        bufptr = nxtptr;
        if (nxtptr = strchr(bufptr, '.')) {
          *nxtptr++ = '\0';
          g = atoi(bufptr);
          b = atoi(nxtptr);
          Serial.println(r);
          Serial.println(g);
          Serial.println(b);
          analogWrite(PIN_R, r);
          analogWrite(PIN_G, g);
          analogWrite(PIN_B, b);
        }
      }
    } 
  }
}

