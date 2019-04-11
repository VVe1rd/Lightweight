


#ifndef ___LESAMNTALW_H
#define ___LESAMNTALW_H

/* The Lesamnta-LW hash length is 256 only. */
#define LESAMNTALW_HASH_BITLENGTH 256

/* The type of the input data */
typedef unsigned char BitSequence;

/* The data length type */
typedef uint64_t DataLength;

/* The success code values */
typedef enum {
/* Successfully computed the hash value */
            SUCCESS = 0,
/* Failed to compute the hash value */
            FAIL = 1,
/* Unsupported hash bit length */
            BAD_HASHBITLEN = 2,
} HashReturn;

/*
  SHA-3 API: Hash() provides a method to perform all-at-once
  processing of the input data and returns the resulting hash
  value. The Hash() function is called with a pointer to the data to
  be processed, the length of the data to be processed (databitlen), a
  pointer to the storage for the resulting hash value (hashval), and a
  length of the desired hash value (hashbitlen). This function
  utilizes the previous three function calls, namely Init(), Update(),
  and Final().
  Parameters:
  - hashbitlen: the length in bits of the desired hash value
  - data: the input data to be hashed
  - databitlen: the length, in bits, of the data to be hashed
  - hashval: the resulting hash value of the provided data
  Returns:
  - Success value.
*/
HashReturn Hash(int hashbitlen, const BitSequence *data,
                DataLength databitlen, BitSequence *hashval);


#endif  /* ___LESAMNTALW_H */

/* end of file */
