/*-------------subroutine.cpp-------------------------------------------------//
*
* Purpose: We are creating a webcomic with code using cairo.
*
*   Notes: This is where we keep main()
*-----------------------------------------------------------------------------*/

#include <cairo.h>
#include <iostream>
#include <math.h>

// Function to draw initial layout
void create_scene(int num_box, int box_width, int box_height);

/*----------------------------------------------------------------------------//
* MAIN
*-----------------------------------------------------------------------------*/
int main (){

    create_scene(10, 500, 500);

/*
    // Creating initial surface to draw on.
    cairo_surface_t *surface =
        cairo_image_surface_create (CAIRO_FORMAT_ARGB32, 1000, 400);
    cairo_t *cr =
        cairo_create (surface);

    cairo_select_font_face (cr, "serif", CAIRO_FONT_SLANT_NORMAL, 
                            CAIRO_FONT_WEIGHT_BOLD);
    cairo_set_source_rgb (cr, 0, 0.0, 1.0);

    // Draws a line of width pixels thick
    int width = 50;
    cairo_move_to (cr, 0, 0);
    cairo_line_to (cr, 1000, 0);
    cairo_set_line_width (cr, width);
    cairo_stroke(cr);

    cairo_set_font_size (cr, 12.0);
    cairo_set_source_rgb (cr, 1.0, 1.0, 1.0);
    cairo_move_to (cr, 0.0, 25.0);
    cairo_show_text (cr, "Hello, world");

    // Create a rectangle
    cairo_set_source_rgb(cr, 0, 0, 1);
    cairo_rectangle(cr, 0, 50, 500, 100);
    cairo_fill(cr);

    cairo_rectangle(cr, 0, 200, 500, 100);
    cairo_stroke(cr);

    // writing and destroying rendering device
    cairo_destroy (cr);
    cairo_surface_write_to_png (surface, "subroutine.png");
    cairo_surface_destroy (surface);
*/

}

/*----------------------------------------------------------------------------//
* SUBROUTINES
*-----------------------------------------------------------------------------*/

// Function to draw initial layout 
void create_scene(int num_box, int box_width, int box_height){

    // Create initial surface and context
    // Note: The size of the surface is dependent on the number of boxes

    // Note: When considering box position, we assume a maximum width of 3 boxes
    int surface_width, surface_height;
    if (num_box == 1){
        surface_width = box_width;
        surface_height = box_height;
    }
    else if (num_box % 2 == 0){
        surface_width = box_width * 2;
        surface_height = box_height * (num_box / 2);
    }
    else{
        surface_width = box_width * 3;
        surface_height = box_height * ceil(num_box / 3.0);
    }
    cairo_surface_t *surface = 
        cairo_image_surface_create(CAIRO_FORMAT_ARGB32, surface_width, 
                                   surface_height);

    cairo_t *context = cairo_create(surface);

    // Set the border source
    cairo_set_source_rgb(context, 0.0, 0.0, 0.0);
    cairo_set_line_width(context, 5);

    // Now we need to draw the boxes
    if (num_box == 1){
        cairo_rectangle(context, 0, 0, box_width, box_height);
    }
    else if (num_box % 2 == 0){
        for (size_t i = 0; i < 2; ++i){
            for (size_t j = 0; j < (size_t)(num_box / 2); ++j){
                cairo_rectangle(context, i * box_width, j * box_height,
                                box_width, box_height);
            }
        }
    }
    else{
        std::cout << "ceil(num_box/3) = " << ceil(num_box / 3.0) << '\n';
        switch(num_box % 3){
             case 0:
                std::cout << "we are in case 0" << '\n';
                for (size_t i = 0; i < 3; ++i){
                    for (size_t j = 0; j < ceil(num_box / 3.0); ++j){
                        cairo_rectangle(context, i * box_width, j * box_height,
                                        box_width, box_height);
                    }
                }
                break;
             case 2:
                std::cout << "we are in case 2" << '\n';
                for (size_t i = 0; i < 3; ++i){
                    for (size_t j = 0; j < ceil(num_box / 3.0) - 1; ++j){
                        cairo_rectangle(context, i * box_width, j * box_height,
                                        box_width, box_height);
                    }
                }
                for (size_t i = 0; i < 2; ++i){
                    cairo_rectangle(context, 
                                    surface_width / 2 + (i - 1) * box_width, 
                                    (ceil(num_box / 3.0)-1) * box_height, 
                                    box_width, box_height);
                }
                break;
        }
    }

    cairo_stroke(context);

    // writing and destroying rendering device
    cairo_destroy (context);
    cairo_surface_write_to_png (surface, "subroutine.png");
    cairo_surface_destroy (surface);


}

