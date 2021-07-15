## BoringSSL Symmetric Encryption with Bazel

A trivial helloworld example of using [Boring SSL](https://www.chromium.org/Home/chromium-security/boringssl) with [Bazel](https://bazel.build/).

Its basically a copy paste of openssl wiki example for [EVP Symmetric Encryption and Decryption](https://wiki.openssl.org/index.php/EVP_Symmetric_Encryption_and_Decryption) with BoringSSL and the bazel build system.

Includes:

* `EVP_aes_256_cbc`
* `EVP_aead_aes_256_gcm_siv`

You'll need bazel installed to use this sale

once its setup, you can run it to encrypt
```bash
$ bazel run //main:bssl_aes_cbc
    Ciphertext is:
    4G9jpxHot6qflEAQfUaAoReZQ4DqMdKimblTAtQ5uXAsjmWpkjbskgcEkVzxqYpE
    Decrypted text is:
    The quick brown fox jumps over the lazy dog
```


```bash
$ bazel run //main:bssl_aes_siv
    Ciphertext is:
    AB3E62CFC73FA188265ED94BE50B9482F342613541213D
    Plaintext is:
    666F6F6F626172
```

---

## References

- [AES-SIV with openssl](https://github.com/sophieschmieg/fun-with-gcm)
- [EVP Authenticated Encryption and Decryption](https://wiki.openssl.org/index.php/EVP_Authenticated_Encryption_and_Decryption)
- [Encoding and decoding base 64 with c++](https://renenyffenegger.ch/notes/development/Base64/Encoding-and-decoding-base-64-with-cpp/index)


