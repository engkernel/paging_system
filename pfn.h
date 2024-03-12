/*
* here, I want make some schemes on pfn structures.
* virtual pages requires their corresponds pfns.
*/

#define NUM_PAGES 100

struct page_frame{
	void* physical_address;
	bool is_allocated;
};


static struct page_frame* page_frame_pool;
unsigned int  init_page_frame() {
	page_frame_pool = malloc(NUM_PAGES * sizeof(struct page_frame));
	if (page_frame_pool == NULL) {
		return ;
	}
	for (int i = 0; i < NUM_PAGES; i++) {
		page_frame_pool[i].physical_address = NULL;
		page_frame_pool[i].is_allocated = false;
	}

	return 0;
}
