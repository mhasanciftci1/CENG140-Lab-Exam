#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

#include "lab4.h"

/*
    This function calculates the final position of an object on
    a 1D line with reading:
        force   (N)
        mass    (kg)
        gravity (kg/ms^2)
        f_Coeff (no unit)
        time    (s)
    from stdin according to the description and prints the final position
    as it is instructed.
*/
void CalculatePos()
{
    float force,mass,gravity,f_Coeff,time1,frictionforce,acceleration,position;
    scanf("%f %f %f %f %f",&force,&mass,&gravity,&f_Coeff,&time1);
    frictionforce=mass*gravity*f_Coeff;
    if(frictionforce>force){
        printf("The position is 0.00");
    }
    else{
        acceleration=(force-frictionforce)/mass;
        position=(1.0/2.0)*acceleration*pow(time1,2);
        printf("The position is %.2f",position);
    }
    /* Write Your Code Here */
}

/*
    Transposes the given nxn matrix
    mat -> nxn matrix given as a 1D array (row-major)
    n   -> size of one dimension
*/
void TransposeSquareMatrix(int* mat, int n)
{
    int i=0,j=0;
    int* tempmat=(int*)malloc(sizeof(mat));
    while(i<n){
        j=0;
        while(j<n){
            tempmat[j*n+i]=mat[i*n+j];
            j++;
        }
        i++;
    }
    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            mat[i*n+j]=tempmat[i*n+j];
        }
    }
    /* Write Your Code Here */
}


/*
    This function traverses shipment nodes
    according to the rules in the description
*/
void ProcessShipment(char* Username,
                          float DistanceLimit,
                          StationNode* HeadNode,
                          Response* Resp)
{
    double distance;
    int stationcounter=1;
    StationNode* controllernode;
    controllernode=HeadNode;
    strcpy(Resp->username,Username);
    while(controllernode->next!=NULL){
        distance +=sqrt(fabs(pow((controllernode->coordX - controllernode->next->coordX),2)+pow((controllernode->coordY - controllernode->next->coordY),2)));
        stationcounter++;
        controllernode=controllernode->next;
    }
    if(distance>DistanceLimit){
        Resp->data.error.code='D';
    }
    else{
        Resp->data.success.stationCount=stationcounter;
        Resp->data.success.totalDistance=distance;
    }
    /* Write Your Code Here */
}


/*
    This function reverses a linked list without creating
    a new one
*/
void ReverseLinkedList(LinkedList* list)
{
    ListNode* controller;
    ListNode* temp1;
    ListNode* temp2;
    controller=list->head;
    temp1=controller->next;
    controller->next=NULL;
    while(temp1!=NULL){
        temp2=temp1->next;
        temp1->next=controller;
        controller=temp1;
        temp1=temp2;
    }
    list->head=controller;
    /* Write Your Code Here */
}

/*
    This function splits the given circular linked list into
    two halves. If the list is not equally splitted, the first
    list gets less nodes.
*/
CircularLLs* SplitCircularLLs(CircularLLNode* head)
{
    CircularLLs* headers=(CircularLLs*)malloc(sizeof(CircularLLs));
    CircularLLNode* controller;
    CircularLLNode* secondcontroller;
    int counter=1,firstlength,i=0;
    controller=head;
    controller=controller->next;
    while(controller!=head){
        counter++;
        controller=controller->next;
    }
    controller=head;
    firstlength=counter/2;
    headers->head1=head;
    secondcontroller=headers->head1;
    for(i=1;i<firstlength;i++){
        secondcontroller=secondcontroller->next;
    }
    
    controller=secondcontroller->next;
    secondcontroller->next=headers->head1;
    headers->head2=controller;
    for(i=firstlength+1;i<counter;i++){
        controller=controller->next;
    }
    controller->next=headers->head2;
    /* Write Your Code Here */
    return headers;
}