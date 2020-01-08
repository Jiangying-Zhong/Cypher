#define _CRT_SECURE_NO_DEPRECATE
#pragma warning( disable : 4996)

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <openssl/sha.h>

#define LEN 999999
unsigned long *Digest = (unsigned long *)malloc(sizeof(unsigned long) * 5);//���hashֵ,SHA1���ɵ�LM_HASH����Ϊ40
char mdString[SHA_DIGEST_LENGTH * 2 + 1];//���LM_HASHֵ
unsigned char digest[SHA_DIGEST_LENGTH];
char index[LEN] = { '0' };						  //�ʺ����������,�Ѿ�R�õ��˵�ֵ�Ͳ��ٳ�Ϊ��ͷ
void Generatehash();
void GenerateTable();
int  Ri(unsigned long *Digest, int i);
int R(int s, unsigned long *Digest, int t);
void Hash(int p, unsigned long *Digest);
unsigned long char_to_hex(char input[41], int t);
int Crack();
//unsigned char AscToHex(unsigned char aHex);

int main() {
	int op = 1, plain;
	char P[7];
	while (op){
		printf("\n\n");
		printf("	��1 SHA1�õ�hashֵ                 \n\n");
		printf("	��2 ���ɲʺ��                     \n\n");
		printf("	��3 �ƽ�HASH                   \n\n");
		printf("	��0 �˳�                           \n\n");
		printf("\n\n");
		printf("��ѡ����Ĳ���:");
		scanf("%d", &op);
		getchar();
		switch (op) {
		case 1:
			Generatehash();
			break;
		case 2:
			GenerateTable();
			break;
		case 3:
			plain = Crack();
			if (plain < 0)
				printf("�ƽ�HASHʧ�ܣ�\n");
			else {
				printf("\n�ƽ�HASH�ɹ���\n");
				int i,res=0,rem=0;
				char x[7];
				//printf("\n�ƽ��������Ϊ��%d", plain);
				for (i = 5; i >= 0; i--){
					res = plain % 36;
					plain= plain / 36;
					if ((res >= 0) && (res <= 9))
						x[i] = res + '0';
					else if ((res >= 10) && (res <= 35))
						x[i] = res - 10 + 'a';
					//printf("\n�ƽ��������Ϊ��%c\n", x[i]);
					//res = rem;
				}
				x[6] = '\0';
				printf("\n�ƽ��������Ϊ��%06s ", x);
			}
			break;
		case 0:
			printf("\n��ӭ�´η���\n");
			break;
		default:
			printf("\n�������!\n");
			break;
		}
		printf("\n\n");
		system("pause");
		system("cls");
	} 
}

/*��ָ����������hashֵ*/
void Generatehash() {
	int  j, i;
	char *x;//����x
	x = (char *)malloc(sizeof(char) * 7);
	int x1,sum=0,mul;
	printf("���������ģ�");
	scanf("%s", x);
	getchar();
	for (i = 0; i < 6; i++){
		if ((x[i] >= '0') && (x[i] <= '9'))
			x1 = x[i] - '0';
		else if ((x[i] >= 'a') && (x[i] <= 'z'))
			x1 = x[i] - 'a' + 10;
		
		/*mul = pow(36.0,5-i);
		sum *= mul;*/
		sum =sum * 36 + x1;
	}
	sprintf(x, "%06d", sum);

	x[6] = '\0';
	SHA1((unsigned char *)x, 7, (unsigned char *)&digest);
	printf("\n���ɵ�HASHֵΪ��\n");
	for (j = 0; j < 5; j++)
		for (i = 0; i < 4; i++)
			sprintf(&mdString[(i + j * 4) * 2], "%02x", (unsigned int)digest[3 - i + j * 4]);

	printf("%s\n", mdString);
	printf("\n����hashֵ�ɹ���\n");
}



/*���ɲʺ��*/
void GenerateTable() {
	FILE *fp;
	if ((fp = fopen("rainbow.txt", "wb+")) == NULL) {
		fputs("File error", stderr);
		exit(1); //���ļ������˳�1
	}
	int i;
	int temp;
	for (i = 0; i < LEN; i++) {
		if (index[i] == 1) continue;//�жϽڵ��Ƿ���ֹ�
		temp = R(i, Digest, 10);
		if (temp != 0) {
			fwrite(&i, sizeof(int), 1, fp);
			fwrite(&temp, sizeof(int), 1, fp);
		}
	}
	fclose(fp);
	printf("\n���ɲʺ��ɹ���\n");
}

