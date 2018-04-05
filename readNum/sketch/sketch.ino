char num;

void setup() {
  Serial.begin(115200);
}

void loop() {
  if(Serial.available() > 0)
  {
    num = Serial.read();
    Serial.println(num);
  }
}
