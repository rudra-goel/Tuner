void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(A0, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int voltage = analogRead(A0);
  int prev;
  if (voltage != prev){
    Serial.println(voltage);
  }
  prev = voltage;
  delay(10);
}
