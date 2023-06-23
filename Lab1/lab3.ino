int R = D1;
int G = D2;
int B = D3;
void setup() {
pinMode(R, OUTPUT);
pinMode(G, OUTPUT);
pinMode(B, OUTPUT);
Serial.begin(9600);
}
void loop() {
// กำหนด LED สีขาว
analogWrite(R, 95);
analogWrite(G, 243);
analogWrite(B, 240);
delay(500);
}
