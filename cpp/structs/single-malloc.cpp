/**
 * Initialization of struct members with single malloc
 * ===================================================
 */

#include "tests.h"

/* ===========================================================================
 * Algorithms implementation
 * ===========================================================================
 */
typedef struct employee_ {
	char *name;
	int id;
} ee_t;

/*
 * When a struct has pointers e.g. name in struct employee_ then it requires
 * at least two malloc calls to allocate memory first for the struct and then
 * for its pointer members. This can be a performance issue as malloc calls
 * are expensive. To overcome that we allocate a single large block of memory
 * with single malloc call and point struct pointer members to locations in
 * that block.
 *
 * p0 is start of pointer to single large block of memory allocated using a
 * single malloc. In this block struct pointer members can be pointed to at:
 *
 * +-------------------+------------------+
 * | struct employee_  | remaining memory |
 * +-------------+-----+------------------+
 * | p0 (id, name_ptr) | p1 (name_val)    |
 * +-------------------+------------------+
 */
ee_t *init_ee(int id, const char *name)
{
	size_t n0 = strlen(name), n1 = n0 + 1;
	size_t sz = sizeof(ee_t), es = sz + n1;

	char *p0 = (char *)malloc(es);
	char *p1 = (char *)(p0 + sz);

	memset(p1, 0, n1);
	strncpy(p1, name, n0);

	ee_t *ep = (ee_t *)p0;
	ep->name = p1;
	ep->id = id;
	return ep;
}

/* ===========================================================================
 * Test code
 * ===========================================================================
 */
#define _sm_check(_id, _name)                                                \
	{                                                                    \
		ee_t *ep = init_ee(_id, _name);                              \
		string em, am;                                               \
		em = format("id: {}, name: {}", _id, _name);                 \
		am = format("id: {}, name: {}", ep->id, ep->name);           \
		CHECK_EQ(em, am);                                            \
		SHOW_OUTPUT(em, am);                                         \
		free(ep);                                                    \
	}

TEST(init_ee, "Initialization of struct members with single malloc")
{
	int _i[] = {2, 5};
	const char *_n[] = {"abc", "new hello world, testing single malloc"};
	int n = sizeof(_i) / sizeof(_i[0]);
	fii (i, n) _sm_check(_i[i], _n[i]);
}

INIT_TEST_MAIN();
