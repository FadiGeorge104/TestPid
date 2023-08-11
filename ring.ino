#include "ring.h"

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif
#define PIN 17       // On Trinket or Gemma, suggest changing this to 1
#define NUMPIXELS 16 // Popular NeoPixel ring size
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

#define DELAYVAL 50 // Time (in milliseconds) to pause between pixels

void ringSetup()
{
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
    clock_prescale_set(clock_div_1);
#endif
    pixels.begin();
}


void ringRed()
{
    for (int j = 0; j < 5; j++)
    {
        pixels.clear();
        for (int i = 0; i < NUMPIXELS; i++)
        { // For each pixel...
            // pixels.Color() takes RGB values, from 0,0,0 up to 255,255,255
            // Here we're using a darker shade of green:
            pixels.setPixelColor(i, pixels.Color(c1, 0, 0));
            pixels.show();
            delay(DELAYVAL);
        }
    }
    pixels.clear();
    for (int i = 0; i < NUMPIXELS; i++)
    { // For each pixel...
        // pixels.Color() takes RGB values, from 0,0,0 up to 255,255,255
        // Here we're using a darker shade of green:
        pixels.setPixelColor(i, pixels.Color(0, 40, 0));
        pixels.show();
        delay(DELAYVAL);
    }
}

void ringGreen(){
        for (int i = NUMPIXELS - 1; i >= 0; i--)
        { // For each pixel, starting from the last one...
            // pixels.Color() takes RGB values, from 0,0,0 up to 255,255,255
            // Here we're using a darker shade of green:
            pixels.setPixelColor(i, pixels.Color(0, c1, 0));
            pixels.show();
            delay(DELAYVAL);
        }
}

//     if (x == 's')
//     {
//         for (int j = 0; j < 5; j++)
//         {
//             pixels.setPixelColor(0, pixels.Color(c1, 0, c2));
//             pixels.setPixelColor(1, pixels.Color(c1, 0, c2));
//             pixels.setPixelColor(2, pixels.Color(c1, 0, c2));
//             pixels.setPixelColor(3, pixels.Color(c1, 0, c2));
//             pixels.setPixelColor(4, pixels.Color(c1, 0, c2));
//             pixels.setPixelColor(5, pixels.Color(c1, 0, c2));
//             pixels.setPixelColor(6, pixels.Color(c1, 0, c2));
//             pixels.setPixelColor(7, pixels.Color(c1, 0, c2));
//             pixels.setPixelColor(8, pixels.Color(c1, 0, c2));
//             pixels.setPixelColor(9, pixels.Color(c1, 0, c2));
//             pixels.setPixelColor(10, pixels.Color(c1, 0, c2));
//             pixels.setPixelColor(11, pixels.Color(c1, 0, c2));
//             pixels.setPixelColor(12, pixels.Color(c1, 0, c2));
//             pixels.setPixelColor(13, pixels.Color(c1, 0, c2));
//             pixels.setPixelColor(14, pixels.Color(c1, 0, c2));
//             pixels.setPixelColor(15, pixels.Color(c1, 0, c2));
//             pixels.show();
//             delay(500);
//             pixels.clear();
//             pixels.show();
//             delay(500);
//         }
//     }
// }