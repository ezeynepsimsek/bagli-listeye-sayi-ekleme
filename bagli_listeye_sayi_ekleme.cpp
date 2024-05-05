#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int veri;
    struct Node* onceki;
    struct Node* sonraki;
} Dugum;

void siraEkle(Dugum** bas, int veri) {
    Dugum* yeniDugum = (Dugum*)malloc(sizeof(Dugum));
    yeniDugum->veri = veri;
    yeniDugum->onceki = NULL;
    yeniDugum->sonraki = NULL;

    if (*bas == NULL) {
        *bas = yeniDugum;
    } else if (veri <= (*bas)->veri) {
        yeniDugum->sonraki = *bas;
        (*bas)->onceki = yeniDugum;
        *bas = yeniDugum;
    } else {
        Dugum* simdiki = *bas;
        while (simdiki->sonraki != NULL && simdiki->sonraki->veri < veri) {
            simdiki = simdiki->sonraki;
        }
        yeniDugum->sonraki = simdiki->sonraki;
        if (simdiki->sonraki != NULL) {
            simdiki->sonraki->onceki = yeniDugum;
        }
        yeniDugum->onceki = simdiki;
        simdiki->sonraki = yeniDugum;
    }
}

void listeyiGoster(Dugum* bas) {
    if (bas == NULL) {
        printf("Liste bos.\n");
        return;
    }

    printf("Liste elemanlari: ");
    while (bas != NULL) {
        printf("%d ", bas->veri);
        bas = bas->sonraki;
    }
    printf("\n");
}

void listeTemizle(Dugum** bas) {
    Dugum* simdiki = *bas;
    while (simdiki != NULL) {
        Dugum* temp = simdiki;
        simdiki = simdiki->sonraki;
        free(temp);
    }
    *bas = NULL;
}

int main() {
    Dugum* bas = NULL;
    int veri;
    char devam;

    printf("Tam sayilari sirali olarak girin (Cikis icin x girin):\n");

    do {
        printf("Bir tam sayi girin: ");
        if (scanf("%d", &veri) == 1) {
            siraEkle(&bas, veri);
        } else {
            scanf(" %c", &devam);
            if (devam == 'x' || devam == 'X') {
                break;
            } else {
                printf("Gecersiz giris. Devam etmek icin bir tam sayi girin veya 'x' tusuna basin.\n");
            }
        }
    } while (1);

    listeyiGoster(bas);

    listeTemizle(&bas);

    return 0;
}

