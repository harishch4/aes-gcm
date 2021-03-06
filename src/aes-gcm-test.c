/*
 * aes-gcm-test.c
 */

#define AES_DEBUG

#include "aes.h"

const unsigned char t3_key[] = {
    0xfe, 0xff, 0xe9, 0x92, 0x86, 0x65, 0x73, 0x1c, 0x6d, 0x6a, 0x8f, 0x94, 0x67, 0x30, 0x83, 0x08
};
const unsigned char t3_iv[] = {
    0xca, 0xfe, 0xba, 0xbe, 0xfa, 0xce, 0xdb, 0xad, 0xde, 0xca, 0xf8, 0x88
};
const unsigned char t3_aad[] = {};
const unsigned char t3_plain[] = {
    0xd9, 0x31, 0x32, 0x25, 0xf8, 0x84, 0x06, 0xe5, 0xa5, 0x59, 0x09, 0xc5, 0xaf, 0xf5, 0x26, 0x9a,
    0x86, 0xa7, 0xa9, 0x53, 0x15, 0x34, 0xf7, 0xda, 0x2e, 0x4c, 0x30, 0x3d, 0x8a, 0x31, 0x8a, 0x72,
    0x1c, 0x3c, 0x0c, 0x95, 0x95, 0x68, 0x09, 0x53, 0x2f, 0xcf, 0x0e, 0x24, 0x49, 0xa6, 0xb5, 0x25,
    0xb1, 0x6a, 0xed, 0xf5, 0xaa, 0x0d, 0xe6, 0x57, 0xba, 0x63, 0x7b, 0x39, 0x1a, 0xaf, 0xd2, 0x55
};
const unsigned char t3_crypt[] = {
    0x42, 0x83, 0x1e, 0xc2, 0x21, 0x77, 0x74, 0x24, 0x4b, 0x72, 0x21, 0xb7, 0x84, 0xd0, 0xd4, 0x9c,
    0xe3, 0xaa, 0x21, 0x2f, 0x2c, 0x02, 0xa4, 0xe0, 0x35, 0xc1, 0x7e, 0x23, 0x29, 0xac, 0xa1, 0x2e,
    0x21, 0xd5, 0x14, 0xb2, 0x54, 0x66, 0x93, 0x1c, 0x7d, 0x8f, 0x6a, 0x5a, 0xac, 0x84, 0xaa, 0x05,
    0x1b, 0xa3, 0x0b, 0x39, 0x6a, 0x0a, 0xac, 0x97, 0x3d, 0x58, 0xe0, 0x91, 0x47, 0x3f, 0x59, 0x85
};
const unsigned char t3_tag[] = {
    0x4d, 0x5c, 0x2a, 0xf3, 0x27, 0xcd, 0x64, 0xa6, 0x2c, 0xf3, 0x5a, 0xbd, 0x2b, 0xa6, 0xfa, 0xb4
};

int main(int argc, const char **argv)
{
    int result;
    
    unsigned char* crypt_buf = malloc(sizeof(t3_crypt));
    unsigned char* plain_buf = malloc(sizeof(t3_plain));
    unsigned char* tag_buf = malloc(sizeof(t3_tag));
    
    memset(crypt_buf, 0, sizeof(t3_crypt));
    memset(plain_buf, 0, sizeof(t3_plain));
    memset(tag_buf, 0, sizeof(t3_tag));
    
    result = aes_gcm_ae(t3_key, sizeof(t3_key),
                        t3_iv, sizeof(t3_iv),
                        t3_plain, sizeof(t3_plain),
                        t3_aad, sizeof(t3_aad),
                        crypt_buf, tag_buf);
    
    aes_printf(MSG_INFO, "t3 aes_gcm encrypt result %s",
               result == 0 ? "PASS" : "FAIL");
    aes_printf(MSG_INFO, "t3 aes_gcm encrypt crypt  %s",
               (memcmp(t3_crypt, crypt_buf, sizeof(t3_crypt)) == 0) ? "PASS" : "FAIL");
    aes_printf(MSG_INFO, "t3 aes_gcm encrypt tag    %s",
               (memcmp(t3_tag, tag_buf, sizeof(t3_tag)) == 0) ? "PASS" : "FAIL");
    
    result = aes_gcm_ad(t3_key, sizeof(t3_key),
                        t3_iv, sizeof(t3_iv),
                        t3_crypt, sizeof(t3_crypt),
                        t3_aad, sizeof(t3_aad),
                        tag_buf, plain_buf);
    
    aes_printf(MSG_INFO, "t3 aes_gcm decrypt result %s",
               result == 0 ? "PASS" : "FAIL");
    aes_printf(MSG_INFO, "t3 aes_gcm decrypt plain  %s",
               (memcmp(t3_plain, plain_buf, sizeof(t3_plain)) == 0) ? "PASS" : "FAIL");
    
    free(crypt_buf);
    free(plain_buf);
    free(tag_buf);

    return 0;
}
