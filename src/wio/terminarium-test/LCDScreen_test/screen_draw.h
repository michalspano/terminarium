//Define acceptable boundaries
#define MAX_LIMIT 75
#define MIN_LIMIT 25

extern Screen screen;

void dashboardScreen(int t, int h, int v, int m, int li, int lo) {

  //Set dashboard lines
  spr.drawFastVLine(106,50,190,TFT_DARKGREEN); //Drawing 1st verticle line
  spr.drawFastVLine(212,50,190,TFT_DARKGREEN); // Drawing 2nd vertical line
  spr.drawFastHLine(0,140,320,TFT_DARKGREEN); //Drawing horizontal line

  //Setting temperature
  spr.setTextSize(2);
  spr.setTextColor(TFT_WHITE);
  spr.drawString("Temp",30,65);
  spr.setTextSize(3);
  if(t > MAX_LIMIT || t < MIN_LIMIT){
    spr.setTextColor(TFT_RED);
  }
  spr.drawNumber(t,25,95); //Display temperature values 
  spr.drawString("C",65,95);

  //Setting humidity
  spr.setTextSize(2);
  spr.setTextColor(TFT_WHITE);
  spr.drawString("Humi",140,65);
  spr.setTextSize(3);
  if(h > MAX_LIMIT || h < MIN_LIMIT){
    spr.setTextColor(TFT_RED);
  }
  spr.drawNumber(h,115,95); //Display humidity values as a percentage
  spr.drawString("%RH",155,95);

  //Setting vibration
  spr.setTextSize(2);
  spr.setTextColor(TFT_WHITE);
  spr.drawString("Vib",250,65);
  spr.setTextSize(3);
  if(v == 0) {
    spr.setTextColor(TFT_RED);
    spr.drawString("Yes",242,95);
  } else {
    spr.drawString("No",251,95);
  }

  //Setting moisture
  spr.setTextSize(2);
  spr.setTextColor(TFT_WHITE);
  spr.drawString("Moist",25,160);
  spr.setTextSize(3);
  if(m > MAX_LIMIT || m < MIN_LIMIT){
    spr.setTextColor(TFT_RED);
  }
  spr.drawNumber(m,30,190); //Display humidity values 
  spr.drawString("%",70,190);
  
  //Setting light 
  spr.setTextSize(2);
  spr.setTextColor(TFT_WHITE);
  spr.drawString("Light",134,160);
  spr.setTextSize(3);
  if(li > MAX_LIMIT || li < MIN_LIMIT){
    spr.setTextColor(TFT_RED);
  }
  spr.drawNumber(li,135,190); //Display sensor values as percentage  
  spr.drawString("%",175,190);

  //Setting loudness
  spr.setTextSize(2);
  spr.setTextColor(TFT_WHITE);
  spr.drawString("Loud",245,160);
  spr.setTextSize(3);
  if(lo > MAX_LIMIT || lo < MIN_LIMIT){
    spr.setTextColor(TFT_RED);
  }
  spr.drawNumber(lo,240,190); //Display sensor values as percentage  
  spr.drawString("%",280,190);
}

void drawStatus(int value) {
  spr.setTextSize(2);
  spr.setTextColor(TFT_WHITE);
  spr.drawString("STATUS:",60,175);
  if(value > MAX_LIMIT) {
    spr.setTextColor(TFT_RED);
    spr.drawString("TOO HIGH", 160,175);
  } else if (value < MIN_LIMIT) {
    spr.setTextColor(TFT_RED);
    spr.drawString("TOO LOW", 172,175);
  } else {
    spr.setTextColor(TFT_GREEN);
    spr.drawString("OK",200,175);
  }
}

void drawTriangles() {
  spr.fillTriangle(55, 115, 55, 135, 35, 125, TFT_WHITE);
  spr.fillTriangle(260, 115, 260, 135, 280, 125, TFT_WHITE);
}

void tempScreen(int t) {

  //Draw temperature reading
  spr.setTextSize(3);
  spr.setTextColor(TFT_WHITE);
  spr.drawString("Temperature",60,75);
  if(t < MIN_LIMIT || t > MAX_LIMIT) {
    spr.setTextColor(TFT_RED);
  }
  spr.drawNumber(t,132,115); 
  spr.drawString("C",172,115);
  
  drawStatus(t);

  drawTriangles();
}

void humiScreen(int h) {

  //Draw humidity reading
  spr.setTextSize(3);
  spr.setTextColor(TFT_WHITE);
  spr.drawString("Humidity",87,75);
  if(h < MIN_LIMIT || h > MAX_LIMIT) {
    spr.setTextColor(TFT_RED);
  }
  spr.drawNumber(h,105,115); 
  spr.drawString("% RH",145,115);
  
  drawStatus(h);

  drawTriangles();
}

void vibScreen(int v) {

  //Draw temperature reading
  spr.setTextSize(3);
  spr.setTextColor(TFT_WHITE);
  spr.drawString("Vibration",80,75);
  if(v == 0) {
    spr.setTextColor(TFT_RED);
    spr.drawString("Vibrating",80,115);
  } else {
    spr.setTextColor(TFT_GREEN);
    spr.drawString("NOT",135,115);
    spr.setTextColor(TFT_WHITE);
    spr.drawString("Vibrating",80,155);
  }

  drawTriangles(); 
}

void moistScreen(int m) {

  //Draw moisture reading
  spr.setTextSize(3);
  spr.setTextColor(TFT_WHITE);
  spr.drawString("Moisture",91,75);
  if(m < MIN_LIMIT || m > MAX_LIMIT) {
    spr.setTextColor(TFT_RED);
  }
  spr.drawNumber(m,132,115); 
  spr.drawString("%",172,115);
  
  drawStatus(m);

  drawTriangles();
}

void lightScreen(int li) {

  //Draw moisture reading
  spr.setTextSize(3);
  spr.setTextColor(TFT_WHITE);
  spr.drawString("Light",115,75);
  if(li < MIN_LIMIT || li > MAX_LIMIT) {
    spr.setTextColor(TFT_RED);
  }
  spr.drawNumber(li,132,115); 
  spr.drawString("%",172,115);
  
  //Draw Status
  drawStatus(li);

  drawTriangles();
}

void loudScreen(int lo) {

  //Draw moisture reading
  spr.setTextSize(3);
  spr.setTextColor(TFT_WHITE);
  spr.drawString("Loudness",91,75);
  if(lo < MIN_LIMIT || lo > MAX_LIMIT) {
    spr.setTextColor(TFT_RED);
  }
  spr.drawNumber(lo,132,115); 
  spr.drawString("%",172,115);
  
  drawStatus(lo);

  drawTriangles();
}

void drawScreen(int t, int h, int v, int m, int li, int lo) {
  
  //Setting the background color and title header, present in all screens
  spr.fillSprite(TFT_BLACK); //Fill background with black color
  spr.fillRect(0,0,320,50,TFT_DARKGREEN); //Rectangle fill with dark green 
  spr.setTextColor(TFT_WHITE); //Setting text color
  spr.setTextSize(3); //Setting text size 
  spr.drawString("Terminarium",60,15); //Drawing a text string 

  switch(screen) {

    case TEMP:
      tempScreen(t);
      break;
    case HUMI:
      humiScreen(h);
      break;
    case VIB:
      vibScreen(v);
      break; 
    case MOIST:
      moistScreen(m);
      break;
    case LIGHT:
      lightScreen(li);
      break;
    case LOUD:
      loudScreen(lo);
      break;
    default:
      dashboardScreen(t, h, v, m, li, lo);
      break;
  }
}