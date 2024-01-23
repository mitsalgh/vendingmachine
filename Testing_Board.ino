#define rpwm1 3
#define rpwm2 5
#define rpwm3 7
#define rpwm4 9
#define rpwm5 11

#define lpwm1 4
#define lpwm2 6
#define lpwm3 8
#define lpwm4 10
#define lpwm5 12

void setup() {
 pinMode(rpwm1, OUTPUT);
 pinMode(rpwm2, OUTPUT);
 pinMode(rpwm3, OUTPUT);
 pinMode(rpwm4, OUTPUT);
 pinMode(rpwm5, OUTPUT);
 
 pinMode(lpwm1, OUTPUT);
 pinMode(lpwm2, OUTPUT);
 pinMode(lpwm3, OUTPUT);
 pinMode(lpwm4, OUTPUT);
 pinMode(lpwm5, OUTPUT);

}

void loop() 
{
   analogWrite(rpwm1, 0);
   analogWrite(lpwm1, 255);
   Serial.println("buka");
   delay(750);
   analogWrite(rpwm1, 255);
   analogWrite(lpwm1, 0);
   Serial.println("tutup");
   delay(550); 

}
