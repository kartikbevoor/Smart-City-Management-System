#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//---Tunnel
struct Aareas_tunnel  // Structure to store areas, number and rainfall recorded
{
    int priority_tunnel;
    char areas_name_tunnel[150];
    int rainfall;
};
typedef struct Aareas_tunnel T;
T areas_tunnel[300];

int global_count_tunnel = 0;
int v_tunnel = 6;

void load_from_file_tunnel() // Function to load data from file to structure
{
    FILE *fp;
    fp = fopen("Areas2.txt", "r");

    if (fp == NULL)
    {
        printf("File Not found\n");
        return;
    }

    while (!feof(fp))
    {
        fscanf(fp, "%d\t%d\t%[^\n]s", &areas_tunnel[global_count_tunnel].priority_tunnel,&areas_tunnel[global_count_tunnel].rainfall,areas_tunnel[global_count_tunnel].areas_name_tunnel);
        global_count_tunnel++;
    }

    fclose(fp);
}

void copy(int v_tunnel, int A[])  // Function to copy rainfall recorded into an array
{
    for (int i = 0; i < v_tunnel; i++)
    {
        A[i] = areas_tunnel[i].rainfall;
    }
}

void merge(int B[], int p, int C[], int q, int A[], int v_tunnel)  // Function to merge sorted arrays
{
    int i = 0, j = 0, k = 0;

    while (i < p && j < q)
    {
        if (B[i] <= C[j])
        {
            A[k] = B[i];
            i++;
        }
        else
        {
            A[k] = C[j];
            j++;
        }
        k++;
    }

    if (i == p)
    {
        while (j < q)
        {
            A[k] = C[j];
            j++;
            k++;
        }
    }
    else
    {
        while (i < p)
        {
            A[k] = B[i];
            i++;
            k++;
        }
    }

}

void mergesort(int A[], int n)  // Function to sort given array
{
    if (n > 1)
    {
        int mid = n / 2;
        int B[mid];
        int C[n - mid];
        for (int i = 0; i < mid; i++)
        {
            B[i] = A[i];
        }

        for (int i = mid; i < n; i++)
        {
            C[i - mid] = A[i];
        }
        mergesort(B, mid);
        mergesort(C, n - mid);
        merge(B, mid, C, n - mid, A, n);
    }
}

int find_max(int A[])   // Function to find maximum rainfall recorded
{
    int i,max=0;
    for(i=0; i<v_tunnel; i++)
    {
        if(max < A[i])
        {
            max=A[i];
        }
    }
    printf("Highest Rainfall recorded is %d\n",max);
    return max;
}

int find_source_tunnel(int max)  // Function find priority number of source
{
    int i,y=0;
    for(i=0; i<v_tunnel; i++)
    {
        if(max==areas_tunnel[i].rainfall)
        {
            y=areas_tunnel[i].priority_tunnel;
        }
    }
    return y;
}

void dfs(int m[6][6], int visited[6], int src_tunnel)  // Function to find depth for search
{
    visited[src_tunnel] = 1;
    for (int i = 0; i < v_tunnel; i++)
    {
        if (m[src_tunnel][i] == 1 && visited[i] == 0)
        {
            for(int k=0; k<v_tunnel; k++)
            {
                if(i==areas_tunnel[k].priority_tunnel)
                {
                    printf("\n%s",areas_tunnel[k].areas_name_tunnel);
                }
            }
            dfs(m, visited, i);
        }
    }
}

void bfs(int m[6][6], int src_tunnel)   // Function to find breadth for search
{
    int visited[6] = {0};

    int queue[10], i, u;
    int front = 0, rear = 0;

    queue[rear] = src_tunnel;
    visited[src_tunnel] = 1;

    while (front <= rear)
    {
        u = queue[front];
        for(int k=0; k<v_tunnel; k++)
        {
            if(u==areas_tunnel[k].priority_tunnel)
            {
                printf("\n%s",areas_tunnel[k].areas_name_tunnel);
            }
        }
        front++;

        for (i = 0; i < v_tunnel; i++)
        {
            if (m[u][i] == 1 && visited[i] == 0)
            {
                visited[i] = 1;
                rear++;
                queue[rear] = i;
            }
        }
    }
    printf("\n");
}
//------------
//---Project--
#define M 100
int v_areas=6;

