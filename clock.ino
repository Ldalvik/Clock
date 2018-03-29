#include <neopixel.h>

#include <Particle.h>

SYSTEM_MODE(AUTOMATIC)

#define PIXEL_PIN D6
#define PIXEL_COUNT 149
#define PIXEL_TYPE WS2812B

int hours[14][2] = {
  {0, 0},
  {63, 67},  //one
  {75, 78},  //two
  {55, 61},  //three
  {80, 84},  //four
  {85, 89},  //five
  {90, 92},  //six
  {106, 112}, //seven
  {99, 104}, //eight
  {93, 97},  //nine
  {113, 118}, //ten
  {119, 130}, //eleven
  {141, 149}, //twelve
  {63, 67}   //one (for past half an hour)
};

int minutes[30][4] = {
  {0, 0},
  {37, 41},  //five
  {14, 17},  //ten
  {27, 36},  //quarter
  {19, 26},  //twenty
  {19, 26},  //twenty
  {7, 13},   //half
  {19, 26},  //twenty
  {19, 26},  //twenty
  {27, 36},  //quarter
  {14, 17},  //ten
  {37, 41},  //five
  {0, 3},   //it
  {4, 5},   //is
  {42, 51}, //minutes
  {52, 54}, //to
  {68, 73},  //past
  {131, 139} //oclock
};

int minuteControl[12][4] = {
  {0, 0, 0, 0},
  {1, 0, 14, 16},
  {2, 0, 14, 16},
  {3, 0, 0, 16},
  {4, 0, 14, 16},
  {5, 1, 14, 16},
  {6, 0, 0, 16},
  {7, 1, 14, 15},
  {8, 0, 14, 15},
  {9, 0, 0, 15},
  {10, 0, 14, 15},
  {11, 0, 14, 15}
};

int rainbow[150][3]{
{255,0, 0},
{250,5, 0},
{245,10, 0},
{240,15, 0},
{235,20, 0},
{230,25, 0},
{225,30, 0},
{220,35, 0},
{215,40, 0},
{210,45, 0},
{205,50, 0},
{200,55, 0},
{195,60, 0},
{190,65, 0},
{185,70, 0},
{180,75, 0},
{175,80, 0},
{170,85, 0},
{165,90, 0},
{160,95, 0},
{155,100, 0},
{150,105, 0},
{145,110, 0},
{140,115, 0},
{135,120, 0},
{130,125, 0},
{125,130, 0},
{120,135, 0},
{115,140, 0},
{110,145, 0},
{105,150, 0},
{100,155, 0},
{95,160, 0},
{90,165, 0},
{85,170, 0},
{80,175, 0},
{75,180, 0},
{70,185, 0},
{65,190, 0},
{60,195, 0},
{55,200, 0},
{50,205, 0},
{45,210, 0},
{40,215, 0},
{35,220, 0},
{30,225, 0},
{25,230, 0},
{20,235, 0},
{15,240, 0},
{10,245, 0},
{0,255, 0},
{0,250, 5},
{0,245, 10},
{0,240, 15},
{0,235, 20},
{0,230, 25},
{0,225, 30},
{0,220, 35},
{0,215, 40},
{0,210, 45},
{0,205, 50},
{0,200, 55},
{0,195, 60},
{0,190, 65},
{0,185, 70},
{0,180, 75},
{0,175, 80},
{0,170, 85},
{0,165, 90},
{0,160, 95},
{0,155, 100},
{0,150, 105},
{0,145, 110},
{0,140, 115},
{0,135, 120},
{0,130, 125},
{0,125, 130},
{0,120, 135},
{0,115, 140},
{0,110, 145},
{0,105, 150},
{0,100, 155},
{0,95, 160},
{0,90, 165},
{0,85, 170},
{0,80, 175},
{0,75, 180},
{0,70, 185},
{0,65, 190},
{0,60, 195},
{0,55, 200},
{0,50, 205},
{0,45, 210},
{0,40, 215},
{0,35, 220},
{0,30, 225},
{0,25, 230},
{0,20, 235},
{0,15, 240},
{0,10, 245},
{0, 0, 255},
{5, 0, 250},
{10, 0, 245},
{15, 0, 240},
{20, 0, 235},
{25, 0, 230},
{30, 0, 225},
{35, 0, 220},
{40, 0, 215},
{45, 0, 210},
{50, 0, 205},
{55, 0, 200},
{60, 0, 195},
{65, 0, 190},
{70, 0, 185},
{75, 0, 180},
{80, 0, 175},
{85, 0, 170},
{90, 0, 165},
{95, 0, 160},
{100, 0, 155},
{105, 0, 150},
{110, 0, 145},
{115, 0, 140},
{120, 0, 135},
{125, 0, 130},
{130, 0, 125},
{135, 0, 120},
{140, 0, 115},
{145, 0, 110},
{150, 0, 105},
{155, 0, 100},
{160, 0, 95},
{165, 0, 90},
{170, 0, 85},
{175, 0, 80},
{180, 0, 75},
{185, 0, 70},
{190, 0, 65},
{195, 0, 60},
{200, 0, 55},
{205, 0, 50},
{210, 0, 45},
{215, 0, 40},
{220, 0, 35},
{225, 0, 30},
{230, 0, 25},
{235, 0, 20},
{240, 0, 15},
{245, 0, 10}
};

