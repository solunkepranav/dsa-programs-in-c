#include <stdio.h>
#include <stdlib.h>

// Structure for a single line in the cache [cite: 378]
typedef struct {
    int valid; 
    int block_id;
    int data; 
} CacheLine;

// Structure for a Set [cite: 383]
typedef struct {
    CacheLine *lines; 
    int fifo_index; 
} CacheSet;

// Structure for the entire Cache [cite: 392]
typedef struct {
    CacheSet *sets;
    int num_sets;
    int num_ways;
} Cache;

// Initialize Cache [cite: 399]
void initializeCache(Cache *cache, int cache_size, int ways) {
    cache->num_ways = ways;
    cache->num_sets = cache_size / ways;
    cache->sets = (CacheSet *)malloc(cache->num_sets * sizeof(CacheSet));
    for (int i=0; i < cache->num_sets; i++) {
        cache->sets[i].lines = (CacheLine *)malloc(ways * sizeof(CacheLine));
        cache->sets[i].fifo_index = 0;
        for (int j = 0; j < ways; j++) {
            cache->sets[i].lines[j].valid = 0;
            cache->sets[i].lines[j].block_id = -1;
            cache->sets[i].lines[j].data = 0;
        }
    }
}

// Access Memory Function [cite: 420]
int accessMemory(Cache *cache, int *main_memory, int block_id) {
    int set_index = block_id % cache->num_sets;
    int tag = block_id / cache->num_sets;
    CacheSet *current_set = &cache->sets[set_index];
    int hit = 0;

    // Associative Search [cite: 426]
    for (int i=0; i < cache->num_ways; i++) {
        if (current_set->lines[i].valid && current_set->lines[i].block_id == block_id) {
            hit = 1;
            break;
        }
    }

    // Handle Miss -> Fetch from Main Memory [cite: 434]
    if (!hit) {
        int replace_idx = current_set->fifo_index;
        int fetched_data = main_memory[block_id];
        
        current_set->lines[replace_idx].block_id = block_id;
        current_set->lines[replace_idx].data = fetched_data;
        current_set->lines[replace_idx].valid = 1;
        
        // Update FIFO [cite: 450]
        current_set->fifo_index = (replace_idx + 1) % cache->num_ways;
    }

    // Display Output [cite: 452]
    printf("%-5d | %-9d | %-3d | %-6s | [", block_id, set_index, tag, hit? "HIT": "MISS");
    for (int i = 0; i < cache->num_ways; i++) {
        if (current_set->lines[i].valid) {
            printf("%d ", current_set->lines[i].block_id);
        } else {
            printf("- ");
        }
    }
    printf("]\n");
    return hit;
}

int main() {
    int main_mem_size, cache_size, ways, choice, n_requests;
    int total_hits = 0;

    printf("=== Cache Simulator ===\n");
    printf("Enter Main Memory Size (number of blocks): ");
    scanf("%d", &main_mem_size);
    int *main_memory = (int *)malloc(main_mem_size * sizeof(int));
    
    printf("\n--- Fill Main Memory Data ---\n");
    printf("Enter data for each block: ");
    for (int i=0; i < main_mem_size; i++) {
        scanf("%d", &main_memory[i]);
    }

    printf("\nEnter Cache Memory Size (total lines): ");
    scanf("%d", &cache_size);
    printf("\nSelect Associativity:\n1. Direct Mapping\n2. Fully Associative\n3. K-way Set Associative\nChoice: ");
    scanf("%d", &choice);

    if (choice == 1) ways = 1;
    else if (choice == 2) ways = cache_size;
    else {
        printf("Enter K: ");
        scanf("%d", &ways);
    }

    Cache myCache;
    initializeCache(&myCache, cache_size, ways);

    printf("\nEnter number of memory requests: ");
    scanf("%d", &n_requests);
    int *requests = (int*)malloc(n_requests * sizeof(int));
    printf("Enter the Memory Block References: ");
    for (int i=0; i < n_requests; i++) {
        scanf("%d", &requests[i]);
    }

    printf("\n%-5s | %-9s | %-3s | %-6s | %s\n", "Block", "Set Index", "Tag", "Status", "Set Content");
    printf("----------------------------------------------\n");

    for (int i=0; i < n_requests; i++) {
        if(requests[i] < main_mem_size) {
            total_hits += accessMemory(&myCache, main_memory, requests[i]);
        } else {
            printf("Error: Block %d exceeds Main Memory size.\n", requests[i]);
        }
    }

    printf("----------------------------------------------\n");
    printf("Total Hits: %d\n", total_hits);
    printf("Total Misses: %d\n", n_requests - total_hits);
    printf("Hit Ratio: %.2f%%\n", ((float)total_hits / n_requests) * 100.0);

    return 0;
}