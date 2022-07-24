#include <memory>
#include <optional>
#include <vector>

#include "driver/i2c.h"
#include "i2cdev.h"

const int DEFAULT_I2C_SPEED = 250000;
const int DEFAULT_SSD1306_ADDR = 0x3c;
namespace sbn
{

class i2c_port {
    public:
	i2c_port(int port, int sda, int sdc, bool sda_pullup, bool scl_pullup,
		 int clk_speed = DEFAULT_I2C_SPEED) noexcept
	{
		if (port_count_ == 0) {
			i2cdev_init();
		}
		port_count_
		dev_ = i2c_dev_t{};
		dev_.port = port;
		dev_.cfg.mode = I2C_MODE_MASTER;
		dev_.cfg.sda_io_num = sda;
		dev_.cfg.sda_pullup_en = sda_pullup;
		dev_.cfg.scl_io_num = sdc;
		dev_.cfg.scl_pullup_en = scl_pullup;
		dev_.cfg.master.clk_speed = clk_speed;
	};

	~i2c_port()
	{
		port_count_--;
		if (port_count_ == 0) {
			i2cdev_done();
		}
	}
	esp_err_t scan();
	void addr(int addr);

    private:
	i2c_dev_t dev_;
	static inline int port_count_ = 0;
};

class ssd1306 {
    private:
	// own the underlying dev struct, so ideally nothing else can
	// modify the values
	std::unique_ptr<i2c_port> port_;

    public:
	ssd1306(std::unique_ptr<i2c_port> p, int addr = DEFAULT_SSD1306_ADDR)
		: port_{ std::move(p) }
	{
		port_->addr(addr);
	};
	esp_err_t scan();
};

} // namespace sbn