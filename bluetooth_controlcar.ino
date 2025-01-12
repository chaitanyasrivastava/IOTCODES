char t;
 
void setup() {
pinMode(9,OUTPUT);   //left motors forward
pinMode(10,OUTPUT);   //left motors reverse
pinMode(11,OUTPUT);   //right motors forward
pinMode(12,OUTPUT);   //right motors reverse
 
Serial.begin(9600);
 
}
 
void loop() {
if(Serial.available()){
  t = Serial.read();
  Serial.println(t);
}
 
if(t == 'F'){            
  digitalWrite(9,HIGH);
  digitalWrite(10,LOW);
  digitalWrite(11,HIGH);
  digitalWrite(12,LOW);
}
 
else if(t == 'B'){      
  digitalWrite(9,LOW);
  digitalWrite(10,HIGH);
  digitalWrite(11,LOW);
  digitalWrite(12,HIGH);
}
 
else if(t == '3'){      
  digitalWrite(9,LOW);
  digitalWrite(10,LOW);
  digitalWrite(11,HIGH);
  digitalWrite(12,LOW);
}
 
else if(t == 'L'){      
  digitalWrite(9,HIGH);
  digitalWrite(10,LOW);
  digitalWrite(11,LOW);
  digitalWrite(12,LOW);
}
 
else if(t == 'R'){      
  digitalWrite(9,LOW);
  digitalWrite(10,LOW);
  digitalWrite(11,LOW);
  digitalWrite(12,LOW);
}
delay(100);
}

    
