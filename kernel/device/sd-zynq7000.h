/*
 * Copyright (C) 2015 David Gao <davidgao1001@gmail.com>
 *
 * This program is free software; you can redistribute	it and/or modify it
 * under	the terms of	the GNU General	Public License as published by the
 * Free Software Foundation;	either version 2 of the	License, or (at your
 * option) any later version.
 *
 */

#ifndef _DRIVERS_SD_SD_ZYNQ7000_H
#define _DRIVERS_SD_SD_ZYNQ7000_H

/*
 * ZYNQ7000 SD driver
 */

#include "config.h"
#include "type.h"
#include "io.h"
#include "gtc-a9mpcode.h"

#ifdef KERNEL
#define SD_BASE	sd0_base
#else /* KERNEL */
#define SD_BASE	SD0_PHYSBASE
#endif /* KERNEL */

void sd_init();
int sd_spin_init_mem_card();
int sd_dma_spin_read(u32 pa, u16 count, u32 offset);
int sd_dma_spin_write(u32 pa, u16 count, u32 offset);
int sd_spin_send_cmd(u16 cmd, u16 count, u32 arg, int mode);

/* Register Offset */
#define SD_SDMA_SYS_ADDR_OFFSET		0x00	/* u32 */
#define SD_BLK_SIZE_OFFSET		0x04	/* u16 */
#define SD_BLK_CNT_OFFSET		0x06	/* u16 */
#define SD_ARGMT_OFFSET			0x08	/* u32 */
#define SD_XFER_MODE_OFFSET		0x0C	/* u16 */
#define SD_CMD_OFFSET			0x0E	/* u16 */
#define SD_RESP0_OFFSET			0x10	/* u32 */
#define SD_RESP1_OFFSET			0x14	/* u32 */
#define SD_RESP2_OFFSET			0x18	/* u32 */
#define SD_RESP3_OFFSET			0x1C	/* u32 */
#define SD_BUF_DAT_PORT_OFFSET		0x20	/* u32 */
#define SD_PRES_STATE_OFFSET		0x24	/* u32 */
#define SD_HOST_CTRL1_OFFSET		0x28	/* u8 */
#define SD_POWER_CTRL_OFFSET		0x29	/* u8 */
#define SD_BLK_GAP_CTRL_OFFSET		0x2A	/* u8 */
#define SD_WAKE_UP_CTRL_OFFSET		0x2B	/* u8 */
#define SD_CLK_CTRL_OFFSET		0x2C	/* u16 */
#define SD_TIMEOUT_CTRL_OFFSET		0x2E	/* u8 */
#define SD_SW_RST_OFFSET		0x2F	/* u8 */
#define SD_NORM_INTR_STS_OFFSET		0x30	/* u16 */
#define SD_ERR_INTR_STS_OFFSET		0x32	/* u16 */
#define SD_NORM_INTR_STS_EN_OFFSET	0x34	/* u16 */
#define SD_ERR_INTR_STS_EN_OFFSET	0x36	/* u16 */
#define SD_NORM_INTR_SIG_EN_OFFSET	0x38	/* u16 */
#define SD_ERR_INTR_SIG_EN_OFFSET	0x3A	/* u16 */
#define SD_AUTO_CMD12_ERR_STS_OFFSET	0x3C	/* u16 */
#define SD_HOST_CTRL2_OFFSET		0x3E	/* u16 */
#define SD_CAPS_OFFSET			0x40	/* u32 */
#define SD_CAPS_EXT_OFFSET		0x44	/* u32 */
#define SD_MAX_CURR_CAPS_OFFSET		0x48	/* u32 */
#define SD_MAX_CURR_CAPS_EXT_OFFSET	0x4C	/* u32 */
#define SD_FE_AUTO_CMD12_EIS_OFFSET	0x50	/* u16 */
#define SD_FE_ERR_INT_STS_OFFSET	0x52	/* u16 */
#define SD_ADMA_ERR_STS_OFFSET		0x54	/* u32 */
#define SD_ADMA_SAR_OFFSET		0x58	/* u32 */
#define SD_ADMA_SAR_EXT_OFFSET		0x5C	/* u32 */
#define SD_PRE_VAL_1_OFFSET		0x60	/* u32 */
#define SD_PRE_VAL_2_OFFSET		0x64	/* u32 */
#define SD_PRE_VAL_13_OFFSET		0x68	/* u32 */
#define SD_PRE_VAL_4_OFFSET		0x6C	/* u32 */
#define SD_SHARED_BUS_CTRL_OFFSET	0xE0	/* u32 */
#define SD_SLOT_INTR_STS_OFFSET		0xFC	/* u32 */
#define SD_HOST_CTRL_VER_OFFSET		0xFE	/* u32 */

