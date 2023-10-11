#include "Arduino.h"
#include "Clicks.h"

Clicks::Clicks(int _pin) {
  pinMode(_pin, INPUT_PULLUP);
  pin = _pin;
}

/* int clicks(): returns number of clicks 
 *  
 *  Button clicks are only registered as clicks after a certain delay
 *  This is set up so that we can also count double/triple clicks
 *  
 *  ex:
 *  if waitDuration[3] = {0, 333, 222}; then
 *  single click: if no additional click after 333ms of first button click
 *  double click: 2 clicks within 333ms, no additional click after 222ms of second click
 *  triple click: first 2 clicks within 333ms, last 2 clicks within 222ms
 *  
 *  There is also a period of time where button clicks are disabled
 *  right after a click is returned to avoid over counting.
 *  Specified with disableDuration.
 */

int Clicks::getClicks() {
  
  // conditions to satisfy to increment btnClickCnt
  // 1. current button state is LOW, previously was HIGH
  // 2. if we are not currently disabling this 
  curBtnState = digitalRead(pin);
  if (prevBtnState==HIGH && curBtnState==LOW &&
    millis() - disableStartTime >= disableDuration
  ) {
    lastClickTime = millis();
    btnClickCnt += 1;
  }
  prevBtnState = curBtnState;


  // condition to register the click
  // 1. if we counted 3 clicks already, no more clicks
  // 2. if we waited a sufficient amount of time after a click
  int clicks = 0;
  if (btnClickCnt == 3 ||
    (btnClickCnt > 0 && millis() - lastClickTime >= waitDuration[btnClickCnt])
  ){
    clicks = btnClickCnt;
    btnClickCnt = 0;
    disableStartTime = millis();
  } 

// use serial monitor to debug
//  Serial.print("BtnClick: ");
//  Serial.print(btnClickCnt);
//  Serial.print("  Click: ");
//  Serial.println(clicks);
  return clicks;
}
