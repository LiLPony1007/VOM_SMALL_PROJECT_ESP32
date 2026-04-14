# VOM_SMALL_PROJECT_ESP32
# 📝 Giới thiệu dự án
![z7716042692885_a50d0d34f0f6eb07ac7dab6c8332fa82](https://github.com/user-attachments/assets/770851da-dd9c-4fac-a185-180c0f3a0bf8)


* Dự án này tập trung vào việc xây dựng một thiết bị đo điện trở dựa trên vi điều khiển ESP32. Mục tiêu chính là nghiên cứu cách thức hoạt động của bộ chuyển đổi Analog-to-Digital (ADC) 12-bit trên ESP32, đồng thời tích hợp hiển thị dữ liệu thời gian thực qua giao thức I2C trên màn hình OLED.

* Điểm đặc biệt là việc phân tích và xử lý sai số phi tuyến tính của ESP32 – một thách thức phổ biến khi làm việc với các dòng chip giá rẻ nhưng có hiệu năng xử lý mạnh mẽ này.

# 🛠 Phần cứng và Vật liệu 
Dưới đây là danh sách các linh kiện được sử dụng trong dự án:

![z7716042683275_01e946cb15bc3f0dfebfcf33478da4f0](https://github.com/user-attachments/assets/16263b02-8d6b-4337-83d5-86d27f9404d0)


1. Vi điều khiển trung tâm
  * ESP32 DevKit V1: Độ phân giải ADC: 12-bit được tính theo công thức 2^M-1 mức tương đương 0 - 4095.

  * Điện áp hoạt động: 3.3V.

 2. Thiết bị hiển thị
  * Màn hình OLED 0.96 inch:

  * Công nghệ: SSD1306.

  * Giao thức giao tiếp: I2C.

  * Độ phân giải: 128x64 pixel.
# 🪬 CÁC KHÁI NIỆM CẦN BIẾT

1. ADC (Analog-to-Digital Converter) là bộ chuyển đổi tín hiệu tương tự sang tín hiệu số.
   * Định nghĩa: Trong thế giới thực, các đại lượng như nhiệt độ, ánh sáng hay điện áp là liên tục. ADC ghi các mức điện áp đó và biến chúng thành các con số mà vi điều khiển như ESP32 có thể hiểu và xử lý được qua các chân chuyên dụng nhận tín hiệu ADC như GPIO pin 4, 2, 15,...

<img width="1216" height="891" alt="DATASHEET_ESP32" src="https://github.com/user-attachments/assets/ba58c448-65d6-4f93-9db5-be83d4b46cac" />


    * Thông số quan trọng: Độ phân giải. Với ESP32 là 12-bit, nghĩa là nó chia dải điện áp từ 0V đến 3.3V thành 2^12 = 4096 mức nhỏ để đo lường.
    * Các loại khác của ADC:

   <img width="1246" height="882" alt="Screenshot 2026-04-12 202140" src="https://github.com/user-attachments/assets/3f30bd9c-aa7a-4593-bf93-dc2496ba1a5e" />


2. I2C (Inter-Integrated Circuit) là một giao thức giao tiếp nối tiếp đồng bộ giữa các vi mạch.
   * Định nghĩa: Đây là một cách thức giao tiếp giữa vi điều khiển gọi là Master và các thiết bị ngoại vi như màn hình OLED, cảm biến là Slaves chỉ thông qua 2 sợi dây duy nhất:
   * SDA (Serial Data): Đường truyền dữ liệu hai chiều.
   * SCL (Serial Clock): Đường truyền tín hiệu nhịp xung để đồng bộ thời gian.
   * Ưu điểm: Cho phép kết nối nhiều thiết bị trên cùng một bus dây bằng cách phân biệt qua địa chỉ riêng biệt của mỗi thiết bị, giúp tiết kiệm tối đa chân cắm cho ESP32. 
   
   <img width="600" height="167" alt="Screenshot 2026-04-11 224838" src="https://github.com/user-attachments/assets/7db5712e-5efc-4c3b-a873-b598b0c7e67c" />
   

   
# ⚙️ Thực hiện 

* Việc thực hiện dự án được chia làm hai giai đoạn chính: Lắp đặt phần cứng và Xử lý phần mềm.
   
1. Lắp đặt phần cứng dựa trên mô phỏng

<img width="1259" height="642" alt="Screenshot 2026-04-11 230830" src="https://github.com/user-attachments/assets/f19d6697-6c9f-4290-b864-f66d412105ae" />


   * Dựa trên sơ đồ Wokwi, mạch được triển khai với cấu trúc tối ưu:
   * Mạch cầu phân áp: Sử dụng điện trở mẫu 5kOmega.
   * Điểm giữa của cầu phân áp được nối vào chân GPIO35 để đọc giá trị Analog.
       * Giao tiếp hiển thị I2C:Màn hình OLED SSD1306 kết nối với ESP32 qua chân GPIO21 (SDA) và GPIO22 (SCL).
       * Nguồn cấp 3.3V và GND được lấy trực tiếp từ các chân nguồn của ESP32.
       * Bộ phận điều khiển:Một nút nhấn được kết nối với chân GPIO4 để thực hiện tính năng chuyển đổi chế độ đo.
  
 2. Xử lý phần mềm và Thuật toán
   * Phần mềm được thiết kế để tối ưu hóa độ chính xác của bộ ADC 12-bit trên ESP32 thông qua các bước:
   * Khởi tạo hệ thống: Thiết lập thư viện Adafruit_SSD1306 cho I2C và cấu hình các chân pinMode cho nút nhấn và ADC.
   * Lưu ý cho việc thiết kế nút bấm:
      * sau khi khai báo chân nút bấm đến phần setup() ta cần chỉnh cho nó về chế độ INPUT_PULLUP thay vì INPUT thông thường bởi khi khai báo INPUT ta phải nối 1 điện trở với chân nút bấm trước khi về chân GPIO để tránh trạng thái Floating, INPUT_PULLUP sẽ kích hoạt một điện trở có sẵn bên trong chip để kéo chân đó lên mức HIGH mặc định.
  
      <img width="665" height="492" alt="Screenshot 2026-04-12 215134" src="https://github.com/user-attachments/assets/33e18641-441e-4659-9932-0f84056c46ae" />
      
      * Về code:
        
       <img width="559" height="193" alt="Screenshot 2026-04-12 214738" src="https://github.com/user-attachments/assets/78ba7352-40d3-42f7-b774-1e23186f8d3c" />

      * Kỹ thuật lấy mẫu: Thay vì đọc một giá trị đơn lẻ, chương trình thực hiện đọc 64 lần liên tiếp và lấy giá trị trung bình.
      * Điều này giúp loại bỏ nhiễu và làm ổn định con số hiển thị trên màn hình.
      * Về việc sử dụng công thức trong kĩ thuật điện tính điện áp nối vào để chuyển đổi thành mẫu ADC tính ra điện trở:
     
        <img width="1033" height="1024" alt="Gemini_Generated_Image_9mcjx89mcjx89mcj" src="https://github.com/user-attachments/assets/60f62a93-0fe1-436f-a15c-91ceab7ae627" />
        
      * Công thức tính điện trở đo được
      
       <img width="395" height="131" alt="Screenshot 2026-04-12 220756" src="https://github.com/user-attachments/assets/c3342d6f-6d1e-456e-b5ea-365eb6447b1b" />

       
      * Giá trị ADC

      
        <img width="438" height="150" alt="Screenshot 2026-04-12 220902" src="https://github.com/user-attachments/assets/77e72ff7-b07d-4107-a844-0a33df9f659b" />

      * Sau đó chuyển đổi dữ liệu sử dụng công thức toán học:
     
       <img width="484" height="147" alt="Screenshot 2026-04-12 220950" src="https://github.com/user-attachments/assets/e0608a74-2a1c-4c18-a35f-75b8de19dd89" />

      * Áp dụng Hệ số hiệu chỉnh để bù đắp cho đặc tính phi tuyến tính của ESP32, đảm bảo sai số thấp nhất.
      * Ngoài ra để đo điện áp ở chế độ điện áp ta cần bấm nút để chuyển lại chế độ đo áp, việc đo điện áp đơn giản hơn so với đo điện trở không cần điện trở mẫu chỉ cần dây đỏ + và chân đen - đấu trực tiếp vào vị trí cần đo
      * Cảnh báo an toàn: Do trên ESP32 chỉ sử dụng điện áp tối đa đến 3.3V nên việc đo điện áp cao hơn sẽ cực kì nguy hiểm gây hỏng chip, để đảm bảo an toàn ta hay sử dụng các modul chuyên dụng để thay đổi điện áp đo an toàn. Còn với việc học tập để tận dụng tối đa khả năng đọc ADC mà không tốn nhiều chi phí ta có thể sử dụng ESP32 để đo áp <3.3V hoặc sử dụng Adrunio có thể đo được điện áp <5V.
# 💎 Kết quả 
  ![z7716042699872_9a72740c4d3ad3730f162f772874d8e9](https://github.com/user-attachments/assets/6eb6f385-009f-4ba7-95a5-efe3106a1006)
  ![z7716042691230_51affcfee0bffc5749a97acb38eb92a6](https://github.com/user-attachments/assets/d039147c-4d1c-4620-9e43-3f81e94ebda4)
  ![z7716042692215_7896b5b049b080c4da5bbb066ab3572c](https://github.com/user-attachments/assets/37a427f1-df17-415d-9d69-57dae2d68be7)

# 📝 Học được gì từ project 

1. Hiểu sâu về đặc tính ADC của ESP32 Độ phân giải và Thực tế: Mặc dù ESP32 có ADC 12-bit 2^12 = 4096, nhưng thực tế dải đo không hoàn toàn tuyến tính.
     * Xử lý nhiễu: Tín hiệu Analog rất dễ bị nhiễu bởi môi trường.
     * Việc áp dụng kỹ thuật Oversampling là bắt buộc để có một con số hiển thị ổn định, không bị nhảy liên tục.

2. Giao thức I2C giúp tối ưu hóa kết nối: Tôi đã hiểu cách thức hoạt động của bus I2C chỉ với 2 dây SDA và SCL để điều khiển màn hình OLED.
     * Điều này giúp tiết kiệm tài nguyên chân GPIO cho các mục đích khác.
     * Quản lý thư viện: Cách tích hợp và sử dụng các thư viện phần cứng như Adafruit_SSD1306 để thiết kế giao diện trực quan.

3. Quy trình phát triển dự án chuẩn mô phỏng trước khi lắp đặt:
    * Sử dụng các công cụ như Wokwi giúp kiểm tra tính đúng đắn của logic code và sơ đồ nối dây, giảm thiểu rủi ro làm hỏng linh kiện thật.
    * Tư duy lập trình có cấu trúc: Chia nhỏ chương trình thành các tab (.ino) riêng biệt giúp mã nguồn dễ quản lý, bảo trì và mở rộng sau này.
# 🧐 Nhận xét và Đánh giá 
* ✅Điểm mạnh*
Tốc độ xử lý cực nhanh: Với xung nhịp lên đến 240MHz, ESP32 xử lý các thuật toán trung bình mẫu và xuất dữ liệu ra OLED gần như không có độ trễ.
Kết nối linh hoạt: Tích hợp sẵn Wi-Fi và Bluetooth, giúp dự án này dễ dàng nâng cấp lên thành một trạm đo lường IoT.
Giá thành và hiệu năng: Là dòng chip rẻ nhưng sở hữu ADC 12-bit, vượt xa các dòng Arduino truyền thống thường chỉ 10-bit.
* ❌Điểm yếu* 
Tính phi tuyến tính của ADC: Đây là điểm yếu lớn nhất. ADC của ESP32 thường bị "mù" ở hai đầu dải điện áp và có đường cong đáp ứng không thẳng, gây sai số đáng kể nếu không hiệu chuẩn phần mềm.
Nhiễu nội tại: Bộ ADC của ESP32 khá nhạy cảm với nhiễu từ các module Wi-Fi/Bluetooth đang hoạt động, đòi hỏi phải lọc nhiễu kỹ càng bằng tụ điện hoặc thuật toán.
# 💡 Gợi ý nâng cấp
Nếu bạn cần một dự án đo lường yêu cầu độ chính xác cực cao máy đo y tế, cân điện tử chính xác, bạn có thể cân nhắc:
STM32 Series: Có bộ ADC ổn định và tuyến tính hơn rất nhiều so với ESP32.
Sử dụng ADC rời ADS1115: Thay vì dùng ADC tích hợp của chip, bạn nối ESP32 với module ADS1115 16-bit qua I2C. Đây là giải pháp tối ưu nhất để vừa có tốc độ của ESP32, vừa có độ chính xác tuyệt đối của một chip đo chuyên dụng.
# 👋 Lời kết
Cảm ơn các bạn đã theo dõi dự án ESP32 Digital Ohmmeter của mình. Hy vọng những chia sẻ về cách xử lý ADC và giao tiếp I2C này sẽ giúp ích cho các bạn trong những bước đầu khám phá thế giới vi điều khiển.
Nếu có bất kỳ thắc mắc hay ý tưởng tối ưu nào khác, đừng ngần ngại để lại một Issue hoặc Star cho kho lưu trữ này nhé!
Chúc các bạn có những dự án DIY thú vị!🚀
