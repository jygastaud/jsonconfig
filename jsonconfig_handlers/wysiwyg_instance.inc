<?php


function jsonconfig_wysiwyg_instance_handler_validate($def) {
  if (empty($def['ref'])) {
    return FALSE;
  }
  return TRUE;
}

function jsonconfig_wysiwyg_instance_handler_preprocess(&$def) {
  $def += array(
    'weight' => 0,
  );
}

function jsonconfig_wysiwyg_instance_handler_create($def) {
  jsonconfig_store_value('wysiwyg_instance', $def['ref'], $def);
}

function jsonconfig_wysiwyg_instance_handler_refresh($def) {
  jsonconfig_wysiwyg_instance_handler_create($def);
}

function jsonconfig_wysiwyg_instance_handler_uninstall($def) {
  jsonconfig_remove_value('wysiwyg_instance', $def['ref']);
}

