
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "code2x.h"

///
///	File:	hexs2std.h: ��ʮ�������ַ����鰴8�ֽڲ�ȫ��ʵ��
///

/*
*����:��ʮ�������ַ����鰴8�ֽ�padding��ȫ
*������src:Դʮ�������ַ���
*���أ�����һ��ָ��Ŀ�������ָ��
*/
char *hexs_to_std(const char *src)
{
	if (src == NULL)
	{
		return NULL;
	}

	int len = 0, slen = 0;	//nlen:Դ���� len�������׼����
	char *stdsrc = NULL, ch = '\0', *srcasc = NULL, *stdhex = NULL;

	srcasc = hexs_to_ascs(src);
	slen = strlen(srcasc);
	
	len = (slen / 8 + (slen % 8 ? 1 : 0)) * 8;
	
	stdsrc = (char *)malloc(sizeof(char) * len);
	if (stdsrc == NULL)
	{
		return NULL;
	}

	memcpy(stdsrc, srcasc, len);
	
	ch = 8 - slen % 8;	//padding ���뷽ʽ

	memset(stdsrc + slen, ch, 8 - slen % 8);
	stdsrc[len] = '\0';
	

	stdhex = ascs_to_hexs(stdsrc);

	free(srcasc);
	free(stdsrc);
	
	return stdhex;

}
