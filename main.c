#include "main.h"
#include <stdint.h>
#include <string.h>
#include "usart_api.h"

#define DATA_BLOCK_SIZE		128

struct usart_handle huart1;
struct usart_handle huart2;
uint8_t usart_rx_buffer[DATA_BLOCK_SIZE];
uint8_t usart_tx_buffer[DATA_BLOCK_SIZE];

void error_handler(struct usart_handle *usarthandle, enum error_code errcode);

void usart1_init(void)
{
	enum error_code retval = NO_ERROR;
	huart1.instance = USART1;
	huart1.baudrate = 9600;
	huart1.parity = NONE_PARITY;
	huart1.stopbit = STOPBIT1;
	huart1.usart_mode = RX_ONLY_MODE;
	huart1.callback_usart_rx = usart_rx_callback;
	retval = usart_init(&huart1);
	if(retval != NO_ERROR) {
		error_handler(&huart1, retval);
	}
}

void usart2_init(void)
{
	enum error_code retval = NO_ERROR;
	huart2.instance = USART2;
	huart2.baudrate = 115200;
	huart2.parity = NONE_PARITY;
	huart2.stopbit = STOPBIT1;
	huart2.usart_mode = TX_ONLY_MODE;
	huart2.callback_usart_tx = usart_tx_callback;
	retval = usart_init(&huart2);
	if(retval != NO_ERROR) {
		error_handler(&huart2, retval);
	}
}

int main(void)
{
	enum error_code errno = NO_ERROR;
	usart1_init();
	usart2_init();
	errno = usart_receive_it(&huart1, usart_rx_buffer, DATA_BLOCK_SIZE);
	if (errno != NO_ERROR) {
		error_handler(&huart1, errno);
	}
	for(;;) {
		
	}
}

void usart_tx_callback(struct usart_instance *usart_inst)
{
	if (usart_inst == USART2) {
		
	}
}

void usart_rx_callback(struct usart_instance *usart_inst)
{
	enum error_code errno = NO_ERROR;
	if (usart_inst == USART1) {
		memcpy(usart_rx_buffer, usart_tx_buffer, DATA_BLOCK_SIZE);
		errno = usart_receive_it(&huart1, usart_rx_buffer, DATA_BLOCK_SIZE);
		if (errno != NO_ERROR) {
			error_handler(&huart1, errno);
		}
		errno = usart_transmit_it(&huart2, usart_tx_buffer, DATA_BLOCK_SIZE);
		if (errno != NO_ERROR) {
			error_handler(&huart2, errno);
		}
	}
}

void error_handler(struct usart_handle *usarthandle, enum error_code errcode)
{
	debug(usarthandle);
	debug(errcode);
	for(;;) {
		__NOP();
	}
}
