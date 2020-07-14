
#include <BleKeyboard.h>

#include "Button2.h";
#include "ESPRotary.h";


#define ROTARY_PIN1  19
#define ROTARY_PIN2 16
#define BUTTON_PIN  17

#define CLICKS_PER_STEP   4  


ESPRotary r = ESPRotary(ROTARY_PIN1, ROTARY_PIN2, CLICKS_PER_STEP);
Button2 b = Button2(BUTTON_PIN);

BleKeyboard bleKeyboard = BleKeyboard("Concrete Control", "md-tech");

void setup() {
  Serial.begin(115200);
  Serial.println("BLE active");
  bleKeyboard.begin();
  
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

void rotate(ESPRotary& r) {
    Serial.println(r.getPosition());
}


void showDirection(ESPRotary& r) {
    if (r.getDirection() == RE_RIGHT) {
      bleKeyboard.write(KEY_MEDIA_VOLUME_UP);
    } else {
      bleKeyboard.write(KEY_MEDIA_VOLUME_DOWN);
    }
    
    bleKeyboard.releaseAll();
}

void click(Button2& btn) {
    if (bleKeyboard.isConnected()) {
      bleKeyboard.write(KEY_MEDIA_PLAY_PAUSE);
      
      bleKeyboard.releaseAll();
    }
    Serial.println("Click");
}

void resetPosition(Button2& btn) {
    r.resetPosition();
    Serial.println("Reset");
}
