#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "user.h"
#include "list.h"
#include "ap.h"
#include "vendible.h"
#include "query.h"

/************************** My additions ******************************************/
/*My string func*/
int AlphabetSort(char* str1, char* str2){
    int i = 0;
    while((str1[i]!= '\0')||(str2[i] != '\0')){
        if (str1[i] > str2[i]) return 0;
        else if (str1[i] < str2[i]) return 1;
        i++;
    }
    --i;
    if (str1[i] == str2[i]) return 0;
    if (str1[i] == '\0') return 0;
    if (str2[i] == '\0') return 1;
}

/**********************************************************************************/
/*
int main(){
    Item* item = NULL;
    item = Item_create(10, "C0603", "Cap", 10, "0603", 0.25, 10);
    Item_print(item);
    Item_delete(item);
	return 0;
}
*/
int main(){

	List* root = NULL;

	char option = 'N';
	printf("Load saved data? [Y/N]: ");
    scanf("%c", &option);
    if (option == 'Y'){
        root = App_LoadFromFile("test.txt", root);
    }
    else{
        root = List_push(root, Item_create(10, "C0603", "Cap", 10, "0603", 0.25, 10));
        root = List_push(root, Item_create(15, "R0603", "Res", 10, "0603", 0.25, 10));
    }

	int action = 0;
	while(action !=8){
		action = App_showMenu();
		switch(action) {
			case 1:{
			App_printAllItemsFromList(root);
			} break;
			case 2:{
                root = App_AddNew(root);
			} break;
			case 3: {
                root = App_ItemDelete(root);
			} break;
			case 4: {
			    root = App_Sort(root);
			} break;
			case 5: {
                App_Save(root);
			} break;
			case 6: {
                App_CreateChart(root);
			} break;
			case 7: {
			    printf("\nWork with filtered base\n");
                App_Filter(root);
                printf("\nWork with all base\n");
			} break;
		}
	}
	App_deleteAllItemsFromList(root);

	return 0;
}
