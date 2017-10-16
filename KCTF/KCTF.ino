/*
 Name:		KCTF.ino
 Created:	2017-10-13 오후 9:28:44
 Author:	Joosung Park
*/

#define LED 4	//LED핀
#define IR 2	//IR센서 핀
#define LIMIT 2		//LIMIT설정
#define BUZZ 5	//버저 핀

// the setup function runs once when you press reset or power the board

volatile unsigned int count = 0;	//인터럽트에서 사용하기 위해 volatile 붙임
unsigned long int oldcount = 0, newcount = 0;
bool isOver = false;

unsigned long previousMillis = 0, loopPMillis = 0, unlPMillis = 0;
const long interval = 100, loopInterval = 200, unlockInterval = 1000;

void irCount() {
	unsigned long currentMillis = millis();
	if (currentMillis - previousMillis >= interval) {
		previousMillis = currentMillis;
		count += 1;
	}
}

void setup() {
	pinMode(LED, OUTPUT);	//LED핀 출력
	pinMode(IR, INPUT);	//IR센서 입력
	attachInterrupt(0, irCount, RISING);
	Serial.begin(115200);
}

// the loop function runs over and over again until power down or reset
void loop() {
	
	oldcount = count;
	unsigned long currentMillis = millis();

	if (currentMillis - loopPMillis >= loopInterval) {
		loopPMillis = currentMillis;
		
		newcount = count;
	}

	currentMillis = millis();

	if (currentMillis - unlPMillis >= unlockInterval)
	{
		unlPMillis = currentMillis;
		count = 0;
		isOver = false;
		Serial.println("It's OK!!");
	}

	if ((oldcount+LIMIT) < newcount)
	{
		isOver = true;
	}

	if (isOver==true)
	{
		Serial.println("It's OVER!!");
		tone(BUZZ, 440, 200);
		digitalWrite(LED, HIGH);
		delay(100);
	}else{
		digitalWrite(LED, LOW);
	}
}
