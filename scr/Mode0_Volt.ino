void displayVoltmeter() {
  // Lấy trung bình 64 lần điện áp đầu vào 
  long sum = 0;
  for(int i=0; i<64; i++) {
    sum += analogRead(VOLT_PIN);
  }
  float rawV = sum / 20.0;
  // ở esp32 chân đo ADC 12 bits nên nó chạy từ 0-4095 và nó có điện áp tham chiếu 3.3V nên ta lấy data đọc được áp dụng cho công thức sau
  float v_x = (rawV * 3.3) / 4095.0;

  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println("MODE: VOLTMETER");

  display.drawLine(0, 10, 128, 10, WHITE);

  display.setTextSize(3);
  display.setCursor(15, 25);
  
  display.print(v_x, 1); // Lấy 1 chữ số thập phân
  display.print("V");
 
}
