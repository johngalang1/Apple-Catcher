#include <osbind.h>
#include "raster.h"
#include "bitmaps.h"

int main()
{
	UINT32 *FB = Physbase();  
	plot_apple_32(FB, 400, 100, apple_bitmap, APPLE_HEIGHT); 
	plot_basket_64(FB, 400, 200, basket_bitmap, BASKET_HEIGHT);
	plot_vertical_line(FB, 100, 0, 400);
	plot_vertical_line(FB, 200, 100, 300);

	return 0;
}
