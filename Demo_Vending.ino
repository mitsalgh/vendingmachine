#include <string.h>
#include <SoftwareSerial.h>
#include <SPI.h>
#include <Adafruit_PN532.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

//Setting Miso Mosi NFC ID Sensor
#define SCK  (13)
#define MOSI (11)
#define SS   (10)
#define MISO (12)
Adafruit_PN532 nfc(SCK, MISO, MOSI, SS);

#define pinButton A1
#define pwm1 5
#define pwm2 6

int lcdColumns = 18; 
int lcdRows = 4;
LiquidCrystal_I2C lcd(0x27, lcdColumns, lcdRows);

//Variabel
String nfcID="";

void prosesBuka()
{
   analogWrite(pwm1, 0);
   analogWrite(pwm2, 200);
   delay(700);
   analogWrite(pwm1, 0);
   analogWrite(pwm2, 0);
   delay(1000);
   analogWrite(pwm1, 200);
   analogWrite(pwm2, 0);
   delay(500);
}
void stopVending()
{
  analogWrite(pwm1, 0);
  analogWrite(pwm2, 0);
}

void getNfcIdUser()//check NFC ID
{
  uint8_t success;
  uint8_t uid[] = { 0, 0, 0, 0, 0, 0, 0 };  // Buffer to store the returned UID
  uint8_t uidLength;                        // Length of the UID (4 or 7 bytes depending on ISO14443A card type)
  success = nfc.readPassiveTargetID(PN532_MIFARE_ISO14443A, uid, &uidLength);
  String CardID = "";
  String Link = "";
  if (success) 
  {
    unsigned int hex_num;
    hex_num =  uid[3] << 24;
    hex_num += uid[2] << 16;
    hex_num += uid[1] <<  8;
    hex_num += uid[0];
    CardID = String(hex_num);
    if (CardID.length()==8) 
    {
      CardID = '0'+CardID;
    } 
    if(CardID.length()==9) //panjang karakter untuk nfc id
    {
      CardID = '0'+CardID;
    }
    else 
    {
      nfcID=CardID;
    }
    nfcID=CardID;
    lcd.clear();
    lcd.setCursor(2, 1);
    lcd.print("Sedang Diproses");
    prosesBuka();
    lcd.clear();
    lcd.setCursor(3, 1);
    lcd.print("Silahkan Ambil");
    delay(2000);
    lcd.clear();
  }
  else
  {
    lcd.setCursor(3, 1);
    lcd.print("TAP KARTU ANDA");
    stopVending();
  }
}

void setup()
{
  lcd.init();// initialize LCD
  lcd.backlight();
  lcd.setCursor(0, 0);
  pinMode(pinButton,INPUT_PULLUP);
  pinMode(pwm1, OUTPUT);
  pinMode(pwm2, OUTPUT);
  Serial.begin(9600);
  nfc.begin();
  nfc.SAMConfig();
//  lcd.setCursor(3, 1);
//  lcd.print("TAP KARTU ANDA");
}

void loop()
{
  lcd.setCursor(3, 1);
  lcd.print("TAP KARTU ANDA");
  getNfcIdUser();
//  while(1)
//  {
//    Serial.println(digitalRead(pinButton));
//  }
//  if(digitalRead(pinButton)==LOW)
//  {
//   analogWrite(pwm1, 0);
//   analogWrite(pwm2, 200);
//   delay(700);
//   analogWrite(pwm1, 0);
//   analogWrite(pwm2, 0);
//   delay(1000);
//   analogWrite(pwm1, 200);
//   analogWrite(pwm2, 0);
//   delay(500); 
//  }
//  else
//  {
//   analogWrite(pwm1, 0);
//   analogWrite(pwm2, 0); 
//  }
  
}
