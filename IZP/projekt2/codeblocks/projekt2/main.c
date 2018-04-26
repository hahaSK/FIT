/**
 * Author: Juraj Lahvicka, 164322
 * ID: (xlahvi00)
 * Subject: IZP
 * Name: Projekt2 - iteračné výpočty
 * URL: https://wis.fit.vutbr.cz/FIT/st/cwk.php?title=IZP:Projekt2&csid=647749&id=12214
 */

#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define iteration_count (9) //the result from taylor tangens function has the required precision (magic number)

//Result definitions
#define HELP 0
#define TAN 1
#define MA 2      //argument -m with parameter -A (Alpha) only
#define MAB 3      //argument -m with parameter -A (Alpha) and -B (Beta)
#define CA 4      //argument -c with parameter -A (Alpha) only
#define CAB 5      //argument -c with parameter -A (Alpha) and -B (Beta)

//Array of argumets
#define ALPHA 0
#define ARGN 1
#define ARGM 2
#define BETA 3
#define ARGX 4


#define COLOR_RED  "\x1b[31m"
#define COLOR_RESET "\x1b[0m"

/**
 * Calulates the tangens function through concatenation fraction
 * @param x - angle A in radians
 * @param n - number of iterations
 * @return result
 */

double cfrac_tan(double x, unsigned int n)
{
	double a;
	double b = x * x;
	double cf = 0.;
	for (unsigned int i = n; i > 1; i--)
	{
		a = 2 * i - 1;
		cf = b / (a - cf);
	}
	return x / (1 - cf);
}

/**
 * Calulates the tangens function through Taylor's polynome
 * @param x - angle Alpha in radians
 * @param n - number of iterations
 * @return result
 */

double taylor_tan(double x, unsigned int n)
{
	long long numerator[13] = {1, 1, 2, 17, 62, 1382, 21844, 929569, 6404582, 443861162, 18888466084, 113927491862, 58870668456604};
	long long denominator[13] = {1, 3, 15, 315, 2835, 155925, 6081075, 638512875, 10854718875, 1856156927625, 194896477400625, 49308808782358125, 3698160658676859375};

	double t = x;
	double s = t;
	unsigned int i = 1;

	while (i < n)
	{
		t *= x * x;
		s += t * numerator[i] / denominator[i];
		i++;
	}

	return s;
}

/**
 * Calls functions to calculate tangens through different mathematical methods
 * @param A - angle Aplha in radians
 * @param N - starting number of iterations
 * @param M - ending number of iterations
 */

void calculate_tan(double A, int N, int M)
{
	double taylor_result;

	for (int i = N; i <= M; i++)
	{
		taylor_result = taylor_tan(A, i);
		double cfrac_result = cfrac_tan(A, i);

		double taylor_difference = fabs(tan(A) - taylor_result);
		double cfrac_difference = fabs(tan(A) - cfrac_result);

		printf("%d %e %e %e %e %e\n", i, tan(A), taylor_result, taylor_difference, cfrac_result, cfrac_difference);
	}
}

/**
 * Error reporting
 * @param result - specific number of error
 */

void error_report(int result)
{
	switch (result)
	{
		case -3:
			printf(COLOR_RED "--tan" COLOR_RESET " argument has invalid number of arguments. For more informations use:\n" COLOR_RED "--help\n" COLOR_RESET);
			break;
		case -4:
			printf(COLOR_RED "-m" COLOR_RESET " argument has invalid number of arguments. For more informations use:\n" COLOR_RED "--help\n" COLOR_RESET);
			break;
		case -5:
			printf(COLOR_RED "-c" COLOR_RESET " argument has invalid number of arguments. For more informations use:\n" COLOR_RED "--help\n" COLOR_RESET);
			break;
		case -6:
			printf(COLOR_RED "N M" COLOR_RESET " out of interval. For more informations use:\n" COLOR_RED "--help\n" COLOR_RESET);
			break;
		case -7:
			printf(COLOR_RED "A" COLOR_RESET " Angle is out of interval. For more informations use:\n" COLOR_RED "--help\n" COLOR_RESET);
			break;
		case -8:
			printf(COLOR_RED "B" COLOR_RESET " Angle is out of interval. For more informations use:\n" COLOR_RED "--help\n" COLOR_RESET);
			break;
		case -9:
			printf(COLOR_RED "X" COLOR_RESET " Distance is out of interval. For more informations use:\n" COLOR_RED "--help\n" COLOR_RESET);
			break;
		case -10:
			printf("Invalid conversion to double. Please check your numbers again. (Replace , for . if any).\n");
			break;
	}

}

/**
 * Checks if entered arguments are in required intervals
 * @param result - specific number of result
 * @param arguments - entered arguments (A, N, M, B, X)
 * @return specific number of error or number of mode
 */

int intervals(int result, double *arguments)
{

	if (result == TAN)
	{
		int N = (int) (arguments[ARGN]), M = (int) (arguments[ARGM]);
		if (0 >= N || 0 >= M || N > M || N >= 14 || M >= 14)
			return -6;
		calculate_tan(arguments[ALPHA], N, M);
		return result;
	}

	if (arguments[ALPHA] <= 0.0 || arguments[ALPHA] > 1.4)
		return -7;

	if (result == MAB || result == CAB)
	{
		if (arguments[BETA] <= 0.0 || arguments[BETA] > 1.4)
			return -8;
	}

	if (result == CA || result == CAB)
	{
		if (arguments[ARGX] <= 0.0 || arguments[ARGX] > 100.0)
			return -9;
	}

	return result;
}

