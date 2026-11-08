#include<stdio.h>
#include<stdlib.h>


typedef struct Stack* position;

typedef struct Stack {
    int broj;
    position next;
}stack;


int push(position head, int broj);
int pop(position head, char znak);
int izbrisiStog(position head);


int main(){
    stack head={0, NULL};

    FILE* fp= fopen("postfiks.txt", "r");
    if(!fp){
        printf("Greska pri otvaranju datoteke postfiks.txt!\n");
        return -1;
    }

    int broj;
    char znak;


   while(fscanf(fp, " %c", &znak)!=EOF){
        if (fscanf(fp, "%d", &broj)==1){
            if(push(&head, broj)!=0){
                fclose(fp);
                return -1;
            }
        }
        else if (fscanf(fp, " %c", &znak)==1){
            if(pop(&head, znak)!=0){
                fclose(fp);
                return -1;
            }
        }

   }




        fclose(fp);

    printf("Rezultat: %d\n", head.next->broj);
    
    if(izbrisiStog(&head)!=0)
        return -1;
    return 0;
}
    





int push(position head, int broj){
    position newB= malloc(sizeof(stack));
    if(!newB){
        printf("Greska pri alociranju memorije!\n");
        return -1;
    }
    newB->broj= broj;
    newB->next= head->next;
    head->next= newB;

    return 0;
}

int pop(position head, char znak){

    position p,q;
    
    if(head->next==NULL || head->next->next==NULL){
        printf("Greska pri pop operaciji!\n");
        return -1;
    }

    p= head->next;
    q= p->next;

    switch(znak){
        case '+':
            p->broj= p->broj + q->broj;
            break;
        case '-':
            p->broj= p->broj - q->broj;
            break;
        case '*':
            p->broj= p->broj * q->broj;
            break;
        case '/':
            if(q->broj==0){
                printf("Greska pri dijeljenju s nulom!\n");
                return -1;
            }
            p->broj= p->broj / q->broj;
            break;
        default:
            printf("Nepoznata operacija!\n");
            return -1;
    }

    int rez=p->broj;
    head->next=q->next->next;
    
    free(q);
    free(p);

    push(head, rez);
    return 0;

}

int izbrisiStog(position head){
    position temp;

    while(head->next!=NULL){
        temp = head->next;
        head->next=temp->next;
        free(temp);
    }
    return 0;
}