int potPin1 = A8; // Analog input for potentiometer 1
int potPin2 = A9; // Analog input for potentiometer 2
int potPin3 = A10; // Analog input for potentiometer 3
int potPin4 = A11; // Analog input for potentiometer 4


void setup() {

  Serial.begin(9600);
  
}

void loop() {
  int pot1Value = analogRead(potPin1);
  int pot2Value = analogRead(potPin2);
  int pot3Value = analogRead(potPin3);
  int pot4Value = analogRead(potPin4);

  Serial.print(" ");
  Serial.print(pot1Value);
  Serial.print(" ");
  Serial.print(pot2Value);
  Serial.print(" ");
  Serial.print(pot3Value);
  Serial.print(" ");
  Serial.println(pot4Value);


  delay(100); // Adjust the delay time as needed to control the data output rate.
}
