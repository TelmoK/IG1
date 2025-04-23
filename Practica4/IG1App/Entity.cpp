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

SingleColorEntity::SingleColorEntity(const glm::vec4& color)
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
		mShader->setUniform("modelView", aMat);
		mMesh->render();
	}
}

glm::vec4 SingleColorEntity::getColor() const {
	return mColor;
}

void SingleColorEntity::setColor(const glm::vec4& color) {
	mColor = color;
}


RegularPolygon::RegularPolygon(GLuint num, GLdouble r, const glm::vec4& color)
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
	setWPos({ 0,0,0 });
	setModelMat(glm::rotate(modelMat(), radians(-5.0f), vec3(0, 0, 1)));

	setWPos({ glm::cos(orbit_angle) * 200, glm::sin(orbit_angle) * 200, 0 });
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

		//Error anterior con los vértices en sentido horario:
		// glCullFace(GL_FRONT); // Tambi�n se puede hacer: glFrontFace(GL_CCW); 
		glCullFace(GL_BACK);
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		mMesh->render();

		//Error anterior con los vértices en sentido horario:
		//glCullFace(GL_BACK); // Tambi�n se puede hacer: glFrontFace(GL_CW); 
		glCullFace(GL_FRONT);
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

		//Error anterior con los vértices en sentido horario:
		// glCullFace(GL_FRONT); // Tambi�n se puede hacer: glFrontFace(GL_CCW); 
		glCullFace(GL_BACK);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		mMesh->render();

		//Error anterior con los vértices en sentido horario:
		//glCullFace(GL_BACK); // Tambi�n se puede hacer: glFrontFace(GL_CW); 
		glCullFace(GL_FRONT);
		glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
		mMesh->render();

		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // Reset to default orelse leaks to other scenes
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

Ground::Ground(Texture* texture, bool modulate, GLdouble w, GLdouble h, GLuint rw, GLuint rh) : EntityWithTexture(texture, modulate)
{
	mMesh = Mesh::generateRectangleTexCor(w, h, rw, rh);
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
	//setModelMat(glm::translate(glm::mat4(1), glm::vec3(0, length / 2, 100)));
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

		//Error anterior con los vértices en sentido horario:
		// glCullFace(GL_FRONT); // Tambi�n se puede hacer: glFrontFace(GL_CCW); 
		glCullFace(GL_BACK);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		mMesh->render();

		if (mTexture != nullptr) mTexture->unbind();

		if (mIteriorTexture != nullptr) mIteriorTexture->bind();

		//Error anterior con los vértices en sentido horario:
		//glCullFace(GL_BACK); // Tambi�n se puede hacer: glFrontFace(GL_CW); 
		glCullFace(GL_FRONT);
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
	setModelMat(glm::rotate(mat4(1), glm::radians(90.0f), vec3(1, 0, 0))); // gira 90 alrededor de x
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
	mTexture->loadColorBuffer(IG1App::s_ig1app.viewPort().width(), IG1App::s_ig1app.viewPort().height());
}

void Photo::save(const std::string& name)
{
	mTexture->save(name);
}

BoxCover::BoxCover(Texture* texture, Texture* iteriorTexture, bool modulate, GLdouble length)
	: EntityWithTexture(texture, modulate), mIteriorTexture(iteriorTexture), mLength(length)
{
	mMesh = Mesh::generateRectangleTexCor(length, length, 1, 1);

	mAngle = glm::radians(90.0f);
	mCurrAngle = mAngle;
	mRotSpeed = -0.01f;
}

void BoxCover::render(const glm::mat4& modelViewMat) const
{
	if (mMesh != nullptr) {
		mat4 aMat = modelViewMat * mModelMat; // glm matrix multiplication
		mShader->use();

		glEnable(GL_CULL_FACE); // Activa el renderizado solo para las caras visibles para la c�mara

		mShader->setUniform("modulate", mModulate);
		upload(aMat);

		if (mTexture != nullptr) mTexture->bind();

		//Error anterior con los vértices en sentido horario:
		// glCullFace(GL_FRONT); // Tambi�n se puede hacer: glFrontFace(GL_CCW); 
		glCullFace(GL_BACK);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		mMesh->render();

		if (mTexture != nullptr) mTexture->unbind();

		if (mIteriorTexture != nullptr) mIteriorTexture->bind();

		//Error anterior con los vértices en sentido horario:
		//glCullFace(GL_BACK); // Tambi�n se puede hacer: glFrontFace(GL_CW); 
		glCullFace(GL_FRONT);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		mMesh->render();

		if (mIteriorTexture != nullptr) mIteriorTexture->unbind();

		glDisable(GL_CULL_FACE);
	}
}

void BoxCover::update()
{
	if (mCurrAngle < -glm::pi<float>() / 4 || mCurrAngle > mAngle) {
		mRotSpeed = -mRotSpeed;
	}
	mCurrAngle += mRotSpeed;

	glm::mat4 trans1 = glm::translate(glm::mat4(1), glm::vec3(0, mLength / 2, 0)); // ajuste del pivot
	glm::mat4 rot = glm::rotate(glm::mat4(1), mCurrAngle, vec3(1, 0, 0)); // rota alrededor del pivot

	glm::mat4 trans2 = glm::translate(glm::mat4(1), mWorldPosition); // translada a la posicion final
	glm::mat4 trans3 = glm::translate(glm::mat4(1), glm::vec3(0, -mLength / 2, 0)); // vuelve ajuste del pivot

	setModelMat(trans3 * trans2 * rot * trans1);
}

Grass::Grass(Texture* texture, bool modulate, GLdouble w, GLdouble h)
	: EntityWithTexture(texture, modulate)
{
	mShader = Shader::get("texture:texture_alpha");
	mMesh = Mesh::generateRectangleTexCor(w, h, 1, 1);
}

