/*
* pages definitions
*/
#define PGD_OFFSET(addr) (addr >> 22 & 0xFFC00000)
#define PMD_OFFSET(addr) (addr >> 12 & 0x3FF000)
#define PTE_OFFSET(addr) (addr & 0xFFF)

struct page_attr{
	unsigned int present;
	unsigned int protection;
	unsigned int reference;
	unsigned int caching;
	unsigned int dirty;
};

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
	struct page_attr attr;
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

struct virt_page{
	/*
	we would like to have 3 level paging
	 - 32 bits
	   -- 10 pgd
	   -- 10 pmd
	   -- 12 pte
	 */
	struct page_pgd pgd[1024];
};

/* convert virtual address to its corresponds physical */
void* virt_to_phys(void* virt_addr){
	struct page_pgd pgd_offset;
	struct page_pmd pmd_offset;
	struct page_pte pte_offset;

	pgd_offset = PGD_OFFSET(virt_addr);	
	pmd_offest = PMD_OFFSET(virt_addr);
	pte_offset = PTE_OFFSET(virt_addr);

	
}

