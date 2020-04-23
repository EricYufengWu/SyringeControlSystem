void setup() {
  // put your setup code here, to run once:
  pinMode(14,INPUT_PULLDOWN);
  Serial.begin(38400);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println(digitalRead(14));
  delay(10);
}
