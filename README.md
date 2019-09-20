# EPD 

Porting of [Waveshare](https://github.com/waveshare/e-Paper) official 2in9 lib for esp32 idf.

## Getting Started

To get started see [Espressif offical doc](https://docs.espressif.com/projects/esp-idf/en/latest/get-started/index.html)

### Usage

```
unsigned char image[EPD_WIDTH*EPD_HEIGHT/8];
Paint paint(image, 0, 0);
Epd epd;
	
if (epd.Init(lut_partial_update) != 0) {
    ESP_LOGE(kEPDTAG, "e-Paper init failed");
    vTaskDelay(2000 / portTICK_RATE_MS);
    return;
}

epd.ClearFrameMemory(0xFF); 
epd.DisplayFrame();
epd.ClearFrameMemory(0xFF); 
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

```