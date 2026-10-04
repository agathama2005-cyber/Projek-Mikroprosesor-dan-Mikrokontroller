```cpp
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>

#define DHTPIN 2
#define DHTTYPE DHT22
#define FLAME_A A0
#define FLAME_D 8
#define BUTTON_PIN 3
#define LED_MERAH 5
#define LED_HIJAU 6#define BUZZER 9

LiquidCrystal_I2C lcd(0x27, 16, 2);
DHT dht(DHTPIN, DHTTYPE);

bool alarmDimatikan = false;
bool apiSebelumnya = false;

void setup() {
    Wire.begin();
    Serial.begin(9600);
    dht.begin();
    lcd.init();
    lcd.backlight();

    pinMode(FLAME_A, INPUT);
    pinMode(FLAME_D, INPUT);
    pinMode(BUTTON_PIN, INPUT_PULLUP);
    pinMode(LED_MERAH, OUTPUT);
    pinMode(LED_HIJAU, OUTPUT);
    pinMode(BUZZER, OUTPUT);

    digitalWrite(LED_MERAH, LOW);
    digitalWrite(LED_HIJAU, LOW);
    noTone(BUZZER);

    lcd.setCursor(0,0);
    lcd.print("Sistem Mulai...");
    delay(1200);
    lcd.clear();
} v
oid loop() {
    float suhu = dht.readTemperature();
    float kelembapan = dht.readHumidity();

    int flameAnalog = analogRead(FLAME_A);
    int flameDigital = digitalRead(FLAME_D);
    bool tombol = (digitalRead(BUTTON_PIN) == LOW);

    if (isnan(suhu) || isnan(kelembapan)) {
        lcd.setCursor(0,0);
        lcd.print("Err Sensor DHT ");
        lcd.setCursor(0,1);
        lcd.print("Cek Kabel!");
        delay(1000);
        return;
    } l
cd.setCursor(0, 0);
    lcd.print("T:");
    lcd.print(suhu, 1);
    lcd.print("C ");

    lcd.setCursor(0, 1);
    lcd.print("H:");
    lcd.print(kelembapan, 0);
    lcd.print("% ");

    bool adaApi = false;

    if (flameAnalog < 300 && suhu > 28)
        adaApi = true;

    if (flameDigital == LOW && suhu > 28)
        adaApi = true;

    if (flameDigital == HIGH && flameAnalog < 600 && suhu > 32)
        adaApi = true;

    if (tombol) {
        alarmDimatikan = true; // Tandai bahwa alarm sudah dimatikan manual
        noTone(BUZZER); // Matikan buzzer langsung
        delay(300); // Debouncing} i
f (adaApi) {
        digitalWrite(LED_MERAH, HIGH);
        digitalWrite(LED_HIJAU, LOW);

        if (!apiSebelumnya) {
            alarmDimatikan = false;
        } a
piSebelumnya = true;

        if (!alarmDimatikan) {
            tone(BUZZER, 1200);
        } else {
            noTone(BUZZER);
        } l
cd.setCursor(10, 1);
        lcd.print(" API!");
    } e
lse if (suhu >= 30 && suhu < 40) {
        digitalWrite(LED_MERAH, LOW);
        digitalWrite(LED_HIJAU, HIGH);
        noTone(BUZZER);

        apiSebelumnya = false;
        alarmDimatikan = false;

        lcd.setCursor(10, 1);
        lcd.print("HANGAT");
    } e
lse if (suhu >= 40) {
        digitalWrite(LED_MERAH, HIGH);
        digitalWrite(LED_HIJAU, LOW);

        if (!apiSebelumnya) {
            alarmDimatikan = false;
        } a
piSebelumnya = true;

        if (!alarmDimatikan) {
            tone(BUZZER, 1000);
        } else {
            noTone(BUZZER);
        } l
cd.setCursor(10, 1);
        lcd.print(" PANAS");
    } e
lse {
        digitalWrite(LED_MERAH, LOW);
        digitalWrite(LED_HIJAU, HIGH);
        noTone(BUZZER);

        apiSebelumnya = false;
        alarmDimatikan = false;

        lcd.setCursor(10, 1);
        lcd.print("NORMAL");
    } d
elay(200);
}
```
