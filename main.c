#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "frac_doublelinklist.h"

typedef struct point {
    float x, y, z;
} Point;

typedef struct Triangle {
    Point *point1, *point2, *point3;
} Triangle;

typedef struct mesh {
    DoublyList triangle_array;
} Mesh;

Point* createPoint(float x, float y, float z) {
    Point* p = (Point*)malloc(sizeof(Point));
    p->x = x; p->y = y; p->z = z;
    return p;
}

Triangle* createTriangle(Point* p1, Point* p2, Point* p3) {
    Triangle* t = (Triangle*)malloc(sizeof(Triangle));
    t->point1 = p1; t->point2 = p2; t->point3 = p3;
    return t;
}

void generateFractal(Mesh* mesh, float cx, float cy, float cz, float size, int depth) {
    
    if(depth == 0){
        addFront(&mesh->triangle_array , createTriangle(createPoint(cx,cy,cz) , createPoint(cx+size,cy,cz),createPoint(cx,cy+size,cz)));
        addFront(&mesh->triangle_array , createTriangle(createPoint(cx+size,cy+size,cz),createPoint(cx+size,cy,cz),createPoint(cx,cy+size,cz)));
        addFront(&mesh->triangle_array , createTriangle(createPoint(cx,cy+size,cz),createPoint(cx,cy+size,cz+size),createPoint(cx+size,cy+size,cz)));
        addFront(&mesh->triangle_array , createTriangle(createPoint(cx+size,cy+size,cz+size),createPoint(cx+size,cy+size,cz),createPoint(cx+size,cy,cz)));
        addFront(&mesh->triangle_array , createTriangle(createPoint(cx+size,cy,cz+size),createPoint(cx+size,cy+size,cz+size),createPoint(cx+size,cy,cz)));
        addFront(&mesh->triangle_array , createTriangle(createPoint(cx,cy+size,cz+size),createPoint(cx+size,cy+size,cz),createPoint(cx+size,cy+size,cz+size)));
        addFront(&mesh->triangle_array , createTriangle(createPoint(cx+size,cy,cz+size),createPoint(cx,cy+size,cz+size),createPoint(cx+size,cy+size,cz+size)));
        addFront(&mesh->triangle_array , createTriangle(createPoint(cx,cy,cz+size),createPoint(cx,cy+size,cz+size),createPoint(cx+size,cy,cz+size)));
        addFront(&mesh->triangle_array , createTriangle(createPoint(cx+size,cy,cz+size),createPoint(cx+size,cy,cz),createPoint(cx,cy,cz+size)));
        addFront(&mesh->triangle_array , createTriangle(createPoint(cx,cy,cz+size),createPoint(cx+size,cy,cz),createPoint(cx,cy,cz)));
        addFront(&mesh->triangle_array , createTriangle(createPoint(cx,cy+size,cz),createPoint(cx,cy+size,cz+size),createPoint(cx,cy,cz)));
        addFront(&mesh->triangle_array , createTriangle(createPoint(cx,cy,cz),createPoint(cx,cy,cz+size),createPoint(cx,cy+size,cz+size)));
        return;
    }

    Mesh mesh1;
    initDoublyList(&mesh1.triangle_array);
    generateFractal(&mesh1,cx+size,cy+(size/4),cz+(size/4),size/2,depth-1);
    Mesh mesh2;
    initDoublyList(&mesh2.triangle_array);
    generateFractal(&mesh2,cx+(size/4),cy+size,cz+(size/4),size/2,depth-1);
    Mesh mesh3;
    initDoublyList(&mesh3.triangle_array);
    generateFractal(&mesh3,cx+(size/4),cy+(size/4),cz+size,size/2,depth-1);
    Mesh mesh4;
    initDoublyList(&mesh4.triangle_array);
    generateFractal(&mesh4,cx-(size/2),cy+(size/4),cz+(size/4),size/2,depth-1);
    Mesh mesh5;
    initDoublyList(&mesh5.triangle_array);
    generateFractal(&mesh5,cx+(size/4),cy+(size/4),cz-(size/2),size/2,depth-1);
    Mesh mesh6;
    initDoublyList(&mesh6.triangle_array);
    generateFractal(&mesh6,cx+(size/4),cy-(size/2),cz+(size/4),size/2,depth-1);

    Node* current = mesh1.triangle_array.head;
    int y = mesh1.triangle_array.elemcount;
    for(int i=0; i<y && current!=NULL; i++){
        addFront(&mesh->triangle_array,current->data);
        current = current->next;
        removeFront(&mesh1.triangle_array);
    }

    current = mesh2.triangle_array.head;
    y = mesh2.triangle_array.elemcount;
    for(int i=0; i<y && current!=NULL; i++){
        addFront(&mesh->triangle_array,current->data);
        current = current->next;
        removeFront(&mesh2.triangle_array);
    }   
    
    current = mesh3.triangle_array.head;
    y = mesh3.triangle_array.elemcount;
    for(int i=0; i<y && current!=NULL; i++){
        addFront(&mesh->triangle_array,current->data);
        current = current->next;
        removeFront(&mesh3.triangle_array);
    }

    current = mesh4.triangle_array.head;
    y = mesh4.triangle_array.elemcount;
    for(int i=0; i<y && current!=NULL; i++){
        addFront(&mesh->triangle_array,current->data);
        current = current->next;
        removeFront(&mesh4.triangle_array);
    }

    current = mesh5.triangle_array.head;
    y = mesh5.triangle_array.elemcount;
    for(int i=0; i<y && current!=NULL; i++){
        addFront(&mesh->triangle_array,current->data);
        current = current->next;
        removeFront(&mesh5.triangle_array);
    }

    current = mesh6.triangle_array.head;
    y = mesh6.triangle_array.elemcount;
    for(int i=0; i<y && current!=NULL; i++){
        addFront(&mesh->triangle_array,current->data);
        current = current->next;
        removeFront(&mesh6.triangle_array);
    }

    addFront(&mesh->triangle_array , createTriangle(createPoint(cx,cy,cz) , createPoint(cx+size,cy,cz),createPoint(cx,cy+size,cz)));
    addFront(&mesh->triangle_array , createTriangle(createPoint(cx+size,cy+size,cz),createPoint(cx+size,cy,cz),createPoint(cx,cy+size,cz)));
    addFront(&mesh->triangle_array , createTriangle(createPoint(cx,cy+size,cz),createPoint(cx,cy+size,cz+size),createPoint(cx+size,cy+size,cz)));
    addFront(&mesh->triangle_array , createTriangle(createPoint(cx+size,cy+size,cz+size),createPoint(cx+size,cy+size,cz),createPoint(cx+size,cy,cz)));
    addFront(&mesh->triangle_array , createTriangle(createPoint(cx+size,cy,cz+size),createPoint(cx+size,cy+size,cz+size),createPoint(cx+size,cy,cz)));
    addFront(&mesh->triangle_array , createTriangle(createPoint(cx,cy+size,cz+size),createPoint(cx+size,cy+size,cz),createPoint(cx+size,cy+size,cz+size)));
    addFront(&mesh->triangle_array , createTriangle(createPoint(cx+size,cy,cz+size),createPoint(cx,cy+size,cz+size),createPoint(cx+size,cy+size,cz+size)));
    addFront(&mesh->triangle_array , createTriangle(createPoint(cx,cy,cz+size),createPoint(cx,cy+size,cz+size),createPoint(cx+size,cy,cz+size)));
    addFront(&mesh->triangle_array , createTriangle(createPoint(cx+size,cy,cz+size),createPoint(cx+size,cy,cz),createPoint(cx,cy,cz+size)));
    addFront(&mesh->triangle_array , createTriangle(createPoint(cx,cy,cz+size),createPoint(cx+size,cy,cz),createPoint(cx,cy,cz)));
    addFront(&mesh->triangle_array , createTriangle(createPoint(cx,cy+size,cz),createPoint(cx,cy+size,cz+size),createPoint(cx,cy,cz)));
    addFront(&mesh->triangle_array , createTriangle(createPoint(cx,cy,cz),createPoint(cx,cy,cz+size),createPoint(cx,cy+size,cz+size)));
}

