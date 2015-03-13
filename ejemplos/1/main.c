#include "concesionario.h"

int main(void)
{
	struct coche *c1, *c2;
	struct concesionario *con;
	char info[4000];

	c1 = curso_coche_alloc();

	curso_coche_attr_set_str(c1, CURSO_COCHE_ATTR_MATRICULA, "DF 67838 SE");
	curso_coche_attr_set_str(c1, CURSO_COCHE_ATTR_MARCA, "mini");
	curso_coche_attr_set_u32(c1, CURSO_COCHE_ATTR_ID, 0);

	c2 = curso_coche_alloc();

	curso_coche_attr_set_str(c2, CURSO_COCHE_ATTR_MATRICULA, "DF 8819 M");
	curso_coche_attr_set_str(c2, CURSO_COCHE_ATTR_MARCA, "BMW");
	curso_coche_attr_set_u32(c2, CURSO_COCHE_ATTR_ID, 0);

	con = curso_concesionario_alloc();

	curso_concesionario_attr_set_str(con, CURSO_CONCESIONARIO_ATTR_DUENO,
					 "Alvaro");

	curso_concesionario_attr_set_coche(con, CURSO_CONCESIONARIO_ATTR_COCHE,
					   c1);

	curso_concesionario_attr_set_coche(con, CURSO_CONCESIONARIO_ATTR_COCHE,
					   c2);

	curso_concesionario_snprintf(info, sizeof(info), con);
	printf("%s", info);

	curso_concesionario_free(con);
	return 0;
}
