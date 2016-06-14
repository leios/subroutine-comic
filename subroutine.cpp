/*-------------subroutine.cpp-------------------------------------------------//
*
* Purpose: We are creating a webcomic with code using cairo.
*
*   Notes: This is where we keep main()
*          Prime numbers of slides have not been implemented
*-----------------------------------------------------------------------------*/

#include <cairo.h>
#include <iostream>
#include <math.h>
#include <string>

// defining a global variable for the number of panels
#define num_panel 5

// Class to hold all panel data
class panel{
    public:
        int box_height, box_width, lw;
        cairo_surface_t *panel_surface[num_panel];
        cairo_t *panel_ctx[num_panel];
        cairo_surface_t *bg_surface;
        cairo_t *bg_ctx;
        double gap;
        double xpos[num_panel], ypos[num_panel];
};

// Function to draw initial layout
void create_scene(panel &comic);
void write_image(panel comic, std::string pngname);
void destroy_all(panel &comic);

// Function to draw circle -- FUTURE
// void draw_circle(panel &comic, double radius, double x, double y);

/*----------------------------------------------------------------------------//
* MAIN
*-----------------------------------------------------------------------------*/
int main (){

    panel comic;
    comic.box_height = 2000;
    comic.box_width  = 2000;
    comic.gap        = 10.0;
    comic.lw         = 5;

    create_scene(comic);

    for (size_t i = 0; i < num_panel; ++i){
        cairo_move_to (comic.panel_ctx[i], 1000, 1000);
        cairo_curve_to (comic.panel_ctx[i], 150, 200, 200, 150, 
                            500, 500);
        cairo_stroke(comic.panel_ctx[i]);
    }

    write_image(comic, "subroutine.png");

    destroy_all(comic);

    // This is for testing purposes
    /*
    // Creating initial surface to draw on.
    cairo_surface_t *surface =
        cairo_image_surface_create (CAIRO_FORMAT_ARGB32, 1000, 400);
    cairo_t *cr =
        cairo_create (surface);

    cairo_surface_t *surface_2 = 
        cairo_image_surface_create (CAIRO_FORMAT_ARGB32, 550, 150);

    cairo_t *cr_2 = cairo_create(surface_2);

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

    cairo_rectangle(cr_2, 5, 5, 50, 10);
    cairo_stroke (cr_2);
    cairo_set_font_size (cr_2, 12.0);
    cairo_set_source_rgb (cr_2, 1.0, 0, 1.0);
    cairo_move_to (cr_2, 0.0, 25.0);
    cairo_show_text (cr_2, "Hello, world");

    cairo_stroke(cr);

    cairo_set_source_surface (cr, surface_2, 500, 200);

    cairo_paint(cr);

    // writing and destroying rendering device
    cairo_destroy (cr);
    cairo_destroy (cr_2);
    cairo_surface_write_to_png (surface, "subroutine.png");
    cairo_surface_write_to_png (surface_2, "sub_2.png");
    cairo_surface_destroy (surface);
    cairo_surface_destroy (surface_2);
    */

}

/*----------------------------------------------------------------------------//
* SUBROUTINES
*-----------------------------------------------------------------------------*/

