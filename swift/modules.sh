#!/bin/sh

MODULES_DIR=${PROJECT_TEMP_ROOT}/${SDK_NAME}/HadronModules/

if [ ! -L "${MODULES_DIR}/usr" ]; then
  mkdir -p "${MODULES_DIR}"
  cp "${HADRON_PATH}/swift/system.modulemap" "${MODULES_DIR}/module.modulemap"
  ln -s "${SDKROOT}/usr" "${MODULES_DIR}/usr"
fi
