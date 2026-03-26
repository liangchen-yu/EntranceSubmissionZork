//
// Created by yumerxcy on 3/26/26.
//

#ifndef ENTRANCESUBMISSIONZORK_ITEM_H
#define ENTRANCESUBMISSIONZORK_ITEM_H

typedef struct {
    char *name;
    char *description;
} Item;

Item *CreateItem(char *name, char *description);
#endif //ENTRANCESUBMISSIONZORK_ITEM_H