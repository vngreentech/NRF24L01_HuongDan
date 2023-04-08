#include <Servo.h>
Servo myservo;
int servo = 5;

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(7, 8); // CE, CSN
const byte diachi[6] = "12345";

int den = 6;
boolean gtden = 0;
int gtservo;

byte mang[2];

void setup() 
{
  Serial.begin(9600);
  
  if (!radio.begin()) 
  {
    Serial.println("Module không khởi động được...!!");
    while (1) {}
  }    
  radio.openReadingPipe(0, diachi);
  radio.setPALevel(RF24_PA_MIN);
  radio.setChannel(80);
  radio.setDataRate(RF24_250KBPS);  
  radio.startListening();
  if (!radio.available())
  {
    Serial.println("Chưa kết nối được với TX...!!");
    Serial.println("CHỜ KẾT NỐI.......");
  }
  
  pinMode(den, OUTPUT);
  myservo.attach(servo);
}

void loop() 
{
  if (radio.available()) 
  {
    radio.read(&mang, sizeof(mang));
    Serial.print("Đèn: "); Serial.print(mang[1]); Serial.print("    ");
    Serial.print("Servo: "); Serial.println(mang[0]);

    if(mang[1] == 1)
    {
      digitalWrite(den, HIGH);
    }
    else
    {
      digitalWrite(den, LOW);
    }

    myservo.write(mang[0]);
  }
}
