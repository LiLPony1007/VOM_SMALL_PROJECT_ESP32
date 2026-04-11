#include <Adafruit_SSD1306.h> //vẽ
#include <Adafruit_GFX.h>
#include <Wire.h>
//khai báo chiều dài chiều rộng
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

#define BUTTON_PIN 4    // Nút nhấn chân 4
const int VOLT_PIN = 34; // Chân đo Volt
const int OHM_PIN  = 35; // Đảm bảo tên biến ở đây là OHM_PIN

Adafruit_SSD1306 display(SCREEN_WIDTH,SCREEN_HEIGHT,&Wire,-1);//khoi tao man hinh

int mode = 0; 
bool lastBtn = HIGH;

void setup() {
  Serial.begin(115200);
  Wire.begin(21, 22);//kich hoat chan I2C
  //gan dia chi I2C la 0x3C
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  //if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)){
  //  for(;;);
  pinMode(BUTTON_PIN,INPUT_PULLUP);
  //}
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(4,12);// tro cot va hang
  display.println("Welcome to");

  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(46,38);// tro cot va hang
  display.println("VOM");


  display.display();
  delay(2000);
  display.clearDisplay();
  display.display();
}

void loop() {
 int reading = digitalRead(BUTTON_PIN);

  if (reading == LOW && lastBtn == HIGH) { // Phát hiện vừa nhấn xuống
    delay(50); // Chống dội cơ khí
    if (digitalRead(BUTTON_PIN) == LOW) { // Xác nhận chắc chắn nhấn
      mode++;
      Serial.println(mode);
      if (mode > 1) mode = 0; 
     
      display.clearDisplay();
      display.setCursor(10, 25);
      display.setTextSize(1);
      display.print("Changing Mode...");
      display.display();
    }
  }
  lastBtn = reading;
  // --- HIỂN THỊ ---
  //chế độ 0 đo V
  //chế độ 1 đo Ohm
  display.clearDisplay();
  if (mode == 0) {displayVoltmeter();}
  else if (mode == 1) {displayOhmmeter();}
  display.display();
  delay(100);
}