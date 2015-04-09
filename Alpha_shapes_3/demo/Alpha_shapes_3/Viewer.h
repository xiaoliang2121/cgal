#ifndef VIEWER_H
#define VIEWER_H

#include "typedefs.h"
#include <QGLViewer/qglviewer.h>
#include <QOpenGLFunctions_3_3_Core>
#include <QGLFunctions>
#include <QOpenGLVertexArrayObject>
#include <QGLBuffer>
#include <QOpenGLShaderProgram>



class Viewer : public QGLViewer, protected QGLFunctions {
  Q_OBJECT

  CGAL::Timer timer;
  Scene* scene;

  int nr_of_facets;
public:
  Viewer(QWidget* parent)
    : QGLViewer(parent)
  {
  }
  ~Viewer()
  {
    buffers[0].destroy();
    buffers[1].destroy();
    vao[0].destroy();
    vao[1].destroy();
  }
  void setScene(Scene* scene_)
  {
    scene = scene_;
  }

  void clear();

public:
  void draw();

  void 
  gl_draw_surface();

private:
  //Shaders elements

      int poly_vertexLocation;
      int tex_Location;
      int points_vertexLocation;
      int normalsLocation;
      int mvpLocation;
      int mvpLocation_points;
      int mvLocation;
      int colorLocation;
      int colorLocation_points;
      int lightLocation[5];


      std::vector<float> pos_points;
      std::vector<float> pos_poly;
      std::vector<float> normals;

      QGLBuffer buffers[3];
      QOpenGLVertexArrayObject vao[2];
      QOpenGLShaderProgram rendering_program;
      QOpenGLShaderProgram rendering_program_points;
      void initialize_buffers();
      void compute_elements();
      void attrib_buffers(QGLViewer*);
      void compile_shaders();
 public slots :
        void initializeGL();
 void sceneChanged();
 void changed(){
     compute_elements();
     initialize_buffers();
 }
 void alphaChanged();

};

#endif
