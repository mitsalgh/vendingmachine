//#define rpwm1 3
//#define rpwm2 5
//#define rpwm3 7
//#define rpwm4 9
//#define rpwm5 11
//
//#define lpwm1 4
//#define lpwm2 6
//#define lpwm3 8
//#define lpwm4 10
//#define lpwm5 12


// pin setup untuk 
//const int rpwm[0]= 3;
//const int rpwm[1]= 5;
//const int rpwm[2]= 7;
//const int rpwm[3]= 9;
int rpwm[5]= {3,5,7,9,11};

//const int lpwm[0]= 4;
//const int lpwm[1]= 6;
//const int lpwm[2]= 8;
//const int lpwm[3]= 10;
int lpwm[5]= {4,6,8,10,12};

String dataIn;
String dataBukaShaf[10];
int i;
boolean parsing=false;
 
void setup() 
{
  Serial.begin(9600);
  dataIn="";
//  pinMode(rpwm1, OUTPUT);
//  pinMode(rpwm2, OUTPUT);
//  pinMode(rpwm3, OUTPUT);
//  pinMode(rpwm4, OUTPUT);
//  pinMode(rpwm5, OUTPUT);
//  pinMode(lpwm1, OUTPUT);
//  pinMode(lpwm2, OUTPUT);
//  pinMode(lpwm3, OUTPUT);
//  pinMode(lpwm4, OUTPUT);
//  pinMode(lpwm5, OUTPUT);

  for(int x=0;x<=4;x++)
  {
    pinMode(rpwm[x], OUTPUT);
    pinMode(lpwm[x], OUTPUT);
  }
  
}
 
void loop() 
{
  if(Serial.available()>0)
  {
    char inChar = (char)Serial.read();
    dataIn += inChar;
    if (inChar == '\n') {parsing = true;}
  }
  if(parsing)
  {
    parsingData();
    prosesBuka();
    parsing=false;
    dataIn="";      
  }
}
void parsingData()
{
  int j=0;
  //kirim data yang telah diterima sebelumnya
  Serial.print("data masuk : ");
  Serial.print(dataIn);
  Serial.print("\n");
  //inisialisasi variabel, (reset isi variabel)
  dataBukaShaf[j]="";
  //proses parsing data
  for(i=0;i<dataIn.length();i++)
  {
   //pengecekan tiap karakter dengan karakter (#) dan (,)
   if ((dataIn[i] == '#') || (dataIn[i] == ','))
   {
     //increment variabel j, digunakan untuk merubah index array penampung
     j++;
     dataBukaShaf[j]=""; //inisialisasi variabel array dt[j]
   }
   else
   {
     //proses tampung data saat pengecekan karakter selesai.
     dataBukaShaf[j] = dataBukaShaf[j] + dataIn[i];
   }
  }
      //kirim data hasil parsing
    Serial.print("Shaf 1 : ");
    Serial.print(dataBukaShaf[0].toInt());
    Serial.print("\n");
    Serial.print("Shaf 2 : ");
    Serial.print(dataBukaShaf[1].toInt());
    Serial.print("\n");
    Serial.print("Shaf 3 : ");
    Serial.print(dataBukaShaf[2].toInt());
    Serial.print("\n");
    Serial.print("Shaf 4 : ");
    Serial.print(dataBukaShaf[3].toInt());
    Serial.print("\n");
    Serial.print("Shaf 5 : ");
    Serial.print(dataBukaShaf[4].toInt());
    Serial.print("\n\n");
}
void resetData()
{
  for(int x=0;x<=4;x++)
  {
    dataBukaShaf[x]="0";
  }
}
void prosesBuka()
{
  for(int jumlahShaf=0;jumlahShaf<=4;jumlahShaf++)
  {
    Serial.print("Shaf ke-");
    Serial.print(jumlahShaf + 1); // di plus 1 hanya untuk lihat di print aja
    Serial.println();
    for(int jumlahOpen=1;jumlahOpen<=dataBukaShaf[jumlahShaf].toInt();jumlahOpen++)
    {
//     Serial.print("$ "); 
//     analogWrite(rpwm1, 0);
//     analogWrite(lpwm1, 100);
//     Serial.println("buka");
//     delay(750);
//     analogWrite(rpwm1, 150);
//     analogWrite(lpwm1, 0);
//     Serial.println("tutup");
//     delay(550); 
//     analogWrite(rpwm1, 0);
//     analogWrite(lpwm1, 0);
//     Serial.println("tutup");
//     delay(550);

     Serial.print("$ ");
     analogWrite(rpwm[jumlahShaf], 0);
     analogWrite(lpwm[jumlahShaf], 255);
     Serial.println("buka");
     delay(750);
     analogWrite(rpwm[jumlahShaf], 255);
     analogWrite(lpwm[jumlahShaf], 0);
     Serial.println("tutup");
     delay(550);
    }
     Serial.println();
  }
  resetData();
}
