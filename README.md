# Hệ thống giám sát chất lượng không khí trong nhà (IoT + Cloud + DSP + Dự báo)

Đồ án tốt nghiệp: Nghiên cứu, thiết kế và chế tạo hệ thống giám sát chất lượng không khí trong nhà ứng dụng IoT và điện toán đám mây, tích hợp bộ lọc DSP và thuật toán dự báo chuỗi thời gian phục vụ cảnh báo sớm.

## Cấu trúc thư mục

| Thư mục | Nội dung |
|---|---|
| `docs/thesis/` | Luận văn, mỗi chương một file |
| `docs/design/` | Sơ đồ khối, sơ đồ nguyên lý, đặc tả JSON và topic MQTT |
| `docs/experiments/` | Kế hoạch, nhật ký và kết quả thí nghiệm |
| `docs/references/` | Tài liệu tham khảo, ghi chú đọc |
| `hardware/` | BOM, sơ đồ đấu nối, ảnh |
| `firmware/` | Mã ESP32: `sensors/`, `dsp/`, `comm/`, `app/` |
| `cloud/` | Broker, ingestion, CSDL, dashboard, bộ giả lập nút đo |
| `analytics/` | Tiền xử lý, hiệu chuẩn, dự báo, cảnh báo, đánh giá |
| `data/` | Dữ liệu (thô và đã xử lý không đưa lên Git) |

## Bí mật

Không commit mật khẩu hay token. Dùng `firmware/app/secrets.example.h` và `.env.example` làm mẫu.

## Quy ước làm việc

- Nhánh: `feat/firmware-*` (A), `feat/cloud-*` (B), `docs/chuong-*`.
- Commit: `feat:`, `fix:`, `docs:`, `data:`, `chore:`.
- Mọi thay đổi vào `main` qua Pull Request, người còn lại duyệt.

## Tiến độ

Xem [docs/README.md](docs/README.md).
