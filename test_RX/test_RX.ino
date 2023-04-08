
/*
 * https://maniacbug.github.io/RF24/classRF24.html
 * 
 * VCC - 3.3v
 * GND - GND
 * CSN - 8
 * CE - 7
 * SCK - 13
 * MOSI - 11
 * MISO - 12
 */

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(7, 8); // CE, CSN
const byte diachi[6] = "12345";

void setup() 
{
  Serial.begin(9600);
  
  if (!radio.begin()) 
  {
    Serial.println("Module không khởi động được...!!");
    while (1) {}
  } 
  
  radio.openReadingPipe(1, diachi);
  //Lệnh openReadingPipe có số đường truyền từ 0-5
  //Nhưng đường 0 đã được dùng cho ghi (mặc định)
  //Vì vậy chỉ dùng 1-5, nếu dùng không sẽ bị chồng lấn
  //Mở 1 kênh có địa chỉ 12345 trên đường truyền 1
  //kênh này chỉ đọc data trên địa chỉ 12345   
  radio.setPALevel(RF24_PA_MIN);
  radio.setChannel(80);
  radio.setDataRate(RF24_250KBPS);
  radio.startListening();
  
  if (!radio.available())
  {
    Serial.println("Chưa kết nối được với TX...!!");
    Serial.println("CHỜ KẾT NỐI.......");
  } 
}

void loop() 
{
  if (radio.available()) 
  {
    char nhan[30] = ""; //30 là số kí tự trong mảng
    radio.read(&nhan, sizeof(nhan));
    Serial.println(nhan);
  }
}