/*�ʺ��R����*/
int  Ri(unsigned long *Digest, int i) {
	unsigned long point = 0;
	point += Digest[1] + i - 1;
	index[point % LEN] = 1;
	return point % LEN;
}

/*�ʺ��R������:������ײ���ʣ��ֲ�����*/
int R(int s, unsigned long *Digest, int t) {//i��t���ɸ������ַ����ȷ�Χ
	int i;
	unsigned long point = 0;
	for (i = 0; i < t; i++) {
		Hash(s, Digest);
		point = 0;
		point += Digest[1] + i % 5 + i / 5 ;//���Ŀռ�Ϊ6��R����Ҫ��֤�������Ҫ�����Ŀռ�һ�£���������������
		index[point % LEN] = 1;
		s = point % LEN;
	}
	return s;
}

/*SHA1��ʽHASH*/
void Hash(int p, unsigned long *Digest) {
	char *x;
	unsigned char *temp1;
	unsigned long *temp2;
	int j, temp;
	x = (char *)malloc(sizeof(char) * 7);
	for (j = 0; j < 6; j++) {
		x[5 - j] = p % 10 + '0';
		p = p / 10;
	}//��p��λ���뵽��������x�д��
	x[6] = '\0';
	SHA1((unsigned char *)x, 7, (unsigned char *)&digest);
	//char string[];SHA1((unsigned char*)&string, strlen(string), (unsigned char*)&digest);
	temp1 = digest;
	for (j = 0; j < 5; j++) {
		temp2 = (unsigned long*)(temp1);
		Digest[j] = *temp2;
		temp1 += 4;//��λһ��
	}//hashֵ��ŵ�Digest������
}

/*�ַ���ת��Ϊ32����ʮ������*/
unsigned long char_to_hex(char input[41], int t) {
	int i;
	char temp[8];
	unsigned long sum = 0;
	for (i = 0; i < 8; i++) {
		temp[i] = input[i + 8 * t];
	}
	sscanf(temp, "%lx", &sum);
	return sum;
}

/*�ƽ�hash*/
int Crack() {
	int i, j, t, n, flag = 1, k, temp;
	unsigned long *CYPHER;//LM_HASHת��Ϊ16����
	char cypher[41];//LM_HASHֵ�ַ���
	int head, tail;
	long lsize;                                   //�ļ���С
	FILE *fp;
	if ((fp = fopen("rainbow.txt", "rb")) == NULL) {
		fputs("File error", stderr);
		exit(1);
	}
	fseek(fp, 0, SEEK_END);//��λ���ļ�ĩβ
	lsize = ftell(fp);//�õ��ļ���С
	rewind(fp);//���ļ�ָ������ָ��һ�����Ŀ�ͷ
	n = lsize / (sizeof(int) * 2);                 //��n�Ա�ͷ��β
	CYPHER = (unsigned long *)malloc(sizeof(unsigned long) * 5);
	printf("���������ģ�");
	scanf("%s", cypher);
	for (j = 0; j < 5; j++)
		CYPHER[j] = char_to_hex(cypher, j);
	for (i = 9; i >= 0; i--) {
		for (j = i; j < 10; j++) {
			k = Ri(Digest, j % 5 + j / 5 + 1);     //������R-H�ظ�
			Hash(k, Digest);
		}
		for (j = 0; j < n; j++) {
			fread(&head, sizeof(int), 1, fp);
			fread(&tail, sizeof(int), 1, fp);
			flag = 1;
			for (t = 0; t < 5; t++)
				Digest[t] = CYPHER[t];
			if (tail == k) {
				temp = R(head, Digest, i); //�����ͬ�����ʺ�����Ӧ��ͷ����temp
				Hash(temp, Digest);                //���õ�������hash��������������ĶԱ�
				for (t = 0; t < 5 ; t++)
					if (Digest[t] != CYPHER[t]) flag = 0;
				if (flag)
					return temp;
			}
		}
		rewind(fp);//���ļ�ָ������ָ��һ�����Ŀ�ͷ
	}
	return -1;
}