/* Block Size */
#define SD_BLK_SIZE_MASK	0x0FFF
#define SD_SDMA_BUFF_SIZE_MASK	0x7000

/* Transfer Mode */
#define SD_TM_MUL_SIN_BLK_SEL	0x20
#define SD_TM_DAT_DIR_SEL	0x10
#define SD_TM_AUTO_CMD12_EN	0x04
#define SD_TM_BLK_CNT_EN	0x02
#define SD_TM_DMA_EN		0x01

/* Present State */
#define SD_PSR_WPS_PL		0x00080000
#define SD_PSR_CARD_DPL		0x00040000
#define SD_PSR_CARD_STABLE	0x00020000
#define SD_PSR_CARD_INSRT	0x00010000
#define SD_PSR_BUFF_RD_EN	0x00000800
#define SD_PSR_BUFF_WR_EN	0x00000400
#define SD_PSR_RD_ACTIVE	0x00000200
#define SD_PSR_WR_ACTIVE	0x00000100
#define SD_PSR_DAT_ACTIVE	0x00000004
#define SD_PSR_INHIBIT_DAT	0x00000002
#define SD_PSR_INHIBIT_CMD	0x00000001

/* Host Controls */
#define SD_HC_CARD_DET_SD	0x80
#define SD_HC_CARD_DET_TL	0x40
#define SD_HC_EXT_BUS_WIDTH	0x20
#define SD_HC_DMA_MASK		0x18
#define SD_HC_DMA_ADMA2_64	0x18
#define SD_HC_DMA_ADMA2_32	0x10
#define SD_HC_DMA_ADMA1		0x08
#define SD_HC_SPEED		0x04
#define SD_HC_WIDTH		0x02
#define SD_HC_LED		0x01
#define SD_HC_DMA_SDMA		0x00

/* Power control */
#define SD_PC_BUS_VSEL_MASK	0x0E
#define SD_PC_BUS_VSEL_3V3	0x0E
#define SD_PC_BUS_VSEL_3V0	0x0C
#define SD_PC_BUS_VSEL_1V8	0x0A
#define SD_PC_BUS_PWR		0x01

/* Block Gap Control */
#define SD_BGC_BOOT_ACK		0x80
#define SD_BGC_ALT_BOOT_EN	0x40
#define SD_BGC_BOOT_EN		0x20
#define SD_BGC_SPI_MODE		0x10
#define SD_BGC_INTR		0x08
#define SD_BGC_RWC		0x04
#define SD_BGC_CNT_REQ		0x02
#define SD_BGC_STP_REQ		0x01

/* Wake Up Control */
#define SD_WC_WUP_ON_REM	0x04
#define SD_WC_WUP_ON_INSRT	0x02
#define SD_WC_WUP_ON_INTR	0x01