struct Aareas // Structure to store areas and a number assigned to it
{
    int priority_areas;
    char areas_name[150];
};

typedef struct Aareas A;
A areas[300];

int global_count_areas = 0;

void load_from_file_areas() // Function to load data from file to structure
{
    FILE *fp;
    fp = fopen("Areas.txt", "r");

    if (fp == NULL)
    {
        printf("File Not found\n");
    }
    else
    {
        printf("List of areas\n\n\n");
    }

    while (fscanf(fp, "%d\t%[^\n]s", &areas[global_count_areas].priority_areas, areas[global_count_areas].areas_name) != EOF)
    {
        printf("%s\n", areas[global_count_areas].areas_name);
        global_count_areas++;
    }

    fclose(fp);
}

char *check_source_areas(char *source_areas) // Function to check whether the input given as source is valid input or not
{
    int m, n, j;
    char *z = NULL;
    int found_source = 0;

    m = strlen(source_areas);
    for (int k = 0; k < global_count_areas; k++)
    {
        n = strlen(areas[k].areas_name);

        for (int i = 0; i <= n - m; i++)
        {
            j = 0;

            while (j < m && source_areas[j] == areas[k].areas_name[i + j])
            {
                j++;
                if (j == m)
                {
                    found_source = 1;
                    z = areas[k].areas_name;
                    break;
                }
            }
        }
        if (found_source)
        {
            break;
        }
    }

    if (!found_source)
    {
        printf("Invalid source\n");
    }

    return z;
}

char *check_desti_areas(char *desti_areas)  // Function to check whether the input given as destination is valid input or not
{
    int p, q, j, n;
    char *y = NULL;
    int found_desti = 0;

    p = strlen(desti_areas);

    for (int k = 0; k < global_count_areas; k++)
    {
        q = strlen(areas[k].areas_name);
        for (int i = 0; i <= q - p; i++)
        {
            j = 0;

            while (j < p && desti_areas[j] == areas[k].areas_name[i + j])
            {
                j++;
                if (j == p)
                {
                    found_desti = 1;
                    y = areas[k].areas_name;
                    break;
                }
            }
        }
    }

    if (!found_desti)
    {
        printf("Invalid destination\n");
    }
    return y;
}

int find_source_areas(char *re_source_areas)   // Function to find source's priority number
{
    int i, q = 0;
    for (i = 0; i < v_areas; i++)
    {
        if (strcmp(re_source_areas, areas[i].areas_name) == 0)
        {
            q = areas[i].priority_areas;
            break;
        }
    }
    return q;
}

int find_destination_areas(char *re_desti_areas)   // Function to find destination's priority number
{
    int i, q = 0;
    for (i = 0; i < v_areas; i++)
    {
        if (strcmp(re_desti_areas, areas[i].areas_name) == 0)
        {
            q = areas[i].priority_areas;
            break;
        }
    }
    return q;
}


int min_areas(int oldV, int newV)  // Function check if the distance needs an update
{
    if (oldV > newV)
    {
        return newV;
    }
    return oldV;
}

void dijikstra_areas(int cost_areas[][6], int u_areas, int dist_areas[v_areas], int path_areas[v_areas], int visited_areas[v_areas], int destination_areas) // Function to find shortest distance and path from source to destination using Dijakstra's algorithm
{
    int minV;
    int min_index;
    int flag;

    for (int i = 0; i < v_areas; i++)
    {
        minV = 9999;
        min_index = -1;

        for (int j = 0; j < v_areas; j++)
        {
            if (!visited_areas[j])
            {
                flag = min_areas(dist_areas[j], dist_areas[u_areas] + cost_areas[u_areas][j]);

                if (flag < dist_areas[j])
                {
                    path_areas[j] = u_areas;
                    dist_areas[j] = dist_areas[u_areas] + cost_areas[u_areas][j];
                }

                if (minV > dist_areas[j])
                {
                    minV = dist_areas[j];
                    min_index = j;
                }
            }
        }

        u_areas = min_index;
        visited_areas[min_index] = 1;
    }

    for (int i = 0; i < v_areas; i++)
    {
        if(destination_areas == i)
        {
            printf("Shortest distance between source to destination is: %d", dist_areas[i]);

        }

    }
    for(int i = 0; i < v_areas; i++)
    {
        if(path_areas[i] == areas[i].priority_areas)
        {
            printf("\t via %s",areas[i].areas_name);
        }
    }
}


