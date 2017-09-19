#include "person.h"

PPerson PersonCreate(const char* name, const int age, const int id){
    // no NULL ptr
    if(name == NULL){
        return NULL;
    }
    // allocate Person
    PPerson newPerson = (PPerson)malloc(sizeof(Person));
    if(newPerson == NULL){
        return NULL;
    }
    // allocate space for Person's name
    newPerson->name = (char*)malloc(strlen(name)+1 * sizeof(char));
    if(newPerson->name == NULL){
        free(newPerson);
        return NULL;
    }
    // assign properties
    strcpy(newPerson->name, name);
    newPerson->age = age;
    newPerson->ID = id;
    return newPerson;
}

PElement clonePerson(const PElement person){
    // no NULL ptr
    if(person == NULL){
        return NULL;
    }
    // cast
    PPerson p = (PPerson)person;
    // create new Person and assign properties
    return (PElement)PersonCreate(p->name, p->age, p->ID);
}

void printPerson(const PElement person){
    // no NULL ptr
    if(person == NULL){
        return;
    }
    // cast
    PPerson p = (PPerson)person;
    // print the data
    printf("Name: %s, ID: %d, Age: %d\n", p->name, p->ID, p->age);
}

void destroyPerson(const PElement person){
    // no NULL ptr
    if(person == NULL){
        return;
    }
    // cast
    PPerson p = (PPerson)person;
    // free dynamic allocations
    free(p->name);
    free(p);
}

BOOL comparePersons(const PElement person1, const PElement person2){
    // no NULL ptrs
    if(person1 == NULL || person2 == NULL){
        return FALSE;
    }
    // casts
    PPerson p1 = (PPerson)person1;
    PPerson p2 = (PPerson)person2;
    // compare IDs
    return (p1->ID == p2->ID);
}