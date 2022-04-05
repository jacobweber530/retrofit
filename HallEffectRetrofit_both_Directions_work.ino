int hallSensorPin = 2;
int hallSensorPinTwo = 3;
//int hallSensorPinThree = 4;
//int hallSensorPinFour = 5;
int ledPin = 13;
int stateOne = 0;
int stateTwo = 0;
//int stateThree = 0;
//int stateFour = 0;
unsigned long counter = 0;
int hasOneGoneOff = 0;
int hasTwoGoneOff = 0;
//int hasThreeGoneOff = false;
//int hasFourGoneOff = true;

void setup() {
  // code here, to run once:
 Serial.begin(9600);
 pinMode(ledPin, OUTPUT);
 pinMode(hallSensorPin, INPUT);
 pinMode(hallSensorPinTwo, INPUT);
 //pinMode(hallSensorPinThree, INPUT);
 //pinMode(hallSensorPinFour, INPUT);

}

void loop() {
  // main code here, to run repeatedly:
stateOne = digitalRead(hallSensorPin);
stateTwo = digitalRead(hallSensorPinTwo);
//stateThree = digitalRead(hallSensorPinThree);
//stateFour = digitalRead(hallSensorPinFour);


if(stateOne == LOW && hasOneGoneOff == 0) {
  counter++;
  hasOneGoneOff = 1;
  hasTwoGoneOff = 0;
  digitalWrite(ledPin, HIGH);
  Serial.print("Magnet read ");
  Serial.println(counter);
  Serial.println(hasOneGoneOff);
  Serial.println(hasTwoGoneOff);
  delay(1000);
  //when state is low, that means magnet was detected so we send a signal to the ledPin to register the magnet. 
  //I need to also write some logic so we know which hall sensor was detected first. This will allow me to know the direction of spin.
}
else if(stateOne == LOW && hasOneGoneOff == 1 && counter > 0) {
  counter--;
  hasOneGoneOff = 0;
  hasTwoGoneOff = 1;
  digitalWrite(ledPin, HIGH);
  Serial.print("Magnet read ");
  Serial.println(counter);
  Serial.println(hasOneGoneOff);
  Serial.println(hasTwoGoneOff);
  delay(1000);
}



//if sensor two is activated and sensor one was activated last, add resistance
if(stateTwo == LOW && hasTwoGoneOff == 0) {
  counter++;
  hasOneGoneOff = 0;
  hasTwoGoneOff = 1;
  Serial.print("H2 Magnet read");
  Serial.print(hasOneGoneOff);
  Serial.print(hasTwoGoneOff);
  delay(1000);
}

//if sensor two is activated and sensor three was activated last, substract resistance
else if(stateTwo == LOW && hasTwoGoneOff == 1 && counter > 0) {
  counter--;
  hasOneGoneOff = 1;
  hasTwoGoneOff = 0;
  Serial.print("H2 Magnet read");
  Serial.print(hasOneGoneOff);
  Serial.print(hasTwoGoneOff);
  delay(1000);
}
//need to account for when resistance and counter are already zero and sensor two is activated (i.e when sensor one is false and two is true but counter is zero). Theoretically once at zero, sensor two can only be reactivated if sensor one is passed first (so this case should never arise) but still want to account for it.

if(stateTwo == LOW && counter == 0) {
  Serial.print("Wow!");
  delay(1000);
}

if(counter == 0) {
  Serial.println("Resistance = 0");
}
else if(counter == 1) {
  Serial.println("Resistance = 15");
}
else if(counter == 2) {
  Serial.println("Resistance = 30");
}
else if(counter == 3) {
  Serial.println("Resistance = 50");
}
else if(counter == 4) {
  Serial.println("Resistance = 70");
}
else if(counter == 5) {
  Serial.println("Resistance = 100");
}

}
