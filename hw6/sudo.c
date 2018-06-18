#include <openssl/sha.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define PASSWORD "211c08aec3385db0da9825b7ccdb458d6c27a337325fe0664926587a91baa7f4"

int auth = 0;

void sha256(const char* data, char* hash)
{
    int i;
    SHA256_CTX sha256;
    unsigned char buff[SHA256_DIGEST_LENGTH] = {0};

    SHA256_Init(&sha256);
    SHA256_Update(&sha256, data, strlen(data));
    SHA256_Final(buff, &sha256);

    for (i = 0; i < sizeof(buff); i++)
        sprintf(hash + 2 * i, "%02x", buff[i]);
}

void check_password(const char* password)
{
    char buff[65] = {0};
    char hash[65] = {0};
    buff[0]  = 'T';
    buff[1]  = 'h';
    buff[2]  = 'i';
    buff[3]  = 's';
    buff[4]  = 'i';
    buff[5]  = 's';
    buff[6]  = 'a';
    buff[7]  = 's';
    buff[8]  = 'a';
    buff[9]  = 'l';
    buff[10] = 't';
    buff[11] = '\0';
    strcat(buff, password);
    sha256(buff, hash);

    if (strcmp(hash, PASSWORD) == 0)
        auth = 1;
}

int main(int argc, char* argv[])
{
    setuid(0);
    setgid(0);

    if (argc < 2) {
        printf("USAGE: %s <password>\n", argv[0]);
        return 1;
    }

    check_password(argv[1]);

    if (auth) {
        puts("Victory!\n");
    }
    else {
        printf("ERROR: invalid password.\n");
        return 1;
    }

    return 0;
}
