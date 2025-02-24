#include "Mesh.h"

using namespace std;
using namespace glm;

// Placeholder for the pending index of a GPU object
constexpr GLuint NONE = numeric_limits<GLuint>::max();

Mesh::Mesh()
 : mVAO(NONE)
 , mVBO(NONE)
 , mCBO(NONE)
{
}

Mesh::~Mesh()
{
	unload();
}

void
Mesh::draw() const
{
	glDrawArrays(
	  mPrimitive,
	  0,
	  size()); // primitive graphic, first index and number of elements to be rendered
}

void
Mesh::load()
{
	assert(mVBO == NONE); // not already loaded

	if (vVertices.size() > 0) { // transfer data
		glGenBuffers(1, &mVBO);
		glGenVertexArrays(1, &mVAO);

		glBindVertexArray(mVAO);
		glBindBuffer(GL_ARRAY_BUFFER, mVBO);
		glBufferData(GL_ARRAY_BUFFER, vVertices.size() * sizeof(vec3), vVertices.data(), GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vec3), nullptr);
		glEnableVertexAttribArray(0);

		if (vColors.size() > 0) {             // upload colors
			glGenBuffers(1, &mCBO);

			glBindBuffer(GL_ARRAY_BUFFER, mCBO);
			glBufferData(GL_ARRAY_BUFFER, vColors.size() * sizeof(vec4), vColors.data(), GL_STATIC_DRAW);
			glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(vec4), nullptr);
			glEnableVertexAttribArray(1);
		}
	}

	if (vTexCoords.size() > 0) {
		glGenBuffers(1, &mTCO);
		glBindBuffer(GL_ARRAY_BUFFER, mTCO);
		glBufferData(GL_ARRAY_BUFFER,
			vTexCoords.size() * sizeof(vec2),
			vTexCoords.data(), GL_STATIC_DRAW);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE,
			sizeof(vec2), nullptr);
		glEnableVertexAttribArray(2);
	}
}

void
Mesh::unload()
{
	if (mVAO != NONE) {
		glDeleteVertexArrays(1, &mVAO);
		glDeleteBuffers(1, &mVBO);
		mVAO = NONE;
		mVBO = NONE;

		if (mCBO != NONE) {
			glDeleteBuffers(1, &mCBO);
			mCBO = NONE;
		}
	}

	if (mTCO != NONE) glDeleteBuffers(1, &mTCO);
}

void
Mesh::render() const
{
	assert(mVAO != NONE);

	glBindVertexArray(mVAO);
	draw();
}

Mesh*
Mesh::createRGBAxes(GLdouble l)
{
	Mesh* mesh = new Mesh();

	mesh->mPrimitive = GL_LINES;

	mesh->mNumVertices = 6;
	mesh->vVertices.reserve(mesh->mNumVertices);

	// X axis vertices
	mesh->vVertices.emplace_back(0.0, 0.0, 0.0);
	mesh->vVertices.emplace_back(l, 0.0, 0.0);
	// Y axis vertices
	mesh->vVertices.emplace_back(0, 0.0, 0.0);
	mesh->vVertices.emplace_back(0.0, l, 0.0);
	// Z axis vertices
	mesh->vVertices.emplace_back(0.0, 0.0, 0.0);
	mesh->vVertices.emplace_back(0.0, 0.0, l);

	mesh->vColors.reserve(mesh->mNumVertices);
	// X axis color: red  (Alpha = 1 : fully opaque)
	mesh->vColors.emplace_back(1.0, 0.0, 0.0, 1.0);
	mesh->vColors.emplace_back(1.0, 0.0, 0.0, 1.0);
	// Y axis color: green
	mesh->vColors.emplace_back(0.0, 1.0, 0.0, 1.0);
	mesh->vColors.emplace_back(0.0, 1.0, 0.0, 1.0);
	// Z axis color: blue
	mesh->vColors.emplace_back(0.0, 0.0, 1.0, 1.0);
	mesh->vColors.emplace_back(0.0, 0.0, 1.0, 1.0);

	return mesh;
}

Mesh* 
Mesh::generateRegularPolygon(GLuint num, GLdouble r)
{
	Mesh* mesh = new Mesh();

	mesh->mPrimitive = GL_LINE_LOOP;
	
	mesh->mNumVertices = num;

	mesh->vVertices.reserve(mesh->mNumVertices);

	constexpr double alpha = glm::radians(90.0);
	const double delta = glm::radians(360.0 / num);

	for (int i = 0; i < num; ++i)
	{
		mesh->vVertices.emplace_back(
			r * glm::cos(alpha + delta*i),
			r * glm::sin(alpha + delta * i),
			0.0);
	}

	return mesh;
}

