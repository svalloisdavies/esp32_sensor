
#include "driver/gpio.h"
#include "driver/i2c.h"
#include "ssd1306.hpp"

const int SSD1306_I2C_MASTER_SDA = 21;
const int SSD1306_I2C_MASTER_SCL = 22;

// static const char *TAG = "main";

extern "C" {
void app_main();
}

void app_main(void)
{
	std::unique_ptr<sbn::i2c_port> i = std::make_unique<sbn::i2c_port>(
		I2C0, SSD1306_I2C_MASTER_SDA, SSD1306_I2C_MASTER_SCL,
		GPIO_PULLUP_ENABLE, GPIO_PULLUP_ENABLE);

	sbn::ssd1306 s{ std::move(i) };
}
