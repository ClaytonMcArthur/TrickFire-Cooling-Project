// I copied from Ishaan sorry 


const int pwm1 = 3;
const int pwm2 = 5;
const int pwm3 = 6;
const int pwm4 = 9;
const int tempPin1 = A0;
const int tempPin2 = A1;
int fanRunTime = 0;

bool fanOn = false;
unsigned long fanStartTime = 0;


void setup() {
  // put your setup code here, to run once:
  pinMode(pwm1, OUTPUT);
  pinMode(pwm2, OUTPUT);
  pinMode(pwm3, OUTPUT);
  pinMode(pwm4, OUTPUT);
  
  Serial.begin(9600);
}

void loop() {

  // float temperature = readTemperature(); //in celcius
  // Serial.print("Temperature: ");
  // Serial.println(temperature);

  // if(temperature > 40.0) {
  //     turnFanOn();
  //     fanStartTime = millis(); //start the timer
  // }

  // //keep fan on until temperature drops below 20degrees C
  // if(fanOn) {
  //   if(millis() - fanStartTime >= fanRunTime || temperature <= 20.0) {
  //     turnFanOff();
  //     fanOn = false;
  //   }
  // }

  // delay(500);

  turnFanOn();
  delay(2000);
  turnFanOff();
  delay(2000);

}


//few added functions
void turnFanOn() {
  analogWrite(pwm1, 255);
  analogWrite(pwm2, 255);
  analogWrite(pwm3, 255);
  analogWrite(pwm4, 255);
  fanOn = true;
  Serial.println("Fan ON");
}


void turnFanOff() {
  analogWrite(pwm1, 0);
  analogWrite(pwm2, 0);
  analogWrite(pwm3, 0);
  analogWrite(pwm4, 0);
  fanOn = false;
  Serial.println("Fan OFF");
}

float readTemperature() {
  int sensorValue1 = analogRead(tempPin1);
  float voltage1 = sensorValue1 * (5.0 / 1023.0); //convert temp1 to voltage
  float temp1 = (voltage1 - 0.5) * 100.0; //convert temp1 to degrees C

  int sensorValue2 = analogRead(tempPin2);
  float voltage2 = sensorValue2 * (5.0/1023.0); //convert temp2 to voltage
  float temp2 = (voltage2 - 0.5) * 100.0; //convert temp2 to degrees C

  return (temp1 + temp2) / 2.0; //return avg. from both temp sensors
}
