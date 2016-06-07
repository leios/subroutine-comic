/*-------------subroutine.cpp-------------------------------------------------//
*
* Purpose: We are creating a webcomic with code using cairo.
*
*   Notes: This is where we keep main()
*-----------------------------------------------------------------------------*/

#include <cairo.h>
#include <iostream>

int main (){

    // Creating initial surface to draw on.
    cairo_surface_t *surface =
        cairo_image_surface_create (CAIRO_FORMAT_ARGB32, 1200, 400);
    cairo_t *cr =
        cairo_create (surface);

    cairo_select_font_face (cr, "serif", CAIRO_FONT_SLANT_NORMAL, 
                            CAIRO_FONT_WEIGHT_BOLD);
    cairo_set_font_size (cr, 32.0);
    cairo_set_source_rgb (cr, 1.0, 0.0, 1.0);
    cairo_move_to (cr, 100.0, 100.0);
    //cairo_show_text (cr, "Hello, world");

    cairo_pattern_t *radpat, *linpat;
    
    radpat = cairo_pattern_create_radial (0.25, 0.25, 0.1,  0.5, 0.5, 0.5);
    cairo_pattern_add_color_stop_rgb (radpat, 0,  1.0, 0.8, 0.8);
    cairo_pattern_add_color_stop_rgb (radpat, 1,  0.9, 0.0, 0.0);
    
    for (size_t i=1; i<10; i++)
        for (size_t j=1; j<10; j++)
            cairo_rectangle (cr, i/10.0 - 0.04, j/10.0 - 0.04, 0.08, 0.08);
    cairo_set_source (cr, radpat);
    cairo_fill (cr);
    
    linpat = cairo_pattern_create_linear (0.25, 0.35, 0.75, 0.65);
    cairo_pattern_add_color_stop_rgba (linpat, 0.00,  1, 1, 1, 0);
    cairo_pattern_add_color_stop_rgba (linpat, 0.25,  0, 1, 0, 0.5);
    cairo_pattern_add_color_stop_rgba (linpat, 0.50,  1, 1, 1, 0);
    cairo_pattern_add_color_stop_rgba (linpat, 0.75,  0, 0, 1, 0.5);
    cairo_pattern_add_color_stop_rgba (linpat, 1.00,  1, 1, 1, 0);
    
    cairo_rectangle (cr, 0.0, 0.0, 1, 1);
    cairo_set_source (cr, linpat);
    //cairo_fill (cr);
    cairo_paint(cr);

    // writing and destroying rendering device
    cairo_destroy (cr);
    cairo_surface_write_to_png (surface, "subroutine.png");
    cairo_surface_destroy (surface);

}
