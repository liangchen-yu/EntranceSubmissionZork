//
// Created by yumerxcy on 3/26/26.
//
#include <stdio.h>
#include <string.h>
#include "Declaration.h"

Command GetCommand(void) {
    Command cmd;
    cmd.commandWord = NULL;
    cmd.secondWord = NULL;

    printf("> ");
    fgets(input, sizeof(input), stdin);

    input[strcspn(input, "\n")] = 0;

    word1[0] = '\0';
    word2[0] = '\0';

    sscanf(input, "%s %s", word1, word2);//fixed

    if (strlen(word1) > 0) cmd.commandWord = word1;
    if (strlen(word2) > 0) cmd.secondWord = word2;

    return cmd;
}