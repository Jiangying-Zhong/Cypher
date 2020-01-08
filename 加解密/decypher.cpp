#define KEY 0x3A94D63F
#define NUM_OF_ROLLKEY 5
#define ROTATE_LEFT(x, s, n) ((x) >> (n)) | ((x) << ((s) - (n)))/*Ñ­»·×óÒÆ*/
#include <stdio.h> 
#include <string.h>
#include <stdlib.h>

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

struct WORD1 inv_pi_s(struct WORD2);/*´úÌæÃÜÂë*/ 
struct WORD2 inv_pi_p(struct WORD2);/*ÖÃ»»ÃÜÂë*/ 

int main() 
{ 
    unsigned short C;//Ã÷ÎÄ 
    unsigned short x;//ÃÜÎÄ 
    FILE *fp = NULL;
    FILE *fp1 = NULL;
    fp = fopen("y.dat", "r"); /*´ÓÎÄ¼þ¶ÁÃÜÎÄ*/
    fp1 = fopen("xp.dat", "w");
    if(fp == NULL || fp1 == NULL)
    {
    	printf("fail to open the file!");
    	exit(-1);
	}
    fscanf(fp, "%x", &C); /*¶ÁÈ¡ÃÜÎÄ*/ 
	 
    unsigned long key = KEY;/*ÃÜÔ¿*/ 
    unsigned short rollkey[NUM_OF_ROLLKEY];/*Éú³ÉÂÖÃÜÔ¿*/
    int i = 0;
	for ( i = NUM_OF_ROLLKEY-1; i>=0 ; i--)
	{
		rollkey[i] = ROTATE_LEFT(key, 32, (4-i)*4) &0x0f;
		printf("K %d  = %8x\n\n", i+1 ,rollkey[i]);
	}
	
	printf("y    = %8x\n\n", C); 
	struct WORD2 w[NUM_OF_ROLLKEY-2];
	struct WORD1 u[NUM_OF_ROLLKEY-1];
	struct WORD2 v[NUM_OF_ROLLKEY-1];
	unsigned short temp;
	int r = 1;
	
	temp = C ^ rollkey[4];
	memcpy(&v[4],&temp ,2);
	u[4] = inv_pi_s(v[4]);
	memcpy(&temp,&u[4],2);
	temp = rollkey[3] ^ temp;
	memcpy(&w[3],&temp ,2);
	for(r = NUM_OF_ROLLKEY-2; r>=1; r--)
	{
		v[r] = inv_pi_p(w[r]);
		u[r] = inv_pi_s(v[r]);
		memcpy(&temp,&u[r] ,2);
		temp = temp ^ rollkey[r-1];
		memcpy(&w[r-1],&temp ,2);

	}
	memcpy(&x,&w[0] ,2);
	printf("x    = %8x\n",x);
	fprintf(fp1, "%x", x);
	fclose(fp);
}

struct WORD1 inv_pi_s(struct WORD2 a)
{
	struct WORD1 b;
	memcpy(&b,&a ,2);
	switch(b.s1)
	{
		case 0xE: b.s1 = 0x0;break;
		case 0x4: b.s1 = 0x1;break;
		case 0xD: b.s1 = 0x2;break;
		case 0x1: b.s1 = 0x3;break;
		case 0x2: b.s1 = 0x4;break;
		case 0xF: b.s1 = 0x5;break;
		case 0xB: b.s1 = 0x6;break;
		case 0x8: b.s1 = 0x7;break;
		case 0x3: b.s1 = 0x8;break;
		case 0xA: b.s1 = 0x9;break;
		case 0x6: b.s1 = 0xA;break;
		case 0xC: b.s1 = 0xB;break;
		case 0x5: b.s1 = 0xC;break;
		case 0x9: b.s1 = 0xD;break;
		case 0x0: b.s1 = 0xE;break;
		case 0x7: b.s1 = 0xF;break;
	}
	
	switch(b.s2)
	{
		case 0xE: b.s2 = 0x0;break;
		case 0x4: b.s2 = 0x1;break;
		case 0xD: b.s2 = 0x2;break;
		case 0x1: b.s2 = 0x3;break;
		case 0x2: b.s2 = 0x4;break;
		case 0xF: b.s2 = 0x5;break;
		case 0xB: b.s2 = 0x6;break;
		case 0x8: b.s2 = 0x7;break;
		case 0x3: b.s2 = 0x8;break;
		case 0xA: b.s2 = 0x9;break;
		case 0x6: b.s2 = 0xA;break;
		case 0xC: b.s2 = 0xB;break;
		case 0x5: b.s2 = 0xC;break;
		case 0x9: b.s2 = 0xD;break;
		case 0x0: b.s2 = 0xE;break;
		case 0x7: b.s2 = 0xF;break;
	}
	
	switch(b.s3)
	{
		case 0xE: b.s3 = 0x0;break;
		case 0x4: b.s3 = 0x1;break;
		case 0xD: b.s3 = 0x2;break;
		case 0x1: b.s3 = 0x3;break;
		case 0x2: b.s3 = 0x4;break;
		case 0xF: b.s3 = 0x5;break;
		case 0xB: b.s3 = 0x6;break;
		case 0x8: b.s3 = 0x7;break;
		case 0x3: b.s3 = 0x8;break;
		case 0xA: b.s3 = 0x9;break;
		case 0x6: b.s3 = 0xA;break;
		case 0xC: b.s3 = 0xB;break;
		case 0x5: b.s3 = 0xC;break;
		case 0x9: b.s3 = 0xD;break;
		case 0x0: b.s3 = 0xE;break;
		case 0x7: b.s3 = 0xF;break;
	}
	
	switch(b.s4)
	{
		case 0xE: b.s4 = 0x0;break;
		case 0x4: b.s4 = 0x1;break;
		case 0xD: b.s4 = 0x2;break;
		case 0x1: b.s4 = 0x3;break;
		case 0x2: b.s4 = 0x4;break;
		case 0xF: b.s4 = 0x5;break;
		case 0xB: b.s4 = 0x6;break;
		case 0x8: b.s4 = 0x7;break;
		case 0x3: b.s4 = 0x8;break;
		case 0xA: b.s4 = 0x9;break;
		case 0x6: b.s4 = 0xA;break;
		case 0xC: b.s4 = 0xB;break;
		case 0x5: b.s4 = 0xC;break;
		case 0x9: b.s4 = 0xD;break;
		case 0x0: b.s4 = 0xE;break;
		case 0x7: b.s4 = 0xF;break;
	}
	return b;
}

struct WORD2 inv_pi_p(struct WORD2 a)
{
	struct WORD2 b;
	b.p1 = a.p1;
	b.p5 = a.p2;
	b.p9 = a.p3;
	b.p13 = a.p4;
	b.p2 = a.p5;
	b.p6 = a.p6;
	b.p10 = a.p7;
	b.p14 = a.p8;
	b.p3 = a.p9;
	b.p7 = a.p10;
	b.p11 = a.p11;
	b.p15 = a.p12;
	b.p4 = a.p13;
	b.p8 = a.p14;
	b.p12 = a.p15;
	b.p16 = a.p16;
	return b;
}
