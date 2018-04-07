char inByte;
int start = 1;

void setup() {
  Serial.begin(115200);
}

void loop() {

    if( Serial.available() > 0)
    {
      inByte = Serial.read();

      if( inByte == '0' )
        Serial.println("START!");
      else
        missionStage();
    }

}

void missionStage()
{
  if(inByte == '1')
  {
    Serial.println("Starting First Stage");
    delay(10);
  }
  else if(inByte == '2')
  {
    Serial.println("Starting Second Stage");
    delay(10);
  }
  else if(inByte == '3')
  {
    Serial.println("Starting Third Stage");
    delay(10);
  }
  
}

