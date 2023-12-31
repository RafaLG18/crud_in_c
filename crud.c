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
int deletar(Livro *l,int size_l);
void atualizar(Livro *l);
void gravar(Livro *l,int size_l);
void ler(Livro *l,int size_l);
void ler_lista(Livro *l,int size_l);
void ler_autor(Livro *l,int size_l);
void ler_arquivo();
void armazena_arquivo(Livro *l);
int verifica_arquivo();
int conta_linha();
int busca(char *nome,Livro *l);

int main(){
    int seleciona;
    int retorno_chama,retorno_verifica_livro;
    int size_l;
    Livro *l = NULL;

    /*
    Lê quantidade de linhas do arquivo para 
    dividir por 3 e saber quantas posições teremos do struct
    */
   retorno_verifica_livro=verifica_arquivo();

    if (retorno_verifica_livro==1){
        l= (Livro*) malloc(1*sizeof(Livro));
        size_l=0;
    }else if(retorno_verifica_livro!=1 && retorno_verifica_livro>=0 ){
        size_l=retorno_verifica_livro;
        // Se arquivo exitir, mas estiver vazio
        if (size_l==0){
            l= (Livro*) malloc(1*sizeof(Livro));
        }else{
            l=(Livro*) malloc((size_l+1)*sizeof(Livro));
        }
        armazena_arquivo(l);
    }

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
        gravar(l,size_l);
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
        gravar(l,size_l);
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
        puts("#|###############################|#");
        puts("#| 0- Menu principal             |#");
        puts(" ################################# ");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 0:
            /* code */
            system("clear ");
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
            puts("# 0- Menu principal             #");
            puts("#################################");
            scanf("%d",&opcao);
            switch (opcao)
            {
            case 0:
                system("clear ");
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
        puts("Livro atualizado:");
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

void gravar(Livro *l,int size_l){
    FILE *f;

    if ((f=fopen("livros.txt","w+"))==NULL)
    {
        printf("Erro na abertura do arquivo\n");
    }else{
        for (int i = 0; i < size_l; i++)
        {
            fprintf(f,"%s\n",l[i].nome_do_livro);
            fprintf(f,"%s\n",l[i].nome_do_autor);
            fprintf(f,"%s\n",l[i].nome_da_editora);

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
    char array[TAM_LIVRO];

    if ((f=fopen("livros.txt","r"))==NULL)
    {
        printf("Arquivo inexistente\n");
    }else{
        printf("Conteudo do livro:\n");
        while (fscanf(f,"%s\n",array)!=EOF){
            printf("%s\n",array);
        }
        fclose(f);    
    }
       
}

int conta_linha(){
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
        fclose(f);
        return conta;
    }   
}

int verifica_arquivo(){
    FILE *f;
    int size_l;
    /*
    Lê quantidade de linhas do arquivo para 
    dividir por 3 e saber quantas posições teremos do struct
    */
    if ((f=fopen("livros.txt","r"))==NULL){
        printf("Arquivo inexistente\n");
        return 1;
    }else{
        size_l=conta_linha()/3;
        fclose(f);
        return size_l;
    }
}

void armazena_arquivo(Livro *l){
    char palavra[TAM_LIVRO]={0};
    int conta_linha=1, size=0;
    FILE *f;
    if ((f=fopen("livros.txt","r"))==NULL){
        printf("Arquivo inexistente\n");
    }else{
        while (fscanf(f,"%s\n",palavra)!=EOF)
        {
            switch (conta_linha)
            {
            case 1:
                strcpy(l[size].nome_do_livro,palavra);
                memset(palavra,0,strlen(palavra));
                conta_linha++;
                break;
            case 2:
                strcpy(l[size].nome_do_autor,palavra);
                memset(palavra,0,strlen(palavra));
                conta_linha++;
                break;
            case 3:
                strcpy(l[size].nome_da_editora,palavra);
                memset(palavra,0,strlen(palavra));
                conta_linha=1;
                size++;
                break;
            default:
                break;
            }
        }
        fclose(f);
    }   
}
