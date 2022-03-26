#include <Arduino.h>
#include <U8g2lib.h>

#define OLED_CLOCK 15
#define OLED_DATA   4
#define OLED_RESET 16

U8G2_SSD1306_128X64_NONAME_F_HW_I2C g_OLED(U8G2_R2, OLED_RESET, OLED_CLOCK, OLED_DATA);
int g_lineHeight = 0;


double FramesPerSecond(double seconds){

    static double framesPerSecond;
    framesPerSecond = (framesPerSecond * .9) + (1.0 / seconds * .1);
    return framesPerSecond;
}

void setup(){
    
    pinMode(LED_BUILTIN, OUTPUT);
    
    Serial.begin(115200);
    while (!Serial) { }
    Serial.println("ESP32 Startup");

    g_OLED.begin();
    g_OLED.clear();
    g_OLED.setFont(u8g2_font_profont15_tf);
    g_lineHeight = g_OLED.getFontAscent() - g_OLED.getFontDescent();
}

void loop() {

    bool bLED = 0;
    double fps = 0;

    for(;;){
        bLED = !bLED;
        digitalWrite(LED_BUILTIN, bLED);

        double dStart = millis() / 1000.0;

        g_OLED.clearBuffer();
        g_OLED.setCursor(0, g_lineHeight);
        g_OLED.printf("FPS: %.01f", fps);
        g_OLED.sendBuffer();

        double dEnd = millis() / 1000.0;
        fps = FramesPerSecond(dEnd - dStart);
    }



}