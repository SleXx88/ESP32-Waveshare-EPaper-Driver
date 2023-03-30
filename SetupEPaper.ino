#define ENABLE_GxEPD2_GFX 0

#include <GxEPD2_3C.h>
#include <Fonts/FreeMonoBold9pt7b.h>
#include <U8g2_for_Adafruit_GFX.h>

#define GxEPD2_DISPLAY_CLASS GxEPD2_3C
//#define GxEPD2_DRIVER_CLASS GxEPD2_420c_Z21 // GDEQ042Z21  400x300, UC8276
#define GxEPD2_DRIVER_CLASS GxEPD2_750c_Z08 // GDEW075Z08  800x480, GD7965
//#define GxEPD2_DRIVER_CLASS GxEPD2_750c_Z90 // GDEH075Z90  880x528, SSD1677

//#define GxEPD2_3C_IS_GxEPD2_3C true
#define GxEPD2_750c_Z08_IS_3C true
//#define GxEPD2_750c_Z90_IS_3C true

#define IS_GxEPD2_DRIVER(c, x) (c##x)
#define IS_GxEPD2_3C(x) IS_GxEPD(GxEPD2_3C_IS_, x)
#define MAX_DISPLAY_BUFFER_SIZE 65536ul
#define MAX_HEIGHT(EPD) (EPD::HEIGHT <= (MAX_DISPLAY_BUFFER_SIZE / 2) / (EPD::WIDTH / 8) ? EPD::HEIGHT : (MAX_DISPLAY_BUFFER_SIZE / 2) / (EPD::WIDTH / 8))
GxEPD2_DISPLAY_CLASS<GxEPD2_DRIVER_CLASS, MAX_HEIGHT(GxEPD2_DRIVER_CLASS)> display(GxEPD2_DRIVER_CLASS(PIN_CS, PIN_DC, PIN_RST, PIN_BUSY));

//#define GxEPD2_420c_Z21_IS_3C true
#define GxEPD2_750c_Z08_IS_3C true
//#define GxEPD2_750c_Z90_IS_3C true

U8G2_FOR_ADAFRUIT_GFX u8g2Fonts;

void ePaperSetup()
{
  //pinMode(16, INPUT_PULLUP);
  display.init(115200, true, 100, false);
  u8g2Fonts.begin(display);
  display.setRotation(0);
}