void dijikstra_for_lookup(int cost_areas[][6], int u_areas, int L_dist[v_areas], int L_path[v_areas], int L_visited[v_areas])  // Function to find shortest distance from one area to all other area and store it in 2d array using Dijakstra's algorithm
{
    int minV;
    int min_index;
    int flag;

    for (int i = 0; i < v_areas; i++)
    {
        minV = 9999;
        min_index = -1;

        for (int j = 0; j < v_areas; j++)
        {
            if (!L_visited[j])
            {
                flag = min_areas(L_dist[j], L_dist[u_areas] + cost_areas[u_areas][j]);

                if (flag < L_dist[j])
                {
                    L_path[j] = u_areas;
                    L_dist[j] = L_dist[u_areas] + cost_areas[u_areas][j];
                }

                if (minV > L_dist[j])
                {
                    minV = L_dist[j];
                    min_index = j;
                }
            }
        }

        u_areas = min_index;
        L_visited[min_index] = 1;
    }
    printf("\n\n\n");
    for(int i = 0; i < v_areas; i++)
    {
        printf("%d\t",L_dist[i]);
    }
}
//----
//---Locations
#define N 100

struct Llocations  // Structure to store locations and a number
{
    int priority_locations;
    char loc_name[150];
};

typedef struct Llocations L;
L locations[300];

int global_count_locations = 0;
int v_locations = 7;

void load_from_file_locations()  // Function to load data from file to structure
{
    FILE *fp;
    fp = fopen("Locations.txt", "r");

    if (fp == NULL)
    {
        printf("File Not found\n");
        return;
    }
    else
    {
        printf("List of areas\n\n\n");
    }

    while (fscanf(fp, "%d\t%[^\n]s", &locations[global_count_locations].priority_locations, locations[global_count_locations].loc_name) != EOF)
    {
        printf("%s\n", locations[global_count_locations].loc_name);
        global_count_locations++;
    }

    fclose(fp);
}

char *check_source_locations(char *source)  // Function to check whether the input given as source is valid input or not
{
    int m, k, n, i, j;
    char *z = NULL;
    int foundSource = 0;

    m = strlen(source);

    for (k = 0; k < global_count_locations; k++)
    {
        n = strlen(locations[k].loc_name);

        for (i = 0; i <= n - m; i++)
        {
            j = 0;

            while (j < m && source[j] == locations[k].loc_name[i + j])
            {
                j++;
                if (j == m)
                {
                    foundSource = 1;
                    z = locations[k].loc_name;
                    break;
                }
            }
        }
        if (foundSource)
        {
            break;
        }
    }

    if (!foundSource)
    {
        printf("Invalid source\n");
    }

    return z;
}

char *check_desti_locations(char *desti)  // Function to check whether the input given as destination is valid input or not
{
    int p, q, k, n, i, j;
    char *y = NULL;
    int foundDesti = 0;

    p = strlen(desti);

    for (k = 0; k < global_count_locations; k++)
    {
        q = strlen(locations[k].loc_name);

        for (i = 0; i <= q - p; i++)
        {
            j = 0;

            while (j < p && desti[j] == locations[k].loc_name[i + j])
            {
                j++;
                if (j == p)
                {
                    foundDesti = 1;
                    y = locations[k].loc_name;
                    break;
                }
            }
        }
    }

    if (!foundDesti)
    {
        printf("Invalid destination\n");
    }
    return y;
}

int find_source_locations(char *re_source)  // Function to find source's priority number
{
    int i, q = 0;
    for (i = 0; i < v_locations; i++)
    {
        if (strcmp(re_source, locations[i].loc_name) == 0)
        {
            q = locations[i].priority_locations;
            break;
        }
    }
    return q;
}

int find_destination_locations(char *re_desti)  // Function to find destination's priority number
{
    int i, q = 0;
    for (i = 0; i < v_locations; i++)
    {
        if (strcmp(re_desti, locations[i].loc_name) == 0)
        {
            q = locations[i].priority_locations;
            break;
        }
    }
    return q;
}

