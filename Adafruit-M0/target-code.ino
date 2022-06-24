
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200); // open the serial port at 115200
  Serial.print("Serial port setup\n");
  digitalWrite(13, LOW);
}

void loop()
{
#define RUN_CNT 2000
#define OUTER_LOOP_CNT 900
#define INNER_LOOP_CNT 900

  Serial.print("Booting into for loop...\n");

  digitalWrite(13, LOW);
  volatile uint32_t i, j;
  volatile uint32_t cnt;
  uint32_t blink_status = 1;
  uint32_t b = 0;
  uint32_t run_cnt = 0;
  uint32_t glitch_cnt = 0;

  for (run_cnt = 0; run_cnt < RUN_CNT; run_cnt++) {
    Serial.print("starting loop...");
    Serial.println(run_cnt);
    //run led on
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
      Serial.print("Found an issue!!!\n");
      //if glitched, reset the run count and blink the fault LED
      for( b = 0 ; b < 10; b++) 
      {
      digitalWrite(13, HIGH);
      delay(300);
      digitalWrite(13, LOW);
      delay(300);
      }
      run_cnt = 0;
      delay(5000);
    }
  }
}
