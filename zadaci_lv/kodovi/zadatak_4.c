#include<stdio.h>
#include<stdlib.h>

typedef struct poly *position;

typedef struct poly{
    int coef;
    int pow;
    position next;
} polynom;

int sortiraniUnos(position head, int coef, int pow);
int ucitajIzDatoteke(position head, const char *filename);
int zbrojiPolinome(position headF, position headS, position headZ);
int pomnoziPolinome(position headF, position headS, position headZ);
int izbrisiPolinom(position head);

int main() {

    polynom headF={0, 0, NULL};
    polynom headS={0, 0, NULL};
    polynom headZ={0, 0, NULL};

    if(ucitajIzDatoteke(&headF, "polinom1.txt")!=0)
    return -1;

    if(ucitajIzDatoteke(&headS, "polinom2.txt")!=0)
    return -1;

    if(zbrojiPolinome(&headF, &headS, &headZ)!=0)
    return -1;

    izbrisiPolinom(&headF);
    izbrisiPolinom(&headS);
    izbrisiPolinom(&headZ);

    return 0;
}

int sortiraniUnos(position head, int coef, int pow)
{
    position previous = head;
    position current = head->next;
    position newPoly;

    while (current != NULL && current->pow > pow){
        previous = current;
        current = current->next;
    }

    if (current !=NULL && current->pow == pow){
        current->coef=current->coef + coef;

        if (current->coef == 0){
            previous->next = current->next;
            free(current);
        }

        return 0;
    }
    newPoly = malloc(sizeof(polynom));  //moze i sizeof(*newPoly)
    if (newPoly == NULL)
        return -1;

    newPoly->coef = coef;
    newPoly->pow = pow;
    newPoly->next = current;
    previous->next = newPoly;
    return 0;
}

int ucitajIzDatoteke(position head, const char* filename){
    FILE* fp = fopen(filename, "r");
    int coef;
    int pow;

    if (fp == NULL){
        printf("Greska pri otvaranju datoteke %s!\n", filename);
        return -1;
    }

    while (fscanf(fp, "%d %d", &coef, &pow) == 2){
        if(sortiraniUnos(head, coef, pow)!=0){
            fclose(fp);
            return -1;
        }
    }
    fclose(fp);
    return 0;
}

int zbrojiPolinome(position headF, position headS, position headZ){
    position current;

    for(current= headF->next; current!=NULL; current=current->next){
        
        if(sortiraniUnos(headZ, current->coef, current->pow)!=0)
            return -1;
    }
    for(current= headS->next; current!=NULL; current=current->next){
        
        if(sortiraniUnos(headZ, current->coef, current->pow)!=0)
            return -1;
    }
    return 0;
}

int pomnoziPolinome(position headF, position headS, position headZ){

    
    position currentF;
    position currentS;


    for(currentF = headF->next; currentF!=NULL; currentF= currentF->next){
        for(currentS=headS->next; currentS!=NULL; currentS=currentS->next){
            if(sortiraniUnos(headZ, currentF->coef * currentS->coef, currentF->pow + currentS->pow)!=0)
                return -1;
        }
    }
    return 0;
}
int izbrisiPolinom(position head){

    position current= head->next;
    position next;

    while(current!=NULL){
        next= current->next;
        free(current);
        current= next;
    }

    head->next= NULL;

    return 0;
}