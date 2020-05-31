
#define REDPIN 5
#define GREENPIN 6
#define BLUEPIN 9
#define FADESPEED 5     // make this higher to slow down

#define sw 2
#define inputCLK 4
#define inputDT 3

int counter = 0;
int btnCounter = 0;
int currentStateCLK;
int previousStateCLK;
int rgbcount = 0;
int statecount = 0;
unsigned long lastButtonPress = 0;

String encdir = "";

long duration; // variable for the duration of sound wave travel
int distance; // variable for the distance measurement
int r, g, b;
void setup() {
  pinMode(REDPIN, OUTPUT);
  pinMode(GREENPIN, OUTPUT);
  pinMode(BLUEPIN, OUTPUT);
  pinMode (inputCLK,INPUT);
  pinMode (inputDT,INPUT);
  pinMode (sw, INPUT);
  Serial.begin(9600);
  previousStateCLK = digitalRead(inputCLK);
}
void loop() {
  currentStateCLK = digitalRead(inputCLK);
  if (currentStateCLK != previousStateCLK){ 
     // If the inputDT state is different than the inputCLK state then 
     // the encoder is rotating counterclockwise
     if (digitalRead(inputDT) != currentStateCLK) { 
       counter --;
       encdir ="CCW";
       
     } else {
       // Encoder is rotating clockwise
       counter ++;
       encdir ="CW";
     }
   }
   previousStateCLK = currentStateCLK;  

   int btnState = digitalRead(sw);
 //If we detect LOW signal, button is pressed
  if (btnState == LOW) {
    //if 50ms have passed since last LOW pulse, it means that the
    //button has been pressed, released and pressed again
    if (millis() - lastButtonPress > 50) {
      btnCounter++;
      counter = 0;
      if (btnCounter >= 5){
        btnCounter = 0;
      }
    }

    // Remember last button press event
    lastButtonPress = millis();
  }
  
  light(counter, btnCounter);
  if (btnCounter == 0){
    light(counter, btnCounter);
  } else if (btnCounter == 1){
    light(counter, btnCounter);
  } else if (btnCounter == 2){
    light(counter, btnCounter);
  } else if (btnCounter == 3){
    cycle(statecount, rgbcount);
    rgbcount++;
    if (rgbcount > 255){
      statecount++;
      rgbcount = 0;
    }
    if (statecount == 5){
      statecount = 0;
    }
  }
 
}
void cycle(int state, int col){
  delay(5);
  Serial.println(state);
  Serial.println(col);
  int hold = 0;
  if (state == 0){
    hold = 255 - col;
    analogWrite(BLUEPIN, hold);
  } else if(state == 1){
    analogWrite(GREENPIN, col);
  }else if(state == 2){
    hold = 255 - col;
    analogWrite(REDPIN, hold);
  }else if(state == 3){
    analogWrite(BLUEPIN,col);
  }else if(state == 4){
    hold = 255 - col;
    analogWrite(GREENPIN, hold);
  }
}

void light(int counter1, int btnCounter1){
  int colcounter = 0;
  if (counter1 < 0){
    counter1 = 0;
  }
  int scaled = -(counter) * 10;
  if (scaled > 255){
    scaled = 255;
  }
  if (btnCounter1 == 0){
    analogWrite(GREENPIN, scaled);
  } else if(btnCounter1 == 1){
    analogWrite(REDPIN, scaled);
  } else if(btnCounter1 == 2){
    analogWrite(BLUEPIN, scaled);
  } else if(btnCounter1 == 3){
    for (r = 0; r < 256; r++) { 
    analogWrite(REDPIN, r);
  } 

  } else if(btnCounter1 == 4){
    analogWrite(GREENPIN, 0);
    analogWrite(REDPIN, 0);
    analogWrite(BLUEPIN, 0);
  }
}
