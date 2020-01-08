#ifndef DIFF_H_INCLUDED
#define DIFF_H_INCLUDED
#define NUM_OF_TEST 80 
#define P 0x26B7//Ã÷ÎÄ
#define C 0xBCD6//ÃÜÎÄ
#define NUM_OF_ROLLKEY 5
#define ROTATE_RIGHT(x, s, n) ((x) >> (n)) | ((x) << ((s) - (n)))/*Ñ­»·ÓÒÒÆ*/ 
struct WORD0
{
	unsigned int l1:4;
	unsigned int l2:4;
};

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

struct WORD1 b;
struct WORD1 inv_pi_s(struct WORD2);//´úÌæÃÜÂëÄæ 
struct WORD2 pi_s(struct WORD1);//´úÌæÃÜÂë
struct WORD2 pi_p(struct WORD2);//ÖÃ»»ÃÜÂë
int analyze(unsigned short,unsigned short,unsigned short,unsigned short);

struct WORD1 inv_pi_s(struct WORD2 a)
{
	
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
#endif
