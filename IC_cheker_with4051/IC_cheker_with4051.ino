/*VA ->16(Y5),14(Y5),5(Y0)
  GND ->8(Y0),7(Y1),12(Y5),13(Y6)
*/
String pins;
#define N14 10
#define N16 15
typedef struct{
  byte IP[10];
  byte OP[6];
  byte L[2][10];
  byte TT[2][6];
}p16;
p16 IC[25];
char names[20][8] = {"IC7400","IC7402","IC7404","IC7408","IC7410","IC7420","IC7430","IC7432","IC7486"};
typedef struct{
  byte V2 :1;
  byte V1 :1;
  byte V0 :1;
  byte G2 :1;
  byte G1 :1;
  byte G0 :1;
}p;
p source[5];

void setup() {
Serial.begin(9600);
byte i;
IC[0] ={ //7400
        {1,2,4,5,9,10,12,13,14},
        {3,6,8,11},
        {{1,1,0,0,1,1,0,0,1},{0,0,1,1,0,0,1,1,1}}, // Too many I/Ps 
        {{0,1,0,1},{1,0,1,0}}
       };
source[0] = {1,0,1,0,0,1}; //14,7 (Y5,Y1)
/*for(i=22;i<38;i++)
 {pinMode(i,OUTPUT);
  digitalWrite(i,0);
 }*/
for(i=37;i<=47;i+=2)
 {pinMode(i,OUTPUT);
  digitalWrite(i,0);
 }
 Serial.setTimeout(10000);
}

void setvcc(byte j) // Demuxes
{
 
 digitalWrite(37,source[j].G2);
 digitalWrite(39,source[j].G1);
 digitalWrite(41,source[j].G0);
 digitalWrite(43,source[j].V2);
 digitalWrite(45,source[j].V1);
 digitalWrite(47,source[j].V0);
   
}
void begincheck(){
   byte i,j,k,ctr=0,ops=0,runs=0;

 for(i=0;i<1;i++)
 {if(i==0)
  {setvcc(0);
   Serial.println("\nchanging Vcc gnd stage 1");
   delay(3000);
  } 
  Serial.print("\nDatacycle for ");
   Serial.println(names[i]);
   ctr = ops = runs =0 ;
   for(j=0;j<10;j++)
   {if(IC[i].IP[j]==0)
    {continue;}
    else if((i<=N14) && (IC[i].IP[j] >7))
    {  IC[i].IP[j] = IC[i].IP[j]+23;
     }
    else
    {IC[i].IP[j] = IC[i].IP[j]+21;}
    
    pinMode(IC[i].IP[j],OUTPUT);
    Serial.println(IC[i].IP[j]);
   }
   
   Serial.println("IPs are initialized");
   for(j=0;j<6;j++)
   {
    if(IC[i].OP[j]==0)
    {continue;}
    else if((i<N14)&&(IC[i].OP[j]>7))
    {
      IC[i].OP[j] = IC[i].OP[j]+23;
     }
     else{
      IC[i].OP[j] = IC[i].OP[j]+21;}
      ops++;
      pinMode(IC[i].OP[j],INPUT);
      Serial.println(IC[i].OP[j]);
    }
   
  Serial.println("OPs are initialized");
  for(k=0;k<2;k++)
   {ctr = 0;
   int data[6] = {0,0,0,0,0,0};
    for(j=0;j<10;j++)
    { if(IC[i].L[k][j])
      {digitalWrite(IC[i].IP[j],HIGH);
      
      }
      
    }
    delay(1000);
    
    Serial.println("\nIPs activated");
    for(j=0;j<ops;j++)
    {
     data[j]= digitalRead(IC[i].OP[j]);
     
    }
    delay(1000);
    for(j=0;j<10;j++)
    { 
      
      digitalWrite(IC[i].IP[j],LOW);
    }
    delay(1000);
    Serial.print("Expected O/Ps : ");
    for(j=0;j<ops;j++)
    {
      Serial.print(IC[i].TT[k][j]);
      
    }
    Serial.print("\nObtained O/Ps : ");
    for(j=0;j<ops;j++)
    {
      Serial.print(data[j]);
      if(IC[i].TT[k][j] == data[j])
      { ctr++;
      }
     }
   
    if(ctr==ops)
    {
      runs++;
    }
   }
   if(runs==2)
   {
    Serial.print("\nThe IC is :");
    Serial.println(names[i]);
    delay(500);
    exit(0);
   }
   delay(1000);
}
}
void loop() {

 /*if(Serial.available()>0)
{
   Serial.print("Enter the number of pins of the IC : ");
 pins = Serial.readString();
 if(pins == "14" )
 Serial.println("14 pins huh");
 else
 Serial.println("16 pins mhu");
 delay(1000);

 
}
*/
begincheck();
delay(1000);
exit(0); ///////////////////////////////////////////////////////////////////////////////
}
