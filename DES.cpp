#include <iostream>
#include "windows.h"

using namespace std;

//variables

UINT8 InitialPermutation[] = {
    58, 50, 42, 34, 26, 18, 10, 2,
    60, 52, 44, 36, 28, 20, 12, 4,
    62, 54, 46, 38, 30, 22, 14, 6,
    64, 56, 48, 40, 32, 24, 16, 8,
    57, 49, 41, 33, 25, 17, 9, 1,
    59, 51, 43, 35, 27, 19, 11, 3,
    61, 53, 45, 37, 29, 21, 13, 5,
    63, 55, 47, 39, 31, 23, 15, 7
};

UINT8 InvInitialPermutation[] = {
    40, 8, 48, 16, 56, 24, 64, 32,
    39, 7, 47, 15, 55, 23, 63, 31,
    38, 6, 46, 14, 54, 22, 62, 30,
    37, 5, 45, 13, 53, 21, 61, 29,
    36, 4, 44, 12, 52, 20, 60, 28,
    35, 3, 43, 11, 51, 19, 59, 27,
    34, 2, 42, 10, 50, 18, 58, 26,
    33, 1, 41, 9,  49, 17, 57, 25
};

UINT8 PBox[] = {
    32, 1,  2,  3,  4,  5,
    4,  5,  6,  7,  8,  9,
    8,  9,  10, 11, 12, 13,
    12, 13, 14, 15, 16, 17,
    16, 17, 18, 19, 20, 21,
    20, 21, 22, 23, 24, 25,
    24, 25, 26, 27, 28, 29,
    28, 29, 30, 31, 32, 1
};

UINT8 StraightPBox[] = {
    16, 7,  20, 21, 29, 12, 28, 17,
    1,  15, 23, 26, 5,  18, 31, 10,
    2,  8,  24, 14, 32, 27, 3,  9,
    19, 13, 30, 6,  22, 11, 4,  25
};

UINT8 SBox[8][4][16] = {
    {
        {14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7},
        {0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8},
        {4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0},
        {15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13}
    },
    {
        {15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10},
        {3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5},
        {0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15},
        {13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9}
    },
    {
        {10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8},
        {13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1},
        {13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7},
        {1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12}
    },
    {
        {7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15},
        {13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9},
        {10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4},
        {3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14}
    },
    {
        {2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9},
        {14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6},
        {4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14},
        {11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3}
    },
    {
        {12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11},
        {10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8},
        {9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6},
        {4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13}
    },
    {
        {4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1},
        {13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6},
        {1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2},
        {6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12}
    },
    {
        {13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7},
        {1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2},
        {7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8},
        {2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11}
    }
};

UINT8 KeyTransposition[] = {
    57, 49, 41, 33, 25, 17, 9, 1, 58, 50, 42, 34, 26, 18,
    10, 2, 59, 51, 43, 35, 27, 19, 11, 3, 60, 52, 44, 36,
    63, 55, 47, 39, 31, 23, 15, 7, 62, 54, 46, 38, 30, 22,
    14, 6, 61, 53, 45, 37, 29, 21, 13, 5, 28, 20, 12, 4
};

UINT8 LeftCiklTrans[] = {
    1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1
};

UINT8 RoundCompression[] = {
    14, 17, 11, 24, 1, 5, 3, 28,
    15, 6, 21, 10, 23, 19, 12, 4,
    26, 8, 16, 7, 27, 20, 13, 2,
    41, 52, 31, 37, 47, 55, 30, 40,
    51, 45, 33, 48, 44, 49, 39, 56,
    34, 53, 46, 42, 50, 36, 29, 32
};

//functions

void IsEqueal(BYTE* a, BYTE* b)
{
    bool res=true;
    for (int i = 0; i < 8; i++)
        if (a[i] != b[i]) res = false;
    if (res) cout << "Success!\n";
    else cout << "Failed!\n";
}

void Print(bool* bits, int sz)
{
    for (int i = 0; i < sz; i++)
        cout << (int)bits[i];
    cout << endl;
}

void Print(BYTE* data)
{
    for (int i = 0; i < 8; i++)
        cout << (int)data[i] << " ";
    cout << endl;
}

bool* BYTEStoBITS(BYTE* data)
{
    bool* bits = new bool[64];
    for (int i = 0; i < 8; i++)
    {
        BYTE tmp = data[i];
        for (int j = 0; j < 8; j++)
        {
            bits[8 * i + 7 - j] = (tmp % 2);
            tmp >>= 1;
        }
    }

    return bits;
}

