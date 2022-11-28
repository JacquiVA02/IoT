//Extraido de:
//https://naylampmechatronics.com/blog/42_tutorial-sensores-de-gas-mq2-mq3-mq7-y-mq135.html

int pin_mq = 135;

void setup() { 
  Serial.begin(115200);
  pinMode(pin_mq, INPUT);
}


void loop() {
  
  boolean mq_estado = digitalRead(pin_mq);//Leemos el sensor
  if(mq_estado) //si la salida del sensor es 1
  {
    Serial.println("Sin presencia de gas");
  }
  else //si la salida del sensor es 0
  {
    Serial.println("Gas detectado");
  }
  delay(100); 
}