int min_locations(int oldV, int newV)  // Function check if the distance needs an update
{
    if (oldV > newV)
    {
        return 1;
    }
    return 0;
}

void dijikstra_locations(int cost_locations[][7], int u_locations, int dist_locations[v_locations], int path_locations[v_locations], int visited_locations[v_locations], int destination_locations)  // Function to find shortest distance and path from source to destination using Dijakstra's algorithm
{
    int minV;
    int min_index;
    int flag;

    for (int i = 0; i < v_locations; i++)
    {
        minV = 9999;
        min_index = -1;

        for (int j = 0; j < v_locations; j++)
        {
            if (!visited_locations[j])
            {
                flag = min_locations(dist_locations[j], dist_locations[u_locations] + cost_locations[u_locations][j]);

                if (flag < dist_locations[j])
                {
                    path_locations[j] = u_locations;
                    dist_locations[j] = dist_locations[u_locations] + cost_locations[u_locations][j];
                }

                if (minV > dist_locations[j])
                {
                    minV = dist_locations[j];
                    min_index = j;
                }
            }
        }

        u_locations = min_index;
        visited_locations[min_index] = 1;
    }

    for (int i = 0; i < v_locations; i++)
    {
        if(destination_locations == i)
        {
            printf("Shortest distance between source to destination is: %d", dist_locations[i]);

        }

    }
    for(int i = 0; i < v_locations; i++)
    {
        if(path_locations[i] == locations[i].priority_locations)
        {
            printf("\t via %s",locations[i].loc_name);
        }
    }
    printf("\n\n\n");

}
//-----

