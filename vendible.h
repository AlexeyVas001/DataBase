#ifndef VENDIBLE_H
#define VENDIBLE_H
#include <stdio.h>

typedef struct Item{
	int id;
	char partnumber[30];
	char parttype[10];
	float feature;
	char footprint[10];
	float price;
	int number;
} Item;

int Item_fill(Item* item, int id, char* pn, char* pt, float ftr, char* ftp, float prc, int cnt){
		if (item == NULL){
            return (1);
		}
		item->id = id;
        strcpy(item->partnumber, pn);
        strcpy(item->parttype, pt);
        item->feature = ftr;
        strcpy(item->footprint, ftp);
        item->price = prc;
        item->number = cnt;
		return (0);
}

Item* Item_create(int id, char* pn, char* pt, float ftr, char* ftp, float prc, int cnt){
	Item* item = (Item*)malloc(sizeof(Item));
	Item_fill(item, id, pn, pt, ftr, ftp, prc, cnt);
	return item;
}

void Item_delete(Item* item){
	if (item == NULL) return;
    free(item);
}


void Item_print(const Item* const item){
	if (item == NULL) return;
	printf("item id : %d;\n partnumber : %s;\n parttype : %s\n feature : %0.3f\n, footprint : %s\n, price : %0.3f\n, balance : %d\n",
        item->id, item->partnumber, item->parttype, item->feature, item->footprint, item->price, item->number);
}
void Item_SaveToFile(FILE* file, Item* item){
	if (item == NULL) return;
	fprintf(file, "%d\t%s\t%s\t%0.3f\t%s\t%0.3f\t%d\r\n",
        item->id, item->partnumber, item->parttype, item->feature, item->footprint, item->price, item->number);
}

#endif
