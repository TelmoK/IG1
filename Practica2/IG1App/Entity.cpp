#include <iostream>
#include "Entity.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace glm;

void
Abs_Entity::upload(const mat4& modelViewMat) const
{
	mShader->setUniform("modelView", modelViewMat);
}

Abs_Entity::~Abs_Entity()
{
	delete mMesh;
	mMesh = nullptr;
}

void
Abs_Entity::load()
{
	mMesh->load();
}

void
Abs_Entity::unload()
{
	mMesh->unload();
}

glm::vec3 
Abs_Entity::getWPos()
{
	return mWorldPosition;
}

void 
Abs_Entity::setWPos(glm::vec3 position)
{
	setModelMat(glm::translate(modelMat(), -mWorldPosition));
	mWorldPosition = position;
	setModelMat(glm::translate(modelMat(), mWorldPosition));
}

EntityWithColors::EntityWithColors()
{
	mShader = Shader::get("vcolors");
}

void
EntityWithColors::render(mat4 const& modelViewMat) const
{
	if (mMesh != nullptr) {
		mat4 aMat = modelViewMat * mModelMat; // glm matrix multiplication
		mShader->use();
		upload(aMat);
		mMesh->render();
	}
}

RGBAxes::RGBAxes(GLdouble l)
{
	mShader = Shader::get("vcolors");
	mMesh = Mesh::createRGBAxes(l);
}

// A�adidos >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

SingleColorEntity::SingleColorEntity(const dvec4& color)
	: mColor(color)
{
	mShader = Shader::get("simple");
}

void
SingleColorEntity::render(mat4 const& modelViewMat) const
{
	if (mMesh != nullptr) {
		mat4 aMat = modelViewMat * mModelMat; // glm matrix multiplication
		
		mShader->use();
		mShader->setUniform("color", (glm::vec4)mColor);
		upload(aMat);
		mMesh->render();
	}
}

glm::dvec4 SingleColorEntity::getColor() const {
	return mColor;
}

void SingleColorEntity::setColor(const glm::dvec4& color) {
	mColor = color;
}


RegularPolygon::RegularPolygon(GLuint num, GLdouble r, const glm::dvec4& color) 
	: SingleColorEntity(color)
{
	mMesh = Mesh::generateRegularPolygon(num, r);
}

RGBTriangle::RGBTriangle(GLdouble r)
	: EntityWithColors()
{
	constexpr int num = 3;

	mMesh = Mesh::createRGBTriangle(r);
}

void
RGBTriangle::render(mat4 const& modelViewMat) const
{
	if (mMesh != nullptr) {
		mat4 aMat = modelViewMat * mModelMat; // glm matrix multiplication
		mShader->use();
		upload(aMat);

		glEnable(GL_CULL_FACE); // Activa el renderizado solo para las caras visibles para la c�mara

		glCullFace(GL_BACK); // Tambi�n se puede hacer: glFrontFace(GL_CCW);  
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		mMesh->render();

		glCullFace(GL_FRONT); // Tambi�n se puede hacer: glFrontFace(GL_CW);
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		mMesh->render();

		glDisable(GL_CULL_FACE);

	}
}

void
RGBTriangle::update()
{
	setWPos({0,0,0});
	setModelMat(glm::rotate(modelMat(), radians(-5.0f), vec3(0, 0, 1)));

	setWPos({glm::cos(orbit_angle)*100, glm::sin(orbit_angle) * 100, 0});
	orbit_angle += 0.2;
	
}

RGBRectangle::RGBRectangle(GLdouble w, GLdouble h)
{
	mMesh = Mesh::generateRGBRectangle(w, h);
}

void
RGBRectangle::render(mat4 const& modelViewMat) const
{
	if (mMesh != nullptr) {
		mat4 aMat = modelViewMat * mModelMat; // glm matrix multiplication
		mShader->use();
		upload(aMat);

		glEnable(GL_CULL_FACE); // Activa el renderizado solo para las caras visibles para la c�mara

		glCullFace(GL_BACK); // Tambi�n se puede hacer: glFrontFace(GL_CCW); 
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		mMesh->render();

		glCullFace(GL_FRONT); // Tambi�n se puede hacer: glFrontFace(GL_CW); 
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		mMesh->render();

		glDisable(GL_CULL_FACE);

	}
}

Cube::Cube(GLdouble length)
{
	mMesh = Mesh::generateCube(length);
}

void
Cube::render(mat4 const& modelViewMat) const
{
	if (mMesh != nullptr) {
		mat4 aMat = modelViewMat * mModelMat; // glm matrix multiplication
		mShader->use();
		upload(aMat);

		glEnable(GL_CULL_FACE); // Activa el renderizado solo para las caras visibles para la c�mara

		glCullFace(GL_FRONT); // Tambi�n se puede hacer: glFrontFace(GL_CCW); 
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		mMesh->render();

		glCullFace(GL_BACK); // Tambi�n se puede hacer: glFrontFace(GL_CW); 
		glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
		mMesh->render();

		glDisable(GL_CULL_FACE);

	}
}

RGBCube::RGBCube(GLdouble length)
{
	mMesh = Mesh::generateRGBCubeTriangles(length);
}

