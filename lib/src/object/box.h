#ifndef BOX_H
#define BOX_H


class object_box : public Object
{
public:
  float width, length, height;
  Vector3D normal, wvec, lvec;
  GLuint		texture[6];									// 1 Texture
  GLfloat rotate;
  Vector3D angles;
  bool touching[6];
  object_planes planes;

  object_box();
  object_box(float mass, float wid, float len, float hei, float ph, float th, Vector3D pos, Vector3D mAxis);
//	virtual void draw();
  //virtual bool doCollisions(const object_holder *allObjs);
//	void makeBase();
//	void flipBase();
};


#endif // BOX_H
