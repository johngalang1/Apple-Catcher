#include <osbind.h>
#include "raster.h"
#include "bitmaps.h"

int main()
{
	UINT32 *FB32 = Physbase();  
	UINT16 *FB16 = Physbase();
	plot_apple_32(FB32, 400, 100, apple_bitmap, APPLE_HEIGHT); 
	plot_basket_64(FB32, 400, 150, basket_bitmap, BASKET_HEIGHT);
	plot_char(FB16, 200, 200, letterA_bitmap, CHARACTER_HEIGHT);

	return 0;
}
