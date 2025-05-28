#include <Arduino.h>
// define the pins
#define EN1_PIN    4 //enable 
#define STEP1_PIN  3 //step
#define DIR1_PIN   2 //direction

#define EN2_PIN    7 //enable 
#define STEP2_PIN  6 //step
#define DIR2_PIN   5 //direction

#define EN3_PIN    10 //enable 
#define STEP3_PIN  9 //step
#define DIR3_PIN   8 //direction

#define VERTICAL_PIN 12

int FULL_ROTATE = 9276; //Полный оборот площадки
int DEGREE_60 = 1546; //Поворот площадки на 60 градусов
int MILLIMETER = 200; //Количество шагов на миллиметр вертикальной оси

int FULL = 250; //Шагов для полного выдавливания шприца
int HALF = 125; //Половина выдавливания шприца

int SPEED = 700;  //Скорость моторов

bool STOP = true; //Переменная безопаности. При значении true и срабатывании концевика мотор отключается

void rotateMotor1(int steps, bool direction, int speed) {    //steps - колчество шагов, direction - направление движения, speed - задержка между шагами
  // Установить направление мотора
  digitalWrite(DIR1_PIN, direction);
  
  // Шаги мотора
  for (int i = 0; i < steps; i++) {
    digitalWrite(STEP1_PIN, HIGH);
    delayMicroseconds(speed);
    digitalWrite(STEP1_PIN, LOW);
    delayMicroseconds(speed);
  }
}

void rotateMotor2(int steps, bool direction, int speed) {    //steps - колчество шагов, direction - направление движения, speed - задержка между шагами
  // Установить направление мотора
  digitalWrite(DIR2_PIN, direction);
  
  // Шаги мотора
  for (int i = 0; i < steps; i++) {
    digitalWrite(STEP2_PIN, HIGH);
    delayMicroseconds(speed);
    digitalWrite(STEP2_PIN, LOW);
    delayMicroseconds(speed);
    if (digitalRead(VERTICAL_PIN) == 0 && STOP == true) {
      break;
    }
  }
}

void rotateMotor3(int steps, bool direction, int speed) {    //steps - колчество шагов, direction - направление движения, speed - задержка между шагами
  // Установить направление мотора
  digitalWrite(DIR3_PIN, direction);
  
  // Шаги мотора
  for (int i = 0; i < steps; i++) {
    digitalWrite(STEP3_PIN, HIGH);
    delayMicroseconds(speed);
    digitalWrite(STEP3_PIN, LOW);
    delayMicroseconds(speed);
  }
}

void initialization(){
  rotateMotor2(25000,1,500); // Опускаем до концевика
  STOP = false;
  rotateMotor2(115 * MILLIMETER,0,500); //Поднимаем в рабочее положение
  STOP = true;
}

void extrude(int mil){
  rotateMotor2(20 * MILLIMETER,1,600); //Шриц вниз
  delay(500);
  rotateMotor3(mil, 1, 1000); //Надавить
  delay(1000);
  rotateMotor3(mil, 0, 1000); //Отжать
  delay(500);
  rotateMotor2(20 * MILLIMETER,0,600);  //Уехать наверх
}

void setup() 
{
  //Установка режима работы пинов gpio
  pinMode(EN1_PIN, OUTPUT); // set the EN_PIN as an output
  digitalWrite(EN1_PIN, HIGH); // deactivate driver (LOW active)
  pinMode(DIR1_PIN, OUTPUT); // set the DIR_PIN as an output
  digitalWrite(DIR1_PIN, LOW); // set the direction pin to low
  pinMode(STEP1_PIN, OUTPUT); // set the STEP_PIN as an output
  digitalWrite(STEP1_PIN, LOW); // set the step pin to low

  digitalWrite(EN1_PIN, LOW); // activate driver

  pinMode(EN2_PIN, OUTPUT); // set the EN_PIN as an output
  digitalWrite(EN2_PIN, HIGH); // deactivate driver (LOW active)
  pinMode(DIR2_PIN, OUTPUT); // set the DIR_PIN as an output
  digitalWrite(DIR2_PIN, LOW); // set the direction pin to low
  pinMode(STEP2_PIN, OUTPUT); // set the STEP_PIN as an output
  digitalWrite(STEP2_PIN, LOW); // set the step pin to low

  digitalWrite(EN2_PIN, LOW); // activate driver

  pinMode(EN3_PIN, OUTPUT); // set the EN_PIN as an output
  digitalWrite(EN3_PIN, HIGH); // deactivate driver (LOW active)
  pinMode(DIR3_PIN, OUTPUT); // set the DIR_PIN as an output
  digitalWrite(DIR3_PIN, LOW); // set the direction pin to low
  pinMode(STEP3_PIN, OUTPUT); // set the STEP_PIN as an output
  digitalWrite(STEP3_PIN, LOW); // set the step pin to low

  digitalWrite(EN3_PIN, LOW); // activate driver

  pinMode(VERTICAL_PIN, INPUT);

  initialization(); //Вызов функции инициализации
}


void loop()
{

  delay(500);
  extrude(FULL);
  delay(500);
  rotateMotor1(DEGREE_60, 0, SPEED);  //Поворот стола на 60 градусов
  delay(500);
  extrude(HALF);
  delay(500);
  rotateMotor1(DEGREE_60, 0, SPEED);  //Поворот стола на 60 градусов
  delay(500);
  extrude(FULL);
  delay(500);
  rotateMotor1(2 * DEGREE_60, 1, SPEED); //Вернуться к лабораторной колбе
  delay(500);
  extrude(FULL);
  delay(500);
  rotateMotor1(DEGREE_60, 1, SPEED);  //Поворот стола на 60 градусов
  delay(500);
  extrude(HALF);
  delay(500);
  rotateMotor1(DEGREE_60, 1, SPEED);  //Поворот стола на 60 градусов
  delay(500);
  extrude(HALF);
  delay(500);
  rotateMotor1(2 * DEGREE_60, 0, SPEED); //Вернуться к лабораторной колбе
  delay(500);
  extrude(HALF);
  delay(500);
  rotateMotor1(3 * DEGREE_60, 1, SPEED);  //Поворот стола на 180 градусов
  delay(500);
  extrude(FULL);
  delay(500);
  rotateMotor1(3 * DEGREE_60, 0, SPEED); //Вернуться к лабораторной колбе
  delay(60000);

}