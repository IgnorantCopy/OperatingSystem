//
// Created by Ignorant on 2025/5/6.
//

#include "queue.h"

#include <assert.h>
#include <stdlib.h>


void queue_init(queue_t* queue) {
    node_t *temp = malloc(sizeof(node_t));  // dummy node
    assert(temp != nullptr);
    temp->next = nullptr;
    queue->head = queue->tail = temp;
    pthread_mutex_init(&queue->headLock, nullptr);
    pthread_mutex_init(&queue->tailLock, nullptr);
}

void queue_enqueue(queue_t* queue, const int value) {
    node_t *temp = malloc(sizeof(node_t));
    assert(temp != nullptr);
    temp->value = value;
    temp->next = nullptr;

    pthread_mutex_lock(&queue->tailLock);
    queue->tail->next = temp;
    queue->tail = temp;
    pthread_mutex_unlock(&queue->tailLock);
}

int queue_dequeue(queue_t* queue, int *value) {
    pthread_mutex_lock(&queue->headLock);
    node_t *temp = queue->head;
    node_t *newHead = temp->next;
    if (newHead == nullptr) {
        pthread_mutex_unlock(&queue->headLock);
        return -1;
    }
    *value = temp->value;
    queue->head = newHead;
    pthread_mutex_unlock(&queue->headLock);
    free(temp);
    return 0;
}

int main() {
    
    return 0;
}
