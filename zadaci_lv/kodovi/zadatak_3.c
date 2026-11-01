#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct _osoba* position;

typedef struct _osoba{
    char name[20];
    char lastName[20];
    int birthYear;
    position next;
}person;

int insertAfter(position p, position newP){
    newP->next=p->next;
    p->next=newP;
    return 0;
}

int insertBeginning(position head, char* ime, char* prezime, int godina)
{
    position newPerson=NULL;
    newPerson=(position)malloc(sizeof(person));
    if(newPerson==NULL)
        return -1;
    newPerson->birthYear=godina;
    strcpy(newPerson->name, ime);
    strcpy(newPerson->lastName, prezime);
    newPerson->next=NULL;
    insertAfter(head, newPerson);
    return 0;
}

int ispisiListu(position head){
    position curr=head->next;
    while(curr!=NULL){
        printf("%s %s %d\n", curr->name, curr->lastName, curr->birthYear);
        curr=curr->next;
    }
    return 0;
}

int upisiUDatoteku(position head, char* filename){
    FILE* fp=fopen(filename, "w");
    if(fp==NULL){
        printf("Error opening file!\n");
        return -1;
    }
    position curr=head->next;
    while(curr!=NULL){
        fprintf(fp, "%s %s %d\n", curr->name, curr->lastName, curr->birthYear);
        curr=curr->next;
    }
    fclose(fp);
    return 0;
}

int citajIzDatoteke(position head, char* filename){
    FILE* fp=fopen(filename, "r");
    if(fp==NULL){
        printf("Error opening file!\n");
        return -1;
    }
    char ime[20], prezime[20];
    int godina;
    position osoba=NULL;

    while(fscanf(fp, "%s %s %d", ime, prezime, &godina)==3){
   /*      osoba=(position)malloc(sizeof(person));
    if(osoba==NULL)
        return -1; */
        insertEnd(ime, prezime, godina, head);
    }
   

    
    fclose(fp);
    return 0;
}

int insertEnd(char* ime, char* prezime, int godina, position p){
    position newPerson=NULL;
    newPerson=(position)malloc(sizeof(person));
    newPerson->birthYear=godina;
    strcpy(newPerson->name, ime);
    strcpy(newPerson->lastName, prezime);
    newPerson->next=NULL;
    while(p->next!=NULL){
        p=p->next;
    }
    insertAfter(p, newPerson);
    return 0;
}

position findLastName(char* prezime, position p){
    for(p=p->next; p!=NULL; p=p->next){
        if (strcmp(p->lastName, prezime)==0)
            return p;
    }
}

int deletePerson(char* prezime, position p){
    position curr=p->next;
    position prev=p;
    curr=findLastName(prezime, p);
    while (prev->next!=curr)
    prev=prev->next;
    prev->next=curr->next;
    free(curr);
    return 0;
    }

void freeList(position head){
    position curr = head->next;
    position next;

    while(curr != NULL){
        next = curr->next;
        free(curr);
        curr = next;
    }

    head->next = NULL;
}

int insertAfterElement(char* lastName, int godina, char* ime, char* prezime, position p){
    position newPerson=NULL;
    p=findLastName(lastName, p);
    newPerson=(position)malloc(sizeof(person));
    if(newPerson==NULL)
        return -1;
    newPerson->birthYear=godina;
    strcpy(newPerson->name, ime);
    strcpy(newPerson->lastName, prezime);
    newPerson->next=p->next;
    p->next=newPerson;
    return 0;
}

int insertBeforeElement(char* lastName, int godina, char* ime, char* prezime, position p){
    position newPerson=NULL;
    position prev=p;
    p=findLastName(lastName, p);
    while(prev->next!=p)
        prev=prev->next;
    newPerson=(position)malloc(sizeof(person));
    if(newPerson==NULL)
        return -1;
    newPerson->birthYear=godina;
    strcpy(newPerson->name, ime);
    strcpy(newPerson->lastName, prezime);
    newPerson->next=p;
    prev->next=newPerson;
    return 0;
}

int sortList(position head){
    position p=head->next;
    position sorted=NULL;
    position temp=NULL;

    if (head->next==NULL)
        return -1;

    while(p->next!=NULL){
        if(strcmp(p->lastName, p->next->lastName)>0){
            temp=p->next;
            p->next=temp->next;
            temp->next=p;
        }
        p=p->next;
    }
    return 0;
}


int main(){

    person head={ .name={0},
    .lastName={0},
    .birthYear=0,
    .next=NULL,
    };
    position p=&head;
    FILE* fp=fopen("datoteka.txt", "r");

    insertBeginning(p, "Lena", "Kragic", 2005);
    insertEnd("Tonka", "Skoko", 2006, p);
    insertEnd("Petra", "Petrovic", 2007, p);
    insertEnd("Nikola", "Nikolic", 1998, p);
    insertBeginning(p, "Jelena", "Jovanovic", 1999);
    insertEnd("Katija", "Reljanovic", 2006, p);
    insertEnd("Janko", "Jankovic", 1995, p);
    insertEnd("Petar", "Petrovic", 1985, p);
    

    ispisiListu(p);
    deletePerson("Nikolic", p);

    ispisiListu(p);

    upisiUDatoteku(p, "datoteka.txt");
    freeList(p);

    

}