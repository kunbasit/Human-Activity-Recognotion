#include "config.h"

TTGOClass *watch;
TFT_eSPI *tft;
BMA *sensor;

void setup()
{
    Serial.begin(115200);

    watch = TTGOClass::getWatch();

   
    watch->begin();

    
    watch->openBL();


    tft = watch->tft;
    sensor = watch->bma;

    Acfg cfg;
  
    
    cfg.odr = BMA4_OUTPUT_DATA_RATE_100HZ;

    
    cfg.range = BMA4_ACCEL_RANGE_2G;

    
    cfg.bandwidth = BMA4_ACCEL_NORMAL_AVG4;

    
    cfg.perf_mode = BMA4_CONTINUOUS_MODE;

    // Configure the BMA423 accelerometer
    sensor->accelConfig(cfg);

    // Enable BMA423 accelerometer
    sensor->enableAccel();

    
    tft->setTextColor(random(0xFFFF));
    tft->drawString("BMA423 accel",  25, 50, 4);
    tft->setTextFont(4);
    tft->setTextColor(TFT_WHITE, TFT_BLACK);
}

void loop()
{
    Accel acc;

    
    bool res = sensor->getAccel(acc);

    if (res == false) {
        Serial.println("getAccel FAIL");
    } else {
        
        tft->fillRect(98, 100, 70, 85, TFT_BLACK);
        tft->setCursor(80, 100);
        tft->print("X:"); tft->println(acc.x);
        tft->setCursor(80, 130);
        tft->print("Y:"); tft->println(acc.y);
        tft->setCursor(80, 160);
        tft->print("Z:"); tft->println(acc.z);
    }
    delay(100);
}
