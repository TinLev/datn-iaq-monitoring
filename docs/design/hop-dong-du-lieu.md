# Hợp đồng dữ liệu

Phiên bản: **0.1 (bản nháp, chờ hai người chốt)**
Áp dụng cho: firmware (Người A), cloud (Người B), phân tích, bộ giả lập.

Mọi thành phần phải tuân theo file này. **Muốn đổi thì nhắn người kia trước**, rồi cập nhật file, tăng số phiên bản và ghi vào mục "Lịch sử thay đổi".

## Các điểm còn mở (cần chốt, hiện đang dùng giá trị đề xuất)

| # | Câu hỏi | Giá trị đang dùng | Chốt |
|---|---|---|---|
| 1 | Có gửi `pm1` và `pm10` không | Có | [ ] |
| 2 | Chu kỳ gửi | 10 giây | [ ] |
| 3 | Có gửi `rssi` không | Có | [ ] |

## 1. MQTT

| Mục | Giá trị |
|---|---|
| Giao thức | MQTT 3.1.1 |
| `node_id` | `node1`, `node2` (chữ thường, không dấu cách) |
| Xác thực | Tên đăng nhập + mật khẩu (không ghi vào repo, dùng `.env` / `secrets.h`) |

### Topic

| Topic | Hướng | QoS | Retain | Nội dung |
|---|---|---|---|---|
| `iaq/<node_id>/data` | Nút → Cloud | 1 | Không | Bản tin đo (mục 2) |
| `iaq/<node_id>/status` | Nút → Cloud | 1 | **Có** | Chuỗi `online` hoặc `offline` |

### Trạng thái và LWT

- Khi kết nối thành công, nút gửi `online` lên `iaq/<node_id>/status` (retain).
- Khi kết nối MQTT, đăng ký **Last Will**: topic `iaq/<node_id>/status`, nội dung `offline`, QoS 1, retain.
- Cloud coi nút là offline khi nhận `offline`, hoặc khi quá **3 chu kỳ** (30 giây) không có bản tin `data`.

## 2. Bản tin đo `iaq/<node_id>/data`

Định dạng: JSON UTF-8, một đối tượng phẳng, mã hóa nhỏ gọn (không xuống dòng).

| Trường | Kiểu | Đơn vị | Bắt buộc | Mô tả |
|---|---|---|---|---|
| `node_id` | string | | Có | Trùng với `<node_id>` trong topic |
| `ts` | integer | giây Unix, UTC | Có | Thời điểm đo, lấy từ NTP trên nút |
| `seq` | integer | | Có | Số thứ tự bản tin, tăng 1 mỗi lần gửi, quay về 0 khi nút khởi động lại |
| `pm1` | number | µg/m³ | Có | PM1.0, **đã lọc** |
| `pm25` | number | µg/m³ | Có | PM2.5, **đã lọc** |
| `pm10` | number | µg/m³ | Có | PM10, **đã lọc** |
| `co2` | number | ppm | Có | CO₂, **đã lọc** |
| `temp` | number | °C | Có | Nhiệt độ, **đã lọc** |
| `hum` | number | %RH | Có | Độ ẩm tương đối, **đã lọc** |
| `pres` | number | hPa | Có | Áp suất, **đã lọc** |
| `pm25_raw` | number | µg/m³ | Có | PM2.5 **thô** (trước lọc) |
| `co2_raw` | number | ppm | Có | CO₂ thô |
| `temp_raw` | number | °C | Có | Nhiệt độ thô |
| `hum_raw` | number | %RH | Có | Độ ẩm thô |
| `rssi` | integer | dBm | Có | Cường độ Wi-Fi tại thời điểm gửi |

Số thực lấy tối đa **2 chữ số thập phân**.

### Giá trị thiếu hoặc lỗi

- Nếu một cảm biến không đọc được, gửi trường tương ứng với giá trị **`null`**. Không gửi `0`, không bỏ trường.
- Bản tin không bao giờ bị bỏ chỉ vì một cảm biến hỏng.

### Dải giá trị hợp lệ (cloud kiểm tra)

