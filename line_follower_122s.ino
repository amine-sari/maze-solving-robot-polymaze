//motor pins
int IND1 = 5;
int IND2 = 6;
int ING1 = 2;
int ING2 = 3;
int MD = 9;
int MG = 10;

//IR sensors pins
int IRuprightPin = A2;
int IRupleftPin = A1;
int IRfarrightPin =A4;
int IRfarleftPin= A3 ;
int IRCenterPin = A0;

//IR shit:
int IRupright ;
int IRupleft ;
int IRfarright ;
int IRfarleft ;
int IRCenter ;
 
bool upRightState ;
bool upLeftState ;
bool farRightState ;
bool farLeftState ;
bool CenterState ; 

int seuil = 150;

//motor speed
int speedInint = 80;
int speedD = 100 ;
int speedG = 100 ;
int regul = 5;

//functions:
void straight();
int MinMaxMt(int);
void uTurn();
void leftTurn();
void rightTurn();
void Stop();
void Priority();





void setup() {
  // put your setup code here, to run once:
  pinMode(IND1 , OUTPUT);
  pinMode(IND2 , OUTPUT);
  pinMode(ING1 , OUTPUT);
  pinMode(ING2 , OUTPUT);
  pinMode(MD , OUTPUT);
  pinMode(MG , OUTPUT);
  Serial.begin(9600);


  

}

void loop() {
  // IR input :
  IRupright = analogRead(IRuprightPin);
  IRupleft = analogRead(IRupleftPin);
  IRfarright = analogRead(IRfarrightPin);
  IRfarleft = analogRead(IRfarleftPin);
  IRCenter = analogRead(IRCenterPin);
 
  upRightState = IRupright > seuil;
  upLeftState = IRupleft > seuil;
  farRightState = IRfarright > seuil;
  farLeftState = IRfarleft > seuil;
  CenterState = IRCenter > seuil;

  Priority();

  
  Serial.println(String(IRfarleft)+' '+String(IRupleft)+' '+String(IRCenter)+' '+String(IRupright)+' '+String(IRfarright));
}
  







//functions :
void Priority(){
  if( farLeftState ){

    Stop();
    delay(100);
    leftTurn();
    
  }
  else if(CenterState || upRightState || upLeftState){
    
    straight();
    
  }
  else if(farRightState){

    Stop();
    delay(100);
    rightTurn();
  }
  else{
    Stop();
    delay(1000);
    //uTurn();

  }
}


void straight()
{
  if (!CenterState && upRightState && !upLeftState)
  {
    Serial.print("G ");
      speedG += regul;
      speedD -= regul;
      
  }
  else if ( !CenterState && !upRightState && upLeftState){
      Serial.print("D ");
      speedD += regul;
      speedG -= regul;
      
  }
  
  else if( !CenterState && !upRightState && !upLeftState) {
    delay(100);
    speedG = 0;
    speedD = 0;   
  }
  else {
    speedD = speedInint;
    speedG = speedInint;
  }

  
  speedD = MinMaxMt(speedD);
  speedG = MinMaxMt(speedG);
  digitalWrite(IND1, HIGH );
  digitalWrite(IND2, LOW );
  digitalWrite(ING1, HIGH );
  digitalWrite(ING2, LOW );

  analogWrite(MD, speedD);
  analogWrite(MG, speedG);
}

void uTurn(){
  
  
 digitalWrite(IND1, HIGH );
  digitalWrite(IND2, LOW );
  digitalWrite(ING1, LOW );
  digitalWrite(ING2, HIGH );

  analogWrite(MD, 80);
  analogWrite(MG, 80); 
  delay(420); 
  analogWrite(MD, 0);
  analogWrite(MG, 0); 
  delay(200);
  
}
void rightTurn(){

  digitalWrite(ING1, HIGH );
  digitalWrite(ING2, LOW );
  digitalWrite(IND1, HIGH );
  digitalWrite(IND2, LOW );
  
  analogWrite(MG, 150);
  analogWrite(MD, 0);
  delay(250); 
  analogWrite(MG, 0); 
  analogWrite(MD, 0); 
  delay(200);
}
void leftTurn(){
  digitalWrite(ING1, HIGH );
  digitalWrite(ING2, LOW );
  digitalWrite(IND1, HIGH );
  digitalWrite(IND2, LOW );
  
  analogWrite(MG, 0);
  analogWrite(MD, 150);

  delay(250); 
  analogWrite(MG, 0); 
  analogWrite(MD, 0); 
  delay(200);

}
void Stop(){
  analogWrite(MG, 0);
  analogWrite(MD, 0);
}






int MinMaxMt(int X)
{
  int max = speedInint;
  int min = 0;
  if (X > max){
    X = max;
  }else if (X < min){
    X = min;
  }
  return X;
}




