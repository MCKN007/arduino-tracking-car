#include <Servo.h>

// 定义电机引脚
#define AIN1 6          // TB6612 AIN1连接到Arduino引脚6
#define AIN2 7          // TB6612 AIN2连接到Arduino引脚7
#define BIN1 4          // TB6612 BIN1连接到Arduino引脚4
#define BIN2 5          // TB6612 BIN2连接到Arduino引脚5
#define PWMA 9          // TB6612 PWMA连接到Arduino引脚9
#define PWMB 10         // TB6612 PWMB连接到Arduino引脚10
#define STBY 3          // TB6612 STBY连接到Arduino引脚3

// 定义传感器引脚
#define sensorLeft 1    // 左侧红外传感器连接到Arduino引脚1
#define sensorMiddle 8  // 中间红外传感器连接到Arduino引脚8
#define sensorRight 2   // 右侧红外传感器连接到Arduino引脚2

// 定义LED引脚
#define ledPin1 11      // LED1引脚连接到Arduino引脚11
#define ledPin2 12      // LED2引脚连接到Arduino引脚12

// 定义舵机引脚
#define servoPin 13     // 舵机引脚连接到Arduino引脚13

// 定义运动状态
#define STOP        0   // 停止
#define FORWARD     1   // 前进
#define TURNLEFT    2   // 左转
#define TURNRIGHT   3   // 右转
#define SWAYLEFT    4   // 左摇摆
#define SWAYRIGHT   5   // 右摇摆

int sensorData[3];      // 用来接受三个传感器状态
int forwardSpeed = 255; // 前进速度
int turnSpeed = 200;    // 转弯速度
int reactionTime = 100; // 电机反应时间
int checkInterval = 200; // 传感器检查间隔
unsigned long lastCheckTime = 0; // 上次检查传感器的时间
unsigned long lastMoveTime = 0;  // 上次运动状态切换的时间
Servo myservo;          // 创建舵机对象
int currentAction = FORWARD; // 当前动作状态

void setup() {
  Serial.begin(9600);                   // 初始化串口通信，波特率为9600
  pinMode(AIN1, OUTPUT);                // 设置AIN1引脚为输出模式
  pinMode(AIN2, OUTPUT);                // 设置AIN2引脚为输出模式
  pinMode(BIN1, OUTPUT);                // 设置BIN1引脚为输出模式
  pinMode(BIN2, OUTPUT);                // 设置BIN2引脚为输出模式
  pinMode(PWMA, OUTPUT);                // 设置PWMA引脚为输出模式
  pinMode(PWMB, OUTPUT);                // 设置PWMB引脚为输出模式
  pinMode(STBY, OUTPUT);                // 设置STBY引脚为输出模式
  pinMode(sensorLeft, INPUT);           // 设置左侧传感器引脚为输入模式
  pinMode(sensorMiddle, INPUT);         // 设置中间传感器引脚为输入模式
  pinMode(sensorRight, INPUT);          // 设置右侧传感器引脚为输入模式
  pinMode(ledPin1, OUTPUT);             // 设置LED1引脚为输出模式
  pinMode(ledPin2, OUTPUT);             // 设置LED2引脚为输出模式
  myservo.attach(servoPin);             // 初始化舵机
}

void loop() {
  if (millis() - lastCheckTime >= checkInterval) { // 检查是否到了传感器检查时间
    lastCheckTime = millis();
    checkSensors();  // 检查传感器状态
  }
  
  blinkLEDs();      // 控制LED灯闪烁
}

