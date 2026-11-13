#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char hoten[30];
    int masv;
    float d1, d2, d3;
} Data;

typedef struct tagNode {
    Data infor;
    struct tagNode *link;
} Node;

typedef struct {
    Node *pHead;  
    Node *pTail;
    int spt;
} LList;

/////////////////////////////////////
void initList(LList *L) {
    L->pHead = NULL;
    L->pTail = NULL;
    L->spt = 0;
}

/////////////////////////////////////
int emptyList(LList L) {
    return (L.spt == 0); 
}

/////////////////////////////////////
void insert_Head(LList *L, Data x) {
    Node *pp = (Node*) malloc(sizeof(Node));
    pp->infor = x;
    pp->link = NULL;
    if(emptyList(*L)) {
        L->pHead = pp;
        L->pTail = pp;
    } else {
        pp->link = L->pHead;
        L->pHead = pp;
    }
    L->spt++;
}

/////////////////////////////////////
void insert_Tail(LList *L, Data x) {
    Node *pp = (Node*) malloc(sizeof(Node));
    pp->infor = x;
    pp->link = NULL;
    if(emptyList(*L)) {
        L->pHead = pp;
        L->pTail = pp;
    } else {
        L->pTail->link = pp; 
        L->pTail = pp;       
    }
    L->spt++;
}

/////////////////////////////////////
void insert_After(LList *L, int target_masv, Data x) {
    Node *p = L->pHead;
    // Find the node with matching masv
    while (p != NULL && p->infor.masv != target_masv) {
        p = p->link;
    }
    
    if (p != NULL) {
        Node *pp = (Node*) malloc(sizeof(Node));
        pp->infor = x;
        pp->link = p->link;
        p->link = pp;
        
        // If we inserted after the tail, update pTail
        if (p == L->pTail) {
            L->pTail = pp;
        }
        L->spt++;
        printf("Them thanh cong!\n");
    } else {
        printf("Khong tim thay sinh vien co ma %d trong danh sach!\n", target_masv);
    }
}

///////////////////////////////////////
void nhap(Data *x){
    printf("Nhap ma sv: ");
    scanf("%d", &(x->masv));
    if(x->masv > 0){
        getchar(); // Clear newline buffer
        printf("Nhap ho ten: ");
        fgets(x->hoten, sizeof(x->hoten), stdin);
        x->hoten[strcspn(x->hoten, "\n")] = 0; 
        
        printf("Nhap diem mon 1: ");
        scanf("%f", &(x->d1));
        printf("Nhap diem mon 2: ");
        scanf("%f", &(x->d2));
        printf("Nhap diem mon 3: ");
        scanf("%f", &(x->d3));
    }
}

void in(Data x){
    printf("Ten: %s | Ma: %d | Diem 1: %.2f | Diem 2: %.2f | Diem 3: %.2f\n",  
            x.hoten, x.masv, x.d1, x.d2, x.d3);
}

void processList(LList L){
    if (emptyList(L)) {
        printf("Danh sach rong!\n");
        return;
    }
    Node *pp = L.pHead;
    while(pp != NULL){
        in(pp->infor); 
        pp = pp->link;
    }
}

void freeList(LList *L) {
    Node *p = L->pHead;
    while (p != NULL) {
        Node *temp = p;
        p = p->link;
        free(temp);
    }
    initList(L);
}

/////////////////////////////////////////
int main(){
    LList L;
    int kt = 0;
    Data x;
    initList(&L); 
    do{
        printf("\n=== Chuong trinh lam viec voi DSLK don SV ===\n");
        printf("1: Them nut vao dau danh sach\n");
        printf("2: Them nut vao cuoi danh sach\n");
        printf("3: Them nut vao sau mot nut khac trong danh sach\n");
        printf("9: Duyet ds\n");
        printf("0: Thoat\n");
        printf("Moi ban chon: ");
        int chon;
        scanf("%d", &chon);
        switch(chon){
            case 1: 
                printf("Nhap thong tin sv can them:\n");
                nhap(&x);
                if(x.masv > 0) 
                    insert_Head(&L, x);
                break;
            case 2:    
                printf("Nhap thong tin sv can them:\n");
                nhap(&x);
                if(x.masv > 0) 
                    insert_Tail(&L, x);
                break;
            case 3: {
                if (emptyList(L)) {
                    printf("Danh sach dang rong, khong the chen sau\n");
                    break;
                }
                int target;
                printf("Nhap ma sv cua nut can chen !sau! no: ");
                scanf("%d", &target);
                printf("Nhap thong tin sinh vien moi:\n");
                nhap(&x);
                if(x.masv > 0) 
                    insert_After(&L, target, x);
                break;
            }
            case 9: 
                processList(L);
                break;    
            case 0: 
                freeList(&L);
                printf("Bye bye!\n");
                kt = 1;
                break;
            default:
                printf("Lua chon khong hop le. Vui long chon lai!\n");
        }
    } while(kt == 0);
    return 0;
}