Adafruit_NeoPixel strip(PIXEL_COUNT, PIXEL_PIN, PIXEL_TYPE);

int number;
uint8_t r = 0;
uint8_t g = 0;
uint8_t b = 0;
int red;
int green;
int blue;

int solidred = 149;
int solidgreen;
int solidblue;

int redFraction;
int greenFraction;
int blueFraction;

String arg;

bool gradient = false;

void setup() {
  strip.begin();
  Time.zone(-4);
}


void loop() {
  int minute = Time.minute();
  int hour = Time.hourFormat12();
  
    Particle.function("color", colorToggle);
    setTime(hour, minute / 5);
  
}

int colorToggle(String command) {

  if (strstr(command, "redslide")) {
    number = command.remove(0, 8).toInt();
    solidred = number;
    gradient = false;
    arg="";
  }

  if (strstr(command, "greenslide")) {
    number = command.remove(0, 10).toInt();
    solidgreen = number;
    gradient = false;
    arg="";
  }

  if (strstr(command, "blueslide")) {
    number = command.remove(0, 9).toInt();
    solidblue = number;
    gradient = false;
    arg="";
  }

  if (command == "reset") {
    System.sleep(SLEEP_MODE_DEEP,1);
  }

  if (command == "rainbow") {
    arg = "rainbow";
  }
  
   if (command == "xmas") {
    arg = "xmas";
  }
  
  if (command == "superRainbow") {
    arg = "superRainbow";
  }

  if (command == "blink") {
    setBlink(255, 0, 0);
    delay(200);
    setBlink(0, 0, 0);
    delay(200);
    setBlink(0, 255, 0);
    delay(200);
    setBlink(0, 0, 0);
    delay(200);
    setBlink(0, 0, 255);
    delay(200);
    setBlink(255, 0, 0);
    delay(200);
    setBlink(0, 0, 0);
    delay(200);
    setBlink(0, 255, 0);
    delay(200);
    setBlink(0, 0, 0);
    delay(200);
    setBlink(0, 0, 255);
    delay(200);
    setBlink(0, 0, 0);
    delay(300);
  }
  
  if (strstr(command, "turnOn=")) {
    int led = command.remove(0, 7).toInt();
        turnOnLed(led);
  }
  
     if (strstr(command, "turnOnMultiple=")) {
            String leds = command.remove(0,15);            
            //Particle.publish("led_params", leds);
            int ledStart = leds.remove(leds.indexOf("&"), leds.length()).toInt();
            int ledEnd = leds.remove(0, 2).toInt();
            Particle.publish("start_end", String(ledStart)+"&"+String(ledEnd));
            turnOnMultipleLeds(ledStart, ledEnd);
    }

  if (strstr(command, "gradientRed=")) {
    String rgbE = command.remove(0, 12);
    red = (uint8_t) rgbE.toInt();
    gradient = true;
    arg="";
  }

  if (strstr(command, "gradientGreen=")) {
    String rgbE = command.remove(0, 14);
    green = (uint8_t) rgbE.toInt();
    gradient = true;
    arg="";
  }

  if (strstr(command, "gradientBlue=")) {
    String rgbE = command.remove(0, 13);
    blue = (uint8_t) rgbE.toInt();
    gradient = true;
    arg="";
  }

  if (strstr(command, "redFraction=")) {
    String rgbE = command.remove(0, 12);
    redFraction = rgbE.toInt();
    gradient = true;
    arg="";
  }

  if (strstr(command, "greenFraction=")) {
    String rgbE = command.remove(0, 14);
    greenFraction = rgbE.toInt();
    gradient = true;
    arg="";
  }

  if (strstr(command, "blueFraction=")) {
    String rgbE = command.remove(0, 13);
    blueFraction = rgbE.toInt();
    gradient = true;
    arg="";
  }
}

void turnOnLed(int ledNumber){
    strip.setPixelColor(ledNumber, solidred, solidgreen, solidblue);
    strip.show();
}

