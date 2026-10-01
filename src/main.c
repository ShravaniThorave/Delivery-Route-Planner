#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXV 50
#define MAXE 500
#define INF 1000000000

typedef struct edge
{
    int from;
    int to;
    int cost;
} edge;

edge edges[MAXE];

int vertex_count = 0;
int edge_count = 0;

int source = 0;
int destination = -1;

int dist[MAXV];
int parent[MAXV];
int affected[MAXV];

int has_negative_cycle = 0;
int algorithm_run = 0;

long long comparisons = 0;
long long relaxations = 0;
int passes_used = 0;

void add_edge(int u, int v, int w)
{
    edges[edge_count].from = u;
    edges[edge_count].to = v;
    edges[edge_count].cost = w;
    edge_count++;
}

void bellman_ford()
{
    int i, j, pass;
    int updated;

    comparisons = 0;
    relaxations = 0;
    passes_used = 0;
    has_negative_cycle = 0;

    for (i = 0; i < vertex_count; i++)
    {
        dist[i] = INF;
        parent[i] = -1;
        affected[i] = 0;
    }

    dist[source] = 0;

    for (pass = 1; pass <= vertex_count - 1; pass++)
    {
        updated = 0;
        passes_used++;

        for (j = 0; j < edge_count; j++)
        {
            int u = edges[j].from;
            int v = edges[j].to;
            int w = edges[j].cost;

            comparisons++;

            if (dist[u] != INF && dist[u] + w < dist[v])
            {
                dist[v] = dist[u] + w;
                parent[v] = u;
                relaxations++;
                updated = 1;
            }
        }

        if (updated == 0)
            break;
    }

    for (j = 0; j < edge_count; j++)
    {
        int u = edges[j].from;
        int v = edges[j].to;
        int w = edges[j].cost;

        comparisons++;

        if (dist[u] != INF && dist[u] + w < dist[v])
        {
            has_negative_cycle = 1;
            affected[v] = 1;
        }
    }

    if (has_negative_cycle == 1)
    {
        for (i = 0; i < vertex_count; i++)
        {
            for (j = 0; j < edge_count; j++)
            {
                if (affected[edges[j].from] == 1)
                    affected[edges[j].to] = 1;
            }
        }
    }

    algorithm_run = 1;
}

void print_path(int v)
{
    if (parent[v] != -1)
        print_path(parent[v]);

    printf("%d ", v);
}

void show_route(int v)
{
    printf("%d to %d : ", source, v);

    if (affected[v] == 1)
        printf("No finite shortest path (negative cycle)\n");
    else if (dist[v] == INF)
        printf("Unreachable\n");
    else
    {
        print_path(v);
        printf("(Cost = %d)\n", dist[v]);
    }
}

void load_test(int t)
{
    edge_count = 0;
    algorithm_run = 0;
    source = 0;

    if (t == 1)
    {
        vertex_count = 4;
        add_edge(0, 1, 4);
        add_edge(0, 2, 1);
        add_edge(2, 1, 2);
        add_edge(1, 3, 1);
        add_edge(2, 3, 5);
        destination = 3;
    }
    else if (t == 2)
    {
        vertex_count = 5;
        add_edge(0, 1, 6);
        add_edge(0, 2, 7);
        add_edge(1, 2, 8);
        add_edge(1, 3, 5);
        add_edge(1, 4, -4);
        add_edge(2, 3, -3);
        add_edge(2, 4, 9);
        add_edge(3, 1, -2);
        add_edge(4, 3, 7);
        add_edge(4, 0, 2);
        destination = 4;
    }
    else if (t == 3)
    {
        vertex_count = 4;
        add_edge(0, 1, 3);
        add_edge(1, 2, 4);
        add_edge(3, 2, 1);
        destination = 3;
    }
    else if (t == 4)
    {
        vertex_count = 4;
        add_edge(0, 1, 1);
        add_edge(1, 2, -1);
        add_edge(2, 3, -1);
        add_edge(3, 1, -1);
        destination = 3;
    }
    else
    {
        vertex_count = 4;
        add_edge(0, 1, 2);
        add_edge(2, 3, -1);
        add_edge(3, 2, -1);
        destination = -1;
    }
}

