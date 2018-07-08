#include "bpt.h"
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>


// STRUCTS.

// Header page is the first page (offset 0-4095) of a data file, and contains metadata.
typedef struct _HeaderPage {
    // points the first free page (head of free page list)
    // 0, if there is no free page left.
    int64_t free_page_offset;
    // pointing the root page within the data file.
    int64_t root_page_offset;
    // how many pages exist in this data file now.
    int64_t numbef_of_pages;
    // (Reserved)
    char padding[4072];
} HeaderPage;

// Free pages are linked and allocation is managed by the free page list.
typedef struct _FreePage {
    // points the next free page. 0, if end of the free page list.
    int64_t next_free_page_offset;
    // (Not used)
    char padding[4092];
} FreePage;

// Internal/Leaf page have first 128 bytes as a page header.
typedef struct _PageHeader {
    // If internal/leaf page, this field points the position of parent page.
    int64_t parent_page_offset;
    // 0 is internal page, 1 is leaf page.
    int is_leaf;
    // the number of keys within this page.
    int number_of_keys;
    // (Not used)
    char padding[104];
    union _offset {
        // Used in leaf page. If rightmost leaf page, right sibling page offset field is 0.
        int64_t right_sibling_page;
        // Used in internal page. 
        int64_t one_more_page;
    } offset;
} PageHeader;

typedef struct _Record {
    int64_t key;
    char value[120];
} Record;

// Leaf page contains the key/value records.
typedef struct _LeafPage {
    PageHeader header;
    Record records[31];
} LeafPage;

typedef struct _KeyOffsetPair {
    int64_t key;
    int64_t page_offset;
} KeyOffsetPair;

// Internal page is similar to leaf page, but instead of containing 120 bytes of values,
// it contains 8 bytes of another page (internal or leaf) offset.
typedef struct _InternalPage {
    PageHeader header;
    KeyOffsetPair key_offset_pairs[248];
} InternalPage;


// GLOBALS.

// File pointer to database file.
FILE * g_db_file;


// FUNCTION DEFINITIONS.

int open_db(const char * pathname) {
    if (g_db_file) {
        fclose(g_db_file);
    }
    g_db_file = fopen(pathname, "rw");
    return g_db_file != NULL;
}

int insert(int64_t key, const char * value) {
    return 0;
}

char * find(int64_t key) {
    return NULL;
}

int delete(int64_t key) {
    return 0;
}