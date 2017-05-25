#include <iostream.h>
#include <conio.h>
#include <dos.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

int far * scr = (int far *)0xb8000000;
int eog=0;

void init();
char Getkey(int &c);
void docommand(char c,int i);
void flow();
int canfall();
void rotate();
void settet();
int canleft();
void doleft();
int canright();
void doright();
int checkl(int x);
void dol(int x);
void lose();
int maxX(int a1,int a2,int a3,int a4);
enum color{
black	= 0x01,
blue 	= 0x02,
green	= 0x03,
cyan	= 0x04,
red  	= 0x05,
pink    = 0x06,
orange	= 0x07,
white	= 0x08

}co=blue;

int tet[4][2];
int tetnext[4][2];
int dt=150;
int block_char='Û';//block character
int score=0;
int far * start=(int far *)0x0480;
int far * end = (int far *)0x0482;
int level=1;



int main()
{
init();
while(!eog){
	if( kbhit() ){
	int i;
	char c=Getkey(i);
	docommand(c,i);
	}
	flow();
}
if(eog==-1)lose();
return 0;
}

void settet(){
if(co==orange)
co=black;
co=co+0x01;
for(int i=0;i<4;i++){
	tet[i][0]=tetnext[i][0];
	tet[i][1]=tetnext[i][1];
}
for(i=0;i<4;i++)
	*(scr+tetnext[i][0]*80+tetnext[i][1]+50)=32;
srand(time(NULL));
int R=(rand() % ( level + 1 ) );
//R=0;
switch(R){
	case 0:
	tetnext[0][0]=1;
	tetnext[0][1]=40;
	tetnext[1][0]=1;
	tetnext[1][1]=39;
	tetnext[2][0]=2;
	tetnext[2][1]=40;
	tetnext[3][0]=2;
	tetnext[3][1]=39;
	break;
	case 1:
	tetnext[0][0]=2;
	tetnext[0][1]=40;
	tetnext[1][0]=2;
	tetnext[1][1]=39;
	tetnext[2][0]=2;
	tetnext[2][1]=41;
	tetnext[3][0]=2;
	tetnext[3][1]=42;
	break;
	case 2:
	tetnext[0][0]=2;
	tetnext[0][1]=40;
	tetnext[1][0]=2;
	tetnext[1][1]=39;
	tetnext[2][0]=1;
	tetnext[2][1]=40;
	tetnext[3][0]=1;
	tetnext[3][1]=41;
	break;
	case 3:
	tetnext[0][0]=2;
	tetnext[0][1]=40;
	tetnext[1][0]=2;
	tetnext[1][1]=39;
	tetnext[2][0]=1;
	tetnext[2][1]=39;
	tetnext[3][0]=1;
	tetnext[3][1]=38;
	break;
	case 4:
	tetnext[0][0]=2;
	tetnext[0][1]=40;
	tetnext[1][0]=1;
	tetnext[1][1]=40;
	tetnext[2][0]=1;
	tetnext[2][1]=39;
	tetnext[3][0]=1;
	tetnext[3][1]=41;
	break;
	case 5:
	tetnext[0][0]=2;
	tetnext[0][1]=40;
	tetnext[1][0]=1;
	tetnext[1][1]=40;
	tetnext[2][0]=0;
	tetnext[2][1]=40;
	tetnext[3][0]=0;
	tetnext[3][1]=39;
	break;
	case 6:
	tetnext[0][0]=2;
	tetnext[0][1]=40;
	tetnext[1][0]=1;
	tetnext[1][1]=40;
	tetnext[2][0]=0;
	tetnext[2][1]=40;
	tetnext[3][0]=0;
	tetnext[3][1]=41;
	break;


}
if(co!=orange)
for(i=0;i<4;i++)
*(scr+tetnext[i][0]*80+tetnext[i][1]+50)=(co+0x01)*256+block_char;
else
for(i=0;i<4;i++)
*(scr+tetnext[i][0]*80+tetnext[i][1]+50)=(blue)*256+block_char;
}

