// Khung chương trình nút đo. Chỉ có bộ khung; phần logic do người làm tự viết.
#include <Arduino.h>

#include "sensors/sensor_source.h"

// Chu kỳ theo hợp đồng dữ liệu (docs/design/hop-dong-du-lieu.md)
static const uint32_t SAMPLE_PERIOD_MS = 1000;   // lấy mẫu
static const uint32_t PUBLISH_PERIOD_MS = 10000; // gửi

void setup() {
  Serial.begin(115200);
  Serial.println("IAQ node: khoi dong");

  // TODO: khởi tạo nguồn cảm biến (giả hoặc thật) qua ISensorSource
  // TODO: khởi tạo bộ lọc (dsp/)
  // TODO: kết nối Wi-Fi, NTP, MQTT (comm/)
}

void loop() {
  // TODO mỗi SAMPLE_PERIOD_MS:
  //   1. đọc cảm biến -> Reading
  //   2. kiểm tra hợp lệ (ngoài dải thì coi là null)
  //   3. đưa qua chuỗi lọc: Median -> MA/EMA (-> Kalman)
  // TODO mỗi PUBLISH_PERIOD_MS:
  //   đóng gói JSON đúng hợp đồng (cả giá trị thô và đã lọc) rồi publish
  // TODO: tự kết nối lại khi mất Wi-Fi/MQTT
  delay(SAMPLE_PERIOD_MS);
}
