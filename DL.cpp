#include "DL.h"

DancingLinks::DancingLinks(){
	isSolved=false;
	HeadNode=&Head;	

}

void DancingLinks::coverCol(Node* col){
	col->l->r=col->r;
	col->r->l=col->l;
	for(Node* nv=col->d; nv!=col; nv = nv->d){
		for(Node* nh=nv->r; nh!=nv; nh = nh->r){
			nh->d->u = nh->u;
			nh->u->d = nh->d;

			nh->head->size--;
		}
	}
}

void DancingLinks::uncoverCol(Node* col){
	col->l->r=col;
	col->r->l=col;

	for(Node* nv=col->u; nv!=col; nv = nv->u){
		for(Node* nh=nv->l; nh!=nv; nh = nh->l){
			nh->d->u = nh;
			nh->u->d = nh;

			nh->head->size++;
		}
	}
}

bool DancingLinks::search(int sc,int **sudoku){
	if(HeadNode->r==HeadNode){
		return isSolved=true;
	}

	Node* col=HeadNode->r;
	for(Node* nh=col->r;nh!=HeadNode;nh=nh->r)
		if(nh->size < col->size)
			col=nh;

	coverCol(col);

	for(Node* nv=col->d;nv!=col;nv=nv->d){
		for(Node* nh=nv->r;nh!=nv;nh=nh->r){
			coverCol(nh->head);
		}

		if(search(sc+1,sudoku)){
			sudoku[nv->rowEl[1]-1][nv->rowEl[2]-1]=nv->rowEl[0];
			return true;
		}

		for(Node* nh=nv->l;nh!=nv;nh=nh->l){
			uncoverCol(nh->head);
		}
	}

	uncoverCol(col);

	return false;
}