void turnOnMultipleLeds(int start, int end){
    for(int led = start; led <= end; led++) {
        strip.setPixelColor(led, solidred, solidgreen, solidblue);
        strip.show();
    }
}

void setTime(int hour, int fraction) {
if (arg == "rainbow") {
    setRainbow(hour, fraction);
} else if (arg == "xmas") {
    setXmas(hour, fraction);
} else if (arg == "superRainbow") {
    setSuperRainbow(hour, fraction);
} else {
  for (int led = 0; led < 149; led++) {
    if (fraction > 6) {
      if (led >= 0 && led <= 5 ||
          led >= hours[hour + 1][0] && led <= hours[hour + 1][1] ||
          led >= minutes[minuteControl[fraction][0]] [0] && led <= minutes[minuteControl[fraction][0]] [1] ||
          led >= minutes[minuteControl[fraction][1]] [0] && led <= minutes[minuteControl[fraction][1]] [1] ||
          led >= minutes[minuteControl[fraction][2]] [0] && led <= minutes[minuteControl[fraction][2]] [1] ||
          led >= minutes[minuteControl[fraction][3]] [0] && led <= minutes[minuteControl[fraction][3]] [1] ||
          led >= 131 && led <= 139) {
        if (gradient == true) {
          strip.setPixelColor(led, r = abs(redFraction * (red - led)), g = abs(greenFraction * (green - led)), b = abs(blueFraction * (blue - led)));
        } else {
          strip.setPixelColor(led, solidred, solidgreen, solidblue);
        }
      } else {
        strip.setPixelColor(led, 0, 0, 0);
      }
      strip.show();
    } else {
      if (led >= 0 && led <= 5 ||
          led >= hours[hour][0] && led <= hours[hour][1] ||
          led >= minutes[minuteControl[fraction][0]] [0] && led <= minutes[minuteControl[fraction][0]] [1] ||
          led >= minutes[minuteControl[fraction][1]] [0] && led <= minutes[minuteControl[fraction][1]] [1] ||
          led >= minutes[minuteControl[fraction][2]] [0] && led <= minutes[minuteControl[fraction][2]] [1] ||
          led >= minutes[minuteControl[fraction][3]] [0] && led <= minutes[minuteControl[fraction][3]] [1] ||
          led >= 131 && led <= 139) {
        if (gradient == true) {
          strip.setPixelColor(led, r = abs(redFraction * (red - led)), g = abs(greenFraction * (green - led)), b = abs(blueFraction * (blue - led)));
        } else {
          strip.setPixelColor(led, solidred, solidgreen, solidblue);
        }
      } else {
        strip.setPixelColor(led, 0, 0, 0);
      }
      strip.show();
    }
  }
  if (gradient == true) {
    r = 0;
    g = 0;
    b = 0;
  }
}
}

void setBlink(int r, int g, int b){
    for (int led = 0; led < 149; led++) {
        strip.setPixelColor(led, r, g, b);
    }
    strip.show();
}

void setRainbow(int hour, int fraction){
  for (int led = 0; led < 149; led++) {
    if (fraction > 6) {
      if (led >= 0 && led <= 6 ||
          led >= hours[hour + 1][0] && led <= hours[hour + 1][1] ||
          led >= minutes[minuteControl[fraction][0]] [0] && led <= minutes[minuteControl[fraction][0]] [1] ||
          led >= minutes[minuteControl[fraction][1]] [0] && led <= minutes[minuteControl[fraction][1]] [1] ||
          led >= minutes[minuteControl[fraction][2]] [0] && led <= minutes[minuteControl[fraction][2]] [1] ||
          led >= minutes[minuteControl[fraction][3]] [0] && led <= minutes[minuteControl[fraction][3]] [1] ||
          led >= 131 && led <= 139) {
                strip.setPixelColor(led, rainbow[led][0], rainbow[led][1], rainbow[led][2]);
                strip.show();
      } else {
        strip.setPixelColor(led, 0, 0, 0);
      }
    } else {
      if (led >= 0 && led <= 6 ||
          led >= hours[hour][0] && led <= hours[hour][1] ||
          led >= minutes[minuteControl[fraction][0]] [0] && led <= minutes[minuteControl[fraction][0]] [1] ||
          led >= minutes[minuteControl[fraction][1]] [0] && led <= minutes[minuteControl[fraction][1]] [1] ||
          led >= minutes[minuteControl[fraction][2]] [0] && led <= minutes[minuteControl[fraction][2]] [1] ||
          led >= minutes[minuteControl[fraction][3]] [0] && led <= minutes[minuteControl[fraction][3]] [1] ||
          led >= 131 && led <= 139) {
                strip.setPixelColor(led, rainbow[led][0], rainbow[led][1], rainbow[led][2]);
                strip.show();
      } else {
        strip.setPixelColor(led, 0, 0, 0);
      }
  }
}
}

