#include "myReadKeys.h"

int rk_readkey(enum keys *key)
{
	termios orig_conf;
	char buff[16] = "\0";
	int result;
	tcgetattr(1,&orig_conf);
	rk_mytermregime(0, 0, 1, 0, 1);
	result = read(1,buff,15);
	tcsetattr(1,TCSANOW,&orig_conf);
	if(!result){
		*key = KEY_nothing;
		return 0;
	}
  if (!strncmp(buff, "q",1)){
    *key = KEY_q;
		return 0;
	}
	if (!strncmp(buff,"l",1)){
		*key=KEY_l;
		return 0;
	}
	if (!strncmp(buff,"s",1)){
		*key=KEY_s;
		return 0;
	}
	if (!strncmp(buff,"r",1)){
		*key=KEY_r;
		return 0;
	}
	if (!strncmp(buff,"t",1)){
		*key=KEY_t;
		return 0;
	}
	if (!strncmp(buff,"i",1)){
		*key=KEY_i;
		return 0;
	}
	if (!strncmp(buff,"\E[15~",5)){
		*key=KEY_f5;
		return 0;
	}
	if (!strncmp(buff,"\E[17~",5)){
		*key=KEY_f6;
		return 0;
	}
	if (!strncmp(buff,"\E[A",3)){
		*key=KEY_up;
		return 0;
	}
	if (!strncmp(buff,"\E[B",3)){
		*key=KEY_down;
		return 0;
	}
	if (!strncmp(buff,"\E[D",3)){
		*key=KEY_left;
		return 0;
	}
	if (!strncmp(buff,"\E[C",3)){
		*key=KEY_right;
		return 0;
	}
	if (!strncmp(buff,"\n",1)){
		*key=KEY_enter;
		return 0;
	}
	if (!strncmp(buff,"\E",1)){
		*key=KEY_esc;
		return 0;
	}
		*key = KEY_nothing;
	return 0;
}

int rc_mytermsave(){
  tcgetattr(1, &termsave);
  return 0;
}

int rk_mytermrestore(){
  tcsetattr(1,TCSAFLUSH,&termsave);
  return 0;
}

int rk_mytermregime(int regime, int vtime, int vmin, int echo, int sigint)
{
	if (tcgetattr(1,&mode)!=0)
		return -1;

	if (regime==1) {		// канонический режим
		mode.c_lflag|=ICANON;
		mode.c_cc[VTIME]=0;
		mode.c_cc[VMIN]=1;
		mode.c_lflag|=ECHO;
		mode.c_lflag|=ISIG;
		return -1;
	}
	if (regime==0) //  если выбрали не канонический режим
	{
		mode.c_lflag&=~ICANON;
		mode.c_cc[VTIME]=vtime; // через сколько символом надо отправлять в read()
		mode.c_cc[VMIN]=vmin; // минимальное кол-во символов (1)

		if (echo==1) // отображать то что вводим в терминал
			mode.c_lflag|=ECHO;
		else if (echo==0)
			mode.c_lflag&=~ECHO;
		else
			return -1;
		if (sigint==1) // разрешить обработку прерываний в терминале (Ctrl+c Ctrl+v)
			mode.c_lflag|=ISIG;
		else if (sigint==0)
			mode.c_lflag&=~ISIG;
		else
			return -1;
	}

	if (tcsetattr(1, TCSANOW, &mode)!=0) // устанавливаем новые настройки терминала
		return -1;

	return 0;
}

int print_key(enum keys key)
{
	switch (key) {
	case KEY_q:
		printf("%5s","q");
		break;
	case KEY_l:
		printf("%5s","l");
		break;
	case KEY_s:
		printf("%5s","s");
		break;
	case KEY_r:
		printf("%5s","r");
		break;
	case KEY_t:
		printf("%5s","t");
		break;
	case KEY_i:
		printf("%5s","i");
		break;
	case KEY_f5:
		printf("%5s","F5");
		break;
	case KEY_f6:
		printf("%5s","F6");
		break;
	case KEY_up:
		printf("%5s","up");
		break;
	case KEY_down:
		printf("%5s","down");
		break;
	case KEY_left:
		printf("%5s","left");
		break;
	case KEY_right:
		printf("%5s","right");
		break;
	case KEY_enter:
		printf("%5s","enter");
		break;
	case KEY_esc:
		printf("%5s","esc");
		break;
	}
  return 0;
}
