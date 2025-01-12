#include <main.h>
#include <time.h>

static void add_objs(t_world *world)
{
	t_sphere	floor;
	t_light		light;
	t_light		light2;
	t_sphere	left_wall;
	t_sphere	right_wall;
	t_sphere	sph_mid;
	t_sphere	sph_right;
	t_sphere	sph_left;


	floor = eng_new_sphere();
	eng_set_transform((t_obj_ptr)&floor, mtx_scale(10, 0.01, 10));
	floor.base_obj.material.fcolor = new_fcolor(1, 0.9, 0.9, 1);
	floor.base_obj.material.specular = 0;
	eng_add_obj_to_world(world, (t_obj_ptr)&floor);

	left_wall = eng_new_sphere();
	// left_wall.base_obj.material.fcolor = new_fcolor(1, 0.9, 0.9, 0.9);
	eng_set_transform((t_obj_ptr)&left_wall, mtx_translate(0, 0, 5));
	eng_set_transform((t_obj_ptr)&left_wall, mtx_rotation_y(-M_PI / 4));
	eng_set_transform((t_obj_ptr)&left_wall, mtx_rotation_x(M_PI / 2));
	eng_set_transform((t_obj_ptr)&left_wall, mtx_scale(10, 0.01, 10));
	left_wall.base_obj.material = floor.base_obj.material;
	eng_add_obj_to_world(world, (t_obj_ptr)&left_wall);

	right_wall = eng_new_sphere();
	// right_wall.base_obj.material.fcolor = new_fcolor(1, 0.9, 0.9, 1);
	right_wall.base_obj.material = floor.base_obj.material;
	eng_set_transform((t_obj_ptr)&right_wall, mtx_translate(0, 0, 5));
	eng_set_transform((t_obj_ptr)&right_wall, mtx_rotation_y(M_PI / 4));
	eng_set_transform((t_obj_ptr)&right_wall, mtx_rotation_x(M_PI / 2));
	eng_set_transform((t_obj_ptr)&right_wall, mtx_scale(10, 0.01, 10));
	eng_add_obj_to_world(world, (t_obj_ptr)&right_wall);

	sph_right = eng_new_sphere();
	eng_set_transform((t_obj_ptr)&sph_right, mtx_translate(1.5, 0.5, -0.5));
	eng_set_transform((t_obj_ptr)&sph_right, mtx_scale(0.5, 0.5, 0.5));
	sph_right.base_obj.material.fcolor = new_fcolor(1, 1, 1, 1);
	sph_right.base_obj.material.diffuse = 0.7;
	sph_right.base_obj.material.specular = 0.3;
	eng_add_obj_to_world(world, (t_obj_ptr)&sph_right);

	sph_mid = eng_new_sphere();
	eng_set_transform((t_obj_ptr)&sph_mid , mtx_translate(-0.5, 1, 0.5));
	sph_mid.base_obj.material.fcolor = new_fcolor(1, 1, 1, 1);
	sph_mid.base_obj.material.diffuse = 0.7;
	sph_mid.base_obj.material.specular = 0.3;
	eng_add_obj_to_world(world, (t_obj_ptr)&sph_mid);

	sph_left = eng_new_sphere();
	eng_set_transform((t_obj_ptr)&sph_left, mtx_translate(-1.5, 0.33, -0.75));
	eng_set_transform((t_obj_ptr)&sph_left, mtx_scale(0.33, 0.33, 0.33));
	sph_left.base_obj.material.fcolor = new_fcolor(1, 1, 1, 1);
	sph_left.base_obj.material.diffuse = 0.7;
	// sph_left.base_obj.material.shininess = 500;
	sph_left.base_obj.material.specular = 0.3;
	eng_add_obj_to_world(world, (t_obj_ptr)&sph_left);

	light = eng_point_light(new_fcolor(1, 1, 1, 1), new_point(10, 10, -10));
	eng_add_obj_to_world(world, (t_obj_ptr)&light);

	light2 = eng_point_light(new_fcolor(1, 1, 1, 1), new_point(-10, 10, -10));
	// eng_add_obj_to_world(world, (t_obj_ptr)&light2);
}

void create_filename(char *filename, size_t size) {
	// Hole das aktuelle Datum und die Uhrzeit
	time_t rawtime;
	struct tm *timeinfo;
	char buffer[80];
	time(&rawtime);
	timeinfo = localtime(&rawtime);
	// Formatierung des Zeitstempels im deutschen Format: z.B. "26-09-2024_15-30-45"
	strftime(buffer, sizeof(buffer), "%d-%m-%Y_%H-%M-%S", timeinfo);
	// Erstelle den Dateinamen mit dem Zeitstempel
	snprintf(filename, size, "screenshot_%s.ppm", buffer);
}

void	sphere_test_v6(void *main_data)
{
	t_main			*m_data = (t_main *)main_data;
	t_canvas		canvas = m_data->engine.canvas;
	t_camera		camera;
	t_world			*world;
	char			filename[100];

	camera = eng_new_camera(WIDTH, HEIGHT, M_PI / 3);
	eng_set_transform((t_obj_ptr)&camera, sc_transforme_view(new_point(0, 1.5, -5),
			new_point(0, 1, 0), new_vec(0, 1, 0)));
	static bool first = true;
	world = &m_data->engine.world;
	create_filename(filename, sizeof(filename));
	if (first)
	{
		first = false;
		add_objs(world);
	}
	eng_render(camera, *world, canvas);
	// if (first)
	// 	store_as_plain_ppm(m_data, filename);
}
