#define _CRT_SECURE_NO_WARNINGS
#define MAP_SIZE 10.f


#include "shader.h"
#include "load_OBJ.h"

Objectload Cube_Load;
GLint Cube = Cube_Load.loadObj("car1.obj");

void initTextures() {

    Cube_Load.InitTexture("Car_TEX.jpg");

}

GLuint VAO_Cube, VBO_Cube_VERTEX, VBO_Cube_NORMAL, VBO_Cube_UV;
GLuint VAO_Cone, VBO_Cone_VERTEX, VBO_Cone_NORMAL, VBO_Cone_UV;

int timer{ 0 };



int dicePyramidToggle = 0;
bool rotateXOn = false;
bool rotateYOn = false;
float rotateX = 0.f;
float rotateY = 0.f;


void InitBuffer() {

    //cube
    glGenVertexArrays(1, &VAO_Cube);
    glBindVertexArray(VAO_Cube);
    //vertex
    glGenBuffers(1, &VBO_Cube_VERTEX);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_Cube_VERTEX);
    glBufferData(GL_ARRAY_BUFFER, Cube_Load.outvertex.size() * sizeof(glm::vec3), &Cube_Load.outvertex[0], GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
    glEnableVertexAttribArray(0);
    //normal
    glGenBuffers(1, &VBO_Cube_NORMAL);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_Cube_NORMAL);
    glBufferData(GL_ARRAY_BUFFER, Cube_Load.outnormal.size() * sizeof(glm::vec3), &Cube_Load.outnormal[0], GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
    glEnableVertexAttribArray(1);
    //uv
    glGenBuffers(1, &VBO_Cube_UV);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_Cube_UV);
    glBufferData(GL_ARRAY_BUFFER, Cube_Load.outuv.size() * sizeof(glm::vec2), &Cube_Load.outuv[0], GL_STATIC_DRAW);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);
    glEnableVertexAttribArray(2);

   
}


GLvoid drawScene();
GLvoid KeyBoard(unsigned char key, int x, int y);
GLvoid Reshape(int w, int h);
GLvoid TimerFunc(int x);

int main(int argc, char** argv)
{
    srand(time(NULL));
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(800, 800);
    glutCreateWindow("Example1");

    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
    {
        std::cerr << "Unable to initialize GLEW" << std::endl;
        exit(EXIT_FAILURE);
    }
    else
        std::cout << "GLEW Initialized\n";

    InitBuffer();
    initTextures();
    shaderID.makeShader("vertexShaderSource.glsl", "fragmentShaderSource.glsl");
    glutKeyboardFunc(KeyBoard);
    glutTimerFunc(10, TimerFunc, 0);
    glutDisplayFunc(drawScene);
    glutReshapeFunc(Reshape);
    glutMainLoop();
}
float objectPositionX = 0.0f;  // Initial position of the object
float objectSpeed = 0.01f;

GLvoid drawScene()
{
    shaderID.use();
    glBindVertexArray(VAO_Cube);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);


    //조명
    shaderID.setVec3("lightPos", 0.f, 3.f, 0.f);
    shaderID.setVec3("lightColor", 3.f, 3.f, 3.f);

    //투영 변환
    glm::mat4 pTransform = glm::mat4(1.0f);
    pTransform = glm::perspective(glm::radians(45.0f), 1.0f, 0.1f, 50.0f);
    shaderID.setMat4("projectionTransform", pTransform);


    glm::mat4 vTransform = glm::mat4(1.0f);
    glm::vec3 cameraPos = glm::vec3(0, 1.f, 1.f);
    glm::vec3 cameraDirection = glm::vec3(0, 0.0f, 0);
    glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
    vTransform = glm::lookAt(cameraPos, cameraDirection, cameraUp);
    shaderID.setMat4("viewTransform", vTransform);
    shaderID.setVec3("viewPos", 0, 0, 0);



    if (dicePyramidToggle == 0) {
        // Update object position
        objectPositionX += objectSpeed;

        // Wrap the object around when it goes beyond the screen
        if (objectPositionX > MAP_SIZE) {
            objectPositionX = -MAP_SIZE;
        }

        glBindTexture(GL_TEXTURE_2D, Cube_Load.texture);
        glBindVertexArray(VAO_Cube);
        glm::mat4 PlayerTransform = glm::mat4(1.0f);
        PlayerTransform = glm::translate(PlayerTransform, glm::vec3(-objectPositionX, 0.0f, 0.0f));  // Translate object
        PlayerTransform = glm::rotate(PlayerTransform, glm::radians(90.0f), glm::vec3(0, 1, 0));
        PlayerTransform = glm::scale(PlayerTransform, glm::vec3(0.005f, 0.005f, 0.005f));
        PlayerTransform = glm::rotate(PlayerTransform, glm::radians(rotateX), glm::vec3(1, 0, 0));
        PlayerTransform = glm::rotate(PlayerTransform, glm::radians(rotateY), glm::vec3(0, 1, 0));
        shaderID.setMat4("modelTransform", PlayerTransform);
        shaderID.setVec3("objectColor", 1.f, 1.f, 1.f);
        glDrawArrays(GL_TRIANGLES, 0, Cube);
    }

    glutSwapBuffers();
}
GLvoid Reshape(int w, int h)
{
    glViewport(0, 0, w, h);
}

GLvoid KeyBoard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'p':
        dicePyramidToggle = 0;
        break;
    case 'c':
        dicePyramidToggle = 1;
        break;
    case 'x':
        rotateXOn = !rotateXOn;
        break;
    case 'y':
        rotateYOn = !rotateYOn;
        break;
    case 'q':
        exit(-1);
    }
    glutPostRedisplay();
}

GLvoid TimerFunc(int x)
{
    switch (x)
    {
    case 0:
        if (rotateXOn) {
            rotateX += 0.5;
        }
        if (rotateYOn) {
            rotateY += 0.5;
        }
        break;
    }
    glutTimerFunc(10, TimerFunc, 0);
    glutPostRedisplay();
}