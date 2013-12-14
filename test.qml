import QtQuick 2.0
import net.WonderRabbitProject.tmp 1.0

Row
{
  focus: true
  Keys.onEscapePressed: Qt.quit()

  GLTeapot
  {
    width: 320
    height: 240
  }
}
