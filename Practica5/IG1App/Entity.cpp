#include <iostream>
#include "Entity.h"
#include "IG1App.h"

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


/* ---------------------ENTITY WITH COLORS--------------------- */

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


/* ---------------------SINGLE COLOR ENTITY--------------------- */

SingleColorEntity::SingleColorEntity(const glm::vec4& color)
	: mColor(color)
{
	mShader = Shader::get("simple_light");
}

void
SingleColorEntity::render(mat4 const& modelViewMat) const
{
	if (mMesh != nullptr) {
		mat4 aMat = modelViewMat * mModelMat; // glm matrix multiplication

		mShader->use();
		mShader->setUniform("color", (glm::vec4)mColor);
		mShader->setUniform("lightDir", glm::vec4(modelViewMat * vec4(-1, -1, -1, 0)));
		upload(aMat);

		mMesh->render();
	}
}

glm::vec4 SingleColorEntity::getColor() const {
	return mColor;
}

void SingleColorEntity::setColor(const glm::vec4& color) {
	mColor = color;
}


/* ---------------------ENTITY WITH TEXTURE--------------------- */

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


/* ---------------------COMPOUND ENTITY--------------------- */

CompoundEntity::~CompoundEntity()
{
	for (Abs_Entity* el : gObjects)
		delete el;
}

void CompoundEntity::render(const glm::mat4& modelViewMat) const
{
	/*
	* Se multiplica la matriz modelViewMat recibida por la matriz de modelado que la entidad compuesta
	* tiene por ser una entidad
	*/
	mat4 aMat = modelViewMat * mModelMat;

	for (Abs_Entity* e : gObjects)
		e->render(aMat);
}

void CompoundEntity::load()
{
	for (Abs_Entity* obj : gObjects)
		obj->load();
}

void CompoundEntity::unload()
{
	for (Abs_Entity* obj : gObjects)
		obj->unload();
}

void CompoundEntity::addEntity(Abs_Entity* ae)
{
	gObjects.push_back(ae);
}


/* ---------------------ENTITY WITH MATERIAL--------------------- */

EntityWithMaterial::EntityWithMaterial(const glm::vec4& color)
	: SingleColorEntity(color)
	, mMaterial(color)
{
	mShader = Shader::get("light");
}

void EntityWithMaterial::render(const glm::mat4& modelViewMat) const
{
	if (mMesh != nullptr)
	{
		mat4 aMat = modelViewMat * mModelMat; // glm matrix multiplication

		assert(mShader == Shader::get("light"));
		mShader->use();
		upload(aMat); // = mShader->setUniform("modelView", aMat);
		mMaterial.upload(*mShader);

		mMesh->render();
	}

	if (mShowNormals)
	{
		renderNormals(modelViewMat);
	}
}

void EntityWithMaterial::toggleShowNormals()
{
	mShowNormals = !mShowNormals;
}

void EntityWithMaterial::renderNormals(const glm::mat4& modelViewMat) const
{
	mat4 aMat = modelViewMat * mModelMat; // glm matrix multiplication

	Shader* nShader = Shader::get("normals");
	nShader->use();
	nShader->setUniform("modelView", aMat);

	mMesh->render();
}


/* ---------------------COLOR MATERIAL ENTITY--------------------- */

// Subclase trivial = sin nada
ColorMaterialEntity::ColorMaterialEntity(const glm::vec4& color)
	: EntityWithMaterial(color)
{
}
