const int dispatchButton = 23; //Dispatch Button Pin

const int gateButton = 25; //gate button pin

const int harnessButton = 27; //harness button pin

const int eStopButton = 29;

const int resetButton = 31;

const int rideStartButton = 33;

const int ackButton = 35;

int dispatchButtonState = 0; //Dispatch Button State

int gateButtonState = 0; //Gate Button State

int harnessButtonState = 0; //Harness Button State

int eStopButtonState = 0; 

int resetButtonState = 0;

int rideStartButtonState = 0;

int ackButtonState = 0;

bool gateToggle = 0; //Gate Toggle

bool harnessToggle = 0; //Harness Toggle

bool eStopToggle = 0;

bool resetToggle = 0;

bool rideStartToggle = 1;

bool ackToggle = 0;

const int dispatchLight = 22;  //Dispatch Light Pin

const int gateLight = 24; //Gate Light Pin

const int harnessLight = 26; //Harness Light Pin

const int eStopLight = 28;

const int resetLight = 30;

const int rideStartLight = 32;

const int ackLight = 34;

int dispatchLightState = LOW;  //storing the state of the dispatch LED

int gateLightState = LOW; //storing the state of the gate LED

unsigned long previousMillis = 0;  //stores the last time

long dispatchLightInterval = 100; //interval at which the Dispatch Light Will Blink

const int dispatchingInterval = 150; //interval at which the Dispatch Light Will Blink after the Dispatch Button has been pushed

int i = 0;

void setup() {

  Serial.begin(9600);
  
  pinMode(dispatchLight, OUTPUT);

  pinMode(gateLight, OUTPUT);

  pinMode(harnessLight, OUTPUT);

  pinMode(eStopLight, OUTPUT);

  pinMode(resetLight, OUTPUT);

  pinMode(rideStartLight, OUTPUT);

  pinMode(ackLight, OUTPUT);

  pinMode(dispatchButton, INPUT);

  pinMode(gateButton, INPUT);

  pinMode(harnessButton, INPUT);

  pinMode(eStopButton, INPUT);

  pinMode(resetButton, INPUT);

  pinMode(rideStartButton, INPUT);

  pinMode(ackButton, INPUT);

}

