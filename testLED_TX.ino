
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(7, 8); // CE, CSN
const byte diachi[6] = "12345"; //Mảng kí tự dạng chuỗi có 6 kí tự

int nutnhan = 6; boolean gtnutnhan = 0;

void setup() 
{
  Serial.begin(9600);

  if (!radio.begin()) 
  {
    Serial.println("Module không khởi động được...!!");
    while (1) {}
  }   
  radio.openWritingPipe(diachi); 
  //Lệnh openWritingPipe mặc định là đường truyền 0
  //mở 1 kênh có địa chỉ 12345 trên đường truyền 0
  // kênh này ghi data lên địa chỉ 12345  
  radio.setPALevel(RF24_PA_MIN); //Cài bộ khuyết đại công suất ở mức MIN
  radio.setChannel(80);
  radio.setDataRate(RF24_250KBPS);
  radio.stopListening(); //Cài đặt module là TX
  if (!radio.available())
  {
    Serial.println("Chưa kết nối được với RX...!!");
    Serial.println("CHỜ KẾT NỐI.......");
  }

  pinMode(nutnhan, INPUT_PULLUP);
}

void loop() 
{
  gtnutnhan = digitalRead(nutnhan);
  Serial.print("Giá Trị nút nhấn: "); Serial.println(gtnutnhan);
  radio.write(&gtnutnhan, sizeof(gtnutnhan));
  delay(500);
}
