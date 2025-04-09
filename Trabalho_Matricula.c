#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define VERMELHO 1
#define VERDE 2
#define AMARELO 3
#define AZUL 4
#define ROXO 5
#define ALUNO "Aluno_trabalho.dat"
#define DISCIPLINA "Disc_trabalho.dat"
#define MATRICULA "Mat_trabalho.dat"

void _linha(int cor){
	for(int i=0; i<50; i++)
		printf("\33[3%dm-\33[39m", cor);
	printf("\n");
}
void limpar(){
	fflush(stdout);
	system("sleep 1");
	system("clear");
}
typedef struct{
	char nome[20];
	int idade, id;
	char curso[20];
	char email[40];
}Aluno;

typedef struct{
	char nome[20];
	int carga;
	int cod;
	char prof[20];
	int valid;
}Disciplina;

typedef struct{
	int m_cod_aluno;
	int m_cod_disc;
	char materia[20];
	char aluno[20];
	float nota;
	int nulo;
	int id;
}Matricula;

void enter(){
	printf("\npressione enter para continuar...");
	setbuf(stdin, NULL);
	while(getchar()!='\n');
	system("clear");
}

int abrir(FILE *arquivo){
	if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }
    return 0;
}

int _vazio(FILE *arq) {
    fseek(arq, 0, SEEK_END);
    return ftell(arq) == 0;
}

int _v_matr(FILE* arq2){
	Matricula matr;
	int cont=0;
	rewind(arq2);
	while(fread(&matr, sizeof(Matricula), 1, arq2)){
		if(!matr.nulo){
			cont=1;
			break;
		}
	}
	return cont;
}

int _v_disc(FILE* arq1){
	Disciplina disc;
	int cont=0;
	rewind(arq1);
	while(fread(&disc, sizeof(Disciplina), 1, arq1)){
		if(disc.valid){
			cont=1;
			break;
		}
	}
	return cont;
}

void mostrar_aluno(){
	FILE* arq = fopen(ALUNO, "rb+");
	Aluno aluno;
	rewind(arq);
	printf("\33[33m=ALUNOS=\33[39m\n");
	printf("\33[32m%-5s | %-30s\33[39m\n", "ID", "Nome");
   _linha(AZUL);
	while(fread(&aluno,sizeof(Aluno), 1, arq)){
		printf("%-5d | %-30s\n", aluno.id, aluno.nome);
	}	
}

void mostrar_disc(){
	FILE* arq = fopen(DISCIPLINA, "rb+");
	Disciplina disc;
	rewind(arq);
	printf("\n\33[33m=DISCIPLINAS=\33[39m\n");
	printf("\33[32m%-5s | %-15s \33[39m", "ID", "DISCIPLINA");
	printf("\n");
	_linha(AZUL);
	while(fread(&disc, sizeof(Disciplina), 1, arq))
		if(disc.valid){
				printf("%-5d | %-15s\n",
					disc.cod, disc.nome);
		}
}
void mostrar_mat(){
	FILE* arq = fopen(MATRICULA, "rb+");
	Matricula mat;
	rewind(arq);
	printf("\n\33[33m=MATRICULAS=\33[39m\n");
	printf("\33[32m%-5s | %-15s | %-15s \33[39m", "ID", "ALUNO", "DISCIPLINA");
	printf("\n");
	_linha(AZUL);
	while(fread(&mat, sizeof(Matricula), 1, arq))
		if(!mat.nulo){
				printf("%-5d | %-15s | %-15s\n",
					mat.id,
					mat.aluno, mat.materia);
		}
		
}

int interface(FILE** arq){
	printf("\t\33[1;32m== MENU PRINCIPAL ==\33[0m\n");
	_linha(ROXO);
	printf("1 - DISCENTES\n");
	printf("2 - DISCIPLINAS\n");
	if(_vazio(arq[0]) || _vazio(arq[1]))
		printf("\33[31m3 - MATRICULAS\33[39m\n");
	else
		printf("3 - MATRICULAS\n");
	if(_vazio(arq[0]) && _vazio(arq[1]) && _vazio(arq[2]))
		printf("\33[31m4 - RESUMO GERAL\33[0m\n");
	else
		printf("4 - RESUMO GERAL\n");
	_linha(ROXO);
	printf("0 - Sair do Programa\n\n");
	printf("Escolha o Módulo: ");
	int opt;
	scanf(" %d", &opt);
	system("clear");
	return opt;
	
}

