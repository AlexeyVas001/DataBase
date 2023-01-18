#ifndef AP_H
#define AP_H

#include <stdio.h>
#include "list.h"
#include "user.h"
#include "vendible.h"
#include "query.h"

void App_deleteAllItemsFromList(List* root){
		for (int i = List_count(root)-1; i >= 0 ; i--){
		Item* item = (Item*)List_at(root, i);
		if (item != NULL){
			Item_delete(item);
			root = List_delete(root, i);
		} else{
			break;
		}
	}
}

void App_printAllItemsFromList(List* root){
       // printf("new root - prt: %p\n", root);
        //printf("new root: %d\n", List_count(root));
		printf("+------------+--------------+---------+---------+-----------+--------+---------+\n");
		printf("|     id     |     name     | type    | feature | footprint | Price  | Balance | \n");
		printf("+------------+--------------+---------+---------+-----------+--------+---------+\n");
		for (int i = 0; i < List_count(root) ; i++){
		Item* item = (Item*)List_at(root, i);
		printf("|%12d|%14s|%9s|%9f|%11s|%7.2f|%9d|\n", item->id, item->partnumber, item->parttype, item->feature, item->footprint,item->price, item->number);
		}
		printf("--------------------------------------------------------------------------------\n");
}


int App_showMenu(){
	printf("!!!!!MENU!!!!!\n");
	printf("1. Print all items\n");
	printf("2. Add new items\n");
	printf("3. Delete items\n");
	printf("4. AlphabetSort\n");
	printf("5. Save to File\n");
    printf("6. CreateChart\n");
    printf("7. Filter\n");
    printf("8. Exit\n");
	printf("\n");
	printf("Input action [1-8]\n");
	int id;
	scanf("%d", &id);
	return id;
}

void App_SaveToFile(FILE* file, List* root){
		for (int i = 0; i < List_count(root) ; i++){
		Item* item = (Item*)List_at(root, i);
		Item_SaveToFile(file, item);
		}
}

void App_PrintToFile(FILE* file, List* root){
    //App_SaveToFile(file, root);
        for (int i = 0; i < List_count(root) ; i++){
		Item* item = (Item*)List_at(root, i);
		fprintf(file, "|%12d|%14s|%9s|%9f|%11s|%7f|%9d|\n", item->id, item->partnumber, item->parttype, item->feature, item->footprint,item->price, item->number);
		}
		printf("--------------------------------------------------------------------------------\n");

}

List* App_LoadFromFile(char* fname, List* root){
    FILE* file = fopen(fname, "r");
	int counter = 0;
	Item tmp;
	while (fscanf(file, "%d%s%s%f%s%f%d", &tmp.id, tmp.partnumber, tmp.parttype, &tmp.feature, tmp.footprint, &tmp.price, &tmp.number) != EOF){
		//Item_print(&tmp);
		root = List_push(root, Item_create(tmp.id, tmp.partnumber, tmp.parttype, tmp.feature, tmp.footprint, tmp.price, tmp.number));
	}
	fclose(file);
	return (root);
}

List* App_ChartFill(List* root, List* chart_root, int id, int cnt){
    //if( root == NULL){ return (root);}
    int nmb = List_count(root);
    int i = 0;
    Item* tmp;
    while (i < nmb){
            tmp = ((Item*)List_at(root, i));
        if (tmp->id == id){
            if (tmp->number >= cnt){
                tmp->number = tmp->number - cnt;
                chart_root = List_push(chart_root, Item_create(tmp->id, tmp->partnumber, tmp->parttype, tmp->feature, tmp->footprint, cnt*(tmp->price), cnt));
                return (chart_root);
            }else{
                root = List_push(chart_root, Item_create(tmp->id, tmp->partnumber, tmp->parttype, tmp->feature, tmp->footprint, cnt*(tmp->price), tmp->number));
                tmp->number = 0;
                return (chart_root);
            }
        }
        i++;
    }
    return (chart_root);
}

