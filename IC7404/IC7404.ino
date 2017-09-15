// IC 7404
typedef struct{
  byte IP[8];
  byte OP[6];
  byte L[2][8];
  byte TT[2][4];
}p14;

p14 IC[2];


void setup() {
  Serial.begin(9600);
IC[0] ={ //7400
        {1,2,4,5,9,10,12,13},
        {3,6,8,11},
        {{1,1,1,1,1,1,1,1},{1,0,1,0,1,0,1,0}},
        {{0,0,0,0},{1,1,1,1}}
       };
IC[1] = { //7402
        {2,3,5,6,8,9,11,12},
        {1,4,10,13},
        {{0,0,0,0,0,0,0,0},{1,0,1,0,1,0,1,0}},
        {{1,1,1,1},{0,0,0,0}}
       };
 byte i;

for(i=22;i<36;i++)
 {pinMode(i,LOW);
 }
 
}

void begincheck(){
   byte i,j,k,data[4] ={0},ctr=0,ops=0,runs=0;

 for(i=0;i<2;i++)
 { Serial.print("Datacycle for ");
//   Serial.println(names[i]);
   ctr = ops = 0;
   for(j=0;j<8;j++)
   {if(IC[i].IP[j]<7)
    IC[i].IP[j] = IC[i].IP[j]+21;
    else if(IC[i].IP[j]>7)
    IC[i].IP[j] = IC[i].IP[j]+20; 
    
    if(IC[i].IP[j]==0)
    continue;
    else
    pinMode(IC[i].IP[j],OUTPUT);
   }
   Serial.println("IPs are initialized");
   for(j=0;j<6;j++)
   {
    if(IC[i].OP[j]==0)
    continue;
    else
    { if(IC[i].OP[j]<7)
      IC[i].OP[j] = IC[i].OP[j]+21;
      else if(IC[i].OP[j]>7)
      IC[i].OP[j] = IC[i].OP[j]+20; 
      ops++;
      pinMode(IC[i].OP[j],INPUT);
    }
   }
   Serial.println("OPs are initialized");
  for(k=0;k<2;k++)
   {
    for(j=0;j<8;j++)
    { if(IC[i].L[k][j])
      {digitalWrite(IC[i].IP[j],HIGH);
      delay(50);
      }
    }
    
    Serial.println("IPs activated");
    for(j=0;j<ops;j++)
    {
     data[j]= digitalRead(IC[i].OP[j]);
     delay(50);
     Serial.println(data[j]);
    }
    
    for(j=0;j<8;j++)
    { 
      delay(10);
      digitalWrite(IC[i].IP[j],LOW);
    }
    for(j=0;j<4;j++)
    {
      if(IC[i].TT[k][j] == data[j])
      { ctr++;
        Serial.println("O/P works");
      }
    }
    if(ctr==ops)
    {
      runs++;
    }
   }
   if(runs==2)
   {
    Serial.print("The IC is :");
   // Serial.println(names[i]);
    delay(500);
    exit(0);
   }
   delay(3000);
}
}

void loop() {
  delay(5000);
  begincheck();
}
