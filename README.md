# Sistem Pendeteksi Api & Suhu Berbasis Arduino Uno

Project matkul Mikroprosesor dan Mikrokontroler, FILKOM UB.
Sistem peringatan dini kebakaran skala kecil dengan 4 status: NORMAL, HANGAT, PANAS, dan API.

## Video Demo
[▶ Tonton video demo di sini](https://youtu.be/tRZb-aqycJI?si=kcwWPCmXxr2Md-rx)

## Cara Kerja
Arduino membaca suhu dan kelembapan dari DHT22 serta sinyal api dari flame sensor (analog dan digital).
Status ditampilkan di LCD, sedangkan LED dan buzzer memberi peringatan sesuai kondisi.
Tombol push button bisa mematikan buzzer secara manual (manual override).

| Status | Kondisi | LED | Buzzer |
|---|---|---|---|
| NORMAL | Suhu < 30°C, tidak ada api | Hijau | Mati |
| HANGAT | Suhu 30-39°C | Hijau | Mati |
| PANAS | Suhu ≥ 40°C | Merah | 1000 Hz |
| API | Flame terdeteksi + suhu mendukung | Merah | 1200 Hz |

## Komponen
Arduino Uno R3, DHT22, Flame Sensor IR (analog + digital), LCD 16x2 I2C,
LED merah dan hijau, buzzer pasif, push button, resistor 220Ω, breadboard

## Konsep yang Diterapkan
ADC, PWM (`tone()`), I2C/TWI, digital input pull-up, Serial communication

## Wiring
| Komponen | Pin |
|---|---|
| DHT22 | D2 |
| Flame sensor (analog / digital) | A0 / D8 |
| Push button | D3 (INPUT_PULLUP) |
| LED merah / hijau | D5 / D6 |
| Buzzer pasif | D9 |
| LCD I2C | SDA A4 / SCL A5 |

## Library
- `LiquidCrystal_I2C`
- `DHT sensor library`

## Hasil Pengujian
Setiap kondisi diuji minimal 3 kali, dan semua hasil sesuai logika desain.

| Kondisi | Suhu | Flame Analog | Flame Digital | Output |
|---|---|---|---|---|
| NORMAL | 26,7°C | 820 | HIGH | LED hijau, buzzer off |
| HANGAT | 31,6°C | 760 | HIGH | LED hijau, buzzer off |
| PANAS | 40,3°C | 700 | HIGH | LED merah, buzzer 1000 Hz |
| API | 35,6°C | 210 | LOW | LED merah, buzzer 1200 Hz |

## Kontribusi Saya
Merakit hardware dan wiring rangkaian, serta membantu sebagian kode program ([sebutkan bagian, misal logika LED/buzzer atau tampilan LCD]).

## Tim
Rezky Auliasarie, Agatha Triotama, Afifah Zuriah Mindarini, Adinda Eka Suja Pertiwi, Delvin Nhean Olamina

Dosen pengampu: Agung Setia Budi, S.T., M.T., M.Eng., Ph.D.
