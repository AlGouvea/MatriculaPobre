#include <locale.h>
#include <stdio.h>
#include <string.h>
#include <windows.h>

#define TAM_MAX 256

// Declaracoes:
//---------------------------------------------------------//
//Variaveis globais
struct Alunos {
    int total;
    int ASS;
    int AMS;
    int AMM;
    int AMI;
    int AII;
    int ASR;
    int AT;
}Turma;

int opcao_escolhida;

char Busca[TAM_MAX];

//---------------------------------------------------------//
// Funcoes essenciais do menu

void menu();

void cadastrardisc();

void cadastrarTurma();

void deletarDisc();

void deletarTurma();

void updateturma();

void relatorioDisc();

void relatorioGeral();

void nomecodigo();

void lista();

void resetsystem();

//---------------------------------------------------------//
// Funções complementares

void creditos();

void bloq_tecla();

void error();

void pesquisaparte(char nome[]);

int checkcod(char cod[]);

int checkturma(char codigoturma[]);

//---------------------------------------------------------//
// Principal:
//---------------------------------------------------------//
 main() {
	printf("Bem Vindo ao MatriculaPobre.com!\n");
	menu();

	return 0;
}
//---------------------------------------------------------//
// Funcao do Menu de opcoes:
//---------------------------------------------------------//
void menu() {
	setlocale(LC_ALL, "Portuguese");

	// Declarações
	FILE *Geral;
	//Arquvis de informacoes essenciais (relatorio geral, Disciplinas, etc...);

	Geral = fopen("C:\\APC\\geral\\Disciplinas.txt", "r");
	fclose(Geral);
	if (Geral == NULL) {
		mkdir("C:\\APC");
		mkdir("C:\\APC\\geral");
        Geral = fopen("C:\\APC\\geral\\Disciplinas.txt", "w");
		fclose(Geral);
	}
	//Menu

	printf("Menu de opcoes:\n");
	printf("--------------------------------------------------------\n");
    printf("(0) Cadastrar Disciplina                               |\n");
    printf("(1) Cadastrar Turma                                    |\n");
    printf("(2) Excluir Disciplina                                 |\n");
    printf("(3) Excluir Turma                                      |\n");
    printf("(4) Atualizar Turma                                    |\n");
    printf("(5) Gerar relatório por disciplina                     |\n");
    printf("(6) Gerar relatório geral                              |\n");
    printf("(7) Relação nome-código                                |\n");
    printf("(8) Lista de Disciplinas cadastradas                   |\n");
    printf("(9) Sair do programa                                   |\n");
    printf("(10) Reset System                                      |\n");
    printf("--------------------------------------------------------\n");

    fflush(stdin);
	bloq_tecla(0, 11);
    //Menu de opcoes
	switch (opcao_escolhida) {
	case 0:
		system("cls");
		printf("Cadastrar Disciplina:\n");
		printf("-----------------\n\n");
		cadastrardisc();
		break;
	case 1:
		system("cls");
		printf("Cadastrar turma:\n");
		printf("-----------------\n\n");
		cadastrarTurma();
		break;
	case 2:
		system("cls");
		printf("Deletar Disciplina:\n");
		printf("-----------------\n\n");
		deletarDisc();
		break;
	case 3:
		system("cls");
		printf("Deletar Turma: \n");
		printf("-----------------\n\n");
		deletarTurma();
		break;
    case 4:
        system("cls");
        printf("Atualizar Turma: \n");
		printf("-----------------\n\n");
		updateturma();
    break;
	case 5:
		system("cls");
		printf("Relatório Por Disciplina:\n");
		printf("-----------------\n\n");
		relatorioDisc();
		break;
	case 6:
		system("cls");
		printf("Relatório Geral Da Universidade:\n");
		printf("-----------------\n\n");
		relatorioGeral();
		break;
	case 7:
		system("cls");
		printf("Relação Nome-código:\n");
		printf("-----------------\n\n");
		nomecodigo();
    case 8:
        system("cls");
        printf("Lista de Disciplinas cadastradas:\n");
        printf("-----------------\n");
        lista();
        break;
	case 9:
		system("cls");
		printf("Obrigado por utilizar MatriculaPobre.com!");
		exit("0");
		break;
    case 10:
        resetsystem();
    break;
    case 11:
        system("cls");
        printf("Creditos do Programa:\n");
        printf("-----------------\n\n");
        creditos();
        break;

	}
}
//---------------------------------------------------------//
// Funcao de cadastro de disciplina:
//---------------------------------------------------------//
void cadastrardisc() {
	//Declaeacoes
	char nome[TAM_MAX], diretorio_1[TAM_MAX], diretorio_2[TAM_MAX], Percent_Disc[TAM_MAX], disc[TAM_MAX], cod[TAM_MAX], Linha[TAM_MAX], codigo_arq[TAM_MAX];
	int opc, i, J, indicador;
	FILE *disciplina;
	//Principal

	printf("Informe o nome da disciplina: ");
	fflush(stdin);
	gets(disc);

	//check para nome vazio
	if(disc[0] == '\0'){
        system("cls");
        printf("Favor inserir um nome válido para a disciplina!\n");
        menu();
	}
	//colocar em maiusculo
    for(i = 0; i < TAM_MAX; i++){
        disc[i] = toupper(disc[i]);
    }

	printf("Informe o código da disciplina: ");
	fflush(stdin);
	gets(cod);
	//mesmo para o codigo
    if(cod[0] == '\0'){
        system("cls");
        printf("Favor inserir um código válido para a disciplina!\n");
        menu();
	}
    for(i = 0; i < TAM_MAX; i++){
        cod[i] = toupper(cod[i]);
    }
    //check de nome = codigo
	switch(strcmp(disc, cod)){
        case 0:
            system("cls");
            printf("Nao se pode cadastrar esse codigo!\n");
            menu();
        break;
    }
    //funcao que confere existencia do codigo
    if(checkcod(cod) == 1){
            system("cls");
            printf("Esse código já foi cadastrado!\n");
            menu();
    }


	// Definição de diretórios e arquivos
	snprintf(nome, TAM_MAX, "C:\\APC\\%s.txt", disc);

	disciplina = fopen(nome, "r");
	fclose(disciplina);
	if (disciplina != NULL) {
		system("cls");
		printf("Essa disciplina ja possui um cadastro!\n");
		menu();
	} else {
		//Organizacao dos arquivos
		disciplina = fopen(nome, "w");
            fprintf(disciplina, "Disciplina: %s\n", disc);
		fclose(disciplina);

		disciplina = fopen("C:\\APC\\geral\\Disciplinas.txt", "a");
            fprintf(disciplina, "%s|%s|\n", disc, cod);
		fclose(disciplina);

		// Confirmacao de sucesso da funcao
		if (disciplina != NULL) {
			printf("\nDisciplina cadastrada com Sucesso!\n");
            Beep(900, 500);
            Beep(1250, 300);

			//Saida da funcao
			printf("-----------------\n\n");
			printf("Deseja retornar ao menu?\n1)Sim    2)Nao\n");
			bloq_tecla(1, 2);
			switch (opcao_escolhida) {
			case 1:
				system("cls");
				menu();
				break;
			case 2:
				system("cls");
				printf("Obrigado por utilizar MatriculaPobre.com!");
				exit("0");
				break;
			}
		} else {
			system("cls");
			printf("Ocorreu um erro no cadastramento da disciplina.\n");
			menu();
		}
	}
}
//---------------------------------------------------------//
// Funcao de cadastrar turma:
//---------------------------------------------------------//
void cadastrarTurma() {
	//Declarações
	char nomeArquivo[TAM_MAX], nome[TAM_MAX], cod[TAM_MAX];
	int ano, seme, i, inf[12];
	FILE *disciplina;
	FILE *codigo;

	//Principal
	printf("Informe o Código/Nome da disciplina: ");
	fflush(stdin);
	gets(nome);
	pesquisaparte(nome);

	// Concatenação do Arquivo para busca de informações
	snprintf(nomeArquivo, TAM_MAX, "C:\\APC\\%s.txt", Busca);
	disciplina = fopen(nomeArquivo, "r");
	fclose(disciplina);

	//Check de existencia da disciplina
	if (disciplina != NULL) {

		//Informacoes da turma e check de validade
		printf("Informe o código da turma: ");
		fflush(stdin);
		gets(cod);

		//checks de nome vazio e colocar em maiusculo
        if(cod[0] == '\0'){
        system("cls");
        printf("Favor inserir um código válido para a turma!\n");
        menu();
        }
        for(i = 0; i < TAM_MAX; i++){
            cod[i] = toupper(cod[i]);
        }
        Turma.total = 0;
		system("cls");
		printf("Cadastro de Turma: \n");
		printf("-----------------\n\n");
		printf("Disciplina: %s\n", Busca);
		printf("Código da Turma: %s\n", cod);
		printf("Informe o ano da turma: ");
		bloq_tecla(1, 3020);
		ano = opcao_escolhida;
		printf("\nSemestre: ");
		bloq_tecla(1, 2);
		seme = opcao_escolhida;
		printf("º\n");
		snprintf(cod, TAM_MAX, "%s%d%d", cod, ano, seme);
		//leitura de informacoes da turma (quantidades de alunos etc)
            if(checkturma(cod) == 1){
                system("cls");
                printf("Essa turma ja foi cadastrada!\n");
                system("pause");
                menu();
            }
            printf("Alunos que trancaram: ");
            bloq_tecla(0, 10000);
            Turma.AT = opcao_escolhida;
            printf("\nAlunos com rendimento SS: ");
            bloq_tecla(0, 10000);
            Turma.ASS = opcao_escolhida;
            printf("\nAlunos com rendimento MS: ");
            bloq_tecla(0, 10000);
            Turma.AMS = opcao_escolhida;
            printf("\nAlunos com rendimento MM: ");
            bloq_tecla(0, 10000);
            Turma.AMM = opcao_escolhida;
            printf("\nAlunos com rendimento MI: ");
            bloq_tecla(0, 10000);
            Turma.AMI = opcao_escolhida;
            printf("\nAlunos com rendimento II: ");
            bloq_tecla(0, 10000);
            Turma.AII = opcao_escolhida;
            printf("\nAlunos sem rendimento (SR): ");
            bloq_tecla(0, 10000);
            Turma.ASR = opcao_escolhida;

            Turma.total = Turma.AII + Turma.AMI + Turma.AMM + Turma.AMS + Turma.ASR + Turma.ASS + Turma.AT;
            printf("\nTotal de alunos: %d\n", Turma.total);

            if(Turma.total == 0){
                system("cls");
                printf("Não é possível cadastrar uma turma sem alunos!\n");
                menu();
            }


            //Atualizacao de arquivos
            disciplina = fopen(nomeArquivo, "a");
                fprintf(disciplina, "%s|\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n", cod, Turma.AT, Turma.total, Turma.ASS, Turma.AMS, Turma.AMM, Turma.AMI, Turma.AII, Turma.ASR);
            fclose(disciplina);

            //saida da funcao
            system("pause");
            printf("Turma cadastrada com sucesso!\n");
            Beep(900, 500);
            Beep(1250, 300);
            printf("\n-----------------\n\n");
            printf("Deseja retornar ao menu principal?\n1)Sim 2)Nao\n");
            bloq_tecla(1, 2);
            switch (opcao_escolhida) {
                case 1:
                system("cls");
                menu();
                break;
                case 2:
                system("cls");
                printf("Obrigado por utilizar MatriculaPobre.com!");
                exit("0");
                break;

        }
}
}
//---------------------------------------------------------//
// Funcao para deletar disciplina:
//---------------------------------------------------------//
void deletarDisc() {

	//Declaracoes
	char nomeArquivo[TAM_MAX], linha[TAM_MAX], nome[TAM_MAX];
	int opcao, del1, i, ctr = 0, lno = 0;
	FILE *arquivos, *temp;

	//Principal
	printf("Código/Sigla da disciplina desejada: ");
	fflush(stdin);
	gets(nome);
    pesquisaparte(nome);

	//Concatenacao dos nomes dos arquivos
	snprintf(nomeArquivo, TAM_MAX, "C:\\APC\\%s.txt", Busca);

	//Exclusao de arquivos
	printf("Deseja realmente excluir a disciplina de %s?\n1)Sim    2)Nao\n", Busca);
        bloq_tecla(1, 2);
	switch (opcao_escolhida) {
	case 1:

        //Atualizacao de arquivos
        arquivos = fopen("C:\\APC\\geral\\Disciplinas.txt", "r");
        temp = fopen("C:\\APC\\temp.txt", "w");

        while (!feof(arquivos)){
            strcpy(linha, "\0");
            fgets(linha, TAM_MAX, arquivos);
                ctr++;
                if(strstr(linha, Busca) != 0){
                    lno = ctr;
                }
                if(ctr != lno){
                    fprintf(temp, "%s", linha);
                }
        }
        fclose(arquivos);
        fclose(temp);
        arquivos = fopen("C:\\APC\\geral\\Disciplinas.txt", "w");
        temp = fopen("C:\\APC\\temp.txt", "r");
        while(!feof(temp)){
            fgets(linha, TAM_MAX, temp);
            if(!feof(temp)){
            fprintf(arquivos, "%s", linha);
            }
        }
        fclose(arquivos);
        fclose(temp);
        remove("C:\\APC\\temp.txt");

		printf("\n");
		system("pause");

        //Exclusao de arquivos
		del1 = remove(nomeArquivo);

		if (del1 == 0) {
			printf("\n-----------------\n\n");
			printf("Disciplina excluída com sucesso!\n");
            Beep(900, 500);
            Beep(1250, 300);
			printf("Deseja retornar ao menu?\n1)Sim    2) Nao\n");
			bloq_tecla(1, 2);
			switch (opcao_escolhida) {
			case 1:
				system("cls");
				menu();
				break;
			case 2:
				system("cls");
				printf("Obrigado por usar o MatriculaPobre.com!\n");
				exit("0");
				break;
			}
		} else {
			system("cls");
			printf("Ocorreu um erro na exclusao da disciplina!\n");
			menu();
		}
		break;
	case 2:
		system("cls");
		menu();
		break;
	}
}
//---------------------------------------------------------//
// Funcao para deletar turma:
//---------------------------------------------------------//
void deletarTurma() {
	// Declarações
	int lno = 0, ctr = 0, i = 0, ano, seme;
	float inf[12], relatorio[12], percent[14], aprova;
	char nome[TAM_MAX], nome_arq[TAM_MAX], codigo[TAM_MAX], dir_per_1[TAM_MAX];
	char str[TAM_MAX], temp[] = "temp.txt";
    FILE *arq_OG, *arq_Copy, *arquivo;

	// PRINCIPAL
	printf("Código/Nome da disciplina: ");
	fflush(stdin);
	gets(nome);
	pesquisaparte(nome);

        snprintf(nome_arq, TAM_MAX, "C:\\APC\\%s.txt", Busca);

		printf("Codigo da turma: ");
		fflush(stdin);
		gets(codigo);
		for(i = 0; i < TAM_MAX; i++){
            codigo[i] = toupper(codigo[i]);
		}
		printf("Informe o ano da Turma: ");
		bloq_tecla(1, 3020);
		printf("\n");
		ano = opcao_escolhida;
		printf("Informe o semestre da Turma: ");
		bloq_tecla(1, 2);
		printf("\n");
		seme = opcao_escolhida;

		printf("Deseja realmente excluir a turma %s da disciplina %s?\n1)Sim    2)Nao\n", codigo, Busca);
		snprintf(codigo, TAM_MAX, "%s%d%d", codigo, ano, seme);

		bloq_tecla(1, 2);
		switch(opcao_escolhida){
            case 1:
                goto continua;
            break;
            case 2:
                system("cls");
                menu();
            break;
		}

    continua:

	if(checkturma(codigo) == 0){
        system("cls");
        printf("Essa turma nao foi cadastrada!\n");
        system("pause");
        menu();
    }
		// Copiar todas as informações do arquivo exceto o desejado
		arq_OG = fopen(nome_arq, "r");//abrir o arquivo original
		arq_Copy = fopen(temp, "w");//abrir um arquivo temporario
		i = 0;
		while (!feof(arq_OG)) {
			strcpy(str, "\0");
			fgets(str, TAM_MAX, arq_OG);
			if (!feof(arq_OG)) {
				ctr++;
				if (strstr(str, codigo) != 0) {
					lno = ctr;
				}
				// Pular as linhas desejadas
				if (lno != 0) {
					if (ctr < lno || ctr > (lno + 8)) {
						fprintf(arq_Copy, "%s", str);
					} else {
						fscanf(arq_OG, "%f", &inf[i]);
						i++;
					}

				} else {
					fprintf(arq_Copy, "%s", str);
				}
			}
		}
		fclose(arq_OG);
		fclose(arq_Copy);
		//Reabrir arquivos e realocar do temporario para o original
        arq_OG = fopen(nome_arq, "w");
		arq_Copy = fopen(temp, "r");
		do{
            fgets(str, TAM_MAX, arq_Copy);
            fprintf(arq_OG, "%s", str);
		}while(!feof(arq_Copy));
        fclose(arq_Copy);
        fclose(arq_OG);
        remove(temp);

        printf("\n");
        system("pause");
        printf("Turma excluída com sucesso!\n");
        Beep(900, 500);
        Beep(1250, 300);
        printf("\n-----------------\n\n");

        printf("Deseja retornar ao menu principal?\n1)Sim   2)Não\n");

        bloq_tecla(1, 2);
        switch (opcao_escolhida) {
            case 1:
                system("cls");
                menu();
            break;
            case 2:
                system("cls");
                printf("Obrigado por utilizar MatrículaPobre.com!\n");
                exit("0");
            break;
        }
}
//---------------------------------------------------------//
//Funcao para atualizar Turma
//---------------------------------------------------------//
void updateturma(){
    //Declaracoes

    char turma[TAM_MAX], disciplina[TAM_MAX], arquivo[TAM_MAX], Linha[TAM_MAX], percent[TAM_MAX], cod[TAM_MAX];
    int lno = 0, cont_linha = 0, limite = 0, i, cont_turma = 0, ano, seme;
    unsigned int alunos[12];
    FILE *disc, *copia, *relatorios;
    //Pirncipal

    printf("Informe a disciplina da turma: ");
    gets(disciplina);
    pesquisaparte(disciplina);

    snprintf(arquivo, TAM_MAX, "C:\\APC\\%s.txt", Busca);

    disc = fopen(arquivo, "r");
    fclose(disc);

    if(arquivo == NULL){
        system("cls");
        printf("Essa disciplina não existe!\n");
        menu();
    }else{
        printf("Informe o código da turma: ");
        gets(turma);
        for(i = 0; i < TAM_MAX; i++){
            turma[i] = toupper(turma[i]);
            cod[i] = turma[i];
        }
        printf("Informe o ano da Turma: ");
		bloq_tecla(1, 20000);
		printf("\n");
		ano = opcao_escolhida;
		printf("Informe o semestre da Turma: ");
		bloq_tecla(1, 2);
		printf("\n");
		seme = opcao_escolhida;
        system("pause");
        snprintf(turma, TAM_MAX, "%s%d%d", turma, ano, seme);

        if(checkturma(turma) != 1){
            system("cls");
            printf("Essa turma não foi cadastrada!\n");
            menu();
        }else{

            //Obtenção das informações novas
            system("cls");
            printf("Turma: \n");
            printf("-------------------------------------\n");
            printf("Disciplina: %s\n", Busca);
            printf("Código: %s\n", cod);
            printf("-------------------------------------\n");
            printf("Informe a nova organização da Turma: \n");
            printf("-------------------------------------\n");
            alunos[1] = 0;
            printf("Alunos que trancaram: ");
            scanf("%d", &alunos[0]);
            printf("Alunos com rendimento SS: ");
            scanf("%d", &alunos[2]);
            printf("Alunos com rendimento MS: ");
            scanf("%d", &alunos[3]);
            printf("Alunos com rendimento MM: ");
            scanf("%d", &alunos[4]);
            printf("Alunos com rendimento MI: ");
            scanf("%d", &alunos[5]);
            printf("Alunos com rendimento II: ");
            scanf("%d", &alunos[6]);
            printf("Alunos sem rendimento (SR): ");
            scanf("%d", &alunos[7]);
            for(i = 0; i < 8; i++){
                if(i != 1){
                alunos[1] = alunos[1] + alunos[i];
                }
            }
            printf("Total de Alunos: %d\n", alunos[1]);

            cont_turma = 0;
        copia = fopen("Temp.txt", "w");
        disc = fopen(arquivo, "r");
		while (!feof(disc)) {
			strcpy(Linha, "\0");
			fgets(Linha, TAM_MAX, disc);
			if (!feof(disc)) {
				cont_linha++;
				if (strstr(Linha, turma) != 0) {
                    for( i = 0; i < TAM_MAX; i++){
                        if(Linha[i] == '|'){
                            Linha[i] = '\0';
                        }
                    }
                    if(strcmp(Linha, turma) == 0){
					lno = cont_linha-1;
                    }
				}
				// Pular as linhas desejadas
				if (lno != 0) {
					if (cont_linha < lno || cont_linha > (lno + 9)) {
						fprintf(copia, "%s", Linha);
					} else {
					    if(limite == 0){
                        fprintf(copia, "%s|\n", Linha);
                        limite++;
					    }else{
                                fprintf(copia, "%d\n", alunos[cont_turma]);
                                cont_turma++;
					}
					}

				} else {
                    fprintf(copia, "%s", Linha);
				}
			}
		}
		fclose(disc);
		fclose(copia);
		remove(arquivo);		// Remover arquivo original
		rename("Temp.txt", arquivo); // Renomear arquivo temporário

            printf("-------------------------------------\n");
            system("pause");
            printf("Turma atualizada com sucesso!\n");
            Beep(900, 500);
            Beep(1250, 300);
            printf("Deseja retornar ao menu principal?\n1)Sim   2)Não\n");
            bloq_tecla(1, 2);
            switch(opcao_escolhida){
            case 1:
                system("cls");
                menu();
            break;
            case 2:
                printf("\nObrigado por utilizar o MatrículaPobre.com!\n");
                exit("0");
            break;
            }


        }
    }

}
//---------------------------------------------------------//
// Funcao do relatorio por disciplina:
//---------------------------------------------------------//
void relatorioDisc() {
	// Declaracoes
	char nome[TAM_MAX], linha[TAM_MAX];
	float inf[7] = {0,0,0,0,0,0,0};
	int i, cont = 0, lno = 0, aux;
	FILE *Relatorio;
	// Principal
	printf("Código/Nome da disciplina: ");
	fflush(stdin);
	gets(nome);
	pesquisaparte(nome);
    snprintf(nome, TAM_MAX, "C:\\APC\\%s.txt", Busca);
    Relatorio = fopen(nome, "r");
        do{
            fgets(linha, TAM_MAX, Relatorio);
            if(linha[0] == 'T'){
                lno = cont;
                i = 0;
            }
            if(lno != 0){
                if(cont > lno && cont < lno + 7){
                    aux = atoi(linha);
                   inf[i] =  inf[i] + aux;
                   i++;
                   }
            }
            cont++;
        }while(!feof(Relatorio));
    fclose(Relatorio);

	    //Relatorio
		system("cls");
		if(inf[1] != 0){
		printf("Relatório da disciplina %s:\n\n", Busca);
		printf("-----------------\n\n");
		printf("Percentual de evasão: %.02f%%\n", (inf[0] + inf[7]) * 100 / inf[1]);
		printf("Percentual de aprovação: %.02f%%\n",(inf[2] + inf[3] + inf[4]) * 100 / inf[1]);
		printf("Percentual de alunos com SS: %.02f%%\n", inf[2] * 100 / inf[1]);
		printf("Percentual de alunos com MS: %.02f%%\n", inf[3] * 100 / inf[1]);
		printf("Percentual de alunos com MM: %.02f%%\n\n", inf[4] * 100 / inf[1]);
		}
		else{
            printf("Nao existem Turmas cadastradas nessa disciplina!\n");
		}
		printf("-----------------\n\n");
		printf("Deseja retornar ao menu principal?\n1)Sim  2)Nao\n");
		bloq_tecla(1, 2);
		switch (opcao_escolhida) {
            case 1:
                system("cls");
                menu();
                break;
            case 2:
                system("cls");
                printf("Obrigado por utilizar MatriculaPobre.com!");
                exit("0");
			break;
		}
}
//---------------------------------------------------------//
// Funcao do relatorio geral:
//---------------------------------------------------------//
void relatorioGeral() {
	// Declaracoes
	float informacao[12] = {0,0,0,0,0,0,0,0,0,0,0,0}, melhor = 0, pior = 101, turma[8], aprova, T30 = 0, T50 = 0, TM = 0, TT = 0;
	char best[TAM_MAX], worse[TAM_MAX], linha[TAM_MAX], Arq[TAM_MAX], nome[TAM_MAX], string[TAM_MAX];
	int i = 0, cont, soma, auxilia[12], lno = 0;
	FILE *relatorios, *disc;
	// Principal
    relatorios = fopen("C:\\APC\\geral\\Disciplinas.txt", "r");
        do{
            fgets(linha, TAM_MAX, relatorios);
            if(!feof(relatorios)){
                for(i = 0; i < TAM_MAX; i++){
                    if(linha[i] == '|'){//seleciona parte especifica da linha
                        linha[i] = '\0';
                    }
                    nome[i] = linha[i];
                }
                snprintf(Arq, TAM_MAX, "C:\\APC\\%s.txt", linha);//concatena
                disc = fopen(Arq, "r");//abre arquivo da disciplina
                cont = 0;
                do{
                    fgets(string, TAM_MAX, disc);
                    if(string[0] == 'T'){//Procura exustencia de uma turma
                        lno = cont;
                        i = 0;
                    }
                    if(lno != 0){
                    if(cont > lno && cont < lno + 9){//le informacoes da turma para o relatorio
                    soma = atoi(string);
                    auxilia[i] = soma;
                    informacao[i] = informacao[i] + soma;
                    turma[i] = soma;
                    i++;
                    }
                    if(i == 7){
                        aprova = (turma[2] + turma[3] + turma[4])*100/turma[1];
                        if(aprova <= 30){
                            T30++;
                            TT++;
                        }
                        if(aprova > 30 && aprova < 50){
                            T50++;
                            TT++;
                        }
                        if(aprova >= 50){
                            TM++;
                            TT++;
                        }
                    }
                    }
                    cont++;
                }while(!feof(disc));
                fclose(disc);
                //Inicio dos calculos do relatorio
                if(auxilia[1] > -1){
                  auxilia[1] = ((auxilia[2] + auxilia[3] + auxilia[4])*100)/auxilia[1];

                if(auxilia[1] > melhor){
                    for(i = 0; i < TAM_MAX; i++){
                        best[i] = nome[i];
                    }

                    melhor = auxilia[1];
                }
                if(auxilia[1] < pior){
                    for(i = 0; i < TAM_MAX; i++){
                        worse[i] = nome[i];
                    }
                    pior = auxilia[1];
                }
                }
            }
        }while(!feof(relatorios));
        fclose(relatorios);
        if(informacao[1] == 0){
            printf("Nao existem Turmas cadastradas em nenhuma disciplina!\n");
            goto semTurmas;
        }

        //Relatorio
        printf("Percentual de aprovação: %.02f%%\n", (informacao[2] + informacao[3] + informacao[4])*100/informacao[1]);
        printf("Percentual de Alunos com rendimento SS: %.02f%%\n", (informacao[2]*100)/informacao[1]);
        printf("Percentual de Alunos com rendimento MS: %.02f%%\n", (informacao[3]*100)/informacao[1]);
        printf("Percentual de Alunos com rendimento MM: %.02f%%\n", (informacao[4]*100)/informacao[1]);
        printf("Percentual de Evasão: %.02f%%\n", ((informacao[0]+informacao[7])*100)/informacao[1]);
        printf("\nPercentual de Turmas com aprovação menor que 30%%: %.02f\n", T30*100/TT);
        printf("Percentual de Turmas com aprovação entre 30%% e 50%%: %.02f\n", T50*100/TT);
        printf("Percentual de Turmas com aprovação maior que 50%%: %.02f\n", TM*100/TT);
        printf("\n\nDisciplina com maior percentual de aprovação: %s\n", best);
        printf("Disciplina com menor percentual de aprovação: %s\n", worse);
        semTurmas:
        printf("----------------------------------------------------------\n\n");
        printf("Deseja voltar ao menu?\n1)Sim   2)Não\n");
        bloq_tecla(1, 2);
        switch(opcao_escolhida){
            case 1:
                system("cls");
                menu();
            break;
            case 2:
                system("cls");
                printf("Obrigado por utilizar MatrículaPobre.com!\n");
                exit("0");
            break;
        }
}
//---------------------------------------------------------//
// Função relação nome-código:
//---------------------------------------------------------//
void nomecodigo() {

	// Declaração
	char nome[TAM_MAX], string[TAM_MAX], linha[TAM_MAX];
	int i, j = 0, indicador, cont = 0, cond = 1;
	FILE *arquivo;
    FILE *disc;

	// Principal

	printf("Informe o código/nome da disciplina:\n");
	fflush(stdin);
	gets(nome);
    pesquisaparte(nome);

    disc = fopen("C:\\APC\\geral\\Disciplinas.txt", "r");
    do{
            fgets(string, TAM_MAX, disc);
            indicador = strstr(string, Busca);
            if(indicador != 0){
                    cont++;
                for(i = 0; i < TAM_MAX; i++){
                    Busca[i] = string[i];
                    if(string[i] == '|'){
                        Busca[i] = '\0';
                        j = i;
                        cond =0;
                    }
                    if(cond == 0){
                        for(i = j; i < TAM_MAX; i++){
                            linha[i-j] = string[i+1];
                            if(linha[i - j] == '|'){
                                linha[i - j] = '\0';
                            }
                        }
                    }
                }
            }
    }while(!feof(disc));
    fclose(disc);
    if(cont == 0){
        system("cls");
        printf("Essa disciplina nao possui cadastro!\n");
        menu();
    }
    //Relacao nome codigo
        printf("\n-------------------------------------------------\n");
		printf("A relação Nome-Código dessa diciplina é:\n\nNome da disciplina:    %s\nCodigo da disciplina:    %s", Busca, linha);
        printf("\n-------------------------------------------------\n");
		system("pause");
		printf("Deseja retornar ao menu principal?\n1)Sim   2)Não\n");
		bloq_tecla(1, 2);
		switch (opcao_escolhida) {
            case 1:
                system("cls");
                menu();
                break;
            case 2:
                system("cls");
                printf("Obrigado por utilizar MatrículaPobre.com!\n");
                exit("0");
			break;
		}
}
//---------------------------------------------------------//
//Funcao para listar Disciplinas:
//---------------------------------------------------------//
void lista() {

//Declaracoes
    char linha[TAM_MAX];
    int i, cont = 0, discs = 0;
    FILE *arquivo;
//Principal
    arquivo = fopen("C:\\APC\\geral\\Disciplinas.txt", "r");
        do{
            cont++;
            fgets(linha, TAM_MAX, arquivo);
            for(i = 0; i < TAM_MAX; i++){
                if(linha[i] == '|'){
                    linha[i] = '\0';
                    discs++;
                }
            }
            if(!feof(arquivo)){
                printf("%s\n", linha);
            }
        }while(!feof(arquivo));
    fclose(arquivo);
    if(discs == 0){
        printf("Nã há Disciplinas cadastradas!\n");
    }
    printf("-----------------\n\n");
    printf("Deseja retornar ao menu principal?\n1)Sim   2)Nao\n");
    bloq_tecla(1, 2);
    switch(opcao_escolhida){
        case 1:
            system("cls");
            menu();
        break;
        case 2:
            system("cls");
            printf("Obrigado por utilizar MatriculaPobre.com!\n");
            exit("0");
        break;
    }

}
//---------------------------------------------------------//
//Funcao dos creditos do programa:
void creditos(){
    //Declaracao
    char Autor[TAM_MAX] = {"Alvaro Henrique de Sousa Gouvea"};

    //Principal
    printf("Desenvolvimento:\n\n");
    printf("Desenvolvimento do Sistema:___| %s|\n", Autor);
    printf("Otimização de funções_________| %s|\n", Autor);
    printf("Modularização_________________| %s|\n", Autor);
    printf("Organização de Arquivos_______| %s|\n", Autor);
    printf("Cadastro de Disciplina________| %s|\n", Autor);
    printf("Cadastro de Turmas____________| %s|\n", Autor);
    printf("Exclusão de Disciplinas_______| %s|\n", Autor);
    printf("Exclusão de Turmas____________| %s|\n", Autor);
    printf("Relatorio por Disciplina______| %s|\n", Autor);
    printf("Relatorio Geral_______________| %s|\n", Autor);
    printf("Diretor Executivo_____________| %s|\n", Autor);
    printf("Produtor Executivo____________| %s|\n", Autor);
    printf("Beta Tester___________________|  Zeres Henrique de Sousa|\n");
    system("pause");
    system("cls");
    printf("Agradecimentos Especiais:\n");
    printf("\n-------|Joab Gouvea de Oliveira|------\n");
    printf("-----------|Ailton Aires|-------------\n");
    printf("---------|Anieli Schrammel|-----------\n");
    printf("--------|Isabele dos Santos|----------\n");
    printf("------|Gabriel \"gabgol\" Franck|------\n");
    printf("-------|Bruna Nayara Moreira|---------\n");
    printf("---------|Giovanni Almeida|-----------\n");
    system("pause");
    system("cls");
    printf("Obrigado por utilizar MatriculaPobre.com!\n");
    printf("Autor: %s\n", Autor);
    printf("Matricula: 18/0012002\n");
    printf("Um projeto possibilitador pela Universidade De Brasília Campus Gama!\n");
    system("pause");
    system("cls");
    menu();
}
//---------------------------------------------------------//
//Funcao para checar existencia da turma:
//---------------------------------------------------------//
int checkturma(char codigoturma[]){
//Declaracoes
    char NomeArquivo[TAM_MAX], Linha[TAM_MAX], codigo[TAM_MAX];
    int indicador = 0, check, i, ano, seme;
    FILE *Disciplina;
//Principal
    snprintf(NomeArquivo, TAM_MAX, "C:\\APC\\%s.txt", Busca);
    snprintf(codigo, TAM_MAX, "Turma: %s", codigoturma);
    for(i = 0; i < TAM_MAX; i++){
        codigoturma[i] = codigo[i];
    }
    Disciplina = fopen(NomeArquivo, "r");
        while(!feof(Disciplina)){
            fgets(Linha, TAM_MAX, Disciplina);
           check = strstr(Linha, codigoturma);
            if(check != 0){
                    for(i = 0; i < TAM_MAX; i++){
                        if(Linha[i] == '|'){
                            Linha[i] = '\0';
                            if(strcmp(Linha, codigoturma) == 0){
                                indicador = 1;
                            }
                        }
                    }
            }
        }
    fclose(Disciplina);

return indicador;
}
//---------------------------------------------------------//
//Funcao que permite pesquisar por nome, codigo, ou parte do nome:
//---------------------------------------------------------//
void pesquisaparte(char nome[]){

//Declaracoes
    int i, j, indicador, cont_casos = 0, opc;
    char string[TAM_MAX], codigo[TAM_MAX];
    FILE *disc, *temp;

    //Principal
    for(i = 0; i < TAM_MAX; i++){
        nome[i] = toupper(nome[i]);
    }
    if(nome[0] == '\0'){
        system("cls");
        printf("Favor informar um nome válido para a disciplina!\n");
        menu();
    }
    disc = fopen("C:\\APC\\geral\\Disciplinas.txt", "r");
        do{
            fgets(string, TAM_MAX, disc);
            indicador = strstr(string, nome);
            if(indicador != 0 && !feof(disc)){
                cont_casos++;
                for(i = 0; i < TAM_MAX; i++){
                    if(string[i] == '|'){
                        string[i] = '\0';
                    }
                }
                temp = fopen("C:\\APC\\temp.txt", "a");
                    fprintf(temp, "%s\n",string);
                fclose(temp);
                }
        }while(!feof(disc));
    fclose(disc);
        if(cont_casos == 0){
        system("cls");
        printf("A disciplina que você procura não está cadastrada!\n");
        menu();
        }
        if(cont_casos == 1){
            temp = fopen("C:\\APC\\temp.txt", "r");
                fgets(string, TAM_MAX, temp);
            fclose(temp);
            goto continua;
        }
        system("cls");
        printf("Disciplinas relacionadas à %s: \n", nome);
        printf("----------------------------------------\n");
        temp = fopen("C:\\APC\\temp.txt", "r");
        i = 0;
        do{
            i++;
            fgets(string, TAM_MAX, temp);
            if(!feof(temp)){
            printf("%d - %s", i, string);
            }
        }while(!feof(temp));
        fclose(temp);
        printf("Indique o número da disciplina que deseja: ");
        bloq_tecla(1, cont_casos);
        printf("\n");
        temp = fopen("C:\\APC\\temp.txt", "r");
        i = 0;
            do{
            i++;
            fgets(string, TAM_MAX, temp);
            }while(i < opcao_escolhida);
        fclose(temp);
        continua:
        for(i = 0; i < TAM_MAX; i++){
            if(string[i] == '\n'){
                string[i] = '\0';
            }
            Busca[i] = string[i];
        }
    remove("C:\\APC\\temp.txt");
}
//---------------------------------------------------------//
// Funcao que confere se já existe o código
//---------------------------------------------------------//
int checkcod(char cod[]){
    char Linha[TAM_MAX], comparador[TAM_MAX];
    int J = 0, i, cont = 0, result = 0;
    FILE *disc;
    for(i = 0; i < TAM_MAX; i++){
        cod[i] = toupper(cod[i]);
    }

    disc = fopen("C:\\APC\\geral\\Disciplinas.txt", "r");
        do{
            fgets(Linha, TAM_MAX, disc);
           if(strstr(Linha, cod) != 0){
                for(i = 0; i < TAM_MAX; i++){
                    comparador[J] = Linha[i];
                    J++;
                    if(Linha[i] == '|' && cont == 0){
                        J = 0;
                        cont++;
                    }
                }

                J = strlen(comparador);
                comparador[J- 2] = '\0';
                J = strcmp(comparador, cod);
                if(J == 0){
                result++;
                }
            }
        }while(!feof(disc));
    fclose(disc);

return result;

}
//---------------------------------------------------------//
//Funcao para bloqueio de teclas especficas:
//---------------------------------------------------------//
void bloq_tecla(int menor_opcao, int maior_opcao) {
	int i = 0;
	char b;
	char opcao[50];

	do {
		do {
			b = getch();
			if (isdigit(b) != 0) {
				opcao[i] = b;
				i++;
				printf("%c", b);
			} else if (b == 8 && i) {
				opcao[i] = '\0';

				i--;
				printf("\b \b");
			}

		} while (b != 13);
		opcao[i] = '\0';

		opcao_escolhida = atoi(opcao);

	} while (opcao_escolhida < menor_opcao || opcao_escolhida > maior_opcao);
}
//---------------------------------------------------------//
// Reset system
//---------------------------------------------------------//
void resetsystem(){
    //Declarações

    char disciplina[TAM_MAX], linha[TAM_MAX];
    int i;
    FILE *disc;
    //Principal
    disc = fopen("C:\\APC\\geral\\Disciplinas.txt", "r");
        do{
            fgets(linha, TAM_MAX, disc);
            for(i = 0; i < TAM_MAX; i++){
                if(linha[i] == '|'){
                    linha[i] = '\0';
                }
            }
            snprintf(disciplina, TAM_MAX, "C:\\APC\\%s.txt", linha);
            remove(disciplina);
        }while(!feof(disc));
    fclose(disc);
    remove("C:\\APC\\geral\\Disciplinas.txt");
    rmdir("C:\\APC\\geral");
    rmdir("C:\\APC");
    system("cls");
    printf("Sistema reiniciado com sucesso! Volte Novamente!\n");
    exit("0");
}
//---------------------------------------------------------//
// So um erro padrao:
//---------------------------------------------------------//
void error() {
	system("cls");
	printf("Error!\n\n");
}
//---------------------------------------------------------//
