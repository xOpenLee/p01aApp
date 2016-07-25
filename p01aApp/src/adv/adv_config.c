/*
 * adv_config.c

 *
 *  Created on: 2016��7��17��
 *      Author: xopenlee
 */



#include <stdio.h>

void print(char *str);
#define printf xil_printf
#define ADV9518_BASE_ADDR (0x61000000)
#define ADV9518_SPI_RW_OFFSET (0x118)
#define ADV9518_SPI_RW_TRIG (0x120)
#define ADV9518_SPI_W_TRIG_VAL (0x1)
#define ADV9518_SPI_R_TRIG_VAL (0x2)
#define ADV9518_SPI_READ_VAL_OFFSET (0x14)

#define ADV9520_BASE_ADDR (0x61000000)
#define ADV9520_SPI_RW_OFFSET (0x11C)
#define ADV9520_SPI_RW_TRIG (0x120)
#define ADV9520_SPI_W_TRIG_VAL (0x10)
#define ADV9520_SPI_R_TRIG_VAL (0x20)
#define ADV9520_SPI_READ_VAL_OFFSET (0x18)

#define ADV9520_TMP_BASE_ADDR (0x61000000)
#define ADV9520_TMP_SPI_RW_OFFSET (0x124)
#define ADV9520_TMP_SPI_RW_TRIG   (0x120)
#define ADV9520_TMP_SPI_W_TRIG_VAL (0x100)
#define ADV9520_TMP_SPI_R_TRIG_VAL (0x200)
#define ADV9520_TMP_SPI_READ_VAL_OFFSET (0x1c)

void delay_us(unsigned int us_number)
{
	unsigned int i;
	unsigned int j;
	for(i=0;i<us_number;i++)
	{
		for(j=0;j<120;j++);
	}
}

static int spi_write(unsigned int base, unsigned int val)
{
	unsigned int check = 0;
	Xil_Out32(base, val);
	check = Xil_In32(base);
	if(check != val) {
		printf("#ERR: spi write base = 0x%x val = 0x%x failed. \r\r\n", base, val);
		return -1;
	}

	return 0;
}

static int spi_read(unsigned int base)
{
	return Xil_In32(base);
}

static int adv_write(unsigned int base, unsigned int rw_offset, unsigned int rw_trig,
		unsigned int rw_trig_val, unsigned int offset, unsigned int val)
{
	int ret = 0;
	unsigned int reg_val = 0;
	reg_val = ((offset << 16) & 0xFFFF0000) | ((val << 8) & 0xFF00);
	ret = spi_write(base + rw_offset, reg_val);
	if (ret < 0) {
		printf("#ERR: adv9520_write offset = 0x%x, val = 0x%x failed\r\n", offset, val);
		return 0;
	}
	spi_write(ADV9520_BASE_ADDR + rw_trig, rw_trig_val);
	return 0;
}

static int adv_read(unsigned int base, unsigned int rw_offset, unsigned int rw_trig,
		unsigned int rw_trig_val, unsigned int offset, unsigned int read_val_offset)
{
	int ret = 0;
	unsigned int reg_val = 0;
	reg_val = ((offset << 16) & 0xFFFF0000) | 0x80000000;
	ret = spi_write(base + rw_offset, reg_val);
	if (ret < 0) {
		printf("#ERR: adv9520_write offset = 0x%x failed\r\n", offset);
		return -1;
	}

	spi_write(base + rw_trig, rw_trig_val);

	return spi_read(base + read_val_offset);
}

static int adv9520_write(unsigned int offset, unsigned int val)
{
	int ret = 0;
	ret = adv_write(ADV9520_BASE_ADDR, ADV9520_SPI_RW_OFFSET, ADV9520_SPI_RW_TRIG,
			ADV9520_SPI_W_TRIG_VAL, offset, val);
	if (ret < 0) {
		printf("#ERR: adv9520_write offset = 0x%x, val = 0x%x failed\r\n", offset, val);
		return 0;
	}
	return 0;
}

static int adv9520_read(unsigned int offset)
{
	int ret = 0;
	ret = adv_read(ADV9520_BASE_ADDR, ADV9520_SPI_RW_OFFSET,ADV9520_SPI_RW_TRIG,
			ADV9520_SPI_R_TRIG_VAL, offset, ADV9520_SPI_READ_VAL_OFFSET);
	if (ret < 0) {
		printf("#ERR: adv9520_write offset = 0x%x failed\r\n", offset);
		return -1;
	}
	return 0;
}

static int adv9520_tmp_write(unsigned int offset, unsigned int val)
{
	int ret = 0;
	ret = adv_write(ADV9520_TMP_BASE_ADDR, ADV9520_TMP_SPI_RW_OFFSET, ADV9520_TMP_SPI_RW_TRIG,
			ADV9520_TMP_SPI_W_TRIG_VAL, offset, val);
	if (ret < 0) {
		printf("#ERR: adv9520_tmp_write offset = 0x%x, val = 0x%x failed\r\n", offset, val);
		return 0;
	}
	return 0;
}

