#include <stdio.h>
#include "encode.h"
#include "types.h"
#include "common.h"
#include "encode.c"
#include "decode.h"
#include "decode.c"

int main(int argc, char *argv[])
{
    EncodeInfo encInfo;
    DecodeInfo decInfo;
    uint img_size;
   
    encInfo.src_image_fname = "beautiful.bmp";
    encInfo.secret_fname = "secret.txt";
    encInfo.stego_image_fname = "stego_img.bmp";
    decInfo.stego_image_fname = "stego_img.bmp";
    decInfo.secret_fname = "secret_msg.txt";
	
    // Fill with sample filenames
	
	if (argc < 3)
	{
		printf("%s: Encoding: %s -e <.bmp file> <.txt file> [output file]\n", argv[0], argv[0]);

		printf("%s: Decoding: %s -d <.bmp file> [output file]\n", argv[0], argv[0]);
		return 1;
	}

	if(read_and_validate_encode_args(argv, &encInfo) == e_failure)
	{
		printf("ERROR: check your argumemts\n");
		return 1;
	}

	if(check_operation_type(argv) == e_encode)
	{
		if(argv[4] == NULL)
		{
			printf("INFO: output file not mentioned. Creating stego_img.bmp as default\n");
		}
    // Test open_files
		 printf("INFO: Opening required files\n");
		if (open_files(&encInfo,argv) == e_failure)
		{
			printf("ERROR: %s function failed\n", "open_files" );
		}
		 else
		{
			printf("INFO: Opened %s\n", argv[2]);
			printf("INFO: Opened %s\n", argv[3]);
			printf("INFO: Opened %s\n", argv[4]);
			printf("INFO; Done\n");
		 }

		printf("INFO: ## Encoding Procedure Started ##\n");
    
		 // Test get_image_size_for_bmp
		img_size = get_image_size_for_bmp(encInfo.fptr_src_image);
	
		// Getting the size of secret file
		printf("INFO: Checking for secret.txt size\n");
		encInfo.size_secret_file = get_file_size(encInfo.fptr_secret);
		if (encInfo.size_secret_file > 0)
		{
			printf("INFO: Done. Not Empty\n");
		}
		else
		{
			printf("INFO: ERROR. Function Failed\n");
		}
		// Checking the capacity of .bmp to handle .txt
		printf("INFO: Checking for beautiful.bmp capapcity to handle secret.txt\n");
		if (img_size > encInfo.size_secret_file)
		{
			printf("INFO: Done. Found OK\n");
		}
		else
		{
			printf("INFO: ERROR. Function Failed\n");
		}
		// Copying Image Header
		printf("INFO: Copying Image Header\n");
		if ( copy_bmp_header(encInfo.fptr_src_image,encInfo.fptr_stego_image) == e_success)
		{
			printf("INFO: Done\n");
		}
		else
		{
			printf("INFO: ERROR. Function Failed\n");
		}
		// Encoding Magic String
		printf("INFO: Encoding Magic String Signature\n");
		if ( encode_magic_string(MAGIC_STRING, &encInfo) == e_success)
		{
			printf("INFO: Done\n");
		}
		else
		{
			printf("INFO: ERROR. Function Failed\n");
		}
		// Encoding Secret file extension
		printf("INFO: Encoding Secret File Extension\n");
		if ( encode_secret_file_extn(EXTN_STRING, &encInfo) == e_success)
		{
			printf("INFO: Done\n");
		}
		else
		{
			printf("INFO: ERROR. Function Failed\n");
		}
		// Encoding secret file size
		printf("INFO: Encoding Secret File Size\n");
		if ( encode_secret_file_size(encInfo.size_secret_file, &encInfo)  == e_success)
		{
			printf("INFO: Done\n");
		}
		else
		{
			printf("INFO: ERROR. Function Failed\n");
		}
		// Encoding Secret file data
		printf("INFO: Encoding Secret File Data\n");
		if ( encode_secret_file_data(&encInfo) == e_success )
		{
			printf("INFO: Done\n");
		}
		else
		{
			printf("INFO: ERROR. Function Failed\n");
		}
		// Copying the remaining bytes
		printf("INFO: Copying Left Over Data\n");
		if ( copy_remaining_img_data(encInfo.fptr_src_image, encInfo.fptr_stego_image) == e_success)
		{
			printf("INFO: Done\n");
		}
		else
		{
			printf("INFO: ERROR. Function Failed\n");
		}
		printf("INFO: ## Encoding Done Successfully ##\n");
	}
	else if(check_operation_type(argv) == e_decode)
	{
		printf("INFO: ## Decoding Procedure Started\n");
	
		printf("INFO: Opening required files\n");
	
		if (open_dec_files(&decInfo,argv) == e_failure)
		{
			printf("error\n");
		}
		else
		{
			printf("INFO: Opended %s\n", argv[3]);
		}
		printf("INFO: Opened secret_msg.txt\n");

		printf("INFO: Decoding Magic String Signature\n");
		if(decode_magic_string(decInfo.secret_data, &decInfo) == d_success)
		{
			printf("INFO: Done\n");
		}
		else
		{
			printf("INFO: ERROR. Function Failed\n");
		}
		printf("INFO: Done.Opened all required files\n");
		decode_secret_file_extn(decInfo.extn_secret_file, &decInfo);
	
		printf("INFO: Decoding secret_msg.txt File Size\n");
	
		if(decode_secret_file_size(&decInfo) == d_success)
		{
			printf("INFO: Done\n");
		}
		else
		{
			printf("INFO: ERROR. Function Failed\n");
		}
		printf("INFO: Decoding secret_msg.txt File Data\n");
	
		if(decode_secret_file_data(&decInfo) == d_success)
		{
			printf("INFO: Done\n");
		}
		else
		{
			printf("INFO: ERROR. Function Failed\n");
		}
		printf("INFO: ## Decoding Done Successfully ##\n");
		}
		else
		{
			printf("INFO: Unsupported operation\n");
		}
}
