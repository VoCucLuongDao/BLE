/*
 * Copyright (c) 2012-2014 Wind River Systems, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <stdio.h>
#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>

int main(void)
{
	while(1) {
		printk("Hello World!\n");
		k_sleep(K_SECONDS(5));
	}
	return 0;
}
