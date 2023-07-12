// Programa parar fazer cadastro de livros

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM_LIVRO 100

typedef struct _livro{
    char nome_do_livro[TAM_LIVRO];
    char nome_do_autor[TAM_LIVRO];
    char nome_da_editora[TAM_LIVRO];
} Livro;

int chama(int seleciona,Livro *l,int size_l);
int cadastrar(Livro *l, int size_l);
void ler(Livro *l,int size_l);
void ler_lista(Livro *l,int size_l);
void ler_autor(Livro *l,int size_l);
void ler_arquivo();
void atualizar(Livro *l);
int deletar(Livro *l,int size_l);
int busca(char *nome,Livro *l);
void grava(Livro *l,int size_l);
int conta_linha(FILE *f);

int main(){
    int seleciona;
    int retorno_chama;
    int size_l;
    Livro *l;
    
    FILE *f;

    /*
    Lê quantidade de linhas do arquivo para 
    dividir por 3 e saber quantas posições teremos do struct
    */
    if ((f=fopen("livros.txt","r"))==NULL){
        printf("Arquivo inexistente\n");
        l= (Livro*) malloc(1*sizeof(Livro));
    }else{
        size_l=conta_linha(f)/3;
        if (size_l==0){
            l= (Livro*) malloc(1*sizeof(Livro));
        }else{
            l=realloc (l,(size_l+1)*sizeof(Livro));
        }
    }
    fclose(f);


    do{   
        puts(" ############################# ");
        puts("#| Digite a opção:           |#");
        puts("#| 0- Sair                   |#");
        puts("#| 1- Cadastrar              |#");
        puts("#| 2- Ler informação do livro|#");
        puts("#| 3- Atualizar livro        |#");
        puts("#| 4- Deletar livro          |#");
        puts("#| 5- Gravar informações     |#");
        puts(" ############################# ");
        scanf("%d",&seleciona);

        if (size_l>0 && seleciona==1){
            l=realloc (l,(size_l+1)*sizeof(Livro));
        }
        retorno_chama = chama(seleciona,l,size_l);

        if (retorno_chama==0)
        {
            continue;
        }else{
            size_l = retorno_chama;
            printf("Na main() size_l eh %d\n",size_l);
        }
        
    } while (seleciona!=0);
    free(l);
    return 0;
}

int chama(int seleciona,Livro *l,int size_l){
    switch (seleciona)
    {
    case 0:
        system("clear ");
        //scanf("%c");
        printf("Obrigado por usar o nosso programa\n");
        return 0;
        break;
    case 1:
        system("clear ");
        return cadastrar(l,size_l);
        break;
    case 2:
        system("clear ");
        ler(l,size_l);
        return 0;
        break;
    case 3:
        system("clear ");
        atualizar(l);
        return 0;
        break;
    case 4:
        system("clear ");
        return deletar(l,size_l);
        break;
    case 5:
        system("clear ");
        grava(l,size_l);
        printf("Gravando as informações....\n");
        return 0;
        break;
    default:
        system("clear");
        printf("Digite uma opção disponĩvel\n");
        return 0;
        break;
    }  
}

int cadastrar(Livro *l, int size_l){
    printf("Digite o nome do Livro \n");
    scanf(" %100[^\n]",&l[size_l].nome_do_livro);
    printf("Digite o nome do autor \n");
    scanf(" %100[^\n]",&l[size_l].nome_do_autor);
    printf("Digite o nome da editora \n");
    scanf(" %100[^\n]",&l[size_l].nome_da_editora);
    size_l=size_l+1;
    return size_l;
}

void ler(Livro *l,int size_l){
    int opcao;
    
    do
    {
        puts(" ################################# ");
        puts("#| Digite qual meio você quer    |#");
        puts("#| pesquisar os livros:          |#");
        puts("#|                               |#");
        puts("#| 1- Por nome de autor          |#");
        puts("#| 2- Todos os livros na memoria |#");
        puts("#| 3- Todos os livros no arquivo |#");
        puts("#| 0- Sair                       |#");
        puts(" ################################# ");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 0:
            /* code */
            break;
        case 1:
            ler_autor(l,size_l);
            break;
        case 2:
            ler_lista(l,size_l);
            break;
        case 3:
            ler_arquivo();
            break;
        default:
            break;
        }
    } while (opcao!=0);

}

void atualizar(Livro *l){
    int pos,opcao;
    char nome[TAM_LIVRO];
    
    printf("Qual nome do livro?\n");
    scanf(" %100[^\n]",&nome);
    
    pos=busca(nome,l);
    if (pos==-1){
        printf("Infelizmente não foi possível encontrar o livro '%s', tente novamente\n",nome);
    }else{
        do{   
            puts("#################################");
            puts("# O que voce quer atualizar?    #");
            puts("# 1- Nome do livro              #");
            puts("# 2- Nome do autor              #");
            puts("# 3- Nome da editora            #");
            puts("#################################");
            puts("# Pra sair digite 0             #");
            puts("#################################");
            scanf("%d",&opcao);
            switch (opcao)
            {
            case 0:
                break;
            case 1:
                // funcao para limpar string: nome_do_livro
                memset(l[pos].nome_do_livro,0,strlen(l[pos].nome_do_livro));
                puts("Digite o novo nome do livro");
                scanf(" %100[^\n]",&l[pos].nome_do_livro);
                break;
            case 2:
                // funcao para limpar string: nome_do_autor
                memset(l[pos].nome_do_autor,0,strlen(l[pos].nome_do_autor));
                puts("Digite o novo nome do autor");
                scanf(" %100[^\n]",l[pos].nome_do_autor);
                break;
            case 3:
                // funcao para limpar string: nome_da_editora
                memset(l[pos].nome_da_editora,0,strlen(l[pos].nome_da_editora));
                puts("Digite o novo nome do livro");
                scanf(" %100[^\n]",l[pos].nome_da_editora);
                break;
            default:
                printf("Digite um valor dentro do esperado");
                opcao=-1;
                system("clear");
                // limpa buffer
                scanf("%c");
                break;
            }
        } while (opcao!=0);
        
        printf("Livro: %s\n",l[pos].nome_do_livro);
        printf("Autor: %s\n",l[pos].nome_do_autor);
        printf("Editora: %s\n",l[pos].nome_da_editora);
    }
}

