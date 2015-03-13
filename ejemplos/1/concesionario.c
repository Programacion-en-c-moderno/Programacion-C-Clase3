#include "concesionario.h"
#include <string.h>

struct concesionario {
	struct list_head	garaje;
	const char      	*dueno;
	uint32_t		num_coches;

	uint32_t		flags;
};

struct concesionario *curso_concesionario_alloc(void)
{
	struct concesionario *con;

	con = malloc(sizeof(struct concesionario));
	if (con ==  NULL)
		return NULL;

	INIT_LIST_HEAD(&con->garaje);

	return con;
}

void curso_concesionario_free(struct concesionario *con)
{
	int i;
	struct coche *c, *tmp;

	if (con->flags & (1 << CURSO_CONCESIONARIO_ATTR_DUENO))
		xfree(con->dueno);

	list_for_each_entry_safe(c, tmp, &con->garaje, head) {
		list_del(&c->head);
		curso_coche_free(c);
	}

	xfree(con);
}

void curso_concesionario_attr_unset_coche(struct concesionario *con,
					  uint32_t pos)
{
	int i = 0;
	struct coche *c, *tmp;

	if (pos < 0 || pos > con->num_coches)
		return;

	list_for_each_entry_safe(c, tmp, &con->garaje, head) {
		if (i == pos) {
			list_del(&c->head);
			curso_coche_free(c);
			break;
		}

		i++;
	}

	con->num_coches--;
}

static void curso_concesionario_set_data(struct concesionario *con,
					 uint16_t attr, const void *data)
{
	struct coche *c;

	if (attr > CURSO_CONCESIONARIO_ATTR_MAX)
		return;

	switch (attr) {
	case CURSO_CONCESIONARIO_ATTR_DUENO:
		if (con->dueno)
			xfree(con->dueno);

		con->dueno = strdup(data);
		break;
	case CURSO_CONCESIONARIO_ATTR_COCHE:
		if (con->num_coches > 50) {
			printf("El garaje esta lleno\n");
			break;
		}
		c = (struct coche *)data;
		list_add(&c->head, &con->garaje);
		con->num_coches++;
		break;
	}

	con->flags |= (1 << attr);
}

void curso_concesionario_attr_set_str(struct concesionario *con,
					uint16_t attr, const char *data)
{
	curso_concesionario_set_data(con, attr, data);
}

void curso_concesionario_attr_set_coche(struct concesionario *con,
					  uint16_t attr, struct coche *data)
{
	curso_concesionario_set_data(con, attr, data);
}

const void *curso_concesionario_attr_get_data(struct concesionario *con,
					      uint16_t attr, uint32_t pos)
{
	int i = 0;
	struct coche *c;

	if (!(con->flags & (1 << attr)))
		return NULL;

	switch(attr) {
	case CURSO_CONCESIONARIO_ATTR_DUENO:
		return con->dueno;
	case CURSO_CONCESIONARIO_ATTR_NUM_COCHES:
		return &con->num_coches;
	case CURSO_CONCESIONARIO_ATTR_COCHE:
		list_for_each_entry(c, &con->garaje, head) {
			if (i == pos)
				break;

			i++;
		}

		return c;
	}
	return NULL;
}

uint32_t curso_concesionario_attr_get_u32(struct concesionario *con,
					  uint16_t attr)
{
	const void *ret = curso_concesionario_attr_get_data(con, attr, 0);
	return ret == NULL ? 0 : *((uint32_t *)ret);
}

const char *curso_concesionario_attr_get_str(struct concesionario *con,
					     uint16_t attr)
{
	return curso_concesionario_attr_get_data(con, attr, 0);
}

struct coche *curso_concesionario_attr_get_coche(struct concesionario *con,
					         uint16_t attr, uint32_t pos)
{
	return (struct coche *)curso_concesionario_attr_get_data(con, attr,
								 pos);
}

int curso_concesionario_snprintf(char *buf, size_t size,
				 struct concesionario *con)
{
	int ret = 0;
	struct coche *c;

	ret += snprintf(buf, size,
			"el concesionario propiedad de %s, tiene %d y son:\n",
			con->dueno, con->num_coches);

	list_for_each_entry(c, &con->garaje, head) {
		ret += curso_coche_snprintf(buf + ret, size - ret, c);
		ret += snprintf(buf + ret, size - ret, "\n");
	}

	return ret;
}
