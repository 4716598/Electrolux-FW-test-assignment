#ifndef USART_API_H
#define USART_API_H 

/* Includes */
#include "low_level_platform_defenition_header_file.h"

/* Error codes values */
enum error_code {NO_ERROR = 0, ERROR};
/* USART parity values */
enum parity_values {NONE_PARITY = 0, EVEN_PARITY, ODD_PARITY};
/* USART stopbits values */
enum stopbits {STOPBIT1 = 0, STOPBIT2}; 
/* USART mode values */
enum usart_mode {RXTX_MODE = 0, RX_ONLY_MODE, TX_ONLY_MODE};	

/* USART handle definition */
struct usart_handle {
	struct usart_instance *instance; 			/* 
								 * USART instance 
								 * struct defined in "low_level_platform_defenition_header_file.h" 
								 * possible value: UASRT1, USART2
								 */
						 
	uint32_t baudrate;					/* 
								 * This member configures the UART communication baud rate 
								 * possible value: 300 to 115200
								 */
						 
	enum parity_values parity;				/* 
								 * Member set UART parity mode 
								 * possible value: enum parity_values 
								 */
						 
	enum stopbits stopbit;					/* 
								 * Member set UART stop bit value
								 * possible value: enum stopbits
								 */
						 
	enum usart_mode mode;					/* 
								 * Member set usart work mode: Transmit and receive, receive only, transmit only
								 */
						 
	void (*callback_usart_tx)(struct usart_instance *);	/* Pointer to callback function for transmit complete */
						 
	void (*callback_usart_rx)(struct usart_instance *);	/* Pointer to callback funclion for receive complete */
};

/* Initialization function */
enum error_code usart_init(struct usart_handle *usart_h);

/* 
 * Transmit function 
 * usart_h - pointer to USART handle
 * data - pointer to transmit data block
 * data_size - data block size
 */
enum error_code usart_transmit_it(struct usart_handle *usart_h, uint8_t *data, size_t data_size);

/*
 * Receive function
 * usart_h - pointer to USART handle
 * data - pointer to place received data
 * data_size - the size of the data to be received
 */
enum error_code usart_receive_it(struct usart_handle *usart_h, uint8_t *data, size_t data_size);

#endif			/* USART_API_H */
