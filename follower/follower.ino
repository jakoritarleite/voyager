#define motorAs1 12
#define motorAs2 13

#define motorBs1 8
#define motorBs2 9

#define motorA_pwm 11
#define motorB_pwm 10


#define sideSensorA       7
#define lineFollowSensor3 6
#define lineFollowSensor2 5
#define lineFollowSensor1 4
#define lineFollowSensor0 3
#define sideSensorB       2



  int error = 0;
  int LFSensor[4]={0, 0, 0, 0};


//---------------------------------------------
void setup() 
{
  
  Serial.begin(9600);

  pinMode(motorAs1, OUTPUT);
  pinMode(motorAs2, OUTPUT);
  pinMode(motorBs1, OUTPUT);
  pinMode(motorBs2, OUTPUT);
  pinMode(motorA_pwm, OUTPUT);
  pinMode(motorB_pwm, OUTPUT);

  pinMode(sideSensorA, INPUT);
  pinMode(lineFollowSensor3, INPUT);
  pinMode(lineFollowSensor2, INPUT);
  pinMode(lineFollowSensor1, INPUT);
  pinMode(lineFollowSensor0, INPUT);
  pinMode(sideSensorB, INPUT);
  
  digitalWrite(motorAs1, HIGH);
  digitalWrite(motorAs2, LOW);
  
  digitalWrite(motorBs1, HIGH);
  digitalWrite(motorBs2, LOW);

  delay(5000);

   analogWrite(motorA_pwm, 100);
  analogWrite(motorB_pwm, 100);
  delay(200);
}

void loop() 
{
  
  LFSensor[0] = !digitalRead(lineFollowSensor0);
  LFSensor[1] = !digitalRead(lineFollowSensor1);
  LFSensor[2] = !digitalRead(lineFollowSensor2);
  LFSensor[3] = !digitalRead(lineFollowSensor3);
  
    
   if((LFSensor[0]== 0 )&&(LFSensor[1]== 0 )&&(LFSensor[2]== 0 )&&(LFSensor[3]== 1 )) error = 3;
  
  else if((LFSensor[0]== 0 )&&(LFSensor[1]== 0 )&&(LFSensor[2]== 1 )&&(LFSensor[3]== 1 )) error = 2;
  
  else if((LFSensor[0]== 0 )&&(LFSensor[1]== 0 )&&(LFSensor[2]== 1 )&&(LFSensor[3]== 0 )) error = 1;
  
  else if((LFSensor[0]== 0 )&&(LFSensor[1]== 1 )&&(LFSensor[2]== 1 )&&(LFSensor[3]== 0 )) error = 0;
  
  else if((LFSensor[0]== 0 )&&(LFSensor[1]== 1 )&&(LFSensor[2]== 0 )&&(LFSensor[3]== 0 )) error =- 1;
  
  else if((LFSensor[0]== 1 )&&(LFSensor[1]== 1 )&&(LFSensor[2]== 0 )&&(LFSensor[3]== 0 )) error = -2;
  
  else if((LFSensor[0]== 1 )&&(LFSensor[1]== 0 )&&(LFSensor[2]== 0 )&&(LFSensor[3]== 0 )) error = -3;

  else error = 999;

  if(error == 3){
    digitalWrite(motorAs1, HIGH);
    digitalWrite(motorAs2, LOW);
    
    digitalWrite(motorBs1, LOW);
    digitalWrite(motorBs2, HIGH);
    
    analogWrite(motorA_pwm, 255);
    analogWrite(motorB_pwm, 255);
  }
  else if(error == 2){
    digitalWrite(motorAs1, HIGH);
    digitalWrite(motorAs2, LOW);
    
    digitalWrite(motorBs1, LOW);
    digitalWrite(motorBs2, HIGH);
    
    analogWrite(motorA_pwm, 150);
    analogWrite(motorB_pwm, 150);    
    
  }
  else if(error == 1){
    digitalWrite(motorAs1, HIGH);
    digitalWrite(motorAs2, LOW);
    
    digitalWrite(motorBs1, HIGH);
    digitalWrite(motorBs2, HIGH);
    
    analogWrite(motorA_pwm, 100);
    analogWrite(motorB_pwm, 0);    
  }
  else if(error == 0){
    digitalWrite(motorAs1, HIGH);
    digitalWrite(motorAs2, LOW);
    
    digitalWrite(motorBs1, HIGH);
    digitalWrite(motorBs2, LOW);
    
    analogWrite(motorA_pwm, 80);
    analogWrite(motorB_pwm, 80);    
  }
  else if(error == -1){
    digitalWrite(motorAs1, HIGH);
    digitalWrite(motorAs2, HIGH);
    
    digitalWrite(motorBs1, HIGH);
    digitalWrite(motorBs2, LOW);
    
    analogWrite(motorA_pwm, 0);
    analogWrite(motorB_pwm, 100);    
  }
  else if(error == -2){
    digitalWrite(motorAs1, LOW);
    digitalWrite(motorAs2, HIGH);
    
    digitalWrite(motorBs1, HIGH);
    digitalWrite(motorBs2, LOW);
    
    analogWrite(motorA_pwm, 150);
    analogWrite(motorB_pwm, 150);    
  }
  else if(error == -3){
    digitalWrite(motorAs1, LOW);
    digitalWrite(motorAs2, HIGH);
    
    digitalWrite(motorBs1, HIGH);
    digitalWrite(motorBs2, LOW);
    
    analogWrite(motorA_pwm, 255);
    analogWrite(motorB_pwm, 255);    
  }
  else if(error = 999){
    
    digitalWrite(motorAs1, HIGH);
    digitalWrite(motorAs2, LOW);
    
    digitalWrite(motorBs1, HIGH);
    digitalWrite(motorBs2, LOW);
    
    analogWrite(motorA_pwm, 100);
    analogWrite(motorB_pwm, 100);    
    
  }

}