int menu_aluno(FILE* arq){
	printf("\t\33[1;34m== DISCENTES ==\33[0m\n");
	_linha(AZUL);
	printf("1 - Cadastrar Discente\n");
	if(_vazio(arq)){
		printf("\33[31m2 - Relatório Discentes\n");
		printf("3 - Consultar Discente\n");
		printf("4 - Editar Discentes\33[39m\n");
	}else{
		printf("2 - Relatório Discentes\n");
		printf("3 - Consultar Discente\n");
		printf("4 - Editar Discentes\n");
	}
	_linha(AZUL);
	printf("0 - Retornar ao MENU PRINCIPAL\n\n");	
	printf("Escolha uma opção: ");
	int opt;
	scanf(" %d", &opt);
	system("clear");
	return opt;
}

int menu_disciplina(FILE** arq){
	printf("\t\33[1;33m== DISCIPLINAS ==\33[0m\n");
	_linha(AMARELO);
	printf("1 - Cadastrar Disciplina\n");
	if(_vazio(arq[1]) || !_v_disc(arq[1])){
		printf("\33[31m2 - Relatório Disciplinas\n");
		printf("3 - Diario de Disciplina\n");
		if(_v_matr(arq[2]))
			printf("\33[31m4 - Lançar Notas\33[0m\n");
		else	
			printf("4 - Lançar Notas\n");
		printf("5 - Editar Disciplina\n");
		printf("6 - Cancelar Oferta de Disciplina\33[39m\n");
	}else{
		printf("2 - Relatório Disciplinas\n");
		printf("3 - Diario de Disciplina\n");
		if(_vazio(arq[0]) || _vazio(arq[2]))
			printf("\33[31m4 - Lançar Notas\33[39m\n");
		else
			printf("4 - Lançar Notas\n");
		printf("5 - Editar Disciplina\n");
		printf("6 - Cancelar Oferta de Disciplina\n");
	}
	_linha(AMARELO);
	printf("0 - Retornar ao MENU PRINCIPAL\n\n");
	printf("Escolha uma opção: ");
	//...
	int opt;
	scanf(" %d",&opt);
	system("clear");
	return opt;	
}

int menu_matricula(FILE* arq2){
	printf("\t\33[1;32m== MATRICULAS ==\33[0m\n");
	_linha(VERDE);
	printf("1 - Realizar Matricula\n");
	if(_vazio(arq2) || _v_matr(arq2)==0){
		printf("\33[31m2 - Consultar Todas Matriculas\n");
		printf("3 - Cancelar Matricula\33[39m\n");
	}else{		
		printf("2 - Consultar Todas Matriculas\n");
		printf("3 - Cancelar Matricula\n");
	}
		printf("0 - Retornar ao MENU PRINCIPAL\n");
		
	_linha(VERDE);
	//...
	int opt;
	scanf(" %d",&opt);
	system("clear");
	return opt;
}

void cad_aluno(FILE *arq){
		
	Aluno aluno;
	char temp[20];
	int z;
	
	printf("\t\33[1;34m== CADASTRAMENTO ==\33[0m\n\n");
	printf("Digite o nome do aluno (\33[33mou 0 para sair\33[39m): ");
	scanf(" %[^\n]s", temp);
	if(strcmp(temp, "0")==0){
		system("clear");
		return;
	}
	rewind(arq);
	while(fread(&aluno, sizeof(Aluno), 1, arq)){
		z=0;
		if(strcmp(temp, aluno.nome)==0){
			printf("ESSE NOME JÁ ESTÁ REGISTRADO (TENTE USAR O SOBRENOME)\n");
			z=1;
			return;
		}
	}
	if(!z)
		strcpy(aluno.nome, temp);
		
	printf("Digite a idade do aluno: "); scanf(" %d", &aluno.idade);
	printf("Digite o curso do aluno: "); scanf(" %[^\n]s", aluno.curso);
	printf("Digite o email do aluno: "); scanf(" %[^\n]s", aluno.email);
	printf("Digite o ID do aluno: "); scanf(" %d", &aluno.id);
	
	fseek(arq, 0, SEEK_END);
	if(fwrite(&aluno, sizeof(Aluno), 1, arq)){
		fflush(arq);
		printf("\nCADASTRO REALIZADO COM SUCESSO\n");
	}
	
	enter();
}


