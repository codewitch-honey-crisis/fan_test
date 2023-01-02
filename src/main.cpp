#include <Arduino.h>
#define PERIOD_SECS 1
static volatile int ticks;
static volatile uint32_t tick_ts;
static volatile uint32_t tick_ts_old;
static uint32_t ts;
static void tick_counter() {
  tick_ts = millis();
  ++ticks;
  tick_ts_old = tick_ts;
}
void setup() {
  const float power = 1;
  Serial.begin(115200);
  ticks = 0;
  tick_ts = 0;
  tick_ts_old = 0;
  ts = 0;
  pinMode(22,INPUT);
  attachInterrupt(22,tick_counter,FALLING);
  ledcAttachPin(23,0);
  ledcSetup(0,25*1000,8);
  ledcWrite(0,uint8_t(-1)*power);
}

void loop() {
  uint32_t ms = millis();
  if(ms>ts+(1000*PERIOD_SECS)) {
      ts = ms;
      Serial.print((60/(float)PERIOD_SECS) *(ticks/2));
      Serial.println(" RPM");
      ticks = 0;
    }
}