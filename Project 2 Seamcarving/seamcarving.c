# include "seamcarving.h"
# include "c_img.h"
# include <stdio.h>
# include <stdlib.h>
# include <math.h>


double min_of_two(double x, double y);

double min_of_three(double x, double y, double z);

double get_delta_x_squared(int y, int x1, int x2, struct rgb_img *im);

double get_delta_y_squared(int x, int y1, int y2, struct rgb_img *im);


double min_of_two(double x, double y) {
    // returns the smallest of two input doubles
    return (x < y) ? x : y;
}

double min_of_three(double x, double y, double z) {
    // returns the smallest of three input doubles
    double temp = (x < y) ? x : y;
    return (temp < z) ? temp : z;
}


double get_delta_x_squared(int y, int x1, int x2, struct rgb_img *im) {
    return pow(get_pixel(im, y, x1, 0) - get_pixel(im, y, x2, 0), 2)
           + pow(get_pixel(im, y, x1, 1) - get_pixel(im, y, x2, 1), 2)
           + pow(get_pixel(im, y, x1, 2) - get_pixel(im, y, x2, 2), 2);
}


double get_delta_y_squared(int x, int y1, int y2, struct rgb_img *im) {
    return pow(get_pixel(im, y1, x, 0) - get_pixel(im, y2, x, 0), 2)
           + pow(get_pixel(im, y1, x, 1) - get_pixel(im, y2, x, 1), 2)
           + pow(get_pixel(im, y1, x, 2) - get_pixel(im, y2, x, 2), 2);
}


void calc_energy(struct rgb_img *im, struct rgb_img **grad) {

    // allocating memory for grad
    create_img(grad, im->height, im->width);

    // set each pixel on the raster of grad to the dual-gradient energy

    for (int y = 0; y < (im->height); y++) { // for each y-coordinate of the picture

        for (int x = 0; x < (im->width); x++) { // for each x-coordinate of the picture

            double delta_x_squared;
            double delta_y_squared;

            // if the pixel is on the left edge
            if (x == 0) {
                delta_x_squared = get_delta_x_squared(y, (int) im->width - 1, 1, im);
            }
                // if the pixel is on the right edge
            else if (x == im->width - 1) {
                delta_x_squared = get_delta_x_squared(y, (int) im->width - 2, 0, im);
            }
                // if the pixel is neither on the right nor on the left edge
            else {
                delta_x_squared = get_delta_x_squared(y, x - 1, x + 1, im);
            }

            // if the pixel is on the top edge
            if (y == 0) {
                delta_y_squared = get_delta_y_squared(x, (int) im->height - 1, 1, im);
            }
                // if the pixel is on the bottom edge
            else if (y == im->height - 1) {
                delta_y_squared = get_delta_y_squared(x, (int) im->height - 2, 0, im);
            }
                // if the pixel is neither on the top nor on the bottom edge
            else {
                delta_y_squared = get_delta_y_squared(x, y - 1, y + 1, im);
            }

            // set the pixels of grad to the energy
            int energy = (int) ((sqrt(delta_x_squared + delta_y_squared)) / 10);
            set_pixel(*grad, y, x, energy, energy, energy);
        }
    }
}


void dynamic_seam(struct rgb_img *grad, double **best_arr) {
    // given the gradient array and a pointer to an array of doubles, makes best_arr point to the array of best seams
    // output best_arr such that all the pixels from one height are together, then the next height, etc.
    *best_arr = (double *) malloc(sizeof(double) * grad->width * grad->height);

    int x;
    int y;

    // set the first rows' costs to the first rows' energies
    for (x = 0; x < grad->width; x++) {
        (*best_arr)[x] = get_pixel(grad, 0, x, 0);
    }

    if (grad->width == 1) { // if the image has width 1
        // set the minimum costs with dynamic programming by moving down best_arr
        for (y = 1; y < grad->height; y++) {
            (*best_arr)[y] = get_pixel(grad, y, 0, 0) + (*best_arr)[y - 1];
        }
        return;
    }

    for (y = 1; y < (grad->height); y++) {
        for (x = 0; x < (grad->width); x++) {
            if (x == 0) { // if the pixel is on the left edge
                (*best_arr)[y * (grad->width) + x] = get_pixel(grad, y, x, 0)
                                                     + min_of_two((*best_arr)[(y - 1) * (grad->width) + x],
                                                                  (*best_arr)[(y - 1) * (grad->width) + x + 1]);
            } else if (x == (grad->width - 1)) { // if the pixel is on the right edge
                (*best_arr)[y * (grad->width) + x] = get_pixel(grad, y, x, 0) +
                                                     min_of_two((*best_arr)[(y - 1) * (grad->width) + x],
                                                                (*best_arr)[(y - 1) * (grad->width) + x - 1]);
            } else {    // covers case of width 2
                (*best_arr)[y * (grad->width) + x] = get_pixel(grad, y, x, 0) +
                                                     min_of_three((*best_arr)[(y - 1) * (grad->width) + x],
                                                                  (*best_arr)[(y - 1) * (grad->width) + x - 1],
                                                                  (*best_arr)[(y - 1) * (grad->width) + x + 1]);
            }
        }
    }
}

void recover_path(double *best, int height, int width, int **path) {

    if (!height || !width) { // if the image does not have a height or width
        return;
    }
    *path = (int *) malloc(sizeof(int) * height); // allocate memory for the path

    int y = height - 1;
    int x = 0;

    // initialize the current minimum and minimum index
    int cur_min_x_ind = 0;
    double cur_min = best[(y) * width + cur_min_x_ind];

    // set the ending of the path
    for (x = 0; x < width; x++) {
        if (best[y * width + x] < cur_min) {
            cur_min_x_ind = x;
            cur_min = best[y * width + x];
        }
    }
    (*path)[y] = cur_min_x_ind;
    x = (*path)[y];

    for (y = height - 2; y >= 0; y--) {
        if (x == 0) { // x is on the left edge, comparing the on on top and the one on top and to the right
            x = (best[y * width] <= best[y * width + 1]) ? 0 : 1;
        } else if (x == width - 1) {
            // x is on the right edge, comparing the on on top and the one on top and to the left
            x = (best[y * width + width - 2] <= best[y * width + width - 1]) ? width - 2 : width - 1;
        } else { // x is in the middle, comparing the 3 on top of the previous one
            int temp_ind = (best[y * width + x - 1] <= best[y * width + x]) ? x - 1 : x;
            x = (best[y * width + temp_ind] <= best[y * width + x + 1]) ? temp_ind : x + 1;
        }
        (*path)[y] = x;
    }
}


void remove_seam(struct rgb_img *src, struct rgb_img **dest, int *path) {
    create_img(dest, src->height, src->width - 1);
    int found;
    for (int y = 0; y < src->height; y++) {
        found = 0;
        for (int x = 0; x < src->width; x++) {
            if (path[y] == x) {
                found = 1;
            } else if (found) {
                set_pixel(*dest, y, x - 1,
                          get_pixel(src, y, x, 0), get_pixel(src, y, x, 1), get_pixel(src, y, x, 2));
            } else {
                set_pixel(*dest, y, x,
                          get_pixel(src, y, x, 0), get_pixel(src, y, x, 1), get_pixel(src, y, x, 2));
            }
        }
    }
}

