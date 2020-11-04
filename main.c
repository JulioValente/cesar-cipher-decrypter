#include <stdlib.h>
#include <stdio.h>
#include <locale.h>
#include <string.h>

void nl(int y){  //função para novas linhas.
    for(int i=0;i<y;i++){
        printf("\n");
    }
}

void tabul (int t){ //função para tabulações.
	int i;

	for(i=0; i<t; i++){
		printf("\t");
	}
}

void cabecalho (){ //função do cabeçalho.
	printf("*================================================================================================================*");
	printf("\n\t\t\t\tdecodificador");
	printf("\n*================================================================================================================*");
	printf("\n\n");

	printf(" ->");
	tabul(3);
	printf("decodifica uma mensagem recebida por um arquivo de mensagem");
	nl(2);

	printf(" ->");
	tabul(3);
	printf("não pode ser escrito com caracteres especiais");
	nl(3);
}

void rodaMensagem(char *mensagem, int tamanho, int numRotacoes){ //função para deslocar os caracteres da mensagem.
    int i;
    for(i=0; i<tamanho;i++){
        mensagem[i] = ((mensagem[i]-'A')+numRotacoes)%26 + 'A';
    }
}

void rodaMensagemAntHorario(char *mensagem, int tamanho, int numRotacoes){ //função para deslocar os caracteres da mensagem.
	int i;

	while(numRotacoes < 0){
		numRotacoes+=26;
	}

    for(i=0; i<tamanho;i++){
        mensagem[i] =  ((mensagem[i]-'A')+(26-numRotacoes))%26 + 'A';
    }
}

int verificaMensagem(char *mensagem, int palavraTamanho, int contMax){
	FILE *arquivo;
	char palavra[50];
	int tamanho;

    if(contMax > 0){
        arquivo = fopen("banco de dados.txt", "r");

        while(fgets(palavra, 50, arquivo) != NULL){
            tamanho = 0;

            char *p;
            for(p = palavra;*(p)!='\0' && *(p)!='\n';p++){
                tamanho++;
            }

            palavra[tamanho] = '\0';

            if(tamanho <= palavraTamanho && !strncmp(palavra, mensagem, tamanho)){

                if(tamanho < palavraTamanho){ //mais de 1 palavra
                    if(verificaMensagem((mensagem + tamanho), palavraTamanho - tamanho, contMax-1)){
                        fclose(arquivo);
                        return 1;
                    }
                }else{ //somente uma palavra
                    fclose(arquivo);
                    return 1;
                }

            }
        }

        fclose(arquivo);
        return 0;
    }else{
        return 0;
    }
}

int decifraMensagem(char *mensagem, int tamanho, int nPalavras){ //decifra a mensagem automaticamente com o parâmetro de número máximo de palavras.
    int i;
    for(i=1;i<26;i++){
        rodaMensagem(mensagem, tamanho, 1);

        if(verificaMensagem(mensagem, tamanho, nPalavras)){
            return 1;
        }
    }

    mensagem[0] = '\0';

    return 0;
}

char menu(){
	system("cls");

	cabecalho();
	/**/
	printf(" opções:");
	nl(1);
	printf(" ====//====//====//====");
	nl(2);
	printf(" 1. decodificação pelo usuário");
	nl(2);
	printf(" 2. decodificação automática");
	nl(2);
	printf(" 3. sair do programa");
	nl(2);
	printf(" Digite uma opção: ");
	/*digitando uma opção*/

	return getch();

}

