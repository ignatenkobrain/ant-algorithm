#include "version.h"
#include <glib.h>
#include <stdlib.h>
#include <stdio.h>

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
            Here, n is the number of cities in a TSP instance. All variants of AS also require some additional\n\\
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
  g_printf ("ant_alg version %s\n", VERSION);
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
  guint N = 0; // Count cities
  guint i, j;
  guint A, B; // Start and end points
  guint alpha = 1; // relative influence of the pheromone trail
  guint beta = 3; // heuristic information
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
  g_printf ("Input relative influence of the pheromone trail (default: %u): ", alpha);
  scanf ("%u", &alpha);
  g_printf ("Input heutistic information (default: %u): ", beta);
  scanf ("%u", &beta);
  g_free (D);
  return 0;
}
