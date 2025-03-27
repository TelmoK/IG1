#include "Shader.h"
#include "Camera.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_access.hpp>

#include <iostream>


Camera::Camera(Viewport* vp)
	: mViewMat(1.0)
	, mProjMat(1.0)
	, xRight(vp->width() / 2.0)
	, xLeft(-xRight)
	, yTop(vp->height() / 2.0)
	, yBot(-yTop)
	, mViewPort(vp)
{
	setPM();
}

void
Camera::uploadVM() const
{
	Shader::setUniform4All("modelView", mViewMat);
}

void
Camera::setVM()
{
	mViewMat = glm::lookAt(mEye, mLook, mUp); // glm::lookAt defines the view matrix

	setAxes(); // Update the Axes based on the new Matrix
}

void
Camera::set2D()
{
	mEye = { 0, 0, 500 };
	mLook = { 0, 0, 0 };
	mUp = { 0, 1, 0 };
	setVM();
}

void
Camera::set3D()
{
	mEye = { 500, 500, 500 };
	mLook = { 0, 10, 0 };
	mUp = { 0, 1, 0 };
	setVM();
}

void
Camera::pitch(GLdouble a)
{
	mViewMat = glm::rotate(mViewMat, glm::radians(a), glm::dvec3(1.0, 0, 0));
	// glm::rotate returns mViewMat * rotationMatrix

	setAxes(); // Update the Axes based on the new Matrix
}

void
Camera::yaw(GLdouble a)
{
	mViewMat = glm::rotate(mViewMat, glm::radians(a), glm::dvec3(0, 1.0, 0));
	// glm::rotate returns mViewMat * rotationMatrix

	setAxes(); // Update the Axes based on the new Matrix
}

void
Camera::roll(GLdouble a)
{
	mViewMat = glm::rotate(mViewMat, glm::radians(a), glm::dvec3(0, 0, 1.0));
	// glm::rotate returns mViewMat * rotationMatrix

	setAxes(); // Update the Axes based on the new Matrix
}

void
Camera::setSize(GLdouble xw, GLdouble yh)
{
	xRight = xw / 2.0;
	xLeft = -xRight;
	yTop = yh / 2.0;
	yBot = -yTop;
	setPM();
}

void
Camera::setScale(GLdouble s)
{
	mScaleFact -= s;
	if (mScaleFact < 0)
		mScaleFact = 0.01;
	setPM();
}

void
Camera::setPM()
{
	if (bOrto) { //  if orthogonal projection
		mProjMat = glm::ortho(xLeft * mScaleFact,
			xRight * mScaleFact,
			yBot * mScaleFact,
			yTop * mScaleFact,
			mNearVal,
			mFarVal);
		// glm::ortho defines the orthogonal projection matrix
	}
	else {
		// Me gusta más esto: (también está en la diapositivas)
		double aspect = mViewPort->width() / (double)mViewPort->height();
		double fovy = glm::radians(60.0);
		mProjMat = glm::perspective(fovy, aspect, mNearVal, mFarVal);

		// Que esto: 
		//mProjMat = glm::frustum(xLeft, xRight,
		//	yBot, yTop,
		//	mNearVal, mFarVal);
	}
}

void
Camera::uploadPM() const
{
	Shader::setUniform4All("projection", mProjMat);
}

void
Camera::upload() const
{
	mViewPort->upload();
	uploadVM();
	uploadPM();
}


void
Camera::setAxes()
{
	mRight = glm::row(mViewMat, 0);
	mUpward = glm::row(mViewMat, 1);
	mFront = -glm::row(mViewMat, 2);
}

void
Camera::moveLR(GLfloat cs)
{
	mEye += mRight * cs;
	mLook += mRight * cs;
	setVM();
}

void
Camera::moveFB(GLfloat cs)
{
	mEye += mFront * cs;
	mLook += mFront * cs; // Or else the mEye point would surpass the mLook and it would be behind the camera
	setVM();
}

void
Camera::moveUD(GLfloat cs)
{
	mEye += mUpward * cs;
	mLook += mUpward * cs;
	setVM();
}
void
Camera::changePrj()
{
	bOrto = !bOrto;
	setPM(); // Vuelve a calcular mProjMat según el tipo de vista
}

void 
Camera::pitchReal(GLfloat cs)
{
	GLdouble a = cs;
	mViewMat = rotate(mViewMat, glm::radians(a), glm::dvec3(mRight));
	// glm::rotate returns mViewMat * rotationMatrix

	setAxes(); // Update the Axes based on the new Matrix
}

void 
Camera::yawReal(GLfloat cs)
{
	GLdouble a = cs;
	mViewMat = rotate(mViewMat, glm::radians(a), glm::dvec3(mUpward));
	// glm::rotate returns mViewMat * rotationMatrix

	setAxes(); // Update the Axes based on the new Matrix
}

void 
Camera::rollReal(GLfloat cs)
{
	GLdouble a = cs;
	mViewMat = rotate(mViewMat, glm::radians(a), glm::dvec3(-mFront));
	// glm::rotate returns mViewMat * rotationMatrix

	setAxes(); // Update the Axes based on the new Matrix
}
