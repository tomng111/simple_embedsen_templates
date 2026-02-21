int led1 = 13; // LED1 pin
int led2 = 9; // LED2 pin
int trig = 8; 
int echo = 7;
int distanz, dauer;
unsigned long pre_time;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  pre_time = millis();
}

int Distanz(){
  // trigger
  digitalWrite(trig,0);
  delayMicroseconds(2);
  digitalWrite(trig,1);
  delayMicroseconds(5);
  digitalWrite(trig,0);
  // calculating
  dauer = pulseIn(echo, HIGH);
  distanz = int(dauer/2/29.412);
  delay(100);
  return distanz;
}

void loop() {
  // put your main code here, to run repeatedly:
  String datum = "";
  while(Serial.available()>0){
    char r = Serial.read();
    datum += r;
    delay(5);
  }
  datum.trim(); // Blank space
  // LED1
  if(datum == "e1")  digitalWrite(led1, HIGH);
  if(datum == "a1")  digitalWrite(led1, LOW);
  // LED2
  if(datum == "e2")  digitalWrite(led2, HIGH);
  if(datum == "a2")  digitalWrite(led2, LOW);
  // transferring
  if(millis() - pre_time >= 1000){
    pre_time = millis();
    int distance = Distanz();
    Serial.println(String(distance));
  }
}