int main()
{
    int choicee;
    int src_tunnel=0,z=0;
            int m[6][6] =      // Adjacency matrix of areas
            {
                {0,1,0,0,1,0},
                {1,0,1,0,1,0},
                {0,1,0,1,0,0},
                {0,0,1,0,1,1},
                {1,1,0,1,0,0},
                {0,0,0,1,0,0}
            };

    do
    {
        printf("\n\nPress 1 to travel in your locality\n");
        printf("Press 2 to travel from one area to another\n");
        printf("Press 3 to view blueprint of the under ground tunnel to store rainwater\n");
        printf("Press 4 to EXIT\n");
        scanf("%d",&choicee);
        switch(choicee)
        {
        case 1:
            load_from_file_locations();

            char source_locations[150], desti_locations[150];
            char *re_source_locations;
            char *re_desti_locations;
            int src_locations,destination_locations;

            printf("Enter the place you are in: ");
            scanf("%s", source_locations);
            printf("Enter the place you want to visit: ");
            scanf("%s", desti_locations);

            re_source_locations = check_source_locations(source_locations);  // Value returned from check_source function is stored in re_source
            re_desti_locations = check_desti_locations(desti_locations);     // Value returned from check_desti function is stored in re_desti
            src_locations = find_source_locations(re_source_locations);      // Priority number returned from function find_source is stored in src
            destination_locations = find_destination_locations(re_desti_locations);  // Priority number returned from function find_destination is stored in destination

            int cost_locations[7][7] = {{0, 2, 9999, 3, 9999, 9999, 9999}, // Matrix which represents the distance from one location to other if they are adjacent to each other
                {2, 0, 9999, 5, 9999, 6, 8},
                {9999, 9999, 0, 9999, 3, 5, 9999},
                {3, 5, 9999, 0, 1, 9999, 9999},
                {9999, 9999, 3, 1, 0, 4, 9},
                {9999, 6, 5, 9999, 4, 0, 2},
                {9999, 8, 9999, 9999, 9, 2, 0}
            };

            int dist_locations[20];
            int path_locations[20];
            int visited_locations[20] = {0};

            for (int i = 0; i < v_locations; i++)
            {
                path_locations[i] = src_locations;
            }

            for (int i = 0; i < v_locations; i++)
            {
                dist_locations[i] = cost_locations[src_locations][i];
            }

            visited_locations[src_locations] = 1;
            int u_locations;
            int m_locations = 99999;
            for (int i = 0; i < v_locations; i++)
            {
                if (dist_locations[i] < m_locations && visited_locations[i] != 1)
                {
                    u_locations = i;
                    m_locations = dist_locations[u_locations];
                }
            }
            visited_locations[u_locations] = 1;
            dijikstra_locations(cost_locations, u_locations, dist_locations, path_locations, visited_locations, destination_locations);  // Function call for Dijakstra
            break;
        case 2:
            load_from_file_areas();

            char source_areas[150], desti_areas[150];
            char *re_source_areas;
            char *re_desti_areas;
            int src_areas,destination_areas;
            int dist_areas[20];
            int path_areas[20];
            int visited_areas[20] = {0};
            int cost_areas[6][6] = {{0, 20, 15, 9999, 9999, 9999},   // Matrix which represents the distance from one area to other if they are adjacent to each other
                {20, 0, 9999, 23, 7, 10},
                {15, 9999, 0, 25, 9999, 9999},
                {9999, 23, 25, 0, 9999, 9999},
                {9999, 7, 9999, 9999, 0, 9},
                {9999, 10, 9999, 9999, 9, 0}
            };

            printf("Enter the source: ");
            scanf("%s", source_areas);
            printf("Enter the destination: ");
            scanf("%s", desti_areas);

            re_source_areas = check_source_areas(source_areas);  // Value returned from check_source function is stored in re_source
            re_desti_areas = check_desti_areas(desti_areas);     // Value returned from check_desti function is stored in re_desti
            src_areas = find_source_areas(re_source_areas);      // Priority number returned from function find_source is stored in src
            destination_areas = find_destination_areas(re_desti_areas);   // Priority number returned from function find_destination is stored in destination


            for (int i = 0; i < v_areas; i++)
            {
                path_areas[i] = src_areas;
            }

            for (int i = 0; i < v_areas; i++)
            {
                dist_areas[i] = cost_areas[src_areas][i];
            }

            visited_areas[src_areas] = 1;
            int u_areas;
            int m_areas = 99999;
            for (int i = 0; i < v_areas; i++)
            {
                if (dist_areas[i] < m_areas && visited_areas[i] != 1)
                {
                    u_areas = i;
                    m_areas = dist_areas[u_areas];
                }
            }
            visited_areas[u_areas] = 1;
            dijikstra_areas(cost_areas, u_areas, dist_areas, path_areas, visited_areas, destination_areas);  // Function call for Dijakstra
            int L_source;
            printf("\n\n\nHere is the table(Look Up table) which shows the shortest distance from one path to all other parts\n\n\n");


            for (int i = 0; i < v_areas; i++)  // Loop to give each area as source
            {
                int L_dist[20];
                int L_path[20];
                int L_visited[20] = {0};
                L_source=i;
                for(int j = 0; j < v_areas; j++)
                {
                    L_path[j] = L_source;
                    L_dist[j] = cost_areas[L_source][j];
                }
                L_visited[L_source] = 1;
                int u_areas;
                int m_areas = 99999;
                for (int i = 0; i < v_areas; i++)
                {
                    if (L_dist[i] < m_areas && L_visited[i] != 1)
                    {
                        u_areas = i;
                        m_areas = L_dist[u_areas];
                    }
                }
                visited_areas[u_areas] = 1;
                dijikstra_for_lookup(cost_areas, u_areas, L_dist, L_path, L_visited); // Call for Dijakstra's function for look up table
            }
            break;
        case 3:
            load_from_file_tunnel();
            int A[v_tunnel];
            copy(v_tunnel, A);
            mergesort(A, v_tunnel);
            z=find_max(A);
            src_tunnel=find_source_tunnel(z);
            int visited[6] = {0};
            printf("Construction of under ground passage as per Depth First Search Traversal is.... \n");
            for(int k=0; k<v_tunnel; k++)
            {
                if(src_tunnel==areas_tunnel[k].priority_tunnel)
                {
                    printf("\n%s",areas_tunnel[k].areas_name_tunnel);
                }
            }
            dfs(m, visited, src_tunnel);
            printf("\n\n\nConstruction of under ground passage as per Breadth First Search Traversal is.... \n");
            bfs(m,src_tunnel);
            printf("\n");
            break;
        }
    }
    while(choicee!=4);

    return 0;
}
