int count1 = 0;
int count2 = 0;

int relay1_on_time_s = 10*60;
int relay2_on_time_s = 30*60;

int relay1_off_time_s = 1*60*60;
int relay2_off_time_s = 1*60*60;

int DIGITAL_PIN_RELAY_1 = 7;
int DIGITAL_PIN_RELAY_2 = 8;

void setup() {
//  Serial.begin(9600);
  pinMode(DIGITAL_PIN_RELAY_1, OUTPUT);
  pinMode(DIGITAL_PIN_RELAY_2, OUTPUT);
}

void loop() {
//  Serial.print(count1);
//  Serial.println(count2);
  delay(1000);
  count1 += 1;
  count2 += 1;  

  if (count1 == relay1_on_time_s) {
    digitalWrite(DIGITAL_PIN_RELAY_1, HIGH);
  }

  if (count1 == relay1_on_time_s + relay1_off_time_s) {
    digitalWrite(DIGITAL_PIN_RELAY_1, LOW);
    count1 = 0;
  }

  if (count2 == relay2_on_time_s) {
    digitalWrite(DIGITAL_PIN_RELAY_2, HIGH);
  }

  if (count2 == relay2_on_time_s + relay2_off_time_s) {
    digitalWrite(DIGITAL_PIN_RELAY_2, LOW);
    count2 = 0;
  }
  

}
