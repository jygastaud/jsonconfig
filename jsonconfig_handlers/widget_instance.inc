<?php


function jsonconfig_widget_instance_handler_validate($def) {
  if (empty($def['type'])) {
    return FALSE;
  }
  if (empty($def['ref'])) {
    return FALSE;
  }
  return TRUE;
}

function jsonconfig_widget_instance_handler_preprocess(&$def) {
  $def += array(
    'weight' => 0,
  );
}

function jsonconfig_widget_instance_handler_create($def) {
  jsonconfig_store_value('widget_instance', $def['ref'], $def);
}

function jsonconfig_widget_instance_handler_refresh($def) {
  jsonconfig_widget_instance_handler_create($def);
}

function jsonconfig_widget_instance_handler_uninstall($def) {
  jsonconfig_remove_value('widget_instance', $def['ref']);
}

