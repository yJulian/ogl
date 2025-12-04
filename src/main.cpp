#include <GL/glew.h>
#include <GL/glut.h>
#include <iostream>

GLfloat vertices[][3] = {
    {-0.5f, -0.5f, -0.5f}, // v0
    { 0.5f, -0.5f, -0.5f}, // v1
    { 0.5f,  0.5f, -0.5f}, // v2
    {-0.5f,  0.5f, -0.5f}, // v3
    {-0.5f, -0.5f,  0.5f}, // v4
    { 0.5f, -0.5f,  0.5f}, // v5
    { 0.5f,  0.5f,  0.5f}, // v6
    {-0.5f,  0.5f,  0.5f}  // v7
};

GLfloat colors[][3] = {
    {1.0f, 0.0f, 0.0f}, // v0 rot
    {0.0f, 1.0f, 0.0f}, // v1 grün
    {0.0f, 0.0f, 1.0f}, // v2 blau
    {1.0f, 1.0f, 0.0f}, // v3 gelb
    {1.0f, 0.0f, 1.0f}, // v4 magenta
    {0.0f, 1.0f, 1.0f}, // v5 cyan
    {1.0f, 1.0f, 1.0f}, // v6 weiß
    {0.5f, 0.5f, 0.5f}  // v7 grau
};

GLuint indices[] = {
    // Front
    4, 5, 6,  4, 6, 7,
    // Back
    0, 2, 1,  0, 3, 2,
    // Left
    0, 4, 7,  0, 7, 3,
    // Right
    1, 2, 6,  1, 6, 5,
    // Bottom
    0, 1, 5,  0, 5, 4,
    // Top
    3, 7, 6,  3, 6, 2
};

GLuint vboVertices, vboColors, ebo;
float angle = 0.0f;

void initGL()
{
    glewInit();

    glEnable(GL_DEPTH_TEST);
    //glClearColor(0.2f, 0.2f, 0.3f, 1.0f); // Hintergrundfarbe

    // Vertex Buffer
    glGenBuffers(1, &vboVertices);
    glBindBuffer(GL_ARRAY_BUFFER, vboVertices);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, 0);

    // Color Buffer
    glGenBuffers(1, &vboColors);
    glBindBuffer(GL_ARRAY_BUFFER, vboColors);
    glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);

    glEnableClientState(GL_COLOR_ARRAY);
    glColorPointer(3, GL_FLOAT, 0, 0);

    // Index Buffer
    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Projektion setzen
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, 800.0/600.0, 0.1, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();
    glTranslatef(0.0f, 0.0f, -5.0f);
    glRotatef(angle, 1.0f, 1.0f, 0.0f);

    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, nullptr);

    glutSwapBuffers();
}

void timer(int value)
{
    angle += 1.0f;
    if (angle > 360.0f) angle -= 360.0f;

    glutPostRedisplay();
    glutTimerFunc(16, timer, 0); // ~60 FPS
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Bunter Würfel mit Indices");

    initGL();

    glutDisplayFunc(display);
    glutTimerFunc(0, timer, 0);

    glutMainLoop();
    return 0;
}