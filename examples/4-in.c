#include <stdio.h>
#include <assert.h>
#include "libflat.h"

void flatten_debug_info();
void flatten_set_debug_flag(int flag);
void flatten_debug_memory();

int main(void) {

	FILE* out = fopen("/tmp/memory.img", "w");
	assert(out);
	flatten_init();

	static char carr[] = "You don't need to be great to start, "
			"but you need to start to be great";

	const char* start = carr;
	const char* middle = carr + 41;

	flatten_set_debug_flag(7);

	FOR_ROOT_POINTER(start,
		FLATTEN_TYPE(const char*,&start);
		FOR_POINTER(const char*,s,&start,
			FLATTEN_STRING(s);
		);
	);

	FOR_ROOT_POINTER(middle,
		FLATTEN_TYPE(const char*,&middle);
		FOR_POINTER(const char*,s,&middle,
			FLATTEN_STRING(s);
		);
	);

	flatten_debug_info();

	printf("&carr[0]: %p\n", &carr[0]);
	printf("&start: %p -> %p\n", &start, start);
	printf("&middle: %p -> %p\n", &middle, middle);

	assert(flatten_write(out) == 0);

	flatten_fini();
	fclose(out);

	return 0;
}