/* Clock Control */
#define SD_CC_SDCLK_FREQ_MASK		0xFF00
#define SD_CC_SDCLK_FREQ_D256		0x8000
#define SD_CC_SDCLK_FREQ_D128		0x4000
#define SD_CC_SDCLK_FREQ_D64		0x2000
#define SD_CC_SDCLK_FREQ_D32		0x1000
#define SD_CC_SDCLK_FREQ_D16		0x0800
#define SD_CC_SDCLK_FREQ_D8		0x0400
#define SD_CC_SDCLK_FREQ_D4		0x0200
#define SD_CC_SDCLK_FREQ_D2		0x0100
#define SD_CC_SDCLK_FREQ_BASE		0x0000
#define SD_CC_SDCLK_FREQ_EXT_MASK	0x00C0
#define SD_CC_SD_CLK_GEN_SEL		0x0020
#define SD_CC_SD_CLK_EN			0x0004
#define SD_CC_INT_CLK_STABLE		0x0002
#define SD_CC_INT_CLK_EN		0x0001
#define SD_CC_MAX_NUM_OF_DIV		9
#define SD_CC_DIV_SHIFT			8

/* Timeout Control */
#define SD_TC_CNTR_VAL_MASK	0x0000000F

/* Reset */
#define SD_SWRST_ALL_MASK	0x00000001
#define SD_SWRST_CMD_LINE_MASK	0x00000002
#define SD_SWRST_DAT_LINE_MASK	0x00000004

/* Normal Interrupt */
#define SD_NORM_INTR_ALL	0xFFFF
#define SD_INTR_ERR		0x8000
#define SD_INTR_BOOT_ACK_RECV	0x4000
#define SD_INTR_BOOT_TERM	0x2000
#define SD_INTR_RE_TUNING	0x1000
#define SD_INTR_INT_C		0x0800
#define SD_INTR_INT_B		0x0400
#define SD_INTR_INT_A		0x0200
#define SD_INTR_CARD		0x0100
#define SD_INTR_CARD_REM	0x0080
#define SD_INTR_CARD_INSRT	0x0040
#define SD_INTR_BRR		0x0020
#define SD_INTR_BWR		0x0010
#define SD_INTR_DMA		0x0008
#define SD_INTR_BGE		0x0004
#define SD_INTR_TC		0x0002
#define SD_INTR_CC		0x0001

/* Error Interrupts */
#define SD_ERR_INTR_ALL		0xF3FF
#define SD_INTR_VEND_SPF_ERR	0xE000
#define SD_INTR_ERR_TR		0x1000
#define SD_INTR_ERR_ADMA	0x0200
#define SD_INTR_ERR_AUTO_CMD12	0x0100
#define SD_INTR_ERR_I_LMT	0x0080
#define SD_INTR_ERR_DEB		0x0040
#define SD_INTR_ERR_DCRC	0x0020
#define SD_INTR_ERR_DT		0x0010
#define SD_INTR_ERR_CI		0x0008
#define SD_INTR_ERR_CEB		0x0004
#define SD_INTR_ERR_CCRC	0x0002
#define SD_INTR_ERR_CT		0x0001

/* Command and response */
#define SD_CMD_TYPE_MASK	0xC0
#define SD_CMD_TYPE_ABORT	0xC0
#define SD_CMD_TYPE_RESUME	0x80
#define SD_CMD_TYPE_SUSPEND	0x40
#define SD_DAT_PRESENT		0x20
#define SD_CMD_INX_CHK_EN	0x10
#define SD_CMD_CRC_CHK_EN	0x08
#define SD_CMD_TYPE_NORM	0x00
#define SD_CMD_RESP_MASK	0x03
#define SD_CMD_RESP_L48_BSY_CHK	0x03
#define SD_CMD_RESP_L48		0x02
#define SD_CMD_RESP_L136	0x01
#define SD_CMD_RESP_NONE	0x00

/* Command */
#define SD_CMD_MASK	0x3F00
#define SD_CMD0		0x0000
#define SD_CMD1		0x0100
#define SD_CMD2		0x0200
#define SD_CMD3		0x0300
#define SD_CMD4		0x0400
#define SD_CMD5		0x0500
#define SD_CMD6		0x0600
#define SD_CMD7		0x0700
#define SD_CMD8		0x0800
#define SD_CMD9		0x0900
#define SD_CMD10	0x0A00
#define SD_CMD12	0x0C00
#define SD_CMD16	0x1000
#define SD_CMD17	0x1100
#define SD_CMD18	0x1200
#define SD_CMD23	0x1700
#define SD_CMD24	0x1800
#define SD_CMD25	0x1900
#define SD_CMD41	0x2900
#define SD_CMD52	0x3400
#define SD_CMD55	0x3700
#define SD_CMD58	0x3A00
#define SD_ACMD6	0x8600
#define SD_ACMD13	0x8D00
#define SD_ACMD23	0x9700
#define SD_ACMD41	0xA900
#define SD_ACMD42	0xAA00
#define SD_ACMD51	0xB300

