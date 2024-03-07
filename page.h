/*
* pages definitions
*/
struct page_pte{
	/*
	 * page_frame_number
	 * present/absent
	 * protection
	 * reference
	 * caching
	 * dirty
	 */
	unsigned int page_pfn;
	unsigned int present;
	unsigned int protection;
	unsigned int reference;
	unsigned int caching;
	unsigned int dirty;
};

struct page_pmd{
	/*
	 *
	 */
	struct page_pte pte[1024];	
};

struct page_pgd{
	struct page_pmd pmd[1024];
};

struct virtual_page{
	/*
	we would like to have 3 level paging
	 - 32 bits
	   -- 10 pgd
	   -- 10 pmd
	   -- 12 pte
	 */
	struct page_pgd pgd[1024];
};
