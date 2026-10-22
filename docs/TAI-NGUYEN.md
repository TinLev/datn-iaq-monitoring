# Tổng hợp tài nguyên cần chuẩn bị

Số lượng tính cho **2 nút đo**. Giá chỉ là ước lượng, cần kiểm tra lại khi mua. Khi mua hoặc cài xong, tick `[x]` và ghi tên người phụ trách.

## A. Phần cứng

### A1. Bắt buộc (mỗi nút 1 bộ)

| Đã có | Linh kiện | SL (2 nút) | Ước tính / cái | Người mua | Lưu ý |
|---|---|---|---|---|---|
| [ ] | ESP32 DevKit (WROOM-32) | 2 (+1 dự phòng) | 100–150k | | Xem loại chip USB (CP210x hoặc CH340) để cài driver |
| [ ] | PMS5003 (bụi PM1/2.5/10) | 2 | 300–450k | | Cấp 5V, TX/RX mức 3.3V, thường kèm cáp/adapter |
| [ ] | MH-Z19B (CO₂, NDIR) | 2 | 400–600k | | Cấp 5V, UART 3.3V, khởi động khoảng 3 phút |
| [ ] | BME280 (nhiệt độ, độ ẩm, áp suất) | 2 | 60–100k | | Mua **BME280**, không phải BMP280 |
| [ ] | Nguồn 5V 2A + cáp | 2 | 50–80k | | PMS5003 có quạt, hút dòng khi khởi động |
| [ ] | Dây jumper (đực-cái, cái-cái) | 2 bộ | 20–30k | | |
| [ ] | Breadboard | 2 | 30–50k | | Dùng giai đoạn thử |

### A2. Nên có

| Đã có | Linh kiện | SL | Ước tính | Người mua | Lý do |
|---|---|---|---|---|---|
| [ ] | Tụ 100–470 µF | vài cái | 10k | | Chống sụt áp khi quạt PMS5003 chạy |
| [ ] | Hộp nhựa / vỏ in 3D | 2 | 30–100k | | Cố định cảm biến, chừa đường lưu thông khí |
| [ ] | **Thiết bị tham chiếu** (mượn hoặc dùng trạm đo công khai) | 1 | tùy | | Bắt buộc về mặt nghiên cứu cho mục tiêu hiệu chuẩn |
| [ ] | Đồng hồ vạn năng | 1 | 100–300k | | Đo điện áp, kiểm tra thông mạch |
| [ ] | Cáp USB **data** (không phải cáp chỉ sạc) | 2 | 30–50k | | Cáp chỉ sạc là lỗi rất hay gặp khi máy không nhận board |

### A3. Tùy chọn

| Linh kiện | Khi nào cần |
|---|---|
| SGP30 (TVOC) | Muốn thêm một chất ô nhiễm |
| Màn hình OLED SSD1306 | Hiển thị cục bộ khi demo |
| Logic analyzer rẻ tiền | Gỡ lỗi UART/I²C |
| Relay + quạt | Chỉ khi làm hướng phát triển điều khiển |
| Raspberry Pi | Chạy cloud liên tục thay máy cá nhân |
| PCB hàn sẵn | Muốn sản phẩm gọn hơn |

**Ngân sách tham khảo:** khoảng 1,1–1,7 triệu đồng mỗi nút cho nhóm A1 + A2. Nhân đôi phần nút đo cho 2 nút, không nhân đôi thiết bị tham chiếu và đồng hồ vạn năng.

## B. Công cụ phần mềm

### B1. Firmware (Người A)

| Đã cài | Công cụ | Mục đích | Mức |
|---|---|---|---|
| [ ] | VS Code + PlatformIO (hoặc Arduino IDE) | Viết và nạp code ESP32 | Bắt buộc |
| [ ] | Driver USB (CP210x / CH340) | Máy nhận board | Bắt buộc |
| [ ] | Thư viện MQTT (`PubSubClient`) và thư viện cảm biến | Giao tiếp | Bắt buộc |
| [ ] | Serial Monitor / Plotter | Xem dữ liệu thô và đã lọc | Bắt buộc |
| [ ] | Wokwi | Giả lập khi chưa có board | Nên có |

