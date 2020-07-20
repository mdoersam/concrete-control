
#include <BleKeyboard.h>

#include "Button2.h";
#include "ESPRotary.h";


#define ROTARY_PIN1 22
#define ROTARY_PIN2 14
#define BUTTON_PIN  23

#define CLICKS_PER_STEP   1

const int encoderResolution = 5;


ESPRotary r = ESPRotary(ROTARY_PIN1, ROTARY_PIN2);//, CLICKS_PER_STEP);
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


int previous1 = 0;
int previous2 = 0;

void loop() {
  r.loop();
  b.loop();
}

void rotate(ESPRotary& r) {
   // Serial.println(r.getPosition());
}

int encoderActionCount = 0;

void showDirection(ESPRotary& r) {
  if((++encoderActionCount % encoderResolution) == 0){
    
    if (r.getDirection() == RE_RIGHT) {
      Serial.println("up");
      bleKeyboard.write(KEY_MEDIA_VOLUME_UP);
    } else {
      Serial.println("down");
      bleKeyboard.write(KEY_MEDIA_VOLUME_DOWN);
    }
    
    bleKeyboard.releaseAll();
    
  }
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
