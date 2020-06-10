char isWaterValid = 1;
float tempC = 123.123;
float humidity = 123.123;
float Lux = 123.123;
char buf[15] = {0}, empty[1024];

void setup(){
  Serial.begin(9600);

  buf[0] = 's';
  buf[1] = isWaterValid;
  sprintf(&buf[2], "%f", tempC);
  sprintf(&buf[6], "%f", humidity);
  sprintf(&buf[10], "%f", Lux);  
  buf[14] = 'a';

  //for(int i=0;i<15;i++)
  //  Serial.println((int)buf[i]);
}
 
void loop(){
  delay(1410);
  for(int i=0;i<15;i++)
    Serial.write(buf[i]);//Serial.println();
}

void serialEvent(){
  Serial.readBytes(empty, sizeof(buf));
}

