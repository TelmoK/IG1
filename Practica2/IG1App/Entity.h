#ifndef _H_Entities_H_
#define _H_Entities_H_

#include <GL/glew.h>
#include <glm/glm.hpp>

#include "Mesh.h"
#include "Shader.h"
#include "Texture.h"

class Abs_Entity // abstract class
{
public:
	Abs_Entity()
	  : mModelMat(1.0)  // 4x4 identity matrix
	  , mShader(nullptr) 
	  , mWorldPosition({0, 0, 0}) {};
	virtual ~Abs_Entity();

	Abs_Entity(const Abs_Entity& e) = delete;            // no copy constructor
	Abs_Entity& operator=(const Abs_Entity& e) = delete; // no copy assignment

	virtual void render(const glm::mat4& modelViewMat) const = 0; // abstract method
	virtual void update() {};

	// modeling matrix
	glm::mat4 const& modelMat() const { return mModelMat; };
	void setModelMat(glm::mat4 const& aMat) { mModelMat = aMat; };

	// position modification
	glm::vec3 getWPos();
	void setWPos(glm::vec3 position);

	// load or unload entity data into the GPU
	void load();
	void unload();

protected:
	Mesh* mMesh = nullptr; // the mesh
	glm::mat4 mModelMat;  // modeling matrix
	Shader* mShader; // shader

	glm::vec3 mWorldPosition; // position with axis as origin

	// transfers modelViewMat to the GPU
	virtual void upload(const glm::mat4& mModelViewMat) const;
};

class EntityWithColors : public Abs_Entity
{
public:
	explicit EntityWithColors();
	void render(const glm::mat4& modelViewMat) const override;
};

class RGBAxes : public EntityWithColors
{
public:
	explicit RGBAxes(GLdouble l);
};

// Añadidos >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

class SingleColorEntity : public Abs_Entity // Apartado 3
{
	glm::dvec4 mColor;

public:
	explicit SingleColorEntity(const glm::dvec4& color = glm::dvec4(1));
	void render(const glm::mat4& modelViewMat) const override;
	glm::dvec4 getColor() const;
	void setColor(const glm::dvec4& color);
};

class RegularPolygon : public SingleColorEntity // Apartado 4
{
public:
	explicit RegularPolygon(GLuint num, GLdouble r, const glm::dvec4& color);
};

class RGBTriangle : public EntityWithColors // Apartado 6
{
public:
	explicit RGBTriangle(GLdouble r);
	void render(const glm::mat4& modelViewMat) const override;
	void update() override;
private:
	GLdouble orbit_angle = 0.0f;
};

class RGBRectangle : public EntityWithColors // Apartado 8
{
public:
	explicit RGBRectangle(GLdouble w, GLdouble h);
	void render(const glm::mat4& modelViewMat) const override;
};

class Cube : public SingleColorEntity
{
public:
	explicit Cube(GLdouble length);
	void render(const glm::mat4& modelViewMat) const override;
};

class RGBCube : public EntityWithColors
{
public:
	explicit RGBCube(GLdouble length);
	void render(const glm::mat4& modelViewMat) const override;
};

class Ground : public EntityWithColors
{
public:
	explicit Ground(GLdouble w, GLdouble h);

};

class EntityWithTexture : public Abs_Entity
{
public:
	explicit EntityWithTexture(Texture* texture);
	void render(const glm::mat4& modelViewMat) const override;

protected:
	Texture* mTexture = nullptr;
	bool mModulate = false;
};

#endif //_H_Entities_H_
