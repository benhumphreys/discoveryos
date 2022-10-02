#include "kmalloc.h"

#include "types.h"
#include "stddef.h"
#include "console.h"

struct block_metadata {
    size_t size;
    struct block_metadata *next;
    uint32_t free;
    uint32_t magic;
};

static struct block_metadata *alloc_list = NULL;

#define METADATA_MAGIC 0xCAFEBABE
#define METADATA_SIZE sizeof(struct block_metadata)

static struct block_metadata *find_free(size_t size);
static struct block_metadata *get_block_ptr(void *ptr);
static void assert_block(struct block_metadata *block);

void *kmalloc(size_t size) {
    struct block_metadata *block= find_free(size);
    if (!block) {
        return NULL;
    }
    block->free = 0;
    return block + 1;
}

void kmalloc_init(void *ptr, size_t size) {
    if (size < METADATA_SIZE) {
        return;
    }
    console_printf("Malloc initialized with block of %d bytes\n", size);
    struct block_metadata *block = ptr;
    block->size = size - METADATA_SIZE;
    block->next = NULL;
    block->free = 0;
    block->magic = METADATA_MAGIC;
}

void kfree(void *ptr) {
    if (!ptr) {
        return;
    }

    struct block_metadata *block = get_block_ptr(ptr);
    assert_block(block);
    if (block->free != 0) {
        console_printf("free(): block is already free\n");
        *(int *)0 = 0;
    }
    block->free = 1;
}

static struct block_metadata *find_free(size_t size) {
    struct block_metadata *current = alloc_list;
    while (current) {
        assert_block(current);
        if (current->free == 1 && current->size >= size) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

static struct block_metadata *get_block_ptr(void *ptr) {
    return (struct block_metadata*) ptr - 1;
}

static void assert_block(struct block_metadata *block) {
    if (block->magic != METADATA_MAGIC) {
        *(int *)0 = 0;
    }
}