void Grass::render(const glm::mat4& modelViewMat) const
{
	if (mMesh != nullptr) {
		mat4 aMat = modelViewMat * mModelMat; // glm matrix multiplication
		mShader->use();
		mShader->setUniform("modulate", mModulate);

		float alpha = 0;

		if (mTexture != nullptr) mTexture->bind();

		for (int i = 0; i < 3; ++i)
		{
			aMat = glm::rotate(aMat, alpha, glm::vec3(0, 1, 0));

			upload(aMat);

			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			mMesh->render();

			alpha += (glm::pi<float>() * 2) / 8;
		}

		if (mTexture != nullptr) mTexture->unbind();
	}
}

ColorMaterialEntity::ColorMaterialEntity(const glm::vec4& color)
	: SingleColorEntity(color)
{
	mShader = Shader::get("simple_light");
}

void ColorMaterialEntity::toggleShowNormals()
{
	mShowNormals = !mShowNormals;
}

void ColorMaterialEntity::render(const glm::mat4& modelViewMat) const
{
	SingleColorEntity::render(modelViewMat);

	if (mShowNormals && mMesh != nullptr)
	{
		mat4 aMat = modelViewMat * mModelMat; // glm matrix multiplication

		Shader* nShader = Shader::get("normals");
		nShader->use();
		nShader->setUniform("modelView", aMat);
		mMesh->render();

	}
}

Toros::Toros(GLdouble R, GLdouble r, GLuint nPoints, GLuint nSamples)
	: ColorMaterialEntity(glm::vec4(1, 0, 0, 1))
{
	std::vector<glm::vec2> profile(nPoints);

	double delta = 2 * glm::pi<double>() / nPoints;
	double teta = glm::pi<double>() / 2.0;

	for (int i = 0; i < nPoints; ++i) {
		profile[i] = { r * cos(teta) + R, r * sin(teta) };
		teta -= delta;
	}

	mMesh = IndexMesh::generateByRevolution(profile, nSamples, 2 * glm::pi<double>());
}

IndexedBox::IndexedBox(GLdouble length, const glm::vec4& color)
	: ColorMaterialEntity(color)
{
	mMesh = IndexMesh::generateIndexedBox(length);
}

Sphere::Sphere(GLdouble radius, GLuint nParallels, GLuint nMeridians, const glm::vec4& color)
	: ColorMaterialEntity(color)
{
	std::vector<glm::vec2> profile(nParallels);

	double delta = glm::pi<double>() / static_cast<double>(nParallels);
	double teta = glm::pi<double>() / 2.0;

	for (int i = 0; i < nParallels; ++i) {
		profile[i] = { radius * cos(teta), radius * sin(teta) };
		teta -= delta;
	}

	mMesh = IndexMesh::generateByRevolution(profile, nMeridians, 2 * glm::pi<double>());
}

Disk::Disk(GLdouble R, GLdouble r, GLuint nRings, GLuint nSamples, const glm::vec4& color)
	: ColorMaterialEntity(color)
{
	std::vector<glm::vec2> profile(nRings);

	double dist = (R - r) / nRings;

	for (int i = 0; i < nRings; ++i) {
		profile[i] = { r + i * dist, 0 };
	}

	mMesh = IndexMesh::generateByRevolution(profile, nSamples, 2 * glm::pi<double>());
}

Cone::Cone(GLdouble h, GLdouble r, GLdouble R, GLuint nRings, GLuint nSamples, const glm::vec4& color)
	: ColorMaterialEntity(color)
{
	int nVetexes = nRings + 2;
	// La R es la parte de arriba y la r la de abajo
	std::vector<glm::vec2> profile(nVetexes);

	profile[0] = { 0, 0 };

	double distX = (R - r) / nRings; // Orden de la resta importante
	double distY = h / (nRings - 1);

	for (int i = 0; i < nRings; ++i) {
		profile[i + 1] = { r + i * distX, i * distY };
	}

	profile[nVetexes - 1] = { 0, h };

	mMesh = IndexMesh::generateByRevolution(profile, nSamples, 2 * glm::pi<double>());
}

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

WingAdvancedTIE::WingAdvancedTIE()
	: EntityWithTexture(new Texture(), false)
{
	mMesh = Mesh::generateWingAdvancedTIE(80, 50);

	mTexture->load("../assets/images/noche.jpg", 122);
}

void WingAdvancedTIE::render(const glm::mat4& modelViewMat) const
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

TieFighter::TieFighter()
{
	addEntity(new Sphere(40, 30, 40, glm::vec4(0, 65, 106, 255)));

	Cone* wingConnector = new Cone(100, 5, 5, 30, 30, glm::vec4(0, 65, 106, 255));

	glm::mat4 rot = glm::rotate(glm::mat4(1), glm::radians(90.0f), vec3(1, 0, 0));
	glm::mat4 trans = glm::translate(glm::mat4(1), glm::vec3(0, 0, -50));

	wingConnector->setModelMat(trans * rot);

	addEntity(wingConnector);

	// Right Wing
	WingAdvancedTIE* rWing = new WingAdvancedTIE();
	rot = glm::rotate(modelMat(), glm::radians(180.0f), vec3(0, 1, 0));
	trans = glm::translate(glm::mat4(1), glm::vec3(0, 0, 15));

	rWing->setModelMat(trans * rot);

	addEntity(rWing);

	// Left Wing
	WingAdvancedTIE* lWing = new WingAdvancedTIE();
	trans = glm::translate(glm::mat4(1), glm::vec3(0, 0, -15));

	lWing->setModelMat(trans);

	addEntity(lWing);
}