void init(){
clrscr();

tetnext[0][0]=2;
tetnext[0][1]=40;
tetnext[1][0]=2;
tetnext[1][1]=39;
tetnext[2][0]=1;
tetnext[2][1]=40;
tetnext[3][0]=1;
tetnext[3][1]=39;

for(int k=0;k<2000;k++) *(scr+k)=32;
for(int i=34;i<46;i++)	*(scr+21*80+i)=0x02*256+5;
for(    i=21;i>0 ;i--)  *(scr+i*80+34)=0x02*256+5;
for(    i=21;i>0 ;i--)  *(scr+i*80+45)=0x02*256+5;


tet[0][0]=2;
tet[0][1]=40;
tet[1][0]=2;
tet[1][1]=39;
tet[2][0]=1;
tet[2][1]=40;
tet[3][0]=1;
tet[3][1]=39;
settet();
for(i=0;i<4;i++)	*(scr+80*tet[i][0]+tet[i][1])=co*256+block_char;

*(scr+22*80+35)=0x0B*256+'s';
*(scr+22*80+36)=0x0B*256+'c';
*(scr+22*80+37)=0x0B*256+'o';
*(scr+22*80+38)=0x0B*256+'r';
*(scr+22*80+39)=0x0B*256+'e';
*(scr+22*80+40)=0x0B*256+':';
*(scr+22*80+41)=0x0B*256+'0';
*(scr+22*80+42)=0x0B*256+'0';
*(scr+22*80+43)=0x0B*256+'0';

*(scr+23*80+36)=0x0B*256+'l';
*(scr+23*80+37)=0x0B*256+'e';
*(scr+23*80+38)=0x0B*256+'v';
*(scr+23*80+39)=0x0B*256+'e';
*(scr+23*80+40)=0x0B*256+'l';
*(scr+23*80+41)=0x0B*256+':';
*(scr+23*80+42)=0x0B*256+'1';

*(scr+24*80+28)=0x0B*256+'f';
*(scr+24*80+29)=0x0B*256+'o';
*(scr+24*80+30)=0x0B*256+'r';
*(scr+24*80+32)=0x0B*256+'e';
*(scr+24*80+33)=0x0B*256+'a';
*(scr+24*80+34)=0x0B*256+'c';
*(scr+24*80+35)=0x0B*256+'h';
*(scr+24*80+37)=0x0B*256+'4';
*(scr+24*80+38)=0x0B*256+'0';
*(scr+24*80+40)=0x0B*256+'s';
*(scr+24*80+41)=0x0B*256+'c';
*(scr+24*80+42)=0x0B*256+'o';
*(scr+24*80+43)=0x0B*256+'r';
*(scr+24*80+44)=0x0B*256+'e';
*(scr+24*80+46)=0x0B*256+'g';
*(scr+24*80+47)=0x0B*256+'o';
*(scr+24*80+49)=0x0B*256+'n';
*(scr+24*80+50)=0x0B*256+'e';
*(scr+24*80+51)=0x0B*256+'x';
*(scr+24*80+52)=0x0B*256+'t';
*(scr+24*80+53)=0x0B*256+'l';
*(scr+24*80+55)=0x0B*256+'e';
*(scr+24*80+56)=0x0B*256+'v';
*(scr+24*80+57)=0x0B*256+'e';
*(scr+24*80+58)=0x0B*256+'l';


*(scr+0*80+37)=0x0C*256+'S';
*(scr+0*80+38)=0x0C*256+'A';
*(scr+0*80+39)=0x0C*256+'M';
*(scr+0*80+40)=0x0C*256+'I';
*(scr+0*80+41)=0x0C*256+'E';
*(scr+0*80+42)=0x0C*256+'I';
}

