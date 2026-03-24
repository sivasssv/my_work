#ifndef DECODE_H
#define DECODE_H

#include "types.h" // Contains user defined types

#define MAX_SECRET_BUF_SIZE 1
#define MAX_IMAGE_BUF_SIZE (MAX_SECRET_BUF_SIZE * 8)
#define MAX_FILE_SUFFIX 4

typedef struct _DecodeInfo
{
    // Secret File Info
    char *secret_fname;
    FILE *fptr_secret;
    char extn_secret_file[MAX_FILE_SUFFIX];
    char secret_data[MAX_SECRET_BUF_SIZE];
    int size_secret_file;

    // Stego Image Info 
    char *stego_image_fname;
    FILE *fptr_stego_image;

} DecodeInfo;

/* Perform the decoding */
Status_dec do_decoding(DecodeInfo *decInfo);

/* Get File pointers for i/p and o/p files */
Status_dec open_dec_files(DecodeInfo *decInfo, char *argv[]);

/* check capacity */
//Status check_capacity(DecodeInfo *decInfo);

/* Get image size */
//uint get_image_size_for_bmp(FILE *fptr_image);

/* Get file size */
//uint get_file_size(FILE *fptr);

/* Copy bmp image header */
//Status copy_bmp_header(FILE *fptr_src_image, FILE *fptr_dest_image);

/* Store Magic String */
Status_dec decode_magic_string(char *magic_string, DecodeInfo *decInfo);

/* Encode secret file extenstion */
Status_dec decode_secret_file_extn(char *file_extn, DecodeInfo *decInfo);

/* Encode secret file size */
Status_dec decode_secret_file_size(DecodeInfo *decInfo);

/* Encode secret file data*/
Status_dec decode_secret_file_data(DecodeInfo *decInfo);

/* Encode function, which does the real encoding */
//Status decode_data_to_image(char *data, int size, FILE *fptr_src_image, FILE *fptr_stego_image);

/* Encode a byte into LSB of image data array */
Status_dec decode_lsb_to_byte(char data, char *image_buffer);

/* Copy remaining image bytes from src to stego image after encoding */
//Status copy_remaining_img_data(FILE *fptr_src, FILE *fptr_dest);

#endif