/* Response */
#define SD_RESP_NONE	SD_CMD_RESP_NONE
#define SD_RESP_R1	(SD_CMD_RESP_L48 | SD_CMD_CRC_CHK_EN | SD_CMD_INX_CHK_EN)
#define SD_RESP_R1B	(SD_CMD_RESP_L48_BSY_CHK | SD_CMD_CRC_CHK_EN | SD_CMD_INX_CHK_EN)
#define SD_RESP_R2	(SD_CMD_RESP_L136 | SD_CMD_CRC_CHK_EN)
#define SD_RESP_R3	(SD_CMD_RESP_L48)
#define SD_RESP_R6	(SD_CMD_RESP_L48_BSY_CHK | SD_CMD_CRC_CHK_EN | SD_CMD_INX_CHK_EN)

/* Capabilities */
#define SD_CAP_SPI_MODE		0x20000000
#define SD_CAP_SPI_BLOCK_MODE	0x20000000
#define SD_CAP_SYS_BUS_64	0x10000000
#define SD_CAP_INTR_MODE	0x08000000
#define SD_CAP_VOLT_1V8		0x04000000
#define SD_CAP_VOLT_3V0		0x02000000
#define SD_CAP_VOLT_3V3		0x01000000
#define SD_CAP_SUSP_RESUME	0x00800000
#define SD_CAP_SDMA		0x00400000
#define SD_CAP_HIGH_SPEED	0x00200000
#define SD_CAP_ADMA2		0x00080000
#define SD_CAP_EXT_MEDIA_BUS	0x00040000
#define SD_CAP_MAX_BLK_LEN_MASK	0x00030000
#define SD_CAP_TOUT_CLK_UNIT	0x00000080
#define SD_CAP_TOUT_CLK_FREQ	0x0000003F
#define SD_CAP_MAX_BLK_LEN_512B	0x00000000

/* ADMA2 Descripter*/
#define SD_DESC_MAX_LENGTH	65536

#define SD_DESC_VALID	0x01
#define SD_DESC_END	0x02
#define SD_DESC_INT	0x04
#define SD_DESC_TRAN	0x20

/* Misc */
#define SD_CMD8_VOL_PATTERN	0x01AA
#define SD_RESP_READY		0x80000000
#define SD_ACMD41_HCS		0x40000000
#define SD_ACMD41_3V3		0x00300000
#define SD_CMD1_HIGH_VOL	0x00FF8000
#define SD_CMD1_DUAL_VOL	0x00FF8010

/*
 * Initialize the controller.
 * This can (almost) only be done in polling mode.
 */
