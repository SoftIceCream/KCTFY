/*
 Name:		KCTF.ino
 Created:	2017-10-13 오후 9:28:44
 Author:	Joosung Park
*/

#define LED 13	//LED핀
#define IR 2	//IR센서 핀
#define LIMIT (POINTNUM * 1)		//LIMIT설정
#define POINTNUM 4		//한 판에 표시 개수

// the setup function runs once when you press reset or power the board

volatile unsigned int count = 0;	//인터럽트에서 사용하기 위해 volatile 붙임
unsigned int oldcount = 0, newcount = 0;
long int sameCount = 0;	//같은지 여부 검사(변함이 없으면 0.2초마다 1씩 증가, 5번 실행되면,즉 1초 후 초기화)
bool isOver = false;

void irCount() {
	count += 1;
}

void setup() {
	pinMode(LED, OUTPUT);	//LED핀 출력
	pinMode(IR, INPUT);	//IR센서 입력
	attachInterrupt(digitalPinToInterrupt(IR), irCount, RISING);	//인터럽트 활성화, LOW에서 HIGH로 올라갈 때 인터럽트 활성화
}

// the loop function runs over and over again until power down or reset
void loop() {
	oldcount = count;
	delay(200);
	newcount = count;

	if (oldcount==newcount)
	{
		sameCount++;
		if (sameCount>=5)
		{
			count = 0;	//1초동안 변함이 없으면 초기화
		}
	}

	if ((oldcount+LIMIT) >= newcount)
	{
		isOver = true;
	}
	else
	{
		isOver = false;
	}

	if (isOver==true)
	{
		digitalWrite(LED, HIGH);

	}
}
