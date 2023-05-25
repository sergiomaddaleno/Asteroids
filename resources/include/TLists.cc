

enum TPosition{
    previous,  //To leave a pointer on the node prior to the one located in the search and to be able to delete
    actual     //To leave a pointer over the node located in the search 
};

struct TNode{
	TBullet info;
	TNode *prox;
};

struct TNodeEnemies{
	TEnemies info;
	TNodeEnemies *prox;
};


#define TList TNode
#define TListEnemies TNodeEnemies

void CreateList(TNode **List){
	*List=nullptr;
}

void CreateListEnemies(TNodeEnemies **List){
	*List=nullptr;
}


bool IsemptyList(TNode *List){
    return (List==nullptr);
}

bool IsemptyListEnemies(TNodeEnemies *List){
    return (List==nullptr);
}

short InsertList(TNode **List, TBullet value){
    TNode *newnode;
    
    if((newnode=(TNode*)malloc(1*sizeof(TNode)))==nullptr){
        //no memory
        return 0;
    } else{
            //there is memory
            newnode->info=value;
            newnode->prox=nullptr;
             if(IsemptyList(*List)){
                *List=newnode;
             }else{
                    newnode->prox=*List;
                    *List=newnode;
             }
             return 1;
    }          
}

short InsertListEnemies(TNodeEnemies **List, TEnemies value){
    TNodeEnemies *newnode;
    
    if((newnode=(TNodeEnemies*)malloc(1*sizeof(TNodeEnemies)))==nullptr){
        //no memory
        return 0;
    } else{
            //there is memory
            newnode->info=value;
            newnode->prox=nullptr;
             if(IsemptyListEnemies(*List)){
                *List=newnode;
             } else{
                    newnode->prox=*List;
                    *List=newnode;
             }
             return 1;
    }          
}


//Ej. if index = 3, returns a pointer to a list to the third element of the list
TNode *IndexaList(TNode *List,int index){ 
    TNode *p;

    if(index>=0 && !IsemptyList(List)){
      p=List;
      for(int i=0;p->prox!=nullptr && i<index;i++){
        p=p->prox;
      }
      return p;
    }
    else return nullptr;
}

//search a value in the list, if pos = previous returns the pointer to the previous node
TNode *SearchList(TNode *List, TPosition pos){ 

    bool found=false;
    TNode *p=List;

    if(!IsemptyList(List)){
        do{
            switch(pos){//We stop located on the searched or on the previous
                case   actual:found=(p->info.firstbullet==true); break;
                case previous:found=(p->prox->info.firstbullet==true); break;
            }
            if(!found) p=p->prox;//when found, pointer not changed
        }while(!found && p!=nullptr);
        return p;//No found p = NULL
    }else{
        return nullptr;
    }
}  

void DeleteFromListBullet(TNode **p, int key) 
{ 
    TNode *temp = *p, *q; 
  
    //if head node holds the key to be deleted 
    if (temp != NULL && temp->info.countForward == key){ 
        *p = temp->prox; 
        free(temp);  
        return; 
    } 
  
    //search for the key to be deleted, keep track of the previous node 
    while (temp != NULL && temp->info.countForward != key){ 
        q = temp; 
        temp = temp->prox; 
    } 
  
    if (temp == NULL) 
        return; 
  
    //unlink the node from list 
    q->prox = temp->prox; 
  
    free(temp);
}

void DeleteFromListEnemy(TNodeEnemies **p, int key) 
{ 
    TNodeEnemies *temp = *p, *q; 
  
    //if head node itself holds the key to be deleted 
    if (temp != NULL && temp->info.countHit == key){ 
        *p = temp->prox;   // Changed head 
        free(temp);        //free old head 
        return; 
    } 
  
    //search for the key to be deleted, keep track of the previous node 
    while (temp != NULL && temp->info.countHit != key){ 
        q = temp; 
        temp = temp->prox; 
    } 
  
    //if key was not present in linked list 
    if (temp == NULL) 
        return; 
  
    //unlink the node from linked list 
    q->prox = temp->prox; 
  
    free(temp);
}
