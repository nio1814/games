#include <keys.h>
#include <vector3d.h>
#include <camera.h>
#include <mouse.h>
#include "gameobject.h"

void runKeys(level* lvl, Mouse *ms)
{
    CameraPoint *cam = &lvl->cameras->cpoints[lvl->cameras->currentPoint];
	Vector3D cam2look;
	Vector3D toSideDir;

	if(isKeys('E'))
	{
		cam->pos += lvl->majAxis*.1f;
		cam->look += lvl->majAxis*.1f;
	}
	if(isKeys('Q'))
	{
		cam->pos -= lvl->majAxis*.1f;
		cam->look -= lvl->majAxis*.1f;
	}
	if(isKeys('A'))
	{
        toSideDir =  cam->dir2RSide();
		cam->pos -= toSideDir*.1f;
		cam->look -= toSideDir*.1f;
	}
	if(isKeys('D'))
	{
        toSideDir =  cam->dir2RSide();
		cam->pos += toSideDir*.1f;
		cam->look += toSideDir*.1f;
	}
    if(isKeys(Qt::Key_Up) || isKeys('W'))
	{
		cam2look =  cam->look - cam->pos;
		cam2look.unitize();
		cam->pos += cam2look*.1f;
		cam->look += cam2look*.1f;
	}
    if(isKeys(Qt::Key_Down) || isKeys('S'))
	{
		cam2look =  cam->look - cam->pos;
		cam2look.unitize();
		cam->pos -= cam2look*.1f;
		cam->look -= cam2look*.1f;
	}
    if(isKeys(Qt::Key_Left))
	{
		cam2look =  cam->look - cam->pos;
		cam2look.unitize();
		cam2look = cam2look.rotate3D(&lvl->majAxis, 1.0f);
		cam->look = cam->pos + cam2look;
	}
    if(isKeys(Qt::Key_Right))
	{
		cam2look =  cam->look - cam->pos;
		cam2look.unitize();
		cam2look = cam2look.rotate3D(&lvl->majAxis, -1.0f);
		cam->look = cam->pos + cam2look;
	}
	
	cam2look =  cam->look - cam->pos;
	toSideDir = Cross(&cam2look,&lvl->majAxis);
	toSideDir.unitize();
	/*if(ms->y != ms->yOld)
	{
		cam2look = cam2look.rotate3D(&toSideDir,(ms->y-ms->yOld)*DEFMOUSETHROTTLEY);
		cam->look = cam->pos + cam2look;
	}
	cam2look =  cam->look - cam->pos;
	if(ms->x != ms->xOld)
	{
		cam2look = cam2look.rotate3D(&lvl->majAxis,-(ms->x-ms->xOld)*DEFMOUSETHROTTLEX);
		cam->look = cam->pos + cam2look;
	}*/

	return;
}