/***************************************************************************************************/
void App_Save(List* root){
    char fname[10];
    printf("Enter filename: ");
    scanf("%s", fname);
    printf("\n");
    FILE* file;
    file = fopen(fname, "w");
    App_SaveToFile(file, root);
    fclose(file);
}
/****************************************************************************************************/
List* App_ItemDelete(List* root){
    int id;
    printf("Input item id\n");
    scanf("%d", &id);
    int cnt = List_count(root);
    int i = 0;
    while (i < cnt){
        if (((Item*)List_at(root, i))->id == id){
            Item_delete( (Item*)List_at(root, i));
            root = List_delete(root, i);
            printf("new root: %p\n", root);
            break;
        }
        i++;
    }
    return root;
}

/*****************************************************************************************************/
List* App_AddNew(List* root){
    Item tmp;
    int cnt = List_count(root);
    int i = 0;

    printf("Input ID\n");
    scanf("%d", &tmp.id);

    while (i < cnt){
        if (((Item*)List_at(root, i))->id == tmp.id){
            printf("Quantity\n");
            scanf("%d", &tmp.number);
            ((Item*)List_at(root, i))->number += tmp.number;
            break;
        }
        i++;
    }

    if (i != cnt){
        return root;
    }

    printf("Partnumber\n");
    scanf("%s", tmp.partnumber);

    printf("Parttype\n");
    scanf("%s", tmp.parttype);

    printf("Feature\n");
    scanf("%f", &tmp.feature);

    printf("Footprint\n");
    scanf("%s", tmp.footprint);

    printf("Price\n");
    scanf("%f", &tmp.price);

    printf("Quantity\n");
    scanf("%d", &tmp.number);
    root = List_push(root, Item_create(tmp.id, tmp.partnumber, tmp.parttype, tmp.feature, tmp.footprint, tmp.price, tmp.number));
}
/********************************************************************************************************/


void App_CreateChart(List* root){
    char fname[10];
    int id = 0;
    int cnt = 0;
    FILE* file = fopen("chart.txt", "w");
    List* chart_root = NULL;
    while(1){
        printf("Enter id and quantity or enter 0,0 for finish: ");
        scanf("%d%d", &id,&cnt);
        if (id == 0){ break;}
        chart_root = App_ChartFill(root, chart_root, id, cnt);
    }

    fprintf(file, "BANKS REQUSITE: 123456789\r\n");
    fprintf(file, "+------------+--------------+---------+---------+-----------+--------+---------+\r\n");
    fprintf(file, "|     id     |     name     | type    | feature | footprint | Price  | Balance |\r\n");
    fprintf(file, "+------------+--------------+---------+---------+-----------+--------+---------+\r\n");
    App_PrintToFile(file, chart_root);

    float sum = 0;

    cnt = List_count(chart_root);
    int i = 0;
    while (i < cnt){
        sum += ((Item*)List_at(chart_root, i))->price;
        i++;
    }

    fprintf(file, "Total: %0.5f RUB\r\n", sum);
    fclose(file);
    App_deleteAllItemsFromList(chart_root);
}


/**********************Sort by size (footprint)*********************************/
List* App_ListUnionByFp(List* dist, List* src, int mod){
// для вставки по алфавиту: mod = 1, dist > src;
// для простого объединения списков: mod != 1;
int one = List_count(dist);
if( mod == 1){
    int i = 0;
    while(i<one){
        Item* item1 = (Item*)(List_at(dist, i));
        Item* item2 = (Item*)(List_at(src, 0));
        if((strcmp(item1->footprint, item2->footprint))<=0){
            i++;
        }
        else{
            List* cur = src->next;
            dist = List_insert(dist, src, i);
            src = cur;
            one++;
            i++;
        }
        if(src == NULL){ break;}
    }
    if (i == one){
        List* tmp = List_id(dist, i-1);
        tmp->next = src;
    }
    return dist;
}
    List* tmp = List_id(dist, one-1);
    tmp->next = src;
    return dist;
}

