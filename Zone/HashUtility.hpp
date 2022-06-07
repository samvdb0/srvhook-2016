#pragma once
#include "pch.h"
#include <WinCrypt.h>

class HashUtil
{
public:
    static const char* GetMD5(const char* data)
    {
        DWORD dwStatus = 0;
        DWORD cbHash = 16;
        HCRYPTPROV cryptProv;
        HCRYPTHASH cryptHash;
        BYTE hash[16];
        const char* hex = "0123456789abcdef";
        char* strHash;
        strHash = (char*)malloc(500);
        memset(strHash, '\0', 500);

        if (!CryptAcquireContext(&cryptProv, NULL, MS_DEF_PROV, PROV_RSA_FULL, CRYPT_VERIFYCONTEXT))
        {
            return NULL;
        }

        if (!CryptCreateHash(cryptProv, CALG_MD5, 0, 0, &cryptHash))
        {
            CryptReleaseContext(cryptProv, 0);
            return NULL;
        }

        if (!CryptHashData(cryptHash, (BYTE*)data, strlen(data), 0))
        {
            CryptReleaseContext(cryptProv, 0);
            CryptDestroyHash(cryptHash);
            return NULL;
        }

        if (!CryptGetHashParam(cryptHash, HP_HASHVAL, hash, &cbHash, 0))
        {
            CryptReleaseContext(cryptProv, 0);
            CryptDestroyHash(cryptHash);
            return NULL;
        }

        for (UINT32 i = 0; i < cbHash; i++)
        {
            strHash[i * 2] = hex[hash[i] >> 4];
            strHash[(i * 2) + 1] = hex[hash[i] & 0xF];
        }

        CryptReleaseContext(cryptProv, 0);
        CryptDestroyHash(cryptHash);
        return strHash;
    }
};