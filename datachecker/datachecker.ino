typedef struct{
  byte IP[8];
  byte OP[6];
  byte L[2][8];
  byte TT[2][6];
}p14;
p14 IC[20];
char names[20][8] = {"IC7400","IC7402","IC7404","IC7408","IC7410","IC7420","IC7430","IC7432","IC7486"};
void setup() {
Serial.begin(9600);
IC[0] ={ //7400
        {1,2,4,5,9,10,12,13},
        {3,6,8,11},
        {{1,1,1,1,1,1,1,1},{0,0,0,0,0,0,0,0}},
        {{0,0,0,0},{1,1,1,1}}
       };
IC[1] = { //7402
        {2,3,5,6,8,9,11,12},
        {1,4,10,13},
        {{0,0,0,0,0,0,0,0},{1,0,1,0,1,0,1,0}},
        {{1,1,1,1},{0,0,0,0}}
       };
 IC[2] = { //7404
         {1,3,5,9,11,13},
         {2,4,6,8,10,12},
         {{1,1,1,1,1,1},{0,0,0,0,0,0}},
         {{0,0,0,0,0,0},{1,1,1,1,1,1}}
        };
 IC[3] = { //7408
         {1,2,4,5,9,10,12,13},
         {3,6,8,11},
         {{1,1,1,1,1,1,1,1},{1,0,1,0,1,0,1,0}},
         {{1,1,1,1},{0,0,0,0}}
       };
 IC[4] = { //7410 // only checking for 2 of the gates
         {1,2,13,3,4,5,9,10},
         {12,6,8},
         {{1,1,1,1,1,1,1,1},{1,0,1,0,1,0,1,0}},
         {{0,0,1},{1,1,1}}
       };
 IC[5] = { //7420 
         {1,2,4,5,9,10,12,13},
         {6,8},
         {{1,1,0,0,1,1,1,1},{1,1,1,0,1,0,1,0}},
         {{1,0},{1,1}}
       };
 IC[6] = { //7430
         {1,2,3,4,5,6,11,12},
         {8},
         {{1,1,1,1,1,1,1,1},{1,0,1,0,1,0,1,0}},
         {{0},{1}}
       };
 IC[7] = { //7432
         {1,2,4,5,9,10,12,13},
         {3,6,8,11},
         {{0,0,0,0,0,0,0,0},{1,1,1,0,1,0,1,1}},
         {{0,0,0,0},{1,1,1,1}}
       };

 IC[8] = { //7486
         {1,2,4,5,9,10,12,13},
         {3,6,8,11},
         {{1,1,1,1,1,1,1,1},{1,0,0,0,0,0,1,0}},
         {{0,0,0,0},{1,0,0,1}}
       };
byte i;

for(i=22;i<36;i++)
 {pinMode(i,OUTPUT);
  digitalWrite(i,LOW);// da faq XD
 }
}

void begincheck(){
   byte i,j,k,data[6] ={0},ctr=0,ops=0,runs=0;

 for(i=0;i<9;i++)
 { Serial.print("\nDatacycle for ");
   Serial.println(names[i]);
   ctr = ops = runs =0 ;
   for(j=0;j<8;j++)
   {if(IC[i].IP[j]==0)
    continue;
    else
    {
    if(IC[i].IP[j]<7)
    IC[i].IP[j] = IC[i].IP[j]+21;
    else if(IC[i].IP[j]>7)
    IC[i].IP[j] = IC[i].IP[j]+20;
    pinMode(IC[i].IP[j],OUTPUT);
   }
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
   {ctr = 0;
    for(j=0;j<8;j++)
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
    
    for(j=0;j<8;j++)
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
   delay(1000);
}

}
void loop() {
  delay(5000);
  begincheck();}
