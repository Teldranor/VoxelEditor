//graphic interface
#include "libG.h"

//my header
#include "Shader.h"
#include "BasicCube.h"
#include "BasicColorCube.h"

//std
#include <stdio.h>

int main( int argc, char * argv[] )
{
    SDL_Init( SDL_INIT_VIDEO );
    SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );
    SDL_GL_SetAttribute( SDL_GL_ACCELERATED_VISUAL, 1 );
    SDL_GL_SetAttribute( SDL_GL_RED_SIZE, 8 );
    SDL_GL_SetAttribute( SDL_GL_GREEN_SIZE, 8 );
    SDL_GL_SetAttribute( SDL_GL_BLUE_SIZE, 8 );
    SDL_GL_SetAttribute( SDL_GL_ALPHA_SIZE, 8 );

    SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, 3 );
    SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, 2 );
    SDL_GL_SetAttribute( SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE );

    static const int width = 800;
    static const int height = 600;

    SDL_Window * window = SDL_CreateWindow( "Test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN );
    SDL_GLContext context = SDL_GL_CreateContext( window );

    Shader myShader("Shader/shader.vs", "Shader/shader.fs");
    Shader myCubeShader("Shader/cubeShader.vs", "Shader/cubeShader.fs");
    Shader myColorCubeShader("Shader/colorCubeShader.vs", "Shader/colorCubeShader.fs");

    glEnable( GL_DEPTH_TEST );
    glClearColor( 0.5, 0.0, 0.0, 0.0 );
    glViewport( 0, 0, width, height );

    BasicCube cube;
    cube.setColor(0.5f, 0.5f, 1.0f, 1.0f);

    BasicColorCube colorCube;
    /*
    GLuint vao, vbo, vertexColor;

    glGenVertexArrays( 1, &vao );
    glGenBuffers( 1, &vbo );
    glBindVertexArray( vao );
    glBindBuffer( GL_ARRAY_BUFFER, vbo );

    float vertices[] = {
    0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,
    0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,
    -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,
    -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f
};

GLuint elements[] = {
0,1,2,
2,3,0
};

glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,sizeof(float)*6,0);
glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,sizeof(float)*6,(void*)(sizeof(float)*3));
glEnableVertexAttribArray(0);
glEnableVertexAttribArray(1);

glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
*/
int i = 0;
for( ;; )
{
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    SDL_Event event;
    while( SDL_PollEvent( &event ) ){
        switch( event.type ){
            case SDL_KEYUP:
            if( event.key.keysym.sym == SDLK_ESCAPE )
            return 0;
            break;
        }
    }

    //myShader.use();
    myCubeShader.use();
    myColorCubeShader.use();


    //glm::mat4 transform;
    //transform = glm::scale(transform, glm::vec3(1.0f, 1.0f, 1.0f));
    //transform = glm::rotate(transform, 45.0f, glm::vec3(0.0f, 0.0f, 1.0f));
    //transform = glm::translate(transform, glm::vec3(0.5f, 0.0f, 0.0f));
    //myShader.setUniformMatrix4Float("transform", transform);
    glm::mat4 model, view, projection;
    //model matrix
    i++;
    model = glm::rotate(model, (float)i*1.0f, glm::vec3(0.5f, 1.0f, 0.0f));
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
    projection = glm::perspective(60.0f, (float)(width / height), 0.1f, 100.0f);

    //myShader.setUniformMatrix4Float("model", model);
    //myShader.setUniformMatrix4Float("view", view);
    //myShader.setUniformMatrix4Float("projection", projection);

    myCubeShader.setUniformMatrix4Float("model", model);
    myCubeShader.setUniformMatrix4Float("view", view);
    myCubeShader.setUniformMatrix4Float("projection", projection);

    myColorCubeShader.setUniformMatrix4Float("model", model);
    myColorCubeShader.setUniformMatrix4Float("view", view);
    myColorCubeShader.setUniformMatrix4Float("projection", projection);

    //draw
    //glBindVertexArray( vao );
    //glDrawArrays( GL_TRIANGLE_FAN, 0, 4 );
    //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, elements);
    //myCubeShader.setUniform4Float("cubeColor", cube.getColor_R(), cube.getColor_G(), cube.getColor_B(), cube.getColor_A());
    //cube.draw();
    colorCube.draw();

    SDL_GL_SwapWindow( window );
    SDL_Delay( 10 );
}

SDL_GL_DeleteContext( context );
SDL_DestroyWindow( window );
SDL_Quit();

return 0;
}
