#include "version.h"
#include <glib.h>
#include <stdlib.h>
#include <stdio.h>

gint main ()
{
  guint N = 0; // Count cities
  guint i, j;
  guint A, B; // Start and end points
  g_printf ("Input cities count..\n");
  scanf ("%u", &N);
  guint **D = g_new0 (guint *, N + 1);
  for (i = 0; i < N; i++)
    D[i] = g_new (guint, N + 1);
  g_printf ("Input cities destination matrix..\n");
  for (i = 0; i < N; i++)
    for (j = 0; j < N; j++) {
      if (i == j) continue;
      g_printf ("Input D[%u][%u]: ", i, j);
      scanf ("%u", &D[i][j]);
    }
  g_printf ("Input start point: ");
  scanf ("%u", &A);
  g_printf ("Input end point: ");
  scanf ("%u", &B);
  g_free (D);
  return 0;
}
