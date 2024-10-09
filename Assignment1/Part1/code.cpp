#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "code.h"
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <vector>

//////////////////////////////////////////////////////
// The Global Variables To Be Used

struct Triangle {
    double vertices[3][2];
    double matrix[3][3];
    int color_index;
};

// list of triangles, each element is of type Triangle
// to access the kth triangle, just use triangles[k]
// to get the number of triangles in the list, use triangles.size()
std::vector<Triangle> triangles;

// a triangle object for temporary storage of points
Triangle triangle_to_draw;
// count the number of points specified in this triangle
int point_count = 0;

// color array for triangles
// size is 11. So color_index should range from 0 to 10 for triangles.
double color_array[][3] = {{0.9, 0, 0},  // red
                           {0, 0.5, 0.4},  {0.1, 0.2, 0.46}, {0.9, 0.9, 0},
                           {0, 1.0, 0},    {0, 1.0, 1.0},    {0, 0, 1.0},
                           {1.0, 0, 1.0},  {0.9, 0.6, 0},    {0.9, 1.0, 0.6},
                           {0.2, 0.2, 0.2}};

/////////////////////////////////////////////////////////////////////////////////////////
// This function is called to clear triangles.

void ClearTriangles() {
    triangles.clear();
    point_count = 0;
}

/////////////////////////////////////////////////////////////////////////////////////////
// This function is called to draw triangles in the Triangles window.

void DrawTriangles() {
    // uncomment this line if you would like to unfill triangles
    // glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);

    glPointSize(4);

    // Draw previous triangles
    glBegin(GL_TRIANGLES);
    for (Triangle t : triangles) {
        glColor3d(color_array[t.color_index][0], color_array[t.color_index][1],
                  color_array[t.color_index][2]);
        for (int i = 0; i < 3; i++) {
            glVertex2d(t.vertices[i][0], t.vertices[i][1]);
        }
    }
    glEnd();

    // Draw vertices of current triangle
    glBegin(GL_POINTS);
    int next_triangle_idx = triangles.size();
    glColor3d(color_array[next_triangle_idx % 11][0],
              color_array[next_triangle_idx % 11][1],
              color_array[next_triangle_idx % 11][2]);
    for (int i = 0; i < point_count; i++) {
        glVertex2d(triangle_to_draw.vertices[i][0],
                   triangle_to_draw.vertices[i][1]);
    }
    glEnd();
}

/////////////////////////////////////////////////////////////////////////////////////////
// This function is called to handle mouse left click events.
// m_x and m_y are the x and y coordinates of the clicked point in OpenGL
// coordinate system.

void MouseInteraction(double m_x, double m_y) {
    // Add new point to the temporary triangle
    triangle_to_draw.vertices[point_count][0] = m_x;
    triangle_to_draw.vertices[point_count][1] = m_y;
    point_count++;

    // When 3 points are specified, we get a new triangle
    if (point_count != 3) return;
    triangle_to_draw.color_index = triangles.size() % 11;
    triangles.push_back(Triangle(triangle_to_draw));
    point_count = 0;
}
