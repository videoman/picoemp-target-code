

int GREEN_LED = 0;
int RED_LED = 1;
int Reset = 2;
int GLITCH_SIG = 3;

//https://learn.adafruit.com/adafruit-trinket-m0-circuitpython-arduino/pinouts


#include <Adafruit_DotStar.h>
#define DATAPIN 7
#define CLOCKPIN 8
Adafruit_DotStar strip = Adafruit_DotStar(1, DATAPIN, CLOCKPIN, DOTSTAR_BGR);
  
#define OUTER_LOOP_CNT 9000
#define INNER_LOOP_CNT 500

int glitched = 0;
int greenblinkcnt = 0;
volatile uint32_t i,j;
volatile uint32_t cnt;


void setup() {
    pinMode(GLITCH_SIG, OUTPUT);
    digitalWrite(GLITCH_SIG, LOW);

  
    pinMode(LED_BUILTIN, OUTPUT);
    pinMode(GREEN_LED, OUTPUT);
    pinMode(RED_LED, OUTPUT);

    //Turn on Greens to prove they work
    digitalWrite(LED_BUILTIN, HIGH);
    digitalWrite(GREEN_LED, HIGH);
  
    delay(1000);

    //Go to preglitched light state
    digitalWrite(LED_BUILTIN, LOW);
    digitalWrite(GREEN_LED, LOW);
    digitalWrite(RED_LED, HIGH);

    //Turn off Built in blinding LED
    strip.begin();
    strip.show();
    
    Serial.begin(115200); // open the serial port at 115200
    Serial.print("Setup complete on Trinket.\n");
}

void loop()
{
    if (glitched == 1) {
        digitalWrite(GLITCH_SIG, HIGH);

        //I use this method to blink so I don't miss the reset stuck in a for loop.  Hopefully hard to miss reset because it was down shorter than this loop runs.
        digitalWrite(LED_BUILTIN, HIGH);
        digitalWrite(RED_LED, LOW);
        greenblinkcnt++;

        if (greenblinkcnt < 5000) {
            digitalWrite(GREEN_LED, HIGH);
        }
        else if (greenblinkcnt < 10000) {
            digitalWrite(GREEN_LED, LOW);
        }
        else {
            greenblinkcnt = 0;
        }
    }
    else {
        Serial.print("Starting For Loop on Trinket\n");
        cnt = 0;
        for (i = 0; i < INNER_LOOP_CNT; i++) {
            for (j = 0; j < OUTER_LOOP_CNT; j++) {
              cnt++;
            }            
        }
        Serial.print("Glitch Check on Trinket\n");
        if (i != INNER_LOOP_CNT || j != OUTER_LOOP_CNT || cnt != INNER_LOOP_CNT * OUTER_LOOP_CNT) {
            Serial.print ("----------------------------Done Glitched on Trinket!\n");
            glitched = 1;
        }
    }
    
}
