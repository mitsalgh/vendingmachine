#include <Stepper.h>
//#include <string.h>
#include <SoftwareSerial.h>
#include <SPI.h>
//#include <Adafruit_PN532.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>


#define pinTombolManual A0
#define pinMotor 3
#define delayOpen 4100

LiquidCrystal_I2C lcd(0x27, 16, 2);
int relayBawah[5] = {3, 5, 7, 9, 11}; // setup pin untuk Relay yang akan disetting di bawah

const int stepsPerRevolution = 50;
Stepper myStepper(stepsPerRevolution, 8, 9, 10, 11);



String dataIn;
String dataBukaShaf[10];
String statusVending="";
int i;
int flagSet=0;
boolean parsing = false;

void setup()
{
  Serial.begin(9600);
  dataIn = "";
  lcd.init();// initialize LCD
  lcd.backlight();
  lcd.clear();
  // set the speed at 60 rpm:
  myStepper.setSpeed(60);
  pinMode(pinTombolManual, INPUT_PULLUP);
  pinMode(pinMotor, OUTPUT);
  //  pinMode(relayAtas1, OUTPUT);
  //  pinMode(relayAtas2, OUTPUT);
  //  pinMode(relayAtas3, OUTPUT);
  //  pinMode(relayAtas4, OUTPUT);
  //  pinMode(relayAtas5, OUTPUT);
  //  pinMode(relayBawah1, OUTPUT);
  //  pinMode(relayBawah2, OUTPUT);
  //  pinMode(relayBawah3, OUTPUT);
  //  pinMode(relayBawah4, OUTPUT);
  //  pinMode(relayBawah5, OUTPUT);
  for (int x = 0; x <= 4; x++) //aktivator pin untuk seluruh relay
  {
    //    pinMode(relayAtas[x], OUTPUT);
    pinMode(relayBawah[x], OUTPUT);
  }
  Serial.println("ready");
  statusVending="ready";
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("ready");
  Serial.flush();
}

void loop()
{
//  Serial.println(flagSet);
//  while(1)
//  {
//    Serial.println(digitalRead(pinTombolManual));
//     analogWrite(pinMotor, 150);
//     delay(8000);
//     analogWrite(pinMotor, 0);
//     delay(1000);
//  }
  
//  if(Serial.available() > 0 && flagSet==1)
//  {
//    char inChar = (char)Serial.read();
//    
//    flagSet=0;
//    parsing = false;
//    flagSet=0;
//    Serial.println(flagSet);
//    dataIn = "";
//  }
  if (Serial.available() > 0 )
  {
    char inChar = (char)Serial.read();
    dataIn += inChar;
    if (inChar == '\n') {  
      parsing = true; // jika parsing oke
      
    }
  }
  if (parsing)
  {
    parsingData();
    prosesBuka();
    parsing = false;
//    flagSet=1;
   Serial.flush();
   delay(1000);
    dataIn = "";
  }
  if (digitalRead(pinTombolManual) == LOW)
  {
    prosesBukaManual();
  }
  if (digitalRead(pinTombolManual) == HIGH)
  {
    analogWrite(pinMotor, 0);
    delay(100);
//    prosesBukaManual();
  }
}
void parsingData()
{
  int j = 0;
  //kirim data yang telah diterima sebelumnya
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("in:");
  //  lcd.print(1,2);
  lcd.print(dataIn);
  delay(500);
  //  Serial.print("\n");
  //inisialisasi variabel, (reset isi variabel)
  dataBukaShaf[j] = "";
  //proses parsing data
  for (i = 0; i < dataIn.length(); i++)
  {
    //pengecekan tiap karakter dengan karakter (#) dan (,)
    if (dataIn[i] == ',')
    {
      //increment variabel j, digunakan untuk merubah index array penampung
      j++;
      dataBukaShaf[j] = ""; //inisialisasi variabel array dt[j]
    }
    else
    {
      //proses tampung data saat pengecekan karakter selesai.
      dataBukaShaf[j] = dataBukaShaf[j] + dataIn[i];
    }
  }
  //kirim data hasil parsing
  //    Serial.print("Shaf 1 : ");
  //    Serial.print(dataBukaShaf[0].toInt());
  //    Serial.print("\n");
  //    Serial.print("Shaf 2 : ");
  //    Serial.print(dataBukaShaf[1].toInt());
  //    Serial.print("\n");
  //    Serial.print("Shaf 3 : ");
  //    Serial.print(dataBukaShaf[2].toInt());
  //    Serial.print("\n");
  //    Serial.print("Shaf 4 : ");
  //    Serial.print(dataBukaShaf[3].toInt());
  //    Serial.print("\n");
  //    Serial.print("Shaf 5 : ");
  //    Serial.print(dataBukaShaf[4].toInt());
  //    Serial.print("\n\n");
}
void resetData()
{
  for (int x = 0; x <= 4; x++)
  {
    dataBukaShaf[x] = "0";
  }
}
void prosesBuka()
{
  for (int jumlahShaf = 0; jumlahShaf <= 4; jumlahShaf++)
  {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Shaf ke-");
    lcd.print(jumlahShaf + 1); // di plus 1 hanya untuk lihat di print aja
    //    Serial.println();
    for (int jumlahOpen = 1; jumlahOpen <= dataBukaShaf[jumlahShaf].toInt(); jumlahOpen++)
    {
      lcd.print("$");
//      analogWrite(relayBawah[jumlahShaf], HIGH);
//      delay(500);
//      digitalWrite(relayBawah[jumlahShaf], LOW);
//      delay(500);
//      myStepper.step(stepsPerRevolution);
//      delay(200);
     analogWrite(pinMotor, 254);
     delay(delayOpen);
     analogWrite(pinMotor, 0);
     delay(500);
    }
    //     Serial.println();
  }
  resetData();
  setup();
}
void prosesBukaManual()
{
  
  analogWrite(pinMotor, 250);
  delay(100);
//  analogWrite(pinMotor, 0);
//   delay(500);
}