| Trường | Tối thiểu | Tối đa |
|---|---|---|
| `pm1`, `pm25`, `pm10` (và `pm25_raw`) | 0 | 1000 |
| `co2`, `co2_raw` | 300 | 5000 |
| `temp`, `temp_raw` | -40 | 85 |
| `hum`, `hum_raw` | 0 | 100 |
| `pres` | 300 | 1100 |
| `rssi` | -100 | 0 |

Ngoài dải thì cloud **ghi log và không ghi vào cơ sở dữ liệu** giá trị đó (các trường khác vẫn ghi). Ràng buộc phụ: `pm1 ≤ pm25 ≤ pm10`. Vi phạm thì ghi log cảnh báo, vẫn lưu.

### Ví dụ hợp lệ

```json
{"node_id":"node1","ts":1792670400,"seq":1042,"pm1":8.2,"pm25":14.6,"pm10":19.3,"co2":612,"temp":27.4,"hum":58.1,"pres":1008.7,"pm25_raw":15.0,"co2_raw":620,"temp_raw":27.5,"hum_raw":58.3,"rssi":-61}
```

### Ví dụ có một cảm biến lỗi (CO₂ không đọc được)

```json
{"node_id":"node1","ts":1792670410,"seq":1043,"pm1":8.1,"pm25":14.5,"pm10":19.2,"co2":null,"temp":27.4,"hum":58.1,"pres":1008.7,"pm25_raw":14.9,"co2_raw":null,"temp_raw":27.5,"hum_raw":58.2,"rssi":-62}
```

### Ví dụ không hợp lệ (cloud loại)

```json
{"node_id":"node9","ts":"hôm nay","pm25":-5}
```

Lỗi: `node_id` không thuộc danh sách, `ts` sai kiểu, thiếu trường bắt buộc, giá trị ngoài dải.

## 3. Chu kỳ

| Mục | Giá trị |
|---|---|
| Chu kỳ lấy mẫu cảm biến | 1–2 giây (đủ cho bộ lọc) |
| Chu kỳ gửi `data` | **10 giây** |
| Bản tin gửi là giá trị | Đã lọc tại thời điểm gửi, kèm giá trị thô tương ứng |

## 4. Ánh xạ sang InfluxDB (cloud)

| Mục | Giá trị |
|---|---|
| Bucket | `iaq` |
| Measurement | `air` |
| Tag | `node_id` |
| Field | Mọi trường số ở mục 2, trừ `node_id`, `ts` |
| Timestamp | `ts` (giây) |
| Giá trị `null` | Không ghi field đó |
| Tên field thô | Giữ nguyên hậu tố `_raw` |

Bản tin `status` ghi vào measurement `node_status` (tag `node_id`, field `online` kiểu boolean).

## 5. Định dạng CSV chuẩn (dữ liệu giả, xuất file, phân tích)

- Cột trùng **đúng thứ tự và tên** với bảng ở mục 2, dòng đầu là tên cột.
- `ts` là giây Unix UTC. Giá trị thiếu để trống.
- Mã hóa UTF-8, phân cách bằng dấu phẩy, dấu thập phân là dấu chấm.

```csv
node_id,ts,seq,pm1,pm25,pm10,co2,temp,hum,pres,pm25_raw,co2_raw,temp_raw,hum_raw,rssi
node1,1792670400,1042,8.2,14.6,19.3,612,27.4,58.1,1008.7,15.0,620,27.5,58.3,-61
node1,1792670410,1043,8.1,14.5,19.2,,27.4,58.1,1008.7,14.9,,27.5,58.2,-62
```

## 6. Quy tắc chung

- Đơn vị cố định như bảng trên, không đổi giữa các thành phần.
- Thời gian luôn UTC; chuyển múi giờ chỉ khi hiển thị.
- `seq` dùng để phát hiện mất gói: cloud tính số bản tin thiếu từ khoảng cách `seq`, và hiểu `seq` giảm về 0 là nút khởi động lại.
- Mọi thành phần phải **bỏ qua trường lạ** thay vì lỗi, để thêm trường sau này không làm vỡ hệ thống.

## 7. Lịch sử thay đổi

| Phiên bản | Ngày | Thay đổi | Người |
|---|---|---|---|
| 0.1 | 22/10/2026 | Bản nháp đầu tiên | |
