#include <main.h>

#ifdef NO_ASSERT
void	do_nothing(int sig)
{
	(void) sig;
	return ;
}

// to deactivate assert interrupt
// comment later duo to unallowed fn
#include <signal.h>
void	deactivate_assert_interrupt(void)
{
	printf("dactivating assert interrupt\n");
	struct sigaction sig_data = {0};
	sig_data.sa_handler = do_nothing;
	sigemptyset(&sig_data.sa_mask);
	sig_data.sa_mask = 0;
	sigaction(SIGTRAP, &sig_data, 0);
	raise(SIGTRAP);//test
}
#endif //NO_ASSERT

int	example_add(int a, int b)
{
	return (a + b);
}

bool	example_test(void)
{
	const int	tests[5][3] = {
		{1, 1, 2},          // 1 + 1 = 2
		{-2, 10, 8},        // -2 + 10 = 8
		{0, 0, 0},          // 0 + 0 = 0
		{100, -100, 0},     // 100 - 100 = 0
		{-5, -5, -10}       // -5 + -5 = -10
	};
	const int	a = 0;
	const int 	b = 1;
	const int 	expected = 2;
	bool		all_tests_passed;
	size_t		i;

	i = 0;
	all_tests_passed = true;
	while (i < sizeof tests / sizeof tests[0])
	{
		int actual = example_add(tests[i][a], tests[i][b]);
		bool test_passed = actual == tests[i][expected];
		ft_assert(test_passed, "a + b != result", __LINE__, __FILE__);
		if (!test_passed)
			all_tests_passed = false;
		i++;
	}
	return (all_tests_passed);
}

void	tuple_tests(int *total_tests, int *passed_tests)
{
	if (is_point_test())
		*passed_tests += 1;
	*total_tests += 1;
	if (is_vec_test())
		*passed_tests += 1;
	*total_tests += 1;
}

void	test_print_4x4(void)
{
	t_mat4x4	*mtx4;
	int			i;
	int			k;
	int			dimension;

	mtx4 = malloc(sizeof(t_mat4x4) * 1);
	if (!mtx4)
		return ;
	dimension = mtx_get_matrix_dimension(MAT4x4);
	i = 0;
	while (i < dimension)
	{
		k = 0;
		while (k < dimension)
		{
			(*mtx4)[i][k] = 4.0;
			k++;
		}
		i++;
	}
	(*mtx4)[0][0] = 17.11;
	(*mtx4)[2][3] = 19.01;
	mtx_print_matrix(mtx4, MAT4x4);
	free (mtx4);
}

void	test_print_3x3(void)
{
	t_mat3x3	*mtx3;
	int			i;
	int			k;
	int			dimension;

	mtx3 = malloc(sizeof(t_mat3x3) * 1);
	if (!mtx3)
		return ;
	dimension = mtx_get_matrix_dimension(MAT3x3);
	i = 0;
	while (i < dimension)
	{
		k = 0;
		while (k < dimension)
		{
			(*mtx3)[i][k] = 3.0;
			k++;
		}
		i++;
	}
	mtx_print_matrix(mtx3, MAT3x3);
	free (mtx3);
}
void	test_print_2x2(void)
{
	t_mat2x2	*mtx2x2;
	int			i;
	int			k;
	int			dimension;

	mtx2x2 = malloc(sizeof(t_mat2x2) * 1);
	if (!mtx2x2)
		return ;
	dimension = mtx_get_matrix_dimension(MAT2X2);
	i = 0;
	while (i < dimension)
	{
		k = 0;
		while (k < dimension)
		{
			(*mtx2x2)[i][k] = 0.0;
			k++;
		}
		i++;
	}
	mtx_print_matrix(mtx2x2, MAT2X2);
	free (mtx2x2);
}

void	test_print_matrix(void)
{
	test_print_2x2();
	printf("\n");
	test_print_3x3();
	printf("\n");
	test_print_4x4();
	printf("\n");
}

void	matrix_test(void)
{
	test_print_matrix();
	//TODO: Multiplication of Matrices
}

int	main(void)
{
#ifdef NO_ASSERT
	deactivate_assert_interrupt();
#endif
	matrix_test();
	return (0);
}
// int	main(void)
// {
// #ifdef NO_ASSERT
// 	deactivate_assert_interrupt();
// #endif
// 	int	passed = 0;
// 	int	total = 0;
// 	if (example_test())
// 		passed++;
// 	total++;
// 	tuple_tests(&total, &passed);
// 	if (total == passed)
// 		printf("all tests passed!\n");
// 	else
// 		printf("%d of %d test passed\n", passed, total);
// 	return (0);
// }
