# Firmware nút đo (ESP32)

Khung dự án PlatformIO + Wokwi. **Chưa build, chưa chạy thử** vào thời điểm tạo. Người làm phải kiểm tra bước đầu.

## Cấu trúc

| Thư mục/file | Nội dung |
|---|---|
| `platformio.ini` | Cấu hình build. `esp32dev` cho board, `native` để test bộ lọc trên máy |
| `app/main.cpp` | Chương trình chính (chỉ có khung và TODO) |
| `sensors/sensor_source.h` | Giao diện nguồn cảm biến (giả hoặc thật) |
| `dsp/` | Bộ lọc Median, MA/EMA, Kalman |
| `comm/` | Wi-Fi, NTP, MQTT, đóng gói JSON |
| `diagram.json`, `wokwi.toml` | Mạch ảo cho Wokwi |
| `app/secrets.example.h` | Mẫu bí mật. Sao chép thành `secrets.h` (đã bị `.gitignore` chặn) |

## Chạy lần đầu

1. Cài VS Code, tiện ích **PlatformIO IDE** và tiện ích **Wokwi**.
2. Mở thư mục `firmware/` trong VS Code (đúng thư mục chứa `platformio.ini`).
3. Biên dịch: `pio run`. Lần đầu sẽ tải nền tảng và thư viện, cần mạng.
4. Mở `diagram.json` để Wokwi dựng mạch ảo, rồi bấm chạy. Mở Serial Monitor xem log.

## Cần kiểm tra khi chạy lần đầu

- `diagram.json`: tên linh kiện (`board-esp32-devkit-c-v4`) và tên chân (`34`, `35`, `32`, `33`, `GND.1`, `3V3`) soạn theo trí nhớ về Wokwi, **có thể lệch**. Nếu Wokwi báo lỗi, mở trình soạn thảo mạch của Wokwi, nối lại bằng tay rồi chép JSON ngược vào file.
- Wokwi **không có sẵn** BME280, PMS5003, MH-Z19B (theo tài liệu chính thức, chưa kiểm tra trực tiếp danh mục đầy đủ). Vì vậy mạch ảo chỉ dùng biến trở làm nguồn giả. Driver cảm biến thật chỉ kiểm chứng được khi có phần cứng.
- Wokwi Wi-Fi ảo (`Wokwi-GUEST`) ra Internet, **không thấy broker chạy trên laptop**. Khi thử MQTT dùng broker công khai và không gửi dữ liệu nhạy cảm.
- Phiên bản thư viện trong `lib_deps` có thể cần chỉnh nếu PlatformIO báo không tìm thấy.
- Nếu Wokwi yêu cầu giấy phép cho extension VS Code, đăng ký tài khoản miễn phí.
- Bốn biến trở thay cho cảm biến trong lúc chưa có hàng:

| Biến trở | Chân ESP32 | Đại diện cho |
|---|---|---|
| `pot_pm` | GPIO34 | PM2.5 (PMS5003) |
| `pot_co2` | GPIO35 | CO₂ (MH-Z19B) |
| `pot_temp` | GPIO32 | Nhiệt độ (BME280) |
| `pot_hum` | GPIO33 | Độ ẩm (BME280) |

Các chân này thuộc ADC1, dùng được cùng lúc với Wi-Fi.

## Việc kế tiếp (Người A)

1. Đọc bốn biến trở bằng ADC, in giá trị ra Serial.
2. Viết nguồn cảm biến giả theo `ISensorSource`, quy đổi giá trị ADC sang đơn vị thật (µg/m³, ppm, °C, %RH).
3. Viết bộ lọc trong `dsp/` và test bằng `pio test -e native`.
4. Gửi JSON theo hợp đồng dữ liệu qua MQTT.
