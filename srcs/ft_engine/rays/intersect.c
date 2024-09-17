#include <main.h>
#include <ft_engine.h>
#include <libft.h>

static bool	swap_intersc(void *a, void *b)
{
	return (((t_intersc *)a)->t > ((t_intersc *)b)->t);
}

void	eng_sort_intersc(t_intersc_arr *interscs)
{
	ft_sort(interscs->arr, sizeof(t_intersc), interscs->count, swap_intersc);
}

t_intersc	eng_add_intersc(t_intersc_arr *interscs, t_obj *obj, float t)
{
	t_intersc		intersc;

	intersc.t = t;
	intersc.type = obj->type;
	intersc.obj = obj;
	if (!interscs->arr)
		*interscs = eng_new_intersc_arr();
	dyn_arr_add_save((void **)(&interscs->arr), &intersc, interscs->count++);
	return (intersc);
}

t_intersc_arr	eng_new_intersc_arr(void)
{
	t_intersc_arr	arr;

	arr.arr = dyn_arr_init(sizeof(t_intersc), 0);
	if (!arr.arr)
		ft_error("malloc fail", __FILE__, __LINE__, 1);
	arr.count = 0;
	return (arr);
}


/*
//Wikipedia line sphere intersection step by step:
point px: intersection point
float t: scalar for ray->direct to reach the intersection point and
	the var we want

// ray formular with px beeing a point on the ray
1:	ray->origin + t * ray.direct = px
// sphere formular with px beeing on the surface of the sphere
2:	|| px - sph.origin || = sph.rad
// substitude px in 2 by 1 since px should meet both formulars
-> || (ray->origin + t * ray.direct) - sph.origin || = sph.rad
// start solving for t:
-> || ray->origin - sph.origin + t * ray.direct  || = sph.rad
// vec ori_diff = ray->origin - sph.origin
-> || ori_diff + t * ray->direct  || = sph.rad
-> sqr(dot(ori_diff + t * ray->direct, ori_diff + t * ray.direct)) = sph.rad
// square both sides to get rid of sqrt
->dot(ori_diff + t * ray->direct, ori_diff + t * ray.direct) = sph.rad^2
//distributive law
->dot(ori_diff, ori_diff + t * ray->direct) + dot(t * ray.direct, ori_diff + t * ray.direct) = sph.rad^2
//distributive law
->dot(ori_diff, ori_diff) + dot(ori_diff, t * ray->direct) + dot(t * ray.direct, ori_diff) + dot(t * ray.direct, t * ray.direct) = sph.rad^2
->dot(ori_diff, ori_diff) + 2 * dot(ori_diff, t * ray->direct) + dot(t * ray.direct, t * ray.direct) = sph.rad^2
->dot(ori_diff, ori_diff) + 2 * t * dot(ori_diff, ray->direct) + t^2 * dot(ray.direct, ray.direct) = sph.rad^2
// form quadratic formular
//at^2 + tb + c = 0
//-sph.rad^2
->dot(ori_diff, ori_diff) + t * 2 * dot(ori_diff, ray->direct) + t^2 * dot(ray.direct, ray.direct) - sph.rad^2 = 0
->t^2 * dot(ray->direct, ray.direct) + 2 * t * dot(ori_diff, ray.direct) + dot(ori_diff, ori_diff) - sph.rad^2 = 0
// float	dot_direct = dot(ray->dircet, ray.direct)
// float	dot_diff_direct = dot(ori_diff, ray->direct);
// float	dot_diff = dot(ori_diff, ori_diff);
// a = dot_direct
// b =  2 *dot_diff_direct
// c = dot_diff - sph.rad^2
// t = (-b +- sqrt(b^2 - 4 * a * c)) / 2a
// float sqr_dot_diff_direct = dot_direct * dot_direct
-> t = -2*dot_diff_direct +- sqrt(sqr_dot_diff_direct - 4 * dot_direct * (dot_diff - sph.rad^2)) / (2 * dot_direct)
*/
// can be simplyfied by making assumtions like unit vectors, that the sphere
// is in the orgin, or has a radius of 1
// this function should always fork for spheres so I think we can simplyfy
// later when we can make some assumptions we can simplify
static void	eng_intersc_ray_sphere(t_intersc_arr *interscs, t_ray *ray, t_sphere *sph)
{
	t_vec	ori_diff = sub_t(ray->origin, sph->origin);
	float	dot_direct = dot_prod(ray->direct, ray->direct);
	float	dot_diff_direct = dot_prod(ori_diff, ray->direct);
	float	dot_diff = dot_prod(ori_diff, ori_diff);
	float	rad_sqr = sph->rad * sph->rad;
	float	a = dot_direct;
	float	b = 2 * dot_diff_direct;
	float	c = dot_diff - rad_sqr;
	float	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return ;
	float	sqrt_discriminant = sqrt(discriminant);
	float	t1 = (-b + sqrt_discriminant) / (2 * a);
	float	t2 = (-b - sqrt_discriminant) / (2 * a);
	eng_add_intersc(interscs, (t_obj *)sph, t1);
	eng_add_intersc(interscs, (t_obj *)sph, t2);
}

void	eng_intersc_ray(t_intersc_arr *interscs, t_ray *ray, t_obj *obj)
{
	if (obj->type == OBJ_SPHERE)
		eng_intersc_ray_sphere(interscs, ray, (t_sphere *)obj);
	else
		ft_assert(0, __FILE__, __LINE__, "eng_intersc_ray: invalid obj type");
}
