#include "Button2.h";
#include "ESPRotary.h";


#define ROTARY_PIN1  19
#define ROTARY_PIN2 16
#define BUTTON_PIN  17

#define CLICKS_PER_STEP   4  


ESPRotary r = ESPRotary(ROTARY_PIN1, ROTARY_PIN2, CLICKS_PER_STEP);
Button2 b = Button2(BUTTON_PIN);


void setup() {
  Serial.begin(115200);
  delay(50);
  
  r.setChangedHandler(rotate);
  r.setLeftRotationHandler(showDirection);
  r.setRightRotationHandler(showDirection);

  b.setTapHandler(click);
  b.setLongClickHandler(resetPosition);
}

void loop() {
  r.loop();
  b.loop();
}

// on change
void rotate(ESPRotary& r) {
   Serial.println(r.getPosition());
}


void showDirection(ESPRotary& r) {
  Serial.println(directionToVolume(r.getDirection()));
}


void click(Button2& btn) {
  Serial.println("Click!");
}


void resetPosition(Button2& btn) {
  r.resetPosition();
  Serial.println("Reset!");
}

String directionToVolume(byte direction) {
  if (direction == RE_LEFT) {
    return "DOWN";
  } else if (direction == RE_RIGHT) {
    return "UP";
  }
}
