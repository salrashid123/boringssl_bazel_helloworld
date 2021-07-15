#include <ctime>
#include <string>
#include <iostream>
#include <string.h>  
#include <vector>
#include <ostream>
#include <sstream>

#include "lib/utils.h"

#include <openssl/bio.h>
#include <openssl/evp.h>
#include <openssl/aes.h>
#include <openssl/err.h>
#include <openssl/mem.h>
#include <openssl/obj.h>
#include <openssl/crypto.h>
#include <openssl/aead.h>

#include "openssl/rand.h"

void handleErrors(void)
{
    ERR_print_errors_fp(stderr);
    abort();
}

std::string uint8_vector_to_hex_string(const std::vector<uint8_t>& v)
{
    std::string result;
    result.reserve(v.size() * 2);   // two digits per character

    static constexpr char hex[] = "0123456789ABCDEF";

    for (uint8_t c : v)
    {
        result.push_back(hex[c / 16]);
        result.push_back(hex[c % 16]);
    }

    return result;
}
//https://commondatastorage.googleapis.com/chromium-boringssl-docs/aead.h.html
std::string encrypt(std::string plaintext, std::string key,  std::string additional_data, std::string nonce, std::string tag)
{
    EVP_AEAD_CTX ctx;
    const EVP_AEAD *aead = EVP_aead_aes_256_gcm_siv(); 
    std::vector<uint8_t> akey, anonce, aplaintext, arad, act, atag;

    ConvertToBytes(&akey, key);
    ConvertToBytes(&anonce, nonce);
    ConvertToBytes(&aplaintext, plaintext);
    ConvertToBytes(&arad, additional_data);
    ConvertToBytes(&atag, tag);


    if (!EVP_AEAD_CTX_init(&ctx, aead, akey.data(), akey.size(),  atag.size(), NULL))
        handleErrors();

    size_t out_len;
    std::vector<uint8_t> out(aplaintext.size() + EVP_AEAD_max_overhead(aead));

    if (!EVP_AEAD_CTX_seal(&ctx, out.data(), &out_len, out.size(),
                                    anonce.data(), anonce.size(), aplaintext.data(),
                                    aplaintext.size(), arad.data(), arad.size()))
        handleErrors();
    out.resize(out_len);

    EVP_AEAD_CTX_cleanup(&ctx);

    return uint8_vector_to_hex_string(out);
}


std::string decrypt(std::string cipher_text, std::string key,  std::string additional_data, std::string nonce, std::string tag)
{
    EVP_AEAD_CTX ctx;
    const EVP_AEAD *aead = EVP_aead_aes_256_gcm_siv();
    std::vector<uint8_t> akey, anonce, aciphertext, arad, act, atag;

    ConvertToBytes(&akey, key);
    ConvertToBytes(&anonce, nonce);
    ConvertToBytes(&aciphertext, cipher_text);
    ConvertToBytes(&arad, additional_data);
    ConvertToBytes(&atag, tag);

    if (!EVP_AEAD_CTX_init(&ctx, aead, akey.data(), akey.size(),  atag.size(), NULL))
        handleErrors();

    size_t out_len;
    std::vector<uint8_t> out(aciphertext.size() + EVP_AEAD_max_overhead(aead));

    if (!EVP_AEAD_CTX_open(&ctx, out.data(), &out_len, out.size(),
                                    anonce.data(), anonce.size(), aciphertext.data(),
                                    aciphertext.size(), arad.data(), arad.size()))
        handleErrors();
    out.resize(out_len);

    EVP_AEAD_CTX_cleanup(&ctx);

    return uint8_vector_to_hex_string(out);
}


int main (void)
{
    // control:
    // https://github.com/google/boringssl/blob/94b477cea5057d9372984a311aba9276f737f748/crypto/cipher_extra/test/aes_256_gcm_siv_tests.txt#L139
    // plaintext = ced477a00135f16006e100b9d7521f9e1bddbc7d339cc41333abe3cc79dd8e3a18e310dd1dd53ac664673ab9090d5dc07b4859

    std::string key = "9c8fde2be2cf97e74e932d4ed87da44102952ef94b02b805249bac80e6f61455";
    std::string nonce = "bfac8308a2d40d8c84511780";
    std::string plaintext = "666f6f6f626172";   // fooobar
    std::string additional_data ="06556fb6aa7890bebc18fe6b3db4da3d57aa94842b9803a96e07fb";
    std::string tag = "fdfb01ef873060efc7c3c32adf3b46cc";
    std::string cipher_text = encrypt (plaintext, key, additional_data, nonce ,tag);

     printf("Ciphertext is:\n");
    std::cout << cipher_text << std::endl;

    std::string plain_text = decrypt (cipher_text, key, additional_data, nonce ,tag);

     printf("Plaintext is:\n");
    std::cout << plain_text << std::endl;


    return 0;
}