BYTE* BITStoBYTES(bool* data)
{
    BYTE* res = new BYTE[8];
    for (int i = 0; i < 8; i++)
    {
        BYTE tmp = 0;
        for (int j = 0; j < 8; j++)
        {
            tmp <<= 1;
            tmp += (int)data[8 * i + j];
        }
        res[i] = tmp;
    }
    return res;
}

UINT32* BITStoUINT32(bool* data)
{
    UINT32* res = new UINT32[2];
    for (int i=0; i<2; i++)
    {
        UINT32 tmp = 0;
        for (int j = 0; j < 32; j++)
        {
            tmp <<= 1;
            tmp += (int)data[32 * i + j];
        }
        res[i] = tmp;
    }
    return res;
}

UINT32 ConvertBITS(bool* data)
{
    UINT32 res = 0;
    for (int j = 0; j < 32; j++)
    {
        res <<= 1;
        res += (int)data[j];
    }
    return res;
}

bool* UINT32toBITS(UINT32 data)
{
    bool* bits = new bool[32];
    for (int i = 0; i < 32; i++)
    {
        bits[31 - i] = data % 2;
        data >>= 1;
    }
    return bits;
}

bool* UINT32toBITS(UINT32 dt1, UINT32 dt2)
{
    bool* bits = new bool[64];
    for (int i = 31; i >= 0; i--)
    {
        bits[i] = dt1 % 2;
        dt1 >>= 1;
    }
    for (int i = 63; i >= 32; i--)
    {
        bits[i] = dt2 % 2;
        dt2 >>= 1;
    }
    return bits;
}

bool* ShiftPerm(bool* data)
{
    bool* res = new bool[64];
    for (int i = 0; i < 64; i++)
    {
        res[i] = data[InitialPermutation[i] - 1];
    }
    return res;
}

bool* InvShiftPerm(bool* data)
{
    bool* res = new bool[64];
    for (int i = 0; i < 64; i++)
    {
        res[i] = data[InvInitialPermutation[i] - 1];
    }
    return res;
}

bool* ExpansionPBox(bool* data)
{
    bool* res = new bool[48];
    for (int i = 0; i < 48; i++)
    {
        res[i] = data[PBox[i] - 1];
    }
    return res;
}

bool* XOR(bool* A, bool* B, int sz)
{
    bool* res = new bool[sz];
    for (int i = 0; i < sz; i++)
    {
        res[i] = (int)A[i] ^ (int)B[i];
    }
    return res;
}

bool* СompressionSBox(bool* data)
{
    bool* res = new bool[32];

    for (int n = 0; n < 8; n++)
    {
        UINT8 m = 2 * (int)data[6 * n] + (int)data[6 * n + 5];
        UINT8 l = (int)data[6 * n + 1] * 8 + (int)data[6 * n + 2] * 4 + (int)data[6 * n + 3] * 2 + (int)data[6 * n + 4];
        UINT8 num = SBox[n][m][l];
        for (int i = 0; i < 4; i++)
        {
            res[4 * n + i] = num % 2;
            num >>= 1;
        }
    }

    return res;
}

bool* GenerateKey(int sid)
{
    bool* key = new bool[64];

    srand(sid);

    for (int n = 0; n < 8; n++)
    {
        int control = 0;
        for (int i = 0; i < 7; i++)
        {
            key[8 * n + i] = (rand() % 2);
            control += (int)key[8 * n + i];
        }
        key[8 * n + 7] = !(control % 2);
    }
    return key;
}

bool* CompressionKey(bool* data)
{
    bool* res = new bool[56];
    for (int i = 0; i < 56; i++)
    {
        res[i] = data[KeyTransposition[i]];
    }
    return res;
}

bool* CicklTrans(bool* data, int rnd)
{
    bool* res = new bool[56];
    UINT8 shift = LeftCiklTrans[rnd];
    for (int i = 0; i < 28; i++)
    {
        res[i] = data[((i + shift) % 28)];
    }
    for (int i = 0; i < 28; i++)
    {
        res[i + 28] = data[28 + ((i + shift) % 28)];
    }
    return res;
}

bool* GetRoundKey(bool* data)
{
    bool* res = new bool[48];
    for (int i = 0; i < 48; i++)
    {
        res[i] = data[RoundCompression[i]];
    }
    return res;
}



