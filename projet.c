#include <stdio.h>

#define num_noeud 11
#define NUM_NODES 11
#define DAMPING_FACTOR 0.85
#define MAX_ITERATIONS 100

void initializeMatrix(int Matrice_ad[num_noeud][num_noeud], int edges[][2], int num_edges) {
    for (int i = 0; i < num_edges; i++) {
        int from = edges[i][0];
        int to = edges[i][1];
        Matrice_ad[from - 1][to - 1] = 1;
    }
}

void printAdjacencyMatrix(int Matrice_ad[num_noeud][num_noeud]) {
    printf("Matrice d'adjacence:\n");
    for (int i = 0; i < num_noeud; i++) {
        for (int j = 0; j < num_noeud; j++) {
            printf("%d ", Matrice_ad[i][j]);
        }
        printf("\n");
    }
}

void initializePageRank(double pageRank[NUM_NODES]) {
    for (int i = 0; i < NUM_NODES; i++) {
        pageRank[i] = 1.0 / NUM_NODES;
    }
}

void calculatePageRank(int Matrice_ad[num_noeud][num_noeud], double pageRank[NUM_NODES], double newPageRank[NUM_NODES]) {
    for (int i = 0; i < NUM_NODES; i++) {
        for (int j = 0; j < NUM_NODES; j++) {
            if (Matrice_ad[j][i] == 1) {
                int outgoingLinks = 0;
                for (int k = 0; k < NUM_NODES; k++) {
                    outgoingLinks += Matrice_ad[j][k];
                }
                newPageRank[i] += DAMPING_FACTOR * pageRank[j] / outgoingLinks;
            }
        }
        newPageRank[i] += (1 - DAMPING_FACTOR) / NUM_NODES;
    }
}

void updatePageRank(double pageRank[NUM_NODES], double newPageRank[NUM_NODES]) {
    for (int i = 0; i < NUM_NODES; i++) {
        pageRank[i] = newPageRank[i];
    }
}

void normalizePageRank(double pageRank[NUM_NODES]) {
    double sum = 0;
    for (int i = 0; i < NUM_NODES; i++) {
        sum += pageRank[i];
    }

    for (int i = 0; i < NUM_NODES; i++) {
        pageRank[i] /= sum;
    }
}

void printFinalPageRank(double pageRank[NUM_NODES]) {
    printf("Final PageRank scores:\n");
    for (int i = 0; i < NUM_NODES; i++) {
        printf("Node %d: %f\n", i + 1, pageRank[i]);
    }
}
void rank(double pageRank[NUM_NODES], int classement[NUM_NODES]) {
    for (int i = 0; i < NUM_NODES; i++) {
        classement[i] = i;
    }
    for (int i = 0; i < NUM_NODES - 1; i++) {
        for (int j = i + 1; j < NUM_NODES; j++) {
            if (pageRank[classement[i]] < pageRank[classement[j]]) {
                int temp = classement[i];
                classement[i] = classement[j];
                classement[j] = temp;
            }
        }
    }
}

void printRankedPageRank(double pageRank[NUM_NODES], int classement[NUM_NODES]) {
    printf("Classement des pages par PageRank:\n");
    for (int i = 0; i < NUM_NODES; i++) {
        int n = classement[i];
        printf("Page %d: %f\n", n + 1, pageRank[n]);
    }
}



int main() {
    int Matrice_ad[num_noeud][num_noeud] = {0};
    int edges[][2] = {
        {2, 3},
        {3, 2},
        {4, 1},{4, 2},
        {5, 4},{5, 6},
        {6, 5},{6, 2},
        {7, 2},{7,5},
        {8, 5},{8,2},
        {9, 5},{9,2},
        {10, 5},
        {11, 5},
        };

    initializeMatrix(Matrice_ad, edges, 15);
    printAdjacencyMatrix(Matrice_ad);

    double pageRank[NUM_NODES];
    initializePageRank(pageRank);

    for (int iter = 0; iter < MAX_ITERATIONS; iter++) {
        double newPageRank[NUM_NODES] = {0};
        calculatePageRank(Matrice_ad, pageRank, newPageRank);
        updatePageRank(pageRank, newPageRank);
    }

    normalizePageRank(pageRank);
    int classement[NUM_NODES];
    rank(pageRank, classement);
    printRankedPageRank(pageRank, classement);

    return 0;
}