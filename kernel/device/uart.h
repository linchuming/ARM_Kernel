/*
 * Copyright (C) 2015 Gan Quan <coin2028@hotmail.com>
 *
 * This program is free software; you can redistribute  it and/or modify it
 * under  the terms of  the GNU General  Public License as published by the
 * Free Software Foundation;  either version 2 of the  License, or (at your
 * option) any later version.
 *
 */

#ifndef _DRIVERS_SERIAL_UART_H
#define _DRIVERS_SERIAL_UART_H

#include "config.h"
#include "type.h"
#include "uart-zynq7000.h"


void uart_spin_puts(const char *str);

void uart_spin_puts(const char *str)
{
	spin_lock(&puts_lock);
	for (; *str != '\0'; ++str)
		uart_spin_putbyte((unsigned char)*str);
	release_lock(&puts_lock);
}

#endif
