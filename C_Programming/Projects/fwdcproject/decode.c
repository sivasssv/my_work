#include <stdio.h>
#include <stdlib.h>
#include "decode.h"
#include "types.h"
#include <string.h>
#include "common.h"
#include "string.h"
Status_dec open_dec_files(DecodeInfo *decInfo, char *argv[])
{
	decInfo->fptr_stego_image = fopen(argv[2], "r");
	if (decInfo->fptr_stego_image == NULL)
	{
		perror("fopen");
		return d_failure;
	}

	decInfo->fptr_secret = fopen(argv[3], "w");
	if (decInfo->fptr_secret == NULL)
	{
		perror("fopen");
		return d_failure;
	}
	return d_success;
}

Status_dec decode_magic_string(char *magic_string, DecodeInfo *decInfo)
{
	char temp, mask, buffer = 0;
	int i;
	fseek(decInfo->fptr_stego_image,54,SEEK_SET);

	mask = 0x01;
	for(i = 0; i < (sizeof(char) * 8); ++i)
	{
		fread(&temp,1,1,decInfo->fptr_stego_image);
		if (decInfo->fptr_stego_image == NULL)
		{
			perror("fread");
			return d_failure;
		}
		buffer = buffer | ((temp & mask) << (7-i));
	}
	*magic_string = buffer;
//	if(*magic_string == MAGIC_STRING)
		return d_success;
//	return d_failure;
}

Status_dec decode_secret_file_extn(char *file_extn, DecodeInfo *decInfo)
{
	int i,j;
	unsigned int buffer = 0;
	char temp, mask, temp1;
	unsigned char buffer1;
//	fseek(decInfo->fptr_stego_image,62,SEEK_SET);
		
	for(j = 0; j < (sizeof(int) * 8); ++j)
	{
		mask = 0x01;
		fread(&temp,1,1,decInfo->fptr_stego_image);
		if (decInfo->fptr_stego_image == NULL)
		{
			perror("fread");
			return d_failure;
		}
		if(temp & mask)
		{
			buffer = (buffer << 1) | ~(-1 << 1);
		}
		else
		{
			buffer = (buffer << 1);
		} 
	}

//	fseek(decInfo->fptr_stego_image,94,SEEK_SET);

	for (i = 0; i < buffer; i++)
	{
		mask = 0x01;
		buffer1 = 0;
		for (j = 0; j < (sizeof(char) * 8); j++)
		{
			fread(&temp1,1,1,decInfo->fptr_stego_image);
			
			if (decInfo->fptr_stego_image == NULL)
			{
				perror("fread");
				return d_failure;
			}

			buffer1 = buffer1 | ((temp1 & mask) << (7-j));
		}
	}
	return d_success;
}

Status_dec decode_secret_file_size(DecodeInfo *decInfo)
{
	char mask, temp;
	unsigned int buffer = 0;
	int j;

//	fseek(decInfo->fptr_stego_image,126,SEEK_SET);
		
	for(j = 0; j < (sizeof(int) * 8); ++j)
	{
		mask = 0x01;
		fread(&temp,1,1,decInfo->fptr_stego_image);
		
		if (decInfo->fptr_stego_image == NULL)
		{
			perror("fread");
			return d_failure;
		}
		
		if(temp & mask)
		{
			buffer = (buffer << 1) | ~(-1 << 1);
		}
		else
		{
			buffer = (buffer << 1);
		} 
	}
	decInfo->size_secret_file = buffer;
	return d_success;
}

Status_dec decode_secret_file_data(DecodeInfo *decInfo)
{
	int size = decInfo->size_secret_file, i, j;
	char temp, mask;
	unsigned char buffer;

//	fseek(decInfo->fptr_stego_image, 158, SEEK_SET);
	fseek(decInfo->fptr_secret, 0, SEEK_SET);
		
	for(i = 0; i < size; ++i)
	{
		mask = 0x01;
		buffer = 0;
		for(j = 0; j < (sizeof(char) * 8); ++j)
		{
			fread(&temp,1,1,decInfo->fptr_stego_image);
		
			if (decInfo->fptr_stego_image == NULL)
			{
				perror("fread");
				return d_failure;
			}

			buffer = buffer | ((temp & mask) << (7-j));
		}
		fwrite(&buffer,1,1,decInfo->fptr_secret);
		
		if (decInfo->fptr_secret == NULL)
		{
			perror("fread");
			return d_failure;
		}
	}
	return d_success;
}

