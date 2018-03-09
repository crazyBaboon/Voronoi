 /*
 * Copyright (C) 2018 Nuno Ferreira
 *
 * veronoi.c is  free software; you can redistribute  it and/or modify
 * it under the  terms of the GNU General  Public License as published
 * by the Free  Software Foundation; either version 3  of the License,
 * or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT  ANY  WARRANTY;  without   even  the  implied  warranty  of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.   See the GNU
 * General Public License for more details.
 *
 * gcc veronoi.c -o veronoi `pkg-config --cflags --libs gtk+-3.0` && ./veronoi 
 * 
 * */


#include <time.h>
#include <cairo.h>
#include <gtk/gtk.h>
#include <math.h>
#include <stdlib.h>

#define number_nodes 20

static void do_drawing(cairo_t *, GtkWidget *widget);

struct Node{
  int index;
  int x;
  int y;
  float color[3];
};


struct Node node[number_nodes];

static gboolean on_draw_event(GtkWidget *widget, cairo_t *cr, 
    gpointer user_data)
{        
  do_drawing(cr, widget);
  return FALSE;
}

static void do_drawing(cairo_t *cr, GtkWidget *widget)
{         
  GtkWidget *win = gtk_widget_get_toplevel(widget);
  gint width, height;
  gtk_window_get_size(GTK_WINDOW(win), &width, &height);

  //~ /* Draw the edges of the graph */

  //~ cairo_set_source_rgb(cr, 1.0, 1.0, 1.0);
  //~ cairo_set_line_width(cr, 0.1);

  //~ for (int i = 0; i < node.number_nodes - 1; i++ ) 
  //~ {
  //~ cairo_move_to(cr, node.x[i], node.y[i]);
  //~ cairo_line_to(cr, node.x[i+1], node.y[i+1]);
  //~ }
  //~ cairo_stroke(cr); 
  
  //~ for (int i = 0; i < number_nodes; i++ ) 
  //~ {
    //~ for (int j = 0; j < number_nodes; j++ ) 
    //~ {
      //~ cairo_move_to(cr, node[i].x, node[i].y);
      //~ cairo_line_to(cr, node[j].x, node[j].y);
    //~ }
  //~ }
  //~ cairo_stroke(cr); 

  /* Draw the veronoi regions */
  int distance, distance_min, dummy_color_index;
  
  for (int i = 10; i < 800 ; i = i + 10 ) 
  {    
	for (int j = 10; j < 800 ; j = j + 10 )
	{        
	  int distance_min = 100000000;

      for (int k = 0; k < number_nodes ; k++ ) 
      {
        /* Calculate distances between the pixels and the Veronoi center nodes */	
       
        distance = (i - node[k].x) * (i - node[k].x) + (j - node[k].y) * (j - node[k].y); 
		  
		if (distance < distance_min)
		{
          distance_min = distance;
          dummy_color_index = k;         
		}	
	  }
  	 
	  cairo_set_source_rgb(cr, node[dummy_color_index].color[0], node[dummy_color_index].color[1], node[dummy_color_index].color[2]);
      cairo_arc(cr, i, j, 7, 0, 2*M_PI);
      cairo_fill(cr);
    }
  }
  cairo_stroke(cr); 
  


  /* Draw the vertices of the graph */

  cairo_set_source_rgb(cr, 0.0, 0.0, 0.0);	
  
  for (int i = 0; i < number_nodes ; i++ ) 
  {    
  cairo_arc(cr, node[i].x, node[i].y, 6, 0, 2*M_PI);
  cairo_fill(cr);
  }
  cairo_stroke(cr); 
  
}


int main(int argc, char *argv[])
{
  GtkWidget *window;
  GtkWidget *darea;

  gtk_init(&argc, &argv);

  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

  darea = gtk_drawing_area_new();
  gtk_container_add(GTK_CONTAINER (window), darea);

  g_signal_connect(G_OBJECT(darea), "draw", 
      G_CALLBACK(on_draw_event), NULL);
  g_signal_connect(G_OBJECT(window), "destroy",
      G_CALLBACK(gtk_main_quit), NULL);

  gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
  gtk_window_set_default_size(GTK_WINDOW(window), 800, 800); 
  gtk_window_set_title(GTK_WINDOW(window), "Simple graph");
  
  gtk_widget_show_all(window);
  
  
  srand(time(NULL));   /* seed for random number generator */

  
  for (int i = 0; i < number_nodes; i++ ) 
  {
    node[i].x = 100 + rand() % 650;
    node[i].y = 100 + rand() % 650;
    node[i].color[0] = (float)rand()/(float)(RAND_MAX);
    node[i].color[1] = (float)rand()/(float)(RAND_MAX);
    node[i].color[2] = (float)rand()/(float)(RAND_MAX);
  }
  
  gtk_main();

  return 0;
}
