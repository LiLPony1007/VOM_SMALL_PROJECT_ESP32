void displayOhmmeter() {
 //tương tự lấy trung bình 64 lần
  long sum = 0;
  for(int i=0; i<64; i++) {
    sum += analogRead(OHM_PIN);
  }
  int rawR = sum / 64;
  //lấy 1 điện trở mẫu để so sánh 
  float R_5k = 5000.0; 
  Serial.println(rawR);
  float R_x=R_5k*(float)rawR/(4095-rawR);

  //decor
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println("MODE: OHMMETER");
  display.drawLine(0, 10, 128, 10, WHITE);

  if(rawR>4000){
    //nếu giá trị ADC đọc được >4000 để tránh cho công thức R_x=R_5k*(float)rawR/(4095-rawR) tiến đến vô cùng nghĩa là mạch hở 
    display.setTextSize(2);
    display.setCursor(20, 30);
    display.print("OPEN");
  }else{
    display.setCursor(0, 30);
    if(R_x<1000){
      //nếu nhỏ hơn 1k ta xét định dạng ohm
      display.setTextSize(2);
      display.print((int)R_x); 
      display.print(" Ohm");
    }else{
      //lớn hơn 1k định dạng 1kohm
      display.setTextSize(2);
      display.print(R_x / 1000.0, 1); 
      display.print(" kOhm");
    }
  }
}