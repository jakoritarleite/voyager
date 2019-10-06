#include <SoftwareSerial.h>

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

array pins* = [
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
			] 

int error = 0;
int lastError = NULL;
int LFSensor[4] = NULL;

int speedE1 = 0;
int speedE2 = 0;
int speedE3 = 0;
int speedE0 = 0;

const int pinRX = 0;
const int pinTX = 1;

String dataBluetooth = "";

SoftwareSerial Bluetooth(pinRX, pinTX);

void setup() {
	Serial.begin(9600);
	Bluetooth.begin(9600);

	for(int i = 0; i < 12; i++) {
		if(i == 6) {
			pinMode(pins[i], INPUT);
		} else {
			pinMode(pins[i], OUTPUT);
		}
	}
	delete [] pins; 
	pins = NULL;

	digitalWrite(motorAs1, HIGH);
	digitalWrite(motorAs2, LOW);

	digitalWrite(motorBs1, HIGH);
	digitalWrite(motorBs2, LOW);

	delay(5000);

	analogWrite(pwmA, 100);
	analogWrite(pwmB, 100);
}

void loop() {
	int sensorsError = sensorToWork();
	errorVerify(sensorsError);
	//sendErrorByBluetooth(sensorsError); 

	/*João Koritar @gitlab
	@j_koritar on Twitter
	I am studying to know how to get it more optimezed.
	Bcause at this way of void loop is working, it need to stop the code and verify if has any bluetooth available and after send data. And it enter in a while loop on sendErrorByBluetooth which is deactivated.
	I get at the point of thiniking about to start the sensorErrorByBluetooth function first then inside this function call the sensorToWork function and after call the errorVerify*()  
	*/

}

void sensorToWork() {
	LFSensor[0] = !digitalRead(sensorLine0);
	LFSensor[1] = !digitalRead(sensorLine1);
	LFSensor[2] = !digitalRead(sensorLine2);
	LFSensor[3] = !digitalRead(sensorLine3);

	if((LFSensor[0] == 0) && (LFSensor[1] == 0) && (LFSensor[2] == 0) && (LFSensor[3] == 1)) { error = 3 }
	else if ((LFSensor[0] == 0) && (LFSensor[1] == 0) && (LFSensor[2] == 1) && (LFSensor[3] == 1)) { error = 2 }
	else if ((LFSensor[0] == 0) && (LFSensor[1] == 0) && (LFSensor[2] == 1) && (LFSensor[3] == 0)) { error = 1 }
	else if ((LFSensor[0] == 0) && (LFSensor[1] == 1) && (LFSensor[2] == 1) && (LFSensor[3] == 0)) { error = 0 }
	else if ((LFSensor[0] == 0) && (LFSensor[1] == 1) && (LFSensor[2] == 0) && (LFSensor[3] == 0)) { error = -1 }
	else if ((LFSensor[0] == 1) && (LFSensor[1] == 1) && (LFSensor[2] == 0) && (LFSensor[3] == 0)) { error = -2 }
	else if ((LFSensor[0] == 1) && (LFSensor[1] == 0) && (LFSensor[2] == 0) && (LFSensor[3] == 0)) { error = -3 }
	else { error = lastError }	

	return(error);

}

void errorVerify(int err) {
	if (err == 3) { motorsToWork(speedE3, speedE3, HIGH, LOW, HIGH, LOW) }
	else if (err == 2) { motorsToWork(speedE2, speedE2, HIGH, LOW, HIGH, HIGH) }]
	else if (err == 1) { motorsToWork(speedE1, 0, HIGH, LOW, HIGH, HIGH) }
	else if (err == 0) { motorsToWork(speedE0, speedE0, HIGH, LOW, HIGH, LOW) }
	else if (err == -1)	{ motorsToWork(0, speedE1, HIGH, HIGH, HIGH, LOW) }
	else if (err == -2) { motorsToWork(speedE2, speedE2, HIGH, HIGH, HIGH LOW) }
	else if (err == -3) { motorsToWork(speedE3, speedE3, LOW, HIGH, HIGH, LOW) }

	lastError = err;
}

void motorsToWork(int A, int B, int valueA1, int valueA2, int valueB1, int valueB2) {
	digitalWrite(motorAs1, valueA1);
	digitalWrite(motorAs2, valueA2);
	digitalWrite(motorBs1, valueB1);
	digitalWrite(motorBs2, valueB2);

	analogWrite(pwmA, A);
	analogWrite(pwmB, B);
}

void sendErrorByBluetooth(int err) {
	/*while (Bluetooth.available()) {
		//char tmpData = Bluetooth.read();
		//dataBluetooth += tmpData;

		Bluetooth.println("Error: " + err);
	}*/
	Bluetooth.println("Error: " + err); //It's to have certain that bth is sending the data

	/*if (dataBluetooth.length() > 0) {
		Serial.println(dataBluetooth);
	}*/
	dataBluetooth = "";
}