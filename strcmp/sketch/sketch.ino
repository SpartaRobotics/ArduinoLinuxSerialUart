char inByte;
int start = 1;

void setup() {
  Serial.begin(115200);
}

void loop() {
  
  if( Serial.available() > 0 )
  {
    Serial.println("hello world!");
    Serial.read();
  }

}


