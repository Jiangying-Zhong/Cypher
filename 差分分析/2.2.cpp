#define KEY 0x3A94D63F
#define NUM_OF_ROLLKEY 5
#define ROTATE_RIGHT(x, s, n) ((x) >> (n)) | ((x) << ((s) - (n)))/*循环右移*/
#define NUM_OF_TEST 0xffff
#define xp 0x0B00/*   x'  */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

struct WORD1
{
	unsigned int s1:4;
	unsigned int s2:4;
	unsigned int s3:4;
	unsigned int s4:4;
};

struct WORD2
{
	unsigned int p1:1;
	unsigned int p2:1;
	unsigned int p3:1;
	unsigned int p4:1;
	unsigned int p5:1;
	unsigned int p6:1;
	unsigned int p7:1;
	unsigned int p8:1;
	unsigned int p9:1;
	unsigned int p10:1;
	unsigned int p11:1;
	unsigned int p12:1;
	unsigned int p13:1;
	unsigned int p14:1;
	unsigned int p15:1;
	unsigned int p16:1;
};

struct WORD2 pi_s(struct WORD1);/*代替密码*/
struct WORD2 pi_p(struct WORD2);/*置换密码*/
unsigned short encode(unsigned short x, unsigned long key);

int main()
{
    unsigned short P[NUM_OF_TEST];//明文
    unsigned short x2;
    unsigned short y;//密文
	unsigned short y2;
	int d;
	int num = 0;
    FILE *fp = NULL;
    FILE *fp1 = NULL;
    fp = fopen("1.1.dat", "r"); /*从文件读明文*/
    fp1 = fopen("2.1.dat", "w");

    if(fp == NULL || fp1 == NULL)
    {
    	printf("fail to open the file!");
    	exit(-1);
	}
	unsigned long key = KEY;/*密钥*/
    unsigned short rollkey[NUM_OF_ROLLKEY];/*生成轮密钥*/
    int i = 0;
	struct WORD2 w[NUM_OF_ROLLKEY-2];
	struct WORD1 u[NUM_OF_ROLLKEY-1];
	struct WORD2 v[NUM_OF_ROLLKEY-1];
	unsigned short temp;
	int r = 1;
	unsigned short count = 0;
	for(count = 0; count !=NUM_OF_TEST ;count++)
	{
		fscanf(fp, "%x ", &P[count]); /*读取明文*/

	for ( i = 0; i<NUM_OF_ROLLKEY ; i++)
	{
		rollkey[i] = ROTATE_RIGHT(key, 32, (4-i)*4) &0x0f;
	}

	x2 = P[count] ^ xp;

	/*memcpy(&w[0],&P[count] ,2);
	for(r = 1; r<=NUM_OF_ROLLKEY-2; r++)
	{
		memcpy(&temp,&w[r-1] ,2);
		temp = temp ^ rollkey[r-1];
		memcpy(&u[r],&temp ,2);
		v[r] = pi_s(u[r]);
		w[r] = pi_p(v[r]);
	}
	memcpy(&temp,&w[r-1] ,2);
	temp = temp ^ rollkey[r-1];
	memcpy(&u[r],&temp ,2);
	v[r] = pi_s(u[r]);
	memcpy(&temp,&v[r] ,2);
	y = temp ^ rollkey[NUM_OF_ROLLKEY-1];*/
	y=encode(P[count],key);
	y2=encode(x2,key);


//	y=0x0402;
//	y2=0x030b;


	d=  (((y^y2)>>12)&0xf) | (((y^y2)>>4)&0xf);
//	system("Pause");
	if(d==0)
	{
		printf("x = %4x   x2 = %4x   y = %4x   y2 = %4x  %4x %4x\n",P[count], x2, y, y2,P[count]^x2,y^y2);
		fprintf(fp1, "%x %x %x %x\n", P[count], x2, y, y2); /*输出*/
	//	system("Pause");
		num++;
	}

	else
		printf("x = %4x   x2 = %4x   y = %4x   y2 = %4x  %4x %4x\n",P[count], x2, y, y2,P[count]^x2,y^y2);
	//fprintf(fp1, "%x ", P[count]); /*输出*/

	}
	printf("明密文对均已经生成并保存在了2.1.dat中。共计%d",num);

//	fprintf(fp1, "%x", y); /*输出密文*/
	fclose(fp);
	fclose(fp1);

/*	memcpy(&temp,&w[NUM_OF_ROLLKEY-2] ,2);
	temp = temp ^ rollkey[NUM_OF_ROLLKEY-1];
	memcpy(&u[NUM_OF_ROLLKEY-1],&temp ,2);
	v[NUM_OF_ROLLKEY-1] = pi_s(u[NUM_OF_ROLLKEY-1]);
	memcpy(&temp,&v[NUM_OF_ROLLKEY-1] ,2);
	y = temp ^ rollkey[NUM_OF_ROLLKEY];
*/
//  fgets(s, 24, fp); /*从文件中读取23个字符*/
//  printf("%s", s);
//  putchar(fgetc(fp)); /*读取一个字符同时输出*/
//  fgets(m, 17, fp); /*读取16个字符*/
//  puts(m); /*输出所读字符串*/
}

