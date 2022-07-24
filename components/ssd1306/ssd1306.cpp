#include "ssd1306.hpp"

namespace sbn
{

void i2c_port::addr(int addr)
{
	dev_.addr = addr;
}

esp_err_t i2c_port::scan()
{
	esp_err_t res = ESP_OK;
	printf("     0  1  2  3  4  5  6  7  8  9  a  b  c  d  e  f");
	for (uint8_t addr = 0x00; addr <= 0x7F; addr++) {
		if (addr % 16 == 0)
			printf("\n%.2x:", addr);

		dev_.addr = addr;
		res = i2c_dev_probe(&dev_, I2C_DEV_WRITE);

		if (res == 0)
			printf(" %.2x", addr);
		else
			printf(" --");
	}
	printf("\n\n");

	return res;
}

} // namespace sbn