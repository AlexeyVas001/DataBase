#ifndef QUERY_H_INCLUDED
#define QUERY_H_INCLUDED

#include "list.h"
#include "ap.h"
#include "vendible.h"
#include "string.h"
#include "query.h"

int Query_FindString(char* base, char* str){
    int len_str = strlen(str);
    int len_base = strlen(base);
    if (len_base < len_str){
        return (0);
    }
    if (len_base == len_str){
        if (strcmp(base, str) == 0){
            return (1);
        }
        else{
            return (0);
        }
    }

    int iter = len_base-len_str+1;
    char* buf = (char*)malloc((len_str + 1)* sizeof(char));
    for (int i = 0; i < iter; i++){
        strncpy(buf, &base[i], len_str);
        buf[len_str] = '\0';
        if (strcmp(buf, str) == 0){
            free(buf);
            return (1);
        }
    }
    free(buf);
    return (0);
}

List* Query_StringAtPartNumber(List* root, List* filt, char* str){
    int cnt = List_count(root);
    for (int i = 0; i < cnt; i++){
            Item* tmp = (Item*)List_at(root, i);
        if (Query_FindString(tmp->partnumber, str) == 1){
            filt = List_push(filt, Item_create(tmp->id, tmp->partnumber, tmp->parttype, tmp->feature, tmp->footprint, tmp->price, tmp->number));
        }
    }
    return filt;
}

List* Query_StringAtPartType(List* root, List* filt, char* str){
    int cnt = List_count(root);
    for (int i = 0; i < cnt; i++){
            Item* tmp = (Item*)List_at(root, i);
        if (Query_FindString(tmp->parttype, str) == 1){
            filt = List_push(filt, Item_create(tmp->id, tmp->partnumber, tmp->parttype, tmp->feature, tmp->footprint, tmp->price, tmp->number));
        }
    }
    return filt;
}


List* Query_RangeAtFeature(List* root, List* filt, float feat_min, float feat_max){
    if (root == NULL){
        return root;
    }
    if(feat_min > feat_max){
        float c = feat_max;
        feat_max = feat_min;
        feat_min = c;
    }
    int cnt = List_count(root);
    for (int i = 0; i < cnt; i++){
            Item* tmp = (Item*)List_at(root, i);
        if ((tmp->feature <= feat_max)&&(tmp->feature >= feat_min)){
            filt = List_push(filt, Item_create(tmp->id, tmp->partnumber, tmp->parttype, tmp->feature, tmp->footprint, tmp->price, tmp->number));
        }
    }
    return filt;
}

List* Query_RangeAtPrice(List* root, List* filt, float prc_min, float prc_max){
    if (root == NULL){
        return root;
    }
    if(prc_min > prc_max){
        float c = prc_max;
        prc_max = prc_min;
        prc_min = c;
    }
    int cnt = List_count(root);
    for (int i = 0; i < cnt; i++){
            Item* tmp = (Item*)List_at(root, i);
        if ((tmp->price <= prc_max)&&(tmp->price >= prc_min)){
            filt = List_push(filt, Item_create(tmp->id, tmp->partnumber, tmp->parttype, tmp->feature, tmp->footprint, tmp->price, tmp->number));
        }
    }
    return filt;
}


#endif // QUERY_H_INCLUDED
