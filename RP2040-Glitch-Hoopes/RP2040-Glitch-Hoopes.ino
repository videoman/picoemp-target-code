
//Define the Pins
#define GREEN_LED 0
#define RED_LED 1
//#define RESET_IN 9
#define GLITCH_SIG 10

//Connect pin 30 (not gpio pin 30, but RUN) to ground and pico should reset.

#define OUTER_LOOP_CNT 9000
#define INNER_LOOP_CNT 500

int glitched = 0;
int greenblinkcnt = 0;
//int resetcheck = 0;
volatile uint32_t i,j;
volatile uint32_t cnt;

void setup() {
  // put your setup code here, to run once:
    // put your setup code here, to run once:
//    pinMode(RESET_IN, INPUT);
 
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

    
    Serial.begin(115200); // open the serial port at 115200
    Serial.print("Setup complete on Pico.\n");

}



void loop() {
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
        Serial.print("Starting For Loop on Pico\n");
        cnt = 0;
        for (i = 0; i < INNER_LOOP_CNT; i++) {
            for (j = 0; j < OUTER_LOOP_CNT; j++) {
              cnt++;
            }            
        }
        Serial.print("Glitch Check on Pico\n");
        if (i != INNER_LOOP_CNT || j != OUTER_LOOP_CNT || cnt != INNER_LOOP_CNT * OUTER_LOOP_CNT) {
            Serial.print ("----------------------------Done Glitched on Picos!\n");
            glitched = 1;
        }
    }
    
}