int main()
{
    cout << hex;
    cout << "OpenText:" << endl;
    BYTE* OpenText = new BYTE[8];
    OpenText[0] = 0x12; OpenText[1] = 0x34; OpenText[2] = 0x56; OpenText[3] = 0xab;
    OpenText[4] = 0xcd; OpenText[5] = 0x13; OpenText[6] = 0x25; OpenText[7] = 0x36;
    Print(OpenText);

    cout << "BYTES to BITS:" << endl;
    bool* bits = BYTEStoBITS(OpenText);
    Print(bits, 64);

    cout << "Initial Permutation:" << endl;
    bits = ShiftPerm(bits);
    Print(bits, 64);

    cout << "OpenText to UNT32 Left and Ridht:" << endl;
    UINT32* uintText = BITStoUINT32(bits);
    cout << uintText[0] << " " << uintText[1] << endl;

    cout << "Key:" << endl;
    bool* Key = GenerateKey(228);
    Print(Key, 64);

    cout << "Compressioned key:" << endl;
    Key = CompressionKey(Key);
    Print(Key, 56);

    //start round
    for (int rnd = 0; rnd < 1; rnd++)
    {
        cout << "Cyclic Shift" << endl;
        Key = CicklTrans(Key, rnd);
        Print(Key, 56);

        cout << "Round Key:" << endl;
        bool* RoundKey = GetRoundKey(Key);
        Print(RoundKey, 48);

        cout << "Ridht binary:" << endl;
        bool* Right = UINT32toBITS(uintText[1]);
        Print(Right, 32);

        cout << "Start of Feistel function:" << endl;

        cout << "Expansion with P-box:" << endl;
        Right = ExpansionPBox(Right);
        Print(Right, 48);

        cout << "xor with key:" << endl;
        Right = XOR(Right, RoundKey, 48);
        Print(Right, 48);

        cout << "Compression with SBox:" << endl;
        Right = СompressionSBox(Right);
        Print(Right, 32);

        cout << "End of Feistel function:" << endl;

        cout << "New Left and Right:" << endl;
        UINT32 tmp = uintText[0];
        uintText[0] = uintText[1];
        bool* Left = UINT32toBITS(tmp);
        Left = XOR(Left, Right, 32);
        uintText[1] = ConvertBITS(Left);
        cout << uintText[0] << " " << uintText[1] << endl;

        cout << endl;
    }
    //end round

    cout << "Connection Left and Right:" << endl;
    bits = UINT32toBITS(uintText[0], uintText[1]);
    Print(bits, 64);

    cout << "Invert Initial Permutation:" << endl;
    bits = InvShiftPerm(bits);
    Print(bits, 64);

    cout << "BITS to BYTES:" << endl;
    BYTE* ClosedText = BITStoBYTES(bits);
    Print(ClosedText);

    cout << endl;
    /////////////////////////////////////////////////////////////////////////////
    cout << "Decryption:" << endl;

    cout << "BYTES to BITS:" << endl;
    bits = BYTEStoBITS(ClosedText);
    Print(bits, 64);

    cout << "Initial Permutation:" << endl;
    bits = ShiftPerm(bits);
    Print(bits, 64);

    cout << "ClosedText to UNT32 Left and Ridht:" << endl;
    uintText = BITStoUINT32(bits);
    cout << uintText[0] << " " << uintText[1] << endl;

    cout << "Round Key:" << endl;
    bool* RoundKey = GetRoundKey(Key);
    Print(RoundKey, 48);

    cout << "Left binary:" << endl;
    bool* Left = UINT32toBITS(uintText[0]);
    Print(Left, 32);

    cout << "Start of Feistel function:" << endl;

    cout << "Expansion with P-box:" << endl;
    Left = ExpansionPBox(Left);
    Print(Left, 48);

    cout << "xor with key:" << endl;
    Left = XOR(Left, RoundKey, 48);
    Print(Left, 48);

    cout << "Compression with SBox:" << endl;
    Left = СompressionSBox(Left);
    Print(Left, 32);

    cout << "End of Feistel function:" << endl;

    cout << "New Left and Right:" << endl;
    UINT32 tmp = uintText[1];
    uintText[1] = uintText[0];
    bool* Right = UINT32toBITS(tmp);
    Right = XOR(Right, Left, 32);
    uintText[0] = ConvertBITS(Right);
    cout << uintText[0] << " " << uintText[1] << endl;

    cout << "Connection Left and Right:" << endl;
    bits = UINT32toBITS(uintText[0], uintText[1]);
    Print(bits, 64);

    cout << "Invert Initial Permutation:" << endl;
    bits = InvShiftPerm(bits);
    Print(bits, 64);

    cout << "BITS to BYTES:" << endl;
    BYTE* DecryptedText = BITStoBYTES(bits);
    Print(DecryptedText);

    cout << endl;


    ///////////////////////////////////////////////////////////////////////////////
    IsEqueal(OpenText, DecryptedText);

    return 0;
}