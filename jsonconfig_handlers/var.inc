<?php

function jsonconfig_var_handler_create($def) {
  foreach ($def as $key => $value) {
    variable_set($key, $value);
  }
}

function jsonconfig_var_handler_update($def) {
  jsonconfig_var_handler_create($def);
}

function jsonconfig_var_handler_uninstall($def) {
  foreach ($def as $key => $value) {
    variable_del($key);
  }
}

function jsonconfig_var_handler_list() {
  return db_select('variable')
      ->fields('variable', array('name'))
      ->execute()
      ->fetchAllKeyed(0,0);
}

function jsonconfig_var_handler_export($key) {
  return array(
    $key => variable_get($key),
  );
}