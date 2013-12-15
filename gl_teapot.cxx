#include <iostream>
#include <QSGSimpleTextureNode>
#include <QQuickWindow>
#include <QOpenGLPaintDevice>
#include <QPainter>
#include <QOpenGLBuffer>
#include <GL/glu.h>
#include <GL/glut.h>
#include "gl_teapot.h"

gl_teapot::gl_teapot(QQuickItem *parent):
    QQuickItem(parent)
{
  setFlag(ItemHasContents);
  setSmooth(false);

  int argc = 0;
  glutInit(&argc, {});
  
  timer_id = startTimer(timer_interval);
}

gl_teapot::~gl_teapot()
{
  killTimer(timer_id);
}

void gl_teapot::timerEvent(QTimerEvent* e)
{
  timer_counter += timer_interval;
  update();
}

QSGNode* gl_teapot::updatePaintNode(QSGNode* node_old, UpdatePaintNodeData* data)
{
  
  if(width() <= 0 || height() <= 0)
  {
    delete node_old;
    return nullptr;
  }
  
  auto node = static_cast<QSGSimpleTextureNode*>(node_old);
  
  if(!node)
  {
    node = new QSGSimpleTextureNode();
    node->setFiltering(QSGTexture::Nearest);
  }
  
  // refresh texture
  {
    glPushClientAttrib(GL_CLIENT_ALL_ATTRIB_BITS);
    glPushAttrib(GL_ALL_ATTRIB_BITS);
    glMatrixMode(GL_TEXTURE);
    glPushMatrix();
    glLoadIdentity();
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    
    glShadeModel(GL_FLAT);
    glDisable(GL_CULL_FACE);
    glDisable(GL_LIGHTING);
    glDisable(GL_STENCIL_TEST);
    glDisable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
    
    delete fbo;
    fbo = nullptr;
    
    fbo = new QOpenGLFramebufferObject(width(), height(), QOpenGLFramebufferObject::Depth);
    node->setTexture(window()->createTextureFromId(fbo->texture(), fbo->size()));
    
    node->setRect(boundingRect());
    
    QMatrix4x4 flipY;
    flipY.translate(0.5 * width(), 0.5 * height());
    flipY.scale(1.0, -1.0);
    flipY.translate(0.5 * -width(),0.5 * -height());
    data->transformNode->setMatrix(flipY);
    
    if(fbo)
    {
      fbo->bind();
      
      QRectF drawRect(0, 0, width(), height());

      QOpenGLPaintDevice device(width(), height());
      QPainter painter;
      
      painter.begin(&device);
      
      painter.setRenderHints(QPainter::Antialiasing | QPainter::HighQualityAntialiasing);
      painter.fillRect(drawRect, QColor::fromHslF(std::cos(.001f * timer_counter) * .5f + .5f, 1.f, .9f));
      painter.drawTiledPixmap(drawRect, QPixmap(":/qt-project.org/qmessagebox/images/qtlogo-64.png"));
      
      painter.setPen(QPen(Qt::black, 0));
      QFont font;
      font.setPointSize(28);
      painter.setFont(font);
      painter.drawText(drawRect, "QML2\nGLTeapot", QTextOption(Qt::AlignRight | Qt::AlignBottom));
      
      painter.end();
      
      glMatrixMode(GL_PROJECTION);
      glLoadIdentity();
      gluPerspective(30., GLdouble(width()) / GLdouble(height()), 0.1, 1000.);
      
      glMatrixMode(GL_MODELVIEW);
      glLoadIdentity();
      float ex = 5.f * std::sin(.0005f * timer_counter);
      float ey = 3.f * std::sin(.0005f * timer_counter);
      float ez = 5.f * std::cos(.0005f * timer_counter);
      gluLookAt( ex, ey, ez
               , 0., 0., 0.
               , 0., 1., 0.
               );

      glEnable(GL_DEPTH_TEST);
      glEnable(GL_LIGHT0);
      glEnable(GL_LIGHTING);
      
      glViewport(0, 0, width(), height());
      
      glutSolidTeapot(0.8);
      
      fbo->release();
    }
    
    glMatrixMode(GL_TEXTURE);
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
    glPopAttrib();
    glPopClientAttrib();
  }
  
  //fbo->toImage().save("/tmp/hoge.png");

  return node;
}
