int anzahl_messungen = 10;
int led_power = 7;
int led_player1 = 2;
int led_player2 = 3;
int player1_input = A0;
int player2_input = A1;
float refval = 0;
long starttime = 0;
long last_update = 0;

void (* resetFunc)(void) = 0;

void setup() { 
  Serial.begin(9600);
  analogReference(INTERNAL);
  pinMode(led_power, OUTPUT);
  pinMode(led_player1, OUTPUT);
  pinMode(led_player2, OUTPUT);
  digitalWrite(led_power, HIGH);
  digitalWrite(led_player1, LOW);
  digitalWrite(led_player2, LOW);
  delay(1000);
  kalibrieren(player2_input);
}

int messen(int analog_pin, int anzahl) {
  float average = 0.0;
  int val;
  float x = 0;
  for(int n=0; n<anzahl; n++){
    val = analogRead(analog_pin);
    // if(val > 0) {
      x = x + 1.0;
      average = average + val;
    // }
    delay(10);
  }
  if(x > 0) {
    average = average / x;
  }
  else {
    average = 0;
  }
  return average;
}

void kalibrieren(int letzter_verlierer) {
  refval = 0;
  Serial.println("Spiel wird geladen ...");
  int refval1 = messen(player1_input, anzahl_messungen);
  int refval2 = messen(player2_input, anzahl_messungen);
  if(refval2 < refval2){
    refval = refval2 + 3.0;
  }
  else {
    refval = refval1 + 3.0;
  }
  Serial.print("... es muessen ");
  Serial.print(refval+1);
  Serial.println(" Gluehwuermchen gefangen werden ...");
  digitalWrite(led_player1, HIGH);
  digitalWrite(led_player2, HIGH);
  delay(200);
  digitalWrite(led_player1, LOW);
  digitalWrite(led_player2, LOW);
  delay(800);
  Serial.print("3 ... ");
  digitalWrite(led_player1, HIGH);
  digitalWrite(led_player2, HIGH);
  delay(200);
  digitalWrite(led_player1, LOW);
  digitalWrite(led_player2, LOW);
  delay(800);
  Serial.print("2 ... ");
  digitalWrite(led_player1, HIGH);
  digitalWrite(led_player2, HIGH);
  delay(200);
  digitalWrite(led_player1, LOW);
  digitalWrite(led_player2, LOW);
  delay(800);
  Serial.print("1 ... ");
  digitalWrite(led_player1, HIGH);
  digitalWrite(led_player2, HIGH);
  delay(200);
  digitalWrite(led_player1, LOW);
  digitalWrite(led_player2, LOW);
  delay(800);
  Serial.println("Go!");
  starttime = micros();
}



void loop() {
  int analogwert1 = messen(player1_input, anzahl_messungen);
  if(analogwert1 > refval) {
    digitalWrite(led_player1, HIGH);
    Serial.print("Spieler 1 hat gewonnen, Zeit: ");
    Serial.println((micros()-starttime)/1000000);
    Serial.print("Gluehwuermchen: ");
    Serial.println(analogwert1);
    delay(3000);
    digitalWrite(led_player2, LOW);
    //kalibrieren(player2_input);
    resetFunc();
  }
  int analogwert2 = messen(player2_input, anzahl_messungen);
  if(analogwert2 > refval) {
    digitalWrite(led_player2, HIGH);
    Serial.print("Spieler 2 hat gewonnen, Zeit: ");
    Serial.println((micros()-starttime)/1000000);
    Serial.print("Gluehwuermchen: ");
    Serial.println(analogwert2);
    delay(3000);
    digitalWrite(led_player2, LOW);
    //kalibrieren(player1_input);
    resetFunc();
  }
  if(millis()-last_update > 1000) {
    last_update = millis();
    Serial.println(".");
  }
  // delay(100);
  // Serial.println(analogRead(A0)); 
}
    
