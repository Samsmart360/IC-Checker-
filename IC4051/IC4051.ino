// testing a NAND gate at Y0
void setup() {
Serial.begin(9600);
pinMode(49,OUTPUT);
pinMode(51,OUTPUT);
pinMode(53,OUTPUT);
pinMode(43,OUTPUT);
pinMode(45,OUTPUT);
pinMode(47,OUTPUT);
digitalWrite(49,0);
digitalWrite(51,0);
digitalWrite(53,0);
digitalWrite(43,1);
digitalWrite(45,0);
digitalWrite(47,1);

 pinMode(23,OUTPUT);
 pinMode(25,OUTPUT);
 pinMode(27,INPUT);
}

void loop() {
int val;
digitalWrite(23,LOW);
digitalWrite(25,HIGH);
Serial.println("LOW HIGH : ");
delay(100);
val = digitalRead(27);
Serial.println(val);

digitalWrite(23,LOW);
digitalWrite(25,LOW);
Serial.println("LOW LOW : ");
delay(100);
val = digitalRead(27);
Serial.println(val);


digitalWrite(23,HIGH);
digitalWrite(25,HIGH);
Serial.println("HIGH HIGH : ");
delay(100);
val = digitalRead(27);
Serial.println(val);
delay(1000);
}
