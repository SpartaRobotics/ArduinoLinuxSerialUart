String msg;

void setup() {
  Serial.begin(115200);
}

void loop() {
  if(Serial.available() > 0)
  {
    msg = Serial.readString();
    msg += " World!";
    Serial.println(msg);
  }
}
