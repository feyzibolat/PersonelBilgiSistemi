#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

struct personel
{
    char isim[100];
    char TCKimlikNo[12];
    char telefon[12];
    char eposta[100];
    char adres[100];
 }per;

int kayitsayisi=0;
void kayitSay();
void secimYap();
void kayitEkle();
void kayitListele();
void kayitDuzenle(char isim[]);
void TCileBul(char tc[]);
void IsimileBul(char isim[]);
void kayitSil(char siltc[]);

int main()
{
    setlocale(LC_ALL, "Turkish");
    kayitSay();
    secimYap();
    return 0;
}

void kayitSay()
{
    FILE *fp;
    fp= fopen("personel.txt","rb");
    if(fp != NULL)
    {
        int sayac=0, kayit=0;
        while((fgetc(fp))!=EOF)
        {
            sayac++;
         if(sayac==sizeof(per))
         {
             kayit++;
             sayac=0;
         }
        }
        kayitsayisi=kayit;

        if(kayitsayisi<=0)
            printf("Kayýt Bulunamadi! Lutfen Yeni Personel Ekleyin!\n");
        else
            printf("%d adet Personel kaydý bulundu!\n",kayitsayisi);

    }
    else
    {
        printf("Dosya Bulunamadi!\n");
    }
    fclose(fp);

}

void secimYap()
{
    char aranantc[12];
    char arananisim[100];
    char duzenleisim[100];
    char silinecektc[12];

    printf("\n\n----ÝÞLEMLER----\n");
    printf("[1] Kayýt Ekle\n");
    printf("[2] Personel Listele\n");
    printf("[3] Kaydý Düzenle\n");
    printf("[4] TC Kimlik No ile Kayýt Bul\n");
    printf("[5] Ýsim ile Kayýt Bul\n");
    printf("[6] Kayýt Sil\n");
    printf("[0] Çýkýþ\n\n");

    printf("Lütfen Seçim Yapýnýz >>> ");
    int secim;
    scanf("%d",&secim);

    switch(secim)
    {
        case 0:
            printf("Güle güle");
            exit(1); break;
        case 1:
            kayitEkle(); break;
        case 2:
            if(kayitsayisi!=0)
            {
                kayitListele();
            }
            else
            {
                system("CLS");
                printf("Personel Kaydý Bulunamadý. Lutfen Kayýt Yapýnýz!\n\n");
                secimYap();
            }
            break;
        case 3:
            printf("Lütfen Düzenlenecek Kayda ait Ýsim giriniz >>> ");
            scanf("%s",duzenleisim);
            kayitDuzenle(duzenleisim);
            break;
        case 4:
            printf("Lütfen Aranacak TC giriniz >>> ");
            scanf("%s",aranantc);
            TCileBul(aranantc);
            break;
        case 5:
            printf("Lütfen Aranacak Ýsim giriniz >>> ");
            scanf("%s",arananisim);
            IsimileBul(arananisim);
            break;
        case 6:
            printf("Lütfen Silinecek TC giriniz >>> ");
            scanf("%s",silinecektc);
            kayitSil(silinecektc);
            break;
        default:
                printf("HATA: Bilinmeyen bir deðer girdiniz!\n");
    }
}

void kayitEkle()
{
    system("CLS"); //ekran temizler

    FILE *fp;

    if((fp=fopen("personel.txt","a+")) != NULL)
    {
        kayitsayisi++;

        printf("Lütfen Personel ismini Giriniz >>> ");
        scanf("%s",per.isim);

        printf("Lütfen Personel TCKN Giriniz >>> ");
        scanf("%s",per.TCKimlikNo);

        printf("Lütfen Personel Telefon Giriniz >>> ");
        scanf("%s",per.telefon);

        printf("Lütfen Personel ePosta Giriniz >>> ");
        scanf("%s",per.eposta);

        printf("Lütfen Personel Adres Giriniz >>> ");
        scanf("%s",per.adres);

        fwrite(&per, sizeof(per), 1, fp);

        fclose(fp);

        system("CLS");
        printf("Personel Kaydý Baþarýyla Tamamlandý!\n\n");

        kayitSay();
        secimYap();




    }
}

void kayitListele()
{
        system("CLS");

        printf("*Personel Kayýtlarý*\n\n");

        FILE *fp;
        fp = fopen("personel.txt","rb");

        while((fread(&per, sizeof(per), 1, fp)) !=0)
        {
             printf("Ýsim: %s\n",per.isim);
             printf("TCKimlikNo: %s\n",per.TCKimlikNo);
             printf("Telefon: %s\n",per.telefon);
             printf("Eposta: %s\n",per.eposta);
             printf("Adres: %s\n",per.adres);
             printf("\n");
        }
        fclose(fp);

        kayitSay();
        secimYap();
}

