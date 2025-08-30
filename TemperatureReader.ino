// Ishaan Shete
// TrickFire Robotics Cooling Team
// Team: Clayton, Pasha, Davin, Reyhan, Abdullahi
// 03/16/2025

const int fanPin1 = 2;
const int fanPin2 = 4;
const int fanPin3 = 7;
const int fanPin4 = 8;
const int tempPin1 = A0;
const int tempPin2 = A1;

bool fanOn = false;
unsigned long fanStartTime = 0;


void setup() {
  // put your setup code here, to run once:
  pinMode(fanPin1, OUTPUT);
  pinMode(fanPin2, OUTPUT);
  pinMode(fanPin3, OUTPUT);
  pinMode(fanPin4, OUTPUT);
  
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  float temperature = readTemperature(); //in celcius
  Serial.print("Temperature: ");
  Serial.println(temperature);

  if(temperature > 40.0) {
      turnFanOn();
      fanStartTime = millis(); //start the timer
  }

  //keep fan on until temperature drops below 20degrees C
  if(fanOn) {
    if(millis() - fanStartTime >= fanRunTime || temperature <= 20.0) {
      turnFanOff();
      fanOn = false;
    }
  }

  delay(500);

}


//few added functions
void turnFanOn() {
  digitalWrite(fanPin1, HIGH);
  digitalWrite(fanPin2, HIGH);
  digitalWrite(fanPin3, HIGH);
  digitalWrite(fanPin4, HIGH);
  fanOn = true;
  Serial.println("Fan ON");
}

void turnFanOff() {
  digitalWrite(fanPin1, LOW);
  digitalWrite(fanPin2, LOW);
  digitalWrite(fanPin3, LOW);
  digitalWrite(fanPin4, LOW);
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

