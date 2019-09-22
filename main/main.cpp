/**
 *
 * @author Paolo Gatti
 *
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documnetation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to  whom the Software is
 * furished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS OR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include "epd2in9.h"
#include "epdpaint.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/timer.h"
#include "imagedata.h"
#include "strings.h"

static const char * kEPDTAG = "EPD";

unsigned char image[EPD_WIDTH*EPD_HEIGHT/8];
Paint paint(image, 0, 0);    // width should be the multiple of 8
Epd epd;

extern "C" void app_main() {

  if (epd.Init(lut_partial_update) != 0) {
      ESP_LOGE(kEPDTAG, "e-Paper init failed");
      vTaskDelay(2000 / portTICK_RATE_MS);
      return;
  }
  ESP_LOGE(kEPDTAG, "e-Paper initialized");

  /**
   *  there are 2 memory areas embedded in the e-paper display
   *  and once the display is refreshed, the memory area will be auto-toggled,
   *  i.e. the next action of SetFrameMemory will set the other memory area
   *  therefore you have to clear the frame memory twice.
   */
  epd.ClearFrameMemory(0xFF);   // bit set = white, bit reset = black
  epd.DisplayFrame();
  epd.ClearFrameMemory(0xFF);   // bit set = white, bit reset = black
  epd.DisplayFrame();

  paint.SetRotate(ROTATE_90);
  paint.SetWidth(EPD_WIDTH);
  paint.SetHeight(EPD_HEIGHT);

  paint.Clear(UNCOLORED);

  paint.DrawStringAt(0, 0, "e-Paper Demo F24", &Font24, COLORED);

  paint.DrawStringAt(0, 28, "e-Paper Demo F20", &Font20, COLORED);

  paint.DrawStringAt(0, 50, "e-Paper Demo F16", &Font16, COLORED);

  paint.DrawStringAt(0, 70, "e-Paper Demo F12", &Font12, COLORED);

  paint.DrawStringAt(0, 90, "e-Paper Demo F8", &Font8, COLORED);

  epd.SetFrameMemory(paint.GetImage(), 0, 0, paint.GetWidth(), paint.GetHeight());

  epd.DisplayFrame();

  vTaskDelay(5000 / portTICK_RATE_MS);

  paint.Clear(UNCOLORED);

  epd.SetFrameMemory(IMAGE_DATA);

  epd.DisplayFrame();
}



