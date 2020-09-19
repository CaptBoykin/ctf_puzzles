#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>
#include<string.h>
#include<termios.h>
#include<time.h>
#include<ctype.h>

const char *AUTHOR =  "htb: captboykin | twtter: @CaptBoykin | email: capt.boykin.0602@gmail.com";

char rfc3986[256] = {0};
char html5[256] = {0};
char safebuf[512] = {0};
char safebuf_e[512] = {0};

//6162694e
// AAAaaaAAAbbbAAAcccAAAdddAAAeeeAAAfffAAAgggAAAhhhAAAiiiAAAjjjAAAkkkAAAlllAAAmmmAAAnnnAAAoooAAApppAAAqqqAAArrrAAAsssAAAtttAAAuuuAAAvvvAAAwwwAAAxxxAAAANibaZZZZ

void babyshark()
{
	__asm__ __volatile__(	"nop; nop; nop; nop;"
							"nop; nop; nop; nop;"
							"nop; nop; nop; nop;"
							"nop; nop; nop; nop;"
							"nop; nop; nop; nop;"
							"nop; nop; nop; nop;"
							"nop; nop; nop; nop;"
							"xor %eax, %eax;"
							"push  %eax;"
							"push  $0x68732f2f;"
							"push  $0x6e69622f;"
							"mov   %esp,%ebx;"
							"push   %eax;"
							"push   %ebx;"
							"mov    %esp,%ecx;"
							"mov    $0xb,%al;"
							"int    $0x80;"
	);
}

void mommyshark()
{
	babyshark();

}

void url_encoder_rfc_tables_init(){

    int i;

    for (i = 0; i < 256; i++){

        rfc3986[i] = isalnum( i) || i == '~' || i == '-' || i == '.' || i == '_' ? i : 0;
        html5[i] = isalnum( i) || i == '*' || i == '-' || i == '.' || i == '_' ? i : (i == ' ') ? '+' : 0;
    }
}


char *url_encode( char *table, unsigned char *s, char *enc){

    for (; *s; s++){

        if (table[*s]) sprintf( enc, "%c", table[*s]);
        else sprintf( enc, "%%%02X", *s);
        while (*++enc);
    }

    return( enc);
}

int main(int argc, char *argv[])
{

	setreuid(geteuid(), geteuid());

	static struct termios oldt, newt;
	char vulnbuf[128] = {0};

	url_encoder_rfc_tables_init();

    tcgetattr( STDIN_FILENO, &oldt);
    newt = oldt;

    newt.c_lflag &= ~(ICANON);          
	newt.c_lflag &= ~ECHO;

    tcsetattr( STDIN_FILENO, TCSANOW, &newt);

	printf("SWIM A LAP! Alternate tapping between q and p to padddle\n");
	int dist = 0;
	char p = 'p';
	char q = 'q';
	char ch;
	clock_t t;

	printf("[PRESS ENTER TO CONTINUE]\n");
	ch=getchar();
	if(ch == '\n')
	{
		printf(">> Ready <<\n");
		sleep(1);
		printf(">> Set <<\n");
		sleep(1);
		printf(">> GO! <<\n");
		printf("Alternate q and p to paddle\n");
		printf("---------------------------\n");
		
		t = clock();
		while(dist < 20)
		{
			ch=getchar();
			if(ch == q)
			{
				ch=getchar();
				if(ch == p)
				{
					printf("DISTANCE [%d]\r",dist);
					dist++;
					continue;
				}
				else
				{
					continue;
				}
			}
			else
			{
				continue;
			}
		}
		t = clock() - t;	
	}
	else
	{
		tcsetattr( STDIN_FILENO, TCSANOW, &oldt);
		printf(" You slipped off the board...try again\n");
		return(1);
	}
	
	tcsetattr( STDIN_FILENO, TCSANOW, &oldt);
	printf("Your time was %2f\n",(((double)t)/CLOCKS_PER_SEC)*10000);
	printf("Hall of Fame! Enter name(First Last):");

	fgets(safebuf,511,stdin);
	
	url_encode(html5,safebuf,safebuf_e);

	memcpy(vulnbuf,safebuf_e,512);

	printf("Conglaturation %s !!\n\n",safebuf_e);

	while(0)
	{
		mommyshark();
	}

	return(0);
}
