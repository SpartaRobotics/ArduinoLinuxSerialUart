char inByte;
int start = 1;

void setup() {
  Serial.begin(115200);
}

void loop() {

  if(start > 0)
  {
    Serial.println("START");

    if( Serial.read() == '7' )
    {
      start = 0;
    }
  }
  
  if( Serial.available() > 0 )
  {
    inByte = Serial.read();
    missionStage();
  }

}

void missionStage()
{
  if(inByte == '1')
  {
    Serial.println("Starting First Stage");
  }
  else if(inByte == '2')
  {
    Serial.println("Starting Second Stage");
  }
  if(inByte == '3')
  {
    Serial.println("Starting Third Stage");
  }
  
}

