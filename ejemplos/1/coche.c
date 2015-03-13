#include "coche.h"
#include <string.h>

struct coche *curso_coche_alloc(void)
{
	return (struct coche *)malloc(sizeof(struct coche));
}

void curso_coche_free(struct coche *c)
{
	if (c->flags & (1 << CURSO_COCHE_ATTR_MARCA))
		xfree(c->marca);

	if (c->flags & (1 << CURSO_COCHE_ATTR_MATRICULA))
		xfree(c->matricula);

	xfree(c);
}

bool curso_coche_attr_is_set(const struct coche *c, uint16_t attr)
{
	return c->flags & (1 << attr);
}

void curso_coche_attr_unset(struct coche *c, uint16_t attr)
{
	if (!(c->flags & (1 << attr)))
		return;

	switch (attr) {
	case CURSO_COCHE_ATTR_MARCA:
		if (c->marca) {
			xfree(c->marca);
			c->marca = NULL;
		}
		break;
	case CURSO_COCHE_ATTR_MATRICULA:
		if (c->matricula) {
			xfree(c->matricula);
			c->matricula = NULL;
		}
		break;
	case CURSO_COCHE_ATTR_ID:
		break;
	}

	c->flags &= ~(1 << attr);
}

void curso_coche_set_data(struct coche *c, uint16_t attr, const void *data,
			  uint32_t data_len)
{
	if (attr > CURSO_COCHE_ATTR_MAX)
		return;

	switch (attr) {
	case CURSO_COCHE_ATTR_MARCA:
		if (c->marca)
			xfree(c->marca);

		c->marca = strdup(data);
		break;
	case CURSO_COCHE_ATTR_MATRICULA:
		if (c->matricula)
			xfree(c->matricula);

		c->matricula = strdup(data);
		break;
	case CURSO_COCHE_ATTR_ID:
		c->id = *((uint32_t *)data);
		break;
	}

	c->flags |= (1 << attr);
}

void curso_coche_attr_set_u32(struct coche *c, uint16_t attr, uint32_t data)
{
	curso_coche_set_data(c, attr, &data, sizeof(uint32_t));
}

void curso_coche_attr_set_str(struct coche *c, uint16_t attr, const char *data)
{
	curso_coche_set_data(c, attr, data, 0);
}

const void *curso_coche_attr_get_data(struct coche *c, uint16_t attr)
{
	if (!(c->flags & (1 << attr)))
		return NULL;

	switch(attr) {
	case CURSO_COCHE_ATTR_MARCA:
		return c->marca;
	case CURSO_COCHE_ATTR_MATRICULA:
		return c->matricula;
	case CURSO_COCHE_ATTR_ID:
		return &c->id;
	}
	return NULL;
}

uint32_t curso_coche_attr_get_u32(struct coche *c, uint16_t attr)
{
	const void *ret = curso_coche_attr_get_data(c, attr);
	return ret == NULL ? 0 : *((uint32_t *)ret);
}

const char *curso_coche_attr_get_str(struct coche *c, uint16_t attr)
{
	return curso_coche_attr_get_data(c, attr);
}

int curso_coche_snprintf(char *buf, size_t size, struct coche *c)
{
	return snprintf(buf, size, "matricula %s marca %s id %d",
			c->matricula, c->marca, c->id);
}
