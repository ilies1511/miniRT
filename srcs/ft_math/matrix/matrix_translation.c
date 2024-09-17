#include <ft_matrix.h>

t_matrix	mtx_translation_izi(t_tuple tuple)
{
	t_matrix	ret;

	ret = mtx_new_ident(MAT4X4);
	ret.m[0][3] = tuple.x;
	ret.m[1][3] = tuple.y;
	ret.m[2][3] = tuple.z;
	return (ret);
}

/*
	ret.m[0][3] += x;
	Warum "+="
*/
t_matrix	mtx_translation(float x, float y, float z)
{
	t_matrix	ret;

	ret = mtx_new_ident(MAT4X4);
	ret.m[0][3] += x;
	ret.m[1][3] += y;
	ret.m[2][3] += z;
	return (ret);
}