void loop() {

  unsigned long currentMillis = millis();  //the current time

  dispatchButtonState = digitalRead(dispatchButton);

  gateButtonState = digitalRead(gateButton);

  harnessButtonState = digitalRead(harnessButton);

  eStopButtonState = digitalRead(eStopButton);

  resetButtonState = digitalRead(resetButton);

  rideStartButtonState = digitalRead(rideStartButton);

  ackButtonState = digitalRead(ackButton);

  if (eStopButtonState == HIGH) {
    if (ackToggle == 0 and eStopToggle == 0 and rideStartToggle == 0) {
      eStopToggle = 1;

      dispatchLightInterval = 150;

      delay(150);
    }

   /* else {
      eStopToggle = 0;

      dispatchLightInterval = 1000;

      delay(150);
    }


    */
  }

  if (resetButtonState == HIGH) {
    if (eStopToggle == 1) {
      digitalWrite(eStopLight, HIGH);
      delay(4000);

      if (digitalRead(resetButton) == HIGH) {
        eStopToggle = 0;

        rideStartToggle = 1;

        dispatchLightInterval = 100;

        delay(150);
      }
    }
  }

  if (rideStartButtonState == HIGH) {
    if (rideStartToggle == 1) {
      ackToggle = 1;

      dispatchLightInterval = 1000;
      

      rideStartToggle = 0;

      delay(150);

      
    }
  }

  if (ackButtonState == HIGH) {
    if (ackToggle == 1) {

      delay(3000);

      if (digitalRead(ackButton) == HIGH) {
        ackToggle = 0;

        delay(250);
      }

    }
  }
  

  if (dispatchButtonState == HIGH) {

    if (ackToggle == 0 and eStopToggle == 0 and gateToggle == 0 and harnessToggle == 0 and rideStartToggle == 0) {

      digitalWrite(gateLight, LOW);

      digitalWrite(harnessLight, LOW);
      
      dispatch();
    }

  }

  if (gateButtonState == HIGH) {

    if (ackToggle == 0 and eStopToggle == 0 and rideStartToggle == 0) {

    if (gateToggle == 0) {
      gateToggle = 1;

      digitalWrite(dispatchLight, LOW);

      delay(150);
    }

    else {
      gateToggle = 0;

      digitalWrite(gateLight, LOW);

      delay(150);
    }
    }

  }


  if (harnessButtonState == HIGH) {

    if (ackToggle == 0 and eStopToggle == 0 and rideStartToggle == 0) {

    if (harnessToggle == 0) {
      harnessToggle = 1;

      digitalWrite(dispatchLight, LOW);

      delay(150);
    }

    else {
      harnessToggle = 0;

      digitalWrite(harnessLight, LOW);

      delay(150);
    }

    }
  }

  if (rideStartToggle == 0 and ackToggle == 0 and eStopToggle == 0 and gateToggle == 1 and harnessToggle == 0) {

    digitalWrite(harnessLight, HIGH);
  }

  if (rideStartToggle == 0 and ackToggle == 0 and eStopToggle == 0 and harnessToggle == 1 and gateToggle == 0) {
    digitalWrite(gateLight, HIGH);
  }

  

  if (currentMillis - previousMillis >= dispatchLightInterval) {

    previousMillis = currentMillis;

    if (dispatchLightState == LOW) {
      dispatchLightState = HIGH;
    }

    else {
      dispatchLightState = LOW;
    }

    if (eStopToggle == 1) {
      digitalWrite(eStopLight, dispatchLightState);

      digitalWrite(gateLight, LOW);

      digitalWrite(harnessLight, LOW);

      digitalWrite(dispatchLight, LOW);

      
    }

    if(ackToggle == 0 and eStopToggle == 0 and rideStartToggle == 0) {
      digitalWrite(eStopLight, HIGH);
      digitalWrite(resetLight, LOW);
    }

    if(rideStartToggle == 1) {

      if (i <= 35) {
        digitalWrite(rideStartLight, LOW);

        i++;
      }

      if (i == 36) { 
        digitalWrite(rideStartLight, HIGH);

        i = 0;
        
      }
      
      
      digitalWrite(eStopLight, LOW);

      digitalWrite(resetLight, LOW);

      digitalWrite(gateLight, LOW);

      digitalWrite(harnessLight, LOW);

      digitalWrite(dispatchLight, LOW);
    }

    

    if (eStopToggle == 1) {
      digitalWrite(resetLight, HIGH);
    }



    if (ackToggle == 0 and rideStartToggle == 0 and eStopToggle == 0 and gateToggle == 1) {
      digitalWrite(gateLight, dispatchLightState);

      
    }

    if (ackToggle == 0 and rideStartToggle == 0 and eStopToggle == 0 and harnessToggle == 1) {
      digitalWrite(harnessLight, dispatchLightState);


      
    }

    if (ackToggle == 0 and eStopToggle == 0 and gateToggle == 0 and harnessToggle == 0 and rideStartToggle == 0) {
      digitalWrite(dispatchLight, dispatchLightState);

      digitalWrite(harnessLight, HIGH);

      digitalWrite(gateLight, HIGH);
      
    }

    if (ackToggle == 1) {
      if(dispatchLightState == HIGH) {
        digitalWrite(ackLight, LOW);
      }

      else {
        digitalWrite(ackLight, HIGH);
      }

      digitalWrite(rideStartLight, dispatchLightState);

      digitalWrite(resetLight, dispatchLightState);

      digitalWrite(eStopLight, dispatchLightState);

      digitalWrite(dispatchLight, dispatchLightState);

      digitalWrite(harnessLight, dispatchLightState);

      digitalWrite(gateLight, dispatchLightState);
    }

    if (ackToggle == 0) {
      digitalWrite(ackLight, LOW);
    }

    if (rideStartToggle == 0 and ackToggle == 0) {
      digitalWrite(rideStartLight, LOW);
    }
   

      
    } //bracket for the end of the millis loop

    
  } //end of the void loop



 void dispatch() {

  for (int i = 0; i < 15; i++) {

    digitalWrite(dispatchLight, HIGH);

    delay(dispatchingInterval);

    digitalWrite(dispatchLight, LOW);

    delay(dispatchingInterval);
   
  }

  digitalWrite(dispatchLight, LOW);

  delay(2000);


}