int deletar(Livro *l,int size_l){
   int pos; 
   char nome[TAM_LIVRO];
   printf("Qual nome do livro que você quer deletar?\n");
   scanf(" %100[^\n]",&nome);
   
   pos=busca(nome,l);

   if (pos==-1){
       printf("Infelizmente não foi possível encontrar o livro '%s', tente novamente\n",nome);
   }else{
       printf("Apagando:\n");
       printf("Livro: %s\n",l[pos].nome_do_livro);
       printf("Autor: %s\n",l[pos].nome_do_autor);
       printf("Editora: %s\n",l[pos].nome_da_editora);
       // Esvaziando as strings
       memset(l[pos].nome_do_livro,0,strlen(l[pos].nome_do_livro));
       memset(l[pos].nome_do_autor,0,strlen(l[pos].nome_do_autor));
       memset(l[pos].nome_da_editora,0,strlen(l[pos].nome_da_editora));
       // Copiando os valores da ultima string, parar posicão que teve as informações apagadas
       strncpy(l[pos].nome_do_livro,l[(size_l-1)].nome_do_livro,TAM_LIVRO);
       strncpy(l[pos].nome_do_autor,l[(size_l-1)].nome_do_autor,TAM_LIVRO);
       strncpy(l[pos].nome_da_editora,l[(size_l-1)].nome_da_editora,TAM_LIVRO);
       // Esvaziando as strings da ultima posicao
       memset(l[(size_l-1)].nome_do_livro,0,strlen(l[(size_l-1)].nome_do_livro));
       memset(l[(size_l-1)].nome_do_autor,0,strlen(l[(size_l-1)].nome_do_autor));
       memset(l[(size_l-1)].nome_da_editora,0,strlen(l[(size_l-1)].nome_da_editora));
       puts("Apagado\n");
       size_l=size_l-1;
       return size_l;

   } 
}

int busca(char *nome,Livro *l){
    for (int i = 0; i < sizeof(l); i++)
    {
        if(strcmp(nome,l[i].nome_do_livro)==0){
            return i;
        }else if (i==(sizeof(l)-1)){
            return -1;
        }else{
            continue;
        }
    }

}

void grava(Livro *l,int size_l){
    FILE *f;

    if ((f=fopen("livros.txt","a"))==NULL)
    {
        printf("Erro na abertura do arquivo\n");
    }else{
        for (int i = 0; i < size_l; i++)
        {
            fprintf(f,"#################################\n");
            fprintf(f,"%s\n",l[i].nome_do_livro);
            fprintf(f,"%s\n",l[i].nome_do_autor);
            fprintf(f,"%s\n",l[i].nome_da_editora);
            fprintf(f,"#################################\n");
            fprintf(f,"\n");

        }    
    }
    fclose(f);
}

void ler_lista(Livro *l,int size_l){
    printf("Listando todos os livros salvos até agora:\n");
    for (int i = 0; i < size_l; i++)
    {
        printf("#################################\n");
        printf("Livro: %s\n",l[i].nome_do_livro);
        printf("Autor: %s\n",l[i].nome_do_autor);
        printf("Editora: %s\n",l[i].nome_da_editora);
        printf("#################################\n");
        printf("\n");
    }
}

void ler_autor(Livro *l,int size_l){
    int pos;
    char nome[TAM_LIVRO];

    printf("Qual nome do livro?\n");
    scanf(" %100[^\n]",&nome);
    
    pos=busca(nome,l);
    
    if (pos==-1){
        printf("Infelizmente não foi possível encontrar o livro '%s', tente novamente\n",nome);
    }else{
        printf("Livro: %s\n",l[pos].nome_do_livro);
        printf("Autor: %s\n",l[pos].nome_do_autor);
        printf("Editora: %s\n",l[pos].nome_da_editora);
    }
}

void ler_arquivo(){
    FILE *f;
    char *livros;

    if ((f=fopen("livros.txt","a"))==NULL)
    {
        printf("Erro na abertura do arquivo\n");
    }else{
        for (int i = 0; i < sizeof(f); i++)
        {
            printf("%s",f[i]);
        }
        
    }
    fclose(f);   
}

int conta_linha(FILE *f){
    char c;
    int conta=0;
    FILE *f;
    
    if ((f=fopen("livros.txt","r"))==NULL){
        printf("Arquivo inexistente\n");
        return 0;
    }else{
        for ( c = getc(f); c != EOF; c = getc(f)){
            if (c=='\n')
            {
                conta++;
            }
        }
    }   
    fclose(f);
}