struct WORD2 pi_s(struct WORD1 a)
{
	struct WORD1 b;
	struct WORD2 c;
	switch(a.s1)
	{
		case 0x0: b.s1 = 0xE;break;
		case 0x1: b.s1 = 0x4;break;
		case 0x2: b.s1 = 0xD;break;
		case 0x3: b.s1 = 0x1;break;
		case 0x4: b.s1 = 0x2;break;
		case 0x5: b.s1 = 0xF;break;
		case 0x6: b.s1 = 0xB;break;
		case 0x7: b.s1 = 0x8;break;
		case 0x8: b.s1 = 0x3;break;
		case 0x9: b.s1 = 0xA;break;
		case 0xA: b.s1 = 0x6;break;
		case 0xB: b.s1 = 0xC;break;
		case 0xC: b.s1 = 0x5;break;
		case 0xD: b.s1 = 0x9;break;
		case 0xE: b.s1 = 0x0;break;
		case 0xF: b.s1 = 0x7;break;
	}

	switch(a.s2)
	{
		case 0x0: b.s2 = 0xE;break;
		case 0x1: b.s2 = 0x4;break;
		case 0x2: b.s2 = 0xD;break;
		case 0x3: b.s2 = 0x1;break;
		case 0x4: b.s2 = 0x2;break;
		case 0x5: b.s2 = 0xF;break;
		case 0x6: b.s2 = 0xB;break;
		case 0x7: b.s2 = 0x8;break;
		case 0x8: b.s2 = 0x3;break;
		case 0x9: b.s2 = 0xA;break;
		case 0xA: b.s2 = 0x6;break;
		case 0xB: b.s2 = 0xC;break;
		case 0xC: b.s2 = 0x5;break;
		case 0xD: b.s2 = 0x9;break;
		case 0xE: b.s2 = 0x0;break;
		case 0xF: b.s2 = 0x7;break;
	}

	switch(a.s3)
	{
		case 0x0: b.s3 = 0xE;break;
		case 0x1: b.s3 = 0x4;break;
		case 0x2: b.s3 = 0xD;break;
		case 0x3: b.s3 = 0x1;break;
		case 0x4: b.s3 = 0x2;break;
		case 0x5: b.s3 = 0xF;break;
		case 0x6: b.s3 = 0xB;break;
		case 0x7: b.s3 = 0x8;break;
		case 0x8: b.s3 = 0x3;break;
		case 0x9: b.s3 = 0xA;break;
		case 0xA: b.s3 = 0x6;break;
		case 0xB: b.s3 = 0xC;break;
		case 0xC: b.s3 = 0x5;break;
		case 0xD: b.s3 = 0x9;break;
		case 0xE: b.s3 = 0x0;break;
		case 0xF: b.s3 = 0x7;break;
	}

	switch(a.s4)
	{
		case 0x0: b.s4 = 0xE;break;
		case 0x1: b.s4 = 0x4;break;
		case 0x2: b.s4 = 0xD;break;
		case 0x3: b.s4 = 0x1;break;
		case 0x4: b.s4 = 0x2;break;
		case 0x5: b.s4 = 0xF;break;
		case 0x6: b.s4 = 0xB;break;
		case 0x7: b.s4 = 0x8;break;
		case 0x8: b.s4 = 0x3;break;
		case 0x9: b.s4 = 0xA;break;
		case 0xA: b.s4 = 0x6;break;
		case 0xB: b.s4 = 0xC;break;
		case 0xC: b.s4 = 0x5;break;
		case 0xD: b.s4 = 0x9;break;
		case 0xE: b.s4 = 0x0;break;
		case 0xF: b.s4 = 0x7;break;
	}

	memcpy(&c,&b ,2);
	return c;
}

struct WORD2 pi_p(struct WORD2 a)
{
	struct WORD2 b;
	b.p1 = a.p1;
	b.p2 = a.p5;
	b.p3 = a.p9;
	b.p4 = a.p13;
	b.p5 = a.p2;
	b.p6 = a.p6;
	b.p7 = a.p10;
	b.p8 = a.p14;
	b.p9 = a.p3;
	b.p10 = a.p7;
	b.p11 = a.p11;
	b.p12 = a.p15;
	b.p13 = a.p4;
	b.p14 = a.p8;
	b.p15 = a.p12;
	b.p16 = a.p16;
	return b;
}


unsigned short encode(unsigned short x, unsigned long key)
{
	unsigned short y;//密文
	unsigned short rollkey[NUM_OF_ROLLKEY];/*生成轮密钥*/
    int i = 0;
	for ( i = 0; i<NUM_OF_ROLLKEY ; i++)
	{
		rollkey[i] = ROTATE_RIGHT(key, 32, (4-i)*4) &0x0f;
	}

	struct WORD2 w[NUM_OF_ROLLKEY-2];
	struct WORD1 u[NUM_OF_ROLLKEY-1];
	struct WORD2 v[NUM_OF_ROLLKEY-1];
	unsigned short temp;
	int r = 1;

	memcpy(&w[0], &x ,2);
	for(r = 1; r<=NUM_OF_ROLLKEY-2; r++)
	{
		memcpy(&temp,&w[r-1] ,2);
		temp = temp ^ rollkey[r-1];
		memcpy(&u[r],&temp ,2);
		v[r] = pi_s(u[r]);
		w[r] = pi_p(v[r]);
	}
	memcpy(&temp,&w[r-1] ,2);
	temp = temp ^ rollkey[r-1];
	memcpy(&u[r],&temp ,2);
	v[r] = pi_s(u[r]);
	memcpy(&temp,&v[r] ,2);
	y = temp ^ rollkey[NUM_OF_ROLLKEY-1];

	return y;
}
