
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(7, 8); // CE, CSN
const byte diachi[6] = "12345"; //Mảng kí tự dạng chuỗi có 6 kí tự

int nutnhan = 6; boolean gtnutnhan = 0;
int bientro = A0; int gtbientro; int gtbiendoi;

byte mang[2]; //Mảng có 2 phần tử

void setup() 
{
  Serial.begin(9600);

  if (!radio.begin()) 
  {
    Serial.println("Module không khởi động được...!!");
    while (1) {}
  }   
  radio.openWritingPipe(diachi);
  radio.setPALevel(RF24_PA_MIN); //Cài bộ khuyết địa công suất ở mức MIN
  radio.setChannel(80);
  radio.setDataRate(RF24_250KBPS);  
  radio.stopListening(); //Cài đặt module là TX
  if (!radio.available())
  {
    Serial.println("Chưa kết nối được với RX...!!");
    Serial.println("CHỜ KẾT NỐI.......");
  }

  pinMode(nutnhan, INPUT_PULLUP);
  pinMode(bientro, INPUT);
}

void loop() 
{
  gtbientro = analogRead(bientro);
  gtbiendoi = map(gtbientro, 0, 1023, 0, 180);
  mang[0] = gtbiendoi; //Ghi gtbiendoi vào phần tử 0
  Serial.print("Góc Servo: "); Serial.print(gtbiendoi); Serial.print("   ");
  
  gtnutnhan = digitalRead(nutnhan);
  mang[1] = gtnutnhan;
  Serial.print("Giá Trị nút nhấn: "); Serial.println(gtnutnhan);

  radio.write(&mang, sizeof(mang));
  
  delay(50);
}
