#include <stdio.h>
#include <stdlib.h>
#include <GL\glew.h>
#include <GL\glfw.h>

//bool topLeft = true;
//std::vector<GLubyte> indexVec;

class Test {
public:
	int test;
};

typedef struct {
	float XYZW[4];
	float RGBA[4];
} Vertex;

int WindowHandle = 0,
		CurrentWidth = 640,
		CurrentHeight = 480;

GLuint VertexShaderId,
			 FragmentShaderId,
			 ProgramId,
			 VaoId,
			 IndexBufferId,
			 VboId;

const GLcharARB* VertexShader = {
	"#version 400\n"\

	"layout(location=0) in vec4 in_Position;\n"\
	"layout(location=1) in vec4 in_Color;\n"\
	"out vec4 ex_Color;\n"\

	"void main(void) {\n"\
	"	gl_Position = in_Position;\n"\
	"	ex_Color = in_Color;\n"\
	"}\n"
};

const GLcharARB* FragmentShader = {
	"#version 400\n"\

	"in vec4 ex_Color;\n"\
	"out vec4 out_Color;\n"\

	"void main(void) {\n"\
	"	out_Color = ex_Color;\n"\
	"}\n"\
};

void CreateVBO() {
	Vertex Vertices[] =
    {
/*        { { -0.5f, 0.5f, 0.0f, 1.0f }, { 1.0f, 0.0f, 0.0f, 1.0f } },
        { { 0.0f,  0.5f, 0.0f, 1.0f }, { 0.0f, 1.0f, 0.0f, 1.0f } },
        { { -0.5f, -0.0f, 0.0f, 1.0f }, { 0.0f, 0.0f, 1.0f, 1.0f } },
        { { 0.0f, -0.0f, 0.0f, 1.0f }, { 1.0f, 1.0f, 1.0f, 1.0f } },
        { { 0.5f, 0.5f, 0.0f, 1.0f }, { 1.0f, 0.0f, 0.0f, 1.0f } },
        { {  0.5f,  -0.0f, 0.0f, 1.0f }, { 0.0f, 1.0f, 0.0f, 1.0f } },
        { { -0.1f, -0.8f, 0.0f, 1.0f }, { 0.0f, 0.0f, 1.0f, 1.0f } },
        { { 0.1f, -0.8f, 0.0f, 1.0f }, { 1.0f, 1.0f, 1.0f, 1.0f } }*/
        { { -0.5f, -0.5f, 0.0f, 1.0f }, { 1.0f, 0.0f, 0.0f, 1.0f } },
        { { -0.5f,  0.5f, 0.0f, 1.0f }, { 0.0f, 1.0f, 0.0f, 1.0f } },
        { { 0.5f, 0.5f, 0.0f, 1.0f }, { 0.0f, 0.0f, 1.0f, 1.0f } },
        { { 0.5f, -0.5f, 0.0f, 1.0f }, { 1.0f, 1.0f, 1.0f, 1.0f } },
        /*{ { 0.5f, 0.5f, 0.0f, 1.0f }, { 1.0f, 0.0f, 0.0f, 1.0f } },
        { {  0.5f,  -0.0f, 0.0f, 1.0f }, { 0.0f, 1.0f, 0.0f, 1.0f } },
        { { -0.1f, -0.8f, 0.0f, 1.0f }, { 0.0f, 0.0f, 1.0f, 1.0f } },
        { { 0.1f, -0.8f, 0.0f, 1.0f }, { 1.0f, 1.0f, 1.0f, 1.0f } }*/
    };

	GLubyte Indices[] = {
		0, 1, 2,
		2, 1, 3
		/*1, 3, 4,
		3, 4, 5*/
	};

	//GLubyte Indices[MAX_ROW];

	GLenum ErrorCheckValue = glGetError();
	const size_t BufferSize = sizeof(Vertices);
	const size_t VertexSize = sizeof(Vertices[0]);
	const size_t RGBOffset = sizeof(Vertices[0].XYZW);

	glGenBuffers(1, &VboId);

	glGenVertexArrays(1, &VaoId);
	glBindVertexArray(VaoId);

	glBindBuffer(GL_ARRAY_BUFFER, VboId);
	glBufferData(GL_ARRAY_BUFFER, BufferSize, Vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, VertexSize, 0);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, VertexSize, (GLvoid*)RGBOffset);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	// Pushing Indices 
	glGenBuffers(1, &IndexBufferId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IndexBufferId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indices), Indices, GL_STATIC_DRAW);

	ErrorCheckValue = glGetError();
	if (ErrorCheckValue != GL_NO_ERROR) {
		//fprintf(stderr, "ERROR: Could not create a VBO: %s \n", gluErrorString(ErrorCheckValue));

		exit(-1);
	}
}

