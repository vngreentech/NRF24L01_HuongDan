
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(7, 8); // CE, CSN
const byte diachi[][6] = {"12345", "10000"}; //0, 1

int led = 6;
boolean nutnhan = 0;
int bientro = A0; int gtbientro; int gtbiendoi;

void setup() 
{
  Serial.begin(9600);

  if (!radio.begin()) 
  {
    Serial.println("Module không khởi động được...!!");
    while (1) {}
  }   
  radio.openWritingPipe(diachi[1]);
  //Chỉ có thể mở 1 đường ghi
  //Lệnh openWritingPipe có số đường truyền mặc định là 0
  //Mở 1 kênh có địa chỉ 10000 trên đường truyền 0
  //kênh này chỉ ghi data trên địa chỉ 10000   
  radio.openReadingPipe(1, diachi[0]);
  //Có thể mở 6 đường đọc cùng lúc
  //Nhưng đường 0 mặc định dùng cho ghi
  //Lệnh openReadingPipe có thể mở đường truyền từ 1-5
  //Đọc data của địa chỉ 12345 trên đường truyền 1
     
  radio.setPALevel(RF24_PA_MIN); //Cài bộ khuyết địa công suất ở mức MIN
  radio.setChannel(80);
  radio.setDataRate(RF24_250KBPS);    
  if (!radio.available())
  {
    Serial.println("Chưa kết nối được với RX...!!");
    Serial.println("CHỜ KẾT NỐI.......");
  }

  pinMode(led, OUTPUT);
  pinMode(bientro, INPUT);
}

void loop() 
{
  radio.stopListening(); //Ngưng nhận
    gtbientro = analogRead(bientro);
    gtbiendoi = map(gtbientro, 0, 1023, 0, 180);
    radio.write(&gtbiendoi, sizeof(gtbiendoi));
    Serial.print("Biến trở gửi: "); Serial.print(gtbiendoi); Serial.print("   ");
    delay(10);
      
  radio.startListening(); //Bắt đầu nhận
    while(!radio.available());
    radio.read(&nutnhan, sizeof(nutnhan));
    Serial.print("Nhận nút nhấn: "); Serial.println(nutnhan);
    if (nutnhan == HIGH)
     {
       digitalWrite(led, HIGH);
     }
    else
     {
       digitalWrite(led, LOW);
     }
    delay(10);  
}
