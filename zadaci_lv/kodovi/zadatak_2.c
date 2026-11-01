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

int main(){

    person head={ .name={0},
    .lastName={0},
    .birthYear=0,
    .next=NULL,
    };
    position p=&head;

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

    freeList(p);

    

}