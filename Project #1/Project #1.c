#include <stdio.h>
#include <stdlib.h>
struct list{
long long int sayi ;
struct list *next_list;
struct list *pre_list;
};
void sayi_at(struct list *listem_head,long long int sayi);
void push(struct list *liste_head,long long int sayi);
void setup(struct list *listem_head);
void yazdir(struct list *);
int main()
{
    struct list *listem1_head,*listem2_head,*listem3_head;
    long long int sayi1,sayi2 ;
    listem1_head=malloc(sizeof(struct list));//YERLERI AÇIYORUZ...
    listem2_head=malloc(sizeof(struct list));
    listem3_head=malloc(sizeof(struct list));
    setup(listem1_head);//YUKLUYORUZ...
    setup(listem2_head);
    setup(listem3_head);
    printf("Ilk    sayiyi giriniz  :");
    scanf("%lld",&sayi1);
    printf("Ikinci sayiyi giriniz  :");
    scanf("%lld",&sayi2);
    sayi_at(listem1_head,sayi1);
    sayi_at(listem2_head,sayi2);
    sayilari_carp(listem1_head,listem2_head,listem3_head);
    yazdir(listem3_head);
    return 0;
}
void setup(struct list *listem_head)
{
    listem_head->next_list=NULL;
    listem_head->pre_list=NULL;
}
void sayilari_carp(struct list *list1,struct list *list2,struct list *list3)
{
    struct list *iterator1,*iterator2,*iterator3;
    iterator1=list1;
    iterator2=list2;
    iterator3=list3;
    long long int toplam=0;
    while(iterator2->next_list!=NULL)
    {
        iterator2=iterator2->next_list;
    }
    long long int m=1;//Liste 2 deki her eleman degiþiminde toplam sayiyi bir basamak arttiriyor , liste3 teki bastan itibaren basamak katlarini 1,10,100... diye arttirma amaçli ki sonradan tekrar islem yapmayalim diye.
    while(iterator2->pre_list!=NULL)//iterator 2deki elemanlar bitene kadar.
    {
        long long int sayi =0;//her iterator 2 (2. liste) elemani degiþiminde toplam sayiyi tutup sonra 3. listeye pushlamamiz için
        long long int k =1;//bu ise her iterator 1 (1.liste) elemani degisiminde basamak katlarini 1,10,100,1000... diye arttirabilmek için , bir nevi küçük çarpma islemi.
        while(iterator1->next_list!=NULL)
        {
            iterator1=iterator1->next_list;
        }
        while(iterator1->pre_list!=NULL)
        {
            sayi += iterator1->sayi*iterator2->sayi*k;//Her 1. Liste(iterator1) elemani degisiminde soldan saga sayilarin basamak katlarini 10 ar  arttirmaya yarar k degiskeni. teker teker list1 ve 2 (it1,it2) nin o anki konumunu çarpar ve list1 deki elemanin almasi gereken katsayiyla  çarpar(k) . örnek olarak 21*34 te 4 ile 2 yi çarparken k=10 olacaktir .
            iterator1=iterator1->pre_list;
            k*=10;
        }
        push(list3,sayi*m);
        m*=10;//3. listenin (iterator 3) ün yukardan asagi dogru basamak katlarini 10 un katlari þeklinde arttirmaya yarar.
        iterator2=iterator2->pre_list;
    }
    while(iterator3->next_list!=NULL)//iterator3'ü 3. listenin sonuna tasidik.
        {
            iterator3=iterator3->next_list;
        }
    long long int k=1;
    while(iterator3->pre_list!=NULL)//3. listedeki sayilari teker teker toplatýp toplam degiskenine atiyoruz.
    {
        toplam+=iterator3->sayi;
        iterator3=iterator3->pre_list;
    }
    list3->sayi=toplam;
}
void sayi_at(struct list *listem_head,long long int sayi)//Sayilari rakamlarina ayirip listelere atmak icin.
{
    long long int basamak_say=1;
    long long int i =10;
    long long int k =1;
    long long int current;
    listem_head->next_list=NULL;
    while(sayi%i!=sayi)//Eger sayi tek basamakli degilse ice girip basamak sayacak.
    {
        basamak_say++;
        i*=10;
    }
   for( i =0;i<basamak_say-1;i++)//en soldaki yani en büyük basamak kat sayisina sahip rakami bulmak için basamak sayisinin bir eksigi kadar k yi katlarina bölüyoruz. mesela 123 sayisi elimizde ise ilk almak istedigimiz sayi =1 , bunun için de k yi 100 yapiyorum ve ilerde 123%100 = 23 sayisini 123 ten çikararak 123-23 =100 , daha sonra k ya bölerek 100/100=1 , ilk rakamimi elde ediyorum.
    {
        k*=10;
    }
    while(k!=1)
    {
        current=(sayi-sayi%k)/k;//üstte bahsettigim olay.
        push(listem_head,current);//rakami pushluyorum.
        sayi-=k*(current);//çikartmayi yapyoruz mesela 123 ise ilk sayimiz döngümüz bir kez dönünce 123-100 =23 sayisiyla isleme devam etmek istiyoruz , üstte current =1 ve k ise =100.
        k/=10;//k yi bölüyoruz.
    }
    push(listem_head,sayi);//istedigimize ulasinca son kalan rakami da pushluyoruz.
}
void push(struct list *liste_head,long long int sayi)
{
    struct list *new_node=(struct node*)malloc(sizeof(struct list));//Casting yaptık.
    struct list *iterator;//Kaydirma işleminde kullancagiz
    iterator=liste_head->next_list;//Bir sonraki listesine atiyoruz iterator'u , liste_head'in.
    new_node->sayi=sayi;
    if(liste_head->next_list==NULL)
    {
        liste_head->next_list=new_node;
        new_node->next_list=NULL;
        new_node->pre_list=liste_head;
    }
    else{
            while(iterator->next_list!=NULL)
            {
                iterator=iterator->next_list;
            }
            iterator->next_list=new_node;
            new_node->next_list=NULL;
            new_node->pre_list=iterator;
        }
}
void yazdir(struct list *liste_head)
{
    struct list *iterator=liste_head->next_list;
    long long int list=1;//Liste elemanlarinin sirasini belli etmek için.
    printf("\n  Carpma Islemindeki LL3 Icindeki Islemler\n  ----------------------------------------\n  |");
    while(iterator!=NULL)
    {
        printf("\n  |%5lld. LL3 Sayisi : %-23lld",list,iterator->sayi);
        list++;
        iterator=iterator->next_list;
    }
    printf("\n  |\n  ----------------------------------------\n\n\n    SONUC\n    --------------------\n    |%-3lld|\n    --------------------",liste_head->sayi);
}
