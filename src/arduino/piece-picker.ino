/****
Controls piece picker
"A" = Actuator
"M" = Magnet
****/

void setup() {
  pinMode (2, OUTPUT);
  pinMode (3, OUTPUT);
  pinMode (4, OUTPUT);
  digitalWrite(2, HIGH); //Defaults Relay 2 to OFF
  digitalWrite(3, HIGH); //Defaults Relay 3 to OFF
  digitalWrite(4, HIGH); //Defaults Relay 4 to OFF
  
  //z-axis innitial homing 
  digitalWrite(2, HIGH);
  digitalWrite(3, LOW);
  delay(2110);
  digitalWrite(2, HIGH);
  digitalWrite(3, HIGH);

  Serial.begin(115200);
}

void loop() {
  if (Serial.available() > 0) {
    String command = Serial.readStringUntil('\r\n');
    executeCommand(command);
  }
  delay(10);
}

void executeCommand(String command) {
  command.trim(); // Remove leading and trailing whitespace
 
  if (command == "AS_PICK") {
    //down movement
    digitalWrite(2, LOW);
    digitalWrite(3, HIGH);
    delay(2300);
    digitalWrite(2, HIGH);
    digitalWrite(3, HIGH);

    //magnet on
    digitalWrite(4, LOW);
    delay(100);

    //up movement
    digitalWrite(2, HIGH);
    digitalWrite(3, LOW);
    delay(2300);
    digitalWrite(2, HIGH);
    digitalWrite(3, HIGH);
  } 

  if (command == "AS_DROP") {
    //down movement
    digitalWrite(2, LOW);
    digitalWrite(3, HIGH);
    delay(2300);
    digitalWrite(2, HIGH);
    digitalWrite(3, HIGH);

    //magnet off
    digitalWrite(4, HIGH);
    delay(100);

    //up movement
    digitalWrite(2, HIGH);
    digitalWrite(3, LOW);
    delay(2300);
    digitalWrite(2, HIGH);
    digitalWrite(3, HIGH);
  } 
  
  else if (command == "AT_PICK") {
    //down movement
    digitalWrite(2, LOW);
    digitalWrite(3, HIGH);
    delay(1650);
    digitalWrite(2, HIGH);
    digitalWrite(3, HIGH);

    //magnet on
    digitalWrite(4, LOW);
    delay(100);
    
    //up movement
    digitalWrite(2, HIGH);
    digitalWrite(3, LOW);
    delay(1800);
    digitalWrite(2, HIGH);
    digitalWrite(3, HIGH);
  }
  
  else if (command == "AT_DROP") {
    //down movement
    digitalWrite(2, LOW);
    digitalWrite(3, HIGH);
    delay(1650);
    digitalWrite(2, HIGH);
    digitalWrite(3, HIGH);

    //magnet off
    digitalWrite(4, HIGH);
    delay(100);
    
    //up movement
    digitalWrite(2, HIGH);
    digitalWrite(3, LOW);
    delay(1800);
    digitalWrite(2, HIGH);
    digitalWrite(3, HIGH);
  }
  
  else {
    Serial.println("UNKNOWN COMMAND RECEIVED:");
    Serial.println(command);
    Serial.println("--");
  }
}
