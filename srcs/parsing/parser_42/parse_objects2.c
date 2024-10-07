#include <main.h>
#include <ft_engine.h>
#include <parser_42.h>

static void	set_transform_cylinder(t_cylinder *cyl, t_vec axis, double radius,
	t_point center)
{
	t_trans_cy_norm	n;

	n.rotation = mtx_new_ident(MAT4X4);
	n.scaleing_radius = mtx_scale(radius, 1, radius);
	n.translation = mtx_translate(center.x, center.y, center.z);
	n.transformation = mtx_new_ident(MAT4X4);
	if (eq_t(norm(new_vec(0, -1, 0)), axis))
		n.rotation = mtx_rotation_x(M_PI);
	else if (!eq_t(norm(new_vec(0, 1, 0)), axis))
	{
		n.rot = cross_prod(norm(new_vec(0, 1, 0)), axis);
		n.angle = acos(dot_prod(norm(new_vec(0, 1, 0)), axis));
		n.rotation = mtx_rotation_axis_angle(n.rot, n.angle);
	}
	n.transformation = mtx_mult_mm(n.transformation, n.translation);
	n.transformation = mtx_mult_mm(n.transformation, n.rotation);
	n.transformation = mtx_mult_mm(n.transformation, n.scaleing_radius);
	eng_set_transform((t_obj_ptr)cyl, n.transformation);
}

void	parse_cylinder(t_main *m_data, char *line,
			size_t mem_points[PARSER_MEM_SIZE])
{
	t_cylinder	cyl;
	t_point		center;
	t_vec		axis;
	double		radius;
	double		height;

	line += 2;
	cyl = eng_new_cylinder();
	cyl.closed = true;
	str_to_tuple(line, &center, &line, 1.0);
	center = handle_point_collision(mem_points, center, PARSER_OFFSET_CYLINDER);
	str_to_tuple(line, &axis, &line, 0.0);
	axis = norm(axis);
	if (!ft_isdigit(*line))
		parser_error("parsing error", __FILE__, __LINE__, 100);
	radius = str_to_float(line) / 2;
	skip_float(&line);
	height = str_to_float(line);
	cyl.max = height / 2;
	cyl.min = -height / 2;
	skip_float(&line);
	str_to_fcolor(line, &cyl.base_obj.material.fcolor, &line);
	set_transform_cylinder(&cyl, axis, radius, center);
	eng_add_obj_to_world(&m_data->engine.world, (t_obj_ptr) & cyl);
}

static void	set_transform_cone(t_cone *cone, t_vec axis, double radius,
	t_point center)
{
	t_trans_cy_norm	n;

	n.rotation = mtx_new_ident(MAT4X4);
	n.scaleing_radius = mtx_scale(radius, 1, radius);
	n.translation = mtx_translate(center.x, center.y, center.z);
	n.transformation = mtx_new_ident(MAT4X4);
	if (eq_t(norm(new_vec(0, -1, 0)), axis))
		n.rotation = mtx_rotation_x(M_PI);
	else if (!eq_t(norm(new_vec(0, 1, 0)), axis))
	{
		n.rot = cross_prod(norm(new_vec(0, 1, 0)), axis);
		n.angle = acos(dot_prod(norm(new_vec(0, 1, 0)), axis));
		n.rotation = mtx_rotation_axis_angle(n.rot, n.angle);
	}
	n.transformation = mtx_mult_mm(n.transformation, n.translation);
	n.transformation = mtx_mult_mm(n.transformation, n.rotation);
	n.transformation = mtx_mult_mm(n.transformation, n.scaleing_radius);

	eng_set_transform((t_obj_ptr)cone, n.transformation);
}

void	parse_cone(t_main *m_data, char *line,
			size_t mem_points[PARSER_MEM_SIZE])
{
	t_cone		cone;
	t_point		center;
	t_vec		axis;
	double		radius;
	double		height;

	line += 2;
	cone = eng_new_cone();
	cone.closed = true;
	str_to_tuple(line, &center, &line, 1.0);
	center = handle_point_collision(mem_points, center, PARSER_OFFSET_CYLINDER);
	str_to_tuple(line, &axis, &line, 0.0);
	axis = norm(axis);
	if (!ft_isdigit(*line))
		parser_error("parsing error", __FILE__, __LINE__, 100);
	radius = str_to_float(line) / 2;
	skip_float(&line);
	height = str_to_float(line);
	cone.max = height;
	cone.min = 0;
	skip_float(&line);
	str_to_fcolor(line, &cone.base_obj.material.fcolor, &line);
	set_transform_cone(&cone, axis, radius, center);
	eng_add_obj_to_world(&m_data->engine.world, (t_obj_ptr) & cone);
}

void	parse_double_cone(t_main *m_data, char *line,
			size_t mem_points[PARSER_MEM_SIZE])
{
	t_cone		cone;
	t_point		center;
	t_vec		axis;
	double		radius;
	double		height;

	line += 3;
	cone = eng_new_cone();
	cone.closed = true;
	str_to_tuple(line, &center, &line, 1.0);
	center = handle_point_collision(mem_points, center, PARSER_OFFSET_CYLINDER);
	str_to_tuple(line, &axis, &line, 0.0);
	axis = norm(axis);
	if (!ft_isdigit(*line))
		parser_error("parsing error", __FILE__, __LINE__, 100);
	radius = str_to_float(line) / 2;
	skip_float(&line);
	height = str_to_float(line);
	cone.max = height / 2;
	cone.min = -height / 2;
	skip_float(&line);
	str_to_fcolor(line, &cone.base_obj.material.fcolor, &line);
	set_transform_cone(&cone, axis, radius, center);
	eng_add_obj_to_world(&m_data->engine.world, (t_obj_ptr) & cone);
}
