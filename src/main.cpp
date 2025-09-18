#include <Adafruit_NeoPixel.h>
#include <TroykaButton.h>
#include <TroykaRTC.h>

constexpr uint8_t DELAYVAL = 50;

constexpr uint8_t INTENS = 150;

constexpr uint8_t BUTTON_1 = A0;
constexpr uint8_t BUTTON_2 = A1;
constexpr uint8_t BUTTON_3 = A2;
constexpr uint8_t BUTTON_4 = A3;

Adafruit_NeoPixel matrix(40, 2, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel dot(1, 9, NEO_GRB + NEO_KHZ800);

TroykaButton button_1(BUTTON_1, 1000, true, 200);
TroykaButton button_2(BUTTON_2, 1000, true, 200);
TroykaButton button_3(BUTTON_3, 1000, true, 200);
TroykaButton button_4(BUTTON_4, 1000, true, 200);

RTC clock;

int i = 0;
int mil = 0;

void setup()
{
    Serial.begin(9600);

    matrix.begin();
    dot.begin();

    matrix.clear();
    dot.clear();

    button_1.begin();
    button_2.begin();
    button_3.begin();
    button_4.begin();

    clock.begin();

    i = clock.getRAMData(0x08);

    Serial.print("Restore i to ");
    Serial.println(i);

    Serial.println("Setup complete");
}

void loop()
{
    button_1.read();
    button_2.read();
    button_3.read();
    button_4.read();

    if (button_1.isClick())
    {
        Serial.println("Button 1 Click");
    }
    if (button_2.isClick())
    {
        Serial.println("Button 2 Click");
    }
    if (button_3.isClick())
    {
        Serial.println("Button 3 Click");
    }
    if (button_4.isClick())
    {
        Serial.println("Button 4 Click");
    }

    int m = millis();
    if (m - mil >= 1000)
    {
        mil = m;

        clock.read();
        Serial.print("Current Time: ");
        Serial.print(clock.getHour());
        Serial.print(":");
        Serial.print(clock.getMinute());
        Serial.print(":");
        Serial.println(clock.getSecond());
    }

    if (i % 10 == 0)
    {
        if (i < 10)
        {
            dot.setPixelColor(0, dot.Color(INTENS, INTENS, 0));
        }
        else if (i < 20)
        {
            dot.setPixelColor(0, dot.Color(INTENS, 0, INTENS));
        }
        else if (i < 30)
        {
            dot.setPixelColor(0, dot.Color(0, INTENS, INTENS));
        }
        else if (i < 40)
        {
            dot.setPixelColor(0, dot.Color(0, INTENS, 0));
        }
        else
        {
            dot.setPixelColor(0, dot.Color(0, 0, 0));
        }
    }
    dot.show();

    if (i < 10)
    {
        matrix.setPixelColor(i, matrix.Color(INTENS, INTENS, 0));
    }
    else if (i < 20)
    {
        matrix.setPixelColor(i, matrix.Color(INTENS, 0, INTENS));
    }
    else if (i < 30)
    {
        matrix.setPixelColor(i, matrix.Color(0, INTENS, INTENS));
    }
    else if (i < 40)
    {
        matrix.setPixelColor(i, matrix.Color(0, INTENS, 0));
    }
    else
    {
        matrix.setPixelColor(i - 40, matrix.Color(0, 0, 0));
    }
    matrix.show();

    if (++i >= 80)
    {
        i = 0;
        matrix.clear();
    }
    else
    {
        delay(DELAYVAL);
    }

    clock.setRAMData(0x08, i);
}