### B2. Cloud (Người B)

| Đã cài | Công cụ | Mục đích | Mức |
|---|---|---|---|
| [ ] | Docker + Docker Compose | Chạy Mosquitto, InfluxDB, Grafana | Rất nên có |
| [ ] | Mosquitto | MQTT broker | Bắt buộc |
| [ ] | InfluxDB (hoặc TimescaleDB) | Cơ sở dữ liệu chuỗi thời gian | Bắt buộc |
| [ ] | Grafana | Dashboard | Bắt buộc |
| [ ] | MQTTX hoặc MQTT Explorer | Gỡ lỗi MQTT | Rất nên có |
| [ ] | Telegram Bot (BotFather) | Cảnh báo | Bắt buộc |
| [ ] | Máy chạy liên tục (máy cá nhân, Raspberry Pi hoặc VPS) | Thu dữ liệu nhiều ngày | Bắt buộc |

### B3. Phân tích và học máy

| Đã cài | Công cụ | Mục đích | Mức |
|---|---|---|---|
| [ ] | Python 3.12 + `.venv` | Ngôn ngữ chính | Bắt buộc |
| [ ] | JupyterLab | Thử nghiệm, vẽ đồ thị | Bắt buộc |
| [ ] | pandas, numpy, scipy, matplotlib | Dữ liệu và biểu đồ | Bắt buộc |
| [ ] | scikit-learn | Hồi quy hiệu chuẩn, chỉ tiêu | Bắt buộc |
| [ ] | statsmodels | ARIMA, kiểm định tính dừng | Bắt buộc |
| [ ] | prophet | Mô hình Prophet | Bắt buộc |
| [ ] | TensorFlow/Keras hoặc PyTorch | LSTM/GRU | Chỉ nếu làm LSTM |
| [ ] | paho-mqtt, influxdb-client, requests | Nhận MQTT, ghi InfluxDB, gọi Telegram | Bắt buộc |

Lệnh cài thư viện Python (chạy trong `.venv`):

```bash
pip install jupyterlab pandas numpy scipy matplotlib scikit-learn statsmodels prophet paho-mqtt influxdb-client requests
```

### B4. Làm việc nhóm và luận văn

| Đã cài | Công cụ | Mục đích | Mức |
|---|---|---|---|
| [x] | Git + GitHub + `gh` | Quản lý mã và nhóm | Bắt buộc |
| [ ] | Word (khuyến nghị) hoặc LaTeX/Overleaf | Soạn luận văn | Chọn 1 |
| [ ] | Zotero | Quản lý trích dẫn | Rất nên có |
| [ ] | draw.io | Sơ đồ khối, lưu đồ | Bắt buộc |
| [ ] | KiCad hoặc Fritzing | Sơ đồ nguyên lý, đấu nối | Nên có |
| [ ] | PowerPoint / Google Slides | Slide bảo vệ | Bắt buộc |

## C. Thứ tự ưu tiên

1. **Đặt hàng ngay** nhóm A1 và cáp USB data. Hàng về chậm là rủi ro lớn nhất.
2. **Tìm thiết bị tham chiếu** song song với việc đặt hàng.
3. **Cài công cụ** trong tuần 1: VS Code, Python 3.12, Docker, Zotero, draw.io.
4. **Khi hàng về:** kiểm tra từng linh kiện ngay bằng đồng hồ vạn năng, thử từng cảm biến riêng.

## D. Quyết định còn mở (cần hai người thống nhất)

- [ ] Word hay LaTeX
- [ ] InfluxDB hay TimescaleDB
- [ ] Chạy cloud ở máy nào (máy cá nhân, Raspberry Pi hay VPS)
- [ ] Có làm LSTM hay không (phụ thuộc lượng dữ liệu thu được)
- [ ] Ai làm A (edge), ai làm B (cloud)