void buildIndices() {
	//for (int i = 0; i < MAX_ROW; i+=2) {
		/*indexVec.push_back(i); indexVec.push_back(i+1); indexVec.push_back(i+2);
		indexVec.push_back(i+2); indexVec.push_back(i+1); indexVec.push_back(i+3);*/
	//}
}

void DestroyVBO() {
	GLenum ErrorCheckValue = glGetError();

	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glDeleteBuffers(1, &VboId);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glDeleteBuffers(1, &IndexBufferId);

	glBindVertexArray(0);
	glDeleteVertexArrays(1, &VaoId);

	ErrorCheckValue = glGetError();
	if (ErrorCheckValue != GL_NO_ERROR) {
		//fprintf(stderr, "ERROR: Could not destroy the VBO: %s \n", gluErrorString(ErrorCheckValue));

		exit(-1);
	}
}

void CreateShaders() {
	GLenum ErrorCheckValue = glGetError();

	VertexShaderId = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(VertexShaderId, 1, &VertexShader, NULL);
	glCompileShader(VertexShaderId);

	FragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(FragmentShaderId, 1, &FragmentShader, NULL);
	glCompileShader(FragmentShaderId);

	ProgramId = glCreateProgram();
		glAttachShader(ProgramId, VertexShaderId);
		glAttachShader(ProgramId, FragmentShaderId);
	glLinkProgram(ProgramId);
	glUseProgram(ProgramId);

	ErrorCheckValue = glGetError();
	if (ErrorCheckValue != GL_NO_ERROR) {
		//fprintf(stderr, "ERROR: Could not create the shaders: %s \n", gluErrorString(ErrorCheckValue));

		exit(-1);
	}
}

void DestroyShaders() {
	GLenum ErrorCheckValue = glGetError();

	glUseProgram(0);

	glDetachShader(ProgramId, VertexShaderId);
	glDetachShader(ProgramId, FragmentShaderId);

	glDeleteShader(FragmentShaderId);
	glDeleteShader(VertexShaderId);

	glDeleteProgram(ProgramId);

	ErrorCheckValue = glGetError();
	if (ErrorCheckValue != GL_NO_ERROR) {
		//fprintf(stderr, "ERROR: Could not destroy shaders: %s \n", gluErrorString(ErrorCheckValue));

		exit(-1);
	}
}

void ResizeFunction(int Width, int Height) {
	CurrentWidth = Width;
	CurrentHeight = Height;
	glViewport(0, 0, CurrentWidth, CurrentHeight);
}

void RenderFunction() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	glDrawElements(GL_TRIANGLE_STRIP, 6, GL_UNSIGNED_BYTE, (GLvoid*)0);

	glfwSwapBuffers();
	//glutPostRedisplay();
}

void Cleanup() {
	DestroyShaders();
	DestroyVBO();
	glfwCloseWindow();
}

void Initialize(int argc, char* argv[]) {
	GLenum GlewInitResult;

	glfwInit();

	glfwOpenWindow(640, 480, 24, 24, 24, 24, 24, 24, GLFW_WINDOW);

	glfwSetWindowSizeCallback(ResizeFunction);
	//glutDisplayFunc(RenderFunction);

	glewExperimental = GL_TRUE;
	GlewInitResult = glewInit();
	if (GLEW_OK != GlewInitResult) {
		//fprintf(stderr, "ERROR: %s\n", glewGetErrorString(GlewInitResult));
		exit(EXIT_FAILURE);
	}

	CreateShaders();
	CreateVBO();

	glClearColor(0, 0, 0, 0);
}

int main(int argc, char* argv[]) {
	int Running = GL_TRUE;

	Initialize(argc, argv);

	buildIndices();

	while (Running) 
		RenderFunction();

	Cleanup();

	glfwTerminate();
}