int anzahl_messungen = 10;
int led1 = 7;
int led2 = 2;
float refval = 0;
long starttime = 0;
long last_update = 0;

void setup() { 
  Serial.begin(9600);
  analogReference(INTERNAL);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  digitalWrite(led1, HIGH);
  digitalWrite(led2, LOW);
  
  delay(1000);
  // pinMode(led1a, OUTPUT);
  kalibrieren();
}

int messen(int anzahl) {
  float average = 0.0;
  int val;
  float x = 0;
  for(int n=0; n<anzahl; n++){
    val = analogRead(A1);
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

void kalibrieren() {
  refval = 0;
  Serial.println("Spiel wird geladen ...");
  refval = messen(anzahl_messungen);
  refval += 1.0;
  Serial.print("... Firefly gefangen: ");
  Serial.print(refval);
  Serial.println(" ... ");
  digitalWrite(led2, HIGH);
  delay(200);
  digitalWrite(led2, LOW);
  delay(800);
  Serial.print("3 ... ");
  digitalWrite(led2, HIGH);
  delay(200);
  digitalWrite(led2, LOW);
  delay(800);
  Serial.print("2 ... ");
  digitalWrite(led2, HIGH);
  delay(200);
  digitalWrite(led2, LOW);
  delay(800);
  Serial.print("1 ... ");
  digitalWrite(led2, HIGH);
  delay(200);
  digitalWrite(led2, LOW);
  delay(800);
  Serial.println("Go!");
  starttime = micros();
}


void loop() {
  int analogwert = messen(anzahl_messungen);
  if(analogwert > refval) {
    digitalWrite(led2, HIGH);
    Serial.println("Du hast gewonnen");
    Serial.print("Zeit: ");
    Serial.println((micros()-starttime)/1000000);
    Serial.print("Spannung: ");
    Serial.println(analogwert);
    delay(3000);
    digitalWrite(led2, LOW);
    kalibrieren();
  }
  if(millis()-last_update > 1000) {
    last_update = millis();
    Serial.println(".");
  }
  // delay(100);
  // Serial.println(analogRead(A0)); 
}
    
