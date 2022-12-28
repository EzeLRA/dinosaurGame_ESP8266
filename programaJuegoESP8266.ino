#include <Wire.h>
#include <SPI.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>

#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978

//Botones
//esp8266
#define Boton1 10   //Izquierdo
#define Boton2 9    //Derecho
//arduino mega
//#define Boton1 5   //Izquierdo
//#define Boton2 4    //Derecho

//Buzzer
//esp8266
#define buzzer 15
//arduino mega
//#define buzzer 9

//Configuracion de Pantalla
#define ANCHO_PANTALLA 128
#define LARGO_PANTALLA 64
Adafruit_SSD1306 display(ANCHO_PANTALLA,LARGO_PANTALLA,&Wire,-1);



//Configuracion del juego
bool INICIO=false;
bool ARRANQUE=false;
int x,y;

int static Retardo=50;
int Velocidad=4;
int Frame;
int static ImpulsoS=12;
bool Salto=false;
int posicion=28;
int pos1,pos2,pos3,pos4;
int static Gravedad=5;

//Figuras
int obstaculo1[20][15]={
{0,0,0,0,0,0,1,1,0,0,0,0,0,0},
{0,0,0,0,0,1,1,1,1,0,0,0,0,0},
{0,0,0,0,0,1,1,1,1,0,0,0,0,0},
{0,0,0,0,0,1,1,1,1,0,0,0,0,0},
{0,0,0,0,0,1,1,1,1,0,0,0,1,0},
{0,0,0,0,0,1,1,1,1,0,0,1,1,1},
{0,0,0,0,0,1,1,1,1,0,0,1,1,1},
{0,0,0,0,0,1,1,1,1,0,0,1,1,1},
{0,1,0,0,0,1,1,1,1,0,0,1,1,1},
{1,1,1,0,0,1,1,1,1,1,1,1,1,1},
{1,1,1,0,0,1,1,1,1,1,1,1,1,0},
{1,1,1,0,0,1,1,1,1,1,1,1,0,0},
{1,1,1,0,0,1,1,1,1,0,0,0,0,0},
{1,1,1,1,1,1,1,1,1,0,0,0,0,0},
{0,1,1,1,1,1,1,1,1,0,0,0,0,0},
{0,0,1,1,1,1,1,1,1,0,0,0,0,0},
{0,0,0,0,0,1,1,1,1,0,0,0,0,0},
{0,0,0,0,0,1,1,1,1,0,0,0,0,0},
{0,0,0,0,0,1,1,1,1,0,0,0,0,0},
{0,0,0,0,0,1,1,1,1,0,0,0,0,0}
};

int cuerpo[22][20]={
{0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,0},
{0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1},
{0,0,0,0,0,0,0,0,0,0,1,1,0,1,1,1,1,1,1,1},
{0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1},
{0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1},
{0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1},
{0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,0,0},
{1,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0},
{1,0,0,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0},
{1,1,0,0,0,0,1,1,1,1,1,1,1,1,1,1,0,0,0,0},
{1,1,1,0,0,1,1,1,1,1,1,1,1,1,0,1,0,0,0,0},
{1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0},
{1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0},
{0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0},
{0,0,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0},
{0,0,0,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0},
{0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,1,1,1,0,1,1,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,1,1,0,0,0,1,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,1,1,0,0,0,1,1,0,0,0,0,0,0,0,0}
};

int cuerpo1[22][20]={
{0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,0},
{0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1},
{0,0,0,0,0,0,0,0,0,0,1,1,0,1,1,1,1,1,1,1},
{0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1},
{0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1},
{0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1},
{0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,0,0},
{1,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0},
{1,0,0,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0},
{1,1,0,0,0,0,1,1,1,1,1,1,1,1,1,1,0,0,0,0},
{1,1,1,0,0,1,1,1,1,1,1,1,1,1,0,1,0,0,0,0},
{1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0},
{1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0},
{0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0},
{0,0,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0},
{0,0,0,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0},
{0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,1,1,1,0,0,1,1,1,0,0,0,0,0,0,0},
{0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0}
};

