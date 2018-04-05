char msg;
int total;

void setup() {
  Serial.begin(115200);
}

void loop() {
  if(Serial.available() > 0)
  {
    msg = Serial.read();
    total = msg - '0'; //converts character number to integer
    total += 4;
    Serial.println( total );
  }
}
