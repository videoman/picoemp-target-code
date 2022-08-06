

int GREEN_LED = D0;
int RED_LED = D1;
int Reset = D9;
int GLITCH_SIG = D10;
int b = 0;

void setup() {
  // put your setup code here, to run once:
  digitalWrite(Reset, HIGH);
  delay(200);
  pinMode(Reset, OUTPUT);
  digitalWrite(Reset, HIGH);

  pinMode(GLITCH_SIG, OUTPUT);
  digitalWrite(GLITCH_SIG, LOW);

  Serial.begin(115200); // open the serial port at 115200
  Serial.print("Serial port setup\n");

  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  digitalWrite(GREEN_LED, HIGH);
  delay(1000);
  digitalWrite(LED_BUILTIN, LOW);
  digitalWrite(GREEN_LED, LOW);
  digitalWrite(RED_LED, HIGH);
}

void loop()
{
#define RUN_CNT 500
#define OUTER_LOOP_CNT 900
#define INNER_LOOP_CNT 900

  //Serial.print("Booting into for loop...\n");
  //Serial.print("Booting into for loop...\n");
  //Serial.print("Booting into for loop...\n");
  //Serial.print("Booting into for loop...\n");
  Serial.print("Booting into for loop...\n");

  digitalWrite(LED_BUILTIN, LOW);
  volatile uint32_t i, j;
  volatile uint32_t cnt;
  uint32_t blink_status = 1;
  uint32_t b = 0;
  uint32_t run_cnt = 0;
  uint32_t glitch_cnt = 0;
  //Serial.print("\nCONNECTED 115200\n");
  //Serial.print("W. O. P. R. Login: \n");
  for (run_cnt = 0; run_cnt < RUN_CNT; run_cnt++) {
    //Serial.print("starting loop...");
    //Serial.println(run_cnt);
    //run led on
    //Serial.print("\nCONNECTED 115200\n");
    //Serial.print("W. O. P. R. Login: \n");
    /*digitalWrite(13, HIGH);
      delay(500);
      digitalWrite(13, LOW);
      delay(500);
      digitalWrite(13, HIGH);
      delay(500);
      digitalWrite(13, LOW);
      delay(500);
      blink_status ^= 1;*/
    cnt = 0;
    for ( i = 0; i < OUTER_LOOP_CNT; i++) {
      for ( j = 0; j < INNER_LOOP_CNT; j++) {
        cnt++;
      }
    }

    //Serial.print("Looking for a glitch...\n");
    //look for glitch
    /*Serial.print("Outer Loop CNT: ");
      Serial.println(i);
      Serial.print("Inner Loop CNT: ");
      Serial.println(j);
      Serial.print("Total Loop Count: ");
      Serial.println(cnt);*/
    if (i != OUTER_LOOP_CNT || j != INNER_LOOP_CNT ||
        cnt != (OUTER_LOOP_CNT * INNER_LOOP_CNT)  ) {
      /*Serial.print("GEETINGS PROFESSOR FALKEN.\n");
        Serial.print("\n");
        Serial.print("HOW ARE YOU FEELING TODAY?\n");*/
      Serial.print("Glitched!\n");
      digitalWrite(RED_LED, LOW);
      digitalWrite(GLITCH_SIG, HIGH);
      //if glitched, reset the run count and blink the fault LED
      for ( b = 0 ; b < 16; b++)
      {
        digitalWrite(LED_BUILTIN, HIGH);
        digitalWrite(GREEN_LED, HIGH);
        delay(200);
        digitalWrite(LED_BUILTIN, LOW);
        digitalWrite(GREEN_LED, LOW);
        delay(200);
      }
      run_cnt = 0;
      digitalWrite(GLITCH_SIG, LOW);
      digitalWrite(RED_LED, HIGH);
      delay(100);
      //digitalWrite(Reset, LOW);
    }
  }
}