Mesh*
Mesh::createRGBTriangle(GLdouble r)
{
	Mesh* mesh = new Mesh();

	mesh->mPrimitive = GL_TRIANGLES;

	constexpr int num = 3;
	mesh->mNumVertices = num;

	mesh->vVertices.reserve(mesh->mNumVertices);

	constexpr double alpha = glm::radians(90.0);
	const double delta = glm::radians(360.0 / num);

	for (int i = 0; i < num; ++i)
	{
		mesh->vVertices.emplace_back(
			r * glm::cos(alpha + delta * i),
			r * glm::sin(alpha + delta * i),
			0.0);
	}

	mesh->vColors.reserve(mesh->mNumVertices);
	// X axis color: red  (Alpha = 1 : fully opaque)
	mesh->vColors.emplace_back(1.0, 0.0, 0.0, 1.0);
	// Y axis color: green
	mesh->vColors.emplace_back(0.0, 1.0, 0.0, 1.0);
	// Z axis color: blue
	mesh->vColors.emplace_back(0.0, 0.0, 1.0, 1.0);

	return mesh;
}

Mesh* 
Mesh::generateRectangle(GLdouble w, GLdouble h)
{
	Mesh* mesh = new Mesh();

	mesh->mPrimitive = GL_TRIANGLE_STRIP;

	mesh->mNumVertices = 4;

	mesh->vVertices.reserve(mesh->mNumVertices);

	// Orden importante para añadir el color luego 
	// (en este caso los vértices hacen un zig-zag, es decir, una ´Z´)
	mesh->vVertices.emplace_back(-w/2,  h/2, 0.0);
	mesh->vVertices.emplace_back(-w/2, -h/2, 0.0);
	mesh->vVertices.emplace_back( w/2,  h/2, 0.0);
	mesh->vVertices.emplace_back( w/2, -h/2, 0.0);

	return mesh;
}

Mesh*
Mesh::generateRGBRectangle(GLdouble w, GLdouble h)
{
	Mesh* mesh = generateRectangle(w, h);

	mesh->vColors.reserve(mesh->mNumVertices);

	// X axis color: red
	mesh->vColors.emplace_back(1.0, 0.0, 0.0, 1.0);
	// Y axis color: green
	mesh->vColors.emplace_back(0.0, 1.0, 0.0, 1.0);
	// Y axis color: green
	mesh->vColors.emplace_back(0.0, 1.0, 0.0, 1.0);
	// Z axis color: blue
	mesh->vColors.emplace_back(0.0, 0.0, 1.0, 1.0);

	

	return mesh;
}

Mesh* 
Mesh::generateCube(GLdouble length)
{
	Mesh* mesh = new Mesh();

	mesh->mPrimitive = GL_TRIANGLES;

	mesh->mNumVertices = 36;

	mesh->vVertices.reserve(mesh->mNumVertices);

	// face1
	mesh->vVertices.emplace_back(length / 2, -length / 2, length / 2); // 0
	mesh->vVertices.emplace_back(length / 2, length / 2, length / 2); // 1
	mesh->vVertices.emplace_back(length / 2, -length / 2, -length / 2); // 2

	mesh->vVertices.emplace_back(length / 2, length / 2, length / 2); // 1
	mesh->vVertices.emplace_back(length / 2, length / 2, -length / 2); // 3
	mesh->vVertices.emplace_back(length / 2, -length / 2, -length / 2); // 2

	// face2
	mesh->vVertices.emplace_back(length / 2, length / 2, length / 2); // 1
	mesh->vVertices.emplace_back(-length / 2, length / 2, -length / 2); // 4
	mesh->vVertices.emplace_back(length / 2, length / 2, -length / 2); // 3

	mesh->vVertices.emplace_back(length / 2, length / 2, length / 2); // 1
	mesh->vVertices.emplace_back(-length / 2, length / 2, length / 2); // 6
	mesh->vVertices.emplace_back(-length / 2, length / 2, -length / 2); // 4

	// face3
	mesh->vVertices.emplace_back(length / 2, -length / 2, length / 2); // 0
	mesh->vVertices.emplace_back(-length / 2, -length / 2, length / 2); // 7
	mesh->vVertices.emplace_back(length / 2, length / 2, length / 2); // 1

	mesh->vVertices.emplace_back(length / 2, length / 2, length / 2); // 1
	mesh->vVertices.emplace_back(-length / 2, -length / 2, length / 2); // 7
	mesh->vVertices.emplace_back(-length / 2, length / 2, length / 2); // 6

	//face4
	mesh->vVertices.emplace_back(-length / 2, length / 2, length / 2); // 6
	mesh->vVertices.emplace_back(-length / 2, -length / 2, length / 2); // 7
	mesh->vVertices.emplace_back(-length / 2, -length / 2, -length / 2); // 5

	mesh->vVertices.emplace_back(-length / 2, length / 2, length / 2); // 6
	mesh->vVertices.emplace_back(-length / 2, -length / 2, -length / 2); // 5
	mesh->vVertices.emplace_back(-length / 2, length / 2, -length / 2); // 4

	//face5
	mesh->vVertices.emplace_back(-length / 2, -length / 2, length / 2); // 7
	mesh->vVertices.emplace_back(length / 2, -length / 2, length / 2); // 0
	mesh->vVertices.emplace_back(-length / 2, -length / 2, -length / 2); // 5

	mesh->vVertices.emplace_back(length / 2, -length / 2, length / 2); // 0
	mesh->vVertices.emplace_back(length / 2, -length / 2, -length / 2); // 2
	mesh->vVertices.emplace_back(-length / 2, -length / 2, -length / 2); // 5

	//face6
	mesh->vVertices.emplace_back(length / 2, length / 2, -length / 2); // 3
	mesh->vVertices.emplace_back(-length / 2, length / 2, -length / 2); // 4
	mesh->vVertices.emplace_back(-length / 2, -length / 2, -length / 2); // 5

	mesh->vVertices.emplace_back(-length / 2, -length / 2, -length / 2); // 5
	mesh->vVertices.emplace_back(length / 2, -length / 2, -length / 2); // 2
	mesh->vVertices.emplace_back(length / 2, length / 2, -length / 2); // 3

	return mesh;
}

