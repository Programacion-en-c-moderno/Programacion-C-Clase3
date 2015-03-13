#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include "list.h"

enum {
	CURSO_COCHE_ATTR_MARCA,
	CURSO_COCHE_ATTR_MATRICULA,
	CURSO_COCHE_ATTR_ID,
	__CURSO_COCHE_ATTR_MAX
};

#define CURSO_COCHE_ATTR_MAX (__CURSO_COCHE_ATTR_MAX - 1)

#define xfree(ptr)      free((void *)ptr);

struct coche {
	struct list_head	head;
	uint32_t		id;
	const char      	*matricula;
	const char		*marca;

	uint32_t		flags;
};

struct coche *curso_coche_alloc(void);
void curso_coche_free(struct coche *);

bool curso_coche_attr_is_set(const struct coche *c, uint16_t attr);

void curso_coche_attr_unset(struct coche *c, uint16_t attr);

void curso_coche_attr_set_data(struct coche *c, uint16_t attr, const void *data,
			       uint32_t data_len);
void curso_coche_attr_set_u32(struct coche *c, uint16_t attr, uint32_t data);
void curso_coche_attr_set_str(struct coche *c, uint16_t attr, const char *data);

const void *curso_coche_attr_get_data(struct coche *c, uint16_t attr);
uint32_t curso_coche_attr_get_u32(struct coche *c, uint16_t attr);
const char *curso_coche_attr_get_str(struct coche *c, uint16_t attr);

int curso_coche_snprintf(char *buf, size_t size, struct coche *c);