int main()
{
    int choice = 0;
    int n;
    int test_choice;

    while (choice != 9)
    {
        printf("\n");
        printf("========================================\n");
        printf("      DELIVERY ROUTE PLANNER\n");
        printf("========================================\n");

        printf("1. Enter graph\n");
        printf("2. Display edges\n");
        printf("3. Choose source and destination\n");
        printf("4. Run Bellman-Ford\n");
        printf("5. Display distance and parent table\n");
        printf("6. Display route\n");
        printf("7. Analyze performance\n");
        printf("8. Load test case\n");
        printf("9. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (choice >= 2 && choice <= 4 && vertex_count == 0)
        {
            printf("\nPlease enter a graph first.\n");
            continue;
        }

        if (choice >= 5 && choice <= 7 && algorithm_run == 0)
        {
            printf("\nPlease run Bellman-Ford first.\n");
            continue;
        }

        if (choice == 1)
        {
            printf("\nEnter the number of vertices: ");
            scanf("%d", &vertex_count);

            printf("Enter the number of edges: ");
            scanf("%d", &n);

            if (vertex_count <= 0 || vertex_count > MAXV || n < 0 || n > MAXE)
            {
                printf("Invalid input.\n");
                printf("Maximum %d vertices and %d edges allowed.\n", MAXV, MAXE);
                vertex_count = 0;
                continue;
            }

            edge_count = 0;
            algorithm_run = 0;
            source = 0;
            destination = -1;

            printf("\nVertices are numbered from 0 to %d\n", vertex_count - 1);

            for (int i = 0; i < n; i++)
            {
                int u, v, w;

                printf("\nEnter edge %d (from to cost): ", i + 1);
                scanf("%d %d %d", &u, &v, &w);

                if (u < 0 || u >= vertex_count || v < 0 || v >= vertex_count)
                {
                    printf("Invalid vertex. Enter this edge again.\n");
                    i--;
                    continue;
                }

                add_edge(u, v, w);
            }

            printf("\nGraph entered successfully.\n");
            printf("Default source is 0 and all destinations are shown.\n");
        }

        else if (choice == 2)
        {
            printf("\n");
            printf("========================================\n");
            printf("               EDGE LIST\n");
            printf("========================================\n");

            printf("Vertices : %d\n", vertex_count);
            printf("Edges    : %d\n", edge_count);
            printf("----------------------------------------\n");
            printf("From\tTo\tCost\n");
            printf("----------------------------------------\n");

            for (int i = 0; i < edge_count; i++)
            {
                printf("%d\t%d\t%d\n",
                       edges[i].from,
                       edges[i].to,
                       edges[i].cost);
            }
        }

        else if (choice == 3)
        {
            printf("\nEnter the source vertex: ");
            scanf("%d", &source);

            if (source < 0 || source >= vertex_count)
            {
                printf("Invalid source.\n");
                source = 0;
                continue;
            }

            printf("Enter the destination vertex (-1 for all): ");
            scanf("%d", &destination);

            if (destination < -1 || destination >= vertex_count)
            {
                printf("Invalid destination.\n");
                destination = -1;
            }
            else
            {
                printf("Source and destination selected successfully.\n");
            }

            algorithm_run = 0;
        }

        else if (choice == 4)
        {
            printf("\n");
            printf("========================================\n");
            printf("          STARTING BELLMAN-FORD\n");
            printf("========================================\n");

            printf("Source      : %d\n", source);

            if (destination == -1)
                printf("Destination : All vertices\n");
            else
                printf("Destination : %d\n", destination);

            bellman_ford();

            printf("\nBellman-Ford completed.\n");

            if (has_negative_cycle == 1)
                printf("Negative cycle detected!\n");
            else
                printf("No negative cycle found.\n");
        }

        else if (choice == 5)
        {
            printf("\n");
            printf("========================================\n");
            printf("       DISTANCE AND PARENT TABLE\n");
            printf("========================================\n");

            printf("Vertex\tDistance\tParent\n");
            printf("----------------------------------------\n");

            for (int i = 0; i < vertex_count; i++)
            {
                printf("%d\t", i);

                if (affected[i] == 1)
                    printf("-INF\t\t");
                else if (dist[i] == INF)
                    printf("INF\t\t");
                else
                    printf("%d\t\t", dist[i]);

                if (parent[i] == -1)
                    printf("-\n");
                else
                    printf("%d\n", parent[i]);
            }

            if (has_negative_cycle == 1)
            {
                printf("----------------------------------------\n");
                printf("Warning: Negative cycle reachable from source.\n");
                printf("Vertices marked -INF have no finite shortest path.\n");
            }
        }

        else if (choice == 6)
        {
            printf("\n");
            printf("========================================\n");
            printf("             SHORTEST ROUTES\n");
            printf("========================================\n");

            if (destination == -1)
            {
                for (int i = 0; i < vertex_count; i++)
                    show_route(i);
            }
            else
            {
                show_route(destination);
            }
        }

        else if (choice == 7)
        {
            printf("\n");
            printf("========================================\n");
            printf("          PERFORMANCE ANALYSIS\n");
            printf("========================================\n");

            printf("Number of Vertices      : %d\n", vertex_count);
            printf("Number of Edges         : %d\n", edge_count);
            printf("Source Vertex           : %d\n", source);

            printf("----------------------------------------\n");

            printf("Passes Used             : %d\n", passes_used);
            printf("Maximum Passes (V - 1)  : %d\n", vertex_count - 1);
            printf("Edge Comparisons        : %lld\n", comparisons);
            printf("Successful Relaxations  : %lld\n", relaxations);

            printf("----------------------------------------\n");

            if (passes_used < vertex_count - 1)
                printf("Stopped early because no update occurred.\n");
            else
                printf("All V - 1 passes were required.\n");

            if (has_negative_cycle == 1)
                printf("Result: Negative cycle detected.\n");
            else
                printf("Result: Shortest paths are valid.\n");

            printf("========================================\n");
        }

        else if (choice == 8)
        {
            printf("\n");
            printf("========================================\n");
            printf("            LOAD TEST CASE\n");
            printf("========================================\n");

            printf("1. Positive edges only\n");
            printf("2. Negative edges without cycle\n");
            printf("3. Unreachable vertex\n");
            printf("4. Negative cycle\n");
            printf("5. Negative cycle not reachable\n");

            printf("Enter your choice: ");
            scanf("%d", &test_choice);

            if (test_choice < 1 || test_choice > 5)
            {
                printf("Invalid test case choice.\n");
            }
            else
            {
                load_test(test_choice);

                printf("\nTest case loaded successfully!\n");
                printf("Use option 2 to view edges and option 4 to run.\n");
            }
        }

        else if (choice != 9)
        {
            printf("\nInvalid choice. Please try again.\n");
        }
    }

    printf("\nProgram terminated successfully.\n");

    return 0;
}
