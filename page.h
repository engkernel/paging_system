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

struct virt_page_table{
	/*
	we would like to have 3 level paging
	 - 32 bits
	   -- 10 pgd
	   -- 10 pmd
	   -- 12 pte
	 */
	struct page_pgd pgd[1024];
};

static inline struct page_pte get_pte(struct page_pmd pmd, int pte_offset)
{
	return pmd[pte_offset];
};

static inline struct page_pmd get_pmd(struct page_pgd pgd, int pmd_offset)
{
	return pgd[pmd_offset]; 
};

static inline struct page_pgd get_pgd(struct virt_page page, int pgd_offset)
{
	return page[pgd_offset];
};

/* we just define a variable as a table */
static virt_page_table table; 

/* convert virtual address to its corresponds physical */
void* virt_to_phys(void* virt_addr){
	struct page_pgd pgd_offset;
	struct page_pmd pmd_offset;
	struct page_pte pte_offset;
	void* pfn;

	pgd_offset = PGD_OFFSET(virt_addr);	
	pmd_offest = PMD_OFFSET(virt_addr);
	pte_offset = PTE_OFFSET(virt_addr);

	/*
	 * we just try to emphasis a dumb solution to get big picture
	 * 	pgd[pgd_offset] ->
	 			  pmd[pmgd_offest] ->
				  			pte[pte_offset];
	 */
	pfn = get_pte(get_pmd(get_pgd(table, pgd_offset), pmd_offset), pte_offset);		

	return pfn;
}

