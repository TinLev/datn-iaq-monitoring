// Giao diện chung cho nguồn dữ liệu cảm biến.
// Hiện tại cắm nguồn giả; khi có phần cứng thì thay bằng driver thật,
// phần DSP và MQTT phía sau không phải sửa.
#pragma once

struct Reading {
  float pm1, pm25, pm10;  // µg/m³
  float co2;              // ppm
  float temp;             // °C
  float hum;              // %RH
  float pres;             // hPa
  bool  valid;            // false nếu không đọc được
};

class ISensorSource {
 public:
  virtual ~ISensorSource() {}
  virtual bool begin() = 0;
  virtual bool read(Reading &out) = 0;  // true nếu đọc thành công
};

// TODO (Người A):
//  - SimSensorSource: sinh hoặc đọc dữ liệu giả (ví dụ từ biến trở trong Wokwi).
//  - RealSensorSource: driver PMS5003 + MH-Z19B + BME280 khi có phần cứng.
