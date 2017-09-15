int val;
void setup() {
 Serial.begin(9600);
 pinMode(22,OUTPUT);
 pinMode(23,OUTPUT);
 pinMode(24,INPUT);
 pinMode(2,INPUT);
 pinMode(13,OUTPUT);
 pinMode(13,1); 

}

void loop() {

digitalWrite(22,LOW);
digitalWrite(23,HIGH);
Serial.println("LOW HIGH : ");
delay(100);
val = digitalRead(7);
Serial.println(val);
val = digitalRead(24);
Serial.println(val);
val = analogRead(0); 
Serial.println(val);


digitalWrite(22,LOW);
digitalWrite(23,LOW);
Serial.println("LOW LOW : ");
delay(100);
val = digitalRead(7);
Serial.println(val);
val = digitalRead(24);
Serial.println(val);
val = analogRead(0); 
Serial.println(val);


digitalWrite(22,HIGH);
digitalWrite(23,HIGH);
Serial.println("HIGH HIGH : ");
delay(100);
val = digitalRead(7);
Serial.println(val);
val = digitalRead(24);
Serial.println(val);
val = analogRead(0); 
Serial.println(val);

delay(1000);
}