void lista_alunos(FILE *arq) {
    Aluno aluno;

    printf("\t\33[1;34m== RELATÓRIO DE DISCENTES ==\33[0m\n\n");

    if (fseek(arq, 0, SEEK_END) == 0 && ftell(arq) == 0) {
        printf("\n\33[33mNenhum cadastro realizado.\33[0m\n");
        enter();
        return;
    }

    printf("%-5s | %-20s | %-5s | %-15s | %-15s\n", 
           "ID", "NOME", "IDADE", "CURSO", "EMAIL");
    printf("-------------------------------------------------------------------------------\n");

    rewind(arq);
    while (fread(&aluno, sizeof(Aluno), 1, arq) == 1) {
        printf("%-5d | %-20s | %-5d | %-15s | %-15s\n", 
               aluno.id, 
               aluno.nome, 
               aluno.idade, 
               aluno.curso, 
               aluno.email);
    }

    enter();
}

void cad_disciplina(FILE *arq1){
	
	Disciplina disc;
	char alvo[20];
	int alvoid;
	int z=0;
	printf("\t\33[1;33m== CADASTRO DE DISCIPLINA ==\33[0m\n\n");
	do{
		printf("Digite o nome da disciplina (\33[33mou 0 para sair\33[39m): ");
		scanf(" %[^\n]s", alvo);
		if(strcmp(alvo, "0")==0){
			system("clear");
			return;
		}
		while(fread(&disc, sizeof(Disciplina), 1, arq1)){
			if(strcmp(disc.nome, alvo)==0){
				printf("Esse nome já foi registrado\n");
				z=1;
			}
		}
		if(!z)
			break;
	}while(1);
	z=0;
	do{
		printf("Digite o código da disciplina: ");
		scanf(" %d", &alvoid);
		while(fread(&disc, sizeof(Disciplina), 1, arq1)){
			if(alvoid==disc.cod){
				printf("Esse ID já foi registrado\n");
				z=1;
			}
		}
		if(!z)
			break;
	}while(1);
	printf("Digite o nome do professor: ");
	scanf(" %[^\n]s", disc.prof);
	printf("Digite a carga horária: ");
	scanf(" %d", &disc.carga);
	
	disc.valid=1;
	strcpy(disc.nome, alvo);
	disc.cod=alvoid;
	if(fwrite(&disc, sizeof(Disciplina), 1, arq1)){
		fflush(arq1);
		printf("CADASTRO REALIZADO COM SUCESSO");
	}
	else
		printf("ERRO AO CADASTRAR A DISCIPLINA");
	
	enter();
}

