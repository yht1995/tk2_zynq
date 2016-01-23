/*
 * Copyright (c) 2009-2013 Xilinx, Inc.  All rights reserved.
 *
 * Xilinx, Inc.
 * XILINX IS PROVIDING THIS DESIGN, CODE, OR INFORMATION "AS IS" AS A
 * COURTESY TO YOU.  BY PROVIDING THIS DESIGN, CODE, OR INFORMATION AS
 * ONE POSSIBLE   IMPLEMENTATION OF THIS FEATURE, APPLICATION OR
 * STANDARD, XILINX IS MAKING NO REPRESENTATION THAT THIS IMPLEMENTATION
 * IS FREE FROM ANY CLAIMS OF INFRINGEMENT, AND YOU ARE RESPONSIBLE
 * FOR OBTAINING ANY RIGHTS YOU MAY REQUIRE FOR YOUR IMPLEMENTATION.
 * XILINX EXPRESSLY DISCLAIMS ANY WARRANTY WHATSOEVER WITH RESPECT TO
 * THE ADEQUACY OF THE IMPLEMENTATION, INCLUDING BUT NOT LIMITED TO
 * ANY WARRANTIES OR REPRESENTATIONS THAT THIS IMPLEMENTATION IS FREE
 * FROM CLAIMS OF INFRINGEMENT, IMPLIED WARRANTIES OF MERCHANTABILITY
 * AND FITNESS FOR A PARTICULAR PURPOSE.
 *
 */

#include <stdio.h>
#include <string.h>

#include "lwip/err.h"
#include "lwip/udp.h"

#include "cmdProcess.h"
#include "cmdline/cmdline.h"
#include "pulse.h"

#if defined (__arm__) || defined(__aarch64__)
#include "xil_printf.h"
#endif


void send_back(struct udp_pcb *pcb,ip_addr_t *addr, u16_t port, char* str)
{
	char info[100];
	int realCnt[4];

	GetRealCnt(realCnt);
	sprintf(info,"%s %d %d %d %d",str,realCnt[0],realCnt[1],realCnt[2],realCnt[3]);

	struct pbuf * p;
	p = pbuf_alloc(PBUF_TRANSPORT, strlen(str), PBUF_REF);
	p->payload = info;
	p->len = strlen(info);
	p->tot_len = p->len;
	udp_sendto(pcb, p, addr, 50000);
	pbuf_free(p);
}

void recv_callback(void *arg, struct udp_pcb *pcb, struct pbuf *p, ip_addr_t *addr, u16_t port)
{
	/* echo the payload */
	xil_printf("[receive]%s\r\n",(char*)p->payload);

	char response[2];

	if (p->len) {
		int result = CmdLineProcess((char*)p->payload);
		switch (result) {
		case 0:
			strcpy(response, "F");
			break;
		case CMDLINE_BAD_CMD:
			strcpy(response, "B");
			break;
		case CMDLINE_TOO_MANY_ARGS:
		case CMDLINE_TOO_FEW_ARGS:
		case CMDLINE_INVALID_ARG:
			strcpy(response, "E");
		}
		send_back(pcb,addr,port,response);
	}

	/* free the received pbuf */
	pbuf_free(p);
}

int start_application()
{
	struct udp_pcb *pcb;
	err_t err;
	unsigned port = 50000;

	/* create new UDP PCB structure */
	pcb = udp_new();
	if (!pcb) {
		xil_printf("Error creating UDP PCB. Out of Memory\n\r");
		return -1;
	}

	/* bind to specified @port */
	err = udp_bind(pcb, IP_ADDR_ANY, port);
	if (err != ERR_OK) {
		xil_printf("Unable to bind to port %d: err = %d\n\r", port, err);
		return -2;
	}

	/* specify callback to use for incoming connections */
	udp_recv(pcb, recv_callback,(void *)0);

	xil_printf("Server started @ port %d\n\r", port);

	return 0;
}
