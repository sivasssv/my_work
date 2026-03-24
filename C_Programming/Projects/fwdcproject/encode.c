#include <stdio.h>
#include "encode.h"
#include "types.h"
#include <string.h>

/* Function Definitions */
OperationType check_operation_type(char *argv[])
{
	if (strcmp(argv[1], "-e") == 0)
		return e_encode;
	else if (strcmp(argv[1], "-d") == 0)
		return e_decode;
	else
		return e_unsupported;
}
Status read_and_validate_encode_args(char *argv[], EncodeInfo *encInfo)
{
	if(check_operation_type(argv) == e_encode)
	{
		encInfo->src_image_fname = argv[2];
		if(argv[3] != NULL)
		{
			encInfo->secret_fname = argv[3];
		}
		return e_success;
	}
	if(check_operation_type(argv) == e_decode)
	{
		encInfo->stego_image_fname = argv[2];
		if(argv[3] != NULL)
		{
			encInfo->secret_fname = argv[3];
		}
		return e_success;
	}
	
	else
		return e_failure;
}
/* Get image size
 * Input: Image file ptr
 * Output: width * height * bytes per pixel (3 in our case)
 * Description: In BMP Image, width is stored in offset 18,
 * and height after that. size is 4 bytes
 */
uint get_image_size_for_bmp(FILE *fptr_image)
{
	int length;
/*    uint width, height;
    // Seek to 18th byte
    fseek(fptr_image, 18, SEEK_SET);

    // Read the width (an int)
    fread(&width, sizeof(int), 1, fptr_image);
    printf("width = %u\n", width);

    // Read the height (an int)
    fread(&height, sizeof(int), 1, fptr_image);
    printf("height = %u\n", height);

    // Return image capacity
    return width * height * 3;*/
    fseek(fptr_image,0,SEEK_END);
    length = ftell(fptr_image);
    return (length - 55);
}
uint get_file_size(FILE *fptr)
{
	uint file_size;
	fseek(fptr,0,SEEK_END);
	file_size = ftell(fptr);
	fseek(fptr,0,SEEK_SET);
	return file_size;
}

/* 
 * Get File pointers for i/p and o/p files
 * Inputs: Src Image file, Secret file and
 * Stego Image file
 * Output: FILE pointer for above files
 * Return Value: e_success or e_failure, on file errors
 */
Status open_files(EncodeInfo *encInfo, char *argv[])
{
    encInfo->fptr_src_image = fopen(encInfo->src_image_fname, "r");
    if (encInfo->fptr_src_image == NULL)
    {
    	perror("fopen");
    	return e_failure;
    }

    encInfo->fptr_secret = fopen(encInfo->secret_fname, "r");
    if (encInfo->fptr_secret == NULL)
    {
    	perror("fopen");
    	return e_failure;
    }

    encInfo->fptr_stego_image = fopen(argv[4], "w");
    if (encInfo->fptr_stego_image == NULL)
    {
    	perror("fopen");
    	return e_failure;
    }
    return e_success;
}
Status copy_bmp_header(FILE *fptr_src_image, FILE *fptr_dest_image)
{
	char buf[54];

	fseek(fptr_src_image, 0L, SEEK_SET);
	fread(buf, sizeof(char), 54,fptr_src_image);
    if (fptr_src_image == NULL)
    {
    	perror("fread");
    	return e_failure;
    }

	fseek(fptr_dest_image, 0L, SEEK_SET);
	fwrite(buf, sizeof(char), 54,fptr_dest_image);
    if (fptr_dest_image == NULL)
    {
    	perror("fwrite");
    	return e_failure;
    }
    return e_success;
}