int cuerpo2[22][20]={
{0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,0},
{0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1},
{0,0,0,0,0,0,0,0,0,0,1,1,0,1,1,1,1,1,1,1},
{0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1},
{0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1},
{0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1},
{0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,0,0},
{1,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0},
{1,0,0,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0},
{1,1,0,0,0,0,1,1,1,1,1,1,1,1,1,1,0,0,0,0},
{1,1,1,0,0,1,1,1,1,1,1,1,1,1,0,1,0,0,0,0},
{1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0},
{1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0},
{0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0},
{0,0,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0},
{0,0,0,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0},
{0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,1,1,0,0,1,1,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,1,1,0,0,1,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0}
};


bool Colisiones(int a,int b,int c,int d){

int Cactus[12][2]={
{c,d+8},
{c+3,d+8},
{c+3,d+13},
{c+5,d+13},
{c+5,d},
{c+9,d},
{c+9,d+9},
{c+11,d+9},
{c+11,d+4},
{c+14,d+4},
{c+14,d+12},
{c,y+16}
};

int Dinosaurio1[52][2]={
{a+10,b},
{a+20,b},
{a+20,b+6},
{a+18,b+6},
{a+18,b+8},
{a+16,b+8},
{a+16,b+12},
{a+14,b+12},
{a+14,b+14},
{a+13,b+14},
{a+13,b+19},
{a+9,b+19},
{a+9,b+22},
{a+6,b+22},
{a+6,b+18},
{a+4,b+18},
{a+4,b+16},
{a+2,b+16},
{a+2,b+14},
{a,b+14},
{a,b+7},
{a+1,b+7},
{a+1,b+9},
{a+9,b+9},
{a+9,b+6},
{a+10,b+6}
};

int Dinosaurio2[52][2]={
{a+10,b},
{a+20,b},
{a+20,b+6},
{a+18,b+6},
{a+18,b+8},
{a+16,b+8},
{a+16,b+12},
{a+14,b+12},
{a+14,b+14},
{a+13,b+14},
{a+13,b+22},
{a+9,b+22},
{a+9,b+19},
{a+6,b+19},
{a+6,b+18},
{a+4,b+18},
{a+4,b+16},
{a+2,b+16},
{a+2,b+14},
{a,b+14},
{a,b+7},
{a+1,b+7},
{a+1,b+9},
{a+9,b+9},
{a+9,b+6},
{a+10,b+6}
};

for(int i=0;i<52;i++){
  for(int I=1;I<12;I++){
    if(Dinosaurio1[i][0] >= Cactus[I][0] && Dinosaurio1[i][0] <= Cactus[I][0]){
      if(Dinosaurio1[i][1] >= Cactus[I][1] && Dinosaurio1[i][1] == Cactus[I][1]){
      return true;
      }
    }
  }
}
      return false;
}

void nubes(int x,int y){
  display.drawPixel(x,y+2,WHITE);
  display.drawLine(x+1,y+1,x+2,y+1,WHITE);
  display.drawLine(x+3,y,x+5,y,WHITE);
  display.drawPixel(x+6,y+1,WHITE);
  display.drawLine(x+7,y,x+10,y,WHITE);
  display.drawLine(x+10,y+1,x+11,y+1,WHITE);
  display.drawLine(x+4,y+2,x+12,y+2,WHITE);
}

void ObstaculosEstaticos(int x,int y){
  for(int b=0;b<20;b++){
  for(int i=0;i<15;i++){
  if(obstaculo1[b][i]==1){
  display.drawPixel(x+i,y+b,WHITE);
  }
 }
}
}

void Dinosaurio(int x,int y){
  if(ARRANQUE==false){
  for(int b=0;b<22;b++){
  for(int i=0;i<20;i++){
  if(cuerpo[b][i]==1){
  display.drawPixel(x+i,y+b,WHITE);
  }
 }
}
}

  if(ARRANQUE==true && Frame==1){
  for(int b=0;b<22;b++){
  for(int i=0;i<20;i++){
  if(cuerpo1[b][i]==1){
  display.drawPixel(x+i,y+b,WHITE);
   }
  }
 }
}
  
  if(ARRANQUE==true && Frame==2){
  for(int b=0;b<22;b++){
  for(int i=0;i<20;i++){
  if(cuerpo2[b][i]==1){
  display.drawPixel(x+i,y+b,WHITE);
   }
  }
 }
}
  
}

