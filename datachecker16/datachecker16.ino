typedef struct{
  byte IP[10];
  byte OP[6];
  byte L[2][10];
  byte TT[2][6];
  byte vcc :5;
  byte gnd :5;
}p16;

p16 IC[20];
char names[3][10] = {"IC7483"};

void setup() {
Serial.begin(9600);
IC[0] = { //7483
           {1,3,8,10,16,4,7,11,13},
           {15,2,6,9},
           {{0,0,0,1,0,1,1,1,0},{1,0,1,0,1,1,0,1,0}},
           {{1,0,0,0},{0,1,1,1}},
           5,12
          };

}// end of function

void begincheck(){
   byte i,j,k,data[6] ={0},ctr=0,ips=0,ops=0,runs=0;

 for(i=0;i<1;i++)
 { Serial.print("\nDatacycle for ");
   Serial.println(names[i]);
   ctr = ops = ips = runs =0 ;
   for(j=0;j<10;j++)
   {if(IC[i].IP[j]==0)
    continue;
    else
    {
    IC[i].IP[j] = IC[i].IP[j]+35;
    ips++;
    pinMode(IC[i].IP[j],OUTPUT);
    }
   }
   
   Serial.println("IPs are initialized");
   for(j=0;j<6;j++)
   {
    if(IC[i].OP[j]==0)
    continue;
    else
    { 
      IC[i].OP[j] = IC[i].OP[j]+35;
      ops++;
      pinMode(IC[i].OP[j],INPUT);
    }
   }
   Serial.println("OPs are initialized");
   pinMode(IC[i].vcc,OUTPUT);
   pinMode(IC[i].gnd,OUTPUT);
   digitalWrite(IC[i].vcc,HIGH);
   digitalWrite(IC[i].gnd,LOW);
   delay(500);
  for(k=0;k<2;k++)
   {ctr = 0;
    for(j=0;j<ips;j++)
    { if(IC[i].L[k][j])
      {digitalWrite(IC[i].IP[j],HIGH);
      delay(50);
      }
    }
    
    Serial.println("\nIPs activated");
    for(j=0;j<ops;j++)
    {
     data[j]= digitalRead(IC[i].OP[j]);
     delay(50);
     
    }
    
    for(j=0;j<ips;j++)
    { 
      delay(10);
      digitalWrite(IC[i].IP[j],LOW);
    }
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
   delay(3000);
}

}
void loop() {
  delay(5000);
  begincheck();}