char Getkey(int& c)
{
char I=getch();
if(I==0)
	{
	I=getch();
	c=1;
	}
else
	c=0;
return I;
}

void docommand(char c ,int i){
if(i==0 && c==27)eog=1;
if(i){
	switch(c){
	case 'H':
		rotate();
		break;
	case 'P':
		dt=20;
		break;
	case 'M':
		if(canright())doright();
		break;
	case 'K':
		if(canleft())doleft();
		break;
	}
	int far * a = (int far *)0x000041a;
	int far * b = (int far *)0x000041c;
	*(a)=*(b);
}
else{switch(c){
     case 'p':
	getch();
	break;
     case ' ':
	dt=0;
	break;

}}
}

void flow(){
if( canfall()){
	for(int i=0;i<4;i++)*(scr+80*tet[i][0]+tet[i][1])=32;
		for(    i=0;i<4;i++){
			tet[i][0]++;
			*(scr+80*tet[i][0]+tet[i][1])=co*256+block_char;
	}
}
else {
	for(int i=0;i<4;i++)
		if(checkl(tet[i][0]))
			dol(tet[i][0]);
	for( i=0;i<4;i++)
		if(checkl(tet[i][0]))
			dol(tet[i][0]);
	dt=150;
	if(score/40 >= level ){
		level++;
		*(scr+23*80+42)=0x0B*256+'0'+level;
	}
	if(maxX(tet[0][0],tet[1][0],tet[2][0],tet[3][0])<3)eog=-1;
	settet();

}
delay(dt);
if(dt<150 && dt!=0)
dt+=20;
if(dt>150)
dt=150;
}

int canfall(){
for(int i=0;i<4;i++)
	if(*(scr+80*tet[i][0]+tet[i][1]+80)!=32 )
		if(tet[i][0]+1 != tet[0][0] || tet[i][1] != tet[0][1] )
			if(tet[i][0]+1 != tet[1][0] || tet[i][1] != tet[1][1] )
				if(tet[i][0]+1 != tet[2][0] || tet[i][1] != tet[2][1] )
					if(tet[i][0]+1 != tet[3][0] || tet[i][1] != tet[3][1] )return 0;
return 1;
}

int canleft(){
for(int i=0;i<4;i++)
	if(*(scr+80*tet[i][0]+tet[i][1]-1)!=32 )
		if(tet[i][1]-1 != tet[0][1] )
			if(tet[i][1]-1 != tet[1][1] )
				if(tet[i][1]-1 != tet[2][1] )
					if(tet[i][1]-1 != tet[3][1] )return 0;
return 1;
}

void doleft(){
for(int i=0;i<4;i++)*(scr+80*tet[i][0]+tet[i][1])=32;
for(    i=0;i<4;i++){
		tet[i][1]--;
		*(scr+80*tet[i][0]+tet[i][1])=co*256+block_char;
	}
}

int canright(){
for(int i=0;i<4;i++)
	if(*(scr+80*tet[i][0]+tet[i][1]+1)!=32 )
		if(tet[i][1]+1 != tet[0][1] )
			if(tet[i][1]+1 != tet[1][1] )
				if(tet[i][1]+1 != tet[2][1] )
					if(tet[i][1]+1 != tet[3][1] )return 0;
return 1;
}

void doright(){
for(int i=0;i<4;i++)*(scr+80*tet[i][0]+tet[i][1])=32;
for(    i=0;i<4;i++){
		tet[i][1]++;
		*(scr+80*tet[i][0]+tet[i][1])=co*256+block_char;
	}
}

int checkl(int x){
for(int i=35;i<45;i++)
if( *(scr+x*80+i) == 32 )return 0;
score+=10;
*(scr+22*80+41)=0x0B*256+'0'+(score%10);
*(scr+22*80+42)=0x0B*256+'0'+(score/10)%10;
*(scr+22*80+43)=0x0B*256+'0'+(score/100)%10;
return 1;
}

