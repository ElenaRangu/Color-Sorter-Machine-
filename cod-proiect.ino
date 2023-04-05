#include <Servo.h>
Servo pickServo;
Servo dropServo;


// definire pini. Senzorul de culoare TCS230 poate funcționa fără bibliotecă, deoarece este nevoie doar de citirea frecvenței de la pinul senzorului
 pentru a decide  culoarea.
 
#define S0 4 
#define S1 5
#define S2 7
#define S3 6
#define sensorOut 8    
int frequency = 0;
int color=0;


int detectColor() {
  // activare culoare rosu. Scrierea în S2 și S3 (LOW, LOW) activează fotodiodele roșii pentru a lua citirile pentru densitatea culorii roșii.
  digitalWrite(S2, LOW);
  digitalWrite(S3, LOW);
  frequency = pulseIn(sensorOut, LOW);
  int R = frequency;
  Serial.print("Red = ");
  Serial.print(frequency);//printeaza frecventa culorii rosu
  Serial.print("   ");
  delay(50);
  

   // activare culoare albastra. Scrierea în S2 și S3 (LOW, LOW) activează fotodiodele albastre pentru a lua citirile pentru densitatea culorii albastru
  digitalWrite(S2, LOW);
  digitalWrite(S3, HIGH);
  frequency = pulseIn(sensorOut, LOW);
  int B = frequency;
  Serial.print("Blue = ");
  Serial.print(frequency);
  Serial.println("   ");
  
  // activare culoare verde
  digitalWrite(S2, HIGH);
  digitalWrite(S3, HIGH);
  // Reading the output frequency
  frequency = pulseIn(sensorOut, LOW);
  int G = frequency;
  Serial.print("Green = ");
  Serial.print(frequency);
  Serial.print("   ");
  delay(50);

  delay(50);

  if(R<22 & R>20 & G<29 & G>27){
    color = 1; // Red
    Serial.print("Detected Color is = ");
    Serial.println("RED");
  }
  if(G<25 & G>22 & B<22 &B>19){
    color = 2; // Orange
      Serial.println("Orange  ");
  }
  if(R<21 & R>20 & G<28 & G>25){
    color = 3; // Green
      Serial.print("Detected Color is = ");
    Serial.println("GREEN");
  }
  if(R<38 & R>24 & G<44 & G>30){
    color = 4; // Yellow
       Serial.print("Detected Color is = ");
    Serial.println("YELLOW");
  }
  if (G<29 & G>27 & B<22 &B>19){
    color = 5; // Blue
     Serial.print("Detected Color is = ");
    Serial.println("BLUE");
  }
  return color;  // returneaza culoarea
}


void setup() {
  pinMode(S0, OUTPUT);   //pinii selectati ca iesire/Pinul OUT va oferi frecvență.
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(sensorOut, INPUT);
  //frecventa de 20%
  digitalWrite(S0, LOW);
  digitalWrite(S1, HIGH);  //



  pickServo.attach(9); 
  dropServo.attach(10); //Servomotorele sunt conectate la pinii 9 și 10 din Arduino. Servo-ul de preluare care va prelua bilele de 
culoare este conectat la pinul 9 și servo-ul care va arunca bilele de culoare
 în funcție de culoare este conectat la pinul 10

  Serial.begin(9600);
}

void loop() {
  //pozitie initiala servo motor
  pickServo.write(115);
  delay(600);
  
  for(int i = 115; i > 65; i--) { //intial servomotorul este setat in pozitia lui initiala 
    pickServo.write(i);
    delay(2);
  }
  delay(500);
  // citeste variabilele in functie de culoare si este chemata functia
  color = detectColor();
  delay(1000);  



  switch (color) { //În funcție de culoarea detectată, servomotorul de mișcare se mișcă cu un unghi special și lasă bila de culoare în caseta respectivă.
    case 1:
    dropServo.write(50); // citește culoarea și dă frecvența in pinul Out
    break;

    case 2:
    dropServo.write(80);
    break;

    case 3:
    dropServo.write(110);
    break;

    case 4:
    dropServo.write(140);
    break;

    case 5:
    dropServo.write(170);
    break;
    
    case 0:
    break;
  }
  delay(500);
  
  for(int i = 65; i > 29; i--) {   //Inițial, servomotorul pick este setat în poziția inițială. Motorul se deplasează după o anumită întârziere
 în regiunea detectorului și așteaptă detectarea.
 
    pickServo.write(i);
    delay(2);
  } 
  delay(300);
  
  for(int i = 29; i < 115; i++) {
    pickServo.write(i);
    delay(2);
  }
  color=0;
}
