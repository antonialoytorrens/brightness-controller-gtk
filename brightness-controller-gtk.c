#include <gtk/gtk.h>


/* This is the callback function. 
 * It is a handler function which reacts to the signal. 
 * In this case, it will notify the user the value of their scale as a label.
 */
static void
hscale_moved (GtkRange *range,
              gpointer  user_data)
{
   GtkWidget *label = user_data;

   /* Get the value of the range, and convert it into a string which will be
    * used as a new label for the horizontal scale.
    * %.0f - stands for a double that will have 0 decimal places.
    */
   gdouble pos = gtk_range_get_value (range);
   /* Note: Using g_strdup_printf returns a string that must be freed. 
    * (In which is done below)
    */
   gchar *str = g_strdup_printf ("Your brightness is %.0f", pos);
   gchar *command = g_strdup_printf ("/usr/bin/xbacklight -set %.0f", pos);
   gtk_label_set_text (GTK_LABEL (label), str);
   system(g_strdup_printf("/usr/bin/xbacklight -set %.0f", pos));

   g_free(str);
}


static gchar
get_brightness() {
    /* Display current brightness */
  FILE *current;
  gchar buf[BUFSIZ];

    if ((current = popen("/usr/bin/xbacklight -get", "r")) == NULL) {
        printf("Error opening pipe!\n");
    }

    while (fgets(buf, BUFSIZ, current) != NULL) {
        return buf[0];
    }

    if(pclose(current))  {
        printf("Command not found or exited with error status\n");
    }
}


static void
activate (GtkApplication *app,
          gpointer        user_data)
{
  /* Declare variables */
  GtkWidget *window;
  GtkWidget *h_scale;
  GtkWidget *hlabel;
  GtkWidget *grid;
  gshort brightness;

  /* The Adjustment object represents a value 
   * which has an associated lower and upper bound.
   */
  GtkAdjustment *hadjustment;

  /* Create a window with a title and a default size */
  window = gtk_application_window_new (app);
  gtk_window_set_title (GTK_WINDOW (window), "Brightness Controller");
  gtk_window_set_default_size (GTK_WINDOW (window), 400, 75);
  gtk_container_set_border_width (GTK_CONTAINER (window), 5);
  gtk_window_set_icon_from_file (GTK_WINDOW (window), "/usr/share/icons/sun.png", NULL);
  
  /* Display current brightness */
  brightness = get_brightness();
   
  /* gtk_adjustment_new takes six parameters, three of which 
   * may be difficult to understand:
   * step increment- move the handle with the arrow keys on your keyboard to see.
   * page increment - move the handle by clicking away from it 
   * on the scale to see.
   * page size - not used here.
   */
  hadjustment = gtk_adjustment_new (brightness, 1, 100, 5, 10, 0);

  /* Two labels to be shown in the window */
  hlabel = gtk_label_new ("Move the cursor to modify the brightness");

  /* Create the Horizontal scale, making sure the 
   * digits used have no decimals.
   */
  h_scale = gtk_scale_new (GTK_ORIENTATION_HORIZONTAL, hadjustment);
  gtk_scale_set_digits (GTK_SCALE (h_scale), 0); 

  /* Allow it to expand horizontally (if there's space), and 
   * set the vertical alignment
   */
  gtk_widget_set_hexpand (h_scale, TRUE);
  gtk_widget_set_valign (h_scale, GTK_ALIGN_START);
  
  /* Connecting the "value-changed" signal for the horizontal scale 
   * to the appropriate callback function. 
   * take note that GtkRange is part of GtkScale's Object Hierarchy.
   */
  g_signal_connect (h_scale, 
                    "value-changed", 
                    G_CALLBACK (hscale_moved), 
                    hlabel);

  /* Create a grid and arrange everything accordingly */
  grid = gtk_grid_new ();
  gtk_grid_set_column_spacing (GTK_GRID (grid), 10);
  gtk_grid_set_column_homogeneous (GTK_GRID (grid), TRUE);
  gtk_grid_attach (GTK_GRID (grid), h_scale, 0, 0, 1, 1);
  gtk_grid_attach (GTK_GRID (grid), hlabel, 0, 1, 1, 1);
  

  gtk_container_add (GTK_CONTAINER (window), grid);

  gtk_widget_show_all (window);
}


int
main (int argc, char **argv)
{
  GtkApplication *app;
  int status;

  app = gtk_application_new ("org.gtk.example", G_APPLICATION_FLAGS_NONE);
  g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
  status = g_application_run (G_APPLICATION (app), argc, argv);
  g_object_unref (app);

  return status;
}
