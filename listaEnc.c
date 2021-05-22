#include <stdio.h>
#include <stdlib.h>

struct Item {
    int dado;
    struct Item *proximo;
};

struct Lista {
    struct Item *primeiro;
};

struct Item * criaItem(int);
struct Lista * criaLista();
void inserir(struct Lista *, struct Item *);
void listar(struct Item *);
struct Lista * reverseList(struct Lista *);
void apagarlista(struct Item *);

int main()
{
    int q, n, i, c, chave;
    struct Lista *lista, *invlista;
    scanf ("%d", &q);
    for (i=0; i<q; i++)
    {
        scanf("%d", &n);
        if (n!=0){
            lista = criaLista();
            for (c=0; c<n; c++){
                scanf ("%d", &chave);
                inserir(lista, criaItem(chave));
            }
            invlista = reverseList(lista);
            listar(invlista->primeiro);
            printf ("\n");
            apagarlista(invlista->primeiro);
            free (lista);
            free (invlista);
        }
        
    }
    return 0;
}

struct Item *criaItem(int chave)
{
    struct Item *it = (struct Item*) malloc (sizeof(struct Item));
    if (it!=NULL){
        it->dado = chave;
        it->proximo = NULL;
    }
    return it;
}

struct Lista *criaLista()
{
    struct Lista *l = (struct Lista*) malloc (sizeof(struct Lista));
    if (l!=NULL){
        l->primeiro = NULL;
    }
    return l;
}

void inserir(struct Lista *lista, struct Item *novo)
{
    struct Item *anterior=NULL, *atual=lista->primeiro;
    int achei = 0;
    
    while(atual!=NULL && !achei)
    {
        if(atual->dado < novo->dado)
        {
            anterior = atual;
            atual = atual->proximo;
        }
        else
        {
            achei = 1;
        }
    }
        if(anterior == NULL) // eh o primeiro
        {
            lista->primeiro = novo;
        }
        else // eh no final ou no meio
        {
            anterior->proximo = novo;
        }
        novo->proximo = atual;
}

void listar(struct Item *it)
{
    if(it!=NULL && it->proximo!=NULL)
    {
        printf("%d ", it->dado);
        listar(it->proximo);
    }
    else if (it!=NULL && it->proximo==NULL)
    {
        printf("%d", it->dado);
    }
}

struct Lista * reverseList(struct Lista *lista)
{
    struct Item *anterior=NULL, *atual=lista->primeiro, *proximo=NULL;
    struct Lista *listainv= (struct Lista*) malloc (sizeof(struct Lista));
    while (atual!=NULL)
    {
        proximo = atual->proximo;
        atual->proximo=anterior; //ponteiro do atual vai apontar para o anterior (inverte)
        anterior=atual; // o anterior vira atual;
        atual= proximo; // atual vira o proximo;
    }
    listainv->primeiro = anterior;
    return listainv;
}

void apagarlista(struct Item *item)
{
    struct Item *atual=item, *proximo=NULL;
    while (atual!=NULL){
        proximo = atual->proximo;
        free (atual);
        atual = proximo;
    }
}
