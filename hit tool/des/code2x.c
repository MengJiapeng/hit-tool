#include "code2x.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//
//	File:	code2x.c: ASCII���ַ�����ʮ�������Լ��������ַ�����ת��ʵ��
//

/*
*���ܣ�ʵ��һ��ʮ�������ַ���ʮ����������ת��
*������ch��ָ��ʮ�������ַ�
*���أ�uint8_t
*/
uint8_t asc_to_hex(const char ch)
{
	if (ch >= '0' && ch <= '9')  //����0~9
	{
		return (ch - 0x30);
	}
	else
	{
		if (ch >= 'A' && ch <= 'F')  //��д��ĸA~F
		{
			return (ch - 0x37);
		}
		else if (ch >= 'a' && ch <= 'f') //Сд��ĸa~f
		{
			return ch - 0x57;
		}
		else
		{
			return 0xFF;
		}
	}
}

/*
*���ܣ�ʵ��һ��ʮ����������ʮ�����ƴ�д�ַ���ת��
*������hex��ָ��ʮ��������
*���أ�char
*/
char hex_to_asc(uint8_t hex)
{
	if(hex < 10)
	{
		return hex + '0';
	}
	else if(hex < 16)
	{
		return hex + 55;
	}
	else
	{
		return 0;
	}
}
/*
*���ܣ�ʵ��һ���������ַ���������������ת��
*������ch��ָ���������ַ�
*���أ�uint8_t
*/
uint8_t asc_to_bin(const char ch)
{
	if (ch == '0') {
		return 0;
	}
	else if (ch == '1') {
		return 1;
	}
	else return -1;
}

/*
*���ܣ�ʵ��ASCII���ַ�����ʮ�������ַ�����ת��
*������src:��Ҫת����ASEII���ַ���
*���أ�ָ��ת����ʮ�������ַ��������ָ��
*/
char *ascs_to_hexs(const char *src)
{
	if (src == NULL) {
		return NULL;
	}

	int datasize = 0, buffsize = 0;
	char *dst;

	datasize = strlen(src);
	buffsize = 2 * datasize;	//����GBK���룬�ַ���תʮ�����Ƴ��Ȼ���ԭ������

	dst = (char *)malloc(sizeof(char)*buffsize + 1);
	memset(dst,0,sizeof(char)*buffsize + 1);

	dst[buffsize + 1] = '\0';	//��β��ӽ�����

	if (dst != NULL)
	{
		for (int i = 0; 0 != src[i]; i++)
		{
			sprintf(dst + i * 2, "%02x", (unsigned char)src[i]);
		}
		return dst;
	}
	else return NULL;
}

/*
*���ܣ�ʵ��ʮ�������ַ������������ַ�����ת��
*������src:��Ҫת����ʮ�������ַ���
*���أ�ָ��ת����������ַ��������ָ��
*/
char *hexs_to_bins(const char *src)
{
	if (src == NULL || (strlen(src) % 2 != 0)) {
		return NULL;
	}

	int datasize = 0, buffsize = 0;
	uint8_t n, nhex;

	char *dst;

	datasize = strlen(src);
	buffsize = 4 * datasize;	//ʮ������ת�����Ƴ��Ȼ���ԭ���ı�

	dst = (char *)malloc(sizeof(char)*buffsize + 1);
	memset(dst, 0, sizeof(char)*buffsize + 1);

	dst[buffsize + 1] = '\0';	//��β��ӽ�����

	if (dst != NULL)
	{
		for (int i = 0; 0 != src[i]; i++)
		{
			//ת������λ
			nhex = 0;
			n = asc_to_hex(src[i++]);
			if (n == 0xFF)
			{
				return NULL;
			}
			nhex = n << 4;
			
			//ת������λ
			n = asc_to_hex(src[i]);
			if (n == 0xFF)
			{
				return NULL;
			}
			nhex |= n;

			//������Ŀ������
			for (int j = 0; j < 8; j++)
			{
				dst[((i-1)/2)*8+j] = ((nhex & (1 << (7 - j))) && 1) + '0';
			}
		}
		return dst;
	}
	else return NULL;
}

/*
*���ܣ�ʵ�ֶ������ַ�����ʮ�������ַ�����ת��
*������src:��Ҫת���Ķ������ַ���
*���أ�ָ��ת����ʮ�������ַ��������ָ��
*/
char *bins_to_hexs(const char *src)
{
	if (src == NULL || (strlen(src) % 8 != 0)) {	//ÿ��λת��Ϊһ��ʮ��������
		return NULL;
	}

	int datasize = 0, buffsize = 0;
	uint8_t n, nbin;

	char *dst;

	datasize = strlen(src);
	buffsize = datasize / 4;	//ʮ������ת�����Ƴ��Ȼ���ԭ���ķ�֮һ

	dst = (char *)malloc(sizeof(char)*buffsize + 1);
	memset(dst, 0, sizeof(char)*buffsize + 1);

	dst[buffsize + 1] = '\0';	//��β��ӽ�����

	if (dst != NULL)
	{
		for (int i = 0; 0 != src[i]; i++)
		{
			//ת������λ
			nbin = 0;
			for (int j = 0; j < 4; j++)
			{
				n = asc_to_bin(src[i++]);
				if (n == -1)
				{
					return NULL;
				}
				nbin |= n << (7-j);	//�� 0 1 ���������
			}

			//ת������λ
			for (int j = 0; j < 4; j++) 
			{

				n = asc_to_bin(src[i++]);
				if (n == -1)
				{
					return NULL;
				}
				nbin |= n << (3-j);
			}

			//������Ŀ������

			sprintf(dst + (((i / 8) - 1)*2), "%x", nbin);

			i--;	//ת������λʱi���һλ����ȥ
		}
		return dst;
	}
	else return NULL;
}

/*
*���ܣ�ʵ��ʮ�������ַ�����ASCII�ַ�����ת��
*������src:��Ҫת����ʮ�������ַ���
*���أ�ָ��ת����ASCII���ַ��������ָ��
*/
char *hexs_to_ascs(const char *src)
{
	if (src == NULL || (strlen(src) % 2 != 0)) {	//GBK������λ�����ϱ�ʾһ���ַ�
		return NULL;
	}

	int datasize = 0, buffsize = 0, tmp = 0, i = 0;
	char *dst;

	datasize = strlen(src);
	buffsize = datasize / 2;	//GBK���룬ʮ������ת�ַ����ȼ�һ��

	dst = (char *)malloc(sizeof(char)*buffsize + 1);
	memset(dst, 0, sizeof(char)*buffsize + 1);

	dst[buffsize + 1] = '\0';	//��β��ӽ�����

	if (dst != NULL)
	{
		for (i = 0; i < buffsize; i++)	//iӦ�õ�datasize/2 = buffssize����
		{
			sscanf(src + i*2, "%2x", &tmp);
			dst[i] = (char)tmp;
		}
		return dst;
	}
	else return NULL;
}
