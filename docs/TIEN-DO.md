# Bảng tiến độ đồ án

Làm xong việc nào thì đổi `[ ]` thành `[x]` rồi commit. Cuối mỗi giai đoạn, đếm số ô đã tick để biết tiến độ.

**Người A:** (edge, hiệu chuẩn) &nbsp;|&nbsp; **Người B:** (cloud, dự báo)

---

## Giai đoạn 1. Tổng quan tài liệu và chọn phần cứng (Tuần 1)

- [ ] Chốt phạm vi: số nút, vị trí, chất ô nhiễm, chuẩn AQI, ngân sách
- [ ] Chốt câu hỏi nghiên cứu và 6 mục tiêu có chỉ tiêu
- [ ] Vẽ sơ đồ khối hệ thống
- [ ] Chọn MCU (có bảng so sánh và lý do)
- [ ] Chọn cảm biến (có bảng so sánh và lý do)
- [ ] Tóm tắt datasheet PMS5003, MH-Z19B, BME280
- [ ] Lập BOM và tổng chi phí
- [ ] Đặt mua linh kiện
- [ ] Tìm được thiết bị tham chiếu
- [ ] Đọc và ghi chú tối thiểu 8–10 tài liệu
- [ ] Chốt hợp đồng dữ liệu (topic MQTT, cấu trúc JSON, chu kỳ gửi)
- [ ] Tạo repo, mời đủ hai người, thống nhất quy ước nhánh và commit

## Giai đoạn 2. Firmware nhúng và DSP tại biên (Tuần 1–2)

- [ ] Kiểm tra từng linh kiện khi nhận hàng
- [ ] Đọc được PMS5003 (kiểm tra checksum)
- [ ] Đọc được MH-Z19B
- [ ] Đọc được BME280
- [ ] Kiểm tra hợp lệ dữ liệu (ngoài dải đo, lỗi khung)
- [ ] Cài Median filter
- [ ] Cài Moving Average hoặc EMA
- [ ] (Tùy chọn) Cài Kalman 1 chiều
- [ ] Gửi song song giá trị thô và đã lọc
- [ ] Đồng bộ thời gian (NTP)
- [ ] Tự kết nối lại Wi-Fi/MQTT, watchdog, đệm dữ liệu khi mất mạng
- [ ] Đồ thị trước/sau lọc và so sánh bộ lọc (phương sai, SNR, độ trễ)
- [ ] Nút 1 chạy ổn định
- [ ] Nút 2 chạy ổn định

## Giai đoạn 3. IoT và cloud (Tuần 1–3)

- [ ] Dựng Mosquitto, có xác thực
- [ ] Viết bộ giả lập nút đo (dữ liệu có xu hướng, nhiễu, spike, sự kiện)
- [ ] Viết dịch vụ ingestion, ghi vào InfluxDB
- [ ] Thiết kế lược đồ dữ liệu và chính sách lưu trữ
- [ ] Dashboard Grafana (AQI, từng chỉ số, so sánh 2 nút)
- [ ] Dịch vụ tự khởi động lại sau sự cố
- [ ] Giám sát nút online/offline (LWT)
- [ ] Nút đo thật gửi được dữ liệu lên cloud
- [ ] Đo độ trễ đầu-cuối và tỉ lệ mất gói
- [ ] **Bắt đầu thu dữ liệu liên tục** (muộn nhất đầu tuần 2)
- [ ] Thu đủ 10–14 ngày dữ liệu

## Giai đoạn 4. Hiệu chuẩn, dự báo và cảnh báo sớm (Tuần 3–4)

- [ ] Đợt hiệu chuẩn với thiết bị tham chiếu
- [ ] Mô hình hiệu chuẩn và kiểm chứng trên tập riêng
- [ ] Sự kiện có kiểm soát (nấu ăn, đốt hương, mở cửa sổ) và nhật ký gán nhãn
- [ ] Tiền xử lý: dữ liệu thiếu, ngoại lai, lấy mẫu lại
- [ ] Chia train/validation/test theo thời gian
- [ ] Baseline persistence
- [ ] ARIMA
- [ ] Prophet
- [ ] LSTM/GRU (nếu đủ dữ liệu)
- [ ] Định nghĩa sự kiện cảnh báo (vượt ngưỡng T trong H phút) và ngưỡng
- [ ] Logic cảnh báo có hysteresis và giới hạn tần suất
- [ ] Tích hợp Telegram Bot
- [ ] Cảnh báo chạy thử đầu-cuối

## Giai đoạn 5. Tích hợp, đánh giá, hoàn thiện (Tuần 4)

- [ ] Chạy thí nghiệm bóc tách C0, C1, C2, C3
- [ ] RMSE/MAE theo mô hình và khoảng dự báo (15/30/60 phút)
- [ ] Precision, recall, F1, false alarm rate, lead time của cảnh báo
- [ ] So sánh với cảnh báo chỉ dựa ngưỡng
- [ ] Kiểm thử độ ổn định (chạy dài ngày, ngắt mạng thử)
- [ ] Đối chiếu từng mục tiêu: đạt hay chưa
- [ ] Chuẩn bị câu hỏi và trả lời cho buổi bảo vệ
- [ ] Hai người đọc chéo toàn bộ luận văn

---

## Luận văn (mỗi chương: người chính viết, người phản biện đọc)

| Chương | Người chính | Người phản biện | Viết xong bản nháp | Đã phản biện | Hoàn chỉnh |
|---|---|---|---|---|---|
| 1. Mở đầu | | | [ ] | [ ] | [ ] |
| 2. Tổng quan, chất lượng không khí, cảm biến | | | [ ] | [ ] | [ ] |
| 3. Lý thuyết IoT, đám mây, DSP | | | [ ] | [ ] | [ ] |
| 4. Lý thuyết dự báo và cảnh báo sớm | | | [ ] | [ ] | [ ] |
| 5. Thiết kế và chế tạo nút đo | | | [ ] | [ ] | [ ] |
| 6. Thiết kế hệ thống IoT và đám mây | | | [ ] | [ ] | [ ] |
| 7. Phương pháp thực nghiệm | | | [ ] | [ ] | [ ] |
| 8. Kết quả và thảo luận | | | [ ] | [ ] | [ ] |
| 9. Kết luận và hướng phát triển | | | [ ] | [ ] | [ ] |

## Phần cuối luận văn

- [ ] Tóm tắt và Abstract
- [ ] Mục lục, danh mục hình, bảng, từ viết tắt
- [ ] Tài liệu tham khảo (25–40 nguồn)
- [ ] Phụ lục A: thông số và datasheet
- [ ] Phụ lục B: sơ đồ nguyên lý
- [ ] Phụ lục C: trích đoạn mã
- [ ] Phụ lục D: số liệu chi tiết
- [ ] Phụ lục E: nhật ký thí nghiệm
- [ ] Slide bảo vệ
- [ ] Nộp bài

## Mốc lớn

- [ ] Hết tuần 1: dashboard hiện dữ liệu giả
- [ ] Hết tuần 2: nút đo thật gửi dữ liệu và bắt đầu thu
- [ ] Hết tuần 3: có tập dữ liệu và baseline dự báo
- [ ] Hết tuần 4: bảng kết quả hoàn chỉnh, nộp báo cáo
