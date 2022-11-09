#define GUMB1 29 
#define GUMB2 31
#define STIKALO 27
#define LED1 23
#define LED2 25
#define STARTLED 10
#define N 4

long int zacetek = 0;
int stanje1 = 0;
int stanje2 = 0;
int igra_poteka = 0;
int zamik = 0;
int zadnje_stanje=0;
int zacetek_igre=0;
int gorim = 500;
int zacetek_ledice = 0;
int konec = 0;
int konec_igre=0;
int cakam=0;
int rezultat=0;
int rezultat_izpis[4];
long int zaslon[32];
int temp = 0;
int lista[32]={2,3,4,5,6,7,8,9,45,53,51,49,47,55,43,41,36,34,32,30,28,26,24,22,44,52,50,48,46,55,42,40};
int stevilke[10][8]={{1,1,1,0,1,0,1,1},
                     {0,0,1,0,0,0,0,1},
                     {1,1,0,1,0,0,1,1},
                     {0,1,1,1,0,0,1,1},
                     {0,0,1,1,1,0,0,1},
                     {0,1,1,1,1,0,1,0},
                     {1,1,1,1,1,0,1,0},
                     {0,0,1,0,0,0,1,1},
                     {1,1,1,1,1,0,1,1},
                     {0,1,1,1,1,0,1,1}};

void setup() {
  
  Serial.begin(9600);
  pinMode(GUMB1,INPUT);
  pinMode(GUMB2,INPUT);
  pinMode(STIKALO,INPUT);
  pinMode(LED1,OUTPUT);
  pinMode(LED2,OUTPUT);
  pinMode(STARTLED,OUTPUT);

  for(int i=0;i<=32;i++){
      pinMode(lista[i], OUTPUT);
    }
  
  
  digitalWrite(LED1, HIGH);
  digitalWrite(LED2, HIGH);
  delay(100);
  digitalWrite(LED1, LOW);  
  digitalWrite(LED2, LOW);
  Serial.println("*******************************************");
  //Serial.println(1023%10);
}

int izpis(int zapisi){
    //razdelimo cifre na array
    for(int i=0; i<N;i++){
      Serial.println(rezultat%10);
      rezultat_izpis[i]=rezultat%10;
      rezultat=rezultat/10;
    }
    //TODO obrnit array:

    for(int i = 0; i<4/2; i++){
        temp = rezultat_izpis[i];
        rezultat_izpis[i] = rezultat_izpis[N-i-1];
        rezultat_izpis[N-i-1] = temp;
    }
    
  //naš array cifer pretvorimo v bitni zapis za izpis na 7-seg displayu
  for(int i=0;i<4;i++){
    Serial.println(rezultat_izpis[i]);
    switch(rezultat_izpis[i]){
      case 0:
      
        for(int g=0+i*8;g<8*(i+1);g++){
          zaslon[g]=stevilke[0][g-i*8];
        }
        break;
      case 1:
        for(int g=0+i*8;g<8*(i+1);g++){
          zaslon[g]=stevilke[1][g-i*8];
        }
        break;
      case 2:
        for(int g=0+i*8;g<8*(i+1);g++){
          zaslon[g]=stevilke[2][g-i*8];
        }
        break;
      case 3:
        for(int g=0+i*8;g<8*(i+1);g++){
          zaslon[g]=stevilke[3][g-i*8];
        }
        break;
      case 4:
        for(int g=0+i*8;g<8*(i+1);g++){
          zaslon[g]=stevilke[4][g-i*8];
        }
        break;
      case 5:
        for(int g=0+i*8;g<8*(i+1);g++){
          zaslon[g]=stevilke[5][g-i*8];
        }
        break;
      case 6:
        for(int g=0+i*8;g<8*(i+1);g++){
          zaslon[g]=stevilke[6][g-i*8];
        }
        break;
      case 7:
        for(int g=0+i*8;g<8*(i+1);g++){
          zaslon[g]=stevilke[7][g-i*8];
        }
        break;
      case 8:
        for(int g=0+i*8;g<8*(i+1);g++){
          zaslon[g]=stevilke[8][g-i*8];
        }
        break;
      case 9:
        for(int g=0+i*8;g<8*(i+1);g++){
          zaslon[g]=stevilke[9][g-i*8];
        }
        break;
    }
    
  }
  zaslon[5]=1;
  //izpis cifer na displayu
      for(int i=0;i<32;i++){
      
        //Serial.print(i);
        //Serial.print(" = ");
        //Serial.println(zaslon[i]);
        if(zaslon[i]==1){digitalWrite(lista[i],HIGH);}
        else{digitalWrite(lista[i],LOW);}
        
    }
    return;  
  }

void loop() {
zadnje_stanje=stanje1;
stanje1=digitalRead(STIKALO);

if(stanje1==1 && zadnje_stanje==0){
  zacetek_igre=millis();
  zamik=random(500,4000);
  Serial.print("zacetek igre: ");
  Serial.println(zacetek_igre);
  Serial.print("zamik: ");
  Serial.println(zamik);
  igra_poteka=1;
  cakam=1;
  digitalWrite(LED1,0);
  digitalWrite(LED2,0);
  for(int i=0;i<=32;i++){
    digitalWrite(lista[i],0);
  }
  digitalWrite(lista[3],1);
  
}



while(igra_poteka==1){
  if(cakam==1){
    delay(zamik);
    zacetek_ledice=millis();
    Serial.print("zacetek merjenja: ");
    Serial.println(zacetek_ledice);
    digitalWrite(STARTLED,1);
    cakam=0;
  } 
    
  if(digitalRead(GUMB2)==1){
    konec=millis();
    Serial.print("konec merjenja: ");
    Serial.println(konec);
    digitalWrite(LED2,1);
    digitalWrite(STARTLED,0);
    Serial.print("konec igre: ");
    rezultat = konec-zacetek_ledice;
    Serial.println(rezultat);
    Serial.println("zmagal levi");


    izpis(rezultat);
    igra_poteka=0;
    
  }
    if(digitalRead(GUMB1)==1){
    konec=millis();
    Serial.print("konec merjenja: ");
    Serial.println(konec);
    digitalWrite(LED1,1);
    digitalWrite(STARTLED,0);
    Serial.print("konec igre: ");
    rezultat = konec-zacetek_ledice;
    Serial.println(rezultat);
    Serial.println("zmagal desni");
    Serial.println(rezultat);

    izpis(rezultat);
    
    igra_poteka=0;
  }
  
}
//Serial.println("cakam");
  
  
  delay(1);
}
