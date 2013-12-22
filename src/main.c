#include <glib.h>
#include <stdlib.h>
#include <stdio.h>
#include "config.h"

void print_help ()
{
  g_printf ("This is HELP!\n");
  g_printf ("Recommended values:\n");
  g_printf ("\
            | %13s | %5s | %6s | %4s | %2s | %24s |\n\
            | %13s | %5s | %6s | %4s | %2s | %24s |\n\
            | %13s | %5s | %6s | %4s | %2s | %24s |\n\
            | %13s | %5s | %6s | %4s | %2s | %24s |\n\
            | %13s | %5s | %6s | %4s | %2s | %24s |\n\
            | %13s | %5s | %6s | %4s | %2s | %24s |\n\
            | %13s | %5s | %6s | %4s | %2s | %24s |\n\n",
            "ACO algorithm", "alpha", "beta", "rho", "m", "tau(0)",
            "", "", "", "", "", "",
            "AS", "1", "2 to 5", "0.5", "n", "m/(C^nn)",
            "EAS", "1", "2 to 5", "0.5", "n", "(e+m)/(rho*(C^nn))",
            "AS(rank)", "1", "2 to 5", "0.1", "n", "0.5*r*(r-1)/(rho*(C^nn))",
            "MMAS", "1", "2 to 5", "0.02", "n", "1/(rho*(C^nn))",
            "ACS", "-", "2 to 5", "0.1", "10", "1/(rho*(C^nn))");
  g_printf ("\
            Here, n is the number of cities in a TSP instance. All variants of AS also require some additional\n\
            parameters. Good values for these parameters are:\n\n\
            EAS: The parameter e is set to e = n.\n\
            AS(rank): The number of ants that deposit pheromones is w = 6.\n\
            MMAS: The pheromone trail limits are tau(max) = 1/(rho*(C^bs)) and\n\
            tau(min) = tau(max)*(1-(0.05^(1/n)))/((avg-1)*(0.05^(1/n))),\n\
            where avg is the average number of different choices available to an ant at each step while\n\
            constructing a solution (for a justification of these values see Stutzle and Hoos (2000). When applied\n\
            to small TSP instances with up to 200 cities, good results are obtained by using always the iteration-\n\
            best pheromone update rule, while on larger instances it becomes increasingly important to alter-\n\
            nate between the iteration-best and the best-so-far pheromone update rules.\n\
            ACS: In the local pheromone trail update rule: epsilon = 0.1. In the pseudorandom proportional action\n\
            choice rule: q(0) = 0.9.\n\n\
            It should be clear that in individual instances, different settings may result in much better per-\n\
            formance. However, these parameters were found to yield reasonable performance over a signifi-\n\
            cant set of TSP instances.\n");
}


void print_version ()
{
  g_printf ("ant_alg version %s\n", PACKAGE_VERSION);
}


gint main (gint argc, gchar **argv)
{
  if (argc > 0)
    if (g_strcmp0 (argv[1], "help") == 0) {
      print_help ();
      return 0;
    } else if (g_strcmp0 (argv[1], "version") == 0) {
      print_version ();
      return 0;
    }
  guint n = 0; // Count cities
  guint m = 0; // Count ants
  guint i, j;
  guint A, B; // Start and end points
  guint alpha = 1; // relative influence of the pheromone trail
  guint beta = 3; // heuristic information
  gfloat rho = 0.5; // pheromone evaporation rate
  gdouble tau0 = 0.0; // deposit of pheromone
  g_printf ("Input cities count..\n");
  scanf ("%u", &n);
  guint **D = g_new0 (guint *, n + 1);
  gdouble **eta = g_new0 (gdouble *, n + 1);
  gfloat **tau = g_new0 (gfloat *, n + 1);
  for (i = 0; i < n; i++) {
    D[i] = g_new0 (guint, n + 1);
    eta[i] = g_new0 (gdouble, n + 1);
    tau[i] = g_new0 (gfloat, n + 1);
  }
  g_printf ("Input cities destination matrix..\n");
  for (i = 0; i < n; i++)
    for (j = 0; j < n; j++) {
      if (i == j) continue;
      g_printf ("Input D[%u][%u]: ", i, j);
      scanf ("%u", &D[i][j]);
    }
#ifdef ENABLE_DEBUG 
  g_printf ("Distance of matrix:\n");
  for (i = 0; i < n; i++) {
    g_printf ("\n|");
    for (j = 0; j < n; j++) 
      g_printf ("%10u", D[i][j]);
    g_printf ("|");
  }
#endif
  g_printf ("Input start point: ");
  scanf ("%u", &A);
  g_printf ("Input end point: ");
  scanf ("%u", &B);
  g_printf ("Input relative influence of the pheromone trail (default: %u): ", alpha);
  scanf ("%u", &alpha);
  g_printf ("Input heutistic information (default: %u): ", beta);
  scanf ("%u", &beta);
  while (rho < 0 || rho > 1) {
    g_printf ("Input pheromone evaporation rate (min: 0; max: 1; default: %f): ", rho);
    scanf ("%f", &rho);
  }
  g_printf ("Input count of ants: ");
  // temporary hack
  m = n;
  g_printf ("ants: %u\n", m);

  // hack for finding min
  guint min = 4294967295;
  for (j = 0; j < n; j++) {
    if (j == A || D[A][j] == 0) continue;
    if (D[A][j] < min) min = D[A][j];
  }
#ifdef ENABLE_DEBUG
  g_printf ("min = %u", min);
#endif
  tau0 = 1.0 / min;
  for (i = 0; i < n; i++)
    for (j = 0; j < n; j++) {
      if (i == j) continue;
      eta[i][j] = 1.0 / D[i][j];
      tau[i][j] = tau0;
    }
#ifdef ENABLE_DEBUG
  g_printf ("Function heuristic value:\n");
  for (i = 0; i < n; i++) {
    g_printf ("\n|");
    for (j = 0; j < n; j++) 
      g_printf ("%10lf", eta[i][j]);
    g_printf ("|");
  }
#endif

  g_free (D);
  return 0;
}
