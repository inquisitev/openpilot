#include <QDebug>
#include <iostream>

#include "selfdrive/ui/qt/offroad/developer_panel.h"
#include "qprocess.h"
#include "selfdrive/ui/qt/widgets/ssh_keys.h"
#include "selfdrive/ui/qt/widgets/controls.h"

namespace{
  int MAX_REFRESH_COUNT = 20;
}

DeveloperPanel::DeveloperPanel(SettingsWindow *parent)
  : ListWidget(parent)
  , clearStorageProcess(std::make_unique<QProcess>()) {
  // SSH keys
  addItem(new SshToggle());
  addItem(new SshControl());

  joystickToggle = new ParamControl("JoystickDebugMode", tr("Joystick Debug Mode"), "", "");
  QObject::connect(joystickToggle, &ParamControl::toggleFlipped, [=](bool state) {
    params.putBool("LongitudinalManeuverMode", false);
    longManeuverToggle->refresh();
  });
  addItem(joystickToggle);

  longManeuverToggle = new ParamControl("LongitudinalManeuverMode", tr("Longitudinal Maneuver Mode"), "", "");
  QObject::connect(longManeuverToggle, &ParamControl::toggleFlipped, [=](bool state) {
    params.putBool("JoystickDebugMode", false);
    joystickToggle->refresh();
  });
  addItem(longManeuverToggle);

  storageClearButton = new ButtonControl("Storage: --\% remaining", tr("Clear"));
  addItem(storageClearButton);
  refresh_storage_percent_timer.setSingleShot(true);
  refresh_storage_percent_timer.setInterval(750);
  QObject::connect(&refresh_storage_percent_timer, &QTimer::timeout, this, &DeveloperPanel::onRefreshTimerExpired);

  QObject::connect(storageClearButton, &ButtonControl::clicked, [=]() {
        clearStorageProcess->start("python3 /data/openpilot/system/loggerd/delete_media.py");
        refresh_storage_percent_timer.start();
  });

  updateStoragePercent();

  is_release = params.getBool("IsReleaseBranch");
  QObject::connect(uiState(), &UIState::offroadTransition, [=](bool _offroad) {
    updateStoragePercent();
    for (auto btn : findChildren<ParamControl *>()) {
      btn->setVisible(!is_release);
      btn->setEnabled(_offroad);
    }
  });

  // Toggles should be not available to change in onroad state
  QObject::connect(uiState(), &UIState::offroadTransition, this, &DeveloperPanel::updateToggles);
}

void DeveloperPanel::onRefreshTimerExpired(){
  if (!isVisible()) return;

  updateStoragePercent();

  if(MAX_REFRESH_COUNT >=count_of_time_checked_since_clear++){
    refresh_storage_percent_timer.start();
  }
}

void DeveloperPanel::updateStoragePercent(){
  auto &sm = *(uiState()->sm);

  int freeperc = static_cast<int>(sm["deviceState"].getDeviceState().getFreeSpacePercent());
  storageClearButton->setTitle(QString("Storage: %1\% remaining").arg(freeperc));
  std::cout << "Updating Storage: " << freeperc << std::endl;
}

void DeveloperPanel::updateToggles(bool _offroad) {
  for (auto btn : findChildren<ParamControl *>()) {
    btn->setVisible(!is_release);
    btn->setEnabled(_offroad);
  }
  // longManeuverToggle should not be toggleable if the car don't have longitudinal control
  auto cp_bytes = params.get("CarParamsPersistent");
  if (!cp_bytes.empty()) {
    AlignedBuffer aligned_buf;
    capnp::FlatArrayMessageReader cmsg(aligned_buf.align(cp_bytes.data(), cp_bytes.size()));
    cereal::CarParams::Reader CP = cmsg.getRoot<cereal::CarParams>();
    longManeuverToggle->setEnabled(hasLongitudinalControl(CP) && _offroad);
  } else {
    longManeuverToggle->setEnabled(false);
  }

  updateStoragePercent();

  offroad = _offroad;
}