List* App_FootprintSort(List* root, int length){
    if(length > 2){
        int one = length/2;
        int two = length-one;
        List* onehalf = root;
        List* twohalf = List_id(root, one);
        List* list1 = App_FootprintSort(root, one);
        List* list2 = App_FootprintSort(twohalf, two);
        List* dist = NULL;
        List* src = NULL;
        if(one > two){
            return App_ListUnionByFp(list1, list2, 1);
        }
        else{
            return App_ListUnionByFp(list2, list1, 1);
        }
    }
    if (length == 2){
        Item* item1 = (Item*)(List_at(root, 0));
        Item* item2 = (Item*)(List_at(root, 1));
        List* current = root->next;
        if((strcmp(item1->footprint, item2->footprint))<=0){
            current->next = NULL;
            return root;
        }//по алфавиту
        else{
            root->next = NULL;
            current->next = root;
            return current;
        }
    }
    if (length == 1){
        root->next = NULL;
        return root;
    }
}
/***********************************************************************************/

/****************Sort by feature********************/
List* App_ListUnionByFea(List* dist, List* src, int mod){
// для вставки по алфавиту: mod = 1, dist > src;
// для простого объединения списков: mod != 1;
int one = List_count(dist);
if( mod == 1){
    int i = 0;
    while(i<one){
        Item* item1 = (Item*)(List_at(dist, i));
        Item* item2 = (Item*)(List_at(src, 0));
        if((item1->feature) <= (item2->feature)){
            i++;
        }
        else{
            List* cur = src->next;
            dist = List_insert(dist, src, i);
            src = cur;
            one++;
            i++;
        }
        if(src == NULL){ break;}
    }
    if (i == one){
        List* tmp = List_id(dist, i-1);
        tmp->next = src;
    }
    return dist;
}
    List* tmp = List_id(dist, one-1);
    tmp->next = src;
    return dist;
}

List* App_FeatureSort(List* root, int length){
    if(length > 2){
        int one = length/2;
        int two = length-one;
        List* onehalf = root;
        List* twohalf = List_id(root, one);
        List* list1 = App_FeatureSort(root, one);
        List* list2 = App_FeatureSort(twohalf, two);
        List* dist = NULL;
        List* src = NULL;
        if(one > two){
            return App_ListUnionByFea(list1, list2, 1);
        }
        else{
            return App_ListUnionByFea(list2, list1, 1);
        }
    }
    if (length == 2){
        Item* item1 = (Item*)(List_at(root, 0));
        Item* item2 = (Item*)(List_at(root, 1));
        List* current = root->next;
        if((item1->feature) <= (item2->feature)){
            current->next = NULL;
            return root;
        }//по алфавиту
        else{
            root->next = NULL;
            current->next = root;
            return current;
        }
    }
    if (length == 1){
        root->next = NULL;
        return root;
    }
}
/***********************************************************************************/

/****************Sort by price********************/
List* App_ListUnionByPrice(List* dist, List* src, int mod){
// для вставки по алфавиту: mod = 1, dist > src;
// для простого объединения списков: mod != 1;
int one = List_count(dist);
if( mod == 1){
    int i = 0;
    while(i<one){
        Item* item1 = (Item*)(List_at(dist, i));
        Item* item2 = (Item*)(List_at(src, 0));
        if((item1->price) <= (item2->price)){
            i++;
        }
        else{
            List* cur = src->next;
            dist = List_insert(dist, src, i);
            src = cur;
            one++;
            i++;
        }
        if(src == NULL){ break;}
    }
    if (i == one){
        List* tmp = List_id(dist, i-1);
        tmp->next = src;
    }
    return dist;
}
    List* tmp = List_id(dist, one-1);
    tmp->next = src;
    return dist;
}

