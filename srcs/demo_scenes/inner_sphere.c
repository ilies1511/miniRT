#include <ft_material.h>
#include <ft_scene.h>
#include <main.h>
#include <ft_colors.h>

static void	init_world(t_world *world)
{
	t_light	light_1 = eng_point_light(new_fcolor(0, 0.3, 1, 1), new_point(1, 10, -1));
	t_light	light_2 = eng_point_light(new_fcolor(1, 0.3, 0, 1), new_point(-20, 10, 30));
	t_sphere	sph1 = eng_new_glass_sphere();
	t_plane		floor	 = eng_new_plane();
	const struct s_skew	skew = {.xy=0.03, .xz=0.41, .yx=0.67, .yz=0.123, .zx=0.31 ,.zy=0.13};

	eng_set_transform((t_obj *)&sph1, mtx_scale(30, 30, 30));
	sph1.base_obj.material.pattern = pat_square3d_pattern(new_fcolor(1, 0, 0, 1), new_fcolor(0,0,1, 1));
	sph1.base_obj.material.reflective = 0;
	sph1.base_obj.material.transparency = 0.9;
	sph1.base_obj.material.ambient = 0;
	eng_set_transform((t_obj_ptr) sph1.base_obj.material.pattern, mtx_scale(0.07, 0.07, 0.07));
	eng_set_transform((t_obj_ptr) sph1.base_obj.material.pattern, mtx_skew(skew));
	floor.base_obj.material.fcolor.r = 0xFF;
	floor.base_obj.material.fcolor.g = 0x00;
	floor.base_obj.material.fcolor.b = 0x00;
	floor.base_obj.material.ambient = 0;
	floor.base_obj.material = material_silver_and_gold();
	floor.base_obj.material.bump = bump_wave();
	eng_add_obj_to_world(world, (t_obj *) & light_1);
	eng_add_obj_to_world(world, (t_obj *) & light_2);
	eng_add_obj_to_world(world, (t_obj *) & sph1);
	eng_add_obj_to_world(world, (t_obj *) & floor);

}
static void	init_camera(t_main *m_data)
{
t_camera	*camera;

	if (m_data->camera_type == USER_INPUT)
		return ;
	m_data->camera_type = PRESET;
camera = &(m_data->engine.camera);
*(camera) = eng_new_camera(WIDTH, HEIGHT, M_PI / 3);
	eng_set_transform((t_obj *)camera, sc_transforme_view(new_point(0, 2, -10),
		new_point(0, 0, 0), new_vec(0, 1, 0)));
}

void	inner_sphere_demo(void *main_data)
{
	t_main		*m_data = (t_main *)main_data;
	t_world		*world;

	init_camera(m_data);
	world = &m_data->engine.world;
	init_world(world);
	//store_as_plain_ppm(m_data, "asd.ppm");
}