void dol(int x){
for(int i=35;i<45;i++)
	*(scr+x*80+i) = 32;
for(i=35;i<45;i++){
int f=x*80+i;
//while(*(scr+f-80)!=32){
for(int j=x;j>1;j--){
*(scr+f)=*(scr+f-80);
f=f-80;
}
//*(scr+f)=*(scr+f-80);
}
}

void rotate(){
int tetup[4][2];
for(int i=0;i<4;i++)
	for(int j=0;j<2;j++)
		tetup[i][j]=tet[i][j];
for(i=0;i<4;i++)
	*(scr+80*tet[i][0]+tet[i][1])=32;
int z;
int avx=((tet[0][0]+tet[1][0]+tet[2][0]+tet[3][0])/4);
int avy=((tet[0][1]+tet[1][1]+tet[2][1]+tet[3][1])/4);
for(i=0;i<4;i++){
	*(scr+tet[i][0]*80+tet[i][1])=32;
}
for(i=0;i<4;i++){
z=tet[i][1]-avy;
tet[i][1]=-(tet[i][0]-avx)+avy;
tet[i][0]=z+avx;
}
int av2x=((tet[0][0]+tet[1][0]+tet[2][0]+tet[3][0])/4);
int av2y=((tet[0][1]+tet[1][1]+tet[2][1]+tet[3][1])/4);
for(i=0;i<4;i++){
tet[i][0]+=(-av2x+avx);
tet[i][1]+=(-av2y+avy);
}//etmam shabih sazi

int t=1;
for(i=0;i<4;i++)
	if(*(scr+80*tet[i][0]+tet[i][1]) != 32 )
		t=0;
/*if(t==1)
{for(i=0;i<4;i++)
*(scr+tet[i][0]*80+tet[i][1])=co*256+block_char;
}*/
if(t==0){
for(int i=0;i<4;i++)
	for(int j=0;j<2;j++)
		tet[i][j]=tetup[i][j];
}
for(i=0;i<4;i++)
*(scr+tet[i][0]*80+tet[i][1])=co*256+block_char;
}
int maxX(int a1,int a2,int a3,int a4){
if(a1>a2 && a1>a3 && a1>a4)return a1;
if(a2>a3 && a2>a4)return a2;
if(a3>a4)return a3;
}
void lose(){
for(int i=0;i<2000;i++)
	*(scr+i)=0x88*256+'Û';
for(i=5;i<16;i++)                        //L
	*(scr+80*i+10)=0xf5*256+'Û';
for(i=10;i<15;i++)
	*(scr+80*15+i)=0xf5*256+'Û';
for(i=5;i<15;i++)                    //O
	*(scr+80*i+20)=0xf5*256+'Û';
for(i=5;i<15;i++)
	*(scr+80*i+30)=0xf5*256+'Û';
for(i=20;i<=30;i++)
	*(scr+80*5+i)=0xf5*256+'Û';
for(i=20;i<=30;i++)
	*(scr+80*15+i)=0xf5*256+'Û';
for(i=35;i<45;i++)                       //S
	*(scr+80*5+i)=0xf5*256+'Û';
for(i=35;i<45;i++)
	*(scr+80*10+i)=0xf5*256+'Û';
for(i=35;i<45;i++)
	*(scr+80*15+i)=0xf5*256+'Û';
for(i=5;i<11;i++)
	*(scr+80*i+35)=0xf5*256+'Û';
for(i=10;i<16;i++)
	*(scr+80*i+45)=0xf5*256+'Û';
for(i=50;i<60;i++)                       //E
	*(scr+80*5+i)=0xf5*256+'Û';
for(i=50;i<60;i++)
	*(scr+80*10+i)=0xf5*256+'Û';
for(i=50;i<60;i++)
	*(scr+80*15+i)=0xf5*256+'Û';
for(i=5;i<15;i++)
	*(scr+80*i+50)=0xf5*256+'Û';
getch();

}