void suelo(int x,int y){
  display.drawLine(0,50,128,50,WHITE);
  
  for(int i=0;i<256;i+=32){
  display.drawLine(x+i,y+7,x+4+i,y+7,WHITE);
  display.drawLine(x+10+i,y+5,x+13+i,y+5,WHITE);
  display.drawLine(x+16+i,y+7,x+18+i,y+7,WHITE);
  display.drawLine(x+25+i,y+5,x+26+i,y+5,WHITE);
  }
  
  }
 


void terreno(){
  display.clearDisplay();

  //Instruccion de saltar
  if(digitalRead(Boton2)==0 && Salto==false && posicion==28){
    Salto=true;
  }
  //Mecanismo de salto
  if(posicion>-5 && Salto==true){
    posicion-=ImpulsoS;
  }
  if(posicion==-5 && Salto==true){
    Salto=false;
  }

  //Mecanismo de gravedad
  if(posicion<28){
    posicion+=Gravedad;
  }
  if(posicion>28){
    posicion=28;
  }

  //Animacion de Arranque
  x-=Velocidad;
  pos1-=Velocidad;

  pos3-=Velocidad-2;
  pos4-=Velocidad-2;
  
  suelo(x,y+50);
  ObstaculosEstaticos(pos1,y+30);

  nubes(pos3,y+10);
  nubes(pos4,y+10);
  
  if(x<-128){
  x+=128;
  }
  
  if(pos1<-80){
  pos1=random(150,160);
  }

  if(pos3<-30){
  pos3=130;
  }
  if(pos4<-30){
  pos4=130;
  }
  
  Dinosaurio(10,posicion);

  while(Colisiones(10,posicion,pos1,y+30)==true){
    INICIO=false;
    ARRANQUE=false;

    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(36,10);
    display.println("Has perdido");
    display.setCursor(36,20);
    display.println("Continuar?");
    display.display();
    
    if(digitalRead(Boton1)==0 || digitalRead(Boton2)==0){
    INICIO=true;
    ARRANQUE=true;
    break;
  }
 }
  
  display.display();
  delay(Retardo);
  
  if(Frame==1){
    Frame++;
  }
  
  display.clearDisplay();
  x-=Velocidad;
  pos1-=Velocidad;

  pos3-=Velocidad-2;
  pos4-=Velocidad-2;
  
  suelo(x,y+50);
  ObstaculosEstaticos(pos1,y+30);

  nubes(pos3,y+10);
  nubes(pos4,y+10);
  
  if(x<-128){
  x+=128;
  }

  if(pos1<-80){
  pos1=random(150,160);
  }

  if(pos3<-30){
  pos3=130;
  }
  if(pos4<-30){
  pos4=130;
  }
  
  Dinosaurio(10,posicion);

  while(Colisiones(10,posicion,pos1,y+30)==true){
    INICIO=false;
    ARRANQUE=false;

    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(36,10);
    display.println("Has perdido");
    display.setCursor(36,20);
    display.println("Continuar?");
    display.display();
    
    if(digitalRead(Boton1)==0 || digitalRead(Boton2)==0){
    INICIO=true;
    ARRANQUE=true;
    break;
  }
 }
  
  display.display();
  delay(Retardo);
  if(Frame==2){
    Frame--;
  }
}


void interfaz(){
  while(INICIO==false){
  //Titulo
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(36,10);
  display.println("Dinosaurio");
  display.setCursor(44,30);
  display.println("Iniciar");
  Dinosaurio(x+10,y+28);
  //Superficie
  suelo(x,y+50);
  nubes(pos3,y+10);
  nubes(pos4,y+10);
  
  if(digitalRead(Boton1)==0 || digitalRead(Boton2)==0){
    INICIO=true;
    ARRANQUE=true;
  }
  display.display();
  }

  //Arranque del juego
  while(ARRANQUE==true){
  terreno();
  }
}

void setup() {
  pinMode(Boton1,INPUT_PULLUP);
  pinMode(Boton2,INPUT_PULLUP);
  Serial.begin(115200);
  if(!display.begin(SSD1306_SWITCHCAPVCC,0x3c)){
    Serial.println("No se encontro la pantalla");
    for(;;);
  }
  display.clearDisplay();
  INICIO=false;
  Frame=1;
  pos1=random(150,160);
  pos3=10;
  pos4=110;
}

void loop() {
  interfaz(); 
}
