#ifndef _READKEYS_H_
#define _READKEYS_H_

#include <iostream>
#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <termios.h>

enum keys {KEY_q, KEY_l,KEY_s,KEY_r,KEY_t,KEY_i,KEY_f5,KEY_f6,KEY_up,KEY_down,KEY_left,KEY_right,KEY_enter, KEY_esc, KEY_nothing};

static struct termios termsave;
static struct termios mode;

int rk_readkey(enum keys *key);
int rc_mytermsave();
int rk_mytermrestore();
int rk_mytermregime(int regime, int vtime, int vmin, int echo, int sigint);
int print_key(enum keys key);

#endif
