#include <stdio.h>
#include <string.h>

#define MAX 1000

// Perform CRC division using XOR
void crcDivision(char data[], char generator[], char remainder[])
{
    int dataLen = strlen(data);
    int genLen = strlen(generator);
    char temp[MAX];

    strcpy(temp, data);

    // XOR division
    for (int i = 0; i <= dataLen - genLen; i++)
    {
        if (temp[i] == '1')
        {
            for (int j = 0; j < genLen; j++)
            {
                if (temp[i + j] == generator[j])
                    temp[i + j] = '0';
                else
                    temp[i + j] = '1';
            }
        }
    }

    // Last (genLen - 1) bits are the remainder
    strcpy(remainder, &temp[dataLen - genLen + 1]);
}

// Convert a word into binary ASCII
void wordToBinary(char word[], char binary[])
{
    binary[0] = '\0';

    for (int i = 0; word[i] != '\0'; i++)
    {
        unsigned char ch = word[i];

        for (int j = 7; j >= 0; j--)
        {
            if (ch & (1 << j))
                strcat(binary, "1");
            else
                strcat(binary, "0");
        }
    }
}

int main()
{
    char word[100];
    char generator[] = "10011";

    char data[MAX];
    char paddedData[MAX];
    char remainder[100];
    char transmitted[MAX];

    printf("Enter a word: ");
    scanf("%s", word);

    // Convert word to binary
    wordToBinary(word, data);

    printf("\nData in binary : %s\n", data);
    printf("Generator      : %s\n", generator);

    // Append n-1 zeros
    strcpy(paddedData, data);

    for (int i = 0; i < strlen(generator) - 1; i++)
        strcat(paddedData, "0");

    // Find CRC remainder
    crcDivision(paddedData, generator, remainder);

    printf("CRC Remainder  : %s\n", remainder);

    // Append CRC to original data
    strcpy(transmitted, data);
    strcat(transmitted, remainder);

    printf("Transmitted Data: %s\n", transmitted);

    return 0;
}