void setXmas(int hour, int fraction){
  for (int led = 0; led < 149; led++) {
      int colors = random(0, 150);
    if (fraction > 6) {
      if (led >= 0 && led <= 6 ||
          led >= hours[hour + 1][0] && led <= hours[hour + 1][1] ||
          led >= minutes[minuteControl[fraction][0]] [0] && led <= minutes[minuteControl[fraction][0]] [1] ||
          led >= minutes[minuteControl[fraction][1]] [0] && led <= minutes[minuteControl[fraction][1]] [1] ||
          led >= minutes[minuteControl[fraction][2]] [0] && led <= minutes[minuteControl[fraction][2]] [1] ||
          led >= minutes[minuteControl[fraction][3]] [0] && led <= minutes[minuteControl[fraction][3]] [1] ||
          led >= 131 && led <= 139) {
                strip.setPixelColor(led, rainbow[colors][0], rainbow[colors][1], 0);
                strip.show();
      } else {
        strip.setPixelColor(led, 0, 0, 0);
      }
    } else {
      if (led >= 0 && led <= 6 ||
          led >= hours[hour][0] && led <= hours[hour][1] ||
          led >= minutes[minuteControl[fraction][0]] [0] && led <= minutes[minuteControl[fraction][0]] [1] ||
          led >= minutes[minuteControl[fraction][1]] [0] && led <= minutes[minuteControl[fraction][1]] [1] ||
          led >= minutes[minuteControl[fraction][2]] [0] && led <= minutes[minuteControl[fraction][2]] [1] ||
          led >= minutes[minuteControl[fraction][3]] [0] && led <= minutes[minuteControl[fraction][3]] [1] ||
          led >= 131 && led <= 139) {
                strip.setPixelColor(led, rainbow[colors][0], rainbow[colors][1], 0);
                strip.show();
      } else {
        strip.setPixelColor(led, 0, 0, 0);
      }
  }
}
}

void clearBoard() {
  for (int x = 0; x < 149; x++) {
    strip.setPixelColor(x, 0, 0, 0);
  }
}

String getValue(String data, char separator, int index)
{
    int found = 0;
    int strIndex[] = { 0, -1 };
    int maxIndex = data.length() - 1;

    for (int i = 0; i <= maxIndex && found <= index; i++) {
        if (data.charAt(i) == separator || i == maxIndex) {
            found++;
            strIndex[0] = strIndex[1] + 1;
            strIndex[1] = (i == maxIndex) ? i+1 : i;
        }
    }
    return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}

void setSuperRainbow(int hour, int fraction){
  for (int led = 0; led < 149; led++) {
      int colors = random(0, 150);
    if (fraction > 6) {
      if (led >= 0 && led <= 6 ||
          led >= hours[hour + 1][0] && led <= hours[hour + 1][1] ||
          led >= minutes[minuteControl[fraction][0]] [0] && led <= minutes[minuteControl[fraction][0]] [1] ||
          led >= minutes[minuteControl[fraction][1]] [0] && led <= minutes[minuteControl[fraction][1]] [1] ||
          led >= minutes[minuteControl[fraction][2]] [0] && led <= minutes[minuteControl[fraction][2]] [1] ||
          led >= minutes[minuteControl[fraction][3]] [0] && led <= minutes[minuteControl[fraction][3]] [1] ||
          led >= 131 && led <= 139) {
                strip.setPixelColor(led, rainbow[colors][0], rainbow[colors][1], rainbow[colors][2]);
                strip.show();
      } else {
        strip.setPixelColor(led, 0, 0, 0);
      }
    } else {
      if (led >= 0 && led <= 6 ||
          led >= hours[hour][0] && led <= hours[hour][1] ||
          led >= minutes[minuteControl[fraction][0]] [0] && led <= minutes[minuteControl[fraction][0]] [1] ||
          led >= minutes[minuteControl[fraction][1]] [0] && led <= minutes[minuteControl[fraction][1]] [1] ||
          led >= minutes[minuteControl[fraction][2]] [0] && led <= minutes[minuteControl[fraction][2]] [1] ||
          led >= minutes[minuteControl[fraction][3]] [0] && led <= minutes[minuteControl[fraction][3]] [1] ||
          led >= 131 && led <= 139) {
                strip.setPixelColor(led, rainbow[colors][0], rainbow[colors][1], rainbow[colors][2]);
                strip.show();
      } else {
        strip.setPixelColor(led, 0, 0, 0);
      }
  }
}
}
