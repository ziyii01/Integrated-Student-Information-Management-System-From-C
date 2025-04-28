#pragma once
#include "common.h"

void sha256_hash(const char *input, char outputBuffer[65])
{
    unsigned char hash[EVP_MAX_MD_SIZE];
    unsigned int hash_len;
    EVP_MD_CTX *mdctx;

    // 创建并初始化消息摘要上下文
    mdctx = EVP_MD_CTX_new();
    EVP_DigestInit_ex(mdctx, EVP_sha256(), NULL);

    // 更新消息摘要上下文 dengan 输入数据
    EVP_DigestUpdate(mdctx, input, strlen(input));

    // 完成消息摘要计算并获取结果
    EVP_DigestFinal_ex(mdctx, hash, &hash_len);
    EVP_MD_CTX_free(mdctx);

    // 将哈希值转换为十六进制字符串
    for (unsigned int i = 0; i < hash_len; i++)
    {
        sprintf(outputBuffer + (i * 2), "%02x", hash[i]);
    }
    outputBuffer[64] = '\0'; // 确保字符串以null结尾
}