void kayitDuzenle(char isim[100])
{
        system("CLS");
        FILE *fp;
        fp = fopen("personel.txt","rb");

        int sayac=0,bulunansayisi=0;
        while((fread(&per, sizeof(per), 1, fp)) !=0)
        {
            sayac++;
            if(strcmp(isim, per.isim)==0)
            {
                bulunansayisi++;
             printf("**** Bulunan Kayýt ****\n");
             printf("Ýsim: %s\n",per.isim);
             printf("TCKimlikNo: %s\n",per.TCKimlikNo);
             printf("Telefon: %s\n",per.telefon);
             printf("Eposta: %s\n",per.eposta);
             printf("Adres: %s\n",per.adres);
             printf("\n");

             }

            if (bulunansayisi==1)
            {
                break;
            }
        }
        fclose(fp);

        if(bulunansayisi<=0)
        {
            system("CLS");
            printf("Aranan Ýsim kaydý bulunamadý. Düzenlemek için Yeniden Ýsim ile Arama Yapmak Ýstermisiniz? (E/H) >>> ");
            if (toupper(getche())=='E')
            {
                char duzenlenecekisim[100];
                printf("\nLütfen Düzenlenecek Kayda ait Ýsim giriniz >>> ");
                scanf("%s",duzenlenecekisim);
                kayitDuzenle(duzenlenecekisim);
            }
        }
        else if (bulunansayisi==1)
        {
            printf("Bulunan Kaydý Düzenlemek Ýstediðinize Eminmisiniz? (E/H) >>> ");
            if (toupper(getche())=='E')
            {
                //Düzenleme Ýþlemi Baþ

                FILE *fp;
                fp = fopen("personel.txt","rb+");

                printf("\n\nLütfen Personelin YENÝ ismini Giriniz >>> ");
                scanf("%s",per.isim);

                printf("\nLütfen Personelin YENÝ TCKN Giriniz >>> ");
                scanf("%s",per.TCKimlikNo);

                printf("\nLütfen Personelin YENÝ Telefon Giriniz >>> ");
                scanf("%s",per.telefon);

                printf("\nLütfen Personelin YENÝ ePosta Giriniz >>> ");
                scanf("%s",per.eposta);

                printf("\nLütfen Personelin YENÝ Adres Giriniz >>> ");
                scanf("%s",per.adres);


                fseek(fp, (sayac - 1) * sizeof(per), SEEK_SET); // imleci ilgili kayýta getirdik.

                fwrite(&per, sizeof(per), 1, fp); // bas

                fclose(fp);


                //Düzenleme Ýþlemi Son

                system("CLS");
                kayitSay();
                printf("\n %s isimli personel kaydý baþarýyla düzenlenmiþtir!",isim);

            }
        }
        secimYap();
}

void TCileBul(char tc[12])
{
        system("CLS");

        FILE *fp;
        fp = fopen("personel.txt","rb");

        int bulunansayisi=0;
        while((fread(&per, sizeof(per), 1, fp)) !=0)
        {
            if(strcmp(tc, per.TCKimlikNo)==0)
            {
                bulunansayisi++;
            printf("****Bulunan Kayýt****\n");
             printf("Ýsim: %s\n",per.isim);
             printf("TCKimlikNo: %s\n",per.TCKimlikNo);
             printf("Telefon: %s\n",per.telefon);
             printf("Eposta: %s\n",per.eposta);
             printf("Adres: %s\n",per.adres);
             printf("\n");

            }
        }
        if(bulunansayisi<=0)
        {
            printf("Aranan TC kaydý bulunamadý!");
        }

        fclose(fp);
        secimYap();
}

void IsimileBul(char isim[100])
{
        system("CLS");

        FILE *fp;
        fp = fopen("personel.txt","rb");
        int bulunansayisi=0;
        while((fread(&per, sizeof(per), 1, fp)) !=0)
        {
            if(strcmp(isim, per.isim)==0)
            {
                bulunansayisi++;
            printf("****%d. Bulunan Kayýt****\n",bulunansayisi);
             printf("Ýsim: %s\n",per.isim);
             printf("TCKimlikNo: %s\n",per.TCKimlikNo);
             printf("Telefon: %s\n",per.telefon);
             printf("Eposta: %s\n",per.eposta);
             printf("Adres: %s\n",per.adres);
             printf("\n");

            }
        }
        if(bulunansayisi<=0)
            printf("Aranan Ýsim ile kayýt bulunamadý!");
        else
            printf("Bulunan Toplam Kayýt Sayýsý: %d",bulunansayisi);
        fclose(fp);
        secimYap();
}

void kayitSil(char siltc[12])
{
        system("CLS");

        FILE *fp;
        fp = fopen("personel.txt","rb");

        int bulunansayisi=0;
        while((fread(&per, sizeof(per), 1, fp)) !=0)
        {
            if(strcmp(siltc, per.TCKimlikNo)==0)
            {
                bulunansayisi++;
            printf("****Silinecek Kayýt****\n",bulunansayisi);
             printf("Ýsim: %s\n",per.isim);
             printf("TCKimlikNo: %s\n",per.TCKimlikNo);
             printf("Telefon: %s\n",per.telefon);
             printf("Eposta: %s\n",per.eposta);
             printf("Adres: %s\n",per.adres);
             printf("\n");

            }
        }
        fclose(fp);

        if(bulunansayisi<=0)
        {
            printf("Aranan TC kaydý bulunamadý. Silmek için Yeniden TC ile Arama Yapmak Ýstermisiniz? (E/H) >>> ");
            if (toupper(getche())=='E')
            {
                char silinecektc[12];
                printf("\nLütfen TC giriniz >>> ");
                scanf("%s",silinecektc);
                kayitSil(silinecektc);
            }
        }
        else if (bulunansayisi>0)
        {
            printf("Bulunan Kaydý Silmek Ýstediðinize Eminmisiniz? (E/H) >>> ");
            if (toupper(getche())=='E')
            {
                //Silme Ýþlemi Baþ

                FILE *fp;
                fp = fopen("personel.txt","rb");
                FILE *temp;
                temp = fopen("temp.txt","ab+");
                while((fread(&per, sizeof(per), 1, fp)) !=0)
                    {
                        if(strcmp(siltc, per.TCKimlikNo)==0)
                        {
                            continue; // eðer silinecek tc gelirse atla
                        }

                        fwrite(&per, sizeof(per), 1, temp);
                    }

                fclose(temp);
                fclose(fp);
                remove("personel.txt");
                rename("temp.txt","personel.txt");

                //Silme Ýþlemi Son
                system("CLS");
                kayitSay();
                printf("\n %s nolu TC Kayýtlardan Baþarýyla Silinmiþtir!",siltc);
            }
        }
        secimYap();
}