Mesh*
Mesh::generateRGBCubeTriangles(GLdouble length)
{
	Mesh* mesh = generateCube(length);

	mesh->vColors.reserve(mesh->mNumVertices);

	for (int i = 0; i < mesh->mNumVertices; ++i) {
		if (i / 6 == 0 || i / 6 == 3) {
			mesh->vColors.emplace_back(0.0, 1.0, 0.0, 1.0);
		}
		else if (i / 6 == 1 || i / 6 == 4) {
			mesh->vColors.emplace_back(0.0, 0.0, 1.0, 1.0);
		}
		else mesh->vColors.emplace_back(1.0, 0.0, 0.0, 1.0);
		
	}
	
	return mesh;
}

Mesh* 
Mesh::generateRectangleTexCor(GLdouble w, GLdouble h, GLuint rw, GLuint rh)
{
	Mesh* mesh = generateRectangle(w * rw, h * rh);

	mesh->vTexCoords.reserve(4);
	
	mesh->vTexCoords.emplace_back(0.0, rh);
	mesh->vTexCoords.emplace_back(0.0, 0.0);
	mesh->vTexCoords.emplace_back(rw, rh);
	mesh->vTexCoords.emplace_back(rw, 0.0);

	return mesh;
}

Mesh* 
Mesh::generateBoxOutline(GLdouble length)
{
	Mesh* mesh = new Mesh();

	mesh->mPrimitive = GL_TRIANGLE_STRIP;

	mesh->mNumVertices = 10;

	mesh->vVertices.reserve(mesh->mNumVertices);

	// Se asignan en zig-zag
	mesh->vVertices.emplace_back(length / 2, -length / 2, -length / 2); // 0
	mesh->vVertices.emplace_back(length / 2, length / 2, -length / 2);  // 1
	mesh->vVertices.emplace_back(-length / 2, -length / 2, -length / 2);// 2
	mesh->vVertices.emplace_back(-length / 2, length / 2, -length / 2); // 3

	mesh->vVertices.emplace_back(-length / 2, -length / 2, length / 2); // 5
	mesh->vVertices.emplace_back(-length / 2, length / 2, length / 2);  // 6
	mesh->vVertices.emplace_back(length / 2, -length / 2, length / 2);  // 7
	mesh->vVertices.emplace_back(length / 2, length / 2, length / 2);   // 8

	mesh->vVertices.emplace_back(length / 2, -length / 2, -length / 2); // 0
	mesh->vVertices.emplace_back(length / 2, length / 2, -length / 2);  // 1

	return mesh;
}

Mesh* 
Mesh::generateBoxOutlineTexCor(GLdouble length)
{
	Mesh* mesh = generateBoxOutline(length);

	mesh->vTexCoords.reserve(10);

	mesh->vTexCoords.emplace_back(1.0, 0.0); // 0
	mesh->vTexCoords.emplace_back(1.0, 1.0);  // 1
	mesh->vTexCoords.emplace_back(0.0, 0.0); // 2
	mesh->vTexCoords.emplace_back(0.0, 1.0); // 3

	mesh->vTexCoords.emplace_back(1.0, 0.0); // 0
	mesh->vTexCoords.emplace_back(1.0, 1.0);  // 1
	mesh->vTexCoords.emplace_back(0.0, 0.0); // 2
	mesh->vTexCoords.emplace_back(0.0, 1.0); // 3

	mesh->vTexCoords.emplace_back(1.0, 0.0); // 0
	mesh->vTexCoords.emplace_back(1.0, 1.0);  // 1

	return mesh;
}