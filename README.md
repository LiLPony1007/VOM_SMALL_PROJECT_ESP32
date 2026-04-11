# VOM_SMALL_PROJECT_EPS32
📝 Giới thiệu dự án
Dự án này tập trung vào việc xây dựng một thiết bị đo điện trở dựa trên vi điều khiển ESP32. Mục tiêu chính là nghiên cứu cách thức hoạt động của bộ chuyển đổi Analog-to-Digital (ADC) 12-bit trên ESP32, đồng thời tích hợp hiển thị dữ liệu thời gian thực qua giao thức I2C trên màn hình OLED.

Điểm đặc biệt của dự án là việc phân tích và xử lý sai số phi tuyến tính của ESP32 – một thách thức phổ biến khi làm việc với các dòng chip giá rẻ nhưng có hiệu năng xử lý mạnh mẽ này.

🛠 Phần cứng và Vật liệu 
Dưới đây là danh sách các linh kiện được sử dụng trong dự án:

1. Vi điều khiển trung tâm
ESP32 DevKit V1: Độ phân giải ADC: 12-bit (0 - 4095).

Hỗ trợ WiFi/Bluetooth.

Điện áp hoạt động: 3.3V.

2. Thiết bị hiển thị
Màn hình OLED 0.96 inch:

Công nghệ: SSD1306.

Giao thức: I2C.

Độ phân giải: 128x64 pixel.
CÁC KHÁI NIỆM CẦN BIẾT
1. ADC (Analog-to-Digital Converter)ADC là bộ chuyển đổi tín hiệu tương tự sang tín hiệu số.
    Định nghĩa: Trong thế giới thực, các đại lượng như nhiệt độ, ánh sáng hay điện áp là liên tục. ADC ghi các mức điện áp đó và biến chúng thành các con số mà vi điều khiển như ESP32 có thể hiểu và xử lý được.
   Thông số quan trọng: Độ phân giải. Với ESP32 là 12-bit, nghĩa là nó chia dải điện áp từ 0V đến 3.3V thành 2^12 = 4096 mức nhỏ để đo lường.
3. I2C (Inter-Integrated Circuit)I2C là một giao thức giao tiếp nối tiếp đồng bộ giữa các vi mạch.
    Định nghĩa: Đây là một cách thức giao tiếp giữa vi điều khiển gọi là Master và các thiết bị ngoại vi như màn hình OLED, cảm biến là Slaves chỉ thông qua 2 sợi dây duy nhất:
   +SDA (Serial Data): Đường truyền dữ liệu hai chiều.
   +SCL (Serial Clock): Đường truyền tín hiệu nhịp xung để đồng bộ thời gian.
   Ưu điểm: Cho phép kết nối nhiều thiết bị trên cùng một bus dây bằng cách phân biệt qua địa chỉ riêng biệt của mỗi thiết bị, giúp tiết kiệm tối đa chân cắm cho ESP32.
   <img width="600" height="167" alt="Screenshot 2026-04-11 224838" src="https://github.com/user-attachments/assets/7db5712e-5efc-4c3b-a873-b598b0c7e67c" />
   
