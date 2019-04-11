
#include <getopt.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "lesamnta-LW.h"

#define NELMS(a) (sizeof(a)/sizeof(a[0]))


static void showUsage(const char *programName)
{
    fprintf(stderr, "%s [--help] [--testVector] file\n", programName);
}


static void showTestVector(void)
{
    /* Hash value */
    BitSequence hashval[LESAMNTALW_HASH_BITLENGTH / 8];

    /* Test vector 1
       Ref: IEICE Trans. vol.E95-A, no.1, 2012, p.97 */
    {
        BitSequence data[] = { 'a', 'b', 'c' };
        DataLength databitlen = NELMS(data) * 8;
        memset(hashval, 0x00, sizeof(hashval));
        Hash(LESAMNTALW_HASH_BITLENGTH, data, databitlen, hashval);
        printf("message: ");
        for (int i = 0; i < NELMS(data); ++i) {
            printf("%02x", data[i]);
        }
        printf("\n");
        printf("hashval: ");
        for (int i = 0; i < LESAMNTALW_HASH_BITLENGTH / 8; ++i) {
            printf("%02x", hashval[i]);
        }
        printf("\n");
        printf("Note: The hash value in the reference is incorrect.\n\n");
    }

    /* Test vector 2 */
    {
        BitSequence data[256/8] = { 0x00 };
        for (int i = 0; i < NELMS(data); ++i) {
            data[i] = (BitSequence)'L';
        }
        DataLength databitlen = NELMS(data) * 8;
        Hash(LESAMNTALW_HASH_BITLENGTH, data, databitlen, hashval);
        printf("message: ");
        for (int i = 0; i < NELMS(data); ++i) {
            printf("%02x", data[i]);
        }
        printf("\n");
        printf("hashval: ");
        for (int i = 0; i < LESAMNTALW_HASH_BITLENGTH / 8; ++i) {
            printf("%02x", hashval[i]);
        }
        printf("\n");
    }
}


int main_LW(unsigned char* random_message, int msg_length, unsigned char*, int, unsigned char*, int)
{
    BitSequence *data = random_message;
    DataLength bytelen = msg_length;
    DataLength databitlen = bytelen * 8;
    BitSequence hashval[LESAMNTALW_HASH_BITLENGTH / 8];
    Hash(LESAMNTALW_HASH_BITLENGTH, data, databitlen, hashval);
    printf("message: ");
    for (int i = 0; i < bytelen; ++i) {
        printf("%02x", data[i]);
    }
    printf("\n");
    printf("hashval: ");
    for (int i = 0; i < LESAMNTALW_HASH_BITLENGTH / 8; ++i) {
        printf("%02x", hashval[i]);
    }
    printf("\n");
    free(data);

    return 0;
}

/* end of file */
