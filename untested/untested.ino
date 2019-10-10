#define motorAs1 12
#define motorAs2 13

#define motorBs1 8
#define motorBs2 9

#define pwmA 11
#define pwmB 10

#define sideSensorA 7
#define sensorLine3 6
#define sensorLine2 5
#define sensorLine1 4
#define sensorLine0 3
#define sideSensorB 2

int pins[] = {
	motorAs1,
	motorAs2,
	motorBs1,
	motorBs2,
	pwmA,
	pwmB,
	sideSensorA,
	sideSensorB,
	sensorLine3,
	sensorLine2,
	sensorLine1,
	sensorLine0,
	sideSensorB
};

int error = 0;
int lastError = 0;
int LFSensor[4];

int speedE1 = 100;
int speedE2 = 130;
int speedE3 = 160;
int speedE0 = 140;

unsigned long startMillis;
unsigned long lapTime = 25000;

int long timeBoostStart, timeBoostEnd;
boolean doBoost = false;

void setup() {
	Serial.begin(9600);

	for(int i = 0; i < 12; i++) {
		if(i == 6) {
			pinMode(pins[i], OUTPUT);
		} else {
			pinMode(pins[i], INPUT);
		}
	}

	digitalWrite(motorAs1, HIGH);
	digitalWrite(motorAs2, LOW);

	digitalWrite(motorBs1, HIGH);
	digitalWrite(motorBs2, LOW);

	delay(5000);
    
    startMillis = millis();

	analogWrite(pwmA, 100);
	analogWrite(pwmB, 100);
}

void loop() {
  if ((millis() - startMillis) >= lapTime) {
    motorsToWork(0, 0, HIGH, HIGH, HIGH, HIGH);
  } 
  else {
  	//(doBoost && (millis() - startMillis) >= timeBoostStart && (millis() - startMillis) <= timeBoostEnd) ? (changeSpeeds()) : (changeSpeeds());
    
//    if(doBoost && (millis() - startMillis) >= timeBoostStart && (millis() - startMillis) <= timeBoostEnd) {
//      changeSpeeds();
//    } else { 
//      //DoNothing
//    } 

    errorVerify(sensorToWork());
  }

	/*João Koritar @gitlab
	@j_koritar on Twitter
	I've studyied and discuss with my group to know if we were going to mantain the bluetooth function, then we've decided to remove it.
	But if you want to use bluetooth, search for an older branch which haves the bluetooth func. 
	*/
}

int sensorToWork() {
	LFSensor[0] = !digitalRead(sensorLine0);
	LFSensor[1] = !digitalRead(sensorLine1);
	LFSensor[2] = !digitalRead(sensorLine2);
	LFSensor[3] = !digitalRead(sensorLine3);

	if((LFSensor[0] == 0) && (LFSensor[1] == 0) && (LFSensor[2] == 0) && (LFSensor[3] == 1)) { error = 3; }
	else if ((LFSensor[0] == 0) && (LFSensor[1] == 0) && (LFSensor[2] == 1) && (LFSensor[3] == 1)) { error = 2; }
	else if ((LFSensor[0] == 0) && (LFSensor[1] == 0) && (LFSensor[2] == 1) && (LFSensor[3] == 0)) { error = 1; }
	else if ((LFSensor[0] == 0) && (LFSensor[1] == 1) && (LFSensor[2] == 1) && (LFSensor[3] == 0)) { error = 0; }
	else if ((LFSensor[0] == 0) && (LFSensor[1] == 1) && (LFSensor[2] == 0) && (LFSensor[3] == 0)) { error = -1; }
	else if ((LFSensor[0] == 1) && (LFSensor[1] == 1) && (LFSensor[2] == 0) && (LFSensor[3] == 0)) { error = -2; }
	else if ((LFSensor[0] == 1) && (LFSensor[1] == 0) && (LFSensor[2] == 0) && (LFSensor[3] == 0)) { error = -3; }
	else { error = lastError; }	

  return(error);
}

void errorVerify(int err) {
	if (err == 3) { motorsToWork(speedE3, speedE3, HIGH, LOW, LOW, HIGH); }
	else if (err == 2) { motorsToWork(speedE2, 0, HIGH, LOW, HIGH, HIGH); }
	else if (err == 1) { motorsToWork(speedE1, speedE1*.5, HIGH, LOW, HIGH, LOW); }
	else if (err == 0) { motorsToWork(speedE0, speedE0, HIGH, LOW, HIGH, LOW); }
	else if (err == -1)	{ motorsToWork(speedE1*.5, speedE1, HIGH, LOW, HIGH, LOW); }
	else if (err == -2) { motorsToWork(0, speedE2, HIGH, HIGH, HIGH, LOW); }
	else if (err == -3) { motorsToWork(speedE3, speedE3, LOW, HIGH, HIGH, LOW); }

	lastError = err;
}

void motorsToWork(int A, int B, int valueA1, int valueA2, int valueB1, int valueB2) {
	digitalWrite(motorAs1, valueA1);
	digitalWrite(motorAs2, valueA2);
	digitalWrite(motorBs1, valueB1);
	digitalWrite(motorBs2, valueB2);

	analogWrite(pwmA, A);
	analogWrite(pwmB, B*1.1);

	//studyVelocity(A, B);
}

void changeSpeeds(int E0 = speedE0, int E1 = speedE1, int E2 = speedE2, int E3 = speedE3) {
	// This function is based on the ideia of get more fast and minus time at laptime, for that I did this function to do like a boost at the car based at
	// we know how many time the car spend to do a complete lap, and at wich point it need to have a boost.

	speedE0 = E0;
	speedE1 = E1;
	speedE2 = E2;
	speedE3 = E3;
}

// ? : ;
//<CONDIÇÃO1> ? <OPERAÇÃO1> : <OPRAÇÃO2>;
//SE-ENTÃO-SENÃO
