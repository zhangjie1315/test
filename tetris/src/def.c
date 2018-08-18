#include <def.h>

struct data t = {.x=2, .y=0};
int background[H][W];
int cur = 0;
int next = 0;
struct info g_info;
int nfd = -1;

struct shape shape_arr[7] = {
	{
		0, 0, 0, 0, 0,
		0, 0, 1, 0, 0,
		0, 1, 1, 1, 0,
		0, 0, 0, 0, 0,
		0, 0, 0, 0, 0
	},
	{
		0, 0, 0, 0, 0,
		0, 1, 1, 0, 0,
		0, 0, 1, 1, 0,
		0, 0, 0, 0, 0,
		0, 0, 0, 0, 0
	},
	{
		0, 0, 0, 0, 0,
		0, 0, 1, 1, 0,
		0, 1, 1, 0, 0,
		0, 0, 0, 0, 0,
		0, 0, 0, 0, 0
	},
	{
		0, 0, 0, 0, 0,
		0, 0, 1, 0, 0,
		0, 0, 1, 0, 0,
		0, 0, 1, 1, 0,
		0, 0, 0, 0, 0
	},
	{
		0, 0, 0, 0, 0,
		0, 0, 1, 0, 0,
		0, 0, 1, 0, 0,
		0, 1, 1, 0, 0,
		0, 0, 0, 0, 0
	},
	{
		0, 0, 0, 0, 0,
		0, 0, 1, 0, 0,
		0, 0, 1, 0, 0,
		0, 0, 1, 0, 0,
		0, 0, 1, 0, 0
	},
	{
		0, 0, 0, 0, 0,
		0, 1, 1, 0, 0,
		0, 1, 1, 0, 0,
		0, 0, 0, 0, 0,
		0, 0, 0, 0, 0
	}
};

