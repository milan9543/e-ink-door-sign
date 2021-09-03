/* Includes ------------------------------------------------------------------*/
#include "DEV_Config.h"
#include "EPD.h"
#include "GUI_Paint.h"
#include "imagedata.h"
#include "image_b.h"
#include "image_r.h"
#include <stdlib.h>

//Create a new image cache named IMAGE_BW and fill it with white
UBYTE *BlackImage, *RYImage;

String status_message = String("out-of-office");

// ------ redraw the boiler plate screen ---------------
void redraw() {
  printf("redrawing the screen\r\n");
  /*Horizontal screen*/
  //1.Draw black image
  Paint_SelectImage(BlackImage);
  Paint_Clear(WHITE);
  Paint_DrawString_EN(250, 100, "Dr Shane T. Fleming", &Font24, WHITE, BLACK);
  Paint_DrawString_EN(230, 150, "Status:", &Font24, WHITE, BLACK);


  //2.Draw red image
  Paint_SelectImage(RYImage);
  Paint_Clear(WHITE);
  Paint_DrawString_EN(360, 150, status_message.c_str(), &Font24, WHITE, BLACK);

  printf("EPD_Display\r\n");
  EPD_7IN5B_V2_Display(BlackImage, RYImage);
  DEV_Delay_ms(2000);

}

// ------------ Draw the base image -----------------------------
void drawImage() {
  printf("show image for array\r\n");
  EPD_7IN5B_V2_Display(screen_data_b, screen_data_r);
}

// --------------------------------------------------------------

/* Entry point ----------------------------------------------------------------*/
void setup()
{
  printf("STFs door sign\r\n");
  DEV_Module_Init();

  EPD_7IN5B_V2_Init();
  //EPD_7IN5B_V2_Clear();

  UWORD Imagesize = ((EPD_7IN5B_V2_WIDTH % 8 == 0) ? (EPD_7IN5B_V2_WIDTH / 8 ) : (EPD_7IN5B_V2_WIDTH / 8 + 1)) * EPD_7IN5B_V2_HEIGHT;
  if ((BlackImage = (UBYTE *)malloc(Imagesize)) == NULL) {
    printf("Failed to apply for black memory...\r\n");
    while(1);
  }
  if ((RYImage = (UBYTE *)malloc(Imagesize)) == NULL) {
    printf("Failed to apply for red memory...\r\n");
    while(1);
  }
  printf("NewImage:BlackImage and RYImage\r\n");
  Paint_NewImage(BlackImage, EPD_7IN5B_V2_WIDTH, EPD_7IN5B_V2_HEIGHT , 0, WHITE);
  Paint_NewImage(RYImage, EPD_7IN5B_V2_WIDTH, EPD_7IN5B_V2_HEIGHT , 0, WHITE);

  drawImage();

  //redraw();

  //printf("Goto Sleep...\r\n");
  //EPD_7IN5B_V2_Sleep();
  //free(BlackImage);
  //free(RYImage);
  //BlackImage = NULL;
  //RYImage = NULL;

}

/* The main loop -------------------------------------------------------------*/
void loop()
{
  delay(30000);
  status_message = String("out-of-office");
  //redraw();

  delay(30000);
  status_message = String("working from home");
  //redraw();

  delay(30000);
  status_message = String("in the CoFo");
  //redraw();
}

//DEV_Delay_ms(500);



  //Select Image
//  Paint_SelectImage(BlackImage);
//  Paint_Clear(WHITE);
//  Paint_SelectImage(RYImage);
//  Paint_Clear(WHITE);

//#if 1   // show image for array    
//  printf("show image for array\r\n");
//  EPD_7IN5B_V2_Display(gImage_7in5_V2_b, gImage_7in5_V2_ry);
//  DEV_Delay_ms(2000);
//#endif
