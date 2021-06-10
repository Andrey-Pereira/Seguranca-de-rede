/*
    Segurança de Rede
    Tarefa 1. Implementar RC4

 Tarefa realizada no software Code::Blocks, cuja linguagem de progração implementada foi C++

 RC4 gera um fluxo pseudo-aleatório de bits (um fluxo de chaves ).
 Como acontece com qualquer cifra de fluxo, eles podem ser usados ​​para criptografia combinando-o com o texto simples usando bit-wise exclusive-or.
 A descriptografia é realizada da mesma maneira (uma vez que exclusive-or com dados fornecidos é uma involução).
 Para gerar o fluxo de chaves, a cifra usa um estado interno secreto que consiste em duas partes:
    - Uma permutação de todos os 256 bytes possíveis (denotado como "S" abaixo).
    - Dois ponteiros de índice de 8 bits (denotados "i" e "j").
A permutação é inicializada com uma chave de comprimento variável , normalmente entre 40 e 2048 bits, usando o algoritmo de escalonamento de chave (KSA).
Depois de concluído, o fluxo de bits é gerado usando o algoritmo de geração pseudo-aleatória (PRGA).

*/

#include<stdio.h>
#include<random>
#include<time.h>
#include<string.h>
#define MAX 65534

int S[256];         //Vetor S
char T[256];        //Vetor T
int Key[256];       //Chave aleatória
int KeyStream[MAX]; //Chave
char PlainText[MAX];
char CryptoText[MAX];
const char *WordList = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";

void init_S()   //Iniciar S
{
    for(int i = 0; i < 256; i++){
        S[i] = i;
    }
}

void init_Key() // Chave inicial
{
    int index;
    srand(time(NULL));                                      //Gerar valores aleatórios
    int keylen = int(double(rand())/double(RAND_MAX)*256);  //Comprimento aleatório da chave
    for(int i = 0; i < keylen; i++){
        index = int(double(rand())/double(RAND_MAX)*63);    //Chave "array"
        Key[i] = WordList[index];
    }
    int d;
    for(int i = 0; i < 256; i++){   //Inicia T[]
        T[i] = Key[i%keylen];
    }


}

void  permute_S() //Substituir S
{
    int temp;
    int j = 0;
    for(int i = 0; i < 256; i++){
        j = (j + S[i] + T[i]) % 256;
        temp = S[i];
        S[i] = S[j];
        S[j] = temp;
    }
}

void create_key_stream(char *text, int textLength) //Fluxo de chave
{
    int i,j;
    int temp, t, k;
    int index = 0;
    i = j = 0;
    while(textLength --){   //Gerar fluxo de caixa
        i = (i+1)%256;
        j = (j + S[i]) % 256;
        temp = S[i];
        S[i] = S[j];
        S[j] = temp;
        t = (S[i] + S[j]) % 256;
        KeyStream[index] = S[t];
        index ++;
    }

}


 void Rc4EncryptText(char *text)        //Codificação e decodificação
{
    int textLength = strlen(text);
    init_S();
    init_Key();
    permute_S();
    create_key_stream(text, textLength);
    int plain_word;
    printf("Texto codificado:");
    for(int i = 0; i < textLength; i++){
        CryptoText[i] = char(KeyStream[i] ^ text[i]); //Codificação
    }
    for(int i = 0; i < textLength; i++){
        printf("%c", CryptoText[i]);
    }
    printf("\nTexto decodificado:");
    for(int i = 0; i < textLength; i++){
        PlainText[i] = char(KeyStream[i] ^ CryptoText[i]);   //Decodificação
    }
    for(int i = 0; i < textLength; i++){
        printf("%c", PlainText[i]);
    }

}
int main()
{
    char text[] = "Tarefa 1. Implementar RC4"; //Texto para criptografar
    Rc4EncryptText(text);
    return 0;
}
