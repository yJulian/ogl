#include <GL/glew.h>
#include <GL/glut.h>
#include <cmath>
#include <glm/glm.hpp>
#include <cmath>

#define N 128

GLfloat vertices[N*N][3];
GLfloat colors[N*N][3];
GLuint indices[6*(N-1)*(N-1)];

GLuint vboVertices, vboColors, ebo;
float angle = 0.0f;
int x = 1920;
int y = 1080;

void generateIndices() {
    int idx = 0;
    for (int x = 0; x < N-1; ++x) {
        for (int y = 0; y < N-1; ++y) {
            const int topLeft     = x * N + y;
            const int topRight    = topLeft + 1;
            const int bottomLeft  = (x+1) * N + y;
            const int bottomRight = bottomLeft + 1;

            indices[idx++] = topLeft;
            indices[idx++] = bottomLeft;
            indices[idx++] = topRight;
            indices[idx++] = topRight;
            indices[idx++] = bottomLeft;
            indices[idx++] = bottomRight;
        }
    }
}

void generateVertices() {
    constexpr float distance = 1.0f / (N-1);
    for (int x = 0; x < N; ++x) {
        for (int y = 0; y < N; ++y) {
            int idx = x*N + y;
            vertices[idx][0] = distance * static_cast<float>(x);
            vertices[idx][1] = 0.0f;
            vertices[idx][2] = distance * static_cast<float>(y);

            colors[idx][0] = 0.f;
            colors[idx][1] = 0.f;
            colors[idx][2] = 0.f;
        }
    }
    generateIndices();
}

glm::vec3 calculateColor(float h) {
    return {0.5f + 0.5f*h, 0.5f - 0.5f*h, 0.2f};
}

void updateHeight(float t) {
    for (int i = 0; i < N*N; ++i) {
        const float x = vertices[i][0];
        const float z = vertices[i][2];
        const float h = glm::sin(10.0f * x + t) * glm::cos(10.0f * z + t);

        vertices[i][1] = h * 0.2f;
        glm::vec3 c = calculateColor(h);
        colors[i][0] = c.x;
        colors[i][1] = c.y;
        colors[i][2] = c.z;
    }

    glBindBuffer(GL_ARRAY_BUFFER, vboVertices);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
    glBindBuffer(GL_ARRAY_BUFFER, vboColors);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(colors), colors);
}

void initGL() {
    glewInit();
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.2f, 0.2f, 0.3f, 1.0f);

    glGenBuffers(1, &vboVertices);
    glBindBuffer(GL_ARRAY_BUFFER, vboVertices);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, (void*)0);

    glGenBuffers(1, &vboColors);
    glBindBuffer(GL_ARRAY_BUFFER, vboColors);
    glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_DYNAMIC_DRAW);
    glEnableClientState(GL_COLOR_ARRAY);
    glColorPointer(3, GL_FLOAT, 0, (void*)0);

    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, static_cast<float>(x)/static_cast<float>(y), 0.1, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(-0.5f, -0.0f, -1.5f);
    //glRotatef(angle, 1.0f, 1.0f, 0.0f);
    glDrawElements(GL_TRIANGLES, 6*(N-1)*(N-1), GL_UNSIGNED_INT, nullptr);
    glutSwapBuffers();
}

void timer(int value) {
    angle += 1.0f;
    if (angle > 360.0f) angle -= 360.0f;
    updateHeight(angle * 0.05f);
    glutPostRedisplay();
    glutTimerFunc(16, timer, 0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(x, y);
    glutCreateWindow("OpenGL");
    generateVertices();

    initGL();
    glutDisplayFunc(display);
    glutTimerFunc(0, timer, 0);
    glutMainLoop();
    return 0;
}