void matricular(FILE **arq){
	Matricula matricula;
	Aluno aluno;
	Disciplina disc;
	int id_aluno, cod_disc;
	int alun_achou = 0, disc_achou = 0;
	
	printf("\t\33[1;32m== MATRICULAR ==\33[0m\n\n");
	
	mostrar_aluno();
	
	mostrar_disc();
	printf("\n");
	//Procurar ID aluno
	do{	
		printf("Digite o ID do aluno (\33[33mou 0 para sair\33[39m): ");
		scanf(" %d", &id_aluno);
		if(id_aluno==0){
			system("clear");
			return;
		}
		rewind(arq[0]);
		while (fread(&aluno, sizeof(Aluno), 1, arq[0])) {
			if (aluno.id == id_aluno) {
				alun_achou = 1;
				break;
			}
		}

		if (!alun_achou) {
			printf("\33[31mAluno com ID %d não registrado.\33[39m\n\n", id_aluno);
			
		}
		if(alun_achou)
			break;
	}while(1);
	//Procurar ID disciplina
	do{
		printf("Digite o CÓDIGO da disciplina: ");
		scanf(" %d", &cod_disc);

		rewind(arq[1]);
		while (fread(&disc, sizeof(Disciplina), 1, arq[1])) {
			if (disc.cod == cod_disc) {
				disc_achou = 1;
				break;
			}
		}

		if (!disc_achou) {
			printf("Disciplina com código %d não registrada.\n", cod_disc);
			enter();
		}
		if(disc_achou)
			break;
	}while(1);
	
	//Confirmação
	int a = 0;
	rewind(arq[2]);
	while (fread(&matricula, sizeof(Matricula), 1, arq[2])) {
		if (cod_disc == matricula.m_cod_disc && id_aluno == matricula.m_cod_aluno && !matricula.nulo) {
			a = 1;
			break;
		}
	}
	if (a) {
		printf("\n\33[33mESSE ALUNO JÁ ESTÁ MATRICULADO NESSA MATÉRIA\n\33[39m");
		enter();
		return;
	}
	
	//procurar ID matricula
	int _id;
	int mat_achou;
	do{
		mat_achou=0;
		printf("Digite o ID da nova matricula: ");
		scanf(" %d", &_id);

		rewind(arq[2]);
		while (fread(&matricula, sizeof(Matricula), 1, arq[2])) {
			if (matricula.id ==_id && !matricula.nulo) {
				mat_achou = 1;
				break;
			}
		}

		if (mat_achou) {
			printf("Já existe uma matricula com esse ID.\n");
			enter();
		}
		if(!mat_achou)
			break;
	}while(1);
	
	
	matricula.id = _id;
	matricula.m_cod_aluno = aluno.id;
	matricula.m_cod_disc = disc.cod;
	
	strcpy(matricula.aluno, aluno.nome);
	strcpy(matricula.materia, disc.nome);
	matricula.nulo = 0;
	matricula.nota = 0;  

	fseek(arq[2], 0, SEEK_END);
	fwrite(&matricula, sizeof(Matricula), 1, arq[2]);
	fflush(arq[2]);

	printf("\nMATRÍCULA REALIZADA COM SUCESSO!\n");
	printf("Aluno: %s | Disciplina: %s\n", aluno.nome, disc.nome);
	enter();
}


void lista_disciplina(FILE *arq1, FILE *arq2){
	
	Disciplina disc;
	
	printf("\t\33[1;33m== LISTA DE DISCIPILNAS ==\33[0m\n\n");
	if(fseek(arq1, 0, SEEK_END)==0 && ftell(arq1)==0){
		printf("nenhuma disciplina cadastrada\n");
		enter();
		return;
	}else{
		rewind(arq1);
		printf("%-5s | %-15s | %-15s | %-8s",
			"ID", "DISCIPLINA", "PROFESSOR", "CH");
		printf("\n");
		_linha(AMARELO);
		while(fread(&disc, sizeof(Disciplina), 1, arq1)){
			if(disc.valid){
				printf("%-5d | %-15s | %-15s | %-8d\n",
					disc.cod, disc.nome, disc.prof, disc.carga);
			}
			
		}
	}
	printf("\n");
	enter();
}

void lista_matricula(FILE** arq){
	Matricula matr;
	printf("\t\33[1;32m== RELATÓRIO MATRICULAS ==\33[0m\n\n");
    printf("%-5s | %-20s | %s\n","ID", "MATÉRIA", "ALUNO");
    printf("---------------------------------------------------------\n");
	
	rewind(arq[2]);
	while(fread(&matr, sizeof(Matricula), 1, arq[2])){
		if(matr.nulo==0)
			printf("%-5d | %-20s | %s\n", matr.id, matr.materia, matr.aluno);
	}
	enter();
}

void resumo(FILE** arq){
	printf("\t\33[1;31m== RESUMO GERAL ==\33[0m\n\n");
	if(!_vazio(arq[0])){
		mostrar_aluno();
		_linha(VERMELHO);
	}
	if(!_vazio(arq[1]) && _v_disc(arq[1])){
		mostrar_disc();
		_linha(VERMELHO);
	}
	if(!_vazio(arq[2]) && _v_matr(arq[2])){
		mostrar_mat();
		_linha(VERMELHO);
	}
	enter();
}

