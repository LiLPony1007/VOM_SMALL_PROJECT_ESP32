# VOM_SMALL_PROJECT_EPS32
📝 Giới thiệu dự án
![z7716042692885_a50d0d34f0f6eb07ac7dab6c8332fa82](https://github.com/user-attachments/assets/770851da-dd9c-4fac-a185-180c0f3a0bf8)


Dự án này tập trung vào việc xây dựng một thiết bị đo điện trở dựa trên vi điều khiển ESP32. Mục tiêu chính là nghiên cứu cách thức hoạt động của bộ chuyển đổi Analog-to-Digital (ADC) 12-bit trên ESP32, đồng thời tích hợp hiển thị dữ liệu thời gian thực qua giao thức I2C trên màn hình OLED.

Điểm đặc biệt của dự án là việc phân tích và xử lý sai số phi tuyến tính của ESP32 – một thách thức phổ biến khi làm việc với các dòng chip giá rẻ nhưng có hiệu năng xử lý mạnh mẽ này.

🛠 Phần cứng và Vật liệu 
Dưới đây là danh sách các linh kiện được sử dụng trong dự án:

![z7716042683275_01e946cb15bc3f0dfebfcf33478da4f0](https://github.com/user-attachments/assets/16263b02-8d6b-4337-83d5-86d27f9404d0)


1. Vi điều khiển trung tâm
ESP32 DevKit V1: Độ phân giải ADC: 12-bit (0 - 4095).

Hỗ trợ WiFi/Bluetooth để dùng treen website.

Điện áp hoạt động: 3.3V.

2. Thiết bị hiển thị
Màn hình OLED 0.96 inch:

Công nghệ: SSD1306.

Giao thức: I2C.

Độ phân giải: 128x64 pixel.
# CÁC KHÁI NIỆM CẦN BIẾT

1. ADC (Analog-to-Digital Converter) là bộ chuyển đổi tín hiệu tương tự sang tín hiệu số.
    Định nghĩa: Trong thế giới thực, các đại lượng như nhiệt độ, ánh sáng hay điện áp là liên tục. ADC ghi các mức điện áp đó và biến chúng thành các con số mà vi điều khiển như ESP32 có thể hiểu và xử lý được.
   Thông số quan trọng: Độ phân giải. Với ESP32 là 12-bit, nghĩa là nó chia dải điện áp từ 0V đến 3.3V thành 2^12 = 4096 mức nhỏ để đo lường.

2. I2C (Inter-Integrated Circuit) là một giao thức giao tiếp nối tiếp đồng bộ giữa các vi mạch.
    Định nghĩa: Đây là một cách thức giao tiếp giữa vi điều khiển gọi là Master và các thiết bị ngoại vi như màn hình OLED, cảm biến là Slaves chỉ thông qua 2 sợi dây duy nhất:
   +SDA (Serial Data): Đường truyền dữ liệu hai chiều.
   +SCL (Serial Clock): Đường truyền tín hiệu nhịp xung để đồng bộ thời gian.
   Ưu điểm: Cho phép kết nối nhiều thiết bị trên cùng một bus dây bằng cách phân biệt qua địa chỉ riêng biệt của mỗi thiết bị, giúp tiết kiệm tối đa chân cắm cho ESP32.
   
   <img width="600" height="167" alt="Screenshot 2026-04-11 224838" src="https://github.com/user-attachments/assets/7db5712e-5efc-4c3b-a873-b598b0c7e67c" />
   
# Thực hiện 

Việc thực hiện dự án được chia làm hai giai đoạn chính: Lắp đặt phần cứng và Xử lý phần mềm.
   
   1. Lắp đặt phần cứng dựa trên mô phỏng

<img width="1259" height="642" alt="Screenshot 2026-04-11 230830" src="https://github.com/user-attachments/assets/f19d6697-6c9f-4290-b864-f66d412105ae" />


   Dựa trên sơ đồ Wokwi, mạch được triển khai với cấu trúc tối ưu:
     +Mạch cầu phân áp: Sử dụng điện trở mẫu 5kOmega.
       Điểm giữa của cầu phân áp được nối vào chân GPIO35 để đọc giá trị Analog.
       Giao tiếp hiển thị I2C:Màn hình OLED SSD1306 kết nối với ESP32 qua chân GPIO21 (SDA) và GPIO22 (SCL).
       Nguồn cấp 3.3V và GND được lấy trực tiếp từ các chân nguồn của ESP32.
       Bộ phận điều khiển:Một nút nhấn được kết nối với chân GPIO4 để thực hiện tính năng chuyển đổi chế độ đo.
  
   2. Xử lý phần mềm và Thuật toán
     +Phần mềm được thiết kế để tối ưu hóa độ chính xác của bộ ADC 12-bit trên ESP32 thông qua các bước:
       Khởi tạo hệ thống: Thiết lập thư viện Adafruit_SSD1306 cho I2C và cấu hình các chân pinMode cho nút nhấn và ADC.
       Kỹ thuật lấy mẫu: Thay vì đọc một giá trị đơn lẻ, chương trình thực hiện đọc 64 lần liên tiếp và lấy giá trị trung bình.
       Điều này giúp loại bỏ nhiễu và làm ổn định con số hiển thị trên màn hình.
       Chuyển đổi dữ liệu:Sử dụng công thức toán học:
                         Rx = R_ref*ADC_raw/(4095 - ADC_raw).
      Áp dụng Hệ số hiệu chỉnh để bù đắp cho đặc tính phi tuyến tính của ESP32, đảm bảo sai số thấp nhất.
# Kết quả 
  ![z7716042699872_9a72740c4d3ad3730f162f772874d8e9](https://github.com/user-attachments/assets/6eb6f385-009f-4ba7-95a5-efe3106a1006)
  ![z7716042691230_51affcfee0bffc5749a97acb38eb92a6](https://github.com/user-attachments/assets/d039147c-4d1c-4620-9e43-3f81e94ebda4)
  ![z7716042692215_7896b5b049b080c4da5bbb066ab3572c](https://github.com/user-attachments/assets/37a427f1-df17-415d-9d69-57dae2d68be7)

# Học được gì từ project 
Sau khi hoàn thành dự án thiết kế Ôm-kế với ESP32, tôi đã đúc kết được những kiến thức và kỹ năng quan trọng sau:

1. Hiểu sâu về đặc tính ADC của ESP32 Độ phân giải và Thực tế: Mặc dù ESP32 có ADC 12-bit 2^12 = 4096, nhưng thực tế dải đo không hoàn toàn tuyến tính.
     Tôi đã học được rằng không thể tin tưởng tuyệt đối vào công thức toán học lý thuyết mà cần có bước Calibration.
     Xử lý nhiễu: Tín hiệu Analog rất dễ bị nhiễu bởi môi trường.
     Việc áp dụng kỹ thuật Oversampling là bắt buộc để có một con số hiển thị ổn định, không bị nhảy liên tục.

3. Làm chủ giao thức I2C Tối ưu hóa kết nối: Tôi đã hiểu cách thức hoạt động của bus I2C chỉ với 2 dây SDA và SCL để điều khiển màn hình OLED.
     Điều này giúp tiết kiệm tài nguyên chân GPIO cho các mục đích khác.
     Quản lý thư viện: Cách tích hợp và sử dụng các thư viện phần cứng như Adafruit_SSD1306 để thiết kế giao diện trực quan.

4. Quy trình phát triển dự án chuẩn mô phỏng trước khi lắp đặt:
    Sử dụng các công cụ như Wokwi giúp kiểm tra tính đúng đắn của logic code và sơ đồ nối dây, giảm thiểu rủi ro làm hỏng linh kiện thật.
    Tư duy lập trình có cấu trúc: Chia nhỏ chương trình thành các tab (.ino) riêng biệt giúp mã nguồn dễ quản lý, bảo trì và mở rộng sau này.
