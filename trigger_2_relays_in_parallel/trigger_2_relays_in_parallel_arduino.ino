int count1 = 0;
int count2 = 0;

int relay1_on_time_s = 3*60;
int relay2_on_time_s = 8*60;

int relay1_off_time_s = 15*60;
int relay2_off_time_s = 15*60;

int cycle_sec = 5;

int DIGITAL_PIN_RELAY_1 = 7;
int DIGITAL_PIN_RELAY_2 = 8;

String message;
String SerialMessage; // for incoming serial data

void setup() {
  Serial.begin(115200);
  pinMode(DIGITAL_PIN_RELAY_1, OUTPUT);
  pinMode(DIGITAL_PIN_RELAY_2, OUTPUT);
}

void loop() {
  if (Serial.available() > 0) {
    // read the incoming string:
    SerialMessage = Serial.readString();
    Serial.print(SerialMessage);
    if (SerialMessage == "START_R1") {
      digitalWrite(DIGITAL_PIN_RELAY_1, LOW);
      count1 = 0;
      Serial.println("count_1 RESET");
      }
    if (SerialMessage == "START_R2") {
      digitalWrite(DIGITAL_PIN_RELAY_2, LOW);
      count2 = 0;
      Serial.println("count_2 RESET");
      }
  }
  
  message = String("STATUS: ")
  + "count_1 " + String(count1) + " " + String(digitalRead(DIGITAL_PIN_RELAY_1)) + " " + String(relay1_on_time_s) + " " + String(relay1_off_time_s)
  + "|| count_2 " + String(count2) + " " + String(digitalRead(DIGITAL_PIN_RELAY_2)) + " " + String(relay2_on_time_s) + " " + String(relay2_off_time_s);
  Serial.println(message);   

  // turn off conditions
  if ((count1 <= relay1_on_time_s) && ((count1 + cycle_sec) > relay1_on_time_s)) {
    digitalWrite(DIGITAL_PIN_RELAY_1, HIGH);
  }
  
  if ((count2 <= relay2_on_time_s) && ((count2 + cycle_sec) > relay2_on_time_s)) {
    digitalWrite(DIGITAL_PIN_RELAY_2, HIGH);
  }
  
  // turn on conditions
  if ((count1 <= (relay1_on_time_s + relay1_off_time_s)) && ((count1 + cycle_sec) > (relay1_on_time_s + relay1_off_time_s))) {
    digitalWrite(DIGITAL_PIN_RELAY_1, LOW);
    count1 = 0;
  }
  
  if ((count2 <= (relay2_on_time_s + relay2_off_time_s)) && ((count2 + cycle_sec) > (relay2_on_time_s + relay2_off_time_s))) {
    digitalWrite(DIGITAL_PIN_RELAY_2, LOW);
    count2 = 0;
  }
  
  delay(cycle_sec * 1000);
  count1 += cycle_sec;
  count2 += cycle_sec; 
  
}
