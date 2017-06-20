int d_ch_1 = 3;
int d_ch_2 = 4;
int ch = 2;
unsigned long previousMillis = 0;
unsigned long previousMillis2 = 0;
int voltage_s1;
int voltage_s2;
boolean st_t1 = 0;
boolean st_t2 = 0;
void setup() {
pinMode(d_ch_1, OUTPUT);
pinMode(d_ch_2, OUTPUT);
pinMode(ch, OUTPUT);
digitalWrite(ch, LOW);
digitalWrite(d_ch_2, HIGH);
digitalWrite(d_ch_1, LOW);

Serial.begin(9600);
}

void loop() {

    unsigned long currentMillis = millis();

    if (currentMillis - previousMillis2 >= 10&&st_t1==0) {
      digitalWrite(ch, LOW);
      int sensorValue = analogRead(A0);
      int sensorValue2 = analogRead(A1);
        // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
      float voltage = (sensorValue * (4.9854 / 1007.0))*2;
      float voltage2 = sensorValue2 * (4.9854 / 1010.0);
        // print out the value you read:
      voltage_s1=voltage2*10;
      voltage_s2 =  (voltage- voltage2)*10;

      if(voltage_s1>voltage_s2){
        digitalWrite(d_ch_1, HIGH);
        digitalWrite(d_ch_2, HIGH);
      }else if(voltage_s1<voltage_s2){
        digitalWrite(d_ch_2, LOW);
        digitalWrite(d_ch_1, LOW);
      }else{
        digitalWrite(d_ch_2, HIGH);
        digitalWrite(d_ch_1, LOW);
        if(voltage_s1<41&&voltage_s2<41){
          st_t2=1;
        }else{
          st_t2=0;
        }
      }


      previousMillis2 = currentMillis;
    }
    if(st_t1==1&&st_t2==1){
      digitalWrite(ch, HIGH);
    }else{
      digitalWrite(ch, LOW);
    }


if (currentMillis - previousMillis >= 3000) {
  // save the last time you blinked the LED
  Serial.print(voltage_s1);
    Serial.print(" ");
    Serial.print(voltage_s2);
    Serial.print(" ");
    Serial.print(voltage_s2+voltage_s1);
    Serial.print(" ");
    Serial.println(st_t1);
  previousMillis = currentMillis;
  if(st_t1==1){
    st_t1 = 0;
  }else{
    st_t1 =1;
  }
}

}
