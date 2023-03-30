void refresh_epaper() //800x480
{
  uint16_t white  = GxEPD_WHITE;
  uint16_t black  = GxEPD_BLACK;
  uint16_t red    = GxEPD_RED;

  display.firstPage();
  do
  {
  display.fillScreen(GxEPD_WHITE);

//############ draw H-Lines    ###################################################################################################
  display.drawFastHLine(0, 25, 800, black);
  display.drawFastHLine(0, 26, 800, black);

  display.drawFastHLine(0, 125, 800, black);
  display.drawFastHLine(0, 126, 800, black);

  display.drawFastHLine(0, 200, 800, black);
  display.drawFastHLine(0, 201, 800, black);

  display.drawFastHLine(6, 174, 40, black);
  display.drawFastHLine(139, 174, 40, black);
  display.drawFastHLine(272, 174, 40, black);

  display.drawFastHLine(0, 313, 401, black);
  display.drawFastHLine(0, 314, 401, black);

  display.drawFastHLine(0, 423, 401, black);
  display.drawFastHLine(0, 424, 401, black);
//############ draw V-Lines    ###################################################################################################
  display.drawFastVLine(133, 125, 75, black);
  display.drawFastVLine(134, 125, 75, black);

  display.drawFastVLine(266, 125, 75, black);
  display.drawFastVLine(267, 125, 75, black);

  display.drawFastVLine(401, 25, 454, black);
  display.drawFastVLine(402, 25, 454, black);
//############ Current weather ###################################################################################################
  if(String(weather_icon) == "01d") display.drawBitmap(18, 43, icon_64x64_01d, 64, 64, GxEPD_BLACK);
  if(String(weather_icon) == "01n") display.drawBitmap(18, 43, icon_64x64_01n, 64, 64, GxEPD_BLACK);
  if(String(weather_icon) == "02d") display.drawBitmap(18, 43, icon_64x64_02d, 64, 64, GxEPD_BLACK);
  if(String(weather_icon) == "02n") display.drawBitmap(18, 43, icon_64x64_02n, 64, 64, GxEPD_BLACK);
  if(String(weather_icon) == "03d") display.drawBitmap(18, 43, icon_64x64_03d, 64, 64, GxEPD_BLACK);
  if(String(weather_icon) == "03n") display.drawBitmap(18, 43, icon_64x64_03n, 64, 64, GxEPD_BLACK);
  if(String(weather_icon) == "04d") display.drawBitmap(18, 43, icon_64x64_04d, 64, 64, GxEPD_BLACK);
  if(String(weather_icon) == "04n") display.drawBitmap(18, 43, icon_64x64_04n, 64, 64, GxEPD_BLACK);
  if(String(weather_icon) == "09d") display.drawBitmap(18, 43, icon_64x64_09d, 64, 64, GxEPD_BLACK);
  if(String(weather_icon) == "09n") display.drawBitmap(18, 43, icon_64x64_09n, 64, 64, GxEPD_BLACK);
  if(String(weather_icon) == "10d") display.drawBitmap(18, 43, icon_64x64_10d, 64, 64, GxEPD_BLACK);
  if(String(weather_icon) == "10n") display.drawBitmap(18, 43, icon_64x64_10n, 64, 64, GxEPD_BLACK);
  if(String(weather_icon) == "11d") display.drawBitmap(18, 43, icon_64x64_11d, 64, 64, GxEPD_BLACK);
  if(String(weather_icon) == "11n") display.drawBitmap(18, 43, icon_64x64_11n, 64, 64, GxEPD_BLACK);
  if(String(weather_icon) == "13d") display.drawBitmap(18, 43, icon_64x64_13d, 64, 64, GxEPD_BLACK);
  if(String(weather_icon) == "13n") display.drawBitmap(18, 43, icon_64x64_13n, 64, 64, GxEPD_BLACK);
  if(String(weather_icon) == "50d") display.drawBitmap(18, 43, icon_64x64_50d, 64, 64, GxEPD_BLACK);
  if(String(weather_icon) == "50n") display.drawBitmap(18, 43, icon_64x64_50n, 64, 64, GxEPD_BLACK);

  u8g2Fonts.setFontMode(1);      
  u8g2Fonts.setFontDirection(0);
  u8g2Fonts.setForegroundColor(black);
  u8g2Fonts.setBackgroundColor(white);

//############ HEADER          ###################################################################################################
  u8g2Fonts.setFont(u8g2_font_helvR14_tf);

  display.drawBitmap(10, 7, icon_update, 16, 16, GxEPD_BLACK);
  u8g2Fonts.setCursor(35, 21);
  u8g2Fonts.print(F(currentTime));

  // RSSI
  if(WiFi.RSSI() >= -50){
    display.drawBitmap(270, 6, icon_wifi4, 16, 16, GxEPD_BLACK);
    }
  if(WiFi.RSSI() >= -60 && WiFi.RSSI() < -50 ){
    display.drawBitmap(270, 6, icon_wifi3, 16, 16, GxEPD_BLACK);
    }
  if(WiFi.RSSI() >= -70 && WiFi.RSSI() < -60 ){
    display.drawBitmap(270, 6, icon_wifi2, 16, 16, GxEPD_BLACK);
    }
  if(WiFi.RSSI() < -70){
    display.drawBitmap(270, 6, icon_wifi1, 16, 16, GxEPD_BLACK);
    }
  // Router IP
  u8g2Fonts.setCursor(295, 21);
  u8g2Fonts.print(NetworkIP);

  // Battery Voltages
  // 75 - 100%  = State4  =   >= 3.98
  // 50 - 75%   = State3  =   >= 3.84 && < 3.98
  // 25 - 50%   = State2  =   >= 3.75 && < 3.84
  // 15 - 25%   = State1  =   >= 3.71 && < 3.75
  // 0 - 15%    = empty   =   < 3.71
  if(VCC_USB > 4.00)
  {
    display.drawBitmap(768, 2, icon_charge, 24, 24, GxEPD_BLACK);
  }
  else
  {
    if(VCC_BAT >= 3.98)                   display.drawBitmap(768, 2, icon_state4, 24, 24, GxEPD_BLACK);
    if(VCC_BAT >= 3.84 && VCC_BAT < 3.98) display.drawBitmap(768, 2, icon_state3, 24, 24, GxEPD_BLACK);
    if(VCC_BAT >= 3.75 && VCC_BAT < 3.84) display.drawBitmap(768, 2, icon_state2, 24, 24, GxEPD_BLACK);
    if(VCC_BAT >= 3.71 && VCC_BAT < 3.75) display.drawBitmap(768, 2, icon_state1, 24, 24, GxEPD_BLACK);
    if(VCC_BAT < 3.71)                    display.drawBitmap(768, 2, icon_empty,  24, 24, GxEPD_BLACK);
  }
  
  u8g2Fonts.setFont(u8g2_font_helvR14_tf);

  display.drawBitmap(305, 30, icon_sunrise, 30, 22, GxEPD_BLACK);

  u8g2Fonts.setCursor(337, 50);
  u8g2Fonts.print(weather_sunrise);

  display.drawBitmap(305, 54, icon_sunset, 30, 22, GxEPD_BLACK);

  u8g2Fonts.setCursor(337, 72);
  u8g2Fonts.print(weather_sunset);

  display.drawBitmap(305, 76, icon_uv, 30, 22, GxEPD_BLACK);
  u8g2Fonts.setCursor(337, 94);
  u8g2Fonts.print(weather_uv);

  display.drawBitmap(305, 98, icon_wind, 30, 22, GxEPD_BLACK);
  u8g2Fonts.setCursor(337, 116);
  u8g2Fonts.print(weather_wind);
  
  u8g2Fonts.setFont(u8g2_font_helvR24_tf);
  u8g2Fonts.setCursor(105, 60);

  u8g2Fonts.print(weather_temp);
  u8g2Fonts.setCursor(105, 92);
  u8g2Fonts.print(weather_hum);
  u8g2Fonts.setFont(u8g2_font_helvR14_tf);
  u8g2Fonts.setCursor(105, 116);
  u8g2Fonts.print(weather_desc);
  
//############ Daily weather   ###################################################################################################
  //--------------- Day 1 -------------------------------------------------
  u8g2Fonts.setCursor(6, 145);
  u8g2Fonts.print(day1_time);
  u8g2Fonts.setCursor(6, 170);
  u8g2Fonts.setForegroundColor(red);
  u8g2Fonts.print(day1_tempMax, 0); u8g2Fonts.print("°C");
  u8g2Fonts.setCursor(6, 192);
  u8g2Fonts.setForegroundColor(black);
  u8g2Fonts.print(day1_tempMin, 0); u8g2Fonts.print("°C");

  if(String(day1_icon) == "01d") display.drawBitmap(63, 130, icon_64x64_01d, 64, 64, GxEPD_BLACK);
  if(String(day1_icon) == "01n") display.drawBitmap(63, 130, icon_64x64_01n, 64, 64, GxEPD_BLACK);
  if(String(day1_icon) == "02d") display.drawBitmap(63, 130, icon_64x64_02d, 64, 64, GxEPD_BLACK);
  if(String(day1_icon) == "02n") display.drawBitmap(63, 130, icon_64x64_02n, 64, 64, GxEPD_BLACK);
  if(String(day1_icon) == "03d") display.drawBitmap(63, 130, icon_64x64_03d, 64, 64, GxEPD_BLACK);
  if(String(day1_icon) == "03n") display.drawBitmap(63, 130, icon_64x64_03n, 64, 64, GxEPD_BLACK);
  if(String(day1_icon) == "04d") display.drawBitmap(63, 130, icon_64x64_04d, 64, 64, GxEPD_BLACK);
  if(String(day1_icon) == "04n") display.drawBitmap(63, 130, icon_64x64_04n, 64, 64, GxEPD_BLACK);
  if(String(day1_icon) == "09d") display.drawBitmap(63, 130, icon_64x64_09d, 64, 64, GxEPD_BLACK);
  if(String(day1_icon) == "09n") display.drawBitmap(63, 130, icon_64x64_09n, 64, 64, GxEPD_BLACK);
  if(String(day1_icon) == "10d") display.drawBitmap(63, 130, icon_64x64_10d, 64, 64, GxEPD_BLACK);
  if(String(day1_icon) == "10n") display.drawBitmap(63, 130, icon_64x64_10n, 64, 64, GxEPD_BLACK);
  if(String(day1_icon) == "11d") display.drawBitmap(63, 130, icon_64x64_11d, 64, 64, GxEPD_BLACK);
  if(String(day1_icon) == "11n") display.drawBitmap(63, 130, icon_64x64_11n, 64, 64, GxEPD_BLACK);
  if(String(day1_icon) == "13d") display.drawBitmap(63, 130, icon_64x64_13d, 64, 64, GxEPD_BLACK);
  if(String(day1_icon) == "13n") display.drawBitmap(63, 130, icon_64x64_13n, 64, 64, GxEPD_BLACK);
  if(String(day1_icon) == "50d") display.drawBitmap(63, 130, icon_64x64_50d, 64, 64, GxEPD_BLACK);
  if(String(day1_icon) == "50n") display.drawBitmap(63, 130, icon_64x64_50n, 64, 64, GxEPD_BLACK);

  //--------------- Day 2 -------------------------------------------------
  u8g2Fonts.setCursor(139, 145);
  u8g2Fonts.print(day2_time);
  u8g2Fonts.setCursor(139, 170);
  u8g2Fonts.setForegroundColor(red);
  u8g2Fonts.print(day2_tempMax, 0); u8g2Fonts.print("°C");
  u8g2Fonts.setCursor(139, 192);
  u8g2Fonts.setForegroundColor(black);
  u8g2Fonts.print(day2_tempMin, 0); u8g2Fonts.print("°C");

  if(String(day2_icon) == "01d") display.drawBitmap(196, 130, icon_64x64_01d, 64, 64, GxEPD_BLACK);
  if(String(day2_icon) == "01n") display.drawBitmap(196, 130, icon_64x64_01n, 64, 64, GxEPD_BLACK);
  if(String(day2_icon) == "02d") display.drawBitmap(196, 130, icon_64x64_02d, 64, 64, GxEPD_BLACK);
  if(String(day2_icon) == "02n") display.drawBitmap(196, 130, icon_64x64_02n, 64, 64, GxEPD_BLACK);
  if(String(day2_icon) == "03d") display.drawBitmap(196, 130, icon_64x64_03d, 64, 64, GxEPD_BLACK);
  if(String(day2_icon) == "03n") display.drawBitmap(196, 130, icon_64x64_03n, 64, 64, GxEPD_BLACK);
  if(String(day2_icon) == "04d") display.drawBitmap(196, 130, icon_64x64_04d, 64, 64, GxEPD_BLACK);
  if(String(day2_icon) == "04n") display.drawBitmap(196, 130, icon_64x64_04n, 64, 64, GxEPD_BLACK);
  if(String(day2_icon) == "09d") display.drawBitmap(196, 130, icon_64x64_09d, 64, 64, GxEPD_BLACK);
  if(String(day2_icon) == "09n") display.drawBitmap(196, 130, icon_64x64_09n, 64, 64, GxEPD_BLACK);
  if(String(day2_icon) == "10d") display.drawBitmap(196, 130, icon_64x64_10d, 64, 64, GxEPD_BLACK);
  if(String(day2_icon) == "10n") display.drawBitmap(196, 130, icon_64x64_10n, 64, 64, GxEPD_BLACK);
  if(String(day2_icon) == "11d") display.drawBitmap(196, 130, icon_64x64_11d, 64, 64, GxEPD_BLACK);
  if(String(day2_icon) == "11n") display.drawBitmap(196, 130, icon_64x64_11n, 64, 64, GxEPD_BLACK);
  if(String(day2_icon) == "13d") display.drawBitmap(196, 130, icon_64x64_13d, 64, 64, GxEPD_BLACK);
  if(String(day2_icon) == "13n") display.drawBitmap(196, 130, icon_64x64_13n, 64, 64, GxEPD_BLACK);
  if(String(day2_icon) == "50d") display.drawBitmap(196, 130, icon_64x64_50d, 64, 64, GxEPD_BLACK);
  if(String(day2_icon) == "50n") display.drawBitmap(196, 130, icon_64x64_50n, 64, 64, GxEPD_BLACK);

  //--------------- Day 3 -------------------------------------------------
  u8g2Fonts.setCursor(272, 145);
  u8g2Fonts.print(day3_time);
  u8g2Fonts.setCursor(272, 170);
  u8g2Fonts.setForegroundColor(red);
  u8g2Fonts.print(day3_tempMax, 0); u8g2Fonts.print("°C");
  u8g2Fonts.setCursor(272, 192);
  u8g2Fonts.setForegroundColor(black);
  u8g2Fonts.print(day3_tempMin, 0); u8g2Fonts.print("°C");

  if(String(day3_icon) == "01d") display.drawBitmap(329, 130, icon_64x64_01d, 64, 64, GxEPD_BLACK);
  if(String(day3_icon) == "01n") display.drawBitmap(329, 130, icon_64x64_01n, 64, 64, GxEPD_BLACK);
  if(String(day3_icon) == "02d") display.drawBitmap(329, 130, icon_64x64_02d, 64, 64, GxEPD_BLACK);
  if(String(day3_icon) == "02n") display.drawBitmap(329, 130, icon_64x64_02n, 64, 64, GxEPD_BLACK);
  if(String(day3_icon) == "03d") display.drawBitmap(329, 130, icon_64x64_03d, 64, 64, GxEPD_BLACK);
  if(String(day3_icon) == "03n") display.drawBitmap(329, 130, icon_64x64_03n, 64, 64, GxEPD_BLACK);
  if(String(day3_icon) == "04d") display.drawBitmap(329, 130, icon_64x64_04d, 64, 64, GxEPD_BLACK);
  if(String(day3_icon) == "04n") display.drawBitmap(329, 130, icon_64x64_04n, 64, 64, GxEPD_BLACK);
  if(String(day3_icon) == "09d") display.drawBitmap(329, 130, icon_64x64_09d, 64, 64, GxEPD_BLACK);
  if(String(day3_icon) == "09n") display.drawBitmap(329, 130, icon_64x64_09n, 64, 64, GxEPD_BLACK);
  if(String(day3_icon) == "10d") display.drawBitmap(329, 130, icon_64x64_10d, 64, 64, GxEPD_BLACK);
  if(String(day3_icon) == "10n") display.drawBitmap(329, 130, icon_64x64_10n, 64, 64, GxEPD_BLACK);
  if(String(day3_icon) == "11d") display.drawBitmap(329, 130, icon_64x64_11d, 64, 64, GxEPD_BLACK);
  if(String(day3_icon) == "11n") display.drawBitmap(329, 130, icon_64x64_11n, 64, 64, GxEPD_BLACK);
  if(String(day3_icon) == "13d") display.drawBitmap(329, 130, icon_64x64_13d, 64, 64, GxEPD_BLACK);
  if(String(day3_icon) == "13n") display.drawBitmap(329, 130, icon_64x64_13n, 64, 64, GxEPD_BLACK);
  if(String(day3_icon) == "50d") display.drawBitmap(329, 130, icon_64x64_50d, 64, 64, GxEPD_BLACK);
  if(String(day3_icon) == "50n") display.drawBitmap(329, 130, icon_64x64_50n, 64, 64, GxEPD_BLACK);

//############ Calendar        ###################################################################################################
  u8g2Fonts.setFont(u8g2_font_fub14_tf);
  u8g2Fonts.setCursor(410, 225); u8g2Fonts.print(cal1_titel);
  u8g2Fonts.setFont(u8g2_font_helvR14_tf);
  u8g2Fonts.setCursor(410, 250); u8g2Fonts.print(cal1_start);u8g2Fonts.print(cal1_end);
  // 35px
  display.drawFastHLine(401, 258, 398, black);
  u8g2Fonts.setFont(u8g2_font_fub14_tf);
  u8g2Fonts.setCursor(410, 280); u8g2Fonts.print(cal2_titel);
  u8g2Fonts.setFont(u8g2_font_helvR14_tf);
  u8g2Fonts.setCursor(410, 305); u8g2Fonts.print(cal2_start);u8g2Fonts.print(cal2_end);
  // 35px
  display.drawFastHLine(401, 313, 398, black);
  u8g2Fonts.setFont(u8g2_font_fub14_tf);
  u8g2Fonts.setCursor(410, 335); u8g2Fonts.print(cal3_titel);
  u8g2Fonts.setFont(u8g2_font_helvR14_tf);
  u8g2Fonts.setCursor(410, 360); u8g2Fonts.print(cal3_start);u8g2Fonts.print(cal3_end);
  // 35px
  display.drawFastHLine(401, 368, 398, black);
  u8g2Fonts.setFont(u8g2_font_fub14_tf);
  u8g2Fonts.setCursor(410, 390); u8g2Fonts.print(cal4_titel);
  u8g2Fonts.setFont(u8g2_font_helvR14_tf);
  u8g2Fonts.setCursor(410, 415); u8g2Fonts.print(cal4_start);u8g2Fonts.print(cal4_end);
  // 35px
  display.drawFastHLine(401, 423, 398, black);
  u8g2Fonts.setFont(u8g2_font_fub14_tf);
  u8g2Fonts.setCursor(410, 445); u8g2Fonts.print(cal5_titel);
  u8g2Fonts.setFont(u8g2_font_helvR14_tf);
  u8g2Fonts.setCursor(410, 470); u8g2Fonts.print(cal5_start);u8g2Fonts.print(cal5_end);

//############ Area 0.0 ##########################################################################################################
  u8g2Fonts.setForegroundColor(black);
  u8g2Fonts.setFont(u8g2_font_helvR14_tf);
  u8g2Fonts.setCursor(5, 224); 
  u8g2Fonts.print(F(Area0Line0desc));  
  if(Area0Line0Icon0 != -1) display.drawBitmap(135, 206,  iconID[Area0Line0Icon0], 24, 24, GxEPD_BLACK);
  u8g2Fonts.setCursor(163, 224); 
  u8g2Fonts.print(F(Area0Line0Text0));  
  if(Area0Line0Icon1 != -1) display.drawBitmap(230, 206,  iconID[Area0Line0Icon1], 24, 24, GxEPD_BLACK);
  u8g2Fonts.setCursor(258, 224); 
  u8g2Fonts.print(F(Area0Line0Text1));  
  if(Area0Line0color != 0)
  {
    if(Area0Line0Icon2 != -1) display.drawBitmap(325, 206,  icon_bat_ID[Area0Line0Icon2], 24, 24, GxEPD_RED);
    u8g2Fonts.setCursor(353, 224);
    u8g2Fonts.setForegroundColor(red); 
    u8g2Fonts.print(F(Area0Line0Text2));  
  }
  else
  {
    if(Area0Line0Icon2 != -1) display.drawBitmap(325, 206,  icon_bat_ID[Area0Line0Icon2], 24, 24, GxEPD_BLACK);
    u8g2Fonts.setForegroundColor(black);
    u8g2Fonts.setCursor(353, 224);
    u8g2Fonts.print(F(Area0Line0Text2));
  }
//############ Area 0.1 ##########################################################################################################
  u8g2Fonts.setForegroundColor(black);
  u8g2Fonts.setCursor(5, 250); 
  u8g2Fonts.print(F(Area0Line1desc));  
  if(Area0Line1Icon0 != -1) display.drawBitmap(135, 232,  iconID[Area0Line1Icon0], 24, 24, GxEPD_BLACK);
  u8g2Fonts.setCursor(163, 250); 
  u8g2Fonts.print(F(Area0Line1Text0));  
  if(Area0Line1Icon1 != -1) display.drawBitmap(230, 232,  iconID[Area0Line1Icon1], 24, 24, GxEPD_BLACK);
  u8g2Fonts.setCursor(258, 250); 
  u8g2Fonts.print(F(Area0Line1Text1));
  if(Area0Line1color != 0)
  {
    if(Area0Line1Icon2 != -1) display.drawBitmap(325, 232,  icon_bat_ID[Area0Line1Icon2], 24, 24, GxEPD_RED);
    u8g2Fonts.setCursor(353, 250);
    u8g2Fonts.setForegroundColor(red);
    u8g2Fonts.print(F(Area0Line1Text2));
  }
  else
  {
    if(Area0Line1Icon2 != -1) display.drawBitmap(325, 232,  icon_bat_ID[Area0Line1Icon2], 24, 24, GxEPD_BLACK);
    u8g2Fonts.setForegroundColor(black);
    u8g2Fonts.setCursor(353, 250); 
    u8g2Fonts.print(F(Area0Line1Text2));
  }
//############ Area 0.2 ##########################################################################################################
  u8g2Fonts.setForegroundColor(black);
  u8g2Fonts.setCursor(5, 276); 
  u8g2Fonts.print(F(Area0Line2desc));  
  if(Area0Line2Icon0 != -1) display.drawBitmap(135, 258,  iconID[Area0Line2Icon0], 24, 24, GxEPD_BLACK);
  u8g2Fonts.setCursor(163, 276); 
  u8g2Fonts.print(F(Area0Line2Text0));  
  if(Area0Line2Icon1 != -1) display.drawBitmap(230, 258,  iconID[Area0Line2Icon1], 24, 24, GxEPD_BLACK);
  u8g2Fonts.setCursor(258, 276); 
  u8g2Fonts.print(F(Area0Line2Text1));
  if(Area0Line2color != 0)
  {
    if(Area0Line2Icon2 != -1) display.drawBitmap(325, 258,  icon_bat_ID[Area0Line2Icon2], 24, 24, GxEPD_RED);
    u8g2Fonts.setForegroundColor(red);
    u8g2Fonts.setCursor(353, 276); 
    u8g2Fonts.print(F(Area0Line2Text2));
  }
  else
  {
    if(Area0Line2Icon2 != -1) display.drawBitmap(325, 258,  icon_bat_ID[Area0Line2Icon2], 24, 24, GxEPD_BLACK);
    u8g2Fonts.setForegroundColor(black);
    u8g2Fonts.setCursor(353, 276);
    u8g2Fonts.print(F(Area0Line2Text2));
  }
//############ Area 0.3 ##########################################################################################################
  u8g2Fonts.setForegroundColor(black);
  u8g2Fonts.setCursor(5, 302); 
  u8g2Fonts.print(F(Area0Line3desc));  
  if(Area0Line3Icon0 != -1) display.drawBitmap(135, 284,  iconID[Area0Line3Icon0], 24, 24, GxEPD_BLACK);
  u8g2Fonts.setCursor(163, 302); 
  u8g2Fonts.print(F(Area0Line3Text0));  
  if(Area0Line3Icon1 != -1) display.drawBitmap(230, 284,  iconID[Area0Line3Icon1], 24, 24, GxEPD_BLACK);
  u8g2Fonts.setCursor(258, 302); 
  u8g2Fonts.print(F(Area0Line3Text1));
  if(Area0Line3color != 0)
  {
    if(Area0Line3Icon2 != -1) display.drawBitmap(325, 284,  icon_bat_ID[Area0Line3Icon2], 24, 24, GxEPD_RED);
    u8g2Fonts.setCursor(353, 302);
    u8g2Fonts.setForegroundColor(red); 
    u8g2Fonts.print(F(Area0Line3Text2));
  }
  else
  {
    if(Area0Line3Icon2 != -1) display.drawBitmap(325, 284,  icon_bat_ID[Area0Line3Icon2], 24, 24, GxEPD_BLACK);
    u8g2Fonts.setForegroundColor(black);
    u8g2Fonts.setCursor(353, 302); 
    u8g2Fonts.print(F(Area0Line3Text2));
  }
//############ Area 1.0 ##########################################################################################################
  if(Area1Line0Icon0 != -1) display.drawBitmap(5, 319,  iconID[Area1Line0Icon0], 24, 24, GxEPD_BLACK);
  u8g2Fonts.setForegroundColor(black);
  u8g2Fonts.setFont(u8g2_font_helvR14_tf);
  u8g2Fonts.setCursor(39, 337); 
  u8g2Fonts.print(F(Area1Line0Text0));

  if(Area1Line0color == 1)
  {
    if(Area1Line0Icon1 != -1) display.drawBitmap(325, 319,  icon_bat_ID[Area1Line0Icon1], 24, 24, GxEPD_RED);
    u8g2Fonts.setCursor(353, 337);
    u8g2Fonts.setForegroundColor(red); 
    u8g2Fonts.print(F(Area1Line0Text1));
  }
  else
  {
    if(Area1Line0Icon1 != -1) display.drawBitmap(325, 319,  icon_bat_ID[Area1Line0Icon1], 24, 24, GxEPD_BLACK);
    u8g2Fonts.setForegroundColor(black);
    u8g2Fonts.setCursor(353, 337); 
    u8g2Fonts.print(F(Area1Line0Text1));
  }
//############ Area 1.1 ##########################################################################################################
  if(Area1Line1Icon0 != -1) display.drawBitmap(5, 345, iconID[Area1Line1Icon0], 24, 24, GxEPD_BLACK);
  u8g2Fonts.setForegroundColor(black);
  u8g2Fonts.setCursor(39, 363); 
  u8g2Fonts.print(F(Area1Line1Text0));

  if(Area1Line1color == 1)
  {
    if(Area1Line1Icon1 != -1) display.drawBitmap(325, 345,  icon_bat_ID[Area1Line1Icon1], 24, 24, GxEPD_RED);
    u8g2Fonts.setCursor(353, 363);
    u8g2Fonts.setForegroundColor(red); 
    u8g2Fonts.print(F(Area1Line1Text1));
  }
  else
  {
    if(Area1Line1Icon1 != -1) display.drawBitmap(325, 345,  icon_bat_ID[Area1Line1Icon1], 24, 24, GxEPD_BLACK);
    u8g2Fonts.setForegroundColor(black);
    u8g2Fonts.setCursor(353, 363); 
    u8g2Fonts.print(F(Area1Line1Text1));
  }
//############ Area 1.2 ##########################################################################################################
  if(Area1Line2Icon0 != -1) display.drawBitmap(5, 371, iconID[Area1Line2Icon0], 24, 24, GxEPD_BLACK);
  u8g2Fonts.setForegroundColor(black);
  u8g2Fonts.setCursor(39, 389); 
  u8g2Fonts.print(F(Area1Line2Text0));

  if(Area1Line2color == 1)
  {
    if(Area1Line2Icon1 != -1) display.drawBitmap(325, 371,  icon_bat_ID[Area1Line2Icon1], 24, 24, GxEPD_RED);
    u8g2Fonts.setCursor(353, 389);
    u8g2Fonts.setForegroundColor(red); 
    u8g2Fonts.print(F(Area1Line2Text1));
  }
  else
  {
    if(Area1Line2Icon1 != -1) display.drawBitmap(325, 371,  icon_bat_ID[Area1Line2Icon1], 24, 24, GxEPD_BLACK);
    u8g2Fonts.setForegroundColor(black);
    u8g2Fonts.setCursor(353, 389); 
    u8g2Fonts.print(F(Area1Line2Text1));
  }
//############ Area 1.3 ##########################################################################################################
  if(Area1Line3Icon0 != -1) display.drawBitmap(5, 397, iconID[Area1Line3Icon0], 24, 24, GxEPD_BLACK);
  u8g2Fonts.setForegroundColor(black);
  u8g2Fonts.setCursor(39, 415); 
  u8g2Fonts.print(F(Area1Line3Text0));

  if(Area1Line3color == 1)
  {
    if(Area1Line3Icon1 != -1) display.drawBitmap(325, 397,  icon_bat_ID[Area1Line3Icon1], 24, 24, GxEPD_RED);
    u8g2Fonts.setCursor(353, 415);
    u8g2Fonts.setForegroundColor(red); 
    u8g2Fonts.print(F(Area1Line3Text1));
  }
  else
  {
    if(Area1Line3Icon1 != -1) display.drawBitmap(325, 397,  icon_bat_ID[Area1Line3Icon1], 24, 24, GxEPD_BLACK);
    u8g2Fonts.setForegroundColor(black);
    u8g2Fonts.setCursor(353, 415); 
    u8g2Fonts.print(F(Area1Line3Text1));
  }

//############ Area 2.0 ##########################################################################################################
  if(Area2Icon0 != -1) display.drawBitmap(5, 427,  iconID[Area2Icon0], 24, 24, GxEPD_BLACK);
  u8g2Fonts.setForegroundColor(black);
  u8g2Fonts.setFont(u8g2_font_helvR14_tf);
  u8g2Fonts.setCursor(39, 445);
  u8g2Fonts.print(F(Area2Text0));
//############ Area 2.1 ##########################################################################################################
  u8g2Fonts.setFont(u8g2_font_helvR14_tf);
  if(Area2Text1color == 0){
    if(Area2Icon1 != -1) display.drawBitmap(5, 453,  iconID[Area2Icon1], 24, 24, GxEPD_BLACK);
    u8g2Fonts.setForegroundColor(black);
    u8g2Fonts.setCursor(39, 471);
    u8g2Fonts.print(F(Area2Text1));
  }
  else{
    if(Area2Icon1 != -1) display.drawBitmap(5, 453,  iconID[Area2Icon1], 24, 24, GxEPD_RED);
    u8g2Fonts.setForegroundColor(red);
    u8g2Fonts.setCursor(39, 471);
    u8g2Fonts.print(F(Area2Text1));
  }
  

  // u8g2Fonts.print("Pegel Chemnitz: "); u8g2Fonts.print(WaterLevel); u8g2Fonts.print("cm");
  // u8g2Fonts.print("   Flow: "); u8g2Fonts.print(WaterFlow); u8g2Fonts.print("m³/s");
  // u8g2Fonts.setCursor(10, 470); 
  // u8g2Fonts.print("Meldung: "); 
  // if(String(WaterReport) != "Kein Hochwasser")
  // {
  //   u8g2Fonts.setForegroundColor(red);
  //   u8g2Fonts.print(WaterReport);
  // }
  // else
  // {
  //   u8g2Fonts.setForegroundColor(black);
  //   u8g2Fonts.print(WaterReport);
  // }
//############ EM3      ##########################################################################################################

  int d1h = map(int(em3e[0]*10), 0, em3emax, 0, 140);  // 0 kwh - max kwh, size = 0 - 140px
  int d2h = map(int(em3e[1]*10), 0, em3emax, 0, 140);
  int d3h = map(int(em3e[2]*10), 0, em3emax, 0, 140);
  int d4h = map(int(em3e[3]*10), 0, em3emax, 0, 140);
  int d5h = map(int(em3e[4]*10), 0, em3emax, 0, 140);
  int d6h = map(int(em3e[5]*10), 0, em3emax, 0, 140);
  int d7h = map(int(em3e[6]*10), 0, em3emax, 0, 140);

  display.fillRect(445, 35, d1h, 7, black);
  display.fillRect(445, 48, d2h, 7, black);
  display.fillRect(445, 61, d3h, 7, black);
  display.fillRect(445, 74, d4h, 7, black);
  display.fillRect(445, 87, d5h, 7, black);
  display.fillRect(445, 100, d6h, 7, black);
  display.fillRect(445, 113, d7h, 7, red);

  u8g2Fonts.setFont(u8g2_font_helvB08_tf);
  u8g2Fonts.setForegroundColor(black);
  u8g2Fonts.setCursor(410, 43);   u8g2Fonts.print(em3day[0]); u8g2Fonts.setCursor(d1h + 450, 43);  u8g2Fonts.print(em3e[0],1);
  u8g2Fonts.setCursor(410, 56);   u8g2Fonts.print(em3day[1]); u8g2Fonts.setCursor(d2h + 450, 56);  u8g2Fonts.print(em3e[1],1);
  u8g2Fonts.setCursor(410, 69);   u8g2Fonts.print(em3day[2]); u8g2Fonts.setCursor(d3h + 450, 69);  u8g2Fonts.print(em3e[2],1);
  u8g2Fonts.setCursor(410, 82);   u8g2Fonts.print(em3day[3]); u8g2Fonts.setCursor(d4h + 450, 82);  u8g2Fonts.print(em3e[3],1);
  u8g2Fonts.setCursor(410, 95);   u8g2Fonts.print(em3day[4]); u8g2Fonts.setCursor(d5h + 450, 95);  u8g2Fonts.print(em3e[4],1);
  u8g2Fonts.setCursor(410, 108);  u8g2Fonts.print(em3day[5]); u8g2Fonts.setCursor(d6h + 450, 108); u8g2Fonts.print(em3e[5],1);
  u8g2Fonts.setForegroundColor(red);
  u8g2Fonts.setCursor(410, 121);  u8g2Fonts.print(em3day[6]); u8g2Fonts.setCursor(d7h + 450, 121); u8g2Fonts.print(em3e[6],1);

  // u8g2Fonts.setForegroundColor(black);
  // u8g2Fonts.setFont(u8g2_font_helvR14_tf);
  // u8g2Fonts.setCursor(680, 50);  u8g2Fonts.print("Total");
  // u8g2Fonts.setCursor(680, 70);  u8g2Fonts.print(em3total, 1); u8g2Fonts.print(" kWh");
//############ Area 3.0 ##########################################################################################################
  if(Area3Icon0 != -1) display.drawBitmap(641, 40,  iconID[Area3Icon0], 24, 24, GxEPD_BLACK);
  u8g2Fonts.setFont(u8g2_font_helvR14_tf);
  u8g2Fonts.setForegroundColor(black);
  u8g2Fonts.setFont(u8g2_font_helvR14_tf);
  u8g2Fonts.setCursor(670, 50);  u8g2Fonts.print(F(Area3Text0));
  u8g2Fonts.setCursor(670, 70);  u8g2Fonts.print(F(Area3Text1));
//############ Area 3.1 ##########################################################################################################
  if(Area3Icon1 != -1) display.drawBitmap(641, 88,  iconID[Area3Icon1], 24, 24, GxEPD_BLACK);
  u8g2Fonts.setFont(u8g2_font_helvR14_tf);
  u8g2Fonts.setForegroundColor(black);
  u8g2Fonts.setFont(u8g2_font_helvR14_tf);
  u8g2Fonts.setCursor(670, 98);  u8g2Fonts.print(F(Area3Text2));
  u8g2Fonts.setCursor(670, 118);  u8g2Fonts.print(F(Area3Text3));
//############ Location ##########################################################################################################
  // display.drawBitmap(641, 90,  iconID[Area3Icon1], 24, 24, GxEPD_BLACK);
  // u8g2Fonts.setFont(u8g2_font_helvR14_tf);
  // u8g2Fonts.setForegroundColor(black);
  // u8g2Fonts.setFont(u8g2_font_helvR14_tf);
  // u8g2Fonts.setCursor(670, 100);  u8g2Fonts.print(Area3Text2);
  // u8g2Fonts.setCursor(670, 120);  u8g2Fonts.print(Area3Text3);
//############ Area 4.0 ##########################################################################################################
  if(Area4Icon0 != -1) display.drawBitmap(406, 136,  iconID[Area4Icon0], 24, 24, GxEPD_BLACK);
  u8g2Fonts.setFont(u8g2_font_helvR14_tf);
  u8g2Fonts.setCursor(440, 154); 
  u8g2Fonts.print(F(Area4Text0));
//############ Area 4.1 ##########################################################################################################
  if(Area4Icon1 != -1) display.drawBitmap(406, 166,  iconID[Area4Icon1], 24, 24, GxEPD_BLACK);
  u8g2Fonts.setFont(u8g2_font_helvR14_tf);
  u8g2Fonts.setCursor(440, 184); 
  u8g2Fonts.print(F(Area4Text1));
//############ Area 4.2 ##########################################################################################################
  if(Area4Icon2 != -1) display.drawBitmap(600, 136,  iconID[Area4Icon2], 24, 24, GxEPD_BLACK);
  u8g2Fonts.setFont(u8g2_font_helvR14_tf);
  u8g2Fonts.setCursor(634, 154); 
  u8g2Fonts.print(F(Area4Text2));
//############ Area 4.2 ##########################################################################################################
  if(Area4Icon3 != -1) display.drawBitmap(600, 166,  iconID[Area4Icon3], 24, 24, GxEPD_BLACK);
  u8g2Fonts.setFont(u8g2_font_helvR14_tf);
  u8g2Fonts.setCursor(634, 184); 
  u8g2Fonts.print(F(Area4Text3));
//############ End ###############################################################################################################
//  display.display();
//  display.hibernate();
  }
  while (display.nextPage());
  display.powerOff();
  display.hibernate();
  
}
