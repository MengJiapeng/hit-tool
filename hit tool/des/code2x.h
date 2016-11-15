#ifndef CODE2X_H
#define CODE2X_H
//
//	File:	code2x.h : ASCII���ַ�����ʮ�������Լ��������ַ���
//
typedef unsigned char uint8_t;

char hex_to_asc(uint8_t hex);
uint8_t asc_to_hex(const char ch);		//ʮ�������ַ�ת����
uint8_t asc_to_bin(const char ch);		//�������ַ�ת����
char *ascs_to_hexs(const char *src);	//�ַ���תʮ������
char *hexs_to_bins(const char *src);	//ʮ������ת������
char *bins_to_hexs(const char *src);	//������תʮ������
char *hexs_to_ascs(const char *src);	//ʮ������ת�ַ���

#endif // !CODE2X_H



