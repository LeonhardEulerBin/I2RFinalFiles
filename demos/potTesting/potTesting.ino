void setup() {
  // Initialize serial communication
  Serial.begin(9600);
}

void loop() {
  // Read the analog value from the potentiometer (0 to 1023)
  int potValue1 = analogRead(A8);
  int potValue2 = analogRead(A9);
  int potValue3 = analogRead(A10);
  int potValue4 = analogRead(A11);

  // Print the potentiometer value to the serial monitor
  Serial.print("PV1: ");
  Serial.print(potValue1);
  Serial.print("   ");
  Serial.print("PV2: ");
  Serial.print(potValue2);
  Serial.print("   ");

  Serial.print("PV3: ");
  Serial.print(potValue3);
  Serial.print("   ");

  Serial.print("PV4: ");
  Serial.print(potValue4);
  Serial.println("   ");


  // Add a short delay to avoid rapid serial output
  delay(100);
}
