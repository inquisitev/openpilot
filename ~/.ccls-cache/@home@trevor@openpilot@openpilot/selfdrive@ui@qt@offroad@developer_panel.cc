#include <QDebug>
#include <iostream>

#include "selfdrive/ui/qt/offroad/developer_panel.h"
#include "qprocess.h"
#include "selfdrive/ui/qt/widgets/ssh_keys.h"
#include "selfdrive/ui/qt/widgets/controls.h"
#include "common/util.h"

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

  storageClearButton = new ButtonControl("Storage", tr("Clear"));
  addItem(storageClearButton);

  QObject::connect(storageClearButton, &ButtonControl::clicked, [=]() {
        clearStorageProcess->start("rm -rf ~/openpilot/openpilot/test");
        qInfo() << "Debug";
        std::cout << "TEST" <<std::endl;
  });

  QObject::connect(clearStorageProcess.get(), &QProcess::stateChanged, [=](QProcess::ProcessState state){
      switch (state) {
        case QProcess::ProcessState::NotRunning: {
          std::cout << "Not Running" <<std::endl;
          std::cout << QString(clearStorageProcess->readAllStandardError()).toStdString() << std::endl;
          std::cout << QString(clearStorageProcess->readAllStandardOutput()).toStdString() << std::endl;
          storageClearButton->setEnabled(true);
          break;
        }
        case QProcess::ProcessState::Starting:
        case QProcess::ProcessState::Running: {
          std::cout << "Running" <<std::endl;
          storageClearButton->setEnabled(false);
          break;
        }
      }

    updateToggles(offroad);
  });



  // Joystick and longitudinal maneuvers should be hidden on release branches
  is_release = params.getBool("IsReleaseBranch");

  // Toggles should be not available to change in onroad state
  QObject::connect(uiState(), &UIState::offroadTransition, this, &DeveloperPanel::updateToggles);
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

  offroad = _offroad;
}

void DeveloperPanel::showEvent(QShowEvent *event) {
  updateToggles(offroad);
}