void save_stl(const char* filename, Mesh* mesh) {
    FILE* f = fopen(filename, "w");
    if (!f) {
        perror("Error opening STL file");
        return;
    }
    fprintf(f, "solid fractal_cube\n");

    Node* node = mesh->triangle_array.head;
    while (node) {
        Triangle* t = node->data;
        fprintf(f, "facet normal 0 0 0\n");
        fprintf(f, "  outer loop\n");
        fprintf(f, "    vertex %f %f %f\n", t->point1->x, t->point1->y, t->point1->z);
        fprintf(f, "    vertex %f %f %f\n", t->point2->x, t->point2->y, t->point2->z);
        fprintf(f, "    vertex %f %f %f\n", t->point3->x, t->point3->y, t->point3->z);
        fprintf(f, "  endloop\n");
        fprintf(f, "endfacet\n");
        node = node->next;
    }
    fprintf(f, "endsolid fractal_cube\n");
    fclose(f);
}

int main() {
    while (1) {
        int option;
        printf("------------------------------------\n");
        printf("1- Cube Pattern\n");
        printf("2- Quit\n");
        printf("------------------------------------\n");
        printf("Please enter an action: ");
        scanf("%d", &option);

        if (option == 1) {
            int iteration;
            printf("Enter Iteration count: ");
            scanf("%d", &iteration);

            Mesh mesh;
            initDoublyList(&mesh.triangle_array);
            generateFractal(&mesh, 0.0f, 0.0f, 0.0f, 1.0f, iteration);
            save_stl("cube_result.stl", &mesh);
            Node* old = NULL;
            Node* current = mesh.triangle_array.head;
            int y = mesh.triangle_array.elemcount;
            for(int i=0; i<y && current != NULL; i++){
                old = current;
                current = current->next;
                free(old->data->point1);
                free(old->data->point2);
                free(old->data->point3);
                free(old->data);
                removeFront(&mesh.triangle_array);
            }
            printf("STL file 'cube_result.stl' generated.\n");
        } else if (option == 2) {
            break;
        }
    }
    return 0;
}
