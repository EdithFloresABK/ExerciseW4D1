#include <iostream>
#include <chrono>
#include <map>
#include <limits.h>

#define V 4
using namespace std;

uint32_t GetNanos();
void PrintArray(int arr[], int size);
void FillArray(int arr[], int size);

void SelectionSort(int arr[], int size);
int minDistance(int allEdges[], bool isClosed[],int totalVertices);
void printSolution(int allEdges[], int dest);
void AStar(int graph[V][V], int src, int dest);
void createGraph(int graph[V][V]);


int main()
{
    cout << "Hello Traveler! Nice to see you again.\n Would you like to do Challenge 1 or Challenge 2? ";
    int challenge;
    cin >> challenge;
    cout << '\n';
    cout << "Great!\n";

    uint32_t startNano;
    uint32_t endNano;
    int size;

    int graph[V][V];
    int src;
    int dest;
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
        cout << "We will now use the A* algorithm with Heuristics of 0" << endl;

        createGraph(graph);
        cout << "Great now I need two more things to get you your answer.\n";
        cout << "\n What is the source? ";
        cin >> src;
        cout << "\n What is the destination? ";
        cin >> dest;
        cout << '\n';

        AStar(graph, src-1,dest-1);
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
    int min = INT_MAX;
    int min_index = 0;

    for (int v = 0; v < totalVertices; v++)
        if (isClosed[v] == false && allEdges[v] <= min)
            min = allEdges[v], min_index = v;

    return min_index;
}
// A utility function to print the constructed distance array
void printSolution(int allEdges[], int dest)
{
    printf("Perfect! The distance from Source to Destination is ");
    cout << allEdges[dest] << endl;
}
void createGraph(int graph[V][V]){
    //Blank graph
    for(int x=0;x<V;x++){
        for (int y= 0; y < V; y++) {
            graph[x][y] = 0;
        }
    }

    cout << "\n How many edges do you have? ";
    int numEdges;
    cin >> numEdges;
    cout << "Legend: 1)a 2)b 3)c 4)d\n";
    int firstEdge;
    int secondEdge;
    int cost;
    for (int i =0;i<numEdges;i++){
        cout << "\n What is the first edge?: ";
        cin >> firstEdge;
        cout << "\n What is the second edge?: ";
        cin >> secondEdge;
        cout << "\n What is the vertex cost?: ";
        cin >> cost;
        cout << '\n';
        graph[firstEdge - 1][secondEdge - 1] = cost;
        graph[secondEdge - 1][firstEdge - 1] = cost;
    }
}
void AStar(int graph[4][4], int src, int dest)
{
    //Heuristic of 0

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

    cout << "Sorry! Destination was never found." << endl;
}

uint32_t GetNanos() {
    using namespace std::chrono;
    return static_cast<uint32_t>(duration_cast<nanoseconds>(system_clock::now().time_since_epoch()).count());
}