void motorRun(int cmd) {
  digitalWrite(STBY, HIGH); // 使能电机驱动
  
  switch (cmd) {
    case FORWARD:  // 前进
      digitalWrite(AIN1, HIGH);
      digitalWrite(AIN2, LOW);
      digitalWrite(BIN1, HIGH);
      digitalWrite(BIN2, LOW);
      analogWrite(PWMA, forwardSpeed);
      analogWrite(PWMB, forwardSpeed);
      digitalWrite(ledPin1, LOW);  // 熄灭左转LED
      digitalWrite(ledPin2, LOW);  // 熄灭右转LED
      myservo.write(90);           // 舵机保持中立位置
      break;
      
    case TURNLEFT: // 左转
      analogWrite(PWMA, turnSpeed); // 左电机减速
      analogWrite(PWMB, turnSpeed); // 右电机减速
      digitalWrite(AIN1, HIGH);
      digitalWrite(AIN2, LOW);
      digitalWrite(BIN1, LOW);
      digitalWrite(BIN2, HIGH); 
      digitalWrite(ledPin1, HIGH);  // 点亮左转LED
      digitalWrite(ledPin2, LOW);   // 熄灭右转LED
      myservo.write(75);            // 舵机转到左转角度（75度）
      break;
      
    case TURNRIGHT: // 右转
      analogWrite(PWMA, turnSpeed); // 左电机减速
      analogWrite(PWMB, turnSpeed); // 右电机减速
      digitalWrite(AIN1, LOW);
      digitalWrite(AIN2, HIGH);
      digitalWrite(BIN1, HIGH);
      digitalWrite(BIN2, LOW);
      digitalWrite(ledPin1, LOW);   // 熄灭左转LED 
      digitalWrite(ledPin2, HIGH);  // 点亮右转LED
      myservo.write(105);           // 舵机转到右转角度（105度）
      break;
      
    case SWAYLEFT: // 左摇摆
      analogWrite(PWMA, turnSpeed); // 左电机减速
      analogWrite(PWMB, turnSpeed); // 右电机减速
      digitalWrite(AIN1, HIGH);
      digitalWrite(AIN2, LOW);
      digitalWrite(BIN1, LOW);
      digitalWrite(BIN2, HIGH); 
      digitalWrite(ledPin1, HIGH);  // 点亮左转LED
      digitalWrite(ledPin2, LOW);   // 熄灭右转LED
      myservo.write(85);            // 舵机转到左转角度（85度）
      break;
      
    case SWAYRIGHT: // 右摇摆
      analogWrite(PWMA, turnSpeed); // 左电机减速
      analogWrite(PWMB, turnSpeed); // 右电机减速
      digitalWrite(AIN1, LOW);
      digitalWrite(AIN2, HIGH);
      digitalWrite(BIN1, HIGH);
      digitalWrite(BIN2, LOW);
      digitalWrite(ledPin1, LOW);   // 熄灭左转LED 
      digitalWrite(ledPin2, HIGH);  // 点亮右转LED
      myservo.write(95);           // 舵机转到右转角度（95度）
      break;
      
    default: // 停止
      digitalWrite(AIN1, LOW);
      digitalWrite(AIN2, LOW);
      digitalWrite(BIN1, LOW);
      digitalWrite(BIN2, LOW);
      analogWrite(PWMA, 0);
      analogWrite(PWMB, 0);
      digitalWrite(ledPin1, LOW);  // 熄灭左转LED
      digitalWrite(ledPin2, LOW);  // 熄灭右转LED
      myservo.write(90);           // 舵机保持中立位置
      break;
  }
}

void checkSensors() {
  sensorData[0] = digitalRead(sensorLeft);   // 读取左侧传感器状态
  sensorData[1] = digitalRead(sensorMiddle); // 读取中间传感器状态
  sensorData[2] = digitalRead(sensorRight);  // 读取右侧传感器状态

  if (sensorData[1] == HIGH) { // 中间传感器检测到黑线
    motorRun(FORWARD);
    currentAction = FORWARD;
  } else if (sensorData[0] == HIGH) { // 左侧传感器检测到黑线
    motorRun(TURNLEFT); // 向左转
    currentAction = TURNLEFT;
  } else if (sensorData[2] == HIGH) { // 右侧传感器检测到黑线
    motorRun(TURNRIGHT); // 向右转
    currentAction = TURNRIGHT;
  } else if (sensorData[0] == LOW && sensorData[1] == LOW && sensorData[2] == LOW) { 
    // 所有传感器都未检测到黑线
    if (millis() - lastMoveTime >= 400) { // 前进400ms后左右摇摆
      if (currentAction == SWAYLEFT) {
        motorRun(SWAYRIGHT);
        currentAction = SWAYRIGHT;
      } else {
        motorRun(SWAYLEFT);
        currentAction = SWAYLEFT;
      }
      lastMoveTime = millis();
    }
  } else {
    motorRun(STOP); // 其他任何情况停止
    currentAction = STOP;
  }
  delay(reactionTime); // 反应时间，确保电机有充足的时间响应
}

void blinkLEDs() {
  digitalWrite(ledPin1, HIGH);
  digitalWrite(ledPin2, HIGH);
  delay(500);
  digitalWrite(ledPin1, LOW);
  digitalWrite(ledPin2, LOW);
  delay(500);
}