void busca(FILE *arq, FILE *arq2) {
    Aluno aluno;
    Matricula matricula;
    int alvo_id;
    int encontrado = 0;
    int cont = 0;
	printf("\t\33[1;34m== CONSULTAR DISCENTE ==\33[0m\n\n");
    printf("Digite o ID do aluno que deseja buscar (\33[33mou 0 para sair\33[39m): ");
    scanf(" %d", &alvo_id);
	if(alvo_id==0){
		system("clear");
		return;
	}
	printf("\n%-10s | %-5s | %-10s | %-15s | %-5s", 
		"NOME", "IDADE", "CURSO", "EMAIL", "ID\n");
	_linha(AZUL);
    rewind(arq);
    while (fread(&aluno, sizeof(Aluno), 1, arq)) {
        if (aluno.id == alvo_id) {
           printf("%-10s | %-5d | %-10s | %-15s | %-5d \n",
                   aluno.nome, aluno.idade, aluno.curso, aluno.email, aluno.id);

            rewind(arq2);
            printf("\nMatérias Matriculadas:\n\n");
            while (fread(&matricula, sizeof(Matricula), 1, arq2)) {
                if (strcmp(aluno.nome, matricula.aluno) == 0 && !matricula.nulo) {
                    cont++;
                    printf("[%d] %-15s | NOTA: %.2f\n", cont, matricula.materia, matricula.nota);
                }
            }

            if (cont == 0) {
                printf("Não realizou nenhuma matrícula.\n");
            }

            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        printf("Aluno com ID %d não encontrado.\n", alvo_id);
    }

    printf("\n");
    enter();
}

FILE *abrir_arquivo(char *nome){
	FILE *arq = fopen(nome, "rb+");
	if(!arq){
		arq = fopen(nome, "a+b");
		if(!arq){
			printf("ERRO AO ABRIR O ARQUIVO\n");
		exit(1);
		}
	}
	return arq;
}

void diario_disciplina(FILE *disc, FILE *mat) {
    Disciplina disciplina;
    Matricula matricula;
    char nome_disciplina[20];
    int achou = 0, contador = 0;

    printf("\t\33[1;33m== DIÁRIO DE DISCIPLINA ==\33[0m\n\n");
    printf("Digite o nome da disciplina (\33[33mou 0 para sair\33[39m): ");
    scanf(" %[^\n]s", nome_disciplina);
    if(strcmp(nome_disciplina, "0")==0){
		system("clear");
		return;
	}

    rewind(disc);
    while (fread(&disciplina, sizeof(Disciplina), 1, disc)) {
        if (strcmp(disciplina.nome, nome_disciplina) == 0) {
            achou = 1;
            printf("\nDISCIPLINA: %s\n", disciplina.nome);
            printf("CÓDIGO: %04d\n", disciplina.cod);
            printf("PROFESSOR: %s\n", disciplina.prof);
            printf("CARGA HORÁRIA: %d horas\n", disciplina.carga);
            printf("\nALUNOS MATRICULADOS:\n");
            
            rewind(mat);
            while (fread(&matricula, sizeof(Matricula), 1, mat)) {
                if (strcmp(matricula.materia, disciplina.nome) == 0) {
                    contador++;
                    printf("%d - %s (Nota: %.2f)\n", contador, matricula.aluno, matricula.nota);
                }
            }

            if (contador == 0) {
                printf("Nenhum aluno matriculado nesta disciplina.\n");
            }
            break;
        }
    }

    if (!achou) {
        printf("Disciplina '%s' não encontrada.\n", nome_disciplina);
    }

    printf("\n");
    enter();
}

void fechar_arquivo(FILE **arq, int size){
	for (int i = 0; i < size; i++){
		fclose(arq[i]);
	}
}

void apagar_arquivo(){
	int a;
	printf("TEM CERTEZA DA SUA DECISÃO? (==1 - sim, !=1 - não)"); scanf(" %d", &a);
	if(a==1){
		remove(ALUNO);
		remove(DISCIPLINA);
		remove(MATRICULA);
		printf("OS DADOS FORAM APAGADOS.\n");
		return;
	}else{
		printf("OS DADOS NÃO FORAM APAGADOS.\n");
	}
	enter();
}

void editar_aluno(FILE* arq[0]){
	Aluno aluno;
	int alvo;
	int a=0;
	printf("\t\33[1;34m== ALTERAR DADOS ==\33[0m\n\n");
	mostrar_aluno();
	
	do{
		printf("\nDigite o ID do aluno que deseja alterar (\33[33mou 0 para sair\33[39m): ");
		scanf(" %d", &alvo);
		if(alvo==0){
			system("clear");
			return;
		}			
		rewind(arq[0]);
		while(fread(&aluno, sizeof(Aluno), 1, arq[0])){
			if(alvo==aluno.id){
				a=1;
				fseek(arq[0], -sizeof(Aluno), SEEK_CUR);
				break;
			}
		}
		if(!a){
				printf("\33[34m\nALUNO NÃO REGISTRADO\33[39m\n");
		}
		if(a)
			break;
	}while(1);
	
	
	printf("Digite o novo nome: "); scanf(" %[^\n]s", aluno.nome);
	printf("Digite o novo ID: "); scanf(" %d", &aluno.id);
	printf("Digite o nova idade: "); scanf(" %d", &aluno.idade);
	printf("Digite o novo curso: "); scanf(" %[^\n]s", aluno.curso);
	printf("Digite o novo email: "); scanf(" %[^\n]s", aluno.email);
	
	fwrite(&aluno, sizeof(Aluno), 1, arq[0]);
	fflush(arq[0]);
	
	printf("\n\33[33mEdição realizada com sucesso\33[39m\n");
	enter();
}

void editar_disciplina(FILE* arq1, FILE* arq2){
	Disciplina disc;
	Matricula matr;
	printf("\t\33[1;33m== ALTERAR DISCIPLINA ==\33[0m\n");
	
	mostrar_disc();
	int alvo, a;
	do{
		a=0;
		printf("\nDigite o ID da disciplina que deseja alterar (\33[33mou 0 para sair\33[39m): ");
		scanf(" %d", &alvo);
		if(alvo==0){
			system("clear");
			return;
		}
		rewind(arq1);
		while(fread(&disc, sizeof(Disciplina), 1, arq1)){
			if(alvo==disc.cod){
				a=1;
				fseek(arq1, -sizeof(Disciplina), SEEK_CUR);
				break;
			}
		}
		if(!a)
			printf("Disciplina não encontrada\n");
		else
			break;
	}while(1);	
	
	printf("Novo nome: "); scanf(" %s", disc.nome);
	printf("Novo Professor: "); scanf(" %s", disc.prof);
	printf("Nova CH: "); scanf(" %d", &disc.carga);
	printf("Novo ID: "); scanf(" %d", &disc.cod);
	disc.valid=1;
	
	fwrite(&disc, sizeof(Disciplina), 1, arq1);
	fflush(arq1);
	
	rewind(arq2);
	while(fread(&matr, sizeof(Matricula), 1, arq2)){
		if(alvo==matr.m_cod_disc){
			matr.nulo=1;
			fseek(arq2, -sizeof(Matricula), SEEK_CUR);
			fwrite(&matr, sizeof(Matricula), 1, arq2);
			fflush(arq2);
		}
	}
	
	printf("Alteração realizada\n");
	enter();
}

void trancar_matricula(FILE* arq2){
	Matricula matricula;
	
	printf("\t\33[1;32m== CANCELAR MATRÍCULA ==\33[0m\n");
	mostrar_mat();
	
	int _id;
	int mat_achou;
	do{
		mat_achou=0;
		printf("Digite o ID da matricula (\33[33mou 0 para sair\33[39m): ");
		scanf(" %d", &_id);
		if(_id==0){
			system("clear");
			return;
		}

		rewind(arq2);
		while (fread(&matricula, sizeof(Matricula), 1, arq2)) {
			if (matricula.id == _id) {
				mat_achou = 1;
				matricula.nulo=1;
				fseek(arq2, -sizeof(Matricula), SEEK_CUR);
				fwrite(&matricula, sizeof(Matricula), 1, arq2);
				fflush(arq2);
				break;
			}
		}

		if (mat_achou){
			printf("\nMatricula Cancelada.\n\n");
			enter();
			break;
		}
		if(!mat_achou)
			printf("Matricula não encontrada");
	}while(1);
}

void trancar_disciplina(FILE* arq1){
	Disciplina disc;
	
	printf("\t\33[1;33m== CANCELAR DISCIPLINA ==\33[0m\n");
	mostrar_disc();
	int alvo, a;
	do{
		a=0;
		printf("\nDigite o ID da disciplina que deseja cancelar (\33[33mou 0 para sair\33[39m): ");
		scanf(" %d", &alvo);
		if(alvo==0){
			system("clear");
			return;
		}
		rewind(arq1);
		while(fread(&disc, sizeof(Disciplina), 1, arq1)){
			if(alvo==disc.cod){
				a=1;
				disc.valid=0;
				fseek(arq1, -sizeof(Disciplina), SEEK_CUR);
				fwrite(&disc, sizeof(Disciplina), 1, arq1);
				fflush(arq1);
				break;
			}
		}
		if(!a)
			printf("Disciplina não encontrada\n");
		else
			break;
	}while(1);
	
	printf("Disciplina cancelada\n");
	enter();
}

void _lista_alun_matr(FILE** arq) {
    Aluno aluno;
    Disciplina disc;
    Matricula matricula;
    int encontrou;

    printf("\n%-5s | %-20s | %s\n", "ID", "NOME DO ALUNO", "MATRICULADO EM");
    printf("-----------------------------------------------------------\n");

    rewind(arq[0]);
    while (fread(&aluno, sizeof(Aluno), 1, arq[0])) {
        printf("%-5d | %-20s | ", aluno.id, aluno.nome);
        encontrou = 0;

        rewind(arq[2]);
        while (fread(&matricula, sizeof(Matricula), 1, arq[2])) {
            if (matricula.m_cod_aluno == aluno.id) {
               
                rewind(arq[1]);
                while (fread(&disc, sizeof(Disciplina), 1, arq[1])) {
                    if (disc.cod == matricula.m_cod_disc) {
                        if (encontrou) printf(", ");
                        printf("[%d] - %s",disc.cod, disc.nome);
                        encontrou = 1;
                        break;
                    }
                }
            }
        }

        if (!encontrou) {
            printf("Sem Matrículas");
        }

        printf("\n");
    }

    printf("-----------------------------------------------------------\n");
}


void dist_notas(FILE** arq){
	Aluno aluno;
	Disciplina disc;
	Matricula matricula;
	int alvo, alvo1, a, b;
	
	printf("\t\33[1;33m== LANÇAR NOTAS ==\33[0m\n\n");
	
	_lista_alun_matr(arq);
	do{
		a=0;
		b=0;
		printf("\nDigite o ID do aluno (\33[33mou 0 para sair\33[39m): ");
		scanf(" %d", &alvo);
		if(alvo==0){
			system("clear");
			return;
		}
		rewind(arq[2]);
		while(fread(&matricula, sizeof(Matricula), 1, arq[2])){
			if(alvo==matricula.m_cod_aluno){
				a=1;
				printf("Digite o ID da disciplina: ");
				scanf(" %d", &alvo1);
				rewind(arq[2]);
				while(fread(&matricula, sizeof(Matricula), 1, arq[2]))
					if(alvo==matricula.m_cod_aluno && alvo1==matricula.m_cod_disc){
						b=1;
						fseek(arq[2], -sizeof(Matricula), SEEK_CUR);
						break;
					}
				break;
			}
		}
		if(a==0)
			printf("\33[33mDiscente não encontrado...\n\33[39m");
		if(a==1 && b==0)
			printf("\33[33mDiscente não cadastrado nessa Disciplina...\33[39m");
		if(a==1 && b==1)
			break;
	}while(1);
	char _nome[20];
	char _disc[20];
	float _nota;
	
	rewind(arq[0]);
	while(fread(&aluno, sizeof(Aluno), 1, arq[0]))
		if(alvo==aluno.id){
			strcpy(_nome, aluno.nome);
			break;
		}
		
	rewind(arq[1]);
	while(fread(&disc, sizeof(Disciplina), 1, arq[1]))
		if(alvo1==disc.cod){
			strcpy(_disc, disc.nome);
			break;
		}
		
	printf("%-15s | %-15s | %-6s", "DISCENTE", "DISCIPLINA", "NOTA ATUAL");
	printf("\n");
	_linha(AMARELO);
	printf("%-15d | %-15d | %-6.2f", alvo, alvo1, matricula.nota);
	printf("\nNOVA NOTA: ");
	scanf(" %f", &_nota);
	matricula.nota = _nota;
	
	fseek(arq[2], -sizeof(Matricula), SEEK_CUR);
	fwrite(&matricula, sizeof(Matricula), 1, arq[2]);

    printf("\n\33[32mNota lançada com sucesso!\33[39m\n");
    enter();
}


void controle_aluno(FILE** arq){
	do{
		switch(menu_aluno(arq[0])){
			case 1: cad_aluno(arq[0]);
					break;
			case 2:	if(_vazio(arq[0]))
						printf("\33[33mOPÇÃO INDISPONÍVEL\33[39m\n");
					else
						lista_alunos(arq[0]);
					break;
					
			case 3: if(_vazio(arq[0]))
						printf("\33[33mOPÇÃO INDISPONÍVEL\33[39m\n");
					else
						busca(arq[0], arq[2]);
					break;
					
			case 4: editar_aluno(arq);
					break;
			case 0:return;
			
			default: printf("OPÇÃO INVÁLIDA\n");
					limpar();
					break;
		}
	}while(1);
}

void controle_disciplina(FILE** arq){
	do{
		switch(menu_disciplina(arq)){
			case 1:	cad_disciplina(arq[1]);
					break;
			case 2: if(_vazio(arq[1]) || !_v_disc(arq[1]))
						printf("\33[33mOPÇÃO INDISPONÍVEL\33[39m\n");
					else
						lista_disciplina(arq[1], arq[2]);
					break;
					
			case 3: if(_vazio(arq[1]) || !_v_disc(arq[1]))
						printf("\33[33mOPÇÃO INDISPONÍVEL\33[39m\n");
					else
						diario_disciplina(arq[1], arq[2]);
					break;
			case 4: if(_vazio(arq[1]) || _vazio(arq[2]) || !_v_disc(arq[1]))
						printf("\33[33mOPÇÃO INDISPONÍVEL\33[39m\n");
					else
						dist_notas(arq);
					break;
			case 5: if(_vazio(arq[1]) || !_v_disc(arq[1]))
						printf("\33[33mOPÇÃO INDISPONÍVEL\33[39m\n");
					else
						editar_disciplina(arq[1], arq[2]);
					break;
			case 6: if(_vazio(arq[1]) || !_v_disc(arq[1]))
						printf("\33[33mOPÇÃO INDISPONÍVEL\33[39m\n");
					else
						trancar_disciplina(arq[1]);
					break;
			case 0:return;
			default: printf("OPÇÃO INVÁLIDA\n");
					limpar();
					break;			
			
		}
		
	}while(1);
}

void controle_matricula(FILE** arq){
	do{
		switch(menu_matricula(arq[2])){
			case 1: matricular(arq);
					break;
			case 2: if(!_v_matr(arq[2]))
						printf("\33[33mOPÇÃO INDISPONÍVEL\33[39m\n");
					else	
						lista_matricula(arq);
					break;
			case 3: if(!_v_matr(arq[2]))
						printf("\33[33mOPÇÃO INDISPONÍVEL\33[39m\n");
					else	
						trancar_matricula(arq[2]);
					break;
			case 0: return;
			default: printf("OPÇÃO INVÁLIDA\n");
					limpar();
					break;			
		}
	
	}while(1);
	
}

int main(){
	FILE* arq[3];
	arq[0] = abrir_arquivo(ALUNO);
	arq[1] = abrir_arquivo(DISCIPLINA);
	arq[2] = abrir_arquivo(MATRICULA);
	
	do{
		switch(interface(arq)){
			case 1: controle_aluno(arq);
					break;
			case 2: controle_disciplina(arq);
					break;
					
			case 3: if(_vazio(arq[0]) || _vazio(arq[1]) || !_v_disc(arq[1]))
						printf("\33[33mÉ NECESSÁRIO CADASTRAR PELO MENOS UM DISCENTE E UMA DISCIPLINA\33[39m\n");
					else
						controle_matricula(arq);
					break;
					
			case 4: if(_vazio(arq[0]) && _vazio(arq[1]) && _vazio(arq[2]))
						printf("\33[33mNÃO HÁ NADA PARA MOSTRAR\33[39m\n");
					else
						resumo(arq);
					break;
					
			case 0: fechar_arquivo(arq, 3);
					return 0;
			case -1: apagar_arquivo();
					return 0;
			default: printf("Opção invalida...");
					limpar();
					break;
			
		}
	}while(1);
	

	return 0;
}