/**
 * Test if conversion to double is valid
 * @param arg - arguments
 * @param str_tod_err - sets true if Error in conversion
 * @return converted argument
 */

double test_strtod(char *arg, bool *str_tod_err)
{
	char *err = NULL;
	strtod(arg, &err);
	if (*err != '\0')
	{
		*str_tod_err=true;
	}
		return strtod(arg, &err);
}

/**
 * Loads arguments
 * @param argc - number of arguments
 * @param argv - arguments
 * @param arguments - loads arguments into array
 * @return specific value of error or mode
 */

int load_arguments(int argc, char *argv[], double *arguments)
{
	bool str_tod_err=false;

	if (argc == 1)
	{
		printf("No parameter (user's input). For more informations use:\n" COLOR_RED "--help\n" COLOR_RESET);
		return -2;
	}

	for (int i = 1; i < argc; i++)
	{
		if (strcmp(argv[i], "--help") == 0)
		{
			printf("This Aplication was made by Juraj Lahvicka (xlahvi00)\n"
										 "Accepted arguments by application:\n"
										 COLOR_RED "--tan A N M\n"
										 "[-c X] -m A [B]\n" COLOR_RESET
										 COLOR_RED "--tan" COLOR_RESET " compares calculation of tangens of angle " COLOR_RED "A" COLOR_RESET " (Alpha) (in radians) from math.h library, Taylor's polynome and concatenation fraction.\n"
										 COLOR_RED "  N M" COLOR_RESET " arguments indicates the number of steps (interval) of iterations the calculations should calculate. ! 0 < N <= M < 14 !\n"
										 COLOR_RED "-m" COLOR_RESET " argument calculates and measures distances.\n"
										 COLOR_RED "  A" COLOR_RESET " (Alha) is angle (in radians). Application calculates and prints the distance of object. ! 0 < A <= 1.4 ! \n"
										 COLOR_RED "  B" COLOR_RESET " (Beta) is angle (in radians) and it's OPTIONAL parameter. If it is entered, the application also calculates the height of object.\n"
										 COLOR_RED "-c X" COLOR_RESET " parameter -c sets the initial height of measuring device. The height is given by X. If -c is not entered, the initial height is 1.5 m. ! 0 < X <= 100 !\n");
			return HELP;
		}
		else if (strcmp(argv[i], "--tan") == 0)
		{
			if (argc == 5)
			{
				arguments[ALPHA] = test_strtod(argv[2],&str_tod_err);
				arguments[ARGN] = test_strtod(argv[3],&str_tod_err);
				arguments[ARGM] = test_strtod(argv[4],&str_tod_err);

				if (str_tod_err == true)
					return -10;

				return TAN;
			}
			else
				return -3;
		}
		else if (strcmp(argv[i], "-m") == 0)
		{
			if (argc == 3)
			{
				arguments[ALPHA] = test_strtod(argv[2],&str_tod_err);
				arguments[ARGX] = 1.5;

				if (str_tod_err == true)
					return -10;

				return MA;
			}

			else if (argc == 4)
			{
				arguments[ALPHA] = test_strtod(argv[2],&str_tod_err);
				arguments[BETA] = test_strtod(argv[3],&str_tod_err);
				arguments[ARGX] = 1.5;

				if (str_tod_err == true)
					return -10;

				return MAB;
			}
			else
				return -4;
		}
		else if (strcmp(argv[i], "-c") == 0)
		{
			if (argc == 5)
			{
				if(strcmp(argv[i+1], "-m") == 0)
					return -5;

				arguments[ALPHA] = test_strtod(argv[4],&str_tod_err);
				arguments[ARGX] = test_strtod(argv[2],&str_tod_err);

				if (str_tod_err == true)
					return -10;

				return CA;
			}
			if (argc == 6)
			{
				arguments[ALPHA] = test_strtod(argv[4],&str_tod_err);
				arguments[BETA] = test_strtod(argv[5],&str_tod_err);
				arguments[ARGX] = test_strtod(argv[2],&str_tod_err);

				if (str_tod_err == true)
					return -10;

				return CAB;
			}
			else
				return -5;
		}
		else
		{
			printf("Unrecognised parameter (user's input). For more informations use:\n" COLOR_RED "--help\n" COLOR_RESET);
			return -1;
		}
	}

	return 0;
}

/**
 * Calculates distance and height of object
 * @param result - specific mode
 * @param arguments - entered arguments (A, N, M, B, X)
 */

void calc(int result, double arguments[4])
{
	double d = arguments[ARGX] / cfrac_tan(arguments[ALPHA], iteration_count), v;

	if (result == MA || result == CA)
		v = cfrac_tan(arguments[ALPHA], iteration_count) * d + arguments[ARGX];
	else
		v = cfrac_tan(arguments[BETA], iteration_count) * d + arguments[ARGX];

	switch (result)
	{
		case MA:
			printf("%.10e\n", d);
			break;
		case MAB:
			printf("%.10e\n%.10e\n", d, v);
			break;
		case CA:
			printf("%.10e\n", d);
			break;
		case CAB:
			printf("%.10e\n%.10e\n", d, v);
			break;
	}

}


int main(int argc, char *argv[])
{
	int result;
	double arguments[4];    //[Alpha,N,M,Beta,Height (X)]

	result = load_arguments(argc, argv, arguments);

	if (result > HELP)
	{
		result = intervals(result, arguments);
		calc(result, arguments);
	}

	if (result < HELP)
		error_report(result);

	return result;
}
