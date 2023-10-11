#ifndef Clicks_h
#define Clicks_h

/* 
 *  Counts single, double, and triple clicks
 *  Assumes the button pin is INPUT_PULLUP
 */

typedef unsigned long ull;

class Clicks {

  public:

    /* 
     * constructor: initializes pin to INPUT_PULLUP
     */
    Clicks(int pin);

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
    int getClicks();
    
  private:
    ull disableDuration = 300;
    ull waitDuration[3] = {0, 333, 222};
    ull lastClickTime = 0, disableStartTime = 0;
    int prevBtnState = HIGH, curBtnState = HIGH, btnClickCnt = 0, pin;
};

#endif
