// display TFT = 320*240

#include <TFT_eSPI.h>   

TFT_eSPI tft = TFT_eSPI();

#define WHITE       0xFFFF
#define BLACK       0x0000
#define BLUE        0x001F
#define RED         0xF800
#define GREEN       0x07E0
#define CYAN        0x07FF
#define MAGENTA     0xF81F
#define YELLOW      0xFFE0
#define GREY        0x2108

#define DEG2RAD 0.0174532925

int rotazione = 0;            // rotazione
int colore = 255;

void setup() {
  Serial.begin(115200);
  tft.init ();
  tft.setRotation (3);                                                        
  tft.fillScreen (TFT_BLACK);
}

void loop() {
  int ramo = 40;                // lunghezza ramio
  int livello = 12;             // numero livelli
  int angolo_dex = 15;          // angolo destra
  int angolo_sin = 25;          // angolo sinistra

  tft.fillScreen (TFT_BLACK);

  albero(ramo, livello, angolo_dex, angolo_sin, 160, 0, 160, ramo);
  delay(2000);
}

// funzione che disegna una Y
void albero(int ramo, int livello, int angolo_dex, int angolo_sin, int pos_x1, int pos_y1, int pos_x2, int pos_y2) {    
  if (livello > 0) { 

    // disegno la linea base
    tft.drawLine(pos_x1, pos_y1, pos_x2, pos_y2, livello * 5000);
    
    rotazione = rotazione + angolo_sin;

    // chiamata ricorsiva
    albero(0.75 * ramo, livello - 1, angolo_dex, angolo_sin, pos_x2, pos_y2, pos_x2 + ramo * sin(DEG2RAD * rotazione), pos_y2 + ramo * cos(DEG2RAD * rotazione));

    rotazione = rotazione - angolo_sin - angolo_dex;

    // chiamata ricorsiva
    albero(0.75 * ramo, livello - 1, angolo_dex, angolo_sin, pos_x2, pos_y2, pos_x2 + ramo * sin(DEG2RAD * rotazione), pos_y2 + ramo * cos(DEG2RAD * rotazione));

    rotazione = rotazione + angolo_dex;

    // disegno la linea base
    tft.drawLine(pos_x1, pos_y1, pos_x2, pos_y2, livello * 5000);
  }
}
