#include <avr/io.h>
#include <stdio.h>

#define F_CPU 16000000UL  /* 16 MHz */
#define BAUD 9600
#include <util/setbaud.h>

void uart_init(void) {
  UBRR0H = UBRRH_VALUE;
  UBRR0L = UBRRL_VALUE;

#if USE_2X
  UCSR0A |= _BV(U2X0);
#else
  UCSR0A &= ~(_BV(U2X0));
#endif

  UCSR0C = _BV(UCSZ01) | _BV(UCSZ00);
  UCSR0B = _BV(RXEN0) | _BV(TXEN0);
}

void uart_putchar(char c, FILE *stream) {
  if (c == '\n')
    uart_putchar('\r', stream);

  loop_until_bit_is_set(UCSR0A, UDRE0);
  UDR0 = c;
}

char uart_getchar(FILE *stream) {
  (void) stream;  /* suppress GCC warning */
  loop_until_bit_is_set(UCSR0A, RXC0);
  return UDR0;
}

/* important: do we believe that successive voltage
   readings are independent? if not, the von Neumann extractor
   will not work
   we can try xor'ing two bitstreams, or use a voltage difference
   instead? we could also just SHA256 the bitstream or something */
/*
char poll_random_bit(int pin) {
  char b1 = analogRead(pin);
  char b2 = analogRead(pin);
  do {
    if (b1 > b2) {
      return 0;
    } else if (b1 < b2) {
      return 1;
    }
  } while (b1 != b2);
}*/

/*
void loop() {
  char rand_byte = 0;
  for (int i = 0; i < 8; i++) {
    int rand_bit = poll_random_bit(A0);
    rand_byte += (rand_bit << i);
  }
  Serial.write(rand_byte;
  delay(500);
}
*/

int main() {
  FILE uart_output = FDEV_SETUP_STREAM(uart_putchar, NULL, _FDEV_SETUP_WRITE);
  FILE uart_input  = FDEV_SETUP_STREAM(NULL, uart_getchar, _FDEV_SETUP_READ);
  uart_init();
  stdout = &uart_output;
  stdin  = &uart_input;

  printf("%c\n", 'a');
  return 0;
}

