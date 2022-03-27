#include <Arduino.h>
#include <U8g2lib.h>
#define FASTLED_INTERNAL
#include <FastLED.h>


#define OLED_CLOCK 15
#define OLED_DATA   4
#define OLED_RESET 16
#define NUM_LEDS   60
#define LED_PIN    21

CRGB g_LEDs[NUM_LEDS] = {0};
U8G2_SSD1306_128X64_NONAME_F_HW_I2C g_OLED(U8G2_R2, OLED_RESET, OLED_CLOCK, OLED_DATA);
int g_lineHeight = 0;

double FramesPerSecond(double seconds){
    
    static double framesPerSecond;
    framesPerSecond = (framesPerSecond * .9) + (1.0 / seconds * 0.1);
    return framesPerSecond;
}

void setup(){
    
    pinMode(LED_BUILTIN, OUTPUT);
    pinMode(LED_PIN, OUTPUT);
    
    Serial.begin(115200);
    while (!Serial) { }
    Serial.println("ESP32 Startup");

    g_OLED.begin();
    g_OLED.clear();
    g_OLED.setFont(u8g2_font_profont15_tf);
    g_lineHeight = g_OLED.getFontAscent() - g_OLED.getFontDescent();

    FastLED.addLeds<WS2812B, LED_PIN, GRB>(g_LEDs, NUM_LEDS);
    FastLED.setBrightness(16);
}

void loop() {

    //digitalWrite(LED_BUILTIN, 0);
    //delay(1000);
    //digitalWrite(LED_BUILTIN, 1);
    //delay(1000);
    bool bLED = 0;
    double fps = 0;

    for(;;){
        bLED = !bLED;
        digitalWrite(LED_BUILTIN, bLED);

        double dStart = millis() / 1000.0;

        g_OLED.clearBuffer();
        g_OLED.setCursor(0, g_lineHeight);
        g_OLED.printf("FPS: %.1lf", fps);
        //delay(1000);
        g_OLED.sendBuffer();

        for (int i = 0; i < NUM_LEDS; i++){

           g_LEDs[i] = CRGB::Red; 
        }
        
        FastLED.show();

        double dEnd = millis() / 1000.0;
        fps = FramesPerSecond(dEnd - dStart);
    }
}