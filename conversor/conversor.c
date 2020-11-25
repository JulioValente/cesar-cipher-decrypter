#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

int converter(char *str){
    char *p;
    for(p=str;*p!='\0';p++){
        if(*p >= 'A' && *p <= 'z'){
            *p = toupper(*p);
        }else if((*p >= 'À' && *p <= 'Æ') || ((*p-0x20) >= 'À' && (*p-0x20) <= 'Æ')){
            *p='A';
        }else if((*p >= 'È' && *p <= 'Ë') || ((*p-0x20) >= 'È' && (*p-0x20) <= 'Ë')){
            *p='E';
        }else if((*p >= 'Ì' && *p <= 'Ï') || ((*p-0x20) >= 'Ì' && (*p-0x20) <= 'Ï')){
            *p='I';
        }else if((*p >= 'Ò' && *p <= 'Ö') || ((*p-0x20) >= 'Ò' && (*p-0x20) <= 'Ö')){
            *p='O';
        }else if((*p >= 'Ù' && *p <= 'Ü') || ((*p-0x20) >= 'Ù' && (*p-0x20) <= 'Ü')){
            *p='U';
        }else if((*p == 'Ç') || ((*p-0x20) == 'Ç')){
            *p='C';
        }else{
            return 0;
        }
    }

    return 1;
}

int main(){
    //salva a codepage atual
    int outputCodePage = GetConsoleOutputCP();
    int inputCodePage = GetConsoleCP();

    //seta a codepage da língua portuguesa
    SetConsoleCP(1252);
    SetConsoleOutputCP(1252);

    FILE *arquivo;
    FILE *arquivo2;
    int spc=1;
    int nCaractere=0;
    int nPalavra=0;
    int maior = 0;

    arquivo = fopen("palavras.txt", "r");
    arquivo2 = fopen("banco de dados.txt", "w+t");

    if(arquivo == NULL){
        printf("Erro ao abrir o arquivo.");
        getch();
        return 1;
    }

    char c=fgetc(arquivo);
    char string[50];

    while(c!=EOF){
        string[nCaractere] = c;

        if(c==' ' || c=='\n' || c=='\0'){
            string[nCaractere] = '\0';
            if(nCaractere > 2 && converter(string)){
                fprintf(arquivo2, "%s\n", string);
            }
            spc=1;
            if(nCaractere>maior){
                maior = nCaractere;
            }
            nCaractere=-1;
        }else if(spc){
            nPalavra++;
            spc=0;
        }

        c=fgetc(arquivo);
        nCaractere++;
    }

    if(fclose(arquivo)==EOF){
        printf("Erro ao fechar o arquivo.");
        getch();
        return 1;
    }

    if(fclose(arquivo2)==EOF){
        printf("Erro ao fechar o arquivo.");
        getch();
        return 1;
    }

    printf("Número de palavras: %d\n\nMaior número de caracteres em uma palavra:%d", nPalavra, maior);

    while(!GetAsyncKeyState(VK_ESCAPE)){}

    //retorna a antiga codepage
    SetConsoleOutputCP(outputCodePage);
    SetConsoleCP(inputCodePage);

    return 0;
}