static int adv9520_tmp_read(unsigned int offset)
{
	int ret = 0;
	ret = adv_read(ADV9520_TMP_BASE_ADDR, ADV9520_TMP_SPI_RW_OFFSET,ADV9520_TMP_SPI_RW_TRIG,
			ADV9520_TMP_SPI_R_TRIG_VAL, offset, ADV9520_TMP_SPI_READ_VAL_OFFSET);
	if (ret < 0) {
		printf("#ERR: adv9520_tmp_read offset = 0x%x failed\r\n", offset);
		return -1;
	}
	return 0;
}

static int adv9518_write(unsigned int offset, unsigned int val)
{
	int ret = 0;
	ret = adv_write(ADV9518_BASE_ADDR, ADV9518_SPI_RW_OFFSET, ADV9518_SPI_RW_TRIG,
					ADV9518_SPI_W_TRIG_VAL, offset, val);
	if (ret < 0) {
		printf("#ERR: adv9518_write offset = 0x%x, val = 0x%x failed\r\n", offset, val);
		return 0;
	}
	return 0;
}

static int adv9518_read(unsigned int offset)
{
	int ret = 0;
	ret = adv_read(ADV9518_BASE_ADDR, ADV9518_SPI_RW_OFFSET, ADV9518_SPI_RW_TRIG,
			ADV9518_SPI_R_TRIG_VAL, offset, ADV9518_SPI_READ_VAL_OFFSET);
	if (ret < 0) {
		printf("#ERR: adv9518_read offset = 0x%x failed\r\n", offset);
		return -1;
	}
	return 0;
}

static int adv9520_write_check(unsigned int offset, unsigned int val)
{
	int ret = 0, read_back;
	ret = adv9520_write(offset, val);
	if (ret < 0) {
		printf("#ERR: adv9520_write_check offset = 0x%x failed\r\n", offset);
		return -1;
	}
	delay_us(1);
	read_back = adv9520_read(offset);
	if(val != read_back)  {
		printf("#ERR: adv9520_write_check val = 0x%x , read_back = 0x%x failed\r\n", val, read_back);
		return -1;
	}

	return 0;
}

static int adv9518_write_check(unsigned int offset, unsigned int val)
{
	int ret = 0, read_back;
	ret = adv9518_write(offset, val);
	if (ret < 0) {
		printf("#ERR: adv9518_write offset = 0x%x failed\r\n", offset);
		return -1;
	}
	delay_us(1);
	read_back = adv9518_read(offset);
	if(val != read_back)  {
		printf("#ERR: adv9518_read val = 0x%x , read_back = 0x%x failed\r\n", val, read_back);
		return -1;
	}

	return 0;
}

struct adv_t {
	unsigned int addr;
	unsigned int val;
};


void ad9518_config(void)
{
	int i = 0, lock = 0;
	struct adv_t ad9518_config[] =
	{
			{0x10, 0x7c},
			{0x11, 0x01},
			{0x12, 0x00},
			{0x13, 0x04},
			{0x14, 0x07},
			{0x15, 0x00},
			{0x16, 0x04},
			{0x1c, 0x02},
			{0x18, 0x04},
			{0x232, 0x01},
			{0x1e0, 0x00},
			{0x1e1, 0x02},
			{0x18, 0x05},
			{0x190, 0x22},
			{0x193, 0x22},
			{0x196, 0x22},
			{0xf0, 0x08},
			{0xf1, 0x08},
			{0xf2, 0x08},
			{0xf3, 0x08},
			{0xf4, 0x08},
			{0x191, 0x00},
			{0x194, 0x00},
			{0x197, 0x00},
			{0x232, 0x01},
	};

	for(i = 0; i < sizeof(ad9518_config)/sizeof(struct adv_t); i++) {
		adv9518_write(ad9518_config[i].addr, ad9518_config[i].val);
		delay_us(1);
	}
	lock = adv9518_read(0x1f);
}

void ad9520_config(void)
{
	int i = 0, lock = 0;
	struct adv_t ad9520_config[] =
	{
			{0x10, 0x7c},
			{0x11, 0x01},
			{0x12, 0x00},
			{0x13, 0x04},
			{0x14, 0x07},
			{0x15, 0x00},
			{0x16, 0x04},
			{0x1e1, 0x02},
			{0x1c, 0x02},
			{0x1e0, 0x00},
			{0x18, 0x84},
			{0x232, 0x01},
			{0x190, 0x22},
			{0x193, 0x22},
			{0x196, 0x22},
			{0x199, 0x22},
			{0xf0, 0xFC},
			{0xf1, 0xFC},
			{0xf2, 0xFC},
			{0xf3, 0xFC},
			{0xf5, 0xFC},
			{0xf6, 0xFC},
			{0xf7, 0xFC},
			{0xf8, 0xFC},
			{0xf9, 0xFC},
			{0xfa, 0xFC},
			{0xfb, 0xFC},
			{0x18, 0x85},
			{0x232, 0x01},
	};

	for(i = 0; i < sizeof(ad9520_config)/sizeof(struct adv_t); i++) {
		adv9520_write(ad9520_config[i].addr, ad9520_config[i].val);
		delay_us(1);
	}
	lock = adv9520_read(0x1f);

	for(i = 0; i < sizeof(ad9520_config)/sizeof(struct adv_t); i++) {
		adv9520_tmp_write(ad9520_config[i].addr, ad9520_config[i].val);
		delay_us(1);
	}
	lock = adv9520_tmp_read(0x1f);

}
