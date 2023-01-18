#ifndef LIST_H
#define LIST_H

#include "vendible.h"
#include <stdio.h>

typedef struct List{
	void* data;
	struct List* next; // определена за пределами структуры
} List;

List* List_push(List* root, void* data){
	if (root == NULL){
		List* list = (List*)malloc(sizeof(List));
		list -> data = data;
		list -> next = NULL;
		return list;
	}
	List* current = root;
	while(current-> next != NULL){
		current = current->next;
	}
	List* list = (List*)malloc(sizeof(List));
	list -> data = data;
	list -> next = NULL;
	current -> next = list;
	return root;
}


void* List_at(List* root, int id){
	List* current = root;
	int i = 0;
	while (current){
		if (i == id) return current->data;
		current = current->next;
		i++;
	}
	return NULL;
}

List* List_id(List* root, int id){
	List* current = root;
	int i = 0;
	while (current){
		if (i == id) return current;
		current = current->next;
		i++;
	}
	return NULL;
}

List* List_delete(List* root, int id){
	if (id==0){
		List* next = NULL;
		next = root->next;
		//Item_print((Item*)(next->data));
		free(root);
		root = NULL;
		//printf("new root - del: %p\n", next);
		return next;
	}
	List* current = root;
	List* prev;
	int i = 0;
	while(current != NULL){
		if(i == id){
			prev->next = current->next;
			free(current);
			return root;
		}
		prev = current;
		current = current->next;
		i++;
	}
	return root;
}

int List_count(List* root){
   // printf("new root _ cnt: %p\n", root);
	List* current = root;
	int i = 0;
	while(current != NULL){
		current = current-> next;
		i++;
	}
	return i;
}

List* List_revese(List* root){
    if(root == NULL){
        return root;
    }
    List* tmp = root->next;
    if(tmp == NULL){
        tmp->next = root;
        root->next = NULL;
        return tmp;
    }
    List* next = tmp->next;
    List* cur = NULL;
    tmp->next = root;
    root->next = NULL;
    while (next != NULL){
        cur = next;
        next = next->next;
        cur->next = tmp;
        tmp = cur;
    }
    return tmp;
}

List* List_insert(List* dist, List* src, int pos){
    if(pos == 0){
        src->next = dist;
        return src;
    }
    List* tmp = List_id(dist, pos-1);
    src->next = tmp->next;
    tmp->next = src;
    return dist;
}

#endif // LIST_H
