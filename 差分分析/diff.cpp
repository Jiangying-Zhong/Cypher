#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "diff.h"
unsigned short encode(unsigned short x, unsigned long key);
int baopo(); 

int main()
{
	FILE *fp;
	fp = fopen("2.1.dat", "r");
	unsigned short x1[NUM_OF_TEST];
	unsigned short x2[NUM_OF_TEST];
	unsigned short y1[NUM_OF_TEST];
	unsigned short y2[NUM_OF_TEST];
	int i=0;
	int j=0;
	int k=0;
	int COUNT[16][16];
	int t1,t2,time1,time2;
	unsigned short l;
	int max = -1;
	unsigned char maxkey;
	struct WORD1 u4_1;
	struct WORD2 v4_1;
	struct WORD1 u4_2;
	struct WORD2 v4_2;
	unsigned short temp;
	unsigned short p1;
	unsigned short p2;
	unsigned short X1,X2,Y1,Y2;
	int p;
	int q;
	
	printf("P    = %8x\n", P);
	printf("C    = %8x\n\n", C);
	
	for(j = 0; j<0x10; j++)
	{
		for(k=0;k<0x10;k++)
		{
			COUNT[j][k] = 0;//计数器清零
		}
	}
	
	t1=clock();
	for(i=0;i!=NUM_OF_TEST;i++)
	{
		fscanf(fp, "%x %x %x %x\n", &x1[i],&x2[i],&y1[i],&y2[i]);
		X1=x1[i];	
		X2=x2[i];
		Y1=y1[i];
		Y2=y2[i];
		temp = 0;	
		for(j = 0; j<16; j++)
		{
			for(k=0;k<16;k++)
			{
				l=k+(j<<8);  
				temp=l^Y1;
				memcpy(&v4_1,&temp,2);
				u4_1=inv_pi_s(v4_1);
				temp=l^Y2;
				memcpy(&v4_2,&temp,2);
				u4_2=inv_pi_s(v4_2);
				memcpy(&p1,&u4_1,2);
				memcpy(&p2,&u4_2,2);
				temp = p1 ^ p2;
				p=(temp>>8)&0x000f;
				q=(temp)&0x000f;
				if( (p == 6) && (q == 6))
					COUNT[j][k]++;
			}
		}	
	}
	
	max = -1;
	
	int maxkey1=-1,maxkey2=-1;
	for(j = 0; j<16; j++)
		{
			for(k=0;k<16;k++)
			{
				if(COUNT[j][k]>max)
		{
			max = COUNT[j][k];
			maxkey1 = j;
			maxkey2 = k;
		}
	}
}

	
	printf("候选子密钥key : %x %x\n\n",maxkey1,maxkey2);
	t2=clock();
	time1=(double)(t2-t1);
	printf("时间为%dms\n\n", time1);
	t1=clock();
	baopo();
	/*t2=clock();
	time2=(double)(t2-t1);
	printf("时间为%dms\n\n", time2);*/ 
	fclose(fp);
}

int baopo()
{
	unsigned short x = P;
    unsigned short y = C;//密文
	unsigned long key =0;/*密钥*/
	unsigned long rightkey[10000];
	int i = 1;
	int l;
	                 //3A94D63F
	int t = 0;
	int u = 0;
	for(u=0;u<=0x000fffff;u++) //u表示遍历前20位
	{
		for(t=0;t<=16;t++)//t表示遍历t位
		{
			key=u<<12&0xfffff000|0x0000060f|(t<<4);
			if( encode(x, key) == y)
			{
				if(encode(0,key)==0x00009278)
				{
					printf("一个可能密钥已经找到.key = %8x\n",key);
					/*printf("按'c'继续, 其他键停止.");
					if(getchar()!='c')
						goto end;*/ 
					rightkey[i] = key;
					i++;
				} 
				continue;
		}
		else; 
		}

	}
	end:
		l=i;
	/*for(i=1;i<l;i++)
	{
		printf("第%d个 :key= %8x\n",i,rightkey[i]);
	}*/ 
	return 0;
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


