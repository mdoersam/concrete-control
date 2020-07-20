
#include <BleKeyboard.h>

#include "Button2.h";
#include "ESPRotary.h";


#define ROTARY_PIN1 22
#define ROTARY_PIN2 14
#define BUTTON_PIN  23

#define CLICKS_PER_STEP   4


ESPRotary r = ESPRotary(ROTARY_PIN1, ROTARY_PIN2, CLICKS_PER_STEP);
Button2 b = Button2(BUTTON_PIN);

BleKeyboard bleKeyboard = BleKeyboard("Concrete Control", "md-tech");

void setup() {
  Serial.begin(115200);
  Serial.println("BLE active");
  bleKeyboard.begin();
  
  r.setChangedHandler(rotate);

  b.setTapHandler(click);
  b.setLongClickHandler(resetPosition);
}


void loop() {
  r.loop();
  b.loop();
}

void rotate(ESPRotary& r) {
    if (r.getDirection() == RE_RIGHT) {
      Serial.println("up");
      sendViaBluetooth(KEY_MEDIA_VOLUME_UP);
    } else {
      Serial.println("down");
      sendViaBluetooth(KEY_MEDIA_VOLUME_DOWN);
    }
}

void sendViaBluetooth(const MediaKeyReport c){
    bleKeyboard.write(c);
    bleKeyboard.release(c);
}


void click(Button2& btn) {
    if (bleKeyboard.isConnected()) {
      bleKeyboard.write(KEY_MEDIA_PLAY_PAUSE);
      
      bleKeyboard.release(KEY_MEDIA_PLAY_PAUSE);
    }
    Serial.println("Click");
}

void resetPosition(Button2& btn) {
    r.resetPosition();
    Serial.println("Reset");
}
