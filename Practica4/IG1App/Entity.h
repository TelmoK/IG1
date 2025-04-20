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

	void setTexture(Texture* tex) { mTexture = tex; }

	// load or unload entity data into the GPU
	void load();
	void unload();

protected:
	Mesh* mMesh = nullptr; // the mesh
	glm::mat4 mModelMat;  // modeling matrix
	Shader* mShader; // shader
	Texture* mTexture = nullptr;

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

// A�adidos >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

class SingleColorEntity : public Abs_Entity // Apartado 3
{
protected:
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

class EntityWithTexture : public Abs_Entity
{
public:
	explicit EntityWithTexture(Texture* texture, bool modulate);
	void render(const glm::mat4& modelViewMat) const override;

protected:
	bool mModulate = false;
};

class Ground : public EntityWithTexture
{
public:
	explicit Ground(Texture* texture, bool modulate, GLdouble w, GLdouble h, GLuint rw, GLuint rh);
	void render(const glm::mat4& modelViewMat) const override;
};

class BoxOutline : public EntityWithTexture
{
public:

	explicit BoxOutline(Texture* texture, Texture* iteriorTexture, bool modulate, GLdouble length);
	void render(const glm::mat4& modelViewMat) const override;

protected:

	Texture* mIteriorTexture;
};

class Star3D : public EntityWithTexture
{
public:
	explicit Star3D(Texture* texture, bool modulate, GLdouble re, GLuint np, GLdouble h);
	void render(const glm::mat4& modelViewMat) const override;
	void update() override;
};

class GlassParapet : public EntityWithTexture
{
public:
	explicit GlassParapet(Texture* texture, bool modulate, GLdouble length);
	void render(const glm::mat4& modelViewMat) const override;
};

class Photo : public EntityWithTexture
{
public:
	explicit Photo(Texture* texture, bool modulate, GLdouble w, GLdouble h);
	void render(const glm::mat4& modelViewMat) const override;
	void update() override;
	void save(const std::string& name);
};

class BoxCover : public EntityWithTexture
{
public:
	explicit BoxCover(Texture* texture, Texture* iteriorTexture, bool modulate, GLdouble length);
	void render(const glm::mat4& modelViewMat) const override;
	void update() override;

protected:
	Texture* mIteriorTexture;
	GLdouble mLength;
	float mAngle;
	float mCurrAngle;
	float mRotSpeed;
};

class Grass : public EntityWithTexture
{
public:
	explicit Grass(Texture* texture, bool modulate, GLdouble w, GLdouble h);
	void render(const glm::mat4& modelViewMat) const override;
};

class Toros: public SingleColorEntity 
{
public:
	explicit Toros(GLdouble R, GLdouble r, GLuint nPoints = 40, GLuint nSamples = 40);
};

class ColorMaterialEntity : public SingleColorEntity
{
public:
	explicit ColorMaterialEntity(const glm::dvec4& color);
	void render(const glm::mat4& modelViewMat) const override;

	void toggleShowNormals();

private:
	bool mShowNormals = false;
};

class IndexedBox : public ColorMaterialEntity
{
public:
	explicit IndexedBox(const glm::dvec4& color = glm::dvec4(0, 1, 0, 1));
};

#endif //_H_Entities_H_
