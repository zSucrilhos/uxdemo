#include <cstdlib>
#include <cstdio>
#include <cmath>

#include <error.h>

#include <ux/gl.h>
#include <ux/util.h>
#include <ux/shaders.h>
#include <ux/shapes.h>

const GLfloat sValues[] = {
    -0.5f, 0.5f, 0.0f, 1.0f,
    -0.5f, -0.5f, 0.0f, 1.0f,
    0.5f, 0.5f, 0.0f, 1.0f,
    0.5f, -0.5f, 0.0f, 1.0f,
    1.0f, 0.0f, 0.0f, 1.0f,
    0.0f, 1.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 1.0f, 1.0f,
    1.0f, 0.0f, 0.0f, 1.0f,
};

static GLuint sProgram;
static GLuint sLocPosition;
static GLuint sLocColor;
static GLuint sValuesBuffer;

void init() {
    std::string vertexShaderSource = readFile("shaders/main.vsh");
    std::string fragmentShaderSource = readFile("shaders/main.fsh");

    GLuint vertexShader = CreateShader(GL_VERTEX_SHADER, vertexShaderSource);
    GLuint fragmentShader = CreateShader(GL_FRAGMENT_SHADER, fragmentShaderSource);
    sProgram = CreateProgram(vertexShader, fragmentShader);

    sLocPosition = glGetAttribLocation(sProgram, "position");
    sLocColor = glGetAttribLocation(sProgram, "color");

    glGenBuffers(1, &sValuesBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, sValuesBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(sValues), sValues, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glEnable( GL_LINE_SMOOTH );
    glEnable( GL_POLYGON_SMOOTH );
    glHint( GL_LINE_SMOOTH_HINT, GL_NICEST );
    glHint( GL_POLYGON_SMOOTH_HINT, GL_NICEST );
}

void GLUT_display() {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(sProgram);

    glBindBuffer(GL_ARRAY_BUFFER, sValuesBuffer);
    glEnableVertexAttribArray(sLocPosition);
    glVertexAttribPointer(sLocPosition, 4, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(sLocColor);
    glVertexAttribPointer(sLocColor, 4, GL_FLOAT, GL_FALSE, 0, (void *)64);

    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    for (GLenum err = glGetError(); err != GL_NO_ERROR; err = glGetError()) {
        fprintf(stderr, "%d: %s\n", err, gluErrorString(err));
    }

    glDisableVertexAttribArray(sLocPosition);
    glDisableVertexAttribArray(sLocColor);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glUseProgram(0);

    glutSwapBuffers();
}

void GLUT_reshape(int w, int h) {
    glViewport(0, 0, w, h);
    if(w > h) {
        glm::mat4 projectionMatrix = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, 1.0f, -1.0f);
    }
}


int main(int argc, char *argv[]) {

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_ALPHA | GLUT_DEPTH | GLUT_STENCIL);
    // glutInitWindowSize(800, 2560);
    // glutInitWindowPosition(200, 100);
    glutCreateWindow(argv[0]);
    glutFullScreen();

    glutDisplayFunc(GLUT_display);
    glutReshapeFunc(GLUT_reshape);

    init();
    glutMainLoop();

    return 0;
}

