int PIN = 3;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(PIN, OUTPUT);
  Serial.setTimeout(10);
}

int data;

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available()) {
    data = Serial.parseInt();
    Serial.println(data);
    analogWrite(PIN, data);
  }
}
