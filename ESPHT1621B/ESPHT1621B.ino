#define HT1621_CS   10
#define HT1621_WR   11
#define HT1621_DATA 12

void ht1621_send_bits(uint8_t data, uint8_t cnt) {
  for (int i = cnt - 1; i >= 0; i--) {
    digitalWrite(HT1621_WR, LOW);
    digitalWrite(HT1621_DATA, (data >> i) & 1);
    digitalWrite(HT1621_WR, HIGH);
  }
}

void ht1621_cmd(uint8_t cmd) {
  digitalWrite(HT1621_CS, LOW);
  ht1621_send_bits(0b100, 3);
  ht1621_send_bits(cmd, 8);
  ht1621_send_bits(0, 1);
  digitalWrite(HT1621_CS, HIGH);
}

void ht1621_write(uint8_t addr, uint8_t data) {
  digitalWrite(HT1621_CS, LOW);
  ht1621_send_bits(0b101, 3);
  ht1621_send_bits(addr, 6);
  ht1621_send_bits(data, 4);
  digitalWrite(HT1621_CS, HIGH);
}

void setup() {
  pinMode(HT1621_CS, OUTPUT);
  pinMode(HT1621_WR, OUTPUT);
  pinMode(HT1621_DATA, OUTPUT);
  digitalWrite(HT1621_CS, HIGH);
  digitalWrite(HT1621_WR, HIGH);

  delay(100);
  ht1621_cmd(0x01); // RC 256K
  ht1621_cmd(0x03); // LCD on
  ht1621_cmd(0x52); // 1/3 bias, 4 commons

  // Barcha segmentlarni yoqish
  for (int i = 0; i < 32; i++) {
    ht1621_write(i, 0xFF);
  }
}

void loop() {}
