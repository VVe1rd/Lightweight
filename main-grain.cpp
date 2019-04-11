/*
 * REFERENCE IMPLEMENTATION OF STREAM CIPHER GRAIN VERSION 1
 *
 * Filename: testvectors.c
 *
 * Author:
 * Martin Hell
 * Dept. of Information Technology
 * P.O. Box 118
 * SE-221 00 Lund, Sweden,
 * email: martin@it.lth.se
 *
 * Synopsis:
 *    Generates testvectors from the reference implementation of Grain Version 1.
 *
 */


#include <stdio.h>
#include <string.h>
#include "grain.h"

/*  GENERATE TEST VECTORS  */

void printData(u8 *key, u8 *IV, u8 *ks) {
	u32 i;
	printf("\n\nkey:        ");
	for (i=0;i<10;++i) printf("%02x",(int)key[i]);
	printf("\nIV :        ");
	for (i=0;i<8;++i) printf("%02x",(int)IV[i]);
	printf("\nkeystream:  ");
	for (i=0;i<10;++i) printf("%02x",(int)ks[i]);
}

int main_grain(unsigned char* random_message, int msg_length, unsigned char* random_key, int key_length, unsigned char* random_iv, int iv_length) {
    int i;
    u8 key[10], IV[8], ks[10];
    ECRYPT_ctx ctx;
    printf("---REFERENCE IMPLEMENTATION OF GRAIN---\n");
    for (i = 0; i < 10; ++i)
    {
        key[i] = random_key[i];
    }
    for (i = 0; i < 8; ++i)
    {
		IV[i] = random_iv[i];
    }

	ECRYPT_keysetup(&ctx,key,80,64);
	ECRYPT_ivsetup(&ctx,IV);
	ECRYPT_keystream_bytes(&ctx,ks,10);
	printData(key,IV,ks);

	printf("\n");
	return 0;
}


