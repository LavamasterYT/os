#ifndef TTY_H
#define TTY_H

#define TTY_BUFFER_LEN (80 * 25)

void tty_put(char c);
void tty_write(const char* str);

#endif