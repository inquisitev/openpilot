#pragma once

#include <QProcess>
#include <QTimer>
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
  QTimer refresh_storage_percent_timer;
  bool is_release;
  bool offroad;
  int count_of_time_checked_since_clear{0};

private slots:
  void updateToggles(bool _offroad);
  void onRefreshTimerExpired();
  void updateStoragePercent();
};