Status encode_magic_string(const char *magic_string, EncodeInfo *encInfo)
{
	unsigned char temp, temp1, mask;
	int i, j;

	fseek(encInfo->fptr_src_image,0,SEEK_CUR);
	fseek(encInfo->fptr_stego_image,0,SEEK_CUR);
	
	mask = ((~0) << 7);
	temp = *magic_string;
	for(j = 0; j < (sizeof(char) * 8); ++j)
	{
		fread(&temp1,1,1,encInfo->fptr_src_image);
		if (encInfo->fptr_src_image == NULL)
		{
			perror("fread");
			return e_failure;
		}

		if(temp & mask)
			temp1 = temp1 | (0x01);
		else
			temp1 = temp1 & ((~0) << 1);

		fwrite(&temp1,1,1,encInfo->fptr_stego_image);
		if (encInfo->fptr_stego_image == NULL)
		{
			perror("fwrite");
			return e_failure;
		}
		mask >>= 1;
	}
	return e_success;
}
Status encode_secret_file_extn(const char *file_extn, EncodeInfo *encInfo)
{
	unsigned char temp, temp1, mask;
	int i, j;
	unsigned int mask1, num = strlen(file_extn);

	fseek(encInfo->fptr_src_image,0,SEEK_CUR);
	fseek(encInfo->fptr_stego_image,0,SEEK_CUR);
	
	mask1 = 0x80000000; 
	for(j = 0; j < (sizeof(int) * 8); ++j)
	{
		fread(&temp1,1,1,encInfo->fptr_src_image);
		if (encInfo->fptr_src_image == NULL)
		{
			perror("fread");
			return e_failure;
		}
		if(num & mask1)
			temp1 = temp1 | (0x01);
		else
			temp1 = temp1 & (0xFE);

		fwrite(&temp1,1,1,encInfo->fptr_stego_image);
		if (encInfo->fptr_stego_image == NULL)
		{
			perror("fwrite");
			return e_failure;
		}
		mask1 >>= 1;
	}

	fseek(encInfo->fptr_src_image,0,SEEK_CUR);
	fseek(encInfo->fptr_stego_image,0,SEEK_CUR);
	
	for(i = 0; i < strlen(file_extn); ++i)
	{
		mask = ((~0) << 7);
		temp = *(file_extn + i);
		for(j = 0; j < (sizeof(char) * 8); ++j)
		{
			fread(&temp1,1,1,encInfo->fptr_src_image);
			if (encInfo->fptr_src_image == NULL)
			{
				perror("fread");
				return e_failure;
			}
			if(temp & mask)
				temp1 = temp1 | (0x01);
			else
				temp1 = temp1 & ((~0) << 1);

			fwrite(&temp1,1,1,encInfo->fptr_stego_image);
			if (encInfo->fptr_stego_image == NULL)
			{
				perror("fwrite");
				return e_failure;
			}
			mask >>= 1;
		}
	}
	return e_success;
}
Status encode_secret_file_size(int file_size, EncodeInfo *encInfo)
{
	char temp1;
	int j;
	unsigned int mask = (~0) << 31;

	fseek(encInfo->fptr_src_image,0,SEEK_CUR);
	fseek(encInfo->fptr_stego_image,0,SEEK_CUR);
	
	for(j = 0; j < (sizeof(int) * 8); ++j)
	{
		fread(&temp1,1,1,encInfo->fptr_src_image);
		if (encInfo->fptr_src_image == NULL)
		{
			perror("fread");
			return e_failure;
		}

		if( (file_size & mask) == 0)
			temp1 = temp1 & (-1 << 1);
		else
			temp1 = temp1 | (0x01);
		
		fwrite(&temp1,1,1,encInfo->fptr_stego_image);
		if (encInfo->fptr_stego_image == NULL)
		{
			perror("fwrite");
			return e_failure;
		}

		mask >>= 1;
	}
	return e_success;
}
Status encode_secret_file_data(EncodeInfo *encInfo)
{
	char ch, temp;
	unsigned char mask;
	int j;

	fseek(encInfo->fptr_src_image,0,SEEK_CUR);
	fseek(encInfo->fptr_stego_image,0,SEEK_CUR);
	
	while( (ch = fgetc(encInfo->fptr_secret)) != EOF)
	{
		mask = 0x80;
		for(j = 0; j < (sizeof(char) * 8); ++j)
		{
			fread(&temp,1,1,encInfo->fptr_src_image);
			if (encInfo->fptr_src_image == NULL)
			{
				perror("fread");
				return e_failure;
			}
			
			if(ch & mask)
				temp = temp | (0x01);
			else
				temp = temp & ((~0) << 1);

			fwrite(&temp,1,1,encInfo->fptr_stego_image);
			if (encInfo->fptr_stego_image == NULL)
			{
				perror("fwrite");
				return e_failure;
			}

			mask >>= 1;
		}
	}
	return e_success;
}
Status copy_remaining_img_data(FILE *fptr_src_image, FILE *fptr_stego_image)
{
	char temp;
	fseek(fptr_src_image,0,SEEK_CUR);
	fseek(fptr_stego_image,0,SEEK_CUR);

/*	while(feof(fptr_src_image) == 0)
	{
		fread(&temp,1,1,fptr_src_image);
		if (fptr_src_image == NULL)
		{
			perror("fread");
			return e_failure;
		}

		fwrite(&temp,1,1,fptr_stego_image);
		if (fptr_stego_image == NULL)
		{
			perror("fwrite");
			return e_failure;
		}
	}*/
	while(1)
	{
		fread(&temp,1,1,fptr_src_image);
		if (fptr_src_image == NULL)
		{
			perror("fread");
			return e_failure;
		}

		if (feof(fptr_src_image))
			break;

		fwrite(&temp,1,1,fptr_stego_image);
		if (fptr_stego_image == NULL)
		{
			perror("fwrite");
			return e_failure;
		}
	}
	return e_success;
}