int main(){
    FILE *arquivo;
    char nomeArquivo[30];
    char temp[30];
    char mensagem[100];
    int mensagemTamanho;
    int palavrasMax;
    char c;
	int rot=0;

    setlocale(LC_ALL, "");

    /*rodando o programa*/
    while(1){
    	switch(menu()){
    		case '1': 	system("cls");
						printf("Digite o nome do arquivo: ");
					    nl(2);
						scanf("%s", nomeArquivo);

						strcpy(temp, nomeArquivo); //copia o nome do arquivo para uma variável temporária.
					    strcat(temp, ".txt"); //adiciona o formato do arquivo.
					    arquivo = fopen(temp, "r");

					    if(arquivo == NULL){ //verifica se o arquivo foi aberto.
					        nl(1);
					        printf("Não foi possível abrir o arquivo.");
					        nl(2);
					        printf("Digite qualquer tecla para continuar.");
					        getch();
					        return 1;
					    }


					    /*armazena a mensagem do arquivo*/

					    c = toupper(fgetc(arquivo));
					    mensagemTamanho=0;
					    while(c!=EOF){
					        if(c >= 'A' && c <= 'Z'){
					            mensagem[mensagemTamanho] = toupper(c);
					            mensagemTamanho++;
					        }
					        c=fgetc(arquivo);
					    }
					    mensagem[mensagemTamanho] = '\0';

					    /**/

					    if(fclose(arquivo) == EOF){ //verifica se o arquivo foi fechado.
					        nl(2);
					        printf("Não foi possível fechar o arquivo.");
					        nl(2);
					        printf("Digite qualquer tecla para continuar.");
					        getch();
					        return 1;
					    }

						system("cls");
					    printf("Digite a chave da mensagem: ");
					    scanf("%d", &rot);

					    //decodifica a mensagem
					    rodaMensagemAntHorario(mensagem, mensagemTamanho, rot);

						/*salvando a mensagem*/
					    strcat(nomeArquivo, "_dec.txt"); //adiciona o formato do arquivo.
					    arquivo = fopen(nomeArquivo, "w+t");

					    if(arquivo == NULL){ //verifica se o arquivo foi criado.
					        nl(1);
					        printf("Não foi possível abrir o arquivo.");
					        nl(2);
					        printf("Digite qualquer tecla para continuar.");
					        getch();
					        return 1;
					    }

					    fprintf(arquivo, "Mensagem decodificada: %s", mensagem);

					    if(fclose(arquivo) == EOF){ //verifica se o arquivo foi fechado.
					        nl(2);
					        printf("Não foi possível fechar o arquivo.");
					        nl(2);
					        printf("Digite qualquer tecla para continuar.");
					        getch();
					        return 1;
					    }


					    nl(1);
					    printf("Operação concluída com sucesso.");

					    /**/

					    nl(2);
					    printf("Digite qualquer tecla para continuar.");
					    getch();
    			break;

    		case '2': 	system("cls");
						printf("Digite o nome do arquivo: ");
					    nl(2);
						scanf("%s", nomeArquivo);

                        nl(1);
						printf("Digite o número máximo de palavras: ");
					    nl(2);
						scanf("%d", &palavrasMax);

						strcpy(temp, nomeArquivo); //copia o nome do arquivo para uma variável temporária.
					    strcat(temp, ".txt"); //adiciona o formato do arquivo.
					    arquivo = fopen(temp, "r");

					    if(arquivo == NULL){ //verifica se o arquivo foi aberto.
					        nl(1);
					        printf("Não foi possível abrir o arquivo.");
					        nl(2);
					        printf("Digite qualquer tecla para continuar.");
					        getch();
					        return 1;
					    }


					    /*armazena a mensagem do arquivo*/

					    c = fgetc(arquivo);
					    mensagemTamanho=0;
					    while(c!=EOF){
					        if(c >= 'A' && c <= 'z'){
					            mensagem[mensagemTamanho] = toupper(c);
					            mensagemTamanho++;
					        }
					        c=fgetc(arquivo);
					    }
					    mensagem[mensagemTamanho] = '\0';

					    /**/

					    if(fclose(arquivo) == EOF){ //verifica se o arquivo foi fechado.
					        nl(2);
					        printf("Não foi possível fechar o arquivo.");
					        nl(2);
					        printf("Digite qualquer tecla para continuar.");
					        getch();
					        return 1;
					    }

						/*salvando a mensagem*/
					    strcat(nomeArquivo, "_dec.txt"); //adiciona o formato do arquivo.
					    arquivo = fopen(nomeArquivo, "w+t");

					    if(arquivo == NULL){ //verifica se o arquivo foi criado.
					        nl(1);
					        printf("Não foi possível abrir o arquivo.");
					        nl(2);
					        printf("Digite qualquer tecla para continuar.");
					        getch();
					        return 1;
					    }

                        nl(1);
                        printf("Decodificando...");

					   	rodaMensagemAntHorario(mensagem, mensagemTamanho, 3); //primeira possível decodificação
					    fprintf(arquivo, "Primeira possível mensagem: %s", mensagem);

					    decifraMensagem(mensagem, mensagemTamanho, palavrasMax); //segunda possível decodificação
					    fprintf(arquivo, "\n\nSegunda possível mensagem: %s", mensagem);

					   	decifraMensagem(mensagem, mensagemTamanho, palavrasMax); //terceira possível decodificação
					    fprintf(arquivo, "\n\nTerceira possível mensagem: %s", mensagem);

					    if(fclose(arquivo) == EOF){ //verifica se o arquivo foi fechado.
					        nl(2);
					        printf("Não foi possível fechar o arquivo.");
					        nl(2);
					        printf("Digite qualquer tecla para continuar.");
					        getch();
					        return 1;
					    }


					    nl(2);
					    printf("Operação concluída com sucesso.");

					    /**/

					    nl(2);
					    printf("Digite qualquer tecla para continuar.");
					    getch();
    			break;

    		case '3': return 0;

    		default: nl(2);
				   	 printf(" opção inválida");
					 getch();
		}
	}
	/**/

    //fim do programa.
    nl(2);
    printf("Digite qualquer tecla para continuar.");
    getch();

	return 0;
}
