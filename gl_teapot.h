#pragma once
#include <QQuickItem>
#include <QOpenGLFramebufferObject>

class gl_teapot : public QQuickItem
{
  Q_OBJECT
  Q_DISABLE_COPY(gl_teapot)
    
public:
  gl_teapot(QQuickItem* parent = nullptr);
  ~gl_teapot();
  
protected:
  virtual void timerEvent(QTimerEvent*);
  virtual QSGNode* updatePaintNode(QSGNode*, UpdatePaintNodeData*);
  
private:
  QOpenGLFramebufferObject* fbo;
  int timer_id;
  uint64_t timer_counter;
  
  static constexpr int timer_interval = 16;
  static constexpr float pi = 3.14159265359f;
};

QML_DECLARE_TYPE(gl_teapot)