List* App_PriceSort(List* root, int length){
    if(length > 2){
        int one = length/2;
        int two = length-one;
        List* onehalf = root;
        List* twohalf = List_id(root, one);
        List* list1 = App_PriceSort(root, one);
        List* list2 = App_PriceSort(twohalf, two);
        List* dist = NULL;
        List* src = NULL;
        if(one > two){
            return App_ListUnionByPrice(list1, list2, 1);
        }
        else{
            return App_ListUnionByPrice(list2, list1, 1);
        }
    }
    if (length == 2){
        Item* item1 = (Item*)(List_at(root, 0));
        Item* item2 = (Item*)(List_at(root, 1));
        List* current = root->next;
        if((item1->price) <= (item2->price)){
            current->next = NULL;
            return root;
        }//по алфавиту
        else{
            root->next = NULL;
            current->next = root;
            return current;
        }
    }
    if (length == 1){
        root->next = NULL;
        return root;
    }
}
/***********************************************************************************/
List* App_Sort(List* root){
    int dir = 0;
    int srt = 0;
    printf("Input sort parametr:\n\t 0:Sort by size;\n\t 1:Sort by feature;\n\t 2:Sort by price\n");
    scanf("%d", &srt);
    switch(srt){
        case 0:{
            root = App_FootprintSort(root, List_count(root));
        }break;
        case 1:{
            root = App_FeatureSort(root, List_count(root));
        }break;
        case 2:{
            root = App_PriceSort(root, List_count(root));
        }break;
        default:{
            root = App_FootprintSort(root, List_count(root));
        }break;
    }
    printf("Input sort dirrection [0:a-z],[1:z-a]\n");
    scanf("%d", &dir);
    if(dir){
        root = List_revese(root);
    }

    return root;
}


int App_showAltMenu(){
	printf("!!!!!MENU!!!!!\n");
	printf("1. Print all items at root\n");
	printf("2. Print all items at filter\n");
	printf("3. Find at partnumber\n");
	printf("4. Find at parttype\n");
	printf("5. Find at feature range\n");
	printf("6. Find at price range\n");
	printf("7. Sort\n");
    printf("8. Save to file\n");
    printf("9. CreateChart\n");
    printf("10. Filter\n");
    printf("11. Exit\n");
	printf("\n");
	printf("Input action [1-11]\n");
	int id;
	scanf("%d", &id);
	return id;
}


int App_Filter(List* root){
    List* filter = NULL;
	int action = 0;
	while(action !=11){
		action = App_showAltMenu();
		switch(action) {
			case 1:{
                App_printAllItemsFromList(root);
			} break;
			case 2:{
                App_printAllItemsFromList(filter);
			} break;
			case 3:{
			    char str[15];
			    printf("\nEnter find string Partnumber\n");
			    scanf("%s", &str);
			    printf("Scaned string: %s\n", str);
                filter = Query_StringAtPartNumber(root, filter, str);
			} break;
			case 4: {
			    char str[15];
			    printf("\nEnter find string for Part Type\n");
			    scanf("%s", &str);
                filter = Query_StringAtPartType(root, filter, str);
			} break;
			case 5: {
			    float feat_min;
			    float feat_max;
			    printf("\nEnter min and max feature\n");
			    scanf("%f%f", &feat_min, &feat_max);
			    filter = Query_RangeAtFeature(root, filter, feat_min, feat_max);
			} break;
			case 6: {
			    float prc_min;
			    float prc_max;
			    printf("\nEnter min and max price\n");
			    scanf("%f%f", &prc_min, &prc_max);
			    filter = Query_RangeAtPrice(root, filter, prc_min, prc_max);
			} break;
			case 7: {
                filter = App_Sort(filter);
			} break;
			case 8: {
                App_Save(filter);
			} break;
			case 9: {
                App_CreateChart(filter);
			} break;
			case 10: {
			    printf("\nWork with new stage filtered base\n");
			    action = App_Filter(filter);
			} break;
		}
	}
	App_deleteAllItemsFromList(filter);
	return action;
};

#endif // AP_H
