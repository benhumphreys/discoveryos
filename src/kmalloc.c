#include "kmalloc.h"

#include "types.h"
#include "stddef.h"
#include "console.h"
#include "panic.h"

struct block_metadata {
	size_t size;
	struct block_metadata *next;
	uint32_t free;
	uint32_t magic;
};

static struct block_metadata *alloc_list = NULL;

#define METADATA_MAGIC 0xCAFEBABE
#define METADATA_SIZE sizeof(struct block_metadata)
#define SPLIT_THRESHOLD (4 + METADATA_SIZE)

static void assert_block(struct block_metadata *block);
static struct block_metadata *find_free(size_t size);
static struct block_metadata *find_last();
static struct block_metadata *get_block_ptr(void *ptr);
static struct block_metadata *init_block(void *ptr, size_t size);

void *kmalloc(size_t size) {
	struct block_metadata *block = find_free(size);
	if (!block) {
		return NULL;
	}
	if (block->size > size + METADATA_SIZE + SPLIT_THRESHOLD) {
		void *next_ptr = ((void *)block) + METADATA_SIZE + size;
		size_t excess = block->size - size;
		struct block_metadata *next_block = init_block(next_ptr, excess);
		next_block->next = block->next;
		block->next = next_block;
		block->size = block->size - excess;
	}
	block->free = 0;
	return block + 1;
}

void kmalloc_init(void *ptr, size_t size) {
	if (size < METADATA_SIZE) {
		return;
	}
	console_printf("mm: initialized with block 0x%p, length %d bytes\n", ptr, size);
	struct block_metadata *block = ptr;
	block->size = size - METADATA_SIZE;
	block->next = NULL;
	block->free = 1;
	block->magic = METADATA_MAGIC;

	if (alloc_list == NULL) {
		alloc_list = block;
	} else {
		struct block_metadata *tail = find_last();
		tail->next = block;
	}
}

void kfree(void *ptr) {
	if (!ptr) {
		return;
	}

	struct block_metadata *block = get_block_ptr(ptr);
	assert_block(block);
	if (block->free != 0) {
		panic("free(): block is already free");
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

static struct block_metadata *find_last() {
	struct block_metadata *current = alloc_list;
	while (current->next) {
		assert_block(current);
		current = current->next;
	}
	return current;
}

static struct block_metadata *get_block_ptr(void *ptr) {
	return (struct block_metadata *)ptr - 1;
}

static void assert_block(struct block_metadata *block) {
	if (block->magic != METADATA_MAGIC) {
		panic("assert_block(): Not a valid block header");
	}
}

static struct block_metadata *init_block(void *ptr, size_t size) {
	if (size < METADATA_SIZE + 1) {
		panic("init_block(): Block too small");
	}
	struct block_metadata *block = ptr;
	block->size = size - METADATA_SIZE;
	block->next = NULL;
	block->free = 1;
	block->magic = METADATA_MAGIC;

	return block;
}
