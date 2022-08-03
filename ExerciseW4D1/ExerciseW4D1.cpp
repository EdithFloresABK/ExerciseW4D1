#include <iostream>
#include <chrono>
#include <map>
#include <limits.h>

using namespace std;

uint32_t GetNanos();
void PrintArray(int arr[], int size);
void FillArray(int arr[], int size);

void SelectionSort(int arr[], int size);
int minDistance(int allEdges[], bool isClosed[],int totalVertices);
void printSolution(int allEdges[], int dest);
void dijkstra(int graph[4][4], int src, int dest);


int main()
{
    cout << "Hello Traveler! Would you like to do Challenge 1 or Challenge 2? ";
    int challenge;
    cin >> challenge;
    cout << '\n';

    uint32_t startNano;
    uint32_t endNano;;
    int size;

    const int V = 4;
    int graph[V][V] = { {0,5,0,7},{5,0,1,0},{0,1,0,1},{7,0,1,0} };
    switch (challenge) {
    case 1:
        cout << "We will now use the Selection Sort Algorithm using various array sizes" << endl;

        size = 4;
        int Dataset[4];
        FillArray(Dataset, size);
        cout << "Array size:" << size << endl;
        cout << "Unsorted: ";
        PrintArray(Dataset, size);
        startNano = GetNanos();
        SelectionSort(Dataset, size);
        endNano = GetNanos();
        cout << "Sorted: ";
        PrintArray(Dataset, size);
        cout << "Duration (ns): " << (endNano-startNano) << endl;
        cout << "-----------------------------------------------------------" << endl;

        size = 16;
        int Dataset2[16];
        FillArray(Dataset2, size);
        cout << "Array size:" << size << endl;
        cout << "Unsorted: ";
        PrintArray(Dataset2, size);
        startNano = GetNanos();
        SelectionSort(Dataset2, size);
        endNano = GetNanos();
        cout << "Sorted: ";
        PrintArray(Dataset2, size);
        cout << "Duration (ns): " << (endNano - startNano) << endl;
        cout << "-----------------------------------------------------------" << endl;

        size = 167;
        int Dataset3[167];
        FillArray(Dataset3, size);
        cout << "Array size:" << size << endl;
        startNano = GetNanos();
        SelectionSort(Dataset3, size);
        endNano = GetNanos();
        cout << "Duration (ns): " << (endNano - startNano) << endl;
        cout << "-----------------------------------------------------------" << endl;

        size = 1000;
        int Dataset4[1000];
        FillArray(Dataset4, size);
        cout << "Array size:" << size << endl;
        startNano = GetNanos();
        SelectionSort(Dataset4, size);
        endNano = GetNanos();
        cout << "Duration (ns): " << (endNano - startNano) << endl;
        cout << "-----------------------------------------------------------" << endl;

        break;

    case 2:
        cout << "We will now use the Dijkstra algorithm" << endl;

        dijkstra(graph, 0,3);
        break;

    default:
        cout << "Invalid choice. Exiting now. Rerun to start again.\n";
        break;
    }

    return 0;
}
void PrintArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}
void FillArray(int arr[], int size) {

    for (int i = 0; i < size; i++) {
        arr[i] = rand()%size;
    }
}

void SelectionSort(int arr[], int size) {
    //Loop through the array
    int smallest;
    int index;
    int temp;

    for (int i = 0; i < size; i++) {
        smallest = arr[i];
        index = i;

        for (int j = i; j < size; j++) {
            if (smallest > arr[j]) {
                smallest = arr[j];
                index = j;
            }
        }

        temp = arr[i];
        arr[i] = arr[index];
        arr[index] = temp;
    }
}
int minDistance(int allEdges[], bool isClosed[], int totalVertices)
{
    // Initialize min value
    int min = INT_MAX, min_index;

    for (int v = 0; v < totalVertices; v++)
        if (isClosed[v] == false && allEdges[v] <= min)
            min = allEdges[v], min_index = v;

    return min_index;
}
// A utility function to print the constructed distance array
void printSolution(int allEdges[], int dest)
{
    printf("Distance from Source to Destination\n");
    cout << allEdges[dest] << endl;
}
void dijkstra(int graph[4][4], int src, int dest)
{
    const int V = 4;
    int allEdges[V]; // The output array.  Will hold all the lowest paths to all edges

    bool isClosed[V]; // isClosed[i] will be true if vertex i is included in shortest
    // path tree or shortest distance from src to i is finalized

    // Initialize all distances as INFINITE and isClosed[] as false
    for (int i = 0; i < V; i++)
        allEdges[i] = INT_MAX, isClosed[i] = false;

    // Distance of source vertex from itself is always 0
    allEdges[src] = 0;

    // Find shortest path for all vertices until we are evaluating the destination
    for (int count = 0; count < V; count++) {
        // Pick the minimum distance vertex from the set of vertices not
        // yet processed.
        int u = minDistance(allEdges, isClosed,4);

        //If source is what we are evaluating. We can stop here.
        if (u == dest) {
            printSolution(allEdges, dest);
            return;
        }

        // Mark the picked vertex as processed so it doesnt process itself
        isClosed[u] = true;

        // Update dist value of the adjacent vertices of the picked vertex.
        for (int v = 0; v < V; v++) {

            // Update allEdges[v] only if is not in isClosed, there is an edge from
            // u to v, and total weight of path from src to  v through u is
            // smaller than current value of dist[v]
            if (!isClosed[v] && graph[u][v] && allEdges[u] != INT_MAX
                && allEdges[u] + graph[u][v] < allEdges[v])
                allEdges[v] = allEdges[u] + graph[u][v];
        }
    }

    cout << "Destination Never found. Sorry!" << endl;
}

uint32_t GetNanos() {
    using namespace std::chrono;
    return static_cast<uint32_t>(duration_cast<nanoseconds>(system_clock::now().time_since_epoch()).count());
}