void
RGBCube::render(mat4 const& modelViewMat) const
{
	if (mMesh != nullptr) {
		mat4 aMat = modelViewMat * mModelMat; // glm matrix multiplication
		mShader->use();
		upload(aMat);

		glEnable(GL_CULL_FACE); // Activa el renderizado solo para las caras visibles para la c�mara

		glCullFace(GL_FRONT); // Tambi�n se puede hacer: glFrontFace(GL_CCW); 
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		mMesh->render();

		glCullFace(GL_BACK); // Tambi�n se puede hacer: glFrontFace(GL_CW); 
		glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
		mMesh->render();

		glDisable(GL_CULL_FACE);

	}
}

EntityWithTexture::EntityWithTexture(Texture* texture, bool modulate) : mModulate(modulate)
{
	mShader = Shader::get("texture");
	setTexture(texture);
}

void EntityWithTexture::render(const glm::mat4& modelViewMat) const
{
	if (mMesh != nullptr) {
		mat4 aMat = modelViewMat * mModelMat; // glm matrix multiplication
		mShader->use();

		mShader->setUniform("modulate", mModulate);
		upload(aMat);

		if (mTexture != nullptr) mTexture->bind();

		mMesh->render();

		if (mTexture != nullptr) mTexture->unbind();
	}
}

Ground::Ground(Texture* texture, bool modulate, GLdouble w, GLdouble h) : EntityWithTexture(texture, modulate)
{
	mMesh = Mesh::generateRectangleTexCor(w, h, 4, 4);
	setModelMat(glm::rotate(modelMat(), radians(90.0f), vec3(1, 0, 0)));

}

void Ground::render(const glm::mat4& modelViewMat) const
{
	EntityWithTexture::render(modelViewMat);
}

BoxOutline::BoxOutline(Texture* texture, Texture* iteriorTexture, bool modulate, GLdouble length) 
	: EntityWithTexture(texture, modulate), mIteriorTexture(iteriorTexture)
{
	mMesh = Mesh::generateBoxOutlineTexCor(length);
}

void BoxOutline::render(const glm::mat4& modelViewMat) const
{
	if (mMesh != nullptr) {
		mat4 aMat = modelViewMat * mModelMat; // glm matrix multiplication
		mShader->use();

		glEnable(GL_CULL_FACE); // Activa el renderizado solo para las caras visibles para la c�mara

		mShader->setUniform("modulate", mModulate);
		upload(aMat);

		if (mTexture != nullptr) mTexture->bind();
		
		glCullFace(GL_FRONT); // Tambi�n se puede hacer: glFrontFace(GL_CCW); 
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		mMesh->render();

		if (mTexture != nullptr) mTexture->unbind();

		if (mIteriorTexture != nullptr) mIteriorTexture->bind();
		
		glCullFace(GL_BACK); // Tambi�n se puede hacer: glFrontFace(GL_CW); 
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		mMesh->render();
		
		if (mIteriorTexture != nullptr) mIteriorTexture->unbind();

		glDisable(GL_CULL_FACE);

	}
}

Star3D::Star3D(Texture* texture, bool modulate, GLdouble re, GLuint np, GLdouble h)
	: EntityWithTexture(texture, modulate)
{
	mMesh = Mesh::generateStar3DTexCor(re, np, h);
}

void
Star3D::render(mat4 const& modelViewMat) const
{
	if (mMesh != nullptr) {
		mat4 aMat = modelViewMat * mModelMat; // glm matrix multiplication
		mShader->use();
		mShader->setUniform("modulate", mModulate);

		upload(aMat);

		if (mTexture != nullptr) mTexture->bind();
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		mMesh->render();
		if (mTexture != nullptr) mTexture->unbind();

		aMat = glm::scale(aMat, vec3(1, 1, -1));
		upload(aMat);

		if (mTexture != nullptr) mTexture->bind();
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		mMesh->render();
		if (mTexture != nullptr) mTexture->unbind();
	}
}

void Star3D::update()
{
	setModelMat(glm::rotate(modelMat(), 0.1f, vec3(0, 0, 1)));
}

GlassParapet::GlassParapet(Texture* texture, bool modulate, GLdouble length)
	: EntityWithTexture(texture, modulate)
{
	mMesh = Mesh::generateBoxOutlineTexCor(length);
}

void GlassParapet::render(const glm::mat4& modelViewMat) const
{
	if (mMesh != nullptr) {
		mat4 aMat = modelViewMat * mModelMat; // glm matrix multiplication
		mShader->use();

		mShader->setUniform("modulate", mModulate);
		upload(aMat);

		glDepthMask(GL_FALSE);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		if (mTexture != nullptr) mTexture->bind();

		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		mMesh->render();

		if (mTexture != nullptr) mTexture->unbind();

		glDepthMask(GL_TRUE);
		glDisable(GL_BLEND);
	}
}

Photo::Photo(Texture* texture, bool modulate, GLdouble w, GLdouble h)
	: EntityWithTexture(texture, modulate)
{
	mMesh = Mesh::generateRectangleTexCor(w, h, 1, 1);
}

void Photo::render(const glm::mat4& modelViewMat) const
{
	if (mMesh != nullptr) {
		mat4 aMat = modelViewMat * mModelMat; // glm matrix multiplication
		mShader->use();
		mShader->setUniform("modulate", mModulate);

		upload(aMat);

		if (mTexture != nullptr) mTexture->bind();
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		mMesh->render();
		if (mTexture != nullptr) mTexture->unbind();
	}
}

void Photo::update()
{
	mTexture->loadColorBuffer(300, 300);
}
