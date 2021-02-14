#include "Hud.h"

Hud::Hud(void)
{
}

Hud::~Hud(void)
{
}

void Hud::DrawText(void){
	glDisable(GL_DEPTH_TEST);
	glPushMatrix();
		glLoadIdentity();
		SetOrthographicProjection();
		for (std::vector<Text>::const_iterator i = _text.begin(); i != _text.end(); ++i){
			glColor4fv((*i).GetColorFloatArray());
			glRasterPos2f((*i).GetX(), (*i).GetY());
			Printf((*i).GetFormat().c_str(), (*i).GetText().c_str());
		}
	glPopMatrix();
	ResetPerspectiveProjection();
	glEnable(GL_DEPTH_TEST);
}