//Define acceptable boundaries
#define MAX_LIMIT 75
#define MIN_LIMIT 25

extern TFT_eSprite spr;
extern Screen screen;

void dashboardScreen(int temp, int humi, int vib, int moist, int light, int loud) {

  //Set dashboard lines
  spr.drawFastVLine(106,50,190,TFT_DARKGREEN); //Drawing 1st verticle line
  spr.drawFastVLine(212,50,190,TFT_DARKGREEN); // Drawing 2nd vertical line
  spr.drawFastHLine(0,140,320,TFT_DARKGREEN); //Drawing horizontal line

  //Setting temperature
  spr.setTextSize(2);
  spr.setTextColor(TFT_WHITE);
  spr.drawString("Temp",30,65);
  spr.setTextSize(3);
  if(temp > MAX_LIMIT || temp < MIN_LIMIT){
    spr.setTextColor(TFT_RED);
  }
  spr.drawNumber(temp,25,95); //Display temperature values 
  spr.drawString("C",65,95);

  //Setting humidity
  spr.setTextSize(2);
  spr.setTextColor(TFT_WHITE);
  spr.drawString("Humi",140,65);
  spr.setTextSize(3);
  if(humi > MAX_LIMIT || humi < MIN_LIMIT){
    spr.setTextColor(TFT_RED);
  }
  spr.drawNumber(humi,115,95); //Display humidity values as a percentage
  spr.drawString("%RH",155,95);

  //Setting vibration
  spr.setTextSize(2);
  spr.setTextColor(TFT_WHITE);
  spr.drawString("Vib",250,65);
  spr.setTextSize(3);
  if(vib == 0) {
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
  if(moist > MAX_LIMIT || moist < MIN_LIMIT){
    spr.setTextColor(TFT_RED);
  }
  spr.drawNumber(moist,30,190); //Display humidity values 
  spr.drawString("%",70,190);
  
  //Setting light 
  spr.setTextSize(2);
  spr.setTextColor(TFT_WHITE);
  spr.drawString("Light",134,160);
  spr.setTextSize(3);
  if(light > MAX_LIMIT || light < MIN_LIMIT){
    spr.setTextColor(TFT_RED);
  }
  spr.drawNumber(light,135,190); //Display sensor values as percentage  
  spr.drawString("%",175,190);

  //Setting loudness
  spr.setTextSize(2);
  spr.setTextColor(TFT_WHITE);
  spr.drawString("Loud",245,160);
  spr.setTextSize(3);
  if(loud > MAX_LIMIT || loud < MIN_LIMIT){
    spr.setTextColor(TFT_RED);
  }
  spr.drawNumber(loud,240,190); //Display sensor values as percentage  
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

void tempScreen(int temp) {

  //Draw temperature reading
  spr.setTextSize(3);
  spr.setTextColor(TFT_WHITE);
  spr.drawString("Temperature",60,75);
  if(temp < MIN_LIMIT || temp > MAX_LIMIT) {
    spr.setTextColor(TFT_RED);
  }
  spr.drawNumber(temp,132,115); 
  spr.drawString("C",172,115);
  
  drawStatus(temp);

  drawTriangles();
}

void humiScreen(int humi) {

  //Draw humidity reading
  spr.setTextSize(3);
  spr.setTextColor(TFT_WHITE);
  spr.drawString("Humidity",87,75);
  if(humi < MIN_LIMIT || humi > MAX_LIMIT) {
    spr.setTextColor(TFT_RED);
  }
  spr.drawNumber(humi,105,115); 
  spr.drawString("% RH",145,115);
  
  drawStatus(humi);

  drawTriangles();
}

void vibScreen(int vib) {

  //Draw temperature reading
  spr.setTextSize(3);
  spr.setTextColor(TFT_WHITE);
  spr.drawString("Vibration",80,75);
  if(vib == 0) {
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

void moistScreen(int moist) {

  //Draw moisture reading
  spr.setTextSize(3);
  spr.setTextColor(TFT_WHITE);
  spr.drawString("Moisture",91,75);
  if(moist < MIN_LIMIT || moist > MAX_LIMIT) {
    spr.setTextColor(TFT_RED);
  }
  spr.drawNumber(moist,132,115); 
  spr.drawString("%",172,115);
  
  drawStatus(moist);

  drawTriangles();
}

void lightScreen(int light) {

  //Draw moisture reading
  spr.setTextSize(3);
  spr.setTextColor(TFT_WHITE);
  spr.drawString("Light",115,75);
  if(light < MIN_LIMIT || light > MAX_LIMIT) {
    spr.setTextColor(TFT_RED);
  }
  spr.drawNumber(light,132,115); 
  spr.drawString("%",172,115);
  
  //Draw Status
  drawStatus(light);

  drawTriangles();
}

void loudScreen(int loud) {

  //Draw moisture reading
  spr.setTextSize(3);
  spr.setTextColor(TFT_WHITE);
  spr.drawString("Loudness",91,75);
  if(loud < MIN_LIMIT || loud > MAX_LIMIT) {
    spr.setTextColor(TFT_RED);
  }
  spr.drawNumber(loud,132,115); 
  spr.drawString("%",172,115);
  
  drawStatus(loud);

  drawTriangles();
}

void drawScreen(int temp, int humi, int vib, int moist, int light, int loud) {
  
  //Setting the background color and title header, present in all screens
  spr.fillSprite(TFT_BLACK); //Fill background with black color
  spr.fillRect(0,0,320,50,TFT_DARKGREEN); //Rectangle fill with dark green 
  spr.setTextColor(TFT_WHITE); //Setting text color
  spr.setTextSize(3); //Setting text size 
  spr.drawString("Terminarium",60,15); //Drawing a text string 

  switch(screen) {

    case TEMP:
      tempScreen(temp);
      break;
    case HUMI:
      humiScreen(humi);
      break;
    case VIB:
      vibScreen(vib);
      break; 
    case MOIST:
      moistScreen(moist);
      break;
    case LIGHT:
      lightScreen(light);
      break;
    case LOUD:
      loudScreen(loud);
      break;
    default:
      dashboardScreen(temp, humi, vib, moist, light, loud);
      break;
  }
}