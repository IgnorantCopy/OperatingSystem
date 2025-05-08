//
// Created by Ignorant on 2025/5/6.
//

#include "linked_list.h"

#include <stdio.h>
#include <stdlib.h>

void list_init(list_t *list) {
    list->head = nullptr;
    pthread_mutex_init(&list->lock, nullptr);
}

int list_insert(list_t *list, const int key) {
    // synchronization not needed
    node_t *new_node = malloc(sizeof(node_t));
    if (new_node == nullptr) {
        perror("malloc");
        return -1;
    }
    new_node->key = key;

    pthread_mutex_lock(&list->lock);
    new_node->next = list->head;
    list->head = new_node;
    pthread_mutex_unlock(&list->lock);
    return 0;
}

int list_search(list_t *list, const int key) {
    int ret = -1;
    pthread_mutex_lock(&list->lock);
    const node_t *current = list->head;
    while (current) {
        if (current->key == key) {
            ret = 0;
            break;
        }
        current = current->next;
    }
    pthread_mutex_unlock(&list->lock);
    return ret;
}

int list_remove(list_t *list, int key) {
    int ret = -1;
    pthread_mutex_lock(&list->lock);
    node_t *previous = nullptr;
    node_t *current = list->head;
    while (current) {
        if (current->key == key) {
            ret = 0;
            break;
        }
        previous = current;
        current = current->next;
    }
    if (ret == 0) {
        if (previous) {
            previous->next = current->next;
        } else {
            list->head = current->next;
        }
        free(current);
    }
    pthread_mutex_unlock(&list->lock);
    return ret;
}

void list_delete(list_t *list) {
    pthread_mutex_lock(&list->lock);
    node_t *current = list->head;
    while (current) {
        node_t *next = current->next;
        free(current);
        current = next;
    }
    pthread_mutex_unlock(&list->lock);
    list->head = nullptr;
}

int main() {
    
    return 0;
}