void sd_init()
{
	u16 	tmp16;
	u8	tmp8;
	/* reset */
	out8(SD_BASE + SD_SW_RST_OFFSET, SD_SWRST_ALL_MASK);
	while (in8(SD_BASE + SD_SW_RST_OFFSET) & SD_SWRST_ALL_MASK);

	/* capabilities = in32(SD_BASE + SD_CAPS_OFFSET) */

	/* enable internal clock */
	tmp16 = SD_CC_SDCLK_FREQ_D128 | SD_CC_INT_CLK_EN;
	out16(SD_BASE + SD_CLK_CTRL_OFFSET, tmp16);
	while (!(in16(SD_BASE + SD_CLK_CTRL_OFFSET) & SD_CC_INT_CLK_STABLE));

	/* enable SD clock */
	tmp16 = in16(SD_BASE + SD_CLK_CTRL_OFFSET) | SD_CC_SD_CLK_EN;
	out16(SD_BASE + SD_CLK_CTRL_OFFSET, tmp16);

	/* enable bus power */
	tmp8 = SD_PC_BUS_VSEL_3V3 | SD_PC_BUS_PWR;
	out8(SD_BASE + SD_POWER_CTRL_OFFSET, tmp8);
	out8(SD_BASE + SD_HOST_CTRL1_OFFSET, SD_HC_DMA_SDMA);
	/*
	 * Xilinx's driver uses ADMA2 by default, we use single-operation
	 * DMA to avoid putting descriptors in memory.
	 */

	/* enable interrupt status except card */
	tmp16 = SD_NORM_INTR_ALL & (~SD_INTR_CARD);
	out16(SD_BASE + SD_NORM_INTR_STS_EN_OFFSET, tmp16);
	out16(SD_BASE + SD_ERR_INTR_STS_EN_OFFSET, SD_ERR_INTR_ALL);

	/* but disable all interrupt signals */
	out16(SD_BASE + SD_NORM_INTR_SIG_EN_OFFSET, 0x0);
	out16(SD_BASE + SD_ERR_INTR_SIG_EN_OFFSET, 0x0);

	/* set block size to 512 */
	out16(SD_BASE + SD_BLK_SIZE_OFFSET, 512);
}

/* add descriptions to a command */
u16 sd_frame_cmd(u16 cmd)
{
	switch (cmd) {
		case SD_CMD0:
		case SD_CMD4:
			cmd |= SD_RESP_NONE; break;
		case SD_ACMD6:
		case SD_CMD7:
		case SD_CMD10:
		case SD_CMD12:
		case SD_ACMD13:
		case SD_CMD16:
		case SD_ACMD42:
		case SD_CMD52:
		case SD_CMD55:
			cmd |= SD_RESP_R1; break;
		case SD_CMD17:
		case SD_CMD18:
		case SD_CMD23:
		case SD_ACMD23:
		case SD_CMD24:
		case SD_CMD25:
		case SD_ACMD51:
			cmd |= SD_RESP_R1 | SD_DAT_PRESENT; break;
		case SD_CMD5:
			cmd |= SD_RESP_R1B; break;
		case SD_CMD2:
		case SD_CMD9:
			cmd |= SD_RESP_R2; break;
		case SD_CMD1:
		case SD_ACMD41:
			cmd |= SD_RESP_R3; break;
		case SD_CMD3:
			cmd |= SD_RESP_R6; break;
		case SD_CMD6:
			cmd |= SD_RESP_R1 | SD_DAT_PRESENT; break;
			/* for MMC card it is SD_RESP_R1B */
		case SD_CMD8:
			cmd |= SD_RESP_R1; break;
			/* for MMC card it is SD_RESP_R1 | SD_DAT_PRESENT */
	}
	return cmd & 0x3FFF;
}

/*
 * send non-data command
 * data commands are a little different, use read/write instead.
 *
 * 0 = good
 * -1 = command inhibited
 * -2 = command has data but data is inhibited
 * -3 = controller reported error
 */
