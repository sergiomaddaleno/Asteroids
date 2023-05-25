
#define CreateStack CreateList
#define IsemptyStack IsemptyList
#define ShowStack Showlist
#define InsertStack InsertList

#define TStack TList

TStack *TopStack(TNode *list){

    return list;
}


TStack *ExtractLIFO(TNode **list){

	TNode *p;
	if(!IsemptyList(*list)){
		p=*list;
        *list=p->prox;
        return p;
	}else{ //if the list is empty, return a null pointer
	 	return nullptr;
    }
		   
}

TStack *ExtractFIFO(TNode **list){

	TNode *p=*list, *pAnt=nullptr, *p2Ant=nullptr;

	if(!IsemptyList(*list)){
    	while(p!=nullptr){ //loop through the list until it finds nullptr (the end)
        	pAnt = p;   //save the previous node pointer
			p2Ant=pAnt; //save the pointer of 2 previous nodes
			p=p->prox;
    	}
		p2Ant->prox=nullptr;
		return pAnt;

	}else{ //if the list is empty, return a null pointer
	 	return nullptr;
    }	   
}

void EmptyStack(TNode **list){

	TNode *p=*list, *pAnt=nullptr;
	while(p!=nullptr){
		pAnt=p; //save previous node to free
		p=p->prox;
		free(pAnt);
	}
	*list=nullptr;
}