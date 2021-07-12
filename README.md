## BoringSSL Symmetric Encryption with Bazel

A trivial helloworld example of using [Boring SSL](https://www.chromium.org/Home/chromium-security/boringssl) with [Bazel](https://bazel.build/).

Its basically a copy paste of openssl wiki example for [EVP Symmetric Encryption and Decryption](https://wiki.openssl.org/index.php/EVP_Symmetric_Encryption_and_Decryption) with BoringSSL and the bazel build system


You'll need bazel installed to use this sale

once its setup, you can run it to encrypt
```bash
$ bazel run //main:bssl_aes_cbc

Ciphertext is:
4G9jpxHot6qflEAQfUaAoReZQ4DqMdKimblTAtQ5uXAsjmWpkjbskgcEkVzxqYpE
Decrypted text is:
The quick brown fox jumps over the lazy dog
```

---

## References

- [AES-SIV with openssl](https://github.com/sophieschmieg/fun-with-gcm)
- [EVP Authenticated Encryption and Decryption](https://wiki.openssl.org/index.php/EVP_Authenticated_Encryption_and_Decryption)
- [Encoding and decoding base 64 with c++](https://renenyffenegger.ch/notes/development/Base64/Encoding-and-decoding-base-64-with-cpp/index)