// Function to draw initial layout 
void create_scene(panel &comic){

    // Create bg surface and context
    // Note: The size of the surface is dependent on the number of boxes

    // Note: When considering box position, we assume a maximum width of 3 boxes
    int surface_width, surface_height;
    if (num_panel == 1){
        surface_width = comic.box_width + comic.gap;
        surface_height = comic.box_height + comic.gap;
    }
    else if (num_panel % 2 == 0){
        surface_width = (comic.box_width + comic.gap / 2) * 2 + comic.gap / 2;
        surface_height = (comic.box_height + comic.gap / 2) * (num_panel / 2)
                         + comic.gap / 2;
    }
    else{
        surface_width = (comic.box_width + comic.gap / 2) * 3 + comic.gap / 2;
        surface_height = (comic.box_height + comic.gap / 2)
                         * ceil(num_panel / 3.0) + comic.gap / 2;
    }

    // creating background for writing to
    comic.bg_surface = 
        cairo_image_surface_create(CAIRO_FORMAT_ARGB32, surface_width, 
                                   surface_height);

    comic.bg_ctx = cairo_create(comic.bg_surface);

    // Create the panel surfaces and contexts
    for (int i = 0; i < num_panel; ++i){
        comic.panel_surface[i] = 
            cairo_image_surface_create(CAIRO_FORMAT_ARGB32, comic.box_width,
                                       comic.box_height);
        comic.panel_ctx[i] = cairo_create(comic.panel_surface[i]);

        // Setting border and source
        cairo_set_source_rgb(comic.panel_ctx[i], 0.0, 0.0, 0.0);
        cairo_set_line_width(comic.panel_ctx[i], comic.lw);
    }

    // Set the border and source
    cairo_set_source_rgb(comic.bg_ctx, 0.0, 0.0, 0.0);
    cairo_set_line_width(comic.bg_ctx, comic.lw * 2);

    // Now we need to draw the boxes

    // curr is the current box we are drawing
    int curr = 0;
    double xpos, ypos;
    
    // For 1 panel
    if (num_panel == 1){
        cairo_rectangle(comic.panel_ctx[0], 0, 0, 
                        comic.box_width, comic.box_height);

        // painting bg box to surface
        cairo_stroke(comic.panel_ctx[0]);
        comic.xpos[0] = comic.gap / 2;
        comic.ypos[0] = comic.gap / 2;
    }

    // For even numbers of panlse
    else if (num_panel % 2 == 0){
        curr = 0;
        for (size_t i = 0; i < 2; ++i){
            for (size_t j = 0; j < (size_t)(num_panel / 2); ++j){
                xpos = i * (comic.box_width + comic.gap / 2) + (comic.gap / 2);
                ypos = j * (comic.box_height + comic.gap / 2) + (comic.gap / 2);

                cairo_rectangle(comic.panel_ctx[curr], 0, 0, 
                                comic.box_width, comic.box_height);

                // painting bg box to surface
                cairo_stroke(comic.panel_ctx[curr]);
                comic.xpos[curr] = xpos;
                comic.ypos[curr] = ypos;
                curr += 1;
            }
        }

    }

    // For everything else, (except primes)
    else{
        curr = 0;

        // Multiples of 3 or not
        switch(num_panel % 3){

            // Multiple of 3
            case 0:
                std::cout << "we are in case 0" << '\n';
                for (size_t i = 0; i < 3; ++i){
                    for (size_t j = 0; j < ceil(num_panel / 3.0); ++j){
                        xpos = i * (comic.box_width + comic.gap / 2)
                               + (comic.gap / 2);
                        ypos = j * (comic.box_height + comic.gap / 2) 
                               + (comic.gap / 2);

                        cairo_rectangle(comic.panel_ctx[curr], 0, 0, 
                                        comic.box_width, comic.box_height);
                        // painting bg box to surface
                        cairo_stroke(comic.panel_ctx[curr]);
                        comic.xpos[curr] = xpos;
                        comic.ypos[curr] = ypos;
                        curr += 1;
                    }
                }
                break;

            // Not multiple of 3
            case 2:
                std::cout << "we are in case 2" << '\n';
                // creating initial rows of 3
                for (size_t i = 0; i < 3; ++i){
                    for (size_t j = 0; j < ceil(num_panel / 3.0) - 1; ++j){
                        xpos = i * (comic.box_width + comic.gap / 2)
                               + (comic.gap / 2);
                        ypos = j * (comic.box_height + comic.gap / 2) 
                               + (comic.gap / 2);
                        cairo_rectangle(comic.panel_ctx[curr], 0, 0, 
                                        comic.box_width, comic.box_height);

                        // painting bg box to surface
                        cairo_stroke(comic.panel_ctx[curr]);
                        comic.xpos[curr] = xpos;
                        comic.ypos[curr] = ypos;
                        curr += 1;
                    }
                }
                // creating final row of 2
                for (int i = 0; i < 2; ++i){
                    // The x and y positions here are defined around the 
                    // middle of the surface we are drawing to
                    xpos = surface_width / 2 + (i-1) * (comic.box_width);
                    if ((i-1) < 0){
                        xpos -= comic.gap / 4;
                    }
                    else{
                        xpos += comic.gap / 4;
                    }
                    ypos = (ceil(num_panel / 3.0) - 1) * ((comic.box_height 
                           + comic.gap / 2) + comic.gap / 2);
                    cairo_rectangle(comic.panel_ctx[curr], 0, 0,
                                    comic.box_width, comic.box_height);
                    // painting bg box to surface
                    cairo_stroke(comic.panel_ctx[curr]);
                    comic.xpos[curr] = xpos;
                    comic.ypos[curr] = ypos;
                    curr += 1;
                }
                break;

            case 1:
                std::cout << "primes have not been implemented, sorry!" << '\n';
        }
    }

    // writing and destroying rendering device
    // write_image(comic, "subroutine.png");

}

// Function to write to png
void write_image(panel comic, std::string pngname){
    for (size_t i = 0; i < num_panel; ++i){
        cairo_set_source_surface(comic.bg_ctx, comic.panel_surface[i],
                                 comic.xpos[i], comic.ypos[i]);
        cairo_paint(comic.bg_ctx);
    }
    cairo_surface_write_to_png (comic.bg_surface, pngname.c_str());
}

// Function to destroy all contexts and surfaces
void destroy_all(panel &comic){
    for (size_t i = 0; i < num_panel; ++i){
        cairo_destroy(comic.panel_ctx[i]);
        cairo_surface_destroy (comic.panel_surface[i]);
    }
    cairo_destroy (comic.bg_ctx);
    cairo_surface_destroy (comic.bg_surface);
}
