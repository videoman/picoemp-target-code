

int GREENLED = 0;
int REDLED = 1;
int Reset = 5;
int GLITCH_SIG = 6;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200); // open the serial port at 115200
  Serial.print("Serial port setup\n");
  digitalWrite(Reset, HIGH);
  pinMode(Reset, OUTPUT);
  digitalWrite(Reset, HIGH);
  
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(GREENLED, OUTPUT);
  pinMode(REDLED, OUTPUT);
  
  digitalWrite(LED_BUILTIN, HIGH);
  digitalWrite(GREENLED, HIGH);
  
  delay(1000);
  
  digitalWrite(LED_BUILTIN, LOW);
  digitalWrite(GREENLED, LOW);
  digitalWrite(REDLED, HIGH);

  pinMode(GLITCH_SIG, OUTPUT);
  digitalWrite(GLITCH_SIG, LOW);
}

void loop()
{
#define RUN_CNT 1000
#define OUTER_LOOP_CNT 1000
#define INNER_LOOP_CNT 1000

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
      //Serial.print("Glitched!\n");
      digitalWrite(REDLED, LOW);
      //if glitched, reset the run count and blink the fault LED
      digitalWrite(GLITCH_SIG, HIGH);
      for ( b = 0 ; b < 10; b++)
      {
        digitalWrite(LED_BUILTIN, HIGH);
        digitalWrite(GREENLED, HIGH);
        delay(300);
        digitalWrite(LED_BUILTIN, LOW);
        digitalWrite(GREENLED, LOW);
        delay(300);
      }
      run_cnt = 0;
      digitalWrite(REDLED, HIGH);
      delay(100);
      digitalWrite(GLITCH_SIG, LOW);
      digitalWrite(Reset, LOW);
      digitalWrite(Reset, HIGH);

    }
  }
}
