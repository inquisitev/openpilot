#pragma once

#include <QProcess>
#include "selfdrive/ui/qt/offroad/settings.h"
#include "selfdrive/ui/qt/widgets/controls.h"

class DeveloperPanel : public ListWidget {
  Q_OBJECT
public:
  explicit DeveloperPanel(SettingsWindow *parent);

private:
  Params params;
  ParamControl* joystickToggle;
  ParamControl* longManeuverToggle;
  ButtonControl* storageClearButton;
  std::unique_ptr<QProcess> clearStorageProcess;
  bool is_release;
  bool offroad;

private slots:
  void updateToggles(bool _offroad);
};