int sd_spin_send_cmd(u16 cmd, u16 count, u32 arg, int mode)
{
	u32 state;
	u16 result, tmp16;
	/* frame the command */
	cmd = sd_frame_cmd(cmd);
	/* do a state check */
	state = in32(SD_BASE + SD_PRES_STATE_OFFSET);
	if (state & SD_PSR_INHIBIT_CMD) return -1;
	if ((state & SD_PSR_INHIBIT_DAT) && (cmd & SD_DAT_PRESENT)) return -2;
	/* write block count */
	out16(SD_BASE + SD_BLK_CNT_OFFSET, count);
	out16(SD_BASE + SD_TIMEOUT_CTRL_OFFSET, 0xE);
	/* write argument */
	out32(SD_BASE + SD_ARGMT_OFFSET, arg);
	out16(SD_BASE + SD_NORM_INTR_STS_OFFSET, SD_NORM_INTR_ALL);
	out16(SD_BASE + SD_ERR_INTR_STS_OFFSET, SD_ERR_INTR_ALL);
	/* set transfer mode */
	switch(mode) {
		/* DMA read */
		case 1:
			tmp16 = SD_TM_MUL_SIN_BLK_SEL | SD_TM_DAT_DIR_SEL | \
				SD_TM_AUTO_CMD12_EN | SD_TM_BLK_CNT_EN | \
				SD_TM_DMA_EN;
			break;
		/* DMA write */
		case 2:
			tmp16 = SD_TM_MUL_SIN_BLK_SEL | SD_TM_AUTO_CMD12_EN | \
				SD_TM_BLK_CNT_EN | SD_TM_DMA_EN;
			break;
		/* non-data */
		default:
			tmp16 = SD_TM_DMA_EN;
			break;
	}
	out16(SD_BASE + SD_XFER_MODE_OFFSET, tmp16);
	/* write command */
	out16(SD_BASE + SD_CMD_OFFSET, cmd);
	/* wait for result */
	do {
		result = in16(SD_BASE + SD_NORM_INTR_STS_OFFSET);
		if (result & SD_INTR_ERR) return -3;
		/* We don't read error states, and we dont't clear them. */
	} while(!(result & SD_INTR_CC));
	/* Clear */
	out16(SD_BASE + SD_NORM_INTR_STS_OFFSET, SD_INTR_CC);
	return 0;
}

/*
 * initialize a memory card
 * card inserted into SD slot can be MMC, SDIO, SD(SC/HC/XC)-(memory/combo).
 * we want a SD(SC/HC)-memory here. if we see a combo, we ignore the sdio.
 * 1 = good SDHC
 * 0 = good SD(SC)
 * -1 = no card
 * -2 = error sending CMD0
 * -3 = error sending CMD8
 * -4 = CMD8 response bad
 * -5 = error sending CMD55 & ACMD41
 * -6 = error sending CMD2
 * -7 = error sending CMD3
 * -8 = error sending CMD9
 * -9 = error sending CMD7
 */

int sd_spin_init_mem_card()
{
	u32 state, resp;
	int ret, cardtype;
	/* check card */
	state = in32(SD_BASE + SD_PRES_STATE_OFFSET);
	if (!(state & SD_PSR_CARD_INSRT)) return -1;
	/* wait 74 clocks (of sd controller). */
	usleep(2000);
	/* CMD0 */
	ret = sd_spin_send_cmd(SD_CMD0, 0, 0, 0);
	if (ret) return -2;
	/* CMD8 */
	ret = sd_spin_send_cmd(SD_CMD8, 0, SD_CMD8_VOL_PATTERN, 0);
	if (ret) return -3;
	resp = in32(SD_BASE + SD_RESP0_OFFSET);
	if (resp != SD_CMD8_VOL_PATTERN) return -4;
	/* CMD55 & ACMD41 */
	do {
		ret = sd_spin_send_cmd(SD_CMD55, 0, 0, 0);
		if (ret) return -5;
		ret = sd_spin_send_cmd(SD_ACMD41, 0, \
			(SD_ACMD41_HCS | SD_ACMD41_3V3), 0);
		if (ret) return -5;
		resp = in32(SD_BASE + SD_RESP0_OFFSET);
	} while (!(resp & SD_RESP_READY));
	/* SD or SDHC? */
	if (resp & SD_ACMD41_HCS) cardtype = 1; /* SDHC */
	else cardtype = 0; /* SD(SC) */
	/* assume S18A(OR) good and go on to CMD2 */
	ret = sd_spin_send_cmd(SD_CMD2, 0, 0, 0);
	if (ret) return -6;
	/* response0-3 contains cardID */
	/* CMD3 */
	do {
		ret = sd_spin_send_cmd(SD_CMD3, 0, 0, 0);
		if (ret) return -7;
		resp = in32(SD_BASE + SD_RESP0_OFFSET) & 0xFFFF0000;
	} while (resp == 0);
	/* response0(high 16bit) contains card RCA */
	/* CMD9 for specs, we don't use this now */
	ret = sd_spin_send_cmd(SD_CMD9, 0, resp, 0);
	if (ret) return -8;
	/* response0-3 contains cardSpecs */
	/* CMD7 */
	ret = sd_spin_send_cmd(SD_CMD7, 0, resp, 0);
	if (ret) return -9;
	return cardtype;
}

