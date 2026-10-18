#include<stdio.h>
#include<stdlib.h>

typedef struct _person* position;

typedef struct _person{
    -data
    position next;
}person;

int insertAfter(position p, position newP){
    newP->next=p->next;
    p->next=newP
}

int insertBegin(char* ime, char* prezime, int godine, position head){
    position newPerson=NULL;
    newPerson=(position)malloc(sizeof(person));
    newPerson->year=godine;
    strcpy(newPerson->name, ime);
    newPerson->next=NULL;
    insertAfter(head,newPerson);
}

int insertEnd(char* ime, char*prezime, int god){
    position newP=NULL;
    newP=(position)malloc(sizeof(person));
    newP->year=god;
    strcpy(newP->name,ime);
    newP->next=NULL;
    while(p->next!=NULL)
    p=p->next;
    insertAfter(p,newP);
}

position findLastName(char* prezime, position p){
    for(p=p->next;p!=NULL;p=p->next)
    if strcmp(p->LName, prezime)==0;
    return p;
}

int printList(position p){
    while(p!=NULL)
    printf("");
    p=p->next;
}

int deletePerson(char* prezime, position p){
//pomocni pokazivac current
position curr=p->next
position prev=p;
while(prev->next!=curr)
prev=prev->next;
prev->next=curr->next;
//ili sa 2 nexta(samo sa 1 pokazivacem)(prev->next=prev->next->next?)
curr=findLastName(prezime, p);
free(curr);}

int main(){
    person head={.name={0}
    .LName=`\0`
    .year=0
    .next=NULL};
    position p=&head;



}