/*
 * read block from memory card
 * utilize basic DMA (known as SDMA in documents)
 * processor will spin to wait.
 *
 * pa = physical address
 * count = block count
 * offset = starting offset on card.
 *
 **********************************************
 * WARNING: OFFSET IS IN BYTES ON SD(SC) CARD *
 * BUT IN 512-BYTE BLOCKS ON SDHC CARD!       *
 **********************************************
 *
 * To make cross-platform design easier, we allow 512-byte blocks only.
 *
 * return values:
 * 0 = good
 * -1 = no card
 * -2 = error sending CMD18
 * -3 = error during DMA transfer
 */
int sd_dma_spin_read(u32 pa, u16 count, u32 offset)
{
	int ret;
	u16 state16;
	u32 state32;
	/* check card */
	state32 = in32(SD_BASE + SD_PRES_STATE_OFFSET);
	if (!(state32 & SD_PSR_CARD_INSRT)) return -1;
	/* block size set to 512 during controller init, skipping check */
	/* write address */
	out32(SD_BASE + SD_SDMA_SYS_ADDR_OFFSET, pa);
	/* CMD18 with auto_cmd12 */
	ret = sd_spin_send_cmd(SD_CMD18, count, offset, 1);
	if (ret) return -2;
	/* wait for transfer complete */
	do {
		state16 = in16(SD_BASE + SD_NORM_INTR_STS_OFFSET);
		if (state16 & SD_INTR_ERR) {
			out16(SD_BASE + SD_ERR_INTR_STS_OFFSET, \
				SD_ERR_INTR_ALL);
			return -3;
		}
	} while (!(state16 & SD_INTR_TC));
	/* clean up */
	out16(SD_BASE + SD_NORM_INTR_STS_OFFSET, SD_INTR_TC);
	return 0;
}

/*
 * write block to memory card
 * utilize basic DMA (known as SDMA in documents)
 * processor will spin to wait.
 *
 * pa = physical address
 * count = block count
 * offset = starting offset on card.
 *
 **********************************************
 * WARNING: OFFSET IS IN BYTES ON SD(SC) CARD *
 * BUT IN 512-BYTE BLOCKS ON SDHC CARD!       *
 **********************************************
 *
 * To make cross-platform design easier, we allow 512-byte blocks only.
 *
 * return values:
 * 0 = good
 * -1 = no card
 * -2 = error sending CMD25
 * -3 = error during DMA transfer
 */
int sd_dma_spin_write(u32 pa, u16 count, u32 offset)
{
	int ret;
	u16 state16;
	u32 state32;
	/* check card */
	state32 = in32(SD_BASE + SD_PRES_STATE_OFFSET);
	if (!(state32 & SD_PSR_CARD_INSRT)) return -1;
	/* block size set to 512 during controller init, skipping check */
	/* write address */
	out32(SD_BASE + SD_SDMA_SYS_ADDR_OFFSET, pa);
	/* CMD18 with auto_cmd12 */
	ret = sd_spin_send_cmd(SD_CMD25, count, offset, 2);
	if (ret) return -2;
	/* wait for transfer complete */
	do {
		state16 = in16(SD_BASE + SD_NORM_INTR_STS_OFFSET);
		if (state16 & SD_INTR_ERR) {
			out16(SD_BASE + SD_ERR_INTR_STS_OFFSET, \
				SD_ERR_INTR_ALL);
			return -3;
		}
	} while (!(state16 & SD_INTR_TC));
	/* clean up */
	out16(SD_BASE + SD_NORM_INTR_STS_OFFSET, SD_INTR_TC);
	return 0;
}

#endif /* _DRIVERS_SD_SD_ZYNQ7000_H */
